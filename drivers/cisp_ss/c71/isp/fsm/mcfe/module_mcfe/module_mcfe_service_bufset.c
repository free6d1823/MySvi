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

#include "system_assert.h"
#include "module_mcfe_service.h"
#include "module_mcfe_service_buf.h"

#define MCFE_MAX_BUFSET ( ISP_MCFE_MAX_SLOT * 2 )

#define FRAME_USAGE_VALIDATION 0

#if ( FRAME_USAGE_VALIDATION )
#define CNT_REPORT_FREQ 10000

typedef struct frame_stats_t {
    uint32_t used_count;
    uint32_t planes[AFRAME_MAX_PLANES];
} frame_stats_t;

typedef struct context_frame_stats_t {
    // Frame->frame_id starts from 1, so reserve one additional element
    frame_stats_t out_frames[FRAME_STREAM_MAX_FRAMES + 1];
    frame_stats_t raw_frames[FRAME_STREAM_MAX_FRAMES + 1];
    uint64_t frame_counter;
} context_frame_stats_t;

static context_frame_stats_t context_frame_stats[FIRMWARE_CONTEXT_NUMBER] = {0};

static void print_cnt_el_report( const frame_stats_t *frame_stats )
{
    int i, j;

    for ( i = 1; i <= FRAME_STREAM_MAX_FRAMES; ++i ) {
        if ( frame_stats[i].used_count ) {
            LOG( LOG_NOTICE, "   -- Frame id: %d, used count: %u", i, frame_stats[i].used_count );
            for ( j = 0; j < AFRAME_MAX_PLANES; ++j ) {
                if ( frame_stats[i].planes[j] ) {
                    LOG( LOG_NOTICE, "      -- Plane id: %d, used count: %u", j, frame_stats[i].planes[j] );
                }
            }
        }
    }
}

static void print_cnt_report( const context_frame_stats_t *context_stats, uint32_t context_id )
{
    if ( context_stats == NULL ) {
        return;
    }

    LOG( LOG_NOTICE, "" );
    LOG( LOG_NOTICE, "Frame usage report, context id: %d, frame swaps: %llu",
         context_id,
         context_stats->frame_counter );

    LOG( LOG_NOTICE, "-- Output frames statistics" );
    print_cnt_el_report( context_stats->out_frames );
    LOG( LOG_NOTICE, "-- Raw frames statistics" );
    print_cnt_el_report( context_stats->raw_frames );

    LOG( LOG_NOTICE, "End of frame usage report" );
    LOG( LOG_NOTICE, "" );
}

static void register_frame_usage( const aframe_t *frame )
{
    if ( ( frame == NULL ) || ( frame->context_id >= FIRMWARE_CONTEXT_NUMBER ) || ( frame->frame_id > FRAME_STREAM_MAX_FRAMES ) ) {
        return;
    }

    context_frame_stats_t *context_stats = &context_frame_stats[frame->context_id];
    frame_stats_t *frame_stats;

    if ( context_stats->frame_counter > 0 && ( ( context_stats->frame_counter % CNT_REPORT_FREQ ) == 0 ) ) {
        print_cnt_report( context_stats, frame->context_id );
    }

    context_stats->frame_counter++;

    switch ( frame->type ) {
    case AFRAME_TYPE_OUT:
        frame_stats = context_stats->out_frames;
        break;
    case AFRAME_TYPE_RAW:
        frame_stats = context_stats->raw_frames;
        break;
    default:
        LOG( LOG_ERR, "Unrecognised frame type!" );
        return;
    }

    frame_stats[frame->frame_id].used_count++;
}

static void register_plane_usage( const aframe_t *frame, uint32_t plane_id )
{
    if ( ( frame == NULL ) || ( frame->context_id >= FIRMWARE_CONTEXT_NUMBER ) || ( plane_id >= frame->num_planes ) ) {
        return;
    }

    context_frame_stats_t *context_stats = &context_frame_stats[frame->context_id];
    frame_stats_t *frame_stats;

    switch ( frame->type ) {
    case AFRAME_TYPE_OUT:
        frame_stats = context_stats->out_frames;
        break;
    case AFRAME_TYPE_RAW:
        frame_stats = context_stats->raw_frames;
        break;
    default:
        LOG( LOG_ERR, "Unrecognised frame type!" );
        return;
    }

    frame_stats[frame->frame_id].planes[plane_id]++;
}

#endif

/**
 * @brief Pool resource helper to describe buffer sets.
 *
*/
typedef struct module_mcfe_bufset_pool_t {
    module_mcfe_bufset_t *bufsets;
    size_t bufsets_max;
} module_mcfe_bufset_pool_t;

// Statically allocated resources, buffer sets
static module_mcfe_bufset_t mcfe_bufsets[MCFE_MAX_BUFSET] = {0};

static module_mcfe_bufset_pool_t pool = {
    .bufsets = mcfe_bufsets,
    .bufsets_max = MCFE_MAX_BUFSET};

static void module_mcfe_bufset_init_pool( void )
{
    size_t i;

    for ( i = 0; i < pool.bufsets_max; ++i ) {
        pool.bufsets[i].enabled = 0;
        pool.bufsets[i].index = i;
        pool.bufsets[i].type = MCFE_BUFSET_TYPE_NONE;
        pool.bufsets[i].frames.num_frames = 0;
        pool.bufsets[i].buffs.buffer_type = MCFE_BUF_TYPE_NONE;
        pool.bufsets[i].buffs.num_buffers = 0;
        pool.bufsets[i].buffs.num_planes = 0;

        size_t j, k;
        for ( j = 0; j < MODULE_MCFE_BUFSET_MAX_FRAMES; j++ ) {
            pool.bufsets[i].frames.frame[j] = NULL;
        }

        for ( j = 0; j < MODULE_MCFE_BUFSET_MAX_FRAMES; j++ ) {
            for ( k = 0; k < AFRAME_MAX_PLANES; k++ ) {
                pool.bufsets[i].buffs.buff[j][k] = NULL;
            }
        }
    }
}

void module_mcfe_bufset_init( void )
{
    module_mcfe_buf_init_pool( MCFE_BUF_TYPE_RAW );
    module_mcfe_buf_init_pool( MCFE_BUF_TYPE_OUT );
    module_mcfe_bufset_init_pool();
}

static module_mcfe_bufset_type_t frame_type_to_bufset_type( const aframe_type_t type )
{
    switch ( type ) {
    case AFRAME_TYPE_RAW:
        return MCFE_BUFSET_TYPE_RAW;
    case AFRAME_TYPE_OUT:
        return MCFE_BUFSET_TYPE_OUT;
    default:
        LOG( LOG_ERR, "Unsupported frame type supplied (%d)", type );
        return MCFE_BUFSET_TYPE_NONE;
    }
}

static mcfe_hwif_buf_type_t bufset_type_to_buffer_type( const module_mcfe_bufset_type_t type )
{
    switch ( type ) {
    case MCFE_BUFSET_TYPE_RAW:
        return MCFE_BUF_TYPE_RAW;
    case MCFE_BUFSET_TYPE_OUT:
        return MCFE_BUF_TYPE_OUT;
    default:
        LOG( LOG_ERR, "Unsupported buffer set type supplied (%d)", type );
        return MCFE_BUF_TYPE_NONE;
    }
}

static size_t bufset_get_free_count( void )
{
    size_t i, n = 0;
    for ( i = 0; i < pool.bufsets_max; ++i ) {
        if ( !pool.bufsets[i].enabled ) {
            n++;
        }
    }

    return n;
}

static module_mcfe_bufset_t *bufset_get_free( void )
{
    size_t i;

    for ( i = 0; i < pool.bufsets_max; ++i ) {
        if ( !pool.bufsets[i].enabled ) {
            return &pool.bufsets[i];
        }
    }

    return NULL;
}

static int bufset_validate_frames( aframe_t *frames[], const size_t num_frames )
{
    size_t i, j;

    assert( frames );
    assert( num_frames );

    if ( num_frames > MODULE_MCFE_BUFSET_MAX_FRAMES ) {
        LOG( LOG_ERR, "Number of frames %lu exceeds maximum limit of %d.", num_frames, MODULE_MCFE_BUFSET_MAX_FRAMES );
        return MCFE_ERR_INV_PARM;
    }

    for ( i = 0; i < num_frames; i++ ) {

        if ( ( frames[i]->type <= AFRAME_TYPE_UNKNOWN ) || ( frames[i]->type >= AFRAME_TYPE_MAX ) ) {
            LOG( LOG_ERR, "Incorrect frame type (%d).", frames[i]->type );
            return MCFE_ERR_INV_PARM;
        }

        if ( ( frames[i]->type != AFRAME_TYPE_RAW ) && ( frames[i]->type != AFRAME_TYPE_OUT ) ) {
            LOG( LOG_ERR, "Unsupported frame type (%d). Only the AFRAME_TYPE_RAW and AFRAME_TYPE_OUT frame types are supported", frames[i]->type );
            return MCFE_ERR_INV_PARM;
        }

        if ( frames[0]->type != frames[i]->type ) {
            LOG( LOG_ERR, "Frames (%d, %lu) have different types (%d, %d).",
                 0,
                 i,
                 frames[0]->type,
                 frames[i]->type );
            return MCFE_ERR_INV_PARM;
        }

        if ( frames[i]->num_planes > AFRAME_MAX_PLANES ) {
            LOG( LOG_ERR, "Number of planes %d exceeds maximum limit of %d.", frames[i]->num_planes, AFRAME_MAX_PLANES );
            return MCFE_ERR_INV_PARM;
        }

        if ( frames[0]->num_planes != frames[i]->num_planes ) {
            LOG( LOG_ERR, "Frames (%d, %lu) have different number of planes (%d, %d).",
                 0,
                 i,
                 frames[0]->num_planes,
                 frames[i]->num_planes );
            return MCFE_ERR_INV_PARM;
        }

        for ( j = 0; j < frames[i]->num_planes; j++ ) {
            if ( frames[i]->planes[j].line_offset % AFRAME_PLANE_ALIGNMENT ) {
                LOG( LOG_ERR, "Line offset %d (frame %lu, plane %lu ) is not multiple of %d (incorrect alignment).",
                     frames[i]->planes[j].line_offset, i, j, AFRAME_PLANE_ALIGNMENT );
                return MCFE_ERR_INV_PARM;
            }

            if ( frames[i]->planes[j].address == 0 ) {
                LOG( LOG_ERR, "Incorrect plane address %d (frame %lu, plane %lu ).",
                     frames[i]->planes[j].address, i, j );
                return MCFE_ERR_INV_PARM;
            }
        }
    }

    return MCFE_ERR_NONE;
}

static size_t bufset_get_required_buffer_count( aframe_t *frames[], const size_t num_frames )
{
    size_t i, required_buffer_count = 0;

    for ( i = 0; i < num_frames; i++ ) {
        required_buffer_count += frames[i]->num_planes;
    }

    return required_buffer_count;
}

static void bufset_config_header( module_mcfe_bufset_t *bufset, aframe_t *frames[], module_mcfe_bufset_type_t type, mcfe_hwif_buf_type_t buffer_type, unsigned int num_frames )
{
    size_t i;

    for ( i = 0; i < MODULE_MCFE_BUFSET_MAX_FRAMES; i++ ) {
        bufset->frames.frame[i] = NULL;
    }

    for ( i = 0; i < num_frames; i++ ) {
        bufset->frames.frame[i] = frames[i];
    }

    bufset->type = type;
    bufset->frames.num_frames = num_frames;
    bufset->buffs.buffer_type = buffer_type;
    bufset->buffs.num_planes = frames[0]->num_planes;
}

static void bufset_reset_header( module_mcfe_bufset_t *bufset )
{
    size_t i;

    for ( i = 0; i < MODULE_MCFE_BUFSET_MAX_FRAMES; i++ ) {
        bufset->frames.frame[i] = NULL;
    }

    bufset->type = MCFE_BUFSET_TYPE_NONE;
    bufset->frames.num_frames = 0;
    bufset->buffs.buffer_type = MCFE_BUF_TYPE_NONE;
    bufset->buffs.num_planes = 0;
}

static int bufset_destroy_buffers( module_mcfe_bufset_t *bufset )
{
    size_t i, j;

    // Destroy HW buffers
    for ( i = 0; i < bufset->frames.num_frames; i++ ) {
        for ( j = 0; j < bufset->buffs.num_planes; j++ ) {
            if ( ( bufset->buffs.buff[i][j] != NULL ) && ( bufset->buffs.num_buffers > 0 ) ) {

                module_mcfe_buf_destroy( bufset->buffs.buff[i][j] );
                bufset->buffs.buff[i][j] = NULL;

                bufset->buffs.num_buffers--;
            }
        }
    }

    if ( bufset->buffs.num_buffers != 0 ) {
        LOG( LOG_ERR, "Possible buffer leak during buffer destroy ( ( num_buffers = %u ) != 0 ).", bufset->buffs.num_buffers );
        return MCFE_ERR_GENERAL;
    }

    return MCFE_ERR_NONE;
}

static unsigned short create_buffer_flags( uint32_t frame_flags )
{
    unsigned short buffer_flags = 0;

    buffer_flags |= ( ( frame_flags & ( AFRAME_HW_FLAG_MSB_ALIGN ) ) ? ( MCFE_BUF_FLAG_MSB_ALIGN ) : ( 0 ) );
    buffer_flags |= ( ( frame_flags & ( AFRAME_HW_FLAG_POOL ) ) ? ( MCFE_BUF_FLAG_POOL ) : ( 0 ) );
    buffer_flags |= ( ( frame_flags & ( AFRAME_HW_FLAG_CLONE ) ) ? ( MCFE_BUF_FLAG_CLONE ) : ( 0 ) );
    buffer_flags |= ( ( frame_flags & ( AFRAME_HW_FLAG_INFINITE ) ) ? ( MCFE_BUF_FLAG_INFINITE ) : ( 0 ) );

    return buffer_flags;
}

static int bufset_create_buffers( module_mcfe_bufset_t *bufset )
{
    size_t i, j;
    module_mcfe_buf_cfg_t buffer_config;
    const aplane_t *plane;

    // Reset all HW buffer pointers
    for ( i = 0; i < MODULE_MCFE_BUFSET_MAX_FRAMES; i++ ) {
        for ( j = 0; j < AFRAME_MAX_PLANES; j++ ) {
            bufset->buffs.buff[i][j] = NULL;
        }
    }

    bufset->buffs.num_buffers = 0;

    // Init frame pointers and create HW buffers
    for ( i = 0; i < bufset->frames.num_frames; i++ ) {
        for ( j = 0; j < bufset->buffs.num_planes; j++ ) {
            plane = &( bufset->frames.frame[i]->planes[j] );

            buffer_config.active_height = plane->height;
            buffer_config.active_width = plane->width;
            buffer_config.data_width = plane->data_width;
            buffer_config.flags = create_buffer_flags( plane->hw_cfg.flags );
            buffer_config.line_offset = plane->line_offset;
            buffer_config.type = bufset->buffs.buffer_type;
            buffer_config.address = plane->address;

            if ( ( bufset->buffs.buff[i][j] = module_mcfe_buf_create( &buffer_config ) ) == NULL ) {
                LOG( LOG_ERR, "Failed to create HW buffer (type = %u).", buffer_config.type );
                bufset_destroy_buffers( bufset );
                return MCFE_ERR_NO_RES;
            }

            LOG( LOG_NOTICE, "Buffer set buffer created:\n"
                            "\tenabled: %u\n"
                            "\tindex: %u\n"
                            "\ttype: %u\n"
                            "\twidth: %u\n"
                            "\theight: %u\n"
                            "\tdata width: %u\n"
                            "\tflags: 0x%x\n"
                            "\tline offset: %u\n"
                            "\taddress: 0x%llx\n",
                 bufset->buffs.buff[i][j]->enabled,
                 bufset->buffs.buff[i][j]->index,
                 bufset->buffs.buff[i][j]->type,
                 bufset->buffs.buff[i][j]->active_width,
                 bufset->buffs.buff[i][j]->active_height,
                 bufset->buffs.buff[i][j]->data_width,
                 bufset->buffs.buff[i][j]->flags,
                 bufset->buffs.buff[i][j]->line_offset,
                 bufset->buffs.buff[i][j]->address );

            bufset->buffs.num_buffers++;
        }
    }

    return MCFE_ERR_NONE;
}

static int bufset_get_frame_index_with_status( const module_mcfe_bufset_t *bufset, const int frame_no, const module_mcfe_bufset_status_t status )
{
    int status_match_count, index = -1;
    size_t i, j;
    uint8_t req_buffer_status;

    assert( bufset );

    if ( ( frame_no > 0 ) && ( frame_no >= bufset->frames.num_frames ) ) {
        LOG( LOG_ERR, "Frame number (%d) is out of range (0-%d).", frame_no, ( bufset->frames.num_frames > 0 ) ? bufset->frames.num_frames - 1 : 0 );
        return index;
    }

    switch ( status ) {
    case MCFE_BUFSET_STATUS_EMPTY:
        req_buffer_status = 0;
        break;
    case MCFE_BUFSET_STATUS_FILLED:
        req_buffer_status = 1;
        break;
    default:
        LOG( LOG_ERR, "Incorrect buffer set status supplied: %d.", status );
        return index;
    }

    // Check if frame_no is set to specific frame index, so search only within that frame
    const size_t frame_start_index = ( frame_no > 0 ) ? frame_no : 0;
    const size_t frame_end_index = ( frame_no > 0 ) ? ( frame_no + 1 ) : bufset->frames.num_frames;

    for ( i = frame_start_index; i < frame_end_index; i++ ) {

        status_match_count = 0;

        for ( j = 0; j < bufset->buffs.num_planes; j++ ) {

            const uint8_t buffer_status = mcfe_hwif_buff_status_get( bufset->buffs.buff[i][j]->type, bufset->buffs.buff[i][j]->index );

            LOG( LOG_DEBUG, "Buffer status query:\n"
                            "\tenabled: %u\n"
                            "\tstatus: %u\n"
                            "\trequested status: %u\n"
                            "\tindex: %u\n"
                            "\ttype: %u\n",
                 bufset->buffs.buff[i][j]->enabled,
                 buffer_status,
                 req_buffer_status,
                 bufset->buffs.buff[i][j]->index,
                 bufset->buffs.buff[i][j]->type );

            if ( buffer_status == req_buffer_status ) {
                status_match_count++;
            } else {
                break;
            }
        }

        if ( status_match_count == bufset->buffs.num_planes ) {
            index = i;
            break;
        }
    }

    return index;
}

static int bufset_set_buffer_address_and_status( const module_mcfe_bufset_t *bufset, const aframe_t *frame, const int frame_index, const module_mcfe_bufset_status_t status )
{
    int buffer_status;
    size_t i;

    assert( bufset );
    assert( frame );

    if ( frame_index >= bufset->frames.num_frames ) {
        LOG( LOG_ERR, "Incorrect buffer set frame index supplied: %d. Buffer set has only %d frames", frame_index, bufset->frames.num_frames );
        return MCFE_ERR_INV_PARM;
    }

    switch ( status ) {
    case MCFE_BUFSET_STATUS_EMPTY:
        buffer_status = 0;
        break;
    case MCFE_BUFSET_STATUS_FILLED:
        buffer_status = 1;
        break;
    default:
        LOG( LOG_ERR, "Incorrect buffer set status supplied: %d.", status );
        return MCFE_ERR_INV_PARM;
    }

#if ( FRAME_USAGE_VALIDATION )
    register_frame_usage( frame );
#endif

    for ( i = 0; i < bufset->buffs.num_planes; i++ ) {
        module_mcfe_buf_t *buffer = bufset->buffs.buff[frame_index][i];
        mcfe_hwif_buff_addr_set( buffer->type, buffer->index, frame->planes[i].address );
        mcfe_hwif_buff_status_set( buffer->type, buffer->index, buffer_status );
#if ( FRAME_USAGE_VALIDATION )
        register_plane_usage( frame, i );
#endif
    }

    return MCFE_ERR_NONE;
}


int module_mcfe_bufset_create( aframe_t *frames[], module_mcfe_bufset_t **bufset, const unsigned int num_frames )
{
    size_t buffers_required;

    // Check input
    if ( frames == NULL ) {
        LOG( LOG_ERR, "Frames pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( bufset == NULL ) {
        LOG( LOG_ERR, "Buffer set pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    // Check mode
    if ( ( num_frames > MODULE_MCFE_BUFSET_MAX_FRAMES ) || ( num_frames == 0 ) ) {
        LOG( LOG_ERR, "Incorrect frame count supplied: %d.", num_frames );
        return MCFE_ERR_INV_PARM;
    }

    if ( bufset_validate_frames( frames, num_frames ) != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Failed to validate frames." );
        return MCFE_ERR_INV_PARM;
    }

    if ( ( buffers_required = bufset_get_required_buffer_count( frames, num_frames ) ) == 0 ) {
        LOG( LOG_ERR, "Failed to get required buffer count." );
        return MCFE_ERR_INV_PARM;
    }

    // Check if we have free buffer sets
    if ( bufset_get_free_count() < 1 ) {
        LOG( LOG_ERR, "Error, out of buffer sets." );
        return MCFE_ERR_NO_RES;
    }

    // Check if we have enough free buffers
    const module_mcfe_bufset_type_t bufset_type = frame_type_to_bufset_type( frames[0]->type );
    const mcfe_hwif_buf_type_t buffer_type = bufset_type_to_buffer_type( bufset_type );
    const size_t buffers_available = module_mcfe_buf_get_free_count( buffer_type );

    if ( buffers_available < buffers_required ) {
        LOG( LOG_ERR, "Error, out of hardware buffers. (type = %u, required = %lu, available = %lu)",
             buffer_type, buffers_required, buffers_available );
        return MCFE_ERR_NO_RES;
    }

    module_mcfe_bufset_t *lbufset = bufset_get_free();

    // We checked we have free bufsets, sanity check
    assert( lbufset );

    bufset_config_header( lbufset, frames, bufset_type, buffer_type, num_frames );

    if ( bufset_create_buffers( lbufset ) != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Failed to find free HW buffers (type = %d, count = %lu) for the buffer set (type = %d).",
             lbufset->buffs.buffer_type, buffers_required, lbufset->type );
        return MCFE_ERR_NO_RES;
    }

    if ( lbufset->buffs.num_buffers != buffers_required ) {
        bufset_destroy_buffers( lbufset );
        LOG( LOG_ERR, "Failed to create required number of HW buffers (type = %d, required = %lu, created = %u) for the buffer set (type = %d).",
             lbufset->buffs.buffer_type, buffers_required, lbufset->buffs.num_buffers, lbufset->type );
        return MCFE_ERR_NO_RES;
    }

    lbufset->enabled = 1;

    *bufset = lbufset;

    return MCFE_ERR_NONE;
}

int module_mcfe_bufset_destroy( module_mcfe_bufset_t *bufset )
{
    int errno = MCFE_ERR_NONE;

    // Check input
    if ( bufset == NULL ) {
        LOG( LOG_ERR, "Buffer set pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    if ( bufset_destroy_buffers( bufset ) != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Failed to destroy HW buffers (type = %d) for the buffer set (type = %d).", bufset->buffs.buffer_type, bufset->type );
        errno = MCFE_ERR_GENERAL;
    }

    bufset_reset_header( bufset );

    bufset->enabled = 0;

    return errno;
}

int module_mcfe_bufset_swap( aframe_t *in,
                             aframe_t **out,
                             module_mcfe_bufset_t *bufset,
                             const module_mcfe_bufset_swap_mode_t mode )
{
    int frame_index;
    module_mcfe_bufset_status_t get_status, set_status;
    const char *get_status_desc, *set_status_desc;

    // Check input
    if ( out == NULL ) {
        LOG( LOG_ERR, "Output frame pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else {
        *out = NULL;
    }

    if ( in == NULL ) {
        LOG( LOG_ERR, "Input frame pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( bufset == NULL ) {
        LOG( LOG_ERR, "Buffer set pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    switch ( mode ) {
    case MCFE_BUFSET_SWAP_EMPTY_IN_FILLED_OUT:
        get_status = MCFE_BUFSET_STATUS_FILLED;
        set_status = MCFE_BUFSET_STATUS_EMPTY;
        get_status_desc = "filled";
        set_status_desc = "empty";
        break;
    case MCFE_BUFSET_SWAP_FILLED_IN_EMPTY_OUT:
        get_status = MCFE_BUFSET_STATUS_EMPTY;
        set_status = MCFE_BUFSET_STATUS_FILLED;
        get_status_desc = "empty";
        set_status_desc = "filled";
        break;
    default:
        LOG( LOG_ERR, "Incorrect buffer set swap mode supplied (%d).", mode );
        return MCFE_ERR_INV_PARM;
    }

    // Check frame type of the input frame
    if ( bufset->type != frame_type_to_bufset_type( in->type ) ) {
        LOG( LOG_ERR, "Frame type (type = %d) doesn't match buffer set type (type = %d).", in->type, bufset->type );
        return MCFE_ERR_INV_PARM;
    }

    // Check plane count the input frame
    if ( bufset->buffs.num_planes != in->num_planes ) {
        LOG( LOG_ERR, "Buffer set and input frame supplied have different number of planes (%u vs %u).", bufset->buffs.num_planes, in->num_planes );
        return MCFE_ERR_INV_PARM;
    }

    // Check if any frame of the buffer set has all assigned buffers in required state
    if ( ( frame_index = bufset_get_frame_index_with_status( bufset, -1, get_status ) ) < 0 ) {
        LOG( LOG_ERR, "Failed to get %s frame index of the buffer set (type = %d). Not all or none of the buffers are %s.",
             get_status_desc, bufset->type, get_status_desc );
        return MCFE_ERR_GENERAL;
    }

    // Everything should be fine, update buffer address and status
    if ( bufset_set_buffer_address_and_status( bufset, in, frame_index, set_status ) != MCFE_ERR_NONE ) {
        LOG( LOG_ERR, "Failed to set buffer addresses and statuses (%s) of the buffer set (type = %d).",
             set_status_desc, bufset->type );
        return MCFE_ERR_GENERAL;
    }

    // Swapping frame pointers
    *out = bufset->frames.frame[frame_index];
    bufset->frames.frame[frame_index] = in;

    return MCFE_ERR_NONE;
}

int module_mcfe_bufset_get_buf_id( const module_mcfe_bufset_t *bufset,
                                   const int frame_no,
                                   const int plane_no,
                                   const module_mcfe_bufset_status_t status,
                                   uint8_t *buf_id )
{
    int frame_index;

    // Check input
    if ( bufset == NULL ) {
        LOG( LOG_ERR, "Buffer set pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( buf_id == NULL ) {
        LOG( LOG_ERR, "Buffer id pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( plane_no >= bufset->buffs.num_planes ) {
        LOG( LOG_ERR, "Plane number (%d) is out of range (0-%d).", plane_no, ( bufset->buffs.num_planes > 0 ) ? bufset->buffs.num_planes - 1 : 0 );
        return MCFE_ERR_INV_PARM;
    } else if ( ( frame_no > 0 ) && ( frame_no >= bufset->frames.num_frames ) ) {
        LOG( LOG_ERR, "Frame number (%d) is out of range (0-%d).", frame_no, ( bufset->frames.num_frames > 0 ) ? bufset->frames.num_frames - 1 : 0 );
        return MCFE_ERR_INV_PARM;
    } else if ( ( status <= MCFE_BUFSET_STATUS_NONE ) || ( status >= MCFE_BUFSET_STATUS_MAX ) ) {
        LOG( LOG_ERR, "Status value (%d) is out of range.", status );
        return MCFE_ERR_INV_PARM;
    }

    // Check if any frame of the buffer set has all assigned buffers in empty state
    if ( ( frame_index = bufset_get_frame_index_with_status( bufset, frame_no, status ) ) < 0 ) {
        const char *frame_status = ( status == MCFE_BUFSET_STATUS_EMPTY ) ? ( "empty" ) : ( "filled" );
        LOG( LOG_ERR, "Failed to get %s frame index of the buffer set (type = %d). Not all or none of the buffers are %s.",
             frame_status, bufset->type, frame_status );
        return MCFE_ERR_GENERAL;
    }

    // Update buffer id
    *buf_id = bufset->buffs.buff[frame_index][plane_no]->index;

    return MCFE_ERR_NONE;
}

int module_mcfe_bufset_set_buf_status( const module_mcfe_bufset_t *bufset, const module_mcfe_bufset_status_t status )
{
    int buffer_status;
    size_t i, j;

    if ( bufset == NULL ) {
        LOG( LOG_ERR, "Buffer set pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    switch ( status ) {
    case MCFE_BUFSET_STATUS_EMPTY:
        buffer_status = 0;
        break;
    case MCFE_BUFSET_STATUS_FILLED:
        buffer_status = 1;
        break;
    default:
        LOG( LOG_ERR, "Incorrect buffer set status supplied: %d.", status );
        return MCFE_ERR_INV_PARM;
    }

    for ( i = 0; i < bufset->frames.num_frames; i++ ) {
        for ( j = 0; j < bufset->buffs.num_planes; j++ ) {
            mcfe_hwif_buff_status_set( bufset->buffs.buff[i][j]->type, bufset->buffs.buff[i][j]->index, buffer_status );
        }
    }

    return MCFE_ERR_NONE;
}

int module_mcfe_bufset_get_frames( const module_mcfe_bufset_t *bufset, module_mcfe_bufset_frames_t *frames )
{
    size_t i;

    if ( bufset == NULL ) {
        LOG( LOG_ERR, "Buffer set pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    } else if ( frames == NULL ) {
        LOG( LOG_ERR, "Frames pointer is NULL." );
        return MCFE_ERR_INV_PARM;
    }

    for ( i = 0; i < MODULE_MCFE_BUFSET_MAX_FRAMES; i++ ) {
        if ( i < bufset->frames.num_frames ) {
            frames->frame[i] = (aframe_t *)bufset->frames.frame[i];
        } else {
            frames->frame[i] = NULL;
        }
    }

    frames->num_frames = bufset->frames.num_frames;

    return MCFE_ERR_NONE;
}
