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

void AE_fsm_clear( AE_fsm_t *p_fsm )
{
    p_fsm->error_log2 = 0;
    p_fsm->ae_hist_mean = 0;
    p_fsm->exposure_log2 = 0;
    p_fsm->integrator = 0;
    p_fsm->exposure_ratio = 64;
    p_fsm->exposure_ratio_avg = 64;
    p_fsm->ae_roi = 0;
    p_fsm->next_hist_idx = 0x0;
    p_fsm->max_target = 0x0;
    p_fsm->ae_core = NULL;
}

void AE_request_interrupt( AE_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void AE_fsm_switch_state( AE_fsm_t *p_fsm, AE_state_t new_state )
{
    AE_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == AE_state_initialized )
    /* switching into AE_state_initialized */
    {
        ae_init( p_fsm );
    } else if ( new_state == AE_state_configured )
    /* switching into AE_state_configured */
    {
        ae_config( p_fsm );
    } else if ( new_state == AE_state_reload_calibration )
    /* switching into AE_state_reload_calibration */
    {
        ae_reload_calibration( p_fsm );
    } else if ( new_state == AE_state_update_algo )
    /* switching into AE_state_update_algo */
    {
        ae_update_algo( p_fsm );
    }
}

void AE_fsm_process_state( AE_fsm_t *p_fsm )
{
    AE_state_t state = p_fsm->state;
    for ( ;; ) {
        AE_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case AE_state_reload_calibration:
            state = AE_state_ready;
            break;
        case AE_state_update_algo:
            state = AE_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        AE_fsm_switch_state( p_fsm, state );
    }
}

uint8_t AE_fsm_process_event( AE_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == AE_state_initialized ) {
            AE_fsm_switch_state( p_fsm, AE_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == AE_state_stopped ) {
            AE_fsm_switch_state( p_fsm, AE_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == AE_state_configured ) {
            AE_fsm_switch_state( p_fsm, AE_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == AE_state_stopped ) {
            AE_fsm_switch_state( p_fsm, AE_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_isphw_stats_ready_ae:
        if ( p_fsm->state == AE_state_ready ) {
            AE_fsm_switch_state( p_fsm, AE_state_update_algo );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == AE_state_ready ) {
            AE_fsm_switch_state( p_fsm, AE_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == AE_state_ready ) {
            AE_fsm_switch_state( p_fsm, AE_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == AE_state_stopped ) {
            AE_fsm_switch_state( p_fsm, AE_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        AE_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
