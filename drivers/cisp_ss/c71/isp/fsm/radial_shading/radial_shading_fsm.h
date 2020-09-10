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

#if !defined( __RADIAL_SHADING_FSM_H__ )
#define __RADIAL_SHADING_FSM_H__


typedef struct _radial_shading_fsm_t radial_shading_fsm_t;
typedef struct _radial_shading_fsm_t *radial_shading_fsm_ptr_t;
typedef const struct _radial_shading_fsm_t *radial_shading_fsm_const_ptr_t;

enum _radial_shading_state_t {
    radial_shading_state_initialized,
    radial_shading_state_configured,
    radial_shading_state_reload_calibration,
    radial_shading_state_ready,
    radial_shading_state_stopped,
    radial_shading_state_deinit,
    radial_shading_state_invalid
};

typedef enum _radial_shading_state_t radial_shading_state_t;


void radial_shading_init( radial_shading_fsm_ptr_t p_fsm );
void radial_shading_reload_calibration( radial_shading_fsm_ptr_t p_fsm );
void radial_shading_deinit( radial_shading_fsm_ptr_t p_fsm );


struct _radial_shading_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    radial_shading_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    uint16_t hist_shading_lut[17];
};


void radial_shading_fsm_clear( radial_shading_fsm_ptr_t p_fsm );
void radial_shading_fsm_switch_state( radial_shading_fsm_ptr_t p_fsm, radial_shading_state_t state );
void radial_shading_fsm_process_state( radial_shading_fsm_ptr_t p_fsm );
uint8_t radial_shading_fsm_process_event( radial_shading_fsm_ptr_t p_fsm, event_id_t event_id );

void radial_shading_fsm_process_interrupt( radial_shading_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void radial_shading_request_interrupt( radial_shading_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __RADIAL_SHADING_FSM_H__ */
