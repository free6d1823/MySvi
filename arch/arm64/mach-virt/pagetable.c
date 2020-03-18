#include <target/memory.h>
#include <asm/fastmmu.h>

/*
 * Sample table for virt, for far, Table and Block descriptors are used.
 *
 * L0(Table) [0TB, 256TB)
 *    -> L1(Table) [0GB, 512GB)
 *       ->L2_0(Table) [0GB, 1GB)
 *          (Block 0x08000000)  MK_DEV_2M_SECURE  gic
 *          (Block 0x09000000)         MK_DEV_2M  uart
 *          (Block 0x10000000  2M X 8) MK_DEV_2M  pci mem
 *       ->L2_1(Table) [1GB, 2GB)
            (Block SVI_TEXT_BASE 0x40000000)      RWE memory, code
            (Block SVI_TEXT_BASE + 2M  2M X 64)   RW memory
 *       ->L2_2(Table) [2GB, 3GB)
 *       ->L2_3(Table) [3GB, 4GB)
 *       ......
 *       ->L2_PCI_CONFIG_SPACE(Table) [256GB, 257GB)
 *          (Block 0x4010000000ul)  pci config space
 */

/* 4KB:  L0(512G), L1(1G), L2(2M)  9+9+9+9+12=48
 * 16KB: L0(-),    L1(-),  L2(32M) 1+11+11+11+14=48
 * 64KB: L0(X),    L1(4T),  L2(512M) 0+6+13+13+16=48
 */
enum {
	L0,
	L1,
	L2_0,
	L2_1,
	L2_2,
	L2_3,

	L2_PCI_CONFIG_SPACE,

	PT_MAX,
};


pt_section pte pagetable[PT_MAX][MAX_PTE_ENTRIES] = {

	MK_TBL(0, L0, L1, 0x0ul, 0),

	MK_TBL(1, L1, L2_0, GB(0), 0),
	MK_TBL(1, L1, L2_1, GB(1), 0),
	MK_TBL(1, L1, L2_2, GB(2), 0),
	MK_TBL(1, L1, L2_3, GB(3), 0),

	/* for gic */
	MK_DEV_2M_SECURE(L2_0, 0x08000000),

	/* for uart */
	MK_DEV_2M(L2_0, 0x09000000),

	MK_MEMX_2M(L2_1, SVI_TEXT_BASE),
	MK_MEM_2M_64X(L2_1, SVI_TEXT_BASE + MB(2)),

	/* for pci */
	MK_TBL(1, L1, L2_PCI_CONFIG_SPACE, 0x4000000000ul, 0),
	MK_DEV_2M(L2_PCI_CONFIG_SPACE, 0x4010000000ul),
	MK_MEM_2M_8X(L2_0, 0x10000000),
};



