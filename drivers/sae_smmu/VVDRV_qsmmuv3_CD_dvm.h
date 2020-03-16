
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

#ifndef __VVDRV_QSMMUV3_CD_H__
#define __VVDRV_QSMMUV3_CD_H__

//#include "VVDRV_qsmmuv3_CommonInclude.h"
#include <stdint.h>
typedef enum {
  CD_TxSZ_32 = 32,
  CD_TxSZ_36 = 28,
  CD_TxSZ_40 = 24,
  CD_TxSZ_44 = 20,
  CD_TxSZ_48 = 16,
  CD_TxSZ_v7L_32 = 0
} CD_TxSZ;

typedef enum {
  CD_TG0_4K = 0,
  CD_TG0_16K = 2,
  CD_TG0_64K = 1
} CD_TG0;

typedef enum {
  CD_xR_NC = 0,
  CD_xR_WB = 1,
  CD_xR_WT = 2,
  CD_xR_WBnWA = 3,
} CD_xR;

typedef enum {
  CD_SHx_NONE = 0,
  CD_SHx_OUTER = 2,
  CD_SHx_INNER = 3
} CD_SHx;

typedef enum {
  CD_EPDx_ENABLE = 0,
  CD_EPDx_DISABLE = 1
} CD_EPDx;

typedef enum {
  CD_ENDI_LITTLE = 0,
  CD_ENDI_BIG = 1
} CD_ENDI;

typedef enum {
  CD_TG1_4K = 2,
  CD_TG1_16K = 1,
  CD_TG1_64K = 3
} CD_TG1;

typedef enum {
  CD_INVALID = 0,
  CD_VALID = 1
} CD_V;

typedef enum {
  CD_IPS_32 = 0,
  CD_IPS_36 = 1,
  CD_IPS_40 = 2,
  CD_IPS_42 = 3,
  CD_IPS_44 = 4,
  CD_IPS_48 = 5
} CD_IPS;

typedef enum {
  CD_AFFD_ENABLE = 0,
  CD_AFFD_DISABLE = 1
} CD_AFFD;

typedef enum {
  CD_WXN_OFF = 0,
  CD_WXN_ON = 1
} CD_WXN;

typedef enum {
  CD_UWXN_OFF = 0,
  CD_UWXN_ON = 1
} CD_UWXN;

typedef enum {
  CD_TBI_OFF = 0,
  CD_TBI_ON = 1
} CD_TBI;

typedef enum {
  CD_AA64_32 = 0, 
  CD_AA64_64 = 1
} CD_AA64;

typedef enum {
  CD_HD_OFF = 0,
  CD_HD_ON = 1
} CD_HD;

typedef enum {
  CD_HA_OFF = 0,
  CD_HA_ON = 1
} CD_HA;

typedef enum {
  CD_ARS_TERM_SILENT = 0,
  CD_ARS_TERM_RECORD = 2,
  CD_ARS_STALL_SILENT = 1,
  CD_ARS_STALL_RECORD = 3,
  CD_ARS_STALL_ABORT_SILENT = 5,
  CD_ARS_STALL_ABORT_RECORD = 7,
  CD_ARS_ABORT_SILENT = 4,
  CD_ARS_ABORT_RECORD = 6
} CD_ARS;

typedef enum {
  CD_ASET_SHARED = 0,
  CD_ASET_NONSHARED = 1
} CD_ASET;

typedef enum {
  CD_NSCFG_SECURE = 0,
  CD_NSCFG_NONSECURE = 1
} CD_NSCFGx;

typedef enum {
  CD_HAD_ENABLED = 0,
  CD_HAD_DISABLED = 1
} CD_HADx;

typedef enum {
  CD_MAIR_DEVICE_nGnRnE = 0x00,
  CD_MAIR_DEVICE_nGnRE = 0x04,
  CD_MAIR_DEVICE_nGRE = 0x08,
  CD_MAIR_DEVICE_GRE = 0x0c,
  CD_MAIR_NORMAL_NC = 0x44,
  CD_MAIR_NORMAL_WTNT_RA   = 0xaa,
  CD_MAIR_NORMAL_WTNT_RAWA = 0xbb,
  CD_MAIR_NORMAL_WBNT      = 0xcc,
  CD_MAIR_NORMAL_WBNT_WA   = 0xdd,
  CD_MAIR_NORMAL_WBNT_RA   = 0xee,
  CD_MAIR_NORMAL_OUT_WBNT_RAWA_IN_NC = 0xf4,
  CD_MAIR_NORMAL_WBNT_RAWA = 0xff
} CD_MAIR;

void VVDRV_qsmmuv3_writeCD_full(uint64_t cd_base, int cd_index, CD_TxSZ t0sz, CD_TG0 tg0, CD_xR ir0, CD_xR or0, CD_SHx sh0, CD_EPDx epd0, CD_ENDI endi, CD_TxSZ t1sz, CD_TG1 tg1, CD_xR ir1, CD_xR or1, CD_SHx sh1, CD_EPDx epd1, CD_V v, CD_IPS ips, CD_AFFD affd, CD_WXN wxn, CD_UWXN uwxn, CD_TBI tbi0, CD_TBI tbi1, int pan, CD_AA64 aa64, CD_HD hd, CD_HA ha, CD_ARS ars, CD_ASET aset, int asid, CD_NSCFGx nscfg0, CD_HADx had0, uint64_t ttb0, CD_NSCFGx nscfg1, CD_HADx had1, uint64_t ttb1, CD_MAIR mair0, CD_MAIR mair1, CD_MAIR mair2, CD_MAIR mair3, CD_MAIR mair4, CD_MAIR mair5, CD_MAIR mair6, CD_MAIR mair7);

void VVDRV_qsmmuv3_writeCD_basic(uint64_t cd_base, int cd_index, CD_TxSZ t0sz, CD_TG0 tg0, CD_NSCFGx nscfg0, uint64_t ttb0);

void VVDRV_qsmmuv3_writeCD_invalid(uint64_t cd_base, int cd_index);
#endif
