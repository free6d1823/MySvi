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

#if !defined( __CAC_FSM_H__ )
#define __CAC_FSM_H__


typedef struct _cac_fsm_t cac_fsm_t;
typedef struct _cac_fsm_t *cac_fsm_ptr_t;
typedef const struct _cac_fsm_t *cac_fsm_const_ptr_t;

enum _cac_state_t {
    cac_state_initialized,
    cac_state_configured,
    cac_state_reload_calibration,
    cac_state_ready,
    cac_state_stopped,
    cac_state_deinit,
    cac_state_invalid
};

typedef enum _cac_state_t cac_state_t;


void cac_init( cac_fsm_ptr_t p_fsm );
void cac_config( cac_fsm_ptr_t p_fsm );
void cac_reload_calibration( cac_fsm_ptr_t p_fsm );
void cac_deinit( cac_fsm_ptr_t p_fsm );


struct _cac_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    cac_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
};


void cac_fsm_clear( cac_fsm_ptr_t p_fsm );
void cac_fsm_switch_state( cac_fsm_ptr_t p_fsm, cac_state_t state );
void cac_fsm_process_state( cac_fsm_ptr_t p_fsm );
uint8_t cac_fsm_process_event( cac_fsm_ptr_t p_fsm, event_id_t event_id );

void cac_fsm_process_interrupt( cac_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void cac_request_interrupt( cac_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __CAC_FSM_H__ */
