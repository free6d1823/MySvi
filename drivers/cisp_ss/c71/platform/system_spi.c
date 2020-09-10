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

#include "system_spi.h"

int32_t system_spi_init( volatile void *regs )
{
    return 0;
}

uint32_t system_spi_rw48( uint32_t sel_mask, uint32_t control_inp, uint32_t address, uint8_t addr_size, uint32_t data, uint8_t data_size )
{
    return 0;
}

uint32_t system_spi_rw32( uint32_t sel_mask, uint32_t control, uint32_t data, uint8_t data_size )
{
    return 0;
}
