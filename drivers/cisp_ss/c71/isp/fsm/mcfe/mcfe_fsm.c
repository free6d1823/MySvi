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

void mcfe_fsm_clear( mcfe_fsm_t *p_fsm )
{
}

void mcfe_request_interrupt( mcfe_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void mcfe_fsm_switch_state( mcfe_fsm_t *p_fsm, mcfe_state_t new_state )
{
    mcfe_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == mcfe_state_initialized )
    /* switching into mcfe_state_initialized */
    {
        mcfe_init( p_fsm );
    } else if ( new_state == mcfe_state_configured )
    /* switching into mcfe_state_configured */
    {
        mcfe_config( p_fsm );
    } else if ( new_state == mcfe_state_ready )
    /* switching into mcfe_state_ready */
    {
        mcfe_start( p_fsm );
    } else if ( new_state == mcfe_state_stopped )
    /* switching into mcfe_state_stopped */
    {
        mcfe_stop( p_fsm );
    } else if ( new_state == mcfe_state_deinit )
    /* switching into mcfe_state_deinit */
    {
        mcfe_deinit( p_fsm );
    } else if ( new_state == mcfe_state_out_buffer_ready )
    /* switching into mcfe_state_out_buffer_ready */
    {
        mcfe_out_buffer_ready( p_fsm );
    } else if ( new_state == mcfe_state_raw_buffer_ready )
    /* switching into mcfe_state_raw_buffer_ready */
    {
        mcfe_raw_buffer_ready( p_fsm );
    }
}

void mcfe_fsm_process_state( mcfe_fsm_t *p_fsm )
{
    mcfe_state_t state = p_fsm->state;
    for ( ;; ) {
        mcfe_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case mcfe_state_out_buffer_ready:
            state = mcfe_state_ready;
            break;
        case mcfe_state_raw_buffer_ready:
            state = mcfe_state_ready;
            break;
        case mcfe_state_reload_calibration:
            state = mcfe_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        mcfe_fsm_switch_state( p_fsm, state );
    }
}

uint8_t mcfe_fsm_process_event( mcfe_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == mcfe_state_initialized ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == mcfe_state_stopped ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == mcfe_state_configured ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == mcfe_state_stopped ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_isphw_frame_end_fe:
        if ( p_fsm->state == mcfe_state_ready ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_raw_buffer_ready );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_isphw_frame_end:
        if ( p_fsm->state == mcfe_state_ready ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_out_buffer_ready );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == mcfe_state_ready ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == mcfe_state_ready ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == mcfe_state_stopped ) {
            mcfe_fsm_switch_state( p_fsm, mcfe_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        mcfe_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
