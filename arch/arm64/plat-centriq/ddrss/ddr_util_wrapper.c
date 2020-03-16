/** @file ddr_util_wrapper.c

  Utility wrapper functions for supporting a single instance DDR driver.

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
**/


/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include <target/ddr.h>
#include <stddef.h>

/*===========================================================================
                                 DATA
===========================================================================*/ 
extern ddr_func_tbl ddr_function_table;

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 
/* ============================================================================
**  Function : ddr_wait_us
** ===========================================================================*/
bool ddr_wait_us(uint32_t us_to_wait)
{
    if(ddr_function_table.util.wait_us != NULL)
    {
        return ddr_function_table.util.wait_us(us_to_wait);
    }
    else
    {
        return false;
    }
}   


/* ============================================================================
**  Function : ddr_wait_us
** ===========================================================================*/
int ddr_printf(const char * fmt, va_list vargs)
{
    if(ddr_function_table.util.printf != NULL)
    {
        return ddr_function_table.util.printf(fmt, vargs);
    }
    else
    {
        return false;
    }
}
