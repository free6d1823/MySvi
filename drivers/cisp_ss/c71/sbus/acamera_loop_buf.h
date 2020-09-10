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

#ifndef __ACAMERA_LOOP_BUF_H__
#define __ACAMERA_LOOP_BUF_H__

#include "system_spinlock.h"

// Number of bits reserved for filter bits
#define ACAMERA_LOOP_BUFFER_FILTER_MAX_BITS ( 8 )

typedef struct _acamera_loop_buf_t acamera_loop_buf_t;
typedef struct _acamera_loop_buf_t *acamera_loop_buf_ptr_t;
typedef const struct _acamera_loop_buf_t *acamera_loop_buf_const_ptr_t;

struct _acamera_loop_buf_t {
    volatile int head;
    volatile int tail;
    volatile unsigned int filter;
    volatile unsigned int filter_max;
    volatile unsigned int filter_counters[ACAMERA_LOOP_BUFFER_FILTER_MAX_BITS];
    uint16_t *p_data_buf;
    int data_buf_size;
    sys_spinlock lock;
};

void acamera_loop_buffer_init( acamera_loop_buf_ptr_t p_buf, uint16_t *p_data_buf, int data_buf_size );
uint16_t acamera_loop_buffer_read( acamera_loop_buf_ptr_t p_buf, int pos );
int acamera_loop_buffer_write( acamera_loop_buf_ptr_t p_buf, int pos, uint16_t sample );

#endif /* __ACAMERA_LOOP_BUF_H__ */
