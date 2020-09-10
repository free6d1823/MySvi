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
#include "acamera_sbus_api.h"

void control_init( control_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint32_t isp_base = p_ictx->settings.isp_base;

    // Init config buffer mode to 2 - ISP settings are applied local blanking timing
    acamera_isp_pipeline_config_buffer_mode_write( isp_base, 2 );

    // Init context no to context ID
    acamera_isp_pipeline_context_no_write( isp_base, p_ictx->context_id );

    // Initialize ISP sbus to get access to ISP memory
    // in API function REGISTERS_SOURCE_ID.
    //acamera_sbus_isp_init(&p_fsm->isp_sbus);
    acamera_sbus_init( &p_fsm->isp_sbus, sbus_isp );
    p_fsm->isp_sbus.mask = SBUS_MASK_SAMPLE_8BITS | SBUS_MASK_ADDR_32BITS | SBUS_MASK_SAMPLE_32BITS;

// Test pattern generator parameter init.
#if defined( ACAMERA_ISP_VIDEO_TEST_GEN_PATTERN_TYPE_DEFAULT ) && defined( ACAMERA_ISP_VIDEO_TEST_GEN_TEST_PATTERN_OFF_ON_DEFAULT )
    p_fsm->tpg_enable = ACAMERA_ISP_VIDEO_TEST_GEN_TEST_PATTERN_OFF_ON_DEFAULT;
    p_fsm->tpg_mode = ACAMERA_ISP_VIDEO_TEST_GEN_PATTERN_TYPE_DEFAULT;
    acamera_isp_video_test_gen_test_pattern_off_on_write( isp_base, p_fsm->tpg_enable );
    acamera_isp_video_test_gen_pattern_type_write( isp_base, p_fsm->tpg_mode );
    acamera_isp_pipeline_bypass_video_test_gen_write( isp_base, p_fsm->tpg_enable ? 0 : 1 );
    set_context_param( p_ictx, TEST_PATTERN_ENABLE_ID_PARAM, p_fsm->tpg_enable );
    set_context_param( p_ictx, TEST_PATTERN_MODE_ID_PARAM, p_fsm->tpg_mode );
#endif
}

void control_config( control_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint32_t wdr_mode = get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM );

    // Load calibration
    acamera_isp_ctx_load_calibrations( p_ictx, wdr_mode );

    // Attempt to load any custom settings that may exist in calibrations.
    acamera_isp_ctx_load_custom_settings( p_ictx );
}

void control_update_hw( control_fsm_ptr_t p_fsm )
{
// Test pattern generator parameters handling.
#if defined( ACAMERA_ISP_VIDEO_TEST_GEN_PATTERN_TYPE_DEFAULT ) && defined( ACAMERA_ISP_VIDEO_TEST_GEN_TEST_PATTERN_OFF_ON_DEFAULT )
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    const uint32_t tpg_enable = get_context_param( p_ictx, TEST_PATTERN_ENABLE_ID_PARAM );
    const uint8_t tpg_mode = get_context_param( p_ictx, TEST_PATTERN_MODE_ID_PARAM );
    const uint32_t isp_base = p_ictx->settings.isp_base;

    if ( tpg_enable != p_fsm->tpg_enable ) {
        acamera_isp_video_test_gen_test_pattern_off_on_write( isp_base, tpg_enable );
        acamera_isp_pipeline_bypass_video_test_gen_write( isp_base, tpg_enable ? 0 : 1 );
        p_fsm->tpg_enable = tpg_enable;
    }

    if ( tpg_mode != p_fsm->tpg_mode ) {
        acamera_isp_video_test_gen_pattern_type_write( isp_base, tpg_mode );
        p_fsm->tpg_mode = tpg_mode;
    }

#endif
}
