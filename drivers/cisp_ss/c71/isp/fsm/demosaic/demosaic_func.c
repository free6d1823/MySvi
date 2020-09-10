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

static void demosaic_load_configuration( demosaic_fsm_ptr_t p_fsm )
{
    if ( !calib_mgr_lut_exists( ACAMERA_FSM2CM_PTR( p_fsm ),
                                CALIBRATION_DEMOSAIC_CONFIG ) ) {
        LOG( LOG_ERR, "CALIBRATION_DEMOSAIC_CONFIG does not exist for this context." );
        return;
    }

    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    const uint16_t *config = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ),
                                                    CALIBRATION_DEMOSAIC_CONFIG );
    acamera_isp_demosaic_aa_offset_write( isp_base, config[0] );
    acamera_isp_demosaic_aa_slope_write( isp_base, config[1] );
    acamera_isp_demosaic_aa_thresh_write( isp_base, config[2] );
    acamera_isp_demosaic_ac_offset_write( isp_base, config[3] );
    acamera_isp_demosaic_ac_slope_write( isp_base, config[4] );
    acamera_isp_demosaic_ac_thresh_write( isp_base, config[5] );
    acamera_isp_demosaic_fc_alias_slope_write( isp_base, config[6] );
    acamera_isp_demosaic_fc_alias_thresh_write( isp_base, config[7] );
    acamera_isp_demosaic_fc_slope_write( isp_base, config[8] );
    acamera_isp_demosaic_lum_thresh_write( isp_base, config[9] );
    acamera_isp_demosaic_min_d_strength_write( isp_base, config[10] );
    acamera_isp_demosaic_min_ud_strength_write( isp_base, config[11] );
    acamera_isp_demosaic_np_off_write( isp_base, config[12] );
    acamera_isp_demosaic_np_off_reflect_write( isp_base, config[13] );
    acamera_isp_demosaic_np_offset_write( isp_base, config[14] );
    acamera_isp_demosaic_sad_amp_write( isp_base, config[15] );
    acamera_isp_demosaic_sat_offset_write( isp_base, config[16] );
    acamera_isp_demosaic_sat_slope_write( isp_base, config[17] );
    acamera_isp_demosaic_sat_thresh_write( isp_base, config[18] );
    acamera_isp_demosaic_uu_offset_write( isp_base, config[19] );
    acamera_isp_demosaic_uu_thresh_write( isp_base, config[20] );
    acamera_isp_demosaic_va_offset_write( isp_base, config[21] );
    acamera_isp_demosaic_va_slope_write( isp_base, config[22] );
    acamera_isp_demosaic_va_thresh_write( isp_base, config[23] );
    acamera_isp_demosaic_vh_offset_write( isp_base, config[24] );
    acamera_isp_demosaic_vh_slope_write( isp_base, config[25] );
    acamera_isp_demosaic_vh_thresh_write( isp_base, config[26] );
    acamera_isp_demosaic_sharpen_alg_select_write( isp_base, config[27] );
}

static void demosaic_weight_lut_reload( demosaic_fsm_ptr_t p_fsm )
{

    const uint8_t *demosaic_lut = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DEMOSAIC );
    const uint32_t demosaic_lut_size = calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DEMOSAIC );

    uint32_t i;
    for ( i = 0; i < demosaic_lut_size; i++ ) {
        acamera_isp_demosaic_lut_weight_lut_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i, demosaic_lut[i] );
    }
}

/**
 *   @brief     Initialise demosaic.
 *
 *   @param     p_fsm Pointer to FSM private data
 *   @details   Initialise demosaic to default settings.
 */
void demosaic_init( demosaic_fsm_ptr_t p_fsm )
{
    acamera_isp_pipeline_bypass_demosaic_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 0 );
}

/**
 *   @brief     Reload static calibration LUTs.
 *
 *   @param     p_fsm Pointer to FSM private data
 *   @details   Reload static calibration lookup tables.
 */
void demosaic_reload_calibration( demosaic_fsm_ptr_t p_fsm )
{
    demosaic_load_configuration( p_fsm );
    demosaic_weight_lut_reload( p_fsm );
}

/**
 *   @brief     Deinitialise demosaic.
 *
 *   @param     p_fsm Pointer to FSM private data
 *   @details   Deinitialise demosaic.
 */
void demosaic_deinit( demosaic_fsm_ptr_t p_fsm )
{
    acamera_isp_pipeline_bypass_demosaic_write(
        ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );
}