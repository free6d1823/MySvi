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

#include "system_timer.h"
#include "system_types.h"
#include "acamera_command_api.h"
#include "acamera_frame_stream_api.h"
#include "acamera_frontend_config.h"
#include "acamera_isp_config.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "acamera_math.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_SENSOR

#define OFFSET_BLACK_DEFAULT 0xF0000

// Remote sensor stream functions

static void remote_sensor_frame_stream_deinit( uint32_t contex_id, int force )
{
    if ( frame_stream_destroy( contex_id, AFRAME_TYPE_RAW, force ) ) {
        LOG( LOG_ERR, "Failed to destroy raw frame stream." );
    }
}

static int remote_sensor_frame_stream_init( uint32_t contex_id, const sensor_param_t *sensor_config )
{
	LOG( LOG_DEBUG, "%s E", __FUNCTION__);
    frame_stream_cfg_t frame_stream_cfg = {0};
    size_t i;

    // Raw frame stream config header
    frame_stream_cfg.num_planes = sensor_config->num_channel;
    frame_stream_cfg.context_id = contex_id;
    frame_stream_cfg.type = AFRAME_TYPE_RAW;
    frame_stream_cfg.num_frames = 4;

    // Allocate raw-buffers.
    for ( i = 0; i < frame_stream_cfg.num_planes; i++ ) {

        frame_stream_plane_cfg_t *plane_cfg = &( frame_stream_cfg.planes[i] );

        plane_cfg->hw_cfg.flags = AFRAME_HW_FLAG_MSB_ALIGN;
        plane_cfg->data_width = sensor_config->data_width;
        plane_cfg->width = sensor_config->active.width;
        plane_cfg->height = sensor_config->active.height;
        plane_cfg->line_offset = AFRAME_ALIGN_PLANE( plane_cfg->width * plane_cfg->data_width / 8 );

		LOG(LOG_NOTICE, "raw buffer: data_width=0x%2x, width=0x%2x, height=0x%2x, line_offset=0x%2x,flags=0x%2x",
				plane_cfg->data_width, plane_cfg->width, plane_cfg->height, plane_cfg->line_offset, plane_cfg->hw_cfg.flags);
    }

    if ( frame_stream_create( &frame_stream_cfg ) != 0 ) {
        LOG( LOG_ERR, "Error, failed to create raw frame stream." );
        return -1;
    }

	LOG( LOG_DEBUG, "%s X", __FUNCTION__);
    return 0;
}

////////////////////////////////////////////////////
// FSM event handler

void sensor_init( sensor_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint32_t ctx_id = p_ictx->context_id;

    LOG( LOG_INFO, "%s ctx %u E", __FUNCTION__, ctx_id );

    // Init sensor hardware
    p_ictx->settings.sensor_init( &p_fsm->drv_priv, ctx_id, &p_fsm->ctrl, &p_ictx->settings.sensor_options );

    // Get sensor parameters
    const sensor_param_t *s_param = p_fsm->ctrl.get_parameters( p_fsm->drv_priv );

    // Set default preset mode
    override_context_param( p_ictx, SENSOR_PRESET_PARAM, p_ictx->settings.sensor_options.preset_mode );
#if 1
    /* @todo check if this value can be hardcoded or should we add it to
    calibration. Testing locally I haven't really observed a big difference. */
    acamera_isp_offset_black_00_write( p_ictx->settings.isp_base, OFFSET_BLACK_DEFAULT );
    acamera_isp_offset_black_01_write( p_ictx->settings.isp_base, OFFSET_BLACK_DEFAULT );
    acamera_isp_offset_black_10_write( p_ictx->settings.isp_base, OFFSET_BLACK_DEFAULT );
    acamera_isp_offset_black_11_write( p_ictx->settings.isp_base, OFFSET_BLACK_DEFAULT );

    acamera_isp_pipeline_bypass_sensor_offset_wdr_write( p_ictx->settings.isp_base, 0 );
    acamera_isp_pipeline_bypass_sensor_offset_linear_write( p_ictx->settings.isp_base, 0 );
#endif
    // Initialise remote sensor callbacks
    if ( s_param->is_remote ) {
		//LOG( LOG_INFO, "sensor is remote.\n");
        if ( p_fsm->ctrl.register_frame_callbacks ) {

            const sensor_remote_callbacks_t callbacks = {
                .callback_owner = p_fsm,
                .get_frame = remote_sensor_get_frame_callback_handler,
                .put_frame = remote_sensor_put_frame_callback_handler,
                .release_frame = remote_sensor_release_frame_callback_handler};

            p_fsm->ctrl.register_frame_callbacks( p_fsm->drv_priv, &callbacks );
        } else {
            LOG( LOG_ERR, "Error. Sensor API 'register_frame_callbacks' is not initialized (NULL).\n" );
        }
    }
    LOG( LOG_INFO, "%s ctx %u X", __FUNCTION__, ctx_id );
}

void sensor_config( sensor_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    LOG( LOG_INFO, "%s ctx %d E", __FUNCTION__, p_ictx->context_id );

    // Get sensor parameters.
    const sensor_param_t *s_param = p_fsm->ctrl.get_parameters( p_fsm->drv_priv );

    // Get preset mode and do range check.
    uint32_t preset_mode = get_context_param( p_ictx, SENSOR_PRESET_PARAM );

    // Check preset mode
    if ( preset_mode >= s_param->modes_num ) {
        if ( s_param->modes_num > 0 ) {
            preset_mode = s_param->modes_num - 1;
        } else {
            preset_mode = 0;
        }

        override_context_param( p_ictx, SENSOR_PRESET_PARAM, preset_mode );
    }

    // Check if required number of input ports available (not needed for remote sensors)
    //if ( !s_param->is_remote ) {

    //    int available_inputs = 0;
    //    WRAP_GENERAL_CMD( p_ictx, CMD_ID_MCFE_GET_SLOT_AVAIL_INPUTS, CMD_DIRECTION_GET, NULL, &available_inputs );

    //    if ( s_param->modes_table[preset_mode].num_channels > available_inputs ) {
    //        LOG( LOG_ERR, "Failed to set new sensor preset %d. Not enough free input ports available (required: %d, available: %d).",
    //             preset_mode,
    //             s_param->modes_table[preset_mode].num_channels,
    //             available_inputs );
    //        LOG( LOG_ERR, "Sensor preset is set back to: %d.", s_param->preset_mode );

    //        // Reset sensor preset param to current valid preset
    //        override_context_param( p_ictx, SENSOR_PRESET_PARAM, s_param->preset_mode );

    //        return;
    //    }
    //}

    // Update flag so remote sensor can reconfigure frames streams
    // Flag must be set before calling set_mode because set_mode will trigger remote
    // sensor callback get_frame which rely on it
    if ( s_param->is_remote ) {
        p_fsm->is_remote_stream_reconfig_req = 1;
    }

    // Update sensor hardware with given preset mode.
    p_fsm->ctrl.set_mode( p_fsm->drv_priv, preset_mode );

    // Set WDR mode context parameter.
    override_context_param( p_ictx, SENSOR_WDR_MODE_PARAM, s_param->modes_table[preset_mode].wdr_mode );

    // Update general_sensor_info.
    p_fsm->general_sensor_info.total_width = s_param->total.width;
    p_fsm->general_sensor_info.total_height = s_param->total.height;
    p_fsm->general_sensor_info.active_width = s_param->active.width;
    p_fsm->general_sensor_info.active_height = s_param->active.height;
    p_fsm->general_sensor_info.black_level = p_fsm->black_level;
    p_fsm->general_sensor_info.lines_per_second = s_param->lines_per_second;
    p_fsm->general_sensor_info.cfa_pattern = s_param->cfa_pattern;

    p_fsm->general_sensor_info.again_log2_max = s_param->again_log2_max;
    p_fsm->general_sensor_info.dgain_log2_max = s_param->dgain_log2_max;
    p_fsm->general_sensor_info.again_accuracy = s_param->again_accuracy;
    p_fsm->general_sensor_info.wb_gain_log2_max = s_param->wb_gain_log2_max;

    p_fsm->general_sensor_info.integration_time_min = s_param->integration_time_min;
    p_fsm->general_sensor_info.integration_time_max = s_param->integration_time_max;
    p_fsm->general_sensor_info.integration_time_long_max = s_param->integration_time_long_max;
    p_fsm->general_sensor_info.integration_time_medium_max = s_param->integration_time_medium_max;
    p_fsm->general_sensor_info.integration_time_limit = s_param->integration_time_limit;
    p_fsm->general_sensor_info.integration_time_precision = s_param->integration_time_precision;
    p_fsm->general_sensor_info.integration_time_apply_delay = s_param->integration_time_apply_delay;

    p_fsm->general_sensor_info.sensor_exp_number = s_param->sensor_exp_number;
    p_fsm->general_sensor_info.isp_exposure_channel_delay = s_param->isp_exposure_channel_delay;
    p_fsm->general_sensor_info.sensor_output_bits = s_param->data_width;

    p_fsm->general_sensor_info.is_remote = s_param->is_remote;

    // Update context parameters.
    override_context_param( p_ictx, SENSOR_HEIGHT_PARAM, s_param->modes_table[preset_mode].resolution.height );
    override_context_param( p_ictx, SENSOR_WIDTH_PARAM, s_param->modes_table[preset_mode].resolution.width );
    override_context_param( p_ictx, SENSOR_FPS_PARAM, ( s_param->lines_per_second << 8 ) / s_param->total.height );
    override_context_param( p_ictx, SENSOR_EXPOSURES_PARAM, s_param->sensor_exp_number );
    override_context_param( p_ictx, SENSOR_SUPPORTED_PRESETS_PARAM, s_param->modes_num );
}

void sensor_ready( sensor_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    uint32_t ctx_id = p_ictx->context_id;

    if ( get_context_param( p_ictx, SENSOR_STREAMING_PARAM ) == 0 && p_fsm->ctrl.start_streaming != NULL ) {
#if !IS_MALI_C71
        // We need a delay between sensors starts,
        // otherwise histograms comes at the same time and on R0 only one is served, resulting in AE not working.
        // Problem only present on split_architecture because of mcfe_fsm starting sensors at the same time.
        system_timer_usleep( 7000 );
#endif
        LOG( LOG_INFO, "Start streaming (pos = %u)", ctx_id );

        // Call sensor API.
        p_fsm->ctrl.start_streaming( p_fsm->drv_priv );

        // Update context param (override used to update read-only param).
        override_context_param( p_ictx, SENSOR_STREAMING_PARAM, 1 );
    }
	LOG( LOG_INFO, "%s X", __FUNCTION__);
}

void sensor_stopped( sensor_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    uint32_t ctx_id = p_ictx->context_id;

    if ( get_context_param( p_ictx, SENSOR_STREAMING_PARAM ) == 1 && p_fsm->ctrl.stop_streaming != NULL ) {
        LOG( LOG_INFO, "Stop streaming (pos = %u)", ctx_id );

        // Call sensor API
        p_fsm->ctrl.stop_streaming( p_fsm->drv_priv );

        // Update context param (override used to update read-only param).
        override_context_param( p_ictx, SENSOR_STREAMING_PARAM, 0 );
    }
}

void sensor_update_hw( sensor_fsm_ptr_t p_fsm )
{
	printf("Enter sensor_update_hw.\n");
    int stub = 0;
    exposure_set_t exp;

    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    WRAP_GENERAL_CMD( p_ictx, CMD_ID_FRAME_EXPOSURE_SET, CMD_DIRECTION_GET, &stub, &exp );
    const uint16_t again_log2 = ( uint16_t )( exp.info.again_log2 >> ( LOG2_GAIN_SHIFT - 5 ) ); // Makes again in format log2( gain ) * 32.

    const uint32_t idx_r = CALIBRATION_BLACK_LEVEL_R;
    const uint32_t idx_b = CALIBRATION_BLACK_LEVEL_B;
    const uint32_t idx_gr = CALIBRATION_BLACK_LEVEL_GR;
    const uint32_t idx_gb = CALIBRATION_BLACK_LEVEL_GB;

    const uint32_t bl_r = calc_modulation_u16( again_log2, calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), idx_r ), calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), idx_r ) );
    const uint32_t bl_b = calc_modulation_u16( again_log2, calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), idx_b ), calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), idx_b ) );
    const uint32_t bl_gr = calc_modulation_u16( again_log2, calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), idx_gr ), calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), idx_gr ) );
    const uint32_t bl_gb = calc_modulation_u16( again_log2, calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), idx_gb ), calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), idx_gb ) );

    const uint32_t wdr_mode = get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM );

    // Update black-level FSM variable with average black level.
    p_fsm->black_level = ( bl_r + bl_gr + bl_gb + bl_b ) >> 2;

    // Default black level shift and value
    uint32_t black_level_shift = BLACK_LEVEL_SHIFT_DG;
    uint32_t black_level = p_fsm->black_level << black_level_shift;

    /* Handle bypass settings, depends on the mode. */
    switch ( wdr_mode ) {
    case WDR_MODE_FS_LIN:
        acamera_isp_pipeline_bypass_frame_stitch_write( p_ictx->settings.isp_base, 0 );
        break;
    default:
        acamera_isp_pipeline_bypass_frame_stitch_write( p_ictx->settings.isp_base, 1 );
        break;
    }

    // Coefficient calculation depends on wdr_mode.
    if ( ( wdr_mode == WDR_MODE_FS_LIN ) && ( get_context_param( p_ictx, ISP_MODULES_MANUAL_FRAME_STITCH_PARAM ) == 0 ) ) {
#ifdef ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_LONG_DEFAULT
        acamera_isp_frame_stitch_black_level_long_write( p_ictx->settings.isp_base, p_fsm->black_level << BLACK_LEVEL_SHIFT_FS );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_MEDIUM1_DEFAULT
        acamera_isp_frame_stitch_black_level_medium1_write( p_ictx->settings.isp_base, p_fsm->black_level << BLACK_LEVEL_SHIFT_FS );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_MEDIUM2_DEFAULT
        acamera_isp_frame_stitch_black_level_medium2_write( p_ictx->settings.isp_base, p_fsm->black_level << BLACK_LEVEL_SHIFT_FS );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_MEDIUM_DEFAULT
        acamera_isp_frame_stitch_black_level_medium_write( p_ictx->settings.isp_base, p_fsm->black_level << BLACK_LEVEL_SHIFT_FS );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_SHORT_DEFAULT
        acamera_isp_frame_stitch_black_level_short_write( p_ictx->settings.isp_base, p_fsm->black_level << BLACK_LEVEL_SHIFT_FS );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_VERY_SHORT_DEFAULT
        acamera_isp_frame_stitch_black_level_very_short_write( p_ictx->settings.isp_base, p_fsm->black_level << BLACK_LEVEL_SHIFT_FS );
#endif

    } else if ( wdr_mode == WDR_MODE_NATIVE ) {
        black_level_shift = 4;
        black_level = p_fsm->black_level << black_level_shift;
    }

    // Update black-levels in pipeline when it's not manual.
    if ( get_context_param( p_ictx, ISP_MODULES_MANUAL_BLACK_LEVEL_PARAM ) == 0 ) {
        acamera_isp_offset_black_00_write( p_ictx->settings.isp_base, bl_r << black_level_shift );
        acamera_isp_offset_black_01_write( p_ictx->settings.isp_base, bl_gr << black_level_shift );
        acamera_isp_offset_black_10_write( p_ictx->settings.isp_base, bl_gb << black_level_shift );
        acamera_isp_offset_black_11_write( p_ictx->settings.isp_base, bl_b << black_level_shift );
#ifdef ACAMERA_ISP_DIGITAL_GAIN_OFFSET_DEFAULT
        acamera_isp_digital_gain_offset_write( p_ictx->settings.isp_base, black_level );
#endif

// FE/BE and FS blackLevel set to the average of offset blackLevel.
#ifdef ACAMERA_ISP_GAMMA_FE_BLACK_LEVEL_IN_DL_DEFAULT // r0
        acamera_isp_gamma_fe_black_level_in_dl_write( p_ictx->settings.isp_base, black_level );
        acamera_isp_gamma_be_black_level_out_dl_write( p_ictx->settings.isp_base, black_level );
#endif
#ifdef ACAMERA_ISP_GAMMA_FE_BLACK_LEVEL_IN_SQ_DEFAULT // r1
        acamera_isp_gamma_fe_black_level_in_sq_write( p_ictx->settings.isp_base, black_level );
        acamera_isp_gamma_be_black_level_out_sq_write( p_ictx->settings.isp_base, black_level );
#endif

#ifdef ACAMERA_ISP_FRAME_STITCH_BLACK_LEVEL_OUT_DEFAULT
        acamera_isp_frame_stitch_black_level_out_write( p_ictx->settings.isp_base, black_level );
#endif
    }
}

void sensor_request_next_frame( sensor_fsm_ptr_t p_fsm )
{

    // Check if sensor is remote type and request next frame.
    if ( p_fsm->general_sensor_info.is_remote ) {

        if ( p_fsm->ctrl.request_next_frame ) {

            p_fsm->ctrl.request_next_frame( p_fsm->drv_priv );
        } else {
            LOG( LOG_ERR, "Sensor API 'request_next_frame' is not defined (NULL)." );
        }
    }
}

////////////////////////////////////////////////////
// General router command handler

void sensor_get_general_sensor_info( sensor_fsm_ptr_t p_fsm, acamera_cmd_sensor_info *p_sensor_info )
{
    // Update black-level and copy p_fsm->general_sensor_info.
    p_fsm->general_sensor_info.black_level = p_fsm->black_level;
    *p_sensor_info = p_fsm->general_sensor_info;
}

int remote_sensor_put_frame_callback_handler( void *owner, void *frame )
{
#if !MODEL_MODULE
    if ( !owner ) {
        LOG( LOG_ERR, "Error. Invalid owner pointer (NULL)." );
        return -1;
    } else if ( !frame ) {
        LOG( LOG_ERR, "Error. Invalid frame pointer (NULL)." );
        return -1;
    }

    const sensor_fsm_ptr_t p_fsm = owner;
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const int ctx_id = (int)( p_ictx->context_id );

    // Update FSM variable p_remote_sensor_frame to be fetched by MCFE
    p_fsm->p_remote_sensor_frame = frame;

    fsm_raise_event( p_fsm, event_id_isphw_frame_end_fe );

    LOG( LOG_DEBUG, "Filled raw frame is ready to be fetched by the MCFE (context id: %d, ptr: %p).", ctx_id, frame );

#endif
    return 0;
}

int remote_sensor_get_frame_callback_handler( void *owner, void **frame )
{
#if !MODEL_MODULE
    if ( !owner ) {
        LOG( LOG_ERR, "Error. Invalid owner pointer (NULL)." );
        return -1;
    } else if ( !frame ) {
        LOG( LOG_ERR, "Error. Invalid frame pointer (NULL)." );
        return -1;
    }

    const sensor_fsm_ptr_t p_fsm = owner;
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const int ctx_id = (int)( p_ictx->context_id );
	LOG(LOG_DEBUG, "%s E", __FUNCTION__);
    if ( p_fsm->is_remote_stream_reconfig_req ) {

        // Get sensor parameters
        const sensor_param_t *s_param = p_fsm->ctrl.get_parameters( p_fsm->drv_priv );

        if ( p_fsm->is_remote_stream_created ) {
            remote_sensor_frame_stream_deinit( p_ictx->context_id, 0 );
        }

        if ( remote_sensor_frame_stream_init( p_ictx->context_id, s_param ) ) {
            LOG( LOG_ERR, "Failed to create raw frame stream for remote sensor." );
            return -1;
        }

        p_fsm->is_remote_stream_reconfig_req = 0;
        p_fsm->is_remote_stream_created = 1;
    }

    if ( frame_stream_isp_get_frame( ctx_id, AFRAME_TYPE_RAW, (aframe_t **)frame ) ) {
        LOG( LOG_ERR, "Failed to get empty raw frame from the frame streamer." );
        *frame = NULL;
        return -1;
    }

    LOG( LOG_DEBUG, "Empty raw frame acquired (context id: %d, ptr: %p).", ctx_id, *frame );

#endif
    return 0;
}

int remote_sensor_release_frame_callback_handler( void *owner, void *frame )
{
#if !MODEL_MODULE
    if ( !owner ) {
        LOG( LOG_ERR, "Error. Invalid owner pointer (NULL)." );
        return -1;
    } else if ( !frame ) {
        LOG( LOG_ERR, "Error. Invalid frame pointer (NULL)." );
        return -1;
    }

    const sensor_fsm_ptr_t p_fsm = owner;
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const int ctx_id = (int)( p_ictx->context_id );

    ( (aframe_t *)frame )->state = AFRAME_STATE_EMPTY;

    if ( frame_stream_isp_put_frame( frame ) ) {
        LOG( LOG_ERR, "Failed to put raw frame to the frame streamer." );
        return -1;
    }

    LOG( LOG_DEBUG, "Raw frame released (context id: %d, ptr: %p).", ctx_id, frame );

#endif
    return 0;
}

void sensor_deinit( sensor_fsm_ptr_t p_fsm )
{
#if !MODEL_MODULE
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    acamera_isp_pipeline_bypass_sensor_offset_wdr_write( isp_base, 1 );
    acamera_isp_pipeline_bypass_sensor_offset_linear_write( isp_base, 1 );

    if ( p_fsm->ctrl.deinit ) {
        p_fsm->ctrl.deinit( p_fsm->drv_priv );

        if ( p_fsm->general_sensor_info.is_remote ) {
            remote_sensor_frame_stream_deinit( p_ictx->context_id, 1 );
        }
    } else {
        LOG( LOG_ERR, "Error. Sensor API 'deinit' is not initialized (NULL).\n" );
    }
#endif
}
