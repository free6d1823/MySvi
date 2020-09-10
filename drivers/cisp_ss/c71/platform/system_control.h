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

#ifndef __SYSTEM_CONTROL_H__
#define __SYSTEM_CONTROL_H__

#include "system_types.h"

/**
 *   Initialize customer platform
 *
 *   This function is called by application before any other system routines
 *
 *   @return none
 */
void bsp_init( void );

void bsp_init_dv_case( void );

/**
 *   Destroys customer platform
 *
 *   This function is called by application after any other system routine
 *
 *   @return none
 */
void bsp_destroy( void );


#endif // __SYSTEM_CONTROL_H__
