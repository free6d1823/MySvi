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

/** @file util_crc16.h
    @addtogroup
    @{
*/

#ifndef _UTIL_CRC16_H_
#define _UTIL_CRC16_H_

#include "util_crc.h" //config

#if CRC16_POLY_CCITT
uint16_t acrc_ccitt_memory( const uint16_t init, const unsigned char *data,
                            const size_t sz );
uint16_t acrc_ccitt_byte( const uint16_t init, const unsigned char byte );
#endif /*CRC16_POLY_CCITT*/

#endif

/** @}*/