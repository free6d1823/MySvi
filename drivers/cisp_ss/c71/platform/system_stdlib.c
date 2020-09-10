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

#include "system_stdlib.h"


#include <string.h>
#include <target/cache.h>
int32_t system_memcpy( void *dst, const void *src, uint32_t size )
{
    int32_t result = 0;
    memcpy( dst, src, size );
    return result;
}


int32_t system_memset( void *ptr, uint8_t value, uint32_t size )
{
    int32_t result = 0;
    memset( ptr, value, size );
    return result;
}


int32_t system_memcpy_phy2phy( uint32_t dst_addr, uint32_t src_addr, uint32_t size )
{
    /* not implemented*/
	uint32_t *dst = (uint32_t*)(uintptr_t)dst_addr;
	uint32_t *src = (uint32_t*)(uintptr_t)src_addr;
  	memcpy( dst, src, size );
	flush_dcache_area(dst, size);
  return -1;
}


int32_t system_memcpy_vir2phy( uint32_t dst_addr, void *src, uint32_t size )
{
    /* not implemented*/
    return -1;
}
