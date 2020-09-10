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

#include "acamera.h"
#include "acamera_command_api.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "module_mcfe.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_MCFE

static void module_mcfe_usecase_create_sensor_config( mcfe_fsm_ptr_t p_fsm, module_mcfe_sensor_cfg_t *sensor_config )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint32_t ctx_id = p_ictx->context_id;

    // Get sensor config.
    const sensor_param_t *s_param = ACAMERA_FSM2FSMGR_PTR( p_fsm )->sensor_fsm.ctrl.get_parameters( ACAMERA_FSM2FSMGR_PTR( p_fsm )->sensor_fsm.drv_priv );

    sensor_config->h_start = s_param->h_start;
    sensor_config->v_start = s_param->v_start;
    sensor_config->is_remote = s_param->is_remote;
    sensor_config->num_channel = s_param->num_channel;
    sensor_config->is_reverse_order = s_param->is_reverse_order;
    sensor_config->video_port_id = s_param->video_port_id;
    sensor_config->data_width = s_param->data_width;
    sensor_config->width = s_param->active.width;
    sensor_config->height = s_param->active.height;
    sensor_config->rggb_start = s_param->rggb_start;
    sensor_config->cfa_pattern = s_param->cfa_pattern;
    sensor_config->cdma_addr = p_ictx->settings.isp_base;

    LOG( LOG_DEBUG, "CTX %d [Sensor configuration] - remote=%d, vid=%d, ch=%d, dw=%d, hs=%d, vs=%d, w=%d, h=%d, rgb=%d, cfa=%d, cdmaOff=0x%x.",
         ctx_id,
         sensor_config->is_remote,
         sensor_config->video_port_id,
         sensor_config->num_channel,
         sensor_config->data_width,
         sensor_config->h_start,
         sensor_config->v_start,
         sensor_config->width,
         sensor_config->height,
         sensor_config->rggb_start,
         sensor_config->cfa_pattern,
         sensor_config->cdma_addr );
}

static void module_mcfe_usecase_create_output_config( mcfe_fsm_ptr_t p_fsm, module_mcfe_output_cfg_t *output_config )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint32_t ctx_id = p_ictx->context_id;
    int i;

    output_formatter_cfg_t output_formatter_config;
    WRAP_GENERAL_CMD( p_ictx, CMD_ID_OUTPUT_FORMATTER_DATA, CMD_DIRECTION_GET, NULL, (uint32_t *)&output_formatter_config );

    // Prepare output config.
    output_config->format = output_formatter_config.format;
    output_config->num_planes = output_formatter_config.num_planes;
    output_config->crop.startx = get_context_param( p_ictx, IMAGE_CROP_XOFFSET_ID_PARAM );
    output_config->crop.starty = get_context_param( p_ictx, IMAGE_CROP_YOFFSET_ID_PARAM );
    output_config->crop.width = get_context_param( p_ictx, IMAGE_CROP_WIDTH_ID_PARAM );
    output_config->crop.height = get_context_param( p_ictx, IMAGE_CROP_HEIGHT_ID_PARAM );
    output_config->crop.enabled = get_context_param( p_ictx, IMAGE_CROP_ENABLE_ID_PARAM );

    for ( i = 0; i < output_config->num_planes; i++ ) {
        output_config->plane[i].axi = output_formatter_config.plane[i].axi;
		//TODO: out buffer msb_align and data_width are the same as out format msg_align by 10000058
        output_config->plane[i].msb_align = output_formatter_config.plane[i].axi_cfg.msb_align;//AFRAME_HW_FLAG_MSB_ALIGN
        output_config->plane[i].data_width = output_formatter_config.plane[i].axi_cfg.data_width;
        output_config->plane[i].h_subsampling = output_formatter_config.plane[i].axi_cfg.h_subsampling;
        output_config->plane[i].v_subsampling = output_formatter_config.plane[i].axi_cfg.v_subsampling;
    }

    LOG( LOG_DEBUG, "CTX %d [Output configuration] - format=%d, planes=%d, axi1=%d, axi2=%d, axi3=%d.",
         ctx_id,
         output_config->format,
         output_config->num_planes,
         output_config->plane[0].axi,
         output_config->plane[1].axi,
         output_config->plane[2].axi );
}

// FSM event handlers

/**
 *   @brief     Initialise FSM.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   Initialise corresponding MCFE and cdma_offsets.
 */
void mcfe_init( mcfe_fsm_ptr_t p_fsm )
{
    LOG( LOG_INFO, "%s E", __FUNCTION__ );
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint32_t ctx_id = p_ictx->context_id;

    // Get sensor config
    const sensor_param_t *s_param = ACAMERA_FSM2FSMGR_PTR( p_fsm )->sensor_fsm.ctrl.get_parameters( ACAMERA_FSM2FSMGR_PTR( p_fsm )->sensor_fsm.drv_priv );


    // Check sensor type and initialise usecase structure
    const module_mcfe_usecase_type_t usecase_type = ( s_param->is_remote ) ? ( MODULE_MCFE_USECASE_MANUAL ) : ( MODULE_MCFE_USECASE_TDMF );

    module_mcfe_usecase_init( &( p_fsm->usecase_cfg ), usecase_type, ctx_id, ISP_HISTOGRAM_POSITION_IS_BE );
    override_context_param( p_ictx, MCFE_USECASE_PARAM, usecase_type );
    LOG( LOG_INFO, "%s X", __FUNCTION__ );
}

/**
 *   @brief     Start MCFE FSM.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   Configure MCFE context with its sensor input and output format.
 */
void mcfe_config( mcfe_fsm_ptr_t p_fsm )
{
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint32_t ctx_id = p_ictx->context_id;

    module_mcfe_sensor_cfg_t sensor_config;
    module_mcfe_output_cfg_t output_config;

    module_mcfe_usecase_create_sensor_config( p_fsm, &sensor_config );
    module_mcfe_usecase_create_output_config( p_fsm, &output_config );

    int rc = p_fsm->usecase_cfg.functions.config( &( p_fsm->usecase_cfg ), &sensor_config, &output_config );

    // Error handler
    if ( rc != MCFE_ERR_NONE ) {
        p_fsm->usecase_cfg.functions.release_resources( &( p_fsm->usecase_cfg ) );
        LOG( LOG_ERR, "Failed to configure use-case (context id: %d, type: %d), error code: (%d).",
             ctx_id,
             p_fsm->usecase_cfg.type,
             rc );
    }

    rc = module_mcfe_update_inputs();
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Failed to update MCFE inputs in use" );
    }
}

/**
 *   @brief     Start MCFE FSM.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   Start MCFE slot.
 */
void mcfe_start( mcfe_fsm_ptr_t p_fsm )
{
    p_fsm->usecase_cfg.functions.start( &( p_fsm->usecase_cfg ) );
}

/**
 *   @brief     Stop MCFE FSM.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   This is not per-context approach. It stops and re-inits all slots again.
 */
void mcfe_stop( mcfe_fsm_ptr_t p_fsm )
{
    p_fsm->usecase_cfg.functions.stop( &( p_fsm->usecase_cfg ) );
}

/**
 *   @brief     Raw buffer ready event handler.
 *
 *   @param     p_fsm   Pointer to FSM private data
 */
//#define MCFE_DEBUG_FRAME_COUNTER
void mcfe_raw_buffer_ready( mcfe_fsm_ptr_t p_fsm )
{
	LOG( LOG_INFO, "%s E", __FUNCTION__);
#if defined( MCFE_DEBUG_FRAME_COUNTER )
    static int raw_buffer_counter = 0;
    LOG( LOG_INFO, "isphw_frame_end_fe event occurred! (cnt = %d, ctx_id = [%u])",
         raw_buffer_counter++, ACAMERA_FSM2ICTX_PTR( p_fsm )->context_id );
#endif

    // If use-case type is MODULE_MCFE_USECASE_MANUAL fetch remote_sensor_frame from sensor FSM
    // and update use-case configuration structure
	if (p_fsm->usecase_cfg.type != MODULE_MCFE_USECASE_MANUAL) {
		p_fsm->usecase_cfg.type = MODULE_MCFE_USECASE_MANUAL;
		LOG(LOG_ERR, "usecase type is not MODULE_MCFE_USECASE_MANUAL.");
	}
    if ( p_fsm->usecase_cfg.type == MODULE_MCFE_USECASE_MANUAL ) {
        acamera_cmd_sensor_remote_frame_info remote_sensor_frame_info;

        WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_REMOTE_FRAME_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&remote_sensor_frame_info );

        LOG( LOG_DEBUG, "CMD_ID_SENSOR_REMOTE_FRAME_INFO returned frame pointer: %p", remote_sensor_frame_info.p_remote_sensor_frame );

        p_fsm->usecase_cfg.remote_sensor_frame = remote_sensor_frame_info.p_remote_sensor_frame;
    }

    p_fsm->usecase_cfg.functions.process_event( &( p_fsm->usecase_cfg ), MODULE_MCFE_EVENT_RAW_BUFFER_READY );
}

/**
 *   @brief     Out buffer ready event handler.
 *
 *   @param     p_fsm   Pointer to FSM private data
 */
void mcfe_out_buffer_ready( mcfe_fsm_ptr_t p_fsm )
{
#if defined( MCFE_DEBUG_FRAME_COUNTER )
    static int out_buffer_counter = 0;
    LOG( LOG_INFO, "isphw_frame_end event occurred! (cnt = %d, ctx_id = [%u])",
         out_buffer_counter++, ACAMERA_FSM2ICTX_PTR( p_fsm )->context_id );
#endif
    p_fsm->usecase_cfg.functions.process_event( &( p_fsm->usecase_cfg ), MODULE_MCFE_EVENT_OUT_BUFFER_READY );
}

/**
 *   @brief     Deinitialise MCFE FSM.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   This is not per-context approach. It deinits all slots.
 */
void mcfe_deinit( mcfe_fsm_ptr_t p_fsm )
{
    module_mcfe_usecase_deinit( &( p_fsm->usecase_cfg ) );
}
