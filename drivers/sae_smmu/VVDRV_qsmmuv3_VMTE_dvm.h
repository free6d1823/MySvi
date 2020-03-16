
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

#ifndef __VVDRV_QSMMUV3_VMTE_H__
#define __VVDRV_QSMMUV3_VMTE_H__

#include <stdint.h>
//#include "VVDRV_qsmmuv3_CommonInclude.h"

typedef enum {
  VMTE_TxSZ_32 = 32,
  VMTE_TxSZ_36 = 28,
  VMTE_TxSZ_40 = 24,
  VMTE_TxSZ_44 = 20,
  VMTE_TxSZ_48 = 16
} VMTE_TxSZ;

typedef enum {
  VMTE_SL_4K_2 = 0,
  VMTE_SL_16K_3 = 0,
  VMTE_SL_64K_3 = 0,
  VMTE_SL_4K_1 = 1,
  VMTE_SL_16K_2 = 1,
  VMTE_SL_64K_2 = 1,
  VMTE_SL_4K_0 = 2,
  VMTE_SL_16K_1 = 2,
  VMTE_SL_64K_1 = 2,
} VMTE_SL;

typedef enum {
  VMTE_xR_NC = 0,
  VMTE_xR_WB = 1,
  VMTE_xR_WT = 2,
  VMTE_xR_WBnWA = 3,
} VMTE_xR;

typedef enum {
  VMTE_SHx_NONE = 0,
  VMTE_SHx_OUTER = 2,
  VMTE_SHx_INNER = 3
} VMTE_SHx;

typedef enum {
  VMTE_TG_4K = 0,
  VMTE_TG_16K = 2,
  VMTE_TG_64K = 1
} VMTE_TG;

typedef enum {
  VMTE_PS_32 = 0,
  VMTE_PS_36 = 1,
  VMTE_PS_40 = 2,
  VMTE_PS_42 = 3,
  VMTE_PS_44 = 4,
  VMTE_PS_48 = 5
} VMTE_PS;

typedef enum {
  VMTE_LPAE_AARCH64 = 0,
  VMTE_LPAE_AARCH32 = 1
} VMTE_LPAE;

typedef enum {
  VMTE_ENDI_LITTLE = 0,
  VMTE_ENDI_BIG = 1
} VMTE_ENDI;

typedef enum {
  VMTE_AFFD_ENABLE = 0,
  VMTE_AFFD_DISABLE = 1
} VMTE_AFFD;

typedef enum {
  VMTE_PTW_ANY = 0,
  VMTE_PTW_NO_DEVICE = 1
} VMTE_PTW;

typedef enum {
  VMTE_HTTU_DISABLED = 0,
  VMTE_HTTU_ACCESS_ONLY = 2,
  VMTE_HTTU_ACCESS_DIRTY = 3
} VMTE_HTTU;

typedef enum {
  VMTE_INVALID = 0,
  VMTE_VALID = 1
} VMTE_V;

void VVDRV_qsmmuv3_writeVMTE_full(uint64_t vmte_base, int vmte_index, VMTE_TxSZ t0sz, VMTE_SL sl0, VMTE_xR ir0, VMTE_xR or0, VMTE_SHx sh0, VMTE_TG tg, VMTE_PS ps, VMTE_LPAE lpae, VMTE_ENDI endi, VMTE_AFFD affd, VMTE_PTW ptw, VMTE_HTTU httu, VMTE_V v, uint64_t ttb, uint32_t vmid);

void VVDRV_qsmmuv3_writeVMTE_basic(uint64_t vmte_base, int vmte_index, VMTE_TxSZ t0sz, VMTE_SL sl0, VMTE_TG tg, uint64_t ttb);

void VVDRV_qsmmuv3_writeVMTE_invalid(uint64_t vmte_base, int vmte_index);
#endif