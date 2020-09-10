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

#include "isp_params.h"
#include "acamera_command_api.h"
#include "acamera_configuration.h"
#include "revision.h"

// External parameter handler functions declaration
extern uint8_t system_logger_level( void *instance, uint32_t value, uint8_t direction, uint32_t *ret_value );
extern uint8_t system_logger_mask( void *instance, uint32_t value, uint8_t direction, uint32_t *ret_value );


// SYSTEM_LOGGER_LEVEL_PARAM values list
static param_list_value system_logger_level_param_values_list[] = {
    // List size
    {9, 0x0},
    {SYSTEM_LOGGER_DEBUG, 0x0},
    {SYSTEM_LOGGER_INFO, 0x0},
    {SYSTEM_LOGGER_NOTICE, 0x0},
    {SYSTEM_LOGGER_WARNING, 0x0},
    {SYSTEM_LOGGER_ERROR, 0x0},
    {SYSTEM_LOGGER_CRITICAL, 0x0},
    {SYSTEM_LOGGER_ALERT, 0x0},
    {SYSTEM_LOGGER_EMERG, 0x0},
    {SYSTEM_LOGGER_NOTHING, 0x0}};

// Initialize isp parameters with default values
void init_isp_params( isp_params *params )
{
    if ( params == NULL ) {
        return;
    }

    // ACTIVE_CONTEXT_PARAM
    params->params[0].value = 0x00000000;
    params->params[0].default_value = 0x00000000;
    params->params[0].min = 0;
    params->params[0].max = FIRMWARE_CONTEXT_NUMBER - 1;
    params->params[0].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[0].values_list = NULL;
    params->params[0].param_handler = NULL;

    // CONTEXT_NUMBER_PARAM
    params->params[1].value = FIRMWARE_CONTEXT_NUMBER;
    params->params[1].default_value = FIRMWARE_CONTEXT_NUMBER;
    params->params[1].min = 0;
    params->params[1].max = FIRMWARE_CONTEXT_NUMBER;
    params->params[1].flags = ( PARAM_FLAG_READ );
    params->params[1].values_list = NULL;
    params->params[1].param_handler = NULL;

    // FW_REVISION_PARAM
    params->params[2].value = FIRMWARE_REVISION;
    params->params[2].default_value = FIRMWARE_REVISION;
    params->params[2].min = 0x00000000;
    params->params[2].max = 0xFFFFFFFF;
    params->params[2].flags = ( PARAM_FLAG_READ );
    params->params[2].values_list = NULL;
    params->params[2].param_handler = NULL;

    // SYSTEM_LOGGER_LEVEL_PARAM
    params->params[3].value = 0x00000000;
    params->params[3].default_value = 0x00000000;
    params->params[3].min = 0x00000000;
    params->params[3].max = 0xFFFFFFFF;
    params->params[3].flags = ( PARAM_FLAG_HANDLER_FUNCTION | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[3].values_list = system_logger_level_param_values_list;
    params->params[3].param_handler = system_logger_level;

    // SYSTEM_LOGGER_MASK_PARAM
    params->params[4].value = 0x00000000;
    params->params[4].default_value = 0x00000000;
    params->params[4].min = 0x00000000;
    params->params[4].max = 0xFFFFFFFF;
    params->params[4].flags = ( PARAM_FLAG_HANDLER_FUNCTION | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[4].values_list = NULL;
    params->params[4].param_handler = system_logger_mask;
}
