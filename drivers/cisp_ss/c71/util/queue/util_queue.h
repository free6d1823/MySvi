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

#ifndef __UTIL_QUEUE_H__
#define __UTIL_QUEUE_H__

#include "system_types.h"

typedef struct aqueue_t aqueue;
struct aqueue_t {
    uint32_t filled;   //Amount of in use elements inside of the queue
    uint32_t head;     //Id of the ring buffer head
    uint32_t tail;     //Id of the ring buffer tail
    uint32_t max_size; //Max elements that could be handled by the queue
    void **array;      //Array of elements
};

/**
 * @brief   Initializes queue data structure
 *
 * @param   hndl handle to aqueue data structure
 * @param   holders ptr to array of holders
 * @param   max_size max amount of elements to handle
 *
 * @return  0 on success
 *
 * @details This function should be called by the user to initialise the queue
 */
void aqueue_create( aqueue *hndl, void **holders, uint32_t max_size );

/**
 * @brief   Deinitializes queue data structure
 *
 * @param   hndl handle to aqueue data structure
 *
 * @return  0 on success
 *
 * @details This function should be called by the user to deinitialise the queue
 */
void aqueue_destroy( aqueue *hndl );

/**
 * @brief   Enqueue data in the queue
 *
 * @param   hndl handle to aqueue data structure
 *
 * @return  0 on success
 *
 * @details This function should be called by the user to enqueue an element
 */
int aqueue_enqueue( aqueue *hndl, void *element );

/**
 * @brief   Dequeue data in the queue
 *
 * @param   hndl handle to aqueue data structure
 *
 * @return  0 on success
 *
 * @details This function should be called by the user to dequeue an element
 */
void *aqueue_dequeue( aqueue *hndl );

/**
 * @brief   Returns number of elements in queue
 *
 * @param   hndl handle to aqueue data structure
 *
 * @return  0 on success
 *
 * @details This function should be called by the user to query the number of
 *          elements contained in the queue
 */
uint32_t aqueue_size( aqueue *hndl );

#endif