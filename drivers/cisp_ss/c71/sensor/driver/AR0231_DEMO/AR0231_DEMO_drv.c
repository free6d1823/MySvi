/*
*
* SPDX-License-Identifier: GPL-2.0
*
* Copyright (C) 2011-2019 ARM or its affiliates
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 2.
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

//-------------------------------------------------------------------------------------
// STRUCTURE:
//  VARIABLE SECTION:
//      CONTROLS - Dependence from preprocessor
//      DATA	 - Modulation
//      RESET	 - Reset function
//      MIPI     - MIPI settings
//      FLASH    - Flash support
//  CONSTANT SECTION
//      DRIVER
//
//      This sensor is set to 7.5 FPS in FULL resolution (8Mp), and 30 FPS in 1080p.
//
//-------------------------------------------------------------------------------------

#include "system_platform.h"
#include "system_stdlib.h"
#include "system_timer.h"
#include "system_types.h"
#include "acamera_command_api.h"
#include "acamera_configuration.h"
#include "acamera_logger.h"
#include "acamera_math.h"
#include "acamera_sbus_api.h"
#include "sensor_api.h"
#include "sensor_init.h"
#include "sensor_interface_config.h"
#include "AR0231_DEMO_config.h"
#include "AR0231_DEMO_seq.h"
#include "application_command_api.h"
#if ACAMERA_MIPI_TO_DVP_BOARD
#include "sensor_interface_mipi_to_dvp.h"
#endif
#if ACAMERA_MIPI_BOARD
#include "sensor_interface_mipi.h"
#endif
#include "remote_sensor_common.h"
#include "util/math/acamera_math.h"
#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_SENSOR

#if ( SENSOR_ANALOG_GAIN_APPLY_DELAY < 0 )
#error "SENSOR_ANALOG_GAIN_APPLY_DELAY cannot be negative please check configuration AR0231.set."
#endif

// Update flags
#define UPDATE_1_INTEGRATION_TIME ( 1 << 0 )
#define UPDATE_2_INTEGRATION_TIMES ( 1 << 1 )
#define UPDATE_3_INTEGRATION_TIMES ( 1 << 2 )
#define UPDATE_4_INTEGRATION_TIMES ( 1 << 3 )
#define UPDATE_LONG_INTEGRATION_TIME ( 1 << 4 )
#define UPDATE_AGAIN ( 1 << 5 )
#define UPDATE_DGAIN ( 1 << 6 )
#define UPDATE_CHANNEL_DGAIN ( 1 << 7 )
#define UPDATE_POST_CHANNEL_DGAIN ( 1 << 8 )

#define MAX_SENSOR_EXPOSURES 4

#define HCG_BIT 7
#define HCG_MASK ( 1 << HCG_BIT )

#define USE_CONV_GAIN 1
#if USE_CONV_GAIN
#define AGAIN_SHIFT 16
#define HCG_VALUE 2.95
#else
#define AGAIN_SHIFT 4
#define HCG_VALUE 1
#endif

#define USE_POST_DLO_WB_COMPENSATION 1
#define LCG_VALUE 1
#define DGAIN_SHIFT 7
#define POST_DLO_DGAIN_SHIFT 9
#define SENSOR_ANALOG_GAIN_N ( SENSOR_ANALOG_GAIN_APPLY_DELAY + 1 )

static void sensor_get_lines_per_second( void *sensor_priv );
static void start_streaming( void *sensor_priv );

#define AGIAN_LUT_7_0 ( 2520 * 5 / 5 )
#define AGIAN_LUT_8_0 ( 2520 * 5 / 4 )
#define AGIAN_LUT_9_0 ( 2520 * 6 / 4 )
#define AGIAN_LUT_10_0 ( 2520 * 6 / 3 )
#define AGIAN_LUT_11_0 ( 2520 * 7 / 3 )
#define AGIAN_LUT_12_0 ( 2520 * 7 / 2 )
#define AGIAN_LUT_13_0 ( 2520 * 8 / 2 )
#define AGIAN_LUT_14_0 ( 2520 * 8 / 1 )
#define AGIAN_LUT_7_1 ( 0b0111 )
#define AGIAN_LUT_8_1 ( 0b1000 )
#define AGIAN_LUT_9_1 ( 0b1001 )
#define AGIAN_LUT_10_1 ( 0b1010 )
#define AGIAN_LUT_11_1 ( 0b1011 )
#define AGIAN_LUT_12_1 ( 0b1100 )
#define AGIAN_LUT_13_1 ( 0b1101 )
#define AGIAN_LUT_14_1 ( 0b1110 )

static const uint32_t gain_tbl[][3] = {
    {AGIAN_LUT_7_0 * LCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_7_1, 0},   //  0 - 1.00
    {AGIAN_LUT_8_0 * LCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_8_1, 0},   //  1 - 1.25
    {AGIAN_LUT_9_0 * LCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_9_1, 0},   //  2 - 1.50
    {AGIAN_LUT_10_0 * LCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_10_1, 0}, //  3 - 2.00
    {AGIAN_LUT_11_0 * LCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_11_1, 0}, //  4 - 2.3333
    {AGIAN_LUT_7_0 * HCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_7_1, 1},   //  5 - 2.95
    {AGIAN_LUT_12_0 * LCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_12_1, 0}, //  6 - 3.50
    {AGIAN_LUT_8_0 * HCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_8_1, 1},   //  7 - 3.6875
    {AGIAN_LUT_13_0 * LCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_13_1, 0}, //  8 - 4.00
    {AGIAN_LUT_9_0 * HCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_9_1, 1},   //  9 - 4.425
    {AGIAN_LUT_10_0 * HCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_10_1, 1}, // 10 - 5.90
    {AGIAN_LUT_11_0 * HCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_11_1, 1}, // 11 - 6.8832
    {AGIAN_LUT_14_0 * LCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_14_1, 0}, // 12 - 8.00
    {AGIAN_LUT_12_0 * HCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_12_1, 1}, // 13 - 10.325
    {AGIAN_LUT_13_0 * HCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_13_1, 1}, // 14 - 11.8
    {AGIAN_LUT_14_0 * HCG_VALUE * ( 1 << AGAIN_SHIFT ) / 2520, AGIAN_LUT_14_1, 1}, // 15 - 23.6
};

/* Short line-count to exposure ratio.
 * Table will be used only if short line count is smaller or equal to the last entry.
 * In all other cases default ratio from the sensor will be used. */
static const uint32_t sexp_ratio[][2] = {
    {1 * ( 1 << SENSOR_INTEGRATION_TIME_PRECISION ), 64},
    {4 * ( 1 << SENSOR_INTEGRATION_TIME_PRECISION ), 256},
};
static sensor_mode_t supported_modes[] = {
    // Presets
    {.wdr_mode = WDR_MODE_LINEAR,
     .resolution.width = 1920,
     .resolution.height = 1080,
     .exposures = 1,
     .num_channels = 1},
    {.wdr_mode = WDR_MODE_LINEAR,
     .resolution.width = 1920,
     .resolution.height = 1080,
     .exposures = 1,
     .num_channels = 1},
    {// PWL
     .wdr_mode = WDR_MODE_NATIVE,
     .resolution.width = 1920,
     .resolution.height = 1080,
     .exposures = 3,
     .num_channels = 1},
    {// DOL
     .wdr_mode = WDR_MODE_FS_LIN,
     .resolution.width = 1920,
     .resolution.height = 1080,
     .exposures = 2,
     .num_channels = 2},
    {// DOL
     .wdr_mode = WDR_MODE_FS_LIN,
     .resolution.width = 1920,
     .resolution.height = 1080,
     .exposures = 3,
     .num_channels = 3},
    {// DOL
     .wdr_mode = WDR_MODE_FS_LIN,
     .resolution.width = 1920,
     .resolution.height = 1080,
     .exposures = 4,
     .num_channels = 4},
};

typedef struct {
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;

} int_time_buffers_t;

typedef struct {
    uint32_t t3_t4;
    uint32_t t2_t3;
    uint32_t t1_t2;
} exp_ratios_t;

typedef struct _sensor_private_t {
    sensor_param_t param;
    uint8_t address; // Sensor address for direct write (not used currently).
    uint8_t seq_width;
    uint8_t streaming_flg;
    uint16_t again[SENSOR_ANALOG_GAIN_N];
    uint32_t integration_time;
    uint32_t integration_timeM;
    uint32_t integration_timeM2;
    uint32_t integration_timeL;
    uint16_t ch_dgain[4];
    uint16_t ch_post_dlo_dgain[4];
    uint32_t dgain;
    uint16_t change_flg;
    uint32_t again_limit;
    uint32_t again_limit_min;
    uint16_t again_old;
#if defined( ISP_HAS_ANTI_FLICKER_FSM )
    int32_t anti_flicker_pos;
#endif
    acamera_sbus_t sbus;
    uint32_t is_fixed_exp_ratio;
    exp_ratios_t exp_ratios;
    remote_sensor_frame_data_t remote_frame_data;
} sensor_private_t;

static sensor_private_t priv_array[FIRMWARE_CONTEXT_NUMBER];


static uint32_t reset_state = 0;

static const int_time_buffers_t int_time_buffers[MAX_SENSOR_EXPOSURES] = {
    {0, 0, 0},
    {84, 0, 0},
    {76, 8, 0},
    {68, 12, 4}};

static const uint32_t exp_ratios_lut[MAX_SENSOR_EXPOSURES] = {
    0x555, 0x444, 0x333};

//-------------------------------------------------------------------------------------
#if defined( SENSOR_AR0231_SEQUENCE_DEFAULT ) // Kernel module
#if SENSOR_SEQ_BINARY_AND_EXTERNAL
static char p_sensor_data[] = SENSOR_AR0231_SEQUENCE_DEFAULT;
#else
static const sensor_reg_t *p_sensor_data = SENSOR_AR0231_SEQUENCE_DEFAULT;
#endif
static int p_sensor_data_initialized = 1;

void sensor_ar0231_demo_set_init_seq( const char *seq, int seq_sz ) {}
int sensor_ar0231_demo_get_init_seq( char *seq )
{
    if ( seq != NULL && p_sensor_data_initialized ) {
        system_memcpy( seq, p_sensor_data, sizeof( SENSOR_AR0231_SEQUENCE_DEFAULT ) );
    }
    return !p_sensor_data_initialized;
}

#elif defined( SENSOR_AR0231_SEQUENCE_DEFAULT_SIZE ) // Userspace app
#if SENSOR_SEQ_BINARY_AND_EXTERNAL
static char p_sensor_data[SENSOR_AR0231_SEQUENCE_DEFAULT_SIZE];
#else
static sensor_reg_t p_sensor_data[( SENSOR_AR0231_SEQUENCE_DEFAULT_SIZE / 4 )];
#endif
static int p_sensor_data_initialized = 0;
void sensor_ar0231_demo_set_init_seq( const char *seq, int seq_sz )
{
    if ( seq_sz != SENSOR_AR0231_SEQUENCE_DEFAULT_SIZE ) {
        LOG( LOG_ERR, "Sensor seq size doesn't match %d(seninit_dev) != %d(_seq.h).", seq_sz, SENSOR_AR0231_SEQUENCE_DEFAULT_SIZE );
        return;
    }
    system_memcpy( p_sensor_data, seq, SENSOR_AR0231_SEQUENCE_DEFAULT_SIZE );
    p_sensor_data_initialized = 1;
}
int sensor_ar0231_demo_get_init_seq( char *seq )
{
    if ( seq != NULL && p_sensor_data_initialized ) {
        system_memcpy( seq, p_sensor_data, SENSOR_AR0231_SEQUENCE_DEFAULT_SIZE );
    }
    return !p_sensor_data_initialized;
}
#else
#error "SENSOR_AR0231_SEQUENCE_DEFAULT nor SENSOR_AR0231_SEQUENCE_DEFAULT_SIZE are defined"
#endif

static int seq_number[] = {
    SENSOR_AR0231_SEQUENCE_DEFAULT_INIT_4LINE_1920X1080_30FPS,
    SENSOR_AR0231_SEQUENCE_DEFAULT_INIT_MIPI_1920X1080_15FPS,
    SENSOR_AR0231_SEQUENCE_DEFAULT_INIT_MIPI_NATIVE_WDR_3EXP,
    SENSOR_AR0231_SEQUENCE_DEFAULT_INIT_MIPI_DOL_2EXP,
    SENSOR_AR0231_SEQUENCE_DEFAULT_INIT_MIPI_DOL_3EXP,
    SENSOR_AR0231_SEQUENCE_DEFAULT_INIT_MIPI_DOL_4EXP,
};


//--------------------RESET------------------------------------------------------------
static void sensor_hw_reset_enable( void *sensor_priv )
{
    sensor_param_t *cfg = &( (sensor_private_t *)sensor_priv )->param;
    reset_state &= ~( 3 << ( 2 * cfg->video_port_id ) );
    system_timer_usleep( 10000 );
}

static void sensor_hw_reset_disable( void *sensor_priv )
{
    sensor_param_t *cfg = &( (sensor_private_t *)sensor_priv )->param;
    reset_state |= 3 << ( 2 * cfg->video_port_id );
    system_timer_usleep( 10000 );
}

static int32_t sensor_alloc_analog_gain( void *sensor_priv, int32_t gain )
{
    sensor_private_t *priv = sensor_priv;
    uint32_t again_linear;
    uint32_t cnt;

// Delay line logic
#if ( SENSOR_ANALOG_GAIN_APPLY_DELAY > 0 )
    {
        size_t i = SENSOR_ANALOG_GAIN_APPLY_DELAY;
        while ( i > 0 ) {
            priv->again[i] = priv->again[i - 1];
            --i;
        }
    }
#endif /*SENSOR_ANALOG_GAIN_APPLY_DELAY > 0*/

    if ( gain > priv->again_limit ) {
        gain = priv->again_limit;
    }

#if USE_CONV_GAIN
    uint32_t again_linear_in = again_linear = math_exp2( gain, LOG2_GAIN_SHIFT, AGAIN_SHIFT );
    uint32_t idx;

    for ( cnt = 0; cnt < sizeof( gain_tbl ) / sizeof( gain_tbl[0] ); cnt++ ) {
        if ( again_linear < gain_tbl[cnt][0] ) {
            break;
        }
    }
    if ( cnt ) {
        idx = cnt - 1;
    } else {
        idx = 0;
    }
    priv->again[0] = gain_tbl[idx][1];
    priv->again[0] |= ( gain_tbl[idx][2] << HCG_BIT );
    again_linear = gain_tbl[idx][0];
    LOG( LOG_DEBUG, "again: %d, conv gain: %d, idx: %d, in gain: %d, ret gain: %d",
         priv->again[0] & ~HCG_MASK, ( priv->again[0] >> HCG_BIT ) & 0x1, idx, again_linear_in, again_linear );

#else
    static const uint32_t again_lut[][2] = {
        {2520 * 4 / 5, 0b0110},
        {2520 * 5 / 5, 0b0111},
        {2520 * 5 / 4, 0b1000},
        {2520 * 6 / 4, 0b1001},
        {2520 * 6 / 3, 0b1010},
        {2520 * 7 / 3, 0b1011},
        {2520 * 7 / 2, 0b1100},
        {2520 * 8 / 2, 0b1101},
        {2520 * 8 / 1, 0b1110},
    };

    again_linear = math_exp2( gain, LOG2_GAIN_SHIFT, AGAIN_SHIFT );

    again_linear = again_linear * 2520 >> AGAIN_SHIFT;

    for ( cnt = 0; cnt < ( sizeof( again_lut ) / sizeof( again_lut[0] ) ); cnt++ ) {
        if ( again_linear < again_lut[cnt][0] ) {
            break;
        }
    }
    if ( cnt ) {
        priv->again[0] = again_lut[cnt - 1][1];
        again_linear = again_lut[cnt - 1][0];
        again_linear = ( again_linear << AGAIN_SHIFT ) / 2520;
    } else {
        priv->again[0] = again_lut[0][1];
        again_linear = again_lut[0][0];
        again_linear = ( again_linear << AGAIN_SHIFT ) / 2520;
    }
#endif

    /* After we have delayed the gain, check if the sensor requires an update.*/
    if ( priv->again_old != priv->again[SENSOR_ANALOG_GAIN_APPLY_DELAY] ) {
        priv->change_flg |= UPDATE_AGAIN;
    }

    return log2_fixed_to_fixed( again_linear, AGAIN_SHIFT, LOG2_GAIN_SHIFT );
}

static int32_t sensor_alloc_digital_gain( void *sensor_priv, int32_t gain )
{
    sensor_private_t *priv = sensor_priv;
    uint32_t dgain_linear;

    dgain_linear = math_exp2( gain, LOG2_GAIN_SHIFT, DGAIN_SHIFT );

    if ( priv->dgain != dgain_linear ) {
        priv->change_flg |= ( UPDATE_DGAIN );
        priv->dgain = dgain_linear;
        LOG( LOG_DEBUG, "alloc dgain: %d.%d\n", dgain_linear / 0x80, dgain_linear % 0x80 );
    }
    return log2_fixed_to_fixed( dgain_linear, DGAIN_SHIFT, LOG2_GAIN_SHIFT );
}

#if defined( ISP_HAS_ANTI_FLICKER_FSM )
static uint32_t get_flicker_freq( void )
{
    uint32_t flicker_freq = 0;
#if defined( TSYSTEM ) && defined( SYSTEM_ANTIFLICKER_ENABLE )
    uint32_t value = 0;
    uint8_t flicker_enable;
    application_command( TSYSTEM, SYSTEM_ANTIFLICKER_ENABLE, value, COMMAND_GET, (uint32_t *)&flicker_enable );
    if ( flicker_enable ) {
        application_command( TSYSTEM, SYSTEM_ANTI_FLICKER_FREQUENCY, value, COMMAND_GET, (uint32_t *)&value );
    }
    switch ( value ) {
    case FLICKER_50:
        flicker_freq = 50;
        break;
    case FLICKER_60:
        flicker_freq = 60;
        break;
    default:
        flicker_freq = 0;
        break;
    }
#endif
    return flicker_freq;
}
#endif

static uint32_t sensor_correct_exp_ratio( uint32_t input_int_time_short )
{
    uint32_t l_s_ratio = 0;

    if ( sexp_ratio[0][0] >= input_int_time_short ) {
        l_s_ratio = sexp_ratio[0][1];
    } else {
        uint32_t i;
        for ( i = 1; i < sizeof( sexp_ratio ) / sizeof( sexp_ratio[0] ); i++ ) {
            if ( sexp_ratio[i][0] >= input_int_time_short ) {
                uint32_t alpha = ( ( input_int_time_short - sexp_ratio[i - 1][0] ) * 256 ) /
                                 ( sexp_ratio[i][0] - sexp_ratio[i - 1][0] );

                l_s_ratio = sexp_ratio[i - 1][1] +
                            ( alpha * ( sexp_ratio[i][1] - sexp_ratio[i - 1][1] ) / 256 );
                break;
            }
        }
    }
    return l_s_ratio;
}

static void sensor_alloc_4_exp( void *sensor_priv, integration_times_t *int_times )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;
    uint32_t *int_time = &int_times->int_time;
    uint32_t *int_time_M = &int_times->int_time_M;
    uint32_t *int_time_M2 = &int_times->int_time_M2;
    uint32_t *int_time_L = &int_times->int_time_L;
    uint32_t input_int_time_t1 = *int_time_L;
    uint32_t input_int_time_t2 = *int_time_M;
    uint32_t input_int_time_t3 = *int_time_M2;
    uint32_t input_int_time_t4 = *int_time;

    if ( priv->is_fixed_exp_ratio ) {
        uint32_t l_s_ratio = 0;

        input_int_time_t3 = input_int_time_t4 * priv->exp_ratios.t3_t4;
        input_int_time_t2 = input_int_time_t3 * priv->exp_ratios.t2_t3;
        input_int_time_t1 = input_int_time_t2 * priv->exp_ratios.t1_t2;
        if ( input_int_time_t1 > cfg->integration_time_long_max ) {
            *int_time_L = input_int_time_t1 = cfg->integration_time_long_max;
        }
        /* Correct L/S exposure ratio based on sexp_ratio lookup table. */
        l_s_ratio = sensor_correct_exp_ratio( input_int_time_t4 );

        /* Correct long line-count if long to short ratio is set. */
        if ( l_s_ratio != 0 ) {
            input_int_time_t1 = ( input_int_time_t4 * l_s_ratio );
        }
        *int_time_L = input_int_time_t1;
        *int_time_M2 = *int_time_L / priv->exp_ratios.t1_t2;
        *int_time_M = *int_time_M2 / priv->exp_ratios.t2_t3;

        input_int_time_t1 = input_int_time_t1 & ~( ( 1 << cfg->integration_time_precision ) - 1 );
        if ( priv->integration_timeL != ( input_int_time_t1 ) ) {
            priv->integration_timeL = input_int_time_t1;
            priv->change_flg |= ( UPDATE_LONG_INTEGRATION_TIME );
        }
    } else {
        if ( ( *int_time < cfg->integration_time_min ) || ( ( *int_time ) > ( *int_time_M ) ) || ( ( *int_time_M ) > ( *int_time_L ) ) ) {
            LOG( LOG_ERR, "Incorrect integration times ratios! int time S: %d, M2: %d, M: %d, L: %d",
                 *int_time, *int_time_M2, *int_time_M, *int_time_L );
            *int_time = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME4 ) << cfg->integration_time_precision;
            *int_time_M2 = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME3 ) << cfg->integration_time_precision;
            *int_time_M = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME2 ) << cfg->integration_time_precision;
            *int_time_L = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME ) << cfg->integration_time_precision;
            return;
        }
        priv->exp_ratios.t1_t2 = ( *int_time_L ) / ( *int_time_M );
        priv->exp_ratios.t2_t3 = ( *int_time_M ) / ( *int_time_M2 );
        priv->exp_ratios.t3_t4 = ( *int_time_M2 ) / ( *int_time );

        if ( input_int_time_t4 > cfg->integration_time_max )
            *int_time = input_int_time_t4 = cfg->integration_time_max;
        if ( input_int_time_t2 > cfg->integration_time_medium_max )
            *int_time_M = input_int_time_t2 = cfg->integration_time_medium_max;
        if ( input_int_time_t1 > cfg->integration_time_long_max )
            *int_time_L = input_int_time_t1 = cfg->integration_time_long_max;

        // Sensor will not apply fine integration time, discard fraction part.
        input_int_time_t4 = input_int_time_t4 & ~( ( 1 << cfg->integration_time_precision ) - 1 );
        input_int_time_t3 = input_int_time_t3 & ~( ( 1 << cfg->integration_time_precision ) - 1 );
        input_int_time_t2 = input_int_time_t2 & ~( ( 1 << cfg->integration_time_precision ) - 1 );
        input_int_time_t1 = input_int_time_t1 & ~( ( 1 << cfg->integration_time_precision ) - 1 );

        if ( ( priv->integration_time != input_int_time_t4 ) || ( priv->integration_timeM2 != input_int_time_t3 ) || ( priv->integration_timeM != input_int_time_t2 ) || ( priv->integration_timeL != input_int_time_t1 ) ) {
            priv->integration_time = input_int_time_t4;
            priv->integration_timeM2 = input_int_time_t3;
            priv->integration_timeM = input_int_time_t2;
            priv->integration_timeL = input_int_time_t1;

            priv->change_flg |= ( UPDATE_4_INTEGRATION_TIMES );
        }
        LOG( LOG_INFO, "Apply integration times - S: %d, M: %d, L: %d - ratios M2/S: %d, M/M2: %d, L/M: %d.",
             *int_time,
             *int_time_M2,
             *int_time_L,
             priv->exp_ratios.t3_t4,
             priv->exp_ratios.t2_t3,
             priv->exp_ratios.t1_t2 );
    }
}

static void sensor_alloc_3_exp( void *sensor_priv, integration_times_t *int_times )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;
    uint32_t *int_time = &int_times->int_time;
    uint32_t *int_time_M = &int_times->int_time_M;
    uint32_t *int_time_L = &int_times->int_time_L;
    uint32_t input_int_time_t1 = *int_time_L;
    uint32_t input_int_time_t2 = *int_time_M;
    uint32_t input_int_time_t3 = *int_time;

    if ( priv->is_fixed_exp_ratio ) {
        /* Long to short ratio 0 is invalid value. */
        uint32_t l_s_ratio = 0;

        input_int_time_t2 = input_int_time_t3 * priv->exp_ratios.t2_t3;
        input_int_time_t1 = input_int_time_t2 * priv->exp_ratios.t1_t2;
        if ( input_int_time_t1 > cfg->integration_time_long_max ) {
            *int_time_L = input_int_time_t1 = cfg->integration_time_long_max;
        }

        /* Correct L/S exposure ratio based on sexp_ratio lookup table. */
        l_s_ratio = sensor_correct_exp_ratio( input_int_time_t3 );

        /* Correct long line-count if long to short ratio is set. */
        if ( l_s_ratio != 0 ) {
            input_int_time_t1 = ( input_int_time_t3 * l_s_ratio );
        }
        *int_time_L = input_int_time_t1;
        *int_time_M = *int_time_L / priv->exp_ratios.t1_t2;

        input_int_time_t1 = input_int_time_t1 & ~( ( 1 << cfg->integration_time_precision ) - 1 );
        if ( priv->integration_timeL != ( input_int_time_t1 ) ) {
            priv->integration_timeL = input_int_time_t1;
            priv->change_flg |= ( UPDATE_LONG_INTEGRATION_TIME );
        }

        /* Limit min exposure times to one line. */
        if ( *int_time_M < ( 1 << cfg->integration_time_precision ) ) {
            *int_time_M = ( 1 << cfg->integration_time_precision );
        }

        /* When long to short ratio is used and long exposure time is corrected,
         * dont report real short exposure, but leave as it was provided from AE */
        if ( l_s_ratio == 0 ) {
            if ( *int_time < ( 1 << cfg->integration_time_precision ) ) {
                *int_time = ( 1 << cfg->integration_time_precision );
            }
        }

        LOG( LOG_DEBUG, "Apply integration times - S: %d, M: %d, L: %d - ratios L/S: %d, L/M: %d.",
             *int_time, *int_time_M, *int_time_L, l_s_ratio, priv->exp_ratios.t1_t2 );
    } else {
        if ( ( *int_time < cfg->integration_time_min ) || ( ( *int_time ) > ( *int_time_M ) ) || ( ( *int_time_M ) > ( *int_time_L ) ) ) {
            LOG( LOG_ERR, "Incorrect integration times ratios! int time S: %d, M: %d, L: %d.",
                 *int_time, *int_time_M, *int_time_L );
            *int_time = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME3 ) << cfg->integration_time_precision;
            *int_time_M = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME2 ) << cfg->integration_time_precision;
            *int_time_L = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME ) << cfg->integration_time_precision;
            return;
        }
        priv->exp_ratios.t1_t2 = ( *int_time_L ) / ( *int_time_M );
        priv->exp_ratios.t2_t3 = ( *int_time_M ) / ( *int_time );

        if ( input_int_time_t3 > cfg->integration_time_max )
            *int_time = input_int_time_t3 = cfg->integration_time_max;
        if ( input_int_time_t2 > cfg->integration_time_medium_max )
            *int_time_M = input_int_time_t2 = cfg->integration_time_medium_max;
        if ( input_int_time_t1 > cfg->integration_time_long_max )
            *int_time_L = input_int_time_t1 = cfg->integration_time_long_max;

        // Sensor will not apply fine integration time, discard fractional part.
        input_int_time_t3 = input_int_time_t3 & ~( ( 1 << cfg->integration_time_precision ) - 1 );
        input_int_time_t2 = input_int_time_t2 & ~( ( 1 << cfg->integration_time_precision ) - 1 );
        input_int_time_t1 = input_int_time_t1 & ~( ( 1 << cfg->integration_time_precision ) - 1 );

        if ( ( priv->integration_time != input_int_time_t3 ) || ( priv->integration_timeM != input_int_time_t2 ) || ( priv->integration_timeL != input_int_time_t1 ) ) {
            priv->integration_time = input_int_time_t3;
            priv->integration_timeM = input_int_time_t2;
            priv->integration_timeL = input_int_time_t1;

            priv->change_flg |= ( UPDATE_3_INTEGRATION_TIMES );
        }
        LOG( LOG_DEBUG, "Apply integration times - S: %d, M: %d, L: %d - ratios M/S: %d, L/M: %d.",
             *int_time, *int_time_M, *int_time_L, priv->exp_ratios.t2_t3, priv->exp_ratios.t1_t2 );
    }
}


static void sensor_alloc_2_exp( void *sensor_priv, integration_times_t *int_times )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;
    uint32_t *int_time = &int_times->int_time;
    uint32_t *int_time_L = &int_times->int_time_L;
    uint32_t input_int_time_t1 = *int_time_L;
    uint32_t input_int_time_t2 = *int_time;

    if ( priv->is_fixed_exp_ratio ) {
        uint32_t l_s_ratio = 0;

        input_int_time_t1 = input_int_time_t2 * priv->exp_ratios.t1_t2;
        if ( input_int_time_t1 > cfg->integration_time_long_max ) {
            *int_time_L = input_int_time_t1 = cfg->integration_time_long_max;
        }
        /* Correct L/S exposure ratio based on sexp_ratio lookup table */
        l_s_ratio = sensor_correct_exp_ratio( input_int_time_t2 );

        /* Correct long line-count if long to short ratio is set */
        if ( l_s_ratio != 0 ) {
            input_int_time_t1 = ( input_int_time_t2 * l_s_ratio );
        }

        *int_time_L = input_int_time_t1;

        input_int_time_t1 &= ~( ( 1 << cfg->integration_time_precision ) - 1 );
        if ( priv->integration_timeL != ( input_int_time_t1 ) ) {
            priv->integration_timeL = input_int_time_t1;
            priv->change_flg |= ( UPDATE_LONG_INTEGRATION_TIME );
        }
        LOG( LOG_DEBUG, "Alloc integration times - S: %d, L: %d - ratios L/S: %d.",
             *int_time, *int_time_L, priv->exp_ratios.t1_t2 );
    } else {
        if ( ( *int_time < cfg->integration_time_min ) || ( ( *int_time ) > ( *int_time_L ) ) ) {
            LOG( LOG_ERR, "Incorrect integration times ratios! int time S: %d, L: %d",
                 *int_time, *int_time_L );
            *int_time = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME2 ) << cfg->integration_time_precision;
            *int_time_L = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME ) << cfg->integration_time_precision;
            return;
        }
        priv->exp_ratios.t1_t2 = ( *int_time_L ) / ( *int_time );

        if ( input_int_time_t2 > cfg->integration_time_max )
            *int_time = input_int_time_t2 = cfg->integration_time_max;
        if ( input_int_time_t1 > cfg->integration_time_long_max )
            *int_time_L = input_int_time_t1 = cfg->integration_time_long_max;

        // Sensor will not apply fine integration time, discard fraction part.
        input_int_time_t2 = input_int_time_t2 & ~( ( 1 << cfg->integration_time_precision ) - 1 );
        input_int_time_t1 = input_int_time_t1 & ~( ( 1 << cfg->integration_time_precision ) - 1 );

        if ( ( priv->integration_time != input_int_time_t2 ) || ( priv->integration_timeL != input_int_time_t1 ) ) {
            priv->integration_time = input_int_time_t2;
            priv->integration_timeL = input_int_time_t1;

            priv->change_flg |= ( UPDATE_2_INTEGRATION_TIMES );
        }
        LOG( LOG_DEBUG, "Apply integration times - S: %d, L: %d - ratio L/S: %d.",
             *int_time, *int_time_L, priv->exp_ratios.t1_t2 );
    }
}

static void sensor_alloc_1_exp( void *sensor_priv, integration_times_t *int_times )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    uint32_t *int_time = &int_times->int_time;

    if ( *int_time < cfg->integration_time_min )
        *int_time = cfg->integration_time_min;

    // Extend total line width if requested integration time is bigger than HTS.
    if ( *int_time > cfg->integration_time_max )
        *int_time = cfg->integration_time_max;

    // Sensor will not apply fine integration time, discard fraction part.
    *int_time = *int_time & ~( ( 1 << cfg->integration_time_precision ) - 1 );

    // Check if integration time has changed.
    if ( priv->integration_time != ( *int_time ) ) {
        priv->change_flg |= ( UPDATE_1_INTEGRATION_TIME );
        priv->integration_time = *int_time;
    }
}

static void sensor_alloc_integration_time( void *sensor_priv, integration_times_t *int_times )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;

    switch ( cfg->sensor_exp_number ) {
    case 1:
        sensor_alloc_1_exp( sensor_priv, int_times );
        break;
    case 2:
        sensor_alloc_2_exp( sensor_priv, int_times );
        break;
    case 3:
        sensor_alloc_3_exp( sensor_priv, int_times );
        break;
    case 4:
        sensor_alloc_4_exp( sensor_priv, int_times );
        break;
    }
}

#if USE_POST_DLO_WB_COMPENSATION
static void sensor_alloc_white_balance_post_dlo_gains( sensor_private_t *priv, int32_t gain[4] )
{
    priv->change_flg |= UPDATE_POST_CHANNEL_DGAIN;

    priv->ch_post_dlo_dgain[0] = ( ( 1U << 31 ) / priv->ch_dgain[0] ) >> ( 31 - POST_DLO_DGAIN_SHIFT - DGAIN_SHIFT );
    priv->ch_post_dlo_dgain[1] = ( ( 1U << 31 ) / priv->ch_dgain[1] ) >> ( 31 - POST_DLO_DGAIN_SHIFT - DGAIN_SHIFT );
    priv->ch_post_dlo_dgain[2] = ( ( 1U << 31 ) / priv->ch_dgain[2] ) >> ( 31 - POST_DLO_DGAIN_SHIFT - DGAIN_SHIFT );
    priv->ch_post_dlo_dgain[3] = ( ( 1U << 31 ) / priv->ch_dgain[3] ) >> ( 31 - POST_DLO_DGAIN_SHIFT - DGAIN_SHIFT );

    gain[0] = 0;
    gain[1] = 0;
    gain[2] = 0;
    gain[3] = 0;
}
#else
static void sensor_alloc_white_balance_post_dlo_gains( sensor_private_t *priv, int32_t gain[4] )
{
}
#endif

static void sensor_alloc_white_balance_gains( void *sensor_priv, int32_t gain[4] )
{
    sensor_private_t *priv = sensor_priv;

    priv->change_flg |= UPDATE_CHANNEL_DGAIN;

    priv->ch_dgain[0] = math_exp2( gain[0], LOG2_GAIN_SHIFT, DGAIN_SHIFT );
    priv->ch_dgain[1] = math_exp2( gain[1], LOG2_GAIN_SHIFT, DGAIN_SHIFT );
    priv->ch_dgain[2] = math_exp2( gain[2], LOG2_GAIN_SHIFT, DGAIN_SHIFT );
    priv->ch_dgain[3] = math_exp2( gain[3], LOG2_GAIN_SHIFT, DGAIN_SHIFT );

    /* Allocate post DLO gains used for white balance compensation.
     * NOTE: function is changing the values of the gains. */
    sensor_alloc_white_balance_post_dlo_gains( priv, gain );
}

/**
 * @brief      Updates sensor registers
 *
 * @param      sensor_priv  The sensor private data
 *
 * @details    All register writes are delayed by one frame. A
 *             register that is written to during the readout of frame n will
 *             not be updated to the new value until the readout of frame n+2.
 *             This includes WRITEs to the sensor gain and integration
 *             registers.
 */
static void sensor_update( void *sensor_priv )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;

    if ( priv->change_flg ) {
        // ---------- Start Changes -------------
        acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_GROUPED_PARAMETER_HOLD, 0x01 );

        if ( priv->change_flg & UPDATE_LONG_INTEGRATION_TIME ) {
            uint32_t x = priv->integration_timeL >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME, (uint16_t)x );
            LOG( LOG_DEBUG, "Set expo long: %d", x );
        }
        if ( priv->change_flg & UPDATE_3_INTEGRATION_TIMES ) {
            uint32_t x = priv->integration_timeL >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME, (uint16_t)x );

            x = priv->integration_timeM >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME2, (uint16_t)x );

            x = priv->integration_time >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME3, (uint16_t)x );
            LOG( LOG_DEBUG, "Set expo S: %d, M: %d, L: %d", priv->integration_time,
                 priv->integration_timeM, priv->integration_timeL );
        }
        if ( priv->change_flg & UPDATE_4_INTEGRATION_TIMES ) {
            uint32_t x = priv->integration_timeL >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME, (uint16_t)x );

            x = priv->integration_timeM >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME2, (uint16_t)x );

            x = priv->integration_timeM2 >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME3, (uint16_t)x );

            x = priv->integration_time >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME4, (uint16_t)x );
            LOG( LOG_DEBUG, "Set expo S: %d, M: %d, M2: %d, L: %d", priv->integration_time,
                 priv->integration_timeM, priv->integration_timeM2, priv->integration_timeL );
        }
        if ( priv->change_flg & UPDATE_2_INTEGRATION_TIMES ) {
            uint32_t x = priv->integration_timeL >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME, (uint16_t)x );

            x = priv->integration_time >> cfg->integration_time_precision;
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME2, (uint16_t)x );
            LOG( LOG_DEBUG, "Set expo S: %d, L: %d", priv->integration_time,
                 priv->integration_timeL );
        }

        if ( priv->change_flg & UPDATE_AGAIN ) {
            priv->again_old = priv->again[SENSOR_ANALOG_GAIN_APPLY_DELAY];
            // ---------- Analog Gain -------------
            uint16_t again = priv->again[SENSOR_ANALOG_GAIN_APPLY_DELAY] & ( ~HCG_MASK );
            again = again | ( again << 4 ) | ( again << 8 ) | ( again << 12 );
            LOG( LOG_DEBUG, "Set again: 0x%x", again );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_ANALOG_GAIN, again );
#if USE_CONV_GAIN
            uint32_t cgain_single = ( priv->again[SENSOR_ANALOG_GAIN_APPLY_DELAY] >> HCG_BIT ) & 0x1;
            // set same conversion gain for T1, T2 and T3
            uint32_t conv_gain = cgain_single | cgain_single << 1 | cgain_single << 2;
            LOG( LOG_DEBUG, "Set conversion gain: 0x%x", conv_gain );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_CONV_GAIN, conv_gain );
#endif
        }

        if ( priv->change_flg & UPDATE_1_INTEGRATION_TIME ) {
            // -------- Integration Time ----------
            uint32_t x = priv->integration_time >> cfg->integration_time_precision;
            LOG( LOG_DEBUG, "Set expo: %d", x );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME, (uint16_t)x );
        }

        if ( priv->change_flg & UPDATE_DGAIN ) {
            // ---------- Digital Gain -------------
            LOG( LOG_DEBUG, "Set dgain: %d", priv->dgain );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_GLOBAL_GAIN, priv->dgain );
        }

        if ( priv->change_flg & UPDATE_CHANNEL_DGAIN ) {
            // ---------- Per channel digital gain -------------
            LOG( LOG_DEBUG, "Set per channel dgain: %d %d %d %d", priv->ch_dgain[0],
                 priv->ch_dgain[1], priv->ch_dgain[2], priv->ch_dgain[3] );

            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_DGAIN_R, priv->ch_dgain[0] );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_DGAIN_G1, priv->ch_dgain[1] );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_DGAIN_G2, priv->ch_dgain[2] );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_DGAIN_B, priv->ch_dgain[3] );
        }

        if ( priv->change_flg & UPDATE_POST_CHANNEL_DGAIN ) {
            // ---------- Per channel digital gain -------------
            LOG( LOG_DEBUG, "Set per post dlo channel dgain: %d %d %d %d", priv->ch_post_dlo_dgain[0],
                 priv->ch_post_dlo_dgain[1], priv->ch_post_dlo_dgain[2], priv->ch_post_dlo_dgain[3] );

            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_POST_DLO_DGAIN_R, priv->ch_post_dlo_dgain[0] );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_POST_DLO_DGAIN_G1, priv->ch_post_dlo_dgain[1] );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_POST_DLO_DGAIN_G2, priv->ch_post_dlo_dgain[2] );
            acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_POST_DLO_DGAIN_B, priv->ch_post_dlo_dgain[3] );
        }

        // ---------- End of changes -------------
        acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_GROUPED_PARAMETER_HOLD, 0x00 );
        priv->change_flg = 0;
    }
}

void request_next_frame( void *sensor_priv )
{
    sensor_private_t *priv = sensor_priv;
    request_next_frame_common( &priv->param, &priv->remote_frame_data );

    sensor_update( sensor_priv );
}

static void register_frame_callbacks( void *sensor_priv, const sensor_remote_callbacks_t *callbacks )
{
    sensor_private_t *priv = sensor_priv;
    register_frame_callbacks_common( &priv->param, callbacks );
}

static void sensor_get_exp_ratios( void *sensor_priv )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;
    uint32_t exp_ratio_reg;

    exp_ratio_reg = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_EXPOSURE_RATIO );
    if ( ( exp_ratio_reg & 0x8000 ) ) {
        LOG( LOG_DEBUG, "Exposure ratios are not fixed" );
        priv->is_fixed_exp_ratio = 0;
        uint32_t int_time_t1 = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME ) << cfg->integration_time_precision;
        uint32_t int_time_t2 = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME2 ) << cfg->integration_time_precision;
        uint32_t int_time_t3 = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME3 ) << cfg->integration_time_precision;
        uint32_t int_time_t4 = (uint32_t)acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_INTEGRATION_TIME4 ) << cfg->integration_time_precision;
        priv->exp_ratios.t1_t2 = int_time_t1 / int_time_t2;
        priv->exp_ratios.t2_t3 = int_time_t2 / int_time_t3;
        priv->exp_ratios.t3_t4 = int_time_t3 / int_time_t4;
    } else {
        LOG( LOG_DEBUG, "Exposure ratios are fixed in sensor" );
        priv->is_fixed_exp_ratio = 1;
        priv->exp_ratios.t1_t2 = 1 << ( exp_ratio_reg & 0x7 );
        priv->exp_ratios.t2_t3 = 1 << ( ( exp_ratio_reg & 0x70 ) >> 4 );
        priv->exp_ratios.t3_t4 = 1 << ( ( exp_ratio_reg & 0x700 ) >> 8 );
    }
    LOG( LOG_INFO, "Exposure ratios - T1/T2: %d, T2/T3: %d, T3/T4: %d",
         priv->exp_ratios.t1_t2,
         priv->exp_ratios.t2_t3,
         priv->exp_ratios.t3_t4 );
}

static uint32_t set_num_exposures( acamera_sbus_ptr_t p_sbus, uint32_t num_expos )
{
    uint16_t op_mode_ctrl;
    uint16_t exp_ratio_reg;

    if ( MAX_SENSOR_EXPOSURES < num_expos ) {
        num_expos = MAX_SENSOR_EXPOSURES;
        LOG( LOG_ERR, "Trying to set number of exposures bigger than expected!" );
    }
    op_mode_ctrl = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_OPERATION_MODE_CTRL );
    op_mode_ctrl &= ( ~( 3 << 2 ) );
    op_mode_ctrl |= ( ( num_expos - 1 ) << 2 );
    LOG( LOG_DEBUG, "Set operation mode ctrl: 0x%x", op_mode_ctrl );
    acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_OPERATION_MODE_CTRL, op_mode_ctrl );

    if ( num_expos > 1 ) {
        exp_ratio_reg = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_EXPOSURE_RATIO );
        exp_ratio_reg &= 0x8000;
        exp_ratio_reg |= exp_ratios_lut[num_expos - 2];
        LOG( LOG_DEBUG, "Write exposure ratio register: 0x%x", exp_ratio_reg );
        acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_EXPOSURE_RATIO, exp_ratio_reg );
    }
    return num_expos;
}

static void set_int_time_limits( acamera_sbus_ptr_t p_sbus, sensor_param_t *cfg )
{
    uint16_t exp_ratio_reg;
    uint32_t exp = cfg->sensor_exp_number - 1;
    uint32_t exp_buf_limit;

    cfg->integration_time_min = SENSOR_MIN_INTEGRATION_TIME << cfg->integration_time_precision;
    if ( cfg->sensor_exp_number > 1 ) {
        exp_ratio_reg = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_EXPOSURE_RATIO );
        // Fixed exposure ratios
        cfg->integration_time_long_max = cfg->active.height << cfg->integration_time_precision;
        // Multiply T1 buffer limit by T1/T2 exposure ratio.
        exp_buf_limit = int_time_buffers[exp].t1 * ( 1 << ( exp_ratio_reg & 7 ) ) << cfg->integration_time_precision;
        if ( exp_buf_limit < cfg->integration_time_long_max ) {
            LOG( LOG_DEBUG, "Limit max long exposure to %d.", exp_buf_limit );
            cfg->integration_time_long_max = exp_buf_limit;
        }
        if ( cfg->sensor_exp_number == 2 ) {
            cfg->integration_time_max = int_time_buffers[exp].t1 << cfg->integration_time_precision;
        } else if ( cfg->sensor_exp_number == 3 ) {
            cfg->integration_time_medium_max = int_time_buffers[exp].t1 << cfg->integration_time_precision;
            cfg->integration_time_max = int_time_buffers[exp].t2 << cfg->integration_time_precision;
        } else if ( cfg->sensor_exp_number == 4 ) {
            cfg->integration_time_medium_max = int_time_buffers[exp].t1 << cfg->integration_time_precision;
            // cfg->integration_time_medium2_max = int_time_buffers[exp].t2 << cfg->integration_time_precision;
            cfg->integration_time_max = int_time_buffers[exp].t3 << cfg->integration_time_precision;
        }
    } else {
        cfg->integration_time_max = cfg->active.height << cfg->integration_time_precision;
    }
    LOG( LOG_DEBUG, "Set max int time - long: %d, med: %d, med2: %d, short: %d",
         cfg->integration_time_long_max,
         cfg->integration_time_medium_max,
         -1, // cfg->integration_time_medium2_max,
         cfg->integration_time_max );

    cfg->integration_time_limit = cfg->integration_time_max;
    cfg->day_light_integration_time_max = SENSOR_DAY_LIGHT_INTEGRATION_TIME_LIMIT << cfg->integration_time_precision;
}

static void sensor_set_mode( void *sensor_priv, uint8_t mode ) // Mode is preset
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    remote_sensor_frame_data_t *remote_frame_data = &priv->remote_frame_data;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;

    LOG( LOG_INFO, "\n" );
    LOG( LOG_INFO, "--------- AR0231 set_mode start ----------" );
	// remove sensor init sequence by 10000058
    //if ( sensor_ar0231_demo_get_init_seq( NULL ) != 0 ) {
    //    LOG( LOG_ERR, "There's NO sensor_init_seq!!! sensor_set_mode failed. Returning..." );
    //    return;
    //}
    if ( mode >= ( sizeof( seq_number ) / sizeof( seq_number[0] ) ) ) {
        LOG( LOG_ERR, "Mode value is greater than expected!" );
        return;
    }

#if ACAMERA_MIPI_TO_DVP_BOARD
    mipi_init( &priv->sensor_iface, &mipi_settings[mode] );
#endif

    LOG( LOG_INFO, "Preset mode: %d, seq num: %d", mode, seq_number[mode] );
	// remove sensor load sequence by 10000058
    //sensor_load_sequence( p_sbus, priv->seq_width, p_sensor_data, seq_number[mode] );

    cfg->active.width = 1920;  //acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_X_ADDR_END ) -
                               //           acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_X_ADDR_START ) + 1;
    cfg->active.height = 1080; //acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_Y_ADDR_END ) -
                               //           acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_Y_ADDR_START ) + 1;
    cfg->total.width = 1920;//acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_LINE_LENGH_PCK );
    cfg->total.height = 1080;//acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_FRAME_LENGTH_LINES );


    LOG( LOG_DEBUG, "Read width: %d, height: %d", cfg->active.width, cfg->active.height );
    LOG( LOG_DEBUG, "Read line len: %d, frame len: %d", cfg->total.width, cfg->total.height );

    cfg->preset_mode = mode;
    cfg->sensor_exp_number = set_num_exposures( p_sbus, supported_modes[mode].exposures );
    cfg->num_channel = supported_modes[mode].num_channels;
    cfg->is_reverse_order = 1;

    // Due to SENSOR_REGADDR_GLOBAL_GAIN sensor register format (fixed-point 4.7) we have to limit digital gain value to
    // 1111.1111111 ~ 15.9921875
    // After LOG2_SENSOR_DGAIN_(*)_MAXIMUM (default 4) conversion to fixed-point format (currently s13.18) final value is then limited to
    // 111.111111111111111111 (3.99999618...) which will give linear digital gain 2^3.99999618 ~ 15.999957
    if ( supported_modes[mode].wdr_mode == WDR_MODE_NATIVE ) {
        cfg->dgain_log2_max = ( LOG2_SENSOR_DGAIN_NATIVE_MAXIMUM > 0 ) ? ( ( ( LOG2_SENSOR_DGAIN_NATIVE_MAXIMUM ) << LOG2_GAIN_SHIFT ) - 1 ) : 0;
        // Code blocked due to abnormal behavior on white balance.
        //cfg->wb_gain_log2_max = ( LOG2_SENSOR_WB_GAIN_NATIVE_MAXIMUM << LOG2_GAIN_SHIFT );
    } else {
        cfg->dgain_log2_max = ( LOG2_SENSOR_DGAIN_MAXIMUM > 0 ) ? ( ( ( LOG2_SENSOR_DGAIN_MAXIMUM ) << LOG2_GAIN_SHIFT ) - 1 ) : 0;
        // Code blocked due to abnormal behavior on white balance.
        //cfg->wb_gain_log2_max = ( LOG2_SENSOR_WB_GAIN_MAXIMUM << LOG2_GAIN_SHIFT );
    }

    LOG( LOG_DEBUG, "Exposures number: %d", cfg->sensor_exp_number );
    LOG( LOG_DEBUG, "Channels number: %d", cfg->num_channel );

    set_int_time_limits( p_sbus, cfg );

    sensor_get_lines_per_second( sensor_priv );

    if ( cfg->sensor_exp_number > 1 ) {
        sensor_get_exp_ratios( sensor_priv );

        LOG( LOG_INFO, "--------- AR0231 set_mode end ----------\n" );
    }

    sensor_alloc_analog_gain( sensor_priv, 0 );

    priv->integration_time = 4 << SENSOR_INTEGRATION_TIME_PRECISION;
    priv->integration_timeM = ( priv->integration_time * 2 ) << SENSOR_INTEGRATION_TIME_PRECISION;
    priv->integration_timeM2 = ( priv->integration_timeM * 2 ) << SENSOR_INTEGRATION_TIME_PRECISION;
    priv->integration_timeL = ( priv->integration_timeM2 * 2 ) << SENSOR_INTEGRATION_TIME_PRECISION;

    priv->change_flg = 0;

    if ( remote_sensor_reinit( cfg, remote_frame_data, 1 ) ) {
        LOG( LOG_ERR, "Failed to initialize remote sensor." );
    }
}

static uint16_t sensor_get_id( void *sensor_priv )
{
    sensor_private_t *priv = sensor_priv;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;

    uint16_t sensor_id = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_CHIP_VERSION_REG );
    return ( sensor_id );
}

static const sensor_param_t *sensor_get_parameters( void *sensor_priv )
{
    sensor_private_t *priv = sensor_priv;
    return (const sensor_param_t *)&priv->param;
}

static uint8_t sensor_fps_control( void *sensor_priv, uint8_t fps )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    //    acamera_sbus_ptr_t p_sbus = &priv->sbus;
    if ( cfg->preset_mode != 0 ) {
        return 0;
    }
    switch ( fps ) {
    case 0: // Means read FPS.
        sensor_get_lines_per_second( sensor_priv );
        return cfg->lines_per_second / cfg->total.height;
    case 25:
        sensor_get_lines_per_second( sensor_priv );
        return 25;
    case 30:
        sensor_get_lines_per_second( sensor_priv );
        return 30;
    }
    return 0;
}

static void sensor_get_lines_per_second( void *sensor_priv )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;

    uint32_t lines_per_second = 0;
    uint32_t pixel_clock;

    uint16_t pll_multiplier = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_PLL_MULTIPLIER );
    uint16_t pre_pll_clk_div = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_PRE_PLL_CLK_DIV );
    uint16_t vt_sys_clk_div = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_VT_SYS_CLK_DIV );
    uint16_t vt_pix_clk_div = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_VT_PIX_CLK_DIV );

    pixel_clock = ( ( ( SENSOR_BOARD_MASTER_CLOCK / 1000 ) << 8 ) * pll_multiplier ) /
                  ( pre_pll_clk_div * vt_sys_clk_div * vt_pix_clk_div );

    pixel_clock = pixel_clock << 12; //Format 12.20 in MHz

    lines_per_second = pixel_clock / cfg->total.width;
    lines_per_second = ( lines_per_second * ( ( 1000 * 1000 ) >> 8 ) ) >> 12;
    cfg->lines_per_second = lines_per_second;
    LOG( LOG_DEBUG, "Pixel clock: %u, lines per second: %u", pixel_clock >> 20, lines_per_second );
}

static uint32_t read_register( void *sensor_priv, uint32_t address )
{
    sensor_private_t *priv = sensor_priv;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;
    return acamera_sbus_read_u16( p_sbus, address );
}

static void write_register( void *sensor_priv, uint32_t address, uint32_t data )
{
    sensor_private_t *priv = sensor_priv;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;
    acamera_sbus_write_u16( p_sbus, address, data );
}

static void stop_streaming( void *sensor_priv )
{
    uint16_t cur_reg;
    sensor_private_t *priv = sensor_priv;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;
    priv->streaming_flg = 0;

    cur_reg = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_RESET_REGISTER );
    cur_reg &= ( ~0x4 );
    acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_RESET_REGISTER, cur_reg );

    // Wait util sensor is stopped
    int iterations = 0;
    while ( ( acamera_sbus_read_u16( p_sbus, SENSOR_FRAME_STATUS ) & ( 1 << SENSOR_FRAME_STATUS_PLL_LOCKED_BIT ) ) && ( iterations < 100 ) ) {
        system_timer_usleep( 1000 );
        iterations++;
    }

    if ( iterations >= 100 ) {
        LOG( LOG_ERR, "Sensor failed to stop after %d ms.", iterations );
    } else {
        LOG( LOG_NOTICE, "Sensor stopped after %d ms.", iterations );
    }
}

static void start_streaming( void *sensor_priv )
{
    uint16_t cur_reg;
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    remote_sensor_frame_data_t *remote_frame_data = &priv->remote_frame_data;
    acamera_sbus_ptr_t p_sbus = &priv->sbus;

    priv->streaming_flg = 1;
    cur_reg = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_RESET_REGISTER );
    cur_reg |= ( 0x4 );
    acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_RESET_REGISTER, cur_reg );

    remote_sensor_start_streaming( cfg, remote_frame_data );
}

static void sensor_deinit( void *sensor_priv )
{
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    remote_sensor_frame_data_t *remote_frame_data = &priv->remote_frame_data;

    remote_sensor_deinit( cfg, remote_frame_data );
}
#define PLATFORM_DEVICE_SENSOR 0
void sensor_init_ar0231_demo( void **priv_ptr, uint8_t location, sensor_control_t *ctrl, const sensor_options_t *const options )
{
    sensor_private_t *priv = *priv_ptr = priv_array + location;
    sensor_param_t *cfg = &priv->param;
    remote_sensor_frame_data_t *remote_frame_data = &priv->remote_frame_data;
    system_memset( cfg, 0, sizeof( sensor_param_t ) );
    system_memset( remote_frame_data, 0, sizeof( remote_sensor_frame_data_t ) );
    
	priv->sbus.bus = system_platform_get_regbase_vaddr( PLATFORM_DEVICE_SENSOR, location );
    priv->sbus.device = SENSOR_DEV_ADDRESS;
    priv->sbus.mask = ( SBUS_MASK_SAMPLE_16BITS |
                        SBUS_MASK_ADDR_16BITS |
                        SBUS_MASK_ADDR_SWAP_BYTES |
                        SBUS_MASK_SAMPLE_SWAP_BYTES );

    acamera_sbus_init( &priv->sbus, SENSOR_BUS );
    // Initial local parameters
    priv->address = SENSOR_DEV_ADDRESS;
    priv->streaming_flg = 0;

    // If we want to use sensor sequence loading through source array,
    // data width should correspond to SBUS_MASK_SAMPLE_16_BITS.
    priv->seq_width = 2;

    priv->again_old = 0;

    size_t i;
    // Initialise the gain history to lowest gain possible.
    for ( i = 0; i < SENSOR_ANALOG_GAIN_N; i++ )
        priv->again[i] = gain_tbl[0][1] | ( gain_tbl[0][2] << HCG_BIT );

    priv->integration_time = 4 << SENSOR_INTEGRATION_TIME_PRECISION;
    priv->integration_timeM = ( priv->integration_time * 2 ) << SENSOR_INTEGRATION_TIME_PRECISION;
    priv->integration_timeM2 = ( priv->integration_timeM * 2 ) << SENSOR_INTEGRATION_TIME_PRECISION;
    priv->integration_timeL = ( priv->integration_timeM2 * 2 ) << SENSOR_INTEGRATION_TIME_PRECISION;

    priv->change_flg = 0;

    priv->again_limit = ( LOG2_SENSOR_AGAIN_MAXIMUM << LOG2_GAIN_SHIFT );
    priv->again_limit_min = ( ( 0 << LOG2_GAIN_SHIFT ) | ( 59 << ( LOG2_GAIN_SHIFT - 8 ) ) );
    cfg->sensor_exp_number = SENSOR_EXP_NUMBER;
    cfg->again_log2_max = priv->again_limit;
    cfg->dgain_log2_max = ( LOG2_SENSOR_DGAIN_MAXIMUM > 0 ) ? ( ( ( LOG2_SENSOR_DGAIN_MAXIMUM ) << LOG2_GAIN_SHIFT ) - 1 ) : 0;
    cfg->integration_time_apply_delay = SENSOR_INTEGRATION_TIME_APPLY_DELAY;

    cfg->integration_time_precision = SENSOR_INTEGRATION_TIME_PRECISION;

    cfg->modes_table = supported_modes;
    cfg->modes_num = array_size( supported_modes );
    cfg->again_accuracy = ( 1 << ( LOG2_GAIN_SHIFT - 2 ) );

    cfg->active.width = supported_modes[0].resolution.width;   // Default value needed by some logic.
    cfg->active.height = supported_modes[0].resolution.height; // Default value needed by some logic.

    cfg->h_start = 0;
    cfg->v_start = 0;
    cfg->is_remote = options->is_remote;
    cfg->video_port_id = location;
    cfg->num_channel = supported_modes[0].num_channels;
    cfg->is_reverse_order = 1;
    cfg->data_width = 12;
    cfg->rggb_start = 1;
    cfg->cfa_pattern = 0;
    cfg->shared_vc_clk = 1;

    ctrl->alloc_analog_gain = sensor_alloc_analog_gain;
    ctrl->alloc_digital_gain = sensor_alloc_digital_gain;
    ctrl->alloc_integration_time = sensor_alloc_integration_time;
    ctrl->alloc_white_balance_gains = sensor_alloc_white_balance_gains;
    ctrl->sensor_update = sensor_update;
    ctrl->set_mode = sensor_set_mode;
    ctrl->fps_control = sensor_fps_control;
    ctrl->get_parameters = sensor_get_parameters;
    ctrl->read_sensor_register = read_register;
    ctrl->write_sensor_register = write_register;
    ctrl->start_streaming = start_streaming;
    ctrl->stop_streaming = stop_streaming;
    ctrl->register_frame_callbacks = register_frame_callbacks;
    ctrl->request_next_frame = request_next_frame;
    ctrl->deinit = sensor_deinit;

    sensor_hw_reset_disable( priv );
#if ACAMERA_MIPI_TO_DVP_BOARD
    priv->sensor_iface.mipi_i2c_bus.bus = priv->sbus.bus;
    init_sensor_interface( &priv->sensor_iface );
    reset_sensor_interface( &priv->sensor_iface );
    sensor_hw_reset_enable( priv );
    mipi_init( &priv->sensor_iface, &mipi_settings[0] );
    sensor_hw_reset_disable( priv );
#else
    sensor_hw_reset_enable( priv );
    sensor_hw_reset_disable( priv );
#endif
    uint16_t sensor_rev = acamera_sbus_read_u16( (acamera_sbus_ptr_t)&priv->sbus, SENSOR_REGADDR_REVISION_NUMBER );
    uint16_t sensor_id = sensor_get_id( priv );
    LOG( LOG_INFO, "Sensor AR0231 (id 0x%04x, rev 0x%04x) initialized at position %d.", sensor_id, sensor_rev, location );
}

//*************************************************************************************
