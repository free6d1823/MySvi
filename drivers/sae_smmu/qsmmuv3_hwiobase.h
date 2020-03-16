
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

#ifndef __QSMMUV3_HWIOBASE_H__
#define __QSMMUV3_HWIOBASE_H__

#define QSMMUV3_BASE                                                0x00000000
#define QSMMUV3_BASE_SIZE                                           0x100000000
#define QSMMUV3_BASE_PHYS                                           0x00000000
/*
#ifndef QSMMU_QSMMUV3_GLOBALREG_SPACE1_REG_BASE
#define QSMMU_QSMMUV3_GLOBALREG_SPACE1_REG_BASE    0x00010000//                 (QSMMUV3_BASE      + 0x00010000)
#endif
#ifndef QSMMU_QSMMUV3_IMPDEF_REG_BASE
#define QSMMU_QSMMUV3_IMPDEF_REG_BASE              0x00028000//                               (QSMMUV3_BASE      + 0x00028000)
#endif
#define HWIO_QGLOBAL_CR1_DISPATCHER_EN_BMSK                                           0x4000
#define HWIO_QGLOBAL_CR1_DISPATCHER_EN_SHFT                                              0xe
#define HWIO_QGLOBAL_CR3_OUTM(x,m,v) \
        out_dword_masked_ns(HWIO_QGLOBAL_CR3_ADDR(x),m,v,HWIO_QGLOBAL_CR3_IN(x))
#define HWIO_QGLOBAL_CR3_RESP_SRT_TID_DIS_FEAT_EN_BMSK                                   0x1

#define OUTP32(addr, val)    out_dword(addr, val)
*/
#define OUTP32(addr, val)    out_dword(addr, val)
#endif
