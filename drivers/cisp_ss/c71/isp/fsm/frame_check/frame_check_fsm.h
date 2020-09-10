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

#if !defined( __FRAME_CHECK_FSM_H__ )
#define __FRAME_CHECK_FSM_H__


typedef struct _frame_check_fsm_t frame_check_fsm_t;
typedef struct _frame_check_fsm_t *frame_check_fsm_ptr_t;
typedef const struct _frame_check_fsm_t *frame_check_fsm_const_ptr_t;

enum _frame_check_state_t {
    frame_check_state_initialized,
    frame_check_state_configured,
    frame_check_state_reload_calibration,
    frame_check_state_ready,
    frame_check_state_stopped,
    frame_check_state_deinit,
    frame_check_state_invalid
};

typedef enum _frame_check_state_t frame_check_state_t;


void frame_check_init( frame_check_fsm_ptr_t p_fsm );
void frame_check_config( frame_check_fsm_ptr_t p_fsm );


struct _frame_check_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    frame_check_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    int16_t manual_trigger;
    uint8_t field_mode;
    uint32_t active_width;
    uint32_t active_height;
    uint32_t hblank_min;
    uint32_t hblank_max;
    uint32_t vblank_min;
    uint32_t vblank_max;
};


void frame_check_fsm_clear( frame_check_fsm_ptr_t p_fsm );
void frame_check_fsm_switch_state( frame_check_fsm_ptr_t p_fsm, frame_check_state_t state );
void frame_check_fsm_process_state( frame_check_fsm_ptr_t p_fsm );
uint8_t frame_check_fsm_process_event( frame_check_fsm_ptr_t p_fsm, event_id_t event_id );

void frame_check_fsm_process_interrupt( frame_check_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void frame_check_request_interrupt( frame_check_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __FRAME_CHECK_FSM_H__ */
