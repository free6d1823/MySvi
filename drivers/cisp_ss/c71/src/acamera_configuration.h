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

#ifndef __ACAMERA_CONFIGURATION_H__
#define __ACAMERA_CONFIGURATION_H__


// stub-bare-metal-r1-quad-2T-dummy-2M-dummy.set
#define AFBC_ENABLE 1
#define FIRMWARE_CONTEXT_NUMBER 1
#define PHY_ADDR_ISP 0x0E80C0000//0x7fc00000
#define PHY_ADDR_FPGA 0x7fe00000
#define PHY_ADDR_CDMA 0x61000000//DDR //0x8f5d0000
#define PHY_ADDR_BUFF_POOL 0x60000000 //DDR
#define ISPAS_MINUS_SYSPHY 0
#define LEN_ADDR_ISP 0x20000
#define LEN_ADDR_FPGA 0x2000
#define LEN_ADDR_META 0
#define ISP_HAS_SENSOR_FSM 1
#define ISP_HAS_CONTROL_FSM 1
#define ISP_HAS_DECOMPANDER_FSM 0
#define ISP_HAS_OUTPUT_FORMATTER_FSM 1
#define ISP_HAS_CROP_FSM 0
#define ISP_HAS_CMOS_FSM 0
#define ISP_HAS_AE_BALANCED_FSM 0
#define ISP_HAS_HISTOGRAM_FSM 0
#define ISP_HAS_AWB_MESH_NBP_FSM 0
#define ISP_HAS_COLOR_MATRIX_FSM 0
#define ISP_HAS_MESH_SHADING_FSM 0
#define ISP_HAS_IRIDIX8_FSM 0
#define ISP_HAS_MCFE_FSM 1
#define ISP_HAS_FRAME_CHECK_FSM 1
#define ISP_HAS_SHARPENING_FSM 0
#define ISP_HAS_NOISE_REDUCTION_FSM 0
#define ISP_HAS_DEFECT_PIXEL_FSM 0
#define ISP_HAS_ISP_WRAPPER_DUMMY_FSM 0
#define ISP_HAS_CAC_FSM 0
#define ISP_HAS_RADIAL_SHADING_FSM 0
#define ISP_HAS_NOISE_PROFILE_FSM 0
#define ISP_HAS_DEMOSAIC_FSM 0
#define ISP_HAS_ML_BIST_FSM 0
#define ISP_HAS_RAW_FE_FSM 0
#define ISP_HAS_CONNECTION_BUFFER 0
#define IS_MALI_C71 1
// project_defaults.set
#define ISP_HAS_CONNECTION_CHARDEV 0
#define ISP_HAS_CONNECTION_SOCKET 0
#define ISP_HAS_CONNECTION_SOCKET_PORT 0
#define ISP_HAS_CONNECTION_UART 0
#define ACAMERA_ISP_PROFILING 0
#define ACAMERA_ISP_PROFILING_INIT 0
#define ISP_HISTOGRAM_POSITION_IS_BE 1
#define ISP_HISTOGRAM_BE_POSITION AE_HISTOGRAM_TAP_AFTER_DECOMPANDER
#define ISP_PROCESS_NUM_EVENTS_QUANT 5
#define ACAMERA_EVENT_QUEUE_SIZE 512
#define AE_CENTER_ZONES 0x0000FFFF
#define BLACK_LEVEL_SHIFT_DG 12
#define BLACK_LEVEL_SHIFT_FS 4
#define BLACK_LEVEL_SHIFT_HIST 8
#define CONNECTION_BUFFER_SIZE ( 4 * 8192 )
#define DEBUG_FRAME_COUNT 0
#define FW_HAS_CONTROL_CHANNEL 0
#define KERNEL_MODULE 0
#define LOG2_GAIN_SHIFT 18
#define SENSOR_SEQ_BINARY_AND_EXTERNAL 0
#define STATISTICS_BUFFER_DATA_LOCALLY 1
#define SYSTEM_EXPOSURE_RATIO_DEFAULT 8
#define SYSTEM_LOG_DEFAULT_VALUE LOG_LEVEL_NOTICE
#define SYSTEM_LOG_USE_COLOR 1
#define USER_MODULE 0
#define MODEL_MODULE 0
#define FRAME_STREAM_MAX_FRAMES 10
#endif
