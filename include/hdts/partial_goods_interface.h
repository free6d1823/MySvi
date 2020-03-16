/*
 * Copyright (c) 2015 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */


#ifndef __PARTIAL_GOODS_INTERFACE_H__
#define __PARTIAL_GOODS_INTERFACE_H__

#include <bits/alltypes.h>

/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
**  Function :  sbl1_set_cpu_pg
** ==========================================================================
*/
/*!
*
* @brief
*   This function sets CPU PG mask
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
void sbl1_set_cpu_pg(uint64 cpu_mask);


/*===========================================================================
**  Function :  sbl1_get_cpu_pg
** ==========================================================================
*/
/*!
*
* @brief
*   This function gets CPU PG mask
*
* @par Dependencies
*   None
*
* @retval
*   uint64 64 bit value representing all cpu status
*
* @par Side Effects
*   None
*
*/
uint64 sbl1_get_cpu_pg(void);


/*===========================================================================
**  Function :  sbl1_get_default_cpu_pg
** ==========================================================================
*/
/*!
*
* @brief
*   This function gets default CPU PG mask
*
* @par Dependencies
*   None
*
* @retval
*   uint64 64 bit value representing all cpu status
*
* @par Side Effects
*   None
*
*/
uint64 sbl1_get_default_cpu_pg(void);


/*===========================================================================
**  Function :  sbl1_set_l3_pg
** ==========================================================================
*/
/*!
*
* @brief
*   This function sets L3 PG mask
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
void sbl1_set_l3_pg(uint64 l3_mask);


/*===========================================================================
**  Function :  sbl1_get_l3_pg
** ==========================================================================
*/
/*!
*
* @brief
*   This function gets L3 PG mask
*
* @par Dependencies
*   None
*
* @retval
*   uint64 64 bit value representing all l3 status
*
* @par Side Effects
*   None
*
*/
uint64 sbl1_get_l3_pg(void);


/*===========================================================================
**  Function :  sbl1_get_default_l3_pg
** ==========================================================================
*/
/*!
*
* @brief
*   This function gets default L3 PG mask
*
* @par Dependencies
*   None
*
* @retval
*   uint64 64 bit value representing all l3 status
*
* @par Side Effects
*   None
*
*/
uint64 sbl1_get_default_l3_pg(void);


boolean is_core_supported(unsigned int core);

#endif
