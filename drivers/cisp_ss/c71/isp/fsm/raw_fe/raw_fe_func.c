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

#include "acamera_isp_config.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"

/**
 *   @brief     Initialise FSM.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   Initialise corresponding HW/SW modules to initial status.
 */
void raw_fe_init( raw_fe_fsm_ptr_t p_fsm )
{
}

/**
 *   @brief     Configure FSM.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   Configure corresponding HW/SW modules to given mode of operation with given parameters.
 */
void raw_fe_config( raw_fe_fsm_ptr_t p_fsm )
{
    const int32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    acamera_isp_pipeline_bypass_raw_frontend_write( isp_base, 0 );
    acamera_isp_raw_frontend_show_dynamic_defect_pixel_write( isp_base,
                                                              ACAMERA_ISP_RAW_FRONTEND_SHOW_DYNAMIC_DEFECT_PIXEL_DEFAULT );
}

/**
 *   @brief     Update FSM hardware.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   Update corresponding HW/SW modules on timing event generated by ISP HW or Algorithm.
 */
void raw_fe_update_hw( raw_fe_fsm_ptr_t p_fsm )
{
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( get_context_param( p_ictx, ISP_MODULES_MANUAL_RAW_FRONTEND_PARAM ) ) {
        return;
    }

    const int32_t isp_base = p_ictx->settings.isp_base;
    acamera_calib_mgr_entry_t *p_cmgr = ACAMERA_FSM2CM_PTR( p_fsm );
    int32_t total_gain = 0;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_CMOS_TOTAL_GAIN, CMD_DIRECTION_GET, NULL, (uint32_t *)&total_gain ) ) {
        return;
    }

    const uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );

    const uint16_t dp_slope = calc_modulation_u16( log2_gain,
                                                   calib_mgr_mod16_lut_get( p_cmgr, CALIBRATION_DP_SLOPE ),
                                                   calib_mgr_lut_rows( p_cmgr, CALIBRATION_DP_THRESHOLD ) );

    const uint16_t dp_threshold = calc_modulation_u16( log2_gain,
                                                       calib_mgr_mod16_lut_get( p_cmgr, CALIBRATION_DP_THRESHOLD ),
                                                       calib_mgr_lut_rows( p_cmgr, CALIBRATION_DP_SLOPE ) );

    acamera_isp_raw_frontend_dp_slope_write( isp_base, dp_slope );
    acamera_isp_raw_frontend_dp_threshold_write( isp_base, dp_threshold );
}


/**
 *   @brief      Reload FSM calibration LUTs.
 *
 *   @param      p_fsm  Pointer to FSM private data
 *
 *   @details    Reloads corresponding calibration LUTs and updates HW.
 */
void raw_fe_reload_calibration( raw_fe_fsm_ptr_t p_fsm )
{

    /* raw fe stands for raw front end and is a hardware block in the pipeline
    containing the dynamic defect pixel and green equalizer blocks.

    Once the parameters are setup the blocks do not need any extra attention.

    */
    const int32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

    if ( calib_mgr_lut_exists( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_RAW_FRONTEND_CONFIG ) ) {
        const uint16_t *config = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_RAW_FRONTEND_CONFIG );

        acamera_isp_raw_frontend_hpdev_threshold_write( isp_base, *config++ ); // dpdev threshold
        acamera_isp_raw_frontend_line_thresh_write( isp_base, *config++ );     // dp line thresh
        acamera_isp_raw_frontend_ge_slope_write( isp_base, *config++ );        // ge slope
        acamera_isp_raw_frontend_ge_sens_write( isp_base, *config++ );         // ge sens
        acamera_isp_raw_frontend_ge_threshold_write( isp_base, *config++ );    // ge threshold
        acamera_isp_raw_frontend_ge_strength_write( isp_base, *config++ );     // ge strength
        acamera_isp_raw_frontend_thresh_long_write( isp_base, *config++ );     // Thresh Long
        acamera_isp_raw_frontend_thresh_short_write( isp_base, *config++ );    // Thresh Short

        acamera_isp_raw_frontend_ge_enable_write( isp_base, 1 );
        acamera_isp_raw_frontend_dp_enable_write( isp_base, 1 );
    } else {
        LOG( LOG_ERR, "Cannot configure raw_fe, calibration table CALIBRATION_RAW_FRONTEND_CONFIG not found!" );
        acamera_isp_raw_frontend_ge_enable_write( isp_base, 0 );
        acamera_isp_raw_frontend_dp_enable_write( isp_base, 0 );
    }
}

/**
 *   @brief     De-initialise FSM.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   De-initialise corresponding HW/SW modules to reset status and release all allocated resources.
 */
void raw_fe_deinit( raw_fe_fsm_ptr_t p_fsm )
{
    const int32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    acamera_isp_pipeline_bypass_raw_frontend_write( isp_base, 1 );
    acamera_isp_raw_frontend_ge_enable_write( isp_base, 0 );
    acamera_isp_raw_frontend_dp_enable_write( isp_base, 0 );
}