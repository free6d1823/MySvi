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

#include "system_platform.h"

uintptr_t system_platform_get_regbase_paddr( system_platform_device_t device, unsigned int id )
{
    return 0;
}

size_t system_platform_get_regsize( system_platform_device_t device, unsigned int id )
{
    return 0;
}

volatile void *system_platform_get_regbase_vaddr( system_platform_device_t device, unsigned int id )
{
    return NULL;
}

int system_platform_init( void )
{
    return 0;
}

void system_platform_deinit( void )
{
}
