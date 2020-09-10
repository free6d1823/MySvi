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
#define LOG_MODULE LOG_MODULE_COLOR_MATRIX

#ifndef AWB_LIGHT_SOURCE_A
#define AWB_LIGHT_SOURCE_A 0x01
#endif

#ifndef AWB_LIGHT_SOURCE_D40
#define AWB_LIGHT_SOURCE_D40 0x02
#endif

#ifndef AWB_LIGHT_SOURCE_D50
#define AWB_LIGHT_SOURCE_D50 0x03
#endif

// threshold for the LSC table hysterisis.
#define AWB_DLS_LIGHT_SOURCE_D40_D50_BORDER_low ( ( ( AWB_LIGHT_SOURCE_D50_TEMPERATURE + AWB_LIGHT_SOURCE_D40_TEMPERATURE ) >> 1 ) - 200 )
#define AWB_DLS_LIGHT_SOURCE_D40_D50_BORDER_high ( ( ( AWB_LIGHT_SOURCE_D40_TEMPERATURE + AWB_LIGHT_SOURCE_D50_TEMPERATURE ) >> 1 ) + 200 )
#define AWB_DLS_LIGHT_SOURCE_A_D40_BORDER_low ( ( ( AWB_LIGHT_SOURCE_A_TEMPERATURE + AWB_LIGHT_SOURCE_D40_TEMPERATURE ) >> 1 ) - 200 )
#define AWB_DLS_LIGHT_SOURCE_A_D40_BORDER_high ( ( ( AWB_LIGHT_SOURCE_D40_TEMPERATURE + AWB_LIGHT_SOURCE_A_TEMPERATURE ) >> 1 ) + 200 )

//==============Math Functions========================================================
void matrix_matrix_multiply( int16_t *a1, int16_t *a2, int16_t *result, int dim1, int dim2, int dim3 )
{
    int i, j, k;

    for ( i = 0; i < dim1; ++i ) {
        for ( j = 0; j < dim3; ++j ) {

            int32_t temp = 0;
            for ( k = 0; k < dim2; ++k ) {
                temp += ( ( (int32_t)a1[i * dim2 + k] * a2[k * dim3 + j] ) >> 8 );
            }

            result[i * dim3 + j] = (int16_t)temp;
        }
    }
}

void matrix_vector_multiply( int16_t *m, uint16_t *v, uint16_t *result, int dim1, int dim2 )
{
    int i, j;

    for ( i = 0; i < dim1; ++i ) {

        int32_t temp = 0;
        for ( j = 0; j < dim2; ++j ) {
            temp += ( ( (int32_t)m[i * dim2 + j] * v[j] ) >> 8 );
        }

        result[i] = (uint16_t)temp;
    }
}

uint16_t complement_to_direct( int16_t v )
{
    uint16_t result;

    if ( v >= 0 )
        result = v;
    else {
        result = -v;
        result |= ( 1 << 15 );
    }

    return result;
}

int16_t direct_to_complement( uint16_t v )
{
    int16_t result = v & ( ~( 1 << 15 ) );

    if ( v & ( 1 << 15 ) )
        result = -result;

    return result;
}

//==============Saturation Related Functions========================================================
void saturation_modulate_strength( color_matrix_fsm_ptr_t p_fsm )
{
    int32_t total_gain = 0;
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    WRAP_GENERAL_CMD( p_ictx, CMD_ID_CMOS_TOTAL_GAIN, CMD_DIRECTION_GET, NULL, (uint32_t *)&total_gain );

    uint16_t log2_gain = total_gain >> ( LOG2_GAIN_SHIFT - 8 );

    uint32_t ccm_saturation_table_idx = CALIBRATION_SATURATION_STRENGTH;
    const modulation_entry_t *ccm_saturation_table = calib_mgr_mod16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), ccm_saturation_table_idx );
    uint32_t ccm_saturation_table_len = calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), ccm_saturation_table_idx );
    uint16_t strength = calc_modulation_u16( log2_gain, ccm_saturation_table, ccm_saturation_table_len );

    set_context_param( p_ictx, SYSTEM_SATURATION_TARGET_PARAM, strength );
}

static void color_mat_calculate_saturation_matrix( int16_t *saturation_matrix, uint8_t saturation )
{
    static const int16_t identity[9] = {0x0100, 0x0000, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000, 0x0000, 0x0100};
    static const int16_t black_white[9] = {0x004c, 0x0096, 0x001d, 0x004c, 0x0096, 0x001d, 0x004c, 0x0096, 0x001d};
    int i;
    int16_t alpha;
    // (1 - saturation)
    alpha = (int16_t)0x100 - ( (uint16_t)saturation << 1 );

    for ( i = 0; i < 9; ++i ) {
        int16_t result;
        // (1. - saturation) * _black_white
        result = ( (int32_t)alpha * black_white[i] + 0x80 ) >> 8;
        // += (saturation * _identity)
        result = result + ( ( (int32_t)identity[i] * ( (uint16_t)saturation << 1 ) + 0x80 ) >> 8 );
        saturation_matrix[i] = result;
    }
}

//==============Color Matrix Related Functions========================================================
void color_matrix_recalculate( color_matrix_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    // Saturation matrix
    if ( get_context_param( p_ictx, SYSTEM_MANUAL_SATURATION_PARAM ) == 0 ) { //  Do not update values if manual mode

        saturation_modulate_strength( p_fsm );
    }

    color_mat_calculate_saturation_matrix( p_fsm->color_saturation_matrix, (uint8_t)get_context_param( p_ictx, SYSTEM_SATURATION_TARGET_PARAM ) );
    // New colour management:
    matrix_matrix_multiply( p_fsm->color_saturation_matrix, p_fsm->color_correction_matrix, p_fsm->color_matrix, 3, 3, 3 );
}

void color_matrix_setup( int16_t *p_matrix, const uint16_t *source_matrix, int16_t size )
{
    int i;

    for ( i = 0; i < size; i++ ) {
        p_matrix[i] = direct_to_complement( source_matrix[i] );
    }
}

static void rgb2rgb_matrix_update( uint32_t isp_base, int16_t *CCM_A, int16_t *CCM_B )
{
    acamera_isp_out_format_rgb2rgb_coef_a_11_write( isp_base, complement_to_direct( CCM_A[0] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_12_write( isp_base, complement_to_direct( CCM_A[1] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_13_write( isp_base, complement_to_direct( CCM_A[2] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_21_write( isp_base, complement_to_direct( CCM_A[3] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_22_write( isp_base, complement_to_direct( CCM_A[4] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_23_write( isp_base, complement_to_direct( CCM_A[5] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_31_write( isp_base, complement_to_direct( CCM_A[6] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_32_write( isp_base, complement_to_direct( CCM_A[7] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_33_write( isp_base, complement_to_direct( CCM_A[8] ) );

    acamera_isp_out_format_rgb2rgb_coef_a_14_write( isp_base, complement_to_direct( CCM_A[9] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_24_write( isp_base, complement_to_direct( CCM_A[10] ) );
    acamera_isp_out_format_rgb2rgb_coef_a_34_write( isp_base, complement_to_direct( CCM_A[11] ) );

    if ( CCM_B != NULL ) {
        acamera_isp_out_format_rgb2rgb_coef_b_1_write( isp_base, complement_to_direct( CCM_B[0] ) );
        acamera_isp_out_format_rgb2rgb_coef_b_2_write( isp_base, complement_to_direct( CCM_B[1] ) );
        acamera_isp_out_format_rgb2rgb_coef_b_3_write( isp_base, complement_to_direct( CCM_B[2] ) );
    } else {
        acamera_isp_out_format_rgb2rgb_coef_b_1_write( isp_base, complement_to_direct( 0 ) );
        acamera_isp_out_format_rgb2rgb_coef_b_2_write( isp_base, complement_to_direct( 0 ) );
        acamera_isp_out_format_rgb2rgb_coef_b_3_write( isp_base, complement_to_direct( 0 ) );
    }
}

void color_matrix_write( color_matrix_fsm_ptr_t p_fsm )
{
    int16_t *p_cm_target = p_fsm->manual_CCM ? p_fsm->manual_color_matrix : p_fsm->color_matrix;

    // LUV
    if ( !( acamera_isp_out_format_rgb2xyz_bypass_read( PHY_ADDR_ISP ) & 0x1 ) ) {

        acamera_isp_out_format_rgb2xyz_coef_a_11_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[0] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_12_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[1] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_13_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[2] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_21_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[3] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_22_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[4] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_23_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[5] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_31_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[6] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_32_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[7] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_33_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[8] ) );

        acamera_isp_out_format_rgb2xyz_coef_a_14_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[9] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_24_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[10] ) );
        acamera_isp_out_format_rgb2xyz_coef_a_34_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_luv[11] ) );

        acamera_isp_out_format_rgb2yuv_coef_b_1_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->color_matrix_luv_b[0] );
        acamera_isp_out_format_rgb2yuv_coef_b_2_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->color_matrix_luv_b[1] );
        acamera_isp_out_format_rgb2yuv_coef_b_3_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->color_matrix_luv_b[2] );
        return;
    }

    if ( !( acamera_isp_out_format_rgb2s_bypass_read( PHY_ADDR_ISP ) & 0x1 ) ) {
        rgb2rgb_matrix_update( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->color_matrix_s2, p_fsm->color_matrix_s2_b );
    } else if ( !( acamera_isp_out_format_ab2hs_bypass_read( PHY_ADDR_ISP ) & 0x1 ) ) {
        rgb2rgb_matrix_update( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->color_matrix_hs, p_fsm->color_matrix_hs_b );
    } else {
        // Default (rgb2rgb)
        LOG( LOG_DEBUG, "p_fsm->manual_CCM %d %d %d %d", p_fsm->manual_CCM, *( p_cm_target + 0 ), *( p_cm_target + 1 ), *( p_cm_target + 2 ) );

        rgb2rgb_matrix_update( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_cm_target, NULL );
    }

    // YUV (requires rgb2rgb)
    if ( !( acamera_isp_out_format_rgb2yuv_bypass_read( PHY_ADDR_ISP ) & 0x1 ) ) {

        acamera_isp_out_format_rgb2yuv_coef_a_11_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[0] ) );
        acamera_isp_out_format_rgb2yuv_coef_a_12_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[1] ) );
        acamera_isp_out_format_rgb2yuv_coef_a_13_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[2] ) );
        acamera_isp_out_format_rgb2yuv_coef_a_21_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[3] ) );
        acamera_isp_out_format_rgb2yuv_coef_a_22_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[4] ) );
        acamera_isp_out_format_rgb2yuv_coef_a_23_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[5] ) );
        acamera_isp_out_format_rgb2yuv_coef_a_31_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[6] ) );
        acamera_isp_out_format_rgb2yuv_coef_a_32_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[7] ) );
        acamera_isp_out_format_rgb2yuv_coef_a_33_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, complement_to_direct( p_fsm->color_matrix_yuv[8] ) );
        acamera_isp_out_format_rgb2yuv_coef_b_1_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->color_matrix_yuv_b[0] );
        acamera_isp_out_format_rgb2yuv_coef_b_2_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->color_matrix_yuv_b[1] );
        acamera_isp_out_format_rgb2yuv_coef_b_3_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, p_fsm->color_matrix_yuv_b[2] );
    }
}

void color_matrix_change_CCMs( color_matrix_fsm_ptr_t p_fsm )
{
    uint8_t i;
    const uint16_t *p_mtrx;
    //	For CCM switching

    // Light source: A
    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_MT_ABSOLUTE_LS_A_CCM );
    color_matrix_setup( p_fsm->color_matrix_A, p_mtrx, ISP_CCM_SIZE );
    // Light source: D40
    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_MT_ABSOLUTE_LS_D40_CCM );
    color_matrix_setup( p_fsm->color_matrix_D40, p_mtrx, ISP_CCM_SIZE );
    // Light source: D50
    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_MT_ABSOLUTE_LS_D50_CCM );
    color_matrix_setup( p_fsm->color_matrix_D50, p_mtrx, ISP_CCM_SIZE );

    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_COLOR_MATRIX_YUV_PRESETS );
    color_matrix_setup( p_fsm->color_matrix_yuv, p_mtrx, ISP_CCM_SIZE );

    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_COLOR_MATRIX_LUV_PRESETS );
    color_matrix_setup( p_fsm->color_matrix_luv, p_mtrx, ISP_CCM_SIZE );

    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_RGB2RGB_HS_CONVERSION );
    color_matrix_setup( p_fsm->color_matrix_hs, p_mtrx, ISP_CCM_SIZE );

    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_RGB2RGB_S2_CONVERSION );
    color_matrix_setup( p_fsm->color_matrix_s2, p_mtrx, ISP_CCM_SIZE );

    // Default tables
    static uint16_t cm_one[ISP_CCM_SIZE] = {256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0};
    color_matrix_setup( p_fsm->color_matrix_one, cm_one, ISP_CCM_SIZE );

    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_COLOR_MATRIX_B_YUV_PRESETS );
    color_matrix_setup( p_fsm->color_matrix_yuv_b, p_mtrx, ISP_CCM_B_SIZE );

    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_COLOR_MATRIX_B_LUV_PRESETS );
    color_matrix_setup( p_fsm->color_matrix_luv_b, p_mtrx, ISP_CCM_B_SIZE );

    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_RGB2RGB_HS_CONVERSION_B );
    color_matrix_setup( p_fsm->color_matrix_hs_b, p_mtrx, ISP_CCM_B_SIZE );

    p_mtrx = calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_RGB2RGB_S2_CONVERSION_B );
    color_matrix_setup( p_fsm->color_matrix_s2_b, p_mtrx, ISP_CCM_B_SIZE );

    if ( p_fsm->light_source_change_frames_left != 0 ) {

        // In CCM switching
        // call CCM switcher to update CCM
        // (note: this does mean CCM switching takes one frame less than normal)
        color_matrix_update_hw( p_fsm );
    } else {
        // Not moving, update current CCMs

        int16_t *p_ccm_next;

        switch ( p_fsm->light_source_ccm ) {

        case AWB_LIGHT_SOURCE_A:
            p_ccm_next = p_fsm->color_matrix_A;
            break;
        case AWB_LIGHT_SOURCE_D40:
            p_ccm_next = p_fsm->color_matrix_D40;
            break;
        case AWB_LIGHT_SOURCE_D50:
            p_ccm_next = p_fsm->color_matrix_D50;
            break;
        default:
            p_ccm_next = p_fsm->color_matrix_one;
            break;
        }

        for ( i = 0; i < 9; i++ ) {
            p_fsm->color_correction_matrix[i] = p_ccm_next[i];
        }
    }
}

/**
 * color_matrix_initialize() - FSM handler function
 * @p_fsm: Pointer to color_matrix fsm.

 * Return: None
 */
void color_matrix_init( color_matrix_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    p_fsm->saturation_target = 0x80;

    set_context_param( p_ictx, SYSTEM_SATURATION_TARGET_PARAM, p_fsm->saturation_target );
    set_context_param( p_ictx, SYSTEM_MANUAL_SATURATION_PARAM, 0 );
}

/**
 * color_matrix_configure() - FSM handler function
 * @p_fsm: Pointer to color_matrix fsm.

 * Return: None
 */
void color_matrix_config( color_matrix_fsm_ptr_t p_fsm )
{
    color_matrix_change_CCMs( p_fsm );
}

/**
 * color_matrix_update_hw() - FSM handler function
 * @p_fsm: Pointer to color_matrix fsm.

 * Return: None
 */
void color_matrix_update_hw( color_matrix_fsm_ptr_t p_fsm )
{
    //	For CCM switching
    if ( p_fsm->light_source_change_frames_left != 0 ) {

        int16_t *p_ccm_prev;
        int16_t *p_ccm_cur = p_fsm->color_correction_matrix;
        int16_t *p_ccm_target;
        int16_t delta;

        switch ( p_fsm->light_source_ccm_previous ) {

        case AWB_LIGHT_SOURCE_A:
            p_ccm_prev = p_fsm->color_matrix_A;
            break;
        case AWB_LIGHT_SOURCE_D40:
            p_ccm_prev = p_fsm->color_matrix_D40;
            break;
        case AWB_LIGHT_SOURCE_D50:
            p_ccm_prev = p_fsm->color_matrix_D50;
            break;
        default:
            p_ccm_prev = p_fsm->color_matrix_one;
            break;
        }

        switch ( p_fsm->light_source_ccm ) {

        case AWB_LIGHT_SOURCE_A:
            p_ccm_target = p_fsm->color_matrix_A;
            break;
        case AWB_LIGHT_SOURCE_D40:
            p_ccm_target = p_fsm->color_matrix_D40;
            break;
        case AWB_LIGHT_SOURCE_D50:
            p_ccm_target = p_fsm->color_matrix_D50;
            break;
        default:
            p_ccm_target = p_fsm->color_matrix_one;
            break;
        }

        int i;
        for ( i = 0; i < 9; ++i ) {

            // smooth transition
            // using curr += (target - curr)/frames_left causes no movement in first half
            // for small movements
            if ( p_fsm->light_source_change_frames > 1 ) {
                delta = ( ( p_ccm_target[i] - p_ccm_prev[i] ) * ( p_fsm->light_source_change_frames - p_fsm->light_source_change_frames_left ) ) / ( p_fsm->light_source_change_frames - 1 ); // division by zero is checked
                p_ccm_cur[i] = p_ccm_prev[i] + delta;
            }
        }
    }

    color_matrix_recalculate( p_fsm );
    color_matrix_write( p_fsm );

    if ( p_fsm->light_source_change_frames_left > 0 ) {
        p_fsm->light_source_change_frames_left--;
    }
}

void color_matrix_get_info( const color_matrix_fsm_ptr_t p_fsm, acamera_cmd_ccm_info *p_info )
{
    p_info->light_source = p_fsm->light_source;
    p_info->light_source_previous = p_fsm->light_source_previous;
    p_info->light_source_ccm = p_fsm->light_source_ccm;
    p_info->light_source_ccm_previous = p_fsm->light_source_ccm_previous;
    p_info->light_source_change_frames = p_fsm->light_source_change_frames;
    p_info->light_source_change_frames_left = p_fsm->light_source_change_frames_left;
}

void color_matrix_set_info( color_matrix_fsm_ptr_t p_fsm, const acamera_cmd_ccm_info *p_info )
{
    p_fsm->light_source = p_info->light_source;
    p_fsm->light_source_previous = p_info->light_source_previous;
    p_fsm->light_source_ccm = p_info->light_source_ccm;
    p_fsm->light_source_ccm_previous = p_info->light_source_ccm_previous;
    p_fsm->light_source_change_frames = p_info->light_source_change_frames;
    p_fsm->light_source_change_frames_left = p_info->light_source_change_frames_left;
}