
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

//#include "vv_msg_file_number_def.h"
#include "VVDRV_qsmmuv3_VMTE_dvm.h"
//#include <HALhwio.h>
#include "asm/hal/HALhwio.h"
#define VV_MSG_FILE_NUMBER DRV_QSMMUV3_FILE_NUM_7
//#define outp64(port, val) (*((volatile uint64_t *) (port)) = ((uint64_t) (val)))
void VVDRV_qsmmuv3_writeVMTE_full(uint64_t vmte_base, int vmte_index, VMTE_TxSZ t0sz, VMTE_SL sl0, VMTE_xR ir0, VMTE_xR or0, VMTE_SHx sh0, VMTE_TG tg, VMTE_PS ps, VMTE_LPAE lpae, VMTE_ENDI endi, VMTE_AFFD affd, VMTE_PTW ptw, VMTE_HTTU httu, VMTE_V v, uint64_t ttb, uint32_t vmid) {
  uint64_t vmte_addr;
  uint64_t vmte_data0;
  uint64_t vmte_data1;

  vmte_addr = vmte_base + (vmte_index << 5);

  vmte_data0 = ((uint32_t)v << 31) + (httu << 29) + (ptw << 27) + (affd << 26) + (endi << 20) + (lpae << 19) + (ps << 16) + (tg << 14) + (sh0 << 12) + (or0 << 10) + (ir0 << 8) + (sl0 << 6) + (t0sz);

  vmte_data1 = ((uint64_t)vmid << 48) + (ttb);

  outp64(vmte_addr, vmte_data0);
  vmte_addr += 0x08;
  outp64(vmte_addr, vmte_data1);
  vmte_addr += 0x08;
  outp64(vmte_addr, 0x0000000000000000);
  vmte_addr += 0x08;
  outp64(vmte_addr, 0x0000000000000000);

  return;
}

void VVDRV_qsmmuv3_writeVMTE_basic(uint64_t vmte_base, int vmte_index, VMTE_TxSZ t0sz, VMTE_SL sl0, VMTE_TG tg, uint64_t ttb) {

  VVDRV_qsmmuv3_writeVMTE_full(vmte_base, vmte_index, t0sz, sl0, VMTE_xR_NC, VMTE_xR_NC, VMTE_SHx_OUTER, tg, VMTE_PS_48, VMTE_LPAE_AARCH64, VMTE_ENDI_LITTLE, VMTE_AFFD_DISABLE, VMTE_PTW_ANY, VMTE_HTTU_DISABLED, VMTE_VALID, ttb, 0x0);

  return;
}

void VVDRV_qsmmuv3_writeVMTE_invalid(uint64_t vmte_base, int vmte_index) {

  VVDRV_qsmmuv3_writeVMTE_full(vmte_base, vmte_index, VMTE_TxSZ_48, VMTE_SL_4K_2, VMTE_xR_NC, VMTE_xR_NC, VMTE_SHx_NONE, VMTE_TG_4K, VMTE_PS_32, VMTE_LPAE_AARCH64, VMTE_ENDI_LITTLE, VMTE_AFFD_DISABLE, VMTE_PTW_ANY, VMTE_HTTU_DISABLED, VMTE_INVALID, 0x0, 0x0);

  return;
}
