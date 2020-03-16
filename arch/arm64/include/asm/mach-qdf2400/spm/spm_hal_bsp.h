#ifndef _SPM_HAL_BSP_H_
#define _SPM_HAL_BSP_H_

/*==============================================================================
Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================

  FILE:         spm_hal_bsp.h

  OVERVIEW:     This file provides typedefs for the target specific data. Usually
                these types emulate underlying SPM HW block.

  DEPENDENCIES: None

==============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <asm/hal/HALcomdef.h>

/*========================================================================
 *                                 TYPES
 *=======================================================================*/

/**
 * @brief Enumeration to indicate size of PMIC data.
 */
typedef enum
{
  SPM_HAL_BSP_PMIC_DATA_SIZE_0,   /* HW treats data size to be 1 byte */
  SPM_HAL_BSP_PMIC_DATA_SIZE_1    /* HW treats data size to be 2 bytes */
} spm_hal_bsp_pmic_data_size_t;

/**
 * @brief SPM wakeup configuration type.
 */
typedef enum
{
  SPM_HAL_BSP_WAKEUP_CONFIG_0,    /* sys_spm_wakeup */
  SPM_HAL_BSP_WAKEUP_CONFIG_1,    /* sys_spm_wakeup OR !cpu_spm_wait_req */
  SPM_HAL_BSP_WAKEUP_CONFIG_2,    /* sys_spm_wakeup OR rising edge of
                                   * sys_spm_dbg_nopwrdwn */
  SPM_HAL_BSP_WAKEUP_CONFIG_3     /* sys_spm_wakeup OR !cpu_spm_wait_req OR
                                   * rising edge of sys_saw_dbg_nopwrdwn */
} spm_hal_bsp_wakeup_cfg_t;

/**
 * @brief PMIC operation mode for the commands that are being sent to PMIC.
 */
typedef enum
{
  SPM_HAL_BSP_PMIC_MODE_NOMINAL,
  SPM_HAL_BSP_PMIC_MODE_PC,
  SPM_HAL_BSP_PMIC_MODE_MAX = 6  /* Max no of modes supported on SAW3 */
} spm_hal_bsp_pmic_mode_t;

/**
 * @brief Structure containing configuration of common SPM and AVS controls.
 */
typedef struct spm_hal_bsp_clk_cfg_s
{
  uint8_t frc_ref_clk_on;
  uint8_t clk_div;
} spm_hal_bsp_clk_cfg_t;

/**
 * @brief Contains some of the SPM control parameters.
 */
typedef struct spm_hal_bsp_ctl_cfg_s
{
  uint8_t isar;                          /* Inhibit start address reset */
  spm_hal_bsp_wakeup_cfg_t wakeup;     /* SPM wakeup configuration */
} spm_hal_bsp_ctl_cfg_t;

/**
 * @brief Type to provide delays between various SPM commands.
 */
typedef struct spm_hal_bsp_delay_cfg_s
{
  uint16_t delay1;
  uint16_t delay2;
  uint16_t delay3;
} spm_hal_bsp_delay_cfg_t;

typedef struct spm_hal_bsp_pmic_cfg_s
{
  spm_hal_bsp_pmic_mode_t mode;        /* PMIC mode of operation */
  uint8_t data;                          /* Data sent to PMIC arbiter */
  uint8_t delay;                         /* PMIC delay - time between pmic
                                        * command and next command in sequnce */
  spm_hal_bsp_pmic_data_size_t size;   /* Data size per PMIC request */
  uint8_t index;                         /* PMIC arbiter address index */
} spm_hal_bsp_pmic_cfg_t;

/**
 * @brief Structure containing initial SPM configuration.
 */
typedef struct spm_hal_bsp_cfg_s
{
  spm_hal_bsp_clk_cfg_t clk_cfg;
  spm_hal_bsp_ctl_cfg_t ctl_cfg;
  spm_hal_bsp_delay_cfg_t delay_cfg;
  spm_hal_bsp_pmic_cfg_t *pmic_cfg;
  uint8_t pmic_cfg_count;                /* Number of elements above */
} spm_hal_bsp_cfg_t;

/**
 * @brief Type to specify an SPM command sequence for a low power mode.
 */
typedef struct spm_hal_bsp_mode_s
{
  uint8_t* cmds;               /* Pointer to command sequence */
  uint16_t length;             /* Length of above command sequence */
  uint8_t mode_id;             /* Mode id - usually comes from HPG */
  uint32_t ctl_vals;
  int16_t start_addr;          /* Sequence's start address in SPM - filled
                              * during initialization. */
} spm_hal_bsp_mode_t;


#ifdef __cplusplus
}
#endif

#endif

