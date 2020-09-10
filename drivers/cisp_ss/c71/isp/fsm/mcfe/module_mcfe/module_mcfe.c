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

/**************************************************
 * Headers
 **************************************************/
#include "module_mcfe.h"
#include "system_stdlib.h"
#include "module_mcfe_common.h"
#include "module_mcfe_service.h"

/**************************************************
 * Static globals
 **************************************************/
static module_mcfe_config_t mcfe_module_config = {0};

// External functions
int module_mcfe_get_slot_id_for_input( int input, int first_only )
{
    // Error handler
    if ( mcfe_module_config.initialized == 0 ) {
        return -1;
    } else if ( ( input < 0 ) || ( input >= MODULE_MCFE_INPUT_PORT_MAX ) ) {
        return -1;
    }

    if ( first_only ) {
        int i, slot_id;
        if ( ( slot_id = mcfe_module_config.video_input_table[input] ) != -1 ) {
            for ( i = 0; i < input; i++ ) {
                if ( mcfe_module_config.video_input_table[i] == slot_id ) {
                    return -1;
                }
            }
        }
    }

    return mcfe_module_config.video_input_table[input];
}

int module_mcfe_get_input_for_slot_id( int slot_id )
{
    int input;
    int retval = -1;

    // Error handler
    if ( mcfe_module_config.initialized == 0 ) {
        return retval;
    }

    for ( input = 0; input < MODULE_MCFE_INPUT_PORT_MAX; input++ ) {
        if ( mcfe_module_config.video_input_table[input] == slot_id ) {
            retval = input;
        }
    }

    return retval;
}

int module_mcfe_get_free_inputs_for_slot_id( int slot_id )
{
    int i, retval = 0;

    // Error handler
    if ( mcfe_module_config.initialized == 0 ) {
        return retval;
    }

    // Look for slots on all inputs
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        if ( ( mcfe_module_config.video_input_table[i] == -1 ) || ( mcfe_module_config.video_input_table[i] == slot_id ) ) {
            retval++;
        }
    }

    return retval;
}

/**************************************************
 * Init, deinit
 **************************************************/
int module_mcfe_init( void )
{
    int rc = MCFE_ERR_NONE;

    // Check if MCFE is already initialized.
    if ( mcfe_module_config.initialized != 0 ) {
        return rc;
    }

    LOG( LOG_INFO, "Initializing module_mcfe : E" );

    // Initialize MCFE instance.
    system_memset( &mcfe_module_config, 0x0, sizeof( mcfe_module_config ) );
    mcfe_module_config.initialized = 1;
    mcfe_module_config.running = 0;

    // initialize service layer
    module_mcfe_service_init();

    LOG( LOG_INFO, "Initializing module_mcfe : X" );

    return rc;
}

int module_mcfe_deinit( void )
{
    int rc = MCFE_ERR_NONE;

    LOG( LOG_INFO, "De-initializing module_mcfe : E" );

    // Error handler
    if ( mcfe_module_config.initialized == 0 ) {
        LOG( LOG_ERR, "Error, MCFE module is not initialized." );
        return MCFE_ERR_NOT_INIT;
    } else if ( mcfe_module_config.running != 0 ) {
        LOG( LOG_ERR, "Error, MCFE module is still running." );
        return MCFE_ERR_NOT_RUN;
    }

    // Initialize service layer with defaults
    module_mcfe_service_init();

    // Deinitialize MCFE instance.
    mcfe_module_config.initialized = 0;

    LOG( LOG_INFO, "De-initializing module_mcfe : X" );

    return rc;
}

int module_mcfe_start( void )
{
    int rc = MCFE_ERR_NONE;

    LOG( LOG_INFO, "Starting module_mcfe : E" );

    // Error handler
    if ( mcfe_module_config.initialized == 0 ) {
        LOG( LOG_ERR, "Error, MCFE module is not initialized." );
        return MCFE_ERR_NOT_INIT;
    } else if ( mcfe_module_config.running != 0 ) {
        LOG( LOG_ERR, "Error, MCFE module is already running." );
        return MCFE_ERR_NOT_RUN;
    }

    // Update mcfe scheduler mode
    rc = module_mcfe_scheduler_set_mode( MODULE_MCFE_SCHED_MODE_MANUAL );
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, failed to set scheduler mode." );
        return rc;
    }

    rc = module_mcfe_scheduler_start();
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, failed to start scheduler." );
        return rc;
    }

    mcfe_module_config.running = 1;
    LOG( LOG_INFO, "Starting module_mcfe : X" );

    return rc;
}

int module_mcfe_stop( void )
{
    int rc = MCFE_ERR_NONE;

    LOG( LOG_INFO, "Stopping module_mcfe : E" );

    // Error handler
    if ( mcfe_module_config.initialized == 0 ) {
        LOG( LOG_ERR, "Error, MCFE module is not initialized." );
        return MCFE_ERR_NOT_INIT;
    } else if ( mcfe_module_config.running == 0 ) {
        LOG( LOG_ERR, "Error, MCFE module is not running." );
        return MCFE_ERR_NOT_RUN;
    }

    module_mcfe_scheduler_stop();
    rc = module_mcfe_check_scheduler_status( 0, 20, 1000 );
    if ( rc != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Error, failed to stop MCFE scheduler." );
        return rc;
    }

    // Update MCFE status.
    mcfe_module_config.running = 0;

    LOG( LOG_INFO, "Stopping module_mcfe : X" );

    return rc;
}

int module_mcfe_update_inputs( void )
{
    int i;

    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        mcfe_slot_id_t slot_id;

        // search slot id with input id
        int rc = module_mcfe_slot_get_slot_id_with_input_id( &slot_id, i );
        if ( rc == MCFE_ERR_NO_RES ) {
            mcfe_module_config.video_input_table[i] = -1;
            continue;
        }

        if ( rc != MCFE_ERR_NONE ) {
            LOG( LOG_ERR, "Error, failed to get slot id for input %d (rc = %d)\n", i, rc );
            return rc;
        }

        // update table
        mcfe_module_config.video_input_table[i] = slot_id;
    }

    return MCFE_ERR_NONE;
}