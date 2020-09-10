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

#if !defined( __RAW_FE_FSM_H__ )
#define __RAW_FE_FSM_H__


typedef struct _raw_fe_fsm_t raw_fe_fsm_t;
typedef struct _raw_fe_fsm_t *raw_fe_fsm_ptr_t;
typedef const struct _raw_fe_fsm_t *raw_fe_fsm_const_ptr_t;

enum _raw_fe_state_t {
    raw_fe_state_initialized,
    raw_fe_state_configured,
    raw_fe_state_reload_calibration,
    raw_fe_state_ready,
    raw_fe_state_stopped,
    raw_fe_state_deinit,
    raw_fe_state_update_hw,
    raw_fe_state_invalid
};

typedef enum _raw_fe_state_t raw_fe_state_t;


void raw_fe_init( raw_fe_fsm_ptr_t p_fsm );
void raw_fe_config( raw_fe_fsm_ptr_t p_fsm );
void raw_fe_update_hw( raw_fe_fsm_ptr_t p_fsm );
void raw_fe_reload_calibration( raw_fe_fsm_ptr_t p_fsm );
void raw_fe_deinit( raw_fe_fsm_ptr_t p_fsm );


struct _raw_fe_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    raw_fe_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
};


void raw_fe_fsm_clear( raw_fe_fsm_ptr_t p_fsm );
void raw_fe_fsm_switch_state( raw_fe_fsm_ptr_t p_fsm, raw_fe_state_t state );
void raw_fe_fsm_process_state( raw_fe_fsm_ptr_t p_fsm );
uint8_t raw_fe_fsm_process_event( raw_fe_fsm_ptr_t p_fsm, event_id_t event_id );

void raw_fe_fsm_process_interrupt( raw_fe_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void raw_fe_request_interrupt( raw_fe_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __RAW_FE_FSM_H__ */
