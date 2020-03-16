#ifndef __PCIEPSPAHB2PHYSWMAN_H__
#define __PCIEPSPAHB2PHYSWMAN_H__
/*
===========================================================================
*/
/**
  @file PciePspAhb2PhySwman.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r64.0]

  This file contains HWIO register definitions for the following modules:
    PSP0_A2P_AHB2PHY_SWMAN

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 

  Attribute definitions for the HWIO_*_ATTR macros are as follows:
    0x0: Command register
    0x1: Read-Only
    0x2: Write-Only
    0x3: Read/Write
*/
/*
  ===========================================================================

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  Qualcomm Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies Incorporated.

  ===========================================================================

  $Header: $
  $DateTime: $
  $Author: $

  ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: PSP0_A2P_AHB2PHY_SWMAN
 *--------------------------------------------------------------------------*/

#define PSP0_A2P_AHB2PHY_SWMAN_REG_BASE                                               (PSP0_A2P_AHB2PHY_SWMAN_BASE      + 0x00000000)
#define PSP0_A2P_AHB2PHY_SWMAN_REG_BASE_OFFS                                          0x00000000

#define HWIO_PSP_A2P_HW_VERSION_ADDR(x)                                              ((x) + 0x00000000)
#define HWIO_PSP_A2P_HW_VERSION_OFFS                                                 (0x00000000)
#define HWIO_PSP_A2P_HW_VERSION_RMSK                                                   0xffffff
#define HWIO_PSP_A2P_HW_VERSION_ATTR                                                        0x1
#define HWIO_PSP_A2P_HW_VERSION_IN(x)      \
        in_dword_masked(HWIO_PSP_A2P_HW_VERSION_ADDR(x), HWIO_PSP_A2P_HW_VERSION_RMSK)
#define HWIO_PSP_A2P_HW_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_PSP_A2P_HW_VERSION_ADDR(x), m)
#define HWIO_PSP_A2P_HW_VERSION_MAJOR_BMSK                                             0xff0000
#define HWIO_PSP_A2P_HW_VERSION_MAJOR_SHFT                                                 0x10
#define HWIO_PSP_A2P_HW_VERSION_MINOR_BMSK                                               0xff00
#define HWIO_PSP_A2P_HW_VERSION_MINOR_SHFT                                                  0x8
#define HWIO_PSP_A2P_HW_VERSION_STEP_BMSK                                                  0xff
#define HWIO_PSP_A2P_HW_VERSION_STEP_SHFT                                                   0x0

#define HWIO_PSP_A2P_HW_INFO_ADDR(x)                                                 ((x) + 0x00000004)
#define HWIO_PSP_A2P_HW_INFO_OFFS                                                    (0x00000004)
#define HWIO_PSP_A2P_HW_INFO_RMSK                                                    0xffffffff
#define HWIO_PSP_A2P_HW_INFO_ATTR                                                           0x1
#define HWIO_PSP_A2P_HW_INFO_IN(x)      \
        in_dword_masked(HWIO_PSP_A2P_HW_INFO_ADDR(x), HWIO_PSP_A2P_HW_INFO_RMSK)
#define HWIO_PSP_A2P_HW_INFO_INM(x, m)      \
        in_dword_masked(HWIO_PSP_A2P_HW_INFO_ADDR(x), m)
#define HWIO_PSP_A2P_HW_INFO_HW_MAJOR_BMSK                                           0xff000000
#define HWIO_PSP_A2P_HW_INFO_HW_MAJOR_SHFT                                                 0x18
#define HWIO_PSP_A2P_HW_INFO_HW_BRANCH_BMSK                                            0xff0000
#define HWIO_PSP_A2P_HW_INFO_HW_BRANCH_SHFT                                                0x10
#define HWIO_PSP_A2P_HW_INFO_HW_MINOR_BMSK                                               0xff00
#define HWIO_PSP_A2P_HW_INFO_HW_MINOR_SHFT                                                  0x8
#define HWIO_PSP_A2P_HW_INFO_HW_ECO_BMSK                                                   0xff
#define HWIO_PSP_A2P_HW_INFO_HW_ECO_SHFT                                                    0x0

#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR(x)                          ((x) + 0x00000008)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_OFFS                             (0x00000008)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_RMSK                             0xffffffff
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ATTR                                    0x3
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_IN(x)      \
        in_dword_masked(HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR(x), HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_RMSK)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_INM(x, m)      \
        in_dword_masked(HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR(x), m)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_OUT(x, v)      \
        out_dword(HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR(x),v)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_ADDR(x),m,v,HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_IN(x))
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_BROADCAST_EN_LOWER_BMSK          0xffffffff
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_LOWER_BROADCAST_EN_LOWER_SHFT                 0x0

#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR(x)                          ((x) + 0x0000000c)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_OFFS                             (0x0000000c)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_RMSK                             0x3fffffff
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ATTR                                    0x3
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_IN(x)      \
        in_dword_masked(HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR(x), HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_RMSK)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_INM(x, m)      \
        in_dword_masked(HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR(x), m)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_OUT(x, v)      \
        out_dword(HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR(x),v)
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_ADDR(x),m,v,HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_IN(x))
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_BROADCAST_EN_UPPER_BMSK          0x3fffffff
#define HWIO_PSP_A2P_AHB2PHY_BROADCAST_EN_CFG_UPPER_BROADCAST_EN_UPPER_SHFT                 0x0

#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_ADDR(x)                                         ((x) + 0x00000010)
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_OFFS                                            (0x00000010)
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_RMSK                                                  0x33
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_ATTR                                                   0x3
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_IN(x)      \
        in_dword_masked(HWIO_PSP_A2P_AHB2PHY_TOP_CFG_ADDR(x), HWIO_PSP_A2P_AHB2PHY_TOP_CFG_RMSK)
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_INM(x, m)      \
        in_dword_masked(HWIO_PSP_A2P_AHB2PHY_TOP_CFG_ADDR(x), m)
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_OUT(x, v)      \
        out_dword(HWIO_PSP_A2P_AHB2PHY_TOP_CFG_ADDR(x),v)
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_A2P_AHB2PHY_TOP_CFG_ADDR(x),m,v,HWIO_PSP_A2P_AHB2PHY_TOP_CFG_IN(x))
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_BMSK                                0x30
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_SHFT                                 0x4
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_NO_WAIT_STATES_FVAL                  0x0
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_ONE_WAIT_STATE_FVAL                  0x1
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_TWO_WAIT_STATES_FVAL                 0x2
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_WRITE_WAIT_STATES_THREE_WAIT_STATES_FVAL               0x3
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_BMSK                                  0x3
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_SHFT                                  0x0
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_NO_WAIT_STATES_FVAL                   0x0
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_ONE_WAIT_STATE_FVAL                   0x1
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_TWO_WAIT_STATES_FVAL                  0x2
#define HWIO_PSP_A2P_AHB2PHY_TOP_CFG_READ_WAIT_STATES_THREE_WAIT_STATES_FVAL                0x3

#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR(x)                                   ((x) + 0x00000014)
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_OFFS                                      (0x00000014)
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_RMSK                                             0x3
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_ATTR                                             0x3
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_IN(x)      \
        in_dword_masked(HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR(x), HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_RMSK)
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_INM(x, m)      \
        in_dword_masked(HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR(x), m)
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_OUT(x, v)      \
        out_dword(HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR(x),v)
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_ADDR(x),m,v,HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_IN(x))
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_BMSK                               0x3
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SHFT                               0x0
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_NONE_OUTPUT_ZERO_FVAL              0x0
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SELECT_DEBUG_OUTPUT_ONE_FVAL        0x1
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SELECT_DEBUG_OUTPUT_TWO_FVAL        0x2
#define HWIO_PSP_A2P_AHB2PHY_DEBUG_BUS_CFG_DEBUG_BUS_SEL_SELECT_DEBUG_OUTPUT_THREE_FVAL        0x3


#endif /* __PCIEPSPAHB2PHYSWMAN_H__ */
