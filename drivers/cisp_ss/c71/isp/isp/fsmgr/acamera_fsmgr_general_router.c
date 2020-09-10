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
#include "acamera_isp_core_settings.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "acamera_math.h"

#include "system_stdlib.h"

#if defined( ISP_HAS_USER2KERNEL_FSM )
#include "sbuf.h"
#endif

acamera_cmd_result general_ae_info( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_INVALID_PARAM;
    }

    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_AE_BALANCED_FSM ) || defined( ISP_HAS_AE_MANUAL_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;

    acamera_cmd_ae_info *p_ae_info = (acamera_cmd_ae_info *)ret_value;

    p_ae_info->exposure_log2 = p_fsmgr->AE_fsm.exposure_log2;
    p_ae_info->exposure_ratio = p_fsmgr->AE_fsm.exposure_ratio;
#else
#error "No general router handler for CMD_ID_AE_INFO !"
#endif

    return CMD_RESULT_OK;
}

static acamera_cmd_result general_hist_info( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

    // parameter check
    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_HISTOGRAM_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    acamera_cmd_hist_info *p_hist_info = (acamera_cmd_hist_info *)ret_value;

    p_hist_info->fullhist_sum = p_fsmgr->histogram_fsm.fullhist_sum;
    p_hist_info->fullhist = p_fsmgr->histogram_fsm.fullhist;
#else
#error "No general router handler for CMD_ID_HIST_INFO !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_cmos_current_exposure_log2( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

#if defined( ISP_HAS_CMOS_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    *( (int32_t *)ret_value ) = p_fsmgr->cmos_fsm.exposure_log2;
#else
#error "No general router handler for CMD_ID_CMOS_CURRENT_EXPOSURE_LOG2 !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_cmos_exposure_ratio( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

#if defined( ISP_HAS_CMOS_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    *ret_value = p_fsmgr->cmos_fsm.exposure_ratio;
#else
#error "No general router handler for CMD_ID_CMOS_EXPOSURE_RATIO !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_cmos_max_exposure_log2( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

#if defined( ISP_HAS_USER2KERNEL_FSM )
    // user-driver takes the max_exposure_log from user2kernel sbuf
    cmos_info_t sbuf_cmos_info;
    user2kernel_get_sbuf_cmos_info( p_ictx->context_id, &sbuf_cmos_info );
    *( (int32_t *)ret_value ) = sbuf_cmos_info.max_exposure_log2;

#elif defined( ISP_HAS_CMOS_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    *( (int32_t *)ret_value ) = p_fsmgr->cmos_fsm.max_exposure_log2;
#else
#error "No general router handler for CMD_ID_CMOS_MAX_EXPOSURE_LOG2 !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_cmos_history_size_get( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

#if defined( ISP_HAS_CMOS_FSM )
    *ret_value = sizeof( p_ictx->fsmgr.cmos_fsm.exposure_hist ) / sizeof( p_ictx->fsmgr.cmos_fsm.exposure_hist[0] );
#else
#error "No general router handler for CMD_ID_CMOS_HISTORY_SIZE !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_exposure_target( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_GET == dir ) {
        LOG( LOG_NOTICE, "GET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

#if defined( ISP_HAS_CMOS_FSM )
    acamera_cmd_result rc = CMD_RESULT_OK;
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    acamera_cmd_exposure_target *p_exp_target = (acamera_cmd_exposure_target *)value;

    LOG( LOG_DEBUG, "exp_target: exp_log2: %d, exp_ratio: %u.", (int)p_exp_target->exposure_log2, (unsigned int)p_exp_target->exposure_ratio );
    cmos_set_exposure_target( &( p_fsmgr->cmos_fsm ), p_exp_target->exposure_log2, p_exp_target->exposure_ratio );

#if !USER_MODULE
    /* check whether the apply is succeed */
    if ( ( p_fsmgr->cmos_fsm.exposure_log2 != p_exp_target->exposure_log2 ) ) {
        LOG( LOG_INFO, "new AE failed, expected: exp_log2: %d, exp_ratio: %u, cmos_values: exp_log2: %d, exp_ratio: %u.",
             (int)p_exp_target->exposure_log2,
             (unsigned int)p_exp_target->exposure_ratio,
             (int)p_fsmgr->cmos_fsm.exposure_log2,
             (unsigned int)p_fsmgr->cmos_fsm.exposure_ratio_in );

        rc = CMD_RESULT_ERR;
    }
    /* if cmos limits exposure ratio to max then return limited exposure ratio */
    if ( p_fsmgr->cmos_fsm.exposure_ratio_in != p_exp_target->exposure_ratio ) {
        p_exp_target->exposure_ratio = p_fsmgr->cmos_fsm.exposure_ratio_in;
    }
#endif

    return rc;
#else
#error "No general router handler for CMD_ID_EXPOSURE_TARGET !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_frame_exposure_set( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

    // parameter check
    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_CMOS_FSM )
    if ( NULL == value ) {
        LOG( LOG_ERR, "Invalid param: value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }
    exposure_set_t *p_set_get = NULL;
    exposure_set_t *p_set_out = (exposure_set_t *)ret_value;
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;

    p_set_get = cmos_get_frame_exposure_set( &( p_fsmgr->cmos_fsm ), *( (int *)value ) );

    *p_set_out = *p_set_get;
#else
#error "No general router handler for CMD_ID_FRAME_EXPOSURE_SET !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_cmos_total_gain( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

#if defined( ISP_HAS_CMOS_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;

    *( (int32_t *)ret_value ) = p_fsmgr->cmos_fsm.again_val_log2 +
                                p_fsmgr->cmos_fsm.dgain_val_log2 +
                                p_fsmgr->cmos_fsm.isp_dgain_log2;
#else
#error "No general router handler for CMD_ID_CMOS_TOTAL_GAIN !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_ccm_info( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // parameter check
    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

    if ( ( CMD_DIRECTION_SET == dir ) && ( NULL == value ) ) {
        LOG( LOG_ERR, "Invalid param: value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_COLOR_MATRIX_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;

    if ( CMD_DIRECTION_GET == dir ) {
        acamera_cmd_ccm_info *p_ccm_info = (acamera_cmd_ccm_info *)ret_value;
        color_matrix_get_info( &( p_fsmgr->color_matrix_fsm ), p_ccm_info );
    } else {
        acamera_cmd_ccm_info *p_ccm_info = (acamera_cmd_ccm_info *)value;
        color_matrix_set_info( &( p_fsmgr->color_matrix_fsm ), p_ccm_info );
    }
#elif defined( ISP_HAS_USER2KERNEL_FSM )
    // Temporal space is provided in linux-user driver
    static acamera_cmd_ccm_info ccm_info[FIRMWARE_CONTEXT_NUMBER];
    static int ccm_info_initialized = 0;
    if ( ccm_info_initialized == 0 ) {
        acamera_cmd_ccm_info init_val = {
            .light_source = 0x3,              // AWB_LIGHT_SOURCE_D50,
            .light_source_previous = 0x3,     // AWB_LIGHT_SOURCE_D50,
            .light_source_ccm = 0x3,          // AWB_LIGHT_SOURCE_D50,
            .light_source_ccm_previous = 0x3, // AWB_LIGHT_SOURCE_D50,
            .light_source_change_frames = 3,
            .light_source_change_frames_left = 2,
        };
        int i;
        for ( i = 0; i < FIRMWARE_CONTEXT_NUMBER; i++ )
            system_memcpy( ccm_info + i, &init_val, sizeof( acamera_cmd_ccm_info ) );
        ccm_info_initialized = 1;
    }

    if ( CMD_DIRECTION_GET == dir ) {
        acamera_cmd_ccm_info *p_ccm_info = (acamera_cmd_ccm_info *)ret_value;
        *p_ccm_info = ccm_info[p_ictx->context_id];
    } else {
        acamera_cmd_ccm_info *p_ccm_info = (acamera_cmd_ccm_info *)value;
        ccm_info[p_ictx->context_id] = *p_ccm_info;
    }
#else
#error "No general router handler for CMD_ID_CCM_INFO !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_wb_info( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // parameter check
    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

    // right now only support GET
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_ERR, "Invalid param: set is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_AWB_MESH_NBP_FSM ) || defined( ISP_HAS_AWB_MANUAL_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;

    if ( CMD_DIRECTION_GET == dir ) {
        acamera_cmd_wb_info *p_wb_info = (acamera_cmd_wb_info *)ret_value;
        awb_get_info( &( p_fsmgr->AWB_fsm ), p_wb_info );
    }

#else
#error "No general router handler for CMD_ID_WB_INFO !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_wb_frame_quantity( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // right now only support SET
    if ( CMD_DIRECTION_GET == dir ) {
        LOG( LOG_ERR, "Invalid param: get is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

    if ( ( CMD_DIRECTION_SET == dir ) && ( NULL == value ) ) {
        LOG( LOG_ERR, "Invalid param: value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_AWB_MESH_NBP_FSM ) || defined( ISP_HAS_AWB_MANUAL_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    acamera_cmd_wb_frame_quantity *p_fr_quan = (acamera_cmd_wb_frame_quantity *)value;

    p_fsmgr->AWB_fsm.switch_light_source_detect_frames_quantity = p_fr_quan->switch_light_source_detect_frames_quantity;
    p_fsmgr->AWB_fsm.switch_light_source_change_frames_quantity = p_fr_quan->switch_light_source_change_frames_quantity;

#else
#error "No general router handler for CMD_ID_WB_FRAME_QUANTITY !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_sensor_info( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // parameter check
    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

    // right now only support SET
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_ERR, "Invalid param: set is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_USER2KERNEL_FSM )
    // user-driver takes sensor_info from user2kernel sbuf
    acamera_cmd_sensor_info *p_sensor_info = (acamera_cmd_sensor_info *)ret_value;

    sensor_info_t sbuf_sensor_info;
    user2kernel_get_sbuf_sensor_info( p_ictx->context_id, &sbuf_sensor_info );

    system_memset( p_sensor_info, 0, sizeof( acamera_cmd_sensor_info ) );

    *p_sensor_info = sbuf_sensor_info.sensor_info;

#elif defined( ISP_HAS_SENSOR_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;

    acamera_cmd_sensor_info *p_sensor_info = (acamera_cmd_sensor_info *)ret_value;
    sensor_get_general_sensor_info( &p_fsmgr->sensor_fsm, p_sensor_info );
#else
#error "No general router handler for CMD_ID_SENSOR_INFO !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_sensor_alloc_analog_gain( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // right now only support GET
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_ERR, "Invalid param: Set is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_SENSOR_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    int32_t gain = *( (int32_t *)value );

    *( (int32_t *)ret_value ) = p_fsmgr->sensor_fsm.ctrl.alloc_analog_gain( p_fsmgr->sensor_fsm.drv_priv, gain );

#elif defined( ISP_HAS_USER2KERNEL_FSM )
// No-operation in linux-user driver
#else
#error "No general router handler for CMD_ID_SENSOR_ALLOC_ANALOG_GAIN !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_sensor_alloc_digital_gain( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // right now only support GET
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_ERR, "Invalid param: Set is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_SENSOR_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    int32_t gain = *( (int32_t *)value );

    *( (int32_t *)ret_value ) = p_fsmgr->sensor_fsm.ctrl.alloc_digital_gain( p_fsmgr->sensor_fsm.drv_priv, gain );

#elif defined( ISP_HAS_USER2KERNEL_FSM )
// No-operation in linux-user driver
#else
#error "No general router handler for CMD_ID_SENSOR_ALLOC_DIGITAL_GAIN !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_sensor_update( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // right now only support SET
    if ( CMD_DIRECTION_GET == dir ) {
        LOG( LOG_ERR, "Invalid param: Get is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_SENSOR_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;

    p_fsmgr->sensor_fsm.ctrl.sensor_update( p_fsmgr->sensor_fsm.drv_priv );

#elif defined( ISP_HAS_USER2KERNEL_FSM )
// No-operation in linux-user driver
#else
#error "No general router handler for CMD_ID_SENSOR_UPDATE !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_sensor_alloc_integration_time( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // right now only support SET
    if ( CMD_DIRECTION_GET == dir ) {
        LOG( LOG_ERR, "Invalid param: Get is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_SENSOR_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    integration_times_t int_time;

    acamera_cmd_sensor_integration_time *p_time = (acamera_cmd_sensor_integration_time *)value;
    acamera_cmd_sensor_integration_time *p_time_out = (acamera_cmd_sensor_integration_time *)ret_value;

    int_time.int_time = p_time->int_time;
    int_time.int_time_M = p_time->int_time_M;
    int_time.int_time_M2 = p_time->int_time_M2;
    int_time.int_time_L = p_time->int_time_L;

    p_fsmgr->sensor_fsm.ctrl.alloc_integration_time( p_fsmgr->sensor_fsm.drv_priv, &int_time );

    p_time_out->int_time = int_time.int_time;
    p_time_out->int_time_M = int_time.int_time_M;
    p_time_out->int_time_M2 = int_time.int_time_M2;
    p_time_out->int_time_L = int_time.int_time_L;

#elif defined( ISP_HAS_USER2KERNEL_FSM )
    // cmos FSM expects the times to be written out to ret_value.
    system_memcpy( ret_value, value, sizeof( acamera_cmd_sensor_integration_time ) );
#else
#error "No general router handler for CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_sensor_set_wdr_mode( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // right now only support SET
    if ( CMD_DIRECTION_GET == dir ) {
        LOG( LOG_ERR, "Invalid param: Get is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

    return CMD_RESULT_OK;
}

acamera_cmd_result general_sensor_remote_frame_info( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{

#if defined( ISP_HAS_SENSOR_FSM )

    // Right now only support GET
    if ( CMD_DIRECTION_GET != dir ) {
        LOG( LOG_ERR, "Invalid param: Only Get is supported" );
        return CMD_RESULT_NOT_SUPPORTED;
    } else if ( !ret_value ) {
        LOG( LOG_ERR, "Invalid param: Return value pointer is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    acamera_cmd_sensor_remote_frame_info *p_remote_sensor_frame_info = (acamera_cmd_sensor_remote_frame_info *)ret_value;

    p_remote_sensor_frame_info->p_remote_sensor_frame = p_fsmgr->sensor_fsm.p_remote_sensor_frame;

#elif defined( ISP_HAS_USER2KERNEL_FSM )
// No-operation in linux-user driver
#elif defined( PLATFORM_MODEL )
// No-operation for PLATFORM_MODEL build configuration
#else
#error "No general router handler for CMD_ID_SENSOR_REMOTE_FRAME_INFO !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_sensor_alloc_channel_dgains( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
#if defined( ISP_HAS_SENSOR_FSM )
    // right now only support SET
    if ( CMD_DIRECTION_GET == dir ) {
        LOG( LOG_ERR, "Invalid param: Get is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;

    if ( p_fsmgr->sensor_fsm.ctrl.alloc_white_balance_gains )
        p_fsmgr->sensor_fsm.ctrl.alloc_white_balance_gains( p_fsmgr->sensor_fsm.drv_priv, (int32_t *)value );

#elif defined( ISP_HAS_USER2KERNEL_FSM )
// No-operation in linux-user driver
#elif defined( PLATFORM_MODEL )
// No-operation for PLATFORM_MODEL build configuration
#else
#error "No general router handler for CMD_ID_SENSOR_ALLOC_WB_GAINS !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_defect_pixel_info( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // parameter check
    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

    // right now only support GET
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_ERR, "Invalid param: set is not supported" );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_DEFECT_PIXEL_FSM )
    acamera_fsmgr_t *p_fsmgr = &p_ictx->fsmgr;
    acamera_cmd_defect_pixel_info *p_defect_pixel_info = (acamera_cmd_defect_pixel_info *)ret_value;

    p_defect_pixel_info->hp_started = p_fsmgr->defect_pixel_fsm.hp_started;

#elif defined( ISP_HAS_USER2KERNEL_FSM )
    // return 0 for linux user-driver
    acamera_cmd_defect_pixel_info *p_defect_pixel_info = (acamera_cmd_defect_pixel_info *)ret_value;
    p_defect_pixel_info->hp_started = 0;

#else
#error "No general router handler for CMD_ID_DEFECT_PIXEL_INFO !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_output_formatter_data( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // parameter check
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_OUTPUT_FORMATTER_FSM )
    system_memcpy( ret_value, &p_ictx->fsmgr.output_formatter_fsm.output_formatter_cfg, sizeof( output_formatter_cfg_t ) );
#elif defined( ISP_HAS_USER2KERNEL_FSM )
// No-operation in linux-user driver
#elif defined( PLATFORM_MODEL )
// No-operation for PLATFORM_MODEL build configuration
#else
#error "No general router handler for CMD_ID_OUTPUT_FORMATTER_DATA !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_mcfe_get_slot_avail_inputs( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // parameter check
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_MCFE_FSM )
    *( (int32_t *)ret_value ) = module_mcfe_get_free_inputs_for_slot_id( p_ictx->context_id );
#elif defined( ISP_HAS_USER2KERNEL_FSM )
// No-operation in linux-user driver
#elif defined( PLATFORM_MODEL )
    *( (int32_t *)ret_value ) = PLATFORM_MODEL_GENERAL_MCFE_SLOT_AVAIL_INPUTS;
#else
#error "No general router handler for CMD_ID_MCFE_GET_SLOT_AVAIL_INPUTS !"
#endif

    return CMD_RESULT_OK;
}

acamera_cmd_result general_hist_is_on_sqrt( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value )
{
    // parameter check
    if ( CMD_DIRECTION_SET == dir ) {
        LOG( LOG_NOTICE, "SET is not supported." );
        return CMD_RESULT_NOT_SUPPORTED;
    }

    if ( ( CMD_DIRECTION_GET == dir ) && ( NULL == ret_value ) ) {
        LOG( LOG_ERR, "Invalid param: ret_value is NULL." );
        return CMD_RESULT_INVALID_PARAM;
    }

#if defined( ISP_HAS_HISTOGRAM_FSM )
    *ret_value = p_ictx->fsmgr.histogram_fsm.hist_is_on_sqrt;
#elif defined( ISP_HAS_USER2KERNEL_FSM )
// No-operation in linux-user driver
#elif defined( PLATFORM_MODEL )
// No-operation for PLATFORM_MODEL build configuration
#else
#error "No general router handler for CMD_ID_MCFE_GET_SLOT_AVAIL_INPUTS !"
#endif

    return CMD_RESULT_OK;
}


typedef acamera_cmd_result ( *P_HANDLE )( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_direction dir, const uint32_t *value, uint32_t *ret_value );

static P_HANDLE handle_arr[CMD_ID_MAX] = {
    [CMD_ID_AE_INFO] = general_ae_info,
    [CMD_ID_CCM_INFO] = general_ccm_info,
    [CMD_ID_CMOS_CURRENT_EXPOSURE_LOG2] = general_cmos_current_exposure_log2,
    [CMD_ID_CMOS_EXPOSURE_RATIO] = general_cmos_exposure_ratio,
    [CMD_ID_CMOS_MAX_EXPOSURE_LOG2] = general_cmos_max_exposure_log2,
    [CMD_ID_CMOS_HISTORY_SIZE] = general_cmos_history_size_get,
    [CMD_ID_CMOS_TOTAL_GAIN] = general_cmos_total_gain,
    [CMD_ID_DEFECT_PIXEL_INFO] = general_defect_pixel_info,
    [CMD_ID_EXPOSURE_TARGET] = general_exposure_target,
    [CMD_ID_FRAME_EXPOSURE_SET] = general_frame_exposure_set,
    [CMD_ID_HIST_INFO] = general_hist_info,
    [CMD_ID_OUTPUT_FORMATTER_DATA] = general_output_formatter_data,
    [CMD_ID_SENSOR_INFO] = general_sensor_info,
    [CMD_ID_SENSOR_ALLOC_ANALOG_GAIN] = general_sensor_alloc_analog_gain,
    [CMD_ID_SENSOR_ALLOC_DIGITAL_GAIN] = general_sensor_alloc_digital_gain,
    [CMD_ID_SENSOR_ALLOC_WB_GAINS] = general_sensor_alloc_channel_dgains,
    [CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME] = general_sensor_alloc_integration_time,
    [CMD_ID_SENSOR_UPDATE] = general_sensor_update,
    [CMD_ID_SENSOR_SET_WDR_MODE] = general_sensor_set_wdr_mode,
    [CMD_ID_SENSOR_REMOTE_FRAME_INFO] = general_sensor_remote_frame_info,
    [CMD_ID_WB_INFO] = general_wb_info,
    [CMD_ID_WB_FRAME_QUANTITY] = general_wb_frame_quantity,
    [CMD_ID_MCFE_GET_SLOT_AVAIL_INPUTS] = general_mcfe_get_slot_avail_inputs,
    [CMD_ID_HIST_IS_ON_SRQT] = general_hist_is_on_sqrt};

acamera_cmd_result general_handle_cmd( void *p_ictx, acamera_cmd_id cmd_id, acamera_cmd_direction dir, const void *value, void *ret_value )
{
    if ( p_ictx == NULL ) {
        LOG( LOG_ERR, "Invalid param: p_ictx is NULL" );
        return CMD_RESULT_INVALID_PARAM;
    }

    if ( cmd_id >= CMD_ID_MAX ) {
        LOG( LOG_ERR, "Invalid param: cmd_id: %d, max: %d", cmd_id, CMD_ID_MAX );
        return CMD_RESULT_INVALID_PARAM;
    }

    if ( ( dir != CMD_DIRECTION_SET ) && ( dir != CMD_DIRECTION_GET ) ) {
        LOG( LOG_ERR, "Invalid cmd_direction: %d., cmd_id: %d.", dir, cmd_id );
        return CMD_RESULT_INVALID_PARAM;
    }

    return handle_arr[cmd_id]( p_ictx, dir, (const uint32_t *)value, (uint32_t *)ret_value );
}
