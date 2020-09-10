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

#if !defined( __SHARPENING_FSM_H__ )
#define __SHARPENING_FSM_H__


typedef struct _sharpening_fsm_t sharpening_fsm_t;
typedef struct _sharpening_fsm_t *sharpening_fsm_ptr_t;
typedef const struct _sharpening_fsm_t *sharpening_fsm_const_ptr_t;

enum _sharpening_state_t {
    sharpening_state_initialized,
    sharpening_state_configured,
    sharpening_state_reload_calibration,
    sharpening_state_ready,
    sharpening_state_stopped,
    sharpening_state_deinit,
    sharpening_state_update_hw,
    sharpening_state_invalid
};

typedef enum _sharpening_state_t sharpening_state_t;


void sharpening_update_hw( sharpening_fsm_ptr_t p_fsm );

struct _sharpening_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    sharpening_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    uint16_t sharpening_mult;
};


void sharpening_fsm_clear( sharpening_fsm_ptr_t p_fsm );
void sharpening_fsm_switch_state( sharpening_fsm_ptr_t p_fsm, sharpening_state_t state );
void sharpening_fsm_process_state( sharpening_fsm_ptr_t p_fsm );
uint8_t sharpening_fsm_process_event( sharpening_fsm_ptr_t p_fsm, event_id_t event_id );

void sharpening_fsm_process_interrupt( sharpening_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void sharpening_request_interrupt( sharpening_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __SHARPENING_FSM_H__ */
