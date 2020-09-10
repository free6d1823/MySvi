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

#include "util_queue.h"
#include "system_stdlib.h"
#include "system_types.h"

void aqueue_create( aqueue *hndl, void **holders, uint32_t max_size )
{
    system_memset( hndl, 0, sizeof( *hndl ) );

    hndl->max_size = max_size;
    hndl->array = holders;
}

void aqueue_destroy( aqueue *hndl )
{
    system_memset( hndl, 0, sizeof( *hndl ) );
}

int aqueue_enqueue( aqueue *hndl, void *element )
{
    if ( hndl->filled < hndl->max_size ) {
        hndl->array[hndl->head] = element;
        hndl->head = ( hndl->head + 1 ) % hndl->max_size;
        hndl->filled++;
    } else {
        return -1;
    }

    return 0;
}

void *aqueue_dequeue( aqueue *hndl )
{
    void *element = NULL;

    if ( hndl->filled == 0 ) {
        return NULL;
    }

    element = hndl->array[hndl->tail];
    hndl->array[hndl->tail] = NULL;
    hndl->tail = ( hndl->tail + 1 ) % hndl->max_size;
    hndl->filled--;

    return element;
}

uint32_t aqueue_size( aqueue *hndl )
{
    return hndl->filled;
}
