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

#include "ae_update_histogram.h"
#include "acamera_command_api.h"
#include "acamera_frontend_config.h"
#include "acamera_logger.h"
#include "acamera_math.h"

// Called from histogram_fsm_interrupt - ae_read_full_histogram_data func.
void ae_histogram_dgain_compensation( histogram_fsm_ptr_t p_fsm )
{
    if ( acamera_isp_pipeline_bypass_digital_gain_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base ) == 0 ) {
        int stub = 0;
        exposure_set_t exp;
        uint16_t ispDGain;

        if ( ISP_HISTOGRAM_POSITION_IS_BE && ( ISP_HISTOGRAM_BE_POSITION == AE_HISTOGRAM_TAP_AFTER_DECOMPANDER || ISP_HISTOGRAM_BE_POSITION == AE_HISTOGRAM_TAP_AFTER_SHADING ) )
            return; // Stream already includes dgain.

        WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_FRAME_EXPOSURE_SET, CMD_DIRECTION_GET, &stub, &exp );
        ispDGain = math_exp2( exp.info.isp_dgain_log2, LOG2_GAIN_SHIFT, 8 );

        //LOG( LOG_DEBUG, "ispDG %d", ispDGain );
        if ( ispDGain > 0x100 ) {
            //uint16_t pivot = div_fixed( ISP_METERING_HISTOGRAM_SIZE_BINS << 8, ispDGain, 8 ) >> 8; // Need only int part.
            uint16_t pivot = ( ( ISP_METERING_HISTOGRAM_SIZE_BINS << 8 ) / ispDGain );

            //LOG( LOG_DEBUG, "pivot %d", pivot );

            int i;

            // Moving all elems after pivot to the clipped area.
            for ( i = pivot; i <= ISP_METERING_HISTOGRAM_SIZE_BINS - 2; i++ ) {
                p_fsm->fullhist[ISP_METERING_HISTOGRAM_SIZE_BINS - 1] += p_fsm->fullhist[i];
                p_fsm->fullhist[i] = 0;
            }

            // Spreading all elems before pivot all over hist.
            for ( i = pivot - 1; i >= 0; i-- ) {
                uint32_t j = multiplication_fixed_to_fixed( (uint32_t)i, ispDGain, 0, 8 );
                if ( j != i ) {
                    p_fsm->fullhist[j] = p_fsm->fullhist[i];
                    p_fsm->fullhist[i] = 0;
                }
            }
        } else {
            if ( ispDGain < 0x100 )
                LOG( LOG_ERR, "ispDGain %x < 0x100 is not handled; ispGDain not applied to histogram.", ispDGain );
        }
    }
}

#if defined( ISP_HAS_MCFE_FSM )
static void ae_update_histogram_shading_lut( histogram_fsm_const_ptr_t p_fsm, int idx )
{
    uint32_t cfg_offset = PHY_ADDR_ISP;
    uint8_t hist_radial_shading_enable = 1;
    if ( acamera_isp_pipeline_bypass_radial_shading_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base ) != 0 ) {
        hist_radial_shading_enable = 0;
    }

    if ( ISP_HISTOGRAM_POSITION_IS_BE ) {
        cfg_offset = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
        idx = 0;
        // After FE, BE_WDRGAIN,BE_FS and BE_COMPAND, histogram already includes shading_correction.
        if ( ISP_HISTOGRAM_BE_POSITION == AE_HISTOGRAM_TAP_AFTER_SHADING )
            hist_radial_shading_enable = 0;
    }


    switch ( idx ) {
    case 0:
        acamera_isp_metering_hist_1_radial_shading_enable_write( cfg_offset, hist_radial_shading_enable );
        break;
    case 1:
        acamera_isp_metering_hist_2_radial_shading_enable_write( cfg_offset, hist_radial_shading_enable );
        break;
    case 2:
        acamera_isp_metering_hist_3_radial_shading_enable_write( cfg_offset, hist_radial_shading_enable );
        break;
    case 3:
        acamera_isp_metering_hist_4_radial_shading_enable_write( cfg_offset, hist_radial_shading_enable );
        break;
    }
    if ( hist_radial_shading_enable == 0 )
        return;

#if defined( ISP_HAS_RADIAL_SHADING_FSM )
    int shading_lut_size = sizeof( ACAMERA_FSM2ICTX_PTR( p_fsm )->fsmgr.radial_shading_fsm.hist_shading_lut ) / sizeof( ACAMERA_FSM2ICTX_PTR( p_fsm )->fsmgr.radial_shading_fsm.hist_shading_lut[0] );
    int i = 0;
    switch ( idx ) {
    case 0:
        for ( i = 0; i < shading_lut_size; i++ )
            acamera_isp_metering_hist_1_shading_lut_write( cfg_offset, i, ACAMERA_FSM2ICTX_PTR( p_fsm )->fsmgr.radial_shading_fsm.hist_shading_lut[i] );
        break;
    case 1:
        for ( i = 0; i < shading_lut_size; i++ )
            acamera_isp_metering_hist_2_shading_lut_write( cfg_offset, i, ACAMERA_FSM2ICTX_PTR( p_fsm )->fsmgr.radial_shading_fsm.hist_shading_lut[i] );
        break;
    case 2:
        for ( i = 0; i < shading_lut_size; i++ )
            acamera_isp_metering_hist_3_shading_lut_write( cfg_offset, i, ACAMERA_FSM2ICTX_PTR( p_fsm )->fsmgr.radial_shading_fsm.hist_shading_lut[i] );
        break;
    case 3:
        for ( i = 0; i < shading_lut_size; i++ )
            acamera_isp_metering_hist_4_shading_lut_write( cfg_offset, i, ACAMERA_FSM2ICTX_PTR( p_fsm )->fsmgr.radial_shading_fsm.hist_shading_lut[i] );
        break;
    default:
        LOG( LOG_ERR, "Invalid metering hist input" );
        break;
    }
#else
    // TODO: need logic for getting shading LUT for pipeline without general FSM.
    return;
#endif // defined(ISP_HAS_RADIAL_SHADING_FSM)
}

static void ae_update_histogram_wbgain( histogram_fsm_const_ptr_t p_fsm, int input )
{
    uint8_t awb_enabled = 1;
    uint16_t wbGain[4];
    uint32_t cfg_offset = PHY_ADDR_ISP;

    if ( acamera_isp_pipeline_bypass_white_balance_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base ) != 0 )
        awb_enabled = 0;

    if ( ISP_HISTOGRAM_POSITION_IS_BE ) {
        cfg_offset = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
        input = 0;
        // After FE, BE_WDRGAIN,BE_FS and BE_COMPAND, histogram already includes wbGain.
        if ( ISP_HISTOGRAM_BE_POSITION == AE_HISTOGRAM_TAP_AFTER_SHADING )
            awb_enabled = 0; // stream already includes wb_gains
    }

    if ( awb_enabled == 0 ) {
        wbGain[0] = 256;
        wbGain[1] = 256;
        wbGain[2] = 256;
        wbGain[3] = 256;
    } else {
#if defined( ISP_HAS_AWB_MESH_NBP_FSM ) || defined( ISP_HAS_AWB_MANUAL_FSM )
        wbGain[0] = ACAMERA_FSM2FSMGR_PTR( p_fsm )->cmos_fsm.wb[0];
        wbGain[1] = ACAMERA_FSM2FSMGR_PTR( p_fsm )->cmos_fsm.wb[1];
        wbGain[2] = ACAMERA_FSM2FSMGR_PTR( p_fsm )->cmos_fsm.wb[2];
        wbGain[3] = ACAMERA_FSM2FSMGR_PTR( p_fsm )->cmos_fsm.wb[3];
#else
        wbGain[0] = acamera_isp_white_balance_gain_00_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
        wbGain[1] = acamera_isp_white_balance_gain_01_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
        wbGain[2] = acamera_isp_white_balance_gain_10_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
        wbGain[3] = acamera_isp_white_balance_gain_11_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
#endif

        if ( ISP_HISTOGRAM_POSITION_IS_BE && ISP_HISTOGRAM_BE_POSITION == AE_HISTOGRAM_TAP_AFTER_DECOMPANDER ) {
            // x format is fixed 6.8; to get sqrt of x in 6.8 format, we:
            // make make it format 6.16 (tmp = x<<8), then sqrt32(tmp) (format is 3.8 now).
            // Actual gain format here is 7.8 (used 6.8 in the example for simplicity).
            uint32_t i, tmp;
            for ( i = 0; i < 4; i++ ) {
                tmp = wbGain[i] << 8;      //format 7.16
                wbGain[i] = sqrt32( tmp ); //format 4.8
            }
        }
    }
    switch ( input ) {
    case 0:
        acamera_isp_metering_hist_1_gain_00_write( cfg_offset, wbGain[0] );
        acamera_isp_metering_hist_1_gain_01_write( cfg_offset, wbGain[1] );
        acamera_isp_metering_hist_1_gain_10_write( cfg_offset, wbGain[2] );
        acamera_isp_metering_hist_1_gain_11_write( cfg_offset, wbGain[3] );
        break;
    case 1:
        acamera_isp_metering_hist_2_gain_00_write( cfg_offset, wbGain[0] );
        acamera_isp_metering_hist_2_gain_01_write( cfg_offset, wbGain[1] );
        acamera_isp_metering_hist_2_gain_10_write( cfg_offset, wbGain[2] );
        acamera_isp_metering_hist_2_gain_11_write( cfg_offset, wbGain[3] );
        break;
    case 2:
        acamera_isp_metering_hist_3_gain_00_write( cfg_offset, wbGain[0] );
        acamera_isp_metering_hist_3_gain_01_write( cfg_offset, wbGain[1] );
        acamera_isp_metering_hist_3_gain_10_write( cfg_offset, wbGain[2] );
        acamera_isp_metering_hist_3_gain_11_write( cfg_offset, wbGain[3] );
        break;
    case 3:
        acamera_isp_metering_hist_4_gain_00_write( cfg_offset, wbGain[0] );
        acamera_isp_metering_hist_4_gain_01_write( cfg_offset, wbGain[1] );
        acamera_isp_metering_hist_4_gain_10_write( cfg_offset, wbGain[2] );
        acamera_isp_metering_hist_4_gain_11_write( cfg_offset, wbGain[3] );
        break;
    default:
        LOG( LOG_ERR, "Invalid metering hist input" );
        break;
    }
    //LOG( LOG_DEBUG, "WB: %d: %#x/%#x/%#x/%#x", input, wbGain[0], wbGain[1], wbGain[2], wbGain[3] );
}

static void ae_update_histogram_black_level( histogram_fsm_const_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    uint32_t cfg_offset = PHY_ADDR_ISP;
    uint8_t black_level_shift = BLACK_LEVEL_SHIFT_HIST;

    if ( get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM ) == WDR_MODE_NATIVE ) {
        black_level_shift = 0;
    }

    uint32_t sensor_bk_level = p_ictx->fsmgr.sensor_fsm.black_level;
    uint32_t hist_bk_level = sensor_bk_level << black_level_shift;
#if defined( ISP_HAS_MCFE_FSM )
    int input = module_mcfe_get_input_for_slot_id( ACAMERA_FSM2ICTX_PTR( p_fsm )->context_id );
#else
    int input = ISP_MODEL_INPUT_PORT_FOR_AE_UPDATE_HIST;
#endif

    if ( ISP_HISTOGRAM_POSITION_IS_BE ) {
        cfg_offset = p_ictx->settings.isp_base;
        input = 0;

        if ( ISP_HISTOGRAM_BE_POSITION == AE_HISTOGRAM_TAP_AFTER_DECOMPANDER ) {
#if IS_MALI_C71
            hist_bk_level = acamera_isp_gamma_fe_black_level_out_sq_read( p_ictx->settings.isp_base );
#else
            hist_bk_level = acamera_isp_gamma_fe_black_level_out_dl_read( p_ictx->settings.isp_base ); //comes from json files for R1
#endif
        }
    }

    //LOG( LOG_DEBUG, "bk = %ud (%#xh) // %#xh << %u", hist_bk_level, hist_bk_level, sensor_bk_level, black_level_shift );

    /* coverity[const]*/
    switch ( input ) {
    case 0:
        acamera_isp_metering_hist_1_black_00_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_1_black_01_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_1_black_10_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_1_black_11_write( cfg_offset, hist_bk_level );
        break;
    case 1:
        acamera_isp_metering_hist_2_black_00_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_2_black_01_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_2_black_10_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_2_black_11_write( cfg_offset, hist_bk_level );
        break;
    case 2:
        acamera_isp_metering_hist_3_black_00_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_3_black_01_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_3_black_10_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_3_black_11_write( cfg_offset, hist_bk_level );
        break;
    case 3:
        acamera_isp_metering_hist_4_black_00_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_4_black_01_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_4_black_10_write( cfg_offset, hist_bk_level );
        acamera_isp_metering_hist_4_black_11_write( cfg_offset, hist_bk_level );
        break;
    default:
        LOG( LOG_WARNING, "Could not find the input port so not setting black level for it." );
    }
    return;
}

static void ae_update_histogram_geometry( histogram_fsm_const_ptr_t p_fsm, int input )
{
    uint16_t width = acamera_isp_top_active_width_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
    uint16_t height = acamera_isp_top_active_height_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
    uint8_t rggb_start = acamera_isp_top_rggb_start_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
    uint8_t cfa_pattern = acamera_isp_top_cfa_pattern_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
    uint32_t cfg_offset = PHY_ADDR_ISP;

    if ( ISP_HISTOGRAM_POSITION_IS_BE ) {
        cfg_offset = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
        input = 0;
    }

    switch ( input ) {
    case 0:
        acamera_isp_metering_hist_1_active_width_write( cfg_offset, width );
        acamera_isp_metering_hist_1_active_height_write( cfg_offset, height );
        acamera_isp_metering_hist_1_rggb_start_write( cfg_offset, rggb_start );
        acamera_isp_metering_hist_1_cfa_pattern_write( cfg_offset, cfa_pattern );
        break;
    case 1:
        acamera_isp_metering_hist_2_active_width_write( cfg_offset, width );
        acamera_isp_metering_hist_2_active_height_write( cfg_offset, height );
        acamera_isp_metering_hist_2_rggb_start_write( cfg_offset, rggb_start );
        acamera_isp_metering_hist_2_cfa_pattern_write( cfg_offset, cfa_pattern );
        break;
    case 2:
        acamera_isp_metering_hist_3_active_width_write( cfg_offset, width );
        acamera_isp_metering_hist_3_active_height_write( cfg_offset, height );
        acamera_isp_metering_hist_3_rggb_start_write( cfg_offset, rggb_start );
        acamera_isp_metering_hist_3_cfa_pattern_write( cfg_offset, cfa_pattern );
        break;
    case 3:
        acamera_isp_metering_hist_4_active_width_write( cfg_offset, width );
        acamera_isp_metering_hist_4_active_height_write( cfg_offset, height );
        acamera_isp_metering_hist_4_rggb_start_write( cfg_offset, rggb_start );
        acamera_isp_metering_hist_4_cfa_pattern_write( cfg_offset, cfa_pattern );
        break;
    default:
        LOG( LOG_ERR, "Invalid metering hist input" );
        break;
    }
}
#endif // defined(ISP_HAS_MCFE_FSM)

// Called from histogram_fsm - ae_read_full_histogram_data func.
void ae_histogram_pipeline_update( histogram_fsm_const_ptr_t p_fsm )
{
#if defined( ISP_HAS_MCFE_FSM )
    int input = module_mcfe_get_input_for_slot_id( ACAMERA_FSM2ICTX_PTR( p_fsm )->context_id );
    ae_update_histogram_wbgain( p_fsm, input );
    ae_update_histogram_shading_lut( p_fsm, input );
    ae_update_histogram_black_level( p_fsm );
    ae_update_histogram_geometry( p_fsm, input );
#else
// TODO: need logic to decide input for pipeline without MCFE.
#endif
}

/**
 * configure_histogram_neq_lut() - Configure histogram neq lut based on calibration.
 *
 * Histogram configuration is written directly to isp hw registers.
 * The position of histogram is set to be on the input port.
 *
 * This function has two implementation depending on the Morgan ISP revision.
 * Revision 0 has no NEQ LUT present in Histogram engine.
 *
 * Return: None
 */
// Called from hist_fsm via ae_hist_changed event.
void configure_histogram_neq_lut( histogram_fsm_const_ptr_t p_fsm )
{
#if defined( ISP_HAS_DECOMPANDER_FSM )
#if IS_MALI_C71
    uint32_t cfg_offset = PHY_ADDR_ISP;
    // TODO2: handle case when decompander is disabled on input_formatter
    if ( !calib_mgr_lut_exists( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DECOMPANDER_CONTROL ) )
        return;

    const decompander_ctrl *p_decompander_ctrl = (const decompander_ctrl *)calib_mgr_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DECOMPANDER_CONTROL );
    uint8_t enable = p_decompander_ctrl->hist_neq_lut_enable;

#if defined( ISP_HAS_MCFE_FSM )
    uint8_t input_port = module_mcfe_get_input_for_slot_id( ACAMERA_FSM2ICTX_PTR( p_fsm )->context_id );
#else
    uint8_t input_port = ISP_MODEL_INPUT_PORT_FOR_AE_UPDATE_HIST;
#endif

    if ( ISP_HISTOGRAM_POSITION_IS_BE ) {
        cfg_offset = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
        input_port = 0;
        // If we enable here for BE_FS, BE_DECOMPANDER or BE_SHADING, we need to add input_port = 0;
        // TODO: should check on decompanding happening in inputFormatter or gammaFE.
        enable = 0;
    }

    if ( enable == 0 ) {
        LOG( LOG_INFO, "Hist Neq lut OFF" );
        switch ( input_port ) {
        case 0:
            acamera_isp_metering_hist_1_neq_lut_enable_write( cfg_offset, 0 );
            break;
        case 1:
            acamera_isp_metering_hist_2_neq_lut_enable_write( cfg_offset, 0 );
            break;
#if defined( ISP_HAS_MCFE_FSM )
        case 2:
            acamera_isp_metering_hist_3_neq_lut_enable_write( cfg_offset, 0 );
            break;
        case 3:
            acamera_isp_metering_hist_4_neq_lut_enable_write( cfg_offset, 0 );
            break;
#endif
        }
    } else {
        LOG( LOG_INFO, "Hist Neq lut ON" );
#ifdef ACAMERA_ISP_METERING_HIST_1_NEQ_LUT_POSITION_DEFAULT
        const uint8_t hist_neq_lut_pos = p_decompander_ctrl->hist_neq_lut_pos;
#endif
        const histogram_neq_lut *ptr_look =
            (histogram_neq_lut *)calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_NEQ_LUT );
        const uint32_t rows = calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_NEQ_LUT );
        int i;
        /* coverity[const]*/
        switch ( input_port ) {
        case 0:
#ifdef ACAMERA_ISP_METERING_HIST_1_NEQ_LUT_POSITION_DEFAULT
            acamera_isp_metering_hist_1_neq_lut_position_write( cfg_offset, hist_neq_lut_pos );
#endif
            acamera_isp_metering_hist_1_neq_lut_enable_write( cfg_offset, 1 );
            for ( i = 0; i < rows; i++ ) {
                acamera_isp_metering_hist_1_lut_x_write( cfg_offset, i, ptr_look[i].x );
                acamera_isp_metering_hist_1_lut_y_write( cfg_offset, i, ptr_look[i].y );
            }
            break;
        case 1:
#ifdef ACAMERA_ISP_METERING_HIST_1_NEQ_LUT_POSITION_DEFAULT
            acamera_isp_metering_hist_2_neq_lut_position_write( cfg_offset, hist_neq_lut_pos );
#endif
            acamera_isp_metering_hist_2_neq_lut_enable_write( cfg_offset, 1 );
            for ( i = 0; i < rows; i++ ) {
                acamera_isp_metering_hist_2_lut_x_write( cfg_offset, i, ptr_look[i].x );
                acamera_isp_metering_hist_2_lut_y_write( cfg_offset, i, ptr_look[i].y );
            }
            break;
#if defined( ISP_HAS_MCFE_FSM )


        case 2:
#ifdef ACAMERA_ISP_METERING_HIST_1_NEQ_LUT_POSITION_DEFAULT
            acamera_isp_metering_hist_3_neq_lut_position_write( cfg_offset, hist_neq_lut_pos );
#endif
            acamera_isp_metering_hist_3_neq_lut_enable_write( cfg_offset, 1 );
            for ( i = 0; i < rows; i++ ) {
                acamera_isp_metering_hist_3_lut_x_write( cfg_offset, i, ptr_look[i].x );
                acamera_isp_metering_hist_3_lut_y_write( cfg_offset, i, ptr_look[i].y );
            }
            break;
        case 3:
#ifdef ACAMERA_ISP_METERING_HIST_1_NEQ_LUT_POSITION_DEFAULT
            acamera_isp_metering_hist_4_neq_lut_position_write( cfg_offset, hist_neq_lut_pos );
#endif
            acamera_isp_metering_hist_4_neq_lut_enable_write( cfg_offset, 1 );
            for ( i = 0; i < rows; i++ ) {
                acamera_isp_metering_hist_4_lut_x_write( cfg_offset, i, ptr_look[i].x );
                acamera_isp_metering_hist_4_lut_y_write( cfg_offset, i, ptr_look[i].y );
            }
            break;
#endif /*defined( ISP_HAS_MCFE_FSM )*/
        }
    }
#else
    LOG( LOG_WARNING, "Histogram NEQ LUT is not present in Morgan ISP Revision 0!" );
#endif
#endif // defined(ISP_HAS_DECOMPANDER_FSM)
}

// Called from hist_fsm via ae_reconfigure/sensor_ready events.
void histogram_configure_position( histogram_fsm_const_ptr_t p_fsm )
{
    uint8_t hist_tap_fe_be; // Backend
    uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

    if ( ISP_HISTOGRAM_POSITION_IS_BE )
        hist_tap_fe_be = 2;
    else
        hist_tap_fe_be = 0;
    acamera_frontend_pipeline_frontend_histogram1_switch_write( PHY_ADDR_ISP, hist_tap_fe_be );
    acamera_frontend_pipeline_frontend_histogram2_switch_write( PHY_ADDR_ISP, hist_tap_fe_be );
    acamera_frontend_pipeline_frontend_histogram3_switch_write( PHY_ADDR_ISP, hist_tap_fe_be );
    acamera_frontend_pipeline_frontend_histogram4_switch_write( PHY_ADDR_ISP, hist_tap_fe_be );

    // Set to 1 for current context.
    acamera_isp_metering_hist_1_skip_x_write( isp_base, 1 );
    acamera_isp_metering_hist_2_skip_x_write( isp_base, 1 );
    acamera_isp_metering_hist_3_skip_x_write( isp_base, 1 );
    acamera_isp_metering_hist_4_skip_x_write( isp_base, 1 );

    if ( !ISP_HISTOGRAM_POSITION_IS_BE ) {
        // Don't do anything more if position == FE
        return;
    }

    switch ( ISP_HISTOGRAM_BE_POSITION ) {
    case AE_HISTOGRAM_TAP_AFTER_WDRGAIN:
        acamera_isp_pipeline_histogram1_isp_switch_write( isp_base, 0 );
        acamera_isp_pipeline_histogram2_isp_switch_write( isp_base, 0 );
        acamera_isp_pipeline_histogram3_isp_switch_write( isp_base, 0 );
        acamera_isp_pipeline_histogram4_isp_switch_write( isp_base, 0 );
        LOG( LOG_DEBUG, "AE_HISTOGRAM_TAP_AFTER_WDRGAIN" );
        break;
    case AE_HISTOGRAM_TAP_AFTER_FS:
        acamera_isp_pipeline_histogram1_isp_switch_write( isp_base, 1 );
        LOG( LOG_DEBUG, "AE_HISTOGRAM_TAP_AFTER_FS" );
        break;
    case AE_HISTOGRAM_TAP_AFTER_DECOMPANDER:
        acamera_isp_pipeline_histogram1_isp_switch_write( isp_base, 2 );
        LOG( LOG_DEBUG, "AE_HISTOGRAM_TAP_AFTER_DECOMPANDER" );
        break;
    case AE_HISTOGRAM_TAP_AFTER_SHADING:
        acamera_isp_pipeline_histogram1_isp_switch_write( isp_base, 3 );
        LOG( LOG_DEBUG, "AE_HISTOGRAM_TAP_AFTER_SHADING" );
        break;
    // Skip case AE_HISTOGRAM_TAP_AFTER_COMPAND: as hist needs to be squared (gamma_sqrt).
    default:
        LOG( LOG_ERR, "Unsupported hist be value %#x.", ISP_HISTOGRAM_BE_POSITION );
        break;
    }
}
