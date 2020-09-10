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

void sensor_fsm_clear( sensor_fsm_t *p_fsm )
{
    p_fsm->sensor_pos = ( 0xff );
    p_fsm->drv_priv = NULL;
    p_fsm->is_remote_stream_reconfig_req = ( 1 );
    p_fsm->is_remote_stream_created = ( 0 );
    p_fsm->p_remote_sensor_frame = NULL;
}

void sensor_request_interrupt( sensor_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask )
{
    system_interrupts_disable();
    p_fsm->irq_mask |= mask;
    system_interrupts_enable();
}

void sensor_fsm_switch_state( sensor_fsm_t *p_fsm, sensor_state_t new_state )
{
    sensor_state_t prev_state = p_fsm->state;
    if ( new_state == prev_state ) return;
    p_fsm->state = new_state;
    if ( new_state == sensor_state_initialized )
    /* switching into sensor_state_initialized */
    {
        sensor_init( p_fsm );
    } else if ( new_state == sensor_state_configured )
    /* switching into sensor_state_configured */
    {

        sensor_config( p_fsm );

    } else if ( new_state == sensor_state_ready )
    /* switching into sensor_state_ready */
    {
        sensor_ready( p_fsm );
    } else if ( new_state == sensor_state_stopped )
    /* switching into sensor_state_stopped */
    {
        sensor_stopped( p_fsm );
    } else if ( new_state == sensor_state_deinit )
    /* switching into sensor_state_deinit */
    {
        sensor_deinit( p_fsm );
    } else if ( new_state == sensor_state_update_hw )
    /* switching into sensor_state_update_hw */
    {
        sensor_update_hw( p_fsm );
    } else if ( new_state == sensor_state_request_next_frame )
    /* switching into sensor_state_request_next_frame */
    {
        sensor_request_next_frame( p_fsm );
    }
}

void sensor_fsm_process_state( sensor_fsm_t *p_fsm )
{
    sensor_state_t state = p_fsm->state;
    for ( ;; ) {
        sensor_state_t prev_state = state;
        switch ( state ) {
        default:
            break;
        case sensor_state_reload_calibration:
            state = sensor_state_ready;
            break;
        case sensor_state_request_next_frame:
            state = sensor_state_ready;
            break;
        case sensor_state_update_hw:
            state = sensor_state_ready;
            break;
        }
        if ( state == prev_state ) {
            break;
        }
        sensor_fsm_switch_state( p_fsm, state );
    }
}

uint8_t sensor_fsm_process_event( sensor_fsm_t *p_fsm, event_id_t event_id )
{
    uint8_t b_event_processed = 0;
    switch ( event_id ) {
    default:
        break;
    case event_id_fsm_config:
        if ( p_fsm->state == sensor_state_initialized ) {
            sensor_fsm_switch_state( p_fsm, sensor_state_configured );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == sensor_state_stopped ) {
            sensor_fsm_switch_state( p_fsm, sensor_state_configured );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_start:
        if ( p_fsm->state == sensor_state_configured ) {
            sensor_fsm_switch_state( p_fsm, sensor_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        if ( p_fsm->state == sensor_state_stopped ) {
            sensor_fsm_switch_state( p_fsm, sensor_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_update_hw:
        if ( p_fsm->state == sensor_state_ready ) {
            sensor_fsm_switch_state( p_fsm, sensor_state_update_hw );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_stop:
        if ( p_fsm->state == sensor_state_ready ) {
            sensor_fsm_switch_state( p_fsm, sensor_state_stopped );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_reload_calibration:
        if ( p_fsm->state == sensor_state_ready ) {
            sensor_fsm_switch_state( p_fsm, sensor_state_reload_calibration );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_isphw_frame_end:
        if ( p_fsm->state == sensor_state_ready ) {
			LOG (LOG_NOTICE, "process event_id_isphw_frame_end event in sensor fsm");
			//TODO: only support single frame by 10000058
            //sensor_fsm_switch_state( p_fsm, sensor_state_request_next_frame );
            b_event_processed = 1;
            break;
        }
        break;
    case event_id_fsm_deinit:
        if ( p_fsm->state == sensor_state_stopped ) {
            sensor_fsm_switch_state( p_fsm, sensor_state_deinit );
            b_event_processed = 1;
            break;
        }
        break;
    }
    if ( b_event_processed ) {
        sensor_fsm_process_state( p_fsm );
    }
    return b_event_processed;
}
