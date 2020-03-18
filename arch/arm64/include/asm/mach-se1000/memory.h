/*
 */
#ifndef __SE1000_MEMORY_H_INCLUDE__
#define __SE1000_MEMORY_H_INCLUDE__
#include <asm/mach/cpus.h>

#include <target/compiler.h>
#include <target/cpus.h>

#define DDR_L1GB_START	0x60000000
#define DDR_L1GB_SIZE 	0x40000000
#define DDR_L1GB_END		(DDR_L1GB_START + DDR_L1GB_SIZE)

#define SH_RAM_START	0x00000
#define SH_RAM_SIZE 	0x80000
#define SH_RAM_END		(SH_RAM_START + SH_RAM_SIZE)

#define SVI_TEXT_BASE	(SH_RAM_START + 0x10000)
#define SVI_RAM_END		SH_RAM_END

#define PAGE_SIZE			4096

#define ARCH_TIMER_FREQUENCY	62500000

#define UART_BASE(n)			(0xC1200000 + (n*0x10000))

#define EMAC_BASE			    0xa24a0000

#define GIC600_GICR_COUNT       2
#define GIC600_GITS_COUNT       1
#define GIC600_BASE             0xb6000000

#define GIC600_PAGE_SHIFT       16

#define GIC600_GICR_COUNT       2
#define GIC600_GITS_COUNT       1
#define GIC600_BASE             0xb6000000

#define GIC600_GICD_BASE        GIC600_BASE
#define GIC600_GICR_BASE(x)     GIC600_BASE + ( (4 + (2*GIC600_GITS_COUNT) + x*2) << GIC600_PAGE_SHIFT )

#define GICD_gic3_BASE		GIC600_GICD_BASE
#define GICR_gic3_BASE		GIC600_GICR_BASE(0)

#define GICR_GIC3_CPU_SHIFT		17

#define SMMU_V3_BASE			0x09050000

#define SYSREG_BASE				0xa00c0000

#define UFS0_REG_BASE			0xA4030000

#define DW_AHB_DMAC				0xC1000000
#define DW_WDT_REG_BASE(n)		(0xC1020000 + (n*0x10000))
#define DW_I2C_REG_BASE(n)		(0xC10C0000 + (n*0x10000))
#define DW_SPI_REG_BASE(n)		(0xC1180000 + (n*0x10000))

#define EMMC_REG_BASE			0
#define EMMC_DESC_BASE			0

#define SDHCI_REG_BASE			0xa4020000

#define D71_REG_BASE 			0xc3100000

#define VC8000D_REG_BASE			0xbc000000
#define VC8000E_REG_BASE			0xbc020000
#endif /* __SE1000_MEMORY_H_INCLUDE__ */

