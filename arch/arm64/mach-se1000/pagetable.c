#include <target/memory.h>
#include <asm/fastmmu.h>

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

	L3_SVI,

	PT_MAX,
};

pt_section pte pagetable[PT_MAX][MAX_PTE_ENTRIES] = {

	MK_TBL(0, L0, L1, 0x0ul, 0),

	MK_TBL(1, L1, L2_0, GB(0), 0),
	MK_TBL(1, L1, L2_1, GB(1), 0),
	MK_TBL(1, L1, L2_2, GB(2), 0),
	MK_TBL(1, L1, L2_3, GB(3), 0),

	/* L2_0: 0x00000000 ~ 0x40000000 */

	/* for SVI_TEXT_BASE */
	MK_TBL(2, L2_0, L3_SVI, PAGE(0), 0),
	MK_PAGE_MEMX_32X(L3_SVI, SVI_TEXT_BASE),
	MK_PAGE_MEMX_32X(L3_SVI, SVI_TEXT_BASE + PAGE(0x20)),
	MK_PAGE_MEMX_32X(L3_SVI, SVI_TEXT_BASE + PAGE(0x40)),
	MK_PAGE_MEMX_8X(L3_SVI, SVI_TEXT_BASE + PAGE(0x60)),
	MK_PAGE_MEMX_8X(L3_SVI, SVI_TEXT_BASE + PAGE(0x68)),

	MK_DEV_2M(L2_0, SMMU_V3_BASE),

	/* SAF_SS */
	MK_DEV_2M_64X(L2_0, 0x30000000),
	MK_DEV_2M_64X(L2_0, 0x30000000 + MB(0x80)),

	/* L2_1: 0x40000000 ~ 0x80000000 */
	/* SPU_PERI */
	MK_DEV_2M_8X(L2_1, 0x40000000),

	/* for gic */
	MK_DEV_2M_SECURE(L2_1, GIC600_BASE),

	/* SMP_SS */
	MK_DEV_2M(L2_1, 0x058000000),

	/* Actual RAM size depends on initial RAM and device memory settings */
	MK_MEM_2M_64X(L2_1, 0x60000000),
	MK_MEM_2M_64X(L2_1, 0x60000000 + MB(0x80)),
	MK_MEM_2M_64X(L2_1, 0x60000000 + MB(0x100)),
	MK_MEM_2M_64X(L2_1, 0x60000000 + MB(0x180)),

	/* L2_2: 0x80000000 ~ 0xc0000000 */
	MK_MEM_2M_64X(L2_2, 0x80000000),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x80)),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x100)),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x180)),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x200)),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x280)),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x300)),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x380)),

	/* L2_3: 0xc0000000 ~ 0x100000000 */
	/*
		AUD_SS
		u_aud_sys_mem, u_aud_dma, u_aud_apu, u_aud_wdg
		u_aud_timer, u_aud_i2s0 ~ 6, u_aud_spdif
		u_aud_pwm0 ~ 1
	*/
	MK_DEV_2M_8X(L2_3, 0xC0000000),

	/* DDR_CFG */
	MK_DEV_2M_8X(L2_3, 0xE1000000),
	MK_DEV_2M_8X(L2_3, 0xE1000000 + MB(0x10)),

	/* SFC_SS */
	MK_DEV_2M_8X(L2_3, 0x0E3000000),

	/* NPU1_SS */
	MK_DEV_2M_8X(L2_3, 0x0E4000000),

	/* GPU_SS */
	MK_DEV_2M_8X(L2_3, 0x0E5000000),

	/* MDP_SS */
	MK_DEV_2M_8X(L2_3, 0x0E6000000),

	/* PCIE_SS */
	MK_DEV_2M(L2_3, 0x0E7000000),
	MK_DEV_2M(L2_3, 0x0E7000000 + MB(0x2)),

	/* USB_SS */
	MK_DEV_2M(L2_3, 0x0E7400000),
	MK_DEV_2M(L2_3, 0x0E7400000 + MB(0x2)),

	/* VPU_SS */
	MK_DEV_2M(L2_3, 0x0E7800000),

	/* SADP_SS */
	MK_DEV_2M(L2_3, 0x0E7C00000),
	MK_DEV_2M(L2_3, 0x0E7C00000 + MB(2)),

	/* CISP_SS */
	MK_DEV_2M_8X(L2_3, 0x0E8000000),

	/*
		PERI_SS
		peri_dmac, peri_eic, peri_wdt_0 ~ 2, peri_tim_t0 ~ 1
		peri_pwm_p0 ~ 2, peri_smb_0 ~ 1, peri_i2c_0 ~ 11
		peri_mst_spi_0 ~ 3, peri_slv_spi_0 ~ 3, uart0 ~ 15
		peri_debug
	*/
	MK_DEV_2M_8X(L2_3, 0x0E9000000),

	/*
		PCIe internal mapped memry
	*/
	MK_TBL(1, L1, L2_PCI_CONFIG_SPACE, 0x400000000, 0),
	MK_DEV_2G_8X(L2_PCI_CONFIG_SPACE, 0x400000000),
	MK_DEV_2G_8X(L2_PCI_CONFIG_SPACE, 0x400000000 + GB(0x10)),

};

