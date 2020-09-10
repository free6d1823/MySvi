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

#include "acamera_fsmgr_event_queue.h"
#include "acamera_logger.h"

#define SET_EVENT_FLAGS( event, flags ) ( ( event ) |= ( ( (flags)&0xFF ) << 8 ) )
#define GET_EVENT_FLAGS( event ) ( ( (event)&0xFF00 ) >> 8 )
#define GET_EVENT( event ) ( (event)&0xFF )

void acamera_event_queue_push( acamera_event_queue_ptr_t p_queue, int event, unsigned int event_flags )
{
    unsigned long flags;
    flags = system_spinlock_lock( p_queue->lock );

    if ( p_queue->head < 0 || p_queue->head >= p_queue->data_buf_size ||
         p_queue->tail < 0 || p_queue->tail >= p_queue->data_buf_size ) {
        LOG( LOG_ERR, "Event Queue Corrupted" );
    }

    if ( ( p_queue->filter == 0 ) || ( p_queue->filter & event_flags ) ) {

        if ( event_flags ) {
            SET_EVENT_FLAGS( event, event_flags );
        }

        if ( event_flags & EVENT_QUEUE_EVENT_FLAG_FILTER ) {

            // Check if current flags don't exceed maximum size
            if ( ( p_queue->filter_max & event_flags ) != event_flags ) {

                LOG( LOG_ERR, "Event flags exceed maximum value and will be truncated (event id: %d, flags: 0x%x, flags_max: 0x%x).",
                     event,
                     event_flags,
                     p_queue->filter_max );

                event_flags &= p_queue->filter_max;
            }

            p_queue->filter |= event_flags;

            // Updating counters
            int event_flag_counter = 0;
            while ( event_flags ) {
                if ( event_flags & 0x1 ) {
                    // Increase counter if flag bit is set
                    p_queue->filter_counters[event_flag_counter]++;
                }
                event_flag_counter++;
                event_flags >>= 1;
            }
        }

        int pos = acamera_loop_buffer_write( p_queue, 0, (uint16_t)event );
        if ( pos != p_queue->tail ) {
            p_queue->head = pos;
        } else {
            LOG( LOG_CRIT, "Event Queue overflow" );
        }
    }

    system_spinlock_unlock( p_queue->lock, flags );
}

int acamera_event_queue_pop( acamera_event_queue_ptr_t p_queue )
{
    unsigned long flags;
    flags = system_spinlock_lock( p_queue->lock );

    if ( p_queue->head == p_queue->tail ) {
        system_spinlock_unlock( p_queue->lock, flags );
        return -1;
    }

    if ( p_queue->head < 0 || p_queue->head >= p_queue->data_buf_size ||
         p_queue->tail < 0 || p_queue->tail >= p_queue->data_buf_size ) {
        LOG( LOG_ERR, "Event Queue Corrupted" );
    }

    uint16_t sample = acamera_loop_buffer_read( p_queue, 0 );
    int event = GET_EVENT( sample );
    unsigned int event_flags = GET_EVENT_FLAGS( sample );

    int pos = p_queue->tail + 1;
    if ( pos >= p_queue->data_buf_size ) {
        pos -= p_queue->data_buf_size;
    }
    p_queue->tail = pos;

    if ( event_flags ) {
        if ( event_flags & EVENT_QUEUE_EVENT_FLAG_FILTER ) {

            // Check if current flags don't exceed maximum size
            if ( ( p_queue->filter_max & event_flags ) != event_flags ) {

                LOG( LOG_ERR, "Event flags exceed maximum value and will be truncated (event id: %d, flags: 0x%x, flags_max: 0x%x).",
                     event,
                     event_flags,
                     p_queue->filter_max );

                event_flags &= p_queue->filter_max;
            }

            int event_flag_counter = 0;
            while ( event_flags ) {
                if ( event_flags & 0x1 ) {
                    // Update filter counter. Decrease counter if flag bit is set
                    if ( p_queue->filter_counters[event_flag_counter] > 0 ) {
                        p_queue->filter_counters[event_flag_counter]--;
                    }

                    // Clear filter flag bit if counter is zero
                    if ( p_queue->filter_counters[event_flag_counter] == 0 ) {
                        p_queue->filter &= ~( 1UL << event_flag_counter );
                    }
                }

                event_flag_counter++;
                event_flags >>= 1;
            }
        }
    }

    system_spinlock_unlock( p_queue->lock, flags );

    return event;
}

int acamera_event_queue_is_empty( acamera_event_queue_ptr_t p_queue )
{
    return p_queue->head == p_queue->tail;
}
