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

#include "acamera_loop_buf.h"
#include "bitop.h"

void acamera_loop_buffer_init( acamera_loop_buf_ptr_t p_buf, uint16_t *p_data_buf, int data_buf_size )
{
    p_buf->head = p_buf->tail = 0;
    p_buf->filter = 0;
    p_buf->filter_max = BITFIELD( ACAMERA_LOOP_BUFFER_FILTER_MAX_BITS );
    p_buf->p_data_buf = p_data_buf;
    p_buf->data_buf_size = data_buf_size;

    int i;
    for ( i = 0; i < ACAMERA_LOOP_BUFFER_FILTER_MAX_BITS; i++ ) {
        p_buf->filter_counters[i] = 0;
    }
}

uint16_t acamera_loop_buffer_read( acamera_loop_buf_ptr_t p_buf, int pos )
{
    pos += p_buf->tail;
    if ( pos >= p_buf->data_buf_size ) {
        pos -= p_buf->data_buf_size;
    }

    return p_buf->p_data_buf[pos];
}

int acamera_loop_buffer_write( acamera_loop_buf_ptr_t p_buf, int pos, uint16_t sample )
{
    pos += p_buf->head;
    if ( pos >= p_buf->data_buf_size ) {
        pos -= p_buf->data_buf_size;
    }

    p_buf->p_data_buf[pos++] = sample;

    if ( pos >= p_buf->data_buf_size ) {
        pos -= p_buf->data_buf_size;
    }

    return pos;
}
