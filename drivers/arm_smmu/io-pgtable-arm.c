/*
 * CPU-agnostic ARM page table allocator.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2014 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */
#include <string.h>
#include <asm/io.h>
#include <target/console.h>
#include <target/bitops.h>
#include <target/cmdline.h>
#include <errno.h>

#include "io-pgtable.h"

#define PAGE_MASK		(~(PAGE_SIZE-1))

#define ARM_LPAE_MAX_ADDR_BITS		52
#define ARM_LPAE_S2_MAX_CONCAT_PAGES	16
#define ARM_LPAE_MAX_LEVELS		4

/* Struct accessors */
#define io_pgtable_to_data(x)						\
	container_of((x), struct arm_lpae_io_pgtable, iop)

#define io_pgtable_ops_to_data(x)					\
	io_pgtable_to_data(io_pgtable_ops_to_pgtable(x))

/*
 * For consistency with the architecture, we always consider
 * ARM_LPAE_MAX_LEVELS levels, with the walk starting at level n >=0
 */
#define ARM_LPAE_START_LVL(d)		(ARM_LPAE_MAX_LEVELS - (d)->levels)

/*
 * Calculate the right shift amount to get to the portion describing level l
 * in a virtual address mapped by the pagetable in d.
 */
#define ARM_LPAE_LVL_SHIFT(l,d)						\
	((((d)->levels - ((l) - ARM_LPAE_START_LVL(d) + 1))		\
	  * (d)->bits_per_level) + (d)->pg_shift)

#define ARM_LPAE_GRANULE(d)		(1UL << (d)->pg_shift)

#define ARM_LPAE_PAGES_PER_PGD(d)					\
	DIV_ROUND_UP((d)->pgd_size, ARM_LPAE_GRANULE(d))

/*
 * Calculate the index at level l used to map virtual address a using the
 * pagetable in d.
 */
#define ARM_LPAE_PGD_IDX(l,d)						\
	((l) == ARM_LPAE_START_LVL(d) ? __ilog2(ARM_LPAE_PAGES_PER_PGD(d)) : 0)

#define ARM_LPAE_LVL_IDX(a,l,d)						\
	(((u64)(a) >> ARM_LPAE_LVL_SHIFT(l,d)) &			\
	 ((1 << ((d)->bits_per_level + ARM_LPAE_PGD_IDX(l,d))) - 1))


/* Calculate the block/page mapping size at level l for pagetable in d. */
#define ARM_LPAE_BLOCK_SIZE(l,d)					\
	(1ULL << (__ilog2(sizeof(arm_lpae_iopte)) +			\
		((ARM_LPAE_MAX_LEVELS - (l)) * (d)->bits_per_level)))

/* Page table bits */
#define ARM_LPAE_PTE_TYPE_SHIFT		0
#define ARM_LPAE_PTE_TYPE_MASK		0x3

#define ARM_LPAE_PTE_TYPE_BLOCK		1
#define ARM_LPAE_PTE_TYPE_TABLE		3
#define ARM_LPAE_PTE_TYPE_PAGE		3

#define ARM_LPAE_PTE_ADDR_MASK		GENMASK_ULL(47,12)

#define ARM_LPAE_PTE_NSTABLE		(((arm_lpae_iopte)1) << 63)
#define ARM_LPAE_PTE_XN			(((arm_lpae_iopte)3) << 53)
#define ARM_LPAE_PTE_AF			(((arm_lpae_iopte)1) << 10)
#define ARM_LPAE_PTE_SH_NS		(((arm_lpae_iopte)0) << 8)
#define ARM_LPAE_PTE_SH_OS		(((arm_lpae_iopte)2) << 8)
#define ARM_LPAE_PTE_SH_IS		(((arm_lpae_iopte)3) << 8)
#define ARM_LPAE_PTE_NS			(((arm_lpae_iopte)1) << 5)
#define ARM_LPAE_PTE_VALID		(((arm_lpae_iopte)1) << 0)

#define ARM_LPAE_PTE_ATTR_LO_MASK	(((arm_lpae_iopte)0x3ff) << 2)
/* Ignore the contiguous bit for block splitting */
#define ARM_LPAE_PTE_ATTR_HI_MASK	(((arm_lpae_iopte)6) << 52)
#define ARM_LPAE_PTE_ATTR_MASK		(ARM_LPAE_PTE_ATTR_LO_MASK |	\
					 ARM_LPAE_PTE_ATTR_HI_MASK)
/* Software bit for solving coherency races */
#define ARM_LPAE_PTE_SW_SYNC		(((arm_lpae_iopte)1) << 55)

/* Stage-1 PTE */
#define ARM_LPAE_PTE_AP_UNPRIV		(((arm_lpae_iopte)1) << 6)
#define ARM_LPAE_PTE_AP_RDONLY		(((arm_lpae_iopte)2) << 6)
#define ARM_LPAE_PTE_ATTRINDX_SHIFT	2
#define ARM_LPAE_PTE_nG			(((arm_lpae_iopte)1) << 11)

/* Stage-2 PTE */
#define ARM_LPAE_PTE_HAP_FAULT		(((arm_lpae_iopte)0) << 6)
#define ARM_LPAE_PTE_HAP_READ		(((arm_lpae_iopte)1) << 6)
#define ARM_LPAE_PTE_HAP_WRITE		(((arm_lpae_iopte)2) << 6)
#define ARM_LPAE_PTE_MEMATTR_OIWB	(((arm_lpae_iopte)0xf) << 2)
#define ARM_LPAE_PTE_MEMATTR_NC		(((arm_lpae_iopte)0x5) << 2)
#define ARM_LPAE_PTE_MEMATTR_DEV	(((arm_lpae_iopte)0x1) << 2)

/* Register bits */
#define ARM_32_LPAE_TCR_EAE		(1 << 31)
#define ARM_64_LPAE_S2_TCR_RES1		(1 << 31)

#define ARM_LPAE_TCR_EPD1		(1 << 23)

#define ARM_LPAE_TCR_TG0_4K		(0 << 14)
#define ARM_LPAE_TCR_TG0_64K		(1 << 14)
#define ARM_LPAE_TCR_TG0_16K		(2 << 14)

#define ARM_LPAE_TCR_SH0_SHIFT		12
#define ARM_LPAE_TCR_SH0_MASK		0x3
#define ARM_LPAE_TCR_SH_NS		0
#define ARM_LPAE_TCR_SH_OS		2
#define ARM_LPAE_TCR_SH_IS		3

#define ARM_LPAE_TCR_ORGN0_SHIFT	10
#define ARM_LPAE_TCR_IRGN0_SHIFT	8
#define ARM_LPAE_TCR_RGN_MASK		0x3
#define ARM_LPAE_TCR_RGN_NC		0
#define ARM_LPAE_TCR_RGN_WBWA		1
#define ARM_LPAE_TCR_RGN_WT		2
#define ARM_LPAE_TCR_RGN_WB		3

#define ARM_LPAE_TCR_SL0_SHIFT		6
#define ARM_LPAE_TCR_SL0_MASK		0x3

#define ARM_LPAE_TCR_T0SZ_SHIFT		0
#define ARM_LPAE_TCR_SZ_MASK		0xf

#define ARM_LPAE_TCR_PS_SHIFT		16
#define ARM_LPAE_TCR_PS_MASK		0x7

#define ARM_LPAE_TCR_IPS_SHIFT		32
#define ARM_LPAE_TCR_IPS_MASK		0x7

#define ARM_LPAE_TCR_PS_32_BIT		0x0ULL
#define ARM_LPAE_TCR_PS_36_BIT		0x1ULL
#define ARM_LPAE_TCR_PS_40_BIT		0x2ULL
#define ARM_LPAE_TCR_PS_42_BIT		0x3ULL
#define ARM_LPAE_TCR_PS_44_BIT		0x4ULL
#define ARM_LPAE_TCR_PS_48_BIT		0x5ULL
#define ARM_LPAE_TCR_PS_52_BIT		0x6ULL

#define ARM_LPAE_MAIR_ATTR_SHIFT(n)	((n) << 3)
#define ARM_LPAE_MAIR_ATTR_MASK		0xff
#define ARM_LPAE_MAIR_ATTR_DEVICE	0x04
#define ARM_LPAE_MAIR_ATTR_NC		0x44
#define ARM_LPAE_MAIR_ATTR_WBRWA	0xff
#define ARM_LPAE_MAIR_ATTR_IDX_NC	0
#define ARM_LPAE_MAIR_ATTR_IDX_CACHE	1
#define ARM_LPAE_MAIR_ATTR_IDX_DEV	2

#define __va(x)			((void *)phys_to_virt((phys_addr_t)(x)))
#define __pa(x)			virt_to_phys(x)
/* IOPTE accessors */
#define iopte_deref(pte,d) __va(iopte_to_paddr(pte, d))

#define iopte_type(pte,l)					\
	(((pte) >> ARM_LPAE_PTE_TYPE_SHIFT) & ARM_LPAE_PTE_TYPE_MASK)

#define iopte_prot(pte)	((pte) & ARM_LPAE_PTE_ATTR_MASK)

#define iopte_leaf(pte,l)					\
	(l == (ARM_LPAE_MAX_LEVELS - 1) ?			\
		(iopte_type(pte,l) == ARM_LPAE_PTE_TYPE_PAGE) :	\
		(iopte_type(pte,l) == ARM_LPAE_PTE_TYPE_BLOCK))

struct arm_lpae_io_pgtable {
	struct io_pgtable	iop;

	int			levels;
	size_t			pgd_size;
	unsigned long		pg_shift;
	unsigned long		bits_per_level;

	void			*pgd;
};

typedef u64 arm_lpae_iopte;

static arm_lpae_iopte paddr_to_iopte(phys_addr_t paddr,
				     struct arm_lpae_io_pgtable *data)
{
	arm_lpae_iopte pte = paddr;

	/* Of the bits which overlap, either 51:48 or 15:12 are always RES0 */
	return (pte | (pte >> (48 - 12))) & ARM_LPAE_PTE_ADDR_MASK;
}

static phys_addr_t iopte_to_paddr(arm_lpae_iopte pte,
				  struct arm_lpae_io_pgtable *data)
{
	u64 paddr = pte & ARM_LPAE_PTE_ADDR_MASK;

	if (data->pg_shift < 16)
		return paddr;

	/* Rotate the packed high-order bits back to the top */
	return (paddr | (paddr << (48 - 12))) & (ARM_LPAE_PTE_ADDR_MASK << 4);
}

static bool selftest_running = false;
char* smmu_page_buf=NULL;
//DEFINE_ALIGN_BUFFER(char, page_buf, PAGE_SIZE*PAGE_SIZE, PAGE_SIZE);

void *current_page=NULL;
void* alloc_pagesize(int size)
{
	if (current_page == NULL)
		current_page = smmu_page_buf;
	current_page = current_page + size*PAGE_SIZE;
	if ((char*)current_page - (char*)smmu_page_buf > PAGE_SIZE*8)
		dev_err(NULL,"page alloc failure\n");

	return current_page;
}
static void *__arm_lpae_alloc_pages(size_t size)
{
	int order = get_order(size);//how many pages needed???

	void *pages = alloc_pagesize(order+1);

	return pages;
}

static void __arm_lpae_free_pages(void *pages, size_t size,
				  struct io_pgtable_cfg *cfg)
{
	return;
}


static void __arm_lpae_set_pte(arm_lpae_iopte *ptep, arm_lpae_iopte pte,
			       struct io_pgtable_cfg *cfg)
{
	*ptep = pte;
}


static void __arm_lpae_init_pte(struct arm_lpae_io_pgtable *data,
				phys_addr_t paddr, arm_lpae_iopte prot,
				int lvl, arm_lpae_iopte *ptep)
{
	arm_lpae_iopte pte = prot;

	if (data->iop.cfg.quirks & IO_PGTABLE_QUIRK_ARM_NS)
		pte |= ARM_LPAE_PTE_NS;

	if (lvl == ARM_LPAE_MAX_LEVELS - 1)
		pte |= ARM_LPAE_PTE_TYPE_PAGE;
	else
		pte |= ARM_LPAE_PTE_TYPE_BLOCK;

	pte |= ARM_LPAE_PTE_AF | ARM_LPAE_PTE_SH_IS;

	pte |= paddr_to_iopte(paddr, data);

	__arm_lpae_set_pte(ptep, pte, &data->iop.cfg);
}

static int arm_lpae_init_pte(struct arm_lpae_io_pgtable *data,
			     unsigned long iova, phys_addr_t paddr,
			     arm_lpae_iopte prot, int lvl,
			     arm_lpae_iopte *ptep)
{
	arm_lpae_iopte pte = *ptep;

	if (iopte_leaf(pte, lvl)) {
		/* We require an unmap first */
		/*Is using same mapping item for all SMMUs, so
		ignore the warning*/
		//WARN_ON(!selftest_running);
		return -EEXIST;
	}

	__arm_lpae_init_pte(data, paddr, prot, lvl, ptep);
	return 0;
}

static arm_lpae_iopte arm_lpae_install_table(arm_lpae_iopte *table,
					     arm_lpae_iopte *ptep,
					     arm_lpae_iopte curr,
					     struct io_pgtable_cfg *cfg)
{
	arm_lpae_iopte old, new;

	new = ((arm_lpae_iopte)__pa(table)) | ARM_LPAE_PTE_TYPE_TABLE;
	if (cfg->quirks & IO_PGTABLE_QUIRK_ARM_NS)
		new |= ARM_LPAE_PTE_NSTABLE;

	/*
	 * Ensure the table itself is visible before its PTE can be.
	 * Whilst we could get away with cmpxchg64_release below, this
	 * doesn't have any ordering semantics when !CONFIG_SMP.
	 */
	dmb(sy);
	old = 0;
	//old = cmpxchg64_relaxed(ptep, curr, new);
	//old = atomic64_cmpxchg(ptep, curr, new);

	if (*ptep == curr) {//how to support atomic operaton
		old = *ptep;
		*ptep = new;
	}
	isb();
	dsb(sy);
	if ((cfg->quirks & IO_PGTABLE_QUIRK_NO_DMA) ||
	    (old & ARM_LPAE_PTE_SW_SYNC))
		return old;


	if (old == curr)
		WRITE_ONCE(*ptep, new | ARM_LPAE_PTE_SW_SYNC);

	return old;
}

static int __arm_lpae_map(struct arm_lpae_io_pgtable *data, unsigned long iova,
			  phys_addr_t paddr, size_t size, arm_lpae_iopte prot,
			  int lvl, arm_lpae_iopte *ptep)
{
	arm_lpae_iopte *cptep, pte;
	size_t block_size = ARM_LPAE_BLOCK_SIZE(lvl, data);
	size_t tblsz = ARM_LPAE_GRANULE(data);
	struct io_pgtable_cfg *cfg = &data->iop.cfg;

	/* Find our entry at the current level */
	ptep += ARM_LPAE_LVL_IDX(iova, lvl, data);
	//printf("block_size=0x%lx,size=0x%lx, cfg->pgsize_bitmap=0x%lx\n",
	//	(unsigned long)block_size,(unsigned long)size,(unsigned long)cfg->pgsize_bitmap);
	/* If we can install a leaf entry at this level, then do so */
	if (size == block_size && (size & cfg->pgsize_bitmap))
		return arm_lpae_init_pte(data, iova, paddr, prot, lvl, ptep);

	/* We can't allocate tables at the final level */
	if (WARN_ON(lvl >= ARM_LPAE_MAX_LEVELS - 1))
		return -EINVAL;

	/* Grab a pointer to the next level */
	pte = READ_ONCE(*ptep);
	if (!pte) {
		cptep = __arm_lpae_alloc_pages(tblsz);

		if (!cptep) {
			printf("failed to allocate page buffer\n");
			return -ENOMEM;
		}

		pte = arm_lpae_install_table(cptep, ptep, 0, cfg);
		if (pte)
			__arm_lpae_free_pages(cptep, tblsz, cfg);
	}

	if (pte && !iopte_leaf(pte, lvl)) {
		cptep = iopte_deref(pte, data);
	} else if (pte) {
		/* We require an unmap first */
		WARN_ON(!selftest_running);
		return -EEXIST;
	}

	/* Rinse, repeat */
	return __arm_lpae_map(data, iova, paddr, size, prot, lvl + 1, cptep);
}

static arm_lpae_iopte arm_lpae_prot_to_pte(struct arm_lpae_io_pgtable *data,
					   int prot)
{
	arm_lpae_iopte pte;

	if (data->iop.fmt == ARM_64_LPAE_S1 ||
	    data->iop.fmt == ARM_32_LPAE_S1) {
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
	} else {
		pte = ARM_LPAE_PTE_HAP_FAULT;
		if (prot & IOMMU_READ)
			pte |= ARM_LPAE_PTE_HAP_READ;
		if (prot & IOMMU_WRITE)
			pte |= ARM_LPAE_PTE_HAP_WRITE;
		if (prot & IOMMU_MMIO)
			pte |= ARM_LPAE_PTE_MEMATTR_DEV;
		else if (prot & IOMMU_CACHE)
			pte |= ARM_LPAE_PTE_MEMATTR_OIWB;
		else
			pte |= ARM_LPAE_PTE_MEMATTR_NC;
	}

	if (prot & IOMMU_NOEXEC)
		pte |= ARM_LPAE_PTE_XN;

	return pte;
}

static int arm_lpae_map(struct io_pgtable_ops *ops, unsigned long iova,
			phys_addr_t paddr, size_t size, int iommu_prot)
{
	struct arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	arm_lpae_iopte *ptep = data->pgd;
	int ret, lvl = ARM_LPAE_START_LVL(data);
	arm_lpae_iopte prot;

	/* If no access, then nothing to do */
	if (!(iommu_prot & (IOMMU_READ | IOMMU_WRITE)))
		return 0;

	if (WARN_ON(iova >= (1ULL << data->iop.cfg.ias) ||
		    paddr >= (1ULL << data->iop.cfg.oas)))
		return -ERANGE;

	prot = arm_lpae_prot_to_pte(data, iommu_prot);
	ret = __arm_lpae_map(data, iova, paddr, size, prot, lvl, ptep);
	/*
	 * Synchronise all PTE updates for the new mapping before there's
	 * a chance for anything to kick off a table walk for the new iova.
	 */
	dmb(sy);

	return ret;
}

static void arm_lpae_free_pgtable(struct io_pgtable *iop)
{
	return;
}

static phys_addr_t arm_lpae_iova_to_phys(struct io_pgtable_ops *ops,
					 unsigned long iova)
{
	struct arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	arm_lpae_iopte pte, *ptep = data->pgd;
	int lvl = ARM_LPAE_START_LVL(data);

	do {
		/* Valid IOPTE pointer? */
		if (!ptep)
			return 0;

		/* Grab the IOPTE we're interested in */
		ptep += ARM_LPAE_LVL_IDX(iova, lvl, data);
		pte = READ_ONCE(*ptep);

		/* Valid entry? */
		if (!pte)
			return 0;

		/* Leaf entry? */
		if (iopte_leaf(pte,lvl))
			goto found_translation;

		/* Take it to the next level */
		ptep = iopte_deref(pte, data);
	} while (++lvl < ARM_LPAE_MAX_LEVELS);

	/* Ran out of page tables to walk */
	return 0;

found_translation:
	iova &= (ARM_LPAE_BLOCK_SIZE(lvl, data) - 1);
	return iopte_to_paddr(pte, data) | iova;
}

static void arm_lpae_restrict_pgsizes(struct io_pgtable_cfg *cfg)
{
	unsigned long granule, page_sizes;
	unsigned int max_addr_bits = 48;

	/*
	 * We need to restrict the supported page sizes to match the
	 * translation regime for a particular granule. Aim to match
	 * the CPU page size if possible, otherwise prefer smaller sizes.
	 * While we're at it, restrict the block sizes to match the
	 * chosen granule.
	 */
	if (cfg->pgsize_bitmap & PAGE_SIZE)
		granule = PAGE_SIZE;
	else if (cfg->pgsize_bitmap & ~PAGE_MASK)
		granule = 1UL << fls64(cfg->pgsize_bitmap & ~PAGE_MASK);
	else if (cfg->pgsize_bitmap & PAGE_MASK)
		granule = 1UL << fls64(cfg->pgsize_bitmap & PAGE_MASK);
	else
		granule = 0;

	switch (granule) {
	case SZ_4K:
		page_sizes = (SZ_4K | SZ_2M | SZ_1G);
		break;
	case SZ_16K:
		page_sizes = (SZ_16K | SZ_32M);
		break;
	case SZ_64K:
		max_addr_bits = 52;
		page_sizes = (SZ_64K | SZ_512M);
		if (cfg->oas > 48)
			page_sizes |= 1ULL << 42; /* 4TB */
		break;
	default:
		page_sizes = 0;
	}

	cfg->pgsize_bitmap &= page_sizes;
	cfg->ias = min(cfg->ias, max_addr_bits);
	cfg->oas = min(cfg->oas, max_addr_bits);
}


struct arm_lpae_io_pgtable data_dev;
static struct arm_lpae_io_pgtable *
arm_lpae_alloc_pgtable(struct io_pgtable_cfg *cfg)
{
	unsigned long va_bits, pgd_bits;
	struct arm_lpae_io_pgtable *data;

	arm_lpae_restrict_pgsizes(cfg);

	if (!(cfg->pgsize_bitmap & (SZ_4K | SZ_16K | SZ_64K)))
		return NULL;

	if (cfg->ias > ARM_LPAE_MAX_ADDR_BITS)
		return NULL;

	if (cfg->oas > ARM_LPAE_MAX_ADDR_BITS)
		return NULL;


	data = &data_dev;//kmalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return NULL;

	data->pg_shift = ffs(cfg->pgsize_bitmap)-1;
	data->bits_per_level = data->pg_shift - __ilog2(sizeof(arm_lpae_iopte));

	va_bits = cfg->ias - data->pg_shift;
	data->levels = DIV_ROUND_UP(va_bits, data->bits_per_level);

	/* Calculate the actual size of our pgd (without concatenation) */
	pgd_bits = va_bits - (data->bits_per_level * (data->levels - 1));
	data->pgd_size = 1UL << (pgd_bits + __ilog2(sizeof(arm_lpae_iopte)));

	data->iop.ops = (struct io_pgtable_ops) {
		.map		= arm_lpae_map,
		.unmap		= NULL,
		.iova_to_phys	= arm_lpae_iova_to_phys,
	};

	return data;
}

static struct io_pgtable *
arm_64_lpae_alloc_pgtable_s1(struct io_pgtable_cfg *cfg, void *cookie)
{
	u64 reg;
	struct arm_lpae_io_pgtable *data;

	if (cfg->quirks & ~(IO_PGTABLE_QUIRK_ARM_NS | IO_PGTABLE_QUIRK_NO_DMA))
		return NULL;

	data = arm_lpae_alloc_pgtable(cfg);
	if (!data)
		return NULL;

	/* TCR */
	reg = (ARM_LPAE_TCR_SH_IS << ARM_LPAE_TCR_SH0_SHIFT) |
	      (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_IRGN0_SHIFT) |
	      (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_ORGN0_SHIFT);

	switch (ARM_LPAE_GRANULE(data)) {
	case SZ_4K:
		reg |= ARM_LPAE_TCR_TG0_4K;
		break;
	case SZ_16K:
		reg |= ARM_LPAE_TCR_TG0_16K;
		break;
	case SZ_64K:
		reg |= ARM_LPAE_TCR_TG0_64K;
		break;
	}

	switch (cfg->oas) {
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

	reg |= (64ULL - cfg->ias) << ARM_LPAE_TCR_T0SZ_SHIFT;

	/* Disable speculative walks through TTBR1 */
	reg |= ARM_LPAE_TCR_EPD1;
	cfg->arm_lpae_s1_cfg.tcr = reg;

	/* MAIRs */
	reg = (ARM_LPAE_MAIR_ATTR_NC
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_NC)) |
	      (ARM_LPAE_MAIR_ATTR_WBRWA
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_CACHE)) |
	      (ARM_LPAE_MAIR_ATTR_DEVICE
	       << ARM_LPAE_MAIR_ATTR_SHIFT(ARM_LPAE_MAIR_ATTR_IDX_DEV));

	cfg->arm_lpae_s1_cfg.mair[0] = reg;
	cfg->arm_lpae_s1_cfg.mair[1] = 0;

	/* Looking good; allocate a pgd */
	data->pgd = __arm_lpae_alloc_pages(data->pgd_size);
	if (!data->pgd)
		goto out_free_data;

	/* Ensure the empty pgd is visible before any actual TTBR write */
	dmb(sy);

	/* TTBRs */
	cfg->arm_lpae_s1_cfg.ttbr[0] = (u64)virt_to_phys(data->pgd);
	cfg->arm_lpae_s1_cfg.ttbr[1] = 0;
	return &data->iop;

out_free_data:
	//kfree(data);
	return NULL;
}

static struct io_pgtable *
arm_64_lpae_alloc_pgtable_s2(struct io_pgtable_cfg *cfg, void *cookie)
{
	u64 reg, sl;
	struct arm_lpae_io_pgtable *data;

	/* The NS quirk doesn't apply at stage 2 */
	if (cfg->quirks & ~IO_PGTABLE_QUIRK_NO_DMA)
		return NULL;

	data = arm_lpae_alloc_pgtable(cfg);
	if (!data)
		return NULL;

	/*
	 * Concatenate PGDs at level 1 if possible in order to reduce
	 * the depth of the stage-2 walk.
	 */
	if (data->levels == ARM_LPAE_MAX_LEVELS) {
		unsigned long pgd_pages;

		pgd_pages = data->pgd_size >> __ilog2(sizeof(arm_lpae_iopte));
		if (pgd_pages <= ARM_LPAE_S2_MAX_CONCAT_PAGES) {
			data->pgd_size = pgd_pages << data->pg_shift;
			data->levels--;
		}
	}

	/* VTCR */
	reg = ARM_64_LPAE_S2_TCR_RES1 |
	     (ARM_LPAE_TCR_SH_IS << ARM_LPAE_TCR_SH0_SHIFT) |
	     (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_IRGN0_SHIFT) |
	     (ARM_LPAE_TCR_RGN_WBWA << ARM_LPAE_TCR_ORGN0_SHIFT);

	sl = ARM_LPAE_START_LVL(data);

	switch (ARM_LPAE_GRANULE(data)) {
	case SZ_4K:
		reg |= ARM_LPAE_TCR_TG0_4K;
		sl++; /* SL0 format is different for 4K granule size */
		break;
	case SZ_16K:
		reg |= ARM_LPAE_TCR_TG0_16K;
		break;
	case SZ_64K:
		reg |= ARM_LPAE_TCR_TG0_64K;
		break;
	}

	switch (cfg->oas) {
	case 32:
		reg |= (ARM_LPAE_TCR_PS_32_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 36:
		reg |= (ARM_LPAE_TCR_PS_36_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 40:
		reg |= (ARM_LPAE_TCR_PS_40_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 42:
		reg |= (ARM_LPAE_TCR_PS_42_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 44:
		reg |= (ARM_LPAE_TCR_PS_44_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 48:
		reg |= (ARM_LPAE_TCR_PS_48_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	case 52:
		reg |= (ARM_LPAE_TCR_PS_52_BIT << ARM_LPAE_TCR_PS_SHIFT);
		break;
	default:
		goto out_free_data;
	}

	reg |= (64ULL - cfg->ias) << ARM_LPAE_TCR_T0SZ_SHIFT;
	reg |= (~sl & ARM_LPAE_TCR_SL0_MASK) << ARM_LPAE_TCR_SL0_SHIFT;
	cfg->arm_lpae_s2_cfg.vtcr = reg;

	/* Allocate pgd pages */
	data->pgd = __arm_lpae_alloc_pages(data->pgd_size);
	if (!data->pgd)
		goto out_free_data;

	/* Ensure the empty pgd is visible before any actual TTBR write */
	dmb(sy);

	/* VTTBR */
	cfg->arm_lpae_s2_cfg.vttbr = (u64)virt_to_phys(data->pgd);
	return &data->iop;

out_free_data:
	//kfree(data);
	return NULL;
}

struct io_pgtable_init_fns io_pgtable_arm_64_lpae_s1_init_fns = {
	.alloc	= arm_64_lpae_alloc_pgtable_s1,
	.free	= arm_lpae_free_pgtable,
};

struct io_pgtable_init_fns io_pgtable_arm_64_lpae_s2_init_fns = {
	.alloc	= arm_64_lpae_alloc_pgtable_s2,
	.free	= arm_lpae_free_pgtable,
};
