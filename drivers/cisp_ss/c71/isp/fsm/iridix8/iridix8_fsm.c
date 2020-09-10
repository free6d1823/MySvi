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

void iridix_fsm_clear( iridix_fsm_t *p_fsm )
{
    p_fsm->dark_enh = 15000;
    p_fsm->strength_target = 0;
    p_fsm->iridix_contrast = 256;
    p_fsm->strength_avg = 0;
    p_fsm->iridix_digital_gain_prev = 256;
    p_fsm->iridix_core = NULL;
}

void iridix_request_interrupt( iridix_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void iridix_fsm_switch_state( iridix_fsm_t *p_fsm, iridix_state_t new_state )
{
    iridix_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == iridix_state_initialized )
    /* switching into iridix_state_initialized */
    {
        iridix_init( p_fsm );
    } else if ( new_state == iridix_state_configured )
    /* switching into iridix_state_configured */
    {
        iridix_config( p_fsm );
    } else if ( new_state == iridix_state_reload_calibration )
    /* switching into iridix_state_reload_calibration */
    {
        iridix_reload_calibration( p_fsm );
    } else if ( new_state == iridix_state_update_algo )
    /* switching into iridix_state_update_algo */
    {
        iridix_update_algo( p_fsm );
    } else if ( new_state == iridix_state_update_hw )
    /* switching into iridix_state_update_hw */
    {
        iridix_update_hw( p_fsm );
    }
}

void iridix_fsm_process_state( iridix_fsm_t *p_fsm )
{
    iridix_state_t state = p_fsm->state;
    for ( ;; ) {
        iridix_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case iridix_state_reload_calibration:
            state = iridix_state_ready;
            break;
        case iridix_state_update_algo:
            state = iridix_state_ready;
            break;
        case iridix_state_update_hw:
            state = iridix_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        iridix_fsm_switch_state( p_fsm, state );
    }
}

uint8_t iridix_fsm_process_event( iridix_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == iridix_state_initialized ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == iridix_state_stopped ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == iridix_state_configured ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == iridix_state_stopped ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_algo_ae_done:
        if ( p_fsm->state == iridix_state_ready ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_update_algo );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == iridix_state_ready ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == iridix_state_ready ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_update_hw:
        if ( p_fsm->state == iridix_state_ready ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_update_hw );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == iridix_state_stopped ) {
            iridix_fsm_switch_state( p_fsm, iridix_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        iridix_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
