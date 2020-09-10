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

void AWB_fsm_clear( AWB_fsm_t *p_fsm )
{
    p_fsm->curr_AWB_ZONES = MAX_AWB_ZONES;
    p_fsm->p_high = 50;
    p_fsm->temperature_detected = 5000;
    p_fsm->light_source_detected = AWB_LIGHT_SOURCE_D50;
    p_fsm->light_source_candidate = AWB_LIGHT_SOURCE_D50;
    p_fsm->detect_light_source_frames_count = 0;
    p_fsm->awb_roi = 65535;
    p_fsm->switch_light_source_detect_frames_quantity = AWB_DLS_SWITCH_LIGHT_SOURCE_DETECT_FRAMES_QUANTITY;
    p_fsm->switch_light_source_change_frames_quantity = AWB_DLS_SWITCH_LIGHT_SOURCE_CHANGE_FRAMES_QUANTITY;
    p_fsm->awb_core = NULL;
}

void AWB_request_interrupt( AWB_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void AWB_fsm_switch_state( AWB_fsm_t *p_fsm, AWB_state_t new_state )
{
    AWB_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == AWB_state_initialized )
    /* switching into AWB_state_initialized */
    {
        awb_init( p_fsm );
    } else if ( new_state == AWB_state_configured )
    /* switching into AWB_state_configured */
    {
        awb_config( p_fsm );
    } else if ( new_state == AWB_state_reload_calibration )
    /* switching into AWB_state_reload_calibration */
    {
        awb_reload_calibration( p_fsm );
    } else if ( new_state == AWB_state_update_algo )
    /* switching into AWB_state_update_algo */
    {
        awb_update_algo( p_fsm );
    } else if ( new_state == AWB_state_update_hw )
    /* switching into AWB_state_update_hw */
    {
        awb_update_hw( p_fsm );
    }
}

void AWB_fsm_process_state( AWB_fsm_t *p_fsm )
{
    AWB_state_t state = p_fsm->state;
    for ( ;; ) {
        AWB_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case AWB_state_reload_calibration:
            state = AWB_state_ready;
            break;
        case AWB_state_update_algo:
            state = AWB_state_ready;
            break;
        case AWB_state_update_hw:
            state = AWB_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        AWB_fsm_switch_state( p_fsm, state );
    }
}

uint8_t AWB_fsm_process_event( AWB_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == AWB_state_initialized ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == AWB_state_stopped ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == AWB_state_configured ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == AWB_state_stopped ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == AWB_state_ready ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_isphw_stats_ready_awb:
        if ( p_fsm->state == AWB_state_ready ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_update_algo );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == AWB_state_ready ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_update_hw:
        if ( p_fsm->state == AWB_state_ready ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_update_hw );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == AWB_state_stopped ) {
            AWB_fsm_switch_state( p_fsm, AWB_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        AWB_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
