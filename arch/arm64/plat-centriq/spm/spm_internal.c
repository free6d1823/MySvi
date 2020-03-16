/*==============================================================================
  FILE:         spm_internal.c

  OVERVIEW:     This file provides implementation of functions that usually are
                internal to SPM driver (in terms of functionality or data
                access).

  DEPENDENCIES: None

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================*/

#include <string.h>
#include <asm/mach/spm/spm.h>
#include <asm/mach/spm/spm_internal.h>
#include <asm/mach/spm/spm_hal.h>
#include <asm/mach/spm/spm_hal_bsp.h>


/*=======================================================================
 *                           GLOBAL FUNCTIONS
 *======================================================================*/

/*
 * spm_internal_config
 *
 * @note - This needs somewhat more refactoring to decouple BSP structures.
 */
void spm_internal_config(spm_handle handle)
{
  uint32_t i;
  uint8_t* addr = handle->addr;
  spm_hal_bsp_cfg_t *cfg = handle->cfg;
  spm_hal_bsp_clk_cfg_t *clk_cfg = &cfg->clk_cfg;
  spm_hal_bsp_ctl_cfg_t *ctl_cfg = &cfg->ctl_cfg;
  spm_hal_bsp_delay_cfg_t *delay_cfg = &cfg->delay_cfg;
  spm_hal_bsp_pmic_cfg_t *pmic_cfg = NULL;
  spm_hal_bsp_mode_t *mode = NULL;

  spm_hal_config_clk_div(addr, clk_cfg->clk_div);

  spm_hal_config_isar(addr, ctl_cfg->isar);
  spm_hal_config_wakeup(addr, ctl_cfg->wakeup);

  spm_hal_config_delays(addr, delay_cfg->delay1,
                        delay_cfg->delay2, delay_cfg->delay3);

  for (i = 0; i < cfg->pmic_cfg_count; i++)
  {
    pmic_cfg = &cfg->pmic_cfg[i];

    spm_hal_config_pmic(addr, pmic_cfg->mode, pmic_cfg->index,
                        pmic_cfg->data, pmic_cfg->size, pmic_cfg->delay);
  }

  /* Some basic set up for sanity. */
  spm_hal_invalidate_cmd_seqs(handle->addr);
  for (i = 0; i < handle->mode_count; i++)
  {
    mode = &handle->modes[i];
    mode->start_addr = SPM_HAL_INVALID_SEQ_START_ADR;
  }
  handle->copied_cmds = 0;
}

/*
 * spm_copy_cmd_seqs
 */
spm_result_t spm_copy_cmd_seqs(spm_handle handle)
{
  uint32_t i = 0, j = 0;
  spm_result_t result = SPM_SUCCESS;
  uint8_t* spm_base = handle->addr;
  spm_hal_bsp_mode_t *curr_mode = NULL;
  const spm_hal_bsp_mode_t *ref_mode = NULL;
  uint32_t copied_cmds = 0;

  for (i = 0; i < handle->mode_count; i++)
  {
    curr_mode = &handle->modes[i];

    if (0 == curr_mode->length)
    {
      result = SPM_INVALID_PARAM;
      break;
    }

    /* Check if the mode points to already programmed sequence */
    for (j = 0; j < i; j++)
    {
      ref_mode = &handle->modes[j];
      if ((ref_mode->cmds == curr_mode->cmds) &&
         (SPM_HAL_INVALID_SEQ_START_ADR != ref_mode->start_addr))
        break;
    }

    if (j == i)
    {
      /* Mode's sequence is not programmed yet */
      copied_cmds = spm_hal_copy_cmd_seq(spm_base, handle->copied_cmds,
                                         curr_mode->cmds, curr_mode->length);

      if (0 == copied_cmds)
      {
        result = SPM_NO_SEQ_MEMORY;
        break;
      }

      curr_mode->start_addr = handle->copied_cmds;
      handle->copied_cmds += copied_cmds;
    }
    else
    {
      curr_mode->start_addr = ref_mode->start_addr;
    }

    curr_mode->ctl_vals |= SPM_HAL_START_ADR_SET(curr_mode->start_addr);
  }

  return result;
}

/*
 * spm_mode_index
 */
int32_t spm_mode_index(spm_handle handle, uint8_t lpm)
{
  uint32_t i = 0;
  spm_hal_bsp_mode_t *mode;

  for (i = 0; i < handle->mode_count; i++)
  {
    mode = &handle->modes[i];
    if (mode->mode_id == lpm)
      return i;
  }

  return SPM_HAL_INVALID_MODE_INDEX;
}
