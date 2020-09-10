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

void radial_shading_fsm_clear( radial_shading_fsm_t *p_fsm )
{
}

void radial_shading_request_interrupt( radial_shading_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void radial_shading_fsm_switch_state( radial_shading_fsm_t *p_fsm, radial_shading_state_t new_state )
{
    radial_shading_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == radial_shading_state_initialized )
    /* switching into radial_shading_state_initialized */
    {
        radial_shading_init( p_fsm );
    } else if ( new_state == radial_shading_state_reload_calibration )
    /* switching into radial_shading_state_reload_calibration */
    {
        radial_shading_reload_calibration( p_fsm );
    } else if ( new_state == radial_shading_state_deinit )
    /* switching into radial_shading_state_deinit */
    {
        radial_shading_deinit( p_fsm );
    }
}

void radial_shading_fsm_process_state( radial_shading_fsm_t *p_fsm )
{
    radial_shading_state_t state = p_fsm->state;
    for ( ;; ) {
        radial_shading_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case radial_shading_state_reload_calibration:
            state = radial_shading_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        radial_shading_fsm_switch_state( p_fsm, state );
    }
}

uint8_t radial_shading_fsm_process_event( radial_shading_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == radial_shading_state_initialized ) {
            radial_shading_fsm_switch_state( p_fsm, radial_shading_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == radial_shading_state_stopped ) {
            radial_shading_fsm_switch_state( p_fsm, radial_shading_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == radial_shading_state_configured ) {
            radial_shading_fsm_switch_state( p_fsm, radial_shading_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == radial_shading_state_stopped ) {
            radial_shading_fsm_switch_state( p_fsm, radial_shading_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == radial_shading_state_ready ) {
            radial_shading_fsm_switch_state( p_fsm, radial_shading_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == radial_shading_state_ready ) {
            radial_shading_fsm_switch_state( p_fsm, radial_shading_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == radial_shading_state_stopped ) {
            radial_shading_fsm_switch_state( p_fsm, radial_shading_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        radial_shading_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
