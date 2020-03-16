#ifndef _SPM_INTERNAL_H_
#define _SPM_INTERNAL_H_

/*==============================================================================
  FILE:         spm_internal.h

  OVERVIEW:     This file provides prototypes for internal or utility functions
                for SPM driver.

  DEPENDENCIES: Functions declared in this file may require proper initialization
                before and are not expected to be called directly outside of SPM
                module.

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================*/

#include "spm.h"

/*=======================================================================
 *                           SPM INTERNAL MACROS
 *======================================================================*/

/**
 * @brief Macro to check SPM handle validity. It ensures that the SPM
 *        handle and its 'addr' field are not NULL. Usually 'addr' field
 *        points to SPM instance's address in memory map so it would be
 *        non NULL on successful SPM handle initialization.
 */
#define SPM_VALID_HANDLE(h) (NULL != (h) && NULL != (h)->addr)

/*=======================================================================
 *                           SPM INERNAL FUNCTIONS
 *======================================================================*/

/**
 * @brief Target specific initialization. This function must be called
 *        as part of spm common driver initialization.
 */
void spm_target_init(void);

/**
 * @brief Sets up various SPM instance attributes.
 *
 * @note This function does not validate input handle as it is an internal
 *       function and needs to be called only with valid handle.
 *
 * @param handle: Handle to SPM that is being set up.
 */
void spm_internal_config(spm_handle handle);

/**
 * @brief Copied given SPM's command sequences to actual HW.
 *
 * @param handle: Handle to SPM for which command sequences are copied.
 *
 * @return SPM error code (@see spm_result_t)
 */
spm_result_t spm_copy_cmd_seqs(spm_handle handle);

/**
 * @brief Returns the index of the input mode for a given SPM instance.
 *
 * @param handle: Handle to SPM.
 * @param lpm: Mode id for which we want to find index.
 *
 * @return If mode is found on input SPM, its index else -1.
 */
int32_t spm_mode_index(spm_handle handle, uint8_t lpm);

#endif
