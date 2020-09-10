//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2020] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifndef ACAMERA_3A_MATH_H__
#define ACAMERA_3A_MATH_H__

#include "3a/misc/acamera_types.h"

//#ifdef __KERNEL__
#if 0
#include <asm/div64.h>
#include "linux/math64.h"
#endif


uint64_t acamera_div64_u64( uint64_t x, uint64_t y );


static inline uint32_t acamera_abs_int32( int32_t val )
{
    int32_t ret = 0;

    ret = ( val < 0 ) ? -val : val;

    return (uint32_t)ret;
}


static inline uint64_t acamera_abs_int64( int64_t val )
{
    int64_t ret = 0;

    ret = ( val < 0 ) ? -val : val;

    return (uint64_t)ret;
}


#ifndef U16_MAX
#define U16_MAX 0xFFFFu
#endif

uint16_t acamera_max_u16( uint16_t arg1, uint16_t arg2 );
uint16_t acamera_min_u16( uint16_t arg1, uint16_t arg2 );
uint32_t acamera_max_u32( uint32_t arg1, uint32_t arg2 );
uint32_t acamera_min_u32( uint32_t arg1, uint32_t arg2 );

uint16_t acamera_sqrt32( uint32_t arg );
uint32_t acamera_log2_int_to_fixed( const uint32_t val, const uint8_t out_precision, const uint8_t shift_out );
uint32_t acamera_log2_fixed_to_fixed( const uint32_t val, const int32_t in_fix_point, const uint8_t out_fix_point );
uint32_t acamera_math_exp2( uint32_t val, const uint8_t shift_in, const uint8_t shift_out );
uint16_t acamera_calc_modulation_u16( uint16_t x, const modulation_entry_t *p_table, uint32_t table_len );

int32_t acamera_signed_right_shift( int32_t val, uint32_t times );
int32_t acamera_interpl_linear( const int32_t x, const int32_t x0, const int32_t y0, const int32_t x1,
                                const int32_t y1 );

#endif /* ACAMERA_3A_MATH_H__ */
