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

void output_formatter_fsm_clear( output_formatter_fsm_t *p_fsm )
{
}

void output_formatter_request_interrupt( output_formatter_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void output_formatter_fsm_switch_state( output_formatter_fsm_t *p_fsm, output_formatter_state_t new_state )
{
    output_formatter_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == output_formatter_state_initialized )
    /* switching into output_formatter_state_initialized */
    {
        output_formatter_init( p_fsm );
    } else if ( new_state == output_formatter_state_configured )
    /* switching into output_formatter_state_configured */
    {
        output_formatter_config( p_fsm );
    } else if ( new_state == output_formatter_state_reload_calibration )
    /* switching into output_formatter_state_reload_calibration */
    {
        output_formatter_reload_calibration( p_fsm );
    } else if ( new_state == output_formatter_state_deinit )
    /* switching into output_formatter_state_deinit */
    {
        output_formatter_deinit( p_fsm );
    }
}

void output_formatter_fsm_process_state( output_formatter_fsm_t *p_fsm )
{
    output_formatter_state_t state = p_fsm->state;
    for ( ;; ) {
        output_formatter_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case output_formatter_state_reload_calibration:
            state = output_formatter_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        output_formatter_fsm_switch_state( p_fsm, state );
    }
}

uint8_t output_formatter_fsm_process_event( output_formatter_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == output_formatter_state_initialized ) {
            output_formatter_fsm_switch_state( p_fsm, output_formatter_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == output_formatter_state_stopped ) {
            output_formatter_fsm_switch_state( p_fsm, output_formatter_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == output_formatter_state_configured ) {
            output_formatter_fsm_switch_state( p_fsm, output_formatter_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == output_formatter_state_stopped ) {
            output_formatter_fsm_switch_state( p_fsm, output_formatter_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == output_formatter_state_ready ) {
            output_formatter_fsm_switch_state( p_fsm, output_formatter_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == output_formatter_state_ready ) {
            output_formatter_fsm_switch_state( p_fsm, output_formatter_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == output_formatter_state_stopped ) {
            output_formatter_fsm_switch_state( p_fsm, output_formatter_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        output_formatter_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
