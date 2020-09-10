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

#ifndef AE_BALANCED_PARAM_H
#define AE_BALANCED_PARAM_H

#include "3a/misc/acamera_types.h"

/**
 * @brief Balanced parameter struct used by Iridix and AE algorithms.
 * This structure should match a corresponding calibration table.
 */
typedef struct {
    uint32_t pi_coeff;          /**<  AE convergance ratio, only used by AE. */
    uint32_t target_point;      /**< LDR AE target, this should match 18% grey of the output gamma. */
    uint32_t tail_weight;       /**< AE tail weight. */
    uint32_t long_clip;         /**< WDR mode only: Max percentage of clipped pixels for long exposure. 256 == 100% clipped. */
    uint32_t er_avg_coeff;      /**< WDR mode only: Time filter for exposure ratio */
    uint32_t bright_prc;        /**< Bright percentage of pixels that should be below hi_target_prc */
    uint32_t hi_target_prc;     /**< Highlights percentage, target for tail of histogram. */
    uint32_t enable_iridix_gdg; /**< 1:0 enable:disable for iridix global gain*/
    uint32_t AE_tol;            /**< AE tolerance */
} ae_balanced_param_t;


#endif
