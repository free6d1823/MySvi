#ifndef __HDP_PLATFORM_H__
#define __HDP_PLATFORM_H__

#include <asm/platform_arch.h>
#include <asm/mach/cpus.h>

/*******************************************************************************
 * Platform definitions of power-levels
 ******************************************************************************/
#define PLATFORM_RAIL_COUNT		MAX_CPU_RAILS
#define PLATFORM_MAX_CLUSTERS_PER_RAIL  CLUSTERS_PER_RAIL
#define PLATFORM_MAX_CPUS_PER_CLUSTER   CPUS_PER_CLUSTER
#define PLATFORM_MAX_CPUS_PER_RAIL	(PLATFORM_MAX_CPUS_PER_CLUSTER * \
					 PLATFORM_MAX_CLUSTERS_PER_RAIL)
#define PLATFORM_CLUSTER_COUNT		(PLATFORM_RAIL_COUNT * \
					 PLATFORM_MAX_CLUSTERS_PER_RAIL)
#define PLATFORM_CORE_COUNT		(PLATFORM_CLUSTER_COUNT * \
					 PLATFORM_MAX_CPUS_PER_CLUSTER)
#define PLATFORM_CORE_TO_MPIDR(core_num) \
        (((core_num / PLATFORM_MAX_CPUS_PER_CLUSTER) \
        << MPIDR_AFF1_SHIFT)| (core_num & 0x1)) \

/*******************************************************************************
 * Currently supporting up to rail level suspend.
 ******************************************************************************/
#define PLAT_MAX_PWR_LVL		2
#define PLAT_NUM_PWR_DOMAINS		(PLATFORM_RAIL_COUNT \
					 + PLATFORM_CLUSTER_COUNT \
					 + PLATFORM_CORE_COUNT)

#define PLAT_MAX_RET_STATE		4
#define PLAT_MAX_OFF_STATE		5

#define PLAT_MAX_PWR_LVL_STATES		5

/* Convenience definitions for each supported power level */
#define PLAT_CPU_PWR_LVL		PSCI_CPU_PWR_LVL
#define PLAT_CLUSTER_PWR_LVL		(PLAT_CPU_PWR_LVL + 1)
#define PLAT_RAIL_PWR_LVL		(PLAT_CLUSTER_PWR_LVL + 1)


/*******************************************************************************
 * Power domain index conversion
 ******************************************************************************/
#define CLU_TO_RAIL_IDX(idx)        ((idx) / PLATFORM_MAX_CLUSTERS_PER_RAIL)
#define CLU_ON_RAIL_IDX(idx)        ((idx) % PLATFORM_MAX_CLUSTERS_PER_RAIL)

#define CPU_TO_CLU_IDX(idx)         ((idx) >> 1)
#define CPU_ON_CLU_IDX(idx)         ((idx) & 1)

#define CPU_TO_RAIL_IDX(idx)        (CLU_TO_RAIL_IDX(CPU_TO_CLU_IDX(idx)))
#define CPU_ON_RAIL_IDX(idx)        ((idx) % PLATFORM_MAX_CPUS_PER_RAIL)

#define RAIL_MIN_CLU_IDX(idx)       ((idx) * PLATFORM_MAX_CLUSTERS_PER_RAIL)
#define RAIL_MAX_CLU_IDX(idx)       (RAIL_MIN_CLU_IDX(idx) + PLATFORM_MAX_CLUSTERS_PER_RAIL)

#define RAIL_MIN_CPU_IDX(idx)       ((idx) * PLATFORM_MAX_CPUS_PER_RAIL)
#define RAIL_MAX_CPU_IDX(idx)       (RAIL_MIN_CPU_IDX(idx) + PLATFORM_MAX_CPUS_PER_RAIL)

#define CLU_MIN_CPU_IDX(idx)        ((idx) * PLATFORM_MAX_CPUS_PER_CLUSTER)
#define CLU_MAX_CPU_IDX(idx)        (CLU_MIN_CPU_IDX(idx) + PLATFORM_MAX_CPUS_PER_CLUSTER)


/*******************************************************************************
 * Power state id definitions
 ******************************************************************************/
#define PSTATE_CORE_ID_SHIFT		0
#define PSTATE_CLUSTER_ID_SHIFT		4
#define PSTATE_RAIL_ID_SHIFT		8

#define PSTATE_ID_LEVEL_MASK		0xf

#define get_pwrlvl_core_lpm(pstate)	((pstate >> PSTATE_CORE_ID_SHIFT) & \
					 PSTATE_ID_LEVEL_MASK)

#define set_pwrlvl_core_lpm(lstate)	((lstate & PSTATE_ID_LEVEL_MASK) << \
					 PSTATE_CORE_ID_SHIFT)

#define get_pwrlvl_cluster_lpm(pstate)	((pstate >> PSTATE_CLUSTER_ID_SHIFT) & \
					 PSTATE_ID_LEVEL_MASK)

#define set_pwrlvl_cluster_lpm(lstate)	((lstate & PSTATE_ID_LEVEL_MASK) << \
					 PSTATE_CLUSTER_ID_SHIFT)

#define get_pwrlvl_rail_lpm(pstate)	((pstate >> PSTATE_RAIL_ID_SHIFT) & \
					 PSTATE_ID_LEVEL_MASK)

#define set_pwrlvl_rail_lpm(lstate)	((lstate & PSTATE_ID_LEVEL_MASK) << \
					 PSTATE_RAIL_ID_SHIFT)


/*******************************************************************************
 * Platform memory map related constants - address space size
 ******************************************************************************/
#define ADDR_TOP_BIT            40
#define MAX_XLAT_TABLES         20

/*******************************************************************************
 * Platform memory map related constants
 ******************************************************************************/

/***
* Memory bases, offsets and sizes
***/

#define IMEM_BASE           0xFF70000000
#define IMEM_SIZE           0x40000

#define SHARED_IMEM_BASE    0xFF70300000  // left 1 MB space from SYSTEM IMEM Base Address for XBL
#define SHARED_IMEM_SIZE    0x2000

#define DDR_BASE            0x0
#define DDR_SIZE            0xC000000000 // 768 GiB

#define MSG_RAM_BASE        0xFF70400000
#define MSG_RAM_SIZE        0x10000

#define IO_BASE             0xFF00000000
#define IO_SIZE             0xA0000000

#define NS_IMAGE_OFFSET     0x2800000
#define NS_IMAGE_ADDRESS    (DDR_BASE + NS_IMAGE_OFFSET)
#define NS_IMAGE_SIZE       0x200000

#define QDSS_STM_STIMULUS_PORT_BASE_PHYS (0xFF63000000)
#define QDSS_STM_STIMULUS_PORT_BASE_SIZE (0x1000000)

/* New MMU Page sizes for PERIPH_SS and TLMM */
#define PERIPH_SS_SIZE      0x1400000
#define TLMM_SIZE           0x11000

/***
* Register bases
***/

#define CLK_CTL_BASE        0xFF7AC00000  // GCCSN_REG --> moved to  PCC_REG & GCCMW_REG
#define CLK_CTL_SIZE        0x00800000

#define QTIMER_AC_BASE      0xFF7EA40000
#define QTIMER_BASE         0xFF7EA50000
#define QTIMER_SIZE         0x331000
#define QTIMER_FG_COUNT     6

/*******************************************************************************
 * GIC-400 & interrupt handling related constants
 ******************************************************************************/
/* Base FVP compatible GIC memory map */
#define BASE_GICD_BASE      0xFF7EFC0000
#define BASE_GICR_BASE      0xFF7F000000
#define GIC_ARE_ENABLED     0
#if GIC_ARE_ENABLED == 1
#define BASE_GICC_BASE      0x0
#else
#define BASE_GICC_BASE      0xFF7EF00000
#endif
#define BASE_GIC_SIZE       0xD00000

/* Interrupt constants and macros */

#define IRQ_SEC_PHY_TIMER   29

#define IRQ_TCSR_XPU2_SEC   753
#define IRQ_TCSR_XPU2_NSEC  754
#define IRQ_MPM_HMSS_WS1    378
#define IRQ_GPIO_SUMMARY_TZ 544

#define SHARED_IMEM_ADDR        0xFF70034000

/*******************************************************************************
* SDCC/eMMC platform specific memory addresses.
******************************************************************************/
#define IO_SDCC_SDCC5_CFG			0xFF79424000
#define IO_SDCC_SDCC5_SIZE			0x1000
#define SDCC_GPIO_51_CFG			0xFF02340000
#define SDCC_GPIO_52_CFG			0xFF02350000
#define SDCC_GPIO_53_CFG			0xFF02360000
#define SDCC_GPIO_54_CFG			0xFF02370000
#define SDCC_GPIO_55_CFG			0xFF02380000
#define SDCC_GPIO_56_CFG			0xFF02390000
#define SDCC_GPIO_57_CFG			0xFF023A0000
#define SDCC_GPIO_58_CFG			0xFF023B0000
#define SDCC_GPIO_59_CFG			0xFF023C0000
#define SDCC_GPIO_60_CFG			0xFF023D0000
#define SDCC_GPIO_CFG_SIZE			0x1000

/*******************************************************************************
* SPI-NOR  platform specific memory addresses.
******************************************************************************/
#define SPI_NOR_BLSP_QUP0_CFG			0xFF79330000
#define SPI_NOR_BLSP_QUP0_CFG_SIZE		0x1000
#define SPI_NOR_GPIO_40_CFG			0xFF02290000
#define SPI_NOR_GPIO_41_CFG			0xFF022A0000
#define SPI_NOR_GPIO_42_CFG			0xFF022B0000
#define SPI_NOR_GPIO_43_CFG			0xFF022C0000
#define SPI_NOR_GPIO_CFG_SIZE			0x1000

/*******************************************************************************
* SPI GPIOs.
******************************************************************************/
#define SPI_MISO		40
#define SPI_MOSI		41
#define SPI_CLK		42
#define SPI_TPM_CS		33
#define SPI_NOR_CS		43

/*******************************************************************************
* TSCR platform specific memory addresses.
******************************************************************************/
#define TCSR_SOC_HW_VERSION_BASE		0xFF02E40000
#define TCSR_SOC_HW_VERSION_SIZE		0x1000

#define TCSR_SOC_HW_VERSION_2400_V1		0x50010100
#define TCSR_SOC_HW_VERSION_2400_V1_1		0x50010101
#define TCSR_SOC_HW_VERSION_2400_V2		0x50010200

/*******************************************************************************
* No platform specific per-cpu data needed.
******************************************************************************/
#define PLAT_PCPU_DATA_SIZE    0

/* PMIC constants required to enable fuse blowing. On QDF2400
 * the PMIC chip index is 0, and the LVS index is 0. This can
 * be obtained from looking at IMC PMIC code or talking to
 * IMC PMIC owners.
 */
#define PM_VS_LVS1_INDEX 0
#define PMIC_CHIP_INDEX 0

/* TZ-IMC IPC interrupt registers and masks */
#define SYSTEM_RESET 1
#define SYSTEM_OFF   2
#define APCS_TZ_IMC_IPC_INTERRUPT_ADDR              0xFF7E940008  // APCS_CSR_TZ_IPC_INTERRUPT register
#define APCS_TZ_IMC_IPC_INTERRUPT_MASK(X)           (0x1 << X)    // TZ_IMC_IPC[X] (X is 0 - 2)
#define APCS_TZ_IMC_RESET_INTERRUPT_MASK            APCS_TZ_IMC_IPC_INTERRUPT_MASK(SYSTEM_RESET)
#define APCS_TZ_IMC_SHUTDOWN_INTERRUPT_MASK         APCS_TZ_IMC_IPC_INTERRUPT_MASK(SYSTEM_OFF)

/* Platform specific cache line alignment shift.
 * QDF2400 has 128b cache line size.
 */
#define PLAT_CACHE_ALIGN_SHIFT 7

// XPU regions are mapped for test app
#define XPU_PROTECTED_ADDRESS_SEC        (0xFF70028000) // SYS_IMEM Locked to IMC-Only
#define XPU_PROTECTED_ADDRESS_NSEC       (0x10000000) // DDR Locked to Secure-Only
#define XPU_MAPPED_REGION_SIZE           (0x1000)

/*******************************************************************************
* GPIO related constants
******************************************************************************/
#define ACPI_TO_TZ_PCIE_INTR_GPIO        147
#define TPM_TO_TZ_INTR_GPIO              47

/* TCSR related constants */
#define TCSR_SOC_HW_VERSION_ADDR   (0xFF02E40000)
#define TCSR_RG14_SPARE1_BASE   (0xFF02EF0000)
#define TCSR_RG14_SPARE1_REG   (0xFF02EF0010)

/* QUP related constants */
#define I0_BLSP_QUP0_BASE                  (0xFF79330000)

/*******************************************************************************
* Watchdog allocated to TZ
******************************************************************************/
#define PLAT_WDT_CTL_BASE		0xFF7EA30000

#define SCL_DEFAULT_VARIABLES_TEMP_BUF_SIZE 0x00002000
#define SCL_SHARED_VARIABLES_TEMP_BUF_SIZE 0x00002000
#include <asm/mach/qc_platcommon.h>

#endif /* __HDP_PLATFORM_H__ */
