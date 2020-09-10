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

#if !defined( __NOISE_PROFILE_FSM_H__ )
#define __NOISE_PROFILE_FSM_H__


typedef struct _noise_profile_fsm_t noise_profile_fsm_t;
typedef struct _noise_profile_fsm_t *noise_profile_fsm_ptr_t;
typedef const struct _noise_profile_fsm_t *noise_profile_fsm_const_ptr_t;

enum _noise_profile_state_t {
    noise_profile_state_initialized,
    noise_profile_state_configured,
    noise_profile_state_reload_calibration,
    noise_profile_state_ready,
    noise_profile_state_stopped,
    noise_profile_state_deinit,
    noise_profile_state_invalid
};

typedef enum _noise_profile_state_t noise_profile_state_t;


void noise_profile_init( noise_profile_fsm_ptr_t p_fsm );
void noise_profile_reload_calibration( noise_profile_fsm_ptr_t p_fsm );
void noise_profile_deinit( noise_profile_fsm_ptr_t p_fsm );


struct _noise_profile_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    noise_profile_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
};


void noise_profile_fsm_clear( noise_profile_fsm_ptr_t p_fsm );
void noise_profile_fsm_switch_state( noise_profile_fsm_ptr_t p_fsm, noise_profile_state_t state );
void noise_profile_fsm_process_state( noise_profile_fsm_ptr_t p_fsm );
uint8_t noise_profile_fsm_process_event( noise_profile_fsm_ptr_t p_fsm, event_id_t event_id );

void noise_profile_fsm_process_interrupt( noise_profile_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void noise_profile_request_interrupt( noise_profile_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __NOISE_PROFILE_FSM_H__ */
