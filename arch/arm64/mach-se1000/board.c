#include <asm/mmu.h>
#include <target/bitops.h>
#include <asm/memory.h>

const mmu_map_attr_t static_mmu_entry_list[] =
{
#if 1
	/*virt_gicdist, virt_gicredist*/
	{ GIC600_GICD_BASE, GIC600_GICD_BASE, 0x00200000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, true, false,
	  MMU_MAP_NAME_STATIC(gic)
	},

	/* SMP_SS
	   Spinlock, Mailbox, Security_Ctrl, INTC, Pin_reg
	   Systick, Srcure_RTC, Sec_Timer, Sec_WDG, AonClkRst_Ctrl
	   PMU, ROSC, sysreg, PVT_ctrl
	 */
	{ 0xA0000000, 0xA0000000, 0x00200000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(smp)
	},

	/* SAF_SS
	   r52_apb0, mmu_tcu, intc, saf_ctrl, uart, i2c, spi
	   safe_reg, fault_det, eth0_apb, eth1_apb, GIC
	 */
	{ 0xA2400000, 0xA2400000, 0x00400000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(saf)
	},

	/* SFC_SS
	   BootROM, SD_EMMC, UFS_C0, UFS_C1, QSPI, QSPI_RemapIO
	   ClkRst_Ctrl, SysReg, INTC, Crypto_smx, HiDMA, Crypto_ips
	 */
	{ 0xA4000000, 0xA4000000, 0x10C00000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(sfc)
	},

	/* DDR_SS */
	{ 0xB8000000, 0xB8000000, 0x02000000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(ddr)
	},

	/* CON_SS
	   pcie0dbi ~ pcie3dbi, usb3_0, usb3_1, usb2
	 */
	{ 0xBB000000, 0xBB000000, 0x00600000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(con)
	},

	/* VPU_SS
	   vpud0 ~ 1, vpue
	 */
	{ 0xBC000000, 0xBC000000, 0x00200000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(vpu)
	},

	/* NPU_SS */
	{ 0xBD000000, 0xBD000000, 0x00200000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(npu)
	},

	/* ISP_SS
	   isp0 ~ 11
	 */
	{ 0xBE000000, 0xBE000000, 0x00200000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(isp)
	},

	/* GPU_SS
	   gpu_c0_s0 ~ 1
	 */
	{ 0xBF000000, 0xBF000000, 0x00200000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(aud)
	},

	/* AUD_SS
	   u_aud_sys_mem, u_aud_dma, u_aud_apu, u_aud_wdg
	   u_aud_timer, u_aud_i2s0 ~ 6, u_aud_spdif
	   u_aud_pwm0 ~ 1
	 */
	{ 0xC0000000, 0xC0000000, 0x00200000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(aud)
	},

	/* PERI_SS
	   peri_dmac, peri_eic, peri_wdt_0 ~ 2, peri_tim_t0 ~ 1
	   peri_pwm_p0 ~ 2, peri_smb_0 ~ 1, peri_i2c_0 ~ 11
	   peri_mst_spi_0 ~ 3, peri_slv_spi_0 ~ 3, uart0 ~ 15
	   peri_debug
	 */
	{ 0xC1000000, 0xC1000000, 0x00400000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(peri)
	},

	/* MDP_SS */
	{ 0xC3000000, 0xC3000000, 0x01200000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(mdp)
	},

	/* SADP_SS */
	{ 0xC5000000, 0xC5000000, 0x00400000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(sadp)
	},
#else
	{ 0xa0000000LL, 0xa0000000LL, 0x40000000LL,
	  PERM_RW, 0x0, CACHE_DEVICE_nGnRnE, false, false,
	  MMU_MAP_NAME_STATIC(mem)
	},
#endif
	/* Actual RAM size depends on initial RAM and device memory settings */
	{ 0x60000000LL, 0x60000000LL, 0x40000000LL,
	  PERM_RW, SHARE_INNER, CACHE_OUTER_WB_INNER_WB, false, false,
	  MMU_MAP_NAME_STATIC(mem)
	},
};

UINT32 static_mmu_entry_list_len = ARRAY_SIZE(static_mmu_entry_list);


