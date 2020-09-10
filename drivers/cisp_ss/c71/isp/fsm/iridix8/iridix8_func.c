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

#include "system_assert.h"
#include "3a/iridix/iridix_acamera_core.h"
#include "acamera_fsmgr_general_router.h"
#include "acamera_isp_core_settings.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "acamera_math.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_IRIDIX8

void *iridix_acamera_core_init( uint32_t ctx_id )
{
	return NULL;
}

int32_t iridix_acamera_core_proc( void *iridix_ctx, const iridix_stats_data_t *stats, const iridix_input_data_t *input,
	const iridix_output_data_t *output )
{
	return 0;
}

static void iridix_fetch_calibration( iridix_fsm_ptr_t p_fsm, iridix_calibration_data_t *p_cali )
{
    assert( p_cali );
    acamera_calib_mgr_entry_t *cm = ACAMERA_FSM2CM_PTR( p_fsm );
    p_cali->cali_iridix_avg_coef = (uint8_t *)calib_mgr_u8_lut_get( cm, CALIBRATION_IRIDIX_AVG_COEF );
    p_cali->cali_iridix_min_max_str = (uint16_t *)calib_mgr_u16_lut_get( cm, CALIBRATION_IRIDIX_MIN_MAX_STR );
    p_cali->cali_ae_ctrl = (ae_balanced_param_t *)calib_mgr_u32_lut_get( cm, CALIBRATION_AE_CONTROL );
    p_cali->cali_iridix_ev_lim_no_str = (uint32_t *)calib_mgr_u32_lut_get( cm, CALIBRATION_IRIDIX_EV_LIM_NO_STR );
    p_cali->cali_iridix_ev_lim_full_str = (uint32_t *)calib_mgr_u32_lut_get( cm, CALIBRATION_IRIDIX_EV_LIM_FULL_STR );
    p_cali->cali_iridix_strength_dk_enh_ctrl = (iridix_strength_dk_enh_control_t *)calib_mgr_u32_lut_get( cm, CALIBRATION_IRIDIX8_STRENGTH_DK_ENH_CONTROL );
}

static void iridix_fetch_misc_info( iridix_fsm_ptr_t p_fsm, iridix_misc_info_t *p_misc )
{
    assert( p_misc );
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    WRAP_GENERAL_CMD( p_ictx, CMD_ID_CMOS_CURRENT_EXPOSURE_LOG2, CMD_DIRECTION_GET, NULL, (uint32_t *)&p_misc->cur_exposure_log2 );
    p_misc->global_minimum_iridix_strength = get_context_param( p_ictx, SYSTEM_MINIMUM_IRIDIX_STRENGTH_PARAM );
    p_misc->global_maximum_iridix_strength = get_context_param( p_ictx, SYSTEM_MAXIMUM_IRIDIX_STRENGTH_PARAM );
    p_misc->global_manual_iridix = get_context_param( p_ictx, ISP_MODULES_MANUAL_IRIDIX_PARAM );
    p_misc->global_iridix_strength_target = get_context_param( p_ictx, SYSTEM_IRIDIX_STRENGTH_TARGET_PARAM );
}

static void iridix_fetch_stats( iridix_fsm_ptr_t p_fsm, iridix_stats_data_t *p_stats )
{
    assert( p_stats );
    acamera_cmd_hist_info hist_info;

    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_HIST_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&hist_info ) ) {
        return;
    }

    {
        p_stats->fullhist = (uint32_t *)hist_info.fullhist; //discard const here
        p_stats->fullhist_sum = hist_info.fullhist_sum;
        p_stats->fullhist_size = ISP_METERING_HISTOGRAM_SIZE_BINS;
    }
}


////////////////////////////////////////////////////
// FSM event handlers

void iridix_init( iridix_fsm_t *p_fsm )
{
    LOG( LOG_NOTICE, "iridix USING 3A LIB" );
    p_fsm->iridix_core = iridix_acamera_core_init( ACAMERA_FSM_GET_FW_ID( p_fsm ) );
    if ( p_fsm->iridix_core == NULL )
        LOG( LOG_ERR, "Failed to initialize Iridix core!" );
}

void iridix_config( iridix_fsm_t *p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    // Initialize parameters.
    set_context_param( p_ictx, SYSTEM_IRIDIX_STRENGTH_TARGET_PARAM,
                       p_fsm->strength_target );
    set_context_param( p_ictx, SYSTEM_MAXIMUM_IRIDIX_STRENGTH_PARAM,
                       calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ),
                                             CALIBRATION_IRIDIX_STRENGTH_MAXIMUM )[0] );

    p_fsm->repeat_irq_mask = 0;
    iridix_request_interrupt( p_fsm, p_fsm->repeat_irq_mask );

    /* Enable */
    {
        acamera_isp_pipeline_bypass_digital_gain_iridix_write( p_ictx->settings.isp_base, 0 );
        acamera_isp_pipeline_bypass_iridix_write( p_ictx->settings.isp_base, 0 );
    }
}

void iridix_reload_calibration( iridix_fsm_t *p_fsm )
{
    uint16_t i;

    /* Configure the IRIDIX. */
    if ( calib_mgr_lut_exists( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX8_EXTENDED_CONTROL ) ) {
        const uint16_t *config = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX8_EXTENDED_CONTROL );
        acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

        /* Do not change the order of this init sequence. */
        acamera_isp_iridix_filter_mux_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_svariance_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_bright_pr_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_contrast_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_strength_inroi_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_iridix_strength_outroi_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_iridix_variance_intensity_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_variance_space_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_fwd_percept_control_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_rev_percept_control_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_slope_min_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
        acamera_isp_iridix_slope_max_write( p_ictx->settings.isp_base, (uint8_t)*config++ );
    } else {
        LOG( LOG_ERR, "CALIBRATION_IRIDIX8_EXTENDED_CONTROL is missing, module will not be configured correctly!" );
    }


    const uint32_t lut_element_size = calib_mgr_lut_width( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_ASYMMETRY );

    // 32 bit tables
    if ( lut_element_size == 4 ) {

        const uint32_t *lut_data = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_ASYMMETRY );
        for ( i = 0; i < calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_ASYMMETRY ); i++ ) {
            acamera_isp_iridix_lut_asymmetry_lut_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i, lut_data[i] );
        }
        // 16 bit tables
    } else if ( lut_element_size == 2 ) {

        const uint16_t *lut_data = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_ASYMMETRY );
        for ( i = 0; i < calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_ASYMMETRY ); i++ ) {
            acamera_isp_iridix_lut_asymmetry_lut_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i, lut_data[i] );
        }
    } else {
        LOG( LOG_ERR, "Unsupported CALIBRATION_IRIDIX_ASYMMETRY LUT element size: expected 4 or 2 bytes, got %d bytes", lut_element_size );
    }

    // Update gtm tables.
    const uint32_t *lut_gtm_x = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_GTM_LUT_X );
    const uint32_t *lut_gtm_y = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_GTM_LUT_Y );

    for ( i = 0; i < calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_GTM_LUT_X ); i++ ) {
        acamera_isp_iridix_lut_globaltm_x_lut_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i, lut_gtm_x[i] );
    }

    for ( i = 0; i < calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_GTM_LUT_Y ); i++ ) {
        acamera_isp_iridix_lut_globaltm_y_lut_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i, lut_gtm_y[i] );
    }

    /* reload calibration pointers for algorithm */
    iridix_fetch_calibration( p_fsm, &p_fsm->iridix_input.cali_data );
}

void iridix_update_hw( iridix_fsm_t *p_fsm )
{
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint16_t iridix_digital_gain = get_context_param( p_ictx, SYSTEM_IRIDIX_DIGITAL_GAIN_PARAM );
    const int32_t iridix_digital_gain_diff = ( int32_t )( ( iridix_digital_gain << 8 ) / p_fsm->iridix_digital_gain_prev );

    acamera_isp_digital_gain_iridix_gain_write( p_ictx->settings.isp_base, iridix_digital_gain );

    exposure_set_t exp_set_fr_next;
    exposure_set_t exp_set_fr_prev;
    int32_t frame_next = 1, frame_prev = 2;

    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_FRAME_EXPOSURE_SET, CMD_DIRECTION_GET, (const uint32_t *)&frame_next, (uint32_t *)&exp_set_fr_next ) ) {
        return;
    }

    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_FRAME_EXPOSURE_SET, CMD_DIRECTION_GET, (const uint32_t *)&frame_prev, (uint32_t *)&exp_set_fr_prev ) ) {
        return;
    }

    int32_t diff = math_exp2( exp_set_fr_prev.info.exposure_log2 - exp_set_fr_next.info.exposure_log2, LOG2_GAIN_SHIFT, 8 );
    diff = ( diff * iridix_digital_gain_diff ) >> 8;

    //LOG( LOG_DEBUG, "diff2 %d", (int)diff );
    if ( diff < 0 )
        diff = 256;
    if ( diff >= ( 1 << ACAMERA_ISP_IRIDIX_COLLECTION_CORRECTION_DATASIZE ) )
        diff = ( 1 << ACAMERA_ISP_IRIDIX_COLLECTION_CORRECTION_DATASIZE );
    //LOG( LOG_DEBUG, "%u %ld prev %ld", (unsigned int)diff, exp_set_fr1.info.exposure_log2, exp_set_fr0.info.exposure_log2 );
    //LOG( LOG_DEBUG, "diff3 %d", (int)diff );
    acamera_isp_iridix_collection_correction_write( p_ictx->settings.isp_base, diff );

    // Time filter for iridix strength.
    const uint8_t iridix_avg_coeff = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_IRIDIX_AVG_COEF )[0];
    uint16_t iridix_strength = p_fsm->strength_target;
    if ( iridix_avg_coeff > 1 ) {
        ( (iridix_fsm_ptr_t)p_fsm )->strength_avg += p_fsm->strength_target - p_fsm->strength_avg / iridix_avg_coeff; // Division by zero is checked.
        iridix_strength = ( uint16_t )( p_fsm->strength_avg / iridix_avg_coeff );                                     // Division by zero is checked.
    }

    acamera_isp_iridix_strength_inroi_write( p_ictx->settings.isp_base, iridix_strength >> 6 );
    acamera_isp_iridix_dark_enh_write( p_ictx->settings.isp_base, p_fsm->dark_enh );
    acamera_isp_iridix_slope_max_write( p_ictx->settings.isp_base, MIN( p_fsm->dark_enh, 255 ) );
    p_fsm->iridix_digital_gain_prev = iridix_digital_gain;
}

void iridix_update_algo( iridix_fsm_t *p_fsm )
{
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    iridix_fetch_misc_info( p_fsm, &p_fsm->iridix_input.misc_info );
    iridix_fetch_stats( p_fsm, &p_fsm->iridix_stats );
    const iridix_input_data_t input = {.acamera_input = &p_fsm->iridix_input};
    const iridix_output_data_t output = {.acamera_output = &p_fsm->iridix_output};

    // remove the casts to strip const once 3a lib is updated.
    int32_t err = iridix_acamera_core_proc( p_fsm->iridix_core, &p_fsm->iridix_stats, (iridix_input_data_t *)&input, (iridix_output_data_t *)&output );

    if ( err != 0 )
        LOG( LOG_ERR, "Failed process Iridix (error=%d)!", err );
    else {
        p_fsm->strength_target = p_fsm->iridix_output.strength_target;
        p_fsm->dark_enh = p_fsm->iridix_output.dark_enh;
        p_fsm->iridix_contrast = p_fsm->iridix_output.iridix_contrast;
        set_context_param( p_ictx, SYSTEM_IRIDIX_DIGITAL_GAIN_PARAM, p_fsm->iridix_output.iridix_global_DG );
    }

    override_context_param( p_ictx, STATUS_INFO_AWB_MIX_LIGHT_CONTRAST_PARAM, p_fsm->iridix_contrast );
}

void iridix_deinit( iridix_fsm_ptr_t p_fsm )
{
    acamera_isp_pipeline_bypass_digital_gain_iridix_write(
        ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );
    acamera_isp_pipeline_bypass_iridix_write(
        ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );
}
