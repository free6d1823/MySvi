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

#ifndef __GENERAL__ROUTER_H__
#define __GENERAL__ROUTER_H__

#include "system_types.h"


typedef enum {
    CMD_DIRECTION_GET,
    CMD_DIRECTION_SET,
} acamera_cmd_direction;

typedef enum {
    CMD_ID_AE_INFO,
    CMD_ID_CCM_INFO,
    CMD_ID_CMOS_CURRENT_EXPOSURE_LOG2,
    CMD_ID_CMOS_EXPOSURE_RATIO,
    CMD_ID_CMOS_HISTORY_SIZE,
    CMD_ID_CMOS_MAX_EXPOSURE_LOG2,
    CMD_ID_CMOS_TOTAL_GAIN,
    CMD_ID_DEFECT_PIXEL_INFO,
    CMD_ID_EXPOSURE_TARGET,
    CMD_ID_FRAME_EXPOSURE_SET,
    CMD_ID_HIST_INFO,
    CMD_ID_OUTPUT_FORMATTER_DATA,
    CMD_ID_SENSOR_INFO,
    CMD_ID_SENSOR_ALLOC_ANALOG_GAIN,
    CMD_ID_SENSOR_ALLOC_DIGITAL_GAIN,
    CMD_ID_SENSOR_ALLOC_WB_GAINS,
    CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME,
    CMD_ID_SENSOR_UPDATE,
    CMD_ID_SENSOR_SET_WDR_MODE,
    CMD_ID_SENSOR_REMOTE_FRAME_INFO,
    CMD_ID_WB_INFO,
    CMD_ID_WB_FRAME_QUANTITY,
    CMD_ID_MCFE_GET_SLOT_AVAIL_INPUTS,
    CMD_ID_HIST_IS_ON_SRQT,

    // MAX
    CMD_ID_MAX,
} acamera_cmd_id;

typedef enum {
    CMD_RESULT_OK,
    CMD_RESULT_INVALID_PARAM,
    CMD_RESULT_NOT_SUPPORTED,
    CMD_RESULT_ERR,
} acamera_cmd_result;

typedef struct {
    int32_t exposure_log2;
    uint32_t exposure_ratio;
    uint32_t contrast;
} acamera_cmd_ae_info;

typedef struct {
    int32_t exposure_log2;
    uint32_t exposure_ratio;
} acamera_cmd_exposure_target;

typedef struct {
    uint32_t again_reg;
    uint32_t again_log2;
} acamera_cmd_set_analog_gain;

typedef struct _exposure_data_set_t {
    uint32_t integration_time; /* fixed point format Q"sensor_info.integration_time_precision" */
    uint32_t again_reg;
    uint32_t dgain_reg;
    int32_t isp_dgain_log2;
    uint32_t exposure_ratio;
    uint32_t actual_integration_time; /* fixed point format Q"sensor_info.integration_time_precision" */

    uint32_t exposure_ratio_short;
    uint32_t integration_time_long; /* fixed point format Q"sensor_info.integration_time_precision" */

    uint32_t exposure_ratio_medium;
    uint32_t integration_time_medium; /* fixed point format Q"sensor_info.integration_time_precision" */

    uint32_t exposure_ratio_medium2;
    uint32_t integration_time_medium2; /* fixed point format Q"sensor_info.integration_time_precision" */
} exposure_data_set_t;

typedef struct _exposure_info_set_t {
    int32_t exposure_log2;
    int32_t again_log2;
    int32_t dgain_log2;
    int32_t isp_dgain_log2;
} exposure_info_set_t;

typedef struct _exposure_set_t {
    exposure_info_set_t info;
    exposure_data_set_t data;
} exposure_set_t;

typedef struct {
    uint8_t light_source;
    uint8_t light_source_previous;
    uint8_t light_source_ccm;
    uint8_t light_source_ccm_previous;
    uint8_t light_source_change_frames;
    uint8_t light_source_change_frames_left;
} acamera_cmd_ccm_info;

typedef struct {
    int32_t wb_log2[4];
    int32_t temperature_detected;
    uint8_t p_high;
    uint8_t light_source_candidate;
} acamera_cmd_wb_info;

typedef struct {
    int16_t accel_angle;
} acamera_cmd_accel_data;


typedef struct {
    uint32_t switch_light_source_detect_frames_quantity;
    uint32_t switch_light_source_change_frames_quantity;
} acamera_cmd_wb_frame_quantity;

typedef struct {
    uint16_t total_width;
    uint16_t total_height;
    uint16_t active_width;
    uint16_t active_height;
    uint16_t black_level;
    uint32_t lines_per_second;
    uint8_t cfa_pattern;
    int32_t again_log2_max;
    int32_t dgain_log2_max;
    int32_t again_accuracy;
    int32_t wb_gain_log2_max;
    uint32_t integration_time_min;
    uint32_t integration_time_max;
    uint32_t integration_time_medium_max;
    uint32_t integration_time_long_max;
    uint32_t integration_time_limit;
    uint8_t integration_time_precision;
    uint8_t integration_time_apply_delay;
    uint8_t sensor_exp_number;
    uint8_t isp_exposure_channel_delay;
    uint8_t sensor_output_bits;
    uint8_t is_remote;
} acamera_cmd_sensor_info;

typedef struct {
    uint32_t int_time;
    uint32_t int_time_M;
    uint32_t int_time_M2;
    uint32_t int_time_L;

    // NOTE:
    // We need this dummy variable because we want to convert this struct pointer
    // to (const uint32_t *), without this dummy, build has warnings and nios2
    // toolchain tream warning as errors.
    uint32_t dummy;
} acamera_cmd_sensor_integration_time;

typedef struct {
    uint32_t fullhist_sum;
    const uint32_t *fullhist;
} acamera_cmd_hist_info;

typedef struct {
    uint16_t autolevel_black_level;
    uint16_t autolevel_white_level;

    // NOTE:
    // We need this dummy variable because we want to convert this struct pointer
    // to (const uint32_t *), without this dummy, build has warnings and nios2
    // toolchain tream warning as errors.
    uint32_t dummy;
} acamera_cmd_sharpening_info;

typedef struct {
    uint8_t hp_started;
} acamera_cmd_defect_pixel_info;

typedef struct acamera_cmd_sensor_remote_frame_info {
    void *p_remote_sensor_frame;
} acamera_cmd_sensor_remote_frame_info;

acamera_cmd_result general_handle_cmd( void *p_ictx, acamera_cmd_id cmd_id, acamera_cmd_direction dir, const void *value, void *ret_value );

/**
 * @brief      Wrapper macro to call general_handle_cmd and check return code
 * @details    If return code is not #CMD_RESULT_OK then print error message. Returns error code
 */
#define WRAP_GENERAL_CMD( p_ictx, cmd_id, dir, value, ret_value ) ( {                     \
    acamera_cmd_result rc;                                                                \
    rc = general_handle_cmd( ( p_ictx ), ( cmd_id ), ( dir ), ( value ), ( ret_value ) ); \
    if ( rc != CMD_RESULT_OK ) {                                                          \
        LOG( LOG_ERR,                                                                     \
             "general_handle_cmd(..., " #cmd_id ", " #dir ", ...) failed with error: %d", \
             rc );                                                                        \
    }                                                                                     \
    rc;                                                                                   \
} )

/**
 * @brief       Value that allow to avoid error condition:
 *              "Not enough free input ports available (required: %d, available: %d)"
 *              in function: void sensor_config( sensor_fsm_ptr_t p_fsm ); file: sensor_func.c
 *              for "PLATFORM_MODEL" build configuration
 */
#if defined( PLATFORM_MODEL )
#define PLATFORM_MODEL_GENERAL_MCFE_SLOT_AVAIL_INPUTS ( 2 )
#endif


#endif /* __GENERAL__ROUTER_H__ */
