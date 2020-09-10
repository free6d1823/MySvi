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

#if !defined( __ML_BIST_FSM_H__ )
#define __ML_BIST_FSM_H__


typedef struct _ml_bist_fsm_t ml_bist_fsm_t;
typedef struct _ml_bist_fsm_t *ml_bist_fsm_ptr_t;
typedef const struct _ml_bist_fsm_t *ml_bist_fsm_const_ptr_t;

enum _ml_bist_state_t {
    ml_bist_state_initialized,
    ml_bist_state_configured,
    ml_bist_state_reload_calibration,
    ml_bist_state_ready,
    ml_bist_state_stopped,
    ml_bist_state_deinit,
    ml_bist_state_invalid
};

typedef enum _ml_bist_state_t ml_bist_state_t;

void ml_bist_init( ml_bist_fsm_ptr_t p_fsm );
void ml_bist_prepare_frame( ml_bist_fsm_ptr_t p_fsm );
void ml_bist_frame_end( ml_bist_fsm_ptr_t p_fsm );

struct _ml_bist_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    ml_bist_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    uint8_t current_test_number;
};


void ml_bist_fsm_clear( ml_bist_fsm_ptr_t p_fsm );
void ml_bist_fsm_switch_state( ml_bist_fsm_ptr_t p_fsm, ml_bist_state_t state );
void ml_bist_fsm_process_state( ml_bist_fsm_ptr_t p_fsm );
uint8_t ml_bist_fsm_process_event( ml_bist_fsm_ptr_t p_fsm, event_id_t event_id );

void ml_bist_fsm_process_interrupt( ml_bist_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void ml_bist_request_interrupt( ml_bist_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __ML_BIST_FSM_H__ */
