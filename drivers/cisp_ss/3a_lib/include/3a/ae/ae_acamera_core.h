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

#ifndef AE_ACAMERA_CORE_H
#define AE_ACAMERA_CORE_H

#include "3a/misc/acamera_types.h"
#include "3a/ae/ae_balanced_param.h"

typedef struct {
    uint32_t *fullhist;
    uint32_t fullhist_size;
    uint32_t fullhist_sum;
    uint16_t *zone_hist;
    uint32_t zone_hist_size;
} ae_stats_data_t;

typedef struct {
    void *custom_input;
    void *acamera_input;
} ae_input_data_t;

typedef struct {
    void *custom_output;
    void *acamera_output;
} ae_output_data_t;

typedef struct {
    int32_t sensor_exp_number;

    uint32_t total_gain;
    uint32_t max_exposure_log2;
    uint32_t global_max_exposure_ratio;

    uint32_t iridix_contrast;
    uint32_t global_exposure;

    uint8_t global_ae_compensation;
    uint8_t global_manual_exposure;
    uint8_t global_manual_exposure_ratio;
    uint8_t global_exposure_ratio;

    struct {
        uint32_t has_iridix : 1;
    } flags;
} ae_misc_info_t;


typedef struct {
    uint8_t *ae_corr_lut;
    uint32_t ae_corr_lut_len;

    uint32_t *ae_exp_corr_lut;
    uint32_t ae_exp_corr_lut_len;

    modulation_entry_t *ae_hdr_target;
    uint32_t ae_hdr_target_len;

    modulation_entry_t *ae_exp_ratio_adjustment;
    uint32_t ae_exp_ratio_adjustment_len;

    ae_balanced_param_t *ae_ctrl;
} ae_calibration_data_t;


typedef struct {
    ae_misc_info_t misc_info;
    ae_calibration_data_t cali_data;
} ae_acamera_input_t;


#ifdef USE_AE_CUSTOM_INPUT
typedef struct {
    uint32_t *custom_cali_data;
    uint32_t custom_cali_data_size;
} ae_custom_input_t;
#endif // USE_AE_CUSTOM_INPUT


typedef struct {
    uint32_t exposure_log2;
    uint32_t exposure_ratio;

    uint8_t ae_converged;
} ae_acamera_output_t;


void *ae_acamera_core_init( uint32_t ctx_id );
int32_t ae_acamera_core_deinit( const void *ae_ctx );
int32_t ae_acamera_core_proc( void *ae_ctx, const ae_stats_data_t *stats, const ae_input_data_t *input,
                              const ae_output_data_t *output );


#endif
