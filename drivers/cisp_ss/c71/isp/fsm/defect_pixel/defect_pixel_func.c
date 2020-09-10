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

#include "acamera_defect_pixel_mem_config.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "acamera_math.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_DEFECT_PIXEL

#define FRAME_COUNTER_LIMIT 16
#define ACAMERA_FW_SHP_DETECTED_MAXIMUM 1023

// We don't currently use static defect pixels calibration.
// If required put it on context parameter.
static uint32_t global_calibrate_bad_pixels = 0;

static void defect_pixel_lut_reload( defect_pixel_fsm_ptr_t p_fsm )
{
    const uint32_t *defect_pixel_lut = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DEFECT_PIXEL );
    const uint32_t defect_pixel_lut_size = calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DEFECT_PIXEL );
    const uint32_t defect_pixel_lut_hw_size = ( ACAMERA_DEFECT_PIXEL_MEM_SIZE >> 2 );
    const uint32_t defect_pixel_lut_min_size = ( defect_pixel_lut_size < defect_pixel_lut_hw_size ) ? defect_pixel_lut_size : defect_pixel_lut_hw_size;

    if ( defect_pixel_lut_size != defect_pixel_lut_hw_size ) {
        LOG( LOG_ERR, "CALIBRATION_DEFECT_PIXEL has wrong size: expected %d got %d", defect_pixel_lut_hw_size, defect_pixel_lut_size );
    }

    uint32_t i;

    for ( i = 0; i < defect_pixel_lut_min_size; i++ ) {
        acamera_defect_pixel_mem_array_data_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i, defect_pixel_lut[i] );
    }

    // Update defect pixel count value
    acamera_isp_defect_pixel_defect_pixel_count_in_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, defect_pixel_lut_min_size );

    // Reset pointer_reset register to apply new pixel count value
    acamera_isp_defect_pixel_pointer_reset_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );
    acamera_isp_defect_pixel_pointer_reset_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 0 );
}

/**
 *   @brief     Initialise defect pixel.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   Initialise defect pixel to default settings.
 */
void defect_pixel_init( defect_pixel_fsm_ptr_t p_fsm )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;


    p_fsm->hp_strength = ACAMERA_ISP_RAW_FRONTEND_DP_THRESHOLD_DEFAULT;

    acamera_isp_defect_pixel_defect_pixel_count_in_write( isp_base,
                                                          ACAMERA_ISP_DEFECT_PIXEL_DEFECT_PIXEL_COUNT_IN_DEFAULT );

    acamera_isp_defect_pixel_pointer_reset_write( isp_base, 0 );
    acamera_isp_defect_pixel_show_reference_write( isp_base, 0 );
    acamera_isp_defect_pixel_show_static_defect_pixels_write( isp_base, 0 );
    acamera_isp_defect_pixel_enable_write( isp_base, 1 );
    acamera_isp_pipeline_bypass_defect_pixel_write( isp_base, 0 );


    // Strength for counting static hot pixels
    acamera_isp_raw_frontend_dp_threshold_write( isp_base, p_fsm->hp_strength );

    p_fsm->hp_started = 0;
}

/**
 *   @brief     Reload static calibration LUTs.
 *
 *   @param     p_fsm  Pointer to FSM private data
 *
 *   @details   Reload static calibration lookup tables.
 */
void defect_pixel_reload_calibration( defect_pixel_fsm_ptr_t p_fsm )
{
    defect_pixel_lut_reload( p_fsm );
}

/**
 *   @brief     Reconfigure defect pixel.
 *
 *   @param     p_fsm   Pointer to FSM private data
 *
 *   @details   Reconfigure defect pixel on <fsm_update_hw> event.
 */
void defect_pixel_update_hw( defect_pixel_fsm_ptr_t p_fsm )
{
    // For static hot pixels calibration.
    if ( global_calibrate_bad_pixels == 1 ) {
        if ( p_fsm->hp_started == 0 ) {
            // Start hot pixel calibration
            // Set exposure to minimum
            acamera_cmd_exposure_target exp_target;
            exp_target.exposure_log2 = 0;
            exp_target.exposure_ratio = 0;
            WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_EXPOSURE_TARGET, CMD_DIRECTION_SET, (const uint32_t *)&exp_target, NULL );

            p_fsm->hp_started = 1;
            p_fsm->frame_counter = FRAME_COUNTER_LIMIT;
            // Setup HP strength
            p_fsm->hp_strength = ACAMERA_ISP_RAW_FRONTEND_DP_THRESHOLD_DEFAULT * 4;
            acamera_isp_raw_frontend_dp_threshold_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->hp_strength );
        } else {
            // Start actual calibration
            if ( ( p_fsm->frame_counter <= FRAME_COUNTER_LIMIT / 2 ) && ( p_fsm->hp_started == 1 ) ) {
                p_fsm->hp_started = 2;
                // Setup ISP
                acamera_isp_defect_pixel_enable_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );            // Enable calibration
                acamera_isp_defect_pixel_pointer_reset_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );     // Reset
                acamera_isp_defect_pixel_pointer_reset_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 0 );     // Reset
                acamera_isp_defect_pixel_detection_trigger_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 ); // Detection trigger
            }
            // Wait for the end
            else if ( p_fsm->frame_counter == 0 ) {
                // Check that we found enough hot pixels, if not decrease sthrength
                uint16_t dp_pixel_cnt = acamera_isp_defect_pixel_defect_pixel_count_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
                if ( ( dp_pixel_cnt < ACAMERA_FW_SHP_DETECTED_MAXIMUM ) && ( p_fsm->hp_strength != 0 ) ) {
                    p_fsm->hp_strength = p_fsm->hp_strength * 15 >> 4;
                    acamera_isp_raw_frontend_dp_threshold_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->hp_strength );
                    p_fsm->frame_counter = FRAME_COUNTER_LIMIT;
                } else {
                    if ( ( dp_pixel_cnt < ACAMERA_FW_SHP_DETECTED_MAXIMUM ) && ( p_fsm->hp_strength == 0 ) ) {
                        LOG( LOG_ERR, "Defect pixel calibration procedure fails! Detected dp pixles: %u, required dp pixels: %u!", dp_pixel_cnt, ACAMERA_FW_SHP_DETECTED_MAXIMUM );
                    }
                    // Finish calibration
                    acamera_isp_defect_pixel_detection_trigger_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 0 ); // Detection trigger
                    global_calibrate_bad_pixels = 0;
                    p_fsm->hp_started = 0;
                    p_fsm->hp_strength = ACAMERA_ISP_RAW_FRONTEND_DP_THRESHOLD_DEFAULT;
                    acamera_isp_raw_frontend_dp_threshold_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->hp_strength );
                }
            }
            p_fsm->frame_counter = p_fsm->frame_counter - 1;
        }
    }
}

/**
 *   @brief     Deinitialise defect pixel.
 *
 *   @param     p_fsm   Pointer to fsm private data
 *
 *   @details   Deinitialise defect pixel.
 */
void defect_pixel_deinit( defect_pixel_fsm_ptr_t p_fsm )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    acamera_isp_defect_pixel_enable_write( isp_base, 0 );
    acamera_isp_pipeline_bypass_defect_pixel_write( isp_base, 1 );
}