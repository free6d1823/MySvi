#ifndef _SPM_TARGET_H_
#define _SPM_TARGET_H_

/*==============================================================================
  FILE:         spm_target.h

  OVERVIEW:     This file provides target specific SPM types.

  DEPENDENCIES: None

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=======================================================================
 *                           TYPE DEFINITIONS
 *======================================================================*/

/**
 * @brief CPU SPM low power modes
 */
enum
{
  SPM_MODE_C0_RUN,
  SPM_MODE_C1_CLK_GATE,
  SPM_MODE_C2_RET,
  SPM_MODE_C3_RET_INV,
  SPM_MODE_C4_FASTPC_INV,
  SPM_MODE_C5_PC,
  SPM_NUM_CPU_LOW_POWER_MODES
};

/**
 * @brief L2 SPM low power modes
 */
enum
{
  SPM_MODE_D0_RUN,
  SPM_MODE_D1_CLK_GATE,
  SPM_MODE_D2_RET,
  SPM_MODE_D3_FASTPC_RET,
  SPM_MODE_D4_FASTPC_INV,
  SPM_MODE_D5_PC,
  SPM_NUM_L2_LOW_POWER_MODES
};

/**
 * @brief APR SPM low power modes
 */
enum
{
  SPM_MODE_G0_APC_ON,
  SPM_MODE_G1_LIGHT_SLEEP,
  SPM_MODE_G2_APC_OFF,
  SPM_NUM_APR_LOW_POWER_MODES
};

/**
 * @brief Types of subsystems which are managed by SPMs.
 */
typedef enum
{
  SPM_TYPE_CPU,
  SPM_TYPE_L2,
  SPM_TYPE_APR,
  SPM_NUM_TYPES
} spm_type_t;

#ifdef __cplusplus
}
#endif


#endif
