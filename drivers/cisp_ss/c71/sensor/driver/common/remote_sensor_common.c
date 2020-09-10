/*
*
* SPDX-License-Identifier: GPL-2.0
*
* Copyright (C) 2011-2019 ARM or its affiliates
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 2.
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#include "remote_sensor_common.h"
#include "system_types.h"
#include "acamera_aframe.h"
#include "acamera_logger.h"
#include "util_addr_calc.h"

void register_frame_callbacks_common( sensor_param_t *cfg, const sensor_remote_callbacks_t *callbacks )
{
    if ( cfg == NULL ) {
        LOG( LOG_ERR, "Sensor parameters struct pointer is NULL." );
        return;
    }

    if ( callbacks == NULL ) {
        cfg->remote_cfg.callbacks.callback_owner = NULL;
        cfg->remote_cfg.callbacks.get_frame = NULL;
        cfg->remote_cfg.callbacks.put_frame = NULL;
        cfg->remote_cfg.callbacks.release_frame = NULL;

        LOG( LOG_NOTICE, "Frame callback deregistered." );
        return;
    } else if ( callbacks->callback_owner == NULL ) {
        LOG( LOG_ERR, "Invalid callback owner pointer (NULL)." );
        return;
    } else if ( ( callbacks->get_frame == NULL ) || ( callbacks->put_frame == NULL ) || ( callbacks->release_frame == NULL ) ) {
        LOG( LOG_ERR, "Invalid callback function (%s) pointer (NULL).",
             ( ( !callbacks->get_frame ) ? ( "get_frame" ) : ( ( !callbacks->put_frame ) ? ( "put_frame" ) : ( "release_frame" ) ) ) );
        return;
    }

    cfg->remote_cfg.callbacks.callback_owner = callbacks->callback_owner;
    cfg->remote_cfg.callbacks.get_frame = callbacks->get_frame;
    cfg->remote_cfg.callbacks.put_frame = callbacks->put_frame;
    cfg->remote_cfg.callbacks.release_frame = callbacks->release_frame;

    LOG( LOG_DEBUG, "Remote sensor callback functions registered." );
}

static int sensor_frame_buffers_destroy( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data )
{
    size_t i;
    const size_t num_frames = frame_data->frames.num_frames;

    for ( i = 0; i < num_frames; i++ ) {

        if ( cfg->remote_cfg.callbacks.release_frame( cfg->remote_cfg.callbacks.callback_owner, frame_data->frames.frame[i] ) ) {
            LOG( LOG_ERR, "Failed to release frame (sensor_remote_callback_release_frame call returned error)." );
        } else {
            LOG( LOG_DEBUG, "Releasing frame ptr %p", frame_data->frames.frame[i] );
            frame_data->frames.num_frames--;
            frame_data->frames.frame[i] = NULL;
        }
    }

    if ( frame_data->frames.num_frames ) {
        LOG( LOG_ERR, "Possible frame leak. Frame data size after destroy is: %u.", frame_data->frames.num_frames );
    }

    LOG( LOG_DEBUG, "Remote sensor frame data released." );

    return 0;
}

static int sensor_frame_buffers_init( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data )
{
    size_t i;
	LOG( LOG_DEBUG, "%s E", __FUNCTION__);
    frame_data->frames.max_frames = FRAME_DATA_NUM_FRAME_CUR;
    frame_data->frames.num_frames = 0;

    for ( i = 0; i < FRAME_DATA_NUM_FRAME_MAX; i++ ) {

        frame_data->frames.frame[i] = NULL;

        if ( i < FRAME_DATA_NUM_FRAME_CUR ) {

            if ( cfg->remote_cfg.callbacks.get_frame( cfg->remote_cfg.callbacks.callback_owner, &( frame_data->frames.frame[i] ) ) ) {
                LOG( LOG_ERR, "Failed to get empty frame (sensor_remote_callback_get_frame call returned error)." );
                return -1;
            }

            if ( frame_data->frames.frame[i] == NULL ) {
                LOG( LOG_ERR, "Failed to get empty frame (sensor_remote_callback_get_frame call returned NULL)." );
                return -1;
            }

            // Check aframe configuration against sensor current config
            const aframe_t *frame = frame_data->frames.frame[i];

            if ( frame->num_planes != cfg->num_channel ) {
                LOG( LOG_ERR, "Number of planes (%u) of received frame and number of sensor channels (%u) don't match.",
                     frame->num_planes,
                     cfg->num_channel );
                return -1;
            }

            if ( ( frame->planes[0].width != cfg->active.width ) || ( frame->planes[0].height != cfg->active.height ) ) {
                LOG( LOG_ERR, "Size of received frame (%ux%u) and sensor active resolution (%ux%u) don't match.",
                     frame->planes[0].width,
                     frame->planes[0].height,
                     cfg->active.width,
                     cfg->active.height );
                return -1;
            }

            if ( frame->planes[0].data_width != cfg->data_width ) {
                LOG( LOG_ERR, "Data width of received frame (%u) and sensor data width (%u) don't match.",
                     frame->planes[0].data_width,
                     cfg->data_width );
                return -1;
            }

            frame_data->frames.num_frames++;

            LOG( LOG_DEBUG, "Frame with %ux%ux%u (%u bpp) successfully added to remote sensor frame data.",
                 frame->planes[0].width,
                 frame->planes[0].height,
                 frame->num_planes,
                 frame->planes[0].data_width );
        }
    }

    LOG( LOG_DEBUG, "Remote sensor frame data successfully initialised with the size of %u frames.", frame_data->frames.num_frames );

    return 0;
}

static void create_s2m_dma_vport_config( const sensor_param_t *cfg, const remote_sensor_frame_data_t *frame_data, s2m_dma_vport_resource_t *config )
{
    config->vport = cfg->video_port_id;
    config->height = cfg->active.height;
    config->width = cfg->active.width;
    config->data_width = cfg->data_width;

    const size_t num_frames = ( frame_data->frames.num_frames > S2M_DMA_MAX_BANK ) ? ( S2M_DMA_MAX_BANK ) : ( frame_data->frames.num_frames );
    const size_t num_planes = ( ( (aframe_t *)( frame_data->frames.frame[0] ) )->num_planes > S2M_DMA_MAX_CH ) ? ( S2M_DMA_MAX_CH ) : ( ( (aframe_t *)( frame_data->frames.frame[0] ) )->num_planes );

    if ( frame_data->frames.num_frames != num_frames ) {
        LOG( LOG_WARNING, "Remote sensor frame storage size (%u) is bigger than number of DMA banks (%d). Only (%lu) frame(s) will be used.",
             frame_data->frames.num_frames,
             S2M_DMA_MAX_BANK,
             num_frames );
    }

    LOG( LOG_DEBUG, "Creating S2M vport configuration." );

    size_t frame_index;
    for ( frame_index = 0; frame_index < num_frames; frame_index++ ) {

        const aframe_t *frame = frame_data->frames.frame[frame_index];

        if ( frame->num_planes != num_planes ) {
            LOG( LOG_WARNING, "Remote sensor frame has more planes (%u) than available DMA channels (%d). Only (%lu) planes will be used.",
                 frame->num_planes,
                 S2M_DMA_MAX_CH,
                 num_planes );
        }

        LOG( LOG_DEBUG, "S2M vport configuration, configuring frame: %lu out of %lu", ( frame_index + 1 ), num_frames );

        size_t plane_index;
        for ( plane_index = 0; plane_index < num_planes; plane_index++ ) {
            // addrs[DMA_CHANNEL][DMA_BANKS] -> addrs[plane_index][frame_index]
            config->addrs[plane_index][frame_index] = frame->planes[plane_index].address;
            LOG( LOG_DEBUG, "\tPlane %lu out of %lu, address: 0x%x",
                 ( plane_index + 1 ),
                 num_planes,
                 ADDR_SYSPHY2ISPAS( config->addrs[plane_index][frame_index] ) );
        }
    }

    config->num_channels = num_planes;
    config->num_banks = num_frames;

    LOG( LOG_DEBUG, "S2M vport configuration created successfully." );
}

int remote_sensor_reinit( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data, int is_virtual )
{
    if ( cfg == NULL ) {
        LOG( LOG_ERR, "Sensor parameters struct pointer is NULL." );
        return -1;
    } else if ( frame_data == NULL ) {
        LOG( LOG_ERR, "Remote sensor frame data struct pointer is NULL." );
        return -1;
    }

	LOG( LOG_DEBUG, "cfg->is_remote: %d.", cfg->is_remote);
    if ( cfg->is_remote ) {

        //if ( sensor_frame_buffers_destroy( cfg, frame_data ) ) {
        //    LOG( LOG_ERR, "Failed to destroy sensor (type 'remote') frame buffers." );
        //    return -1;
        //}

        if ( sensor_frame_buffers_init( cfg, frame_data ) ) {
            LOG( LOG_ERR, "Failed to initialise sensor (type 'remote') frame buffers." );
            sensor_frame_buffers_destroy( cfg, frame_data );
            return -1;
        }

        frame_data->flags.is_virtual = is_virtual;

        // "virtual" mode is set for remote sensors which do not occupy any inputs (e.g. VDGEN )
        if ( !frame_data->flags.is_virtual ) {

            //frame_data->stats.dropped = 0;
            //frame_data->stats.ontime = 0;
            //frame_data->stats.repeated = 0;
            //frame_data->stats.total = 0;

            //s2m_dma_vport_resource_t vport_config;

            //create_s2m_dma_vport_config( cfg, frame_data, &vport_config );

            //frame_data->flags.s2m_config_status = s2m_dma_start( &vport_config );

        } else {
            frame_data->flags.s2m_config_status = 0;
        }

        LOG( LOG_DEBUG, "Remote sensor reinitialized successfully." );
    }

    return 0;
}

static void update_stats( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data, uint32_t frames_passed )
{
    if ( frames_passed == 1 ) {
        frame_data->stats.ontime++;
        frame_data->stats.total++;
    } else if ( frames_passed == 0 ) {
        frame_data->stats.repeated++;
        if ( frame_data->stats.repeated % 100 == 0 )
            LOG( LOG_WARNING, "vport %d S2M_DMA frame stats: repeated: %u, dropped: %u, ontime: %u, total %u",
                 cfg->video_port_id,
                 frame_data->stats.repeated,
                 frame_data->stats.dropped,
                 frame_data->stats.ontime,
                 frame_data->stats.total );
    } else {
        if ( frame_data->stats.dropped == 0 ) {
            frames_passed = 2; //ignore initial value
        }

        frame_data->stats.dropped += frames_passed - 1;
        frame_data->stats.total += frames_passed;

        if ( frame_data->stats.dropped % 100 == 0 )
            LOG( LOG_WARNING, "vport %d S2M_DMA frame stats: repeated: %u, dropped: %u, ontime: %u, total %u",
                 cfg->video_port_id,
                 frame_data->stats.repeated,
                 frame_data->stats.dropped,
                 frame_data->stats.ontime,
                 frame_data->stats.total );
    }
}

void request_next_frame_common( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data )
{

    void *empty_frame = NULL, *filled_frame = NULL;
    uint32_t frames_passed;

    if ( cfg == NULL ) {
        LOG( LOG_ERR, "Sensor parameters struct pointer is NULL." );
        return;
    } else if ( frame_data == NULL ) {
        LOG( LOG_ERR, "Remote sensor frame data struct pointer is NULL." );
        return;
    }

    // Failed to configure sensors are not processed
    if ( frame_data->flags.s2m_config_status ) {
        return;
    }

    // Get new empty frame
    if ( cfg->remote_cfg.callbacks.get_frame( cfg->remote_cfg.callbacks.callback_owner, &empty_frame ) ) {
        LOG( LOG_ERR, "Failed to get empty frame (sensor_remote_callback_get_frame call returned error)." );
        return;
    }

    if ( empty_frame == NULL ) {
        LOG( LOG_ERR, "Failed to get empty frame (sensor_remote_callback_get_frame call returned NULL)." );
        return;
    }

    if ( frame_data->flags.is_virtual ) {
        // For virtual remote sensors that do not occupy any channels logic is simple:
        // send empty frame
        filled_frame = empty_frame;
    } else {
        // For Sensor2Memory sensors which are backed by DMA frame writers:
        // get filled frame by swapping last bank with empty frame
        //uint8_t last_bank = s2m_dma_get_last_bank( cfg->video_port_id, &frames_passed );

        //update_stats( cfg, frame_data, frames_passed );

        //if ( last_bank >= frame_data->frames.num_frames ) {
        //    LOG( LOG_ERR, "s2m_dma_get_last_bank returned (%u) which is out of range (0-%u). The value will be clipped.",
        //         last_bank,
        //         ( frame_data->frames.num_frames > 0 ) ? ( frame_data->frames.num_frames - 1 ) : ( 0 ) );

        //    last_bank = ( frame_data->frames.num_frames > 0 ) ? ( frame_data->frames.num_frames - 1 ) : ( 0 );
        //}

        //LOG( LOG_DEBUG, "last bank: %u", last_bank );

        //filled_frame = frame_data->frames.frame[last_bank];
        //frame_data->frames.frame[last_bank] = empty_frame;

        //s2m_dma_vport_resource_t vport_config;

        //create_s2m_dma_vport_config( cfg, frame_data, &vport_config );

        //s2m_dma_swap( &vport_config, last_bank );
    }

    if ( cfg->remote_cfg.callbacks.put_frame( cfg->remote_cfg.callbacks.callback_owner, (aframe_t *)filled_frame ) ) {
        LOG( LOG_ERR, "Failed to put filled frame (sensor_remote_callback_put_frame call returned error)." );
        return;
    }

    LOG( LOG_DEBUG, "Remote sensor next frame request processing completed." );
}

void remote_sensor_start_streaming( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data )
{
    if ( cfg == NULL ) {
        LOG( LOG_ERR, "Sensor parameters struct pointer is NULL." );
        return;
    } else if ( frame_data == NULL ) {
        LOG( LOG_ERR, "Remote sensor frame data struct pointer is NULL." );
        return;
    }

    if ( cfg->is_remote ) {
        request_next_frame_common( cfg, frame_data );

        LOG( LOG_DEBUG, "Remote sensor streaming started." );
    }
}

void remote_sensor_deinit( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data )
{
    if ( cfg == NULL ) {
        LOG( LOG_ERR, "Sensor parameters struct pointer is NULL." );
        return;
    } else if ( frame_data == NULL ) {
        LOG( LOG_ERR, "Remote sensor frame data struct pointer is NULL." );
        return;
    }

    if ( cfg->is_remote ) {
        if ( sensor_frame_buffers_destroy( cfg, frame_data ) ) {
            LOG( LOG_ERR, "Failed to destroy sensor (type 'remote') frame buffers." );
        }

        LOG( LOG_DEBUG, "Remote sensor deinitialized." );
    }
}
