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

#if !defined( __AE_FSM_H__ )
#define __AE_FSM_H__


typedef struct _AE_fsm_t AE_fsm_t;
typedef struct _AE_fsm_t *AE_fsm_ptr_t;
typedef const struct _AE_fsm_t *AE_fsm_const_ptr_t;

enum _AE_state_t {
    AE_state_initialized,
    AE_state_configured,
    AE_state_reload_calibration,
    AE_state_ready,
    AE_state_stopped,
    AE_state_deinit,
    AE_state_update_algo,
    AE_state_invalid
};

typedef enum _AE_state_t AE_state_t;

#include "3a/ae/ae_acamera_core.h"
#include "acamera_isp_core_settings.h"

#define ISP_HAS_AE_FSM 1
#define AE_CLIPPING_ANTIFLICKER_N 5

void ae_init( AE_fsm_ptr_t p_fsm );
void ae_config( AE_fsm_ptr_t p_fsm );
void ae_reload_calibration( AE_fsm_ptr_t p_fsm );
void ae_update_algo( AE_fsm_ptr_t p_fsm );

struct _AE_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    AE_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    int32_t error_log2;
    int32_t ae_hist_mean;
    int32_t exposure_log2;
    int64_t integrator;
    uint32_t exposure_ratio;
    uint32_t exposure_ratio_avg;
    uint32_t ae_roi;
    uint64_t WSNR_cumsum[ISP_METERING_HISTOGRAM_SIZE_BINS];
    int32_t targets_history[AE_CLIPPING_ANTIFLICKER_N];
    uint32_t next_hist_idx;
    int32_t max_target;
    ae_acamera_input_t ae_input;
    ae_stats_data_t ae_stats;
    ae_acamera_output_t ae_output;
    void *ae_core;
};


void AE_fsm_clear( AE_fsm_ptr_t p_fsm );
void AE_fsm_switch_state( AE_fsm_ptr_t p_fsm, AE_state_t state );
void AE_fsm_process_state( AE_fsm_ptr_t p_fsm );
uint8_t AE_fsm_process_event( AE_fsm_ptr_t p_fsm, event_id_t event_id );

void AE_fsm_process_interrupt( AE_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void AE_request_interrupt( AE_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __AE_FSM_H__ */
