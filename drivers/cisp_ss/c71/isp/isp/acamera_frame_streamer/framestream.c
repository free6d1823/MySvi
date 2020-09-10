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

#include "framestream.h"

#include "util_pool.h"
#include "util_queue.h"

#include "system_cma.h"
#include "system_semaphore.h"
#include "system_stdlib.h"
#include "system_types.h"
#include "acamera_aframe.h"
#include "acamera_logger.h"

#if 0//__KERNEL__

static inline void framestream_mutex_lock( framestream_mutex *m )
{
    mutex_lock( &m->lock );
}

static inline void framestream_mutex_unlock( framestream_mutex *m )
{
    mutex_unlock( &m->lock );
}

static inline void framestream_mutex_init( framestream_mutex *m )
{
    mutex_init( &m->lock );
}

#else

static inline void framestream_mutex_lock( framestream_mutex *m )
{
    (void)m;
}

static inline void framestream_mutex_unlock( framestream_mutex *m )
{
    (void)m;
}

static inline void framestream_mutex_init( framestream_mutex *m )
{
    (void)m;
}

#endif

static void framestream_deallocate_frame( aframe_t *frame )
{
    int i;

    for ( i = 0; i < frame->num_planes; ++i ) {
        if ( frame->planes[i].address ) {
            system_cma_free( frame->planes[i].address );
            frame->planes[i].address = 0;
        }
    }
}

static int framestream_alloc_frame( framestream_cfg_t *frm_cfg, aframe_t *frame )
{
    frame->context_id = frm_cfg->context_id;
    frame->type = frm_cfg->type;

    int i;
    for ( i = 0; i < frm_cfg->num_planes; ++i ) {
        aplane_t *tplane = &frame->planes[i];
        const framestream_plane_cfg_t *mplane = &frm_cfg->planes[i];

        const uint32_t data_size = mplane->line_offset * mplane->height;
        if ( !data_size ) {
            goto frame_alloc_failed;
        }

        tplane->height = mplane->height;
        tplane->width = mplane->width;
        tplane->data_width = mplane->data_width;
        tplane->line_offset = mplane->line_offset;
        tplane->hw_cfg = mplane->hw_cfg;
		if (AFRAME_TYPE_RAW == frame->type)
		{
			tplane->virt_addr = 0;
			if (0 == i)
				tplane->address = 0x61100000;//0x80000;//0x60000000 + 0x1400000 * 4;
			else if (1 == i)
				tplane->address = 0x61120000;
			else
				tplane->address = 0x61140000;
		}
		else if(AFRAME_TYPE_OUT == frame->type)
		{
			#if defined(AFBC_ENABLE)
				LOG (LOG_LEVEL_NOTICE, "AFBC enabled.");
				tplane->address = 0xf0200000;
			#else
				LOG (LOG_LEVEL_NOTICE, "AFBC bypass.");
        		int ret = system_cma_alloc( &tplane->virt_addr, &tplane->address, data_size );
				LOG (LOG_NOTICE, "allocate frame, address: 0x%2x, data_size: %d", &tplane->address, data_size);
        		if ( ret ) {
        		    LOG( LOG_ERR, "Failed to allocate frame, plane: %d, data size: %d", i, data_size );
        		    tplane->virt_addr = NULL;
        		    tplane->address = 0;
        		    goto frame_alloc_failed;
        		}
			#endif
		}
		else
		{
			LOG (LOG_LEVEL_NOTICE, "frame type: %d", frame->type);
		}
        frame->num_planes = i + 1;
    }

    return 0;

frame_alloc_failed:

    framestream_deallocate_frame( frame );

    return -1;
}

static int framestream_reclaim_frame( framestream *fsm, void *frame )
{
    framestream_mutex_lock( &fsm->reclaim_pool_lock );
    aframe_t *temp = apool_remove( &fsm->reclaim_pool, frame );
    framestream_mutex_unlock( &fsm->reclaim_pool_lock );
    if ( !temp ) {
        return -1;
    }

    LOG( LOG_DEBUG, "%s, frame (ptr: %p) removed from reclaim pool and going to be deallocated", __func__, temp );

    // Deallocating returned frame
    framestream_deallocate_frame( temp );

    return 0;
}

static int framestream_clear_from_pool( void *pool, aqueue *queue )
{
    const size_t queue_size = aqueue_size( queue );

    size_t i;
    for ( i = 0; i < queue_size; ++i ) {
        aframe_t *frame = (aframe_t *)aqueue_dequeue( queue );
        if ( frame == NULL ) {
            break;
        }

        if ( apool_remove( pool, frame ) == NULL ) {
            // This should never happen
            LOG( LOG_CRIT, "Frame is not present in the active pool, context id: %u, type: %u, id: %u, state: %u, ptr: %p.",
                 frame->context_id,
                 frame->type,
                 frame->frame_id,
                 frame->state,
                 frame );
            continue;
        }

        framestream_deallocate_frame( frame );
    }

    return 0;
}

static int framestream_clear_frames( framestream *fsm )
{
    // Clean empty_queue:
    framestream_mutex_lock( &fsm->empty_queue_lock );
    framestream_mutex_lock( &fsm->active_pool_lock );
    int ret = framestream_clear_from_pool( &fsm->active_pool, &fsm->empty_queue );
    framestream_mutex_unlock( &fsm->active_pool_lock );
    framestream_mutex_unlock( &fsm->empty_queue_lock );
    if ( ret ) {
        // Should not happen
        LOG( LOG_ERR, "Failed to clear empty queue of frames." );
    }

    //Clean filled_queue:
    framestream_mutex_lock( &fsm->filled_queue_lock );
    framestream_mutex_lock( &fsm->active_pool_lock );
    ret = framestream_clear_from_pool( &fsm->active_pool, &fsm->filled_queue );
    framestream_mutex_unlock( &fsm->active_pool_lock );
    framestream_mutex_unlock( &fsm->filled_queue_lock );
    if ( ret ) {
        // Should not happen
        LOG( LOG_ERR, "Failed to clear filled queue of frames." );
    }

    framestream_mutex_lock( &fsm->active_pool_lock );
    framestream_mutex_lock( &fsm->reclaim_pool_lock );
    int i, pool_size = apool_size( &fsm->active_pool );

    LOG( LOG_DEBUG, "%s, active pool size after queue cleanup: %d", __func__, pool_size );

    for ( i = 0; i < pool_size; ++i ) {
        void *temp = apool_remove_used( &fsm->active_pool );
        LOG( LOG_DEBUG, "%s, frame (ptr: %p) is going to reclaim pool", __func__, temp );
        apool_add( &fsm->reclaim_pool, temp );
    }
    framestream_mutex_unlock( &fsm->reclaim_pool_lock );
    framestream_mutex_unlock( &fsm->active_pool_lock );

    return 0;
}

int framestream_create( framestream *hndl, aframe_t *frame_storage, uint32_t frame_storage_size, framestream_cfg_t *frm_cfg )
{
    if ( !hndl || !frame_storage || !frm_cfg || !frame_storage_size ) {
        return -1;
    }

    hndl->max_frames = frm_cfg->num_frames;

    framestream_mutex_init( &hndl->filled_queue_lock );
    framestream_mutex_init( &hndl->empty_queue_lock );
    framestream_mutex_init( &hndl->active_pool_lock );
    framestream_mutex_init( &hndl->reclaim_pool_lock );

    aqueue_create( &hndl->empty_queue, (void **)hndl->empty_queue_data, hndl->max_frames );
    aqueue_create( &hndl->filled_queue, (void **)hndl->filled_queue_data, hndl->max_frames );

    apool_create( &hndl->active_pool, hndl->active_pool_elements, hndl->max_frames );

    // Reclaim pool should be reset only when empty;
    int ret = apool_size( &hndl->reclaim_pool );
    if ( !ret ) {
        apool_create( &hndl->reclaim_pool, hndl->reclaim_pool_elements, hndl->max_frames );
    }

    framestream_mutex_lock( &hndl->reclaim_pool_lock );
    ret = apool_size( &hndl->reclaim_pool );
    framestream_mutex_unlock( &hndl->reclaim_pool_lock );

    framestream_mutex_lock( &hndl->active_pool_lock );
    framestream_mutex_lock( &hndl->reclaim_pool_lock );
    framestream_mutex_lock( &hndl->empty_queue_lock );

    uint32_t i, j, frame_counter = 1;
    for ( i = 0, j = 0; ( i < frame_storage_size ) && ( j < frm_cfg->num_frames ); i++ ) {

        aframe_t *frame = &frame_storage[i];

        // Check Reclaim pool;
        ret = apool_contains( &hndl->reclaim_pool, frame );
        if ( !ret ) {
            LOG( LOG_DEBUG, "Frame (ptr: %p) is currently in use. Skipping...", frame );
            continue;
        }

        system_memset( frame, 0, sizeof( *frame ) );

        ret = framestream_alloc_frame( frm_cfg, frame );
        if ( ret ) {
            LOG( LOG_ERR, "Failed to allocate frame." );
            framestream_mutex_unlock( &hndl->empty_queue_lock );
            framestream_mutex_unlock( &hndl->reclaim_pool_lock );
            framestream_mutex_unlock( &hndl->active_pool_lock );
            goto frame_alloc_failed;
        }

        frame->frame_id = frame_counter++;

        apool_add( &hndl->active_pool, frame );
        aqueue_enqueue( &hndl->empty_queue, frame );

        j++;
    }

    if ( j != frm_cfg->num_frames ) {
        LOG( LOG_ERR, "Only %d out of %d frames allocated, not enough free entries in the frame storage.",
             j, frm_cfg->num_frames );
        goto frame_alloc_failed;
    }

    ret = apool_size( &hndl->active_pool );
    framestream_mutex_unlock( &hndl->empty_queue_lock );
    framestream_mutex_unlock( &hndl->reclaim_pool_lock );
    framestream_mutex_unlock( &hndl->active_pool_lock );

    return 0;

frame_alloc_failed:

    framestream_clear_frames( hndl );
    return -1;
}

void framestream_destroy( framestream *hndl, uint32_t force )
{
    if ( hndl == NULL ) {
        LOG( LOG_ERR, "Incorrect parameter. Frame stream handle is NULL." );
        return;
    }

    int ret = framestream_clear_frames( hndl );
    if ( ret ) {
        LOG( LOG_ERR, "Failed to deallocate frame queues." );
        return;
    }

    framestream_mutex_lock( &hndl->reclaim_pool_lock );
    ret = apool_size( &hndl->reclaim_pool );
    framestream_mutex_unlock( &hndl->reclaim_pool_lock );

    if ( force ) {
        framestream_mutex_lock( &hndl->reclaim_pool_lock );
        int i, reclaim_size = apool_size( &hndl->reclaim_pool );
        for ( i = 0; i < reclaim_size; ++i ) {
            aframe_t *frame = (aframe_t *)apool_remove_used( &hndl->reclaim_pool );
            if ( frame != NULL ) {
                framestream_deallocate_frame( frame );
            }
        }

        ret = apool_size( &hndl->reclaim_pool );
        framestream_mutex_unlock( &hndl->reclaim_pool_lock );
    }
}

int framestream_enqueue_empty( framestream *hndl, aframe_t *frame )
{
    if ( hndl == NULL || frame == NULL ) {
        LOG( LOG_ERR, "Incorrect parameter. One or more parameters are NULL." );
        return -1;
    }

    int ret = framestream_reclaim_frame( hndl, frame );
    if ( !ret ) {
        LOG( LOG_DEBUG, "%s, frame (ptr: %p) reclaimed and will not be enqueued.", __func__, frame );
        return ret;
    }

    framestream_mutex_lock( &hndl->empty_queue_lock );
    ret = aqueue_enqueue( &hndl->empty_queue, frame );
    framestream_mutex_unlock( &hndl->empty_queue_lock );

    if ( ret ) {
        LOG( LOG_ERR, "Failed to add frame to the empty queue." );
        return -1;
    }

    return ret;
}

aframe_t *framestream_dequeue_empty( framestream *hndl )
{
    if ( hndl == NULL ) {
        LOG( LOG_ERR, "Incorrect parameter. Frame stream handle is NULL." );
        return NULL;
    }

    framestream_mutex_lock( &hndl->empty_queue_lock );
    aframe_t *frame = (aframe_t *)aqueue_dequeue( &hndl->empty_queue );
    framestream_mutex_unlock( &hndl->empty_queue_lock );

    if ( frame ) {
        frame->state = AFRAME_STATE_EMPTY;
    }

    return frame;
}

int framestream_enqueue_filled( framestream *hndl, aframe_t *frame )
{
    if ( hndl == NULL || frame == NULL ) {
        LOG( LOG_ERR, "Incorrect parameter. One or more parameters are NULL." );
        return -1;
    }

    int ret = framestream_reclaim_frame( hndl, frame );
    if ( !ret ) {
        LOG( LOG_DEBUG, "%s, frame (ptr: %p) reclaimed and will not be enqueued.", __func__, frame );
        return ret;
    }

    framestream_mutex_lock( &hndl->filled_queue_lock );
    ret = aqueue_enqueue( &hndl->filled_queue, frame );
    framestream_mutex_unlock( &hndl->filled_queue_lock );

    if ( ret ) {
        LOG( LOG_ERR, "Failed to add frame to the filled queue." );
        return -1;
    }

    return 0;
}

aframe_t *framestream_dequeue_filled( framestream *hndl )
{
    if ( hndl == NULL ) {
        LOG( LOG_ERR, "Incorrect parameter. Frame stream handle is NULL." );
        return NULL;
    }

    framestream_mutex_lock( &hndl->filled_queue_lock );
    aframe_t *frame = (aframe_t *)aqueue_dequeue( &hndl->filled_queue );
    framestream_mutex_unlock( &hndl->filled_queue_lock );

    if ( frame ) {
        frame->state = AFRAME_STATE_FULL;
    }

    return frame;
}

uint32_t framestream_active_size( framestream *hndl )
{
    if ( hndl == NULL ) {
        LOG( LOG_ERR, "Incorrect parameter. Frame stream handle is NULL." );
        return 0;
    }

    framestream_mutex_lock( &hndl->active_pool_lock );
    const uint32_t ret = apool_size( &hndl->active_pool );
    framestream_mutex_unlock( &hndl->active_pool_lock );

    return ret;
}

uint32_t framestream_reclaim_size( framestream *hndl )
{
    if ( hndl == NULL ) {
        LOG( LOG_ERR, "Incorrect parameter. Frame stream handle is NULL." );
        return 0;
    }

    framestream_mutex_lock( &hndl->reclaim_pool_lock );
    const uint32_t ret = apool_size( &hndl->reclaim_pool );
    framestream_mutex_unlock( &hndl->reclaim_pool_lock );

    return ret;
}
