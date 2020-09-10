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

#if !defined( __MCFE_FSM_H__ )
#define __MCFE_FSM_H__


typedef struct _mcfe_fsm_t mcfe_fsm_t;
typedef struct _mcfe_fsm_t *mcfe_fsm_ptr_t;
typedef const struct _mcfe_fsm_t *mcfe_fsm_const_ptr_t;

enum _mcfe_state_t {
    mcfe_state_initialized,
    mcfe_state_configured,
    mcfe_state_reload_calibration,
    mcfe_state_ready,
    mcfe_state_stopped,
    mcfe_state_deinit,
    mcfe_state_out_buffer_ready,
    mcfe_state_raw_buffer_ready,
    mcfe_state_invalid
};

typedef enum _mcfe_state_t mcfe_state_t;

#include "module_mcfe_usecase.h"
void mcfe_init( mcfe_fsm_ptr_t p_fsm );
void mcfe_config( mcfe_fsm_ptr_t p_fsm );
void mcfe_start( mcfe_fsm_ptr_t p_fsm );
void mcfe_stop( mcfe_fsm_ptr_t p_fsm );
void mcfe_deinit( mcfe_fsm_ptr_t p_fsm );
void mcfe_raw_buffer_ready( mcfe_fsm_ptr_t p_fsm );
void mcfe_out_buffer_ready( mcfe_fsm_ptr_t p_fsm );

struct _mcfe_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    mcfe_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    module_mcfe_usecase_config_t usecase_cfg;
};


void mcfe_fsm_clear( mcfe_fsm_ptr_t p_fsm );
void mcfe_fsm_switch_state( mcfe_fsm_ptr_t p_fsm, mcfe_state_t state );
void mcfe_fsm_process_state( mcfe_fsm_ptr_t p_fsm );
uint8_t mcfe_fsm_process_event( mcfe_fsm_ptr_t p_fsm, event_id_t event_id );

void mcfe_fsm_process_interrupt( mcfe_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void mcfe_request_interrupt( mcfe_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __MCFE_FSM_H__ */
