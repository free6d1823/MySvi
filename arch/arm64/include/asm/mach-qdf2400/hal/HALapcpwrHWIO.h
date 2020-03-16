#ifndef __QDF2400_APCPWR_HWIO_H__
#define __QDF2400_APCPWR_HWIO_H__
/*
===========================================================================
*/
/**
  @file QDF2400_apcpwr_hwio.h
  @brief Auto-generated HWIO interface include file.

  Reference chip release:
    Amberwing [amberwing_v1.0_p3r59.0]

  This file contains HWIO register definitions for the following modules:
    APCS_HPSS0_HPSS_CFG
    APCS_HPSS0_HPSS_DBG
    APCS_HPSS0_HPSS_HW_EVENT
    APCS_HPSS0_HPSS_STS
    APCS_HPSS0_HPSS_VOTE
    APCS_APR0_SAW4_2_0_AVS
    APCS_APR0_SAW4_2_0_STS
    APCS_APR0_APR_PWR_CTL
    APCS_APR0_APR_STS
    APCS_APR0_APR_SW_EVENT
    APCS_APR0_APR_WAR
    APCS_APR0_APR_DBG
    APCS_APR0_DCVS_APR
    APCS_APR0_APR_CFG
    APCS_APC00_DCVS_APC
    APCS_APC00_APC_APC_CFG
    APCS_APC00_APC_APC_STS
    APCS_APC00_APC_APC_TZ
    APCS_APC00_L2_L2_CFG
    APCS_APC00_L2_L2_PWR_CTL
    APCS_APC00_L2_L2_STS
    APCS_APC00_L2_L2_SW_EVENT
    APCS_APC00_L2_L2_DATA_PUSH
    APCS_APC00_L2_L2_WAR
    APCS_APC00_L2_L2_DBG
    APCS_APC00_CPU0_CPU_CFG
    APCS_APC00_CPU0_CPU_PWR_CTL
    APCS_APC00_CPU0_CPU_STS
    APCS_APC00_CPU0_CPU_SW_EVENT
    APCS_APC00_CPU0_CPU_WAR
    APCS_APC00_CPU0_CPU_DBG

  'Include' filters applied:
  'Exclude' filters applied: RESERVED DUMMY

  The following substitutions were performed:
    s/_L2_L2_/_L2_/g
    s/_APC_APC_/_APC_/g

  Basic information about the following registers was added:
    HWIO_APCS_APR0_EMU_DBG_MODE_MSK_ADDR
    HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR
    HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR
    HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_ADDR
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
*/

/*----------------------------------------------------------------------------
 * MODULE: APCS_HPSS0_HPSS_CFG
 *--------------------------------------------------------------------------*/

#define APCS_HPSS0_HPSS_CFG_REG_BASE                             (HMSS_PERIPH_BASE      + 0x00287000)
#define APCS_HPSS0_HPSS_CFG_REG_BASE_OFFS                        0x00287000

#define HWIO_APCS_HPSS0_RST_CNTR_CFG_ADDR(x)                     ((x) + 0x00000000)
#define HWIO_APCS_HPSS0_RST_CNTR_CFG_OFFS                        (0x00000000)
#define HWIO_APCS_HPSS0_RST_CNTR_CFG_RMSK                              0x1f
#define HWIO_APCS_HPSS0_RST_CNTR_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_RST_CNTR_CFG_ADDR(x), HWIO_APCS_HPSS0_RST_CNTR_CFG_RMSK)
#define HWIO_APCS_HPSS0_RST_CNTR_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_RST_CNTR_CFG_ADDR(x), m)
#define HWIO_APCS_HPSS0_RST_CNTR_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_RST_CNTR_CFG_ADDR(x),v)
#define HWIO_APCS_HPSS0_RST_CNTR_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_RST_CNTR_CFG_ADDR(x),m,v,HWIO_APCS_HPSS0_RST_CNTR_CFG_IN(x))
#define HWIO_APCS_HPSS0_RST_CNTR_CFG_GFMUX_RST_CNT_BMSK                0x1f
#define HWIO_APCS_HPSS0_RST_CNTR_CFG_GFMUX_RST_CNT_SHFT                 0x0

#define HWIO_APCS_HPSS0_REF_CBCR_ADDR(x)                         ((x) + 0x00000020)
#define HWIO_APCS_HPSS0_REF_CBCR_OFFS                            (0x00000020)
#define HWIO_APCS_HPSS0_REF_CBCR_RMSK                            0x80000003
#define HWIO_APCS_HPSS0_REF_CBCR_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_REF_CBCR_ADDR(x), HWIO_APCS_HPSS0_REF_CBCR_RMSK)
#define HWIO_APCS_HPSS0_REF_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_REF_CBCR_ADDR(x), m)
#define HWIO_APCS_HPSS0_REF_CBCR_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_REF_CBCR_ADDR(x),v)
#define HWIO_APCS_HPSS0_REF_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_REF_CBCR_ADDR(x),m,v,HWIO_APCS_HPSS0_REF_CBCR_IN(x))
#define HWIO_APCS_HPSS0_REF_CBCR_CLK_OFF_BMSK                    0x80000000
#define HWIO_APCS_HPSS0_REF_CBCR_CLK_OFF_SHFT                          0x1f
#define HWIO_APCS_HPSS0_REF_CBCR_HW_CTL_BMSK                            0x2
#define HWIO_APCS_HPSS0_REF_CBCR_HW_CTL_SHFT                            0x1
#define HWIO_APCS_HPSS0_REF_CBCR_SW_CTL_BMSK                            0x1
#define HWIO_APCS_HPSS0_REF_CBCR_SW_CTL_SHFT                            0x0

#define HWIO_APCS_HPSS0_AHB_CBCR_ADDR(x)                         ((x) + 0x00000024)
#define HWIO_APCS_HPSS0_AHB_CBCR_OFFS                            (0x00000024)
#define HWIO_APCS_HPSS0_AHB_CBCR_RMSK                            0x80000003
#define HWIO_APCS_HPSS0_AHB_CBCR_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_AHB_CBCR_ADDR(x), HWIO_APCS_HPSS0_AHB_CBCR_RMSK)
#define HWIO_APCS_HPSS0_AHB_CBCR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_AHB_CBCR_ADDR(x), m)
#define HWIO_APCS_HPSS0_AHB_CBCR_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_AHB_CBCR_ADDR(x),v)
#define HWIO_APCS_HPSS0_AHB_CBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_AHB_CBCR_ADDR(x),m,v,HWIO_APCS_HPSS0_AHB_CBCR_IN(x))
#define HWIO_APCS_HPSS0_AHB_CBCR_CLK_OFF_BMSK                    0x80000000
#define HWIO_APCS_HPSS0_AHB_CBCR_CLK_OFF_SHFT                          0x1f
#define HWIO_APCS_HPSS0_AHB_CBCR_HW_CTL_BMSK                            0x2
#define HWIO_APCS_HPSS0_AHB_CBCR_HW_CTL_SHFT                            0x1
#define HWIO_APCS_HPSS0_AHB_CBCR_SW_CTL_BMSK                            0x1
#define HWIO_APCS_HPSS0_AHB_CBCR_SW_CTL_SHFT                            0x0

#define HWIO_APCS_HPSS0_LDO_CFG_ADDR(x)                          ((x) + 0x000000c0)
#define HWIO_APCS_HPSS0_LDO_CFG_OFFS                             (0x000000c0)
#define HWIO_APCS_HPSS0_LDO_CFG_RMSK                             0xffffffff
#define HWIO_APCS_HPSS0_LDO_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_LDO_CFG_ADDR(x), HWIO_APCS_HPSS0_LDO_CFG_RMSK)
#define HWIO_APCS_HPSS0_LDO_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_LDO_CFG_ADDR(x), m)
#define HWIO_APCS_HPSS0_LDO_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_LDO_CFG_ADDR(x),v)
#define HWIO_APCS_HPSS0_LDO_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_LDO_CFG_ADDR(x),m,v,HWIO_APCS_HPSS0_LDO_CFG_IN(x))
#define HWIO_APCS_HPSS0_LDO_CFG_CFG_BMSK                         0xffffffff
#define HWIO_APCS_HPSS0_LDO_CFG_CFG_SHFT                                0x0

#define HWIO_APCS_HPSS0_APM_CFG_ADDR(x)                          ((x) + 0x000000c4)
#define HWIO_APCS_HPSS0_APM_CFG_OFFS                             (0x000000c4)
#define HWIO_APCS_HPSS0_APM_CFG_RMSK                                   0xff
#define HWIO_APCS_HPSS0_APM_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_APM_CFG_ADDR(x), HWIO_APCS_HPSS0_APM_CFG_RMSK)
#define HWIO_APCS_HPSS0_APM_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_APM_CFG_ADDR(x), m)
#define HWIO_APCS_HPSS0_APM_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_APM_CFG_ADDR(x),v)
#define HWIO_APCS_HPSS0_APM_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_APM_CFG_ADDR(x),m,v,HWIO_APCS_HPSS0_APM_CFG_IN(x))
#define HWIO_APCS_HPSS0_APM_CFG_CFG_BMSK                               0xff
#define HWIO_APCS_HPSS0_APM_CFG_CFG_SHFT                                0x0

#define HWIO_APCS_HPSS0_ODCM_CFG_ADDR(x)                         ((x) + 0x000000c8)
#define HWIO_APCS_HPSS0_ODCM_CFG_OFFS                            (0x000000c8)
#define HWIO_APCS_HPSS0_ODCM_CFG_RMSK                            0xffffffff
#define HWIO_APCS_HPSS0_ODCM_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_ODCM_CFG_ADDR(x), HWIO_APCS_HPSS0_ODCM_CFG_RMSK)
#define HWIO_APCS_HPSS0_ODCM_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_ODCM_CFG_ADDR(x), m)
#define HWIO_APCS_HPSS0_ODCM_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_ODCM_CFG_ADDR(x),v)
#define HWIO_APCS_HPSS0_ODCM_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_ODCM_CFG_ADDR(x),m,v,HWIO_APCS_HPSS0_ODCM_CFG_IN(x))
#define HWIO_APCS_HPSS0_ODCM_CFG_CFG_BMSK                        0xffffffff
#define HWIO_APCS_HPSS0_ODCM_CFG_CFG_SHFT                               0x0

#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_ADDR(x)                    ((x) + 0x000000d0)
#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_OFFS                       (0x000000d0)
#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_RMSK                             0x7f
#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_MEM_VMIN_VREF_ADDR(x), HWIO_APCS_HPSS0_MEM_VMIN_VREF_RMSK)
#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_MEM_VMIN_VREF_ADDR(x), m)
#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_MEM_VMIN_VREF_ADDR(x),v)
#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_MEM_VMIN_VREF_ADDR(x),m,v,HWIO_APCS_HPSS0_MEM_VMIN_VREF_IN(x))
#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_VREF_BMSK                        0x7f
#define HWIO_APCS_HPSS0_MEM_VMIN_VREF_VREF_SHFT                         0x0

#define HWIO_APCS_HPSS0_MEM_RET_VREF_ADDR(x)                     ((x) + 0x000000d4)
#define HWIO_APCS_HPSS0_MEM_RET_VREF_OFFS                        (0x000000d4)
#define HWIO_APCS_HPSS0_MEM_RET_VREF_RMSK                              0x7f
#define HWIO_APCS_HPSS0_MEM_RET_VREF_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_MEM_RET_VREF_ADDR(x), HWIO_APCS_HPSS0_MEM_RET_VREF_RMSK)
#define HWIO_APCS_HPSS0_MEM_RET_VREF_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_MEM_RET_VREF_ADDR(x), m)
#define HWIO_APCS_HPSS0_MEM_RET_VREF_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_MEM_RET_VREF_ADDR(x),v)
#define HWIO_APCS_HPSS0_MEM_RET_VREF_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_MEM_RET_VREF_ADDR(x),m,v,HWIO_APCS_HPSS0_MEM_RET_VREF_IN(x))
#define HWIO_APCS_HPSS0_MEM_RET_VREF_VREF_BMSK                         0x7f
#define HWIO_APCS_HPSS0_MEM_RET_VREF_VREF_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_HPSS0_HPSS_DBG
 *--------------------------------------------------------------------------*/

#define APCS_HPSS0_HPSS_DBG_REG_BASE                                     (HMSS_PERIPH_BASE      + 0x00307000)
#define APCS_HPSS0_HPSS_DBG_REG_BASE_OFFS                                0x00307000

#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_ADDR(x)                             ((x) + 0x00000000)
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_OFFS                                (0x00000000)
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_RMSK                                 0x3f30773
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_WDOG_DIAG_EN_ADDR(x), HWIO_APCS_HPSS0_WDOG_DIAG_EN_RMSK)
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_WDOG_DIAG_EN_ADDR(x), m)
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_WDOG_DIAG_EN_ADDR(x),v)
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_WDOG_DIAG_EN_ADDR(x),m,v,HWIO_APCS_HPSS0_WDOG_DIAG_EN_IN(x))
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_LDO_BMSK                    0x2000000
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_LDO_SHFT                         0x19
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_NMM_BMSK                    0x1000000
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_NMM_SHFT                         0x18
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_DCVS_VOTE_BMSK               0x800000
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_DCVS_VOTE_SHFT                   0x17
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_DCVS_REQ_BMSK                0x400000
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_DCVS_REQ_SHFT                    0x16
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_CPR_BMSK                     0x200000
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_CPR_SHFT                         0x15
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_AVM_BMSK                     0x100000
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_DSBL_AVM_SHFT                         0x14
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_ENBL_FLM_THROTTLE_BMSK             0x20000
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_ENBL_FLM_THROTTLE_SHFT                0x11
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_ENBL_REDUCE_FREQ_BMSK              0x10000
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WDW_ENBL_REDUCE_FREQ_SHFT                 0x10
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_SUDN_ACK_OVRRIDE_BMSK                0x400
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_SUDN_ACK_OVRRIDE_SHFT                  0xa
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_BGUP_ACK_OVRRIDE_BMSK                0x200
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_BGUP_ACK_OVRRIDE_SHFT                  0x9
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_EN_SHALLOW_BMSK                      0x100
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_EN_SHALLOW_SHFT                        0x8
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_EN_APC2_BMSK                          0x40
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_EN_APC2_SHFT                           0x6
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_EN_APC1_BMSK                          0x20
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_EN_APC1_SHFT                           0x5
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_EN_APC0_BMSK                          0x10
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_SPM_EN_APC0_SHFT                           0x4
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WPRS_EN_BMSK                               0x2
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WPRS_EN_SHFT                               0x1
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WPRH_EN_BMSK                               0x1
#define HWIO_APCS_HPSS0_WDOG_DIAG_EN_WPRH_EN_SHFT                               0x0

#define HWIO_APCS_HPSS0_TEST_BUS_SEL_ADDR(x)                             ((x) + 0x00000008)
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_OFFS                                (0x00000008)
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_RMSK                                0xffffffff
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_TEST_BUS_SEL_ADDR(x), HWIO_APCS_HPSS0_TEST_BUS_SEL_RMSK)
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_TEST_BUS_SEL_ADDR(x), m)
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_TEST_BUS_SEL_ADDR(x),v)
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_TEST_BUS_SEL_ADDR(x),m,v,HWIO_APCS_HPSS0_TEST_BUS_SEL_IN(x))
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_RSV_BMSK                            0xfc000000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_RSV_SHFT                                  0x1a
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_IO_BMSK                     0x2000000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_IO_SHFT                          0x19
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_IO_BMSK                     0x1000000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_IO_SHFT                          0x18
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_IO_BMSK                      0x800000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_IO_SHFT                          0x17
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_SMT_CPR_BMSK                      0x400000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_SMT_CPR_SHFT                          0x16
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_ACC_CTL_BMSK                      0x200000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_ACC_CTL_SHFT                          0x15
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_NMM_BMSK                          0x100000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_NMM_SHFT                              0x14
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_DCVS_BMSK                          0x80000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_DCVS_SHFT                             0x13
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_AVM_BMSK                           0x40000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_AVM_SHFT                              0x12
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_FLM_BMSK                           0x20000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_FLM_SHFT                              0x11
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_ODCM_STS_BMSK                 0x10000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_ODCM_STS_SHFT                    0x10
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_ODCM_STS_BMSK                  0x8000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_ODCM_STS_SHFT                     0xf
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_ODCM_STS_BMSK                  0x4000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_ODCM_STS_SHFT                     0xe
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_ACTV_MODE_BMSK                      0x2000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_ACTV_MODE_SHFT                         0xd
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_SER_STS_BMSK                        0x1000
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_SER_STS_SHFT                           0xc
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_GLB_CONST_BMSK                       0x800
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_GLB_CONST_SHFT                         0xb
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APR_CPR3_BMSK                        0x400
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APR_CPR3_SHFT                          0xa
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APR_SAW_BMSK                         0x200
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APR_SAW_SHFT                           0x9
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_L2_SAW_BMSK                     0x100
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_L2_SAW_SHFT                       0x8
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_C1_SAW_BMSK                      0x80
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_C1_SAW_SHFT                       0x7
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_C0_SAW_BMSK                      0x40
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC2_C0_SAW_SHFT                       0x6
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_L2_SAW_BMSK                      0x20
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_L2_SAW_SHFT                       0x5
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_C1_SAW_BMSK                      0x10
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_C1_SAW_SHFT                       0x4
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_C0_SAW_BMSK                       0x8
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC1_C0_SAW_SHFT                       0x3
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_L2_SAW_BMSK                       0x4
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_L2_SAW_SHFT                       0x2
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_C1_SAW_BMSK                       0x2
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_C1_SAW_SHFT                       0x1
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_C0_SAW_BMSK                       0x1
#define HWIO_APCS_HPSS0_TEST_BUS_SEL_SEL_APC0_C0_SAW_SHFT                       0x0

#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_ADDR(x)                         ((x) + 0x0000000c)
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_OFFS                            (0x0000000c)
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_RMSK                                   0xf
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_ADDR(x), HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_RMSK)
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_ADDR(x), m)
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_ADDR(x),v)
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_ADDR(x),m,v,HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_IN(x))
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_LVL2_SEL_BMSK                          0xc
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_LVL2_SEL_SHFT                          0x2
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_LVL1_SEL_BMSK                          0x3
#define HWIO_APCS_HPSS0_PLL_TEST_CLK_SEL_LVL1_SEL_SHFT                          0x0

#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_ADDR(x)                         ((x) + 0x00000010)
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_OFFS                            (0x00000010)
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_RMSK                                  0x3f
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_ADDR(x), HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_RMSK)
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_ADDR(x), m)
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_ADDR(x),v)
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_ADDR(x),m,v,HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_IN(x))
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_LVL3_SEL_BMSK                         0x30
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_LVL3_SEL_SHFT                          0x4
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_LVL2_SEL_BMSK                          0xc
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_LVL2_SEL_SHFT                          0x2
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_LVL1_SEL_BMSK                          0x3
#define HWIO_APCS_HPSS0_DBG_TEST_CLK_SEL_LVL1_SEL_SHFT                          0x0

#define HWIO_APCS_HPSS0_ATEST0_EN_ADDR(x)                                ((x) + 0x00000014)
#define HWIO_APCS_HPSS0_ATEST0_EN_OFFS                                   (0x00000014)
#define HWIO_APCS_HPSS0_ATEST0_EN_RMSK                                        0x1ff
#define HWIO_APCS_HPSS0_ATEST0_EN_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_ATEST0_EN_ADDR(x), HWIO_APCS_HPSS0_ATEST0_EN_RMSK)
#define HWIO_APCS_HPSS0_ATEST0_EN_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_ATEST0_EN_ADDR(x), m)
#define HWIO_APCS_HPSS0_ATEST0_EN_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_ATEST0_EN_ADDR(x),v)
#define HWIO_APCS_HPSS0_ATEST0_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_ATEST0_EN_ADDR(x),m,v,HWIO_APCS_HPSS0_ATEST0_EN_IN(x))
#define HWIO_APCS_HPSS0_ATEST0_EN_A2_ATEST0_EN_BMSK                           0x100
#define HWIO_APCS_HPSS0_ATEST0_EN_A2_ATEST0_EN_SHFT                             0x8
#define HWIO_APCS_HPSS0_ATEST0_EN_A2C1_ATEST0_EN_BMSK                          0x80
#define HWIO_APCS_HPSS0_ATEST0_EN_A2C1_ATEST0_EN_SHFT                           0x7
#define HWIO_APCS_HPSS0_ATEST0_EN_A2C0_ATEST0_EN_BMSK                          0x40
#define HWIO_APCS_HPSS0_ATEST0_EN_A2C0_ATEST0_EN_SHFT                           0x6
#define HWIO_APCS_HPSS0_ATEST0_EN_A1_ATEST0_EN_BMSK                            0x20
#define HWIO_APCS_HPSS0_ATEST0_EN_A1_ATEST0_EN_SHFT                             0x5
#define HWIO_APCS_HPSS0_ATEST0_EN_A1C1_ATEST0_EN_BMSK                          0x10
#define HWIO_APCS_HPSS0_ATEST0_EN_A1C1_ATEST0_EN_SHFT                           0x4
#define HWIO_APCS_HPSS0_ATEST0_EN_A1C0_ATEST0_EN_BMSK                           0x8
#define HWIO_APCS_HPSS0_ATEST0_EN_A1C0_ATEST0_EN_SHFT                           0x3
#define HWIO_APCS_HPSS0_ATEST0_EN_A0_ATEST0_EN_BMSK                             0x4
#define HWIO_APCS_HPSS0_ATEST0_EN_A0_ATEST0_EN_SHFT                             0x2
#define HWIO_APCS_HPSS0_ATEST0_EN_A0C1_ATEST0_EN_BMSK                           0x2
#define HWIO_APCS_HPSS0_ATEST0_EN_A0C1_ATEST0_EN_SHFT                           0x1
#define HWIO_APCS_HPSS0_ATEST0_EN_A0C0_ATEST0_EN_BMSK                           0x1
#define HWIO_APCS_HPSS0_ATEST0_EN_A0C0_ATEST0_EN_SHFT                           0x0

#define HWIO_APCS_HPSS0_ATEST1_EN_ADDR(x)                                ((x) + 0x00000018)
#define HWIO_APCS_HPSS0_ATEST1_EN_OFFS                                   (0x00000018)
#define HWIO_APCS_HPSS0_ATEST1_EN_RMSK                                        0x1ff
#define HWIO_APCS_HPSS0_ATEST1_EN_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_ATEST1_EN_ADDR(x), HWIO_APCS_HPSS0_ATEST1_EN_RMSK)
#define HWIO_APCS_HPSS0_ATEST1_EN_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_ATEST1_EN_ADDR(x), m)
#define HWIO_APCS_HPSS0_ATEST1_EN_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_ATEST1_EN_ADDR(x),v)
#define HWIO_APCS_HPSS0_ATEST1_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_ATEST1_EN_ADDR(x),m,v,HWIO_APCS_HPSS0_ATEST1_EN_IN(x))
#define HWIO_APCS_HPSS0_ATEST1_EN_A2_ATEST1_EN_BMSK                           0x100
#define HWIO_APCS_HPSS0_ATEST1_EN_A2_ATEST1_EN_SHFT                             0x8
#define HWIO_APCS_HPSS0_ATEST1_EN_A2C1_ATEST1_EN_BMSK                          0x80
#define HWIO_APCS_HPSS0_ATEST1_EN_A2C1_ATEST1_EN_SHFT                           0x7
#define HWIO_APCS_HPSS0_ATEST1_EN_A2C0_ATEST1_EN_BMSK                          0x40
#define HWIO_APCS_HPSS0_ATEST1_EN_A2C0_ATEST1_EN_SHFT                           0x6
#define HWIO_APCS_HPSS0_ATEST1_EN_A1_ATEST1_EN_BMSK                            0x20
#define HWIO_APCS_HPSS0_ATEST1_EN_A1_ATEST1_EN_SHFT                             0x5
#define HWIO_APCS_HPSS0_ATEST1_EN_A1C1_ATEST1_EN_BMSK                          0x10
#define HWIO_APCS_HPSS0_ATEST1_EN_A1C1_ATEST1_EN_SHFT                           0x4
#define HWIO_APCS_HPSS0_ATEST1_EN_A1C0_ATEST1_EN_BMSK                           0x8
#define HWIO_APCS_HPSS0_ATEST1_EN_A1C0_ATEST1_EN_SHFT                           0x3
#define HWIO_APCS_HPSS0_ATEST1_EN_A0_ATEST1_EN_BMSK                             0x4
#define HWIO_APCS_HPSS0_ATEST1_EN_A0_ATEST1_EN_SHFT                             0x2
#define HWIO_APCS_HPSS0_ATEST1_EN_A0C1_ATEST1_EN_BMSK                           0x2
#define HWIO_APCS_HPSS0_ATEST1_EN_A0C1_ATEST1_EN_SHFT                           0x1
#define HWIO_APCS_HPSS0_ATEST1_EN_A0C0_ATEST1_EN_BMSK                           0x1
#define HWIO_APCS_HPSS0_ATEST1_EN_A0C0_ATEST1_EN_SHFT                           0x0

#define HWIO_APCS_HPSS0_ATEST_CFG_ADDR(x)                                ((x) + 0x0000001c)
#define HWIO_APCS_HPSS0_ATEST_CFG_OFFS                                   (0x0000001c)
#define HWIO_APCS_HPSS0_ATEST_CFG_RMSK                                         0xff
#define HWIO_APCS_HPSS0_ATEST_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_ATEST_CFG_ADDR(x), HWIO_APCS_HPSS0_ATEST_CFG_RMSK)
#define HWIO_APCS_HPSS0_ATEST_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_ATEST_CFG_ADDR(x), m)
#define HWIO_APCS_HPSS0_ATEST_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_ATEST_CFG_ADDR(x),v)
#define HWIO_APCS_HPSS0_ATEST_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_ATEST_CFG_ADDR(x),m,v,HWIO_APCS_HPSS0_ATEST_CFG_IN(x))
#define HWIO_APCS_HPSS0_ATEST_CFG_ATEST_CFG_BMSK                               0xff
#define HWIO_APCS_HPSS0_ATEST_CFG_ATEST_CFG_SHFT                                0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_HPSS0_HPSS_HW_EVENT
 *--------------------------------------------------------------------------*/

#define APCS_HPSS0_HPSS_HW_EVENT_REG_BASE                (HMSS_PERIPH_BASE      + 0x00387000)
#define APCS_HPSS0_HPSS_HW_EVENT_REG_BASE_OFFS           0x00387000

#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_ADDR(base,n)      ((base) + 0x00000000 + 0x4 * (n))
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_OFFS(base,n)      (0x00000000 + 0x4 * (n))
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_RMSK              0x8000000f
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_MAXn                      31
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_INI(base,n)        \
        in_dword_masked(HWIO_APCS_HPSS0_HW_EVENT_SEL_n_ADDR(base,n), HWIO_APCS_HPSS0_HW_EVENT_SEL_n_RMSK)
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_APCS_HPSS0_HW_EVENT_SEL_n_ADDR(base,n), mask)
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_OUTI(base,n,val)    \
        out_dword(HWIO_APCS_HPSS0_HW_EVENT_SEL_n_ADDR(base,n),val)
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_HW_EVENT_SEL_n_ADDR(base,n),mask,val,HWIO_APCS_HPSS0_HW_EVENT_SEL_n_INI(base,n))
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_EN_BMSK           0x80000000
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_EN_SHFT                 0x1f
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_SEL_BMSK                 0xf
#define HWIO_APCS_HPSS0_HW_EVENT_SEL_n_SEL_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_HPSS0_HPSS_STS
 *--------------------------------------------------------------------------*/

#define APCS_HPSS0_HPSS_STS_REG_BASE                  (HMSS_PERIPH_BASE      + 0x002c7000)
#define APCS_HPSS0_HPSS_STS_REG_BASE_OFFS             0x002c7000

#define HWIO_APCS_HPSS0_VERSION_ADDR(x)               ((x) + 0x00000fd0)
#define HWIO_APCS_HPSS0_VERSION_OFFS                  (0x00000fd0)
#define HWIO_APCS_HPSS0_VERSION_RMSK                  0xffffffff
#define HWIO_APCS_HPSS0_VERSION_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_VERSION_ADDR(x), HWIO_APCS_HPSS0_VERSION_RMSK)
#define HWIO_APCS_HPSS0_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_VERSION_ADDR(x), m)
#define HWIO_APCS_HPSS0_VERSION_MAJOR_BMSK            0xf0000000
#define HWIO_APCS_HPSS0_VERSION_MAJOR_SHFT                  0x1c
#define HWIO_APCS_HPSS0_VERSION_MINOR_BMSK             0xfff0000
#define HWIO_APCS_HPSS0_VERSION_MINOR_SHFT                  0x10
#define HWIO_APCS_HPSS0_VERSION_STEP_BMSK                 0xffff
#define HWIO_APCS_HPSS0_VERSION_STEP_SHFT                    0x0

#define HWIO_APCS_HPSS0_IDR_ADDR(x)                   ((x) + 0x00000fd8)
#define HWIO_APCS_HPSS0_IDR_OFFS                      (0x00000fd8)
#define HWIO_APCS_HPSS0_IDR_RMSK                      0xf00c0fff
#define HWIO_APCS_HPSS0_IDR_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_IDR_ADDR(x), HWIO_APCS_HPSS0_IDR_RMSK)
#define HWIO_APCS_HPSS0_IDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_IDR_ADDR(x), m)
#define HWIO_APCS_HPSS0_IDR_VARIANT_BMSK              0xf0000000
#define HWIO_APCS_HPSS0_IDR_VARIANT_SHFT                    0x1c
#define HWIO_APCS_HPSS0_IDR_L2_SIZE_BMSK                 0xc0000
#define HWIO_APCS_HPSS0_IDR_L2_SIZE_SHFT                    0x12
#define HWIO_APCS_HPSS0_IDR_NUM_CLUSTER_BMSK               0xff0
#define HWIO_APCS_HPSS0_IDR_NUM_CLUSTER_SHFT                 0x4
#define HWIO_APCS_HPSS0_IDR_NUM_CPU_BMSK                     0xf
#define HWIO_APCS_HPSS0_IDR_NUM_CPU_SHFT                     0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_HPSS0_HPSS_VOTE
 *--------------------------------------------------------------------------*/

#define APCS_HPSS0_HPSS_VOTE_REG_BASE                      (HMSS_PERIPH_BASE      + 0x000c7000)
#define APCS_HPSS0_HPSS_VOTE_REG_BASE_OFFS                 0x000c7000

#define HWIO_APCS_HPSS0_SW_EN_VOTE_ADDR(x)                 ((x) + 0x00000000)
#define HWIO_APCS_HPSS0_SW_EN_VOTE_OFFS                    (0x00000000)
#define HWIO_APCS_HPSS0_SW_EN_VOTE_RMSK                           0x3
#define HWIO_APCS_HPSS0_SW_EN_VOTE_IN(x)      \
        in_dword_masked(HWIO_APCS_HPSS0_SW_EN_VOTE_ADDR(x), HWIO_APCS_HPSS0_SW_EN_VOTE_RMSK)
#define HWIO_APCS_HPSS0_SW_EN_VOTE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_HPSS0_SW_EN_VOTE_ADDR(x), m)
#define HWIO_APCS_HPSS0_SW_EN_VOTE_OUT(x, v)      \
        out_dword(HWIO_APCS_HPSS0_SW_EN_VOTE_ADDR(x),v)
#define HWIO_APCS_HPSS0_SW_EN_VOTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_HPSS0_SW_EN_VOTE_ADDR(x),m,v,HWIO_APCS_HPSS0_SW_EN_VOTE_IN(x))
#define HWIO_APCS_HPSS0_SW_EN_VOTE_CBF_SW_EN_BMSK                 0x2
#define HWIO_APCS_HPSS0_SW_EN_VOTE_CBF_SW_EN_SHFT                 0x1
#define HWIO_APCS_HPSS0_SW_EN_VOTE_APR_SW_EN_BMSK                 0x1
#define HWIO_APCS_HPSS0_SW_EN_VOTE_APR_SW_EN_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_SAW4_2_0_AVS
 *--------------------------------------------------------------------------*/

#define APCS_APR0_SAW4_2_0_AVS_REG_BASE                                 (HMSS_PERIPH_BASE      + 0x00246000)
#define APCS_APR0_SAW4_2_0_AVS_REG_BASE_OFFS                            0x00246000

#define HWIO_APCS_APR0_SAW4_VCTL_ADDR(x)                                ((x) + 0x00000100)
#define HWIO_APCS_APR0_SAW4_VCTL_OFFS                                   (0x00000100)
#define HWIO_APCS_APR0_SAW4_VCTL_RMSK                                     0x1700ff
#define HWIO_APCS_APR0_SAW4_VCTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_VCTL_ADDR(x), HWIO_APCS_APR0_SAW4_VCTL_RMSK)
#define HWIO_APCS_APR0_SAW4_VCTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_VCTL_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_VCTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_VCTL_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_VCTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_VCTL_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_VCTL_IN(x))
#define HWIO_APCS_APR0_SAW4_VCTL_SIZE_BMSK                                0x100000
#define HWIO_APCS_APR0_SAW4_VCTL_SIZE_SHFT                                    0x14
#define HWIO_APCS_APR0_SAW4_VCTL_ADR_IDX_BMSK                              0x70000
#define HWIO_APCS_APR0_SAW4_VCTL_ADR_IDX_SHFT                                 0x10
#define HWIO_APCS_APR0_SAW4_VCTL_PMIC_DATA_BMSK                               0xff
#define HWIO_APCS_APR0_SAW4_VCTL_PMIC_DATA_SHFT                                0x0

#define HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x)                             ((x) + 0x00000104)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_OFFS                                (0x00000104)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_RMSK                                0xffffdf7f
#define HWIO_APCS_APR0_SAW4_AVS_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x), HWIO_APCS_APR0_SAW4_AVS_CTL_RMSK)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_AVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_AVS_CTL_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_AVS_CTL_IN(x))
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_STEP_DN_BMSK                   0xff000000
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_STEP_DN_SHFT                         0x18
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_STEP_UP_BMSK                     0xff0000
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_STEP_UP_SHFT                         0x10
#define HWIO_APCS_APR0_SAW4_AVS_CTL_CPR_RAMP_EN_BMSK                        0x8000
#define HWIO_APCS_APR0_SAW4_AVS_CTL_CPR_RAMP_EN_SHFT                           0xf
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VCTL_RAMP_EN_BMSK                       0x4000
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VCTL_RAMP_EN_SHFT                          0xe
#define HWIO_APCS_APR0_SAW4_AVS_CTL_TMR_CLK_DIV_BMSK                        0x1f00
#define HWIO_APCS_APR0_SAW4_AVS_CTL_TMR_CLK_DIV_SHFT                           0x8
#define HWIO_APCS_APR0_SAW4_AVS_CTL_ILCPR_BMSK                                0x40
#define HWIO_APCS_APR0_SAW4_AVS_CTL_ILCPR_SHFT                                 0x6
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_WIDTH_BMSK                           0x20
#define HWIO_APCS_APR0_SAW4_AVS_CTL_VLVL_WIDTH_SHFT                            0x5
#define HWIO_APCS_APR0_SAW4_AVS_CTL_CTL_SEL_BMSK                              0x10
#define HWIO_APCS_APR0_SAW4_AVS_CTL_CTL_SEL_SHFT                               0x4
#define HWIO_APCS_APR0_SAW4_AVS_CTL_SW_DONE_INT_EN_BMSK                        0x8
#define HWIO_APCS_APR0_SAW4_AVS_CTL_SW_DONE_INT_EN_SHFT                        0x3
#define HWIO_APCS_APR0_SAW4_AVS_CTL_MAX_INT_EN_BMSK                            0x4
#define HWIO_APCS_APR0_SAW4_AVS_CTL_MAX_INT_EN_SHFT                            0x2
#define HWIO_APCS_APR0_SAW4_AVS_CTL_MIN_INT_EN_BMSK                            0x2
#define HWIO_APCS_APR0_SAW4_AVS_CTL_MIN_INT_EN_SHFT                            0x1
#define HWIO_APCS_APR0_SAW4_AVS_CTL_EN_BMSK                                    0x1
#define HWIO_APCS_APR0_SAW4_AVS_CTL_EN_SHFT                                    0x0

#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x)                           ((x) + 0x00000108)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_OFFS                              (0x00000108)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_RMSK                                0xff00ff
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x), HWIO_APCS_APR0_SAW4_AVS_LIMIT_RMSK)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_AVS_LIMIT_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_AVS_LIMIT_IN(x))
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_MAX_VLVL_BMSK                       0xff0000
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_MAX_VLVL_SHFT                           0x10
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_MIN_VLVL_BMSK                           0xff
#define HWIO_APCS_APR0_SAW4_AVS_LIMIT_MIN_VLVL_SHFT                            0x0

#define HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x)                             ((x) + 0x0000010c)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_OFFS                                (0x0000010c)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_RMSK                                     0x3ff
#define HWIO_APCS_APR0_SAW4_AVS_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x), HWIO_APCS_APR0_SAW4_AVS_DLY_RMSK)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_AVS_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_AVS_DLY_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_AVS_DLY_IN(x))
#define HWIO_APCS_APR0_SAW4_AVS_DLY_AVS_DELAY_BMSK                           0x3ff
#define HWIO_APCS_APR0_SAW4_AVS_DLY_AVS_DELAY_SHFT                             0x0

#define HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x)                            ((x) + 0x00000110)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_OFFS                               (0x00000110)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_RMSK                                    0x3ff
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x), HWIO_APCS_APR0_SAW4_VCTL_DLY_RMSK)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_VCTL_DLY_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_VCTL_DLY_IN(x))
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_VCTL_DELAY_BMSK                         0x3ff
#define HWIO_APCS_APR0_SAW4_VCTL_DLY_VCTL_DELAY_SHFT                           0x0

#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_ADDR(x)                         ((x) + 0x00000114)
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_OFFS                            (0x00000114)
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_RMSK                                   0x1
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_AVS_CLR_STS_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_CLR_CMD_BMSK                           0x1
#define HWIO_APCS_APR0_SAW4_AVS_CLR_STS_CLR_CMD_SHFT                           0x0

#define HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x)                             ((x) + 0x00000120)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_OFFS                                (0x00000120)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_RMSK                                  0x7e1ff9
#define HWIO_APCS_APR0_SAW4_CVS_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x), HWIO_APCS_APR0_SAW4_CVS_CTL_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_CVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_CVS_CTL_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_CVS_CTL_IN(x))
#define HWIO_APCS_APR0_SAW4_CVS_CTL_SEQ_IDX_BMSK                          0x700000
#define HWIO_APCS_APR0_SAW4_CVS_CTL_SEQ_IDX_SHFT                              0x14
#define HWIO_APCS_APR0_SAW4_CVS_CTL_REQ_BMSK                               0x80000
#define HWIO_APCS_APR0_SAW4_CVS_CTL_REQ_SHFT                                  0x13
#define HWIO_APCS_APR0_SAW4_CVS_CTL_HALT_DONE_BMSK                         0x40000
#define HWIO_APCS_APR0_SAW4_CVS_CTL_HALT_DONE_SHFT                            0x12
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CTL_SEL_BMSK                           0x20000
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CTL_SEL_SHFT                              0x11
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CVS_START_ADR_BMSK                      0x1ff0
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CVS_START_ADR_SHFT                         0x4
#define HWIO_APCS_APR0_SAW4_CVS_CTL_ISAR_BMSK                                  0x8
#define HWIO_APCS_APR0_SAW4_CVS_CTL_ISAR_SHFT                                  0x3
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CVS_EN_BMSK                                0x1
#define HWIO_APCS_APR0_SAW4_CVS_CTL_CVS_EN_SHFT                                0x0

#define HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x)                             ((x) + 0x00000124)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_OFFS                                (0x00000124)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_RMSK                                0x3fffffff
#define HWIO_APCS_APR0_SAW4_CVS_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x), HWIO_APCS_APR0_SAW4_CVS_DLY_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_CVS_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_CVS_DLY_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_CVS_DLY_IN(x))
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY3_BMSK                           0x3ff00000
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY3_SHFT                                 0x14
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY2_BMSK                              0xffc00
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY2_SHFT                                  0xa
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY1_BMSK                                0x3ff
#define HWIO_APCS_APR0_SAW4_CVS_DLY_DLY1_SHFT                                  0x0

#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n)                ((base) + 0x00000140 + 0x4 * (n))
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_OFFS(base,n)                (0x00000140 + 0x4 * (n))
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_RMSK                        0x801700ff
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_MAXn                                 3
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_INI(base,n)        \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n), HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n), mask)
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_OUTI(base,n,val)    \
        out_dword(HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n),val)
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADDR(base,n),mask,val,HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_INI(base,n))
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_PMIC_CMD_MASK_BMSK          0x80000000
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_PMIC_CMD_MASK_SHFT                0x1f
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_SIZE_BMSK                     0x100000
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_SIZE_SHFT                         0x14
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADR_IDX_BMSK                   0x70000
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_ADR_IDX_SHFT                      0x10
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_DATA_BMSK                         0xff
#define HWIO_APCS_APR0_SAW4_CVS_PMIC_DATA_n_DATA_SHFT                          0x0

#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n)                ((base) + 0x00000200 + 0x4 * (n))
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_OFFS(base,n)                (0x00000200 + 0x4 * (n))
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_RMSK                        0xffffffff
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_MAXn                                31
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_INI(base,n)        \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n), HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_INMI(base,n,mask)    \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n), mask)
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_OUTI(base,n,val)    \
        out_dword(HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n),val)
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_ADDR(base,n),mask,val,HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_INI(base,n))
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD3_BMSK                   0xff000000
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD3_SHFT                         0x18
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD2_BMSK                     0xff0000
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD2_SHFT                         0x10
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD1_BMSK                       0xff00
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD1_SHFT                          0x8
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD0_BMSK                         0xff
#define HWIO_APCS_APR0_SAW4_CVS_SEQ_ENTRY_n_CMD0_SHFT                          0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_SAW4_2_0_STS
 *--------------------------------------------------------------------------*/

#define APCS_APR0_SAW4_2_0_STS_REG_BASE                               (HMSS_PERIPH_BASE      + 0x002c6000)
#define APCS_APR0_SAW4_2_0_STS_REG_BASE_OFFS                          0x002c6000

#define HWIO_APCS_APR0_SAW4_SECURE_ADDR(x)                            ((x) + 0x00000000)
#define HWIO_APCS_APR0_SAW4_SECURE_OFFS                               (0x00000000)
#define HWIO_APCS_APR0_SAW4_SECURE_RMSK                                      0x7
#define HWIO_APCS_APR0_SAW4_SECURE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_SECURE_ADDR(x), HWIO_APCS_APR0_SAW4_SECURE_RMSK)
#define HWIO_APCS_APR0_SAW4_SECURE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_SECURE_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_SECURE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_SECURE_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_SECURE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_SECURE_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_SECURE_IN(x))
#define HWIO_APCS_APR0_SAW4_SECURE_SAW_CTL_BMSK                              0x4
#define HWIO_APCS_APR0_SAW4_SECURE_SAW_CTL_SHFT                              0x2
#define HWIO_APCS_APR0_SAW4_SECURE_PWR_CTL_BMSK                              0x2
#define HWIO_APCS_APR0_SAW4_SECURE_PWR_CTL_SHFT                              0x1
#define HWIO_APCS_APR0_SAW4_SECURE_VLT_CTL_BMSK                              0x1
#define HWIO_APCS_APR0_SAW4_SECURE_VLT_CTL_SHFT                              0x0

#define HWIO_APCS_APR0_SAW4_ID_ADDR(x)                                ((x) + 0x00000004)
#define HWIO_APCS_APR0_SAW4_ID_OFFS                                   (0x00000004)
#define HWIO_APCS_APR0_SAW4_ID_RMSK                                   0xff3f1f7f
#define HWIO_APCS_APR0_SAW4_ID_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_ID_ADDR(x), HWIO_APCS_APR0_SAW4_ID_RMSK)
#define HWIO_APCS_APR0_SAW4_ID_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_ID_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_ID_NUM_SPM_ENTRY_BMSK                     0xff000000
#define HWIO_APCS_APR0_SAW4_ID_NUM_SPM_ENTRY_SHFT                           0x18
#define HWIO_APCS_APR0_SAW4_ID_NUM_PWR_CTL_BMSK                         0x3f0000
#define HWIO_APCS_APR0_SAW4_ID_NUM_PWR_CTL_SHFT                             0x10
#define HWIO_APCS_APR0_SAW4_ID_NUM_CVS_PMIC_DATA_BMSK                     0x1c00
#define HWIO_APCS_APR0_SAW4_ID_NUM_CVS_PMIC_DATA_SHFT                        0xa
#define HWIO_APCS_APR0_SAW4_ID_CVS_PRESENT_BMSK                            0x200
#define HWIO_APCS_APR0_SAW4_ID_CVS_PRESENT_SHFT                              0x9
#define HWIO_APCS_APR0_SAW4_ID_PMIC_DATA_WIDTH_BMSK                        0x100
#define HWIO_APCS_APR0_SAW4_ID_PMIC_DATA_WIDTH_SHFT                          0x8
#define HWIO_APCS_APR0_SAW4_ID_NUM_SPM_PMIC_DATA_BMSK                       0x70
#define HWIO_APCS_APR0_SAW4_ID_NUM_SPM_PMIC_DATA_SHFT                        0x4
#define HWIO_APCS_APR0_SAW4_ID_CFG_NS_ACCESS_BMSK                            0x8
#define HWIO_APCS_APR0_SAW4_ID_CFG_NS_ACCESS_SHFT                            0x3
#define HWIO_APCS_APR0_SAW4_ID_PMIC_ARB_INTF_BMSK                            0x4
#define HWIO_APCS_APR0_SAW4_ID_PMIC_ARB_INTF_SHFT                            0x2
#define HWIO_APCS_APR0_SAW4_ID_AVS_PRESENT_BMSK                              0x2
#define HWIO_APCS_APR0_SAW4_ID_AVS_PRESENT_SHFT                              0x1
#define HWIO_APCS_APR0_SAW4_ID_SPM_PRESENT_BMSK                              0x1
#define HWIO_APCS_APR0_SAW4_ID_SPM_PRESENT_SHFT                              0x0

#define HWIO_APCS_APR0_SAW4_SPM_STS_ADDR(x)                           ((x) + 0x0000000c)
#define HWIO_APCS_APR0_SAW4_SPM_STS_OFFS                              (0x0000000c)
#define HWIO_APCS_APR0_SAW4_SPM_STS_RMSK                              0xffffffff
#define HWIO_APCS_APR0_SAW4_SPM_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_SPM_STS_ADDR(x), HWIO_APCS_APR0_SAW4_SPM_STS_RMSK)
#define HWIO_APCS_APR0_SAW4_SPM_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_SPM_STS_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_SPM_STS_SPM_EVENT_BMSK                    0xffff0000
#define HWIO_APCS_APR0_SAW4_SPM_STS_SPM_EVENT_SHFT                          0x10
#define HWIO_APCS_APR0_SAW4_SPM_STS_SHTDWN_REQ_BMSK                       0x8000
#define HWIO_APCS_APR0_SAW4_SPM_STS_SHTDWN_REQ_SHFT                          0xf
#define HWIO_APCS_APR0_SAW4_SPM_STS_SHTDWN_ACK_BMSK                       0x4000
#define HWIO_APCS_APR0_SAW4_SPM_STS_SHTDWN_ACK_SHFT                          0xe
#define HWIO_APCS_APR0_SAW4_SPM_STS_BRNGUP_REQ_BMSK                       0x2000
#define HWIO_APCS_APR0_SAW4_SPM_STS_BRNGUP_REQ_SHFT                          0xd
#define HWIO_APCS_APR0_SAW4_SPM_STS_BRNGUP_ACK_BMSK                       0x1000
#define HWIO_APCS_APR0_SAW4_SPM_STS_BRNGUP_ACK_SHFT                          0xc
#define HWIO_APCS_APR0_SAW4_SPM_STS_RPM_STATE_BMSK                         0xc00
#define HWIO_APCS_APR0_SAW4_SPM_STS_RPM_STATE_SHFT                           0xa
#define HWIO_APCS_APR0_SAW4_SPM_STS_SPM_BUSY_BMSK                          0x200
#define HWIO_APCS_APR0_SAW4_SPM_STS_SPM_BUSY_SHFT                            0x9
#define HWIO_APCS_APR0_SAW4_SPM_STS_SPM_CMD_ADDR_BMSK                      0x1ff
#define HWIO_APCS_APR0_SAW4_SPM_STS_SPM_CMD_ADDR_SHFT                        0x0

#define HWIO_APCS_APR0_SAW4_SPM_STS2_ADDR(x)                          ((x) + 0x00000010)
#define HWIO_APCS_APR0_SAW4_SPM_STS2_OFFS                             (0x00000010)
#define HWIO_APCS_APR0_SAW4_SPM_STS2_RMSK                               0xffffff
#define HWIO_APCS_APR0_SAW4_SPM_STS2_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_SPM_STS2_ADDR(x), HWIO_APCS_APR0_SAW4_SPM_STS2_RMSK)
#define HWIO_APCS_APR0_SAW4_SPM_STS2_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_SPM_STS2_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_SPM_STS2_CURR_PWR_CTL_BMSK                  0xffffff
#define HWIO_APCS_APR0_SAW4_SPM_STS2_CURR_PWR_CTL_SHFT                       0x0

#define HWIO_APCS_APR0_SAW4_AVS_STS_ADDR(x)                           ((x) + 0x00000014)
#define HWIO_APCS_APR0_SAW4_AVS_STS_OFFS                              (0x00000014)
#define HWIO_APCS_APR0_SAW4_AVS_STS_RMSK                              0x3ff7ffff
#define HWIO_APCS_APR0_SAW4_AVS_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_STS_ADDR(x), HWIO_APCS_APR0_SAW4_AVS_STS_RMSK)
#define HWIO_APCS_APR0_SAW4_AVS_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_AVS_STS_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_CURR_DLY_BMSK                 0x3ff00000
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_CURR_DLY_SHFT                       0x14
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_FLOOR_REQ_BMSK                   0x40000
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_FLOOR_REQ_SHFT                      0x12
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_LDCEIL_REQ_BMSK                  0x20000
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_LDCEIL_REQ_SHFT                     0x11
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_LD_REQ_BMSK                      0x10000
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_LD_REQ_SHFT                         0x10
#define HWIO_APCS_APR0_SAW4_AVS_STS_MAX_ERR_STKY_BMSK                     0x8000
#define HWIO_APCS_APR0_SAW4_AVS_STS_MAX_ERR_STKY_SHFT                        0xf
#define HWIO_APCS_APR0_SAW4_AVS_STS_MIN_ERR_STKY_BMSK                     0x4000
#define HWIO_APCS_APR0_SAW4_AVS_STS_MIN_ERR_STKY_SHFT                        0xe
#define HWIO_APCS_APR0_SAW4_AVS_STS_MAX_LMT_STKY_BMSK                     0x2000
#define HWIO_APCS_APR0_SAW4_AVS_STS_MAX_LMT_STKY_SHFT                        0xd
#define HWIO_APCS_APR0_SAW4_AVS_STS_MIN_LMT_STKY_BMSK                     0x1000
#define HWIO_APCS_APR0_SAW4_AVS_STS_MIN_LMT_STKY_SHFT                        0xc
#define HWIO_APCS_APR0_SAW4_AVS_STS_SIC_SW_DONE_IRQ_BMSK                   0x800
#define HWIO_APCS_APR0_SAW4_AVS_STS_SIC_SW_DONE_IRQ_SHFT                     0xb
#define HWIO_APCS_APR0_SAW4_AVS_STS_SIC_IRQ_BMSK                           0x400
#define HWIO_APCS_APR0_SAW4_AVS_STS_SIC_IRQ_SHFT                             0xa
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_ERR_BMSK                           0x200
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_ERR_SHFT                             0x9
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_ACK_BMSK                           0x100
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_ACK_SHFT                             0x8
#define HWIO_APCS_APR0_SAW4_AVS_STS_VOLTAGE_RAMP_BMSK                       0x80
#define HWIO_APCS_APR0_SAW4_AVS_STS_VOLTAGE_RAMP_SHFT                        0x7
#define HWIO_APCS_APR0_SAW4_AVS_STS_SW_WR_PEND_BMSK                         0x40
#define HWIO_APCS_APR0_SAW4_AVS_STS_SW_WR_PEND_SHFT                          0x6
#define HWIO_APCS_APR0_SAW4_AVS_STS_MAX_INT_BMSK                            0x20
#define HWIO_APCS_APR0_SAW4_AVS_STS_MAX_INT_SHFT                             0x5
#define HWIO_APCS_APR0_SAW4_AVS_STS_MIN_INT_BMSK                            0x10
#define HWIO_APCS_APR0_SAW4_AVS_STS_MIN_INT_SHFT                             0x4
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_UP_REQ_BMSK                          0x8
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_UP_REQ_SHFT                          0x3
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_DN_REQ_BMSK                          0x4
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_DN_REQ_SHFT                          0x2
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_FSM_STATE_BMSK                       0x3
#define HWIO_APCS_APR0_SAW4_AVS_STS_AVS_FSM_STATE_SHFT                       0x0

#define HWIO_APCS_APR0_SAW4_PMIC_STS_ADDR(x)                          ((x) + 0x00000018)
#define HWIO_APCS_APR0_SAW4_PMIC_STS_OFFS                             (0x00000018)
#define HWIO_APCS_APR0_SAW4_PMIC_STS_RMSK                               0xff00ff
#define HWIO_APCS_APR0_SAW4_PMIC_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_PMIC_STS_ADDR(x), HWIO_APCS_APR0_SAW4_PMIC_STS_RMSK)
#define HWIO_APCS_APR0_SAW4_PMIC_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_PMIC_STS_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_PMIC_STS_PMIC_DONE_BMSK                     0x800000
#define HWIO_APCS_APR0_SAW4_PMIC_STS_PMIC_DONE_SHFT                         0x17
#define HWIO_APCS_APR0_SAW4_PMIC_STS_PMIC_REQ_BMSK                      0x400000
#define HWIO_APCS_APR0_SAW4_PMIC_STS_PMIC_REQ_SHFT                          0x16
#define HWIO_APCS_APR0_SAW4_PMIC_STS_CURR_PMIC_ADDR_IDX_BMSK            0x380000
#define HWIO_APCS_APR0_SAW4_PMIC_STS_CURR_PMIC_ADDR_IDX_SHFT                0x13
#define HWIO_APCS_APR0_SAW4_PMIC_STS_CURR_PMIC_SIZE_BMSK                 0x40000
#define HWIO_APCS_APR0_SAW4_PMIC_STS_CURR_PMIC_SIZE_SHFT                    0x12
#define HWIO_APCS_APR0_SAW4_PMIC_STS_PMIC_STATE_BMSK                     0x30000
#define HWIO_APCS_APR0_SAW4_PMIC_STS_PMIC_STATE_SHFT                        0x10
#define HWIO_APCS_APR0_SAW4_PMIC_STS_CURR_PMIC_DATA_BMSK                    0xff
#define HWIO_APCS_APR0_SAW4_PMIC_STS_CURR_PMIC_DATA_SHFT                     0x0

#define HWIO_APCS_APR0_SAW4_RST_ADDR(x)                               ((x) + 0x0000001c)
#define HWIO_APCS_APR0_SAW4_RST_OFFS                                  (0x0000001c)
#define HWIO_APCS_APR0_SAW4_RST_RMSK                                         0x1
#define HWIO_APCS_APR0_SAW4_RST_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_RST_ADDR(x), HWIO_APCS_APR0_SAW4_RST_RMSK)
#define HWIO_APCS_APR0_SAW4_RST_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_RST_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_RST_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SAW4_RST_ADDR(x),v)
#define HWIO_APCS_APR0_SAW4_RST_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SAW4_RST_ADDR(x),m,v,HWIO_APCS_APR0_SAW4_RST_IN(x))
#define HWIO_APCS_APR0_SAW4_RST_RST_BMSK                                     0x1
#define HWIO_APCS_APR0_SAW4_RST_RST_SHFT                                     0x0

#define HWIO_APCS_APR0_SAW4_SPM_STS3_ADDR(x)                          ((x) + 0x00000020)
#define HWIO_APCS_APR0_SAW4_SPM_STS3_OFFS                             (0x00000020)
#define HWIO_APCS_APR0_SAW4_SPM_STS3_RMSK                             0x7fffffff
#define HWIO_APCS_APR0_SAW4_SPM_STS3_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_SPM_STS3_ADDR(x), HWIO_APCS_APR0_SAW4_SPM_STS3_RMSK)
#define HWIO_APCS_APR0_SAW4_SPM_STS3_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_SPM_STS3_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_SPM_STS3_SPM_CURR_DLY_BMSK                0x7fe00000
#define HWIO_APCS_APR0_SAW4_SPM_STS3_SPM_CURR_DLY_SHFT                      0x15
#define HWIO_APCS_APR0_SAW4_SPM_STS3_SPM_EVENT2_BMSK                    0x1fffe0
#define HWIO_APCS_APR0_SAW4_SPM_STS3_SPM_EVENT2_SHFT                         0x5
#define HWIO_APCS_APR0_SAW4_SPM_STS3_DBG_STAY_AWAKE_BMSK                    0x10
#define HWIO_APCS_APR0_SAW4_SPM_STS3_DBG_STAY_AWAKE_SHFT                     0x4
#define HWIO_APCS_APR0_SAW4_SPM_STS3_SLEEP_STATE_BMSK                        0x8
#define HWIO_APCS_APR0_SAW4_SPM_STS3_SLEEP_STATE_SHFT                        0x3
#define HWIO_APCS_APR0_SAW4_SPM_STS3_WAKEUP_BMSK                             0x4
#define HWIO_APCS_APR0_SAW4_SPM_STS3_WAKEUP_SHFT                             0x2
#define HWIO_APCS_APR0_SAW4_SPM_STS3_WAIT_ACK_BMSK                           0x2
#define HWIO_APCS_APR0_SAW4_SPM_STS3_WAIT_ACK_SHFT                           0x1
#define HWIO_APCS_APR0_SAW4_SPM_STS3_WAIT_REQ_BMSK                           0x1
#define HWIO_APCS_APR0_SAW4_SPM_STS3_WAIT_REQ_SHFT                           0x0

#define HWIO_APCS_APR0_SAW4_CVS_STS_ADDR(x)                           ((x) + 0x00000040)
#define HWIO_APCS_APR0_SAW4_CVS_STS_OFFS                              (0x00000040)
#define HWIO_APCS_APR0_SAW4_CVS_STS_RMSK                              0xffff03ff
#define HWIO_APCS_APR0_SAW4_CVS_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_STS_ADDR(x), HWIO_APCS_APR0_SAW4_CVS_STS_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_STS_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_CVS_STS_CVS_EVENT_BMSK                    0xffff0000
#define HWIO_APCS_APR0_SAW4_CVS_STS_CVS_EVENT_SHFT                          0x10
#define HWIO_APCS_APR0_SAW4_CVS_STS_CVS_BUSY_BMSK                          0x200
#define HWIO_APCS_APR0_SAW4_CVS_STS_CVS_BUSY_SHFT                            0x9
#define HWIO_APCS_APR0_SAW4_CVS_STS_CVS_CMD_ADDR_BMSK                      0x1ff
#define HWIO_APCS_APR0_SAW4_CVS_STS_CVS_CMD_ADDR_SHFT                        0x0

#define HWIO_APCS_APR0_SAW4_CVS_STS2_ADDR(x)                          ((x) + 0x00000044)
#define HWIO_APCS_APR0_SAW4_CVS_STS2_OFFS                             (0x00000044)
#define HWIO_APCS_APR0_SAW4_CVS_STS2_RMSK                             0xffffffff
#define HWIO_APCS_APR0_SAW4_CVS_STS2_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_STS2_ADDR(x), HWIO_APCS_APR0_SAW4_CVS_STS2_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_STS2_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_STS2_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_CVS_STS2_CVS_PWR_CTL_BMSK                 0xffffffff
#define HWIO_APCS_APR0_SAW4_CVS_STS2_CVS_PWR_CTL_SHFT                        0x0

#define HWIO_APCS_APR0_SAW4_CVS_STS3_ADDR(x)                          ((x) + 0x00000048)
#define HWIO_APCS_APR0_SAW4_CVS_STS3_OFFS                             (0x00000048)
#define HWIO_APCS_APR0_SAW4_CVS_STS3_RMSK                               0xf0ffff
#define HWIO_APCS_APR0_SAW4_CVS_STS3_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_STS3_ADDR(x), HWIO_APCS_APR0_SAW4_CVS_STS3_RMSK)
#define HWIO_APCS_APR0_SAW4_CVS_STS3_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_CVS_STS3_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_CVS_STS3_HALT_STATE_BMSK                    0x800000
#define HWIO_APCS_APR0_SAW4_CVS_STS3_HALT_STATE_SHFT                        0x17
#define HWIO_APCS_APR0_SAW4_CVS_STS3_HALT_DONE_BMSK                     0x400000
#define HWIO_APCS_APR0_SAW4_CVS_STS3_HALT_DONE_SHFT                         0x16
#define HWIO_APCS_APR0_SAW4_CVS_STS3_CVS_ACK_BMSK                       0x200000
#define HWIO_APCS_APR0_SAW4_CVS_STS3_CVS_ACK_SHFT                           0x15
#define HWIO_APCS_APR0_SAW4_CVS_STS3_CVS_REQ_BMSK                       0x100000
#define HWIO_APCS_APR0_SAW4_CVS_STS3_CVS_REQ_SHFT                           0x14
#define HWIO_APCS_APR0_SAW4_CVS_STS3_CVS_EVENT2_BMSK                      0xffff
#define HWIO_APCS_APR0_SAW4_CVS_STS3_CVS_EVENT2_SHFT                         0x0

#define HWIO_APCS_APR0_SAW4_VERSION_ADDR(x)                           ((x) + 0x000003d0)
#define HWIO_APCS_APR0_SAW4_VERSION_OFFS                              (0x000003d0)
#define HWIO_APCS_APR0_SAW4_VERSION_RMSK                              0xffffffff
#define HWIO_APCS_APR0_SAW4_VERSION_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_VERSION_ADDR(x), HWIO_APCS_APR0_SAW4_VERSION_RMSK)
#define HWIO_APCS_APR0_SAW4_VERSION_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SAW4_VERSION_ADDR(x), m)
#define HWIO_APCS_APR0_SAW4_VERSION_MAJOR_BMSK                        0xf0000000
#define HWIO_APCS_APR0_SAW4_VERSION_MAJOR_SHFT                              0x1c
#define HWIO_APCS_APR0_SAW4_VERSION_MINOR_BMSK                         0xfff0000
#define HWIO_APCS_APR0_SAW4_VERSION_MINOR_SHFT                              0x10
#define HWIO_APCS_APR0_SAW4_VERSION_STEP_BMSK                             0xffff
#define HWIO_APCS_APR0_SAW4_VERSION_STEP_SHFT                                0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_APR_PWR_CTL
 *--------------------------------------------------------------------------*/

#define APCS_APR0_APR_PWR_CTL_REG_BASE                   (HMSS_PERIPH_BASE      + 0x00046000)
#define APCS_APR0_APR_PWR_CTL_REG_BASE_OFFS              0x00046000

#define HWIO_APCS_APR0_PWR_CTL_ADDR(x)                   ((x) + 0x00000000)
#define HWIO_APCS_APR0_PWR_CTL_OFFS                      (0x00000000)
#define HWIO_APCS_APR0_PWR_CTL_RMSK                      0xa0000005
#define HWIO_APCS_APR0_PWR_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_PWR_CTL_ADDR(x), HWIO_APCS_APR0_PWR_CTL_RMSK)
#define HWIO_APCS_APR0_PWR_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_PWR_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_PWR_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_PWR_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_PWR_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_PWR_CTL_ADDR(x),m,v,HWIO_APCS_APR0_PWR_CTL_IN(x))
#define HWIO_APCS_APR0_PWR_CTL_PMIC_APC_ON_BMSK          0x80000000
#define HWIO_APCS_APR0_PWR_CTL_PMIC_APC_ON_SHFT                0x1f
#define HWIO_APCS_APR0_PWR_CTL_SLP_STATE_BMSK            0x20000000
#define HWIO_APCS_APR0_PWR_CTL_SLP_STATE_SHFT                  0x1d
#define HWIO_APCS_APR0_PWR_CTL_POR_RST_BMSK                     0x4
#define HWIO_APCS_APR0_PWR_CTL_POR_RST_SHFT                     0x2
#define HWIO_APCS_APR0_PWR_CTL_CLAMP_APCPD_BMSK                 0x1
#define HWIO_APCS_APR0_PWR_CTL_CLAMP_APCPD_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_APR_STS
 *--------------------------------------------------------------------------*/

#define APCS_APR0_APR_STS_REG_BASE                                         (HMSS_PERIPH_BASE      + 0x002c6400)
#define APCS_APR0_APR_STS_REG_BASE_OFFS                                    0x002c6400

#define HWIO_APCS_APR0_PGS_RET_STS_ADDR(x)                                 ((x) + 0x00000000)
#define HWIO_APCS_APR0_PGS_RET_STS_OFFS                                    (0x00000000)
#define HWIO_APCS_APR0_PGS_RET_STS_RMSK                                         0x1ff
#define HWIO_APCS_APR0_PGS_RET_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_PGS_RET_STS_ADDR(x), HWIO_APCS_APR0_PGS_RET_STS_RMSK)
#define HWIO_APCS_APR0_PGS_RET_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_PGS_RET_STS_ADDR(x), m)
#define HWIO_APCS_APR0_PGS_RET_STS_APC2_L2_PGS_RET_SLP_BMSK                     0x100
#define HWIO_APCS_APR0_PGS_RET_STS_APC2_L2_PGS_RET_SLP_SHFT                       0x8
#define HWIO_APCS_APR0_PGS_RET_STS_APC2_CPU1_PGS_RET_SLP_BMSK                    0x80
#define HWIO_APCS_APR0_PGS_RET_STS_APC2_CPU1_PGS_RET_SLP_SHFT                     0x7
#define HWIO_APCS_APR0_PGS_RET_STS_APC2_CPU0_PGS_RET_SLP_BMSK                    0x40
#define HWIO_APCS_APR0_PGS_RET_STS_APC2_CPU0_PGS_RET_SLP_SHFT                     0x6
#define HWIO_APCS_APR0_PGS_RET_STS_APC1_L2_PGS_RET_SLP_BMSK                      0x20
#define HWIO_APCS_APR0_PGS_RET_STS_APC1_L2_PGS_RET_SLP_SHFT                       0x5
#define HWIO_APCS_APR0_PGS_RET_STS_APC1_CPU1_PGS_RET_SLP_BMSK                    0x10
#define HWIO_APCS_APR0_PGS_RET_STS_APC1_CPU1_PGS_RET_SLP_SHFT                     0x4
#define HWIO_APCS_APR0_PGS_RET_STS_APC1_CPU0_PGS_RET_SLP_BMSK                     0x8
#define HWIO_APCS_APR0_PGS_RET_STS_APC1_CPU0_PGS_RET_SLP_SHFT                     0x3
#define HWIO_APCS_APR0_PGS_RET_STS_APC0_L2_PGS_RET_SLP_BMSK                       0x4
#define HWIO_APCS_APR0_PGS_RET_STS_APC0_L2_PGS_RET_SLP_SHFT                       0x2
#define HWIO_APCS_APR0_PGS_RET_STS_APC0_CPU1_PGS_RET_SLP_BMSK                     0x2
#define HWIO_APCS_APR0_PGS_RET_STS_APC0_CPU1_PGS_RET_SLP_SHFT                     0x1
#define HWIO_APCS_APR0_PGS_RET_STS_APC0_CPU0_PGS_RET_SLP_BMSK                     0x1
#define HWIO_APCS_APR0_PGS_RET_STS_APC0_CPU0_PGS_RET_SLP_SHFT                     0x0

#define HWIO_APCS_APR0_APM_CTL_STS_ADDR(x)                                 ((x) + 0x00000040)
#define HWIO_APCS_APR0_APM_CTL_STS_OFFS                                    (0x00000040)
#define HWIO_APCS_APR0_APM_CTL_STS_RMSK                                    0xffffffff
#define HWIO_APCS_APR0_APM_CTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_APM_CTL_STS_ADDR(x), HWIO_APCS_APR0_APM_CTL_STS_RMSK)
#define HWIO_APCS_APR0_APM_CTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_APM_CTL_STS_ADDR(x), m)
#define HWIO_APCS_APR0_APM_CTL_STS_PWR_MUX_MODE_BMSK                       0xff000000
#define HWIO_APCS_APR0_APM_CTL_STS_PWR_MUX_MODE_SHFT                             0x18
#define HWIO_APCS_APR0_APM_CTL_STS_TIMER_BMSK                                0xff0000
#define HWIO_APCS_APR0_APM_CTL_STS_TIMER_SHFT                                    0x10
#define HWIO_APCS_APR0_APM_CTL_STS_APC2_APC_GT_MEM_CELL_VMIN_BMSK              0x8000
#define HWIO_APCS_APR0_APM_CTL_STS_APC2_APC_GT_MEM_CELL_VMIN_SHFT                 0xf
#define HWIO_APCS_APR0_APM_CTL_STS_APC1_APC_GT_MEM_CELL_VMIN_BMSK              0x4000
#define HWIO_APCS_APR0_APM_CTL_STS_APC1_APC_GT_MEM_CELL_VMIN_SHFT                 0xe
#define HWIO_APCS_APR0_APM_CTL_STS_APC0_APC_GT_MEM_CELL_VMIN_BMSK              0x2000
#define HWIO_APCS_APR0_APM_CTL_STS_APC0_APC_GT_MEM_CELL_VMIN_SHFT                 0xd
#define HWIO_APCS_APR0_APM_CTL_STS_FORCE_CLK_OFF_BMSK                          0x1c00
#define HWIO_APCS_APR0_APM_CTL_STS_FORCE_CLK_OFF_SHFT                             0xa
#define HWIO_APCS_APR0_APM_CTL_STS_APC2_APC_GT_MX_BMSK                          0x200
#define HWIO_APCS_APR0_APM_CTL_STS_APC2_APC_GT_MX_SHFT                            0x9
#define HWIO_APCS_APR0_APM_CTL_STS_APC1_APC_GT_MX_BMSK                          0x100
#define HWIO_APCS_APR0_APM_CTL_STS_APC1_APC_GT_MX_SHFT                            0x8
#define HWIO_APCS_APR0_APM_CTL_STS_APC0_APC_GT_MX_BMSK                           0x80
#define HWIO_APCS_APR0_APM_CTL_STS_APC0_APC_GT_MX_SHFT                            0x7
#define HWIO_APCS_APR0_APM_CTL_STS_FREEZE_BMSK                                   0x40
#define HWIO_APCS_APR0_APM_CTL_STS_FREEZE_SHFT                                    0x6
#define HWIO_APCS_APR0_APM_CTL_STS_FORCE_CLK_OFF_BIT0_BMSK                       0x20
#define HWIO_APCS_APR0_APM_CTL_STS_FORCE_CLK_OFF_BIT0_SHFT                        0x5
#define HWIO_APCS_APR0_APM_CTL_STS_CUR_FSM_BMSK                                  0x1c
#define HWIO_APCS_APR0_APM_CTL_STS_CUR_FSM_SHFT                                   0x2
#define HWIO_APCS_APR0_APM_CTL_STS_PWR_MUX_SEL_SYNC_D1_BMSK                       0x2
#define HWIO_APCS_APR0_APM_CTL_STS_PWR_MUX_SEL_SYNC_D1_SHFT                       0x1
#define HWIO_APCS_APR0_APM_CTL_STS_PWR_MUX_SEL_SYNC_BMSK                          0x1
#define HWIO_APCS_APR0_APM_CTL_STS_PWR_MUX_SEL_SYNC_SHFT                          0x0

#define HWIO_APCS_APR0_MAS_RET_STS_ADDR(x)                                 ((x) + 0x00000044)
#define HWIO_APCS_APR0_MAS_RET_STS_OFFS                                    (0x00000044)
#define HWIO_APCS_APR0_MAS_RET_STS_RMSK                                         0x1ff
#define HWIO_APCS_APR0_MAS_RET_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_MAS_RET_STS_ADDR(x), HWIO_APCS_APR0_MAS_RET_STS_RMSK)
#define HWIO_APCS_APR0_MAS_RET_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_MAS_RET_STS_ADDR(x), m)
#define HWIO_APCS_APR0_MAS_RET_STS_APC2_L2_MAS_RET_SLP_BMSK                     0x100
#define HWIO_APCS_APR0_MAS_RET_STS_APC2_L2_MAS_RET_SLP_SHFT                       0x8
#define HWIO_APCS_APR0_MAS_RET_STS_APC2_CPU1_MAS_RET_SLP_BMSK                    0x80
#define HWIO_APCS_APR0_MAS_RET_STS_APC2_CPU1_MAS_RET_SLP_SHFT                     0x7
#define HWIO_APCS_APR0_MAS_RET_STS_APC2_CPU0_MAS_RET_SLP_BMSK                    0x40
#define HWIO_APCS_APR0_MAS_RET_STS_APC2_CPU0_MAS_RET_SLP_SHFT                     0x6
#define HWIO_APCS_APR0_MAS_RET_STS_APC1_L2_MAS_RET_SLP_BMSK                      0x20
#define HWIO_APCS_APR0_MAS_RET_STS_APC1_L2_MAS_RET_SLP_SHFT                       0x5
#define HWIO_APCS_APR0_MAS_RET_STS_APC1_CPU1_MAS_RET_SLP_BMSK                    0x10
#define HWIO_APCS_APR0_MAS_RET_STS_APC1_CPU1_MAS_RET_SLP_SHFT                     0x4
#define HWIO_APCS_APR0_MAS_RET_STS_APC1_CPU0_MAS_RET_SLP_BMSK                     0x8
#define HWIO_APCS_APR0_MAS_RET_STS_APC1_CPU0_MAS_RET_SLP_SHFT                     0x3
#define HWIO_APCS_APR0_MAS_RET_STS_APC0_L2_MAS_RET_SLP_BMSK                       0x4
#define HWIO_APCS_APR0_MAS_RET_STS_APC0_L2_MAS_RET_SLP_SHFT                       0x2
#define HWIO_APCS_APR0_MAS_RET_STS_APC0_CPU1_MAS_RET_SLP_BMSK                     0x2
#define HWIO_APCS_APR0_MAS_RET_STS_APC0_CPU1_MAS_RET_SLP_SHFT                     0x1
#define HWIO_APCS_APR0_MAS_RET_STS_APC0_CPU0_MAS_RET_SLP_BMSK                     0x1
#define HWIO_APCS_APR0_MAS_RET_STS_APC0_CPU0_MAS_RET_SLP_SHFT                     0x0

#define HWIO_APCS_APR0_PWR_CTL_STS_ADDR(x)                                 ((x) + 0x00000080)
#define HWIO_APCS_APR0_PWR_CTL_STS_OFFS                                    (0x00000080)
#define HWIO_APCS_APR0_PWR_CTL_STS_RMSK                                    0xffffffff
#define HWIO_APCS_APR0_PWR_CTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_PWR_CTL_STS_ADDR(x), HWIO_APCS_APR0_PWR_CTL_STS_RMSK)
#define HWIO_APCS_APR0_PWR_CTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_PWR_CTL_STS_ADDR(x), m)
#define HWIO_APCS_APR0_PWR_CTL_STS_TBD_BMSK                                0xffffffff
#define HWIO_APCS_APR0_PWR_CTL_STS_TBD_SHFT                                       0x0

#define HWIO_APCS_APR0_SER_STS_ADDR(x)                                     ((x) + 0x00000090)
#define HWIO_APCS_APR0_SER_STS_OFFS                                        (0x00000090)
#define HWIO_APCS_APR0_SER_STS_RMSK                                        0xffffffff
#define HWIO_APCS_APR0_SER_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SER_STS_ADDR(x), HWIO_APCS_APR0_SER_STS_RMSK)
#define HWIO_APCS_APR0_SER_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SER_STS_ADDR(x), m)
#define HWIO_APCS_APR0_SER_STS_RSV_1_BMSK                                  0xffff0000
#define HWIO_APCS_APR0_SER_STS_RSV_1_SHFT                                        0x10
#define HWIO_APCS_APR0_SER_STS_COUNTER_BMSK                                    0xff00
#define HWIO_APCS_APR0_SER_STS_COUNTER_SHFT                                       0x8
#define HWIO_APCS_APR0_SER_STS_RSV_0_BMSK                                        0xfc
#define HWIO_APCS_APR0_SER_STS_RSV_0_SHFT                                         0x2
#define HWIO_APCS_APR0_SER_STS_ANY_4_CLR_BMSK                                     0x2
#define HWIO_APCS_APR0_SER_STS_ANY_4_CLR_SHFT                                     0x1
#define HWIO_APCS_APR0_SER_STS_EN_DLY1_BMSK                                       0x1
#define HWIO_APCS_APR0_SER_STS_EN_DLY1_SHFT                                       0x0

#define HWIO_APCS_APR0_SER_INPUT_STS_ADDR(x)                               ((x) + 0x00000094)
#define HWIO_APCS_APR0_SER_INPUT_STS_OFFS                                  (0x00000094)
#define HWIO_APCS_APR0_SER_INPUT_STS_RMSK                                  0xffffffff
#define HWIO_APCS_APR0_SER_INPUT_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SER_INPUT_STS_ADDR(x), HWIO_APCS_APR0_SER_INPUT_STS_RMSK)
#define HWIO_APCS_APR0_SER_INPUT_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SER_INPUT_STS_ADDR(x), m)
#define HWIO_APCS_APR0_SER_INPUT_STS_IN_SIG_BMSK                           0xffffffff
#define HWIO_APCS_APR0_SER_INPUT_STS_IN_SIG_SHFT                                  0x0

#define HWIO_APCS_APR0_SER_OUTPUT_STS_ADDR(x)                              ((x) + 0x00000098)
#define HWIO_APCS_APR0_SER_OUTPUT_STS_OFFS                                 (0x00000098)
#define HWIO_APCS_APR0_SER_OUTPUT_STS_RMSK                                 0xffffffff
#define HWIO_APCS_APR0_SER_OUTPUT_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SER_OUTPUT_STS_ADDR(x), HWIO_APCS_APR0_SER_OUTPUT_STS_RMSK)
#define HWIO_APCS_APR0_SER_OUTPUT_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SER_OUTPUT_STS_ADDR(x), m)
#define HWIO_APCS_APR0_SER_OUTPUT_STS_OUT_SIG_BMSK                         0xffffffff
#define HWIO_APCS_APR0_SER_OUTPUT_STS_OUT_SIG_SHFT                                0x0

#define HWIO_APCS_APR0_SYSRST_DIAG_STS_ADDR(x)                             ((x) + 0x000000c0)
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_OFFS                                (0x000000c0)
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_RMSK                                       0x7
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SYSRST_DIAG_STS_ADDR(x), HWIO_APCS_APR0_SYSRST_DIAG_STS_RMSK)
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SYSRST_DIAG_STS_ADDR(x), m)
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_APR_G2_BMSK                                0x4
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_APR_G2_SHFT                                0x2
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_APR_G1_BMSK                                0x2
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_APR_G1_SHFT                                0x1
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_APR_G0_BMSK                                0x1
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_APR_G0_SHFT                                0x0

#define HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_ADDR(x)                         ((x) + 0x000000c4)
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_OFFS                            (0x000000c4)
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_RMSK                                 0x1ff
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_ADDR(x), HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_RMSK)
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_ADDR(x), m)
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_APR_SPM_CMD_BMSK                     0x1ff
#define HWIO_APCS_APR0_SYSRST_DIAG_STS_SPM_APR_SPM_CMD_SHFT                       0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_APR_SW_EVENT
 *--------------------------------------------------------------------------*/

#define APCS_APR0_APR_SW_EVENT_REG_BASE                     (HMSS_PERIPH_BASE      + 0x00106000)
#define APCS_APR0_APR_SW_EVENT_REG_BASE_OFFS                0x00106000

#define HWIO_APCS_APR0_SW_SPM_EVENT_ADDR(x)                 ((x) + 0x00000000)
#define HWIO_APCS_APR0_SW_SPM_EVENT_OFFS                    (0x00000000)
#define HWIO_APCS_APR0_SW_SPM_EVENT_RMSK                           0x3
#define HWIO_APCS_APR0_SW_SPM_EVENT_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SW_SPM_EVENT_ADDR(x), HWIO_APCS_APR0_SW_SPM_EVENT_RMSK)
#define HWIO_APCS_APR0_SW_SPM_EVENT_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SW_SPM_EVENT_ADDR(x), m)
#define HWIO_APCS_APR0_SW_SPM_EVENT_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SW_SPM_EVENT_ADDR(x),v)
#define HWIO_APCS_APR0_SW_SPM_EVENT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SW_SPM_EVENT_ADDR(x),m,v,HWIO_APCS_APR0_SW_SPM_EVENT_IN(x))
#define HWIO_APCS_APR0_SW_SPM_EVENT_SPM_SPARE_BMSK                 0x2
#define HWIO_APCS_APR0_SW_SPM_EVENT_SPM_SPARE_SHFT                 0x1
#define HWIO_APCS_APR0_SW_SPM_EVENT_SPM_EVENT_BMSK                 0x1
#define HWIO_APCS_APR0_SW_SPM_EVENT_SPM_EVENT_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_APR_WAR
 *--------------------------------------------------------------------------*/

#define APCS_APR0_APR_WAR_REG_BASE                              (HMSS_PERIPH_BASE      + 0x00146000)
#define APCS_APR0_APR_WAR_REG_BASE_OFFS                         0x00146000

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_APR_DBG
 *--------------------------------------------------------------------------*/

#define APCS_APR0_APR_DBG_REG_BASE                         (HMSS_PERIPH_BASE      + 0x00306000)
#define APCS_APR0_APR_DBG_REG_BASE_OFFS                    0x00306000

#define HWIO_APCS_APR0_EMU_DBG_MODE_MSK_ADDR(x)            ((x) + 0x00000008)
#define HWIO_APCS_APR0_EMU_DBG_MODE_MSK_OFFS               (0x00000008)
#define HWIO_APCS_APR0_EMU_DBG_MODE_MSK_RMSK                 0xffffff
#define HWIO_APCS_APR0_EMU_DBG_MODE_MSK_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_EMU_DBG_MODE_MSK_ADDR(x), HWIO_APCS_APR0_EMU_DBG_MODE_MSK_RMSK)
#define HWIO_APCS_APR0_EMU_DBG_MODE_MSK_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_EMU_DBG_MODE_MSK_ADDR(x), m)
#define HWIO_APCS_APR0_EMU_DBG_MODE_MSK_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_EMU_DBG_MODE_MSK_ADDR(x),v)
#define HWIO_APCS_APR0_EMU_DBG_MODE_MSK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_EMU_DBG_MODE_MSK_ADDR(x),m,v,HWIO_APCS_APR0_EMU_DBG_MODE_MSK_IN(x))

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_DCVS_APR
 *--------------------------------------------------------------------------*/

#define APCS_APR0_DCVS_APR_REG_BASE                                                (HMSS_PERIPH_BASE      + 0x00246600)
#define APCS_APR0_DCVS_APR_REG_BASE_OFFS                                           0x00246600

#define HWIO_APCS_APR0_DCVS_CTL_ADDR(x)                                            ((x) + 0x00000000)
#define HWIO_APCS_APR0_DCVS_CTL_OFFS                                               (0x00000000)
#define HWIO_APCS_APR0_DCVS_CTL_RMSK                                               0x80030001
#define HWIO_APCS_APR0_DCVS_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CTL_ADDR(x), HWIO_APCS_APR0_DCVS_CTL_RMSK)
#define HWIO_APCS_APR0_DCVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CTL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CTL_IN(x))
#define HWIO_APCS_APR0_DCVS_CTL_BUSY_BMSK                                          0x80000000
#define HWIO_APCS_APR0_DCVS_CTL_BUSY_SHFT                                                0x1f
#define HWIO_APCS_APR0_DCVS_CTL_IRQ_EN_BMSK                                           0x20000
#define HWIO_APCS_APR0_DCVS_CTL_IRQ_EN_SHFT                                              0x11
#define HWIO_APCS_APR0_DCVS_CTL_CSM_EN_BMSK                                           0x10000
#define HWIO_APCS_APR0_DCVS_CTL_CSM_EN_SHFT                                              0x10
#define HWIO_APCS_APR0_DCVS_CTL_REQ_BMSK                                                  0x1
#define HWIO_APCS_APR0_DCVS_CTL_REQ_SHFT                                                  0x0

#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x)                                  ((x) + 0x00000004)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_OFFS                                     (0x00000004)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_RMSK                                     0x80000001
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x), HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_RMSK)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_IN(x))
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_IRQ_STS_BMSK                             0x80000000
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_IRQ_STS_SHFT                                   0x1f
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_DONE_BMSK                                       0x1
#define HWIO_APCS_APR0_DCVS_CVS_HALT_DONE_DONE_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_ADDR(x)                               ((x) + 0x00000008)
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_OFFS                                  (0x00000008)
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_RMSK                                         0x7
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_ADDR(x), HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_RMSK)
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_CPR_MODE_STS_BMSK                            0x7
#define HWIO_APCS_APR0_DCVS_CUR_CPR_MODE_STS_CPR_MODE_STS_SHFT                            0x0

#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x)                                  ((x) + 0x00000010)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_OFFS                                     (0x00000010)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_RMSK                                           0xff
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_VLVL_BMSK                                      0xff
#define HWIO_APCS_APR0_DCVS_APM_VMIN_VLVL_VLVL_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x)                                  ((x) + 0x00000014)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_OFFS                                     (0x00000014)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_RMSK                                           0xff
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_VLVL_BMSK                                      0xff
#define HWIO_APCS_APR0_DCVS_ACC_VMIN_VLVL_VLVL_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x)                                  ((x) + 0x00000018)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_OFFS                                     (0x00000018)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_RMSK                                           0xff
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_VLVL_BMSK                                      0xff
#define HWIO_APCS_APR0_DCVS_LDO_HDRM_VLVL_VLVL_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x)                                   ((x) + 0x0000001c)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_OFFS                                      (0x0000001c)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_RMSK                                            0xff
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_VLVL_BMSK                                       0xff
#define HWIO_APCS_APR0_DCVS_LDO_RET_VLVL_VLVL_SHFT                                        0x0

#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x)                                  ((x) + 0x00000020)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_OFFS                                     (0x00000020)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_RMSK                                           0xff
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x), HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_RMSK)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_IN(x))
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_VLVL_BMSK                                      0xff
#define HWIO_APCS_APR0_DCVS_LDO_VMAX_VLVL_VLVL_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x)                              ((x) + 0x00000030)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_OFFS                                 (0x00000030)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_RMSK                                      0x1ff
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_START_ADDR_BMSK                           0x1ff
#define HWIO_APCS_APR0_DCVS_DVS_UP_START_ADDR_START_ADDR_SHFT                             0x0

#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x)                              ((x) + 0x00000034)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_OFFS                                 (0x00000034)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_RMSK                                      0x1ff
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_START_ADDR_BMSK                           0x1ff
#define HWIO_APCS_APR0_DCVS_DVS_DN_START_ADDR_START_ADDR_SHFT                             0x0

#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x)                             ((x) + 0x00000038)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_OFFS                                (0x00000038)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_RMSK                                     0x1ff
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_START_ADDR_BMSK                          0x1ff
#define HWIO_APCS_APR0_DCVS_PRE_SEQ_START_ADDR_START_ADDR_SHFT                            0x0

#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x)                            ((x) + 0x0000003c)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_OFFS                               (0x0000003c)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_RMSK                                    0x1ff
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_START_ADDR_BMSK                         0x1ff
#define HWIO_APCS_APR0_DCVS_POST_SEQ_START_ADDR_START_ADDR_SHFT                           0x0

#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x)                            ((x) + 0x00000040)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_OFFS                               (0x00000040)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_RMSK                                    0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_START_ADDR_BMSK                         0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC0_START_ADDR_START_ADDR_SHFT                           0x0

#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x)                            ((x) + 0x00000044)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_OFFS                               (0x00000044)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_RMSK                                    0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_START_ADDR_BMSK                         0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC1_START_ADDR_START_ADDR_SHFT                           0x0

#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x)                            ((x) + 0x00000048)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_OFFS                               (0x00000048)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_RMSK                                    0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x), HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_RMSK)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_IN(x))
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_START_ADDR_BMSK                         0x1ff
#define HWIO_APCS_APR0_DCVS_DFS_APC2_START_ADDR_START_ADDR_SHFT                           0x0

#define HWIO_APCS_APR0_DCVS_CFG_ADDR(x)                                            ((x) + 0x00000050)
#define HWIO_APCS_APR0_DCVS_CFG_OFFS                                               (0x00000050)
#define HWIO_APCS_APR0_DCVS_CFG_RMSK                                                     0x71
#define HWIO_APCS_APR0_DCVS_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CFG_ADDR(x), HWIO_APCS_APR0_DCVS_CFG_RMSK)
#define HWIO_APCS_APR0_DCVS_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CFG_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CFG_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CFG_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CFG_IN(x))
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC2_BMSK                               0x40
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC2_SHFT                                0x6
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC1_BMSK                               0x20
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC1_SHFT                                0x5
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC0_BMSK                               0x10
#define HWIO_APCS_APR0_DCVS_CFG_LDO_MODE_DISABLE_APC0_SHFT                                0x4
#define HWIO_APCS_APR0_DCVS_CFG_CPR_FEATURE_EN_BMSK                                       0x1
#define HWIO_APCS_APR0_DCVS_CFG_CPR_FEATURE_EN_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x)                                ((x) + 0x00000054)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_OFFS                                   (0x00000054)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_RMSK                                   0xffffffff
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x), HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_RMSK)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_IN(x))
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_CVS_DLY_BMSK                           0xff000000
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_CVS_DLY_SHFT                                 0x18
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_AVS_DLY_BMSK                             0xff0000
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_AVS_DLY_SHFT                                 0x10
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_CPR_DLY_BMSK                               0xff00
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_CPR_DLY_SHFT                                  0x8
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_APM_DLY_BMSK                                 0xff
#define HWIO_APCS_APR0_DCVS_FSM_POST_HS_DLY_APM_DLY_SHFT                                  0x0

#define HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x)                                       ((x) + 0x00000058)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_OFFS                                          (0x00000058)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_RMSK                                           0x7ff07ff
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x), HWIO_APCS_APR0_DCVS_CHKN_FSM_RMSK)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CHKN_FSM_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CHKN_FSM_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CHKN_FSM_IN(x))

#define HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x)                                       ((x) + 0x0000005c)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_OFFS                                          (0x0000005c)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_RMSK                                                0xff
#define HWIO_APCS_APR0_DCVS_CHKN_APR_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x), HWIO_APCS_APR0_DCVS_CHKN_APR_RMSK)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CHKN_APR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CHKN_APR_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CHKN_APR_IN(x))

#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x)                                    ((x) + 0x00000060)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_OFFS                                       (0x00000060)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_RMSK                                              0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ENABLE_BMSK                                       0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_CTL_ENABLE_SHFT                                       0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x)                               ((x) + 0x00000064)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_OFFS                                  (0x00000064)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RMSK                                   0x7ffffff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_PGS_RET_DIS_BMSK                       0x4000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_PGS_RET_DIS_SHFT                            0x1a
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_APM_MODE_BMSK                          0x2000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_APM_MODE_SHFT                               0x19
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ACC_SEL_BMSK                           0x1000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_ACC_SEL_SHFT                                0x18
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_SAFE_LVAL_BMSK                     0xff0000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_SAFE_LVAL_SHFT                         0x10
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_FLOOR_VLVL_BMSK                      0xff00
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_FLOOR_VLVL_SHFT                         0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_CEILING_VLVL_BMSK                      0xff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_RAIL_LVL_RAIL_CEILING_VLVL_SHFT                       0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x)                                ((x) + 0x00000068)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_OFFS                                   (0x00000068)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_RMSK                                   0x7777f773
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_ACC_SEL_BMSK                       0x70000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_ACC_SEL_SHFT                             0x1c
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_CPR_MODE_BMSK                           0x7000000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_CPR_MODE_SHFT                                0x18
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_LDO_MODE_BMSK                            0x700000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_LDO_MODE_SHFT                                0x14
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_LDO_DSBL_MASK_BMSK                        0x70000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_LDO_DSBL_MASK_SHFT                           0x10
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_PMIC_CMD_MASK_BMSK                         0xf000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_PMIC_CMD_MASK_SHFT                            0xc
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_PERF_DN_BMSK                            0x700
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_PERF_DN_SHFT                              0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_PERF_UP_BMSK                             0x70
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_APC_PERF_UP_SHFT                              0x4
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_VOLTAGE_DN_BMSK                               0x2
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_VOLTAGE_DN_SHFT                               0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_VOLTAGE_UP_BMSK                               0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_CTL_VOLTAGE_UP_SHFT                               0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x)                               ((x) + 0x0000006c)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_OFFS                                  (0x0000006c)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_RMSK                                       0x7ff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_CPR_POST_BMSK                         0x400
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_CPR_POST_SHFT                           0xa
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_POST_CHANGE_BMSK                  0x200
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_POST_CHANGE_SHFT                    0x9
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_FREQ_UP_BMSK               0x100
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_FREQ_UP_SHFT                 0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_VOLTAGE_BMSK                0x80
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_VOLTAGE_SHFT                 0x7
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_FREQ_DN_BMSK                0x40
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_CHANGE_FREQ_DN_SHFT                 0x6
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_PRE_CHANGE_BMSK                    0x20
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_SEQ_PRE_CHANGE_SHFT                     0x5
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_FLOOR_BMSK                      0x10
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_FLOOR_SHFT                       0x4
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_CEILING_BMSK                     0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_CEILING_SHFT                     0x3
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_RAIL_BMSK                        0x4
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_UPDATE_RAIL_SHFT                        0x2
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_CPR_PRE_BMSK                            0x2
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_CPR_PRE_SHFT                            0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_ALL_SEQ_BMSK                            0x1
#define HWIO_APCS_APR0_DCVS_AGG_CMD_FSM_SKIP_SKIP_ALL_SEQ_SHFT                            0x0

#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x)                              ((x) + 0x00000070)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_OFFS                                 (0x00000070)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_RMSK                                   0xffffff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_IN(x))
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC2_SAFE_LVAL_BMSK                    0xff0000
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC2_SAFE_LVAL_SHFT                        0x10
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC1_SAFE_LVAL_BMSK                      0xff00
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC1_SAFE_LVAL_SHFT                         0x8
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC0_SAFE_LVAL_BMSK                        0xff
#define HWIO_APCS_APR0_DCVS_AGG_CMD_SAFE_LVAL_APC0_SAFE_LVAL_SHFT                         0x0

#define HWIO_APCS_APR0_DCVS_AGG_STS_ADDR(x)                                        ((x) + 0x00000074)
#define HWIO_APCS_APR0_DCVS_AGG_STS_OFFS                                           (0x00000074)
#define HWIO_APCS_APR0_DCVS_AGG_STS_RMSK                                           0xffffffff
#define HWIO_APCS_APR0_DCVS_AGG_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_STS_ADDR(x), HWIO_APCS_APR0_DCVS_AGG_STS_RMSK)
#define HWIO_APCS_APR0_DCVS_AGG_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_AGG_STS_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_AGG_STS_STATUS_BMSK                                    0xffffffff
#define HWIO_APCS_APR0_DCVS_AGG_STS_STATUS_SHFT                                           0x0

#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x)                                    ((x) + 0x00000080)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_OFFS                                       (0x00000080)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_RMSK                                              0x1
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x), HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_RMSK)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x), m)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x),v)
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_ADDR(x),m,v,HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_IN(x))
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_CVS_EVENT_BMSK                                    0x1
#define HWIO_APCS_APR0_DCVS_CVS_SW_EVNT_CVS_EVENT_SHFT                                    0x0

#define HWIO_APCS_APR0_APM_MODE_ADDR(x)                                            ((x) + 0x000000a0)
#define HWIO_APCS_APR0_APM_MODE_OFFS                                               (0x000000a0)
#define HWIO_APCS_APR0_APM_MODE_RMSK                                                 0x117111
#define HWIO_APCS_APR0_APM_MODE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_APM_MODE_ADDR(x), HWIO_APCS_APR0_APM_MODE_RMSK)
#define HWIO_APCS_APR0_APM_MODE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_APM_MODE_ADDR(x), m)
#define HWIO_APCS_APR0_APM_MODE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_APM_MODE_ADDR(x),v)
#define HWIO_APCS_APR0_APM_MODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_APM_MODE_ADDR(x),m,v,HWIO_APCS_APR0_APM_MODE_IN(x))
#define HWIO_APCS_APR0_APM_MODE_SPARE_BMSK                                           0x100000
#define HWIO_APCS_APR0_APM_MODE_SPARE_SHFT                                               0x14
#define HWIO_APCS_APR0_APM_MODE_DISABLE_FORCE_CLK_BMSK                                0x10000
#define HWIO_APCS_APR0_APM_MODE_DISABLE_FORCE_CLK_SHFT                                   0x10
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC2_EN_BMSK                               0x4000
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC2_EN_SHFT                                  0xe
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC1_EN_BMSK                               0x2000
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC1_EN_SHFT                                  0xd
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC0_EN_BMSK                               0x1000
#define HWIO_APCS_APR0_APM_MODE_HW_AUTO_DET_APC0_EN_SHFT                                  0xc
#define HWIO_APCS_APR0_APM_MODE_APM_VCMP_SEL_BMSK                                       0x100
#define HWIO_APCS_APR0_APM_MODE_APM_VCMP_SEL_SHFT                                         0x8
#define HWIO_APCS_APR0_APM_MODE_SW_PWR_MUX_APCC_SEL_BMSK                                 0x10
#define HWIO_APCS_APR0_APM_MODE_SW_PWR_MUX_APCC_SEL_SHFT                                  0x4
#define HWIO_APCS_APR0_APM_MODE_SW_HW_MODE_SEL_BMSK                                       0x1
#define HWIO_APCS_APR0_APM_MODE_SW_HW_MODE_SEL_SHFT                                       0x0

#define HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x)                                        ((x) + 0x000000a4)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_OFFS                                           (0x000000a4)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_RMSK                                                  0x1
#define HWIO_APCS_APR0_RAIL_ACC_SEL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x), HWIO_APCS_APR0_RAIL_ACC_SEL_RMSK)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x), m)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x),v)
#define HWIO_APCS_APR0_RAIL_ACC_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_RAIL_ACC_SEL_ADDR(x),m,v,HWIO_APCS_APR0_RAIL_ACC_SEL_IN(x))
#define HWIO_APCS_APR0_RAIL_ACC_SEL_RAIL_ACC_SEL_BMSK                                     0x1
#define HWIO_APCS_APR0_RAIL_ACC_SEL_RAIL_ACC_SEL_SHFT                                     0x0

#define HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x)                                       ((x) + 0x000000a8)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_OFFS                                          (0x000000a8)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RMSK                                          0xffffff01
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x), HWIO_APCS_APR0_MEGA_RAIL_CTL_RMSK)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_MEGA_RAIL_CTL_ADDR(x),m,v,HWIO_APCS_APR0_MEGA_RAIL_CTL_IN(x))
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_SAFE_LVAL_BMSK                           0xff000000
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_SAFE_LVAL_SHFT                                 0x18
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_FLOOR_VLVL_BMSK                            0xff0000
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_FLOOR_VLVL_SHFT                                0x10
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_CEIL_VLVL_BMSK                               0xff00
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_RAIL_CEIL_VLVL_SHFT                                  0x8
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_MEGA_RAIL_MODE_BMSK                                  0x1
#define HWIO_APCS_APR0_MEGA_RAIL_CTL_MEGA_RAIL_MODE_SHFT                                  0x0

#define HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x)                                        ((x) + 0x000000ac)
#define HWIO_APCS_APR0_LDO_VREF_ACC_OFFS                                           (0x000000ac)
#define HWIO_APCS_APR0_LDO_VREF_ACC_RMSK                                                 0x7f
#define HWIO_APCS_APR0_LDO_VREF_ACC_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x), HWIO_APCS_APR0_LDO_VREF_ACC_RMSK)
#define HWIO_APCS_APR0_LDO_VREF_ACC_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x), m)
#define HWIO_APCS_APR0_LDO_VREF_ACC_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x),v)
#define HWIO_APCS_APR0_LDO_VREF_ACC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_LDO_VREF_ACC_ADDR(x),m,v,HWIO_APCS_APR0_LDO_VREF_ACC_IN(x))
#define HWIO_APCS_APR0_LDO_VREF_ACC_VREF_ACC_BMSK                                        0x7f
#define HWIO_APCS_APR0_LDO_VREF_ACC_VREF_ACC_SHFT                                         0x0

#define HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x)                                          ((x) + 0x000000b0)
#define HWIO_APCS_APR0_ACC_CTL_EN_OFFS                                             (0x000000b0)
#define HWIO_APCS_APR0_ACC_CTL_EN_RMSK                                                    0x1
#define HWIO_APCS_APR0_ACC_CTL_EN_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x), HWIO_APCS_APR0_ACC_CTL_EN_RMSK)
#define HWIO_APCS_APR0_ACC_CTL_EN_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x), m)
#define HWIO_APCS_APR0_ACC_CTL_EN_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x),v)
#define HWIO_APCS_APR0_ACC_CTL_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_ACC_CTL_EN_ADDR(x),m,v,HWIO_APCS_APR0_ACC_CTL_EN_IN(x))
#define HWIO_APCS_APR0_ACC_CTL_EN_ENABLE_BMSK                                             0x1
#define HWIO_APCS_APR0_ACC_CTL_EN_ENABLE_SHFT                                             0x0

#define HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x)                                         ((x) + 0x000000b4)
#define HWIO_APCS_APR0_ACC_CTL_DLY_OFFS                                            (0x000000b4)
#define HWIO_APCS_APR0_ACC_CTL_DLY_RMSK                                            0xffffffff
#define HWIO_APCS_APR0_ACC_CTL_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x), HWIO_APCS_APR0_ACC_CTL_DLY_RMSK)
#define HWIO_APCS_APR0_ACC_CTL_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_ACC_CTL_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_ACC_CTL_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_ACC_CTL_DLY_ADDR(x),m,v,HWIO_APCS_APR0_ACC_CTL_DLY_IN(x))
#define HWIO_APCS_APR0_ACC_CTL_DLY_VREF_TGT_DLY_BMSK                               0xff000000
#define HWIO_APCS_APR0_ACC_CTL_DLY_VREF_TGT_DLY_SHFT                                     0x18
#define HWIO_APCS_APR0_ACC_CTL_DLY_ACC_SEL_DLY_BMSK                                  0xff0000
#define HWIO_APCS_APR0_ACC_CTL_DLY_ACC_SEL_DLY_SHFT                                      0x10
#define HWIO_APCS_APR0_ACC_CTL_DLY_SWITCH_DLY_BMSK                                     0xff00
#define HWIO_APCS_APR0_ACC_CTL_DLY_SWITCH_DLY_SHFT                                        0x8
#define HWIO_APCS_APR0_ACC_CTL_DLY_VREF_ACC_DLY_BMSK                                     0xff
#define HWIO_APCS_APR0_ACC_CTL_DLY_VREF_ACC_DLY_SHFT                                      0x0

#define HWIO_APCS_APR0_ACC_CTL_STS_ADDR(x)                                         ((x) + 0x000000b8)
#define HWIO_APCS_APR0_ACC_CTL_STS_OFFS                                            (0x000000b8)
#define HWIO_APCS_APR0_ACC_CTL_STS_RMSK                                            0xffffffff
#define HWIO_APCS_APR0_ACC_CTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_STS_ADDR(x), HWIO_APCS_APR0_ACC_CTL_STS_RMSK)
#define HWIO_APCS_APR0_ACC_CTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_ACC_CTL_STS_ADDR(x), m)
#define HWIO_APCS_APR0_ACC_CTL_STS_STATUS_BMSK                                     0xffffffff
#define HWIO_APCS_APR0_ACC_CTL_STS_STATUS_SHFT                                            0x0

#define HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x)                                         ((x) + 0x000000c0)
#define HWIO_APCS_APR0_AVM_AGG_CTL_OFFS                                            (0x000000c0)
#define HWIO_APCS_APR0_AVM_AGG_CTL_RMSK                                            0xffff00ff
#define HWIO_APCS_APR0_AVM_AGG_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x), HWIO_APCS_APR0_AVM_AGG_CTL_RMSK)
#define HWIO_APCS_APR0_AVM_AGG_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_AGG_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_AGG_CTL_ADDR(x),m,v,HWIO_APCS_APR0_AVM_AGG_CTL_IN(x))
#define HWIO_APCS_APR0_AVM_AGG_CTL_DN_STEP_SIZE_BMSK                               0xff000000
#define HWIO_APCS_APR0_AVM_AGG_CTL_DN_STEP_SIZE_SHFT                                     0x18
#define HWIO_APCS_APR0_AVM_AGG_CTL_UP_STEP_SIZE_BMSK                                 0xff0000
#define HWIO_APCS_APR0_AVM_AGG_CTL_UP_STEP_SIZE_SHFT                                     0x10
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_DN_IRPT_EN_BMSK                                  0x80
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_DN_IRPT_EN_SHFT                                   0x7
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_UP_IRPT_EN_BMSK                                  0x40
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_UP_IRPT_EN_SHFT                                   0x6
#define HWIO_APCS_APR0_AVM_AGG_CTL_LDO_DN_IRPT_EN_BMSK                                   0x20
#define HWIO_APCS_APR0_AVM_AGG_CTL_LDO_DN_IRPT_EN_SHFT                                    0x5
#define HWIO_APCS_APR0_AVM_AGG_CTL_LDO_UP_IRPT_EN_BMSK                                   0x10
#define HWIO_APCS_APR0_AVM_AGG_CTL_LDO_UP_IRPT_EN_SHFT                                    0x4
#define HWIO_APCS_APR0_AVM_AGG_CTL_DN_ERR_IRPT_EN_BMSK                                    0x8
#define HWIO_APCS_APR0_AVM_AGG_CTL_DN_ERR_IRPT_EN_SHFT                                    0x3
#define HWIO_APCS_APR0_AVM_AGG_CTL_UP_ERR_IRPT_EN_BMSK                                    0x4
#define HWIO_APCS_APR0_AVM_AGG_CTL_UP_ERR_IRPT_EN_SHFT                                    0x2
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_MODE_BMSK                                         0x2
#define HWIO_APCS_APR0_AVM_AGG_CTL_RAIL_MODE_SHFT                                         0x1
#define HWIO_APCS_APR0_AVM_AGG_CTL_EN_BMSK                                                0x1
#define HWIO_APCS_APR0_AVM_AGG_CTL_EN_SHFT                                                0x0

#define HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x)                                         ((x) + 0x000000c4)
#define HWIO_APCS_APR0_AVM_AGG_DLY_OFFS                                            (0x000000c4)
#define HWIO_APCS_APR0_AVM_AGG_DLY_RMSK                                               0x3ff1f
#define HWIO_APCS_APR0_AVM_AGG_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x), HWIO_APCS_APR0_AVM_AGG_DLY_RMSK)
#define HWIO_APCS_APR0_AVM_AGG_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_AGG_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_AGG_DLY_ADDR(x),m,v,HWIO_APCS_APR0_AVM_AGG_DLY_IN(x))
#define HWIO_APCS_APR0_AVM_AGG_DLY_DLY_BMSK                                           0x3ff00
#define HWIO_APCS_APR0_AVM_AGG_DLY_DLY_SHFT                                               0x8
#define HWIO_APCS_APR0_AVM_AGG_DLY_CLK_DIV_BMSK                                          0x1f
#define HWIO_APCS_APR0_AVM_AGG_DLY_CLK_DIV_SHFT                                           0x0

#define HWIO_APCS_APR0_AVM_AGG_STS_ADDR(x)                                         ((x) + 0x000000c8)
#define HWIO_APCS_APR0_AVM_AGG_STS_OFFS                                            (0x000000c8)
#define HWIO_APCS_APR0_AVM_AGG_STS_RMSK                                            0xffffffff
#define HWIO_APCS_APR0_AVM_AGG_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_STS_ADDR(x), HWIO_APCS_APR0_AVM_AGG_STS_RMSK)
#define HWIO_APCS_APR0_AVM_AGG_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_AGG_STS_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_AGG_STS_STATUS_BMSK                                     0xffffffff
#define HWIO_APCS_APR0_AVM_AGG_STS_STATUS_SHFT                                            0x0

#define HWIO_APCS_APR0_AVM_EVENT_STS_ADDR(x)                                       ((x) + 0x000000cc)
#define HWIO_APCS_APR0_AVM_EVENT_STS_OFFS                                          (0x000000cc)
#define HWIO_APCS_APR0_AVM_EVENT_STS_RMSK                                             0x7777f
#define HWIO_APCS_APR0_AVM_EVENT_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_EVENT_STS_ADDR(x), HWIO_APCS_APR0_AVM_EVENT_STS_RMSK)
#define HWIO_APCS_APR0_AVM_EVENT_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_EVENT_STS_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_DN_EVENT_BMSK                               0x40000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_DN_EVENT_SHFT                                  0x12
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_DN_EVENT_BMSK                               0x20000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_DN_EVENT_SHFT                                  0x11
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_DN_EVENT_BMSK                               0x10000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_DN_EVENT_SHFT                                  0x10
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_UP_EVENT_BMSK                                0x4000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_UP_EVENT_SHFT                                   0xe
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_UP_EVENT_BMSK                                0x2000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_UP_EVENT_SHFT                                   0xd
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_UP_EVENT_BMSK                                0x1000
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_UP_EVENT_SHFT                                   0xc
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_LDO_DN_EVENT_BMSK                             0x400
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_LDO_DN_EVENT_SHFT                               0xa
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_LDO_DN_EVENT_BMSK                             0x200
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_LDO_DN_EVENT_SHFT                               0x9
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_LDO_DN_EVENT_BMSK                             0x100
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_LDO_DN_EVENT_SHFT                               0x8
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_LDO_UP_EVENT_BMSK                              0x40
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC2_LDO_UP_EVENT_SHFT                               0x6
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_LDO_UP_EVENT_BMSK                              0x20
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC1_LDO_UP_EVENT_SHFT                               0x5
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_LDO_UP_EVENT_BMSK                              0x10
#define HWIO_APCS_APR0_AVM_EVENT_STS_APC0_LDO_UP_EVENT_SHFT                               0x4
#define HWIO_APCS_APR0_AVM_EVENT_STS_RAIL_DN_EVENT_BMSK                                   0x8
#define HWIO_APCS_APR0_AVM_EVENT_STS_RAIL_DN_EVENT_SHFT                                   0x3
#define HWIO_APCS_APR0_AVM_EVENT_STS_RAIL_UP_EVENT_BMSK                                   0x4
#define HWIO_APCS_APR0_AVM_EVENT_STS_RAIL_UP_EVENT_SHFT                                   0x2
#define HWIO_APCS_APR0_AVM_EVENT_STS_DN_ERR_EVENT_BMSK                                    0x2
#define HWIO_APCS_APR0_AVM_EVENT_STS_DN_ERR_EVENT_SHFT                                    0x1
#define HWIO_APCS_APR0_AVM_EVENT_STS_UP_ERR_EVENT_BMSK                                    0x1
#define HWIO_APCS_APR0_AVM_EVENT_STS_UP_ERR_EVENT_SHFT                                    0x0

#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_ADDR(x)                              ((x) + 0x000000d0)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_OFFS                                 (0x000000d0)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_RMSK                                        0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_ACK_BMSK                                    0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_BHS_ACK_SHFT                                    0x0

#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_ADDR(x)                             ((x) + 0x000000d4)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_OFFS                                (0x000000d4)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_RMSK                                       0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_DONE_BMSK                                  0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_BHS_DONE_SHFT                                  0x0

#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_ADDR(x)                              ((x) + 0x000000d8)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_OFFS                                 (0x000000d8)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_RMSK                                        0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_ACK_BMSK                                    0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_ACK_CMD_LDO_ACK_SHFT                                    0x0

#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_ADDR(x)                             ((x) + 0x000000dc)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_OFFS                                (0x000000dc)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_RMSK                                       0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_DONE_BMSK                                  0x1
#define HWIO_APCS_APR0_AVM_AGG_SW_DONE_CMD_LDO_DONE_SHFT                                  0x0

#define HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x)                                       ((x) + 0x000000e0)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_OFFS                                          (0x000000e0)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_RMSK                                                0x73
#define HWIO_APCS_APR0_AVM_APC0_VOTE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x), HWIO_APCS_APR0_AVM_APC0_VOTE_RMSK)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_APC0_VOTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_APC0_VOTE_ADDR(x),m,v,HWIO_APCS_APR0_AVM_APC0_VOTE_IN(x))
#define HWIO_APCS_APR0_AVM_APC0_VOTE_PWR_STATE_THRESHOLD_BMSK                            0x70
#define HWIO_APCS_APR0_AVM_APC0_VOTE_PWR_STATE_THRESHOLD_SHFT                             0x4
#define HWIO_APCS_APR0_AVM_APC0_VOTE_VOTE_SLP_EN_BMSK                                     0x2
#define HWIO_APCS_APR0_AVM_APC0_VOTE_VOTE_SLP_EN_SHFT                                     0x1
#define HWIO_APCS_APR0_AVM_APC0_VOTE_VOTE_EN_BMSK                                         0x1
#define HWIO_APCS_APR0_AVM_APC0_VOTE_VOTE_EN_SHFT                                         0x0

#define HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x)                                       ((x) + 0x000000e4)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_OFFS                                          (0x000000e4)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_RMSK                                                0x73
#define HWIO_APCS_APR0_AVM_APC1_VOTE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x), HWIO_APCS_APR0_AVM_APC1_VOTE_RMSK)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_APC1_VOTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_APC1_VOTE_ADDR(x),m,v,HWIO_APCS_APR0_AVM_APC1_VOTE_IN(x))
#define HWIO_APCS_APR0_AVM_APC1_VOTE_PWR_STATE_THRESHOLD_BMSK                            0x70
#define HWIO_APCS_APR0_AVM_APC1_VOTE_PWR_STATE_THRESHOLD_SHFT                             0x4
#define HWIO_APCS_APR0_AVM_APC1_VOTE_VOTE_SLP_EN_BMSK                                     0x2
#define HWIO_APCS_APR0_AVM_APC1_VOTE_VOTE_SLP_EN_SHFT                                     0x1
#define HWIO_APCS_APR0_AVM_APC1_VOTE_VOTE_EN_BMSK                                         0x1
#define HWIO_APCS_APR0_AVM_APC1_VOTE_VOTE_EN_SHFT                                         0x0

#define HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x)                                       ((x) + 0x000000e8)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_OFFS                                          (0x000000e8)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_RMSK                                                0x73
#define HWIO_APCS_APR0_AVM_APC2_VOTE_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x), HWIO_APCS_APR0_AVM_APC2_VOTE_RMSK)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_APC2_VOTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_APC2_VOTE_ADDR(x),m,v,HWIO_APCS_APR0_AVM_APC2_VOTE_IN(x))
#define HWIO_APCS_APR0_AVM_APC2_VOTE_PWR_STATE_THRESHOLD_BMSK                            0x70
#define HWIO_APCS_APR0_AVM_APC2_VOTE_PWR_STATE_THRESHOLD_SHFT                             0x4
#define HWIO_APCS_APR0_AVM_APC2_VOTE_VOTE_SLP_EN_BMSK                                     0x2
#define HWIO_APCS_APR0_AVM_APC2_VOTE_VOTE_SLP_EN_SHFT                                     0x1
#define HWIO_APCS_APR0_AVM_APC2_VOTE_VOTE_EN_BMSK                                         0x1
#define HWIO_APCS_APR0_AVM_APC2_VOTE_VOTE_EN_SHFT                                         0x0

#define HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x)                                         ((x) + 0x000000f0)
#define HWIO_APCS_APR0_AVM_IRQ_STS_OFFS                                            (0x000000f0)
#define HWIO_APCS_APR0_AVM_IRQ_STS_RMSK                                                 0x77f
#define HWIO_APCS_APR0_AVM_IRQ_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x), HWIO_APCS_APR0_AVM_IRQ_STS_RMSK)
#define HWIO_APCS_APR0_AVM_IRQ_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x), m)
#define HWIO_APCS_APR0_AVM_IRQ_STS_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x),v)
#define HWIO_APCS_APR0_AVM_IRQ_STS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_AVM_IRQ_STS_ADDR(x),m,v,HWIO_APCS_APR0_AVM_IRQ_STS_IN(x))
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC2_LDO_DN_EVENT_BMSK                               0x400
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC2_LDO_DN_EVENT_SHFT                                 0xa
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC1_LDO_DN_EVENT_BMSK                               0x200
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC1_LDO_DN_EVENT_SHFT                                 0x9
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC0_LDO_DN_EVENT_BMSK                               0x100
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC0_LDO_DN_EVENT_SHFT                                 0x8
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC2_LDO_UP_EVENT_BMSK                                0x40
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC2_LDO_UP_EVENT_SHFT                                 0x6
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC1_LDO_UP_EVENT_BMSK                                0x20
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC1_LDO_UP_EVENT_SHFT                                 0x5
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC0_LDO_UP_EVENT_BMSK                                0x10
#define HWIO_APCS_APR0_AVM_IRQ_STS_APC0_LDO_UP_EVENT_SHFT                                 0x4
#define HWIO_APCS_APR0_AVM_IRQ_STS_RAIL_DN_EVENT_BMSK                                     0x8
#define HWIO_APCS_APR0_AVM_IRQ_STS_RAIL_DN_EVENT_SHFT                                     0x3
#define HWIO_APCS_APR0_AVM_IRQ_STS_RAIL_UP_EVENT_BMSK                                     0x4
#define HWIO_APCS_APR0_AVM_IRQ_STS_RAIL_UP_EVENT_SHFT                                     0x2
#define HWIO_APCS_APR0_AVM_IRQ_STS_DN_ERR_EVENT_BMSK                                      0x2
#define HWIO_APCS_APR0_AVM_IRQ_STS_DN_ERR_EVENT_SHFT                                      0x1
#define HWIO_APCS_APR0_AVM_IRQ_STS_UP_ERR_EVENT_BMSK                                      0x1
#define HWIO_APCS_APR0_AVM_IRQ_STS_UP_ERR_EVENT_SHFT                                      0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APR0_APR_CFG
 *--------------------------------------------------------------------------*/

#define APCS_APR0_APR_CFG_REG_BASE                                   (HMSS_PERIPH_BASE      + 0x00286000)
#define APCS_APR0_APR_CFG_REG_BASE_OFFS                              0x00286000

#define HWIO_APCS_APR0_PWR_GATE_DLY0_ADDR(x)                         ((x) + 0x00000000)
#define HWIO_APCS_APR0_PWR_GATE_DLY0_OFFS                            (0x00000000)
#define HWIO_APCS_APR0_PWR_GATE_DLY0_RMSK                            0x1f1fff3f
#define HWIO_APCS_APR0_PWR_GATE_DLY0_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_PWR_GATE_DLY0_ADDR(x), HWIO_APCS_APR0_PWR_GATE_DLY0_RMSK)
#define HWIO_APCS_APR0_PWR_GATE_DLY0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_PWR_GATE_DLY0_ADDR(x), m)
#define HWIO_APCS_APR0_PWR_GATE_DLY0_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_PWR_GATE_DLY0_ADDR(x),v)
#define HWIO_APCS_APR0_PWR_GATE_DLY0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_PWR_GATE_DLY0_ADDR(x),m,v,HWIO_APCS_APR0_PWR_GATE_DLY0_IN(x))
#define HWIO_APCS_APR0_PWR_GATE_DLY0_HS_EN1_DLY_BMSK                 0x1f000000
#define HWIO_APCS_APR0_PWR_GATE_DLY0_HS_EN1_DLY_SHFT                       0x18
#define HWIO_APCS_APR0_PWR_GATE_DLY0_HS_EN0_DLY_BMSK                   0x1f0000
#define HWIO_APCS_APR0_PWR_GATE_DLY0_HS_EN0_DLY_SHFT                       0x10
#define HWIO_APCS_APR0_PWR_GATE_DLY0_VREF_SEL_DLY_BMSK                   0xff00
#define HWIO_APCS_APR0_PWR_GATE_DLY0_VREF_SEL_DLY_SHFT                      0x8
#define HWIO_APCS_APR0_PWR_GATE_DLY0_HS_EN_REST_DLY_BMSK                   0x3f
#define HWIO_APCS_APR0_PWR_GATE_DLY0_HS_EN_REST_DLY_SHFT                    0x0

#define HWIO_APCS_APR0_PWR_GATE_DLY1_ADDR(x)                         ((x) + 0x00000004)
#define HWIO_APCS_APR0_PWR_GATE_DLY1_OFFS                            (0x00000004)
#define HWIO_APCS_APR0_PWR_GATE_DLY1_RMSK                              0x3f0fff
#define HWIO_APCS_APR0_PWR_GATE_DLY1_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_PWR_GATE_DLY1_ADDR(x), HWIO_APCS_APR0_PWR_GATE_DLY1_RMSK)
#define HWIO_APCS_APR0_PWR_GATE_DLY1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_PWR_GATE_DLY1_ADDR(x), m)
#define HWIO_APCS_APR0_PWR_GATE_DLY1_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_PWR_GATE_DLY1_ADDR(x),v)
#define HWIO_APCS_APR0_PWR_GATE_DLY1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_PWR_GATE_DLY1_ADDR(x),m,v,HWIO_APCS_APR0_PWR_GATE_DLY1_IN(x))
#define HWIO_APCS_APR0_PWR_GATE_DLY1_LDO_BYP_DLY_BMSK                  0x3f0000
#define HWIO_APCS_APR0_PWR_GATE_DLY1_LDO_BYP_DLY_SHFT                      0x10
#define HWIO_APCS_APR0_PWR_GATE_DLY1_LDO_PD_DLY_BMSK                      0xf00
#define HWIO_APCS_APR0_PWR_GATE_DLY1_LDO_PD_DLY_SHFT                        0x8
#define HWIO_APCS_APR0_PWR_GATE_DLY1_PC_HS_EN_DLY_BMSK                     0xff
#define HWIO_APCS_APR0_PWR_GATE_DLY1_PC_HS_EN_DLY_SHFT                      0x0

#define HWIO_APCS_APR0_APM_MODE_DLY0_ADDR(x)                         ((x) + 0x00000040)
#define HWIO_APCS_APR0_APM_MODE_DLY0_OFFS                            (0x00000040)
#define HWIO_APCS_APR0_APM_MODE_DLY0_RMSK                            0xffffffff
#define HWIO_APCS_APR0_APM_MODE_DLY0_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_APM_MODE_DLY0_ADDR(x), HWIO_APCS_APR0_APM_MODE_DLY0_RMSK)
#define HWIO_APCS_APR0_APM_MODE_DLY0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_APM_MODE_DLY0_ADDR(x), m)
#define HWIO_APCS_APR0_APM_MODE_DLY0_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_APM_MODE_DLY0_ADDR(x),v)
#define HWIO_APCS_APR0_APM_MODE_DLY0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_APM_MODE_DLY0_ADDR(x),m,v,HWIO_APCS_APR0_APM_MODE_DLY0_IN(x))
#define HWIO_APCS_APR0_APM_MODE_DLY0_HALT_CLK_DLY_BMSK               0xff000000
#define HWIO_APCS_APR0_APM_MODE_DLY0_HALT_CLK_DLY_SHFT                     0x18
#define HWIO_APCS_APR0_APM_MODE_DLY0_HYST_CNT_BMSK                     0xff0000
#define HWIO_APCS_APR0_APM_MODE_DLY0_HYST_CNT_SHFT                         0x10
#define HWIO_APCS_APR0_APM_MODE_DLY0_RESUME_CLK_DLY_BMSK                 0xff00
#define HWIO_APCS_APR0_APM_MODE_DLY0_RESUME_CLK_DLY_SHFT                    0x8
#define HWIO_APCS_APR0_APM_MODE_DLY0_SEL_SWITCH_DLY_BMSK                   0xff
#define HWIO_APCS_APR0_APM_MODE_DLY0_SEL_SWITCH_DLY_SHFT                    0x0

#define HWIO_APCS_APR0_APM_MODE_DLY1_ADDR(x)                         ((x) + 0x00000044)
#define HWIO_APCS_APR0_APM_MODE_DLY1_OFFS                            (0x00000044)
#define HWIO_APCS_APR0_APM_MODE_DLY1_RMSK                                  0xff
#define HWIO_APCS_APR0_APM_MODE_DLY1_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_APM_MODE_DLY1_ADDR(x), HWIO_APCS_APR0_APM_MODE_DLY1_RMSK)
#define HWIO_APCS_APR0_APM_MODE_DLY1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_APM_MODE_DLY1_ADDR(x), m)
#define HWIO_APCS_APR0_APM_MODE_DLY1_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_APM_MODE_DLY1_ADDR(x),v)
#define HWIO_APCS_APR0_APM_MODE_DLY1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_APM_MODE_DLY1_ADDR(x),m,v,HWIO_APCS_APR0_APM_MODE_DLY1_IN(x))
#define HWIO_APCS_APR0_APM_MODE_DLY1_POST_HALT_CLK_DLY_BMSK                0xff
#define HWIO_APCS_APR0_APM_MODE_DLY1_POST_HALT_CLK_DLY_SHFT                 0x0

#define HWIO_APCS_APR0_MAS_DLY0_ADDR(x)                              ((x) + 0x00000048)
#define HWIO_APCS_APR0_MAS_DLY0_OFFS                                 (0x00000048)
#define HWIO_APCS_APR0_MAS_DLY0_RMSK                                   0x3f3f3f
#define HWIO_APCS_APR0_MAS_DLY0_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_MAS_DLY0_ADDR(x), HWIO_APCS_APR0_MAS_DLY0_RMSK)
#define HWIO_APCS_APR0_MAS_DLY0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_MAS_DLY0_ADDR(x), m)
#define HWIO_APCS_APR0_MAS_DLY0_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_MAS_DLY0_ADDR(x),v)
#define HWIO_APCS_APR0_MAS_DLY0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_MAS_DLY0_ADDR(x),m,v,HWIO_APCS_APR0_MAS_DLY0_IN(x))
#define HWIO_APCS_APR0_MAS_DLY0_RET_BMSK                               0x3f0000
#define HWIO_APCS_APR0_MAS_DLY0_RET_SHFT                                   0x10
#define HWIO_APCS_APR0_MAS_DLY0_SEL_BMSK                                 0x3f00
#define HWIO_APCS_APR0_MAS_DLY0_SEL_SHFT                                    0x8
#define HWIO_APCS_APR0_MAS_DLY0_CLAMP_BMSK                                 0x3f
#define HWIO_APCS_APR0_MAS_DLY0_CLAMP_SHFT                                  0x0

#define HWIO_APCS_APR0_MAS_DLY1_ADDR(x)                              ((x) + 0x0000004c)
#define HWIO_APCS_APR0_MAS_DLY1_OFFS                                 (0x0000004c)
#define HWIO_APCS_APR0_MAS_DLY1_RMSK                                   0x3f3f3f
#define HWIO_APCS_APR0_MAS_DLY1_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_MAS_DLY1_ADDR(x), HWIO_APCS_APR0_MAS_DLY1_RMSK)
#define HWIO_APCS_APR0_MAS_DLY1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_MAS_DLY1_ADDR(x), m)
#define HWIO_APCS_APR0_MAS_DLY1_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_MAS_DLY1_ADDR(x),v)
#define HWIO_APCS_APR0_MAS_DLY1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_MAS_DLY1_ADDR(x),m,v,HWIO_APCS_APR0_MAS_DLY1_IN(x))
#define HWIO_APCS_APR0_MAS_DLY1_ENF1_BMSK                              0x3f0000
#define HWIO_APCS_APR0_MAS_DLY1_ENF1_SHFT                                  0x10
#define HWIO_APCS_APR0_MAS_DLY1_ENF0_BMSK                                0x3f00
#define HWIO_APCS_APR0_MAS_DLY1_ENF0_SHFT                                   0x8
#define HWIO_APCS_APR0_MAS_DLY1_ENR_BMSK                                   0x3f
#define HWIO_APCS_APR0_MAS_DLY1_ENR_SHFT                                    0x0

#define HWIO_APCS_APR0_SER_EN_ADDR(x)                                ((x) + 0x00000080)
#define HWIO_APCS_APR0_SER_EN_OFFS                                   (0x00000080)
#define HWIO_APCS_APR0_SER_EN_RMSK                                          0x1
#define HWIO_APCS_APR0_SER_EN_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SER_EN_ADDR(x), HWIO_APCS_APR0_SER_EN_RMSK)
#define HWIO_APCS_APR0_SER_EN_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SER_EN_ADDR(x), m)
#define HWIO_APCS_APR0_SER_EN_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SER_EN_ADDR(x),v)
#define HWIO_APCS_APR0_SER_EN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SER_EN_ADDR(x),m,v,HWIO_APCS_APR0_SER_EN_IN(x))
#define HWIO_APCS_APR0_SER_EN_ENABLE_BMSK                                   0x1
#define HWIO_APCS_APR0_SER_EN_ENABLE_SHFT                                   0x0

#define HWIO_APCS_APR0_SER_DLY_ADDR(x)                               ((x) + 0x00000084)
#define HWIO_APCS_APR0_SER_DLY_OFFS                                  (0x00000084)
#define HWIO_APCS_APR0_SER_DLY_RMSK                                  0xffffffff
#define HWIO_APCS_APR0_SER_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SER_DLY_ADDR(x), HWIO_APCS_APR0_SER_DLY_RMSK)
#define HWIO_APCS_APR0_SER_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SER_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_SER_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SER_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_SER_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SER_DLY_ADDR(x),m,v,HWIO_APCS_APR0_SER_DLY_IN(x))
#define HWIO_APCS_APR0_SER_DLY_DELAY_3_BMSK                          0xff000000
#define HWIO_APCS_APR0_SER_DLY_DELAY_3_SHFT                                0x18
#define HWIO_APCS_APR0_SER_DLY_DELAY_2_BMSK                            0xff0000
#define HWIO_APCS_APR0_SER_DLY_DELAY_2_SHFT                                0x10
#define HWIO_APCS_APR0_SER_DLY_DELAY_1_BMSK                              0xff00
#define HWIO_APCS_APR0_SER_DLY_DELAY_1_SHFT                                 0x8
#define HWIO_APCS_APR0_SER_DLY_DELAY_0_BMSK                                0xff
#define HWIO_APCS_APR0_SER_DLY_DELAY_0_SHFT                                 0x0

#define HWIO_APCS_APR0_SER_DLY_SEL0_ADDR(x)                          ((x) + 0x00000088)
#define HWIO_APCS_APR0_SER_DLY_SEL0_OFFS                             (0x00000088)
#define HWIO_APCS_APR0_SER_DLY_SEL0_RMSK                             0xffffffff
#define HWIO_APCS_APR0_SER_DLY_SEL0_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SER_DLY_SEL0_ADDR(x), HWIO_APCS_APR0_SER_DLY_SEL0_RMSK)
#define HWIO_APCS_APR0_SER_DLY_SEL0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SER_DLY_SEL0_ADDR(x), m)
#define HWIO_APCS_APR0_SER_DLY_SEL0_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SER_DLY_SEL0_ADDR(x),v)
#define HWIO_APCS_APR0_SER_DLY_SEL0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SER_DLY_SEL0_ADDR(x),m,v,HWIO_APCS_APR0_SER_DLY_SEL0_IN(x))
#define HWIO_APCS_APR0_SER_DLY_SEL0_DLY_SEL0_BMSK                    0xffffffff
#define HWIO_APCS_APR0_SER_DLY_SEL0_DLY_SEL0_SHFT                           0x0

#define HWIO_APCS_APR0_SER_DLY_SEL1_ADDR(x)                          ((x) + 0x0000008c)
#define HWIO_APCS_APR0_SER_DLY_SEL1_OFFS                             (0x0000008c)
#define HWIO_APCS_APR0_SER_DLY_SEL1_RMSK                             0xffffffff
#define HWIO_APCS_APR0_SER_DLY_SEL1_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SER_DLY_SEL1_ADDR(x), HWIO_APCS_APR0_SER_DLY_SEL1_RMSK)
#define HWIO_APCS_APR0_SER_DLY_SEL1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SER_DLY_SEL1_ADDR(x), m)
#define HWIO_APCS_APR0_SER_DLY_SEL1_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SER_DLY_SEL1_ADDR(x),v)
#define HWIO_APCS_APR0_SER_DLY_SEL1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SER_DLY_SEL1_ADDR(x),m,v,HWIO_APCS_APR0_SER_DLY_SEL1_IN(x))
#define HWIO_APCS_APR0_SER_DLY_SEL1_DLY_SEL1_BMSK                    0xffffffff
#define HWIO_APCS_APR0_SER_DLY_SEL1_DLY_SEL1_SHFT                           0x0

#define HWIO_APCS_APR0_SER_DLY_SEL2_ADDR(x)                          ((x) + 0x00000090)
#define HWIO_APCS_APR0_SER_DLY_SEL2_OFFS                             (0x00000090)
#define HWIO_APCS_APR0_SER_DLY_SEL2_RMSK                                   0xff
#define HWIO_APCS_APR0_SER_DLY_SEL2_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SER_DLY_SEL2_ADDR(x), HWIO_APCS_APR0_SER_DLY_SEL2_RMSK)
#define HWIO_APCS_APR0_SER_DLY_SEL2_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SER_DLY_SEL2_ADDR(x), m)
#define HWIO_APCS_APR0_SER_DLY_SEL2_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SER_DLY_SEL2_ADDR(x),v)
#define HWIO_APCS_APR0_SER_DLY_SEL2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SER_DLY_SEL2_ADDR(x),m,v,HWIO_APCS_APR0_SER_DLY_SEL2_IN(x))
#define HWIO_APCS_APR0_SER_DLY_SEL2_DLY_SEL2_BMSK                          0xff
#define HWIO_APCS_APR0_SER_DLY_SEL2_DLY_SEL2_SHFT                           0x0

#define HWIO_APCS_APR0_SLP_REQ_DLY_ADDR(x)                           ((x) + 0x000000c0)
#define HWIO_APCS_APR0_SLP_REQ_DLY_OFFS                              (0x000000c0)
#define HWIO_APCS_APR0_SLP_REQ_DLY_RMSK                                    0xff
#define HWIO_APCS_APR0_SLP_REQ_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APR0_SLP_REQ_DLY_ADDR(x), HWIO_APCS_APR0_SLP_REQ_DLY_RMSK)
#define HWIO_APCS_APR0_SLP_REQ_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APR0_SLP_REQ_DLY_ADDR(x), m)
#define HWIO_APCS_APR0_SLP_REQ_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APR0_SLP_REQ_DLY_ADDR(x),v)
#define HWIO_APCS_APR0_SLP_REQ_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APR0_SLP_REQ_DLY_ADDR(x),m,v,HWIO_APCS_APR0_SLP_REQ_DLY_IN(x))
#define HWIO_APCS_APR0_SLP_REQ_DLY_HYST_CNT_BMSK                           0xff
#define HWIO_APCS_APR0_SLP_REQ_DLY_HYST_CNT_SHFT                            0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_DCVS_APC
 *--------------------------------------------------------------------------*/

#define APCS_APC00_DCVS_APC_REG_BASE                                       (HMSS_PERIPH_BASE      + 0x00244600)
#define APCS_APC00_DCVS_APC_REG_BASE_OFFS                                  0x00244600

#define HWIO_APCS_APC00_DCVS_CTL_ADDR(x)                                   ((x) + 0x00000000)
#define HWIO_APCS_APC00_DCVS_CTL_OFFS                                      (0x00000000)
#define HWIO_APCS_APC00_DCVS_CTL_RMSK                                      0x80030001
#define HWIO_APCS_APC00_DCVS_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_CTL_ADDR(x), HWIO_APCS_APC00_DCVS_CTL_RMSK)
#define HWIO_APCS_APC00_DCVS_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_CTL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_CTL_IN(x))
#define HWIO_APCS_APC00_DCVS_CTL_BUSY_BMSK                                 0x80000000
#define HWIO_APCS_APC00_DCVS_CTL_BUSY_SHFT                                       0x1f
#define HWIO_APCS_APC00_DCVS_CTL_IRQ_EN_BMSK                                  0x20000
#define HWIO_APCS_APC00_DCVS_CTL_IRQ_EN_SHFT                                     0x11
#define HWIO_APCS_APC00_DCVS_CTL_CSM_EN_BMSK                                  0x10000
#define HWIO_APCS_APC00_DCVS_CTL_CSM_EN_SHFT                                     0x10
#define HWIO_APCS_APC00_DCVS_CTL_REQ_BMSK                                         0x1
#define HWIO_APCS_APC00_DCVS_CTL_REQ_SHFT                                         0x0

#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x)                             ((x) + 0x00000004)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_OFFS                                (0x00000004)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_RMSK                                      0xff
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x), HWIO_APCS_APC00_DCVS_CEIL_VLVL_RMSK)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_CEIL_VLVL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_CEIL_VLVL_IN(x))
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_CEILING_VLVL_BMSK                         0xff
#define HWIO_APCS_APC00_DCVS_CEIL_VLVL_CEILING_VLVL_SHFT                          0x0

#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x)                            ((x) + 0x00000008)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_OFFS                               (0x00000008)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_RMSK                                     0xff
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x), HWIO_APCS_APC00_DCVS_FLOOR_VLVL_RMSK)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_FLOOR_VLVL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_FLOOR_VLVL_IN(x))
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_FLOOR_VLVL_BMSK                          0xff
#define HWIO_APCS_APC00_DCVS_FLOOR_VLVL_FLOOR_VLVL_SHFT                           0x0

#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x)                             ((x) + 0x0000000c)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_OFFS                                (0x0000000c)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_RMSK                                      0xff
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x), HWIO_APCS_APC00_DCVS_SAFE_LVAL_RMSK)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_SAFE_LVAL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_SAFE_LVAL_IN(x))
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_SAFE_LVAL_BMSK                            0xff
#define HWIO_APCS_APC00_DCVS_SAFE_LVAL_SAFE_LVAL_SHFT                             0x0

#define HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x)                              ((x) + 0x00000010)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_OFFS                                 (0x00000010)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_RMSK                                 0xffff0073
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x), HWIO_APCS_APC00_DCVS_VOTE_CTL_RMSK)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_DCVS_VOTE_CTL_ADDR(x),m,v,HWIO_APCS_APC00_DCVS_VOTE_CTL_IN(x))
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_HYST_DLY_BMSK                        0xffff0000
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_HYST_DLY_SHFT                              0x10
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_PWR_STATE_THRESHOLD_BMSK                   0x70
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_PWR_STATE_THRESHOLD_SHFT                    0x4
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_SW_VOTE_VAL_BMSK                            0x2
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_SW_VOTE_VAL_SHFT                            0x1
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_VOTE_EN_BMSK                                0x1
#define HWIO_APCS_APC00_DCVS_VOTE_CTL_VOTE_EN_SHFT                                0x0

#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x)                          ((x) + 0x00000020)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_OFFS                             (0x00000020)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_RMSK                                    0x1
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x), HWIO_APCS_APC00_APC_PWR_GATE_MODE_RMSK)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x), m)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x),v)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_PWR_GATE_MODE_ADDR(x),m,v,HWIO_APCS_APC00_APC_PWR_GATE_MODE_IN(x))
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_MODE_BMSK                               0x1
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_MODE_SHFT                               0x0

#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x)                          ((x) + 0x00000024)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_OFFS                             (0x00000024)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_RMSK                                   0x7f
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x), HWIO_APCS_APC00_APC_LDO_VREF_FUNC_RMSK)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x), m)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x),v)
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_LDO_VREF_FUNC_ADDR(x),m,v,HWIO_APCS_APC00_APC_LDO_VREF_FUNC_IN(x))
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_VREF_LDO_BMSK                          0x7f
#define HWIO_APCS_APC00_APC_LDO_VREF_FUNC_VREF_LDO_SHFT                           0x0

#define HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x)                           ((x) + 0x00000028)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_OFFS                              (0x00000028)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_RMSK                                    0x7f
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x), HWIO_APCS_APC00_APC_LDO_VREF_RET_RMSK)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x), m)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x),v)
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_LDO_VREF_RET_ADDR(x),m,v,HWIO_APCS_APC00_APC_LDO_VREF_RET_IN(x))
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_VREF_RET_BMSK                           0x7f
#define HWIO_APCS_APC00_APC_LDO_VREF_RET_VREF_RET_SHFT                            0x0

#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x)                            ((x) + 0x00000030)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_OFFS                               (0x00000030)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_RMSK                                     0x13
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x), HWIO_APCS_APC00_APC_LDO_ACC_SEL_RMSK)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x), m)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x),v)
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_LDO_ACC_SEL_ADDR(x),m,v,HWIO_APCS_APC00_APC_LDO_ACC_SEL_IN(x))
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_PERF_MUX_SEL_BMSK                        0x10
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_PERF_MUX_SEL_SHFT                         0x4
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_L2_MODE_BMSK                              0x2
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_L2_MODE_SHFT                              0x1
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_CPU_MODE_BMSK                             0x1
#define HWIO_APCS_APC00_APC_LDO_ACC_SEL_CPU_MODE_SHFT                             0x0

#define HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x)                            ((x) + 0x00000034)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_OFFS                               (0x00000034)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_RMSK                                      0x7
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x), HWIO_APCS_APC00_APC_PGS_RET_DIS_RMSK)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x), m)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x),v)
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_PGS_RET_DIS_ADDR(x),m,v,HWIO_APCS_APC00_APC_PGS_RET_DIS_IN(x))
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_L2_PGS_RET_SLP_DIS_BMSK                   0x4
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_L2_PGS_RET_SLP_DIS_SHFT                   0x2
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_CPU1_PGS_RET_SLP_DIS_BMSK                 0x2
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_CPU1_PGS_RET_SLP_DIS_SHFT                 0x1
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_CPU0_PGS_RET_SLP_DIS_BMSK                 0x1
#define HWIO_APCS_APC00_APC_PGS_RET_DIS_CPU0_PGS_RET_SLP_DIS_SHFT                 0x0

#define HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x)                            ((x) + 0x00000038)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_OFFS                               (0x00000038)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_RMSK                                      0x7
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x), HWIO_APCS_APC00_APC_MAS_RET_DIS_RMSK)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x), m)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x),v)
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_MAS_RET_DIS_ADDR(x),m,v,HWIO_APCS_APC00_APC_MAS_RET_DIS_IN(x))
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_L2_MAS_RET_SLP_DIS_BMSK                   0x4
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_L2_MAS_RET_SLP_DIS_SHFT                   0x2
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_CPU1_MAS_RET_SLP_DIS_BMSK                 0x2
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_CPU1_MAS_RET_SLP_DIS_SHFT                 0x1
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_CPU0_MAS_RET_SLP_DIS_BMSK                 0x1
#define HWIO_APCS_APC00_APC_MAS_RET_DIS_CPU0_MAS_RET_SLP_DIS_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_APC_CFG
 *--------------------------------------------------------------------------*/

#define APCS_APC00_APC_CFG_REG_BASE                                 (HMSS_PERIPH_BASE      + 0x00284400)
#define APCS_APC00_APC_CFG_REG_BASE_OFFS                            0x00284400

#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_ADDR(x)                   ((x) + 0x00000000)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_OFFS                      (0x00000000)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_RMSK                           0xf0f
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_ADDR(x), HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_RMSK)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_ADDR(x), m)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_ADDR(x),v)
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_ADDR(x),m,v,HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_IN(x))
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_LDO2BHS_DLY_BMSK               0xf00
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_LDO2BHS_DLY_SHFT                 0x8
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_BHS2LDO_DLY_BMSK                 0xf
#define HWIO_APCS_APC00_APC_PWR_GATE_MODE_DLY_BHS2LDO_DLY_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_APC_STS
 *--------------------------------------------------------------------------*/

#define APCS_APC00_APC_STS_REG_BASE                                    (HMSS_PERIPH_BASE      + 0x002c4600)
#define APCS_APC00_APC_STS_REG_BASE_OFFS                               0x002c4600

#define HWIO_APCS_APC00_APC_PGSCTL_STS_ADDR(x)                             ((x) + 0x00000000)
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OFFS                                (0x00000000)
#define HWIO_APCS_APC00_APC_PGSCTL_STS_RMSK                                   0xf03ff
#define HWIO_APCS_APC00_APC_PGSCTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PGSCTL_STS_ADDR(x), HWIO_APCS_APC00_APC_PGSCTL_STS_RMSK)
#define HWIO_APCS_APC00_APC_PGSCTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_PGSCTL_STS_ADDR(x), m)
#define HWIO_APCS_APC00_APC_PGSCTL_STS_TIMER_BMSK                             0xf0000
#define HWIO_APCS_APC00_APC_PGSCTL_STS_TIMER_SHFT                                0x10
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_CPU_MODE_BIT1_BMSK                   0x200
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_CPU_MODE_BIT1_SHFT                     0x9
#define HWIO_APCS_APC00_APC_PGSCTL_STS_FSM_CUR_STATE_BIT2_BMSK                  0x100
#define HWIO_APCS_APC00_APC_PGSCTL_STS_FSM_CUR_STATE_BIT2_SHFT                    0x8
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_CPR_BYPASS_BMSK                       0x80
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_CPR_BYPASS_SHFT                        0x7
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_FREEZE_BMSK                           0x40
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_FREEZE_SHFT                            0x6
#define HWIO_APCS_APC00_APC_PGSCTL_STS_FSM_CUR_STATE_BMSK                        0x30
#define HWIO_APCS_APC00_APC_PGSCTL_STS_FSM_CUR_STATE_SHFT                         0x4
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_L2_MODE_BMSK                           0x8
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_L2_MODE_SHFT                           0x3
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_CPU_MODE_BMSK                          0x4
#define HWIO_APCS_APC00_APC_PGSCTL_STS_OUT_CPU_MODE_SHFT                          0x2
#define HWIO_APCS_APC00_APC_PGSCTL_STS_NEW_MODE_BMSK                              0x2
#define HWIO_APCS_APC00_APC_PGSCTL_STS_NEW_MODE_SHFT                              0x1
#define HWIO_APCS_APC00_APC_PGSCTL_STS_CSR_MODE_BMSK                              0x1
#define HWIO_APCS_APC00_APC_PGSCTL_STS_CSR_MODE_SHFT                              0x0

#define HWIO_APCS_APC00_APC_DOMAIN_STS_ADDR(x)                             ((x) + 0x00000080)
#define HWIO_APCS_APC00_APC_DOMAIN_STS_OFFS                                (0x00000080)
#define HWIO_APCS_APC00_APC_DOMAIN_STS_RMSK                                  0x333333
#define HWIO_APCS_APC00_APC_DOMAIN_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_DOMAIN_STS_ADDR(x), HWIO_APCS_APC00_APC_DOMAIN_STS_RMSK)
#define HWIO_APCS_APC00_APC_DOMAIN_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_DOMAIN_STS_ADDR(x), m)
#define HWIO_APCS_APC00_APC_DOMAIN_STS_L2_MAS_BMSK                           0x300000
#define HWIO_APCS_APC00_APC_DOMAIN_STS_L2_MAS_SHFT                               0x14
#define HWIO_APCS_APC00_APC_DOMAIN_STS_L2_PGS_BMSK                            0x30000
#define HWIO_APCS_APC00_APC_DOMAIN_STS_L2_PGS_SHFT                               0x10
#define HWIO_APCS_APC00_APC_DOMAIN_STS_CPU1_MAS_BMSK                           0x3000
#define HWIO_APCS_APC00_APC_DOMAIN_STS_CPU1_MAS_SHFT                              0xc
#define HWIO_APCS_APC00_APC_DOMAIN_STS_CPU1_PGS_BMSK                            0x300
#define HWIO_APCS_APC00_APC_DOMAIN_STS_CPU1_PGS_SHFT                              0x8
#define HWIO_APCS_APC00_APC_DOMAIN_STS_CPU0_MAS_BMSK                             0x30
#define HWIO_APCS_APC00_APC_DOMAIN_STS_CPU0_MAS_SHFT                              0x4
#define HWIO_APCS_APC00_APC_DOMAIN_STS_CPU0_PGS_BMSK                              0x3
#define HWIO_APCS_APC00_APC_DOMAIN_STS_CPU0_PGS_SHFT                              0x0

#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_ADDR(x)                        ((x) + 0x000000c0)
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_OFFS                           (0x000000c0)
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_RMSK                             0x3f3f3f
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_ADDR(x), HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_RMSK)
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_ADDR(x), m)
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D5_BMSK                       0x200000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D5_SHFT                           0x15
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D4_BMSK                       0x100000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D4_SHFT                           0x14
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D3_BMSK                        0x80000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D3_SHFT                           0x13
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D2_BMSK                        0x40000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D2_SHFT                           0x12
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D1_BMSK                        0x20000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D1_SHFT                           0x11
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D0_BMSK                        0x10000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_L2_D0_SHFT                           0x10
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C5_BMSK                       0x2000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C5_SHFT                          0xd
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C4_BMSK                       0x1000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C4_SHFT                          0xc
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C3_BMSK                        0x800
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C3_SHFT                          0xb
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C2_BMSK                        0x400
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C2_SHFT                          0xa
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C1_BMSK                        0x200
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C1_SHFT                          0x9
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C0_BMSK                        0x100
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU1_C0_SHFT                          0x8
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C5_BMSK                         0x20
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C5_SHFT                          0x5
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C4_BMSK                         0x10
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C4_SHFT                          0x4
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C3_BMSK                          0x8
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C3_SHFT                          0x3
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C2_BMSK                          0x4
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C2_SHFT                          0x2
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C1_BMSK                          0x2
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C1_SHFT                          0x1
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C0_BMSK                          0x1
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_CPU0_C0_SHFT                          0x0

#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_ADDR(x)                    ((x) + 0x000000c4)
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_OFFS                       (0x000000c4)
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_RMSK                       0x1ff7fdff
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_ADDR(x), HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_RMSK)
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_ADDR(x), m)
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_L2_SPM_CMD_BMSK            0x1ff00000
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_L2_SPM_CMD_SHFT                  0x14
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_CPU1_SPM_CMD_BMSK             0x7fc00
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_CPU1_SPM_CMD_SHFT                 0xa
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_CPU0_SPM_CMD_BMSK               0x1ff
#define HWIO_APCS_APC00_APC_SYSRST_DIAG_STS_SPM_CPU0_SPM_CMD_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_APC_TZ
 *--------------------------------------------------------------------------*/

#define APCS_APC00_APC_TZ_REG_BASE                  (HMSS_PERIPH_BASE      + 0x001c4400)
#define APCS_APC00_APC_TZ_REG_BASE_OFFS             0x001c4400

#define HWIO_APCS_APC00_APC_TZ_VOTE_ADDR(x)             ((x) + 0x00000000)
#define HWIO_APCS_APC00_APC_TZ_VOTE_OFFS                (0x00000000)
#define HWIO_APCS_APC00_APC_TZ_VOTE_RMSK                       0x1
#define HWIO_APCS_APC00_APC_TZ_VOTE_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_APC_TZ_VOTE_ADDR(x), HWIO_APCS_APC00_APC_TZ_VOTE_RMSK)
#define HWIO_APCS_APC00_APC_TZ_VOTE_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_APC_TZ_VOTE_ADDR(x), m)
#define HWIO_APCS_APC00_APC_TZ_VOTE_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_APC_TZ_VOTE_ADDR(x),v)
#define HWIO_APCS_APC00_APC_TZ_VOTE_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_APC_TZ_VOTE_ADDR(x),m,v,HWIO_APCS_APC00_APC_TZ_VOTE_IN(x))
#define HWIO_APCS_APC00_APC_TZ_VOTE_L2_PC_BMSK                 0x1
#define HWIO_APCS_APC00_APC_TZ_VOTE_L2_PC_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_L2_CFG
 *--------------------------------------------------------------------------*/

#define APCS_APC00_L2_CFG_REG_BASE                                    (HMSS_PERIPH_BASE      + 0x00284000)
#define APCS_APC00_L2_CFG_REG_BASE_OFFS                               0x00284000

#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_ADDR(x)                         ((x) + 0x00000000)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_OFFS                            (0x00000000)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_RMSK                            0x3f3f3f3f
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_GATE_CFG0_ADDR(x), HWIO_APCS_APC00_L2_PWR_GATE_CFG0_RMSK)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_GATE_CFG0_ADDR(x), m)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_L2_PWR_GATE_CFG0_ADDR(x),v)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_L2_PWR_GATE_CFG0_ADDR(x),m,v,HWIO_APCS_APC00_L2_PWR_GATE_CFG0_IN(x))
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_LDO_PWR_DWN_BMSK                0x3f000000
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_LDO_PWR_DWN_SHFT                      0x18
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_LDO_BYP_BMSK                      0x3f0000
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_LDO_BYP_SHFT                          0x10
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_SEG_EN_OUTER_BMSK                   0x3f00
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_SEG_EN_OUTER_SHFT                      0x8
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_SEG_EN_INNER_BMSK                     0x3f
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG0_SEG_EN_INNER_SHFT                      0x0

#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_ADDR(x)                         ((x) + 0x00000004)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_OFFS                            (0x00000004)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_RMSK                                 0x73f
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_GATE_CFG1_ADDR(x), HWIO_APCS_APC00_L2_PWR_GATE_CFG1_RMSK)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_GATE_CFG1_ADDR(x), m)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_L2_PWR_GATE_CFG1_ADDR(x),v)
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_L2_PWR_GATE_CFG1_ADDR(x),m,v,HWIO_APCS_APC00_L2_PWR_GATE_CFG1_IN(x))
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_LDO_PWR_LVL_4_RET_BMSK               0x700
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_LDO_PWR_LVL_4_RET_SHFT                 0x8
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_LDO_PWR_DWN_4_RET_BMSK                0x3f
#define HWIO_APCS_APC00_L2_PWR_GATE_CFG1_LDO_PWR_DWN_4_RET_SHFT                 0x0

#define HWIO_APCS_APC00_L2_MAS_CFG_ADDR(x)                               ((x) + 0x00000040)
#define HWIO_APCS_APC00_L2_MAS_CFG_OFFS                                  (0x00000040)
#define HWIO_APCS_APC00_L2_MAS_CFG_RMSK                                       0x387
#define HWIO_APCS_APC00_L2_MAS_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_MAS_CFG_ADDR(x), HWIO_APCS_APC00_L2_MAS_CFG_RMSK)
#define HWIO_APCS_APC00_L2_MAS_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_MAS_CFG_ADDR(x), m)
#define HWIO_APCS_APC00_L2_MAS_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_L2_MAS_CFG_ADDR(x),v)
#define HWIO_APCS_APC00_L2_MAS_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_L2_MAS_CFG_ADDR(x),m,v,HWIO_APCS_APC00_L2_MAS_CFG_IN(x))
#define HWIO_APCS_APC00_L2_MAS_CFG_SEG_EN_MX_BMSK                             0x380
#define HWIO_APCS_APC00_L2_MAS_CFG_SEG_EN_MX_SHFT                               0x7
#define HWIO_APCS_APC00_L2_MAS_CFG_SEG_EN_APC_BMSK                              0x7
#define HWIO_APCS_APC00_L2_MAS_CFG_SEG_EN_APC_SHFT                              0x0

#define HWIO_APCS_APC00_L2_NMM_CTL_ADDR(x)                               ((x) + 0x00000100)
#define HWIO_APCS_APC00_L2_NMM_CTL_OFFS                                  (0x00000100)
#define HWIO_APCS_APC00_L2_NMM_CTL_RMSK                                        0x73
#define HWIO_APCS_APC00_L2_NMM_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_NMM_CTL_ADDR(x), HWIO_APCS_APC00_L2_NMM_CTL_RMSK)
#define HWIO_APCS_APC00_L2_NMM_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_NMM_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_L2_NMM_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_L2_NMM_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_L2_NMM_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_L2_NMM_CTL_ADDR(x),m,v,HWIO_APCS_APC00_L2_NMM_CTL_IN(x))
#define HWIO_APCS_APC00_L2_NMM_CTL_PWR_STATE_THRESHOLD_BMSK                    0x70
#define HWIO_APCS_APC00_L2_NMM_CTL_PWR_STATE_THRESHOLD_SHFT                     0x4
#define HWIO_APCS_APC00_L2_NMM_CTL_VOTE_SLP_EN_BMSK                             0x2
#define HWIO_APCS_APC00_L2_NMM_CTL_VOTE_SLP_EN_SHFT                             0x1
#define HWIO_APCS_APC00_L2_NMM_CTL_VOTE_EN_BMSK                                 0x1
#define HWIO_APCS_APC00_L2_NMM_CTL_VOTE_EN_SHFT                                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_L2_PWR_CTL
 *--------------------------------------------------------------------------*/

#define APCS_APC00_L2_PWR_CTL_REG_BASE                           (HMSS_PERIPH_BASE      + 0x00044000)
#define APCS_APC00_L2_PWR_CTL_REG_BASE_OFFS                      0x00044000

#define HWIO_APCS_APC00_L2_PWR_CTL_ADDR(x)                          ((x) + 0x00000000)
#define HWIO_APCS_APC00_L2_PWR_CTL_OFFS                             (0x00000000)
#define HWIO_APCS_APC00_L2_PWR_CTL_RMSK                             0xfd0001ff
#define HWIO_APCS_APC00_L2_PWR_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_CTL_ADDR(x), HWIO_APCS_APC00_L2_PWR_CTL_RMSK)
#define HWIO_APCS_APC00_L2_PWR_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_L2_PWR_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_L2_PWR_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_L2_PWR_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_L2_PWR_CTL_ADDR(x),m,v,HWIO_APCS_APC00_L2_PWR_CTL_IN(x))
#define HWIO_APCS_APC00_L2_PWR_CTL_DISABLE_SPM_WAKEUP_BMSK          0x80000000
#define HWIO_APCS_APC00_L2_PWR_CTL_DISABLE_SPM_WAKEUP_SHFT                0x1f
#define HWIO_APCS_APC00_L2_PWR_CTL_HY_RST_COMP_REQ_BMSK             0x40000000
#define HWIO_APCS_APC00_L2_PWR_CTL_HY_RST_COMP_REQ_SHFT                   0x1e
#define HWIO_APCS_APC00_L2_PWR_CTL_SLP_STATE_STATUS_BMSK            0x20000000
#define HWIO_APCS_APC00_L2_PWR_CTL_SLP_STATE_STATUS_SHFT                  0x1d
#define HWIO_APCS_APC00_L2_PWR_CTL_GF_MUX_RST_STATUS_BMSK           0x10000000
#define HWIO_APCS_APC00_L2_PWR_CTL_GF_MUX_RST_STATUS_SHFT                 0x1c
#define HWIO_APCS_APC00_L2_PWR_CTL_CBF_ACTIVE_BMSK                   0x8000000
#define HWIO_APCS_APC00_L2_PWR_CTL_CBF_ACTIVE_SHFT                        0x1b
#define HWIO_APCS_APC00_L2_PWR_CTL_APR_ACTIVE_BMSK                   0x4000000
#define HWIO_APCS_APC00_L2_PWR_CTL_APR_ACTIVE_SHFT                        0x1a
#define HWIO_APCS_APC00_L2_PWR_CTL_RST_COMP_ACK_BMSK                 0x1000000
#define HWIO_APCS_APC00_L2_PWR_CTL_RST_COMP_ACK_SHFT                      0x18
#define HWIO_APCS_APC00_L2_PWR_CTL_L2_PWRD_UP_BMSK                       0x100
#define HWIO_APCS_APC00_L2_PWR_CTL_L2_PWRD_UP_SHFT                         0x8
#define HWIO_APCS_APC00_L2_PWR_CTL_GF_MUX_RST_BMSK                        0x80
#define HWIO_APCS_APC00_L2_PWR_CTL_GF_MUX_RST_SHFT                         0x7
#define HWIO_APCS_APC00_L2_PWR_CTL_CLAMP_APMPD_BMSK                       0x40
#define HWIO_APCS_APC00_L2_PWR_CTL_CLAMP_APMPD_SHFT                        0x6
#define HWIO_APCS_APC00_L2_PWR_CTL_MA_DSBL_BMSK                           0x20
#define HWIO_APCS_APC00_L2_PWR_CTL_MA_DSBL_SHFT                            0x5
#define HWIO_APCS_APC00_L2_PWR_CTL_HS_DSBL_BMSK                           0x10
#define HWIO_APCS_APC00_L2_PWR_CTL_HS_DSBL_SHFT                            0x4
#define HWIO_APCS_APC00_L2_PWR_CTL_HS_RST_BMSK                             0x8
#define HWIO_APCS_APC00_L2_PWR_CTL_HS_RST_SHFT                             0x3
#define HWIO_APCS_APC00_L2_PWR_CTL_POR_RST_BMSK                            0x4
#define HWIO_APCS_APC00_L2_PWR_CTL_POR_RST_SHFT                            0x2
#define HWIO_APCS_APC00_L2_PWR_CTL_WARM_RST_BMSK                           0x2
#define HWIO_APCS_APC00_L2_PWR_CTL_WARM_RST_SHFT                           0x1
#define HWIO_APCS_APC00_L2_PWR_CTL_CLAMP_L2PD_BMSK                         0x1
#define HWIO_APCS_APC00_L2_PWR_CTL_CLAMP_L2PD_SHFT                         0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_L2_STS
 *--------------------------------------------------------------------------*/

#define APCS_APC00_L2_STS_REG_BASE                                 (HMSS_PERIPH_BASE      + 0x002c4400)
#define APCS_APC00_L2_STS_REG_BASE_OFFS                            0x002c4400

#define HWIO_APCS_APC00_L2_PGS_STS_ADDR(x)                            ((x) + 0x00000000)
#define HWIO_APCS_APC00_L2_PGS_STS_OFFS                               (0x00000000)
#define HWIO_APCS_APC00_L2_PGS_STS_RMSK                                 0xfff3ff
#define HWIO_APCS_APC00_L2_PGS_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PGS_STS_ADDR(x), HWIO_APCS_APC00_L2_PGS_STS_RMSK)
#define HWIO_APCS_APC00_L2_PGS_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PGS_STS_ADDR(x), m)
#define HWIO_APCS_APC00_L2_PGS_STS_DLY_CNT_BMSK                         0xff0000
#define HWIO_APCS_APC00_L2_PGS_STS_DLY_CNT_SHFT                             0x10
#define HWIO_APCS_APC00_L2_PGS_STS_STEADY_SLEEP_BMSK                      0x8000
#define HWIO_APCS_APC00_L2_PGS_STS_STEADY_SLEEP_SHFT                         0xf
#define HWIO_APCS_APC00_L2_PGS_STS_STEADY_ACTIVE_BMSK                     0x4000
#define HWIO_APCS_APC00_L2_PGS_STS_STEADY_ACTIVE_SHFT                        0xe
#define HWIO_APCS_APC00_L2_PGS_STS_SPM_RET_BMSK                           0x2000
#define HWIO_APCS_APC00_L2_PGS_STS_SPM_RET_SHFT                              0xd
#define HWIO_APCS_APC00_L2_PGS_STS_SPM_PC_BMSK                            0x1000
#define HWIO_APCS_APC00_L2_PGS_STS_SPM_PC_SHFT                               0xc
#define HWIO_APCS_APC00_L2_PGS_STS_NEW_MODE_BMSK                           0x300
#define HWIO_APCS_APC00_L2_PGS_STS_NEW_MODE_SHFT                             0x8
#define HWIO_APCS_APC00_L2_PGS_STS_FSM_STATE_BMSK                           0xf0
#define HWIO_APCS_APC00_L2_PGS_STS_FSM_STATE_SHFT                            0x4
#define HWIO_APCS_APC00_L2_PGS_STS_CURR_MODE_BMSK                            0xf
#define HWIO_APCS_APC00_L2_PGS_STS_CURR_MODE_SHFT                            0x0

#define HWIO_APCS_APC00_L2_PWR_GATE_STS_ADDR(x)                       ((x) + 0x00000004)
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_OFFS                          (0x00000004)
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_RMSK                          0x1ffffff3
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_GATE_STS_ADDR(x), HWIO_APCS_APC00_L2_PWR_GATE_STS_RMSK)
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_GATE_STS_ADDR(x), m)
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_LDO_VREF_SEL_BMSK             0x10000000
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_LDO_VREF_SEL_SHFT                   0x1c
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_LDO_BYP_BMSK                   0xfc00000
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_LDO_BYP_SHFT                        0x16
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_LDO_PWR_DWN_BMSK                0x3f0000
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_LDO_PWR_DWN_SHFT                    0x10
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_EN_REST_OUTER_BMSK                0xfc00
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_EN_REST_OUTER_SHFT                   0xa
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_EN_REST_INNER_BMSK                 0x3f0
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_EN_REST_INNER_SHFT                   0x4
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_EN_FEW_BMSK                          0x3
#define HWIO_APCS_APC00_L2_PWR_GATE_STS_EN_FEW_SHFT                          0x0

#define HWIO_APCS_APC00_L2_MAS_STS_ADDR(x)                            ((x) + 0x00000040)
#define HWIO_APCS_APC00_L2_MAS_STS_OFFS                               (0x00000040)
#define HWIO_APCS_APC00_L2_MAS_STS_RMSK                                 0xfff373
#define HWIO_APCS_APC00_L2_MAS_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_MAS_STS_ADDR(x), HWIO_APCS_APC00_L2_MAS_STS_RMSK)
#define HWIO_APCS_APC00_L2_MAS_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_MAS_STS_ADDR(x), m)
#define HWIO_APCS_APC00_L2_MAS_STS_TMR_CNT_BMSK                         0xff0000
#define HWIO_APCS_APC00_L2_MAS_STS_TMR_CNT_SHFT                             0x10
#define HWIO_APCS_APC00_L2_MAS_STS_STEADY_SLEEP_BMSK                      0x8000
#define HWIO_APCS_APC00_L2_MAS_STS_STEADY_SLEEP_SHFT                         0xf
#define HWIO_APCS_APC00_L2_MAS_STS_STEADY_ACTIVE_BMSK                     0x4000
#define HWIO_APCS_APC00_L2_MAS_STS_STEADY_ACTIVE_SHFT                        0xe
#define HWIO_APCS_APC00_L2_MAS_STS_SPM_RET_BMSK                           0x2000
#define HWIO_APCS_APC00_L2_MAS_STS_SPM_RET_SHFT                              0xd
#define HWIO_APCS_APC00_L2_MAS_STS_SPM_PC_BMSK                            0x1000
#define HWIO_APCS_APC00_L2_MAS_STS_SPM_PC_SHFT                               0xc
#define HWIO_APCS_APC00_L2_MAS_STS_NEW_MODE_BMSK                           0x300
#define HWIO_APCS_APC00_L2_MAS_STS_NEW_MODE_SHFT                             0x8
#define HWIO_APCS_APC00_L2_MAS_STS_FSM_STATE_BMSK                           0x70
#define HWIO_APCS_APC00_L2_MAS_STS_FSM_STATE_SHFT                            0x4
#define HWIO_APCS_APC00_L2_MAS_STS_CURR_MODE_BMSK                            0x3
#define HWIO_APCS_APC00_L2_MAS_STS_CURR_MODE_SHFT                            0x0

#define HWIO_APCS_APC00_L2_PWR_MUX_STS_ADDR(x)                        ((x) + 0x00000044)
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_OFFS                           (0x00000044)
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_RMSK                              0x70773
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_MUX_STS_ADDR(x), HWIO_APCS_APC00_L2_PWR_MUX_STS_RMSK)
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_MUX_STS_ADDR(x), m)
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_CLAMP_BMSK                        0x40000
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_CLAMP_SHFT                           0x12
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_TGL_SEL_BMSK                      0x20000
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_TGL_SEL_SHFT                         0x11
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_MEM_RET_BMSK                      0x10000
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_MEM_RET_SHFT                         0x10
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_MX_EN_REST_BMSK                     0x700
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_MX_EN_REST_SHFT                       0x8
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_APCC_EN_REST_BMSK                    0x70
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_APCC_EN_REST_SHFT                     0x4
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_EN_FEW_BMSK                           0x3
#define HWIO_APCS_APC00_L2_PWR_MUX_STS_EN_FEW_SHFT                           0x0

#define HWIO_APCS_APC00_L2_PWR_CTL_STS_ADDR(x)                        ((x) + 0x00000080)
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_OFFS                           (0x00000080)
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RMSK                           0xffffffff
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_CTL_STS_ADDR(x), HWIO_APCS_APC00_L2_PWR_CTL_STS_RMSK)
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_CTL_STS_ADDR(x), m)
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_FUSE_DSBL_CPU1_BMSK            0x80000000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_FUSE_DSBL_CPU1_SHFT                  0x1f
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_FUSE_DSBL_CPU0_BMSK            0x40000000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_FUSE_DSBL_CPU0_SHFT                  0x1e
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_GFMUX_ARST_BMSK                0x20000000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_GFMUX_ARST_SHFT                      0x1d
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CXPD_FUNC_ARST_BMSK            0x10000000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CXPD_FUNC_ARST_SHFT                  0x1c
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CXPD_DBG_ARST_BMSK              0x8000000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CXPD_DBG_ARST_SHFT                   0x1b
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_POR_ARST_BMSK                   0x4000000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_POR_ARST_SHFT                        0x1a
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_FUNC_ARST_BMSK                  0x2000000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_FUNC_ARST_SHFT                       0x19
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_NMM_REQ_BMSK                    0x1000000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_NMM_REQ_SHFT                         0x18
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D5_BMSK                0x800000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D5_SHFT                    0x17
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D4_BMSK                0x400000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D4_SHFT                    0x16
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D3_BMSK                0x200000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D3_SHFT                    0x15
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D2_BMSK                0x100000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D2_SHFT                    0x14
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D1_BMSK                 0x80000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D1_SHFT                    0x13
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D0_BMSK                 0x40000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PWR_STATE_D0_SHFT                    0x12
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CPR_CTL_BMSK                      0x20000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CPR_CTL_SHFT                         0x11
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_SNP_WAKE_UP_BMSK                  0x10000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_SNP_WAKE_UP_SHFT                     0x10
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PLL_PWR_DWN_ACK_BMSK               0x8000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PLL_PWR_DWN_ACK_SHFT                  0xf
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PLL_PWR_DWN_REQ_BMSK               0x4000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_PLL_PWR_DWN_REQ_SHFT                  0xe
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_L2_PUSHED_B4_SLP_BMSK              0x2000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_L2_PUSHED_B4_SLP_SHFT                 0xd
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_L2_PUSH_B4_SLP_BMSK                0x1000
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_L2_PUSH_B4_SLP_SHFT                   0xc
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RET_RESTORE_ACK_BMSK                0x800
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RET_RESTORE_ACK_SHFT                  0xb
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RET_RESTORE_REQ_BMSK                0x400
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RET_RESTORE_REQ_SHFT                  0xa
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RET_SAVE_ACK_BMSK                   0x200
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RET_SAVE_ACK_SHFT                     0x9
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RET_SAVE_REQ_BMSK                   0x100
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RET_SAVE_REQ_SHFT                     0x8
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RST_COMPLT_ACK_BMSK                  0x80
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RST_COMPLT_ACK_SHFT                   0x7
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RST_COMPLT_REQ_BMSK                  0x40
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_RST_COMPLT_REQ_SHFT                   0x6
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_SLEEP_ACK_BMSK                       0x20
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_SLEEP_ACK_SHFT                        0x5
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_SLEEP_REQ_BMSK                       0x10
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_SLEEP_REQ_SHFT                        0x4
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_L2_PWRD_UP_BMSK                       0x8
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_L2_PWRD_UP_SHFT                       0x3
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CLAMP_APMPD_BMSK                      0x4
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CLAMP_APMPD_SHFT                      0x2
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CLAMP_L2PD_BMSK                       0x2
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_CLAMP_L2PD_SHFT                       0x1
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_FRC_CLK_OFF_BMSK                      0x1
#define HWIO_APCS_APC00_L2_PWR_CTL_STS_FRC_CLK_OFF_SHFT                      0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_L2_SW_EVENT
 *--------------------------------------------------------------------------*/

#define APCS_APC00_L2_SW_EVENT_REG_BASE                       (HMSS_PERIPH_BASE      + 0x00104000)
#define APCS_APC00_L2_SW_EVENT_REG_BASE_OFFS                  0x00104000

#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_ADDR(x)                  ((x) + 0x00000000)
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_OFFS                     (0x00000000)
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_RMSK                            0x7
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_SW_SPM_EVENT_ADDR(x), HWIO_APCS_APC00_L2_SW_SPM_EVENT_RMSK)
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_SW_SPM_EVENT_ADDR(x), m)
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_L2_SW_SPM_EVENT_ADDR(x),v)
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_L2_SW_SPM_EVENT_ADDR(x),m,v,HWIO_APCS_APC00_L2_SW_SPM_EVENT_IN(x))
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_SPM_SPARE_BMSK                  0x4
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_SPM_SPARE_SHFT                  0x2
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_SPM_WAKEUP_BMSK                 0x2
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_SPM_WAKEUP_SHFT                 0x1
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_SPM_EVENT_BMSK                  0x1
#define HWIO_APCS_APC00_L2_SW_SPM_EVENT_SPM_EVENT_SHFT                  0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_L2_DATA_PUSH
 *--------------------------------------------------------------------------*/

#define APCS_APC00_L2_DATA_PUSH_REG_BASE            (HMSS_PERIPH_BASE      + 0x00005800)
#define APCS_APC00_L2_DATA_PUSH_REG_BASE_OFFS       0x00005800

#define HWIO_APCS_APC00_L2_DATA_PUSH_ADDR(x)           ((x) + 0x00000000)
#define HWIO_APCS_APC00_L2_DATA_PUSH_OFFS              (0x00000000)
#define HWIO_APCS_APC00_L2_DATA_PUSH_RMSK                     0x1
#define HWIO_APCS_APC00_L2_DATA_PUSH_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_DATA_PUSH_ADDR(x), HWIO_APCS_APC00_L2_DATA_PUSH_RMSK)
#define HWIO_APCS_APC00_L2_DATA_PUSH_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_DATA_PUSH_ADDR(x), m)
#define HWIO_APCS_APC00_L2_DATA_PUSH_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_L2_DATA_PUSH_ADDR(x),v)
#define HWIO_APCS_APC00_L2_DATA_PUSH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_L2_DATA_PUSH_ADDR(x),m,v,HWIO_APCS_APC00_L2_DATA_PUSH_IN(x))
#define HWIO_APCS_APC00_L2_DATA_PUSH_REQ_BMSK                 0x1
#define HWIO_APCS_APC00_L2_DATA_PUSH_REQ_SHFT                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_L2_WAR
 *--------------------------------------------------------------------------*/

#define APCS_APC00_L2_WAR_REG_BASE                         (HMSS_PERIPH_BASE      + 0x00144000)
#define APCS_APC00_L2_WAR_REG_BASE_OFFS                    0x00144000

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_L2_DBG
 *--------------------------------------------------------------------------*/

#define APCS_APC00_L2_DBG_REG_BASE                                         (HMSS_PERIPH_BASE      + 0x00304000)
#define APCS_APC00_L2_DBG_REG_BASE_OFFS                                    0x00304000

#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_ADDR(x)                              ((x) + 0x00000004)
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_OFFS                                 (0x00000004)
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_RMSK                                 0x9f9f0600
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_GATE_DIAG_ADDR(x), HWIO_APCS_APC00_L2_PWR_GATE_DIAG_RMSK)
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_L2_PWR_GATE_DIAG_ADDR(x), m)
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_L2_PWR_GATE_DIAG_ADDR(x),v)
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_L2_PWR_GATE_DIAG_ADDR(x),m,v,HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IN(x))
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IMEAS_LDO_ACC_TRIM_SEL_BMSK          0x80000000
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IMEAS_LDO_ACC_TRIM_SEL_SHFT                0x1f
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IMEAS_LDO_ACC_TRIM_BMSK              0x1f000000
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IMEAS_LDO_ACC_TRIM_SHFT                    0x18
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IMEAS_BHS_ACC_TRIM_SEL_BMSK            0x800000
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IMEAS_BHS_ACC_TRIM_SEL_SHFT                0x17
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IMEAS_BHS_ACC_TRIM_BMSK                0x1f0000
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_IMEAS_BHS_ACC_TRIM_SHFT                    0x10
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_CPUL2_SHS_OVERRIDE_BMSK                   0x400
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_CPUL2_SHS_OVERRIDE_SHFT                     0xa
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_CURR_LOAD_OVERRIDE_BMSK                   0x200
#define HWIO_APCS_APC00_L2_PWR_GATE_DIAG_CURR_LOAD_OVERRIDE_SHFT                     0x9

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_CPU0_CPU_CFG
 *--------------------------------------------------------------------------*/

#define APCS_APC00_CPU0_CPU_CFG_REG_BASE                                   (HMSS_PERIPH_BASE      + 0x00280000)
#define APCS_APC00_CPU0_CPU_CFG_REG_BASE_OFFS                              0x00280000

#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_ADDR(x)                         ((x) + 0x00000000)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_OFFS                            (0x00000000)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_RMSK                            0x3f3f3f3f
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_ADDR(x), HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_RMSK)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_ADDR(x),v)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_ADDR(x),m,v,HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_IN(x))
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_LDO_PWR_DWN_BMSK                0x3f000000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_LDO_PWR_DWN_SHFT                      0x18
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_LDO_BYP_BMSK                      0x3f0000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_LDO_BYP_SHFT                          0x10
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_SEG_EN_OUTER_BMSK                   0x3f00
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_SEG_EN_OUTER_SHFT                      0x8
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_SEG_EN_INNER_BMSK                     0x3f
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG0_SEG_EN_INNER_SHFT                      0x0

#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_ADDR(x)                         ((x) + 0x00000004)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_OFFS                            (0x00000004)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_RMSK                                  0x3f
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_ADDR(x), HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_RMSK)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_ADDR(x),v)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_ADDR(x),m,v,HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_IN(x))
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_LDO_PWR_DWN_4_RET_BMSK                0x3f
#define HWIO_APCS_APC00_CPU0_PWR_GATE_CFG1_LDO_PWR_DWN_4_RET_SHFT                 0x0

#define HWIO_APCS_APC00_CPU0_MAS_CFG_ADDR(x)                               ((x) + 0x00000040)
#define HWIO_APCS_APC00_CPU0_MAS_CFG_OFFS                                  (0x00000040)
#define HWIO_APCS_APC00_CPU0_MAS_CFG_RMSK                                       0x387
#define HWIO_APCS_APC00_CPU0_MAS_CFG_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_MAS_CFG_ADDR(x), HWIO_APCS_APC00_CPU0_MAS_CFG_RMSK)
#define HWIO_APCS_APC00_CPU0_MAS_CFG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_MAS_CFG_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_MAS_CFG_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPU0_MAS_CFG_ADDR(x),v)
#define HWIO_APCS_APC00_CPU0_MAS_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPU0_MAS_CFG_ADDR(x),m,v,HWIO_APCS_APC00_CPU0_MAS_CFG_IN(x))
#define HWIO_APCS_APC00_CPU0_MAS_CFG_SEG_EN_MX_BMSK                             0x380
#define HWIO_APCS_APC00_CPU0_MAS_CFG_SEG_EN_MX_SHFT                               0x7
#define HWIO_APCS_APC00_CPU0_MAS_CFG_SEG_EN_APC_BMSK                              0x7
#define HWIO_APCS_APC00_CPU0_MAS_CFG_SEG_EN_APC_SHFT                              0x0

#define HWIO_APCS_APC00_CPU0_NMM_CTL_ADDR(x)                               ((x) + 0x00000100)
#define HWIO_APCS_APC00_CPU0_NMM_CTL_OFFS                                  (0x00000100)
#define HWIO_APCS_APC00_CPU0_NMM_CTL_RMSK                                        0x73
#define HWIO_APCS_APC00_CPU0_NMM_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_NMM_CTL_ADDR(x), HWIO_APCS_APC00_CPU0_NMM_CTL_RMSK)
#define HWIO_APCS_APC00_CPU0_NMM_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_NMM_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_NMM_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPU0_NMM_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPU0_NMM_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPU0_NMM_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPU0_NMM_CTL_IN(x))
#define HWIO_APCS_APC00_CPU0_NMM_CTL_PWR_STATE_THRESHOLD_BMSK                    0x70
#define HWIO_APCS_APC00_CPU0_NMM_CTL_PWR_STATE_THRESHOLD_SHFT                     0x4
#define HWIO_APCS_APC00_CPU0_NMM_CTL_VOTE_SLP_EN_BMSK                             0x2
#define HWIO_APCS_APC00_CPU0_NMM_CTL_VOTE_SLP_EN_SHFT                             0x1
#define HWIO_APCS_APC00_CPU0_NMM_CTL_VOTE_EN_BMSK                                 0x1
#define HWIO_APCS_APC00_CPU0_NMM_CTL_VOTE_EN_SHFT                                 0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_CPU0_CPU_PWR_CTL
 *--------------------------------------------------------------------------*/

#define APCS_APC00_CPU0_CPU_PWR_CTL_REG_BASE                             (HMSS_PERIPH_BASE      + 0x00040000)
#define APCS_APC00_CPU0_CPU_PWR_CTL_REG_BASE_OFFS                        0x00040000

#define HWIO_APCS_APC00_CPU0_PWR_CTL_ADDR(x)                             ((x) + 0x00000000)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_OFFS                                (0x00000000)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_RMSK                                0xf900017f
#define HWIO_APCS_APC00_CPU0_PWR_CTL_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_CTL_ADDR(x), HWIO_APCS_APC00_CPU0_PWR_CTL_RMSK)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_CTL_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPU0_PWR_CTL_ADDR(x),v)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPU0_PWR_CTL_ADDR(x),m,v,HWIO_APCS_APC00_CPU0_PWR_CTL_IN(x))
#define HWIO_APCS_APC00_CPU0_PWR_CTL_DISABLE_SPM_WAKEUP_BMSK             0x80000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_DISABLE_SPM_WAKEUP_SHFT                   0x1f
#define HWIO_APCS_APC00_CPU0_PWR_CTL_HY_RST_COMP_REQ_BMSK                0x40000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_HY_RST_COMP_REQ_SHFT                      0x1e
#define HWIO_APCS_APC00_CPU0_PWR_CTL_SLP_STATE_STATUS_BMSK               0x20000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_SLP_STATE_STATUS_SHFT                     0x1d
#define HWIO_APCS_APC00_CPU0_PWR_CTL_MAS_PGS_ACTIVE_STATUS_BMSK          0x10000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_MAS_PGS_ACTIVE_STATUS_SHFT                0x1c
#define HWIO_APCS_APC00_CPU0_PWR_CTL_L2_ACTIVE_BMSK                       0x8000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_L2_ACTIVE_SHFT                            0x1b
#define HWIO_APCS_APC00_CPU0_PWR_CTL_RST_COMP_ACK_BMSK                    0x1000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_RST_COMP_ACK_SHFT                         0x18
#define HWIO_APCS_APC00_CPU0_PWR_CTL_CORE_PWRD_UP_BMSK                        0x100
#define HWIO_APCS_APC00_CPU0_PWR_CTL_CORE_PWRD_UP_SHFT                          0x8
#define HWIO_APCS_APC00_CPU0_PWR_CTL_CLAMP_APMPD_BMSK                          0x40
#define HWIO_APCS_APC00_CPU0_PWR_CTL_CLAMP_APMPD_SHFT                           0x6
#define HWIO_APCS_APC00_CPU0_PWR_CTL_MA_DSBL_BMSK                              0x20
#define HWIO_APCS_APC00_CPU0_PWR_CTL_MA_DSBL_SHFT                               0x5
#define HWIO_APCS_APC00_CPU0_PWR_CTL_HS_DSBL_BMSK                              0x10
#define HWIO_APCS_APC00_CPU0_PWR_CTL_HS_DSBL_SHFT                               0x4
#define HWIO_APCS_APC00_CPU0_PWR_CTL_HS_RST_BMSK                                0x8
#define HWIO_APCS_APC00_CPU0_PWR_CTL_HS_RST_SHFT                                0x3
#define HWIO_APCS_APC00_CPU0_PWR_CTL_POR_RST_BMSK                               0x4
#define HWIO_APCS_APC00_CPU0_PWR_CTL_POR_RST_SHFT                               0x2
#define HWIO_APCS_APC00_CPU0_PWR_CTL_WARM_RST_BMSK                              0x2
#define HWIO_APCS_APC00_CPU0_PWR_CTL_WARM_RST_SHFT                              0x1
#define HWIO_APCS_APC00_CPU0_PWR_CTL_CLAMP_CPUPD_BMSK                           0x1
#define HWIO_APCS_APC00_CPU0_PWR_CTL_CLAMP_CPUPD_SHFT                           0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_CPU0_CPU_STS
 *--------------------------------------------------------------------------*/

#define APCS_APC00_CPU0_CPU_STS_REG_BASE                                (HMSS_PERIPH_BASE      + 0x002c0400)
#define APCS_APC00_CPU0_CPU_STS_REG_BASE_OFFS                           0x002c0400

#define HWIO_APCS_APC00_CPU0_PGS_STS_ADDR(x)                            ((x) + 0x00000000)
#define HWIO_APCS_APC00_CPU0_PGS_STS_OFFS                               (0x00000000)
#define HWIO_APCS_APC00_CPU0_PGS_STS_RMSK                                 0xfff373
#define HWIO_APCS_APC00_CPU0_PGS_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PGS_STS_ADDR(x), HWIO_APCS_APC00_CPU0_PGS_STS_RMSK)
#define HWIO_APCS_APC00_CPU0_PGS_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PGS_STS_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_PGS_STS_DLY_CNT_BMSK                         0xff0000
#define HWIO_APCS_APC00_CPU0_PGS_STS_DLY_CNT_SHFT                             0x10
#define HWIO_APCS_APC00_CPU0_PGS_STS_STEADY_SLEEP_BMSK                      0x8000
#define HWIO_APCS_APC00_CPU0_PGS_STS_STEADY_SLEEP_SHFT                         0xf
#define HWIO_APCS_APC00_CPU0_PGS_STS_STEADY_ACTIVE_BMSK                     0x4000
#define HWIO_APCS_APC00_CPU0_PGS_STS_STEADY_ACTIVE_SHFT                        0xe
#define HWIO_APCS_APC00_CPU0_PGS_STS_SPM_RET_BMSK                           0x2000
#define HWIO_APCS_APC00_CPU0_PGS_STS_SPM_RET_SHFT                              0xd
#define HWIO_APCS_APC00_CPU0_PGS_STS_SPM_PC_BMSK                            0x1000
#define HWIO_APCS_APC00_CPU0_PGS_STS_SPM_PC_SHFT                               0xc
#define HWIO_APCS_APC00_CPU0_PGS_STS_NEW_MODE_BMSK                           0x300
#define HWIO_APCS_APC00_CPU0_PGS_STS_NEW_MODE_SHFT                             0x8
#define HWIO_APCS_APC00_CPU0_PGS_STS_FSM_STATE_BMSK                           0x70
#define HWIO_APCS_APC00_CPU0_PGS_STS_FSM_STATE_SHFT                            0x4
#define HWIO_APCS_APC00_CPU0_PGS_STS_CURR_MODE_BMSK                            0x3
#define HWIO_APCS_APC00_CPU0_PGS_STS_CURR_MODE_SHFT                            0x0

#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_ADDR(x)                       ((x) + 0x00000004)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_OFFS                          (0x00000004)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_RMSK                          0x1ffffff3
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_GATE_STS_ADDR(x), HWIO_APCS_APC00_CPU0_PWR_GATE_STS_RMSK)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_GATE_STS_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_LDO_VREF_SEL_BMSK             0x10000000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_LDO_VREF_SEL_SHFT                   0x1c
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_LDO_BYP_BMSK                   0xfc00000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_LDO_BYP_SHFT                        0x16
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_LDO_PWR_DWN_BMSK                0x3f0000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_LDO_PWR_DWN_SHFT                    0x10
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_EN_REST_OUTER_BMSK                0xfc00
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_EN_REST_OUTER_SHFT                   0xa
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_EN_REST_INNER_BMSK                 0x3f0
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_EN_REST_INNER_SHFT                   0x4
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_EN_FEW_BMSK                          0x3
#define HWIO_APCS_APC00_CPU0_PWR_GATE_STS_EN_FEW_SHFT                          0x0

#define HWIO_APCS_APC00_CPU0_MAS_STS_ADDR(x)                            ((x) + 0x00000040)
#define HWIO_APCS_APC00_CPU0_MAS_STS_OFFS                               (0x00000040)
#define HWIO_APCS_APC00_CPU0_MAS_STS_RMSK                                 0xfff373
#define HWIO_APCS_APC00_CPU0_MAS_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_MAS_STS_ADDR(x), HWIO_APCS_APC00_CPU0_MAS_STS_RMSK)
#define HWIO_APCS_APC00_CPU0_MAS_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_MAS_STS_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_MAS_STS_TMR_CNT_BMSK                         0xff0000
#define HWIO_APCS_APC00_CPU0_MAS_STS_TMR_CNT_SHFT                             0x10
#define HWIO_APCS_APC00_CPU0_MAS_STS_STEADY_SLEEP_BMSK                      0x8000
#define HWIO_APCS_APC00_CPU0_MAS_STS_STEADY_SLEEP_SHFT                         0xf
#define HWIO_APCS_APC00_CPU0_MAS_STS_STEADY_ACTIVE_BMSK                     0x4000
#define HWIO_APCS_APC00_CPU0_MAS_STS_STEADY_ACTIVE_SHFT                        0xe
#define HWIO_APCS_APC00_CPU0_MAS_STS_SPM_RET_BMSK                           0x2000
#define HWIO_APCS_APC00_CPU0_MAS_STS_SPM_RET_SHFT                              0xd
#define HWIO_APCS_APC00_CPU0_MAS_STS_SPM_PC_BMSK                            0x1000
#define HWIO_APCS_APC00_CPU0_MAS_STS_SPM_PC_SHFT                               0xc
#define HWIO_APCS_APC00_CPU0_MAS_STS_NEW_MODE_BMSK                           0x300
#define HWIO_APCS_APC00_CPU0_MAS_STS_NEW_MODE_SHFT                             0x8
#define HWIO_APCS_APC00_CPU0_MAS_STS_FSM_STATE_BMSK                           0x70
#define HWIO_APCS_APC00_CPU0_MAS_STS_FSM_STATE_SHFT                            0x4
#define HWIO_APCS_APC00_CPU0_MAS_STS_CURR_MODE_BMSK                            0x3
#define HWIO_APCS_APC00_CPU0_MAS_STS_CURR_MODE_SHFT                            0x0

#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_ADDR(x)                        ((x) + 0x00000044)
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_OFFS                           (0x00000044)
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_RMSK                              0x70773
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_MUX_STS_ADDR(x), HWIO_APCS_APC00_CPU0_PWR_MUX_STS_RMSK)
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_MUX_STS_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_CLAMP_BMSK                        0x40000
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_CLAMP_SHFT                           0x12
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_TGL_SEL_BMSK                      0x20000
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_TGL_SEL_SHFT                         0x11
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_MEM_RET_BMSK                      0x10000
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_MEM_RET_SHFT                         0x10
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_MX_EN_REST_BMSK                     0x700
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_MX_EN_REST_SHFT                       0x8
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_APCC_EN_REST_BMSK                    0x70
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_APCC_EN_REST_SHFT                     0x4
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_EN_FEW_BMSK                           0x3
#define HWIO_APCS_APC00_CPU0_PWR_MUX_STS_EN_FEW_SHFT                           0x0

#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_ADDR(x)                        ((x) + 0x00000080)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_OFFS                           (0x00000080)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RMSK                           0xf7ffffff
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_CTL_STS_ADDR(x), HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RMSK)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_CTL_STS_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_NMM_REQ_BMSK                   0x80000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_NMM_REQ_SHFT                         0x1f
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CORE_RST_REQ_BMSK              0x40000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CORE_RST_REQ_SHFT                    0x1e
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CORE_PWR_UP_REQ_BMSK           0x20000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CORE_PWR_UP_REQ_SHFT                 0x1d
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_SYS_POR_ARST_BMSK              0x10000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_SYS_POR_ARST_SHFT                    0x1c
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_POR_ARST_BMSK                   0x4000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_POR_ARST_SHFT                        0x1a
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_FUNC_ARST_BMSK                  0x2000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_FUNC_ARST_SHFT                       0x19
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_DBG_ARST_BMSK                   0x1000000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_DBG_ARST_SHFT                        0x18
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C5_BMSK                0x800000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C5_SHFT                    0x17
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C4_BMSK                0x400000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C4_SHFT                    0x16
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C3_BMSK                0x200000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C3_SHFT                    0x15
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C2_BMSK                0x100000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C2_SHFT                    0x14
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C1_BMSK                 0x80000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C1_SHFT                    0x13
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C0_BMSK                 0x40000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_PWR_STATE_C0_SHFT                    0x12
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_WARM_RST_REQ_BMSK                 0x20000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_WARM_RST_REQ_SHFT                    0x11
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_WAKE_UP_REQ_BMSK                  0x10000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_WAKE_UP_REQ_SHFT                     0x10
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CPR_CTL_BMSK                       0x8000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CPR_CTL_SHFT                          0xf
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_SNP_HALT_ARY_INV_BMSK              0x4000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_SNP_HALT_ARY_INV_SHFT                 0xe
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_SNP_HALT_ACK_BMSK                  0x2000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_SNP_HALT_ACK_SHFT                     0xd
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_SNP_HALT_REQ_BMSK                  0x1000
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_SNP_HALT_REQ_SHFT                     0xc
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RET_RESTORE_ACK_BMSK                0x800
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RET_RESTORE_ACK_SHFT                  0xb
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RET_RESTORE_REQ_BMSK                0x400
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RET_RESTORE_REQ_SHFT                  0xa
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RET_SAVE_ACK_BMSK                   0x200
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RET_SAVE_ACK_SHFT                     0x9
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RET_SAVE_REQ_BMSK                   0x100
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RET_SAVE_REQ_SHFT                     0x8
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RST_COMPLT_ACK_BMSK                  0x80
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RST_COMPLT_ACK_SHFT                   0x7
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RST_COMPLT_REQ_BMSK                  0x40
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_RST_COMPLT_REQ_SHFT                   0x6
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_WAIT_ACK_BMSK                        0x20
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_WAIT_ACK_SHFT                         0x5
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_WAIT_REQ_BMSK                        0x10
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_WAIT_REQ_SHFT                         0x4
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_DBG_CORE_PWRD_UP_BMSK                 0x8
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_DBG_CORE_PWRD_UP_SHFT                 0x3
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CLAMP_APMPD_BMSK                      0x4
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CLAMP_APMPD_SHFT                      0x2
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CLAMP_CPUPD_BMSK                      0x2
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_CLAMP_CPUPD_SHFT                      0x1
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_FRC_CLK_OFF_BMSK                      0x1
#define HWIO_APCS_APC00_CPU0_PWR_CTL_STS_FRC_CLK_OFF_SHFT                      0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_CPU0_CPU_SW_EVENT
 *--------------------------------------------------------------------------*/

#define APCS_APC00_CPU0_CPU_SW_EVENT_REG_BASE                      (HMSS_PERIPH_BASE      + 0x00100000)
#define APCS_APC00_CPU0_CPU_SW_EVENT_REG_BASE_OFFS                 0x00100000

#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_ADDR(x)                  ((x) + 0x00000000)
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_OFFS                     (0x00000000)
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_RMSK                            0x7
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_ADDR(x), HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_RMSK)
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_ADDR(x),v)
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_ADDR(x),m,v,HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_IN(x))
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_SPM_SPARE_BMSK                  0x4
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_SPM_SPARE_SHFT                  0x2
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_SPM_WAKEUP_BMSK                 0x2
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_SPM_WAKEUP_SHFT                 0x1
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_SPM_EVENT_BMSK                  0x1
#define HWIO_APCS_APC00_CPU0_SW_SPM_EVENT_SPM_EVENT_SHFT                  0x0

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_CPU0_CPU_WAR
 *--------------------------------------------------------------------------*/

#define APCS_APC00_CPU0_CPU_WAR_REG_BASE                          (HMSS_PERIPH_BASE      + 0x00140000)
#define APCS_APC00_CPU0_CPU_WAR_REG_BASE_OFFS                     0x00140000

/*----------------------------------------------------------------------------
 * MODULE: APCS_APC00_CPU0_CPU_DBG
 *--------------------------------------------------------------------------*/

#define APCS_APC00_CPU0_CPU_DBG_REG_BASE                                        (HMSS_PERIPH_BASE      + 0x00300000)
#define APCS_APC00_CPU0_CPU_DBG_REG_BASE_OFFS                                   0x00300000

#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_ADDR(x)                              ((x) + 0x00000004)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_OFFS                                 (0x00000004)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_RMSK                                 0x9f9f0200
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_ADDR(x), HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_RMSK)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_ADDR(x),v)
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_ADDR(x),m,v,HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IN(x))
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IMEAS_LDO_ACC_TRIM_SEL_BMSK          0x80000000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IMEAS_LDO_ACC_TRIM_SEL_SHFT                0x1f
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IMEAS_LDO_ACC_TRIM_BMSK              0x1f000000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IMEAS_LDO_ACC_TRIM_SHFT                    0x18
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IMEAS_BHS_ACC_TRIM_SEL_BMSK            0x800000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IMEAS_BHS_ACC_TRIM_SEL_SHFT                0x17
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IMEAS_BHS_ACC_TRIM_BMSK                0x1f0000
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_IMEAS_BHS_ACC_TRIM_SHFT                    0x10
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_CURR_LOAD_OVERRIDE_BMSK                   0x200
#define HWIO_APCS_APC00_CPU0_PWR_GATE_DIAG_CURR_LOAD_OVERRIDE_SHFT                     0x9

#define HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_ADDR(x)                           ((x) + 0x00000008)
#define HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_OFFS                              (0x00000008)
#define HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_RMSK                                0xffffff
#define HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_IN(x)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_ADDR(x), HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_RMSK)
#define HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_INM(x, m)      \
        in_dword_masked(HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_ADDR(x), m)
#define HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_OUT(x, v)      \
        out_dword(HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_ADDR(x),v)
#define HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_ADDR(x),m,v,HWIO_APCS_APC00_CPU0_EMU_DBG_MODE_MSK_IN(x))


#endif /* __QDF2400_APCPWR_HWIO_H__ */
