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

#include "acamera_isp_ctx.h"
#include "system_assert.h"
#include "system_stdlib.h"
#include "system_types.h"
#include "acamera_command_api.h"
#include "acamera_configuration.h"
#include "acamera_interrupt_numbers.h"
#include "acamera_logger.h"

#if ACAMERA_ISP_PROFILING
#include "acamera_profiler.h"
#endif

#if DEBUG_FRAME_COUNT
#include "system_timer.h" // Used to get system ticks for counters.
#endif

#if IS_MALI_C71
#include "acamera_faults_cfg_config.h" // @TODO move this.

// @TODO: eventually remove this
// Workaround for r1a0 and r1b0 builds
#ifndef ACAMERA_FAULTS_CFG_FAULTS_CFG_STATUS_IC_SCONFIG_PCLK2_TOP_APB_FAULT_S_ADDRESS_RANGE_DEFAULT
#define acamera_faults_cfg_faults_cfg_status_ic_sconfig_pclk2_top_apb_fault_s_address_range_write acamera_faults_cfg_faults_cfg_status_ic_sconfig_pclk2_top_fault_s_address_range_write
#endif

#endif


////////////////////////////////////////////////////
// Static functions

// Raise_event functions.
static void raise_context_event( acamera_isp_ctx_ptr_t p_ictx, event_id_t event_id, int event_flags )
{
    acamera_event_queue_push( &p_ictx->fsmgr.event_queue, (int)( event_id ), event_flags );

    system_semaphore_raise( p_ictx->sync_sem );
}


////////////////////////////////////////////////////
// isp_ctx API functions

int32_t acamera_isp_ctx_init( acamera_isp_ctx_ptr_t p_ictx, acamera_settings *settings )
{
    int32_t result = 0;

#if ACAMERA_ISP_PROFILING
// Profiler init
#if ACAMERA_ISP_PROFILING_INIT
    p_ictx->binit_profiler = 0;
    p_ictx->breport_profiler = 0;
#else
    p_ictx->binit_profiler = 1;
    p_ictx->breport_profiler = 1;
#endif                             // ACAMERA_ISP_PROFILING_INIT
    p_ictx->start_profiling = 500; // Start when gframe == 500
    p_ictx->stop_profiling = 1000; // Stop  when gframe == 1000
#endif                             // ACAMERA_ISP_PROFILING

    LOG( LOG_INFO, "* -------------------------------------------" );
    LOG( LOG_INFO, "* Start initializing context #%02d ------------", p_ictx->context_id );

    // Copy settings.
    system_memcpy( (void *)&p_ictx->settings, (void *)settings, sizeof( acamera_settings ) );

    // Initialize context API parameters.
    // Should be done before FSM manager init as FSM may initialize default param values.
    init_context_params( &p_ictx->params );

    // Initialize FSM manager.
    p_ictx->fsmgr.p_ictx = p_ictx;
    acamera_event_queue_init( &( p_ictx->fsmgr.event_queue ), p_ictx->fsmgr.event_queue_data, ACAMERA_EVENT_QUEUE_SIZE );
    acamera_fsmgr_init( &p_ictx->fsmgr );

    // TODO: temporal solution, should be moved to upper layer.
    raise_context_event( p_ictx, event_id_fsm_config, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
    raise_context_event( p_ictx, event_id_fsm_start, EVENT_QUEUE_EVENT_FLAG_FILTER | EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );

    return result;
}

void acamera_isp_ctx_deinit( acamera_isp_ctx_ptr_t p_ictx )
{
    p_ictx->fsmgr.p_ictx = p_ictx;

    // Deinitialize FSM manager.
    acamera_event_queue_free( &( p_ictx->fsmgr.event_queue ) );
}

void acamera_isp_ctx_fsm_config( acamera_isp_ctx_ptr_t p_ictx )
{
    // Dispatch config event to FSM manager.
    raise_context_event( p_ictx, event_id_fsm_config, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
}

void acamera_isp_ctx_fsm_start( acamera_isp_ctx_ptr_t p_ictx )
{
    // Dispatch start event to FSM manager.
    raise_context_event( p_ictx, event_id_fsm_start, EVENT_QUEUE_EVENT_FLAG_FILTER | EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
}

void acamera_isp_ctx_fsm_stop( acamera_isp_ctx_ptr_t p_ictx )
{
    // Dispatch stop event to FSM manager.
    raise_context_event( p_ictx, event_id_fsm_stop, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
}

void acamera_isp_ctx_fsm_deinit( acamera_isp_ctx_ptr_t p_ictx )
{
    // Dispatch stop event to FSM manager.
    raise_context_event( p_ictx, event_id_fsm_deinit, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
}

#if 0
#define DISCON_TRACE( fmt, ... ) LOG( LOG_ERR, fmt, ##__VA_ARGS__ )
#else
#define DISCON_TRACE( fmt, ... )
#endif

void acamera_isp_ctx_process_interrupt( acamera_isp_ctx_ptr_t p_ictx, uint8_t event )
{
	LOG( LOG_NOTICE, "%s, event = %d", __FUNCTION__, event);
    uint8_t is_event_stats = 0;
    uint8_t is_fw_freeze = get_context_param( p_ictx, SYSTEM_FREEZE_FIRMWARE_PARAM );

    if ( event == ACAMERA_IRQ_FE_FRAME_START ) {
        // Front End Frame Start
        p_ictx->fe_frame_counter++;
    }

    if ( event == ACAMERA_IRQ_BE_FRAME_START ) {
        // Back End Frame Start
        p_ictx->be_frame_counter++;
        if ( p_ictx->be_frame_counter != p_ictx->fe_frame_counter ) {
            DISCON_TRACE( "FW[%u] FE->BE discontinuity, possible frame drop, FE %u BE %u", p_ictx->context_id, p_ictx->fe_frame_counter, p_ictx->be_frame_counter );
            if ( p_ictx->fe_frame_counter < 20 )
                p_ictx->be_frame_counter = p_ictx->fe_frame_counter;
        }
    }

    if ( event == ACAMERA_IRQ_AE_STATS ) {
        // Front End AE Stats
        p_ictx->ae_stats_counter++;
        if ( p_ictx->ae_stats_counter != p_ictx->fe_frame_counter ) {
            DISCON_TRACE( "FW[%u] AE_STATS discontinuity!!!, FS %u AE %u", p_ictx->context_id, p_ictx->fe_frame_counter, p_ictx->ae_stats_counter );
            if ( p_ictx->fe_frame_counter < 20 )
                p_ictx->ae_stats_counter = p_ictx->fe_frame_counter;
        }
        is_event_stats = 1;
    }

    if ( event == ACAMERA_IRQ_AWB_STATS ) {
        // Back End AWB Stats
        p_ictx->awb_stats_counter++;
        if ( p_ictx->awb_stats_counter != p_ictx->be_frame_counter ) {
            DISCON_TRACE( "FW[%u] AWB_STATS discontinuity!!!, BE_FS %u AWB %u", p_ictx->context_id, p_ictx->be_frame_counter, p_ictx->awb_stats_counter );
            if ( p_ictx->be_frame_counter < 20 )
                p_ictx->awb_stats_counter = p_ictx->be_frame_counter;
        }
        is_event_stats = 1;
    }

    if ( event == ACAMERA_IRQ_ANTIFOG_HIST ) {
        // ANTIFOG_HIST is not implemented yet.
        is_event_stats = 1;
    }

    if ( event == ACAMERA_IRQ_FE_FRAME_END ) {
        // Front End Frame End
        p_ictx->dfe_frame_counter++;
        if ( p_ictx->fe_frame_counter != p_ictx->dfe_frame_counter ) {
            DISCON_TRACE( "FW[%u] FRAME_START discontinuity!!!, FS %u DFE %u", p_ictx->context_id, p_ictx->fe_frame_counter, p_ictx->dfe_frame_counter );
            if ( p_ictx->fe_frame_counter < 20 )
                p_ictx->dfe_frame_counter = p_ictx->fe_frame_counter;
        }
    }

    if ( event == ACAMERA_IRQ_BE_FRAME_END ) {
        // Back End Frame End
        p_ictx->frame_end_counter++;

#if IS_MALI_C71
        // TODO: to move this to somewhere-else.
        if ( p_ictx->be_frame_counter == 2 ) {
            acamera_faults_cfg_faults_cfg_status_ic_sconfig_vclk_top_fault_s_address_range_write( PHY_ADDR_ISP, 1 );
            acamera_faults_cfg_faults_cfg_status_ic_sconfig_pclk2_top_apb_fault_s_address_range_write( PHY_ADDR_ISP, 1 );
            acamera_faults_cfg_faults_cfg_status_ic_sconfig_frontend_top_fault_s_address_range_write( PHY_ADDR_ISP, 1 );
        }
#endif

        if ( p_ictx->frame_end_counter != p_ictx->be_frame_counter ) {
            DISCON_TRACE( "FW[%u] FRAME_END discontinuity!!!, BE_FS %u FE %u", p_ictx->context_id, p_ictx->be_frame_counter, p_ictx->frame_end_counter );
            if ( p_ictx->be_frame_counter < 20 )
                p_ictx->frame_end_counter = p_ictx->be_frame_counter;
        }

        // Updating all hw blocks when firmware is not freezed.
        // Currently on frame end, but can be on frame start if system has enough processing power.
        if ( is_fw_freeze == 0 )
            raise_context_event( p_ictx, event_id_fsm_update_hw, 0 );

#if defined( ISP_HAS_MCFE_FSM )
        raise_context_event( p_ictx, event_id_isphw_frame_end, 0 );
#endif

#if ACAMERA_ISP_PROFILING
        acamera_profiler_new_frame();
#endif
    }

	printf("is_fw_freeze = %d\n", is_fw_freeze);
    // Process FSM interrupts.
    if ( ( is_fw_freeze == 0 ) || ( is_event_stats == 0 ) ) {
        // Block statistics irq when firmware is frozen to block 3a to run.
        acamera_fsmgr_process_interrupt( &p_ictx->fsmgr, (uint8_t)event );
    }
}

int32_t acamera_isp_ctx_process_event( acamera_isp_ctx_ptr_t p_ictx )
{
#if ACAMERA_ISP_PROFILING
    if ( ( p_ictx->fe_frame_counter >= p_ictx->start_profiling ) && ( !p_ictx->binit_profiler ) ) {
        acamera_profiler_init();
        p_ictx->binit_profiler = 1;
    }
#endif

    // Process events.
    acamera_fsmgr_process_events( &p_ictx->fsmgr, ISP_PROCESS_NUM_EVENTS_QUANT );

#if ACAMERA_ISP_PROFILING
    if ( ( p_ictx->fe_frame_counter >= p_ictx->stop_profiling ) && ( !p_ictx->breport_profiler ) ) {
        acamera_profiler_report();
        p_ictx->breport_profiler = 1;
    }
#endif

    // Returns 0 if queue is empty.
    // return acamera_event_queue_is_empty( &(( &p_ictx->fsmgr )->event_queue) );
    return !acamera_event_queue_is_empty( &( p_ictx->fsmgr.event_queue ) );
}


////////////////////////////////////////////////////
// FSM helper functions

/**
 * @brief      Loads custom settings if they exist in calibrations for this context.
 *
 * @param[in]  p_ictx  The ictx
 */
void acamera_isp_ctx_load_custom_settings( acamera_isp_ctx_ptr_t p_ictx )
{
    assert( p_ictx );
    if ( calib_mgr_lut_exists( p_ictx->calib_mgr_data, CALIBRATION_CUSTOM_SETTINGS ) ) {
        LOG( LOG_NOTICE, "Loading custom settings CTX[%d]", p_ictx->context_id );
        const uint32_t *lut = calib_mgr_u32_lut_get( p_ictx->calib_mgr_data,
                                                     CALIBRATION_CUSTOM_SETTINGS );
        for ( ;; ) {
            const uint32_t offset = *lut++;
            const uint32_t value = *lut++;
            const uint32_t mask = *lut++;
            const uint32_t length = *lut++;
            const uint32_t address = PHY_ADDR_ISP + offset;

            /* It may be possible to have a register at offset 0x0000_0000,
             * but a mask of 0x0000_0000 does not do anything so a zero offset
             * with a non zero write is a legitimate operation where as a zero
             * offset with a zero mask is a terminating sequence. */
            if ( !( offset | mask ) ) break;

            switch ( length ) {
            case sizeof( uint8_t ):
                system_isp_write_8( address,
                                    ( system_isp_read_8( address ) & ~mask ) |
                                        ( value & mask ) );
                break;
            case sizeof( uint16_t ):
                system_isp_write_16( address,
                                     ( system_isp_read_16( address ) & ~mask ) |
                                         ( value & mask ) );
                break;
            case sizeof( uint32_t ):
            /* By default assume 32bit register. */
            default:
                system_isp_write_32( address,
                                     ( system_isp_read_32( address ) & ~mask ) |
                                         ( value & mask ) );
                break;
            }
        }
    }
}

int32_t acamera_isp_ctx_load_calibrations( acamera_isp_ctx_ptr_t p_ictx, uint32_t wdr_mode )
{
    int32_t result = 0;

    if ( p_ictx->calib_mgr_data != NULL ) {
        if ( ( result = acamera_calib_mgr_update( p_ictx->calib_mgr_data, wdr_mode ) ) != 0 ) {
            LOG( LOG_CRIT, "Failed to update calibration set. Fatal error." );
        }
    } else {
        LOG( LOG_CRIT, "Calibration manager entry is not initialized. Failed to get calibrations." );
        result = -1;
    }

    return result;
}

#if DEBUG_FRAME_COUNT
static void count_algo_done( acamera_fsmgr_t *p_fsmgr )
{
    static size_t last_stamps[FIRMWARE_CONTEXT_NUMBER] = {0};
    static size_t counters[FIRMWARE_CONTEXT_NUMBER] = {0};
    const size_t fps = 30;
    const uint32_t context_id = ACAMERA_FSMGR2ICTX_PTR( p_fsmgr )->context_id;

    if ( context_id >= FIRMWARE_CONTEXT_NUMBER ) return;

    if ( ( ++counters[context_id] % fps ) == 0 ) {
        const size_t this_stamp = system_timer_timestamp();
        const size_t elapsed_stamp = this_stamp - last_stamps[context_id];
        const size_t elapsed_ms = ( elapsed_stamp * 1000 ) / system_timer_frequency();
        const size_t current_fps = ( fps * system_timer_frequency() ) / elapsed_stamp;
        const size_t average_frame_time = elapsed_ms / fps;

        last_stamps[context_id] = this_stamp;

        LOG( LOG_NOTICE, "Algo done, context_id %d, count %zu, ftime %zums, fps: %zu.",
             context_id,
             counters[context_id],
             average_frame_time,
             current_fps );
    }
}
#endif


/* Note: acamera_fsmgr_raise_event() is defined in acamera_fsmgr.h (generated one).
         This creates dependancy between isp_ctx and fsm-mgr.
         We are keeping this unavoidable evil to make raise_context_event static. */
void acamera_fsmgr_raise_event( acamera_fsmgr_t *p_fsmgr, event_id_t event_id )
{
#if DEBUG_FRAME_COUNT
    if ( event_id == event_id_algo_ae_done ) {
        count_algo_done( p_fsmgr );
    }
#endif

    raise_context_event( p_fsmgr->p_ictx, event_id, 0 );
}


////////////////////////////////////////////////////
// Context param handlers

// Functions to handle register access requests by context param handler.
static uint8_t handle_register_get_value( acamera_isp_ctx_ptr_t p_ictx, uint32_t *value );
static uint8_t handle_register_set_value( acamera_isp_ctx_ptr_t p_ictx, uint32_t value );

// Get parameter value by its id.
// sub_index may be used as a sub index for a custom param handler function.
static uint8_t get_context_param_ret( acamera_isp_ctx_ptr_t p_ictx, uint32_t sub_index, uint32_t param_id, uint32_t *value )
{
    context_params *params = &( p_ictx->params );
    uint32_t flags;
    uint8_t ret = SUCCESS;

    // Class check
    if ( param_id & CONTEXT_PARAM_CLASS_MASK ) {
        param_id ^= CONTEXT_PARAM_CLASS_MASK;
    } else {
        return NOT_SUPPORTED;
    }

    // ID range check
    if ( param_id > CONTEXT_PARAM_CLASS_MAX ) {
        return NOT_SUPPORTED;
    }

    flags = params->params[param_id].flags;

    // Permission check
    if ( ( flags & PARAM_FLAG_READ ) == 0 ) {
        return NOT_PERMITTED;
    }

    if ( flags ) {
        if ( flags & PARAM_FLAG_REGISTER_REQUEST ) {
            ret = handle_register_get_value( p_ictx, &params->params[param_id].value );
        }

        if ( ( flags & PARAM_FLAG_HANDLER_FUNCTION ) && ( params->params[param_id].param_handler != NULL ) ) {
            ret = params->params[param_id].param_handler( p_ictx, sub_index, COMMAND_GET, &params->params[param_id].value );
        }
    }

    *value = params->params[param_id].value;

    return ret;
}

// Set parameter value by its id.
static uint8_t set_context_param_ret( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id, uint32_t value )
{
    context_params *params = &( p_ictx->params );
    uint32_t flags;
    uint8_t ret = SUCCESS;

    // Class check
    if ( param_id & CONTEXT_PARAM_CLASS_MASK ) {
        param_id ^= CONTEXT_PARAM_CLASS_MASK;
    } else {
        return NOT_SUPPORTED;
    }

    // ID range check
    if ( param_id > CONTEXT_PARAM_CLASS_MAX ) {
        return NOT_SUPPORTED;
    }

    // Permission check
    if ( ( params->params[param_id].flags & PARAM_FLAG_WRITE ) == 0 ) {
        return NOT_PERMITTED;
    }

    // If values list is empty do a simple range check.
    if ( params->params[param_id].values_list == NULL ) {
        if ( ( value > params->params[param_id].max ) || ( value < params->params[param_id].min ) ) {
            return NOT_EXISTS;
        }
    } else {
        uint32_t i, list_index = 0;
        // Check if new value is in the list
        for ( i = 1; i <= params->params[param_id].values_list[0].value; i++ ) {
            if ( value == params->params[param_id].values_list[i].value ) {
                list_index = i;
                break;
            }
        }

        if ( !list_index ) {
            return NOT_EXISTS;
        } else {
            // Check if value has specific flags.
            flags = params->params[param_id].values_list[list_index].flags;

            if ( flags ) {
                if ( flags & PARAM_FLAG_RECONFIG_ON_LIST_VALUE ) {
                    raise_context_event( p_ictx, event_id_fsm_stop, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
                    raise_context_event( p_ictx, event_id_fsm_config, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
                    raise_context_event( p_ictx, event_id_fsm_start, EVENT_QUEUE_EVENT_FLAG_FILTER | EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
                }
            }
        }
    }

    params->params[param_id].value = value;

    // Param flags check
    flags = params->params[param_id].flags;

    if ( flags ) {
        if ( flags & PARAM_FLAG_RECONFIG ) {
            raise_context_event( p_ictx, event_id_fsm_stop, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
            raise_context_event( p_ictx, event_id_fsm_config, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
            raise_context_event( p_ictx, event_id_fsm_start, EVENT_QUEUE_EVENT_FLAG_FILTER | EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
        } else if ( ( flags & PARAM_FLAG_RECONFIG_ON_TRUE_DEFAULT_RESET ) && value ) {
            raise_context_event( p_ictx, event_id_fsm_stop, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
            raise_context_event( p_ictx, event_id_fsm_config, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
            raise_context_event( p_ictx, event_id_fsm_start, EVENT_QUEUE_EVENT_FLAG_FILTER | EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
            params->params[param_id].value = params->params[param_id].default_value;
        }

        if ( flags & PARAM_FLAG_REGISTER_REQUEST ) {
            ret = handle_register_set_value( p_ictx, value );
        }

        if ( ( flags & PARAM_FLAG_STOP_ON_FALSE ) && !value ) {
            raise_context_event( p_ictx, event_id_fsm_stop, EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
        } else if ( ( flags & PARAM_FLAG_START_ON_TRUE ) && value ) {
            raise_context_event( p_ictx, event_id_fsm_start, EVENT_QUEUE_EVENT_FLAG_FILTER | EVENT_QUEUE_EVENT_FLAG_FSM_TYPE );
        }

        if ( ( flags & PARAM_FLAG_HANDLER_FUNCTION ) && ( params->params[param_id].param_handler != NULL ) ) {
            uint32_t get_value;
            ret = params->params[param_id].param_handler( p_ictx, value, COMMAND_SET, &get_value );
        }
    }

    return ret;
}

// Override set (no access mode check, no flags check) parameter value by its id.
static uint8_t override_context_param_ret( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id, uint32_t value )
{
    context_params *params = &( p_ictx->params );

    // Class check
    if ( param_id & CONTEXT_PARAM_CLASS_MASK ) {
        param_id ^= CONTEXT_PARAM_CLASS_MASK;
    } else {
        return NOT_SUPPORTED;
    }

    // ID range check
    if ( param_id > CONTEXT_PARAM_CLASS_MAX ) {
        return NOT_SUPPORTED;
    }

    params->params[param_id].value = value;

    return SUCCESS;
}

// Get parameter value by its id (no return code provided).
uint32_t get_context_param( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id )
{
    uint32_t value = 0;

    get_context_param_ret( p_ictx, 0, param_id, &value );

    return value;
}

// Set parameter value by its id (no return code provided).
void set_context_param( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id, uint32_t value )
{
    set_context_param_ret( p_ictx, param_id, value );
}

// Override set (no access mode check, no flags check) parameter value by its id (no return code provided).
void override_context_param( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id, uint32_t value )
{
    override_context_param_ret( p_ictx, param_id, value );
}

uint8_t handle_context_param( acamera_isp_ctx_ptr_t p_ictx, uint32_t param_id, uint8_t direction, uint32_t set_value, uint32_t *get_value )
{
    if ( direction == COMMAND_SET ) {
        return set_context_param_ret( p_ictx, param_id, set_value );

    } else if ( direction == COMMAND_GET ) {
        return get_context_param_ret( p_ictx, set_value, param_id, get_value );
    }

    return NOT_SUPPORTED;
}

static uint8_t handle_register_get_value( acamera_isp_ctx_ptr_t p_ictx, uint32_t *value )
{
    acamera_sbus_t *s_bus = &p_ictx->fsmgr.control_fsm.isp_sbus;
    const uint32_t isp_base = p_ictx->settings.isp_base;

    const uint32_t reg_addr = get_context_param( p_ictx, REGISTERS_ADDRESS_ID_PARAM );
    const uint32_t reg_size = get_context_param( p_ictx, REGISTERS_SIZE_ID_PARAM );
    const uint32_t reg_src = get_context_param( p_ictx, REGISTERS_SOURCE_ID_PARAM );

    switch ( reg_src ) {
#if defined( ISP_HAS_SENSOR_FSM )
    case SENSOR:
        *value = p_ictx->fsmgr.sensor_fsm.ctrl.read_sensor_register( p_ictx->fsmgr.sensor_fsm.drv_priv, reg_addr );
        return SUCCESS;
#endif
    case ISP:
        switch ( reg_size ) {
        case 8:
            *value = acamera_sbus_read_u8( s_bus, reg_addr + isp_base );
            break;
        case 16:
            *value = acamera_sbus_read_u16( s_bus, reg_addr + isp_base );
            break;
        case 32:
            *value = acamera_sbus_read_u32( s_bus, reg_addr + isp_base );
            break;
        default:
            return NOT_EXISTS;
        }

        return SUCCESS;

    default:
        return NOT_EXISTS;
    }

    return SUCCESS;
}

static uint8_t handle_register_set_value( acamera_isp_ctx_ptr_t p_ictx, uint32_t value )
{
    acamera_sbus_t *s_bus = &p_ictx->fsmgr.control_fsm.isp_sbus;
    const uint32_t isp_base = p_ictx->settings.isp_base;

    const uint32_t reg_addr = get_context_param( p_ictx, REGISTERS_ADDRESS_ID_PARAM );
    const uint32_t reg_size = get_context_param( p_ictx, REGISTERS_SIZE_ID_PARAM );
    const uint32_t reg_src = get_context_param( p_ictx, REGISTERS_SOURCE_ID_PARAM );

    switch ( reg_src ) {
#if defined( ISP_HAS_SENSOR_FSM )
    case SENSOR:
        p_ictx->fsmgr.sensor_fsm.ctrl.write_sensor_register( p_ictx->fsmgr.sensor_fsm.drv_priv, reg_addr, value );
        return SUCCESS;
#endif
    case ISP:
        switch ( reg_size ) {
        case 8:
            acamera_sbus_write_u8( s_bus, reg_addr + isp_base, (uint8_t)value );
            break;
        case 16:
            acamera_sbus_write_u16( s_bus, reg_addr + isp_base, (uint16_t)value );
            break;
        case 32:
            acamera_sbus_write_u32( s_bus, reg_addr + isp_base, value );
            break;
        default:
            return NOT_EXISTS;
        }

        return SUCCESS;

    default:
        return NOT_EXISTS;
    }

    return SUCCESS;
}
