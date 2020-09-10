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

#ifndef __SYSTEM_PLATFORM_H__
#define __SYSTEM_PLATFORM_H__

#include "system_platform_device_numbers.h"

/**
 * @brief      Initialize system layer.
 */
int system_platform_init( void );


/**
 * @brief      Deinitialize system layer.
 */
void system_platform_deinit( void );


/**
 * @brief      Get the virtual address of the MMIO for a given device, suitable for usage within driver code.
 *
 * @param[in]  device           The device type, see @ref system_platform_device_t
 * @param[in]  id               The device ID, if applicable (used for example for sensors)
 *
 * @return     The virtual address, or NULL on error
 */
volatile void *system_platform_get_regbase_vaddr( system_platform_device_t device, unsigned int id );

/**
 * @brief      Get the physical address of the MMIO for a given device.
 *
 * @param[in]  device           The device type, see @ref system_platform_device_t
 * @param[in]  id               The device ID, if applicable (used for example for sensors)
 *
 * @return     The virtual address, or 0 on error
 */
uintptr_t system_platform_get_regbase_paddr( system_platform_device_t device, unsigned int id );

/**
 * @brief      Get the mapped size of the MMIO for a given device.
 *
 * @param[in]  device           The device type, see @ref system_platform_device_t
 * @param[in]  id               The device ID, if applicable (used for example for sensors)
 *
 * @return     The mapped size, or 0 on error
 */
size_t system_platform_get_regsize( system_platform_device_t device, unsigned int id );

#endif /* __SYSTEM_PLATFORM_H__ */
