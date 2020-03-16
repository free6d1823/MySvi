#ifndef _SPM_H_
#define _SPM_H_

/*==============================================================================
Copyright (c) 2016 Qualcomm Datacenter Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

Copyright (c) 2009-2016 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================

  FILE:         spm.h

  OVERVIEW:     This file contains APIs for external modules to interact with
                SPM HW block(s).

  DEPENDENCIES: None

==============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <asm/hal/HALcomdef.h>
#include "spm_target.h"

/*=======================================================================
 *                           TYPE DEFINITIONS
 *======================================================================*/

/**
 * @brief Forward declaration of SPM configuration structure. This struct's
 *        definition could be version specific.
 */
struct spm_hal_bsp_cfg_s;

/**
 * @brief Forward declaration of SPM low power mode structure. Its definition
 *        could be SPM version specific.
 */
struct spm_hal_bsp_mode_s;

/**
 * @brief Structure containing information about a specific SPM instance.
 *
 * This can be moved to internal header file eventually. In general, each
 * target will have one or more instances of this structure in target
 * specific file(s).
 */
typedef struct spm_s
{
  struct spm_hal_bsp_cfg_s* cfg;     /* Init time config */
  struct spm_hal_bsp_mode_s* modes;  /* List of modes for this SPM */
  uint32_t mode_count;                 /* Number of mode in above list */

  /* Internal fields */
  uint8_t *addr;                       /* Instance address in memory map */
  uint32_t copied_cmds;                /* Number of commands copied on this SPM
                                      * instance - may be convert in to generic
                                      * internal structure. */
} spm_t;

typedef struct spm_s* spm_handle;

/**
 * @brief Return value enumeration for different SPM APIs.
 */
typedef enum
{
  SPM_SUCCESS = 0,
  SPM_INVALID_HANDLE = 1,
  SPM_INVALID_PARAM = 2,
  SPM_NO_SEQ_MEMORY = 3,
  SPM_ERROR = -1
} spm_result_t;

/*=======================================================================
 *                           GLOBAL FUNCTIONS
 *======================================================================*/

/**
 * @brief Performs initialization of common SPM driver (SPM instance agnostic
 *        initialization).
 *
 * @note This function must be called before calling any other SPM function.
 */
void spm_driver_init(void);

/**
 * @brief Returns the SPM handle associated with requested SPM.
 *
 * @dependency spm_driver_init
 *
 * @param type: Target specific type of SPM requested.
 * @param index: Index of the requested SPM type.
 *
 * @return Handle to the requested SPM on success, NULL on failure.
 */
spm_handle spm_get_handle(spm_type_t type, uint32_t index);

/**
 * @brief Performs SPM instance specific initialization.
 *
 * @note This function must be called on an instance before calling any
 *       other functions that take SPM handle as one of the parameters.
 *
 * @dependency spm_driver_init
 *
 * @param handle: Handle to SPM that is going to be initialized.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_init(spm_handle handle);

/**
 * @brief Flush data for the specified SPM instance.
 *
 * @param handle: Handle to SPM that is going to be initialized.
 */
void spm_cache_flush(spm_handle handle);

/**
 * @brief Sets a low power mode in SPM. The configured low power mode
 *        settings will take place next time SPM state machine kicks
 *        in.
 *
 * @dependency spm_init
 *
 * @param handle: Handle to desired SPM instance.
 * @param lpm: Low power mode id (typically corresponds to the ones defined
 *              in subsystem HPG).
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_set_low_power_mode(spm_handle handle, uint8_t lpm);

/**
 * @brief Returns the index of low power mode the input SPM is currently
 *        executing.
 *
 * @dependency spm_init
 *
 * @param handle: Handle to desired SPM instance.
 * @param mode_id: Low power mode id (negative value if SPM is not executing
 *                 any low power mode currently).
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_executing_low_power_mode(spm_handle handle, int16_t *mode_id);

/**
 * @brief Returns whether the input SPM last executed the requested mode.
 *
 * @dependency spm_init
 *
 * @param handle: Handle to desired SPM instance.
 * @param lpm: Low power mode to check for.
 * @param executed: TRUE if mode was the last executed by SPM instance,
 *                  FALSE otherwise.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_executed_low_power_mode(spm_handle handle, uint8_t lpm,
                                         bool *executed);

/**
 * @brief Sets SPM to perform or skip RPM handshake when command sequence
 *        triggers next time.
 *
 * @dependency spm_init
 *
 * @param handle: Handle to desired SPM instance.
 * @param handshake: Value to indicate whether to perform handshake or skip it
 *                   (TRUE - Perform RPM handshake, FALSE - skip it).
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_set_rpm_handshake(spm_handle handle, bool handshake);

/**
 * @brief Enables or disables SPM.
 *
 * @dependency spm_init
 *
 * @param handle: Handle to desired SPM instance.
 * @param enable: If TRUE, enables the SPM. If FALSE, disables SPM.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_enable(spm_handle handle, bool enable);

/**
 * @brief Wakeup a sleeping SPM.
 *
 * @dependency spm_init
 *
 * @param handle: Handle to desired SPM instance.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_wakeup(spm_handle handle);

/**
 * @brief Returns the busy state of SPM.
 *
 * @dependency spm_init
 *
 * @param handle: Handle to desired SPM instance.
 * @param sleep_state: TRUE if SPM is busy,
 *                     FALSE otherwise.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_busy(spm_handle handle, bool *busy);

/**
 * @brief Sets a low power mode in SPM and starts executing the sequence.
 *
 * @dependency spm_init, HALv4
 *
 * @param handle: Handle to desired SPM instance.
 * @param lpm: Low power mode id (typically corresponds to the ones defined
 *              in subsystem HPG).
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_start_low_power_mode(spm_handle handle, uint8_t lpm);

/**
 * @brief Configure SPM to mimic entry to a low power mode.
 *
 * This is required for a controlled entity which is masked out via
 * Partial Goods. The SPM is configured such that it appears to be in
 * the specified low power mode from an external subsystem's perspective.
 *
 * @dependency spm_init, HALv4
 *
 * @param handle: Handle to desired SPM instance.
 * @param lpm: Low power mode id (typically corresponds to the ones defined
 *              in subsystem HPG).
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_mimic_low_power_mode(spm_handle handle, uint8_t lpm);

/**
 * @brief Returns the sleep state of SPM.
 *
 * @dependency spm_init, HALv4
 *
 * @param handle: Handle to desired SPM instance.
 * @param sleep_state: TRUE if SPM is sleeping,
 *                     FALSE otherwise.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_sleep_state(spm_handle handle, bool *sleep_state);

#ifdef __cplusplus
}
#endif

#endif
