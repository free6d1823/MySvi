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

/**
 * @file bitop.h
 * @brief      Header file for bit manipulation
 */

#ifndef _BITOP_H_
#define _BITOP_H_ 0
#include "system_types.h"

#if 0//( __KERNEL__ )
#include "linux/bitops.h" //Linux has a BIT macro already
#endif

#ifndef BIT
/**
 * @brief      Create a bitmask of one bit position n
 *
 * @param      n     bit position
 *
 * @return     bitmask
 *
 * @details    Usage:
 * @code
 *  x |= BIT(3); //Sets bit 3 in x
 * @endcode
 */
#define BIT( n ) \
    ( 1UL << ( n ) )

#endif /*BIT*/


#ifndef BITFIELD
/**
 * @brief      Creates a bit mask of length l
 *
 * @param[in]  x     Number of bits in mask
 *
 * @return     Bitmask where if x = 4 the return value would be 0b1111
 *
 * @details    Usage:
 * @code
 *   x &= BITFIELD(4); //Mask lower 4 bits of x.
 * @endcode
 *
 * @warning    This function will only work for bit fields of up to and
 *             including unsigned long for bigger fields consider changing the
 *             type
 */
static inline unsigned long BITFIELD( const size_t x )
{
    return ( x >= sizeof( unsigned long ) * 8 ) ? (unsigned long)-1 : ( BIT( x ) ) - 1;
}
#endif /*BITFIELD*/

/**
 * @brief      Creates bit field mask
 *
 * @param      start   Lowest bit in mask
 * @param      length  Number of bits
 *
 * @return     Creates a bitmasks and shifts it by start, for example BF_MASK(1, 4) == 0b11110
 *
 * @details   This is useful for creating register bitmasks where values are more than one bit. Example:
 * @code
 *  x &= BF_MASK(5, 4); //Mask 4bit value at bit position 5.
 * @endcode
 */
#define BF_MASK( start, length ) \
    ( BITFIELD( length ) << ( start ) )


/**
 * @brief      Reads in value y shifts to right by right and masks.
 *
 * @param      y      bitfield to read.
 * @param      start  The start bit
 * @param      len    Number of bits in the field
 *
 * @return     Returns a bitfield from a value (for example register)
 *
 * @details    This is useful for reading register values.
 * @code
 *   uint8_t r = BF_GET(read_reg32(), 8, 8); //Read a byte from a 32 bit register and mask it.
 * @endcode
 */
#define BF_GET( y, start, len ) \
    ( ( ( y ) >> ( start ) ) & BITFIELD( len ) )

#define BF_PREP( x, start, len ) \
    ( ( (x)&BITFIELD( len ) ) << ( start ) )


/**
 * @brief      Sets a bitfield from x to y.
 *
 * @param      y      Target bitfield
 * @param      x      Source bitfield
 * @param      start  The start
 * @param      len    The length
 *
 * @return     The new value of y
 *
 * @details    Sets a bitfield in y to a value in x and returns new bit value.
 * @code
 *   reg = BF_SET(reg, 0xDEAD, 8, 16); //Set bits 23..8 to 0xDEAD
 * @endcode
 */
#define BF_SET( y, x, start, len ) \
    ( ( ( y ) & ~BF_MASK( start, len ) ) | BF_PREP( ( x ), start, len ) )


#endif
