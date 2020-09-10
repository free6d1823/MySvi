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

#ifndef __REMOTE_SENSOR_COMMON_H__
#define __REMOTE_SENSOR_COMMON_H__

#include "sensor_api.h"
#include "isp_wrapper_lib.h"

#define FRAME_DATA_NUM_FRAME_REQ ( 2 )
#define FRAME_DATA_NUM_FRAME_MAX ( 28 )//( S2M_DMA_MAX_BANK )
#define FRAME_DATA_NUM_FRAME_CUR \
    ( ( FRAME_DATA_NUM_FRAME_REQ > ( FRAME_DATA_NUM_FRAME_MAX ) ) ? ( FRAME_DATA_NUM_FRAME_MAX ) : ( FRAME_DATA_NUM_FRAME_REQ ) )

typedef struct remote_sensor_frame_stats_t {
    uint32_t repeated;
    uint32_t dropped;
    uint32_t ontime;
    uint32_t total;
} remote_sensor_frame_stats_t;

typedef struct remote_sensor_frames_t {
    void *frame[FRAME_DATA_NUM_FRAME_MAX];
    uint32_t num_frames;
    uint32_t max_frames;
} remote_sensor_frames_t;

typedef struct remote_sensor_flags_t {
    int s2m_config_status;
    int is_virtual;
} remote_sensor_flags_t;

typedef struct remote_sensor_frame_data_t {
    remote_sensor_flags_t flags;
    remote_sensor_frame_stats_t stats;
    remote_sensor_frames_t frames;
} remote_sensor_frame_data_t;

void request_next_frame_common( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data );
void register_frame_callbacks_common( sensor_param_t *cfg, const sensor_remote_callbacks_t *callbacks );
int remote_sensor_reinit( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data, int is_virtual );
void remote_sensor_start_streaming( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data );
void remote_sensor_deinit( const sensor_param_t *cfg, remote_sensor_frame_data_t *frame_data );

#endif // __REMOTE_SENSOR_COMMON_H__
