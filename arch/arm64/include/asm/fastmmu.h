#ifndef __FASTMMU_H__
#define __FASTMMU_H__

#include <target/regdef.h>

/* page table entry */
typedef unsigned long pte;

enum {
	DEVICE_nGnRnE,
	DEVICE_nGnRE,
	DEVICE_GRE,
	OUTER_NC_INNER_NC,
	OUTER_WT_INNER_WT,
	OUTER_WB_INNER_WB,
	OUTER_WB_INNER_NC,
	OUTER_NC_INNER_WB,
};

#define MAIR(attr, mt) (UL(attr) << ((mt) << 3))

#define DEFAULT_MAIR ( \
	MAIR(0x4f, OUTER_NC_INNER_WB)  | \
	MAIR(0xf4, OUTER_WB_INNER_NC) | \
	MAIR(0xff, OUTER_WB_INNER_WB) | \
	MAIR(0xbb, OUTER_WT_INNER_WT) | \
	MAIR(0x44, OUTER_NC_INNER_NC) | \
	MAIR(0x0c, DEVICE_GRE) | \
	MAIR(0x04, DEVICE_nGnRE) | \
	MAIR(0x00, DEVICE_nGnRnE))

/* PAGE_SHIFT determines the page size */
#undef  PAGE_SIZE
#define PAGE_SHIFT		12
#define PAGE_SIZE		(1 << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE - 1))

#define PT_SHIFT        (PAGE_SHIFT - 3)
#define MAX_PTE_ENTRIES (PAGE_SIZE / sizeof(pte))

/*
 * Hardware page table definitions.
 *
 */
#define PTE_TYPE_MASK		(3 << 0)
#define PTE_TYPE_FAULT		(0 << 0)
#define PTE_TYPE_TABLE		(3 << 0)
#define PTE_TYPE_PAGE		(3 << 0)
#define PTE_TYPE_BLOCK		(1 << 0)
#define PTE_TYPE_VALID		(1 << 0)

/*
 * Next-level attributes in stage 1 VMSAv8-64 Table descriptors
 *
 */
#define PTE_PXNTable	BIT_UL(59)
#define PTE_XNTable		BIT_UL(60)
#define PTE_APTable		(UL(0) << 61)
#define PTE_NSTable		BIT_UL(63)

/*
 * Attribute fields in stage 1 VMSAv8-64 Block and Page descriptors
 */
#define PTE_MT(x)	((x) << 2)
#define PTE_NS		(1 << 5)
#define PTE_AP_RW		(0 << 6)
#define PTE_AP_RW_EL0	(1 << 6)
#define PTE_AP_RO		(2 << 6)
#define PTE_AP_RO_EL0	(3 << 6)
#define PTE_SH_NONE		(0 << 8)
#define PTE_SH_OUTER	(2 << 8)
#define PTE_SH_INNER	(3 << 8)
#define PTE_AF		(1 << 10)
#define PTE_nG		(1 << 11)
#define PTE_PXN		BIT_UL(53)
#define PTE_UXN		BIT_UL(54)

/* Translation Control Register */
#define TCR_T0SZ(x)     ((64 - (x)) << 0)
#define TCR_IRGN0_NC    (0 << 8)
#define TCR_IRGN0_WBWA  (1 << 8)
#define TCR_IRGN0_WT    (2 << 8)
#define TCR_IRGN0_WBNWA (3 << 8)

#define TCR_ORGN0_NC    (0 << 10)
#define TCR_ORGN0_WBWA  (1 << 10)
#define TCR_ORGN0_WT    (2 << 10)
#define TCR_ORGN0_WBNWA (3 << 10)

#define TCR_SH0_NONE    (0 << 12)
#define TCR_SH0_OUTER   (2 << 12)
#define TCR_SH0_INNER   (3 << 12)

#define TCR_TG0_4KB     (0 << 14)
#define TCR_TG0_64KB    (1 << 14)
#define TCR_TG0_16KB    (2 << 14)

#define TCR_PS_32BITS   (0 << 16)
#define TCR_PS_36BITS   (1 << 16)
#define TCR_PS_40BITS   (2 << 16)
#define TCR_PS_42BITS   (3 << 16)
#define TCR_PS_44BITS   (4 << 16)
#define TCR_PS_48BITS   (5 << 16)

#define TCR_TBI         (1 << 20)
#define TCR_HA          (1 << 21)
#define TCR_HD          (1 << 22)
#define TCR_HPD         (1 << 24)

#define TCR_EL1_RSVD	(1 << 31)
#define TCR_EL2_RSVD	(1 << 31 | 1 << 23)
#define TCR_EL3_RSVD	(1 << 31 | 1 << 23)

#define TB(x) (UL(x) << 40)
#define GB(x) (UL(x) << 30)
#define MB(x) (UL(x) << 20)
#define KB(x) (UL(x) << 10)

#define PT_BASE (SVI_TEXT_BASE + PAGE_SIZE)
#define PT_ADDR(pt) (PT_BASE + (1 << PAGE_SHIFT) * pt)

#define PTE_IDX(lvl, va) (((pte)(va) >> (PAGE_SHIFT + PT_SHIFT * (3 - lvl))) & \
							((1 << PT_SHIFT) - 1))

/* VMSAv8-64 translation table level 0, level 1, and level 2 descriptor */
/* Table */
#define MK_TBL(lvl, pt, next_pt, va, attr) \
	[pt][PTE_IDX(lvl, va)] = (PT_ADDR(next_pt) | attr | PTE_TYPE_TABLE)

/* Block */
#define MK_BLK(lvl, pt, va, pa, attr) \
	[pt][PTE_IDX(lvl, va)] = ((pa) | attr | PTE_TYPE_BLOCK)

/* ARMv8 translation table level 3 descriptor */
#define MK_PAGE(pt, va, pa, attr) \
	[pt][PTE_IDX(3, va)] = ((pa) | attr | PTE_TYPE_PAGE)

/* make device memory */
#define MK_DEV(lvl, pt, addr, attr) \
	MK_BLK(lvl, pt, addr, addr, attr | PTE_UXN | PTE_PXN | PTE_nG | PTE_AF | \
							PTE_SH_NONE | PTE_AP_RW_EL0 | PTE_MT(DEVICE_nGnRnE))

/* make normal memory */
#define MK_MEM(lvl, pt, addr) \
	MK_BLK(lvl, pt, addr, addr, PTE_UXN | PTE_PXN | PTE_nG | PTE_AF | PTE_SH_INNER | \
							PTE_AP_RW_EL0 | PTE_NS | PTE_MT(OUTER_WB_INNER_WB))

/* make normal memory w/ executable attribute */
#define MK_MEMX(lvl, pt, addr) \
	MK_BLK(lvl, pt, addr, addr, PTE_nG | PTE_AF | PTE_SH_INNER | \
							PTE_AP_RW_EL0 | PTE_NS | PTE_MT(OUTER_WB_INNER_WB))


#define MK_DEV_2M(pt, addr) MK_DEV(2, pt, addr, PTE_NS)
#define MK_DEV_2M_SECURE(pt, addr) MK_DEV(2, pt, addr, 0)

#define MK_MEM_2M(pt, addr) MK_MEM(2, pt, addr)
#define MK_MEMX_2M(pt, addr) MK_MEMX(2, pt, addr)

#define MK_MEM_2M_8X(pt, addr) \
	MK_MEM_2M(pt, addr), \
	MK_MEM_2M(pt, addr + MB(2)), \
	MK_MEM_2M(pt, addr + MB(4)), \
	MK_MEM_2M(pt, addr + MB(6)), \
	MK_MEM_2M(pt, addr + MB(8)), \
	MK_MEM_2M(pt, addr + MB(10)), \
	MK_MEM_2M(pt, addr + MB(12)), \
	MK_MEM_2M(pt, addr + MB(14))

#define MK_MEM_2M_64X(pt, addr) \
	MK_MEM_2M_8X(pt, addr), \
	MK_MEM_2M_8X(pt, addr + MB(0x10)), \
	MK_MEM_2M_8X(pt, addr + MB(0x20)), \
	MK_MEM_2M_8X(pt, addr + MB(0x30)), \
	MK_MEM_2M_8X(pt, addr + MB(0x40)), \
	MK_MEM_2M_8X(pt, addr + MB(0x50)), \
	MK_MEM_2M_8X(pt, addr + MB(0x60)), \
	MK_MEM_2M_8X(pt, addr + MB(0x70))

#define pt_section __attribute__((section(".pagetable")))
extern pt_section pte pagetable[][MAX_PTE_ENTRIES];

#endif /* __FASTMMU_H__ */
