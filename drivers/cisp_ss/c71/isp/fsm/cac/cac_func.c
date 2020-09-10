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

#include "acamera_ca_correction_mem_config.h"
#include "acamera_ca_filter_mem_config.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"

#define CAC_MEM_LUT_LEN 4096

typedef const uint16_t cac_mem_lut_t[][10];

static inline uint32_t bit_shift( uint32_t v, int32_t s )
{
    return ( s > 0 ) ? ( v << s ) : ( v >> ( -s ) );
}

static int32_t signed_bitshift( int32_t val, int32_t shift )
{
    int32_t out_val = 0;
    uint8_t val_sign = val < 0;

    val = ACAMERA_ABS( val );

    if ( val_sign ) {
        out_val = -bit_shift( val, shift );
    } else {
        out_val = bit_shift( val, shift );
    }

    return out_val;
}

static void ca_filter_mem_reload( cac_fsm_ptr_t p_fsm )
{
    const uint32_t ca_filter_mem_len = calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_CA_FILTER_MEM );
    const uint32_t *p_ca_filter_mem = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_CA_FILTER_MEM );

    LOG( LOG_DEBUG, "ca_filter_mem_len: %d", ca_filter_mem_len );

    int32_t i;

    for ( i = 0; i < ca_filter_mem_len; i++ ) {
        LOG( LOG_DEBUG, "%d): 0x%x.", i, p_ca_filter_mem[i] );
        acamera_ca_filter_mem_array_data_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i, p_ca_filter_mem[i] );
    }
}

static void cac_lut_reload( cac_fsm_ptr_t p_fsm )
{
    acamera_calib_mgr_entry_t *cm_p = ACAMERA_FSM2CM_PTR( p_fsm );
    acamera_isp_ctx_t *ctx_p = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const int32_t isp_base = ctx_p->settings.isp_base;

    cac_mem_lut_t *p_calibration_ca_model = (cac_mem_lut_t *)calib_mgr_lut_get( cm_p, CALIBRATION_CA_CORRECTION_MEM );
    const uint32_t cac_mem_len = calib_mgr_lut_len( cm_p, CALIBRATION_CA_CORRECTION_MEM );

    const uint16_t *p_calibration_cac_cfg = calib_mgr_u16_lut_get( cm_p, CALIBRATION_CA_CORRECTION );

    const uint16_t calibration_ca_min_correction = p_calibration_cac_cfg[0];
    const uint16_t calibration_ca_mesh_width = p_calibration_cac_cfg[1];
    const uint16_t calibration_ca_mesh_height = p_calibration_cac_cfg[2];

    const uint8_t line_offset = calibration_ca_mesh_width;
    const uint16_t plane_offset = calibration_ca_mesh_width * calibration_ca_mesh_height;

    acamera_cmd_sensor_info sensor_info;
    WRAP_GENERAL_CMD( ctx_p, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info );

    uint8_t cfa_pattern = sensor_info.cfa_pattern;

    if ( sensor_info.active_width / calibration_ca_mesh_width < 30 ) {
        // Disable mesh when width doesn't match.
        LOG( LOG_ERR, "Error, CAC mesh width pixel number is too small (Frame width = %d, mesh width = %d)", sensor_info.active_width, calibration_ca_mesh_width );
        acamera_isp_ca_correction_enable_write( isp_base, 0 );
        return;
    }

    if ( CAC_MEM_LUT_LEN != ( ACAMERA_CA_CORRECTION_MEM_SIZE >> 2 ) ) {
        LOG( LOG_CRIT, "cac_mem_lut size mismatch, hw_size: %d, expected: %d.", ( ACAMERA_CA_CORRECTION_MEM_SIZE >> 2 ), CAC_MEM_LUT_LEN );
        return;
    }

    // Configure mesh size and reset the table.
    acamera_isp_ca_correction_mesh_width_write( isp_base, calibration_ca_mesh_width );
    acamera_isp_ca_correction_mesh_height_write( isp_base, calibration_ca_mesh_height );
    acamera_isp_ca_correction_line_offset_write( isp_base, calibration_ca_mesh_width );
    acamera_isp_ca_correction_plane_offset_write( isp_base, calibration_ca_mesh_width * calibration_ca_mesh_height );

    uint8_t plane_count;

    switch ( cfa_pattern ) {
    case 0: // RGGB
        plane_count = 2;
        break;
    case 1: // RCCC
        plane_count = 1;
        break;
    default: // RGBIr
        plane_count = 3;
        break;
    }

    LOG( LOG_DEBUG, "cfa_pattern: %d, plane_count: %d, cac_mem_len: %d", cfa_pattern, plane_count, cac_mem_len );

    int32_t ca_model[10];
    int32_t mesh_vars[9];
    uint16_t component;

    for ( component = 0; component < plane_count * 2; component++ ) {

        uint8_t term;

        // Generate s15.0 ca_model (int32) from u16.0 ca_model_u (uint16).
        for ( term = 0; term < 10; term++ ) {
            if ( ( *p_calibration_ca_model )[component][term] < 32768 ) {
                ca_model[term] = ( *p_calibration_ca_model )[component][term];
            } else {
                ca_model[term] = ( *p_calibration_ca_model )[component][term] - 65536;
            }
        }

        const uint32_t plane_offset_val = plane_offset * bit_shift( component, -1 );
        const uint16_t vh_shift = ( component % 2 ) * 8;

        uint8_t x;
        uint8_t y;

        for ( x = 0; x < calibration_ca_mesh_width; x++ ) {
            for ( y = 0; y < calibration_ca_mesh_height; y++ ) {
                int32_t z32 = 0;
                int16_t z16 = 0;
                int16_t z_norm = 0;
                int32_t product = 0;
                uint8_t z_sign = 0;
                uint32_t zu32 = 0;
                uint16_t lut_index = 0;
                uint8_t lut_shift = 0;
                uint32_t old_value = 0;
                uint32_t new_value = 0;

                // Apply model - this polynomial:
                // z = b0*x^3 + b1*x^2*y + b2*x*y^2 + b3*y^3 + b4*x^2 + b5*x*y + b6*y^2 + b7*x + b8*y +b9

                // mesh_vars(:,1:4) are u18.0, coeffs(1:4) are s-10.23 so product is s8.23.
                // mesh_vars(:,5:7) are u12.0, coeffs(5:7) are s-3.17 so product is s9.17.
                // mesh_vars(:,8:9) are u6.0, coeffs(8:9) are s2.11 so product is s8.11.
                // mesh_vars(:,10) are u1.0, coeffs(10) is s6.5 so product is s6.5.

                mesh_vars[8] = y;
                mesh_vars[7] = x;
                mesh_vars[6] = y * y;
                mesh_vars[5] = x * y;
                mesh_vars[4] = x * x;
                mesh_vars[3] = mesh_vars[6] * y;
                mesh_vars[2] = mesh_vars[5] * y;
                mesh_vars[1] = mesh_vars[4] * y;
                mesh_vars[0] = mesh_vars[4] * x;

                for ( term = 0; term < 4; term++ ) {
                    product = mesh_vars[term] * ca_model[term];
                    product = signed_bitshift( product, -4 );
                    z32 = z32 + product;
                }

                // Drop precision to match next set of coefficients.
                z32 = signed_bitshift( z32, -2 );

                for ( term = 4; term < 7; term++ ) {
                    product = mesh_vars[term] * ca_model[term];
                    z32 = z32 + product;
                }

                // Drop precision to match next set of coefficients.
                z32 = signed_bitshift( z32, -6 );

                for ( term = 7; term < 9; term++ ) {
                    product = mesh_vars[term] * ca_model[term];
                    z32 = z32 + product;
                }

                // Drop precision to match error model (precision of coeff 10 is also set to match this).
                z32 = signed_bitshift( z32, -4 );

                z32 = z32 + ca_model[9];

                // Clip to s4.7 range.
                z32 = MAX( z32, -2048 );
                z32 = MIN( z32, 2047 );

                // Cast z from int32 to int16 here. Its size is only 12 bits.
                z16 = (int16_t)z32;

                // Apply periodic linear approximation of error model:
                // z = z - 0.1*sin(pi*z)
                // Approximation between is z = z+0.25z_norm

                // z_norm is equivalent position of z within linear range of +/-0.5
                if ( ( z16 + 128 ) < 0 ) {
                    z_norm = ( ( z16 + 128 ) % 256 ) - 128;
                    z_norm = 256 + z_norm;
                } else {
                    z_norm = ( ( z16 + 128 ) % 256 ) - 128;
                }

                if ( z_norm < -64 ) {
                    z_norm = -128 - z_norm;
                } else if ( z_norm > 64 ) {
                    z_norm = 128 - z_norm;
                }

                // Shift by -2 is like multiplying by 0.25z_norm.
                z_norm = signed_bitshift( z_norm, -2 );
                z16 = z16 - z_norm;

                z16 = signed_bitshift( z16, -2 );

                // Now manipulate z to the format of the mesh (u4.4, 2s complement).

                z_sign = z16 < 0;

                // Round z to 4 bits precision.
                z16 = ACAMERA_ABS( z16 );
                z16 = ( z16 % 2 ) + bit_shift( z16, -1 );

                // Apply ca_min_correction (clip small corrections to 0).
                if ( z16 <= calibration_ca_min_correction ) {
                    z_sign = 0;
                    z16 = 0;
                }

                if ( z16 > 127 ) {
                    z16 = 127;
                }

                // Convert to 2s complement.
                if ( z_sign ) {
                    z16 = 256 - z16;
                }

                // Cast z from int16 to uint32 here.
                zu32 = (uint32_t)z16;

                // Work out which LUT entry this z value should be placed in.
                lut_index = plane_offset_val + y * line_offset + x;

                // Shift increases by 16 bits for odd entries.
                lut_shift = vh_shift + ( lut_index % 2 ) * 16;

                // Find location within half sized array (2 blocks per register).
                lut_index = bit_shift( lut_index, -1 );

                // Clip to size of LUT (in case of error).
                lut_index = lut_index & 4095;

                old_value = acamera_ca_correction_mem_array_data_read( isp_base, lut_index );
                new_value = ( old_value & ( ~bit_shift( zu32, lut_shift ) ) ) | bit_shift( zu32, lut_shift );
                acamera_ca_correction_mem_array_data_write( isp_base, lut_index, new_value );
            }
        }
    }

    // Enable and reload the table.
    acamera_isp_ca_correction_enable_write( isp_base, 1 );
    acamera_isp_ca_correction_mesh_reload_write( isp_base, 0 );
    acamera_isp_ca_correction_mesh_reload_write( isp_base, 1 );
    acamera_isp_ca_correction_mesh_reload_write( isp_base, 0 );
}

void cac_init( cac_fsm_ptr_t p_fsm )
{
    const int32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

    /* Default configuration */
    acamera_isp_ca_correction_mesh_scale_write( isp_base,
                                                ACAMERA_ISP_CA_CORRECTION_MESH_SCALE_DEFAULT );

    acamera_isp_pipeline_bypass_ca_correction_write( isp_base, 0 );
}

void cac_config( cac_fsm_ptr_t p_fsm )
{
}

void cac_reload_calibration( cac_fsm_ptr_t p_fsm )
{
    ca_filter_mem_reload( p_fsm );
    cac_lut_reload( p_fsm );
}

void cac_deinit( cac_fsm_ptr_t p_fsm )
{
    const int32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    acamera_isp_pipeline_bypass_ca_correction_write( isp_base, 1 );
}