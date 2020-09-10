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

void noise_reduction_fsm_clear( noise_reduction_fsm_t *p_fsm )
{
    p_fsm->temper_ev_previous_frame = 0;
    p_fsm->temper_diff_avg = 0;
    p_fsm->temper_diff_coeff = 10;
}

void noise_reduction_request_interrupt( noise_reduction_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void noise_reduction_fsm_switch_state( noise_reduction_fsm_t *p_fsm, noise_reduction_state_t new_state )
{
    noise_reduction_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == noise_reduction_state_configured )
    /* switching into noise_reduction_state_configured */
    {
        noise_reduction_config( p_fsm );
    } else if ( new_state == noise_reduction_state_reload_calibration )
    /* switching into noise_reduction_state_reload_calibration */
    {
        noise_reduction_reload_calibration( p_fsm );
    } else if ( new_state == noise_reduction_state_deinit )
    /* switching into noise_reduction_state_deinit */
    {
        noise_reduction_deinit( p_fsm );
    } else if ( new_state == noise_reduction_state_update_hw )
    /* switching into noise_reduction_state_update_hw */
    {
        noise_reduction_update_hw( p_fsm );
    }
}

void noise_reduction_fsm_process_state( noise_reduction_fsm_t *p_fsm )
{
    noise_reduction_state_t state = p_fsm->state;
    for ( ;; ) {
        noise_reduction_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case noise_reduction_state_reload_calibration:
            state = noise_reduction_state_ready;
            break;
        case noise_reduction_state_update_hw:
            state = noise_reduction_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        noise_reduction_fsm_switch_state( p_fsm, state );
    }
}

uint8_t noise_reduction_fsm_process_event( noise_reduction_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == noise_reduction_state_initialized ) {
            noise_reduction_fsm_switch_state( p_fsm, noise_reduction_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == noise_reduction_state_stopped ) {
            noise_reduction_fsm_switch_state( p_fsm, noise_reduction_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == noise_reduction_state_configured ) {
            noise_reduction_fsm_switch_state( p_fsm, noise_reduction_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == noise_reduction_state_stopped ) {
            noise_reduction_fsm_switch_state( p_fsm, noise_reduction_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_update_hw:
        if ( p_fsm->state == noise_reduction_state_ready ) {
            noise_reduction_fsm_switch_state( p_fsm, noise_reduction_state_update_hw );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == noise_reduction_state_ready ) {
            noise_reduction_fsm_switch_state( p_fsm, noise_reduction_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == noise_reduction_state_ready ) {
            noise_reduction_fsm_switch_state( p_fsm, noise_reduction_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == noise_reduction_state_stopped ) {
            noise_reduction_fsm_switch_state( p_fsm, noise_reduction_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        noise_reduction_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
