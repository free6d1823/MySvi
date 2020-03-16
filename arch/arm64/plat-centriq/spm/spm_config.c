/*==============================================================================
  FILE:         spm_config.c

  OVERVIEW:     This file contains target specific data/configuration for SPM
                instances.

  DEPENDENCIES: None

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================*/

#include <asm/mach/spm/spm.h>
#include <asm/mach/spm/spm_hal.h>
#include <asm/mach/spm/spm_hal_bsp.h>
#include <target/bitops.h>
//#include "platform.h"
//#include "bl_common.h"

/*==========================================================================
 *                           INTERNAL MACROS
 *=========================================================================*/

#define SYNC_EVENTS 0xFF000000

/**
 * @brief Common macro to fill out structure members for array followed by
 *        its size.
 */
#define SPM_ARRAY(arr) arr, (sizeof(arr)/sizeof(arr[0]))

/*==========================================================================
 *                          CPU SPM CONFIGURATIONS
 *=========================================================================*/
/**
 * @brief Init time config for CPU SPMs.
 *
 * Currently this is same for all CPUs. If that changes, provide another
 * configs.
 */
spm_hal_bsp_cfg_t g_cpu_spm_cfg =
{
  /* frc_ref_clk_on, clk_div */
  {  0x0,            0x1 },

  /* isar, spm wakeup*/
  {  0x0,  SPM_HAL_BSP_WAKEUP_CONFIG_0 },

  /* delay1, delay2, delay3*/
  {  0x3,    0xA,   0x3C1 },

  /* pmic config data array and size */
  NULL,
  0
};

/**
 * @brief SPM command sequences for different CPU low power modes.
 */
static uint8_t cmdseq_cpu_c1[] =
{
  0x03,  /* Sleep w/o IMC handshake */
  0x0F   /* 0x01 cmd addr */
};

static uint8_t cmdseq_cpu_c2[] =
{
  0x52,  /* Snoop Halt Request */
  0xAB,  /* Snoop Halt ack */
  0x00,  /* Clock gate */
  0x58,  /* CPR Bypass */
  0x20,  /* Clamp apmpd */
  0x10,  /* Clamp cpu pd */
  0x38,  /* MAS to RET Sleep */
  0x90,  /* PGS to RET Sleep */
  0x5B,  /* Check if MAS in sleep mode */
  0x3B,  /* Check if PGS in sleep mode */
  0x03,  /* Sleep w/o IMC handshake */
  0x3C,  /* Switch MAS to operational mode */
  0x4B,  /* Check MAS active */
  0x6B,  /* Check Hold CPU HS Open */
  0x90,  /* PGS to operational mode */
  0x2B,  /* PGS in BHS or LDO state */
  0x20,  /* UnClamp apmpd */
  0x10,  /* UnClamp cpu pd */
  0x0B,  /* Check if L2 online */
  0x58,  /* UnBypass CPR */
  0x02,  /* Enable clocks */
  0x52,  /* Snoop Halt Request */
  0xAB,  /* Snoop Halt ack */
  0x0F   /* 0x19 cmd addr */
};

static uint8_t cmdseq_cpu_c3[] =
{
  0x60,  /* Snoop Halt Array Invalidate */
  0x52,  /* Snoop Halt Request */
  0xAB,  /* Snoop Halt ack */
  0x00,  /* Clock gate */
  0x58,  /* CPR Bypass */
  0x20,  /* Clamp apmpd */
  0x10,  /* Clamp cpu pd */
  0x48,  /* Switch MAS to RET mode */
  0x90,  /* Switch PGS to RET mode */
  0x5B,  /* MemArraySeq in PC or RET state */
  0x3B,  /* PwrGateSeq in PC or RET state */
  0x03,  /* Sleep w/o IMC handshake */
  0x4C,  /* Switch MAS to operational mode */
  0x4B,  /* MemArraySeq in APC or Mx ON state */
  0x6B,  /* Hold CPU HS */
  0x90,  /* Switch PGS to operational mode */
  0x2B,  /* PwrGateSeq in BHS or LDO state */
  0x20,  /* UnClamp apmpd */
  0x10,  /* UnClamp cpu pd */
  0x0B,  /* Check if L2 online */
  0x58,  /* CPR Bypass */
  0x00,  /* Enable clocks */
  0x52,  /* Snoop Halt Request */
  0xAB,  /* Snoop Halt ack */
  0x0F   /* 0x32 cmd addr */
};

static uint8_t cmdseq_cpu_c4[] =
{
  0x60,  /* Snoop Halt Array */
  0x52,  /* Snoop Halt Request */
  0xAB,  /* Snoop Halt ack */
  0x72,  /* Retention save request */
  0x8B,  /* Retention Save ack */
  0x70,  /* Retention save request */
  0x00,  /* Clock gate */
  0x58,  /* CPR Bypass */
  0x20,  /* Clamp apmpd */
  0x10,  /* Clamp cpu0pd */
  0x48,  /* PC Sleep to MAS */
  0xA0,  /* PC Sleep to PGS */
  0x5B,  /* MemArraySeq in PC or RET state */
  0x3B,  /* PwrGateSeq in PC or RET state */
  0x03,  /* Sleep w/o IMC handshake */
  0x1B,  /* Check if PMIC ON */
  0x1F,  /* Delay, WA Bug 599 */
  0xBB,  /* Check if NMM Grant asserted */
  0x4C,  /* Switch MAS to operational mode */
  0x4B,  /* Check if MAS active */
  0x6B,  /* Hold CPU HS */
  0xA0,  /* PGS to operational mode */
  0x2B,  /* PGS in BHS or LDO state */
  0x7B,  /* Check SW Event */
  0x40,  /* Retention reset */
  0x0B,  /* Check if L2 online */
  0x00,  /* Enable clocks */
  0xEB,  /* Wait for reset complete */
  0x20,  /* UnClamp apmpd */
  0x10,  /* UnClamp cpu pd */
  0xB0,  /* Turn ON Reset Complete Ack */
  0xFB,  /* Wait till Reset Complete Ack de-asserted */
  0xB0,  /* De-assert Reset Complete Ack */
  0x58,  /* UnBypass CPR */
  0x80,  /* Assert Retention restore req */
  0x42,  /* Turn OFF Retention reset */
  0xCB,  /* Retention Restore ack */
  0x80,  /* DeAssert Retention restore req */
  0x52,  /* Snoop Halt Request */
  0xAB,  /* Snoop Halt ack */
  0x0F   /* 0x5b cmd addr */
};

static uint8_t cmdseq_cpu_c5[] =
{
  0x60,  /* Set Array Invalidation Flag */
  0x52,  /* Snoop Halt Request */
  0xAB,  /* Snoop Halt ack */
  0x00,  /* Clock gate */
  0x58,  /* CPR Bypass */
  0x20,  /* Clamp apmpd */
  0x10,  /* Clamp cpu pd */
  0x48,  /* PC Sleep to MAS */
  0xA0,  /* PC Sleep to PGS */
  0x5B,  /* MemArraySeq in PC or RET state */
  0x3B,  /* PwrGateSeq in PC or RET state */
  0x03,  /* Sleep w/o IMC handshake */
  0x1B,  /* Check if PMIC ON */
  0x1F,  /* Delay, WA Bug 599 */
  0xBB,  /* Check if NMM Grant asserted */
  0x4C,  /* Switch MAS to operational mode */
  0x4B,  /* Check if MAS active */
  0x6B,  /* Hold CPU HS */
  0xA0,  /* PC Sleep to PGS */
  0x2B,  /* PwrGateSeq in BHS or LDO state */
  0x0B,  /* De-assert L2 sleep ack */
  0x7B,  /* Check SW Event */
  0x30,  /* Core POR reset */
  0x02,  /* Enable clocks */
  0xEB,  /* Wait for reset complete */
  0x20,  /* UnClamp apmpd */
  0x10,  /* UnClamp cpu pd */
  0xB0,  /* Turn ON Reset Complete Ack */
  0xFB,  /* Wait till Reset Complete Ack de-asserted */
  0xB0,  /* De-assert Reset Complete Ack */
  0x58,  /* UnBypass CPR */
  0x30,  /* CorePor reset */
  0x52,  /* Snoop Halt Request */
  0xAB,  /* Snoop Halt ack */
  0x0F   /* 0x7e cmd addr */
};

/**
 * @brief CPU mode configurations objects.
 */
spm_hal_bsp_mode_t g_cpu_modes[] =
{
  {
    SPM_ARRAY(cmdseq_cpu_c1),
    SPM_MODE_C1_CLK_GATE,
    (SYNC_EVENTS | SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_cpu_c2),
    SPM_MODE_C2_RET,
    (SYNC_EVENTS | SPM_HAL_PWR_STATE_IDX(1) | SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_cpu_c3),
    SPM_MODE_C3_RET_INV,
    (SYNC_EVENTS | SPM_HAL_PWR_STATE_IDX(2) | SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_cpu_c4),
    SPM_MODE_C4_FASTPC_INV,
    (SYNC_EVENTS | SPM_HAL_PWR_STATE_IDX(3) | SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_cpu_c5),
    SPM_MODE_C5_PC,
    (SYNC_EVENTS | SPM_HAL_PWR_STATE_IDX(7) | SPM_HAL_EN_SET)
  },
};

/**
 * @brief CPU Mode count.
 */
size_t g_cpu_mode_count = ARRAY_SIZE(g_cpu_modes);

/*==========================================================================
 *                       L2/CLUSTER SPM CONFIGURATIONS
 *=========================================================================*/

/**
 * @brief Init time config for L2 SPMs.
 *
 * Currently this is same for all L2s. If that changes, provide another
 * configs.
 */
spm_hal_bsp_cfg_t g_l2_spm_cfg =
{
  /* frc_ref_clk_on, clk_div */
  {  0x0,            0x1 },

  /* isar, spm wakeup*/
  {  0x0,  SPM_HAL_BSP_WAKEUP_CONFIG_0 },

  /* delay1, delay2, delay3*/
  {  0x3,    0xA,    0x3C1 },

  /* pmic config data array and size */
  NULL,
  0
};

/**
 * @brief SPM command sequences for different L2/cluster low power modes.
 */
static uint8_t cmdseq_l2_d1[] =
{
  0x03,  /* Sleep w/o IMC handshake */
  0x0B,  /* Wait for APR SPM idle */
  0x0F
};

static uint8_t cmdseq_l2_d2[] =
{
  0x60,  /* Hold CPU HS Open */
  0x98,  /* Enable APR sleep vote */
  0x6B,  /* Check if both CPU in sleep */
  0x00,  /* Clock gate */
  0xD8,  /* Bypass CPR */
  0x20,  /* Clamp l2Apmpd */
  0xE0,  /* MAS to RET mode */
  0x90,  /* PGS to RET mode */
  0x5B,  /* Check if MAS in sleep */
  0x3B,  /* Check if PGS in sleep */
  0xB2,  /* Lower LDO power */
  0x03,  /* Sleep w/o IMC handshake */
  0x98,  /* Disable APR sleep vote */
  0xB2,  /* Restore LDO power */
  0xE0,  /* Disable MAS RET mode */
  0x90,  /* Disable PGS RET mode */
  0x4B,  /* Check if MAS active */
  0x2B,  /* Check if PGS active */
  0x60,  /* Clear Hold CPU HS Open */
  0x20,  /* Clamp l2Apmpd */
  0x0B,  /* Wait for APR SPM idle */
  0xD8,  /* Unbypass CPR */
  0x00,  /* Enable clocks */
  0x0F
};

static uint8_t cmdseq_l2_d3[] =
{
  0x60,  /* Hold CPU HS Open */
  0x98,  /* Enable APR sleep vote */
  0x72,  /* Retention Save Request */
  0x8B,  /* L2 Retention Save Act */
  0x70,  /* Retention Save Request */
  0x6B,  /* Check if both CPU in sleep */
  0x00,  /* Clock gate */
  0xD8,  /* Bypass CPR */
  0x20,  /* Clamp l2Apmpd */
  0x10,  /* Clamp l2pd */
  0xE0,  /* MAS to RET mode */
  0xA0,  /* PGS to PC mode */
  0x5B,  /* Check if MAS in sleep */
  0x3B,  /* Check if PGS in sleep */
  0x03,  /* Sleep w/o IMC handshake */
  0x98,  /* Disable APR sleep vote */
  0x1B,  /* Check if PMIC ON */
  0xE0,  /* MAS to operational mode */
  0xA0,  /* PGS to operational mode */
  0x4B,  /* Check if MAS active */
  0x2B,  /* Check if PGS active */
  0x60,  /* Clear Hold CPU HS Open */
  0x0B,  /* Wait for APR SPM idle */
  0x7B,  /* Check SW Event */
  0x30,  /* POR ON */
  0x08,  /* GFMUX reset */
  0x02,  /* Enable clocks */
  0x08,  /* Turn off GFMUX reset */
  0xAB,  /* Wait for reset complete */
  0x20,  /* Clamp l2Apmpd */
  0x10,  /* Clamp l2pd */
  0x78,  /* Assert reset complete ACK */
  0xBB,  /* Wait for reset complete */
  0x78,  /* Deassert reset complete ACK */
  0x80,  /* Assert Retention Restore Request */
  0xD8,  /* Unbypass CPR */
  0x32,  /* POR OFF */
  0xCB,  /* Retention Restore Ack */
  0x80,  /* Deassert Retention Restore Request */
  0x0F
};

static uint8_t cmdseq_l2_d4[] =
{
  0x60,  /* Hold CPU HS Open */
  0x72,  /* Retention Save Request */
  0x8B,  /* L2 Retention Save Act */
  0x70,  /* Retention Save Request */
  0x6B,  /* Check if both CPU in sleep */
  0x98,  /* Enable APR sleep vote */
  0x00,  /* Clock gate */
  0x88,  /* Bypass CPR */
  0x20,  /* Clamp l2Apmpd */
  0x10,  /* Clamp l2pd */
  0xF0,  /* Turn OFF PLL */
  0xD0,  /* MAS to PC mode */
  0xA0,  /* PGS to PC mode */
  0x5B,  /* Check if MAS in sleep */
  0x3B,  /* Check if PGS in sleep */
  0x03,  /* Sleep w/o IMC handshake */
  0x9A,  /* Disable APR sleep vote */
  0x88,  /* Set CPR throttle flag */
  0x1B,  /* Check if PMIC ON */
  0xD0,  /* MAS to operational mode */
  0xA0,  /* PGS to operational mode */
  0x4B,  /* Check if MAS active */
  0x2B,  /* Check if PGS active */
  0x60,  /* Clear Hold CPU HS Open */
  0x0B,  /* Wait for APR SPM idle */
  0xF0,  /* Turn ON PLL */
  0x7B,  /* Check SW Event */
  0x30,  /* POR ON */
  0x08,  /* GFMUX reset */
  0xEB,  /* Check for PLL lock */
  0x02,  /* Enable clocks */
  0x08,  /* Turn off GFMUX reset */
  0xAB,  /* Wait for reset complete */
  0x20,  /* Clamp l2Apmpd */
  0x10,  /* Clamp l2pd */
  0x78,  /* Assert reset complete ACK */
  0xBB,  /* Wait for reset complete */
  0x78,  /* Deassert reset complete ACK */
  0x80,  /* Assert Retention Restore Request */
  0x32,  /* POR OFF */
  0xCB,  /* Retention Restore Ack */
  0x80,  /* Deassert Retention Restore Request */
  0x0F
};

static uint8_t cmdseq_l2_d5[] =
{
  0x60,  /* Hold CPU HS Open */
  0x6B,  /* Check if both CPU in sleep */
  0x98,  /* Enable APR sleep vote */
  0x00,  /* Clock gate */
  0x88,  /* Bypass CPR */
  0x20,  /* Clamp l2Apmpd */
  0x10,  /* Clamp l2pd */
  0xF0,  /* Turn OFF PLL */
  0xD0,  /* MAS to PC mode */
  0xA0,  /* PGS to PC mode */
  0x5B,  /* Check if MAS in sleep */
  0x3B,  /* Check if PGS in sleep */
  0x03,  /* Sleep w/o IMC handshake */
  0x9A,  /* Disable APR sleep vote */
  0x88,  /* Set CPR throttle flag */
  0x1B,  /* Check if PMIC ON */
  0xD0,  /* MAS to operational mode */
  0xA0,  /* PGS to operational mode */
  0x4B,  /* Check if MAS active */
  0x2B,  /* Check if PGS active */
  0x60,  /* Clear Hold CPU HS Open */
  0x0B,  /* Wait for APR SPM idle */
  0xF0,  /* Turn ON PLL */
  0x7B,  /* Check SW Event */
  0x30,  /* POR ON */
  0x08,  /* GFMUX reset */
  0xEB,  /* Check for PLL lock */
  0x02,  /* Enable clocks */
  0x08,  /* Turn off GFMUX reset */
  0xAB,  /* Wait for reset complete */
  0x20,  /* Clamp l2Apmpd */
  0x10,  /* Clamp l2pd */
  0x78,  /* Assert reset complete ACK */
  0xBB,  /* Wait for reset complete */
  0x78,  /* Deassert reset complete ACK */
  0x30,  /* POR OFF */
  0x0F
};

/**
 * @brief L2 Mode configuration objects.
 */
spm_hal_bsp_mode_t g_l2_modes[] =
{
  { /* Described, but unsupported via PSCI */
    SPM_ARRAY(cmdseq_l2_d1),
    SPM_MODE_D1_CLK_GATE,
    (SYNC_EVENTS | SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_l2_d2),
    SPM_MODE_D2_RET,
    (SYNC_EVENTS | SPM_HAL_PWR_STATE_IDX(1) | SPM_HAL_ISAR_SET | SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_l2_d3),
    SPM_MODE_D3_FASTPC_RET,
    (SYNC_EVENTS | SPM_HAL_PWR_STATE_IDX(2) | SPM_HAL_ISAR_SET | SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_l2_d4),
    SPM_MODE_D4_FASTPC_INV,
    (SYNC_EVENTS | SPM_HAL_PWR_STATE_IDX(3) | SPM_HAL_ISAR_SET | SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_l2_d5),
    SPM_MODE_D5_PC,
    (SYNC_EVENTS | SPM_HAL_PWR_STATE_IDX(7) | SPM_HAL_ISAR_SET | SPM_HAL_EN_SET)
  },
};

/**
 * @brief L2 Mode count.
 */
size_t g_l2_mode_count = ARRAY_SIZE(g_l2_modes);

/*==========================================================================
 *                          APR SPM CONFIGURATIONS
 *=========================================================================*/

/**
 * @brief APR SPM PMIC address mapping.
 */
spm_hal_bsp_pmic_cfg_t g_apr_pmic_cfg[] =
{
  { SPM_HAL_BSP_PMIC_MODE_NOMINAL, 0x80, 0x4, SPM_HAL_BSP_PMIC_DATA_SIZE_0, 1 },
  { SPM_HAL_BSP_PMIC_MODE_PC,      0x00, 0x0, SPM_HAL_BSP_PMIC_DATA_SIZE_0, 1 }
};

/**
 * @brief Init time config for APR SPMs.
 *
 * Currently this is same for all APRs.
 */
spm_hal_bsp_cfg_t g_apr_spm_cfg =
{
  /* frc_ref_clk_on, clk_div */
  {  0x0,            0x1 },

  /* isar, spm wakeup*/
  {  0x0,  SPM_HAL_BSP_WAKEUP_CONFIG_0 },

  /* delay1, delay2, delay3*/
  {  0xA,    0x32,   0x3FF },

  /* pmic config data array and size */
  SPM_ARRAY(g_apr_pmic_cfg)
};

/**
 * @brief SPM command sequences for different APR low power modes.
 */
static uint8_t cmdseq_apr_g1[] =
{
  0x03,  /* Sleep w/o IMC handshake */
  0x84,  /* Wait for CBF Active valid */
  0x5B,  /* Wait for CBF online */
  0x0F
};

static uint8_t cmdseq_apr_g2[] =
{
  0x10,  /* Gate APC_PMIC_ON */
  0x00,  /* Clamp Apcpd IOs */
  0x11,  /* PMIC op: power collapse rail */
  0x20,  /* Disable ref generator */
  0x03,  /* Sleep w/o IMC handshake */
  0x20,  /* Enable ref generator */
  0x01,  /* PMIC op: normal voltage */
  0x84,  /* Wait for CBF Active valid */
  0x3F,  /* Delay 102us */
  0x3F,  /* Delay 102us */
  0x3F,  /* Delay 102us */
  0x3F,  /* Delay 102us */
  0x3F,  /* Delay 102us */
  0x3F,  /* Delay 102us */
  0x3F,  /* Delay 102us */
  0x3F,  /* Delay 102us */
  0x50,  /* Assert APC reset */
  0x5B,  /* Wait for CBF online */
  0x00,  /* Unclamp Apcpd IOs */
  0x50,  /* Deassert APC reset */
  0x10,  /* Ungate APC_PMIC_ON */
  0x0F
};

/**
 * @brief APR Mode configuration objects.
 */
spm_hal_bsp_mode_t g_apr_modes[] =
{
  {
    SPM_ARRAY(cmdseq_apr_g1),
    SPM_MODE_G1_LIGHT_SLEEP,
    (SPM_HAL_EN_SET)
  },
  {
    SPM_ARRAY(cmdseq_apr_g2),
    SPM_MODE_G2_APC_OFF,
    (SPM_HAL_PWR_STATE_IDX(1) | SPM_HAL_EN_SET)
  },
};

/**
 * @brief APR Mode count.
 */
size_t g_apr_mode_count = ARRAY_SIZE(g_apr_modes);
