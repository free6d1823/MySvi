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

#include "acamera_command_api_impl.h"
#include "system_types.h"
#include "acamera_calib_mgr.h"
#include "acamera_command_api.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"

#if FW_HAS_CONTROL_CHANNEL
#include "acamera_ctrl_channel.h"
#endif

extern void *get_active_ctx_ptr( void );

// ------------------------------------------------------------------------------ //
//		TSYSTEM
// ------------------------------------------------------------------------------ //


#ifdef SYSTEM_LOGGER_LEVEL
uint8_t system_logger_level( void *instance, uint32_t value, uint8_t direction, uint32_t *ret_value )
{

    /** @bug       calling LOG a lot from here will cause kernel panic. Unsure
     *             why. */

    *ret_value = 0;
    switch ( direction ) {
    case COMMAND_SET:
        alog_set_level( ( alog_level_t )( value ) );
        return SUCCESS;
    case COMMAND_GET:
        *ret_value = (uint32_t)alog_get_level();
        return SUCCESS;
    default:
        return NOT_IMPLEMENTED;
    }
}
#endif

#ifdef SYSTEM_LOGGER_MASK
uint8_t system_logger_mask( void *instance, uint32_t value, uint8_t direction, uint32_t *ret_value )
{

    *ret_value = 0;
    switch ( direction ) {
    case COMMAND_SET:
        alog_set_mask( (alog_mask_t)value );
        return SUCCESS;
    case COMMAND_GET:
        *ret_value = (uint32_t)alog_get_mask();
        return SUCCESS;
    default:
        return NOT_IMPLEMENTED;
    }
}
#endif

#ifdef BUFFER_DATA_TYPE
uint8_t acamera_calibration_update( acamera_isp_ctx_ptr_t p_ictx, uint32_t id, uint8_t direction, void *data, uint32_t data_size, uint32_t *ret_value )
{
    *ret_value = 0;

    if ( direction == COMMAND_GET ) {
        if ( data_size == calib_mgr_lut_read( p_ictx->calib_mgr_data, data, data_size, id ) ) {
            return SUCCESS;
        } else {
            *ret_value = ERR_BAD_ARGUMENT;
            return FAIL;
        }
    } else if ( direction == COMMAND_SET ) {
        if ( data_size == calib_mgr_lut_write( p_ictx->calib_mgr_data, data, data_size, id ) ) {
            return SUCCESS;
        } else {
            *ret_value = ERR_BAD_ARGUMENT;
            return FAIL;
        }
    } else {
        return NOT_SUPPORTED;
    }
}

uint32_t get_calibration_description( acamera_isp_ctx_ptr_t p_ictx, uint32_t id )
{
    uint32_t result = 0;

    if ( id < CALIBRATION_TOTAL_SIZE ) {
        // support only 1, 2 and 4 bytes format now.
        // it's enough 2 bits only for this data
        uint32_t width = ( calib_mgr_lut_width( p_ictx->calib_mgr_data, id ) > 0 ) ? ( calib_mgr_lut_width( p_ictx->calib_mgr_data, id ) - 1 ) : 0;
        uint32_t rows = calib_mgr_lut_rows( p_ictx->calib_mgr_data, id );
        uint32_t cols = calib_mgr_lut_cols( p_ictx->calib_mgr_data, id );
        // the description format is 2 bits for width
        // 15 bits for rows number and 15 bits for cols number
        result = ( width << 30 | ( rows << 15 ) | cols );
    } else {
        LOG( LOG_ERR, "Table pointer has invalid index %d. Maximum possible value is %d", (int)id, CALIBRATION_TOTAL_SIZE );
    }
    return result;
}

uint8_t buffer_data_type( void *instance, uint32_t value, uint8_t direction, uint32_t *ret_value )
{
    *ret_value = 0;

    acamera_isp_ctx_ptr_t p_ictx = (acamera_isp_ctx_ptr_t)instance;

    switch ( direction ) {
    case COMMAND_GET:
        *ret_value = get_calibration_description( p_ictx, value );
        return SUCCESS;
    default:
        return NOT_IMPLEMENTED;
    }
}
#endif // BUFFER_DATA_TYPE

uint8_t acamera_api_calibration( uint8_t type, uint8_t id, uint8_t direction, void *data, uint32_t data_size, uint32_t *ret_value )
{
#ifdef BUFFER_DATA_TYPE
    uint8_t result = SUCCESS;
    acamera_isp_ctx_ptr_t p_ictx = get_active_ctx_ptr();
    *ret_value = 0;

    if ( !p_ictx || ( ( direction != COMMAND_SET ) && ( direction != COMMAND_GET ) ) ) {
        *ret_value = ERR_BAD_ARGUMENT;
        return FAIL;
    }

    if ( id >= CALIBRATION_TOTAL_SIZE ) {
        LOG( LOG_ERR, "Trying to get an access with an invalid LUT index %d", id );
        return FAIL;
    }

    int16_t internal_lut_idx = id;
    if ( internal_lut_idx == -1 ) {
        LOG( LOG_ERR, "Trying to get an access with an invalid LUT index %d", internal_lut_idx );
        return FAIL;
    }

#if FW_HAS_CONTROL_CHANNEL
    ctrl_channel_handle_api_calibration( type, id, direction, data, data_size );
#endif

    // update an internal look-up table
    result = acamera_calibration_update( p_ictx, internal_lut_idx, direction, data, data_size, ret_value );

    if ( direction == COMMAND_SET ) {
        acamera_fsmgr_raise_event( &p_ictx->fsmgr, event_id_fsm_reload_calibration );
        result = SUCCESS;
    }

    return result;
#else
    return FAIL;
#endif // BUFFER_DATA_TYPE
}