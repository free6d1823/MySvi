
//-----------------------------------------------------------------------------
// Qualcomm Technologies, Inc. Proprietary
// Copyright (c) 2012-2016, Qualcomm Technologies, Inc. All rights reserved.
//
// All data and information contained in or disclosed by this document are
// confidential and proprietary information of Qualcomm Technologies, Inc. or
// its Affiliates, or their licensors, and all rights therein are expressly
// reserved. By accepting this material, the recipient agrees that this
// material and the information contained therein are held in confidence and
// in trust and will not be used, copied, reproduced in whole or in part, nor
// its contents revealed in any manner to others, without the express written
// permission of Qualcomm Technologies, Inc., or to the extent expressly
// permitted by the Technology License Agreement between Qualcomm Technologies,

//
// This technology was exported from the United States in accordance with the
// approval from the U.S. Department of Commerce, Bureau of Industry and
// Security, Export Administration Regulations (EAR).  Any re-export or
// in-country transfers of this technology is subject to U.S. Laws and
// regulations. Diversion contrary to U.S. law prohibited.
//-----------------------------------------------------------------------------

#ifndef __QSMMUV3_HWIOREG_H__
#define __QSMMUV3_HWIOREG_H__

#include "qsmmuv3_hwiobase.h"

#define QSMMU_QSMMUV3_GLOBALREG_SPACE0_REG_BASE                         (QSMMUV3_BASE      + 0x00000000)
#define QSMMU_QSMMUV3_GLOBALREG_SPACE0_REG_BASE_PHYS                    (QSMMUV3_BASE_PHYS + 0x00000000)

#define HWIO_IDR0_ADDR(x)                                               ((x) + 0x00000000)
#define HWIO_IDR0_PHYS(x)                                               ((x) + 0x00000000)
#define HWIO_IDR0_RMSK                                                  0x1f7fffff
#define HWIO_IDR0_POR                                                   0x081cf6bf
#define HWIO_IDR0_POR_RMSK                                              0xffffffff
#define HWIO_IDR0_ATTR                                                         0x1
#define HWIO_IDR0_IN(x)      \
        in_dword_masked(HWIO_IDR0_ADDR(x), HWIO_IDR0_RMSK)
#define HWIO_IDR0_INM(x, m)      \
        in_dword_masked(HWIO_IDR0_ADDR(x), m)
#define HWIO_IDR0_ST_LEVEL_BMSK                                         0x18000000
#define HWIO_IDR0_ST_LEVEL_SHFT                                               0x1b
#define HWIO_IDR0_TERM_MODEL_BMSK                                        0x4000000
#define HWIO_IDR0_TERM_MODEL_SHFT                                             0x1a
#define HWIO_IDR0_STALL_MODEL_BMSK                                       0x3000000
#define HWIO_IDR0_STALL_MODEL_SHFT                                            0x18
#define HWIO_IDR0_TTENDIAN_BMSK                                           0x600000
#define HWIO_IDR0_TTENDIAN_SHFT                                               0x15
#define HWIO_IDR0_VATOS_BMSK                                              0x100000
#define HWIO_IDR0_VATOS_SHFT                                                  0x14
#define HWIO_IDR0_CD2L_BMSK                                                0x80000
#define HWIO_IDR0_CD2L_SHFT                                                   0x13
#define HWIO_IDR0_VMID16_BMSK                                              0x40000
#define HWIO_IDR0_VMID16_SHFT                                                 0x12
#define HWIO_IDR0_VMW_BMSK                                                 0x20000
#define HWIO_IDR0_VMW_SHFT                                                    0x11
#define HWIO_IDR0_PRI_BMSK                                                 0x10000
#define HWIO_IDR0_PRI_SHFT                                                    0x10
#define HWIO_IDR0_ATOS_BMSK                                                 0x8000
#define HWIO_IDR0_ATOS_SHFT                                                    0xf
#define HWIO_IDR0_SEV_BMSK                                                  0x4000
#define HWIO_IDR0_SEV_SHFT                                                     0xe
#define HWIO_IDR0_MSI_BMSK                                                  0x2000
#define HWIO_IDR0_MSI_SHFT                                                     0xd
#define HWIO_IDR0_ASID16_BMSK                                               0x1000
#define HWIO_IDR0_ASID16_SHFT                                                  0xc
#define HWIO_IDR0_NS1ATS_BMSK                                                0x800
#define HWIO_IDR0_NS1ATS_SHFT                                                  0xb
#define HWIO_IDR0_ATS_BMSK                                                   0x400
#define HWIO_IDR0_ATS_SHFT                                                     0xa
#define HWIO_IDR0_HYP_BMSK                                                   0x200
#define HWIO_IDR0_HYP_SHFT                                                     0x9
#define HWIO_IDR0_DORMHINT_BMSK                                              0x100
#define HWIO_IDR0_DORMHINT_SHFT                                                0x8
#define HWIO_IDR0_HTTU_BMSK                                                   0xc0
#define HWIO_IDR0_HTTU_SHFT                                                    0x6
#define HWIO_IDR0_BTM_BMSK                                                    0x20
#define HWIO_IDR0_BTM_SHFT                                                     0x5
#define HWIO_IDR0_COHACC_BMSK                                                 0x10
#define HWIO_IDR0_COHACC_SHFT                                                  0x4
#define HWIO_IDR0_TTF_BMSK                                                     0xc
#define HWIO_IDR0_TTF_SHFT                                                     0x2
#define HWIO_IDR0_S1P_BMSK                                                     0x2
#define HWIO_IDR0_S1P_SHFT                                                     0x1
#define HWIO_IDR0_S2P_BMSK                                                     0x1
#define HWIO_IDR0_S2P_SHFT                                                     0x0

#define HWIO_IDR1_ADDR(x)                                               ((x) + 0x00000004)
#define HWIO_IDR1_PHYS(x)                                               ((x) + 0x00000004)
#define HWIO_IDR1_RMSK                                                  0x7fffffff
#define HWIO_IDR1_POR                                                   0x0e730510
#define HWIO_IDR1_POR_RMSK                                              0xffffffff
#define HWIO_IDR1_ATTR                                                         0x1
#define HWIO_IDR1_IN(x)      \
        in_dword_masked(HWIO_IDR1_ADDR(x), HWIO_IDR1_RMSK)
#define HWIO_IDR1_INM(x, m)      \
        in_dword_masked(HWIO_IDR1_ADDR(x), m)
#define HWIO_IDR1_TABLES_PRESET_BMSK                                    0x40000000
#define HWIO_IDR1_TABLES_PRESET_SHFT                                          0x1e
#define HWIO_IDR1_QUEUES_PRESET_BMSK                                    0x20000000
#define HWIO_IDR1_QUEUES_PRESET_SHFT                                          0x1d
#define HWIO_IDR1_REL_BMSK                                              0x10000000
#define HWIO_IDR1_REL_SHFT                                                    0x1c
#define HWIO_IDR1_ATTR_TYPES_OVR_BMSK                                    0x8000000
#define HWIO_IDR1_ATTR_TYPES_OVR_SHFT                                         0x1b
#define HWIO_IDR1_ATTR_PERM_OVR_BMSK                                     0x4000000
#define HWIO_IDR1_ATTR_PERM_OVR_SHFT                                          0x1a
#define HWIO_IDR1_CMDQS_BMSK                                             0x3e00000
#define HWIO_IDR1_CMDQS_SHFT                                                  0x15
#define HWIO_IDR1_EVENTQS_BMSK                                            0x1f0000
#define HWIO_IDR1_EVENTQS_SHFT                                                0x10
#define HWIO_IDR1_PRIQS_BMSK                                                0xf800
#define HWIO_IDR1_PRIQS_SHFT                                                   0xb
#define HWIO_IDR1_SSIDSIZE_BMSK                                              0x7c0
#define HWIO_IDR1_SSIDSIZE_SHFT                                                0x6
#define HWIO_IDR1_SIDSIZE_BMSK                                                0x3f
#define HWIO_IDR1_SIDSIZE_SHFT                                                 0x0

#define HWIO_IDR2_ADDR(x)                                               ((x) + 0x00000008)
#define HWIO_IDR2_PHYS(x)                                               ((x) + 0x00000008)
#define HWIO_IDR2_RMSK                                                       0x3ff
#define HWIO_IDR2_POR                                                   0x00000001
#define HWIO_IDR2_POR_RMSK                                              0xffffffff
#define HWIO_IDR2_ATTR                                                         0x1
#define HWIO_IDR2_IN(x)      \
        in_dword_masked(HWIO_IDR2_ADDR(x), HWIO_IDR2_RMSK)
#define HWIO_IDR2_INM(x, m)      \
        in_dword_masked(HWIO_IDR2_ADDR(x), m)
#define HWIO_IDR2_BA_VATOS_BMSK                                              0x3ff
#define HWIO_IDR2_BA_VATOS_SHFT                                                0x0

#define HWIO_IDR3_ADDR(x)                                               ((x) + 0x0000000c)
#define HWIO_IDR3_PHYS(x)                                               ((x) + 0x0000000c)
#define HWIO_IDR3_RMSK                                                         0x4
#define HWIO_IDR3_POR                                                   0x00000000
#define HWIO_IDR3_POR_RMSK                                              0xffffffff
#define HWIO_IDR3_ATTR                                                         0x1
#define HWIO_IDR3_IN(x)      \
        in_dword_masked(HWIO_IDR3_ADDR(x), HWIO_IDR3_RMSK)
#define HWIO_IDR3_INM(x, m)      \
        in_dword_masked(HWIO_IDR3_ADDR(x), m)
#define HWIO_IDR3_HAD_BMSK                                                     0x4
#define HWIO_IDR3_HAD_SHFT                                                     0x2

#define HWIO_IDR4_ADDR(x)                                               ((x) + 0x00000010)
#define HWIO_IDR4_PHYS(x)                                               ((x) + 0x00000010)
#define HWIO_IDR4_RMSK                                                    0xff0007
#define HWIO_IDR4_POR                                                   0x00320002
#define HWIO_IDR4_POR_RMSK                                              0xffffffff
#define HWIO_IDR4_ATTR                                                         0x1
#define HWIO_IDR4_IN(x)      \
        in_dword_masked(HWIO_IDR4_ADDR(x), HWIO_IDR4_RMSK)
#define HWIO_IDR4_INM(x, m)      \
        in_dword_masked(HWIO_IDR4_ADDR(x), m)
#define HWIO_IDR4_BA_PMCG_PG1_BMSK                                        0xf00000
#define HWIO_IDR4_BA_PMCG_PG1_SHFT                                            0x14
#define HWIO_IDR4_BA_PMCG_PG0_BMSK                                         0xf0000
#define HWIO_IDR4_BA_PMCG_PG0_SHFT                                            0x10
#define HWIO_IDR4_QACT_QAD_RST_VAL_BMSK                                        0x4
#define HWIO_IDR4_QACT_QAD_RST_VAL_SHFT                                        0x2
#define HWIO_IDR4_QACT_SSD_RST_VAL_BMSK                                        0x2
#define HWIO_IDR4_QACT_SSD_RST_VAL_SHFT                                        0x1
#define HWIO_IDR4_QACT_RST_EN_BMSK                                             0x1
#define HWIO_IDR4_QACT_RST_EN_SHFT                                             0x0

#define HWIO_IDR5_ADDR(x)                                               ((x) + 0x00000014)
#define HWIO_IDR5_PHYS(x)                                               ((x) + 0x00000014)
#define HWIO_IDR5_RMSK                                                  0xffff0077
#define HWIO_IDR5_POR                                                   0x00080074
#define HWIO_IDR5_POR_RMSK                                              0xffffffff
#define HWIO_IDR5_ATTR                                                         0x1
#define HWIO_IDR5_IN(x)      \
        in_dword_masked(HWIO_IDR5_ADDR(x), HWIO_IDR5_RMSK)
#define HWIO_IDR5_INM(x, m)      \
        in_dword_masked(HWIO_IDR5_ADDR(x), m)
#define HWIO_IDR5_STALL_MAX_BMSK                                        0xffff0000
#define HWIO_IDR5_STALL_MAX_SHFT                                              0x10
#define HWIO_IDR5_GRAN64K_BMSK                                                0x40
#define HWIO_IDR5_GRAN64K_SHFT                                                 0x6
#define HWIO_IDR5_GRAN16K_BMSK                                                0x20
#define HWIO_IDR5_GRAN16K_SHFT                                                 0x5
#define HWIO_IDR5_GRAN4K_BMSK                                                 0x10
#define HWIO_IDR5_GRAN4K_SHFT                                                  0x4
#define HWIO_IDR5_OAS_BMSK                                                     0x7
#define HWIO_IDR5_OAS_SHFT                                                     0x0

#define HWIO_IIDR_ADDR(x)                                               ((x) + 0x00000018)
#define HWIO_IIDR_PHYS(x)                                               ((x) + 0x00000018)
#define HWIO_IIDR_RMSK                                                  0xffffffff
#define HWIO_IIDR_POR                                                   0x04020070
#define HWIO_IIDR_POR_RMSK                                              0xffffffff
#define HWIO_IIDR_ATTR                                                         0x1
#define HWIO_IIDR_IN(x)      \
        in_dword_masked(HWIO_IIDR_ADDR(x), HWIO_IIDR_RMSK)
#define HWIO_IIDR_INM(x, m)      \
        in_dword_masked(HWIO_IIDR_ADDR(x), m)
#define HWIO_IIDR_PRODUCTID_BMSK                                        0xfff00000
#define HWIO_IIDR_PRODUCTID_SHFT                                              0x14
#define HWIO_IIDR_VARIANT_BMSK                                             0xf0000
#define HWIO_IIDR_VARIANT_SHFT                                                0x10
#define HWIO_IIDR_REVISION_BMSK                                             0xf000
#define HWIO_IIDR_REVISION_SHFT                                                0xc
#define HWIO_IIDR_IMPLEMENTER_BMSK                                           0xfff
#define HWIO_IIDR_IMPLEMENTER_SHFT                                             0x0

#define HWIO_AIDR_ADDR(x)                                               ((x) + 0x0000001c)
#define HWIO_AIDR_PHYS(x)                                               ((x) + 0x0000001c)
#define HWIO_AIDR_RMSK                                                        0xff
#define HWIO_AIDR_POR                                                   0x00000000
#define HWIO_AIDR_POR_RMSK                                              0xffffffff
#define HWIO_AIDR_ATTR                                                         0x1
#define HWIO_AIDR_IN(x)      \
        in_dword_masked(HWIO_AIDR_ADDR(x), HWIO_AIDR_RMSK)
#define HWIO_AIDR_INM(x, m)      \
        in_dword_masked(HWIO_AIDR_ADDR(x), m)
#define HWIO_AIDR_ARCHMAJORREV_BMSK                                           0xf0
#define HWIO_AIDR_ARCHMAJORREV_SHFT                                            0x4
#define HWIO_AIDR_ARCHMINORREV_BMSK                                            0xf
#define HWIO_AIDR_ARCHMINORREV_SHFT                                            0x0

#define HWIO_CR0_ADDR(x)                                                ((x) + 0x00000020)
#define HWIO_CR0_PHYS(x)                                                ((x) + 0x00000020)
#define HWIO_CR0_RMSK                                                        0x1df
#define HWIO_CR0_POR                                                    0x00000000
#define HWIO_CR0_POR_RMSK                                               0xffffffff
#define HWIO_CR0_ATTR                                                          0x3
#define HWIO_CR0_IN(x)      \
        in_dword_masked(HWIO_CR0_ADDR(x), HWIO_CR0_RMSK)
#define HWIO_CR0_INM(x, m)      \
        in_dword_masked(HWIO_CR0_ADDR(x), m)
#define HWIO_CR0_OUT(x, v)      \
        out_dword(HWIO_CR0_ADDR(x),v)
#define HWIO_CR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CR0_ADDR(x),m,v,HWIO_CR0_IN(x))
#define HWIO_CR0_VMW_BMSK                                                    0x1c0
#define HWIO_CR0_VMW_SHFT                                                      0x6
#define HWIO_CR0_ATSCHK_BMSK                                                  0x10
#define HWIO_CR0_ATSCHK_SHFT                                                   0x4
#define HWIO_CR0_CMDQEN_BMSK                                                   0x8
#define HWIO_CR0_CMDQEN_SHFT                                                   0x3
#define HWIO_CR0_EVENTQEN_BMSK                                                 0x4
#define HWIO_CR0_EVENTQEN_SHFT                                                 0x2
#define HWIO_CR0_PRIQEN_BMSK                                                   0x2
#define HWIO_CR0_PRIQEN_SHFT                                                   0x1
#define HWIO_CR0_SMMUEN_BMSK                                                   0x1
#define HWIO_CR0_SMMUEN_SHFT                                                   0x0

#define HWIO_CR0ACK_ADDR(x)                                             ((x) + 0x00000024)
#define HWIO_CR0ACK_PHYS(x)                                             ((x) + 0x00000024)
#define HWIO_CR0ACK_RMSK                                                     0x1df
#define HWIO_CR0ACK_POR                                                 0x00000000
#define HWIO_CR0ACK_POR_RMSK                                            0xffffffff
#define HWIO_CR0ACK_ATTR                                                       0x1
#define HWIO_CR0ACK_IN(x)      \
        in_dword_masked(HWIO_CR0ACK_ADDR(x), HWIO_CR0ACK_RMSK)
#define HWIO_CR0ACK_INM(x, m)      \
        in_dword_masked(HWIO_CR0ACK_ADDR(x), m)
#define HWIO_CR0ACK_VMW_BMSK                                                 0x1c0
#define HWIO_CR0ACK_VMW_SHFT                                                   0x6
#define HWIO_CR0ACK_ATSCHK_BMSK                                               0x10
#define HWIO_CR0ACK_ATSCHK_SHFT                                                0x4
#define HWIO_CR0ACK_CMDQEN_BMSK                                                0x8
#define HWIO_CR0ACK_CMDQEN_SHFT                                                0x3
#define HWIO_CR0ACK_EVENTQEN_BMSK                                              0x4
#define HWIO_CR0ACK_EVENTQEN_SHFT                                              0x2
#define HWIO_CR0ACK_PRIQEN_BMSK                                                0x2
#define HWIO_CR0ACK_PRIQEN_SHFT                                                0x1
#define HWIO_CR0ACK_SMMUEN_BMSK                                                0x1
#define HWIO_CR0ACK_SMMUEN_SHFT                                                0x0

#define HWIO_CR1_ADDR(x)                                                ((x) + 0x00000028)
#define HWIO_CR1_PHYS(x)                                                ((x) + 0x00000028)
#define HWIO_CR1_RMSK                                                        0xfff
#define HWIO_CR1_POR                                                    0x00000000
#define HWIO_CR1_POR_RMSK                                               0xffffffff
#define HWIO_CR1_ATTR                                                          0x3
#define HWIO_CR1_IN(x)      \
        in_dword_masked(HWIO_CR1_ADDR(x), HWIO_CR1_RMSK)
#define HWIO_CR1_INM(x, m)      \
        in_dword_masked(HWIO_CR1_ADDR(x), m)
#define HWIO_CR1_OUT(x, v)      \
        out_dword(HWIO_CR1_ADDR(x),v)
#define HWIO_CR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CR1_ADDR(x),m,v,HWIO_CR1_IN(x))
#define HWIO_CR1_TABLE_SH_BMSK                                               0xc00
#define HWIO_CR1_TABLE_SH_SHFT                                                 0xa
#define HWIO_CR1_TABLE_OC_BMSK                                               0x300
#define HWIO_CR1_TABLE_OC_SHFT                                                 0x8
#define HWIO_CR1_TABLE_IC_BMSK                                                0xc0
#define HWIO_CR1_TABLE_IC_SHFT                                                 0x6
#define HWIO_CR1_QUEUE_SH_BMSK                                                0x30
#define HWIO_CR1_QUEUE_SH_SHFT                                                 0x4
#define HWIO_CR1_QUEUE_OC_BMSK                                                 0xc
#define HWIO_CR1_QUEUE_OC_SHFT                                                 0x2
#define HWIO_CR1_QUEUE_IC_BMSK                                                 0x3
#define HWIO_CR1_QUEUE_IC_SHFT                                                 0x0

#define HWIO_CR2_ADDR(x)                                                ((x) + 0x0000002c)
#define HWIO_CR2_PHYS(x)                                                ((x) + 0x0000002c)
#define HWIO_CR2_RMSK                                                          0x7
#define HWIO_CR2_POR                                                    0x00000004
#define HWIO_CR2_POR_RMSK                                               0xffffffff
#define HWIO_CR2_ATTR                                                          0x3
#define HWIO_CR2_IN(x)      \
        in_dword_masked(HWIO_CR2_ADDR(x), HWIO_CR2_RMSK)
#define HWIO_CR2_INM(x, m)      \
        in_dword_masked(HWIO_CR2_ADDR(x), m)
#define HWIO_CR2_OUT(x, v)      \
        out_dword(HWIO_CR2_ADDR(x),v)
#define HWIO_CR2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CR2_ADDR(x),m,v,HWIO_CR2_IN(x))
#define HWIO_CR2_PTM_BMSK                                                      0x4
#define HWIO_CR2_PTM_SHFT                                                      0x2
#define HWIO_CR2_RECINVSID_BMSK                                                0x2
#define HWIO_CR2_RECINVSID_SHFT                                                0x1
#define HWIO_CR2_E2H_BMSK                                                      0x1
#define HWIO_CR2_E2H_SHFT                                                      0x0

#define HWIO_STATUSR_ADDR(x)                                            ((x) + 0x00000040)
#define HWIO_STATUSR_PHYS(x)                                            ((x) + 0x00000040)
#define HWIO_STATUSR_RMSK                                                      0x1
#define HWIO_STATUSR_POR                                                0x00000000
#define HWIO_STATUSR_POR_RMSK                                           0xffffffff
#define HWIO_STATUSR_ATTR                                                      0x1
#define HWIO_STATUSR_IN(x)      \
        in_dword_masked(HWIO_STATUSR_ADDR(x), HWIO_STATUSR_RMSK)
#define HWIO_STATUSR_INM(x, m)      \
        in_dword_masked(HWIO_STATUSR_ADDR(x), m)
#define HWIO_STATUSR_DORMANT_BMSK                                              0x1
#define HWIO_STATUSR_DORMANT_SHFT                                              0x0

#define HWIO_GBPA_ADDR(x)                                               ((x) + 0x00000044)
#define HWIO_GBPA_PHYS(x)                                               ((x) + 0x00000044)
#define HWIO_GBPA_RMSK                                                  0x801f3f1f
#define HWIO_GBPA_POR                                                   0x00001000
#define HWIO_GBPA_POR_RMSK                                              0xffffffff
#define HWIO_GBPA_ATTR                                                         0x3
#define HWIO_GBPA_IN(x)      \
        in_dword_masked(HWIO_GBPA_ADDR(x), HWIO_GBPA_RMSK)
#define HWIO_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_GBPA_ADDR(x), m)
#define HWIO_GBPA_OUT(x, v)      \
        out_dword(HWIO_GBPA_ADDR(x),v)
#define HWIO_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GBPA_ADDR(x),m,v,HWIO_GBPA_IN(x))
#define HWIO_GBPA_UPDATE_BMSK                                           0x80000000
#define HWIO_GBPA_UPDATE_SHFT                                                 0x1f
#define HWIO_GBPA_ABORT_BMSK                                              0x100000
#define HWIO_GBPA_ABORT_SHFT                                                  0x14
#define HWIO_GBPA_INSTCFG_BMSK                                             0xc0000
#define HWIO_GBPA_INSTCFG_SHFT                                                0x12
#define HWIO_GBPA_PRIVCFG_BMSK                                             0x30000
#define HWIO_GBPA_PRIVCFG_SHFT                                                0x10
#define HWIO_GBPA_SHCFG_BMSK                                                0x3000
#define HWIO_GBPA_SHCFG_SHFT                                                   0xc
#define HWIO_GBPA_ALLOCCFG_BMSK                                              0xf00
#define HWIO_GBPA_ALLOCCFG_SHFT                                                0x8
#define HWIO_GBPA_MTCFG_BMSK                                                  0x10
#define HWIO_GBPA_MTCFG_SHFT                                                   0x4
#define HWIO_GBPA_MEMATTR_BMSK                                                 0xf
#define HWIO_GBPA_MEMATTR_SHFT                                                 0x0

#define HWIO_AGBPA_ADDR(x)                                              ((x) + 0x00000048)
#define HWIO_AGBPA_PHYS(x)                                              ((x) + 0x00000048)
#define HWIO_AGBPA_RMSK                                                    0x7ffff
#define HWIO_AGBPA_POR                                                  0x00000000
#define HWIO_AGBPA_POR_RMSK                                             0xffffffff
#define HWIO_AGBPA_ATTR                                                        0x3
#define HWIO_AGBPA_IN(x)      \
        in_dword_masked(HWIO_AGBPA_ADDR(x), HWIO_AGBPA_RMSK)
#define HWIO_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_AGBPA_ADDR(x), m)
#define HWIO_AGBPA_OUT(x, v)      \
        out_dword(HWIO_AGBPA_ADDR(x),v)
#define HWIO_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_AGBPA_ADDR(x),m,v,HWIO_AGBPA_IN(x))
#define HWIO_AGBPA_REQPRIORITY_BMSK                                        0x60000
#define HWIO_AGBPA_REQPRIORITY_SHFT                                           0x11
#define HWIO_AGBPA_REQPRIORITY_REPLACE_BMSK                                0x10000
#define HWIO_AGBPA_REQPRIORITY_REPLACE_SHFT                                   0x10
#define HWIO_AGBPA_BPVMID_BMSK                                              0xffff
#define HWIO_AGBPA_BPVMID_SHFT                                                 0x0

#define HWIO_IRQ_CTRL_ADDR(x)                                           ((x) + 0x00000050)
#define HWIO_IRQ_CTRL_PHYS(x)                                           ((x) + 0x00000050)
#define HWIO_IRQ_CTRL_RMSK                                                     0x7
#define HWIO_IRQ_CTRL_POR                                               0x00000000
#define HWIO_IRQ_CTRL_POR_RMSK                                          0xffffffff
#define HWIO_IRQ_CTRL_ATTR                                                     0x3
#define HWIO_IRQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_IRQ_CTRL_ADDR(x), HWIO_IRQ_CTRL_RMSK)
#define HWIO_IRQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_IRQ_CTRL_ADDR(x), m)
#define HWIO_IRQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_IRQ_CTRL_ADDR(x),v)
#define HWIO_IRQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_IRQ_CTRL_ADDR(x),m,v,HWIO_IRQ_CTRL_IN(x))
#define HWIO_IRQ_CTRL_EVENTQ_IRQEN_BMSK                                        0x4
#define HWIO_IRQ_CTRL_EVENTQ_IRQEN_SHFT                                        0x2
#define HWIO_IRQ_CTRL_PRIQ_IRQEN_BMSK                                          0x2
#define HWIO_IRQ_CTRL_PRIQ_IRQEN_SHFT                                          0x1
#define HWIO_IRQ_CTRL_GERROR_IRQEN_BMSK                                        0x1
#define HWIO_IRQ_CTRL_GERROR_IRQEN_SHFT                                        0x0

#define HWIO_IRQ_CTRLACK_ADDR(x)                                        ((x) + 0x00000054)
#define HWIO_IRQ_CTRLACK_PHYS(x)                                        ((x) + 0x00000054)
#define HWIO_IRQ_CTRLACK_RMSK                                                  0x7
#define HWIO_IRQ_CTRLACK_POR                                            0x00000000
#define HWIO_IRQ_CTRLACK_POR_RMSK                                       0xffffffff
#define HWIO_IRQ_CTRLACK_ATTR                                                  0x1
#define HWIO_IRQ_CTRLACK_IN(x)      \
        in_dword_masked(HWIO_IRQ_CTRLACK_ADDR(x), HWIO_IRQ_CTRLACK_RMSK)
#define HWIO_IRQ_CTRLACK_INM(x, m)      \
        in_dword_masked(HWIO_IRQ_CTRLACK_ADDR(x), m)
#define HWIO_IRQ_CTRLACK_EVENTQ_IRQEN_BMSK                                     0x4
#define HWIO_IRQ_CTRLACK_EVENTQ_IRQEN_SHFT                                     0x2
#define HWIO_IRQ_CTRLACK_PRIQ_IRQEN_BMSK                                       0x2
#define HWIO_IRQ_CTRLACK_PRIQ_IRQEN_SHFT                                       0x1
#define HWIO_IRQ_CTRLACK_GERROR_IRQEN_BMSK                                     0x1
#define HWIO_IRQ_CTRLACK_GERROR_IRQEN_SHFT                                     0x0

#define HWIO_GERROR_ADDR(x)                                             ((x) + 0x00000060)
#define HWIO_GERROR_PHYS(x)                                             ((x) + 0x00000060)
#define HWIO_GERROR_RMSK                                                     0x1fd
#define HWIO_GERROR_POR                                                 0x00000000
#define HWIO_GERROR_POR_RMSK                                            0xffffffff
#define HWIO_GERROR_ATTR                                                       0x1
#define HWIO_GERROR_IN(x)      \
        in_dword_masked(HWIO_GERROR_ADDR(x), HWIO_GERROR_RMSK)
#define HWIO_GERROR_INM(x, m)      \
        in_dword_masked(HWIO_GERROR_ADDR(x), m)
#define HWIO_GERROR_SFM_ERR_BMSK                                             0x100
#define HWIO_GERROR_SFM_ERR_SHFT                                               0x8
#define HWIO_GERROR_MSI_GERROR_ABT_ERR_BMSK                                   0x80
#define HWIO_GERROR_MSI_GERROR_ABT_ERR_SHFT                                    0x7
#define HWIO_GERROR_MSI_PRIQ_ABT_ERR_BMSK                                     0x40
#define HWIO_GERROR_MSI_PRIQ_ABT_ERR_SHFT                                      0x6
#define HWIO_GERROR_MSI_EVENTQ_ABT_ERR_BMSK                                   0x20
#define HWIO_GERROR_MSI_EVENTQ_ABT_ERR_SHFT                                    0x5
#define HWIO_GERROR_MSI_CMDQ_ABT_ERR_BMSK                                     0x10
#define HWIO_GERROR_MSI_CMDQ_ABT_ERR_SHFT                                      0x4
#define HWIO_GERROR_PRIQ_ABT_ERR_BMSK                                          0x8
#define HWIO_GERROR_PRIQ_ABT_ERR_SHFT                                          0x3
#define HWIO_GERROR_EVENTQ_ABT_ERR_BMSK                                        0x4
#define HWIO_GERROR_EVENTQ_ABT_ERR_SHFT                                        0x2
#define HWIO_GERROR_CMDQ_ERR_BMSK                                              0x1
#define HWIO_GERROR_CMDQ_ERR_SHFT                                              0x0

#define HWIO_GERRORN_ADDR(x)                                            ((x) + 0x00000064)
#define HWIO_GERRORN_PHYS(x)                                            ((x) + 0x00000064)
#define HWIO_GERRORN_RMSK                                                    0x1fd
#define HWIO_GERRORN_POR                                                0x00000000
#define HWIO_GERRORN_POR_RMSK                                           0xffffffff
#define HWIO_GERRORN_ATTR                                                      0x3
#define HWIO_GERRORN_IN(x)      \
        in_dword_masked(HWIO_GERRORN_ADDR(x), HWIO_GERRORN_RMSK)
#define HWIO_GERRORN_INM(x, m)      \
        in_dword_masked(HWIO_GERRORN_ADDR(x), m)
#define HWIO_GERRORN_OUT(x, v)      \
        out_dword(HWIO_GERRORN_ADDR(x),v)
#define HWIO_GERRORN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GERRORN_ADDR(x),m,v,HWIO_GERRORN_IN(x))
#define HWIO_GERRORN_SFM_ERR_BMSK                                            0x100
#define HWIO_GERRORN_SFM_ERR_SHFT                                              0x8
#define HWIO_GERRORN_MSI_GERROR_ABT_ERR_BMSK                                  0x80
#define HWIO_GERRORN_MSI_GERROR_ABT_ERR_SHFT                                   0x7
#define HWIO_GERRORN_MSI_PRIQ_ABT_ERR_BMSK                                    0x40
#define HWIO_GERRORN_MSI_PRIQ_ABT_ERR_SHFT                                     0x6
#define HWIO_GERRORN_MSI_EVENTQ_ABT_ERR_BMSK                                  0x20
#define HWIO_GERRORN_MSI_EVENTQ_ABT_ERR_SHFT                                   0x5
#define HWIO_GERRORN_MSI_CMDQ_ABT_ERR_BMSK                                    0x10
#define HWIO_GERRORN_MSI_CMDQ_ABT_ERR_SHFT                                     0x4
#define HWIO_GERRORN_PRIQ_ABT_ERR_BMSK                                         0x8
#define HWIO_GERRORN_PRIQ_ABT_ERR_SHFT                                         0x3
#define HWIO_GERRORN_EVENTQ_ABT_ERR_BMSK                                       0x4
#define HWIO_GERRORN_EVENTQ_ABT_ERR_SHFT                                       0x2
#define HWIO_GERRORN_CMDQ_ERR_BMSK                                             0x1
#define HWIO_GERRORN_CMDQ_ERR_SHFT                                             0x0

#define HWIO_GERROR_IRQ_CFG0_L_ADDR(x)                                  ((x) + 0x00000068)
#define HWIO_GERROR_IRQ_CFG0_L_PHYS(x)                                  ((x) + 0x00000068)
#define HWIO_GERROR_IRQ_CFG0_L_RMSK                                     0xfffffffc
#define HWIO_GERROR_IRQ_CFG0_L_POR                                      0x00000000
#define HWIO_GERROR_IRQ_CFG0_L_POR_RMSK                                 0xffffffff
#define HWIO_GERROR_IRQ_CFG0_L_ATTR                                            0x3
#define HWIO_GERROR_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_GERROR_IRQ_CFG0_L_ADDR(x), HWIO_GERROR_IRQ_CFG0_L_RMSK)
#define HWIO_GERROR_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_GERROR_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_GERROR_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_GERROR_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_GERROR_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GERROR_IRQ_CFG0_L_ADDR(x),m,v,HWIO_GERROR_IRQ_CFG0_L_IN(x))
#define HWIO_GERROR_IRQ_CFG0_L_ADDR_31_2_BMSK                           0xfffffffc
#define HWIO_GERROR_IRQ_CFG0_L_ADDR_31_2_SHFT                                  0x2

#define HWIO_GERROR_IRQ_CFG0_H_ADDR(x)                                  ((x) + 0x0000006c)
#define HWIO_GERROR_IRQ_CFG0_H_PHYS(x)                                  ((x) + 0x0000006c)
#define HWIO_GERROR_IRQ_CFG0_H_RMSK                                         0xffff
#define HWIO_GERROR_IRQ_CFG0_H_POR                                      0x00000000
#define HWIO_GERROR_IRQ_CFG0_H_POR_RMSK                                 0xffffffff
#define HWIO_GERROR_IRQ_CFG0_H_ATTR                                            0x3
#define HWIO_GERROR_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_GERROR_IRQ_CFG0_H_ADDR(x), HWIO_GERROR_IRQ_CFG0_H_RMSK)
#define HWIO_GERROR_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_GERROR_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_GERROR_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_GERROR_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_GERROR_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GERROR_IRQ_CFG0_H_ADDR(x),m,v,HWIO_GERROR_IRQ_CFG0_H_IN(x))
#define HWIO_GERROR_IRQ_CFG0_H_ADDR_47_32_BMSK                              0xffff
#define HWIO_GERROR_IRQ_CFG0_H_ADDR_47_32_SHFT                                 0x0

#define HWIO_GERROR_IRQ_CFG1_ADDR(x)                                    ((x) + 0x00000070)
#define HWIO_GERROR_IRQ_CFG1_PHYS(x)                                    ((x) + 0x00000070)
#define HWIO_GERROR_IRQ_CFG1_RMSK                                       0xffffffff
#define HWIO_GERROR_IRQ_CFG1_POR                                        0x00000000
#define HWIO_GERROR_IRQ_CFG1_POR_RMSK                                   0xffffffff
#define HWIO_GERROR_IRQ_CFG1_ATTR                                              0x3
#define HWIO_GERROR_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_GERROR_IRQ_CFG1_ADDR(x), HWIO_GERROR_IRQ_CFG1_RMSK)
#define HWIO_GERROR_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_GERROR_IRQ_CFG1_ADDR(x), m)
#define HWIO_GERROR_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_GERROR_IRQ_CFG1_ADDR(x),v)
#define HWIO_GERROR_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GERROR_IRQ_CFG1_ADDR(x),m,v,HWIO_GERROR_IRQ_CFG1_IN(x))
#define HWIO_GERROR_IRQ_CFG1_DATA_BMSK                                  0xffffffff
#define HWIO_GERROR_IRQ_CFG1_DATA_SHFT                                         0x0

#define HWIO_GERROR_IRQ_CFG2_ADDR(x)                                    ((x) + 0x00000074)
#define HWIO_GERROR_IRQ_CFG2_PHYS(x)                                    ((x) + 0x00000074)
#define HWIO_GERROR_IRQ_CFG2_RMSK                                             0x3f
#define HWIO_GERROR_IRQ_CFG2_POR                                        0x00000000
#define HWIO_GERROR_IRQ_CFG2_POR_RMSK                                   0xffffffff
#define HWIO_GERROR_IRQ_CFG2_ATTR                                              0x3
#define HWIO_GERROR_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_GERROR_IRQ_CFG2_ADDR(x), HWIO_GERROR_IRQ_CFG2_RMSK)
#define HWIO_GERROR_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_GERROR_IRQ_CFG2_ADDR(x), m)
#define HWIO_GERROR_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_GERROR_IRQ_CFG2_ADDR(x),v)
#define HWIO_GERROR_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GERROR_IRQ_CFG2_ADDR(x),m,v,HWIO_GERROR_IRQ_CFG2_IN(x))
#define HWIO_GERROR_IRQ_CFG2_SH_BMSK                                          0x30
#define HWIO_GERROR_IRQ_CFG2_SH_SHFT                                           0x4
#define HWIO_GERROR_IRQ_CFG2_MEMATTR_BMSK                                      0xf
#define HWIO_GERROR_IRQ_CFG2_MEMATTR_SHFT                                      0x0

#define HWIO_STRTAB_BASE_L_ADDR(x)                                      ((x) + 0x00000080)
#define HWIO_STRTAB_BASE_L_PHYS(x)                                      ((x) + 0x00000080)
#define HWIO_STRTAB_BASE_L_RMSK                                         0xffffffc0
#define HWIO_STRTAB_BASE_L_POR                                          0x00000000
#define HWIO_STRTAB_BASE_L_POR_RMSK                                     0xffffffff
#define HWIO_STRTAB_BASE_L_ATTR                                                0x3
#define HWIO_STRTAB_BASE_L_IN(x)      \
        in_dword_masked(HWIO_STRTAB_BASE_L_ADDR(x), HWIO_STRTAB_BASE_L_RMSK)
#define HWIO_STRTAB_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_STRTAB_BASE_L_ADDR(x), m)
#define HWIO_STRTAB_BASE_L_OUT(x, v)      \
        out_dword(HWIO_STRTAB_BASE_L_ADDR(x),v)
#define HWIO_STRTAB_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_STRTAB_BASE_L_ADDR(x),m,v,HWIO_STRTAB_BASE_L_IN(x))
#define HWIO_STRTAB_BASE_L_ADDR_31_6_BMSK                               0xffffffc0
#define HWIO_STRTAB_BASE_L_ADDR_31_6_SHFT                                      0x6

#define HWIO_STRTAB_BASE_H_ADDR(x)                                      ((x) + 0x00000084)
#define HWIO_STRTAB_BASE_H_PHYS(x)                                      ((x) + 0x00000084)
#define HWIO_STRTAB_BASE_H_RMSK                                         0x4000ffff
#define HWIO_STRTAB_BASE_H_POR                                          0x00000000
#define HWIO_STRTAB_BASE_H_POR_RMSK                                     0xffffffff
#define HWIO_STRTAB_BASE_H_ATTR                                                0x3
#define HWIO_STRTAB_BASE_H_IN(x)      \
        in_dword_masked(HWIO_STRTAB_BASE_H_ADDR(x), HWIO_STRTAB_BASE_H_RMSK)
#define HWIO_STRTAB_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_STRTAB_BASE_H_ADDR(x), m)
#define HWIO_STRTAB_BASE_H_OUT(x, v)      \
        out_dword(HWIO_STRTAB_BASE_H_ADDR(x),v)
#define HWIO_STRTAB_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_STRTAB_BASE_H_ADDR(x),m,v,HWIO_STRTAB_BASE_H_IN(x))
#define HWIO_STRTAB_BASE_H_RA_BMSK                                      0x40000000
#define HWIO_STRTAB_BASE_H_RA_SHFT                                            0x1e
#define HWIO_STRTAB_BASE_H_ADDR_47_32_BMSK                                  0xffff
#define HWIO_STRTAB_BASE_H_ADDR_47_32_SHFT                                     0x0

#define HWIO_STRTAB_BASE_CFG_ADDR(x)                                    ((x) + 0x00000088)
#define HWIO_STRTAB_BASE_CFG_PHYS(x)                                    ((x) + 0x00000088)
#define HWIO_STRTAB_BASE_CFG_RMSK                                          0x307ff
#define HWIO_STRTAB_BASE_CFG_POR                                        0x00000000
#define HWIO_STRTAB_BASE_CFG_POR_RMSK                                   0xffffffff
#define HWIO_STRTAB_BASE_CFG_ATTR                                              0x3
#define HWIO_STRTAB_BASE_CFG_IN(x)      \
        in_dword_masked(HWIO_STRTAB_BASE_CFG_ADDR(x), HWIO_STRTAB_BASE_CFG_RMSK)
#define HWIO_STRTAB_BASE_CFG_INM(x, m)      \
        in_dword_masked(HWIO_STRTAB_BASE_CFG_ADDR(x), m)
#define HWIO_STRTAB_BASE_CFG_OUT(x, v)      \
        out_dword(HWIO_STRTAB_BASE_CFG_ADDR(x),v)
#define HWIO_STRTAB_BASE_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_STRTAB_BASE_CFG_ADDR(x),m,v,HWIO_STRTAB_BASE_CFG_IN(x))
#define HWIO_STRTAB_BASE_CFG_FMT_BMSK                                      0x30000
#define HWIO_STRTAB_BASE_CFG_FMT_SHFT                                         0x10
#define HWIO_STRTAB_BASE_CFG_SPLIT_BMSK                                      0x7c0
#define HWIO_STRTAB_BASE_CFG_SPLIT_SHFT                                        0x6
#define HWIO_STRTAB_BASE_CFG_LOG2SIZE_BMSK                                    0x3f
#define HWIO_STRTAB_BASE_CFG_LOG2SIZE_SHFT                                     0x0

#define HWIO_CMDQ_BASE_L_ADDR(x)                                        ((x) + 0x00000090)
#define HWIO_CMDQ_BASE_L_PHYS(x)                                        ((x) + 0x00000090)
#define HWIO_CMDQ_BASE_L_RMSK                                           0xffffffff
#define HWIO_CMDQ_BASE_L_POR                                            0x00000000
#define HWIO_CMDQ_BASE_L_POR_RMSK                                       0xffffffff
#define HWIO_CMDQ_BASE_L_ATTR                                                  0x3
#define HWIO_CMDQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_CMDQ_BASE_L_ADDR(x), HWIO_CMDQ_BASE_L_RMSK)
#define HWIO_CMDQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_CMDQ_BASE_L_ADDR(x), m)
#define HWIO_CMDQ_BASE_L_OUT(x, v)      \
        out_dword(HWIO_CMDQ_BASE_L_ADDR(x),v)
#define HWIO_CMDQ_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CMDQ_BASE_L_ADDR(x),m,v,HWIO_CMDQ_BASE_L_IN(x))
#define HWIO_CMDQ_BASE_L_ADDR_31_5_BMSK                                 0xffffffe0
#define HWIO_CMDQ_BASE_L_ADDR_31_5_SHFT                                        0x5
#define HWIO_CMDQ_BASE_L_LOG2SIZE_BMSK                                        0x1f
#define HWIO_CMDQ_BASE_L_LOG2SIZE_SHFT                                         0x0

#define HWIO_CMDQ_BASE_H_ADDR(x)                                        ((x) + 0x00000094)
#define HWIO_CMDQ_BASE_H_PHYS(x)                                        ((x) + 0x00000094)
#define HWIO_CMDQ_BASE_H_RMSK                                           0x4000ffff
#define HWIO_CMDQ_BASE_H_POR                                            0x00000000
#define HWIO_CMDQ_BASE_H_POR_RMSK                                       0xffffffff
#define HWIO_CMDQ_BASE_H_ATTR                                                  0x3
#define HWIO_CMDQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_CMDQ_BASE_H_ADDR(x), HWIO_CMDQ_BASE_H_RMSK)
#define HWIO_CMDQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_CMDQ_BASE_H_ADDR(x), m)
#define HWIO_CMDQ_BASE_H_OUT(x, v)      \
        out_dword(HWIO_CMDQ_BASE_H_ADDR(x),v)
#define HWIO_CMDQ_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CMDQ_BASE_H_ADDR(x),m,v,HWIO_CMDQ_BASE_H_IN(x))
#define HWIO_CMDQ_BASE_H_RA_BMSK                                        0x40000000
#define HWIO_CMDQ_BASE_H_RA_SHFT                                              0x1e
#define HWIO_CMDQ_BASE_H_ADDR_47_32_BMSK                                    0xffff
#define HWIO_CMDQ_BASE_H_ADDR_47_32_SHFT                                       0x0

#define HWIO_CMDQ_PROD_ADDR(x)                                          ((x) + 0x00000098)
#define HWIO_CMDQ_PROD_PHYS(x)                                          ((x) + 0x00000098)
#define HWIO_CMDQ_PROD_RMSK                                                0xfffff
#define HWIO_CMDQ_PROD_POR                                              0x00000000
#define HWIO_CMDQ_PROD_POR_RMSK                                         0xffffffff
#define HWIO_CMDQ_PROD_ATTR                                                    0x3
#define HWIO_CMDQ_PROD_IN(x)      \
        in_dword_masked(HWIO_CMDQ_PROD_ADDR(x), HWIO_CMDQ_PROD_RMSK)
#define HWIO_CMDQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_CMDQ_PROD_ADDR(x), m)
#define HWIO_CMDQ_PROD_OUT(x, v)      \
        out_dword(HWIO_CMDQ_PROD_ADDR(x),v)
#define HWIO_CMDQ_PROD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CMDQ_PROD_ADDR(x),m,v,HWIO_CMDQ_PROD_IN(x))
#define HWIO_CMDQ_PROD_WR_INDEX_AND_WRAP_BMSK                              0xfffff
#define HWIO_CMDQ_PROD_WR_INDEX_AND_WRAP_SHFT                                  0x0

#define HWIO_CMDQ_CONS_ADDR(x)                                          ((x) + 0x0000009c)
#define HWIO_CMDQ_CONS_PHYS(x)                                          ((x) + 0x0000009c)
#define HWIO_CMDQ_CONS_RMSK                                             0x7f0fffff
#define HWIO_CMDQ_CONS_POR                                              0x00000000
#define HWIO_CMDQ_CONS_POR_RMSK                                         0xffffffff
#define HWIO_CMDQ_CONS_ATTR                                                    0x3
#define HWIO_CMDQ_CONS_IN(x)      \
        in_dword_masked(HWIO_CMDQ_CONS_ADDR(x), HWIO_CMDQ_CONS_RMSK)
#define HWIO_CMDQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_CMDQ_CONS_ADDR(x), m)
#define HWIO_CMDQ_CONS_OUT(x, v)      \
        out_dword(HWIO_CMDQ_CONS_ADDR(x),v)
#define HWIO_CMDQ_CONS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_CMDQ_CONS_ADDR(x),m,v,HWIO_CMDQ_CONS_IN(x))
#define HWIO_CMDQ_CONS_ERR_BMSK                                         0x7f000000
#define HWIO_CMDQ_CONS_ERR_SHFT                                               0x18
#define HWIO_CMDQ_CONS_RD_INDEX_AND_WRAP_BMSK                              0xfffff
#define HWIO_CMDQ_CONS_RD_INDEX_AND_WRAP_SHFT                                  0x0

#define HWIO_EVENTQ_BASE_L_ADDR(x)                                      ((x) + 0x000000a0)
#define HWIO_EVENTQ_BASE_L_PHYS(x)                                      ((x) + 0x000000a0)
#define HWIO_EVENTQ_BASE_L_RMSK                                         0xffffffff
#define HWIO_EVENTQ_BASE_L_POR                                          0x00000000
#define HWIO_EVENTQ_BASE_L_POR_RMSK                                     0xffffffff
#define HWIO_EVENTQ_BASE_L_ATTR                                                0x3
#define HWIO_EVENTQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_EVENTQ_BASE_L_ADDR(x), HWIO_EVENTQ_BASE_L_RMSK)
#define HWIO_EVENTQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_EVENTQ_BASE_L_ADDR(x), m)
#define HWIO_EVENTQ_BASE_L_OUT(x, v)      \
        out_dword(HWIO_EVENTQ_BASE_L_ADDR(x),v)
#define HWIO_EVENTQ_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EVENTQ_BASE_L_ADDR(x),m,v,HWIO_EVENTQ_BASE_L_IN(x))
#define HWIO_EVENTQ_BASE_L_ADDR_31_5_BMSK                               0xffffffe0
#define HWIO_EVENTQ_BASE_L_ADDR_31_5_SHFT                                      0x5
#define HWIO_EVENTQ_BASE_L_LOG2SIZE_BMSK                                      0x1f
#define HWIO_EVENTQ_BASE_L_LOG2SIZE_SHFT                                       0x0

#define HWIO_EVENTQ_BASE_H_ADDR(x)                                      ((x) + 0x000000a4)
#define HWIO_EVENTQ_BASE_H_PHYS(x)                                      ((x) + 0x000000a4)
#define HWIO_EVENTQ_BASE_H_RMSK                                         0x4000ffff
#define HWIO_EVENTQ_BASE_H_POR                                          0x00000000
#define HWIO_EVENTQ_BASE_H_POR_RMSK                                     0xffffffff
#define HWIO_EVENTQ_BASE_H_ATTR                                                0x3
#define HWIO_EVENTQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_EVENTQ_BASE_H_ADDR(x), HWIO_EVENTQ_BASE_H_RMSK)
#define HWIO_EVENTQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_EVENTQ_BASE_H_ADDR(x), m)
#define HWIO_EVENTQ_BASE_H_OUT(x, v)      \
        out_dword(HWIO_EVENTQ_BASE_H_ADDR(x),v)
#define HWIO_EVENTQ_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EVENTQ_BASE_H_ADDR(x),m,v,HWIO_EVENTQ_BASE_H_IN(x))
#define HWIO_EVENTQ_BASE_H_WA_BMSK                                      0x40000000
#define HWIO_EVENTQ_BASE_H_WA_SHFT                                            0x1e
#define HWIO_EVENTQ_BASE_H_ADDR_47_32_BMSK                                  0xffff
#define HWIO_EVENTQ_BASE_H_ADDR_47_32_SHFT                                     0x0

#define HWIO_EVENTQ_IRQ_CFG0_L_ADDR(x)                                  ((x) + 0x000000b0)
#define HWIO_EVENTQ_IRQ_CFG0_L_PHYS(x)                                  ((x) + 0x000000b0)
#define HWIO_EVENTQ_IRQ_CFG0_L_RMSK                                     0xfffffffc
#define HWIO_EVENTQ_IRQ_CFG0_L_POR                                      0x00000000
#define HWIO_EVENTQ_IRQ_CFG0_L_POR_RMSK                                 0xffffffff
#define HWIO_EVENTQ_IRQ_CFG0_L_ATTR                                            0x3
#define HWIO_EVENTQ_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_EVENTQ_IRQ_CFG0_L_ADDR(x), HWIO_EVENTQ_IRQ_CFG0_L_RMSK)
#define HWIO_EVENTQ_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_EVENTQ_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_EVENTQ_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_EVENTQ_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_EVENTQ_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EVENTQ_IRQ_CFG0_L_ADDR(x),m,v,HWIO_EVENTQ_IRQ_CFG0_L_IN(x))
#define HWIO_EVENTQ_IRQ_CFG0_L_ADDR_31_2_BMSK                           0xfffffffc
#define HWIO_EVENTQ_IRQ_CFG0_L_ADDR_31_2_SHFT                                  0x2

#define HWIO_EVENTQ_IRQ_CFG0_H_ADDR(x)                                  ((x) + 0x000000b4)
#define HWIO_EVENTQ_IRQ_CFG0_H_PHYS(x)                                  ((x) + 0x000000b4)
#define HWIO_EVENTQ_IRQ_CFG0_H_RMSK                                         0xffff
#define HWIO_EVENTQ_IRQ_CFG0_H_POR                                      0x00000000
#define HWIO_EVENTQ_IRQ_CFG0_H_POR_RMSK                                 0xffffffff
#define HWIO_EVENTQ_IRQ_CFG0_H_ATTR                                            0x3
#define HWIO_EVENTQ_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_EVENTQ_IRQ_CFG0_H_ADDR(x), HWIO_EVENTQ_IRQ_CFG0_H_RMSK)
#define HWIO_EVENTQ_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_EVENTQ_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_EVENTQ_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_EVENTQ_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_EVENTQ_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EVENTQ_IRQ_CFG0_H_ADDR(x),m,v,HWIO_EVENTQ_IRQ_CFG0_H_IN(x))
#define HWIO_EVENTQ_IRQ_CFG0_H_ADDR_47_32_BMSK                              0xffff
#define HWIO_EVENTQ_IRQ_CFG0_H_ADDR_47_32_SHFT                                 0x0

#define HWIO_EVENTQ_IRQ_CFG1_ADDR(x)                                    ((x) + 0x000000b8)
#define HWIO_EVENTQ_IRQ_CFG1_PHYS(x)                                    ((x) + 0x000000b8)
#define HWIO_EVENTQ_IRQ_CFG1_RMSK                                       0xffffffff
#define HWIO_EVENTQ_IRQ_CFG1_POR                                        0x00000000
#define HWIO_EVENTQ_IRQ_CFG1_POR_RMSK                                   0xffffffff
#define HWIO_EVENTQ_IRQ_CFG1_ATTR                                              0x3
#define HWIO_EVENTQ_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_EVENTQ_IRQ_CFG1_ADDR(x), HWIO_EVENTQ_IRQ_CFG1_RMSK)
#define HWIO_EVENTQ_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_EVENTQ_IRQ_CFG1_ADDR(x), m)
#define HWIO_EVENTQ_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_EVENTQ_IRQ_CFG1_ADDR(x),v)
#define HWIO_EVENTQ_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EVENTQ_IRQ_CFG1_ADDR(x),m,v,HWIO_EVENTQ_IRQ_CFG1_IN(x))
#define HWIO_EVENTQ_IRQ_CFG1_DATA_BMSK                                  0xffffffff
#define HWIO_EVENTQ_IRQ_CFG1_DATA_SHFT                                         0x0

#define HWIO_EVENTQ_IRQ_CFG2_ADDR(x)                                    ((x) + 0x000000bc)
#define HWIO_EVENTQ_IRQ_CFG2_PHYS(x)                                    ((x) + 0x000000bc)
#define HWIO_EVENTQ_IRQ_CFG2_RMSK                                             0x3f
#define HWIO_EVENTQ_IRQ_CFG2_POR                                        0x00000000
#define HWIO_EVENTQ_IRQ_CFG2_POR_RMSK                                   0xffffffff
#define HWIO_EVENTQ_IRQ_CFG2_ATTR                                              0x3
#define HWIO_EVENTQ_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_EVENTQ_IRQ_CFG2_ADDR(x), HWIO_EVENTQ_IRQ_CFG2_RMSK)
#define HWIO_EVENTQ_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_EVENTQ_IRQ_CFG2_ADDR(x), m)
#define HWIO_EVENTQ_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_EVENTQ_IRQ_CFG2_ADDR(x),v)
#define HWIO_EVENTQ_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EVENTQ_IRQ_CFG2_ADDR(x),m,v,HWIO_EVENTQ_IRQ_CFG2_IN(x))
#define HWIO_EVENTQ_IRQ_CFG2_SH_BMSK                                          0x30
#define HWIO_EVENTQ_IRQ_CFG2_SH_SHFT                                           0x4
#define HWIO_EVENTQ_IRQ_CFG2_MEMATTR_BMSK                                      0xf
#define HWIO_EVENTQ_IRQ_CFG2_MEMATTR_SHFT                                      0x0

#define HWIO_PRIQ_BASE_L_ADDR(x)                                        ((x) + 0x000000c0)
#define HWIO_PRIQ_BASE_L_PHYS(x)                                        ((x) + 0x000000c0)
#define HWIO_PRIQ_BASE_L_RMSK                                           0xffffffff
#define HWIO_PRIQ_BASE_L_POR                                            0x00000000
#define HWIO_PRIQ_BASE_L_POR_RMSK                                       0xffffffff
#define HWIO_PRIQ_BASE_L_ATTR                                                  0x1
#define HWIO_PRIQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_PRIQ_BASE_L_ADDR(x), HWIO_PRIQ_BASE_L_RMSK)
#define HWIO_PRIQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_PRIQ_BASE_L_ADDR(x), m)
#define HWIO_PRIQ_BASE_L_ADDR_31_5_BMSK                                 0xffffffe0
#define HWIO_PRIQ_BASE_L_ADDR_31_5_SHFT                                        0x5
#define HWIO_PRIQ_BASE_L_LOG2SIZE_BMSK                                        0x1f
#define HWIO_PRIQ_BASE_L_LOG2SIZE_SHFT                                         0x0

#define HWIO_PRIQ_BASE_H_ADDR(x)                                        ((x) + 0x000000c4)
#define HWIO_PRIQ_BASE_H_PHYS(x)                                        ((x) + 0x000000c4)
#define HWIO_PRIQ_BASE_H_RMSK                                           0x4000ffff
#define HWIO_PRIQ_BASE_H_POR                                            0x00000000
#define HWIO_PRIQ_BASE_H_POR_RMSK                                       0xffffffff
#define HWIO_PRIQ_BASE_H_ATTR                                                  0x1
#define HWIO_PRIQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_PRIQ_BASE_H_ADDR(x), HWIO_PRIQ_BASE_H_RMSK)
#define HWIO_PRIQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_PRIQ_BASE_H_ADDR(x), m)
#define HWIO_PRIQ_BASE_H_WA_BMSK                                        0x40000000
#define HWIO_PRIQ_BASE_H_WA_SHFT                                              0x1e
#define HWIO_PRIQ_BASE_H_ADDR_47_32_BMSK                                    0xffff
#define HWIO_PRIQ_BASE_H_ADDR_47_32_SHFT                                       0x0

#define HWIO_PRIQ_IRQ_CFG0_L_ADDR(x)                                    ((x) + 0x000000d0)
#define HWIO_PRIQ_IRQ_CFG0_L_PHYS(x)                                    ((x) + 0x000000d0)
#define HWIO_PRIQ_IRQ_CFG0_L_RMSK                                       0xfffffffc
#define HWIO_PRIQ_IRQ_CFG0_L_POR                                        0x00000000
#define HWIO_PRIQ_IRQ_CFG0_L_POR_RMSK                                   0xffffffff
#define HWIO_PRIQ_IRQ_CFG0_L_ATTR                                              0x1
#define HWIO_PRIQ_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_PRIQ_IRQ_CFG0_L_ADDR(x), HWIO_PRIQ_IRQ_CFG0_L_RMSK)
#define HWIO_PRIQ_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_PRIQ_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_PRIQ_IRQ_CFG0_L_ADDR_31_2_BMSK                             0xfffffffc
#define HWIO_PRIQ_IRQ_CFG0_L_ADDR_31_2_SHFT                                    0x2

#define HWIO_PRIQ_IRQ_CFG0_H_ADDR(x)                                    ((x) + 0x000000d4)
#define HWIO_PRIQ_IRQ_CFG0_H_PHYS(x)                                    ((x) + 0x000000d4)
#define HWIO_PRIQ_IRQ_CFG0_H_RMSK                                           0xffff
#define HWIO_PRIQ_IRQ_CFG0_H_POR                                        0x00000000
#define HWIO_PRIQ_IRQ_CFG0_H_POR_RMSK                                   0xffffffff
#define HWIO_PRIQ_IRQ_CFG0_H_ATTR                                              0x1
#define HWIO_PRIQ_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_PRIQ_IRQ_CFG0_H_ADDR(x), HWIO_PRIQ_IRQ_CFG0_H_RMSK)
#define HWIO_PRIQ_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_PRIQ_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_PRIQ_IRQ_CFG0_H_ADDR_47_32_BMSK                                0xffff
#define HWIO_PRIQ_IRQ_CFG0_H_ADDR_47_32_SHFT                                   0x0

#define HWIO_PRIQ_IRQ_CFG1_ADDR(x)                                      ((x) + 0x000000d8)
#define HWIO_PRIQ_IRQ_CFG1_PHYS(x)                                      ((x) + 0x000000d8)
#define HWIO_PRIQ_IRQ_CFG1_RMSK                                         0xffffffff
#define HWIO_PRIQ_IRQ_CFG1_POR                                          0x00000000
#define HWIO_PRIQ_IRQ_CFG1_POR_RMSK                                     0xffffffff
#define HWIO_PRIQ_IRQ_CFG1_ATTR                                                0x1
#define HWIO_PRIQ_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_PRIQ_IRQ_CFG1_ADDR(x), HWIO_PRIQ_IRQ_CFG1_RMSK)
#define HWIO_PRIQ_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_PRIQ_IRQ_CFG1_ADDR(x), m)
#define HWIO_PRIQ_IRQ_CFG1_DATA_BMSK                                    0xffffffff
#define HWIO_PRIQ_IRQ_CFG1_DATA_SHFT                                           0x0

#define HWIO_PRIQ_IRQ_CFG2_ADDR(x)                                      ((x) + 0x000000dc)
#define HWIO_PRIQ_IRQ_CFG2_PHYS(x)                                      ((x) + 0x000000dc)
#define HWIO_PRIQ_IRQ_CFG2_RMSK                                         0x8000003f
#define HWIO_PRIQ_IRQ_CFG2_POR                                          0x00000000
#define HWIO_PRIQ_IRQ_CFG2_POR_RMSK                                     0xffffffff
#define HWIO_PRIQ_IRQ_CFG2_ATTR                                                0x1
#define HWIO_PRIQ_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_PRIQ_IRQ_CFG2_ADDR(x), HWIO_PRIQ_IRQ_CFG2_RMSK)
#define HWIO_PRIQ_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_PRIQ_IRQ_CFG2_ADDR(x), m)
#define HWIO_PRIQ_IRQ_CFG2_LO_BMSK                                      0x80000000
#define HWIO_PRIQ_IRQ_CFG2_LO_SHFT                                            0x1f
#define HWIO_PRIQ_IRQ_CFG2_SH_BMSK                                            0x30
#define HWIO_PRIQ_IRQ_CFG2_SH_SHFT                                             0x4
#define HWIO_PRIQ_IRQ_CFG2_MEMATTR_BMSK                                        0xf
#define HWIO_PRIQ_IRQ_CFG2_MEMATTR_SHFT                                        0x0

#define HWIO_GATOS_CTRL_ADDR(x)                                         ((x) + 0x00000100)
#define HWIO_GATOS_CTRL_PHYS(x)                                         ((x) + 0x00000100)
#define HWIO_GATOS_CTRL_RMSK                                                   0x1
#define HWIO_GATOS_CTRL_POR                                             0x00000000
#define HWIO_GATOS_CTRL_POR_RMSK                                        0xffffffff
#define HWIO_GATOS_CTRL_ATTR                                                   0x3
#define HWIO_GATOS_CTRL_IN(x)      \
        in_dword_masked(HWIO_GATOS_CTRL_ADDR(x), HWIO_GATOS_CTRL_RMSK)
#define HWIO_GATOS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_GATOS_CTRL_ADDR(x), m)
#define HWIO_GATOS_CTRL_OUT(x, v)      \
        out_dword(HWIO_GATOS_CTRL_ADDR(x),v)
#define HWIO_GATOS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GATOS_CTRL_ADDR(x),m,v,HWIO_GATOS_CTRL_IN(x))
#define HWIO_GATOS_CTRL_RUN_BMSK                                               0x1
#define HWIO_GATOS_CTRL_RUN_SHFT                                               0x0

#define HWIO_GATOS_SID_L_ADDR(x)                                        ((x) + 0x00000108)
#define HWIO_GATOS_SID_L_PHYS(x)                                        ((x) + 0x00000108)
#define HWIO_GATOS_SID_L_RMSK                                               0xffff
#define HWIO_GATOS_SID_L_POR                                            0x00000000
#define HWIO_GATOS_SID_L_POR_RMSK                                       0xffffffff
#define HWIO_GATOS_SID_L_ATTR                                                  0x3
#define HWIO_GATOS_SID_L_IN(x)      \
        in_dword_masked(HWIO_GATOS_SID_L_ADDR(x), HWIO_GATOS_SID_L_RMSK)
#define HWIO_GATOS_SID_L_INM(x, m)      \
        in_dword_masked(HWIO_GATOS_SID_L_ADDR(x), m)
#define HWIO_GATOS_SID_L_OUT(x, v)      \
        out_dword(HWIO_GATOS_SID_L_ADDR(x),v)
#define HWIO_GATOS_SID_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GATOS_SID_L_ADDR(x),m,v,HWIO_GATOS_SID_L_IN(x))
#define HWIO_GATOS_SID_L_STREAMID_BMSK                                      0xffff
#define HWIO_GATOS_SID_L_STREAMID_SHFT                                         0x0

#define HWIO_GATOS_SID_H_ADDR(x)                                        ((x) + 0x0000010c)
#define HWIO_GATOS_SID_H_PHYS(x)                                        ((x) + 0x0000010c)
#define HWIO_GATOS_SID_H_RMSK                                             0x1fffff
#define HWIO_GATOS_SID_H_POR                                            0x00000000
#define HWIO_GATOS_SID_H_POR_RMSK                                       0xffffffff
#define HWIO_GATOS_SID_H_ATTR                                                  0x3
#define HWIO_GATOS_SID_H_IN(x)      \
        in_dword_masked(HWIO_GATOS_SID_H_ADDR(x), HWIO_GATOS_SID_H_RMSK)
#define HWIO_GATOS_SID_H_INM(x, m)      \
        in_dword_masked(HWIO_GATOS_SID_H_ADDR(x), m)
#define HWIO_GATOS_SID_H_OUT(x, v)      \
        out_dword(HWIO_GATOS_SID_H_ADDR(x),v)
#define HWIO_GATOS_SID_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GATOS_SID_H_ADDR(x),m,v,HWIO_GATOS_SID_H_IN(x))
#define HWIO_GATOS_SID_H_SSID_VALID_BMSK                                  0x100000
#define HWIO_GATOS_SID_H_SSID_VALID_SHFT                                      0x14
#define HWIO_GATOS_SID_H_SUBSTREAMID_BMSK                                  0xfffff
#define HWIO_GATOS_SID_H_SUBSTREAMID_SHFT                                      0x0

#define HWIO_GATOS_ADDR_L_ADDR(x)                                       ((x) + 0x00000110)
#define HWIO_GATOS_ADDR_L_PHYS(x)                                       ((x) + 0x00000110)
#define HWIO_GATOS_ADDR_L_RMSK                                          0xffffffc0
#define HWIO_GATOS_ADDR_L_POR                                           0x00000000
#define HWIO_GATOS_ADDR_L_POR_RMSK                                      0xffffffff
#define HWIO_GATOS_ADDR_L_ATTR                                                 0x3
#define HWIO_GATOS_ADDR_L_IN(x)      \
        in_dword_masked(HWIO_GATOS_ADDR_L_ADDR(x), HWIO_GATOS_ADDR_L_RMSK)
#define HWIO_GATOS_ADDR_L_INM(x, m)      \
        in_dword_masked(HWIO_GATOS_ADDR_L_ADDR(x), m)
#define HWIO_GATOS_ADDR_L_OUT(x, v)      \
        out_dword(HWIO_GATOS_ADDR_L_ADDR(x),v)
#define HWIO_GATOS_ADDR_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GATOS_ADDR_L_ADDR(x),m,v,HWIO_GATOS_ADDR_L_IN(x))
#define HWIO_GATOS_ADDR_L_ADDR_31_12_BMSK                               0xfffff000
#define HWIO_GATOS_ADDR_L_ADDR_31_12_SHFT                                      0xc
#define HWIO_GATOS_ADDR_L_TYPE_BMSK                                          0xc00
#define HWIO_GATOS_ADDR_L_TYPE_SHFT                                            0xa
#define HWIO_GATOS_ADDR_L_PNU_BMSK                                           0x200
#define HWIO_GATOS_ADDR_L_PNU_SHFT                                             0x9
#define HWIO_GATOS_ADDR_L_RNW_BMSK                                           0x100
#define HWIO_GATOS_ADDR_L_RNW_SHFT                                             0x8
#define HWIO_GATOS_ADDR_L_IND_BMSK                                            0x80
#define HWIO_GATOS_ADDR_L_IND_SHFT                                             0x7
#define HWIO_GATOS_ADDR_L_HTTUI_BMSK                                          0x40
#define HWIO_GATOS_ADDR_L_HTTUI_SHFT                                           0x6

#define HWIO_GATOS_ADDR_H_ADDR(x)                                       ((x) + 0x00000114)
#define HWIO_GATOS_ADDR_H_PHYS(x)                                       ((x) + 0x00000114)
#define HWIO_GATOS_ADDR_H_RMSK                                          0xffffffff
#define HWIO_GATOS_ADDR_H_POR                                           0x00000000
#define HWIO_GATOS_ADDR_H_POR_RMSK                                      0xffffffff
#define HWIO_GATOS_ADDR_H_ATTR                                                 0x3
#define HWIO_GATOS_ADDR_H_IN(x)      \
        in_dword_masked(HWIO_GATOS_ADDR_H_ADDR(x), HWIO_GATOS_ADDR_H_RMSK)
#define HWIO_GATOS_ADDR_H_INM(x, m)      \
        in_dword_masked(HWIO_GATOS_ADDR_H_ADDR(x), m)
#define HWIO_GATOS_ADDR_H_OUT(x, v)      \
        out_dword(HWIO_GATOS_ADDR_H_ADDR(x),v)
#define HWIO_GATOS_ADDR_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_GATOS_ADDR_H_ADDR(x),m,v,HWIO_GATOS_ADDR_H_IN(x))
#define HWIO_GATOS_ADDR_H_ADDR_63_32_BMSK                               0xffffffff
#define HWIO_GATOS_ADDR_H_ADDR_63_32_SHFT                                      0x0

#define HWIO_GATOS_PAR_L_ADDR(x)                                        ((x) + 0x00000118)
#define HWIO_GATOS_PAR_L_PHYS(x)                                        ((x) + 0x00000118)
#define HWIO_GATOS_PAR_L_RMSK                                           0xffffffff
#define HWIO_GATOS_PAR_L_POR                                            0x00000000
#define HWIO_GATOS_PAR_L_POR_RMSK                                       0xffffffff
#define HWIO_GATOS_PAR_L_ATTR                                                  0x1
#define HWIO_GATOS_PAR_L_IN(x)      \
        in_dword_masked(HWIO_GATOS_PAR_L_ADDR(x), HWIO_GATOS_PAR_L_RMSK)
#define HWIO_GATOS_PAR_L_INM(x, m)      \
        in_dword_masked(HWIO_GATOS_PAR_L_ADDR(x), m)
#define HWIO_GATOS_PAR_L_ADDR_BMSK                                      0xfffff000
#define HWIO_GATOS_PAR_L_ADDR_SHFT                                             0xc
#define HWIO_GATOS_PAR_L_FIELD_BMSK                                          0xffe
#define HWIO_GATOS_PAR_L_FIELD_SHFT                                            0x1
#define HWIO_GATOS_PAR_L_FAULT_BMSK                                            0x1
#define HWIO_GATOS_PAR_L_FAULT_SHFT                                            0x0

#define HWIO_GATOS_PAR_H_ADDR(x)                                        ((x) + 0x0000011c)
#define HWIO_GATOS_PAR_H_PHYS(x)                                        ((x) + 0x0000011c)
#define HWIO_GATOS_PAR_H_RMSK                                           0xff00ffff
#define HWIO_GATOS_PAR_H_POR                                            0x00000000
#define HWIO_GATOS_PAR_H_POR_RMSK                                       0xffffffff
#define HWIO_GATOS_PAR_H_ATTR                                                  0x1
#define HWIO_GATOS_PAR_H_IN(x)      \
        in_dword_masked(HWIO_GATOS_PAR_H_ADDR(x), HWIO_GATOS_PAR_H_RMSK)
#define HWIO_GATOS_PAR_H_INM(x, m)      \
        in_dword_masked(HWIO_GATOS_PAR_H_ADDR(x), m)
#define HWIO_GATOS_PAR_H_MEMATTR_BMSK                                   0xff000000
#define HWIO_GATOS_PAR_H_MEMATTR_SHFT                                         0x18
#define HWIO_GATOS_PAR_H_ADDR_BMSK                                          0xffff
#define HWIO_GATOS_PAR_H_ADDR_SHFT                                             0x0

#define HWIO_VATOS_SEL_ADDR(x)                                          ((x) + 0x00000180)
#define HWIO_VATOS_SEL_PHYS(x)                                          ((x) + 0x00000180)
#define HWIO_VATOS_SEL_RMSK                                                 0xffff
#define HWIO_VATOS_SEL_POR                                              0x00000000
#define HWIO_VATOS_SEL_POR_RMSK                                         0xffffffff
#define HWIO_VATOS_SEL_ATTR                                                    0x3
#define HWIO_VATOS_SEL_IN(x)      \
        in_dword_masked(HWIO_VATOS_SEL_ADDR(x), HWIO_VATOS_SEL_RMSK)
#define HWIO_VATOS_SEL_INM(x, m)      \
        in_dword_masked(HWIO_VATOS_SEL_ADDR(x), m)
#define HWIO_VATOS_SEL_OUT(x, v)      \
        out_dword(HWIO_VATOS_SEL_ADDR(x),v)
#define HWIO_VATOS_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VATOS_SEL_ADDR(x),m,v,HWIO_VATOS_SEL_IN(x))
#define HWIO_VATOS_SEL_VMID_BMSK                                            0xffff
#define HWIO_VATOS_SEL_VMID_SHFT                                               0x0

#define HWIO_QIDR0_ADDR(x)                                              ((x) + 0x00000e00)
#define HWIO_QIDR0_PHYS(x)                                              ((x) + 0x00000e00)
#define HWIO_QIDR0_RMSK                                                 0x7ffffff5
#define HWIO_QIDR0_POR                                                  0x540234f5
#define HWIO_QIDR0_POR_RMSK                                             0xffffffff
#define HWIO_QIDR0_ATTR                                                        0x1
#define HWIO_QIDR0_IN(x)      \
        in_dword_masked(HWIO_QIDR0_ADDR(x), HWIO_QIDR0_RMSK)
#define HWIO_QIDR0_INM(x, m)      \
        in_dword_masked(HWIO_QIDR0_ADDR(x), m)
#define HWIO_QIDR0_NUM_QAD_BMSK                                         0x40000000
#define HWIO_QIDR0_NUM_QAD_SHFT                                               0x1e
#define HWIO_QIDR0_QACT_RST_QAD_VAL_BMSK                                0x20000000
#define HWIO_QIDR0_QACT_RST_QAD_VAL_SHFT                                      0x1d
#define HWIO_QIDR0_QACT_RST_SSD_VAL_BMSK                                0x10000000
#define HWIO_QIDR0_QACT_RST_SSD_VAL_SHFT                                      0x1c
#define HWIO_QIDR0_QACT_RST_EN_BMSK                                      0x8000000
#define HWIO_QIDR0_QACT_RST_EN_SHFT                                           0x1b
#define HWIO_QIDR0_QACT_SIZE_BMSK                                        0x7fc0000
#define HWIO_QIDR0_QACT_SIZE_SHFT                                             0x12
#define HWIO_QIDR0_QACT_INDEX_WIDTH_BMSK                                   0x3c000
#define HWIO_QIDR0_QACT_INDEX_WIDTH_SHFT                                       0xe
#define HWIO_QIDR0_QACT_SSD_HW_EN_BMSK                                      0x2000
#define HWIO_QIDR0_QACT_SSD_HW_EN_SHFT                                         0xd
#define HWIO_QIDR0_QACT_QAD_HW_EN_BMSK                                      0x1000
#define HWIO_QIDR0_QACT_QAD_HW_EN_SHFT                                         0xc
#define HWIO_QIDR0_QAD_NS_TRANS_HW_EN_BMSK                                   0x800
#define HWIO_QIDR0_QAD_NS_TRANS_HW_EN_SHFT                                     0xb
#define HWIO_QIDR0_QAD_NS_BYP_HW_EN_BMSK                                     0x400
#define HWIO_QIDR0_QAD_NS_BYP_HW_EN_SHFT                                       0xa
#define HWIO_QIDR0_QAD_S_TRANS_HW_EN_BMSK                                    0x200
#define HWIO_QIDR0_QAD_S_TRANS_HW_EN_SHFT                                      0x9
#define HWIO_QIDR0_QAD_S_BYP_HW_EN_BMSK                                      0x100
#define HWIO_QIDR0_QAD_S_BYP_HW_EN_SHFT                                        0x8
#define HWIO_QIDR0_CLIENT_MSI_WDATA_GEN_EN_BMSK                               0x80
#define HWIO_QIDR0_CLIENT_MSI_WDATA_GEN_EN_SHFT                                0x7
#define HWIO_QIDR0_QSMMU_NATIVE_MSI_EN_BMSK                                   0x40
#define HWIO_QIDR0_QSMMU_NATIVE_MSI_EN_SHFT                                    0x6
#define HWIO_QIDR0_PCIE_FUNC_EN_BMSK                                          0x20
#define HWIO_QIDR0_PCIE_FUNC_EN_SHFT                                           0x5
#define HWIO_QIDR0_CLNT_INT_EN_BMSK                                           0x10
#define HWIO_QIDR0_CLNT_INT_EN_SHFT                                            0x4
#define HWIO_QIDR0_SI_INTF_EN_BMSK                                             0x4
#define HWIO_QIDR0_SI_INTF_EN_SHFT                                             0x2
#define HWIO_QIDR0_DVM_EN_BMSK                                                 0x1
#define HWIO_QIDR0_DVM_EN_SHFT                                                 0x0

#define HWIO_QIDR1_ADDR(x)                                              ((x) + 0x00000e04)
#define HWIO_QIDR1_PHYS(x)                                              ((x) + 0x00000e04)
#define HWIO_QIDR1_RMSK                                                   0x3fffff
#define HWIO_QIDR1_POR                                                  0x0019420f
#define HWIO_QIDR1_POR_RMSK                                             0xffffffff
#define HWIO_QIDR1_ATTR                                                        0x1
#define HWIO_QIDR1_IN(x)      \
        in_dword_masked(HWIO_QIDR1_ADDR(x), HWIO_QIDR1_RMSK)
#define HWIO_QIDR1_INM(x, m)      \
        in_dword_masked(HWIO_QIDR1_ADDR(x), m)
#define HWIO_QIDR1_CONFIG_BID_WIDTH_BMSK                                  0x380000
#define HWIO_QIDR1_CONFIG_BID_WIDTH_SHFT                                      0x13
#define HWIO_QIDR1_CONFIG_PID_WIDTH_BMSK                                   0x7c000
#define HWIO_QIDR1_CONFIG_PID_WIDTH_SHFT                                       0xe
#define HWIO_QIDR1_CONFIG_MID_WIDTH_BMSK                                    0x3fc0
#define HWIO_QIDR1_CONFIG_MID_WIDTH_SHFT                                       0x6
#define HWIO_QIDR1_CONFIG_DATA_WIDTH_BMSK                                     0x30
#define HWIO_QIDR1_CONFIG_DATA_WIDTH_SHFT                                      0x4
#define HWIO_QIDR1_VMID_WIDTH_BMSK                                             0xf
#define HWIO_QIDR1_VMID_WIDTH_SHFT                                             0x0

#define HWIO_QIDR2_ADDR(x)                                              ((x) + 0x00000e08)
#define HWIO_QIDR2_PHYS(x)                                              ((x) + 0x00000e08)
#define HWIO_QIDR2_RMSK                                                       0xff
#define HWIO_QIDR2_POR                                                  0x00000021
#define HWIO_QIDR2_POR_RMSK                                             0xffffffff
#define HWIO_QIDR2_ATTR                                                        0x1
#define HWIO_QIDR2_IN(x)      \
        in_dword_masked(HWIO_QIDR2_ADDR(x), HWIO_QIDR2_RMSK)
#define HWIO_QIDR2_INM(x, m)      \
        in_dword_masked(HWIO_QIDR2_ADDR(x), m)
#define HWIO_QIDR2_MAJOR_BMSK                                                 0xf0
#define HWIO_QIDR2_MAJOR_SHFT                                                  0x4
#define HWIO_QIDR2_MINOR_BMSK                                                  0xf
#define HWIO_QIDR2_MINOR_SHFT                                                  0x0

#define HWIO_QIDR3_ADDR(x)                                              ((x) + 0x00000e0c)
#define HWIO_QIDR3_PHYS(x)                                              ((x) + 0x00000e0c)
#define HWIO_QIDR3_RMSK                                                       0x3f
#define HWIO_QIDR3_POR                                                  0x00000020
#define HWIO_QIDR3_POR_RMSK                                             0xffffffff
#define HWIO_QIDR3_ATTR                                                        0x1
#define HWIO_QIDR3_IN(x)      \
        in_dword_masked(HWIO_QIDR3_ADDR(x), HWIO_QIDR3_RMSK)
#define HWIO_QIDR3_INM(x, m)      \
        in_dword_masked(HWIO_QIDR3_ADDR(x), m)
#define HWIO_QIDR3_MSIDEVICEID_WIDTH_BMSK                                     0x3f
#define HWIO_QIDR3_MSIDEVICEID_WIDTH_SHFT                                      0x0

#define HWIO_QIDR4_ADDR(x)                                              ((x) + 0x00000e10)
#define HWIO_QIDR4_PHYS(x)                                              ((x) + 0x00000e10)
#define HWIO_QIDR4_RMSK                                                  0xfffffff
#define HWIO_QIDR4_POR                                                  0x0357683f
#define HWIO_QIDR4_POR_RMSK                                             0xffffffff
#define HWIO_QIDR4_ATTR                                                        0x1
#define HWIO_QIDR4_IN(x)      \
        in_dword_masked(HWIO_QIDR4_ADDR(x), HWIO_QIDR4_RMSK)
#define HWIO_QIDR4_INM(x, m)      \
        in_dword_masked(HWIO_QIDR4_ADDR(x), m)
#define HWIO_QIDR4_CLIENT_BID_WIDTH_BMSK                                 0xf000000
#define HWIO_QIDR4_CLIENT_BID_WIDTH_SHFT                                      0x18
#define HWIO_QIDR4_CLIENT_PID_WIDTH_BMSK                                  0xf00000
#define HWIO_QIDR4_CLIENT_PID_WIDTH_SHFT                                      0x14
#define HWIO_QIDR4_CLIENT_MID_WIDTH_BMSK                                   0xf0000
#define HWIO_QIDR4_CLIENT_MID_WIDTH_SHFT                                      0x10
#define HWIO_QIDR4_CLIENT_TID_WIDTH_BMSK                                    0xf000
#define HWIO_QIDR4_CLIENT_TID_WIDTH_SHFT                                       0xc
#define HWIO_QIDR4_CLIENT_BURST_LNGTH_BMSK                                   0xfc0
#define HWIO_QIDR4_CLIENT_BURST_LNGTH_SHFT                                     0x6
#define HWIO_QIDR4_CLIENT_DATA_WIDTH_BMSK                                     0x30
#define HWIO_QIDR4_CLIENT_DATA_WIDTH_SHFT                                      0x4
#define HWIO_QIDR4_VMID_WIDTH_BMSK                                             0xf
#define HWIO_QIDR4_VMID_WIDTH_SHFT                                             0x0

#define HWIO_QIDR5_ADDR(x)                                              ((x) + 0x00000e14)
#define HWIO_QIDR5_PHYS(x)                                              ((x) + 0x00000e14)
#define HWIO_QIDR5_RMSK                                                      0xfff
#define HWIO_QIDR5_POR                                                  0x00000686
#define HWIO_QIDR5_POR_RMSK                                             0xffffffff
#define HWIO_QIDR5_ATTR                                                        0x1
#define HWIO_QIDR5_IN(x)      \
        in_dword_masked(HWIO_QIDR5_ADDR(x), HWIO_QIDR5_RMSK)
#define HWIO_QIDR5_INM(x, m)      \
        in_dword_masked(HWIO_QIDR5_ADDR(x), m)
#define HWIO_QIDR5_CLIENT_HIT_MISS_TAGID_WIDTH_BMSK                          0xf00
#define HWIO_QIDR5_CLIENT_HIT_MISS_TAGID_WIDTH_SHFT                            0x8
#define HWIO_QIDR5_CLIENT_OUTPUT_MID_WIDTH_BMSK                               0xf0
#define HWIO_QIDR5_CLIENT_OUTPUT_MID_WIDTH_SHFT                                0x4
#define HWIO_QIDR5_CLIENT_OUTPUT_TID_WIDTH_BMSK                                0xf
#define HWIO_QIDR5_CLIENT_OUTPUT_TID_WIDTH_SHFT                                0x0

#define HWIO_QIDR6_ADDR(x)                                              ((x) + 0x00000e18)
#define HWIO_QIDR6_PHYS(x)                                              ((x) + 0x00000e18)
#define HWIO_QIDR6_RMSK                                                      0xf7f
#define HWIO_QIDR6_POR                                                  0x00000409
#define HWIO_QIDR6_POR_RMSK                                             0xffffffff
#define HWIO_QIDR6_ATTR                                                        0x1
#define HWIO_QIDR6_IN(x)      \
        in_dword_masked(HWIO_QIDR6_ADDR(x), HWIO_QIDR6_RMSK)
#define HWIO_QIDR6_INM(x, m)      \
        in_dword_masked(HWIO_QIDR6_ADDR(x), m)
#define HWIO_QIDR6_TOTAL_WDATA_RAM_SIZE_BMSK                                 0xf00
#define HWIO_QIDR6_TOTAL_WDATA_RAM_SIZE_SHFT                                   0x8
#define HWIO_QIDR6_PERF_NUM_BMSK                                              0x7f
#define HWIO_QIDR6_PERF_NUM_SHFT                                               0x0

#define HWIO_QIDR7_ADDR(x)                                              ((x) + 0x00000e1c)
#define HWIO_QIDR7_PHYS(x)                                              ((x) + 0x00000e1c)
#define HWIO_QIDR7_RMSK                                                  0x7e0ffff
#define HWIO_QIDR7_POR                                                  0x01007bc8
#define HWIO_QIDR7_POR_RMSK                                             0xffffffff
#define HWIO_QIDR7_ATTR                                                        0x1
#define HWIO_QIDR7_IN(x)      \
        in_dword_masked(HWIO_QIDR7_ADDR(x), HWIO_QIDR7_RMSK)
#define HWIO_QIDR7_INM(x, m)      \
        in_dword_masked(HWIO_QIDR7_ADDR(x), m)
#define HWIO_QIDR7_NUM_HANDLER_SLOTS_BMSK                                0x7e00000
#define HWIO_QIDR7_NUM_HANDLER_SLOTS_SHFT                                     0x15
#define HWIO_QIDR7_NUM_OUTSTANDING_WRITES_BMSK                              0xf800
#define HWIO_QIDR7_NUM_OUTSTANDING_WRITES_SHFT                                 0xb
#define HWIO_QIDR7_NUM_OUTSTANDING_READS_BMSK                                0x7c0
#define HWIO_QIDR7_NUM_OUTSTANDING_READS_SHFT                                  0x6
#define HWIO_QIDR7_NUM_HTW_BMSK                                               0x3f
#define HWIO_QIDR7_NUM_HTW_SHFT                                                0x0

#define HWIO_QIDR8_ADDR(x)                                              ((x) + 0x00000e20)
#define HWIO_QIDR8_PHYS(x)                                              ((x) + 0x00000e20)
#define HWIO_QIDR8_RMSK                                                 0xffffffff
#define HWIO_QIDR8_POR                                                  0x02000008
#define HWIO_QIDR8_POR_RMSK                                             0xffffffff
#define HWIO_QIDR8_ATTR                                                        0x1
#define HWIO_QIDR8_IN(x)      \
        in_dword_masked(HWIO_QIDR8_ADDR(x), HWIO_QIDR8_RMSK)
#define HWIO_QIDR8_INM(x, m)      \
        in_dword_masked(HWIO_QIDR8_ADDR(x), m)
#define HWIO_QIDR8_NUM_TLB_ENTRIES_BMSK                                 0xffff0000
#define HWIO_QIDR8_NUM_TLB_ENTRIES_SHFT                                       0x10
#define HWIO_QIDR8_MAX_NUM_TLB_PARTITIONS_BMSK                              0xffff
#define HWIO_QIDR8_MAX_NUM_TLB_PARTITIONS_SHFT                                 0x0

#define HWIO_QIDR9_ADDR(x)                                              ((x) + 0x00000e24)
#define HWIO_QIDR9_PHYS(x)                                              ((x) + 0x00000e24)
#define HWIO_QIDR9_RMSK                                                  0xfffffff
#define HWIO_QIDR9_POR                                                  0x0c040503
#define HWIO_QIDR9_POR_RMSK                                             0xffffffff
#define HWIO_QIDR9_ATTR                                                        0x1
#define HWIO_QIDR9_IN(x)      \
        in_dword_masked(HWIO_QIDR9_ADDR(x), HWIO_QIDR9_RMSK)
#define HWIO_QIDR9_INM(x, m)      \
        in_dword_masked(HWIO_QIDR9_ADDR(x), m)
#define HWIO_QIDR9_TLB_LRU_EN_BMSK                                       0x8000000
#define HWIO_QIDR9_TLB_LRU_EN_SHFT                                            0x1b
#define HWIO_QIDR9_TLB_MODE_TABLE_WIDTH_BMSK                             0x7000000
#define HWIO_QIDR9_TLB_MODE_TABLE_WIDTH_SHFT                                  0x18
#define HWIO_QIDR9_TLB_MODE_TABLE_DEPTH_BMSK                              0xff0000
#define HWIO_QIDR9_TLB_MODE_TABLE_DEPTH_SHFT                                  0x10
#define HWIO_QIDR9_TLB_LAYOUT_TYPE_BMSK                                     0xff00
#define HWIO_QIDR9_TLB_LAYOUT_TYPE_SHFT                                        0x8
#define HWIO_QIDR9_TLB_PARTITION_INDEX_WIDTH_BMSK                             0xff
#define HWIO_QIDR9_TLB_PARTITION_INDEX_WIDTH_SHFT                              0x0

#define HWIO_QIDR10_ADDR(x)                                             ((x) + 0x00000e28)
#define HWIO_QIDR10_PHYS(x)                                             ((x) + 0x00000e28)
#define HWIO_QIDR10_RMSK                                                   0x1ffff
#define HWIO_QIDR10_POR                                                 0x00013030
#define HWIO_QIDR10_POR_RMSK                                            0xffffffff
#define HWIO_QIDR10_ATTR                                                       0x1
#define HWIO_QIDR10_IN(x)      \
        in_dword_masked(HWIO_QIDR10_ADDR(x), HWIO_QIDR10_RMSK)
#define HWIO_QIDR10_INM(x, m)      \
        in_dword_masked(HWIO_QIDR10_ADDR(x), m)
#define HWIO_QIDR10_CONFIG_CACHE_LRU_EN_BMSK                               0x10000
#define HWIO_QIDR10_CONFIG_CACHE_LRU_EN_SHFT                                  0x10
#define HWIO_QIDR10_CONFIG_CACHE_ENTRIES_BMSK                               0xff00
#define HWIO_QIDR10_CONFIG_CACHE_ENTRIES_SHFT                                  0x8
#define HWIO_QIDR10_RESIDENT_CONTEXT_BANKS_BMSK                               0xff
#define HWIO_QIDR10_RESIDENT_CONTEXT_BANKS_SHFT                                0x0

#define HWIO_PIDR4_ADDR(x)                                              ((x) + 0x00000fd0)
#define HWIO_PIDR4_PHYS(x)                                              ((x) + 0x00000fd0)
#define HWIO_PIDR4_RMSK                                                       0xff
#define HWIO_PIDR4_POR                                                  0x00000000
#define HWIO_PIDR4_POR_RMSK                                             0xffffffff
#define HWIO_PIDR4_ATTR                                                        0x1
#define HWIO_PIDR4_IN(x)      \
        in_dword_masked(HWIO_PIDR4_ADDR(x), HWIO_PIDR4_RMSK)
#define HWIO_PIDR4_INM(x, m)      \
        in_dword_masked(HWIO_PIDR4_ADDR(x), m)
#define HWIO_PIDR4_SIZE_BMSK                                                  0xf0
#define HWIO_PIDR4_SIZE_SHFT                                                   0x4
#define HWIO_PIDR4_DES_2_BMSK                                                  0xf
#define HWIO_PIDR4_DES_2_SHFT                                                  0x0

#define HWIO_PIDR5_ADDR(x)                                              ((x) + 0x00000fd4)
#define HWIO_PIDR5_PHYS(x)                                              ((x) + 0x00000fd4)
#define HWIO_PIDR5_RMSK                                                 0xffffffff
#define HWIO_PIDR5_POR                                                  0x00000000
#define HWIO_PIDR5_POR_RMSK                                             0xffffffff
#define HWIO_PIDR5_ATTR                                                        0x1
#define HWIO_PIDR5_IN(x)      \
        in_dword_masked(HWIO_PIDR5_ADDR(x), HWIO_PIDR5_RMSK)
#define HWIO_PIDR5_INM(x, m)      \
        in_dword_masked(HWIO_PIDR5_ADDR(x), m)
#define HWIO_PIDR5_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PIDR5_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PIDR6_ADDR(x)                                              ((x) + 0x00000fd8)
#define HWIO_PIDR6_PHYS(x)                                              ((x) + 0x00000fd8)
#define HWIO_PIDR6_RMSK                                                 0xffffffff
#define HWIO_PIDR6_POR                                                  0x00000000
#define HWIO_PIDR6_POR_RMSK                                             0xffffffff
#define HWIO_PIDR6_ATTR                                                        0x1
#define HWIO_PIDR6_IN(x)      \
        in_dword_masked(HWIO_PIDR6_ADDR(x), HWIO_PIDR6_RMSK)
#define HWIO_PIDR6_INM(x, m)      \
        in_dword_masked(HWIO_PIDR6_ADDR(x), m)
#define HWIO_PIDR6_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PIDR6_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PIDR7_ADDR(x)                                              ((x) + 0x00000fdc)
#define HWIO_PIDR7_PHYS(x)                                              ((x) + 0x00000fdc)
#define HWIO_PIDR7_RMSK                                                 0xffffffff
#define HWIO_PIDR7_POR                                                  0x00000000
#define HWIO_PIDR7_POR_RMSK                                             0xffffffff
#define HWIO_PIDR7_ATTR                                                        0x1
#define HWIO_PIDR7_IN(x)      \
        in_dword_masked(HWIO_PIDR7_ADDR(x), HWIO_PIDR7_RMSK)
#define HWIO_PIDR7_INM(x, m)      \
        in_dword_masked(HWIO_PIDR7_ADDR(x), m)
#define HWIO_PIDR7_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PIDR7_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PIDR0_ADDR(x)                                              ((x) + 0x00000fe0)
#define HWIO_PIDR0_PHYS(x)                                              ((x) + 0x00000fe0)
#define HWIO_PIDR0_RMSK                                                       0xff
#define HWIO_PIDR0_POR                                                  0x00000040
#define HWIO_PIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PIDR0_ATTR                                                        0x1
#define HWIO_PIDR0_IN(x)      \
        in_dword_masked(HWIO_PIDR0_ADDR(x), HWIO_PIDR0_RMSK)
#define HWIO_PIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PIDR0_ADDR(x), m)
#define HWIO_PIDR0_PART_0_BMSK                                                0xff
#define HWIO_PIDR0_PART_0_SHFT                                                 0x0

#define HWIO_PIDR1_ADDR(x)                                              ((x) + 0x00000fe4)
#define HWIO_PIDR1_PHYS(x)                                              ((x) + 0x00000fe4)
#define HWIO_PIDR1_RMSK                                                       0xff
#define HWIO_PIDR1_POR                                                  0x00000000
#define HWIO_PIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PIDR1_ATTR                                                        0x1
#define HWIO_PIDR1_IN(x)      \
        in_dword_masked(HWIO_PIDR1_ADDR(x), HWIO_PIDR1_RMSK)
#define HWIO_PIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PIDR1_ADDR(x), m)
#define HWIO_PIDR1_DES_0_BMSK                                                 0xf0
#define HWIO_PIDR1_DES_0_SHFT                                                  0x4
#define HWIO_PIDR1_PART_1_BMSK                                                 0xf
#define HWIO_PIDR1_PART_1_SHFT                                                 0x0

#define HWIO_PIDR2_ADDR(x)                                              ((x) + 0x00000fe8)
#define HWIO_PIDR2_PHYS(x)                                              ((x) + 0x00000fe8)
#define HWIO_PIDR2_RMSK                                                       0xff
#define HWIO_PIDR2_POR                                                  0x0000003f
#define HWIO_PIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PIDR2_ATTR                                                        0x1
#define HWIO_PIDR2_IN(x)      \
        in_dword_masked(HWIO_PIDR2_ADDR(x), HWIO_PIDR2_RMSK)
#define HWIO_PIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PIDR2_ADDR(x), m)
#define HWIO_PIDR2_REVISION_BMSK                                              0xf0
#define HWIO_PIDR2_REVISION_SHFT                                               0x4
#define HWIO_PIDR2_JEDEC_VAL_BMSK                                              0x8
#define HWIO_PIDR2_JEDEC_VAL_SHFT                                              0x3
#define HWIO_PIDR2_DES_1_BMSK                                                  0x7
#define HWIO_PIDR2_DES_1_SHFT                                                  0x0

#define HWIO_PIDR3_ADDR(x)                                              ((x) + 0x00000fec)
#define HWIO_PIDR3_PHYS(x)                                              ((x) + 0x00000fec)
#define HWIO_PIDR3_RMSK                                                       0xff
#define HWIO_PIDR3_POR                                                  0x00000000
#define HWIO_PIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PIDR3_ATTR                                                        0x1
#define HWIO_PIDR3_IN(x)      \
        in_dword_masked(HWIO_PIDR3_ADDR(x), HWIO_PIDR3_RMSK)
#define HWIO_PIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PIDR3_ADDR(x), m)
#define HWIO_PIDR3_REVAND_BMSK                                                0xf0
#define HWIO_PIDR3_REVAND_SHFT                                                 0x4
#define HWIO_PIDR3_CMOD_BMSK                                                   0xf
#define HWIO_PIDR3_CMOD_SHFT                                                   0x0

#define HWIO_CIDR0_ADDR(x)                                              ((x) + 0x00000ff0)
#define HWIO_CIDR0_PHYS(x)                                              ((x) + 0x00000ff0)
#define HWIO_CIDR0_RMSK                                                       0xff
#define HWIO_CIDR0_POR                                                  0x0000000d
#define HWIO_CIDR0_POR_RMSK                                             0xffffffff
#define HWIO_CIDR0_ATTR                                                        0x1
#define HWIO_CIDR0_IN(x)      \
        in_dword_masked(HWIO_CIDR0_ADDR(x), HWIO_CIDR0_RMSK)
#define HWIO_CIDR0_INM(x, m)      \
        in_dword_masked(HWIO_CIDR0_ADDR(x), m)
#define HWIO_CIDR0_COMPONENT_IDR0_BMSK                                        0xff
#define HWIO_CIDR0_COMPONENT_IDR0_SHFT                                         0x0

#define HWIO_CIDR1_ADDR(x)                                              ((x) + 0x00000ff4)
#define HWIO_CIDR1_PHYS(x)                                              ((x) + 0x00000ff4)
#define HWIO_CIDR1_RMSK                                                       0xff
#define HWIO_CIDR1_POR                                                  0x000000f0
#define HWIO_CIDR1_POR_RMSK                                             0xffffffff
#define HWIO_CIDR1_ATTR                                                        0x1
#define HWIO_CIDR1_IN(x)      \
        in_dword_masked(HWIO_CIDR1_ADDR(x), HWIO_CIDR1_RMSK)
#define HWIO_CIDR1_INM(x, m)      \
        in_dword_masked(HWIO_CIDR1_ADDR(x), m)
#define HWIO_CIDR1_COMPONENT_IDR1_BMSK                                        0xff
#define HWIO_CIDR1_COMPONENT_IDR1_SHFT                                         0x0

#define HWIO_CIDR2_ADDR(x)                                              ((x) + 0x00000ff8)
#define HWIO_CIDR2_PHYS(x)                                              ((x) + 0x00000ff8)
#define HWIO_CIDR2_RMSK                                                       0xff
#define HWIO_CIDR2_POR                                                  0x00000005
#define HWIO_CIDR2_POR_RMSK                                             0xffffffff
#define HWIO_CIDR2_ATTR                                                        0x1
#define HWIO_CIDR2_IN(x)      \
        in_dword_masked(HWIO_CIDR2_ADDR(x), HWIO_CIDR2_RMSK)
#define HWIO_CIDR2_INM(x, m)      \
        in_dword_masked(HWIO_CIDR2_ADDR(x), m)
#define HWIO_CIDR2_COMPONENT_IDR2_BMSK                                        0xff
#define HWIO_CIDR2_COMPONENT_IDR2_SHFT                                         0x0

#define HWIO_CIDR3_ADDR(x)                                              ((x) + 0x00000ffc)
#define HWIO_CIDR3_PHYS(x)                                              ((x) + 0x00000ffc)
#define HWIO_CIDR3_RMSK                                                       0xff
#define HWIO_CIDR3_POR                                                  0x000000b1
#define HWIO_CIDR3_POR_RMSK                                             0xffffffff
#define HWIO_CIDR3_ATTR                                                        0x1
#define HWIO_CIDR3_IN(x)      \
        in_dword_masked(HWIO_CIDR3_ADDR(x), HWIO_CIDR3_RMSK)
#define HWIO_CIDR3_INM(x, m)      \
        in_dword_masked(HWIO_CIDR3_ADDR(x), m)
#define HWIO_CIDR3_COMPONENT_IDR3_BMSK                                        0xff
#define HWIO_CIDR3_COMPONENT_IDR3_SHFT                                         0x0

#define HWIO_QCR0_ADDR(x)                                               ((x) + 0x00001000)
#define HWIO_QCR0_PHYS(x)                                               ((x) + 0x00001000)
#define HWIO_QCR0_RMSK                                                        0x1a
#define HWIO_QCR0_POR                                                   0x00000012
#define HWIO_QCR0_POR_RMSK                                              0xffffffff
#define HWIO_QCR0_ATTR                                                         0x3
#define HWIO_QCR0_IN(x)      \
        in_dword_masked(HWIO_QCR0_ADDR(x), HWIO_QCR0_RMSK)
#define HWIO_QCR0_INM(x, m)      \
        in_dword_masked(HWIO_QCR0_ADDR(x), m)
#define HWIO_QCR0_OUT(x, v)      \
        out_dword(HWIO_QCR0_ADDR(x),v)
#define HWIO_QCR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QCR0_ADDR(x),m,v,HWIO_QCR0_IN(x))
#define HWIO_QCR0_CMDQ_SYNC_RESP_TRK_DIS_BMSK                                 0x10
#define HWIO_QCR0_CMDQ_SYNC_RESP_TRK_DIS_SHFT                                  0x4
#define HWIO_QCR0_STALL_ON_CMDQ_SYNC_BMSK                                      0x8
#define HWIO_QCR0_STALL_ON_CMDQ_SYNC_SHFT                                      0x3
#define HWIO_QCR0_AHB_ERROR_REPORT_EN_BMSK                                     0x2
#define HWIO_QCR0_AHB_ERROR_REPORT_EN_SHFT                                     0x1

#define HWIO_QTABLE_ACR1_ADDR(x)                                        ((x) + 0x00001020)
#define HWIO_QTABLE_ACR1_PHYS(x)                                        ((x) + 0x00001020)
#define HWIO_QTABLE_ACR1_RMSK                                                  0x7
#define HWIO_QTABLE_ACR1_POR                                            0x00000000
#define HWIO_QTABLE_ACR1_POR_RMSK                                       0xffffffff
#define HWIO_QTABLE_ACR1_ATTR                                                  0x3
#define HWIO_QTABLE_ACR1_IN(x)      \
        in_dword_masked(HWIO_QTABLE_ACR1_ADDR(x), HWIO_QTABLE_ACR1_RMSK)
#define HWIO_QTABLE_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QTABLE_ACR1_ADDR(x), m)
#define HWIO_QTABLE_ACR1_OUT(x, v)      \
        out_dword(HWIO_QTABLE_ACR1_ADDR(x),v)
#define HWIO_QTABLE_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QTABLE_ACR1_ADDR(x),m,v,HWIO_QTABLE_ACR1_IN(x))
#define HWIO_QTABLE_ACR1_TRCFG_BMSK                                            0x4
#define HWIO_QTABLE_ACR1_TRCFG_SHFT                                            0x2
#define HWIO_QTABLE_ACR1_REQPRIORITY_BMSK                                      0x3
#define HWIO_QTABLE_ACR1_REQPRIORITY_SHFT                                      0x0

#define HWIO_QQUEUE_ACR1_ADDR(x)                                        ((x) + 0x00001024)
#define HWIO_QQUEUE_ACR1_PHYS(x)                                        ((x) + 0x00001024)
#define HWIO_QQUEUE_ACR1_RMSK                                                  0x7
#define HWIO_QQUEUE_ACR1_POR                                            0x00000000
#define HWIO_QQUEUE_ACR1_POR_RMSK                                       0xffffffff
#define HWIO_QQUEUE_ACR1_ATTR                                                  0x3
#define HWIO_QQUEUE_ACR1_IN(x)      \
        in_dword_masked(HWIO_QQUEUE_ACR1_ADDR(x), HWIO_QQUEUE_ACR1_RMSK)
#define HWIO_QQUEUE_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QQUEUE_ACR1_ADDR(x), m)
#define HWIO_QQUEUE_ACR1_OUT(x, v)      \
        out_dword(HWIO_QQUEUE_ACR1_ADDR(x),v)
#define HWIO_QQUEUE_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QQUEUE_ACR1_ADDR(x),m,v,HWIO_QQUEUE_ACR1_IN(x))
#define HWIO_QQUEUE_ACR1_TRCFG_BMSK                                            0x4
#define HWIO_QQUEUE_ACR1_TRCFG_SHFT                                            0x2
#define HWIO_QQUEUE_ACR1_REQPRIORITY_BMSK                                      0x3
#define HWIO_QQUEUE_ACR1_REQPRIORITY_SHFT                                      0x0

#define HWIO_QGERROR_MSI_ACR1_ADDR(x)                                   ((x) + 0x00001028)
#define HWIO_QGERROR_MSI_ACR1_PHYS(x)                                   ((x) + 0x00001028)
#define HWIO_QGERROR_MSI_ACR1_RMSK                                             0xf
#define HWIO_QGERROR_MSI_ACR1_POR                                       0x00000000
#define HWIO_QGERROR_MSI_ACR1_POR_RMSK                                  0xffffffff
#define HWIO_QGERROR_MSI_ACR1_ATTR                                             0x3
#define HWIO_QGERROR_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QGERROR_MSI_ACR1_ADDR(x), HWIO_QGERROR_MSI_ACR1_RMSK)
#define HWIO_QGERROR_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QGERROR_MSI_ACR1_ADDR(x), m)
#define HWIO_QGERROR_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QGERROR_MSI_ACR1_ADDR(x),v)
#define HWIO_QGERROR_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGERROR_MSI_ACR1_ADDR(x),m,v,HWIO_QGERROR_MSI_ACR1_IN(x))
#define HWIO_QGERROR_MSI_ACR1_WA_BMSK                                          0x8
#define HWIO_QGERROR_MSI_ACR1_WA_SHFT                                          0x3
#define HWIO_QGERROR_MSI_ACR1_TRCFG_BMSK                                       0x4
#define HWIO_QGERROR_MSI_ACR1_TRCFG_SHFT                                       0x2
#define HWIO_QGERROR_MSI_ACR1_REQPRIORITY_BMSK                                 0x3
#define HWIO_QGERROR_MSI_ACR1_REQPRIORITY_SHFT                                 0x0

#define HWIO_QCMDQ_MSI_ACR1_ADDR(x)                                     ((x) + 0x0000102c)
#define HWIO_QCMDQ_MSI_ACR1_PHYS(x)                                     ((x) + 0x0000102c)
#define HWIO_QCMDQ_MSI_ACR1_RMSK                                               0xf
#define HWIO_QCMDQ_MSI_ACR1_POR                                         0x00000000
#define HWIO_QCMDQ_MSI_ACR1_POR_RMSK                                    0xffffffff
#define HWIO_QCMDQ_MSI_ACR1_ATTR                                               0x3
#define HWIO_QCMDQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QCMDQ_MSI_ACR1_ADDR(x), HWIO_QCMDQ_MSI_ACR1_RMSK)
#define HWIO_QCMDQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QCMDQ_MSI_ACR1_ADDR(x), m)
#define HWIO_QCMDQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QCMDQ_MSI_ACR1_ADDR(x),v)
#define HWIO_QCMDQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QCMDQ_MSI_ACR1_ADDR(x),m,v,HWIO_QCMDQ_MSI_ACR1_IN(x))
#define HWIO_QCMDQ_MSI_ACR1_WA_BMSK                                            0x8
#define HWIO_QCMDQ_MSI_ACR1_WA_SHFT                                            0x3
#define HWIO_QCMDQ_MSI_ACR1_TRCFG_BMSK                                         0x4
#define HWIO_QCMDQ_MSI_ACR1_TRCFG_SHFT                                         0x2
#define HWIO_QCMDQ_MSI_ACR1_REQPRIORITY_BMSK                                   0x3
#define HWIO_QCMDQ_MSI_ACR1_REQPRIORITY_SHFT                                   0x0

#define HWIO_QEVENTQ_MSI_ACR1_ADDR(x)                                   ((x) + 0x00001030)
#define HWIO_QEVENTQ_MSI_ACR1_PHYS(x)                                   ((x) + 0x00001030)
#define HWIO_QEVENTQ_MSI_ACR1_RMSK                                             0xf
#define HWIO_QEVENTQ_MSI_ACR1_POR                                       0x00000000
#define HWIO_QEVENTQ_MSI_ACR1_POR_RMSK                                  0xffffffff
#define HWIO_QEVENTQ_MSI_ACR1_ATTR                                             0x3
#define HWIO_QEVENTQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QEVENTQ_MSI_ACR1_ADDR(x), HWIO_QEVENTQ_MSI_ACR1_RMSK)
#define HWIO_QEVENTQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QEVENTQ_MSI_ACR1_ADDR(x), m)
#define HWIO_QEVENTQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QEVENTQ_MSI_ACR1_ADDR(x),v)
#define HWIO_QEVENTQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QEVENTQ_MSI_ACR1_ADDR(x),m,v,HWIO_QEVENTQ_MSI_ACR1_IN(x))
#define HWIO_QEVENTQ_MSI_ACR1_WA_BMSK                                          0x8
#define HWIO_QEVENTQ_MSI_ACR1_WA_SHFT                                          0x3
#define HWIO_QEVENTQ_MSI_ACR1_TRCFG_BMSK                                       0x4
#define HWIO_QEVENTQ_MSI_ACR1_TRCFG_SHFT                                       0x2
#define HWIO_QEVENTQ_MSI_ACR1_REQPRIORITY_BMSK                                 0x3
#define HWIO_QEVENTQ_MSI_ACR1_REQPRIORITY_SHFT                                 0x0

#define HWIO_QPRIQ_MSI_ACR1_ADDR(x)                                     ((x) + 0x00001034)
#define HWIO_QPRIQ_MSI_ACR1_PHYS(x)                                     ((x) + 0x00001034)
#define HWIO_QPRIQ_MSI_ACR1_RMSK                                               0xf
#define HWIO_QPRIQ_MSI_ACR1_POR                                         0x00000000
#define HWIO_QPRIQ_MSI_ACR1_POR_RMSK                                    0xffffffff
#define HWIO_QPRIQ_MSI_ACR1_ATTR                                               0x3
#define HWIO_QPRIQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QPRIQ_MSI_ACR1_ADDR(x), HWIO_QPRIQ_MSI_ACR1_RMSK)
#define HWIO_QPRIQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QPRIQ_MSI_ACR1_ADDR(x), m)
#define HWIO_QPRIQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QPRIQ_MSI_ACR1_ADDR(x),v)
#define HWIO_QPRIQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QPRIQ_MSI_ACR1_ADDR(x),m,v,HWIO_QPRIQ_MSI_ACR1_IN(x))
#define HWIO_QPRIQ_MSI_ACR1_WA_BMSK                                            0x8
#define HWIO_QPRIQ_MSI_ACR1_WA_SHFT                                            0x3
#define HWIO_QPRIQ_MSI_ACR1_TRCFG_BMSK                                         0x4
#define HWIO_QPRIQ_MSI_ACR1_TRCFG_SHFT                                         0x2
#define HWIO_QPRIQ_MSI_ACR1_REQPRIORITY_BMSK                                   0x3
#define HWIO_QPRIQ_MSI_ACR1_REQPRIORITY_SHFT                                   0x0

#define HWIO_QPMCG_MSI_ACR1_ADDR(x)                                     ((x) + 0x00001038)
#define HWIO_QPMCG_MSI_ACR1_PHYS(x)                                     ((x) + 0x00001038)
#define HWIO_QPMCG_MSI_ACR1_RMSK                                               0xf
#define HWIO_QPMCG_MSI_ACR1_POR                                         0x00000000
#define HWIO_QPMCG_MSI_ACR1_POR_RMSK                                    0xffffffff
#define HWIO_QPMCG_MSI_ACR1_ATTR                                               0x3
#define HWIO_QPMCG_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QPMCG_MSI_ACR1_ADDR(x), HWIO_QPMCG_MSI_ACR1_RMSK)
#define HWIO_QPMCG_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QPMCG_MSI_ACR1_ADDR(x), m)
#define HWIO_QPMCG_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QPMCG_MSI_ACR1_ADDR(x),v)
#define HWIO_QPMCG_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QPMCG_MSI_ACR1_ADDR(x),m,v,HWIO_QPMCG_MSI_ACR1_IN(x))
#define HWIO_QPMCG_MSI_ACR1_WA_BMSK                                            0x8
#define HWIO_QPMCG_MSI_ACR1_WA_SHFT                                            0x3
#define HWIO_QPMCG_MSI_ACR1_TRCFG_BMSK                                         0x4
#define HWIO_QPMCG_MSI_ACR1_TRCFG_SHFT                                         0x2
#define HWIO_QPMCG_MSI_ACR1_REQPRIORITY_BMSK                                   0x3
#define HWIO_QPMCG_MSI_ACR1_REQPRIORITY_SHFT                                   0x0

#define HWIO_QGERROR_ADDR(x)                                            ((x) + 0x0000103c)
#define HWIO_QGERROR_PHYS(x)                                            ((x) + 0x0000103c)
#define HWIO_QGERROR_RMSK                                               0xfffff803
#define HWIO_QGERROR_POR                                                0x00000000
#define HWIO_QGERROR_POR_RMSK                                           0xffffffff
#define HWIO_QGERROR_ATTR                                                      0x1
#define HWIO_QGERROR_IN(x)      \
        in_dword_masked(HWIO_QGERROR_ADDR(x), HWIO_QGERROR_RMSK)
#define HWIO_QGERROR_INM(x, m)      \
        in_dword_masked(HWIO_QGERROR_ADDR(x), m)
#define HWIO_QGERROR_SYNDROME_CFG_BMSK                                  0xffffe000
#define HWIO_QGERROR_SYNDROME_CFG_SHFT                                         0xd
#define HWIO_QGERROR_SYNDROME_PMCG_BMSK                                     0x1800
#define HWIO_QGERROR_SYNDROME_PMCG_SHFT                                        0xb
#define HWIO_QGERROR_MSI_PMCG_ABT_ERR_BMSK                                     0x2
#define HWIO_QGERROR_MSI_PMCG_ABT_ERR_SHFT                                     0x1
#define HWIO_QGERROR_CFG_FAULT_BMSK                                            0x1
#define HWIO_QGERROR_CFG_FAULT_SHFT                                            0x0

#define HWIO_QGERROR_RST_ADDR(x)                                        ((x) + 0x00001040)
#define HWIO_QGERROR_RST_PHYS(x)                                        ((x) + 0x00001040)
#define HWIO_QGERROR_RST_RMSK                                                  0x3
#define HWIO_QGERROR_RST_POR                                            0x00000000
#define HWIO_QGERROR_RST_POR_RMSK                                       0xffffffff
#define HWIO_QGERROR_RST_ATTR                                                  0x2
#define HWIO_QGERROR_RST_OUT(x, v)      \
        out_dword(HWIO_QGERROR_RST_ADDR(x),v)
#define HWIO_QGERROR_RST_MSI_PMCG_ABT_ERR_BMSK                                 0x2
#define HWIO_QGERROR_RST_MSI_PMCG_ABT_ERR_SHFT                                 0x1
#define HWIO_QGERROR_RST_CFG_FAULT_BMSK                                        0x1
#define HWIO_QGERROR_RST_CFG_FAULT_SHFT                                        0x0

#define HWIO_QGITS_GBPA_ADDR(x)                                         ((x) + 0x00001050)
#define HWIO_QGITS_GBPA_PHYS(x)                                         ((x) + 0x00001050)
#define HWIO_QGITS_GBPA_RMSK                                            0x801f3f1f
#define HWIO_QGITS_GBPA_POR                                             0x00002010
#define HWIO_QGITS_GBPA_POR_RMSK                                        0xffffffff
#define HWIO_QGITS_GBPA_ATTR                                                   0x3
#define HWIO_QGITS_GBPA_IN(x)      \
        in_dword_masked(HWIO_QGITS_GBPA_ADDR(x), HWIO_QGITS_GBPA_RMSK)
#define HWIO_QGITS_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_QGITS_GBPA_ADDR(x), m)
#define HWIO_QGITS_GBPA_OUT(x, v)      \
        out_dword(HWIO_QGITS_GBPA_ADDR(x),v)
#define HWIO_QGITS_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGITS_GBPA_ADDR(x),m,v,HWIO_QGITS_GBPA_IN(x))
#define HWIO_QGITS_GBPA_UPDATE_BMSK                                     0x80000000
#define HWIO_QGITS_GBPA_UPDATE_SHFT                                           0x1f
#define HWIO_QGITS_GBPA_ABORT_BMSK                                        0x100000
#define HWIO_QGITS_GBPA_ABORT_SHFT                                            0x14
#define HWIO_QGITS_GBPA_INSTCFG_BMSK                                       0xc0000
#define HWIO_QGITS_GBPA_INSTCFG_SHFT                                          0x12
#define HWIO_QGITS_GBPA_PRIVCFG_BMSK                                       0x30000
#define HWIO_QGITS_GBPA_PRIVCFG_SHFT                                          0x10
#define HWIO_QGITS_GBPA_SHCFG_BMSK                                          0x3000
#define HWIO_QGITS_GBPA_SHCFG_SHFT                                             0xc
#define HWIO_QGITS_GBPA_ALLOCCFG_BMSK                                        0xf00
#define HWIO_QGITS_GBPA_ALLOCCFG_SHFT                                          0x8
#define HWIO_QGITS_GBPA_MTCFG_BMSK                                            0x10
#define HWIO_QGITS_GBPA_MTCFG_SHFT                                             0x4
#define HWIO_QGITS_GBPA_MEMATTR_BMSK                                           0xf
#define HWIO_QGITS_GBPA_MEMATTR_SHFT                                           0x0

#define HWIO_QGITS_AGBPA_ADDR(x)                                        ((x) + 0x00001054)
#define HWIO_QGITS_AGBPA_PHYS(x)                                        ((x) + 0x00001054)
#define HWIO_QGITS_AGBPA_RMSK                                              0x7ffff
#define HWIO_QGITS_AGBPA_POR                                            0x00000000
#define HWIO_QGITS_AGBPA_POR_RMSK                                       0xffffffff
#define HWIO_QGITS_AGBPA_ATTR                                                  0x3
#define HWIO_QGITS_AGBPA_IN(x)      \
        in_dword_masked(HWIO_QGITS_AGBPA_ADDR(x), HWIO_QGITS_AGBPA_RMSK)
#define HWIO_QGITS_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_QGITS_AGBPA_ADDR(x), m)
#define HWIO_QGITS_AGBPA_OUT(x, v)      \
        out_dword(HWIO_QGITS_AGBPA_ADDR(x),v)
#define HWIO_QGITS_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGITS_AGBPA_ADDR(x),m,v,HWIO_QGITS_AGBPA_IN(x))
#define HWIO_QGITS_AGBPA_REQPRIORITY_BMSK                                  0x60000
#define HWIO_QGITS_AGBPA_REQPRIORITY_SHFT                                     0x11
#define HWIO_QGITS_AGBPA_REQPRIORITY_REPLACE_BMSK                          0x10000
#define HWIO_QGITS_AGBPA_REQPRIORITY_REPLACE_SHFT                             0x10
#define HWIO_QGITS_AGBPA_BPVMID_BMSK                                        0xffff
#define HWIO_QGITS_AGBPA_BPVMID_SHFT                                           0x0

#define HWIO_QDEVICEID_ADDR(x)                                          ((x) + 0x00001058)
#define HWIO_QDEVICEID_PHYS(x)                                          ((x) + 0x00001058)
#define HWIO_QDEVICEID_RMSK                                             0xffffffff
#define HWIO_QDEVICEID_POR                                              0x00000000
#define HWIO_QDEVICEID_POR_RMSK                                         0xffffffff
#define HWIO_QDEVICEID_ATTR                                                    0x3
#define HWIO_QDEVICEID_IN(x)      \
        in_dword_masked(HWIO_QDEVICEID_ADDR(x), HWIO_QDEVICEID_RMSK)
#define HWIO_QDEVICEID_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICEID_ADDR(x), m)
#define HWIO_QDEVICEID_OUT(x, v)      \
        out_dword(HWIO_QDEVICEID_ADDR(x),v)
#define HWIO_QDEVICEID_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICEID_ADDR(x),m,v,HWIO_QDEVICEID_IN(x))
#define HWIO_QDEVICEID_DEVICEID_BMSK                                    0xffffffff
#define HWIO_QDEVICEID_DEVICEID_SHFT                                           0x0

#define HWIO_QACT_CR0_ADDR(x)                                           ((x) + 0x00001060)
#define HWIO_QACT_CR0_PHYS(x)                                           ((x) + 0x00001060)
#define HWIO_QACT_CR0_RMSK                                                     0x3
#define HWIO_QACT_CR0_POR                                               0x00000001
#define HWIO_QACT_CR0_POR_RMSK                                          0xffffffff
#define HWIO_QACT_CR0_ATTR                                                     0x3
#define HWIO_QACT_CR0_IN(x)      \
        in_dword_masked(HWIO_QACT_CR0_ADDR(x), HWIO_QACT_CR0_RMSK)
#define HWIO_QACT_CR0_INM(x, m)      \
        in_dword_masked(HWIO_QACT_CR0_ADDR(x), m)
#define HWIO_QACT_CR0_OUT(x, v)      \
        out_dword(HWIO_QACT_CR0_ADDR(x),v)
#define HWIO_QACT_CR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QACT_CR0_ADDR(x),m,v,HWIO_QACT_CR0_IN(x))
#define HWIO_QACT_CR0_USA_VALID_BMSK                                           0x2
#define HWIO_QACT_CR0_USA_VALID_SHFT                                           0x1
#define HWIO_QACT_CR0_USA_BMSK                                                 0x1
#define HWIO_QACT_CR0_USA_SHFT                                                 0x0

#define HWIO_QTT_CNTL_ADDR(x)                                           ((x) + 0x0000108c)
#define HWIO_QTT_CNTL_PHYS(x)                                           ((x) + 0x0000108c)
#define HWIO_QTT_CNTL_RMSK                                                     0x1
#define HWIO_QTT_CNTL_POR                                               0x00000000
#define HWIO_QTT_CNTL_POR_RMSK                                          0xffffffff
#define HWIO_QTT_CNTL_ATTR                                                     0x3
#define HWIO_QTT_CNTL_IN(x)      \
        in_dword_masked(HWIO_QTT_CNTL_ADDR(x), HWIO_QTT_CNTL_RMSK)
#define HWIO_QTT_CNTL_INM(x, m)      \
        in_dword_masked(HWIO_QTT_CNTL_ADDR(x), m)
#define HWIO_QTT_CNTL_OUT(x, v)      \
        out_dword(HWIO_QTT_CNTL_ADDR(x),v)
#define HWIO_QTT_CNTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QTT_CNTL_ADDR(x),m,v,HWIO_QTT_CNTL_IN(x))
#define HWIO_QTT_CNTL_ATS_ATTR_OVR_BMSK                                        0x1
#define HWIO_QTT_CNTL_ATS_ATTR_OVR_SHFT                                        0x0

#define HWIO_QTT_GBPA_ADDR(x)                                           ((x) + 0x00001090)
#define HWIO_QTT_GBPA_PHYS(x)                                           ((x) + 0x00001090)
#define HWIO_QTT_GBPA_RMSK                                              0x800f3f0f
#define HWIO_QTT_GBPA_POR                                               0x0000280f
#define HWIO_QTT_GBPA_POR_RMSK                                          0xffffffff
#define HWIO_QTT_GBPA_ATTR                                                     0x3
#define HWIO_QTT_GBPA_IN(x)      \
        in_dword_masked(HWIO_QTT_GBPA_ADDR(x), HWIO_QTT_GBPA_RMSK)
#define HWIO_QTT_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_QTT_GBPA_ADDR(x), m)
#define HWIO_QTT_GBPA_OUT(x, v)      \
        out_dword(HWIO_QTT_GBPA_ADDR(x),v)
#define HWIO_QTT_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QTT_GBPA_ADDR(x),m,v,HWIO_QTT_GBPA_IN(x))
#define HWIO_QTT_GBPA_UPDATE_BMSK                                       0x80000000
#define HWIO_QTT_GBPA_UPDATE_SHFT                                             0x1f
#define HWIO_QTT_GBPA_INSTCFG_BMSK                                         0xc0000
#define HWIO_QTT_GBPA_INSTCFG_SHFT                                            0x12
#define HWIO_QTT_GBPA_PRIVCFG_BMSK                                         0x30000
#define HWIO_QTT_GBPA_PRIVCFG_SHFT                                            0x10
#define HWIO_QTT_GBPA_SHCFG_BMSK                                            0x3000
#define HWIO_QTT_GBPA_SHCFG_SHFT                                               0xc
#define HWIO_QTT_GBPA_ALLOCCFG_BMSK                                          0xf00
#define HWIO_QTT_GBPA_ALLOCCFG_SHFT                                            0x8
#define HWIO_QTT_GBPA_MEMATTR_BMSK                                             0xf
#define HWIO_QTT_GBPA_MEMATTR_SHFT                                             0x0

#define HWIO_QTT_AGBPA_ADDR(x)                                          ((x) + 0x00001094)
#define HWIO_QTT_AGBPA_PHYS(x)                                          ((x) + 0x00001094)
#define HWIO_QTT_AGBPA_RMSK                                                0x7ffff
#define HWIO_QTT_AGBPA_POR                                              0x00000000
#define HWIO_QTT_AGBPA_POR_RMSK                                         0xffffffff
#define HWIO_QTT_AGBPA_ATTR                                                    0x3
#define HWIO_QTT_AGBPA_IN(x)      \
        in_dword_masked(HWIO_QTT_AGBPA_ADDR(x), HWIO_QTT_AGBPA_RMSK)
#define HWIO_QTT_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_QTT_AGBPA_ADDR(x), m)
#define HWIO_QTT_AGBPA_OUT(x, v)      \
        out_dword(HWIO_QTT_AGBPA_ADDR(x),v)
#define HWIO_QTT_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QTT_AGBPA_ADDR(x),m,v,HWIO_QTT_AGBPA_IN(x))
#define HWIO_QTT_AGBPA_REQPRIORITY_BMSK                                    0x60000
#define HWIO_QTT_AGBPA_REQPRIORITY_SHFT                                       0x11
#define HWIO_QTT_AGBPA_REQPRIORITY_REPLACE_BMSK                            0x10000
#define HWIO_QTT_AGBPA_REQPRIORITY_REPLACE_SHFT                               0x10
#define HWIO_QTT_AGBPA_BPVMID_BMSK                                          0xffff
#define HWIO_QTT_AGBPA_BPVMID_SHFT                                             0x0

#define HWIO_S_IDR0_ADDR(x)                                             ((x) + 0x00008000)
#define HWIO_S_IDR0_PHYS(x)                                             ((x) + 0x00008000)
#define HWIO_S_IDR0_RMSK                                                 0x3002000
#define HWIO_S_IDR0_POR                                                 0x00002000
#define HWIO_S_IDR0_POR_RMSK                                            0xffffffff
#define HWIO_S_IDR0_ATTR                                                       0x1
#define HWIO_S_IDR0_IN(x)      \
        in_dword_masked(HWIO_S_IDR0_ADDR(x), HWIO_S_IDR0_RMSK)
#define HWIO_S_IDR0_INM(x, m)      \
        in_dword_masked(HWIO_S_IDR0_ADDR(x), m)
#define HWIO_S_IDR0_STALL_MODEL_BMSK                                     0x3000000
#define HWIO_S_IDR0_STALL_MODEL_SHFT                                          0x18
#define HWIO_S_IDR0_MSI_BMSK                                                0x2000
#define HWIO_S_IDR0_MSI_SHFT                                                   0xd

#define HWIO_S_IDR1_ADDR(x)                                             ((x) + 0x00008004)
#define HWIO_S_IDR1_PHYS(x)                                             ((x) + 0x00008004)
#define HWIO_S_IDR1_RMSK                                                0x8000001f
#define HWIO_S_IDR1_POR                                                 0x80000010
#define HWIO_S_IDR1_POR_RMSK                                            0xffffffff
#define HWIO_S_IDR1_ATTR                                                       0x1
#define HWIO_S_IDR1_IN(x)      \
        in_dword_masked(HWIO_S_IDR1_ADDR(x), HWIO_S_IDR1_RMSK)
#define HWIO_S_IDR1_INM(x, m)      \
        in_dword_masked(HWIO_S_IDR1_ADDR(x), m)
#define HWIO_S_IDR1_SECURE_IMPL_BMSK                                    0x80000000
#define HWIO_S_IDR1_SECURE_IMPL_SHFT                                          0x1f
#define HWIO_S_IDR1_S_SIDSIZE_BMSK                                            0x1f
#define HWIO_S_IDR1_S_SIDSIZE_SHFT                                             0x0

#define HWIO_S_IDR2_ADDR(x)                                             ((x) + 0x00008008)
#define HWIO_S_IDR2_PHYS(x)                                             ((x) + 0x00008008)
#define HWIO_S_IDR2_RMSK                                                0xffffffff
#define HWIO_S_IDR2_POR                                                 0x00000000
#define HWIO_S_IDR2_POR_RMSK                                            0xffffffff
#define HWIO_S_IDR2_ATTR                                                       0x1
#define HWIO_S_IDR2_IN(x)      \
        in_dword_masked(HWIO_S_IDR2_ADDR(x), HWIO_S_IDR2_RMSK)
#define HWIO_S_IDR2_INM(x, m)      \
        in_dword_masked(HWIO_S_IDR2_ADDR(x), m)
#define HWIO_S_IDR2_RSRVED_31_0_BMSK                                    0xffffffff
#define HWIO_S_IDR2_RSRVED_31_0_SHFT                                           0x0

#define HWIO_S_IDR3_ADDR(x)                                             ((x) + 0x0000800c)
#define HWIO_S_IDR3_PHYS(x)                                             ((x) + 0x0000800c)
#define HWIO_S_IDR3_RMSK                                                0xffffffff
#define HWIO_S_IDR3_POR                                                 0x00000000
#define HWIO_S_IDR3_POR_RMSK                                            0xffffffff
#define HWIO_S_IDR3_ATTR                                                       0x1
#define HWIO_S_IDR3_IN(x)      \
        in_dword_masked(HWIO_S_IDR3_ADDR(x), HWIO_S_IDR3_RMSK)
#define HWIO_S_IDR3_INM(x, m)      \
        in_dword_masked(HWIO_S_IDR3_ADDR(x), m)
#define HWIO_S_IDR3_RSRVED_31_0_BMSK                                    0xffffffff
#define HWIO_S_IDR3_RSRVED_31_0_SHFT                                           0x0

#define HWIO_S_IDR4_ADDR(x)                                             ((x) + 0x00008010)
#define HWIO_S_IDR4_PHYS(x)                                             ((x) + 0x00008010)
#define HWIO_S_IDR4_RMSK                                                0xffffffff
#define HWIO_S_IDR4_POR                                                 0x00000000
#define HWIO_S_IDR4_POR_RMSK                                            0xffffffff
#define HWIO_S_IDR4_ATTR                                                       0x1
#define HWIO_S_IDR4_IN(x)      \
        in_dword_masked(HWIO_S_IDR4_ADDR(x), HWIO_S_IDR4_RMSK)
#define HWIO_S_IDR4_INM(x, m)      \
        in_dword_masked(HWIO_S_IDR4_ADDR(x), m)
#define HWIO_S_IDR4_IMPDEF_BMSK                                         0xffffffff
#define HWIO_S_IDR4_IMPDEF_SHFT                                                0x0

#define HWIO_S_CR0_ADDR(x)                                              ((x) + 0x00008020)
#define HWIO_S_CR0_PHYS(x)                                              ((x) + 0x00008020)
#define HWIO_S_CR0_RMSK                                                      0x22d
#define HWIO_S_CR0_POR                                                  0x00000000
#define HWIO_S_CR0_POR_RMSK                                             0xffffffff
#define HWIO_S_CR0_ATTR                                                        0x3
#define HWIO_S_CR0_IN(x)      \
        in_dword_masked(HWIO_S_CR0_ADDR(x), HWIO_S_CR0_RMSK)
#define HWIO_S_CR0_INM(x, m)      \
        in_dword_masked(HWIO_S_CR0_ADDR(x), m)
#define HWIO_S_CR0_OUT(x, v)      \
        out_dword(HWIO_S_CR0_ADDR(x),v)
#define HWIO_S_CR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_CR0_ADDR(x),m,v,HWIO_S_CR0_IN(x))
#define HWIO_S_CR0_NSSTALLD_BMSK                                             0x200
#define HWIO_S_CR0_NSSTALLD_SHFT                                               0x9
#define HWIO_S_CR0_SIF_BMSK                                                   0x20
#define HWIO_S_CR0_SIF_SHFT                                                    0x5
#define HWIO_S_CR0_CMDQEN_BMSK                                                 0x8
#define HWIO_S_CR0_CMDQEN_SHFT                                                 0x3
#define HWIO_S_CR0_EVENTQEN_BMSK                                               0x4
#define HWIO_S_CR0_EVENTQEN_SHFT                                               0x2
#define HWIO_S_CR0_SMMUEN_BMSK                                                 0x1
#define HWIO_S_CR0_SMMUEN_SHFT                                                 0x0

#define HWIO_S_CR0ACK_ADDR(x)                                           ((x) + 0x00008024)
#define HWIO_S_CR0ACK_PHYS(x)                                           ((x) + 0x00008024)
#define HWIO_S_CR0ACK_RMSK                                                   0x22d
#define HWIO_S_CR0ACK_POR                                               0x00000000
#define HWIO_S_CR0ACK_POR_RMSK                                          0xffffffff
#define HWIO_S_CR0ACK_ATTR                                                     0x1
#define HWIO_S_CR0ACK_IN(x)      \
        in_dword_masked(HWIO_S_CR0ACK_ADDR(x), HWIO_S_CR0ACK_RMSK)
#define HWIO_S_CR0ACK_INM(x, m)      \
        in_dword_masked(HWIO_S_CR0ACK_ADDR(x), m)
#define HWIO_S_CR0ACK_NSSTALLD_BMSK                                          0x200
#define HWIO_S_CR0ACK_NSSTALLD_SHFT                                            0x9
#define HWIO_S_CR0ACK_SIF_BMSK                                                0x20
#define HWIO_S_CR0ACK_SIF_SHFT                                                 0x5
#define HWIO_S_CR0ACK_CMDQEN_BMSK                                              0x8
#define HWIO_S_CR0ACK_CMDQEN_SHFT                                              0x3
#define HWIO_S_CR0ACK_EVENTQEN_BMSK                                            0x4
#define HWIO_S_CR0ACK_EVENTQEN_SHFT                                            0x2
#define HWIO_S_CR0ACK_SMMUEN_BMSK                                              0x1
#define HWIO_S_CR0ACK_SMMUEN_SHFT                                              0x0

#define HWIO_S_CR1_ADDR(x)                                              ((x) + 0x00008028)
#define HWIO_S_CR1_PHYS(x)                                              ((x) + 0x00008028)
#define HWIO_S_CR1_RMSK                                                      0xfff
#define HWIO_S_CR1_POR                                                  0x00000000
#define HWIO_S_CR1_POR_RMSK                                             0xffffffff
#define HWIO_S_CR1_ATTR                                                        0x3
#define HWIO_S_CR1_IN(x)      \
        in_dword_masked(HWIO_S_CR1_ADDR(x), HWIO_S_CR1_RMSK)
#define HWIO_S_CR1_INM(x, m)      \
        in_dword_masked(HWIO_S_CR1_ADDR(x), m)
#define HWIO_S_CR1_OUT(x, v)      \
        out_dword(HWIO_S_CR1_ADDR(x),v)
#define HWIO_S_CR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_CR1_ADDR(x),m,v,HWIO_S_CR1_IN(x))
#define HWIO_S_CR1_TABLE_SH_BMSK                                             0xc00
#define HWIO_S_CR1_TABLE_SH_SHFT                                               0xa
#define HWIO_S_CR1_TABLE_OC_BMSK                                             0x300
#define HWIO_S_CR1_TABLE_OC_SHFT                                               0x8
#define HWIO_S_CR1_TABLE_IC_BMSK                                              0xc0
#define HWIO_S_CR1_TABLE_IC_SHFT                                               0x6
#define HWIO_S_CR1_QUEUE_SH_BMSK                                              0x30
#define HWIO_S_CR1_QUEUE_SH_SHFT                                               0x4
#define HWIO_S_CR1_QUEUE_OC_BMSK                                               0xc
#define HWIO_S_CR1_QUEUE_OC_SHFT                                               0x2
#define HWIO_S_CR1_QUEUE_IC_BMSK                                               0x3
#define HWIO_S_CR1_QUEUE_IC_SHFT                                               0x0

#define HWIO_S_CR2_ADDR(x)                                              ((x) + 0x0000802c)
#define HWIO_S_CR2_PHYS(x)                                              ((x) + 0x0000802c)
#define HWIO_S_CR2_RMSK                                                        0x6
#define HWIO_S_CR2_POR                                                  0x00000004
#define HWIO_S_CR2_POR_RMSK                                             0xffffffff
#define HWIO_S_CR2_ATTR                                                        0x3
#define HWIO_S_CR2_IN(x)      \
        in_dword_masked(HWIO_S_CR2_ADDR(x), HWIO_S_CR2_RMSK)
#define HWIO_S_CR2_INM(x, m)      \
        in_dword_masked(HWIO_S_CR2_ADDR(x), m)
#define HWIO_S_CR2_OUT(x, v)      \
        out_dword(HWIO_S_CR2_ADDR(x),v)
#define HWIO_S_CR2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_CR2_ADDR(x),m,v,HWIO_S_CR2_IN(x))
#define HWIO_S_CR2_PTM_BMSK                                                    0x4
#define HWIO_S_CR2_PTM_SHFT                                                    0x2
#define HWIO_S_CR2_RECINVSID_BMSK                                              0x2
#define HWIO_S_CR2_RECINVSID_SHFT                                              0x1

#define HWIO_S_INIT_ADDR(x)                                             ((x) + 0x0000803c)
#define HWIO_S_INIT_PHYS(x)                                             ((x) + 0x0000803c)
#define HWIO_S_INIT_RMSK                                                       0x1
#define HWIO_S_INIT_POR                                                 0x00000000
#define HWIO_S_INIT_POR_RMSK                                            0xffffffff
#define HWIO_S_INIT_ATTR                                                       0x3
#define HWIO_S_INIT_IN(x)      \
        in_dword_masked(HWIO_S_INIT_ADDR(x), HWIO_S_INIT_RMSK)
#define HWIO_S_INIT_INM(x, m)      \
        in_dword_masked(HWIO_S_INIT_ADDR(x), m)
#define HWIO_S_INIT_OUT(x, v)      \
        out_dword(HWIO_S_INIT_ADDR(x),v)
#define HWIO_S_INIT_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_INIT_ADDR(x),m,v,HWIO_S_INIT_IN(x))
#define HWIO_S_INIT_INV_ALL_BMSK                                               0x1
#define HWIO_S_INIT_INV_ALL_SHFT                                               0x0

#define HWIO_S_GBPA_ADDR(x)                                             ((x) + 0x00008044)
#define HWIO_S_GBPA_PHYS(x)                                             ((x) + 0x00008044)
#define HWIO_S_GBPA_RMSK                                                0x801fff1f
#define HWIO_S_GBPA_POR                                                 0x00001000
#define HWIO_S_GBPA_POR_RMSK                                            0xffffffff
#define HWIO_S_GBPA_ATTR                                                       0x3
#define HWIO_S_GBPA_IN(x)      \
        in_dword_masked(HWIO_S_GBPA_ADDR(x), HWIO_S_GBPA_RMSK)
#define HWIO_S_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_S_GBPA_ADDR(x), m)
#define HWIO_S_GBPA_OUT(x, v)      \
        out_dword(HWIO_S_GBPA_ADDR(x),v)
#define HWIO_S_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GBPA_ADDR(x),m,v,HWIO_S_GBPA_IN(x))
#define HWIO_S_GBPA_UPDATE_BMSK                                         0x80000000
#define HWIO_S_GBPA_UPDATE_SHFT                                               0x1f
#define HWIO_S_GBPA_ABORT_BMSK                                            0x100000
#define HWIO_S_GBPA_ABORT_SHFT                                                0x14
#define HWIO_S_GBPA_INSTCFG_BMSK                                           0xc0000
#define HWIO_S_GBPA_INSTCFG_SHFT                                              0x12
#define HWIO_S_GBPA_PRIVCFG_BMSK                                           0x30000
#define HWIO_S_GBPA_PRIVCFG_SHFT                                              0x10
#define HWIO_S_GBPA_NSCFG_BMSK                                              0xc000
#define HWIO_S_GBPA_NSCFG_SHFT                                                 0xe
#define HWIO_S_GBPA_SHCFG_BMSK                                              0x3000
#define HWIO_S_GBPA_SHCFG_SHFT                                                 0xc
#define HWIO_S_GBPA_ALLOCCFG_BMSK                                            0xf00
#define HWIO_S_GBPA_ALLOCCFG_SHFT                                              0x8
#define HWIO_S_GBPA_MTCFG_BMSK                                                0x10
#define HWIO_S_GBPA_MTCFG_SHFT                                                 0x4
#define HWIO_S_GBPA_MEMATTR_BMSK                                               0xf
#define HWIO_S_GBPA_MEMATTR_SHFT                                               0x0

#define HWIO_S_AGBPA_ADDR(x)                                            ((x) + 0x00008048)
#define HWIO_S_AGBPA_PHYS(x)                                            ((x) + 0x00008048)
#define HWIO_S_AGBPA_RMSK                                                  0x7ffff
#define HWIO_S_AGBPA_POR                                                0x00000000
#define HWIO_S_AGBPA_POR_RMSK                                           0xffffffff
#define HWIO_S_AGBPA_ATTR                                                      0x3
#define HWIO_S_AGBPA_IN(x)      \
        in_dword_masked(HWIO_S_AGBPA_ADDR(x), HWIO_S_AGBPA_RMSK)
#define HWIO_S_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_S_AGBPA_ADDR(x), m)
#define HWIO_S_AGBPA_OUT(x, v)      \
        out_dword(HWIO_S_AGBPA_ADDR(x),v)
#define HWIO_S_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_AGBPA_ADDR(x),m,v,HWIO_S_AGBPA_IN(x))
#define HWIO_S_AGBPA_REQPRIORITY_BMSK                                      0x60000
#define HWIO_S_AGBPA_REQPRIORITY_SHFT                                         0x11
#define HWIO_S_AGBPA_REQPRIORITY_REPLACE_BMSK                              0x10000
#define HWIO_S_AGBPA_REQPRIORITY_REPLACE_SHFT                                 0x10
#define HWIO_S_AGBPA_BPVMID_BMSK                                            0xffff
#define HWIO_S_AGBPA_BPVMID_SHFT                                               0x0

#define HWIO_S_IRQ_CTRL_ADDR(x)                                         ((x) + 0x00008050)
#define HWIO_S_IRQ_CTRL_PHYS(x)                                         ((x) + 0x00008050)
#define HWIO_S_IRQ_CTRL_RMSK                                                   0x5
#define HWIO_S_IRQ_CTRL_POR                                             0x00000000
#define HWIO_S_IRQ_CTRL_POR_RMSK                                        0xffffffff
#define HWIO_S_IRQ_CTRL_ATTR                                                   0x3
#define HWIO_S_IRQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_S_IRQ_CTRL_ADDR(x), HWIO_S_IRQ_CTRL_RMSK)
#define HWIO_S_IRQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_S_IRQ_CTRL_ADDR(x), m)
#define HWIO_S_IRQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_S_IRQ_CTRL_ADDR(x),v)
#define HWIO_S_IRQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_IRQ_CTRL_ADDR(x),m,v,HWIO_S_IRQ_CTRL_IN(x))
#define HWIO_S_IRQ_CTRL_EVENTQ_IRQEN_BMSK                                      0x4
#define HWIO_S_IRQ_CTRL_EVENTQ_IRQEN_SHFT                                      0x2
#define HWIO_S_IRQ_CTRL_GERROR_IRQEN_BMSK                                      0x1
#define HWIO_S_IRQ_CTRL_GERROR_IRQEN_SHFT                                      0x0

#define HWIO_S_IRQ_CTRLACK_ADDR(x)                                      ((x) + 0x00008054)
#define HWIO_S_IRQ_CTRLACK_PHYS(x)                                      ((x) + 0x00008054)
#define HWIO_S_IRQ_CTRLACK_RMSK                                                0x5
#define HWIO_S_IRQ_CTRLACK_POR                                          0x00000000
#define HWIO_S_IRQ_CTRLACK_POR_RMSK                                     0xffffffff
#define HWIO_S_IRQ_CTRLACK_ATTR                                                0x1
#define HWIO_S_IRQ_CTRLACK_IN(x)      \
        in_dword_masked(HWIO_S_IRQ_CTRLACK_ADDR(x), HWIO_S_IRQ_CTRLACK_RMSK)
#define HWIO_S_IRQ_CTRLACK_INM(x, m)      \
        in_dword_masked(HWIO_S_IRQ_CTRLACK_ADDR(x), m)
#define HWIO_S_IRQ_CTRLACK_EVENTQ_IRQEN_BMSK                                   0x4
#define HWIO_S_IRQ_CTRLACK_EVENTQ_IRQEN_SHFT                                   0x2
#define HWIO_S_IRQ_CTRLACK_GERROR_IRQEN_BMSK                                   0x1
#define HWIO_S_IRQ_CTRLACK_GERROR_IRQEN_SHFT                                   0x0

#define HWIO_S_GERROR_ADDR(x)                                           ((x) + 0x00008060)
#define HWIO_S_GERROR_PHYS(x)                                           ((x) + 0x00008060)
#define HWIO_S_GERROR_RMSK                                                   0x1b5
#define HWIO_S_GERROR_POR                                               0x00000000
#define HWIO_S_GERROR_POR_RMSK                                          0xffffffff
#define HWIO_S_GERROR_ATTR                                                     0x1
#define HWIO_S_GERROR_IN(x)      \
        in_dword_masked(HWIO_S_GERROR_ADDR(x), HWIO_S_GERROR_RMSK)
#define HWIO_S_GERROR_INM(x, m)      \
        in_dword_masked(HWIO_S_GERROR_ADDR(x), m)
#define HWIO_S_GERROR_SFM_ERR_BMSK                                           0x100
#define HWIO_S_GERROR_SFM_ERR_SHFT                                             0x8
#define HWIO_S_GERROR_MSI_GERROR_ABT_ERR_BMSK                                 0x80
#define HWIO_S_GERROR_MSI_GERROR_ABT_ERR_SHFT                                  0x7
#define HWIO_S_GERROR_MSI_EVENTQ_ABT_ERR_BMSK                                 0x20
#define HWIO_S_GERROR_MSI_EVENTQ_ABT_ERR_SHFT                                  0x5
#define HWIO_S_GERROR_MSI_CMDQ_ABT_ERR_BMSK                                   0x10
#define HWIO_S_GERROR_MSI_CMDQ_ABT_ERR_SHFT                                    0x4
#define HWIO_S_GERROR_EVENTQ_ABT_ERR_BMSK                                      0x4
#define HWIO_S_GERROR_EVENTQ_ABT_ERR_SHFT                                      0x2
#define HWIO_S_GERROR_CMDQ_ERR_BMSK                                            0x1
#define HWIO_S_GERROR_CMDQ_ERR_SHFT                                            0x0

#define HWIO_S_GERRORN_ADDR(x)                                          ((x) + 0x00008064)
#define HWIO_S_GERRORN_PHYS(x)                                          ((x) + 0x00008064)
#define HWIO_S_GERRORN_RMSK                                                  0x1b5
#define HWIO_S_GERRORN_POR                                              0x00000000
#define HWIO_S_GERRORN_POR_RMSK                                         0xffffffff
#define HWIO_S_GERRORN_ATTR                                                    0x3
#define HWIO_S_GERRORN_IN(x)      \
        in_dword_masked(HWIO_S_GERRORN_ADDR(x), HWIO_S_GERRORN_RMSK)
#define HWIO_S_GERRORN_INM(x, m)      \
        in_dword_masked(HWIO_S_GERRORN_ADDR(x), m)
#define HWIO_S_GERRORN_OUT(x, v)      \
        out_dword(HWIO_S_GERRORN_ADDR(x),v)
#define HWIO_S_GERRORN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GERRORN_ADDR(x),m,v,HWIO_S_GERRORN_IN(x))
#define HWIO_S_GERRORN_SFM_ERR_BMSK                                          0x100
#define HWIO_S_GERRORN_SFM_ERR_SHFT                                            0x8
#define HWIO_S_GERRORN_MSI_GERROR_ABT_ERR_BMSK                                0x80
#define HWIO_S_GERRORN_MSI_GERROR_ABT_ERR_SHFT                                 0x7
#define HWIO_S_GERRORN_MSI_EVENTQ_ABT_ERR_BMSK                                0x20
#define HWIO_S_GERRORN_MSI_EVENTQ_ABT_ERR_SHFT                                 0x5
#define HWIO_S_GERRORN_MSI_CMDQ_ABT_ERR_BMSK                                  0x10
#define HWIO_S_GERRORN_MSI_CMDQ_ABT_ERR_SHFT                                   0x4
#define HWIO_S_GERRORN_EVENTQ_ABT_ERR_BMSK                                     0x4
#define HWIO_S_GERRORN_EVENTQ_ABT_ERR_SHFT                                     0x2
#define HWIO_S_GERRORN_CMDQ_ERR_BMSK                                           0x1
#define HWIO_S_GERRORN_CMDQ_ERR_SHFT                                           0x0

#define HWIO_S_GERROR_IRQ_CFG0_L_ADDR(x)                                ((x) + 0x00008068)
#define HWIO_S_GERROR_IRQ_CFG0_L_PHYS(x)                                ((x) + 0x00008068)
#define HWIO_S_GERROR_IRQ_CFG0_L_RMSK                                   0xfffffffc
#define HWIO_S_GERROR_IRQ_CFG0_L_POR                                    0x00000000
#define HWIO_S_GERROR_IRQ_CFG0_L_POR_RMSK                               0xffffffff
#define HWIO_S_GERROR_IRQ_CFG0_L_ATTR                                          0x3
#define HWIO_S_GERROR_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_S_GERROR_IRQ_CFG0_L_ADDR(x), HWIO_S_GERROR_IRQ_CFG0_L_RMSK)
#define HWIO_S_GERROR_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_S_GERROR_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_S_GERROR_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_S_GERROR_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_S_GERROR_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GERROR_IRQ_CFG0_L_ADDR(x),m,v,HWIO_S_GERROR_IRQ_CFG0_L_IN(x))
#define HWIO_S_GERROR_IRQ_CFG0_L_ADDR_31_2_BMSK                         0xfffffffc
#define HWIO_S_GERROR_IRQ_CFG0_L_ADDR_31_2_SHFT                                0x2

#define HWIO_S_GERROR_IRQ_CFG0_H_ADDR(x)                                ((x) + 0x0000806c)
#define HWIO_S_GERROR_IRQ_CFG0_H_PHYS(x)                                ((x) + 0x0000806c)
#define HWIO_S_GERROR_IRQ_CFG0_H_RMSK                                       0xffff
#define HWIO_S_GERROR_IRQ_CFG0_H_POR                                    0x00000000
#define HWIO_S_GERROR_IRQ_CFG0_H_POR_RMSK                               0xffffffff
#define HWIO_S_GERROR_IRQ_CFG0_H_ATTR                                          0x3
#define HWIO_S_GERROR_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_S_GERROR_IRQ_CFG0_H_ADDR(x), HWIO_S_GERROR_IRQ_CFG0_H_RMSK)
#define HWIO_S_GERROR_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_S_GERROR_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_S_GERROR_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_S_GERROR_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_S_GERROR_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GERROR_IRQ_CFG0_H_ADDR(x),m,v,HWIO_S_GERROR_IRQ_CFG0_H_IN(x))
#define HWIO_S_GERROR_IRQ_CFG0_H_ADDR_47_32_BMSK                            0xffff
#define HWIO_S_GERROR_IRQ_CFG0_H_ADDR_47_32_SHFT                               0x0

#define HWIO_S_GERROR_IRQ_CFG1_ADDR(x)                                  ((x) + 0x00008070)
#define HWIO_S_GERROR_IRQ_CFG1_PHYS(x)                                  ((x) + 0x00008070)
#define HWIO_S_GERROR_IRQ_CFG1_RMSK                                     0xffffffff
#define HWIO_S_GERROR_IRQ_CFG1_POR                                      0x00000000
#define HWIO_S_GERROR_IRQ_CFG1_POR_RMSK                                 0xffffffff
#define HWIO_S_GERROR_IRQ_CFG1_ATTR                                            0x3
#define HWIO_S_GERROR_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_S_GERROR_IRQ_CFG1_ADDR(x), HWIO_S_GERROR_IRQ_CFG1_RMSK)
#define HWIO_S_GERROR_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_S_GERROR_IRQ_CFG1_ADDR(x), m)
#define HWIO_S_GERROR_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_S_GERROR_IRQ_CFG1_ADDR(x),v)
#define HWIO_S_GERROR_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GERROR_IRQ_CFG1_ADDR(x),m,v,HWIO_S_GERROR_IRQ_CFG1_IN(x))
#define HWIO_S_GERROR_IRQ_CFG1_DATA_BMSK                                0xffffffff
#define HWIO_S_GERROR_IRQ_CFG1_DATA_SHFT                                       0x0

#define HWIO_S_GERROR_IRQ_CFG2_ADDR(x)                                  ((x) + 0x00008074)
#define HWIO_S_GERROR_IRQ_CFG2_PHYS(x)                                  ((x) + 0x00008074)
#define HWIO_S_GERROR_IRQ_CFG2_RMSK                                           0x3f
#define HWIO_S_GERROR_IRQ_CFG2_POR                                      0x00000000
#define HWIO_S_GERROR_IRQ_CFG2_POR_RMSK                                 0xffffffff
#define HWIO_S_GERROR_IRQ_CFG2_ATTR                                            0x3
#define HWIO_S_GERROR_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_S_GERROR_IRQ_CFG2_ADDR(x), HWIO_S_GERROR_IRQ_CFG2_RMSK)
#define HWIO_S_GERROR_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_S_GERROR_IRQ_CFG2_ADDR(x), m)
#define HWIO_S_GERROR_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_S_GERROR_IRQ_CFG2_ADDR(x),v)
#define HWIO_S_GERROR_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GERROR_IRQ_CFG2_ADDR(x),m,v,HWIO_S_GERROR_IRQ_CFG2_IN(x))
#define HWIO_S_GERROR_IRQ_CFG2_SH_BMSK                                        0x30
#define HWIO_S_GERROR_IRQ_CFG2_SH_SHFT                                         0x4
#define HWIO_S_GERROR_IRQ_CFG2_MEMATTR_BMSK                                    0xf
#define HWIO_S_GERROR_IRQ_CFG2_MEMATTR_SHFT                                    0x0

#define HWIO_S_STRTAB_BASE_L_ADDR(x)                                    ((x) + 0x00008080)
#define HWIO_S_STRTAB_BASE_L_PHYS(x)                                    ((x) + 0x00008080)
#define HWIO_S_STRTAB_BASE_L_RMSK                                       0xffffffc0
#define HWIO_S_STRTAB_BASE_L_POR                                        0x00000000
#define HWIO_S_STRTAB_BASE_L_POR_RMSK                                   0xffffffff
#define HWIO_S_STRTAB_BASE_L_ATTR                                              0x3
#define HWIO_S_STRTAB_BASE_L_IN(x)      \
        in_dword_masked(HWIO_S_STRTAB_BASE_L_ADDR(x), HWIO_S_STRTAB_BASE_L_RMSK)
#define HWIO_S_STRTAB_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_S_STRTAB_BASE_L_ADDR(x), m)
#define HWIO_S_STRTAB_BASE_L_OUT(x, v)      \
        out_dword(HWIO_S_STRTAB_BASE_L_ADDR(x),v)
#define HWIO_S_STRTAB_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_STRTAB_BASE_L_ADDR(x),m,v,HWIO_S_STRTAB_BASE_L_IN(x))
#define HWIO_S_STRTAB_BASE_L_ADDR_31_6_BMSK                             0xffffffc0
#define HWIO_S_STRTAB_BASE_L_ADDR_31_6_SHFT                                    0x6

#define HWIO_S_STRTAB_BASE_H_ADDR(x)                                    ((x) + 0x00008084)
#define HWIO_S_STRTAB_BASE_H_PHYS(x)                                    ((x) + 0x00008084)
#define HWIO_S_STRTAB_BASE_H_RMSK                                       0x4000ffff
#define HWIO_S_STRTAB_BASE_H_POR                                        0x00000000
#define HWIO_S_STRTAB_BASE_H_POR_RMSK                                   0xffffffff
#define HWIO_S_STRTAB_BASE_H_ATTR                                              0x3
#define HWIO_S_STRTAB_BASE_H_IN(x)      \
        in_dword_masked(HWIO_S_STRTAB_BASE_H_ADDR(x), HWIO_S_STRTAB_BASE_H_RMSK)
#define HWIO_S_STRTAB_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_S_STRTAB_BASE_H_ADDR(x), m)
#define HWIO_S_STRTAB_BASE_H_OUT(x, v)      \
        out_dword(HWIO_S_STRTAB_BASE_H_ADDR(x),v)
#define HWIO_S_STRTAB_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_STRTAB_BASE_H_ADDR(x),m,v,HWIO_S_STRTAB_BASE_H_IN(x))
#define HWIO_S_STRTAB_BASE_H_RA_BMSK                                    0x40000000
#define HWIO_S_STRTAB_BASE_H_RA_SHFT                                          0x1e
#define HWIO_S_STRTAB_BASE_H_ADDR_47_32_BMSK                                0xffff
#define HWIO_S_STRTAB_BASE_H_ADDR_47_32_SHFT                                   0x0

#define HWIO_S_STRTAB_BASE_CFG_ADDR(x)                                  ((x) + 0x00008088)
#define HWIO_S_STRTAB_BASE_CFG_PHYS(x)                                  ((x) + 0x00008088)
#define HWIO_S_STRTAB_BASE_CFG_RMSK                                        0x307ff
#define HWIO_S_STRTAB_BASE_CFG_POR                                      0x00000000
#define HWIO_S_STRTAB_BASE_CFG_POR_RMSK                                 0xffffffff
#define HWIO_S_STRTAB_BASE_CFG_ATTR                                            0x3
#define HWIO_S_STRTAB_BASE_CFG_IN(x)      \
        in_dword_masked(HWIO_S_STRTAB_BASE_CFG_ADDR(x), HWIO_S_STRTAB_BASE_CFG_RMSK)
#define HWIO_S_STRTAB_BASE_CFG_INM(x, m)      \
        in_dword_masked(HWIO_S_STRTAB_BASE_CFG_ADDR(x), m)
#define HWIO_S_STRTAB_BASE_CFG_OUT(x, v)      \
        out_dword(HWIO_S_STRTAB_BASE_CFG_ADDR(x),v)
#define HWIO_S_STRTAB_BASE_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_STRTAB_BASE_CFG_ADDR(x),m,v,HWIO_S_STRTAB_BASE_CFG_IN(x))
#define HWIO_S_STRTAB_BASE_CFG_FMT_BMSK                                    0x30000
#define HWIO_S_STRTAB_BASE_CFG_FMT_SHFT                                       0x10
#define HWIO_S_STRTAB_BASE_CFG_SPLIT_BMSK                                    0x7c0
#define HWIO_S_STRTAB_BASE_CFG_SPLIT_SHFT                                      0x6
#define HWIO_S_STRTAB_BASE_CFG_LOG2SIZE_BMSK                                  0x3f
#define HWIO_S_STRTAB_BASE_CFG_LOG2SIZE_SHFT                                   0x0

#define HWIO_S_CMDQ_BASE_L_ADDR(x)                                      ((x) + 0x00008090)
#define HWIO_S_CMDQ_BASE_L_PHYS(x)                                      ((x) + 0x00008090)
#define HWIO_S_CMDQ_BASE_L_RMSK                                         0xffffffff
#define HWIO_S_CMDQ_BASE_L_POR                                          0x00000000
#define HWIO_S_CMDQ_BASE_L_POR_RMSK                                     0xffffffff
#define HWIO_S_CMDQ_BASE_L_ATTR                                                0x3
#define HWIO_S_CMDQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_S_CMDQ_BASE_L_ADDR(x), HWIO_S_CMDQ_BASE_L_RMSK)
#define HWIO_S_CMDQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_S_CMDQ_BASE_L_ADDR(x), m)
#define HWIO_S_CMDQ_BASE_L_OUT(x, v)      \
        out_dword(HWIO_S_CMDQ_BASE_L_ADDR(x),v)
#define HWIO_S_CMDQ_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_CMDQ_BASE_L_ADDR(x),m,v,HWIO_S_CMDQ_BASE_L_IN(x))
#define HWIO_S_CMDQ_BASE_L_ADDR_31_5_BMSK                               0xffffffe0
#define HWIO_S_CMDQ_BASE_L_ADDR_31_5_SHFT                                      0x5
#define HWIO_S_CMDQ_BASE_L_LOG2SIZE_BMSK                                      0x1f
#define HWIO_S_CMDQ_BASE_L_LOG2SIZE_SHFT                                       0x0

#define HWIO_S_CMDQ_BASE_H_ADDR(x)                                      ((x) + 0x00008094)
#define HWIO_S_CMDQ_BASE_H_PHYS(x)                                      ((x) + 0x00008094)
#define HWIO_S_CMDQ_BASE_H_RMSK                                         0x4000ffff
#define HWIO_S_CMDQ_BASE_H_POR                                          0x00000000
#define HWIO_S_CMDQ_BASE_H_POR_RMSK                                     0xffffffff
#define HWIO_S_CMDQ_BASE_H_ATTR                                                0x3
#define HWIO_S_CMDQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_S_CMDQ_BASE_H_ADDR(x), HWIO_S_CMDQ_BASE_H_RMSK)
#define HWIO_S_CMDQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_S_CMDQ_BASE_H_ADDR(x), m)
#define HWIO_S_CMDQ_BASE_H_OUT(x, v)      \
        out_dword(HWIO_S_CMDQ_BASE_H_ADDR(x),v)
#define HWIO_S_CMDQ_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_CMDQ_BASE_H_ADDR(x),m,v,HWIO_S_CMDQ_BASE_H_IN(x))
#define HWIO_S_CMDQ_BASE_H_RA_BMSK                                      0x40000000
#define HWIO_S_CMDQ_BASE_H_RA_SHFT                                            0x1e
#define HWIO_S_CMDQ_BASE_H_ADDR_47_32_BMSK                                  0xffff
#define HWIO_S_CMDQ_BASE_H_ADDR_47_32_SHFT                                     0x0

#define HWIO_S_CMDQ_PROD_ADDR(x)                                        ((x) + 0x00008098)
#define HWIO_S_CMDQ_PROD_PHYS(x)                                        ((x) + 0x00008098)
#define HWIO_S_CMDQ_PROD_RMSK                                              0xfffff
#define HWIO_S_CMDQ_PROD_POR                                            0x00000000
#define HWIO_S_CMDQ_PROD_POR_RMSK                                       0xffffffff
#define HWIO_S_CMDQ_PROD_ATTR                                                  0x3
#define HWIO_S_CMDQ_PROD_IN(x)      \
        in_dword_masked(HWIO_S_CMDQ_PROD_ADDR(x), HWIO_S_CMDQ_PROD_RMSK)
#define HWIO_S_CMDQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_S_CMDQ_PROD_ADDR(x), m)
#define HWIO_S_CMDQ_PROD_OUT(x, v)      \
        out_dword(HWIO_S_CMDQ_PROD_ADDR(x),v)
#define HWIO_S_CMDQ_PROD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_CMDQ_PROD_ADDR(x),m,v,HWIO_S_CMDQ_PROD_IN(x))
#define HWIO_S_CMDQ_PROD_WR_INDEX_AND_WRAP_BMSK                            0xfffff
#define HWIO_S_CMDQ_PROD_WR_INDEX_AND_WRAP_SHFT                                0x0

#define HWIO_S_CMDQ_CONS_ADDR(x)                                        ((x) + 0x0000809c)
#define HWIO_S_CMDQ_CONS_PHYS(x)                                        ((x) + 0x0000809c)
#define HWIO_S_CMDQ_CONS_RMSK                                           0x7f0fffff
#define HWIO_S_CMDQ_CONS_POR                                            0x00000000
#define HWIO_S_CMDQ_CONS_POR_RMSK                                       0xffffffff
#define HWIO_S_CMDQ_CONS_ATTR                                                  0x3
#define HWIO_S_CMDQ_CONS_IN(x)      \
        in_dword_masked(HWIO_S_CMDQ_CONS_ADDR(x), HWIO_S_CMDQ_CONS_RMSK)
#define HWIO_S_CMDQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_S_CMDQ_CONS_ADDR(x), m)
#define HWIO_S_CMDQ_CONS_OUT(x, v)      \
        out_dword(HWIO_S_CMDQ_CONS_ADDR(x),v)
#define HWIO_S_CMDQ_CONS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_CMDQ_CONS_ADDR(x),m,v,HWIO_S_CMDQ_CONS_IN(x))
#define HWIO_S_CMDQ_CONS_ERR_BMSK                                       0x7f000000
#define HWIO_S_CMDQ_CONS_ERR_SHFT                                             0x18
#define HWIO_S_CMDQ_CONS_RD_INDEX_AND_WRAP_BMSK                            0xfffff
#define HWIO_S_CMDQ_CONS_RD_INDEX_AND_WRAP_SHFT                                0x0

#define HWIO_S_EVENTQ_BASE_L_ADDR(x)                                    ((x) + 0x000080a0)
#define HWIO_S_EVENTQ_BASE_L_PHYS(x)                                    ((x) + 0x000080a0)
#define HWIO_S_EVENTQ_BASE_L_RMSK                                       0xffffffff
#define HWIO_S_EVENTQ_BASE_L_POR                                        0x00000000
#define HWIO_S_EVENTQ_BASE_L_POR_RMSK                                   0xffffffff
#define HWIO_S_EVENTQ_BASE_L_ATTR                                              0x3
#define HWIO_S_EVENTQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_S_EVENTQ_BASE_L_ADDR(x), HWIO_S_EVENTQ_BASE_L_RMSK)
#define HWIO_S_EVENTQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_S_EVENTQ_BASE_L_ADDR(x), m)
#define HWIO_S_EVENTQ_BASE_L_OUT(x, v)      \
        out_dword(HWIO_S_EVENTQ_BASE_L_ADDR(x),v)
#define HWIO_S_EVENTQ_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_EVENTQ_BASE_L_ADDR(x),m,v,HWIO_S_EVENTQ_BASE_L_IN(x))
#define HWIO_S_EVENTQ_BASE_L_ADDR_31_5_BMSK                             0xffffffe0
#define HWIO_S_EVENTQ_BASE_L_ADDR_31_5_SHFT                                    0x5
#define HWIO_S_EVENTQ_BASE_L_LOG2SIZE_BMSK                                    0x1f
#define HWIO_S_EVENTQ_BASE_L_LOG2SIZE_SHFT                                     0x0

#define HWIO_S_EVENTQ_BASE_H_ADDR(x)                                    ((x) + 0x000080a4)
#define HWIO_S_EVENTQ_BASE_H_PHYS(x)                                    ((x) + 0x000080a4)
#define HWIO_S_EVENTQ_BASE_H_RMSK                                       0x4000ffff
#define HWIO_S_EVENTQ_BASE_H_POR                                        0x00000000
#define HWIO_S_EVENTQ_BASE_H_POR_RMSK                                   0xffffffff
#define HWIO_S_EVENTQ_BASE_H_ATTR                                              0x3
#define HWIO_S_EVENTQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_S_EVENTQ_BASE_H_ADDR(x), HWIO_S_EVENTQ_BASE_H_RMSK)
#define HWIO_S_EVENTQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_S_EVENTQ_BASE_H_ADDR(x), m)
#define HWIO_S_EVENTQ_BASE_H_OUT(x, v)      \
        out_dword(HWIO_S_EVENTQ_BASE_H_ADDR(x),v)
#define HWIO_S_EVENTQ_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_EVENTQ_BASE_H_ADDR(x),m,v,HWIO_S_EVENTQ_BASE_H_IN(x))
#define HWIO_S_EVENTQ_BASE_H_WA_BMSK                                    0x40000000
#define HWIO_S_EVENTQ_BASE_H_WA_SHFT                                          0x1e
#define HWIO_S_EVENTQ_BASE_H_ADDR_47_32_BMSK                                0xffff
#define HWIO_S_EVENTQ_BASE_H_ADDR_47_32_SHFT                                   0x0

#define HWIO_S_EVENTQ_PROD_ADDR(x)                                      ((x) + 0x000080a8)
#define HWIO_S_EVENTQ_PROD_PHYS(x)                                      ((x) + 0x000080a8)
#define HWIO_S_EVENTQ_PROD_RMSK                                         0x800fffff
#define HWIO_S_EVENTQ_PROD_POR                                          0x00000000
#define HWIO_S_EVENTQ_PROD_POR_RMSK                                     0xffffffff
#define HWIO_S_EVENTQ_PROD_ATTR                                                0x3
#define HWIO_S_EVENTQ_PROD_IN(x)      \
        in_dword_masked(HWIO_S_EVENTQ_PROD_ADDR(x), HWIO_S_EVENTQ_PROD_RMSK)
#define HWIO_S_EVENTQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_S_EVENTQ_PROD_ADDR(x), m)
#define HWIO_S_EVENTQ_PROD_OUT(x, v)      \
        out_dword(HWIO_S_EVENTQ_PROD_ADDR(x),v)
#define HWIO_S_EVENTQ_PROD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_EVENTQ_PROD_ADDR(x),m,v,HWIO_S_EVENTQ_PROD_IN(x))
#define HWIO_S_EVENTQ_PROD_OVFLG_BMSK                                   0x80000000
#define HWIO_S_EVENTQ_PROD_OVFLG_SHFT                                         0x1f
#define HWIO_S_EVENTQ_PROD_WR_INDEX_AND_WRAP_BMSK                          0xfffff
#define HWIO_S_EVENTQ_PROD_WR_INDEX_AND_WRAP_SHFT                              0x0

#define HWIO_S_EVENTQ_CONS_ADDR(x)                                      ((x) + 0x000080ac)
#define HWIO_S_EVENTQ_CONS_PHYS(x)                                      ((x) + 0x000080ac)
#define HWIO_S_EVENTQ_CONS_RMSK                                         0x800fffff
#define HWIO_S_EVENTQ_CONS_POR                                          0x00000000
#define HWIO_S_EVENTQ_CONS_POR_RMSK                                     0xffffffff
#define HWIO_S_EVENTQ_CONS_ATTR                                                0x3
#define HWIO_S_EVENTQ_CONS_IN(x)      \
        in_dword_masked(HWIO_S_EVENTQ_CONS_ADDR(x), HWIO_S_EVENTQ_CONS_RMSK)
#define HWIO_S_EVENTQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_S_EVENTQ_CONS_ADDR(x), m)
#define HWIO_S_EVENTQ_CONS_OUT(x, v)      \
        out_dword(HWIO_S_EVENTQ_CONS_ADDR(x),v)
#define HWIO_S_EVENTQ_CONS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_EVENTQ_CONS_ADDR(x),m,v,HWIO_S_EVENTQ_CONS_IN(x))
#define HWIO_S_EVENTQ_CONS_OVACKFLG_BMSK                                0x80000000
#define HWIO_S_EVENTQ_CONS_OVACKFLG_SHFT                                      0x1f
#define HWIO_S_EVENTQ_CONS_RD_INDEX_AND_WRAP_BMSK                          0xfffff
#define HWIO_S_EVENTQ_CONS_RD_INDEX_AND_WRAP_SHFT                              0x0

#define HWIO_S_EVENTQ_IRQ_CFG0_L_ADDR(x)                                ((x) + 0x000080b0)
#define HWIO_S_EVENTQ_IRQ_CFG0_L_PHYS(x)                                ((x) + 0x000080b0)
#define HWIO_S_EVENTQ_IRQ_CFG0_L_RMSK                                   0xfffffffc
#define HWIO_S_EVENTQ_IRQ_CFG0_L_POR                                    0x00000000
#define HWIO_S_EVENTQ_IRQ_CFG0_L_POR_RMSK                               0xffffffff
#define HWIO_S_EVENTQ_IRQ_CFG0_L_ATTR                                          0x3
#define HWIO_S_EVENTQ_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_S_EVENTQ_IRQ_CFG0_L_ADDR(x), HWIO_S_EVENTQ_IRQ_CFG0_L_RMSK)
#define HWIO_S_EVENTQ_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_S_EVENTQ_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_S_EVENTQ_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_S_EVENTQ_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_S_EVENTQ_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_EVENTQ_IRQ_CFG0_L_ADDR(x),m,v,HWIO_S_EVENTQ_IRQ_CFG0_L_IN(x))
#define HWIO_S_EVENTQ_IRQ_CFG0_L_ADDR_31_2_BMSK                         0xfffffffc
#define HWIO_S_EVENTQ_IRQ_CFG0_L_ADDR_31_2_SHFT                                0x2

#define HWIO_S_EVENTQ_IRQ_CFG0_H_ADDR(x)                                ((x) + 0x000080b4)
#define HWIO_S_EVENTQ_IRQ_CFG0_H_PHYS(x)                                ((x) + 0x000080b4)
#define HWIO_S_EVENTQ_IRQ_CFG0_H_RMSK                                       0xffff
#define HWIO_S_EVENTQ_IRQ_CFG0_H_POR                                    0x00000000
#define HWIO_S_EVENTQ_IRQ_CFG0_H_POR_RMSK                               0xffffffff
#define HWIO_S_EVENTQ_IRQ_CFG0_H_ATTR                                          0x3
#define HWIO_S_EVENTQ_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_S_EVENTQ_IRQ_CFG0_H_ADDR(x), HWIO_S_EVENTQ_IRQ_CFG0_H_RMSK)
#define HWIO_S_EVENTQ_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_S_EVENTQ_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_S_EVENTQ_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_S_EVENTQ_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_S_EVENTQ_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_EVENTQ_IRQ_CFG0_H_ADDR(x),m,v,HWIO_S_EVENTQ_IRQ_CFG0_H_IN(x))
#define HWIO_S_EVENTQ_IRQ_CFG0_H_ADDR_47_32_BMSK                            0xffff
#define HWIO_S_EVENTQ_IRQ_CFG0_H_ADDR_47_32_SHFT                               0x0

#define HWIO_S_EVENTQ_IRQ_CFG1_ADDR(x)                                  ((x) + 0x000080b8)
#define HWIO_S_EVENTQ_IRQ_CFG1_PHYS(x)                                  ((x) + 0x000080b8)
#define HWIO_S_EVENTQ_IRQ_CFG1_RMSK                                     0xffffffff
#define HWIO_S_EVENTQ_IRQ_CFG1_POR                                      0x00000000
#define HWIO_S_EVENTQ_IRQ_CFG1_POR_RMSK                                 0xffffffff
#define HWIO_S_EVENTQ_IRQ_CFG1_ATTR                                            0x3
#define HWIO_S_EVENTQ_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_S_EVENTQ_IRQ_CFG1_ADDR(x), HWIO_S_EVENTQ_IRQ_CFG1_RMSK)
#define HWIO_S_EVENTQ_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_S_EVENTQ_IRQ_CFG1_ADDR(x), m)
#define HWIO_S_EVENTQ_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_S_EVENTQ_IRQ_CFG1_ADDR(x),v)
#define HWIO_S_EVENTQ_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_EVENTQ_IRQ_CFG1_ADDR(x),m,v,HWIO_S_EVENTQ_IRQ_CFG1_IN(x))
#define HWIO_S_EVENTQ_IRQ_CFG1_DATA_BMSK                                0xffffffff
#define HWIO_S_EVENTQ_IRQ_CFG1_DATA_SHFT                                       0x0

#define HWIO_S_EVENTQ_IRQ_CFG2_ADDR(x)                                  ((x) + 0x000080bc)
#define HWIO_S_EVENTQ_IRQ_CFG2_PHYS(x)                                  ((x) + 0x000080bc)
#define HWIO_S_EVENTQ_IRQ_CFG2_RMSK                                           0x3f
#define HWIO_S_EVENTQ_IRQ_CFG2_POR                                      0x00000000
#define HWIO_S_EVENTQ_IRQ_CFG2_POR_RMSK                                 0xffffffff
#define HWIO_S_EVENTQ_IRQ_CFG2_ATTR                                            0x3
#define HWIO_S_EVENTQ_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_S_EVENTQ_IRQ_CFG2_ADDR(x), HWIO_S_EVENTQ_IRQ_CFG2_RMSK)
#define HWIO_S_EVENTQ_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_S_EVENTQ_IRQ_CFG2_ADDR(x), m)
#define HWIO_S_EVENTQ_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_S_EVENTQ_IRQ_CFG2_ADDR(x),v)
#define HWIO_S_EVENTQ_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_EVENTQ_IRQ_CFG2_ADDR(x),m,v,HWIO_S_EVENTQ_IRQ_CFG2_IN(x))
#define HWIO_S_EVENTQ_IRQ_CFG2_SH_BMSK                                        0x30
#define HWIO_S_EVENTQ_IRQ_CFG2_SH_SHFT                                         0x4
#define HWIO_S_EVENTQ_IRQ_CFG2_MEMATTR_BMSK                                    0xf
#define HWIO_S_EVENTQ_IRQ_CFG2_MEMATTR_SHFT                                    0x0

#define HWIO_S_GATOS_CTRL_ADDR(x)                                       ((x) + 0x00008100)
#define HWIO_S_GATOS_CTRL_PHYS(x)                                       ((x) + 0x00008100)
#define HWIO_S_GATOS_CTRL_RMSK                                                 0x1
#define HWIO_S_GATOS_CTRL_POR                                           0x00000000
#define HWIO_S_GATOS_CTRL_POR_RMSK                                      0xffffffff
#define HWIO_S_GATOS_CTRL_ATTR                                                 0x3
#define HWIO_S_GATOS_CTRL_IN(x)      \
        in_dword_masked(HWIO_S_GATOS_CTRL_ADDR(x), HWIO_S_GATOS_CTRL_RMSK)
#define HWIO_S_GATOS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_S_GATOS_CTRL_ADDR(x), m)
#define HWIO_S_GATOS_CTRL_OUT(x, v)      \
        out_dword(HWIO_S_GATOS_CTRL_ADDR(x),v)
#define HWIO_S_GATOS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GATOS_CTRL_ADDR(x),m,v,HWIO_S_GATOS_CTRL_IN(x))
#define HWIO_S_GATOS_CTRL_RUN_BMSK                                             0x1
#define HWIO_S_GATOS_CTRL_RUN_SHFT                                             0x0

#define HWIO_S_GATOS_SID_L_ADDR(x)                                      ((x) + 0x00008108)
#define HWIO_S_GATOS_SID_L_PHYS(x)                                      ((x) + 0x00008108)
#define HWIO_S_GATOS_SID_L_RMSK                                             0xffff
#define HWIO_S_GATOS_SID_L_POR                                          0x00000000
#define HWIO_S_GATOS_SID_L_POR_RMSK                                     0xffffffff
#define HWIO_S_GATOS_SID_L_ATTR                                                0x3
#define HWIO_S_GATOS_SID_L_IN(x)      \
        in_dword_masked(HWIO_S_GATOS_SID_L_ADDR(x), HWIO_S_GATOS_SID_L_RMSK)
#define HWIO_S_GATOS_SID_L_INM(x, m)      \
        in_dword_masked(HWIO_S_GATOS_SID_L_ADDR(x), m)
#define HWIO_S_GATOS_SID_L_OUT(x, v)      \
        out_dword(HWIO_S_GATOS_SID_L_ADDR(x),v)
#define HWIO_S_GATOS_SID_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GATOS_SID_L_ADDR(x),m,v,HWIO_S_GATOS_SID_L_IN(x))
#define HWIO_S_GATOS_SID_L_STREAMID_BMSK                                    0xffff
#define HWIO_S_GATOS_SID_L_STREAMID_SHFT                                       0x0

#define HWIO_S_GATOS_SID_H_ADDR(x)                                      ((x) + 0x0000810c)
#define HWIO_S_GATOS_SID_H_PHYS(x)                                      ((x) + 0x0000810c)
#define HWIO_S_GATOS_SID_H_RMSK                                           0x3fffff
#define HWIO_S_GATOS_SID_H_POR                                          0x00000000
#define HWIO_S_GATOS_SID_H_POR_RMSK                                     0xffffffff
#define HWIO_S_GATOS_SID_H_ATTR                                                0x3
#define HWIO_S_GATOS_SID_H_IN(x)      \
        in_dword_masked(HWIO_S_GATOS_SID_H_ADDR(x), HWIO_S_GATOS_SID_H_RMSK)
#define HWIO_S_GATOS_SID_H_INM(x, m)      \
        in_dword_masked(HWIO_S_GATOS_SID_H_ADDR(x), m)
#define HWIO_S_GATOS_SID_H_OUT(x, v)      \
        out_dword(HWIO_S_GATOS_SID_H_ADDR(x),v)
#define HWIO_S_GATOS_SID_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GATOS_SID_H_ADDR(x),m,v,HWIO_S_GATOS_SID_H_IN(x))
#define HWIO_S_GATOS_SID_H_SSEC_BMSK                                      0x200000
#define HWIO_S_GATOS_SID_H_SSEC_SHFT                                          0x15
#define HWIO_S_GATOS_SID_H_SSID_VALID_BMSK                                0x100000
#define HWIO_S_GATOS_SID_H_SSID_VALID_SHFT                                    0x14
#define HWIO_S_GATOS_SID_H_SUBSTREAMID_BMSK                                0xfffff
#define HWIO_S_GATOS_SID_H_SUBSTREAMID_SHFT                                    0x0

#define HWIO_S_GATOS_ADDR_L_ADDR(x)                                     ((x) + 0x00008110)
#define HWIO_S_GATOS_ADDR_L_PHYS(x)                                     ((x) + 0x00008110)
#define HWIO_S_GATOS_ADDR_L_RMSK                                        0xffffffc0
#define HWIO_S_GATOS_ADDR_L_POR                                         0x00000000
#define HWIO_S_GATOS_ADDR_L_POR_RMSK                                    0xffffffff
#define HWIO_S_GATOS_ADDR_L_ATTR                                               0x3
#define HWIO_S_GATOS_ADDR_L_IN(x)      \
        in_dword_masked(HWIO_S_GATOS_ADDR_L_ADDR(x), HWIO_S_GATOS_ADDR_L_RMSK)
#define HWIO_S_GATOS_ADDR_L_INM(x, m)      \
        in_dword_masked(HWIO_S_GATOS_ADDR_L_ADDR(x), m)
#define HWIO_S_GATOS_ADDR_L_OUT(x, v)      \
        out_dword(HWIO_S_GATOS_ADDR_L_ADDR(x),v)
#define HWIO_S_GATOS_ADDR_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GATOS_ADDR_L_ADDR(x),m,v,HWIO_S_GATOS_ADDR_L_IN(x))
#define HWIO_S_GATOS_ADDR_L_ADDR_31_12_BMSK                             0xfffff000
#define HWIO_S_GATOS_ADDR_L_ADDR_31_12_SHFT                                    0xc
#define HWIO_S_GATOS_ADDR_L_TYPE_BMSK                                        0xc00
#define HWIO_S_GATOS_ADDR_L_TYPE_SHFT                                          0xa
#define HWIO_S_GATOS_ADDR_L_PNU_BMSK                                         0x200
#define HWIO_S_GATOS_ADDR_L_PNU_SHFT                                           0x9
#define HWIO_S_GATOS_ADDR_L_RNW_BMSK                                         0x100
#define HWIO_S_GATOS_ADDR_L_RNW_SHFT                                           0x8
#define HWIO_S_GATOS_ADDR_L_IND_BMSK                                          0x80
#define HWIO_S_GATOS_ADDR_L_IND_SHFT                                           0x7
#define HWIO_S_GATOS_ADDR_L_HTTUI_BMSK                                        0x40
#define HWIO_S_GATOS_ADDR_L_HTTUI_SHFT                                         0x6

#define HWIO_S_GATOS_ADDR_H_ADDR(x)                                     ((x) + 0x00008114)
#define HWIO_S_GATOS_ADDR_H_PHYS(x)                                     ((x) + 0x00008114)
#define HWIO_S_GATOS_ADDR_H_RMSK                                        0xffffffff
#define HWIO_S_GATOS_ADDR_H_POR                                         0x00000000
#define HWIO_S_GATOS_ADDR_H_POR_RMSK                                    0xffffffff
#define HWIO_S_GATOS_ADDR_H_ATTR                                               0x3
#define HWIO_S_GATOS_ADDR_H_IN(x)      \
        in_dword_masked(HWIO_S_GATOS_ADDR_H_ADDR(x), HWIO_S_GATOS_ADDR_H_RMSK)
#define HWIO_S_GATOS_ADDR_H_INM(x, m)      \
        in_dword_masked(HWIO_S_GATOS_ADDR_H_ADDR(x), m)
#define HWIO_S_GATOS_ADDR_H_OUT(x, v)      \
        out_dword(HWIO_S_GATOS_ADDR_H_ADDR(x),v)
#define HWIO_S_GATOS_ADDR_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_GATOS_ADDR_H_ADDR(x),m,v,HWIO_S_GATOS_ADDR_H_IN(x))
#define HWIO_S_GATOS_ADDR_H_ADDR_63_32_BMSK                             0xffffffff
#define HWIO_S_GATOS_ADDR_H_ADDR_63_32_SHFT                                    0x0

#define HWIO_S_GATOS_PAR_L_ADDR(x)                                      ((x) + 0x00008118)
#define HWIO_S_GATOS_PAR_L_PHYS(x)                                      ((x) + 0x00008118)
#define HWIO_S_GATOS_PAR_L_RMSK                                         0xffffffff
#define HWIO_S_GATOS_PAR_L_POR                                          0x00000000
#define HWIO_S_GATOS_PAR_L_POR_RMSK                                     0xffffffff
#define HWIO_S_GATOS_PAR_L_ATTR                                                0x1
#define HWIO_S_GATOS_PAR_L_IN(x)      \
        in_dword_masked(HWIO_S_GATOS_PAR_L_ADDR(x), HWIO_S_GATOS_PAR_L_RMSK)
#define HWIO_S_GATOS_PAR_L_INM(x, m)      \
        in_dword_masked(HWIO_S_GATOS_PAR_L_ADDR(x), m)
#define HWIO_S_GATOS_PAR_L_ADDR_BMSK                                    0xfffff000
#define HWIO_S_GATOS_PAR_L_ADDR_SHFT                                           0xc
#define HWIO_S_GATOS_PAR_L_FIELD_BMSK                                        0xffe
#define HWIO_S_GATOS_PAR_L_FIELD_SHFT                                          0x1
#define HWIO_S_GATOS_PAR_L_FAULT_BMSK                                          0x1
#define HWIO_S_GATOS_PAR_L_FAULT_SHFT                                          0x0

#define HWIO_S_GATOS_PAR_H_ADDR(x)                                      ((x) + 0x0000811c)
#define HWIO_S_GATOS_PAR_H_PHYS(x)                                      ((x) + 0x0000811c)
#define HWIO_S_GATOS_PAR_H_RMSK                                         0xff00ffff
#define HWIO_S_GATOS_PAR_H_POR                                          0x00000000
#define HWIO_S_GATOS_PAR_H_POR_RMSK                                     0xffffffff
#define HWIO_S_GATOS_PAR_H_ATTR                                                0x1
#define HWIO_S_GATOS_PAR_H_IN(x)      \
        in_dword_masked(HWIO_S_GATOS_PAR_H_ADDR(x), HWIO_S_GATOS_PAR_H_RMSK)
#define HWIO_S_GATOS_PAR_H_INM(x, m)      \
        in_dword_masked(HWIO_S_GATOS_PAR_H_ADDR(x), m)
#define HWIO_S_GATOS_PAR_H_MEMATTR_BMSK                                 0xff000000
#define HWIO_S_GATOS_PAR_H_MEMATTR_SHFT                                       0x18
#define HWIO_S_GATOS_PAR_H_ADDR_BMSK                                        0xffff
#define HWIO_S_GATOS_PAR_H_ADDR_SHFT                                           0x0

#define HWIO_S_QCR0_ADDR(x)                                             ((x) + 0x00009000)
#define HWIO_S_QCR0_PHYS(x)                                             ((x) + 0x00009000)
#define HWIO_S_QCR0_RMSK                                                      0x1e
#define HWIO_S_QCR0_POR                                                 0x00000012
#define HWIO_S_QCR0_POR_RMSK                                            0xffffffff
#define HWIO_S_QCR0_ATTR                                                       0x3
#define HWIO_S_QCR0_IN(x)      \
        in_dword_masked(HWIO_S_QCR0_ADDR(x), HWIO_S_QCR0_RMSK)
#define HWIO_S_QCR0_INM(x, m)      \
        in_dword_masked(HWIO_S_QCR0_ADDR(x), m)
#define HWIO_S_QCR0_OUT(x, v)      \
        out_dword(HWIO_S_QCR0_ADDR(x),v)
#define HWIO_S_QCR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QCR0_ADDR(x),m,v,HWIO_S_QCR0_IN(x))
#define HWIO_S_QCR0_CMDQ_SYNC_RESP_TRK_DIS_BMSK                               0x10
#define HWIO_S_QCR0_CMDQ_SYNC_RESP_TRK_DIS_SHFT                                0x4
#define HWIO_S_QCR0_STALL_ON_CMDQ_SYNC_BMSK                                    0x8
#define HWIO_S_QCR0_STALL_ON_CMDQ_SYNC_SHFT                                    0x3
#define HWIO_S_QCR0_NSCFGEE_BMSK                                               0x4
#define HWIO_S_QCR0_NSCFGEE_SHFT                                               0x2
#define HWIO_S_QCR0_AHB_ERROR_REPORT_EN_BMSK                                   0x2
#define HWIO_S_QCR0_AHB_ERROR_REPORT_EN_SHFT                                   0x1

#define HWIO_S_QTABLE_ACR1_ADDR(x)                                      ((x) + 0x00009020)
#define HWIO_S_QTABLE_ACR1_PHYS(x)                                      ((x) + 0x00009020)
#define HWIO_S_QTABLE_ACR1_RMSK                                                0x7
#define HWIO_S_QTABLE_ACR1_POR                                          0x00000000
#define HWIO_S_QTABLE_ACR1_POR_RMSK                                     0xffffffff
#define HWIO_S_QTABLE_ACR1_ATTR                                                0x3
#define HWIO_S_QTABLE_ACR1_IN(x)      \
        in_dword_masked(HWIO_S_QTABLE_ACR1_ADDR(x), HWIO_S_QTABLE_ACR1_RMSK)
#define HWIO_S_QTABLE_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_S_QTABLE_ACR1_ADDR(x), m)
#define HWIO_S_QTABLE_ACR1_OUT(x, v)      \
        out_dword(HWIO_S_QTABLE_ACR1_ADDR(x),v)
#define HWIO_S_QTABLE_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QTABLE_ACR1_ADDR(x),m,v,HWIO_S_QTABLE_ACR1_IN(x))
#define HWIO_S_QTABLE_ACR1_TRCFG_BMSK                                          0x4
#define HWIO_S_QTABLE_ACR1_TRCFG_SHFT                                          0x2
#define HWIO_S_QTABLE_ACR1_REQPRIORITY_BMSK                                    0x3
#define HWIO_S_QTABLE_ACR1_REQPRIORITY_SHFT                                    0x0

#define HWIO_S_QQUEUE_ACR1_ADDR(x)                                      ((x) + 0x00009024)
#define HWIO_S_QQUEUE_ACR1_PHYS(x)                                      ((x) + 0x00009024)
#define HWIO_S_QQUEUE_ACR1_RMSK                                                0x7
#define HWIO_S_QQUEUE_ACR1_POR                                          0x00000000
#define HWIO_S_QQUEUE_ACR1_POR_RMSK                                     0xffffffff
#define HWIO_S_QQUEUE_ACR1_ATTR                                                0x3
#define HWIO_S_QQUEUE_ACR1_IN(x)      \
        in_dword_masked(HWIO_S_QQUEUE_ACR1_ADDR(x), HWIO_S_QQUEUE_ACR1_RMSK)
#define HWIO_S_QQUEUE_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_S_QQUEUE_ACR1_ADDR(x), m)
#define HWIO_S_QQUEUE_ACR1_OUT(x, v)      \
        out_dword(HWIO_S_QQUEUE_ACR1_ADDR(x),v)
#define HWIO_S_QQUEUE_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QQUEUE_ACR1_ADDR(x),m,v,HWIO_S_QQUEUE_ACR1_IN(x))
#define HWIO_S_QQUEUE_ACR1_TRCFG_BMSK                                          0x4
#define HWIO_S_QQUEUE_ACR1_TRCFG_SHFT                                          0x2
#define HWIO_S_QQUEUE_ACR1_REQPRIORITY_BMSK                                    0x3
#define HWIO_S_QQUEUE_ACR1_REQPRIORITY_SHFT                                    0x0

#define HWIO_S_QGERROR_MSI_ACR1_ADDR(x)                                 ((x) + 0x00009028)
#define HWIO_S_QGERROR_MSI_ACR1_PHYS(x)                                 ((x) + 0x00009028)
#define HWIO_S_QGERROR_MSI_ACR1_RMSK                                           0xf
#define HWIO_S_QGERROR_MSI_ACR1_POR                                     0x00000000
#define HWIO_S_QGERROR_MSI_ACR1_POR_RMSK                                0xffffffff
#define HWIO_S_QGERROR_MSI_ACR1_ATTR                                           0x3
#define HWIO_S_QGERROR_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_S_QGERROR_MSI_ACR1_ADDR(x), HWIO_S_QGERROR_MSI_ACR1_RMSK)
#define HWIO_S_QGERROR_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_S_QGERROR_MSI_ACR1_ADDR(x), m)
#define HWIO_S_QGERROR_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_S_QGERROR_MSI_ACR1_ADDR(x),v)
#define HWIO_S_QGERROR_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QGERROR_MSI_ACR1_ADDR(x),m,v,HWIO_S_QGERROR_MSI_ACR1_IN(x))
#define HWIO_S_QGERROR_MSI_ACR1_WA_BMSK                                        0x8
#define HWIO_S_QGERROR_MSI_ACR1_WA_SHFT                                        0x3
#define HWIO_S_QGERROR_MSI_ACR1_TRCFG_BMSK                                     0x4
#define HWIO_S_QGERROR_MSI_ACR1_TRCFG_SHFT                                     0x2
#define HWIO_S_QGERROR_MSI_ACR1_REQPRIORITY_BMSK                               0x3
#define HWIO_S_QGERROR_MSI_ACR1_REQPRIORITY_SHFT                               0x0

#define HWIO_S_QCMDQ_MSI_ACR1_ADDR(x)                                   ((x) + 0x0000902c)
#define HWIO_S_QCMDQ_MSI_ACR1_PHYS(x)                                   ((x) + 0x0000902c)
#define HWIO_S_QCMDQ_MSI_ACR1_RMSK                                             0xf
#define HWIO_S_QCMDQ_MSI_ACR1_POR                                       0x00000000
#define HWIO_S_QCMDQ_MSI_ACR1_POR_RMSK                                  0xffffffff
#define HWIO_S_QCMDQ_MSI_ACR1_ATTR                                             0x3
#define HWIO_S_QCMDQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_S_QCMDQ_MSI_ACR1_ADDR(x), HWIO_S_QCMDQ_MSI_ACR1_RMSK)
#define HWIO_S_QCMDQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_S_QCMDQ_MSI_ACR1_ADDR(x), m)
#define HWIO_S_QCMDQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_S_QCMDQ_MSI_ACR1_ADDR(x),v)
#define HWIO_S_QCMDQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QCMDQ_MSI_ACR1_ADDR(x),m,v,HWIO_S_QCMDQ_MSI_ACR1_IN(x))
#define HWIO_S_QCMDQ_MSI_ACR1_WA_BMSK                                          0x8
#define HWIO_S_QCMDQ_MSI_ACR1_WA_SHFT                                          0x3
#define HWIO_S_QCMDQ_MSI_ACR1_TRCFG_BMSK                                       0x4
#define HWIO_S_QCMDQ_MSI_ACR1_TRCFG_SHFT                                       0x2
#define HWIO_S_QCMDQ_MSI_ACR1_REQPRIORITY_BMSK                                 0x3
#define HWIO_S_QCMDQ_MSI_ACR1_REQPRIORITY_SHFT                                 0x0

#define HWIO_S_QEVENTQ_MSI_ACR1_ADDR(x)                                 ((x) + 0x00009030)
#define HWIO_S_QEVENTQ_MSI_ACR1_PHYS(x)                                 ((x) + 0x00009030)
#define HWIO_S_QEVENTQ_MSI_ACR1_RMSK                                           0xf
#define HWIO_S_QEVENTQ_MSI_ACR1_POR                                     0x00000000
#define HWIO_S_QEVENTQ_MSI_ACR1_POR_RMSK                                0xffffffff
#define HWIO_S_QEVENTQ_MSI_ACR1_ATTR                                           0x3
#define HWIO_S_QEVENTQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_S_QEVENTQ_MSI_ACR1_ADDR(x), HWIO_S_QEVENTQ_MSI_ACR1_RMSK)
#define HWIO_S_QEVENTQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_S_QEVENTQ_MSI_ACR1_ADDR(x), m)
#define HWIO_S_QEVENTQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_S_QEVENTQ_MSI_ACR1_ADDR(x),v)
#define HWIO_S_QEVENTQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QEVENTQ_MSI_ACR1_ADDR(x),m,v,HWIO_S_QEVENTQ_MSI_ACR1_IN(x))
#define HWIO_S_QEVENTQ_MSI_ACR1_WA_BMSK                                        0x8
#define HWIO_S_QEVENTQ_MSI_ACR1_WA_SHFT                                        0x3
#define HWIO_S_QEVENTQ_MSI_ACR1_TRCFG_BMSK                                     0x4
#define HWIO_S_QEVENTQ_MSI_ACR1_TRCFG_SHFT                                     0x2
#define HWIO_S_QEVENTQ_MSI_ACR1_REQPRIORITY_BMSK                               0x3
#define HWIO_S_QEVENTQ_MSI_ACR1_REQPRIORITY_SHFT                               0x0

#define HWIO_S_QGERROR_ADDR(x)                                          ((x) + 0x0000903c)
#define HWIO_S_QGERROR_PHYS(x)                                          ((x) + 0x0000903c)
#define HWIO_S_QGERROR_RMSK                                             0xfffff803
#define HWIO_S_QGERROR_POR                                              0x00000000
#define HWIO_S_QGERROR_POR_RMSK                                         0xffffffff
#define HWIO_S_QGERROR_ATTR                                                    0x1
#define HWIO_S_QGERROR_IN(x)      \
        in_dword_masked(HWIO_S_QGERROR_ADDR(x), HWIO_S_QGERROR_RMSK)
#define HWIO_S_QGERROR_INM(x, m)      \
        in_dword_masked(HWIO_S_QGERROR_ADDR(x), m)
#define HWIO_S_QGERROR_SYNDROME_CFG_BMSK                                0xffffe000
#define HWIO_S_QGERROR_SYNDROME_CFG_SHFT                                       0xd
#define HWIO_S_QGERROR_SYNDROME_PMCG_BMSK                                   0x1800
#define HWIO_S_QGERROR_SYNDROME_PMCG_SHFT                                      0xb
#define HWIO_S_QGERROR_MSI_PMCG_ABT_ERR_BMSK                                   0x2
#define HWIO_S_QGERROR_MSI_PMCG_ABT_ERR_SHFT                                   0x1
#define HWIO_S_QGERROR_CFG_FAULT_BMSK                                          0x1
#define HWIO_S_QGERROR_CFG_FAULT_SHFT                                          0x0

#define HWIO_S_QGERROR_RST_ADDR(x)                                      ((x) + 0x00009040)
#define HWIO_S_QGERROR_RST_PHYS(x)                                      ((x) + 0x00009040)
#define HWIO_S_QGERROR_RST_RMSK                                                0x3
#define HWIO_S_QGERROR_RST_POR                                          0x00000000
#define HWIO_S_QGERROR_RST_POR_RMSK                                     0xffffffff
#define HWIO_S_QGERROR_RST_ATTR                                                0x2
#define HWIO_S_QGERROR_RST_OUT(x, v)      \
        out_dword(HWIO_S_QGERROR_RST_ADDR(x),v)
#define HWIO_S_QGERROR_RST_MSI_PMCG_ABT_ERR_BMSK                               0x2
#define HWIO_S_QGERROR_RST_MSI_PMCG_ABT_ERR_SHFT                               0x1
#define HWIO_S_QGERROR_RST_CFG_FAULT_BMSK                                      0x1
#define HWIO_S_QGERROR_RST_CFG_FAULT_SHFT                                      0x0

#define HWIO_S_QGITS_GBPA_ADDR(x)                                       ((x) + 0x00009050)
#define HWIO_S_QGITS_GBPA_PHYS(x)                                       ((x) + 0x00009050)
#define HWIO_S_QGITS_GBPA_RMSK                                          0x801f3f1f
#define HWIO_S_QGITS_GBPA_POR                                           0x00002010
#define HWIO_S_QGITS_GBPA_POR_RMSK                                      0xffffffff
#define HWIO_S_QGITS_GBPA_ATTR                                                 0x3
#define HWIO_S_QGITS_GBPA_IN(x)      \
        in_dword_masked(HWIO_S_QGITS_GBPA_ADDR(x), HWIO_S_QGITS_GBPA_RMSK)
#define HWIO_S_QGITS_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_S_QGITS_GBPA_ADDR(x), m)
#define HWIO_S_QGITS_GBPA_OUT(x, v)      \
        out_dword(HWIO_S_QGITS_GBPA_ADDR(x),v)
#define HWIO_S_QGITS_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QGITS_GBPA_ADDR(x),m,v,HWIO_S_QGITS_GBPA_IN(x))
#define HWIO_S_QGITS_GBPA_UPDATE_BMSK                                   0x80000000
#define HWIO_S_QGITS_GBPA_UPDATE_SHFT                                         0x1f
#define HWIO_S_QGITS_GBPA_ABORT_BMSK                                      0x100000
#define HWIO_S_QGITS_GBPA_ABORT_SHFT                                          0x14
#define HWIO_S_QGITS_GBPA_INSTCFG_BMSK                                     0xc0000
#define HWIO_S_QGITS_GBPA_INSTCFG_SHFT                                        0x12
#define HWIO_S_QGITS_GBPA_PRIVCFG_BMSK                                     0x30000
#define HWIO_S_QGITS_GBPA_PRIVCFG_SHFT                                        0x10
#define HWIO_S_QGITS_GBPA_SHCFG_BMSK                                        0x3000
#define HWIO_S_QGITS_GBPA_SHCFG_SHFT                                           0xc
#define HWIO_S_QGITS_GBPA_ALLOCCFG_BMSK                                      0xf00
#define HWIO_S_QGITS_GBPA_ALLOCCFG_SHFT                                        0x8
#define HWIO_S_QGITS_GBPA_MTCFG_BMSK                                          0x10
#define HWIO_S_QGITS_GBPA_MTCFG_SHFT                                           0x4
#define HWIO_S_QGITS_GBPA_MEMATTR_BMSK                                         0xf
#define HWIO_S_QGITS_GBPA_MEMATTR_SHFT                                         0x0

#define HWIO_S_QGITS_AGBPA_ADDR(x)                                      ((x) + 0x00009054)
#define HWIO_S_QGITS_AGBPA_PHYS(x)                                      ((x) + 0x00009054)
#define HWIO_S_QGITS_AGBPA_RMSK                                            0x7ffff
#define HWIO_S_QGITS_AGBPA_POR                                          0x00000000
#define HWIO_S_QGITS_AGBPA_POR_RMSK                                     0xffffffff
#define HWIO_S_QGITS_AGBPA_ATTR                                                0x3
#define HWIO_S_QGITS_AGBPA_IN(x)      \
        in_dword_masked(HWIO_S_QGITS_AGBPA_ADDR(x), HWIO_S_QGITS_AGBPA_RMSK)
#define HWIO_S_QGITS_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_S_QGITS_AGBPA_ADDR(x), m)
#define HWIO_S_QGITS_AGBPA_OUT(x, v)      \
        out_dword(HWIO_S_QGITS_AGBPA_ADDR(x),v)
#define HWIO_S_QGITS_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QGITS_AGBPA_ADDR(x),m,v,HWIO_S_QGITS_AGBPA_IN(x))
#define HWIO_S_QGITS_AGBPA_REQPRIORITY_BMSK                                0x60000
#define HWIO_S_QGITS_AGBPA_REQPRIORITY_SHFT                                   0x11
#define HWIO_S_QGITS_AGBPA_REQPRIORITY_REPLACE_BMSK                        0x10000
#define HWIO_S_QGITS_AGBPA_REQPRIORITY_REPLACE_SHFT                           0x10
#define HWIO_S_QGITS_AGBPA_BPVMID_BMSK                                      0xffff
#define HWIO_S_QGITS_AGBPA_BPVMID_SHFT                                         0x0

#define HWIO_S_QDEVICEID_ADDR(x)                                        ((x) + 0x00009058)
#define HWIO_S_QDEVICEID_PHYS(x)                                        ((x) + 0x00009058)
#define HWIO_S_QDEVICEID_RMSK                                           0xffffffff
#define HWIO_S_QDEVICEID_POR                                            0x00000000
#define HWIO_S_QDEVICEID_POR_RMSK                                       0xffffffff
#define HWIO_S_QDEVICEID_ATTR                                                  0x3
#define HWIO_S_QDEVICEID_IN(x)      \
        in_dword_masked(HWIO_S_QDEVICEID_ADDR(x), HWIO_S_QDEVICEID_RMSK)
#define HWIO_S_QDEVICEID_INM(x, m)      \
        in_dword_masked(HWIO_S_QDEVICEID_ADDR(x), m)
#define HWIO_S_QDEVICEID_OUT(x, v)      \
        out_dword(HWIO_S_QDEVICEID_ADDR(x),v)
#define HWIO_S_QDEVICEID_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_S_QDEVICEID_ADDR(x),m,v,HWIO_S_QDEVICEID_IN(x))
#define HWIO_S_QDEVICEID_DEVICEID_BMSK                                  0xffffffff
#define HWIO_S_QDEVICEID_DEVICEID_SHFT                                         0x0

#define HWIO_QAD0_IDR0_ADDR(x)                                          ((x) + 0x00000000)
#define HWIO_QAD0_IDR0_PHYS(x)                                          ((x) + 0x00000000)
#define HWIO_QAD0_IDR0_RMSK                                             0x1f7fffff
#define HWIO_QAD0_IDR0_POR                                              0x081cf6bf
#define HWIO_QAD0_IDR0_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_IDR0_ATTR                                                    0x1
#define HWIO_QAD0_IDR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_IDR0_ADDR(x), HWIO_QAD0_IDR0_RMSK)
#define HWIO_QAD0_IDR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IDR0_ADDR(x), m)
#define HWIO_QAD0_IDR0_ST_LEVEL_BMSK                                    0x18000000
#define HWIO_QAD0_IDR0_ST_LEVEL_SHFT                                          0x1b
#define HWIO_QAD0_IDR0_TERM_MODEL_BMSK                                   0x4000000
#define HWIO_QAD0_IDR0_TERM_MODEL_SHFT                                        0x1a
#define HWIO_QAD0_IDR0_STALL_MODEL_BMSK                                  0x3000000
#define HWIO_QAD0_IDR0_STALL_MODEL_SHFT                                       0x18
#define HWIO_QAD0_IDR0_TTENDIAN_BMSK                                      0x600000
#define HWIO_QAD0_IDR0_TTENDIAN_SHFT                                          0x15
#define HWIO_QAD0_IDR0_VATOS_BMSK                                         0x100000
#define HWIO_QAD0_IDR0_VATOS_SHFT                                             0x14
#define HWIO_QAD0_IDR0_CD2L_BMSK                                           0x80000
#define HWIO_QAD0_IDR0_CD2L_SHFT                                              0x13
#define HWIO_QAD0_IDR0_VMID16_BMSK                                         0x40000
#define HWIO_QAD0_IDR0_VMID16_SHFT                                            0x12
#define HWIO_QAD0_IDR0_VMW_BMSK                                            0x20000
#define HWIO_QAD0_IDR0_VMW_SHFT                                               0x11
#define HWIO_QAD0_IDR0_PRI_BMSK                                            0x10000
#define HWIO_QAD0_IDR0_PRI_SHFT                                               0x10
#define HWIO_QAD0_IDR0_ATOS_BMSK                                            0x8000
#define HWIO_QAD0_IDR0_ATOS_SHFT                                               0xf
#define HWIO_QAD0_IDR0_SEV_BMSK                                             0x4000
#define HWIO_QAD0_IDR0_SEV_SHFT                                                0xe
#define HWIO_QAD0_IDR0_MSI_BMSK                                             0x2000
#define HWIO_QAD0_IDR0_MSI_SHFT                                                0xd
#define HWIO_QAD0_IDR0_ASID16_BMSK                                          0x1000
#define HWIO_QAD0_IDR0_ASID16_SHFT                                             0xc
#define HWIO_QAD0_IDR0_NS1ATS_BMSK                                           0x800
#define HWIO_QAD0_IDR0_NS1ATS_SHFT                                             0xb
#define HWIO_QAD0_IDR0_ATS_BMSK                                              0x400
#define HWIO_QAD0_IDR0_ATS_SHFT                                                0xa
#define HWIO_QAD0_IDR0_HYP_BMSK                                              0x200
#define HWIO_QAD0_IDR0_HYP_SHFT                                                0x9
#define HWIO_QAD0_IDR0_DORMHINT_BMSK                                         0x100
#define HWIO_QAD0_IDR0_DORMHINT_SHFT                                           0x8
#define HWIO_QAD0_IDR0_HTTU_BMSK                                              0xc0
#define HWIO_QAD0_IDR0_HTTU_SHFT                                               0x6
#define HWIO_QAD0_IDR0_BTM_BMSK                                               0x20
#define HWIO_QAD0_IDR0_BTM_SHFT                                                0x5
#define HWIO_QAD0_IDR0_COHACC_BMSK                                            0x10
#define HWIO_QAD0_IDR0_COHACC_SHFT                                             0x4
#define HWIO_QAD0_IDR0_TTF_BMSK                                                0xc
#define HWIO_QAD0_IDR0_TTF_SHFT                                                0x2
#define HWIO_QAD0_IDR0_S1P_BMSK                                                0x2
#define HWIO_QAD0_IDR0_S1P_SHFT                                                0x1
#define HWIO_QAD0_IDR0_S2P_BMSK                                                0x1
#define HWIO_QAD0_IDR0_S2P_SHFT                                                0x0

#define HWIO_QAD0_IDR1_ADDR(x)                                          ((x) + 0x00000004)
#define HWIO_QAD0_IDR1_PHYS(x)                                          ((x) + 0x00000004)
#define HWIO_QAD0_IDR1_RMSK                                             0x7fffffff
#define HWIO_QAD0_IDR1_POR                                              0x0e730510
#define HWIO_QAD0_IDR1_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_IDR1_ATTR                                                    0x1
#define HWIO_QAD0_IDR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_IDR1_ADDR(x), HWIO_QAD0_IDR1_RMSK)
#define HWIO_QAD0_IDR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IDR1_ADDR(x), m)
#define HWIO_QAD0_IDR1_TABLES_PRESET_BMSK                               0x40000000
#define HWIO_QAD0_IDR1_TABLES_PRESET_SHFT                                     0x1e
#define HWIO_QAD0_IDR1_QUEUES_PRESET_BMSK                               0x20000000
#define HWIO_QAD0_IDR1_QUEUES_PRESET_SHFT                                     0x1d
#define HWIO_QAD0_IDR1_REL_BMSK                                         0x10000000
#define HWIO_QAD0_IDR1_REL_SHFT                                               0x1c
#define HWIO_QAD0_IDR1_ATTR_TYPES_OVR_BMSK                               0x8000000
#define HWIO_QAD0_IDR1_ATTR_TYPES_OVR_SHFT                                    0x1b
#define HWIO_QAD0_IDR1_ATTR_PERM_OVR_BMSK                                0x4000000
#define HWIO_QAD0_IDR1_ATTR_PERM_OVR_SHFT                                     0x1a
#define HWIO_QAD0_IDR1_CMDQS_BMSK                                        0x3e00000
#define HWIO_QAD0_IDR1_CMDQS_SHFT                                             0x15
#define HWIO_QAD0_IDR1_EVENTQS_BMSK                                       0x1f0000
#define HWIO_QAD0_IDR1_EVENTQS_SHFT                                           0x10
#define HWIO_QAD0_IDR1_PRIQS_BMSK                                           0xf800
#define HWIO_QAD0_IDR1_PRIQS_SHFT                                              0xb
#define HWIO_QAD0_IDR1_SSIDSIZE_BMSK                                         0x7c0
#define HWIO_QAD0_IDR1_SSIDSIZE_SHFT                                           0x6
#define HWIO_QAD0_IDR1_SIDSIZE_BMSK                                           0x3f
#define HWIO_QAD0_IDR1_SIDSIZE_SHFT                                            0x0

#define HWIO_QAD0_IDR2_ADDR(x)                                          ((x) + 0x00000008)
#define HWIO_QAD0_IDR2_PHYS(x)                                          ((x) + 0x00000008)
#define HWIO_QAD0_IDR2_RMSK                                                  0x3ff
#define HWIO_QAD0_IDR2_POR                                              0x00000001
#define HWIO_QAD0_IDR2_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_IDR2_ATTR                                                    0x1
#define HWIO_QAD0_IDR2_IN(x)      \
        in_dword_masked(HWIO_QAD0_IDR2_ADDR(x), HWIO_QAD0_IDR2_RMSK)
#define HWIO_QAD0_IDR2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IDR2_ADDR(x), m)
#define HWIO_QAD0_IDR2_BA_VATOS_BMSK                                         0x3ff
#define HWIO_QAD0_IDR2_BA_VATOS_SHFT                                           0x0

#define HWIO_QAD0_IDR3_ADDR(x)                                          ((x) + 0x0000000c)
#define HWIO_QAD0_IDR3_PHYS(x)                                          ((x) + 0x0000000c)
#define HWIO_QAD0_IDR3_RMSK                                                    0x4
#define HWIO_QAD0_IDR3_POR                                              0x00000000
#define HWIO_QAD0_IDR3_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_IDR3_ATTR                                                    0x1
#define HWIO_QAD0_IDR3_IN(x)      \
        in_dword_masked(HWIO_QAD0_IDR3_ADDR(x), HWIO_QAD0_IDR3_RMSK)
#define HWIO_QAD0_IDR3_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IDR3_ADDR(x), m)
#define HWIO_QAD0_IDR3_HAD_BMSK                                                0x4
#define HWIO_QAD0_IDR3_HAD_SHFT                                                0x2

#define HWIO_QAD0_IDR4_ADDR(x)                                          ((x) + 0x00000010)
#define HWIO_QAD0_IDR4_PHYS(x)                                          ((x) + 0x00000010)
#define HWIO_QAD0_IDR4_RMSK                                               0xff0007
#define HWIO_QAD0_IDR4_POR                                              0x00320002
#define HWIO_QAD0_IDR4_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_IDR4_ATTR                                                    0x1
#define HWIO_QAD0_IDR4_IN(x)      \
        in_dword_masked(HWIO_QAD0_IDR4_ADDR(x), HWIO_QAD0_IDR4_RMSK)
#define HWIO_QAD0_IDR4_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IDR4_ADDR(x), m)
#define HWIO_QAD0_IDR4_BA_PMCG_PG1_BMSK                                   0xf00000
#define HWIO_QAD0_IDR4_BA_PMCG_PG1_SHFT                                       0x14
#define HWIO_QAD0_IDR4_BA_PMCG_PG0_BMSK                                    0xf0000
#define HWIO_QAD0_IDR4_BA_PMCG_PG0_SHFT                                       0x10
#define HWIO_QAD0_IDR4_QACT_QAD_RST_VAL_BMSK                                   0x4
#define HWIO_QAD0_IDR4_QACT_QAD_RST_VAL_SHFT                                   0x2
#define HWIO_QAD0_IDR4_QACT_SSD_RST_VAL_BMSK                                   0x2
#define HWIO_QAD0_IDR4_QACT_SSD_RST_VAL_SHFT                                   0x1
#define HWIO_QAD0_IDR4_QACT_RST_EN_BMSK                                        0x1
#define HWIO_QAD0_IDR4_QACT_RST_EN_SHFT                                        0x0

#define HWIO_QAD0_IDR5_ADDR(x)                                          ((x) + 0x00000014)
#define HWIO_QAD0_IDR5_PHYS(x)                                          ((x) + 0x00000014)
#define HWIO_QAD0_IDR5_RMSK                                             0xffff0077
#define HWIO_QAD0_IDR5_POR                                              0x00080074
#define HWIO_QAD0_IDR5_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_IDR5_ATTR                                                    0x1
#define HWIO_QAD0_IDR5_IN(x)      \
        in_dword_masked(HWIO_QAD0_IDR5_ADDR(x), HWIO_QAD0_IDR5_RMSK)
#define HWIO_QAD0_IDR5_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IDR5_ADDR(x), m)
#define HWIO_QAD0_IDR5_STALL_MAX_BMSK                                   0xffff0000
#define HWIO_QAD0_IDR5_STALL_MAX_SHFT                                         0x10
#define HWIO_QAD0_IDR5_GRAN64K_BMSK                                           0x40
#define HWIO_QAD0_IDR5_GRAN64K_SHFT                                            0x6
#define HWIO_QAD0_IDR5_GRAN16K_BMSK                                           0x20
#define HWIO_QAD0_IDR5_GRAN16K_SHFT                                            0x5
#define HWIO_QAD0_IDR5_GRAN4K_BMSK                                            0x10
#define HWIO_QAD0_IDR5_GRAN4K_SHFT                                             0x4
#define HWIO_QAD0_IDR5_OAS_BMSK                                                0x7
#define HWIO_QAD0_IDR5_OAS_SHFT                                                0x0

#define HWIO_QAD0_IIDR_ADDR(x)                                          ((x) + 0x00000018)
#define HWIO_QAD0_IIDR_PHYS(x)                                          ((x) + 0x00000018)
#define HWIO_QAD0_IIDR_RMSK                                             0xffffffff
#define HWIO_QAD0_IIDR_POR                                              0x04020070
#define HWIO_QAD0_IIDR_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_IIDR_ATTR                                                    0x1
#define HWIO_QAD0_IIDR_IN(x)      \
        in_dword_masked(HWIO_QAD0_IIDR_ADDR(x), HWIO_QAD0_IIDR_RMSK)
#define HWIO_QAD0_IIDR_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IIDR_ADDR(x), m)
#define HWIO_QAD0_IIDR_PRODUCTID_BMSK                                   0xfff00000
#define HWIO_QAD0_IIDR_PRODUCTID_SHFT                                         0x14
#define HWIO_QAD0_IIDR_VARIANT_BMSK                                        0xf0000
#define HWIO_QAD0_IIDR_VARIANT_SHFT                                           0x10
#define HWIO_QAD0_IIDR_REVISION_BMSK                                        0xf000
#define HWIO_QAD0_IIDR_REVISION_SHFT                                           0xc
#define HWIO_QAD0_IIDR_IMPLEMENTER_BMSK                                      0xfff
#define HWIO_QAD0_IIDR_IMPLEMENTER_SHFT                                        0x0

#define HWIO_QAD0_AIDR_ADDR(x)                                          ((x) + 0x0000001c)
#define HWIO_QAD0_AIDR_PHYS(x)                                          ((x) + 0x0000001c)
#define HWIO_QAD0_AIDR_RMSK                                                   0xff
#define HWIO_QAD0_AIDR_POR                                              0x00000000
#define HWIO_QAD0_AIDR_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_AIDR_ATTR                                                    0x1
#define HWIO_QAD0_AIDR_IN(x)      \
        in_dword_masked(HWIO_QAD0_AIDR_ADDR(x), HWIO_QAD0_AIDR_RMSK)
#define HWIO_QAD0_AIDR_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_AIDR_ADDR(x), m)
#define HWIO_QAD0_AIDR_ARCHMAJORREV_BMSK                                      0xf0
#define HWIO_QAD0_AIDR_ARCHMAJORREV_SHFT                                       0x4
#define HWIO_QAD0_AIDR_ARCHMINORREV_BMSK                                       0xf
#define HWIO_QAD0_AIDR_ARCHMINORREV_SHFT                                       0x0

#define HWIO_QAD0_CR0_ADDR(x)                                           ((x) + 0x00000020)
#define HWIO_QAD0_CR0_PHYS(x)                                           ((x) + 0x00000020)
#define HWIO_QAD0_CR0_RMSK                                                   0x1df
#define HWIO_QAD0_CR0_POR                                               0x00000000
#define HWIO_QAD0_CR0_POR_RMSK                                          0xffffffff
#define HWIO_QAD0_CR0_ATTR                                                     0x3
#define HWIO_QAD0_CR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_CR0_ADDR(x), HWIO_QAD0_CR0_RMSK)
#define HWIO_QAD0_CR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CR0_ADDR(x), m)
#define HWIO_QAD0_CR0_OUT(x, v)      \
        out_dword(HWIO_QAD0_CR0_ADDR(x),v)
#define HWIO_QAD0_CR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_CR0_ADDR(x),m,v,HWIO_QAD0_CR0_IN(x))
#define HWIO_QAD0_CR0_VMW_BMSK                                               0x1c0
#define HWIO_QAD0_CR0_VMW_SHFT                                                 0x6
#define HWIO_QAD0_CR0_ATSCHK_BMSK                                             0x10
#define HWIO_QAD0_CR0_ATSCHK_SHFT                                              0x4
#define HWIO_QAD0_CR0_CMDQEN_BMSK                                              0x8
#define HWIO_QAD0_CR0_CMDQEN_SHFT                                              0x3
#define HWIO_QAD0_CR0_EVENTQEN_BMSK                                            0x4
#define HWIO_QAD0_CR0_EVENTQEN_SHFT                                            0x2
#define HWIO_QAD0_CR0_PRIQEN_BMSK                                              0x2
#define HWIO_QAD0_CR0_PRIQEN_SHFT                                              0x1
#define HWIO_QAD0_CR0_SMMUEN_BMSK                                              0x1
#define HWIO_QAD0_CR0_SMMUEN_SHFT                                              0x0

#define HWIO_QAD0_CR0ACK_ADDR(x)                                        ((x) + 0x00000024)
#define HWIO_QAD0_CR0ACK_PHYS(x)                                        ((x) + 0x00000024)
#define HWIO_QAD0_CR0ACK_RMSK                                                0x1df
#define HWIO_QAD0_CR0ACK_POR                                            0x00000000
#define HWIO_QAD0_CR0ACK_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_CR0ACK_ATTR                                                  0x1
#define HWIO_QAD0_CR0ACK_IN(x)      \
        in_dword_masked(HWIO_QAD0_CR0ACK_ADDR(x), HWIO_QAD0_CR0ACK_RMSK)
#define HWIO_QAD0_CR0ACK_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CR0ACK_ADDR(x), m)
#define HWIO_QAD0_CR0ACK_VMW_BMSK                                            0x1c0
#define HWIO_QAD0_CR0ACK_VMW_SHFT                                              0x6
#define HWIO_QAD0_CR0ACK_ATSCHK_BMSK                                          0x10
#define HWIO_QAD0_CR0ACK_ATSCHK_SHFT                                           0x4
#define HWIO_QAD0_CR0ACK_CMDQEN_BMSK                                           0x8
#define HWIO_QAD0_CR0ACK_CMDQEN_SHFT                                           0x3
#define HWIO_QAD0_CR0ACK_EVENTQEN_BMSK                                         0x4
#define HWIO_QAD0_CR0ACK_EVENTQEN_SHFT                                         0x2
#define HWIO_QAD0_CR0ACK_PRIQEN_BMSK                                           0x2
#define HWIO_QAD0_CR0ACK_PRIQEN_SHFT                                           0x1
#define HWIO_QAD0_CR0ACK_SMMUEN_BMSK                                           0x1
#define HWIO_QAD0_CR0ACK_SMMUEN_SHFT                                           0x0

#define HWIO_QAD0_CR1_ADDR(x)                                           ((x) + 0x00000028)
#define HWIO_QAD0_CR1_PHYS(x)                                           ((x) + 0x00000028)
#define HWIO_QAD0_CR1_RMSK                                                   0xfff
#define HWIO_QAD0_CR1_POR                                               0x00000000
#define HWIO_QAD0_CR1_POR_RMSK                                          0xffffffff
#define HWIO_QAD0_CR1_ATTR                                                     0x3
#define HWIO_QAD0_CR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_CR1_ADDR(x), HWIO_QAD0_CR1_RMSK)
#define HWIO_QAD0_CR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CR1_ADDR(x), m)
#define HWIO_QAD0_CR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_CR1_ADDR(x),v)
#define HWIO_QAD0_CR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_CR1_ADDR(x),m,v,HWIO_QAD0_CR1_IN(x))
#define HWIO_QAD0_CR1_TABLE_SH_BMSK                                          0xc00
#define HWIO_QAD0_CR1_TABLE_SH_SHFT                                            0xa
#define HWIO_QAD0_CR1_TABLE_OC_BMSK                                          0x300
#define HWIO_QAD0_CR1_TABLE_OC_SHFT                                            0x8
#define HWIO_QAD0_CR1_TABLE_IC_BMSK                                           0xc0
#define HWIO_QAD0_CR1_TABLE_IC_SHFT                                            0x6
#define HWIO_QAD0_CR1_QUEUE_SH_BMSK                                           0x30
#define HWIO_QAD0_CR1_QUEUE_SH_SHFT                                            0x4
#define HWIO_QAD0_CR1_QUEUE_OC_BMSK                                            0xc
#define HWIO_QAD0_CR1_QUEUE_OC_SHFT                                            0x2
#define HWIO_QAD0_CR1_QUEUE_IC_BMSK                                            0x3
#define HWIO_QAD0_CR1_QUEUE_IC_SHFT                                            0x0

#define HWIO_QAD0_CR2_ADDR(x)                                           ((x) + 0x0000002c)
#define HWIO_QAD0_CR2_PHYS(x)                                           ((x) + 0x0000002c)
#define HWIO_QAD0_CR2_RMSK                                                     0x7
#define HWIO_QAD0_CR2_POR                                               0x00000004
#define HWIO_QAD0_CR2_POR_RMSK                                          0xffffffff
#define HWIO_QAD0_CR2_ATTR                                                     0x3
#define HWIO_QAD0_CR2_IN(x)      \
        in_dword_masked(HWIO_QAD0_CR2_ADDR(x), HWIO_QAD0_CR2_RMSK)
#define HWIO_QAD0_CR2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CR2_ADDR(x), m)
#define HWIO_QAD0_CR2_OUT(x, v)      \
        out_dword(HWIO_QAD0_CR2_ADDR(x),v)
#define HWIO_QAD0_CR2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_CR2_ADDR(x),m,v,HWIO_QAD0_CR2_IN(x))
#define HWIO_QAD0_CR2_PTM_BMSK                                                 0x4
#define HWIO_QAD0_CR2_PTM_SHFT                                                 0x2
#define HWIO_QAD0_CR2_RECINVSID_BMSK                                           0x2
#define HWIO_QAD0_CR2_RECINVSID_SHFT                                           0x1
#define HWIO_QAD0_CR2_E2H_BMSK                                                 0x1
#define HWIO_QAD0_CR2_E2H_SHFT                                                 0x0

#define HWIO_QAD0_STATUSR_ADDR(x)                                       ((x) + 0x00000040)
#define HWIO_QAD0_STATUSR_PHYS(x)                                       ((x) + 0x00000040)
#define HWIO_QAD0_STATUSR_RMSK                                                 0x1
#define HWIO_QAD0_STATUSR_POR                                           0x00000000
#define HWIO_QAD0_STATUSR_POR_RMSK                                      0xffffffff
#define HWIO_QAD0_STATUSR_ATTR                                                 0x1
#define HWIO_QAD0_STATUSR_IN(x)      \
        in_dword_masked(HWIO_QAD0_STATUSR_ADDR(x), HWIO_QAD0_STATUSR_RMSK)
#define HWIO_QAD0_STATUSR_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_STATUSR_ADDR(x), m)
#define HWIO_QAD0_STATUSR_DORMANT_BMSK                                         0x1
#define HWIO_QAD0_STATUSR_DORMANT_SHFT                                         0x0

#define HWIO_QAD0_GBPA_ADDR(x)                                          ((x) + 0x00000044)
#define HWIO_QAD0_GBPA_PHYS(x)                                          ((x) + 0x00000044)
#define HWIO_QAD0_GBPA_RMSK                                             0x801f3f1f
#define HWIO_QAD0_GBPA_POR                                              0x00001000
#define HWIO_QAD0_GBPA_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_GBPA_ATTR                                                    0x3
#define HWIO_QAD0_GBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_GBPA_ADDR(x), HWIO_QAD0_GBPA_RMSK)
#define HWIO_QAD0_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GBPA_ADDR(x), m)
#define HWIO_QAD0_GBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_GBPA_ADDR(x),v)
#define HWIO_QAD0_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GBPA_ADDR(x),m,v,HWIO_QAD0_GBPA_IN(x))
#define HWIO_QAD0_GBPA_UPDATE_BMSK                                      0x80000000
#define HWIO_QAD0_GBPA_UPDATE_SHFT                                            0x1f
#define HWIO_QAD0_GBPA_ABORT_BMSK                                         0x100000
#define HWIO_QAD0_GBPA_ABORT_SHFT                                             0x14
#define HWIO_QAD0_GBPA_INSTCFG_BMSK                                        0xc0000
#define HWIO_QAD0_GBPA_INSTCFG_SHFT                                           0x12
#define HWIO_QAD0_GBPA_PRIVCFG_BMSK                                        0x30000
#define HWIO_QAD0_GBPA_PRIVCFG_SHFT                                           0x10
#define HWIO_QAD0_GBPA_SHCFG_BMSK                                           0x3000
#define HWIO_QAD0_GBPA_SHCFG_SHFT                                              0xc
#define HWIO_QAD0_GBPA_ALLOCCFG_BMSK                                         0xf00
#define HWIO_QAD0_GBPA_ALLOCCFG_SHFT                                           0x8
#define HWIO_QAD0_GBPA_MTCFG_BMSK                                             0x10
#define HWIO_QAD0_GBPA_MTCFG_SHFT                                              0x4
#define HWIO_QAD0_GBPA_MEMATTR_BMSK                                            0xf
#define HWIO_QAD0_GBPA_MEMATTR_SHFT                                            0x0

#define HWIO_QAD0_AGBPA_ADDR(x)                                         ((x) + 0x00000048)
#define HWIO_QAD0_AGBPA_PHYS(x)                                         ((x) + 0x00000048)
#define HWIO_QAD0_AGBPA_RMSK                                               0x7ffff
#define HWIO_QAD0_AGBPA_POR                                             0x00000000
#define HWIO_QAD0_AGBPA_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_AGBPA_ATTR                                                   0x3
#define HWIO_QAD0_AGBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_AGBPA_ADDR(x), HWIO_QAD0_AGBPA_RMSK)
#define HWIO_QAD0_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_AGBPA_ADDR(x), m)
#define HWIO_QAD0_AGBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_AGBPA_ADDR(x),v)
#define HWIO_QAD0_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_AGBPA_ADDR(x),m,v,HWIO_QAD0_AGBPA_IN(x))
#define HWIO_QAD0_AGBPA_REQPRIORITY_BMSK                                   0x60000
#define HWIO_QAD0_AGBPA_REQPRIORITY_SHFT                                      0x11
#define HWIO_QAD0_AGBPA_REQPRIORITY_REPLACE_BMSK                           0x10000
#define HWIO_QAD0_AGBPA_REQPRIORITY_REPLACE_SHFT                              0x10
#define HWIO_QAD0_AGBPA_BPVMID_BMSK                                         0xffff
#define HWIO_QAD0_AGBPA_BPVMID_SHFT                                            0x0

#define HWIO_QAD0_IRQ_CTRL_ADDR(x)                                      ((x) + 0x00000050)
#define HWIO_QAD0_IRQ_CTRL_PHYS(x)                                      ((x) + 0x00000050)
#define HWIO_QAD0_IRQ_CTRL_RMSK                                                0x7
#define HWIO_QAD0_IRQ_CTRL_POR                                          0x00000000
#define HWIO_QAD0_IRQ_CTRL_POR_RMSK                                     0xffffffff
#define HWIO_QAD0_IRQ_CTRL_ATTR                                                0x3
#define HWIO_QAD0_IRQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_QAD0_IRQ_CTRL_ADDR(x), HWIO_QAD0_IRQ_CTRL_RMSK)
#define HWIO_QAD0_IRQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IRQ_CTRL_ADDR(x), m)
#define HWIO_QAD0_IRQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_QAD0_IRQ_CTRL_ADDR(x),v)
#define HWIO_QAD0_IRQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_IRQ_CTRL_ADDR(x),m,v,HWIO_QAD0_IRQ_CTRL_IN(x))
#define HWIO_QAD0_IRQ_CTRL_EVENTQ_IRQEN_BMSK                                   0x4
#define HWIO_QAD0_IRQ_CTRL_EVENTQ_IRQEN_SHFT                                   0x2
#define HWIO_QAD0_IRQ_CTRL_PRIQ_IRQEN_BMSK                                     0x2
#define HWIO_QAD0_IRQ_CTRL_PRIQ_IRQEN_SHFT                                     0x1
#define HWIO_QAD0_IRQ_CTRL_GERROR_IRQEN_BMSK                                   0x1
#define HWIO_QAD0_IRQ_CTRL_GERROR_IRQEN_SHFT                                   0x0

#define HWIO_QAD0_IRQ_CTRLACK_ADDR(x)                                   ((x) + 0x00000054)
#define HWIO_QAD0_IRQ_CTRLACK_PHYS(x)                                   ((x) + 0x00000054)
#define HWIO_QAD0_IRQ_CTRLACK_RMSK                                             0x7
#define HWIO_QAD0_IRQ_CTRLACK_POR                                       0x00000000
#define HWIO_QAD0_IRQ_CTRLACK_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_IRQ_CTRLACK_ATTR                                             0x1
#define HWIO_QAD0_IRQ_CTRLACK_IN(x)      \
        in_dword_masked(HWIO_QAD0_IRQ_CTRLACK_ADDR(x), HWIO_QAD0_IRQ_CTRLACK_RMSK)
#define HWIO_QAD0_IRQ_CTRLACK_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_IRQ_CTRLACK_ADDR(x), m)
#define HWIO_QAD0_IRQ_CTRLACK_EVENTQ_IRQEN_BMSK                                0x4
#define HWIO_QAD0_IRQ_CTRLACK_EVENTQ_IRQEN_SHFT                                0x2
#define HWIO_QAD0_IRQ_CTRLACK_PRIQ_IRQEN_BMSK                                  0x2
#define HWIO_QAD0_IRQ_CTRLACK_PRIQ_IRQEN_SHFT                                  0x1
#define HWIO_QAD0_IRQ_CTRLACK_GERROR_IRQEN_BMSK                                0x1
#define HWIO_QAD0_IRQ_CTRLACK_GERROR_IRQEN_SHFT                                0x0

#define HWIO_QAD0_GERROR_ADDR(x)                                        ((x) + 0x00000060)
#define HWIO_QAD0_GERROR_PHYS(x)                                        ((x) + 0x00000060)
#define HWIO_QAD0_GERROR_RMSK                                                0x1fd
#define HWIO_QAD0_GERROR_POR                                            0x00000000
#define HWIO_QAD0_GERROR_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_GERROR_ATTR                                                  0x1
#define HWIO_QAD0_GERROR_IN(x)      \
        in_dword_masked(HWIO_QAD0_GERROR_ADDR(x), HWIO_QAD0_GERROR_RMSK)
#define HWIO_QAD0_GERROR_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GERROR_ADDR(x), m)
#define HWIO_QAD0_GERROR_SFM_ERR_BMSK                                        0x100
#define HWIO_QAD0_GERROR_SFM_ERR_SHFT                                          0x8
#define HWIO_QAD0_GERROR_MSI_GERROR_ABT_ERR_BMSK                              0x80
#define HWIO_QAD0_GERROR_MSI_GERROR_ABT_ERR_SHFT                               0x7
#define HWIO_QAD0_GERROR_MSI_PRIQ_ABT_ERR_BMSK                                0x40
#define HWIO_QAD0_GERROR_MSI_PRIQ_ABT_ERR_SHFT                                 0x6
#define HWIO_QAD0_GERROR_MSI_EVENTQ_ABT_ERR_BMSK                              0x20
#define HWIO_QAD0_GERROR_MSI_EVENTQ_ABT_ERR_SHFT                               0x5
#define HWIO_QAD0_GERROR_MSI_CMDQ_ABT_ERR_BMSK                                0x10
#define HWIO_QAD0_GERROR_MSI_CMDQ_ABT_ERR_SHFT                                 0x4
#define HWIO_QAD0_GERROR_PRIQ_ABT_ERR_BMSK                                     0x8
#define HWIO_QAD0_GERROR_PRIQ_ABT_ERR_SHFT                                     0x3
#define HWIO_QAD0_GERROR_EVENTQ_ABT_ERR_BMSK                                   0x4
#define HWIO_QAD0_GERROR_EVENTQ_ABT_ERR_SHFT                                   0x2
#define HWIO_QAD0_GERROR_CMDQ_ERR_BMSK                                         0x1
#define HWIO_QAD0_GERROR_CMDQ_ERR_SHFT                                         0x0

#define HWIO_QAD0_GERRORN_ADDR(x)                                       ((x) + 0x00000064)
#define HWIO_QAD0_GERRORN_PHYS(x)                                       ((x) + 0x00000064)
#define HWIO_QAD0_GERRORN_RMSK                                               0x1fd
#define HWIO_QAD0_GERRORN_POR                                           0x00000000
#define HWIO_QAD0_GERRORN_POR_RMSK                                      0xffffffff
#define HWIO_QAD0_GERRORN_ATTR                                                 0x3
#define HWIO_QAD0_GERRORN_IN(x)      \
        in_dword_masked(HWIO_QAD0_GERRORN_ADDR(x), HWIO_QAD0_GERRORN_RMSK)
#define HWIO_QAD0_GERRORN_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GERRORN_ADDR(x), m)
#define HWIO_QAD0_GERRORN_OUT(x, v)      \
        out_dword(HWIO_QAD0_GERRORN_ADDR(x),v)
#define HWIO_QAD0_GERRORN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GERRORN_ADDR(x),m,v,HWIO_QAD0_GERRORN_IN(x))
#define HWIO_QAD0_GERRORN_SFM_ERR_BMSK                                       0x100
#define HWIO_QAD0_GERRORN_SFM_ERR_SHFT                                         0x8
#define HWIO_QAD0_GERRORN_MSI_GERROR_ABT_ERR_BMSK                             0x80
#define HWIO_QAD0_GERRORN_MSI_GERROR_ABT_ERR_SHFT                              0x7
#define HWIO_QAD0_GERRORN_MSI_PRIQ_ABT_ERR_BMSK                               0x40
#define HWIO_QAD0_GERRORN_MSI_PRIQ_ABT_ERR_SHFT                                0x6
#define HWIO_QAD0_GERRORN_MSI_EVENTQ_ABT_ERR_BMSK                             0x20
#define HWIO_QAD0_GERRORN_MSI_EVENTQ_ABT_ERR_SHFT                              0x5
#define HWIO_QAD0_GERRORN_MSI_CMDQ_ABT_ERR_BMSK                               0x10
#define HWIO_QAD0_GERRORN_MSI_CMDQ_ABT_ERR_SHFT                                0x4
#define HWIO_QAD0_GERRORN_PRIQ_ABT_ERR_BMSK                                    0x8
#define HWIO_QAD0_GERRORN_PRIQ_ABT_ERR_SHFT                                    0x3
#define HWIO_QAD0_GERRORN_EVENTQ_ABT_ERR_BMSK                                  0x4
#define HWIO_QAD0_GERRORN_EVENTQ_ABT_ERR_SHFT                                  0x2
#define HWIO_QAD0_GERRORN_CMDQ_ERR_BMSK                                        0x1
#define HWIO_QAD0_GERRORN_CMDQ_ERR_SHFT                                        0x0

#define HWIO_QAD0_GERROR_IRQ_CFG0_L_ADDR(x)                             ((x) + 0x00000068)
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_PHYS(x)                             ((x) + 0x00000068)
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_RMSK                                0xfffffffc
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_POR                                 0x00000000
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_POR_RMSK                            0xffffffff
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_ATTR                                       0x3
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_GERROR_IRQ_CFG0_L_ADDR(x), HWIO_QAD0_GERROR_IRQ_CFG0_L_RMSK)
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GERROR_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_GERROR_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GERROR_IRQ_CFG0_L_ADDR(x),m,v,HWIO_QAD0_GERROR_IRQ_CFG0_L_IN(x))
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_ADDR_31_2_BMSK                      0xfffffffc
#define HWIO_QAD0_GERROR_IRQ_CFG0_L_ADDR_31_2_SHFT                             0x2

#define HWIO_QAD0_GERROR_IRQ_CFG0_H_ADDR(x)                             ((x) + 0x0000006c)
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_PHYS(x)                             ((x) + 0x0000006c)
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_RMSK                                    0xffff
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_POR                                 0x00000000
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_POR_RMSK                            0xffffffff
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_ATTR                                       0x3
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_GERROR_IRQ_CFG0_H_ADDR(x), HWIO_QAD0_GERROR_IRQ_CFG0_H_RMSK)
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GERROR_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_GERROR_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GERROR_IRQ_CFG0_H_ADDR(x),m,v,HWIO_QAD0_GERROR_IRQ_CFG0_H_IN(x))
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_ADDR_47_32_BMSK                         0xffff
#define HWIO_QAD0_GERROR_IRQ_CFG0_H_ADDR_47_32_SHFT                            0x0

#define HWIO_QAD0_GERROR_IRQ_CFG1_ADDR(x)                               ((x) + 0x00000070)
#define HWIO_QAD0_GERROR_IRQ_CFG1_PHYS(x)                               ((x) + 0x00000070)
#define HWIO_QAD0_GERROR_IRQ_CFG1_RMSK                                  0xffffffff
#define HWIO_QAD0_GERROR_IRQ_CFG1_POR                                   0x00000000
#define HWIO_QAD0_GERROR_IRQ_CFG1_POR_RMSK                              0xffffffff
#define HWIO_QAD0_GERROR_IRQ_CFG1_ATTR                                         0x3
#define HWIO_QAD0_GERROR_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_QAD0_GERROR_IRQ_CFG1_ADDR(x), HWIO_QAD0_GERROR_IRQ_CFG1_RMSK)
#define HWIO_QAD0_GERROR_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GERROR_IRQ_CFG1_ADDR(x), m)
#define HWIO_QAD0_GERROR_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_QAD0_GERROR_IRQ_CFG1_ADDR(x),v)
#define HWIO_QAD0_GERROR_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GERROR_IRQ_CFG1_ADDR(x),m,v,HWIO_QAD0_GERROR_IRQ_CFG1_IN(x))
#define HWIO_QAD0_GERROR_IRQ_CFG1_DATA_BMSK                             0xffffffff
#define HWIO_QAD0_GERROR_IRQ_CFG1_DATA_SHFT                                    0x0

#define HWIO_QAD0_GERROR_IRQ_CFG2_ADDR(x)                               ((x) + 0x00000074)
#define HWIO_QAD0_GERROR_IRQ_CFG2_PHYS(x)                               ((x) + 0x00000074)
#define HWIO_QAD0_GERROR_IRQ_CFG2_RMSK                                        0x3f
#define HWIO_QAD0_GERROR_IRQ_CFG2_POR                                   0x00000000
#define HWIO_QAD0_GERROR_IRQ_CFG2_POR_RMSK                              0xffffffff
#define HWIO_QAD0_GERROR_IRQ_CFG2_ATTR                                         0x3
#define HWIO_QAD0_GERROR_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_QAD0_GERROR_IRQ_CFG2_ADDR(x), HWIO_QAD0_GERROR_IRQ_CFG2_RMSK)
#define HWIO_QAD0_GERROR_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GERROR_IRQ_CFG2_ADDR(x), m)
#define HWIO_QAD0_GERROR_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_QAD0_GERROR_IRQ_CFG2_ADDR(x),v)
#define HWIO_QAD0_GERROR_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GERROR_IRQ_CFG2_ADDR(x),m,v,HWIO_QAD0_GERROR_IRQ_CFG2_IN(x))
#define HWIO_QAD0_GERROR_IRQ_CFG2_SH_BMSK                                     0x30
#define HWIO_QAD0_GERROR_IRQ_CFG2_SH_SHFT                                      0x4
#define HWIO_QAD0_GERROR_IRQ_CFG2_MEMATTR_BMSK                                 0xf
#define HWIO_QAD0_GERROR_IRQ_CFG2_MEMATTR_SHFT                                 0x0

#define HWIO_QAD0_STRTAB_BASE_L_ADDR(x)                                 ((x) + 0x00000080)
#define HWIO_QAD0_STRTAB_BASE_L_PHYS(x)                                 ((x) + 0x00000080)
#define HWIO_QAD0_STRTAB_BASE_L_RMSK                                    0xffffffc0
#define HWIO_QAD0_STRTAB_BASE_L_POR                                     0x00000000
#define HWIO_QAD0_STRTAB_BASE_L_POR_RMSK                                0xffffffff
#define HWIO_QAD0_STRTAB_BASE_L_ATTR                                           0x3
#define HWIO_QAD0_STRTAB_BASE_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_STRTAB_BASE_L_ADDR(x), HWIO_QAD0_STRTAB_BASE_L_RMSK)
#define HWIO_QAD0_STRTAB_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_STRTAB_BASE_L_ADDR(x), m)
#define HWIO_QAD0_STRTAB_BASE_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_STRTAB_BASE_L_ADDR(x),v)
#define HWIO_QAD0_STRTAB_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_STRTAB_BASE_L_ADDR(x),m,v,HWIO_QAD0_STRTAB_BASE_L_IN(x))
#define HWIO_QAD0_STRTAB_BASE_L_ADDR_31_6_BMSK                          0xffffffc0
#define HWIO_QAD0_STRTAB_BASE_L_ADDR_31_6_SHFT                                 0x6

#define HWIO_QAD0_STRTAB_BASE_H_ADDR(x)                                 ((x) + 0x00000084)
#define HWIO_QAD0_STRTAB_BASE_H_PHYS(x)                                 ((x) + 0x00000084)
#define HWIO_QAD0_STRTAB_BASE_H_RMSK                                    0x4000ffff
#define HWIO_QAD0_STRTAB_BASE_H_POR                                     0x00000000
#define HWIO_QAD0_STRTAB_BASE_H_POR_RMSK                                0xffffffff
#define HWIO_QAD0_STRTAB_BASE_H_ATTR                                           0x3
#define HWIO_QAD0_STRTAB_BASE_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_STRTAB_BASE_H_ADDR(x), HWIO_QAD0_STRTAB_BASE_H_RMSK)
#define HWIO_QAD0_STRTAB_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_STRTAB_BASE_H_ADDR(x), m)
#define HWIO_QAD0_STRTAB_BASE_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_STRTAB_BASE_H_ADDR(x),v)
#define HWIO_QAD0_STRTAB_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_STRTAB_BASE_H_ADDR(x),m,v,HWIO_QAD0_STRTAB_BASE_H_IN(x))
#define HWIO_QAD0_STRTAB_BASE_H_RA_BMSK                                 0x40000000
#define HWIO_QAD0_STRTAB_BASE_H_RA_SHFT                                       0x1e
#define HWIO_QAD0_STRTAB_BASE_H_ADDR_47_32_BMSK                             0xffff
#define HWIO_QAD0_STRTAB_BASE_H_ADDR_47_32_SHFT                                0x0

#define HWIO_QAD0_STRTAB_BASE_CFG_ADDR(x)                               ((x) + 0x00000088)
#define HWIO_QAD0_STRTAB_BASE_CFG_PHYS(x)                               ((x) + 0x00000088)
#define HWIO_QAD0_STRTAB_BASE_CFG_RMSK                                     0x307ff
#define HWIO_QAD0_STRTAB_BASE_CFG_POR                                   0x00000000
#define HWIO_QAD0_STRTAB_BASE_CFG_POR_RMSK                              0xffffffff
#define HWIO_QAD0_STRTAB_BASE_CFG_ATTR                                         0x3
#define HWIO_QAD0_STRTAB_BASE_CFG_IN(x)      \
        in_dword_masked(HWIO_QAD0_STRTAB_BASE_CFG_ADDR(x), HWIO_QAD0_STRTAB_BASE_CFG_RMSK)
#define HWIO_QAD0_STRTAB_BASE_CFG_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_STRTAB_BASE_CFG_ADDR(x), m)
#define HWIO_QAD0_STRTAB_BASE_CFG_OUT(x, v)      \
        out_dword(HWIO_QAD0_STRTAB_BASE_CFG_ADDR(x),v)
#define HWIO_QAD0_STRTAB_BASE_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_STRTAB_BASE_CFG_ADDR(x),m,v,HWIO_QAD0_STRTAB_BASE_CFG_IN(x))
#define HWIO_QAD0_STRTAB_BASE_CFG_FMT_BMSK                                 0x30000
#define HWIO_QAD0_STRTAB_BASE_CFG_FMT_SHFT                                    0x10
#define HWIO_QAD0_STRTAB_BASE_CFG_SPLIT_BMSK                                 0x7c0
#define HWIO_QAD0_STRTAB_BASE_CFG_SPLIT_SHFT                                   0x6
#define HWIO_QAD0_STRTAB_BASE_CFG_LOG2SIZE_BMSK                               0x3f
#define HWIO_QAD0_STRTAB_BASE_CFG_LOG2SIZE_SHFT                                0x0

#define HWIO_QAD0_CMDQ_BASE_L_ADDR(x)                                   ((x) + 0x00000090)
#define HWIO_QAD0_CMDQ_BASE_L_PHYS(x)                                   ((x) + 0x00000090)
#define HWIO_QAD0_CMDQ_BASE_L_RMSK                                      0xffffffff
#define HWIO_QAD0_CMDQ_BASE_L_POR                                       0x00000000
#define HWIO_QAD0_CMDQ_BASE_L_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_CMDQ_BASE_L_ATTR                                             0x3
#define HWIO_QAD0_CMDQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_CMDQ_BASE_L_ADDR(x), HWIO_QAD0_CMDQ_BASE_L_RMSK)
#define HWIO_QAD0_CMDQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CMDQ_BASE_L_ADDR(x), m)
#define HWIO_QAD0_CMDQ_BASE_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_CMDQ_BASE_L_ADDR(x),v)
#define HWIO_QAD0_CMDQ_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_CMDQ_BASE_L_ADDR(x),m,v,HWIO_QAD0_CMDQ_BASE_L_IN(x))
#define HWIO_QAD0_CMDQ_BASE_L_ADDR_31_5_BMSK                            0xffffffe0
#define HWIO_QAD0_CMDQ_BASE_L_ADDR_31_5_SHFT                                   0x5
#define HWIO_QAD0_CMDQ_BASE_L_LOG2SIZE_BMSK                                   0x1f
#define HWIO_QAD0_CMDQ_BASE_L_LOG2SIZE_SHFT                                    0x0

#define HWIO_QAD0_CMDQ_BASE_H_ADDR(x)                                   ((x) + 0x00000094)
#define HWIO_QAD0_CMDQ_BASE_H_PHYS(x)                                   ((x) + 0x00000094)
#define HWIO_QAD0_CMDQ_BASE_H_RMSK                                      0x4000ffff
#define HWIO_QAD0_CMDQ_BASE_H_POR                                       0x00000000
#define HWIO_QAD0_CMDQ_BASE_H_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_CMDQ_BASE_H_ATTR                                             0x3
#define HWIO_QAD0_CMDQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_CMDQ_BASE_H_ADDR(x), HWIO_QAD0_CMDQ_BASE_H_RMSK)
#define HWIO_QAD0_CMDQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CMDQ_BASE_H_ADDR(x), m)
#define HWIO_QAD0_CMDQ_BASE_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_CMDQ_BASE_H_ADDR(x),v)
#define HWIO_QAD0_CMDQ_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_CMDQ_BASE_H_ADDR(x),m,v,HWIO_QAD0_CMDQ_BASE_H_IN(x))
#define HWIO_QAD0_CMDQ_BASE_H_RA_BMSK                                   0x40000000
#define HWIO_QAD0_CMDQ_BASE_H_RA_SHFT                                         0x1e
#define HWIO_QAD0_CMDQ_BASE_H_ADDR_47_32_BMSK                               0xffff
#define HWIO_QAD0_CMDQ_BASE_H_ADDR_47_32_SHFT                                  0x0

#define HWIO_QAD0_CMDQ_PROD_ADDR(x)                                     ((x) + 0x00000098)
#define HWIO_QAD0_CMDQ_PROD_PHYS(x)                                     ((x) + 0x00000098)
#define HWIO_QAD0_CMDQ_PROD_RMSK                                           0xfffff
#define HWIO_QAD0_CMDQ_PROD_POR                                         0x00000000
#define HWIO_QAD0_CMDQ_PROD_POR_RMSK                                    0xffffffff
#define HWIO_QAD0_CMDQ_PROD_ATTR                                               0x3
#define HWIO_QAD0_CMDQ_PROD_IN(x)      \
        in_dword_masked(HWIO_QAD0_CMDQ_PROD_ADDR(x), HWIO_QAD0_CMDQ_PROD_RMSK)
#define HWIO_QAD0_CMDQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CMDQ_PROD_ADDR(x), m)
#define HWIO_QAD0_CMDQ_PROD_OUT(x, v)      \
        out_dword(HWIO_QAD0_CMDQ_PROD_ADDR(x),v)
#define HWIO_QAD0_CMDQ_PROD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_CMDQ_PROD_ADDR(x),m,v,HWIO_QAD0_CMDQ_PROD_IN(x))
#define HWIO_QAD0_CMDQ_PROD_WR_INDEX_AND_WRAP_BMSK                         0xfffff
#define HWIO_QAD0_CMDQ_PROD_WR_INDEX_AND_WRAP_SHFT                             0x0

#define HWIO_QAD0_CMDQ_CONS_ADDR(x)                                     ((x) + 0x0000009c)
#define HWIO_QAD0_CMDQ_CONS_PHYS(x)                                     ((x) + 0x0000009c)
#define HWIO_QAD0_CMDQ_CONS_RMSK                                        0x7f0fffff
#define HWIO_QAD0_CMDQ_CONS_POR                                         0x00000000
#define HWIO_QAD0_CMDQ_CONS_POR_RMSK                                    0xffffffff
#define HWIO_QAD0_CMDQ_CONS_ATTR                                               0x3
#define HWIO_QAD0_CMDQ_CONS_IN(x)      \
        in_dword_masked(HWIO_QAD0_CMDQ_CONS_ADDR(x), HWIO_QAD0_CMDQ_CONS_RMSK)
#define HWIO_QAD0_CMDQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CMDQ_CONS_ADDR(x), m)
#define HWIO_QAD0_CMDQ_CONS_OUT(x, v)      \
        out_dword(HWIO_QAD0_CMDQ_CONS_ADDR(x),v)
#define HWIO_QAD0_CMDQ_CONS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_CMDQ_CONS_ADDR(x),m,v,HWIO_QAD0_CMDQ_CONS_IN(x))
#define HWIO_QAD0_CMDQ_CONS_ERR_BMSK                                    0x7f000000
#define HWIO_QAD0_CMDQ_CONS_ERR_SHFT                                          0x18
#define HWIO_QAD0_CMDQ_CONS_RD_INDEX_AND_WRAP_BMSK                         0xfffff
#define HWIO_QAD0_CMDQ_CONS_RD_INDEX_AND_WRAP_SHFT                             0x0

#define HWIO_QAD0_EVENTQ_BASE_L_ADDR(x)                                 ((x) + 0x000000a0)
#define HWIO_QAD0_EVENTQ_BASE_L_PHYS(x)                                 ((x) + 0x000000a0)
#define HWIO_QAD0_EVENTQ_BASE_L_RMSK                                    0xffffffff
#define HWIO_QAD0_EVENTQ_BASE_L_POR                                     0x00000000
#define HWIO_QAD0_EVENTQ_BASE_L_POR_RMSK                                0xffffffff
#define HWIO_QAD0_EVENTQ_BASE_L_ATTR                                           0x3
#define HWIO_QAD0_EVENTQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_BASE_L_ADDR(x), HWIO_QAD0_EVENTQ_BASE_L_RMSK)
#define HWIO_QAD0_EVENTQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_BASE_L_ADDR(x), m)
#define HWIO_QAD0_EVENTQ_BASE_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_EVENTQ_BASE_L_ADDR(x),v)
#define HWIO_QAD0_EVENTQ_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_EVENTQ_BASE_L_ADDR(x),m,v,HWIO_QAD0_EVENTQ_BASE_L_IN(x))
#define HWIO_QAD0_EVENTQ_BASE_L_ADDR_31_5_BMSK                          0xffffffe0
#define HWIO_QAD0_EVENTQ_BASE_L_ADDR_31_5_SHFT                                 0x5
#define HWIO_QAD0_EVENTQ_BASE_L_LOG2SIZE_BMSK                                 0x1f
#define HWIO_QAD0_EVENTQ_BASE_L_LOG2SIZE_SHFT                                  0x0

#define HWIO_QAD0_EVENTQ_BASE_H_ADDR(x)                                 ((x) + 0x000000a4)
#define HWIO_QAD0_EVENTQ_BASE_H_PHYS(x)                                 ((x) + 0x000000a4)
#define HWIO_QAD0_EVENTQ_BASE_H_RMSK                                    0x4000ffff
#define HWIO_QAD0_EVENTQ_BASE_H_POR                                     0x00000000
#define HWIO_QAD0_EVENTQ_BASE_H_POR_RMSK                                0xffffffff
#define HWIO_QAD0_EVENTQ_BASE_H_ATTR                                           0x3
#define HWIO_QAD0_EVENTQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_BASE_H_ADDR(x), HWIO_QAD0_EVENTQ_BASE_H_RMSK)
#define HWIO_QAD0_EVENTQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_BASE_H_ADDR(x), m)
#define HWIO_QAD0_EVENTQ_BASE_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_EVENTQ_BASE_H_ADDR(x),v)
#define HWIO_QAD0_EVENTQ_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_EVENTQ_BASE_H_ADDR(x),m,v,HWIO_QAD0_EVENTQ_BASE_H_IN(x))
#define HWIO_QAD0_EVENTQ_BASE_H_WA_BMSK                                 0x40000000
#define HWIO_QAD0_EVENTQ_BASE_H_WA_SHFT                                       0x1e
#define HWIO_QAD0_EVENTQ_BASE_H_ADDR_47_32_BMSK                             0xffff
#define HWIO_QAD0_EVENTQ_BASE_H_ADDR_47_32_SHFT                                0x0

#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_ADDR(x)                             ((x) + 0x000000b0)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_PHYS(x)                             ((x) + 0x000000b0)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_RMSK                                0xfffffffc
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_POR                                 0x00000000
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_POR_RMSK                            0xffffffff
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_ATTR                                       0x3
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_IRQ_CFG0_L_ADDR(x), HWIO_QAD0_EVENTQ_IRQ_CFG0_L_RMSK)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_EVENTQ_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_EVENTQ_IRQ_CFG0_L_ADDR(x),m,v,HWIO_QAD0_EVENTQ_IRQ_CFG0_L_IN(x))
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_ADDR_31_2_BMSK                      0xfffffffc
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_L_ADDR_31_2_SHFT                             0x2

#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_ADDR(x)                             ((x) + 0x000000b4)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_PHYS(x)                             ((x) + 0x000000b4)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_RMSK                                    0xffff
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_POR                                 0x00000000
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_POR_RMSK                            0xffffffff
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_ATTR                                       0x3
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_IRQ_CFG0_H_ADDR(x), HWIO_QAD0_EVENTQ_IRQ_CFG0_H_RMSK)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_EVENTQ_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_EVENTQ_IRQ_CFG0_H_ADDR(x),m,v,HWIO_QAD0_EVENTQ_IRQ_CFG0_H_IN(x))
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_ADDR_47_32_BMSK                         0xffff
#define HWIO_QAD0_EVENTQ_IRQ_CFG0_H_ADDR_47_32_SHFT                            0x0

#define HWIO_QAD0_EVENTQ_IRQ_CFG1_ADDR(x)                               ((x) + 0x000000b8)
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_PHYS(x)                               ((x) + 0x000000b8)
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_RMSK                                  0xffffffff
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_POR                                   0x00000000
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_POR_RMSK                              0xffffffff
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_ATTR                                         0x3
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_IRQ_CFG1_ADDR(x), HWIO_QAD0_EVENTQ_IRQ_CFG1_RMSK)
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_IRQ_CFG1_ADDR(x), m)
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_QAD0_EVENTQ_IRQ_CFG1_ADDR(x),v)
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_EVENTQ_IRQ_CFG1_ADDR(x),m,v,HWIO_QAD0_EVENTQ_IRQ_CFG1_IN(x))
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_DATA_BMSK                             0xffffffff
#define HWIO_QAD0_EVENTQ_IRQ_CFG1_DATA_SHFT                                    0x0

#define HWIO_QAD0_EVENTQ_IRQ_CFG2_ADDR(x)                               ((x) + 0x000000bc)
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_PHYS(x)                               ((x) + 0x000000bc)
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_RMSK                                        0x3f
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_POR                                   0x00000000
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_POR_RMSK                              0xffffffff
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_ATTR                                         0x3
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_IRQ_CFG2_ADDR(x), HWIO_QAD0_EVENTQ_IRQ_CFG2_RMSK)
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_IRQ_CFG2_ADDR(x), m)
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_QAD0_EVENTQ_IRQ_CFG2_ADDR(x),v)
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_EVENTQ_IRQ_CFG2_ADDR(x),m,v,HWIO_QAD0_EVENTQ_IRQ_CFG2_IN(x))
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_SH_BMSK                                     0x30
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_SH_SHFT                                      0x4
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_MEMATTR_BMSK                                 0xf
#define HWIO_QAD0_EVENTQ_IRQ_CFG2_MEMATTR_SHFT                                 0x0

#define HWIO_QAD0_PRIQ_BASE_L_ADDR(x)                                   ((x) + 0x000000c0)
#define HWIO_QAD0_PRIQ_BASE_L_PHYS(x)                                   ((x) + 0x000000c0)
#define HWIO_QAD0_PRIQ_BASE_L_RMSK                                      0xffffffff
#define HWIO_QAD0_PRIQ_BASE_L_POR                                       0x00000000
#define HWIO_QAD0_PRIQ_BASE_L_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_PRIQ_BASE_L_ATTR                                             0x1
#define HWIO_QAD0_PRIQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_PRIQ_BASE_L_ADDR(x), HWIO_QAD0_PRIQ_BASE_L_RMSK)
#define HWIO_QAD0_PRIQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PRIQ_BASE_L_ADDR(x), m)
#define HWIO_QAD0_PRIQ_BASE_L_ADDR_31_5_BMSK                            0xffffffe0
#define HWIO_QAD0_PRIQ_BASE_L_ADDR_31_5_SHFT                                   0x5
#define HWIO_QAD0_PRIQ_BASE_L_LOG2SIZE_BMSK                                   0x1f
#define HWIO_QAD0_PRIQ_BASE_L_LOG2SIZE_SHFT                                    0x0

#define HWIO_QAD0_PRIQ_BASE_H_ADDR(x)                                   ((x) + 0x000000c4)
#define HWIO_QAD0_PRIQ_BASE_H_PHYS(x)                                   ((x) + 0x000000c4)
#define HWIO_QAD0_PRIQ_BASE_H_RMSK                                      0x4000ffff
#define HWIO_QAD0_PRIQ_BASE_H_POR                                       0x00000000
#define HWIO_QAD0_PRIQ_BASE_H_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_PRIQ_BASE_H_ATTR                                             0x1
#define HWIO_QAD0_PRIQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_PRIQ_BASE_H_ADDR(x), HWIO_QAD0_PRIQ_BASE_H_RMSK)
#define HWIO_QAD0_PRIQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PRIQ_BASE_H_ADDR(x), m)
#define HWIO_QAD0_PRIQ_BASE_H_WA_BMSK                                   0x40000000
#define HWIO_QAD0_PRIQ_BASE_H_WA_SHFT                                         0x1e
#define HWIO_QAD0_PRIQ_BASE_H_ADDR_47_32_BMSK                               0xffff
#define HWIO_QAD0_PRIQ_BASE_H_ADDR_47_32_SHFT                                  0x0

#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_ADDR(x)                               ((x) + 0x000000d0)
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_PHYS(x)                               ((x) + 0x000000d0)
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_RMSK                                  0xfffffffc
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_POR                                   0x00000000
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_POR_RMSK                              0xffffffff
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_ATTR                                         0x1
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_PRIQ_IRQ_CFG0_L_ADDR(x), HWIO_QAD0_PRIQ_IRQ_CFG0_L_RMSK)
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PRIQ_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_ADDR_31_2_BMSK                        0xfffffffc
#define HWIO_QAD0_PRIQ_IRQ_CFG0_L_ADDR_31_2_SHFT                               0x2

#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_ADDR(x)                               ((x) + 0x000000d4)
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_PHYS(x)                               ((x) + 0x000000d4)
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_RMSK                                      0xffff
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_POR                                   0x00000000
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_POR_RMSK                              0xffffffff
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_ATTR                                         0x1
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_PRIQ_IRQ_CFG0_H_ADDR(x), HWIO_QAD0_PRIQ_IRQ_CFG0_H_RMSK)
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PRIQ_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_ADDR_47_32_BMSK                           0xffff
#define HWIO_QAD0_PRIQ_IRQ_CFG0_H_ADDR_47_32_SHFT                              0x0

#define HWIO_QAD0_PRIQ_IRQ_CFG1_ADDR(x)                                 ((x) + 0x000000d8)
#define HWIO_QAD0_PRIQ_IRQ_CFG1_PHYS(x)                                 ((x) + 0x000000d8)
#define HWIO_QAD0_PRIQ_IRQ_CFG1_RMSK                                    0xffffffff
#define HWIO_QAD0_PRIQ_IRQ_CFG1_POR                                     0x00000000
#define HWIO_QAD0_PRIQ_IRQ_CFG1_POR_RMSK                                0xffffffff
#define HWIO_QAD0_PRIQ_IRQ_CFG1_ATTR                                           0x1
#define HWIO_QAD0_PRIQ_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_QAD0_PRIQ_IRQ_CFG1_ADDR(x), HWIO_QAD0_PRIQ_IRQ_CFG1_RMSK)
#define HWIO_QAD0_PRIQ_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PRIQ_IRQ_CFG1_ADDR(x), m)
#define HWIO_QAD0_PRIQ_IRQ_CFG1_DATA_BMSK                               0xffffffff
#define HWIO_QAD0_PRIQ_IRQ_CFG1_DATA_SHFT                                      0x0

#define HWIO_QAD0_PRIQ_IRQ_CFG2_ADDR(x)                                 ((x) + 0x000000dc)
#define HWIO_QAD0_PRIQ_IRQ_CFG2_PHYS(x)                                 ((x) + 0x000000dc)
#define HWIO_QAD0_PRIQ_IRQ_CFG2_RMSK                                    0x8000003f
#define HWIO_QAD0_PRIQ_IRQ_CFG2_POR                                     0x00000000
#define HWIO_QAD0_PRIQ_IRQ_CFG2_POR_RMSK                                0xffffffff
#define HWIO_QAD0_PRIQ_IRQ_CFG2_ATTR                                           0x1
#define HWIO_QAD0_PRIQ_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_QAD0_PRIQ_IRQ_CFG2_ADDR(x), HWIO_QAD0_PRIQ_IRQ_CFG2_RMSK)
#define HWIO_QAD0_PRIQ_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PRIQ_IRQ_CFG2_ADDR(x), m)
#define HWIO_QAD0_PRIQ_IRQ_CFG2_LO_BMSK                                 0x80000000
#define HWIO_QAD0_PRIQ_IRQ_CFG2_LO_SHFT                                       0x1f
#define HWIO_QAD0_PRIQ_IRQ_CFG2_SH_BMSK                                       0x30
#define HWIO_QAD0_PRIQ_IRQ_CFG2_SH_SHFT                                        0x4
#define HWIO_QAD0_PRIQ_IRQ_CFG2_MEMATTR_BMSK                                   0xf
#define HWIO_QAD0_PRIQ_IRQ_CFG2_MEMATTR_SHFT                                   0x0

#define HWIO_QAD0_GATOS_CTRL_ADDR(x)                                    ((x) + 0x00000100)
#define HWIO_QAD0_GATOS_CTRL_PHYS(x)                                    ((x) + 0x00000100)
#define HWIO_QAD0_GATOS_CTRL_RMSK                                              0x1
#define HWIO_QAD0_GATOS_CTRL_POR                                        0x00000000
#define HWIO_QAD0_GATOS_CTRL_POR_RMSK                                   0xffffffff
#define HWIO_QAD0_GATOS_CTRL_ATTR                                              0x3
#define HWIO_QAD0_GATOS_CTRL_IN(x)      \
        in_dword_masked(HWIO_QAD0_GATOS_CTRL_ADDR(x), HWIO_QAD0_GATOS_CTRL_RMSK)
#define HWIO_QAD0_GATOS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GATOS_CTRL_ADDR(x), m)
#define HWIO_QAD0_GATOS_CTRL_OUT(x, v)      \
        out_dword(HWIO_QAD0_GATOS_CTRL_ADDR(x),v)
#define HWIO_QAD0_GATOS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GATOS_CTRL_ADDR(x),m,v,HWIO_QAD0_GATOS_CTRL_IN(x))
#define HWIO_QAD0_GATOS_CTRL_RUN_BMSK                                          0x1
#define HWIO_QAD0_GATOS_CTRL_RUN_SHFT                                          0x0

#define HWIO_QAD0_GATOS_SID_L_ADDR(x)                                   ((x) + 0x00000108)
#define HWIO_QAD0_GATOS_SID_L_PHYS(x)                                   ((x) + 0x00000108)
#define HWIO_QAD0_GATOS_SID_L_RMSK                                          0xffff
#define HWIO_QAD0_GATOS_SID_L_POR                                       0x00000000
#define HWIO_QAD0_GATOS_SID_L_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_GATOS_SID_L_ATTR                                             0x3
#define HWIO_QAD0_GATOS_SID_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_GATOS_SID_L_ADDR(x), HWIO_QAD0_GATOS_SID_L_RMSK)
#define HWIO_QAD0_GATOS_SID_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GATOS_SID_L_ADDR(x), m)
#define HWIO_QAD0_GATOS_SID_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_GATOS_SID_L_ADDR(x),v)
#define HWIO_QAD0_GATOS_SID_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GATOS_SID_L_ADDR(x),m,v,HWIO_QAD0_GATOS_SID_L_IN(x))
#define HWIO_QAD0_GATOS_SID_L_STREAMID_BMSK                                 0xffff
#define HWIO_QAD0_GATOS_SID_L_STREAMID_SHFT                                    0x0

#define HWIO_QAD0_GATOS_SID_H_ADDR(x)                                   ((x) + 0x0000010c)
#define HWIO_QAD0_GATOS_SID_H_PHYS(x)                                   ((x) + 0x0000010c)
#define HWIO_QAD0_GATOS_SID_H_RMSK                                        0x1fffff
#define HWIO_QAD0_GATOS_SID_H_POR                                       0x00000000
#define HWIO_QAD0_GATOS_SID_H_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_GATOS_SID_H_ATTR                                             0x3
#define HWIO_QAD0_GATOS_SID_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_GATOS_SID_H_ADDR(x), HWIO_QAD0_GATOS_SID_H_RMSK)
#define HWIO_QAD0_GATOS_SID_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GATOS_SID_H_ADDR(x), m)
#define HWIO_QAD0_GATOS_SID_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_GATOS_SID_H_ADDR(x),v)
#define HWIO_QAD0_GATOS_SID_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GATOS_SID_H_ADDR(x),m,v,HWIO_QAD0_GATOS_SID_H_IN(x))
#define HWIO_QAD0_GATOS_SID_H_SSID_VALID_BMSK                             0x100000
#define HWIO_QAD0_GATOS_SID_H_SSID_VALID_SHFT                                 0x14
#define HWIO_QAD0_GATOS_SID_H_SUBSTREAMID_BMSK                             0xfffff
#define HWIO_QAD0_GATOS_SID_H_SUBSTREAMID_SHFT                                 0x0

#define HWIO_QAD0_GATOS_ADDR_L_ADDR(x)                                  ((x) + 0x00000110)
#define HWIO_QAD0_GATOS_ADDR_L_PHYS(x)                                  ((x) + 0x00000110)
#define HWIO_QAD0_GATOS_ADDR_L_RMSK                                     0xffffffc0
#define HWIO_QAD0_GATOS_ADDR_L_POR                                      0x00000000
#define HWIO_QAD0_GATOS_ADDR_L_POR_RMSK                                 0xffffffff
#define HWIO_QAD0_GATOS_ADDR_L_ATTR                                            0x3
#define HWIO_QAD0_GATOS_ADDR_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_GATOS_ADDR_L_ADDR(x), HWIO_QAD0_GATOS_ADDR_L_RMSK)
#define HWIO_QAD0_GATOS_ADDR_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GATOS_ADDR_L_ADDR(x), m)
#define HWIO_QAD0_GATOS_ADDR_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_GATOS_ADDR_L_ADDR(x),v)
#define HWIO_QAD0_GATOS_ADDR_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GATOS_ADDR_L_ADDR(x),m,v,HWIO_QAD0_GATOS_ADDR_L_IN(x))
#define HWIO_QAD0_GATOS_ADDR_L_ADDR_31_12_BMSK                          0xfffff000
#define HWIO_QAD0_GATOS_ADDR_L_ADDR_31_12_SHFT                                 0xc
#define HWIO_QAD0_GATOS_ADDR_L_TYPE_BMSK                                     0xc00
#define HWIO_QAD0_GATOS_ADDR_L_TYPE_SHFT                                       0xa
#define HWIO_QAD0_GATOS_ADDR_L_PNU_BMSK                                      0x200
#define HWIO_QAD0_GATOS_ADDR_L_PNU_SHFT                                        0x9
#define HWIO_QAD0_GATOS_ADDR_L_RNW_BMSK                                      0x100
#define HWIO_QAD0_GATOS_ADDR_L_RNW_SHFT                                        0x8
#define HWIO_QAD0_GATOS_ADDR_L_IND_BMSK                                       0x80
#define HWIO_QAD0_GATOS_ADDR_L_IND_SHFT                                        0x7
#define HWIO_QAD0_GATOS_ADDR_L_HTTUI_BMSK                                     0x40
#define HWIO_QAD0_GATOS_ADDR_L_HTTUI_SHFT                                      0x6

#define HWIO_QAD0_GATOS_ADDR_H_ADDR(x)                                  ((x) + 0x00000114)
#define HWIO_QAD0_GATOS_ADDR_H_PHYS(x)                                  ((x) + 0x00000114)
#define HWIO_QAD0_GATOS_ADDR_H_RMSK                                     0xffffffff
#define HWIO_QAD0_GATOS_ADDR_H_POR                                      0x00000000
#define HWIO_QAD0_GATOS_ADDR_H_POR_RMSK                                 0xffffffff
#define HWIO_QAD0_GATOS_ADDR_H_ATTR                                            0x3
#define HWIO_QAD0_GATOS_ADDR_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_GATOS_ADDR_H_ADDR(x), HWIO_QAD0_GATOS_ADDR_H_RMSK)
#define HWIO_QAD0_GATOS_ADDR_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GATOS_ADDR_H_ADDR(x), m)
#define HWIO_QAD0_GATOS_ADDR_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_GATOS_ADDR_H_ADDR(x),v)
#define HWIO_QAD0_GATOS_ADDR_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_GATOS_ADDR_H_ADDR(x),m,v,HWIO_QAD0_GATOS_ADDR_H_IN(x))
#define HWIO_QAD0_GATOS_ADDR_H_ADDR_63_32_BMSK                          0xffffffff
#define HWIO_QAD0_GATOS_ADDR_H_ADDR_63_32_SHFT                                 0x0

#define HWIO_QAD0_GATOS_PAR_L_ADDR(x)                                   ((x) + 0x00000118)
#define HWIO_QAD0_GATOS_PAR_L_PHYS(x)                                   ((x) + 0x00000118)
#define HWIO_QAD0_GATOS_PAR_L_RMSK                                      0xffffffff
#define HWIO_QAD0_GATOS_PAR_L_POR                                       0x00000000
#define HWIO_QAD0_GATOS_PAR_L_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_GATOS_PAR_L_ATTR                                             0x1
#define HWIO_QAD0_GATOS_PAR_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_GATOS_PAR_L_ADDR(x), HWIO_QAD0_GATOS_PAR_L_RMSK)
#define HWIO_QAD0_GATOS_PAR_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GATOS_PAR_L_ADDR(x), m)
#define HWIO_QAD0_GATOS_PAR_L_ADDR_BMSK                                 0xfffff000
#define HWIO_QAD0_GATOS_PAR_L_ADDR_SHFT                                        0xc
#define HWIO_QAD0_GATOS_PAR_L_FIELD_BMSK                                     0xffe
#define HWIO_QAD0_GATOS_PAR_L_FIELD_SHFT                                       0x1
#define HWIO_QAD0_GATOS_PAR_L_FAULT_BMSK                                       0x1
#define HWIO_QAD0_GATOS_PAR_L_FAULT_SHFT                                       0x0

#define HWIO_QAD0_GATOS_PAR_H_ADDR(x)                                   ((x) + 0x0000011c)
#define HWIO_QAD0_GATOS_PAR_H_PHYS(x)                                   ((x) + 0x0000011c)
#define HWIO_QAD0_GATOS_PAR_H_RMSK                                      0xff00ffff
#define HWIO_QAD0_GATOS_PAR_H_POR                                       0x00000000
#define HWIO_QAD0_GATOS_PAR_H_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_GATOS_PAR_H_ATTR                                             0x1
#define HWIO_QAD0_GATOS_PAR_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_GATOS_PAR_H_ADDR(x), HWIO_QAD0_GATOS_PAR_H_RMSK)
#define HWIO_QAD0_GATOS_PAR_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_GATOS_PAR_H_ADDR(x), m)
#define HWIO_QAD0_GATOS_PAR_H_MEMATTR_BMSK                              0xff000000
#define HWIO_QAD0_GATOS_PAR_H_MEMATTR_SHFT                                    0x18
#define HWIO_QAD0_GATOS_PAR_H_ADDR_BMSK                                     0xffff
#define HWIO_QAD0_GATOS_PAR_H_ADDR_SHFT                                        0x0

#define HWIO_QAD0_VATOS_SEL_ADDR(x)                                     ((x) + 0x00000180)
#define HWIO_QAD0_VATOS_SEL_PHYS(x)                                     ((x) + 0x00000180)
#define HWIO_QAD0_VATOS_SEL_RMSK                                            0xffff
#define HWIO_QAD0_VATOS_SEL_POR                                         0x00000000
#define HWIO_QAD0_VATOS_SEL_POR_RMSK                                    0xffffffff
#define HWIO_QAD0_VATOS_SEL_ATTR                                               0x3
#define HWIO_QAD0_VATOS_SEL_IN(x)      \
        in_dword_masked(HWIO_QAD0_VATOS_SEL_ADDR(x), HWIO_QAD0_VATOS_SEL_RMSK)
#define HWIO_QAD0_VATOS_SEL_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_VATOS_SEL_ADDR(x), m)
#define HWIO_QAD0_VATOS_SEL_OUT(x, v)      \
        out_dword(HWIO_QAD0_VATOS_SEL_ADDR(x),v)
#define HWIO_QAD0_VATOS_SEL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_VATOS_SEL_ADDR(x),m,v,HWIO_QAD0_VATOS_SEL_IN(x))
#define HWIO_QAD0_VATOS_SEL_VMID_BMSK                                       0xffff
#define HWIO_QAD0_VATOS_SEL_VMID_SHFT                                          0x0

#define HWIO_QAD0_QIDR0_ADDR(x)                                         ((x) + 0x00000e00)
#define HWIO_QAD0_QIDR0_PHYS(x)                                         ((x) + 0x00000e00)
#define HWIO_QAD0_QIDR0_RMSK                                            0x7ffffff5
#define HWIO_QAD0_QIDR0_POR                                             0x540234f5
#define HWIO_QAD0_QIDR0_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR0_ATTR                                                   0x1
#define HWIO_QAD0_QIDR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR0_ADDR(x), HWIO_QAD0_QIDR0_RMSK)
#define HWIO_QAD0_QIDR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR0_ADDR(x), m)
#define HWIO_QAD0_QIDR0_NUM_QAD_BMSK                                    0x40000000
#define HWIO_QAD0_QIDR0_NUM_QAD_SHFT                                          0x1e
#define HWIO_QAD0_QIDR0_QACT_RST_QAD_VAL_BMSK                           0x20000000
#define HWIO_QAD0_QIDR0_QACT_RST_QAD_VAL_SHFT                                 0x1d
#define HWIO_QAD0_QIDR0_QACT_RST_SSD_VAL_BMSK                           0x10000000
#define HWIO_QAD0_QIDR0_QACT_RST_SSD_VAL_SHFT                                 0x1c
#define HWIO_QAD0_QIDR0_QACT_RST_EN_BMSK                                 0x8000000
#define HWIO_QAD0_QIDR0_QACT_RST_EN_SHFT                                      0x1b
#define HWIO_QAD0_QIDR0_QACT_SIZE_BMSK                                   0x7fc0000
#define HWIO_QAD0_QIDR0_QACT_SIZE_SHFT                                        0x12
#define HWIO_QAD0_QIDR0_QACT_INDEX_WIDTH_BMSK                              0x3c000
#define HWIO_QAD0_QIDR0_QACT_INDEX_WIDTH_SHFT                                  0xe
#define HWIO_QAD0_QIDR0_QACT_SSD_HW_EN_BMSK                                 0x2000
#define HWIO_QAD0_QIDR0_QACT_SSD_HW_EN_SHFT                                    0xd
#define HWIO_QAD0_QIDR0_QACT_QAD_HW_EN_BMSK                                 0x1000
#define HWIO_QAD0_QIDR0_QACT_QAD_HW_EN_SHFT                                    0xc
#define HWIO_QAD0_QIDR0_QAD_NS_TRANS_HW_EN_BMSK                              0x800
#define HWIO_QAD0_QIDR0_QAD_NS_TRANS_HW_EN_SHFT                                0xb
#define HWIO_QAD0_QIDR0_QAD_NS_BYP_HW_EN_BMSK                                0x400
#define HWIO_QAD0_QIDR0_QAD_NS_BYP_HW_EN_SHFT                                  0xa
#define HWIO_QAD0_QIDR0_QAD_S_TRANS_HW_EN_BMSK                               0x200
#define HWIO_QAD0_QIDR0_QAD_S_TRANS_HW_EN_SHFT                                 0x9
#define HWIO_QAD0_QIDR0_QAD_S_BYP_HW_EN_BMSK                                 0x100
#define HWIO_QAD0_QIDR0_QAD_S_BYP_HW_EN_SHFT                                   0x8
#define HWIO_QAD0_QIDR0_CLIENT_MSI_WDATA_GEN_EN_BMSK                          0x80
#define HWIO_QAD0_QIDR0_CLIENT_MSI_WDATA_GEN_EN_SHFT                           0x7
#define HWIO_QAD0_QIDR0_QSMMU_NATIVE_MSI_EN_BMSK                              0x40
#define HWIO_QAD0_QIDR0_QSMMU_NATIVE_MSI_EN_SHFT                               0x6
#define HWIO_QAD0_QIDR0_PCIE_FUNC_EN_BMSK                                     0x20
#define HWIO_QAD0_QIDR0_PCIE_FUNC_EN_SHFT                                      0x5
#define HWIO_QAD0_QIDR0_CLNT_INT_EN_BMSK                                      0x10
#define HWIO_QAD0_QIDR0_CLNT_INT_EN_SHFT                                       0x4
#define HWIO_QAD0_QIDR0_SI_INTF_EN_BMSK                                        0x4
#define HWIO_QAD0_QIDR0_SI_INTF_EN_SHFT                                        0x2
#define HWIO_QAD0_QIDR0_DVM_EN_BMSK                                            0x1
#define HWIO_QAD0_QIDR0_DVM_EN_SHFT                                            0x0

#define HWIO_QAD0_QIDR1_ADDR(x)                                         ((x) + 0x00000e04)
#define HWIO_QAD0_QIDR1_PHYS(x)                                         ((x) + 0x00000e04)
#define HWIO_QAD0_QIDR1_RMSK                                              0x3fffff
#define HWIO_QAD0_QIDR1_POR                                             0x0019420f
#define HWIO_QAD0_QIDR1_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR1_ATTR                                                   0x1
#define HWIO_QAD0_QIDR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR1_ADDR(x), HWIO_QAD0_QIDR1_RMSK)
#define HWIO_QAD0_QIDR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR1_ADDR(x), m)
#define HWIO_QAD0_QIDR1_CONFIG_BID_WIDTH_BMSK                             0x380000
#define HWIO_QAD0_QIDR1_CONFIG_BID_WIDTH_SHFT                                 0x13
#define HWIO_QAD0_QIDR1_CONFIG_PID_WIDTH_BMSK                              0x7c000
#define HWIO_QAD0_QIDR1_CONFIG_PID_WIDTH_SHFT                                  0xe
#define HWIO_QAD0_QIDR1_CONFIG_MID_WIDTH_BMSK                               0x3fc0
#define HWIO_QAD0_QIDR1_CONFIG_MID_WIDTH_SHFT                                  0x6
#define HWIO_QAD0_QIDR1_CONFIG_DATA_WIDTH_BMSK                                0x30
#define HWIO_QAD0_QIDR1_CONFIG_DATA_WIDTH_SHFT                                 0x4
#define HWIO_QAD0_QIDR1_VMID_WIDTH_BMSK                                        0xf
#define HWIO_QAD0_QIDR1_VMID_WIDTH_SHFT                                        0x0

#define HWIO_QAD0_QIDR2_ADDR(x)                                         ((x) + 0x00000e08)
#define HWIO_QAD0_QIDR2_PHYS(x)                                         ((x) + 0x00000e08)
#define HWIO_QAD0_QIDR2_RMSK                                                  0xff
#define HWIO_QAD0_QIDR2_POR                                             0x00000021
#define HWIO_QAD0_QIDR2_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR2_ATTR                                                   0x1
#define HWIO_QAD0_QIDR2_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR2_ADDR(x), HWIO_QAD0_QIDR2_RMSK)
#define HWIO_QAD0_QIDR2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR2_ADDR(x), m)
#define HWIO_QAD0_QIDR2_MAJOR_BMSK                                            0xf0
#define HWIO_QAD0_QIDR2_MAJOR_SHFT                                             0x4
#define HWIO_QAD0_QIDR2_MINOR_BMSK                                             0xf
#define HWIO_QAD0_QIDR2_MINOR_SHFT                                             0x0

#define HWIO_QAD0_QIDR3_ADDR(x)                                         ((x) + 0x00000e0c)
#define HWIO_QAD0_QIDR3_PHYS(x)                                         ((x) + 0x00000e0c)
#define HWIO_QAD0_QIDR3_RMSK                                                  0x3f
#define HWIO_QAD0_QIDR3_POR                                             0x00000020
#define HWIO_QAD0_QIDR3_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR3_ATTR                                                   0x1
#define HWIO_QAD0_QIDR3_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR3_ADDR(x), HWIO_QAD0_QIDR3_RMSK)
#define HWIO_QAD0_QIDR3_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR3_ADDR(x), m)
#define HWIO_QAD0_QIDR3_MSIDEVICEID_WIDTH_BMSK                                0x3f
#define HWIO_QAD0_QIDR3_MSIDEVICEID_WIDTH_SHFT                                 0x0

#define HWIO_QAD0_QIDR4_ADDR(x)                                         ((x) + 0x00000e10)
#define HWIO_QAD0_QIDR4_PHYS(x)                                         ((x) + 0x00000e10)
#define HWIO_QAD0_QIDR4_RMSK                                             0xfffffff
#define HWIO_QAD0_QIDR4_POR                                             0x0357683f
#define HWIO_QAD0_QIDR4_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR4_ATTR                                                   0x1
#define HWIO_QAD0_QIDR4_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR4_ADDR(x), HWIO_QAD0_QIDR4_RMSK)
#define HWIO_QAD0_QIDR4_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR4_ADDR(x), m)
#define HWIO_QAD0_QIDR4_CLIENT_BID_WIDTH_BMSK                            0xf000000
#define HWIO_QAD0_QIDR4_CLIENT_BID_WIDTH_SHFT                                 0x18
#define HWIO_QAD0_QIDR4_CLIENT_PID_WIDTH_BMSK                             0xf00000
#define HWIO_QAD0_QIDR4_CLIENT_PID_WIDTH_SHFT                                 0x14
#define HWIO_QAD0_QIDR4_CLIENT_MID_WIDTH_BMSK                              0xf0000
#define HWIO_QAD0_QIDR4_CLIENT_MID_WIDTH_SHFT                                 0x10
#define HWIO_QAD0_QIDR4_CLIENT_TID_WIDTH_BMSK                               0xf000
#define HWIO_QAD0_QIDR4_CLIENT_TID_WIDTH_SHFT                                  0xc
#define HWIO_QAD0_QIDR4_CLIENT_BURST_LNGTH_BMSK                              0xfc0
#define HWIO_QAD0_QIDR4_CLIENT_BURST_LNGTH_SHFT                                0x6
#define HWIO_QAD0_QIDR4_CLIENT_DATA_WIDTH_BMSK                                0x30
#define HWIO_QAD0_QIDR4_CLIENT_DATA_WIDTH_SHFT                                 0x4
#define HWIO_QAD0_QIDR4_VMID_WIDTH_BMSK                                        0xf
#define HWIO_QAD0_QIDR4_VMID_WIDTH_SHFT                                        0x0

#define HWIO_QAD0_QIDR5_ADDR(x)                                         ((x) + 0x00000e14)
#define HWIO_QAD0_QIDR5_PHYS(x)                                         ((x) + 0x00000e14)
#define HWIO_QAD0_QIDR5_RMSK                                                 0xfff
#define HWIO_QAD0_QIDR5_POR                                             0x00000686
#define HWIO_QAD0_QIDR5_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR5_ATTR                                                   0x1
#define HWIO_QAD0_QIDR5_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR5_ADDR(x), HWIO_QAD0_QIDR5_RMSK)
#define HWIO_QAD0_QIDR5_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR5_ADDR(x), m)
#define HWIO_QAD0_QIDR5_CLIENT_HIT_MISS_TAGID_WIDTH_BMSK                     0xf00
#define HWIO_QAD0_QIDR5_CLIENT_HIT_MISS_TAGID_WIDTH_SHFT                       0x8
#define HWIO_QAD0_QIDR5_CLIENT_OUTPUT_MID_WIDTH_BMSK                          0xf0
#define HWIO_QAD0_QIDR5_CLIENT_OUTPUT_MID_WIDTH_SHFT                           0x4
#define HWIO_QAD0_QIDR5_CLIENT_OUTPUT_TID_WIDTH_BMSK                           0xf
#define HWIO_QAD0_QIDR5_CLIENT_OUTPUT_TID_WIDTH_SHFT                           0x0

#define HWIO_QAD0_QIDR6_ADDR(x)                                         ((x) + 0x00000e18)
#define HWIO_QAD0_QIDR6_PHYS(x)                                         ((x) + 0x00000e18)
#define HWIO_QAD0_QIDR6_RMSK                                                 0xf7f
#define HWIO_QAD0_QIDR6_POR                                             0x00000409
#define HWIO_QAD0_QIDR6_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR6_ATTR                                                   0x1
#define HWIO_QAD0_QIDR6_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR6_ADDR(x), HWIO_QAD0_QIDR6_RMSK)
#define HWIO_QAD0_QIDR6_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR6_ADDR(x), m)
#define HWIO_QAD0_QIDR6_TOTAL_WDATA_RAM_SIZE_BMSK                            0xf00
#define HWIO_QAD0_QIDR6_TOTAL_WDATA_RAM_SIZE_SHFT                              0x8
#define HWIO_QAD0_QIDR6_PERF_NUM_BMSK                                         0x7f
#define HWIO_QAD0_QIDR6_PERF_NUM_SHFT                                          0x0

#define HWIO_QAD0_QIDR7_ADDR(x)                                         ((x) + 0x00000e1c)
#define HWIO_QAD0_QIDR7_PHYS(x)                                         ((x) + 0x00000e1c)
#define HWIO_QAD0_QIDR7_RMSK                                             0x7e0ffff
#define HWIO_QAD0_QIDR7_POR                                             0x01007bc8
#define HWIO_QAD0_QIDR7_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR7_ATTR                                                   0x1
#define HWIO_QAD0_QIDR7_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR7_ADDR(x), HWIO_QAD0_QIDR7_RMSK)
#define HWIO_QAD0_QIDR7_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR7_ADDR(x), m)
#define HWIO_QAD0_QIDR7_NUM_HANDLER_SLOTS_BMSK                           0x7e00000
#define HWIO_QAD0_QIDR7_NUM_HANDLER_SLOTS_SHFT                                0x15
#define HWIO_QAD0_QIDR7_NUM_OUTSTANDING_WRITES_BMSK                         0xf800
#define HWIO_QAD0_QIDR7_NUM_OUTSTANDING_WRITES_SHFT                            0xb
#define HWIO_QAD0_QIDR7_NUM_OUTSTANDING_READS_BMSK                           0x7c0
#define HWIO_QAD0_QIDR7_NUM_OUTSTANDING_READS_SHFT                             0x6
#define HWIO_QAD0_QIDR7_NUM_HTW_BMSK                                          0x3f
#define HWIO_QAD0_QIDR7_NUM_HTW_SHFT                                           0x0

#define HWIO_QAD0_QIDR8_ADDR(x)                                         ((x) + 0x00000e20)
#define HWIO_QAD0_QIDR8_PHYS(x)                                         ((x) + 0x00000e20)
#define HWIO_QAD0_QIDR8_RMSK                                            0xffffffff
#define HWIO_QAD0_QIDR8_POR                                             0x02000008
#define HWIO_QAD0_QIDR8_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR8_ATTR                                                   0x1
#define HWIO_QAD0_QIDR8_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR8_ADDR(x), HWIO_QAD0_QIDR8_RMSK)
#define HWIO_QAD0_QIDR8_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR8_ADDR(x), m)
#define HWIO_QAD0_QIDR8_NUM_TLB_ENTRIES_BMSK                            0xffff0000
#define HWIO_QAD0_QIDR8_NUM_TLB_ENTRIES_SHFT                                  0x10
#define HWIO_QAD0_QIDR8_MAX_NUM_TLB_PARTITIONS_BMSK                         0xffff
#define HWIO_QAD0_QIDR8_MAX_NUM_TLB_PARTITIONS_SHFT                            0x0

#define HWIO_QAD0_QIDR9_ADDR(x)                                         ((x) + 0x00000e24)
#define HWIO_QAD0_QIDR9_PHYS(x)                                         ((x) + 0x00000e24)
#define HWIO_QAD0_QIDR9_RMSK                                             0xfffffff
#define HWIO_QAD0_QIDR9_POR                                             0x0c040503
#define HWIO_QAD0_QIDR9_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_QIDR9_ATTR                                                   0x1
#define HWIO_QAD0_QIDR9_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR9_ADDR(x), HWIO_QAD0_QIDR9_RMSK)
#define HWIO_QAD0_QIDR9_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR9_ADDR(x), m)
#define HWIO_QAD0_QIDR9_TLB_LRU_EN_BMSK                                  0x8000000
#define HWIO_QAD0_QIDR9_TLB_LRU_EN_SHFT                                       0x1b
#define HWIO_QAD0_QIDR9_TLB_MODE_TABLE_WIDTH_BMSK                        0x7000000
#define HWIO_QAD0_QIDR9_TLB_MODE_TABLE_WIDTH_SHFT                             0x18
#define HWIO_QAD0_QIDR9_TLB_MODE_TABLE_DEPTH_BMSK                         0xff0000
#define HWIO_QAD0_QIDR9_TLB_MODE_TABLE_DEPTH_SHFT                             0x10
#define HWIO_QAD0_QIDR9_TLB_LAYOUT_TYPE_BMSK                                0xff00
#define HWIO_QAD0_QIDR9_TLB_LAYOUT_TYPE_SHFT                                   0x8
#define HWIO_QAD0_QIDR9_TLB_PARTITION_INDEX_WIDTH_BMSK                        0xff
#define HWIO_QAD0_QIDR9_TLB_PARTITION_INDEX_WIDTH_SHFT                         0x0

#define HWIO_QAD0_QIDR10_ADDR(x)                                        ((x) + 0x00000e28)
#define HWIO_QAD0_QIDR10_PHYS(x)                                        ((x) + 0x00000e28)
#define HWIO_QAD0_QIDR10_RMSK                                              0x1ffff
#define HWIO_QAD0_QIDR10_POR                                            0x00013030
#define HWIO_QAD0_QIDR10_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_QIDR10_ATTR                                                  0x1
#define HWIO_QAD0_QIDR10_IN(x)      \
        in_dword_masked(HWIO_QAD0_QIDR10_ADDR(x), HWIO_QAD0_QIDR10_RMSK)
#define HWIO_QAD0_QIDR10_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QIDR10_ADDR(x), m)
#define HWIO_QAD0_QIDR10_CONFIG_CACHE_LRU_EN_BMSK                          0x10000
#define HWIO_QAD0_QIDR10_CONFIG_CACHE_LRU_EN_SHFT                             0x10
#define HWIO_QAD0_QIDR10_CONFIG_CACHE_ENTRIES_BMSK                          0xff00
#define HWIO_QAD0_QIDR10_CONFIG_CACHE_ENTRIES_SHFT                             0x8
#define HWIO_QAD0_QIDR10_RESIDENT_CONTEXT_BANKS_BMSK                          0xff
#define HWIO_QAD0_QIDR10_RESIDENT_CONTEXT_BANKS_SHFT                           0x0

#define HWIO_QAD0_PIDR4_ADDR(x)                                         ((x) + 0x00000fd0)
#define HWIO_QAD0_PIDR4_PHYS(x)                                         ((x) + 0x00000fd0)
#define HWIO_QAD0_PIDR4_RMSK                                                  0xff
#define HWIO_QAD0_PIDR4_POR                                             0x00000000
#define HWIO_QAD0_PIDR4_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_PIDR4_ATTR                                                   0x1
#define HWIO_QAD0_PIDR4_IN(x)      \
        in_dword_masked(HWIO_QAD0_PIDR4_ADDR(x), HWIO_QAD0_PIDR4_RMSK)
#define HWIO_QAD0_PIDR4_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PIDR4_ADDR(x), m)
#define HWIO_QAD0_PIDR4_SIZE_BMSK                                             0xf0
#define HWIO_QAD0_PIDR4_SIZE_SHFT                                              0x4
#define HWIO_QAD0_PIDR4_DES_2_BMSK                                             0xf
#define HWIO_QAD0_PIDR4_DES_2_SHFT                                             0x0

#define HWIO_QAD0_PIDR5_ADDR(x)                                         ((x) + 0x00000fd4)
#define HWIO_QAD0_PIDR5_PHYS(x)                                         ((x) + 0x00000fd4)
#define HWIO_QAD0_PIDR5_RMSK                                            0xffffffff
#define HWIO_QAD0_PIDR5_POR                                             0x00000000
#define HWIO_QAD0_PIDR5_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_PIDR5_ATTR                                                   0x1
#define HWIO_QAD0_PIDR5_IN(x)      \
        in_dword_masked(HWIO_QAD0_PIDR5_ADDR(x), HWIO_QAD0_PIDR5_RMSK)
#define HWIO_QAD0_PIDR5_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PIDR5_ADDR(x), m)
#define HWIO_QAD0_PIDR5_RSRVED_31_0_BMSK                                0xffffffff
#define HWIO_QAD0_PIDR5_RSRVED_31_0_SHFT                                       0x0

#define HWIO_QAD0_PIDR6_ADDR(x)                                         ((x) + 0x00000fd8)
#define HWIO_QAD0_PIDR6_PHYS(x)                                         ((x) + 0x00000fd8)
#define HWIO_QAD0_PIDR6_RMSK                                            0xffffffff
#define HWIO_QAD0_PIDR6_POR                                             0x00000000
#define HWIO_QAD0_PIDR6_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_PIDR6_ATTR                                                   0x1
#define HWIO_QAD0_PIDR6_IN(x)      \
        in_dword_masked(HWIO_QAD0_PIDR6_ADDR(x), HWIO_QAD0_PIDR6_RMSK)
#define HWIO_QAD0_PIDR6_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PIDR6_ADDR(x), m)
#define HWIO_QAD0_PIDR6_RSRVED_31_0_BMSK                                0xffffffff
#define HWIO_QAD0_PIDR6_RSRVED_31_0_SHFT                                       0x0

#define HWIO_QAD0_PIDR7_ADDR(x)                                         ((x) + 0x00000fdc)
#define HWIO_QAD0_PIDR7_PHYS(x)                                         ((x) + 0x00000fdc)
#define HWIO_QAD0_PIDR7_RMSK                                            0xffffffff
#define HWIO_QAD0_PIDR7_POR                                             0x00000000
#define HWIO_QAD0_PIDR7_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_PIDR7_ATTR                                                   0x1
#define HWIO_QAD0_PIDR7_IN(x)      \
        in_dword_masked(HWIO_QAD0_PIDR7_ADDR(x), HWIO_QAD0_PIDR7_RMSK)
#define HWIO_QAD0_PIDR7_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PIDR7_ADDR(x), m)
#define HWIO_QAD0_PIDR7_RSRVED_31_0_BMSK                                0xffffffff
#define HWIO_QAD0_PIDR7_RSRVED_31_0_SHFT                                       0x0

#define HWIO_QAD0_PIDR0_ADDR(x)                                         ((x) + 0x00000fe0)
#define HWIO_QAD0_PIDR0_PHYS(x)                                         ((x) + 0x00000fe0)
#define HWIO_QAD0_PIDR0_RMSK                                                  0xff
#define HWIO_QAD0_PIDR0_POR                                             0x00000040
#define HWIO_QAD0_PIDR0_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_PIDR0_ATTR                                                   0x1
#define HWIO_QAD0_PIDR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_PIDR0_ADDR(x), HWIO_QAD0_PIDR0_RMSK)
#define HWIO_QAD0_PIDR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PIDR0_ADDR(x), m)
#define HWIO_QAD0_PIDR0_PART_0_BMSK                                           0xff
#define HWIO_QAD0_PIDR0_PART_0_SHFT                                            0x0

#define HWIO_QAD0_PIDR1_ADDR(x)                                         ((x) + 0x00000fe4)
#define HWIO_QAD0_PIDR1_PHYS(x)                                         ((x) + 0x00000fe4)
#define HWIO_QAD0_PIDR1_RMSK                                                  0xff
#define HWIO_QAD0_PIDR1_POR                                             0x00000000
#define HWIO_QAD0_PIDR1_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_PIDR1_ATTR                                                   0x1
#define HWIO_QAD0_PIDR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_PIDR1_ADDR(x), HWIO_QAD0_PIDR1_RMSK)
#define HWIO_QAD0_PIDR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PIDR1_ADDR(x), m)
#define HWIO_QAD0_PIDR1_DES_0_BMSK                                            0xf0
#define HWIO_QAD0_PIDR1_DES_0_SHFT                                             0x4
#define HWIO_QAD0_PIDR1_PART_1_BMSK                                            0xf
#define HWIO_QAD0_PIDR1_PART_1_SHFT                                            0x0

#define HWIO_QAD0_PIDR2_ADDR(x)                                         ((x) + 0x00000fe8)
#define HWIO_QAD0_PIDR2_PHYS(x)                                         ((x) + 0x00000fe8)
#define HWIO_QAD0_PIDR2_RMSK                                                  0xff
#define HWIO_QAD0_PIDR2_POR                                             0x0000003f
#define HWIO_QAD0_PIDR2_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_PIDR2_ATTR                                                   0x1
#define HWIO_QAD0_PIDR2_IN(x)      \
        in_dword_masked(HWIO_QAD0_PIDR2_ADDR(x), HWIO_QAD0_PIDR2_RMSK)
#define HWIO_QAD0_PIDR2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PIDR2_ADDR(x), m)
#define HWIO_QAD0_PIDR2_REVISION_BMSK                                         0xf0
#define HWIO_QAD0_PIDR2_REVISION_SHFT                                          0x4
#define HWIO_QAD0_PIDR2_JEDEC_VAL_BMSK                                         0x8
#define HWIO_QAD0_PIDR2_JEDEC_VAL_SHFT                                         0x3
#define HWIO_QAD0_PIDR2_DES_1_BMSK                                             0x7
#define HWIO_QAD0_PIDR2_DES_1_SHFT                                             0x0

#define HWIO_QAD0_PIDR3_ADDR(x)                                         ((x) + 0x00000fec)
#define HWIO_QAD0_PIDR3_PHYS(x)                                         ((x) + 0x00000fec)
#define HWIO_QAD0_PIDR3_RMSK                                                  0xff
#define HWIO_QAD0_PIDR3_POR                                             0x00000000
#define HWIO_QAD0_PIDR3_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_PIDR3_ATTR                                                   0x1
#define HWIO_QAD0_PIDR3_IN(x)      \
        in_dword_masked(HWIO_QAD0_PIDR3_ADDR(x), HWIO_QAD0_PIDR3_RMSK)
#define HWIO_QAD0_PIDR3_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PIDR3_ADDR(x), m)
#define HWIO_QAD0_PIDR3_REVAND_BMSK                                           0xf0
#define HWIO_QAD0_PIDR3_REVAND_SHFT                                            0x4
#define HWIO_QAD0_PIDR3_CMOD_BMSK                                              0xf
#define HWIO_QAD0_PIDR3_CMOD_SHFT                                              0x0

#define HWIO_QAD0_CIDR0_ADDR(x)                                         ((x) + 0x00000ff0)
#define HWIO_QAD0_CIDR0_PHYS(x)                                         ((x) + 0x00000ff0)
#define HWIO_QAD0_CIDR0_RMSK                                                  0xff
#define HWIO_QAD0_CIDR0_POR                                             0x0000000d
#define HWIO_QAD0_CIDR0_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_CIDR0_ATTR                                                   0x1
#define HWIO_QAD0_CIDR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_CIDR0_ADDR(x), HWIO_QAD0_CIDR0_RMSK)
#define HWIO_QAD0_CIDR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CIDR0_ADDR(x), m)
#define HWIO_QAD0_CIDR0_COMPONENT_IDR0_BMSK                                   0xff
#define HWIO_QAD0_CIDR0_COMPONENT_IDR0_SHFT                                    0x0

#define HWIO_QAD0_CIDR1_ADDR(x)                                         ((x) + 0x00000ff4)
#define HWIO_QAD0_CIDR1_PHYS(x)                                         ((x) + 0x00000ff4)
#define HWIO_QAD0_CIDR1_RMSK                                                  0xff
#define HWIO_QAD0_CIDR1_POR                                             0x000000f0
#define HWIO_QAD0_CIDR1_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_CIDR1_ATTR                                                   0x1
#define HWIO_QAD0_CIDR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_CIDR1_ADDR(x), HWIO_QAD0_CIDR1_RMSK)
#define HWIO_QAD0_CIDR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CIDR1_ADDR(x), m)
#define HWIO_QAD0_CIDR1_COMPONENT_IDR1_BMSK                                   0xff
#define HWIO_QAD0_CIDR1_COMPONENT_IDR1_SHFT                                    0x0

#define HWIO_QAD0_CIDR2_ADDR(x)                                         ((x) + 0x00000ff8)
#define HWIO_QAD0_CIDR2_PHYS(x)                                         ((x) + 0x00000ff8)
#define HWIO_QAD0_CIDR2_RMSK                                                  0xff
#define HWIO_QAD0_CIDR2_POR                                             0x00000005
#define HWIO_QAD0_CIDR2_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_CIDR2_ATTR                                                   0x1
#define HWIO_QAD0_CIDR2_IN(x)      \
        in_dword_masked(HWIO_QAD0_CIDR2_ADDR(x), HWIO_QAD0_CIDR2_RMSK)
#define HWIO_QAD0_CIDR2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CIDR2_ADDR(x), m)
#define HWIO_QAD0_CIDR2_COMPONENT_IDR2_BMSK                                   0xff
#define HWIO_QAD0_CIDR2_COMPONENT_IDR2_SHFT                                    0x0

#define HWIO_QAD0_CIDR3_ADDR(x)                                         ((x) + 0x00000ffc)
#define HWIO_QAD0_CIDR3_PHYS(x)                                         ((x) + 0x00000ffc)
#define HWIO_QAD0_CIDR3_RMSK                                                  0xff
#define HWIO_QAD0_CIDR3_POR                                             0x000000b1
#define HWIO_QAD0_CIDR3_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_CIDR3_ATTR                                                   0x1
#define HWIO_QAD0_CIDR3_IN(x)      \
        in_dword_masked(HWIO_QAD0_CIDR3_ADDR(x), HWIO_QAD0_CIDR3_RMSK)
#define HWIO_QAD0_CIDR3_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_CIDR3_ADDR(x), m)
#define HWIO_QAD0_CIDR3_COMPONENT_IDR3_BMSK                                   0xff
#define HWIO_QAD0_CIDR3_COMPONENT_IDR3_SHFT                                    0x0

#define HWIO_QAD0_QCR0_ADDR(x)                                          ((x) + 0x00001000)
#define HWIO_QAD0_QCR0_PHYS(x)                                          ((x) + 0x00001000)
#define HWIO_QAD0_QCR0_RMSK                                                   0x1a
#define HWIO_QAD0_QCR0_POR                                              0x00000012
#define HWIO_QAD0_QCR0_POR_RMSK                                         0xffffffff
#define HWIO_QAD0_QCR0_ATTR                                                    0x3
#define HWIO_QAD0_QCR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_QCR0_ADDR(x), HWIO_QAD0_QCR0_RMSK)
#define HWIO_QAD0_QCR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QCR0_ADDR(x), m)
#define HWIO_QAD0_QCR0_OUT(x, v)      \
        out_dword(HWIO_QAD0_QCR0_ADDR(x),v)
#define HWIO_QAD0_QCR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QCR0_ADDR(x),m,v,HWIO_QAD0_QCR0_IN(x))
#define HWIO_QAD0_QCR0_CMDQ_SYNC_RESP_TRK_DIS_BMSK                            0x10
#define HWIO_QAD0_QCR0_CMDQ_SYNC_RESP_TRK_DIS_SHFT                             0x4
#define HWIO_QAD0_QCR0_STALL_ON_CMDQ_SYNC_BMSK                                 0x8
#define HWIO_QAD0_QCR0_STALL_ON_CMDQ_SYNC_SHFT                                 0x3
#define HWIO_QAD0_QCR0_AHB_ERROR_REPORT_EN_BMSK                                0x2
#define HWIO_QAD0_QCR0_AHB_ERROR_REPORT_EN_SHFT                                0x1

#define HWIO_QAD0_QTABLE_ACR1_ADDR(x)                                   ((x) + 0x00001020)
#define HWIO_QAD0_QTABLE_ACR1_PHYS(x)                                   ((x) + 0x00001020)
#define HWIO_QAD0_QTABLE_ACR1_RMSK                                             0x7
#define HWIO_QAD0_QTABLE_ACR1_POR                                       0x00000000
#define HWIO_QAD0_QTABLE_ACR1_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_QTABLE_ACR1_ATTR                                             0x3
#define HWIO_QAD0_QTABLE_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_QTABLE_ACR1_ADDR(x), HWIO_QAD0_QTABLE_ACR1_RMSK)
#define HWIO_QAD0_QTABLE_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QTABLE_ACR1_ADDR(x), m)
#define HWIO_QAD0_QTABLE_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_QTABLE_ACR1_ADDR(x),v)
#define HWIO_QAD0_QTABLE_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QTABLE_ACR1_ADDR(x),m,v,HWIO_QAD0_QTABLE_ACR1_IN(x))
#define HWIO_QAD0_QTABLE_ACR1_TRCFG_BMSK                                       0x4
#define HWIO_QAD0_QTABLE_ACR1_TRCFG_SHFT                                       0x2
#define HWIO_QAD0_QTABLE_ACR1_REQPRIORITY_BMSK                                 0x3
#define HWIO_QAD0_QTABLE_ACR1_REQPRIORITY_SHFT                                 0x0

#define HWIO_QAD0_QQUEUE_ACR1_ADDR(x)                                   ((x) + 0x00001024)
#define HWIO_QAD0_QQUEUE_ACR1_PHYS(x)                                   ((x) + 0x00001024)
#define HWIO_QAD0_QQUEUE_ACR1_RMSK                                             0x7
#define HWIO_QAD0_QQUEUE_ACR1_POR                                       0x00000000
#define HWIO_QAD0_QQUEUE_ACR1_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_QQUEUE_ACR1_ATTR                                             0x3
#define HWIO_QAD0_QQUEUE_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_QQUEUE_ACR1_ADDR(x), HWIO_QAD0_QQUEUE_ACR1_RMSK)
#define HWIO_QAD0_QQUEUE_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QQUEUE_ACR1_ADDR(x), m)
#define HWIO_QAD0_QQUEUE_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_QQUEUE_ACR1_ADDR(x),v)
#define HWIO_QAD0_QQUEUE_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QQUEUE_ACR1_ADDR(x),m,v,HWIO_QAD0_QQUEUE_ACR1_IN(x))
#define HWIO_QAD0_QQUEUE_ACR1_TRCFG_BMSK                                       0x4
#define HWIO_QAD0_QQUEUE_ACR1_TRCFG_SHFT                                       0x2
#define HWIO_QAD0_QQUEUE_ACR1_REQPRIORITY_BMSK                                 0x3
#define HWIO_QAD0_QQUEUE_ACR1_REQPRIORITY_SHFT                                 0x0

#define HWIO_QAD0_QGERROR_MSI_ACR1_ADDR(x)                              ((x) + 0x00001028)
#define HWIO_QAD0_QGERROR_MSI_ACR1_PHYS(x)                              ((x) + 0x00001028)
#define HWIO_QAD0_QGERROR_MSI_ACR1_RMSK                                        0xf
#define HWIO_QAD0_QGERROR_MSI_ACR1_POR                                  0x00000000
#define HWIO_QAD0_QGERROR_MSI_ACR1_POR_RMSK                             0xffffffff
#define HWIO_QAD0_QGERROR_MSI_ACR1_ATTR                                        0x3
#define HWIO_QAD0_QGERROR_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_QGERROR_MSI_ACR1_ADDR(x), HWIO_QAD0_QGERROR_MSI_ACR1_RMSK)
#define HWIO_QAD0_QGERROR_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QGERROR_MSI_ACR1_ADDR(x), m)
#define HWIO_QAD0_QGERROR_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_QGERROR_MSI_ACR1_ADDR(x),v)
#define HWIO_QAD0_QGERROR_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QGERROR_MSI_ACR1_ADDR(x),m,v,HWIO_QAD0_QGERROR_MSI_ACR1_IN(x))
#define HWIO_QAD0_QGERROR_MSI_ACR1_WA_BMSK                                     0x8
#define HWIO_QAD0_QGERROR_MSI_ACR1_WA_SHFT                                     0x3
#define HWIO_QAD0_QGERROR_MSI_ACR1_TRCFG_BMSK                                  0x4
#define HWIO_QAD0_QGERROR_MSI_ACR1_TRCFG_SHFT                                  0x2
#define HWIO_QAD0_QGERROR_MSI_ACR1_REQPRIORITY_BMSK                            0x3
#define HWIO_QAD0_QGERROR_MSI_ACR1_REQPRIORITY_SHFT                            0x0

#define HWIO_QAD0_QCMDQ_MSI_ACR1_ADDR(x)                                ((x) + 0x0000102c)
#define HWIO_QAD0_QCMDQ_MSI_ACR1_PHYS(x)                                ((x) + 0x0000102c)
#define HWIO_QAD0_QCMDQ_MSI_ACR1_RMSK                                          0xf
#define HWIO_QAD0_QCMDQ_MSI_ACR1_POR                                    0x00000000
#define HWIO_QAD0_QCMDQ_MSI_ACR1_POR_RMSK                               0xffffffff
#define HWIO_QAD0_QCMDQ_MSI_ACR1_ATTR                                          0x3
#define HWIO_QAD0_QCMDQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_QCMDQ_MSI_ACR1_ADDR(x), HWIO_QAD0_QCMDQ_MSI_ACR1_RMSK)
#define HWIO_QAD0_QCMDQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QCMDQ_MSI_ACR1_ADDR(x), m)
#define HWIO_QAD0_QCMDQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_QCMDQ_MSI_ACR1_ADDR(x),v)
#define HWIO_QAD0_QCMDQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QCMDQ_MSI_ACR1_ADDR(x),m,v,HWIO_QAD0_QCMDQ_MSI_ACR1_IN(x))
#define HWIO_QAD0_QCMDQ_MSI_ACR1_WA_BMSK                                       0x8
#define HWIO_QAD0_QCMDQ_MSI_ACR1_WA_SHFT                                       0x3
#define HWIO_QAD0_QCMDQ_MSI_ACR1_TRCFG_BMSK                                    0x4
#define HWIO_QAD0_QCMDQ_MSI_ACR1_TRCFG_SHFT                                    0x2
#define HWIO_QAD0_QCMDQ_MSI_ACR1_REQPRIORITY_BMSK                              0x3
#define HWIO_QAD0_QCMDQ_MSI_ACR1_REQPRIORITY_SHFT                              0x0

#define HWIO_QAD0_QEVENTQ_MSI_ACR1_ADDR(x)                              ((x) + 0x00001030)
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_PHYS(x)                              ((x) + 0x00001030)
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_RMSK                                        0xf
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_POR                                  0x00000000
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_POR_RMSK                             0xffffffff
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_ATTR                                        0x3
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_QEVENTQ_MSI_ACR1_ADDR(x), HWIO_QAD0_QEVENTQ_MSI_ACR1_RMSK)
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QEVENTQ_MSI_ACR1_ADDR(x), m)
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_QEVENTQ_MSI_ACR1_ADDR(x),v)
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QEVENTQ_MSI_ACR1_ADDR(x),m,v,HWIO_QAD0_QEVENTQ_MSI_ACR1_IN(x))
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_WA_BMSK                                     0x8
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_WA_SHFT                                     0x3
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_TRCFG_BMSK                                  0x4
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_TRCFG_SHFT                                  0x2
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_REQPRIORITY_BMSK                            0x3
#define HWIO_QAD0_QEVENTQ_MSI_ACR1_REQPRIORITY_SHFT                            0x0

#define HWIO_QAD0_QPRIQ_MSI_ACR1_ADDR(x)                                ((x) + 0x00001034)
#define HWIO_QAD0_QPRIQ_MSI_ACR1_PHYS(x)                                ((x) + 0x00001034)
#define HWIO_QAD0_QPRIQ_MSI_ACR1_RMSK                                          0xf
#define HWIO_QAD0_QPRIQ_MSI_ACR1_POR                                    0x00000000
#define HWIO_QAD0_QPRIQ_MSI_ACR1_POR_RMSK                               0xffffffff
#define HWIO_QAD0_QPRIQ_MSI_ACR1_ATTR                                          0x3
#define HWIO_QAD0_QPRIQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_QPRIQ_MSI_ACR1_ADDR(x), HWIO_QAD0_QPRIQ_MSI_ACR1_RMSK)
#define HWIO_QAD0_QPRIQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QPRIQ_MSI_ACR1_ADDR(x), m)
#define HWIO_QAD0_QPRIQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_QPRIQ_MSI_ACR1_ADDR(x),v)
#define HWIO_QAD0_QPRIQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QPRIQ_MSI_ACR1_ADDR(x),m,v,HWIO_QAD0_QPRIQ_MSI_ACR1_IN(x))
#define HWIO_QAD0_QPRIQ_MSI_ACR1_WA_BMSK                                       0x8
#define HWIO_QAD0_QPRIQ_MSI_ACR1_WA_SHFT                                       0x3
#define HWIO_QAD0_QPRIQ_MSI_ACR1_TRCFG_BMSK                                    0x4
#define HWIO_QAD0_QPRIQ_MSI_ACR1_TRCFG_SHFT                                    0x2
#define HWIO_QAD0_QPRIQ_MSI_ACR1_REQPRIORITY_BMSK                              0x3
#define HWIO_QAD0_QPRIQ_MSI_ACR1_REQPRIORITY_SHFT                              0x0

#define HWIO_QAD0_QPMCG_MSI_ACR1_ADDR(x)                                ((x) + 0x00001038)
#define HWIO_QAD0_QPMCG_MSI_ACR1_PHYS(x)                                ((x) + 0x00001038)
#define HWIO_QAD0_QPMCG_MSI_ACR1_RMSK                                          0xf
#define HWIO_QAD0_QPMCG_MSI_ACR1_POR                                    0x00000000
#define HWIO_QAD0_QPMCG_MSI_ACR1_POR_RMSK                               0xffffffff
#define HWIO_QAD0_QPMCG_MSI_ACR1_ATTR                                          0x3
#define HWIO_QAD0_QPMCG_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_QPMCG_MSI_ACR1_ADDR(x), HWIO_QAD0_QPMCG_MSI_ACR1_RMSK)
#define HWIO_QAD0_QPMCG_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QPMCG_MSI_ACR1_ADDR(x), m)
#define HWIO_QAD0_QPMCG_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_QPMCG_MSI_ACR1_ADDR(x),v)
#define HWIO_QAD0_QPMCG_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QPMCG_MSI_ACR1_ADDR(x),m,v,HWIO_QAD0_QPMCG_MSI_ACR1_IN(x))
#define HWIO_QAD0_QPMCG_MSI_ACR1_WA_BMSK                                       0x8
#define HWIO_QAD0_QPMCG_MSI_ACR1_WA_SHFT                                       0x3
#define HWIO_QAD0_QPMCG_MSI_ACR1_TRCFG_BMSK                                    0x4
#define HWIO_QAD0_QPMCG_MSI_ACR1_TRCFG_SHFT                                    0x2
#define HWIO_QAD0_QPMCG_MSI_ACR1_REQPRIORITY_BMSK                              0x3
#define HWIO_QAD0_QPMCG_MSI_ACR1_REQPRIORITY_SHFT                              0x0

#define HWIO_QAD0_QGERROR_ADDR(x)                                       ((x) + 0x0000103c)
#define HWIO_QAD0_QGERROR_PHYS(x)                                       ((x) + 0x0000103c)
#define HWIO_QAD0_QGERROR_RMSK                                          0xfffff803
#define HWIO_QAD0_QGERROR_POR                                           0x00000000
#define HWIO_QAD0_QGERROR_POR_RMSK                                      0xffffffff
#define HWIO_QAD0_QGERROR_ATTR                                                 0x1
#define HWIO_QAD0_QGERROR_IN(x)      \
        in_dword_masked(HWIO_QAD0_QGERROR_ADDR(x), HWIO_QAD0_QGERROR_RMSK)
#define HWIO_QAD0_QGERROR_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QGERROR_ADDR(x), m)
#define HWIO_QAD0_QGERROR_SYNDROME_CFG_BMSK                             0xffffe000
#define HWIO_QAD0_QGERROR_SYNDROME_CFG_SHFT                                    0xd
#define HWIO_QAD0_QGERROR_SYNDROME_PMCG_BMSK                                0x1800
#define HWIO_QAD0_QGERROR_SYNDROME_PMCG_SHFT                                   0xb
#define HWIO_QAD0_QGERROR_MSI_PMCG_ABT_ERR_BMSK                                0x2
#define HWIO_QAD0_QGERROR_MSI_PMCG_ABT_ERR_SHFT                                0x1
#define HWIO_QAD0_QGERROR_CFG_FAULT_BMSK                                       0x1
#define HWIO_QAD0_QGERROR_CFG_FAULT_SHFT                                       0x0

#define HWIO_QAD0_QGERROR_RST_ADDR(x)                                   ((x) + 0x00001040)
#define HWIO_QAD0_QGERROR_RST_PHYS(x)                                   ((x) + 0x00001040)
#define HWIO_QAD0_QGERROR_RST_RMSK                                             0x3
#define HWIO_QAD0_QGERROR_RST_POR                                       0x00000000
#define HWIO_QAD0_QGERROR_RST_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_QGERROR_RST_ATTR                                             0x2
#define HWIO_QAD0_QGERROR_RST_OUT(x, v)      \
        out_dword(HWIO_QAD0_QGERROR_RST_ADDR(x),v)
#define HWIO_QAD0_QGERROR_RST_MSI_PMCG_ABT_ERR_BMSK                            0x2
#define HWIO_QAD0_QGERROR_RST_MSI_PMCG_ABT_ERR_SHFT                            0x1
#define HWIO_QAD0_QGERROR_RST_CFG_FAULT_BMSK                                   0x1
#define HWIO_QAD0_QGERROR_RST_CFG_FAULT_SHFT                                   0x0

#define HWIO_QAD0_QGITS_GBPA_ADDR(x)                                    ((x) + 0x00001050)
#define HWIO_QAD0_QGITS_GBPA_PHYS(x)                                    ((x) + 0x00001050)
#define HWIO_QAD0_QGITS_GBPA_RMSK                                       0x801f3f1f
#define HWIO_QAD0_QGITS_GBPA_POR                                        0x00002010
#define HWIO_QAD0_QGITS_GBPA_POR_RMSK                                   0xffffffff
#define HWIO_QAD0_QGITS_GBPA_ATTR                                              0x3
#define HWIO_QAD0_QGITS_GBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_QGITS_GBPA_ADDR(x), HWIO_QAD0_QGITS_GBPA_RMSK)
#define HWIO_QAD0_QGITS_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QGITS_GBPA_ADDR(x), m)
#define HWIO_QAD0_QGITS_GBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_QGITS_GBPA_ADDR(x),v)
#define HWIO_QAD0_QGITS_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QGITS_GBPA_ADDR(x),m,v,HWIO_QAD0_QGITS_GBPA_IN(x))
#define HWIO_QAD0_QGITS_GBPA_UPDATE_BMSK                                0x80000000
#define HWIO_QAD0_QGITS_GBPA_UPDATE_SHFT                                      0x1f
#define HWIO_QAD0_QGITS_GBPA_ABORT_BMSK                                   0x100000
#define HWIO_QAD0_QGITS_GBPA_ABORT_SHFT                                       0x14
#define HWIO_QAD0_QGITS_GBPA_INSTCFG_BMSK                                  0xc0000
#define HWIO_QAD0_QGITS_GBPA_INSTCFG_SHFT                                     0x12
#define HWIO_QAD0_QGITS_GBPA_PRIVCFG_BMSK                                  0x30000
#define HWIO_QAD0_QGITS_GBPA_PRIVCFG_SHFT                                     0x10
#define HWIO_QAD0_QGITS_GBPA_SHCFG_BMSK                                     0x3000
#define HWIO_QAD0_QGITS_GBPA_SHCFG_SHFT                                        0xc
#define HWIO_QAD0_QGITS_GBPA_ALLOCCFG_BMSK                                   0xf00
#define HWIO_QAD0_QGITS_GBPA_ALLOCCFG_SHFT                                     0x8
#define HWIO_QAD0_QGITS_GBPA_MTCFG_BMSK                                       0x10
#define HWIO_QAD0_QGITS_GBPA_MTCFG_SHFT                                        0x4
#define HWIO_QAD0_QGITS_GBPA_MEMATTR_BMSK                                      0xf
#define HWIO_QAD0_QGITS_GBPA_MEMATTR_SHFT                                      0x0

#define HWIO_QAD0_QGITS_AGBPA_ADDR(x)                                   ((x) + 0x00001054)
#define HWIO_QAD0_QGITS_AGBPA_PHYS(x)                                   ((x) + 0x00001054)
#define HWIO_QAD0_QGITS_AGBPA_RMSK                                         0x7ffff
#define HWIO_QAD0_QGITS_AGBPA_POR                                       0x00000000
#define HWIO_QAD0_QGITS_AGBPA_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_QGITS_AGBPA_ATTR                                             0x3
#define HWIO_QAD0_QGITS_AGBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_QGITS_AGBPA_ADDR(x), HWIO_QAD0_QGITS_AGBPA_RMSK)
#define HWIO_QAD0_QGITS_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QGITS_AGBPA_ADDR(x), m)
#define HWIO_QAD0_QGITS_AGBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_QGITS_AGBPA_ADDR(x),v)
#define HWIO_QAD0_QGITS_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QGITS_AGBPA_ADDR(x),m,v,HWIO_QAD0_QGITS_AGBPA_IN(x))
#define HWIO_QAD0_QGITS_AGBPA_REQPRIORITY_BMSK                             0x60000
#define HWIO_QAD0_QGITS_AGBPA_REQPRIORITY_SHFT                                0x11
#define HWIO_QAD0_QGITS_AGBPA_REQPRIORITY_REPLACE_BMSK                     0x10000
#define HWIO_QAD0_QGITS_AGBPA_REQPRIORITY_REPLACE_SHFT                        0x10
#define HWIO_QAD0_QGITS_AGBPA_BPVMID_BMSK                                   0xffff
#define HWIO_QAD0_QGITS_AGBPA_BPVMID_SHFT                                      0x0

#define HWIO_QAD0_QDEVICEID_ADDR(x)                                     ((x) + 0x00001058)
#define HWIO_QAD0_QDEVICEID_PHYS(x)                                     ((x) + 0x00001058)
#define HWIO_QAD0_QDEVICEID_RMSK                                        0xffffffff
#define HWIO_QAD0_QDEVICEID_POR                                         0x00000000
#define HWIO_QAD0_QDEVICEID_POR_RMSK                                    0xffffffff
#define HWIO_QAD0_QDEVICEID_ATTR                                               0x3
#define HWIO_QAD0_QDEVICEID_IN(x)      \
        in_dword_masked(HWIO_QAD0_QDEVICEID_ADDR(x), HWIO_QAD0_QDEVICEID_RMSK)
#define HWIO_QAD0_QDEVICEID_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QDEVICEID_ADDR(x), m)
#define HWIO_QAD0_QDEVICEID_OUT(x, v)      \
        out_dword(HWIO_QAD0_QDEVICEID_ADDR(x),v)
#define HWIO_QAD0_QDEVICEID_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QDEVICEID_ADDR(x),m,v,HWIO_QAD0_QDEVICEID_IN(x))
#define HWIO_QAD0_QDEVICEID_DEVICEID_BMSK                               0xffffffff
#define HWIO_QAD0_QDEVICEID_DEVICEID_SHFT                                      0x0

#define HWIO_QAD0_QTT_CNTL_ADDR(x)                                      ((x) + 0x0000108c)
#define HWIO_QAD0_QTT_CNTL_PHYS(x)                                      ((x) + 0x0000108c)
#define HWIO_QAD0_QTT_CNTL_RMSK                                                0x1
#define HWIO_QAD0_QTT_CNTL_POR                                          0x00000000
#define HWIO_QAD0_QTT_CNTL_POR_RMSK                                     0xffffffff
#define HWIO_QAD0_QTT_CNTL_ATTR                                                0x3
#define HWIO_QAD0_QTT_CNTL_IN(x)      \
        in_dword_masked(HWIO_QAD0_QTT_CNTL_ADDR(x), HWIO_QAD0_QTT_CNTL_RMSK)
#define HWIO_QAD0_QTT_CNTL_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QTT_CNTL_ADDR(x), m)
#define HWIO_QAD0_QTT_CNTL_OUT(x, v)      \
        out_dword(HWIO_QAD0_QTT_CNTL_ADDR(x),v)
#define HWIO_QAD0_QTT_CNTL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QTT_CNTL_ADDR(x),m,v,HWIO_QAD0_QTT_CNTL_IN(x))
#define HWIO_QAD0_QTT_CNTL_ATS_ATTR_OVR_BMSK                                   0x1
#define HWIO_QAD0_QTT_CNTL_ATS_ATTR_OVR_SHFT                                   0x0

#define HWIO_QAD0_QTT_GBPA_ADDR(x)                                      ((x) + 0x00001090)
#define HWIO_QAD0_QTT_GBPA_PHYS(x)                                      ((x) + 0x00001090)
#define HWIO_QAD0_QTT_GBPA_RMSK                                         0x800f3f0f
#define HWIO_QAD0_QTT_GBPA_POR                                          0x0000280f
#define HWIO_QAD0_QTT_GBPA_POR_RMSK                                     0xffffffff
#define HWIO_QAD0_QTT_GBPA_ATTR                                                0x3
#define HWIO_QAD0_QTT_GBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_QTT_GBPA_ADDR(x), HWIO_QAD0_QTT_GBPA_RMSK)
#define HWIO_QAD0_QTT_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QTT_GBPA_ADDR(x), m)
#define HWIO_QAD0_QTT_GBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_QTT_GBPA_ADDR(x),v)
#define HWIO_QAD0_QTT_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QTT_GBPA_ADDR(x),m,v,HWIO_QAD0_QTT_GBPA_IN(x))
#define HWIO_QAD0_QTT_GBPA_UPDATE_BMSK                                  0x80000000
#define HWIO_QAD0_QTT_GBPA_UPDATE_SHFT                                        0x1f
#define HWIO_QAD0_QTT_GBPA_INSTCFG_BMSK                                    0xc0000
#define HWIO_QAD0_QTT_GBPA_INSTCFG_SHFT                                       0x12
#define HWIO_QAD0_QTT_GBPA_PRIVCFG_BMSK                                    0x30000
#define HWIO_QAD0_QTT_GBPA_PRIVCFG_SHFT                                       0x10
#define HWIO_QAD0_QTT_GBPA_SHCFG_BMSK                                       0x3000
#define HWIO_QAD0_QTT_GBPA_SHCFG_SHFT                                          0xc
#define HWIO_QAD0_QTT_GBPA_ALLOCCFG_BMSK                                     0xf00
#define HWIO_QAD0_QTT_GBPA_ALLOCCFG_SHFT                                       0x8
#define HWIO_QAD0_QTT_GBPA_MEMATTR_BMSK                                        0xf
#define HWIO_QAD0_QTT_GBPA_MEMATTR_SHFT                                        0x0

#define HWIO_QAD0_QTT_AGBPA_ADDR(x)                                     ((x) + 0x00001094)
#define HWIO_QAD0_QTT_AGBPA_PHYS(x)                                     ((x) + 0x00001094)
#define HWIO_QAD0_QTT_AGBPA_RMSK                                           0x7ffff
#define HWIO_QAD0_QTT_AGBPA_POR                                         0x00000000
#define HWIO_QAD0_QTT_AGBPA_POR_RMSK                                    0xffffffff
#define HWIO_QAD0_QTT_AGBPA_ATTR                                               0x3
#define HWIO_QAD0_QTT_AGBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_QTT_AGBPA_ADDR(x), HWIO_QAD0_QTT_AGBPA_RMSK)
#define HWIO_QAD0_QTT_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_QTT_AGBPA_ADDR(x), m)
#define HWIO_QAD0_QTT_AGBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_QTT_AGBPA_ADDR(x),v)
#define HWIO_QAD0_QTT_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_QTT_AGBPA_ADDR(x),m,v,HWIO_QAD0_QTT_AGBPA_IN(x))
#define HWIO_QAD0_QTT_AGBPA_REQPRIORITY_BMSK                               0x60000
#define HWIO_QAD0_QTT_AGBPA_REQPRIORITY_SHFT                                  0x11
#define HWIO_QAD0_QTT_AGBPA_REQPRIORITY_REPLACE_BMSK                       0x10000
#define HWIO_QAD0_QTT_AGBPA_REQPRIORITY_REPLACE_SHFT                          0x10
#define HWIO_QAD0_QTT_AGBPA_BPVMID_BMSK                                     0xffff
#define HWIO_QAD0_QTT_AGBPA_BPVMID_SHFT                                        0x0

#define HWIO_QAD0_S_IDR0_ADDR(x)                                        ((x) + 0x00008000)
#define HWIO_QAD0_S_IDR0_PHYS(x)                                        ((x) + 0x00008000)
#define HWIO_QAD0_S_IDR0_RMSK                                            0x3002000
#define HWIO_QAD0_S_IDR0_POR                                            0x00002000
#define HWIO_QAD0_S_IDR0_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_S_IDR0_ATTR                                                  0x1
#define HWIO_QAD0_S_IDR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_IDR0_ADDR(x), HWIO_QAD0_S_IDR0_RMSK)
#define HWIO_QAD0_S_IDR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_IDR0_ADDR(x), m)
#define HWIO_QAD0_S_IDR0_STALL_MODEL_BMSK                                0x3000000
#define HWIO_QAD0_S_IDR0_STALL_MODEL_SHFT                                     0x18
#define HWIO_QAD0_S_IDR0_MSI_BMSK                                           0x2000
#define HWIO_QAD0_S_IDR0_MSI_SHFT                                              0xd

#define HWIO_QAD0_S_IDR1_ADDR(x)                                        ((x) + 0x00008004)
#define HWIO_QAD0_S_IDR1_PHYS(x)                                        ((x) + 0x00008004)
#define HWIO_QAD0_S_IDR1_RMSK                                           0x8000001f
#define HWIO_QAD0_S_IDR1_POR                                            0x80000010
#define HWIO_QAD0_S_IDR1_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_S_IDR1_ATTR                                                  0x1
#define HWIO_QAD0_S_IDR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_IDR1_ADDR(x), HWIO_QAD0_S_IDR1_RMSK)
#define HWIO_QAD0_S_IDR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_IDR1_ADDR(x), m)
#define HWIO_QAD0_S_IDR1_SECURE_IMPL_BMSK                               0x80000000
#define HWIO_QAD0_S_IDR1_SECURE_IMPL_SHFT                                     0x1f
#define HWIO_QAD0_S_IDR1_S_SIDSIZE_BMSK                                       0x1f
#define HWIO_QAD0_S_IDR1_S_SIDSIZE_SHFT                                        0x0

#define HWIO_QAD0_S_IDR2_ADDR(x)                                        ((x) + 0x00008008)
#define HWIO_QAD0_S_IDR2_PHYS(x)                                        ((x) + 0x00008008)
#define HWIO_QAD0_S_IDR2_RMSK                                           0xffffffff
#define HWIO_QAD0_S_IDR2_POR                                            0x00000000
#define HWIO_QAD0_S_IDR2_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_S_IDR2_ATTR                                                  0x1
#define HWIO_QAD0_S_IDR2_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_IDR2_ADDR(x), HWIO_QAD0_S_IDR2_RMSK)
#define HWIO_QAD0_S_IDR2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_IDR2_ADDR(x), m)
#define HWIO_QAD0_S_IDR2_RSRVED_31_0_BMSK                               0xffffffff
#define HWIO_QAD0_S_IDR2_RSRVED_31_0_SHFT                                      0x0

#define HWIO_QAD0_S_IDR3_ADDR(x)                                        ((x) + 0x0000800c)
#define HWIO_QAD0_S_IDR3_PHYS(x)                                        ((x) + 0x0000800c)
#define HWIO_QAD0_S_IDR3_RMSK                                           0xffffffff
#define HWIO_QAD0_S_IDR3_POR                                            0x00000000
#define HWIO_QAD0_S_IDR3_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_S_IDR3_ATTR                                                  0x1
#define HWIO_QAD0_S_IDR3_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_IDR3_ADDR(x), HWIO_QAD0_S_IDR3_RMSK)
#define HWIO_QAD0_S_IDR3_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_IDR3_ADDR(x), m)
#define HWIO_QAD0_S_IDR3_RSRVED_31_0_BMSK                               0xffffffff
#define HWIO_QAD0_S_IDR3_RSRVED_31_0_SHFT                                      0x0

#define HWIO_QAD0_S_IDR4_ADDR(x)                                        ((x) + 0x00008010)
#define HWIO_QAD0_S_IDR4_PHYS(x)                                        ((x) + 0x00008010)
#define HWIO_QAD0_S_IDR4_RMSK                                           0xffffffff
#define HWIO_QAD0_S_IDR4_POR                                            0x00000000
#define HWIO_QAD0_S_IDR4_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_S_IDR4_ATTR                                                  0x1
#define HWIO_QAD0_S_IDR4_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_IDR4_ADDR(x), HWIO_QAD0_S_IDR4_RMSK)
#define HWIO_QAD0_S_IDR4_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_IDR4_ADDR(x), m)
#define HWIO_QAD0_S_IDR4_IMPDEF_BMSK                                    0xffffffff
#define HWIO_QAD0_S_IDR4_IMPDEF_SHFT                                           0x0

#define HWIO_QAD0_S_CR0_ADDR(x)                                         ((x) + 0x00008020)
#define HWIO_QAD0_S_CR0_PHYS(x)                                         ((x) + 0x00008020)
#define HWIO_QAD0_S_CR0_RMSK                                                 0x22d
#define HWIO_QAD0_S_CR0_POR                                             0x00000000
#define HWIO_QAD0_S_CR0_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_S_CR0_ATTR                                                   0x3
#define HWIO_QAD0_S_CR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_CR0_ADDR(x), HWIO_QAD0_S_CR0_RMSK)
#define HWIO_QAD0_S_CR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_CR0_ADDR(x), m)
#define HWIO_QAD0_S_CR0_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_CR0_ADDR(x),v)
#define HWIO_QAD0_S_CR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_CR0_ADDR(x),m,v,HWIO_QAD0_S_CR0_IN(x))
#define HWIO_QAD0_S_CR0_NSSTALLD_BMSK                                        0x200
#define HWIO_QAD0_S_CR0_NSSTALLD_SHFT                                          0x9
#define HWIO_QAD0_S_CR0_SIF_BMSK                                              0x20
#define HWIO_QAD0_S_CR0_SIF_SHFT                                               0x5
#define HWIO_QAD0_S_CR0_CMDQEN_BMSK                                            0x8
#define HWIO_QAD0_S_CR0_CMDQEN_SHFT                                            0x3
#define HWIO_QAD0_S_CR0_EVENTQEN_BMSK                                          0x4
#define HWIO_QAD0_S_CR0_EVENTQEN_SHFT                                          0x2
#define HWIO_QAD0_S_CR0_SMMUEN_BMSK                                            0x1
#define HWIO_QAD0_S_CR0_SMMUEN_SHFT                                            0x0

#define HWIO_QAD0_S_CR0ACK_ADDR(x)                                      ((x) + 0x00008024)
#define HWIO_QAD0_S_CR0ACK_PHYS(x)                                      ((x) + 0x00008024)
#define HWIO_QAD0_S_CR0ACK_RMSK                                              0x22d
#define HWIO_QAD0_S_CR0ACK_POR                                          0x00000000
#define HWIO_QAD0_S_CR0ACK_POR_RMSK                                     0xffffffff
#define HWIO_QAD0_S_CR0ACK_ATTR                                                0x1
#define HWIO_QAD0_S_CR0ACK_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_CR0ACK_ADDR(x), HWIO_QAD0_S_CR0ACK_RMSK)
#define HWIO_QAD0_S_CR0ACK_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_CR0ACK_ADDR(x), m)
#define HWIO_QAD0_S_CR0ACK_NSSTALLD_BMSK                                     0x200
#define HWIO_QAD0_S_CR0ACK_NSSTALLD_SHFT                                       0x9
#define HWIO_QAD0_S_CR0ACK_SIF_BMSK                                           0x20
#define HWIO_QAD0_S_CR0ACK_SIF_SHFT                                            0x5
#define HWIO_QAD0_S_CR0ACK_CMDQEN_BMSK                                         0x8
#define HWIO_QAD0_S_CR0ACK_CMDQEN_SHFT                                         0x3
#define HWIO_QAD0_S_CR0ACK_EVENTQEN_BMSK                                       0x4
#define HWIO_QAD0_S_CR0ACK_EVENTQEN_SHFT                                       0x2
#define HWIO_QAD0_S_CR0ACK_SMMUEN_BMSK                                         0x1
#define HWIO_QAD0_S_CR0ACK_SMMUEN_SHFT                                         0x0

#define HWIO_QAD0_S_CR1_ADDR(x)                                         ((x) + 0x00008028)
#define HWIO_QAD0_S_CR1_PHYS(x)                                         ((x) + 0x00008028)
#define HWIO_QAD0_S_CR1_RMSK                                                 0xfff
#define HWIO_QAD0_S_CR1_POR                                             0x00000000
#define HWIO_QAD0_S_CR1_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_S_CR1_ATTR                                                   0x3
#define HWIO_QAD0_S_CR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_CR1_ADDR(x), HWIO_QAD0_S_CR1_RMSK)
#define HWIO_QAD0_S_CR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_CR1_ADDR(x), m)
#define HWIO_QAD0_S_CR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_CR1_ADDR(x),v)
#define HWIO_QAD0_S_CR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_CR1_ADDR(x),m,v,HWIO_QAD0_S_CR1_IN(x))
#define HWIO_QAD0_S_CR1_TABLE_SH_BMSK                                        0xc00
#define HWIO_QAD0_S_CR1_TABLE_SH_SHFT                                          0xa
#define HWIO_QAD0_S_CR1_TABLE_OC_BMSK                                        0x300
#define HWIO_QAD0_S_CR1_TABLE_OC_SHFT                                          0x8
#define HWIO_QAD0_S_CR1_TABLE_IC_BMSK                                         0xc0
#define HWIO_QAD0_S_CR1_TABLE_IC_SHFT                                          0x6
#define HWIO_QAD0_S_CR1_QUEUE_SH_BMSK                                         0x30
#define HWIO_QAD0_S_CR1_QUEUE_SH_SHFT                                          0x4
#define HWIO_QAD0_S_CR1_QUEUE_OC_BMSK                                          0xc
#define HWIO_QAD0_S_CR1_QUEUE_OC_SHFT                                          0x2
#define HWIO_QAD0_S_CR1_QUEUE_IC_BMSK                                          0x3
#define HWIO_QAD0_S_CR1_QUEUE_IC_SHFT                                          0x0

#define HWIO_QAD0_S_CR2_ADDR(x)                                         ((x) + 0x0000802c)
#define HWIO_QAD0_S_CR2_PHYS(x)                                         ((x) + 0x0000802c)
#define HWIO_QAD0_S_CR2_RMSK                                                   0x6
#define HWIO_QAD0_S_CR2_POR                                             0x00000004
#define HWIO_QAD0_S_CR2_POR_RMSK                                        0xffffffff
#define HWIO_QAD0_S_CR2_ATTR                                                   0x3
#define HWIO_QAD0_S_CR2_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_CR2_ADDR(x), HWIO_QAD0_S_CR2_RMSK)
#define HWIO_QAD0_S_CR2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_CR2_ADDR(x), m)
#define HWIO_QAD0_S_CR2_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_CR2_ADDR(x),v)
#define HWIO_QAD0_S_CR2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_CR2_ADDR(x),m,v,HWIO_QAD0_S_CR2_IN(x))
#define HWIO_QAD0_S_CR2_PTM_BMSK                                               0x4
#define HWIO_QAD0_S_CR2_PTM_SHFT                                               0x2
#define HWIO_QAD0_S_CR2_RECINVSID_BMSK                                         0x2
#define HWIO_QAD0_S_CR2_RECINVSID_SHFT                                         0x1

#define HWIO_QAD0_S_GBPA_ADDR(x)                                        ((x) + 0x00008044)
#define HWIO_QAD0_S_GBPA_PHYS(x)                                        ((x) + 0x00008044)
#define HWIO_QAD0_S_GBPA_RMSK                                           0x801fff1f
#define HWIO_QAD0_S_GBPA_POR                                            0x00001000
#define HWIO_QAD0_S_GBPA_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_S_GBPA_ATTR                                                  0x3
#define HWIO_QAD0_S_GBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GBPA_ADDR(x), HWIO_QAD0_S_GBPA_RMSK)
#define HWIO_QAD0_S_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GBPA_ADDR(x), m)
#define HWIO_QAD0_S_GBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GBPA_ADDR(x),v)
#define HWIO_QAD0_S_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GBPA_ADDR(x),m,v,HWIO_QAD0_S_GBPA_IN(x))
#define HWIO_QAD0_S_GBPA_UPDATE_BMSK                                    0x80000000
#define HWIO_QAD0_S_GBPA_UPDATE_SHFT                                          0x1f
#define HWIO_QAD0_S_GBPA_ABORT_BMSK                                       0x100000
#define HWIO_QAD0_S_GBPA_ABORT_SHFT                                           0x14
#define HWIO_QAD0_S_GBPA_INSTCFG_BMSK                                      0xc0000
#define HWIO_QAD0_S_GBPA_INSTCFG_SHFT                                         0x12
#define HWIO_QAD0_S_GBPA_PRIVCFG_BMSK                                      0x30000
#define HWIO_QAD0_S_GBPA_PRIVCFG_SHFT                                         0x10
#define HWIO_QAD0_S_GBPA_NSCFG_BMSK                                         0xc000
#define HWIO_QAD0_S_GBPA_NSCFG_SHFT                                            0xe
#define HWIO_QAD0_S_GBPA_SHCFG_BMSK                                         0x3000
#define HWIO_QAD0_S_GBPA_SHCFG_SHFT                                            0xc
#define HWIO_QAD0_S_GBPA_ALLOCCFG_BMSK                                       0xf00
#define HWIO_QAD0_S_GBPA_ALLOCCFG_SHFT                                         0x8
#define HWIO_QAD0_S_GBPA_MTCFG_BMSK                                           0x10
#define HWIO_QAD0_S_GBPA_MTCFG_SHFT                                            0x4
#define HWIO_QAD0_S_GBPA_MEMATTR_BMSK                                          0xf
#define HWIO_QAD0_S_GBPA_MEMATTR_SHFT                                          0x0

#define HWIO_QAD0_S_AGBPA_ADDR(x)                                       ((x) + 0x00008048)
#define HWIO_QAD0_S_AGBPA_PHYS(x)                                       ((x) + 0x00008048)
#define HWIO_QAD0_S_AGBPA_RMSK                                             0x7ffff
#define HWIO_QAD0_S_AGBPA_POR                                           0x00000000
#define HWIO_QAD0_S_AGBPA_POR_RMSK                                      0xffffffff
#define HWIO_QAD0_S_AGBPA_ATTR                                                 0x3
#define HWIO_QAD0_S_AGBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_AGBPA_ADDR(x), HWIO_QAD0_S_AGBPA_RMSK)
#define HWIO_QAD0_S_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_AGBPA_ADDR(x), m)
#define HWIO_QAD0_S_AGBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_AGBPA_ADDR(x),v)
#define HWIO_QAD0_S_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_AGBPA_ADDR(x),m,v,HWIO_QAD0_S_AGBPA_IN(x))
#define HWIO_QAD0_S_AGBPA_REQPRIORITY_BMSK                                 0x60000
#define HWIO_QAD0_S_AGBPA_REQPRIORITY_SHFT                                    0x11
#define HWIO_QAD0_S_AGBPA_REQPRIORITY_REPLACE_BMSK                         0x10000
#define HWIO_QAD0_S_AGBPA_REQPRIORITY_REPLACE_SHFT                            0x10
#define HWIO_QAD0_S_AGBPA_BPVMID_BMSK                                       0xffff
#define HWIO_QAD0_S_AGBPA_BPVMID_SHFT                                          0x0

#define HWIO_QAD0_S_IRQ_CTRL_ADDR(x)                                    ((x) + 0x00008050)
#define HWIO_QAD0_S_IRQ_CTRL_PHYS(x)                                    ((x) + 0x00008050)
#define HWIO_QAD0_S_IRQ_CTRL_RMSK                                              0x5
#define HWIO_QAD0_S_IRQ_CTRL_POR                                        0x00000000
#define HWIO_QAD0_S_IRQ_CTRL_POR_RMSK                                   0xffffffff
#define HWIO_QAD0_S_IRQ_CTRL_ATTR                                              0x3
#define HWIO_QAD0_S_IRQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_IRQ_CTRL_ADDR(x), HWIO_QAD0_S_IRQ_CTRL_RMSK)
#define HWIO_QAD0_S_IRQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_IRQ_CTRL_ADDR(x), m)
#define HWIO_QAD0_S_IRQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_IRQ_CTRL_ADDR(x),v)
#define HWIO_QAD0_S_IRQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_IRQ_CTRL_ADDR(x),m,v,HWIO_QAD0_S_IRQ_CTRL_IN(x))
#define HWIO_QAD0_S_IRQ_CTRL_EVENTQ_IRQEN_BMSK                                 0x4
#define HWIO_QAD0_S_IRQ_CTRL_EVENTQ_IRQEN_SHFT                                 0x2
#define HWIO_QAD0_S_IRQ_CTRL_GERROR_IRQEN_BMSK                                 0x1
#define HWIO_QAD0_S_IRQ_CTRL_GERROR_IRQEN_SHFT                                 0x0

#define HWIO_QAD0_S_IRQ_CTRLACK_ADDR(x)                                 ((x) + 0x00008054)
#define HWIO_QAD0_S_IRQ_CTRLACK_PHYS(x)                                 ((x) + 0x00008054)
#define HWIO_QAD0_S_IRQ_CTRLACK_RMSK                                           0x5
#define HWIO_QAD0_S_IRQ_CTRLACK_POR                                     0x00000000
#define HWIO_QAD0_S_IRQ_CTRLACK_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_IRQ_CTRLACK_ATTR                                           0x1
#define HWIO_QAD0_S_IRQ_CTRLACK_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_IRQ_CTRLACK_ADDR(x), HWIO_QAD0_S_IRQ_CTRLACK_RMSK)
#define HWIO_QAD0_S_IRQ_CTRLACK_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_IRQ_CTRLACK_ADDR(x), m)
#define HWIO_QAD0_S_IRQ_CTRLACK_EVENTQ_IRQEN_BMSK                              0x4
#define HWIO_QAD0_S_IRQ_CTRLACK_EVENTQ_IRQEN_SHFT                              0x2
#define HWIO_QAD0_S_IRQ_CTRLACK_GERROR_IRQEN_BMSK                              0x1
#define HWIO_QAD0_S_IRQ_CTRLACK_GERROR_IRQEN_SHFT                              0x0

#define HWIO_QAD0_S_GERROR_ADDR(x)                                      ((x) + 0x00008060)
#define HWIO_QAD0_S_GERROR_PHYS(x)                                      ((x) + 0x00008060)
#define HWIO_QAD0_S_GERROR_RMSK                                              0x1b5
#define HWIO_QAD0_S_GERROR_POR                                          0x00000000
#define HWIO_QAD0_S_GERROR_POR_RMSK                                     0xffffffff
#define HWIO_QAD0_S_GERROR_ATTR                                                0x1
#define HWIO_QAD0_S_GERROR_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_ADDR(x), HWIO_QAD0_S_GERROR_RMSK)
#define HWIO_QAD0_S_GERROR_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_ADDR(x), m)
#define HWIO_QAD0_S_GERROR_SFM_ERR_BMSK                                      0x100
#define HWIO_QAD0_S_GERROR_SFM_ERR_SHFT                                        0x8
#define HWIO_QAD0_S_GERROR_MSI_GERROR_ABT_ERR_BMSK                            0x80
#define HWIO_QAD0_S_GERROR_MSI_GERROR_ABT_ERR_SHFT                             0x7
#define HWIO_QAD0_S_GERROR_MSI_EVENTQ_ABT_ERR_BMSK                            0x20
#define HWIO_QAD0_S_GERROR_MSI_EVENTQ_ABT_ERR_SHFT                             0x5
#define HWIO_QAD0_S_GERROR_MSI_CMDQ_ABT_ERR_BMSK                              0x10
#define HWIO_QAD0_S_GERROR_MSI_CMDQ_ABT_ERR_SHFT                               0x4
#define HWIO_QAD0_S_GERROR_EVENTQ_ABT_ERR_BMSK                                 0x4
#define HWIO_QAD0_S_GERROR_EVENTQ_ABT_ERR_SHFT                                 0x2
#define HWIO_QAD0_S_GERROR_CMDQ_ERR_BMSK                                       0x1
#define HWIO_QAD0_S_GERROR_CMDQ_ERR_SHFT                                       0x0

#define HWIO_QAD0_S_GERRORN_ADDR(x)                                     ((x) + 0x00008064)
#define HWIO_QAD0_S_GERRORN_PHYS(x)                                     ((x) + 0x00008064)
#define HWIO_QAD0_S_GERRORN_RMSK                                             0x1b5
#define HWIO_QAD0_S_GERRORN_POR                                         0x00000000
#define HWIO_QAD0_S_GERRORN_POR_RMSK                                    0xffffffff
#define HWIO_QAD0_S_GERRORN_ATTR                                               0x3
#define HWIO_QAD0_S_GERRORN_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GERRORN_ADDR(x), HWIO_QAD0_S_GERRORN_RMSK)
#define HWIO_QAD0_S_GERRORN_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GERRORN_ADDR(x), m)
#define HWIO_QAD0_S_GERRORN_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GERRORN_ADDR(x),v)
#define HWIO_QAD0_S_GERRORN_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GERRORN_ADDR(x),m,v,HWIO_QAD0_S_GERRORN_IN(x))
#define HWIO_QAD0_S_GERRORN_SFM_ERR_BMSK                                     0x100
#define HWIO_QAD0_S_GERRORN_SFM_ERR_SHFT                                       0x8
#define HWIO_QAD0_S_GERRORN_MSI_GERROR_ABT_ERR_BMSK                           0x80
#define HWIO_QAD0_S_GERRORN_MSI_GERROR_ABT_ERR_SHFT                            0x7
#define HWIO_QAD0_S_GERRORN_MSI_EVENTQ_ABT_ERR_BMSK                           0x20
#define HWIO_QAD0_S_GERRORN_MSI_EVENTQ_ABT_ERR_SHFT                            0x5
#define HWIO_QAD0_S_GERRORN_MSI_CMDQ_ABT_ERR_BMSK                             0x10
#define HWIO_QAD0_S_GERRORN_MSI_CMDQ_ABT_ERR_SHFT                              0x4
#define HWIO_QAD0_S_GERRORN_EVENTQ_ABT_ERR_BMSK                                0x4
#define HWIO_QAD0_S_GERRORN_EVENTQ_ABT_ERR_SHFT                                0x2
#define HWIO_QAD0_S_GERRORN_CMDQ_ERR_BMSK                                      0x1
#define HWIO_QAD0_S_GERRORN_CMDQ_ERR_SHFT                                      0x0

#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_ADDR(x)                           ((x) + 0x00008068)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_PHYS(x)                           ((x) + 0x00008068)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_RMSK                              0xfffffffc
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_POR                               0x00000000
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_POR_RMSK                          0xffffffff
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_ATTR                                     0x3
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_IRQ_CFG0_L_ADDR(x), HWIO_QAD0_S_GERROR_IRQ_CFG0_L_RMSK)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GERROR_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GERROR_IRQ_CFG0_L_ADDR(x),m,v,HWIO_QAD0_S_GERROR_IRQ_CFG0_L_IN(x))
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_ADDR_31_2_BMSK                    0xfffffffc
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_L_ADDR_31_2_SHFT                           0x2

#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_ADDR(x)                           ((x) + 0x0000806c)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_PHYS(x)                           ((x) + 0x0000806c)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_RMSK                                  0xffff
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_POR                               0x00000000
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_POR_RMSK                          0xffffffff
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_ATTR                                     0x3
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_IRQ_CFG0_H_ADDR(x), HWIO_QAD0_S_GERROR_IRQ_CFG0_H_RMSK)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GERROR_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GERROR_IRQ_CFG0_H_ADDR(x),m,v,HWIO_QAD0_S_GERROR_IRQ_CFG0_H_IN(x))
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_ADDR_47_32_BMSK                       0xffff
#define HWIO_QAD0_S_GERROR_IRQ_CFG0_H_ADDR_47_32_SHFT                          0x0

#define HWIO_QAD0_S_GERROR_IRQ_CFG1_ADDR(x)                             ((x) + 0x00008070)
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_PHYS(x)                             ((x) + 0x00008070)
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_RMSK                                0xffffffff
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_POR                                 0x00000000
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_POR_RMSK                            0xffffffff
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_ATTR                                       0x3
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_IRQ_CFG1_ADDR(x), HWIO_QAD0_S_GERROR_IRQ_CFG1_RMSK)
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_IRQ_CFG1_ADDR(x), m)
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GERROR_IRQ_CFG1_ADDR(x),v)
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GERROR_IRQ_CFG1_ADDR(x),m,v,HWIO_QAD0_S_GERROR_IRQ_CFG1_IN(x))
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_DATA_BMSK                           0xffffffff
#define HWIO_QAD0_S_GERROR_IRQ_CFG1_DATA_SHFT                                  0x0

#define HWIO_QAD0_S_GERROR_IRQ_CFG2_ADDR(x)                             ((x) + 0x00008074)
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_PHYS(x)                             ((x) + 0x00008074)
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_RMSK                                      0x3f
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_POR                                 0x00000000
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_POR_RMSK                            0xffffffff
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_ATTR                                       0x3
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_IRQ_CFG2_ADDR(x), HWIO_QAD0_S_GERROR_IRQ_CFG2_RMSK)
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GERROR_IRQ_CFG2_ADDR(x), m)
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GERROR_IRQ_CFG2_ADDR(x),v)
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GERROR_IRQ_CFG2_ADDR(x),m,v,HWIO_QAD0_S_GERROR_IRQ_CFG2_IN(x))
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_SH_BMSK                                   0x30
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_SH_SHFT                                    0x4
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_MEMATTR_BMSK                               0xf
#define HWIO_QAD0_S_GERROR_IRQ_CFG2_MEMATTR_SHFT                               0x0

#define HWIO_QAD0_S_STRTAB_BASE_L_ADDR(x)                               ((x) + 0x00008080)
#define HWIO_QAD0_S_STRTAB_BASE_L_PHYS(x)                               ((x) + 0x00008080)
#define HWIO_QAD0_S_STRTAB_BASE_L_RMSK                                  0xffffffc0
#define HWIO_QAD0_S_STRTAB_BASE_L_POR                                   0x00000000
#define HWIO_QAD0_S_STRTAB_BASE_L_POR_RMSK                              0xffffffff
#define HWIO_QAD0_S_STRTAB_BASE_L_ATTR                                         0x3
#define HWIO_QAD0_S_STRTAB_BASE_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_STRTAB_BASE_L_ADDR(x), HWIO_QAD0_S_STRTAB_BASE_L_RMSK)
#define HWIO_QAD0_S_STRTAB_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_STRTAB_BASE_L_ADDR(x), m)
#define HWIO_QAD0_S_STRTAB_BASE_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_STRTAB_BASE_L_ADDR(x),v)
#define HWIO_QAD0_S_STRTAB_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_STRTAB_BASE_L_ADDR(x),m,v,HWIO_QAD0_S_STRTAB_BASE_L_IN(x))
#define HWIO_QAD0_S_STRTAB_BASE_L_ADDR_31_6_BMSK                        0xffffffc0
#define HWIO_QAD0_S_STRTAB_BASE_L_ADDR_31_6_SHFT                               0x6

#define HWIO_QAD0_S_STRTAB_BASE_H_ADDR(x)                               ((x) + 0x00008084)
#define HWIO_QAD0_S_STRTAB_BASE_H_PHYS(x)                               ((x) + 0x00008084)
#define HWIO_QAD0_S_STRTAB_BASE_H_RMSK                                  0x4000ffff
#define HWIO_QAD0_S_STRTAB_BASE_H_POR                                   0x00000000
#define HWIO_QAD0_S_STRTAB_BASE_H_POR_RMSK                              0xffffffff
#define HWIO_QAD0_S_STRTAB_BASE_H_ATTR                                         0x3
#define HWIO_QAD0_S_STRTAB_BASE_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_STRTAB_BASE_H_ADDR(x), HWIO_QAD0_S_STRTAB_BASE_H_RMSK)
#define HWIO_QAD0_S_STRTAB_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_STRTAB_BASE_H_ADDR(x), m)
#define HWIO_QAD0_S_STRTAB_BASE_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_STRTAB_BASE_H_ADDR(x),v)
#define HWIO_QAD0_S_STRTAB_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_STRTAB_BASE_H_ADDR(x),m,v,HWIO_QAD0_S_STRTAB_BASE_H_IN(x))
#define HWIO_QAD0_S_STRTAB_BASE_H_RA_BMSK                               0x40000000
#define HWIO_QAD0_S_STRTAB_BASE_H_RA_SHFT                                     0x1e
#define HWIO_QAD0_S_STRTAB_BASE_H_ADDR_47_32_BMSK                           0xffff
#define HWIO_QAD0_S_STRTAB_BASE_H_ADDR_47_32_SHFT                              0x0

#define HWIO_QAD0_S_STRTAB_BASE_CFG_ADDR(x)                             ((x) + 0x00008088)
#define HWIO_QAD0_S_STRTAB_BASE_CFG_PHYS(x)                             ((x) + 0x00008088)
#define HWIO_QAD0_S_STRTAB_BASE_CFG_RMSK                                   0x307ff
#define HWIO_QAD0_S_STRTAB_BASE_CFG_POR                                 0x00000000
#define HWIO_QAD0_S_STRTAB_BASE_CFG_POR_RMSK                            0xffffffff
#define HWIO_QAD0_S_STRTAB_BASE_CFG_ATTR                                       0x3
#define HWIO_QAD0_S_STRTAB_BASE_CFG_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_STRTAB_BASE_CFG_ADDR(x), HWIO_QAD0_S_STRTAB_BASE_CFG_RMSK)
#define HWIO_QAD0_S_STRTAB_BASE_CFG_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_STRTAB_BASE_CFG_ADDR(x), m)
#define HWIO_QAD0_S_STRTAB_BASE_CFG_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_STRTAB_BASE_CFG_ADDR(x),v)
#define HWIO_QAD0_S_STRTAB_BASE_CFG_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_STRTAB_BASE_CFG_ADDR(x),m,v,HWIO_QAD0_S_STRTAB_BASE_CFG_IN(x))
#define HWIO_QAD0_S_STRTAB_BASE_CFG_FMT_BMSK                               0x30000
#define HWIO_QAD0_S_STRTAB_BASE_CFG_FMT_SHFT                                  0x10
#define HWIO_QAD0_S_STRTAB_BASE_CFG_SPLIT_BMSK                               0x7c0
#define HWIO_QAD0_S_STRTAB_BASE_CFG_SPLIT_SHFT                                 0x6
#define HWIO_QAD0_S_STRTAB_BASE_CFG_LOG2SIZE_BMSK                             0x3f
#define HWIO_QAD0_S_STRTAB_BASE_CFG_LOG2SIZE_SHFT                              0x0

#define HWIO_QAD0_S_CMDQ_BASE_L_ADDR(x)                                 ((x) + 0x00008090)
#define HWIO_QAD0_S_CMDQ_BASE_L_PHYS(x)                                 ((x) + 0x00008090)
#define HWIO_QAD0_S_CMDQ_BASE_L_RMSK                                    0xffffffff
#define HWIO_QAD0_S_CMDQ_BASE_L_POR                                     0x00000000
#define HWIO_QAD0_S_CMDQ_BASE_L_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_CMDQ_BASE_L_ATTR                                           0x3
#define HWIO_QAD0_S_CMDQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_CMDQ_BASE_L_ADDR(x), HWIO_QAD0_S_CMDQ_BASE_L_RMSK)
#define HWIO_QAD0_S_CMDQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_CMDQ_BASE_L_ADDR(x), m)
#define HWIO_QAD0_S_CMDQ_BASE_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_CMDQ_BASE_L_ADDR(x),v)
#define HWIO_QAD0_S_CMDQ_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_CMDQ_BASE_L_ADDR(x),m,v,HWIO_QAD0_S_CMDQ_BASE_L_IN(x))
#define HWIO_QAD0_S_CMDQ_BASE_L_ADDR_31_5_BMSK                          0xffffffe0
#define HWIO_QAD0_S_CMDQ_BASE_L_ADDR_31_5_SHFT                                 0x5
#define HWIO_QAD0_S_CMDQ_BASE_L_LOG2SIZE_BMSK                                 0x1f
#define HWIO_QAD0_S_CMDQ_BASE_L_LOG2SIZE_SHFT                                  0x0

#define HWIO_QAD0_S_CMDQ_BASE_H_ADDR(x)                                 ((x) + 0x00008094)
#define HWIO_QAD0_S_CMDQ_BASE_H_PHYS(x)                                 ((x) + 0x00008094)
#define HWIO_QAD0_S_CMDQ_BASE_H_RMSK                                    0x4000ffff
#define HWIO_QAD0_S_CMDQ_BASE_H_POR                                     0x00000000
#define HWIO_QAD0_S_CMDQ_BASE_H_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_CMDQ_BASE_H_ATTR                                           0x3
#define HWIO_QAD0_S_CMDQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_CMDQ_BASE_H_ADDR(x), HWIO_QAD0_S_CMDQ_BASE_H_RMSK)
#define HWIO_QAD0_S_CMDQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_CMDQ_BASE_H_ADDR(x), m)
#define HWIO_QAD0_S_CMDQ_BASE_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_CMDQ_BASE_H_ADDR(x),v)
#define HWIO_QAD0_S_CMDQ_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_CMDQ_BASE_H_ADDR(x),m,v,HWIO_QAD0_S_CMDQ_BASE_H_IN(x))
#define HWIO_QAD0_S_CMDQ_BASE_H_RA_BMSK                                 0x40000000
#define HWIO_QAD0_S_CMDQ_BASE_H_RA_SHFT                                       0x1e
#define HWIO_QAD0_S_CMDQ_BASE_H_ADDR_47_32_BMSK                             0xffff
#define HWIO_QAD0_S_CMDQ_BASE_H_ADDR_47_32_SHFT                                0x0

#define HWIO_QAD0_S_CMDQ_PROD_ADDR(x)                                   ((x) + 0x00008098)
#define HWIO_QAD0_S_CMDQ_PROD_PHYS(x)                                   ((x) + 0x00008098)
#define HWIO_QAD0_S_CMDQ_PROD_RMSK                                         0xfffff
#define HWIO_QAD0_S_CMDQ_PROD_POR                                       0x00000000
#define HWIO_QAD0_S_CMDQ_PROD_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_S_CMDQ_PROD_ATTR                                             0x3
#define HWIO_QAD0_S_CMDQ_PROD_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_CMDQ_PROD_ADDR(x), HWIO_QAD0_S_CMDQ_PROD_RMSK)
#define HWIO_QAD0_S_CMDQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_CMDQ_PROD_ADDR(x), m)
#define HWIO_QAD0_S_CMDQ_PROD_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_CMDQ_PROD_ADDR(x),v)
#define HWIO_QAD0_S_CMDQ_PROD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_CMDQ_PROD_ADDR(x),m,v,HWIO_QAD0_S_CMDQ_PROD_IN(x))
#define HWIO_QAD0_S_CMDQ_PROD_WR_INDEX_AND_WRAP_BMSK                       0xfffff
#define HWIO_QAD0_S_CMDQ_PROD_WR_INDEX_AND_WRAP_SHFT                           0x0

#define HWIO_QAD0_S_CMDQ_CONS_ADDR(x)                                   ((x) + 0x0000809c)
#define HWIO_QAD0_S_CMDQ_CONS_PHYS(x)                                   ((x) + 0x0000809c)
#define HWIO_QAD0_S_CMDQ_CONS_RMSK                                      0x7f0fffff
#define HWIO_QAD0_S_CMDQ_CONS_POR                                       0x00000000
#define HWIO_QAD0_S_CMDQ_CONS_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_S_CMDQ_CONS_ATTR                                             0x3
#define HWIO_QAD0_S_CMDQ_CONS_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_CMDQ_CONS_ADDR(x), HWIO_QAD0_S_CMDQ_CONS_RMSK)
#define HWIO_QAD0_S_CMDQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_CMDQ_CONS_ADDR(x), m)
#define HWIO_QAD0_S_CMDQ_CONS_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_CMDQ_CONS_ADDR(x),v)
#define HWIO_QAD0_S_CMDQ_CONS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_CMDQ_CONS_ADDR(x),m,v,HWIO_QAD0_S_CMDQ_CONS_IN(x))
#define HWIO_QAD0_S_CMDQ_CONS_ERR_BMSK                                  0x7f000000
#define HWIO_QAD0_S_CMDQ_CONS_ERR_SHFT                                        0x18
#define HWIO_QAD0_S_CMDQ_CONS_RD_INDEX_AND_WRAP_BMSK                       0xfffff
#define HWIO_QAD0_S_CMDQ_CONS_RD_INDEX_AND_WRAP_SHFT                           0x0

#define HWIO_QAD0_S_EVENTQ_BASE_L_ADDR(x)                               ((x) + 0x000080a0)
#define HWIO_QAD0_S_EVENTQ_BASE_L_PHYS(x)                               ((x) + 0x000080a0)
#define HWIO_QAD0_S_EVENTQ_BASE_L_RMSK                                  0xffffffff
#define HWIO_QAD0_S_EVENTQ_BASE_L_POR                                   0x00000000
#define HWIO_QAD0_S_EVENTQ_BASE_L_POR_RMSK                              0xffffffff
#define HWIO_QAD0_S_EVENTQ_BASE_L_ATTR                                         0x3
#define HWIO_QAD0_S_EVENTQ_BASE_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_BASE_L_ADDR(x), HWIO_QAD0_S_EVENTQ_BASE_L_RMSK)
#define HWIO_QAD0_S_EVENTQ_BASE_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_BASE_L_ADDR(x), m)
#define HWIO_QAD0_S_EVENTQ_BASE_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_EVENTQ_BASE_L_ADDR(x),v)
#define HWIO_QAD0_S_EVENTQ_BASE_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_EVENTQ_BASE_L_ADDR(x),m,v,HWIO_QAD0_S_EVENTQ_BASE_L_IN(x))
#define HWIO_QAD0_S_EVENTQ_BASE_L_ADDR_31_5_BMSK                        0xffffffe0
#define HWIO_QAD0_S_EVENTQ_BASE_L_ADDR_31_5_SHFT                               0x5
#define HWIO_QAD0_S_EVENTQ_BASE_L_LOG2SIZE_BMSK                               0x1f
#define HWIO_QAD0_S_EVENTQ_BASE_L_LOG2SIZE_SHFT                                0x0

#define HWIO_QAD0_S_EVENTQ_BASE_H_ADDR(x)                               ((x) + 0x000080a4)
#define HWIO_QAD0_S_EVENTQ_BASE_H_PHYS(x)                               ((x) + 0x000080a4)
#define HWIO_QAD0_S_EVENTQ_BASE_H_RMSK                                  0x4000ffff
#define HWIO_QAD0_S_EVENTQ_BASE_H_POR                                   0x00000000
#define HWIO_QAD0_S_EVENTQ_BASE_H_POR_RMSK                              0xffffffff
#define HWIO_QAD0_S_EVENTQ_BASE_H_ATTR                                         0x3
#define HWIO_QAD0_S_EVENTQ_BASE_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_BASE_H_ADDR(x), HWIO_QAD0_S_EVENTQ_BASE_H_RMSK)
#define HWIO_QAD0_S_EVENTQ_BASE_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_BASE_H_ADDR(x), m)
#define HWIO_QAD0_S_EVENTQ_BASE_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_EVENTQ_BASE_H_ADDR(x),v)
#define HWIO_QAD0_S_EVENTQ_BASE_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_EVENTQ_BASE_H_ADDR(x),m,v,HWIO_QAD0_S_EVENTQ_BASE_H_IN(x))
#define HWIO_QAD0_S_EVENTQ_BASE_H_WA_BMSK                               0x40000000
#define HWIO_QAD0_S_EVENTQ_BASE_H_WA_SHFT                                     0x1e
#define HWIO_QAD0_S_EVENTQ_BASE_H_ADDR_47_32_BMSK                           0xffff
#define HWIO_QAD0_S_EVENTQ_BASE_H_ADDR_47_32_SHFT                              0x0

#define HWIO_QAD0_S_EVENTQ_PROD_ADDR(x)                                 ((x) + 0x000080a8)
#define HWIO_QAD0_S_EVENTQ_PROD_PHYS(x)                                 ((x) + 0x000080a8)
#define HWIO_QAD0_S_EVENTQ_PROD_RMSK                                    0x800fffff
#define HWIO_QAD0_S_EVENTQ_PROD_POR                                     0x00000000
#define HWIO_QAD0_S_EVENTQ_PROD_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_EVENTQ_PROD_ATTR                                           0x3
#define HWIO_QAD0_S_EVENTQ_PROD_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_PROD_ADDR(x), HWIO_QAD0_S_EVENTQ_PROD_RMSK)
#define HWIO_QAD0_S_EVENTQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_PROD_ADDR(x), m)
#define HWIO_QAD0_S_EVENTQ_PROD_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_EVENTQ_PROD_ADDR(x),v)
#define HWIO_QAD0_S_EVENTQ_PROD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_EVENTQ_PROD_ADDR(x),m,v,HWIO_QAD0_S_EVENTQ_PROD_IN(x))
#define HWIO_QAD0_S_EVENTQ_PROD_OVFLG_BMSK                              0x80000000
#define HWIO_QAD0_S_EVENTQ_PROD_OVFLG_SHFT                                    0x1f
#define HWIO_QAD0_S_EVENTQ_PROD_WR_INDEX_AND_WRAP_BMSK                     0xfffff
#define HWIO_QAD0_S_EVENTQ_PROD_WR_INDEX_AND_WRAP_SHFT                         0x0

#define HWIO_QAD0_S_EVENTQ_CONS_ADDR(x)                                 ((x) + 0x000080ac)
#define HWIO_QAD0_S_EVENTQ_CONS_PHYS(x)                                 ((x) + 0x000080ac)
#define HWIO_QAD0_S_EVENTQ_CONS_RMSK                                    0x800fffff
#define HWIO_QAD0_S_EVENTQ_CONS_POR                                     0x00000000
#define HWIO_QAD0_S_EVENTQ_CONS_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_EVENTQ_CONS_ATTR                                           0x3
#define HWIO_QAD0_S_EVENTQ_CONS_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_CONS_ADDR(x), HWIO_QAD0_S_EVENTQ_CONS_RMSK)
#define HWIO_QAD0_S_EVENTQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_CONS_ADDR(x), m)
#define HWIO_QAD0_S_EVENTQ_CONS_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_EVENTQ_CONS_ADDR(x),v)
#define HWIO_QAD0_S_EVENTQ_CONS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_EVENTQ_CONS_ADDR(x),m,v,HWIO_QAD0_S_EVENTQ_CONS_IN(x))
#define HWIO_QAD0_S_EVENTQ_CONS_OVACKFLG_BMSK                           0x80000000
#define HWIO_QAD0_S_EVENTQ_CONS_OVACKFLG_SHFT                                 0x1f
#define HWIO_QAD0_S_EVENTQ_CONS_RD_INDEX_AND_WRAP_BMSK                     0xfffff
#define HWIO_QAD0_S_EVENTQ_CONS_RD_INDEX_AND_WRAP_SHFT                         0x0

#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_ADDR(x)                           ((x) + 0x000080b0)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_PHYS(x)                           ((x) + 0x000080b0)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_RMSK                              0xfffffffc
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_POR                               0x00000000
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_POR_RMSK                          0xffffffff
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_ATTR                                     0x3
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_ADDR(x), HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_RMSK)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_ADDR(x),m,v,HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_IN(x))
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_ADDR_31_2_BMSK                    0xfffffffc
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_L_ADDR_31_2_SHFT                           0x2

#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_ADDR(x)                           ((x) + 0x000080b4)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_PHYS(x)                           ((x) + 0x000080b4)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_RMSK                                  0xffff
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_POR                               0x00000000
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_POR_RMSK                          0xffffffff
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_ATTR                                     0x3
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_ADDR(x), HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_RMSK)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_ADDR(x),m,v,HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_IN(x))
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_ADDR_47_32_BMSK                       0xffff
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG0_H_ADDR_47_32_SHFT                          0x0

#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_ADDR(x)                             ((x) + 0x000080b8)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_PHYS(x)                             ((x) + 0x000080b8)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_RMSK                                0xffffffff
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_POR                                 0x00000000
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_POR_RMSK                            0xffffffff
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_ATTR                                       0x3
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_IRQ_CFG1_ADDR(x), HWIO_QAD0_S_EVENTQ_IRQ_CFG1_RMSK)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_IRQ_CFG1_ADDR(x), m)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_EVENTQ_IRQ_CFG1_ADDR(x),v)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_EVENTQ_IRQ_CFG1_ADDR(x),m,v,HWIO_QAD0_S_EVENTQ_IRQ_CFG1_IN(x))
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_DATA_BMSK                           0xffffffff
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG1_DATA_SHFT                                  0x0

#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_ADDR(x)                             ((x) + 0x000080bc)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_PHYS(x)                             ((x) + 0x000080bc)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_RMSK                                      0x3f
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_POR                                 0x00000000
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_POR_RMSK                            0xffffffff
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_ATTR                                       0x3
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_IRQ_CFG2_ADDR(x), HWIO_QAD0_S_EVENTQ_IRQ_CFG2_RMSK)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_EVENTQ_IRQ_CFG2_ADDR(x), m)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_EVENTQ_IRQ_CFG2_ADDR(x),v)
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_EVENTQ_IRQ_CFG2_ADDR(x),m,v,HWIO_QAD0_S_EVENTQ_IRQ_CFG2_IN(x))
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_SH_BMSK                                   0x30
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_SH_SHFT                                    0x4
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_MEMATTR_BMSK                               0xf
#define HWIO_QAD0_S_EVENTQ_IRQ_CFG2_MEMATTR_SHFT                               0x0

#define HWIO_QAD0_S_GATOS_CTRL_ADDR(x)                                  ((x) + 0x00008100)
#define HWIO_QAD0_S_GATOS_CTRL_PHYS(x)                                  ((x) + 0x00008100)
#define HWIO_QAD0_S_GATOS_CTRL_RMSK                                            0x1
#define HWIO_QAD0_S_GATOS_CTRL_POR                                      0x00000000
#define HWIO_QAD0_S_GATOS_CTRL_POR_RMSK                                 0xffffffff
#define HWIO_QAD0_S_GATOS_CTRL_ATTR                                            0x3
#define HWIO_QAD0_S_GATOS_CTRL_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_CTRL_ADDR(x), HWIO_QAD0_S_GATOS_CTRL_RMSK)
#define HWIO_QAD0_S_GATOS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_CTRL_ADDR(x), m)
#define HWIO_QAD0_S_GATOS_CTRL_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GATOS_CTRL_ADDR(x),v)
#define HWIO_QAD0_S_GATOS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GATOS_CTRL_ADDR(x),m,v,HWIO_QAD0_S_GATOS_CTRL_IN(x))
#define HWIO_QAD0_S_GATOS_CTRL_RUN_BMSK                                        0x1
#define HWIO_QAD0_S_GATOS_CTRL_RUN_SHFT                                        0x0

#define HWIO_QAD0_S_GATOS_SID_L_ADDR(x)                                 ((x) + 0x00008108)
#define HWIO_QAD0_S_GATOS_SID_L_PHYS(x)                                 ((x) + 0x00008108)
#define HWIO_QAD0_S_GATOS_SID_L_RMSK                                        0xffff
#define HWIO_QAD0_S_GATOS_SID_L_POR                                     0x00000000
#define HWIO_QAD0_S_GATOS_SID_L_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_GATOS_SID_L_ATTR                                           0x3
#define HWIO_QAD0_S_GATOS_SID_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_SID_L_ADDR(x), HWIO_QAD0_S_GATOS_SID_L_RMSK)
#define HWIO_QAD0_S_GATOS_SID_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_SID_L_ADDR(x), m)
#define HWIO_QAD0_S_GATOS_SID_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GATOS_SID_L_ADDR(x),v)
#define HWIO_QAD0_S_GATOS_SID_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GATOS_SID_L_ADDR(x),m,v,HWIO_QAD0_S_GATOS_SID_L_IN(x))
#define HWIO_QAD0_S_GATOS_SID_L_STREAMID_BMSK                               0xffff
#define HWIO_QAD0_S_GATOS_SID_L_STREAMID_SHFT                                  0x0

#define HWIO_QAD0_S_GATOS_SID_H_ADDR(x)                                 ((x) + 0x0000810c)
#define HWIO_QAD0_S_GATOS_SID_H_PHYS(x)                                 ((x) + 0x0000810c)
#define HWIO_QAD0_S_GATOS_SID_H_RMSK                                      0x3fffff
#define HWIO_QAD0_S_GATOS_SID_H_POR                                     0x00000000
#define HWIO_QAD0_S_GATOS_SID_H_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_GATOS_SID_H_ATTR                                           0x3
#define HWIO_QAD0_S_GATOS_SID_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_SID_H_ADDR(x), HWIO_QAD0_S_GATOS_SID_H_RMSK)
#define HWIO_QAD0_S_GATOS_SID_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_SID_H_ADDR(x), m)
#define HWIO_QAD0_S_GATOS_SID_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GATOS_SID_H_ADDR(x),v)
#define HWIO_QAD0_S_GATOS_SID_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GATOS_SID_H_ADDR(x),m,v,HWIO_QAD0_S_GATOS_SID_H_IN(x))
#define HWIO_QAD0_S_GATOS_SID_H_SSEC_BMSK                                 0x200000
#define HWIO_QAD0_S_GATOS_SID_H_SSEC_SHFT                                     0x15
#define HWIO_QAD0_S_GATOS_SID_H_SSID_VALID_BMSK                           0x100000
#define HWIO_QAD0_S_GATOS_SID_H_SSID_VALID_SHFT                               0x14
#define HWIO_QAD0_S_GATOS_SID_H_SUBSTREAMID_BMSK                           0xfffff
#define HWIO_QAD0_S_GATOS_SID_H_SUBSTREAMID_SHFT                               0x0

#define HWIO_QAD0_S_GATOS_ADDR_L_ADDR(x)                                ((x) + 0x00008110)
#define HWIO_QAD0_S_GATOS_ADDR_L_PHYS(x)                                ((x) + 0x00008110)
#define HWIO_QAD0_S_GATOS_ADDR_L_RMSK                                   0xffffffc0
#define HWIO_QAD0_S_GATOS_ADDR_L_POR                                    0x00000000
#define HWIO_QAD0_S_GATOS_ADDR_L_POR_RMSK                               0xffffffff
#define HWIO_QAD0_S_GATOS_ADDR_L_ATTR                                          0x3
#define HWIO_QAD0_S_GATOS_ADDR_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_ADDR_L_ADDR(x), HWIO_QAD0_S_GATOS_ADDR_L_RMSK)
#define HWIO_QAD0_S_GATOS_ADDR_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_ADDR_L_ADDR(x), m)
#define HWIO_QAD0_S_GATOS_ADDR_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GATOS_ADDR_L_ADDR(x),v)
#define HWIO_QAD0_S_GATOS_ADDR_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GATOS_ADDR_L_ADDR(x),m,v,HWIO_QAD0_S_GATOS_ADDR_L_IN(x))
#define HWIO_QAD0_S_GATOS_ADDR_L_ADDR_31_12_BMSK                        0xfffff000
#define HWIO_QAD0_S_GATOS_ADDR_L_ADDR_31_12_SHFT                               0xc
#define HWIO_QAD0_S_GATOS_ADDR_L_TYPE_BMSK                                   0xc00
#define HWIO_QAD0_S_GATOS_ADDR_L_TYPE_SHFT                                     0xa
#define HWIO_QAD0_S_GATOS_ADDR_L_PNU_BMSK                                    0x200
#define HWIO_QAD0_S_GATOS_ADDR_L_PNU_SHFT                                      0x9
#define HWIO_QAD0_S_GATOS_ADDR_L_RNW_BMSK                                    0x100
#define HWIO_QAD0_S_GATOS_ADDR_L_RNW_SHFT                                      0x8
#define HWIO_QAD0_S_GATOS_ADDR_L_IND_BMSK                                     0x80
#define HWIO_QAD0_S_GATOS_ADDR_L_IND_SHFT                                      0x7
#define HWIO_QAD0_S_GATOS_ADDR_L_HTTUI_BMSK                                   0x40
#define HWIO_QAD0_S_GATOS_ADDR_L_HTTUI_SHFT                                    0x6

#define HWIO_QAD0_S_GATOS_ADDR_H_ADDR(x)                                ((x) + 0x00008114)
#define HWIO_QAD0_S_GATOS_ADDR_H_PHYS(x)                                ((x) + 0x00008114)
#define HWIO_QAD0_S_GATOS_ADDR_H_RMSK                                   0xffffffff
#define HWIO_QAD0_S_GATOS_ADDR_H_POR                                    0x00000000
#define HWIO_QAD0_S_GATOS_ADDR_H_POR_RMSK                               0xffffffff
#define HWIO_QAD0_S_GATOS_ADDR_H_ATTR                                          0x3
#define HWIO_QAD0_S_GATOS_ADDR_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_ADDR_H_ADDR(x), HWIO_QAD0_S_GATOS_ADDR_H_RMSK)
#define HWIO_QAD0_S_GATOS_ADDR_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_ADDR_H_ADDR(x), m)
#define HWIO_QAD0_S_GATOS_ADDR_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_GATOS_ADDR_H_ADDR(x),v)
#define HWIO_QAD0_S_GATOS_ADDR_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_GATOS_ADDR_H_ADDR(x),m,v,HWIO_QAD0_S_GATOS_ADDR_H_IN(x))
#define HWIO_QAD0_S_GATOS_ADDR_H_ADDR_63_32_BMSK                        0xffffffff
#define HWIO_QAD0_S_GATOS_ADDR_H_ADDR_63_32_SHFT                               0x0

#define HWIO_QAD0_S_GATOS_PAR_L_ADDR(x)                                 ((x) + 0x00008118)
#define HWIO_QAD0_S_GATOS_PAR_L_PHYS(x)                                 ((x) + 0x00008118)
#define HWIO_QAD0_S_GATOS_PAR_L_RMSK                                    0xffffffff
#define HWIO_QAD0_S_GATOS_PAR_L_POR                                     0x00000000
#define HWIO_QAD0_S_GATOS_PAR_L_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_GATOS_PAR_L_ATTR                                           0x1
#define HWIO_QAD0_S_GATOS_PAR_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_PAR_L_ADDR(x), HWIO_QAD0_S_GATOS_PAR_L_RMSK)
#define HWIO_QAD0_S_GATOS_PAR_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_PAR_L_ADDR(x), m)
#define HWIO_QAD0_S_GATOS_PAR_L_ADDR_BMSK                               0xfffff000
#define HWIO_QAD0_S_GATOS_PAR_L_ADDR_SHFT                                      0xc
#define HWIO_QAD0_S_GATOS_PAR_L_FIELD_BMSK                                   0xffe
#define HWIO_QAD0_S_GATOS_PAR_L_FIELD_SHFT                                     0x1
#define HWIO_QAD0_S_GATOS_PAR_L_FAULT_BMSK                                     0x1
#define HWIO_QAD0_S_GATOS_PAR_L_FAULT_SHFT                                     0x0

#define HWIO_QAD0_S_GATOS_PAR_H_ADDR(x)                                 ((x) + 0x0000811c)
#define HWIO_QAD0_S_GATOS_PAR_H_PHYS(x)                                 ((x) + 0x0000811c)
#define HWIO_QAD0_S_GATOS_PAR_H_RMSK                                    0xff00ffff
#define HWIO_QAD0_S_GATOS_PAR_H_POR                                     0x00000000
#define HWIO_QAD0_S_GATOS_PAR_H_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_GATOS_PAR_H_ATTR                                           0x1
#define HWIO_QAD0_S_GATOS_PAR_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_PAR_H_ADDR(x), HWIO_QAD0_S_GATOS_PAR_H_RMSK)
#define HWIO_QAD0_S_GATOS_PAR_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_GATOS_PAR_H_ADDR(x), m)
#define HWIO_QAD0_S_GATOS_PAR_H_MEMATTR_BMSK                            0xff000000
#define HWIO_QAD0_S_GATOS_PAR_H_MEMATTR_SHFT                                  0x18
#define HWIO_QAD0_S_GATOS_PAR_H_ADDR_BMSK                                   0xffff
#define HWIO_QAD0_S_GATOS_PAR_H_ADDR_SHFT                                      0x0

#define HWIO_QAD0_S_QCR0_ADDR(x)                                        ((x) + 0x00009000)
#define HWIO_QAD0_S_QCR0_PHYS(x)                                        ((x) + 0x00009000)
#define HWIO_QAD0_S_QCR0_RMSK                                                 0x1e
#define HWIO_QAD0_S_QCR0_POR                                            0x00000012
#define HWIO_QAD0_S_QCR0_POR_RMSK                                       0xffffffff
#define HWIO_QAD0_S_QCR0_ATTR                                                  0x3
#define HWIO_QAD0_S_QCR0_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QCR0_ADDR(x), HWIO_QAD0_S_QCR0_RMSK)
#define HWIO_QAD0_S_QCR0_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QCR0_ADDR(x), m)
#define HWIO_QAD0_S_QCR0_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QCR0_ADDR(x),v)
#define HWIO_QAD0_S_QCR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QCR0_ADDR(x),m,v,HWIO_QAD0_S_QCR0_IN(x))
#define HWIO_QAD0_S_QCR0_CMDQ_SYNC_RESP_TRK_DIS_BMSK                          0x10
#define HWIO_QAD0_S_QCR0_CMDQ_SYNC_RESP_TRK_DIS_SHFT                           0x4
#define HWIO_QAD0_S_QCR0_STALL_ON_CMDQ_SYNC_BMSK                               0x8
#define HWIO_QAD0_S_QCR0_STALL_ON_CMDQ_SYNC_SHFT                               0x3
#define HWIO_QAD0_S_QCR0_NSCFGEE_BMSK                                          0x4
#define HWIO_QAD0_S_QCR0_NSCFGEE_SHFT                                          0x2
#define HWIO_QAD0_S_QCR0_AHB_ERROR_REPORT_EN_BMSK                              0x2
#define HWIO_QAD0_S_QCR0_AHB_ERROR_REPORT_EN_SHFT                              0x1

#define HWIO_QAD0_S_QTABLE_ACR1_ADDR(x)                                 ((x) + 0x00009020)
#define HWIO_QAD0_S_QTABLE_ACR1_PHYS(x)                                 ((x) + 0x00009020)
#define HWIO_QAD0_S_QTABLE_ACR1_RMSK                                           0x7
#define HWIO_QAD0_S_QTABLE_ACR1_POR                                     0x00000000
#define HWIO_QAD0_S_QTABLE_ACR1_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_QTABLE_ACR1_ATTR                                           0x3
#define HWIO_QAD0_S_QTABLE_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QTABLE_ACR1_ADDR(x), HWIO_QAD0_S_QTABLE_ACR1_RMSK)
#define HWIO_QAD0_S_QTABLE_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QTABLE_ACR1_ADDR(x), m)
#define HWIO_QAD0_S_QTABLE_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QTABLE_ACR1_ADDR(x),v)
#define HWIO_QAD0_S_QTABLE_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QTABLE_ACR1_ADDR(x),m,v,HWIO_QAD0_S_QTABLE_ACR1_IN(x))
#define HWIO_QAD0_S_QTABLE_ACR1_TRCFG_BMSK                                     0x4
#define HWIO_QAD0_S_QTABLE_ACR1_TRCFG_SHFT                                     0x2
#define HWIO_QAD0_S_QTABLE_ACR1_REQPRIORITY_BMSK                               0x3
#define HWIO_QAD0_S_QTABLE_ACR1_REQPRIORITY_SHFT                               0x0

#define HWIO_QAD0_S_QQUEUE_ACR1_ADDR(x)                                 ((x) + 0x00009024)
#define HWIO_QAD0_S_QQUEUE_ACR1_PHYS(x)                                 ((x) + 0x00009024)
#define HWIO_QAD0_S_QQUEUE_ACR1_RMSK                                           0x7
#define HWIO_QAD0_S_QQUEUE_ACR1_POR                                     0x00000000
#define HWIO_QAD0_S_QQUEUE_ACR1_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_QQUEUE_ACR1_ATTR                                           0x3
#define HWIO_QAD0_S_QQUEUE_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QQUEUE_ACR1_ADDR(x), HWIO_QAD0_S_QQUEUE_ACR1_RMSK)
#define HWIO_QAD0_S_QQUEUE_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QQUEUE_ACR1_ADDR(x), m)
#define HWIO_QAD0_S_QQUEUE_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QQUEUE_ACR1_ADDR(x),v)
#define HWIO_QAD0_S_QQUEUE_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QQUEUE_ACR1_ADDR(x),m,v,HWIO_QAD0_S_QQUEUE_ACR1_IN(x))
#define HWIO_QAD0_S_QQUEUE_ACR1_TRCFG_BMSK                                     0x4
#define HWIO_QAD0_S_QQUEUE_ACR1_TRCFG_SHFT                                     0x2
#define HWIO_QAD0_S_QQUEUE_ACR1_REQPRIORITY_BMSK                               0x3
#define HWIO_QAD0_S_QQUEUE_ACR1_REQPRIORITY_SHFT                               0x0

#define HWIO_QAD0_S_QGERROR_MSI_ACR1_ADDR(x)                            ((x) + 0x00009028)
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_PHYS(x)                            ((x) + 0x00009028)
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_RMSK                                      0xf
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_POR                                0x00000000
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_POR_RMSK                           0xffffffff
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_ATTR                                      0x3
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QGERROR_MSI_ACR1_ADDR(x), HWIO_QAD0_S_QGERROR_MSI_ACR1_RMSK)
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QGERROR_MSI_ACR1_ADDR(x), m)
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QGERROR_MSI_ACR1_ADDR(x),v)
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QGERROR_MSI_ACR1_ADDR(x),m,v,HWIO_QAD0_S_QGERROR_MSI_ACR1_IN(x))
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_WA_BMSK                                   0x8
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_WA_SHFT                                   0x3
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_TRCFG_BMSK                                0x4
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_TRCFG_SHFT                                0x2
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_REQPRIORITY_BMSK                          0x3
#define HWIO_QAD0_S_QGERROR_MSI_ACR1_REQPRIORITY_SHFT                          0x0

#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_ADDR(x)                              ((x) + 0x0000902c)
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_PHYS(x)                              ((x) + 0x0000902c)
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_RMSK                                        0xf
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_POR                                  0x00000000
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_POR_RMSK                             0xffffffff
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_ATTR                                        0x3
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QCMDQ_MSI_ACR1_ADDR(x), HWIO_QAD0_S_QCMDQ_MSI_ACR1_RMSK)
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QCMDQ_MSI_ACR1_ADDR(x), m)
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QCMDQ_MSI_ACR1_ADDR(x),v)
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QCMDQ_MSI_ACR1_ADDR(x),m,v,HWIO_QAD0_S_QCMDQ_MSI_ACR1_IN(x))
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_WA_BMSK                                     0x8
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_WA_SHFT                                     0x3
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_TRCFG_BMSK                                  0x4
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_TRCFG_SHFT                                  0x2
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_REQPRIORITY_BMSK                            0x3
#define HWIO_QAD0_S_QCMDQ_MSI_ACR1_REQPRIORITY_SHFT                            0x0

#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_ADDR(x)                            ((x) + 0x00009030)
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_PHYS(x)                            ((x) + 0x00009030)
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_RMSK                                      0xf
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_POR                                0x00000000
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_POR_RMSK                           0xffffffff
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_ATTR                                      0x3
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QEVENTQ_MSI_ACR1_ADDR(x), HWIO_QAD0_S_QEVENTQ_MSI_ACR1_RMSK)
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QEVENTQ_MSI_ACR1_ADDR(x), m)
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QEVENTQ_MSI_ACR1_ADDR(x),v)
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QEVENTQ_MSI_ACR1_ADDR(x),m,v,HWIO_QAD0_S_QEVENTQ_MSI_ACR1_IN(x))
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_WA_BMSK                                   0x8
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_WA_SHFT                                   0x3
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_TRCFG_BMSK                                0x4
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_TRCFG_SHFT                                0x2
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_REQPRIORITY_BMSK                          0x3
#define HWIO_QAD0_S_QEVENTQ_MSI_ACR1_REQPRIORITY_SHFT                          0x0

#define HWIO_QAD0_S_QGERROR_ADDR(x)                                     ((x) + 0x0000903c)
#define HWIO_QAD0_S_QGERROR_PHYS(x)                                     ((x) + 0x0000903c)
#define HWIO_QAD0_S_QGERROR_RMSK                                        0xfffff803
#define HWIO_QAD0_S_QGERROR_POR                                         0x00000000
#define HWIO_QAD0_S_QGERROR_POR_RMSK                                    0xffffffff
#define HWIO_QAD0_S_QGERROR_ATTR                                               0x1
#define HWIO_QAD0_S_QGERROR_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QGERROR_ADDR(x), HWIO_QAD0_S_QGERROR_RMSK)
#define HWIO_QAD0_S_QGERROR_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QGERROR_ADDR(x), m)
#define HWIO_QAD0_S_QGERROR_SYNDROME_CFG_BMSK                           0xffffe000
#define HWIO_QAD0_S_QGERROR_SYNDROME_CFG_SHFT                                  0xd
#define HWIO_QAD0_S_QGERROR_SYNDROME_PMCG_BMSK                              0x1800
#define HWIO_QAD0_S_QGERROR_SYNDROME_PMCG_SHFT                                 0xb
#define HWIO_QAD0_S_QGERROR_MSI_PMCG_ABT_ERR_BMSK                              0x2
#define HWIO_QAD0_S_QGERROR_MSI_PMCG_ABT_ERR_SHFT                              0x1
#define HWIO_QAD0_S_QGERROR_CFG_FAULT_BMSK                                     0x1
#define HWIO_QAD0_S_QGERROR_CFG_FAULT_SHFT                                     0x0

#define HWIO_QAD0_S_QGERROR_RST_ADDR(x)                                 ((x) + 0x00009040)
#define HWIO_QAD0_S_QGERROR_RST_PHYS(x)                                 ((x) + 0x00009040)
#define HWIO_QAD0_S_QGERROR_RST_RMSK                                           0x3
#define HWIO_QAD0_S_QGERROR_RST_POR                                     0x00000000
#define HWIO_QAD0_S_QGERROR_RST_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_QGERROR_RST_ATTR                                           0x2
#define HWIO_QAD0_S_QGERROR_RST_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QGERROR_RST_ADDR(x),v)
#define HWIO_QAD0_S_QGERROR_RST_MSI_PMCG_ABT_ERR_BMSK                          0x2
#define HWIO_QAD0_S_QGERROR_RST_MSI_PMCG_ABT_ERR_SHFT                          0x1
#define HWIO_QAD0_S_QGERROR_RST_CFG_FAULT_BMSK                                 0x1
#define HWIO_QAD0_S_QGERROR_RST_CFG_FAULT_SHFT                                 0x0

#define HWIO_QAD0_S_QGITS_GBPA_ADDR(x)                                  ((x) + 0x00009050)
#define HWIO_QAD0_S_QGITS_GBPA_PHYS(x)                                  ((x) + 0x00009050)
#define HWIO_QAD0_S_QGITS_GBPA_RMSK                                     0x801f3f1f
#define HWIO_QAD0_S_QGITS_GBPA_POR                                      0x00002010
#define HWIO_QAD0_S_QGITS_GBPA_POR_RMSK                                 0xffffffff
#define HWIO_QAD0_S_QGITS_GBPA_ATTR                                            0x3
#define HWIO_QAD0_S_QGITS_GBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QGITS_GBPA_ADDR(x), HWIO_QAD0_S_QGITS_GBPA_RMSK)
#define HWIO_QAD0_S_QGITS_GBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QGITS_GBPA_ADDR(x), m)
#define HWIO_QAD0_S_QGITS_GBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QGITS_GBPA_ADDR(x),v)
#define HWIO_QAD0_S_QGITS_GBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QGITS_GBPA_ADDR(x),m,v,HWIO_QAD0_S_QGITS_GBPA_IN(x))
#define HWIO_QAD0_S_QGITS_GBPA_UPDATE_BMSK                              0x80000000
#define HWIO_QAD0_S_QGITS_GBPA_UPDATE_SHFT                                    0x1f
#define HWIO_QAD0_S_QGITS_GBPA_ABORT_BMSK                                 0x100000
#define HWIO_QAD0_S_QGITS_GBPA_ABORT_SHFT                                     0x14
#define HWIO_QAD0_S_QGITS_GBPA_INSTCFG_BMSK                                0xc0000
#define HWIO_QAD0_S_QGITS_GBPA_INSTCFG_SHFT                                   0x12
#define HWIO_QAD0_S_QGITS_GBPA_PRIVCFG_BMSK                                0x30000
#define HWIO_QAD0_S_QGITS_GBPA_PRIVCFG_SHFT                                   0x10
#define HWIO_QAD0_S_QGITS_GBPA_SHCFG_BMSK                                   0x3000
#define HWIO_QAD0_S_QGITS_GBPA_SHCFG_SHFT                                      0xc
#define HWIO_QAD0_S_QGITS_GBPA_ALLOCCFG_BMSK                                 0xf00
#define HWIO_QAD0_S_QGITS_GBPA_ALLOCCFG_SHFT                                   0x8
#define HWIO_QAD0_S_QGITS_GBPA_MTCFG_BMSK                                     0x10
#define HWIO_QAD0_S_QGITS_GBPA_MTCFG_SHFT                                      0x4
#define HWIO_QAD0_S_QGITS_GBPA_MEMATTR_BMSK                                    0xf
#define HWIO_QAD0_S_QGITS_GBPA_MEMATTR_SHFT                                    0x0

#define HWIO_QAD0_S_QGITS_AGBPA_ADDR(x)                                 ((x) + 0x00009054)
#define HWIO_QAD0_S_QGITS_AGBPA_PHYS(x)                                 ((x) + 0x00009054)
#define HWIO_QAD0_S_QGITS_AGBPA_RMSK                                       0x7ffff
#define HWIO_QAD0_S_QGITS_AGBPA_POR                                     0x00000000
#define HWIO_QAD0_S_QGITS_AGBPA_POR_RMSK                                0xffffffff
#define HWIO_QAD0_S_QGITS_AGBPA_ATTR                                           0x3
#define HWIO_QAD0_S_QGITS_AGBPA_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QGITS_AGBPA_ADDR(x), HWIO_QAD0_S_QGITS_AGBPA_RMSK)
#define HWIO_QAD0_S_QGITS_AGBPA_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QGITS_AGBPA_ADDR(x), m)
#define HWIO_QAD0_S_QGITS_AGBPA_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QGITS_AGBPA_ADDR(x),v)
#define HWIO_QAD0_S_QGITS_AGBPA_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QGITS_AGBPA_ADDR(x),m,v,HWIO_QAD0_S_QGITS_AGBPA_IN(x))
#define HWIO_QAD0_S_QGITS_AGBPA_REQPRIORITY_BMSK                           0x60000
#define HWIO_QAD0_S_QGITS_AGBPA_REQPRIORITY_SHFT                              0x11
#define HWIO_QAD0_S_QGITS_AGBPA_REQPRIORITY_REPLACE_BMSK                   0x10000
#define HWIO_QAD0_S_QGITS_AGBPA_REQPRIORITY_REPLACE_SHFT                      0x10
#define HWIO_QAD0_S_QGITS_AGBPA_BPVMID_BMSK                                 0xffff
#define HWIO_QAD0_S_QGITS_AGBPA_BPVMID_SHFT                                    0x0

#define HWIO_QAD0_S_QDEVICEID_ADDR(x)                                   ((x) + 0x00009058)
#define HWIO_QAD0_S_QDEVICEID_PHYS(x)                                   ((x) + 0x00009058)
#define HWIO_QAD0_S_QDEVICEID_RMSK                                      0xffffffff
#define HWIO_QAD0_S_QDEVICEID_POR                                       0x00000000
#define HWIO_QAD0_S_QDEVICEID_POR_RMSK                                  0xffffffff
#define HWIO_QAD0_S_QDEVICEID_ATTR                                             0x3
#define HWIO_QAD0_S_QDEVICEID_IN(x)      \
        in_dword_masked(HWIO_QAD0_S_QDEVICEID_ADDR(x), HWIO_QAD0_S_QDEVICEID_RMSK)
#define HWIO_QAD0_S_QDEVICEID_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_S_QDEVICEID_ADDR(x), m)
#define HWIO_QAD0_S_QDEVICEID_OUT(x, v)      \
        out_dword(HWIO_QAD0_S_QDEVICEID_ADDR(x),v)
#define HWIO_QAD0_S_QDEVICEID_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_S_QDEVICEID_ADDR(x),m,v,HWIO_QAD0_S_QDEVICEID_IN(x))
#define HWIO_QAD0_S_QDEVICEID_DEVICEID_BMSK                             0xffffffff
#define HWIO_QAD0_S_QDEVICEID_DEVICEID_SHFT                                    0x0

#define QSMMU_QSMMUV3_GLOBALREG_SPACE1_REG_BASE                     (QSMMUV3_BASE      + 0x00010000)
#define QSMMU_QSMMUV3_GLOBALREG_SPACE1_REG_BASE_PHYS                (QSMMUV3_BASE_PHYS + 0x00010000)

#define HWIO_EVENTQ_PROD_ADDR(x)                                    ((x) + 0x000000a8)
#define HWIO_EVENTQ_PROD_PHYS(x)                                    ((x) + 0x000000a8)
#define HWIO_EVENTQ_PROD_RMSK                                       0x800fffff
#define HWIO_EVENTQ_PROD_POR                                        0x00000000
#define HWIO_EVENTQ_PROD_POR_RMSK                                   0xffffffff
#define HWIO_EVENTQ_PROD_ATTR                                              0x3
#define HWIO_EVENTQ_PROD_IN(x)      \
        in_dword_masked(HWIO_EVENTQ_PROD_ADDR(x), HWIO_EVENTQ_PROD_RMSK)
#define HWIO_EVENTQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_EVENTQ_PROD_ADDR(x), m)
#define HWIO_EVENTQ_PROD_OUT(x, v)      \
        out_dword(HWIO_EVENTQ_PROD_ADDR(x),v)
#define HWIO_EVENTQ_PROD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EVENTQ_PROD_ADDR(x),m,v,HWIO_EVENTQ_PROD_IN(x))
#define HWIO_EVENTQ_PROD_OVFLG_BMSK                                 0x80000000
#define HWIO_EVENTQ_PROD_OVFLG_SHFT                                       0x1f
#define HWIO_EVENTQ_PROD_WR_INDEX_AND_WRAP_BMSK                        0xfffff
#define HWIO_EVENTQ_PROD_WR_INDEX_AND_WRAP_SHFT                            0x0

#define HWIO_EVENTQ_CONS_ADDR(x)                                    ((x) + 0x000000ac)
#define HWIO_EVENTQ_CONS_PHYS(x)                                    ((x) + 0x000000ac)
#define HWIO_EVENTQ_CONS_RMSK                                       0x800fffff
#define HWIO_EVENTQ_CONS_POR                                        0x00000000
#define HWIO_EVENTQ_CONS_POR_RMSK                                   0xffffffff
#define HWIO_EVENTQ_CONS_ATTR                                              0x3
#define HWIO_EVENTQ_CONS_IN(x)      \
        in_dword_masked(HWIO_EVENTQ_CONS_ADDR(x), HWIO_EVENTQ_CONS_RMSK)
#define HWIO_EVENTQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_EVENTQ_CONS_ADDR(x), m)
#define HWIO_EVENTQ_CONS_OUT(x, v)      \
        out_dword(HWIO_EVENTQ_CONS_ADDR(x),v)
#define HWIO_EVENTQ_CONS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_EVENTQ_CONS_ADDR(x),m,v,HWIO_EVENTQ_CONS_IN(x))
#define HWIO_EVENTQ_CONS_OVACKFLG_BMSK                              0x80000000
#define HWIO_EVENTQ_CONS_OVACKFLG_SHFT                                    0x1f
#define HWIO_EVENTQ_CONS_RD_INDEX_AND_WRAP_BMSK                        0xfffff
#define HWIO_EVENTQ_CONS_RD_INDEX_AND_WRAP_SHFT                            0x0

#define HWIO_PRIQ_PROD_ADDR(x)                                      ((x) + 0x000000c8)
#define HWIO_PRIQ_PROD_PHYS(x)                                      ((x) + 0x000000c8)
#define HWIO_PRIQ_PROD_RMSK                                         0x800fffff
#define HWIO_PRIQ_PROD_POR                                          0x00000000
#define HWIO_PRIQ_PROD_POR_RMSK                                     0xffffffff
#define HWIO_PRIQ_PROD_ATTR                                                0x1
#define HWIO_PRIQ_PROD_IN(x)      \
        in_dword_masked(HWIO_PRIQ_PROD_ADDR(x), HWIO_PRIQ_PROD_RMSK)
#define HWIO_PRIQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_PRIQ_PROD_ADDR(x), m)
#define HWIO_PRIQ_PROD_OVFLG_BMSK                                   0x80000000
#define HWIO_PRIQ_PROD_OVFLG_SHFT                                         0x1f
#define HWIO_PRIQ_PROD_WR_INDEX_AND_WRAP_BMSK                          0xfffff
#define HWIO_PRIQ_PROD_WR_INDEX_AND_WRAP_SHFT                              0x0

#define HWIO_PRIQ_CONS_ADDR(x)                                      ((x) + 0x000000cc)
#define HWIO_PRIQ_CONS_PHYS(x)                                      ((x) + 0x000000cc)
#define HWIO_PRIQ_CONS_RMSK                                         0x800fffff
#define HWIO_PRIQ_CONS_POR                                          0x00000000
#define HWIO_PRIQ_CONS_POR_RMSK                                     0xffffffff
#define HWIO_PRIQ_CONS_ATTR                                                0x1
#define HWIO_PRIQ_CONS_IN(x)      \
        in_dword_masked(HWIO_PRIQ_CONS_ADDR(x), HWIO_PRIQ_CONS_RMSK)
#define HWIO_PRIQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_PRIQ_CONS_ADDR(x), m)
#define HWIO_PRIQ_CONS_OVACKFLG_BMSK                                0x80000000
#define HWIO_PRIQ_CONS_OVACKFLG_SHFT                                      0x1f
#define HWIO_PRIQ_CONS_RD_INDEX_AND_WRAP_BMSK                          0xfffff
#define HWIO_PRIQ_CONS_RD_INDEX_AND_WRAP_SHFT                              0x0

#define HWIO_QAD0_EVENTQ_PROD_ADDR(x)                               ((x) + 0x000000a8)
#define HWIO_QAD0_EVENTQ_PROD_PHYS(x)                               ((x) + 0x000000a8)
#define HWIO_QAD0_EVENTQ_PROD_RMSK                                  0x800fffff
#define HWIO_QAD0_EVENTQ_PROD_POR                                   0x00000000
#define HWIO_QAD0_EVENTQ_PROD_POR_RMSK                              0xffffffff
#define HWIO_QAD0_EVENTQ_PROD_ATTR                                         0x3
#define HWIO_QAD0_EVENTQ_PROD_IN(x)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_PROD_ADDR(x), HWIO_QAD0_EVENTQ_PROD_RMSK)
#define HWIO_QAD0_EVENTQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_PROD_ADDR(x), m)
#define HWIO_QAD0_EVENTQ_PROD_OUT(x, v)      \
        out_dword(HWIO_QAD0_EVENTQ_PROD_ADDR(x),v)
#define HWIO_QAD0_EVENTQ_PROD_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_EVENTQ_PROD_ADDR(x),m,v,HWIO_QAD0_EVENTQ_PROD_IN(x))
#define HWIO_QAD0_EVENTQ_PROD_OVFLG_BMSK                            0x80000000
#define HWIO_QAD0_EVENTQ_PROD_OVFLG_SHFT                                  0x1f
#define HWIO_QAD0_EVENTQ_PROD_WR_INDEX_AND_WRAP_BMSK                   0xfffff
#define HWIO_QAD0_EVENTQ_PROD_WR_INDEX_AND_WRAP_SHFT                       0x0

#define HWIO_QAD0_EVENTQ_CONS_ADDR(x)                               ((x) + 0x000000ac)
#define HWIO_QAD0_EVENTQ_CONS_PHYS(x)                               ((x) + 0x000000ac)
#define HWIO_QAD0_EVENTQ_CONS_RMSK                                  0x800fffff
#define HWIO_QAD0_EVENTQ_CONS_POR                                   0x00000000
#define HWIO_QAD0_EVENTQ_CONS_POR_RMSK                              0xffffffff
#define HWIO_QAD0_EVENTQ_CONS_ATTR                                         0x3
#define HWIO_QAD0_EVENTQ_CONS_IN(x)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_CONS_ADDR(x), HWIO_QAD0_EVENTQ_CONS_RMSK)
#define HWIO_QAD0_EVENTQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_EVENTQ_CONS_ADDR(x), m)
#define HWIO_QAD0_EVENTQ_CONS_OUT(x, v)      \
        out_dword(HWIO_QAD0_EVENTQ_CONS_ADDR(x),v)
#define HWIO_QAD0_EVENTQ_CONS_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_EVENTQ_CONS_ADDR(x),m,v,HWIO_QAD0_EVENTQ_CONS_IN(x))
#define HWIO_QAD0_EVENTQ_CONS_OVACKFLG_BMSK                         0x80000000
#define HWIO_QAD0_EVENTQ_CONS_OVACKFLG_SHFT                               0x1f
#define HWIO_QAD0_EVENTQ_CONS_RD_INDEX_AND_WRAP_BMSK                   0xfffff
#define HWIO_QAD0_EVENTQ_CONS_RD_INDEX_AND_WRAP_SHFT                       0x0

#define HWIO_QAD0_PRIQ_PROD_ADDR(x)                                 ((x) + 0x000000c8)
#define HWIO_QAD0_PRIQ_PROD_PHYS(x)                                 ((x) + 0x000000c8)
#define HWIO_QAD0_PRIQ_PROD_RMSK                                    0x800fffff
#define HWIO_QAD0_PRIQ_PROD_POR                                     0x00000000
#define HWIO_QAD0_PRIQ_PROD_POR_RMSK                                0xffffffff
#define HWIO_QAD0_PRIQ_PROD_ATTR                                           0x1
#define HWIO_QAD0_PRIQ_PROD_IN(x)      \
        in_dword_masked(HWIO_QAD0_PRIQ_PROD_ADDR(x), HWIO_QAD0_PRIQ_PROD_RMSK)
#define HWIO_QAD0_PRIQ_PROD_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PRIQ_PROD_ADDR(x), m)
#define HWIO_QAD0_PRIQ_PROD_OVFLG_BMSK                              0x80000000
#define HWIO_QAD0_PRIQ_PROD_OVFLG_SHFT                                    0x1f
#define HWIO_QAD0_PRIQ_PROD_WR_INDEX_AND_WRAP_BMSK                     0xfffff
#define HWIO_QAD0_PRIQ_PROD_WR_INDEX_AND_WRAP_SHFT                         0x0

#define HWIO_QAD0_PRIQ_CONS_ADDR(x)                                 ((x) + 0x000000cc)
#define HWIO_QAD0_PRIQ_CONS_PHYS(x)                                 ((x) + 0x000000cc)
#define HWIO_QAD0_PRIQ_CONS_RMSK                                    0x800fffff
#define HWIO_QAD0_PRIQ_CONS_POR                                     0x00000000
#define HWIO_QAD0_PRIQ_CONS_POR_RMSK                                0xffffffff
#define HWIO_QAD0_PRIQ_CONS_ATTR                                           0x1
#define HWIO_QAD0_PRIQ_CONS_IN(x)      \
        in_dword_masked(HWIO_QAD0_PRIQ_CONS_ADDR(x), HWIO_QAD0_PRIQ_CONS_RMSK)
#define HWIO_QAD0_PRIQ_CONS_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_PRIQ_CONS_ADDR(x), m)
#define HWIO_QAD0_PRIQ_CONS_OVACKFLG_BMSK                           0x80000000
#define HWIO_QAD0_PRIQ_CONS_OVACKFLG_SHFT                                 0x1f
#define HWIO_QAD0_PRIQ_CONS_RD_INDEX_AND_WRAP_BMSK                     0xfffff
#define HWIO_QAD0_PRIQ_CONS_RD_INDEX_AND_WRAP_SHFT                         0x0

#define QSMMU_QSMMUV3_QSCT_REG_BASE                     (QSMMUV3_BASE      + 0x00020000)
#define QSMMU_QSMMUV3_QSCT_REG_BASE_PHYS                (QSMMUV3_BASE_PHYS + 0x00020000)

#define HWIO_ALLOC_QACTn_ADDR(base,n)                   ((base) + 0x00000000 + 0x4 * (n))
#define HWIO_ALLOC_QACTn_PHYS(base,n)                   ((base) + 0x00000000 + 0x4 * (n))
#define HWIO_ALLOC_QACTn_RMSK                           0xffffffff
#define HWIO_ALLOC_QACTn_MAXn                                    7
#define HWIO_ALLOC_QACTn_POR                            0x00000000
#define HWIO_ALLOC_QACTn_POR_RMSK                       0xffffffff
#define HWIO_ALLOC_QACTn_ATTR                                  0x3
#define HWIO_ALLOC_QACTn_INI(base,n)        \
        in_dword_masked(HWIO_ALLOC_QACTn_ADDR(base,n), HWIO_ALLOC_QACTn_RMSK)
#define HWIO_ALLOC_QACTn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_ALLOC_QACTn_ADDR(base,n), mask)
#define HWIO_ALLOC_QACTn_OUTI(base,n,val)    \
        out_dword(HWIO_ALLOC_QACTn_ADDR(base,n),val)
#define HWIO_ALLOC_QACTn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_ALLOC_QACTn_ADDR(base,n),mask,val,HWIO_ALLOC_QACTn_INI(base,n))
#define HWIO_ALLOC_QACTn_QACT_INDEX_BMSK                0xffffffff
#define HWIO_ALLOC_QACTn_QACT_INDEX_SHFT                       0x0

#define HWIO_FREE_QACTn_ADDR(base,n)                    ((base) + 0x00002000 + 0x4 * (n))
#define HWIO_FREE_QACTn_PHYS(base,n)                    ((base) + 0x00002000 + 0x4 * (n))
#define HWIO_FREE_QACTn_RMSK                            0xffffffff
#define HWIO_FREE_QACTn_MAXn                                     7
#define HWIO_FREE_QACTn_POR                             0x00000000
#define HWIO_FREE_QACTn_POR_RMSK                        0xffffffff
#define HWIO_FREE_QACTn_ATTR                                   0x3
#define HWIO_FREE_QACTn_INI(base,n)        \
        in_dword_masked(HWIO_FREE_QACTn_ADDR(base,n), HWIO_FREE_QACTn_RMSK)
#define HWIO_FREE_QACTn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_FREE_QACTn_ADDR(base,n), mask)
#define HWIO_FREE_QACTn_OUTI(base,n,val)    \
        out_dword(HWIO_FREE_QACTn_ADDR(base,n),val)
#define HWIO_FREE_QACTn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_FREE_QACTn_ADDR(base,n),mask,val,HWIO_FREE_QACTn_INI(base,n))
#define HWIO_FREE_QACTn_QACT_INDEX_BMSK                 0xffffffff
#define HWIO_FREE_QACTn_QACT_INDEX_SHFT                        0x0

#define QSMMU_QSMMUV3_IMPDEF_REG_BASE                                             (QSMMUV3_BASE      + 0x00028000)
#define QSMMU_QSMMUV3_IMPDEF_REG_BASE_PHYS                                        (QSMMUV3_BASE_PHYS + 0x00028000)

#define HWIO_QGLOBAL_CR0_ADDR(x)                                                  ((x) + 0x00000000)
#define HWIO_QGLOBAL_CR0_PHYS(x)                                                  ((x) + 0x00000000)
#define HWIO_QGLOBAL_CR0_RMSK                                                      0x1ffffff
#define HWIO_QGLOBAL_CR0_POR                                                      0x0021f249
#define HWIO_QGLOBAL_CR0_POR_RMSK                                                 0xffffffff
#define HWIO_QGLOBAL_CR0_ATTR                                                            0x3
#define HWIO_QGLOBAL_CR0_IN(x)      \
        in_dword_masked(HWIO_QGLOBAL_CR0_ADDR(x), HWIO_QGLOBAL_CR0_RMSK)
#define HWIO_QGLOBAL_CR0_INM(x, m)      \
        in_dword_masked(HWIO_QGLOBAL_CR0_ADDR(x), m)
#define HWIO_QGLOBAL_CR0_OUT(x, v)      \
        out_dword(HWIO_QGLOBAL_CR0_ADDR(x),v)
#define HWIO_QGLOBAL_CR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGLOBAL_CR0_ADDR(x),m,v,HWIO_QGLOBAL_CR0_IN(x))
#define HWIO_QGLOBAL_CR0_ATS_NF_CACHE_DIS_BMSK                                     0x1000000
#define HWIO_QGLOBAL_CR0_ATS_NF_CACHE_DIS_SHFT                                          0x18
#define HWIO_QGLOBAL_CR0_CLU_EXIT_ON_CANCEL_BMSK                                    0x800000
#define HWIO_QGLOBAL_CR0_CLU_EXIT_ON_CANCEL_SHFT                                        0x17
#define HWIO_QGLOBAL_CR0_CMDQ_MULT_TRAN_PER_BUS_EN_BMSK                             0x400000
#define HWIO_QGLOBAL_CR0_CMDQ_MULT_TRAN_PER_BUS_EN_SHFT                                 0x16
#define HWIO_QGLOBAL_CR0_CLU_BUS_OPT_STE_FWD_EN_BMSK                                0x200000
#define HWIO_QGLOBAL_CR0_CLU_BUS_OPT_STE_FWD_EN_SHFT                                    0x15
#define HWIO_QGLOBAL_CR0_CLU_NO_CD_FILL_IF_NO_CD_BMSK                               0x100000
#define HWIO_QGLOBAL_CR0_CLU_NO_CD_FILL_IF_NO_CD_SHFT                                   0x14
#define HWIO_QGLOBAL_CR0_DROP_LA_ALWAYS_BMSK                                         0x80000
#define HWIO_QGLOBAL_CR0_DROP_LA_ALWAYS_SHFT                                            0x13
#define HWIO_QGLOBAL_CR0_DROP_LA_WHEN_BUSY_BMSK                                      0x40000
#define HWIO_QGLOBAL_CR0_DROP_LA_WHEN_BUSY_SHFT                                         0x12
#define HWIO_QGLOBAL_CR0_ABAR_SEND_PA_DIS_BMSK                                       0x20000
#define HWIO_QGLOBAL_CR0_ABAR_SEND_PA_DIS_SHFT                                          0x11
#define HWIO_QGLOBAL_CR0_SLOT_WRITE_RR_EN_BMSK                                       0x10000
#define HWIO_QGLOBAL_CR0_SLOT_WRITE_RR_EN_SHFT                                          0x10
#define HWIO_QGLOBAL_CR0_CLU_ALLOW_TRAN_CANCEL_BMSK                                   0x8000
#define HWIO_QGLOBAL_CR0_CLU_ALLOW_TRAN_CANCEL_SHFT                                      0xf
#define HWIO_QGLOBAL_CR0_CLU_BUS_OPTIMIZATION_EN_BMSK                                 0x4000
#define HWIO_QGLOBAL_CR0_CLU_BUS_OPTIMIZATION_EN_SHFT                                    0xe
#define HWIO_QGLOBAL_CR0_CLIENT_MSI_GEN_BIT_BMSK                                      0x2000
#define HWIO_QGLOBAL_CR0_CLIENT_MSI_GEN_BIT_SHFT                                         0xd
#define HWIO_QGLOBAL_CR0_NATIVE_MSI_GITS_COMPARE_EN_BMSK                              0x1000
#define HWIO_QGLOBAL_CR0_NATIVE_MSI_GITS_COMPARE_EN_SHFT                                 0xc
#define HWIO_QGLOBAL_CR0_CLU_DO_FULL_LOOKUP_ON_PARTIAL_HIT_BMSK                        0x800
#define HWIO_QGLOBAL_CR0_CLU_DO_FULL_LOOKUP_ON_PARTIAL_HIT_SHFT                          0xb
#define HWIO_QGLOBAL_CR0_SYNC_ABAR_RESP_IGNORE_BMSK                                    0x400
#define HWIO_QGLOBAL_CR0_SYNC_ABAR_RESP_IGNORE_SHFT                                      0xa
#define HWIO_QGLOBAL_CR0_HTTU_OVERRIDE_BMSK                                            0x300
#define HWIO_QGLOBAL_CR0_HTTU_OVERRIDE_SHFT                                              0x8
#define HWIO_QGLOBAL_CR0_DEVICE_ATTRIB_OVRD_EN_BMSK                                     0x80
#define HWIO_QGLOBAL_CR0_DEVICE_ATTRIB_OVRD_EN_SHFT                                      0x7
#define HWIO_QGLOBAL_CR0_SKIP_ADDR_HAZ_CHECK_BMSK                                       0x40
#define HWIO_QGLOBAL_CR0_SKIP_ADDR_HAZ_CHECK_SHFT                                        0x6
#define HWIO_QGLOBAL_CR0_PRIQ_INDICATE_SUPPORT_BMSK                                     0x20
#define HWIO_QGLOBAL_CR0_PRIQ_INDICATE_SUPPORT_SHFT                                      0x5
#define HWIO_QGLOBAL_CR0_SYNC_MODE_BMSK                                                 0x18
#define HWIO_QGLOBAL_CR0_SYNC_MODE_SHFT                                                  0x3
#define HWIO_QGLOBAL_CR0_CLU_FAULT_ON_ADDR_SIZE_BMSK                                     0x4
#define HWIO_QGLOBAL_CR0_CLU_FAULT_ON_ADDR_SIZE_SHFT                                     0x2
#define HWIO_QGLOBAL_CR0_S2_FOR_CD_DIS_BMSK                                              0x2
#define HWIO_QGLOBAL_CR0_S2_FOR_CD_DIS_SHFT                                              0x1
#define HWIO_QGLOBAL_CR0_TID_FOR_CFG_LOOKUP_EN_BMSK                                      0x1
#define HWIO_QGLOBAL_CR0_TID_FOR_CFG_LOOKUP_EN_SHFT                                      0x0

#define HWIO_QGLOBAL_CR1_ADDR(x)                                                  ((x) + 0x00000004)
#define HWIO_QGLOBAL_CR1_PHYS(x)                                                  ((x) + 0x00000004)
#define HWIO_QGLOBAL_CR1_RMSK                                                       0xffffff
#define HWIO_QGLOBAL_CR1_POR                                                      0x0021c008
#define HWIO_QGLOBAL_CR1_POR_RMSK                                                 0xffffffff
#define HWIO_QGLOBAL_CR1_ATTR                                                            0x3
#define HWIO_QGLOBAL_CR1_IN(x)      \
        in_dword_masked(HWIO_QGLOBAL_CR1_ADDR(x), HWIO_QGLOBAL_CR1_RMSK)
#define HWIO_QGLOBAL_CR1_INM(x, m)      \
        in_dword_masked(HWIO_QGLOBAL_CR1_ADDR(x), m)
#define HWIO_QGLOBAL_CR1_OUT(x, v)      \
        out_dword(HWIO_QGLOBAL_CR1_ADDR(x),v)
#define HWIO_QGLOBAL_CR1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGLOBAL_CR1_ADDR(x),m,v,HWIO_QGLOBAL_CR1_IN(x))
#define HWIO_QGLOBAL_CR1_RESP_ERR_LIMIT_DISABLE_BMSK                                0x800000
#define HWIO_QGLOBAL_CR1_RESP_ERR_LIMIT_DISABLE_SHFT                                    0x17
#define HWIO_QGLOBAL_CR1_RESP_ERR_COUNT_LIMIT_BMSK                                  0x7c0000
#define HWIO_QGLOBAL_CR1_RESP_ERR_COUNT_LIMIT_SHFT                                      0x12
#define HWIO_QGLOBAL_CR1_DISPATCHER_DISABLE_LAST_SLOT_BMSK                           0x20000
#define HWIO_QGLOBAL_CR1_DISPATCHER_DISABLE_LAST_SLOT_SHFT                              0x11
#define HWIO_QGLOBAL_CR1_DISPATCHER_XLATE4_BYPASS_EN_BMSK                            0x10000
#define HWIO_QGLOBAL_CR1_DISPATCHER_XLATE4_BYPASS_EN_SHFT                               0x10
#define HWIO_QGLOBAL_CR1_DISPATCHER_SPEC_DIS_BMSK                                     0x8000
#define HWIO_QGLOBAL_CR1_DISPATCHER_SPEC_DIS_SHFT                                        0xf
#define HWIO_QGLOBAL_CR1_DISPATCHER_EN_BMSK                                           0x4000
#define HWIO_QGLOBAL_CR1_DISPATCHER_EN_SHFT                                              0xe
#define HWIO_QGLOBAL_CR1_DISPATHER_PAGE_SZ_BMSK                                       0x3000
#define HWIO_QGLOBAL_CR1_DISPATHER_PAGE_SZ_SHFT                                          0xc
#define HWIO_QGLOBAL_CR1_ROB_IGNORE_ORDEREDRD_BMSK                                     0x800
#define HWIO_QGLOBAL_CR1_ROB_IGNORE_ORDEREDRD_SHFT                                       0xb
#define HWIO_QGLOBAL_CR1_ROB_IGNORE_ORDEREDWR_BMSK                                     0x400
#define HWIO_QGLOBAL_CR1_ROB_IGNORE_ORDEREDWR_SHFT                                       0xa
#define HWIO_QGLOBAL_CR1_ROB_FORCE_DEV_TO_FLUSH_ALL_DIS_BMSK                           0x200
#define HWIO_QGLOBAL_CR1_ROB_FORCE_DEV_TO_FLUSH_ALL_DIS_SHFT                             0x9
#define HWIO_QGLOBAL_CR1_ROB_FORCE_EXCL_TO_FLUSH_ALL_DIS_BMSK                          0x100
#define HWIO_QGLOBAL_CR1_ROB_FORCE_EXCL_TO_FLUSH_ALL_DIS_SHFT                            0x8
#define HWIO_QGLOBAL_CR1_ROB_FORCE_DEV_DEP_DIS_BMSK                                     0x80
#define HWIO_QGLOBAL_CR1_ROB_FORCE_DEV_DEP_DIS_SHFT                                      0x7
#define HWIO_QGLOBAL_CR1_ROB_FORCE_EXCL_DEP_DIS_BMSK                                    0x40
#define HWIO_QGLOBAL_CR1_ROB_FORCE_EXCL_DEP_DIS_SHFT                                     0x6
#define HWIO_QGLOBAL_CR1_ROB_GLOBAL_REORDER_DIS_BMSK                                    0x20
#define HWIO_QGLOBAL_CR1_ROB_GLOBAL_REORDER_DIS_SHFT                                     0x5
#define HWIO_QGLOBAL_CR1_RESP_OOO_ERR_INJCT_DIS_BMSK                                    0x10
#define HWIO_QGLOBAL_CR1_RESP_OOO_ERR_INJCT_DIS_SHFT                                     0x4
#define HWIO_QGLOBAL_CR1_RESP_DVM_SYNC_RESP_TRK_DIS_BMSK                                 0x8
#define HWIO_QGLOBAL_CR1_RESP_DVM_SYNC_RESP_TRK_DIS_SHFT                                 0x3
#define HWIO_QGLOBAL_CR1_RESP_STALL_ON_DVM_SYNC_BMSK                                     0x4
#define HWIO_QGLOBAL_CR1_RESP_STALL_ON_DVM_SYNC_SHFT                                     0x2
#define HWIO_QGLOBAL_CR1_RESP_STALL_ON_ERR_BMSK                                          0x2
#define HWIO_QGLOBAL_CR1_RESP_STALL_ON_ERR_SHFT                                          0x1
#define HWIO_QGLOBAL_CR1_RESP_TID_REPL_DIS_BMSK                                          0x1
#define HWIO_QGLOBAL_CR1_RESP_TID_REPL_DIS_SHFT                                          0x0

#define HWIO_QGLOBAL_CR2_ADDR(x)                                                  ((x) + 0x00000008)
#define HWIO_QGLOBAL_CR2_PHYS(x)                                                  ((x) + 0x00000008)
#define HWIO_QGLOBAL_CR2_RMSK                                                     0xe0007ffb
#define HWIO_QGLOBAL_CR2_POR                                                      0xe0000200
#define HWIO_QGLOBAL_CR2_POR_RMSK                                                 0xffffffff
#define HWIO_QGLOBAL_CR2_ATTR                                                            0x3
#define HWIO_QGLOBAL_CR2_IN(x)      \
        in_dword_masked(HWIO_QGLOBAL_CR2_ADDR(x), HWIO_QGLOBAL_CR2_RMSK)
#define HWIO_QGLOBAL_CR2_INM(x, m)      \
        in_dword_masked(HWIO_QGLOBAL_CR2_ADDR(x), m)
#define HWIO_QGLOBAL_CR2_OUT(x, v)      \
        out_dword(HWIO_QGLOBAL_CR2_ADDR(x),v)
#define HWIO_QGLOBAL_CR2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGLOBAL_CR2_ADDR(x),m,v,HWIO_QGLOBAL_CR2_IN(x))
#define HWIO_QGLOBAL_CR2_HTW_STREX_CANCEL_TO_EXIT_BMSK                            0x80000000
#define HWIO_QGLOBAL_CR2_HTW_STREX_CANCEL_TO_EXIT_SHFT                                  0x1f
#define HWIO_QGLOBAL_CR2_HTW_ALLOW_TRAN_CANCEL_BMSK                               0x40000000
#define HWIO_QGLOBAL_CR2_HTW_ALLOW_TRAN_CANCEL_SHFT                                     0x1e
#define HWIO_QGLOBAL_CR2_HTW_PREVENT_DUP_BUSREQ_BMSK                              0x20000000
#define HWIO_QGLOBAL_CR2_HTW_PREVENT_DUP_BUSREQ_SHFT                                    0x1d
#define HWIO_QGLOBAL_CR2_EXCL_LDREX_LOOP_LIMIT_BMSK                                   0x7ff8
#define HWIO_QGLOBAL_CR2_EXCL_LDREX_LOOP_LIMIT_SHFT                                      0x3
#define HWIO_QGLOBAL_CR2_EXCL_RETRY_LDREX_MISMATCH_BMSK                                  0x2
#define HWIO_QGLOBAL_CR2_EXCL_RETRY_LDREX_MISMATCH_SHFT                                  0x1
#define HWIO_QGLOBAL_CR2_EXCL_DO_NEXT_EXCL_ON_EXFAIL_BMSK                                0x1
#define HWIO_QGLOBAL_CR2_EXCL_DO_NEXT_EXCL_ON_EXFAIL_SHFT                                0x0

#define HWIO_QGLOBAL_CR3_ADDR(x)                                                  ((x) + 0x0000000c)
#define HWIO_QGLOBAL_CR3_PHYS(x)                                                  ((x) + 0x0000000c)
#define HWIO_QGLOBAL_CR3_RMSK                                                       0x3fffff
#define HWIO_QGLOBAL_CR3_POR                                                      0x0000f193
#define HWIO_QGLOBAL_CR3_POR_RMSK                                                 0xffffffff
#define HWIO_QGLOBAL_CR3_ATTR                                                            0x3
#define HWIO_QGLOBAL_CR3_IN(x)      \
        in_dword_masked(HWIO_QGLOBAL_CR3_ADDR(x), HWIO_QGLOBAL_CR3_RMSK)
#define HWIO_QGLOBAL_CR3_INM(x, m)      \
        in_dword_masked(HWIO_QGLOBAL_CR3_ADDR(x), m)
#define HWIO_QGLOBAL_CR3_OUT(x, v)      \
        out_dword(HWIO_QGLOBAL_CR3_ADDR(x),v)
#define HWIO_QGLOBAL_CR3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGLOBAL_CR3_ADDR(x),m,v,HWIO_QGLOBAL_CR3_IN(x))
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_THRESHOLD_BMSK                                0x3ff000
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_THRESHOLD_SHFT                                     0xc
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_SMPL_WNDOW_SIZE_BMSK                             0xffc
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_SMPL_WNDOW_SIZE_SHFT                               0x2
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_SYNC_FACTORS_BMSK                                  0x2
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_SYNC_FACTORS_SHFT                                  0x1
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_DIS_FEAT_EN_BMSK                                   0x1
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_DIS_FEAT_EN_SHFT                                   0x0

#define HWIO_QCFG_CACHE_CR_ADDR(x)                                                ((x) + 0x00000018)
#define HWIO_QCFG_CACHE_CR_PHYS(x)                                                ((x) + 0x00000018)
#define HWIO_QCFG_CACHE_CR_RMSK                                                         0x1f
#define HWIO_QCFG_CACHE_CR_POR                                                    0x00000003
#define HWIO_QCFG_CACHE_CR_POR_RMSK                                               0xffffffff
#define HWIO_QCFG_CACHE_CR_ATTR                                                          0x3
#define HWIO_QCFG_CACHE_CR_IN(x)      \
        in_dword_masked(HWIO_QCFG_CACHE_CR_ADDR(x), HWIO_QCFG_CACHE_CR_RMSK)
#define HWIO_QCFG_CACHE_CR_INM(x, m)      \
        in_dword_masked(HWIO_QCFG_CACHE_CR_ADDR(x), m)
#define HWIO_QCFG_CACHE_CR_OUT(x, v)      \
        out_dword(HWIO_QCFG_CACHE_CR_ADDR(x),v)
#define HWIO_QCFG_CACHE_CR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QCFG_CACHE_CR_ADDR(x),m,v,HWIO_QCFG_CACHE_CR_IN(x))
#define HWIO_QCFG_CACHE_CR_CC_LRU_MOVE_BMSK                                             0x10
#define HWIO_QCFG_CACHE_CR_CC_LRU_MOVE_SHFT                                              0x4
#define HWIO_QCFG_CACHE_CR_CC_INS_LRU_PRI_BMSK                                           0x8
#define HWIO_QCFG_CACHE_CR_CC_INS_LRU_PRI_SHFT                                           0x3
#define HWIO_QCFG_CACHE_CR_CC_DIS_MRU_INV_BMSK                                           0x4
#define HWIO_QCFG_CACHE_CR_CC_DIS_MRU_INV_SHFT                                           0x2
#define HWIO_QCFG_CACHE_CR_CC_LRU_EN_BMSK                                                0x2
#define HWIO_QCFG_CACHE_CR_CC_LRU_EN_SHFT                                                0x1
#define HWIO_QCFG_CACHE_CR_CC_EN_BMSK                                                    0x1
#define HWIO_QCFG_CACHE_CR_CC_EN_SHFT                                                    0x0

#define HWIO_QTLBCR_ADDR(x)                                                       ((x) + 0x0000001c)
#define HWIO_QTLBCR_PHYS(x)                                                       ((x) + 0x0000001c)
#define HWIO_QTLBCR_RMSK                                                              0x1fff
#define HWIO_QTLBCR_POR                                                           0x00000999
#define HWIO_QTLBCR_POR_RMSK                                                      0xffffffff
#define HWIO_QTLBCR_ATTR                                                                 0x3
#define HWIO_QTLBCR_IN(x)      \
        in_dword_masked(HWIO_QTLBCR_ADDR(x), HWIO_QTLBCR_RMSK)
#define HWIO_QTLBCR_INM(x, m)      \
        in_dword_masked(HWIO_QTLBCR_ADDR(x), m)
#define HWIO_QTLBCR_OUT(x, v)      \
        out_dword(HWIO_QTLBCR_ADDR(x),v)
#define HWIO_QTLBCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QTLBCR_ADDR(x),m,v,HWIO_QTLBCR_IN(x))
#define HWIO_QTLBCR_TLB_LRU_MOVE_BMSK                                                 0x1000
#define HWIO_QTLBCR_TLB_LRU_MOVE_SHFT                                                    0xc
#define HWIO_QTLBCR_TLB_NESTED_IPA2PA_FILL_DIS_BMSK                                    0x800
#define HWIO_QTLBCR_TLB_NESTED_IPA2PA_FILL_DIS_SHFT                                      0xb
#define HWIO_QTLBCR_TLB_CD_IPA2PA_CACHE_EN_BMSK                                        0x400
#define HWIO_QTLBCR_TLB_CD_IPA2PA_CACHE_EN_SHFT                                          0xa
#define HWIO_QTLBCR_TLB_PERM_FAULT_FILL_EN_BMSK                                        0x200
#define HWIO_QTLBCR_TLB_PERM_FAULT_FILL_EN_SHFT                                          0x9
#define HWIO_QTLBCR_TLB_CONFLICT_CHECK_EN_BMSK                                         0x100
#define HWIO_QTLBCR_TLB_CONFLICT_CHECK_EN_SHFT                                           0x8
#define HWIO_QTLBCR_TLB_DUP_FILL_CHECK_EN_BMSK                                          0x80
#define HWIO_QTLBCR_TLB_DUP_FILL_CHECK_EN_SHFT                                           0x7
#define HWIO_QTLBCR_TLB_INS_LRU_PRI_BMSK                                                0x40
#define HWIO_QTLBCR_TLB_INS_LRU_PRI_SHFT                                                 0x6
#define HWIO_QTLBCR_TLB_DIS_MRU_INV_BMSK                                                0x20
#define HWIO_QTLBCR_TLB_DIS_MRU_INV_SHFT                                                 0x5
#define HWIO_QTLBCR_TLB_LRU_EN_BMSK                                                     0x10
#define HWIO_QTLBCR_TLB_LRU_EN_SHFT                                                      0x4
#define HWIO_QTLBCR_TLB_LEVEL_CACHE_EN_BMSK                                              0x8
#define HWIO_QTLBCR_TLB_LEVEL_CACHE_EN_SHFT                                              0x3
#define HWIO_QTLBCR_TLB_S1_S2_PRT_EN_BMSK                                                0x4
#define HWIO_QTLBCR_TLB_S1_S2_PRT_EN_SHFT                                                0x2
#define HWIO_QTLBCR_TLB_MSTR_PART_EN_BMSK                                                0x2
#define HWIO_QTLBCR_TLB_MSTR_PART_EN_SHFT                                                0x1
#define HWIO_QTLBCR_TLB_EN_BMSK                                                          0x1
#define HWIO_QTLBCR_TLB_EN_SHFT                                                          0x0

#define HWIO_QTLB_RESTART_CTRL_ADDR(x)                                            ((x) + 0x00000020)
#define HWIO_QTLB_RESTART_CTRL_PHYS(x)                                            ((x) + 0x00000020)
#define HWIO_QTLB_RESTART_CTRL_RMSK                                                     0xff
#define HWIO_QTLB_RESTART_CTRL_POR                                                0x00000099
#define HWIO_QTLB_RESTART_CTRL_POR_RMSK                                           0xffffffff
#define HWIO_QTLB_RESTART_CTRL_ATTR                                                      0x3
#define HWIO_QTLB_RESTART_CTRL_IN(x)      \
        in_dword_masked(HWIO_QTLB_RESTART_CTRL_ADDR(x), HWIO_QTLB_RESTART_CTRL_RMSK)
#define HWIO_QTLB_RESTART_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_QTLB_RESTART_CTRL_ADDR(x), m)
#define HWIO_QTLB_RESTART_CTRL_OUT(x, v)      \
        out_dword(HWIO_QTLB_RESTART_CTRL_ADDR(x),v)
#define HWIO_QTLB_RESTART_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QTLB_RESTART_CTRL_ADDR(x),m,v,HWIO_QTLB_RESTART_CTRL_IN(x))
#define HWIO_QTLB_RESTART_CTRL_S2_PAGESIZE_BMSK                                         0xf0
#define HWIO_QTLB_RESTART_CTRL_S2_PAGESIZE_SHFT                                          0x4
#define HWIO_QTLB_RESTART_CTRL_S1_PAGESIZE_BMSK                                          0xf
#define HWIO_QTLB_RESTART_CTRL_S1_PAGESIZE_SHFT                                          0x0

#define HWIO_QTLB_PARTITION_ENDn_ADDR(base,n)                                     ((base) + 0x00000024 + 0x4 * (n))
#define HWIO_QTLB_PARTITION_ENDn_PHYS(base,n)                                     ((base) + 0x00000024 + 0x4 * (n))
#define HWIO_QTLB_PARTITION_ENDn_RMSK                                                  0x1ff
#define HWIO_QTLB_PARTITION_ENDn_MAXn                                                      7
#define HWIO_QTLB_PARTITION_ENDn_POR                                              0x000001ff
#define HWIO_QTLB_PARTITION_ENDn_POR_RMSK                                         0xffffffff
#define HWIO_QTLB_PARTITION_ENDn_ATTR                                                    0x3
#define HWIO_QTLB_PARTITION_ENDn_INI(base,n)        \
        in_dword_masked(HWIO_QTLB_PARTITION_ENDn_ADDR(base,n), HWIO_QTLB_PARTITION_ENDn_RMSK)
#define HWIO_QTLB_PARTITION_ENDn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_QTLB_PARTITION_ENDn_ADDR(base,n), mask)
#define HWIO_QTLB_PARTITION_ENDn_OUTI(base,n,val)    \
        out_dword(HWIO_QTLB_PARTITION_ENDn_ADDR(base,n),val)
#define HWIO_QTLB_PARTITION_ENDn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_QTLB_PARTITION_ENDn_ADDR(base,n),mask,val,HWIO_QTLB_PARTITION_ENDn_INI(base,n))
#define HWIO_QTLB_PARTITION_ENDn_TLB_PARTITION_END_BMSK                                0x1ff
#define HWIO_QTLB_PARTITION_ENDn_TLB_PARTITION_END_SHFT                                  0x0

#define HWIO_QTLB_MODE_TABLE_An_ADDR(base,n)                                      ((base) + 0x00000200 + 0x8 * (n))
#define HWIO_QTLB_MODE_TABLE_An_PHYS(base,n)                                      ((base) + 0x00000200 + 0x8 * (n))
#define HWIO_QTLB_MODE_TABLE_An_RMSK                                               0x7070707
#define HWIO_QTLB_MODE_TABLE_An_MAXn                                                       3
#define HWIO_QTLB_MODE_TABLE_An_POR                                               0x00000000
#define HWIO_QTLB_MODE_TABLE_An_POR_RMSK                                          0xffffffff
#define HWIO_QTLB_MODE_TABLE_An_ATTR                                                     0x3
#define HWIO_QTLB_MODE_TABLE_An_INI(base,n)        \
        in_dword_masked(HWIO_QTLB_MODE_TABLE_An_ADDR(base,n), HWIO_QTLB_MODE_TABLE_An_RMSK)
#define HWIO_QTLB_MODE_TABLE_An_INMI(base,n,mask)    \
        in_dword_masked(HWIO_QTLB_MODE_TABLE_An_ADDR(base,n), mask)
#define HWIO_QTLB_MODE_TABLE_An_OUTI(base,n,val)    \
        out_dword(HWIO_QTLB_MODE_TABLE_An_ADDR(base,n),val)
#define HWIO_QTLB_MODE_TABLE_An_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_QTLB_MODE_TABLE_An_ADDR(base,n),mask,val,HWIO_QTLB_MODE_TABLE_An_INI(base,n))
#define HWIO_QTLB_MODE_TABLE_An_TLB_MODE_TABLE_COL1_BMSK                           0x7000000
#define HWIO_QTLB_MODE_TABLE_An_TLB_MODE_TABLE_COL1_SHFT                                0x18
#define HWIO_QTLB_MODE_TABLE_An_TLB_MODE_TABLE_COL2_BMSK                             0x70000
#define HWIO_QTLB_MODE_TABLE_An_TLB_MODE_TABLE_COL2_SHFT                                0x10
#define HWIO_QTLB_MODE_TABLE_An_TLB_MODE_TABLE_COL3_BMSK                               0x700
#define HWIO_QTLB_MODE_TABLE_An_TLB_MODE_TABLE_COL3_SHFT                                 0x8
#define HWIO_QTLB_MODE_TABLE_An_TLB_MODE_TABLE_COL4_BMSK                                 0x7
#define HWIO_QTLB_MODE_TABLE_An_TLB_MODE_TABLE_COL4_SHFT                                 0x0

#define HWIO_QTLB_MODE_TABLE_Bn_ADDR(base,n)                                      ((base) + 0x00000204 + 0x8 * (n))
#define HWIO_QTLB_MODE_TABLE_Bn_PHYS(base,n)                                      ((base) + 0x00000204 + 0x8 * (n))
#define HWIO_QTLB_MODE_TABLE_Bn_RMSK                                                   0x707
#define HWIO_QTLB_MODE_TABLE_Bn_MAXn                                                       3
#define HWIO_QTLB_MODE_TABLE_Bn_POR                                               0x00000000
#define HWIO_QTLB_MODE_TABLE_Bn_POR_RMSK                                          0xffffffff
#define HWIO_QTLB_MODE_TABLE_Bn_ATTR                                                     0x3
#define HWIO_QTLB_MODE_TABLE_Bn_INI(base,n)        \
        in_dword_masked(HWIO_QTLB_MODE_TABLE_Bn_ADDR(base,n), HWIO_QTLB_MODE_TABLE_Bn_RMSK)
#define HWIO_QTLB_MODE_TABLE_Bn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_QTLB_MODE_TABLE_Bn_ADDR(base,n), mask)
#define HWIO_QTLB_MODE_TABLE_Bn_OUTI(base,n,val)    \
        out_dword(HWIO_QTLB_MODE_TABLE_Bn_ADDR(base,n),val)
#define HWIO_QTLB_MODE_TABLE_Bn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_QTLB_MODE_TABLE_Bn_ADDR(base,n),mask,val,HWIO_QTLB_MODE_TABLE_Bn_INI(base,n))
#define HWIO_QTLB_MODE_TABLE_Bn_TLB_MODE_TABLE_COL5_BMSK                               0x700
#define HWIO_QTLB_MODE_TABLE_Bn_TLB_MODE_TABLE_COL5_SHFT                                 0x8
#define HWIO_QTLB_MODE_TABLE_Bn_TLB_MODE_TABLE_COL6_BMSK                                 0x7
#define HWIO_QTLB_MODE_TABLE_Bn_TLB_MODE_TABLE_COL6_SHFT                                 0x0

#define HWIO_TLBR_CTRL_ADDR(x)                                                    ((x) + 0x00000300)
#define HWIO_TLBR_CTRL_PHYS(x)                                                    ((x) + 0x00000300)
#define HWIO_TLBR_CTRL_RMSK                                                       0xc0000007
#define HWIO_TLBR_CTRL_POR                                                        0x00000000
#define HWIO_TLBR_CTRL_POR_RMSK                                                   0xffffffff
#define HWIO_TLBR_CTRL_ATTR                                                              0x3
#define HWIO_TLBR_CTRL_IN(x)      \
        in_dword_masked(HWIO_TLBR_CTRL_ADDR(x), HWIO_TLBR_CTRL_RMSK)
#define HWIO_TLBR_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_TLBR_CTRL_ADDR(x), m)
#define HWIO_TLBR_CTRL_OUT(x, v)      \
        out_dword(HWIO_TLBR_CTRL_ADDR(x),v)
#define HWIO_TLBR_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TLBR_CTRL_ADDR(x),m,v,HWIO_TLBR_CTRL_IN(x))
#define HWIO_TLBR_CTRL_STATUS_BMSK                                                0xc0000000
#define HWIO_TLBR_CTRL_STATUS_SHFT                                                      0x1e
#define HWIO_TLBR_CTRL_QAD_BMSK                                                          0x4
#define HWIO_TLBR_CTRL_QAD_SHFT                                                          0x2
#define HWIO_TLBR_CTRL_NS_BMSK                                                           0x2
#define HWIO_TLBR_CTRL_NS_SHFT                                                           0x1
#define HWIO_TLBR_CTRL_RUN_BMSK                                                          0x1
#define HWIO_TLBR_CTRL_RUN_SHFT                                                          0x0

#define HWIO_TLBR_ADDR_ADDR(x)                                                    ((x) + 0x00000304)
#define HWIO_TLBR_ADDR_PHYS(x)                                                    ((x) + 0x00000304)
#define HWIO_TLBR_ADDR_RMSK                                                            0x1ff
#define HWIO_TLBR_ADDR_POR                                                        0x00000000
#define HWIO_TLBR_ADDR_POR_RMSK                                                   0xffffffff
#define HWIO_TLBR_ADDR_ATTR                                                              0x3
#define HWIO_TLBR_ADDR_IN(x)      \
        in_dword_masked(HWIO_TLBR_ADDR_ADDR(x), HWIO_TLBR_ADDR_RMSK)
#define HWIO_TLBR_ADDR_INM(x, m)      \
        in_dword_masked(HWIO_TLBR_ADDR_ADDR(x), m)
#define HWIO_TLBR_ADDR_OUT(x, v)      \
        out_dword(HWIO_TLBR_ADDR_ADDR(x),v)
#define HWIO_TLBR_ADDR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_TLBR_ADDR_ADDR(x),m,v,HWIO_TLBR_ADDR_IN(x))
#define HWIO_TLBR_ADDR_TLB_DEBUG_ADDR_BMSK                                             0x1ff
#define HWIO_TLBR_ADDR_TLB_DEBUG_ADDR_SHFT                                               0x0

#define HWIO_TLBR_TAGn_ADDR(base,n)                                               ((base) + 0x00000308 + 0x4 * (n))
#define HWIO_TLBR_TAGn_PHYS(base,n)                                               ((base) + 0x00000308 + 0x4 * (n))
#define HWIO_TLBR_TAGn_RMSK                                                       0xffffffff
#define HWIO_TLBR_TAGn_MAXn                                                                2
#define HWIO_TLBR_TAGn_POR                                                        0x00000000
#define HWIO_TLBR_TAGn_POR_RMSK                                                   0xffffffff
#define HWIO_TLBR_TAGn_ATTR                                                              0x1
#define HWIO_TLBR_TAGn_INI(base,n)        \
        in_dword_masked(HWIO_TLBR_TAGn_ADDR(base,n), HWIO_TLBR_TAGn_RMSK)
#define HWIO_TLBR_TAGn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_TLBR_TAGn_ADDR(base,n), mask)
#define HWIO_TLBR_TAGn_TLB_TAG_BMSK                                               0xffffffff
#define HWIO_TLBR_TAGn_TLB_TAG_SHFT                                                      0x0

#define HWIO_TLBR_DATAn_ADDR(base,n)                                              ((base) + 0x00000314 + 0x4 * (n))
#define HWIO_TLBR_DATAn_PHYS(base,n)                                              ((base) + 0x00000314 + 0x4 * (n))
#define HWIO_TLBR_DATAn_RMSK                                                      0xffffffff
#define HWIO_TLBR_DATAn_MAXn                                                               2
#define HWIO_TLBR_DATAn_POR                                                       0x00000000
#define HWIO_TLBR_DATAn_POR_RMSK                                                  0xffffffff
#define HWIO_TLBR_DATAn_ATTR                                                             0x1
#define HWIO_TLBR_DATAn_INI(base,n)        \
        in_dword_masked(HWIO_TLBR_DATAn_ADDR(base,n), HWIO_TLBR_DATAn_RMSK)
#define HWIO_TLBR_DATAn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_TLBR_DATAn_ADDR(base,n), mask)
#define HWIO_TLBR_DATAn_TLB_DATA_BMSK                                             0xffffffff
#define HWIO_TLBR_DATAn_TLB_DATA_SHFT                                                    0x0

#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_ADDR(x)                            ((x) + 0x00000328)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_PHYS(x)                            ((x) + 0x00000328)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_RMSK                               0xffffffff
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_POR                                0x7eff0040
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_POR_RMSK                           0xffffffff
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_ATTR                                      0x3
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_IN(x)      \
        in_dword_masked(HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_ADDR(x), HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_RMSK)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_INM(x, m)      \
        in_dword_masked(HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_ADDR(x), m)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_OUT(x, v)      \
        out_dword(HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_ADDR(x),v)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_ADDR(x),m,v,HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_IN(x))
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_MSI_ADDR_LOW_BMSK                  0xffffffff
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_LOW_MSI_ADDR_LOW_SHFT                         0x0

#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_ADDR(x)                           ((x) + 0x0000032c)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_PHYS(x)                           ((x) + 0x0000032c)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_RMSK                                   0xfff
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_POR                               0x000000ff
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_POR_RMSK                          0xffffffff
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_ATTR                                     0x3
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_IN(x)      \
        in_dword_masked(HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_ADDR(x), HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_RMSK)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_ADDR(x), m)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_OUT(x, v)      \
        out_dword(HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_ADDR(x),v)
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_ADDR(x),m,v,HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_IN(x))
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_MSI_ADDR_HIGH_BMSK                     0xfff
#define HWIO_NATIVE_MSI_GITS_MATCH_ADDRESS_HIGH_MSI_ADDR_HIGH_SHFT                       0x0

#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_ADDR(x)                                 ((x) + 0x00000330)
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_PHYS(x)                                 ((x) + 0x00000330)
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_RMSK                                    0xffffffff
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_POR                                     0x7eff0040
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_POR_RMSK                                0xffffffff
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_ATTR                                           0x3
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_IN(x)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_MATCH_0_LOW_ADDR(x), HWIO_QGITS_TRANSLATER_MATCH_0_LOW_RMSK)
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_MATCH_0_LOW_ADDR(x), m)
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_OUT(x, v)      \
        out_dword(HWIO_QGITS_TRANSLATER_MATCH_0_LOW_ADDR(x),v)
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGITS_TRANSLATER_MATCH_0_LOW_ADDR(x),m,v,HWIO_QGITS_TRANSLATER_MATCH_0_LOW_IN(x))
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_MSI_ADDR_LOW_BMSK                       0xffffffff
#define HWIO_QGITS_TRANSLATER_MATCH_0_LOW_MSI_ADDR_LOW_SHFT                              0x0

#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_ADDR(x)                                ((x) + 0x00000334)
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_PHYS(x)                                ((x) + 0x00000334)
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_RMSK                                        0xfff
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_POR                                    0x000000ff
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_POR_RMSK                               0xffffffff
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_ATTR                                          0x3
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_IN(x)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_ADDR(x), HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_RMSK)
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_ADDR(x), m)
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_OUT(x, v)      \
        out_dword(HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_ADDR(x),v)
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_ADDR(x),m,v,HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_IN(x))
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_MSI_ADDR_HIGH_BMSK                          0xfff
#define HWIO_QGITS_TRANSLATER_MATCH_0_HIGH_MSI_ADDR_HIGH_SHFT                            0x0

#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_ADDR(x)                                 ((x) + 0x00000338)
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_PHYS(x)                                 ((x) + 0x00000338)
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_RMSK                                    0xffffffff
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_POR                                     0x7eff0040
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_POR_RMSK                                0xffffffff
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_ATTR                                           0x3
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_IN(x)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_MATCH_1_LOW_ADDR(x), HWIO_QGITS_TRANSLATER_MATCH_1_LOW_RMSK)
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_MATCH_1_LOW_ADDR(x), m)
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_OUT(x, v)      \
        out_dword(HWIO_QGITS_TRANSLATER_MATCH_1_LOW_ADDR(x),v)
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGITS_TRANSLATER_MATCH_1_LOW_ADDR(x),m,v,HWIO_QGITS_TRANSLATER_MATCH_1_LOW_IN(x))
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_MSI_ADDR_LOW_BMSK                       0xffffffff
#define HWIO_QGITS_TRANSLATER_MATCH_1_LOW_MSI_ADDR_LOW_SHFT                              0x0

#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_ADDR(x)                                ((x) + 0x0000033c)
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_PHYS(x)                                ((x) + 0x0000033c)
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_RMSK                                        0xfff
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_POR                                    0x000000ff
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_POR_RMSK                               0xffffffff
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_ATTR                                          0x3
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_IN(x)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_ADDR(x), HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_RMSK)
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_ADDR(x), m)
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_OUT(x, v)      \
        out_dword(HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_ADDR(x),v)
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_ADDR(x),m,v,HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_IN(x))
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_MSI_ADDR_HIGH_BMSK                          0xfff
#define HWIO_QGITS_TRANSLATER_MATCH_1_HIGH_MSI_ADDR_HIGH_SHFT                            0x0

#define HWIO_QGITS_TRANSLATER_OUT_LOW_ADDR(x)                                     ((x) + 0x00000340)
#define HWIO_QGITS_TRANSLATER_OUT_LOW_PHYS(x)                                     ((x) + 0x00000340)
#define HWIO_QGITS_TRANSLATER_OUT_LOW_RMSK                                        0xffffffff
#define HWIO_QGITS_TRANSLATER_OUT_LOW_POR                                         0x7eff0040
#define HWIO_QGITS_TRANSLATER_OUT_LOW_POR_RMSK                                    0xffffffff
#define HWIO_QGITS_TRANSLATER_OUT_LOW_ATTR                                               0x3
#define HWIO_QGITS_TRANSLATER_OUT_LOW_IN(x)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_OUT_LOW_ADDR(x), HWIO_QGITS_TRANSLATER_OUT_LOW_RMSK)
#define HWIO_QGITS_TRANSLATER_OUT_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_OUT_LOW_ADDR(x), m)
#define HWIO_QGITS_TRANSLATER_OUT_LOW_OUT(x, v)      \
        out_dword(HWIO_QGITS_TRANSLATER_OUT_LOW_ADDR(x),v)
#define HWIO_QGITS_TRANSLATER_OUT_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGITS_TRANSLATER_OUT_LOW_ADDR(x),m,v,HWIO_QGITS_TRANSLATER_OUT_LOW_IN(x))
#define HWIO_QGITS_TRANSLATER_OUT_LOW_MSI_ADDR_LOW_BMSK                           0xffffffff
#define HWIO_QGITS_TRANSLATER_OUT_LOW_MSI_ADDR_LOW_SHFT                                  0x0

#define HWIO_QGITS_TRANSLATER_OUT_HIGH_ADDR(x)                                    ((x) + 0x00000344)
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_PHYS(x)                                    ((x) + 0x00000344)
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_RMSK                                            0xfff
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_POR                                        0x000000ff
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_POR_RMSK                                   0xffffffff
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_ATTR                                              0x3
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_IN(x)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_OUT_HIGH_ADDR(x), HWIO_QGITS_TRANSLATER_OUT_HIGH_RMSK)
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QGITS_TRANSLATER_OUT_HIGH_ADDR(x), m)
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_OUT(x, v)      \
        out_dword(HWIO_QGITS_TRANSLATER_OUT_HIGH_ADDR(x),v)
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGITS_TRANSLATER_OUT_HIGH_ADDR(x),m,v,HWIO_QGITS_TRANSLATER_OUT_HIGH_IN(x))
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_MSI_ADDR_HIGH_BMSK                              0xfff
#define HWIO_QGITS_TRANSLATER_OUT_HIGH_MSI_ADDR_HIGH_SHFT                                0x0

#define HWIO_QDEVICE_START0_LOW_ADDR(x)                                           ((x) + 0x00000348)
#define HWIO_QDEVICE_START0_LOW_PHYS(x)                                           ((x) + 0x00000348)
#define HWIO_QDEVICE_START0_LOW_RMSK                                              0xffffffff
#define HWIO_QDEVICE_START0_LOW_POR                                               0xffffffff
#define HWIO_QDEVICE_START0_LOW_POR_RMSK                                          0xffffffff
#define HWIO_QDEVICE_START0_LOW_ATTR                                                     0x3
#define HWIO_QDEVICE_START0_LOW_IN(x)      \
        in_dword_masked(HWIO_QDEVICE_START0_LOW_ADDR(x), HWIO_QDEVICE_START0_LOW_RMSK)
#define HWIO_QDEVICE_START0_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICE_START0_LOW_ADDR(x), m)
#define HWIO_QDEVICE_START0_LOW_OUT(x, v)      \
        out_dword(HWIO_QDEVICE_START0_LOW_ADDR(x),v)
#define HWIO_QDEVICE_START0_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICE_START0_LOW_ADDR(x),m,v,HWIO_QDEVICE_START0_LOW_IN(x))
#define HWIO_QDEVICE_START0_LOW_ADDR_LOW_BMSK                                     0xffffffff
#define HWIO_QDEVICE_START0_LOW_ADDR_LOW_SHFT                                            0x0

#define HWIO_QDEVICE_START0_HIGH_ADDR(x)                                          ((x) + 0x0000034c)
#define HWIO_QDEVICE_START0_HIGH_PHYS(x)                                          ((x) + 0x0000034c)
#define HWIO_QDEVICE_START0_HIGH_RMSK                                                  0xfff
#define HWIO_QDEVICE_START0_HIGH_POR                                              0x000000fe
#define HWIO_QDEVICE_START0_HIGH_POR_RMSK                                         0xffffffff
#define HWIO_QDEVICE_START0_HIGH_ATTR                                                    0x3
#define HWIO_QDEVICE_START0_HIGH_IN(x)      \
        in_dword_masked(HWIO_QDEVICE_START0_HIGH_ADDR(x), HWIO_QDEVICE_START0_HIGH_RMSK)
#define HWIO_QDEVICE_START0_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICE_START0_HIGH_ADDR(x), m)
#define HWIO_QDEVICE_START0_HIGH_OUT(x, v)      \
        out_dword(HWIO_QDEVICE_START0_HIGH_ADDR(x),v)
#define HWIO_QDEVICE_START0_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICE_START0_HIGH_ADDR(x),m,v,HWIO_QDEVICE_START0_HIGH_IN(x))
#define HWIO_QDEVICE_START0_HIGH_ADDR_HIGH_BMSK                                        0xfff
#define HWIO_QDEVICE_START0_HIGH_ADDR_HIGH_SHFT                                          0x0

#define HWIO_QDEVICE_END0_LOW_ADDR(x)                                             ((x) + 0x00000350)
#define HWIO_QDEVICE_END0_LOW_PHYS(x)                                             ((x) + 0x00000350)
#define HWIO_QDEVICE_END0_LOW_RMSK                                                0xffffffff
#define HWIO_QDEVICE_END0_LOW_POR                                                 0x6f800000
#define HWIO_QDEVICE_END0_LOW_POR_RMSK                                            0xffffffff
#define HWIO_QDEVICE_END0_LOW_ATTR                                                       0x3
#define HWIO_QDEVICE_END0_LOW_IN(x)      \
        in_dword_masked(HWIO_QDEVICE_END0_LOW_ADDR(x), HWIO_QDEVICE_END0_LOW_RMSK)
#define HWIO_QDEVICE_END0_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICE_END0_LOW_ADDR(x), m)
#define HWIO_QDEVICE_END0_LOW_OUT(x, v)      \
        out_dword(HWIO_QDEVICE_END0_LOW_ADDR(x),v)
#define HWIO_QDEVICE_END0_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICE_END0_LOW_ADDR(x),m,v,HWIO_QDEVICE_END0_LOW_IN(x))
#define HWIO_QDEVICE_END0_LOW_ADDR_LOW_BMSK                                       0xffffffff
#define HWIO_QDEVICE_END0_LOW_ADDR_LOW_SHFT                                              0x0

#define HWIO_QDEVICE_END0_HIGH_ADDR(x)                                            ((x) + 0x00000354)
#define HWIO_QDEVICE_END0_HIGH_PHYS(x)                                            ((x) + 0x00000354)
#define HWIO_QDEVICE_END0_HIGH_RMSK                                                    0xfff
#define HWIO_QDEVICE_END0_HIGH_POR                                                0x000000ff
#define HWIO_QDEVICE_END0_HIGH_POR_RMSK                                           0xffffffff
#define HWIO_QDEVICE_END0_HIGH_ATTR                                                      0x3
#define HWIO_QDEVICE_END0_HIGH_IN(x)      \
        in_dword_masked(HWIO_QDEVICE_END0_HIGH_ADDR(x), HWIO_QDEVICE_END0_HIGH_RMSK)
#define HWIO_QDEVICE_END0_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICE_END0_HIGH_ADDR(x), m)
#define HWIO_QDEVICE_END0_HIGH_OUT(x, v)      \
        out_dword(HWIO_QDEVICE_END0_HIGH_ADDR(x),v)
#define HWIO_QDEVICE_END0_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICE_END0_HIGH_ADDR(x),m,v,HWIO_QDEVICE_END0_HIGH_IN(x))
#define HWIO_QDEVICE_END0_HIGH_ADDR_HIGH_BMSK                                          0xfff
#define HWIO_QDEVICE_END0_HIGH_ADDR_HIGH_SHFT                                            0x0

#define HWIO_QDEVICE_START1_LOW_ADDR(x)                                           ((x) + 0x00000358)
#define HWIO_QDEVICE_START1_LOW_PHYS(x)                                           ((x) + 0x00000358)
#define HWIO_QDEVICE_START1_LOW_RMSK                                              0xffffffff
#define HWIO_QDEVICE_START1_LOW_POR                                               0x704fffff
#define HWIO_QDEVICE_START1_LOW_POR_RMSK                                          0xffffffff
#define HWIO_QDEVICE_START1_LOW_ATTR                                                     0x3
#define HWIO_QDEVICE_START1_LOW_IN(x)      \
        in_dword_masked(HWIO_QDEVICE_START1_LOW_ADDR(x), HWIO_QDEVICE_START1_LOW_RMSK)
#define HWIO_QDEVICE_START1_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICE_START1_LOW_ADDR(x), m)
#define HWIO_QDEVICE_START1_LOW_OUT(x, v)      \
        out_dword(HWIO_QDEVICE_START1_LOW_ADDR(x),v)
#define HWIO_QDEVICE_START1_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICE_START1_LOW_ADDR(x),m,v,HWIO_QDEVICE_START1_LOW_IN(x))
#define HWIO_QDEVICE_START1_LOW_ADDR_LOW_BMSK                                     0xffffffff
#define HWIO_QDEVICE_START1_LOW_ADDR_LOW_SHFT                                            0x0

#define HWIO_QDEVICE_START1_HIGH_ADDR(x)                                          ((x) + 0x0000035c)
#define HWIO_QDEVICE_START1_HIGH_PHYS(x)                                          ((x) + 0x0000035c)
#define HWIO_QDEVICE_START1_HIGH_RMSK                                                  0xfff
#define HWIO_QDEVICE_START1_HIGH_POR                                              0x000000ff
#define HWIO_QDEVICE_START1_HIGH_POR_RMSK                                         0xffffffff
#define HWIO_QDEVICE_START1_HIGH_ATTR                                                    0x3
#define HWIO_QDEVICE_START1_HIGH_IN(x)      \
        in_dword_masked(HWIO_QDEVICE_START1_HIGH_ADDR(x), HWIO_QDEVICE_START1_HIGH_RMSK)
#define HWIO_QDEVICE_START1_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICE_START1_HIGH_ADDR(x), m)
#define HWIO_QDEVICE_START1_HIGH_OUT(x, v)      \
        out_dword(HWIO_QDEVICE_START1_HIGH_ADDR(x),v)
#define HWIO_QDEVICE_START1_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICE_START1_HIGH_ADDR(x),m,v,HWIO_QDEVICE_START1_HIGH_IN(x))
#define HWIO_QDEVICE_START1_HIGH_ADDR_HIGH_BMSK                                        0xfff
#define HWIO_QDEVICE_START1_HIGH_ADDR_HIGH_SHFT                                          0x0

#define HWIO_QDEVICE_END1_LOW_ADDR(x)                                             ((x) + 0x00000360)
#define HWIO_QDEVICE_END1_LOW_PHYS(x)                                             ((x) + 0x00000360)
#define HWIO_QDEVICE_END1_LOW_RMSK                                                0xffffffff
#define HWIO_QDEVICE_END1_LOW_POR                                                 0xa0000000
#define HWIO_QDEVICE_END1_LOW_POR_RMSK                                            0xffffffff
#define HWIO_QDEVICE_END1_LOW_ATTR                                                       0x3
#define HWIO_QDEVICE_END1_LOW_IN(x)      \
        in_dword_masked(HWIO_QDEVICE_END1_LOW_ADDR(x), HWIO_QDEVICE_END1_LOW_RMSK)
#define HWIO_QDEVICE_END1_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICE_END1_LOW_ADDR(x), m)
#define HWIO_QDEVICE_END1_LOW_OUT(x, v)      \
        out_dword(HWIO_QDEVICE_END1_LOW_ADDR(x),v)
#define HWIO_QDEVICE_END1_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICE_END1_LOW_ADDR(x),m,v,HWIO_QDEVICE_END1_LOW_IN(x))
#define HWIO_QDEVICE_END1_LOW_ADDR_LOW_BMSK                                       0xffffffff
#define HWIO_QDEVICE_END1_LOW_ADDR_LOW_SHFT                                              0x0

#define HWIO_QDEVICE_END1_HIGH_ADDR(x)                                            ((x) + 0x00000364)
#define HWIO_QDEVICE_END1_HIGH_PHYS(x)                                            ((x) + 0x00000364)
#define HWIO_QDEVICE_END1_HIGH_RMSK                                                    0xfff
#define HWIO_QDEVICE_END1_HIGH_POR                                                0x000000ff
#define HWIO_QDEVICE_END1_HIGH_POR_RMSK                                           0xffffffff
#define HWIO_QDEVICE_END1_HIGH_ATTR                                                      0x3
#define HWIO_QDEVICE_END1_HIGH_IN(x)      \
        in_dword_masked(HWIO_QDEVICE_END1_HIGH_ADDR(x), HWIO_QDEVICE_END1_HIGH_RMSK)
#define HWIO_QDEVICE_END1_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QDEVICE_END1_HIGH_ADDR(x), m)
#define HWIO_QDEVICE_END1_HIGH_OUT(x, v)      \
        out_dword(HWIO_QDEVICE_END1_HIGH_ADDR(x),v)
#define HWIO_QDEVICE_END1_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QDEVICE_END1_HIGH_ADDR(x),m,v,HWIO_QDEVICE_END1_HIGH_IN(x))
#define HWIO_QDEVICE_END1_HIGH_ADDR_HIGH_BMSK                                          0xfff
#define HWIO_QDEVICE_END1_HIGH_ADDR_HIGH_SHFT                                            0x0

#define HWIO_QGICM_SETSPI_MATCH_LOW_ADDR(x)                                       ((x) + 0x00000368)
#define HWIO_QGICM_SETSPI_MATCH_LOW_PHYS(x)                                       ((x) + 0x00000368)
#define HWIO_QGICM_SETSPI_MATCH_LOW_RMSK                                          0xffffffff
#define HWIO_QGICM_SETSPI_MATCH_LOW_POR                                           0x7efd0040
#define HWIO_QGICM_SETSPI_MATCH_LOW_POR_RMSK                                      0xffffffff
#define HWIO_QGICM_SETSPI_MATCH_LOW_ATTR                                                 0x3
#define HWIO_QGICM_SETSPI_MATCH_LOW_IN(x)      \
        in_dword_masked(HWIO_QGICM_SETSPI_MATCH_LOW_ADDR(x), HWIO_QGICM_SETSPI_MATCH_LOW_RMSK)
#define HWIO_QGICM_SETSPI_MATCH_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QGICM_SETSPI_MATCH_LOW_ADDR(x), m)
#define HWIO_QGICM_SETSPI_MATCH_LOW_OUT(x, v)      \
        out_dword(HWIO_QGICM_SETSPI_MATCH_LOW_ADDR(x),v)
#define HWIO_QGICM_SETSPI_MATCH_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGICM_SETSPI_MATCH_LOW_ADDR(x),m,v,HWIO_QGICM_SETSPI_MATCH_LOW_IN(x))
#define HWIO_QGICM_SETSPI_MATCH_LOW_ADDR_LOW_BMSK                                 0xffffffff
#define HWIO_QGICM_SETSPI_MATCH_LOW_ADDR_LOW_SHFT                                        0x0

#define HWIO_QGICM_SETSPI_MATCH_HIGH_ADDR(x)                                      ((x) + 0x0000036c)
#define HWIO_QGICM_SETSPI_MATCH_HIGH_PHYS(x)                                      ((x) + 0x0000036c)
#define HWIO_QGICM_SETSPI_MATCH_HIGH_RMSK                                              0xfff
#define HWIO_QGICM_SETSPI_MATCH_HIGH_POR                                          0x000000ff
#define HWIO_QGICM_SETSPI_MATCH_HIGH_POR_RMSK                                     0xffffffff
#define HWIO_QGICM_SETSPI_MATCH_HIGH_ATTR                                                0x3
#define HWIO_QGICM_SETSPI_MATCH_HIGH_IN(x)      \
        in_dword_masked(HWIO_QGICM_SETSPI_MATCH_HIGH_ADDR(x), HWIO_QGICM_SETSPI_MATCH_HIGH_RMSK)
#define HWIO_QGICM_SETSPI_MATCH_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QGICM_SETSPI_MATCH_HIGH_ADDR(x), m)
#define HWIO_QGICM_SETSPI_MATCH_HIGH_OUT(x, v)      \
        out_dword(HWIO_QGICM_SETSPI_MATCH_HIGH_ADDR(x),v)
#define HWIO_QGICM_SETSPI_MATCH_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGICM_SETSPI_MATCH_HIGH_ADDR(x),m,v,HWIO_QGICM_SETSPI_MATCH_HIGH_IN(x))
#define HWIO_QGICM_SETSPI_MATCH_HIGH_ADDR_HIGH_BMSK                                    0xfff
#define HWIO_QGICM_SETSPI_MATCH_HIGH_ADDR_HIGH_SHFT                                      0x0

#define HWIO_QGICM_CLRSPI_MATCH_LOW_ADDR(x)                                       ((x) + 0x00000370)
#define HWIO_QGICM_CLRSPI_MATCH_LOW_PHYS(x)                                       ((x) + 0x00000370)
#define HWIO_QGICM_CLRSPI_MATCH_LOW_RMSK                                          0xffffffff
#define HWIO_QGICM_CLRSPI_MATCH_LOW_POR                                           0x7efd0048
#define HWIO_QGICM_CLRSPI_MATCH_LOW_POR_RMSK                                      0xffffffff
#define HWIO_QGICM_CLRSPI_MATCH_LOW_ATTR                                                 0x3
#define HWIO_QGICM_CLRSPI_MATCH_LOW_IN(x)      \
        in_dword_masked(HWIO_QGICM_CLRSPI_MATCH_LOW_ADDR(x), HWIO_QGICM_CLRSPI_MATCH_LOW_RMSK)
#define HWIO_QGICM_CLRSPI_MATCH_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QGICM_CLRSPI_MATCH_LOW_ADDR(x), m)
#define HWIO_QGICM_CLRSPI_MATCH_LOW_OUT(x, v)      \
        out_dword(HWIO_QGICM_CLRSPI_MATCH_LOW_ADDR(x),v)
#define HWIO_QGICM_CLRSPI_MATCH_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGICM_CLRSPI_MATCH_LOW_ADDR(x),m,v,HWIO_QGICM_CLRSPI_MATCH_LOW_IN(x))
#define HWIO_QGICM_CLRSPI_MATCH_LOW_ADDR_LOW_BMSK                                 0xffffffff
#define HWIO_QGICM_CLRSPI_MATCH_LOW_ADDR_LOW_SHFT                                        0x0

#define HWIO_QGICM_CLRSPI_MATCH_HIGH_ADDR(x)                                      ((x) + 0x00000374)
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_PHYS(x)                                      ((x) + 0x00000374)
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_RMSK                                              0xfff
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_POR                                          0x000000ff
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_POR_RMSK                                     0xffffffff
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_ATTR                                                0x3
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_IN(x)      \
        in_dword_masked(HWIO_QGICM_CLRSPI_MATCH_HIGH_ADDR(x), HWIO_QGICM_CLRSPI_MATCH_HIGH_RMSK)
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QGICM_CLRSPI_MATCH_HIGH_ADDR(x), m)
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_OUT(x, v)      \
        out_dword(HWIO_QGICM_CLRSPI_MATCH_HIGH_ADDR(x),v)
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGICM_CLRSPI_MATCH_HIGH_ADDR(x),m,v,HWIO_QGICM_CLRSPI_MATCH_HIGH_IN(x))
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_ADDR_HIGH_BMSK                                    0xfff
#define HWIO_QGICM_CLRSPI_MATCH_HIGH_ADDR_HIGH_SHFT                                      0x0

#define HWIO_QGICM_SETSPI_OUT_LOW_ADDR(x)                                         ((x) + 0x00000378)
#define HWIO_QGICM_SETSPI_OUT_LOW_PHYS(x)                                         ((x) + 0x00000378)
#define HWIO_QGICM_SETSPI_OUT_LOW_RMSK                                            0xffffffff
#define HWIO_QGICM_SETSPI_OUT_LOW_POR                                             0x7efd0040
#define HWIO_QGICM_SETSPI_OUT_LOW_POR_RMSK                                        0xffffffff
#define HWIO_QGICM_SETSPI_OUT_LOW_ATTR                                                   0x3
#define HWIO_QGICM_SETSPI_OUT_LOW_IN(x)      \
        in_dword_masked(HWIO_QGICM_SETSPI_OUT_LOW_ADDR(x), HWIO_QGICM_SETSPI_OUT_LOW_RMSK)
#define HWIO_QGICM_SETSPI_OUT_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QGICM_SETSPI_OUT_LOW_ADDR(x), m)
#define HWIO_QGICM_SETSPI_OUT_LOW_OUT(x, v)      \
        out_dword(HWIO_QGICM_SETSPI_OUT_LOW_ADDR(x),v)
#define HWIO_QGICM_SETSPI_OUT_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGICM_SETSPI_OUT_LOW_ADDR(x),m,v,HWIO_QGICM_SETSPI_OUT_LOW_IN(x))
#define HWIO_QGICM_SETSPI_OUT_LOW_ADDR_LOW_BMSK                                   0xffffffff
#define HWIO_QGICM_SETSPI_OUT_LOW_ADDR_LOW_SHFT                                          0x0

#define HWIO_QGICM_SETSPI_OUT_HIGH_ADDR(x)                                        ((x) + 0x0000037c)
#define HWIO_QGICM_SETSPI_OUT_HIGH_PHYS(x)                                        ((x) + 0x0000037c)
#define HWIO_QGICM_SETSPI_OUT_HIGH_RMSK                                                0xfff
#define HWIO_QGICM_SETSPI_OUT_HIGH_POR                                            0x000000ff
#define HWIO_QGICM_SETSPI_OUT_HIGH_POR_RMSK                                       0xffffffff
#define HWIO_QGICM_SETSPI_OUT_HIGH_ATTR                                                  0x3
#define HWIO_QGICM_SETSPI_OUT_HIGH_IN(x)      \
        in_dword_masked(HWIO_QGICM_SETSPI_OUT_HIGH_ADDR(x), HWIO_QGICM_SETSPI_OUT_HIGH_RMSK)
#define HWIO_QGICM_SETSPI_OUT_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QGICM_SETSPI_OUT_HIGH_ADDR(x), m)
#define HWIO_QGICM_SETSPI_OUT_HIGH_OUT(x, v)      \
        out_dword(HWIO_QGICM_SETSPI_OUT_HIGH_ADDR(x),v)
#define HWIO_QGICM_SETSPI_OUT_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGICM_SETSPI_OUT_HIGH_ADDR(x),m,v,HWIO_QGICM_SETSPI_OUT_HIGH_IN(x))
#define HWIO_QGICM_SETSPI_OUT_HIGH_ADDR_HIGH_BMSK                                      0xfff
#define HWIO_QGICM_SETSPI_OUT_HIGH_ADDR_HIGH_SHFT                                        0x0

#define HWIO_QGICM_CLRSPI_OUT_LOW_ADDR(x)                                         ((x) + 0x00000380)
#define HWIO_QGICM_CLRSPI_OUT_LOW_PHYS(x)                                         ((x) + 0x00000380)
#define HWIO_QGICM_CLRSPI_OUT_LOW_RMSK                                            0xffffffff
#define HWIO_QGICM_CLRSPI_OUT_LOW_POR                                             0x7efd0048
#define HWIO_QGICM_CLRSPI_OUT_LOW_POR_RMSK                                        0xffffffff
#define HWIO_QGICM_CLRSPI_OUT_LOW_ATTR                                                   0x3
#define HWIO_QGICM_CLRSPI_OUT_LOW_IN(x)      \
        in_dword_masked(HWIO_QGICM_CLRSPI_OUT_LOW_ADDR(x), HWIO_QGICM_CLRSPI_OUT_LOW_RMSK)
#define HWIO_QGICM_CLRSPI_OUT_LOW_INM(x, m)      \
        in_dword_masked(HWIO_QGICM_CLRSPI_OUT_LOW_ADDR(x), m)
#define HWIO_QGICM_CLRSPI_OUT_LOW_OUT(x, v)      \
        out_dword(HWIO_QGICM_CLRSPI_OUT_LOW_ADDR(x),v)
#define HWIO_QGICM_CLRSPI_OUT_LOW_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGICM_CLRSPI_OUT_LOW_ADDR(x),m,v,HWIO_QGICM_CLRSPI_OUT_LOW_IN(x))
#define HWIO_QGICM_CLRSPI_OUT_LOW_ADDR_LOW_BMSK                                   0xffffffff
#define HWIO_QGICM_CLRSPI_OUT_LOW_ADDR_LOW_SHFT                                          0x0

#define HWIO_QGICM_CLRSPI_OUT_HIGH_ADDR(x)                                        ((x) + 0x00000384)
#define HWIO_QGICM_CLRSPI_OUT_HIGH_PHYS(x)                                        ((x) + 0x00000384)
#define HWIO_QGICM_CLRSPI_OUT_HIGH_RMSK                                                0xfff
#define HWIO_QGICM_CLRSPI_OUT_HIGH_POR                                            0x000000ff
#define HWIO_QGICM_CLRSPI_OUT_HIGH_POR_RMSK                                       0xffffffff
#define HWIO_QGICM_CLRSPI_OUT_HIGH_ATTR                                                  0x3
#define HWIO_QGICM_CLRSPI_OUT_HIGH_IN(x)      \
        in_dword_masked(HWIO_QGICM_CLRSPI_OUT_HIGH_ADDR(x), HWIO_QGICM_CLRSPI_OUT_HIGH_RMSK)
#define HWIO_QGICM_CLRSPI_OUT_HIGH_INM(x, m)      \
        in_dword_masked(HWIO_QGICM_CLRSPI_OUT_HIGH_ADDR(x), m)
#define HWIO_QGICM_CLRSPI_OUT_HIGH_OUT(x, v)      \
        out_dword(HWIO_QGICM_CLRSPI_OUT_HIGH_ADDR(x),v)
#define HWIO_QGICM_CLRSPI_OUT_HIGH_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGICM_CLRSPI_OUT_HIGH_ADDR(x),m,v,HWIO_QGICM_CLRSPI_OUT_HIGH_IN(x))
#define HWIO_QGICM_CLRSPI_OUT_HIGH_ADDR_HIGH_BMSK                                      0xfff
#define HWIO_QGICM_CLRSPI_OUT_HIGH_ADDR_HIGH_SHFT                                        0x0

#define HWIO_QILDE_STATUS_ADDR(x)                                                 ((x) + 0x00000400)
#define HWIO_QILDE_STATUS_PHYS(x)                                                 ((x) + 0x00000400)
#define HWIO_QILDE_STATUS_RMSK                                                       0x7ffff
#define HWIO_QILDE_STATUS_POR                                                     0x00000000
#define HWIO_QILDE_STATUS_POR_RMSK                                                0xffffffff
#define HWIO_QILDE_STATUS_ATTR                                                           0x1
#define HWIO_QILDE_STATUS_IN(x)      \
        in_dword_masked(HWIO_QILDE_STATUS_ADDR(x), HWIO_QILDE_STATUS_RMSK)
#define HWIO_QILDE_STATUS_INM(x, m)      \
        in_dword_masked(HWIO_QILDE_STATUS_ADDR(x), m)
#define HWIO_QILDE_STATUS_TPDM_ACTIVE_BMSK                                           0x40000
#define HWIO_QILDE_STATUS_TPDM_ACTIVE_SHFT                                              0x12
#define HWIO_QILDE_STATUS_CORE_TRANSCORE_BMSK                                        0x20000
#define HWIO_QILDE_STATUS_CORE_TRANSCORE_SHFT                                           0x11
#define HWIO_QILDE_STATUS_CORE_ATOS_BMSK                                             0x10000
#define HWIO_QILDE_STATUS_CORE_ATOS_SHFT                                                0x10
#define HWIO_QILDE_STATUS_CORE_SATOS_BMSK                                             0x8000
#define HWIO_QILDE_STATUS_CORE_SATOS_SHFT                                                0xf
#define HWIO_QILDE_STATUS_CORE_VATOS_BMSK                                             0x4000
#define HWIO_QILDE_STATUS_CORE_VATOS_SHFT                                                0xe
#define HWIO_QILDE_STATUS_CORE_CMDQ_BMSK                                              0x2000
#define HWIO_QILDE_STATUS_CORE_CMDQ_SHFT                                                 0xd
#define HWIO_QILDE_STATUS_CORE_EVENTQ_BMSK                                            0x1000
#define HWIO_QILDE_STATUS_CORE_EVENTQ_SHFT                                               0xc
#define HWIO_QILDE_STATUS_CORE_HTW_BMSK                                                0x800
#define HWIO_QILDE_STATUS_CORE_HTW_SHFT                                                  0xb
#define HWIO_QILDE_STATUS_CORE_CLU_BMSK                                                0x400
#define HWIO_QILDE_STATUS_CORE_CLU_SHFT                                                  0xa
#define HWIO_QILDE_STATUS_WRAPPER_VA_BMSK                                              0x200
#define HWIO_QILDE_STATUS_WRAPPER_VA_SHFT                                                0x9
#define HWIO_QILDE_STATUS_WRAPPER_PA_CTRL_BMSK                                         0x100
#define HWIO_QILDE_STATUS_WRAPPER_PA_CTRL_SHFT                                           0x8
#define HWIO_QILDE_STATUS_WRAPPER_PA_ARB_BMSK                                           0x80
#define HWIO_QILDE_STATUS_WRAPPER_PA_ARB_SHFT                                            0x7
#define HWIO_QILDE_STATUS_WRAPPER_RESP_RD_BMSK                                          0x40
#define HWIO_QILDE_STATUS_WRAPPER_RESP_RD_SHFT                                           0x6
#define HWIO_QILDE_STATUS_WRAPPER_RESP_WR_BMSK                                          0x20
#define HWIO_QILDE_STATUS_WRAPPER_RESP_WR_SHFT                                           0x5
#define HWIO_QILDE_STATUS_WRAPPER_ROB_BMSK                                              0x10
#define HWIO_QILDE_STATUS_WRAPPER_ROB_SHFT                                               0x4
#define HWIO_QILDE_STATUS_WRAPPER_SYNC_ABAR_BMSK                                         0x8
#define HWIO_QILDE_STATUS_WRAPPER_SYNC_ABAR_SHFT                                         0x3
#define HWIO_QILDE_STATUS_WRAPPER_WDATA_BUFF_BMSK                                        0x4
#define HWIO_QILDE_STATUS_WRAPPER_WDATA_BUFF_SHFT                                        0x2
#define HWIO_QILDE_STATUS_WRAPPER_WDATA_INT_SRC_BMSK                                     0x2
#define HWIO_QILDE_STATUS_WRAPPER_WDATA_INT_SRC_SHFT                                     0x1
#define HWIO_QILDE_STATUS_WRAPPER_WDATA_EVICTION_Q_BMSK                                  0x1
#define HWIO_QILDE_STATUS_WRAPPER_WDATA_EVICTION_Q_SHFT                                  0x0

#define QSMMU_QSMMUV3_VATOS_REG_BASE                          (QSMMUV3_BASE      + 0x00030000)
#define QSMMU_QSMMUV3_VATOS_REG_BASE_PHYS                     (QSMMUV3_BASE_PHYS + 0x00030000)

#define HWIO_VATOS_CTRL_ADDR(x)                               ((x) + 0x00000a00)
#define HWIO_VATOS_CTRL_PHYS(x)                               ((x) + 0x00000a00)
#define HWIO_VATOS_CTRL_RMSK                                         0x1
#define HWIO_VATOS_CTRL_POR                                   0x00000000
#define HWIO_VATOS_CTRL_POR_RMSK                              0xffffffff
#define HWIO_VATOS_CTRL_ATTR                                         0x3
#define HWIO_VATOS_CTRL_IN(x)      \
        in_dword_masked(HWIO_VATOS_CTRL_ADDR(x), HWIO_VATOS_CTRL_RMSK)
#define HWIO_VATOS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_VATOS_CTRL_ADDR(x), m)
#define HWIO_VATOS_CTRL_OUT(x, v)      \
        out_dword(HWIO_VATOS_CTRL_ADDR(x),v)
#define HWIO_VATOS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VATOS_CTRL_ADDR(x),m,v,HWIO_VATOS_CTRL_IN(x))
#define HWIO_VATOS_CTRL_RUN_BMSK                                     0x1
#define HWIO_VATOS_CTRL_RUN_SHFT                                     0x0

#define HWIO_VATOS_SID_L_ADDR(x)                              ((x) + 0x00000a08)
#define HWIO_VATOS_SID_L_PHYS(x)                              ((x) + 0x00000a08)
#define HWIO_VATOS_SID_L_RMSK                                 0xffffffff
#define HWIO_VATOS_SID_L_POR                                  0x00000000
#define HWIO_VATOS_SID_L_POR_RMSK                             0xffffffff
#define HWIO_VATOS_SID_L_ATTR                                        0x3
#define HWIO_VATOS_SID_L_IN(x)      \
        in_dword_masked(HWIO_VATOS_SID_L_ADDR(x), HWIO_VATOS_SID_L_RMSK)
#define HWIO_VATOS_SID_L_INM(x, m)      \
        in_dword_masked(HWIO_VATOS_SID_L_ADDR(x), m)
#define HWIO_VATOS_SID_L_OUT(x, v)      \
        out_dword(HWIO_VATOS_SID_L_ADDR(x),v)
#define HWIO_VATOS_SID_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VATOS_SID_L_ADDR(x),m,v,HWIO_VATOS_SID_L_IN(x))
#define HWIO_VATOS_SID_L_STREAMID_BMSK                        0xffffffff
#define HWIO_VATOS_SID_L_STREAMID_SHFT                               0x0

#define HWIO_VATOS_SID_H_ADDR(x)                              ((x) + 0x00000a0c)
#define HWIO_VATOS_SID_H_PHYS(x)                              ((x) + 0x00000a0c)
#define HWIO_VATOS_SID_H_RMSK                                   0x1fffff
#define HWIO_VATOS_SID_H_POR                                  0x00000000
#define HWIO_VATOS_SID_H_POR_RMSK                             0xffffffff
#define HWIO_VATOS_SID_H_ATTR                                        0x3
#define HWIO_VATOS_SID_H_IN(x)      \
        in_dword_masked(HWIO_VATOS_SID_H_ADDR(x), HWIO_VATOS_SID_H_RMSK)
#define HWIO_VATOS_SID_H_INM(x, m)      \
        in_dword_masked(HWIO_VATOS_SID_H_ADDR(x), m)
#define HWIO_VATOS_SID_H_OUT(x, v)      \
        out_dword(HWIO_VATOS_SID_H_ADDR(x),v)
#define HWIO_VATOS_SID_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VATOS_SID_H_ADDR(x),m,v,HWIO_VATOS_SID_H_IN(x))
#define HWIO_VATOS_SID_H_SSID_VALID_BMSK                        0x100000
#define HWIO_VATOS_SID_H_SSID_VALID_SHFT                            0x14
#define HWIO_VATOS_SID_H_SUBSTREAMID_BMSK                        0xfffff
#define HWIO_VATOS_SID_H_SUBSTREAMID_SHFT                            0x0

#define HWIO_VATOS_ADDR_L_ADDR(x)                             ((x) + 0x00000a10)
#define HWIO_VATOS_ADDR_L_PHYS(x)                             ((x) + 0x00000a10)
#define HWIO_VATOS_ADDR_L_RMSK                                0xffffffc0
#define HWIO_VATOS_ADDR_L_POR                                 0x00000000
#define HWIO_VATOS_ADDR_L_POR_RMSK                            0xffffffff
#define HWIO_VATOS_ADDR_L_ATTR                                       0x3
#define HWIO_VATOS_ADDR_L_IN(x)      \
        in_dword_masked(HWIO_VATOS_ADDR_L_ADDR(x), HWIO_VATOS_ADDR_L_RMSK)
#define HWIO_VATOS_ADDR_L_INM(x, m)      \
        in_dword_masked(HWIO_VATOS_ADDR_L_ADDR(x), m)
#define HWIO_VATOS_ADDR_L_OUT(x, v)      \
        out_dword(HWIO_VATOS_ADDR_L_ADDR(x),v)
#define HWIO_VATOS_ADDR_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VATOS_ADDR_L_ADDR(x),m,v,HWIO_VATOS_ADDR_L_IN(x))
#define HWIO_VATOS_ADDR_L_ADDR_31_12_BMSK                     0xfffff000
#define HWIO_VATOS_ADDR_L_ADDR_31_12_SHFT                            0xc
#define HWIO_VATOS_ADDR_L_TYPE_BMSK                                0xc00
#define HWIO_VATOS_ADDR_L_TYPE_SHFT                                  0xa
#define HWIO_VATOS_ADDR_L_PNU_BMSK                                 0x200
#define HWIO_VATOS_ADDR_L_PNU_SHFT                                   0x9
#define HWIO_VATOS_ADDR_L_RNW_BMSK                                 0x100
#define HWIO_VATOS_ADDR_L_RNW_SHFT                                   0x8
#define HWIO_VATOS_ADDR_L_IND_BMSK                                  0x80
#define HWIO_VATOS_ADDR_L_IND_SHFT                                   0x7
#define HWIO_VATOS_ADDR_L_HTTUI_BMSK                                0x40
#define HWIO_VATOS_ADDR_L_HTTUI_SHFT                                 0x6

#define HWIO_VATOS_ADDR_H_ADDR(x)                             ((x) + 0x00000a14)
#define HWIO_VATOS_ADDR_H_PHYS(x)                             ((x) + 0x00000a14)
#define HWIO_VATOS_ADDR_H_RMSK                                0xffffffff
#define HWIO_VATOS_ADDR_H_POR                                 0x00000000
#define HWIO_VATOS_ADDR_H_POR_RMSK                            0xffffffff
#define HWIO_VATOS_ADDR_H_ATTR                                       0x3
#define HWIO_VATOS_ADDR_H_IN(x)      \
        in_dword_masked(HWIO_VATOS_ADDR_H_ADDR(x), HWIO_VATOS_ADDR_H_RMSK)
#define HWIO_VATOS_ADDR_H_INM(x, m)      \
        in_dword_masked(HWIO_VATOS_ADDR_H_ADDR(x), m)
#define HWIO_VATOS_ADDR_H_OUT(x, v)      \
        out_dword(HWIO_VATOS_ADDR_H_ADDR(x),v)
#define HWIO_VATOS_ADDR_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_VATOS_ADDR_H_ADDR(x),m,v,HWIO_VATOS_ADDR_H_IN(x))
#define HWIO_VATOS_ADDR_H_ADDR_63_32_BMSK                     0xffffffff
#define HWIO_VATOS_ADDR_H_ADDR_63_32_SHFT                            0x0

#define HWIO_VATOS_PAR_L_ADDR(x)                              ((x) + 0x00000a18)
#define HWIO_VATOS_PAR_L_PHYS(x)                              ((x) + 0x00000a18)
#define HWIO_VATOS_PAR_L_RMSK                                 0xffffffff
#define HWIO_VATOS_PAR_L_POR                                  0x00000000
#define HWIO_VATOS_PAR_L_POR_RMSK                             0xffffffff
#define HWIO_VATOS_PAR_L_ATTR                                        0x1
#define HWIO_VATOS_PAR_L_IN(x)      \
        in_dword_masked(HWIO_VATOS_PAR_L_ADDR(x), HWIO_VATOS_PAR_L_RMSK)
#define HWIO_VATOS_PAR_L_INM(x, m)      \
        in_dword_masked(HWIO_VATOS_PAR_L_ADDR(x), m)
#define HWIO_VATOS_PAR_L_ADDR_BMSK                            0xfffff000
#define HWIO_VATOS_PAR_L_ADDR_SHFT                                   0xc
#define HWIO_VATOS_PAR_L_FIELD_BMSK                                0xffe
#define HWIO_VATOS_PAR_L_FIELD_SHFT                                  0x1
#define HWIO_VATOS_PAR_L_FAULT_BMSK                                  0x1
#define HWIO_VATOS_PAR_L_FAULT_SHFT                                  0x0

#define HWIO_VATOS_PAR_H_ADDR(x)                              ((x) + 0x00000a1c)
#define HWIO_VATOS_PAR_H_PHYS(x)                              ((x) + 0x00000a1c)
#define HWIO_VATOS_PAR_H_RMSK                                 0xff00ffff
#define HWIO_VATOS_PAR_H_POR                                  0x00000000
#define HWIO_VATOS_PAR_H_POR_RMSK                             0xffffffff
#define HWIO_VATOS_PAR_H_ATTR                                        0x1
#define HWIO_VATOS_PAR_H_IN(x)      \
        in_dword_masked(HWIO_VATOS_PAR_H_ADDR(x), HWIO_VATOS_PAR_H_RMSK)
#define HWIO_VATOS_PAR_H_INM(x, m)      \
        in_dword_masked(HWIO_VATOS_PAR_H_ADDR(x), m)
#define HWIO_VATOS_PAR_H_MEMATTR_BMSK                         0xff000000
#define HWIO_VATOS_PAR_H_MEMATTR_SHFT                               0x18
#define HWIO_VATOS_PAR_H_ADDR_BMSK                                0xffff
#define HWIO_VATOS_PAR_H_ADDR_SHFT                                   0x0

#define HWIO_QAD0_VATOS_CTRL_ADDR(x)                          ((x) + 0x00000a00)
#define HWIO_QAD0_VATOS_CTRL_PHYS(x)                          ((x) + 0x00000a00)
#define HWIO_QAD0_VATOS_CTRL_RMSK                                    0x1
#define HWIO_QAD0_VATOS_CTRL_POR                              0x00000000
#define HWIO_QAD0_VATOS_CTRL_POR_RMSK                         0xffffffff
#define HWIO_QAD0_VATOS_CTRL_ATTR                                    0x3
#define HWIO_QAD0_VATOS_CTRL_IN(x)      \
        in_dword_masked(HWIO_QAD0_VATOS_CTRL_ADDR(x), HWIO_QAD0_VATOS_CTRL_RMSK)
#define HWIO_QAD0_VATOS_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_VATOS_CTRL_ADDR(x), m)
#define HWIO_QAD0_VATOS_CTRL_OUT(x, v)      \
        out_dword(HWIO_QAD0_VATOS_CTRL_ADDR(x),v)
#define HWIO_QAD0_VATOS_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_VATOS_CTRL_ADDR(x),m,v,HWIO_QAD0_VATOS_CTRL_IN(x))
#define HWIO_QAD0_VATOS_CTRL_RUN_BMSK                                0x1
#define HWIO_QAD0_VATOS_CTRL_RUN_SHFT                                0x0

#define HWIO_QAD0_VATOS_SID_L_ADDR(x)                         ((x) + 0x00000a08)
#define HWIO_QAD0_VATOS_SID_L_PHYS(x)                         ((x) + 0x00000a08)
#define HWIO_QAD0_VATOS_SID_L_RMSK                            0xffffffff
#define HWIO_QAD0_VATOS_SID_L_POR                             0x00000000
#define HWIO_QAD0_VATOS_SID_L_POR_RMSK                        0xffffffff
#define HWIO_QAD0_VATOS_SID_L_ATTR                                   0x3
#define HWIO_QAD0_VATOS_SID_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_VATOS_SID_L_ADDR(x), HWIO_QAD0_VATOS_SID_L_RMSK)
#define HWIO_QAD0_VATOS_SID_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_VATOS_SID_L_ADDR(x), m)
#define HWIO_QAD0_VATOS_SID_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_VATOS_SID_L_ADDR(x),v)
#define HWIO_QAD0_VATOS_SID_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_VATOS_SID_L_ADDR(x),m,v,HWIO_QAD0_VATOS_SID_L_IN(x))
#define HWIO_QAD0_VATOS_SID_L_STREAMID_BMSK                   0xffffffff
#define HWIO_QAD0_VATOS_SID_L_STREAMID_SHFT                          0x0

#define HWIO_QAD0_VATOS_SID_H_ADDR(x)                         ((x) + 0x00000a0c)
#define HWIO_QAD0_VATOS_SID_H_PHYS(x)                         ((x) + 0x00000a0c)
#define HWIO_QAD0_VATOS_SID_H_RMSK                              0x1fffff
#define HWIO_QAD0_VATOS_SID_H_POR                             0x00000000
#define HWIO_QAD0_VATOS_SID_H_POR_RMSK                        0xffffffff
#define HWIO_QAD0_VATOS_SID_H_ATTR                                   0x3
#define HWIO_QAD0_VATOS_SID_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_VATOS_SID_H_ADDR(x), HWIO_QAD0_VATOS_SID_H_RMSK)
#define HWIO_QAD0_VATOS_SID_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_VATOS_SID_H_ADDR(x), m)
#define HWIO_QAD0_VATOS_SID_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_VATOS_SID_H_ADDR(x),v)
#define HWIO_QAD0_VATOS_SID_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_VATOS_SID_H_ADDR(x),m,v,HWIO_QAD0_VATOS_SID_H_IN(x))
#define HWIO_QAD0_VATOS_SID_H_SSID_VALID_BMSK                   0x100000
#define HWIO_QAD0_VATOS_SID_H_SSID_VALID_SHFT                       0x14
#define HWIO_QAD0_VATOS_SID_H_SUBSTREAMID_BMSK                   0xfffff
#define HWIO_QAD0_VATOS_SID_H_SUBSTREAMID_SHFT                       0x0

#define HWIO_QAD0_VATOS_ADDR_L_ADDR(x)                        ((x) + 0x00000a10)
#define HWIO_QAD0_VATOS_ADDR_L_PHYS(x)                        ((x) + 0x00000a10)
#define HWIO_QAD0_VATOS_ADDR_L_RMSK                           0xffffffc0
#define HWIO_QAD0_VATOS_ADDR_L_POR                            0x00000000
#define HWIO_QAD0_VATOS_ADDR_L_POR_RMSK                       0xffffffff
#define HWIO_QAD0_VATOS_ADDR_L_ATTR                                  0x3
#define HWIO_QAD0_VATOS_ADDR_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_VATOS_ADDR_L_ADDR(x), HWIO_QAD0_VATOS_ADDR_L_RMSK)
#define HWIO_QAD0_VATOS_ADDR_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_VATOS_ADDR_L_ADDR(x), m)
#define HWIO_QAD0_VATOS_ADDR_L_OUT(x, v)      \
        out_dword(HWIO_QAD0_VATOS_ADDR_L_ADDR(x),v)
#define HWIO_QAD0_VATOS_ADDR_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_VATOS_ADDR_L_ADDR(x),m,v,HWIO_QAD0_VATOS_ADDR_L_IN(x))
#define HWIO_QAD0_VATOS_ADDR_L_ADDR_31_12_BMSK                0xfffff000
#define HWIO_QAD0_VATOS_ADDR_L_ADDR_31_12_SHFT                       0xc
#define HWIO_QAD0_VATOS_ADDR_L_TYPE_BMSK                           0xc00
#define HWIO_QAD0_VATOS_ADDR_L_TYPE_SHFT                             0xa
#define HWIO_QAD0_VATOS_ADDR_L_PNU_BMSK                            0x200
#define HWIO_QAD0_VATOS_ADDR_L_PNU_SHFT                              0x9
#define HWIO_QAD0_VATOS_ADDR_L_RNW_BMSK                            0x100
#define HWIO_QAD0_VATOS_ADDR_L_RNW_SHFT                              0x8
#define HWIO_QAD0_VATOS_ADDR_L_IND_BMSK                             0x80
#define HWIO_QAD0_VATOS_ADDR_L_IND_SHFT                              0x7
#define HWIO_QAD0_VATOS_ADDR_L_HTTUI_BMSK                           0x40
#define HWIO_QAD0_VATOS_ADDR_L_HTTUI_SHFT                            0x6

#define HWIO_QAD0_VATOS_ADDR_H_ADDR(x)                        ((x) + 0x00000a14)
#define HWIO_QAD0_VATOS_ADDR_H_PHYS(x)                        ((x) + 0x00000a14)
#define HWIO_QAD0_VATOS_ADDR_H_RMSK                           0xffffffff
#define HWIO_QAD0_VATOS_ADDR_H_POR                            0x00000000
#define HWIO_QAD0_VATOS_ADDR_H_POR_RMSK                       0xffffffff
#define HWIO_QAD0_VATOS_ADDR_H_ATTR                                  0x3
#define HWIO_QAD0_VATOS_ADDR_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_VATOS_ADDR_H_ADDR(x), HWIO_QAD0_VATOS_ADDR_H_RMSK)
#define HWIO_QAD0_VATOS_ADDR_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_VATOS_ADDR_H_ADDR(x), m)
#define HWIO_QAD0_VATOS_ADDR_H_OUT(x, v)      \
        out_dword(HWIO_QAD0_VATOS_ADDR_H_ADDR(x),v)
#define HWIO_QAD0_VATOS_ADDR_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QAD0_VATOS_ADDR_H_ADDR(x),m,v,HWIO_QAD0_VATOS_ADDR_H_IN(x))
#define HWIO_QAD0_VATOS_ADDR_H_ADDR_63_32_BMSK                0xffffffff
#define HWIO_QAD0_VATOS_ADDR_H_ADDR_63_32_SHFT                       0x0

#define HWIO_QAD0_VATOS_PAR_L_ADDR(x)                         ((x) + 0x00000a18)
#define HWIO_QAD0_VATOS_PAR_L_PHYS(x)                         ((x) + 0x00000a18)
#define HWIO_QAD0_VATOS_PAR_L_RMSK                            0xffffffff
#define HWIO_QAD0_VATOS_PAR_L_POR                             0x00000000
#define HWIO_QAD0_VATOS_PAR_L_POR_RMSK                        0xffffffff
#define HWIO_QAD0_VATOS_PAR_L_ATTR                                   0x1
#define HWIO_QAD0_VATOS_PAR_L_IN(x)      \
        in_dword_masked(HWIO_QAD0_VATOS_PAR_L_ADDR(x), HWIO_QAD0_VATOS_PAR_L_RMSK)
#define HWIO_QAD0_VATOS_PAR_L_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_VATOS_PAR_L_ADDR(x), m)
#define HWIO_QAD0_VATOS_PAR_L_ADDR_BMSK                       0xfffff000
#define HWIO_QAD0_VATOS_PAR_L_ADDR_SHFT                              0xc
#define HWIO_QAD0_VATOS_PAR_L_FIELD_BMSK                           0xffe
#define HWIO_QAD0_VATOS_PAR_L_FIELD_SHFT                             0x1
#define HWIO_QAD0_VATOS_PAR_L_FAULT_BMSK                             0x1
#define HWIO_QAD0_VATOS_PAR_L_FAULT_SHFT                             0x0

#define HWIO_QAD0_VATOS_PAR_H_ADDR(x)                         ((x) + 0x00000a1c)
#define HWIO_QAD0_VATOS_PAR_H_PHYS(x)                         ((x) + 0x00000a1c)
#define HWIO_QAD0_VATOS_PAR_H_RMSK                            0xff00ffff
#define HWIO_QAD0_VATOS_PAR_H_POR                             0x00000000
#define HWIO_QAD0_VATOS_PAR_H_POR_RMSK                        0xffffffff
#define HWIO_QAD0_VATOS_PAR_H_ATTR                                   0x1
#define HWIO_QAD0_VATOS_PAR_H_IN(x)      \
        in_dword_masked(HWIO_QAD0_VATOS_PAR_H_ADDR(x), HWIO_QAD0_VATOS_PAR_H_RMSK)
#define HWIO_QAD0_VATOS_PAR_H_INM(x, m)      \
        in_dword_masked(HWIO_QAD0_VATOS_PAR_H_ADDR(x), m)
#define HWIO_QAD0_VATOS_PAR_H_MEMATTR_BMSK                    0xff000000
#define HWIO_QAD0_VATOS_PAR_H_MEMATTR_SHFT                          0x18
#define HWIO_QAD0_VATOS_PAR_H_ADDR_BMSK                           0xffff
#define HWIO_QAD0_VATOS_PAR_H_ADDR_SHFT                              0x0

#define QSMMU_QSMMUV3_PMCG0_REG_BASE                                          (QSMMUV3_BASE      + 0x00040000)
#define QSMMU_QSMMUV3_PMCG0_REG_BASE_PHYS                                     (QSMMUV3_BASE_PHYS + 0x00040000)

#define HWIO_PMCG0_EVCNTR_Ln_ADDR(base,n)                                     ((base) + 0x00010000 + 0x4 * (n))
#define HWIO_PMCG0_EVCNTR_Ln_PHYS(base,n)                                     ((base) + 0x00010000 + 0x4 * (n))
#define HWIO_PMCG0_EVCNTR_Ln_RMSK                                             0xffffffff
#define HWIO_PMCG0_EVCNTR_Ln_MAXn                                                      7
#define HWIO_PMCG0_EVCNTR_Ln_POR                                              0x00000000
#define HWIO_PMCG0_EVCNTR_Ln_POR_RMSK                                         0xffffffff
#define HWIO_PMCG0_EVCNTR_Ln_ATTR                                                    0x3
#define HWIO_PMCG0_EVCNTR_Ln_INI(base,n)        \
        in_dword_masked(HWIO_PMCG0_EVCNTR_Ln_ADDR(base,n), HWIO_PMCG0_EVCNTR_Ln_RMSK)
#define HWIO_PMCG0_EVCNTR_Ln_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG0_EVCNTR_Ln_ADDR(base,n), mask)
#define HWIO_PMCG0_EVCNTR_Ln_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG0_EVCNTR_Ln_ADDR(base,n),val)
#define HWIO_PMCG0_EVCNTR_Ln_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG0_EVCNTR_Ln_ADDR(base,n),mask,val,HWIO_PMCG0_EVCNTR_Ln_INI(base,n))
#define HWIO_PMCG0_EVCNTR_Ln_COUNTER_VALUE_BMSK                               0xffffffff
#define HWIO_PMCG0_EVCNTR_Ln_COUNTER_VALUE_SHFT                                      0x0

#define HWIO_PMCG0_EVTYPERn_ADDR(base,n)                                      ((base) + 0x00000400 + 0x4 * (n))
#define HWIO_PMCG0_EVTYPERn_PHYS(base,n)                                      ((base) + 0x00000400 + 0x4 * (n))
#define HWIO_PMCG0_EVTYPERn_RMSK                                              0xe000ffff
#define HWIO_PMCG0_EVTYPERn_MAXn                                                       7
#define HWIO_PMCG0_EVTYPERn_POR                                               0x0000ffff
#define HWIO_PMCG0_EVTYPERn_POR_RMSK                                          0xffffffff
#define HWIO_PMCG0_EVTYPERn_ATTR                                                     0x3
#define HWIO_PMCG0_EVTYPERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG0_EVTYPERn_ADDR(base,n), HWIO_PMCG0_EVTYPERn_RMSK)
#define HWIO_PMCG0_EVTYPERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG0_EVTYPERn_ADDR(base,n), mask)
#define HWIO_PMCG0_EVTYPERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG0_EVTYPERn_ADDR(base,n),val)
#define HWIO_PMCG0_EVTYPERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG0_EVTYPERn_ADDR(base,n),mask,val,HWIO_PMCG0_EVTYPERn_INI(base,n))
#define HWIO_PMCG0_EVTYPERn_OVFCAP_BMSK                                       0x80000000
#define HWIO_PMCG0_EVTYPERn_OVFCAP_SHFT                                             0x1f
#define HWIO_PMCG0_EVTYPERn_FILTER_SEC_SID_BMSK                               0x40000000
#define HWIO_PMCG0_EVTYPERn_FILTER_SEC_SID_SHFT                                     0x1e
#define HWIO_PMCG0_EVTYPERn_FILTER_SID_SPAN_BMSK                              0x20000000
#define HWIO_PMCG0_EVTYPERn_FILTER_SID_SPAN_SHFT                                    0x1d
#define HWIO_PMCG0_EVTYPERn_EVENT_BMSK                                            0xffff
#define HWIO_PMCG0_EVTYPERn_EVENT_SHFT                                               0x0

#define HWIO_PMCG0_SVR_Ln_ADDR(base,n)                                        ((base) + 0x00010600 + 0x4 * (n))
#define HWIO_PMCG0_SVR_Ln_PHYS(base,n)                                        ((base) + 0x00010600 + 0x4 * (n))
#define HWIO_PMCG0_SVR_Ln_RMSK                                                0xffffffff
#define HWIO_PMCG0_SVR_Ln_MAXn                                                         7
#define HWIO_PMCG0_SVR_Ln_POR                                                 0x00000000
#define HWIO_PMCG0_SVR_Ln_POR_RMSK                                            0xffffffff
#define HWIO_PMCG0_SVR_Ln_ATTR                                                       0x1
#define HWIO_PMCG0_SVR_Ln_INI(base,n)        \
        in_dword_masked(HWIO_PMCG0_SVR_Ln_ADDR(base,n), HWIO_PMCG0_SVR_Ln_RMSK)
#define HWIO_PMCG0_SVR_Ln_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG0_SVR_Ln_ADDR(base,n), mask)
#define HWIO_PMCG0_SVR_Ln_SHADOW_COUNTER_VALUE_BMSK                           0xffffffff
#define HWIO_PMCG0_SVR_Ln_SHADOW_COUNTER_VALUE_SHFT                                  0x0

#define HWIO_PMCG0_SMRn_ADDR(base,n)                                          ((base) + 0x00000a00 + 0x4 * (n))
#define HWIO_PMCG0_SMRn_PHYS(base,n)                                          ((base) + 0x00000a00 + 0x4 * (n))
#define HWIO_PMCG0_SMRn_RMSK                                                      0xffff
#define HWIO_PMCG0_SMRn_MAXn                                                           7
#define HWIO_PMCG0_SMRn_POR                                                   0x00000000
#define HWIO_PMCG0_SMRn_POR_RMSK                                              0xffffffff
#define HWIO_PMCG0_SMRn_ATTR                                                         0x3
#define HWIO_PMCG0_SMRn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG0_SMRn_ADDR(base,n), HWIO_PMCG0_SMRn_RMSK)
#define HWIO_PMCG0_SMRn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG0_SMRn_ADDR(base,n), mask)
#define HWIO_PMCG0_SMRn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG0_SMRn_ADDR(base,n),val)
#define HWIO_PMCG0_SMRn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG0_SMRn_ADDR(base,n),mask,val,HWIO_PMCG0_SMRn_INI(base,n))
#define HWIO_PMCG0_SMRn_STREAMID_BMSK                                             0xffff
#define HWIO_PMCG0_SMRn_STREAMID_SHFT                                                0x0

#define HWIO_PMCG0_CNTENSET0_ADDR(x)                                          ((x) + 0x00000c00)
#define HWIO_PMCG0_CNTENSET0_PHYS(x)                                          ((x) + 0x00000c00)
#define HWIO_PMCG0_CNTENSET0_RMSK                                                   0xff
#define HWIO_PMCG0_CNTENSET0_POR                                              0x00000000
#define HWIO_PMCG0_CNTENSET0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG0_CNTENSET0_ATTR                                                    0x3
#define HWIO_PMCG0_CNTENSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CNTENSET0_ADDR(x), HWIO_PMCG0_CNTENSET0_RMSK)
#define HWIO_PMCG0_CNTENSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CNTENSET0_ADDR(x), m)
#define HWIO_PMCG0_CNTENSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG0_CNTENSET0_ADDR(x),v)
#define HWIO_PMCG0_CNTENSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_CNTENSET0_ADDR(x),m,v,HWIO_PMCG0_CNTENSET0_IN(x))
#define HWIO_PMCG0_CNTENSET0_CNTEN_BMSK                                             0xff
#define HWIO_PMCG0_CNTENSET0_CNTEN_SHFT                                              0x0

#define HWIO_PMCG0_CNTENCLR0_ADDR(x)                                          ((x) + 0x00000c20)
#define HWIO_PMCG0_CNTENCLR0_PHYS(x)                                          ((x) + 0x00000c20)
#define HWIO_PMCG0_CNTENCLR0_RMSK                                                   0xff
#define HWIO_PMCG0_CNTENCLR0_POR                                              0x00000000
#define HWIO_PMCG0_CNTENCLR0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG0_CNTENCLR0_ATTR                                                    0x3
#define HWIO_PMCG0_CNTENCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CNTENCLR0_ADDR(x), HWIO_PMCG0_CNTENCLR0_RMSK)
#define HWIO_PMCG0_CNTENCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CNTENCLR0_ADDR(x), m)
#define HWIO_PMCG0_CNTENCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG0_CNTENCLR0_ADDR(x),v)
#define HWIO_PMCG0_CNTENCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_CNTENCLR0_ADDR(x),m,v,HWIO_PMCG0_CNTENCLR0_IN(x))
#define HWIO_PMCG0_CNTENCLR0_CNTEN_BMSK                                             0xff
#define HWIO_PMCG0_CNTENCLR0_CNTEN_SHFT                                              0x0

#define HWIO_PMCG0_INTENSET0_ADDR(x)                                          ((x) + 0x00000c40)
#define HWIO_PMCG0_INTENSET0_PHYS(x)                                          ((x) + 0x00000c40)
#define HWIO_PMCG0_INTENSET0_RMSK                                                   0xff
#define HWIO_PMCG0_INTENSET0_POR                                              0x00000000
#define HWIO_PMCG0_INTENSET0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG0_INTENSET0_ATTR                                                    0x3
#define HWIO_PMCG0_INTENSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_INTENSET0_ADDR(x), HWIO_PMCG0_INTENSET0_RMSK)
#define HWIO_PMCG0_INTENSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_INTENSET0_ADDR(x), m)
#define HWIO_PMCG0_INTENSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG0_INTENSET0_ADDR(x),v)
#define HWIO_PMCG0_INTENSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_INTENSET0_ADDR(x),m,v,HWIO_PMCG0_INTENSET0_IN(x))
#define HWIO_PMCG0_INTENSET0_INTEN_BMSK                                             0xff
#define HWIO_PMCG0_INTENSET0_INTEN_SHFT                                              0x0

#define HWIO_PMCG0_INTENCLR0_ADDR(x)                                          ((x) + 0x00000c60)
#define HWIO_PMCG0_INTENCLR0_PHYS(x)                                          ((x) + 0x00000c60)
#define HWIO_PMCG0_INTENCLR0_RMSK                                                   0xff
#define HWIO_PMCG0_INTENCLR0_POR                                              0x00000000
#define HWIO_PMCG0_INTENCLR0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG0_INTENCLR0_ATTR                                                    0x3
#define HWIO_PMCG0_INTENCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_INTENCLR0_ADDR(x), HWIO_PMCG0_INTENCLR0_RMSK)
#define HWIO_PMCG0_INTENCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_INTENCLR0_ADDR(x), m)
#define HWIO_PMCG0_INTENCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG0_INTENCLR0_ADDR(x),v)
#define HWIO_PMCG0_INTENCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_INTENCLR0_ADDR(x),m,v,HWIO_PMCG0_INTENCLR0_IN(x))
#define HWIO_PMCG0_INTENCLR0_INTEN_BMSK                                             0xff
#define HWIO_PMCG0_INTENCLR0_INTEN_SHFT                                              0x0

#define HWIO_PMCG0_OVSCLR0_ADDR(x)                                            ((x) + 0x00010c80)
#define HWIO_PMCG0_OVSCLR0_PHYS(x)                                            ((x) + 0x00010c80)
#define HWIO_PMCG0_OVSCLR0_RMSK                                                     0xff
#define HWIO_PMCG0_OVSCLR0_POR                                                0x00000000
#define HWIO_PMCG0_OVSCLR0_POR_RMSK                                           0xffffffff
#define HWIO_PMCG0_OVSCLR0_ATTR                                                      0x3
#define HWIO_PMCG0_OVSCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_OVSCLR0_ADDR(x), HWIO_PMCG0_OVSCLR0_RMSK)
#define HWIO_PMCG0_OVSCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_OVSCLR0_ADDR(x), m)
#define HWIO_PMCG0_OVSCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG0_OVSCLR0_ADDR(x),v)
#define HWIO_PMCG0_OVSCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_OVSCLR0_ADDR(x),m,v,HWIO_PMCG0_OVSCLR0_IN(x))
#define HWIO_PMCG0_OVSCLR0_OVS_BMSK                                                 0xff
#define HWIO_PMCG0_OVSCLR0_OVS_SHFT                                                  0x0

#define HWIO_PMCG0_OVSSET0_ADDR(x)                                            ((x) + 0x00010cc0)
#define HWIO_PMCG0_OVSSET0_PHYS(x)                                            ((x) + 0x00010cc0)
#define HWIO_PMCG0_OVSSET0_RMSK                                                     0xff
#define HWIO_PMCG0_OVSSET0_POR                                                0x00000000
#define HWIO_PMCG0_OVSSET0_POR_RMSK                                           0xffffffff
#define HWIO_PMCG0_OVSSET0_ATTR                                                      0x3
#define HWIO_PMCG0_OVSSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_OVSSET0_ADDR(x), HWIO_PMCG0_OVSSET0_RMSK)
#define HWIO_PMCG0_OVSSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_OVSSET0_ADDR(x), m)
#define HWIO_PMCG0_OVSSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG0_OVSSET0_ADDR(x),v)
#define HWIO_PMCG0_OVSSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_OVSSET0_ADDR(x),m,v,HWIO_PMCG0_OVSSET0_IN(x))
#define HWIO_PMCG0_OVSSET0_OVS_BMSK                                                 0xff
#define HWIO_PMCG0_OVSSET0_OVS_SHFT                                                  0x0

#define HWIO_PMCG0_CAPR_ADDR(x)                                               ((x) + 0x00010d88)
#define HWIO_PMCG0_CAPR_PHYS(x)                                               ((x) + 0x00010d88)
#define HWIO_PMCG0_CAPR_RMSK                                                         0x1
#define HWIO_PMCG0_CAPR_POR                                                   0x00000000
#define HWIO_PMCG0_CAPR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG0_CAPR_ATTR                                                         0x2
#define HWIO_PMCG0_CAPR_OUT(x, v)      \
        out_dword(HWIO_PMCG0_CAPR_ADDR(x),v)
#define HWIO_PMCG0_CAPR_CAPTURE_BMSK                                                 0x1
#define HWIO_PMCG0_CAPR_CAPTURE_SHFT                                                 0x0

#define HWIO_PMCG0_SCR_ADDR(x)                                                ((x) + 0x00000df8)
#define HWIO_PMCG0_SCR_PHYS(x)                                                ((x) + 0x00000df8)
#define HWIO_PMCG0_SCR_RMSK                                                   0x80000007
#define HWIO_PMCG0_SCR_POR                                                    0x00000002
#define HWIO_PMCG0_SCR_POR_RMSK                                               0xffffffff
#define HWIO_PMCG0_SCR_ATTR                                                          0x3
#define HWIO_PMCG0_SCR_IN(x)      \
        in_dword_masked(HWIO_PMCG0_SCR_ADDR(x), HWIO_PMCG0_SCR_RMSK)
#define HWIO_PMCG0_SCR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_SCR_ADDR(x), m)
#define HWIO_PMCG0_SCR_OUT(x, v)      \
        out_dword(HWIO_PMCG0_SCR_ADDR(x),v)
#define HWIO_PMCG0_SCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_SCR_ADDR(x),m,v,HWIO_PMCG0_SCR_IN(x))
#define HWIO_PMCG0_SCR_READ_AS_ONE_BMSK                                       0x80000000
#define HWIO_PMCG0_SCR_READ_AS_ONE_SHFT                                             0x1f
#define HWIO_PMCG0_SCR_NSMSI_BMSK                                                    0x4
#define HWIO_PMCG0_SCR_NSMSI_SHFT                                                    0x2
#define HWIO_PMCG0_SCR_NSRA_BMSK                                                     0x2
#define HWIO_PMCG0_SCR_NSRA_SHFT                                                     0x1
#define HWIO_PMCG0_SCR_SO_BMSK                                                       0x1
#define HWIO_PMCG0_SCR_SO_SHFT                                                       0x0

#define HWIO_PMCG0_CFGR_ADDR(x)                                               ((x) + 0x00000e00)
#define HWIO_PMCG0_CFGR_PHYS(x)                                               ((x) + 0x00000e00)
#define HWIO_PMCG0_CFGR_RMSK                                                    0x703f3f
#define HWIO_PMCG0_CFGR_POR                                                   0x00701f07
#define HWIO_PMCG0_CFGR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG0_CFGR_ATTR                                                         0x1
#define HWIO_PMCG0_CFGR_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CFGR_ADDR(x), HWIO_PMCG0_CFGR_RMSK)
#define HWIO_PMCG0_CFGR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CFGR_ADDR(x), m)
#define HWIO_PMCG0_CFGR_CAPTURE_BMSK                                            0x400000
#define HWIO_PMCG0_CFGR_CAPTURE_SHFT                                                0x16
#define HWIO_PMCG0_CFGR_MSI_BMSK                                                0x200000
#define HWIO_PMCG0_CFGR_MSI_SHFT                                                    0x15
#define HWIO_PMCG0_CFGR_RELOC_CTRS_BMSK                                         0x100000
#define HWIO_PMCG0_CFGR_RELOC_CTRS_SHFT                                             0x14
#define HWIO_PMCG0_CFGR_SIZE_BMSK                                                 0x3f00
#define HWIO_PMCG0_CFGR_SIZE_SHFT                                                    0x8
#define HWIO_PMCG0_CFGR_NCTR_BMSK                                                   0x3f
#define HWIO_PMCG0_CFGR_NCTR_SHFT                                                    0x0

#define HWIO_PMCG0_CR_ADDR(x)                                                 ((x) + 0x00000e04)
#define HWIO_PMCG0_CR_PHYS(x)                                                 ((x) + 0x00000e04)
#define HWIO_PMCG0_CR_RMSK                                                           0x1
#define HWIO_PMCG0_CR_POR                                                     0x00000000
#define HWIO_PMCG0_CR_POR_RMSK                                                0xffffffff
#define HWIO_PMCG0_CR_ATTR                                                           0x3
#define HWIO_PMCG0_CR_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CR_ADDR(x), HWIO_PMCG0_CR_RMSK)
#define HWIO_PMCG0_CR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CR_ADDR(x), m)
#define HWIO_PMCG0_CR_OUT(x, v)      \
        out_dword(HWIO_PMCG0_CR_ADDR(x),v)
#define HWIO_PMCG0_CR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_CR_ADDR(x),m,v,HWIO_PMCG0_CR_IN(x))
#define HWIO_PMCG0_CR_E_BMSK                                                         0x1
#define HWIO_PMCG0_CR_E_SHFT                                                         0x0

#define HWIO_PMCG0_CEID0_L_ADDR(x)                                            ((x) + 0x00000e20)
#define HWIO_PMCG0_CEID0_L_PHYS(x)                                            ((x) + 0x00000e20)
#define HWIO_PMCG0_CEID0_L_RMSK                                                     0xff
#define HWIO_PMCG0_CEID0_L_POR                                                0x0000001f
#define HWIO_PMCG0_CEID0_L_POR_RMSK                                           0xffffffff
#define HWIO_PMCG0_CEID0_L_ATTR                                                      0x1
#define HWIO_PMCG0_CEID0_L_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CEID0_L_ADDR(x), HWIO_PMCG0_CEID0_L_RMSK)
#define HWIO_PMCG0_CEID0_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CEID0_L_ADDR(x), m)
#define HWIO_PMCG0_CEID0_L_IMPL_EVENTS_BMSK                                         0xff
#define HWIO_PMCG0_CEID0_L_IMPL_EVENTS_SHFT                                          0x0

#define HWIO_PMCG0_CEID0_H_ADDR(x)                                            ((x) + 0x00000e24)
#define HWIO_PMCG0_CEID0_H_PHYS(x)                                            ((x) + 0x00000e24)
#define HWIO_PMCG0_CEID0_H_RMSK                                               0xffffffff
#define HWIO_PMCG0_CEID0_H_POR                                                0x00000000
#define HWIO_PMCG0_CEID0_H_POR_RMSK                                           0xffffffff
#define HWIO_PMCG0_CEID0_H_ATTR                                                      0x1
#define HWIO_PMCG0_CEID0_H_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CEID0_H_ADDR(x), HWIO_PMCG0_CEID0_H_RMSK)
#define HWIO_PMCG0_CEID0_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CEID0_H_ADDR(x), m)
#define HWIO_PMCG0_CEID0_H_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG0_CEID0_H_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG0_CEID1_L_ADDR(x)                                            ((x) + 0x00000e28)
#define HWIO_PMCG0_CEID1_L_PHYS(x)                                            ((x) + 0x00000e28)
#define HWIO_PMCG0_CEID1_L_RMSK                                               0xffffffff
#define HWIO_PMCG0_CEID1_L_POR                                                0x00000000
#define HWIO_PMCG0_CEID1_L_POR_RMSK                                           0xffffffff
#define HWIO_PMCG0_CEID1_L_ATTR                                                      0x1
#define HWIO_PMCG0_CEID1_L_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CEID1_L_ADDR(x), HWIO_PMCG0_CEID1_L_RMSK)
#define HWIO_PMCG0_CEID1_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CEID1_L_ADDR(x), m)
#define HWIO_PMCG0_CEID1_L_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG0_CEID1_L_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG0_CEID1_H_ADDR(x)                                            ((x) + 0x00000e2c)
#define HWIO_PMCG0_CEID1_H_PHYS(x)                                            ((x) + 0x00000e2c)
#define HWIO_PMCG0_CEID1_H_RMSK                                               0xffffffff
#define HWIO_PMCG0_CEID1_H_POR                                                0x00000000
#define HWIO_PMCG0_CEID1_H_POR_RMSK                                           0xffffffff
#define HWIO_PMCG0_CEID1_H_ATTR                                                      0x1
#define HWIO_PMCG0_CEID1_H_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CEID1_H_ADDR(x), HWIO_PMCG0_CEID1_H_RMSK)
#define HWIO_PMCG0_CEID1_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CEID1_H_ADDR(x), m)
#define HWIO_PMCG0_CEID1_H_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG0_CEID1_H_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG0_IMPL_CEID0_ADDR(x)                                         ((x) + 0x00000e30)
#define HWIO_PMCG0_IMPL_CEID0_PHYS(x)                                         ((x) + 0x00000e30)
#define HWIO_PMCG0_IMPL_CEID0_RMSK                                                  0x3f
#define HWIO_PMCG0_IMPL_CEID0_POR                                             0x00000000
#define HWIO_PMCG0_IMPL_CEID0_POR_RMSK                                        0xffffffff
#define HWIO_PMCG0_IMPL_CEID0_ATTR                                                   0x1
#define HWIO_PMCG0_IMPL_CEID0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_IMPL_CEID0_ADDR(x), HWIO_PMCG0_IMPL_CEID0_RMSK)
#define HWIO_PMCG0_IMPL_CEID0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_IMPL_CEID0_ADDR(x), m)
#define HWIO_PMCG0_IMPL_CEID0_IMPL_EVENTS_BMSK                                      0x3f
#define HWIO_PMCG0_IMPL_CEID0_IMPL_EVENTS_SHFT                                       0x0

#define HWIO_PMCG0_IRQ_CTRL_ADDR(x)                                           ((x) + 0x00000e50)
#define HWIO_PMCG0_IRQ_CTRL_PHYS(x)                                           ((x) + 0x00000e50)
#define HWIO_PMCG0_IRQ_CTRL_RMSK                                                     0x1
#define HWIO_PMCG0_IRQ_CTRL_POR                                               0x00000000
#define HWIO_PMCG0_IRQ_CTRL_POR_RMSK                                          0xffffffff
#define HWIO_PMCG0_IRQ_CTRL_ATTR                                                     0x3
#define HWIO_PMCG0_IRQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CTRL_ADDR(x), HWIO_PMCG0_IRQ_CTRL_RMSK)
#define HWIO_PMCG0_IRQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CTRL_ADDR(x), m)
#define HWIO_PMCG0_IRQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_PMCG0_IRQ_CTRL_ADDR(x),v)
#define HWIO_PMCG0_IRQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_IRQ_CTRL_ADDR(x),m,v,HWIO_PMCG0_IRQ_CTRL_IN(x))
#define HWIO_PMCG0_IRQ_CTRL_IRQEN_BMSK                                               0x1
#define HWIO_PMCG0_IRQ_CTRL_IRQEN_SHFT                                               0x0

#define HWIO_PMCG0_IRQ_CTRLACK_ADDR(x)                                        ((x) + 0x00000e54)
#define HWIO_PMCG0_IRQ_CTRLACK_PHYS(x)                                        ((x) + 0x00000e54)
#define HWIO_PMCG0_IRQ_CTRLACK_RMSK                                                  0x1
#define HWIO_PMCG0_IRQ_CTRLACK_POR                                            0x00000000
#define HWIO_PMCG0_IRQ_CTRLACK_POR_RMSK                                       0xffffffff
#define HWIO_PMCG0_IRQ_CTRLACK_ATTR                                                  0x1
#define HWIO_PMCG0_IRQ_CTRLACK_IN(x)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CTRLACK_ADDR(x), HWIO_PMCG0_IRQ_CTRLACK_RMSK)
#define HWIO_PMCG0_IRQ_CTRLACK_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CTRLACK_ADDR(x), m)
#define HWIO_PMCG0_IRQ_CTRLACK_IRQEN_BMSK                                            0x1
#define HWIO_PMCG0_IRQ_CTRLACK_IRQEN_SHFT                                            0x0

#define HWIO_PMCG0_IRQ_CFG0_L_ADDR(x)                                         ((x) + 0x00000e58)
#define HWIO_PMCG0_IRQ_CFG0_L_PHYS(x)                                         ((x) + 0x00000e58)
#define HWIO_PMCG0_IRQ_CFG0_L_RMSK                                            0xfffffffc
#define HWIO_PMCG0_IRQ_CFG0_L_POR                                             0x00000000
#define HWIO_PMCG0_IRQ_CFG0_L_POR_RMSK                                        0xffffffff
#define HWIO_PMCG0_IRQ_CFG0_L_ATTR                                                   0x3
#define HWIO_PMCG0_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CFG0_L_ADDR(x), HWIO_PMCG0_IRQ_CFG0_L_RMSK)
#define HWIO_PMCG0_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_PMCG0_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_PMCG0_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_PMCG0_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_IRQ_CFG0_L_ADDR(x),m,v,HWIO_PMCG0_IRQ_CFG0_L_IN(x))
#define HWIO_PMCG0_IRQ_CFG0_L_ADDR_31_2_BMSK                                  0xfffffffc
#define HWIO_PMCG0_IRQ_CFG0_L_ADDR_31_2_SHFT                                         0x2

#define HWIO_PMCG0_IRQ_CFG0_H_ADDR(x)                                         ((x) + 0x00000e5c)
#define HWIO_PMCG0_IRQ_CFG0_H_PHYS(x)                                         ((x) + 0x00000e5c)
#define HWIO_PMCG0_IRQ_CFG0_H_RMSK                                                0xffff
#define HWIO_PMCG0_IRQ_CFG0_H_POR                                             0x00000000
#define HWIO_PMCG0_IRQ_CFG0_H_POR_RMSK                                        0xffffffff
#define HWIO_PMCG0_IRQ_CFG0_H_ATTR                                                   0x3
#define HWIO_PMCG0_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CFG0_H_ADDR(x), HWIO_PMCG0_IRQ_CFG0_H_RMSK)
#define HWIO_PMCG0_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_PMCG0_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_PMCG0_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_PMCG0_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_IRQ_CFG0_H_ADDR(x),m,v,HWIO_PMCG0_IRQ_CFG0_H_IN(x))
#define HWIO_PMCG0_IRQ_CFG0_H_ADDR_47_32_BMSK                                     0xffff
#define HWIO_PMCG0_IRQ_CFG0_H_ADDR_47_32_SHFT                                        0x0

#define HWIO_PMCG0_IRQ_CFG1_ADDR(x)                                           ((x) + 0x00000e60)
#define HWIO_PMCG0_IRQ_CFG1_PHYS(x)                                           ((x) + 0x00000e60)
#define HWIO_PMCG0_IRQ_CFG1_RMSK                                              0xffffffff
#define HWIO_PMCG0_IRQ_CFG1_POR                                               0x00000000
#define HWIO_PMCG0_IRQ_CFG1_POR_RMSK                                          0xffffffff
#define HWIO_PMCG0_IRQ_CFG1_ATTR                                                     0x3
#define HWIO_PMCG0_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CFG1_ADDR(x), HWIO_PMCG0_IRQ_CFG1_RMSK)
#define HWIO_PMCG0_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CFG1_ADDR(x), m)
#define HWIO_PMCG0_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_PMCG0_IRQ_CFG1_ADDR(x),v)
#define HWIO_PMCG0_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_IRQ_CFG1_ADDR(x),m,v,HWIO_PMCG0_IRQ_CFG1_IN(x))
#define HWIO_PMCG0_IRQ_CFG1_DATA_BMSK                                         0xffffffff
#define HWIO_PMCG0_IRQ_CFG1_DATA_SHFT                                                0x0

#define HWIO_PMCG0_IRQ_CFG2_ADDR(x)                                           ((x) + 0x00000e64)
#define HWIO_PMCG0_IRQ_CFG2_PHYS(x)                                           ((x) + 0x00000e64)
#define HWIO_PMCG0_IRQ_CFG2_RMSK                                                    0x3f
#define HWIO_PMCG0_IRQ_CFG2_POR                                               0x00000000
#define HWIO_PMCG0_IRQ_CFG2_POR_RMSK                                          0xffffffff
#define HWIO_PMCG0_IRQ_CFG2_ATTR                                                     0x3
#define HWIO_PMCG0_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CFG2_ADDR(x), HWIO_PMCG0_IRQ_CFG2_RMSK)
#define HWIO_PMCG0_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_IRQ_CFG2_ADDR(x), m)
#define HWIO_PMCG0_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_PMCG0_IRQ_CFG2_ADDR(x),v)
#define HWIO_PMCG0_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG0_IRQ_CFG2_ADDR(x),m,v,HWIO_PMCG0_IRQ_CFG2_IN(x))
#define HWIO_PMCG0_IRQ_CFG2_SH_BMSK                                                 0x30
#define HWIO_PMCG0_IRQ_CFG2_SH_SHFT                                                  0x4
#define HWIO_PMCG0_IRQ_CFG2_MEMATTR_BMSK                                             0xf
#define HWIO_PMCG0_IRQ_CFG2_MEMATTR_SHFT                                             0x0

#define HWIO_PMCG0_AIDR_ADDR(x)                                               ((x) + 0x00000e70)
#define HWIO_PMCG0_AIDR_PHYS(x)                                               ((x) + 0x00000e70)
#define HWIO_PMCG0_AIDR_RMSK                                                        0xff
#define HWIO_PMCG0_AIDR_POR                                                   0x00000000
#define HWIO_PMCG0_AIDR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG0_AIDR_ATTR                                                         0x1
#define HWIO_PMCG0_AIDR_IN(x)      \
        in_dword_masked(HWIO_PMCG0_AIDR_ADDR(x), HWIO_PMCG0_AIDR_RMSK)
#define HWIO_PMCG0_AIDR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_AIDR_ADDR(x), m)
#define HWIO_PMCG0_AIDR_ARCHMAJORREC_BMSK                                           0xf0
#define HWIO_PMCG0_AIDR_ARCHMAJORREC_SHFT                                            0x4
#define HWIO_PMCG0_AIDR_ARCHMINORREV_BMSK                                            0xf
#define HWIO_PMCG0_AIDR_ARCHMINORREV_SHFT                                            0x0

#define HWIO_PMCG0_IMPDEF0_FILTERn_ADDR(base,n)                               ((base) + 0x00000ec0 + 0x8 * (n))
#define HWIO_PMCG0_IMPDEF0_FILTERn_PHYS(base,n)                               ((base) + 0x00000ec0 + 0x8 * (n))
#define HWIO_PMCG0_IMPDEF0_FILTERn_RMSK                                       0x7fffffff
#define HWIO_PMCG0_IMPDEF0_FILTERn_MAXn                                                7
#define HWIO_PMCG0_IMPDEF0_FILTERn_POR                                        0x78003f8f
#define HWIO_PMCG0_IMPDEF0_FILTERn_POR_RMSK                                   0xffffffff
#define HWIO_PMCG0_IMPDEF0_FILTERn_ATTR                                              0x3
#define HWIO_PMCG0_IMPDEF0_FILTERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG0_IMPDEF0_FILTERn_ADDR(base,n), HWIO_PMCG0_IMPDEF0_FILTERn_RMSK)
#define HWIO_PMCG0_IMPDEF0_FILTERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG0_IMPDEF0_FILTERn_ADDR(base,n), mask)
#define HWIO_PMCG0_IMPDEF0_FILTERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG0_IMPDEF0_FILTERn_ADDR(base,n),val)
#define HWIO_PMCG0_IMPDEF0_FILTERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG0_IMPDEF0_FILTERn_ADDR(base,n),mask,val,HWIO_PMCG0_IMPDEF0_FILTERn_INI(base,n))
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_TLB_S1_BMSK                          0x40000000
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_TLB_S1_SHFT                                0x1e
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_TLB_S1_NF_BMSK                       0x20000000
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_TLB_S1_NF_SHFT                             0x1d
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_TLB_S2_BMSK                          0x10000000
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_TLB_S2_SHFT                                0x1c
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_TLB_S2_NF_BMSK                        0x8000000
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_TLB_S2_NF_SHFT                             0x1b
#define HWIO_PMCG0_IMPDEF0_FILTERn_FILTER_TLB_INDEX_EN_BMSK                    0x4000000
#define HWIO_PMCG0_IMPDEF0_FILTERn_FILTER_TLB_INDEX_EN_SHFT                         0x1a
#define HWIO_PMCG0_IMPDEF0_FILTERn_TLB_INDEX_BMSK                              0x3ffc000
#define HWIO_PMCG0_IMPDEF0_FILTERn_TLB_INDEX_SHFT                                    0xe
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_S1_BMSK                              0x2000
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_S1_SHFT                                 0xd
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_S2_BMSK                              0x1000
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_S2_SHFT                                 0xc
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_CDIPA2PA_BMSK                         0x800
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_CDIPA2PA_SHFT                           0xb
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_LEV0_BMSK                             0x400
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_LEV0_SHFT                               0xa
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_LEV1_BMSK                             0x200
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_LEV1_SHFT                               0x9
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_LEV2_BMSK                             0x100
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_LEV2_SHFT                               0x8
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_LEV3_BMSK                              0x80
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_HTW_LEV3_SHFT                               0x7
#define HWIO_PMCG0_IMPDEF0_FILTERn_FILTER_ALLOC_POLICY_EN_BMSK                      0x40
#define HWIO_PMCG0_IMPDEF0_FILTERn_FILTER_ALLOC_POLICY_EN_SHFT                       0x6
#define HWIO_PMCG0_IMPDEF0_FILTERn_ALLOC_POLICY_BMSK                                0x30
#define HWIO_PMCG0_IMPDEF0_FILTERn_ALLOC_POLICY_SHFT                                 0x4
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_CFG_STE_L1_BMSK                             0x8
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_CFG_STE_L1_SHFT                             0x3
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_CFG_STE_L2_BMSK                             0x4
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_CFG_STE_L2_SHFT                             0x2
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_CFG_CD_L1_BMSK                              0x2
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_CFG_CD_L1_SHFT                              0x1
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_CFG_CD_L2_BMSK                              0x1
#define HWIO_PMCG0_IMPDEF0_FILTERn_COUNT_CFG_CD_L2_SHFT                              0x0

#define HWIO_PMCG0_IMPDEF1_FILTERn_ADDR(base,n)                               ((base) + 0x00000ec4 + 0x8 * (n))
#define HWIO_PMCG0_IMPDEF1_FILTERn_PHYS(base,n)                               ((base) + 0x00000ec4 + 0x8 * (n))
#define HWIO_PMCG0_IMPDEF1_FILTERn_RMSK                                       0xffffffff
#define HWIO_PMCG0_IMPDEF1_FILTERn_MAXn                                                7
#define HWIO_PMCG0_IMPDEF1_FILTERn_POR                                        0x0f800000
#define HWIO_PMCG0_IMPDEF1_FILTERn_POR_RMSK                                   0xffffffff
#define HWIO_PMCG0_IMPDEF1_FILTERn_ATTR                                              0x3
#define HWIO_PMCG0_IMPDEF1_FILTERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG0_IMPDEF1_FILTERn_ADDR(base,n), HWIO_PMCG0_IMPDEF1_FILTERn_RMSK)
#define HWIO_PMCG0_IMPDEF1_FILTERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG0_IMPDEF1_FILTERn_ADDR(base,n), mask)
#define HWIO_PMCG0_IMPDEF1_FILTERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG0_IMPDEF1_FILTERn_ADDR(base,n),val)
#define HWIO_PMCG0_IMPDEF1_FILTERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG0_IMPDEF1_FILTERn_ADDR(base,n),mask,val,HWIO_PMCG0_IMPDEF1_FILTERn_INI(base,n))
#define HWIO_PMCG0_IMPDEF1_FILTERn_COUNT_MID_EN_BMSK                          0x80000000
#define HWIO_PMCG0_IMPDEF1_FILTERn_COUNT_MID_EN_SHFT                                0x1f
#define HWIO_PMCG0_IMPDEF1_FILTERn_MID_HI_BMSK                                0x70000000
#define HWIO_PMCG0_IMPDEF1_FILTERn_MID_HI_SHFT                                      0x1c
#define HWIO_PMCG0_IMPDEF1_FILTERn_COUNT_TRAN_SRC_MID_LO_BMSK                  0xf800000
#define HWIO_PMCG0_IMPDEF1_FILTERn_COUNT_TRAN_SRC_MID_LO_SHFT                       0x17
#define HWIO_PMCG0_IMPDEF1_FILTERn_COUNT_SSID_VALID_EN_BMSK                     0x400000
#define HWIO_PMCG0_IMPDEF1_FILTERn_COUNT_SSID_VALID_EN_SHFT                         0x16
#define HWIO_PMCG0_IMPDEF1_FILTERn_SSID_VALID_BMSK                              0x200000
#define HWIO_PMCG0_IMPDEF1_FILTERn_SSID_VALID_SHFT                                  0x15
#define HWIO_PMCG0_IMPDEF1_FILTERn_COUNT_SSID_SPAN_EN_BMSK                      0x100000
#define HWIO_PMCG0_IMPDEF1_FILTERn_COUNT_SSID_SPAN_EN_SHFT                          0x14
#define HWIO_PMCG0_IMPDEF1_FILTERn_SSID_BMSK                                     0xfffff
#define HWIO_PMCG0_IMPDEF1_FILTERn_SSID_SHFT                                         0x0

#define HWIO_PMCG0_PIDR4_ADDR(x)                                              ((x) + 0x00000fd0)
#define HWIO_PMCG0_PIDR4_PHYS(x)                                              ((x) + 0x00000fd0)
#define HWIO_PMCG0_PIDR4_RMSK                                                       0xff
#define HWIO_PMCG0_PIDR4_POR                                                  0x00000000
#define HWIO_PMCG0_PIDR4_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_PIDR4_ATTR                                                        0x1
#define HWIO_PMCG0_PIDR4_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PIDR4_ADDR(x), HWIO_PMCG0_PIDR4_RMSK)
#define HWIO_PMCG0_PIDR4_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PIDR4_ADDR(x), m)
#define HWIO_PMCG0_PIDR4_SIZE_BMSK                                                  0xff
#define HWIO_PMCG0_PIDR4_SIZE_SHFT                                                   0x0

#define HWIO_PMCG0_PIDR5_ADDR(x)                                              ((x) + 0x00000fd4)
#define HWIO_PMCG0_PIDR5_PHYS(x)                                              ((x) + 0x00000fd4)
#define HWIO_PMCG0_PIDR5_RMSK                                                 0xffffffff
#define HWIO_PMCG0_PIDR5_POR                                                  0x00000000
#define HWIO_PMCG0_PIDR5_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_PIDR5_ATTR                                                        0x1
#define HWIO_PMCG0_PIDR5_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PIDR5_ADDR(x), HWIO_PMCG0_PIDR5_RMSK)
#define HWIO_PMCG0_PIDR5_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PIDR5_ADDR(x), m)
#define HWIO_PMCG0_PIDR5_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG0_PIDR5_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG0_PIDR6_ADDR(x)                                              ((x) + 0x00000fd8)
#define HWIO_PMCG0_PIDR6_PHYS(x)                                              ((x) + 0x00000fd8)
#define HWIO_PMCG0_PIDR6_RMSK                                                 0xffffffff
#define HWIO_PMCG0_PIDR6_POR                                                  0x00000000
#define HWIO_PMCG0_PIDR6_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_PIDR6_ATTR                                                        0x1
#define HWIO_PMCG0_PIDR6_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PIDR6_ADDR(x), HWIO_PMCG0_PIDR6_RMSK)
#define HWIO_PMCG0_PIDR6_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PIDR6_ADDR(x), m)
#define HWIO_PMCG0_PIDR6_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG0_PIDR6_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG0_PIDR7_ADDR(x)                                              ((x) + 0x00000fdc)
#define HWIO_PMCG0_PIDR7_PHYS(x)                                              ((x) + 0x00000fdc)
#define HWIO_PMCG0_PIDR7_RMSK                                                 0xffffffff
#define HWIO_PMCG0_PIDR7_POR                                                  0x00000000
#define HWIO_PMCG0_PIDR7_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_PIDR7_ATTR                                                        0x1
#define HWIO_PMCG0_PIDR7_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PIDR7_ADDR(x), HWIO_PMCG0_PIDR7_RMSK)
#define HWIO_PMCG0_PIDR7_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PIDR7_ADDR(x), m)
#define HWIO_PMCG0_PIDR7_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG0_PIDR7_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG0_PIDR0_ADDR(x)                                              ((x) + 0x00000fe0)
#define HWIO_PMCG0_PIDR0_PHYS(x)                                              ((x) + 0x00000fe0)
#define HWIO_PMCG0_PIDR0_RMSK                                                       0xff
#define HWIO_PMCG0_PIDR0_POR                                                  0x00000040
#define HWIO_PMCG0_PIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_PIDR0_ATTR                                                        0x1
#define HWIO_PMCG0_PIDR0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PIDR0_ADDR(x), HWIO_PMCG0_PIDR0_RMSK)
#define HWIO_PMCG0_PIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PIDR0_ADDR(x), m)
#define HWIO_PMCG0_PIDR0_PART_0_BMSK                                                0xff
#define HWIO_PMCG0_PIDR0_PART_0_SHFT                                                 0x0

#define HWIO_PMCG0_PIDR1_ADDR(x)                                              ((x) + 0x00000fe4)
#define HWIO_PMCG0_PIDR1_PHYS(x)                                              ((x) + 0x00000fe4)
#define HWIO_PMCG0_PIDR1_RMSK                                                      0xf0f
#define HWIO_PMCG0_PIDR1_POR                                                  0x00000000
#define HWIO_PMCG0_PIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_PIDR1_ATTR                                                        0x1
#define HWIO_PMCG0_PIDR1_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PIDR1_ADDR(x), HWIO_PMCG0_PIDR1_RMSK)
#define HWIO_PMCG0_PIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PIDR1_ADDR(x), m)
#define HWIO_PMCG0_PIDR1_PART_1_BMSK                                               0xf00
#define HWIO_PMCG0_PIDR1_PART_1_SHFT                                                 0x8
#define HWIO_PMCG0_PIDR1_DES_0_BMSK                                                  0xf
#define HWIO_PMCG0_PIDR1_DES_0_SHFT                                                  0x0

#define HWIO_PMCG0_PIDR2_ADDR(x)                                              ((x) + 0x00000fe8)
#define HWIO_PMCG0_PIDR2_PHYS(x)                                              ((x) + 0x00000fe8)
#define HWIO_PMCG0_PIDR2_RMSK                                                       0xff
#define HWIO_PMCG0_PIDR2_POR                                                  0x0000003f
#define HWIO_PMCG0_PIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_PIDR2_ATTR                                                        0x1
#define HWIO_PMCG0_PIDR2_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PIDR2_ADDR(x), HWIO_PMCG0_PIDR2_RMSK)
#define HWIO_PMCG0_PIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PIDR2_ADDR(x), m)
#define HWIO_PMCG0_PIDR2_REVISION_BMSK                                              0xf0
#define HWIO_PMCG0_PIDR2_REVISION_SHFT                                               0x4
#define HWIO_PMCG0_PIDR2_JEDEC_VAL_BMSK                                              0x8
#define HWIO_PMCG0_PIDR2_JEDEC_VAL_SHFT                                              0x3
#define HWIO_PMCG0_PIDR2_DES_1_BMSK                                                  0x7
#define HWIO_PMCG0_PIDR2_DES_1_SHFT                                                  0x0

#define HWIO_PMCG0_PIDR3_ADDR(x)                                              ((x) + 0x00000fec)
#define HWIO_PMCG0_PIDR3_PHYS(x)                                              ((x) + 0x00000fec)
#define HWIO_PMCG0_PIDR3_RMSK                                                       0xff
#define HWIO_PMCG0_PIDR3_POR                                                  0x00000000
#define HWIO_PMCG0_PIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_PIDR3_ATTR                                                        0x1
#define HWIO_PMCG0_PIDR3_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PIDR3_ADDR(x), HWIO_PMCG0_PIDR3_RMSK)
#define HWIO_PMCG0_PIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PIDR3_ADDR(x), m)
#define HWIO_PMCG0_PIDR3_REVAND_BMSK                                                0xf0
#define HWIO_PMCG0_PIDR3_REVAND_SHFT                                                 0x4
#define HWIO_PMCG0_PIDR3_CMOD_BMSK                                                   0xf
#define HWIO_PMCG0_PIDR3_CMOD_SHFT                                                   0x0

#define HWIO_PMCG0_CIDR0_ADDR(x)                                              ((x) + 0x00000ff0)
#define HWIO_PMCG0_CIDR0_PHYS(x)                                              ((x) + 0x00000ff0)
#define HWIO_PMCG0_CIDR0_RMSK                                                 0xffffffff
#define HWIO_PMCG0_CIDR0_POR                                                  0x0000000d
#define HWIO_PMCG0_CIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_CIDR0_ATTR                                                        0x1
#define HWIO_PMCG0_CIDR0_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CIDR0_ADDR(x), HWIO_PMCG0_CIDR0_RMSK)
#define HWIO_PMCG0_CIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CIDR0_ADDR(x), m)
#define HWIO_PMCG0_CIDR0_COMPONENT_IDR0_BMSK                                  0xffffffff
#define HWIO_PMCG0_CIDR0_COMPONENT_IDR0_SHFT                                         0x0

#define HWIO_PMCG0_CIDR1_ADDR(x)                                              ((x) + 0x00000ff4)
#define HWIO_PMCG0_CIDR1_PHYS(x)                                              ((x) + 0x00000ff4)
#define HWIO_PMCG0_CIDR1_RMSK                                                 0xffffffff
#define HWIO_PMCG0_CIDR1_POR                                                  0x000000f0
#define HWIO_PMCG0_CIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_CIDR1_ATTR                                                        0x1
#define HWIO_PMCG0_CIDR1_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CIDR1_ADDR(x), HWIO_PMCG0_CIDR1_RMSK)
#define HWIO_PMCG0_CIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CIDR1_ADDR(x), m)
#define HWIO_PMCG0_CIDR1_COMPONENT_IDR1_BMSK                                  0xffffffff
#define HWIO_PMCG0_CIDR1_COMPONENT_IDR1_SHFT                                         0x0

#define HWIO_PMCG0_CIDR2_ADDR(x)                                              ((x) + 0x00000ff8)
#define HWIO_PMCG0_CIDR2_PHYS(x)                                              ((x) + 0x00000ff8)
#define HWIO_PMCG0_CIDR2_RMSK                                                 0xffffffff
#define HWIO_PMCG0_CIDR2_POR                                                  0x00000005
#define HWIO_PMCG0_CIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_CIDR2_ATTR                                                        0x1
#define HWIO_PMCG0_CIDR2_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CIDR2_ADDR(x), HWIO_PMCG0_CIDR2_RMSK)
#define HWIO_PMCG0_CIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CIDR2_ADDR(x), m)
#define HWIO_PMCG0_CIDR2_COMPONENT_IDR2_BMSK                                  0xffffffff
#define HWIO_PMCG0_CIDR2_COMPONENT_IDR2_SHFT                                         0x0

#define HWIO_PMCG0_CIDR3_ADDR(x)                                              ((x) + 0x00000ffc)
#define HWIO_PMCG0_CIDR3_PHYS(x)                                              ((x) + 0x00000ffc)
#define HWIO_PMCG0_CIDR3_RMSK                                                 0xffffffff
#define HWIO_PMCG0_CIDR3_POR                                                  0x000000b1
#define HWIO_PMCG0_CIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PMCG0_CIDR3_ATTR                                                        0x1
#define HWIO_PMCG0_CIDR3_IN(x)      \
        in_dword_masked(HWIO_PMCG0_CIDR3_ADDR(x), HWIO_PMCG0_CIDR3_RMSK)
#define HWIO_PMCG0_CIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_CIDR3_ADDR(x), m)
#define HWIO_PMCG0_CIDR3_COMPONENT_IDR3_BMSK                                  0xffffffff
#define HWIO_PMCG0_CIDR3_COMPONENT_IDR3_SHFT                                         0x0

#define HWIO_PMCG0_PMAUTHSTATUS_ADDR(x)                                       ((x) + 0x00000fb8)
#define HWIO_PMCG0_PMAUTHSTATUS_PHYS(x)                                       ((x) + 0x00000fb8)
#define HWIO_PMCG0_PMAUTHSTATUS_RMSK                                                0xff
#define HWIO_PMCG0_PMAUTHSTATUS_POR                                           0x00000088
#define HWIO_PMCG0_PMAUTHSTATUS_POR_RMSK                                      0xffffffff
#define HWIO_PMCG0_PMAUTHSTATUS_ATTR                                                 0x1
#define HWIO_PMCG0_PMAUTHSTATUS_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PMAUTHSTATUS_ADDR(x), HWIO_PMCG0_PMAUTHSTATUS_RMSK)
#define HWIO_PMCG0_PMAUTHSTATUS_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PMAUTHSTATUS_ADDR(x), m)
#define HWIO_PMCG0_PMAUTHSTATUS_AUTHSTATUS_BMSK                                     0xff
#define HWIO_PMCG0_PMAUTHSTATUS_AUTHSTATUS_SHFT                                      0x0

#define HWIO_PMCG0_PMDEVARCH_ADDR(x)                                          ((x) + 0x00000fbc)
#define HWIO_PMCG0_PMDEVARCH_PHYS(x)                                          ((x) + 0x00000fbc)
#define HWIO_PMCG0_PMDEVARCH_RMSK                                             0xffffffff
#define HWIO_PMCG0_PMDEVARCH_POR                                              0x0e102a56
#define HWIO_PMCG0_PMDEVARCH_POR_RMSK                                         0xffffffff
#define HWIO_PMCG0_PMDEVARCH_ATTR                                                    0x1
#define HWIO_PMCG0_PMDEVARCH_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PMDEVARCH_ADDR(x), HWIO_PMCG0_PMDEVARCH_RMSK)
#define HWIO_PMCG0_PMDEVARCH_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PMDEVARCH_ADDR(x), m)
#define HWIO_PMCG0_PMDEVARCH_ARCHITECT_BMSK                                   0xffe00000
#define HWIO_PMCG0_PMDEVARCH_ARCHITECT_SHFT                                         0x15
#define HWIO_PMCG0_PMDEVARCH_PRESENT_BMSK                                       0x100000
#define HWIO_PMCG0_PMDEVARCH_PRESENT_SHFT                                           0x14
#define HWIO_PMCG0_PMDEVARCH_REVISION_BMSK                                       0xf0000
#define HWIO_PMCG0_PMDEVARCH_REVISION_SHFT                                          0x10
#define HWIO_PMCG0_PMDEVARCH_ARCHID_BMSK                                          0xffff
#define HWIO_PMCG0_PMDEVARCH_ARCHID_SHFT                                             0x0

#define HWIO_PMCG0_PMDEVTYPE_ADDR(x)                                          ((x) + 0x00000fcc)
#define HWIO_PMCG0_PMDEVTYPE_PHYS(x)                                          ((x) + 0x00000fcc)
#define HWIO_PMCG0_PMDEVTYPE_RMSK                                                   0xff
#define HWIO_PMCG0_PMDEVTYPE_POR                                              0x00000056
#define HWIO_PMCG0_PMDEVTYPE_POR_RMSK                                         0xffffffff
#define HWIO_PMCG0_PMDEVTYPE_ATTR                                                    0x1
#define HWIO_PMCG0_PMDEVTYPE_IN(x)      \
        in_dword_masked(HWIO_PMCG0_PMDEVTYPE_ADDR(x), HWIO_PMCG0_PMDEVTYPE_RMSK)
#define HWIO_PMCG0_PMDEVTYPE_INM(x, m)      \
        in_dword_masked(HWIO_PMCG0_PMDEVTYPE_ADDR(x), m)
#define HWIO_PMCG0_PMDEVTYPE_SUB_TYPE_BMSK                                          0xf0
#define HWIO_PMCG0_PMDEVTYPE_SUB_TYPE_SHFT                                           0x4
#define HWIO_PMCG0_PMDEVTYPE_CLASS_BMSK                                              0xf
#define HWIO_PMCG0_PMDEVTYPE_CLASS_SHFT                                              0x0

#define HWIO_PMCG1_EVCNTR_Ln_ADDR(base,n)                                     ((base) + 0x00011000 + 0x4 * (n))
#define HWIO_PMCG1_EVCNTR_Ln_PHYS(base,n)                                     ((base) + 0x00011000 + 0x4 * (n))
#define HWIO_PMCG1_EVCNTR_Ln_RMSK                                             0xffffffff
#define HWIO_PMCG1_EVCNTR_Ln_MAXn                                                      7
#define HWIO_PMCG1_EVCNTR_Ln_POR                                              0x00000000
#define HWIO_PMCG1_EVCNTR_Ln_POR_RMSK                                         0xffffffff
#define HWIO_PMCG1_EVCNTR_Ln_ATTR                                                    0x3
#define HWIO_PMCG1_EVCNTR_Ln_INI(base,n)        \
        in_dword_masked(HWIO_PMCG1_EVCNTR_Ln_ADDR(base,n), HWIO_PMCG1_EVCNTR_Ln_RMSK)
#define HWIO_PMCG1_EVCNTR_Ln_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG1_EVCNTR_Ln_ADDR(base,n), mask)
#define HWIO_PMCG1_EVCNTR_Ln_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG1_EVCNTR_Ln_ADDR(base,n),val)
#define HWIO_PMCG1_EVCNTR_Ln_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG1_EVCNTR_Ln_ADDR(base,n),mask,val,HWIO_PMCG1_EVCNTR_Ln_INI(base,n))
#define HWIO_PMCG1_EVCNTR_Ln_COUNTER_VALUE_BMSK                               0xffffffff
#define HWIO_PMCG1_EVCNTR_Ln_COUNTER_VALUE_SHFT                                      0x0

#define HWIO_PMCG1_EVTYPERn_ADDR(base,n)                                      ((base) + 0x00001400 + 0x4 * (n))
#define HWIO_PMCG1_EVTYPERn_PHYS(base,n)                                      ((base) + 0x00001400 + 0x4 * (n))
#define HWIO_PMCG1_EVTYPERn_RMSK                                              0xe000ffff
#define HWIO_PMCG1_EVTYPERn_MAXn                                                       7
#define HWIO_PMCG1_EVTYPERn_POR                                               0x0000ffff
#define HWIO_PMCG1_EVTYPERn_POR_RMSK                                          0xffffffff
#define HWIO_PMCG1_EVTYPERn_ATTR                                                     0x3
#define HWIO_PMCG1_EVTYPERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG1_EVTYPERn_ADDR(base,n), HWIO_PMCG1_EVTYPERn_RMSK)
#define HWIO_PMCG1_EVTYPERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG1_EVTYPERn_ADDR(base,n), mask)
#define HWIO_PMCG1_EVTYPERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG1_EVTYPERn_ADDR(base,n),val)
#define HWIO_PMCG1_EVTYPERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG1_EVTYPERn_ADDR(base,n),mask,val,HWIO_PMCG1_EVTYPERn_INI(base,n))
#define HWIO_PMCG1_EVTYPERn_OVFCAP_BMSK                                       0x80000000
#define HWIO_PMCG1_EVTYPERn_OVFCAP_SHFT                                             0x1f
#define HWIO_PMCG1_EVTYPERn_FILTER_SEC_SID_BMSK                               0x40000000
#define HWIO_PMCG1_EVTYPERn_FILTER_SEC_SID_SHFT                                     0x1e
#define HWIO_PMCG1_EVTYPERn_FILTER_SID_SPAN_BMSK                              0x20000000
#define HWIO_PMCG1_EVTYPERn_FILTER_SID_SPAN_SHFT                                    0x1d
#define HWIO_PMCG1_EVTYPERn_EVENT_BMSK                                            0xffff
#define HWIO_PMCG1_EVTYPERn_EVENT_SHFT                                               0x0

#define HWIO_PMCG1_SVR_Ln_ADDR(base,n)                                        ((base) + 0x00011600 + 0x4 * (n))
#define HWIO_PMCG1_SVR_Ln_PHYS(base,n)                                        ((base) + 0x00011600 + 0x4 * (n))
#define HWIO_PMCG1_SVR_Ln_RMSK                                                0xffffffff
#define HWIO_PMCG1_SVR_Ln_MAXn                                                         7
#define HWIO_PMCG1_SVR_Ln_POR                                                 0x00000000
#define HWIO_PMCG1_SVR_Ln_POR_RMSK                                            0xffffffff
#define HWIO_PMCG1_SVR_Ln_ATTR                                                       0x1
#define HWIO_PMCG1_SVR_Ln_INI(base,n)        \
        in_dword_masked(HWIO_PMCG1_SVR_Ln_ADDR(base,n), HWIO_PMCG1_SVR_Ln_RMSK)
#define HWIO_PMCG1_SVR_Ln_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG1_SVR_Ln_ADDR(base,n), mask)
#define HWIO_PMCG1_SVR_Ln_SHADOW_COUNTER_VALUE_BMSK                           0xffffffff
#define HWIO_PMCG1_SVR_Ln_SHADOW_COUNTER_VALUE_SHFT                                  0x0

#define HWIO_PMCG1_SMRn_ADDR(base,n)                                          ((base) + 0x00001a00 + 0x4 * (n))
#define HWIO_PMCG1_SMRn_PHYS(base,n)                                          ((base) + 0x00001a00 + 0x4 * (n))
#define HWIO_PMCG1_SMRn_RMSK                                                      0xffff
#define HWIO_PMCG1_SMRn_MAXn                                                           7
#define HWIO_PMCG1_SMRn_POR                                                   0x00000000
#define HWIO_PMCG1_SMRn_POR_RMSK                                              0xffffffff
#define HWIO_PMCG1_SMRn_ATTR                                                         0x3
#define HWIO_PMCG1_SMRn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG1_SMRn_ADDR(base,n), HWIO_PMCG1_SMRn_RMSK)
#define HWIO_PMCG1_SMRn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG1_SMRn_ADDR(base,n), mask)
#define HWIO_PMCG1_SMRn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG1_SMRn_ADDR(base,n),val)
#define HWIO_PMCG1_SMRn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG1_SMRn_ADDR(base,n),mask,val,HWIO_PMCG1_SMRn_INI(base,n))
#define HWIO_PMCG1_SMRn_STREAMID_BMSK                                             0xffff
#define HWIO_PMCG1_SMRn_STREAMID_SHFT                                                0x0

#define HWIO_PMCG1_CNTENSET0_ADDR(x)                                          ((x) + 0x00001c00)
#define HWIO_PMCG1_CNTENSET0_PHYS(x)                                          ((x) + 0x00001c00)
#define HWIO_PMCG1_CNTENSET0_RMSK                                                   0xff
#define HWIO_PMCG1_CNTENSET0_POR                                              0x00000000
#define HWIO_PMCG1_CNTENSET0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG1_CNTENSET0_ATTR                                                    0x3
#define HWIO_PMCG1_CNTENSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CNTENSET0_ADDR(x), HWIO_PMCG1_CNTENSET0_RMSK)
#define HWIO_PMCG1_CNTENSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CNTENSET0_ADDR(x), m)
#define HWIO_PMCG1_CNTENSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG1_CNTENSET0_ADDR(x),v)
#define HWIO_PMCG1_CNTENSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_CNTENSET0_ADDR(x),m,v,HWIO_PMCG1_CNTENSET0_IN(x))
#define HWIO_PMCG1_CNTENSET0_CNTEN_BMSK                                             0xff
#define HWIO_PMCG1_CNTENSET0_CNTEN_SHFT                                              0x0

#define HWIO_PMCG1_CNTENCLR0_ADDR(x)                                          ((x) + 0x00001c20)
#define HWIO_PMCG1_CNTENCLR0_PHYS(x)                                          ((x) + 0x00001c20)
#define HWIO_PMCG1_CNTENCLR0_RMSK                                                   0xff
#define HWIO_PMCG1_CNTENCLR0_POR                                              0x00000000
#define HWIO_PMCG1_CNTENCLR0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG1_CNTENCLR0_ATTR                                                    0x3
#define HWIO_PMCG1_CNTENCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CNTENCLR0_ADDR(x), HWIO_PMCG1_CNTENCLR0_RMSK)
#define HWIO_PMCG1_CNTENCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CNTENCLR0_ADDR(x), m)
#define HWIO_PMCG1_CNTENCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG1_CNTENCLR0_ADDR(x),v)
#define HWIO_PMCG1_CNTENCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_CNTENCLR0_ADDR(x),m,v,HWIO_PMCG1_CNTENCLR0_IN(x))
#define HWIO_PMCG1_CNTENCLR0_CNTEN_BMSK                                             0xff
#define HWIO_PMCG1_CNTENCLR0_CNTEN_SHFT                                              0x0

#define HWIO_PMCG1_INTENSET0_ADDR(x)                                          ((x) + 0x00001c40)
#define HWIO_PMCG1_INTENSET0_PHYS(x)                                          ((x) + 0x00001c40)
#define HWIO_PMCG1_INTENSET0_RMSK                                                   0xff
#define HWIO_PMCG1_INTENSET0_POR                                              0x00000000
#define HWIO_PMCG1_INTENSET0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG1_INTENSET0_ATTR                                                    0x3
#define HWIO_PMCG1_INTENSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_INTENSET0_ADDR(x), HWIO_PMCG1_INTENSET0_RMSK)
#define HWIO_PMCG1_INTENSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_INTENSET0_ADDR(x), m)
#define HWIO_PMCG1_INTENSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG1_INTENSET0_ADDR(x),v)
#define HWIO_PMCG1_INTENSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_INTENSET0_ADDR(x),m,v,HWIO_PMCG1_INTENSET0_IN(x))
#define HWIO_PMCG1_INTENSET0_INTEN_BMSK                                             0xff
#define HWIO_PMCG1_INTENSET0_INTEN_SHFT                                              0x0

#define HWIO_PMCG1_INTENCLR0_ADDR(x)                                          ((x) + 0x00001c60)
#define HWIO_PMCG1_INTENCLR0_PHYS(x)                                          ((x) + 0x00001c60)
#define HWIO_PMCG1_INTENCLR0_RMSK                                                   0xff
#define HWIO_PMCG1_INTENCLR0_POR                                              0x00000000
#define HWIO_PMCG1_INTENCLR0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG1_INTENCLR0_ATTR                                                    0x3
#define HWIO_PMCG1_INTENCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_INTENCLR0_ADDR(x), HWIO_PMCG1_INTENCLR0_RMSK)
#define HWIO_PMCG1_INTENCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_INTENCLR0_ADDR(x), m)
#define HWIO_PMCG1_INTENCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG1_INTENCLR0_ADDR(x),v)
#define HWIO_PMCG1_INTENCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_INTENCLR0_ADDR(x),m,v,HWIO_PMCG1_INTENCLR0_IN(x))
#define HWIO_PMCG1_INTENCLR0_INTEN_BMSK                                             0xff
#define HWIO_PMCG1_INTENCLR0_INTEN_SHFT                                              0x0

#define HWIO_PMCG1_OVSCLR0_ADDR(x)                                            ((x) + 0x00011c80)
#define HWIO_PMCG1_OVSCLR0_PHYS(x)                                            ((x) + 0x00011c80)
#define HWIO_PMCG1_OVSCLR0_RMSK                                                     0xff
#define HWIO_PMCG1_OVSCLR0_POR                                                0x00000000
#define HWIO_PMCG1_OVSCLR0_POR_RMSK                                           0xffffffff
#define HWIO_PMCG1_OVSCLR0_ATTR                                                      0x3
#define HWIO_PMCG1_OVSCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_OVSCLR0_ADDR(x), HWIO_PMCG1_OVSCLR0_RMSK)
#define HWIO_PMCG1_OVSCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_OVSCLR0_ADDR(x), m)
#define HWIO_PMCG1_OVSCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG1_OVSCLR0_ADDR(x),v)
#define HWIO_PMCG1_OVSCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_OVSCLR0_ADDR(x),m,v,HWIO_PMCG1_OVSCLR0_IN(x))
#define HWIO_PMCG1_OVSCLR0_OVS_BMSK                                                 0xff
#define HWIO_PMCG1_OVSCLR0_OVS_SHFT                                                  0x0

#define HWIO_PMCG1_OVSSET0_ADDR(x)                                            ((x) + 0x00011cc0)
#define HWIO_PMCG1_OVSSET0_PHYS(x)                                            ((x) + 0x00011cc0)
#define HWIO_PMCG1_OVSSET0_RMSK                                                     0xff
#define HWIO_PMCG1_OVSSET0_POR                                                0x00000000
#define HWIO_PMCG1_OVSSET0_POR_RMSK                                           0xffffffff
#define HWIO_PMCG1_OVSSET0_ATTR                                                      0x3
#define HWIO_PMCG1_OVSSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_OVSSET0_ADDR(x), HWIO_PMCG1_OVSSET0_RMSK)
#define HWIO_PMCG1_OVSSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_OVSSET0_ADDR(x), m)
#define HWIO_PMCG1_OVSSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG1_OVSSET0_ADDR(x),v)
#define HWIO_PMCG1_OVSSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_OVSSET0_ADDR(x),m,v,HWIO_PMCG1_OVSSET0_IN(x))
#define HWIO_PMCG1_OVSSET0_OVS_BMSK                                                 0xff
#define HWIO_PMCG1_OVSSET0_OVS_SHFT                                                  0x0

#define HWIO_PMCG1_CAPR_ADDR(x)                                               ((x) + 0x00011d88)
#define HWIO_PMCG1_CAPR_PHYS(x)                                               ((x) + 0x00011d88)
#define HWIO_PMCG1_CAPR_RMSK                                                         0x1
#define HWIO_PMCG1_CAPR_POR                                                   0x00000000
#define HWIO_PMCG1_CAPR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG1_CAPR_ATTR                                                         0x2
#define HWIO_PMCG1_CAPR_OUT(x, v)      \
        out_dword(HWIO_PMCG1_CAPR_ADDR(x),v)
#define HWIO_PMCG1_CAPR_CAPTURE_BMSK                                                 0x1
#define HWIO_PMCG1_CAPR_CAPTURE_SHFT                                                 0x0

#define HWIO_PMCG1_SCR_ADDR(x)                                                ((x) + 0x00001df8)
#define HWIO_PMCG1_SCR_PHYS(x)                                                ((x) + 0x00001df8)
#define HWIO_PMCG1_SCR_RMSK                                                   0x80000007
#define HWIO_PMCG1_SCR_POR                                                    0x00000002
#define HWIO_PMCG1_SCR_POR_RMSK                                               0xffffffff
#define HWIO_PMCG1_SCR_ATTR                                                          0x3
#define HWIO_PMCG1_SCR_IN(x)      \
        in_dword_masked(HWIO_PMCG1_SCR_ADDR(x), HWIO_PMCG1_SCR_RMSK)
#define HWIO_PMCG1_SCR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_SCR_ADDR(x), m)
#define HWIO_PMCG1_SCR_OUT(x, v)      \
        out_dword(HWIO_PMCG1_SCR_ADDR(x),v)
#define HWIO_PMCG1_SCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_SCR_ADDR(x),m,v,HWIO_PMCG1_SCR_IN(x))
#define HWIO_PMCG1_SCR_READ_AS_ONE_BMSK                                       0x80000000
#define HWIO_PMCG1_SCR_READ_AS_ONE_SHFT                                             0x1f
#define HWIO_PMCG1_SCR_NSMSI_BMSK                                                    0x4
#define HWIO_PMCG1_SCR_NSMSI_SHFT                                                    0x2
#define HWIO_PMCG1_SCR_NSRA_BMSK                                                     0x2
#define HWIO_PMCG1_SCR_NSRA_SHFT                                                     0x1
#define HWIO_PMCG1_SCR_SO_BMSK                                                       0x1
#define HWIO_PMCG1_SCR_SO_SHFT                                                       0x0

#define HWIO_PMCG1_CFGR_ADDR(x)                                               ((x) + 0x00001e00)
#define HWIO_PMCG1_CFGR_PHYS(x)                                               ((x) + 0x00001e00)
#define HWIO_PMCG1_CFGR_RMSK                                                    0x703f3f
#define HWIO_PMCG1_CFGR_POR                                                   0x00701f07
#define HWIO_PMCG1_CFGR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG1_CFGR_ATTR                                                         0x1
#define HWIO_PMCG1_CFGR_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CFGR_ADDR(x), HWIO_PMCG1_CFGR_RMSK)
#define HWIO_PMCG1_CFGR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CFGR_ADDR(x), m)
#define HWIO_PMCG1_CFGR_CAPTURE_BMSK                                            0x400000
#define HWIO_PMCG1_CFGR_CAPTURE_SHFT                                                0x16
#define HWIO_PMCG1_CFGR_MSI_BMSK                                                0x200000
#define HWIO_PMCG1_CFGR_MSI_SHFT                                                    0x15
#define HWIO_PMCG1_CFGR_RELOC_CTRS_BMSK                                         0x100000
#define HWIO_PMCG1_CFGR_RELOC_CTRS_SHFT                                             0x14
#define HWIO_PMCG1_CFGR_SIZE_BMSK                                                 0x3f00
#define HWIO_PMCG1_CFGR_SIZE_SHFT                                                    0x8
#define HWIO_PMCG1_CFGR_NCTR_BMSK                                                   0x3f
#define HWIO_PMCG1_CFGR_NCTR_SHFT                                                    0x0

#define HWIO_PMCG1_CR_ADDR(x)                                                 ((x) + 0x00001e04)
#define HWIO_PMCG1_CR_PHYS(x)                                                 ((x) + 0x00001e04)
#define HWIO_PMCG1_CR_RMSK                                                           0x1
#define HWIO_PMCG1_CR_POR                                                     0x00000000
#define HWIO_PMCG1_CR_POR_RMSK                                                0xffffffff
#define HWIO_PMCG1_CR_ATTR                                                           0x3
#define HWIO_PMCG1_CR_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CR_ADDR(x), HWIO_PMCG1_CR_RMSK)
#define HWIO_PMCG1_CR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CR_ADDR(x), m)
#define HWIO_PMCG1_CR_OUT(x, v)      \
        out_dword(HWIO_PMCG1_CR_ADDR(x),v)
#define HWIO_PMCG1_CR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_CR_ADDR(x),m,v,HWIO_PMCG1_CR_IN(x))
#define HWIO_PMCG1_CR_E_BMSK                                                         0x1
#define HWIO_PMCG1_CR_E_SHFT                                                         0x0

#define HWIO_PMCG1_CEID0_L_ADDR(x)                                            ((x) + 0x00001e20)
#define HWIO_PMCG1_CEID0_L_PHYS(x)                                            ((x) + 0x00001e20)
#define HWIO_PMCG1_CEID0_L_RMSK                                                     0xff
#define HWIO_PMCG1_CEID0_L_POR                                                0x0000001f
#define HWIO_PMCG1_CEID0_L_POR_RMSK                                           0xffffffff
#define HWIO_PMCG1_CEID0_L_ATTR                                                      0x1
#define HWIO_PMCG1_CEID0_L_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CEID0_L_ADDR(x), HWIO_PMCG1_CEID0_L_RMSK)
#define HWIO_PMCG1_CEID0_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CEID0_L_ADDR(x), m)
#define HWIO_PMCG1_CEID0_L_IMPL_EVENTS_BMSK                                         0xff
#define HWIO_PMCG1_CEID0_L_IMPL_EVENTS_SHFT                                          0x0

#define HWIO_PMCG1_CEID0_H_ADDR(x)                                            ((x) + 0x00001e24)
#define HWIO_PMCG1_CEID0_H_PHYS(x)                                            ((x) + 0x00001e24)
#define HWIO_PMCG1_CEID0_H_RMSK                                               0xffffffff
#define HWIO_PMCG1_CEID0_H_POR                                                0x00000000
#define HWIO_PMCG1_CEID0_H_POR_RMSK                                           0xffffffff
#define HWIO_PMCG1_CEID0_H_ATTR                                                      0x1
#define HWIO_PMCG1_CEID0_H_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CEID0_H_ADDR(x), HWIO_PMCG1_CEID0_H_RMSK)
#define HWIO_PMCG1_CEID0_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CEID0_H_ADDR(x), m)
#define HWIO_PMCG1_CEID0_H_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG1_CEID0_H_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG1_CEID1_L_ADDR(x)                                            ((x) + 0x00001e28)
#define HWIO_PMCG1_CEID1_L_PHYS(x)                                            ((x) + 0x00001e28)
#define HWIO_PMCG1_CEID1_L_RMSK                                               0xffffffff
#define HWIO_PMCG1_CEID1_L_POR                                                0x00000000
#define HWIO_PMCG1_CEID1_L_POR_RMSK                                           0xffffffff
#define HWIO_PMCG1_CEID1_L_ATTR                                                      0x1
#define HWIO_PMCG1_CEID1_L_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CEID1_L_ADDR(x), HWIO_PMCG1_CEID1_L_RMSK)
#define HWIO_PMCG1_CEID1_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CEID1_L_ADDR(x), m)
#define HWIO_PMCG1_CEID1_L_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG1_CEID1_L_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG1_CEID1_H_ADDR(x)                                            ((x) + 0x00001e2c)
#define HWIO_PMCG1_CEID1_H_PHYS(x)                                            ((x) + 0x00001e2c)
#define HWIO_PMCG1_CEID1_H_RMSK                                               0xffffffff
#define HWIO_PMCG1_CEID1_H_POR                                                0x00000000
#define HWIO_PMCG1_CEID1_H_POR_RMSK                                           0xffffffff
#define HWIO_PMCG1_CEID1_H_ATTR                                                      0x1
#define HWIO_PMCG1_CEID1_H_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CEID1_H_ADDR(x), HWIO_PMCG1_CEID1_H_RMSK)
#define HWIO_PMCG1_CEID1_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CEID1_H_ADDR(x), m)
#define HWIO_PMCG1_CEID1_H_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG1_CEID1_H_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG1_IMPL_CEID0_ADDR(x)                                         ((x) + 0x00001e30)
#define HWIO_PMCG1_IMPL_CEID0_PHYS(x)                                         ((x) + 0x00001e30)
#define HWIO_PMCG1_IMPL_CEID0_RMSK                                                  0x3f
#define HWIO_PMCG1_IMPL_CEID0_POR                                             0x00000000
#define HWIO_PMCG1_IMPL_CEID0_POR_RMSK                                        0xffffffff
#define HWIO_PMCG1_IMPL_CEID0_ATTR                                                   0x1
#define HWIO_PMCG1_IMPL_CEID0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_IMPL_CEID0_ADDR(x), HWIO_PMCG1_IMPL_CEID0_RMSK)
#define HWIO_PMCG1_IMPL_CEID0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_IMPL_CEID0_ADDR(x), m)
#define HWIO_PMCG1_IMPL_CEID0_IMPL_EVENTS_BMSK                                      0x3f
#define HWIO_PMCG1_IMPL_CEID0_IMPL_EVENTS_SHFT                                       0x0

#define HWIO_PMCG1_IRQ_CTRL_ADDR(x)                                           ((x) + 0x00001e50)
#define HWIO_PMCG1_IRQ_CTRL_PHYS(x)                                           ((x) + 0x00001e50)
#define HWIO_PMCG1_IRQ_CTRL_RMSK                                                     0x1
#define HWIO_PMCG1_IRQ_CTRL_POR                                               0x00000000
#define HWIO_PMCG1_IRQ_CTRL_POR_RMSK                                          0xffffffff
#define HWIO_PMCG1_IRQ_CTRL_ATTR                                                     0x3
#define HWIO_PMCG1_IRQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CTRL_ADDR(x), HWIO_PMCG1_IRQ_CTRL_RMSK)
#define HWIO_PMCG1_IRQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CTRL_ADDR(x), m)
#define HWIO_PMCG1_IRQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_PMCG1_IRQ_CTRL_ADDR(x),v)
#define HWIO_PMCG1_IRQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_IRQ_CTRL_ADDR(x),m,v,HWIO_PMCG1_IRQ_CTRL_IN(x))
#define HWIO_PMCG1_IRQ_CTRL_IRQEN_BMSK                                               0x1
#define HWIO_PMCG1_IRQ_CTRL_IRQEN_SHFT                                               0x0

#define HWIO_PMCG1_IRQ_CTRLACK_ADDR(x)                                        ((x) + 0x00001e54)
#define HWIO_PMCG1_IRQ_CTRLACK_PHYS(x)                                        ((x) + 0x00001e54)
#define HWIO_PMCG1_IRQ_CTRLACK_RMSK                                                  0x1
#define HWIO_PMCG1_IRQ_CTRLACK_POR                                            0x00000000
#define HWIO_PMCG1_IRQ_CTRLACK_POR_RMSK                                       0xffffffff
#define HWIO_PMCG1_IRQ_CTRLACK_ATTR                                                  0x1
#define HWIO_PMCG1_IRQ_CTRLACK_IN(x)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CTRLACK_ADDR(x), HWIO_PMCG1_IRQ_CTRLACK_RMSK)
#define HWIO_PMCG1_IRQ_CTRLACK_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CTRLACK_ADDR(x), m)
#define HWIO_PMCG1_IRQ_CTRLACK_IRQEN_BMSK                                            0x1
#define HWIO_PMCG1_IRQ_CTRLACK_IRQEN_SHFT                                            0x0

#define HWIO_PMCG1_IRQ_CFG0_L_ADDR(x)                                         ((x) + 0x00001e58)
#define HWIO_PMCG1_IRQ_CFG0_L_PHYS(x)                                         ((x) + 0x00001e58)
#define HWIO_PMCG1_IRQ_CFG0_L_RMSK                                            0xfffffffc
#define HWIO_PMCG1_IRQ_CFG0_L_POR                                             0x00000000
#define HWIO_PMCG1_IRQ_CFG0_L_POR_RMSK                                        0xffffffff
#define HWIO_PMCG1_IRQ_CFG0_L_ATTR                                                   0x3
#define HWIO_PMCG1_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CFG0_L_ADDR(x), HWIO_PMCG1_IRQ_CFG0_L_RMSK)
#define HWIO_PMCG1_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_PMCG1_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_PMCG1_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_PMCG1_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_IRQ_CFG0_L_ADDR(x),m,v,HWIO_PMCG1_IRQ_CFG0_L_IN(x))
#define HWIO_PMCG1_IRQ_CFG0_L_ADDR_31_2_BMSK                                  0xfffffffc
#define HWIO_PMCG1_IRQ_CFG0_L_ADDR_31_2_SHFT                                         0x2

#define HWIO_PMCG1_IRQ_CFG0_H_ADDR(x)                                         ((x) + 0x00001e5c)
#define HWIO_PMCG1_IRQ_CFG0_H_PHYS(x)                                         ((x) + 0x00001e5c)
#define HWIO_PMCG1_IRQ_CFG0_H_RMSK                                                0xffff
#define HWIO_PMCG1_IRQ_CFG0_H_POR                                             0x00000000
#define HWIO_PMCG1_IRQ_CFG0_H_POR_RMSK                                        0xffffffff
#define HWIO_PMCG1_IRQ_CFG0_H_ATTR                                                   0x3
#define HWIO_PMCG1_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CFG0_H_ADDR(x), HWIO_PMCG1_IRQ_CFG0_H_RMSK)
#define HWIO_PMCG1_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_PMCG1_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_PMCG1_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_PMCG1_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_IRQ_CFG0_H_ADDR(x),m,v,HWIO_PMCG1_IRQ_CFG0_H_IN(x))
#define HWIO_PMCG1_IRQ_CFG0_H_ADDR_47_32_BMSK                                     0xffff
#define HWIO_PMCG1_IRQ_CFG0_H_ADDR_47_32_SHFT                                        0x0

#define HWIO_PMCG1_IRQ_CFG1_ADDR(x)                                           ((x) + 0x00001e60)
#define HWIO_PMCG1_IRQ_CFG1_PHYS(x)                                           ((x) + 0x00001e60)
#define HWIO_PMCG1_IRQ_CFG1_RMSK                                              0xffffffff
#define HWIO_PMCG1_IRQ_CFG1_POR                                               0x00000000
#define HWIO_PMCG1_IRQ_CFG1_POR_RMSK                                          0xffffffff
#define HWIO_PMCG1_IRQ_CFG1_ATTR                                                     0x3
#define HWIO_PMCG1_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CFG1_ADDR(x), HWIO_PMCG1_IRQ_CFG1_RMSK)
#define HWIO_PMCG1_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CFG1_ADDR(x), m)
#define HWIO_PMCG1_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_PMCG1_IRQ_CFG1_ADDR(x),v)
#define HWIO_PMCG1_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_IRQ_CFG1_ADDR(x),m,v,HWIO_PMCG1_IRQ_CFG1_IN(x))
#define HWIO_PMCG1_IRQ_CFG1_DATA_BMSK                                         0xffffffff
#define HWIO_PMCG1_IRQ_CFG1_DATA_SHFT                                                0x0

#define HWIO_PMCG1_IRQ_CFG2_ADDR(x)                                           ((x) + 0x00001e64)
#define HWIO_PMCG1_IRQ_CFG2_PHYS(x)                                           ((x) + 0x00001e64)
#define HWIO_PMCG1_IRQ_CFG2_RMSK                                                    0x3f
#define HWIO_PMCG1_IRQ_CFG2_POR                                               0x00000000
#define HWIO_PMCG1_IRQ_CFG2_POR_RMSK                                          0xffffffff
#define HWIO_PMCG1_IRQ_CFG2_ATTR                                                     0x3
#define HWIO_PMCG1_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CFG2_ADDR(x), HWIO_PMCG1_IRQ_CFG2_RMSK)
#define HWIO_PMCG1_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_IRQ_CFG2_ADDR(x), m)
#define HWIO_PMCG1_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_PMCG1_IRQ_CFG2_ADDR(x),v)
#define HWIO_PMCG1_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG1_IRQ_CFG2_ADDR(x),m,v,HWIO_PMCG1_IRQ_CFG2_IN(x))
#define HWIO_PMCG1_IRQ_CFG2_SH_BMSK                                                 0x30
#define HWIO_PMCG1_IRQ_CFG2_SH_SHFT                                                  0x4
#define HWIO_PMCG1_IRQ_CFG2_MEMATTR_BMSK                                             0xf
#define HWIO_PMCG1_IRQ_CFG2_MEMATTR_SHFT                                             0x0

#define HWIO_PMCG1_AIDR_ADDR(x)                                               ((x) + 0x00001e70)
#define HWIO_PMCG1_AIDR_PHYS(x)                                               ((x) + 0x00001e70)
#define HWIO_PMCG1_AIDR_RMSK                                                        0xff
#define HWIO_PMCG1_AIDR_POR                                                   0x00000000
#define HWIO_PMCG1_AIDR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG1_AIDR_ATTR                                                         0x1
#define HWIO_PMCG1_AIDR_IN(x)      \
        in_dword_masked(HWIO_PMCG1_AIDR_ADDR(x), HWIO_PMCG1_AIDR_RMSK)
#define HWIO_PMCG1_AIDR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_AIDR_ADDR(x), m)
#define HWIO_PMCG1_AIDR_ARCHMAJORREC_BMSK                                           0xf0
#define HWIO_PMCG1_AIDR_ARCHMAJORREC_SHFT                                            0x4
#define HWIO_PMCG1_AIDR_ARCHMINORREV_BMSK                                            0xf
#define HWIO_PMCG1_AIDR_ARCHMINORREV_SHFT                                            0x0

#define HWIO_PMCG1_IMPDEF0_FILTERn_ADDR(base,n)                               ((base) + 0x00001ec0 + 0x8 * (n))
#define HWIO_PMCG1_IMPDEF0_FILTERn_PHYS(base,n)                               ((base) + 0x00001ec0 + 0x8 * (n))
#define HWIO_PMCG1_IMPDEF0_FILTERn_RMSK                                       0x7fffffff
#define HWIO_PMCG1_IMPDEF0_FILTERn_MAXn                                                7
#define HWIO_PMCG1_IMPDEF0_FILTERn_POR                                        0x78003f8f
#define HWIO_PMCG1_IMPDEF0_FILTERn_POR_RMSK                                   0xffffffff
#define HWIO_PMCG1_IMPDEF0_FILTERn_ATTR                                              0x3
#define HWIO_PMCG1_IMPDEF0_FILTERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG1_IMPDEF0_FILTERn_ADDR(base,n), HWIO_PMCG1_IMPDEF0_FILTERn_RMSK)
#define HWIO_PMCG1_IMPDEF0_FILTERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG1_IMPDEF0_FILTERn_ADDR(base,n), mask)
#define HWIO_PMCG1_IMPDEF0_FILTERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG1_IMPDEF0_FILTERn_ADDR(base,n),val)
#define HWIO_PMCG1_IMPDEF0_FILTERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG1_IMPDEF0_FILTERn_ADDR(base,n),mask,val,HWIO_PMCG1_IMPDEF0_FILTERn_INI(base,n))
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_TLB_S1_BMSK                          0x40000000
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_TLB_S1_SHFT                                0x1e
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_TLB_S1_NF_BMSK                       0x20000000
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_TLB_S1_NF_SHFT                             0x1d
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_TLB_S2_BMSK                          0x10000000
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_TLB_S2_SHFT                                0x1c
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_TLB_S2_NF_BMSK                        0x8000000
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_TLB_S2_NF_SHFT                             0x1b
#define HWIO_PMCG1_IMPDEF0_FILTERn_FILTER_TLB_INDEX_EN_BMSK                    0x4000000
#define HWIO_PMCG1_IMPDEF0_FILTERn_FILTER_TLB_INDEX_EN_SHFT                         0x1a
#define HWIO_PMCG1_IMPDEF0_FILTERn_TLB_INDEX_BMSK                              0x3ffc000
#define HWIO_PMCG1_IMPDEF0_FILTERn_TLB_INDEX_SHFT                                    0xe
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_S1_BMSK                              0x2000
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_S1_SHFT                                 0xd
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_S2_BMSK                              0x1000
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_S2_SHFT                                 0xc
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_CDIPA2PA_BMSK                         0x800
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_CDIPA2PA_SHFT                           0xb
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_LEV0_BMSK                             0x400
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_LEV0_SHFT                               0xa
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_LEV1_BMSK                             0x200
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_LEV1_SHFT                               0x9
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_LEV2_BMSK                             0x100
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_LEV2_SHFT                               0x8
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_LEV3_BMSK                              0x80
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_HTW_LEV3_SHFT                               0x7
#define HWIO_PMCG1_IMPDEF0_FILTERn_FILTER_ALLOC_POLICY_EN_BMSK                      0x40
#define HWIO_PMCG1_IMPDEF0_FILTERn_FILTER_ALLOC_POLICY_EN_SHFT                       0x6
#define HWIO_PMCG1_IMPDEF0_FILTERn_ALLOC_POLICY_BMSK                                0x30
#define HWIO_PMCG1_IMPDEF0_FILTERn_ALLOC_POLICY_SHFT                                 0x4
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_CFG_STE_L1_BMSK                             0x8
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_CFG_STE_L1_SHFT                             0x3
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_CFG_STE_L2_BMSK                             0x4
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_CFG_STE_L2_SHFT                             0x2
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_CFG_CD_L1_BMSK                              0x2
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_CFG_CD_L1_SHFT                              0x1
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_CFG_CD_L2_BMSK                              0x1
#define HWIO_PMCG1_IMPDEF0_FILTERn_COUNT_CFG_CD_L2_SHFT                              0x0

#define HWIO_PMCG1_IMPDEF1_FILTERn_ADDR(base,n)                               ((base) + 0x00001ec4 + 0x8 * (n))
#define HWIO_PMCG1_IMPDEF1_FILTERn_PHYS(base,n)                               ((base) + 0x00001ec4 + 0x8 * (n))
#define HWIO_PMCG1_IMPDEF1_FILTERn_RMSK                                       0xffffffff
#define HWIO_PMCG1_IMPDEF1_FILTERn_MAXn                                                7
#define HWIO_PMCG1_IMPDEF1_FILTERn_POR                                        0x0f800000
#define HWIO_PMCG1_IMPDEF1_FILTERn_POR_RMSK                                   0xffffffff
#define HWIO_PMCG1_IMPDEF1_FILTERn_ATTR                                              0x3
#define HWIO_PMCG1_IMPDEF1_FILTERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG1_IMPDEF1_FILTERn_ADDR(base,n), HWIO_PMCG1_IMPDEF1_FILTERn_RMSK)
#define HWIO_PMCG1_IMPDEF1_FILTERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG1_IMPDEF1_FILTERn_ADDR(base,n), mask)
#define HWIO_PMCG1_IMPDEF1_FILTERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG1_IMPDEF1_FILTERn_ADDR(base,n),val)
#define HWIO_PMCG1_IMPDEF1_FILTERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG1_IMPDEF1_FILTERn_ADDR(base,n),mask,val,HWIO_PMCG1_IMPDEF1_FILTERn_INI(base,n))
#define HWIO_PMCG1_IMPDEF1_FILTERn_COUNT_MID_EN_BMSK                          0x80000000
#define HWIO_PMCG1_IMPDEF1_FILTERn_COUNT_MID_EN_SHFT                                0x1f
#define HWIO_PMCG1_IMPDEF1_FILTERn_MID_HI_BMSK                                0x70000000
#define HWIO_PMCG1_IMPDEF1_FILTERn_MID_HI_SHFT                                      0x1c
#define HWIO_PMCG1_IMPDEF1_FILTERn_COUNT_TRAN_SRC_MID_LO_BMSK                  0xf800000
#define HWIO_PMCG1_IMPDEF1_FILTERn_COUNT_TRAN_SRC_MID_LO_SHFT                       0x17
#define HWIO_PMCG1_IMPDEF1_FILTERn_COUNT_SSID_VALID_EN_BMSK                     0x400000
#define HWIO_PMCG1_IMPDEF1_FILTERn_COUNT_SSID_VALID_EN_SHFT                         0x16
#define HWIO_PMCG1_IMPDEF1_FILTERn_SSID_VALID_BMSK                              0x200000
#define HWIO_PMCG1_IMPDEF1_FILTERn_SSID_VALID_SHFT                                  0x15
#define HWIO_PMCG1_IMPDEF1_FILTERn_COUNT_SSID_SPAN_EN_BMSK                      0x100000
#define HWIO_PMCG1_IMPDEF1_FILTERn_COUNT_SSID_SPAN_EN_SHFT                          0x14
#define HWIO_PMCG1_IMPDEF1_FILTERn_SSID_BMSK                                     0xfffff
#define HWIO_PMCG1_IMPDEF1_FILTERn_SSID_SHFT                                         0x0

#define HWIO_PMCG1_PIDR4_ADDR(x)                                              ((x) + 0x00001fd0)
#define HWIO_PMCG1_PIDR4_PHYS(x)                                              ((x) + 0x00001fd0)
#define HWIO_PMCG1_PIDR4_RMSK                                                       0xff
#define HWIO_PMCG1_PIDR4_POR                                                  0x00000000
#define HWIO_PMCG1_PIDR4_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_PIDR4_ATTR                                                        0x1
#define HWIO_PMCG1_PIDR4_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PIDR4_ADDR(x), HWIO_PMCG1_PIDR4_RMSK)
#define HWIO_PMCG1_PIDR4_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PIDR4_ADDR(x), m)
#define HWIO_PMCG1_PIDR4_SIZE_BMSK                                                  0xff
#define HWIO_PMCG1_PIDR4_SIZE_SHFT                                                   0x0

#define HWIO_PMCG1_PIDR5_ADDR(x)                                              ((x) + 0x00001fd4)
#define HWIO_PMCG1_PIDR5_PHYS(x)                                              ((x) + 0x00001fd4)
#define HWIO_PMCG1_PIDR5_RMSK                                                 0xffffffff
#define HWIO_PMCG1_PIDR5_POR                                                  0x00000000
#define HWIO_PMCG1_PIDR5_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_PIDR5_ATTR                                                        0x1
#define HWIO_PMCG1_PIDR5_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PIDR5_ADDR(x), HWIO_PMCG1_PIDR5_RMSK)
#define HWIO_PMCG1_PIDR5_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PIDR5_ADDR(x), m)
#define HWIO_PMCG1_PIDR5_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG1_PIDR5_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG1_PIDR6_ADDR(x)                                              ((x) + 0x00001fd8)
#define HWIO_PMCG1_PIDR6_PHYS(x)                                              ((x) + 0x00001fd8)
#define HWIO_PMCG1_PIDR6_RMSK                                                 0xffffffff
#define HWIO_PMCG1_PIDR6_POR                                                  0x00000000
#define HWIO_PMCG1_PIDR6_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_PIDR6_ATTR                                                        0x1
#define HWIO_PMCG1_PIDR6_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PIDR6_ADDR(x), HWIO_PMCG1_PIDR6_RMSK)
#define HWIO_PMCG1_PIDR6_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PIDR6_ADDR(x), m)
#define HWIO_PMCG1_PIDR6_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG1_PIDR6_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG1_PIDR7_ADDR(x)                                              ((x) + 0x00001fdc)
#define HWIO_PMCG1_PIDR7_PHYS(x)                                              ((x) + 0x00001fdc)
#define HWIO_PMCG1_PIDR7_RMSK                                                 0xffffffff
#define HWIO_PMCG1_PIDR7_POR                                                  0x00000000
#define HWIO_PMCG1_PIDR7_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_PIDR7_ATTR                                                        0x1
#define HWIO_PMCG1_PIDR7_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PIDR7_ADDR(x), HWIO_PMCG1_PIDR7_RMSK)
#define HWIO_PMCG1_PIDR7_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PIDR7_ADDR(x), m)
#define HWIO_PMCG1_PIDR7_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG1_PIDR7_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG1_PIDR0_ADDR(x)                                              ((x) + 0x00001fe0)
#define HWIO_PMCG1_PIDR0_PHYS(x)                                              ((x) + 0x00001fe0)
#define HWIO_PMCG1_PIDR0_RMSK                                                       0xff
#define HWIO_PMCG1_PIDR0_POR                                                  0x00000040
#define HWIO_PMCG1_PIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_PIDR0_ATTR                                                        0x1
#define HWIO_PMCG1_PIDR0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PIDR0_ADDR(x), HWIO_PMCG1_PIDR0_RMSK)
#define HWIO_PMCG1_PIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PIDR0_ADDR(x), m)
#define HWIO_PMCG1_PIDR0_PART_0_BMSK                                                0xff
#define HWIO_PMCG1_PIDR0_PART_0_SHFT                                                 0x0

#define HWIO_PMCG1_PIDR1_ADDR(x)                                              ((x) + 0x00001fe4)
#define HWIO_PMCG1_PIDR1_PHYS(x)                                              ((x) + 0x00001fe4)
#define HWIO_PMCG1_PIDR1_RMSK                                                      0xf0f
#define HWIO_PMCG1_PIDR1_POR                                                  0x00000000
#define HWIO_PMCG1_PIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_PIDR1_ATTR                                                        0x1
#define HWIO_PMCG1_PIDR1_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PIDR1_ADDR(x), HWIO_PMCG1_PIDR1_RMSK)
#define HWIO_PMCG1_PIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PIDR1_ADDR(x), m)
#define HWIO_PMCG1_PIDR1_PART_1_BMSK                                               0xf00
#define HWIO_PMCG1_PIDR1_PART_1_SHFT                                                 0x8
#define HWIO_PMCG1_PIDR1_DES_0_BMSK                                                  0xf
#define HWIO_PMCG1_PIDR1_DES_0_SHFT                                                  0x0

#define HWIO_PMCG1_PIDR2_ADDR(x)                                              ((x) + 0x00001fe8)
#define HWIO_PMCG1_PIDR2_PHYS(x)                                              ((x) + 0x00001fe8)
#define HWIO_PMCG1_PIDR2_RMSK                                                       0xff
#define HWIO_PMCG1_PIDR2_POR                                                  0x0000003f
#define HWIO_PMCG1_PIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_PIDR2_ATTR                                                        0x1
#define HWIO_PMCG1_PIDR2_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PIDR2_ADDR(x), HWIO_PMCG1_PIDR2_RMSK)
#define HWIO_PMCG1_PIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PIDR2_ADDR(x), m)
#define HWIO_PMCG1_PIDR2_REVISION_BMSK                                              0xf0
#define HWIO_PMCG1_PIDR2_REVISION_SHFT                                               0x4
#define HWIO_PMCG1_PIDR2_JEDEC_VAL_BMSK                                              0x8
#define HWIO_PMCG1_PIDR2_JEDEC_VAL_SHFT                                              0x3
#define HWIO_PMCG1_PIDR2_DES_1_BMSK                                                  0x7
#define HWIO_PMCG1_PIDR2_DES_1_SHFT                                                  0x0

#define HWIO_PMCG1_PIDR3_ADDR(x)                                              ((x) + 0x00001fec)
#define HWIO_PMCG1_PIDR3_PHYS(x)                                              ((x) + 0x00001fec)
#define HWIO_PMCG1_PIDR3_RMSK                                                       0xff
#define HWIO_PMCG1_PIDR3_POR                                                  0x00000000
#define HWIO_PMCG1_PIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_PIDR3_ATTR                                                        0x1
#define HWIO_PMCG1_PIDR3_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PIDR3_ADDR(x), HWIO_PMCG1_PIDR3_RMSK)
#define HWIO_PMCG1_PIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PIDR3_ADDR(x), m)
#define HWIO_PMCG1_PIDR3_REVAND_BMSK                                                0xf0
#define HWIO_PMCG1_PIDR3_REVAND_SHFT                                                 0x4
#define HWIO_PMCG1_PIDR3_CMOD_BMSK                                                   0xf
#define HWIO_PMCG1_PIDR3_CMOD_SHFT                                                   0x0

#define HWIO_PMCG1_CIDR0_ADDR(x)                                              ((x) + 0x00001ff0)
#define HWIO_PMCG1_CIDR0_PHYS(x)                                              ((x) + 0x00001ff0)
#define HWIO_PMCG1_CIDR0_RMSK                                                 0xffffffff
#define HWIO_PMCG1_CIDR0_POR                                                  0x0000000d
#define HWIO_PMCG1_CIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_CIDR0_ATTR                                                        0x1
#define HWIO_PMCG1_CIDR0_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CIDR0_ADDR(x), HWIO_PMCG1_CIDR0_RMSK)
#define HWIO_PMCG1_CIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CIDR0_ADDR(x), m)
#define HWIO_PMCG1_CIDR0_COMPONENT_IDR0_BMSK                                  0xffffffff
#define HWIO_PMCG1_CIDR0_COMPONENT_IDR0_SHFT                                         0x0

#define HWIO_PMCG1_CIDR1_ADDR(x)                                              ((x) + 0x00001ff4)
#define HWIO_PMCG1_CIDR1_PHYS(x)                                              ((x) + 0x00001ff4)
#define HWIO_PMCG1_CIDR1_RMSK                                                 0xffffffff
#define HWIO_PMCG1_CIDR1_POR                                                  0x000000f0
#define HWIO_PMCG1_CIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_CIDR1_ATTR                                                        0x1
#define HWIO_PMCG1_CIDR1_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CIDR1_ADDR(x), HWIO_PMCG1_CIDR1_RMSK)
#define HWIO_PMCG1_CIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CIDR1_ADDR(x), m)
#define HWIO_PMCG1_CIDR1_COMPONENT_IDR1_BMSK                                  0xffffffff
#define HWIO_PMCG1_CIDR1_COMPONENT_IDR1_SHFT                                         0x0

#define HWIO_PMCG1_CIDR2_ADDR(x)                                              ((x) + 0x00001ff8)
#define HWIO_PMCG1_CIDR2_PHYS(x)                                              ((x) + 0x00001ff8)
#define HWIO_PMCG1_CIDR2_RMSK                                                 0xffffffff
#define HWIO_PMCG1_CIDR2_POR                                                  0x00000005
#define HWIO_PMCG1_CIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_CIDR2_ATTR                                                        0x1
#define HWIO_PMCG1_CIDR2_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CIDR2_ADDR(x), HWIO_PMCG1_CIDR2_RMSK)
#define HWIO_PMCG1_CIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CIDR2_ADDR(x), m)
#define HWIO_PMCG1_CIDR2_COMPONENT_IDR2_BMSK                                  0xffffffff
#define HWIO_PMCG1_CIDR2_COMPONENT_IDR2_SHFT                                         0x0

#define HWIO_PMCG1_CIDR3_ADDR(x)                                              ((x) + 0x00001ffc)
#define HWIO_PMCG1_CIDR3_PHYS(x)                                              ((x) + 0x00001ffc)
#define HWIO_PMCG1_CIDR3_RMSK                                                 0xffffffff
#define HWIO_PMCG1_CIDR3_POR                                                  0x000000b1
#define HWIO_PMCG1_CIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PMCG1_CIDR3_ATTR                                                        0x1
#define HWIO_PMCG1_CIDR3_IN(x)      \
        in_dword_masked(HWIO_PMCG1_CIDR3_ADDR(x), HWIO_PMCG1_CIDR3_RMSK)
#define HWIO_PMCG1_CIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_CIDR3_ADDR(x), m)
#define HWIO_PMCG1_CIDR3_COMPONENT_IDR3_BMSK                                  0xffffffff
#define HWIO_PMCG1_CIDR3_COMPONENT_IDR3_SHFT                                         0x0

#define HWIO_PMCG1_PMAUTHSTATUS_ADDR(x)                                       ((x) + 0x00001fb8)
#define HWIO_PMCG1_PMAUTHSTATUS_PHYS(x)                                       ((x) + 0x00001fb8)
#define HWIO_PMCG1_PMAUTHSTATUS_RMSK                                                0xff
#define HWIO_PMCG1_PMAUTHSTATUS_POR                                           0x00000088
#define HWIO_PMCG1_PMAUTHSTATUS_POR_RMSK                                      0xffffffff
#define HWIO_PMCG1_PMAUTHSTATUS_ATTR                                                 0x1
#define HWIO_PMCG1_PMAUTHSTATUS_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PMAUTHSTATUS_ADDR(x), HWIO_PMCG1_PMAUTHSTATUS_RMSK)
#define HWIO_PMCG1_PMAUTHSTATUS_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PMAUTHSTATUS_ADDR(x), m)
#define HWIO_PMCG1_PMAUTHSTATUS_AUTHSTATUS_BMSK                                     0xff
#define HWIO_PMCG1_PMAUTHSTATUS_AUTHSTATUS_SHFT                                      0x0

#define HWIO_PMCG1_PMDEVARCH_ADDR(x)                                          ((x) + 0x00001fbc)
#define HWIO_PMCG1_PMDEVARCH_PHYS(x)                                          ((x) + 0x00001fbc)
#define HWIO_PMCG1_PMDEVARCH_RMSK                                             0xffffffff
#define HWIO_PMCG1_PMDEVARCH_POR                                              0x0e102a56
#define HWIO_PMCG1_PMDEVARCH_POR_RMSK                                         0xffffffff
#define HWIO_PMCG1_PMDEVARCH_ATTR                                                    0x1
#define HWIO_PMCG1_PMDEVARCH_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PMDEVARCH_ADDR(x), HWIO_PMCG1_PMDEVARCH_RMSK)
#define HWIO_PMCG1_PMDEVARCH_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PMDEVARCH_ADDR(x), m)
#define HWIO_PMCG1_PMDEVARCH_ARCHITECT_BMSK                                   0xffe00000
#define HWIO_PMCG1_PMDEVARCH_ARCHITECT_SHFT                                         0x15
#define HWIO_PMCG1_PMDEVARCH_PRESENT_BMSK                                       0x100000
#define HWIO_PMCG1_PMDEVARCH_PRESENT_SHFT                                           0x14
#define HWIO_PMCG1_PMDEVARCH_REVISION_BMSK                                       0xf0000
#define HWIO_PMCG1_PMDEVARCH_REVISION_SHFT                                          0x10
#define HWIO_PMCG1_PMDEVARCH_ARCHID_BMSK                                          0xffff
#define HWIO_PMCG1_PMDEVARCH_ARCHID_SHFT                                             0x0

#define HWIO_PMCG1_PMDEVTYPE_ADDR(x)                                          ((x) + 0x00001fcc)
#define HWIO_PMCG1_PMDEVTYPE_PHYS(x)                                          ((x) + 0x00001fcc)
#define HWIO_PMCG1_PMDEVTYPE_RMSK                                                   0xff
#define HWIO_PMCG1_PMDEVTYPE_POR                                              0x00000056
#define HWIO_PMCG1_PMDEVTYPE_POR_RMSK                                         0xffffffff
#define HWIO_PMCG1_PMDEVTYPE_ATTR                                                    0x1
#define HWIO_PMCG1_PMDEVTYPE_IN(x)      \
        in_dword_masked(HWIO_PMCG1_PMDEVTYPE_ADDR(x), HWIO_PMCG1_PMDEVTYPE_RMSK)
#define HWIO_PMCG1_PMDEVTYPE_INM(x, m)      \
        in_dword_masked(HWIO_PMCG1_PMDEVTYPE_ADDR(x), m)
#define HWIO_PMCG1_PMDEVTYPE_SUB_TYPE_BMSK                                          0xf0
#define HWIO_PMCG1_PMDEVTYPE_SUB_TYPE_SHFT                                           0x4
#define HWIO_PMCG1_PMDEVTYPE_CLASS_BMSK                                              0xf
#define HWIO_PMCG1_PMDEVTYPE_CLASS_SHFT                                              0x0

#define HWIO_PMCG2_EVCNTR_Ln_ADDR(base,n)                                     ((base) + 0x00012000 + 0x4 * (n))
#define HWIO_PMCG2_EVCNTR_Ln_PHYS(base,n)                                     ((base) + 0x00012000 + 0x4 * (n))
#define HWIO_PMCG2_EVCNTR_Ln_RMSK                                             0xffffffff
#define HWIO_PMCG2_EVCNTR_Ln_MAXn                                                      7
#define HWIO_PMCG2_EVCNTR_Ln_POR                                              0x00000000
#define HWIO_PMCG2_EVCNTR_Ln_POR_RMSK                                         0xffffffff
#define HWIO_PMCG2_EVCNTR_Ln_ATTR                                                    0x3
#define HWIO_PMCG2_EVCNTR_Ln_INI(base,n)        \
        in_dword_masked(HWIO_PMCG2_EVCNTR_Ln_ADDR(base,n), HWIO_PMCG2_EVCNTR_Ln_RMSK)
#define HWIO_PMCG2_EVCNTR_Ln_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG2_EVCNTR_Ln_ADDR(base,n), mask)
#define HWIO_PMCG2_EVCNTR_Ln_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG2_EVCNTR_Ln_ADDR(base,n),val)
#define HWIO_PMCG2_EVCNTR_Ln_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG2_EVCNTR_Ln_ADDR(base,n),mask,val,HWIO_PMCG2_EVCNTR_Ln_INI(base,n))
#define HWIO_PMCG2_EVCNTR_Ln_COUNTER_VALUE_BMSK                               0xffffffff
#define HWIO_PMCG2_EVCNTR_Ln_COUNTER_VALUE_SHFT                                      0x0

#define HWIO_PMCG2_EVTYPERn_ADDR(base,n)                                      ((base) + 0x00002400 + 0x4 * (n))
#define HWIO_PMCG2_EVTYPERn_PHYS(base,n)                                      ((base) + 0x00002400 + 0x4 * (n))
#define HWIO_PMCG2_EVTYPERn_RMSK                                              0xe000ffff
#define HWIO_PMCG2_EVTYPERn_MAXn                                                       7
#define HWIO_PMCG2_EVTYPERn_POR                                               0x0000ffff
#define HWIO_PMCG2_EVTYPERn_POR_RMSK                                          0xffffffff
#define HWIO_PMCG2_EVTYPERn_ATTR                                                     0x3
#define HWIO_PMCG2_EVTYPERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG2_EVTYPERn_ADDR(base,n), HWIO_PMCG2_EVTYPERn_RMSK)
#define HWIO_PMCG2_EVTYPERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG2_EVTYPERn_ADDR(base,n), mask)
#define HWIO_PMCG2_EVTYPERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG2_EVTYPERn_ADDR(base,n),val)
#define HWIO_PMCG2_EVTYPERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG2_EVTYPERn_ADDR(base,n),mask,val,HWIO_PMCG2_EVTYPERn_INI(base,n))
#define HWIO_PMCG2_EVTYPERn_OVFCAP_BMSK                                       0x80000000
#define HWIO_PMCG2_EVTYPERn_OVFCAP_SHFT                                             0x1f
#define HWIO_PMCG2_EVTYPERn_FILTER_SEC_SID_BMSK                               0x40000000
#define HWIO_PMCG2_EVTYPERn_FILTER_SEC_SID_SHFT                                     0x1e
#define HWIO_PMCG2_EVTYPERn_FILTER_SID_SPAN_BMSK                              0x20000000
#define HWIO_PMCG2_EVTYPERn_FILTER_SID_SPAN_SHFT                                    0x1d
#define HWIO_PMCG2_EVTYPERn_EVENT_BMSK                                            0xffff
#define HWIO_PMCG2_EVTYPERn_EVENT_SHFT                                               0x0

#define HWIO_PMCG2_SVR_Ln_ADDR(base,n)                                        ((base) + 0x00012600 + 0x4 * (n))
#define HWIO_PMCG2_SVR_Ln_PHYS(base,n)                                        ((base) + 0x00012600 + 0x4 * (n))
#define HWIO_PMCG2_SVR_Ln_RMSK                                                0xffffffff
#define HWIO_PMCG2_SVR_Ln_MAXn                                                         7
#define HWIO_PMCG2_SVR_Ln_POR                                                 0x00000000
#define HWIO_PMCG2_SVR_Ln_POR_RMSK                                            0xffffffff
#define HWIO_PMCG2_SVR_Ln_ATTR                                                       0x1
#define HWIO_PMCG2_SVR_Ln_INI(base,n)        \
        in_dword_masked(HWIO_PMCG2_SVR_Ln_ADDR(base,n), HWIO_PMCG2_SVR_Ln_RMSK)
#define HWIO_PMCG2_SVR_Ln_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG2_SVR_Ln_ADDR(base,n), mask)
#define HWIO_PMCG2_SVR_Ln_SHADOW_COUNTER_VALUE_BMSK                           0xffffffff
#define HWIO_PMCG2_SVR_Ln_SHADOW_COUNTER_VALUE_SHFT                                  0x0

#define HWIO_PMCG2_SMRn_ADDR(base,n)                                          ((base) + 0x00002a00 + 0x4 * (n))
#define HWIO_PMCG2_SMRn_PHYS(base,n)                                          ((base) + 0x00002a00 + 0x4 * (n))
#define HWIO_PMCG2_SMRn_RMSK                                                      0xffff
#define HWIO_PMCG2_SMRn_MAXn                                                           7
#define HWIO_PMCG2_SMRn_POR                                                   0x00000000
#define HWIO_PMCG2_SMRn_POR_RMSK                                              0xffffffff
#define HWIO_PMCG2_SMRn_ATTR                                                         0x3
#define HWIO_PMCG2_SMRn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG2_SMRn_ADDR(base,n), HWIO_PMCG2_SMRn_RMSK)
#define HWIO_PMCG2_SMRn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG2_SMRn_ADDR(base,n), mask)
#define HWIO_PMCG2_SMRn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG2_SMRn_ADDR(base,n),val)
#define HWIO_PMCG2_SMRn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG2_SMRn_ADDR(base,n),mask,val,HWIO_PMCG2_SMRn_INI(base,n))
#define HWIO_PMCG2_SMRn_STREAMID_BMSK                                             0xffff
#define HWIO_PMCG2_SMRn_STREAMID_SHFT                                                0x0

#define HWIO_PMCG2_CNTENSET0_ADDR(x)                                          ((x) + 0x00002c00)
#define HWIO_PMCG2_CNTENSET0_PHYS(x)                                          ((x) + 0x00002c00)
#define HWIO_PMCG2_CNTENSET0_RMSK                                                   0xff
#define HWIO_PMCG2_CNTENSET0_POR                                              0x00000000
#define HWIO_PMCG2_CNTENSET0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG2_CNTENSET0_ATTR                                                    0x3
#define HWIO_PMCG2_CNTENSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CNTENSET0_ADDR(x), HWIO_PMCG2_CNTENSET0_RMSK)
#define HWIO_PMCG2_CNTENSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CNTENSET0_ADDR(x), m)
#define HWIO_PMCG2_CNTENSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG2_CNTENSET0_ADDR(x),v)
#define HWIO_PMCG2_CNTENSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_CNTENSET0_ADDR(x),m,v,HWIO_PMCG2_CNTENSET0_IN(x))
#define HWIO_PMCG2_CNTENSET0_CNTEN_BMSK                                             0xff
#define HWIO_PMCG2_CNTENSET0_CNTEN_SHFT                                              0x0

#define HWIO_PMCG2_CNTENCLR0_ADDR(x)                                          ((x) + 0x00002c20)
#define HWIO_PMCG2_CNTENCLR0_PHYS(x)                                          ((x) + 0x00002c20)
#define HWIO_PMCG2_CNTENCLR0_RMSK                                                   0xff
#define HWIO_PMCG2_CNTENCLR0_POR                                              0x00000000
#define HWIO_PMCG2_CNTENCLR0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG2_CNTENCLR0_ATTR                                                    0x3
#define HWIO_PMCG2_CNTENCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CNTENCLR0_ADDR(x), HWIO_PMCG2_CNTENCLR0_RMSK)
#define HWIO_PMCG2_CNTENCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CNTENCLR0_ADDR(x), m)
#define HWIO_PMCG2_CNTENCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG2_CNTENCLR0_ADDR(x),v)
#define HWIO_PMCG2_CNTENCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_CNTENCLR0_ADDR(x),m,v,HWIO_PMCG2_CNTENCLR0_IN(x))
#define HWIO_PMCG2_CNTENCLR0_CNTEN_BMSK                                             0xff
#define HWIO_PMCG2_CNTENCLR0_CNTEN_SHFT                                              0x0

#define HWIO_PMCG2_INTENSET0_ADDR(x)                                          ((x) + 0x00002c40)
#define HWIO_PMCG2_INTENSET0_PHYS(x)                                          ((x) + 0x00002c40)
#define HWIO_PMCG2_INTENSET0_RMSK                                                   0xff
#define HWIO_PMCG2_INTENSET0_POR                                              0x00000000
#define HWIO_PMCG2_INTENSET0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG2_INTENSET0_ATTR                                                    0x3
#define HWIO_PMCG2_INTENSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_INTENSET0_ADDR(x), HWIO_PMCG2_INTENSET0_RMSK)
#define HWIO_PMCG2_INTENSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_INTENSET0_ADDR(x), m)
#define HWIO_PMCG2_INTENSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG2_INTENSET0_ADDR(x),v)
#define HWIO_PMCG2_INTENSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_INTENSET0_ADDR(x),m,v,HWIO_PMCG2_INTENSET0_IN(x))
#define HWIO_PMCG2_INTENSET0_INTEN_BMSK                                             0xff
#define HWIO_PMCG2_INTENSET0_INTEN_SHFT                                              0x0

#define HWIO_PMCG2_INTENCLR0_ADDR(x)                                          ((x) + 0x00002c60)
#define HWIO_PMCG2_INTENCLR0_PHYS(x)                                          ((x) + 0x00002c60)
#define HWIO_PMCG2_INTENCLR0_RMSK                                                   0xff
#define HWIO_PMCG2_INTENCLR0_POR                                              0x00000000
#define HWIO_PMCG2_INTENCLR0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG2_INTENCLR0_ATTR                                                    0x3
#define HWIO_PMCG2_INTENCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_INTENCLR0_ADDR(x), HWIO_PMCG2_INTENCLR0_RMSK)
#define HWIO_PMCG2_INTENCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_INTENCLR0_ADDR(x), m)
#define HWIO_PMCG2_INTENCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG2_INTENCLR0_ADDR(x),v)
#define HWIO_PMCG2_INTENCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_INTENCLR0_ADDR(x),m,v,HWIO_PMCG2_INTENCLR0_IN(x))
#define HWIO_PMCG2_INTENCLR0_INTEN_BMSK                                             0xff
#define HWIO_PMCG2_INTENCLR0_INTEN_SHFT                                              0x0

#define HWIO_PMCG2_OVSCLR0_ADDR(x)                                            ((x) + 0x00012c80)
#define HWIO_PMCG2_OVSCLR0_PHYS(x)                                            ((x) + 0x00012c80)
#define HWIO_PMCG2_OVSCLR0_RMSK                                                     0xff
#define HWIO_PMCG2_OVSCLR0_POR                                                0x00000000
#define HWIO_PMCG2_OVSCLR0_POR_RMSK                                           0xffffffff
#define HWIO_PMCG2_OVSCLR0_ATTR                                                      0x3
#define HWIO_PMCG2_OVSCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_OVSCLR0_ADDR(x), HWIO_PMCG2_OVSCLR0_RMSK)
#define HWIO_PMCG2_OVSCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_OVSCLR0_ADDR(x), m)
#define HWIO_PMCG2_OVSCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG2_OVSCLR0_ADDR(x),v)
#define HWIO_PMCG2_OVSCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_OVSCLR0_ADDR(x),m,v,HWIO_PMCG2_OVSCLR0_IN(x))
#define HWIO_PMCG2_OVSCLR0_OVS_BMSK                                                 0xff
#define HWIO_PMCG2_OVSCLR0_OVS_SHFT                                                  0x0

#define HWIO_PMCG2_OVSSET0_ADDR(x)                                            ((x) + 0x00012cc0)
#define HWIO_PMCG2_OVSSET0_PHYS(x)                                            ((x) + 0x00012cc0)
#define HWIO_PMCG2_OVSSET0_RMSK                                                     0xff
#define HWIO_PMCG2_OVSSET0_POR                                                0x00000000
#define HWIO_PMCG2_OVSSET0_POR_RMSK                                           0xffffffff
#define HWIO_PMCG2_OVSSET0_ATTR                                                      0x3
#define HWIO_PMCG2_OVSSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_OVSSET0_ADDR(x), HWIO_PMCG2_OVSSET0_RMSK)
#define HWIO_PMCG2_OVSSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_OVSSET0_ADDR(x), m)
#define HWIO_PMCG2_OVSSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG2_OVSSET0_ADDR(x),v)
#define HWIO_PMCG2_OVSSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_OVSSET0_ADDR(x),m,v,HWIO_PMCG2_OVSSET0_IN(x))
#define HWIO_PMCG2_OVSSET0_OVS_BMSK                                                 0xff
#define HWIO_PMCG2_OVSSET0_OVS_SHFT                                                  0x0

#define HWIO_PMCG2_CAPR_ADDR(x)                                               ((x) + 0x00012d88)
#define HWIO_PMCG2_CAPR_PHYS(x)                                               ((x) + 0x00012d88)
#define HWIO_PMCG2_CAPR_RMSK                                                         0x1
#define HWIO_PMCG2_CAPR_POR                                                   0x00000000
#define HWIO_PMCG2_CAPR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG2_CAPR_ATTR                                                         0x2
#define HWIO_PMCG2_CAPR_OUT(x, v)      \
        out_dword(HWIO_PMCG2_CAPR_ADDR(x),v)
#define HWIO_PMCG2_CAPR_CAPTURE_BMSK                                                 0x1
#define HWIO_PMCG2_CAPR_CAPTURE_SHFT                                                 0x0

#define HWIO_PMCG2_SCR_ADDR(x)                                                ((x) + 0x00002df8)
#define HWIO_PMCG2_SCR_PHYS(x)                                                ((x) + 0x00002df8)
#define HWIO_PMCG2_SCR_RMSK                                                   0x80000007
#define HWIO_PMCG2_SCR_POR                                                    0x00000002
#define HWIO_PMCG2_SCR_POR_RMSK                                               0xffffffff
#define HWIO_PMCG2_SCR_ATTR                                                          0x3
#define HWIO_PMCG2_SCR_IN(x)      \
        in_dword_masked(HWIO_PMCG2_SCR_ADDR(x), HWIO_PMCG2_SCR_RMSK)
#define HWIO_PMCG2_SCR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_SCR_ADDR(x), m)
#define HWIO_PMCG2_SCR_OUT(x, v)      \
        out_dword(HWIO_PMCG2_SCR_ADDR(x),v)
#define HWIO_PMCG2_SCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_SCR_ADDR(x),m,v,HWIO_PMCG2_SCR_IN(x))
#define HWIO_PMCG2_SCR_READ_AS_ONE_BMSK                                       0x80000000
#define HWIO_PMCG2_SCR_READ_AS_ONE_SHFT                                             0x1f
#define HWIO_PMCG2_SCR_NSMSI_BMSK                                                    0x4
#define HWIO_PMCG2_SCR_NSMSI_SHFT                                                    0x2
#define HWIO_PMCG2_SCR_NSRA_BMSK                                                     0x2
#define HWIO_PMCG2_SCR_NSRA_SHFT                                                     0x1
#define HWIO_PMCG2_SCR_SO_BMSK                                                       0x1
#define HWIO_PMCG2_SCR_SO_SHFT                                                       0x0

#define HWIO_PMCG2_CFGR_ADDR(x)                                               ((x) + 0x00002e00)
#define HWIO_PMCG2_CFGR_PHYS(x)                                               ((x) + 0x00002e00)
#define HWIO_PMCG2_CFGR_RMSK                                                    0x703f3f
#define HWIO_PMCG2_CFGR_POR                                                   0x00701f07
#define HWIO_PMCG2_CFGR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG2_CFGR_ATTR                                                         0x1
#define HWIO_PMCG2_CFGR_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CFGR_ADDR(x), HWIO_PMCG2_CFGR_RMSK)
#define HWIO_PMCG2_CFGR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CFGR_ADDR(x), m)
#define HWIO_PMCG2_CFGR_CAPTURE_BMSK                                            0x400000
#define HWIO_PMCG2_CFGR_CAPTURE_SHFT                                                0x16
#define HWIO_PMCG2_CFGR_MSI_BMSK                                                0x200000
#define HWIO_PMCG2_CFGR_MSI_SHFT                                                    0x15
#define HWIO_PMCG2_CFGR_RELOC_CTRS_BMSK                                         0x100000
#define HWIO_PMCG2_CFGR_RELOC_CTRS_SHFT                                             0x14
#define HWIO_PMCG2_CFGR_SIZE_BMSK                                                 0x3f00
#define HWIO_PMCG2_CFGR_SIZE_SHFT                                                    0x8
#define HWIO_PMCG2_CFGR_NCTR_BMSK                                                   0x3f
#define HWIO_PMCG2_CFGR_NCTR_SHFT                                                    0x0

#define HWIO_PMCG2_CR_ADDR(x)                                                 ((x) + 0x00002e04)
#define HWIO_PMCG2_CR_PHYS(x)                                                 ((x) + 0x00002e04)
#define HWIO_PMCG2_CR_RMSK                                                           0x1
#define HWIO_PMCG2_CR_POR                                                     0x00000000
#define HWIO_PMCG2_CR_POR_RMSK                                                0xffffffff
#define HWIO_PMCG2_CR_ATTR                                                           0x3
#define HWIO_PMCG2_CR_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CR_ADDR(x), HWIO_PMCG2_CR_RMSK)
#define HWIO_PMCG2_CR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CR_ADDR(x), m)
#define HWIO_PMCG2_CR_OUT(x, v)      \
        out_dword(HWIO_PMCG2_CR_ADDR(x),v)
#define HWIO_PMCG2_CR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_CR_ADDR(x),m,v,HWIO_PMCG2_CR_IN(x))
#define HWIO_PMCG2_CR_E_BMSK                                                         0x1
#define HWIO_PMCG2_CR_E_SHFT                                                         0x0

#define HWIO_PMCG2_CEID0_L_ADDR(x)                                            ((x) + 0x00002e20)
#define HWIO_PMCG2_CEID0_L_PHYS(x)                                            ((x) + 0x00002e20)
#define HWIO_PMCG2_CEID0_L_RMSK                                                     0xff
#define HWIO_PMCG2_CEID0_L_POR                                                0x000000e0
#define HWIO_PMCG2_CEID0_L_POR_RMSK                                           0xffffffff
#define HWIO_PMCG2_CEID0_L_ATTR                                                      0x1
#define HWIO_PMCG2_CEID0_L_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CEID0_L_ADDR(x), HWIO_PMCG2_CEID0_L_RMSK)
#define HWIO_PMCG2_CEID0_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CEID0_L_ADDR(x), m)
#define HWIO_PMCG2_CEID0_L_IMPL_EVENTS_BMSK                                         0xff
#define HWIO_PMCG2_CEID0_L_IMPL_EVENTS_SHFT                                          0x0

#define HWIO_PMCG2_CEID0_H_ADDR(x)                                            ((x) + 0x00002e24)
#define HWIO_PMCG2_CEID0_H_PHYS(x)                                            ((x) + 0x00002e24)
#define HWIO_PMCG2_CEID0_H_RMSK                                               0xffffffff
#define HWIO_PMCG2_CEID0_H_POR                                                0x00000000
#define HWIO_PMCG2_CEID0_H_POR_RMSK                                           0xffffffff
#define HWIO_PMCG2_CEID0_H_ATTR                                                      0x1
#define HWIO_PMCG2_CEID0_H_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CEID0_H_ADDR(x), HWIO_PMCG2_CEID0_H_RMSK)
#define HWIO_PMCG2_CEID0_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CEID0_H_ADDR(x), m)
#define HWIO_PMCG2_CEID0_H_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG2_CEID0_H_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG2_CEID1_L_ADDR(x)                                            ((x) + 0x00002e28)
#define HWIO_PMCG2_CEID1_L_PHYS(x)                                            ((x) + 0x00002e28)
#define HWIO_PMCG2_CEID1_L_RMSK                                               0xffffffff
#define HWIO_PMCG2_CEID1_L_POR                                                0x00000000
#define HWIO_PMCG2_CEID1_L_POR_RMSK                                           0xffffffff
#define HWIO_PMCG2_CEID1_L_ATTR                                                      0x1
#define HWIO_PMCG2_CEID1_L_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CEID1_L_ADDR(x), HWIO_PMCG2_CEID1_L_RMSK)
#define HWIO_PMCG2_CEID1_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CEID1_L_ADDR(x), m)
#define HWIO_PMCG2_CEID1_L_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG2_CEID1_L_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG2_CEID1_H_ADDR(x)                                            ((x) + 0x00002e2c)
#define HWIO_PMCG2_CEID1_H_PHYS(x)                                            ((x) + 0x00002e2c)
#define HWIO_PMCG2_CEID1_H_RMSK                                               0xffffffff
#define HWIO_PMCG2_CEID1_H_POR                                                0x00000000
#define HWIO_PMCG2_CEID1_H_POR_RMSK                                           0xffffffff
#define HWIO_PMCG2_CEID1_H_ATTR                                                      0x1
#define HWIO_PMCG2_CEID1_H_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CEID1_H_ADDR(x), HWIO_PMCG2_CEID1_H_RMSK)
#define HWIO_PMCG2_CEID1_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CEID1_H_ADDR(x), m)
#define HWIO_PMCG2_CEID1_H_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG2_CEID1_H_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG2_IMPL_CEID0_ADDR(x)                                         ((x) + 0x00002e30)
#define HWIO_PMCG2_IMPL_CEID0_PHYS(x)                                         ((x) + 0x00002e30)
#define HWIO_PMCG2_IMPL_CEID0_RMSK                                                  0x3f
#define HWIO_PMCG2_IMPL_CEID0_POR                                             0x0000003f
#define HWIO_PMCG2_IMPL_CEID0_POR_RMSK                                        0xffffffff
#define HWIO_PMCG2_IMPL_CEID0_ATTR                                                   0x1
#define HWIO_PMCG2_IMPL_CEID0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_IMPL_CEID0_ADDR(x), HWIO_PMCG2_IMPL_CEID0_RMSK)
#define HWIO_PMCG2_IMPL_CEID0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_IMPL_CEID0_ADDR(x), m)
#define HWIO_PMCG2_IMPL_CEID0_IMPL_EVENTS_BMSK                                      0x3f
#define HWIO_PMCG2_IMPL_CEID0_IMPL_EVENTS_SHFT                                       0x0

#define HWIO_PMCG2_IRQ_CTRL_ADDR(x)                                           ((x) + 0x00002e50)
#define HWIO_PMCG2_IRQ_CTRL_PHYS(x)                                           ((x) + 0x00002e50)
#define HWIO_PMCG2_IRQ_CTRL_RMSK                                                     0x1
#define HWIO_PMCG2_IRQ_CTRL_POR                                               0x00000000
#define HWIO_PMCG2_IRQ_CTRL_POR_RMSK                                          0xffffffff
#define HWIO_PMCG2_IRQ_CTRL_ATTR                                                     0x3
#define HWIO_PMCG2_IRQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CTRL_ADDR(x), HWIO_PMCG2_IRQ_CTRL_RMSK)
#define HWIO_PMCG2_IRQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CTRL_ADDR(x), m)
#define HWIO_PMCG2_IRQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_PMCG2_IRQ_CTRL_ADDR(x),v)
#define HWIO_PMCG2_IRQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_IRQ_CTRL_ADDR(x),m,v,HWIO_PMCG2_IRQ_CTRL_IN(x))
#define HWIO_PMCG2_IRQ_CTRL_IRQEN_BMSK                                               0x1
#define HWIO_PMCG2_IRQ_CTRL_IRQEN_SHFT                                               0x0

#define HWIO_PMCG2_IRQ_CTRLACK_ADDR(x)                                        ((x) + 0x00002e54)
#define HWIO_PMCG2_IRQ_CTRLACK_PHYS(x)                                        ((x) + 0x00002e54)
#define HWIO_PMCG2_IRQ_CTRLACK_RMSK                                                  0x1
#define HWIO_PMCG2_IRQ_CTRLACK_POR                                            0x00000000
#define HWIO_PMCG2_IRQ_CTRLACK_POR_RMSK                                       0xffffffff
#define HWIO_PMCG2_IRQ_CTRLACK_ATTR                                                  0x1
#define HWIO_PMCG2_IRQ_CTRLACK_IN(x)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CTRLACK_ADDR(x), HWIO_PMCG2_IRQ_CTRLACK_RMSK)
#define HWIO_PMCG2_IRQ_CTRLACK_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CTRLACK_ADDR(x), m)
#define HWIO_PMCG2_IRQ_CTRLACK_IRQEN_BMSK                                            0x1
#define HWIO_PMCG2_IRQ_CTRLACK_IRQEN_SHFT                                            0x0

#define HWIO_PMCG2_IRQ_CFG0_L_ADDR(x)                                         ((x) + 0x00002e58)
#define HWIO_PMCG2_IRQ_CFG0_L_PHYS(x)                                         ((x) + 0x00002e58)
#define HWIO_PMCG2_IRQ_CFG0_L_RMSK                                            0xfffffffc
#define HWIO_PMCG2_IRQ_CFG0_L_POR                                             0x00000000
#define HWIO_PMCG2_IRQ_CFG0_L_POR_RMSK                                        0xffffffff
#define HWIO_PMCG2_IRQ_CFG0_L_ATTR                                                   0x3
#define HWIO_PMCG2_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CFG0_L_ADDR(x), HWIO_PMCG2_IRQ_CFG0_L_RMSK)
#define HWIO_PMCG2_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_PMCG2_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_PMCG2_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_PMCG2_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_IRQ_CFG0_L_ADDR(x),m,v,HWIO_PMCG2_IRQ_CFG0_L_IN(x))
#define HWIO_PMCG2_IRQ_CFG0_L_ADDR_31_2_BMSK                                  0xfffffffc
#define HWIO_PMCG2_IRQ_CFG0_L_ADDR_31_2_SHFT                                         0x2

#define HWIO_PMCG2_IRQ_CFG0_H_ADDR(x)                                         ((x) + 0x00002e5c)
#define HWIO_PMCG2_IRQ_CFG0_H_PHYS(x)                                         ((x) + 0x00002e5c)
#define HWIO_PMCG2_IRQ_CFG0_H_RMSK                                                0xffff
#define HWIO_PMCG2_IRQ_CFG0_H_POR                                             0x00000000
#define HWIO_PMCG2_IRQ_CFG0_H_POR_RMSK                                        0xffffffff
#define HWIO_PMCG2_IRQ_CFG0_H_ATTR                                                   0x3
#define HWIO_PMCG2_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CFG0_H_ADDR(x), HWIO_PMCG2_IRQ_CFG0_H_RMSK)
#define HWIO_PMCG2_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_PMCG2_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_PMCG2_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_PMCG2_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_IRQ_CFG0_H_ADDR(x),m,v,HWIO_PMCG2_IRQ_CFG0_H_IN(x))
#define HWIO_PMCG2_IRQ_CFG0_H_ADDR_47_32_BMSK                                     0xffff
#define HWIO_PMCG2_IRQ_CFG0_H_ADDR_47_32_SHFT                                        0x0

#define HWIO_PMCG2_IRQ_CFG1_ADDR(x)                                           ((x) + 0x00002e60)
#define HWIO_PMCG2_IRQ_CFG1_PHYS(x)                                           ((x) + 0x00002e60)
#define HWIO_PMCG2_IRQ_CFG1_RMSK                                              0xffffffff
#define HWIO_PMCG2_IRQ_CFG1_POR                                               0x00000000
#define HWIO_PMCG2_IRQ_CFG1_POR_RMSK                                          0xffffffff
#define HWIO_PMCG2_IRQ_CFG1_ATTR                                                     0x3
#define HWIO_PMCG2_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CFG1_ADDR(x), HWIO_PMCG2_IRQ_CFG1_RMSK)
#define HWIO_PMCG2_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CFG1_ADDR(x), m)
#define HWIO_PMCG2_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_PMCG2_IRQ_CFG1_ADDR(x),v)
#define HWIO_PMCG2_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_IRQ_CFG1_ADDR(x),m,v,HWIO_PMCG2_IRQ_CFG1_IN(x))
#define HWIO_PMCG2_IRQ_CFG1_DATA_BMSK                                         0xffffffff
#define HWIO_PMCG2_IRQ_CFG1_DATA_SHFT                                                0x0

#define HWIO_PMCG2_IRQ_CFG2_ADDR(x)                                           ((x) + 0x00002e64)
#define HWIO_PMCG2_IRQ_CFG2_PHYS(x)                                           ((x) + 0x00002e64)
#define HWIO_PMCG2_IRQ_CFG2_RMSK                                                    0x3f
#define HWIO_PMCG2_IRQ_CFG2_POR                                               0x00000000
#define HWIO_PMCG2_IRQ_CFG2_POR_RMSK                                          0xffffffff
#define HWIO_PMCG2_IRQ_CFG2_ATTR                                                     0x3
#define HWIO_PMCG2_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CFG2_ADDR(x), HWIO_PMCG2_IRQ_CFG2_RMSK)
#define HWIO_PMCG2_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_IRQ_CFG2_ADDR(x), m)
#define HWIO_PMCG2_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_PMCG2_IRQ_CFG2_ADDR(x),v)
#define HWIO_PMCG2_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG2_IRQ_CFG2_ADDR(x),m,v,HWIO_PMCG2_IRQ_CFG2_IN(x))
#define HWIO_PMCG2_IRQ_CFG2_SH_BMSK                                                 0x30
#define HWIO_PMCG2_IRQ_CFG2_SH_SHFT                                                  0x4
#define HWIO_PMCG2_IRQ_CFG2_MEMATTR_BMSK                                             0xf
#define HWIO_PMCG2_IRQ_CFG2_MEMATTR_SHFT                                             0x0

#define HWIO_PMCG2_AIDR_ADDR(x)                                               ((x) + 0x00002e70)
#define HWIO_PMCG2_AIDR_PHYS(x)                                               ((x) + 0x00002e70)
#define HWIO_PMCG2_AIDR_RMSK                                                        0xff
#define HWIO_PMCG2_AIDR_POR                                                   0x00000000
#define HWIO_PMCG2_AIDR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG2_AIDR_ATTR                                                         0x1
#define HWIO_PMCG2_AIDR_IN(x)      \
        in_dword_masked(HWIO_PMCG2_AIDR_ADDR(x), HWIO_PMCG2_AIDR_RMSK)
#define HWIO_PMCG2_AIDR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_AIDR_ADDR(x), m)
#define HWIO_PMCG2_AIDR_ARCHMAJORREC_BMSK                                           0xf0
#define HWIO_PMCG2_AIDR_ARCHMAJORREC_SHFT                                            0x4
#define HWIO_PMCG2_AIDR_ARCHMINORREV_BMSK                                            0xf
#define HWIO_PMCG2_AIDR_ARCHMINORREV_SHFT                                            0x0

#define HWIO_PMCG2_IMPDEF0_FILTERn_ADDR(base,n)                               ((base) + 0x00002ec0 + 0x8 * (n))
#define HWIO_PMCG2_IMPDEF0_FILTERn_PHYS(base,n)                               ((base) + 0x00002ec0 + 0x8 * (n))
#define HWIO_PMCG2_IMPDEF0_FILTERn_RMSK                                       0x7fffffff
#define HWIO_PMCG2_IMPDEF0_FILTERn_MAXn                                                7
#define HWIO_PMCG2_IMPDEF0_FILTERn_POR                                        0x78003f8f
#define HWIO_PMCG2_IMPDEF0_FILTERn_POR_RMSK                                   0xffffffff
#define HWIO_PMCG2_IMPDEF0_FILTERn_ATTR                                              0x3
#define HWIO_PMCG2_IMPDEF0_FILTERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG2_IMPDEF0_FILTERn_ADDR(base,n), HWIO_PMCG2_IMPDEF0_FILTERn_RMSK)
#define HWIO_PMCG2_IMPDEF0_FILTERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG2_IMPDEF0_FILTERn_ADDR(base,n), mask)
#define HWIO_PMCG2_IMPDEF0_FILTERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG2_IMPDEF0_FILTERn_ADDR(base,n),val)
#define HWIO_PMCG2_IMPDEF0_FILTERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG2_IMPDEF0_FILTERn_ADDR(base,n),mask,val,HWIO_PMCG2_IMPDEF0_FILTERn_INI(base,n))
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_TLB_S1_BMSK                          0x40000000
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_TLB_S1_SHFT                                0x1e
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_TLB_S1_NF_BMSK                       0x20000000
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_TLB_S1_NF_SHFT                             0x1d
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_TLB_S2_BMSK                          0x10000000
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_TLB_S2_SHFT                                0x1c
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_TLB_S2_NF_BMSK                        0x8000000
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_TLB_S2_NF_SHFT                             0x1b
#define HWIO_PMCG2_IMPDEF0_FILTERn_FILTER_TLB_INDEX_EN_BMSK                    0x4000000
#define HWIO_PMCG2_IMPDEF0_FILTERn_FILTER_TLB_INDEX_EN_SHFT                         0x1a
#define HWIO_PMCG2_IMPDEF0_FILTERn_TLB_INDEX_BMSK                              0x3ffc000
#define HWIO_PMCG2_IMPDEF0_FILTERn_TLB_INDEX_SHFT                                    0xe
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_S1_BMSK                              0x2000
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_S1_SHFT                                 0xd
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_S2_BMSK                              0x1000
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_S2_SHFT                                 0xc
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_CDIPA2PA_BMSK                         0x800
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_CDIPA2PA_SHFT                           0xb
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_LEV0_BMSK                             0x400
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_LEV0_SHFT                               0xa
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_LEV1_BMSK                             0x200
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_LEV1_SHFT                               0x9
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_LEV2_BMSK                             0x100
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_LEV2_SHFT                               0x8
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_LEV3_BMSK                              0x80
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_HTW_LEV3_SHFT                               0x7
#define HWIO_PMCG2_IMPDEF0_FILTERn_FILTER_ALLOC_POLICY_EN_BMSK                      0x40
#define HWIO_PMCG2_IMPDEF0_FILTERn_FILTER_ALLOC_POLICY_EN_SHFT                       0x6
#define HWIO_PMCG2_IMPDEF0_FILTERn_ALLOC_POLICY_BMSK                                0x30
#define HWIO_PMCG2_IMPDEF0_FILTERn_ALLOC_POLICY_SHFT                                 0x4
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_CFG_STE_L1_BMSK                             0x8
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_CFG_STE_L1_SHFT                             0x3
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_CFG_STE_L2_BMSK                             0x4
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_CFG_STE_L2_SHFT                             0x2
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_CFG_CD_L1_BMSK                              0x2
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_CFG_CD_L1_SHFT                              0x1
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_CFG_CD_L2_BMSK                              0x1
#define HWIO_PMCG2_IMPDEF0_FILTERn_COUNT_CFG_CD_L2_SHFT                              0x0

#define HWIO_PMCG2_IMPDEF1_FILTERn_ADDR(base,n)                               ((base) + 0x00002ec4 + 0x8 * (n))
#define HWIO_PMCG2_IMPDEF1_FILTERn_PHYS(base,n)                               ((base) + 0x00002ec4 + 0x8 * (n))
#define HWIO_PMCG2_IMPDEF1_FILTERn_RMSK                                       0xffffffff
#define HWIO_PMCG2_IMPDEF1_FILTERn_MAXn                                                7
#define HWIO_PMCG2_IMPDEF1_FILTERn_POR                                        0x0f800000
#define HWIO_PMCG2_IMPDEF1_FILTERn_POR_RMSK                                   0xffffffff
#define HWIO_PMCG2_IMPDEF1_FILTERn_ATTR                                              0x3
#define HWIO_PMCG2_IMPDEF1_FILTERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG2_IMPDEF1_FILTERn_ADDR(base,n), HWIO_PMCG2_IMPDEF1_FILTERn_RMSK)
#define HWIO_PMCG2_IMPDEF1_FILTERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG2_IMPDEF1_FILTERn_ADDR(base,n), mask)
#define HWIO_PMCG2_IMPDEF1_FILTERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG2_IMPDEF1_FILTERn_ADDR(base,n),val)
#define HWIO_PMCG2_IMPDEF1_FILTERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG2_IMPDEF1_FILTERn_ADDR(base,n),mask,val,HWIO_PMCG2_IMPDEF1_FILTERn_INI(base,n))
#define HWIO_PMCG2_IMPDEF1_FILTERn_COUNT_MID_EN_BMSK                          0x80000000
#define HWIO_PMCG2_IMPDEF1_FILTERn_COUNT_MID_EN_SHFT                                0x1f
#define HWIO_PMCG2_IMPDEF1_FILTERn_MID_HI_BMSK                                0x70000000
#define HWIO_PMCG2_IMPDEF1_FILTERn_MID_HI_SHFT                                      0x1c
#define HWIO_PMCG2_IMPDEF1_FILTERn_COUNT_TRAN_SRC_MID_LO_BMSK                  0xf800000
#define HWIO_PMCG2_IMPDEF1_FILTERn_COUNT_TRAN_SRC_MID_LO_SHFT                       0x17
#define HWIO_PMCG2_IMPDEF1_FILTERn_COUNT_SSID_VALID_EN_BMSK                     0x400000
#define HWIO_PMCG2_IMPDEF1_FILTERn_COUNT_SSID_VALID_EN_SHFT                         0x16
#define HWIO_PMCG2_IMPDEF1_FILTERn_SSID_VALID_BMSK                              0x200000
#define HWIO_PMCG2_IMPDEF1_FILTERn_SSID_VALID_SHFT                                  0x15
#define HWIO_PMCG2_IMPDEF1_FILTERn_COUNT_SSID_SPAN_EN_BMSK                      0x100000
#define HWIO_PMCG2_IMPDEF1_FILTERn_COUNT_SSID_SPAN_EN_SHFT                          0x14
#define HWIO_PMCG2_IMPDEF1_FILTERn_SSID_BMSK                                     0xfffff
#define HWIO_PMCG2_IMPDEF1_FILTERn_SSID_SHFT                                         0x0

#define HWIO_PMCG2_PIDR4_ADDR(x)                                              ((x) + 0x00002fd0)
#define HWIO_PMCG2_PIDR4_PHYS(x)                                              ((x) + 0x00002fd0)
#define HWIO_PMCG2_PIDR4_RMSK                                                       0xff
#define HWIO_PMCG2_PIDR4_POR                                                  0x00000000
#define HWIO_PMCG2_PIDR4_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_PIDR4_ATTR                                                        0x1
#define HWIO_PMCG2_PIDR4_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PIDR4_ADDR(x), HWIO_PMCG2_PIDR4_RMSK)
#define HWIO_PMCG2_PIDR4_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PIDR4_ADDR(x), m)
#define HWIO_PMCG2_PIDR4_SIZE_BMSK                                                  0xff
#define HWIO_PMCG2_PIDR4_SIZE_SHFT                                                   0x0

#define HWIO_PMCG2_PIDR5_ADDR(x)                                              ((x) + 0x00002fd4)
#define HWIO_PMCG2_PIDR5_PHYS(x)                                              ((x) + 0x00002fd4)
#define HWIO_PMCG2_PIDR5_RMSK                                                 0xffffffff
#define HWIO_PMCG2_PIDR5_POR                                                  0x00000000
#define HWIO_PMCG2_PIDR5_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_PIDR5_ATTR                                                        0x1
#define HWIO_PMCG2_PIDR5_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PIDR5_ADDR(x), HWIO_PMCG2_PIDR5_RMSK)
#define HWIO_PMCG2_PIDR5_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PIDR5_ADDR(x), m)
#define HWIO_PMCG2_PIDR5_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG2_PIDR5_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG2_PIDR6_ADDR(x)                                              ((x) + 0x00002fd8)
#define HWIO_PMCG2_PIDR6_PHYS(x)                                              ((x) + 0x00002fd8)
#define HWIO_PMCG2_PIDR6_RMSK                                                 0xffffffff
#define HWIO_PMCG2_PIDR6_POR                                                  0x00000000
#define HWIO_PMCG2_PIDR6_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_PIDR6_ATTR                                                        0x1
#define HWIO_PMCG2_PIDR6_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PIDR6_ADDR(x), HWIO_PMCG2_PIDR6_RMSK)
#define HWIO_PMCG2_PIDR6_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PIDR6_ADDR(x), m)
#define HWIO_PMCG2_PIDR6_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG2_PIDR6_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG2_PIDR7_ADDR(x)                                              ((x) + 0x00002fdc)
#define HWIO_PMCG2_PIDR7_PHYS(x)                                              ((x) + 0x00002fdc)
#define HWIO_PMCG2_PIDR7_RMSK                                                 0xffffffff
#define HWIO_PMCG2_PIDR7_POR                                                  0x00000000
#define HWIO_PMCG2_PIDR7_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_PIDR7_ATTR                                                        0x1
#define HWIO_PMCG2_PIDR7_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PIDR7_ADDR(x), HWIO_PMCG2_PIDR7_RMSK)
#define HWIO_PMCG2_PIDR7_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PIDR7_ADDR(x), m)
#define HWIO_PMCG2_PIDR7_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG2_PIDR7_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG2_PIDR0_ADDR(x)                                              ((x) + 0x00002fe0)
#define HWIO_PMCG2_PIDR0_PHYS(x)                                              ((x) + 0x00002fe0)
#define HWIO_PMCG2_PIDR0_RMSK                                                       0xff
#define HWIO_PMCG2_PIDR0_POR                                                  0x00000040
#define HWIO_PMCG2_PIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_PIDR0_ATTR                                                        0x1
#define HWIO_PMCG2_PIDR0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PIDR0_ADDR(x), HWIO_PMCG2_PIDR0_RMSK)
#define HWIO_PMCG2_PIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PIDR0_ADDR(x), m)
#define HWIO_PMCG2_PIDR0_PART_0_BMSK                                                0xff
#define HWIO_PMCG2_PIDR0_PART_0_SHFT                                                 0x0

#define HWIO_PMCG2_PIDR1_ADDR(x)                                              ((x) + 0x00002fe4)
#define HWIO_PMCG2_PIDR1_PHYS(x)                                              ((x) + 0x00002fe4)
#define HWIO_PMCG2_PIDR1_RMSK                                                      0xf0f
#define HWIO_PMCG2_PIDR1_POR                                                  0x00000000
#define HWIO_PMCG2_PIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_PIDR1_ATTR                                                        0x1
#define HWIO_PMCG2_PIDR1_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PIDR1_ADDR(x), HWIO_PMCG2_PIDR1_RMSK)
#define HWIO_PMCG2_PIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PIDR1_ADDR(x), m)
#define HWIO_PMCG2_PIDR1_PART_1_BMSK                                               0xf00
#define HWIO_PMCG2_PIDR1_PART_1_SHFT                                                 0x8
#define HWIO_PMCG2_PIDR1_DES_0_BMSK                                                  0xf
#define HWIO_PMCG2_PIDR1_DES_0_SHFT                                                  0x0

#define HWIO_PMCG2_PIDR2_ADDR(x)                                              ((x) + 0x00002fe8)
#define HWIO_PMCG2_PIDR2_PHYS(x)                                              ((x) + 0x00002fe8)
#define HWIO_PMCG2_PIDR2_RMSK                                                       0xff
#define HWIO_PMCG2_PIDR2_POR                                                  0x0000003f
#define HWIO_PMCG2_PIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_PIDR2_ATTR                                                        0x1
#define HWIO_PMCG2_PIDR2_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PIDR2_ADDR(x), HWIO_PMCG2_PIDR2_RMSK)
#define HWIO_PMCG2_PIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PIDR2_ADDR(x), m)
#define HWIO_PMCG2_PIDR2_REVISION_BMSK                                              0xf0
#define HWIO_PMCG2_PIDR2_REVISION_SHFT                                               0x4
#define HWIO_PMCG2_PIDR2_JEDEC_VAL_BMSK                                              0x8
#define HWIO_PMCG2_PIDR2_JEDEC_VAL_SHFT                                              0x3
#define HWIO_PMCG2_PIDR2_DES_1_BMSK                                                  0x7
#define HWIO_PMCG2_PIDR2_DES_1_SHFT                                                  0x0

#define HWIO_PMCG2_PIDR3_ADDR(x)                                              ((x) + 0x00002fec)
#define HWIO_PMCG2_PIDR3_PHYS(x)                                              ((x) + 0x00002fec)
#define HWIO_PMCG2_PIDR3_RMSK                                                       0xff
#define HWIO_PMCG2_PIDR3_POR                                                  0x00000000
#define HWIO_PMCG2_PIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_PIDR3_ATTR                                                        0x1
#define HWIO_PMCG2_PIDR3_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PIDR3_ADDR(x), HWIO_PMCG2_PIDR3_RMSK)
#define HWIO_PMCG2_PIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PIDR3_ADDR(x), m)
#define HWIO_PMCG2_PIDR3_REVAND_BMSK                                                0xf0
#define HWIO_PMCG2_PIDR3_REVAND_SHFT                                                 0x4
#define HWIO_PMCG2_PIDR3_CMOD_BMSK                                                   0xf
#define HWIO_PMCG2_PIDR3_CMOD_SHFT                                                   0x0

#define HWIO_PMCG2_CIDR0_ADDR(x)                                              ((x) + 0x00002ff0)
#define HWIO_PMCG2_CIDR0_PHYS(x)                                              ((x) + 0x00002ff0)
#define HWIO_PMCG2_CIDR0_RMSK                                                 0xffffffff
#define HWIO_PMCG2_CIDR0_POR                                                  0x0000000d
#define HWIO_PMCG2_CIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_CIDR0_ATTR                                                        0x1
#define HWIO_PMCG2_CIDR0_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CIDR0_ADDR(x), HWIO_PMCG2_CIDR0_RMSK)
#define HWIO_PMCG2_CIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CIDR0_ADDR(x), m)
#define HWIO_PMCG2_CIDR0_COMPONENT_IDR0_BMSK                                  0xffffffff
#define HWIO_PMCG2_CIDR0_COMPONENT_IDR0_SHFT                                         0x0

#define HWIO_PMCG2_CIDR1_ADDR(x)                                              ((x) + 0x00002ff4)
#define HWIO_PMCG2_CIDR1_PHYS(x)                                              ((x) + 0x00002ff4)
#define HWIO_PMCG2_CIDR1_RMSK                                                 0xffffffff
#define HWIO_PMCG2_CIDR1_POR                                                  0x000000f0
#define HWIO_PMCG2_CIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_CIDR1_ATTR                                                        0x1
#define HWIO_PMCG2_CIDR1_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CIDR1_ADDR(x), HWIO_PMCG2_CIDR1_RMSK)
#define HWIO_PMCG2_CIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CIDR1_ADDR(x), m)
#define HWIO_PMCG2_CIDR1_COMPONENT_IDR1_BMSK                                  0xffffffff
#define HWIO_PMCG2_CIDR1_COMPONENT_IDR1_SHFT                                         0x0

#define HWIO_PMCG2_CIDR2_ADDR(x)                                              ((x) + 0x00002ff8)
#define HWIO_PMCG2_CIDR2_PHYS(x)                                              ((x) + 0x00002ff8)
#define HWIO_PMCG2_CIDR2_RMSK                                                 0xffffffff
#define HWIO_PMCG2_CIDR2_POR                                                  0x00000005
#define HWIO_PMCG2_CIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_CIDR2_ATTR                                                        0x1
#define HWIO_PMCG2_CIDR2_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CIDR2_ADDR(x), HWIO_PMCG2_CIDR2_RMSK)
#define HWIO_PMCG2_CIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CIDR2_ADDR(x), m)
#define HWIO_PMCG2_CIDR2_COMPONENT_IDR2_BMSK                                  0xffffffff
#define HWIO_PMCG2_CIDR2_COMPONENT_IDR2_SHFT                                         0x0

#define HWIO_PMCG2_CIDR3_ADDR(x)                                              ((x) + 0x00002ffc)
#define HWIO_PMCG2_CIDR3_PHYS(x)                                              ((x) + 0x00002ffc)
#define HWIO_PMCG2_CIDR3_RMSK                                                 0xffffffff
#define HWIO_PMCG2_CIDR3_POR                                                  0x000000b1
#define HWIO_PMCG2_CIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PMCG2_CIDR3_ATTR                                                        0x1
#define HWIO_PMCG2_CIDR3_IN(x)      \
        in_dword_masked(HWIO_PMCG2_CIDR3_ADDR(x), HWIO_PMCG2_CIDR3_RMSK)
#define HWIO_PMCG2_CIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_CIDR3_ADDR(x), m)
#define HWIO_PMCG2_CIDR3_COMPONENT_IDR3_BMSK                                  0xffffffff
#define HWIO_PMCG2_CIDR3_COMPONENT_IDR3_SHFT                                         0x0

#define HWIO_PMCG2_PMAUTHSTATUS_ADDR(x)                                       ((x) + 0x00002fb8)
#define HWIO_PMCG2_PMAUTHSTATUS_PHYS(x)                                       ((x) + 0x00002fb8)
#define HWIO_PMCG2_PMAUTHSTATUS_RMSK                                                0xff
#define HWIO_PMCG2_PMAUTHSTATUS_POR                                           0x00000088
#define HWIO_PMCG2_PMAUTHSTATUS_POR_RMSK                                      0xffffffff
#define HWIO_PMCG2_PMAUTHSTATUS_ATTR                                                 0x1
#define HWIO_PMCG2_PMAUTHSTATUS_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PMAUTHSTATUS_ADDR(x), HWIO_PMCG2_PMAUTHSTATUS_RMSK)
#define HWIO_PMCG2_PMAUTHSTATUS_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PMAUTHSTATUS_ADDR(x), m)
#define HWIO_PMCG2_PMAUTHSTATUS_AUTHSTATUS_BMSK                                     0xff
#define HWIO_PMCG2_PMAUTHSTATUS_AUTHSTATUS_SHFT                                      0x0

#define HWIO_PMCG2_PMDEVARCH_ADDR(x)                                          ((x) + 0x00002fbc)
#define HWIO_PMCG2_PMDEVARCH_PHYS(x)                                          ((x) + 0x00002fbc)
#define HWIO_PMCG2_PMDEVARCH_RMSK                                             0xffffffff
#define HWIO_PMCG2_PMDEVARCH_POR                                              0x0e102a56
#define HWIO_PMCG2_PMDEVARCH_POR_RMSK                                         0xffffffff
#define HWIO_PMCG2_PMDEVARCH_ATTR                                                    0x1
#define HWIO_PMCG2_PMDEVARCH_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PMDEVARCH_ADDR(x), HWIO_PMCG2_PMDEVARCH_RMSK)
#define HWIO_PMCG2_PMDEVARCH_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PMDEVARCH_ADDR(x), m)
#define HWIO_PMCG2_PMDEVARCH_ARCHITECT_BMSK                                   0xffe00000
#define HWIO_PMCG2_PMDEVARCH_ARCHITECT_SHFT                                         0x15
#define HWIO_PMCG2_PMDEVARCH_PRESENT_BMSK                                       0x100000
#define HWIO_PMCG2_PMDEVARCH_PRESENT_SHFT                                           0x14
#define HWIO_PMCG2_PMDEVARCH_REVISION_BMSK                                       0xf0000
#define HWIO_PMCG2_PMDEVARCH_REVISION_SHFT                                          0x10
#define HWIO_PMCG2_PMDEVARCH_ARCHID_BMSK                                          0xffff
#define HWIO_PMCG2_PMDEVARCH_ARCHID_SHFT                                             0x0

#define HWIO_PMCG2_PMDEVTYPE_ADDR(x)                                          ((x) + 0x00002fcc)
#define HWIO_PMCG2_PMDEVTYPE_PHYS(x)                                          ((x) + 0x00002fcc)
#define HWIO_PMCG2_PMDEVTYPE_RMSK                                                   0xff
#define HWIO_PMCG2_PMDEVTYPE_POR                                              0x00000056
#define HWIO_PMCG2_PMDEVTYPE_POR_RMSK                                         0xffffffff
#define HWIO_PMCG2_PMDEVTYPE_ATTR                                                    0x1
#define HWIO_PMCG2_PMDEVTYPE_IN(x)      \
        in_dword_masked(HWIO_PMCG2_PMDEVTYPE_ADDR(x), HWIO_PMCG2_PMDEVTYPE_RMSK)
#define HWIO_PMCG2_PMDEVTYPE_INM(x, m)      \
        in_dword_masked(HWIO_PMCG2_PMDEVTYPE_ADDR(x), m)
#define HWIO_PMCG2_PMDEVTYPE_SUB_TYPE_BMSK                                          0xf0
#define HWIO_PMCG2_PMDEVTYPE_SUB_TYPE_SHFT                                           0x4
#define HWIO_PMCG2_PMDEVTYPE_CLASS_BMSK                                              0xf
#define HWIO_PMCG2_PMDEVTYPE_CLASS_SHFT                                              0x0

#define HWIO_PMCG3_EVCNTR_Ln_ADDR(base,n)                                     ((base) + 0x00013000 + 0x4 * (n))
#define HWIO_PMCG3_EVCNTR_Ln_PHYS(base,n)                                     ((base) + 0x00013000 + 0x4 * (n))
#define HWIO_PMCG3_EVCNTR_Ln_RMSK                                             0xffffffff
#define HWIO_PMCG3_EVCNTR_Ln_MAXn                                                      7
#define HWIO_PMCG3_EVCNTR_Ln_POR                                              0x00000000
#define HWIO_PMCG3_EVCNTR_Ln_POR_RMSK                                         0xffffffff
#define HWIO_PMCG3_EVCNTR_Ln_ATTR                                                    0x3
#define HWIO_PMCG3_EVCNTR_Ln_INI(base,n)        \
        in_dword_masked(HWIO_PMCG3_EVCNTR_Ln_ADDR(base,n), HWIO_PMCG3_EVCNTR_Ln_RMSK)
#define HWIO_PMCG3_EVCNTR_Ln_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG3_EVCNTR_Ln_ADDR(base,n), mask)
#define HWIO_PMCG3_EVCNTR_Ln_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG3_EVCNTR_Ln_ADDR(base,n),val)
#define HWIO_PMCG3_EVCNTR_Ln_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG3_EVCNTR_Ln_ADDR(base,n),mask,val,HWIO_PMCG3_EVCNTR_Ln_INI(base,n))
#define HWIO_PMCG3_EVCNTR_Ln_COUNTER_VALUE_BMSK                               0xffffffff
#define HWIO_PMCG3_EVCNTR_Ln_COUNTER_VALUE_SHFT                                      0x0

#define HWIO_PMCG3_EVTYPERn_ADDR(base,n)                                      ((base) + 0x00003400 + 0x4 * (n))
#define HWIO_PMCG3_EVTYPERn_PHYS(base,n)                                      ((base) + 0x00003400 + 0x4 * (n))
#define HWIO_PMCG3_EVTYPERn_RMSK                                              0xe000ffff
#define HWIO_PMCG3_EVTYPERn_MAXn                                                       7
#define HWIO_PMCG3_EVTYPERn_POR                                               0x0000ffff
#define HWIO_PMCG3_EVTYPERn_POR_RMSK                                          0xffffffff
#define HWIO_PMCG3_EVTYPERn_ATTR                                                     0x3
#define HWIO_PMCG3_EVTYPERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG3_EVTYPERn_ADDR(base,n), HWIO_PMCG3_EVTYPERn_RMSK)
#define HWIO_PMCG3_EVTYPERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG3_EVTYPERn_ADDR(base,n), mask)
#define HWIO_PMCG3_EVTYPERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG3_EVTYPERn_ADDR(base,n),val)
#define HWIO_PMCG3_EVTYPERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG3_EVTYPERn_ADDR(base,n),mask,val,HWIO_PMCG3_EVTYPERn_INI(base,n))
#define HWIO_PMCG3_EVTYPERn_OVFCAP_BMSK                                       0x80000000
#define HWIO_PMCG3_EVTYPERn_OVFCAP_SHFT                                             0x1f
#define HWIO_PMCG3_EVTYPERn_FILTER_SEC_SID_BMSK                               0x40000000
#define HWIO_PMCG3_EVTYPERn_FILTER_SEC_SID_SHFT                                     0x1e
#define HWIO_PMCG3_EVTYPERn_FILTER_SID_SPAN_BMSK                              0x20000000
#define HWIO_PMCG3_EVTYPERn_FILTER_SID_SPAN_SHFT                                    0x1d
#define HWIO_PMCG3_EVTYPERn_EVENT_BMSK                                            0xffff
#define HWIO_PMCG3_EVTYPERn_EVENT_SHFT                                               0x0

#define HWIO_PMCG3_SVR_Ln_ADDR(base,n)                                        ((base) + 0x00013600 + 0x4 * (n))
#define HWIO_PMCG3_SVR_Ln_PHYS(base,n)                                        ((base) + 0x00013600 + 0x4 * (n))
#define HWIO_PMCG3_SVR_Ln_RMSK                                                0xffffffff
#define HWIO_PMCG3_SVR_Ln_MAXn                                                         7
#define HWIO_PMCG3_SVR_Ln_POR                                                 0x00000000
#define HWIO_PMCG3_SVR_Ln_POR_RMSK                                            0xffffffff
#define HWIO_PMCG3_SVR_Ln_ATTR                                                       0x1
#define HWIO_PMCG3_SVR_Ln_INI(base,n)        \
        in_dword_masked(HWIO_PMCG3_SVR_Ln_ADDR(base,n), HWIO_PMCG3_SVR_Ln_RMSK)
#define HWIO_PMCG3_SVR_Ln_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG3_SVR_Ln_ADDR(base,n), mask)
#define HWIO_PMCG3_SVR_Ln_SHADOW_COUNTER_VALUE_BMSK                           0xffffffff
#define HWIO_PMCG3_SVR_Ln_SHADOW_COUNTER_VALUE_SHFT                                  0x0

#define HWIO_PMCG3_SMRn_ADDR(base,n)                                          ((base) + 0x00003a00 + 0x4 * (n))
#define HWIO_PMCG3_SMRn_PHYS(base,n)                                          ((base) + 0x00003a00 + 0x4 * (n))
#define HWIO_PMCG3_SMRn_RMSK                                                      0xffff
#define HWIO_PMCG3_SMRn_MAXn                                                           7
#define HWIO_PMCG3_SMRn_POR                                                   0x00000000
#define HWIO_PMCG3_SMRn_POR_RMSK                                              0xffffffff
#define HWIO_PMCG3_SMRn_ATTR                                                         0x3
#define HWIO_PMCG3_SMRn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG3_SMRn_ADDR(base,n), HWIO_PMCG3_SMRn_RMSK)
#define HWIO_PMCG3_SMRn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG3_SMRn_ADDR(base,n), mask)
#define HWIO_PMCG3_SMRn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG3_SMRn_ADDR(base,n),val)
#define HWIO_PMCG3_SMRn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG3_SMRn_ADDR(base,n),mask,val,HWIO_PMCG3_SMRn_INI(base,n))
#define HWIO_PMCG3_SMRn_STREAMID_BMSK                                             0xffff
#define HWIO_PMCG3_SMRn_STREAMID_SHFT                                                0x0

#define HWIO_PMCG3_CNTENSET0_ADDR(x)                                          ((x) + 0x00003c00)
#define HWIO_PMCG3_CNTENSET0_PHYS(x)                                          ((x) + 0x00003c00)
#define HWIO_PMCG3_CNTENSET0_RMSK                                                   0xff
#define HWIO_PMCG3_CNTENSET0_POR                                              0x00000000
#define HWIO_PMCG3_CNTENSET0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG3_CNTENSET0_ATTR                                                    0x3
#define HWIO_PMCG3_CNTENSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CNTENSET0_ADDR(x), HWIO_PMCG3_CNTENSET0_RMSK)
#define HWIO_PMCG3_CNTENSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CNTENSET0_ADDR(x), m)
#define HWIO_PMCG3_CNTENSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG3_CNTENSET0_ADDR(x),v)
#define HWIO_PMCG3_CNTENSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_CNTENSET0_ADDR(x),m,v,HWIO_PMCG3_CNTENSET0_IN(x))
#define HWIO_PMCG3_CNTENSET0_CNTEN_BMSK                                             0xff
#define HWIO_PMCG3_CNTENSET0_CNTEN_SHFT                                              0x0

#define HWIO_PMCG3_CNTENCLR0_ADDR(x)                                          ((x) + 0x00003c20)
#define HWIO_PMCG3_CNTENCLR0_PHYS(x)                                          ((x) + 0x00003c20)
#define HWIO_PMCG3_CNTENCLR0_RMSK                                                   0xff
#define HWIO_PMCG3_CNTENCLR0_POR                                              0x00000000
#define HWIO_PMCG3_CNTENCLR0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG3_CNTENCLR0_ATTR                                                    0x3
#define HWIO_PMCG3_CNTENCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CNTENCLR0_ADDR(x), HWIO_PMCG3_CNTENCLR0_RMSK)
#define HWIO_PMCG3_CNTENCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CNTENCLR0_ADDR(x), m)
#define HWIO_PMCG3_CNTENCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG3_CNTENCLR0_ADDR(x),v)
#define HWIO_PMCG3_CNTENCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_CNTENCLR0_ADDR(x),m,v,HWIO_PMCG3_CNTENCLR0_IN(x))
#define HWIO_PMCG3_CNTENCLR0_CNTEN_BMSK                                             0xff
#define HWIO_PMCG3_CNTENCLR0_CNTEN_SHFT                                              0x0

#define HWIO_PMCG3_INTENSET0_ADDR(x)                                          ((x) + 0x00003c40)
#define HWIO_PMCG3_INTENSET0_PHYS(x)                                          ((x) + 0x00003c40)
#define HWIO_PMCG3_INTENSET0_RMSK                                                   0xff
#define HWIO_PMCG3_INTENSET0_POR                                              0x00000000
#define HWIO_PMCG3_INTENSET0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG3_INTENSET0_ATTR                                                    0x3
#define HWIO_PMCG3_INTENSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_INTENSET0_ADDR(x), HWIO_PMCG3_INTENSET0_RMSK)
#define HWIO_PMCG3_INTENSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_INTENSET0_ADDR(x), m)
#define HWIO_PMCG3_INTENSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG3_INTENSET0_ADDR(x),v)
#define HWIO_PMCG3_INTENSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_INTENSET0_ADDR(x),m,v,HWIO_PMCG3_INTENSET0_IN(x))
#define HWIO_PMCG3_INTENSET0_INTEN_BMSK                                             0xff
#define HWIO_PMCG3_INTENSET0_INTEN_SHFT                                              0x0

#define HWIO_PMCG3_INTENCLR0_ADDR(x)                                          ((x) + 0x00003c60)
#define HWIO_PMCG3_INTENCLR0_PHYS(x)                                          ((x) + 0x00003c60)
#define HWIO_PMCG3_INTENCLR0_RMSK                                                   0xff
#define HWIO_PMCG3_INTENCLR0_POR                                              0x00000000
#define HWIO_PMCG3_INTENCLR0_POR_RMSK                                         0xffffffff
#define HWIO_PMCG3_INTENCLR0_ATTR                                                    0x3
#define HWIO_PMCG3_INTENCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_INTENCLR0_ADDR(x), HWIO_PMCG3_INTENCLR0_RMSK)
#define HWIO_PMCG3_INTENCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_INTENCLR0_ADDR(x), m)
#define HWIO_PMCG3_INTENCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG3_INTENCLR0_ADDR(x),v)
#define HWIO_PMCG3_INTENCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_INTENCLR0_ADDR(x),m,v,HWIO_PMCG3_INTENCLR0_IN(x))
#define HWIO_PMCG3_INTENCLR0_INTEN_BMSK                                             0xff
#define HWIO_PMCG3_INTENCLR0_INTEN_SHFT                                              0x0

#define HWIO_PMCG3_OVSCLR0_ADDR(x)                                            ((x) + 0x00013c80)
#define HWIO_PMCG3_OVSCLR0_PHYS(x)                                            ((x) + 0x00013c80)
#define HWIO_PMCG3_OVSCLR0_RMSK                                                     0xff
#define HWIO_PMCG3_OVSCLR0_POR                                                0x00000000
#define HWIO_PMCG3_OVSCLR0_POR_RMSK                                           0xffffffff
#define HWIO_PMCG3_OVSCLR0_ATTR                                                      0x3
#define HWIO_PMCG3_OVSCLR0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_OVSCLR0_ADDR(x), HWIO_PMCG3_OVSCLR0_RMSK)
#define HWIO_PMCG3_OVSCLR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_OVSCLR0_ADDR(x), m)
#define HWIO_PMCG3_OVSCLR0_OUT(x, v)      \
        out_dword(HWIO_PMCG3_OVSCLR0_ADDR(x),v)
#define HWIO_PMCG3_OVSCLR0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_OVSCLR0_ADDR(x),m,v,HWIO_PMCG3_OVSCLR0_IN(x))
#define HWIO_PMCG3_OVSCLR0_OVS_BMSK                                                 0xff
#define HWIO_PMCG3_OVSCLR0_OVS_SHFT                                                  0x0

#define HWIO_PMCG3_OVSSET0_ADDR(x)                                            ((x) + 0x00013cc0)
#define HWIO_PMCG3_OVSSET0_PHYS(x)                                            ((x) + 0x00013cc0)
#define HWIO_PMCG3_OVSSET0_RMSK                                                     0xff
#define HWIO_PMCG3_OVSSET0_POR                                                0x00000000
#define HWIO_PMCG3_OVSSET0_POR_RMSK                                           0xffffffff
#define HWIO_PMCG3_OVSSET0_ATTR                                                      0x3
#define HWIO_PMCG3_OVSSET0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_OVSSET0_ADDR(x), HWIO_PMCG3_OVSSET0_RMSK)
#define HWIO_PMCG3_OVSSET0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_OVSSET0_ADDR(x), m)
#define HWIO_PMCG3_OVSSET0_OUT(x, v)      \
        out_dword(HWIO_PMCG3_OVSSET0_ADDR(x),v)
#define HWIO_PMCG3_OVSSET0_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_OVSSET0_ADDR(x),m,v,HWIO_PMCG3_OVSSET0_IN(x))
#define HWIO_PMCG3_OVSSET0_OVS_BMSK                                                 0xff
#define HWIO_PMCG3_OVSSET0_OVS_SHFT                                                  0x0

#define HWIO_PMCG3_CAPR_ADDR(x)                                               ((x) + 0x00013d88)
#define HWIO_PMCG3_CAPR_PHYS(x)                                               ((x) + 0x00013d88)
#define HWIO_PMCG3_CAPR_RMSK                                                         0x1
#define HWIO_PMCG3_CAPR_POR                                                   0x00000000
#define HWIO_PMCG3_CAPR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG3_CAPR_ATTR                                                         0x2
#define HWIO_PMCG3_CAPR_OUT(x, v)      \
        out_dword(HWIO_PMCG3_CAPR_ADDR(x),v)
#define HWIO_PMCG3_CAPR_CAPTURE_BMSK                                                 0x1
#define HWIO_PMCG3_CAPR_CAPTURE_SHFT                                                 0x0

#define HWIO_PMCG3_SCR_ADDR(x)                                                ((x) + 0x00003df8)
#define HWIO_PMCG3_SCR_PHYS(x)                                                ((x) + 0x00003df8)
#define HWIO_PMCG3_SCR_RMSK                                                   0x80000007
#define HWIO_PMCG3_SCR_POR                                                    0x00000002
#define HWIO_PMCG3_SCR_POR_RMSK                                               0xffffffff
#define HWIO_PMCG3_SCR_ATTR                                                          0x3
#define HWIO_PMCG3_SCR_IN(x)      \
        in_dword_masked(HWIO_PMCG3_SCR_ADDR(x), HWIO_PMCG3_SCR_RMSK)
#define HWIO_PMCG3_SCR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_SCR_ADDR(x), m)
#define HWIO_PMCG3_SCR_OUT(x, v)      \
        out_dword(HWIO_PMCG3_SCR_ADDR(x),v)
#define HWIO_PMCG3_SCR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_SCR_ADDR(x),m,v,HWIO_PMCG3_SCR_IN(x))
#define HWIO_PMCG3_SCR_READ_AS_ONE_BMSK                                       0x80000000
#define HWIO_PMCG3_SCR_READ_AS_ONE_SHFT                                             0x1f
#define HWIO_PMCG3_SCR_NSMSI_BMSK                                                    0x4
#define HWIO_PMCG3_SCR_NSMSI_SHFT                                                    0x2
#define HWIO_PMCG3_SCR_NSRA_BMSK                                                     0x2
#define HWIO_PMCG3_SCR_NSRA_SHFT                                                     0x1
#define HWIO_PMCG3_SCR_SO_BMSK                                                       0x1
#define HWIO_PMCG3_SCR_SO_SHFT                                                       0x0

#define HWIO_PMCG3_CFGR_ADDR(x)                                               ((x) + 0x00003e00)
#define HWIO_PMCG3_CFGR_PHYS(x)                                               ((x) + 0x00003e00)
#define HWIO_PMCG3_CFGR_RMSK                                                    0x703f3f
#define HWIO_PMCG3_CFGR_POR                                                   0x00701f07
#define HWIO_PMCG3_CFGR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG3_CFGR_ATTR                                                         0x1
#define HWIO_PMCG3_CFGR_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CFGR_ADDR(x), HWIO_PMCG3_CFGR_RMSK)
#define HWIO_PMCG3_CFGR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CFGR_ADDR(x), m)
#define HWIO_PMCG3_CFGR_CAPTURE_BMSK                                            0x400000
#define HWIO_PMCG3_CFGR_CAPTURE_SHFT                                                0x16
#define HWIO_PMCG3_CFGR_MSI_BMSK                                                0x200000
#define HWIO_PMCG3_CFGR_MSI_SHFT                                                    0x15
#define HWIO_PMCG3_CFGR_RELOC_CTRS_BMSK                                         0x100000
#define HWIO_PMCG3_CFGR_RELOC_CTRS_SHFT                                             0x14
#define HWIO_PMCG3_CFGR_SIZE_BMSK                                                 0x3f00
#define HWIO_PMCG3_CFGR_SIZE_SHFT                                                    0x8
#define HWIO_PMCG3_CFGR_NCTR_BMSK                                                   0x3f
#define HWIO_PMCG3_CFGR_NCTR_SHFT                                                    0x0

#define HWIO_PMCG3_CR_ADDR(x)                                                 ((x) + 0x00003e04)
#define HWIO_PMCG3_CR_PHYS(x)                                                 ((x) + 0x00003e04)
#define HWIO_PMCG3_CR_RMSK                                                           0x1
#define HWIO_PMCG3_CR_POR                                                     0x00000000
#define HWIO_PMCG3_CR_POR_RMSK                                                0xffffffff
#define HWIO_PMCG3_CR_ATTR                                                           0x3
#define HWIO_PMCG3_CR_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CR_ADDR(x), HWIO_PMCG3_CR_RMSK)
#define HWIO_PMCG3_CR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CR_ADDR(x), m)
#define HWIO_PMCG3_CR_OUT(x, v)      \
        out_dword(HWIO_PMCG3_CR_ADDR(x),v)
#define HWIO_PMCG3_CR_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_CR_ADDR(x),m,v,HWIO_PMCG3_CR_IN(x))
#define HWIO_PMCG3_CR_E_BMSK                                                         0x1
#define HWIO_PMCG3_CR_E_SHFT                                                         0x0

#define HWIO_PMCG3_CEID0_L_ADDR(x)                                            ((x) + 0x00003e20)
#define HWIO_PMCG3_CEID0_L_PHYS(x)                                            ((x) + 0x00003e20)
#define HWIO_PMCG3_CEID0_L_RMSK                                                     0xff
#define HWIO_PMCG3_CEID0_L_POR                                                0x000000e0
#define HWIO_PMCG3_CEID0_L_POR_RMSK                                           0xffffffff
#define HWIO_PMCG3_CEID0_L_ATTR                                                      0x1
#define HWIO_PMCG3_CEID0_L_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CEID0_L_ADDR(x), HWIO_PMCG3_CEID0_L_RMSK)
#define HWIO_PMCG3_CEID0_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CEID0_L_ADDR(x), m)
#define HWIO_PMCG3_CEID0_L_IMPL_EVENTS_BMSK                                         0xff
#define HWIO_PMCG3_CEID0_L_IMPL_EVENTS_SHFT                                          0x0

#define HWIO_PMCG3_CEID0_H_ADDR(x)                                            ((x) + 0x00003e24)
#define HWIO_PMCG3_CEID0_H_PHYS(x)                                            ((x) + 0x00003e24)
#define HWIO_PMCG3_CEID0_H_RMSK                                               0xffffffff
#define HWIO_PMCG3_CEID0_H_POR                                                0x00000000
#define HWIO_PMCG3_CEID0_H_POR_RMSK                                           0xffffffff
#define HWIO_PMCG3_CEID0_H_ATTR                                                      0x1
#define HWIO_PMCG3_CEID0_H_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CEID0_H_ADDR(x), HWIO_PMCG3_CEID0_H_RMSK)
#define HWIO_PMCG3_CEID0_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CEID0_H_ADDR(x), m)
#define HWIO_PMCG3_CEID0_H_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG3_CEID0_H_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG3_CEID1_L_ADDR(x)                                            ((x) + 0x00003e28)
#define HWIO_PMCG3_CEID1_L_PHYS(x)                                            ((x) + 0x00003e28)
#define HWIO_PMCG3_CEID1_L_RMSK                                               0xffffffff
#define HWIO_PMCG3_CEID1_L_POR                                                0x00000000
#define HWIO_PMCG3_CEID1_L_POR_RMSK                                           0xffffffff
#define HWIO_PMCG3_CEID1_L_ATTR                                                      0x1
#define HWIO_PMCG3_CEID1_L_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CEID1_L_ADDR(x), HWIO_PMCG3_CEID1_L_RMSK)
#define HWIO_PMCG3_CEID1_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CEID1_L_ADDR(x), m)
#define HWIO_PMCG3_CEID1_L_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG3_CEID1_L_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG3_CEID1_H_ADDR(x)                                            ((x) + 0x00003e2c)
#define HWIO_PMCG3_CEID1_H_PHYS(x)                                            ((x) + 0x00003e2c)
#define HWIO_PMCG3_CEID1_H_RMSK                                               0xffffffff
#define HWIO_PMCG3_CEID1_H_POR                                                0x00000000
#define HWIO_PMCG3_CEID1_H_POR_RMSK                                           0xffffffff
#define HWIO_PMCG3_CEID1_H_ATTR                                                      0x1
#define HWIO_PMCG3_CEID1_H_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CEID1_H_ADDR(x), HWIO_PMCG3_CEID1_H_RMSK)
#define HWIO_PMCG3_CEID1_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CEID1_H_ADDR(x), m)
#define HWIO_PMCG3_CEID1_H_NOT_IMPLEMENTED_BMSK                               0xffffffff
#define HWIO_PMCG3_CEID1_H_NOT_IMPLEMENTED_SHFT                                      0x0

#define HWIO_PMCG3_IMPL_CEID0_ADDR(x)                                         ((x) + 0x00003e30)
#define HWIO_PMCG3_IMPL_CEID0_PHYS(x)                                         ((x) + 0x00003e30)
#define HWIO_PMCG3_IMPL_CEID0_RMSK                                                  0x3f
#define HWIO_PMCG3_IMPL_CEID0_POR                                             0x0000003f
#define HWIO_PMCG3_IMPL_CEID0_POR_RMSK                                        0xffffffff
#define HWIO_PMCG3_IMPL_CEID0_ATTR                                                   0x1
#define HWIO_PMCG3_IMPL_CEID0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_IMPL_CEID0_ADDR(x), HWIO_PMCG3_IMPL_CEID0_RMSK)
#define HWIO_PMCG3_IMPL_CEID0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_IMPL_CEID0_ADDR(x), m)
#define HWIO_PMCG3_IMPL_CEID0_IMPL_EVENTS_BMSK                                      0x3f
#define HWIO_PMCG3_IMPL_CEID0_IMPL_EVENTS_SHFT                                       0x0

#define HWIO_PMCG3_IRQ_CTRL_ADDR(x)                                           ((x) + 0x00003e50)
#define HWIO_PMCG3_IRQ_CTRL_PHYS(x)                                           ((x) + 0x00003e50)
#define HWIO_PMCG3_IRQ_CTRL_RMSK                                                     0x1
#define HWIO_PMCG3_IRQ_CTRL_POR                                               0x00000000
#define HWIO_PMCG3_IRQ_CTRL_POR_RMSK                                          0xffffffff
#define HWIO_PMCG3_IRQ_CTRL_ATTR                                                     0x3
#define HWIO_PMCG3_IRQ_CTRL_IN(x)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CTRL_ADDR(x), HWIO_PMCG3_IRQ_CTRL_RMSK)
#define HWIO_PMCG3_IRQ_CTRL_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CTRL_ADDR(x), m)
#define HWIO_PMCG3_IRQ_CTRL_OUT(x, v)      \
        out_dword(HWIO_PMCG3_IRQ_CTRL_ADDR(x),v)
#define HWIO_PMCG3_IRQ_CTRL_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_IRQ_CTRL_ADDR(x),m,v,HWIO_PMCG3_IRQ_CTRL_IN(x))
#define HWIO_PMCG3_IRQ_CTRL_IRQEN_BMSK                                               0x1
#define HWIO_PMCG3_IRQ_CTRL_IRQEN_SHFT                                               0x0

#define HWIO_PMCG3_IRQ_CTRLACK_ADDR(x)                                        ((x) + 0x00003e54)
#define HWIO_PMCG3_IRQ_CTRLACK_PHYS(x)                                        ((x) + 0x00003e54)
#define HWIO_PMCG3_IRQ_CTRLACK_RMSK                                                  0x1
#define HWIO_PMCG3_IRQ_CTRLACK_POR                                            0x00000000
#define HWIO_PMCG3_IRQ_CTRLACK_POR_RMSK                                       0xffffffff
#define HWIO_PMCG3_IRQ_CTRLACK_ATTR                                                  0x1
#define HWIO_PMCG3_IRQ_CTRLACK_IN(x)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CTRLACK_ADDR(x), HWIO_PMCG3_IRQ_CTRLACK_RMSK)
#define HWIO_PMCG3_IRQ_CTRLACK_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CTRLACK_ADDR(x), m)
#define HWIO_PMCG3_IRQ_CTRLACK_IRQEN_BMSK                                            0x1
#define HWIO_PMCG3_IRQ_CTRLACK_IRQEN_SHFT                                            0x0

#define HWIO_PMCG3_IRQ_CFG0_L_ADDR(x)                                         ((x) + 0x00003e58)
#define HWIO_PMCG3_IRQ_CFG0_L_PHYS(x)                                         ((x) + 0x00003e58)
#define HWIO_PMCG3_IRQ_CFG0_L_RMSK                                            0xfffffffc
#define HWIO_PMCG3_IRQ_CFG0_L_POR                                             0x00000000
#define HWIO_PMCG3_IRQ_CFG0_L_POR_RMSK                                        0xffffffff
#define HWIO_PMCG3_IRQ_CFG0_L_ATTR                                                   0x3
#define HWIO_PMCG3_IRQ_CFG0_L_IN(x)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CFG0_L_ADDR(x), HWIO_PMCG3_IRQ_CFG0_L_RMSK)
#define HWIO_PMCG3_IRQ_CFG0_L_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CFG0_L_ADDR(x), m)
#define HWIO_PMCG3_IRQ_CFG0_L_OUT(x, v)      \
        out_dword(HWIO_PMCG3_IRQ_CFG0_L_ADDR(x),v)
#define HWIO_PMCG3_IRQ_CFG0_L_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_IRQ_CFG0_L_ADDR(x),m,v,HWIO_PMCG3_IRQ_CFG0_L_IN(x))
#define HWIO_PMCG3_IRQ_CFG0_L_ADDR_31_2_BMSK                                  0xfffffffc
#define HWIO_PMCG3_IRQ_CFG0_L_ADDR_31_2_SHFT                                         0x2

#define HWIO_PMCG3_IRQ_CFG0_H_ADDR(x)                                         ((x) + 0x00003e5c)
#define HWIO_PMCG3_IRQ_CFG0_H_PHYS(x)                                         ((x) + 0x00003e5c)
#define HWIO_PMCG3_IRQ_CFG0_H_RMSK                                                0xffff
#define HWIO_PMCG3_IRQ_CFG0_H_POR                                             0x00000000
#define HWIO_PMCG3_IRQ_CFG0_H_POR_RMSK                                        0xffffffff
#define HWIO_PMCG3_IRQ_CFG0_H_ATTR                                                   0x3
#define HWIO_PMCG3_IRQ_CFG0_H_IN(x)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CFG0_H_ADDR(x), HWIO_PMCG3_IRQ_CFG0_H_RMSK)
#define HWIO_PMCG3_IRQ_CFG0_H_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CFG0_H_ADDR(x), m)
#define HWIO_PMCG3_IRQ_CFG0_H_OUT(x, v)      \
        out_dword(HWIO_PMCG3_IRQ_CFG0_H_ADDR(x),v)
#define HWIO_PMCG3_IRQ_CFG0_H_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_IRQ_CFG0_H_ADDR(x),m,v,HWIO_PMCG3_IRQ_CFG0_H_IN(x))
#define HWIO_PMCG3_IRQ_CFG0_H_ADDR_47_32_BMSK                                     0xffff
#define HWIO_PMCG3_IRQ_CFG0_H_ADDR_47_32_SHFT                                        0x0

#define HWIO_PMCG3_IRQ_CFG1_ADDR(x)                                           ((x) + 0x00003e60)
#define HWIO_PMCG3_IRQ_CFG1_PHYS(x)                                           ((x) + 0x00003e60)
#define HWIO_PMCG3_IRQ_CFG1_RMSK                                              0xffffffff
#define HWIO_PMCG3_IRQ_CFG1_POR                                               0x00000000
#define HWIO_PMCG3_IRQ_CFG1_POR_RMSK                                          0xffffffff
#define HWIO_PMCG3_IRQ_CFG1_ATTR                                                     0x3
#define HWIO_PMCG3_IRQ_CFG1_IN(x)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CFG1_ADDR(x), HWIO_PMCG3_IRQ_CFG1_RMSK)
#define HWIO_PMCG3_IRQ_CFG1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CFG1_ADDR(x), m)
#define HWIO_PMCG3_IRQ_CFG1_OUT(x, v)      \
        out_dword(HWIO_PMCG3_IRQ_CFG1_ADDR(x),v)
#define HWIO_PMCG3_IRQ_CFG1_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_IRQ_CFG1_ADDR(x),m,v,HWIO_PMCG3_IRQ_CFG1_IN(x))
#define HWIO_PMCG3_IRQ_CFG1_DATA_BMSK                                         0xffffffff
#define HWIO_PMCG3_IRQ_CFG1_DATA_SHFT                                                0x0

#define HWIO_PMCG3_IRQ_CFG2_ADDR(x)                                           ((x) + 0x00003e64)
#define HWIO_PMCG3_IRQ_CFG2_PHYS(x)                                           ((x) + 0x00003e64)
#define HWIO_PMCG3_IRQ_CFG2_RMSK                                                    0x3f
#define HWIO_PMCG3_IRQ_CFG2_POR                                               0x00000000
#define HWIO_PMCG3_IRQ_CFG2_POR_RMSK                                          0xffffffff
#define HWIO_PMCG3_IRQ_CFG2_ATTR                                                     0x3
#define HWIO_PMCG3_IRQ_CFG2_IN(x)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CFG2_ADDR(x), HWIO_PMCG3_IRQ_CFG2_RMSK)
#define HWIO_PMCG3_IRQ_CFG2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_IRQ_CFG2_ADDR(x), m)
#define HWIO_PMCG3_IRQ_CFG2_OUT(x, v)      \
        out_dword(HWIO_PMCG3_IRQ_CFG2_ADDR(x),v)
#define HWIO_PMCG3_IRQ_CFG2_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_PMCG3_IRQ_CFG2_ADDR(x),m,v,HWIO_PMCG3_IRQ_CFG2_IN(x))
#define HWIO_PMCG3_IRQ_CFG2_SH_BMSK                                                 0x30
#define HWIO_PMCG3_IRQ_CFG2_SH_SHFT                                                  0x4
#define HWIO_PMCG3_IRQ_CFG2_MEMATTR_BMSK                                             0xf
#define HWIO_PMCG3_IRQ_CFG2_MEMATTR_SHFT                                             0x0

#define HWIO_PMCG3_AIDR_ADDR(x)                                               ((x) + 0x00003e70)
#define HWIO_PMCG3_AIDR_PHYS(x)                                               ((x) + 0x00003e70)
#define HWIO_PMCG3_AIDR_RMSK                                                        0xff
#define HWIO_PMCG3_AIDR_POR                                                   0x00000000
#define HWIO_PMCG3_AIDR_POR_RMSK                                              0xffffffff
#define HWIO_PMCG3_AIDR_ATTR                                                         0x1
#define HWIO_PMCG3_AIDR_IN(x)      \
        in_dword_masked(HWIO_PMCG3_AIDR_ADDR(x), HWIO_PMCG3_AIDR_RMSK)
#define HWIO_PMCG3_AIDR_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_AIDR_ADDR(x), m)
#define HWIO_PMCG3_AIDR_ARCHMAJORREC_BMSK                                           0xf0
#define HWIO_PMCG3_AIDR_ARCHMAJORREC_SHFT                                            0x4
#define HWIO_PMCG3_AIDR_ARCHMINORREV_BMSK                                            0xf
#define HWIO_PMCG3_AIDR_ARCHMINORREV_SHFT                                            0x0

#define HWIO_PMCG3_IMPDEF0_FILTERn_ADDR(base,n)                               ((base) + 0x00003ec0 + 0x8 * (n))
#define HWIO_PMCG3_IMPDEF0_FILTERn_PHYS(base,n)                               ((base) + 0x00003ec0 + 0x8 * (n))
#define HWIO_PMCG3_IMPDEF0_FILTERn_RMSK                                       0x7fffffff
#define HWIO_PMCG3_IMPDEF0_FILTERn_MAXn                                                7
#define HWIO_PMCG3_IMPDEF0_FILTERn_POR                                        0x78003f8f
#define HWIO_PMCG3_IMPDEF0_FILTERn_POR_RMSK                                   0xffffffff
#define HWIO_PMCG3_IMPDEF0_FILTERn_ATTR                                              0x3
#define HWIO_PMCG3_IMPDEF0_FILTERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG3_IMPDEF0_FILTERn_ADDR(base,n), HWIO_PMCG3_IMPDEF0_FILTERn_RMSK)
#define HWIO_PMCG3_IMPDEF0_FILTERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG3_IMPDEF0_FILTERn_ADDR(base,n), mask)
#define HWIO_PMCG3_IMPDEF0_FILTERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG3_IMPDEF0_FILTERn_ADDR(base,n),val)
#define HWIO_PMCG3_IMPDEF0_FILTERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG3_IMPDEF0_FILTERn_ADDR(base,n),mask,val,HWIO_PMCG3_IMPDEF0_FILTERn_INI(base,n))
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_TLB_S1_BMSK                          0x40000000
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_TLB_S1_SHFT                                0x1e
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_TLB_S1_NF_BMSK                       0x20000000
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_TLB_S1_NF_SHFT                             0x1d
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_TLB_S2_BMSK                          0x10000000
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_TLB_S2_SHFT                                0x1c
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_TLB_S2_NF_BMSK                        0x8000000
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_TLB_S2_NF_SHFT                             0x1b
#define HWIO_PMCG3_IMPDEF0_FILTERn_FILTER_TLB_INDEX_EN_BMSK                    0x4000000
#define HWIO_PMCG3_IMPDEF0_FILTERn_FILTER_TLB_INDEX_EN_SHFT                         0x1a
#define HWIO_PMCG3_IMPDEF0_FILTERn_TLB_INDEX_BMSK                              0x3ffc000
#define HWIO_PMCG3_IMPDEF0_FILTERn_TLB_INDEX_SHFT                                    0xe
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_S1_BMSK                              0x2000
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_S1_SHFT                                 0xd
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_S2_BMSK                              0x1000
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_S2_SHFT                                 0xc
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_CDIPA2PA_BMSK                         0x800
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_CDIPA2PA_SHFT                           0xb
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_LEV0_BMSK                             0x400
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_LEV0_SHFT                               0xa
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_LEV1_BMSK                             0x200
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_LEV1_SHFT                               0x9
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_LEV2_BMSK                             0x100
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_LEV2_SHFT                               0x8
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_LEV3_BMSK                              0x80
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_HTW_LEV3_SHFT                               0x7
#define HWIO_PMCG3_IMPDEF0_FILTERn_FILTER_ALLOC_POLICY_EN_BMSK                      0x40
#define HWIO_PMCG3_IMPDEF0_FILTERn_FILTER_ALLOC_POLICY_EN_SHFT                       0x6
#define HWIO_PMCG3_IMPDEF0_FILTERn_ALLOC_POLICY_BMSK                                0x30
#define HWIO_PMCG3_IMPDEF0_FILTERn_ALLOC_POLICY_SHFT                                 0x4
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_CFG_STE_L1_BMSK                             0x8
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_CFG_STE_L1_SHFT                             0x3
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_CFG_STE_L2_BMSK                             0x4
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_CFG_STE_L2_SHFT                             0x2
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_CFG_CD_L1_BMSK                              0x2
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_CFG_CD_L1_SHFT                              0x1
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_CFG_CD_L2_BMSK                              0x1
#define HWIO_PMCG3_IMPDEF0_FILTERn_COUNT_CFG_CD_L2_SHFT                              0x0

#define HWIO_PMCG3_IMPDEF1_FILTERn_ADDR(base,n)                               ((base) + 0x00003ec4 + 0x8 * (n))
#define HWIO_PMCG3_IMPDEF1_FILTERn_PHYS(base,n)                               ((base) + 0x00003ec4 + 0x8 * (n))
#define HWIO_PMCG3_IMPDEF1_FILTERn_RMSK                                       0xffffffff
#define HWIO_PMCG3_IMPDEF1_FILTERn_MAXn                                                7
#define HWIO_PMCG3_IMPDEF1_FILTERn_POR                                        0x0f800000
#define HWIO_PMCG3_IMPDEF1_FILTERn_POR_RMSK                                   0xffffffff
#define HWIO_PMCG3_IMPDEF1_FILTERn_ATTR                                              0x3
#define HWIO_PMCG3_IMPDEF1_FILTERn_INI(base,n)        \
        in_dword_masked(HWIO_PMCG3_IMPDEF1_FILTERn_ADDR(base,n), HWIO_PMCG3_IMPDEF1_FILTERn_RMSK)
#define HWIO_PMCG3_IMPDEF1_FILTERn_INMI(base,n,mask)    \
        in_dword_masked(HWIO_PMCG3_IMPDEF1_FILTERn_ADDR(base,n), mask)
#define HWIO_PMCG3_IMPDEF1_FILTERn_OUTI(base,n,val)    \
        out_dword(HWIO_PMCG3_IMPDEF1_FILTERn_ADDR(base,n),val)
#define HWIO_PMCG3_IMPDEF1_FILTERn_OUTMI(base,n,mask,val) \
        out_dword_masked_ns(HWIO_PMCG3_IMPDEF1_FILTERn_ADDR(base,n),mask,val,HWIO_PMCG3_IMPDEF1_FILTERn_INI(base,n))
#define HWIO_PMCG3_IMPDEF1_FILTERn_COUNT_MID_EN_BMSK                          0x80000000
#define HWIO_PMCG3_IMPDEF1_FILTERn_COUNT_MID_EN_SHFT                                0x1f
#define HWIO_PMCG3_IMPDEF1_FILTERn_MID_HI_BMSK                                0x70000000
#define HWIO_PMCG3_IMPDEF1_FILTERn_MID_HI_SHFT                                      0x1c
#define HWIO_PMCG3_IMPDEF1_FILTERn_COUNT_TRAN_SRC_MID_LO_BMSK                  0xf800000
#define HWIO_PMCG3_IMPDEF1_FILTERn_COUNT_TRAN_SRC_MID_LO_SHFT                       0x17
#define HWIO_PMCG3_IMPDEF1_FILTERn_COUNT_SSID_VALID_EN_BMSK                     0x400000
#define HWIO_PMCG3_IMPDEF1_FILTERn_COUNT_SSID_VALID_EN_SHFT                         0x16
#define HWIO_PMCG3_IMPDEF1_FILTERn_SSID_VALID_BMSK                              0x200000
#define HWIO_PMCG3_IMPDEF1_FILTERn_SSID_VALID_SHFT                                  0x15
#define HWIO_PMCG3_IMPDEF1_FILTERn_COUNT_SSID_SPAN_EN_BMSK                      0x100000
#define HWIO_PMCG3_IMPDEF1_FILTERn_COUNT_SSID_SPAN_EN_SHFT                          0x14
#define HWIO_PMCG3_IMPDEF1_FILTERn_SSID_BMSK                                     0xfffff
#define HWIO_PMCG3_IMPDEF1_FILTERn_SSID_SHFT                                         0x0

#define HWIO_PMCG3_PIDR4_ADDR(x)                                              ((x) + 0x00003fd0)
#define HWIO_PMCG3_PIDR4_PHYS(x)                                              ((x) + 0x00003fd0)
#define HWIO_PMCG3_PIDR4_RMSK                                                       0xff
#define HWIO_PMCG3_PIDR4_POR                                                  0x00000000
#define HWIO_PMCG3_PIDR4_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_PIDR4_ATTR                                                        0x1
#define HWIO_PMCG3_PIDR4_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PIDR4_ADDR(x), HWIO_PMCG3_PIDR4_RMSK)
#define HWIO_PMCG3_PIDR4_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PIDR4_ADDR(x), m)
#define HWIO_PMCG3_PIDR4_SIZE_BMSK                                                  0xff
#define HWIO_PMCG3_PIDR4_SIZE_SHFT                                                   0x0

#define HWIO_PMCG3_PIDR5_ADDR(x)                                              ((x) + 0x00003fd4)
#define HWIO_PMCG3_PIDR5_PHYS(x)                                              ((x) + 0x00003fd4)
#define HWIO_PMCG3_PIDR5_RMSK                                                 0xffffffff
#define HWIO_PMCG3_PIDR5_POR                                                  0x00000000
#define HWIO_PMCG3_PIDR5_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_PIDR5_ATTR                                                        0x1
#define HWIO_PMCG3_PIDR5_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PIDR5_ADDR(x), HWIO_PMCG3_PIDR5_RMSK)
#define HWIO_PMCG3_PIDR5_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PIDR5_ADDR(x), m)
#define HWIO_PMCG3_PIDR5_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG3_PIDR5_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG3_PIDR6_ADDR(x)                                              ((x) + 0x00003fd8)
#define HWIO_PMCG3_PIDR6_PHYS(x)                                              ((x) + 0x00003fd8)
#define HWIO_PMCG3_PIDR6_RMSK                                                 0xffffffff
#define HWIO_PMCG3_PIDR6_POR                                                  0x00000000
#define HWIO_PMCG3_PIDR6_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_PIDR6_ATTR                                                        0x1
#define HWIO_PMCG3_PIDR6_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PIDR6_ADDR(x), HWIO_PMCG3_PIDR6_RMSK)
#define HWIO_PMCG3_PIDR6_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PIDR6_ADDR(x), m)
#define HWIO_PMCG3_PIDR6_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG3_PIDR6_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG3_PIDR7_ADDR(x)                                              ((x) + 0x00003fdc)
#define HWIO_PMCG3_PIDR7_PHYS(x)                                              ((x) + 0x00003fdc)
#define HWIO_PMCG3_PIDR7_RMSK                                                 0xffffffff
#define HWIO_PMCG3_PIDR7_POR                                                  0x00000000
#define HWIO_PMCG3_PIDR7_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_PIDR7_ATTR                                                        0x1
#define HWIO_PMCG3_PIDR7_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PIDR7_ADDR(x), HWIO_PMCG3_PIDR7_RMSK)
#define HWIO_PMCG3_PIDR7_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PIDR7_ADDR(x), m)
#define HWIO_PMCG3_PIDR7_RSRVED_31_0_BMSK                                     0xffffffff
#define HWIO_PMCG3_PIDR7_RSRVED_31_0_SHFT                                            0x0

#define HWIO_PMCG3_PIDR0_ADDR(x)                                              ((x) + 0x00003fe0)
#define HWIO_PMCG3_PIDR0_PHYS(x)                                              ((x) + 0x00003fe0)
#define HWIO_PMCG3_PIDR0_RMSK                                                       0xff
#define HWIO_PMCG3_PIDR0_POR                                                  0x00000040
#define HWIO_PMCG3_PIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_PIDR0_ATTR                                                        0x1
#define HWIO_PMCG3_PIDR0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PIDR0_ADDR(x), HWIO_PMCG3_PIDR0_RMSK)
#define HWIO_PMCG3_PIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PIDR0_ADDR(x), m)
#define HWIO_PMCG3_PIDR0_PART_0_BMSK                                                0xff
#define HWIO_PMCG3_PIDR0_PART_0_SHFT                                                 0x0

#define HWIO_PMCG3_PIDR1_ADDR(x)                                              ((x) + 0x00003fe4)
#define HWIO_PMCG3_PIDR1_PHYS(x)                                              ((x) + 0x00003fe4)
#define HWIO_PMCG3_PIDR1_RMSK                                                      0xf0f
#define HWIO_PMCG3_PIDR1_POR                                                  0x00000000
#define HWIO_PMCG3_PIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_PIDR1_ATTR                                                        0x1
#define HWIO_PMCG3_PIDR1_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PIDR1_ADDR(x), HWIO_PMCG3_PIDR1_RMSK)
#define HWIO_PMCG3_PIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PIDR1_ADDR(x), m)
#define HWIO_PMCG3_PIDR1_PART_1_BMSK                                               0xf00
#define HWIO_PMCG3_PIDR1_PART_1_SHFT                                                 0x8
#define HWIO_PMCG3_PIDR1_DES_0_BMSK                                                  0xf
#define HWIO_PMCG3_PIDR1_DES_0_SHFT                                                  0x0

#define HWIO_PMCG3_PIDR2_ADDR(x)                                              ((x) + 0x00003fe8)
#define HWIO_PMCG3_PIDR2_PHYS(x)                                              ((x) + 0x00003fe8)
#define HWIO_PMCG3_PIDR2_RMSK                                                       0xff
#define HWIO_PMCG3_PIDR2_POR                                                  0x0000003f
#define HWIO_PMCG3_PIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_PIDR2_ATTR                                                        0x1
#define HWIO_PMCG3_PIDR2_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PIDR2_ADDR(x), HWIO_PMCG3_PIDR2_RMSK)
#define HWIO_PMCG3_PIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PIDR2_ADDR(x), m)
#define HWIO_PMCG3_PIDR2_REVISION_BMSK                                              0xf0
#define HWIO_PMCG3_PIDR2_REVISION_SHFT                                               0x4
#define HWIO_PMCG3_PIDR2_JEDEC_VAL_BMSK                                              0x8
#define HWIO_PMCG3_PIDR2_JEDEC_VAL_SHFT                                              0x3
#define HWIO_PMCG3_PIDR2_DES_1_BMSK                                                  0x7
#define HWIO_PMCG3_PIDR2_DES_1_SHFT                                                  0x0

#define HWIO_PMCG3_PIDR3_ADDR(x)                                              ((x) + 0x00003fec)
#define HWIO_PMCG3_PIDR3_PHYS(x)                                              ((x) + 0x00003fec)
#define HWIO_PMCG3_PIDR3_RMSK                                                       0xff
#define HWIO_PMCG3_PIDR3_POR                                                  0x00000000
#define HWIO_PMCG3_PIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_PIDR3_ATTR                                                        0x1
#define HWIO_PMCG3_PIDR3_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PIDR3_ADDR(x), HWIO_PMCG3_PIDR3_RMSK)
#define HWIO_PMCG3_PIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PIDR3_ADDR(x), m)
#define HWIO_PMCG3_PIDR3_REVAND_BMSK                                                0xf0
#define HWIO_PMCG3_PIDR3_REVAND_SHFT                                                 0x4
#define HWIO_PMCG3_PIDR3_CMOD_BMSK                                                   0xf
#define HWIO_PMCG3_PIDR3_CMOD_SHFT                                                   0x0

#define HWIO_PMCG3_CIDR0_ADDR(x)                                              ((x) + 0x00003ff0)
#define HWIO_PMCG3_CIDR0_PHYS(x)                                              ((x) + 0x00003ff0)
#define HWIO_PMCG3_CIDR0_RMSK                                                 0xffffffff
#define HWIO_PMCG3_CIDR0_POR                                                  0x0000000d
#define HWIO_PMCG3_CIDR0_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_CIDR0_ATTR                                                        0x1
#define HWIO_PMCG3_CIDR0_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CIDR0_ADDR(x), HWIO_PMCG3_CIDR0_RMSK)
#define HWIO_PMCG3_CIDR0_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CIDR0_ADDR(x), m)
#define HWIO_PMCG3_CIDR0_COMPONENT_IDR0_BMSK                                  0xffffffff
#define HWIO_PMCG3_CIDR0_COMPONENT_IDR0_SHFT                                         0x0

#define HWIO_PMCG3_CIDR1_ADDR(x)                                              ((x) + 0x00003ff4)
#define HWIO_PMCG3_CIDR1_PHYS(x)                                              ((x) + 0x00003ff4)
#define HWIO_PMCG3_CIDR1_RMSK                                                 0xffffffff
#define HWIO_PMCG3_CIDR1_POR                                                  0x000000f0
#define HWIO_PMCG3_CIDR1_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_CIDR1_ATTR                                                        0x1
#define HWIO_PMCG3_CIDR1_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CIDR1_ADDR(x), HWIO_PMCG3_CIDR1_RMSK)
#define HWIO_PMCG3_CIDR1_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CIDR1_ADDR(x), m)
#define HWIO_PMCG3_CIDR1_COMPONENT_IDR1_BMSK                                  0xffffffff
#define HWIO_PMCG3_CIDR1_COMPONENT_IDR1_SHFT                                         0x0

#define HWIO_PMCG3_CIDR2_ADDR(x)                                              ((x) + 0x00003ff8)
#define HWIO_PMCG3_CIDR2_PHYS(x)                                              ((x) + 0x00003ff8)
#define HWIO_PMCG3_CIDR2_RMSK                                                 0xffffffff
#define HWIO_PMCG3_CIDR2_POR                                                  0x00000005
#define HWIO_PMCG3_CIDR2_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_CIDR2_ATTR                                                        0x1
#define HWIO_PMCG3_CIDR2_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CIDR2_ADDR(x), HWIO_PMCG3_CIDR2_RMSK)
#define HWIO_PMCG3_CIDR2_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CIDR2_ADDR(x), m)
#define HWIO_PMCG3_CIDR2_COMPONENT_IDR2_BMSK                                  0xffffffff
#define HWIO_PMCG3_CIDR2_COMPONENT_IDR2_SHFT                                         0x0

#define HWIO_PMCG3_CIDR3_ADDR(x)                                              ((x) + 0x00003ffc)
#define HWIO_PMCG3_CIDR3_PHYS(x)                                              ((x) + 0x00003ffc)
#define HWIO_PMCG3_CIDR3_RMSK                                                 0xffffffff
#define HWIO_PMCG3_CIDR3_POR                                                  0x000000b1
#define HWIO_PMCG3_CIDR3_POR_RMSK                                             0xffffffff
#define HWIO_PMCG3_CIDR3_ATTR                                                        0x1
#define HWIO_PMCG3_CIDR3_IN(x)      \
        in_dword_masked(HWIO_PMCG3_CIDR3_ADDR(x), HWIO_PMCG3_CIDR3_RMSK)
#define HWIO_PMCG3_CIDR3_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_CIDR3_ADDR(x), m)
#define HWIO_PMCG3_CIDR3_COMPONENT_IDR3_BMSK                                  0xffffffff
#define HWIO_PMCG3_CIDR3_COMPONENT_IDR3_SHFT                                         0x0

#define HWIO_PMCG3_PMAUTHSTATUS_ADDR(x)                                       ((x) + 0x00003fb8)
#define HWIO_PMCG3_PMAUTHSTATUS_PHYS(x)                                       ((x) + 0x00003fb8)
#define HWIO_PMCG3_PMAUTHSTATUS_RMSK                                                0xff
#define HWIO_PMCG3_PMAUTHSTATUS_POR                                           0x00000088
#define HWIO_PMCG3_PMAUTHSTATUS_POR_RMSK                                      0xffffffff
#define HWIO_PMCG3_PMAUTHSTATUS_ATTR                                                 0x1
#define HWIO_PMCG3_PMAUTHSTATUS_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PMAUTHSTATUS_ADDR(x), HWIO_PMCG3_PMAUTHSTATUS_RMSK)
#define HWIO_PMCG3_PMAUTHSTATUS_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PMAUTHSTATUS_ADDR(x), m)
#define HWIO_PMCG3_PMAUTHSTATUS_AUTHSTATUS_BMSK                                     0xff
#define HWIO_PMCG3_PMAUTHSTATUS_AUTHSTATUS_SHFT                                      0x0

#define HWIO_PMCG3_PMDEVARCH_ADDR(x)                                          ((x) + 0x00003fbc)
#define HWIO_PMCG3_PMDEVARCH_PHYS(x)                                          ((x) + 0x00003fbc)
#define HWIO_PMCG3_PMDEVARCH_RMSK                                             0xffffffff
#define HWIO_PMCG3_PMDEVARCH_POR                                              0x0e102a56
#define HWIO_PMCG3_PMDEVARCH_POR_RMSK                                         0xffffffff
#define HWIO_PMCG3_PMDEVARCH_ATTR                                                    0x1
#define HWIO_PMCG3_PMDEVARCH_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PMDEVARCH_ADDR(x), HWIO_PMCG3_PMDEVARCH_RMSK)
#define HWIO_PMCG3_PMDEVARCH_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PMDEVARCH_ADDR(x), m)
#define HWIO_PMCG3_PMDEVARCH_ARCHITECT_BMSK                                   0xffe00000
#define HWIO_PMCG3_PMDEVARCH_ARCHITECT_SHFT                                         0x15
#define HWIO_PMCG3_PMDEVARCH_PRESENT_BMSK                                       0x100000
#define HWIO_PMCG3_PMDEVARCH_PRESENT_SHFT                                           0x14
#define HWIO_PMCG3_PMDEVARCH_REVISION_BMSK                                       0xf0000
#define HWIO_PMCG3_PMDEVARCH_REVISION_SHFT                                          0x10
#define HWIO_PMCG3_PMDEVARCH_ARCHID_BMSK                                          0xffff
#define HWIO_PMCG3_PMDEVARCH_ARCHID_SHFT                                             0x0

#define HWIO_PMCG3_PMDEVTYPE_ADDR(x)                                          ((x) + 0x00003fcc)
#define HWIO_PMCG3_PMDEVTYPE_PHYS(x)                                          ((x) + 0x00003fcc)
#define HWIO_PMCG3_PMDEVTYPE_RMSK                                                   0xff
#define HWIO_PMCG3_PMDEVTYPE_POR                                              0x00000056
#define HWIO_PMCG3_PMDEVTYPE_POR_RMSK                                         0xffffffff
#define HWIO_PMCG3_PMDEVTYPE_ATTR                                                    0x1
#define HWIO_PMCG3_PMDEVTYPE_IN(x)      \
        in_dword_masked(HWIO_PMCG3_PMDEVTYPE_ADDR(x), HWIO_PMCG3_PMDEVTYPE_RMSK)
#define HWIO_PMCG3_PMDEVTYPE_INM(x, m)      \
        in_dword_masked(HWIO_PMCG3_PMDEVTYPE_ADDR(x), m)
#define HWIO_PMCG3_PMDEVTYPE_SUB_TYPE_BMSK                                          0xf0
#define HWIO_PMCG3_PMDEVTYPE_SUB_TYPE_SHFT                                           0x4
#define HWIO_PMCG3_PMDEVTYPE_CLASS_BMSK                                              0xf
#define HWIO_PMCG3_PMDEVTYPE_CLASS_SHFT                                              0x0

#endif