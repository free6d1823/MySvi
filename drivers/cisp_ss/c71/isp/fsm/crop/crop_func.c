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

#include "acamera_isp_ctx.h"
#include "acamera_logger.h"

void crop_init( crop_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    // Initialise context param
    override_context_param( p_ictx, IMAGE_CROP_ENABLE_ID_PARAM, 0 );
    set_context_param( p_ictx, IMAGE_CROP_XOFFSET_ID_PARAM, 0 );
    set_context_param( p_ictx, IMAGE_CROP_YOFFSET_ID_PARAM, 0 );
    set_context_param( p_ictx, IMAGE_CROP_WIDTH_ID_PARAM, 0 );
    set_context_param( p_ictx, IMAGE_CROP_HEIGHT_ID_PARAM, 0 );
}

void crop_config( crop_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    acamera_cmd_sensor_info sensor_info;
    WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info );

    // Check input values
    uint32_t enable = get_context_param( p_ictx, IMAGE_CROP_ENABLE_ID_PARAM );
    const uint32_t xoffset = get_context_param( p_ictx, IMAGE_CROP_XOFFSET_ID_PARAM );
    const uint32_t yoffset = get_context_param( p_ictx, IMAGE_CROP_YOFFSET_ID_PARAM );
    const uint32_t width = get_context_param( p_ictx, IMAGE_CROP_WIDTH_ID_PARAM );
    const uint32_t height = get_context_param( p_ictx, IMAGE_CROP_HEIGHT_ID_PARAM );
    const uint32_t xsize = xoffset + width;
    const uint32_t ysize = yoffset + height;


    if ( enable ) {
        if ( ( xsize == 0 ) ||
             ( ysize == 0 ) ||
             ( xsize > sensor_info.active_width ) ||
             ( ysize > sensor_info.active_height ) ) {
            LOG( LOG_ERR, "Invalid crop configuration, size: (%ux%u), offset:%u,%u, sensor: (%ux%u)",
                 width,
                 height,
                 xoffset,
                 yoffset,
                 sensor_info.active_width,
                 sensor_info.active_height );
            enable = 0;
            set_context_param( p_ictx, IMAGE_CROP_ENABLE_ID_PARAM, 0 );
        }
    }

    // Configure crop FSM hw module
    if ( enable ) {
        acamera_isp_fr_crop_start_x_write( p_ictx->settings.isp_base, xoffset );
        acamera_isp_fr_crop_start_y_write( p_ictx->settings.isp_base, yoffset );
        acamera_isp_fr_crop_size_x_write( p_ictx->settings.isp_base, width );
        acamera_isp_fr_crop_size_y_write( p_ictx->settings.isp_base, height );
        acamera_isp_fr_crop_enable_crop_write( p_ictx->settings.isp_base, 1 );
        acamera_isp_pipeline_bypass_crop_write( p_ictx->settings.isp_base, 0 );
    } else {
        acamera_isp_fr_crop_enable_crop_write( p_ictx->settings.isp_base, 0 );
        acamera_isp_pipeline_bypass_crop_write( p_ictx->settings.isp_base, 1 );
    }
}

void crop_deinit( crop_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    acamera_isp_fr_crop_enable_crop_write( p_ictx->settings.isp_base, 0 );
    acamera_isp_pipeline_bypass_crop_write( p_ictx->settings.isp_base, 1 );
}