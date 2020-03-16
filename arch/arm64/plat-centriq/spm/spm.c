/*==============================================================================
  FILE:         spm.c

  OVERVIEW:     This file implements some of the APIs defined in spm public
                header file to interact with SPM HW block(s).

  DEPENDENCIES: None

  Copyright (c) 2016 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================*/

#include <asm/mach/spm/spm.h>
#include <asm/mach/spm/spm_hal.h>
#include <asm/mach/spm/spm_hal_bsp.h>
#include <asm/mach/spm/spm_internal.h>
#include <stdbool.h>

/*=======================================================================
 *                             GLOBAL FUNCTIONS
 *======================================================================*/

/*
 * spm_driver_init
 */
void spm_driver_init(void)
{
  /* Nothing as of now to initialize in instance agnostic way. */
  spm_target_init();
}

/*
 * spm_init
 */
spm_result_t spm_init(spm_handle handle)
{
  spm_result_t result;

  if (NULL == handle || NULL == handle->cfg || NULL == handle->modes)
    return SPM_INVALID_PARAM;

  spm_internal_config(handle);

  result = spm_copy_cmd_seqs(handle);

  /* Ensure updates to SPM data made during init are visible to cores
   * running without caches enabled.
   * Xin : remove the spm_cache_flush function */
  //spm_cache_flush(handle);

  return result;
}

/*
 * spm_enable
 */
spm_result_t spm_enable(spm_handle handle, bool enable)
{
  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_PARAM;

  spm_hal_enable(handle->addr, (enable ? 1 : 0));

  return SPM_SUCCESS;
}

/*
 * spm_wakeup
 */
spm_result_t spm_wakeup(spm_handle handle)
{
  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_PARAM;

  spm_hal_wakeup(handle->addr);

  return SPM_SUCCESS;
}

/*
 * spm_busy
 */
spm_result_t spm_busy(spm_handle handle, bool *busy)
{
  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_PARAM;

  if (spm_hal_status(handle->addr) & SPM_HWIO_FMSK(SPM_STS, SPM_BUSY))
    *busy = true;
  else
    *busy = false;

  return SPM_SUCCESS;
}

/*
 * spm_set_rpm_handshake
 */
spm_result_t spm_set_rpm_handshake(spm_handle handle, bool handshake)
{
  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_HANDLE;

  spm_hal_config_rpm_handshake(handle->addr, (handshake ? 1 : 0));

  return SPM_SUCCESS;
}

/*
 * spm_set_low_power_mode
 */
spm_result_t spm_set_low_power_mode(spm_handle handle, uint8_t lpm)
{
  spm_hal_bsp_mode_t *mode;
  int32_t mode_index;

  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_HANDLE;

  mode_index = spm_mode_index(handle, lpm);

  if (SPM_HAL_INVALID_MODE_INDEX == mode_index)
    return SPM_INVALID_PARAM;

  mode = &handle->modes[mode_index];

  if (SPM_HAL_INVALID_SEQ_START_ADR == mode->start_addr)
    return SPM_INVALID_PARAM;

  spm_hal_config_lpm_ctl(handle->addr, mode->ctl_vals);

  return SPM_SUCCESS;
}

/*
 * spm_executing_low_power_mode
 */
spm_result_t spm_executing_low_power_mode(spm_handle handle, int16_t *mode_id)
{
  uint16_t start, end, last_cmd_adr;
  uint32_t i = 0;
  spm_hal_bsp_mode_t *mode;

  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_HANDLE;

  if (NULL == mode_id)
    return SPM_INVALID_PARAM;

  *mode_id = SPM_HAL_INVALID_MODE_INDEX;
  last_cmd_adr = spm_hal_last_cmd_addr(handle->addr);

  for (i = 0; i < handle->mode_count; i++)
  {
    mode = &handle->modes[i];
    start = mode->start_addr;
    end = start + mode->length - 1;    /* -1 for end of sequence command */

    if (0 != last_cmd_adr && last_cmd_adr >= start && last_cmd_adr < end)
    {
      /* There is a subtlety here.
       * If we don't check last_cmd_adr to be non zero, any call made before
       * spm is triggered for the first time will incorrectly return first
       * mode as the one being executed. This may misrepresent node's state.
       *
       * However, with this check, if SPM is indeed triggered and query is
       * made just after first command execution, we would return no mode
       * as running. This can happen even when the query is made from
       * different core before before actually SPM is triggered. So seems
       * like a safe window.
       * */
      *mode_id = mode->mode_id;
      break;
    }
  }

  return SPM_SUCCESS;
}

/*
 * spm_executed_low_power_mode
 */
spm_result_t spm_executed_low_power_mode(spm_handle handle, uint8_t lpm,
                                         bool *executed)
{
  uint16_t mode_end_adr, last_cmd_adr;
  int32_t mode_index;
  spm_hal_bsp_mode_t *mode;

  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_HANDLE;

  if (NULL == executed)
    return SPM_INVALID_PARAM;

  mode_index = spm_mode_index(handle, lpm);

  if (SPM_HAL_INVALID_MODE_INDEX == mode_index)
    return SPM_INVALID_PARAM;

  *executed = false;
  last_cmd_adr = spm_hal_last_cmd_addr(handle->addr);

  mode = &handle->modes[mode_index];
  mode_end_adr = mode->start_addr + mode->length - 1; /* end of sequence cmd */

  if (last_cmd_adr == mode_end_adr)
    *executed = true;

  return SPM_SUCCESS;
}

/*
 * Following functions rely on SAW4 functionality
 */
#ifdef SPM_HAL_V4

/*
 * spm_start_low_power_mode
 */
spm_result_t spm_start_low_power_mode(spm_handle handle, uint8_t lpm)
{
  spm_hal_bsp_mode_t *mode;
  int32_t mode_index;
  uint32_t ctl_val;

  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_HANDLE;

  mode_index = spm_mode_index(handle, lpm);

  if (SPM_HAL_INVALID_MODE_INDEX == mode_index)
    return SPM_INVALID_PARAM;

  mode = &handle->modes[mode_index];

  if (SPM_HAL_INVALID_SEQ_START_ADR == mode->start_addr)
    return SPM_INVALID_PARAM;

  ctl_val = mode->ctl_vals;
  ctl_val &= ~(SPM_HWIO_FMSK(SPM_CTL, EVENT_SYNC));
  ctl_val |= SPM_HWIO_FMSK(SPM_CTL, SLEEP_REQ);

  spm_hal_config_lpm_ctl(handle->addr, ctl_val);

  return SPM_SUCCESS;
}

/*
 * spm_mimic_low_power_mode
 */
spm_result_t spm_mimic_low_power_mode(spm_handle handle, uint8_t lpm)
{
  spm_hal_bsp_mode_t *mode;
  int32_t mode_index;
  uint32_t ctl_val;

  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_PARAM;

  mode_index = spm_mode_index(handle, lpm);

  if (SPM_HAL_INVALID_MODE_INDEX == mode_index)
    return SPM_INVALID_PARAM;

  mode = &handle->modes[mode_index];

  if (SPM_HAL_INVALID_SEQ_START_ADR == mode->start_addr)
    return SPM_INVALID_PARAM;

  /* set just the power state index */
  ctl_val = mode->ctl_vals;
  ctl_val &= SPM_HWIO_FMSK(SPM_CTL, PWR_STATE_IDX);

  spm_hal_config_lpm_ctl(handle->addr, ctl_val);

  return SPM_SUCCESS;
}

/*
 * spm_sleep_state
 */
spm_result_t spm_sleep_state(spm_handle handle, bool *sleep_state)
{
  if (!SPM_VALID_HANDLE(handle))
    return SPM_INVALID_PARAM;

  if (spm_hal_status3(handle->addr) & SPM_HWIO_FMSK(SPM_STS3, SLEEP_STATE))
    *sleep_state = true;
  else
    *sleep_state = false;

  return SPM_SUCCESS;
}


#endif /* SAW4 only functionality */
