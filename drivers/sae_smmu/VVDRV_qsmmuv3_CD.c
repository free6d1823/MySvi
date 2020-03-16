
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
#include "VVDRV_qsmmuv3_CD_dvm.h"

#define VV_MSG_FILE_NUMBER DRV_QSMMUV3_FILE_NUM_1
#define outp64(port, val) (*((volatile uint64_t *) (port)) = ((uint64_t) (val)))
void VVDRV_qsmmuv3_writeCD_full(uint64_t cd_base, int cd_index, CD_TxSZ t0sz, CD_TG0 tg0, CD_xR ir0, CD_xR or0, CD_SHx sh0, CD_EPDx epd0, CD_ENDI endi, CD_TxSZ t1sz, CD_TG1 tg1, CD_xR ir1, CD_xR or1, CD_SHx sh1, CD_EPDx epd1, CD_V v, CD_IPS ips, CD_AFFD affd, CD_WXN wxn, CD_UWXN uwxn, CD_TBI tbi0, CD_TBI tbi1, int pan, CD_AA64 aa64, CD_HD hd, CD_HA ha, CD_ARS ars, CD_ASET aset, int asid, CD_NSCFGx nscfg0, CD_HADx had0, uint64_t ttb0, CD_NSCFGx nscfg1, CD_HADx had1, uint64_t ttb1, CD_MAIR mair0, CD_MAIR mair1, CD_MAIR mair2, CD_MAIR mair3, CD_MAIR mair4, CD_MAIR mair5, CD_MAIR mair6, CD_MAIR mair7) {
  uint64_t cd_addr;
  uint64_t cd_data0;
  uint64_t cd_data1;
  uint64_t cd_data2;
  uint64_t cd_data3;

  cd_addr = cd_base + (cd_index << 6);

  cd_data0 = ((uint64_t)asid << 48) + ((uint64_t)aset << 47) + ((uint64_t)ars << 44) + ((uint64_t)ha << 43) + ((uint64_t)hd << 42) + ((uint64_t)aa64 << 41) + ((uint64_t)pan << 40) + ((uint64_t) tbi1 << 39) + ((uint64_t)tbi0 << 38) + ((uint64_t) uwxn << 37) + ((uint64_t) wxn << 36) + ((uint64_t)affd << 35) + ((uint64_t)ips << 32) + ((uint32_t)v << 31) + (epd1 << 30) + (sh1 << 28) + (or1 << 26) + (ir1 << 24) + (tg1 << 22) + (t1sz << 16) + (endi << 15) + (epd0 << 14) + (sh0 << 12) + (or0 << 10) + (ir0 << 8) + (tg0 << 6) + (t0sz);

  cd_data1 = (ttb0) + (had0 << 1) + (nscfg0);

  cd_data2 = (ttb1) + (had1 << 1) + (nscfg1);

  cd_data3 = ((uint64_t)mair7 << 56) + ((uint64_t)mair6 << 48) + ((uint64_t)mair5 << 40) + ((uint64_t)mair4 << 32) + ((uint32_t)mair3 << 24) + (mair2 << 16) + (mair1 << 8) + (mair0);

  outp64(cd_addr, cd_data0);
  cd_addr += 0x08;
  outp64(cd_addr, cd_data1);
  cd_addr += 0x08;
  outp64(cd_addr, cd_data2);
  cd_addr += 0x08;
  outp64(cd_addr, cd_data3);
  cd_addr += 0x08;
  outp64(cd_addr, 0x0000000000000000);
  cd_addr += 0x08;
  outp64(cd_addr, 0x0000000000000000);
  cd_addr += 0x08;
  outp64(cd_addr, 0x0000000000000000);
  cd_addr += 0x08;
  outp64(cd_addr, 0x0000000000000000);

  return;
}

void VVDRV_qsmmuv3_writeCD_basic(uint64_t cd_base, int cd_index, CD_TxSZ t0sz, CD_TG0 tg0, CD_NSCFGx nscfg0, uint64_t ttb0) {

  VVDRV_qsmmuv3_writeCD_full(cd_base, cd_index, t0sz, tg0, CD_xR_NC, CD_xR_NC, CD_SHx_OUTER, CD_EPDx_ENABLE, CD_ENDI_LITTLE, CD_TxSZ_48, CD_TG1_64K, CD_xR_NC, CD_xR_NC, CD_SHx_OUTER, CD_EPDx_DISABLE, CD_VALID, CD_IPS_44, CD_AFFD_DISABLE,CD_WXN_OFF, CD_UWXN_OFF, CD_TBI_ON, CD_TBI_ON,  0, CD_AA64_64, CD_HD_OFF, CD_HA_OFF, CD_ARS_ABORT_RECORD, CD_ASET_SHARED, 0, nscfg0, CD_HAD_ENABLED, ttb0, CD_NSCFG_NONSECURE, CD_HAD_DISABLED, 0, CD_MAIR_DEVICE_nGnRnE, CD_MAIR_DEVICE_nGnRE, CD_MAIR_DEVICE_nGRE, CD_MAIR_DEVICE_GRE, CD_MAIR_NORMAL_NC, CD_MAIR_NORMAL_WTNT_RAWA, CD_MAIR_NORMAL_WBNT_RA, CD_MAIR_NORMAL_WBNT_RAWA);

  return;
}

void VVDRV_qsmmuv3_writeCD_invalid(uint64_t cd_base, int cd_index) {

  VVDRV_qsmmuv3_writeCD_full(cd_base, cd_index, CD_TxSZ_32, CD_TG0_4K, CD_xR_NC, CD_xR_NC, CD_SHx_NONE, CD_EPDx_ENABLE, CD_ENDI_LITTLE, CD_TxSZ_32, CD_TG1_16K, CD_xR_NC, CD_xR_NC, CD_SHx_NONE, CD_EPDx_ENABLE, CD_INVALID, CD_IPS_32, CD_AFFD_ENABLE, CD_WXN_OFF, CD_UWXN_OFF, CD_TBI_ON, CD_TBI_ON, 0, CD_AA64_64, CD_HD_OFF, CD_HA_OFF, CD_ARS_ABORT_RECORD, CD_ASET_SHARED, 0, CD_NSCFG_SECURE, CD_HAD_ENABLED, 0, CD_NSCFG_SECURE, CD_HAD_ENABLED, 0, CD_MAIR_DEVICE_nGnRnE, CD_MAIR_DEVICE_nGnRnE, CD_MAIR_DEVICE_nGnRnE, CD_MAIR_DEVICE_nGnRnE, CD_MAIR_DEVICE_nGnRnE, CD_MAIR_DEVICE_nGnRnE, CD_MAIR_DEVICE_nGnRnE, CD_MAIR_DEVICE_nGnRnE);

  return;
}
