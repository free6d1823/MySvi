
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


#ifndef __VVDRV_QSMMUV3_STE_H__
#define __VVDRV_QSMMUV3_STE_H__
#include <stdint.h>
//#include "VVDRV_qsmmuv3_CommonInclude.h"

typedef enum {
  STE_INVALID = 0,
  STE_VALID = 1
} STE_V;

typedef enum {
  STE_TYPE_FAULT = 0,
  STE_TYPE_BYPASS = 4,
  STE_TYPE_STAGE1 = 5,
  STE_TYPE_STAGE2 = 6,
  STE_TYPE_NESTED = 7
} STE_Type;

typedef enum {
  STE_HTTU_DISABLED = 0,
  STE_HTTU_ACCESS_ONLY = 2,
  STE_HTTU_ACCESS_DIRTY = 3
} STE_HTTU;

typedef enum {
  STE_PIPA_PA = 0,
  STE_PIPA_IPA = 1
} STE_PIPA;

typedef enum {
  STE_DSS_DISABLED = 0,
  STE_DSS_BYPASS = 1,
  STE_DSS_SS_0 = 2
} STE_DSS;

typedef enum {
  STE_CxR_NC = 0,
  STE_CxR_WB = 1,
  STE_CxR_WT = 2,
  STE_CxR_WBnRA = 3
} STE_CxR;

typedef enum {
  STE_CSH_NONE = 0,
  STE_CSH_OUTER = 2,
  STE_CSH_INNER = 3
} STE_CSH;

typedef enum {
  STE_S1FMT_LINEAR = 0,
  STE_S1FMT_TWO_LEVEL_4k = 1,
  STE_S1FMT_TWO_LEVEL_64k = 2,
} STE_S1Fmt;

typedef enum {
  STE_PPAR_NO_PASID_TLP = 0,
  STE_PPAR_PASID_TLP = 1
} STE_PPAR;

typedef enum {
  STE_MEV_OFF = 0,
  STE_MEV_ON = 1
} STE_MEV;

typedef enum {
  STE_TTFMT_V7L = 0,
  STE_TTFMT_V8L = 1,
  STE_TTFMT_V7S = 2
} STE_TTFmt;

typedef enum {
  STE_ARS_TERM_SILENT = 0,
  STE_ARS_TERM_RECORD = 2,
  STE_ARS_STALL_SILENT = 1,
  STE_ARS_STALL_RECORD = 3,
  STE_ARS_STALL_ABORT_SILENT = 5,
  STE_ARS_STALL_ABORT_RECORD = 7,
  STE_ARS_ABORT_SILENT = 4,
  STE_ARS_ABORT_RECORD = 6
} STE_ARS;

typedef enum {
  STE_STALLD_STALL = 0,
  STE_STALLD_FAULT = 1
} STE_StallD;

typedef enum {
  STE_EATS_TERMINATE = 0,
  STE_EATS_TRANSLATE = 1,
  STE_EATS_STAGE1_TRANSLATE = 2
} STE_EATS;

typedef enum {
  STE_STRW_NS_EL1 = 0,
  STE_STRW_EL2 = 1,
  STE_STRW_SECURE = 0,
  STE_STRW_EL3 = 1
} STE_STRW;

typedef enum {
  STE_MEMATTR_DEVICE_nGnRnE = 0x0,
  STE_MEMATTR_DEVICE_nGnRE = 0x1,
  STE_MEMATTR_DEVICE_nGRE = 0x2,
  STE_MEMATTR_DEVICE_GRE = 0x3,
  STE_MEMATTR_NORMAL_NC = 0x5,
  STE_MEMATTR_NORMAL_WT = 0xa,
  STE_MEMATTR_NORMAL_WB = 0xf
} STE_MemAttr;

typedef enum {
  STE_ALLOCCFG_INCOMING = 0,
  STE_ALLOCCFG_NONE = 0x8,
  STE_ALLOCCFG_TR = 0x9,
  STE_ALLOCCFG_WA = 0xa,
  STE_ALLOCCFG_WA_TR = 0xb,
  STE_ALLOCCFG_RA = 0xc,
  STE_ALLOCCFG_RA_TR = 0xd,
  STE_ALLOCCFG_RA_WA = 0xe,
  STE_ALLOCCFG_RA_WA_TR = 0xf
} STE_AllocCfg;

// this define is not coherent with ARM SMMU spec
//typedef enum {
//  STE_SHCFG_INCOMING = 0,
//  STE_SHCFG_OUTER = 1,
//  STE_SHCFG_INNER = 2,
//  STE_SHCFG_NONE = 3
//} STE_ShCfg;
typedef enum {
  STE_SHCFG_NONE = 0,
  STE_SHCFG_INCOMING = 1,
  STE_SHCFG_OUTER = 2,
  STE_SHCFG_INNER = 3
} STE_ShCfg;

typedef enum {
  STE_NSCFG_INCOMING = 0,
  STE_NSCFG_SECURE = 2,
  STE_NSCFG_NONSECURE = 3
} STE_NSCfg;

typedef enum {
  STE_PRIVCFG_INCOMING = 0,
  STE_PRIVCFG_UNPRIV = 2,
  STE_PRIVCFG_PRIV = 3
} STE_PrivCfg;

typedef enum {
  STE_INSTCFG_INCOMING = 0,
  STE_INSTCFG_DATA = 2,
  STE_INSTCFG_INST = 3
} STE_InstCfg;

typedef enum{
  STE_ATS_NO_WA = 0,
  STE_ATS_WA = 1
} STE_ATS_WA_ENUM;

typedef enum{
  STE_ATS_NO_RA = 0,
  STE_ATS_RA = 1
} STE_ATS_RA_ENUM;

typedef enum{
  STE_ATS_NON_TRANSIENT = 0,
  STE_ATS_TRANSIENT = 1
} STE_ATS_TR;

typedef enum {
  STE_ATS_SHCFG_INCOMING = 0,
  STE_ATS_SHCFG_OUTER = 1,
  STE_ATS_SHCFG_INNER = 2,
  STE_ATS_SHCFG_NONE = 3
} STE_ATS_ShCfg;

typedef enum{
  STE_S2SL0_4KL2_L3 = 0,
  STE_S2SL0_4KL1_L2 = 1,
  STE_S2SL0_4KL0_L1 = 2,
} STE_S2SL0;

typedef enum {
  STE_S2IR0_NC = 0,
  STE_S2IR0_WBC_RA_WA = 1,
  STE_S2IR0_WTC_RA = 2,
  STE_S2IR0_WBC_RA_NWA = 3
} STE_S2IR0;

typedef enum {
  STE_S2OR0_NC = 0,
  STE_S2OR0_WBC_RA_WA = 1,
  STE_S2OR0_WTC_RA = 2,
  STE_S2OR0_WBC_RA_NWA = 3
} STE_S2OR0;

typedef enum {
  STE_S2SH0_NS = 0,
  STE_S2SH0_RES = 1,
  STE_S2SH0_OS = 2,
  STE_S2SH0_IS = 3
} STE_S2SH0;

typedef enum {
  STE_S2TG_4K = 0,
  STE_S2TG_64K = 1,
  STE_S2TG_16K = 2
} STE_S2TG;

typedef enum {
  STE_S2PS_32BITS = 0,
  STE_S2PS_36BITS = 1,
  STE_S2PS_40BITS = 2,
  STE_S2PS_42BITS = 3,
  STE_S2PS_44BITS = 4,
  STE_S2PS_48BITS = 5
} STE_S2PS;

typedef enum {
  STE_S2AA64_AARCH32 = 0,
  STE_S2AA64_AARCH64 = 1
} STE_S2AA64;

typedef enum {
  STE_S2ENDI_LITTLE = 0,
  STE_S2ENDI_BIG = 1
} STE_S2ENDI;

typedef enum {
  STE_S2AFFD_FAULT = 0,
  STE_S2AFFD_NOFAULT = 1
} STE_S2AFFD;

typedef enum {
  STE_S2PTW_PROTECT_OFF = 0,
  STE_S2PTW_PROTECT_ON = 1,
} STE_S2PTW;

typedef enum {
  STE_S2HA_DISABLE = 0,
  STE_S2HA_ENABLE = 1
} STE_S2HA;

typedef enum {
  STE_S2HD_DISABLE = 0,
  STE_S2HD_ENABLE = 1
} STE_S2HD;

typedef enum {
  STE_S2S_OFF = 0,
  STE_S2S_ON = 1
} STE_S2S;

typedef enum {
  STE_S2R_OFF = 0,
  STE_S2R_ON = 1 
} STE_S2R;

typedef enum {
  STE_S2T0SZ_32 = 32,
  STE_S2T0SZ_36 = 28,
  STE_S2T0SZ_40 = 24,
  STE_S2T0SZ_44 = 20,
  STE_S2T0SZ_48 = 16,
  STE_S2T0SZ_v7L_32 = 0
} STE_S2T0SZ;

void VVDRV_qsmmuv3_writeSTE_full(uint64_t ste_base, int ste_index, STE_V v, STE_Type config, STE_S1Fmt s1fmt, uint64_t s1contextptr, int cdmax, STE_DSS dss, STE_CxR cir, STE_CxR cor, STE_CSH csh, int cont, STE_PPAR ppar, STE_MEV mev, STE_StallD stalld, STE_EATS eats, STE_STRW strw, STE_MemAttr memattr, int mtcfg, STE_AllocCfg alloccfg, STE_ShCfg shcfg, STE_NSCfg nscfg, STE_PrivCfg privcfg, STE_InstCfg instcfg, int s2vmid, STE_S2T0SZ s2t0sz, STE_S2SL0 s2sl0, STE_S2IR0 s2ir0, STE_S2OR0 s2or0, STE_S2SH0 s2sh0, STE_S2TG s2tg, STE_S2PS s2ps, STE_S2AA64 s2aa64, STE_S2ENDI s2endi, STE_S2AFFD s2affd, STE_S2PTW s2ptw, STE_S2HD s2hd, STE_S2HA s2ha, STE_S2S s2s, STE_S2R s2r , uint64_t s2ttb);

void VVDRV_qsmmuv3_writeSTE_basic(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb);
void VVDRV_qsmmuv3_writeSTE_basic_vmid(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb, uint32_t vmid);
void VVDRV_qsmmuv3_writeSTE_basic_vmid_el3(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb, uint32_t vmid);

void VVDRV_qsmmuv3_writeSTE_basic_el3(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb);

void VVDRV_qsmmuv3_writeSTE_basic_32bitVA(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb);

void VVDRV_qsmmuv3_writeSTE_basic_v7L(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb);

void VVDRV_qsmmuv3_writeSTE_basic_weak(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb);

void VVDRV_qsmmuv3_writeSTE_basic_weak_WrThru(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb);

void VVDRV_qsmmuv3_writeSTE_data(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb);

void VVDRV_qsmmuv3_writeSTE_invalid(uint64_t ste_base, int ste_index);

void VVDRV_qsmmuv3_writeSTE_bypass(uint64_t ste_base, int ste_index, uint32_t s1vmid, uint64_t s2ttb);

#endif
