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

#if !defined( __NOISE_REDUCTION_FSM_H__ )
#define __NOISE_REDUCTION_FSM_H__


typedef struct _noise_reduction_fsm_t noise_reduction_fsm_t;
typedef struct _noise_reduction_fsm_t *noise_reduction_fsm_ptr_t;
typedef const struct _noise_reduction_fsm_t *noise_reduction_fsm_const_ptr_t;

enum _noise_reduction_state_t {
    noise_reduction_state_initialized,
    noise_reduction_state_configured,
    noise_reduction_state_reload_calibration,
    noise_reduction_state_ready,
    noise_reduction_state_stopped,
    noise_reduction_state_deinit,
    noise_reduction_state_update_hw,
    noise_reduction_state_invalid
};

typedef enum _noise_reduction_state_t noise_reduction_state_t;


#define MAGIC_GAIN_DIGITAL_FINE 0x03FF
#define MAGIC_TNR_EXP_TRESH 192 * 64
#define NR_LUT_SIZE 128
#define NR_SINTER_BITS 16

void noise_reduction_config( noise_reduction_fsm_ptr_t p_fsm );
void noise_reduction_reload_calibration( noise_reduction_fsm_ptr_t p_fsm );
void noise_reduction_update_hw( noise_reduction_fsm_ptr_t p_fsm );
void noise_reduction_deinit( noise_reduction_fsm_ptr_t p_fsm );


struct _noise_reduction_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    noise_reduction_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    int16_t tnr_thresh_exp1;
    int16_t tnr_thresh_exp2;
    int16_t snr_thresh_exp1;
    int16_t snr_thresh_exp2;
    uint8_t tnr_exp_thresh;
    uint8_t tnr_exp1_ratio;
    uint8_t tnr_exp2_ratio;
    uint8_t tnr_strength_target;
    uint8_t snr_strength_target;
    int16_t tnr_thresh_master;
    int16_t snr_thresh_master;
    int16_t snr_thresh_contrast;
    uint32_t temper_ev_previous_frame;
    uint32_t temper_diff_avg;
    uint32_t temper_diff_coeff;
};


void noise_reduction_fsm_clear( noise_reduction_fsm_ptr_t p_fsm );
void noise_reduction_fsm_switch_state( noise_reduction_fsm_ptr_t p_fsm, noise_reduction_state_t state );
void noise_reduction_fsm_process_state( noise_reduction_fsm_ptr_t p_fsm );
uint8_t noise_reduction_fsm_process_event( noise_reduction_fsm_ptr_t p_fsm, event_id_t event_id );

void noise_reduction_fsm_process_interrupt( noise_reduction_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void noise_reduction_request_interrupt( noise_reduction_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __NOISE_REDUCTION_FSM_H__ */
