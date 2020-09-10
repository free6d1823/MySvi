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

#if !defined( __CMOS_FSM_H__ )
#define __CMOS_FSM_H__


typedef struct _cmos_fsm_t cmos_fsm_t;
typedef struct _cmos_fsm_t *cmos_fsm_ptr_t;
typedef const struct _cmos_fsm_t *cmos_fsm_const_ptr_t;

enum _cmos_state_t {
    cmos_state_initialized,
    cmos_state_configured,
    cmos_state_reload_calibration,
    cmos_state_ready,
    cmos_state_stopped,
    cmos_state_deinit,
    cmos_state_update_exposure,
    cmos_state_update_hw,
    cmos_state_invalid
};

typedef enum _cmos_state_t cmos_state_t;

#include "acamera_fsmgr_general_router.h"
#include "acamera_isp_config.h"
#define API_OTAE_ITERATION_COUNT ( 15 )


#define EXP_LUT_TABLE_SIZE ( 14 )


typedef struct _exposure_partition_t {
    uint32_t i;
    uint32_t v;
} exposure_partition_t;
typedef struct _cmos_control_param_t {
    uint32_t antiflicker_enable;
    uint32_t anti_flicker_frequency;
    uint32_t manual_integration_time;
    uint32_t manual_sensor_analog_gain;
    uint32_t manual_sensor_digital_gain;
    uint32_t manual_isp_digital_gain;
    uint32_t manual_max_integration_time;
    uint32_t manual_exposure_ratio;
    uint32_t max_integration_time;
    uint32_t max_sensor_analog_gain;
    uint32_t max_sensor_digital_gain;
    uint32_t max_isp_digital_gain;
    uint32_t max_exposure_ratio;
    uint32_t integration_time;
    uint32_t sensor_analog_gain;
    uint32_t sensor_digital_gain;
    uint32_t isp_digital_gain;
    uint32_t analog_gain_last_priority;
    uint32_t analog_gain_reserve;
    uint32_t isp_gain_reserve;
} cmos_control_param_t;
typedef struct _fps_counter_t {
    uint32_t last_tick;
    uint32_t avg_frame_ticks;
} fps_counter_t;

void cmos_update_exposure_partitioning_lut( cmos_fsm_ptr_t p_fsm );
void cmos_init( cmos_fsm_ptr_t p_fsm );
void cmos_deinit( cmos_fsm_ptr_t p_fsm );
void cmos_config( cmos_fsm_ptr_t p_fsm );
void cmos_update_exposure( cmos_fsm_ptr_t p_fsm );
void cmos_update_hw( cmos_fsm_ptr_t p_fsm );
void cmos_reload_calibration( cmos_fsm_ptr_t p_fsm );
void cmos_inttime_write( cmos_fsm_const_ptr_t p_fsm );
void cmos_gains_write( cmos_fsm_const_ptr_t p_fsm );
void cmos_set_exposure_target( cmos_fsm_ptr_t p_fsm, int32_t exposure_log2, uint32_t exposure_ratio );
exposure_set_t *cmos_get_frame_exposure_set( cmos_fsm_ptr_t p_fsm, int i_frame );
uint16_t cmos_get_fps( cmos_fsm_ptr_t p_fsm );

struct _cmos_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    cmos_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    int16_t isp_gain;
    int16_t wb[4];
    int32_t isp_wb_log2[4];
    uint8_t manual_gain_mode;
    uint32_t manual_gain;
    uint32_t exposure;
    int32_t exposure_log2;
    exposure_set_t exp_next_set;
    exposure_data_set_t exp_write_set;
    int32_t max_exposure_log2;
    exposure_set_t exposure_hist[8];
    int exposure_hist_pos;
    fps_counter_t fps_cnt;
    uint32_t flicker_freq;
    uint32_t lines_per_500ms;
    uint32_t exposure_ratio_in;
    uint32_t prev_integration_time_short;
    uint32_t integration_time_short;
    uint32_t integration_time_medium;
    uint32_t integration_time_medium2;
    uint32_t integration_time_long;
    uint16_t exposure_ratio;
    int32_t again_val_log2;
    int32_t dgain_val_log2;
    int32_t log2_gain_avg;
    int32_t isp_dgain_log2;
    int32_t target_gain_log2;
    int32_t target_gain_step_log2;
    uint8_t flash_state;
    uint8_t flash_skip_charge;
    uint32_t exp_lut[EXP_LUT_TABLE_SIZE];
    uint32_t exp_lut_valid_entries;
    const exposure_partition_t *exp_partition_tbl;
    int32_t maximum_isp_digital_gain;
    uint32_t cmos_frame_start_irq;
};


void cmos_fsm_clear( cmos_fsm_ptr_t p_fsm );
void cmos_fsm_switch_state( cmos_fsm_ptr_t p_fsm, cmos_state_t state );
void cmos_fsm_process_state( cmos_fsm_ptr_t p_fsm );
uint8_t cmos_fsm_process_event( cmos_fsm_ptr_t p_fsm, event_id_t event_id );

void cmos_fsm_process_interrupt( cmos_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void cmos_request_interrupt( cmos_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __CMOS_FSM_H__ */
