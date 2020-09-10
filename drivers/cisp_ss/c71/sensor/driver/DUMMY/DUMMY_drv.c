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

//-------------------------------------------------------------------------------------
// STRUCTURE:
//  VARIABLE SECTION:
//      CONTROLS - Dependence from preprocessor
//      DATA     - Modulation
//      RESET    - Reset function
//      MIPI     - MIPI settings
//      FLASH    - Flash support
//  CONSTANT SECTION
//      DRIVER
//-------------------------------------------------------------------------------------
#include "system_stdlib.h"
#include "system_types.h"
#include "acamera_command_api.h"
#include "acamera_logger.h"
#include "acamera_math.h"
#include "sensor_api.h"
#include "DUMMY_config.h"
#include "remote_sensor_common.h"

static sensor_mode_t supported_modes[] =
    {
        {.wdr_mode = WDR_MODE_LINEAR,
         .resolution.width = 1920,
         .resolution.height = 1080,
         .exposures = 1,
         .num_channels = 1},
};

typedef struct _sensor_private_t {
    sensor_param_t param;
    uint16_t integration_time;
    int32_t again;
    int32_t dgain;
	remote_sensor_frame_data_t remote_frame_data;
} sensor_private_t;
static sensor_private_t priv_array[FIRMWARE_CONTEXT_NUMBER];

//--------------------DATA-------------------------------------------------------------
//--------------------RESET------------------------------------------------------------
static void sensor_hw_reset_enable( void )
{
    return;
}

static void sensor_hw_reset_disable( void )
{
    return;
}

//--------------------FLASH------------------------------------------------------------

static int32_t sensor_alloc_analog_gain( void *sensor_priv, int32_t gain )
{
    sensor_private_t *priv = sensor_priv;

    priv->again = gain;
    return gain;
}

static int32_t sensor_alloc_digital_gain( void *sensor_priv, int32_t gain )
{
    sensor_private_t *priv = sensor_priv;

    priv->dgain = gain;
    return gain;
}

static void sensor_alloc_integration_time( void *sensor_priv, integration_times_t *int_times )
{
    sensor_private_t *priv = sensor_priv;
    uint32_t *int_time = &int_times->int_time;

    priv->integration_time = *int_time;
}

static void sensor_alloc_white_balance_gains( void *sensor_priv, int32_t gain[4] )
{
    (void)sensor_priv; //unusued
    (void)gain;        //unusued
}

static void sensor_update( void *sensor_priv )
{
}

static void sensor_set_mode( void *sensor_priv, uint8_t mode )
{
    sensor_private_t *priv = sensor_priv;
	remote_sensor_frame_data_t *remote_frame_data = &priv->remote_frame_data;
    sensor_param_t *cfg = &priv->param;
    //system_memset( cfg, 0, sizeof( sensor_param_t ) );

    cfg->active.width = SENSOR_IMAGE_WIDTH;
    cfg->active.height = SENSOR_IMAGE_HEIGHT;
    cfg->total.width = 1920;//SENSOR_TOTAL_WIDTH;
    cfg->total.height = 1080;//SENSOR_TOTAL_HEIGHT;
    cfg->integration_time_min = SENSOR_MIN_INTEGRATION_TIME;
    cfg->integration_time_max = SENSOR_MAX_INTEGRATION_TIME;
    cfg->integration_time_limit = SENSOR_MAX_INTEGRATION_TIME_LIMIT;
    cfg->preset_mode = mode;
    cfg->lines_per_second = 0;

    cfg->sensor_exp_number = supported_modes[mode].exposures;
    cfg->num_channel = supported_modes[mode].num_channels;
    LOG( LOG_DEBUG, "Exposures number: %d", cfg->sensor_exp_number );
    LOG( LOG_DEBUG, "Channels number: %d", cfg->num_channel );
    if ( remote_sensor_reinit( cfg, remote_frame_data, 1 ) ) {
        LOG( LOG_ERR, "Failed to initialize remote sensor." );
    }
}

static uint16_t sensor_get_id( void *sensor_priv )
{
    return 0xFFFF;
}

static const sensor_param_t *sensor_get_parameters( void *sensor_priv )
{
    sensor_private_t *priv = sensor_priv;
	LOG( LOG_INFO, "%s: priv = 0x%2x.\n", __FUNCTION__, priv);
    return (const sensor_param_t *)&priv->param;
}

static uint8_t sensor_fps_control( void *sensor_priv, uint8_t fps )
{
    // This sensor does not support FPS switching.
    return 0;
}

static uint32_t read_register( void *sensor_priv, uint32_t address )
{
    return 0;
}

static void write_register( void *sensor_priv, uint32_t address, uint32_t data )
{
}
static void stop_streaming( void *sensor_priv ) {}

static void start_streaming( void *sensor_priv );

static void request_next_frame( void *sensor_priv );

static void register_frame_callbacks( void *sensor_priv, const sensor_remote_callbacks_t *callbacks );

static void sensor_deinit( void *sensor_priv )
{
}

#define array_size( a ) \
    ( sizeof( a ) / sizeof( a[0] ) )
//--------------------Initialization------------------------------------------------------------
void sensor_init_dummy( void **priv_ptr, uint8_t location, sensor_control_t *ctrl, const sensor_options_t *const options )
{
    sensor_private_t *priv = *priv_ptr = priv_array + location;
    sensor_param_t *cfg = &priv->param;
    remote_sensor_frame_data_t *remote_frame_data = &priv->remote_frame_data;
    system_memset( cfg, 0, sizeof( *cfg ) );
    system_memset( remote_frame_data, 0, sizeof( remote_sensor_frame_data_t ) );

    cfg->sensor_exp_number = SENSOR_EXP_NUMBER;
    cfg->again_log2_max = LOG2_SENSOR_AGAIN_MAXIMUM << LOG2_GAIN_SHIFT;
    cfg->dgain_log2_max = LOG2_SENSOR_DGAIN_MAXIMUM << LOG2_GAIN_SHIFT;
    cfg->integration_time_apply_delay = SENSOR_INTEGRATION_TIME_APPLY_DELAY;
    cfg->isp_exposure_channel_delay = 0;
    cfg->modes_table = supported_modes;
    cfg->modes_num = array_size( supported_modes );
    cfg->again_accuracy = ( 1 << ( LOG2_GAIN_SHIFT - 2 ) );
    cfg->h_start = 0;
    cfg->v_start = 0;
    cfg->video_port_id = location;
    cfg->num_channel = supported_modes[0].num_channels;//1;
    cfg->is_reverse_order = 0;
    cfg->is_remote = 1;
    cfg->data_width = 16;//12;
    cfg->rggb_start = 1;
    cfg->cfa_pattern = 0;
    cfg->shared_vc_clk = 0;

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

    // Reset sensor during initialization
    sensor_hw_reset_enable();
    sensor_hw_reset_disable();

    LOG( LOG_INFO, "Sensor DPattern (id 0x%04x) initialized at position %d.", sensor_get_id( priv ), location );
}

//*************************************************************************************
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

static void start_streaming( void *sensor_priv )
{
    uint16_t cur_reg;
    sensor_private_t *priv = sensor_priv;
    sensor_param_t *cfg = &priv->param;
    remote_sensor_frame_data_t *remote_frame_data = &priv->remote_frame_data;
    //acamera_sbus_ptr_t p_sbus = &priv->sbus;

    //priv->streaming_flg = 1;
    //cur_reg = acamera_sbus_read_u16( p_sbus, SENSOR_REGADDR_RESET_REGISTER );
    //cur_reg |= ( 0x4 );
    //acamera_sbus_write_u16( p_sbus, SENSOR_REGADDR_RESET_REGISTER, cur_reg );

    remote_sensor_start_streaming( cfg, remote_frame_data );
}
