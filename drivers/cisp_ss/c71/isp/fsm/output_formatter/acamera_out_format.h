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

#ifndef __ACAMERA_OUT_FORMAT_H__
#define __ACAMERA_OUT_FORMAT_H__

#include "acamera_isp_config.h"

// ------------------------------------------------------------------------------ //
// Mode select register values for DMA/streaming outputs
// Source: Table from Output Formatter section in ISP TRM
// ------------------------------------------------------------------------------ //
#define MODE_SEL_DISABLE 0
#define MODE_SEL_RGB_R14 1
#define MODE_SEL_RGB_G14 2
#define MODE_SEL_RGB_B14 3
#define MODE_SEL_YUV_Y14 4
#define MODE_SEL_YUV_Y8 4
#define MODE_SEL_YUV_U14 5
#define MODE_SEL_YUV_U8 5
#define MODE_SEL_YUV_V14 6
#define MODE_SEL_YUV_V8 6
#define MODE_SEL_YUV_UV88 7
#define MODE_SEL_YUV_VU88 8 // MSB aligned MODE_SEL_YUV_VU88
#define MODE_SEL_SS8 9
#define MODE_SEL_HS_HS88 10
#define MODE_SEL_LUV_L14 11
#define MODE_SEL_LUV_UV88 12
#define MODE_SEL_IR_IR14 13
#define MODE_SEL_IR_IR8 14
#define MODE_SEL_RGB888 15
#define MODE_SEL_RGB32 15
#define MODE_SEL_LUV_U14 16
#define MODE_SEL_LUV_V14 17
#define MODE_SEL_SS14 18 // same as MODE_SEL_HS_S14
#define MODE_SEL_HS_H14 19
#define MODE_SEL_HS_S14 20
#define MODE_SEL_UNDEF_1 21
#define MODE_SEL_LUV_VU88 22 // MSB aligned MODE_SEL_LUV_UV88
#define MODE_SEL_UNDEF_2 23
#define MODE_SEL_RAW8 24
#define MODE_SEL_RAW10 25
#define MODE_SEL_Y10 25
#define MODE_SEL_RAW12 26
#define MODE_SEL_RAW16 27
#define MODE_SEL_UNDEF_3 28
#define MODE_SEL_UNDEF_4 29
#define MODE_SEL_RAW24 30

// ------------------------------------------------------------------------------ //
// In case of change this enum must match OUTPUT_AXI1(2,3)_FORMAT_ID command values in API XML file
// ------------------------------------------------------------------------------ //
enum OUT_FORMAT_AXI_FORMATS {
    OUT_FORMAT_AXI_FORMAT_DISABLE = 0,
    OUT_FORMAT_AXI_FORMAT_R14_LSB,
    OUT_FORMAT_AXI_FORMAT_R14_MSB,
    OUT_FORMAT_AXI_FORMAT_G14_LSB,
    OUT_FORMAT_AXI_FORMAT_G14_MSB,
    OUT_FORMAT_AXI_FORMAT_B14_LSB,
    OUT_FORMAT_AXI_FORMAT_B14_MSB,
    OUT_FORMAT_AXI_FORMAT_RGB_RGB24,
    OUT_FORMAT_AXI_FORMAT_RGB_RGB32,
    OUT_FORMAT_AXI_FORMAT_RGB_BGR24,
    OUT_FORMAT_AXI_FORMAT_RGB_BGR32,
    OUT_FORMAT_AXI_FORMAT_Y_Y10,
    OUT_FORMAT_AXI_FORMAT_YUV_Y8,
    OUT_FORMAT_AXI_FORMAT_YUV_Y14_LSB,
    OUT_FORMAT_AXI_FORMAT_YUV_Y14_MSB,
    OUT_FORMAT_AXI_FORMAT_YUV_U8,
    OUT_FORMAT_AXI_FORMAT_YUV_U14_LSB,
    OUT_FORMAT_AXI_FORMAT_YUV_U14_MSB,
    OUT_FORMAT_AXI_FORMAT_YUV_V8,
    OUT_FORMAT_AXI_FORMAT_YUV_V14_LSB,
    OUT_FORMAT_AXI_FORMAT_YUV_V14_MSB,
    OUT_FORMAT_AXI_FORMAT_YUV_UV88,
    OUT_FORMAT_AXI_FORMAT_YUV_UV88_DOWNSAMPLED,
    OUT_FORMAT_AXI_FORMAT_YUV_UV88_DOWNSAMPLED_H,
    OUT_FORMAT_AXI_FORMAT_YUV_VU88,
    OUT_FORMAT_AXI_FORMAT_YUV_VU88_DOWNSAMPLED,
    OUT_FORMAT_AXI_FORMAT_YUV_VU88_DOWNSAMPLED_H,
    OUT_FORMAT_AXI_FORMAT_S_S8,
    OUT_FORMAT_AXI_FORMAT_S_S14_LSB,
    OUT_FORMAT_AXI_FORMAT_S_S14_MSB,
    OUT_FORMAT_AXI_FORMAT_HS_H14_LSB,
    OUT_FORMAT_AXI_FORMAT_HS_H14_MSB,
    OUT_FORMAT_AXI_FORMAT_HS_S14_LSB,
    OUT_FORMAT_AXI_FORMAT_HS_S14_MSB,
    OUT_FORMAT_AXI_FORMAT_HS_HS88,
    OUT_FORMAT_AXI_FORMAT_LUV_L14,
    OUT_FORMAT_AXI_FORMAT_LUV_U14_LSB,
    OUT_FORMAT_AXI_FORMAT_LUV_U14_MSB,
    OUT_FORMAT_AXI_FORMAT_LUV_V14_LSB,
    OUT_FORMAT_AXI_FORMAT_LUV_V14_MSB,
    OUT_FORMAT_AXI_FORMAT_LUV_UV88,
    OUT_FORMAT_AXI_FORMAT_LUV_VU88,
    OUT_FORMAT_AXI_FORMAT_IR_IR8,
    OUT_FORMAT_AXI_FORMAT_IR_IR14_LSB,
    OUT_FORMAT_AXI_FORMAT_IR_IR14_MSB,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW8,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW10_LSB,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW10_MSB,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW10_DENSE,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW12_LSB,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW12_MSB,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW12_DENSE,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW16,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW24,
    OUT_FORMAT_AXI_FORMAT_RAW_RAW24_DENSE,
    OUT_FORMAT_AXI_FORMAT_MAX
};

// ------------------------------------------------------------------------------ //
// Valid formats supported in DMA mode (AXI output in brackets)
// - RGB: R(1), G(2), B(3), RGB888(1)
// - LU'V': L(1), U'V'(2), U'(2), V'(3)
// - YUV: Y(1), UV(2)
// - HS: HS(3)
// - IR: IR(3)
// - RAW formats (8-, 10-, 12-, 16-, and 24-bit)
//
// Remaining formats are only supported for streaming outputs.
//
// In case of change this enum must match OUTPUT_FORMAT_ID command values in API XML file
// ------------------------------------------------------------------------------ //
enum OUT_FORMAT_OUTPUT_MODES {
    OUT_FORMAT_OUTPUT_MODE_MANUAL = 0,
    OUT_FORMAT_OUTPUT_MODE_DISABLE,
    OUT_FORMAT_OUTPUT_MODE_R14G14B14,
    OUT_FORMAT_OUTPUT_MODE_RGB888,
    OUT_FORMAT_OUTPUT_MODE_Y14UV88,
    OUT_FORMAT_OUTPUT_MODE_Y14VU88,
    OUT_FORMAT_OUTPUT_MODE_HS88,
    OUT_FORMAT_OUTPUT_MODE_H_LSB,
    OUT_FORMAT_OUTPUT_MODE_H_MSB,
    OUT_FORMAT_OUTPUT_MODE_S_14_LSB,
    OUT_FORMAT_OUTPUT_MODE_S_14_MSB,
    OUT_FORMAT_OUTPUT_MODE_S2_8,
    OUT_FORMAT_OUTPUT_MODE_S2_14_LSB,
    OUT_FORMAT_OUTPUT_MODE_S2_14_MSB,
    OUT_FORMAT_OUTPUT_MODE_L14U14V14,
    OUT_FORMAT_OUTPUT_MODE_L14UV88,
    OUT_FORMAT_OUTPUT_MODE_L14VU88,
    OUT_FORMAT_OUTPUT_MODE_RAW8,
    OUT_FORMAT_OUTPUT_MODE_RAW10,
    OUT_FORMAT_OUTPUT_MODE_RAW12,
    OUT_FORMAT_OUTPUT_MODE_RAW16,
    OUT_FORMAT_OUTPUT_MODE_RAW24,
    OUT_FORMAT_OUTPUT_MODE_Y8UV88,
    OUT_FORMAT_OUTPUT_MODE_Y8UV88_2X1, // Chroma subsampling
    OUT_FORMAT_OUTPUT_MODE_Y8UV88_2X2, // Chroma subsampling
    OUT_FORMAT_OUTPUT_MODE_Y8VU88,
    OUT_FORMAT_OUTPUT_MODE_Y8VU88_2X1, // Chroma subsampling
    OUT_FORMAT_OUTPUT_MODE_Y8VU88_2X2, // Chroma subsampling
    OUT_FORMAT_OUTPUT_MODE_Y8U8V8,
    OUT_FORMAT_OUTPUT_MODE_Y14U14V14_MSB,
    OUT_FORMAT_OUTPUT_MODE_Y14U14V14_LSB,
    OUT_FORMAT_OUTPUT_MODE_Y14_MSB,
    OUT_FORMAT_OUTPUT_MODE_Y14_LSB,
    OUT_FORMAT_OUTPUT_MODE_Y8,
    OUT_FORMAT_OUTPUT_MODE_Y10,
    OUT_FORMAT_OUTPUT_MODE_L14MSB_U14LSB_V14LSB,
    OUT_FORMAT_OUTPUT_MODE_BGR888,
    OUT_FORMAT_OUTPUT_MODE_RGB32,
    OUT_FORMAT_OUTPUT_MODE_BGR32,
    OUT_FORMAT_OUTPUT_MODE_IR14LSB,
    OUT_FORMAT_OUTPUT_MODE_IR14MSB,
    OUT_FORMAT_OUTPUT_MODE_IR8,
    OUT_FORMAT_OUTPUT_MODE_R14LSB,
    OUT_FORMAT_OUTPUT_MODE_R14MSB,
    OUT_FORMAT_OUTPUT_MODE_MAX
};

// ------------------------------------------------------------------------------ //
// Color component data width
// ------------------------------------------------------------------------------ //
#define OUT_FORMAT_COLOR_WIDTH8 8
#define OUT_FORMAT_COLOR_WIDTH10 10
#define OUT_FORMAT_COLOR_WIDTH12 12
#define OUT_FORMAT_COLOR_WIDTH16 16
#define OUT_FORMAT_COLOR_WIDTH24 24
#define OUT_FORMAT_COLOR_WIDTH32 32

// ------------------------------------------------------------------------------ //
// MSB alignment
// ------------------------------------------------------------------------------ //
#define MODE_ALIGN_LSB 0
#define MODE_ALIGN_MSB 1

// ------------------------------------------------------------------------------ //
// RAW bypass modes
// ------------------------------------------------------------------------------ //
#define OUT_FORMAT_RAW_BYPASS_DISABLE ACAMERA_ISP_PIPELINE_ISP_RAW_BYPASS_SELECT_PROCESSED
#define OUT_FORMAT_RAW_BYPASS_ENABLE ACAMERA_ISP_PIPELINE_ISP_RAW_BYPASS_BYPASS_ISP_RAW_PROCESSING

// ------------------------------------------------------------------------------ //
// Clipping register max values
// ------------------------------------------------------------------------------ //
#define OUT_FORMAT_LUV_CLIP ACAMERA_ISP_OUT_FORMAT_CLIP1_LUV_DEFAULT
#define OUT_FORMAT_RGB_CLIP ACAMERA_ISP_OUT_FORMAT_CLIP1_RGB_DEFAULT
#define OUT_FORMAT_YUV_SP_CLIP ACAMERA_ISP_OUT_FORMAT_RGB2YUV_SP_CLIP_DEFAULT

#endif // __ACAMERA_OUT_FORMAT_H__
