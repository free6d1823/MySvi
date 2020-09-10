//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2020] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifndef AWB_ACAMERA_CORE_H_
#define AWB_ACAMERA_CORE_H_

#include "3a/misc/acamera_types.h"

#define D50_DEFAULT 256
#define AWB_LIGHT_SOURCE_UNKNOWN 0
#define AWB_LIGHT_SOURCE_A 0x01
#define AWB_LIGHT_SOURCE_D40 0x02
#define AWB_LIGHT_SOURCE_D50 0x03
#define AWB_LIGHT_SOURCE_A_TEMPERATURE 2850
#define AWB_LIGHT_SOURCE_D40_TEMPERATURE 4000
#define AWB_LIGHT_SOURCE_D50_TEMPERATURE 5000
#define AWB_DLS_LIGHT_SOURCE_A_D40_BORDER ( ( AWB_LIGHT_SOURCE_A_TEMPERATURE + AWB_LIGHT_SOURCE_D40_TEMPERATURE ) / 2 )
#define AWB_DLS_LIGHT_SOURCE_D40_D50_BORDER \
    ( ( AWB_LIGHT_SOURCE_D40_TEMPERATURE + AWB_LIGHT_SOURCE_D50_TEMPERATURE ) / 2 )

typedef struct {
    uint16_t rg;
    uint16_t bg;
    uint32_t sum;
} awb_zone_t;

typedef struct {
    awb_zone_t *awb_zones;
    uint32_t zones_size;
} awb_stats_data_t;


typedef struct {
    void *custom_input;
    void *acamera_input;
} awb_input_data_t;


typedef struct {
    void *custom_output;
    void *acamera_output;
} awb_output_data_t;


typedef struct {

    uint16_t log2_gain;
    int32_t cur_exposure_log2;
    uint32_t iridix_contrast;

    uint8_t global_manual_awb;
    uint16_t global_awb_red_gain;
    uint16_t global_awb_blue_gain;
} awb_misc_info_t;


typedef unsigned short ( *calibration_light_src_t )[2];

/**@warning this must match the calibration entry associated in layout*/
typedef struct {
    uint32_t enable_awb_mix_light;
    uint32_t lux_low;
    uint32_t lux_high;
    uint32_t contrast_threshold;
    uint32_t bg_threshold;
    uint32_t bg_weight;
    uint32_t rgHigh_LUT_max;
    uint32_t rgHigh_LUT_min;
    uint32_t print_debug;
} awb_mixed_light_param_t;


typedef struct {
    calibration_light_src_t cali_light_src;
    uint32_t cali_light_src_len;

    uint32_t *cali_evtolux_ev_lut;
    uint32_t cali_evtolux_ev_lut_len;

    uint32_t *cali_evtolux_lux_lut;
    uint32_t cali_evtolux_lux_lut_len;

    uint8_t *cali_awb_avg_coef;
    uint32_t cali_awb_avg_coef_len;

    uint16_t *cali_rg_pos;
    uint32_t cali_rg_pos_len;

    uint16_t *cali_bg_pos;
    uint32_t cali_bg_pos_len;

    uint16_t *cali_color_temp;
    uint32_t cali_color_temp_len;

    uint16_t *cali_ct_rg_pos_calc;
    uint32_t cali_ct_rg_pos_calc_len;

    uint16_t *cali_ct_bg_pos_calc;
    uint32_t cali_ct_bg_pos_calc_len;

    modulation_entry_t *cali_awb_bg_max_gain;
    uint32_t cali_awb_bg_max_gain_len;

    uint16_t *cali_mesh_ls_weight;
    uint16_t *cali_mesh_rgbg_weight;
    uint8_t *cali_evtolux_probability_enable;
    awb_mixed_light_param_t *cali_awb_mix_light_param;
    uint16_t *cali_ct65pos;
    uint16_t *cali_ct40pos;
    uint16_t *cali_ct30pos;
    uint32_t *cali_sky_lux_th;
    uint16_t *cali_wb_strength;
    uint16_t *cali_mesh_color_temperature;
    uint16_t *cali_awb_warming_ls_a;
    uint16_t *cali_awb_warming_ls_d75;
    uint16_t *cali_awb_warming_ls_d50;
    uint16_t *cali_awb_colour_preference;
} awb_calibration_data_t;


typedef struct {
    awb_misc_info_t misc_info;
    awb_calibration_data_t cali_data;
} awb_acamera_input_t;

#ifdef USE_AWB_CUSTOM_INPUT
typedef struct {
    uint32_t *custom_cali_data;
    uint32_t custom_cali_data_size;
} awb_custom_input_t;
#endif

typedef struct {
    uint16_t rg_coef;
    uint16_t bg_coef;
    int32_t temperature_detected;
    uint8_t p_high;
    uint8_t light_source_candidate;
    int32_t awb_warming[3];
    uint8_t awb_converged;
} awb_acamera_output_t;


void *awb_acamera_core_init( uint32_t ctx_id );
int32_t awb_acamera_core_deinit( const void *awb_ctx );
int32_t awb_acamera_core_proc( void *awb_ctx, const awb_stats_data_t *const stats, const awb_input_data_t *const input,
                               const awb_output_data_t *const output );


#endif
