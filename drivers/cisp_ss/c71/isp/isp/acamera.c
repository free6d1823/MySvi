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

#include "acamera.h"
#include "system_assert.h"
#include "system_stdlib.h"
#include "acamera_calib_mgr.h"
#include "acamera_command_api.h"
#include "acamera_configuration.h"
#include "acamera_frontend_config.h"
#include "acamera_isp_ctx.h"
#include "acamera_math.h"
#include "revision.h"

#if FW_HAS_CONTROL_CHANNEL
#include "acamera_ctrl_channel.h"
#endif

#if defined( ISP_HAS_MCFE_FSM )
#include "module_mcfe.h"
#endif

#if ACAMERA_ISP_PROFILING
#include "acamera_profiler.h"
#define CHECK_STACK_SIZE_DWORDS 1024
#define CHECK_STACK_SIZE_START 512
#endif


////////////////////////////////////////////////////
// ISP global object

typedef struct _acamera_isp_t {
    // ISP init flag.
    uint32_t isp_initialized;

    // ISP context related.
    acamera_isp_ctx_t fw_ctx[FIRMWARE_CONTEXT_NUMBER]; // Context instances.

    // ISP API params
    isp_params params;

} acamera_isp_t;

static acamera_isp_t g_isp = {0};


////////////////////////////////////////////////////
// Static helper functions

// TODO: to make this static.
void *get_active_ctx_ptr( void )
{
    return &( g_isp.fw_ctx[get_isp_param( ACTIVE_CONTEXT_PARAM )] );
}

////////////////////////////////////////////////////
// ISP API functions

int32_t acamera_init( acamera_settings *settings, uint8_t num_of_contexts, semaphore_t sem )
{
    assert( settings != NULL );

    int32_t result = 0;

    LOG( LOG_INFO, "Control SW Init" );
    LOG( LOG_NOTICE, FIRMWARE_VERSION_STR "(%x)", FIRMWARE_REVISION );

#if ACAMERA_ISP_PROFILING && ACAMERA_ISP_PROFILING_INIT
    acamera_profiler_init();
    acamera_profiler_start( GENERAL_PERF_SECTION );
#endif

#if defined( ISP_HAS_MCFE_FSM )
    module_mcfe_init();
#endif

#if FW_HAS_CONTROL_CHANNEL
    ctrl_channel_init();
#endif

#if !IS_MALI_C71
    acamera_frontend_pipeline_frontend_global_fsm_reset_write( PHY_ADDR_ISP, 1 );
    acamera_frontend_pipeline_frontend_global_fsm_reset_write( PHY_ADDR_ISP, 0 );
#endif

    init_isp_params( &g_isp.params );

    set_isp_param( ACTIVE_CONTEXT_PARAM, 0 );
    override_isp_param( CONTEXT_NUMBER_PARAM, num_of_contexts );

    uint32_t idx = 0;
    for ( idx = 0; idx < get_isp_param( CONTEXT_NUMBER_PARAM ); idx++ ) {
        acamera_isp_ctx_ptr_t p_ictx = ( acamera_isp_ctx_ptr_t ) & ( g_isp.fw_ctx[idx] );
        system_memset( (void *)p_ictx, 0, sizeof( struct _acamera_isp_ctx_t ) );
        // Each context has unique id.
        p_ictx->context_id = idx;
        p_ictx->sync_sem = sem;

        if ( ( p_ictx->calib_mgr_data = acamera_calib_mgr_init( settings[idx].get_calibrations ) ) == NULL ) {
            LOG( LOG_CRIT, "Failed to initialize calibration manager entry for context %d.", (int)idx );
            result = 1;
            break;
        }

        result = acamera_isp_ctx_init( p_ictx, &settings[idx] );
        if ( result != 0 ) {
            LOG( LOG_CRIT, "Failed to initialize the context %d.", (int)idx );
            break;
        }
    }

    if ( result == 0 ) {
        g_isp.isp_initialized = 1;
    } else {
        LOG( LOG_CRIT, "One or more contexts were not initialized properly." );
        g_isp.isp_initialized = 0;
    }

#if defined( ISP_HAS_MCFE_FSM )
    module_mcfe_start();
#endif

#if ACAMERA_ISP_PROFILING && ACAMERA_ISP_PROFILING_INIT
    acamera_profiler_stop( GENERAL_PERF_SECTION, 1 );
    acamera_profiler_report();
#endif

    return result;
}

int32_t acamera_deinit( void )
{
    uint32_t idx;
    acamera_isp_ctx_ptr_t p_ictx;

#if FW_HAS_CONTROL_CHANNEL
    ctrl_channel_deinit();
#endif

#if defined( ISP_HAS_MCFE_FSM )
    module_mcfe_stop();
#endif

    for ( idx = 0; idx < get_isp_param( CONTEXT_NUMBER_PARAM ); idx++ ) {

        p_ictx = ( acamera_isp_ctx_ptr_t ) & ( g_isp.fw_ctx[idx] );

        acamera_isp_ctx_deinit( p_ictx );

        acamera_calib_mgr_deinit( p_ictx->calib_mgr_data );
    }

#if defined( ISP_HAS_MCFE_FSM )
    module_mcfe_deinit();
#endif

    return 0;
}

void acamera_config_ctx( uint8_t ctx_id )
{
    acamera_isp_ctx_fsm_config( &g_isp.fw_ctx[ctx_id] );
}

void acamera_start_ctx( uint8_t ctx_id )
{
    acamera_isp_ctx_fsm_start( &g_isp.fw_ctx[ctx_id] );
}

void acamera_stop_ctx( uint8_t ctx_id )
{
    acamera_isp_ctx_fsm_stop( &g_isp.fw_ctx[ctx_id] );
}

void acamera_deinit_ctx( uint8_t ctx_id )
{
    acamera_isp_ctx_fsm_deinit( &g_isp.fw_ctx[ctx_id] );
}

void acamera_process_interrupt( uint8_t slot, const uint32_t mask )
{
    // Check if slot number within range.
    if ( slot >= FIRMWARE_CONTEXT_NUMBER ) {
        LOG( LOG_ERR, "IRQ slot number is out of range, skipping. IRQ slot: %d, mask: 0x%x, contexts: %d", slot, mask, FIRMWARE_CONTEXT_NUMBER );
        return;
    }

    const acamera_isp_ctx_ptr_t p_ictx = ( acamera_isp_ctx_ptr_t ) & ( g_isp.fw_ctx[slot] );

    if ( p_ictx && mask ) {

        LOG( LOG_DEBUG, "IRQ slot: %d mask: 0x%x", slot, mask );

        acamera_irq_t irq;
        for ( irq = 0; irq < ACAMERA_IRQ_COUNT; ++irq ) {
            if ( BIT( irq ) & mask ) {
                acamera_isp_ctx_process_interrupt( p_ictx, irq );
            }
        }
    }
}

/**
 * @brief      Event processing interface.
 *
 * @return     0 if no events, >0 if queue not empty, -1 if not initialized.
 *
 */
int32_t acamera_process_event( void )
{
#if ACAMERA_ISP_PROFILING
    // Only used in profiling to detect the stack usage.
    uint32_t i = 0;
    static uint32_t max_stack = CHECK_STACK_SIZE_START;
    uint32_t *stack_ptr;
    stack_ptr = &i;
    i = max_stack;
    while ( stack_ptr[-i] != 0xdeedbeef && i < CHECK_STACK_SIZE_DWORDS ) {
        i++;
    }
    if ( i > max_stack ) {
        max_stack = i;
        printf( "Used stack size(Bytes) = %zu\n", max_stack * sizeof( uint32_t ) );
    }
#endif

    int32_t result = 0; // Return 0 if all event queues are empty.
    uint32_t idx = 0;

    if ( g_isp.isp_initialized == 1 ) {
        for ( idx = 0; idx < get_isp_param( CONTEXT_NUMBER_PARAM ); idx++ ) {
            acamera_isp_ctx_ptr_t p_ictx = ( acamera_isp_ctx_ptr_t ) & ( g_isp.fw_ctx[idx] );
            // system_print_buffer( 0 );
            int32_t ret = acamera_isp_ctx_process_event( p_ictx );
            result = result || ret;
        }
    } else {
        result = -1;
        LOG( LOG_CRIT, "Firmware was not initialized properly. Please initialize the firmware before calling acamera_process." );
    }

#if FW_HAS_CONTROL_CHANNEL
    ctrl_channel_process();
#endif

    return result;
}


////////////////////////////////////////////////////
// Context param handlers

// Get parameter value by its id.
// sub_index may be used as a sub index for a custom param handler function.
static uint8_t get_isp_param_ret( uint32_t sub_index, uint32_t param_id, uint32_t *value )
{
    isp_params *params = &( g_isp.params );
    uint8_t ret = SUCCESS;

    // Class check
    if ( param_id & ISP_PARAM_CLASS_MASK ) {
        param_id ^= ISP_PARAM_CLASS_MASK;
    } else {
        return NOT_SUPPORTED;
    }

    // ID range check
    if ( param_id > ISP_PARAM_CLASS_MAX ) {
        return NOT_SUPPORTED;
    }

    // Permission check
    if ( ( params->params[param_id].flags & PARAM_FLAG_READ ) == 0 ) {
        return NOT_PERMITTED;
    }

    if ( ( params->params[param_id].flags & PARAM_FLAG_HANDLER_FUNCTION ) && ( params->params[param_id].param_handler != NULL ) ) {
        ret = params->params[param_id].param_handler( get_active_ctx_ptr(), sub_index, COMMAND_GET, &params->params[param_id].value );
    }

    *value = params->params[param_id].value;

    return ret;
}

// Set parameter value by its id.
static uint8_t set_isp_param_ret( uint32_t param_id, uint32_t value )
{
    isp_params *params = &( g_isp.params );
    uint32_t flags;
    uint8_t ret = SUCCESS;

    // Class check
    if ( param_id & ISP_PARAM_CLASS_MASK ) {
        param_id ^= ISP_PARAM_CLASS_MASK;
    } else {
        return NOT_SUPPORTED;
    }

    // ID range check
    if ( param_id > ISP_PARAM_CLASS_MAX ) {
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
        // Check if new value is in the list.
        for ( i = 1; i <= params->params[param_id].values_list[0].value; i++ ) {
            if ( value == params->params[param_id].values_list[i].value ) {
                list_index = i;
                break;
            }
        }

        if ( !list_index ) {
            return NOT_EXISTS;
        }
    }

    params->params[param_id].value = value;

    // Param flags check
    flags = params->params[param_id].flags;

    if ( flags ) {
        if ( flags & PARAM_FLAG_RECONFIG ) {
            acamera_isp_ctx_ptr_t p_ictx = get_active_ctx_ptr();

            acamera_fsmgr_raise_event( &p_ictx->fsmgr, event_id_fsm_stop );
            acamera_fsmgr_raise_event( &p_ictx->fsmgr, event_id_fsm_config );
            acamera_fsmgr_raise_event( &p_ictx->fsmgr, event_id_fsm_start );
        }

        if ( ( flags & PARAM_FLAG_HANDLER_FUNCTION ) && ( params->params[param_id].param_handler != NULL ) ) {
            uint32_t get_value;
            ret = params->params[param_id].param_handler( get_active_ctx_ptr(), value, COMMAND_SET, &get_value );
        }
    }

    return ret;
}

// Override set (no access mode check, no flags check) parameter value by its id.
static uint8_t override_isp_param_ret( uint32_t param_id, uint32_t value )
{
    isp_params *params = &( g_isp.params );

    // Class check
    if ( param_id & ISP_PARAM_CLASS_MASK ) {
        param_id ^= ISP_PARAM_CLASS_MASK;
    } else {
        return NOT_SUPPORTED;
    }

    // ID range check
    if ( param_id > ISP_PARAM_CLASS_MAX ) {
        return NOT_SUPPORTED;
    }

    params->params[param_id].value = value;

    return SUCCESS;
}

// Get parameter value by its id (no return code provided).
uint32_t get_isp_param( uint32_t param_id )
{
    uint32_t value = 0;

    get_isp_param_ret( 0, param_id, &value );

    return value;
}

// Set parameter value by its id (no return code provided).
void set_isp_param( uint32_t param_id, uint32_t value )
{
    set_isp_param_ret( param_id, value );
}

// Override set (no access mode check, no flags check) parameter value by its id (no return code provided).
void override_isp_param( uint32_t param_id, uint32_t value )
{
    override_isp_param_ret( param_id, value );
}

static uint8_t handle_isp_param( uint32_t param_id, uint8_t direction, uint32_t set_value, uint32_t *get_value )
{
    if ( direction == COMMAND_SET ) {
        return set_isp_param_ret( param_id, set_value );

    } else if ( direction == COMMAND_GET ) {
        return get_isp_param_ret( set_value, param_id, get_value );
    }

    return NOT_SUPPORTED;
}

// Set/Get parameter value by its id and direction.
uint8_t acamera_handle_param( uint32_t param_id, uint8_t direction, uint32_t set_value, uint32_t *get_value )
{
    if ( param_id & ISP_PARAM_CLASS_MASK ) {
        return handle_isp_param( param_id, direction, set_value, get_value );

    } else if ( param_id & CONTEXT_PARAM_CLASS_MASK ) {
        return handle_context_param( get_active_ctx_ptr(), param_id, direction, set_value, get_value );

    } else {
        LOG( LOG_ERR, "Unsupported param id: 0x%x.", param_id );
        return NOT_SUPPORTED;
    }
}
