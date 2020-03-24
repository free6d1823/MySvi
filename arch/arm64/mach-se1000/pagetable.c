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

	/* L2_2: 0x00000000 ~ 0x40000000 */

	/* for SVI_TEXT_BASE */
	MK_TBL(2, L2_0, L3_SVI, PAGE(0), 0),
	MK_PAGE_MEMX_32X(L3_SVI, SVI_TEXT_BASE),
	MK_PAGE_MEMX_32X(L3_SVI, SVI_TEXT_BASE + PAGE(0x20)),
	MK_PAGE_MEMX_32X(L3_SVI, SVI_TEXT_BASE + PAGE(0x40)),
	MK_PAGE_MEMX_8X(L3_SVI, SVI_TEXT_BASE + PAGE(0x60)),
	MK_PAGE_MEMX_8X(L3_SVI, SVI_TEXT_BASE + PAGE(0x68)),

	MK_DEV_2M(L2_0, SMMU_V3_BASE),

	/* L2_1: 0x40000000 ~ 0x80000000 */
	/* Actual RAM size depends on initial RAM and device memory settings */
	MK_MEM_2M_64X(L2_1, 0x60000000),
	MK_MEM_2M_64X(L2_1, 0x60000000 + MB(0x80)),
	MK_MEM_2M_64X(L2_1, 0x60000000 + MB(0x100)),
	MK_MEM_2M_64X(L2_1, 0x60000000 + MB(0x180)),
	MK_MEM_2M_64X(L2_2, 0x80000000),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x80)),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x100)),
	MK_MEM_2M_64X(L2_2, 0x80000000 + MB(0x180)),

	/* L2_2: 0x80000000 ~ 0xc0000000 */
	/*
		SMP_SS
		Spinlock, Mailbox, Security_Ctrl, INTC, Pin_reg
		Systick, Srcure_RTC, Sec_Timer, Sec_WDG, AonClkRst_Ctrl
		PMU, ROSC, sysreg, PVT_ctrl
	*/
	MK_DEV_2M(L2_2, 0xA0000000),

	/*
		SAF_SS
		r52_apb0, mmu_tcu, intc, saf_ctrl, uart, i2c, spi
		safe_reg, fault_det, eth0_apb, eth1_apb, GIC
	*/
	MK_DEV_2M(L2_2, 0xA2400000),
	MK_DEV_2M(L2_2, 0xA2400000 + MB(2)),

	/*
		SFC_SS
		BootROM, SD_EMMC, UFS_C0, UFS_C1, QSPI, QSPI_RemapIO
		ClkRst_Ctrl, SysReg, INTC, Crypto_smx, HiDMA, Crypto_ips
	*/
	MK_DEV_2M_64X(L2_2, 0xA4000000),
	MK_DEV_2M_64X(L2_2, 0xA4000000 + MB(80)),
	MK_DEV_2M_8X(L2_2, 0xA4000000 + MB(0x100)),
	MK_DEV_2M_8X(L2_2, 0xA4000000 + MB(0x110)),

	/* for gic */
	MK_DEV_2M_SECURE(L2_2, GIC600_BASE),

	/* DDR_SS */
	MK_DEV_2M_8X(L2_2, 0xB8000000),
	MK_DEV_2M_8X(L2_2, 0xBB000000 + MB(80)),

	/*
		CON_SS
		pcie0dbi ~ pcie3dbi, usb3_0, usb3_1, usb2
	*/
	MK_DEV_2M_8X(L2_2, 0xBB000000),

	/*
		VPU_SS
		vpud0 ~ 1, vpue
	*/
	MK_DEV_2M(L2_2, 0xBC000000),

	/* NPU_SS */
	MK_DEV_2M(L2_2, 0xBD000000),

	/*
		ISP_SS
		isp0 ~ 11
	*/
	MK_DEV_2M(L2_2, 0xBE000000),

	/*
		GPU_SS
		gpu_c0_s0 ~ 1
	*/
	MK_DEV_2M(L2_2, 0xBF000000),

	/* L2_3: 0xc0000000 ~ 0x100000000 */
	/*
		AUD_SS
		u_aud_sys_mem, u_aud_dma, u_aud_apu, u_aud_wdg
		u_aud_timer, u_aud_i2s0 ~ 6, u_aud_spdif
		u_aud_pwm0 ~ 1
	*/
	MK_DEV_2M(L2_3, 0xC0000000),

	/*
		PERI_SS
		peri_dmac, peri_eic, peri_wdt_0 ~ 2, peri_tim_t0 ~ 1
		peri_pwm_p0 ~ 2, peri_smb_0 ~ 1, peri_i2c_0 ~ 11
		peri_mst_spi_0 ~ 3, peri_slv_spi_0 ~ 3, uart0 ~ 15
		peri_debug
	*/
	MK_DEV_2M(L2_3, 0xC1000000),
	MK_DEV_2M(L2_3, 0xC1000000 + MB(2)),

	/* MDP_SS */
	MK_DEV_2M(L2_3, 0xC3000000),
	MK_DEV_2M_8X(L2_3, 0xC3000000 + MB(2)),

	/* SADP_SS */
	MK_DEV_2M(L2_3, 0xC5000000),
	MK_DEV_2M(L2_3, 0xC5000000 + MB(2)),

	/*
		PCIe internal mapped memry
	*/
	MK_TBL(1, L1, L2_PCI_CONFIG_SPACE, 0x400000000, 0),
	MK_DEV_2G_8X(L2_PCI_CONFIG_SPACE, 0x400000000),
	MK_DEV_2G_8X(L2_PCI_CONFIG_SPACE, 0x400000000 + GB(0x10)),

};

