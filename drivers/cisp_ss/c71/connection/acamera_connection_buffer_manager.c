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

#include "acamera_connection_buffer_manager.h"
#include "system_types.h"
#include "acamera_cmd_queues_config.h"
#include "acamera_connection.h"
#include "acamera_logger.h"
#include "acamera_math.h"


#define OFFSET_BASE 12                       // 12 is the size of api cmd/api ack fields, each at offset 0
#define OFFSET_STATE ( OFFSET_BASE + 0 )     // offset of state register in the memory
#define OFFSET_WRITE_INX ( OFFSET_BASE + 4 ) // offset of write index register in the memory
#define OFFSET_READ_INX ( OFFSET_BASE + 8 )  // offset of read index register in the memory
#define OFFSET_DATA ( OFFSET_BASE + 12 )     // actual data offset in the memory

#ifndef MIN
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif
enum {
    FW_IS_RESET = 0,
    CHANNEL_REQUESTED,
    CHANNEL_ACKNOWLEDGE,
    WRITE_REGISTER_UPDATED,
    READ_REGISTER_UPDATED
};

static void read_portion( uint32_t addr, uint32_t *data, uint32_t size )
{
    while ( size >= 4 ) {
        *data++ = system_isp_read_32( PHY_ADDR_ISP + addr );
        addr += 4;
        size -= 4;
    }
}

static void write_portion( uint32_t addr, const uint32_t *data, uint32_t size )
{
    while ( size >= 4 ) {
        system_isp_write_32( PHY_ADDR_ISP + addr, *data++ );
        addr += 4;
        size -= 4;
    }
}

static void set_value( uint32_t addr, uint32_t data )
{
    data = ( data & 0xFFFF ) | ( data << 16 );
    system_isp_write_32( PHY_ADDR_ISP + addr, data );
}

#define ERROR_VALUE 0xFFFFFFFF

static uint32_t get_value( uint32_t addr, int check )
{
    uint32_t res = 0;
    if ( check ) {
        int cnt = 10; // do this only some time
        do {
            read_portion( addr, &res, sizeof( uint32_t ) );
        } while ( ( res & 0xFFFF ) != ( res >> 16 ) && --cnt );
        if ( cnt )
            return res & 0xFFFF;
        else
            return ERROR_VALUE;
    } else {
        read_portion( addr, &res, sizeof( uint32_t ) );
        return res & 0xFFFF;
    }
}

void acamera_buffer_manager_init( acamera_buffer_manager_t *p_ctrl, uint32_t base, uint32_t size )
{
    p_ctrl->rx_base = base;
    p_ctrl->tx_base = base + size;
    p_ctrl->data_size = size - OFFSET_DATA;
    set_value( p_ctrl->rx_base + OFFSET_STATE, FW_IS_RESET ); // notify sender that we are reset
    set_value( p_ctrl->tx_base + OFFSET_STATE, FW_IS_RESET );
    set_value( p_ctrl->rx_base + OFFSET_READ_INX, 0 );  // reset index
    set_value( p_ctrl->tx_base + OFFSET_WRITE_INX, 0 ); // reset index
    p_ctrl->rx_ack = 0;
    p_ctrl->tx_ack = 0;
    LOG( LOG_INFO, "FW bus channel is reset" );
}

int acamera_buffer_manager_read( acamera_buffer_manager_t *p_ctrl, uint8_t *data, int size )
{
    uint32_t wr_inx, rd_inx, available, read_size;
    uint32_t state = get_value( p_ctrl->rx_base + OFFSET_STATE, 0 );
    switch ( state ) {
    case FW_IS_RESET:
    case CHANNEL_ACKNOWLEDGE:
    case ERROR_VALUE:
        return 0;
    case CHANNEL_REQUESTED:
        LOG( LOG_INFO, "Accepted channel request on RX part. Reset receiver" );
        set_value( p_ctrl->rx_base + OFFSET_READ_INX, 0 );                // reset index
        set_value( p_ctrl->rx_base + OFFSET_STATE, CHANNEL_ACKNOWLEDGE ); // notify sender that we accept chanel
        p_ctrl->rx_ack = 1;
        return BUS_ERROR_RESET;
    case WRITE_REGISTER_UPDATED:
    case READ_REGISTER_UPDATED:
        if ( p_ctrl->rx_ack ) {
            wr_inx = get_value( p_ctrl->rx_base + OFFSET_WRITE_INX, 1 );
            rd_inx = get_value( p_ctrl->rx_base + OFFSET_READ_INX, 1 );
            if ( wr_inx == ERROR_VALUE || rd_inx == ERROR_VALUE ) return 0;
            available = ( wr_inx >= rd_inx ) ? wr_inx - rd_inx : wr_inx + p_ctrl->data_size - rd_inx; // available data size
            if ( !available ) return 0;
            //printf("rx: wr_inx %ld, rd_inx %ld, available %ld",wr_inx,rd_inx,available);
            if ( size > available ) size = available;                                            // limit requested size to avalable amount
            read_size = MIN( size, p_ctrl->data_size - rd_inx );                                 // calculate size of first portion of data
            read_portion( p_ctrl->rx_base + OFFSET_DATA + rd_inx, (uint32_t *)data, read_size ); // read first portion of data
            rd_inx += read_size;                                                                 // update read index
            if ( rd_inx >= p_ctrl->data_size ) rd_inx = 0;                                       // buffer roll over
            if ( read_size < size ) {
                uint32_t second_read = size - read_size;                                                               // calculate size of second portion of data
                read_portion( p_ctrl->rx_base + OFFSET_DATA + rd_inx, (uint32_t *)( data + read_size ), second_read ); // read second portion of data
                read_size += second_read;                                                                              // update read size
                rd_inx += second_read;                                                                                 // update read index
                if ( rd_inx >= p_ctrl->data_size ) rd_inx = 0;                                                         // buffer roll over
            }
            set_value( p_ctrl->rx_base + OFFSET_READ_INX, rd_inx );             // set new index
            set_value( p_ctrl->rx_base + OFFSET_STATE, READ_REGISTER_UPDATED ); // set flag
            LOG( LOG_DEBUG, "Received portion of data size %u", read_size );
            return read_size;
        } else {
            set_value( p_ctrl->rx_base + OFFSET_STATE, FW_IS_RESET ); // notify sender that we are in reset
            LOG( LOG_WARNING, "Request on non-established channel" );
            return 0;
        }
    }
    LOG( LOG_ERR, "Wrong channel state %u", state );
    p_ctrl->rx_ack = 0;
    return BUS_ERROR_FATAL;
}

int acamera_buffer_manager_write( acamera_buffer_manager_t *p_ctrl, const uint8_t *data, int size )
{
    uint32_t wr_inx, rd_inx, free_space, write_size;
    uint32_t state = get_value( p_ctrl->tx_base + OFFSET_STATE, 0 );
    switch ( state ) {
    case FW_IS_RESET:
        return 0;
    case CHANNEL_ACKNOWLEDGE:
        state = get_value( p_ctrl->rx_base + OFFSET_STATE, 0 );
        if ( state == CHANNEL_REQUESTED ) return BUS_ERROR_RESET;
        return 0;
    case ERROR_VALUE:
        return 0;
    case CHANNEL_REQUESTED:
        LOG( LOG_INFO, "Accepted channel request on TX part. Reset tramsmitter" );
        set_value( p_ctrl->tx_base + OFFSET_WRITE_INX, 0 );               // reset index
        set_value( p_ctrl->tx_base + OFFSET_STATE, CHANNEL_ACKNOWLEDGE ); // notify sender that we accept chanel
        p_ctrl->tx_ack = 1;                                               // first acknowlege, just return 0
        return 0;
    case WRITE_REGISTER_UPDATED:
    case READ_REGISTER_UPDATED:
        if ( p_ctrl->tx_ack ) {
            wr_inx = get_value( p_ctrl->tx_base + OFFSET_WRITE_INX, 1 );
            rd_inx = get_value( p_ctrl->tx_base + OFFSET_READ_INX, 1 );
            if ( wr_inx == ERROR_VALUE || rd_inx == ERROR_VALUE ) return 0;
            free_space = ( wr_inx >= rd_inx ) ? rd_inx - 4 - wr_inx + p_ctrl->data_size : rd_inx - 4 - wr_inx; // free space calculation
            //printf("tx: wr_inx %ld, rd_inx %ld, free_space %ld",wr_inx,rd_inx,free_space);
            if ( !free_space ) return 0;
            if ( size > free_space ) size = free_space;                                            // limit requested size to avalable amount
            write_size = MIN( size, p_ctrl->data_size - wr_inx );                                  // calculate size of first portion of data
            write_portion( p_ctrl->tx_base + OFFSET_DATA + wr_inx, (uint32_t *)data, write_size ); // write first portion of data
            wr_inx += write_size;                                                                  // update write index
            if ( wr_inx >= p_ctrl->data_size ) wr_inx = 0;                                         // buffer roll over
            if ( write_size < size ) {
                uint32_t second_write = size - write_size;                                                                // calculate size of second portion of data
                write_portion( p_ctrl->tx_base + OFFSET_DATA + wr_inx, (uint32_t *)( data + write_size ), second_write ); // write second portion of data
                write_size += second_write;                                                                               // update write amount
                wr_inx += second_write;                                                                                   // update write index
                if ( wr_inx >= p_ctrl->data_size ) wr_inx = 0;                                                            // buffer roll over
            }
            set_value( p_ctrl->tx_base + OFFSET_WRITE_INX, wr_inx );             // set new index
            set_value( p_ctrl->tx_base + OFFSET_STATE, WRITE_REGISTER_UPDATED ); // set flag
            LOG( LOG_DEBUG, "Written portion of data size %u, new wr_inx %u", write_size, wr_inx );
            return write_size;
        } else {
            set_value( p_ctrl->tx_base + OFFSET_STATE, FW_IS_RESET ); // notify sender that we are in reset
            LOG( LOG_WARNING, "Request on non-established channel" );
            return 0;
        }
    }
    LOG( LOG_ERR, "Wrong channel state %u", state );
    p_ctrl->tx_ack = 0;
    return BUS_ERROR_FATAL;
}
