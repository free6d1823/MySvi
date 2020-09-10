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

#include "3a/ae/ae_acamera_core.h"
#include <string.h> //memset
#include "3a/acamera_math.h"
#include "3a/3a_config.h"

#define AE_CLIPPING_ANTIFLICKER_N ( 5U )

typedef struct {
    uint64_t WSNR_cumsum[ISP_FULL_HISTOGRAM_SIZE];
    uint32_t targets_history[AE_CLIPPING_ANTIFLICKER_N];
    uint32_t next_hist_idx;
    uint32_t max_target;

    uint32_t exposure_log2;
    uint32_t ae_hist_mean;
    int32_t error_log2;
    uint32_t exposure_ratio_avg;
    int64_t integrator;

    uint8_t ae_converged;
} ae_acamera_core_obj_t;


#define AE_FXPOINT_QBITS 6U

static uint16_t linear_interpolation_u16( const uint32_t x0, const uint8_t y0, const uint32_t x1, const uint8_t y1,
                                          const uint32_t x )
{
    uint16_t result = y0;

    if ( x1 != x0 ) {
        // division by zero is checked
        int32_t s32_temp = (int32_t)y0 + ( ( ( (int32_t)y1 - (int32_t)y0 ) * ( (int32_t)x - (int32_t)x0 ) ) /
                                           ( (int32_t)x1 - (int32_t)x0 ) );
        result = ( uint16_t )( s32_temp );
    }

    return result;
}

static uint16_t get_exposure_correction( const ae_acamera_core_obj_t *p_ae_core_obj,
                                         const ae_acamera_input_t *p_ae_acamera_input )
{
    const uint32_t exposure = acamera_math_exp2( p_ae_core_obj->exposure_log2, LOG2_GAIN_SHIFT, 6 );
    uint16_t correction = 0;

    if ( exposure <= p_ae_acamera_input->cali_data.ae_exp_corr_lut[0] ) {
        correction = p_ae_acamera_input->cali_data.ae_corr_lut[0];
    } else if ( exposure >= p_ae_acamera_input->cali_data
                                .ae_exp_corr_lut[p_ae_acamera_input->cali_data.ae_exp_corr_lut_len - 1U] ) {
        correction = p_ae_acamera_input->cali_data.ae_corr_lut[p_ae_acamera_input->cali_data.ae_exp_corr_lut_len - 1U];
    } else {
        uint32_t i;
        for ( i = 1; i < p_ae_acamera_input->cali_data.ae_exp_corr_lut_len; i++ ) {
            if ( exposure < p_ae_acamera_input->cali_data.ae_exp_corr_lut[i] ) {
                const uint32_t x0 = p_ae_acamera_input->cali_data.ae_exp_corr_lut[i - 1U];
                const uint8_t y0 = p_ae_acamera_input->cali_data.ae_corr_lut[i - 1U];
                const uint32_t x1 = p_ae_acamera_input->cali_data.ae_exp_corr_lut[i];
                const uint8_t y1 = p_ae_acamera_input->cali_data.ae_corr_lut[i];
                const uint32_t x = exposure;
                correction = linear_interpolation_u16( x0, y0, x1, y1, x );
                break;
            }
        }
    }
    return correction;
}

static uint32_t adjacent_ratio_to_full( int32_t sensor_exp_number, uint32_t ratio )
{
    uint32_t result = 0;
    switch ( sensor_exp_number ) {
    case 4:
        result = ( ratio * ratio * ratio ) << 6;
        break;
    case 3:
        result = ( ratio * ratio ) << 6;
        break;
    case 2:
        result = ratio << 6;
        break;
    default:
        result = ratio << 6;
        break;
    }

    return result;
}

static uint32_t ae_get_max_clipped_amount( const ae_balanced_param_t *const param,
                                           const ae_acamera_input_t *const p_ae_acamera_input,
                                           const ae_stats_data_t *const stats )
{
    uint32_t max_clipped_amount;
    if ( ( p_ae_acamera_input->misc_info.flags.has_iridix == 1u ) &&
         ( p_ae_acamera_input->cali_data.ae_exp_ratio_adjustment != NULL ) &&
         ( p_ae_acamera_input->cali_data.ae_exp_ratio_adjustment_len != 0u ) ) {
        // Modulation of clipped pixels according to contrast of scene, this will be used if the correct tables are
        // provided.
        const uint32_t er_contrast_adj =
            acamera_calc_modulation_u16( (uint16_t)p_ae_acamera_input->misc_info.iridix_contrast,
                                         p_ae_acamera_input->cali_data.ae_exp_ratio_adjustment,
                                         p_ae_acamera_input->cali_data.ae_exp_ratio_adjustment_len );
        const uint32_t long_clip = ( uint32_t )( param->long_clip * er_contrast_adj ) >> 8;
        max_clipped_amount = ( uint32_t )( ( (uint64_t)stats->fullhist_sum * long_clip ) >> 8 ); // without modulation

    } else {
        max_clipped_amount = ( uint32_t )( ( (uint64_t)stats->fullhist_sum * param->long_clip ) >> 8U );
    }

    return max_clipped_amount;
}

static uint32_t ae_calculate_exposure_ratio( ae_acamera_core_obj_t *p_ae_core_obj, const ae_stats_data_t *stats,
                                             const ae_input_data_t *ae_input )
{
    // coverity[misra_c_2012_rule_11_5_violation] input pointers are stored as void*
    const ae_acamera_input_t *p_ae_acamera_input = (const ae_acamera_input_t *)( ae_input->acamera_input );
    const ae_balanced_param_t *param = p_ae_acamera_input->cali_data.ae_ctrl;
    uint32_t exp_ratio = 64;
    uint32_t max_clip_exp_ratio = 64;
    uint32_t ISP_HIST_SIZE = (uint32_t)ISP_FULL_HISTOGRAM_SIZE;

    const uint32_t max_exposure_ratio = adjacent_ratio_to_full(
        p_ae_acamera_input->misc_info.sensor_exp_number, p_ae_acamera_input->misc_info.global_max_exposure_ratio );

    if ( p_ae_acamera_input->misc_info.global_manual_exposure_ratio != 0U ) {
        exp_ratio = adjacent_ratio_to_full( p_ae_acamera_input->misc_info.sensor_exp_number,
                                            p_ae_acamera_input->misc_info.global_exposure_ratio );
    } else {

        const uint32_t max_clipped_amount = ae_get_max_clipped_amount( param, p_ae_acamera_input, stats );
        uint32_t inx = ISP_HIST_SIZE - 1U;
        uint32_t clipped_amount = stats->fullhist[inx];

        while ( ( clipped_amount <= max_clipped_amount ) && ( inx > 0U ) ) { // kernel ooops
            inx--;
            clipped_amount += stats->fullhist[inx];
        }
        exp_ratio = ( ( uint32_t )( ISP_HIST_SIZE - 1U ) << 7U ) / ( ( 2U * inx ) + 1U );
        max_clip_exp_ratio = exp_ratio;
        if ( p_ae_acamera_input->misc_info.sensor_exp_number > 1 ) {
            const uint32_t *hist = stats->fullhist;

            // Compute partial sums
            {
                p_ae_core_obj->WSNR_cumsum[0] = (uint64_t)hist[0] * acamera_sqrt32( 64 );
                uint32_t i = 1;
                for ( ; i < ISP_HIST_SIZE; ++i ) {
                    p_ae_core_obj->WSNR_cumsum[i] =
                        p_ae_core_obj->WSNR_cumsum[i - 1U] + ( (uint64_t)hist[i] * acamera_sqrt32( 64U * ( i + 1U ) ) );
                }
            }

            uint32_t ER_best = ( (uint32_t)1 << AE_FXPOINT_QBITS );
            uint64_t WSNR_best = p_ae_core_obj->WSNR_cumsum[ISP_HIST_SIZE - 1U];

            switch ( p_ae_acamera_input->misc_info.sensor_exp_number ) {
            case 2: {
                uint32_t er_cand = 1U;
                for ( ; er_cand < 16U; ++er_cand ) {
                    const uint32_t ER_candidate_sqr = ( er_cand << AE_FXPOINT_QBITS );

                    uint32_t clip_medium = ( ISP_HIST_SIZE ) / er_cand;
                    clip_medium = acamera_max_u32( 1U, clip_medium );
                    clip_medium = acamera_min_u32( clip_medium, ISP_HIST_SIZE - 1U );

                    // Unsigned because cumsums are monotonic
                    if ( clip_medium < ISP_HIST_SIZE ) { // Explicit check needed for static analysis ( Rule 18.1 )
                        uint64_t current_WSNR = ( ( p_ae_core_obj->WSNR_cumsum[ISP_HIST_SIZE - 1U] -
                                                    p_ae_core_obj->WSNR_cumsum[clip_medium] )
                                                  << AE_FXPOINT_QBITS ) +
                                                ( p_ae_core_obj->WSNR_cumsum[clip_medium] * ER_candidate_sqr );

                        if ( current_WSNR > WSNR_best ) {
                            WSNR_best = current_WSNR;
                            ER_best = ( ER_candidate_sqr * ER_candidate_sqr ) >> AE_FXPOINT_QBITS;
                        }
                    }
                }
                exp_ratio = ER_best;
            } break;

            case 3: {
                uint32_t er_cand = 1U;
                for ( ; er_cand < 16U; ++er_cand ) {
                    const uint32_t ER_candidate_sqr = ( er_cand << AE_FXPOINT_QBITS );

                    uint32_t clip_medium = ( ISP_HIST_SIZE ) / er_cand;
                    uint32_t clip_long = clip_medium / er_cand;

                    clip_long = acamera_max_u32( 1U, clip_long );
                    clip_long = acamera_min_u32( clip_long, ISP_HIST_SIZE - 2U );

                    clip_medium = acamera_max_u32( clip_long + 1U, clip_medium );
                    clip_medium = acamera_min_u32( clip_medium, ISP_HIST_SIZE - 1U );

                    // Unsigned because cumsums are monotonic
                    if ( clip_medium < ISP_HIST_SIZE ) { // Explicit check needed for static analysis ( Rule 18.1 )
                        uint64_t current_WSNR =
                            ( ( p_ae_core_obj->WSNR_cumsum[ISP_HIST_SIZE - 1U] -
                                p_ae_core_obj->WSNR_cumsum[clip_medium] )
                              << AE_FXPOINT_QBITS ) +
                            ( acamera_sqrt32( ER_candidate_sqr << AE_FXPOINT_QBITS ) *
                              ( p_ae_core_obj->WSNR_cumsum[clip_medium] - p_ae_core_obj->WSNR_cumsum[clip_long] ) ) +
                            ( p_ae_core_obj->WSNR_cumsum[clip_long] * ER_candidate_sqr );

                        if ( current_WSNR > WSNR_best ) {
                            WSNR_best = current_WSNR;
                            ER_best = ( ER_candidate_sqr * ER_candidate_sqr ) >> AE_FXPOINT_QBITS;
                        }
                    }
                }
                exp_ratio = ER_best;
            } break;

            case 4: {
                uint32_t er_cand = 1U;
                for ( ; er_cand < 16U; ++er_cand ) {
                    const uint32_t ER_candidate_sqr = ( er_cand << AE_FXPOINT_QBITS );

                    uint32_t clip_medium = ( ISP_HIST_SIZE ) / ( er_cand );
                    uint32_t clip_medium2 = clip_medium / er_cand;
                    uint32_t clip_long = clip_medium2 / er_cand;

                    clip_long = acamera_max_u32( 1U, clip_long );
                    clip_long = acamera_min_u32( clip_long, ISP_HIST_SIZE - 3U );

                    clip_medium2 = acamera_max_u32( clip_long + 1U, clip_medium2 );
                    clip_medium2 = acamera_min_u32( clip_medium2, ISP_HIST_SIZE - 2U );

                    clip_medium = acamera_max_u32( clip_medium2 + 1U, clip_medium );
                    clip_medium = acamera_min_u32( clip_medium, ISP_HIST_SIZE - 1U );

                    const uint32_t canditade_sqr_root = acamera_sqrt32( ( ER_candidate_sqr << AE_FXPOINT_QBITS ) );
                    const uint32_t canditade_cube_root = acamera_math_exp2(
                        acamera_log2_fixed_to_fixed( ER_candidate_sqr, (int32_t)AE_FXPOINT_QBITS, AE_FXPOINT_QBITS ) /
                            3U,
                        AE_FXPOINT_QBITS, AE_FXPOINT_QBITS );

                    // Unsigned because cumsums are monotonic
                    if ( ( clip_medium < ISP_HIST_SIZE ) &&
                         ( clip_medium2 < ISP_HIST_SIZE ) ) { // Explicit check needed for static analysis ( Rule 18.1 )
                        uint64_t current_WSNR =
                            ( ( p_ae_core_obj->WSNR_cumsum[ISP_HIST_SIZE - 1U] -
                                p_ae_core_obj->WSNR_cumsum[clip_medium] )
                              << AE_FXPOINT_QBITS ) +
                            ( canditade_cube_root *
                              ( p_ae_core_obj->WSNR_cumsum[clip_medium] - p_ae_core_obj->WSNR_cumsum[clip_medium2] ) ) +
                            ( canditade_sqr_root *
                              ( p_ae_core_obj->WSNR_cumsum[clip_medium2] - p_ae_core_obj->WSNR_cumsum[clip_long] ) ) +
                            ( ER_candidate_sqr * p_ae_core_obj->WSNR_cumsum[clip_long] );

                        if ( current_WSNR > WSNR_best ) {
                            WSNR_best = current_WSNR;
                            ER_best = ( ER_candidate_sqr * ER_candidate_sqr ) >> AE_FXPOINT_QBITS;
                        }
                    }
                }
                exp_ratio = ER_best;
            } break;

            default: {
                exp_ratio = ER_best;
            } break;
            }

            exp_ratio = ( exp_ratio > max_clip_exp_ratio ) ? max_clip_exp_ratio : exp_ratio;
        }
    }

    if ( exp_ratio < 64U ) {
        exp_ratio = 64U;
    }
    if ( exp_ratio > max_exposure_ratio ) {
        exp_ratio = max_exposure_ratio;
    }
    if ( param->er_avg_coeff > 0U ) {
        p_ae_core_obj->exposure_ratio_avg +=
            exp_ratio - ( p_ae_core_obj->exposure_ratio_avg / param->er_avg_coeff ); // division by zero is checked
        exp_ratio = p_ae_core_obj->exposure_ratio_avg / param->er_avg_coeff;         // division by zero is checked
    }

    return exp_ratio;
}

static void ae_calculate_target( ae_acamera_core_obj_t *p_ae_core_obj, const ae_stats_data_t *stats,
                                 const ae_input_data_t *ae_input )
{
    if ( stats->fullhist_sum != 0U ) {
        // coverity[misra_c_2012_rule_11_5_violation] input pointers are stored as void*
        const ae_acamera_input_t *p_ae_acamera_input = (const ae_acamera_input_t *)( ae_input->acamera_input );
        const ae_balanced_param_t *param = p_ae_acamera_input->cali_data.ae_ctrl;

        uint8_t ae_comp = p_ae_acamera_input->misc_info.global_ae_compensation;
        uint32_t ISP_HIST_SIZE = (uint32_t)ISP_FULL_HISTOGRAM_SIZE;
        // calculate mean value
        uint32_t cnt;
        uint64_t acc = 0;
        uint32_t n = param->tail_weight;
        uint32_t m1;


        for ( cnt = 0; cnt < ( ISP_HIST_SIZE - n ); cnt++ ) {
            acc += ( ( 2U * (uint64_t)cnt ) + 1U ) * stats->fullhist[cnt];
        }
        for ( ; cnt < ISP_HIST_SIZE; cnt++ ) {
            uint64_t tail_w = ( ( (uint64_t)cnt + (uint64_t)n ) - ( uint64_t )( ISP_HIST_SIZE ) + 2ULL ) / 2ULL;
            uint64_t hist_w = ( ( 2ULL * (uint64_t)cnt ) + 1ULL ) * stats->fullhist[cnt];

            acc += tail_w * hist_w;
        }
        m1 = ( uint32_t )( acamera_div64_u64( acc, ( uint64_t )( 2U * (uint64_t)stats->fullhist_sum ) ) );

        p_ae_core_obj->ae_hist_mean = m1;

        uint16_t log2_gain = ( uint16_t )( p_ae_acamera_input->misc_info.total_gain >> ( LOG2_GAIN_SHIFT - 8 ) );

        const uint32_t ldr_target = param->target_point;
        const uint32_t hdr_target = acamera_calc_modulation_u16( log2_gain, p_ae_acamera_input->cali_data.ae_hdr_target,
                                                                 p_ae_acamera_input->cali_data.ae_hdr_target_len );

        const uint32_t hi_target_prc = acamera_min_u32( param->hi_target_prc, 100U );
        const uint32_t bright_prc = acamera_min_u32( param->bright_prc, 100U );
        const uint32_t clip_target = ( uint32_t )( ( hi_target_prc * (uint64_t)stats->fullhist_sum ) / 100U );
        const uint32_t unclipped_point = ( uint32_t )( ( bright_prc * ISP_HIST_SIZE ) / 100U );

        // Find a clip point satisfying clipping thresholds
        uint32_t target_pc_point = 0;
        {
            uint32_t pc_counted = 0;
            for ( ; ( target_pc_point < ISP_HIST_SIZE ); ++target_pc_point ) {
                pc_counted += stats->fullhist[target_pc_point];
                if ( pc_counted >= clip_target ) {
                    break;
                }
            }
            target_pc_point = acamera_max_u32( 1U, target_pc_point ); // target_pc_point >= 1
        }

        const uint32_t is_unknown_target =
            ( uint32_t )( ( target_pc_point >= ( uint32_t )( ISP_HIST_SIZE - 1U ) ) ? 1U : 0U );
        if ( is_unknown_target != 0U ) {
            p_ae_core_obj->targets_history[p_ae_core_obj->next_hist_idx] = 0U;
            p_ae_core_obj->next_hist_idx++;
            if ( p_ae_core_obj->next_hist_idx >= AE_CLIPPING_ANTIFLICKER_N ) {
                p_ae_core_obj->next_hist_idx = 0U;
            }

            uint32_t old_target = hdr_target;
            uint32_t i = 0;
            uint32_t rIdx = p_ae_core_obj->next_hist_idx;
            for ( ; i < AE_CLIPPING_ANTIFLICKER_N; ++i ) {
                rIdx = ( rIdx > 0U ) ? ( rIdx - 1U ) : ( AE_CLIPPING_ANTIFLICKER_N - 1U );
                if ( p_ae_core_obj->targets_history[rIdx] > 0U ) {
                    old_target = p_ae_core_obj->targets_history[rIdx];
                    break;
                }
            }
            // Not using formula X + a * (Y - X) because of unsigned arguments
            p_ae_core_obj->max_target = ( uint32_t )(
                ( ( 819U * (uint64_t)p_ae_core_obj->max_target ) + ( 205U * (uint64_t)old_target ) ) >> 10U );
        } else {
            const uint32_t mean = ( ( m1 > 0U ) ? m1 : 1U );
            const uint32_t target_candidate =
                ( uint32_t )( ( ( 973U * (uint64_t)mean * (uint64_t)unclipped_point ) / target_pc_point ) >>
                              10U ); // division by zero is checked
                                     // 0.95 * 1024 = 973
            p_ae_core_obj->targets_history[p_ae_core_obj->next_hist_idx] = target_candidate;
            p_ae_core_obj->next_hist_idx++;
            if ( p_ae_core_obj->next_hist_idx >= AE_CLIPPING_ANTIFLICKER_N ) {
                p_ae_core_obj->next_hist_idx = 0;
            }

            p_ae_core_obj->max_target = target_candidate;
        }
        // clamp
        p_ae_core_obj->max_target = acamera_max_u32( p_ae_core_obj->max_target, hdr_target );
        p_ae_core_obj->max_target = acamera_min_u32( p_ae_core_obj->max_target, ldr_target );
        const uint32_t new_target = p_ae_core_obj->max_target;
        uint16_t exp_correction = get_exposure_correction( p_ae_core_obj, p_ae_acamera_input );

        uint32_t target_log2 = acamera_log2_fixed_to_fixed( new_target, 0, LOG2_GAIN_SHIFT );
        uint32_t mean_log2 = acamera_log2_fixed_to_fixed( m1, 0, LOG2_GAIN_SHIFT );
        uint32_t comp_factor =
            ( uint32_t )( (uint32_t)1UL << ( uint32_t )( (uint32_t)LOG2_GAIN_SHIFT - (uint32_t)6U + (uint32_t)1U ) );
        int32_t compensation_log2 = ( (int32_t)ae_comp - 0x80 ) * (int32_t)comp_factor;
        int32_t correction_log2 = ( (int32_t)exp_correction - 0x80 ) * (int32_t)comp_factor;

        p_ae_core_obj->error_log2 = (int32_t)target_log2 - (int32_t)mean_log2 + compensation_log2 + correction_log2;

        int32_t p_para = 0, n_para = 0;
        if ( param->AE_tol != 0U ) {
            p_para = (int32_t)acamera_log2_fixed_to_fixed( new_target, 0, LOG2_GAIN_SHIFT ) -
                     (int32_t)acamera_log2_fixed_to_fixed( new_target - param->AE_tol, 0, LOG2_GAIN_SHIFT );
            n_para = (int32_t)acamera_log2_fixed_to_fixed( new_target, 0, LOG2_GAIN_SHIFT ) -
                     (int32_t)acamera_log2_fixed_to_fixed( new_target + param->AE_tol, 0, LOG2_GAIN_SHIFT );
            if ( ( p_ae_core_obj->error_log2 <= p_para ) && ( p_ae_core_obj->error_log2 >= n_para ) ) {
                p_ae_core_obj->error_log2 = 0;
                p_ae_core_obj->ae_converged = 1;
            } else {
                p_ae_core_obj->ae_converged = 0;
            }
        } else {
            p_ae_core_obj->ae_converged = 0;
        }
    }
}

static void ae_calculate_exposure( ae_acamera_core_obj_t *p_ae_core_obj, const ae_stats_data_t *stats,
                                   const ae_input_data_t *ae_input, ae_acamera_output_t *p_ae_acamera_output )
{
    // coverity[misra_c_2012_rule_11_5_violation] input pointers are stored as void*
    const ae_acamera_input_t *p_ae_acamera_input = (ae_acamera_input_t *)( ae_input->acamera_input );

    uint32_t exposure_log2 = 0;

    if ( p_ae_acamera_input->misc_info.global_manual_exposure != 0U ) {
        exposure_log2 =
            acamera_log2_fixed_to_fixed( p_ae_acamera_input->misc_info.global_exposure, 6, LOG2_GAIN_SHIFT );
    } else {
        const ae_balanced_param_t *param = p_ae_acamera_input->cali_data.ae_ctrl;
        uint32_t coeff = param->pi_coeff;
        int64_t max_exposure;
        uint32_t max_exposure_log2 = p_ae_acamera_input->misc_info.max_exposure_log2;

        max_exposure = (int64_t)coeff * (int64_t)max_exposure_log2;
        p_ae_core_obj->integrator += p_ae_core_obj->error_log2;

        if ( p_ae_core_obj->integrator < 0 ) {
            p_ae_core_obj->integrator = 0;
        }
        if ( p_ae_core_obj->integrator > max_exposure ) {
            p_ae_core_obj->integrator = max_exposure;
        }
        // avoid negative exposure result
        int64_t common_exp = p_ae_core_obj->error_log2 + p_ae_core_obj->integrator;
        if ( common_exp < 0 ) {
            common_exp = 0;
        }
        exposure_log2 = (uint32_t)acamera_div64_u64( ( uint64_t )( common_exp ), (uint64_t)coeff );
    }

    p_ae_acamera_output->exposure_log2 = exposure_log2;
    p_ae_core_obj->exposure_log2 = exposure_log2;
    p_ae_acamera_output->exposure_ratio = ae_calculate_exposure_ratio( p_ae_core_obj, stats, ae_input );

    p_ae_acamera_output->ae_converged = p_ae_core_obj->ae_converged;
}

// coverity[misra_c_2012_rule_8_7_violation], part of the API
void *ae_acamera_core_init( uint32_t ctx_id )
{
    static ae_acamera_core_obj_t ae_core_objs[FIRMWARE_CONTEXT_NUMBER];

    uint32_t i;
    ae_acamera_core_obj_t *p_ae_core_obj = NULL;

    if ( ctx_id < (uint32_t)FIRMWARE_CONTEXT_NUMBER ) {
        p_ae_core_obj = &ae_core_objs[ctx_id];
        (void)memset( p_ae_core_obj, 0, sizeof( *p_ae_core_obj ) );

        for ( i = 0; i < AE_CLIPPING_ANTIFLICKER_N; ++i ) {
            p_ae_core_obj->targets_history[i] = 0;
        }

        p_ae_core_obj->exposure_ratio_avg = 64;
    }

    return p_ae_core_obj;
}

// coverity[misra_c_2012_rule_8_7_violation], part of the API
int32_t ae_acamera_core_deinit( const void *ae_ctx )
{
    int32_t ret = 0;

    if ( ae_ctx == NULL ) {
        ret = -1;
    }

    return ret;
}


// coverity[misra_c_2012_rule_8_7_violation], part of the API
int32_t ae_acamera_core_proc( void *ae_ctx, const ae_stats_data_t *stats, const ae_input_data_t *input,
                              const ae_output_data_t *output )
{
    int32_t result = 0;

    if ( ( ae_ctx == NULL ) || ( stats == NULL ) || ( input == NULL ) || ( input->acamera_input == NULL ) ||
         ( output == NULL ) || ( output->acamera_output == NULL ) ) {
        result = -1;
    } else {
        // coverity[misra_c_2012_rule_11_5_violation] User context is stored as void*
        ae_acamera_core_obj_t *p_ae_core_obj = (ae_acamera_core_obj_t *)ae_ctx;
        ae_acamera_output_t *p_ae_acamera_output = (ae_acamera_output_t *)output->acamera_output;

        ae_calculate_target( p_ae_core_obj, stats, input );

        ae_calculate_exposure( p_ae_core_obj, stats, input, p_ae_acamera_output );

        result = 0;
    }

    return result;
}
