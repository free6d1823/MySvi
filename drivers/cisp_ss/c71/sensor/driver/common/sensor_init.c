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

#include "sensor_init.h"
#include "system_stdlib.h"
#include "system_timer.h"
#include "system_types.h"
#include "acamera_configuration.h"
#include "acamera_logger.h"

/*
0x01 -> set address
addr16

0x02 -> set address
addr32

0x10 -> add offset to address
ofs8

0x11 -> subtract offset from address
ofs8

0x2N -> write N+1 bytes
ofs8
b0
b1
..
bN

0x3N -> write N+1 bytes with mask
ofs8
b0
b1
..
bN
m0
m1
..
mN

0xE0 -> wait time8 milliseconds
time8

0xE1 -> wait time16 milliseconds
time16

0xE2 -> wait time32 milliseconds
time32

0xFN -> call N sequence

0x00 -> end of sequence
*/

static inline uint16_t sequence_read_u16( uint8_t *p )
{
    return ( ( ( uint16_t )( p[1] ) ) << 8 ) | p[0];
}
static inline uint32_t sequence_read_u32( uint8_t *p )
{
    return ( ( (uint32_t)sequence_read_u16( p + 2 ) ) << 16 ) | sequence_read_u16( p );
}

static inline void sequence_write_u16( uint8_t *p, uint16_t data )
{
    p[1] = ( uint8_t )( ( data >> 8 ) & 0xFF );
    p[0] = ( uint8_t )( ( data >> 0 ) & 0xFF );
}
static inline void sequence_write_u32( uint8_t *p, uint32_t data )
{
    p[3] = ( uint8_t )( ( data >> 24 ) & 0xFF );
    p[2] = ( uint8_t )( ( data >> 16 ) & 0xFF );
    p[1] = ( uint8_t )( ( data >> 8 ) & 0xFF );
    p[0] = ( uint8_t )( ( data >> 0 ) & 0xFF );
}

#define SENSOR_SEQUENCE_GET_GROUP( sequence, group ) \
    ( ( (uint8_t *)( sequence ) ) + sequence_read_u16( ( (uint8_t *)( sequence ) ) + group * 2 ) )

static void sensor_write_data( acamera_sbus_ptr_t p_sbus, uint32_t isp_offset, uint32_t addr, uint8_t *data, int len )
{
    if ( !len ) {
        return;
    }

    addr = addr + isp_offset;

    if ( addr & 1 ) {
        acamera_sbus_write_u8( p_sbus, ( addr ), data[0] );
        sensor_write_data( p_sbus, isp_offset, addr + 1, data + 1, len - 1 );
    } else {
        int i, ofs;
        int count = len >> 2;
        for ( i = 0, ofs = 0; i < count; ++i, ofs += 4 ) {
            acamera_sbus_write_u32( p_sbus, ( addr + ofs ), sequence_read_u32( data + ofs ) );
        }
        addr += ofs;
        data += ofs;
        len -= ofs;
        count = len >> 1;
        for ( i = 0, ofs = 0; i < count; ++i, ofs += 2 ) {
            acamera_sbus_write_u16( p_sbus, ( addr + ofs ), sequence_read_u16( data + ofs ) );
        }
        addr += ofs;
        data += ofs;
        len -= ofs;
        for ( i = 0; i < len; ++i ) {
            acamera_sbus_write_u8( p_sbus, ( addr + i ), data[i] );
        }
    }
}

static void sensor_read_data_mask( acamera_sbus_ptr_t p_sbus, uint32_t addr, uint8_t *data, int len )
{
    if ( !len ) {
        return;
    } else {
        int i, ofs;
        int count = len >> 2;
        for ( i = 0, ofs = 0; i < count; ++i, ofs += 4 ) {
            uint32_t sdata = acamera_sbus_read_u32( p_sbus, ( addr + ofs ) );
            uint32_t wdata = sequence_read_u32( data + ofs );
            uint32_t mask = sequence_read_u32( data + len + ofs );
            sequence_write_u32( data + ofs, ( sdata & ~mask ) | ( wdata & mask ) );
        }
        count = ( len - ofs ) >> 1;
        for ( i = 0; i < count; ++i, ofs += 2 ) {
            uint16_t sdata = acamera_sbus_read_u16( p_sbus, ( addr + ofs ) );
            uint16_t wdata = sequence_read_u16( data + ofs );
            uint16_t mask = sequence_read_u16( data + len + ofs );
            sequence_write_u16( data + ofs, ( sdata & ~mask ) | ( wdata & mask ) );
        }
        for ( i = 0; i < len - ofs; ++i ) {
            uint8_t sdata = acamera_sbus_read_u8( p_sbus, ( addr + ofs + i ) );
            uint8_t wdata = *( data + ofs + i );
            uint8_t mask = *( data + len + ofs + i );
            *( data + ofs + i ) = ( sdata & ~mask ) | ( wdata & mask );
        }
    }
}

void load_binary_sequence( acamera_sbus_ptr_t p_sbus, uint32_t isp_offset, char size, const char *sequence, int group )
{
    uint32_t addr = 0;
    uint8_t *p = (uint8_t *)SENSOR_SEQUENCE_GET_GROUP( sequence, group );
    for ( ;; ) {
        uint8_t cmd = *( p++ );
        switch ( cmd ) {
        case 0:
            return;
        case 0x01: {
            addr = sequence_read_u16( p );
            p += 2;
        } break;
        case 0x02: {
            addr = sequence_read_u32( p );
            p += 4;
        } break;
        case 0x10: {
            addr += ( *( p++ ) );
        } break;
        case 0x11: {
            addr -= ( *( p++ ) );
        } break;
        case 0xE0: {
            uint8_t time = *( p++ );
            system_timer_usleep( time );
        } break;
        case 0xE1: {
            uint16_t time = sequence_read_u16( p );
            p += 2;
            system_timer_usleep( time );
        } break;
        case 0xE2: {
            uint32_t time = sequence_read_u32( p );
            p += 4;
            system_timer_usleep( time );
        } break;
        default:
            switch ( cmd >> 4 ) {
            case 0x2: {
                int len = ( cmd & 0x0F ) + 1;
                int ofs = ( *( p++ ) );
                sensor_write_data( p_sbus, isp_offset, addr + ofs, p, len );
                p += len;
            } break;
            case 0x3: {
                int len = ( cmd & 0x0F ) + 1;
                int ofs = ( *( p++ ) );
                if ( len <= 4 ) {
                    uint8_t buf[8];
                    system_memcpy( buf, p, 2 * len );
                    sensor_read_data_mask( p_sbus, isp_offset + addr + ofs, buf, len );
                    sensor_write_data( p_sbus, isp_offset, addr + ofs, buf, len );
                } else {
                    LOG( LOG_ERR, "Cannot apply mask for data more then 4 bytes." );
                }
                p += 2 * len;
            } break;
            case 0xF:
                sensor_load_binary_sequence( p_sbus, size, sequence, cmd & 0x0F );
                break;
            }
        }
    }
}


void load_array_sequence( acamera_sbus_ptr_t p_sbus, uint32_t isp_offset, char size, const sensor_reg_t *sequence, int group_start_idx )
{
    const sensor_reg_t *seq = &sequence[group_start_idx]; // The address of the first element of group.
    uint32_t end_seq = 0;
    while ( end_seq == 0 ) {
        uint32_t cmd = seq->address;
        uint32_t val = seq->value;
        switch ( cmd ) {
        case 0xFFFF: // Wait command
            // Time is given in milliseconds. convert to microseconds interval.
            val *= 1000;
            system_timer_usleep( val );
            break;
        case 0x0000: // Sequence end flag.
            end_seq = 1;
            break;
        default:
            sensor_write_data( p_sbus, isp_offset, cmd, (uint8_t *)&val, size );
            break;
        }
        seq++;
    }
}


void sensor_load_binary_sequence( acamera_sbus_ptr_t p_sbus, char size, const char *sequence, int group )
{
    load_binary_sequence( p_sbus, 0, size, sequence, group );
}


void sensor_load_array_sequence( acamera_sbus_ptr_t p_sbus, char size, const sensor_reg_t *sequence, int group_start_idx )
{
    load_array_sequence( p_sbus, 0, size, sequence, group_start_idx );
}
