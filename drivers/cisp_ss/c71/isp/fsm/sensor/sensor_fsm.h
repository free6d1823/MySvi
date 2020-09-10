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

#if !defined( __SENSOR_FSM_H__ )
#define __SENSOR_FSM_H__


typedef struct _sensor_fsm_t sensor_fsm_t;
typedef struct _sensor_fsm_t *sensor_fsm_ptr_t;
typedef const struct _sensor_fsm_t *sensor_fsm_const_ptr_t;

enum _sensor_state_t {
    sensor_state_initialized,
    sensor_state_configured,
    sensor_state_reload_calibration,
    sensor_state_ready,
    sensor_state_stopped,
    sensor_state_deinit,
    sensor_state_update_hw,
    sensor_state_request_next_frame,
    sensor_state_invalid
};

typedef enum _sensor_state_t sensor_state_t;

#include "acamera_fsmgr_general_router.h"


void sensor_init( sensor_fsm_ptr_t p_fsm );
void sensor_deinit( sensor_fsm_ptr_t p_fsm );
void sensor_config( sensor_fsm_ptr_t p_fsm );
void sensor_ready( sensor_fsm_ptr_t p_fsm );
void sensor_stopped( sensor_fsm_ptr_t p_fsm );
void sensor_update_hw( sensor_fsm_ptr_t p_fsm );
void sensor_get_general_sensor_info( sensor_fsm_ptr_t p_fsm, acamera_cmd_sensor_info *p_sensor_info );
uint32_t sensor_get_lines_second( sensor_fsm_ptr_t p_fsm );
int remote_sensor_put_frame_callback_handler( void *owner, void *frame );
int remote_sensor_get_frame_callback_handler( void *owner, void **frame );
int remote_sensor_release_frame_callback_handler( void *owner, void *frame );
void sensor_request_next_frame( sensor_fsm_ptr_t p_fsm );

struct _sensor_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    sensor_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    sensor_control_t ctrl;
    uint8_t sensor_pos;
    void *drv_priv;
    acamera_cmd_sensor_info general_sensor_info;
    uint32_t black_level;
    uint8_t is_remote_stream_reconfig_req;
    uint8_t is_remote_stream_created;
    void *p_remote_sensor_frame;
};


void sensor_fsm_clear( sensor_fsm_ptr_t p_fsm );
void sensor_fsm_switch_state( sensor_fsm_ptr_t p_fsm, sensor_state_t state );
void sensor_fsm_process_state( sensor_fsm_ptr_t p_fsm );
uint8_t sensor_fsm_process_event( sensor_fsm_ptr_t p_fsm, event_id_t event_id );

void sensor_fsm_process_interrupt( sensor_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void sensor_request_interrupt( sensor_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __SENSOR_FSM_H__ */
