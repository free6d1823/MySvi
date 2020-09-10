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

#if !defined( __IRIDIX_FSM_H__ )
#define __IRIDIX_FSM_H__


typedef struct _iridix_fsm_t iridix_fsm_t;
typedef struct _iridix_fsm_t *iridix_fsm_ptr_t;
typedef const struct _iridix_fsm_t *iridix_fsm_const_ptr_t;

enum _iridix_state_t {
    iridix_state_initialized,
    iridix_state_configured,
    iridix_state_reload_calibration,
    iridix_state_ready,
    iridix_state_stopped,
    iridix_state_deinit,
    iridix_state_update_algo,
    iridix_state_update_hw,
    iridix_state_invalid
};

typedef enum _iridix_state_t iridix_state_t;

#include "3a/iridix/iridix_acamera_core.h"

void iridix_init( iridix_fsm_ptr_t p_fsm );
void iridix_config( iridix_fsm_ptr_t p_fsm );
void iridix_reload_calibration( iridix_fsm_ptr_t p_fsm );
void iridix_update_algo( iridix_fsm_ptr_t p_fsm );
void iridix_update_hw( iridix_fsm_ptr_t p_fsm );


struct _iridix_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    iridix_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    uint16_t dark_enh;
    uint16_t strength_target;
    uint32_t iridix_contrast;
    uint32_t strength_avg;
    uint16_t iridix_digital_gain_prev;
    iridix_acamera_input_t iridix_input;
    iridix_stats_data_t iridix_stats;
    iridix_acamera_output_t iridix_output;
    void *iridix_core;
};


void iridix_fsm_clear( iridix_fsm_ptr_t p_fsm );
void iridix_fsm_switch_state( iridix_fsm_ptr_t p_fsm, iridix_state_t state );
void iridix_fsm_process_state( iridix_fsm_ptr_t p_fsm );
uint8_t iridix_fsm_process_event( iridix_fsm_ptr_t p_fsm, event_id_t event_id );

void iridix_fsm_process_interrupt( iridix_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void iridix_request_interrupt( iridix_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __IRIDIX_FSM_H__ */
