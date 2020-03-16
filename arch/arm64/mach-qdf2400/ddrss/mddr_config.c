/** @file ddr.c

  Functions for specail mach DDR

  Copyright (c) 2019-2020 Huaxintong Semiconductor Technology Co., Ltd.
  All Rights Reserved.
  Confidential and Proprietary - Huaxintong Semiconductor Technology Co., Ltd.

**/

#include <target/ddr.h>

// logical channel to physical table
uint8_t hddrss_instance_list[DDR_MAX_NUM_CHANS] = {2, 3, 5, 4, 0, 1};
//Physical channle to logical table
uint8_t physical_instance_list[DDR_MAX_NUM_CHANS] = {4, 5, 0, 1, 3, 2};

/* ============================================================================
**  Function : logical channel to physical table
** ===========================================================================*/
uint8_t ddr_logical_to_physical_channel(uint8_t logical_ch)
{
	return hddrss_instance_list[logical_ch];
}

/* ============================================================================
**  Function : Physical channle to logical table
** ===========================================================================*/
uint8_t ddr_physical_to_logical_channel(uint8_t physical_ch)
{
	return physical_instance_list[physical_ch];
}
