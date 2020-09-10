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
#include "acamera_math.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_MESH_SHADING

#include "acamera_shading_mem_config.h"
#define acamera_shading_array_data_write acamera_shading_mem_array_data_write

#ifndef AWB_LIGHT_SOURCE_A
#define AWB_LIGHT_SOURCE_A 0x01
#endif

#ifndef AWB_LIGHT_SOURCE_D40
#define AWB_LIGHT_SOURCE_D40 0x02
#endif

#ifndef AWB_LIGHT_SOURCE_D50
#define AWB_LIGHT_SOURCE_D50 0x03
#endif

#define MESH_SHADING_LS_A_BANK 0
#define MESH_SHADING_LS_D40_BANK 1
#define MESH_SHADING_LS_D65_BANK 2

void mesh_shading_modulate_strength( mesh_shading_fsm_ptr_t p_fsm )
{
    int32_t total_gain = 0;

    if ( get_context_param( ACAMERA_FSM2ICTX_PTR( p_fsm ), ISP_MODULES_MANUAL_SHADING_PARAM ) == 0 ) {
        WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_CMOS_TOTAL_GAIN, CMD_DIRECTION_GET, NULL, (uint32_t *)&total_gain );
        uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );
        uint16_t strength = calc_modulation_u16( log2_gain, calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_MESH_SHADING_STRENGTH ), calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_MESH_SHADING_STRENGTH ) );
        acamera_isp_mesh_shading_mesh_strength_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, strength );
    }
}

// Mode - one of linear, native, fs_lin or fs_hdr. See EWDRModeID enum.
void mesh_shading_reload( mesh_shading_fsm_ptr_t p_fsm )
{
    int i, j, k;
    const uint8_t *mesh_page[4][3] = {{NULL}};

    // Temporary for mesh shading light switching.
    // @todo: need to clarify where these values should come from (cal table, etc)
    acamera_isp_mesh_shading_mesh_page_r_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 0 );
    acamera_isp_mesh_shading_mesh_page_g_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );
    acamera_isp_mesh_shading_mesh_page_b_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 2 );
    acamera_isp_mesh_shading_mesh_width_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 31 );
    acamera_isp_mesh_shading_mesh_height_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 31 );
    acamera_isp_mesh_shading_mesh_scale_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );
    acamera_isp_mesh_shading_mesh_alpha_mode_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 2 );

    mesh_page[0][0] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_A_R );
    mesh_page[0][1] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_A_G );
    mesh_page[0][2] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_A_B );
    mesh_page[1][0] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_TL84_R );
    mesh_page[1][1] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_TL84_G );
    mesh_page[1][2] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_TL84_B );
    mesh_page[2][0] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_D65_R );
    mesh_page[2][1] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_D65_G );
    mesh_page[2][2] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_D65_B );
    mesh_page[3][0] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_D65_R );
    mesh_page[3][1] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_D65_G );
    mesh_page[3][2] = calib_mgr_u8_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_SHADING_LS_D65_B );

    for ( i = 0; i < 3; ++i ) {
        for ( j = 0; j < 32; ++j ) {
            for ( k = 0; k < 32; ++k ) {
                const int ii = i << 10; // Multiply once by 32 * 32
                const int jj = j << 5;  // Multiply once by 32

                const uint32_t index = ii + jj + k;
                const uint32_t value = (uint32_t)mesh_page[0][i][jj + k] +
                                       ( (uint32_t)mesh_page[1][i][jj + k] << 8 ) +
                                       ( (uint32_t)mesh_page[2][i][jj + k] << 16 ) +
                                       ( (uint32_t)mesh_page[3][i][jj + k] << 24 );

                acamera_shading_mem_array_data_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base,
                                                      index,
                                                      value );
            }
        }
    }

    acamera_isp_mesh_shading_mesh_show_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 0 );
}

/**
 * mesh_shading_init() - FSM handler function
 *
 * @p_fsm: Pointer to mesh_shading FSM.
 *
 * Return: None
 */
void mesh_shading_init( mesh_shading_fsm_ptr_t p_fsm )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

    /* @todo should these be located in a calibration table? */
    p_fsm->temperature_threshold[0] = 3000;
    p_fsm->temperature_threshold[1] = 3900;
    p_fsm->temperature_threshold[2] = 4100;
    p_fsm->temperature_threshold[3] = 4900;
    p_fsm->temperature_threshold[4] = 0;
    p_fsm->temperature_threshold[5] = 0;
    p_fsm->temperature_threshold[6] = 0;
    p_fsm->temperature_threshold[7] = 0;

    p_fsm->shading_alpha = 0;

    acamera_isp_mesh_shading_mesh_alpha_bank_r_write( isp_base, MESH_SHADING_LS_D65_BANK );
    acamera_isp_mesh_shading_mesh_alpha_bank_g_write( isp_base, MESH_SHADING_LS_D65_BANK );
    acamera_isp_mesh_shading_mesh_alpha_bank_b_write( isp_base, MESH_SHADING_LS_D65_BANK );

    acamera_isp_mesh_shading_mesh_alpha_r_write( isp_base, 0 );
    acamera_isp_mesh_shading_mesh_alpha_g_write( isp_base, 0 );
    acamera_isp_mesh_shading_mesh_alpha_b_write( isp_base, 0 );

    acamera_isp_pipeline_bypass_mesh_shading_write( isp_base, 0 );
    acamera_isp_mesh_shading_enable_write( isp_base, 1 );
}

/**
 * mesh_shading_reload_calibration() - FSM handler function
 *
 * @p_fsm: Pointer to mesh_shading FSM.
 *
 * Return: None
 */
void mesh_shading_reload_calibration( mesh_shading_fsm_ptr_t p_fsm )
{
    mesh_shading_reload( p_fsm );
}

/**
 * mesh_shading_update_hw() - FSM handler function
 *
 * @p_fsm: Pointer to mesh_shading FSM.
 *
 * Return: None
 */
void mesh_shading_update_hw( mesh_shading_fsm_ptr_t p_fsm )
{
    if ( get_context_param( ACAMERA_FSM2ICTX_PTR( p_fsm ), ISP_MODULES_MANUAL_SHADING_PARAM ) == 0 ) {

        int32_t mesh_shading_bank = MESH_SHADING_LS_A_BANK;

        acamera_cmd_wb_info wb_info;
        WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_WB_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&wb_info );

        p_fsm->shading_alpha = 0;

        // LSC is completely based on alpha blending and the AWB color temp.

        // If current temp less < 3000 go to A, no blending.
        if ( wb_info.temperature_detected < p_fsm->temperature_threshold[0] ) {
            mesh_shading_bank = MESH_SHADING_LS_A_BANK;
        }

        // If current temp between 3000 and 3900 go to A and alpha blend.
        else if ( ( wb_info.temperature_detected >= p_fsm->temperature_threshold[0] ) && ( wb_info.temperature_detected < p_fsm->temperature_threshold[1] ) ) {

            mesh_shading_bank = MESH_SHADING_LS_A_BANK;

            if ( p_fsm->temperature_threshold[1] != p_fsm->temperature_threshold[0] ) {
                p_fsm->shading_alpha = ( 255 * ( wb_info.temperature_detected - p_fsm->temperature_threshold[0] ) ) / ( p_fsm->temperature_threshold[1] - p_fsm->temperature_threshold[0] );
            }
        }

        // If current temp between 3900 and 4100 go to D40, no blending.
        else if ( ( wb_info.temperature_detected >= p_fsm->temperature_threshold[1] ) && ( wb_info.temperature_detected < p_fsm->temperature_threshold[2] ) ) {
            mesh_shading_bank = MESH_SHADING_LS_D40_BANK;
        }

        // If current temp between 4100 and 4900 go to D40 and alpha blend.
        else if ( ( wb_info.temperature_detected >= p_fsm->temperature_threshold[2] ) && ( wb_info.temperature_detected < p_fsm->temperature_threshold[3] ) ) {

            mesh_shading_bank = MESH_SHADING_LS_D40_BANK;

            if ( p_fsm->temperature_threshold[3] != p_fsm->temperature_threshold[2] ) {
                p_fsm->shading_alpha = ( 255 * ( wb_info.temperature_detected - p_fsm->temperature_threshold[2] ) ) / ( p_fsm->temperature_threshold[3] - p_fsm->temperature_threshold[2] );
            }
        }

        // If current temp > 4900 go to D65, no blending.
        else if ( wb_info.temperature_detected >= p_fsm->temperature_threshold[3] ) {
            mesh_shading_bank = MESH_SHADING_LS_D65_BANK;
        }


        acamera_isp_mesh_shading_mesh_alpha_bank_r_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, mesh_shading_bank );
        acamera_isp_mesh_shading_mesh_alpha_bank_g_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, mesh_shading_bank );
        acamera_isp_mesh_shading_mesh_alpha_bank_b_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, mesh_shading_bank );

        acamera_isp_mesh_shading_mesh_alpha_r_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->shading_alpha );
        acamera_isp_mesh_shading_mesh_alpha_g_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->shading_alpha );
        acamera_isp_mesh_shading_mesh_alpha_b_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->shading_alpha );
    }

    mesh_shading_modulate_strength( p_fsm );
}

void mesh_shading_deinit( mesh_shading_fsm_ptr_t p_fsm )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    acamera_isp_mesh_shading_enable_write( isp_base, 0 );
    acamera_isp_pipeline_bypass_mesh_shading_write( isp_base, 1 );
}
