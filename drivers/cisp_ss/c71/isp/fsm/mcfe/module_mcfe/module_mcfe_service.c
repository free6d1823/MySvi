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
 * headers
 **************************************************/

#include "module_mcfe_service.h"
#include "module_mcfe_common.h"
#include "module_mcfe_hwif.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_MCFE

/**************************************************
 * general functions
 **************************************************/
int module_mcfe_scheduler_init( void );
extern int module_mcfe_input_init( void );
extern int module_mcfe_slot_init( void );
extern int module_mcfe_bufset_init( void );

int module_mcfe_service_init( void )
{
    int rc = MCFE_ERR_NONE;

    // initialize all mcfe service sub-modules
    mcfe_hwif_scheduler_mode_write( 1 );

    module_mcfe_input_init();
    module_mcfe_slot_init();
    module_mcfe_scheduler_init();
    module_mcfe_bufset_init();

    return rc;
}


/**************************************************
 * scheduler control interface
 **************************************************/
static module_mcfe_sched_mode_t sched_mode = MODULE_MCFE_SCHED_MODE_MAX;

int module_mcfe_scheduler_init( void )
{
    mcfe_hwif_scheduler_mode_write( 0 );
    sched_mode = MODULE_MCFE_SCHED_MODE_MAX;

    return MCFE_ERR_NONE;
}

int module_mcfe_scheduler_set_mode( module_mcfe_sched_mode_t mode )
{
    int rc = MCFE_ERR_NONE;

    // error handler
    if ( mcfe_hwif_scheduler_mode_read() != 0 ) {
        LOG( LOG_ERR, "Error, can't config while scheduler is running." );
        return MCFE_ERR_BUSY;
    } else if ( mode >= MODULE_MCFE_SCHED_MODE_MAX ) {
        LOG( LOG_ERR, "Error, invalid scheduler mode." );
        return MCFE_ERR_INV_PARM;
    }

    // configure scheduler with parameter
    sched_mode = mode;

    return rc;
}

int module_mcfe_scheduler_start( void )
{
    int rc = MCFE_ERR_NONE;

    // error handler
    if ( mcfe_hwif_scheduler_mode_read() != 0 ) {
        LOG( LOG_ERR, "Error, scheduler is already running." );
        return MCFE_ERR_BUSY;
    } else if ( sched_mode >= MODULE_MCFE_SCHED_MODE_MAX ) {
        LOG( LOG_ERR, "Error, scheduler is not configured yet." );
        return MCFE_ERR_INV_PARM;
    }

    // start scheduler
    mcfe_hwif_scheduler_mode_write( sched_mode );

    return rc;
}

int module_mcfe_scheduler_stop( void )
{
    int rc = MCFE_ERR_NONE;

    // error handler
    if ( mcfe_hwif_scheduler_mode_read() == 0 ) {
        LOG( LOG_ERR, "Error, scheduler is not running." );
        return MCFE_ERR_NOT_RUN;
    }

    // stop scheduler
    mcfe_hwif_scheduler_mode_write( 0 );

    return rc;
}
