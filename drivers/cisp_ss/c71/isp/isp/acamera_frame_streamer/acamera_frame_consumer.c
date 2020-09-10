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

#include "acamera_frame_consumer.h"

#include "acamera_frame_stream_api.h"
#include "acamera_logger.h"

#define TEST_DOUBLE_BUFFER 0

#if TEST_DOUBLE_BUFFER
#include "system_timer.h"
#endif

static void frame_consumer_do_frame( const int ctx_id, const aframe_type_t type, aframe_t *frame )
{
    (void)frame;
    (void)type;
    (void)frame;

#if TEST_DOUBLE_BUFFER
    {
        const size_t freq = 50; //Delay every 50 frames
        static size_t running_counter = 0;
        if ( ( ++running_counter % freq ) == 0 ) {
            system_timer_usleep( 20 * 1000 );
            LOG( LOG_NOTICE, "Frame consumer double buffering test, injecting 20ms delay." );
        }
    }
#endif
}

static void frame_consumer_filled_notify_callback( const int ctx_id, const aframe_type_t type )
{
    aframe_t *frame = NULL;
    int rc = frame_stream_app_get_frame( ctx_id, type, &frame );
    if ( rc != 0 ) {
        LOG( LOG_CRIT, "frame_stream_isp_get_frame failed rc %d", rc );
        return;
    }

    frame_consumer_do_frame( ctx_id, type, frame );

    // We're done with the frame, put it back
    rc = frame_stream_app_put_frame( frame );
    if ( rc != 0 ) {
        LOG( LOG_CRIT, "frame_stream_isp_put_frame failed rc %d", rc );
        return;
    }
}

int frame_consumer_initialize( void )
{
    int rc = frame_stream_register_notify_callback( frame_consumer_filled_notify_callback );
    if ( rc != 0 ) {
        LOG( LOG_CRIT, "frame_stream_register_notify_callback failed rc %d", rc );
    }
    return rc;
}
