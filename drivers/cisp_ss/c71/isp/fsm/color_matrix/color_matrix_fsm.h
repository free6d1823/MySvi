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

#if !defined( __COLOR_MATRIX_FSM_H__ )
#define __COLOR_MATRIX_FSM_H__


typedef struct _color_matrix_fsm_t color_matrix_fsm_t;
typedef struct _color_matrix_fsm_t *color_matrix_fsm_ptr_t;
typedef const struct _color_matrix_fsm_t *color_matrix_fsm_const_ptr_t;

enum _color_matrix_state_t {
    color_matrix_state_initialized,
    color_matrix_state_configured,
    color_matrix_state_reload_calibration,
    color_matrix_state_ready,
    color_matrix_state_stopped,
    color_matrix_state_deinit,
    color_matrix_state_update_hw,
    color_matrix_state_invalid
};

typedef enum _color_matrix_state_t color_matrix_state_t;

#define ISP_CCM_SIZE 12
#define ISP_CCM_B_SIZE 3

#include "acamera_fsmgr_general_router.h"
void color_matrix_init( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_config( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_update_hw( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_get_info( const color_matrix_fsm_ptr_t p_psm, acamera_cmd_ccm_info *p_info );
void color_matrix_set_info( color_matrix_fsm_ptr_t p_psm, const acamera_cmd_ccm_info *p_info );

struct _color_matrix_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    color_matrix_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    uint8_t saturation_target;
    int16_t color_matrix[ISP_CCM_SIZE];
    int16_t color_matrix_yuv[ISP_CCM_SIZE];
    int16_t color_matrix_yuv_b[ISP_CCM_B_SIZE];
    int16_t color_matrix_luv[ISP_CCM_SIZE];
    int16_t color_matrix_luv_b[ISP_CCM_B_SIZE];
    int16_t color_matrix_hs[ISP_CCM_SIZE];
    int16_t color_matrix_hs_b[ISP_CCM_B_SIZE];
    int16_t color_matrix_s2[ISP_CCM_SIZE];
    int16_t color_matrix_s2_b[ISP_CCM_B_SIZE];
    int16_t color_correction_matrix[ISP_CCM_SIZE];
    int16_t color_saturation_matrix[ISP_CCM_SIZE];
    uint8_t light_source;
    uint8_t light_source_previous;
    uint8_t light_source_ccm;
    uint8_t light_source_ccm_previous;
    uint8_t light_source_change_frames;
    uint8_t light_source_change_frames_left;
    int16_t color_matrix_A[ISP_CCM_SIZE];
    int16_t color_matrix_D40[ISP_CCM_SIZE];
    int16_t color_matrix_D50[ISP_CCM_SIZE];
    int16_t color_matrix_one[ISP_CCM_SIZE];
    uint8_t manual_CCM;
    int16_t manual_color_matrix[ISP_CCM_SIZE];
};


void color_matrix_fsm_clear( color_matrix_fsm_ptr_t p_fsm );
void color_matrix_fsm_switch_state( color_matrix_fsm_ptr_t p_fsm, color_matrix_state_t state );
void color_matrix_fsm_process_state( color_matrix_fsm_ptr_t p_fsm );
uint8_t color_matrix_fsm_process_event( color_matrix_fsm_ptr_t p_fsm, event_id_t event_id );

void color_matrix_fsm_process_interrupt( color_matrix_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void color_matrix_request_interrupt( color_matrix_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __COLOR_MATRIX_FSM_H__ */
