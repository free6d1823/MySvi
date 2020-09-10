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

#ifndef __ACAMERA_H__
#define __ACAMERA_H__

#include "system_semaphore.h"
#include "system_types.h"
#include "acamera_logger.h"
#include "acamera_settings.h"
#include "isp_params.h"


////////////////////////////////////////////////////
// isp api functions

/**
 * @brief      Initialize ISP instance.
 *
 * @details    The firmware can control several context at the same time. Each
 *             context must be initialized with its own set of setting and
 *             independently from all other contexts. A pointer will be returned
 *             on valid context on successful initialization.
 */
int32_t acamera_init( acamera_settings *settings, uint8_t num_of_contexts, semaphore_t sem );


/**
 * @brief      Terminate the firmware.
 *
 * @details    The function will close the firmware and free all previously
 *             allocated resources.
 */
int32_t acamera_deinit( void );


/**
 * @brief      Raise config event for given context.
 */
void acamera_config_ctx( uint8_t ctx_id );


/**
 * @brief      Raise config event for given context.
 */
void acamera_start_ctx( uint8_t ctx_id );


/**
 * @brief      Raise config event for given context.
 */
void acamera_stop_ctx( uint8_t ctx_id );


/**
 * @brief      Raise config event for given context.
 */
void acamera_deinit_ctx( uint8_t ctx_id );


/**
 * @brief      acamera ISP interrupt handler
 *
 * @details    Ideally #acamera_isp_ctx_process_interrupt should take a mask rather than
 *             IRQ number and handle all events for given slot.
 */
void acamera_process_interrupt( uint8_t slot, const uint32_t mask );


/**
 * @brief      acamera ISP event handler.
 *
 *
 * @details    The firmware can control several context at the same time. Each
 *             context must be given a CPU time to fulfil all tasks it has at
 *             the moment. This function has to be called for all contexts as
 *             frequent as possible to avoid delays.
 */
int32_t acamera_process_event( void );

////////////////////////////////////////////////////
// ISP param handlers

uint32_t get_isp_param( uint32_t param_id );

void set_isp_param( uint32_t param_id, uint32_t value );

void override_isp_param( uint32_t param_id, uint32_t value );

uint8_t acamera_handle_param( uint32_t param_id, uint8_t direction, uint32_t set_value, uint32_t *get_value );


#endif // __ACAMERA_H__
