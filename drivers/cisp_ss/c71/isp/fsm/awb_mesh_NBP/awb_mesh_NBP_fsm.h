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

#if !defined( __AWB_FSM_H__ )
#define __AWB_FSM_H__


typedef struct _AWB_fsm_t AWB_fsm_t;
typedef struct _AWB_fsm_t *AWB_fsm_ptr_t;
typedef const struct _AWB_fsm_t *AWB_fsm_const_ptr_t;

enum _AWB_state_t {
    AWB_state_initialized,
    AWB_state_configured,
    AWB_state_reload_calibration,
    AWB_state_ready,
    AWB_state_stopped,
    AWB_state_deinit,
    AWB_state_update_algo,
    AWB_state_update_hw,
    AWB_state_invalid
};

typedef enum _AWB_state_t AWB_state_t;

#include "3a/awb/awb_acamera_core.h"
#include "acamera_fsmgr_general_router.h"
#include "acamera_isp_core_settings.h"
#define ISP_HAS_AWB_FSM 1
#define MAX_AWB_ZONES ( ISP_AWB_HOR_ZONES_MAX * ISP_AWB_VERT_ZONES_MAX )
#define AWB_LIGHT_SOURCE_D50 0x03
#define AWB_DLS_SWITCH_LIGHT_SOURCE_DETECT_FRAMES_QUANTITY 15
#define AWB_DLS_SWITCH_LIGHT_SOURCE_CHANGE_FRAMES_QUANTITY 35
#define D50_DEFAULT 256

void awb_init( AWB_fsm_ptr_t p_fsm );
void awb_config( AWB_fsm_ptr_t p_fsm );
void awb_reload_calibration( AWB_fsm_ptr_t p_fsm );
void awb_update_algo( AWB_fsm_ptr_t p_fsm );
void awb_update_hw( AWB_fsm_ptr_t p_fsm );
void awb_deinit( AWB_fsm_ptr_t p_fsm );

void awb_get_info( AWB_fsm_ptr_t p_psm, acamera_cmd_wb_info *p_info );

struct _AWB_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    AWB_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    uint16_t curr_AWB_ZONES;
    uint32_t sum;
    uint16_t rg_coef;
    uint16_t bg_coef;
    uint8_t p_high;
    awb_zone_t awb_zones[MAX_AWB_ZONES];
    uint16_t rg_valid[MAX_AWB_ZONES];
    uint16_t bg_valid[MAX_AWB_ZONES];
    int32_t wb_log2[4];
    int32_t temperature_detected;
    uint8_t light_source_detected;
    uint8_t light_source_candidate;
    uint8_t detect_light_source_frames_count;
    uint32_t awb_roi;
    int32_t awb_warming[3];
    uint32_t switch_light_source_detect_frames_quantity;
    uint32_t switch_light_source_change_frames_quantity;
    awb_acamera_input_t awb_input;
    awb_stats_data_t awb_stats;
    awb_acamera_output_t awb_output;
    void *awb_core;
};


void AWB_fsm_clear( AWB_fsm_ptr_t p_fsm );
void AWB_fsm_switch_state( AWB_fsm_ptr_t p_fsm, AWB_state_t state );
void AWB_fsm_process_state( AWB_fsm_ptr_t p_fsm );
uint8_t AWB_fsm_process_event( AWB_fsm_ptr_t p_fsm, event_id_t event_id );

void AWB_fsm_process_interrupt( AWB_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void AWB_request_interrupt( AWB_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __AWB_FSM_H__ */
