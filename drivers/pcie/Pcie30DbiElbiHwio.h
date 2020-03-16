#ifndef __PCIE30DBIELBIHWIO_H__
#define __PCIE30DBIELBIHWIO_H__
/*
===========================================================================
*/
/**
  @file Pcie30DbiElbiHwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r64.0]

  This file contains HWIO register definitions for the following modules:
    PCIE0_X16_DWC_PCIE_DM
    PCIE0_PCIE30_ELBI

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
 * MODULE: X16_DWC_PCIE_DM
 *--------------------------------------------------------------------------*/

#define X16_DWC_PCIE_DM_REG_BASE                                                                         (PCIE_SS_VBU_TN_BASE      + 0x00000000)

#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_ADDR(x)                                                            ((x) + 0x00000000)
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_RMSK                                                               0xffffffff
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_ATTR                                                                      0x3
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_IN(x)      \
        in_dword_masked(HWIO_TYPE1_DEV_ID_VEND_ID_REG_ADDR(x), HWIO_TYPE1_DEV_ID_VEND_ID_REG_RMSK)
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_INM(x, m)      \
        in_dword_masked(HWIO_TYPE1_DEV_ID_VEND_ID_REG_ADDR(x), m)
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_OUT(x, v)      \
        out_dword(HWIO_TYPE1_DEV_ID_VEND_ID_REG_ADDR(x),v)
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TYPE1_DEV_ID_VEND_ID_REG_ADDR(x),m,v,HWIO_TYPE1_DEV_ID_VEND_ID_REG_IN(x))
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_DEVICE_ID_BMSK                                                     0xffff0000
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_DEVICE_ID_SHFT                                                           0x10
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_VENDOR_ID_BMSK                                                         0xffff
#define HWIO_TYPE1_DEV_ID_VEND_ID_REG_VENDOR_ID_SHFT                                                            0x0

#define HWIO_TYPE1_STATUS_COMMAND_REG_ADDR(x)                                                            ((x) + 0x00000004)
#define HWIO_TYPE1_STATUS_COMMAND_REG_RMSK                                                               0xfffeffff
#define HWIO_TYPE1_STATUS_COMMAND_REG_ATTR                                                                      0x3
#define HWIO_TYPE1_STATUS_COMMAND_REG_IN(x)      \
        in_dword_masked(HWIO_TYPE1_STATUS_COMMAND_REG_ADDR(x), HWIO_TYPE1_STATUS_COMMAND_REG_RMSK)
#define HWIO_TYPE1_STATUS_COMMAND_REG_INM(x, m)      \
        in_dword_masked(HWIO_TYPE1_STATUS_COMMAND_REG_ADDR(x), m)
#define HWIO_TYPE1_STATUS_COMMAND_REG_OUT(x, v)      \
        out_dword(HWIO_TYPE1_STATUS_COMMAND_REG_ADDR(x),v)
#define HWIO_TYPE1_STATUS_COMMAND_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TYPE1_STATUS_COMMAND_REG_ADDR(x),m,v,HWIO_TYPE1_STATUS_COMMAND_REG_IN(x))
#define HWIO_TYPE1_STATUS_COMMAND_REG_DETECTED_PARITY_ERROR_BMSK                                         0x80000000
#define HWIO_TYPE1_STATUS_COMMAND_REG_DETECTED_PARITY_ERROR_SHFT                                               0x1f
#define HWIO_TYPE1_STATUS_COMMAND_REG_SIGNALED_SYS_ERROR_BMSK                                            0x40000000
#define HWIO_TYPE1_STATUS_COMMAND_REG_SIGNALED_SYS_ERROR_SHFT                                                  0x1e
#define HWIO_TYPE1_STATUS_COMMAND_REG_RCVD_MASTER_ABORT_BMSK                                             0x20000000
#define HWIO_TYPE1_STATUS_COMMAND_REG_RCVD_MASTER_ABORT_SHFT                                                   0x1d
#define HWIO_TYPE1_STATUS_COMMAND_REG_RCVD_TARGET_ABORT_BMSK                                             0x10000000
#define HWIO_TYPE1_STATUS_COMMAND_REG_RCVD_TARGET_ABORT_SHFT                                                   0x1c
#define HWIO_TYPE1_STATUS_COMMAND_REG_SIGNALED_TARGET_ABORT_BMSK                                          0x8000000
#define HWIO_TYPE1_STATUS_COMMAND_REG_SIGNALED_TARGET_ABORT_SHFT                                               0x1b
#define HWIO_TYPE1_STATUS_COMMAND_REG_DEV_SEL_TIMING_BMSK                                                 0x6000000
#define HWIO_TYPE1_STATUS_COMMAND_REG_DEV_SEL_TIMING_SHFT                                                      0x19
#define HWIO_TYPE1_STATUS_COMMAND_REG_MASTER_DPE_BMSK                                                     0x1000000
#define HWIO_TYPE1_STATUS_COMMAND_REG_MASTER_DPE_SHFT                                                          0x18
#define HWIO_TYPE1_STATUS_COMMAND_REG_FAST_B2B_CAP_BMSK                                                    0x800000
#define HWIO_TYPE1_STATUS_COMMAND_REG_FAST_B2B_CAP_SHFT                                                        0x17
#define HWIO_TYPE1_STATUS_COMMAND_REG_RSVDP_22_BMSK                                                        0x400000
#define HWIO_TYPE1_STATUS_COMMAND_REG_RSVDP_22_SHFT                                                            0x16
#define HWIO_TYPE1_STATUS_COMMAND_REG_FAST_66MHZ_CAP_BMSK                                                  0x200000
#define HWIO_TYPE1_STATUS_COMMAND_REG_FAST_66MHZ_CAP_SHFT                                                      0x15
#define HWIO_TYPE1_STATUS_COMMAND_REG_CAP_LIST_BMSK                                                        0x100000
#define HWIO_TYPE1_STATUS_COMMAND_REG_CAP_LIST_SHFT                                                            0x14
#define HWIO_TYPE1_STATUS_COMMAND_REG_INT_STATUS_BMSK                                                       0x80000
#define HWIO_TYPE1_STATUS_COMMAND_REG_INT_STATUS_SHFT                                                          0x13
#define HWIO_TYPE1_STATUS_COMMAND_REG_RSVDP_17_BMSK                                                         0x60000
#define HWIO_TYPE1_STATUS_COMMAND_REG_RSVDP_17_SHFT                                                            0x11
#define HWIO_TYPE1_STATUS_COMMAND_REG_RESERV_BMSK                                                            0xf800
#define HWIO_TYPE1_STATUS_COMMAND_REG_RESERV_SHFT                                                               0xb
#define HWIO_TYPE1_STATUS_COMMAND_REG_INT_EN_BMSK                                                             0x400
#define HWIO_TYPE1_STATUS_COMMAND_REG_INT_EN_SHFT                                                               0xa
#define HWIO_TYPE1_STATUS_COMMAND_REG_RSVDP_9_BMSK                                                            0x200
#define HWIO_TYPE1_STATUS_COMMAND_REG_RSVDP_9_SHFT                                                              0x9
#define HWIO_TYPE1_STATUS_COMMAND_REG_SERREN_BMSK                                                             0x100
#define HWIO_TYPE1_STATUS_COMMAND_REG_SERREN_SHFT                                                               0x8
#define HWIO_TYPE1_STATUS_COMMAND_REG_IDSEL_BMSK                                                               0x80
#define HWIO_TYPE1_STATUS_COMMAND_REG_IDSEL_SHFT                                                                0x7
#define HWIO_TYPE1_STATUS_COMMAND_REG_PERREN_BMSK                                                              0x40
#define HWIO_TYPE1_STATUS_COMMAND_REG_PERREN_SHFT                                                               0x6
#define HWIO_TYPE1_STATUS_COMMAND_REG_VGAPS_BMSK                                                               0x20
#define HWIO_TYPE1_STATUS_COMMAND_REG_VGAPS_SHFT                                                                0x5
#define HWIO_TYPE1_STATUS_COMMAND_REG_MWI_EN_BMSK                                                              0x10
#define HWIO_TYPE1_STATUS_COMMAND_REG_MWI_EN_SHFT                                                               0x4
#define HWIO_TYPE1_STATUS_COMMAND_REG_SCO_BMSK                                                                  0x8
#define HWIO_TYPE1_STATUS_COMMAND_REG_SCO_SHFT                                                                  0x3
#define HWIO_TYPE1_STATUS_COMMAND_REG_BME_BMSK                                                                  0x4
#define HWIO_TYPE1_STATUS_COMMAND_REG_BME_SHFT                                                                  0x2
#define HWIO_TYPE1_STATUS_COMMAND_REG_MSE_BMSK                                                                  0x2
#define HWIO_TYPE1_STATUS_COMMAND_REG_MSE_SHFT                                                                  0x1
#define HWIO_TYPE1_STATUS_COMMAND_REG_IO_EN_BMSK                                                                0x1
#define HWIO_TYPE1_STATUS_COMMAND_REG_IO_EN_SHFT                                                                0x0

#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_ADDR(x)                                                         ((x) + 0x00000008)
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_RMSK                                                            0xffffffff
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_ATTR                                                                   0x3
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_IN(x)      \
        in_dword_masked(HWIO_TYPE1_CLASS_CODE_REV_ID_REG_ADDR(x), HWIO_TYPE1_CLASS_CODE_REV_ID_REG_RMSK)
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_INM(x, m)      \
        in_dword_masked(HWIO_TYPE1_CLASS_CODE_REV_ID_REG_ADDR(x), m)
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_OUT(x, v)      \
        out_dword(HWIO_TYPE1_CLASS_CODE_REV_ID_REG_ADDR(x),v)
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TYPE1_CLASS_CODE_REV_ID_REG_ADDR(x),m,v,HWIO_TYPE1_CLASS_CODE_REV_ID_REG_IN(x))
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_BASE_CLASS_CODE_BMSK                                            0xff000000
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_BASE_CLASS_CODE_SHFT                                                  0x18
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_SUBCLASS_CODE_BMSK                                                0xff0000
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_SUBCLASS_CODE_SHFT                                                    0x10
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_PROGRAM_INTERFACE_BMSK                                              0xff00
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_PROGRAM_INTERFACE_SHFT                                                 0x8
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_REVISION_ID_BMSK                                                      0xff
#define HWIO_TYPE1_CLASS_CODE_REV_ID_REG_REVISION_ID_SHFT                                                       0x0

#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_ADDR(x)                                         ((x) + 0x0000000c)
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_RMSK                                            0xffffffff
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_ATTR                                                   0x3
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_IN(x)      \
        in_dword_masked(HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_ADDR(x), HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_RMSK)
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_INM(x, m)      \
        in_dword_masked(HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_ADDR(x), m)
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_OUT(x, v)      \
        out_dword(HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_ADDR(x),v)
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_ADDR(x),m,v,HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_IN(x))
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_BIST_BMSK                                       0xff000000
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_BIST_SHFT                                             0x18
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_MULTI_FUNC_BMSK                                   0x800000
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_MULTI_FUNC_SHFT                                       0x17
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_HEADER_TYPE_BMSK                                  0x7f0000
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_HEADER_TYPE_SHFT                                      0x10
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_LATENCY_MASTER_TIMER_BMSK                           0xff00
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_LATENCY_MASTER_TIMER_SHFT                              0x8
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_CACHE_LINE_SIZE_BMSK                                  0xff
#define HWIO_TYPE1_BIST_HDR_TYPE_LAT_CACHE_LINE_SIZE_REG_CACHE_LINE_SIZE_SHFT                                   0x0

#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_ADDR(x)                                           ((x) + 0x00000018)
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_RMSK                                              0xffffffff
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_ATTR                                                     0x3
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_IN(x)      \
        in_dword_masked(HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_ADDR(x), HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_RMSK)
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_ADDR(x), m)
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_OUT(x, v)      \
        out_dword(HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_ADDR(x),v)
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_ADDR(x),m,v,HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_IN(x))
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_SEC_LAT_TIMER_BMSK                                0xff000000
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_SEC_LAT_TIMER_SHFT                                      0x18
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_SUB_BUS_BMSK                                        0xff0000
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_SUB_BUS_SHFT                                            0x10
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_SEC_BUS_BMSK                                          0xff00
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_SEC_BUS_SHFT                                             0x8
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_PRIM_BUS_BMSK                                           0xff
#define HWIO_SEC_LAT_TIMER_SUB_BUS_SEC_BUS_PRI_BUS_REG_PRIM_BUS_SHFT                                            0x0

#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_ADDR(x)                                                       ((x) + 0x0000001c)
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_RMSK                                                          0xffffffff
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_ATTR                                                                 0x3
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IN(x)      \
        in_dword_masked(HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_ADDR(x), HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_RMSK)
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_INM(x, m)      \
        in_dword_masked(HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_ADDR(x), m)
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_OUT(x, v)      \
        out_dword(HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_ADDR(x),v)
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_ADDR(x),m,v,HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IN(x))
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_DPE_BMSK                                             0x80000000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_DPE_SHFT                                                   0x1f
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_RCVD_SYS_ERR_BMSK                                    0x40000000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_RCVD_SYS_ERR_SHFT                                          0x1e
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_RCVD_MSTR_ABRT_BMSK                                  0x20000000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_RCVD_MSTR_ABRT_SHFT                                        0x1d
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_RCVD_TRGT_ABRT_BMSK                                  0x10000000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_RCVD_TRGT_ABRT_SHFT                                        0x1c
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_SIG_TRGT_ABRT_BMSK                                    0x8000000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_SIG_TRGT_ABRT_SHFT                                         0x1b
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_RSVDP_25_BMSK                                                  0x6000000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_RSVDP_25_SHFT                                                       0x19
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_MDPE_BMSK                                             0x1000000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_MDPE_SHFT                                                  0x18
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_RSVDP_23_BMSK                                                   0x800000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_RSVDP_23_SHFT                                                       0x17
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_RESERV_BMSK                                            0x7f0000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_SEC_STAT_RESERV_SHFT                                                0x10
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_LIMIT_BMSK                                                     0xf000
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_LIMIT_SHFT                                                        0xc
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_RESERV1_BMSK                                                    0xe00
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_RESERV1_SHFT                                                      0x9
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_DECODE_BIT8_BMSK                                                0x100
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_DECODE_BIT8_SHFT                                                  0x8
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_BASE_BMSK                                                        0xf0
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_BASE_SHFT                                                         0x4
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_RESERV_BMSK                                                       0xe
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_RESERV_SHFT                                                       0x1
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_DECODE_BMSK                                                       0x1
#define HWIO_SEC_STAT_IO_LIMIT_IO_BASE_REG_IO_DECODE_SHFT                                                       0x0

#define HWIO_MEM_LIMIT_MEM_BASE_REG_ADDR(x)                                                              ((x) + 0x00000020)
#define HWIO_MEM_LIMIT_MEM_BASE_REG_RMSK                                                                 0xffffffff
#define HWIO_MEM_LIMIT_MEM_BASE_REG_ATTR                                                                        0x3
#define HWIO_MEM_LIMIT_MEM_BASE_REG_IN(x)      \
        in_dword_masked(HWIO_MEM_LIMIT_MEM_BASE_REG_ADDR(x), HWIO_MEM_LIMIT_MEM_BASE_REG_RMSK)
#define HWIO_MEM_LIMIT_MEM_BASE_REG_INM(x, m)      \
        in_dword_masked(HWIO_MEM_LIMIT_MEM_BASE_REG_ADDR(x), m)
#define HWIO_MEM_LIMIT_MEM_BASE_REG_OUT(x, v)      \
        out_dword(HWIO_MEM_LIMIT_MEM_BASE_REG_ADDR(x),v)
#define HWIO_MEM_LIMIT_MEM_BASE_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MEM_LIMIT_MEM_BASE_REG_ADDR(x),m,v,HWIO_MEM_LIMIT_MEM_BASE_REG_IN(x))
#define HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_LIMIT_BMSK                                                       0xfff00000
#define HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_LIMIT_SHFT                                                             0x14
#define HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_LIMIT_RESERV_BMSK                                                   0xf0000
#define HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_LIMIT_RESERV_SHFT                                                      0x10
#define HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_BASE_BMSK                                                            0xfff0
#define HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_BASE_SHFT                                                               0x4
#define HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_BASE_RESERV_BMSK                                                        0xf
#define HWIO_MEM_LIMIT_MEM_BASE_REG_MEM_BASE_RESERV_SHFT                                                        0x0

#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_ADDR(x)                                                    ((x) + 0x00000024)
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_RMSK                                                       0xffffffff
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_ATTR                                                              0x3
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_IN(x)      \
        in_dword_masked(HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_ADDR(x), HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_RMSK)
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_INM(x, m)      \
        in_dword_masked(HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_ADDR(x), m)
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_OUT(x, v)      \
        out_dword(HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_ADDR(x),v)
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_ADDR(x),m,v,HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_IN(x))
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_MEM_LIMIT_BMSK                                        0xfff00000
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_MEM_LIMIT_SHFT                                              0x14
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_RESERV1_BMSK                                             0xe0000
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_RESERV1_SHFT                                                0x11
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_MEM_LIMIT_DECODE_BMSK                                    0x10000
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_MEM_LIMIT_DECODE_SHFT                                       0x10
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_MEM_BASE_BMSK                                             0xfff0
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_MEM_BASE_SHFT                                                0x4
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_RESERV_BMSK                                                  0xe
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_RESERV_SHFT                                                  0x1
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_MEM_DECODE_BMSK                                              0x1
#define HWIO_PREF_MEM_LIMIT_PREF_MEM_BASE_REG_PREF_MEM_DECODE_SHFT                                              0x0

#define HWIO_PREF_BASE_UPPER_REG_ADDR(x)                                                                 ((x) + 0x00000028)
#define HWIO_PREF_BASE_UPPER_REG_RMSK                                                                    0xffffffff
#define HWIO_PREF_BASE_UPPER_REG_ATTR                                                                           0x3
#define HWIO_PREF_BASE_UPPER_REG_IN(x)      \
        in_dword_masked(HWIO_PREF_BASE_UPPER_REG_ADDR(x), HWIO_PREF_BASE_UPPER_REG_RMSK)
#define HWIO_PREF_BASE_UPPER_REG_INM(x, m)      \
        in_dword_masked(HWIO_PREF_BASE_UPPER_REG_ADDR(x), m)
#define HWIO_PREF_BASE_UPPER_REG_OUT(x, v)      \
        out_dword(HWIO_PREF_BASE_UPPER_REG_ADDR(x),v)
#define HWIO_PREF_BASE_UPPER_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PREF_BASE_UPPER_REG_ADDR(x),m,v,HWIO_PREF_BASE_UPPER_REG_IN(x))
#define HWIO_PREF_BASE_UPPER_REG_PREF_MEM_BASE_UPPER_BMSK                                                0xffffffff
#define HWIO_PREF_BASE_UPPER_REG_PREF_MEM_BASE_UPPER_SHFT                                                       0x0

#define HWIO_PREF_LIMIT_UPPER_REG_ADDR(x)                                                                ((x) + 0x0000002c)
#define HWIO_PREF_LIMIT_UPPER_REG_RMSK                                                                   0xffffffff
#define HWIO_PREF_LIMIT_UPPER_REG_ATTR                                                                          0x3
#define HWIO_PREF_LIMIT_UPPER_REG_IN(x)      \
        in_dword_masked(HWIO_PREF_LIMIT_UPPER_REG_ADDR(x), HWIO_PREF_LIMIT_UPPER_REG_RMSK)
#define HWIO_PREF_LIMIT_UPPER_REG_INM(x, m)      \
        in_dword_masked(HWIO_PREF_LIMIT_UPPER_REG_ADDR(x), m)
#define HWIO_PREF_LIMIT_UPPER_REG_OUT(x, v)      \
        out_dword(HWIO_PREF_LIMIT_UPPER_REG_ADDR(x),v)
#define HWIO_PREF_LIMIT_UPPER_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PREF_LIMIT_UPPER_REG_ADDR(x),m,v,HWIO_PREF_LIMIT_UPPER_REG_IN(x))
#define HWIO_PREF_LIMIT_UPPER_REG_PREF_MEM_LIMIT_UPPER_BMSK                                              0xffffffff
#define HWIO_PREF_LIMIT_UPPER_REG_PREF_MEM_LIMIT_UPPER_SHFT                                                     0x0

#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_ADDR(x)                                                    ((x) + 0x00000030)
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_RMSK                                                       0xffffffff
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_ATTR                                                              0x3
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_IN(x)      \
        in_dword_masked(HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_ADDR(x), HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_RMSK)
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_INM(x, m)      \
        in_dword_masked(HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_ADDR(x), m)
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_OUT(x, v)      \
        out_dword(HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_ADDR(x),v)
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_ADDR(x),m,v,HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_IN(x))
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_IO_LIMIT_UPPER_BMSK                                        0xffff0000
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_IO_LIMIT_UPPER_SHFT                                              0x10
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_IO_BASE_UPPER_BMSK                                             0xffff
#define HWIO_IO_LIMIT_UPPER_IO_BASE_UPPER_REG_IO_BASE_UPPER_SHFT                                                0x0

#define HWIO_TYPE1_CAP_PTR_REG_ADDR(x)                                                                   ((x) + 0x00000034)
#define HWIO_TYPE1_CAP_PTR_REG_RMSK                                                                      0xffffffff
#define HWIO_TYPE1_CAP_PTR_REG_ATTR                                                                             0x3
#define HWIO_TYPE1_CAP_PTR_REG_IN(x)      \
        in_dword_masked(HWIO_TYPE1_CAP_PTR_REG_ADDR(x), HWIO_TYPE1_CAP_PTR_REG_RMSK)
#define HWIO_TYPE1_CAP_PTR_REG_INM(x, m)      \
        in_dword_masked(HWIO_TYPE1_CAP_PTR_REG_ADDR(x), m)
#define HWIO_TYPE1_CAP_PTR_REG_OUT(x, v)      \
        out_dword(HWIO_TYPE1_CAP_PTR_REG_ADDR(x),v)
#define HWIO_TYPE1_CAP_PTR_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TYPE1_CAP_PTR_REG_ADDR(x),m,v,HWIO_TYPE1_CAP_PTR_REG_IN(x))
#define HWIO_TYPE1_CAP_PTR_REG_RSVDP_8_BMSK                                                              0xffffff00
#define HWIO_TYPE1_CAP_PTR_REG_RSVDP_8_SHFT                                                                     0x8
#define HWIO_TYPE1_CAP_PTR_REG_CAP_POINTER_BMSK                                                                0xff
#define HWIO_TYPE1_CAP_PTR_REG_CAP_POINTER_SHFT                                                                 0x0

#define HWIO_TYPE1_EXP_ROM_BASE_REG_ADDR(x)                                                              ((x) + 0x00000038)
#define HWIO_TYPE1_EXP_ROM_BASE_REG_RMSK                                                                 0xffffffff
#define HWIO_TYPE1_EXP_ROM_BASE_REG_ATTR                                                                        0x3
#define HWIO_TYPE1_EXP_ROM_BASE_REG_IN(x)      \
        in_dword_masked(HWIO_TYPE1_EXP_ROM_BASE_REG_ADDR(x), HWIO_TYPE1_EXP_ROM_BASE_REG_RMSK)
#define HWIO_TYPE1_EXP_ROM_BASE_REG_INM(x, m)      \
        in_dword_masked(HWIO_TYPE1_EXP_ROM_BASE_REG_ADDR(x), m)
#define HWIO_TYPE1_EXP_ROM_BASE_REG_OUT(x, v)      \
        out_dword(HWIO_TYPE1_EXP_ROM_BASE_REG_ADDR(x),v)
#define HWIO_TYPE1_EXP_ROM_BASE_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TYPE1_EXP_ROM_BASE_REG_ADDR(x),m,v,HWIO_TYPE1_EXP_ROM_BASE_REG_IN(x))
#define HWIO_TYPE1_EXP_ROM_BASE_REG_EXP_ROM_BASE_ADDRESS_BMSK                                            0xfffff800
#define HWIO_TYPE1_EXP_ROM_BASE_REG_EXP_ROM_BASE_ADDRESS_SHFT                                                   0xb
#define HWIO_TYPE1_EXP_ROM_BASE_REG_RSVDP_1_BMSK                                                              0x7fe
#define HWIO_TYPE1_EXP_ROM_BASE_REG_RSVDP_1_SHFT                                                                0x1
#define HWIO_TYPE1_EXP_ROM_BASE_REG_ROM_BAR_ENABLE_BMSK                                                         0x1
#define HWIO_TYPE1_EXP_ROM_BASE_REG_ROM_BAR_ENABLE_SHFT                                                         0x0

#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ADDR(x)                                                    ((x) + 0x0000003c)
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_RMSK                                                       0xffffffff
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ATTR                                                              0x3
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_IN(x)      \
        in_dword_masked(HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ADDR(x), HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_RMSK)
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_INM(x, m)      \
        in_dword_masked(HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ADDR(x), m)
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_OUT(x, v)      \
        out_dword(HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ADDR(x),v)
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ADDR(x),m,v,HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_IN(x))
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_BRIDGE_CTRL_RESERV_BMSK                                    0xff800000
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_BRIDGE_CTRL_RESERV_SHFT                                          0x17
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_SBR_BMSK                                                     0x400000
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_SBR_SHFT                                                         0x16
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_MSTR_ABORT_MODE_BMSK                                         0x200000
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_MSTR_ABORT_MODE_SHFT                                             0x15
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_VGA_16B_DEC_BMSK                                             0x100000
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_VGA_16B_DEC_SHFT                                                 0x14
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_VGA_EN_BMSK                                                   0x80000
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_VGA_EN_SHFT                                                      0x13
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ISA_EN_BMSK                                                   0x40000
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ISA_EN_SHFT                                                      0x12
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_SERR_EN_BMSK                                                  0x20000
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_SERR_EN_SHFT                                                     0x11
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_PERE_BMSK                                                     0x10000
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_PERE_SHFT                                                        0x10
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_INT_PIN_BMSK                                                   0xff00
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_INT_PIN_SHFT                                                      0x8
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_INT_LINE_BMSK                                                    0xff
#define HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_INT_LINE_SHFT                                                     0x0

#define HWIO_VC_BASE_ADDR(x)                                                                             ((x) + 0x00000148)
#define HWIO_VC_BASE_RMSK                                                                                0xffffffff
#define HWIO_VC_BASE_ATTR                                                                                       0x3
#define HWIO_VC_BASE_IN(x)      \
        in_dword_masked(HWIO_VC_BASE_ADDR(x), HWIO_VC_BASE_RMSK)
#define HWIO_VC_BASE_INM(x, m)      \
        in_dword_masked(HWIO_VC_BASE_ADDR(x), m)
#define HWIO_VC_BASE_OUT(x, v)      \
        out_dword(HWIO_VC_BASE_ADDR(x),v)
#define HWIO_VC_BASE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC_BASE_ADDR(x),m,v,HWIO_VC_BASE_IN(x))
#define HWIO_VC_BASE_VC_NEXT_OFFSET_BMSK                                                                 0xfff00000
#define HWIO_VC_BASE_VC_NEXT_OFFSET_SHFT                                                                       0x14
#define HWIO_VC_BASE_VC_CAP_VERSION_BMSK                                                                    0xf0000
#define HWIO_VC_BASE_VC_CAP_VERSION_SHFT                                                                       0x10
#define HWIO_VC_BASE_VC_PCIE_EXTENDED_CAP_ID_BMSK                                                            0xffff
#define HWIO_VC_BASE_VC_PCIE_EXTENDED_CAP_ID_SHFT                                                               0x0

#define HWIO_VC_CAPABILITIES_REG_1_ADDR(x)                                                               ((x) + 0x0000014c)
#define HWIO_VC_CAPABILITIES_REG_1_RMSK                                                                  0xffffffff
#define HWIO_VC_CAPABILITIES_REG_1_ATTR                                                                         0x3
#define HWIO_VC_CAPABILITIES_REG_1_IN(x)      \
        in_dword_masked(HWIO_VC_CAPABILITIES_REG_1_ADDR(x), HWIO_VC_CAPABILITIES_REG_1_RMSK)
#define HWIO_VC_CAPABILITIES_REG_1_INM(x, m)      \
        in_dword_masked(HWIO_VC_CAPABILITIES_REG_1_ADDR(x), m)
#define HWIO_VC_CAPABILITIES_REG_1_OUT(x, v)      \
        out_dword(HWIO_VC_CAPABILITIES_REG_1_ADDR(x),v)
#define HWIO_VC_CAPABILITIES_REG_1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC_CAPABILITIES_REG_1_ADDR(x),m,v,HWIO_VC_CAPABILITIES_REG_1_IN(x))
#define HWIO_VC_CAPABILITIES_REG_1_RSVDP_12_BMSK                                                         0xfffff000
#define HWIO_VC_CAPABILITIES_REG_1_RSVDP_12_SHFT                                                                0xc
#define HWIO_VC_CAPABILITIES_REG_1_VC_PORT_ARBI_TBL_ENTRY_SIZE_BMSK                                           0xc00
#define HWIO_VC_CAPABILITIES_REG_1_VC_PORT_ARBI_TBL_ENTRY_SIZE_SHFT                                             0xa
#define HWIO_VC_CAPABILITIES_REG_1_VC_REFERENCE_CLOCK_BMSK                                                    0x300
#define HWIO_VC_CAPABILITIES_REG_1_VC_REFERENCE_CLOCK_SHFT                                                      0x8
#define HWIO_VC_CAPABILITIES_REG_1_RSVDP_7_BMSK                                                                0x80
#define HWIO_VC_CAPABILITIES_REG_1_RSVDP_7_SHFT                                                                 0x7
#define HWIO_VC_CAPABILITIES_REG_1_VC_LOW_PRI_EXT_VC_CNT_BMSK                                                  0x70
#define HWIO_VC_CAPABILITIES_REG_1_VC_LOW_PRI_EXT_VC_CNT_SHFT                                                   0x4
#define HWIO_VC_CAPABILITIES_REG_1_RSVDP_3_BMSK                                                                 0x8
#define HWIO_VC_CAPABILITIES_REG_1_RSVDP_3_SHFT                                                                 0x3
#define HWIO_VC_CAPABILITIES_REG_1_VC_EXT_VC_CNT_BMSK                                                           0x7
#define HWIO_VC_CAPABILITIES_REG_1_VC_EXT_VC_CNT_SHFT                                                           0x0

#define HWIO_VC_CAPABILITIES_REG_2_ADDR(x)                                                               ((x) + 0x00000150)
#define HWIO_VC_CAPABILITIES_REG_2_RMSK                                                                  0xffffffff
#define HWIO_VC_CAPABILITIES_REG_2_ATTR                                                                         0x3
#define HWIO_VC_CAPABILITIES_REG_2_IN(x)      \
        in_dword_masked(HWIO_VC_CAPABILITIES_REG_2_ADDR(x), HWIO_VC_CAPABILITIES_REG_2_RMSK)
#define HWIO_VC_CAPABILITIES_REG_2_INM(x, m)      \
        in_dword_masked(HWIO_VC_CAPABILITIES_REG_2_ADDR(x), m)
#define HWIO_VC_CAPABILITIES_REG_2_OUT(x, v)      \
        out_dword(HWIO_VC_CAPABILITIES_REG_2_ADDR(x),v)
#define HWIO_VC_CAPABILITIES_REG_2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC_CAPABILITIES_REG_2_ADDR(x),m,v,HWIO_VC_CAPABILITIES_REG_2_IN(x))
#define HWIO_VC_CAPABILITIES_REG_2_VC_ARBI_TABLE_OFFSET_BMSK                                             0xff000000
#define HWIO_VC_CAPABILITIES_REG_2_VC_ARBI_TABLE_OFFSET_SHFT                                                   0x18
#define HWIO_VC_CAPABILITIES_REG_2_RSVDP_4_BMSK                                                            0xfffff0
#define HWIO_VC_CAPABILITIES_REG_2_RSVDP_4_SHFT                                                                 0x4
#define HWIO_VC_CAPABILITIES_REG_2_VC_ARBI_CAP_BMSK                                                             0xf
#define HWIO_VC_CAPABILITIES_REG_2_VC_ARBI_CAP_SHFT                                                             0x0

#define HWIO_VC_STATUS_CONTROL_REG_ADDR(x)                                                               ((x) + 0x00000154)
#define HWIO_VC_STATUS_CONTROL_REG_RMSK                                                                  0xffffffff
#define HWIO_VC_STATUS_CONTROL_REG_ATTR                                                                         0x3
#define HWIO_VC_STATUS_CONTROL_REG_IN(x)      \
        in_dword_masked(HWIO_VC_STATUS_CONTROL_REG_ADDR(x), HWIO_VC_STATUS_CONTROL_REG_RMSK)
#define HWIO_VC_STATUS_CONTROL_REG_INM(x, m)      \
        in_dword_masked(HWIO_VC_STATUS_CONTROL_REG_ADDR(x), m)
#define HWIO_VC_STATUS_CONTROL_REG_OUT(x, v)      \
        out_dword(HWIO_VC_STATUS_CONTROL_REG_ADDR(x),v)
#define HWIO_VC_STATUS_CONTROL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC_STATUS_CONTROL_REG_ADDR(x),m,v,HWIO_VC_STATUS_CONTROL_REG_IN(x))
#define HWIO_VC_STATUS_CONTROL_REG_RSVDP_17_BMSK                                                         0xfffe0000
#define HWIO_VC_STATUS_CONTROL_REG_RSVDP_17_SHFT                                                               0x11
#define HWIO_VC_STATUS_CONTROL_REG_VC_ARBI_TABLE_STATUS_BMSK                                                0x10000
#define HWIO_VC_STATUS_CONTROL_REG_VC_ARBI_TABLE_STATUS_SHFT                                                   0x10
#define HWIO_VC_STATUS_CONTROL_REG_RSVDP_4_BMSK                                                              0xfff0
#define HWIO_VC_STATUS_CONTROL_REG_RSVDP_4_SHFT                                                                 0x4
#define HWIO_VC_STATUS_CONTROL_REG_VC_ARBI_SELECT_BMSK                                                          0xe
#define HWIO_VC_STATUS_CONTROL_REG_VC_ARBI_SELECT_SHFT                                                          0x1
#define HWIO_VC_STATUS_CONTROL_REG_VC_LOAD_VC_ARBI_TABLE_BMSK                                                   0x1
#define HWIO_VC_STATUS_CONTROL_REG_VC_LOAD_VC_ARBI_TABLE_SHFT                                                   0x0

#define HWIO_RESOURCE_CAP_REG_VC0_ADDR(x)                                                                ((x) + 0x00000158)
#define HWIO_RESOURCE_CAP_REG_VC0_RMSK                                                                   0xffffffff
#define HWIO_RESOURCE_CAP_REG_VC0_ATTR                                                                          0x1
#define HWIO_RESOURCE_CAP_REG_VC0_IN(x)      \
        in_dword_masked(HWIO_RESOURCE_CAP_REG_VC0_ADDR(x), HWIO_RESOURCE_CAP_REG_VC0_RMSK)
#define HWIO_RESOURCE_CAP_REG_VC0_INM(x, m)      \
        in_dword_masked(HWIO_RESOURCE_CAP_REG_VC0_ADDR(x), m)
#define HWIO_RESOURCE_CAP_REG_VC0_VC_PORT_ARBI_TABLE_VC0_BMSK                                            0xff000000
#define HWIO_RESOURCE_CAP_REG_VC0_VC_PORT_ARBI_TABLE_VC0_SHFT                                                  0x18
#define HWIO_RESOURCE_CAP_REG_VC0_RSVDP_22_BMSK                                                            0xc00000
#define HWIO_RESOURCE_CAP_REG_VC0_RSVDP_22_SHFT                                                                0x16
#define HWIO_RESOURCE_CAP_REG_VC0_VC_MAX_TIME_SLOT_VC0_BMSK                                                0x3f0000
#define HWIO_RESOURCE_CAP_REG_VC0_VC_MAX_TIME_SLOT_VC0_SHFT                                                    0x10
#define HWIO_RESOURCE_CAP_REG_VC0_VC_REJECT_SNOOP_TRANS_VC0_BMSK                                             0x8000
#define HWIO_RESOURCE_CAP_REG_VC0_VC_REJECT_SNOOP_TRANS_VC0_SHFT                                                0xf
#define HWIO_RESOURCE_CAP_REG_VC0_RSVDP_8_BMSK                                                               0x7f00
#define HWIO_RESOURCE_CAP_REG_VC0_RSVDP_8_SHFT                                                                  0x8
#define HWIO_RESOURCE_CAP_REG_VC0_VC_PORT_ARBI_CAP_VC0_BMSK                                                    0xff
#define HWIO_RESOURCE_CAP_REG_VC0_VC_PORT_ARBI_CAP_VC0_SHFT                                                     0x0

#define HWIO_RESOURCE_CON_REG_VC0_ADDR(x)                                                                ((x) + 0x0000015c)
#define HWIO_RESOURCE_CON_REG_VC0_RMSK                                                                   0xffffffff
#define HWIO_RESOURCE_CON_REG_VC0_ATTR                                                                          0x3
#define HWIO_RESOURCE_CON_REG_VC0_IN(x)      \
        in_dword_masked(HWIO_RESOURCE_CON_REG_VC0_ADDR(x), HWIO_RESOURCE_CON_REG_VC0_RMSK)
#define HWIO_RESOURCE_CON_REG_VC0_INM(x, m)      \
        in_dword_masked(HWIO_RESOURCE_CON_REG_VC0_ADDR(x), m)
#define HWIO_RESOURCE_CON_REG_VC0_OUT(x, v)      \
        out_dword(HWIO_RESOURCE_CON_REG_VC0_ADDR(x),v)
#define HWIO_RESOURCE_CON_REG_VC0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RESOURCE_CON_REG_VC0_ADDR(x),m,v,HWIO_RESOURCE_CON_REG_VC0_IN(x))
#define HWIO_RESOURCE_CON_REG_VC0_VC_ENABLE_VC0_BMSK                                                     0x80000000
#define HWIO_RESOURCE_CON_REG_VC0_VC_ENABLE_VC0_SHFT                                                           0x1f
#define HWIO_RESOURCE_CON_REG_VC0_RSVDP_27_BMSK                                                          0x78000000
#define HWIO_RESOURCE_CON_REG_VC0_RSVDP_27_SHFT                                                                0x1b
#define HWIO_RESOURCE_CON_REG_VC0_VC_ID_VC_BMSK                                                           0x7000000
#define HWIO_RESOURCE_CON_REG_VC0_VC_ID_VC_SHFT                                                                0x18
#define HWIO_RESOURCE_CON_REG_VC0_RSVDP_18_BMSK                                                            0xfc0000
#define HWIO_RESOURCE_CON_REG_VC0_RSVDP_18_SHFT                                                                0x12
#define HWIO_RESOURCE_CON_REG_VC0_VC_PORT_ARBI_SELECT_VC0_BMSK                                              0x20000
#define HWIO_RESOURCE_CON_REG_VC0_VC_PORT_ARBI_SELECT_VC0_SHFT                                                 0x11
#define HWIO_RESOURCE_CON_REG_VC0_VC_LOAD_PORT_ARBI_TABLE_VC0_BMSK                                          0x10000
#define HWIO_RESOURCE_CON_REG_VC0_VC_LOAD_PORT_ARBI_TABLE_VC0_SHFT                                             0x10
#define HWIO_RESOURCE_CON_REG_VC0_RSVDP_8_BMSK                                                               0xff00
#define HWIO_RESOURCE_CON_REG_VC0_RSVDP_8_SHFT                                                                  0x8
#define HWIO_RESOURCE_CON_REG_VC0_VC_TC_MAP_VC0_BIT1_BMSK                                                      0xfe
#define HWIO_RESOURCE_CON_REG_VC0_VC_TC_MAP_VC0_BIT1_SHFT                                                       0x1
#define HWIO_RESOURCE_CON_REG_VC0_VC_TC_MAP_VC0_BMSK                                                            0x1
#define HWIO_RESOURCE_CON_REG_VC0_VC_TC_MAP_VC0_SHFT                                                            0x0

#define HWIO_RESOURCE_STATUS_REG_VC0_ADDR(x)                                                             ((x) + 0x00000160)
#define HWIO_RESOURCE_STATUS_REG_VC0_RMSK                                                                0xffffffff
#define HWIO_RESOURCE_STATUS_REG_VC0_ATTR                                                                       0x1
#define HWIO_RESOURCE_STATUS_REG_VC0_IN(x)      \
        in_dword_masked(HWIO_RESOURCE_STATUS_REG_VC0_ADDR(x), HWIO_RESOURCE_STATUS_REG_VC0_RMSK)
#define HWIO_RESOURCE_STATUS_REG_VC0_INM(x, m)      \
        in_dword_masked(HWIO_RESOURCE_STATUS_REG_VC0_ADDR(x), m)
#define HWIO_RESOURCE_STATUS_REG_VC0_RSVDP_18_BMSK                                                       0xfffc0000
#define HWIO_RESOURCE_STATUS_REG_VC0_RSVDP_18_SHFT                                                             0x12
#define HWIO_RESOURCE_STATUS_REG_VC0_VC_NEGO_PENDING_VC0_BMSK                                               0x20000
#define HWIO_RESOURCE_STATUS_REG_VC0_VC_NEGO_PENDING_VC0_SHFT                                                  0x11
#define HWIO_RESOURCE_STATUS_REG_VC0_VC_PORT_ARBI_TABLE_STATUS_VC0_BMSK                                     0x10000
#define HWIO_RESOURCE_STATUS_REG_VC0_VC_PORT_ARBI_TABLE_STATUS_VC0_SHFT                                        0x10
#define HWIO_RESOURCE_STATUS_REG_VC0_RSVDP_0_BMSK                                                            0xffff
#define HWIO_RESOURCE_STATUS_REG_VC0_RSVDP_0_SHFT                                                               0x0

#define HWIO_RESOURCE_CAP_REG_VC1_ADDR(x)                                                                ((x) + 0x00000164)
#define HWIO_RESOURCE_CAP_REG_VC1_RMSK                                                                   0xffffffff
#define HWIO_RESOURCE_CAP_REG_VC1_ATTR                                                                          0x1
#define HWIO_RESOURCE_CAP_REG_VC1_IN(x)      \
        in_dword_masked(HWIO_RESOURCE_CAP_REG_VC1_ADDR(x), HWIO_RESOURCE_CAP_REG_VC1_RMSK)
#define HWIO_RESOURCE_CAP_REG_VC1_INM(x, m)      \
        in_dword_masked(HWIO_RESOURCE_CAP_REG_VC1_ADDR(x), m)
#define HWIO_RESOURCE_CAP_REG_VC1_VC_PORT_ARBI_TABLE_VC1_BMSK                                            0xff000000
#define HWIO_RESOURCE_CAP_REG_VC1_VC_PORT_ARBI_TABLE_VC1_SHFT                                                  0x18
#define HWIO_RESOURCE_CAP_REG_VC1_RSVDP_22_BMSK                                                            0xc00000
#define HWIO_RESOURCE_CAP_REG_VC1_RSVDP_22_SHFT                                                                0x16
#define HWIO_RESOURCE_CAP_REG_VC1_VC_MAX_TIME_SLOT_VC1_BMSK                                                0x3f0000
#define HWIO_RESOURCE_CAP_REG_VC1_VC_MAX_TIME_SLOT_VC1_SHFT                                                    0x10
#define HWIO_RESOURCE_CAP_REG_VC1_VC_REJECT_SNOOP_TRANS_VC1_BMSK                                             0x8000
#define HWIO_RESOURCE_CAP_REG_VC1_VC_REJECT_SNOOP_TRANS_VC1_SHFT                                                0xf
#define HWIO_RESOURCE_CAP_REG_VC1_RSVDP_8_BMSK                                                               0x7f00
#define HWIO_RESOURCE_CAP_REG_VC1_RSVDP_8_SHFT                                                                  0x8
#define HWIO_RESOURCE_CAP_REG_VC1_VC_PORT_ARBI_CAP_VC1_BMSK                                                    0xff
#define HWIO_RESOURCE_CAP_REG_VC1_VC_PORT_ARBI_CAP_VC1_SHFT                                                     0x0

#define HWIO_RESOURCE_CON_REG_VC1_ADDR(x)                                                                ((x) + 0x00000168)
#define HWIO_RESOURCE_CON_REG_VC1_RMSK                                                                   0xffffffff
#define HWIO_RESOURCE_CON_REG_VC1_ATTR                                                                          0x3
#define HWIO_RESOURCE_CON_REG_VC1_IN(x)      \
        in_dword_masked(HWIO_RESOURCE_CON_REG_VC1_ADDR(x), HWIO_RESOURCE_CON_REG_VC1_RMSK)
#define HWIO_RESOURCE_CON_REG_VC1_INM(x, m)      \
        in_dword_masked(HWIO_RESOURCE_CON_REG_VC1_ADDR(x), m)
#define HWIO_RESOURCE_CON_REG_VC1_OUT(x, v)      \
        out_dword(HWIO_RESOURCE_CON_REG_VC1_ADDR(x),v)
#define HWIO_RESOURCE_CON_REG_VC1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_RESOURCE_CON_REG_VC1_ADDR(x),m,v,HWIO_RESOURCE_CON_REG_VC1_IN(x))
#define HWIO_RESOURCE_CON_REG_VC1_VC_ENABLE_VC1_BMSK                                                     0x80000000
#define HWIO_RESOURCE_CON_REG_VC1_VC_ENABLE_VC1_SHFT                                                           0x1f
#define HWIO_RESOURCE_CON_REG_VC1_RSVDP_27_BMSK                                                          0x78000000
#define HWIO_RESOURCE_CON_REG_VC1_RSVDP_27_SHFT                                                                0x1b
#define HWIO_RESOURCE_CON_REG_VC1_VC_ID_VC1_BMSK                                                          0x7000000
#define HWIO_RESOURCE_CON_REG_VC1_VC_ID_VC1_SHFT                                                               0x18
#define HWIO_RESOURCE_CON_REG_VC1_RSVDP_20_BMSK                                                            0xf00000
#define HWIO_RESOURCE_CON_REG_VC1_RSVDP_20_SHFT                                                                0x14
#define HWIO_RESOURCE_CON_REG_VC1_VC_PORT_ARBI_SELECT_VC1_BMSK                                              0xe0000
#define HWIO_RESOURCE_CON_REG_VC1_VC_PORT_ARBI_SELECT_VC1_SHFT                                                 0x11
#define HWIO_RESOURCE_CON_REG_VC1_VC_LOAD_PORT_ARBI_TABLE_VC1_BMSK                                          0x10000
#define HWIO_RESOURCE_CON_REG_VC1_VC_LOAD_PORT_ARBI_TABLE_VC1_SHFT                                             0x10
#define HWIO_RESOURCE_CON_REG_VC1_RSVDP_8_BMSK                                                               0xff00
#define HWIO_RESOURCE_CON_REG_VC1_RSVDP_8_SHFT                                                                  0x8
#define HWIO_RESOURCE_CON_REG_VC1_VC_TC_MAP_VC1_BIT1_BMSK                                                      0xfe
#define HWIO_RESOURCE_CON_REG_VC1_VC_TC_MAP_VC1_BIT1_SHFT                                                       0x1
#define HWIO_RESOURCE_CON_REG_VC1_VC_TC_MAP_VC1_BMSK                                                            0x1
#define HWIO_RESOURCE_CON_REG_VC1_VC_TC_MAP_VC1_SHFT                                                            0x0

#define HWIO_RESOURCE_STATUS_REG_VC1_ADDR(x)                                                             ((x) + 0x0000016c)
#define HWIO_RESOURCE_STATUS_REG_VC1_RMSK                                                                0xffffffff
#define HWIO_RESOURCE_STATUS_REG_VC1_ATTR                                                                       0x1
#define HWIO_RESOURCE_STATUS_REG_VC1_IN(x)      \
        in_dword_masked(HWIO_RESOURCE_STATUS_REG_VC1_ADDR(x), HWIO_RESOURCE_STATUS_REG_VC1_RMSK)
#define HWIO_RESOURCE_STATUS_REG_VC1_INM(x, m)      \
        in_dword_masked(HWIO_RESOURCE_STATUS_REG_VC1_ADDR(x), m)
#define HWIO_RESOURCE_STATUS_REG_VC1_RSVDP_18_BMSK                                                       0xfffc0000
#define HWIO_RESOURCE_STATUS_REG_VC1_RSVDP_18_SHFT                                                             0x12
#define HWIO_RESOURCE_STATUS_REG_VC1_VC_NEGO_PENDING_VC1_BMSK                                               0x20000
#define HWIO_RESOURCE_STATUS_REG_VC1_VC_NEGO_PENDING_VC1_SHFT                                                  0x11
#define HWIO_RESOURCE_STATUS_REG_VC1_VC_PORT_ARBI_TABLE_STATUS_VC1_BMSK                                     0x10000
#define HWIO_RESOURCE_STATUS_REG_VC1_VC_PORT_ARBI_TABLE_STATUS_VC1_SHFT                                        0x10
#define HWIO_RESOURCE_STATUS_REG_VC1_RSVDP_0_BMSK                                                            0xffff
#define HWIO_RESOURCE_STATUS_REG_VC1_RSVDP_0_SHFT                                                               0x0

#define HWIO_SPCIE_CAP_HEADER_REG_ADDR(x)                                                                ((x) + 0x00000178)
#define HWIO_SPCIE_CAP_HEADER_REG_RMSK                                                                   0xffffffff
#define HWIO_SPCIE_CAP_HEADER_REG_ATTR                                                                          0x3
#define HWIO_SPCIE_CAP_HEADER_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_HEADER_REG_ADDR(x), HWIO_SPCIE_CAP_HEADER_REG_RMSK)
#define HWIO_SPCIE_CAP_HEADER_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_HEADER_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_HEADER_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_HEADER_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_HEADER_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_HEADER_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_HEADER_REG_IN(x))
#define HWIO_SPCIE_CAP_HEADER_REG_NEXT_OFFSET_BMSK                                                       0xfff00000
#define HWIO_SPCIE_CAP_HEADER_REG_NEXT_OFFSET_SHFT                                                             0x14
#define HWIO_SPCIE_CAP_HEADER_REG_CAP_VERSION_BMSK                                                          0xf0000
#define HWIO_SPCIE_CAP_HEADER_REG_CAP_VERSION_SHFT                                                             0x10
#define HWIO_SPCIE_CAP_HEADER_REG_EXTENDED_CAP_ID_BMSK                                                       0xffff
#define HWIO_SPCIE_CAP_HEADER_REG_EXTENDED_CAP_ID_SHFT                                                          0x0

#define HWIO_LINK_CONTROL3_REG_ADDR(x)                                                                   ((x) + 0x0000017c)
#define HWIO_LINK_CONTROL3_REG_RMSK                                                                      0xffffffff
#define HWIO_LINK_CONTROL3_REG_ATTR                                                                             0x3
#define HWIO_LINK_CONTROL3_REG_IN(x)      \
        in_dword_masked(HWIO_LINK_CONTROL3_REG_ADDR(x), HWIO_LINK_CONTROL3_REG_RMSK)
#define HWIO_LINK_CONTROL3_REG_INM(x, m)      \
        in_dword_masked(HWIO_LINK_CONTROL3_REG_ADDR(x), m)
#define HWIO_LINK_CONTROL3_REG_OUT(x, v)      \
        out_dword(HWIO_LINK_CONTROL3_REG_ADDR(x),v)
#define HWIO_LINK_CONTROL3_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LINK_CONTROL3_REG_ADDR(x),m,v,HWIO_LINK_CONTROL3_REG_IN(x))
#define HWIO_LINK_CONTROL3_REG_RSVDP_2_BMSK                                                              0xfffffffc
#define HWIO_LINK_CONTROL3_REG_RSVDP_2_SHFT                                                                     0x2
#define HWIO_LINK_CONTROL3_REG_EQ_REQ_INT_EN_BMSK                                                               0x2
#define HWIO_LINK_CONTROL3_REG_EQ_REQ_INT_EN_SHFT                                                               0x1
#define HWIO_LINK_CONTROL3_REG_PERFORM_EQ_BMSK                                                                  0x1
#define HWIO_LINK_CONTROL3_REG_PERFORM_EQ_SHFT                                                                  0x0

#define HWIO_LANE_ERR_STATUS_REG_ADDR(x)                                                                 ((x) + 0x00000180)
#define HWIO_LANE_ERR_STATUS_REG_RMSK                                                                    0xffffffff
#define HWIO_LANE_ERR_STATUS_REG_ATTR                                                                           0x3
#define HWIO_LANE_ERR_STATUS_REG_IN(x)      \
        in_dword_masked(HWIO_LANE_ERR_STATUS_REG_ADDR(x), HWIO_LANE_ERR_STATUS_REG_RMSK)
#define HWIO_LANE_ERR_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_LANE_ERR_STATUS_REG_ADDR(x), m)
#define HWIO_LANE_ERR_STATUS_REG_OUT(x, v)      \
        out_dword(HWIO_LANE_ERR_STATUS_REG_ADDR(x),v)
#define HWIO_LANE_ERR_STATUS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LANE_ERR_STATUS_REG_ADDR(x),m,v,HWIO_LANE_ERR_STATUS_REG_IN(x))
#define HWIO_LANE_ERR_STATUS_REG_RSVDP_LANE_ERR_STATUS_BMSK                                              0xffff0000
#define HWIO_LANE_ERR_STATUS_REG_RSVDP_LANE_ERR_STATUS_SHFT                                                    0x10
#define HWIO_LANE_ERR_STATUS_REG_LANE_ERR_STATUS_BMSK                                                        0xffff
#define HWIO_LANE_ERR_STATUS_REG_LANE_ERR_STATUS_SHFT                                                           0x0

#define HWIO_SPCIE_CAP_OFF_0CH_REG_ADDR(x)                                                               ((x) + 0x00000184)
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RMSK                                                                  0xffffffff
#define HWIO_SPCIE_CAP_OFF_0CH_REG_ATTR                                                                         0x3
#define HWIO_SPCIE_CAP_OFF_0CH_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_0CH_REG_ADDR(x), HWIO_SPCIE_CAP_OFF_0CH_REG_RMSK)
#define HWIO_SPCIE_CAP_OFF_0CH_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_0CH_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_OFF_0CH_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_OFF_0CH_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_OFF_0CH_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_OFF_0CH_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_OFF_0CH_REG_IN(x))
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RSVDP_31_BMSK                                                         0x80000000
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RSVDP_31_SHFT                                                               0x1f
#define HWIO_SPCIE_CAP_OFF_0CH_REG_USP_RX_PRESET_HINT1_BMSK                                              0x70000000
#define HWIO_SPCIE_CAP_OFF_0CH_REG_USP_RX_PRESET_HINT1_SHFT                                                    0x1c
#define HWIO_SPCIE_CAP_OFF_0CH_REG_USP_TX_PRESET1_BMSK                                                    0xf000000
#define HWIO_SPCIE_CAP_OFF_0CH_REG_USP_TX_PRESET1_SHFT                                                         0x18
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_SPCIE_CAP_OFF_0CH_REG_DSP_RX_PRESET_HINT1_BMSK                                                0x700000
#define HWIO_SPCIE_CAP_OFF_0CH_REG_DSP_RX_PRESET_HINT1_SHFT                                                    0x14
#define HWIO_SPCIE_CAP_OFF_0CH_REG_DSP_TX_PRESET1_BMSK                                                      0xf0000
#define HWIO_SPCIE_CAP_OFF_0CH_REG_DSP_TX_PRESET1_SHFT                                                         0x10
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RSVDP_15_BMSK                                                             0x8000
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RSVDP_15_SHFT                                                                0xf
#define HWIO_SPCIE_CAP_OFF_0CH_REG_USP_RX_PRESET_HINT0_BMSK                                                  0x7000
#define HWIO_SPCIE_CAP_OFF_0CH_REG_USP_RX_PRESET_HINT0_SHFT                                                     0xc
#define HWIO_SPCIE_CAP_OFF_0CH_REG_USP_TX_PRESET0_BMSK                                                        0xf00
#define HWIO_SPCIE_CAP_OFF_0CH_REG_USP_TX_PRESET0_SHFT                                                          0x8
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RSVDP_7_BMSK                                                                0x80
#define HWIO_SPCIE_CAP_OFF_0CH_REG_RSVDP_7_SHFT                                                                 0x7
#define HWIO_SPCIE_CAP_OFF_0CH_REG_DSP_RX_PRESET_HINT0_BMSK                                                    0x70
#define HWIO_SPCIE_CAP_OFF_0CH_REG_DSP_RX_PRESET_HINT0_SHFT                                                     0x4
#define HWIO_SPCIE_CAP_OFF_0CH_REG_DSP_TX_PRESET0_BMSK                                                          0xf
#define HWIO_SPCIE_CAP_OFF_0CH_REG_DSP_TX_PRESET0_SHFT                                                          0x0

#define HWIO_SPCIE_CAP_OFF_10H_REG_ADDR(x)                                                               ((x) + 0x00000188)
#define HWIO_SPCIE_CAP_OFF_10H_REG_RMSK                                                                  0xffffffff
#define HWIO_SPCIE_CAP_OFF_10H_REG_ATTR                                                                         0x3
#define HWIO_SPCIE_CAP_OFF_10H_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_10H_REG_ADDR(x), HWIO_SPCIE_CAP_OFF_10H_REG_RMSK)
#define HWIO_SPCIE_CAP_OFF_10H_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_10H_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_OFF_10H_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_OFF_10H_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_OFF_10H_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_OFF_10H_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_OFF_10H_REG_IN(x))
#define HWIO_SPCIE_CAP_OFF_10H_REG_RSVDP_31_BMSK                                                         0x80000000
#define HWIO_SPCIE_CAP_OFF_10H_REG_RSVDP_31_SHFT                                                               0x1f
#define HWIO_SPCIE_CAP_OFF_10H_REG_USP_RX_PRESET_HINT3_BMSK                                              0x70000000
#define HWIO_SPCIE_CAP_OFF_10H_REG_USP_RX_PRESET_HINT3_SHFT                                                    0x1c
#define HWIO_SPCIE_CAP_OFF_10H_REG_USP_TX_PRESET3_BMSK                                                    0xf000000
#define HWIO_SPCIE_CAP_OFF_10H_REG_USP_TX_PRESET3_SHFT                                                         0x18
#define HWIO_SPCIE_CAP_OFF_10H_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_SPCIE_CAP_OFF_10H_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_SPCIE_CAP_OFF_10H_REG_DSP_RX_PRESET_HINT3_BMSK                                                0x700000
#define HWIO_SPCIE_CAP_OFF_10H_REG_DSP_RX_PRESET_HINT3_SHFT                                                    0x14
#define HWIO_SPCIE_CAP_OFF_10H_REG_DSP_TX_PRESET3_BMSK                                                      0xf0000
#define HWIO_SPCIE_CAP_OFF_10H_REG_DSP_TX_PRESET3_SHFT                                                         0x10
#define HWIO_SPCIE_CAP_OFF_10H_REG_RSVDP_15_BMSK                                                             0x8000
#define HWIO_SPCIE_CAP_OFF_10H_REG_RSVDP_15_SHFT                                                                0xf
#define HWIO_SPCIE_CAP_OFF_10H_REG_USP_RX_PRESET_HINT2_BMSK                                                  0x7000
#define HWIO_SPCIE_CAP_OFF_10H_REG_USP_RX_PRESET_HINT2_SHFT                                                     0xc
#define HWIO_SPCIE_CAP_OFF_10H_REG_USP_TX_PRESET2_BMSK                                                        0xf00
#define HWIO_SPCIE_CAP_OFF_10H_REG_USP_TX_PRESET2_SHFT                                                          0x8
#define HWIO_SPCIE_CAP_OFF_10H_REG_RSVDP_7_BMSK                                                                0x80
#define HWIO_SPCIE_CAP_OFF_10H_REG_RSVDP_7_SHFT                                                                 0x7
#define HWIO_SPCIE_CAP_OFF_10H_REG_DSP_RX_PRESET_HINT2_BMSK                                                    0x70
#define HWIO_SPCIE_CAP_OFF_10H_REG_DSP_RX_PRESET_HINT2_SHFT                                                     0x4
#define HWIO_SPCIE_CAP_OFF_10H_REG_DSP_TX_PRESET2_BMSK                                                          0xf
#define HWIO_SPCIE_CAP_OFF_10H_REG_DSP_TX_PRESET2_SHFT                                                          0x0

#define HWIO_SPCIE_CAP_OFF_14H_REG_ADDR(x)                                                               ((x) + 0x0000018c)
#define HWIO_SPCIE_CAP_OFF_14H_REG_RMSK                                                                  0xffffffff
#define HWIO_SPCIE_CAP_OFF_14H_REG_ATTR                                                                         0x3
#define HWIO_SPCIE_CAP_OFF_14H_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_14H_REG_ADDR(x), HWIO_SPCIE_CAP_OFF_14H_REG_RMSK)
#define HWIO_SPCIE_CAP_OFF_14H_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_14H_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_OFF_14H_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_OFF_14H_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_OFF_14H_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_OFF_14H_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_OFF_14H_REG_IN(x))
#define HWIO_SPCIE_CAP_OFF_14H_REG_RSVDP_31_BMSK                                                         0x80000000
#define HWIO_SPCIE_CAP_OFF_14H_REG_RSVDP_31_SHFT                                                               0x1f
#define HWIO_SPCIE_CAP_OFF_14H_REG_USP_RX_PRESET_HINT5_BMSK                                              0x70000000
#define HWIO_SPCIE_CAP_OFF_14H_REG_USP_RX_PRESET_HINT5_SHFT                                                    0x1c
#define HWIO_SPCIE_CAP_OFF_14H_REG_USP_TX_PRESET5_BMSK                                                    0xf000000
#define HWIO_SPCIE_CAP_OFF_14H_REG_USP_TX_PRESET5_SHFT                                                         0x18
#define HWIO_SPCIE_CAP_OFF_14H_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_SPCIE_CAP_OFF_14H_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_SPCIE_CAP_OFF_14H_REG_DSP_RX_PRESET_HINT5_BMSK                                                0x700000
#define HWIO_SPCIE_CAP_OFF_14H_REG_DSP_RX_PRESET_HINT5_SHFT                                                    0x14
#define HWIO_SPCIE_CAP_OFF_14H_REG_DSP_TX_PRESET5_BMSK                                                      0xf0000
#define HWIO_SPCIE_CAP_OFF_14H_REG_DSP_TX_PRESET5_SHFT                                                         0x10
#define HWIO_SPCIE_CAP_OFF_14H_REG_RSVDP_15_BMSK                                                             0x8000
#define HWIO_SPCIE_CAP_OFF_14H_REG_RSVDP_15_SHFT                                                                0xf
#define HWIO_SPCIE_CAP_OFF_14H_REG_USP_RX_PRESET_HINT4_BMSK                                                  0x7000
#define HWIO_SPCIE_CAP_OFF_14H_REG_USP_RX_PRESET_HINT4_SHFT                                                     0xc
#define HWIO_SPCIE_CAP_OFF_14H_REG_USP_TX_PRESET4_BMSK                                                        0xf00
#define HWIO_SPCIE_CAP_OFF_14H_REG_USP_TX_PRESET4_SHFT                                                          0x8
#define HWIO_SPCIE_CAP_OFF_14H_REG_RSVDP_7_BMSK                                                                0x80
#define HWIO_SPCIE_CAP_OFF_14H_REG_RSVDP_7_SHFT                                                                 0x7
#define HWIO_SPCIE_CAP_OFF_14H_REG_DSP_RX_PRESET_HINT4_BMSK                                                    0x70
#define HWIO_SPCIE_CAP_OFF_14H_REG_DSP_RX_PRESET_HINT4_SHFT                                                     0x4
#define HWIO_SPCIE_CAP_OFF_14H_REG_DSP_TX_PRESET4_BMSK                                                          0xf
#define HWIO_SPCIE_CAP_OFF_14H_REG_DSP_TX_PRESET4_SHFT                                                          0x0

#define HWIO_SPCIE_CAP_OFF_18H_REG_ADDR(x)                                                               ((x) + 0x00000190)
#define HWIO_SPCIE_CAP_OFF_18H_REG_RMSK                                                                  0xffffffff
#define HWIO_SPCIE_CAP_OFF_18H_REG_ATTR                                                                         0x3
#define HWIO_SPCIE_CAP_OFF_18H_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_18H_REG_ADDR(x), HWIO_SPCIE_CAP_OFF_18H_REG_RMSK)
#define HWIO_SPCIE_CAP_OFF_18H_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_18H_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_OFF_18H_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_OFF_18H_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_OFF_18H_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_OFF_18H_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_OFF_18H_REG_IN(x))
#define HWIO_SPCIE_CAP_OFF_18H_REG_RSVDP_31_BMSK                                                         0x80000000
#define HWIO_SPCIE_CAP_OFF_18H_REG_RSVDP_31_SHFT                                                               0x1f
#define HWIO_SPCIE_CAP_OFF_18H_REG_USP_RX_PRESET_HINT7_BMSK                                              0x70000000
#define HWIO_SPCIE_CAP_OFF_18H_REG_USP_RX_PRESET_HINT7_SHFT                                                    0x1c
#define HWIO_SPCIE_CAP_OFF_18H_REG_USP_TX_PRESET7_BMSK                                                    0xf000000
#define HWIO_SPCIE_CAP_OFF_18H_REG_USP_TX_PRESET7_SHFT                                                         0x18
#define HWIO_SPCIE_CAP_OFF_18H_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_SPCIE_CAP_OFF_18H_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_SPCIE_CAP_OFF_18H_REG_DSP_RX_PRESET_HINT7_BMSK                                                0x700000
#define HWIO_SPCIE_CAP_OFF_18H_REG_DSP_RX_PRESET_HINT7_SHFT                                                    0x14
#define HWIO_SPCIE_CAP_OFF_18H_REG_DSP_TX_PRESET7_BMSK                                                      0xf0000
#define HWIO_SPCIE_CAP_OFF_18H_REG_DSP_TX_PRESET7_SHFT                                                         0x10
#define HWIO_SPCIE_CAP_OFF_18H_REG_RSVDP_15_BMSK                                                             0x8000
#define HWIO_SPCIE_CAP_OFF_18H_REG_RSVDP_15_SHFT                                                                0xf
#define HWIO_SPCIE_CAP_OFF_18H_REG_USP_RX_PRESET_HINT6_BMSK                                                  0x7000
#define HWIO_SPCIE_CAP_OFF_18H_REG_USP_RX_PRESET_HINT6_SHFT                                                     0xc
#define HWIO_SPCIE_CAP_OFF_18H_REG_USP_TX_PRESET6_BMSK                                                        0xf00
#define HWIO_SPCIE_CAP_OFF_18H_REG_USP_TX_PRESET6_SHFT                                                          0x8
#define HWIO_SPCIE_CAP_OFF_18H_REG_RSVDP_7_BMSK                                                                0x80
#define HWIO_SPCIE_CAP_OFF_18H_REG_RSVDP_7_SHFT                                                                 0x7
#define HWIO_SPCIE_CAP_OFF_18H_REG_DSP_RX_PRESET_HINT6_BMSK                                                    0x70
#define HWIO_SPCIE_CAP_OFF_18H_REG_DSP_RX_PRESET_HINT6_SHFT                                                     0x4
#define HWIO_SPCIE_CAP_OFF_18H_REG_DSP_TX_PRESET6_BMSK                                                          0xf
#define HWIO_SPCIE_CAP_OFF_18H_REG_DSP_TX_PRESET6_SHFT                                                          0x0

#define HWIO_SPCIE_CAP_OFF_1CH_REG_ADDR(x)                                                               ((x) + 0x00000194)
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RMSK                                                                  0xffffffff
#define HWIO_SPCIE_CAP_OFF_1CH_REG_ATTR                                                                         0x3
#define HWIO_SPCIE_CAP_OFF_1CH_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_1CH_REG_ADDR(x), HWIO_SPCIE_CAP_OFF_1CH_REG_RMSK)
#define HWIO_SPCIE_CAP_OFF_1CH_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_1CH_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_OFF_1CH_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_OFF_1CH_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_OFF_1CH_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_OFF_1CH_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_OFF_1CH_REG_IN(x))
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RSVDP_31_BMSK                                                         0x80000000
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RSVDP_31_SHFT                                                               0x1f
#define HWIO_SPCIE_CAP_OFF_1CH_REG_USP_RX_PRESET_HINT9_BMSK                                              0x70000000
#define HWIO_SPCIE_CAP_OFF_1CH_REG_USP_RX_PRESET_HINT9_SHFT                                                    0x1c
#define HWIO_SPCIE_CAP_OFF_1CH_REG_USP_TX_PRESET9_BMSK                                                    0xf000000
#define HWIO_SPCIE_CAP_OFF_1CH_REG_USP_TX_PRESET9_SHFT                                                         0x18
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_SPCIE_CAP_OFF_1CH_REG_DSP_RX_PRESET_HINT9_BMSK                                                0x700000
#define HWIO_SPCIE_CAP_OFF_1CH_REG_DSP_RX_PRESET_HINT9_SHFT                                                    0x14
#define HWIO_SPCIE_CAP_OFF_1CH_REG_DSP_TX_PRESET9_BMSK                                                      0xf0000
#define HWIO_SPCIE_CAP_OFF_1CH_REG_DSP_TX_PRESET9_SHFT                                                         0x10
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RSVDP_15_BMSK                                                             0x8000
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RSVDP_15_SHFT                                                                0xf
#define HWIO_SPCIE_CAP_OFF_1CH_REG_USP_RX_PRESET_HINT8_BMSK                                                  0x7000
#define HWIO_SPCIE_CAP_OFF_1CH_REG_USP_RX_PRESET_HINT8_SHFT                                                     0xc
#define HWIO_SPCIE_CAP_OFF_1CH_REG_USP_TX_PRESET8_BMSK                                                        0xf00
#define HWIO_SPCIE_CAP_OFF_1CH_REG_USP_TX_PRESET8_SHFT                                                          0x8
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RSVDP_7_BMSK                                                                0x80
#define HWIO_SPCIE_CAP_OFF_1CH_REG_RSVDP_7_SHFT                                                                 0x7
#define HWIO_SPCIE_CAP_OFF_1CH_REG_DSP_RX_PRESET_HINT8_BMSK                                                    0x70
#define HWIO_SPCIE_CAP_OFF_1CH_REG_DSP_RX_PRESET_HINT8_SHFT                                                     0x4
#define HWIO_SPCIE_CAP_OFF_1CH_REG_DSP_TX_PRESET8_BMSK                                                          0xf
#define HWIO_SPCIE_CAP_OFF_1CH_REG_DSP_TX_PRESET8_SHFT                                                          0x0

#define HWIO_SPCIE_CAP_OFF_20H_REG_ADDR(x)                                                               ((x) + 0x00000198)
#define HWIO_SPCIE_CAP_OFF_20H_REG_RMSK                                                                  0xffffffff
#define HWIO_SPCIE_CAP_OFF_20H_REG_ATTR                                                                         0x3
#define HWIO_SPCIE_CAP_OFF_20H_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_20H_REG_ADDR(x), HWIO_SPCIE_CAP_OFF_20H_REG_RMSK)
#define HWIO_SPCIE_CAP_OFF_20H_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_20H_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_OFF_20H_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_OFF_20H_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_OFF_20H_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_OFF_20H_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_OFF_20H_REG_IN(x))
#define HWIO_SPCIE_CAP_OFF_20H_REG_RSVDP_31_BMSK                                                         0x80000000
#define HWIO_SPCIE_CAP_OFF_20H_REG_RSVDP_31_SHFT                                                               0x1f
#define HWIO_SPCIE_CAP_OFF_20H_REG_USP_RX_PRESET_HINT11_BMSK                                             0x70000000
#define HWIO_SPCIE_CAP_OFF_20H_REG_USP_RX_PRESET_HINT11_SHFT                                                   0x1c
#define HWIO_SPCIE_CAP_OFF_20H_REG_USP_TX_PRESET11_BMSK                                                   0xf000000
#define HWIO_SPCIE_CAP_OFF_20H_REG_USP_TX_PRESET11_SHFT                                                        0x18
#define HWIO_SPCIE_CAP_OFF_20H_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_SPCIE_CAP_OFF_20H_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_SPCIE_CAP_OFF_20H_REG_DSP_RX_PRESET_HINT11_BMSK                                               0x700000
#define HWIO_SPCIE_CAP_OFF_20H_REG_DSP_RX_PRESET_HINT11_SHFT                                                   0x14
#define HWIO_SPCIE_CAP_OFF_20H_REG_DSP_TX_PRESET11_BMSK                                                     0xf0000
#define HWIO_SPCIE_CAP_OFF_20H_REG_DSP_TX_PRESET11_SHFT                                                        0x10
#define HWIO_SPCIE_CAP_OFF_20H_REG_RSVDP_15_BMSK                                                             0x8000
#define HWIO_SPCIE_CAP_OFF_20H_REG_RSVDP_15_SHFT                                                                0xf
#define HWIO_SPCIE_CAP_OFF_20H_REG_USP_RX_PRESET_HINT10_BMSK                                                 0x7000
#define HWIO_SPCIE_CAP_OFF_20H_REG_USP_RX_PRESET_HINT10_SHFT                                                    0xc
#define HWIO_SPCIE_CAP_OFF_20H_REG_USP_TX_PRESET10_BMSK                                                       0xf00
#define HWIO_SPCIE_CAP_OFF_20H_REG_USP_TX_PRESET10_SHFT                                                         0x8
#define HWIO_SPCIE_CAP_OFF_20H_REG_RSVDP_7_BMSK                                                                0x80
#define HWIO_SPCIE_CAP_OFF_20H_REG_RSVDP_7_SHFT                                                                 0x7
#define HWIO_SPCIE_CAP_OFF_20H_REG_DSP_RX_PRESET_HINT10_BMSK                                                   0x70
#define HWIO_SPCIE_CAP_OFF_20H_REG_DSP_RX_PRESET_HINT10_SHFT                                                    0x4
#define HWIO_SPCIE_CAP_OFF_20H_REG_DSP_TX_PRESET10_BMSK                                                         0xf
#define HWIO_SPCIE_CAP_OFF_20H_REG_DSP_TX_PRESET10_SHFT                                                         0x0

#define HWIO_SPCIE_CAP_OFF_24H_REG_ADDR(x)                                                               ((x) + 0x0000019c)
#define HWIO_SPCIE_CAP_OFF_24H_REG_RMSK                                                                  0xffffffff
#define HWIO_SPCIE_CAP_OFF_24H_REG_ATTR                                                                         0x3
#define HWIO_SPCIE_CAP_OFF_24H_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_24H_REG_ADDR(x), HWIO_SPCIE_CAP_OFF_24H_REG_RMSK)
#define HWIO_SPCIE_CAP_OFF_24H_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_24H_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_OFF_24H_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_OFF_24H_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_OFF_24H_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_OFF_24H_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_OFF_24H_REG_IN(x))
#define HWIO_SPCIE_CAP_OFF_24H_REG_RSVDP_31_BMSK                                                         0x80000000
#define HWIO_SPCIE_CAP_OFF_24H_REG_RSVDP_31_SHFT                                                               0x1f
#define HWIO_SPCIE_CAP_OFF_24H_REG_USP_RX_PRESET_HINT13_BMSK                                             0x70000000
#define HWIO_SPCIE_CAP_OFF_24H_REG_USP_RX_PRESET_HINT13_SHFT                                                   0x1c
#define HWIO_SPCIE_CAP_OFF_24H_REG_USP_TX_PRESET13_BMSK                                                   0xf000000
#define HWIO_SPCIE_CAP_OFF_24H_REG_USP_TX_PRESET13_SHFT                                                        0x18
#define HWIO_SPCIE_CAP_OFF_24H_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_SPCIE_CAP_OFF_24H_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_SPCIE_CAP_OFF_24H_REG_DSP_RX_PRESET_HINT13_BMSK                                               0x700000
#define HWIO_SPCIE_CAP_OFF_24H_REG_DSP_RX_PRESET_HINT13_SHFT                                                   0x14
#define HWIO_SPCIE_CAP_OFF_24H_REG_DSP_TX_PRESET13_BMSK                                                     0xf0000
#define HWIO_SPCIE_CAP_OFF_24H_REG_DSP_TX_PRESET13_SHFT                                                        0x10
#define HWIO_SPCIE_CAP_OFF_24H_REG_RSVDP_15_BMSK                                                             0x8000
#define HWIO_SPCIE_CAP_OFF_24H_REG_RSVDP_15_SHFT                                                                0xf
#define HWIO_SPCIE_CAP_OFF_24H_REG_USP_RX_PRESET_HINT12_BMSK                                                 0x7000
#define HWIO_SPCIE_CAP_OFF_24H_REG_USP_RX_PRESET_HINT12_SHFT                                                    0xc
#define HWIO_SPCIE_CAP_OFF_24H_REG_USP_TX_PRESET12_BMSK                                                       0xf00
#define HWIO_SPCIE_CAP_OFF_24H_REG_USP_TX_PRESET12_SHFT                                                         0x8
#define HWIO_SPCIE_CAP_OFF_24H_REG_RSVDP_7_BMSK                                                                0x80
#define HWIO_SPCIE_CAP_OFF_24H_REG_RSVDP_7_SHFT                                                                 0x7
#define HWIO_SPCIE_CAP_OFF_24H_REG_DSP_RX_PRESET_HINT12_BMSK                                                   0x70
#define HWIO_SPCIE_CAP_OFF_24H_REG_DSP_RX_PRESET_HINT12_SHFT                                                    0x4
#define HWIO_SPCIE_CAP_OFF_24H_REG_DSP_TX_PRESET12_BMSK                                                         0xf
#define HWIO_SPCIE_CAP_OFF_24H_REG_DSP_TX_PRESET12_SHFT                                                         0x0

#define HWIO_SPCIE_CAP_OFF_28H_REG_ADDR(x)                                                               ((x) + 0x000001a0)
#define HWIO_SPCIE_CAP_OFF_28H_REG_RMSK                                                                  0xffffffff
#define HWIO_SPCIE_CAP_OFF_28H_REG_ATTR                                                                         0x3
#define HWIO_SPCIE_CAP_OFF_28H_REG_IN(x)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_28H_REG_ADDR(x), HWIO_SPCIE_CAP_OFF_28H_REG_RMSK)
#define HWIO_SPCIE_CAP_OFF_28H_REG_INM(x, m)      \
        in_dword_masked(HWIO_SPCIE_CAP_OFF_28H_REG_ADDR(x), m)
#define HWIO_SPCIE_CAP_OFF_28H_REG_OUT(x, v)      \
        out_dword(HWIO_SPCIE_CAP_OFF_28H_REG_ADDR(x),v)
#define HWIO_SPCIE_CAP_OFF_28H_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SPCIE_CAP_OFF_28H_REG_ADDR(x),m,v,HWIO_SPCIE_CAP_OFF_28H_REG_IN(x))
#define HWIO_SPCIE_CAP_OFF_28H_REG_RSVDP_31_BMSK                                                         0x80000000
#define HWIO_SPCIE_CAP_OFF_28H_REG_RSVDP_31_SHFT                                                               0x1f
#define HWIO_SPCIE_CAP_OFF_28H_REG_USP_RX_PRESET_HINT15_BMSK                                             0x70000000
#define HWIO_SPCIE_CAP_OFF_28H_REG_USP_RX_PRESET_HINT15_SHFT                                                   0x1c
#define HWIO_SPCIE_CAP_OFF_28H_REG_USP_TX_PRESET15_BMSK                                                   0xf000000
#define HWIO_SPCIE_CAP_OFF_28H_REG_USP_TX_PRESET15_SHFT                                                        0x18
#define HWIO_SPCIE_CAP_OFF_28H_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_SPCIE_CAP_OFF_28H_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_SPCIE_CAP_OFF_28H_REG_DSP_RX_PRESET_HINT15_BMSK                                               0x700000
#define HWIO_SPCIE_CAP_OFF_28H_REG_DSP_RX_PRESET_HINT15_SHFT                                                   0x14
#define HWIO_SPCIE_CAP_OFF_28H_REG_DSP_TX_PRESET15_BMSK                                                     0xf0000
#define HWIO_SPCIE_CAP_OFF_28H_REG_DSP_TX_PRESET15_SHFT                                                        0x10
#define HWIO_SPCIE_CAP_OFF_28H_REG_RSVDP_15_BMSK                                                             0x8000
#define HWIO_SPCIE_CAP_OFF_28H_REG_RSVDP_15_SHFT                                                                0xf
#define HWIO_SPCIE_CAP_OFF_28H_REG_USP_RX_PRESET_HINT14_BMSK                                                 0x7000
#define HWIO_SPCIE_CAP_OFF_28H_REG_USP_RX_PRESET_HINT14_SHFT                                                    0xc
#define HWIO_SPCIE_CAP_OFF_28H_REG_USP_TX_PRESET14_BMSK                                                       0xf00
#define HWIO_SPCIE_CAP_OFF_28H_REG_USP_TX_PRESET14_SHFT                                                         0x8
#define HWIO_SPCIE_CAP_OFF_28H_REG_RSVDP_7_BMSK                                                                0x80
#define HWIO_SPCIE_CAP_OFF_28H_REG_RSVDP_7_SHFT                                                                 0x7
#define HWIO_SPCIE_CAP_OFF_28H_REG_DSP_RX_PRESET_HINT14_BMSK                                                   0x70
#define HWIO_SPCIE_CAP_OFF_28H_REG_DSP_RX_PRESET_HINT14_SHFT                                                    0x4
#define HWIO_SPCIE_CAP_OFF_28H_REG_DSP_TX_PRESET14_BMSK                                                         0xf
#define HWIO_SPCIE_CAP_OFF_28H_REG_DSP_TX_PRESET14_SHFT                                                         0x0

#define HWIO_L1SUB_CAP_HEADER_REG_ADDR(x)                                                                ((x) + 0x0000024c)
#define HWIO_L1SUB_CAP_HEADER_REG_RMSK                                                                   0xffffffff
#define HWIO_L1SUB_CAP_HEADER_REG_ATTR                                                                          0x3
#define HWIO_L1SUB_CAP_HEADER_REG_IN(x)      \
        in_dword_masked(HWIO_L1SUB_CAP_HEADER_REG_ADDR(x), HWIO_L1SUB_CAP_HEADER_REG_RMSK)
#define HWIO_L1SUB_CAP_HEADER_REG_INM(x, m)      \
        in_dword_masked(HWIO_L1SUB_CAP_HEADER_REG_ADDR(x), m)
#define HWIO_L1SUB_CAP_HEADER_REG_OUT(x, v)      \
        out_dword(HWIO_L1SUB_CAP_HEADER_REG_ADDR(x),v)
#define HWIO_L1SUB_CAP_HEADER_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_L1SUB_CAP_HEADER_REG_ADDR(x),m,v,HWIO_L1SUB_CAP_HEADER_REG_IN(x))
#define HWIO_L1SUB_CAP_HEADER_REG_NEXT_OFFSET_BMSK                                                       0xfff00000
#define HWIO_L1SUB_CAP_HEADER_REG_NEXT_OFFSET_SHFT                                                             0x14
#define HWIO_L1SUB_CAP_HEADER_REG_CAP_VERSION_BMSK                                                          0xf0000
#define HWIO_L1SUB_CAP_HEADER_REG_CAP_VERSION_SHFT                                                             0x10
#define HWIO_L1SUB_CAP_HEADER_REG_EXTENDED_CAP_ID_BMSK                                                       0xffff
#define HWIO_L1SUB_CAP_HEADER_REG_EXTENDED_CAP_ID_SHFT                                                          0x0

#define HWIO_L1SUB_CAPABILITY_REG_ADDR(x)                                                                ((x) + 0x00000250)
#define HWIO_L1SUB_CAPABILITY_REG_RMSK                                                                   0xffffffff
#define HWIO_L1SUB_CAPABILITY_REG_ATTR                                                                          0x3
#define HWIO_L1SUB_CAPABILITY_REG_IN(x)      \
        in_dword_masked(HWIO_L1SUB_CAPABILITY_REG_ADDR(x), HWIO_L1SUB_CAPABILITY_REG_RMSK)
#define HWIO_L1SUB_CAPABILITY_REG_INM(x, m)      \
        in_dword_masked(HWIO_L1SUB_CAPABILITY_REG_ADDR(x), m)
#define HWIO_L1SUB_CAPABILITY_REG_OUT(x, v)      \
        out_dword(HWIO_L1SUB_CAPABILITY_REG_ADDR(x),v)
#define HWIO_L1SUB_CAPABILITY_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_L1SUB_CAPABILITY_REG_ADDR(x),m,v,HWIO_L1SUB_CAPABILITY_REG_IN(x))
#define HWIO_L1SUB_CAPABILITY_REG_RSVDP_24_BMSK                                                          0xff000000
#define HWIO_L1SUB_CAPABILITY_REG_RSVDP_24_SHFT                                                                0x18
#define HWIO_L1SUB_CAPABILITY_REG_PWR_ON_VALUE_SUPPORT_BMSK                                                0xf80000
#define HWIO_L1SUB_CAPABILITY_REG_PWR_ON_VALUE_SUPPORT_SHFT                                                    0x13
#define HWIO_L1SUB_CAPABILITY_REG_RSVDP_18_BMSK                                                             0x40000
#define HWIO_L1SUB_CAPABILITY_REG_RSVDP_18_SHFT                                                                0x12
#define HWIO_L1SUB_CAPABILITY_REG_PWR_ON_SCALE_SUPPORT_BMSK                                                 0x30000
#define HWIO_L1SUB_CAPABILITY_REG_PWR_ON_SCALE_SUPPORT_SHFT                                                    0x10
#define HWIO_L1SUB_CAPABILITY_REG_COMM_MODE_SUPPORT_BMSK                                                     0xff00
#define HWIO_L1SUB_CAPABILITY_REG_COMM_MODE_SUPPORT_SHFT                                                        0x8
#define HWIO_L1SUB_CAPABILITY_REG_RSVDP_5_BMSK                                                                 0xe0
#define HWIO_L1SUB_CAPABILITY_REG_RSVDP_5_SHFT                                                                  0x5
#define HWIO_L1SUB_CAPABILITY_REG_L1_PMSUB_SUPPORT_BMSK                                                        0x10
#define HWIO_L1SUB_CAPABILITY_REG_L1_PMSUB_SUPPORT_SHFT                                                         0x4
#define HWIO_L1SUB_CAPABILITY_REG_L1_1_ASPM_SUPPORT_BMSK                                                        0x8
#define HWIO_L1SUB_CAPABILITY_REG_L1_1_ASPM_SUPPORT_SHFT                                                        0x3
#define HWIO_L1SUB_CAPABILITY_REG_L1_2_ASPM_SUPPORT_BMSK                                                        0x4
#define HWIO_L1SUB_CAPABILITY_REG_L1_2_ASPM_SUPPORT_SHFT                                                        0x2
#define HWIO_L1SUB_CAPABILITY_REG_L1_1_PCIPM_SUPPORT_BMSK                                                       0x2
#define HWIO_L1SUB_CAPABILITY_REG_L1_1_PCIPM_SUPPORT_SHFT                                                       0x1
#define HWIO_L1SUB_CAPABILITY_REG_L1_2_PCIPM_SUPPORT_BMSK                                                       0x1
#define HWIO_L1SUB_CAPABILITY_REG_L1_2_PCIPM_SUPPORT_SHFT                                                       0x0

#define HWIO_L1SUB_CONTROL1_REG_ADDR(x)                                                                  ((x) + 0x00000254)
#define HWIO_L1SUB_CONTROL1_REG_RMSK                                                                     0xffffffff
#define HWIO_L1SUB_CONTROL1_REG_ATTR                                                                            0x3
#define HWIO_L1SUB_CONTROL1_REG_IN(x)      \
        in_dword_masked(HWIO_L1SUB_CONTROL1_REG_ADDR(x), HWIO_L1SUB_CONTROL1_REG_RMSK)
#define HWIO_L1SUB_CONTROL1_REG_INM(x, m)      \
        in_dword_masked(HWIO_L1SUB_CONTROL1_REG_ADDR(x), m)
#define HWIO_L1SUB_CONTROL1_REG_OUT(x, v)      \
        out_dword(HWIO_L1SUB_CONTROL1_REG_ADDR(x),v)
#define HWIO_L1SUB_CONTROL1_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_L1SUB_CONTROL1_REG_ADDR(x),m,v,HWIO_L1SUB_CONTROL1_REG_IN(x))
#define HWIO_L1SUB_CONTROL1_REG_L1_2_TH_SCA_BMSK                                                         0xe0000000
#define HWIO_L1SUB_CONTROL1_REG_L1_2_TH_SCA_SHFT                                                               0x1d
#define HWIO_L1SUB_CONTROL1_REG_RSVDP_26_BMSK                                                            0x1c000000
#define HWIO_L1SUB_CONTROL1_REG_RSVDP_26_SHFT                                                                  0x1a
#define HWIO_L1SUB_CONTROL1_REG_L1_2_TH_VAL_BMSK                                                          0x3ff0000
#define HWIO_L1SUB_CONTROL1_REG_L1_2_TH_VAL_SHFT                                                               0x10
#define HWIO_L1SUB_CONTROL1_REG_T_COMMON_MODE_BMSK                                                           0xff00
#define HWIO_L1SUB_CONTROL1_REG_T_COMMON_MODE_SHFT                                                              0x8
#define HWIO_L1SUB_CONTROL1_REG_RSVDP_4_BMSK                                                                   0xf0
#define HWIO_L1SUB_CONTROL1_REG_RSVDP_4_SHFT                                                                    0x4
#define HWIO_L1SUB_CONTROL1_REG_L1_1_ASPM_EN_BMSK                                                               0x8
#define HWIO_L1SUB_CONTROL1_REG_L1_1_ASPM_EN_SHFT                                                               0x3
#define HWIO_L1SUB_CONTROL1_REG_L1_2_ASPM_EN_BMSK                                                               0x4
#define HWIO_L1SUB_CONTROL1_REG_L1_2_ASPM_EN_SHFT                                                               0x2
#define HWIO_L1SUB_CONTROL1_REG_L1_1_PCIPM_EN_BMSK                                                              0x2
#define HWIO_L1SUB_CONTROL1_REG_L1_1_PCIPM_EN_SHFT                                                              0x1
#define HWIO_L1SUB_CONTROL1_REG_L1_2_PCIPM_EN_BMSK                                                              0x1
#define HWIO_L1SUB_CONTROL1_REG_L1_2_PCIPM_EN_SHFT                                                              0x0

#define HWIO_L1SUB_CONTROL2_REG_ADDR(x)                                                                  ((x) + 0x00000258)
#define HWIO_L1SUB_CONTROL2_REG_RMSK                                                                     0xffffffff
#define HWIO_L1SUB_CONTROL2_REG_ATTR                                                                            0x3
#define HWIO_L1SUB_CONTROL2_REG_IN(x)      \
        in_dword_masked(HWIO_L1SUB_CONTROL2_REG_ADDR(x), HWIO_L1SUB_CONTROL2_REG_RMSK)
#define HWIO_L1SUB_CONTROL2_REG_INM(x, m)      \
        in_dword_masked(HWIO_L1SUB_CONTROL2_REG_ADDR(x), m)
#define HWIO_L1SUB_CONTROL2_REG_OUT(x, v)      \
        out_dword(HWIO_L1SUB_CONTROL2_REG_ADDR(x),v)
#define HWIO_L1SUB_CONTROL2_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_L1SUB_CONTROL2_REG_ADDR(x),m,v,HWIO_L1SUB_CONTROL2_REG_IN(x))
#define HWIO_L1SUB_CONTROL2_REG_RSVDP_8_BMSK                                                             0xffffff00
#define HWIO_L1SUB_CONTROL2_REG_RSVDP_8_SHFT                                                                    0x8
#define HWIO_L1SUB_CONTROL2_REG_T_POWER_ON_VALUE_BMSK                                                          0xf8
#define HWIO_L1SUB_CONTROL2_REG_T_POWER_ON_VALUE_SHFT                                                           0x3
#define HWIO_L1SUB_CONTROL2_REG_RSVDP_2_BMSK                                                                    0x4
#define HWIO_L1SUB_CONTROL2_REG_RSVDP_2_SHFT                                                                    0x2
#define HWIO_L1SUB_CONTROL2_REG_T_POWER_ON_SCALE_BMSK                                                           0x3
#define HWIO_L1SUB_CONTROL2_REG_T_POWER_ON_SCALE_SHFT                                                           0x0

#define HWIO_CAP_ID_NXT_PTR_REG_ADDR(x)                                                                  ((x) + 0x00000040)
#define HWIO_CAP_ID_NXT_PTR_REG_RMSK                                                                     0xffffffff
#define HWIO_CAP_ID_NXT_PTR_REG_ATTR                                                                            0x3
#define HWIO_CAP_ID_NXT_PTR_REG_IN(x)      \
        in_dword_masked(HWIO_CAP_ID_NXT_PTR_REG_ADDR(x), HWIO_CAP_ID_NXT_PTR_REG_RMSK)
#define HWIO_CAP_ID_NXT_PTR_REG_INM(x, m)      \
        in_dword_masked(HWIO_CAP_ID_NXT_PTR_REG_ADDR(x), m)
#define HWIO_CAP_ID_NXT_PTR_REG_OUT(x, v)      \
        out_dword(HWIO_CAP_ID_NXT_PTR_REG_ADDR(x),v)
#define HWIO_CAP_ID_NXT_PTR_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CAP_ID_NXT_PTR_REG_ADDR(x),m,v,HWIO_CAP_ID_NXT_PTR_REG_IN(x))
#define HWIO_CAP_ID_NXT_PTR_REG_PME_SUPPORT_BMSK                                                         0xf8000000
#define HWIO_CAP_ID_NXT_PTR_REG_PME_SUPPORT_SHFT                                                               0x1b
#define HWIO_CAP_ID_NXT_PTR_REG_D2_SUPPORT_BMSK                                                           0x4000000
#define HWIO_CAP_ID_NXT_PTR_REG_D2_SUPPORT_SHFT                                                                0x1a
#define HWIO_CAP_ID_NXT_PTR_REG_D1_SUPPORT_BMSK                                                           0x2000000
#define HWIO_CAP_ID_NXT_PTR_REG_D1_SUPPORT_SHFT                                                                0x19
#define HWIO_CAP_ID_NXT_PTR_REG_AUX_CURR_BMSK                                                             0x1c00000
#define HWIO_CAP_ID_NXT_PTR_REG_AUX_CURR_SHFT                                                                  0x16
#define HWIO_CAP_ID_NXT_PTR_REG_DSI_BMSK                                                                   0x200000
#define HWIO_CAP_ID_NXT_PTR_REG_DSI_SHFT                                                                       0x15
#define HWIO_CAP_ID_NXT_PTR_REG_PME_IMM_READI_RETURN_DO_BMSK                                               0x100000
#define HWIO_CAP_ID_NXT_PTR_REG_PME_IMM_READI_RETURN_DO_SHFT                                                   0x14
#define HWIO_CAP_ID_NXT_PTR_REG_PME_CLK_BMSK                                                                0x80000
#define HWIO_CAP_ID_NXT_PTR_REG_PME_CLK_SHFT                                                                   0x13
#define HWIO_CAP_ID_NXT_PTR_REG_PM_SPEC_VER_BMSK                                                            0x70000
#define HWIO_CAP_ID_NXT_PTR_REG_PM_SPEC_VER_SHFT                                                               0x10
#define HWIO_CAP_ID_NXT_PTR_REG_PM_NEXT_POINTER_BMSK                                                         0xff00
#define HWIO_CAP_ID_NXT_PTR_REG_PM_NEXT_POINTER_SHFT                                                            0x8
#define HWIO_CAP_ID_NXT_PTR_REG_PM_CAP_ID_BMSK                                                                 0xff
#define HWIO_CAP_ID_NXT_PTR_REG_PM_CAP_ID_SHFT                                                                  0x0

#define HWIO_CON_STATUS_REG_ADDR(x)                                                                      ((x) + 0x00000044)
#define HWIO_CON_STATUS_REG_RMSK                                                                         0xffffffff
#define HWIO_CON_STATUS_REG_ATTR                                                                                0x3
#define HWIO_CON_STATUS_REG_IN(x)      \
        in_dword_masked(HWIO_CON_STATUS_REG_ADDR(x), HWIO_CON_STATUS_REG_RMSK)
#define HWIO_CON_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_CON_STATUS_REG_ADDR(x), m)
#define HWIO_CON_STATUS_REG_OUT(x, v)      \
        out_dword(HWIO_CON_STATUS_REG_ADDR(x),v)
#define HWIO_CON_STATUS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CON_STATUS_REG_ADDR(x),m,v,HWIO_CON_STATUS_REG_IN(x))
#define HWIO_CON_STATUS_REG_DATA_REG_ADD_INFO_BMSK                                                       0xff000000
#define HWIO_CON_STATUS_REG_DATA_REG_ADD_INFO_SHFT                                                             0x18
#define HWIO_CON_STATUS_REG_BUS_PWR_CLK_CON_EN_BMSK                                                        0x800000
#define HWIO_CON_STATUS_REG_BUS_PWR_CLK_CON_EN_SHFT                                                            0x17
#define HWIO_CON_STATUS_REG_B2_B3_SUPPORT_BMSK                                                             0x400000
#define HWIO_CON_STATUS_REG_B2_B3_SUPPORT_SHFT                                                                 0x16
#define HWIO_CON_STATUS_REG_RSVDP_16_BMSK                                                                  0x3f0000
#define HWIO_CON_STATUS_REG_RSVDP_16_SHFT                                                                      0x10
#define HWIO_CON_STATUS_REG_PME_STATUS_BMSK                                                                  0x8000
#define HWIO_CON_STATUS_REG_PME_STATUS_SHFT                                                                     0xf
#define HWIO_CON_STATUS_REG_DATA_SCALE_BMSK                                                                  0x6000
#define HWIO_CON_STATUS_REG_DATA_SCALE_SHFT                                                                     0xd
#define HWIO_CON_STATUS_REG_DATA_SELECT_BMSK                                                                 0x1e00
#define HWIO_CON_STATUS_REG_DATA_SELECT_SHFT                                                                    0x9
#define HWIO_CON_STATUS_REG_PME_ENABLE_BMSK                                                                   0x100
#define HWIO_CON_STATUS_REG_PME_ENABLE_SHFT                                                                     0x8
#define HWIO_CON_STATUS_REG_RSVDP_4_BMSK                                                                       0xf0
#define HWIO_CON_STATUS_REG_RSVDP_4_SHFT                                                                        0x4
#define HWIO_CON_STATUS_REG_NO_SOFT_RST_BMSK                                                                    0x8
#define HWIO_CON_STATUS_REG_NO_SOFT_RST_SHFT                                                                    0x3
#define HWIO_CON_STATUS_REG_RSVDP_2_BMSK                                                                        0x4
#define HWIO_CON_STATUS_REG_RSVDP_2_SHFT                                                                        0x2
#define HWIO_CON_STATUS_REG_POWER_STATE_BMSK                                                                    0x3
#define HWIO_CON_STATUS_REG_POWER_STATE_SHFT                                                                    0x0

#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_ADDR(x)                                          ((x) + 0x00000070)
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RMSK                                             0xffffffff
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_ATTR                                                    0x3
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_IN(x)      \
        in_dword_masked(HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_ADDR(x), HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RMSK)
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_INM(x, m)      \
        in_dword_masked(HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_ADDR(x), m)
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_OUT(x, v)      \
        out_dword(HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_ADDR(x),v)
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_ADDR(x),m,v,HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_IN(x))
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RSVDP_31_BMSK                                    0x80000000
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RSVDP_31_SHFT                                          0x1f
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RSVD_BMSK                                        0x40000000
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_RSVD_SHFT                                              0x1e
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_INT_MSG_NUM_BMSK                            0x3e000000
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_INT_MSG_NUM_SHFT                                  0x19
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_SLOT_IMP_BMSK                                0x1000000
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_SLOT_IMP_SHFT                                     0x18
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_DEV_PORT_TYPE_BMSK                            0xf00000
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_DEV_PORT_TYPE_SHFT                                0x14
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_REG_BMSK                                   0xf0000
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_REG_SHFT                                      0x10
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_NEXT_PTR_BMSK                               0xff00
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_NEXT_PTR_SHFT                                  0x8
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_ID_BMSK                                       0xff
#define HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_ID_SHFT                                        0x0

#define HWIO_DEVICE_CAPABILITIES_REG_ADDR(x)                                                             ((x) + 0x00000074)
#define HWIO_DEVICE_CAPABILITIES_REG_RMSK                                                                0xffffffff
#define HWIO_DEVICE_CAPABILITIES_REG_ATTR                                                                       0x3
#define HWIO_DEVICE_CAPABILITIES_REG_IN(x)      \
        in_dword_masked(HWIO_DEVICE_CAPABILITIES_REG_ADDR(x), HWIO_DEVICE_CAPABILITIES_REG_RMSK)
#define HWIO_DEVICE_CAPABILITIES_REG_INM(x, m)      \
        in_dword_masked(HWIO_DEVICE_CAPABILITIES_REG_ADDR(x), m)
#define HWIO_DEVICE_CAPABILITIES_REG_OUT(x, v)      \
        out_dword(HWIO_DEVICE_CAPABILITIES_REG_ADDR(x),v)
#define HWIO_DEVICE_CAPABILITIES_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DEVICE_CAPABILITIES_REG_ADDR(x),m,v,HWIO_DEVICE_CAPABILITIES_REG_IN(x))
#define HWIO_DEVICE_CAPABILITIES_REG_RSVDP_16_BMSK                                                       0xffff0000
#define HWIO_DEVICE_CAPABILITIES_REG_RSVDP_16_SHFT                                                             0x10
#define HWIO_DEVICE_CAPABILITIES_REG_PCIE_CAP_ROLE_BASED_ERR_REPORT_BMSK                                     0x8000
#define HWIO_DEVICE_CAPABILITIES_REG_PCIE_CAP_ROLE_BASED_ERR_REPORT_SHFT                                        0xf
#define HWIO_DEVICE_CAPABILITIES_REG_RSVDP_6_BMSK                                                            0x7fc0
#define HWIO_DEVICE_CAPABILITIES_REG_RSVDP_6_SHFT                                                               0x6
#define HWIO_DEVICE_CAPABILITIES_REG_PCIE_CAP_EXT_TAG_SUPP_BMSK                                                0x20
#define HWIO_DEVICE_CAPABILITIES_REG_PCIE_CAP_EXT_TAG_SUPP_SHFT                                                 0x5
#define HWIO_DEVICE_CAPABILITIES_REG_PCIE_CAP_PHANTOM_FUNC_SUPPORT_BMSK                                        0x18
#define HWIO_DEVICE_CAPABILITIES_REG_PCIE_CAP_PHANTOM_FUNC_SUPPORT_SHFT                                         0x3
#define HWIO_DEVICE_CAPABILITIES_REG_PCIE_CAP_MAX_PAYLOAD_SIZE_BMSK                                             0x7
#define HWIO_DEVICE_CAPABILITIES_REG_PCIE_CAP_MAX_PAYLOAD_SIZE_SHFT                                             0x0

#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_ADDR(x)                                                        ((x) + 0x00000078)
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_RMSK                                                           0xffffffff
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_ATTR                                                                  0x3
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_IN(x)      \
        in_dword_masked(HWIO_DEVICE_CONTROL_DEVICE_STATUS_ADDR(x), HWIO_DEVICE_CONTROL_DEVICE_STATUS_RMSK)
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_DEVICE_CONTROL_DEVICE_STATUS_ADDR(x), m)
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_OUT(x, v)      \
        out_dword(HWIO_DEVICE_CONTROL_DEVICE_STATUS_ADDR(x),v)
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DEVICE_CONTROL_DEVICE_STATUS_ADDR(x),m,v,HWIO_DEVICE_CONTROL_DEVICE_STATUS_IN(x))
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_RSVDP_22_BMSK                                                  0xffc00000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_RSVDP_22_SHFT                                                        0x16
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_TRANS_PENDING_BMSK                                      0x200000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_TRANS_PENDING_SHFT                                          0x15
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_DETECTED_BMSK                                 0x100000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_DETECTED_SHFT                                     0x14
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORTED_REQ_DETECTED_BMSK                            0x80000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORTED_REQ_DETECTED_SHFT                               0x13
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_DETECTED_BMSK                                  0x40000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_DETECTED_SHFT                                     0x12
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_DETECTED_BMSK                              0x20000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_DETECTED_SHFT                                 0x11
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_DETECTED_BMSK                                   0x10000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_DETECTED_SHFT                                      0x10
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_INITIATE_FLR_BMSK                                         0x8000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_INITIATE_FLR_SHFT                                            0xf
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_READ_REQ_SIZE_BMSK                                    0x7000
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_READ_REQ_SIZE_SHFT                                       0xc
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_NO_SNOOP_BMSK                                           0x800
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_NO_SNOOP_SHFT                                             0xb
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_PM_EN_BMSK                                       0x400
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_AUX_POWER_PM_EN_SHFT                                         0xa
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_PHANTOM_FUNC_EN_BMSK                                       0x200
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_PHANTOM_FUNC_EN_SHFT                                         0x9
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EXT_TAG_EN_BMSK                                            0x100
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EXT_TAG_EN_SHFT                                              0x8
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_PAYLOAD_SIZE_CS_BMSK                                    0xe0
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_MAX_PAYLOAD_SIZE_CS_SHFT                                     0x5
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_REL_ORDER_BMSK                                           0x10
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_EN_REL_ORDER_SHFT                                            0x4
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORT_REQ_REP_EN_BMSK                                    0x8
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_UNSUPPORT_REQ_REP_EN_SHFT                                    0x3
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_REPORT_EN_BMSK                                     0x4
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_FATAL_ERR_REPORT_EN_SHFT                                     0x2
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_REPORT_EN_BMSK                                 0x2
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_NON_FATAL_ERR_REPORT_EN_SHFT                                 0x1
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_REPORT_EN_BMSK                                      0x1
#define HWIO_DEVICE_CONTROL_DEVICE_STATUS_PCIE_CAP_CORR_ERR_REPORT_EN_SHFT                                      0x0

#define HWIO_LINK_CAPABILITIES_REG_ADDR(x)                                                               ((x) + 0x0000007c)
#define HWIO_LINK_CAPABILITIES_REG_RMSK                                                                  0xffffffff
#define HWIO_LINK_CAPABILITIES_REG_ATTR                                                                         0x3
#define HWIO_LINK_CAPABILITIES_REG_IN(x)      \
        in_dword_masked(HWIO_LINK_CAPABILITIES_REG_ADDR(x), HWIO_LINK_CAPABILITIES_REG_RMSK)
#define HWIO_LINK_CAPABILITIES_REG_INM(x, m)      \
        in_dword_masked(HWIO_LINK_CAPABILITIES_REG_ADDR(x), m)
#define HWIO_LINK_CAPABILITIES_REG_OUT(x, v)      \
        out_dword(HWIO_LINK_CAPABILITIES_REG_ADDR(x),v)
#define HWIO_LINK_CAPABILITIES_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LINK_CAPABILITIES_REG_ADDR(x),m,v,HWIO_LINK_CAPABILITIES_REG_IN(x))
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_PORT_NUM_BMSK                                                0xff000000
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_PORT_NUM_SHFT                                                      0x18
#define HWIO_LINK_CAPABILITIES_REG_RSVDP_23_BMSK                                                           0x800000
#define HWIO_LINK_CAPABILITIES_REG_RSVDP_23_SHFT                                                               0x17
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_ASPM_OPT_COMPLIANCE_BMSK                                       0x400000
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_ASPM_OPT_COMPLIANCE_SHFT                                           0x16
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_LINK_BW_NOT_CAP_BMSK                                           0x200000
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_LINK_BW_NOT_CAP_SHFT                                               0x15
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_DLL_ACTIVE_REP_CAP_BMSK                                        0x100000
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_DLL_ACTIVE_REP_CAP_SHFT                                            0x14
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_SURPRISE_DOWN_ERR_REP_CAP_BMSK                                  0x80000
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_SURPRISE_DOWN_ERR_REP_CAP_SHFT                                     0x13
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_CLOCK_POWER_MAN_BMSK                                            0x40000
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_CLOCK_POWER_MAN_SHFT                                               0x12
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY_BMSK                                            0x38000
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY_SHFT                                                0xf
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY_BMSK                                            0x7000
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY_SHFT                                               0xc
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT_BMSK                                 0xc00
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_SUPPORT_SHFT                                   0xa
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_WIDTH_BMSK                                               0x3f0
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_WIDTH_SHFT                                                 0x4
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_SPEED_BMSK                                                 0xf
#define HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_SPEED_SHFT                                                 0x0

#define HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(x)                                                        ((x) + 0x00000080)
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_RMSK                                                           0xffffffff
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_ATTR                                                                  0x3
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_IN(x)      \
        in_dword_masked(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(x), HWIO_LINK_CONTROL_LINK_STATUS_REG_RMSK)
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(x), m)
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_OUT(x, v)      \
        out_dword(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(x),v)
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(x),m,v,HWIO_LINK_CONTROL_LINK_STATUS_REG_IN(x))
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_STATUS_BMSK                              0x80000000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_STATUS_SHFT                                    0x1f
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_STATUS_BMSK                               0x40000000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_STATUS_SHFT                                     0x1e
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DLL_ACTIVE_BMSK                                       0x20000000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DLL_ACTIVE_SHFT                                             0x1d
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_SLOT_CLK_CONFIG_BMSK                                  0x10000000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_SLOT_CLK_CONFIG_SHFT                                        0x1c
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_TRAINING_BMSK                                     0x8000000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_TRAINING_SHFT                                          0x1b
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_RSVDP_26_BMSK                                                   0x4000000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_RSVDP_26_SHFT                                                        0x1a
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH_BMSK                                   0x3f00000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH_SHFT                                        0x14
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED_BMSK                                          0xf0000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED_SHFT                                             0x10
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DRS_SIGNALING_CONTROL_BMSK                                0xc000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_DRS_SIGNALING_CONTROL_SHFT                                   0xe
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_RSVDP_12_BMSK                                                      0x3000
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_RSVDP_12_SHFT                                                         0xc
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_INT_EN_BMSK                                   0x800
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_AUTO_BW_INT_EN_SHFT                                     0xb
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_INT_EN_BMSK                                    0x400
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_BW_MAN_INT_EN_SHFT                                      0xa
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_HW_AUTO_WIDTH_DISABLE_BMSK                                 0x200
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_HW_AUTO_WIDTH_DISABLE_SHFT                                   0x9
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EN_CLK_POWER_MAN_BMSK                                      0x100
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EN_CLK_POWER_MAN_SHFT                                        0x8
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EXTENDED_SYNCH_BMSK                                         0x80
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_EXTENDED_SYNCH_SHFT                                          0x7
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_COMMON_CLK_CONFIG_BMSK                                      0x40
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_COMMON_CLK_CONFIG_SHFT                                       0x6
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RETRAIN_LINK_BMSK                                           0x20
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RETRAIN_LINK_SHFT                                            0x5
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_DISABLE_BMSK                                           0x10
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_DISABLE_SHFT                                            0x4
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RCB_BMSK                                                     0x8
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_RCB_SHFT                                                     0x3
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_RSVDP_2_BMSK                                                          0x4
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_RSVDP_2_SHFT                                                          0x2
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_CONTROL_BMSK                            0x3
#define HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_ACTIVE_STATE_LINK_PM_CONTROL_SHFT                            0x0

#define HWIO_SLOT_CAPABILITIES_REG_ADDR(x)                                                               ((x) + 0x00000084)
#define HWIO_SLOT_CAPABILITIES_REG_RMSK                                                                  0xffffffff
#define HWIO_SLOT_CAPABILITIES_REG_ATTR                                                                         0x3
#define HWIO_SLOT_CAPABILITIES_REG_IN(x)      \
        in_dword_masked(HWIO_SLOT_CAPABILITIES_REG_ADDR(x), HWIO_SLOT_CAPABILITIES_REG_RMSK)
#define HWIO_SLOT_CAPABILITIES_REG_INM(x, m)      \
        in_dword_masked(HWIO_SLOT_CAPABILITIES_REG_ADDR(x), m)
#define HWIO_SLOT_CAPABILITIES_REG_OUT(x, v)      \
        out_dword(HWIO_SLOT_CAPABILITIES_REG_ADDR(x),v)
#define HWIO_SLOT_CAPABILITIES_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SLOT_CAPABILITIES_REG_ADDR(x),m,v,HWIO_SLOT_CAPABILITIES_REG_IN(x))
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_PHY_SLOT_NUM_BMSK                                            0xfff80000
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_PHY_SLOT_NUM_SHFT                                                  0x13
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_NO_CMD_CPL_SUPPORT_BMSK                                         0x40000
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_NO_CMD_CPL_SUPPORT_SHFT                                            0x12
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_ELECTROMECH_INTERLOCK_BMSK                                      0x20000
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_ELECTROMECH_INTERLOCK_SHFT                                         0x11
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_SLOT_POWER_LIMIT_SCALE_BMSK                                     0x18000
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_SLOT_POWER_LIMIT_SCALE_SHFT                                         0xf
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_SLOT_POWER_LIMIT_VALUE_BMSK                                      0x7f80
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_SLOT_POWER_LIMIT_VALUE_SHFT                                         0x7
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_HOT_PLUG_CAPABLE_BMSK                                              0x40
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_HOT_PLUG_CAPABLE_SHFT                                               0x6
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_HOT_PLUG_SURPRISE_BMSK                                             0x20
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_HOT_PLUG_SURPRISE_SHFT                                              0x5
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_POWER_INDICATOR_BMSK                                               0x10
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_POWER_INDICATOR_SHFT                                                0x4
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_ATTENTION_INDICATOR_BMSK                                            0x8
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_ATTENTION_INDICATOR_SHFT                                            0x3
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_MRL_SENSOR_BMSK                                                     0x4
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_MRL_SENSOR_SHFT                                                     0x2
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_POWER_CONTROLLER_BMSK                                               0x2
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_POWER_CONTROLLER_SHFT                                               0x1
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_ATTENTION_INDICATOR_BUTTON_BMSK                                     0x1
#define HWIO_SLOT_CAPABILITIES_REG_PCIE_CAP_ATTENTION_INDICATOR_BUTTON_SHFT                                     0x0

#define HWIO_SLOT_CONTROL_SLOT_STATUS_ADDR(x)                                                            ((x) + 0x00000088)
#define HWIO_SLOT_CONTROL_SLOT_STATUS_RMSK                                                               0xffffffff
#define HWIO_SLOT_CONTROL_SLOT_STATUS_ATTR                                                                      0x3
#define HWIO_SLOT_CONTROL_SLOT_STATUS_IN(x)      \
        in_dword_masked(HWIO_SLOT_CONTROL_SLOT_STATUS_ADDR(x), HWIO_SLOT_CONTROL_SLOT_STATUS_RMSK)
#define HWIO_SLOT_CONTROL_SLOT_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_SLOT_CONTROL_SLOT_STATUS_ADDR(x), m)
#define HWIO_SLOT_CONTROL_SLOT_STATUS_OUT(x, v)      \
        out_dword(HWIO_SLOT_CONTROL_SLOT_STATUS_ADDR(x),v)
#define HWIO_SLOT_CONTROL_SLOT_STATUS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SLOT_CONTROL_SLOT_STATUS_ADDR(x),m,v,HWIO_SLOT_CONTROL_SLOT_STATUS_IN(x))
#define HWIO_SLOT_CONTROL_SLOT_STATUS_RSVDP_25_BMSK                                                      0xfe000000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_RSVDP_25_SHFT                                                            0x19
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_DLL_STATE_CHANGED_BMSK                                     0x1000000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_DLL_STATE_CHANGED_SHFT                                          0x18
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ELECTROMECH_INTERLOCK_STATUS_BMSK                           0x800000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ELECTROMECH_INTERLOCK_STATUS_SHFT                               0x17
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_PRESENCE_DETECT_STATE_BMSK                                  0x400000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_PRESENCE_DETECT_STATE_SHFT                                      0x16
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_MRL_SENSOR_STATE_BMSK                                       0x200000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_MRL_SENSOR_STATE_SHFT                                           0x15
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_CMD_CPLD_BMSK                                               0x100000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_CMD_CPLD_SHFT                                                   0x14
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_PRESENCE_DETECTED_CHANGED_BMSK                               0x80000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_PRESENCE_DETECTED_CHANGED_SHFT                                  0x13
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_MRL_SENSOR_CHANGED_BMSK                                      0x40000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_MRL_SENSOR_CHANGED_SHFT                                         0x12
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_POWER_FAULT_DETECTED_BMSK                                    0x20000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_POWER_FAULT_DETECTED_SHFT                                       0x11
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ATTENTION_BUTTON_PRESSED_BMSK                                0x10000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ATTENTION_BUTTON_PRESSED_SHFT                                   0x10
#define HWIO_SLOT_CONTROL_SLOT_STATUS_RSVDP_13_BMSK                                                          0xe000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_RSVDP_13_SHFT                                                             0xd
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_DLL_STATE_CHANGED_EN_BMSK                                     0x1000
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_DLL_STATE_CHANGED_EN_SHFT                                        0xc
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ELECTROMECH_INTERLOCK_CTRL_BMSK                                0x800
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ELECTROMECH_INTERLOCK_CTRL_SHFT                                  0xb
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_POWER_CONTROLLER_CTRL_BMSK                                     0x400
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_POWER_CONTROLLER_CTRL_SHFT                                       0xa
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_POWER_INDICATOR_CTRL_BMSK                                      0x300
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_POWER_INDICATOR_CTRL_SHFT                                        0x8
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ATTENTION_INDICATOR_CTRL_BMSK                                   0xc0
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ATTENTION_INDICATOR_CTRL_SHFT                                    0x6
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_HOT_PLUG_INT_EN_BMSK                                            0x20
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_HOT_PLUG_INT_EN_SHFT                                             0x5
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_CMD_CPL_INT_EN_BMSK                                             0x10
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_CMD_CPL_INT_EN_SHFT                                              0x4
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_PRESENCE_DETECT_CHANGE_EN_BMSK                                   0x8
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_PRESENCE_DETECT_CHANGE_EN_SHFT                                   0x3
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_MRL_SENSOR_CHANGED_EN_BMSK                                       0x4
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_MRL_SENSOR_CHANGED_EN_SHFT                                       0x2
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_POWER_FAULT_DETECTED_EN_BMSK                                     0x2
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_POWER_FAULT_DETECTED_EN_SHFT                                     0x1
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ATTENTION_BUTTON_PRESSED_EN_BMSK                                 0x1
#define HWIO_SLOT_CONTROL_SLOT_STATUS_PCIE_CAP_ATTENTION_BUTTON_PRESSED_EN_SHFT                                 0x0

#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_ADDR(x)                                                  ((x) + 0x0000008c)
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_RMSK                                                     0xffffffff
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_ATTR                                                            0x3
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_IN(x)      \
        in_dword_masked(HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_ADDR(x), HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_RMSK)
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_INM(x, m)      \
        in_dword_masked(HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_ADDR(x), m)
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_OUT(x, v)      \
        out_dword(HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_ADDR(x),v)
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_ADDR(x),m,v,HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_IN(x))
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_RSVDP_17_BMSK                                            0xfffe0000
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_RSVDP_17_SHFT                                                  0x11
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_BMSK                             0x10000
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_SHFT                                0x10
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_RSVDP_5_BMSK                                                 0xffe0
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_RSVDP_5_SHFT                                                    0x5
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_EN_BMSK                             0x10
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_EN_SHFT                              0x4
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_PME_INT_EN_BMSK                                        0x8
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_PME_INT_EN_SHFT                                        0x3
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_SYS_ERR_ON_FATAL_ERR_EN_BMSK                           0x4
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_SYS_ERR_ON_FATAL_ERR_EN_SHFT                           0x2
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_SYS_ERR_ON_NON_FATAL_ERR_EN_BMSK                       0x2
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_SYS_ERR_ON_NON_FATAL_ERR_EN_SHFT                       0x1
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_SYS_ERR_ON_CORR_ERR_EN_BMSK                            0x1
#define HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_SYS_ERR_ON_CORR_ERR_EN_SHFT                            0x0

#define HWIO_ROOT_STATUS_REG_ADDR(x)                                                                     ((x) + 0x00000090)
#define HWIO_ROOT_STATUS_REG_RMSK                                                                        0xffffffff
#define HWIO_ROOT_STATUS_REG_ATTR                                                                               0x3
#define HWIO_ROOT_STATUS_REG_IN(x)      \
        in_dword_masked(HWIO_ROOT_STATUS_REG_ADDR(x), HWIO_ROOT_STATUS_REG_RMSK)
#define HWIO_ROOT_STATUS_REG_INM(x, m)      \
        in_dword_masked(HWIO_ROOT_STATUS_REG_ADDR(x), m)
#define HWIO_ROOT_STATUS_REG_OUT(x, v)      \
        out_dword(HWIO_ROOT_STATUS_REG_ADDR(x),v)
#define HWIO_ROOT_STATUS_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ROOT_STATUS_REG_ADDR(x),m,v,HWIO_ROOT_STATUS_REG_IN(x))
#define HWIO_ROOT_STATUS_REG_RSVDP_18_BMSK                                                               0xfffc0000
#define HWIO_ROOT_STATUS_REG_RSVDP_18_SHFT                                                                     0x12
#define HWIO_ROOT_STATUS_REG_PCIE_CAP_PME_PENDING_BMSK                                                      0x20000
#define HWIO_ROOT_STATUS_REG_PCIE_CAP_PME_PENDING_SHFT                                                         0x11
#define HWIO_ROOT_STATUS_REG_PCIE_CAP_PME_STATUS_BMSK                                                       0x10000
#define HWIO_ROOT_STATUS_REG_PCIE_CAP_PME_STATUS_SHFT                                                          0x10
#define HWIO_ROOT_STATUS_REG_PCIE_CAP_PME_REQ_ID_BMSK                                                        0xffff
#define HWIO_ROOT_STATUS_REG_PCIE_CAP_PME_REQ_ID_SHFT                                                           0x0

#define HWIO_DEVICE_CAPABILITIES2_REG_ADDR(x)                                                            ((x) + 0x00000094)
#define HWIO_DEVICE_CAPABILITIES2_REG_RMSK                                                               0x7fffffff
#define HWIO_DEVICE_CAPABILITIES2_REG_ATTR                                                                      0x3
#define HWIO_DEVICE_CAPABILITIES2_REG_IN(x)      \
        in_dword_masked(HWIO_DEVICE_CAPABILITIES2_REG_ADDR(x), HWIO_DEVICE_CAPABILITIES2_REG_RMSK)
#define HWIO_DEVICE_CAPABILITIES2_REG_INM(x, m)      \
        in_dword_masked(HWIO_DEVICE_CAPABILITIES2_REG_ADDR(x), m)
#define HWIO_DEVICE_CAPABILITIES2_REG_OUT(x, v)      \
        out_dword(HWIO_DEVICE_CAPABILITIES2_REG_ADDR(x),v)
#define HWIO_DEVICE_CAPABILITIES2_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DEVICE_CAPABILITIES2_REG_ADDR(x),m,v,HWIO_DEVICE_CAPABILITIES2_REG_IN(x))
#define HWIO_DEVICE_CAPABILITIES2_REG_RSVDP_24_BMSK                                                      0x7f000000
#define HWIO_DEVICE_CAPABILITIES2_REG_RSVDP_24_SHFT                                                            0x18
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_CFG_MAX_END2END_TLP_PRFXS_BMSK                             0xc00000
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_CFG_MAX_END2END_TLP_PRFXS_SHFT                                 0x16
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_CFG_END2END_TLP_PRFX_SUPPORT_BMSK                          0x200000
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_CFG_END2END_TLP_PRFX_SUPPORT_SHFT                              0x15
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_CFG_EXTND_FMT_SUPPORT_BMSK                                 0x100000
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_CFG_EXTND_FMT_SUPPORT_SHFT                                     0x14
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_OBFF_SUPPORT_BMSK                                            0xc0000
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_OBFF_SUPPORT_SHFT                                               0x12
#define HWIO_DEVICE_CAPABILITIES2_REG_RSVDP_16_BMSK                                                         0x30000
#define HWIO_DEVICE_CAPABILITIES2_REG_RSVDP_16_SHFT                                                            0x10
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_LN_SYS_CLS_BMSK                                              0xc000
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP2_LN_SYS_CLS_SHFT                                                 0xe
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_1_BMSK                                      0x2000
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_1_SHFT                                         0xd
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_0_BMSK                                      0x1000
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_TPH_CMPLT_SUPPORT_0_SHFT                                         0xc
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_LTR_SUPP_BMSK                                                  0x800
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_LTR_SUPP_SHFT                                                    0xb
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_NO_RO_EN_PR2PR_PAR_BMSK                                        0x400
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_NO_RO_EN_PR2PR_PAR_SHFT                                          0xa
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_128_CAS_CPL_SUPP_BMSK                                          0x200
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_128_CAS_CPL_SUPP_SHFT                                            0x9
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_64_ATOMIC_CPL_SUPP_BMSK                                        0x100
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_64_ATOMIC_CPL_SUPP_SHFT                                          0x8
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_32_ATOMIC_CPL_SUPP_BMSK                                         0x80
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_32_ATOMIC_CPL_SUPP_SHFT                                          0x7
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ATOMIC_ROUTING_SUPP_BMSK                                        0x40
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ATOMIC_ROUTING_SUPP_SHFT                                         0x6
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT_BMSK                                        0x20
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT_SHFT                                         0x5
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE_SUPPORT_BMSK                                0x10
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE_SUPPORT_SHFT                                 0x4
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_RANGE_BMSK                                           0xf
#define HWIO_DEVICE_CAPABILITIES2_REG_PCIE_CAP_CPL_TIMEOUT_RANGE_SHFT                                           0x0

#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_ADDR(x)                                                  ((x) + 0x00000098)
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_RMSK                                                     0xffffffff
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_ATTR                                                            0x3
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_IN(x)      \
        in_dword_masked(HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_ADDR(x), HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_RMSK)
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_INM(x, m)      \
        in_dword_masked(HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_ADDR(x), m)
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_OUT(x, v)      \
        out_dword(HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_ADDR(x),v)
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_ADDR(x),m,v,HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_IN(x))
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_RSVDP_16_BMSK                                            0xffff0000
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_RSVDP_16_SHFT                                                  0x10
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CTRL2_CFG_END2END_TLP_PFX_BLCK_BMSK                     0x8000
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CTRL2_CFG_END2END_TLP_PFX_BLCK_SHFT                        0xf
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_OBFF_EN_BMSK                                        0x6000
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_OBFF_EN_SHFT                                           0xd
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_RSVDP_11_BMSK                                                0x1800
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_RSVDP_11_SHFT                                                   0xb
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_LTR_EN_BMSK                                          0x400
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_LTR_EN_SHFT                                            0xa
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_IDO_CPL_EN_BMSK                                      0x200
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_IDO_CPL_EN_SHFT                                        0x9
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_IDO_REQ_EN_BMSK                                      0x100
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_IDO_REQ_EN_SHFT                                        0x8
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_RSVDP_6_BMSK                                                   0xc0
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_RSVDP_6_SHFT                                                    0x6
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT_CS_BMSK                           0x20
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_ARI_FORWARD_SUPPORT_CS_SHFT                            0x5
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE_BMSK                              0x10
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_DISABLE_SHFT                               0x4
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_VALUE_BMSK                                 0xf
#define HWIO_DEVICE_CONTROL2_DEVICE_STATUS2_REG_PCIE_CAP_CPL_TIMEOUT_VALUE_SHFT                                 0x0

#define HWIO_LINK_CAPABILITIES2_REG_ADDR(x)                                                              ((x) + 0x0000009c)
#define HWIO_LINK_CAPABILITIES2_REG_RMSK                                                                 0xff7fffff
#define HWIO_LINK_CAPABILITIES2_REG_ATTR                                                                        0x3
#define HWIO_LINK_CAPABILITIES2_REG_IN(x)      \
        in_dword_masked(HWIO_LINK_CAPABILITIES2_REG_ADDR(x), HWIO_LINK_CAPABILITIES2_REG_RMSK)
#define HWIO_LINK_CAPABILITIES2_REG_INM(x, m)      \
        in_dword_masked(HWIO_LINK_CAPABILITIES2_REG_ADDR(x), m)
#define HWIO_LINK_CAPABILITIES2_REG_OUT(x, v)      \
        out_dword(HWIO_LINK_CAPABILITIES2_REG_ADDR(x),v)
#define HWIO_LINK_CAPABILITIES2_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LINK_CAPABILITIES2_REG_ADDR(x),m,v,HWIO_LINK_CAPABILITIES2_REG_IN(x))
#define HWIO_LINK_CAPABILITIES2_REG_DRS_SUPPORTED_BMSK                                                   0x80000000
#define HWIO_LINK_CAPABILITIES2_REG_DRS_SUPPORTED_SHFT                                                         0x1f
#define HWIO_LINK_CAPABILITIES2_REG_RSVDP_24_BMSK                                                        0x7f000000
#define HWIO_LINK_CAPABILITIES2_REG_RSVDP_24_SHFT                                                              0x18
#define HWIO_LINK_CAPABILITIES2_REG_RSVDP_9_BMSK                                                           0x7ffe00
#define HWIO_LINK_CAPABILITIES2_REG_RSVDP_9_SHFT                                                                0x9
#define HWIO_LINK_CAPABILITIES2_REG_PCIE_CAP_CROSS_LINK_SUPPORT_BMSK                                          0x100
#define HWIO_LINK_CAPABILITIES2_REG_PCIE_CAP_CROSS_LINK_SUPPORT_SHFT                                            0x8
#define HWIO_LINK_CAPABILITIES2_REG_PCIE_CAP_SUPPORT_LINK_SPEED_VECTOR_BMSK                                    0xfe
#define HWIO_LINK_CAPABILITIES2_REG_PCIE_CAP_SUPPORT_LINK_SPEED_VECTOR_SHFT                                     0x1
#define HWIO_LINK_CAPABILITIES2_REG_RSVDP_0_BMSK                                                                0x1
#define HWIO_LINK_CAPABILITIES2_REG_RSVDP_0_SHFT                                                                0x0

#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_ADDR(x)                                                      ((x) + 0x000000a0)
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_RMSK                                                         0xf03fffff
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_ATTR                                                                0x3
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_IN(x)      \
        in_dword_masked(HWIO_LINK_CONTROL2_LINK_STATUS2_REG_ADDR(x), HWIO_LINK_CONTROL2_LINK_STATUS2_REG_RMSK)
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_INM(x, m)      \
        in_dword_masked(HWIO_LINK_CONTROL2_LINK_STATUS2_REG_ADDR(x), m)
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_OUT(x, v)      \
        out_dword(HWIO_LINK_CONTROL2_LINK_STATUS2_REG_ADDR(x),v)
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LINK_CONTROL2_LINK_STATUS2_REG_ADDR(x),m,v,HWIO_LINK_CONTROL2_LINK_STATUS2_REG_IN(x))
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_DRS_MESSAGE_RECEIVED_BMSK                                    0x80000000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_DRS_MESSAGE_RECEIVED_SHFT                                          0x1f
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_DOWNSTREAM_COMPO_PRESENCE_BMSK                               0x70000000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_DOWNSTREAM_COMPO_PRESENCE_SHFT                                     0x1c
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_LINK_EQ_REQ_BMSK                                      0x200000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_LINK_EQ_REQ_SHFT                                          0x15
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P3_BMSK                                        0x100000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P3_SHFT                                            0x14
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P2_BMSK                                         0x80000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P2_SHFT                                            0x13
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P1_BMSK                                         0x40000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_P1_SHFT                                            0x12
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_BMSK                                            0x20000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_EQ_CPL_SHFT                                               0x11
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_CURR_DEEMPHASIS_BMSK                                   0x10000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_CURR_DEEMPHASIS_SHFT                                      0x10
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_PRESET_BMSK                                  0xf000
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_PRESET_SHFT                                     0xc
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_SOS_BMSK                                      0x800
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_COMPLIANCE_SOS_SHFT                                        0xb
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_MODIFIED_COMPLIANCE_BMSK                           0x400
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_MODIFIED_COMPLIANCE_SHFT                             0xa
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TX_MARGIN_BMSK                                           0x380
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TX_MARGIN_SHFT                                             0x7
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_SEL_DEEMPHASIS_BMSK                                       0x40
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_SEL_DEEMPHASIS_SHFT                                        0x6
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_HW_AUTO_SPEED_DISABLE_BMSK                                0x20
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_HW_AUTO_SPEED_DISABLE_SHFT                                 0x5
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_COMPLIANCE_BMSK                                     0x10
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_ENTER_COMPLIANCE_SHFT                                      0x4
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK                                     0xf
#define HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_SHFT                                     0x0

#define HWIO_AER_EXT_CAP_HDR_OFF_ADDR(x)                                                                 ((x) + 0x00000100)
#define HWIO_AER_EXT_CAP_HDR_OFF_RMSK                                                                    0xffffffff
#define HWIO_AER_EXT_CAP_HDR_OFF_ATTR                                                                           0x3
#define HWIO_AER_EXT_CAP_HDR_OFF_IN(x)      \
        in_dword_masked(HWIO_AER_EXT_CAP_HDR_OFF_ADDR(x), HWIO_AER_EXT_CAP_HDR_OFF_RMSK)
#define HWIO_AER_EXT_CAP_HDR_OFF_INM(x, m)      \
        in_dword_masked(HWIO_AER_EXT_CAP_HDR_OFF_ADDR(x), m)
#define HWIO_AER_EXT_CAP_HDR_OFF_OUT(x, v)      \
        out_dword(HWIO_AER_EXT_CAP_HDR_OFF_ADDR(x),v)
#define HWIO_AER_EXT_CAP_HDR_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AER_EXT_CAP_HDR_OFF_ADDR(x),m,v,HWIO_AER_EXT_CAP_HDR_OFF_IN(x))
#define HWIO_AER_EXT_CAP_HDR_OFF_NEXT_OFFSET_BMSK                                                        0xfff00000
#define HWIO_AER_EXT_CAP_HDR_OFF_NEXT_OFFSET_SHFT                                                              0x14
#define HWIO_AER_EXT_CAP_HDR_OFF_CAP_VERSION_BMSK                                                           0xf0000
#define HWIO_AER_EXT_CAP_HDR_OFF_CAP_VERSION_SHFT                                                              0x10
#define HWIO_AER_EXT_CAP_HDR_OFF_CAP_ID_BMSK                                                                 0xffff
#define HWIO_AER_EXT_CAP_HDR_OFF_CAP_ID_SHFT                                                                    0x0

#define HWIO_UNCORR_ERR_STATUS_OFF_ADDR(x)                                                               ((x) + 0x00000104)
#define HWIO_UNCORR_ERR_STATUS_OFF_RMSK                                                                  0xffffffff
#define HWIO_UNCORR_ERR_STATUS_OFF_ATTR                                                                         0x3
#define HWIO_UNCORR_ERR_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_UNCORR_ERR_STATUS_OFF_ADDR(x), HWIO_UNCORR_ERR_STATUS_OFF_RMSK)
#define HWIO_UNCORR_ERR_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_UNCORR_ERR_STATUS_OFF_ADDR(x), m)
#define HWIO_UNCORR_ERR_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_UNCORR_ERR_STATUS_OFF_ADDR(x),v)
#define HWIO_UNCORR_ERR_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UNCORR_ERR_STATUS_OFF_ADDR(x),m,v,HWIO_UNCORR_ERR_STATUS_OFF_IN(x))
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_26_BMSK                                                         0xfc000000
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_26_SHFT                                                               0x1a
#define HWIO_UNCORR_ERR_STATUS_OFF_TLP_PRFX_BLOCKED_ERR_STATUS_BMSK                                       0x2000000
#define HWIO_UNCORR_ERR_STATUS_OFF_TLP_PRFX_BLOCKED_ERR_STATUS_SHFT                                            0x19
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_23_BMSK                                                          0x1800000
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_23_SHFT                                                               0x17
#define HWIO_UNCORR_ERR_STATUS_OFF_INTERNAL_ERR_STATUS_BMSK                                                0x400000
#define HWIO_UNCORR_ERR_STATUS_OFF_INTERNAL_ERR_STATUS_SHFT                                                    0x16
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_21_BMSK                                                           0x200000
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_21_SHFT                                                               0x15
#define HWIO_UNCORR_ERR_STATUS_OFF_UNSUPPORTED_REQ_ERR_STATUS_BMSK                                         0x100000
#define HWIO_UNCORR_ERR_STATUS_OFF_UNSUPPORTED_REQ_ERR_STATUS_SHFT                                             0x14
#define HWIO_UNCORR_ERR_STATUS_OFF_ECRC_ERR_STATUS_BMSK                                                     0x80000
#define HWIO_UNCORR_ERR_STATUS_OFF_ECRC_ERR_STATUS_SHFT                                                        0x13
#define HWIO_UNCORR_ERR_STATUS_OFF_MALF_TLP_ERR_STATUS_BMSK                                                 0x40000
#define HWIO_UNCORR_ERR_STATUS_OFF_MALF_TLP_ERR_STATUS_SHFT                                                    0x12
#define HWIO_UNCORR_ERR_STATUS_OFF_REC_OVERFLOW_ERR_STATUS_BMSK                                             0x20000
#define HWIO_UNCORR_ERR_STATUS_OFF_REC_OVERFLOW_ERR_STATUS_SHFT                                                0x11
#define HWIO_UNCORR_ERR_STATUS_OFF_UNEXP_CMPLT_ERR_STATUS_BMSK                                              0x10000
#define HWIO_UNCORR_ERR_STATUS_OFF_UNEXP_CMPLT_ERR_STATUS_SHFT                                                 0x10
#define HWIO_UNCORR_ERR_STATUS_OFF_CMPLT_ABORT_ERR_STATUS_BMSK                                               0x8000
#define HWIO_UNCORR_ERR_STATUS_OFF_CMPLT_ABORT_ERR_STATUS_SHFT                                                  0xf
#define HWIO_UNCORR_ERR_STATUS_OFF_CMPLT_TIMEOUT_ERR_STATUS_BMSK                                             0x4000
#define HWIO_UNCORR_ERR_STATUS_OFF_CMPLT_TIMEOUT_ERR_STATUS_SHFT                                                0xe
#define HWIO_UNCORR_ERR_STATUS_OFF_FC_PROTOCOL_ERR_STATUS_BMSK                                               0x2000
#define HWIO_UNCORR_ERR_STATUS_OFF_FC_PROTOCOL_ERR_STATUS_SHFT                                                  0xd
#define HWIO_UNCORR_ERR_STATUS_OFF_POIS_TLP_ERR_STATUS_BMSK                                                  0x1000
#define HWIO_UNCORR_ERR_STATUS_OFF_POIS_TLP_ERR_STATUS_SHFT                                                     0xc
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_6_BMSK                                                               0xfc0
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_6_SHFT                                                                 0x6
#define HWIO_UNCORR_ERR_STATUS_OFF_SUR_DWN_ERR_STATUS_BMSK                                                     0x20
#define HWIO_UNCORR_ERR_STATUS_OFF_SUR_DWN_ERR_STATUS_SHFT                                                      0x5
#define HWIO_UNCORR_ERR_STATUS_OFF_DL_PROTOCOL_ERR_STATUS_BMSK                                                 0x10
#define HWIO_UNCORR_ERR_STATUS_OFF_DL_PROTOCOL_ERR_STATUS_SHFT                                                  0x4
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_0_BMSK                                                                 0xf
#define HWIO_UNCORR_ERR_STATUS_OFF_RSVDP_0_SHFT                                                                 0x0

#define HWIO_UNCORR_ERR_MASK_OFF_ADDR(x)                                                                 ((x) + 0x00000108)
#define HWIO_UNCORR_ERR_MASK_OFF_RMSK                                                                    0xffffffff
#define HWIO_UNCORR_ERR_MASK_OFF_ATTR                                                                           0x3
#define HWIO_UNCORR_ERR_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_UNCORR_ERR_MASK_OFF_ADDR(x), HWIO_UNCORR_ERR_MASK_OFF_RMSK)
#define HWIO_UNCORR_ERR_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_UNCORR_ERR_MASK_OFF_ADDR(x), m)
#define HWIO_UNCORR_ERR_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_UNCORR_ERR_MASK_OFF_ADDR(x),v)
#define HWIO_UNCORR_ERR_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UNCORR_ERR_MASK_OFF_ADDR(x),m,v,HWIO_UNCORR_ERR_MASK_OFF_IN(x))
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_26_BMSK                                                           0xfc000000
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_26_SHFT                                                                 0x1a
#define HWIO_UNCORR_ERR_MASK_OFF_TLP_PRFX_BLOCKED_ERR_MASK_BMSK                                           0x2000000
#define HWIO_UNCORR_ERR_MASK_OFF_TLP_PRFX_BLOCKED_ERR_MASK_SHFT                                                0x19
#define HWIO_UNCORR_ERR_MASK_OFF_ATOMIC_EGRESS_BLOCKED_ERR_MASK_BMSK                                      0x1000000
#define HWIO_UNCORR_ERR_MASK_OFF_ATOMIC_EGRESS_BLOCKED_ERR_MASK_SHFT                                           0x18
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_23_BMSK                                                             0x800000
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_23_SHFT                                                                 0x17
#define HWIO_UNCORR_ERR_MASK_OFF_INTERNAL_ERR_MASK_BMSK                                                    0x400000
#define HWIO_UNCORR_ERR_MASK_OFF_INTERNAL_ERR_MASK_SHFT                                                        0x16
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_21_BMSK                                                             0x200000
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_21_SHFT                                                                 0x15
#define HWIO_UNCORR_ERR_MASK_OFF_UNSUPPORTED_REQ_ERR_MASK_BMSK                                             0x100000
#define HWIO_UNCORR_ERR_MASK_OFF_UNSUPPORTED_REQ_ERR_MASK_SHFT                                                 0x14
#define HWIO_UNCORR_ERR_MASK_OFF_ECRC_ERR_MASK_BMSK                                                         0x80000
#define HWIO_UNCORR_ERR_MASK_OFF_ECRC_ERR_MASK_SHFT                                                            0x13
#define HWIO_UNCORR_ERR_MASK_OFF_MALF_TLP_ERR_MASK_BMSK                                                     0x40000
#define HWIO_UNCORR_ERR_MASK_OFF_MALF_TLP_ERR_MASK_SHFT                                                        0x12
#define HWIO_UNCORR_ERR_MASK_OFF_REC_OVERFLOW_ERR_MASK_BMSK                                                 0x20000
#define HWIO_UNCORR_ERR_MASK_OFF_REC_OVERFLOW_ERR_MASK_SHFT                                                    0x11
#define HWIO_UNCORR_ERR_MASK_OFF_UNEXP_CMPLT_ERR_MASK_BMSK                                                  0x10000
#define HWIO_UNCORR_ERR_MASK_OFF_UNEXP_CMPLT_ERR_MASK_SHFT                                                     0x10
#define HWIO_UNCORR_ERR_MASK_OFF_CMPLT_ABORT_ERR_MASK_BMSK                                                   0x8000
#define HWIO_UNCORR_ERR_MASK_OFF_CMPLT_ABORT_ERR_MASK_SHFT                                                      0xf
#define HWIO_UNCORR_ERR_MASK_OFF_CMPLT_TIMEOUT_ERR_MASK_BMSK                                                 0x4000
#define HWIO_UNCORR_ERR_MASK_OFF_CMPLT_TIMEOUT_ERR_MASK_SHFT                                                    0xe
#define HWIO_UNCORR_ERR_MASK_OFF_FC_PROTOCOL_ERR_MASK_BMSK                                                   0x2000
#define HWIO_UNCORR_ERR_MASK_OFF_FC_PROTOCOL_ERR_MASK_SHFT                                                      0xd
#define HWIO_UNCORR_ERR_MASK_OFF_POIS_TLP_ERR_MASK_BMSK                                                      0x1000
#define HWIO_UNCORR_ERR_MASK_OFF_POIS_TLP_ERR_MASK_SHFT                                                         0xc
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_6_BMSK                                                                 0xfc0
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_6_SHFT                                                                   0x6
#define HWIO_UNCORR_ERR_MASK_OFF_SUR_DWN_ERR_MASK_BMSK                                                         0x20
#define HWIO_UNCORR_ERR_MASK_OFF_SUR_DWN_ERR_MASK_SHFT                                                          0x5
#define HWIO_UNCORR_ERR_MASK_OFF_DL_PROTOCOL_ERR_MASK_BMSK                                                     0x10
#define HWIO_UNCORR_ERR_MASK_OFF_DL_PROTOCOL_ERR_MASK_SHFT                                                      0x4
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_0_BMSK                                                                   0xf
#define HWIO_UNCORR_ERR_MASK_OFF_RSVDP_0_SHFT                                                                   0x0

#define HWIO_UNCORR_ERR_SEV_OFF_ADDR(x)                                                                  ((x) + 0x0000010c)
#define HWIO_UNCORR_ERR_SEV_OFF_RMSK                                                                     0xffffffff
#define HWIO_UNCORR_ERR_SEV_OFF_ATTR                                                                            0x3
#define HWIO_UNCORR_ERR_SEV_OFF_IN(x)      \
        in_dword_masked(HWIO_UNCORR_ERR_SEV_OFF_ADDR(x), HWIO_UNCORR_ERR_SEV_OFF_RMSK)
#define HWIO_UNCORR_ERR_SEV_OFF_INM(x, m)      \
        in_dword_masked(HWIO_UNCORR_ERR_SEV_OFF_ADDR(x), m)
#define HWIO_UNCORR_ERR_SEV_OFF_OUT(x, v)      \
        out_dword(HWIO_UNCORR_ERR_SEV_OFF_ADDR(x),v)
#define HWIO_UNCORR_ERR_SEV_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_UNCORR_ERR_SEV_OFF_ADDR(x),m,v,HWIO_UNCORR_ERR_SEV_OFF_IN(x))
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_26_BMSK                                                            0xfc000000
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_26_SHFT                                                                  0x1a
#define HWIO_UNCORR_ERR_SEV_OFF_TLP_PRFX_BLOCKED_ERR_SEVERITY_BMSK                                        0x2000000
#define HWIO_UNCORR_ERR_SEV_OFF_TLP_PRFX_BLOCKED_ERR_SEVERITY_SHFT                                             0x19
#define HWIO_UNCORR_ERR_SEV_OFF_ATOMIC_EGRESS_BLOCKED_ERR_SEVERITY_BMSK                                   0x1000000
#define HWIO_UNCORR_ERR_SEV_OFF_ATOMIC_EGRESS_BLOCKED_ERR_SEVERITY_SHFT                                        0x18
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_23_BMSK                                                              0x800000
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_23_SHFT                                                                  0x17
#define HWIO_UNCORR_ERR_SEV_OFF_INTERNAL_ERR_SEVERITY_BMSK                                                 0x400000
#define HWIO_UNCORR_ERR_SEV_OFF_INTERNAL_ERR_SEVERITY_SHFT                                                     0x16
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_21_BMSK                                                              0x200000
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_21_SHFT                                                                  0x15
#define HWIO_UNCORR_ERR_SEV_OFF_UNSUPPORTED_REQ_ERR_SEVERITY_BMSK                                          0x100000
#define HWIO_UNCORR_ERR_SEV_OFF_UNSUPPORTED_REQ_ERR_SEVERITY_SHFT                                              0x14
#define HWIO_UNCORR_ERR_SEV_OFF_ECRC_ERR_SEVERITY_BMSK                                                      0x80000
#define HWIO_UNCORR_ERR_SEV_OFF_ECRC_ERR_SEVERITY_SHFT                                                         0x13
#define HWIO_UNCORR_ERR_SEV_OFF_MALF_TLP_ERR_SEVERITY_BMSK                                                  0x40000
#define HWIO_UNCORR_ERR_SEV_OFF_MALF_TLP_ERR_SEVERITY_SHFT                                                     0x12
#define HWIO_UNCORR_ERR_SEV_OFF_REC_OVERFLOW_ERR_SEVERITY_BMSK                                              0x20000
#define HWIO_UNCORR_ERR_SEV_OFF_REC_OVERFLOW_ERR_SEVERITY_SHFT                                                 0x11
#define HWIO_UNCORR_ERR_SEV_OFF_UNEXP_CMPLT_ERR_SEVERITY_BMSK                                               0x10000
#define HWIO_UNCORR_ERR_SEV_OFF_UNEXP_CMPLT_ERR_SEVERITY_SHFT                                                  0x10
#define HWIO_UNCORR_ERR_SEV_OFF_CMPLT_ABORT_ERR_SEVERITY_BMSK                                                0x8000
#define HWIO_UNCORR_ERR_SEV_OFF_CMPLT_ABORT_ERR_SEVERITY_SHFT                                                   0xf
#define HWIO_UNCORR_ERR_SEV_OFF_CMPLT_TIMEOUT_ERR_SEVERITY_BMSK                                              0x4000
#define HWIO_UNCORR_ERR_SEV_OFF_CMPLT_TIMEOUT_ERR_SEVERITY_SHFT                                                 0xe
#define HWIO_UNCORR_ERR_SEV_OFF_FC_PROTOCOL_ERR_SEVERITY_BMSK                                                0x2000
#define HWIO_UNCORR_ERR_SEV_OFF_FC_PROTOCOL_ERR_SEVERITY_SHFT                                                   0xd
#define HWIO_UNCORR_ERR_SEV_OFF_POIS_TLP_ERR_SEVERITY_BMSK                                                   0x1000
#define HWIO_UNCORR_ERR_SEV_OFF_POIS_TLP_ERR_SEVERITY_SHFT                                                      0xc
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_6_BMSK                                                                  0xfc0
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_6_SHFT                                                                    0x6
#define HWIO_UNCORR_ERR_SEV_OFF_SUR_DWN_ERR_SEVERITY_BMSK                                                      0x20
#define HWIO_UNCORR_ERR_SEV_OFF_SUR_DWN_ERR_SEVERITY_SHFT                                                       0x5
#define HWIO_UNCORR_ERR_SEV_OFF_DL_PROTOCOL_ERR_SEVERITY_BMSK                                                  0x10
#define HWIO_UNCORR_ERR_SEV_OFF_DL_PROTOCOL_ERR_SEVERITY_SHFT                                                   0x4
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_0_BMSK                                                                    0xf
#define HWIO_UNCORR_ERR_SEV_OFF_RSVDP_0_SHFT                                                                    0x0

#define HWIO_CORR_ERR_STATUS_OFF_ADDR(x)                                                                 ((x) + 0x00000110)
#define HWIO_CORR_ERR_STATUS_OFF_RMSK                                                                    0xffffffff
#define HWIO_CORR_ERR_STATUS_OFF_ATTR                                                                           0x3
#define HWIO_CORR_ERR_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_CORR_ERR_STATUS_OFF_ADDR(x), HWIO_CORR_ERR_STATUS_OFF_RMSK)
#define HWIO_CORR_ERR_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_CORR_ERR_STATUS_OFF_ADDR(x), m)
#define HWIO_CORR_ERR_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_CORR_ERR_STATUS_OFF_ADDR(x),v)
#define HWIO_CORR_ERR_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CORR_ERR_STATUS_OFF_ADDR(x),m,v,HWIO_CORR_ERR_STATUS_OFF_IN(x))
#define HWIO_CORR_ERR_STATUS_OFF_RSVDP_16_BMSK                                                           0xffff0000
#define HWIO_CORR_ERR_STATUS_OFF_RSVDP_16_SHFT                                                                 0x10
#define HWIO_CORR_ERR_STATUS_OFF_HEADER_LOG_OVERFLOW_STATUS_BMSK                                             0x8000
#define HWIO_CORR_ERR_STATUS_OFF_HEADER_LOG_OVERFLOW_STATUS_SHFT                                                0xf
#define HWIO_CORR_ERR_STATUS_OFF_CORRECTED_INT_ERR_STATUS_BMSK                                               0x4000
#define HWIO_CORR_ERR_STATUS_OFF_CORRECTED_INT_ERR_STATUS_SHFT                                                  0xe
#define HWIO_CORR_ERR_STATUS_OFF_ADVISORY_NON_FATAL_ERR_STATUS_BMSK                                          0x2000
#define HWIO_CORR_ERR_STATUS_OFF_ADVISORY_NON_FATAL_ERR_STATUS_SHFT                                             0xd
#define HWIO_CORR_ERR_STATUS_OFF_RPL_TIMER_TIMEOUT_STATUS_BMSK                                               0x1000
#define HWIO_CORR_ERR_STATUS_OFF_RPL_TIMER_TIMEOUT_STATUS_SHFT                                                  0xc
#define HWIO_CORR_ERR_STATUS_OFF_RSVDP_9_BMSK                                                                 0xe00
#define HWIO_CORR_ERR_STATUS_OFF_RSVDP_9_SHFT                                                                   0x9
#define HWIO_CORR_ERR_STATUS_OFF_REPLAY_NO_ROLEOVER_STATUS_BMSK                                               0x100
#define HWIO_CORR_ERR_STATUS_OFF_REPLAY_NO_ROLEOVER_STATUS_SHFT                                                 0x8
#define HWIO_CORR_ERR_STATUS_OFF_BAD_DLLP_STATUS_BMSK                                                          0x80
#define HWIO_CORR_ERR_STATUS_OFF_BAD_DLLP_STATUS_SHFT                                                           0x7
#define HWIO_CORR_ERR_STATUS_OFF_BAD_TLP_STATUS_BMSK                                                           0x40
#define HWIO_CORR_ERR_STATUS_OFF_BAD_TLP_STATUS_SHFT                                                            0x6
#define HWIO_CORR_ERR_STATUS_OFF_RSVDP_1_BMSK                                                                  0x3e
#define HWIO_CORR_ERR_STATUS_OFF_RSVDP_1_SHFT                                                                   0x1
#define HWIO_CORR_ERR_STATUS_OFF_RX_ERR_STATUS_BMSK                                                             0x1
#define HWIO_CORR_ERR_STATUS_OFF_RX_ERR_STATUS_SHFT                                                             0x0

#define HWIO_CORR_ERR_MASK_OFF_ADDR(x)                                                                   ((x) + 0x00000114)
#define HWIO_CORR_ERR_MASK_OFF_RMSK                                                                      0xffffffff
#define HWIO_CORR_ERR_MASK_OFF_ATTR                                                                             0x3
#define HWIO_CORR_ERR_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_CORR_ERR_MASK_OFF_ADDR(x), HWIO_CORR_ERR_MASK_OFF_RMSK)
#define HWIO_CORR_ERR_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_CORR_ERR_MASK_OFF_ADDR(x), m)
#define HWIO_CORR_ERR_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_CORR_ERR_MASK_OFF_ADDR(x),v)
#define HWIO_CORR_ERR_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CORR_ERR_MASK_OFF_ADDR(x),m,v,HWIO_CORR_ERR_MASK_OFF_IN(x))
#define HWIO_CORR_ERR_MASK_OFF_RSVDP_16_BMSK                                                             0xffff0000
#define HWIO_CORR_ERR_MASK_OFF_RSVDP_16_SHFT                                                                   0x10
#define HWIO_CORR_ERR_MASK_OFF_HEADER_LOG_OVERFLOW_MASK_BMSK                                                 0x8000
#define HWIO_CORR_ERR_MASK_OFF_HEADER_LOG_OVERFLOW_MASK_SHFT                                                    0xf
#define HWIO_CORR_ERR_MASK_OFF_CORRECTED_INT_ERR_MASK_BMSK                                                   0x4000
#define HWIO_CORR_ERR_MASK_OFF_CORRECTED_INT_ERR_MASK_SHFT                                                      0xe
#define HWIO_CORR_ERR_MASK_OFF_ADVISORY_NON_FATAL_ERR_MASK_BMSK                                              0x2000
#define HWIO_CORR_ERR_MASK_OFF_ADVISORY_NON_FATAL_ERR_MASK_SHFT                                                 0xd
#define HWIO_CORR_ERR_MASK_OFF_RPL_TIMER_TIMEOUT_MASK_BMSK                                                   0x1000
#define HWIO_CORR_ERR_MASK_OFF_RPL_TIMER_TIMEOUT_MASK_SHFT                                                      0xc
#define HWIO_CORR_ERR_MASK_OFF_RSVDP_9_BMSK                                                                   0xe00
#define HWIO_CORR_ERR_MASK_OFF_RSVDP_9_SHFT                                                                     0x9
#define HWIO_CORR_ERR_MASK_OFF_REPLAY_NO_ROLEOVER_MASK_BMSK                                                   0x100
#define HWIO_CORR_ERR_MASK_OFF_REPLAY_NO_ROLEOVER_MASK_SHFT                                                     0x8
#define HWIO_CORR_ERR_MASK_OFF_BAD_DLLP_MASK_BMSK                                                              0x80
#define HWIO_CORR_ERR_MASK_OFF_BAD_DLLP_MASK_SHFT                                                               0x7
#define HWIO_CORR_ERR_MASK_OFF_BAD_TLP_MASK_BMSK                                                               0x40
#define HWIO_CORR_ERR_MASK_OFF_BAD_TLP_MASK_SHFT                                                                0x6
#define HWIO_CORR_ERR_MASK_OFF_RSVDP_1_BMSK                                                                    0x3e
#define HWIO_CORR_ERR_MASK_OFF_RSVDP_1_SHFT                                                                     0x1
#define HWIO_CORR_ERR_MASK_OFF_RX_ERR_MASK_BMSK                                                                 0x1
#define HWIO_CORR_ERR_MASK_OFF_RX_ERR_MASK_SHFT                                                                 0x0

#define HWIO_ADV_ERR_CAP_CTRL_OFF_ADDR(x)                                                                ((x) + 0x00000118)
#define HWIO_ADV_ERR_CAP_CTRL_OFF_RMSK                                                                   0xffffffff
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ATTR                                                                          0x3
#define HWIO_ADV_ERR_CAP_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_ADV_ERR_CAP_CTRL_OFF_ADDR(x), HWIO_ADV_ERR_CAP_CTRL_OFF_RMSK)
#define HWIO_ADV_ERR_CAP_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_ADV_ERR_CAP_CTRL_OFF_ADDR(x), m)
#define HWIO_ADV_ERR_CAP_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_ADV_ERR_CAP_CTRL_OFF_ADDR(x),v)
#define HWIO_ADV_ERR_CAP_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ADV_ERR_CAP_CTRL_OFF_ADDR(x),m,v,HWIO_ADV_ERR_CAP_CTRL_OFF_IN(x))
#define HWIO_ADV_ERR_CAP_CTRL_OFF_RSVDP_12_BMSK                                                          0xfffff000
#define HWIO_ADV_ERR_CAP_CTRL_OFF_RSVDP_12_SHFT                                                                 0xc
#define HWIO_ADV_ERR_CAP_CTRL_OFF_TLP_PRFX_LOG_PRESENT_BMSK                                                   0x800
#define HWIO_ADV_ERR_CAP_CTRL_OFF_TLP_PRFX_LOG_PRESENT_SHFT                                                     0xb
#define HWIO_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_EN_BMSK                                                     0x400
#define HWIO_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_EN_SHFT                                                       0xa
#define HWIO_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_CAP_BMSK                                                    0x200
#define HWIO_ADV_ERR_CAP_CTRL_OFF_MULTIPLE_HEADER_CAP_SHFT                                                      0x9
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_EN_BMSK                                                          0x100
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_EN_SHFT                                                            0x8
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_CAP_BMSK                                                          0x80
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ECRC_CHECK_CAP_SHFT                                                           0x7
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_EN_BMSK                                                             0x40
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_EN_SHFT                                                              0x6
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_CAP_BMSK                                                            0x20
#define HWIO_ADV_ERR_CAP_CTRL_OFF_ECRC_GEN_CAP_SHFT                                                             0x5
#define HWIO_ADV_ERR_CAP_CTRL_OFF_FIRST_ERR_POINTER_BMSK                                                       0x1f
#define HWIO_ADV_ERR_CAP_CTRL_OFF_FIRST_ERR_POINTER_SHFT                                                        0x0

#define HWIO_HDR_LOG_0_OFF_ADDR(x)                                                                       ((x) + 0x0000011c)
#define HWIO_HDR_LOG_0_OFF_RMSK                                                                          0xffffffff
#define HWIO_HDR_LOG_0_OFF_ATTR                                                                                 0x1
#define HWIO_HDR_LOG_0_OFF_IN(x)      \
        in_dword_masked(HWIO_HDR_LOG_0_OFF_ADDR(x), HWIO_HDR_LOG_0_OFF_RMSK)
#define HWIO_HDR_LOG_0_OFF_INM(x, m)      \
        in_dword_masked(HWIO_HDR_LOG_0_OFF_ADDR(x), m)
#define HWIO_HDR_LOG_0_OFF_FIRST_DWORD_FOURTH_BYTE_BMSK                                                  0xff000000
#define HWIO_HDR_LOG_0_OFF_FIRST_DWORD_FOURTH_BYTE_SHFT                                                        0x18
#define HWIO_HDR_LOG_0_OFF_FIRST_DWORD_THIRD_BYTE_BMSK                                                     0xff0000
#define HWIO_HDR_LOG_0_OFF_FIRST_DWORD_THIRD_BYTE_SHFT                                                         0x10
#define HWIO_HDR_LOG_0_OFF_FIRST_DWORD_SECOND_BYTE_BMSK                                                      0xff00
#define HWIO_HDR_LOG_0_OFF_FIRST_DWORD_SECOND_BYTE_SHFT                                                         0x8
#define HWIO_HDR_LOG_0_OFF_FIRST_DWORD_FIRST_BYTE_BMSK                                                         0xff
#define HWIO_HDR_LOG_0_OFF_FIRST_DWORD_FIRST_BYTE_SHFT                                                          0x0

#define HWIO_HDR_LOG_1_OFF_ADDR(x)                                                                       ((x) + 0x00000120)
#define HWIO_HDR_LOG_1_OFF_RMSK                                                                          0xffffffff
#define HWIO_HDR_LOG_1_OFF_ATTR                                                                                 0x1
#define HWIO_HDR_LOG_1_OFF_IN(x)      \
        in_dword_masked(HWIO_HDR_LOG_1_OFF_ADDR(x), HWIO_HDR_LOG_1_OFF_RMSK)
#define HWIO_HDR_LOG_1_OFF_INM(x, m)      \
        in_dword_masked(HWIO_HDR_LOG_1_OFF_ADDR(x), m)
#define HWIO_HDR_LOG_1_OFF_SECOND_DWORD_FOURTH_BYTE_BMSK                                                 0xff000000
#define HWIO_HDR_LOG_1_OFF_SECOND_DWORD_FOURTH_BYTE_SHFT                                                       0x18
#define HWIO_HDR_LOG_1_OFF_SECOND_DWORD_THIRD_BYTE_BMSK                                                    0xff0000
#define HWIO_HDR_LOG_1_OFF_SECOND_DWORD_THIRD_BYTE_SHFT                                                        0x10
#define HWIO_HDR_LOG_1_OFF_SECOND_DWORD_SECOND_BYTE_BMSK                                                     0xff00
#define HWIO_HDR_LOG_1_OFF_SECOND_DWORD_SECOND_BYTE_SHFT                                                        0x8
#define HWIO_HDR_LOG_1_OFF_SECOND_DWORD_FIRST_BYTE_BMSK                                                        0xff
#define HWIO_HDR_LOG_1_OFF_SECOND_DWORD_FIRST_BYTE_SHFT                                                         0x0

#define HWIO_HDR_LOG_2_OFF_ADDR(x)                                                                       ((x) + 0x00000124)
#define HWIO_HDR_LOG_2_OFF_RMSK                                                                          0xffffffff
#define HWIO_HDR_LOG_2_OFF_ATTR                                                                                 0x1
#define HWIO_HDR_LOG_2_OFF_IN(x)      \
        in_dword_masked(HWIO_HDR_LOG_2_OFF_ADDR(x), HWIO_HDR_LOG_2_OFF_RMSK)
#define HWIO_HDR_LOG_2_OFF_INM(x, m)      \
        in_dword_masked(HWIO_HDR_LOG_2_OFF_ADDR(x), m)
#define HWIO_HDR_LOG_2_OFF_THIRD_DWORD_FOURTH_BYTE_BMSK                                                  0xff000000
#define HWIO_HDR_LOG_2_OFF_THIRD_DWORD_FOURTH_BYTE_SHFT                                                        0x18
#define HWIO_HDR_LOG_2_OFF_THIRD_DWORD_THIRD_BYTE_BMSK                                                     0xff0000
#define HWIO_HDR_LOG_2_OFF_THIRD_DWORD_THIRD_BYTE_SHFT                                                         0x10
#define HWIO_HDR_LOG_2_OFF_THIRD_DWORD_SECOND_BYTE_BMSK                                                      0xff00
#define HWIO_HDR_LOG_2_OFF_THIRD_DWORD_SECOND_BYTE_SHFT                                                         0x8
#define HWIO_HDR_LOG_2_OFF_THIRD_DWORD_FIRST_BYTE_BMSK                                                         0xff
#define HWIO_HDR_LOG_2_OFF_THIRD_DWORD_FIRST_BYTE_SHFT                                                          0x0

#define HWIO_HDR_LOG_3_OFF_ADDR(x)                                                                       ((x) + 0x00000128)
#define HWIO_HDR_LOG_3_OFF_RMSK                                                                          0xffffffff
#define HWIO_HDR_LOG_3_OFF_ATTR                                                                                 0x1
#define HWIO_HDR_LOG_3_OFF_IN(x)      \
        in_dword_masked(HWIO_HDR_LOG_3_OFF_ADDR(x), HWIO_HDR_LOG_3_OFF_RMSK)
#define HWIO_HDR_LOG_3_OFF_INM(x, m)      \
        in_dword_masked(HWIO_HDR_LOG_3_OFF_ADDR(x), m)
#define HWIO_HDR_LOG_3_OFF_FOURTH_DWORD_FOURTH_BYTE_BMSK                                                 0xff000000
#define HWIO_HDR_LOG_3_OFF_FOURTH_DWORD_FOURTH_BYTE_SHFT                                                       0x18
#define HWIO_HDR_LOG_3_OFF_FOURTH_DWORD_THIRD_BYTE_BMSK                                                    0xff0000
#define HWIO_HDR_LOG_3_OFF_FOURTH_DWORD_THIRD_BYTE_SHFT                                                        0x10
#define HWIO_HDR_LOG_3_OFF_FOURTH_DWORD_SECOND_BYTE_BMSK                                                     0xff00
#define HWIO_HDR_LOG_3_OFF_FOURTH_DWORD_SECOND_BYTE_SHFT                                                        0x8
#define HWIO_HDR_LOG_3_OFF_FOURTH_DWORD_FIRST_BYTE_BMSK                                                        0xff
#define HWIO_HDR_LOG_3_OFF_FOURTH_DWORD_FIRST_BYTE_SHFT                                                         0x0

#define HWIO_ROOT_ERR_CMD_OFF_ADDR(x)                                                                    ((x) + 0x0000012c)
#define HWIO_ROOT_ERR_CMD_OFF_RMSK                                                                       0xffffffff
#define HWIO_ROOT_ERR_CMD_OFF_ATTR                                                                              0x3
#define HWIO_ROOT_ERR_CMD_OFF_IN(x)      \
        in_dword_masked(HWIO_ROOT_ERR_CMD_OFF_ADDR(x), HWIO_ROOT_ERR_CMD_OFF_RMSK)
#define HWIO_ROOT_ERR_CMD_OFF_INM(x, m)      \
        in_dword_masked(HWIO_ROOT_ERR_CMD_OFF_ADDR(x), m)
#define HWIO_ROOT_ERR_CMD_OFF_OUT(x, v)      \
        out_dword(HWIO_ROOT_ERR_CMD_OFF_ADDR(x),v)
#define HWIO_ROOT_ERR_CMD_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ROOT_ERR_CMD_OFF_ADDR(x),m,v,HWIO_ROOT_ERR_CMD_OFF_IN(x))
#define HWIO_ROOT_ERR_CMD_OFF_RSVDP_3_BMSK                                                               0xfffffff8
#define HWIO_ROOT_ERR_CMD_OFF_RSVDP_3_SHFT                                                                      0x3
#define HWIO_ROOT_ERR_CMD_OFF_FATAL_ERR_REPORTING_EN_BMSK                                                       0x4
#define HWIO_ROOT_ERR_CMD_OFF_FATAL_ERR_REPORTING_EN_SHFT                                                       0x2
#define HWIO_ROOT_ERR_CMD_OFF_NON_FATAL_ERR_REPORTING_EN_BMSK                                                   0x2
#define HWIO_ROOT_ERR_CMD_OFF_NON_FATAL_ERR_REPORTING_EN_SHFT                                                   0x1
#define HWIO_ROOT_ERR_CMD_OFF_CORR_ERR_REPORTING_EN_BMSK                                                        0x1
#define HWIO_ROOT_ERR_CMD_OFF_CORR_ERR_REPORTING_EN_SHFT                                                        0x0

#define HWIO_ROOT_ERR_STATUS_OFF_ADDR(x)                                                                 ((x) + 0x00000130)
#define HWIO_ROOT_ERR_STATUS_OFF_RMSK                                                                    0xffffffff
#define HWIO_ROOT_ERR_STATUS_OFF_ATTR                                                                           0x3
#define HWIO_ROOT_ERR_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_ROOT_ERR_STATUS_OFF_ADDR(x), HWIO_ROOT_ERR_STATUS_OFF_RMSK)
#define HWIO_ROOT_ERR_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_ROOT_ERR_STATUS_OFF_ADDR(x), m)
#define HWIO_ROOT_ERR_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_ROOT_ERR_STATUS_OFF_ADDR(x),v)
#define HWIO_ROOT_ERR_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ROOT_ERR_STATUS_OFF_ADDR(x),m,v,HWIO_ROOT_ERR_STATUS_OFF_IN(x))
#define HWIO_ROOT_ERR_STATUS_OFF_ADV_ERR_INT_MSG_NUM_BMSK                                                0xf8000000
#define HWIO_ROOT_ERR_STATUS_OFF_ADV_ERR_INT_MSG_NUM_SHFT                                                      0x1b
#define HWIO_ROOT_ERR_STATUS_OFF_RSVDP_7_BMSK                                                             0x7ffff80
#define HWIO_ROOT_ERR_STATUS_OFF_RSVDP_7_SHFT                                                                   0x7
#define HWIO_ROOT_ERR_STATUS_OFF_FATAL_ERR_MSG_RX_BMSK                                                         0x40
#define HWIO_ROOT_ERR_STATUS_OFF_FATAL_ERR_MSG_RX_SHFT                                                          0x6
#define HWIO_ROOT_ERR_STATUS_OFF_NON_FATAL_ERR_MSG_RX_BMSK                                                     0x20
#define HWIO_ROOT_ERR_STATUS_OFF_NON_FATAL_ERR_MSG_RX_SHFT                                                      0x5
#define HWIO_ROOT_ERR_STATUS_OFF_FIRST_UNCORR_FATAL_BMSK                                                       0x10
#define HWIO_ROOT_ERR_STATUS_OFF_FIRST_UNCORR_FATAL_SHFT                                                        0x4
#define HWIO_ROOT_ERR_STATUS_OFF_MUL_ERR_FATAL_NON_FATAL_RX_BMSK                                                0x8
#define HWIO_ROOT_ERR_STATUS_OFF_MUL_ERR_FATAL_NON_FATAL_RX_SHFT                                                0x3
#define HWIO_ROOT_ERR_STATUS_OFF_ERR_FATAL_NON_FATAL_RX_BMSK                                                    0x4
#define HWIO_ROOT_ERR_STATUS_OFF_ERR_FATAL_NON_FATAL_RX_SHFT                                                    0x2
#define HWIO_ROOT_ERR_STATUS_OFF_MUL_ERR_COR_RX_BMSK                                                            0x2
#define HWIO_ROOT_ERR_STATUS_OFF_MUL_ERR_COR_RX_SHFT                                                            0x1
#define HWIO_ROOT_ERR_STATUS_OFF_ERR_COR_RX_BMSK                                                                0x1
#define HWIO_ROOT_ERR_STATUS_OFF_ERR_COR_RX_SHFT                                                                0x0

#define HWIO_ERR_SRC_ID_OFF_ADDR(x)                                                                      ((x) + 0x00000134)
#define HWIO_ERR_SRC_ID_OFF_RMSK                                                                         0xffffffff
#define HWIO_ERR_SRC_ID_OFF_ATTR                                                                                0x1
#define HWIO_ERR_SRC_ID_OFF_IN(x)      \
        in_dword_masked(HWIO_ERR_SRC_ID_OFF_ADDR(x), HWIO_ERR_SRC_ID_OFF_RMSK)
#define HWIO_ERR_SRC_ID_OFF_INM(x, m)      \
        in_dword_masked(HWIO_ERR_SRC_ID_OFF_ADDR(x), m)
#define HWIO_ERR_SRC_ID_OFF_ERR_FATAL_NON_FATAL_SOURCE_ID_BMSK                                           0xffff0000
#define HWIO_ERR_SRC_ID_OFF_ERR_FATAL_NON_FATAL_SOURCE_ID_SHFT                                                 0x10
#define HWIO_ERR_SRC_ID_OFF_ERR_COR_SOURCE_ID_BMSK                                                           0xffff
#define HWIO_ERR_SRC_ID_OFF_ERR_COR_SOURCE_ID_SHFT                                                              0x0

#define HWIO_TLP_PREFIX_LOG_1_OFF_ADDR(x)                                                                ((x) + 0x00000138)
#define HWIO_TLP_PREFIX_LOG_1_OFF_RMSK                                                                   0xffffffff
#define HWIO_TLP_PREFIX_LOG_1_OFF_ATTR                                                                          0x1
#define HWIO_TLP_PREFIX_LOG_1_OFF_IN(x)      \
        in_dword_masked(HWIO_TLP_PREFIX_LOG_1_OFF_ADDR(x), HWIO_TLP_PREFIX_LOG_1_OFF_RMSK)
#define HWIO_TLP_PREFIX_LOG_1_OFF_INM(x, m)      \
        in_dword_masked(HWIO_TLP_PREFIX_LOG_1_OFF_ADDR(x), m)
#define HWIO_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FOURTH_BYTE_BMSK                                     0xff000000
#define HWIO_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FOURTH_BYTE_SHFT                                           0x18
#define HWIO_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_THIRD_BYTE_BMSK                                        0xff0000
#define HWIO_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_THIRD_BYTE_SHFT                                            0x10
#define HWIO_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_SECOND_BYTE_BMSK                                         0xff00
#define HWIO_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_SECOND_BYTE_SHFT                                            0x8
#define HWIO_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FIRST_BYTE_BMSK                                            0xff
#define HWIO_TLP_PREFIX_LOG_1_OFF_CFG_TLP_PFX_LOG_1_FIRST_BYTE_SHFT                                             0x0

#define HWIO_TLP_PREFIX_LOG_2_OFF_ADDR(x)                                                                ((x) + 0x0000013c)
#define HWIO_TLP_PREFIX_LOG_2_OFF_RMSK                                                                   0xffffffff
#define HWIO_TLP_PREFIX_LOG_2_OFF_ATTR                                                                          0x1
#define HWIO_TLP_PREFIX_LOG_2_OFF_IN(x)      \
        in_dword_masked(HWIO_TLP_PREFIX_LOG_2_OFF_ADDR(x), HWIO_TLP_PREFIX_LOG_2_OFF_RMSK)
#define HWIO_TLP_PREFIX_LOG_2_OFF_INM(x, m)      \
        in_dword_masked(HWIO_TLP_PREFIX_LOG_2_OFF_ADDR(x), m)
#define HWIO_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FOURTH_BYTE_BMSK                                     0xff000000
#define HWIO_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FOURTH_BYTE_SHFT                                           0x18
#define HWIO_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_THIRD_BYTE_BMSK                                        0xff0000
#define HWIO_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_THIRD_BYTE_SHFT                                            0x10
#define HWIO_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_SECOND_BYTE_BMSK                                         0xff00
#define HWIO_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_SECOND_BYTE_SHFT                                            0x8
#define HWIO_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FIRST_BYTE_BMSK                                            0xff
#define HWIO_TLP_PREFIX_LOG_2_OFF_CFG_TLP_PFX_LOG_2_FIRST_BYTE_SHFT                                             0x0

#define HWIO_TLP_PREFIX_LOG_3_OFF_ADDR(x)                                                                ((x) + 0x00000140)
#define HWIO_TLP_PREFIX_LOG_3_OFF_RMSK                                                                   0xffffffff
#define HWIO_TLP_PREFIX_LOG_3_OFF_ATTR                                                                          0x1
#define HWIO_TLP_PREFIX_LOG_3_OFF_IN(x)      \
        in_dword_masked(HWIO_TLP_PREFIX_LOG_3_OFF_ADDR(x), HWIO_TLP_PREFIX_LOG_3_OFF_RMSK)
#define HWIO_TLP_PREFIX_LOG_3_OFF_INM(x, m)      \
        in_dword_masked(HWIO_TLP_PREFIX_LOG_3_OFF_ADDR(x), m)
#define HWIO_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FOURTH_BYTE_BMSK                                     0xff000000
#define HWIO_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FOURTH_BYTE_SHFT                                           0x18
#define HWIO_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_THIRD_BYTE_BMSK                                        0xff0000
#define HWIO_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_THIRD_BYTE_SHFT                                            0x10
#define HWIO_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_SECOND_BYTE_BMSK                                         0xff00
#define HWIO_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_SECOND_BYTE_SHFT                                            0x8
#define HWIO_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FIRST_BYTE_BMSK                                            0xff
#define HWIO_TLP_PREFIX_LOG_3_OFF_CFG_TLP_PFX_LOG_3_FIRST_BYTE_SHFT                                             0x0

#define HWIO_TLP_PREFIX_LOG_4_OFF_ADDR(x)                                                                ((x) + 0x00000144)
#define HWIO_TLP_PREFIX_LOG_4_OFF_RMSK                                                                   0xffffffff
#define HWIO_TLP_PREFIX_LOG_4_OFF_ATTR                                                                          0x1
#define HWIO_TLP_PREFIX_LOG_4_OFF_IN(x)      \
        in_dword_masked(HWIO_TLP_PREFIX_LOG_4_OFF_ADDR(x), HWIO_TLP_PREFIX_LOG_4_OFF_RMSK)
#define HWIO_TLP_PREFIX_LOG_4_OFF_INM(x, m)      \
        in_dword_masked(HWIO_TLP_PREFIX_LOG_4_OFF_ADDR(x), m)
#define HWIO_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FOURTH_BYTE_BMSK                                     0xff000000
#define HWIO_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FOURTH_BYTE_SHFT                                           0x18
#define HWIO_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_THIRD_BYTE_BMSK                                        0xff0000
#define HWIO_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_THIRD_BYTE_SHFT                                            0x10
#define HWIO_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_SECOND_BYTE_BMSK                                         0xff00
#define HWIO_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_SECOND_BYTE_SHFT                                            0x8
#define HWIO_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FIRST_BYTE_BMSK                                            0xff
#define HWIO_TLP_PREFIX_LOG_4_OFF_CFG_TLP_PFX_LOG_4_FIRST_BYTE_SHFT                                             0x0

#define HWIO_TPH_EXT_CAP_HDR_REG_ADDR(x)                                                                 ((x) + 0x000001a8)
#define HWIO_TPH_EXT_CAP_HDR_REG_RMSK                                                                    0xffffffff
#define HWIO_TPH_EXT_CAP_HDR_REG_ATTR                                                                           0x3
#define HWIO_TPH_EXT_CAP_HDR_REG_IN(x)      \
        in_dword_masked(HWIO_TPH_EXT_CAP_HDR_REG_ADDR(x), HWIO_TPH_EXT_CAP_HDR_REG_RMSK)
#define HWIO_TPH_EXT_CAP_HDR_REG_INM(x, m)      \
        in_dword_masked(HWIO_TPH_EXT_CAP_HDR_REG_ADDR(x), m)
#define HWIO_TPH_EXT_CAP_HDR_REG_OUT(x, v)      \
        out_dword(HWIO_TPH_EXT_CAP_HDR_REG_ADDR(x),v)
#define HWIO_TPH_EXT_CAP_HDR_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TPH_EXT_CAP_HDR_REG_ADDR(x),m,v,HWIO_TPH_EXT_CAP_HDR_REG_IN(x))
#define HWIO_TPH_EXT_CAP_HDR_REG_TPH_REQ_NEXT_PTR_BMSK                                                   0xfff00000
#define HWIO_TPH_EXT_CAP_HDR_REG_TPH_REQ_NEXT_PTR_SHFT                                                         0x14
#define HWIO_TPH_EXT_CAP_HDR_REG_TPH_REQ_CAP_VER_BMSK                                                       0xf0000
#define HWIO_TPH_EXT_CAP_HDR_REG_TPH_REQ_CAP_VER_SHFT                                                          0x10
#define HWIO_TPH_EXT_CAP_HDR_REG_PCIE_EXT_CAP_ID_BMSK                                                        0xffff
#define HWIO_TPH_EXT_CAP_HDR_REG_PCIE_EXT_CAP_ID_SHFT                                                           0x0

#define HWIO_TPH_REQ_CAP_REG_REG_ADDR(x)                                                                 ((x) + 0x000001ac)
#define HWIO_TPH_REQ_CAP_REG_REG_RMSK                                                                    0xffffffff
#define HWIO_TPH_REQ_CAP_REG_REG_ATTR                                                                           0x3
#define HWIO_TPH_REQ_CAP_REG_REG_IN(x)      \
        in_dword_masked(HWIO_TPH_REQ_CAP_REG_REG_ADDR(x), HWIO_TPH_REQ_CAP_REG_REG_RMSK)
#define HWIO_TPH_REQ_CAP_REG_REG_INM(x, m)      \
        in_dword_masked(HWIO_TPH_REQ_CAP_REG_REG_ADDR(x), m)
#define HWIO_TPH_REQ_CAP_REG_REG_OUT(x, v)      \
        out_dword(HWIO_TPH_REQ_CAP_REG_REG_ADDR(x),v)
#define HWIO_TPH_REQ_CAP_REG_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TPH_REQ_CAP_REG_REG_ADDR(x),m,v,HWIO_TPH_REQ_CAP_REG_REG_IN(x))
#define HWIO_TPH_REQ_CAP_REG_REG_RSVDP_27_BMSK                                                           0xf8000000
#define HWIO_TPH_REQ_CAP_REG_REG_RSVDP_27_SHFT                                                                 0x1b
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_CAP_ST_TABLE_SIZE_BMSK                                           0x7ff0000
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_CAP_ST_TABLE_SIZE_SHFT                                                0x10
#define HWIO_TPH_REQ_CAP_REG_REG_RSVDP_11_BMSK                                                               0xf800
#define HWIO_TPH_REQ_CAP_REG_REG_RSVDP_11_SHFT                                                                  0xb
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_CAP_ST_TABLE_LOC_1_BMSK                                              0x400
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_CAP_ST_TABLE_LOC_1_SHFT                                                0xa
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_CAP_ST_TABLE_LOC_0_BMSK                                              0x200
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_CAP_ST_TABLE_LOC_0_SHFT                                                0x9
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_EXTENDED_TPH_BMSK                                                    0x100
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_EXTENDED_TPH_SHFT                                                      0x8
#define HWIO_TPH_REQ_CAP_REG_REG_RSVDP_3_BMSK                                                                  0xf8
#define HWIO_TPH_REQ_CAP_REG_REG_RSVDP_3_SHFT                                                                   0x3
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_DEVICE_SPEC_BMSK                                                       0x4
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_DEVICE_SPEC_SHFT                                                       0x2
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_CAP_INT_VEC_BMSK                                                       0x2
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_CAP_INT_VEC_SHFT                                                       0x1
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_NO_ST_MODE_BMSK                                                        0x1
#define HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_NO_ST_MODE_SHFT                                                        0x0

#define HWIO_TPH_REQ_CONTROL_REG_REG_ADDR(x)                                                             ((x) + 0x000001b0)
#define HWIO_TPH_REQ_CONTROL_REG_REG_RMSK                                                                0xffffffff
#define HWIO_TPH_REQ_CONTROL_REG_REG_ATTR                                                                       0x3
#define HWIO_TPH_REQ_CONTROL_REG_REG_IN(x)      \
        in_dword_masked(HWIO_TPH_REQ_CONTROL_REG_REG_ADDR(x), HWIO_TPH_REQ_CONTROL_REG_REG_RMSK)
#define HWIO_TPH_REQ_CONTROL_REG_REG_INM(x, m)      \
        in_dword_masked(HWIO_TPH_REQ_CONTROL_REG_REG_ADDR(x), m)
#define HWIO_TPH_REQ_CONTROL_REG_REG_OUT(x, v)      \
        out_dword(HWIO_TPH_REQ_CONTROL_REG_REG_ADDR(x),v)
#define HWIO_TPH_REQ_CONTROL_REG_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TPH_REQ_CONTROL_REG_REG_ADDR(x),m,v,HWIO_TPH_REQ_CONTROL_REG_REG_IN(x))
#define HWIO_TPH_REQ_CONTROL_REG_REG_RSVDP_10_BMSK                                                       0xfffffc00
#define HWIO_TPH_REQ_CONTROL_REG_REG_RSVDP_10_SHFT                                                              0xa
#define HWIO_TPH_REQ_CONTROL_REG_REG_TPH_REQ_CTRL_REQ_EN_BMSK                                                 0x300
#define HWIO_TPH_REQ_CONTROL_REG_REG_TPH_REQ_CTRL_REQ_EN_SHFT                                                   0x8
#define HWIO_TPH_REQ_CONTROL_REG_REG_RSVDP_3_BMSK                                                              0xf8
#define HWIO_TPH_REQ_CONTROL_REG_REG_RSVDP_3_SHFT                                                               0x3
#define HWIO_TPH_REQ_CONTROL_REG_REG_TPH_REQ_ST_MODE_SELECT_BMSK                                                0x7
#define HWIO_TPH_REQ_CONTROL_REG_REG_TPH_REQ_ST_MODE_SELECT_SHFT                                                0x0

#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_ADDR(x)                                                        ((x) + 0x00000050)
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_RMSK                                                           0xffffffff
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_ATTR                                                                  0x3
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_IN(x)      \
        in_dword_masked(HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_ADDR(x), HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_RMSK)
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_INM(x, m)      \
        in_dword_masked(HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_ADDR(x), m)
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_OUT(x, v)      \
        out_dword(HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_ADDR(x),v)
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_ADDR(x),m,v,HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_IN(x))
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_RSVDP_25_BMSK                                                  0xfe000000
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_RSVDP_25_SHFT                                                        0x19
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_PVM_SUPPORT_BMSK                                            0x1000000
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_PVM_SUPPORT_SHFT                                                 0x18
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_64_BIT_ADDR_CAP_BMSK                                     0x800000
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_64_BIT_ADDR_CAP_SHFT                                         0x17
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_MULTIPLE_MSG_EN_BMSK                                     0x700000
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_MULTIPLE_MSG_EN_SHFT                                         0x14
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_MULTIPLE_MSG_CAP_BMSK                                     0xe0000
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_MULTIPLE_MSG_CAP_SHFT                                        0x11
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_ENABLE_BMSK                                               0x10000
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_ENABLE_SHFT                                                  0x10
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_CAP_NEXT_OFFSET_BMSK                                       0xff00
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_CAP_NEXT_OFFSET_SHFT                                          0x8
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_CAP_ID_BMSK                                                  0xff
#define HWIO_PCI_MSI_CAP_ID_NEXT_CTRL_REG_PCI_MSI_CAP_ID_SHFT                                                   0x0

#define HWIO_MSI_CAP_OFF_04H_REG_ADDR(x)                                                                 ((x) + 0x00000054)
#define HWIO_MSI_CAP_OFF_04H_REG_RMSK                                                                    0xffffffff
#define HWIO_MSI_CAP_OFF_04H_REG_ATTR                                                                           0x3
#define HWIO_MSI_CAP_OFF_04H_REG_IN(x)      \
        in_dword_masked(HWIO_MSI_CAP_OFF_04H_REG_ADDR(x), HWIO_MSI_CAP_OFF_04H_REG_RMSK)
#define HWIO_MSI_CAP_OFF_04H_REG_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CAP_OFF_04H_REG_ADDR(x), m)
#define HWIO_MSI_CAP_OFF_04H_REG_OUT(x, v)      \
        out_dword(HWIO_MSI_CAP_OFF_04H_REG_ADDR(x),v)
#define HWIO_MSI_CAP_OFF_04H_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CAP_OFF_04H_REG_ADDR(x),m,v,HWIO_MSI_CAP_OFF_04H_REG_IN(x))
#define HWIO_MSI_CAP_OFF_04H_REG_PCI_MSI_CAP_OFF_04H_BMSK                                                0xfffffffc
#define HWIO_MSI_CAP_OFF_04H_REG_PCI_MSI_CAP_OFF_04H_SHFT                                                       0x2
#define HWIO_MSI_CAP_OFF_04H_REG_RSVDP_0_BMSK                                                                   0x3
#define HWIO_MSI_CAP_OFF_04H_REG_RSVDP_0_SHFT                                                                   0x0

#define HWIO_MSI_CAP_OFF_08H_REG_ADDR(x)                                                                 ((x) + 0x00000058)
#define HWIO_MSI_CAP_OFF_08H_REG_RMSK                                                                    0xffffffff
#define HWIO_MSI_CAP_OFF_08H_REG_ATTR                                                                           0x3
#define HWIO_MSI_CAP_OFF_08H_REG_IN(x)      \
        in_dword_masked(HWIO_MSI_CAP_OFF_08H_REG_ADDR(x), HWIO_MSI_CAP_OFF_08H_REG_RMSK)
#define HWIO_MSI_CAP_OFF_08H_REG_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CAP_OFF_08H_REG_ADDR(x), m)
#define HWIO_MSI_CAP_OFF_08H_REG_OUT(x, v)      \
        out_dword(HWIO_MSI_CAP_OFF_08H_REG_ADDR(x),v)
#define HWIO_MSI_CAP_OFF_08H_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CAP_OFF_08H_REG_ADDR(x),m,v,HWIO_MSI_CAP_OFF_08H_REG_IN(x))
#define HWIO_MSI_CAP_OFF_08H_REG_PCI_MSI_CAP_OFF_0AH_BMSK                                                0xffff0000
#define HWIO_MSI_CAP_OFF_08H_REG_PCI_MSI_CAP_OFF_0AH_SHFT                                                      0x10
#define HWIO_MSI_CAP_OFF_08H_REG_PCI_MSI_CAP_OFF_08H_BMSK                                                    0xffff
#define HWIO_MSI_CAP_OFF_08H_REG_PCI_MSI_CAP_OFF_08H_SHFT                                                       0x0

#define HWIO_MSI_CAP_OFF_0CH_REG_ADDR(x)                                                                 ((x) + 0x0000005c)
#define HWIO_MSI_CAP_OFF_0CH_REG_RMSK                                                                    0xffffffff
#define HWIO_MSI_CAP_OFF_0CH_REG_ATTR                                                                           0x3
#define HWIO_MSI_CAP_OFF_0CH_REG_IN(x)      \
        in_dword_masked(HWIO_MSI_CAP_OFF_0CH_REG_ADDR(x), HWIO_MSI_CAP_OFF_0CH_REG_RMSK)
#define HWIO_MSI_CAP_OFF_0CH_REG_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CAP_OFF_0CH_REG_ADDR(x), m)
#define HWIO_MSI_CAP_OFF_0CH_REG_OUT(x, v)      \
        out_dword(HWIO_MSI_CAP_OFF_0CH_REG_ADDR(x),v)
#define HWIO_MSI_CAP_OFF_0CH_REG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CAP_OFF_0CH_REG_ADDR(x),m,v,HWIO_MSI_CAP_OFF_0CH_REG_IN(x))
#define HWIO_MSI_CAP_OFF_0CH_REG_PCI_MSI_CAP_OFF_0EH_BMSK                                                0xffff0000
#define HWIO_MSI_CAP_OFF_0CH_REG_PCI_MSI_CAP_OFF_0EH_SHFT                                                      0x10
#define HWIO_MSI_CAP_OFF_0CH_REG_PCI_MSI_CAP_OFF_0CH_BMSK                                                    0xffff
#define HWIO_MSI_CAP_OFF_0CH_REG_PCI_MSI_CAP_OFF_0CH_SHFT                                                       0x0

#define HWIO_ACK_LATENCY_TIMER_OFF_ADDR(x)                                                               ((x) + 0x00000700)
#define HWIO_ACK_LATENCY_TIMER_OFF_RMSK                                                                  0xffffffff
#define HWIO_ACK_LATENCY_TIMER_OFF_ATTR                                                                         0x3
#define HWIO_ACK_LATENCY_TIMER_OFF_IN(x)      \
        in_dword_masked(HWIO_ACK_LATENCY_TIMER_OFF_ADDR(x), HWIO_ACK_LATENCY_TIMER_OFF_RMSK)
#define HWIO_ACK_LATENCY_TIMER_OFF_INM(x, m)      \
        in_dword_masked(HWIO_ACK_LATENCY_TIMER_OFF_ADDR(x), m)
#define HWIO_ACK_LATENCY_TIMER_OFF_OUT(x, v)      \
        out_dword(HWIO_ACK_LATENCY_TIMER_OFF_ADDR(x),v)
#define HWIO_ACK_LATENCY_TIMER_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ACK_LATENCY_TIMER_OFF_ADDR(x),m,v,HWIO_ACK_LATENCY_TIMER_OFF_IN(x))
#define HWIO_ACK_LATENCY_TIMER_OFF_REPLAY_TIME_LIMIT_BMSK                                                0xffff0000
#define HWIO_ACK_LATENCY_TIMER_OFF_REPLAY_TIME_LIMIT_SHFT                                                      0x10
#define HWIO_ACK_LATENCY_TIMER_OFF_ROUND_TRIP_LATENCY_TIME_LIMIT_BMSK                                        0xffff
#define HWIO_ACK_LATENCY_TIMER_OFF_ROUND_TRIP_LATENCY_TIME_LIMIT_SHFT                                           0x0

#define HWIO_VENDOR_SPEC_DLLP_OFF_ADDR(x)                                                                ((x) + 0x00000704)
#define HWIO_VENDOR_SPEC_DLLP_OFF_RMSK                                                                   0xffffffff
#define HWIO_VENDOR_SPEC_DLLP_OFF_ATTR                                                                          0x3
#define HWIO_VENDOR_SPEC_DLLP_OFF_IN(x)      \
        in_dword_masked(HWIO_VENDOR_SPEC_DLLP_OFF_ADDR(x), HWIO_VENDOR_SPEC_DLLP_OFF_RMSK)
#define HWIO_VENDOR_SPEC_DLLP_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VENDOR_SPEC_DLLP_OFF_ADDR(x), m)
#define HWIO_VENDOR_SPEC_DLLP_OFF_OUT(x, v)      \
        out_dword(HWIO_VENDOR_SPEC_DLLP_OFF_ADDR(x),v)
#define HWIO_VENDOR_SPEC_DLLP_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VENDOR_SPEC_DLLP_OFF_ADDR(x),m,v,HWIO_VENDOR_SPEC_DLLP_OFF_IN(x))
#define HWIO_VENDOR_SPEC_DLLP_OFF_VENDOR_SPEC_DLLP_BMSK                                                  0xffffffff
#define HWIO_VENDOR_SPEC_DLLP_OFF_VENDOR_SPEC_DLLP_SHFT                                                         0x0

#define HWIO_PORT_FORCE_OFF_ADDR(x)                                                                      ((x) + 0x00000708)
#define HWIO_PORT_FORCE_OFF_RMSK                                                                         0xffffffff
#define HWIO_PORT_FORCE_OFF_ATTR                                                                                0x3
#define HWIO_PORT_FORCE_OFF_IN(x)      \
        in_dword_masked(HWIO_PORT_FORCE_OFF_ADDR(x), HWIO_PORT_FORCE_OFF_RMSK)
#define HWIO_PORT_FORCE_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PORT_FORCE_OFF_ADDR(x), m)
#define HWIO_PORT_FORCE_OFF_OUT(x, v)      \
        out_dword(HWIO_PORT_FORCE_OFF_ADDR(x),v)
#define HWIO_PORT_FORCE_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PORT_FORCE_OFF_ADDR(x),m,v,HWIO_PORT_FORCE_OFF_IN(x))
#define HWIO_PORT_FORCE_OFF_CPL_SENT_COUNT_BMSK                                                          0xff000000
#define HWIO_PORT_FORCE_OFF_CPL_SENT_COUNT_SHFT                                                                0x18
#define HWIO_PORT_FORCE_OFF_RSVDP_22_BMSK                                                                  0xc00000
#define HWIO_PORT_FORCE_OFF_RSVDP_22_SHFT                                                                      0x16
#define HWIO_PORT_FORCE_OFF_LINK_STATE_BMSK                                                                0x3f0000
#define HWIO_PORT_FORCE_OFF_LINK_STATE_SHFT                                                                    0x10
#define HWIO_PORT_FORCE_OFF_FORCE_EN_BMSK                                                                    0x8000
#define HWIO_PORT_FORCE_OFF_FORCE_EN_SHFT                                                                       0xf
#define HWIO_PORT_FORCE_OFF_RSVDP_12_BMSK                                                                    0x7000
#define HWIO_PORT_FORCE_OFF_RSVDP_12_SHFT                                                                       0xc
#define HWIO_PORT_FORCE_OFF_FORCED_LTSSM_BMSK                                                                 0xf00
#define HWIO_PORT_FORCE_OFF_FORCED_LTSSM_SHFT                                                                   0x8
#define HWIO_PORT_FORCE_OFF_LINK_NUM_BMSK                                                                      0xff
#define HWIO_PORT_FORCE_OFF_LINK_NUM_SHFT                                                                       0x0

#define HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(x)                                                                 ((x) + 0x0000070c)
#define HWIO_ACK_F_ASPM_CTRL_OFF_RMSK                                                                    0xffffffff
#define HWIO_ACK_F_ASPM_CTRL_OFF_ATTR                                                                           0x3
#define HWIO_ACK_F_ASPM_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(x), HWIO_ACK_F_ASPM_CTRL_OFF_RMSK)
#define HWIO_ACK_F_ASPM_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(x), m)
#define HWIO_ACK_F_ASPM_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(x),v)
#define HWIO_ACK_F_ASPM_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(x),m,v,HWIO_ACK_F_ASPM_CTRL_OFF_IN(x))
#define HWIO_ACK_F_ASPM_CTRL_OFF_RSVDP_31_BMSK                                                           0x80000000
#define HWIO_ACK_F_ASPM_CTRL_OFF_RSVDP_31_SHFT                                                                 0x1f
#define HWIO_ACK_F_ASPM_CTRL_OFF_ENTER_ASPM_BMSK                                                         0x40000000
#define HWIO_ACK_F_ASPM_CTRL_OFF_ENTER_ASPM_SHFT                                                               0x1e
#define HWIO_ACK_F_ASPM_CTRL_OFF_L1_ENTRANCE_LATENCY_BMSK                                                0x38000000
#define HWIO_ACK_F_ASPM_CTRL_OFF_L1_ENTRANCE_LATENCY_SHFT                                                      0x1b
#define HWIO_ACK_F_ASPM_CTRL_OFF_L0S_ENTRANCE_LATENCY_BMSK                                                0x7000000
#define HWIO_ACK_F_ASPM_CTRL_OFF_L0S_ENTRANCE_LATENCY_SHFT                                                     0x18
#define HWIO_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_BMSK                                                     0xff0000
#define HWIO_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_SHFT                                                         0x10
#define HWIO_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS_BMSK                                                              0xff00
#define HWIO_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS_SHFT                                                                 0x8
#define HWIO_ACK_F_ASPM_CTRL_OFF_ACK_FREQ_BMSK                                                                 0xff
#define HWIO_ACK_F_ASPM_CTRL_OFF_ACK_FREQ_SHFT                                                                  0x0

#define HWIO_PORT_LINK_CTRL_OFF_ADDR(x)                                                                  ((x) + 0x00000710)
#define HWIO_PORT_LINK_CTRL_OFF_RMSK                                                                     0xff3fffff
#define HWIO_PORT_LINK_CTRL_OFF_ATTR                                                                            0x3
#define HWIO_PORT_LINK_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_PORT_LINK_CTRL_OFF_ADDR(x), HWIO_PORT_LINK_CTRL_OFF_RMSK)
#define HWIO_PORT_LINK_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PORT_LINK_CTRL_OFF_ADDR(x), m)
#define HWIO_PORT_LINK_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_PORT_LINK_CTRL_OFF_ADDR(x),v)
#define HWIO_PORT_LINK_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PORT_LINK_CTRL_OFF_ADDR(x),m,v,HWIO_PORT_LINK_CTRL_OFF_IN(x))
#define HWIO_PORT_LINK_CTRL_OFF_RSVDP_28_BMSK                                                            0xf0000000
#define HWIO_PORT_LINK_CTRL_OFF_RSVDP_28_SHFT                                                                  0x1c
#define HWIO_PORT_LINK_CTRL_OFF_TRANSMIT_LANE_REVERSALE_ENABLE_BMSK                                       0x8000000
#define HWIO_PORT_LINK_CTRL_OFF_TRANSMIT_LANE_REVERSALE_ENABLE_SHFT                                            0x1b
#define HWIO_PORT_LINK_CTRL_OFF_EXTENDED_SYNCH_BMSK                                                       0x4000000
#define HWIO_PORT_LINK_CTRL_OFF_EXTENDED_SYNCH_SHFT                                                            0x1a
#define HWIO_PORT_LINK_CTRL_OFF_CORRUPT_LCRC_ENABLE_BMSK                                                  0x2000000
#define HWIO_PORT_LINK_CTRL_OFF_CORRUPT_LCRC_ENABLE_SHFT                                                       0x19
#define HWIO_PORT_LINK_CTRL_OFF_BEACON_ENABLE_BMSK                                                        0x1000000
#define HWIO_PORT_LINK_CTRL_OFF_BEACON_ENABLE_SHFT                                                             0x18
#define HWIO_PORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK                                                          0x3f0000
#define HWIO_PORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT                                                              0x10
#define HWIO_PORT_LINK_CTRL_OFF_RSVDP_12_BMSK                                                                0xf000
#define HWIO_PORT_LINK_CTRL_OFF_RSVDP_12_SHFT                                                                   0xc
#define HWIO_PORT_LINK_CTRL_OFF_LINK_RATE_BMSK                                                                0xf00
#define HWIO_PORT_LINK_CTRL_OFF_LINK_RATE_SHFT                                                                  0x8
#define HWIO_PORT_LINK_CTRL_OFF_FAST_LINK_MODE_BMSK                                                            0x80
#define HWIO_PORT_LINK_CTRL_OFF_FAST_LINK_MODE_SHFT                                                             0x7
#define HWIO_PORT_LINK_CTRL_OFF_LINK_DISABLE_BMSK                                                              0x40
#define HWIO_PORT_LINK_CTRL_OFF_LINK_DISABLE_SHFT                                                               0x6
#define HWIO_PORT_LINK_CTRL_OFF_DLL_LINK_EN_BMSK                                                               0x20
#define HWIO_PORT_LINK_CTRL_OFF_DLL_LINK_EN_SHFT                                                                0x5
#define HWIO_PORT_LINK_CTRL_OFF_RSVDP_4_BMSK                                                                   0x10
#define HWIO_PORT_LINK_CTRL_OFF_RSVDP_4_SHFT                                                                    0x4
#define HWIO_PORT_LINK_CTRL_OFF_RESET_ASSERT_BMSK                                                               0x8
#define HWIO_PORT_LINK_CTRL_OFF_RESET_ASSERT_SHFT                                                               0x3
#define HWIO_PORT_LINK_CTRL_OFF_LOOPBACK_ENABLE_BMSK                                                            0x4
#define HWIO_PORT_LINK_CTRL_OFF_LOOPBACK_ENABLE_SHFT                                                            0x2
#define HWIO_PORT_LINK_CTRL_OFF_SCRAMBLE_DISABLE_BMSK                                                           0x2
#define HWIO_PORT_LINK_CTRL_OFF_SCRAMBLE_DISABLE_SHFT                                                           0x1
#define HWIO_PORT_LINK_CTRL_OFF_VENDOR_SPECIFIC_DLLP_REQ_BMSK                                                   0x1
#define HWIO_PORT_LINK_CTRL_OFF_VENDOR_SPECIFIC_DLLP_REQ_SHFT                                                   0x0

#define HWIO_LANE_SKEW_OFF_ADDR(x)                                                                       ((x) + 0x00000714)
#define HWIO_LANE_SKEW_OFF_RMSK                                                                          0xffffffff
#define HWIO_LANE_SKEW_OFF_ATTR                                                                                 0x3
#define HWIO_LANE_SKEW_OFF_IN(x)      \
        in_dword_masked(HWIO_LANE_SKEW_OFF_ADDR(x), HWIO_LANE_SKEW_OFF_RMSK)
#define HWIO_LANE_SKEW_OFF_INM(x, m)      \
        in_dword_masked(HWIO_LANE_SKEW_OFF_ADDR(x), m)
#define HWIO_LANE_SKEW_OFF_OUT(x, v)      \
        out_dword(HWIO_LANE_SKEW_OFF_ADDR(x),v)
#define HWIO_LANE_SKEW_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LANE_SKEW_OFF_ADDR(x),m,v,HWIO_LANE_SKEW_OFF_IN(x))
#define HWIO_LANE_SKEW_OFF_DISABLE_LANE_TO_LANE_DESKEW_BMSK                                              0x80000000
#define HWIO_LANE_SKEW_OFF_DISABLE_LANE_TO_LANE_DESKEW_SHFT                                                    0x1f
#define HWIO_LANE_SKEW_OFF_RSVDP_26_BMSK                                                                 0x7c000000
#define HWIO_LANE_SKEW_OFF_RSVDP_26_SHFT                                                                       0x1a
#define HWIO_LANE_SKEW_OFF_ACK_NAK_DISABLE_BMSK                                                           0x2000000
#define HWIO_LANE_SKEW_OFF_ACK_NAK_DISABLE_SHFT                                                                0x19
#define HWIO_LANE_SKEW_OFF_FLOW_CTRL_DISABLE_BMSK                                                         0x1000000
#define HWIO_LANE_SKEW_OFF_FLOW_CTRL_DISABLE_SHFT                                                              0x18
#define HWIO_LANE_SKEW_OFF_INSERT_LANE_SKEW_BMSK                                                           0xffffff
#define HWIO_LANE_SKEW_OFF_INSERT_LANE_SKEW_SHFT                                                                0x0

#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_ADDR(x)                                                         ((x) + 0x00000718)
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_RMSK                                                            0xffffffff
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_ATTR                                                                   0x3
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_IN(x)      \
        in_dword_masked(HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_ADDR(x), HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_RMSK)
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_INM(x, m)      \
        in_dword_masked(HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_ADDR(x), m)
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_OUT(x, v)      \
        out_dword(HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_ADDR(x),v)
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_ADDR(x),m,v,HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_IN(x))
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_RSVDP_29_BMSK                                                   0xe0000000
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_RSVDP_29_SHFT                                                         0x1d
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_UPDATE_FREQ_TIMER_BMSK                                          0x1f000000
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_UPDATE_FREQ_TIMER_SHFT                                                0x18
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_ACK_NAK_BMSK                                            0xf80000
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_ACK_NAK_SHFT                                                0x13
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_REPLAY_TIMER_BMSK                                        0x7c000
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_TIMER_MOD_REPLAY_TIMER_SHFT                                            0xe
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_RSVDP_8_BMSK                                                        0x3f00
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_RSVDP_8_SHFT                                                           0x8
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_MAX_FUNC_NUM_BMSK                                                     0xff
#define HWIO_TIMER_CTRL_MAX_FUNC_NUM_OFF_MAX_FUNC_NUM_SHFT                                                      0x0

#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_ADDR(x)                                                           ((x) + 0x0000071c)
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_RMSK                                                              0xffffffff
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_ATTR                                                                     0x3
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_IN(x)      \
        in_dword_masked(HWIO_SYMBOL_TIMER_FILTER_1_OFF_ADDR(x), HWIO_SYMBOL_TIMER_FILTER_1_OFF_RMSK)
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_INM(x, m)      \
        in_dword_masked(HWIO_SYMBOL_TIMER_FILTER_1_OFF_ADDR(x), m)
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_OUT(x, v)      \
        out_dword(HWIO_SYMBOL_TIMER_FILTER_1_OFF_ADDR(x),v)
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_SYMBOL_TIMER_FILTER_1_OFF_ADDR(x),m,v,HWIO_SYMBOL_TIMER_FILTER_1_OFF_IN(x))
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_BMSK                                                  0xffff0000
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_SHFT                                                        0x10
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_DISABLE_FC_WD_TIMER_BMSK                                              0x8000
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_DISABLE_FC_WD_TIMER_SHFT                                                 0xf
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_EIDLE_TIMER_BMSK                                                      0x7800
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_EIDLE_TIMER_SHFT                                                         0xb
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_SKP_INT_VAL_BMSK                                                       0x7ff
#define HWIO_SYMBOL_TIMER_FILTER_1_OFF_SKP_INT_VAL_SHFT                                                         0x0

#define HWIO_FILTER_MASK_2_OFF_ADDR(x)                                                                   ((x) + 0x00000720)
#define HWIO_FILTER_MASK_2_OFF_RMSK                                                                      0xffffffff
#define HWIO_FILTER_MASK_2_OFF_ATTR                                                                             0x3
#define HWIO_FILTER_MASK_2_OFF_IN(x)      \
        in_dword_masked(HWIO_FILTER_MASK_2_OFF_ADDR(x), HWIO_FILTER_MASK_2_OFF_RMSK)
#define HWIO_FILTER_MASK_2_OFF_INM(x, m)      \
        in_dword_masked(HWIO_FILTER_MASK_2_OFF_ADDR(x), m)
#define HWIO_FILTER_MASK_2_OFF_OUT(x, v)      \
        out_dword(HWIO_FILTER_MASK_2_OFF_ADDR(x),v)
#define HWIO_FILTER_MASK_2_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_FILTER_MASK_2_OFF_ADDR(x),m,v,HWIO_FILTER_MASK_2_OFF_IN(x))
#define HWIO_FILTER_MASK_2_OFF_MASK_RADM_2_BMSK                                                          0xffffffff
#define HWIO_FILTER_MASK_2_OFF_MASK_RADM_2_SHFT                                                                 0x0

#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_ADDR(x)                                              ((x) + 0x00000724)
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_RMSK                                                 0xffffffff
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_ATTR                                                        0x3
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_ADDR(x), HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_RMSK)
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_ADDR(x), m)
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_ADDR(x),v)
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_ADDR(x),m,v,HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_IN(x))
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_RSVDP_1_BMSK                                         0xfffffffe
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_RSVDP_1_SHFT                                                0x1
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_OB_RD_SPLIT_BURST_EN_BMSK                                   0x1
#define HWIO_AMBA_MUL_OB_DECOMP_NP_SUB_REQ_CTRL_OFF_OB_RD_SPLIT_BURST_EN_SHFT                                   0x0

#define HWIO_PL_DEBUG0_OFF_ADDR(x)                                                                       ((x) + 0x00000728)
#define HWIO_PL_DEBUG0_OFF_RMSK                                                                          0xffffffff
#define HWIO_PL_DEBUG0_OFF_ATTR                                                                                 0x1
#define HWIO_PL_DEBUG0_OFF_IN(x)      \
        in_dword_masked(HWIO_PL_DEBUG0_OFF_ADDR(x), HWIO_PL_DEBUG0_OFF_RMSK)
#define HWIO_PL_DEBUG0_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PL_DEBUG0_OFF_ADDR(x), m)
#define HWIO_PL_DEBUG0_OFF_DEB_REG_0_BMSK                                                                0xffffffff
#define HWIO_PL_DEBUG0_OFF_DEB_REG_0_SHFT                                                                       0x0

#define HWIO_PL_DEBUG1_OFF_ADDR(x)                                                                       ((x) + 0x0000072c)
#define HWIO_PL_DEBUG1_OFF_RMSK                                                                          0xffffffff
#define HWIO_PL_DEBUG1_OFF_ATTR                                                                                 0x1
#define HWIO_PL_DEBUG1_OFF_IN(x)      \
        in_dword_masked(HWIO_PL_DEBUG1_OFF_ADDR(x), HWIO_PL_DEBUG1_OFF_RMSK)
#define HWIO_PL_DEBUG1_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PL_DEBUG1_OFF_ADDR(x), m)
#define HWIO_PL_DEBUG1_OFF_DEB_REG_1_BMSK                                                                0xffffffff
#define HWIO_PL_DEBUG1_OFF_DEB_REG_1_SHFT                                                                       0x0

#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_ADDR(x)                                                           ((x) + 0x00000730)
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_ATTR                                                                     0x1
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_TX_P_FC_CREDIT_STATUS_OFF_ADDR(x), HWIO_TX_P_FC_CREDIT_STATUS_OFF_RMSK)
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_TX_P_FC_CREDIT_STATUS_OFF_ADDR(x), m)
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_RSVDP_20_BMSK                                                     0xfff00000
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_RSVDP_20_SHFT                                                           0x14
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_TX_P_HEADER_FC_CREDIT_BMSK                                           0xff000
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_TX_P_HEADER_FC_CREDIT_SHFT                                               0xc
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_TX_P_DATA_FC_CREDIT_BMSK                                               0xfff
#define HWIO_TX_P_FC_CREDIT_STATUS_OFF_TX_P_DATA_FC_CREDIT_SHFT                                                 0x0

#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_ADDR(x)                                                          ((x) + 0x00000734)
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_RMSK                                                             0xffffffff
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_ATTR                                                                    0x1
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_TX_NP_FC_CREDIT_STATUS_OFF_ADDR(x), HWIO_TX_NP_FC_CREDIT_STATUS_OFF_RMSK)
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_TX_NP_FC_CREDIT_STATUS_OFF_ADDR(x), m)
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_RSVDP_20_BMSK                                                    0xfff00000
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_RSVDP_20_SHFT                                                          0x14
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_HEADER_FC_CREDIT_BMSK                                         0xff000
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_HEADER_FC_CREDIT_SHFT                                             0xc
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_DATA_FC_CREDIT_BMSK                                             0xfff
#define HWIO_TX_NP_FC_CREDIT_STATUS_OFF_TX_NP_DATA_FC_CREDIT_SHFT                                               0x0

#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_ADDR(x)                                                         ((x) + 0x00000738)
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_RMSK                                                            0xffffffff
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_ATTR                                                                   0x1
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_ADDR(x), HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_RMSK)
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_ADDR(x), m)
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_RSVDP_20_BMSK                                                   0xfff00000
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_RSVDP_20_SHFT                                                         0x14
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_HEADER_FC_CREDIT_BMSK                                       0xff000
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_HEADER_FC_CREDIT_SHFT                                           0xc
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_DATA_FC_CREDIT_BMSK                                           0xfff
#define HWIO_TX_CPL_FC_CREDIT_STATUS_OFF_TX_CPL_DATA_FC_CREDIT_SHFT                                             0x0

#define HWIO_QUEUE_STATUS_OFF_ADDR(x)                                                                    ((x) + 0x0000073c)
#define HWIO_QUEUE_STATUS_OFF_RMSK                                                                       0xffffffff
#define HWIO_QUEUE_STATUS_OFF_ATTR                                                                              0x3
#define HWIO_QUEUE_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_QUEUE_STATUS_OFF_ADDR(x), HWIO_QUEUE_STATUS_OFF_RMSK)
#define HWIO_QUEUE_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_QUEUE_STATUS_OFF_ADDR(x), m)
#define HWIO_QUEUE_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_QUEUE_STATUS_OFF_ADDR(x),v)
#define HWIO_QUEUE_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QUEUE_STATUS_OFF_ADDR(x),m,v,HWIO_QUEUE_STATUS_OFF_IN(x))
#define HWIO_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_EN_BMSK                                             0x80000000
#define HWIO_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_EN_SHFT                                                   0x1f
#define HWIO_QUEUE_STATUS_OFF_RSVDP_29_BMSK                                                              0x60000000
#define HWIO_QUEUE_STATUS_OFF_RSVDP_29_SHFT                                                                    0x1d
#define HWIO_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_BMSK                                                0x1fff0000
#define HWIO_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_SHFT                                                      0x10
#define HWIO_QUEUE_STATUS_OFF_RSVDP_3_BMSK                                                                   0xfff8
#define HWIO_QUEUE_STATUS_OFF_RSVDP_3_SHFT                                                                      0x3
#define HWIO_QUEUE_STATUS_OFF_RX_QUEUE_NON_EMPTY_BMSK                                                           0x4
#define HWIO_QUEUE_STATUS_OFF_RX_QUEUE_NON_EMPTY_SHFT                                                           0x2
#define HWIO_QUEUE_STATUS_OFF_TX_RETRY_BUFFER_NE_BMSK                                                           0x2
#define HWIO_QUEUE_STATUS_OFF_TX_RETRY_BUFFER_NE_SHFT                                                           0x1
#define HWIO_QUEUE_STATUS_OFF_RX_TLP_FC_CREDIT_NON_RETURN_BMSK                                                  0x1
#define HWIO_QUEUE_STATUS_OFF_RX_TLP_FC_CREDIT_NON_RETURN_SHFT                                                  0x0

#define HWIO_VC_TX_ARBI_1_OFF_ADDR(x)                                                                    ((x) + 0x00000740)
#define HWIO_VC_TX_ARBI_1_OFF_RMSK                                                                       0xffffffff
#define HWIO_VC_TX_ARBI_1_OFF_ATTR                                                                              0x1
#define HWIO_VC_TX_ARBI_1_OFF_IN(x)      \
        in_dword_masked(HWIO_VC_TX_ARBI_1_OFF_ADDR(x), HWIO_VC_TX_ARBI_1_OFF_RMSK)
#define HWIO_VC_TX_ARBI_1_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VC_TX_ARBI_1_OFF_ADDR(x), m)
#define HWIO_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_3_BMSK                                                       0xff000000
#define HWIO_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_3_SHFT                                                             0x18
#define HWIO_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_2_BMSK                                                         0xff0000
#define HWIO_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_2_SHFT                                                             0x10
#define HWIO_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_1_BMSK                                                           0xff00
#define HWIO_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_1_SHFT                                                              0x8
#define HWIO_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_0_BMSK                                                             0xff
#define HWIO_VC_TX_ARBI_1_OFF_WRR_WEIGHT_VC_0_SHFT                                                              0x0

#define HWIO_VC_TX_ARBI_2_OFF_ADDR(x)                                                                    ((x) + 0x00000744)
#define HWIO_VC_TX_ARBI_2_OFF_RMSK                                                                       0xffffffff
#define HWIO_VC_TX_ARBI_2_OFF_ATTR                                                                              0x1
#define HWIO_VC_TX_ARBI_2_OFF_IN(x)      \
        in_dword_masked(HWIO_VC_TX_ARBI_2_OFF_ADDR(x), HWIO_VC_TX_ARBI_2_OFF_RMSK)
#define HWIO_VC_TX_ARBI_2_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VC_TX_ARBI_2_OFF_ADDR(x), m)
#define HWIO_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_7_BMSK                                                       0xff000000
#define HWIO_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_7_SHFT                                                             0x18
#define HWIO_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_6_BMSK                                                         0xff0000
#define HWIO_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_6_SHFT                                                             0x10
#define HWIO_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_5_BMSK                                                           0xff00
#define HWIO_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_5_SHFT                                                              0x8
#define HWIO_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_4_BMSK                                                             0xff
#define HWIO_VC_TX_ARBI_2_OFF_WRR_WEIGHT_VC_4_SHFT                                                              0x0

#define HWIO_VC0_P_RX_Q_CTRL_OFF_ADDR(x)                                                                 ((x) + 0x00000748)
#define HWIO_VC0_P_RX_Q_CTRL_OFF_RMSK                                                                    0xc0efffff
#define HWIO_VC0_P_RX_Q_CTRL_OFF_ATTR                                                                           0x3
#define HWIO_VC0_P_RX_Q_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_VC0_P_RX_Q_CTRL_OFF_ADDR(x), HWIO_VC0_P_RX_Q_CTRL_OFF_RMSK)
#define HWIO_VC0_P_RX_Q_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VC0_P_RX_Q_CTRL_OFF_ADDR(x), m)
#define HWIO_VC0_P_RX_Q_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_VC0_P_RX_Q_CTRL_OFF_ADDR(x),v)
#define HWIO_VC0_P_RX_Q_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC0_P_RX_Q_CTRL_OFF_ADDR(x),m,v,HWIO_VC0_P_RX_Q_CTRL_OFF_IN(x))
#define HWIO_VC0_P_RX_Q_CTRL_OFF_VC_ORDERING_RX_Q_BMSK                                                   0x80000000
#define HWIO_VC0_P_RX_Q_CTRL_OFF_VC_ORDERING_RX_Q_SHFT                                                         0x1f
#define HWIO_VC0_P_RX_Q_CTRL_OFF_TLP_TYPE_ORDERING_VC0_BMSK                                              0x40000000
#define HWIO_VC0_P_RX_Q_CTRL_OFF_TLP_TYPE_ORDERING_VC0_SHFT                                                    0x1e
#define HWIO_VC0_P_RX_Q_CTRL_OFF_VC0_P_TLP_Q_MODE_BMSK                                                     0xe00000
#define HWIO_VC0_P_RX_Q_CTRL_OFF_VC0_P_TLP_Q_MODE_SHFT                                                         0x15
#define HWIO_VC0_P_RX_Q_CTRL_OFF_VC0_P_HEADER_CREDIT_BMSK                                                   0xff000
#define HWIO_VC0_P_RX_Q_CTRL_OFF_VC0_P_HEADER_CREDIT_SHFT                                                       0xc
#define HWIO_VC0_P_RX_Q_CTRL_OFF_VC0_P_DATA_CREDIT_BMSK                                                       0xfff
#define HWIO_VC0_P_RX_Q_CTRL_OFF_VC0_P_DATA_CREDIT_SHFT                                                         0x0

#define HWIO_VC0_NP_RX_Q_CTRL_OFF_ADDR(x)                                                                ((x) + 0x0000074c)
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_RMSK                                                                     0xefffff
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_ATTR                                                                          0x3
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_VC0_NP_RX_Q_CTRL_OFF_ADDR(x), HWIO_VC0_NP_RX_Q_CTRL_OFF_RMSK)
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VC0_NP_RX_Q_CTRL_OFF_ADDR(x), m)
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_VC0_NP_RX_Q_CTRL_OFF_ADDR(x),v)
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC0_NP_RX_Q_CTRL_OFF_ADDR(x),m,v,HWIO_VC0_NP_RX_Q_CTRL_OFF_IN(x))
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_TLP_Q_MODE_BMSK                                                   0xe00000
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_TLP_Q_MODE_SHFT                                                       0x15
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_HEADER_CREDIT_BMSK                                                 0xff000
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_HEADER_CREDIT_SHFT                                                     0xc
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_DATA_CREDIT_BMSK                                                     0xfff
#define HWIO_VC0_NP_RX_Q_CTRL_OFF_VC0_NP_DATA_CREDIT_SHFT                                                       0x0

#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_ADDR(x)                                                               ((x) + 0x00000750)
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_RMSK                                                                    0xefffff
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_ATTR                                                                         0x3
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_VC0_CPL_RX_Q_CTRL_OFF_ADDR(x), HWIO_VC0_CPL_RX_Q_CTRL_OFF_RMSK)
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VC0_CPL_RX_Q_CTRL_OFF_ADDR(x), m)
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_VC0_CPL_RX_Q_CTRL_OFF_ADDR(x),v)
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC0_CPL_RX_Q_CTRL_OFF_ADDR(x),m,v,HWIO_VC0_CPL_RX_Q_CTRL_OFF_IN(x))
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_TLP_Q_MODE_BMSK                                                 0xe00000
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_TLP_Q_MODE_SHFT                                                     0x15
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_HEADER_CREDIT_BMSK                                               0xff000
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_HEADER_CREDIT_SHFT                                                   0xc
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_DATA_CREDIT_BMSK                                                   0xfff
#define HWIO_VC0_CPL_RX_Q_CTRL_OFF_VC0_CPL_DATA_CREDIT_SHFT                                                     0x0

#define HWIO_VC1_P_RX_Q_CTRL_OFF_ADDR(x)                                                                 ((x) + 0x00000754)
#define HWIO_VC1_P_RX_Q_CTRL_OFF_RMSK                                                                    0x40efffff
#define HWIO_VC1_P_RX_Q_CTRL_OFF_ATTR                                                                           0x3
#define HWIO_VC1_P_RX_Q_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_VC1_P_RX_Q_CTRL_OFF_ADDR(x), HWIO_VC1_P_RX_Q_CTRL_OFF_RMSK)
#define HWIO_VC1_P_RX_Q_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VC1_P_RX_Q_CTRL_OFF_ADDR(x), m)
#define HWIO_VC1_P_RX_Q_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_VC1_P_RX_Q_CTRL_OFF_ADDR(x),v)
#define HWIO_VC1_P_RX_Q_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC1_P_RX_Q_CTRL_OFF_ADDR(x),m,v,HWIO_VC1_P_RX_Q_CTRL_OFF_IN(x))
#define HWIO_VC1_P_RX_Q_CTRL_OFF_TLP_TYPE_ORDERING_VC1_BMSK                                              0x40000000
#define HWIO_VC1_P_RX_Q_CTRL_OFF_TLP_TYPE_ORDERING_VC1_SHFT                                                    0x1e
#define HWIO_VC1_P_RX_Q_CTRL_OFF_VC1_P_TLP_Q_MODE_BMSK                                                     0xe00000
#define HWIO_VC1_P_RX_Q_CTRL_OFF_VC1_P_TLP_Q_MODE_SHFT                                                         0x15
#define HWIO_VC1_P_RX_Q_CTRL_OFF_VC1_P_HEADER_CREDIT_BMSK                                                   0xff000
#define HWIO_VC1_P_RX_Q_CTRL_OFF_VC1_P_HEADER_CREDIT_SHFT                                                       0xc
#define HWIO_VC1_P_RX_Q_CTRL_OFF_VC1_P_DATA_CREDIT_BMSK                                                       0xfff
#define HWIO_VC1_P_RX_Q_CTRL_OFF_VC1_P_DATA_CREDIT_SHFT                                                         0x0

#define HWIO_VC1_NP_RX_Q_CTRL_OFF_ADDR(x)                                                                ((x) + 0x00000758)
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_RMSK                                                                     0xefffff
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_ATTR                                                                          0x3
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_VC1_NP_RX_Q_CTRL_OFF_ADDR(x), HWIO_VC1_NP_RX_Q_CTRL_OFF_RMSK)
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VC1_NP_RX_Q_CTRL_OFF_ADDR(x), m)
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_VC1_NP_RX_Q_CTRL_OFF_ADDR(x),v)
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC1_NP_RX_Q_CTRL_OFF_ADDR(x),m,v,HWIO_VC1_NP_RX_Q_CTRL_OFF_IN(x))
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_VC1_NP_TLP_Q_MODE_BMSK                                                   0xe00000
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_VC1_NP_TLP_Q_MODE_SHFT                                                       0x15
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_VC1_NP_HEADER_CREDIT_BMSK                                                 0xff000
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_VC1_NP_HEADER_CREDIT_SHFT                                                     0xc
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_VC1_NP_DATA_CREDIT_BMSK                                                     0xfff
#define HWIO_VC1_NP_RX_Q_CTRL_OFF_VC1_NP_DATA_CREDIT_SHFT                                                       0x0

#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_ADDR(x)                                                               ((x) + 0x0000075c)
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_RMSK                                                                    0xefffff
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_ATTR                                                                         0x3
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_VC1_CPL_RX_Q_CTRL_OFF_ADDR(x), HWIO_VC1_CPL_RX_Q_CTRL_OFF_RMSK)
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_VC1_CPL_RX_Q_CTRL_OFF_ADDR(x), m)
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_VC1_CPL_RX_Q_CTRL_OFF_ADDR(x),v)
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VC1_CPL_RX_Q_CTRL_OFF_ADDR(x),m,v,HWIO_VC1_CPL_RX_Q_CTRL_OFF_IN(x))
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_VC1_CPL_TLP_Q_MODE_BMSK                                                 0xe00000
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_VC1_CPL_TLP_Q_MODE_SHFT                                                     0x15
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_VC1_CPL_HEADER_CREDIT_BMSK                                               0xff000
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_VC1_CPL_HEADER_CREDIT_SHFT                                                   0xc
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_VC1_CPL_DATA_CREDIT_BMSK                                                   0xfff
#define HWIO_VC1_CPL_RX_Q_CTRL_OFF_VC1_CPL_DATA_CREDIT_SHFT                                                     0x0

#define HWIO_GEN2_CTRL_OFF_ADDR(x)                                                                       ((x) + 0x0000080c)
#define HWIO_GEN2_CTRL_OFF_RMSK                                                                          0xffffffff
#define HWIO_GEN2_CTRL_OFF_ATTR                                                                                 0x3
#define HWIO_GEN2_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_GEN2_CTRL_OFF_ADDR(x), HWIO_GEN2_CTRL_OFF_RMSK)
#define HWIO_GEN2_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_GEN2_CTRL_OFF_ADDR(x), m)
#define HWIO_GEN2_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_GEN2_CTRL_OFF_ADDR(x),v)
#define HWIO_GEN2_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GEN2_CTRL_OFF_ADDR(x),m,v,HWIO_GEN2_CTRL_OFF_IN(x))
#define HWIO_GEN2_CTRL_OFF_RSVDP_22_BMSK                                                                 0xffc00000
#define HWIO_GEN2_CTRL_OFF_RSVDP_22_SHFT                                                                       0x16
#define HWIO_GEN2_CTRL_OFF_GEN1_EI_INFERENCE_BMSK                                                          0x200000
#define HWIO_GEN2_CTRL_OFF_GEN1_EI_INFERENCE_SHFT                                                              0x15
#define HWIO_GEN2_CTRL_OFF_SEL_DEEMPHASIS_BMSK                                                             0x100000
#define HWIO_GEN2_CTRL_OFF_SEL_DEEMPHASIS_SHFT                                                                 0x14
#define HWIO_GEN2_CTRL_OFF_CONFIG_TX_COMP_RX_BMSK                                                           0x80000
#define HWIO_GEN2_CTRL_OFF_CONFIG_TX_COMP_RX_SHFT                                                              0x13
#define HWIO_GEN2_CTRL_OFF_CONFIG_PHY_TX_CHANGE_BMSK                                                        0x40000
#define HWIO_GEN2_CTRL_OFF_CONFIG_PHY_TX_CHANGE_SHFT                                                           0x12
#define HWIO_GEN2_CTRL_OFF_DIRECT_SPEED_CHANGE_BMSK                                                         0x20000
#define HWIO_GEN2_CTRL_OFF_DIRECT_SPEED_CHANGE_SHFT                                                            0x11
#define HWIO_GEN2_CTRL_OFF_AUTO_LANE_FLIP_CTRL_EN_BMSK                                                      0x10000
#define HWIO_GEN2_CTRL_OFF_AUTO_LANE_FLIP_CTRL_EN_SHFT                                                         0x10
#define HWIO_GEN2_CTRL_OFF_PRE_DET_LANE_BMSK                                                                 0xe000
#define HWIO_GEN2_CTRL_OFF_PRE_DET_LANE_SHFT                                                                    0xd
#define HWIO_GEN2_CTRL_OFF_NUM_OF_LANES_BMSK                                                                 0x1f00
#define HWIO_GEN2_CTRL_OFF_NUM_OF_LANES_SHFT                                                                    0x8
#define HWIO_GEN2_CTRL_OFF_FAST_TRAINING_SEQ_BMSK                                                              0xff
#define HWIO_GEN2_CTRL_OFF_FAST_TRAINING_SEQ_SHFT                                                               0x0

#define HWIO_PHY_STATUS_OFF_ADDR(x)                                                                      ((x) + 0x00000810)
#define HWIO_PHY_STATUS_OFF_RMSK                                                                         0xffffffff
#define HWIO_PHY_STATUS_OFF_ATTR                                                                                0x1
#define HWIO_PHY_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_PHY_STATUS_OFF_ADDR(x), HWIO_PHY_STATUS_OFF_RMSK)
#define HWIO_PHY_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PHY_STATUS_OFF_ADDR(x), m)
#define HWIO_PHY_STATUS_OFF_PHY_STATUS_BMSK                                                              0xffffffff
#define HWIO_PHY_STATUS_OFF_PHY_STATUS_SHFT                                                                     0x0

#define HWIO_PHY_CONTROL_OFF_ADDR(x)                                                                     ((x) + 0x00000814)
#define HWIO_PHY_CONTROL_OFF_RMSK                                                                        0xffffffff
#define HWIO_PHY_CONTROL_OFF_ATTR                                                                               0x3
#define HWIO_PHY_CONTROL_OFF_IN(x)      \
        in_dword_masked(HWIO_PHY_CONTROL_OFF_ADDR(x), HWIO_PHY_CONTROL_OFF_RMSK)
#define HWIO_PHY_CONTROL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PHY_CONTROL_OFF_ADDR(x), m)
#define HWIO_PHY_CONTROL_OFF_OUT(x, v)      \
        out_dword(HWIO_PHY_CONTROL_OFF_ADDR(x),v)
#define HWIO_PHY_CONTROL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PHY_CONTROL_OFF_ADDR(x),m,v,HWIO_PHY_CONTROL_OFF_IN(x))
#define HWIO_PHY_CONTROL_OFF_PHY_CONTROL_BMSK                                                            0xffffffff
#define HWIO_PHY_CONTROL_OFF_PHY_CONTROL_SHFT                                                                   0x0

#define HWIO_MSI_CTRL_ADDR_OFF_ADDR(x)                                                                   ((x) + 0x00000820)
#define HWIO_MSI_CTRL_ADDR_OFF_RMSK                                                                      0xffffffff
#define HWIO_MSI_CTRL_ADDR_OFF_ATTR                                                                             0x3
#define HWIO_MSI_CTRL_ADDR_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_ADDR_OFF_ADDR(x), HWIO_MSI_CTRL_ADDR_OFF_RMSK)
#define HWIO_MSI_CTRL_ADDR_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_ADDR_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_ADDR_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_ADDR_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_ADDR_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_ADDR_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_ADDR_OFF_IN(x))
#define HWIO_MSI_CTRL_ADDR_OFF_MSI_CTRL_ADDR_BMSK                                                        0xffffffff
#define HWIO_MSI_CTRL_ADDR_OFF_MSI_CTRL_ADDR_SHFT                                                               0x0

#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_ADDR(x)                                                             ((x) + 0x00000824)
#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_UPPER_ADDR_OFF_ADDR(x), HWIO_MSI_CTRL_UPPER_ADDR_OFF_RMSK)
#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_UPPER_ADDR_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_UPPER_ADDR_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_UPPER_ADDR_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_UPPER_ADDR_OFF_IN(x))
#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_MSI_CTRL_UPPER_ADDR_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_UPPER_ADDR_OFF_MSI_CTRL_UPPER_ADDR_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_0_EN_OFF_ADDR(x)                                                               ((x) + 0x00000828)
#define HWIO_MSI_CTRL_INT_0_EN_OFF_RMSK                                                                  0xffffffff
#define HWIO_MSI_CTRL_INT_0_EN_OFF_ATTR                                                                         0x3
#define HWIO_MSI_CTRL_INT_0_EN_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_0_EN_OFF_ADDR(x), HWIO_MSI_CTRL_INT_0_EN_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_0_EN_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_0_EN_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_0_EN_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_0_EN_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_0_EN_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_0_EN_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_0_EN_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_0_EN_OFF_MSI_CTRL_INT_0_EN_BMSK                                                0xffffffff
#define HWIO_MSI_CTRL_INT_0_EN_OFF_MSI_CTRL_INT_0_EN_SHFT                                                       0x0

#define HWIO_MSI_CTRL_INT_0_MASK_OFF_ADDR(x)                                                             ((x) + 0x0000082c)
#define HWIO_MSI_CTRL_INT_0_MASK_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_INT_0_MASK_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_INT_0_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_0_MASK_OFF_ADDR(x), HWIO_MSI_CTRL_INT_0_MASK_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_0_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_0_MASK_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_0_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_0_MASK_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_0_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_0_MASK_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_0_MASK_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_0_MASK_OFF_MSI_CTRL_INT_0_MASK_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_INT_0_MASK_OFF_MSI_CTRL_INT_0_MASK_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_ADDR(x)                                                           ((x) + 0x00000830)
#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_ATTR                                                                     0x3
#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_0_STATUS_OFF_ADDR(x), HWIO_MSI_CTRL_INT_0_STATUS_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_0_STATUS_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_0_STATUS_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_0_STATUS_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_0_STATUS_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_MSI_CTRL_INT_0_STATUS_BMSK                                        0xffffffff
#define HWIO_MSI_CTRL_INT_0_STATUS_OFF_MSI_CTRL_INT_0_STATUS_SHFT                                               0x0

#define HWIO_MSI_CTRL_INT_1_EN_OFF_ADDR(x)                                                               ((x) + 0x00000834)
#define HWIO_MSI_CTRL_INT_1_EN_OFF_RMSK                                                                  0xffffffff
#define HWIO_MSI_CTRL_INT_1_EN_OFF_ATTR                                                                         0x3
#define HWIO_MSI_CTRL_INT_1_EN_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_1_EN_OFF_ADDR(x), HWIO_MSI_CTRL_INT_1_EN_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_1_EN_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_1_EN_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_1_EN_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_1_EN_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_1_EN_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_1_EN_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_1_EN_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_1_EN_OFF_MSI_CTRL_INT_1_EN_BMSK                                                0xffffffff
#define HWIO_MSI_CTRL_INT_1_EN_OFF_MSI_CTRL_INT_1_EN_SHFT                                                       0x0

#define HWIO_MSI_CTRL_INT_1_MASK_OFF_ADDR(x)                                                             ((x) + 0x00000838)
#define HWIO_MSI_CTRL_INT_1_MASK_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_INT_1_MASK_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_INT_1_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_1_MASK_OFF_ADDR(x), HWIO_MSI_CTRL_INT_1_MASK_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_1_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_1_MASK_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_1_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_1_MASK_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_1_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_1_MASK_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_1_MASK_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_1_MASK_OFF_MSI_CTRL_INT_1_MASK_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_INT_1_MASK_OFF_MSI_CTRL_INT_1_MASK_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_ADDR(x)                                                           ((x) + 0x0000083c)
#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_ATTR                                                                     0x3
#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_1_STATUS_OFF_ADDR(x), HWIO_MSI_CTRL_INT_1_STATUS_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_1_STATUS_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_1_STATUS_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_1_STATUS_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_1_STATUS_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_MSI_CTRL_INT_1_STATUS_BMSK                                        0xffffffff
#define HWIO_MSI_CTRL_INT_1_STATUS_OFF_MSI_CTRL_INT_1_STATUS_SHFT                                               0x0

#define HWIO_MSI_CTRL_INT_2_EN_OFF_ADDR(x)                                                               ((x) + 0x00000840)
#define HWIO_MSI_CTRL_INT_2_EN_OFF_RMSK                                                                  0xffffffff
#define HWIO_MSI_CTRL_INT_2_EN_OFF_ATTR                                                                         0x3
#define HWIO_MSI_CTRL_INT_2_EN_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_2_EN_OFF_ADDR(x), HWIO_MSI_CTRL_INT_2_EN_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_2_EN_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_2_EN_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_2_EN_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_2_EN_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_2_EN_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_2_EN_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_2_EN_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_2_EN_OFF_MSI_CTRL_INT_2_EN_BMSK                                                0xffffffff
#define HWIO_MSI_CTRL_INT_2_EN_OFF_MSI_CTRL_INT_2_EN_SHFT                                                       0x0

#define HWIO_MSI_CTRL_INT_2_MASK_OFF_ADDR(x)                                                             ((x) + 0x00000844)
#define HWIO_MSI_CTRL_INT_2_MASK_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_INT_2_MASK_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_INT_2_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_2_MASK_OFF_ADDR(x), HWIO_MSI_CTRL_INT_2_MASK_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_2_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_2_MASK_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_2_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_2_MASK_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_2_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_2_MASK_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_2_MASK_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_2_MASK_OFF_MSI_CTRL_INT_2_MASK_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_INT_2_MASK_OFF_MSI_CTRL_INT_2_MASK_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_ADDR(x)                                                           ((x) + 0x00000848)
#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_ATTR                                                                     0x3
#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_2_STATUS_OFF_ADDR(x), HWIO_MSI_CTRL_INT_2_STATUS_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_2_STATUS_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_2_STATUS_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_2_STATUS_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_2_STATUS_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_MSI_CTRL_INT_2_STATUS_BMSK                                        0xffffffff
#define HWIO_MSI_CTRL_INT_2_STATUS_OFF_MSI_CTRL_INT_2_STATUS_SHFT                                               0x0

#define HWIO_MSI_CTRL_INT_3_EN_OFF_ADDR(x)                                                               ((x) + 0x0000084c)
#define HWIO_MSI_CTRL_INT_3_EN_OFF_RMSK                                                                  0xffffffff
#define HWIO_MSI_CTRL_INT_3_EN_OFF_ATTR                                                                         0x3
#define HWIO_MSI_CTRL_INT_3_EN_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_3_EN_OFF_ADDR(x), HWIO_MSI_CTRL_INT_3_EN_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_3_EN_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_3_EN_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_3_EN_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_3_EN_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_3_EN_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_3_EN_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_3_EN_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_3_EN_OFF_MSI_CTRL_INT_3_EN_BMSK                                                0xffffffff
#define HWIO_MSI_CTRL_INT_3_EN_OFF_MSI_CTRL_INT_3_EN_SHFT                                                       0x0

#define HWIO_MSI_CTRL_INT_3_MASK_OFF_ADDR(x)                                                             ((x) + 0x00000850)
#define HWIO_MSI_CTRL_INT_3_MASK_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_INT_3_MASK_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_INT_3_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_3_MASK_OFF_ADDR(x), HWIO_MSI_CTRL_INT_3_MASK_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_3_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_3_MASK_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_3_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_3_MASK_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_3_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_3_MASK_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_3_MASK_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_3_MASK_OFF_MSI_CTRL_INT_3_MASK_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_INT_3_MASK_OFF_MSI_CTRL_INT_3_MASK_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_ADDR(x)                                                           ((x) + 0x00000854)
#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_ATTR                                                                     0x3
#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_3_STATUS_OFF_ADDR(x), HWIO_MSI_CTRL_INT_3_STATUS_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_3_STATUS_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_3_STATUS_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_3_STATUS_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_3_STATUS_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_MSI_CTRL_INT_3_STATUS_BMSK                                        0xffffffff
#define HWIO_MSI_CTRL_INT_3_STATUS_OFF_MSI_CTRL_INT_3_STATUS_SHFT                                               0x0

#define HWIO_MSI_CTRL_INT_4_EN_OFF_ADDR(x)                                                               ((x) + 0x00000858)
#define HWIO_MSI_CTRL_INT_4_EN_OFF_RMSK                                                                  0xffffffff
#define HWIO_MSI_CTRL_INT_4_EN_OFF_ATTR                                                                         0x3
#define HWIO_MSI_CTRL_INT_4_EN_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_4_EN_OFF_ADDR(x), HWIO_MSI_CTRL_INT_4_EN_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_4_EN_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_4_EN_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_4_EN_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_4_EN_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_4_EN_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_4_EN_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_4_EN_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_4_EN_OFF_MSI_CTRL_INT_4_EN_BMSK                                                0xffffffff
#define HWIO_MSI_CTRL_INT_4_EN_OFF_MSI_CTRL_INT_4_EN_SHFT                                                       0x0

#define HWIO_MSI_CTRL_INT_4_MASK_OFF_ADDR(x)                                                             ((x) + 0x0000085c)
#define HWIO_MSI_CTRL_INT_4_MASK_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_INT_4_MASK_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_INT_4_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_4_MASK_OFF_ADDR(x), HWIO_MSI_CTRL_INT_4_MASK_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_4_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_4_MASK_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_4_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_4_MASK_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_4_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_4_MASK_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_4_MASK_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_4_MASK_OFF_MSI_CTRL_INT_4_MASK_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_INT_4_MASK_OFF_MSI_CTRL_INT_4_MASK_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_ADDR(x)                                                           ((x) + 0x00000860)
#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_ATTR                                                                     0x3
#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_4_STATUS_OFF_ADDR(x), HWIO_MSI_CTRL_INT_4_STATUS_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_4_STATUS_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_4_STATUS_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_4_STATUS_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_4_STATUS_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_MSI_CTRL_INT_4_STATUS_BMSK                                        0xffffffff
#define HWIO_MSI_CTRL_INT_4_STATUS_OFF_MSI_CTRL_INT_4_STATUS_SHFT                                               0x0

#define HWIO_MSI_CTRL_INT_5_EN_OFF_ADDR(x)                                                               ((x) + 0x00000864)
#define HWIO_MSI_CTRL_INT_5_EN_OFF_RMSK                                                                  0xffffffff
#define HWIO_MSI_CTRL_INT_5_EN_OFF_ATTR                                                                         0x3
#define HWIO_MSI_CTRL_INT_5_EN_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_5_EN_OFF_ADDR(x), HWIO_MSI_CTRL_INT_5_EN_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_5_EN_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_5_EN_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_5_EN_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_5_EN_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_5_EN_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_5_EN_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_5_EN_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_5_EN_OFF_MSI_CTRL_INT_5_EN_BMSK                                                0xffffffff
#define HWIO_MSI_CTRL_INT_5_EN_OFF_MSI_CTRL_INT_5_EN_SHFT                                                       0x0

#define HWIO_MSI_CTRL_INT_5_MASK_OFF_ADDR(x)                                                             ((x) + 0x00000868)
#define HWIO_MSI_CTRL_INT_5_MASK_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_INT_5_MASK_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_INT_5_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_5_MASK_OFF_ADDR(x), HWIO_MSI_CTRL_INT_5_MASK_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_5_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_5_MASK_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_5_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_5_MASK_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_5_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_5_MASK_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_5_MASK_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_5_MASK_OFF_MSI_CTRL_INT_5_MASK_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_INT_5_MASK_OFF_MSI_CTRL_INT_5_MASK_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_ADDR(x)                                                           ((x) + 0x0000086c)
#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_ATTR                                                                     0x3
#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_5_STATUS_OFF_ADDR(x), HWIO_MSI_CTRL_INT_5_STATUS_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_5_STATUS_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_5_STATUS_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_5_STATUS_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_5_STATUS_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_MSI_CTRL_INT_5_STATUS_BMSK                                        0xffffffff
#define HWIO_MSI_CTRL_INT_5_STATUS_OFF_MSI_CTRL_INT_5_STATUS_SHFT                                               0x0

#define HWIO_MSI_CTRL_INT_6_EN_OFF_ADDR(x)                                                               ((x) + 0x00000870)
#define HWIO_MSI_CTRL_INT_6_EN_OFF_RMSK                                                                  0xffffffff
#define HWIO_MSI_CTRL_INT_6_EN_OFF_ATTR                                                                         0x3
#define HWIO_MSI_CTRL_INT_6_EN_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_6_EN_OFF_ADDR(x), HWIO_MSI_CTRL_INT_6_EN_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_6_EN_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_6_EN_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_6_EN_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_6_EN_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_6_EN_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_6_EN_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_6_EN_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_6_EN_OFF_MSI_CTRL_INT_6_EN_BMSK                                                0xffffffff
#define HWIO_MSI_CTRL_INT_6_EN_OFF_MSI_CTRL_INT_6_EN_SHFT                                                       0x0

#define HWIO_MSI_CTRL_INT_6_MASK_OFF_ADDR(x)                                                             ((x) + 0x00000874)
#define HWIO_MSI_CTRL_INT_6_MASK_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_INT_6_MASK_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_INT_6_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_6_MASK_OFF_ADDR(x), HWIO_MSI_CTRL_INT_6_MASK_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_6_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_6_MASK_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_6_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_6_MASK_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_6_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_6_MASK_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_6_MASK_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_6_MASK_OFF_MSI_CTRL_INT_6_MASK_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_INT_6_MASK_OFF_MSI_CTRL_INT_6_MASK_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_ADDR(x)                                                           ((x) + 0x00000878)
#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_ATTR                                                                     0x3
#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_6_STATUS_OFF_ADDR(x), HWIO_MSI_CTRL_INT_6_STATUS_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_6_STATUS_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_6_STATUS_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_6_STATUS_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_6_STATUS_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_MSI_CTRL_INT_6_STATUS_BMSK                                        0xffffffff
#define HWIO_MSI_CTRL_INT_6_STATUS_OFF_MSI_CTRL_INT_6_STATUS_SHFT                                               0x0

#define HWIO_MSI_CTRL_INT_7_EN_OFF_ADDR(x)                                                               ((x) + 0x0000087c)
#define HWIO_MSI_CTRL_INT_7_EN_OFF_RMSK                                                                  0xffffffff
#define HWIO_MSI_CTRL_INT_7_EN_OFF_ATTR                                                                         0x3
#define HWIO_MSI_CTRL_INT_7_EN_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_7_EN_OFF_ADDR(x), HWIO_MSI_CTRL_INT_7_EN_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_7_EN_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_7_EN_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_7_EN_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_7_EN_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_7_EN_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_7_EN_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_7_EN_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_7_EN_OFF_MSI_CTRL_INT_7_EN_BMSK                                                0xffffffff
#define HWIO_MSI_CTRL_INT_7_EN_OFF_MSI_CTRL_INT_7_EN_SHFT                                                       0x0

#define HWIO_MSI_CTRL_INT_7_MASK_OFF_ADDR(x)                                                             ((x) + 0x00000880)
#define HWIO_MSI_CTRL_INT_7_MASK_OFF_RMSK                                                                0xffffffff
#define HWIO_MSI_CTRL_INT_7_MASK_OFF_ATTR                                                                       0x3
#define HWIO_MSI_CTRL_INT_7_MASK_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_7_MASK_OFF_ADDR(x), HWIO_MSI_CTRL_INT_7_MASK_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_7_MASK_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_7_MASK_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_7_MASK_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_7_MASK_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_7_MASK_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_7_MASK_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_7_MASK_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_7_MASK_OFF_MSI_CTRL_INT_7_MASK_BMSK                                            0xffffffff
#define HWIO_MSI_CTRL_INT_7_MASK_OFF_MSI_CTRL_INT_7_MASK_SHFT                                                   0x0

#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_ADDR(x)                                                           ((x) + 0x00000884)
#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_RMSK                                                              0xffffffff
#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_ATTR                                                                     0x3
#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_7_STATUS_OFF_ADDR(x), HWIO_MSI_CTRL_INT_7_STATUS_OFF_RMSK)
#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_CTRL_INT_7_STATUS_OFF_ADDR(x), m)
#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_CTRL_INT_7_STATUS_OFF_ADDR(x),v)
#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_CTRL_INT_7_STATUS_OFF_ADDR(x),m,v,HWIO_MSI_CTRL_INT_7_STATUS_OFF_IN(x))
#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_MSI_CTRL_INT_7_STATUS_BMSK                                        0xffffffff
#define HWIO_MSI_CTRL_INT_7_STATUS_OFF_MSI_CTRL_INT_7_STATUS_SHFT                                               0x0

#define HWIO_MSI_GPIO_IO_OFF_ADDR(x)                                                                     ((x) + 0x00000888)
#define HWIO_MSI_GPIO_IO_OFF_RMSK                                                                        0xffffffff
#define HWIO_MSI_GPIO_IO_OFF_ATTR                                                                               0x3
#define HWIO_MSI_GPIO_IO_OFF_IN(x)      \
        in_dword_masked(HWIO_MSI_GPIO_IO_OFF_ADDR(x), HWIO_MSI_GPIO_IO_OFF_RMSK)
#define HWIO_MSI_GPIO_IO_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MSI_GPIO_IO_OFF_ADDR(x), m)
#define HWIO_MSI_GPIO_IO_OFF_OUT(x, v)      \
        out_dword(HWIO_MSI_GPIO_IO_OFF_ADDR(x),v)
#define HWIO_MSI_GPIO_IO_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MSI_GPIO_IO_OFF_ADDR(x),m,v,HWIO_MSI_GPIO_IO_OFF_IN(x))
#define HWIO_MSI_GPIO_IO_OFF_MSI_GPIO_REG_BMSK                                                           0xffffffff
#define HWIO_MSI_GPIO_IO_OFF_MSI_GPIO_REG_SHFT                                                                  0x0

#define HWIO_GEN3_RELATED_OFF_ADDR(x)                                                                    ((x) + 0x00000890)
#define HWIO_GEN3_RELATED_OFF_RMSK                                                                       0xfc9fffff
#define HWIO_GEN3_RELATED_OFF_ATTR                                                                              0x3
#define HWIO_GEN3_RELATED_OFF_IN(x)      \
        in_dword_masked(HWIO_GEN3_RELATED_OFF_ADDR(x), HWIO_GEN3_RELATED_OFF_RMSK)
#define HWIO_GEN3_RELATED_OFF_INM(x, m)      \
        in_dword_masked(HWIO_GEN3_RELATED_OFF_ADDR(x), m)
#define HWIO_GEN3_RELATED_OFF_OUT(x, v)      \
        out_dword(HWIO_GEN3_RELATED_OFF_ADDR(x),v)
#define HWIO_GEN3_RELATED_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GEN3_RELATED_OFF_ADDR(x),m,v,HWIO_GEN3_RELATED_OFF_IN(x))
#define HWIO_GEN3_RELATED_OFF_RSVDP_26_BMSK                                                              0xfc000000
#define HWIO_GEN3_RELATED_OFF_RSVDP_26_SHFT                                                                    0x1a
#define HWIO_GEN3_RELATED_OFF_GEN3_EQ_INVREQ_EVAL_DIFF_DISABLE_BMSK                                        0x800000
#define HWIO_GEN3_RELATED_OFF_GEN3_EQ_INVREQ_EVAL_DIFF_DISABLE_SHFT                                            0x17
#define HWIO_GEN3_RELATED_OFF_RSVDP_19_BMSK                                                                0x180000
#define HWIO_GEN3_RELATED_OFF_RSVDP_19_SHFT                                                                    0x13
#define HWIO_GEN3_RELATED_OFF_GEN3_DC_BALANCE_DISABLE_BMSK                                                  0x40000
#define HWIO_GEN3_RELATED_OFF_GEN3_DC_BALANCE_DISABLE_SHFT                                                     0x12
#define HWIO_GEN3_RELATED_OFF_GEN3_DLLP_XMT_DELAY_DISABLE_BMSK                                              0x20000
#define HWIO_GEN3_RELATED_OFF_GEN3_DLLP_XMT_DELAY_DISABLE_SHFT                                                 0x11
#define HWIO_GEN3_RELATED_OFF_GEN3_EQUALIZATION_DISABLE_BMSK                                                0x10000
#define HWIO_GEN3_RELATED_OFF_GEN3_EQUALIZATION_DISABLE_SHFT                                                   0x10
#define HWIO_GEN3_RELATED_OFF_RSVDP_13_BMSK                                                                  0xe000
#define HWIO_GEN3_RELATED_OFF_RSVDP_13_SHFT                                                                     0xd
#define HWIO_GEN3_RELATED_OFF_RXEQ_PH01_EN_BMSK                                                              0x1000
#define HWIO_GEN3_RELATED_OFF_RXEQ_PH01_EN_SHFT                                                                 0xc
#define HWIO_GEN3_RELATED_OFF_EQ_REDO_BMSK                                                                    0x800
#define HWIO_GEN3_RELATED_OFF_EQ_REDO_SHFT                                                                      0xb
#define HWIO_GEN3_RELATED_OFF_EQ_EIEOS_CNT_BMSK                                                               0x400
#define HWIO_GEN3_RELATED_OFF_EQ_EIEOS_CNT_SHFT                                                                 0xa
#define HWIO_GEN3_RELATED_OFF_EQ_PHASE_2_3_BMSK                                                               0x200
#define HWIO_GEN3_RELATED_OFF_EQ_PHASE_2_3_SHFT                                                                 0x9
#define HWIO_GEN3_RELATED_OFF_DISABLE_SCRAMBLER_GEN_3_BMSK                                                    0x100
#define HWIO_GEN3_RELATED_OFF_DISABLE_SCRAMBLER_GEN_3_SHFT                                                      0x8
#define HWIO_GEN3_RELATED_OFF_RSVDP_1_BMSK                                                                     0xfe
#define HWIO_GEN3_RELATED_OFF_RSVDP_1_SHFT                                                                      0x1
#define HWIO_GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL_BMSK                                                          0x1
#define HWIO_GEN3_RELATED_OFF_GEN3_ZRXDC_NONCOMPL_SHFT                                                          0x0

#define HWIO_GEN3_EQ_CONTROL_OFF_ADDR(x)                                                                 ((x) + 0x000008a8)
#define HWIO_GEN3_EQ_CONTROL_OFF_RMSK                                                                    0xffffffff
#define HWIO_GEN3_EQ_CONTROL_OFF_ATTR                                                                           0x3
#define HWIO_GEN3_EQ_CONTROL_OFF_IN(x)      \
        in_dword_masked(HWIO_GEN3_EQ_CONTROL_OFF_ADDR(x), HWIO_GEN3_EQ_CONTROL_OFF_RMSK)
#define HWIO_GEN3_EQ_CONTROL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_GEN3_EQ_CONTROL_OFF_ADDR(x), m)
#define HWIO_GEN3_EQ_CONTROL_OFF_OUT(x, v)      \
        out_dword(HWIO_GEN3_EQ_CONTROL_OFF_ADDR(x),v)
#define HWIO_GEN3_EQ_CONTROL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GEN3_EQ_CONTROL_OFF_ADDR(x),m,v,HWIO_GEN3_EQ_CONTROL_OFF_IN(x))
#define HWIO_GEN3_EQ_CONTROL_OFF_RSVDP_27_BMSK                                                           0xf8000000
#define HWIO_GEN3_EQ_CONTROL_OFF_RSVDP_27_SHFT                                                                 0x1b
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_REQ_SEND_CONSEC_EIEOS_FOR_PSET_MAP_BMSK                             0x4000000
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_REQ_SEND_CONSEC_EIEOS_FOR_PSET_MAP_SHFT                                  0x1a
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_AS_COEF_BMSK                                            0x2000000
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_AS_COEF_SHFT                                                 0x19
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FOM_INC_INITIAL_EVAL_BMSK                                        0x1000000
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FOM_INC_INITIAL_EVAL_SHFT                                             0x18
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_VEC_BMSK                                                 0xffff00
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PSET_REQ_VEC_SHFT                                                      0x8
#define HWIO_GEN3_EQ_CONTROL_OFF_RSVDP_6_BMSK                                                                  0xc0
#define HWIO_GEN3_EQ_CONTROL_OFF_RSVDP_6_SHFT                                                                   0x6
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_EVAL_2MS_DISABLE_BMSK                                                 0x20
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_EVAL_2MS_DISABLE_SHFT                                                  0x5
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PHASE23_EXIT_MODE_BMSK                                                0x10
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_PHASE23_EXIT_MODE_SHFT                                                 0x4
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FB_MODE_BMSK                                                           0xf
#define HWIO_GEN3_EQ_CONTROL_OFF_GEN3_EQ_FB_MODE_SHFT                                                           0x0

#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_ADDR(x)                                                      ((x) + 0x000008ac)
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_RMSK                                                         0xffffffff
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_ATTR                                                                0x3
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_IN(x)      \
        in_dword_masked(HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_ADDR(x), HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_RMSK)
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_INM(x, m)      \
        in_dword_masked(HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_ADDR(x), m)
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_OUT(x, v)      \
        out_dword(HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_ADDR(x),v)
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_ADDR(x),m,v,HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_IN(x))
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_RSVDP_18_BMSK                                                0xfffc0000
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_RSVDP_18_SHFT                                                      0x12
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA_BMSK                         0x3c000
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_POST_CUSROR_DELTA_SHFT                             0xe
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA_BMSK                           0x3c00
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_MAX_PRE_CUSROR_DELTA_SHFT                              0xa
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_N_EVALS_BMSK                                         0x3e0
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_N_EVALS_SHFT                                           0x5
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_T_MIN_PHASE23_BMSK                                    0x1f
#define HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_GEN3_EQ_FMDC_T_MIN_PHASE23_SHFT                                     0x0

#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_ADDR(x)                                                           ((x) + 0x000008b8)
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RMSK                                                              0xffffffff
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_ATTR                                                                     0x3
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_IN(x)      \
        in_dword_masked(HWIO_PIPE_LOOPBACK_CONTROL_OFF_ADDR(x), HWIO_PIPE_LOOPBACK_CONTROL_OFF_RMSK)
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PIPE_LOOPBACK_CONTROL_OFF_ADDR(x), m)
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_OUT(x, v)      \
        out_dword(HWIO_PIPE_LOOPBACK_CONTROL_OFF_ADDR(x),v)
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PIPE_LOOPBACK_CONTROL_OFF_ADDR(x),m,v,HWIO_PIPE_LOOPBACK_CONTROL_OFF_IN(x))
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_PIPE_LOOPBACK_BMSK                                                0x80000000
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_PIPE_LOOPBACK_SHFT                                                      0x1f
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RSVDP_27_BMSK                                                     0x78000000
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RSVDP_27_SHFT                                                           0x1b
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_VALUE_BMSK                                                0x7000000
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_VALUE_SHFT                                                     0x18
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RSVDP_22_BMSK                                                       0xc00000
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RSVDP_22_SHFT                                                           0x16
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_LANE_BMSK                                                  0x3f0000
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_RXSTATUS_LANE_SHFT                                                      0x10
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_LPBK_RXVALID_BMSK                                                     0xffff
#define HWIO_PIPE_LOOPBACK_CONTROL_OFF_LPBK_RXVALID_SHFT                                                        0x0

#define HWIO_MISC_CONTROL_1_OFF_ADDR(x)                                                                  ((x) + 0x000008bc)
#define HWIO_MISC_CONTROL_1_OFF_RMSK                                                                     0xffffffff
#define HWIO_MISC_CONTROL_1_OFF_ATTR                                                                            0x3
#define HWIO_MISC_CONTROL_1_OFF_IN(x)      \
        in_dword_masked(HWIO_MISC_CONTROL_1_OFF_ADDR(x), HWIO_MISC_CONTROL_1_OFF_RMSK)
#define HWIO_MISC_CONTROL_1_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MISC_CONTROL_1_OFF_ADDR(x), m)
#define HWIO_MISC_CONTROL_1_OFF_OUT(x, v)      \
        out_dword(HWIO_MISC_CONTROL_1_OFF_ADDR(x),v)
#define HWIO_MISC_CONTROL_1_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MISC_CONTROL_1_OFF_ADDR(x),m,v,HWIO_MISC_CONTROL_1_OFF_IN(x))
#define HWIO_MISC_CONTROL_1_OFF_RSVDP_1_BMSK                                                             0xfffffffe
#define HWIO_MISC_CONTROL_1_OFF_RSVDP_1_SHFT                                                                    0x1
#define HWIO_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_BMSK                                                               0x1
#define HWIO_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_SHFT                                                               0x0

#define HWIO_MULTI_LANE_CONTROL_OFF_ADDR(x)                                                              ((x) + 0x000008c0)
#define HWIO_MULTI_LANE_CONTROL_OFF_RMSK                                                                 0xffffffff
#define HWIO_MULTI_LANE_CONTROL_OFF_ATTR                                                                        0x3
#define HWIO_MULTI_LANE_CONTROL_OFF_IN(x)      \
        in_dword_masked(HWIO_MULTI_LANE_CONTROL_OFF_ADDR(x), HWIO_MULTI_LANE_CONTROL_OFF_RMSK)
#define HWIO_MULTI_LANE_CONTROL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_MULTI_LANE_CONTROL_OFF_ADDR(x), m)
#define HWIO_MULTI_LANE_CONTROL_OFF_OUT(x, v)      \
        out_dword(HWIO_MULTI_LANE_CONTROL_OFF_ADDR(x),v)
#define HWIO_MULTI_LANE_CONTROL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_MULTI_LANE_CONTROL_OFF_ADDR(x),m,v,HWIO_MULTI_LANE_CONTROL_OFF_IN(x))
#define HWIO_MULTI_LANE_CONTROL_OFF_RSVDP_8_BMSK                                                         0xffffff00
#define HWIO_MULTI_LANE_CONTROL_OFF_RSVDP_8_SHFT                                                                0x8
#define HWIO_MULTI_LANE_CONTROL_OFF_UPCONFIGURE_SUPPORT_BMSK                                                   0x80
#define HWIO_MULTI_LANE_CONTROL_OFF_UPCONFIGURE_SUPPORT_SHFT                                                    0x7
#define HWIO_MULTI_LANE_CONTROL_OFF_DIRECT_LINK_WIDTH_CHANGE_BMSK                                              0x40
#define HWIO_MULTI_LANE_CONTROL_OFF_DIRECT_LINK_WIDTH_CHANGE_SHFT                                               0x6
#define HWIO_MULTI_LANE_CONTROL_OFF_TARGET_LINK_WIDTH_BMSK                                                     0x3f
#define HWIO_MULTI_LANE_CONTROL_OFF_TARGET_LINK_WIDTH_SHFT                                                      0x0

#define HWIO_PHY_INTEROP_CTRL_OFF_ADDR(x)                                                                ((x) + 0x000008c4)
#define HWIO_PHY_INTEROP_CTRL_OFF_RMSK                                                                   0xffffffff
#define HWIO_PHY_INTEROP_CTRL_OFF_ATTR                                                                          0x3
#define HWIO_PHY_INTEROP_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_PHY_INTEROP_CTRL_OFF_ADDR(x), HWIO_PHY_INTEROP_CTRL_OFF_RMSK)
#define HWIO_PHY_INTEROP_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PHY_INTEROP_CTRL_OFF_ADDR(x), m)
#define HWIO_PHY_INTEROP_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_PHY_INTEROP_CTRL_OFF_ADDR(x),v)
#define HWIO_PHY_INTEROP_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PHY_INTEROP_CTRL_OFF_ADDR(x),m,v,HWIO_PHY_INTEROP_CTRL_OFF_IN(x))
#define HWIO_PHY_INTEROP_CTRL_OFF_RSVDP_10_BMSK                                                          0xfffffc00
#define HWIO_PHY_INTEROP_CTRL_OFF_RSVDP_10_SHFT                                                                 0xa
#define HWIO_PHY_INTEROP_CTRL_OFF_L1_NOWAIT_P1_BMSK                                                           0x200
#define HWIO_PHY_INTEROP_CTRL_OFF_L1_NOWAIT_P1_SHFT                                                             0x9
#define HWIO_PHY_INTEROP_CTRL_OFF_L1SUB_EXIT_MODE_BMSK                                                        0x100
#define HWIO_PHY_INTEROP_CTRL_OFF_L1SUB_EXIT_MODE_SHFT                                                          0x8
#define HWIO_PHY_INTEROP_CTRL_OFF_RSVDP_7_BMSK                                                                 0x80
#define HWIO_PHY_INTEROP_CTRL_OFF_RSVDP_7_SHFT                                                                  0x7
#define HWIO_PHY_INTEROP_CTRL_OFF_RXSTANDBY_CONTROL_BMSK                                                       0x7f
#define HWIO_PHY_INTEROP_CTRL_OFF_RXSTANDBY_CONTROL_SHFT                                                        0x0

#define HWIO_LINK_FLUSH_CONTROL_OFF_ADDR(x)                                                              ((x) + 0x000008cc)
#define HWIO_LINK_FLUSH_CONTROL_OFF_RMSK                                                                 0xffffffff
#define HWIO_LINK_FLUSH_CONTROL_OFF_ATTR                                                                        0x3
#define HWIO_LINK_FLUSH_CONTROL_OFF_IN(x)      \
        in_dword_masked(HWIO_LINK_FLUSH_CONTROL_OFF_ADDR(x), HWIO_LINK_FLUSH_CONTROL_OFF_RMSK)
#define HWIO_LINK_FLUSH_CONTROL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_LINK_FLUSH_CONTROL_OFF_ADDR(x), m)
#define HWIO_LINK_FLUSH_CONTROL_OFF_OUT(x, v)      \
        out_dword(HWIO_LINK_FLUSH_CONTROL_OFF_ADDR(x),v)
#define HWIO_LINK_FLUSH_CONTROL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_LINK_FLUSH_CONTROL_OFF_ADDR(x),m,v,HWIO_LINK_FLUSH_CONTROL_OFF_IN(x))
#define HWIO_LINK_FLUSH_CONTROL_OFF_RSVD_I_8_BMSK                                                        0xff000000
#define HWIO_LINK_FLUSH_CONTROL_OFF_RSVD_I_8_SHFT                                                              0x18
#define HWIO_LINK_FLUSH_CONTROL_OFF_RSVDP_1_BMSK                                                           0xfffffe
#define HWIO_LINK_FLUSH_CONTROL_OFF_RSVDP_1_SHFT                                                                0x1
#define HWIO_LINK_FLUSH_CONTROL_OFF_AUTO_FLUSH_EN_BMSK                                                          0x1
#define HWIO_LINK_FLUSH_CONTROL_OFF_AUTO_FLUSH_EN_SHFT                                                          0x0

#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_ADDR(x)                                                     ((x) + 0x000008d0)
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_RMSK                                                        0xffffffff
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_ATTR                                                               0x3
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_IN(x)      \
        in_dword_masked(HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_ADDR(x), HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_RMSK)
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_INM(x, m)      \
        in_dword_masked(HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_ADDR(x), m)
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_OUT(x, v)      \
        out_dword(HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_ADDR(x),v)
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_ADDR(x),m,v,HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_IN(x))
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_RSVDP_16_BMSK                                               0xffff0000
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_RSVDP_16_SHFT                                                     0x10
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_MAP_BMSK                                    0xfc00
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_MAP_SHFT                                       0xa
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_RSVDP_3_BMSK                                                     0x3f8
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_RSVDP_3_SHFT                                                       0x3
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_VENDORID_BMSK                                  0x4
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_VENDORID_SHFT                                  0x2
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_RSVDP_1_BMSK                                                       0x2
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_RSVDP_1_SHFT                                                       0x1
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_GLOBAL_BMSK                                    0x1
#define HWIO_AMBA_ERROR_RESPONSE_DEFAULT_OFF_AMBA_ERROR_RESPONSE_GLOBAL_SHFT                                    0x0

#define HWIO_AMBA_LINK_TIMEOUT_OFF_ADDR(x)                                                               ((x) + 0x000008d4)
#define HWIO_AMBA_LINK_TIMEOUT_OFF_RMSK                                                                  0xffffffff
#define HWIO_AMBA_LINK_TIMEOUT_OFF_ATTR                                                                         0x3
#define HWIO_AMBA_LINK_TIMEOUT_OFF_IN(x)      \
        in_dword_masked(HWIO_AMBA_LINK_TIMEOUT_OFF_ADDR(x), HWIO_AMBA_LINK_TIMEOUT_OFF_RMSK)
#define HWIO_AMBA_LINK_TIMEOUT_OFF_INM(x, m)      \
        in_dword_masked(HWIO_AMBA_LINK_TIMEOUT_OFF_ADDR(x), m)
#define HWIO_AMBA_LINK_TIMEOUT_OFF_OUT(x, v)      \
        out_dword(HWIO_AMBA_LINK_TIMEOUT_OFF_ADDR(x),v)
#define HWIO_AMBA_LINK_TIMEOUT_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AMBA_LINK_TIMEOUT_OFF_ADDR(x),m,v,HWIO_AMBA_LINK_TIMEOUT_OFF_IN(x))
#define HWIO_AMBA_LINK_TIMEOUT_OFF_RSVDP_9_BMSK                                                          0xfffffe00
#define HWIO_AMBA_LINK_TIMEOUT_OFF_RSVDP_9_SHFT                                                                 0x9
#define HWIO_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_ENABLE_DEFAULT_BMSK                                           0x100
#define HWIO_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_ENABLE_DEFAULT_SHFT                                             0x8
#define HWIO_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_PERIOD_DEFAULT_BMSK                                            0xff
#define HWIO_AMBA_LINK_TIMEOUT_OFF_LINK_TIMEOUT_PERIOD_DEFAULT_SHFT                                             0x0

#define HWIO_AMBA_ORDERING_CTRL_OFF_ADDR(x)                                                              ((x) + 0x000008d8)
#define HWIO_AMBA_ORDERING_CTRL_OFF_RMSK                                                                 0xffffffff
#define HWIO_AMBA_ORDERING_CTRL_OFF_ATTR                                                                        0x3
#define HWIO_AMBA_ORDERING_CTRL_OFF_IN(x)      \
        in_dword_masked(HWIO_AMBA_ORDERING_CTRL_OFF_ADDR(x), HWIO_AMBA_ORDERING_CTRL_OFF_RMSK)
#define HWIO_AMBA_ORDERING_CTRL_OFF_INM(x, m)      \
        in_dword_masked(HWIO_AMBA_ORDERING_CTRL_OFF_ADDR(x), m)
#define HWIO_AMBA_ORDERING_CTRL_OFF_OUT(x, v)      \
        out_dword(HWIO_AMBA_ORDERING_CTRL_OFF_ADDR(x),v)
#define HWIO_AMBA_ORDERING_CTRL_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AMBA_ORDERING_CTRL_OFF_ADDR(x),m,v,HWIO_AMBA_ORDERING_CTRL_OFF_IN(x))
#define HWIO_AMBA_ORDERING_CTRL_OFF_RSVDP_2_BMSK                                                         0xfffffffc
#define HWIO_AMBA_ORDERING_CTRL_OFF_RSVDP_2_SHFT                                                                0x2
#define HWIO_AMBA_ORDERING_CTRL_OFF_AX_SNP_EN_BMSK                                                              0x2
#define HWIO_AMBA_ORDERING_CTRL_OFF_AX_SNP_EN_SHFT                                                              0x1
#define HWIO_AMBA_ORDERING_CTRL_OFF_AX_MSTR_NP_PASS_P_BMSK                                                      0x1
#define HWIO_AMBA_ORDERING_CTRL_OFF_AX_MSTR_NP_PASS_P_SHFT                                                      0x0

#define HWIO_COHERENCY_CONTROL_1_OFF_ADDR(x)                                                             ((x) + 0x000008e0)
#define HWIO_COHERENCY_CONTROL_1_OFF_RMSK                                                                0xffffffff
#define HWIO_COHERENCY_CONTROL_1_OFF_ATTR                                                                       0x3
#define HWIO_COHERENCY_CONTROL_1_OFF_IN(x)      \
        in_dword_masked(HWIO_COHERENCY_CONTROL_1_OFF_ADDR(x), HWIO_COHERENCY_CONTROL_1_OFF_RMSK)
#define HWIO_COHERENCY_CONTROL_1_OFF_INM(x, m)      \
        in_dword_masked(HWIO_COHERENCY_CONTROL_1_OFF_ADDR(x), m)
#define HWIO_COHERENCY_CONTROL_1_OFF_OUT(x, v)      \
        out_dword(HWIO_COHERENCY_CONTROL_1_OFF_ADDR(x),v)
#define HWIO_COHERENCY_CONTROL_1_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_COHERENCY_CONTROL_1_OFF_ADDR(x),m,v,HWIO_COHERENCY_CONTROL_1_OFF_IN(x))
#define HWIO_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_BOUNDARY_LOW_ADDR_BMSK                                  0xfffffffc
#define HWIO_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_BOUNDARY_LOW_ADDR_SHFT                                         0x2
#define HWIO_COHERENCY_CONTROL_1_OFF_RSVDP_1_BMSK                                                               0x2
#define HWIO_COHERENCY_CONTROL_1_OFF_RSVDP_1_SHFT                                                               0x1
#define HWIO_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_VALUE_BMSK                                                     0x1
#define HWIO_COHERENCY_CONTROL_1_OFF_CFG_MEMTYPE_VALUE_SHFT                                                     0x0

#define HWIO_COHERENCY_CONTROL_2_OFF_ADDR(x)                                                             ((x) + 0x000008e4)
#define HWIO_COHERENCY_CONTROL_2_OFF_RMSK                                                                0xffffffff
#define HWIO_COHERENCY_CONTROL_2_OFF_ATTR                                                                       0x3
#define HWIO_COHERENCY_CONTROL_2_OFF_IN(x)      \
        in_dword_masked(HWIO_COHERENCY_CONTROL_2_OFF_ADDR(x), HWIO_COHERENCY_CONTROL_2_OFF_RMSK)
#define HWIO_COHERENCY_CONTROL_2_OFF_INM(x, m)      \
        in_dword_masked(HWIO_COHERENCY_CONTROL_2_OFF_ADDR(x), m)
#define HWIO_COHERENCY_CONTROL_2_OFF_OUT(x, v)      \
        out_dword(HWIO_COHERENCY_CONTROL_2_OFF_ADDR(x),v)
#define HWIO_COHERENCY_CONTROL_2_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_COHERENCY_CONTROL_2_OFF_ADDR(x),m,v,HWIO_COHERENCY_CONTROL_2_OFF_IN(x))
#define HWIO_COHERENCY_CONTROL_2_OFF_CFG_MEMTYPE_BOUNDARY_HIGH_ADDR_BMSK                                 0xffffffff
#define HWIO_COHERENCY_CONTROL_2_OFF_CFG_MEMTYPE_BOUNDARY_HIGH_ADDR_SHFT                                        0x0

#define HWIO_COHERENCY_CONTROL_3_OFF_ADDR(x)                                                             ((x) + 0x000008e8)
#define HWIO_COHERENCY_CONTROL_3_OFF_RMSK                                                                0x78787878
#define HWIO_COHERENCY_CONTROL_3_OFF_ATTR                                                                       0x3
#define HWIO_COHERENCY_CONTROL_3_OFF_IN(x)      \
        in_dword_masked(HWIO_COHERENCY_CONTROL_3_OFF_ADDR(x), HWIO_COHERENCY_CONTROL_3_OFF_RMSK)
#define HWIO_COHERENCY_CONTROL_3_OFF_INM(x, m)      \
        in_dword_masked(HWIO_COHERENCY_CONTROL_3_OFF_ADDR(x), m)
#define HWIO_COHERENCY_CONTROL_3_OFF_OUT(x, v)      \
        out_dword(HWIO_COHERENCY_CONTROL_3_OFF_ADDR(x),v)
#define HWIO_COHERENCY_CONTROL_3_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_COHERENCY_CONTROL_3_OFF_ADDR(x),m,v,HWIO_COHERENCY_CONTROL_3_OFF_IN(x))
#define HWIO_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_VALUE_BMSK                                         0x78000000
#define HWIO_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_VALUE_SHFT                                               0x1b
#define HWIO_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_VALUE_BMSK                                           0x780000
#define HWIO_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_VALUE_SHFT                                               0x13
#define HWIO_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_MODE_BMSK                                              0x7800
#define HWIO_COHERENCY_CONTROL_3_OFF_CFG_MSTR_AWCACHE_MODE_SHFT                                                 0xb
#define HWIO_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_MODE_BMSK                                                0x78
#define HWIO_COHERENCY_CONTROL_3_OFF_CFG_MSTR_ARCACHE_MODE_SHFT                                                 0x3

#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_ADDR(x)                                                           ((x) + 0x000008f0)
#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_RMSK                                                              0xffffffff
#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_ATTR                                                                     0x3
#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_IN(x)      \
        in_dword_masked(HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_ADDR(x), HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_RMSK)
#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_INM(x, m)      \
        in_dword_masked(HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_ADDR(x), m)
#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_OUT(x, v)      \
        out_dword(HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_ADDR(x),v)
#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_ADDR(x),m,v,HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_IN(x))
#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_CFG_AXIMSTR_MSG_ADDR_LOW_BMSK                                     0xfffff000
#define HWIO_AXI_MSTR_MSG_ADDR_LOW_OFF_CFG_AXIMSTR_MSG_ADDR_LOW_SHFT                                            0xc

#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_ADDR(x)                                                          ((x) + 0x000008f4)
#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_RMSK                                                             0xffffffff
#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_ATTR                                                                    0x3
#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_IN(x)      \
        in_dword_masked(HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_ADDR(x), HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_RMSK)
#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_INM(x, m)      \
        in_dword_masked(HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_ADDR(x), m)
#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_OUT(x, v)      \
        out_dword(HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_ADDR(x),v)
#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_ADDR(x),m,v,HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_IN(x))
#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_CFG_AXIMSTR_MSG_ADDR_HIGH_BMSK                                   0xffffffff
#define HWIO_AXI_MSTR_MSG_ADDR_HIGH_OFF_CFG_AXIMSTR_MSG_ADDR_HIGH_SHFT                                          0x0

#define HWIO_PL_LAST_OFF_ADDR(x)                                                                         ((x) + 0x000008fc)
#define HWIO_PL_LAST_OFF_RMSK                                                                            0xffffffff
#define HWIO_PL_LAST_OFF_ATTR                                                                                   0x1
#define HWIO_PL_LAST_OFF_IN(x)      \
        in_dword_masked(HWIO_PL_LAST_OFF_ADDR(x), HWIO_PL_LAST_OFF_RMSK)
#define HWIO_PL_LAST_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PL_LAST_OFF_ADDR(x), m)
#define HWIO_PL_LAST_OFF_RSVDP_1_BMSK                                                                    0xfffffffe
#define HWIO_PL_LAST_OFF_RSVDP_1_SHFT                                                                           0x1
#define HWIO_PL_LAST_OFF_PL_LAST_BMSK                                                                           0x1
#define HWIO_PL_LAST_OFF_PL_LAST_SHFT                                                                           0x0

#define HWIO_IATU_VIEWPORT_OFF_ADDR(x)                                                                   ((x) + 0x00000900)
#define HWIO_IATU_VIEWPORT_OFF_RMSK                                                                      0xffffffff
#define HWIO_IATU_VIEWPORT_OFF_ATTR                                                                             0x3
#define HWIO_IATU_VIEWPORT_OFF_IN(x)      \
        in_dword_masked(HWIO_IATU_VIEWPORT_OFF_ADDR(x), HWIO_IATU_VIEWPORT_OFF_RMSK)
#define HWIO_IATU_VIEWPORT_OFF_INM(x, m)      \
        in_dword_masked(HWIO_IATU_VIEWPORT_OFF_ADDR(x), m)
#define HWIO_IATU_VIEWPORT_OFF_OUT(x, v)      \
        out_dword(HWIO_IATU_VIEWPORT_OFF_ADDR(x),v)
#define HWIO_IATU_VIEWPORT_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IATU_VIEWPORT_OFF_ADDR(x),m,v,HWIO_IATU_VIEWPORT_OFF_IN(x))
#define HWIO_IATU_VIEWPORT_OFF_REGION_DIR_BMSK                                                           0x80000000
#define HWIO_IATU_VIEWPORT_OFF_REGION_DIR_SHFT                                                                 0x1f
#define HWIO_IATU_VIEWPORT_OFF_VP_RSVD_BMSK                                                              0x7ffffff0
#define HWIO_IATU_VIEWPORT_OFF_VP_RSVD_SHFT                                                                     0x4
#define HWIO_IATU_VIEWPORT_OFF_REGION_INDEX_BMSK                                                                0xf
#define HWIO_IATU_VIEWPORT_OFF_REGION_INDEX_SHFT                                                                0x0

#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ADDR(x)                                                   ((x) + 0x00000904)
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_RMSK                                                      0xffffffff
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ATTR                                                             0x3
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IN(x)      \
        in_dword_masked(HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ADDR(x), HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_RMSK)
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_INM(x, m)      \
        in_dword_masked(HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ADDR(x), m)
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_OUT(x, v)      \
        out_dword(HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ADDR(x),v)
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ADDR(x),m,v,HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IN(x))
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_RSVDP_23_BMSK                                             0xff800000
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_RSVDP_23_SHFT                                                   0x17
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_CTRL_1_FUNC_NUM_BMSK                                        0x700000
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_CTRL_1_FUNC_NUM_SHFT                                            0x14
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_PH_BMSK                                                      0xc0000
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_PH_SHFT                                                         0x12
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_AT_BMSK                                                      0x30000
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_AT_SHFT                                                         0x10
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_RSVDP_13_BMSK                                                 0xe000
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_RSVDP_13_SHFT                                                    0xd
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TH_BMSK                                                       0x1000
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TH_SHFT                                                          0xc
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IDO_BMSK                                                       0x800
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_IDO_SHFT                                                         0xb
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ATTR_BMSK                                                      0x600
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ATTR_SHFT                                                        0x9
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TD_BMSK                                                        0x100
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TD_SHFT                                                          0x8
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TC_BMSK                                                         0xe0
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TC_SHFT                                                          0x5
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TYPE_BMSK                                                       0x1f
#define HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_TYPE_SHFT                                                        0x0

#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_ADDR(x)                                                   ((x) + 0x00000908)
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RMSK                                                      0xf7ffffff
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_ATTR                                                             0x3
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IN(x)      \
        in_dword_masked(HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_ADDR(x), HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RMSK)
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INM(x, m)      \
        in_dword_masked(HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_ADDR(x), m)
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_OUT(x, v)      \
        out_dword(HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_ADDR(x),v)
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_ADDR(x),m,v,HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_IN(x))
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_REGION_EN_BMSK                                            0x80000000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_REGION_EN_SHFT                                                  0x1f
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RSVDP_30_BMSK                                             0x40000000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RSVDP_30_SHFT                                                   0x1e
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INVERT_MODE_BMSK                                          0x20000000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INVERT_MODE_SHFT                                                0x1d
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_CFG_SHIFT_MODE_BMSK                                       0x10000000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_CFG_SHIFT_MODE_SHFT                                             0x1c
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RSVDP_24_BMSK                                              0x7000000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RSVDP_24_SHFT                                                   0x18
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_HEADER_SUBSTITUTE_EN_BMSK                                   0x800000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_HEADER_SUBSTITUTE_EN_SHFT                                       0x17
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INHIBIT_PAYLOAD_BMSK                                        0x400000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_INHIBIT_PAYLOAD_SHFT                                            0x16
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RSVDP_21_BMSK                                               0x200000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RSVDP_21_SHFT                                                   0x15
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_SNP_BMSK                                                    0x100000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_SNP_SHFT                                                        0x14
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_FUNC_BYPASS_BMSK                                             0x80000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_FUNC_BYPASS_SHFT                                                0x13
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RSVDP_17_BMSK                                                0x60000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RSVDP_17_SHFT                                                   0x11
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG_SUBSTITUTE_EN_BMSK                                       0x10000
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG_SUBSTITUTE_EN_SHFT                                          0x10
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG_BMSK                                                      0xff00
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_TAG_SHFT                                                         0x8
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_MSG_CODE_BMSK                                                   0xff
#define HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_MSG_CODE_SHFT                                                    0x0

#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x)                                                   ((x) + 0x0000090c)
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_RMSK                                                      0xffffffff
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_ATTR                                                             0x3
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_IN(x)      \
        in_dword_masked(HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x), HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_RMSK)
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_INM(x, m)      \
        in_dword_masked(HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x), m)
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_OUT(x, v)      \
        out_dword(HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x),v)
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x),m,v,HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_IN(x))
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_RW_BMSK                                          0xfffff000
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_RW_SHFT                                                 0xc
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_HW_BMSK                                               0xfff
#define HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_LWR_BASE_HW_SHFT                                                 0x0

#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x)                                                 ((x) + 0x00000910)
#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_RMSK                                                    0xffffffff
#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_ATTR                                                           0x3
#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_IN(x)      \
        in_dword_masked(HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x), HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_RMSK)
#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_INM(x, m)      \
        in_dword_masked(HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x), m)
#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_OUT(x, v)      \
        out_dword(HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x),v)
#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_ADDR(x),m,v,HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_IN(x))
#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_UPPER_BASE_RW_BMSK                                      0xffffffff
#define HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_UPPER_BASE_RW_SHFT                                             0x0

#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_ADDR(x)                                                      ((x) + 0x00000914)
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_RMSK                                                         0xffffffff
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_ATTR                                                                0x3
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IN(x)      \
        in_dword_masked(HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_ADDR(x), HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_RMSK)
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_INM(x, m)      \
        in_dword_masked(HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_ADDR(x), m)
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_OUT(x, v)      \
        out_dword(HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_ADDR(x),v)
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_ADDR(x),m,v,HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_IN(x))
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_RW_BMSK                                           0xfffff000
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_RW_SHFT                                                  0xc
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_HW_BMSK                                                0xfff
#define HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_LIMIT_ADDR_HW_SHFT                                                  0x0

#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x)                                                 ((x) + 0x00000918)
#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_RMSK                                                    0xffffffff
#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_ATTR                                                           0x3
#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_IN(x)      \
        in_dword_masked(HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x), HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_RMSK)
#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_INM(x, m)      \
        in_dword_masked(HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x), m)
#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_OUT(x, v)      \
        out_dword(HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x),v)
#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x),m,v,HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_IN(x))
#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_LWR_TARGET_RW_OUTBOUND_BMSK                             0xffffffff
#define HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_LWR_TARGET_RW_OUTBOUND_SHFT                                    0x0

#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x)                                               ((x) + 0x0000091c)
#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_RMSK                                                  0xffffffff
#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_ATTR                                                         0x3
#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_IN(x)      \
        in_dword_masked(HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x), HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_RMSK)
#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_INM(x, m)      \
        in_dword_masked(HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x), m)
#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_OUT(x, v)      \
        out_dword(HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x),v)
#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(x),m,v,HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_IN(x))
#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_UPPER_TARGET_RW_BMSK                                  0xffffffff
#define HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_UPPER_TARGET_RW_SHFT                                         0x0

#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_ADDR(x)                                                          ((x) + 0x00000a74)
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_RMSK                                                             0xfffe0000
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_ATTR                                                                    0x3
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_IN(x)      \
        in_dword_masked(HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_ADDR(x), HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_RMSK)
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_INM(x, m)      \
        in_dword_masked(HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_ADDR(x), m)
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_OUT(x, v)      \
        out_dword(HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_ADDR(x),v)
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_ADDR(x),m,v,HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_IN(x))
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_DMA_TH_BMSK                                                      0x80000000
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_DMA_TH_SHFT                                                            0x1f
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_DMA_PH_BMSK                                                      0x60000000
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_DMA_PH_SHFT                                                            0x1d
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_DMA_ST_BMSK                                                       0x1fe0000
#define HWIO_DMA_CH_CONTROL2_OFF_WRCH_0_DMA_ST_SHFT                                                            0x11

#define HWIO_PL_LTR_LATENCY_OFF_ADDR(x)                                                                  ((x) + 0x00000b30)
#define HWIO_PL_LTR_LATENCY_OFF_RMSK                                                                     0xffffffff
#define HWIO_PL_LTR_LATENCY_OFF_ATTR                                                                            0x3
#define HWIO_PL_LTR_LATENCY_OFF_IN(x)      \
        in_dword_masked(HWIO_PL_LTR_LATENCY_OFF_ADDR(x), HWIO_PL_LTR_LATENCY_OFF_RMSK)
#define HWIO_PL_LTR_LATENCY_OFF_INM(x, m)      \
        in_dword_masked(HWIO_PL_LTR_LATENCY_OFF_ADDR(x), m)
#define HWIO_PL_LTR_LATENCY_OFF_OUT(x, v)      \
        out_dword(HWIO_PL_LTR_LATENCY_OFF_ADDR(x),v)
#define HWIO_PL_LTR_LATENCY_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PL_LTR_LATENCY_OFF_ADDR(x),m,v,HWIO_PL_LTR_LATENCY_OFF_IN(x))
#define HWIO_PL_LTR_LATENCY_OFF_NO_SNOOP_LATENCY_REQUIRE_BMSK                                            0x80000000
#define HWIO_PL_LTR_LATENCY_OFF_NO_SNOOP_LATENCY_REQUIRE_SHFT                                                  0x1f
#define HWIO_PL_LTR_LATENCY_OFF_RSVDP_29_BMSK                                                            0x60000000
#define HWIO_PL_LTR_LATENCY_OFF_RSVDP_29_SHFT                                                                  0x1d
#define HWIO_PL_LTR_LATENCY_OFF_NO_SNOOP_LATENCY_SCALE_BMSK                                              0x1c000000
#define HWIO_PL_LTR_LATENCY_OFF_NO_SNOOP_LATENCY_SCALE_SHFT                                                    0x1a
#define HWIO_PL_LTR_LATENCY_OFF_NO_SNOOP_LATENCY_VALUE_BMSK                                               0x3ff0000
#define HWIO_PL_LTR_LATENCY_OFF_NO_SNOOP_LATENCY_VALUE_SHFT                                                    0x10
#define HWIO_PL_LTR_LATENCY_OFF_SNOOP_LATENCY_REQUIRE_BMSK                                                   0x8000
#define HWIO_PL_LTR_LATENCY_OFF_SNOOP_LATENCY_REQUIRE_SHFT                                                      0xf
#define HWIO_PL_LTR_LATENCY_OFF_RSVDP_13_BMSK                                                                0x6000
#define HWIO_PL_LTR_LATENCY_OFF_RSVDP_13_SHFT                                                                   0xd
#define HWIO_PL_LTR_LATENCY_OFF_SNOOP_LATENCY_SCALE_BMSK                                                     0x1c00
#define HWIO_PL_LTR_LATENCY_OFF_SNOOP_LATENCY_SCALE_SHFT                                                        0xa
#define HWIO_PL_LTR_LATENCY_OFF_SNOOP_LATENCY_VALUE_BMSK                                                      0x3ff
#define HWIO_PL_LTR_LATENCY_OFF_SNOOP_LATENCY_VALUE_SHFT                                                        0x0

#define HWIO_AUX_CLK_FREQ_OFF_ADDR(x)                                                                    ((x) + 0x00000b40)
#define HWIO_AUX_CLK_FREQ_OFF_RMSK                                                                       0xffffffff
#define HWIO_AUX_CLK_FREQ_OFF_ATTR                                                                              0x3
#define HWIO_AUX_CLK_FREQ_OFF_IN(x)      \
        in_dword_masked(HWIO_AUX_CLK_FREQ_OFF_ADDR(x), HWIO_AUX_CLK_FREQ_OFF_RMSK)
#define HWIO_AUX_CLK_FREQ_OFF_INM(x, m)      \
        in_dword_masked(HWIO_AUX_CLK_FREQ_OFF_ADDR(x), m)
#define HWIO_AUX_CLK_FREQ_OFF_OUT(x, v)      \
        out_dword(HWIO_AUX_CLK_FREQ_OFF_ADDR(x),v)
#define HWIO_AUX_CLK_FREQ_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AUX_CLK_FREQ_OFF_ADDR(x),m,v,HWIO_AUX_CLK_FREQ_OFF_IN(x))
#define HWIO_AUX_CLK_FREQ_OFF_RSVDP_10_BMSK                                                              0xfffffc00
#define HWIO_AUX_CLK_FREQ_OFF_RSVDP_10_SHFT                                                                     0xa
#define HWIO_AUX_CLK_FREQ_OFF_AUX_CLK_FREQ_BMSK                                                               0x3ff
#define HWIO_AUX_CLK_FREQ_OFF_AUX_CLK_FREQ_SHFT                                                                 0x0

#define HWIO_L1_SUBSTATES_OFF_ADDR(x)                                                                    ((x) + 0x00000b44)
#define HWIO_L1_SUBSTATES_OFF_RMSK                                                                       0xffffffff
#define HWIO_L1_SUBSTATES_OFF_ATTR                                                                              0x3
#define HWIO_L1_SUBSTATES_OFF_IN(x)      \
        in_dword_masked(HWIO_L1_SUBSTATES_OFF_ADDR(x), HWIO_L1_SUBSTATES_OFF_RMSK)
#define HWIO_L1_SUBSTATES_OFF_INM(x, m)      \
        in_dword_masked(HWIO_L1_SUBSTATES_OFF_ADDR(x), m)
#define HWIO_L1_SUBSTATES_OFF_OUT(x, v)      \
        out_dword(HWIO_L1_SUBSTATES_OFF_ADDR(x),v)
#define HWIO_L1_SUBSTATES_OFF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_L1_SUBSTATES_OFF_ADDR(x),m,v,HWIO_L1_SUBSTATES_OFF_IN(x))
#define HWIO_L1_SUBSTATES_OFF_RSVDP_8_BMSK                                                               0xffffff00
#define HWIO_L1_SUBSTATES_OFF_RSVDP_8_SHFT                                                                      0x8
#define HWIO_L1_SUBSTATES_OFF_L1SUB_T_PCLKACK_BMSK                                                             0xc0
#define HWIO_L1_SUBSTATES_OFF_L1SUB_T_PCLKACK_SHFT                                                              0x6
#define HWIO_L1_SUBSTATES_OFF_L1SUB_T_L1_2_BMSK                                                                0x3c
#define HWIO_L1_SUBSTATES_OFF_L1SUB_T_L1_2_SHFT                                                                 0x2
#define HWIO_L1_SUBSTATES_OFF_L1SUB_T_POWER_OFF_BMSK                                                            0x3
#define HWIO_L1_SUBSTATES_OFF_L1SUB_T_POWER_OFF_SHFT                                                            0x0

/*----------------------------------------------------------------------------
 * MODULE: PCIE30_ELBI
 *--------------------------------------------------------------------------*/

#define PCIE30_ELBI_REG_BASE                                              (PCIE_SS_VBU_TN_BASE      + 0x00000f20)

#define HWIO_PCIE30_ELBI_VERSION_ADDR(x)                                  ((x) + 0x00000000)
#define HWIO_PCIE30_ELBI_VERSION_RMSK                                          0xfff
#define HWIO_PCIE30_ELBI_VERSION_ATTR                                            0x1
#define HWIO_PCIE30_ELBI_VERSION_IN(x)      \
        in_dword_masked(HWIO_PCIE30_ELBI_VERSION_ADDR(x), HWIO_PCIE30_ELBI_VERSION_RMSK)
#define HWIO_PCIE30_ELBI_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_ELBI_VERSION_ADDR(x), m)
#define HWIO_PCIE30_ELBI_VERSION_IP_CAT_VERSION_BMSK                           0xfff
#define HWIO_PCIE30_ELBI_VERSION_IP_CAT_VERSION_SHFT                             0x0

#define HWIO_PCIE30_ELBI_SYS_CTRL_ADDR(x)                                 ((x) + 0x00000004)
#define HWIO_PCIE30_ELBI_SYS_CTRL_RMSK                                        0xfff0
#define HWIO_PCIE30_ELBI_SYS_CTRL_ATTR                                           0x3
#define HWIO_PCIE30_ELBI_SYS_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_ELBI_SYS_CTRL_ADDR(x), HWIO_PCIE30_ELBI_SYS_CTRL_RMSK)
#define HWIO_PCIE30_ELBI_SYS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_ELBI_SYS_CTRL_ADDR(x), m)
#define HWIO_PCIE30_ELBI_SYS_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_ELBI_SYS_CTRL_ADDR(x),v)
#define HWIO_PCIE30_ELBI_SYS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_ELBI_SYS_CTRL_ADDR(x),m,v,HWIO_PCIE30_ELBI_SYS_CTRL_IN(x))
#define HWIO_PCIE30_ELBI_SYS_CTRL_APPS_PM_XMT_PME_BMSK                        0xf000
#define HWIO_PCIE30_ELBI_SYS_CTRL_APPS_PM_XMT_PME_SHFT                           0xc
#define HWIO_PCIE30_ELBI_SYS_CTRL_OUTBAND_PWRUP_CMD_BMSK                       0xf00
#define HWIO_PCIE30_ELBI_SYS_CTRL_OUTBAND_PWRUP_CMD_SHFT                         0x8
#define HWIO_PCIE30_ELBI_SYS_CTRL_CLK_PM_EN_BMSK                                0x80
#define HWIO_PCIE30_ELBI_SYS_CTRL_CLK_PM_EN_SHFT                                 0x7
#define HWIO_PCIE30_ELBI_SYS_CTRL_INIT_RST_BMSK                                 0x40
#define HWIO_PCIE30_ELBI_SYS_CTRL_INIT_RST_SHFT                                  0x6
#define HWIO_PCIE30_ELBI_SYS_CTRL_UNLOCK_MSG_BMSK                               0x20
#define HWIO_PCIE30_ELBI_SYS_CTRL_UNLOCK_MSG_SHFT                                0x5
#define HWIO_PCIE30_ELBI_SYS_CTRL_PME_TURNOFF_MSG_BMSK                          0x10
#define HWIO_PCIE30_ELBI_SYS_CTRL_PME_TURNOFF_MSG_SHFT                           0x4

#define HWIO_PCIE30_ELBI_SYS_STTS_ADDR(x)                                 ((x) + 0x00000008)
#define HWIO_PCIE30_ELBI_SYS_STTS_RMSK                                      0x1fff17
#define HWIO_PCIE30_ELBI_SYS_STTS_ATTR                                           0x1
#define HWIO_PCIE30_ELBI_SYS_STTS_IN(x)      \
        in_dword_masked(HWIO_PCIE30_ELBI_SYS_STTS_ADDR(x), HWIO_PCIE30_ELBI_SYS_STTS_RMSK)
#define HWIO_PCIE30_ELBI_SYS_STTS_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_ELBI_SYS_STTS_ADDR(x), m)
#define HWIO_PCIE30_ELBI_SYS_STTS_PM_CURNT_STATE_BMSK                       0x1c0000
#define HWIO_PCIE30_ELBI_SYS_STTS_PM_CURNT_STATE_SHFT                           0x12
#define HWIO_PCIE30_ELBI_SYS_STTS_XMLH_LTSSM_STATE_BMSK                      0x3f000
#define HWIO_PCIE30_ELBI_SYS_STTS_XMLH_LTSSM_STATE_SHFT                          0xc
#define HWIO_PCIE30_ELBI_SYS_STTS_XMLH_IN_RL0S_BMSK                            0x800
#define HWIO_PCIE30_ELBI_SYS_STTS_XMLH_IN_RL0S_SHFT                              0xb
#define HWIO_PCIE30_ELBI_SYS_STTS_XMLH_LINK_UP_BMSK                            0x400
#define HWIO_PCIE30_ELBI_SYS_STTS_XMLH_LINK_UP_SHFT                              0xa
#define HWIO_PCIE30_ELBI_SYS_STTS_CFG_HW_AUTO_SP_DIS_BMSK                      0x200
#define HWIO_PCIE30_ELBI_SYS_STTS_CFG_HW_AUTO_SP_DIS_SHFT                        0x9
#define HWIO_PCIE30_ELBI_SYS_STTS_CPL_TIMEOUT_BMSK                             0x100
#define HWIO_PCIE30_ELBI_SYS_STTS_CPL_TIMEOUT_SHFT                               0x8
#define HWIO_PCIE30_ELBI_SYS_STTS_RADMX_RSP_CMPSR_ERR_BMSK                      0x10
#define HWIO_PCIE30_ELBI_SYS_STTS_RADMX_RSP_CMPSR_ERR_SHFT                       0x4
#define HWIO_PCIE30_ELBI_SYS_STTS_BLK_TLP_BMSK                                   0x4
#define HWIO_PCIE30_ELBI_SYS_STTS_BLK_TLP_SHFT                                   0x2
#define HWIO_PCIE30_ELBI_SYS_STTS_PME_TO_ACK_BMSK                                0x2
#define HWIO_PCIE30_ELBI_SYS_STTS_PME_TO_ACK_SHFT                                0x1
#define HWIO_PCIE30_ELBI_SYS_STTS_LINK_REQ_RST_NOT_BMSK                          0x1
#define HWIO_PCIE30_ELBI_SYS_STTS_LINK_REQ_RST_NOT_SHFT                          0x0
#define HWIO_PCIE30_ELBI_SYS_STTS_LINK_REQ_RST_NOT_CORE_REQUESTING_RESET_FVAL        0x0
#define HWIO_PCIE30_ELBI_SYS_STTS_LINK_REQ_RST_NOT_ACTIVE_FVAL                   0x1

#define HWIO_PCIE30_ELBI_SYS_CLR_ADDR(x)                                  ((x) + 0x0000000c)
#define HWIO_PCIE30_ELBI_SYS_CLR_RMSK                                          0x132
#define HWIO_PCIE30_ELBI_SYS_CLR_ATTR                                            0x2
#define HWIO_PCIE30_ELBI_SYS_CLR_OUT(x, v)      \
        out_dword(HWIO_PCIE30_ELBI_SYS_CLR_ADDR(x),v)
#define HWIO_PCIE30_ELBI_SYS_CLR_CPL_TIMEOUT_BMSK                              0x100
#define HWIO_PCIE30_ELBI_SYS_CLR_CPL_TIMEOUT_SHFT                                0x8
#define HWIO_PCIE30_ELBI_SYS_CLR_GM_RSP_CMPSR_ERR_BMSK                          0x20
#define HWIO_PCIE30_ELBI_SYS_CLR_GM_RSP_CMPSR_ERR_SHFT                           0x5
#define HWIO_PCIE30_ELBI_SYS_CLR_RADMX_RSP_CMPSR_ERR_BMSK                       0x10
#define HWIO_PCIE30_ELBI_SYS_CLR_RADMX_RSP_CMPSR_ERR_SHFT                        0x4
#define HWIO_PCIE30_ELBI_SYS_CLR_PME_TO_ACK_BMSK                                 0x2
#define HWIO_PCIE30_ELBI_SYS_CLR_PME_TO_ACK_SHFT                                 0x1

#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_ADDR(x)                             ((x) + 0x00000020)
#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_RMSK                                       0x7
#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_ATTR                                       0x3
#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_IN(x)      \
        in_dword_masked(HWIO_PCIE30_ELBI_TESTBUS_CTRL_ADDR(x), HWIO_PCIE30_ELBI_TESTBUS_CTRL_RMSK)
#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_ELBI_TESTBUS_CTRL_ADDR(x), m)
#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_OUT(x, v)      \
        out_dword(HWIO_PCIE30_ELBI_TESTBUS_CTRL_ADDR(x),v)
#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_ELBI_TESTBUS_CTRL_ADDR(x),m,v,HWIO_PCIE30_ELBI_TESTBUS_CTRL_IN(x))
#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_DIAG_CTRL_BUS_BMSK                         0x7
#define HWIO_PCIE30_ELBI_TESTBUS_CTRL_DIAG_CTRL_BUS_SHFT                         0x0

#define HWIO_PCIE30_ELBI_DEBUG_INFO_n_ADDR(base,n)                        ((base) + 0x00000030 + 0x4 * (n))
#define HWIO_PCIE30_ELBI_DEBUG_INFO_n_RMSK                                0xffffffff
#define HWIO_PCIE30_ELBI_DEBUG_INFO_n_MAXn                                         1
#define HWIO_PCIE30_ELBI_DEBUG_INFO_n_ATTR                                       0x1
#define HWIO_PCIE30_ELBI_DEBUG_INFO_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_ELBI_DEBUG_INFO_n_ADDR(base,n), HWIO_PCIE30_ELBI_DEBUG_INFO_n_RMSK)
#define HWIO_PCIE30_ELBI_DEBUG_INFO_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_ELBI_DEBUG_INFO_n_ADDR(base,n), mask)
#define HWIO_PCIE30_ELBI_DEBUG_INFO_n_BUS_BMSK                            0xffffffff
#define HWIO_PCIE30_ELBI_DEBUG_INFO_n_BUS_SHFT                                   0x0

#define HWIO_PCIE30_ELBI_TB_DIAG_n_ADDR(base,n)                           ((base) + 0x00000040 + 0x4 * (n))
#define HWIO_PCIE30_ELBI_TB_DIAG_n_RMSK                                   0xffffffff
#define HWIO_PCIE30_ELBI_TB_DIAG_n_MAXn                                           19
#define HWIO_PCIE30_ELBI_TB_DIAG_n_ATTR                                          0x1
#define HWIO_PCIE30_ELBI_TB_DIAG_n_INI(base,n)        \
        in_dword_masked(HWIO_PCIE30_ELBI_TB_DIAG_n_ADDR(base,n), HWIO_PCIE30_ELBI_TB_DIAG_n_RMSK)
#define HWIO_PCIE30_ELBI_TB_DIAG_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PCIE30_ELBI_TB_DIAG_n_ADDR(base,n), mask)
#define HWIO_PCIE30_ELBI_TB_DIAG_n_BUS_BMSK                               0xffffffff
#define HWIO_PCIE30_ELBI_TB_DIAG_n_BUS_SHFT                                      0x0

#define HWIO_PCIE30_ELBI_DEBUG_INFO_EI_ADDR(x)                            ((x) + 0x000000a0)
#define HWIO_PCIE30_ELBI_DEBUG_INFO_EI_RMSK                                   0xffff
#define HWIO_PCIE30_ELBI_DEBUG_INFO_EI_ATTR                                      0x1
#define HWIO_PCIE30_ELBI_DEBUG_INFO_EI_IN(x)      \
        in_dword_masked(HWIO_PCIE30_ELBI_DEBUG_INFO_EI_ADDR(x), HWIO_PCIE30_ELBI_DEBUG_INFO_EI_RMSK)
#define HWIO_PCIE30_ELBI_DEBUG_INFO_EI_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_ELBI_DEBUG_INFO_EI_ADDR(x), m)
#define HWIO_PCIE30_ELBI_DEBUG_INFO_EI_BUS_BMSK                               0xffff
#define HWIO_PCIE30_ELBI_DEBUG_INFO_EI_BUS_SHFT                                  0x0

#define HWIO_PCIE30_ELBI_CS2_ENABLE_ADDR(x)                               ((x) + 0x000000a4)
#define HWIO_PCIE30_ELBI_CS2_ENABLE_RMSK                                         0x1
#define HWIO_PCIE30_ELBI_CS2_ENABLE_ATTR                                         0x3
#define HWIO_PCIE30_ELBI_CS2_ENABLE_IN(x)      \
        in_dword_masked(HWIO_PCIE30_ELBI_CS2_ENABLE_ADDR(x), HWIO_PCIE30_ELBI_CS2_ENABLE_RMSK)
#define HWIO_PCIE30_ELBI_CS2_ENABLE_INM(x, m)      \
        in_dword_masked(HWIO_PCIE30_ELBI_CS2_ENABLE_ADDR(x), m)
#define HWIO_PCIE30_ELBI_CS2_ENABLE_OUT(x, v)      \
        out_dword(HWIO_PCIE30_ELBI_CS2_ENABLE_ADDR(x),v)
#define HWIO_PCIE30_ELBI_CS2_ENABLE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PCIE30_ELBI_CS2_ENABLE_ADDR(x),m,v,HWIO_PCIE30_ELBI_CS2_ENABLE_IN(x))
#define HWIO_PCIE30_ELBI_CS2_ENABLE_ENABLE_BMSK                                  0x1
#define HWIO_PCIE30_ELBI_CS2_ENABLE_ENABLE_SHFT                                  0x0


#endif /* __PCIE30DBIELBIHWIO_H__ */
