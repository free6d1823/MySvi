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

#include "module_mcfe_common.h"
#include "module_mcfe_hwif.h"

#include "acamera_frontend_config.h"
#include "acamera_isp_config.h"

#include "system_timer.h" // system_timer_usleep

unsigned char MODULE_MCFE_HWIF_VIDEOINPUT_MODE_SAFE_STOP = ACAMERA_FRONTEND_INPUT_PORT_1_MODE_REQUEST_SAFE_STOP;
unsigned char MODULE_MCFE_HWIF_VIDEOINPUT_MODE_SAFE_START = ACAMERA_FRONTEND_INPUT_PORT_1_MODE_REQUEST_SAFE_START;


inline void mcfe_hwif_input_wrbuf_set( uint8_t input, uint8_t wrbuf_first, uint8_t wrbuf_second )
{
    acamera_frontend_mcfe_input_write_buffer1_write( PHY_ADDR_ISP, input, wrbuf_first );
    LOG( LOG_DEBUG, "Input cfg read 1st %x", acamera_frontend_mcfe_input_write_buffer1_read( PHY_ADDR_ISP, input ) );
    acamera_frontend_mcfe_input_write_buffer2_write( PHY_ADDR_ISP, input, wrbuf_second );
    LOG( LOG_DEBUG, "Input cfg read 2nd %x", acamera_frontend_mcfe_input_write_buffer2_read( PHY_ADDR_ISP, input ) );
}

inline void mcfe_hwif_slot_input_config( uint8_t tslot, uint8_t *input, uint8_t num_of_inputs )
{
    uint8_t i;
	LOG (LOG_NOTICE, "%s", __FUNCTION__);
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        if ( i < num_of_inputs ) {
			LOG (LOG_NOTICE, "input[%d] = %d", i, input[i]);
            acamera_frontend_mcfe_slot_inputs_write( PHY_ADDR_ISP, tslot, i, input[i] );
        } else {
            acamera_frontend_mcfe_slot_inputs_write( PHY_ADDR_ISP, tslot, i, 0xFF );
        }
    }
}


void mcfe_hwif_slot_inputs_config( uint8_t tslot, uint8_t num_of_inputs, uint8_t *inputs )
{
    uint8_t i;
	LOG (LOG_NOTICE, "%s", __FUNCTION__);
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        if ( i < num_of_inputs ) {
			LOG (LOG_NOTICE, "inputs[%d] = %d", i, inputs[i]);
            acamera_frontend_mcfe_slot_inputs_write( PHY_ADDR_ISP, tslot, i, inputs[i] );
        } else {
            acamera_frontend_mcfe_slot_inputs_write( PHY_ADDR_ISP, tslot, i, 0xFF );
        }
    }
}

void mcfe_hwif_slot_output_config( uint8_t tslot, mcfe_hwif_slot_out_buf_cfg_t *out_buf_cfg )
{
    uint8_t i;
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        if ( i < out_buf_cfg->slot_output_num && ( i < ISP_MCFE_HWIF_MAX_OUTPUTS ) ) {
            acamera_frontend_mcfe_slot_outputs_buffer1_write( PHY_ADDR_ISP,
                                                              tslot,
                                                              out_buf_cfg->slot_output_buffers[i] - 1,
                                                              out_buf_cfg->first[i] );


            acamera_frontend_mcfe_slot_outputs_buffer2_write( PHY_ADDR_ISP,
                                                              tslot,
                                                              out_buf_cfg->slot_output_buffers[i] - 1,
                                                              out_buf_cfg->second[i] );
        } else {
            acamera_frontend_mcfe_slot_outputs_buffer1_write( PHY_ADDR_ISP,
                                                              tslot,
                                                              i,
                                                              0xFF );


            acamera_frontend_mcfe_slot_outputs_buffer2_write( PHY_ADDR_ISP,
                                                              tslot,
                                                              i,
                                                              0xFF );
        }
    }
}

void mcfe_hwif_input_cdma_init( void )
{
    int i;
    for ( i = 0; i < MODULE_MCFE_INPUT_PORT_MAX; i++ ) {
        // Reset CDMA configuration.
        acamera_frontend_mcfe_input_stat_valid_write( PHY_ADDR_ISP, i, 0 );		//0x690
        acamera_frontend_mcfe_input_stat_base_write( PHY_ADDR_ISP, i, 0 );		//0x6a0
        acamera_frontend_mcfe_input_stat_size_write( PHY_ADDR_ISP, i, 0 );		//0x6b0
        acamera_frontend_mcfe_input_stat_read_units_write( PHY_ADDR_ISP, i, 0 );		//0x6c0
    }
}

inline void mcfe_hwif_set_slot_mode( uint8_t tslot, uint8_t mode )
{
#if IS_MALI_C71
    // Cancelling slot
    if ( mode == ACAMERA_FRONTEND_MCFE_SLOT_MODE_INACTIVE ) {
        acamera_frontend_mcfe_slot_mode_write( PHY_ADDR_ISP, tslot, ACAMERA_FRONTEND_MCFE_SLOT_MODE_CANCEL_AND_CLEAR_ERRORS );

        // Wait until slot gets cancelled
        int iterations = 0;
        while ( iterations < 100 ) {
            if ( acamera_frontend_mcfe_slot_status_read( PHY_ADDR_ISP, tslot ) == ACAMERA_FRONTEND_MCFE_SLOT_STATUS_PASSING_DATA_THROUGH ) {
                LOG( LOG_INFO, "Slot %d was cancelled after %d ms.", tslot, iterations );
                break;
            }
            system_timer_usleep( 1000 );
            iterations++;
        }

        if ( iterations >= 100 ) {
            LOG( LOG_ERR, "Failed to cancel the slot %d after %d ms.", tslot, iterations );
        }
    }
#endif

    // Set slot mode
    acamera_frontend_mcfe_slot_mode_write( PHY_ADDR_ISP, tslot, mode );
}

inline void mcfe_hwif_slot_trigger( uint8_t slot_id, int reset )
{
    if ( reset )
        acamera_frontend_mcfe_start_slot_write( PHY_ADDR_ISP, ISP_MCFE_START_SLOT_IDLE );
#if KERNEL_MODULE
    wmb();
#endif
    acamera_frontend_mcfe_start_slot_write( PHY_ADDR_ISP, slot_id );
#if KERNEL_MODULE
    wmb();
#endif
}

uint8_t mcfe_hwif_slot_is_idle( uint8_t slot_id )
{
    uint8_t status = acamera_frontend_mcfe_slot_status_read( PHY_ADDR_ISP, slot_id );
    return status == ACAMERA_FRONTEND_MCFE_SLOT_STATUS_IDLE;
}

inline uint8_t mcfe_hwif_scheduler_mode_read( void )
{
    return acamera_frontend_mcfe_scheduler_mode_read( PHY_ADDR_ISP );
}
inline void mcfe_hwif_scheduler_mode_write( uint8_t mode )
{
    acamera_frontend_mcfe_scheduler_mode_write( PHY_ADDR_ISP, mode );
}

inline int module_mcfe_check_scheduler_status( uint32_t exp_val, uint32_t iteration, uint32_t time_us )
{
    int rc = MCFE_ERR_GENERAL;
    int read_val;

    while ( iteration ) {
        read_val = mcfe_hwif_scheduler_mode_read();
        if ( read_val == exp_val ) {
            rc = MCFE_ERR_NONE;
            break;
        }
        system_timer_usleep( time_us );
        iteration--;
    }

    return rc;
}

/* Video input wrapper */
/********************************************************************************
 * Type definition
 *******************************************************************************/
// Writer function wrapper
typedef struct _mcfe_input_port_wrapper_write {
    // Input port
    void ( *input_port_preset )( uint32_t, uint8_t );
    void ( *input_port_aclg_window2 )( uint32_t, uint8_t );
    void ( *input_port_fieldg_window2 )( uint32_t, uint8_t );
    void ( *input_port_hc_start0 )( uint32_t, uint16_t );
    void ( *input_port_hc_size0 )( uint32_t, uint16_t );
    void ( *input_port_hc_start1 )( uint32_t, uint16_t );
    void ( *input_port_hc_size1 )( uint32_t, uint16_t );
    void ( *input_port_vc_start )( uint32_t, uint16_t );
    void ( *input_port_vc_size )( uint32_t, uint16_t );
    void ( *input_port_mode_request )( uint32_t, uint8_t );

    // Stream crossbar
    void ( *stream_xbar_stream_select )( uint32_t, uint8_t );
    void ( *stream_xbar_stream_source )( uint32_t, uint8_t );
    void ( *stream_xbar_stream_id )( uint32_t, uint8_t );
} mcfe_input_port_wrapper_write;

// Read function wrapper
typedef struct _mcfe_input_port_wrapper_read {
    uint8_t ( *input_port_mode_status_read )( uint32_t base );
} mcfe_input_port_wrapper_read;

#define INPUT_WRAPP( INPUT_IDX, IO )                                                                   \
    {                                                                                                  \
        .input_port_preset = acamera_frontend_input_port_##INPUT_IDX##_preset_##IO,                    \
        .input_port_aclg_window2 = acamera_frontend_input_port_##INPUT_IDX##_aclg_window2_##IO,        \
        .input_port_fieldg_window2 = acamera_frontend_input_port_##INPUT_IDX##_fieldg_window2_##IO,    \
        .input_port_hc_start0 = acamera_frontend_input_port_##INPUT_IDX##_hc_start0_##IO,              \
        .input_port_hc_size0 = acamera_frontend_input_port_##INPUT_IDX##_hc_size0_##IO,                \
        .input_port_hc_start1 = acamera_frontend_input_port_##INPUT_IDX##_hc_start1_##IO,              \
        .input_port_hc_size1 = acamera_frontend_input_port_##INPUT_IDX##_hc_size1_##IO,                \
        .input_port_vc_start = acamera_frontend_input_port_##INPUT_IDX##_vc_start_##IO,                \
        .input_port_vc_size = acamera_frontend_input_port_##INPUT_IDX##_vc_size_##IO,                  \
        .input_port_mode_request = acamera_frontend_input_port_##INPUT_IDX##_mode_request_##IO,        \
        .stream_xbar_stream_select = acamera_frontend_stream_crossbar_stream##INPUT_IDX##_select_##IO, \
        .stream_xbar_stream_source = acamera_frontend_stream_crossbar_stream##INPUT_IDX##_source_##IO, \
        .stream_xbar_stream_id = acamera_frontend_stream_crossbar_stream##INPUT_IDX##_id_##IO          \
    }

#define INPUT_READ_WRAPP( INPUT_IDX, IO )                                                          \
    {                                                                                              \
        .input_port_mode_status_read = acamera_frontend_input_port_##INPUT_IDX##_mode_status_##IO, \
    }
static const mcfe_input_port_wrapper_read mcfe_input_port_reg_read[] = {
    INPUT_READ_WRAPP( 1, read ),
    INPUT_READ_WRAPP( 2, read ),
    INPUT_READ_WRAPP( 3, read ),
    INPUT_READ_WRAPP( 4, read ),
};

static const mcfe_input_port_wrapper_write mcfe_input_port_reg_write[] = {
    INPUT_WRAPP( 1, write ),
    INPUT_WRAPP( 2, write ),
    INPUT_WRAPP( 3, write ),
    INPUT_WRAPP( 4, write ),
};

void mcfe_hwif_input_port_config( uint8_t input, uint8_t aclg_window2, uint16_t hc_start0, uint16_t hc_size0, uint16_t hc_start1, uint16_t hc_size1, uint16_t vc_start, uint16_t vc_size, uint8_t stream_select, uint8_t xbar_id )
{
    mcfe_input_port_reg_write[input].input_port_preset( PHY_ADDR_ISP, 0x6 /* Default mode: 15 */ );
    mcfe_input_port_reg_write[input].input_port_aclg_window2( PHY_ADDR_ISP, aclg_window2 );
    mcfe_input_port_reg_write[input].input_port_fieldg_window2( PHY_ADDR_ISP, aclg_window2 );
    mcfe_input_port_reg_write[input].input_port_hc_start0( PHY_ADDR_ISP, hc_start0 );
    mcfe_input_port_reg_write[input].input_port_hc_size0( PHY_ADDR_ISP, hc_size0 );
    mcfe_input_port_reg_write[input].input_port_hc_start1( PHY_ADDR_ISP, hc_start1 );
    mcfe_input_port_reg_write[input].input_port_hc_size1( PHY_ADDR_ISP, hc_size1 );
    mcfe_input_port_reg_write[input].input_port_vc_start( PHY_ADDR_ISP, vc_start );
    mcfe_input_port_reg_write[input].input_port_vc_size( PHY_ADDR_ISP, vc_size );

    mcfe_input_port_reg_write[input].stream_xbar_stream_select( PHY_ADDR_ISP, stream_select );
    mcfe_input_port_reg_write[input].stream_xbar_stream_source( PHY_ADDR_ISP, xbar_id );
    mcfe_input_port_reg_write[input].stream_xbar_stream_id( PHY_ADDR_ISP, 0 );
}

void mcfe_hwif_input_port_set_mode( uint8_t input, uint8_t mode )
{
    mcfe_input_port_reg_write[input].input_port_mode_request( PHY_ADDR_ISP, mode );
}

uint8_t mcfe_hwif_input_port_get_status( uint8_t input )
{
    return mcfe_input_port_reg_read[input].input_port_mode_status_read( PHY_ADDR_ISP );
}

void mcfe_hwif_input_fifos_config_init( void )
{
    acamera_frontend_mcfe_fifo1_low_watermark_write( PHY_ADDR_ISP, 16 );
    acamera_frontend_mcfe_fifo1_high_watermark_write( PHY_ADDR_ISP, 2047 );
    acamera_frontend_mcfe_fifo2_low_watermark_write( PHY_ADDR_ISP, 16 );
    acamera_frontend_mcfe_fifo2_high_watermark_write( PHY_ADDR_ISP, 2047 );
    acamera_frontend_mcfe_fifo3_low_watermark_write( PHY_ADDR_ISP, 16 );
    acamera_frontend_mcfe_fifo3_high_watermark_write( PHY_ADDR_ISP, 2047 );
    acamera_frontend_mcfe_fifo4_low_watermark_write( PHY_ADDR_ISP, 0x2e);//16 );
    acamera_frontend_mcfe_fifo4_high_watermark_write( PHY_ADDR_ISP, 0x3f0);//2047 );
}

void mcfe_hwif_input_fifo_config_init( uint8_t input )
{
    switch ( input ) {
    case 0:
        acamera_frontend_mcfe_fifo1_low_watermark_write( PHY_ADDR_ISP, 16 );
        acamera_frontend_mcfe_fifo1_high_watermark_write( PHY_ADDR_ISP, 2047 );
        break;
    case 1:
        acamera_frontend_mcfe_fifo2_low_watermark_write( PHY_ADDR_ISP, 16 );
        acamera_frontend_mcfe_fifo2_high_watermark_write( PHY_ADDR_ISP, 2047 );
        break;
    case 2:
        acamera_frontend_mcfe_fifo3_low_watermark_write( PHY_ADDR_ISP, 16 );
        acamera_frontend_mcfe_fifo3_high_watermark_write( PHY_ADDR_ISP, 2047 );
        break;
    case 3:
        acamera_frontend_mcfe_fifo4_low_watermark_write( PHY_ADDR_ISP, 0x2e);//16 );
        acamera_frontend_mcfe_fifo4_high_watermark_write( PHY_ADDR_ISP, 0x3f0);//2047 );
        break;
    }
}

void mcfe_hwif_input_fifo_config( uint8_t input, uint16_t data_width, uint16_t width )
{
    switch ( input ) {
    case 0:
        acamera_frontend_mcfe_fifo1_low_watermark_write( PHY_ADDR_ISP, 0x1e0);//0x2e);//width * data_width / 64 );
        acamera_frontend_mcfe_fifo1_high_watermark_write( PHY_ADDR_ISP, 0x3f0 );
        break;
    case 1:
        acamera_frontend_mcfe_fifo2_low_watermark_write( PHY_ADDR_ISP, 0x1e0);//0x2e);//width * data_width / 64 );
        acamera_frontend_mcfe_fifo2_high_watermark_write( PHY_ADDR_ISP, 0x3f0);
        break;
    case 2:
        acamera_frontend_mcfe_fifo3_low_watermark_write( PHY_ADDR_ISP, 0x1e0);//0x2e);//width * data_width / 64 );
        acamera_frontend_mcfe_fifo3_high_watermark_write( PHY_ADDR_ISP, 0x3f0);
        break;
    case 3:
        acamera_frontend_mcfe_fifo4_low_watermark_write( PHY_ADDR_ISP, 0x1e0);//0x2e);//width * data_width / 64 );
        acamera_frontend_mcfe_fifo4_high_watermark_write( PHY_ADDR_ISP, 0x3f0);
        break;
    }
}
void mcbe_hwif_output_fifo_config( uint8_t mux_output, uint16_t data)
{
	switch (mux_output) {
		case 1:
			acamera_frontend_mcbe_fifo1_watermark_write( PHY_ADDR_ISP, data);
			break;
		case 2:
			acamera_frontend_mcbe_fifo2_watermark_write( PHY_ADDR_ISP, data);
			break;
		case 3:
			acamera_frontend_mcbe_fifo3_watermark_write( PHY_ADDR_ISP, data);
			break;
		case 4:
			acamera_frontend_mcbe_fifo4_watermark_write( PHY_ADDR_ISP, data);
			break;
	}
}
void mcfe_hwif_flow_control_enable(int enable)
{
	acamera_frontend_mcbe_enable_flow_control_write( PHY_ADDR_ISP, enable);
	acamera_frontend_mcfe_enable_flow_control_write( PHY_ADDR_ISP, enable);
}

void mcfe_hwif_input_hist_config( uint8_t input, uint16_t rggb_start, uint8_t cfa_pattern )
{
    switch ( input ) {
    case 0:
        acamera_isp_metering_hist_1_rggb_start_write( PHY_ADDR_ISP, rggb_start );
        acamera_isp_metering_hist_1_cfa_pattern_write( PHY_ADDR_ISP, cfa_pattern );
        break;
    case 1:
        acamera_isp_metering_hist_2_rggb_start_write( PHY_ADDR_ISP, rggb_start );
        acamera_isp_metering_hist_2_cfa_pattern_write( PHY_ADDR_ISP, cfa_pattern );
        break;
    case 2:
        acamera_isp_metering_hist_3_rggb_start_write( PHY_ADDR_ISP, rggb_start );
        acamera_isp_metering_hist_3_cfa_pattern_write( PHY_ADDR_ISP, cfa_pattern );
        break;
    case 3:
        acamera_isp_metering_hist_4_rggb_start_write( PHY_ADDR_ISP, rggb_start );
        acamera_isp_metering_hist_4_cfa_pattern_write( PHY_ADDR_ISP, cfa_pattern );
        break;
    }
}
/* Input wrapper END */

void isp_hwif_top_config( uint32_t cdma_addr, uint16_t width, uint16_t height, uint16_t rggb_start, uint8_t cfa_pattern )
{
    LOG( LOG_INFO, "isp_hwif_top_config %#x", cdma_addr );
    acamera_isp_top_rggb_start_write( cdma_addr, rggb_start );
    acamera_isp_top_active_width_write( cdma_addr, width );
    acamera_isp_top_active_height_write( cdma_addr, height );
    acamera_isp_top_cfa_pattern_write( cdma_addr, cfa_pattern );
}
