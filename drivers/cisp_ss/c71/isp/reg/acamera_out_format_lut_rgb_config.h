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

#ifndef __ACAMERA_OUT_FORMAT_LUT_RGB_CONFIG_H__
#define __ACAMERA_OUT_FORMAT_LUT_RGB_CONFIG_H__

#include "system_isp_io.h"

// File generated by isp_config.py

// ------------------------------------------------------------------------------ //
// Instance 'out_format_lut_rgb' of module 'out_format_lut'
// ------------------------------------------------------------------------------ //

#define ACAMERA_OUT_FORMAT_LUT_RGB_BASE_ADDR ( 0x10c00 )
#define ACAMERA_OUT_FORMAT_LUT_RGB_SIZE ( 0x400 )

#define ACAMERA_OUT_FORMAT_LUT_RGB_ARRAY_DATA_DEFAULT ( 0x0 )
#define ACAMERA_OUT_FORMAT_LUT_RGB_ARRAY_DATA_DATASIZE ( 32 )
#define ACAMERA_OUT_FORMAT_LUT_RGB_ARRAY_DATA_OFFSET ( 0x10c00 )

// args: index (0-255), data (32-bit)
static __inline void acamera_out_format_lut_rgb_array_data_write( uint32_t base, uint32_t index, uint32_t data )
{
    system_isp_write_32( base + 0x10c00 + ( index << 2 ), data );
}
static __inline uint32_t acamera_out_format_lut_rgb_array_data_read( uint32_t base, uint32_t index )
{
    return system_isp_read_32( base + 0x10c00 + ( index << 2 ) );
}
// ------------------------------------------------------------------------------ //
#endif //__ACAMERA_OUT_FORMAT_LUT_RGB_CONFIG_H__
