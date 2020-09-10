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

#include "system_cma.h"
#include "system_stdlib.h"
#include "acamera_frame_stream_api.h"
#include "acamera_logger.h"
#include "framestream.h"

// Space reserved for both active and reclaim pools of FRAME_STREAM_MAX_FRAMES size each
#define FRAME_STORAGE_SIZE ( FRAME_STREAM_MAX_FRAMES * 2 )

typedef struct {
    framestream ctx;
    aframe_t frame_storage[FRAME_STORAGE_SIZE];
    bool initialised;
} streamer_ctx_el;

typedef struct {
    streamer_ctx_el out_ctx[FIRMWARE_CONTEXT_NUMBER];
    streamer_ctx_el raw_ctx[FIRMWARE_CONTEXT_NUMBER];
} streamer_ctx;

static frame_stream_notify_callback g_full_frame_callback = NULL;
static streamer_ctx g_str_ctx;

static streamer_ctx_el *frame_stream_get_ctx_el_unchecked( const int ctx_id, const aframe_type_t type )
{
    switch ( type ) {
    case AFRAME_TYPE_OUT:
        return &g_str_ctx.out_ctx[ctx_id];
    case AFRAME_TYPE_RAW:
        return &g_str_ctx.raw_ctx[ctx_id];
    default:
        LOG( LOG_ERR, "Invalid frame type." );
        return NULL;
    }
}

static inline streamer_ctx_el *frame_stream_get_ctx_el( const int ctx_id, const aframe_type_t type )
{
    streamer_ctx_el *el = frame_stream_get_ctx_el_unchecked( ctx_id, type );
    return ( el != NULL && el->initialised ) ? el : NULL;
}

static inline framestream *frame_stream_get_ctx( const int ctx_id, const aframe_type_t type )
{
    streamer_ctx_el *el = frame_stream_get_ctx_el( ctx_id, type );
    return ( el != NULL ) ? &el->ctx : NULL;
}

int frame_stream_app_get_frame( const int ctx_id, const aframe_type_t type, aframe_t **frame )
{
    if ( ctx_id < 0 || ctx_id >= FIRMWARE_CONTEXT_NUMBER ) {
        LOG( LOG_ERR, "Invalid parameter. Context id (%d) is out of range (0-%d).", ctx_id, FIRMWARE_CONTEXT_NUMBER - 1 );
        return -1;
    } else if ( frame == NULL ) {
        LOG( LOG_ERR, "Invalid parameter. Frame pointer is NULL." );
        return -1;
    }

    framestream *ctx = frame_stream_get_ctx( ctx_id, type );
    if ( ctx == NULL ) {
        LOG( LOG_ERR, "Failed to get frame stream context (type: %d) pointer, returned NULL.", type );
        return -1;
    }

    *frame = framestream_dequeue_filled( ctx );
    return ( *frame != NULL ) ? 0 : -1;
}

int frame_stream_app_put_frame( aframe_t *frame )
{
    if ( frame == NULL ) {
        LOG( LOG_ERR, "Invalid parameter. Frame pointer is NULL." );
        return -1;
    }

    framestream *ctx = frame_stream_get_ctx( frame->context_id, frame->type );
    if ( ctx == NULL ) {
        LOG( LOG_ERR, "Failed to get frame stream context (type: %d) pointer, returned NULL.", frame->type );
        return -1;
    }

    return framestream_enqueue_empty( ctx, frame );
}

int frame_stream_isp_get_frame( const int ctx_id, const aframe_type_t type, aframe_t **frame )
{
    if ( ctx_id < 0 || ctx_id >= FIRMWARE_CONTEXT_NUMBER ) {
        LOG( LOG_ERR, "Invalid parameter. Context id (%d) is out of range (0-%d).", ctx_id, FIRMWARE_CONTEXT_NUMBER - 1 );
        return -1;
    } else if ( frame == NULL ) {
        LOG( LOG_ERR, "Invalid parameter. Frame pointer is NULL." );
        return -1;
    }

    framestream *ctx = frame_stream_get_ctx( ctx_id, type );
    if ( ctx == NULL ) {
        LOG( LOG_ERR, "Failed to get frame stream context (type: %d) pointer, returned NULL.", type );
        return -1;
    }

    *frame = framestream_dequeue_empty( ctx );
    return ( *frame != NULL ) ? 0 : -1;
}

int frame_stream_isp_put_frame( aframe_t *frame )
{
    int ret;

    if ( frame == NULL ) {
        LOG( LOG_ERR, "Invalid parameter. Frame pointer is NULL." );
        return -1;
    }

    switch ( frame->type ) {
    case AFRAME_TYPE_OUT:
        if ( frame->state == AFRAME_STATE_FULL ) {
            ret = framestream_enqueue_filled( &g_str_ctx.out_ctx[frame->context_id].ctx, frame );
            if ( ret ) {
                return -1;
            }

            if ( g_full_frame_callback && g_str_ctx.out_ctx[frame->context_id].initialised ) {
                g_full_frame_callback( frame->context_id, frame->type );
            }
        } else {
            ret = framestream_enqueue_empty( &g_str_ctx.out_ctx[frame->context_id].ctx, frame );
            if ( ret ) {
                return -1;
            }
        }

        break;
    case AFRAME_TYPE_RAW:
        if ( frame->state == AFRAME_STATE_FULL ) {
            ret = framestream_enqueue_filled( &g_str_ctx.raw_ctx[frame->context_id].ctx, frame );
            if ( ret ) {
                return -1;
            }

            if ( g_full_frame_callback && g_str_ctx.raw_ctx[frame->context_id].initialised ) {
                g_full_frame_callback( frame->context_id, frame->type );
            }
        } else {
            ret = framestream_enqueue_empty( &g_str_ctx.raw_ctx[frame->context_id].ctx, frame );
            if ( ret ) {
                return -1;
            }
        }

        break;
    default:
        LOG( LOG_ERR, "Invalid frame type (%d).", frame->type );
        return -1;
    }
    return 0;
}

int frame_stream_register_notify_callback( frame_stream_notify_callback callback )
{
    if ( callback == NULL ) {
        LOG( LOG_ERR, "Invalid parameter. Callback function pointer is NULL" );
        return -1;
    }

    g_full_frame_callback = callback;
    return 0;
}

int frame_stream_create( const frame_stream_cfg_t *stream_cfg )
{
    framestream_cfg_t frms_cfg;

    if ( stream_cfg == NULL ) {
        LOG( LOG_ERR, "Invalid parameter. Frame stream configuration pointer is NULL." );
        return -1;
    } else if ( !stream_cfg->num_frames ) {
        LOG( LOG_ERR, "Invalid parameter. Requested number of frames is zero." );
        return -1;
    }

    system_memset( &frms_cfg, 0, sizeof( frms_cfg ) );

    streamer_ctx_el *ctx_el = frame_stream_get_ctx_el_unchecked( stream_cfg->context_id, stream_cfg->type );
    if ( !ctx_el ) {
        return -1;
    }

    frms_cfg.context_id = stream_cfg->context_id;
    frms_cfg.num_planes = stream_cfg->num_planes;
    frms_cfg.type = stream_cfg->type;
    frms_cfg.num_frames = stream_cfg->num_frames;

    if ( frms_cfg.num_frames > FRAME_STREAM_MAX_FRAMES ) {
        LOG( LOG_WARNING, "Requested number of frames (%u) is larger than maximum allowed size (%d). Value will be clipped to (%d).",
             frms_cfg.num_frames,
             FRAME_STREAM_MAX_FRAMES,
             FRAME_STREAM_MAX_FRAMES );

        frms_cfg.num_frames = FRAME_STREAM_MAX_FRAMES;
    }

    int i;
    for ( i = 0; i < stream_cfg->num_planes; ++i ) {
        framestream_plane_cfg_t *tplane = &frms_cfg.planes[i];
        const frame_stream_plane_cfg_t *mplane = &stream_cfg->planes[i];

        tplane->height = mplane->height;
        tplane->width = mplane->width;
        tplane->data_width = mplane->data_width;
        tplane->line_offset = mplane->line_offset;
        tplane->hw_cfg = mplane->hw_cfg;
    }

    framestream_create( &ctx_el->ctx, ctx_el->frame_storage, FRAME_STORAGE_SIZE, &frms_cfg );
    ctx_el->initialised = 1;

    return 0;
}

int frame_stream_destroy( const int ctx_id, const aframe_type_t type, const int force )
{
    streamer_ctx_el *ctx_el = frame_stream_get_ctx_el( ctx_id, type );
    if ( ctx_el == NULL ) {
        LOG( LOG_ERR, "Failed to get frame stream context element (context id: %d, type: %d) pointer, returned NULL.",
             ctx_id, type );
        return -1;
    }

    framestream_destroy( &ctx_el->ctx, force );
    ctx_el->initialised = 0;

    return 0;
}
