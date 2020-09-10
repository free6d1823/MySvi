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
#include "system_timer.h"
#include "module_mcfe_service.h"

#define MCFE_BUF_DEFAULT_DW_RAW ( 12 )
#define MCFE_BUF_DEFAULT_DW_OUT ( 32 )
#define MCFE_BUF_DEFAULT_WIDTH ( 1920 )
#define MCFE_BUF_DEFAULT_HEIGHT ( 1080 )
#define MCFE_DEFAULT_BUFFER_FLAGS ( 0 )
#define MCFE_MAX_RAW_BUF ISP_MCFE_MAX_RAW_BUF
#define MCFE_MAX_OUT_BUF ISP_MCFE_MAX_OUT_BUF

/**
 * @brief Pool resource helper to describe raw/out buffer resources.
 * 
*/
typedef struct module_mcfe_buf_pool_t {
    module_mcfe_buf_t *buffers;
    size_t buffers_max;
} module_mcfe_buf_pool_t;

// Statically allocated resources, buffers
static module_mcfe_buf_t mcfe_buffers_raw[MCFE_MAX_RAW_BUF] = {0};
static module_mcfe_buf_t mcfe_buffers_out[MCFE_MAX_OUT_BUF] = {0};

/**
 * @brief      Gets the resource pool.
 *
 * @param[in]  type  Buffer type
 *
 * @return     Struct describing the available resources. 
 *
 */
static module_mcfe_buf_pool_t get_pool_by_type( const mcfe_hwif_buf_type_t type )
{
    switch ( type ) {

    case MCFE_BUF_TYPE_RAW:
        return ( module_mcfe_buf_pool_t ){
            .buffers = mcfe_buffers_raw,
            .buffers_max = MCFE_MAX_RAW_BUF};
    case MCFE_BUF_TYPE_OUT:
        return ( module_mcfe_buf_pool_t ){
            .buffers = mcfe_buffers_out,
            .buffers_max = MCFE_MAX_OUT_BUF};
    default:
        /* Unexpected branch */
        assert( NULL );
    }
}

/**
 * @brief      Gets the default data width.
 *
 * @param[in]  type The buffer type
 *
 * @return     The data width.
 *
 */
static uint8_t get_data_width( const mcfe_hwif_buf_type_t type )
{
    switch ( type ) {

    case MCFE_BUF_TYPE_RAW:
        return MCFE_BUF_DEFAULT_DW_RAW;
    case MCFE_BUF_TYPE_OUT:
        return MCFE_BUF_DEFAULT_DW_OUT;
    default:
        return 32;
    }
}

void module_mcfe_buf_init_pool( const mcfe_hwif_buf_type_t type )
{
    const module_mcfe_buf_pool_t pool = get_pool_by_type( type );
    size_t i;

    for ( i = 0; i < pool.buffers_max; ++i ) {
        pool.buffers[i].enabled = 0;
        pool.buffers[i].index = i;
        pool.buffers[i].type = type;

        /* We toggle buffer enable bit to clean up the status of the buffer. */
        mcfe_hwif_buff_enable( type, i, 0 );
        mcfe_hwif_buff_enable( type, i, 1 );
        mcfe_hwif_buff_enable( type, i, 0 );

        mcfe_hwif_buff_config( type,
                               i,
                               get_data_width( type ),
                               MCFE_DEFAULT_BUFFER_FLAGS,
                               0x0,
                               MCFE_BUF_DEFAULT_WIDTH * get_data_width( type ) / 8,
                               MCFE_BUF_DEFAULT_WIDTH,
                               MCFE_BUF_DEFAULT_HEIGHT );

        mcfe_hwif_buff_status_set( type, i, 0 );
    }
}

module_mcfe_buf_t *module_mcfe_buf_get_free( const mcfe_hwif_buf_type_t type )
{
    const module_mcfe_buf_pool_t pool = get_pool_by_type( type );

    size_t i;

    for ( i = 0; i < pool.buffers_max; ++i ) {
        if ( !pool.buffers[i].enabled ) {
            return &pool.buffers[i];
        }
    }

    return NULL;
}

size_t module_mcfe_buf_get_free_count( const mcfe_hwif_buf_type_t type )
{
    const module_mcfe_buf_pool_t pool = get_pool_by_type( type );

    size_t i, n = 0;
    for ( i = 0; i < pool.buffers_max; ++i ) {
        if ( !pool.buffers[i].enabled ) {
            n++;
        }
    }

    return n;
}

void module_mcfe_buf_destroy( module_mcfe_buf_t *const buffer )
{

    assert( buffer );

    buffer->enabled = 0;
    buffer->address = 0;

    mcfe_hwif_buff_enable( buffer->type, buffer->index, 0 );
    mcfe_hwif_buff_enable( buffer->type, buffer->index, 1 );
    mcfe_hwif_buff_enable( buffer->type, buffer->index, 0 );

    mcfe_hwif_buff_config( buffer->type,
                           buffer->index,
                           get_data_width( buffer->type ),
                           MCFE_DEFAULT_BUFFER_FLAGS,
                           0x0,
                           MCFE_BUF_DEFAULT_WIDTH * get_data_width( buffer->type ) / 8,
                           MCFE_BUF_DEFAULT_WIDTH,
                           MCFE_BUF_DEFAULT_HEIGHT );

    // Wait until buffer gets cancelled ( status = 7 or 1 or 0 )
    int iterations = 100, status;
    while ( iterations ) {
        status = mcfe_hwif_buff_status_get( buffer->type, buffer->index );
        if ( ( status == 1 ) || ( status == 0 ) || ( status == 7 ) ) {
            LOG( LOG_INFO, "Buffer (type %d) %d cancelled after %d ms with status %d.", buffer->type, buffer->index, 100 - iterations, status );
            break;
        }
        system_timer_usleep( 1000 );
        iterations--;
    }

    if ( !iterations ) {
        LOG( LOG_ERR, "Failed to cancel buffer %d after 100 ms (buffer status = %d).", buffer->index, status );
    }

    mcfe_hwif_buff_status_set( buffer->type, buffer->index, 0 );
}

module_mcfe_buf_t *module_mcfe_buf_create( module_mcfe_buf_cfg_t *const config )
{

    assert( config );

    if ( module_mcfe_buf_get_free_count( config->type ) == 0 ) {
        LOG( LOG_ERR, "Error, out of buffers. (type = %u)", config->type );
        return NULL;
    }

    // Find free buffer of specified type
    module_mcfe_buf_t *const buffer = module_mcfe_buf_get_free( config->type );

    //We assert for sanity here since we already checked if we have enough
    assert( buffer );

    buffer->enabled = 1;
    buffer->data_width = config->data_width;
    buffer->line_offset = config->line_offset;
    buffer->active_width = config->active_width;
    buffer->active_height = config->active_height;
    buffer->address = config->address;
    buffer->flags = config->flags;

    // Buffer hardware update.
    mcfe_hwif_buff_config( buffer->type,
                           buffer->index,
                           buffer->data_width,
                           buffer->flags,
                           buffer->address,
                           buffer->line_offset,
                           buffer->active_width,
                           buffer->active_height );

    mcfe_hwif_buff_enable( buffer->type, buffer->index, 1 );

    mcfe_hwif_buff_status_set( buffer->type, buffer->index, 0 );

    return buffer;
}
