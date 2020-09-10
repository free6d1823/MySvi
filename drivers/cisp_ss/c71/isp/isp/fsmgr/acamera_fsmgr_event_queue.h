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

#ifndef _ACAMERA_FSMGR_EVENT_QUEUE_H_
#define _ACAMERA_FSMGR_EVENT_QUEUE_H_

#include "acamera_loop_buf.h"

// If EVENT_QUEUE_EVENT_FLAG_FILTER is set only events of flagged event type will be pushed into the queue
// Filter is disabled on queue_pop()
#define EVENT_QUEUE_EVENT_FLAG_FILTER ( 1 )
#define EVENT_QUEUE_EVENT_FLAG_FSM_TYPE ( 2 )

typedef acamera_loop_buf_t acamera_event_queue_t;
typedef acamera_loop_buf_ptr_t acamera_event_queue_ptr_t;
typedef acamera_loop_buf_const_ptr_t acamera_event_queue_const_ptr_t;


static __inline void acamera_event_queue_init( acamera_event_queue_ptr_t p_queue, uint16_t *p_data_buf, int data_buf_size )
{
    system_spinlock_init( &p_queue->lock );
    acamera_loop_buffer_init( p_queue, p_data_buf, data_buf_size );
}

static __inline void acamera_event_queue_free( acamera_event_queue_ptr_t p_queue )
{
    system_spinlock_destroy( p_queue->lock );
}

void acamera_event_queue_push( acamera_event_queue_ptr_t p_queue, int event, unsigned int event_flags );
int acamera_event_queue_pop( acamera_event_queue_ptr_t p_queue );
int acamera_event_queue_is_empty( acamera_event_queue_ptr_t p_queue );
#endif /*_ACAMERA_FSMGR_EVENT_QUEUE_H_*/
