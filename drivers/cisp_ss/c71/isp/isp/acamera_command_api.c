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

#include "acamera_command_api.h"
#include "acamera.h"
#include "acamera_command_api_impl.h"
#include "acamera_isp_ctx.h"
#include "command_id_to_params.h"

#if FW_HAS_CONTROL_CHANNEL
#include "acamera_ctrl_channel.h"
#endif

uint8_t acamera_command( uint8_t command_type, uint8_t command, uint32_t value, uint8_t direction, uint32_t *ret_value )
{
    uint8_t ret = NOT_EXISTS;

    switch ( command_type ) {

    case TSELFTEST:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;

    case TGENERAL:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;

    case TSENSOR:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;

    case TSYSTEM:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;

    case TIMAGE:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;

    case TALGORITHMS:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;

    case TREGISTERS:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;

    case TSTATUS:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;

    case TISP_MODULES:
        ret = acamera_handle_param( command_id_to_param_id( command ), direction, value, ret_value );
        break;
    } //switch (command_type)

#if FW_HAS_CONTROL_CHANNEL
    ctrl_channel_handle_command( command_type, command, value, direction );
#endif

    if ( ret != SUCCESS ) {
        LOG( LOG_WARNING, "API COMMAND FAILED: type %d, cmd %d, value %lu, direction %d, ret_value %lu, result %d", command_type, command, (unsigned long)value, direction, (unsigned long)*ret_value, ret );
    } else {
        LOG( LOG_DEBUG, "API type %d, cmd %d, value %lu, direction %d, ret_value %lu, result %d", command_type, command, (unsigned long)value, direction, (unsigned long)*ret_value, ret );
    }

    return ret;
}
