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

#ifndef _ACAMERA_COMMAND_API_H_
#define _ACAMERA_COMMAND_API_H_
#include "system_types.h"


// ------------------------------------------------------------------------------ //
//		ERROR REASONS
// ------------------------------------------------------------------------------ //
#define ERR_UNKNOWN 0x00000000
#define ERR_BAD_ARGUMENT 0x00000001
#define ERR_WRONG_SIZE 0x00000002


// ------------------------------------------------------------------------------ //
//		WDR MODES
// ------------------------------------------------------------------------------ //
#define WDR_MODE_LINEAR 0x00000000
#define WDR_MODE_NATIVE 0x00000001
#define WDR_MODE_FS_HDR 0x00000002
#define WDR_MODE_FS_LIN 0x00000003
#define WDR_MODE_COUNT 0x00000004


// ------------------------------------------------------------------------------ //
//		COMMAND TYPE LIST
// ------------------------------------------------------------------------------ //
#define TSELFTEST 0x00000000
#define TGENERAL 0x00000001
#define TSENSOR 0x00000002
#define TSYSTEM 0x00000003
#define TIMAGE 0x00000004
#define TALGORITHMS 0x00000005
#define TREGISTERS 0x00000006
#define TSTATUS 0x00000007
#define TISP_MODULES 0x00000008


// ------------------------------------------------------------------------------ //
//		BUFFER TYPES
// ------------------------------------------------------------------------------ //
#define STATIC_CALIBRATIONS_ID 0x00000000
#define DYNAMIC_CALIBRATIONS_ID 0x00000001
#define FILE_TRANSFER_ID 0x00000002
#define DYNAMIC_STATE_ID 0x00000003


// ------------------------------------------------------------------------------ //
//		COMMAND LIST
// ------------------------------------------------------------------------------ //
#define FW_REVISION 0x00000000
#define CONTEXT_NUMBER 0x00000001
#define ACTIVE_CONTEXT 0x00000002
#define SENSOR_SUPPORTED_PRESETS 0x00000003
#define SENSOR_PRESET 0x00000004
#define SENSOR_WDR_MODE 0x00000005
#define SENSOR_STREAMING 0x00000006
#define SENSOR_EXPOSURES 0x00000007
#define SENSOR_FPS 0x00000008
#define SENSOR_WIDTH 0x00000009
#define SENSOR_HEIGHT 0x0000000A
#define SYSTEM_LOGGER_LEVEL 0x0000000B
#define SYSTEM_LOGGER_MASK 0x0000000C
#define MCFE_USECASE 0x0000000D
#define BUFFER_DATA_TYPE 0x0000000E
#define TEST_PATTERN_ENABLE_ID 0x0000000F
#define TEST_PATTERN_MODE_ID 0x00000010
#define SYSTEM_FREEZE_FIRMWARE 0x00000011
#define SYSTEM_MANUAL_EXPOSURE 0x00000012
#define SYSTEM_MANUAL_MAX_INTEGRATION_TIME 0x00000013
#define SYSTEM_MANUAL_EXPOSURE_RATIO 0x00000014
#define SYSTEM_MANUAL_INTEGRATION_TIME 0x00000015
#define SYSTEM_MANUAL_SENSOR_ANALOG_GAIN 0x00000016
#define SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN 0x00000017
#define SYSTEM_MANUAL_ISP_DIGITAL_GAIN 0x00000018
#define SYSTEM_MANUAL_DIRECTIONAL_SHARPENING 0x00000019
#define SYSTEM_MANUAL_UN_DIRECTIONAL_SHARPENING 0x0000001A
#define SYSTEM_MANUAL_AWB 0x0000001B
#define SYSTEM_ANTIFLICKER_ENABLE 0x0000001C
#define SYSTEM_MANUAL_SATURATION 0x0000001D
#define SYSTEM_EXPOSURE 0x0000001E
#define SYSTEM_INTEGRATION_TIME_PRECISION 0x0000001F
#define SYSTEM_EXPOSURE_RATIO 0x00000020
#define SYSTEM_MAX_EXPOSURE_RATIO 0x00000021
#define SYSTEM_INTEGRATION_TIME 0x00000022
#define SYSTEM_LONG_INTEGRATION_TIME 0x00000023
#define SYSTEM_MIDDLE_INTEGRATION_TIME 0x00000024
#define SYSTEM_SHORT_INTEGRATION_TIME 0x00000025
#define SYSTEM_MAX_INTEGRATION_TIME 0x00000026
#define SYSTEM_SENSOR_ANALOG_GAIN 0x00000027
#define SYSTEM_MAX_SENSOR_ANALOG_GAIN 0x00000028
#define SYSTEM_SENSOR_DIGITAL_GAIN 0x00000029
#define SYSTEM_MAX_SENSOR_DIGITAL_GAIN 0x0000002A
#define SYSTEM_ISP_DIGITAL_GAIN 0x0000002B
#define SYSTEM_MAX_ISP_DIGITAL_GAIN 0x0000002C
#define SYSTEM_DIRECTIONAL_SHARPENING_TARGET 0x0000002D
#define SYSTEM_UN_DIRECTIONAL_SHARPENING_TARGET 0x0000002E
#define SYSTEM_IRIDIX_STRENGTH_TARGET 0x0000002F
#define SYSTEM_MAXIMUM_IRIDIX_STRENGTH 0x00000030
#define SYSTEM_MINIMUM_IRIDIX_STRENGTH 0x00000031
#define SYSTEM_IRIDIX_DIGITAL_GAIN 0x00000032
#define SYSTEM_SINTER_THRESHOLD_TARGET 0x00000033
#define SYSTEM_AWB_RED_GAIN 0x00000034
#define SYSTEM_AWB_BLUE_GAIN 0x00000035
#define SYSTEM_SATURATION_TARGET 0x00000036
#define SYSTEM_ANTI_FLICKER_FREQUENCY 0x00000037
#define IMAGE_CROP_ENABLE_ID 0x00000038
#define IMAGE_CROP_WIDTH_ID 0x00000039
#define IMAGE_CROP_HEIGHT_ID 0x0000003A
#define IMAGE_CROP_XOFFSET_ID 0x0000003B
#define IMAGE_CROP_YOFFSET_ID 0x0000003C
#define OUTPUT_AXI1_FORMAT_ID 0x0000003D
#define OUTPUT_AXI2_FORMAT_ID 0x0000003E
#define OUTPUT_AXI3_FORMAT_ID 0x0000003F
#define OUTPUT_FORMAT_MANUAL_CFG_APPLY_ID 0x00000040
#define OUTPUT_FORMAT_ID 0x00000041
#define AE_ROI_ID 0x00000042
#define AE_COMPENSATION_ID 0x00000043
#define AWB_ROI_ID 0x00000044
#define REGISTERS_ADDRESS_ID 0x00000045
#define REGISTERS_SIZE_ID 0x00000046
#define REGISTERS_SOURCE_ID 0x00000047
#define REGISTERS_VALUE_ID 0x00000048
#define STATUS_INFO_EXPOSURE_LOG2_ID 0x00000049
#define STATUS_INFO_GAIN_ONES_ID 0x0000004A
#define STATUS_INFO_GAIN_LOG2_ID 0x0000004B
#define STATUS_INFO_AWB_MIX_LIGHT_CONTRAST 0x0000004C
#define ISP_MODULES_MANUAL_IRIDIX 0x0000004D
#define ISP_MODULES_MANUAL_SINTER 0x0000004E
#define ISP_MODULES_MANUAL_FRAME_STITCH 0x0000004F
#define ISP_MODULES_MANUAL_RAW_FRONTEND 0x00000050
#define ISP_MODULES_MANUAL_BLACK_LEVEL 0x00000051
#define ISP_MODULES_MANUAL_SHADING 0x00000052
#define ISP_MODULES_MANUAL_DEMOSAIC 0x00000053


// ------------------------------------------------------------------------------ //
//		COMMAND VALUE LISTS
// ------------------------------------------------------------------------------ //

// SYSTEM_LOGGER_LEVEL command value list
#define SYSTEM_LOGGER_DEBUG 0x00000000
#define SYSTEM_LOGGER_INFO 0x00000001
#define SYSTEM_LOGGER_NOTICE 0x00000002
#define SYSTEM_LOGGER_WARNING 0x00000003
#define SYSTEM_LOGGER_ERROR 0x00000004
#define SYSTEM_LOGGER_CRITICAL 0x00000005
#define SYSTEM_LOGGER_ALERT 0x00000006
#define SYSTEM_LOGGER_EMERG 0x00000007
#define SYSTEM_LOGGER_NOTHING 0x00000008

// MCFE_USECASE command value list
#define NONE 0x00000000
#define TDMF 0x00000001
#define MANUAL 0x00000002

// TEST_PATTERN_ENABLE_ID command value list
#define OFF 0x00000000
#define ON 0x00000001

// TEST_PATTERN_MODE_ID command value list
#define TPG_FLAT_FIELD 0x00000000
#define TPG_H_GRADIENT 0x00000001
#define TPG_V_GRADIENT 0x00000002
#define TPG_V_BARS 0x00000003
#define TPG_ARB_RECT 0x00000004
#define TPG_RANDOM 0x00000005

// OUTPUT_AXI1_FORMAT_ID command value list
#define OF_AXI_FORMAT_DISABLE 0x00000000
#define OF_AXI_FORMAT_R14_LSB 0x00000001
#define OF_AXI_FORMAT_R14_MSB 0x00000002
#define OF_AXI_FORMAT_G14_LSB 0x00000003
#define OF_AXI_FORMAT_G14_MSB 0x00000004
#define OF_AXI_FORMAT_B14_LSB 0x00000005
#define OF_AXI_FORMAT_B14_MSB 0x00000006
#define OF_AXI_FORMAT_RGB_RGB24 0x00000007
#define OF_AXI_FORMAT_RGB_RGB32 0x00000008
#define OF_AXI_FORMAT_RGB_BGR24 0x00000009
#define OF_AXI_FORMAT_RGB_BGR32 0x0000000A
#define OF_AXI_FORMAT_Y_Y10 0x0000000B
#define OF_AXI_FORMAT_YUV_Y8 0x0000000C
#define OF_AXI_FORMAT_YUV_Y14_LSB 0x0000000D
#define OF_AXI_FORMAT_YUV_Y14_MSB 0x0000000E
#define OF_AXI_FORMAT_YUV_U8 0x0000000F
#define OF_AXI_FORMAT_YUV_U14_LSB 0x00000010
#define OF_AXI_FORMAT_YUV_U14_MSB 0x00000011
#define OF_AXI_FORMAT_YUV_V8 0x00000012
#define OF_AXI_FORMAT_YUV_V14_LSB 0x00000013
#define OF_AXI_FORMAT_YUV_V14_MSB 0x00000014
#define OF_AXI_FORMAT_YUV_UV88 0x00000015
#define OF_AXI_FORMAT_YUV_UV88_DOWNSAMPLED 0x00000016
#define OF_AXI_FORMAT_YUV_UV88_DOWNSAMPLED_H 0x00000017
#define OF_AXI_FORMAT_YUV_VU88 0x00000018
#define OF_AXI_FORMAT_YUV_VU88_DOWNSAMPLED 0x00000019
#define OF_AXI_FORMAT_YUV_VU88_DOWNSAMPLED_H 0x0000001A
#define OF_AXI_FORMAT_S_S8 0x0000001B
#define OF_AXI_FORMAT_S_S14_LSB 0x0000001C
#define OF_AXI_FORMAT_S_S14_MSB 0x0000001D
#define OF_AXI_FORMAT_HS_H14_LSB 0x0000001E
#define OF_AXI_FORMAT_HS_H14_MSB 0x0000001F
#define OF_AXI_FORMAT_HS_S14_LSB 0x00000020
#define OF_AXI_FORMAT_HS_S14_MSB 0x00000021
#define OF_AXI_FORMAT_HS_HS88 0x00000022
#define OF_AXI_FORMAT_LUV_L14 0x00000023
#define OF_AXI_FORMAT_LUV_U14_LSB 0x00000024
#define OF_AXI_FORMAT_LUV_U14_MSB 0x00000025
#define OF_AXI_FORMAT_LUV_V14_LSB 0x00000026
#define OF_AXI_FORMAT_LUV_V14_MSB 0x00000027
#define OF_AXI_FORMAT_LUV_UV88 0x00000028
#define OF_AXI_FORMAT_LUV_VU88 0x00000029
#define OF_AXI_FORMAT_IR_IR8 0x0000002A
#define OF_AXI_FORMAT_IR_IR14_LSB 0x0000002B
#define OF_AXI_FORMAT_IR_IR14_MSB 0x0000002C
#define OF_AXI_FORMAT_RAW_RAW8 0x0000002D
#define OF_AXI_FORMAT_RAW_RAW10_LSB 0x0000002E
#define OF_AXI_FORMAT_RAW_RAW10_MSB 0x0000002F
#define OF_AXI_FORMAT_RAW_RAW10_DENSE 0x00000030
#define OF_AXI_FORMAT_RAW_RAW12_LSB 0x00000031
#define OF_AXI_FORMAT_RAW_RAW12_MSB 0x00000032
#define OF_AXI_FORMAT_RAW_RAW12_DENSE 0x00000033
#define OF_AXI_FORMAT_RAW_RAW16 0x00000034
#define OF_AXI_FORMAT_RAW_RAW24 0x00000035
#define OF_AXI_FORMAT_RAW_RAW24_DENSE 0x00000036

// OUTPUT_FORMAT_ID command value list
#define OF_MODE_MANUAL 0x00000000
#define OF_MODE_DISABLE 0x00000001
#define OF_MODE_R14G14B14 0x00000002
#define OF_MODE_RGB888 0x00000003
#define OF_MODE_Y14UV88 0x00000004
#define OF_MODE_Y14VU88 0x00000005
#define OF_MODE_HS88 0x00000006
#define OF_MODE_H_LSB 0x00000007
#define OF_MODE_H_MSB 0x00000008
#define OF_MODE_S_14_LSB 0x00000009
#define OF_MODE_S_14_MSB 0x0000000A
#define OF_MODE_S2_8 0x0000000B
#define OF_MODE_S2_14_LSB 0x0000000C
#define OF_MODE_S2_14_MSB 0x0000000D
#define OF_MODE_L14U14V14 0x0000000E
#define OF_MODE_L14UV88 0x0000000F
#define OF_MODE_L14VU88 0x00000010
#define OF_MODE_RAW8 0x00000011
#define OF_MODE_RAW10 0x00000012
#define OF_MODE_RAW12 0x00000013
#define OF_MODE_RAW16 0x00000014
#define OF_MODE_RAW24 0x00000015
#define OF_MODE_Y8UV88 0x00000016
#define OF_MODE_Y8UV88_2X1 0x00000017
#define OF_MODE_Y8UV88_2X2 0x00000018
#define OF_MODE_Y8VU88 0x00000019
#define OF_MODE_Y8VU88_2X1 0x0000001A
#define OF_MODE_Y8VU88_2X2 0x0000001B
#define OF_MODE_Y8U8V8 0x0000001C
#define OF_MODE_Y14U14V14_MSB 0x0000001D
#define OF_MODE_Y14U14V14_LSB 0x0000001E
#define OF_MODE_Y14_MSB 0x0000001F
#define OF_MODE_Y14_LSB 0x00000020
#define OF_MODE_Y8 0x00000021
#define OF_MODE_Y10 0x00000022
#define OF_MODE_L14MSB_U14LSB_V14LSB 0x00000023
#define OF_MODE_BGR888 0x00000024
#define OF_MODE_RGB32 0x00000025
#define OF_MODE_BGR32 0x00000026
#define OF_MODE_IR14LSB 0x00000027
#define OF_MODE_IR14MSB 0x00000028
#define OF_MODE_IR8 0x00000029
#define OF_MODE_R14LSB 0x0000002A
#define OF_MODE_R14MSB 0x0000002B

// REGISTERS_SOURCE_ID command value list
#define SENSOR 0x00000000
#define LENS 0x00000001
#define ISP 0x00000002
#define MIPI 0x00000003


// ------------------------------------------------------------------------------ //
//		RETURN VALUES
// ------------------------------------------------------------------------------ //
#define SUCCESS 0x00000000
#define NOT_IMPLEMENTED 0x00000001
#define NOT_SUPPORTED 0x00000002
#define NOT_PERMITTED 0x00000003
#define NOT_EXISTS 0x00000004
#define FAIL 0x00000005


// ------------------------------------------------------------------------------ //
//		DIRECTION VALUES
// ------------------------------------------------------------------------------ //
#define COMMAND_SET 0x00000000
#define COMMAND_GET 0x00000001
#define API_VERSION 0x00000064


// ------------------------------------------------------------------------------ //
//		FUNCTIONS
// ------------------------------------------------------------------------------ //
// The main api function to control and change the firmware state
uint8_t acamera_command( uint8_t command_type, uint8_t command, uint32_t value, uint8_t direction, uint32_t *ret_value );

// The function to change firmware internal calibrations.
uint8_t acamera_api_calibration( uint8_t type, uint8_t id, uint8_t direction, void *data, uint32_t data_size, uint32_t *ret_value );

// The function to send a frame buffer to the firmware.
uint8_t acamera_api_frame_buffer( uint32_t dma_output, uint8_t direction, void *frames, uint32_t frame_num, uint32_t *ret_num );

#endif //_ACAMERA_COMMAND_API_H_