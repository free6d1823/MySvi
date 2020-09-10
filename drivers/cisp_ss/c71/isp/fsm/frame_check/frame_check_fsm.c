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

void frame_check_fsm_clear( frame_check_fsm_t *p_fsm )
{
    p_fsm->manual_trigger = 0;
    p_fsm->field_mode = 0;
    p_fsm->active_width = 1280;
    p_fsm->active_height = 960;
    p_fsm->hblank_min = 8;
    p_fsm->hblank_max = 65535;
    p_fsm->vblank_min = 1;
    p_fsm->vblank_max = 4294967295;
}

void frame_check_request_interrupt( frame_check_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void frame_check_fsm_switch_state( frame_check_fsm_t *p_fsm, frame_check_state_t new_state )
{
    frame_check_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == frame_check_state_initialized )
    /* switching into frame_check_state_initialized */
    {
        frame_check_init( p_fsm );
    } else if ( new_state == frame_check_state_configured )
    /* switching into frame_check_state_configured */
    {
        frame_check_config( p_fsm );
    }
}

void frame_check_fsm_process_state( frame_check_fsm_t *p_fsm )
{
    frame_check_state_t state = p_fsm->state;
    for ( ;; ) {
        frame_check_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case frame_check_state_reload_calibration:
            state = frame_check_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        frame_check_fsm_switch_state( p_fsm, state );
    }
}

uint8_t frame_check_fsm_process_event( frame_check_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == frame_check_state_initialized ) {
            frame_check_fsm_switch_state( p_fsm, frame_check_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == frame_check_state_stopped ) {
            frame_check_fsm_switch_state( p_fsm, frame_check_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == frame_check_state_configured ) {
            frame_check_fsm_switch_state( p_fsm, frame_check_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == frame_check_state_stopped ) {
            frame_check_fsm_switch_state( p_fsm, frame_check_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == frame_check_state_ready ) {
            frame_check_fsm_switch_state( p_fsm, frame_check_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == frame_check_state_ready ) {
            frame_check_fsm_switch_state( p_fsm, frame_check_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == frame_check_state_stopped ) {
            frame_check_fsm_switch_state( p_fsm, frame_check_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        frame_check_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
