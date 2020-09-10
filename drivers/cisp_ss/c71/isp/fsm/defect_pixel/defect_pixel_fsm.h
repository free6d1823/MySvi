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

#if !defined( __DEFECT_PIXEL_FSM_H__ )
#define __DEFECT_PIXEL_FSM_H__


typedef struct _defect_pixel_fsm_t defect_pixel_fsm_t;
typedef struct _defect_pixel_fsm_t *defect_pixel_fsm_ptr_t;
typedef const struct _defect_pixel_fsm_t *defect_pixel_fsm_const_ptr_t;

enum _defect_pixel_state_t {
    defect_pixel_state_initialized,
    defect_pixel_state_configured,
    defect_pixel_state_reload_calibration,
    defect_pixel_state_ready,
    defect_pixel_state_stopped,
    defect_pixel_state_deinit,
    defect_pixel_state_update_hw,
    defect_pixel_state_invalid
};

typedef enum _defect_pixel_state_t defect_pixel_state_t;


void defect_pixel_init( defect_pixel_fsm_ptr_t p_fsm );
void defect_pixel_reload_calibration( defect_pixel_fsm_ptr_t p_fsm );
void defect_pixel_update_hw( defect_pixel_fsm_ptr_t p_fsm );
void defect_pixel_deinit( defect_pixel_fsm_ptr_t p_fsm );

struct _defect_pixel_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    defect_pixel_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    uint8_t frame_counter;
    uint16_t hp_strength;
    uint8_t hp_started;
};


void defect_pixel_fsm_clear( defect_pixel_fsm_ptr_t p_fsm );
void defect_pixel_fsm_switch_state( defect_pixel_fsm_ptr_t p_fsm, defect_pixel_state_t state );
void defect_pixel_fsm_process_state( defect_pixel_fsm_ptr_t p_fsm );
uint8_t defect_pixel_fsm_process_event( defect_pixel_fsm_ptr_t p_fsm, event_id_t event_id );

void defect_pixel_fsm_process_interrupt( defect_pixel_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void defect_pixel_request_interrupt( defect_pixel_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __DEFECT_PIXEL_FSM_H__ */
