#ifndef HAL_COMDEF_H
#define HAL_COMDEF_H
/*
==============================================================================

FILE:         HALcomdef.h

DESCRIPTION:

==============================================================================

                             Edit History

$Header$

when       who     what, where, why
--------   ---     -----------------------------------------------------------
06/17/10   sc      Included comdef.h and cleaned up typedefs
05/15/08   gfr     Added HAL_ENUM_32BITS macro.
02/14/08   gfr     Added bool32 type.
11/13/07   gfr     Removed dependency on comdef.h
01/08/07   hxw     Created

==============================================================================
Copyright (c) 2006,2010
Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
==============================================================================
*/


/*
 * Assembly wrapper
 */
#ifndef _ARM_ASM_

/*
 * C++ wrapper
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* -----------------------------------------------------------------------
** Types
** ----------------------------------------------------------------------- */

/*
 * Macro to allow forcing an enum to 32 bits.  The argument should be
 * an identifier in the namespace of the enumeration in question, i.e.
 * for the clk HAL we might use HAL_ENUM_32BITS(CLK_xxx).
 */
#define HAL_ENUM_32BITS(x) HAL_##x##_FORCE32BITS = 0x7FFFFFFF

/*===========================================================================

FUNCTION inp, outp, inpw, outpw, inpdw, outpdw

DESCRIPTION
  IN/OUT port macros for byte and word ports, typically inlined by compilers
  which support these routines

PARAMETERS
  inp(   xx_addr )
  inpw(  xx_addr )
  inpdw( xx_addr )
  outp(   xx_addr, xx_byte_val  )
  outpw(  xx_addr, xx_word_val  )
  outpdw( xx_addr, xx_dword_val )
      xx_addr      - Address of port to read or write (may be memory mapped)
      xx_byte_val  - 8 bit value to write
      xx_word_val  - 16 bit value to write
      xx_dword_val - 32 bit value to write

DEPENDENCIES
  None

RETURN VALUE
  inp/inpw/inpdw: the byte, word or dword read from the given address
  outp/outpw/outpdw: the byte, word or dword written to the given address

SIDE EFFECTS
  None.

===========================================================================*/

  /* ARM based targets use memory mapped i/o, so the inp/outp calls are
  ** macroized to access memory directly
  */

  #define inp(port)         (*((volatile uint8_t *) (port)))
  #define inpw(port)        (*((volatile uint16_t *) (port)))
  #define inpdw(port)       (*((volatile uint32_t *)(port)))
  #define inpqw(port)       (*((volatile uint64_t *)(port)))
  #define inp32(port)       (*((volatile uint32_t *)(port)))
  #define inp64(port)       (*((volatile uint64_t *)(port)))

  #define outp(port, val)   (*((volatile uint8_t *) (port)) = ((uint8_t) (val)))
  #define outpw(port, val)  (*((volatile uint16_t *) (port)) = ((uint16_t) (val)))
  #define outpdw(port, val) (*((volatile uint32_t *) (port)) = ((uint32_t) (val)))
  #define outpqw(port, val) (*((volatile uint64_t *) (port)) = ((uint64_t) (val)))
  #define outp32(port, val) (*((volatile uint32_t *) (port)) = ((uint32_t) (val)))
  #define outp64(port, val) (*((volatile uint64_t *) (port)) = ((uint64_t) (val)))

#ifdef __cplusplus
}
#endif

#endif /* !_ARM_ASM_ */

#endif /* HAL_COMDEF_H */

