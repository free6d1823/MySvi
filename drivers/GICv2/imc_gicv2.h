/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#ifndef __IMC_GIC_H__
#define __IMC_GIC_H__

#include <com_dtypes.h>
#include <ctype.h>
#include <hdts_interrupt.h>
#include <stdbool.h>
#include <string.h>

#ifdef CONFIG_IMC_GICv2
#define SUPPORT_INTERRUPT_TABLE
#endif

#define IMC_GICD_SGIR_ADDR (0xFF6FA40F00)
#define IMC_GICC_CTLR_ADDR (0xFF6FA42000)
#define IMC_QGICV2_REG_BASE (0xFF6F800000 + 0x00240000)
#define IMC_GICD_ISRn_ADDR(n) ((IMC_QGICV2_REG_BASE) + 0x00000080 + 0x4 * (n))
#define IMC_QTMR_WDT_CSR_ADDR (0xFF6FB40000)
#define IMC_QTMR_WDT_OFFSET_ADDR (0xFF6FB40008)
#define IMC_QTMR_WDT_RR_ADDR (0xFF6FB80000)
#define MPM_WDOG_CONTROL_ADDR (0xFF26AB0014)
#define IMC_GICM_TYPER_NS_ADDR (0xFF6FA80008)
#define IMC_GICM_MSI_SETSPI_NS_ADDR (0xFF6FA80040)
#define IMC_PROTNS_CTRL_ADDR (0xFF6FBC0304)
#define IMC_MSA_CTRL_ADDR (0xFF6FBC0300)
#define GICV2_MSI_INT_START                                                    \
  ((in_dword_masked(IMC_GICM_TYPER_NS_ADDR, 0x3ff0000)) >> 16)
#define GICV2_MSI_INT_END                                                      \
  (GICV2_MSI_INT_START + (in_dword_masked(IMC_GICM_TYPER_NS_ADDR, 0x3ff)) - 1)
extern UINT32 g_active_int_id;
extern void gicv2_int_handler();
extern UINT32 imc_wdog_config(UINT8 secure);
extern void imc_wdog_trigger();
#endif
