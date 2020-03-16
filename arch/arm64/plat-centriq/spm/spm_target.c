/*==============================================================================
  FILE:         spm_target.c

  OVERVIEW:     This file implements any target specific functions for SPM.

  DEPENDENCIES: None

  NOTES:        This needs to be refactored once full DeviceCfg (or equivalent)
                support is present.

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================*/

#include <asm/mach/spm/spm.h>
#include <asm/mach/spm/spm_hal_bsp.h>
#include <asm/mach/spm/spm_hal_hwio.h>
#include <asm/mach/spm/spm_internal.h>
#include <asm/mach/platform_def.h>
#include <asm/mach/hal/msmhwiobase.h>

/*=======================================================================
 *                                 MACROS
 *======================================================================*/

/* used to find reg base of each rail */
#define APCS_RAIL_BASE_OFFS           0x8000

/* offsets from the rail reg base to the respective SPM block */
#define APCS_L2_SPM_OFFS              0x4000
#define APCS_RAIL_SPM_OFFS            0x6000

/* offset between SPM instances of the same type within a block */
#define APCS_SPM_INSTANCE_OFFS        0x800

/* top level SPM register base addresses */
#define APCS_RAIL_SPM_REG_BASE(idx)   ((HMSS_PERIPH_BASE) + \
                                       ((idx) * APCS_RAIL_BASE_OFFS) + \
                                       (APCS_RAIL_SPM_OFFS))

#define APCS_L2_SPM_REG_BASE(idx)     ((HMSS_PERIPH_BASE) + \
                                       (CLU_TO_RAIL_IDX(idx) * APCS_RAIL_BASE_OFFS) + \
                                       (APCS_L2_SPM_OFFS) + \
                                       (CLU_ON_RAIL_IDX(idx) * APCS_SPM_INSTANCE_OFFS))

#define APCS_CPU_SPM_REG_BASE(idx)    ((HMSS_PERIPH_BASE) + \
                                       (CPU_TO_RAIL_IDX(idx) * APCS_RAIL_BASE_OFFS) + \
                                       (CPU_ON_RAIL_IDX(idx) * APCS_SPM_INSTANCE_OFFS))


#define INIT_SPM_INSTANCE(idx, pconfig, pmodes, mode_cnt, base) \
            do {                                                \
              g_spms[(idx)].cfg = (pconfig);                    \
              g_spms[(idx)].modes = (pmodes);                   \
              g_spms[(idx)].mode_count = (mode_cnt);            \
              g_spms[(idx)].addr = (uint8_t *)(base);             \
              g_spms[(idx)].copied_cmds = 0;                    \
            } while (0)

/*=======================================================================
 *                             GLOBAL VARIABLES
 *======================================================================*/

/**
 * @brief CPU SPM configuration data.
 */
extern spm_hal_bsp_cfg_t g_cpu_spm_cfg;
extern spm_hal_bsp_mode_t g_cpu_modes[];
extern size_t g_cpu_mode_count;

/**
 * @brief L2 SPM configuration data.
 */
extern spm_hal_bsp_cfg_t g_l2_spm_cfg;
extern spm_hal_bsp_mode_t g_l2_modes[];
extern size_t g_l2_mode_count;

/**
 * @brief APR SPM configuration data.
 */
extern spm_hal_bsp_cfg_t g_apr_spm_cfg;
extern spm_hal_bsp_mode_t g_apr_modes[];
extern size_t g_apr_mode_count;

/**
 * @brief Array containing SPM instances for all subsystems.
 */
static spm_t g_spms[PLATFORM_CORE_COUNT +
                    PLATFORM_CLUSTER_COUNT +
                    PLATFORM_RAIL_COUNT];

/*=======================================================================
 *                             GLOBAL FUNCTIONS
 *======================================================================*/

/*
 * spm_target_init
 */
void spm_target_init(void)
{
  int i, cc = 0;

  /* initialize CPU SPM instances */
  for (i = 0; i < PLATFORM_CORE_COUNT; i++)
  {
    INIT_SPM_INSTANCE(i, &g_cpu_spm_cfg, \
        g_cpu_modes, g_cpu_mode_count, \
        APCS_CPU_SPM_REG_BASE(i));
  }
  cc = i;

  /* initialize L2 SPM instances */
  for (i = 0; i < PLATFORM_CLUSTER_COUNT; i++)
  {
    INIT_SPM_INSTANCE(cc + i, &g_l2_spm_cfg, \
        g_l2_modes, g_l2_mode_count, \
        APCS_L2_SPM_REG_BASE(i));
  }
  cc += i;

  /* initialize APR SPM instances */
  for (i = 0; i < PLATFORM_RAIL_COUNT; i++)
  {
    INIT_SPM_INSTANCE(cc + i, &g_apr_spm_cfg, \
        g_apr_modes, g_apr_mode_count, \
        APCS_RAIL_SPM_REG_BASE(i));
  }
  //assert((cc + i) == ARRAY_SIZE(g_spms));
}


/*
 * spm_get_handle
 */
spm_handle spm_get_handle(spm_type_t type, uint32_t index)
{
  switch (type)
  {
    case SPM_TYPE_CPU:
      if (index < PLATFORM_CORE_COUNT)
        return &g_spms[index];
      break;

    case SPM_TYPE_L2:
      if (index < PLATFORM_CLUSTER_COUNT)
        return &g_spms[PLATFORM_CORE_COUNT + index];
      break;

    case SPM_TYPE_APR:
      if (index < PLATFORM_RAIL_COUNT)
        return &g_spms[PLATFORM_CORE_COUNT + PLATFORM_CLUSTER_COUNT + index];
      break;

    default:
      break;
  }

  return NULL;
}


#if 0
/*
 * spm_flush_data
 */
void spm_cache_flush(spm_handle handle)
{
  flush_dcache_range((uint64_t)handle, sizeof(spm_t));
  flush_dcache_range((uint64_t)handle->modes,
      (sizeof(spm_hal_bsp_mode_t) * handle->mode_count));
}
#endif

