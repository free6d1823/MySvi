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

#include "context_params.h"
#include "acamera_command_api.h"
#include "acamera_configuration.h"

// External parameter handler functions declaration
extern uint8_t buffer_data_type( void *instance, uint32_t value, uint8_t direction, uint32_t *ret_value );


// MCFE_USECASE_PARAM values list
static param_list_value mcfe_usecase_param_values_list[] = {
    // List size
    {3, 0x0},
    {NONE, 0x0},
    {TDMF, 0x0},
    {MANUAL, 0x0}};

// OUTPUT_AXI1_FORMAT_ID_PARAM values list
static param_list_value output_axi1_format_id_param_values_list[] = {
    // List size
    {55, 0x0},
    {OF_AXI_FORMAT_DISABLE, 0x0},
    {OF_AXI_FORMAT_R14_LSB, 0x0},
    {OF_AXI_FORMAT_R14_MSB, 0x0},
    {OF_AXI_FORMAT_G14_LSB, 0x0},
    {OF_AXI_FORMAT_G14_MSB, 0x0},
    {OF_AXI_FORMAT_B14_LSB, 0x0},
    {OF_AXI_FORMAT_B14_MSB, 0x0},
    {OF_AXI_FORMAT_RGB_RGB24, 0x0},
    {OF_AXI_FORMAT_RGB_RGB32, 0x0},
    {OF_AXI_FORMAT_RGB_BGR24, 0x0},
    {OF_AXI_FORMAT_RGB_BGR32, 0x0},
    {OF_AXI_FORMAT_Y_Y10, 0x0},
    {OF_AXI_FORMAT_YUV_Y8, 0x0},
    {OF_AXI_FORMAT_YUV_Y14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_Y14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_U8, 0x0},
    {OF_AXI_FORMAT_YUV_U14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_U14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_V8, 0x0},
    {OF_AXI_FORMAT_YUV_V14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_V14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_UV88, 0x0},
    {OF_AXI_FORMAT_YUV_UV88_DOWNSAMPLED, 0x0},
    {OF_AXI_FORMAT_YUV_UV88_DOWNSAMPLED_H, 0x0},
    {OF_AXI_FORMAT_YUV_VU88, 0x0},
    {OF_AXI_FORMAT_YUV_VU88_DOWNSAMPLED, 0x0},
    {OF_AXI_FORMAT_YUV_VU88_DOWNSAMPLED_H, 0x0},
    {OF_AXI_FORMAT_S_S8, 0x0},
    {OF_AXI_FORMAT_S_S14_LSB, 0x0},
    {OF_AXI_FORMAT_S_S14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_H14_LSB, 0x0},
    {OF_AXI_FORMAT_HS_H14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_S14_LSB, 0x0},
    {OF_AXI_FORMAT_HS_S14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_HS88, 0x0},
    {OF_AXI_FORMAT_LUV_L14, 0x0},
    {OF_AXI_FORMAT_LUV_U14_LSB, 0x0},
    {OF_AXI_FORMAT_LUV_U14_MSB, 0x0},
    {OF_AXI_FORMAT_LUV_V14_LSB, 0x0},
    {OF_AXI_FORMAT_LUV_V14_MSB, 0x0},
    {OF_AXI_FORMAT_LUV_UV88, 0x0},
    {OF_AXI_FORMAT_LUV_VU88, 0x0},
    {OF_AXI_FORMAT_IR_IR8, 0x0},
    {OF_AXI_FORMAT_IR_IR14_LSB, 0x0},
    {OF_AXI_FORMAT_IR_IR14_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW8, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_LSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_DENSE, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_LSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_DENSE, 0x0},
    {OF_AXI_FORMAT_RAW_RAW16, 0x0},
    {OF_AXI_FORMAT_RAW_RAW24, 0x0},
    {OF_AXI_FORMAT_RAW_RAW24_DENSE, 0x0}};

// OUTPUT_AXI2_FORMAT_ID_PARAM values list
static param_list_value output_axi2_format_id_param_values_list[] = {
    // List size
    {55, 0x0},
    {OF_AXI_FORMAT_DISABLE, 0x0},
    {OF_AXI_FORMAT_R14_LSB, 0x0},
    {OF_AXI_FORMAT_R14_MSB, 0x0},
    {OF_AXI_FORMAT_G14_LSB, 0x0},
    {OF_AXI_FORMAT_G14_MSB, 0x0},
    {OF_AXI_FORMAT_B14_LSB, 0x0},
    {OF_AXI_FORMAT_B14_MSB, 0x0},
    {OF_AXI_FORMAT_RGB_RGB24, 0x0},
    {OF_AXI_FORMAT_RGB_RGB32, 0x0},
    {OF_AXI_FORMAT_RGB_BGR24, 0x0},
    {OF_AXI_FORMAT_RGB_BGR32, 0x0},
    {OF_AXI_FORMAT_Y_Y10, 0x0},
    {OF_AXI_FORMAT_YUV_Y8, 0x0},
    {OF_AXI_FORMAT_YUV_Y14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_Y14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_U8, 0x0},
    {OF_AXI_FORMAT_YUV_U14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_U14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_V8, 0x0},
    {OF_AXI_FORMAT_YUV_V14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_V14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_UV88, 0x0},
    {OF_AXI_FORMAT_YUV_UV88_DOWNSAMPLED, 0x0},
    {OF_AXI_FORMAT_YUV_UV88_DOWNSAMPLED_H, 0x0},
    {OF_AXI_FORMAT_YUV_VU88, 0x0},
    {OF_AXI_FORMAT_YUV_VU88_DOWNSAMPLED, 0x0},
    {OF_AXI_FORMAT_YUV_VU88_DOWNSAMPLED_H, 0x0},
    {OF_AXI_FORMAT_S_S8, 0x0},
    {OF_AXI_FORMAT_S_S14_LSB, 0x0},
    {OF_AXI_FORMAT_S_S14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_H14_LSB, 0x0},
    {OF_AXI_FORMAT_HS_H14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_S14_LSB, 0x0},
    {OF_AXI_FORMAT_HS_S14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_HS88, 0x0},
    {OF_AXI_FORMAT_LUV_L14, 0x0},
    {OF_AXI_FORMAT_LUV_U14_LSB, 0x0},
    {OF_AXI_FORMAT_LUV_U14_MSB, 0x0},
    {OF_AXI_FORMAT_LUV_V14_LSB, 0x0},
    {OF_AXI_FORMAT_LUV_V14_MSB, 0x0},
    {OF_AXI_FORMAT_LUV_UV88, 0x0},
    {OF_AXI_FORMAT_LUV_VU88, 0x0},
    {OF_AXI_FORMAT_IR_IR8, 0x0},
    {OF_AXI_FORMAT_IR_IR14_LSB, 0x0},
    {OF_AXI_FORMAT_IR_IR14_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW8, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_LSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_DENSE, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_LSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_DENSE, 0x0},
    {OF_AXI_FORMAT_RAW_RAW16, 0x0},
    {OF_AXI_FORMAT_RAW_RAW24, 0x0},
    {OF_AXI_FORMAT_RAW_RAW24_DENSE, 0x0}};

// OUTPUT_AXI3_FORMAT_ID_PARAM values list
static param_list_value output_axi3_format_id_param_values_list[] = {
    // List size
    {55, 0x0},
    {OF_AXI_FORMAT_DISABLE, 0x0},
    {OF_AXI_FORMAT_R14_LSB, 0x0},
    {OF_AXI_FORMAT_R14_MSB, 0x0},
    {OF_AXI_FORMAT_G14_LSB, 0x0},
    {OF_AXI_FORMAT_G14_MSB, 0x0},
    {OF_AXI_FORMAT_B14_LSB, 0x0},
    {OF_AXI_FORMAT_B14_MSB, 0x0},
    {OF_AXI_FORMAT_RGB_RGB24, 0x0},
    {OF_AXI_FORMAT_RGB_RGB32, 0x0},
    {OF_AXI_FORMAT_RGB_BGR24, 0x0},
    {OF_AXI_FORMAT_RGB_BGR32, 0x0},
    {OF_AXI_FORMAT_Y_Y10, 0x0},
    {OF_AXI_FORMAT_YUV_Y8, 0x0},
    {OF_AXI_FORMAT_YUV_Y14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_Y14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_U8, 0x0},
    {OF_AXI_FORMAT_YUV_U14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_U14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_V8, 0x0},
    {OF_AXI_FORMAT_YUV_V14_LSB, 0x0},
    {OF_AXI_FORMAT_YUV_V14_MSB, 0x0},
    {OF_AXI_FORMAT_YUV_UV88, 0x0},
    {OF_AXI_FORMAT_YUV_UV88_DOWNSAMPLED, 0x0},
    {OF_AXI_FORMAT_YUV_UV88_DOWNSAMPLED_H, 0x0},
    {OF_AXI_FORMAT_YUV_VU88, 0x0},
    {OF_AXI_FORMAT_YUV_VU88_DOWNSAMPLED, 0x0},
    {OF_AXI_FORMAT_YUV_VU88_DOWNSAMPLED_H, 0x0},
    {OF_AXI_FORMAT_S_S8, 0x0},
    {OF_AXI_FORMAT_S_S14_LSB, 0x0},
    {OF_AXI_FORMAT_S_S14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_H14_LSB, 0x0},
    {OF_AXI_FORMAT_HS_H14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_S14_LSB, 0x0},
    {OF_AXI_FORMAT_HS_S14_MSB, 0x0},
    {OF_AXI_FORMAT_HS_HS88, 0x0},
    {OF_AXI_FORMAT_LUV_L14, 0x0},
    {OF_AXI_FORMAT_LUV_U14_LSB, 0x0},
    {OF_AXI_FORMAT_LUV_U14_MSB, 0x0},
    {OF_AXI_FORMAT_LUV_V14_LSB, 0x0},
    {OF_AXI_FORMAT_LUV_V14_MSB, 0x0},
    {OF_AXI_FORMAT_LUV_UV88, 0x0},
    {OF_AXI_FORMAT_LUV_VU88, 0x0},
    {OF_AXI_FORMAT_IR_IR8, 0x0},
    {OF_AXI_FORMAT_IR_IR14_LSB, 0x0},
    {OF_AXI_FORMAT_IR_IR14_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW8, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_LSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW10_DENSE, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_LSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_MSB, 0x0},
    {OF_AXI_FORMAT_RAW_RAW12_DENSE, 0x0},
    {OF_AXI_FORMAT_RAW_RAW16, 0x0},
    {OF_AXI_FORMAT_RAW_RAW24, 0x0},
    {OF_AXI_FORMAT_RAW_RAW24_DENSE, 0x0}};

// OUTPUT_FORMAT_ID_PARAM values list
static param_list_value output_format_id_param_values_list[] = {
    // List size
    {44, 0x0},
    {OF_MODE_MANUAL, 0x0},
    {OF_MODE_DISABLE, 0x0},
    {OF_MODE_R14G14B14, 0x0},
    {OF_MODE_RGB888, 0x0},
    {OF_MODE_Y14UV88, 0x0},
    {OF_MODE_Y14VU88, 0x0},
    {OF_MODE_HS88, 0x0},
    {OF_MODE_H_LSB, 0x0},
    {OF_MODE_H_MSB, 0x0},
    {OF_MODE_S_14_LSB, 0x0},
    {OF_MODE_S_14_MSB, 0x0},
    {OF_MODE_S2_8, 0x0},
    {OF_MODE_S2_14_LSB, 0x0},
    {OF_MODE_S2_14_MSB, 0x0},
    {OF_MODE_L14U14V14, 0x0},
    {OF_MODE_L14UV88, 0x0},
    {OF_MODE_L14VU88, 0x0},
    {OF_MODE_RAW8, 0x0},
    {OF_MODE_RAW10, 0x0},
    {OF_MODE_RAW12, 0x0},
    {OF_MODE_RAW16, 0x0},
    {OF_MODE_RAW24, 0x0},
    {OF_MODE_Y8UV88, 0x0},
    {OF_MODE_Y8UV88_2X1, 0x0},
    {OF_MODE_Y8UV88_2X2, 0x0},
    {OF_MODE_Y8VU88, 0x0},
    {OF_MODE_Y8VU88_2X1, 0x0},
    {OF_MODE_Y8VU88_2X2, 0x0},
    {OF_MODE_Y8U8V8, 0x0},
    {OF_MODE_Y14U14V14_MSB, 0x0},
    {OF_MODE_Y14U14V14_LSB, 0x0},
    {OF_MODE_Y14_MSB, 0x0},
    {OF_MODE_Y14_LSB, 0x0},
    {OF_MODE_Y8, 0x0},
    {OF_MODE_Y10, 0x0},
    {OF_MODE_L14MSB_U14LSB_V14LSB, 0x0},
    {OF_MODE_BGR888, 0x0},
    {OF_MODE_RGB32, 0x0},
    {OF_MODE_BGR32, 0x0},
    {OF_MODE_IR14LSB, 0x0},
    {OF_MODE_IR14MSB, 0x0},
    {OF_MODE_IR8, 0x0},
    {OF_MODE_R14LSB, 0x0},
    {OF_MODE_R14MSB, 0x0}};

// REGISTERS_SIZE_ID_PARAM values list
static param_list_value registers_size_id_param_values_list[] = {
    // List size
    {3, 0x0},
    {8, 0x0},
    {16, 0x0},
    {32, 0x0}};

// REGISTERS_SOURCE_ID_PARAM values list
static param_list_value registers_source_id_param_values_list[] = {
    // List size
    {4, 0x0},
    {SENSOR, 0x0},
    {LENS, 0x0},
    {ISP, 0x0},
    {MIPI, 0x0}};

// SENSOR_WDR_MODE_PARAM values list
static param_list_value sensor_wdr_mode_param_values_list[] = {
    // List size
    {4, 0x0},
    {WDR_MODE_LINEAR, 0x0},
    {WDR_MODE_NATIVE, 0x0},
    {WDR_MODE_FS_HDR, 0x0},
    {WDR_MODE_FS_LIN, 0x0}};

// TEST_PATTERN_ENABLE_ID_PARAM values list
static param_list_value test_pattern_enable_id_param_values_list[] = {
    // List size
    {2, 0x0},
    {OFF, 0x0},
    {ON, 0x0}};

// TEST_PATTERN_MODE_ID_PARAM values list
static param_list_value test_pattern_mode_id_param_values_list[] = {
    // List size
    {6, 0x0},
    {TPG_FLAT_FIELD, 0x0},
    {TPG_H_GRADIENT, 0x0},
    {TPG_V_GRADIENT, 0x0},
    {TPG_V_BARS, 0x0},
    {TPG_ARB_RECT, 0x0},
    {TPG_RANDOM, 0x0}};

// Initialize context parameters with default values
void init_context_params( context_params *params )
{
    if ( params == NULL ) {
        return;
    }

    // AE_COMPENSATION_ID_PARAM
    params->params[0].value = 128;
    params->params[0].default_value = 128;
    params->params[0].min = 0x00000000;
    params->params[0].max = 0xFFFFFFFF;
    params->params[0].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[0].values_list = NULL;
    params->params[0].param_handler = NULL;

    // AE_ROI_ID_PARAM
    params->params[1].value = AE_CENTER_ZONES;
    params->params[1].default_value = AE_CENTER_ZONES;
    params->params[1].min = 0x00000000;
    params->params[1].max = 0xFFFFFFFF;
    params->params[1].flags = ( PARAM_FLAG_RECONFIG | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[1].values_list = NULL;
    params->params[1].param_handler = NULL;

    // AWB_ROI_ID_PARAM
    params->params[2].value = 65535;
    params->params[2].default_value = 65535;
    params->params[2].min = 0x00000000;
    params->params[2].max = 0xFFFFFFFF;
    params->params[2].flags = ( PARAM_FLAG_RECONFIG | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[2].values_list = NULL;
    params->params[2].param_handler = NULL;

    // BUFFER_DATA_TYPE_PARAM
    params->params[3].value = 0x00000000;
    params->params[3].default_value = 0x00000000;
    params->params[3].min = 0x00000000;
    params->params[3].max = 0xFFFFFFFF;
    params->params[3].flags = ( PARAM_FLAG_HANDLER_FUNCTION | PARAM_FLAG_READ );
    params->params[3].values_list = NULL;
    params->params[3].param_handler = buffer_data_type;

    // IMAGE_CROP_ENABLE_ID_PARAM
    params->params[4].value = 0;
    params->params[4].default_value = 0;
    params->params[4].min = 0;
    params->params[4].max = 1;
    params->params[4].flags = ( PARAM_FLAG_RECONFIG | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[4].values_list = NULL;
    params->params[4].param_handler = NULL;

    // IMAGE_CROP_HEIGHT_ID_PARAM
    params->params[5].value = 0;
    params->params[5].default_value = 0;
    params->params[5].min = 0;
    params->params[5].max = 65535;
    params->params[5].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[5].values_list = NULL;
    params->params[5].param_handler = NULL;

    // IMAGE_CROP_WIDTH_ID_PARAM
    params->params[6].value = 0;
    params->params[6].default_value = 0;
    params->params[6].min = 0;
    params->params[6].max = 65535;
    params->params[6].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[6].values_list = NULL;
    params->params[6].param_handler = NULL;

    // IMAGE_CROP_XOFFSET_ID_PARAM
    params->params[7].value = 0;
    params->params[7].default_value = 0;
    params->params[7].min = 0;
    params->params[7].max = 65535;
    params->params[7].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[7].values_list = NULL;
    params->params[7].param_handler = NULL;

    // IMAGE_CROP_YOFFSET_ID_PARAM
    params->params[8].value = 0;
    params->params[8].default_value = 0;
    params->params[8].min = 0;
    params->params[8].max = 65535;
    params->params[8].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[8].values_list = NULL;
    params->params[8].param_handler = NULL;

    // ISP_MODULES_MANUAL_BLACK_LEVEL_PARAM
    params->params[9].value = 0;
    params->params[9].default_value = 0;
    params->params[9].min = 0;
    params->params[9].max = 1;
    params->params[9].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[9].values_list = NULL;
    params->params[9].param_handler = NULL;

    // ISP_MODULES_MANUAL_DEMOSAIC_PARAM
    params->params[10].value = 0;
    params->params[10].default_value = 0;
    params->params[10].min = 0;
    params->params[10].max = 1;
    params->params[10].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[10].values_list = NULL;
    params->params[10].param_handler = NULL;

    // ISP_MODULES_MANUAL_FRAME_STITCH_PARAM
    params->params[11].value = 0;
    params->params[11].default_value = 0;
    params->params[11].min = 0;
    params->params[11].max = 1;
    params->params[11].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[11].values_list = NULL;
    params->params[11].param_handler = NULL;

    // ISP_MODULES_MANUAL_IRIDIX_PARAM
    params->params[12].value = 0;
    params->params[12].default_value = 0;
    params->params[12].min = 0;
    params->params[12].max = 1;
    params->params[12].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[12].values_list = NULL;
    params->params[12].param_handler = NULL;

    // ISP_MODULES_MANUAL_RAW_FRONTEND_PARAM
    params->params[13].value = 0;
    params->params[13].default_value = 0;
    params->params[13].min = 0;
    params->params[13].max = 1;
    params->params[13].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[13].values_list = NULL;
    params->params[13].param_handler = NULL;

    // ISP_MODULES_MANUAL_SHADING_PARAM
    params->params[14].value = 0;
    params->params[14].default_value = 0;
    params->params[14].min = 0;
    params->params[14].max = 1;
    params->params[14].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[14].values_list = NULL;
    params->params[14].param_handler = NULL;

    // ISP_MODULES_MANUAL_SINTER_PARAM
    params->params[15].value = 0;
    params->params[15].default_value = 0;
    params->params[15].min = 0;
    params->params[15].max = 1;
    params->params[15].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[15].values_list = NULL;
    params->params[15].param_handler = NULL;

    // MCFE_USECASE_PARAM
    params->params[16].value = NONE;
    params->params[16].default_value = NONE;
    params->params[16].min = 0x00000000;
    params->params[16].max = 0xFFFFFFFF;
    params->params[16].flags = ( PARAM_FLAG_RECONFIG | PARAM_FLAG_READ );
    params->params[16].values_list = mcfe_usecase_param_values_list;
    params->params[16].param_handler = NULL;

    // OUTPUT_AXI1_FORMAT_ID_PARAM
    params->params[17].value = OF_AXI_FORMAT_RGB_RGB32;
    params->params[17].default_value = OF_AXI_FORMAT_RGB_RGB32;
    params->params[17].min = 0x00000000;
    params->params[17].max = 0xFFFFFFFF;
    params->params[17].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[17].values_list = output_axi1_format_id_param_values_list;
    params->params[17].param_handler = NULL;

    // OUTPUT_AXI2_FORMAT_ID_PARAM
    params->params[18].value = OF_AXI_FORMAT_RGB_RGB32;
    params->params[18].default_value = OF_AXI_FORMAT_RGB_RGB32;
    params->params[18].min = 0x00000000;
    params->params[18].max = 0xFFFFFFFF;
    params->params[18].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[18].values_list = output_axi2_format_id_param_values_list;
    params->params[18].param_handler = NULL;

    // OUTPUT_AXI3_FORMAT_ID_PARAM
    params->params[19].value = OF_AXI_FORMAT_RGB_RGB32;
    params->params[19].default_value = OF_AXI_FORMAT_RGB_RGB32;
    params->params[19].min = 0x00000000;
    params->params[19].max = 0xFFFFFFFF;
    params->params[19].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[19].values_list = output_axi3_format_id_param_values_list;
    params->params[19].param_handler = NULL;

    // OUTPUT_FORMAT_ID_PARAM
    params->params[20].value = OF_MODE_RGB32;
    params->params[20].default_value = OF_MODE_RGB32;
    params->params[20].min = 0x00000000;
    params->params[20].max = 0xFFFFFFFF;
    params->params[20].flags = ( PARAM_FLAG_RECONFIG | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[20].values_list = output_format_id_param_values_list;
    params->params[20].param_handler = NULL;

    // OUTPUT_FORMAT_MANUAL_CFG_APPLY_ID_PARAM
    params->params[21].value = 0;
    params->params[21].default_value = 0;
    params->params[21].min = 0;
    params->params[21].max = 1;
    params->params[21].flags = ( PARAM_FLAG_RECONFIG_ON_TRUE_DEFAULT_RESET | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[21].values_list = NULL;
    params->params[21].param_handler = NULL;

    // REGISTERS_ADDRESS_ID_PARAM
    params->params[22].value = 0x00000000;
    params->params[22].default_value = 0x00000000;
    params->params[22].min = 0x00000000;
    params->params[22].max = 0xFFFFFFFF;
    params->params[22].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[22].values_list = NULL;
    params->params[22].param_handler = NULL;

    // REGISTERS_SIZE_ID_PARAM
    params->params[23].value = 32;
    params->params[23].default_value = 32;
    params->params[23].min = 0x00000000;
    params->params[23].max = 0xFFFFFFFF;
    params->params[23].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[23].values_list = registers_size_id_param_values_list;
    params->params[23].param_handler = NULL;

    // REGISTERS_SOURCE_ID_PARAM
    params->params[24].value = 0x00000000;
    params->params[24].default_value = 0x00000000;
    params->params[24].min = 0x00000000;
    params->params[24].max = 0xFFFFFFFF;
    params->params[24].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[24].values_list = registers_source_id_param_values_list;
    params->params[24].param_handler = NULL;

    // REGISTERS_VALUE_ID_PARAM
    params->params[25].value = 0x00000000;
    params->params[25].default_value = 0x00000000;
    params->params[25].min = 0x00000000;
    params->params[25].max = 0xFFFFFFFF;
    params->params[25].flags = ( PARAM_FLAG_REGISTER_REQUEST | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[25].values_list = NULL;
    params->params[25].param_handler = NULL;

    // SENSOR_EXPOSURES_PARAM
    params->params[26].value = 0x00000000;
    params->params[26].default_value = 0x00000000;
    params->params[26].min = 0x00000000;
    params->params[26].max = 0xFFFFFFFF;
    params->params[26].flags = ( PARAM_FLAG_READ );
    params->params[26].values_list = NULL;
    params->params[26].param_handler = NULL;

    // SENSOR_FPS_PARAM
    params->params[27].value = 0x00000000;
    params->params[27].default_value = 0x00000000;
    params->params[27].min = 0x00000000;
    params->params[27].max = 0xFFFFFFFF;
    params->params[27].flags = ( PARAM_FLAG_READ );
    params->params[27].values_list = NULL;
    params->params[27].param_handler = NULL;

    // SENSOR_HEIGHT_PARAM
    params->params[28].value = 0x00000000;
    params->params[28].default_value = 0x00000000;
    params->params[28].min = 0x00000000;
    params->params[28].max = 0xFFFFFFFF;
    params->params[28].flags = ( PARAM_FLAG_READ );
    params->params[28].values_list = NULL;
    params->params[28].param_handler = NULL;

    // SENSOR_PRESET_PARAM
    params->params[29].value = 0x00000000;
    params->params[29].default_value = 0x00000000;
    params->params[29].min = 0x00000000;
    params->params[29].max = 0xFFFFFFFF;
    params->params[29].flags = ( PARAM_FLAG_RECONFIG | PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[29].values_list = NULL;
    params->params[29].param_handler = NULL;

    // SENSOR_STREAMING_PARAM
    params->params[30].value = 0x00000000;
    params->params[30].default_value = 0x00000000;
    params->params[30].min = 0;
    params->params[30].max = 1;
    params->params[30].flags = ( PARAM_FLAG_READ );
    params->params[30].values_list = NULL;
    params->params[30].param_handler = NULL;

    // SENSOR_SUPPORTED_PRESETS_PARAM
    params->params[31].value = 0x00000000;
    params->params[31].default_value = 0x00000000;
    params->params[31].min = 0x00000000;
    params->params[31].max = 0xFFFFFFFF;
    params->params[31].flags = ( PARAM_FLAG_READ );
    params->params[31].values_list = NULL;
    params->params[31].param_handler = NULL;

    // SENSOR_WDR_MODE_PARAM
    params->params[32].value = WDR_MODE_LINEAR;
    params->params[32].default_value = WDR_MODE_LINEAR;
    params->params[32].min = 0x00000000;
    params->params[32].max = 0xFFFFFFFF;
    params->params[32].flags = ( PARAM_FLAG_READ );
    params->params[32].values_list = sensor_wdr_mode_param_values_list;
    params->params[32].param_handler = NULL;

    // SENSOR_WIDTH_PARAM
    params->params[33].value = 0x00000000;
    params->params[33].default_value = 0x00000000;
    params->params[33].min = 0x00000000;
    params->params[33].max = 0xFFFFFFFF;
    params->params[33].flags = ( PARAM_FLAG_READ );
    params->params[33].values_list = NULL;
    params->params[33].param_handler = NULL;

    // STATUS_INFO_AWB_MIX_LIGHT_CONTRAST_PARAM
    params->params[34].value = 0x00000000;
    params->params[34].default_value = 0x00000000;
    params->params[34].min = 0x00000000;
    params->params[34].max = 0xFFFFFFFF;
    params->params[34].flags = ( PARAM_FLAG_READ );
    params->params[34].values_list = NULL;
    params->params[34].param_handler = NULL;

    // STATUS_INFO_EXPOSURE_LOG2_ID_PARAM
    params->params[35].value = 0x00000000;
    params->params[35].default_value = 0x00000000;
    params->params[35].min = 0x00000000;
    params->params[35].max = 0xFFFFFFFF;
    params->params[35].flags = ( PARAM_FLAG_READ );
    params->params[35].values_list = NULL;
    params->params[35].param_handler = NULL;

    // STATUS_INFO_GAIN_LOG2_ID_PARAM
    params->params[36].value = 0x00000000;
    params->params[36].default_value = 0x00000000;
    params->params[36].min = 0x00000000;
    params->params[36].max = 0xFFFFFFFF;
    params->params[36].flags = ( PARAM_FLAG_READ );
    params->params[36].values_list = NULL;
    params->params[36].param_handler = NULL;

    // STATUS_INFO_GAIN_ONES_ID_PARAM
    params->params[37].value = 0x00000000;
    params->params[37].default_value = 0x00000000;
    params->params[37].min = 0x00000000;
    params->params[37].max = 0xFFFFFFFF;
    params->params[37].flags = ( PARAM_FLAG_READ );
    params->params[37].values_list = NULL;
    params->params[37].param_handler = NULL;

    // SYSTEM_ANTIFLICKER_ENABLE_PARAM
    params->params[38].value = 0;
    params->params[38].default_value = 0;
    params->params[38].min = 0;
    params->params[38].max = 1;
    params->params[38].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[38].values_list = NULL;
    params->params[38].param_handler = NULL;

    // SYSTEM_ANTI_FLICKER_FREQUENCY_PARAM
    params->params[39].value = 0;
    params->params[39].default_value = 0;
    params->params[39].min = 0;
    params->params[39].max = 255;
    params->params[39].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[39].values_list = NULL;
    params->params[39].param_handler = NULL;

    // SYSTEM_AWB_BLUE_GAIN_PARAM
    params->params[40].value = 256;
    params->params[40].default_value = 256;
    params->params[40].min = 0;
    params->params[40].max = 65535;
    params->params[40].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[40].values_list = NULL;
    params->params[40].param_handler = NULL;

    // SYSTEM_AWB_RED_GAIN_PARAM
    params->params[41].value = 256;
    params->params[41].default_value = 256;
    params->params[41].min = 0;
    params->params[41].max = 65535;
    params->params[41].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[41].values_list = NULL;
    params->params[41].param_handler = NULL;

    // SYSTEM_DIRECTIONAL_SHARPENING_TARGET_PARAM
    params->params[42].value = 0;
    params->params[42].default_value = 0;
    params->params[42].min = 0;
    params->params[42].max = 255;
    params->params[42].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[42].values_list = NULL;
    params->params[42].param_handler = NULL;

    // SYSTEM_EXPOSURE_PARAM
    params->params[43].value = 0;
    params->params[43].default_value = 0;
    params->params[43].min = 0x00000000;
    params->params[43].max = 0xFFFFFFFF;
    params->params[43].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[43].values_list = NULL;
    params->params[43].param_handler = NULL;

    // SYSTEM_EXPOSURE_RATIO_PARAM
    params->params[44].value = SYSTEM_EXPOSURE_RATIO_DEFAULT;
    params->params[44].default_value = SYSTEM_EXPOSURE_RATIO_DEFAULT;
    params->params[44].min = 0;
    params->params[44].max = 255;
    params->params[44].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[44].values_list = NULL;
    params->params[44].param_handler = NULL;

    // SYSTEM_FREEZE_FIRMWARE_PARAM
    params->params[45].value = 0;
    params->params[45].default_value = 0;
    params->params[45].min = 0;
    params->params[45].max = 1;
    params->params[45].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[45].values_list = NULL;
    params->params[45].param_handler = NULL;

    // SYSTEM_INTEGRATION_TIME_PARAM
    params->params[46].value = 5000;
    params->params[46].default_value = 5000;
    params->params[46].min = 0;
    params->params[46].max = 1000000;
    params->params[46].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[46].values_list = NULL;
    params->params[46].param_handler = NULL;

    // SYSTEM_INTEGRATION_TIME_PRECISION_PARAM
    params->params[47].value = 0;
    params->params[47].default_value = 0;
    params->params[47].min = 0x00000000;
    params->params[47].max = 0xFFFFFFFF;
    params->params[47].flags = ( PARAM_FLAG_READ );
    params->params[47].values_list = NULL;
    params->params[47].param_handler = NULL;

    // SYSTEM_IRIDIX_DIGITAL_GAIN_PARAM
    params->params[48].value = 256;
    params->params[48].default_value = 256;
    params->params[48].min = 0;
    params->params[48].max = 65535;
    params->params[48].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[48].values_list = NULL;
    params->params[48].param_handler = NULL;

    // SYSTEM_IRIDIX_STRENGTH_TARGET_PARAM
    params->params[49].value = 0;
    params->params[49].default_value = 0;
    params->params[49].min = 0;
    params->params[49].max = 255;
    params->params[49].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[49].values_list = NULL;
    params->params[49].param_handler = NULL;

    // SYSTEM_ISP_DIGITAL_GAIN_PARAM
    params->params[50].value = 0;
    params->params[50].default_value = 0;
    params->params[50].min = 0;
    params->params[50].max = 255;
    params->params[50].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[50].values_list = NULL;
    params->params[50].param_handler = NULL;

    // SYSTEM_LONG_INTEGRATION_TIME_PARAM
    params->params[51].value = 0;
    params->params[51].default_value = 0;
    params->params[51].min = 0x00000000;
    params->params[51].max = 0xFFFFFFFF;
    params->params[51].flags = ( PARAM_FLAG_READ );
    params->params[51].values_list = NULL;
    params->params[51].param_handler = NULL;

    // SYSTEM_MANUAL_AWB_PARAM
    params->params[52].value = 0;
    params->params[52].default_value = 0;
    params->params[52].min = 0;
    params->params[52].max = 1;
    params->params[52].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[52].values_list = NULL;
    params->params[52].param_handler = NULL;

    // SYSTEM_MANUAL_DIRECTIONAL_SHARPENING_PARAM
    params->params[53].value = 0;
    params->params[53].default_value = 0;
    params->params[53].min = 0;
    params->params[53].max = 1;
    params->params[53].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[53].values_list = NULL;
    params->params[53].param_handler = NULL;

    // SYSTEM_MANUAL_EXPOSURE_PARAM
    params->params[54].value = 0;
    params->params[54].default_value = 0;
    params->params[54].min = 0;
    params->params[54].max = 1;
    params->params[54].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[54].values_list = NULL;
    params->params[54].param_handler = NULL;

    // SYSTEM_MANUAL_EXPOSURE_RATIO_PARAM
    params->params[55].value = 0;
    params->params[55].default_value = 0;
    params->params[55].min = 0;
    params->params[55].max = 1;
    params->params[55].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[55].values_list = NULL;
    params->params[55].param_handler = NULL;

    // SYSTEM_MANUAL_INTEGRATION_TIME_PARAM
    params->params[56].value = 0;
    params->params[56].default_value = 0;
    params->params[56].min = 0;
    params->params[56].max = 1;
    params->params[56].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[56].values_list = NULL;
    params->params[56].param_handler = NULL;

    // SYSTEM_MANUAL_ISP_DIGITAL_GAIN_PARAM
    params->params[57].value = 0;
    params->params[57].default_value = 0;
    params->params[57].min = 0;
    params->params[57].max = 1;
    params->params[57].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[57].values_list = NULL;
    params->params[57].param_handler = NULL;

    // SYSTEM_MANUAL_MAX_INTEGRATION_TIME_PARAM
    params->params[58].value = 0;
    params->params[58].default_value = 0;
    params->params[58].min = 0;
    params->params[58].max = 1;
    params->params[58].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[58].values_list = NULL;
    params->params[58].param_handler = NULL;

    // SYSTEM_MANUAL_SATURATION_PARAM
    params->params[59].value = 0;
    params->params[59].default_value = 0;
    params->params[59].min = 0;
    params->params[59].max = 1;
    params->params[59].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[59].values_list = NULL;
    params->params[59].param_handler = NULL;

    // SYSTEM_MANUAL_SENSOR_ANALOG_GAIN_PARAM
    params->params[60].value = 0;
    params->params[60].default_value = 0;
    params->params[60].min = 0;
    params->params[60].max = 1;
    params->params[60].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[60].values_list = NULL;
    params->params[60].param_handler = NULL;

    // SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN_PARAM
    params->params[61].value = 0;
    params->params[61].default_value = 0;
    params->params[61].min = 0;
    params->params[61].max = 1;
    params->params[61].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[61].values_list = NULL;
    params->params[61].param_handler = NULL;

    // SYSTEM_MANUAL_UN_DIRECTIONAL_SHARPENING_PARAM
    params->params[62].value = 0;
    params->params[62].default_value = 0;
    params->params[62].min = 0;
    params->params[62].max = 1;
    params->params[62].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[62].values_list = NULL;
    params->params[62].param_handler = NULL;

    // SYSTEM_MAXIMUM_IRIDIX_STRENGTH_PARAM
    params->params[63].value = 255;
    params->params[63].default_value = 255;
    params->params[63].min = 0;
    params->params[63].max = 255;
    params->params[63].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[63].values_list = NULL;
    params->params[63].param_handler = NULL;

    // SYSTEM_MAX_EXPOSURE_RATIO_PARAM
    params->params[64].value = 0;
    params->params[64].default_value = 0;
    params->params[64].min = 0;
    params->params[64].max = 256;
    params->params[64].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[64].values_list = NULL;
    params->params[64].param_handler = NULL;

    // SYSTEM_MAX_INTEGRATION_TIME_PARAM
    params->params[65].value = 5000;
    params->params[65].default_value = 5000;
    params->params[65].min = 0;
    params->params[65].max = 1000000;
    params->params[65].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[65].values_list = NULL;
    params->params[65].param_handler = NULL;

    // SYSTEM_MAX_ISP_DIGITAL_GAIN_PARAM
    params->params[66].value = 0;
    params->params[66].default_value = 0;
    params->params[66].min = 0;
    params->params[66].max = 255;
    params->params[66].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[66].values_list = NULL;
    params->params[66].param_handler = NULL;

    // SYSTEM_MAX_SENSOR_ANALOG_GAIN_PARAM
    params->params[67].value = 0;
    params->params[67].default_value = 0;
    params->params[67].min = 0;
    params->params[67].max = 255;
    params->params[67].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[67].values_list = NULL;
    params->params[67].param_handler = NULL;

    // SYSTEM_MAX_SENSOR_DIGITAL_GAIN_PARAM
    params->params[68].value = 0;
    params->params[68].default_value = 0;
    params->params[68].min = 0;
    params->params[68].max = 255;
    params->params[68].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[68].values_list = NULL;
    params->params[68].param_handler = NULL;

    // SYSTEM_MIDDLE_INTEGRATION_TIME_PARAM
    params->params[69].value = 0;
    params->params[69].default_value = 0;
    params->params[69].min = 0x00000000;
    params->params[69].max = 0xFFFFFFFF;
    params->params[69].flags = ( PARAM_FLAG_READ );
    params->params[69].values_list = NULL;
    params->params[69].param_handler = NULL;

    // SYSTEM_MINIMUM_IRIDIX_STRENGTH_PARAM
    params->params[70].value = 0;
    params->params[70].default_value = 0;
    params->params[70].min = 0;
    params->params[70].max = 255;
    params->params[70].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[70].values_list = NULL;
    params->params[70].param_handler = NULL;

    // SYSTEM_SATURATION_TARGET_PARAM
    params->params[71].value = 0;
    params->params[71].default_value = 0;
    params->params[71].min = 0;
    params->params[71].max = 255;
    params->params[71].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[71].values_list = NULL;
    params->params[71].param_handler = NULL;

    // SYSTEM_SENSOR_ANALOG_GAIN_PARAM
    params->params[72].value = 0;
    params->params[72].default_value = 0;
    params->params[72].min = 0;
    params->params[72].max = 255;
    params->params[72].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[72].values_list = NULL;
    params->params[72].param_handler = NULL;

    // SYSTEM_SENSOR_DIGITAL_GAIN_PARAM
    params->params[73].value = 0;
    params->params[73].default_value = 0;
    params->params[73].min = 0;
    params->params[73].max = 255;
    params->params[73].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[73].values_list = NULL;
    params->params[73].param_handler = NULL;

    // SYSTEM_SHORT_INTEGRATION_TIME_PARAM
    params->params[74].value = 0;
    params->params[74].default_value = 0;
    params->params[74].min = 0x00000000;
    params->params[74].max = 0xFFFFFFFF;
    params->params[74].flags = ( PARAM_FLAG_READ );
    params->params[74].values_list = NULL;
    params->params[74].param_handler = NULL;

    // SYSTEM_SINTER_THRESHOLD_TARGET_PARAM
    params->params[75].value = 0;
    params->params[75].default_value = 0;
    params->params[75].min = 0;
    params->params[75].max = 255;
    params->params[75].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[75].values_list = NULL;
    params->params[75].param_handler = NULL;

    // SYSTEM_UN_DIRECTIONAL_SHARPENING_TARGET_PARAM
    params->params[76].value = 0;
    params->params[76].default_value = 0;
    params->params[76].min = 0;
    params->params[76].max = 255;
    params->params[76].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[76].values_list = NULL;
    params->params[76].param_handler = NULL;

    // TEST_PATTERN_ENABLE_ID_PARAM
    params->params[77].value = OFF;
    params->params[77].default_value = OFF;
    params->params[77].min = 0x00000000;
    params->params[77].max = 0xFFFFFFFF;
    params->params[77].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[77].values_list = test_pattern_enable_id_param_values_list;
    params->params[77].param_handler = NULL;

    // TEST_PATTERN_MODE_ID_PARAM
    params->params[78].value = TPG_V_BARS;
    params->params[78].default_value = TPG_V_BARS;
    params->params[78].min = 0x00000000;
    params->params[78].max = 0xFFFFFFFF;
    params->params[78].flags = ( PARAM_FLAG_READ | PARAM_FLAG_WRITE );
    params->params[78].values_list = test_pattern_mode_id_param_values_list;
    params->params[78].param_handler = NULL;
}
