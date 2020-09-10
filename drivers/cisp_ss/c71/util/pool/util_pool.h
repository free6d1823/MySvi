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

#ifndef __UTIL_POOL_H__
#define __UTIL_POOL_H__

#include "system_types.h"

typedef struct _apool_element_t apool_element;
struct _apool_element_t {
    void *data; //Ptr do data
};

typedef struct _apool_t apool;
struct _apool_t {
    uint32_t max_size;       //Max elements in pool
    uint32_t current_size;   //Current element count
    apool_element *elements; //Ptr to element array
};

/**
 * @brief   Initializes pool data structure
 *
 * @param   hndl handle to apool data structure
 * @param   elements ptr to element array
 * @param   max_size max amount of elements to handle
 *
 * @return  0 on success
 *
 * @details This function should be called by the user to initialise the pool
 */
void apool_create( apool *hndl, apool_element *elements, uint32_t max_size );

/**
 * @brief   Deinitializes pool data structure
 *
 * @param   hndl handle to apool data structure
 *
 * @return  0 on success
 *
 * @details This function should be called when the user has finished using the pool
 */
void apool_destroy( apool *hndl );

/**
 * @brief   Adds an element to the pool
 *
 * @param   hndl handle to apool data structure
 * @param   dat Ptr to stored data
 *
 * @return  0 on success
 *
 * @details This function should be called when the user want to add an element to the pool
 */
int apool_add( apool *hndl, void *data );

/**
 * @brief   Removes an element to the pool
 *
 * @param   hndl handle to apool data structure
 * @param   data Ptr to stored data to compare with
 *
 * @return  The data of the matching removed element (if any), or NULL.
 *
 * @details This function should be called when the user want to remove an element to the pool
 */
void *apool_remove( apool *hndl, void *data );

/**
 * @brief   Returns a random in use element
 *
 * @param   hndl handle to apool data structure
 *
 * @return  The data of the removed used element (if any), or NULL.
 *
 * @details This function should be called when the user want to remove an arbitrary
 *          in use element to the pool
 */
void *apool_remove_used( apool *hndl );

/**
 * @brief   Checks wether a specific data is contained in the pool
 *
 * @param   hndl handle to apool data structure
 *
 * @param   data ptr to adress of data
 *
 * @return  Returns a 0 when the elements is contained in the pool
 *
 * @details This function should be called when the user want to remove an arbitrary
 *          in use element to the pool
 */
int apool_contains( apool *hndl, void *data );

/**
 * @brief   Returns count of elements in pool
 *
 * @param   hndl handle to apool data structure
 *
 * @return  0 on success
 *
 * @details This function should be called when the user want to check the count
 *          of in use elements in the pool
 */
uint32_t apool_size( apool *hndl );

#endif