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

#include "system_assert.h"
#include "acamera_command_api.h"
#include "acamera_frontend_config.h"
#include "acamera_gamma_be0_mem_config.h"
#include "acamera_gamma_be1_mem_config.h"
#include "acamera_gamma_fe_mem_config.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_DECOMPANDER


#define DECOMPANDER_HAS_SQ defined( ACAMERA_ISP_GAMMA_BE_BLACK_LEVEL_OUT_SQ_DEFAULT )
#define DECOMPANDER_HAS_DL defined( ACAMERA_ISP_GAMMA_BE_BLACK_LEVEL_OUT_DL_DEFAULT )

#if !( DECOMPANDER_HAS_SQ ) && !( DECOMPANDER_HAS_DL )
#error "DECOMPANDER_HAS_SQ or DECOMPANDER_HAS_DL required"
#endif

/**
 * input_formatter_bitwidht_alignment() - Set input formatter bit-width alignment.
 * @isp_base: ISP hw context memory base address.
 * @p_in_fmt: Pointer to input formatter control structure.
 *
 * This function has two implementations, depending on the Morgan ISP revision.
 *
 * Return: None
 */
#if IS_MALI_C71
static void input_formatter_bitwidth_alignment( uint32_t isp_base, const input_formatter_ctrl *p_in_fmt )
{
    acamera_isp_input_formatter_input1_bitwidth_select_write( isp_base, p_in_fmt->input1_bitwidth );
    acamera_isp_input_formatter_input2_bitwidth_select_write( isp_base, p_in_fmt->input2_bitwidth );
    acamera_isp_input_formatter_input3_bitwidth_select_write( isp_base, p_in_fmt->input3_bitwidth );
    acamera_isp_input_formatter_input4_bitwidth_select_write( isp_base, p_in_fmt->input4_bitwidth );

    acamera_isp_input_formatter_input1_alignment_write( isp_base, p_in_fmt->input1_aligment );
    acamera_isp_input_formatter_input2_alignment_write( isp_base, p_in_fmt->input2_aligment );
    acamera_isp_input_formatter_input3_alignment_write( isp_base, p_in_fmt->input3_aligment );
    acamera_isp_input_formatter_input4_alignment_write( isp_base, p_in_fmt->input4_aligment );
}
#else
static void input_formatter_bitwidth_alignment( uint32_t isp_base, const input_formatter_ctrl *p_in_fmt )
{
    acamera_isp_input_formatter_input_bitwidth_select_write( isp_base, p_in_fmt->input1_bitwidth );
    acamera_isp_input_formatter_input_alignment_write( isp_base, p_in_fmt->input1_aligment );
}
#endif // IS_MALI_C71


/**
 * configure_input_formatter() - Configure input formatter based on calibration.
 * @p_ictx: Pointer to isp calibration data.
 * @isp_base: ISP hw context memory base address.
 *
 * Return: None
 */
static void configure_input_formatter(
    decompander_fsm_ptr_t p_fsm,
    const decompander_ctrl *ctrl )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    const input_formatter_ctrl *p_in_fmt = (const input_formatter_ctrl *)
        calib_mgr_u16_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_INPUT_FORMATTER );

    const uint8_t data_source = ctrl->input_formatter_enable ? ACAMERA_ISP_PIPELINE_LINEAR_DATA_SOURCE_DECOMPANDED_SENSOR_DATA : ACAMERA_ISP_PIPELINE_LINEAR_DATA_SOURCE_FRAME_STITCH;

    if ( ctrl->input_formatter_enable ) {
        acamera_isp_input_formatter_mode_in_write( isp_base, p_in_fmt->in_fmt_mode );

        input_formatter_bitwidth_alignment( isp_base, p_in_fmt );

        acamera_isp_input_formatter_black_level_write( isp_base, p_in_fmt->black_level );

        acamera_isp_input_formatter_knee_point0_write( isp_base, p_in_fmt->knee_point0 );
        acamera_isp_input_formatter_knee_point1_write( isp_base, p_in_fmt->knee_point1 );
        acamera_isp_input_formatter_knee_point2_write( isp_base, p_in_fmt->knee_point2 );

        acamera_isp_input_formatter_slope0_select_write( isp_base, p_in_fmt->slope0 );
        acamera_isp_input_formatter_slope1_select_write( isp_base, p_in_fmt->slope1 );
        acamera_isp_input_formatter_slope2_select_write( isp_base, p_in_fmt->slope2 );
        acamera_isp_input_formatter_slope3_select_write( isp_base, p_in_fmt->slope3 );
    }

    acamera_isp_pipeline_linear_data_source_write( isp_base,
                                                   data_source );
    acamera_isp_pipeline_bypass_input_formatter_write( isp_base, ~ctrl->input_formatter_enable );
}

/**
 * configure_gamma_fe() - Configure gamma fe based on calibration.
 * @p_ictx: Pointer to ISP calibration data.
 * @isp_base: ISP hw context memory base address.
 *
 * Return: None
 */
static void configure_gamma_fe(
    decompander_fsm_ptr_t p_fsm,
    const decompander_ctrl *ctrl )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

    if ( ctrl->gamma_fe_lut_enable ) {
        const uint32_t gamma_fe_size = calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_GAMMA_FE );
        const uint32_t *gamma_fe_lut = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_GAMMA_FE );
        size_t i;
        for ( i = 0; i < gamma_fe_size - 1; i++ )
            acamera_gamma_fe_mem_array_data_write( isp_base, i, gamma_fe_lut[i] );
        acamera_isp_gamma_fe_data_last_write( isp_base, gamma_fe_lut[gamma_fe_size - 1] );
    }

    if ( ctrl->gamma_fe_sqrt_enable ) {
        const uint32_t *gamma_black_levels = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_GAMMA_BLACK_LEVELS );
#if DECOMPANDER_HAS_SQ
        acamera_isp_gamma_fe_black_level_in_sq_write( isp_base, *gamma_black_levels++ );
        acamera_isp_gamma_fe_black_level_out_sq_write( isp_base, *gamma_black_levels++ );
#elif DECOMPANDER_HAS_DL
        acamera_isp_gamma_fe_black_level_in_dl_write( isp_base, *gamma_black_levels++ );
        acamera_isp_gamma_fe_black_level_out_dl_write( isp_base, *gamma_black_levels++ );
        acamera_isp_gamma_fe_alpha_write( isp_base, *gamma_black_levels++ );
#endif
    }


#if DECOMPANDER_HAS_SQ
    acamera_isp_pipeline_bypass_gamma_fe_sq_write( isp_base, ~ctrl->gamma_fe_sqrt_enable );
#elif DECOMPANDER_HAS_DL
    acamera_isp_pipeline_bypass_gamma_fe_dl_write( isp_base, ~ctrl->gamma_fe_sqrt_enable );
    acamera_isp_gamma_fe_enable_dl_write( isp_base, ctrl->gamma_fe_sqrt_enable );
#endif

    acamera_isp_pipeline_bypass_gamma_fe_write( isp_base, ~ctrl->gamma_fe_lut_enable );
    acamera_isp_gamma_fe_enable_write( isp_base, ctrl->gamma_fe_lut_enable );
}

/**
 * configure_gamma_be() - Configure gamma be based on calibration.
 * @p_ictx: Pointer to ISP calibration data.
 * @isp_base: ISP hw context memory base address.
 * @mode: Current WDR mode
 *
 * Return: None
 */
static void configure_gamma_be( decompander_fsm_ptr_t p_fsm,
                                const decompander_ctrl *ctrl )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;
    void *p_cm = ACAMERA_FSM2CM_PTR( p_fsm );

    if ( ctrl->gamma_be_lut_enable ) {
        const uint32_t *gamma_be_0_lut = calib_mgr_u32_lut_get( p_cm, CALIBRATION_GAMMA_BE0 );
        const uint32_t *gamma_be_1_lut = calib_mgr_u32_lut_get( p_cm, CALIBRATION_GAMMA_BE1 );
        const uint32_t gamma_be_0_len = calib_mgr_lut_len( p_cm, CALIBRATION_GAMMA_BE0 );
        const uint32_t gamma_be_1_len = calib_mgr_lut_len( p_cm, CALIBRATION_GAMMA_BE1 );
        const uint32_t gamma_be_0_hw_len = ( ACAMERA_GAMMA_BE0_MEM_SIZE / ( ACAMERA_GAMMA_BE0_MEM_ARRAY_DATA_DATASIZE >> 3 ) ) + 1;
        const uint32_t gamma_be_1_hw_len = ( ACAMERA_GAMMA_BE1_MEM_SIZE / ( ACAMERA_GAMMA_BE1_MEM_ARRAY_DATA_DATASIZE >> 3 ) ) + 1;

        if ( gamma_be_0_len != gamma_be_0_hw_len ) {
            LOG( LOG_ERR, "Wrong elements number in gamma_be_0_lut: expected %d got %d.", gamma_be_0_hw_len, gamma_be_0_len );
            return;
        }
        if ( gamma_be_1_len != gamma_be_1_hw_len ) {
            LOG( LOG_ERR, "Wrong elements number in gamma_be_1_lut: expected %d got %d.", gamma_be_1_hw_len, gamma_be_1_len );
            return;
        }

        size_t i;
        for ( i = 0; i < gamma_be_0_len - 1; i++ ) {
            acamera_gamma_be0_mem_array_data_write( isp_base, i, gamma_be_0_lut[i] );
        }
        acamera_isp_gamma_be_data_last_0_write( isp_base, gamma_be_0_lut[gamma_be_0_len - 1] );

        for ( i = 0; i < gamma_be_1_len - 1; i++ ) {
            acamera_gamma_be1_mem_array_data_write( isp_base, i, gamma_be_1_lut[i] );
        }
        acamera_isp_gamma_be_data_last_1_write( isp_base, gamma_be_1_lut[gamma_be_1_len - 1] );


        LOG( LOG_DEBUG, "gamma_be_0_lut length: %d.", gamma_be_0_len );
        LOG( LOG_DEBUG, "gamma_be_1_lut length: %d.", gamma_be_1_len );
    }


    if ( ctrl->gamma_be_sq_enable ) {
        const uint32_t *gamma_black_levels = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_GAMMA_BLACK_LEVELS );
#if DECOMPANDER_HAS_SQ
        acamera_isp_gamma_be_black_level_out_sq_write( isp_base, *gamma_black_levels++ );
        acamera_isp_gamma_be_black_level_in_sq_write( isp_base, *gamma_black_levels++ );
#elif DECOMPANDER_HAS_DL
        acamera_isp_gamma_be_black_level_out_dl_write( isp_base, *gamma_black_levels++ );
        acamera_isp_gamma_be_black_level_in_dl_write( isp_base, *gamma_black_levels++ );
        acamera_isp_gamma_be_alpha_write( isp_base, *gamma_black_levels++ );
#endif
    }


#if DECOMPANDER_HAS_SQ
    acamera_isp_pipeline_bypass_gamma_be_sq_write( isp_base, ~ctrl->gamma_be_sq_enable );
#elif DECOMPANDER_HAS_DL
    acamera_isp_pipeline_bypass_gamma_be_dl_write( isp_base, ~ctrl->gamma_be_sq_enable );
    acamera_isp_gamma_be_enable_dl_write( isp_base, ctrl->gamma_be_sq_enable );
#endif

    acamera_isp_pipeline_bypass_gamma_be_write( isp_base, ~ctrl->gamma_be_lut_enable );
    acamera_isp_gamma_be_enable_0_write( isp_base, ctrl->gamma_be_lut_enable );
    acamera_isp_gamma_be_enable_1_write( isp_base, ctrl->gamma_be_lut_enable );
}

/**
 * decompander_initialize() - FSM handler function.
 * @p_fsm: Pointer to decompander FSM.

 * Return: None
 */
void decompander_init( decompander_fsm_ptr_t p_fsm )
{
}

/**
 * @brief      Tear down the FSM
 *
 * @param[in]  p_fsm  Pointer to the FSM data
 *
 */
void decompander_deinit( decompander_fsm_ptr_t p_fsm )
{
    const uint32_t isp_base = ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base;

#if DECOMPANDER_HAS_SQ
    acamera_isp_pipeline_bypass_gamma_fe_sq_write( isp_base, 1 );
    acamera_isp_pipeline_bypass_gamma_be_sq_write( isp_base, 1 );
#elif DECOMPANDER_HAS_DL
    acamera_isp_pipeline_bypass_gamma_fe_dl_write( isp_base, 1 );
    acamera_isp_pipeline_bypass_gamma_be_dl_write( isp_base, 1 );
    acamera_isp_gamma_fe_enable_dl_write( isp_base, 0 );
    acamera_isp_gamma_be_enable_dl_write( isp_base, 0 );
#endif

    acamera_isp_pipeline_bypass_gamma_fe_write( isp_base, 1 );
    acamera_isp_pipeline_bypass_gamma_be_write( isp_base, 1 );

    acamera_isp_gamma_be_enable_0_write( isp_base, 0 );
    acamera_isp_gamma_be_enable_1_write( isp_base, 0 );
    acamera_isp_gamma_fe_enable_write( isp_base, 0 );
}

/**
 * decompander_reload_calibration() - FSM handler function.
 * @p_fsm: Pointer to decompander FSM.

 * Return: None
 */
void decompander_reload_calibration( decompander_fsm_ptr_t p_fsm )
{
    /* If tuning is missing, do nothing with input formatter. */
    if ( calib_mgr_lut_exists( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DECOMPANDER_CONTROL ) ) {
        assert( calib_mgr_lut_len( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DECOMPANDER_CONTROL ) ==
                sizeof( decompander_ctrl ) );
        const decompander_ctrl *p_decompander_ctrl = (const decompander_ctrl *)calib_mgr_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_DECOMPANDER_CONTROL );
        configure_input_formatter( p_fsm, p_decompander_ctrl );
        configure_gamma_fe( p_fsm, p_decompander_ctrl );
        configure_gamma_be( p_fsm, p_decompander_ctrl );
    }
}