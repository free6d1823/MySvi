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

#if !defined( __CONTROL_FSM_H__ )
#define __CONTROL_FSM_H__


typedef struct _control_fsm_t control_fsm_t;
typedef struct _control_fsm_t *control_fsm_ptr_t;
typedef const struct _control_fsm_t *control_fsm_const_ptr_t;

enum _control_state_t {
    control_state_initialized,
    control_state_configured,
    control_state_reload_calibration,
    control_state_ready,
    control_state_stopped,
    control_state_deinit,
    control_state_update_hw,
    control_state_invalid
};

typedef enum _control_state_t control_state_t;

#include "acamera_configuration.h"
#include "acamera_sbus_api.h"
void control_init( control_fsm_ptr_t p_fsm );
void control_config( control_fsm_ptr_t p_fsm );
void control_update_hw( control_fsm_ptr_t p_fsm );

struct _control_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    control_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    acamera_sbus_t isp_sbus;
    uint8_t antifog_mode;
    uint8_t antifog_enabled;
    uint32_t tpg_enable;
    uint32_t tpg_mode;
};


void control_fsm_clear( control_fsm_ptr_t p_fsm );
void control_fsm_switch_state( control_fsm_ptr_t p_fsm, control_state_t state );
void control_fsm_process_state( control_fsm_ptr_t p_fsm );
uint8_t control_fsm_process_event( control_fsm_ptr_t p_fsm, event_id_t event_id );

void control_fsm_process_interrupt( control_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void control_request_interrupt( control_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __CONTROL_FSM_H__ */
