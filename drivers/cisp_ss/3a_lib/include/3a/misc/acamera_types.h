//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2020] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifndef ACAMERA_TYPES_H
#define ACAMERA_TYPES_H


//#ifndef __KERNEL__
#if 1
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#else /*__KERNEL__*/

#include "linux/kernel.h"
#include "linux/string.h" // For memset
#include "linux/types.h"


#endif /*ndef __KERNEL__*/


#ifndef MODULATION_ENTRY_DEFINED
#define MODULATION_ENTRY_DEFINED
typedef struct {
    uint16_t x, y;
} modulation_entry_t;
#endif /*MODULATION_TYPES_DEFINED*/

#endif /* ACAMERA_TYPES_H */
