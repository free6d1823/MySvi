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

#include "3a/acamera_math.h"

/*----------  Static functions  ----------*/


static uint8_t leading_one_position( const uint32_t in )
{
    uint8_t pos = 0;
    uint32_t val = in;

    if ( val >= 0x10000u ) {
        val >>= 16u;
        pos += 16u;
    }
    if ( val >= 0x100u ) {
        val >>= 8u;
        pos += 8u;
    }
    if ( val >= 0x10u ) {
        val >>= 4u;
        pos += 4u;
    }
    if ( val >= 0x4u ) {
        val >>= 2u;
        pos += 2u;
    }
    if ( val >= 0x2u ) {
        pos += 1u;
    }

    return pos;
}


/*----------  Public functions  ----------*/

//  Solving y = log2(x)
//
//    input:  Integer: val
//    output: Fixed point x.y
//  y: out_precision
//
// coverity[misra_c_2012_rule_8_7_violation], Used internally but also is part of math lib API
uint32_t acamera_log2_int_to_fixed( const uint32_t val, const uint8_t out_precision, const uint8_t shift_out )
{
    uint32_t in = val;
    uint32_t ret = 0;
    uint32_t result = 0;

    if ( 0u == val ) {
        ret = 0;
    } else {
        uint8_t i;
        // integral part
        const uint32_t pos = (uint32_t)leading_one_position( val );
        // fractional part
        uint32_t a = ( pos <= 15u ) ? ( in << ( 15u - pos ) ) : ( in >> ( pos - 15u ) );
        for ( i = 0; i < out_precision; ++i ) {
            const uint32_t b = a * a;
            const uint32_t top_bit_mask = ( (uint32_t)1u << 31u );
            if ( ( b & top_bit_mask ) != 0u ) {
                result = ( result << 1u ) + 1u;
                a = b >> 16;
            } else {
                result = ( result << 1 );
                a = b >> 15;
            }
        }
        ret = ( uint32_t )( ( ( ( pos << out_precision ) + result ) << shift_out ) |
                            ( ( a & 0x7fffu ) >> ( 15u - shift_out ) ) );
    }
    return ret;
}


//  Solution for y = log2(x)
//
//    input:  Fixed point: x1.y1
//    output: Fixed point: x2.y2
//  y1: in_fraction
//  y2: out_precision
//
uint32_t acamera_log2_fixed_to_fixed( const uint32_t val, const int32_t in_fix_point, const uint8_t out_fix_point )
{
    return acamera_log2_int_to_fixed( val, out_fix_point, 0u ) - ( (uint32_t)in_fix_point << out_fix_point );
}


uint32_t acamera_math_exp2( uint32_t val, const uint8_t shift_in, const uint8_t shift_out )
{
    uint32_t ret = 0;
    const uint32_t l_shift_in = (uint32_t)shift_in;
    const uint32_t l_shift_out = (uint32_t)shift_out;
    static const uint32_t pow2_lut[33] = {
        1073741824, 1097253708, 1121280436, 1145833280, 1170923762, 1196563654, 1222764986, 1249540052, 1276901417,
        1304861917, 1333434672, 1362633090, 1392470869, 1422962010, 1454120821, 1485961921, 1518500250, 1551751076,
        1585730000, 1620452965, 1655936265, 1692196547, 1729250827, 1767116489, 1805811301, 1845353420, 1885761398,
        1927054196, 1969251188, 2012372174, 2056437387, 2101467502, 2147483648U};

    uint32_t fract_part = ( val & ( ( (uint32_t)1u << l_shift_in ) - 1u ) );
    uint32_t int_part = val >> l_shift_in;

    if ( shift_in <= 5u ) {
        uint32_t lut_index = fract_part << ( 5u - l_shift_in );
        ret = pow2_lut[lut_index] >> ( 30u - l_shift_out - int_part );
    } else {
        const uint32_t lut_index = fract_part >> ( l_shift_in - 5u );
        const uint32_t lut_fract = fract_part & ( ( (uint32_t)1u << ( l_shift_in - 5u ) ) - 1u );
        const uint64_t a = (uint64_t)pow2_lut[lut_index];
        const uint64_t b = (uint64_t)pow2_lut[lut_index + 1u];
        uint64_t res = ( ( b - a ) * (uint64_t)lut_fract ) >> ( shift_in - 5u );

        ret = ( uint32_t )( ( res + a ) >> ( 30u - l_shift_out - int_part ) );
    }

    return ret;
}

uint16_t acamera_sqrt32( uint32_t arg )
{
    const uint32_t mask = (uint32_t)1u << 15u;
    uint32_t res = 0u;
    uint32_t i;

    for ( i = 0; i < 16u; i++ ) {
        const uint32_t next = (uint32_t)mask >> i;
        if ( ( ( res + next ) * ( res + next ) ) <= arg ) {
            res += next;
        }
    }

    return (uint16_t)res;
}


uint16_t acamera_calc_modulation_u16( uint16_t x, const modulation_entry_t *p_table, uint32_t table_len )
{
    uint16_t ret = 0;
    if ( x <= p_table->x ) {
        ret = p_table->y;
    } else if ( x >= p_table[table_len - 1u].x ) {
        ret = p_table[table_len - 1u].y;
    } else {
        uint32_t i;
        for ( i = 1u; i < table_len; ++i ) {
            if ( x < p_table[i].x ) {
                break;
            }
        }
        if ( ( p_table[i].x - p_table[i - 1u].x ) != 0u ) {
            uint16_t alpha = ( ( x - p_table[i - 1u].x ) * 256u ) /
                             ( p_table[i].x - p_table[i - 1u].x ); // division by zero is checked
            ret = ( ( p_table[i].y * alpha ) + ( p_table[i - 1u].y * ( 256u - alpha ) ) ) >> 8;
        } else {
            ret = p_table[i].y;
        }
    }
    return ret;
}


uint16_t acamera_max_u16( uint16_t arg1, uint16_t arg2 )
{
    uint16_t result = arg1;

    if ( arg2 > arg1 ) {
        result = arg2;
    }

    return result;
}


uint16_t acamera_min_u16( uint16_t arg1, uint16_t arg2 )
{
    uint16_t result = arg1;

    if ( arg2 < arg1 ) {
        result = arg2;
    }

    return result;
}


uint32_t acamera_max_u32( uint32_t arg1, uint32_t arg2 )
{
    uint32_t result = arg1;

    if ( arg2 > arg1 ) {
        result = arg2;
    }

    return result;
}


uint32_t acamera_min_u32( uint32_t arg1, uint32_t arg2 )
{
    uint32_t result = arg1;

    if ( arg2 < arg1 ) {
        result = arg2;
    }

    return result;
}

uint64_t acamera_div64_u64( uint64_t x, uint64_t y )
{
#ifdef 0//__KERNEL__
    return div64_u64( x, y );
#else
    return x / y;
#endif
}

// @brief Misra C compliant routine for right shift op on signed integers
//
// @param[in]  val    The value
// @param[in]  times  Number of places to shift.
//
// @return    Right shifted int32_t value.
//
int32_t acamera_signed_right_shift( int32_t val, uint32_t times )
{
    uint32_t res = (uint32_t)val;
    uint32_t mask = 0x80000000;

    if ( ( res & mask ) == 0u ) {
        res = res >> times;
    } else {
        uint32_t i;
        for ( i = 0; i < times; i++ ) {
            res = res >> 1;
            res = res | mask;
        }
    }

    return (int32_t)res;
}

//
// @brief      Performs linear interpoletion given two points on a line and a new value of x.
//
// @param[in]  x     Value to interpolate
// @param[in]  x0    First point x location
// @param[in]  y0    First point y location
// @param[in]  x1    Second point x location
// @param[in]  y1    Second point y location
//
// @return     Interpolated value
//
int32_t acamera_interpl_linear( const int32_t x, const int32_t x0, const int32_t y0, const int32_t x1,
                                const int32_t y1 )
{
    int32_t res = 0;

    if ( x1 == x0 ) {
        res = y0;
    } else {
        // Using 64bit math here to avoid overflow.
        const int64_t i64_x = (int64_t)x;
        const int64_t i64_x0 = (int64_t)x0;
        const int64_t i64_y0 = (int64_t)y0;
        const int64_t i64_x1 = (int64_t)x1;
        const int64_t i64_y1 = (int64_t)y1;
        const int64_t i64_dy = i64_y1 - i64_y0;
        const int64_t i64_dx = i64_x1 - i64_x0;
        res = ( int32_t )( i64_y0 + ( ( i64_dy * ( i64_x - i64_x0 ) ) / ( i64_dx ) ) ); // division by zero is checked
    }

    return res;
}
