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

#include "3a/iridix/iridix_acamera_core.h"
#include "3a/acamera_math.h"
#include "3a/3a_config.h"


typedef struct {
    uint16_t strength_target;

    uint16_t dark_enh;
    uint32_t dark_enh_avg;
    uint32_t iridix_global_DG_avg;

    uint32_t iridix_contrast;
    uint16_t iridix_global_DG;

    uint16_t mp_iridix_strength;
} iridix_acamera_core_obj_t;

// @brief Calculate strength clip
//
// @param[in]  p_iridix_core_obj    Iridix ctx core object
// @param[in]  p_input  Input params
//
// @return    strength Strength target
//
static uint16_t iridix_control_strength_clip_calculate( iridix_acamera_core_obj_t *p_iridix_core_obj,
                                                        const iridix_acamera_input_t *p_input )
{
    // Calculate iridix strength based on the histogram of the current image

    uint32_t max_str, max_drk;
    const uint32_t cur_exposure_log2 = (uint32_t)p_input->misc_info.cur_exposure_log2;
    const uint32_t cali_iridix_min_max_str0 = (uint32_t)p_input->cali_data.cali_iridix_min_max_str[0];
    const uint32_t ev_lim_no_str = p_input->cali_data.cali_iridix_ev_lim_no_str[0];
    const uint32_t cali_iridix_ev_lim_full_str0 = p_input->cali_data.cali_iridix_ev_lim_full_str[0];

    if ( cur_exposure_log2 < cali_iridix_ev_lim_full_str0 ) {
        max_str = 100u;
    } else if ( ev_lim_no_str < cur_exposure_log2 ) {
        max_str = 0u;
    } else {
        /* Ensure tmp_ev_lim != 0 to avoid division by 0.*/
        uint32_t tmp_ev_lim = ev_lim_no_str - cali_iridix_ev_lim_full_str0;
        tmp_ev_lim = ( tmp_ev_lim != 0u ) ? tmp_ev_lim : 1u;

        /* cur_exposure_log2 >=  cali_iridix_ev_lim_full_str0, max_str cannot be negative. */
        max_str = 100u - ( ( 100u * ( cur_exposure_log2 - cali_iridix_ev_lim_full_str0 ) ) / tmp_ev_lim );
    }

    if ( ( max_str < cali_iridix_min_max_str0 ) && ( cur_exposure_log2 < cali_iridix_ev_lim_full_str0 ) ) {
        max_str = cali_iridix_min_max_str0;
    }

    // Clip iridix strength based on the calculated maxima
    const uint16_t ir_str =
        ( p_iridix_core_obj->mp_iridix_strength > max_str ) ? (uint16_t)max_str : p_iridix_core_obj->mp_iridix_strength;

    //////////////////////////// clip dk according to ev
    const uint32_t ev_lim_no_drk = p_input->cali_data.cali_iridix_ev_lim_no_str[1];

    if ( cur_exposure_log2 < cali_iridix_ev_lim_full_str0 ) {
        max_drk = 100u;
    } else if ( ev_lim_no_drk < cur_exposure_log2 ) {
        max_drk = 0u;
    } else {
        /* Ensure tmp_drk != 0 to avoid division by 0.*/
        uint32_t tmp_drk = ev_lim_no_drk - cali_iridix_ev_lim_full_str0;
        tmp_drk = ( tmp_drk != 0u ) ? tmp_drk : 1u;

        /* cur_exposure_log2 >=  cali_iridix_ev_lim_full_str0, max_str cannot be negative. */
        max_drk = 100u - ( ( 100u * ( cur_exposure_log2 - cali_iridix_ev_lim_full_str0 ) ) / tmp_drk );
    }

    // Clip dark enh
    const uint16_t min_dk = (uint16_t)p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->min_dk;
    const uint16_t max_dk = (uint16_t)p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->max_dk;
    const uint16_t m = max_dk - min_dk;
    const uint16_t dk_enh_clip = min_dk + ( ( m * (uint16_t)max_drk ) / 100u );

    // Clip iridix dark enh based on the calculated maxima
    p_iridix_core_obj->dark_enh =
        ( p_iridix_core_obj->dark_enh > dk_enh_clip ) ? ( dk_enh_clip ) : p_iridix_core_obj->dark_enh;

    const uint16_t smin = (uint16_t)p_input->misc_info.global_minimum_iridix_strength;
    const uint16_t smax = (uint16_t)p_input->misc_info.global_maximum_iridix_strength;
    const uint16_t strength = ( 256u * smin ) + ( ( 256u * ( smax - smin ) * ir_str ) / 100u );

    return strength;
}

// @brief Get index of histogram
//
// @param[in]  p_stats      Pointer to histogram
// @param[in]  cutoff       Cutoff value
//
// @return    index Value of index
//
static uint32_t hist_get_index( const iridix_stats_data_t *p_stats, const uint32_t cutoff )
{
    uint32_t index = 0;
    uint32_t chist = 0;
    uint32_t i;
    for ( i = 0; i < p_stats->fullhist_size; i++ ) {
        chist += p_stats->fullhist[i];
        if ( cutoff <= chist ) {
            index = i;
            break;
        }
    }
    return index;
}


static uint16_t iridix_control_dark_enhancement_and_strength_calculate( iridix_acamera_core_obj_t *p_iridix_core_obj,
                                                                        const iridix_stats_data_t *p_stats,
                                                                        const iridix_acamera_input_t *p_input )
{
    // Calculate iridix strength based on the histogram of the current image
    int32_t ir_strength_max_ratio = 100;

    const uint32_t dark_prc = acamera_min_u32( p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->dark_prc, 100u );
    const uint32_t bright_prc =
        acamera_min_u32( p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->bright_prc, 100u );

    // dark enhancement parameters
    uint32_t min_dk = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->min_dk;
    const uint32_t max_dk = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->max_dk;
    const uint32_t pD_cut_min = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->pD_cut_min;
    const uint32_t pD_cut_max = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->pD_cut_max;
    const uint32_t dark_contrast_min = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->dark_contrast_min;
    const uint32_t dark_contrast_max = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->dark_contrast_max;
    // Iridix strength parameters
    const uint32_t min_str = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->min_str;
    const uint32_t max_str = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->max_str;
    const uint32_t dark_prc_gain_target = p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->dark_prc_gain_target;
    const uint32_t contrast_min =
        p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->contrast_min; // U24.8 tuning parameter
    const uint32_t contrast_max =
        p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->contrast_max; // U24.8 tuning parameter
    const uint32_t iridix_max_gain =
        p_input->cali_data.cali_iridix_strength_dk_enh_ctrl->max_iridix_gain;  // U24.8 tuning parameter
    const uint32_t target_LDR = p_input->cali_data.cali_ae_ctrl->target_point; // This should correspond to 0.48 point
                                                                               // in RAW histogram so that mean
                                                                               // intensity value after gamma correction
                                                                               // is 18% grey (122 in 0:255 histogram)

    // pH, and pD are the percentage of pixels for dark and highlight
    const uint32_t pD = ( p_stats->fullhist_sum * dark_prc ) / 100u;
    const uint32_t pH = ( p_stats->fullhist_sum * bright_prc ) / 100u;
    // mid point of histogram
    const uint32_t tpixels_median = p_stats->fullhist_sum / 2u;

    // calculate median of histogram
    uint32_t median = hist_get_index( p_stats, tpixels_median );

    // calculate pH_cut - intensity cut for highlight pixels
    uint32_t pH_cut = hist_get_index( p_stats, pH );

    // calculate pD - - intensity cut for dark pixels
    uint32_t pD_cut = hist_get_index( p_stats, pD );

    pH_cut = ( pH_cut == 0u ) ? 1u : pH_cut;
    pD_cut = ( pD_cut == 0u ) ? 1u : pD_cut;

    // Compensate for iridix global digital gain
    pD_cut = ( pD_cut * (uint32_t)p_iridix_core_obj->iridix_global_DG ) >> 8;
    pH_cut = ( pH_cut * (uint32_t)p_iridix_core_obj->iridix_global_DG ) >> 8;
    pH_cut = ( pH_cut == 0u ) ? 1u : pH_cut;
    pD_cut = ( pD_cut == 0u ) ? 1u : pD_cut;

    median = ( median * (uint32_t)p_iridix_core_obj->iridix_global_DG ) >> 8u;

    /*
        Calculate dark enhancement as a function of intensity cut of dark pixels
                            f(pD_cut)
            max_dk     ___
                    |    \
                    |    .
                    |     \
                    |      .
                    |        \_____________
            min_dk    |
                    |--|----|-------------
                    pD_cut_min   pD_cut_max
    */

    const uint32_t d_dk = ( max_dk - min_dk ) << 8;
    const int32_t d_pD = ( ( pD_cut_min != pD_cut_max ) ? ( (int32_t)pD_cut_min - (int32_t)pD_cut_max ) : 1 );
    const int32_t m_dk_pD = (int32_t)d_dk / d_pD;

    uint32_t u32_temp; // We require a temp variable for storing u32 results before casting to i32 due to rule 10.8.
    u32_temp = max_dk << 8U;
    const int32_t offset_dk_pD = ( int32_t )( u32_temp );

    int32_t dk_enh_Icut =
        acamera_signed_right_shift( ( ( m_dk_pD * ( (int32_t)median - (int32_t)pD_cut_min ) ) + offset_dk_pD ), 8 );

    u32_temp = pH_cut << 8U;
    const int32_t contrast = ( ( int32_t )( u32_temp ) / (int32_t)pD_cut ); // U24.8

    if ( median <= 2u ) {
        min_dk = ( max_dk * 91u ) / 100u;
    }

    u32_temp = ( max_dk - min_dk ) << 8;
    const uint32_t d_dark_contrast =
        ( ( dark_contrast_max != dark_contrast_min ) ? ( dark_contrast_max - dark_contrast_min ) : 1U );
    const int32_t m_dk_contrast = (int32_t)u32_temp / (int32_t)d_dark_contrast; // U24.8


    u32_temp = max_dk << 8;
    const int32_t offset_dk_contrast = ( int32_t )( u32_temp );

    int32_t dk_enh = acamera_signed_right_shift(
        ( ( m_dk_contrast * ( contrast - (int32_t)dark_contrast_max ) ) + offset_dk_contrast ), 8 ); // U32.0
    dk_enh = ( dk_enh_Icut > dk_enh ) ? dk_enh : dk_enh_Icut;
    if ( dk_enh < (int32_t)min_dk ) {
        dk_enh = (int32_t)min_dk;
    } else if ( dk_enh > (int32_t)max_dk ) {
        dk_enh = (int32_t)max_dk;
    } else {
        ; /* No action required . MisraC rule 15.7 */
    }

    // time filter for iridix dark enhancement
    uint16_t dark_enh_coeff = (uint16_t)p_input->cali_data.cali_iridix_avg_coef[0] * 2u;

    if ( dark_enh_coeff > 1u ) {
        p_iridix_core_obj->dark_enh_avg +=
            (uint32_t)dk_enh -
            ( p_iridix_core_obj->dark_enh_avg / (uint32_t)dark_enh_coeff );              // division by zero is checked
        dk_enh = ( (int32_t)p_iridix_core_obj->dark_enh_avg / (int32_t)dark_enh_coeff ); // division by zero is checked
    }

    // Iridix strength is caclulated as: min(f(pD_cut),f(contrast))
    //------ f(pD_cut)
    const uint32_t dk_target = ( ( p_stats->fullhist_size * dark_prc_gain_target ) / 100u ) << 8;
    const int32_t ir_gain = acamera_signed_right_shift( ( (int32_t)dk_target / (int32_t)pD_cut ), 8 ); // U32.0

    int32_t ir_strength = 100 * ( ir_gain - 1 ) / ( (int32_t)iridix_max_gain - 1 );
    ir_strength = ( ir_strength > 100 ) ? 100 : ir_strength;
    ir_strength = ( ir_strength < 0 ) ? 0 : ir_strength;

    /*
                        f(contrast)
        max str |                --------
                |             /
                |           -
                |         /
                |      -
                |    /
                |....
        min str    |---|----------|--------
                contrast_min   contrast_max
        */

    // clip strength according to f(contrast)
    u32_temp = ( max_str - min_str ) << 8;
    const int32_t d_str = ( int32_t )( u32_temp );

    const int32_t d_target_ldr = ( ( target_LDR != 0u ) ? ( 0 - (int32_t)target_LDR ) : 1 );

    u32_temp = ( ( contrast_max - contrast_min ) != 0U ) ? ( contrast_max - contrast_min ) : 1U;
    const int32_t d_contrast = (int32_t)u32_temp;

    u32_temp = max_str << 8;
    const int32_t offset_str_contrast = (int32_t)u32_temp;

    if ( contrast <= (int32_t)contrast_min ) {
        ir_strength_max_ratio = (int32_t)min_str;
        if ( median <= target_LDR ) {
            const int32_t m_str_contrast = d_str / d_target_ldr; // U24.16
            ir_strength_max_ratio = acamera_signed_right_shift(
                ( ( m_str_contrast * ( (int32_t)median - 0 ) ) + offset_str_contrast ), 8 ); // U32.0
        }
    } else if ( contrast >= (int32_t)contrast_max ) {
        ir_strength_max_ratio = (int32_t)max_str;
    } else {

        if ( pH_cut < target_LDR ) {
            const int32_t m_str_contrast = d_str / d_target_ldr; // U24.16
            ir_strength_max_ratio = acamera_signed_right_shift(
                ( ( m_str_contrast * ( (int32_t)median - 0 ) ) + offset_str_contrast ), 8 ); // U32.0
        } else if ( median <= target_LDR ) {
            const int32_t m_str_contrast = d_str / d_target_ldr; // U24.16
            ir_strength_max_ratio = acamera_signed_right_shift(
                ( m_str_contrast * ( (int32_t)median - 0 ) ) + offset_str_contrast, 8 ); // U32.0
        } else {
            const int32_t m_str_contrast = d_str / d_contrast; // U24.16
            ir_strength_max_ratio = acamera_signed_right_shift(
                ( m_str_contrast * ( contrast - (int32_t)contrast_min ) ) + offset_str_contrast, 8 ); // U32.0
        }
    }

    ir_strength = ( ir_strength > ir_strength_max_ratio ) ? ir_strength_max_ratio : ir_strength;
    ir_strength = ( ir_strength < (int32_t)min_str ) ? (int32_t)min_str : ir_strength;

    p_iridix_core_obj->iridix_contrast = (uint32_t)contrast;
    p_iridix_core_obj->mp_iridix_strength = (uint16_t)ir_strength;

    return ( (uint16_t)dk_enh );
}

static uint16_t iridix_control_global_DG_calculate( iridix_acamera_core_obj_t *p_iridix_core_obj,
                                                    const iridix_stats_data_t *p_stats,
                                                    const iridix_acamera_input_t *p_input )
{

    /*
    Function Description:
    This function calculates the required digital gain, (independant from AE) so that iridix does not need to be used as
    a global gain.
    This gain will be set in accordance to contrast of the scene.
    */

    uint32_t i;
    // ------- Tuning parameters --------- //
    // This should correspond to 0.48 point in RAW histogram so that mean intensity value after gamma correction is 18%
    // grey (122 in 0:255 histogram)
    const uint32_t target_LDR = p_input->cali_data.cali_ae_ctrl->target_point;

    //  No of pixels that should be below hi_target_prc, limited to range of 0-100%
    const uint32_t bright_prc = acamera_min_u32( p_input->cali_data.cali_ae_ctrl->bright_prc, 100u );


    // Target for the bright_prc pixels to avoide/controll clipping
    const uint32_t hi_target_prc = p_input->cali_data.cali_ae_ctrl->hi_target_prc;
    const uint32_t ir_gdg_enable = p_input->cali_data.cali_ae_ctrl->enable_iridix_gdg;

    // max clipped gain will make sure there that only 1% of pixels is avobe 75% of histogram
    //
    // No. of pixels in cummulative histogram that is less than the intensity cut for highlight pixels. This percentage
    // corresponds to bright_prc
    const uint32_t pH = ( p_stats->fullhist_sum * bright_prc ) / 100u;

    // Intensity cut for highlight/clipped pixels. if clipping should be avoided bright_prc should be set to 100% of
    // pixels
    int32_t pClip_cut = -1;
    uint64_t acc = 0;
    uint64_t chist = 0;

    // calculate mean value and find the clip point
    for ( i = 0; i < p_stats->fullhist_size; i++ ) {
        acc += ( ( 2ULL * (uint64_t)i ) + 1ULL ) * (uint64_t)p_stats->fullhist[i];

        // if clip point >= 0: we already found it, don't need to continue
        if ( pClip_cut < 0 ) {
            chist += p_stats->fullhist[i];
            if ( (uint64_t)pH <= chist ) {
                pClip_cut = (int32_t)i;
            }
        }
    }

    // If we have not found a clip point then default to 1
    pClip_cut = ( pClip_cut <= 0 ) ? 1 : pClip_cut;

    const uint32_t hist_mean = ( uint32_t )( acamera_div64_u64( acc, 2ULL * (uint64_t)p_stats->fullhist_sum ) );

    const uint32_t hist_hi_target_clip = ( p_stats->fullhist_size * hi_target_prc / 100u ) << 8;

    // Try to always have a balance target as if it was a low dynamic range scene.
    // Default value of 256 (minima) is used. u32 is used for calculation, but the result is U4.8
    uint32_t gain = 256U;

    // pH pixels should be below hi_target_prc of histogram to avoide clipping
    if ( ir_gdg_enable == 1u ) {
        const uint32_t max_gain_clipping = ( hist_hi_target_clip ) / (uint32_t)pClip_cut; // U24.8
        gain = ( target_LDR << 8 ) / ( ( hist_mean != 0u ) ? hist_mean : 1u );            // U24.8
        gain = ( gain <= max_gain_clipping ) ? gain : max_gain_clipping;
        gain = ( gain > 256U ) ? gain : 256U;
        gain = ( gain > 4095U ) ? 4095U : gain; // 12 bits gain U4.8
    }

    // time filter for iridix global DG
    const uint32_t iridix_avg_coeff = ( uint32_t )( p_input->cali_data.cali_iridix_avg_coef[0] );
    if ( iridix_avg_coeff > 1u ) {
        p_iridix_core_obj->iridix_global_DG_avg +=
            gain - ( p_iridix_core_obj->iridix_global_DG_avg / iridix_avg_coeff ); // division by zero is checked
        gain = p_iridix_core_obj->iridix_global_DG_avg / iridix_avg_coeff;         // division by zero is checked
    }

    // The gain is clipped by this point we can down cast it safely
    return ( (uint16_t)gain );
}

static void iridix_set_strength_target( iridix_acamera_core_obj_t *p_iridix_core_obj,
                                        const iridix_acamera_input_t *input, const uint16_t strength_target )
{
    const uint16_t smin = (uint16_t)input->misc_info.global_minimum_iridix_strength * 256u;
    const uint16_t smax = (uint16_t)input->misc_info.global_maximum_iridix_strength * 256u;
    p_iridix_core_obj->strength_target = acamera_min_u16( acamera_max_u16( strength_target, smin ), smax );
}


// coverity[misra_c_2012_rule_8_7_violation], part of the API
void *iridix_acamera_core_init( uint32_t ctx_id )
{
    static iridix_acamera_core_obj_t iridix_core_objs[FIRMWARE_CONTEXT_NUMBER];
    iridix_acamera_core_obj_t *p_iridix_core_obj = NULL;

    if ( ctx_id < (uint32_t)FIRMWARE_CONTEXT_NUMBER ) {
        p_iridix_core_obj = &iridix_core_objs[ctx_id];
        (void)memset( p_iridix_core_obj, 0, sizeof( *p_iridix_core_obj ) );

        p_iridix_core_obj->dark_enh_avg = IRIDIX_STRENGTH_TARGET * CALIBRATION_IRIDIX_AVG_COEF_INIT * 2;
        p_iridix_core_obj->iridix_global_DG_avg = IRIDIX_STRENGTH_TARGET * CALIBRATION_IRIDIX_AVG_COEF_INIT * 2;
        p_iridix_core_obj->iridix_contrast = 256;
        p_iridix_core_obj->iridix_global_DG = 256;
        p_iridix_core_obj->dark_enh = 15000;
        p_iridix_core_obj->strength_target = IRIDIX_STRENGTH_TARGET;
    }

    return p_iridix_core_obj;
}

// coverity[misra_c_2012_rule_8_7_violation], part of the API
int32_t iridix_acamera_core_deinit( const void *iridix_ctx )
{
    int32_t ret = 0;

    if ( iridix_ctx == NULL ) {
        ret = -1;
    }

    return ret;
}

// coverity[misra_c_2012_rule_8_7_violation], part of the API
int32_t iridix_acamera_core_proc( void *iridix_ctx, const iridix_stats_data_t *stats, const iridix_input_data_t *input,
                                  const iridix_output_data_t *output )
{
    int32_t ret = 0;

    if ( ( iridix_ctx == NULL ) || ( stats == NULL ) || ( input == NULL ) || ( input->acamera_input == NULL ) ||
         ( output == NULL ) || ( output->acamera_output == NULL ) ) {
        ret = -1;
    }

    if ( ret == 0 ) {
        // coverity[misra_c_2012_rule_11_5_violation] User context is stored as void*
        iridix_acamera_core_obj_t *p_iridix_core_obj = (iridix_acamera_core_obj_t *)iridix_ctx;

        // coverity[misra_c_2012_rule_11_5_violation] input pointers are stored as void*
        const iridix_acamera_input_t *p_acamera_input = (const iridix_acamera_input_t *)input->acamera_input;
        iridix_acamera_output_t *p_acamera_output = (iridix_acamera_output_t *)output->acamera_output;

        if ( p_acamera_input->misc_info.global_manual_iridix == 0u ) {

            p_iridix_core_obj->iridix_global_DG =
                iridix_control_global_DG_calculate( p_iridix_core_obj, stats, p_acamera_input );
            p_iridix_core_obj->dark_enh =
                iridix_control_dark_enhancement_and_strength_calculate( p_iridix_core_obj, stats, p_acamera_input );
            const uint16_t strength_target =
                iridix_control_strength_clip_calculate( p_iridix_core_obj, p_acamera_input );
            iridix_set_strength_target( p_iridix_core_obj, p_acamera_input, strength_target );

        } else {

            // Manual iridix, set the strength target as given by the user.
            iridix_set_strength_target( p_iridix_core_obj, p_acamera_input,
                                        (uint16_t)p_acamera_input->misc_info.global_iridix_strength_target << 8 );
        }

        // output values
        {
            p_acamera_output->strength_target = p_iridix_core_obj->strength_target;
            p_acamera_output->dark_enh = p_iridix_core_obj->dark_enh;
            p_acamera_output->iridix_global_DG = p_iridix_core_obj->iridix_global_DG;
            p_acamera_output->iridix_contrast = p_iridix_core_obj->iridix_contrast;
        }
    }

    return ret;
}
