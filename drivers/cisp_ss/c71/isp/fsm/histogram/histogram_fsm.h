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

#if !defined( __HISTOGRAM_FSM_H__ )
#define __HISTOGRAM_FSM_H__


typedef struct _histogram_fsm_t histogram_fsm_t;
typedef struct _histogram_fsm_t *histogram_fsm_ptr_t;
typedef const struct _histogram_fsm_t *histogram_fsm_const_ptr_t;

enum _histogram_state_t {
    histogram_state_initialized,
    histogram_state_configured,
    histogram_state_reload_calibration,
    histogram_state_ready,
    histogram_state_stopped,
    histogram_state_deinit,
    histogram_state_update_hw,
    histogram_state_invalid
};

typedef enum _histogram_state_t histogram_state_t;

#include "acamera_isp_core_settings.h"

#define AE_HISTOGRAM_TAP_AFTER_WDRGAIN 1     // AE is running on metering histogram (be after wdra gain)
#define AE_HISTOGRAM_TAP_AFTER_FS 2          // AE is running on metering histogram (be after frame stitch)
#define AE_HISTOGRAM_TAP_AFTER_DECOMPANDER 3 // AE is running on metering histogram (be after decompander)
#define AE_HISTOGRAM_TAP_AFTER_SHADING 4     // AE is running on metering histogram (be after shading)

void histogram_init( histogram_fsm_ptr_t p_fsm );
void histogram_config( histogram_fsm_ptr_t p_fsm );
void histogram_reload_calibration( histogram_fsm_ptr_t p_fsm );
void histogram_update_hw( histogram_fsm_ptr_t p_fsm );


struct _histogram_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    histogram_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    uint32_t fullhist[ISP_METERING_HISTOGRAM_SIZE_BINS];
    uint32_t fullhist_sum;
    uint8_t hist_ready_mask;
    uint8_t hist_is_on_sqrt;
};


void histogram_fsm_clear( histogram_fsm_ptr_t p_fsm );
void histogram_fsm_switch_state( histogram_fsm_ptr_t p_fsm, histogram_state_t state );
void histogram_fsm_process_state( histogram_fsm_ptr_t p_fsm );
uint8_t histogram_fsm_process_event( histogram_fsm_ptr_t p_fsm, event_id_t event_id );

void histogram_fsm_process_interrupt( histogram_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void histogram_request_interrupt( histogram_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __HISTOGRAM_FSM_H__ */
