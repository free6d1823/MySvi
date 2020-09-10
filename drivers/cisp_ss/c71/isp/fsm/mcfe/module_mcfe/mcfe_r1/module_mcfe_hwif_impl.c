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

#include "system_timer.h" // system_timer_usleep
#include "acamera_configuration.h"
#include "acamera_frontend_config.h"
#include "acamera_logger.h"
#include "module_mcfe_hwif.h"
#include "module_mcfe_hwif_buffer_access.h"
#include "util_addr_calc.h"

// TODO: due to dependency to histogram, to be removed.
#include "module_mcfe_common.h"

#undef LOG_MODULE
#define LOG_MODULE LOG_MODULE_MCFE

#define CDMA_UNIT_METERING_HIST_1 ( 1 << 0 )
#define CDMA_UNIT_METERING_HIST_2 ( 1 << 1 )
#define CDMA_UNIT_METERING_HIST_3 ( 1 << 2 )
#define CDMA_UNIT_METERING_HIST_4 ( 1 << 3 )
#define CDMA_UNIT_ANTIFOG_HIST ( 1 << 4 )
#define CDMA_UNIT_METERING_AE ( 1 << 9 )
#define CDMA_UNIT_METERING_AWB ( 1 << 10 )
#define CDMA_UNIT_IRIDIX ( 1 << 12 )
#define CDMA_UNIT_ISP_SETUP ( 1 << 14 )
#define CDMA_UNIT_BIST ( 1 << 15 )
#define CDMA_UNIT_GLOBAL_TM ( 1 << 16 )
#define CDMA_UNIT_METERING ( 1 << 17 )
#define CDMA_UNIT_DEMOSAIC_RGBIR ( 1 << 18 )
#define CDMA_UNIT_IRIDIX_LUT ( 1 << 20 )
#define CDMA_UNIT_SINTER_RM ( 1 << 21 )
#define CDMA_UNIT_NOISE_PROFILES ( 1 << 22 )
#define CDMA_UNIT_ZONES_3A ( 1 << 23 )
#define CDMA_UNIT_GAMMA_BE ( 1 << 24 )
#define CDMA_UNIT_CA_MEMORY ( 1 << 25 )
#define CDMA_UNIT_OUT_FORMAT_LUT ( 1 << 26 )
#define CDMA_UNIT_RADIAL_SHADING_LUT ( 1 << 27 )
#define CDMA_UNIT_DEFECT_PIXEL_MEMORY ( 1 << 28 )
#define CDMA_UNIT_SHADING_MESH_MEMORY ( 1 << 29 )


void mcfe_hwif_input_config( uint8_t input, uint8_t mode, uint8_t msb_align, uint8_t data_width )
{
    acamera_frontend_mcfe_input_mode_write( PHY_ADDR_ISP, input, mode );
    acamera_frontend_mcfe_input_msb_align_write( PHY_ADDR_ISP, input, msb_align );
    acamera_frontend_mcfe_input_data_width_write( PHY_ADDR_ISP, input, data_width );
}

// Init all slots.
void mcfe_hwif_slot_all_init( void )
{
    int i, j;
    int old_sched_mode;

    // Start scheduler if needed.
    old_sched_mode = mcfe_hwif_scheduler_mode_read();
    if ( old_sched_mode == 0 )
        mcfe_hwif_scheduler_mode_write( 1 );

    // Cancel all slots.
    for ( i = 0; i < ISP_MCFE_MAX_SLOT; i++ ) {
        // Reset slot mode (-> 6 -> 0)
        acamera_frontend_mcfe_slot_mode_write( PHY_ADDR_ISP, i, 6 );
    }

    system_timer_usleep( 100000 );

    // Disable all slots.
    for ( i = 0; i < ISP_MCFE_MAX_SLOT; i++ ) {
        acamera_frontend_mcfe_slot_mode_write( PHY_ADDR_ISP, i, 0 );

        // Reset slot event.
        acamera_frontend_mcfe_slot_event_write( PHY_ADDR_ISP, i, 0 );

        // Reset slot event.
        acamera_frontend_mcfe_slot_delay_write( PHY_ADDR_ISP, i, 0 );

        // Reset slot input/output.
        for ( j = 0; j < MODULE_MCFE_INPUT_PORT_MAX; j++ ) {
            acamera_frontend_mcfe_slot_inputs_write( PHY_ADDR_ISP, i, j, 0xFF );
            acamera_frontend_mcfe_slot_outputs_buffer1_write( PHY_ADDR_ISP, i, j, 0xFF );
            acamera_frontend_mcfe_slot_outputs_buffer2_write( PHY_ADDR_ISP, i, j, 0xFF );
        }

        // Reset CDMA configuration.
        acamera_frontend_mcfe_slot_cfg_valid_write( PHY_ADDR_ISP, i, 0 );
        acamera_frontend_mcfe_slot_cfg_base_write( PHY_ADDR_ISP, i, 0 );
        acamera_frontend_mcfe_slot_cfg_size_write( PHY_ADDR_ISP, i, 0 );
        acamera_frontend_mcfe_slot_cfg_read_units_write( PHY_ADDR_ISP, i, 0 );
        acamera_frontend_mcfe_slot_cfg_write_units_write( PHY_ADDR_ISP, i, 0 );
    }

    // Reset slot cfg ack.
    acamera_frontend_mcfe_slot_cfg_no_ack_write( PHY_ADDR_ISP, 0 );
    acamera_frontend_mcfe_input_stat_no_ack_write( PHY_ADDR_ISP, 0 );

    // Process queue clear.
    acamera_frontend_mcfe_pq_clear_write( PHY_ADDR_ISP, 1 );
    acamera_frontend_mcfe_pq_clear_write( PHY_ADDR_ISP, 0 );

    // Stop scheduler if needed.
    if ( old_sched_mode == 0 )
        mcfe_hwif_scheduler_mode_write( 0 );
}

void mcfe_hwif_disable_hist_on_slot_and_input( uint8_t slot_id, uint8_t input_id )
{
    uint32_t tmp;
    acamera_frontend_mcfe_slot_cfg_valid_write( PHY_ADDR_ISP, slot_id, 0 );
    acamera_frontend_mcfe_input_stat_valid_write( PHY_ADDR_ISP, input_id, 0 );
    tmp = acamera_frontend_mcfe_slot_cfg_read_units_read( PHY_ADDR_ISP, slot_id );
    acamera_frontend_mcfe_slot_cfg_read_units_write( PHY_ADDR_ISP, slot_id, tmp & 0xfffffff0 ); // Disable slot hw2mem.
    tmp = acamera_frontend_mcfe_slot_cfg_write_units_read( PHY_ADDR_ISP, slot_id );
    acamera_frontend_mcfe_slot_cfg_write_units_write( PHY_ADDR_ISP, slot_id, tmp & 0xfffffff0 ); // Disable slot mem2hw.
    tmp = acamera_frontend_mcfe_input_stat_read_units_read( PHY_ADDR_ISP, input_id );
    acamera_frontend_mcfe_input_stat_read_units_write( PHY_ADDR_ISP, input_id, tmp & 0xfffffff0 ); // Disable input hw2mem.
    acamera_frontend_mcfe_slot_cfg_valid_write( PHY_ADDR_ISP, slot_id, 1 );
    acamera_frontend_mcfe_input_stat_valid_write( PHY_ADDR_ISP, input_id, 1 );
}

// Apply CDMA config.
void mcfe_hwif_slot_cfg_CDMA_config( uint8_t slot_id, uint32_t cdma_addr, uint8_t hist_position_is_be )
{
    if ( cdma_addr != (uint32_t)-1 ) {
        cdma_addr = ADDR_SYSPHY2ISPAS( cdma_addr );

        unsigned short ack = acamera_frontend_mcfe_slot_cfg_no_ack_read( PHY_ADDR_ISP );
        acamera_frontend_mcfe_slot_cfg_no_ack_write( PHY_ADDR_ISP, ack | ( 1 << slot_id ) );
        acamera_frontend_mcfe_slot_cfg_base_write( PHY_ADDR_ISP, slot_id, cdma_addr );
        acamera_frontend_mcfe_slot_cfg_size_write( PHY_ADDR_ISP, slot_id, LEN_ADDR_ISP );
    }

    uint32_t slot_reads = CDMA_UNIT_ANTIFOG_HIST | CDMA_UNIT_METERING_AE | CDMA_UNIT_METERING_AWB | CDMA_UNIT_IRIDIX;                                                                                                                                                                                                                                                                                                       // 0x1610
    uint32_t slot_writes = CDMA_UNIT_ISP_SETUP | CDMA_UNIT_BIST | CDMA_UNIT_GLOBAL_TM | CDMA_UNIT_METERING | CDMA_UNIT_IRIDIX_LUT | CDMA_UNIT_SINTER_RM | CDMA_UNIT_NOISE_PROFILES | CDMA_UNIT_ZONES_3A | CDMA_UNIT_GAMMA_BE | CDMA_UNIT_CA_MEMORY | CDMA_UNIT_OUT_FORMAT_LUT | CDMA_UNIT_RADIAL_SHADING_LUT | CDMA_UNIT_DEFECT_PIXEL_MEMORY | CDMA_UNIT_SHADING_MESH_MEMORY | CDMA_UNIT_IRIDIX | CDMA_UNIT_DEMOSAIC_RGBIR; // 0x3FF7D000

    if ( hist_position_is_be ) {
        slot_reads |= CDMA_UNIT_METERING_HIST_1 | CDMA_UNIT_METERING_HIST_2 | CDMA_UNIT_METERING_HIST_3 | CDMA_UNIT_METERING_HIST_4;
        slot_writes |= CDMA_UNIT_METERING_HIST_1 | CDMA_UNIT_METERING_HIST_2 | CDMA_UNIT_METERING_HIST_3 | CDMA_UNIT_METERING_HIST_4;
        LOG( LOG_DEBUG, "hist_position_is_be %d -> BE stats on slot", hist_position_is_be );
    }

    acamera_frontend_mcfe_slot_cfg_valid_write( PHY_ADDR_ISP, slot_id, 0 );
	//disable CDMA data from RAM to ISP by 10000058
	//slot_reads = 0;
    acamera_frontend_mcfe_slot_cfg_read_units_write( PHY_ADDR_ISP, slot_id, slot_reads );   // Stats read from isp before slot_stop.
    acamera_frontend_mcfe_slot_cfg_write_units_write( PHY_ADDR_ISP, slot_id, slot_writes ); // Cfg written to isp after slot_start.
    acamera_frontend_mcfe_slot_cfg_valid_write( PHY_ADDR_ISP, slot_id, 1 );
}

// Stats CDMA config.
void mcfe_hwif_slot_stat_CDMA_config( uint8_t input_id, uint32_t cdma_addr, uint8_t hist_position_is_be )
{
    if ( cdma_addr != (uint32_t)-1 ) {
        uint32_t size = LEN_ADDR_ISP - ( input_id * 2120 );
        cdma_addr = ADDR_SYSPHY2ISPAS( cdma_addr );

        // Input stats CDMA.
        unsigned short ack = acamera_frontend_mcfe_input_stat_no_ack_read( PHY_ADDR_ISP );
        acamera_frontend_mcfe_input_stat_no_ack_write( PHY_ADDR_ISP, ack | ( 1 << input_id ) );
        acamera_frontend_mcfe_input_stat_base_write( PHY_ADDR_ISP, input_id, cdma_addr );
        acamera_frontend_mcfe_input_stat_size_write( PHY_ADDR_ISP, input_id, size );
    }

    uint32_t input_reads = 0x0;
    if ( !hist_position_is_be ) {
        LOG( LOG_ERR, "hist_position_is_be %d -> FE stats on input", hist_position_is_be );
        input_reads |= ( 1 << input_id );
    }

    acamera_frontend_mcfe_input_stat_valid_write( PHY_ADDR_ISP, input_id, 0 );
    acamera_frontend_mcfe_input_stat_read_units_write( PHY_ADDR_ISP, input_id, input_reads );
    acamera_frontend_mcfe_input_stat_valid_write( PHY_ADDR_ISP, input_id, 1 );
}

/**
 * @brief      Returns a pointer to buffer register bank.
 *
 * @param[in]  type   Type of buffer
 * @param[in]  index  Index (range depends on type)
 *
 * @return     Pointer to #ISP_BUFFER_T or NULL if invalid parameters.
 *
 */
static ISP_BUFFER_T *mcfe_hwif_buff_get_ptr( const mcfe_hwif_buf_type_t bftype, const uint8_t idx )
{
    switch ( bftype ) {
    case MCFE_BUF_TYPE_RAW:
        if ( acamera_buffers_is_index_valid( ISP_RAW_BUFFERS, idx ) )
            return acamera_buffers_get_ptr( ISP_RAW_BUFFERS, idx );
        break;
    case MCFE_BUF_TYPE_OUT:
        if ( acamera_buffers_is_index_valid( ISP_OUT_BUFFERS, idx ) )
            return acamera_buffers_get_ptr( ISP_OUT_BUFFERS, idx );
        break;
    default:
        break;
    }

    LOG( LOG_ERR, "Invalid buffer type (%d) or index (%d).", bftype, idx );
    return NULL;
}


/**
 * @brief      Configures buffer
 *
 * @param[in]  bftype         The bftype
 * @param[in]  idx            The index
 * @param[in]  data_width     The data width
 * @param[in]  flags          The flags
 * @param[in]  base_address   The base address
 * @param[in]  line_offset    The line offset
 * @param[in]  active_width   The active width
 * @param[in]  active_height  The active height
 *
 */
void mcfe_hwif_buff_config( const mcfe_hwif_buf_type_t bftype,
                            const uint8_t idx,
                            uint8_t data_width,
                            uint8_t flags,
                            uint32_t base_address,
                            uint32_t line_offset,
                            uint16_t active_width,
                            uint16_t active_height )
{

    ISP_BUFFER_T *ptr = mcfe_hwif_buff_get_ptr( bftype, idx );

    if ( ptr == NULL ) {
        LOG( LOG_ERR, "No valid buffer pointer." );
        return;
    }

    acamera_buffers_data_width_write( ptr, data_width );
    acamera_buffers_infinite_flag_write( ptr, (bool)( flags & MCFE_BUF_FLAG_INFINITE ) );
    acamera_buffers_msb_align_flag_write( ptr, (bool)( flags & MCFE_BUF_FLAG_MSB_ALIGN ) );
    acamera_buffers_clone_flag_write( ptr, (bool)( flags & MCFE_BUF_FLAG_CLONE ) );
    acamera_buffers_pool_flag_write( ptr, (bool)( flags & MCFE_BUF_FLAG_POOL ) );
    acamera_buffers_base_address_write( ptr, ADDR_SYSPHY2ISPAS( base_address ) );
    acamera_buffers_line_offset_write( ptr, line_offset );
    acamera_buffers_active_width_write( ptr, active_width );
    acamera_buffers_active_height_write( ptr, active_height );
}

/**
 * @brief      Sets buffer base address.
 *
 * @param[in]  bftype        Buffer type
 * @param[in]  idx           Buffer index
 * @param[in]  base_address  The base address
 *
 */
void mcfe_hwif_buff_addr_set( const mcfe_hwif_buf_type_t bftype, const uint8_t idx, uint32_t base_address )
{

    ISP_BUFFER_T *ptr = mcfe_hwif_buff_get_ptr( bftype, idx );

    if ( ptr ) {
        acamera_buffers_base_address_write( ptr, ADDR_SYSPHY2ISPAS( base_address ) );
    } else {
        LOG( LOG_ERR, "No valid buffer pointer." );
    }
}

/**
 * @brief      Gets buffer base address.
 *
 * @param[in]  bftype        Buffer type
 * @param[in]  idx           Buffer index
 *
 */
uint32_t mcfe_hwif_buff_addr_get( const mcfe_hwif_buf_type_t bftype, const uint8_t idx )
{
    ISP_BUFFER_T *ptr = mcfe_hwif_buff_get_ptr( bftype, idx );

    if ( ptr ) {
        return ( acamera_buffers_base_address_read( ptr ) );
    } else {
        LOG( LOG_ERR, "No valid buffer pointer." );
        return 0;
    }
}

/**
 * @brief      Enables buffer
 *
 * @param[in]  bftype  The bftype
 * @param[in]  idx     The index
 * @param[in]  onoff   True to enable, false to disable.
 *
 */
void mcfe_hwif_buff_enable( const mcfe_hwif_buf_type_t bftype, const uint8_t idx, uint8_t onoff )
{
    ISP_BUFFER_T *ptr = mcfe_hwif_buff_get_ptr( bftype, idx );

    if ( ptr ) {
        acamera_buffers_valid_write( ptr, onoff );
    } else {
        LOG( LOG_ERR, "No valid buffer pointer." );
    }
}

/**
 * @brief      Sets bufffer status
 *
 * @param[in]  bftype  The bftype
 * @param[in]  idx     The index
 * @param[in]  status  The status
 *
 */
void mcfe_hwif_buff_status_set( const mcfe_hwif_buf_type_t bftype, const uint8_t idx, uint8_t status )
{

    ISP_BUFFER_T *ptr = mcfe_hwif_buff_get_ptr( bftype, idx );

    if ( ptr ) {
        acamera_buffers_status_write( ptr, status );
    } else {
        LOG( LOG_ERR, "No valid buffer pointer." );
    }
}

/**
 * @brief      Reads buffer status
 *
 * @param[in]  bftype  The bftype
 * @param[in]  idx     The index
 *
 * @return     Buffer status
 *
 */
uint8_t mcfe_hwif_buff_status_get( mcfe_hwif_buf_type_t bftype, const uint8_t idx )
{
    ISP_BUFFER_T *ptr = mcfe_hwif_buff_get_ptr( bftype, idx );

    if ( ptr ) {
        return acamera_buffers_status_read( ptr );
    } else {
        LOG( LOG_ERR, "No valid buffer pointer." );
        return 0;
    }
}
