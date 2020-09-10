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

#if !defined( __ISP_WRAPPER_FSM_H__ )
#define __ISP_WRAPPER_FSM_H__


typedef struct _isp_wrapper_fsm_t isp_wrapper_fsm_t;
typedef struct _isp_wrapper_fsm_t *isp_wrapper_fsm_ptr_t;
typedef const struct _isp_wrapper_fsm_t *isp_wrapper_fsm_const_ptr_t;

enum _isp_wrapper_state_t {
    isp_wrapper_state_initialized,
    isp_wrapper_state_configured,
    isp_wrapper_state_reload_calibration,
    isp_wrapper_state_ready,
    isp_wrapper_state_stopped,
    isp_wrapper_state_deinit,
    isp_wrapper_state_invalid
};

typedef enum _isp_wrapper_state_t isp_wrapper_state_t;


void isp_wrapper_init( isp_wrapper_fsm_ptr_t p_fsm );
void isp_wrapper_config( isp_wrapper_fsm_ptr_t p_fsm );
void isp_wrapper_start( isp_wrapper_fsm_ptr_t p_fsm );
void isp_wrapper_stop( isp_wrapper_fsm_ptr_t p_fsm );


struct _isp_wrapper_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    isp_wrapper_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
};


void isp_wrapper_fsm_clear( isp_wrapper_fsm_ptr_t p_fsm );
void isp_wrapper_fsm_switch_state( isp_wrapper_fsm_ptr_t p_fsm, isp_wrapper_state_t state );
void isp_wrapper_fsm_process_state( isp_wrapper_fsm_ptr_t p_fsm );
uint8_t isp_wrapper_fsm_process_event( isp_wrapper_fsm_ptr_t p_fsm, event_id_t event_id );

void isp_wrapper_fsm_process_interrupt( isp_wrapper_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void isp_wrapper_request_interrupt( isp_wrapper_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __ISP_WRAPPER_FSM_H__ */
