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

#ifndef _MODULE_MCFE_HWIF_H_
#define _MODULE_MCFE_HWIF_H_

#include "system_types.h"
#include "acamera_isp_core_settings.h" //For ISP_MCFE_HWIF_MAX_OUTPUTS

extern unsigned char MODULE_MCFE_HWIF_VIDEOINPUT_MODE_SAFE_STOP;
extern unsigned char MODULE_MCFE_HWIF_VIDEOINPUT_MODE_SAFE_START;

typedef struct {
    uint8_t slot_output_num;
    uint8_t first[ISP_MCFE_HWIF_MAX_OUTPUTS];
    uint8_t second[ISP_MCFE_HWIF_MAX_OUTPUTS];
    uint8_t slot_output_buffers[ISP_MCFE_HWIF_MAX_OUTPUTS];
} mcfe_hwif_slot_out_buf_cfg_t;

typedef enum mcfe_hwif_buf_type_t {
    MCFE_BUF_TYPE_NONE,
    MCFE_BUF_TYPE_RAW,
    MCFE_BUF_TYPE_OUT,
    MCFE_BUF_TYPE_MAX
} mcfe_hwif_buf_type_t;

typedef enum mcfe_hwif_buf_flags_t {
    MCFE_BUF_FLAG_MSB_ALIGN = ( 1 << 0 ),
    MCFE_BUF_FLAG_POOL = ( 1 << 1 ),
    MCFE_BUF_FLAG_CLONE = ( 1 << 2 ),
    MCFE_BUF_FLAG_INFINITE = ( 1 << 3 )
} mcfe_hwif_buf_flags_t;

/* Input control interface */
void mcfe_hwif_input_config( uint8_t input, uint8_t mode, uint8_t msb_align, uint8_t data_width );
void mcfe_hwif_input_wrbuf_set( uint8_t input, uint8_t wrbuf_first, uint8_t wrbuf_second );
void mcfe_hwif_input_cdma_init( void );
void mcfe_hwif_input_fifos_config_init( void );
void mcfe_hwif_input_fifo_config_init( uint8_t input );
void mcfe_hwif_input_fifo_config( uint8_t input, uint16_t data_width, uint16_t width );
void mcfe_hwif_flow_control_enable(int enable);
void mcbe_hwif_output_fifo_config( uint8_t mux_output, uint16_t data);
void mcfe_hwif_input_hist_config( uint8_t input, uint16_t rggb_start, uint8_t cfa_pattern );

/* Slot control interface */
void mcfe_hwif_slot_inputs_config( uint8_t tslot, uint8_t num_of_inputs, uint8_t *inputs );
void mcfe_hwif_slot_output_config( uint8_t tslot, mcfe_hwif_slot_out_buf_cfg_t *out_buf_cfg );
void mcfe_hwif_slot_all_init( void );
void mcfe_hwif_set_slot_mode( uint8_t tslot, uint8_t mode );
void mcfe_hwif_slot_trigger( uint8_t slot_id, int reset );
uint8_t mcfe_hwif_slot_is_idle( uint8_t slot_id );
void mcfe_hwif_slot_cfg_CDMA_config( uint8_t slot_id, uint32_t cdma_addr, uint8_t hist_position_is_be );
void mcfe_hwif_slot_stat_CDMA_config( uint8_t input_id, uint32_t cdma_addr, uint8_t hist_position_is_be );
void mcfe_hwif_disable_hist_on_slot_and_input( uint8_t slot_id, uint8_t input_id );
void mcfe_hwif_slot_input_config( uint8_t tslot, uint8_t *input, uint8_t num_of_inputs );

/* Scheduler control interface */
uint8_t mcfe_hwif_scheduler_mode_read( void );
void mcfe_hwif_scheduler_mode_write( uint8_t mode );
int module_mcfe_check_scheduler_status( uint32_t exp_val, uint32_t iteration, uint32_t time_us );

/* Non MCFE controls */
void mcfe_hwif_input_port_config( uint8_t input, uint8_t aclg_window2, uint16_t hc_start0, uint16_t hc_size0, uint16_t hc_start1, uint16_t hc_size1, uint16_t vc_start, uint16_t vc_size, uint8_t stream_select, uint8_t xbar_id );
void mcfe_hwif_input_port_set_mode( uint8_t input, uint8_t mode );
uint8_t mcfe_hwif_input_port_get_status( uint8_t input );

void isp_hwif_top_config( uint32_t cdma_addr, uint16_t width, uint16_t height, uint16_t rggb_start, uint8_t cfa_pattern );

/* Hardware buffer control interface */
void mcfe_hwif_buff_config( const mcfe_hwif_buf_type_t bftype,
                            const uint8_t idx,
                            uint8_t data_width,
                            uint8_t flags,
                            uint32_t base_address,
                            uint32_t line_offset,
                            uint16_t active_width,
                            uint16_t active_height );

void mcfe_hwif_buff_addr_set( const mcfe_hwif_buf_type_t bftype, const uint8_t idx, uint32_t base_address );
uint32_t mcfe_hwif_buff_addr_get( const mcfe_hwif_buf_type_t bftype, const uint8_t idx );
void mcfe_hwif_buff_enable( const mcfe_hwif_buf_type_t bftype, const uint8_t idx, uint8_t onoff );
void mcfe_hwif_buff_status_set( const mcfe_hwif_buf_type_t bftype, const uint8_t idx, uint8_t status );
uint8_t mcfe_hwif_buff_status_get( const mcfe_hwif_buf_type_t bftype, const uint8_t idx );

#endif // _MODULE_MCFE_HWIF_H_
