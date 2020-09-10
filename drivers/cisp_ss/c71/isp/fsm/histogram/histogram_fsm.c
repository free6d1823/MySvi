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

void histogram_fsm_clear( histogram_fsm_t *p_fsm )
{
    p_fsm->hist_ready_mask = 0;
    p_fsm->hist_is_on_sqrt = 0;
}

void histogram_request_interrupt( histogram_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void histogram_fsm_switch_state( histogram_fsm_t *p_fsm, histogram_state_t new_state )
{
    histogram_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == histogram_state_initialized )
    /* switching into histogram_state_initialized */
    {
        histogram_init( p_fsm );
    } else if ( new_state == histogram_state_configured )
    /* switching into histogram_state_configured */
    {
        histogram_config( p_fsm );
    } else if ( new_state == histogram_state_reload_calibration )
    /* switching into histogram_state_reload_calibration */
    {
        histogram_reload_calibration( p_fsm );
    } else if ( new_state == histogram_state_update_hw )
    /* switching into histogram_state_update_hw */
    {
        histogram_update_hw( p_fsm );
    }
}

void histogram_fsm_process_state( histogram_fsm_t *p_fsm )
{
    histogram_state_t state = p_fsm->state;
    for ( ;; ) {
        histogram_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case histogram_state_reload_calibration:
            state = histogram_state_ready;
            break;
        case histogram_state_update_hw:
            state = histogram_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        histogram_fsm_switch_state( p_fsm, state );
    }
}

uint8_t histogram_fsm_process_event( histogram_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == histogram_state_initialized ) {
            histogram_fsm_switch_state( p_fsm, histogram_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == histogram_state_stopped ) {
            histogram_fsm_switch_state( p_fsm, histogram_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == histogram_state_configured ) {
            histogram_fsm_switch_state( p_fsm, histogram_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == histogram_state_stopped ) {
            histogram_fsm_switch_state( p_fsm, histogram_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == histogram_state_ready ) {
            histogram_fsm_switch_state( p_fsm, histogram_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == histogram_state_ready ) {
            histogram_fsm_switch_state( p_fsm, histogram_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_update_hw:
        if ( p_fsm->state == histogram_state_ready ) {
            histogram_fsm_switch_state( p_fsm, histogram_state_update_hw );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == histogram_state_stopped ) {
            histogram_fsm_switch_state( p_fsm, histogram_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        histogram_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
