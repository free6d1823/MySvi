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
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "acamera_math.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_SHARPENING

void sharpening_update_hw( sharpening_fsm_t *p_fsm )
{
    int32_t total_gain = 0;
    uint16_t log2_gain;
    uint16_t alt_d, alt_ud;
    uint32_t sharp_alt_d_idx;
    uint32_t sharp_alt_ud_idx;
    uint16_t alt_du = 0;
    uint32_t sharp_alt_du_idx = CALIBRATION_SHARP_ALT_DU;
    const modulation_entry_t *sharp_alt_du_table_ptr = calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), sharp_alt_du_idx );
    const modulation_entry_t *sharp_alt_d_table_ptr;
    const modulation_entry_t *sharp_alt_ud_table_ptr;

    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    WRAP_GENERAL_CMD( p_ictx, CMD_ID_CMOS_TOTAL_GAIN, CMD_DIRECTION_GET, NULL, (uint32_t *)&total_gain );
    log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );

    sharp_alt_d_idx = CALIBRATION_SHARP_ALT_D;
    sharp_alt_ud_idx = CALIBRATION_SHARP_ALT_UD;
    sharp_alt_d_table_ptr = calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), sharp_alt_d_idx );
    sharp_alt_ud_table_ptr = calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), sharp_alt_ud_idx );

    const uint32_t system_manual_directional_sharpening = get_context_param( p_ictx, SYSTEM_MANUAL_DIRECTIONAL_SHARPENING_PARAM );
    const uint32_t system_manual_un_directional_sharpening = get_context_param( p_ictx, SYSTEM_MANUAL_UN_DIRECTIONAL_SHARPENING_PARAM );

    if ( system_manual_directional_sharpening != 0 ) {
        // Do not update values if manual mode
        alt_d = get_context_param( p_ictx, SYSTEM_DIRECTIONAL_SHARPENING_TARGET_PARAM );
    } else {
        alt_d = calc_modulation_u16( log2_gain,
                                     sharp_alt_d_table_ptr,
                                     calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ),
                                                         sharp_alt_d_idx ) );

        alt_du = calc_modulation_u16( log2_gain,
                                      sharp_alt_du_table_ptr,
                                      calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ),
                                                          sharp_alt_du_idx ) );

        alt_d = ( alt_d * p_fsm->sharpening_mult ) / 128;
        if ( alt_d >= ( 1 << ACAMERA_ISP_DEMOSAIC_SHARP_ALT_D_DATASIZE ) ) {
            alt_d = ( 1 << ACAMERA_ISP_DEMOSAIC_SHARP_ALT_D_DATASIZE ) - 1;
        }

        set_context_param( p_ictx, SYSTEM_DIRECTIONAL_SHARPENING_TARGET_PARAM, alt_d );
    }

    if ( system_manual_un_directional_sharpening != 0 ) {
        //  Do not update values if manual mode
        alt_ud = get_context_param( p_ictx, SYSTEM_UN_DIRECTIONAL_SHARPENING_TARGET_PARAM );
    } else {
        alt_ud = calc_modulation_u16( log2_gain,
                                      sharp_alt_ud_table_ptr,
                                      calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ),
                                                          sharp_alt_ud_idx ) );

        alt_ud = ( alt_ud * p_fsm->sharpening_mult ) / 128;
        if ( alt_ud >= ( 1 << ACAMERA_ISP_DEMOSAIC_SHARP_ALT_UD_DATASIZE ) ) {
            alt_ud = ( 1 << ACAMERA_ISP_DEMOSAIC_SHARP_ALT_UD_DATASIZE ) - 1;
        }

        set_context_param( p_ictx, SYSTEM_UN_DIRECTIONAL_SHARPENING_TARGET_PARAM, alt_ud );
    }

    if ( get_context_param( p_ictx, ISP_MODULES_MANUAL_DEMOSAIC_PARAM ) == 0 ) {
        if ( system_manual_directional_sharpening == 0 ) {
            //  Do not update values if manual mode

            acamera_isp_demosaic_sharp_alt_ld_write( p_ictx->settings.isp_base, alt_d );
            acamera_isp_demosaic_sharp_alt_ldu_write( p_ictx->settings.isp_base, alt_du );
        }
        if ( system_manual_un_directional_sharpening == 0 ) {
            acamera_isp_demosaic_sharp_alt_lu_write( p_ictx->settings.isp_base, alt_ud );
        } //  Do not update values if manual mode
    }
}
