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

#ifndef __UTIL_ADDR_CALC_H__
#define __UTIL_ADDR_CALC_H__

//SYSPHY - system physical addr ; ISPAS - ISP address space
#define ADDR_SYSPHY2ISPAS( x ) ( ( x ) + ISPAS_MINUS_SYSPHY )
#define ADDR_ISPAS2SYSPHY( x ) ( (x)-ISPAS_MINUS_SYSPHY )


#endif /* __UTIL_ADDR_CALC_H__ */
