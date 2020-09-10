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

#if !defined( __DEMOSAIC_FSM_H__ )
#define __DEMOSAIC_FSM_H__


typedef struct _demosaic_fsm_t demosaic_fsm_t;
typedef struct _demosaic_fsm_t *demosaic_fsm_ptr_t;
typedef const struct _demosaic_fsm_t *demosaic_fsm_const_ptr_t;

enum _demosaic_state_t {
    demosaic_state_initialized,
    demosaic_state_configured,
    demosaic_state_reload_calibration,
    demosaic_state_ready,
    demosaic_state_stopped,
    demosaic_state_deinit,
    demosaic_state_invalid
};

typedef enum _demosaic_state_t demosaic_state_t;


void demosaic_init( demosaic_fsm_ptr_t p_fsm );
void demosaic_reload_calibration( demosaic_fsm_ptr_t p_fsm );
void demosaic_deinit( demosaic_fsm_ptr_t p_fsm );


struct _demosaic_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    demosaic_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
};


void demosaic_fsm_clear( demosaic_fsm_ptr_t p_fsm );
void demosaic_fsm_switch_state( demosaic_fsm_ptr_t p_fsm, demosaic_state_t state );
void demosaic_fsm_process_state( demosaic_fsm_ptr_t p_fsm );
uint8_t demosaic_fsm_process_event( demosaic_fsm_ptr_t p_fsm, event_id_t event_id );

void demosaic_fsm_process_interrupt( demosaic_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void demosaic_request_interrupt( demosaic_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __DEMOSAIC_FSM_H__ */
