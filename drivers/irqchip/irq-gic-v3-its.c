/*
 * Copyright (c) 2020, siengine All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <stdlib.h>
#include <asm/io.h>
#include <target/console.h>
#include <target/bitops.h>
#include <target/cmdline.h>
#include <target/utils.h>
#include <errno.h>
#include <target/spinlock.h>
#include <target/delay.h>
#include <target/heap.h>
#include <target/list.h>

#include "target/gic.h"
#include "target/gicv3.h"
/*
 * The ITS command block, which is what the ITS actually parses.
 */
struct its_cmd_block {
	u64	raw_cmd[4];
};
#define ITS_CMD_QUEUE_SZ		SZ_64K
#define ITS_CMD_QUEUE_NR_ENTRIES	(ITS_CMD_QUEUE_SZ / sizeof(struct its_cmd_block))
/*
 * Collection structure - just an ID, and a redistributor address to
 * ping. We use one per CPU as a bag of interrupts assigned to this
 * CPU.
 */
struct its_collection {
	u64			target_address;
	u16			col_id;
};

/*
 * The ITS_BASER structure - contains memory information, cached
 * value of BASER register configuration and ITS page size.
 */
struct its_baser {
	void		*base;
	u64		val;
	u32		order;
	u32		psz;
};

#define GITS_BASER_NR_REGS 8
struct its_local {
	void __iomem		*its_baseaddr;
	void __iomem		*r_baseaddr;
	struct list_head	its_list_entry;
	struct list_head	devid_list_head;
	struct its_cmd_block	*cmd_base;
	struct its_cmd_block	*cmd_write;
	struct its_baser	tables[GITS_BASER_NR_REGS];
	struct its_collection	*collections;
	void		*prop_page;
};

/* holding specific deviceID table */
struct its_deviceID {
	void			*itt;
	u32			nr_ites;
	u32			device_id;
	struct list_head	devid_list_entry;
};

static u32 lpi_id_bits;

/*
 * We allocate memory for PROPBASE to cover 2 ^ lpi_id_bits LPIs to
 * deal with (one configuration byte per interrupt). PENDBASE has to
 * be 64kB aligned (one bit per LPI, plus 8192 bits for SPI/PPI/SGI).
 */
#define LPI_NRBITS		lpi_id_bits
#define LPI_PROPBASE_SZ		ALIGN(BIT(LPI_NRBITS), SZ_64K)
#define LPI_PENDBASE_SZ		ALIGN(BIT(LPI_NRBITS) / 8, SZ_64K)

#ifndef IOREMAP
#define IOREMAP
#endif

#define readl_relaxed(c)	({ u32 __r = le32_to_cpu((__force __le32) \
						__raw_readl(c)); __r; })

#define writel_relaxed(v, c)	((void)__raw_writel((__force u32) \
						    cpu_to_le32(v), (c)))

static int its_probe_one(struct its_local* its_dev);
static void its_free_tables(struct its_local* its_dev);
static void its_free_itsdev(struct its_local* its_dev);

LIST_HEAD(gic_its_devs);

/* in case sram heap memory is not enough for ITS */
static inline void *its_mem_alloc(size_t size)
{
	return heap_aligned_alloc(16, size);
}

static inline void *its_mem_alloc_aligned(size_t align,
		size_t size)
{
	return heap_aligned_alloc(align, size);
}

static inline void its_mem_free(void *p)
{
	return;
}

static inline void *its_alloc_pagealigned_size(size_t size)
{
	return heap_aligned_alloc(PAGE_SIZE, size);
}

static inline void *its_alloc_pages(int order)
{
	return heap_aligned_alloc(PAGE_SIZE, PAGE_SIZE * (order + 1));
}

/* 				ITS,LPI tables manipulate start
 * The following part is for LPI, ITS table configuration
 * Mainly focus on manipulating different table entries
 * Called by client who wants to enable LPI interrupt, for example
 * MSIx
 * */
static bool its_alloc_device_table(struct its_local *its_dev,
						u32 dev_id)
{
	return true;
}

/* create interrupt translate table and map to devID */
struct its_deviceID* its_create_deviceID(struct its_local *its_dev,
				u32 dev_id, int nvecs)
{
	struct its_deviceID *itt_for_devid;
	struct its_deviceID *tmp_its;

	itt_for_devid = NULL;
	list_for_each_entry(struct its_deviceID, tmp_its,
		&its_dev->devid_list_head, devid_list_entry) {
		if (tmp_its->device_id == dev_id) {
			itt_for_devid = tmp_its;
			break;
		}
	}

	if (itt_for_devid != NULL) {
		printf("warn: device id %d has been created\n", dev_id);
		return itt_for_devid;
	}

	itt_for_devid = its_mem_alloc(sizeof(*itt_for_devid));

	if (itt_for_devid == NULL) {
		printf("%s: allocate devID failed\n", __func__);
		return NULL;
	}
	if (!its_alloc_device_table(its_dev, dev_id))
		return NULL;

	list_add_tail(&itt_for_devid->devid_list_entry,
							&its_dev->devid_list_head);

	return itt_for_devid;
}

/* mapping eventid to PINTID */
u32 its_request_LPIID(struct its_deviceID *its_dev, u32 event_id)
{
	return 0;
}

/* write GITS_TRANSLATER register to signal an interrupt */
void its_lpiID_trigger(struct its_local *its_dev,
				u32 dev_id, u32 event_id)
{
	return;
}

/* 				ITS,LPI tables manipulate end
 * The following part is for LPI, ITS table configuration
 * Mainly focus on manipulating different table entries
 * Called by client who wants to enable LPI interrupt, for example
 * MSIx
 * */


/* 				ITS,LPI init start
 * The following part is for LPI, ITS initialization
 * Mainly focus on different tables buffer allocation
 * LPI: PROP table(enable or disable LPI vector), pending
 * table(Interrupt comes)
 * ITS: device table(include deviceIDs), ITT table(translate eventID
 * to PINTID, and ICID), IC table(route to which CPU/rdist)
 * */
/* LPI its init parts:
 * 1. LPI config and pending table
 * 2. ITS collection table
 * */
static int redist_disable_lpis(void)
{
	void __iomem *rbase = gicv3_get_rdist_base();

	return 0;
}

static void *its_allocate_pending_table(void)
{
	void *pend_page;
	/*
	 * The pending pages have to be at least 64kB aligned,
	 * hence the 'max(LPI_PENDBASE_SZ, SZ_64K)' below.
	 * Page size basic allocation
	 */
	pend_page = its_alloc_pages(
				get_order(max_t(u32, LPI_PENDBASE_SZ, SZ_64K)));
	if (!pend_page)
		return NULL;

	/* Make sure the GIC will observe the zero-ed page */
	flush_dcache_area(pend_page, LPI_PENDBASE_SZ);

	return pend_page;
}

/* propbaser and pending table config */
static void its_cpu_init_lpis(void)
{
	/* must be page size aligned for pending table */
	void *pend_page;
	phys_addr_t paddr;

	pend_page = its_allocate_pending_table();
	paddr = virt_to_phys(pend_page);

	/* set PROPBASE register */
	/* set PENDBASE register */
	/* Enable LPIs */

	/* Make sure the GIC has seen the above */
	dsb(sy);
	return;
}

/* collection table init, where to route */
static void its_cpu_init_collections(
				struct its_local* its_dev)
{
	int cpu = smp_processor_id();
	u64 target;

	target = 0;//stub value, should be rdist phy value
	/*
	 * We now have to bind each collection to its target
	 * redistributor.
	 */
	/* Perform collection mapping */
	its_dev->collections[cpu].target_address = target;
	its_dev->collections[cpu].col_id = cpu;

	return;
}

static int its_alloc_lpi_tables(struct its_local* its_dev)
{
	phys_addr_t paddr;
	//sub func, ready gicd_typer to know how many lpis
	//lpi_id_bits = min_t(u32, ?, 16);
	lpi_id_bits = 8;

	its_dev->prop_page = NULL;//stub func, allocate buffer
	if (!its_dev->prop_page) {
		printf("Failed to allocate PROPBASE\n");
		return -ENOMEM;
	}

	paddr = virt_to_phys(its_dev->prop_page);
	//printf("GIC: using LPI property table @%pa\n", &paddr);

	return 0;
}
static void its_free_lpi_tables(struct its_local* its_dev)
{
	its_mem_free(its_dev->prop_page);
}

int itslpi_cpu_init(struct its_local* its_dev)
{
	int ret;

	ret = its_probe_one(its_dev);
	if (ret) {
		printf("failed to probe the its device\n");
		return ret;
	}

	ret = its_alloc_lpi_tables(its_dev);
	if (!ret) {

		/* disable LPI before any config */
		ret = redist_disable_lpis();
		if (ret) {
			its_free_itsdev(its_dev);
			its_free_lpi_tables(its_dev);
			return ret;
		}


		/* LPI tables for prop and pending */
		its_cpu_init_lpis();

		its_cpu_init_collections(its_dev);
	} else {
		its_free_itsdev(its_dev);
		return ret;
	}

	return 0;
}

static int its_force_quiescent(void __iomem *base)
{
	u32 count = 1000000;	/* 1s */
	u32 val;

	val = readl_relaxed(base + GITS_CTLR);
	/*
	 * GIC architecture specification requires the ITS to be both
	 * disabled and quiescent for writes to GITS_BASER<n> or
	 * GITS_CBASER to not have UNPREDICTABLE results.
	 */
	if ((val & GITS_CTLR_QUIESCENT) && !(val & GITS_CTLR_ENABLE))
		return 0;

	/* Disable the generation of all interrupts to this ITS */
	val &= ~(GITS_CTLR_ENABLE | GITS_CTLR_ImDe);
	writel_relaxed(val, base + GITS_CTLR);

	/* Poll GITS_CTLR and wait until ITS becomes quiescent */
	while (1) {
		val = readl_relaxed(base + GITS_CTLR);
		if (val & GITS_CTLR_QUIESCENT)
			return 0;

		count--;
		if (!count)
			return -EBUSY;
		udelay(1);
	}
}

static void its_free_tables(struct its_local* its_dev)
{
	int i;

	for (i = 0; i < GITS_BASER_NR_REGS; i++) {
		if (its_dev->tables[i].base) {
			its_mem_free(its_dev->tables[i].base);
			its_dev->tables[i].base = NULL;
		}
	}
}
static void its_free_itsdev(struct its_local* its_dev)
{
	its_mem_free(its_dev->collections);
	its_free_tables(its_dev);
}

/* read gits_baser<n> register, prepare for device table */
static int its_alloc_tables(struct its_local* its_dev)
{
	//stub func
	//allocate buffer for struct its_baser	tables[GITS_BASER_NR_REGS];

	return 0;
}

/* prepare for the interrupt collection table for routing*/
static int its_alloc_collections(struct its_local* its_dev)
{
	int i;
	int nr_cpu_ids = NR_CPUS;

	its_dev->collections =
				its_mem_alloc(nr_cpu_ids * sizeof(*its_dev->collections));
	if (!its_dev->collections)
		return -ENOMEM;

	for (i = 0; i < nr_cpu_ids; i++)
		its_dev->collections[i].target_address = ~0ULL;

	return 0;
}

/* its related table creating
 * 1. device table
 * 2. interrupt translation table
 * 3. collection table
 * 4. command memory
 * */
static int its_probe_one(struct its_local* its_dev)
{
	void __iomem *its_base;
	u32 val, ctlr;
	u64 baser, tmp, typer;
	int err;

	its_base = its_dev->its_baseaddr;

	val = readl_relaxed(its_base + GITS_PIDR2) & GIC_PIDR2_ARCH_MASK;
	if (val != 0x30 && val != 0x40) {
		printf("ITS@%pa: No ITS detected, giving up\n", its_base);
		err = -ENODEV;
		goto out_unmap;
	}

	//make sure its/lpi is quiet before configuring it
	err = its_force_quiescent(its_base);
	if (err) {
		printf("ITS@%pa: Failed to quiesce, giving up\n", its_base);
		goto out_unmap;
	}

	its_dev->cmd_base = (void *)its_alloc_pages(get_order(ITS_CMD_QUEUE_SZ));
	if (!its_dev->cmd_base) {
		err = -ENOMEM;
		goto out_unmap;
	}
	its_dev->cmd_write = its_dev->cmd_base;

	//its_enable_quirks(its);//stub func
	err = its_alloc_tables(its_dev);
	if (err)
		goto out_free_cmd;

	err = its_alloc_collections(its_dev);
	if (err)
		goto out_free_tables;


out_free_tables:
	its_free_tables(its_dev);
out_free_cmd:
	its_mem_free(its_dev->cmd_base);
out_unmap:
	printf("ITS@%pa: failed probing (%d)\n", its_base, err);
	return err;
}

/* 				ITS,LPI init end
 * The above part is for LPI, ITS initialization
 * Mainly focus on different tables buffer allocation
 * LPI: PROP table(enable or disable LPI vector), pending
 * table(Interrupt comes)
 * ITS: device table(include deviceIDs), ITT table(translate eventID
 * to PINTID, and ICID), IC table(route to which CPU/rdist)
 * */

static struct its_local* gic_its_basic_init(
		uintptr_t its_base)
{
	struct its_local* its_dev;
	int ret;

	if (its_base == 0) {
		printf("%s: wrong parameter\n", __func__);
		return NULL;
	}

	its_dev = its_mem_alloc(sizeof(*its_dev));

	if (NULL == its_dev) {
		printf("failed to allocate its dev structure\n");
		return NULL;
	}

	/* no io remap, suppose physical = virtual*/
	its_dev->its_baseaddr = (void*)IOREMAP(its_base);
	its_dev->r_baseaddr   = gicv3_get_rdist_base();
	if (NULL == its_dev->r_baseaddr) {
		printf("%s: failed to ger rbase address\n", __func__);
		its_mem_free(its_dev);
		return NULL;
	}

	INIT_LIST_HEAD(&its_dev->devid_list_head);
	/* GICD_TYPER can be used to check if GIC HW really support LPI */
	ret = itslpi_cpu_init(its_dev);
	if (ret) {
		printf("failed to init its device\n");
		its_mem_free(its_dev);
		return NULL;
	}

	list_add_tail(&its_dev->its_list_entry, &gic_its_devs);

	return its_dev;
}

static int do_gic_its_test(int argc, char *argv[])
{
	uint64_t its_base = 0;
	u32 devid = 0, eventid;
	bool test;

	test = false;
	if (!strcmp(argv[1],"init")) {
		if (!strcmp(argv[2],"default"))
			its_base = 0x0;
		else
			its_base = strtoull(argv[2], 0, 0);

		if (argc != 3)
			return -EUSAGE;
		printf("Init gic its addr 0x%08llx\n", its_base);
	} else if (!strcmp(argv[1],"test")) {
		if (argc != 5)
			return -EUSAGE;

		if (!strcmp(argv[2],"default"))
			its_base = 0x0;
		else
			its_base = strtoull(argv[2], 0, 0);

		printf("test gic its addr 0x%08llx\n", its_base);
		devid 	= strtoull(argv[3], 0, 0);
		eventid = strtoull(argv[4], 0, 0);
		test = true;
	}

	{
		struct its_local* its_dev, *tmp_its;

		its_dev = NULL;
		list_for_each_entry(struct its_local, tmp_its,
			&gic_its_devs, its_list_entry) {
			if ((uintptr_t)tmp_its->its_baseaddr == its_base) {
				its_dev = tmp_its;
				break;
			}
		}

		if (test && its_dev) {
			/* start testing */
			struct its_deviceID* its_devid;
			u32	pintID;

			pintID = 0;
			its_devid = its_create_deviceID(its_dev, devid, 16);
			if (its_devid)
				pintID = its_request_LPIID(its_devid, eventid);

			if (pintID)
				irq_register_vector(pintID, NULL, NULL);

			its_lpiID_trigger(its_dev, devid, eventid);
			return 1;
		}

		if (its_dev == NULL)
			gic_its_basic_init(its_base);
	}

	return 1;
}

MK_CMD(gic_its, do_gic_its_test, "its basic test",
	"its init <its_addr>\n"
	"    - Init gic its device\n"
	"its test <its_addr> <devID> <eventID>\n"
	"    - test ITS_LPI interrupt\n"
);