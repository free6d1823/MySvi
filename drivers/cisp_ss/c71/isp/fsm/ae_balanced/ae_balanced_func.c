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
#include "system_stdlib.h"
#include "system_types.h"
#include "3a/acamera_math.h"
#include "acamera_isp_core_settings.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_AE_BALANCED

void *ae_acamera_core_init( uint32_t ctx_id )
{
	return NULL;
}

int32_t ae_acamera_core_proc( void *ae_ctx, const ae_stats_data_t *stats, const ae_input_data_t *input,
	const ae_output_data_t *output )
{
	return 0;
}

static inline uint32_t full_ratio_to_adjaced( uint8_t exp_num, uint32_t ratio )
{
    switch ( exp_num ) {
    case 4:
        return math_exp2( log2_fixed_to_fixed( ratio, 6, 8 ) / 3, 8, 6 ) >> 6;
        break;
    case 3:
        return sqrt32( ratio >> 6 );
        break;
    default:
    case 2:
        return ratio >> 6;
        break;
    }
}

////////////////////////////////////////////////////
// AE ROI update

static void ae_roi_update( AE_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    // Get packed (4 8-bit coordinates in 32-bit variable) ROI from param
    const uint32_t ae_roi = get_context_param( p_ictx, AE_ROI_ID_PARAM );

    // Unpack and check values
    const uint32_t y2 = ( ae_roi & 0xff );
    const uint32_t x2 = ( ( ae_roi >> 8 ) & 0xff );
    const uint32_t y1 = ( ( ae_roi >> 16 ) & 0xff );
    const uint32_t x1 = ( ( ae_roi >> 24 ) & 0xff );

    if ( x2 <= x1 || y2 <= y1 ) {
        override_context_param( p_ictx, AE_ROI_ID_PARAM, p_fsm->ae_roi );
        return;
    }

    p_fsm->ae_roi = ae_roi;

    const uint16_t horz_zones = acamera_isp_metering_aexp_nodes_used_horiz_read( p_ictx->settings.isp_base );
    const uint16_t vert_zones = acamera_isp_metering_aexp_nodes_used_vert_read( p_ictx->settings.isp_base );

    const uint16_t *ptr_ae_zone_whgh_h = calib_mgr_u16_lut_get( p_ictx->calib_mgr_data, CALIBRATION_AE_ZONE_WGHT_HOR );
    const uint16_t *ptr_ae_zone_whgh_v = calib_mgr_u16_lut_get( p_ictx->calib_mgr_data, CALIBRATION_AE_ZONE_WGHT_VER );

    const uint8_t x_start = ( uint8_t )( ( x1 * horz_zones + 128 ) >> 8 );
    const uint8_t x_end = ( uint8_t )( ( x2 * horz_zones + 128 ) >> 8 );
    const uint8_t y_start = ( uint8_t )( ( y1 * vert_zones + 128 ) >> 8 );
    const uint8_t y_end = ( uint8_t )( ( y2 * vert_zones + 128 ) >> 8 );

    const uint8_t zone_size_x = x_end - x_start;
    const uint8_t zone_size_y = y_end - y_start;
    const uint32_t middle_x = zone_size_x * 256 / 2;
    const uint32_t middle_y = zone_size_y * 256 / 2;
    const uint32_t ae_zone_wght_hor_len = calib_mgr_lut_len( p_ictx->calib_mgr_data, CALIBRATION_AE_ZONE_WGHT_HOR );
    const uint32_t ae_zone_wght_ver_len = calib_mgr_lut_len( p_ictx->calib_mgr_data, CALIBRATION_AE_ZONE_WGHT_VER );
    uint16_t scale_x = 0;
    uint16_t scale_y = 0;

    if ( ae_zone_wght_hor_len ) {
        scale_x = ( horz_zones - 1 ) / ae_zone_wght_hor_len + 1;
    } else {
        LOG( LOG_CRIT, "ae_zone_wght_hor_len (from CALIBRATION) is zero" );
        return;
    }
    if ( ae_zone_wght_ver_len ) {
        scale_y = ( vert_zones - 1 ) / ae_zone_wght_ver_len + 1;
    } else {
        LOG( LOG_CRIT, "ae_zone_wght_ver_len (from CALIBRATION) is zero" );
        return;
    }

    uint16_t gaus_center_x = ( calib_mgr_lut_len( p_ictx->calib_mgr_data, CALIBRATION_AE_ZONE_WGHT_HOR ) * 256 / 2 ) * scale_x;
    uint16_t gaus_center_y = ( calib_mgr_lut_len( p_ictx->calib_mgr_data, CALIBRATION_AE_ZONE_WGHT_VER ) * 256 / 2 ) * scale_y;
    uint16_t x, y;

    for ( y = 0; y < vert_zones; y++ ) {
        uint8_t ae_coeff = 0;
        for ( x = 0; x < horz_zones; x++ ) {
            if ( y >= y_start && y <= y_end &&
                 x >= x_start && x <= x_end ) {

                uint8_t index_y = ( y - y_start );
                uint8_t index_x = ( x - x_start );
                int32_t distance_x = ( index_x * 256 + 128 ) - middle_x;
                int32_t distance_y = ( index_y * 256 + 128 ) - middle_y;

                if ( ( x == x_end && x_start != x_end ) ||
                     ( y == y_end && y_start != y_end ) ) {
                    ae_coeff = 0;
                } else {
                    uint32_t coeff_x = ( gaus_center_x + distance_x ) / 256;
                    if ( distance_x > 0 && ( distance_x & 0x80 ) )
                        coeff_x--;
                    uint32_t coeff_y = ( gaus_center_y + distance_y ) / 256;
                    if ( distance_y > 0 && ( distance_y & 0x80 ) )
                        coeff_y--;

                    coeff_x = ptr_ae_zone_whgh_h[coeff_x / scale_x];
                    coeff_y = ptr_ae_zone_whgh_v[coeff_y / scale_y];

                    ae_coeff = ( coeff_x * coeff_y ) >> 4;
                    if ( ae_coeff > 1 )
                        ae_coeff--;
                }
            } else {
                ae_coeff = 0;
            }
            acamera_isp_zones_aexp_weight_write( p_ictx->settings.isp_base, y, x, ae_coeff );

            // NOTE: histogram can be on CDMA or not depends on where it is located
            uint32_t base_addr = PHY_ADDR_ISP;
            if ( ISP_HISTOGRAM_POSITION_IS_BE ) {
                base_addr = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
            }
            acamera_isp_metering_hist_1_weight_table_write( base_addr, y, x, ae_coeff );
        }
    }
}

////////////////////////////////////////////////////
// FSM event handlers

void ae_init( AE_fsm_ptr_t p_fsm )
{
    LOG( LOG_INFO, "Initialize ae_balanced FSM." );


    (void)memset( p_fsm->WSNR_cumsum, 0, sizeof( *p_fsm->WSNR_cumsum ) );
    (void)memset( p_fsm->targets_history, 0, sizeof( *p_fsm->targets_history ) );


    p_fsm->ae_roi = get_context_param( ACAMERA_FSM2ICTX_PTR( p_fsm ), AE_ROI_ID_PARAM );
    p_fsm->ae_core = ae_acamera_core_init( ACAMERA_FSM_GET_FW_ID( p_fsm ) );
    if ( p_fsm->ae_core == NULL )
        LOG( LOG_ERR, "Failed to initialize AE core!" );
}


void ae_config( AE_fsm_ptr_t p_fsm )
{
    LOG( LOG_INFO, "AE Configure" );
}

static void ae_fetch_calibration( AE_fsm_ptr_t p_fsm, ae_calibration_data_t *p_cali )
{
    assert( p_cali );
    /* AE control parameters: */
    p_cali->ae_ctrl = (ae_balanced_param_t *)calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_AE_CONTROL );
    /* these are values used in ae core: */

    /*Calibration data: */
    p_cali->ae_corr_lut = (uint8_t *)calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_AE_CORRECTION );
    p_cali->ae_exp_corr_lut = (uint32_t *)calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_AE_EXPOSURE_CORRECTION );
    p_cali->ae_exp_corr_lut_len = calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_AE_EXPOSURE_CORRECTION );

#if defined( CALIBRATION_EXPOSURE_RATIO_ADJUSTMENT )
    p_cali->ae_exp_ratio_adjustment = (modulation_entry_t *)calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_EXPOSURE_RATIO_ADJUSTMENT );
    p_cali->ae_exp_ratio_adjustment_len = calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_EXPOSURE_RATIO_ADJUSTMENT );
#endif
    p_cali->ae_hdr_target = (modulation_entry_t *)calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_AE_CONTROL_HDR_TARGET );
    p_cali->ae_hdr_target_len = calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_AE_CONTROL_HDR_TARGET );
}

static void ae_fetch_misc_info( AE_fsm_ptr_t p_fsm, ae_misc_info_t *p_misc )
{
    assert( p_misc );
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    acamera_cmd_sensor_info sensor;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor ) ) {
        return;
    }

#if ( defined( ISP_HAS_IRIDIX8_FSM ) || defined( ISP_HAS_IRIDIX8_MANUAL_FSM ) || defined( ISP_HAS_IRIDIX_ACAMERA_FSM ) )
    p_misc->iridix_contrast = ( ACAMERA_FSM2FSMGR_PTR( p_fsm )->iridix_fsm.iridix_contrast ); // dw.8 value;
#endif
    p_misc->flags.has_iridix = ISP_HAS_IRIDIX8_FSM;

    /* Misc information */
    p_misc->sensor_exp_number = sensor.sensor_exp_number;
    p_misc->global_max_exposure_ratio = get_context_param( p_ictx, SYSTEM_MAX_EXPOSURE_RATIO_PARAM );
    p_misc->global_exposure_ratio = get_context_param( p_ictx, SYSTEM_EXPOSURE_RATIO_PARAM );
    p_misc->global_manual_exposure_ratio = get_context_param( p_ictx, SYSTEM_MANUAL_EXPOSURE_RATIO_PARAM );
    p_misc->global_ae_compensation = get_context_param( p_ictx, AE_COMPENSATION_ID_PARAM );
    p_misc->global_manual_exposure = get_context_param( p_ictx, SYSTEM_MANUAL_EXPOSURE_PARAM );
    p_misc->global_exposure = get_context_param( p_ictx, SYSTEM_EXPOSURE_PARAM );

    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_CMOS_TOTAL_GAIN, CMD_DIRECTION_GET, NULL, (uint32_t *)&p_misc->total_gain ) ) {
        return;
    }

    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_CMOS_MAX_EXPOSURE_LOG2, CMD_DIRECTION_GET, NULL, (uint32_t *)&p_misc->max_exposure_log2 ) ) {
        return;
    }
}

static void ae_fetch_stats( AE_fsm_ptr_t p_fsm, ae_stats_data_t *p_stats )
{
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


void ae_reload_calibration( AE_fsm_ptr_t p_fsm )
{
    ae_roi_update( p_fsm );
    ae_fetch_calibration( p_fsm, &p_fsm->ae_input.cali_data );
}


void ae_update_algo( AE_fsm_ptr_t p_fsm )
{
    ae_fetch_misc_info( p_fsm, &p_fsm->ae_input.misc_info );
    ae_fetch_stats( p_fsm, &p_fsm->ae_stats );

    const ae_input_data_t input = {.acamera_input = &p_fsm->ae_input};
    const ae_output_data_t output = {.acamera_output = &p_fsm->ae_output};


    /* Run algorithm */
    int32_t err = ae_acamera_core_proc( p_fsm->ae_core, &p_fsm->ae_stats, &input, &output );
    if ( err != 0 )
        LOG( LOG_ERR, "Failed process AE (error=%d)!", err );


    /* Process the algorithm output*/
    {
        p_fsm->exposure_log2 = p_fsm->ae_output.exposure_log2;
        p_fsm->exposure_ratio = p_fsm->ae_output.exposure_ratio;

        // Set exposure target to CMOS
        const acamera_cmd_exposure_target exp_target = {
            .exposure_log2 = p_fsm->exposure_log2,
            .exposure_ratio = p_fsm->exposure_ratio,
        };
        WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_EXPOSURE_TARGET, CMD_DIRECTION_SET, (uint32_t *)&exp_target, NULL );
        LOG( LOG_DEBUG, "ae exposure_log2: %d, exposure_ratio: %d", exp_target.exposure_log2, exp_target.exposure_ratio );


        if ( !get_context_param( ACAMERA_FSM2ICTX_PTR( p_fsm ), SYSTEM_MANUAL_EXPOSURE_RATIO_PARAM ) ) {
            set_context_param( ACAMERA_FSM2ICTX_PTR( p_fsm ), SYSTEM_EXPOSURE_RATIO_PARAM,
                               full_ratio_to_adjaced( p_fsm->ae_input.misc_info.sensor_exp_number,
                                                      p_fsm->ae_output.exposure_ratio ) );
        }
    }

    // Raise ae_ready event
    fsm_raise_event( p_fsm, event_id_algo_ae_calculation_done );
}
