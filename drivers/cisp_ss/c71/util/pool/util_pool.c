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

#include "util_pool.h"
#include "system_stdlib.h"
#include "system_types.h"

static apool_element *apool_find( apool *hndl, void *data )
{
    int i;

    for ( i = 0; i < hndl->current_size; ++i ) {
        if ( hndl->elements[i].data == data ) {
            return &hndl->elements[i];
        }
    }

    return NULL;
}

void apool_create( apool *hndl, apool_element *elements, uint32_t max_size )
{
    system_memset( hndl, 0, sizeof( *hndl ) );

    hndl->current_size = 0;
    hndl->max_size = max_size;
    hndl->elements = elements;
}

void apool_destroy( apool *hndl )
{
    system_memset( hndl, 0, sizeof( *hndl ) );
}

int apool_add( apool *hndl, void *data )
{
    apool_element *elem;

    if ( hndl->current_size >= hndl->max_size ) {
        return -1;
    }

    if ( apool_find( hndl, data ) != NULL ) {
        return -1;
    }

    elem = &hndl->elements[hndl->current_size++];
    elem->data = data;

    return 0;
}

void *apool_remove( apool *hndl, void *data )
{
    apool_element *elem = apool_find( hndl, data );
    if ( elem == NULL ) {
        return NULL;
    }

    // Swap and reduce current size
    *elem = hndl->elements[--hndl->current_size];

    // elem should not be used anymore in this function
    // elem->data == data because of apool_find
    return data;
}

void *apool_remove_used( apool *hndl )
{
    if ( hndl->current_size == 0 ) {
        return NULL;
    }

    // hndl->elements[hndl->current_size - 1] is guaranteed to be used
    void *data = hndl->elements[hndl->current_size - 1].data;

    // Swapping last used element with itself (as above) is a no-op...
    --hndl->current_size;

    return data;
}

int apool_contains( apool *hndl, void *data )
{
    apool_element *elem;
    elem = apool_find( hndl, data );

    if ( !elem ) {
        return -1;
    }

    return 0;
}

uint32_t apool_size( apool *hndl )
{
    return hndl->current_size;
}