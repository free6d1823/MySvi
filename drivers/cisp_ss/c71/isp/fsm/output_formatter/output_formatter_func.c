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

#include "acamera_isp_core_settings.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "acamera_out_format.h"
#include "acamera_out_format_lut_rgb_config.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_OUTPUT_FORMATTER

/* AXI format configuration:
 *  { axi mode, msb align, axi data width, h. downsample factor, v. downsample factor }
 */
static const axi_cfg_t axi_mode_data[OUT_FORMAT_AXI_FORMAT_MAX] = {
    {MODE_SEL_DISABLE, MODE_ALIGN_LSB, 0, 1, 1},
    {MODE_SEL_RGB_R14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RGB_R14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RGB_G14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RGB_G14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RGB_B14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RGB_B14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RGB888, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH24, 1, 1},
    {MODE_SEL_RGB32, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH32, 1, 1},
    {MODE_SEL_RGB888, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH24, 1, 1},
    {MODE_SEL_RGB32, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH32, 1, 1},
    {MODE_SEL_Y10, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH10, 1, 1},
    {MODE_SEL_YUV_Y8, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH8, 1, 1},
    {MODE_SEL_YUV_Y14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_YUV_Y14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_YUV_U8, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH8, 1, 1},
    {MODE_SEL_YUV_U14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_YUV_U14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_YUV_V8, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH8, 1, 1},
    {MODE_SEL_YUV_V14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_YUV_V14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_YUV_UV88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_YUV_UV88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 2, 2},
    {MODE_SEL_YUV_UV88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 2, 1},
    {MODE_SEL_YUV_VU88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_YUV_VU88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 2, 2},
    {MODE_SEL_YUV_VU88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 2, 1},
    {MODE_SEL_SS8, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH8, 1, 1},
    {MODE_SEL_SS14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_SS14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_HS_H14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_HS_H14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_HS_S14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_HS_S14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_HS_HS88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_LUV_L14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_LUV_U14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_LUV_U14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_LUV_V14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_LUV_V14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_LUV_UV88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_LUV_VU88, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_IR_IR8, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH8, 1, 1},
    {MODE_SEL_IR_IR14, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_IR_IR14, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RAW8, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH8, 1, 1},
    {MODE_SEL_RAW10, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RAW10, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RAW10, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH10, 1, 1},
    {MODE_SEL_RAW12, MODE_ALIGN_LSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RAW12, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RAW12, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH12, 1, 1},
    {MODE_SEL_RAW16, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RAW24, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH16, 1, 1},
    {MODE_SEL_RAW24, MODE_ALIGN_MSB, OUT_FORMAT_COLOR_WIDTH12, 1, 1}};

// Sets AXI output 1 to 24-bit RGB with LSB alignment.
inline static void reset_axi_outputs( uint32_t isp_base )
{
    acamera_isp_out_format_mux_a1_mode_select_write( isp_base, OUT_FORMAT_OUTPUT_MODE_RGB32 );
    acamera_isp_out_format_mux_a1_msb_align_write( isp_base, MODE_ALIGN_LSB );
    acamera_isp_out_format_mux_a2_mode_select_write( isp_base, OUT_FORMAT_OUTPUT_MODE_DISABLE );
    acamera_isp_out_format_mux_a2_msb_align_write( isp_base, MODE_ALIGN_LSB );
    acamera_isp_out_format_mux_a3_mode_select_write( isp_base, OUT_FORMAT_OUTPUT_MODE_DISABLE );
    acamera_isp_out_format_mux_a3_msb_align_write( isp_base, MODE_ALIGN_LSB );
}

// Disable all output formatter modules (0=enabled, 1=disabled).
// They can then be selectively enabled as required by mode select.
inline static void reset_bypass_registers( uint32_t isp_base )
{
    // LU'V'
    acamera_isp_out_format_clip_luv_bypass_write( isp_base, 1 );
    acamera_isp_out_format_rgb2xyz_bypass_write( isp_base, 1 );
    acamera_isp_out_format_xyz2luv_bypass_write( isp_base, 1 );
    acamera_isp_out_format_lpf_luv_bypass_write( isp_base, 1 );
    acamera_isp_out_format_lut_luv_bypass_write( isp_base, 1 );
    // RGB
    acamera_isp_out_format_clip_rgb_bypass_write( isp_base, 1 );
    acamera_isp_out_format_rgb2rgb_bypass_write( isp_base, 1 );
    acamera_isp_out_format_lut_rgb_bypass_write( isp_base, 1 );
    // YUV
    acamera_isp_out_format_rgb2yuv_bypass_write( isp_base, 1 );
    acamera_isp_out_format_rgb2yuv_sp_bypass_write( isp_base, 1 );
    acamera_isp_out_format_lpf_yuv_bypass_write( isp_base, 1 );
    acamera_isp_out_format_lut_yuv_bypass_write( isp_base, 1 );
    // HS
    acamera_isp_out_format_rgb2ab_bypass_write( isp_base, 1 );
    acamera_isp_out_format_ab2hs_bypass_write( isp_base, 1 );
    acamera_isp_out_format_lpf_ab_bypass_write( isp_base, 1 );

    // S*
    acamera_isp_out_format_rgb2s_bypass_write( isp_base, 1 );

    /* Other defaults */
    acamera_isp_out_format_ir_ms_bypass_write( isp_base, 1 );
}

inline static void init_clipping( uint32_t isp_base )
{
    if ( acamera_isp_out_format_clip_luv_bypass_read( isp_base ) == 0 ) {
        acamera_isp_out_format_clip1_luv_write( isp_base, OUT_FORMAT_LUV_CLIP );
        acamera_isp_out_format_clip2_luv_write( isp_base, OUT_FORMAT_LUV_CLIP );
        acamera_isp_out_format_clip3_luv_write( isp_base, OUT_FORMAT_LUV_CLIP );
        acamera_isp_out_format_clip4_luv_write( isp_base, OUT_FORMAT_LUV_CLIP );
    } else if ( acamera_isp_out_format_clip_rgb_bypass_read( isp_base ) == 0 ) {
        acamera_isp_out_format_clip1_rgb_write( isp_base, OUT_FORMAT_RGB_CLIP );
        acamera_isp_out_format_clip2_rgb_write( isp_base, OUT_FORMAT_RGB_CLIP );
        acamera_isp_out_format_clip3_rgb_write( isp_base, OUT_FORMAT_RGB_CLIP );
        acamera_isp_out_format_clip4_rgb_write( isp_base, OUT_FORMAT_RGB_CLIP );
        // YUV special mode
        if ( acamera_isp_out_format_rgb2yuv_sp_bypass_read( isp_base ) == 0 ) {
            acamera_isp_out_format_rgb2yuv_sp_clip_write( isp_base, 0x3fff );
        }
    }
}

inline static void init_subsampling( uint32_t isp_base, uint8_t horizontal, uint8_t vertical )
{
    // rgb2xyz
    if ( acamera_isp_out_format_lpf_luv_bypass_read( isp_base ) == 0 ) {
        acamera_isp_out_format_lpf_luv_enable_horiz_filter_write( isp_base, 1 );
        acamera_isp_out_format_lpf_luv_enable_horiz_downsample_write( isp_base, horizontal );
        acamera_isp_out_format_lpf_luv_enable_vert_downsample_write( isp_base, vertical );
    }
    // rgb2ab
    else if ( acamera_isp_out_format_lpf_ab_bypass_read( isp_base ) == 0 ) {
        acamera_isp_out_format_lpf_ab_enable_horiz_filter_write( isp_base, 1 );
        acamera_isp_out_format_lpf_ab_enable_horiz_downsample_write( isp_base, horizontal );
        acamera_isp_out_format_lpf_ab_enable_vert_downsample_write( isp_base, vertical );
    }
    // rgb2yuv
    else if ( acamera_isp_out_format_lpf_yuv_bypass_read( isp_base ) == 0 ) {
        acamera_isp_out_format_lpf_yuv_enable_horiz_downsample_write( isp_base, horizontal );
#ifdef ACAMERA_ISP_OUT_FORMAT_LPF_YUV_ENABLE_VERT_DOWNSAMPLE_DEFAULT
        acamera_isp_out_format_lpf_yuv_enable_vert_downsample_write( isp_base, vertical );
#endif
    }
}

static void init_output_planes( output_formatter_cfg_t *cfg )
{
    uint8_t i;

    cfg->format = OUT_FORMAT_OUTPUT_MODE_DISABLE;
    cfg->num_planes = 0;

    for ( i = 0; i < ISP_MCFE_HWIF_MAX_OUTPUTS; i++ ) {
        cfg->plane[i].axi_format = OUT_FORMAT_AXI_FORMAT_DISABLE;
        cfg->plane[i].axi_cfg.data_width = 0;
        cfg->plane[i].axi_cfg.msb_align = MODE_ALIGN_LSB;
        cfg->plane[i].axi_cfg.h_subsampling = 1;
        cfg->plane[i].axi_cfg.v_subsampling = 1;
        cfg->plane[i].axi = 0;
    }
}

static void configure_output_format_pipeline( output_formatter_fsm_ptr_t p_fsm )
{
    int i;
    uint8_t enable_h_downsampling = 0;
    uint8_t enable_v_downsampling = 0;
    uint8_t rgb2s_clip = 255;
    uint8_t has_raw = 0, has_luv = 0, has_rgb = 0, has_yuv = 0, has_hs = 0, has_s = 0, has_ab = 0;
    uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    output_formatter_cfg_t *cfg = &p_fsm->output_formatter_cfg;

    for ( i = 0; i < cfg->num_planes; i++ ) {
        switch ( cfg->plane[i].axi_cfg.mode ) {
        case MODE_SEL_DISABLE:
            break;
        case MODE_SEL_RGB_R14:
        case MODE_SEL_RGB_G14:
        case MODE_SEL_RGB_B14:
        case MODE_SEL_RGB32: // Same as RGB888
            has_rgb = 1;
            break;
        case MODE_SEL_YUV_Y14: // Same as Y8
        case MODE_SEL_YUV_U14: // Same as U8
        case MODE_SEL_YUV_V14: // Same as V8
        case MODE_SEL_YUV_UV88:
        case MODE_SEL_YUV_VU88:
            has_rgb = 1;
            has_yuv = 1;
            break;
        case MODE_SEL_SS8:
            has_rgb = 1;
            has_s = 1;
            break;
        case MODE_SEL_HS_HS88:
            has_rgb = 1;
            has_hs = 1;
            has_ab = 1;
            break;
        case MODE_SEL_IR_IR14:
        case MODE_SEL_IR_IR8:
            break;
        case MODE_SEL_LUV_L14:
        case MODE_SEL_LUV_U14:
        case MODE_SEL_LUV_V14:
        case MODE_SEL_LUV_UV88:
        case MODE_SEL_LUV_VU88:
            has_luv = 1;
            break;
        case MODE_SEL_SS14:
            has_rgb = 1;
            has_s = 1;
            break;
        case MODE_SEL_HS_H14:
        case MODE_SEL_HS_S14:
            has_rgb = 1;
            has_hs = 1;
            has_ab = 1;
            break;
        case MODE_SEL_UNDEF_1:
        case MODE_SEL_UNDEF_2:
            break;
        case MODE_SEL_RAW10: // Same as Y10
        case MODE_SEL_RAW8:
        case MODE_SEL_RAW12:
        case MODE_SEL_RAW16:
        case MODE_SEL_RAW24:
            has_raw = 1;
            break;
        case MODE_SEL_UNDEF_3:
            break;
        case MODE_SEL_UNDEF_4:
            break;
        }

        if ( cfg->plane[i].axi_cfg.h_subsampling > 1 ) {
            enable_h_downsampling = 1;
        }

        if ( cfg->plane[i].axi_cfg.v_subsampling > 1 ) {
            enable_v_downsampling = 1;
        }
    }

    if ( has_ab ) {
        acamera_isp_out_format_rgb2ab_bypass_write( isp_base, 0 );
        acamera_isp_out_format_lpf_ab_bypass_write( isp_base, 1 );
    }

    if ( has_luv ) {
        acamera_isp_out_format_clip_luv_bypass_write( isp_base, 0 );
        acamera_isp_out_format_rgb2xyz_bypass_write( isp_base, 0 );
        acamera_isp_out_format_xyz2luv_bypass_write( isp_base, 0 );
        acamera_isp_out_format_lpf_luv_bypass_write( isp_base, 1 );
        acamera_isp_out_format_lut_luv_bypass_write( isp_base, 0 );
    }

    if ( has_rgb ) {
        acamera_isp_out_format_clip_rgb_bypass_write( isp_base, 0 );
        acamera_isp_out_format_rgb2rgb_bypass_write( isp_base, 0 );
        acamera_isp_out_format_lut_rgb_bypass_write( isp_base, 0 );
    }

    if ( has_yuv ) {
        acamera_isp_out_format_rgb2yuv_bypass_write( isp_base, 0 );
        acamera_isp_out_format_lpf_yuv_bypass_write( isp_base, 1 );
    }

    if ( has_hs ) {
        acamera_isp_out_format_ab2hs_bypass_write( isp_base, 0 );
    }

    /* S* mode */
    if ( has_s ) {
        acamera_isp_out_format_rgb2s_bypass_write( isp_base, 0 );
        acamera_isp_out_format_rgb2s_mode_write( isp_base, 0 );
        acamera_isp_out_format_rgb2s_clip_write( isp_base, rgb2s_clip );
    }

    if ( has_raw ) {
        acamera_isp_pipeline_isp_raw_bypass_write( isp_base, OUT_FORMAT_RAW_BYPASS_ENABLE );
    } else {
        // Max clipping values for inputs
        init_clipping( isp_base );

        // Coefficients and transformation matrices
        /* See color_matrix_write() in color_matrix FSM */

        // Low-pass filter and subsampling
        init_subsampling( isp_base, enable_h_downsampling, enable_v_downsampling );

        // Select YUV mode - standard vs special
        if ( acamera_isp_out_format_rgb2yuv_sp_bypass_read( isp_base ) == 0 ) {
            acamera_isp_out_format_sel_yuv_sp_write( isp_base, 1 );
            acamera_isp_out_format_rgb2yuv_sp_mode_write( isp_base, 0x2 ); // Select special mode algorithm.
        } else {
            acamera_isp_out_format_sel_yuv_sp_write( isp_base, 0 ); // Reset to standard mode.
        }
    }
}

static axi_cfg_t *get_axi_fmt_2_cfg( uint16_t axi_format )
{
    if ( axi_format > OUT_FORMAT_AXI_FORMAT_MAX - 1 ) {
        return NULL;
    }
    return (axi_cfg_t *)&axi_mode_data[axi_format];
}

static int32_t output_formatter_config_format( output_formatter_fsm_ptr_t p_fsm )
{
    int32_t result = 0;
    int i;
    axi_cfg_t *axi_cfg;
    uint32_t cur_axi_format = 0;

    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    uint32_t isp_base = p_ictx->settings.isp_base;
    output_formatter_cfg_t *cfg = &p_fsm->output_formatter_cfg;

    init_output_planes( &p_fsm->output_formatter_cfg );
    cfg->format = get_context_param( p_ictx, OUTPUT_FORMAT_ID_PARAM );

    // Reset to default state - clears registers that keep previous value on reset.
    acamera_isp_pipeline_isp_raw_bypass_write( isp_base, OUT_FORMAT_RAW_BYPASS_DISABLE );
    reset_axi_outputs( isp_base );
    reset_bypass_registers( isp_base );

#if ISP_MCFE_HWIF_MAX_OUTPUTS <= 3
    static const uint32_t axi_format_param_ids[] = {
        OUTPUT_AXI1_FORMAT_ID_PARAM,
        OUTPUT_AXI2_FORMAT_ID_PARAM,
        OUTPUT_AXI3_FORMAT_ID_PARAM};
#else
#error "Number of OUTPUT_AXI#_FORMAT_ID_PARAM params is less than ISP_MCFE_HWIF_MAX_OUTPUTS"
#endif

    if ( cfg->format == OUT_FORMAT_OUTPUT_MODE_MANUAL ) {
        for ( i = 0; i < ISP_MCFE_HWIF_MAX_OUTPUTS; i++ ) {
            if ( ( cur_axi_format = get_context_param( p_ictx, axi_format_param_ids[i] ) ) ) {
                cfg->plane[cfg->num_planes].axi = i + 1;
                cfg->plane[cfg->num_planes].axi_format = cur_axi_format;
                cfg->num_planes++;
            }
        }
    } else {
        switch ( cfg->format ) {
        case OUT_FORMAT_OUTPUT_MODE_DISABLE:
            break;

        // RAW formats
        case OUT_FORMAT_OUTPUT_MODE_RAW8:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RAW_RAW8;
            break;

        case OUT_FORMAT_OUTPUT_MODE_RAW10:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RAW_RAW10_MSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_RAW12:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RAW_RAW12_MSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_RAW16:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RAW_RAW16;
            break;

        case OUT_FORMAT_OUTPUT_MODE_RAW24:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RAW_RAW24;
            break;

        // LU'V' packed
        case OUT_FORMAT_OUTPUT_MODE_L14UV88:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_L14;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_UV88;
            break;

        case OUT_FORMAT_OUTPUT_MODE_L14VU88:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_L14;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_VU88;
            break;

        // LU'V' planar
        case OUT_FORMAT_OUTPUT_MODE_L14U14V14:
            cfg->num_planes = 3;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_L14;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_U14_MSB;
            cfg->plane[2].axi = 3;
            cfg->plane[2].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_V14_MSB;
            break;

        // RGB planar
        case OUT_FORMAT_OUTPUT_MODE_R14G14B14:
            cfg->num_planes = 3;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_R14_LSB;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_G14_LSB;
            cfg->plane[2].axi = 3;
            cfg->plane[2].axi_format = OUT_FORMAT_AXI_FORMAT_B14_LSB;
            break;

        // YUV - planar Y, packed UV
        case OUT_FORMAT_OUTPUT_MODE_Y14UV88:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y14_MSB;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_UV88;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y14VU88:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y14_MSB;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_VU88;
            break;

        // YUV - planar Y, packed UV
        case OUT_FORMAT_OUTPUT_MODE_Y8UV88:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y8;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_UV88;
            break;

        // YUV - planar Y, packed UV
        case OUT_FORMAT_OUTPUT_MODE_Y8UV88_2X1:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y8;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_UV88_DOWNSAMPLED_H;
            break;

        // YUV - planar Y, packed UV
        case OUT_FORMAT_OUTPUT_MODE_Y8UV88_2X2:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y8;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_UV88_DOWNSAMPLED;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y8VU88:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y8;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_VU88;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y8VU88_2X1:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y8;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_VU88_DOWNSAMPLED_H;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y8VU88_2X2:
            cfg->num_planes = 2;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y8;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_VU88_DOWNSAMPLED;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y8U8V8:
            cfg->num_planes = 3;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y8;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_U8;
            cfg->plane[2].axi = 3;
            cfg->plane[2].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_V8;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y14U14V14_LSB:
            cfg->num_planes = 3;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y14_LSB;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_U14_LSB;
            cfg->plane[2].axi = 3;
            cfg->plane[2].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_V14_LSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y14U14V14_MSB:
            cfg->num_planes = 3;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y14_MSB;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_U14_MSB;
            cfg->plane[2].axi = 3;
            cfg->plane[2].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_V14_MSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y14_MSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y14_MSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y14_LSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y14_LSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y8:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_YUV_Y8;
            break;

        case OUT_FORMAT_OUTPUT_MODE_Y10:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_Y_Y10;
            break;

        case OUT_FORMAT_OUTPUT_MODE_L14MSB_U14LSB_V14LSB:
            cfg->num_planes = 3;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_L14;
            cfg->plane[1].axi = 2;
            cfg->plane[1].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_U14_LSB;
            cfg->plane[2].axi = 3;
            cfg->plane[2].axi_format = OUT_FORMAT_AXI_FORMAT_LUV_V14_LSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_IR14LSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_IR_IR14_LSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_IR14MSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_IR_IR14_MSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_IR8:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_IR_IR8;
            break;

        case OUT_FORMAT_OUTPUT_MODE_R14LSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_R14_LSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_R14MSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_R14_MSB;
            break;

        // HS packed
        case OUT_FORMAT_OUTPUT_MODE_HS88:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_HS_HS88;
            break;

        case OUT_FORMAT_OUTPUT_MODE_H_LSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_HS_H14_LSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_H_MSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_HS_H14_MSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_S_14_LSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_HS_S14_LSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_S_14_MSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_HS_S14_MSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_S2_8:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_S_S8;
            break;

        case OUT_FORMAT_OUTPUT_MODE_S2_14_LSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_S_S14_LSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_S2_14_MSB:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_S_S14_MSB;
            break;

        case OUT_FORMAT_OUTPUT_MODE_BGR888:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RGB_BGR24;
            break;

        case OUT_FORMAT_OUTPUT_MODE_RGB888:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RGB_RGB24;
            break;

        case OUT_FORMAT_OUTPUT_MODE_BGR32:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RGB_BGR32;
            break;

        // RGB packed (default)
        case OUT_FORMAT_OUTPUT_MODE_RGB32:
        default:
            cfg->num_planes = 1;
            cfg->plane[0].axi = 1;
            cfg->plane[0].axi_format = OUT_FORMAT_AXI_FORMAT_RGB_RGB32;
            break;
        }

        for ( i = 0; i < ISP_MCFE_HWIF_MAX_OUTPUTS; i++ ) {
            set_context_param( p_ictx, axi_format_param_ids[i], cfg->plane[i].axi_format );
        }
    }

    for ( i = 0; i < cfg->num_planes; i++ ) {
        axi_cfg = get_axi_fmt_2_cfg( cfg->plane[i].axi_format );
        cfg->plane[i].axi_cfg.mode = axi_cfg->mode;
        cfg->plane[i].axi_cfg.data_width = axi_cfg->data_width;
        cfg->plane[i].axi_cfg.msb_align = axi_cfg->msb_align;
        cfg->plane[i].axi_cfg.h_subsampling = axi_cfg->h_subsampling;
        cfg->plane[i].axi_cfg.v_subsampling = axi_cfg->v_subsampling;

        switch ( cfg->plane[i].axi ) {
        case 1:
            acamera_isp_out_format_mux_a1_mode_select_write( isp_base, cfg->plane[i].axi_cfg.mode );
            acamera_isp_out_format_mux_a1_msb_align_write( isp_base, cfg->plane[i].axi_cfg.msb_align );
            break;
        case 2:
            acamera_isp_out_format_mux_a2_mode_select_write( isp_base, cfg->plane[i].axi_cfg.mode );
            acamera_isp_out_format_mux_a2_msb_align_write( isp_base, cfg->plane[i].axi_cfg.msb_align );
            break;
        case 3:
            acamera_isp_out_format_mux_a3_mode_select_write( isp_base, cfg->plane[i].axi_cfg.mode );
            acamera_isp_out_format_mux_a3_msb_align_write( isp_base, cfg->plane[i].axi_cfg.msb_align );
            break;
        default:
            LOG( LOG_ERR, "Unsupported AXI %d for plane %d", cfg->plane[i].axi, i );
            break;
        }
    }

    configure_output_format_pipeline( p_fsm );

    return result;
}

static void output_formatter_rgb_lut_reload( output_formatter_fsm_ptr_t p_fsm )
{
    const uint32_t *gamma_lut = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_GAMMA );
    const uint32_t gamma_lut_len = calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_GAMMA );

    uint32_t i;
    for ( i = 0; i < gamma_lut_len; i++ ) {
        acamera_out_format_lut_rgb_array_data_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i, gamma_lut[i] );
    }
}

/**
 *   @brief     Initialise output formatter.
 *
 *   @param     p_fsm Pointer to FSM private data
 *
 *   @details   Initialise output formatter to default settings.
 */
void output_formatter_init( output_formatter_fsm_ptr_t p_fsm )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

    acamera_isp_out_format_mux_a1_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A1_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_a1_msb_align_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A1_MSB_ALIGN_DEFAULT );
    acamera_isp_out_format_mux_a2_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A2_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_a2_msb_align_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A2_MSB_ALIGN_DEFAULT );
    acamera_isp_out_format_mux_a3_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A3_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_a3_msb_align_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A3_MSB_ALIGN_DEFAULT );

    acamera_isp_out_format_mux_1_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_1_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_1_msb_align_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_1_MSB_ALIGN_DEFAULT );
    acamera_isp_out_format_mux_2_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_2_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_2_msb_align_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_2_MSB_ALIGN_DEFAULT );
    acamera_isp_out_format_mux_3_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_3_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_3_msb_align_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_3_MSB_ALIGN_DEFAULT );

    output_formatter_config_format( p_fsm );

    acamera_isp_pipeline_bypass_out_format_write( isp_base, 0 );
}

/**
 *   @brief     Configure output formatter.
 *
 *   @param     p_fsm Pointer to FSM private data
 *
 *   @details   Configure output formatter on <fsm_config> event.
 */
void output_formatter_config( output_formatter_fsm_ptr_t p_fsm )
{
    output_formatter_config_format( p_fsm );
}

/**
 *   @brief     Reload static calibration LUTs.
 *
 *   @param     p_fsm Pointer to FSM private data
 *
 *   @details   Reload static calibration lookup tables.
 */
void output_formatter_reload_calibration( output_formatter_fsm_ptr_t p_fsm )
{
    output_formatter_rgb_lut_reload( p_fsm );
}

/**
 *   @brief     Deinitialise output formatter.
 *
 *   @param     p_fsm Pointer to FSM private data
 *
 *   @details   Deinitialise output formatter.
 */
void output_formatter_deinit( output_formatter_fsm_ptr_t p_fsm )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

    acamera_isp_out_format_mux_a1_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A1_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_a2_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A2_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_a3_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_A3_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_1_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_1_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_2_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_2_MODE_SELECT_DEFAULT );
    acamera_isp_out_format_mux_3_mode_select_write( isp_base, ACAMERA_ISP_OUT_FORMAT_MUX_3_MODE_SELECT_DEFAULT );
    acamera_isp_pipeline_bypass_out_format_write( isp_base, 1 );
}
