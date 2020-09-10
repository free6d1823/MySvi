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

#if !defined( __OUTPUT_FORMATTER_FSM_H__ )
#define __OUTPUT_FORMATTER_FSM_H__


typedef struct _output_formatter_fsm_t output_formatter_fsm_t;
typedef struct _output_formatter_fsm_t *output_formatter_fsm_ptr_t;
typedef const struct _output_formatter_fsm_t *output_formatter_fsm_const_ptr_t;

enum _output_formatter_state_t {
    output_formatter_state_initialized,
    output_formatter_state_configured,
    output_formatter_state_reload_calibration,
    output_formatter_state_ready,
    output_formatter_state_stopped,
    output_formatter_state_deinit,
    output_formatter_state_invalid
};

typedef enum _output_formatter_state_t output_formatter_state_t;

#include "acamera_isp_core_settings.h"

typedef struct _axi_cfg_t {
    uint8_t mode;
    uint8_t msb_align;
    uint8_t data_width;
    uint8_t h_subsampling;
    uint8_t v_subsampling;
} axi_cfg_t;

typedef struct _plane_info_t {
    uint8_t axi;
    axi_cfg_t axi_cfg;
    uint8_t axi_format;
} plane_info_t;

typedef struct _output_formatter_cfg_t {
    uint8_t format;
    uint8_t num_planes;
    plane_info_t plane[ISP_MCFE_HWIF_MAX_OUTPUTS];
} output_formatter_cfg_t;

typedef struct _out_format_params_t {
    uint8_t format;
    uint8_t axi_format[ISP_MCFE_HWIF_MAX_OUTPUTS];
} out_format_params_t;

void output_formatter_init( output_formatter_fsm_ptr_t p_fsm );
void output_formatter_config( output_formatter_fsm_ptr_t p_fsm );
void output_formatter_reload_calibration( output_formatter_fsm_ptr_t p_fsm );
void output_formatter_deinit( output_formatter_fsm_ptr_t p_fsm );


struct _output_formatter_fsm_t {
    acamera_fsmgr_t *p_fsmgr;
    output_formatter_state_t state;
    system_fw_interrupt_mask_t irq_mask;
    system_fw_interrupt_mask_t repeat_irq_mask;
    output_formatter_cfg_t output_formatter_cfg;
};


void output_formatter_fsm_clear( output_formatter_fsm_ptr_t p_fsm );
void output_formatter_fsm_switch_state( output_formatter_fsm_ptr_t p_fsm, output_formatter_state_t state );
void output_formatter_fsm_process_state( output_formatter_fsm_ptr_t p_fsm );
uint8_t output_formatter_fsm_process_event( output_formatter_fsm_ptr_t p_fsm, event_id_t event_id );

void output_formatter_fsm_process_interrupt( output_formatter_fsm_const_ptr_t p_fsm, uint8_t irq_event );

void output_formatter_request_interrupt( output_formatter_fsm_ptr_t p_fsm, system_fw_interrupt_mask_t mask );

#endif /* __OUTPUT_FORMATTER_FSM_H__ */
