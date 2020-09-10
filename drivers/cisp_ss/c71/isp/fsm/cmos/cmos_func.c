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
#include "system_stdlib.h"
#include "system_timer.h"
#include "acamera_command_api.h"
#include "acamera_isp_ctx.h"
#include "acamera_logger.h"
#include "acamera_math.h"
#include "cmos_fsm.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_CMOS

#if defined( ISP_HAS_MCFE_FSM )
#define ISP_SETTINGS_APPLY_DELAY 0
#else
#define ISP_SETTINGS_APPLY_DELAY 1
#endif

#define is_short_exposure_frame( base ) ( ACAMERA_FSM2ICTX_PTR( p_fsm )->fe_frame_counter & 1 )

#define EXPOSURE_PARAMETER_INTEGRATION_TIME_INDEX 0
#define EXPOSURE_PARAMETER_GAIN_INDEX 1

#define INTEGRATION_TIME( ms )                        \
    {                                                 \
        EXPOSURE_PARAMETER_INTEGRATION_TIME_INDEX, ms \
    }
#define INTEGRATION_TIME_MAX                         \
    {                                                \
        EXPOSURE_PARAMETER_INTEGRATION_TIME_INDEX, 0 \
    }

#define GAIN( gain )                        \
    {                                       \
        EXPOSURE_PARAMETER_GAIN_INDEX, gain \
    }
#define GAIN_MAX                         \
    {                                    \
        EXPOSURE_PARAMETER_GAIN_INDEX, 0 \
    }
#define API_OTE_THRESHOLD ( 5 )
#define API_OTE_ITERATION_COUNT ( 15 )

// 0 value for Integration time means max possible value.
// 0 value for Gain means max possible value.
// i = 0 in exposure_partition_t structure is used to identify exposure time value
// i = 1 in exposure_partition_t structure is used to identify gain value
const exposure_partition_t default_exposure_partitions_balanced[] = {
    INTEGRATION_TIME( 10 ), // Integration time in ms.
    GAIN( 2 ),              // Gain in multipliers.
    INTEGRATION_TIME( 30 ),
    GAIN( 4 ),
    INTEGRATION_TIME( 60 ),
    GAIN( 6 ),
    INTEGRATION_TIME( 100 ),
    GAIN( 8 ),
    INTEGRATION_TIME_MAX,
    GAIN_MAX};

#define EXPOSURE_PARTIONS_COUNT array_size( default_exposure_partitions_balanced )


const exposure_partition_t exposure_partition_int_priority[EXPOSURE_PARTIONS_COUNT] = {
    INTEGRATION_TIME_MAX,
    GAIN( 0 ),
    INTEGRATION_TIME_MAX,
    GAIN( 0 ),
    INTEGRATION_TIME_MAX,
    GAIN( 0 ),
    INTEGRATION_TIME_MAX,
    GAIN( 0 ),
    INTEGRATION_TIME_MAX,
    GAIN_MAX};


/* Exposure set history helpers */
static exposure_set_t *history_get_exposure_set( cmos_fsm_const_ptr_t p_fsm, const int offset );
static bool history_is_valid( cmos_fsm_const_ptr_t p_fsm );
static void history_reset( cmos_fsm_ptr_t p_fsm );

/* Exposure set struct helpers */
static void exposure_set_store_current( cmos_fsm_ptr_t p_fsm, exposure_set_t *p_set );

/* Public frame exposure accessor for general router. Should only be accessed by general router. */
exposure_set_t *cmos_get_frame_exposure_set( cmos_fsm_ptr_t p_fsm, int i_frame )
{
    return history_get_exposure_set( p_fsm, i_frame );
}

static int cmos_convert_integration_time_ms2lines( cmos_fsm_ptr_t p_fsm, int time_ms )
{
    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return 0;
    }
    return sensor_info.lines_per_second * time_ms / 1000; // Division by zero is checked.
}

void cmos_update_exposure_partitioning_lut( cmos_fsm_ptr_t p_fsm )
{
    int i;
    int32_t param[2] = {0, 0}; // In log2

    if ( calib_mgr_lut_exists( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_CMOS_EXP_PARTITION ) &&
         ( calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_CMOS_EXP_PARTITION ) <= EXP_LUT_TABLE_SIZE ) ) {
        p_fsm->exp_partition_tbl = (const exposure_partition_t *)calib_mgr_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_CMOS_EXP_PARTITION );
        p_fsm->exp_lut_valid_entries = calib_mgr_lut_rows( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_CMOS_EXP_PARTITION );
    } else {
        LOG( LOG_WARNING, "Default table is set! NULL pointer is passed or table is too big!" );

        p_fsm->exp_partition_tbl = default_exposure_partitions_balanced;
        p_fsm->exp_lut_valid_entries = EXPOSURE_PARTIONS_COUNT;
        if ( EXP_LUT_TABLE_SIZE < EXPOSURE_PARTIONS_COUNT ) {
            LOG( LOG_WARNING, "Default cmos exposure partition table is too big! Part of it will be used!" );
            p_fsm->exp_lut_valid_entries = EXP_LUT_TABLE_SIZE;
        }
    }

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    int32_t max_gain = sensor_info.again_log2_max + sensor_info.dgain_log2_max + p_fsm->maximum_isp_digital_gain;
    for ( i = 0; i < p_fsm->exp_lut_valid_entries; ++i ) {
        int i_param = p_fsm->exp_partition_tbl[i].i;
        if ( ( i_param < 0 ) || ( i_param >= 2 ) ) {
            continue;
        }
        int32_t addon = 0;
        uint8_t v = p_fsm->exp_partition_tbl[i].v;
        switch ( i_param ) {
        case EXPOSURE_PARAMETER_INTEGRATION_TIME_INDEX:
            if ( !v ) {
                addon = log2_fixed_to_fixed( ( sensor_info.integration_time_limit >> sensor_info.integration_time_precision ), 0, LOG2_GAIN_SHIFT );
            } else {
                uint32_t lines = cmos_convert_integration_time_ms2lines( p_fsm, v );
                if ( lines < ( sensor_info.integration_time_min >> sensor_info.integration_time_precision ) ) {
                    lines = sensor_info.integration_time_min >> sensor_info.integration_time_precision;
                }
                addon = log2_fixed_to_fixed( lines, 0, LOG2_GAIN_SHIFT );
            }
            break;
        case EXPOSURE_PARAMETER_GAIN_INDEX:
            if ( !v ) {
                addon = max_gain;
            } else {
                addon = log2_fixed_to_fixed( v, 0, LOG2_GAIN_SHIFT );
            }
            break;
        }
        addon -= param[i_param];
        if ( addon < 0 ) {
            addon = 0;
        }
        p_fsm->exp_lut[i] = addon;
        param[i_param] += addon;
    }
}

static void _process_fps_cnt( fps_counter_t *fps_cnt )
{
    uint32_t cur_tick = system_timer_timestamp();
    uint32_t frame_ticks = cur_tick - fps_cnt->last_tick;
    // Skip the first tick that doesn't have last tick, and skip abnormal frame time which probably caused by capture.
    if ( fps_cnt->last_tick != 0 && frame_ticks <= system_timer_frequency() / 2 ) {
        fps_cnt->avg_frame_ticks += frame_ticks - ( fps_cnt->avg_frame_ticks >> 4 );
        //LOG( LOG_DEBUG, "c=%u, p=%u, d=%u, a=%u", cur_tick, fps_cnt->last_tick, frame_ticks, fps_cnt->avg_frame_ticks >> 4 );
    }
    fps_cnt->last_tick = cur_tick;
}

static void _init_fps_cnt( fps_counter_t *fps_cnt )
{
    fps_cnt->last_tick = 0;
    fps_cnt->avg_frame_ticks = ( system_timer_frequency() / 15 ) << 4; // Initially it's something like 15 FPS. // Division by zero is checked.
    system_timer_init();
}

uint16_t cmos_get_fps( cmos_fsm_ptr_t p_fsm )
{
    uint64_t tps = system_timer_frequency();
    uint16_t fps;
    if ( p_fsm->fps_cnt.avg_frame_ticks ) {
        uint64_t _tps = ( tps << ( 8 + 4 ) );
        fps = (uint16_t)div64_u64( _tps, p_fsm->fps_cnt.avg_frame_ticks ); // Division by zero is checked.
    } else {
        LOG( LOG_WARNING, "AVOIDED DIVISION BY ZERO" );
        fps = 15 << 8;
    }
    //LOG( LOG_DEBUG, "fps = %d.%d", fps >> 8,( fps & 0xFF ) * (uint32_t)1000 / 256 );
    return fps;
}

void cmos_init( cmos_fsm_ptr_t p_fsm )
{
    LOG( LOG_INFO, "cmos INIT E" );

    p_fsm->cmos_frame_start_irq = ACAMERA_IRQ_FE_FRAME_START;
    p_fsm->repeat_irq_mask = BIT( p_fsm->cmos_frame_start_irq ) | BIT( ACAMERA_IRQ_BE_FRAME_END );
    cmos_request_interrupt( p_fsm, p_fsm->repeat_irq_mask );

    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    acamera_isp_pipeline_bypass_white_balance_write( p_ictx->settings.isp_base, 0 );
    acamera_isp_pipeline_bypass_digital_gain_write( p_ictx->settings.isp_base, 0 );

#ifdef ACAMERA_ISP_PIPELINE_POSITION_DIGITAL_GAIN_DEFAULT
    acamera_isp_pipeline_position_digital_gain_write( p_ictx->settings.isp_base, 1 );
#endif

    _init_fps_cnt( &p_fsm->fps_cnt );
    LOG( LOG_INFO, "cmos INIT X" );
}

void cmos_config( cmos_fsm_ptr_t p_fsm )
{
    LOG( LOG_INFO, "cmos CFG E" );
    cmos_update_exposure_partitioning_lut( p_fsm );
    LOG( LOG_INFO, "cmos CFG X" );
}

void cmos_reload_calibration( cmos_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    // Configure context parameters with default values (CALIBRATION_CMOS_CONTROL)
    {
        cmos_control_param_t *param = (cmos_control_param_t *)calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_CMOS_CONTROL );
        set_context_param( p_ictx, SYSTEM_ANTIFLICKER_ENABLE_PARAM, param->antiflicker_enable );
        set_context_param( p_ictx, SYSTEM_ANTI_FLICKER_FREQUENCY_PARAM, param->anti_flicker_frequency );
        set_context_param( p_ictx, SYSTEM_MANUAL_INTEGRATION_TIME_PARAM, param->manual_integration_time );
        set_context_param( p_ictx, SYSTEM_MANUAL_SENSOR_ANALOG_GAIN_PARAM, param->manual_sensor_analog_gain );
        set_context_param( p_ictx, SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN_PARAM, param->manual_sensor_digital_gain );
        set_context_param( p_ictx, SYSTEM_MANUAL_ISP_DIGITAL_GAIN_PARAM, param->manual_isp_digital_gain );
        set_context_param( p_ictx, SYSTEM_MANUAL_MAX_INTEGRATION_TIME_PARAM, param->manual_max_integration_time );
        set_context_param( p_ictx, SYSTEM_MANUAL_EXPOSURE_RATIO_PARAM, param->manual_exposure_ratio );
        set_context_param( p_ictx, SYSTEM_MAX_INTEGRATION_TIME_PARAM, param->max_integration_time );
        set_context_param( p_ictx, SYSTEM_MAX_SENSOR_ANALOG_GAIN_PARAM, param->max_sensor_analog_gain );
        set_context_param( p_ictx, SYSTEM_MAX_SENSOR_DIGITAL_GAIN_PARAM, param->max_sensor_digital_gain );
        set_context_param( p_ictx, SYSTEM_MAX_ISP_DIGITAL_GAIN_PARAM, param->max_isp_digital_gain );
        set_context_param( p_ictx, SYSTEM_MAX_EXPOSURE_RATIO_PARAM, param->max_exposure_ratio );
        set_context_param( p_ictx, SYSTEM_INTEGRATION_TIME_PARAM, param->integration_time );
        set_context_param( p_ictx, SYSTEM_SENSOR_ANALOG_GAIN_PARAM, param->sensor_analog_gain );
        set_context_param( p_ictx, SYSTEM_SENSOR_DIGITAL_GAIN_PARAM, param->sensor_digital_gain );
        set_context_param( p_ictx, SYSTEM_ISP_DIGITAL_GAIN_PARAM, param->isp_digital_gain );
    }

    /* Load up wdr stitching configuraiton from calibration */
    if ( calib_mgr_lut_exists( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_WDR_STITCH_CONFIG ) ) {
        const uint32_t *config = calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_WDR_STITCH_CONFIG );
        acamera_isp_frame_stitch_lm_thresh_high_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_lm_thresh_low_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_ms_thresh_high_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_ms_thresh_low_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_svs_thresh_high_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_svs_thresh_low_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_consistency_thresh_lvl_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_consistency_thresh_mov_write( p_ictx->settings.isp_base, *config++ );
#if IS_MALI_C71
        acamera_isp_frame_stitch_mcoff_l_max_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_mcoff_m_max_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_mcoff_s_max_write( p_ictx->settings.isp_base, *config++ );
        acamera_isp_frame_stitch_mcoff_vs_max_write( p_ictx->settings.isp_base, *config++ );
#endif
    } else {
        LOG( LOG_ERR, "CALIBRATION_WDR_STITCH_CONFIG is missing, module will not be configured correctly!" );
    }
}

static void cmos_alloc_integration_time( cmos_fsm_ptr_t p_fsm, uint32_t int_time )
{
    // We should set as maximum as possible analogue gain less than or equals target_gain.
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    const uint32_t is_manual_max_inttime = get_context_param( p_ictx, SYSTEM_MANUAL_MAX_INTEGRATION_TIME_PARAM );
    const uint32_t is_manual_inttime = get_context_param( p_ictx, SYSTEM_MANUAL_INTEGRATION_TIME_PARAM );

    const uint32_t min_integration_time_short = sensor_info.integration_time_min;
    const uint32_t max_integration_time_short = is_manual_max_inttime ? ( get_context_param( p_ictx, SYSTEM_MAX_INTEGRATION_TIME_PARAM ) << sensor_info.integration_time_precision )
                                                                      : sensor_info.integration_time_limit;

    uint32_t new_integration_time_short = is_manual_inttime ? get_context_param( p_ictx, SYSTEM_INTEGRATION_TIME_PARAM )
                                                            : math_exp2( int_time, LOG2_GAIN_SHIFT, sensor_info.integration_time_precision );

    new_integration_time_short = MAX( new_integration_time_short, min_integration_time_short );
    new_integration_time_short = MIN( new_integration_time_short, max_integration_time_short );

    p_fsm->prev_integration_time_short = p_fsm->integration_time_short;
    p_fsm->integration_time_short = new_integration_time_short;
}

static int32_t cmos_alloc_sensor_analog_gain( cmos_fsm_ptr_t p_fsm, int32_t gain )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( gain < 0 ) {
        return 0;
    }

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return 0;
    }

    const int32_t max_gain = get_context_param( p_ictx, SYSTEM_MAX_SENSOR_ANALOG_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 );
    if ( gain > max_gain ) {
        gain = max_gain;
    }

    int32_t ret_value = 0;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_ALLOC_ANALOG_GAIN, CMD_DIRECTION_GET, (const uint32_t *)&gain, (uint32_t *)&ret_value ) ) {
        return 0;
    }

    return ret_value;
}

static int32_t cmos_alloc_sensor_digital_gain( cmos_fsm_ptr_t p_fsm, int32_t gain )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( gain < 0 ) {
        return 0;
    }

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return 0;
    }

    const int32_t max_gain = MIN( sensor_info.dgain_log2_max, ( (int32_t)get_context_param( p_ictx, SYSTEM_MAX_SENSOR_DIGITAL_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 ) ) );
    if ( gain > max_gain ) {
        gain = max_gain;
    }

    int32_t ret_value = 0;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_ALLOC_DIGITAL_GAIN, CMD_DIRECTION_GET, (const uint32_t *)&gain, (uint32_t *)&ret_value ) ) {
        return 0;
    }

    gain = ret_value;
    if ( gain < 0 ) {
        gain = 0; // Special mode like native HDR.
    }
    return gain;
}

static void cmos_alloc_sensor_white_balance_gains( cmos_fsm_ptr_t p_fsm, int32_t gain[4] )
{
    WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_WB_GAINS, CMD_DIRECTION_SET, (const uint32_t *)gain, NULL );
}

static int32_t cmos_alloc_isp_digital_gain( cmos_fsm_ptr_t p_fsm, int32_t gain )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( gain < 0 ) {
        return 0;
    }
    if ( gain > p_fsm->maximum_isp_digital_gain ) {
        gain = p_fsm->maximum_isp_digital_gain;
    }
    const int32_t max_gain = ( int32_t )( get_context_param( p_ictx, SYSTEM_MAX_ISP_DIGITAL_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 ) );
    if ( gain > max_gain ) {
        gain = max_gain;
    }
    return gain;
}

static int32_t cmos_get_manual_again_log2( cmos_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( get_context_param( p_ictx, SYSTEM_MANUAL_SENSOR_ANALOG_GAIN_PARAM ) ) {
        const int32_t gain = get_context_param( p_ictx, SYSTEM_SENSOR_ANALOG_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 );
        return cmos_alloc_sensor_analog_gain( p_fsm, gain );
    }
    return -1; // Negative means it is not manual.
}

static int32_t cmos_get_manual_dgain_log2( cmos_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( get_context_param( p_ictx, SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN_PARAM ) ) {
        const int32_t gain = get_context_param( p_ictx, SYSTEM_SENSOR_DIGITAL_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 );
        return cmos_alloc_sensor_digital_gain( p_fsm, gain );
    }
    return -1; // Negative means it is not manual.
}

static int32_t cmos_get_manual_isp_dgain_log2( cmos_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( get_context_param( p_ictx, SYSTEM_MANUAL_ISP_DIGITAL_GAIN_PARAM ) ) {
        const int32_t gain = ( get_context_param( p_ictx, SYSTEM_ISP_DIGITAL_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 ) );
        return cmos_alloc_isp_digital_gain( p_fsm, gain );
    }
    return -1; // Negative means it is not manual.
}

static exposure_set_t *history_get_exposure_set( cmos_fsm_const_ptr_t p_fsm, const int offset )
{
    int pos = p_fsm->exposure_hist_pos + offset;

    if ( pos < 0 )
        pos += array_size( p_fsm->exposure_hist );        // Division by zero is checked.
    else if ( pos >= array_size( p_fsm->exposure_hist ) ) // Division by zero is checked.
        pos -= array_size( p_fsm->exposure_hist );        // Division by zero is checked.

    return (exposure_set_t *)&p_fsm->exposure_hist[pos];
}

static bool history_is_valid( cmos_fsm_const_ptr_t p_fsm )
{
    return p_fsm->exposure_hist_pos >= 0 &&
           p_fsm->exposure_hist_pos < array_size( p_fsm->exposure_hist );
}

static void history_reset( cmos_fsm_ptr_t p_fsm )
{
    /*This preloads the entire history with current algorithm values. */

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    p_fsm->exposure_hist_pos = 0;
    int pos;
    for ( pos = 0; pos <= sensor_info.integration_time_apply_delay; ++pos ) {
        exposure_set_store_current( p_fsm, history_get_exposure_set( p_fsm, pos ) );
    }
}


/**
 * @brief      Stores current FSM result in a exposure set structure.
 *
 * @param[in]  p_fsm  The fsm pointer
 * @param      p_set  The exposure set
 *
 */
static void exposure_set_store_current( cmos_fsm_ptr_t p_fsm, exposure_set_t *p_set )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    // Clear any previous data.
    system_memset( p_set, 0, sizeof( exposure_set_t ) );

    uint8_t exp_num = sensor_info.sensor_exp_number;
    uint32_t inttime_delay = sensor_info.integration_time_apply_delay;

    p_set->data.integration_time = p_fsm->integration_time_short;
    p_set->data.isp_dgain_log2 = p_fsm->isp_dgain_log2;
    int32_t prev_again;

    if ( exp_num == 4 ) {
        p_set->data.integration_time_long = p_fsm->integration_time_long;
        p_set->data.integration_time_medium = p_fsm->integration_time_medium;
        p_set->data.integration_time_medium2 = p_fsm->integration_time_medium2;

        p_set->data.exposure_ratio_short = 64 * (uint32_t)p_fsm->integration_time_medium / p_fsm->integration_time_short;
        p_set->data.exposure_ratio_medium = 64 * (uint32_t)p_fsm->integration_time_medium2 / p_fsm->integration_time_medium;

        switch ( sensor_info.isp_exposure_channel_delay ) {
        case 1:
            prev_again = history_get_exposure_set( (cmos_fsm_ptr_t)p_fsm, inttime_delay )->info.again_log2;
            p_set->data.exposure_ratio_medium2 = 64 * (uint32_t)p_fsm->integration_time_long / p_fsm->integration_time_medium2 * math_exp2( prev_again - p_fsm->again_val_log2, LOG2_GAIN_SHIFT, 8 ) >> 8;
            break;
        default:
            p_set->data.exposure_ratio_medium2 = 64 * (uint32_t)p_fsm->integration_time_long / p_fsm->integration_time_medium2;
            break;
        }
    } else if ( exp_num == 3 ) {
        p_set->data.integration_time_medium = p_fsm->integration_time_medium;
        p_set->data.exposure_ratio_short = 64 * (uint32_t)p_fsm->integration_time_medium / p_fsm->integration_time_short;
        p_set->data.integration_time_long = p_fsm->integration_time_long;

        switch ( sensor_info.isp_exposure_channel_delay ) {
        case 1:
            prev_again = history_get_exposure_set( (cmos_fsm_ptr_t)p_fsm, inttime_delay )->info.again_log2;
            p_set->data.exposure_ratio_medium = 64 * (uint32_t)p_fsm->integration_time_long / p_fsm->integration_time_medium * math_exp2( prev_again - p_fsm->again_val_log2, LOG2_GAIN_SHIFT, 8 ) >> 8;
            break;
        default:
            p_set->data.exposure_ratio_medium = 64 * (uint32_t)p_fsm->integration_time_long / p_fsm->integration_time_medium;
            break;
        }

    } else if ( exp_num == 2 ) {
        p_set->data.integration_time_long = p_fsm->integration_time_long;

        switch ( sensor_info.isp_exposure_channel_delay ) {
        case 1:
            prev_again = history_get_exposure_set( (cmos_fsm_ptr_t)p_fsm, inttime_delay )->info.again_log2;
            p_set->data.exposure_ratio = 64 * (uint32_t)p_fsm->integration_time_long / p_fsm->integration_time_short * math_exp2( prev_again - p_fsm->again_val_log2, LOG2_GAIN_SHIFT, 8 ) >> 8;
            break;
        default:
            p_set->data.exposure_ratio = 64 * (uint32_t)p_fsm->integration_time_long / p_fsm->integration_time_short;
            break;
        }
    } else {
        p_set->data.integration_time_long = p_fsm->integration_time_long;
        p_set->data.exposure_ratio = 64 * (uint32_t)p_fsm->integration_time_long / p_fsm->integration_time_short;
    }

    // Store the isp dgain value to be written to the register.
    p_set->data.dgain_reg = math_exp2( p_fsm->isp_dgain_log2, LOG2_GAIN_SHIFT, 8 );

    p_set->info.again_log2 = p_fsm->again_val_log2;
    p_set->info.dgain_log2 = p_fsm->dgain_val_log2;
    p_set->info.isp_dgain_log2 = p_fsm->isp_dgain_log2;
    // Update exposure for this frame.
    p_set->info.exposure_log2 = p_set->info.again_log2 + p_set->info.dgain_log2 + p_set->info.isp_dgain_log2;
    p_set->info.exposure_log2 += log2_fixed_to_fixed( p_set->data.integration_time, sensor_info.integration_time_precision, LOG2_GAIN_SHIFT );

    set_context_param( p_ictx, SYSTEM_EXPOSURE_PARAM, math_exp2( p_set->info.exposure_log2, LOG2_GAIN_SHIFT, 6 ) );
}


static void cmos_update_exposure_history( cmos_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    /* We need to ensure the history has been initialized. */
    if ( !history_is_valid( p_fsm ) ) {
        history_reset( p_fsm );
    }

    exposure_set_store_current( p_fsm, &( p_fsm->exp_next_set ) );

    // Display gains in control tool.
    if ( !get_context_param( p_ictx, SYSTEM_MANUAL_INTEGRATION_TIME_PARAM ) ) {
        set_context_param( p_ictx, SYSTEM_INTEGRATION_TIME_PARAM, p_fsm->integration_time_short );
    }
    if ( !get_context_param( p_ictx, SYSTEM_MANUAL_SENSOR_ANALOG_GAIN_PARAM ) ) {
        set_context_param( p_ictx, SYSTEM_SENSOR_ANALOG_GAIN_PARAM, p_fsm->again_val_log2 >> ( LOG2_GAIN_SHIFT - 5 ) );
    }
    if ( !get_context_param( p_ictx, SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN_PARAM ) ) {
        set_context_param( p_ictx, SYSTEM_SENSOR_DIGITAL_GAIN_PARAM, p_fsm->dgain_val_log2 >> ( LOG2_GAIN_SHIFT - 5 ) );
    }
    if ( !get_context_param( p_ictx, SYSTEM_MANUAL_ISP_DIGITAL_GAIN_PARAM ) ) {
        set_context_param( p_ictx, SYSTEM_ISP_DIGITAL_GAIN_PARAM, p_fsm->isp_dgain_log2 >> ( LOG2_GAIN_SHIFT - 5 ) );
    }

    const uint32_t status_info_gain_log2 = ( p_fsm->again_val_log2 + p_fsm->dgain_val_log2 + p_fsm->isp_dgain_log2 + ( ( 1 << ( LOG2_GAIN_SHIFT - 1 ) ) - 1 ) ) >> LOG2_GAIN_SHIFT;
    override_context_param( p_ictx, STATUS_INFO_GAIN_LOG2_ID_PARAM, status_info_gain_log2 );

    const uint32_t status_info_gain_ones = math_exp2( p_fsm->again_val_log2 + p_fsm->dgain_val_log2 + p_fsm->isp_dgain_log2, LOG2_GAIN_SHIFT, 0 );
    override_context_param( p_ictx, STATUS_INFO_GAIN_ONES_ID_PARAM, status_info_gain_ones );
}


static void cmos_move_exposure_history( cmos_fsm_ptr_t p_fsm )
{
    {
        /* Increment current history index by one (with wraparound). The history is a
            circular buffer where exposure_hist_pos is the entry point.*/
        int pos = p_fsm->exposure_hist_pos + 1;
        if ( pos >= array_size( p_fsm->exposure_hist ) ) { // Division by zero is checked.
            pos = 0;
        }
        p_fsm->exposure_hist_pos = pos;
    }

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    /* Stores the calculated exposure set in history. This will be integration_time_apply_delay frames in the future. */
    *history_get_exposure_set( p_fsm, sensor_info.integration_time_apply_delay ) = p_fsm->exp_next_set;
}

static bool is_multi_exposure( acamera_isp_ctx_ptr_t p_ictx, acamera_cmd_sensor_info *sensor_info )
{
    assert( p_ictx );
    assert( sensor_info );

    const uint32_t wdr_mode = get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM );

    switch ( wdr_mode ) {
    case WDR_MODE_FS_HDR:
    case WDR_MODE_FS_LIN:
        return true;

    case WDR_MODE_NATIVE:
        /* If we are in native mode then check sensor number of exposures.*/
        return ( sensor_info->sensor_exp_number > 1 );
    default:
        /* linear or otherwise not multi exposure mode */
        return false;
    }
}

/**
 * @brief      Assigns exposure parameters based on exposure history.
 *
 * @param[in]  p_fsm  The fsm
 *
 * @details    This function fetches exposure sets from history. The parameters
 *             from exp_set_sensor are the most up to date (current algorithm
 *             result). The exp_set_isp parameters are behind by
 *             (integration_time_apply_delay-ISP_SETTINGS_APPLY_DELAY) frames.
 */
static void cmos_calculate_multi_exposure( cmos_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    const uint8_t exp_num = sensor_info.sensor_exp_number;
    const exposure_set_t *exp_set_sensor = history_get_exposure_set( p_fsm, sensor_info.integration_time_apply_delay );
    const exposure_set_t *exp_set_isp = history_get_exposure_set( p_fsm, ISP_SETTINGS_APPLY_DELAY );

    /*Result exposure data set which will be a combination of exp_set_sensor and exp_set_isp*/
    exposure_data_set_t exp_set = {0};

    if ( is_multi_exposure( p_ictx, &sensor_info ) ) {

        switch ( exp_num ) {
        case 1:
            exp_set.integration_time = exp_set_sensor->data.actual_integration_time;
            exp_set.exposure_ratio = exp_set_isp->data.exposure_ratio;
            exp_set.actual_integration_time = exp_set.integration_time;
            break;
        case 2:
            exp_set.integration_time = exp_set_sensor->data.integration_time;
            exp_set.integration_time_long = exp_set_sensor->data.integration_time_long;
            exp_set.exposure_ratio = exp_set_isp->data.exposure_ratio;
            break;
        case 3:
            exp_set.integration_time = exp_set_sensor->data.integration_time;
            exp_set.integration_time_medium = exp_set_sensor->data.integration_time_medium;
            exp_set.integration_time_long = exp_set_sensor->data.integration_time_long;
            exp_set.exposure_ratio_short = exp_set_isp->data.exposure_ratio_short;
            exp_set.exposure_ratio_medium = exp_set_isp->data.exposure_ratio_medium;
            break;

        case 4:
        default:
            exp_set.integration_time = exp_set_sensor->data.integration_time;
            exp_set.integration_time_medium = exp_set_sensor->data.integration_time_medium;
            exp_set.integration_time_medium2 = exp_set_sensor->data.integration_time_medium2;
            exp_set.integration_time_long = exp_set_sensor->data.integration_time_long;
            exp_set.exposure_ratio_short = exp_set_isp->data.exposure_ratio_short;
            exp_set.exposure_ratio_medium = exp_set_isp->data.exposure_ratio_medium;
            exp_set.exposure_ratio_medium2 = exp_set_isp->data.exposure_ratio_medium2;
            break;
        }

        //Update context parameters
        if ( ( exp_num == 1 ) && ( is_short_exposure_frame( p_ictx->settings.isp_base ) == 0 ) ) {
            override_context_param( p_ictx, SYSTEM_LONG_INTEGRATION_TIME_PARAM, exp_set.integration_time );
            override_context_param( p_ictx, SYSTEM_MIDDLE_INTEGRATION_TIME_PARAM, 0 );
            override_context_param( p_ictx, SYSTEM_SHORT_INTEGRATION_TIME_PARAM, 0 );
        } else {
            override_context_param( p_ictx, SYSTEM_LONG_INTEGRATION_TIME_PARAM, exp_set.integration_time_long );
            override_context_param( p_ictx, SYSTEM_MIDDLE_INTEGRATION_TIME_PARAM, exp_set.integration_time_medium );
            override_context_param( p_ictx, SYSTEM_SHORT_INTEGRATION_TIME_PARAM, exp_set.integration_time );
        }

    } else {
        exp_set.integration_time = exp_set_sensor->data.integration_time;
        override_context_param( p_ictx, SYSTEM_SHORT_INTEGRATION_TIME_PARAM, exp_set.integration_time );

        //Not multi exposure, set to 0.
        override_context_param( p_ictx, SYSTEM_MIDDLE_INTEGRATION_TIME_PARAM, 0 );
        override_context_param( p_ictx, SYSTEM_LONG_INTEGRATION_TIME_PARAM, 0 );


        switch ( exp_num ) {
        case 1:
            exp_set.actual_integration_time = exp_set.integration_time;
            exp_set.exposure_ratio = 64;
            break;

        case 2:
            exp_set.integration_time = exp_set_sensor->data.integration_time;
            exp_set.integration_time_long = exp_set_sensor->data.integration_time_long;
            exp_set.exposure_ratio = exp_set_isp->data.exposure_ratio;
            break;

        case 3:
            exp_set.integration_time = exp_set_sensor->data.integration_time;
            exp_set.integration_time_medium = exp_set.integration_time;
            exp_set.integration_time_long = exp_set.integration_time;
            exp_set.exposure_ratio_short = exp_set_isp->data.exposure_ratio_short;
            exp_set.exposure_ratio_medium = exp_set_isp->data.exposure_ratio_medium;
            break;

        case 4:
        default:
            exp_set.integration_time = exp_set_sensor->data.integration_time;
            exp_set.integration_time_medium = exp_set.integration_time;
            exp_set.integration_time_medium2 = exp_set.integration_time;
            exp_set.integration_time_long = exp_set.integration_time;
            exp_set.exposure_ratio_short = exp_set_isp->data.exposure_ratio_short;
            exp_set.exposure_ratio_medium = exp_set_isp->data.exposure_ratio_medium;
            exp_set.exposure_ratio_medium2 = exp_set_isp->data.exposure_ratio_medium2;
            break;
        }
    }

    /* get the dgain including the register value. */
    exp_set.dgain_reg = exp_set_isp->data.dgain_reg;
    exp_set.isp_dgain_log2 = exp_set_isp->data.isp_dgain_log2;

    /* Write to exp_write_set which is used by the hardware update function triggered by update_hw event. */
    p_fsm->exp_write_set = exp_set;
}

static void cmos_update_wb_gains( cmos_fsm_const_ptr_t p_fsm )
{
#if defined( ISP_HAS_AWB_MESH_NBP_FSM ) || defined( ISP_HAS_AWB_MANUAL_FSM )
    acamera_cmd_wb_info wb_info;
    acamera_cmd_sensor_info sensor_info;
    int32_t sensor_wb_log2[4];
    uint32_t i;

    // Update white balance gains.
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_WB_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&wb_info ) ) {
        return;
    }

    // Get sensor info for max_sensor_wb_gains_logs
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    // First try to apply white balance gains in sensor.
    if ( sensor_info.wb_gain_log2_max ) {
        for ( i = 0; i < 4; i++ ) {
            sensor_wb_log2[i] = wb_info.wb_log2[i];
        }

        if ( sensor_info.wb_gain_log2_max ) {
            cmos_alloc_sensor_white_balance_gains( (cmos_fsm_ptr_t)p_fsm, sensor_wb_log2 );
        }

        // Set remaining white balance gains to be applied in ISP.
        for ( i = 0; i < 4; i++ ) {
            ( (cmos_fsm_ptr_t)p_fsm )->isp_wb_log2[i] = wb_info.wb_log2[i] - sensor_wb_log2[i];
        }
    } else {
        for ( i = 0; i < 4; i++ ) {
            ( (cmos_fsm_ptr_t)p_fsm )->isp_wb_log2[i] = wb_info.wb_log2[i];
        }
    }
#endif
}

static void cmos_calculate_gains( cmos_fsm_const_ptr_t p_fsm )
{
#if defined( ISP_HAS_AWB_MESH_NBP_FSM ) || defined( ISP_HAS_AWB_MANUAL_FSM )
    uint32_t i;
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    acamera_cmd_wb_info wb_info;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_WB_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&wb_info ) ) {
        return;
    }

    for ( i = 0; i < 4; ++i ) {
        const uint32_t gain = math_exp2( ( (cmos_fsm_ptr_t)p_fsm )->isp_wb_log2[i], LOG2_GAIN_SHIFT, 8 );
        ( (cmos_fsm_ptr_t)p_fsm )->wb[i] = gain > 0xFFF ? 0xFFF : (uint16_t)gain;
    }

    // Expansion of values to the full range.
    const uint32_t wdr_mode = get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM );
    if ( wdr_mode == WDR_MODE_FS_HDR || wdr_mode == WDR_MODE_FS_LIN || wdr_mode == WDR_MODE_NATIVE ) {
        uint16_t bl[4] = {acamera_isp_offset_black_00_read( p_ictx->settings.isp_base ),
                          acamera_isp_offset_black_01_read( p_ictx->settings.isp_base ),
                          acamera_isp_offset_black_10_read( p_ictx->settings.isp_base ),
                          acamera_isp_offset_black_11_read( p_ictx->settings.isp_base )};
        for ( i = 0; i < 4; ++i ) {
            uint32_t mult = ( 256 * ( ( (uint32_t)1 << ACAMERA_ISP_OFFSET_BLACK_00_DATASIZE ) - 1 ) ) / ( ( ( (uint32_t)1 << ACAMERA_ISP_OFFSET_BLACK_00_DATASIZE ) - 1 ) - bl[i] );
            ( (cmos_fsm_ptr_t)p_fsm )->wb[i] = ( ( ( uint32_t )( (cmos_fsm_ptr_t)p_fsm )->wb[i] ) * mult ) / 256;
        }
    }
#endif
}

static void cmos_write_isp_settings( cmos_fsm_const_ptr_t p_fsm )
{
    const acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    const uint32_t wdr_mode = get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM );

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    override_context_param( p_ictx, SYSTEM_INTEGRATION_TIME_PRECISION_PARAM, sensor_info.integration_time_precision );

    uint8_t exp_num = sensor_info.sensor_exp_number;

    if ( get_context_param( p_ictx, SYSTEM_FREEZE_FIRMWARE_PARAM ) != 0 )
        return; // Remaining func code only sets the ips registers (no fsm/global variable updates).
    if ( ( get_context_param( p_ictx, ISP_MODULES_MANUAL_FRAME_STITCH_PARAM ) == 0 ) &&
         ( ( wdr_mode == WDR_MODE_FS_HDR ) || ( wdr_mode == WDR_MODE_FS_LIN ) ) ) {
        if ( exp_num == 4 ) {
            acamera_isp_frame_stitch_mode_in_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 0 );
#ifdef ACAMERA_ISP_FRAME_STITCH_SVS_EXPOSURE_RATIO_DEFAULT
            acamera_isp_frame_stitch_svs_exposure_ratio_write( p_ictx->settings.isp_base, p_fsm->exp_write_set.exposure_ratio_short );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_MS_EXPOSURE_RATIO_DEFAULT
            acamera_isp_frame_stitch_ms_exposure_ratio_write( p_ictx->settings.isp_base, p_fsm->exp_write_set.exposure_ratio_medium );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_LM_EXPOSURE_RATIO_DEFAULT
            acamera_isp_frame_stitch_lm_exposure_ratio_write( p_ictx->settings.isp_base, p_fsm->exp_write_set.exposure_ratio_medium2 );
#endif

            int32_t R12 = p_fsm->exp_write_set.exposure_ratio_medium2;                        // Long/medium ratio
            int32_t R13 = ( R12 * (int32_t)p_fsm->exp_write_set.exposure_ratio_medium ) >> 6; // Long/short ratio
            int32_t R14 = ( R13 * (int32_t)p_fsm->exp_write_set.exposure_ratio_short ) >> 6;  // Long/very_short ratio

            if ( R12 < 0 ) {
                R12 = 1;
            }
            if ( R13 < 0 ) {
                R13 = 1;
            }
            if ( R14 < 0 ) {
                R14 = 1;
            }


#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_DEFAULT
            const int32_t SF2 = ( 262144 / R12 + 262144 / R13 + 262144 / R14 ) * 2048 / ( 4096 + 262144 / R12 + 262144 / R13 + 262144 / R14 );
            acamera_isp_frame_stitch_mcoff_l_scaler_write( p_ictx->settings.isp_base, (uint16_t)SF2 );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_LM_SCALER_DEFAULT
            const int32_t SF3 = ( 262144 / R13 + 262144 / R14 ) * 2048 / ( 262144 / R12 + 262144 / R13 + 262144 / R14 );
            acamera_isp_frame_stitch_mcoff_lm_scaler_write( p_ictx->settings.isp_base, (uint16_t)SF3 );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_LMS_SCALER_DEFAULT
            const int32_t SF4 = ( 262144 / R14 ) * 2048 / ( 262144 / R13 + 262144 / R14 );
            acamera_isp_frame_stitch_mcoff_lms_scaler_write( p_ictx->settings.isp_base, (uint16_t)SF4 );
#endif

        } else if ( exp_num == 3 ) {
            acamera_isp_frame_stitch_mode_in_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 2 );

#ifdef ACAMERA_ISP_FRAME_STITCH_MS_EXPOSURE_RATIO_DEFAULT
            acamera_isp_frame_stitch_ms_exposure_ratio_write( p_ictx->settings.isp_base, p_fsm->exp_write_set.exposure_ratio_short );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_LM_EXPOSURE_RATIO_DEFAULT
            acamera_isp_frame_stitch_lm_exposure_ratio_write( p_ictx->settings.isp_base, p_fsm->exp_write_set.exposure_ratio_medium );
#endif
// mc off
// if(Exp == 2)
//     param.SF2 = 1/(1 + R12);
//     param.SF3 = 0;
//     param.SF4 = 0;
// elseif(Exp == 3)
//     param.SF2 = (1/R12 + 1/R13) / (1 + 1/R12 + 1/R13);
//     param.SF3 = (1/R13)/(1/R12 + 1/R13);
//     param.SF4 = 0;
// elseif(Exp == 4)
//     param.SF2 = (1/R12 + 1/R13 + 1/R14)/(1 + 1/R12 + 1/R13 + 1/R14);
//     param.SF3 = (1/R13 + 1/R14)/(1/R12 + 1/R13 + 1/R14);
//     param.SF4 = (1/R14)/(1/R13 + 1/R14);
#if defined( ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_DEFAULT ) || defined( ACAMERA_ISP_FRAME_STITCH_MCOFF_LM_SCALER_DEFAULT )
            const int32_t R12 = p_fsm->exp_write_set.exposure_ratio_medium;                                                                                    // Long/medium ratio
            const int32_t R13 = ( ( int32_t )( p_fsm->exp_write_set.exposure_ratio_medium ) * ( int32_t )( p_fsm->exp_write_set.exposure_ratio_short ) ) >> 6; // Long/short ratio
#endif

#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_DEFAULT
            const int32_t SF2 = ( ( 262144 / R12 + 262144 / R13 ) * 2048 ) / ( 4096 + 262144 / R12 + 262144 / R13 ); //U0.11
            acamera_isp_frame_stitch_mcoff_l_scaler_write( p_ictx->settings.isp_base, (uint16_t)SF2 );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_LM_SCALER_DEFAULT
            const int32_t SF3 = ( ( 262144 / R13 ) * 2048 ) / ( 262144 / R12 + 262144 / R13 ); //U0.11
            acamera_isp_frame_stitch_mcoff_lm_scaler_write( p_ictx->settings.isp_base, (uint16_t)SF3 );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_LMS_SCALER_DEFAULT
            const int32_t SF4 = 0;
            acamera_isp_frame_stitch_mcoff_lms_scaler_write( p_ictx->settings.isp_base, (uint16_t)SF4 );
#endif

        } else if ( exp_num == 2 ) {
#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_DEFAULT
            // U0.11 registers
            const int32_t R12 = p_fsm->exp_write_set.exposure_ratio;
            const int32_t SF2 = 262144 / ( 2048 + R12 );
#endif

            acamera_isp_frame_stitch_mode_in_write( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, 1 );
#ifdef ACAMERA_ISP_FRAME_STITCH_LM_EXPOSURE_RATIO_DEFAULT
            acamera_isp_frame_stitch_lm_exposure_ratio_write( p_ictx->settings.isp_base, p_fsm->exp_write_set.exposure_ratio_medium );
#endif

#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_L_SCALER_DEFAULT
            acamera_isp_frame_stitch_mcoff_l_scaler_write( p_ictx->settings.isp_base, (uint16_t)SF2 );
#endif

#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_LM_SCALER_DEFAULT
            acamera_isp_frame_stitch_mcoff_lm_scaler_write( p_ictx->settings.isp_base, (uint16_t)0 );
#endif
#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_LMS_SCALER_DEFAULT
            acamera_isp_frame_stitch_mcoff_lms_scaler_write( p_ictx->settings.isp_base, (uint16_t)0 );
#endif
        } else {
#ifdef ACAMERA_ISP_FRAME_STITCH_LM_EXPOSURE_RATIO_DEFAULT
            acamera_isp_frame_stitch_lm_exposure_ratio_write( p_ictx->settings.isp_base, p_fsm->exp_write_set.exposure_ratio );
#endif
        }
    }


#if defined( ISP_HAS_AWB_MESH_NBP_FSM ) || defined( ISP_HAS_AWB_MANUAL_FSM )
    acamera_isp_digital_gain_gain_write( p_ictx->settings.isp_base, p_fsm->exp_write_set.dgain_reg );
#ifdef ACAMERA_ISP_WHITE_BALANCE_GAIN_00_DEFAULT
    acamera_isp_white_balance_gain_00_write( p_ictx->settings.isp_base, ( (cmos_fsm_ptr_t)p_fsm )->wb[0] );
    acamera_isp_white_balance_gain_01_write( p_ictx->settings.isp_base, ( (cmos_fsm_ptr_t)p_fsm )->wb[1] );
    acamera_isp_white_balance_gain_10_write( p_ictx->settings.isp_base, ( (cmos_fsm_ptr_t)p_fsm )->wb[2] );
    acamera_isp_white_balance_gain_11_write( p_ictx->settings.isp_base, ( (cmos_fsm_ptr_t)p_fsm )->wb[3] );
#endif

    if ( get_context_param( p_ictx, ISP_MODULES_MANUAL_FRAME_STITCH_PARAM ) == 0 ) {
#ifdef ACAMERA_ISP_FRAME_STITCH_GAIN_R_DEFAULT
        acamera_isp_frame_stitch_gain_r_write( p_ictx->settings.isp_base, ( (cmos_fsm_ptr_t)p_fsm )->wb[0] );
        acamera_isp_frame_stitch_gain_b_write( p_ictx->settings.isp_base, ( (cmos_fsm_ptr_t)p_fsm )->wb[3] );
#endif

#ifdef ACAMERA_ISP_FRAME_STITCH_MCOFF_MODE_ENABLE_DEFAULT
        if ( acamera_isp_frame_stitch_mcoff_mode_enable_read( p_ictx->settings.isp_base ) == 1 ) {
            acamera_isp_frame_stitch_gain_r_write( p_ictx->settings.isp_base, 65536 / ( ( (cmos_fsm_ptr_t)p_fsm )->wb[0] ) );
            acamera_isp_frame_stitch_gain_b_write( p_ictx->settings.isp_base, 65536 / ( ( (cmos_fsm_ptr_t)p_fsm )->wb[3] ) );
        }
#endif
    }

#endif

#if defined( FW_TOGGLE_LONG_FIRST )
    if ( exp_num == 1 ) {
        if ( ( wdr_mode == WDR_MODE_FS_HDR ) || ( wdr_mode == WDR_MODE_FS_LIN ) ) {
            if ( p_fsm->exp_write_set.exposure_ratio == 64 ) { // Linear mode, just keep exposure ratio at 64
                acamera_isp_frame_stitch_long_first_write( p_ictx->settings.isp_base, 0 );
            } else {
                acamera_isp_frame_stitch_long_first_write( p_ictx->settings.isp_base, is_short_exposure_frame( p_ictx->settings.isp_base ) ^ 1 ^ ( sensor_info.integration_time_apply_delay & 1 ) );
            }
        }
    }
#endif
}

void cmos_fsm_process_interrupt( cmos_fsm_const_ptr_t p_fsm, uint8_t irq_event )
{
    if ( irq_event == p_fsm->cmos_frame_start_irq ) {
        acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

        if ( ( get_context_param( p_ictx, SYSTEM_FREEZE_FIRMWARE_PARAM ) != 1 ) ||
             ( get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM ) == WDR_MODE_FS_HDR ) ) {

            if ( p_fsm->state == cmos_state_ready ) {
                WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_UPDATE, CMD_DIRECTION_SET, NULL, NULL );
            }
        }
    } else if ( irq_event == ACAMERA_IRQ_BE_FRAME_END ) {
        _process_fps_cnt( (fps_counter_t *)&p_fsm->fps_cnt );
    }
}

static void cmos_inttime_update( cmos_fsm_ptr_t p_fsm )
{
    int32_t int_time = 0;
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( p_fsm->exp_partition_tbl == NULL ) {
        LOG( LOG_INFO, "Initialize exposure partition and exposure lut tables!" );
        cmos_update_exposure_partitioning_lut( p_fsm );
    }

    if ( get_context_param( p_ictx, SYSTEM_MANUAL_INTEGRATION_TIME_PARAM ) == 0 ) {
        int i;
        int32_t exposure = 0, exp_target = p_fsm->exposure_log2;
        if ( p_fsm->manual_gain_mode == 1 ) {
            int_time = exp_target - log2_fixed_to_fixed( p_fsm->manual_gain, 8, LOG2_GAIN_SHIFT );
        } else {
            int32_t gain;
            gain = cmos_get_manual_again_log2( p_fsm );
            if ( gain >= 0 ) {
                exp_target -= gain;
            }
            gain = cmos_get_manual_dgain_log2( p_fsm );
            if ( gain >= 0 ) {
                exp_target -= gain;
            }
            gain = cmos_get_manual_isp_dgain_log2( p_fsm );
            if ( gain >= 0 ) {
                exp_target -= gain;
            }
            if ( exp_target < 0 ) {
                exp_target = 0;
            }

            for ( i = 0; i < p_fsm->exp_lut_valid_entries; ++i ) {
                int i_param = p_fsm->exp_partition_tbl[i].i;
                int32_t addon = p_fsm->exp_lut[i];
                if ( ( i_param < 0 ) || ( i_param >= 2 ) ) {
                    continue;
                }
                if ( i_param == EXPOSURE_PARAMETER_INTEGRATION_TIME_INDEX ) {
                    if ( exposure + addon > exp_target ) {
                        addon = exp_target - exposure;
                    }
                    int_time += addon;
                }
                exposure += addon;
                if ( exposure >= exp_target ) {
                    break;
                }
            }

            const uint32_t system_antiflicker_enable = get_context_param( p_ictx, SYSTEM_ANTIFLICKER_ENABLE_PARAM );

            // Check antiflicker frequency value.
            if ( system_antiflicker_enable == 0 ) {
                p_fsm->flicker_freq = 0;
            } else {
                p_fsm->flicker_freq = get_context_param( p_ictx, SYSTEM_ANTI_FLICKER_FREQUENCY_PARAM ) * 256;
            }

            if ( p_fsm->flicker_freq && !p_fsm->manual_gain_mode && system_antiflicker_enable ) {
                acamera_cmd_sensor_info sensor_info;
                if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
                    return;
                }

                uint32_t line_per_half_period = ( sensor_info.lines_per_second << 8 ) / ( p_fsm->flicker_freq * 2 ); // Division by zero is checked.
                if ( line_per_half_period != 0 ) {
                    int32_t half_period_log2 = log2_fixed_to_fixed( line_per_half_period, 0, LOG2_GAIN_SHIFT );
                    LOG( LOG_LEVEL_DEBUG, "ANTI-FLICKER: calculated integration time:%d , anti-flicker integration time:%d , exposure target:%d", int_time, half_period_log2, exp_target );
                    if ( int_time <= half_period_log2 ) {
                        // If calculated integration time (IT) < antiflicker required IT,
                        // increase IT but not more than exposure target
                        int_time = MIN( exp_target, half_period_log2 );
                    } else {                                                               // othewise decrease it to a mulitple of antiflicker IT
                        uint32_t int_time_lin = math_exp2( int_time, LOG2_GAIN_SHIFT, 0 ); // change to linear scale
                        int_time_lin -= ( int_time_lin % line_per_half_period );
                        int_time = log2_fixed_to_fixed( int_time_lin, 0, LOG2_GAIN_SHIFT ); // change back to logarithmic scale
                    }
                }
            }
        }
    }
    cmos_alloc_integration_time( p_fsm, int_time );
}

static void cmos_analog_gain_update( cmos_fsm_ptr_t p_fsm )
{
    int32_t gain;
    int32_t target_gain = p_fsm->target_gain_log2;
    cmos_control_param_t *param = (cmos_control_param_t *)calib_mgr_u32_lut_get( ACAMERA_FSM2CM_PTR( p_fsm ), CALIBRATION_CMOS_CONTROL );
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    if ( param->analog_gain_last_priority == 1 ) {

        const uint32_t wdr_mode = get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM );

        if ( wdr_mode == WDR_MODE_NATIVE || wdr_mode == WDR_MODE_FS_LIN || wdr_mode == WDR_MODE_LINEAR ) {
            // Automatic sensor digital gain goes before analog gain.
            if ( cmos_get_manual_dgain_log2( p_fsm ) < 0 ) // Negative means it is not manual.
            {
                p_fsm->dgain_val_log2 = cmos_alloc_sensor_digital_gain( p_fsm, target_gain );
                target_gain -= p_fsm->dgain_val_log2;
            }
            const int32_t max_again = (int32_t)get_context_param( p_ictx, SYSTEM_MAX_SENSOR_ANALOG_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 );
            const int32_t reserved_again = max_again - ( ( (int32_t)param->analog_gain_reserve ) << LOG2_GAIN_SHIFT );
            const int32_t max_isp_gain = ( (int32_t)get_context_param( p_ictx, SYSTEM_MAX_ISP_DIGITAL_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 ) ) - ( 1 << LOG2_GAIN_SHIFT );
            const int32_t reserved_isp_gain = max_isp_gain - ( ( (int32_t)param->isp_gain_reserve ) << LOG2_GAIN_SHIFT );
            // Analog gain has reserve before achieving maximum.

            gain = cmos_get_manual_isp_dgain_log2( p_fsm );
            if ( gain < 0 ) // Negative means it is not manual.
            {
                gain = reserved_isp_gain;
            } else {
                // In case of manual ISP gain and manual sensor dgain or no avalable sensor dgain
                // we have to apply all gain as analog gain.
                if ( !get_context_param( p_ictx, SYSTEM_MAX_SENSOR_DIGITAL_GAIN_PARAM ) || cmos_get_manual_dgain_log2( p_fsm ) > 0 ) {
                    sensor_info.again_accuracy = 0;
                }
            }
            if ( target_gain < reserved_again ) {
                /* in the first stage we want to allocate just ISP dgain, so if the target is less
				than the reserve we allocate 0 again:*/
                target_gain = 0;
            } else if ( target_gain < gain ) {
                /* Otherwise if the target is below the isp gain reserve then we limit to again to (0, again_reserve) */
                target_gain = MIN( reserved_again, ( target_gain - reserved_again ) );
            } else {
                /* Start increasing the again but don't drop it below the already met reserve ) */
                target_gain = MAX( reserved_again, target_gain - gain );
            }
        }
    } else {
        gain = cmos_get_manual_dgain_log2( p_fsm );
        if ( gain > 0 ) {
            // Manual sensor dgain gain
            if ( target_gain > gain ) {
                target_gain -= gain;
            } else {
                target_gain = 0;
            }
        }
        gain = cmos_get_manual_isp_dgain_log2( p_fsm );
        if ( gain > 0 ) {
            // Manual ISP dgain gain
            if ( target_gain > gain ) {
                target_gain -= gain;
            } else {
                target_gain = 0;
            }
        }
    }
    gain = cmos_get_manual_again_log2( p_fsm );
    if ( gain < 0 ) { // Negative means it is not manual.
                      // We should set as maximum as possible analogue gain less than or equals target_gain.
        gain = cmos_alloc_sensor_analog_gain( p_fsm, target_gain );
    }

    p_fsm->again_val_log2 = gain;
}

static void cmos_digital_gain_update( cmos_fsm_ptr_t p_fsm )
{
    int32_t isp_gain;

    int32_t gain = cmos_get_manual_dgain_log2( p_fsm );
    if ( gain < 0 ) { // Negative means it is not manual.
        // We should set the rest of gain to make target_gain equals analogue_gain x digital_gain.
        // If manual ISP gain is set we should include it in calculation.
        isp_gain = cmos_get_manual_isp_dgain_log2( p_fsm );
        if ( isp_gain < 0 ) { // Negative means it is not manual.
            gain = cmos_alloc_sensor_digital_gain( p_fsm, p_fsm->target_gain_log2 - p_fsm->again_val_log2 );
        } else {
            gain = cmos_alloc_sensor_digital_gain( p_fsm, p_fsm->target_gain_log2 - p_fsm->again_val_log2 - isp_gain );
        }
    }
    p_fsm->dgain_val_log2 = gain;
    gain = cmos_get_manual_isp_dgain_log2( p_fsm );
    if ( gain < 0 ) { // Negative means it is not manual.
        gain = cmos_alloc_isp_digital_gain( p_fsm, p_fsm->target_gain_log2 - p_fsm->again_val_log2 - p_fsm->dgain_val_log2 );
    }
    p_fsm->isp_dgain_log2 = gain;

    // Update white balance gains.
    cmos_update_wb_gains( p_fsm );
}

static uint32_t get_quantised_integration_time( cmos_fsm_ptr_t p_fsm, uint32_t int_time )
{
    if ( !p_fsm->flicker_freq || p_fsm->manual_gain_mode ) {
        return int_time;
    }
    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return 0;
    }

    uint32_t line_per_half_period = ( sensor_info.lines_per_second << 8 ) / ( p_fsm->flicker_freq * 2 ); // Division by zero is checked.
    if ( line_per_half_period != 0 ) {
        uint32_t N = int_time / line_per_half_period; // Division by zero is checked.
        if ( N < 1 ) {
            N = 1;
        }
        return ( N * line_per_half_period << sensor_info.integration_time_precision );
    } else {
        return int_time;
    }
}

uint32_t get_quantised_long_integration_time( cmos_fsm_ptr_t p_fsm, uint32_t int_time, uint32_t max_int_time )
{
    acamera_cmd_sensor_info sensor_info;

    if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return 0;
    }

    if ( int_time < sensor_info.integration_time_min ) {
        int_time = sensor_info.integration_time_min;
    } else if ( int_time > max_int_time ) {
        int_time = max_int_time;
    }
    return get_quantised_integration_time( p_fsm, int_time );
}

static void cmos_antiflicker_update( cmos_fsm_ptr_t p_fsm )
{
    uint32_t integration_time_short = get_quantised_integration_time( p_fsm, p_fsm->integration_time_short );

    if ( integration_time_short < p_fsm->integration_time_short ) {
        p_fsm->integration_time_short = integration_time_short;
    }
}

static void cmos_long_exposure_update( cmos_fsm_ptr_t p_fsm )
{
    acamera_cmd_sensor_info sensor_info;
    acamera_cmd_sensor_integration_time time;
    acamera_cmd_sensor_integration_time time_output;
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    uint8_t exp_num = sensor_info.sensor_exp_number;
    uint32_t exposure_ratio, integration_time_long, integration_time_long_quant;

    const uint32_t wdr_mode = get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM );

    if ( ( wdr_mode == WDR_MODE_FS_HDR ) || ( wdr_mode == WDR_MODE_FS_LIN ) || ( ( wdr_mode == WDR_MODE_NATIVE ) && ( exp_num > 1 ) ) ) {
        uint32_t integration_time_medium_max = sensor_info.integration_time_medium_max;
        uint32_t integration_time_long_max = sensor_info.integration_time_long_max;
        const uint32_t system_manual_max_integration_time = get_context_param( p_ictx, SYSTEM_MANUAL_MAX_INTEGRATION_TIME_PARAM );
        const uint32_t system_max_integration_time = get_context_param( p_ictx, SYSTEM_MAX_INTEGRATION_TIME_PARAM ) << sensor_info.integration_time_precision;

        if ( !integration_time_long_max ) {
            uint32_t integration_time_long_max = sensor_info.integration_time_limit;

            if ( system_manual_max_integration_time && ( integration_time_long_max > system_max_integration_time ) ) {
                integration_time_long_max = system_max_integration_time;
            }
        }
        if ( !integration_time_medium_max ) {
            uint32_t integration_time_medium_max = sensor_info.integration_time_limit;

            if ( system_manual_max_integration_time && ( integration_time_medium_max > system_max_integration_time ) ) {
                integration_time_medium_max = system_max_integration_time;
            }
        }
        exposure_ratio = p_fsm->exposure_ratio_in;
        if ( exposure_ratio < 64 ) {
            exposure_ratio = 64;
        }
        integration_time_long = (uint32_t)p_fsm->integration_time_short * exposure_ratio >> 6;
        if ( integration_time_long > integration_time_long_max )
            integration_time_long = integration_time_long_max;

        integration_time_long_quant = get_quantised_long_integration_time( p_fsm, integration_time_long, integration_time_long_max );
        if ( integration_time_long_quant > integration_time_long_max ) {
            integration_time_long_quant = integration_time_long_max;
        }
        p_fsm->integration_time_long = integration_time_long_quant;
        if ( exp_num == 4 ) {

            const uint32_t exposure_ratio_thresholded = exposure_ratio > 256 ? exposure_ratio / 2 : exposure_ratio;
            const uint32_t ratio_cube_root = math_exp2( log2_fixed_to_fixed( exposure_ratio_thresholded, 6, 16 ) / 3, 16, 6 );
            //LOG( LOG_DEBUG, "ratio_cube_root: %d -> %d", exposure_ratio_thresholded, ratio_cube_root );

            uint32_t integration_time_medium1 = p_fsm->integration_time_short * ratio_cube_root >> 6;
            uint32_t integration_time_medium2 = integration_time_medium1 * ratio_cube_root >> 6;

            if ( integration_time_medium2 > integration_time_long_max ) {
                integration_time_medium2 = integration_time_long_max;
            }
            if ( integration_time_medium2 > p_fsm->integration_time_long ) {
                integration_time_medium2 = p_fsm->integration_time_long;
            }
            if ( integration_time_medium1 > integration_time_medium2 ) {
                integration_time_medium1 = integration_time_medium2;
            }

            time.int_time = p_fsm->integration_time_short;
            time.int_time_M = integration_time_medium1;
            time.int_time_M2 = integration_time_medium2;
            time.int_time_L = p_fsm->integration_time_long;

            if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME, CMD_DIRECTION_SET, (const uint32_t *)&time, (uint32_t *)&time_output ) ) {
                return;
            }

            // Time is updated in above function, save it.
            p_fsm->integration_time_short = time.int_time;
            p_fsm->integration_time_medium = time.int_time_M;
            p_fsm->integration_time_medium2 = time.int_time_M2;
            p_fsm->integration_time_long = time.int_time_L;

        } else if ( exp_num == 3 ) {
            uint32_t integration_time_medium;
            if ( exposure_ratio > 256 ) {
                // Half ML ratio by two
                integration_time_medium = (uint32_t)p_fsm->integration_time_short * ( sqrt32( exposure_ratio ) << 1 ) >> 3;
            } else {
                integration_time_medium = (uint32_t)p_fsm->integration_time_short * sqrt32( exposure_ratio ) >> 3;
            }
            //integration_time_medium = (uint32_t)p_fsm->integration_time_short * sqrt32( exposure_ratio ) >> 3;

            //LOG( LOG_DEBUG, "integration_time_medium %d exposure_ratio %d  sqrt32( exposure_ratio ) %d", integration_time_medium, exposure_ratio/64, sqrt32( exposure_ratio ) << 3 );
            if ( integration_time_medium > integration_time_medium_max ) {
                integration_time_medium = integration_time_medium_max;
            }
            if ( integration_time_medium > p_fsm->integration_time_long ) {
                integration_time_medium = p_fsm->integration_time_long;
            }
            p_fsm->integration_time_medium = integration_time_medium;
            time.int_time = p_fsm->integration_time_short;
            time.int_time_M = p_fsm->integration_time_medium;
            time.int_time_L = p_fsm->integration_time_long;
            //LOG( LOG_DEBUG, " short %d medium %d long %d", p_fsm->integration_time_short, p_fsm->integration_time_medium, p_fsm->integration_time_long );

            if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME, CMD_DIRECTION_SET, (const uint32_t *)&time, (uint32_t *)&time_output ) ) {
                return;
            }

            // Time is updated in above function, save it.
            p_fsm->integration_time_short = time_output.int_time;
            p_fsm->integration_time_medium = time_output.int_time_M;
            p_fsm->integration_time_long = time_output.int_time_L;

        } else if ( exp_num == 2 ) {
            time.int_time = p_fsm->integration_time_short;
            time.int_time_L = p_fsm->integration_time_long;

            if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME, CMD_DIRECTION_SET, (const uint32_t *)&time, (uint32_t *)&time_output ) ) {
                return;
            }

            // Time is updated in above function, save it.
            p_fsm->integration_time_short = time_output.int_time;
            p_fsm->integration_time_long = time_output.int_time_L;
        } else {
            time.int_time = is_short_exposure_frame( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base ) ? p_fsm->integration_time_short : p_fsm->integration_time_long;

            if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME, CMD_DIRECTION_SET, (const uint32_t *)&time, (uint32_t *)&time_output ) ) {
                return;
            }

            // Time is updated in above function, save it.
            if ( is_short_exposure_frame( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base ) )
                p_fsm->integration_time_short = time_output.int_time;
            else
                p_fsm->integration_time_long = time_output.int_time;
        }

        p_fsm->exposure_ratio = ( uint16_t )( 64 * (uint32_t)p_fsm->integration_time_long / p_fsm->integration_time_short );
    } else {
        p_fsm->exposure_ratio = 64;

        if ( exp_num == 4 ) {

            time.int_time = p_fsm->integration_time_short;
            time.int_time_M = p_fsm->integration_time_short;
            time.int_time_M2 = p_fsm->integration_time_short;
            time.int_time_L = p_fsm->integration_time_short;

            if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME, CMD_DIRECTION_SET, (const uint32_t *)&time, (uint32_t *)&time_output ) ) {
                return;
            }

            // NOTE: the value of 'p_fsm->integration_time_short' depends on the order
            // that sensor function modify the pointer values. I checked some functions,
            // and found that the 3rd parameter will be modified at last, so we use the 3rd
            // parameter to save back into the 'p_fsm->integration_time_short' variable.
            p_fsm->integration_time_short = time.int_time_L;

        } else if ( exp_num == 3 ) {
            time.int_time = p_fsm->integration_time_short;
            time.int_time_M = p_fsm->integration_time_short;
            time.int_time_L = p_fsm->integration_time_short;

            if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME, CMD_DIRECTION_SET, (const uint32_t *)&time, (uint32_t *)&time_output ) ) {
                return;
            }

            // Time is updated in above function, save it.
            p_fsm->integration_time_short = time_output.int_time_L;

        } else if ( exp_num == 2 ) {
            time.int_time = p_fsm->integration_time_short;
            time.int_time_L = p_fsm->integration_time_short;

            if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME, CMD_DIRECTION_SET, (const uint32_t *)&time, (uint32_t *)&time_output ) ) {
                return;
            }

            // Time is updated in above function, save it.
            p_fsm->integration_time_short = time_output.int_time_L;
        } else {
            time.int_time = p_fsm->integration_time_short;

            if ( WRAP_GENERAL_CMD( ACAMERA_FSM2ICTX_PTR( p_fsm ), CMD_ID_SENSOR_ALLOC_INTEGRATION_TIME, CMD_DIRECTION_SET, (const uint32_t *)&time, (uint32_t *)&time_output ) ) {
                return;
            }

            // Time is updated in above function, save it.
            p_fsm->integration_time_short = time_output.int_time;
        }
    }
}

static void cmos_calc_target_gain( cmos_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    acamera_cmd_sensor_info sensor_info;

    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    int32_t target_gain_log2 = 0;
    if ( p_fsm->manual_gain_mode == 1 ) {
        target_gain_log2 = log2_fixed_to_fixed( p_fsm->manual_gain, 8, LOG2_GAIN_SHIFT );
    } else {
        target_gain_log2 = p_fsm->exposure_log2 - log2_fixed_to_fixed( p_fsm->integration_time_short, sensor_info.integration_time_precision, LOG2_GAIN_SHIFT );
    }

    if ( target_gain_log2 < 0 ) {
        target_gain_log2 = 0;
    }
    p_fsm->target_gain_step_log2 = target_gain_log2 - p_fsm->target_gain_log2;
    if ( p_fsm->target_gain_step_log2 < 0 ) {
        p_fsm->target_gain_step_log2 = -p_fsm->target_gain_step_log2;
    }
    p_fsm->target_gain_log2 = target_gain_log2;
}

void cmos_set_exposure_target( cmos_fsm_ptr_t p_fsm, int32_t exposure_log2, uint32_t exposure_ratio )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );

#if defined( ISP_HAS_DEFECT_PIXEL_FSM )
    acamera_cmd_defect_pixel_info dp_info;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_DEFECT_PIXEL_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&dp_info ) ) {
        return;
    }

    if ( !dp_info.hp_started )
#endif
    {
        acamera_cmd_sensor_info sensor_info;
        if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
            return;
        }

        const uint32_t wdr_mode = get_context_param( p_ictx, SENSOR_WDR_MODE_PARAM );
        // For HDR mode with one exposure we can set new exposure only every second frame.
        if ( !( ( ( wdr_mode == WDR_MODE_FS_HDR ) || ( wdr_mode == WDR_MODE_FS_LIN ) ) && ( sensor_info.sensor_exp_number == 1 ) && !is_short_exposure_frame( p_ictx->settings.isp_base ) ) ) {
            p_fsm->exposure_log2 = exposure_log2;
            p_fsm->exposure_ratio_in = exposure_ratio;

            const uint32_t max_exposure_ratio = get_context_param( p_ictx, SYSTEM_MAX_EXPOSURE_RATIO_PARAM ) * 64;

            if ( p_fsm->exposure_ratio_in > max_exposure_ratio ) {
                p_fsm->exposure_ratio_in = max_exposure_ratio;
            }

            override_context_param( p_ictx, STATUS_INFO_EXPOSURE_LOG2_ID_PARAM, p_fsm->exposure_log2 );

            LOG( LOG_DEBUG, "Set exposure %d and exposure ratio %d", (unsigned int)exposure_log2, (unsigned int)exposure_ratio );
        }
    }
#if defined( ISP_HAS_SENSOR_FSM )
    acamera_cmd_sensor_info sensor_info;
    if ( WRAP_GENERAL_CMD( p_ictx, CMD_ID_SENSOR_INFO, CMD_DIRECTION_GET, NULL, (uint32_t *)&sensor_info ) ) {
        return;
    }

    const uint32_t system_max_sensor_analog_gain = MIN( get_context_param( p_ictx, SYSTEM_MAX_SENSOR_ANALOG_GAIN_PARAM ), sensor_info.again_log2_max >> ( LOG2_GAIN_SHIFT - 5 ) );
    set_context_param( p_ictx, SYSTEM_MAX_SENSOR_ANALOG_GAIN_PARAM, system_max_sensor_analog_gain );

    const uint32_t system_max_sensor_digital_gain = MIN( get_context_param( p_ictx, SYSTEM_MAX_SENSOR_DIGITAL_GAIN_PARAM ), sensor_info.dgain_log2_max >> ( LOG2_GAIN_SHIFT - 5 ) );
    set_context_param( p_ictx, SYSTEM_MAX_SENSOR_DIGITAL_GAIN_PARAM, system_max_sensor_digital_gain );


    /* Handle integration time limits, if we are not in manual mode then we
    should reflect the current maximum back to the user. */
    if ( get_context_param( p_ictx, SYSTEM_MANUAL_MAX_INTEGRATION_TIME_PARAM ) == 0 ) {
        set_context_param( p_ictx, SYSTEM_MAX_INTEGRATION_TIME_PARAM, sensor_info.integration_time_limit >> sensor_info.integration_time_precision );
    }


    const int32_t max_again_log2 = MIN( sensor_info.again_log2_max, (int32_t)system_max_sensor_analog_gain << ( LOG2_GAIN_SHIFT - 5 ) );
    const int32_t max_dgain_log2 = MIN( sensor_info.dgain_log2_max, (int32_t)system_max_sensor_digital_gain << ( LOG2_GAIN_SHIFT - 5 ) );
    const int32_t max_isp_gain_log2 = MIN( p_fsm->maximum_isp_digital_gain, (int32_t)get_context_param( p_ictx, SYSTEM_MAX_ISP_DIGITAL_GAIN_PARAM ) << ( LOG2_GAIN_SHIFT - 5 ) );
    const int32_t max_integration_time_log2 = log2_fixed_to_fixed( sensor_info.integration_time_limit, sensor_info.integration_time_precision, LOG2_GAIN_SHIFT );

    p_fsm->max_exposure_log2 = max_again_log2 + max_dgain_log2 + max_isp_gain_log2 + max_integration_time_log2;
#endif
}

void cmos_update_exposure( cmos_fsm_ptr_t p_fsm )
{
    cmos_inttime_update( p_fsm );
    cmos_antiflicker_update( p_fsm );
    cmos_long_exposure_update( p_fsm );
    // Gains
    cmos_calc_target_gain( p_fsm );
    cmos_analog_gain_update( p_fsm );
    cmos_digital_gain_update( p_fsm );
    cmos_update_exposure_history( p_fsm );
    cmos_move_exposure_history( p_fsm );
    cmos_calculate_multi_exposure( p_fsm );
    cmos_calculate_gains( p_fsm );
}

void cmos_update_hw( cmos_fsm_ptr_t p_fsm )
{
    /* Update ISP digital gain on frame start. */
    cmos_write_isp_settings( p_fsm );
}


void cmos_deinit( cmos_fsm_ptr_t p_fsm )
{
    acamera_isp_ctx_ptr_t p_ictx = ACAMERA_FSM2ICTX_PTR( p_fsm );
    acamera_isp_pipeline_bypass_white_balance_write( p_ictx->settings.isp_base, 1 );
    acamera_isp_pipeline_bypass_digital_gain_write( p_ictx->settings.isp_base, 1 );
}
