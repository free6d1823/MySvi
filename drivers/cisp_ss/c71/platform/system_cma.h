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

#ifndef __SYSTEM_CMA_H__
#define __SYSTEM_CMA_H__
#include "system_types.h"

int system_cma_alloc( void **out_virtaddr, uint32_t *out_physaddr, uint32_t size );
void system_cma_free( uint32_t addr );
#endif /* __SYSTEM_CMA_H__ */
