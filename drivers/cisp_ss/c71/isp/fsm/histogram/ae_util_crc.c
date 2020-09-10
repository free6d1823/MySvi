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

#include "ae_util_crc.h"

#include "acamera_metering_mem_config.h"

#include "acamera_logger.h"
#include "util_crc16.h" //fast ccitt

#define HISTMEM_ADDITIONAL_DATA_ITEMS 11 /* not including crc */
#define AEMEM_ADDITIONAL_DATA_ITEMS 3    /* not including crc */

static uint16_t calc_AE_CRC_u32( histogram_fsm_ptr_t p_fsm )
{
    uint16_t crc16 = 0xffff;

    const uint8_t nodes_h = acamera_isp_metering_aexp_nodes_used_horiz_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
    const uint8_t nodes_v = acamera_isp_metering_aexp_nodes_used_vert_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
    const size_t items = ( nodes_h * nodes_v * 2 ) + AEMEM_ADDITIONAL_DATA_ITEMS;
    size_t i;

    for ( i = 0; i < items; i++ ) {
        const uint32_t data = acamera_metering_mem_array_data_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, i );
        crc16 = acrc_ccitt_byte( crc16, ( data >> 24 ) & 0xff );
        crc16 = acrc_ccitt_byte( crc16, ( data >> 16 ) & 0xff );
        crc16 = acrc_ccitt_byte( crc16, ( data >> 8 ) & 0xff );
        crc16 = acrc_ccitt_byte( crc16, ( data >> 0 ) & 0xff );
    }

    return crc16;
}

/*
 * Verify that the AE metering stats crc matches the one generated by hardware
 * returns 1 if CRCs match, 0 otherwise
 */
uint8_t ae_check_metering_stats_crc( histogram_fsm_ptr_t p_fsm )
{
    uint8_t match = 1;

    const uint8_t nodes_h = acamera_isp_metering_aexp_nodes_used_horiz_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );
    const uint8_t nodes_v = acamera_isp_metering_aexp_nodes_used_vert_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base );

    const size_t crc_index = ( nodes_h * nodes_v * 2 ) + AEMEM_ADDITIONAL_DATA_ITEMS;
    const uint32_t crc_hw = acamera_metering_mem_array_data_read( ACAMERA_FSM2ICTX_PTR( p_fsm )->settings.isp_base, crc_index );
    const uint32_t crc = (uint32_t)calc_AE_CRC_u32( p_fsm );

    if ( crc != crc_hw ) {
        LOG( LOG_ERR, "No CRC match for AE metering stats %x read, %x calced", crc_hw, crc );
        match = 0;
    } else {
        ;
    }

    return match;
}