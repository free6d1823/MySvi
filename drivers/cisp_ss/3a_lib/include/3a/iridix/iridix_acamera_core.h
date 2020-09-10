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

#ifndef IRIDIX_ACAMERA_CORE_H_
#define IRIDIX_ACAMERA_CORE_H_

#include "3a/misc/acamera_types.h"
#include "3a/ae/ae_balanced_param.h" // Iridix requires ae_balanced_param_t

typedef struct {
    const uint32_t *fullhist;
    uint32_t fullhist_size;
    uint32_t fullhist_sum;
} iridix_stats_data_t;


typedef struct {
    void *custom_input;
    void *acamera_input;
} iridix_input_data_t;


typedef struct {
    void *custom_output;
    void *acamera_output;
} iridix_output_data_t;


typedef struct {

    uint8_t global_manual_iridix;
    uint8_t global_iridix_strength_target;
    uint8_t global_minimum_iridix_strength;
    uint8_t global_maximum_iridix_strength;

    int32_t cur_exposure_log2;
} iridix_misc_info_t;

/**@warning this must match the calibration entry associated in layout*/
typedef struct {
    uint32_t dark_prc;
    uint32_t bright_prc;
    uint32_t min_dk;     // minimum dark enhancement //48
    uint32_t max_dk;     // maximum dark enhancement //128
    uint32_t pD_cut_min; // minimum intensity cut for dark regions in which dk_enh will be applied
    uint32_t pD_cut_max; // maximum intensity cut for dark regions in which dk_enh will be applied
    uint32_t dark_contrast_min;
    uint32_t dark_contrast_max;
    uint32_t min_str;              // iridix strength in percentage
    uint32_t max_str;              // iridix strength in percentage: 50 = 1x gain. 100 = 2x gain
    uint32_t dark_prc_gain_target; // target in histogram (percentage) for dark_prc after iridix is applied
    uint32_t contrast_min;         // clip factor of strength for LDR scenes.  10 << 8
    uint32_t contrast_max;         // clip factor of strength for HDR scenes. 14 << 8
    uint32_t max_iridix_gain;
    uint32_t print_debug;
} iridix_strength_dk_enh_control_t;


typedef struct {

    uint8_t *cali_iridix_avg_coef;

    uint16_t *cali_iridix_min_max_str;

    ae_balanced_param_t *cali_ae_ctrl;
    uint32_t *cali_iridix_ev_lim_no_str;
    uint32_t *cali_iridix_ev_lim_full_str;
    iridix_strength_dk_enh_control_t *cali_iridix_strength_dk_enh_ctrl;

} iridix_calibration_data_t;


typedef struct {
    iridix_misc_info_t misc_info;
    iridix_calibration_data_t cali_data;
} iridix_acamera_input_t;

#ifdef USE_IRIDIX_CUSTOM_INPUT
typedef struct _iridix_custom_input_ {
    uint32_t *custom_cali_data;
    uint32_t custom_cali_data_size;
} iridix_custom_input_t;
#endif

typedef struct {
    uint16_t strength_target;
    uint16_t dark_enh;
    uint16_t iridix_global_DG;
    uint32_t iridix_contrast;
} iridix_acamera_output_t;


void *iridix_acamera_core_init( uint32_t ctx_id );
int32_t iridix_acamera_core_deinit( const void *iridix_ctx );
int32_t iridix_acamera_core_proc( void *iridix_ctx, const iridix_stats_data_t *stats, const iridix_input_data_t *input,
                                  const iridix_output_data_t *output );


#endif // IRIDIX_ACAMERA_CORE_H_
