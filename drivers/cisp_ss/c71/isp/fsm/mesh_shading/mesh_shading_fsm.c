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

#include "system_interrupts.h"
#include "acamera_isp_ctx.h"

void mesh_shading_fsm_clear( mesh_shading_fsm_t *p_fsm )
{
}

void mesh_shading_request_interrupt( mesh_shading_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void mesh_shading_fsm_switch_state( mesh_shading_fsm_t *p_fsm, mesh_shading_state_t new_state )
{
    mesh_shading_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == mesh_shading_state_initialized )
    /* switching into mesh_shading_state_initialized */
    {
        mesh_shading_init( p_fsm );
    } else if ( new_state == mesh_shading_state_reload_calibration )
    /* switching into mesh_shading_state_reload_calibration */
    {
        mesh_shading_reload_calibration( p_fsm );
    } else if ( new_state == mesh_shading_state_deinit )
    /* switching into mesh_shading_state_deinit */
    {
        mesh_shading_deinit( p_fsm );
    } else if ( new_state == mesh_shading_state_update_hw )
    /* switching into mesh_shading_state_update_hw */
    {
        mesh_shading_update_hw( p_fsm );
    }
}

void mesh_shading_fsm_process_state( mesh_shading_fsm_t *p_fsm )
{
    mesh_shading_state_t state = p_fsm->state;
    for ( ;; ) {
        mesh_shading_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case mesh_shading_state_reload_calibration:
            state = mesh_shading_state_ready;
            break;
        case mesh_shading_state_update_hw:
            state = mesh_shading_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        mesh_shading_fsm_switch_state( p_fsm, state );
    }
}

uint8_t mesh_shading_fsm_process_event( mesh_shading_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == mesh_shading_state_initialized ) {
            mesh_shading_fsm_switch_state( p_fsm, mesh_shading_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == mesh_shading_state_stopped ) {
            mesh_shading_fsm_switch_state( p_fsm, mesh_shading_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == mesh_shading_state_configured ) {
            mesh_shading_fsm_switch_state( p_fsm, mesh_shading_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == mesh_shading_state_stopped ) {
            mesh_shading_fsm_switch_state( p_fsm, mesh_shading_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_update_hw:
        if ( p_fsm->state == mesh_shading_state_ready ) {
            mesh_shading_fsm_switch_state( p_fsm, mesh_shading_state_update_hw );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == mesh_shading_state_ready ) {
            mesh_shading_fsm_switch_state( p_fsm, mesh_shading_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == mesh_shading_state_ready ) {
            mesh_shading_fsm_switch_state( p_fsm, mesh_shading_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == mesh_shading_state_stopped ) {
            mesh_shading_fsm_switch_state( p_fsm, mesh_shading_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        mesh_shading_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
