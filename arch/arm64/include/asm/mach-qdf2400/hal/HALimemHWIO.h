#ifndef __HWIO_IMEM_H__
#define __HWIO_IMEM_H__
/*
===========================================================================
*/
/**
  @file hwio_imem.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r46.0]

  This file contains HWIO register definitions for the following modules:
    MSG_IMEM_IMEM_IMEM_CSRS
    RAM_0_IMEM_IMEM_IMEM_CSRS
    RAM_1_IMEM_IMEM_IMEM_CSRS
    RAM_2_IMEM_IMEM_IMEM_CSRS
    RAM_3_IMEM_IMEM_IMEM_CSRS
    RAM_4_IMEM_IMEM_IMEM_CSRS
    RAM_5_IMEM_IMEM_IMEM_CSRS
    SYS_IMEM_IMEM_IMEM_CSRS

  'Include' filters applied: 
  'Exclude' filters applied: RESERVED DUMMY 
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
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of Qualcomm Technologies, Inc.

  ===========================================================================

  $Header$
  $DateTime$
  $Author$

  ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: MSG_IMEM_IMEM_IMEM_CSRS
 *--------------------------------------------------------------------------*/

#define MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE                               (MSG_IMEM_BASE      + 0x00000000)

#define HWIO_MSG_IMEM_HW_ID_ADDR                                       (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000000)
#define HWIO_MSG_IMEM_HW_ID_RMSK                                       0xffffffff
#define HWIO_MSG_IMEM_HW_ID_IN          \
        in_dword_masked(HWIO_MSG_IMEM_HW_ID_ADDR, HWIO_MSG_IMEM_HW_ID_RMSK)
#define HWIO_MSG_IMEM_HW_ID_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_HW_ID_ADDR, m)
#define HWIO_MSG_IMEM_HW_ID_MAJOR_BMSK                                 0xff000000
#define HWIO_MSG_IMEM_HW_ID_MAJOR_SHFT                                       0x18
#define HWIO_MSG_IMEM_HW_ID_MINOR_BMSK                                   0xff0000
#define HWIO_MSG_IMEM_HW_ID_MINOR_SHFT                                       0x10
#define HWIO_MSG_IMEM_HW_ID_CONFIG_BMSK                                    0xff00
#define HWIO_MSG_IMEM_HW_ID_CONFIG_SHFT                                       0x8
#define HWIO_MSG_IMEM_HW_ID_INSTANCE_BMSK                                    0xff
#define HWIO_MSG_IMEM_HW_ID_INSTANCE_SHFT                                     0x0

#define HWIO_MSG_IMEM_HW_VERSION_ADDR                                  (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000004)
#define HWIO_MSG_IMEM_HW_VERSION_RMSK                                  0xffffffff
#define HWIO_MSG_IMEM_HW_VERSION_IN          \
        in_dword_masked(HWIO_MSG_IMEM_HW_VERSION_ADDR, HWIO_MSG_IMEM_HW_VERSION_RMSK)
#define HWIO_MSG_IMEM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_HW_VERSION_ADDR, m)
#define HWIO_MSG_IMEM_HW_VERSION_MAJOR_BMSK                            0xff000000
#define HWIO_MSG_IMEM_HW_VERSION_MAJOR_SHFT                                  0x18
#define HWIO_MSG_IMEM_HW_VERSION_MINOR_BMSK                              0xff0000
#define HWIO_MSG_IMEM_HW_VERSION_MINOR_SHFT                                  0x10
#define HWIO_MSG_IMEM_HW_VERSION_STEP_BMSK                                 0xffff
#define HWIO_MSG_IMEM_HW_VERSION_STEP_SHFT                                    0x0

#define HWIO_MSG_IMEM_ERR_STATUS_ADDR                                  (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000008)
#define HWIO_MSG_IMEM_ERR_STATUS_RMSK                                       0x3ff
#define HWIO_MSG_IMEM_ERR_STATUS_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_STATUS_ADDR, HWIO_MSG_IMEM_ERR_STATUS_RMSK)
#define HWIO_MSG_IMEM_ERR_STATUS_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_STATUS_ADDR, m)
#define HWIO_MSG_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_BMSK                   0x200
#define HWIO_MSG_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_SHFT                     0x9
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_POISON_SCRUB_BMSK                      0x100
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_POISON_SCRUB_SHFT                        0x8
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_UE_SCRUB_BMSK                           0x80
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_UE_SCRUB_SHFT                            0x7
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_CE_SCRUB_BMSK                           0x40
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_CE_SCRUB_SHFT                            0x6
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_POISON_RMW_BMSK                         0x20
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_POISON_RMW_SHFT                          0x5
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_UE_RMW_BMSK                             0x10
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_UE_RMW_SHFT                              0x4
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_CE_RMW_BMSK                              0x8
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_CE_RMW_SHFT                              0x3
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_BMSK                       0x4
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_SHFT                       0x2
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_UE_QSB_RD_BMSK                           0x2
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_UE_QSB_RD_SHFT                           0x1
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_CE_QSB_RD_BMSK                           0x1
#define HWIO_MSG_IMEM_ERR_STATUS_ECC_CE_QSB_RD_SHFT                           0x0

#define HWIO_MSG_IMEM_ERR_CLR_ADDR                                     (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000000c)
#define HWIO_MSG_IMEM_ERR_CLR_RMSK                                          0x3ff
#define HWIO_MSG_IMEM_ERR_CLR_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_ERR_CLR_ADDR,v)
#define HWIO_MSG_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_MSG_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_UE_RMW_BMSK                            0x10
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_UE_RMW_SHFT                             0x4
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_CE_RMW_BMSK                             0x8
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_CE_RMW_SHFT                             0x3
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_MSG_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_MSG_IMEM_ERR_CTRL_ADDR                                    (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000010)
#define HWIO_MSG_IMEM_ERR_CTRL_RMSK                                         0x3ff
#define HWIO_MSG_IMEM_ERR_CTRL_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CTRL_ADDR, HWIO_MSG_IMEM_ERR_CTRL_RMSK)
#define HWIO_MSG_IMEM_ERR_CTRL_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CTRL_ADDR, m)
#define HWIO_MSG_IMEM_ERR_CTRL_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_ERR_CTRL_ADDR,v)
#define HWIO_MSG_IMEM_ERR_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_ERR_CTRL_ADDR,m,v,HWIO_MSG_IMEM_ERR_CTRL_IN)
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_BMSK                0x200
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_SHFT                  0x9
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_BMSK                   0x100
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_SHFT                     0x8
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_BMSK                        0x80
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_SHFT                         0x7
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_BMSK                        0x40
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_SHFT                         0x6
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_BMSK                      0x20
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_SHFT                       0x5
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_BMSK                          0x10
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_SHFT                           0x4
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_BMSK                           0x8
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_SHFT                           0x3
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_BMSK                    0x4
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_SHFT                    0x2
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_BMSK                        0x2
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_SHFT                        0x1
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_BMSK                        0x1
#define HWIO_MSG_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_SHFT                        0x0

#define HWIO_MSG_IMEM_INT0_CTRL_ADDR                                   (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000014)
#define HWIO_MSG_IMEM_INT0_CTRL_RMSK                                        0x3ff
#define HWIO_MSG_IMEM_INT0_CTRL_IN          \
        in_dword_masked(HWIO_MSG_IMEM_INT0_CTRL_ADDR, HWIO_MSG_IMEM_INT0_CTRL_RMSK)
#define HWIO_MSG_IMEM_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_INT0_CTRL_ADDR, m)
#define HWIO_MSG_IMEM_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_INT0_CTRL_ADDR,v)
#define HWIO_MSG_IMEM_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_INT0_CTRL_ADDR,m,v,HWIO_MSG_IMEM_INT0_CTRL_IN)
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_BMSK                         0x10
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_SHFT                          0x4
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_BMSK                          0x8
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_SHFT                          0x3
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_MSG_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_MSG_IMEM_INT1_CTRL_ADDR                                   (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000018)
#define HWIO_MSG_IMEM_INT1_CTRL_RMSK                                        0x3ff
#define HWIO_MSG_IMEM_INT1_CTRL_IN          \
        in_dword_masked(HWIO_MSG_IMEM_INT1_CTRL_ADDR, HWIO_MSG_IMEM_INT1_CTRL_RMSK)
#define HWIO_MSG_IMEM_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_INT1_CTRL_ADDR, m)
#define HWIO_MSG_IMEM_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_INT1_CTRL_ADDR,v)
#define HWIO_MSG_IMEM_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_INT1_CTRL_ADDR,m,v,HWIO_MSG_IMEM_INT1_CTRL_IN)
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_BMSK                         0x10
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_SHFT                          0x4
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_BMSK                          0x8
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_SHFT                          0x3
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_MSG_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_MSG_IMEM_ERR_INJ_ADDR                                     (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000001c)
#define HWIO_MSG_IMEM_ERR_INJ_RMSK                                          0x3ff
#define HWIO_MSG_IMEM_ERR_INJ_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_ERR_INJ_ADDR,v)
#define HWIO_MSG_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_MSG_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_UE_RMW_BMSK                            0x10
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_UE_RMW_SHFT                             0x4
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_CE_RMW_BMSK                             0x8
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_CE_RMW_SHFT                             0x3
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_MSG_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_MSG_IMEM_ERR_CAP_CNTL_ADDR                                (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000020)
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_RMSK                                      0x1f
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_CNTL_ADDR, HWIO_MSG_IMEM_ERR_CAP_CNTL_RMSK)
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_CNTL_ADDR, m)
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_ERR_CAP_CNTL_ADDR,v)
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_ERR_CAP_CNTL_ADDR,m,v,HWIO_MSG_IMEM_ERR_CAP_CNTL_IN)
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_BMSK                       0x10
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_SHFT                        0x4
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_BMSK                        0x8
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_SHFT                        0x3
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_BMSK                    0x4
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_SHFT                    0x2
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_BMSK                    0x2
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_SHFT                    0x1
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_BMSK                          0x1
#define HWIO_MSG_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_SHFT                          0x0

#define HWIO_MSG_IMEM_ERR_CAP_0_ADDR                                   (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000024)
#define HWIO_MSG_IMEM_ERR_CAP_0_RMSK                                   0xffffffff
#define HWIO_MSG_IMEM_ERR_CAP_0_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_0_ADDR, HWIO_MSG_IMEM_ERR_CAP_0_RMSK)
#define HWIO_MSG_IMEM_ERR_CAP_0_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_0_ADDR, m)
#define HWIO_MSG_IMEM_ERR_CAP_0_ERR_ADDR_LO_BMSK                       0xffffffff
#define HWIO_MSG_IMEM_ERR_CAP_0_ERR_ADDR_LO_SHFT                              0x0

#define HWIO_MSG_IMEM_ERR_CAP_1_ADDR                                   (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000028)
#define HWIO_MSG_IMEM_ERR_CAP_1_RMSK                                   0xffff0fff
#define HWIO_MSG_IMEM_ERR_CAP_1_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_1_ADDR, HWIO_MSG_IMEM_ERR_CAP_1_RMSK)
#define HWIO_MSG_IMEM_ERR_CAP_1_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_1_ADDR, m)
#define HWIO_MSG_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_BMSK                0xff000000
#define HWIO_MSG_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_SHFT                      0x18
#define HWIO_MSG_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_BMSK                   0xff0000
#define HWIO_MSG_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_SHFT                       0x10
#define HWIO_MSG_IMEM_ERR_CAP_1_ERR_ADDR_HI_BMSK                            0xfff
#define HWIO_MSG_IMEM_ERR_CAP_1_ERR_ADDR_HI_SHFT                              0x0

#define HWIO_MSG_IMEM_ERR_CAP_2_ADDR                                   (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000002c)
#define HWIO_MSG_IMEM_ERR_CAP_2_RMSK                                   0x1fffffff
#define HWIO_MSG_IMEM_ERR_CAP_2_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_2_ADDR, HWIO_MSG_IMEM_ERR_CAP_2_RMSK)
#define HWIO_MSG_IMEM_ERR_CAP_2_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_2_ADDR, m)
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_ABURST_BMSK                        0x10000000
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_ABURST_SHFT                              0x1c
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_AWRITE_BMSK                         0x8000000
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_AWRITE_SHFT                              0x1b
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_ALEN_BMSK                           0x7c00000
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_ALEN_SHFT                                0x16
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_BMSK                      0x200000
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_SHFT                          0x15
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_TID_BMSK                             0x1f0000
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_TID_SHFT                                 0x10
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_BID_BMSK                               0xe000
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_BID_SHFT                                  0xd
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_PID_BMSK                               0x1f00
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_PID_SHFT                                  0x8
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_MID_BMSK                                 0xff
#define HWIO_MSG_IMEM_ERR_CAP_2_ERR_MID_SHFT                                  0x0

#define HWIO_MSG_IMEM_ERR_CAP_3_ADDR                                   (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000030)
#define HWIO_MSG_IMEM_ERR_CAP_3_RMSK                                      0x3ffff
#define HWIO_MSG_IMEM_ERR_CAP_3_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_3_ADDR, HWIO_MSG_IMEM_ERR_CAP_3_RMSK)
#define HWIO_MSG_IMEM_ERR_CAP_3_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_3_ADDR, m)
#define HWIO_MSG_IMEM_ERR_CAP_3_ERR_VMID_BMSK                             0x3fc00
#define HWIO_MSG_IMEM_ERR_CAP_3_ERR_VMID_SHFT                                 0xa
#define HWIO_MSG_IMEM_ERR_CAP_3_ERR_MSA_BMSK                                0x200
#define HWIO_MSG_IMEM_ERR_CAP_3_ERR_MSA_SHFT                                  0x9
#define HWIO_MSG_IMEM_ERR_CAP_3_ERR_NSPROT_BMSK                             0x100
#define HWIO_MSG_IMEM_ERR_CAP_3_ERR_NSPROT_SHFT                               0x8
#define HWIO_MSG_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_BMSK                          0xff
#define HWIO_MSG_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_SHFT                           0x0

#define HWIO_MSG_IMEM_ERR_CAP_4_ADDR                                   (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000034)
#define HWIO_MSG_IMEM_ERR_CAP_4_RMSK                                    0x1ffffff
#define HWIO_MSG_IMEM_ERR_CAP_4_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_4_ADDR, HWIO_MSG_IMEM_ERR_CAP_4_RMSK)
#define HWIO_MSG_IMEM_ERR_CAP_4_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_CAP_4_ADDR, m)
#define HWIO_MSG_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_BMSK                      0x1000000
#define HWIO_MSG_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_SHFT                           0x18
#define HWIO_MSG_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_BMSK                    0xff0000
#define HWIO_MSG_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_SHFT                        0x10
#define HWIO_MSG_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_BMSK                      0xff00
#define HWIO_MSG_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_SHFT                         0x8
#define HWIO_MSG_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_BMSK                        0xff
#define HWIO_MSG_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_SHFT                         0x0

#define HWIO_MSG_IMEM_ERR_COUNT_ADDR                                   (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000074)
#define HWIO_MSG_IMEM_ERR_COUNT_RMSK                                   0xffffffff
#define HWIO_MSG_IMEM_ERR_COUNT_IN          \
        in_dword_masked(HWIO_MSG_IMEM_ERR_COUNT_ADDR, HWIO_MSG_IMEM_ERR_COUNT_RMSK)
#define HWIO_MSG_IMEM_ERR_COUNT_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_ERR_COUNT_ADDR, m)
#define HWIO_MSG_IMEM_ERR_COUNT_ERR_UE_COUNT_BMSK                      0xffff0000
#define HWIO_MSG_IMEM_ERR_COUNT_ERR_UE_COUNT_SHFT                            0x10
#define HWIO_MSG_IMEM_ERR_COUNT_ERR_CE_COUNT_BMSK                          0xffff
#define HWIO_MSG_IMEM_ERR_COUNT_ERR_CE_COUNT_SHFT                             0x0

#define HWIO_MSG_IMEM_SCRUB_STATUS_ADDR                                (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000038)
#define HWIO_MSG_IMEM_SCRUB_STATUS_RMSK                                       0x7
#define HWIO_MSG_IMEM_SCRUB_STATUS_IN          \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_STATUS_ADDR, HWIO_MSG_IMEM_SCRUB_STATUS_RMSK)
#define HWIO_MSG_IMEM_SCRUB_STATUS_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_STATUS_ADDR, m)
#define HWIO_MSG_IMEM_SCRUB_STATUS_SCRUB_INPROG_BMSK                          0x4
#define HWIO_MSG_IMEM_SCRUB_STATUS_SCRUB_INPROG_SHFT                          0x2
#define HWIO_MSG_IMEM_SCRUB_STATUS_WIPE_INPROG_BMSK                           0x2
#define HWIO_MSG_IMEM_SCRUB_STATUS_WIPE_INPROG_SHFT                           0x1
#define HWIO_MSG_IMEM_SCRUB_STATUS_ADDR_MAX_BMSK                              0x1
#define HWIO_MSG_IMEM_SCRUB_STATUS_ADDR_MAX_SHFT                              0x0

#define HWIO_MSG_IMEM_SCRUB_CTRL_ADDR                                  (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000003c)
#define HWIO_MSG_IMEM_SCRUB_CTRL_RMSK                                  0xfff8ffff
#define HWIO_MSG_IMEM_SCRUB_CTRL_IN          \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_CTRL_ADDR, HWIO_MSG_IMEM_SCRUB_CTRL_RMSK)
#define HWIO_MSG_IMEM_SCRUB_CTRL_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_CTRL_ADDR, m)
#define HWIO_MSG_IMEM_SCRUB_CTRL_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_SCRUB_CTRL_ADDR,v)
#define HWIO_MSG_IMEM_SCRUB_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_SCRUB_CTRL_ADDR,m,v,HWIO_MSG_IMEM_SCRUB_CTRL_IN)
#define HWIO_MSG_IMEM_SCRUB_CTRL_SCRUB_EN_BMSK                         0x80000000
#define HWIO_MSG_IMEM_SCRUB_CTRL_SCRUB_EN_SHFT                               0x1f
#define HWIO_MSG_IMEM_SCRUB_CTRL_LOAD_ADDR_BMSK                        0x40000000
#define HWIO_MSG_IMEM_SCRUB_CTRL_LOAD_ADDR_SHFT                              0x1e
#define HWIO_MSG_IMEM_SCRUB_CTRL_WRITE_DATA_BMSK                       0x20000000
#define HWIO_MSG_IMEM_SCRUB_CTRL_WRITE_DATA_SHFT                             0x1d
#define HWIO_MSG_IMEM_SCRUB_CTRL_WIPE_DATA_BMSK                        0x10000000
#define HWIO_MSG_IMEM_SCRUB_CTRL_WIPE_DATA_SHFT                              0x1c
#define HWIO_MSG_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_BMSK                    0x8000000
#define HWIO_MSG_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_SHFT                         0x1b
#define HWIO_MSG_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_BMSK                      0x4000000
#define HWIO_MSG_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_SHFT                           0x1a
#define HWIO_MSG_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_BMSK                    0x2000000
#define HWIO_MSG_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_SHFT                         0x19
#define HWIO_MSG_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_BMSK                     0x1000000
#define HWIO_MSG_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_SHFT                          0x18
#define HWIO_MSG_IMEM_SCRUB_CTRL_NUM_ADDR_BMSK                           0xf80000
#define HWIO_MSG_IMEM_SCRUB_CTRL_NUM_ADDR_SHFT                               0x13
#define HWIO_MSG_IMEM_SCRUB_CTRL_SCRUB_TIMER_BMSK                          0xffff
#define HWIO_MSG_IMEM_SCRUB_CTRL_SCRUB_TIMER_SHFT                             0x0

#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_ADDR                             (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000040)
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_RMSK                             0xffffffff
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_IN          \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_ADDR, HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_RMSK)
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_ADDR, m)
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_ADDR                             (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000044)
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_RMSK                                 0xffff
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_IN          \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_ADDR, HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_RMSK)
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_ADDR, m)
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_MSG_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_ADDR                             (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000048)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_RMSK                             0xffffffff
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_IN          \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_ADDR, HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_RMSK)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_ADDR, m)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_ADDR,v)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_ADDR,m,v,HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_IN)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_ADDR                             (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000004c)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_RMSK                                 0xffff
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_IN          \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_ADDR, HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_RMSK)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_ADDR, m)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_ADDR,v)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_ADDR,m,v,HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_IN)
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_MSG_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_MSG_IMEM_SCRUB_DATA_WR_0_ADDR                             (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000050)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_0_RMSK                             0xffffffff
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_0_IN          \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_DATA_WR_0_ADDR, HWIO_MSG_IMEM_SCRUB_DATA_WR_0_RMSK)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_0_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_DATA_WR_0_ADDR, m)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_0_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_SCRUB_DATA_WR_0_ADDR,v)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_SCRUB_DATA_WR_0_ADDR,m,v,HWIO_MSG_IMEM_SCRUB_DATA_WR_0_IN)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_BMSK              0xffffffff
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_SHFT                     0x0

#define HWIO_MSG_IMEM_SCRUB_DATA_WR_1_ADDR                             (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000054)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_1_RMSK                             0xffffffff
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_1_IN          \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_DATA_WR_1_ADDR, HWIO_MSG_IMEM_SCRUB_DATA_WR_1_RMSK)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_1_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_SCRUB_DATA_WR_1_ADDR, m)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_1_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_SCRUB_DATA_WR_1_ADDR,v)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_SCRUB_DATA_WR_1_ADDR,m,v,HWIO_MSG_IMEM_SCRUB_DATA_WR_1_IN)
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_BMSK             0xffffffff
#define HWIO_MSG_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_SHFT                    0x0

#define HWIO_MSG_IMEM_CONFIG_ADDR                                      (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000058)
#define HWIO_MSG_IMEM_CONFIG_RMSK                                            0x1f
#define HWIO_MSG_IMEM_CONFIG_IN          \
        in_dword_masked(HWIO_MSG_IMEM_CONFIG_ADDR, HWIO_MSG_IMEM_CONFIG_RMSK)
#define HWIO_MSG_IMEM_CONFIG_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_CONFIG_ADDR, m)
#define HWIO_MSG_IMEM_CONFIG_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_CONFIG_ADDR,v)
#define HWIO_MSG_IMEM_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_CONFIG_ADDR,m,v,HWIO_MSG_IMEM_CONFIG_IN)
#define HWIO_MSG_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_BMSK                        0x10
#define HWIO_MSG_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_SHFT                         0x4
#define HWIO_MSG_IMEM_CONFIG_ECC_ENABLE_BMSK                                  0x8
#define HWIO_MSG_IMEM_CONFIG_ECC_ENABLE_SHFT                                  0x3
#define HWIO_MSG_IMEM_CONFIG_ECC_ENABLE_WR_BMSK                               0x4
#define HWIO_MSG_IMEM_CONFIG_ECC_ENABLE_WR_SHFT                               0x2
#define HWIO_MSG_IMEM_CONFIG_ECC_ENABLE_RD_BMSK                               0x2
#define HWIO_MSG_IMEM_CONFIG_ECC_ENABLE_RD_SHFT                               0x1
#define HWIO_MSG_IMEM_CONFIG_ECC_RD_RMW_EN_BMSK                               0x1
#define HWIO_MSG_IMEM_CONFIG_ECC_RD_RMW_EN_SHFT                               0x0

#define HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_ADDR                        (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000005c)
#define HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_RMSK                        0xffffffff
#define HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_IN          \
        in_dword_masked(HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_RMSK)
#define HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, m)
#define HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,v)
#define HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,m,v,HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_IN)
#define HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_BMSK              0xffffffff
#define HWIO_MSG_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_SHFT                     0x0

#define HWIO_MSG_IMEM_CLK_ON_CFG_ADDR                                  (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000064)
#define HWIO_MSG_IMEM_CLK_ON_CFG_RMSK                                       0xfff
#define HWIO_MSG_IMEM_CLK_ON_CFG_IN          \
        in_dword_masked(HWIO_MSG_IMEM_CLK_ON_CFG_ADDR, HWIO_MSG_IMEM_CLK_ON_CFG_RMSK)
#define HWIO_MSG_IMEM_CLK_ON_CFG_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_CLK_ON_CFG_ADDR, m)
#define HWIO_MSG_IMEM_CLK_ON_CFG_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_CLK_ON_CFG_ADDR,v)
#define HWIO_MSG_IMEM_CLK_ON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_CLK_ON_CFG_ADDR,m,v,HWIO_MSG_IMEM_CLK_ON_CFG_IN)
#define HWIO_MSG_IMEM_CLK_ON_CFG_CLK_ON_TIME_BMSK                           0xffc
#define HWIO_MSG_IMEM_CLK_ON_CFG_CLK_ON_TIME_SHFT                             0x2
#define HWIO_MSG_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_BMSK                           0x2
#define HWIO_MSG_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_SHFT                           0x1
#define HWIO_MSG_IMEM_CLK_ON_CFG_CLK_ON_EN_BMSK                               0x1
#define HWIO_MSG_IMEM_CLK_ON_CFG_CLK_ON_EN_SHFT                               0x0

#define HWIO_MSG_IMEM_PSBCGC_TIMERS_ADDR                               (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000006c)
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_RMSK                                     0xff
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_IN          \
        in_dword_masked(HWIO_MSG_IMEM_PSBCGC_TIMERS_ADDR, HWIO_MSG_IMEM_PSBCGC_TIMERS_RMSK)
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_PSBCGC_TIMERS_ADDR, m)
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_PSBCGC_TIMERS_ADDR,v)
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_PSBCGC_TIMERS_ADDR,m,v,HWIO_MSG_IMEM_PSBCGC_TIMERS_IN)
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_BMSK                      0xf0
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_SHFT                       0x4
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_BMSK                     0xf
#define HWIO_MSG_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_SHFT                     0x0

#define HWIO_MSG_IMEM_PSBCGC_CONTROL_ADDR                              (MSG_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000070)
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_RMSK                              0x3fffffff
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_IN          \
        in_dword_masked(HWIO_MSG_IMEM_PSBCGC_CONTROL_ADDR, HWIO_MSG_IMEM_PSBCGC_CONTROL_RMSK)
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_MSG_IMEM_PSBCGC_CONTROL_ADDR, m)
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_OUT(v)      \
        out_dword(HWIO_MSG_IMEM_PSBCGC_CONTROL_ADDR,v)
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_MSG_IMEM_PSBCGC_CONTROL_ADDR,m,v,HWIO_MSG_IMEM_PSBCGC_CONTROL_IN)
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_HALT_CLOCK_BMSK                   0x3ff00000
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_HALT_CLOCK_SHFT                         0x14
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_CORE_ON_BMSK                         0xffc00
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_CORE_ON_SHFT                             0xa
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_PERIF_ON_BMSK                          0x3ff
#define HWIO_MSG_IMEM_PSBCGC_CONTROL_PERIF_ON_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: RAM_0_IMEM_IMEM_IMEM_CSRS
 *--------------------------------------------------------------------------*/

#define RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE                               (IMC_BASE      + 0x00500000)

#define HWIO_RAM_0_IMEM_HW_ID_ADDR                                       (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000000)
#define HWIO_RAM_0_IMEM_HW_ID_RMSK                                       0xffffffff
#define HWIO_RAM_0_IMEM_HW_ID_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_HW_ID_ADDR, HWIO_RAM_0_IMEM_HW_ID_RMSK)
#define HWIO_RAM_0_IMEM_HW_ID_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_HW_ID_ADDR, m)
#define HWIO_RAM_0_IMEM_HW_ID_MAJOR_BMSK                                 0xff000000
#define HWIO_RAM_0_IMEM_HW_ID_MAJOR_SHFT                                       0x18
#define HWIO_RAM_0_IMEM_HW_ID_MINOR_BMSK                                   0xff0000
#define HWIO_RAM_0_IMEM_HW_ID_MINOR_SHFT                                       0x10
#define HWIO_RAM_0_IMEM_HW_ID_CONFIG_BMSK                                    0xff00
#define HWIO_RAM_0_IMEM_HW_ID_CONFIG_SHFT                                       0x8
#define HWIO_RAM_0_IMEM_HW_ID_INSTANCE_BMSK                                    0xff
#define HWIO_RAM_0_IMEM_HW_ID_INSTANCE_SHFT                                     0x0

#define HWIO_RAM_0_IMEM_HW_VERSION_ADDR                                  (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000004)
#define HWIO_RAM_0_IMEM_HW_VERSION_RMSK                                  0xffffffff
#define HWIO_RAM_0_IMEM_HW_VERSION_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_HW_VERSION_ADDR, HWIO_RAM_0_IMEM_HW_VERSION_RMSK)
#define HWIO_RAM_0_IMEM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_HW_VERSION_ADDR, m)
#define HWIO_RAM_0_IMEM_HW_VERSION_MAJOR_BMSK                            0xff000000
#define HWIO_RAM_0_IMEM_HW_VERSION_MAJOR_SHFT                                  0x18
#define HWIO_RAM_0_IMEM_HW_VERSION_MINOR_BMSK                              0xff0000
#define HWIO_RAM_0_IMEM_HW_VERSION_MINOR_SHFT                                  0x10
#define HWIO_RAM_0_IMEM_HW_VERSION_STEP_BMSK                                 0xffff
#define HWIO_RAM_0_IMEM_HW_VERSION_STEP_SHFT                                    0x0

#define HWIO_RAM_0_IMEM_ERR_STATUS_ADDR                                  (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000008)
#define HWIO_RAM_0_IMEM_ERR_STATUS_RMSK                                       0x3ff
#define HWIO_RAM_0_IMEM_ERR_STATUS_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_STATUS_ADDR, HWIO_RAM_0_IMEM_ERR_STATUS_RMSK)
#define HWIO_RAM_0_IMEM_ERR_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_STATUS_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_BMSK                   0x200
#define HWIO_RAM_0_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_SHFT                     0x9
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_POISON_SCRUB_BMSK                      0x100
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_POISON_SCRUB_SHFT                        0x8
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_UE_SCRUB_BMSK                           0x80
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_UE_SCRUB_SHFT                            0x7
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_CE_SCRUB_BMSK                           0x40
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_CE_SCRUB_SHFT                            0x6
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_POISON_RMW_BMSK                         0x20
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_POISON_RMW_SHFT                          0x5
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_UE_RMW_BMSK                             0x10
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_UE_RMW_SHFT                              0x4
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_CE_RMW_BMSK                              0x8
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_CE_RMW_SHFT                              0x3
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_BMSK                       0x4
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_SHFT                       0x2
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_UE_QSB_RD_BMSK                           0x2
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_UE_QSB_RD_SHFT                           0x1
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_CE_QSB_RD_BMSK                           0x1
#define HWIO_RAM_0_IMEM_ERR_STATUS_ECC_CE_QSB_RD_SHFT                           0x0

#define HWIO_RAM_0_IMEM_ERR_CLR_ADDR                                     (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000000c)
#define HWIO_RAM_0_IMEM_ERR_CLR_RMSK                                          0x3ff
#define HWIO_RAM_0_IMEM_ERR_CLR_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_ERR_CLR_ADDR,v)
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_0_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_0_IMEM_ERR_CTRL_ADDR                                    (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000010)
#define HWIO_RAM_0_IMEM_ERR_CTRL_RMSK                                         0x3ff
#define HWIO_RAM_0_IMEM_ERR_CTRL_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CTRL_ADDR, HWIO_RAM_0_IMEM_ERR_CTRL_RMSK)
#define HWIO_RAM_0_IMEM_ERR_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CTRL_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_ERR_CTRL_ADDR,v)
#define HWIO_RAM_0_IMEM_ERR_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_ERR_CTRL_ADDR,m,v,HWIO_RAM_0_IMEM_ERR_CTRL_IN)
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_BMSK                0x200
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_SHFT                  0x9
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_BMSK                   0x100
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_SHFT                     0x8
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_BMSK                        0x80
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_SHFT                         0x7
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_BMSK                        0x40
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_SHFT                         0x6
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_BMSK                      0x20
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_SHFT                       0x5
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_BMSK                          0x10
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_SHFT                           0x4
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_BMSK                           0x8
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_SHFT                           0x3
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_BMSK                    0x4
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_SHFT                    0x2
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_BMSK                        0x2
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_SHFT                        0x1
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_BMSK                        0x1
#define HWIO_RAM_0_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_SHFT                        0x0

#define HWIO_RAM_0_IMEM_INT0_CTRL_ADDR                                   (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000014)
#define HWIO_RAM_0_IMEM_INT0_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_0_IMEM_INT0_CTRL_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_INT0_CTRL_ADDR, HWIO_RAM_0_IMEM_INT0_CTRL_RMSK)
#define HWIO_RAM_0_IMEM_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_INT0_CTRL_ADDR, m)
#define HWIO_RAM_0_IMEM_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_INT0_CTRL_ADDR,v)
#define HWIO_RAM_0_IMEM_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_INT0_CTRL_ADDR,m,v,HWIO_RAM_0_IMEM_INT0_CTRL_IN)
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_0_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_0_IMEM_INT1_CTRL_ADDR                                   (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000018)
#define HWIO_RAM_0_IMEM_INT1_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_0_IMEM_INT1_CTRL_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_INT1_CTRL_ADDR, HWIO_RAM_0_IMEM_INT1_CTRL_RMSK)
#define HWIO_RAM_0_IMEM_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_INT1_CTRL_ADDR, m)
#define HWIO_RAM_0_IMEM_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_INT1_CTRL_ADDR,v)
#define HWIO_RAM_0_IMEM_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_INT1_CTRL_ADDR,m,v,HWIO_RAM_0_IMEM_INT1_CTRL_IN)
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_0_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_0_IMEM_ERR_INJ_ADDR                                     (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000001c)
#define HWIO_RAM_0_IMEM_ERR_INJ_RMSK                                          0x3ff
#define HWIO_RAM_0_IMEM_ERR_INJ_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_ERR_INJ_ADDR,v)
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_0_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_ADDR                                (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000020)
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_RMSK                                      0x1f
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_CNTL_ADDR, HWIO_RAM_0_IMEM_ERR_CAP_CNTL_RMSK)
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_CNTL_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_ERR_CAP_CNTL_ADDR,v)
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_ERR_CAP_CNTL_ADDR,m,v,HWIO_RAM_0_IMEM_ERR_CAP_CNTL_IN)
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_BMSK                       0x10
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_SHFT                        0x4
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_BMSK                        0x8
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_SHFT                        0x3
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_BMSK                    0x4
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_SHFT                    0x2
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_BMSK                    0x2
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_SHFT                    0x1
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_BMSK                          0x1
#define HWIO_RAM_0_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_SHFT                          0x0

#define HWIO_RAM_0_IMEM_ERR_CAP_0_ADDR                                   (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000024)
#define HWIO_RAM_0_IMEM_ERR_CAP_0_RMSK                                   0xffffffff
#define HWIO_RAM_0_IMEM_ERR_CAP_0_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_0_ADDR, HWIO_RAM_0_IMEM_ERR_CAP_0_RMSK)
#define HWIO_RAM_0_IMEM_ERR_CAP_0_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_0_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_CAP_0_ERR_ADDR_LO_BMSK                       0xffffffff
#define HWIO_RAM_0_IMEM_ERR_CAP_0_ERR_ADDR_LO_SHFT                              0x0

#define HWIO_RAM_0_IMEM_ERR_CAP_1_ADDR                                   (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000028)
#define HWIO_RAM_0_IMEM_ERR_CAP_1_RMSK                                   0xffff0fff
#define HWIO_RAM_0_IMEM_ERR_CAP_1_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_1_ADDR, HWIO_RAM_0_IMEM_ERR_CAP_1_RMSK)
#define HWIO_RAM_0_IMEM_ERR_CAP_1_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_1_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_BMSK                0xff000000
#define HWIO_RAM_0_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_SHFT                      0x18
#define HWIO_RAM_0_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_BMSK                   0xff0000
#define HWIO_RAM_0_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_SHFT                       0x10
#define HWIO_RAM_0_IMEM_ERR_CAP_1_ERR_ADDR_HI_BMSK                            0xfff
#define HWIO_RAM_0_IMEM_ERR_CAP_1_ERR_ADDR_HI_SHFT                              0x0

#define HWIO_RAM_0_IMEM_ERR_CAP_2_ADDR                                   (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000002c)
#define HWIO_RAM_0_IMEM_ERR_CAP_2_RMSK                                   0x1fffffff
#define HWIO_RAM_0_IMEM_ERR_CAP_2_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_2_ADDR, HWIO_RAM_0_IMEM_ERR_CAP_2_RMSK)
#define HWIO_RAM_0_IMEM_ERR_CAP_2_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_2_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_ABURST_BMSK                        0x10000000
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_ABURST_SHFT                              0x1c
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_AWRITE_BMSK                         0x8000000
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_AWRITE_SHFT                              0x1b
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_ALEN_BMSK                           0x7c00000
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_ALEN_SHFT                                0x16
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_BMSK                      0x200000
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_SHFT                          0x15
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_TID_BMSK                             0x1f0000
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_TID_SHFT                                 0x10
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_BID_BMSK                               0xe000
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_BID_SHFT                                  0xd
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_PID_BMSK                               0x1f00
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_PID_SHFT                                  0x8
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_MID_BMSK                                 0xff
#define HWIO_RAM_0_IMEM_ERR_CAP_2_ERR_MID_SHFT                                  0x0

#define HWIO_RAM_0_IMEM_ERR_CAP_3_ADDR                                   (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000030)
#define HWIO_RAM_0_IMEM_ERR_CAP_3_RMSK                                      0x3ffff
#define HWIO_RAM_0_IMEM_ERR_CAP_3_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_3_ADDR, HWIO_RAM_0_IMEM_ERR_CAP_3_RMSK)
#define HWIO_RAM_0_IMEM_ERR_CAP_3_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_3_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_CAP_3_ERR_VMID_BMSK                             0x3fc00
#define HWIO_RAM_0_IMEM_ERR_CAP_3_ERR_VMID_SHFT                                 0xa
#define HWIO_RAM_0_IMEM_ERR_CAP_3_ERR_MSA_BMSK                                0x200
#define HWIO_RAM_0_IMEM_ERR_CAP_3_ERR_MSA_SHFT                                  0x9
#define HWIO_RAM_0_IMEM_ERR_CAP_3_ERR_NSPROT_BMSK                             0x100
#define HWIO_RAM_0_IMEM_ERR_CAP_3_ERR_NSPROT_SHFT                               0x8
#define HWIO_RAM_0_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_BMSK                          0xff
#define HWIO_RAM_0_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_SHFT                           0x0

#define HWIO_RAM_0_IMEM_ERR_CAP_4_ADDR                                   (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000034)
#define HWIO_RAM_0_IMEM_ERR_CAP_4_RMSK                                    0x1ffffff
#define HWIO_RAM_0_IMEM_ERR_CAP_4_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_4_ADDR, HWIO_RAM_0_IMEM_ERR_CAP_4_RMSK)
#define HWIO_RAM_0_IMEM_ERR_CAP_4_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_CAP_4_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_BMSK                      0x1000000
#define HWIO_RAM_0_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_SHFT                           0x18
#define HWIO_RAM_0_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_BMSK                    0xff0000
#define HWIO_RAM_0_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_SHFT                        0x10
#define HWIO_RAM_0_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_BMSK                      0xff00
#define HWIO_RAM_0_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_SHFT                         0x8
#define HWIO_RAM_0_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_BMSK                        0xff
#define HWIO_RAM_0_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_SHFT                         0x0

#define HWIO_RAM_0_IMEM_ERR_COUNT_ADDR                                   (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000074)
#define HWIO_RAM_0_IMEM_ERR_COUNT_RMSK                                   0xffffffff
#define HWIO_RAM_0_IMEM_ERR_COUNT_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_COUNT_ADDR, HWIO_RAM_0_IMEM_ERR_COUNT_RMSK)
#define HWIO_RAM_0_IMEM_ERR_COUNT_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_ERR_COUNT_ADDR, m)
#define HWIO_RAM_0_IMEM_ERR_COUNT_ERR_UE_COUNT_BMSK                      0xffff0000
#define HWIO_RAM_0_IMEM_ERR_COUNT_ERR_UE_COUNT_SHFT                            0x10
#define HWIO_RAM_0_IMEM_ERR_COUNT_ERR_CE_COUNT_BMSK                          0xffff
#define HWIO_RAM_0_IMEM_ERR_COUNT_ERR_CE_COUNT_SHFT                             0x0

#define HWIO_RAM_0_IMEM_SCRUB_STATUS_ADDR                                (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000038)
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_RMSK                                       0x7
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_STATUS_ADDR, HWIO_RAM_0_IMEM_SCRUB_STATUS_RMSK)
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_STATUS_ADDR, m)
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_SCRUB_INPROG_BMSK                          0x4
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_SCRUB_INPROG_SHFT                          0x2
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_WIPE_INPROG_BMSK                           0x2
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_WIPE_INPROG_SHFT                           0x1
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_ADDR_MAX_BMSK                              0x1
#define HWIO_RAM_0_IMEM_SCRUB_STATUS_ADDR_MAX_SHFT                              0x0

#define HWIO_RAM_0_IMEM_SCRUB_CTRL_ADDR                                  (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000003c)
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_RMSK                                  0xfff8ffff
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_CTRL_ADDR, HWIO_RAM_0_IMEM_SCRUB_CTRL_RMSK)
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_CTRL_ADDR, m)
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_SCRUB_CTRL_ADDR,v)
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_SCRUB_CTRL_ADDR,m,v,HWIO_RAM_0_IMEM_SCRUB_CTRL_IN)
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_SCRUB_EN_BMSK                         0x80000000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_SCRUB_EN_SHFT                               0x1f
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_LOAD_ADDR_BMSK                        0x40000000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_LOAD_ADDR_SHFT                              0x1e
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_WRITE_DATA_BMSK                       0x20000000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_WRITE_DATA_SHFT                             0x1d
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_WIPE_DATA_BMSK                        0x10000000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_WIPE_DATA_SHFT                              0x1c
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_BMSK                    0x8000000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_SHFT                         0x1b
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_BMSK                      0x4000000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_SHFT                           0x1a
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_BMSK                    0x2000000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_SHFT                         0x19
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_BMSK                     0x1000000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_SHFT                          0x18
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_NUM_ADDR_BMSK                           0xf80000
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_NUM_ADDR_SHFT                               0x13
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_SCRUB_TIMER_BMSK                          0xffff
#define HWIO_RAM_0_IMEM_SCRUB_CTRL_SCRUB_TIMER_SHFT                             0x0

#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_ADDR                             (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000040)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_RMSK                             0xffffffff
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_ADDR, HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_RMSK)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_ADDR, m)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_ADDR                             (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000044)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_RMSK                                 0xffff
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_ADDR, HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_RMSK)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_ADDR, m)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_ADDR                             (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000048)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_ADDR, HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_RMSK)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_ADDR, m)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_ADDR,v)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_ADDR,m,v,HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_IN)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_ADDR                             (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000004c)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_RMSK                                 0xffff
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_ADDR, HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_RMSK)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_ADDR, m)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_ADDR,v)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_ADDR,m,v,HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_IN)
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_0_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_ADDR                             (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000050)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_ADDR, HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_RMSK)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_ADDR, m)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_ADDR,v)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_ADDR,m,v,HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_IN)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_BMSK              0xffffffff
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_SHFT                     0x0

#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_ADDR                             (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000054)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_RMSK                             0xffffffff
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_ADDR, HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_RMSK)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_ADDR, m)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_ADDR,v)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_ADDR,m,v,HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_IN)
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_BMSK             0xffffffff
#define HWIO_RAM_0_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_SHFT                    0x0

#define HWIO_RAM_0_IMEM_CONFIG_ADDR                                      (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000058)
#define HWIO_RAM_0_IMEM_CONFIG_RMSK                                            0x1f
#define HWIO_RAM_0_IMEM_CONFIG_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_CONFIG_ADDR, HWIO_RAM_0_IMEM_CONFIG_RMSK)
#define HWIO_RAM_0_IMEM_CONFIG_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_CONFIG_ADDR, m)
#define HWIO_RAM_0_IMEM_CONFIG_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_CONFIG_ADDR,v)
#define HWIO_RAM_0_IMEM_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_CONFIG_ADDR,m,v,HWIO_RAM_0_IMEM_CONFIG_IN)
#define HWIO_RAM_0_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_BMSK                        0x10
#define HWIO_RAM_0_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_SHFT                         0x4
#define HWIO_RAM_0_IMEM_CONFIG_ECC_ENABLE_BMSK                                  0x8
#define HWIO_RAM_0_IMEM_CONFIG_ECC_ENABLE_SHFT                                  0x3
#define HWIO_RAM_0_IMEM_CONFIG_ECC_ENABLE_WR_BMSK                               0x4
#define HWIO_RAM_0_IMEM_CONFIG_ECC_ENABLE_WR_SHFT                               0x2
#define HWIO_RAM_0_IMEM_CONFIG_ECC_ENABLE_RD_BMSK                               0x2
#define HWIO_RAM_0_IMEM_CONFIG_ECC_ENABLE_RD_SHFT                               0x1
#define HWIO_RAM_0_IMEM_CONFIG_ECC_RD_RMW_EN_BMSK                               0x1
#define HWIO_RAM_0_IMEM_CONFIG_ECC_RD_RMW_EN_SHFT                               0x0

#define HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_ADDR                        (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000005c)
#define HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_RMSK                        0xffffffff
#define HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_RMSK)
#define HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, m)
#define HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,v)
#define HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,m,v,HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_IN)
#define HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_BMSK              0xffffffff
#define HWIO_RAM_0_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_SHFT                     0x0

#define HWIO_RAM_0_IMEM_CLK_ON_CFG_ADDR                                  (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000064)
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_RMSK                                       0xfff
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_CLK_ON_CFG_ADDR, HWIO_RAM_0_IMEM_CLK_ON_CFG_RMSK)
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_CLK_ON_CFG_ADDR, m)
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_CLK_ON_CFG_ADDR,v)
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_CLK_ON_CFG_ADDR,m,v,HWIO_RAM_0_IMEM_CLK_ON_CFG_IN)
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_CLK_ON_TIME_BMSK                           0xffc
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_CLK_ON_TIME_SHFT                             0x2
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_BMSK                           0x2
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_SHFT                           0x1
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_CLK_ON_EN_BMSK                               0x1
#define HWIO_RAM_0_IMEM_CLK_ON_CFG_CLK_ON_EN_SHFT                               0x0

#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_ADDR                               (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000006c)
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_RMSK                                     0xff
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_PSBCGC_TIMERS_ADDR, HWIO_RAM_0_IMEM_PSBCGC_TIMERS_RMSK)
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_PSBCGC_TIMERS_ADDR, m)
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_PSBCGC_TIMERS_ADDR,v)
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_PSBCGC_TIMERS_ADDR,m,v,HWIO_RAM_0_IMEM_PSBCGC_TIMERS_IN)
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_BMSK                      0xf0
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_SHFT                       0x4
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_BMSK                     0xf
#define HWIO_RAM_0_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_SHFT                     0x0

#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_ADDR                              (RAM_0_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000070)
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_RMSK                              0x3fffffff
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_IN          \
        in_dword_masked(HWIO_RAM_0_IMEM_PSBCGC_CONTROL_ADDR, HWIO_RAM_0_IMEM_PSBCGC_CONTROL_RMSK)
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_RAM_0_IMEM_PSBCGC_CONTROL_ADDR, m)
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_OUT(v)      \
        out_dword(HWIO_RAM_0_IMEM_PSBCGC_CONTROL_ADDR,v)
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_0_IMEM_PSBCGC_CONTROL_ADDR,m,v,HWIO_RAM_0_IMEM_PSBCGC_CONTROL_IN)
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_HALT_CLOCK_BMSK                   0x3ff00000
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_HALT_CLOCK_SHFT                         0x14
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_CORE_ON_BMSK                         0xffc00
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_CORE_ON_SHFT                             0xa
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_PERIF_ON_BMSK                          0x3ff
#define HWIO_RAM_0_IMEM_PSBCGC_CONTROL_PERIF_ON_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: RAM_1_IMEM_IMEM_IMEM_CSRS
 *--------------------------------------------------------------------------*/

#define RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE                               (IMC_BASE      + 0x00540000)

#define HWIO_RAM_1_IMEM_HW_ID_ADDR                                       (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000000)
#define HWIO_RAM_1_IMEM_HW_ID_RMSK                                       0xffffffff
#define HWIO_RAM_1_IMEM_HW_ID_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_HW_ID_ADDR, HWIO_RAM_1_IMEM_HW_ID_RMSK)
#define HWIO_RAM_1_IMEM_HW_ID_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_HW_ID_ADDR, m)
#define HWIO_RAM_1_IMEM_HW_ID_MAJOR_BMSK                                 0xff000000
#define HWIO_RAM_1_IMEM_HW_ID_MAJOR_SHFT                                       0x18
#define HWIO_RAM_1_IMEM_HW_ID_MINOR_BMSK                                   0xff0000
#define HWIO_RAM_1_IMEM_HW_ID_MINOR_SHFT                                       0x10
#define HWIO_RAM_1_IMEM_HW_ID_CONFIG_BMSK                                    0xff00
#define HWIO_RAM_1_IMEM_HW_ID_CONFIG_SHFT                                       0x8
#define HWIO_RAM_1_IMEM_HW_ID_INSTANCE_BMSK                                    0xff
#define HWIO_RAM_1_IMEM_HW_ID_INSTANCE_SHFT                                     0x0

#define HWIO_RAM_1_IMEM_HW_VERSION_ADDR                                  (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000004)
#define HWIO_RAM_1_IMEM_HW_VERSION_RMSK                                  0xffffffff
#define HWIO_RAM_1_IMEM_HW_VERSION_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_HW_VERSION_ADDR, HWIO_RAM_1_IMEM_HW_VERSION_RMSK)
#define HWIO_RAM_1_IMEM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_HW_VERSION_ADDR, m)
#define HWIO_RAM_1_IMEM_HW_VERSION_MAJOR_BMSK                            0xff000000
#define HWIO_RAM_1_IMEM_HW_VERSION_MAJOR_SHFT                                  0x18
#define HWIO_RAM_1_IMEM_HW_VERSION_MINOR_BMSK                              0xff0000
#define HWIO_RAM_1_IMEM_HW_VERSION_MINOR_SHFT                                  0x10
#define HWIO_RAM_1_IMEM_HW_VERSION_STEP_BMSK                                 0xffff
#define HWIO_RAM_1_IMEM_HW_VERSION_STEP_SHFT                                    0x0

#define HWIO_RAM_1_IMEM_ERR_STATUS_ADDR                                  (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000008)
#define HWIO_RAM_1_IMEM_ERR_STATUS_RMSK                                       0x3ff
#define HWIO_RAM_1_IMEM_ERR_STATUS_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_STATUS_ADDR, HWIO_RAM_1_IMEM_ERR_STATUS_RMSK)
#define HWIO_RAM_1_IMEM_ERR_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_STATUS_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_BMSK                   0x200
#define HWIO_RAM_1_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_SHFT                     0x9
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_POISON_SCRUB_BMSK                      0x100
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_POISON_SCRUB_SHFT                        0x8
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_UE_SCRUB_BMSK                           0x80
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_UE_SCRUB_SHFT                            0x7
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_CE_SCRUB_BMSK                           0x40
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_CE_SCRUB_SHFT                            0x6
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_POISON_RMW_BMSK                         0x20
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_POISON_RMW_SHFT                          0x5
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_UE_RMW_BMSK                             0x10
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_UE_RMW_SHFT                              0x4
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_CE_RMW_BMSK                              0x8
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_CE_RMW_SHFT                              0x3
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_BMSK                       0x4
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_SHFT                       0x2
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_UE_QSB_RD_BMSK                           0x2
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_UE_QSB_RD_SHFT                           0x1
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_CE_QSB_RD_BMSK                           0x1
#define HWIO_RAM_1_IMEM_ERR_STATUS_ECC_CE_QSB_RD_SHFT                           0x0

#define HWIO_RAM_1_IMEM_ERR_CLR_ADDR                                     (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000000c)
#define HWIO_RAM_1_IMEM_ERR_CLR_RMSK                                          0x3ff
#define HWIO_RAM_1_IMEM_ERR_CLR_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_ERR_CLR_ADDR,v)
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_1_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_1_IMEM_ERR_CTRL_ADDR                                    (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000010)
#define HWIO_RAM_1_IMEM_ERR_CTRL_RMSK                                         0x3ff
#define HWIO_RAM_1_IMEM_ERR_CTRL_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CTRL_ADDR, HWIO_RAM_1_IMEM_ERR_CTRL_RMSK)
#define HWIO_RAM_1_IMEM_ERR_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CTRL_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_ERR_CTRL_ADDR,v)
#define HWIO_RAM_1_IMEM_ERR_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_ERR_CTRL_ADDR,m,v,HWIO_RAM_1_IMEM_ERR_CTRL_IN)
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_BMSK                0x200
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_SHFT                  0x9
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_BMSK                   0x100
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_SHFT                     0x8
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_BMSK                        0x80
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_SHFT                         0x7
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_BMSK                        0x40
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_SHFT                         0x6
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_BMSK                      0x20
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_SHFT                       0x5
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_BMSK                          0x10
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_SHFT                           0x4
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_BMSK                           0x8
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_SHFT                           0x3
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_BMSK                    0x4
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_SHFT                    0x2
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_BMSK                        0x2
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_SHFT                        0x1
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_BMSK                        0x1
#define HWIO_RAM_1_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_SHFT                        0x0

#define HWIO_RAM_1_IMEM_INT0_CTRL_ADDR                                   (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000014)
#define HWIO_RAM_1_IMEM_INT0_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_1_IMEM_INT0_CTRL_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_INT0_CTRL_ADDR, HWIO_RAM_1_IMEM_INT0_CTRL_RMSK)
#define HWIO_RAM_1_IMEM_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_INT0_CTRL_ADDR, m)
#define HWIO_RAM_1_IMEM_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_INT0_CTRL_ADDR,v)
#define HWIO_RAM_1_IMEM_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_INT0_CTRL_ADDR,m,v,HWIO_RAM_1_IMEM_INT0_CTRL_IN)
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_1_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_1_IMEM_INT1_CTRL_ADDR                                   (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000018)
#define HWIO_RAM_1_IMEM_INT1_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_1_IMEM_INT1_CTRL_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_INT1_CTRL_ADDR, HWIO_RAM_1_IMEM_INT1_CTRL_RMSK)
#define HWIO_RAM_1_IMEM_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_INT1_CTRL_ADDR, m)
#define HWIO_RAM_1_IMEM_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_INT1_CTRL_ADDR,v)
#define HWIO_RAM_1_IMEM_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_INT1_CTRL_ADDR,m,v,HWIO_RAM_1_IMEM_INT1_CTRL_IN)
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_1_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_1_IMEM_ERR_INJ_ADDR                                     (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000001c)
#define HWIO_RAM_1_IMEM_ERR_INJ_RMSK                                          0x3ff
#define HWIO_RAM_1_IMEM_ERR_INJ_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_ERR_INJ_ADDR,v)
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_1_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_ADDR                                (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000020)
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_RMSK                                      0x1f
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_CNTL_ADDR, HWIO_RAM_1_IMEM_ERR_CAP_CNTL_RMSK)
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_CNTL_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_ERR_CAP_CNTL_ADDR,v)
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_ERR_CAP_CNTL_ADDR,m,v,HWIO_RAM_1_IMEM_ERR_CAP_CNTL_IN)
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_BMSK                       0x10
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_SHFT                        0x4
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_BMSK                        0x8
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_SHFT                        0x3
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_BMSK                    0x4
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_SHFT                    0x2
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_BMSK                    0x2
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_SHFT                    0x1
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_BMSK                          0x1
#define HWIO_RAM_1_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_SHFT                          0x0

#define HWIO_RAM_1_IMEM_ERR_CAP_0_ADDR                                   (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000024)
#define HWIO_RAM_1_IMEM_ERR_CAP_0_RMSK                                   0xffffffff
#define HWIO_RAM_1_IMEM_ERR_CAP_0_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_0_ADDR, HWIO_RAM_1_IMEM_ERR_CAP_0_RMSK)
#define HWIO_RAM_1_IMEM_ERR_CAP_0_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_0_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_CAP_0_ERR_ADDR_LO_BMSK                       0xffffffff
#define HWIO_RAM_1_IMEM_ERR_CAP_0_ERR_ADDR_LO_SHFT                              0x0

#define HWIO_RAM_1_IMEM_ERR_CAP_1_ADDR                                   (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000028)
#define HWIO_RAM_1_IMEM_ERR_CAP_1_RMSK                                   0xffff0fff
#define HWIO_RAM_1_IMEM_ERR_CAP_1_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_1_ADDR, HWIO_RAM_1_IMEM_ERR_CAP_1_RMSK)
#define HWIO_RAM_1_IMEM_ERR_CAP_1_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_1_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_BMSK                0xff000000
#define HWIO_RAM_1_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_SHFT                      0x18
#define HWIO_RAM_1_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_BMSK                   0xff0000
#define HWIO_RAM_1_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_SHFT                       0x10
#define HWIO_RAM_1_IMEM_ERR_CAP_1_ERR_ADDR_HI_BMSK                            0xfff
#define HWIO_RAM_1_IMEM_ERR_CAP_1_ERR_ADDR_HI_SHFT                              0x0

#define HWIO_RAM_1_IMEM_ERR_CAP_2_ADDR                                   (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000002c)
#define HWIO_RAM_1_IMEM_ERR_CAP_2_RMSK                                   0x1fffffff
#define HWIO_RAM_1_IMEM_ERR_CAP_2_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_2_ADDR, HWIO_RAM_1_IMEM_ERR_CAP_2_RMSK)
#define HWIO_RAM_1_IMEM_ERR_CAP_2_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_2_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_ABURST_BMSK                        0x10000000
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_ABURST_SHFT                              0x1c
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_AWRITE_BMSK                         0x8000000
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_AWRITE_SHFT                              0x1b
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_ALEN_BMSK                           0x7c00000
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_ALEN_SHFT                                0x16
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_BMSK                      0x200000
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_SHFT                          0x15
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_TID_BMSK                             0x1f0000
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_TID_SHFT                                 0x10
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_BID_BMSK                               0xe000
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_BID_SHFT                                  0xd
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_PID_BMSK                               0x1f00
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_PID_SHFT                                  0x8
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_MID_BMSK                                 0xff
#define HWIO_RAM_1_IMEM_ERR_CAP_2_ERR_MID_SHFT                                  0x0

#define HWIO_RAM_1_IMEM_ERR_CAP_3_ADDR                                   (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000030)
#define HWIO_RAM_1_IMEM_ERR_CAP_3_RMSK                                      0x3ffff
#define HWIO_RAM_1_IMEM_ERR_CAP_3_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_3_ADDR, HWIO_RAM_1_IMEM_ERR_CAP_3_RMSK)
#define HWIO_RAM_1_IMEM_ERR_CAP_3_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_3_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_CAP_3_ERR_VMID_BMSK                             0x3fc00
#define HWIO_RAM_1_IMEM_ERR_CAP_3_ERR_VMID_SHFT                                 0xa
#define HWIO_RAM_1_IMEM_ERR_CAP_3_ERR_MSA_BMSK                                0x200
#define HWIO_RAM_1_IMEM_ERR_CAP_3_ERR_MSA_SHFT                                  0x9
#define HWIO_RAM_1_IMEM_ERR_CAP_3_ERR_NSPROT_BMSK                             0x100
#define HWIO_RAM_1_IMEM_ERR_CAP_3_ERR_NSPROT_SHFT                               0x8
#define HWIO_RAM_1_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_BMSK                          0xff
#define HWIO_RAM_1_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_SHFT                           0x0

#define HWIO_RAM_1_IMEM_ERR_CAP_4_ADDR                                   (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000034)
#define HWIO_RAM_1_IMEM_ERR_CAP_4_RMSK                                    0x1ffffff
#define HWIO_RAM_1_IMEM_ERR_CAP_4_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_4_ADDR, HWIO_RAM_1_IMEM_ERR_CAP_4_RMSK)
#define HWIO_RAM_1_IMEM_ERR_CAP_4_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_CAP_4_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_BMSK                      0x1000000
#define HWIO_RAM_1_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_SHFT                           0x18
#define HWIO_RAM_1_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_BMSK                    0xff0000
#define HWIO_RAM_1_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_SHFT                        0x10
#define HWIO_RAM_1_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_BMSK                      0xff00
#define HWIO_RAM_1_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_SHFT                         0x8
#define HWIO_RAM_1_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_BMSK                        0xff
#define HWIO_RAM_1_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_SHFT                         0x0

#define HWIO_RAM_1_IMEM_ERR_COUNT_ADDR                                   (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000074)
#define HWIO_RAM_1_IMEM_ERR_COUNT_RMSK                                   0xffffffff
#define HWIO_RAM_1_IMEM_ERR_COUNT_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_COUNT_ADDR, HWIO_RAM_1_IMEM_ERR_COUNT_RMSK)
#define HWIO_RAM_1_IMEM_ERR_COUNT_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_ERR_COUNT_ADDR, m)
#define HWIO_RAM_1_IMEM_ERR_COUNT_ERR_UE_COUNT_BMSK                      0xffff0000
#define HWIO_RAM_1_IMEM_ERR_COUNT_ERR_UE_COUNT_SHFT                            0x10
#define HWIO_RAM_1_IMEM_ERR_COUNT_ERR_CE_COUNT_BMSK                          0xffff
#define HWIO_RAM_1_IMEM_ERR_COUNT_ERR_CE_COUNT_SHFT                             0x0

#define HWIO_RAM_1_IMEM_SCRUB_STATUS_ADDR                                (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000038)
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_RMSK                                       0x7
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_STATUS_ADDR, HWIO_RAM_1_IMEM_SCRUB_STATUS_RMSK)
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_STATUS_ADDR, m)
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_SCRUB_INPROG_BMSK                          0x4
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_SCRUB_INPROG_SHFT                          0x2
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_WIPE_INPROG_BMSK                           0x2
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_WIPE_INPROG_SHFT                           0x1
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_ADDR_MAX_BMSK                              0x1
#define HWIO_RAM_1_IMEM_SCRUB_STATUS_ADDR_MAX_SHFT                              0x0

#define HWIO_RAM_1_IMEM_SCRUB_CTRL_ADDR                                  (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000003c)
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_RMSK                                  0xfff8ffff
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_CTRL_ADDR, HWIO_RAM_1_IMEM_SCRUB_CTRL_RMSK)
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_CTRL_ADDR, m)
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_SCRUB_CTRL_ADDR,v)
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_SCRUB_CTRL_ADDR,m,v,HWIO_RAM_1_IMEM_SCRUB_CTRL_IN)
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_SCRUB_EN_BMSK                         0x80000000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_SCRUB_EN_SHFT                               0x1f
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_LOAD_ADDR_BMSK                        0x40000000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_LOAD_ADDR_SHFT                              0x1e
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_WRITE_DATA_BMSK                       0x20000000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_WRITE_DATA_SHFT                             0x1d
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_WIPE_DATA_BMSK                        0x10000000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_WIPE_DATA_SHFT                              0x1c
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_BMSK                    0x8000000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_SHFT                         0x1b
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_BMSK                      0x4000000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_SHFT                           0x1a
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_BMSK                    0x2000000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_SHFT                         0x19
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_BMSK                     0x1000000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_SHFT                          0x18
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_NUM_ADDR_BMSK                           0xf80000
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_NUM_ADDR_SHFT                               0x13
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_SCRUB_TIMER_BMSK                          0xffff
#define HWIO_RAM_1_IMEM_SCRUB_CTRL_SCRUB_TIMER_SHFT                             0x0

#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_ADDR                             (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000040)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_RMSK                             0xffffffff
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_ADDR, HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_RMSK)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_ADDR, m)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_ADDR                             (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000044)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_RMSK                                 0xffff
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_ADDR, HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_RMSK)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_ADDR, m)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_ADDR                             (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000048)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_ADDR, HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_RMSK)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_ADDR, m)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_ADDR,v)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_ADDR,m,v,HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_IN)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_ADDR                             (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000004c)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_RMSK                                 0xffff
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_ADDR, HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_RMSK)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_ADDR, m)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_ADDR,v)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_ADDR,m,v,HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_IN)
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_1_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_ADDR                             (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000050)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_ADDR, HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_RMSK)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_ADDR, m)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_ADDR,v)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_ADDR,m,v,HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_IN)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_BMSK              0xffffffff
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_SHFT                     0x0

#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_ADDR                             (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000054)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_RMSK                             0xffffffff
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_ADDR, HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_RMSK)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_ADDR, m)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_ADDR,v)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_ADDR,m,v,HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_IN)
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_BMSK             0xffffffff
#define HWIO_RAM_1_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_SHFT                    0x0

#define HWIO_RAM_1_IMEM_CONFIG_ADDR                                      (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000058)
#define HWIO_RAM_1_IMEM_CONFIG_RMSK                                            0x1f
#define HWIO_RAM_1_IMEM_CONFIG_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_CONFIG_ADDR, HWIO_RAM_1_IMEM_CONFIG_RMSK)
#define HWIO_RAM_1_IMEM_CONFIG_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_CONFIG_ADDR, m)
#define HWIO_RAM_1_IMEM_CONFIG_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_CONFIG_ADDR,v)
#define HWIO_RAM_1_IMEM_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_CONFIG_ADDR,m,v,HWIO_RAM_1_IMEM_CONFIG_IN)
#define HWIO_RAM_1_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_BMSK                        0x10
#define HWIO_RAM_1_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_SHFT                         0x4
#define HWIO_RAM_1_IMEM_CONFIG_ECC_ENABLE_BMSK                                  0x8
#define HWIO_RAM_1_IMEM_CONFIG_ECC_ENABLE_SHFT                                  0x3
#define HWIO_RAM_1_IMEM_CONFIG_ECC_ENABLE_WR_BMSK                               0x4
#define HWIO_RAM_1_IMEM_CONFIG_ECC_ENABLE_WR_SHFT                               0x2
#define HWIO_RAM_1_IMEM_CONFIG_ECC_ENABLE_RD_BMSK                               0x2
#define HWIO_RAM_1_IMEM_CONFIG_ECC_ENABLE_RD_SHFT                               0x1
#define HWIO_RAM_1_IMEM_CONFIG_ECC_RD_RMW_EN_BMSK                               0x1
#define HWIO_RAM_1_IMEM_CONFIG_ECC_RD_RMW_EN_SHFT                               0x0

#define HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_ADDR                        (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000005c)
#define HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_RMSK                        0xffffffff
#define HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_RMSK)
#define HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, m)
#define HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,v)
#define HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,m,v,HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_IN)
#define HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_BMSK              0xffffffff
#define HWIO_RAM_1_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_SHFT                     0x0

#define HWIO_RAM_1_IMEM_CLK_ON_CFG_ADDR                                  (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000064)
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_RMSK                                       0xfff
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_CLK_ON_CFG_ADDR, HWIO_RAM_1_IMEM_CLK_ON_CFG_RMSK)
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_CLK_ON_CFG_ADDR, m)
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_CLK_ON_CFG_ADDR,v)
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_CLK_ON_CFG_ADDR,m,v,HWIO_RAM_1_IMEM_CLK_ON_CFG_IN)
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_CLK_ON_TIME_BMSK                           0xffc
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_CLK_ON_TIME_SHFT                             0x2
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_BMSK                           0x2
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_SHFT                           0x1
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_CLK_ON_EN_BMSK                               0x1
#define HWIO_RAM_1_IMEM_CLK_ON_CFG_CLK_ON_EN_SHFT                               0x0

#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_ADDR                               (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000006c)
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_RMSK                                     0xff
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_PSBCGC_TIMERS_ADDR, HWIO_RAM_1_IMEM_PSBCGC_TIMERS_RMSK)
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_PSBCGC_TIMERS_ADDR, m)
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_PSBCGC_TIMERS_ADDR,v)
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_PSBCGC_TIMERS_ADDR,m,v,HWIO_RAM_1_IMEM_PSBCGC_TIMERS_IN)
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_BMSK                      0xf0
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_SHFT                       0x4
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_BMSK                     0xf
#define HWIO_RAM_1_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_SHFT                     0x0

#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_ADDR                              (RAM_1_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000070)
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_RMSK                              0x3fffffff
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_IN          \
        in_dword_masked(HWIO_RAM_1_IMEM_PSBCGC_CONTROL_ADDR, HWIO_RAM_1_IMEM_PSBCGC_CONTROL_RMSK)
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_RAM_1_IMEM_PSBCGC_CONTROL_ADDR, m)
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_OUT(v)      \
        out_dword(HWIO_RAM_1_IMEM_PSBCGC_CONTROL_ADDR,v)
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_1_IMEM_PSBCGC_CONTROL_ADDR,m,v,HWIO_RAM_1_IMEM_PSBCGC_CONTROL_IN)
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_HALT_CLOCK_BMSK                   0x3ff00000
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_HALT_CLOCK_SHFT                         0x14
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_CORE_ON_BMSK                         0xffc00
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_CORE_ON_SHFT                             0xa
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_PERIF_ON_BMSK                          0x3ff
#define HWIO_RAM_1_IMEM_PSBCGC_CONTROL_PERIF_ON_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: RAM_2_IMEM_IMEM_IMEM_CSRS
 *--------------------------------------------------------------------------*/

#define RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE                               (IMC_BASE      + 0x00580000)

#define HWIO_RAM_2_IMEM_HW_ID_ADDR                                       (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000000)
#define HWIO_RAM_2_IMEM_HW_ID_RMSK                                       0xffffffff
#define HWIO_RAM_2_IMEM_HW_ID_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_HW_ID_ADDR, HWIO_RAM_2_IMEM_HW_ID_RMSK)
#define HWIO_RAM_2_IMEM_HW_ID_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_HW_ID_ADDR, m)
#define HWIO_RAM_2_IMEM_HW_ID_MAJOR_BMSK                                 0xff000000
#define HWIO_RAM_2_IMEM_HW_ID_MAJOR_SHFT                                       0x18
#define HWIO_RAM_2_IMEM_HW_ID_MINOR_BMSK                                   0xff0000
#define HWIO_RAM_2_IMEM_HW_ID_MINOR_SHFT                                       0x10
#define HWIO_RAM_2_IMEM_HW_ID_CONFIG_BMSK                                    0xff00
#define HWIO_RAM_2_IMEM_HW_ID_CONFIG_SHFT                                       0x8
#define HWIO_RAM_2_IMEM_HW_ID_INSTANCE_BMSK                                    0xff
#define HWIO_RAM_2_IMEM_HW_ID_INSTANCE_SHFT                                     0x0

#define HWIO_RAM_2_IMEM_HW_VERSION_ADDR                                  (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000004)
#define HWIO_RAM_2_IMEM_HW_VERSION_RMSK                                  0xffffffff
#define HWIO_RAM_2_IMEM_HW_VERSION_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_HW_VERSION_ADDR, HWIO_RAM_2_IMEM_HW_VERSION_RMSK)
#define HWIO_RAM_2_IMEM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_HW_VERSION_ADDR, m)
#define HWIO_RAM_2_IMEM_HW_VERSION_MAJOR_BMSK                            0xff000000
#define HWIO_RAM_2_IMEM_HW_VERSION_MAJOR_SHFT                                  0x18
#define HWIO_RAM_2_IMEM_HW_VERSION_MINOR_BMSK                              0xff0000
#define HWIO_RAM_2_IMEM_HW_VERSION_MINOR_SHFT                                  0x10
#define HWIO_RAM_2_IMEM_HW_VERSION_STEP_BMSK                                 0xffff
#define HWIO_RAM_2_IMEM_HW_VERSION_STEP_SHFT                                    0x0

#define HWIO_RAM_2_IMEM_ERR_STATUS_ADDR                                  (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000008)
#define HWIO_RAM_2_IMEM_ERR_STATUS_RMSK                                       0x3ff
#define HWIO_RAM_2_IMEM_ERR_STATUS_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_STATUS_ADDR, HWIO_RAM_2_IMEM_ERR_STATUS_RMSK)
#define HWIO_RAM_2_IMEM_ERR_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_STATUS_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_BMSK                   0x200
#define HWIO_RAM_2_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_SHFT                     0x9
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_POISON_SCRUB_BMSK                      0x100
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_POISON_SCRUB_SHFT                        0x8
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_UE_SCRUB_BMSK                           0x80
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_UE_SCRUB_SHFT                            0x7
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_CE_SCRUB_BMSK                           0x40
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_CE_SCRUB_SHFT                            0x6
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_POISON_RMW_BMSK                         0x20
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_POISON_RMW_SHFT                          0x5
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_UE_RMW_BMSK                             0x10
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_UE_RMW_SHFT                              0x4
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_CE_RMW_BMSK                              0x8
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_CE_RMW_SHFT                              0x3
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_BMSK                       0x4
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_SHFT                       0x2
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_UE_QSB_RD_BMSK                           0x2
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_UE_QSB_RD_SHFT                           0x1
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_CE_QSB_RD_BMSK                           0x1
#define HWIO_RAM_2_IMEM_ERR_STATUS_ECC_CE_QSB_RD_SHFT                           0x0

#define HWIO_RAM_2_IMEM_ERR_CLR_ADDR                                     (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000000c)
#define HWIO_RAM_2_IMEM_ERR_CLR_RMSK                                          0x3ff
#define HWIO_RAM_2_IMEM_ERR_CLR_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_ERR_CLR_ADDR,v)
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_2_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_2_IMEM_ERR_CTRL_ADDR                                    (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000010)
#define HWIO_RAM_2_IMEM_ERR_CTRL_RMSK                                         0x3ff
#define HWIO_RAM_2_IMEM_ERR_CTRL_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CTRL_ADDR, HWIO_RAM_2_IMEM_ERR_CTRL_RMSK)
#define HWIO_RAM_2_IMEM_ERR_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CTRL_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_ERR_CTRL_ADDR,v)
#define HWIO_RAM_2_IMEM_ERR_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_ERR_CTRL_ADDR,m,v,HWIO_RAM_2_IMEM_ERR_CTRL_IN)
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_BMSK                0x200
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_SHFT                  0x9
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_BMSK                   0x100
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_SHFT                     0x8
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_BMSK                        0x80
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_SHFT                         0x7
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_BMSK                        0x40
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_SHFT                         0x6
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_BMSK                      0x20
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_SHFT                       0x5
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_BMSK                          0x10
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_SHFT                           0x4
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_BMSK                           0x8
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_SHFT                           0x3
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_BMSK                    0x4
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_SHFT                    0x2
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_BMSK                        0x2
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_SHFT                        0x1
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_BMSK                        0x1
#define HWIO_RAM_2_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_SHFT                        0x0

#define HWIO_RAM_2_IMEM_INT0_CTRL_ADDR                                   (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000014)
#define HWIO_RAM_2_IMEM_INT0_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_2_IMEM_INT0_CTRL_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_INT0_CTRL_ADDR, HWIO_RAM_2_IMEM_INT0_CTRL_RMSK)
#define HWIO_RAM_2_IMEM_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_INT0_CTRL_ADDR, m)
#define HWIO_RAM_2_IMEM_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_INT0_CTRL_ADDR,v)
#define HWIO_RAM_2_IMEM_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_INT0_CTRL_ADDR,m,v,HWIO_RAM_2_IMEM_INT0_CTRL_IN)
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_2_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_2_IMEM_INT1_CTRL_ADDR                                   (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000018)
#define HWIO_RAM_2_IMEM_INT1_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_2_IMEM_INT1_CTRL_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_INT1_CTRL_ADDR, HWIO_RAM_2_IMEM_INT1_CTRL_RMSK)
#define HWIO_RAM_2_IMEM_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_INT1_CTRL_ADDR, m)
#define HWIO_RAM_2_IMEM_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_INT1_CTRL_ADDR,v)
#define HWIO_RAM_2_IMEM_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_INT1_CTRL_ADDR,m,v,HWIO_RAM_2_IMEM_INT1_CTRL_IN)
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_2_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_2_IMEM_ERR_INJ_ADDR                                     (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000001c)
#define HWIO_RAM_2_IMEM_ERR_INJ_RMSK                                          0x3ff
#define HWIO_RAM_2_IMEM_ERR_INJ_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_ERR_INJ_ADDR,v)
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_2_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_ADDR                                (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000020)
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_RMSK                                      0x1f
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_CNTL_ADDR, HWIO_RAM_2_IMEM_ERR_CAP_CNTL_RMSK)
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_CNTL_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_ERR_CAP_CNTL_ADDR,v)
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_ERR_CAP_CNTL_ADDR,m,v,HWIO_RAM_2_IMEM_ERR_CAP_CNTL_IN)
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_BMSK                       0x10
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_SHFT                        0x4
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_BMSK                        0x8
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_SHFT                        0x3
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_BMSK                    0x4
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_SHFT                    0x2
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_BMSK                    0x2
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_SHFT                    0x1
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_BMSK                          0x1
#define HWIO_RAM_2_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_SHFT                          0x0

#define HWIO_RAM_2_IMEM_ERR_CAP_0_ADDR                                   (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000024)
#define HWIO_RAM_2_IMEM_ERR_CAP_0_RMSK                                   0xffffffff
#define HWIO_RAM_2_IMEM_ERR_CAP_0_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_0_ADDR, HWIO_RAM_2_IMEM_ERR_CAP_0_RMSK)
#define HWIO_RAM_2_IMEM_ERR_CAP_0_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_0_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_CAP_0_ERR_ADDR_LO_BMSK                       0xffffffff
#define HWIO_RAM_2_IMEM_ERR_CAP_0_ERR_ADDR_LO_SHFT                              0x0

#define HWIO_RAM_2_IMEM_ERR_CAP_1_ADDR                                   (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000028)
#define HWIO_RAM_2_IMEM_ERR_CAP_1_RMSK                                   0xffff0fff
#define HWIO_RAM_2_IMEM_ERR_CAP_1_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_1_ADDR, HWIO_RAM_2_IMEM_ERR_CAP_1_RMSK)
#define HWIO_RAM_2_IMEM_ERR_CAP_1_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_1_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_BMSK                0xff000000
#define HWIO_RAM_2_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_SHFT                      0x18
#define HWIO_RAM_2_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_BMSK                   0xff0000
#define HWIO_RAM_2_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_SHFT                       0x10
#define HWIO_RAM_2_IMEM_ERR_CAP_1_ERR_ADDR_HI_BMSK                            0xfff
#define HWIO_RAM_2_IMEM_ERR_CAP_1_ERR_ADDR_HI_SHFT                              0x0

#define HWIO_RAM_2_IMEM_ERR_CAP_2_ADDR                                   (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000002c)
#define HWIO_RAM_2_IMEM_ERR_CAP_2_RMSK                                   0x1fffffff
#define HWIO_RAM_2_IMEM_ERR_CAP_2_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_2_ADDR, HWIO_RAM_2_IMEM_ERR_CAP_2_RMSK)
#define HWIO_RAM_2_IMEM_ERR_CAP_2_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_2_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_ABURST_BMSK                        0x10000000
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_ABURST_SHFT                              0x1c
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_AWRITE_BMSK                         0x8000000
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_AWRITE_SHFT                              0x1b
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_ALEN_BMSK                           0x7c00000
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_ALEN_SHFT                                0x16
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_BMSK                      0x200000
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_SHFT                          0x15
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_TID_BMSK                             0x1f0000
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_TID_SHFT                                 0x10
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_BID_BMSK                               0xe000
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_BID_SHFT                                  0xd
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_PID_BMSK                               0x1f00
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_PID_SHFT                                  0x8
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_MID_BMSK                                 0xff
#define HWIO_RAM_2_IMEM_ERR_CAP_2_ERR_MID_SHFT                                  0x0

#define HWIO_RAM_2_IMEM_ERR_CAP_3_ADDR                                   (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000030)
#define HWIO_RAM_2_IMEM_ERR_CAP_3_RMSK                                      0x3ffff
#define HWIO_RAM_2_IMEM_ERR_CAP_3_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_3_ADDR, HWIO_RAM_2_IMEM_ERR_CAP_3_RMSK)
#define HWIO_RAM_2_IMEM_ERR_CAP_3_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_3_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_CAP_3_ERR_VMID_BMSK                             0x3fc00
#define HWIO_RAM_2_IMEM_ERR_CAP_3_ERR_VMID_SHFT                                 0xa
#define HWIO_RAM_2_IMEM_ERR_CAP_3_ERR_MSA_BMSK                                0x200
#define HWIO_RAM_2_IMEM_ERR_CAP_3_ERR_MSA_SHFT                                  0x9
#define HWIO_RAM_2_IMEM_ERR_CAP_3_ERR_NSPROT_BMSK                             0x100
#define HWIO_RAM_2_IMEM_ERR_CAP_3_ERR_NSPROT_SHFT                               0x8
#define HWIO_RAM_2_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_BMSK                          0xff
#define HWIO_RAM_2_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_SHFT                           0x0

#define HWIO_RAM_2_IMEM_ERR_CAP_4_ADDR                                   (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000034)
#define HWIO_RAM_2_IMEM_ERR_CAP_4_RMSK                                    0x1ffffff
#define HWIO_RAM_2_IMEM_ERR_CAP_4_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_4_ADDR, HWIO_RAM_2_IMEM_ERR_CAP_4_RMSK)
#define HWIO_RAM_2_IMEM_ERR_CAP_4_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_CAP_4_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_BMSK                      0x1000000
#define HWIO_RAM_2_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_SHFT                           0x18
#define HWIO_RAM_2_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_BMSK                    0xff0000
#define HWIO_RAM_2_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_SHFT                        0x10
#define HWIO_RAM_2_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_BMSK                      0xff00
#define HWIO_RAM_2_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_SHFT                         0x8
#define HWIO_RAM_2_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_BMSK                        0xff
#define HWIO_RAM_2_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_SHFT                         0x0

#define HWIO_RAM_2_IMEM_ERR_COUNT_ADDR                                   (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000074)
#define HWIO_RAM_2_IMEM_ERR_COUNT_RMSK                                   0xffffffff
#define HWIO_RAM_2_IMEM_ERR_COUNT_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_COUNT_ADDR, HWIO_RAM_2_IMEM_ERR_COUNT_RMSK)
#define HWIO_RAM_2_IMEM_ERR_COUNT_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_ERR_COUNT_ADDR, m)
#define HWIO_RAM_2_IMEM_ERR_COUNT_ERR_UE_COUNT_BMSK                      0xffff0000
#define HWIO_RAM_2_IMEM_ERR_COUNT_ERR_UE_COUNT_SHFT                            0x10
#define HWIO_RAM_2_IMEM_ERR_COUNT_ERR_CE_COUNT_BMSK                          0xffff
#define HWIO_RAM_2_IMEM_ERR_COUNT_ERR_CE_COUNT_SHFT                             0x0

#define HWIO_RAM_2_IMEM_SCRUB_STATUS_ADDR                                (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000038)
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_RMSK                                       0x7
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_STATUS_ADDR, HWIO_RAM_2_IMEM_SCRUB_STATUS_RMSK)
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_STATUS_ADDR, m)
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_SCRUB_INPROG_BMSK                          0x4
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_SCRUB_INPROG_SHFT                          0x2
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_WIPE_INPROG_BMSK                           0x2
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_WIPE_INPROG_SHFT                           0x1
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_ADDR_MAX_BMSK                              0x1
#define HWIO_RAM_2_IMEM_SCRUB_STATUS_ADDR_MAX_SHFT                              0x0

#define HWIO_RAM_2_IMEM_SCRUB_CTRL_ADDR                                  (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000003c)
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_RMSK                                  0xfff8ffff
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_CTRL_ADDR, HWIO_RAM_2_IMEM_SCRUB_CTRL_RMSK)
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_CTRL_ADDR, m)
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_SCRUB_CTRL_ADDR,v)
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_SCRUB_CTRL_ADDR,m,v,HWIO_RAM_2_IMEM_SCRUB_CTRL_IN)
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_SCRUB_EN_BMSK                         0x80000000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_SCRUB_EN_SHFT                               0x1f
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_LOAD_ADDR_BMSK                        0x40000000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_LOAD_ADDR_SHFT                              0x1e
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_WRITE_DATA_BMSK                       0x20000000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_WRITE_DATA_SHFT                             0x1d
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_WIPE_DATA_BMSK                        0x10000000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_WIPE_DATA_SHFT                              0x1c
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_BMSK                    0x8000000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_SHFT                         0x1b
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_BMSK                      0x4000000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_SHFT                           0x1a
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_BMSK                    0x2000000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_SHFT                         0x19
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_BMSK                     0x1000000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_SHFT                          0x18
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_NUM_ADDR_BMSK                           0xf80000
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_NUM_ADDR_SHFT                               0x13
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_SCRUB_TIMER_BMSK                          0xffff
#define HWIO_RAM_2_IMEM_SCRUB_CTRL_SCRUB_TIMER_SHFT                             0x0

#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_ADDR                             (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000040)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_RMSK                             0xffffffff
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_ADDR, HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_RMSK)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_ADDR, m)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_ADDR                             (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000044)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_RMSK                                 0xffff
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_ADDR, HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_RMSK)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_ADDR, m)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_ADDR                             (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000048)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_ADDR, HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_RMSK)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_ADDR, m)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_ADDR,v)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_ADDR,m,v,HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_IN)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_ADDR                             (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000004c)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_RMSK                                 0xffff
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_ADDR, HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_RMSK)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_ADDR, m)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_ADDR,v)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_ADDR,m,v,HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_IN)
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_2_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_ADDR                             (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000050)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_ADDR, HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_RMSK)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_ADDR, m)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_ADDR,v)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_ADDR,m,v,HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_IN)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_BMSK              0xffffffff
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_SHFT                     0x0

#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_ADDR                             (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000054)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_RMSK                             0xffffffff
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_ADDR, HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_RMSK)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_ADDR, m)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_ADDR,v)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_ADDR,m,v,HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_IN)
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_BMSK             0xffffffff
#define HWIO_RAM_2_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_SHFT                    0x0

#define HWIO_RAM_2_IMEM_CONFIG_ADDR                                      (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000058)
#define HWIO_RAM_2_IMEM_CONFIG_RMSK                                            0x1f
#define HWIO_RAM_2_IMEM_CONFIG_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_CONFIG_ADDR, HWIO_RAM_2_IMEM_CONFIG_RMSK)
#define HWIO_RAM_2_IMEM_CONFIG_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_CONFIG_ADDR, m)
#define HWIO_RAM_2_IMEM_CONFIG_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_CONFIG_ADDR,v)
#define HWIO_RAM_2_IMEM_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_CONFIG_ADDR,m,v,HWIO_RAM_2_IMEM_CONFIG_IN)
#define HWIO_RAM_2_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_BMSK                        0x10
#define HWIO_RAM_2_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_SHFT                         0x4
#define HWIO_RAM_2_IMEM_CONFIG_ECC_ENABLE_BMSK                                  0x8
#define HWIO_RAM_2_IMEM_CONFIG_ECC_ENABLE_SHFT                                  0x3
#define HWIO_RAM_2_IMEM_CONFIG_ECC_ENABLE_WR_BMSK                               0x4
#define HWIO_RAM_2_IMEM_CONFIG_ECC_ENABLE_WR_SHFT                               0x2
#define HWIO_RAM_2_IMEM_CONFIG_ECC_ENABLE_RD_BMSK                               0x2
#define HWIO_RAM_2_IMEM_CONFIG_ECC_ENABLE_RD_SHFT                               0x1
#define HWIO_RAM_2_IMEM_CONFIG_ECC_RD_RMW_EN_BMSK                               0x1
#define HWIO_RAM_2_IMEM_CONFIG_ECC_RD_RMW_EN_SHFT                               0x0

#define HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_ADDR                        (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000005c)
#define HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_RMSK                        0xffffffff
#define HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_RMSK)
#define HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, m)
#define HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,v)
#define HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,m,v,HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_IN)
#define HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_BMSK              0xffffffff
#define HWIO_RAM_2_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_SHFT                     0x0

#define HWIO_RAM_2_IMEM_CLK_ON_CFG_ADDR                                  (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000064)
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_RMSK                                       0xfff
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_CLK_ON_CFG_ADDR, HWIO_RAM_2_IMEM_CLK_ON_CFG_RMSK)
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_CLK_ON_CFG_ADDR, m)
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_CLK_ON_CFG_ADDR,v)
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_CLK_ON_CFG_ADDR,m,v,HWIO_RAM_2_IMEM_CLK_ON_CFG_IN)
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_CLK_ON_TIME_BMSK                           0xffc
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_CLK_ON_TIME_SHFT                             0x2
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_BMSK                           0x2
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_SHFT                           0x1
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_CLK_ON_EN_BMSK                               0x1
#define HWIO_RAM_2_IMEM_CLK_ON_CFG_CLK_ON_EN_SHFT                               0x0

#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_ADDR                               (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000006c)
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_RMSK                                     0xff
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_PSBCGC_TIMERS_ADDR, HWIO_RAM_2_IMEM_PSBCGC_TIMERS_RMSK)
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_PSBCGC_TIMERS_ADDR, m)
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_PSBCGC_TIMERS_ADDR,v)
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_PSBCGC_TIMERS_ADDR,m,v,HWIO_RAM_2_IMEM_PSBCGC_TIMERS_IN)
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_BMSK                      0xf0
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_SHFT                       0x4
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_BMSK                     0xf
#define HWIO_RAM_2_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_SHFT                     0x0

#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_ADDR                              (RAM_2_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000070)
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_RMSK                              0x3fffffff
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_IN          \
        in_dword_masked(HWIO_RAM_2_IMEM_PSBCGC_CONTROL_ADDR, HWIO_RAM_2_IMEM_PSBCGC_CONTROL_RMSK)
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_RAM_2_IMEM_PSBCGC_CONTROL_ADDR, m)
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_OUT(v)      \
        out_dword(HWIO_RAM_2_IMEM_PSBCGC_CONTROL_ADDR,v)
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_2_IMEM_PSBCGC_CONTROL_ADDR,m,v,HWIO_RAM_2_IMEM_PSBCGC_CONTROL_IN)
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_HALT_CLOCK_BMSK                   0x3ff00000
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_HALT_CLOCK_SHFT                         0x14
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_CORE_ON_BMSK                         0xffc00
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_CORE_ON_SHFT                             0xa
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_PERIF_ON_BMSK                          0x3ff
#define HWIO_RAM_2_IMEM_PSBCGC_CONTROL_PERIF_ON_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: RAM_3_IMEM_IMEM_IMEM_CSRS
 *--------------------------------------------------------------------------*/

#define RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE                               (IMC_BASE      + 0x005c0000)

#define HWIO_RAM_3_IMEM_HW_ID_ADDR                                       (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000000)
#define HWIO_RAM_3_IMEM_HW_ID_RMSK                                       0xffffffff
#define HWIO_RAM_3_IMEM_HW_ID_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_HW_ID_ADDR, HWIO_RAM_3_IMEM_HW_ID_RMSK)
#define HWIO_RAM_3_IMEM_HW_ID_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_HW_ID_ADDR, m)
#define HWIO_RAM_3_IMEM_HW_ID_MAJOR_BMSK                                 0xff000000
#define HWIO_RAM_3_IMEM_HW_ID_MAJOR_SHFT                                       0x18
#define HWIO_RAM_3_IMEM_HW_ID_MINOR_BMSK                                   0xff0000
#define HWIO_RAM_3_IMEM_HW_ID_MINOR_SHFT                                       0x10
#define HWIO_RAM_3_IMEM_HW_ID_CONFIG_BMSK                                    0xff00
#define HWIO_RAM_3_IMEM_HW_ID_CONFIG_SHFT                                       0x8
#define HWIO_RAM_3_IMEM_HW_ID_INSTANCE_BMSK                                    0xff
#define HWIO_RAM_3_IMEM_HW_ID_INSTANCE_SHFT                                     0x0

#define HWIO_RAM_3_IMEM_HW_VERSION_ADDR                                  (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000004)
#define HWIO_RAM_3_IMEM_HW_VERSION_RMSK                                  0xffffffff
#define HWIO_RAM_3_IMEM_HW_VERSION_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_HW_VERSION_ADDR, HWIO_RAM_3_IMEM_HW_VERSION_RMSK)
#define HWIO_RAM_3_IMEM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_HW_VERSION_ADDR, m)
#define HWIO_RAM_3_IMEM_HW_VERSION_MAJOR_BMSK                            0xff000000
#define HWIO_RAM_3_IMEM_HW_VERSION_MAJOR_SHFT                                  0x18
#define HWIO_RAM_3_IMEM_HW_VERSION_MINOR_BMSK                              0xff0000
#define HWIO_RAM_3_IMEM_HW_VERSION_MINOR_SHFT                                  0x10
#define HWIO_RAM_3_IMEM_HW_VERSION_STEP_BMSK                                 0xffff
#define HWIO_RAM_3_IMEM_HW_VERSION_STEP_SHFT                                    0x0

#define HWIO_RAM_3_IMEM_ERR_STATUS_ADDR                                  (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000008)
#define HWIO_RAM_3_IMEM_ERR_STATUS_RMSK                                       0x3ff
#define HWIO_RAM_3_IMEM_ERR_STATUS_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_STATUS_ADDR, HWIO_RAM_3_IMEM_ERR_STATUS_RMSK)
#define HWIO_RAM_3_IMEM_ERR_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_STATUS_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_BMSK                   0x200
#define HWIO_RAM_3_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_SHFT                     0x9
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_POISON_SCRUB_BMSK                      0x100
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_POISON_SCRUB_SHFT                        0x8
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_UE_SCRUB_BMSK                           0x80
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_UE_SCRUB_SHFT                            0x7
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_CE_SCRUB_BMSK                           0x40
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_CE_SCRUB_SHFT                            0x6
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_POISON_RMW_BMSK                         0x20
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_POISON_RMW_SHFT                          0x5
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_UE_RMW_BMSK                             0x10
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_UE_RMW_SHFT                              0x4
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_CE_RMW_BMSK                              0x8
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_CE_RMW_SHFT                              0x3
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_BMSK                       0x4
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_SHFT                       0x2
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_UE_QSB_RD_BMSK                           0x2
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_UE_QSB_RD_SHFT                           0x1
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_CE_QSB_RD_BMSK                           0x1
#define HWIO_RAM_3_IMEM_ERR_STATUS_ECC_CE_QSB_RD_SHFT                           0x0

#define HWIO_RAM_3_IMEM_ERR_CLR_ADDR                                     (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000000c)
#define HWIO_RAM_3_IMEM_ERR_CLR_RMSK                                          0x3ff
#define HWIO_RAM_3_IMEM_ERR_CLR_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_ERR_CLR_ADDR,v)
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_3_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_3_IMEM_ERR_CTRL_ADDR                                    (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000010)
#define HWIO_RAM_3_IMEM_ERR_CTRL_RMSK                                         0x3ff
#define HWIO_RAM_3_IMEM_ERR_CTRL_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CTRL_ADDR, HWIO_RAM_3_IMEM_ERR_CTRL_RMSK)
#define HWIO_RAM_3_IMEM_ERR_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CTRL_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_ERR_CTRL_ADDR,v)
#define HWIO_RAM_3_IMEM_ERR_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_ERR_CTRL_ADDR,m,v,HWIO_RAM_3_IMEM_ERR_CTRL_IN)
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_BMSK                0x200
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_SHFT                  0x9
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_BMSK                   0x100
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_SHFT                     0x8
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_BMSK                        0x80
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_SHFT                         0x7
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_BMSK                        0x40
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_SHFT                         0x6
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_BMSK                      0x20
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_SHFT                       0x5
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_BMSK                          0x10
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_SHFT                           0x4
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_BMSK                           0x8
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_SHFT                           0x3
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_BMSK                    0x4
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_SHFT                    0x2
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_BMSK                        0x2
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_SHFT                        0x1
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_BMSK                        0x1
#define HWIO_RAM_3_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_SHFT                        0x0

#define HWIO_RAM_3_IMEM_INT0_CTRL_ADDR                                   (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000014)
#define HWIO_RAM_3_IMEM_INT0_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_3_IMEM_INT0_CTRL_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_INT0_CTRL_ADDR, HWIO_RAM_3_IMEM_INT0_CTRL_RMSK)
#define HWIO_RAM_3_IMEM_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_INT0_CTRL_ADDR, m)
#define HWIO_RAM_3_IMEM_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_INT0_CTRL_ADDR,v)
#define HWIO_RAM_3_IMEM_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_INT0_CTRL_ADDR,m,v,HWIO_RAM_3_IMEM_INT0_CTRL_IN)
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_3_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_3_IMEM_INT1_CTRL_ADDR                                   (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000018)
#define HWIO_RAM_3_IMEM_INT1_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_3_IMEM_INT1_CTRL_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_INT1_CTRL_ADDR, HWIO_RAM_3_IMEM_INT1_CTRL_RMSK)
#define HWIO_RAM_3_IMEM_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_INT1_CTRL_ADDR, m)
#define HWIO_RAM_3_IMEM_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_INT1_CTRL_ADDR,v)
#define HWIO_RAM_3_IMEM_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_INT1_CTRL_ADDR,m,v,HWIO_RAM_3_IMEM_INT1_CTRL_IN)
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_3_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_3_IMEM_ERR_INJ_ADDR                                     (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000001c)
#define HWIO_RAM_3_IMEM_ERR_INJ_RMSK                                          0x3ff
#define HWIO_RAM_3_IMEM_ERR_INJ_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_ERR_INJ_ADDR,v)
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_3_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_ADDR                                (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000020)
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_RMSK                                      0x1f
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_CNTL_ADDR, HWIO_RAM_3_IMEM_ERR_CAP_CNTL_RMSK)
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_CNTL_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_ERR_CAP_CNTL_ADDR,v)
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_ERR_CAP_CNTL_ADDR,m,v,HWIO_RAM_3_IMEM_ERR_CAP_CNTL_IN)
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_BMSK                       0x10
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_SHFT                        0x4
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_BMSK                        0x8
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_SHFT                        0x3
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_BMSK                    0x4
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_SHFT                    0x2
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_BMSK                    0x2
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_SHFT                    0x1
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_BMSK                          0x1
#define HWIO_RAM_3_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_SHFT                          0x0

#define HWIO_RAM_3_IMEM_ERR_CAP_0_ADDR                                   (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000024)
#define HWIO_RAM_3_IMEM_ERR_CAP_0_RMSK                                   0xffffffff
#define HWIO_RAM_3_IMEM_ERR_CAP_0_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_0_ADDR, HWIO_RAM_3_IMEM_ERR_CAP_0_RMSK)
#define HWIO_RAM_3_IMEM_ERR_CAP_0_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_0_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_CAP_0_ERR_ADDR_LO_BMSK                       0xffffffff
#define HWIO_RAM_3_IMEM_ERR_CAP_0_ERR_ADDR_LO_SHFT                              0x0

#define HWIO_RAM_3_IMEM_ERR_CAP_1_ADDR                                   (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000028)
#define HWIO_RAM_3_IMEM_ERR_CAP_1_RMSK                                   0xffff0fff
#define HWIO_RAM_3_IMEM_ERR_CAP_1_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_1_ADDR, HWIO_RAM_3_IMEM_ERR_CAP_1_RMSK)
#define HWIO_RAM_3_IMEM_ERR_CAP_1_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_1_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_BMSK                0xff000000
#define HWIO_RAM_3_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_SHFT                      0x18
#define HWIO_RAM_3_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_BMSK                   0xff0000
#define HWIO_RAM_3_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_SHFT                       0x10
#define HWIO_RAM_3_IMEM_ERR_CAP_1_ERR_ADDR_HI_BMSK                            0xfff
#define HWIO_RAM_3_IMEM_ERR_CAP_1_ERR_ADDR_HI_SHFT                              0x0

#define HWIO_RAM_3_IMEM_ERR_CAP_2_ADDR                                   (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000002c)
#define HWIO_RAM_3_IMEM_ERR_CAP_2_RMSK                                   0x1fffffff
#define HWIO_RAM_3_IMEM_ERR_CAP_2_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_2_ADDR, HWIO_RAM_3_IMEM_ERR_CAP_2_RMSK)
#define HWIO_RAM_3_IMEM_ERR_CAP_2_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_2_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_ABURST_BMSK                        0x10000000
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_ABURST_SHFT                              0x1c
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_AWRITE_BMSK                         0x8000000
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_AWRITE_SHFT                              0x1b
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_ALEN_BMSK                           0x7c00000
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_ALEN_SHFT                                0x16
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_BMSK                      0x200000
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_SHFT                          0x15
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_TID_BMSK                             0x1f0000
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_TID_SHFT                                 0x10
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_BID_BMSK                               0xe000
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_BID_SHFT                                  0xd
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_PID_BMSK                               0x1f00
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_PID_SHFT                                  0x8
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_MID_BMSK                                 0xff
#define HWIO_RAM_3_IMEM_ERR_CAP_2_ERR_MID_SHFT                                  0x0

#define HWIO_RAM_3_IMEM_ERR_CAP_3_ADDR                                   (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000030)
#define HWIO_RAM_3_IMEM_ERR_CAP_3_RMSK                                      0x3ffff
#define HWIO_RAM_3_IMEM_ERR_CAP_3_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_3_ADDR, HWIO_RAM_3_IMEM_ERR_CAP_3_RMSK)
#define HWIO_RAM_3_IMEM_ERR_CAP_3_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_3_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_CAP_3_ERR_VMID_BMSK                             0x3fc00
#define HWIO_RAM_3_IMEM_ERR_CAP_3_ERR_VMID_SHFT                                 0xa
#define HWIO_RAM_3_IMEM_ERR_CAP_3_ERR_MSA_BMSK                                0x200
#define HWIO_RAM_3_IMEM_ERR_CAP_3_ERR_MSA_SHFT                                  0x9
#define HWIO_RAM_3_IMEM_ERR_CAP_3_ERR_NSPROT_BMSK                             0x100
#define HWIO_RAM_3_IMEM_ERR_CAP_3_ERR_NSPROT_SHFT                               0x8
#define HWIO_RAM_3_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_BMSK                          0xff
#define HWIO_RAM_3_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_SHFT                           0x0

#define HWIO_RAM_3_IMEM_ERR_CAP_4_ADDR                                   (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000034)
#define HWIO_RAM_3_IMEM_ERR_CAP_4_RMSK                                    0x1ffffff
#define HWIO_RAM_3_IMEM_ERR_CAP_4_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_4_ADDR, HWIO_RAM_3_IMEM_ERR_CAP_4_RMSK)
#define HWIO_RAM_3_IMEM_ERR_CAP_4_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_CAP_4_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_BMSK                      0x1000000
#define HWIO_RAM_3_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_SHFT                           0x18
#define HWIO_RAM_3_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_BMSK                    0xff0000
#define HWIO_RAM_3_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_SHFT                        0x10
#define HWIO_RAM_3_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_BMSK                      0xff00
#define HWIO_RAM_3_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_SHFT                         0x8
#define HWIO_RAM_3_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_BMSK                        0xff
#define HWIO_RAM_3_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_SHFT                         0x0

#define HWIO_RAM_3_IMEM_ERR_COUNT_ADDR                                   (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000074)
#define HWIO_RAM_3_IMEM_ERR_COUNT_RMSK                                   0xffffffff
#define HWIO_RAM_3_IMEM_ERR_COUNT_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_COUNT_ADDR, HWIO_RAM_3_IMEM_ERR_COUNT_RMSK)
#define HWIO_RAM_3_IMEM_ERR_COUNT_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_ERR_COUNT_ADDR, m)
#define HWIO_RAM_3_IMEM_ERR_COUNT_ERR_UE_COUNT_BMSK                      0xffff0000
#define HWIO_RAM_3_IMEM_ERR_COUNT_ERR_UE_COUNT_SHFT                            0x10
#define HWIO_RAM_3_IMEM_ERR_COUNT_ERR_CE_COUNT_BMSK                          0xffff
#define HWIO_RAM_3_IMEM_ERR_COUNT_ERR_CE_COUNT_SHFT                             0x0

#define HWIO_RAM_3_IMEM_SCRUB_STATUS_ADDR                                (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000038)
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_RMSK                                       0x7
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_STATUS_ADDR, HWIO_RAM_3_IMEM_SCRUB_STATUS_RMSK)
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_STATUS_ADDR, m)
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_SCRUB_INPROG_BMSK                          0x4
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_SCRUB_INPROG_SHFT                          0x2
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_WIPE_INPROG_BMSK                           0x2
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_WIPE_INPROG_SHFT                           0x1
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_ADDR_MAX_BMSK                              0x1
#define HWIO_RAM_3_IMEM_SCRUB_STATUS_ADDR_MAX_SHFT                              0x0

#define HWIO_RAM_3_IMEM_SCRUB_CTRL_ADDR                                  (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000003c)
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_RMSK                                  0xfff8ffff
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_CTRL_ADDR, HWIO_RAM_3_IMEM_SCRUB_CTRL_RMSK)
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_CTRL_ADDR, m)
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_SCRUB_CTRL_ADDR,v)
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_SCRUB_CTRL_ADDR,m,v,HWIO_RAM_3_IMEM_SCRUB_CTRL_IN)
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_SCRUB_EN_BMSK                         0x80000000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_SCRUB_EN_SHFT                               0x1f
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_LOAD_ADDR_BMSK                        0x40000000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_LOAD_ADDR_SHFT                              0x1e
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_WRITE_DATA_BMSK                       0x20000000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_WRITE_DATA_SHFT                             0x1d
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_WIPE_DATA_BMSK                        0x10000000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_WIPE_DATA_SHFT                              0x1c
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_BMSK                    0x8000000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_SHFT                         0x1b
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_BMSK                      0x4000000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_SHFT                           0x1a
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_BMSK                    0x2000000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_SHFT                         0x19
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_BMSK                     0x1000000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_SHFT                          0x18
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_NUM_ADDR_BMSK                           0xf80000
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_NUM_ADDR_SHFT                               0x13
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_SCRUB_TIMER_BMSK                          0xffff
#define HWIO_RAM_3_IMEM_SCRUB_CTRL_SCRUB_TIMER_SHFT                             0x0

#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_ADDR                             (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000040)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_RMSK                             0xffffffff
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_ADDR, HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_RMSK)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_ADDR, m)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_ADDR                             (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000044)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_RMSK                                 0xffff
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_ADDR, HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_RMSK)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_ADDR, m)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_ADDR                             (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000048)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_ADDR, HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_RMSK)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_ADDR, m)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_ADDR,v)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_ADDR,m,v,HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_IN)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_ADDR                             (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000004c)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_RMSK                                 0xffff
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_ADDR, HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_RMSK)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_ADDR, m)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_ADDR,v)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_ADDR,m,v,HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_IN)
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_3_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_ADDR                             (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000050)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_ADDR, HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_RMSK)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_ADDR, m)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_ADDR,v)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_ADDR,m,v,HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_IN)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_BMSK              0xffffffff
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_SHFT                     0x0

#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_ADDR                             (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000054)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_RMSK                             0xffffffff
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_ADDR, HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_RMSK)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_ADDR, m)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_ADDR,v)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_ADDR,m,v,HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_IN)
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_BMSK             0xffffffff
#define HWIO_RAM_3_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_SHFT                    0x0

#define HWIO_RAM_3_IMEM_CONFIG_ADDR                                      (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000058)
#define HWIO_RAM_3_IMEM_CONFIG_RMSK                                            0x1f
#define HWIO_RAM_3_IMEM_CONFIG_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_CONFIG_ADDR, HWIO_RAM_3_IMEM_CONFIG_RMSK)
#define HWIO_RAM_3_IMEM_CONFIG_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_CONFIG_ADDR, m)
#define HWIO_RAM_3_IMEM_CONFIG_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_CONFIG_ADDR,v)
#define HWIO_RAM_3_IMEM_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_CONFIG_ADDR,m,v,HWIO_RAM_3_IMEM_CONFIG_IN)
#define HWIO_RAM_3_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_BMSK                        0x10
#define HWIO_RAM_3_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_SHFT                         0x4
#define HWIO_RAM_3_IMEM_CONFIG_ECC_ENABLE_BMSK                                  0x8
#define HWIO_RAM_3_IMEM_CONFIG_ECC_ENABLE_SHFT                                  0x3
#define HWIO_RAM_3_IMEM_CONFIG_ECC_ENABLE_WR_BMSK                               0x4
#define HWIO_RAM_3_IMEM_CONFIG_ECC_ENABLE_WR_SHFT                               0x2
#define HWIO_RAM_3_IMEM_CONFIG_ECC_ENABLE_RD_BMSK                               0x2
#define HWIO_RAM_3_IMEM_CONFIG_ECC_ENABLE_RD_SHFT                               0x1
#define HWIO_RAM_3_IMEM_CONFIG_ECC_RD_RMW_EN_BMSK                               0x1
#define HWIO_RAM_3_IMEM_CONFIG_ECC_RD_RMW_EN_SHFT                               0x0

#define HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_ADDR                        (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000005c)
#define HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_RMSK                        0xffffffff
#define HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_RMSK)
#define HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, m)
#define HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,v)
#define HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,m,v,HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_IN)
#define HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_BMSK              0xffffffff
#define HWIO_RAM_3_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_SHFT                     0x0

#define HWIO_RAM_3_IMEM_CLK_ON_CFG_ADDR                                  (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000064)
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_RMSK                                       0xfff
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_CLK_ON_CFG_ADDR, HWIO_RAM_3_IMEM_CLK_ON_CFG_RMSK)
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_CLK_ON_CFG_ADDR, m)
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_CLK_ON_CFG_ADDR,v)
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_CLK_ON_CFG_ADDR,m,v,HWIO_RAM_3_IMEM_CLK_ON_CFG_IN)
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_CLK_ON_TIME_BMSK                           0xffc
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_CLK_ON_TIME_SHFT                             0x2
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_BMSK                           0x2
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_SHFT                           0x1
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_CLK_ON_EN_BMSK                               0x1
#define HWIO_RAM_3_IMEM_CLK_ON_CFG_CLK_ON_EN_SHFT                               0x0

#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_ADDR                               (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000006c)
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_RMSK                                     0xff
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_PSBCGC_TIMERS_ADDR, HWIO_RAM_3_IMEM_PSBCGC_TIMERS_RMSK)
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_PSBCGC_TIMERS_ADDR, m)
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_PSBCGC_TIMERS_ADDR,v)
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_PSBCGC_TIMERS_ADDR,m,v,HWIO_RAM_3_IMEM_PSBCGC_TIMERS_IN)
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_BMSK                      0xf0
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_SHFT                       0x4
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_BMSK                     0xf
#define HWIO_RAM_3_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_SHFT                     0x0

#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_ADDR                              (RAM_3_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000070)
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_RMSK                              0x3fffffff
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_IN          \
        in_dword_masked(HWIO_RAM_3_IMEM_PSBCGC_CONTROL_ADDR, HWIO_RAM_3_IMEM_PSBCGC_CONTROL_RMSK)
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_RAM_3_IMEM_PSBCGC_CONTROL_ADDR, m)
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_OUT(v)      \
        out_dword(HWIO_RAM_3_IMEM_PSBCGC_CONTROL_ADDR,v)
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_3_IMEM_PSBCGC_CONTROL_ADDR,m,v,HWIO_RAM_3_IMEM_PSBCGC_CONTROL_IN)
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_HALT_CLOCK_BMSK                   0x3ff00000
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_HALT_CLOCK_SHFT                         0x14
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_CORE_ON_BMSK                         0xffc00
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_CORE_ON_SHFT                             0xa
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_PERIF_ON_BMSK                          0x3ff
#define HWIO_RAM_3_IMEM_PSBCGC_CONTROL_PERIF_ON_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: RAM_4_IMEM_IMEM_IMEM_CSRS
 *--------------------------------------------------------------------------*/

#define RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE                               (IMC_BASE      + 0x00600000)

#define HWIO_RAM_4_IMEM_HW_ID_ADDR                                       (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000000)
#define HWIO_RAM_4_IMEM_HW_ID_RMSK                                       0xffffffff
#define HWIO_RAM_4_IMEM_HW_ID_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_HW_ID_ADDR, HWIO_RAM_4_IMEM_HW_ID_RMSK)
#define HWIO_RAM_4_IMEM_HW_ID_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_HW_ID_ADDR, m)
#define HWIO_RAM_4_IMEM_HW_ID_MAJOR_BMSK                                 0xff000000
#define HWIO_RAM_4_IMEM_HW_ID_MAJOR_SHFT                                       0x18
#define HWIO_RAM_4_IMEM_HW_ID_MINOR_BMSK                                   0xff0000
#define HWIO_RAM_4_IMEM_HW_ID_MINOR_SHFT                                       0x10
#define HWIO_RAM_4_IMEM_HW_ID_CONFIG_BMSK                                    0xff00
#define HWIO_RAM_4_IMEM_HW_ID_CONFIG_SHFT                                       0x8
#define HWIO_RAM_4_IMEM_HW_ID_INSTANCE_BMSK                                    0xff
#define HWIO_RAM_4_IMEM_HW_ID_INSTANCE_SHFT                                     0x0

#define HWIO_RAM_4_IMEM_HW_VERSION_ADDR                                  (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000004)
#define HWIO_RAM_4_IMEM_HW_VERSION_RMSK                                  0xffffffff
#define HWIO_RAM_4_IMEM_HW_VERSION_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_HW_VERSION_ADDR, HWIO_RAM_4_IMEM_HW_VERSION_RMSK)
#define HWIO_RAM_4_IMEM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_HW_VERSION_ADDR, m)
#define HWIO_RAM_4_IMEM_HW_VERSION_MAJOR_BMSK                            0xff000000
#define HWIO_RAM_4_IMEM_HW_VERSION_MAJOR_SHFT                                  0x18
#define HWIO_RAM_4_IMEM_HW_VERSION_MINOR_BMSK                              0xff0000
#define HWIO_RAM_4_IMEM_HW_VERSION_MINOR_SHFT                                  0x10
#define HWIO_RAM_4_IMEM_HW_VERSION_STEP_BMSK                                 0xffff
#define HWIO_RAM_4_IMEM_HW_VERSION_STEP_SHFT                                    0x0

#define HWIO_RAM_4_IMEM_ERR_STATUS_ADDR                                  (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000008)
#define HWIO_RAM_4_IMEM_ERR_STATUS_RMSK                                       0x3ff
#define HWIO_RAM_4_IMEM_ERR_STATUS_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_STATUS_ADDR, HWIO_RAM_4_IMEM_ERR_STATUS_RMSK)
#define HWIO_RAM_4_IMEM_ERR_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_STATUS_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_BMSK                   0x200
#define HWIO_RAM_4_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_SHFT                     0x9
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_POISON_SCRUB_BMSK                      0x100
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_POISON_SCRUB_SHFT                        0x8
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_UE_SCRUB_BMSK                           0x80
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_UE_SCRUB_SHFT                            0x7
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_CE_SCRUB_BMSK                           0x40
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_CE_SCRUB_SHFT                            0x6
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_POISON_RMW_BMSK                         0x20
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_POISON_RMW_SHFT                          0x5
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_UE_RMW_BMSK                             0x10
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_UE_RMW_SHFT                              0x4
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_CE_RMW_BMSK                              0x8
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_CE_RMW_SHFT                              0x3
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_BMSK                       0x4
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_SHFT                       0x2
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_UE_QSB_RD_BMSK                           0x2
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_UE_QSB_RD_SHFT                           0x1
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_CE_QSB_RD_BMSK                           0x1
#define HWIO_RAM_4_IMEM_ERR_STATUS_ECC_CE_QSB_RD_SHFT                           0x0

#define HWIO_RAM_4_IMEM_ERR_CLR_ADDR                                     (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000000c)
#define HWIO_RAM_4_IMEM_ERR_CLR_RMSK                                          0x3ff
#define HWIO_RAM_4_IMEM_ERR_CLR_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_ERR_CLR_ADDR,v)
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_4_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_4_IMEM_ERR_CTRL_ADDR                                    (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000010)
#define HWIO_RAM_4_IMEM_ERR_CTRL_RMSK                                         0x3ff
#define HWIO_RAM_4_IMEM_ERR_CTRL_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CTRL_ADDR, HWIO_RAM_4_IMEM_ERR_CTRL_RMSK)
#define HWIO_RAM_4_IMEM_ERR_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CTRL_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_ERR_CTRL_ADDR,v)
#define HWIO_RAM_4_IMEM_ERR_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_ERR_CTRL_ADDR,m,v,HWIO_RAM_4_IMEM_ERR_CTRL_IN)
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_BMSK                0x200
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_SHFT                  0x9
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_BMSK                   0x100
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_SHFT                     0x8
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_BMSK                        0x80
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_SHFT                         0x7
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_BMSK                        0x40
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_SHFT                         0x6
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_BMSK                      0x20
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_SHFT                       0x5
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_BMSK                          0x10
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_SHFT                           0x4
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_BMSK                           0x8
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_SHFT                           0x3
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_BMSK                    0x4
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_SHFT                    0x2
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_BMSK                        0x2
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_SHFT                        0x1
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_BMSK                        0x1
#define HWIO_RAM_4_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_SHFT                        0x0

#define HWIO_RAM_4_IMEM_INT0_CTRL_ADDR                                   (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000014)
#define HWIO_RAM_4_IMEM_INT0_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_4_IMEM_INT0_CTRL_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_INT0_CTRL_ADDR, HWIO_RAM_4_IMEM_INT0_CTRL_RMSK)
#define HWIO_RAM_4_IMEM_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_INT0_CTRL_ADDR, m)
#define HWIO_RAM_4_IMEM_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_INT0_CTRL_ADDR,v)
#define HWIO_RAM_4_IMEM_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_INT0_CTRL_ADDR,m,v,HWIO_RAM_4_IMEM_INT0_CTRL_IN)
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_4_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_4_IMEM_INT1_CTRL_ADDR                                   (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000018)
#define HWIO_RAM_4_IMEM_INT1_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_4_IMEM_INT1_CTRL_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_INT1_CTRL_ADDR, HWIO_RAM_4_IMEM_INT1_CTRL_RMSK)
#define HWIO_RAM_4_IMEM_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_INT1_CTRL_ADDR, m)
#define HWIO_RAM_4_IMEM_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_INT1_CTRL_ADDR,v)
#define HWIO_RAM_4_IMEM_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_INT1_CTRL_ADDR,m,v,HWIO_RAM_4_IMEM_INT1_CTRL_IN)
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_4_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_4_IMEM_ERR_INJ_ADDR                                     (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000001c)
#define HWIO_RAM_4_IMEM_ERR_INJ_RMSK                                          0x3ff
#define HWIO_RAM_4_IMEM_ERR_INJ_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_ERR_INJ_ADDR,v)
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_4_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_ADDR                                (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000020)
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_RMSK                                      0x1f
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_CNTL_ADDR, HWIO_RAM_4_IMEM_ERR_CAP_CNTL_RMSK)
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_CNTL_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_ERR_CAP_CNTL_ADDR,v)
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_ERR_CAP_CNTL_ADDR,m,v,HWIO_RAM_4_IMEM_ERR_CAP_CNTL_IN)
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_BMSK                       0x10
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_SHFT                        0x4
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_BMSK                        0x8
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_SHFT                        0x3
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_BMSK                    0x4
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_SHFT                    0x2
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_BMSK                    0x2
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_SHFT                    0x1
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_BMSK                          0x1
#define HWIO_RAM_4_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_SHFT                          0x0

#define HWIO_RAM_4_IMEM_ERR_CAP_0_ADDR                                   (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000024)
#define HWIO_RAM_4_IMEM_ERR_CAP_0_RMSK                                   0xffffffff
#define HWIO_RAM_4_IMEM_ERR_CAP_0_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_0_ADDR, HWIO_RAM_4_IMEM_ERR_CAP_0_RMSK)
#define HWIO_RAM_4_IMEM_ERR_CAP_0_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_0_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_CAP_0_ERR_ADDR_LO_BMSK                       0xffffffff
#define HWIO_RAM_4_IMEM_ERR_CAP_0_ERR_ADDR_LO_SHFT                              0x0

#define HWIO_RAM_4_IMEM_ERR_CAP_1_ADDR                                   (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000028)
#define HWIO_RAM_4_IMEM_ERR_CAP_1_RMSK                                   0xffff0fff
#define HWIO_RAM_4_IMEM_ERR_CAP_1_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_1_ADDR, HWIO_RAM_4_IMEM_ERR_CAP_1_RMSK)
#define HWIO_RAM_4_IMEM_ERR_CAP_1_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_1_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_BMSK                0xff000000
#define HWIO_RAM_4_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_SHFT                      0x18
#define HWIO_RAM_4_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_BMSK                   0xff0000
#define HWIO_RAM_4_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_SHFT                       0x10
#define HWIO_RAM_4_IMEM_ERR_CAP_1_ERR_ADDR_HI_BMSK                            0xfff
#define HWIO_RAM_4_IMEM_ERR_CAP_1_ERR_ADDR_HI_SHFT                              0x0

#define HWIO_RAM_4_IMEM_ERR_CAP_2_ADDR                                   (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000002c)
#define HWIO_RAM_4_IMEM_ERR_CAP_2_RMSK                                   0x1fffffff
#define HWIO_RAM_4_IMEM_ERR_CAP_2_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_2_ADDR, HWIO_RAM_4_IMEM_ERR_CAP_2_RMSK)
#define HWIO_RAM_4_IMEM_ERR_CAP_2_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_2_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_ABURST_BMSK                        0x10000000
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_ABURST_SHFT                              0x1c
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_AWRITE_BMSK                         0x8000000
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_AWRITE_SHFT                              0x1b
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_ALEN_BMSK                           0x7c00000
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_ALEN_SHFT                                0x16
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_BMSK                      0x200000
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_SHFT                          0x15
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_TID_BMSK                             0x1f0000
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_TID_SHFT                                 0x10
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_BID_BMSK                               0xe000
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_BID_SHFT                                  0xd
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_PID_BMSK                               0x1f00
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_PID_SHFT                                  0x8
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_MID_BMSK                                 0xff
#define HWIO_RAM_4_IMEM_ERR_CAP_2_ERR_MID_SHFT                                  0x0

#define HWIO_RAM_4_IMEM_ERR_CAP_3_ADDR                                   (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000030)
#define HWIO_RAM_4_IMEM_ERR_CAP_3_RMSK                                      0x3ffff
#define HWIO_RAM_4_IMEM_ERR_CAP_3_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_3_ADDR, HWIO_RAM_4_IMEM_ERR_CAP_3_RMSK)
#define HWIO_RAM_4_IMEM_ERR_CAP_3_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_3_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_CAP_3_ERR_VMID_BMSK                             0x3fc00
#define HWIO_RAM_4_IMEM_ERR_CAP_3_ERR_VMID_SHFT                                 0xa
#define HWIO_RAM_4_IMEM_ERR_CAP_3_ERR_MSA_BMSK                                0x200
#define HWIO_RAM_4_IMEM_ERR_CAP_3_ERR_MSA_SHFT                                  0x9
#define HWIO_RAM_4_IMEM_ERR_CAP_3_ERR_NSPROT_BMSK                             0x100
#define HWIO_RAM_4_IMEM_ERR_CAP_3_ERR_NSPROT_SHFT                               0x8
#define HWIO_RAM_4_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_BMSK                          0xff
#define HWIO_RAM_4_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_SHFT                           0x0

#define HWIO_RAM_4_IMEM_ERR_CAP_4_ADDR                                   (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000034)
#define HWIO_RAM_4_IMEM_ERR_CAP_4_RMSK                                    0x1ffffff
#define HWIO_RAM_4_IMEM_ERR_CAP_4_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_4_ADDR, HWIO_RAM_4_IMEM_ERR_CAP_4_RMSK)
#define HWIO_RAM_4_IMEM_ERR_CAP_4_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_CAP_4_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_BMSK                      0x1000000
#define HWIO_RAM_4_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_SHFT                           0x18
#define HWIO_RAM_4_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_BMSK                    0xff0000
#define HWIO_RAM_4_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_SHFT                        0x10
#define HWIO_RAM_4_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_BMSK                      0xff00
#define HWIO_RAM_4_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_SHFT                         0x8
#define HWIO_RAM_4_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_BMSK                        0xff
#define HWIO_RAM_4_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_SHFT                         0x0

#define HWIO_RAM_4_IMEM_ERR_COUNT_ADDR                                   (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000074)
#define HWIO_RAM_4_IMEM_ERR_COUNT_RMSK                                   0xffffffff
#define HWIO_RAM_4_IMEM_ERR_COUNT_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_COUNT_ADDR, HWIO_RAM_4_IMEM_ERR_COUNT_RMSK)
#define HWIO_RAM_4_IMEM_ERR_COUNT_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_ERR_COUNT_ADDR, m)
#define HWIO_RAM_4_IMEM_ERR_COUNT_ERR_UE_COUNT_BMSK                      0xffff0000
#define HWIO_RAM_4_IMEM_ERR_COUNT_ERR_UE_COUNT_SHFT                            0x10
#define HWIO_RAM_4_IMEM_ERR_COUNT_ERR_CE_COUNT_BMSK                          0xffff
#define HWIO_RAM_4_IMEM_ERR_COUNT_ERR_CE_COUNT_SHFT                             0x0

#define HWIO_RAM_4_IMEM_SCRUB_STATUS_ADDR                                (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000038)
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_RMSK                                       0x7
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_STATUS_ADDR, HWIO_RAM_4_IMEM_SCRUB_STATUS_RMSK)
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_STATUS_ADDR, m)
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_SCRUB_INPROG_BMSK                          0x4
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_SCRUB_INPROG_SHFT                          0x2
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_WIPE_INPROG_BMSK                           0x2
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_WIPE_INPROG_SHFT                           0x1
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_ADDR_MAX_BMSK                              0x1
#define HWIO_RAM_4_IMEM_SCRUB_STATUS_ADDR_MAX_SHFT                              0x0

#define HWIO_RAM_4_IMEM_SCRUB_CTRL_ADDR                                  (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000003c)
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_RMSK                                  0xfff8ffff
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_CTRL_ADDR, HWIO_RAM_4_IMEM_SCRUB_CTRL_RMSK)
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_CTRL_ADDR, m)
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_SCRUB_CTRL_ADDR,v)
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_SCRUB_CTRL_ADDR,m,v,HWIO_RAM_4_IMEM_SCRUB_CTRL_IN)
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_SCRUB_EN_BMSK                         0x80000000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_SCRUB_EN_SHFT                               0x1f
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_LOAD_ADDR_BMSK                        0x40000000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_LOAD_ADDR_SHFT                              0x1e
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_WRITE_DATA_BMSK                       0x20000000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_WRITE_DATA_SHFT                             0x1d
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_WIPE_DATA_BMSK                        0x10000000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_WIPE_DATA_SHFT                              0x1c
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_BMSK                    0x8000000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_SHFT                         0x1b
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_BMSK                      0x4000000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_SHFT                           0x1a
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_BMSK                    0x2000000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_SHFT                         0x19
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_BMSK                     0x1000000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_SHFT                          0x18
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_NUM_ADDR_BMSK                           0xf80000
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_NUM_ADDR_SHFT                               0x13
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_SCRUB_TIMER_BMSK                          0xffff
#define HWIO_RAM_4_IMEM_SCRUB_CTRL_SCRUB_TIMER_SHFT                             0x0

#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_ADDR                             (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000040)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_RMSK                             0xffffffff
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_ADDR, HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_RMSK)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_ADDR, m)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_ADDR                             (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000044)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_RMSK                                 0xffff
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_ADDR, HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_RMSK)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_ADDR, m)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_ADDR                             (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000048)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_ADDR, HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_RMSK)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_ADDR, m)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_ADDR,v)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_ADDR,m,v,HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_IN)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_ADDR                             (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000004c)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_RMSK                                 0xffff
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_ADDR, HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_RMSK)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_ADDR, m)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_ADDR,v)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_ADDR,m,v,HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_IN)
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_4_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_ADDR                             (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000050)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_ADDR, HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_RMSK)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_ADDR, m)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_ADDR,v)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_ADDR,m,v,HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_IN)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_BMSK              0xffffffff
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_SHFT                     0x0

#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_ADDR                             (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000054)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_RMSK                             0xffffffff
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_ADDR, HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_RMSK)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_ADDR, m)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_ADDR,v)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_ADDR,m,v,HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_IN)
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_BMSK             0xffffffff
#define HWIO_RAM_4_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_SHFT                    0x0

#define HWIO_RAM_4_IMEM_CONFIG_ADDR                                      (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000058)
#define HWIO_RAM_4_IMEM_CONFIG_RMSK                                            0x1f
#define HWIO_RAM_4_IMEM_CONFIG_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_CONFIG_ADDR, HWIO_RAM_4_IMEM_CONFIG_RMSK)
#define HWIO_RAM_4_IMEM_CONFIG_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_CONFIG_ADDR, m)
#define HWIO_RAM_4_IMEM_CONFIG_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_CONFIG_ADDR,v)
#define HWIO_RAM_4_IMEM_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_CONFIG_ADDR,m,v,HWIO_RAM_4_IMEM_CONFIG_IN)
#define HWIO_RAM_4_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_BMSK                        0x10
#define HWIO_RAM_4_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_SHFT                         0x4
#define HWIO_RAM_4_IMEM_CONFIG_ECC_ENABLE_BMSK                                  0x8
#define HWIO_RAM_4_IMEM_CONFIG_ECC_ENABLE_SHFT                                  0x3
#define HWIO_RAM_4_IMEM_CONFIG_ECC_ENABLE_WR_BMSK                               0x4
#define HWIO_RAM_4_IMEM_CONFIG_ECC_ENABLE_WR_SHFT                               0x2
#define HWIO_RAM_4_IMEM_CONFIG_ECC_ENABLE_RD_BMSK                               0x2
#define HWIO_RAM_4_IMEM_CONFIG_ECC_ENABLE_RD_SHFT                               0x1
#define HWIO_RAM_4_IMEM_CONFIG_ECC_RD_RMW_EN_BMSK                               0x1
#define HWIO_RAM_4_IMEM_CONFIG_ECC_RD_RMW_EN_SHFT                               0x0

#define HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_ADDR                        (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000005c)
#define HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_RMSK                        0xffffffff
#define HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_RMSK)
#define HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, m)
#define HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,v)
#define HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,m,v,HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_IN)
#define HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_BMSK              0xffffffff
#define HWIO_RAM_4_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_SHFT                     0x0

#define HWIO_RAM_4_IMEM_CLK_ON_CFG_ADDR                                  (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000064)
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_RMSK                                       0xfff
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_CLK_ON_CFG_ADDR, HWIO_RAM_4_IMEM_CLK_ON_CFG_RMSK)
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_CLK_ON_CFG_ADDR, m)
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_CLK_ON_CFG_ADDR,v)
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_CLK_ON_CFG_ADDR,m,v,HWIO_RAM_4_IMEM_CLK_ON_CFG_IN)
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_CLK_ON_TIME_BMSK                           0xffc
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_CLK_ON_TIME_SHFT                             0x2
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_BMSK                           0x2
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_SHFT                           0x1
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_CLK_ON_EN_BMSK                               0x1
#define HWIO_RAM_4_IMEM_CLK_ON_CFG_CLK_ON_EN_SHFT                               0x0

#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_ADDR                               (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000006c)
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_RMSK                                     0xff
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_PSBCGC_TIMERS_ADDR, HWIO_RAM_4_IMEM_PSBCGC_TIMERS_RMSK)
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_PSBCGC_TIMERS_ADDR, m)
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_PSBCGC_TIMERS_ADDR,v)
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_PSBCGC_TIMERS_ADDR,m,v,HWIO_RAM_4_IMEM_PSBCGC_TIMERS_IN)
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_BMSK                      0xf0
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_SHFT                       0x4
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_BMSK                     0xf
#define HWIO_RAM_4_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_SHFT                     0x0

#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_ADDR                              (RAM_4_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000070)
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_RMSK                              0x3fffffff
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_IN          \
        in_dword_masked(HWIO_RAM_4_IMEM_PSBCGC_CONTROL_ADDR, HWIO_RAM_4_IMEM_PSBCGC_CONTROL_RMSK)
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_RAM_4_IMEM_PSBCGC_CONTROL_ADDR, m)
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_OUT(v)      \
        out_dword(HWIO_RAM_4_IMEM_PSBCGC_CONTROL_ADDR,v)
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_4_IMEM_PSBCGC_CONTROL_ADDR,m,v,HWIO_RAM_4_IMEM_PSBCGC_CONTROL_IN)
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_HALT_CLOCK_BMSK                   0x3ff00000
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_HALT_CLOCK_SHFT                         0x14
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_CORE_ON_BMSK                         0xffc00
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_CORE_ON_SHFT                             0xa
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_PERIF_ON_BMSK                          0x3ff
#define HWIO_RAM_4_IMEM_PSBCGC_CONTROL_PERIF_ON_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: RAM_5_IMEM_IMEM_IMEM_CSRS
 *--------------------------------------------------------------------------*/

#define RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE                               (IMC_BASE      + 0x00640000)

#define HWIO_RAM_5_IMEM_HW_ID_ADDR                                       (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000000)
#define HWIO_RAM_5_IMEM_HW_ID_RMSK                                       0xffffffff
#define HWIO_RAM_5_IMEM_HW_ID_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_HW_ID_ADDR, HWIO_RAM_5_IMEM_HW_ID_RMSK)
#define HWIO_RAM_5_IMEM_HW_ID_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_HW_ID_ADDR, m)
#define HWIO_RAM_5_IMEM_HW_ID_MAJOR_BMSK                                 0xff000000
#define HWIO_RAM_5_IMEM_HW_ID_MAJOR_SHFT                                       0x18
#define HWIO_RAM_5_IMEM_HW_ID_MINOR_BMSK                                   0xff0000
#define HWIO_RAM_5_IMEM_HW_ID_MINOR_SHFT                                       0x10
#define HWIO_RAM_5_IMEM_HW_ID_CONFIG_BMSK                                    0xff00
#define HWIO_RAM_5_IMEM_HW_ID_CONFIG_SHFT                                       0x8
#define HWIO_RAM_5_IMEM_HW_ID_INSTANCE_BMSK                                    0xff
#define HWIO_RAM_5_IMEM_HW_ID_INSTANCE_SHFT                                     0x0

#define HWIO_RAM_5_IMEM_HW_VERSION_ADDR                                  (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000004)
#define HWIO_RAM_5_IMEM_HW_VERSION_RMSK                                  0xffffffff
#define HWIO_RAM_5_IMEM_HW_VERSION_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_HW_VERSION_ADDR, HWIO_RAM_5_IMEM_HW_VERSION_RMSK)
#define HWIO_RAM_5_IMEM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_HW_VERSION_ADDR, m)
#define HWIO_RAM_5_IMEM_HW_VERSION_MAJOR_BMSK                            0xff000000
#define HWIO_RAM_5_IMEM_HW_VERSION_MAJOR_SHFT                                  0x18
#define HWIO_RAM_5_IMEM_HW_VERSION_MINOR_BMSK                              0xff0000
#define HWIO_RAM_5_IMEM_HW_VERSION_MINOR_SHFT                                  0x10
#define HWIO_RAM_5_IMEM_HW_VERSION_STEP_BMSK                                 0xffff
#define HWIO_RAM_5_IMEM_HW_VERSION_STEP_SHFT                                    0x0

#define HWIO_RAM_5_IMEM_ERR_STATUS_ADDR                                  (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000008)
#define HWIO_RAM_5_IMEM_ERR_STATUS_RMSK                                       0x3ff
#define HWIO_RAM_5_IMEM_ERR_STATUS_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_STATUS_ADDR, HWIO_RAM_5_IMEM_ERR_STATUS_RMSK)
#define HWIO_RAM_5_IMEM_ERR_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_STATUS_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_BMSK                   0x200
#define HWIO_RAM_5_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_SHFT                     0x9
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_POISON_SCRUB_BMSK                      0x100
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_POISON_SCRUB_SHFT                        0x8
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_UE_SCRUB_BMSK                           0x80
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_UE_SCRUB_SHFT                            0x7
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_CE_SCRUB_BMSK                           0x40
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_CE_SCRUB_SHFT                            0x6
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_POISON_RMW_BMSK                         0x20
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_POISON_RMW_SHFT                          0x5
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_UE_RMW_BMSK                             0x10
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_UE_RMW_SHFT                              0x4
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_CE_RMW_BMSK                              0x8
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_CE_RMW_SHFT                              0x3
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_BMSK                       0x4
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_SHFT                       0x2
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_UE_QSB_RD_BMSK                           0x2
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_UE_QSB_RD_SHFT                           0x1
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_CE_QSB_RD_BMSK                           0x1
#define HWIO_RAM_5_IMEM_ERR_STATUS_ECC_CE_QSB_RD_SHFT                           0x0

#define HWIO_RAM_5_IMEM_ERR_CLR_ADDR                                     (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000000c)
#define HWIO_RAM_5_IMEM_ERR_CLR_RMSK                                          0x3ff
#define HWIO_RAM_5_IMEM_ERR_CLR_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_ERR_CLR_ADDR,v)
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_5_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_5_IMEM_ERR_CTRL_ADDR                                    (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000010)
#define HWIO_RAM_5_IMEM_ERR_CTRL_RMSK                                         0x3ff
#define HWIO_RAM_5_IMEM_ERR_CTRL_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CTRL_ADDR, HWIO_RAM_5_IMEM_ERR_CTRL_RMSK)
#define HWIO_RAM_5_IMEM_ERR_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CTRL_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_ERR_CTRL_ADDR,v)
#define HWIO_RAM_5_IMEM_ERR_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_ERR_CTRL_ADDR,m,v,HWIO_RAM_5_IMEM_ERR_CTRL_IN)
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_BMSK                0x200
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_SHFT                  0x9
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_BMSK                   0x100
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_SHFT                     0x8
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_BMSK                        0x80
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_SHFT                         0x7
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_BMSK                        0x40
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_SHFT                         0x6
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_BMSK                      0x20
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_SHFT                       0x5
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_BMSK                          0x10
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_SHFT                           0x4
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_BMSK                           0x8
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_SHFT                           0x3
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_BMSK                    0x4
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_SHFT                    0x2
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_BMSK                        0x2
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_SHFT                        0x1
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_BMSK                        0x1
#define HWIO_RAM_5_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_SHFT                        0x0

#define HWIO_RAM_5_IMEM_INT0_CTRL_ADDR                                   (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000014)
#define HWIO_RAM_5_IMEM_INT0_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_5_IMEM_INT0_CTRL_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_INT0_CTRL_ADDR, HWIO_RAM_5_IMEM_INT0_CTRL_RMSK)
#define HWIO_RAM_5_IMEM_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_INT0_CTRL_ADDR, m)
#define HWIO_RAM_5_IMEM_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_INT0_CTRL_ADDR,v)
#define HWIO_RAM_5_IMEM_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_INT0_CTRL_ADDR,m,v,HWIO_RAM_5_IMEM_INT0_CTRL_IN)
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_5_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_5_IMEM_INT1_CTRL_ADDR                                   (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000018)
#define HWIO_RAM_5_IMEM_INT1_CTRL_RMSK                                        0x3ff
#define HWIO_RAM_5_IMEM_INT1_CTRL_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_INT1_CTRL_ADDR, HWIO_RAM_5_IMEM_INT1_CTRL_RMSK)
#define HWIO_RAM_5_IMEM_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_INT1_CTRL_ADDR, m)
#define HWIO_RAM_5_IMEM_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_INT1_CTRL_ADDR,v)
#define HWIO_RAM_5_IMEM_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_INT1_CTRL_ADDR,m,v,HWIO_RAM_5_IMEM_INT1_CTRL_IN)
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_BMSK                         0x10
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_SHFT                          0x4
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_BMSK                          0x8
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_SHFT                          0x3
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_RAM_5_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_RAM_5_IMEM_ERR_INJ_ADDR                                     (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000001c)
#define HWIO_RAM_5_IMEM_ERR_INJ_RMSK                                          0x3ff
#define HWIO_RAM_5_IMEM_ERR_INJ_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_ERR_INJ_ADDR,v)
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_UE_RMW_BMSK                            0x10
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_UE_RMW_SHFT                             0x4
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_CE_RMW_BMSK                             0x8
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_CE_RMW_SHFT                             0x3
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_RAM_5_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_ADDR                                (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000020)
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_RMSK                                      0x1f
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_CNTL_ADDR, HWIO_RAM_5_IMEM_ERR_CAP_CNTL_RMSK)
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_CNTL_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_ERR_CAP_CNTL_ADDR,v)
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_ERR_CAP_CNTL_ADDR,m,v,HWIO_RAM_5_IMEM_ERR_CAP_CNTL_IN)
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_BMSK                       0x10
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_SHFT                        0x4
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_BMSK                        0x8
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_SHFT                        0x3
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_BMSK                    0x4
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_SHFT                    0x2
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_BMSK                    0x2
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_SHFT                    0x1
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_BMSK                          0x1
#define HWIO_RAM_5_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_SHFT                          0x0

#define HWIO_RAM_5_IMEM_ERR_CAP_0_ADDR                                   (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000024)
#define HWIO_RAM_5_IMEM_ERR_CAP_0_RMSK                                   0xffffffff
#define HWIO_RAM_5_IMEM_ERR_CAP_0_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_0_ADDR, HWIO_RAM_5_IMEM_ERR_CAP_0_RMSK)
#define HWIO_RAM_5_IMEM_ERR_CAP_0_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_0_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_CAP_0_ERR_ADDR_LO_BMSK                       0xffffffff
#define HWIO_RAM_5_IMEM_ERR_CAP_0_ERR_ADDR_LO_SHFT                              0x0

#define HWIO_RAM_5_IMEM_ERR_CAP_1_ADDR                                   (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000028)
#define HWIO_RAM_5_IMEM_ERR_CAP_1_RMSK                                   0xffff0fff
#define HWIO_RAM_5_IMEM_ERR_CAP_1_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_1_ADDR, HWIO_RAM_5_IMEM_ERR_CAP_1_RMSK)
#define HWIO_RAM_5_IMEM_ERR_CAP_1_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_1_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_BMSK                0xff000000
#define HWIO_RAM_5_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_SHFT                      0x18
#define HWIO_RAM_5_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_BMSK                   0xff0000
#define HWIO_RAM_5_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_SHFT                       0x10
#define HWIO_RAM_5_IMEM_ERR_CAP_1_ERR_ADDR_HI_BMSK                            0xfff
#define HWIO_RAM_5_IMEM_ERR_CAP_1_ERR_ADDR_HI_SHFT                              0x0

#define HWIO_RAM_5_IMEM_ERR_CAP_2_ADDR                                   (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000002c)
#define HWIO_RAM_5_IMEM_ERR_CAP_2_RMSK                                   0x1fffffff
#define HWIO_RAM_5_IMEM_ERR_CAP_2_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_2_ADDR, HWIO_RAM_5_IMEM_ERR_CAP_2_RMSK)
#define HWIO_RAM_5_IMEM_ERR_CAP_2_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_2_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_ABURST_BMSK                        0x10000000
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_ABURST_SHFT                              0x1c
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_AWRITE_BMSK                         0x8000000
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_AWRITE_SHFT                              0x1b
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_ALEN_BMSK                           0x7c00000
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_ALEN_SHFT                                0x16
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_BMSK                      0x200000
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_SHFT                          0x15
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_TID_BMSK                             0x1f0000
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_TID_SHFT                                 0x10
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_BID_BMSK                               0xe000
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_BID_SHFT                                  0xd
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_PID_BMSK                               0x1f00
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_PID_SHFT                                  0x8
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_MID_BMSK                                 0xff
#define HWIO_RAM_5_IMEM_ERR_CAP_2_ERR_MID_SHFT                                  0x0

#define HWIO_RAM_5_IMEM_ERR_CAP_3_ADDR                                   (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000030)
#define HWIO_RAM_5_IMEM_ERR_CAP_3_RMSK                                      0x3ffff
#define HWIO_RAM_5_IMEM_ERR_CAP_3_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_3_ADDR, HWIO_RAM_5_IMEM_ERR_CAP_3_RMSK)
#define HWIO_RAM_5_IMEM_ERR_CAP_3_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_3_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_CAP_3_ERR_VMID_BMSK                             0x3fc00
#define HWIO_RAM_5_IMEM_ERR_CAP_3_ERR_VMID_SHFT                                 0xa
#define HWIO_RAM_5_IMEM_ERR_CAP_3_ERR_MSA_BMSK                                0x200
#define HWIO_RAM_5_IMEM_ERR_CAP_3_ERR_MSA_SHFT                                  0x9
#define HWIO_RAM_5_IMEM_ERR_CAP_3_ERR_NSPROT_BMSK                             0x100
#define HWIO_RAM_5_IMEM_ERR_CAP_3_ERR_NSPROT_SHFT                               0x8
#define HWIO_RAM_5_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_BMSK                          0xff
#define HWIO_RAM_5_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_SHFT                           0x0

#define HWIO_RAM_5_IMEM_ERR_CAP_4_ADDR                                   (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000034)
#define HWIO_RAM_5_IMEM_ERR_CAP_4_RMSK                                    0x1ffffff
#define HWIO_RAM_5_IMEM_ERR_CAP_4_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_4_ADDR, HWIO_RAM_5_IMEM_ERR_CAP_4_RMSK)
#define HWIO_RAM_5_IMEM_ERR_CAP_4_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_CAP_4_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_BMSK                      0x1000000
#define HWIO_RAM_5_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_SHFT                           0x18
#define HWIO_RAM_5_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_BMSK                    0xff0000
#define HWIO_RAM_5_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_SHFT                        0x10
#define HWIO_RAM_5_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_BMSK                      0xff00
#define HWIO_RAM_5_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_SHFT                         0x8
#define HWIO_RAM_5_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_BMSK                        0xff
#define HWIO_RAM_5_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_SHFT                         0x0

#define HWIO_RAM_5_IMEM_ERR_COUNT_ADDR                                   (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000074)
#define HWIO_RAM_5_IMEM_ERR_COUNT_RMSK                                   0xffffffff
#define HWIO_RAM_5_IMEM_ERR_COUNT_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_COUNT_ADDR, HWIO_RAM_5_IMEM_ERR_COUNT_RMSK)
#define HWIO_RAM_5_IMEM_ERR_COUNT_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_ERR_COUNT_ADDR, m)
#define HWIO_RAM_5_IMEM_ERR_COUNT_ERR_UE_COUNT_BMSK                      0xffff0000
#define HWIO_RAM_5_IMEM_ERR_COUNT_ERR_UE_COUNT_SHFT                            0x10
#define HWIO_RAM_5_IMEM_ERR_COUNT_ERR_CE_COUNT_BMSK                          0xffff
#define HWIO_RAM_5_IMEM_ERR_COUNT_ERR_CE_COUNT_SHFT                             0x0

#define HWIO_RAM_5_IMEM_SCRUB_STATUS_ADDR                                (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000038)
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_RMSK                                       0x7
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_STATUS_ADDR, HWIO_RAM_5_IMEM_SCRUB_STATUS_RMSK)
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_STATUS_ADDR, m)
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_SCRUB_INPROG_BMSK                          0x4
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_SCRUB_INPROG_SHFT                          0x2
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_WIPE_INPROG_BMSK                           0x2
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_WIPE_INPROG_SHFT                           0x1
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_ADDR_MAX_BMSK                              0x1
#define HWIO_RAM_5_IMEM_SCRUB_STATUS_ADDR_MAX_SHFT                              0x0

#define HWIO_RAM_5_IMEM_SCRUB_CTRL_ADDR                                  (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000003c)
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_RMSK                                  0xfff8ffff
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_CTRL_ADDR, HWIO_RAM_5_IMEM_SCRUB_CTRL_RMSK)
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_CTRL_ADDR, m)
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_SCRUB_CTRL_ADDR,v)
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_SCRUB_CTRL_ADDR,m,v,HWIO_RAM_5_IMEM_SCRUB_CTRL_IN)
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_SCRUB_EN_BMSK                         0x80000000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_SCRUB_EN_SHFT                               0x1f
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_LOAD_ADDR_BMSK                        0x40000000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_LOAD_ADDR_SHFT                              0x1e
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_WRITE_DATA_BMSK                       0x20000000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_WRITE_DATA_SHFT                             0x1d
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_WIPE_DATA_BMSK                        0x10000000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_WIPE_DATA_SHFT                              0x1c
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_BMSK                    0x8000000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_SHFT                         0x1b
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_BMSK                      0x4000000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_SHFT                           0x1a
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_BMSK                    0x2000000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_SHFT                         0x19
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_BMSK                     0x1000000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_SHFT                          0x18
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_NUM_ADDR_BMSK                           0xf80000
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_NUM_ADDR_SHFT                               0x13
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_SCRUB_TIMER_BMSK                          0xffff
#define HWIO_RAM_5_IMEM_SCRUB_CTRL_SCRUB_TIMER_SHFT                             0x0

#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_ADDR                             (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000040)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_RMSK                             0xffffffff
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_ADDR, HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_RMSK)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_ADDR, m)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_ADDR                             (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000044)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_RMSK                                 0xffff
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_ADDR, HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_RMSK)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_ADDR, m)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_ADDR                             (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000048)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_ADDR, HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_RMSK)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_ADDR, m)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_ADDR,v)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_ADDR,m,v,HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_IN)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_ADDR                             (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000004c)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_RMSK                                 0xffff
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_ADDR, HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_RMSK)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_ADDR, m)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_ADDR,v)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_ADDR,m,v,HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_IN)
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_RAM_5_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_ADDR                             (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000050)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_RMSK                             0xffffffff
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_ADDR, HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_RMSK)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_ADDR, m)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_ADDR,v)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_ADDR,m,v,HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_IN)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_BMSK              0xffffffff
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_SHFT                     0x0

#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_ADDR                             (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000054)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_RMSK                             0xffffffff
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_ADDR, HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_RMSK)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_ADDR, m)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_ADDR,v)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_ADDR,m,v,HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_IN)
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_BMSK             0xffffffff
#define HWIO_RAM_5_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_SHFT                    0x0

#define HWIO_RAM_5_IMEM_CONFIG_ADDR                                      (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000058)
#define HWIO_RAM_5_IMEM_CONFIG_RMSK                                            0x1f
#define HWIO_RAM_5_IMEM_CONFIG_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_CONFIG_ADDR, HWIO_RAM_5_IMEM_CONFIG_RMSK)
#define HWIO_RAM_5_IMEM_CONFIG_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_CONFIG_ADDR, m)
#define HWIO_RAM_5_IMEM_CONFIG_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_CONFIG_ADDR,v)
#define HWIO_RAM_5_IMEM_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_CONFIG_ADDR,m,v,HWIO_RAM_5_IMEM_CONFIG_IN)
#define HWIO_RAM_5_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_BMSK                        0x10
#define HWIO_RAM_5_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_SHFT                         0x4
#define HWIO_RAM_5_IMEM_CONFIG_ECC_ENABLE_BMSK                                  0x8
#define HWIO_RAM_5_IMEM_CONFIG_ECC_ENABLE_SHFT                                  0x3
#define HWIO_RAM_5_IMEM_CONFIG_ECC_ENABLE_WR_BMSK                               0x4
#define HWIO_RAM_5_IMEM_CONFIG_ECC_ENABLE_WR_SHFT                               0x2
#define HWIO_RAM_5_IMEM_CONFIG_ECC_ENABLE_RD_BMSK                               0x2
#define HWIO_RAM_5_IMEM_CONFIG_ECC_ENABLE_RD_SHFT                               0x1
#define HWIO_RAM_5_IMEM_CONFIG_ECC_RD_RMW_EN_BMSK                               0x1
#define HWIO_RAM_5_IMEM_CONFIG_ECC_RD_RMW_EN_SHFT                               0x0

#define HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_ADDR                        (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000005c)
#define HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_RMSK                        0xffffffff
#define HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_RMSK)
#define HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, m)
#define HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,v)
#define HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,m,v,HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_IN)
#define HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_BMSK              0xffffffff
#define HWIO_RAM_5_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_SHFT                     0x0

#define HWIO_RAM_5_IMEM_CLK_ON_CFG_ADDR                                  (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000064)
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_RMSK                                       0xfff
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_CLK_ON_CFG_ADDR, HWIO_RAM_5_IMEM_CLK_ON_CFG_RMSK)
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_CLK_ON_CFG_ADDR, m)
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_CLK_ON_CFG_ADDR,v)
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_CLK_ON_CFG_ADDR,m,v,HWIO_RAM_5_IMEM_CLK_ON_CFG_IN)
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_CLK_ON_TIME_BMSK                           0xffc
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_CLK_ON_TIME_SHFT                             0x2
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_BMSK                           0x2
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_SHFT                           0x1
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_CLK_ON_EN_BMSK                               0x1
#define HWIO_RAM_5_IMEM_CLK_ON_CFG_CLK_ON_EN_SHFT                               0x0

#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_ADDR                               (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000006c)
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_RMSK                                     0xff
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_PSBCGC_TIMERS_ADDR, HWIO_RAM_5_IMEM_PSBCGC_TIMERS_RMSK)
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_PSBCGC_TIMERS_ADDR, m)
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_PSBCGC_TIMERS_ADDR,v)
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_PSBCGC_TIMERS_ADDR,m,v,HWIO_RAM_5_IMEM_PSBCGC_TIMERS_IN)
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_BMSK                      0xf0
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_SHFT                       0x4
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_BMSK                     0xf
#define HWIO_RAM_5_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_SHFT                     0x0

#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_ADDR                              (RAM_5_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000070)
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_RMSK                              0x3fffffff
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_IN          \
        in_dword_masked(HWIO_RAM_5_IMEM_PSBCGC_CONTROL_ADDR, HWIO_RAM_5_IMEM_PSBCGC_CONTROL_RMSK)
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_RAM_5_IMEM_PSBCGC_CONTROL_ADDR, m)
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_OUT(v)      \
        out_dword(HWIO_RAM_5_IMEM_PSBCGC_CONTROL_ADDR,v)
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_RAM_5_IMEM_PSBCGC_CONTROL_ADDR,m,v,HWIO_RAM_5_IMEM_PSBCGC_CONTROL_IN)
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_HALT_CLOCK_BMSK                   0x3ff00000
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_HALT_CLOCK_SHFT                         0x14
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_CORE_ON_BMSK                         0xffc00
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_CORE_ON_SHFT                             0xa
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_PERIF_ON_BMSK                          0x3ff
#define HWIO_RAM_5_IMEM_PSBCGC_CONTROL_PERIF_ON_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: SYS_IMEM_IMEM_IMEM_CSRS
 *--------------------------------------------------------------------------*/

#define SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE                               (SYS_IMEM_BASE      + 0x00000000)

#define HWIO_SYS_IMEM_HW_ID_ADDR                                       (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000000)
#define HWIO_SYS_IMEM_HW_ID_RMSK                                       0xffffffff
#define HWIO_SYS_IMEM_HW_ID_IN          \
        in_dword_masked(HWIO_SYS_IMEM_HW_ID_ADDR, HWIO_SYS_IMEM_HW_ID_RMSK)
#define HWIO_SYS_IMEM_HW_ID_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_HW_ID_ADDR, m)
#define HWIO_SYS_IMEM_HW_ID_MAJOR_BMSK                                 0xff000000
#define HWIO_SYS_IMEM_HW_ID_MAJOR_SHFT                                       0x18
#define HWIO_SYS_IMEM_HW_ID_MINOR_BMSK                                   0xff0000
#define HWIO_SYS_IMEM_HW_ID_MINOR_SHFT                                       0x10
#define HWIO_SYS_IMEM_HW_ID_CONFIG_BMSK                                    0xff00
#define HWIO_SYS_IMEM_HW_ID_CONFIG_SHFT                                       0x8
#define HWIO_SYS_IMEM_HW_ID_INSTANCE_BMSK                                    0xff
#define HWIO_SYS_IMEM_HW_ID_INSTANCE_SHFT                                     0x0

#define HWIO_SYS_IMEM_HW_VERSION_ADDR                                  (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000004)
#define HWIO_SYS_IMEM_HW_VERSION_RMSK                                  0xffffffff
#define HWIO_SYS_IMEM_HW_VERSION_IN          \
        in_dword_masked(HWIO_SYS_IMEM_HW_VERSION_ADDR, HWIO_SYS_IMEM_HW_VERSION_RMSK)
#define HWIO_SYS_IMEM_HW_VERSION_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_HW_VERSION_ADDR, m)
#define HWIO_SYS_IMEM_HW_VERSION_MAJOR_BMSK                            0xff000000
#define HWIO_SYS_IMEM_HW_VERSION_MAJOR_SHFT                                  0x18
#define HWIO_SYS_IMEM_HW_VERSION_MINOR_BMSK                              0xff0000
#define HWIO_SYS_IMEM_HW_VERSION_MINOR_SHFT                                  0x10
#define HWIO_SYS_IMEM_HW_VERSION_STEP_BMSK                                 0xffff
#define HWIO_SYS_IMEM_HW_VERSION_STEP_SHFT                                    0x0

#define HWIO_SYS_IMEM_ERR_STATUS_ADDR                                  (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000008)
#define HWIO_SYS_IMEM_ERR_STATUS_RMSK                                       0x3ff
#define HWIO_SYS_IMEM_ERR_STATUS_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_STATUS_ADDR, HWIO_SYS_IMEM_ERR_STATUS_RMSK)
#define HWIO_SYS_IMEM_ERR_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_STATUS_ADDR, m)
#define HWIO_SYS_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_BMSK                   0x200
#define HWIO_SYS_IMEM_ERR_STATUS_QSB_ADDR_DECODE_ERR_SHFT                     0x9
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_POISON_SCRUB_BMSK                      0x100
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_POISON_SCRUB_SHFT                        0x8
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_UE_SCRUB_BMSK                           0x80
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_UE_SCRUB_SHFT                            0x7
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_CE_SCRUB_BMSK                           0x40
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_CE_SCRUB_SHFT                            0x6
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_POISON_RMW_BMSK                         0x20
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_POISON_RMW_SHFT                          0x5
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_UE_RMW_BMSK                             0x10
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_UE_RMW_SHFT                              0x4
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_CE_RMW_BMSK                              0x8
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_CE_RMW_SHFT                              0x3
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_BMSK                       0x4
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_POISON_QSB_RD_SHFT                       0x2
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_UE_QSB_RD_BMSK                           0x2
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_UE_QSB_RD_SHFT                           0x1
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_CE_QSB_RD_BMSK                           0x1
#define HWIO_SYS_IMEM_ERR_STATUS_ECC_CE_QSB_RD_SHFT                           0x0

#define HWIO_SYS_IMEM_ERR_CLR_ADDR                                     (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000000c)
#define HWIO_SYS_IMEM_ERR_CLR_RMSK                                          0x3ff
#define HWIO_SYS_IMEM_ERR_CLR_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_ERR_CLR_ADDR,v)
#define HWIO_SYS_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_SYS_IMEM_ERR_CLR_CLR_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_UE_RMW_BMSK                            0x10
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_UE_RMW_SHFT                             0x4
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_CE_RMW_BMSK                             0x8
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_CE_RMW_SHFT                             0x3
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_SYS_IMEM_ERR_CLR_CLR_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_SYS_IMEM_ERR_CTRL_ADDR                                    (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000010)
#define HWIO_SYS_IMEM_ERR_CTRL_RMSK                                         0x3ff
#define HWIO_SYS_IMEM_ERR_CTRL_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CTRL_ADDR, HWIO_SYS_IMEM_ERR_CTRL_RMSK)
#define HWIO_SYS_IMEM_ERR_CTRL_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CTRL_ADDR, m)
#define HWIO_SYS_IMEM_ERR_CTRL_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_ERR_CTRL_ADDR,v)
#define HWIO_SYS_IMEM_ERR_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_ERR_CTRL_ADDR,m,v,HWIO_SYS_IMEM_ERR_CTRL_IN)
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_BMSK                0x200
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_QSB_ADDR_DECODE_ERR_SHFT                  0x9
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_BMSK                   0x100
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_POISON_SCRUB_SHFT                     0x8
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_BMSK                        0x80
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_UE_SCRUB_SHFT                         0x7
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_BMSK                        0x40
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_CE_SCRUB_SHFT                         0x6
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_BMSK                      0x20
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_POISON_RMW_SHFT                       0x5
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_BMSK                          0x10
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_UE_RMW_SHFT                           0x4
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_BMSK                           0x8
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_CE_RMW_SHFT                           0x3
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_BMSK                    0x4
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_POISON_QSB_RD_SHFT                    0x2
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_BMSK                        0x2
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_UE_QSB_RD_SHFT                        0x1
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_BMSK                        0x1
#define HWIO_SYS_IMEM_ERR_CTRL_MASK_ECC_CE_QSB_RD_SHFT                        0x0

#define HWIO_SYS_IMEM_INT0_CTRL_ADDR                                   (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000014)
#define HWIO_SYS_IMEM_INT0_CTRL_RMSK                                        0x3ff
#define HWIO_SYS_IMEM_INT0_CTRL_IN          \
        in_dword_masked(HWIO_SYS_IMEM_INT0_CTRL_ADDR, HWIO_SYS_IMEM_INT0_CTRL_RMSK)
#define HWIO_SYS_IMEM_INT0_CTRL_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_INT0_CTRL_ADDR, m)
#define HWIO_SYS_IMEM_INT0_CTRL_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_INT0_CTRL_ADDR,v)
#define HWIO_SYS_IMEM_INT0_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_INT0_CTRL_ADDR,m,v,HWIO_SYS_IMEM_INT0_CTRL_IN)
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_BMSK                         0x10
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_UE_RMW_SHFT                          0x4
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_BMSK                          0x8
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_CE_RMW_SHFT                          0x3
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_SYS_IMEM_INT0_CTRL_INT0_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_SYS_IMEM_INT1_CTRL_ADDR                                   (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000018)
#define HWIO_SYS_IMEM_INT1_CTRL_RMSK                                        0x3ff
#define HWIO_SYS_IMEM_INT1_CTRL_IN          \
        in_dword_masked(HWIO_SYS_IMEM_INT1_CTRL_ADDR, HWIO_SYS_IMEM_INT1_CTRL_RMSK)
#define HWIO_SYS_IMEM_INT1_CTRL_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_INT1_CTRL_ADDR, m)
#define HWIO_SYS_IMEM_INT1_CTRL_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_INT1_CTRL_ADDR,v)
#define HWIO_SYS_IMEM_INT1_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_INT1_CTRL_ADDR,m,v,HWIO_SYS_IMEM_INT1_CTRL_IN)
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_BMSK               0x200
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_QSB_ADDR_DECODE_ERR_SHFT                 0x9
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_BMSK                  0x100
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_POISON_SCRUB_SHFT                    0x8
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_BMSK                       0x80
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_UE_SCRUB_SHFT                        0x7
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_BMSK                       0x40
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_CE_SCRUB_SHFT                        0x6
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_BMSK                     0x20
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_POISON_RMW_SHFT                      0x5
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_BMSK                         0x10
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_UE_RMW_SHFT                          0x4
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_BMSK                          0x8
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_CE_RMW_SHFT                          0x3
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_BMSK                   0x4
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_POISON_QSB_RD_SHFT                   0x2
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_BMSK                       0x2
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_UE_QSB_RD_SHFT                       0x1
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_BMSK                       0x1
#define HWIO_SYS_IMEM_INT1_CTRL_INT1_ECC_CE_QSB_RD_SHFT                       0x0

#define HWIO_SYS_IMEM_ERR_INJ_ADDR                                     (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000001c)
#define HWIO_SYS_IMEM_ERR_INJ_RMSK                                          0x3ff
#define HWIO_SYS_IMEM_ERR_INJ_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_ERR_INJ_ADDR,v)
#define HWIO_SYS_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_BMSK                  0x200
#define HWIO_SYS_IMEM_ERR_INJ_INJ_QSB_ADDR_DECODE_ERR_SHFT                    0x9
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_BMSK                     0x100
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_POISON_SCRUB_SHFT                       0x8
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_BMSK                          0x80
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_UE_SCRUB_SHFT                           0x7
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_BMSK                          0x40
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_CE_SCRUB_SHFT                           0x6
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_BMSK                        0x20
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_POISON_RMW_SHFT                         0x5
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_UE_RMW_BMSK                            0x10
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_UE_RMW_SHFT                             0x4
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_CE_RMW_BMSK                             0x8
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_CE_RMW_SHFT                             0x3
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_BMSK                      0x4
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_POISON_QSB_RD_SHFT                      0x2
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_BMSK                          0x2
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_UE_QSB_RD_SHFT                          0x1
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_BMSK                          0x1
#define HWIO_SYS_IMEM_ERR_INJ_INJ_ECC_CE_QSB_RD_SHFT                          0x0

#define HWIO_SYS_IMEM_ERR_CAP_CNTL_ADDR                                (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000020)
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_RMSK                                      0x1f
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_CNTL_ADDR, HWIO_SYS_IMEM_ERR_CAP_CNTL_RMSK)
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_CNTL_ADDR, m)
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_ERR_CAP_CNTL_ADDR,v)
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_ERR_CAP_CNTL_ADDR,m,v,HWIO_SYS_IMEM_ERR_CAP_CNTL_IN)
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_BMSK                       0x10
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_CLEAR_UE_COUNT_SHFT                        0x4
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_BMSK                        0x8
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_CLEAR_CE_COUNT_SHFT                        0x3
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_BMSK                    0x4
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_CONTINUOUS_CAPTURE_SHFT                    0x2
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_BMSK                    0x2
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_CLEAR_ERR_CAPTURED_SHFT                    0x1
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_BMSK                          0x1
#define HWIO_SYS_IMEM_ERR_CAP_CNTL_ERR_CAPTURED_SHFT                          0x0

#define HWIO_SYS_IMEM_ERR_CAP_0_ADDR                                   (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000024)
#define HWIO_SYS_IMEM_ERR_CAP_0_RMSK                                   0xffffffff
#define HWIO_SYS_IMEM_ERR_CAP_0_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_0_ADDR, HWIO_SYS_IMEM_ERR_CAP_0_RMSK)
#define HWIO_SYS_IMEM_ERR_CAP_0_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_0_ADDR, m)
#define HWIO_SYS_IMEM_ERR_CAP_0_ERR_ADDR_LO_BMSK                       0xffffffff
#define HWIO_SYS_IMEM_ERR_CAP_0_ERR_ADDR_LO_SHFT                              0x0

#define HWIO_SYS_IMEM_ERR_CAP_1_ADDR                                   (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000028)
#define HWIO_SYS_IMEM_ERR_CAP_1_RMSK                                   0xffff0fff
#define HWIO_SYS_IMEM_ERR_CAP_1_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_1_ADDR, HWIO_SYS_IMEM_ERR_CAP_1_RMSK)
#define HWIO_SYS_IMEM_ERR_CAP_1_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_1_ADDR, m)
#define HWIO_SYS_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_BMSK                0xff000000
#define HWIO_SYS_IMEM_ERR_CAP_1_ERR_SYNDROME_FIRST_SHFT                      0x18
#define HWIO_SYS_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_BMSK                   0xff0000
#define HWIO_SYS_IMEM_ERR_CAP_1_ERR_SYNDROME_LAST_SHFT                       0x10
#define HWIO_SYS_IMEM_ERR_CAP_1_ERR_ADDR_HI_BMSK                            0xfff
#define HWIO_SYS_IMEM_ERR_CAP_1_ERR_ADDR_HI_SHFT                              0x0

#define HWIO_SYS_IMEM_ERR_CAP_2_ADDR                                   (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000002c)
#define HWIO_SYS_IMEM_ERR_CAP_2_RMSK                                   0x1fffffff
#define HWIO_SYS_IMEM_ERR_CAP_2_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_2_ADDR, HWIO_SYS_IMEM_ERR_CAP_2_RMSK)
#define HWIO_SYS_IMEM_ERR_CAP_2_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_2_ADDR, m)
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_ABURST_BMSK                        0x10000000
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_ABURST_SHFT                              0x1c
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_AWRITE_BMSK                         0x8000000
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_AWRITE_SHFT                              0x1b
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_ALEN_BMSK                           0x7c00000
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_ALEN_SHFT                                0x16
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_BMSK                      0x200000
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_AEXCLUSIVE_SHFT                          0x15
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_TID_BMSK                             0x1f0000
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_TID_SHFT                                 0x10
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_BID_BMSK                               0xe000
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_BID_SHFT                                  0xd
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_PID_BMSK                               0x1f00
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_PID_SHFT                                  0x8
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_MID_BMSK                                 0xff
#define HWIO_SYS_IMEM_ERR_CAP_2_ERR_MID_SHFT                                  0x0

#define HWIO_SYS_IMEM_ERR_CAP_3_ADDR                                   (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000030)
#define HWIO_SYS_IMEM_ERR_CAP_3_RMSK                                      0x3ffff
#define HWIO_SYS_IMEM_ERR_CAP_3_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_3_ADDR, HWIO_SYS_IMEM_ERR_CAP_3_RMSK)
#define HWIO_SYS_IMEM_ERR_CAP_3_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_3_ADDR, m)
#define HWIO_SYS_IMEM_ERR_CAP_3_ERR_VMID_BMSK                             0x3fc00
#define HWIO_SYS_IMEM_ERR_CAP_3_ERR_VMID_SHFT                                 0xa
#define HWIO_SYS_IMEM_ERR_CAP_3_ERR_MSA_BMSK                                0x200
#define HWIO_SYS_IMEM_ERR_CAP_3_ERR_MSA_SHFT                                  0x9
#define HWIO_SYS_IMEM_ERR_CAP_3_ERR_NSPROT_BMSK                             0x100
#define HWIO_SYS_IMEM_ERR_CAP_3_ERR_NSPROT_SHFT                               0x8
#define HWIO_SYS_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_BMSK                          0xff
#define HWIO_SYS_IMEM_ERR_CAP_3_ERR_BEAT_INDEX_SHFT                           0x0

#define HWIO_SYS_IMEM_ERR_CAP_4_ADDR                                   (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000034)
#define HWIO_SYS_IMEM_ERR_CAP_4_RMSK                                    0x1ffffff
#define HWIO_SYS_IMEM_ERR_CAP_4_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_4_ADDR, HWIO_SYS_IMEM_ERR_CAP_4_RMSK)
#define HWIO_SYS_IMEM_ERR_CAP_4_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_CAP_4_ADDR, m)
#define HWIO_SYS_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_BMSK                      0x1000000
#define HWIO_SYS_IMEM_ERR_CAP_4_ERR_SCRUB_REQ_SHFT                           0x18
#define HWIO_SYS_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_BMSK                    0xff0000
#define HWIO_SYS_IMEM_ERR_CAP_4_ERR_ECC_CHK_BITS_SHFT                        0x10
#define HWIO_SYS_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_BMSK                      0xff00
#define HWIO_SYS_IMEM_ERR_CAP_4_ERR_ECC_GEN_BITS_SHFT                         0x8
#define HWIO_SYS_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_BMSK                        0xff
#define HWIO_SYS_IMEM_ERR_CAP_4_ERR_ECC_SYNDROME_SHFT                         0x0

#define HWIO_SYS_IMEM_ERR_COUNT_ADDR                                   (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000074)
#define HWIO_SYS_IMEM_ERR_COUNT_RMSK                                   0xffffffff
#define HWIO_SYS_IMEM_ERR_COUNT_IN          \
        in_dword_masked(HWIO_SYS_IMEM_ERR_COUNT_ADDR, HWIO_SYS_IMEM_ERR_COUNT_RMSK)
#define HWIO_SYS_IMEM_ERR_COUNT_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_ERR_COUNT_ADDR, m)
#define HWIO_SYS_IMEM_ERR_COUNT_ERR_UE_COUNT_BMSK                      0xffff0000
#define HWIO_SYS_IMEM_ERR_COUNT_ERR_UE_COUNT_SHFT                            0x10
#define HWIO_SYS_IMEM_ERR_COUNT_ERR_CE_COUNT_BMSK                          0xffff
#define HWIO_SYS_IMEM_ERR_COUNT_ERR_CE_COUNT_SHFT                             0x0

#define HWIO_SYS_IMEM_SCRUB_STATUS_ADDR                                (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000038)
#define HWIO_SYS_IMEM_SCRUB_STATUS_RMSK                                       0x7
#define HWIO_SYS_IMEM_SCRUB_STATUS_IN          \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_STATUS_ADDR, HWIO_SYS_IMEM_SCRUB_STATUS_RMSK)
#define HWIO_SYS_IMEM_SCRUB_STATUS_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_STATUS_ADDR, m)
#define HWIO_SYS_IMEM_SCRUB_STATUS_SCRUB_INPROG_BMSK                          0x4
#define HWIO_SYS_IMEM_SCRUB_STATUS_SCRUB_INPROG_SHFT                          0x2
#define HWIO_SYS_IMEM_SCRUB_STATUS_WIPE_INPROG_BMSK                           0x2
#define HWIO_SYS_IMEM_SCRUB_STATUS_WIPE_INPROG_SHFT                           0x1
#define HWIO_SYS_IMEM_SCRUB_STATUS_ADDR_MAX_BMSK                              0x1
#define HWIO_SYS_IMEM_SCRUB_STATUS_ADDR_MAX_SHFT                              0x0

#define HWIO_SYS_IMEM_SCRUB_CTRL_ADDR                                  (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000003c)
#define HWIO_SYS_IMEM_SCRUB_CTRL_RMSK                                  0xfff8ffff
#define HWIO_SYS_IMEM_SCRUB_CTRL_IN          \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_CTRL_ADDR, HWIO_SYS_IMEM_SCRUB_CTRL_RMSK)
#define HWIO_SYS_IMEM_SCRUB_CTRL_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_CTRL_ADDR, m)
#define HWIO_SYS_IMEM_SCRUB_CTRL_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_SCRUB_CTRL_ADDR,v)
#define HWIO_SYS_IMEM_SCRUB_CTRL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_SCRUB_CTRL_ADDR,m,v,HWIO_SYS_IMEM_SCRUB_CTRL_IN)
#define HWIO_SYS_IMEM_SCRUB_CTRL_SCRUB_EN_BMSK                         0x80000000
#define HWIO_SYS_IMEM_SCRUB_CTRL_SCRUB_EN_SHFT                               0x1f
#define HWIO_SYS_IMEM_SCRUB_CTRL_LOAD_ADDR_BMSK                        0x40000000
#define HWIO_SYS_IMEM_SCRUB_CTRL_LOAD_ADDR_SHFT                              0x1e
#define HWIO_SYS_IMEM_SCRUB_CTRL_WRITE_DATA_BMSK                       0x20000000
#define HWIO_SYS_IMEM_SCRUB_CTRL_WRITE_DATA_SHFT                             0x1d
#define HWIO_SYS_IMEM_SCRUB_CTRL_WIPE_DATA_BMSK                        0x10000000
#define HWIO_SYS_IMEM_SCRUB_CTRL_WIPE_DATA_SHFT                              0x1c
#define HWIO_SYS_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_BMSK                    0x8000000
#define HWIO_SYS_IMEM_SCRUB_CTRL_CLEAR_ADDR_MAX_SHFT                         0x1b
#define HWIO_SYS_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_BMSK                      0x4000000
#define HWIO_SYS_IMEM_SCRUB_CTRL_SCRUB_RMW_EN_SHFT                           0x1a
#define HWIO_SYS_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_BMSK                    0x2000000
#define HWIO_SYS_IMEM_SCRUB_CTRL_SCRUB_QSB_PREF_SHFT                         0x19
#define HWIO_SYS_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_BMSK                     0x1000000
#define HWIO_SYS_IMEM_SCRUB_CTRL_ADDR_MAX_HALT_SHFT                          0x18
#define HWIO_SYS_IMEM_SCRUB_CTRL_NUM_ADDR_BMSK                           0xf80000
#define HWIO_SYS_IMEM_SCRUB_CTRL_NUM_ADDR_SHFT                               0x13
#define HWIO_SYS_IMEM_SCRUB_CTRL_SCRUB_TIMER_BMSK                          0xffff
#define HWIO_SYS_IMEM_SCRUB_CTRL_SCRUB_TIMER_SHFT                             0x0

#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_ADDR                             (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000040)
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_RMSK                             0xffffffff
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_IN          \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_ADDR, HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_RMSK)
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_ADDR, m)
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_ADDR                             (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000044)
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_RMSK                                 0xffff
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_IN          \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_ADDR, HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_RMSK)
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_ADDR, m)
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_SYS_IMEM_SCRUB_ADDR_RD_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_ADDR                             (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000048)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_RMSK                             0xffffffff
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_IN          \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_ADDR, HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_RMSK)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_ADDR, m)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_ADDR,v)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_ADDR,m,v,HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_IN)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_BMSK              0xffffffff
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_0_SCRUB_ADDR_LOW_SHFT                     0x0

#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_ADDR                             (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000004c)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_RMSK                                 0xffff
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_IN          \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_ADDR, HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_RMSK)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_ADDR, m)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_ADDR,v)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_ADDR,m,v,HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_IN)
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_BMSK                 0xffff
#define HWIO_SYS_IMEM_SCRUB_ADDR_WR_1_SCRUB_ADDR_HIGH_SHFT                    0x0

#define HWIO_SYS_IMEM_SCRUB_DATA_WR_0_ADDR                             (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000050)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_0_RMSK                             0xffffffff
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_0_IN          \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_DATA_WR_0_ADDR, HWIO_SYS_IMEM_SCRUB_DATA_WR_0_RMSK)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_0_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_DATA_WR_0_ADDR, m)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_0_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_SCRUB_DATA_WR_0_ADDR,v)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_0_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_SCRUB_DATA_WR_0_ADDR,m,v,HWIO_SYS_IMEM_SCRUB_DATA_WR_0_IN)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_BMSK              0xffffffff
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_0_SCRUB_DATA_LOW_SHFT                     0x0

#define HWIO_SYS_IMEM_SCRUB_DATA_WR_1_ADDR                             (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000054)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_1_RMSK                             0xffffffff
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_1_IN          \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_DATA_WR_1_ADDR, HWIO_SYS_IMEM_SCRUB_DATA_WR_1_RMSK)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_1_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_SCRUB_DATA_WR_1_ADDR, m)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_1_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_SCRUB_DATA_WR_1_ADDR,v)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_1_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_SCRUB_DATA_WR_1_ADDR,m,v,HWIO_SYS_IMEM_SCRUB_DATA_WR_1_IN)
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_BMSK             0xffffffff
#define HWIO_SYS_IMEM_SCRUB_DATA_WR_1_SCRUB_DATA_HIGH_SHFT                    0x0

#define HWIO_SYS_IMEM_CONFIG_ADDR                                      (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000058)
#define HWIO_SYS_IMEM_CONFIG_RMSK                                            0x1f
#define HWIO_SYS_IMEM_CONFIG_IN          \
        in_dword_masked(HWIO_SYS_IMEM_CONFIG_ADDR, HWIO_SYS_IMEM_CONFIG_RMSK)
#define HWIO_SYS_IMEM_CONFIG_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_CONFIG_ADDR, m)
#define HWIO_SYS_IMEM_CONFIG_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_CONFIG_ADDR,v)
#define HWIO_SYS_IMEM_CONFIG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_CONFIG_ADDR,m,v,HWIO_SYS_IMEM_CONFIG_IN)
#define HWIO_SYS_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_BMSK                        0x10
#define HWIO_SYS_IMEM_CONFIG_CLR_EEM_CLREXMONREQ_SHFT                         0x4
#define HWIO_SYS_IMEM_CONFIG_ECC_ENABLE_BMSK                                  0x8
#define HWIO_SYS_IMEM_CONFIG_ECC_ENABLE_SHFT                                  0x3
#define HWIO_SYS_IMEM_CONFIG_ECC_ENABLE_WR_BMSK                               0x4
#define HWIO_SYS_IMEM_CONFIG_ECC_ENABLE_WR_SHFT                               0x2
#define HWIO_SYS_IMEM_CONFIG_ECC_ENABLE_RD_BMSK                               0x2
#define HWIO_SYS_IMEM_CONFIG_ECC_ENABLE_RD_SHFT                               0x1
#define HWIO_SYS_IMEM_CONFIG_ECC_RD_RMW_EN_BMSK                               0x1
#define HWIO_SYS_IMEM_CONFIG_ECC_RD_RMW_EN_SHFT                               0x0

#define HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_ADDR                        (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000005c)
#define HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_RMSK                        0xffffffff
#define HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_IN          \
        in_dword_masked(HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_RMSK)
#define HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_ADDR, m)
#define HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,v)
#define HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_ADDR,m,v,HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_IN)
#define HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_BMSK              0xffffffff
#define HWIO_SYS_IMEM_AXI_BASE_ADDR_OFFSET_BASE_ADDR_SHFT                     0x0

#define HWIO_SYS_IMEM_CLK_ON_CFG_ADDR                                  (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000064)
#define HWIO_SYS_IMEM_CLK_ON_CFG_RMSK                                       0xfff
#define HWIO_SYS_IMEM_CLK_ON_CFG_IN          \
        in_dword_masked(HWIO_SYS_IMEM_CLK_ON_CFG_ADDR, HWIO_SYS_IMEM_CLK_ON_CFG_RMSK)
#define HWIO_SYS_IMEM_CLK_ON_CFG_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_CLK_ON_CFG_ADDR, m)
#define HWIO_SYS_IMEM_CLK_ON_CFG_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_CLK_ON_CFG_ADDR,v)
#define HWIO_SYS_IMEM_CLK_ON_CFG_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_CLK_ON_CFG_ADDR,m,v,HWIO_SYS_IMEM_CLK_ON_CFG_IN)
#define HWIO_SYS_IMEM_CLK_ON_CFG_CLK_ON_TIME_BMSK                           0xffc
#define HWIO_SYS_IMEM_CLK_ON_CFG_CLK_ON_TIME_SHFT                             0x2
#define HWIO_SYS_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_BMSK                           0x2
#define HWIO_SYS_IMEM_CLK_ON_CFG_AHB_CLK_ON_EN_SHFT                           0x1
#define HWIO_SYS_IMEM_CLK_ON_CFG_CLK_ON_EN_BMSK                               0x1
#define HWIO_SYS_IMEM_CLK_ON_CFG_CLK_ON_EN_SHFT                               0x0

#define HWIO_SYS_IMEM_PSBCGC_TIMERS_ADDR                               (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x0000006c)
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_RMSK                                     0xff
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_IN          \
        in_dword_masked(HWIO_SYS_IMEM_PSBCGC_TIMERS_ADDR, HWIO_SYS_IMEM_PSBCGC_TIMERS_RMSK)
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_PSBCGC_TIMERS_ADDR, m)
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_PSBCGC_TIMERS_ADDR,v)
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_PSBCGC_TIMERS_ADDR,m,v,HWIO_SYS_IMEM_PSBCGC_TIMERS_IN)
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_BMSK                      0xf0
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_WAKEUP_COUNTER_SHFT                       0x4
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_BMSK                     0xf
#define HWIO_SYS_IMEM_PSBCGC_TIMERS_TO_SLEEP_COUNTER_SHFT                     0x0

#define HWIO_SYS_IMEM_PSBCGC_CONTROL_ADDR                              (SYS_IMEM_IMEM_IMEM_CSRS_REG_BASE      + 0x00000070)
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_RMSK                              0x3fffffff
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_IN          \
        in_dword_masked(HWIO_SYS_IMEM_PSBCGC_CONTROL_ADDR, HWIO_SYS_IMEM_PSBCGC_CONTROL_RMSK)
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_INM(m)      \
        in_dword_masked(HWIO_SYS_IMEM_PSBCGC_CONTROL_ADDR, m)
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_OUT(v)      \
        out_dword(HWIO_SYS_IMEM_PSBCGC_CONTROL_ADDR,v)
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_OUTM(m,v) \
        out_dword_masked_ns(HWIO_SYS_IMEM_PSBCGC_CONTROL_ADDR,m,v,HWIO_SYS_IMEM_PSBCGC_CONTROL_IN)
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_HALT_CLOCK_BMSK                   0x3ff00000
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_HALT_CLOCK_SHFT                         0x14
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_CORE_ON_BMSK                         0xffc00
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_CORE_ON_SHFT                             0xa
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_PERIF_ON_BMSK                          0x3ff
#define HWIO_SYS_IMEM_PSBCGC_CONTROL_PERIF_ON_SHFT                            0x0


#endif /* __HWIO_IMEM_H__ */
