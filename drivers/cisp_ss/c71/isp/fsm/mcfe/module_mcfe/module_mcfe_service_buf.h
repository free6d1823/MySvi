//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2019] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifndef __MODULE_MCFE_SERVICE_BUF_H__
#define __MODULE_MCFE_SERVICE_BUF_H__

#include "module_mcfe_service.h"

/**
 * @brief      Initializes the pool.
 *
 * @param[in]  type The buffer type.
 *
 */
void module_mcfe_buf_init_pool( const mcfe_hwif_buf_type_t type );

/**
 * @brief      Returns next free buffer in the pool.
 *
 * @param[in]  type The buffer type.
 *
 * @return     Pointer to free buffer or NULL if no free buffer is found. 
 *
 */
module_mcfe_buf_t *module_mcfe_buf_get_free( const mcfe_hwif_buf_type_t type );

/**
 * @brief      Counts number of free buffers in the pool
 *
 * @param[in]  type The buffer type.
 *
 * @return     Number of free buffers.
 *
 */
size_t module_mcfe_buf_get_free_count( const mcfe_hwif_buf_type_t type );

/**
 * @brief      Destroys HW buffer by resetting it registers to defaults
 *
 * @param[in]  buffer Pointer to a buffer.
 *
 */
void module_mcfe_buf_destroy( module_mcfe_buf_t *const buffer );

/**
 * @brief      Creates and configures HW buffer
 *
 * @param[in]  config Pointer to a buffer configuration.
 *
 * @return     Pointer to a created buffer.
 *
 */
module_mcfe_buf_t *module_mcfe_buf_create( module_mcfe_buf_cfg_t *const config );

#endif // __MODULE_MCFE_SERVICE_BUF_H__