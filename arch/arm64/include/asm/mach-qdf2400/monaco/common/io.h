#ifndef _IO_H
#define _IO_H

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
* @file io.h
*
* @par Description:
*    This module provides a common set of definitions to access the memory and
*      the configuration space in the system.
*
******************************************************************************/

#include <stdint.h>

#define read8(addr) (*((volatile uint8_t *) (addr)))
#define write8(addr, val) (*((volatile uint8_t *) (addr)) = ((uint8_t) (val)))
#define read16(addr) (*((volatile uint16_t *) (addr)))
#define write16(addr, val) (*((volatile uint16_t *) (addr)) = ((uint16_t) (val)))
#define read32(addr) (*((volatile uint32_t *) (addr)))
#define write32(addr, val) (*((volatile uint32_t *) (addr)) = ((uint32_t) (val)))
#define read64(addr) (*((volatile uint64_t *) (addr)))
#define write64(addr, val) (*((volatile uint64_t *) (addr)) = ((uint64_t) (val)))

#endif

