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

#ifndef __SYSTEM_CACHE_H__
#define __SYSTEM_CACHE_H__

/**
 *   Enable instruction cache
 *
 *   @return  None
 */
void system_inst_cache_enable( void );

/**
 *   Disable instruction cache
 *
 *   @return  None
 */
void system_inst_cache_disable( void );

/**
 *   Enable data cache
 *
 *   @return  None
 */
void system_data_cache_enable( void );

/**
 *   Enable data cache
 *
 *   @return  None
 */
void system_data_cache_disable( void );

/**
 *   Invalidate data cache
 *
 *   @return  None
 */
void system_data_cache_inv( void );

/**
 *   Flush data cache
 *
 *   @return  None
 */
void system_data_cache_flush( void );

/**
 *   Invalidate data cache range
 *
 *   @param
 *        phys_addr - Physical address
 *        size - Size in bytes
 *
 *   @return  None
 */
void system_data_cache_inv_range( unsigned long phys_addr, unsigned long size );

/**
 *   Flush data cache range
 *
 *   @param
 *        phys_addr - Physical address
 *        size - Size in bytes
 *
 *   @return  None
 */
void system_data_cache_flush_range( unsigned long phys_addr, unsigned long size );

#endif /* __SYSTEM_CACHE_H__ */
