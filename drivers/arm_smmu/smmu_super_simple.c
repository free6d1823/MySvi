/*
 * Copyright (c) 2018-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* Before reading the code, you'd better read arm SMMU v3 spec first.
 * need to know what does stream ID mean*/
#include <string.h>
#include <stdlib.h>
#include <asm/io.h>
#include <target/console.h>
#include <target/bitops.h>
#include <target/cmdline.h>
#include <errno.h>
#include <target/spinlock.h>
#include <target/delay.h>
#include <target/heap.h>
#include <target/list.h>

#include "smmu_simple.h"

struct smmu_s1_config {
	volatile u64		*ctx_desc;
	volatile u64		*pgd;
	struct list_head	s1_cfg_list_entry;
};
/* An SMMUv3 instance */
struct arm_smmu_device {
	void				*dev;
	void __iomem			*base;

	struct list_head		smmu_list_entry;
	struct list_head		s1_cfg_list_head;
	volatile u64			*l1_strtab_desc;
	u64				strtab_base;
	u32				strtab_base_cfg;
};

LIST_HEAD(smmu_devs);
static int
smmu_reset_device(struct arm_smmu_device* smmu, bool bypass);
#define SMMU_BUFFER_ALIGN 128

/* GBPA is "special" */
static int arm_smmu_update_gbpa(struct arm_smmu_device *smmu, u32 set, u32 clr)
{
	int ret,times;
	u32 reg, __iomem *gbpa = smmu->base + ARM_SMMU_GBPA;

	reg = readl_relaxed(gbpa);
	times = 0;
	ret = -1;
	for (;;) {
		if(times++ > 10)
			break;
		if (!(reg & GBPA_UPDATE)) {
			ret = 0;
			break;
		}
		udelay(ARM_SMMU_POLL_TIMEOUT_US);
		reg = readl_relaxed(gbpa);
	}

	if (ret)
		return ret;

	reg &= ~clr;
	reg |= set;
	writel_relaxed(reg | GBPA_UPDATE, gbpa);

	times = 0;
	ret = -1;
	for (;;) {
		if(times++ > 10)
			break;
		if (!(reg & GBPA_UPDATE)) {
			ret = 0;
			break;
		}
		udelay(ARM_SMMU_POLL_TIMEOUT_US);
		reg = readl_relaxed(gbpa);
	}


	if (ret)
		dev_err(smmu->dev, "GBPA not responding to update\n");
	return ret;
}

static int arm_smmu_write_reg_sync(struct arm_smmu_device *smmu, u32 val,
				   unsigned int reg_off, unsigned int ack_off)
{
	int ret,times;
	u32 reg;

	writel_relaxed(val, smmu->base + reg_off);

	times = 0;
	ret = -1;
	reg = readl_relaxed(smmu->base + ack_off);
	for (;;) {
		if(times++ > 10)
			break;
		if (reg == val) {
			ret = 0;
			break;
		}
		udelay(ARM_SMMU_POLL_TIMEOUT_US);
		reg = readl_relaxed(smmu->base + ack_off);
	}

	return ret;
}

static int arm_smmu_device_disable(struct arm_smmu_device *smmu)
{
	int ret;

	ret = arm_smmu_write_reg_sync(smmu, 0, ARM_SMMU_CR0, ARM_SMMU_CR0ACK);
	if (ret)
		dev_err(smmu->dev, "failed to clear cr0\n");

	return ret;
}

#define SMMU_MAP_SAMPLE_CODE 1
#ifdef SMMU_MAP_SAMPLE_CODE
struct smmu_ram_mapping_t {
	unsigned long virt_addr;
	unsigned long phys_addr;
	unsigned long flag;
	unsigned long addr_size;
};

static void arm_lpae_map(unsigned long iova,
			  phys_addr_t paddr, size_t size, u64 prot,
			  volatile u64 *ptep)
{
	size_t block_size = SZ_1G;
	int index,i;
	volatile u64 *pte_tmp = ptep;

	/* Find our entry at the current level 
	 * only support 4KB granuity */
	index = iova >> (12+9+9);
	pte_tmp += index;

	if (size == block_size ) {
		u64 pte = prot;
		u64 pte_addr;

		pte |= ARM_LPAE_PTE_TYPE_BLOCK;

		pte |= ARM_LPAE_PTE_AF | ARM_LPAE_PTE_SH_IS;

		/* Of the bits which overlap, either 51:48 or 15:12 are always RES0 */
		pte_addr = (paddr | (paddr >> (48 - 12))) & ARM_LPAE_PTE_ADDR_MASK;
		pte |= pte_addr;

		*pte_tmp = pte;
		printf("Configured PGD entry at index %d with addr 0x%lx pte=0x%lx\n",
						index, pte_addr, pte);
		flush_dcache_addr(pte_tmp);
	} else {
		printf("mapping failed. Only support 0x%x block size\n", block_size);
	}
}

static u64 arm_lpae_prot_to_pte(int prot)
{
	u64 pte;


	pte = ARM_LPAE_PTE_nG;

	if (!(prot & IOMMU_WRITE) && (prot & IOMMU_READ))
		pte |= ARM_LPAE_PTE_AP_RDONLY;

	if (!(prot & IOMMU_PRIV))
		pte |= ARM_LPAE_PTE_AP_UNPRIV;

	if (prot & IOMMU_MMIO)
		pte |= (ARM_LPAE_MAIR_ATTR_IDX_DEV
			<< ARM_LPAE_PTE_ATTRINDX_SHIFT);
	else if (prot & IOMMU_CACHE)
		pte |= (ARM_LPAE_MAIR_ATTR_IDX_CACHE
			<< ARM_LPAE_PTE_ATTRINDX_SHIFT);


	if (prot & IOMMU_NOEXEC)
		pte |= ARM_LPAE_PTE_XN;

	return pte;
}

struct smmu_ram_mapping_t smmu_mapping[] = {
	{.virt_addr = 0x40000000,
	 .phys_addr = 0x40000000,
	 .flag = (IOMMU_READ | IOMMU_WRITE),
	 .addr_size = SZ_1G},
};

int smmu_ram_map(volatile u64* pgd,
			struct smmu_ram_mapping_t* map_table)
{
	int index,size;
	unsigned long i,virt_addr,phys_addr,flag,addr_size;
	unsigned long prot;

	if (NULL == map_table)
		return 0;

	size = sizeof(*map_table) / sizeof(map_table[0]);

	for (index=0; index<size; index++) {
		virt_addr = map_table[index].virt_addr;
		phys_addr = map_table[index].phys_addr;
		flag = map_table[index].flag;
		addr_size = map_table[index].addr_size;

		if (!(flag & (IOMMU_READ | IOMMU_WRITE)))
			return 0;

		/*if (WARN_ON(virt_addr >= (1ULL << ias) ||
				paddr >= (1ULL << data->iop.cfg.oas)))
			return -ERANGE;*/
		printf("mapping virt_addr = 0x%lx to 0x%lx\n",
					virt_addr, phys_addr);
		prot = arm_lpae_prot_to_pte(flag);
		for (i=0; i<(addr_size/SZ_1G); i++) {
			arm_lpae_map(virt_addr+SZ_1G*i, phys_addr+SZ_1G*i, SZ_1G, prot,
						pgd);
			/*
			* Synchronise all PTE updates for the new mapping before there's
			* a chance for anything to kick off a table walk for the new iova.
			*/
			dmb(sy);
		}
	}
	return 0;

}

u64* smmu_get_s1ctx(struct arm_smmu_device* smmu, int sid)
{
	u64 *l1_desc, *dst;
	u64	l2ptr, s1ContextPtr;
	int idx;

	l1_desc = (u64*)smmu->l1_strtab_desc;
	idx = (sid >> STRTAB_SPLIT) * STRTAB_L1_DESC_DWORDS;
	l1_desc += idx;

	l2ptr = ((u64)*l1_desc & STRTAB_L1_DESC_L2PTR_MASK);
	dst = (u64*)l2ptr;
	idx = (sid & ((1 << STRTAB_SPLIT) - 1)) * STRTAB_STE_DWORDS;
	dst += idx;

	s1ContextPtr = dst[0] & STRTAB_STE_0_S1CTXPTR_MASK;
	dst = (u64*)s1ContextPtr;
	return dst;
}

void smmu_config_remap(struct arm_smmu_device* smmu, int sid,
				u64 virt_addr, u64 phys_addr, u64 addr_size)
{
	struct smmu_ram_mapping_t  map;
	volatile u64* pgd;
	u64* s1_ctx;

	if (!smmu || !smmu->l1_strtab_desc) {
		printf("SMMU is null\n");
		return;
	}

	s1_ctx = smmu_get_s1ctx(smmu, sid);
	if (!s1_ctx) {
		printf("failed to get s1 context descriptor\n");
		return;
	}

	printf("s1_ctx value 0x%lx, 0x%lx\n", s1_ctx[0], s1_ctx[1]);
	pgd = (volatile u64*)(s1_ctx[1] & CTXDESC_CD_1_TTB0_MASK);

	if (!pgd) {
		printf("failed to get pgd from s1 context descriptor\n");
		return;
	}
	map.addr_size = addr_size / SZ_1G * SZ_1G;
	if (addr_size%SZ_1G != 0)
		map.addr_size += SZ_1G;
	map.flag = (IOMMU_READ | IOMMU_WRITE);
	map.virt_addr = virt_addr / SZ_1G * SZ_1G;
	map.phys_addr = phys_addr - (virt_addr - map.virt_addr);

	if ((virt_addr + addr_size) > (map.virt_addr + map.addr_size)){
		map.addr_size += SZ_1G;
	}

	smmu_ram_map(pgd, &map);
}
#endif

void  smmu_2lvl_data_dump(struct arm_smmu_device* smmu, int sid)
{
	int idx;
	u64 *l1_desc, *dst;
	u64	l2ptr, s1ContextPtr;
	u32 strtab_cfg;
	idx = (sid >> STRTAB_SPLIT) * STRTAB_L1_DESC_DWORDS;
	l1_desc = (u64*)(smmu->strtab_base & 0xFFFFFFFFFF);
	l1_desc += idx;
	printf("2 levles Strtab info dump:\n");

	strtab_cfg =readl_relaxed(smmu->base + ARM_SMMU_STRTAB_BASE_CFG);
	printf("\t strbase cfg reg=0x%x\n",strtab_cfg);
	printf("\t l1_desc at sid %d's address = 0x%lx\n",
				sid, (u64)l1_desc);
	l2ptr = ((u64)*l1_desc & STRTAB_L1_DESC_L2PTR_MASK);
	printf("\t l2_desc(STE) at sid %d's address = 0x%lx\n", sid, l2ptr);
	dst = (u64*)l2ptr;
	idx = (sid & ((1 << STRTAB_SPLIT) - 1)) * STRTAB_STE_DWORDS;
	dst += idx;
	printf("\t dump strtab info at sid %d\n", sid);
	printf("\t\t dst[0]=0x%lx, dst[1]=0x%lx, dst[2]=0x%lx, dst[3]=0x%lx\n\n",
				dst[0], dst[1], dst[2], dst[3]);

	s1ContextPtr = dst[0] & STRTAB_STE_0_S1CTXPTR_MASK;
	if (s1ContextPtr) {
		printf("\t dump context descriptor at sid %d\n", sid);
		dst = (u64*)s1ContextPtr;
		printf("\t\t dst[0]=0x%lx, dst[1]=0x%lx, dst[2]=0x%lx, dst[3]=0x%lx\n",
					dst[0], dst[1], dst[2], dst[3]);
	}
}

void smmu_bypass_abort(struct arm_smmu_device* smmu, int sid, bool bypass)
{
	volatile u64* dst;
	u32 idx;
	u64 val, l2_strtab;
	if (!smmu || (!smmu->l1_strtab_desc)) {
		printf("smmu device has not been initialized\n");
		return;
	}
	if (sid == -1)
	{
		arm_smmu_update_gbpa(smmu, 0, GBPA_ABORT);
		arm_smmu_write_reg_sync(smmu, 0, ARM_SMMU_CR0,
					ARM_SMMU_CR0ACK);
		printf("smmu device is disabled\n");
		return;
	}

	idx = (sid >> STRTAB_SPLIT);
	/* find out the l1_desc*/
	dst = smmu->l1_strtab_desc + idx;

	/* find out the l2_desc*/
	l2_strtab = dst[0] & STRTAB_L1_DESC_L2PTR_MASK;
	dst = (volatile u64*)l2_strtab;
	idx = (sid & ((1 << STRTAB_SPLIT) - 1)) * STRTAB_STE_DWORDS;
	dst += idx;

	smmu_2lvl_data_dump(smmu, sid);
	val = STRTAB_STE_0_V;
	/* bypass sid entry*/
	if (bypass) {
		val |= FIELD_PREP(STRTAB_STE_0_CFG, STRTAB_STE_0_CFG_BYPASS);
		dst[0] = val;
		printf("bypass sid %d\n", sid);
	} else {
		val |= FIELD_PREP(STRTAB_STE_0_CFG, STRTAB_STE_0_CFG_ABORT);
		dst[0] = val;
		dst[1] = dst[2] = dst[3] = 0;
		arm_smmu_device_disable(smmu);
		arm_smmu_update_gbpa(smmu, 1, GBPA_ABORT);
		arm_smmu_write_reg_sync(smmu, 1, ARM_SMMU_CR0,
					ARM_SMMU_CR0ACK);
		printf("abort sid %d\n", sid);
	}
	/* volatile to gurantee to write into memory*/
	flush_dcache_addr(dst);

	smmu_2lvl_data_dump(smmu, sid);
}

void smmu_close(struct arm_smmu_device* smmu)
{
	u64 *l1_desc, *dst, *l2_desc;
	struct smmu_s1_config* tmp_s1;
	int i;
	u64 reg64;

	/* bypass the SMMU first */
	smmu_bypass_abort(smmu, -1, true);
	reg64 = readq_relaxed(smmu->base + ARM_SMMU_STRTAB_BASE);
	if (!reg64) {
			printf("smmu is not used\n");
			return;
	}

	l1_desc = (u64*)(reg64 & 0xFFFFFFFFFF);
	dst = l1_desc;
	for (i=0; i<3; i++) {
		if (dst[i] != 0) {
			l2_desc = (u64*)(dst[i] & STRTAB_L1_DESC_L2PTR_MASK);
			if (l2_desc != NULL)
				heap_free(l2_desc);
		}
		dst++;
	}
	heap_free(l1_desc);

	list_for_each_entry(struct smmu_s1_config, tmp_s1,
		&smmu->s1_cfg_list_head, s1_cfg_list_entry) {
			if (tmp_s1->ctx_desc != 0) {
				heap_free((void *)tmp_s1->ctx_desc);
			}
			if (tmp_s1->pgd)
				heap_free((void *)tmp_s1->pgd);
			heap_free(tmp_s1);
		}
	list_del(&smmu->smmu_list_entry);
	heap_free((void*)smmu);
}


/* Context descriptor manipulation functions */
static u64 arm_smmu_cpu_tcr_to_cd(u64 tcr)
{
	u64 val = 0;

	/* Repack the TCR. Just care about TTBR0 for now */
	val |= ARM_SMMU_TCR2CD(tcr, T0SZ);
	val |= ARM_SMMU_TCR2CD(tcr, TG0);
	val |= ARM_SMMU_TCR2CD(tcr, IRGN0);
	val |= ARM_SMMU_TCR2CD(tcr, ORGN0);
	val |= ARM_SMMU_TCR2CD(tcr, SH0);
	val |= ARM_SMMU_TCR2CD(tcr, EPD0);
	val |= ARM_SMMU_TCR2CD(tcr, EPD1);
	val |= ARM_SMMU_TCR2CD(tcr, IPS);
	val |= ARM_SMMU_TCR2CD(tcr, TBI0);

	return val;
}

static int
configure_s1_ctx_with_ioas(volatile u64* ctx_desc,
						u64 pgd, long ias, long oas)
{
	u64 reg, val;

	if (ctx_desc == NULL || !pgd) {
		printf("context descriptor is NULL, failed to config it\n");
		return 0;
	}

	ctx_desc[1] = ((u64)pgd & CTXDESC_CD_1_TTB0_MASK);
	/* TCR */
	reg = (ARM_LPAE_TCR_SH_IS << ARM_LPAE_TCR_SH0_SHIFT) |
	      (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_IRGN0_SHIFT) |
	      (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_ORGN0_SHIFT);

	reg |= ARM_LPAE_TCR_TG0_4K;
	/* only support 4KB size currently
	 * ARM_LPAE_TCR_TG0_16K;
	 * ARM_LPAE_TCR_TG0_64K;
	 * */
	switch (oas) {
	case 32:
		reg |= (ARM_LPAE_TCR_PS_32_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 36:
		reg |= (ARM_LPAE_TCR_PS_36_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 40:
		reg |= (ARM_LPAE_TCR_PS_40_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 42:
		reg |= (ARM_LPAE_TCR_PS_42_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 44:
		reg |= (ARM_LPAE_TCR_PS_44_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 48:
		reg |= (ARM_LPAE_TCR_PS_48_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	case 52:
		reg |= (ARM_LPAE_TCR_PS_52_BIT << ARM_LPAE_TCR_IPS_SHIFT);
		break;
	default:
		goto out_free_data;
	}

	reg |= (64ULL - ias) << ARM_LPAE_TCR_T0SZ_SHIFT;

	/* Disable speculative walks through TTBR1 */
	reg |= ARM_LPAE_TCR_EPD1;

	val = arm_smmu_cpu_tcr_to_cd(reg) |
#ifdef __BIG_ENDIAN_ENABLE
	      CTXDESC_CD_0_ENDI |
#endif
	      CTXDESC_CD_0_R | CTXDESC_CD_0_A | CTXDESC_CD_0_ASET |
	      CTXDESC_CD_0_AA64 | FIELD_PREP(CTXDESC_CD_0_ASID, 0) |
	      CTXDESC_CD_0_V;
	ctx_desc[0] = val;

	/* MAIRs */
	reg = (ARM_LPAE_MAIR_ATTR_NC
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_NC)) |
	      (ARM_LPAE_MAIR_ATTR_WBRWA
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_CACHE)) |
	      (ARM_LPAE_MAIR_ATTR_DEVICE
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_DEV));

	ctx_desc[3] = reg;
	flush_dcache_area((void *)ctx_desc, 64);
	return 1;
out_free_data:
	printf("not supported oas %d\n", oas);
	return 0;
}

static int
smmu_reset_device(struct arm_smmu_device* smmu, bool bypass)
{
	u32 reg, enables;
	int ret;

	/* Clear CR0 and sync (disables SMMU and queue processing) */
	reg = readl_relaxed(smmu->base + ARM_SMMU_CR0);
	if (reg & CR0_SMMUEN) {
		printf("SMMU currently enabled! Resetting...\n");
	}

	ret = arm_smmu_device_disable(smmu);
	if (ret)
		return ret;

	/* CR1 (table and queue memory attributes) */
	reg = FIELD_PREP(CR1_TABLE_SH, ARM_SMMU_SH_ISH) |
		FIELD_PREP(CR1_TABLE_OC, CR1_CACHE_WB) |
		FIELD_PREP(CR1_TABLE_IC, CR1_CACHE_WB) |
		FIELD_PREP(CR1_QUEUE_SH, ARM_SMMU_SH_ISH) |
		FIELD_PREP(CR1_QUEUE_OC, CR1_CACHE_WB) |
		FIELD_PREP(CR1_QUEUE_IC, CR1_CACHE_WB);
	writel_relaxed(reg, smmu->base + ARM_SMMU_CR1);

	/* CR2 (random crap) */
	reg = CR2_PTM | CR2_RECINVSID | CR2_E2H;
	writel_relaxed(reg, smmu->base + ARM_SMMU_CR2);

	/* Stream table */
	writeq_relaxed(smmu->strtab_base,
			smmu->base + ARM_SMMU_STRTAB_BASE);
	writel_relaxed(smmu->strtab_base_cfg,
			smmu->base + ARM_SMMU_STRTAB_BASE_CFG);
	/* Enable the SMMU interface, or ensure bypass */
	if (!bypass) {
		enables = CR0_SMMUEN;
	} else {
		ret = arm_smmu_update_gbpa(smmu, 0, GBPA_ABORT);
		if (ret)
			return ret;
	}
	ret = arm_smmu_write_reg_sync(smmu, enables, ARM_SMMU_CR0,
					ARM_SMMU_CR0ACK);
	if (ret) {
		printf("failed to enable smmu\n");
		return ret;
	}
	return 0;
}

#define L1_DESC_ENTRIES 3
struct arm_smmu_device*
smmu_fast_configure(u64 smmu_base, u16 sid, struct arm_smmu_device* smmu_o)
{
	struct arm_smmu_device* smmu;
	volatile u64 *l1_strtab_desc, *l2_strtab, *ctx_desc, *pgd, *dst;
	u64 reg64, val;
	int idx, ret;
	bool bypass;

	if ((sid != -1) &&
		(sid > (L1_DESC_ENTRIES * (1<<STRTAB_SPLIT)))) {
		printf("error: stream ID exceeded the maximum %d\n");
		return NULL;
	}

	smmu = smmu_o;
	if (smmu == NULL) {
		smmu = heap_aligned_alloc(SMMU_BUFFER_ALIGN, sizeof(struct arm_smmu_device));
		if (!smmu) {
			printf("Error: not enough buffer.\n");
			return NULL;
		}

		printf("first time allocation, create smmu device and l1 strtab pointer\n");

		memset(smmu, 0, sizeof(struct arm_smmu_device));
		smmu->base = (void*)smmu_base;
		INIT_LIST_HEAD(&smmu->s1_cfg_list_head);
		/*
		*Level1 stream Table descriptor's size is 8bytes, just allocate
		* 3 entries, The maximum SID is 3*2^8
		*/
		l1_strtab_desc = (u64*)heap_aligned_alloc(SMMU_BUFFER_ALIGN, 8 * L1_DESC_ENTRIES);
		if (!l1_strtab_desc) {
			printf("Error: not enough buffer to allocate l1.\n");
			return NULL;
		}
		memset((void *)l1_strtab_desc, 0, 8 * L1_DESC_ENTRIES);
		smmu->l1_strtab_desc = l1_strtab_desc;

		/* Configure strtab register*/
		reg64  = (u64)l1_strtab_desc & STRTAB_BASE_ADDR_MASK;
		reg64 |= STRTAB_BASE_RA;
		smmu->strtab_base = reg64;

		/* Configure strtab_base_cfg for 2 levels */
		reg64  = FIELD_PREP(STRTAB_BASE_CFG_FMT, STRTAB_BASE_CFG_FMT_2LVL);
		reg64 |= FIELD_PREP(STRTAB_BASE_CFG_LOG2SIZE, 16);
		reg64 |= FIELD_PREP(STRTAB_BASE_CFG_SPLIT, STRTAB_SPLIT);
		smmu->strtab_base_cfg = reg64;
		/* reset device*/
		if (smmu_reset_device(smmu, false)) {
			printf("failed to reset device, exit\n");
			heap_free((void*)l1_strtab_desc);
			heap_free((void*)smmu);
			return NULL;
		}
	}

	if (sid == -1)
		return smmu;

	if (!smmu->l1_strtab_desc) {
		printf("l1 strtab not exist, bad error\n");
		return NULL;
	}
	idx = (sid >> STRTAB_SPLIT);
	dst = smmu->l1_strtab_desc + idx;

	/* does L2 strtab already exist */
	if (dst[0] == 0) {
		/* Level2 stream Table size is 64bytes, just allocate
		* 256 entries*/
		l2_strtab = (u64*)heap_aligned_alloc(SMMU_BUFFER_ALIGN, 64 * (1<<STRTAB_SPLIT));
		if (!l2_strtab) {
			printf("Error: not enough buffer to allocate l2.\n");
			return NULL;
		}

		printf("L2 strtab doesn't exist for sid %d, create new\n", sid);
		val = STRTAB_STE_0_V;
		/* bypass all entries*/
		val |= FIELD_PREP(STRTAB_STE_0_CFG, STRTAB_STE_0_CFG_BYPASS);
		memset((void *)l2_strtab, val, 64 * (1<<STRTAB_SPLIT));

		/* Configure l1 strtab pointer*/
		idx = (sid >> STRTAB_SPLIT);
		dst = l1_strtab_desc + idx;
		val = 0;
		val |= FIELD_PREP(STRTAB_L1_DESC_SPAN, STRTAB_SPLIT + 1);
		/* suppose virt = physical address */
		val |= (u64)l2_strtab & STRTAB_L1_DESC_L2PTR_MASK;
		*dst = val;
		flush_dcache_addr(dst);
	} else {
		printf("L2 strtab already exist for sid %d, use old\n", sid);
		val = dst[0] & STRTAB_L1_DESC_L2PTR_MASK;
		l2_strtab = (u64*)val;
	}

	dst = l2_strtab;
	idx = (sid & ((1 << STRTAB_SPLIT) - 1)) * STRTAB_STE_DWORDS;
	dst += idx;
	if (FIELD_GET(STRTAB_STE_0_CFG, dst[0] & 0xF) != STRTAB_STE_0_CFG_BYPASS) {
		printf("current SID %d has been configured\n", sid);
		return NULL;
	} else {
		printf("configure new SID %d\n", sid);
	}

	struct smmu_s1_config *s1_cfg = (struct smmu_s1_config*)
		heap_aligned_alloc(SMMU_BUFFER_ALIGN, sizeof(struct smmu_s1_config));
	/* Context descriptor structure size is 64bytes, just allocate
	* one*/
	ctx_desc = (u64*)heap_aligned_alloc(SMMU_BUFFER_ALIGN, 64 * 1);

	/* PGD structure is 8ytes, allocate 16 blocks to support maximux 16GB */
	pgd = (u64*)heap_aligned_alloc(PAGE_SIZE, 8 * 16);

	/* Caution: suppose virtual address == physical address*/
	if (!s1_cfg || !ctx_desc || !pgd) {
		printf("Error: not enough buffer. memory leak\n");
		return NULL;
	}

	s1_cfg->ctx_desc = ctx_desc;
	s1_cfg->pgd		 = pgd;
	/* add into list for memory management*/
	list_add_tail(&s1_cfg->s1_cfg_list_entry, &smmu->s1_cfg_list_head);

	/* Configure l2 strtab */
	val = STRTAB_STE_0_V;
	val |= FIELD_PREP(STRTAB_STE_0_CFG, STRTAB_STE_0_CFG_S1_TRANS);
	dst[0] = val | ((u64)ctx_desc & STRTAB_STE_0_S1CTXPTR_MASK);
	dst[1] = (FIELD_PREP(STRTAB_STE_1_S1CIR, STRTAB_STE_1_S1C_CACHE_WBRA) |
			 FIELD_PREP(STRTAB_STE_1_S1COR, STRTAB_STE_1_S1C_CACHE_WBRA) |
			 FIELD_PREP(STRTAB_STE_1_S1CSH, ARM_SMMU_SH_ISH) |
#ifdef CONFIG_PCI_ATS
			 FIELD_PREP(STRTAB_STE_1_EATS, STRTAB_STE_1_EATS_TRANS) |
#endif
			 FIELD_PREP(STRTAB_STE_1_STRW, STRTAB_STE_1_STRW_NSEL1));
	dst[2] = 0x0;
	dst[3] = 0x0;

	flush_dcache_area((void *)dst, 64);
	/* Configure Context descriptor */
	dst = ctx_desc;
	configure_s1_ctx_with_ioas(dst, (u64)pgd, 32, 32);

	/* basic sanity check */
	if (0)
	{
		u64 *l1_str, *step, *cd_p;
		u64 s1ContextPtr, ttb0;
		reg64 = readq_relaxed(smmu->base + ARM_SMMU_STRTAB_BASE);
		if ((!reg64) || (smmu->strtab_base != reg64)) {
			printf("error: smmu stream table failed 0x%lx, ori=0x%lx\n",
						reg64, smmu->strtab_base);
			return NULL;
		}

		l1_str = (u64*)(reg64 & 0xFFFFFFFFFF);
		idx = (sid >> STRTAB_SPLIT);
		l1_str += idx;
		if (!l1_str) {
			printf("error: l1 ste entry miss\n");
			return NULL;
		}
		/* suppose virt = physical address */
		val = (u64)(*l1_str) & STRTAB_L1_DESC_L2PTR_MASK;
		step = (u64*)val;
		if (!l1_str) {
			printf("error: l2 ste entry miss\n");
			return NULL;
		}
		idx = (sid & ((1 << STRTAB_SPLIT) - 1)) * STRTAB_STE_DWORDS;
		step += idx;

		s1ContextPtr = (STRTAB_STE_0_S1CTXPTR_MASK & step[0]);
		if ((!s1ContextPtr) || ((u64)ctx_desc != s1ContextPtr)) {
			printf("error: smmu ste->contextptr doesn't match\n");
			printf("\t cdptr form STE=0x%lx, orginal=0x%lx, STE ori=0x%lx\n",
						s1ContextPtr, (u64)ctx_desc, step[0]);
			return NULL;
		}

		if (s1ContextPtr) {
			cd_p = (u64*)phys_to_virt(s1ContextPtr);
			ttb0 = (CTXDESC_CD_1_TTB0_MASK & cd_p[1]);

			if ((!ttb0) || (ttb0 != (u64)pgd)) {
				printf("error: smmu ste->contextptr->PGD doesn't match\n");
				printf("\t PGD from CD=0x%lx, orginal=0x%lx, CD ori=0x%lx\n",
						ttb0, (u64)pgd, cd_p[1]);
				return NULL;
			}
		} else {
			printf("error: smmu ste->contextptr not found\n");
			return NULL;
		}
	}
	/* mapping the address */
	smmu_ram_map(pgd, smmu_mapping);

	dmb(sy);

	return smmu;
}

/***************************************************
 * how to get streamID when pci device is connected to smmu
 *
 * #define PCI_DEVID(bus, devfn)	((((u16)(bus)) << 8) | (devfn))
 * #define PCI_DEVFN(slot, func)	((((slot) & 0x1f) << 3) | ((func) & 0x07))
 * streamID = PCI_DEVID(bus, devfn)
 *
 * *************************************************/

static int do_smmu_test(int argc, char *argv[])
{
	int sid;
	uint64_t smmu_base;
	u64 virt_addr, phys_addr, addr_size;
	bool bypass, abort, close, remap;

	bypass = abort = close = remap = false;
	if (!strcmp(argv[1],"bypass")) {
		if (!strcmp(argv[2],"default"))
			smmu_base = SMMU_V3_BASE;
		else
			smmu_base = strtoull(argv[2], 0, 0);
		bypass = true;
		sid = strtoul(argv[3], NULL, 0);
		if (argc != 4)
			return -EUSAGE;
		printf("bypass sid value =%d with smmu addr 0x%08llx\n",sid, smmu_base);
	} else if (!strcmp(argv[1],"init")) {
		if (!strcmp(argv[2],"default"))
			smmu_base = SMMU_V3_BASE;
		else
			smmu_base = strtoull(argv[2], 0, 0);
		if (argc != 4)
			return -EUSAGE;
		sid = strtoul(argv[3], NULL, 0);

		printf("init sid value =%d with smmu addr 0x%08llx\n",sid, smmu_base);
	} else if (!strcmp(argv[1],"abort")) {
		if (!strcmp(argv[2],"default"))
			smmu_base = SMMU_V3_BASE;
		else
			smmu_base = strtoull(argv[2], 0, 0);
		if (argc != 4)
			return -EUSAGE;
		sid = strtoul(argv[3], NULL, 0);
		abort = true;
		printf("abort sid value =%d with smmu addr 0x%08llx\n",sid, smmu_base);
	} else if (!strcmp(argv[1],"close")) {
		if (!strcmp(argv[2],"default"))
			smmu_base = SMMU_V3_BASE;
		else
			smmu_base = strtoull(argv[2], 0, 0);
		if (argc != 3)
			return -EUSAGE;
		close = true;
		printf("close smmu addr 0x%08llx\n", smmu_base);
	} else if (!strcmp(argv[1],"configmap")) {
		if (!strcmp(argv[2],"default"))
			smmu_base = SMMU_V3_BASE;
		else
			smmu_base = strtoull(argv[2], 0, 0);
		if (argc != 7)
			return -EUSAGE;
		sid = strtoul(argv[3], NULL, 0);
		virt_addr = strtoull(argv[4], 0, 0);
		phys_addr = strtoull(argv[5], 0, 0);
		addr_size = strtoull(argv[6], 0, 0);
		remap = true;
		printf("remap smmu addr 0x%08llx, virt_addr=0x%lx, 0x%lx, 0x%lx\n",
					smmu_base, virt_addr, phys_addr, addr_size);
	} else{
		return -EUSAGE;
	}

	{/* smmu test code */
		struct arm_smmu_device* smmu, *tmp_smmu;

		smmu = NULL;
		list_for_each_entry(struct arm_smmu_device, tmp_smmu,
			&smmu_devs, smmu_list_entry) {
			if ((u64)tmp_smmu->base == smmu_base) {
				smmu = tmp_smmu;
				break;
			}
		}

		if (smmu && bypass)
			smmu_bypass_abort(smmu, sid, true);
		if (smmu && abort)
			smmu_bypass_abort(smmu, sid, false);
		if (smmu && close)
			smmu_close(smmu);
		if (smmu && remap)
			smmu_config_remap(smmu, sid, virt_addr, phys_addr, addr_size);

		if (bypass || abort || close | remap)
			return 1;

		if (NULL == smmu) {
			/* caution: critical resource, no protection, don't use in multi_thread*/
			smmu = smmu_fast_configure(smmu_base, sid, NULL);
			list_add_tail(&smmu->smmu_list_entry, &smmu_devs);
		} else {
			smmu = smmu_fast_configure(smmu_base, sid, smmu);
		}
	}

	return 1;
}

MK_CMD(smmu, do_smmu_test, "smmu basic test",
	"smmu init <smmu_addr> <sid>\n"
	"    - Init SMMU device and configure the page table for the StreamID.\n"
	"smmu bypass <smmu_addr> <sid>\n"
	"    -SMMU passes the IO access issued by device/SID\n"
	"smmu abort <smmu_addr> <sid>\n"
	"    -IO access is block/aborted by SMMU\n"
	"smmu configmap <smmu_addr> <sid> <virt> <phys> <size>\n"
	"    -Configure a specific SMMU address mapping.\n"
	"smmu close <smmu_addr>\n"
	"    -Close the smmu device allocated by smmu init <smmu_addr> <sid>\n"
);
