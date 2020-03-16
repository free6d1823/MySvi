#ifndef _MODULE_COMMON_DEFS_H_
#define _MODULE_COMMON_DEFS_H_

/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file common_defs.h
*
* @par Description:
*    This header provides a common set of definitions to be used accross various
*    Monaco related software components.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <asm/mach/monaco/common/monaco_defs.h>

/******************************************************************************
* Defined Constants
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    Attribute marking a function parameter as intentionally unused. Quiets
*    compiler warnings for specific instances of unused parameters, allowing
*    unused parameter warnings for accidentally unused parameters.
*
******************************************************************************/
#define UNUSED_PARAM                    __attribute__((unused))


/*!****************************************************************************
*
* @defgroup barrier_ops CPU barrier operations
*
* @par Description
*    Group of constants to provide a set of assembly wrappers for common
*    barrier operations.
*
* @{
******************************************************************************/
#define DO_ISB     __asm__ volatile \
                ( \
                    "isb #0 \n\t" \
                );                      //!<  Do an instruction barrier.

#define DO_DSB     __asm__ volatile \
                ( \
                    "dsb #0 \n\t" \
                );                      //!<  Do a data sync barrier.

#define DO_DMB     __asm__ volatile \
                ( \
                    "dmb #0 \n\t" \
                );                      //!<  Do a data memory barrier.
/* @} */

/*!****************************************************************************
*
* @defgroup common_status_vals Common Status Values
*
* @par Description
*    Common status indicator values used to a common good bad indication.
*    Generally used to indicate this success / failure for various
*    functions and operations.
*
* @{
******************************************************************************/
#define COM_OK                  0x00
#define COM_ERROR               0xFF
/* @} */


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of millisecond(ms) per second to
*    allow translation of time bases.
*
******************************************************************************/
#define MILLI_SEC_PER_SEC        1000


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of microsecond(us) per millisecond(ms) to
*    allow translation of time bases.
*
******************************************************************************/
#define MICRO_SEC_PER_MILLI_SEC 1000


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of nanosecond(ns) per microsecond(us) to
*    allow translation of time bases.
*
******************************************************************************/
#define NANO_SEC_PER_MICRO_SEC  1000


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of picoseconds(ps) per nanosecond(ns) to
*    allow translation of time bases.
*
******************************************************************************/
#define PICO_SEC_PER_NANO_SEC   1000


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of picoseconds(ps) per microsecond(us)
*    to allow translation of time bases.
*
******************************************************************************/
#define PICO_SEC_PER_MICRO_SEC   (PICO_SEC_PER_NANO_SEC * NANO_SEC_PER_MICRO_SEC)


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of femtoseconds per picoseconds(ps) to
*    allow translation of time bases.
*
******************************************************************************/
#define FEMTO_SEC_PER_PICO_SEC   1000


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of megabytes per gigabyte to
*    allow translation of memory units.
*
******************************************************************************/
#define MB_PER_GB               1024


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of kilobytes per megabyte to
*    allow translation of memory units.
*
******************************************************************************/
#define KB_PER_MB            1024


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of bytes per kilobyte to
*    allow translation of memory units.
*
******************************************************************************/
#define BYTES_PER_KB            1024


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of bits per byte to
*    allow translation of memory units.
*
******************************************************************************/
#define BITS_PER_BYTE           8


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of kilohertz per megahertz to
*    allow translation of memory units.
*
******************************************************************************/
#define KHZ_PER_MHZ            1000


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of hertz per kilohertz to
*    allow translation of memory units.
*
******************************************************************************/
#define HZ_PER_KHZ             1000


/******************************************************************************
* Derived data types
******************************************************************************/



/******************************************************************************
* Global Variables
******************************************************************************/

extern importance_t log_level;

extern bool verbose_mode;

/******************************************************************************
* Macros
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This macro determines the maximum between two given values.
*
*                                  @param
*    val1           The first value to consider.
*                                  @param
*    val2           The second value to consider.
*
*
* @return
*    Maximum between the two values.
*
******************************************************************************/
#define COM_MAX(val1,val2) ((val1 > val2) ? val1 : val2)


/*!****************************************************************************
*
* @par Description:
*    This macro determines the minimum between two given values.
*
*                                  @param
*    val1           The first value to consider.
*                                  @param
*    val2           The second value to consider.
*
*
* @return
*    Minimum between the two values.
*
******************************************************************************/
#define COM_MIN(val1,val2) ((val1 < val2) ? val1 : val2)


/*!****************************************************************************
*
* @defgroup com_clk_converters SPD Clock Converters
*
* @par Description
*    Set of macros to convert between clock rates and time.
*
* @{
******************************************************************************/
#define COM_MHZ_TO_PS(freq_mhz)(1000000 / freq_mhz)
#define COM_KHZ_TO_PS(freq_khz)(1000000000 / freq_khz)
#define COM_PS_TO_MHZ(ps)(1000000 / ps)
#define COM_PS_TO_KHZ(ps)(1000000000 / ps)
/* @} */



/******************************************************************************
* Function Prototypes
******************************************************************************/

int com_log2(unsigned val);
int com_ceil_div(uint32_t dividend, uint32_t divisor);
uint64_t com_ceil_div_64(uint64_t dividend, uint64_t divisor);
unsigned com_blk_copy(uint8_t *src_ptr, uint8_t *dst_ptr, uint16_t size_bytes);


/*****************************************************************************/
#endif

