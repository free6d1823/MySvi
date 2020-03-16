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
* @file common_defs.c
*
* @par Description:
*    This module provides a common set of definitions / utilities to be used
*    accross various Monaco related software components.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <target/ring.h>

/******************************************************************************
* Defined Constants
******************************************************************************/


/******************************************************************************
* Derived data types
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    Control used to globally indicate the level of detailed information
*     that should be reported / displayed.
*
******************************************************************************/
importance_t log_level = CRITICAL;


/*!****************************************************************************
*
* @par Description
*    Flag used to globally indicate if detailed information should be
*     should be reported / displayed.
*
******************************************************************************/
bool   verbose_mode = false;


/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/


/******************************************************************************
* External Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function determines the base 2 log of the given value.
*
*                                  @param
*  val              The value whose log2 is being determined. Must be a power of 2.
*
*
* @return
*    The base 2 log of the given value. 0 if the input is 0.
*
******************************************************************************/
int com_log2(unsigned val)
{
    int log_val;
    unsigned mask;


    mask = 0x1;

    if (val != 0)
    {
        log_val = 0;

        while ((val & mask) != mask)
        {
            val = val >> 1;
            log_val = log_val + 1;
        }
    }
    else
    {
        log_val = 0;
    }

    return log_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function performs a divide paired with a ceiling operation.
*
*                                  @param
*    dividend       The dividend of the divide operation.
*                                  @param
*    divisor        The divisor of the divide operation.
*
*
* @return
*    The ceilinged result of the divide.
*
******************************************************************************/
int com_ceil_div(uint32_t dividend, uint32_t divisor)
{
    uint32_t result;
    uint32_t remainder;


    result = dividend / divisor;
    remainder = dividend % divisor;

    if (remainder != 0)    //ceiling FN (round up if remainder)
    {
        ++result;
    }

    return result;
}


/*!****************************************************************************
*
* @par Description:
*    This function performs a divide paired with a ceiling operation for 64-bit
*     unsigned integer type.
*
*                                  @param
*    dividend       The dividend of the divide operation.
*                                  @param
*    divisor        The divisor of the divide operation.
*
*
* @return
*    The ceilinged result of the divide.
*
******************************************************************************/
uint64_t com_ceil_div_64(uint64_t dividend, uint64_t divisor)
{
    uint64_t result;
    uint64_t remainder;


    result = dividend / divisor;
    remainder = dividend % divisor;

    if (remainder != 0)    //ceiling FN (round up if remainder)
    {
        ++result;
    }

    return result;
}


/*!****************************************************************************
*
* @par Description:
*    This function does a byte wise block copy.
*
*                                  @param
*    src_ptr        Pointer to the source data to copy.
*                                  @param
*    dst_ptr        Pointer to the destination to receive the copied data.
*                                  @param
*    size_bytes     Size of the block to copy in bytes.
*
*
* @return
*    COM_OK if the copy was successful, COM_ERROR otherwise.
*
******************************************************************************/
unsigned com_blk_copy(uint8_t *src_ptr, uint8_t *dst_ptr, uint16_t size_bytes)
{
    unsigned status = -1;
    uint16_t byte_num;


    if((src_ptr != NULL) && (dst_ptr != NULL))
    {
        status = 0;

        for(byte_num = 0; byte_num < size_bytes; ++byte_num)
        {
            *dst_ptr = *src_ptr;
            ++dst_ptr;
            ++src_ptr;
        }
    }

    return status;
}



/******************************************************************************
* Local Functions
******************************************************************************/


