
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
#include "VVDRV_qsmmuv3_STE_dvm.h"

#define VV_MSG_FILE_NUMBER DRV_QSMMUV3_FILE_NUM_6
#define outp64(port, val) (*((volatile uint64_t *) (port)) = ((uint64_t) (val)))
void VVDRV_qsmmuv3_writeSTE_full(uint64_t ste_base, int ste_index, STE_V v, STE_Type config, STE_S1Fmt s1fmt, uint64_t s1contextptr, int cdmax, STE_DSS dss, STE_CxR cir, STE_CxR cor, STE_CSH csh, int cont, STE_PPAR ppar, STE_MEV mev, STE_StallD stalld, STE_EATS eats, STE_STRW strw, STE_MemAttr memattr, int mtcfg, STE_AllocCfg alloccfg, STE_ShCfg shcfg, STE_NSCfg nscfg, STE_PrivCfg privcfg, STE_InstCfg instcfg, int s2vmid, STE_S2T0SZ s2t0sz, STE_S2SL0 s2sl0, STE_S2IR0 s2ir0, STE_S2OR0 s2or0, STE_S2SH0 s2sh0, STE_S2TG s2tg, STE_S2PS s2ps, STE_S2AA64 s2aa64, STE_S2ENDI s2endi, STE_S2AFFD s2affd, STE_S2PTW s2ptw, STE_S2HD s2hd, STE_S2HA s2ha, STE_S2S s2s, STE_S2R s2r , uint64_t s2ttb) {
  uint64_t ste_addr;
  uint64_t ste_data0;
  uint64_t ste_data1;
  uint64_t ste_data2;
  uint64_t ste_data3;

  ste_addr = ste_base + ((uint64_t)ste_index << 6);

  ste_data0 = ((uint64_t)cdmax << 59) + ((uint64_t)s1contextptr) + ((uint64_t)s1fmt << 4) +((uint64_t)config << 1) + (v);

  ste_data1 =  ((uint64_t)instcfg << 50) + ((uint64_t)privcfg << 48) + ((uint64_t)nscfg << 46) + ((uint64_t)shcfg << 44) + ((uint64_t)alloccfg << 37) + ((uint64_t)mtcfg << 36) + ((uint64_t)memattr << 32) + ((uint64_t)strw << 30) + ((uint64_t)eats << 28 ) +((uint64_t)stalld << 27 ) + ((uint64_t)mev << 19) + ((uint64_t)ppar << 18) + ((uint64_t)cont << 13) + ((uint64_t)csh << 6) + ((uint64_t)cor << 4) + ((uint64_t)cir << 2) + ((uint64_t)dss);

  ste_data2 = ((uint64_t)s2r << 58) + ((uint64_t)s2s << 57) + ((uint64_t)s2ha << 56) + ((uint64_t)s2hd << 55) + ((uint64_t)s2ptw << 54) + ((uint64_t)s2affd << 53) + ((uint64_t)s2endi << 52) + ((uint64_t)s2aa64 << 51) + ((uint64_t)s2ps<< 48) + ((uint64_t)s2tg << 46) + ((uint64_t)s2sh0 << 44) + ((uint64_t)s2or0 << 42) + ((uint64_t)s2ir0 << 40) + ((uint64_t)s2sl0 << 38) + ((uint64_t)s2t0sz << 32) + ((uint64_t)s2vmid);

  ste_data3 = ( ( (uint64_t)s2ttb >> 4)  << 4 );

  outp64(ste_addr, ste_data0);
  ste_addr += 0x08;
  outp64(ste_addr, ste_data1);
  ste_addr += 0x08;
  outp64(ste_addr, ste_data2);
  ste_addr += 0x08;
  outp64(ste_addr, ste_data3);
  ste_addr += 0x08;
  outp64(ste_addr, 0x0000000000000000);
  ste_addr += 0x08;
  outp64(ste_addr, 0x0000000000000000);
  ste_addr += 0x08;
  outp64(ste_addr, 0x0000000000000000);
  ste_addr += 0x08;
  outp64(ste_addr, 0x0000000000000000);

  return;
}

void VVDRV_qsmmuv3_writeSTE_basic(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb) {

int       mtcfg = (config == STE_TYPE_STAGE2) ? 1 : 0;
STE_NSCfg nscfg = (config == STE_TYPE_STAGE2) ? STE_NSCFG_NONSECURE : STE_NSCFG_INCOMING;

  	VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, STE_VALID, config, STE_S1FMT_LINEAR, s1contextptr, 0, STE_DSS_DISABLED, STE_CxR_NC, STE_CxR_NC, STE_CSH_OUTER, 0, STE_PPAR_NO_PASID_TLP, STE_MEV_OFF, STE_STALLD_STALL, STE_EATS_TERMINATE, STE_STRW_NS_EL1, STE_MEMATTR_NORMAL_WB, mtcfg, STE_ALLOCCFG_RA_WA, STE_SHCFG_INCOMING, nscfg, STE_PRIVCFG_INCOMING, STE_INSTCFG_INCOMING, 0, STE_S2T0SZ_44, STE_S2SL0_4KL0_L1,  STE_S2IR0_NC, STE_S2OR0_NC,  STE_S2SH0_OS, STE_S2TG_4K, STE_S2PS_48BITS ,STE_S2AA64_AARCH64, STE_S2ENDI_LITTLE, STE_S2AFFD_FAULT, STE_S2PTW_PROTECT_OFF, STE_S2HD_DISABLE, STE_S2HA_DISABLE, STE_S2S_OFF, STE_S2R_ON, s2ttb);

  	return;
}
void VVDRV_qsmmuv3_writeSTE_basic_vmid(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb,uint32_t vmid) {

int       mtcfg = (config == STE_TYPE_STAGE2) ? 1 : 0;
STE_NSCfg nscfg = (config == STE_TYPE_STAGE2) ? STE_NSCFG_NONSECURE : STE_NSCFG_INCOMING;

  	VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, STE_VALID, config, STE_S1FMT_LINEAR, s1contextptr, 0, STE_DSS_DISABLED, STE_CxR_NC, STE_CxR_NC, STE_CSH_OUTER, 0, STE_PPAR_NO_PASID_TLP, STE_MEV_OFF, STE_STALLD_STALL, STE_EATS_TERMINATE, STE_STRW_NS_EL1, STE_MEMATTR_NORMAL_WB, mtcfg, STE_ALLOCCFG_RA_WA, STE_SHCFG_INCOMING, nscfg, STE_PRIVCFG_INCOMING, STE_INSTCFG_INCOMING, vmid, STE_S2T0SZ_44, STE_S2SL0_4KL0_L1,  STE_S2IR0_NC, STE_S2OR0_NC,  STE_S2SH0_OS, STE_S2TG_4K, STE_S2PS_48BITS ,STE_S2AA64_AARCH64, STE_S2ENDI_LITTLE, STE_S2AFFD_FAULT, STE_S2PTW_PROTECT_OFF, STE_S2HD_DISABLE, STE_S2HA_DISABLE, STE_S2S_OFF, STE_S2R_ON, s2ttb);

  	return;
}

void VVDRV_qsmmuv3_writeSTE_basic_vmid_el3(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb,uint32_t vmid) {

int       mtcfg = (config == STE_TYPE_STAGE2) ? 1 : 0;
STE_NSCfg nscfg = (config == STE_TYPE_STAGE2) ? STE_NSCFG_NONSECURE : STE_NSCFG_INCOMING;

  	VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, STE_VALID, config, STE_S1FMT_LINEAR, s1contextptr, 0, STE_DSS_DISABLED, STE_CxR_NC, STE_CxR_NC, STE_CSH_OUTER, 0, STE_PPAR_NO_PASID_TLP, STE_MEV_OFF, STE_STALLD_STALL, STE_EATS_TERMINATE, STE_STRW_EL3, STE_MEMATTR_NORMAL_WB, mtcfg, STE_ALLOCCFG_RA_WA, STE_SHCFG_INCOMING, nscfg, STE_PRIVCFG_INCOMING, STE_INSTCFG_INCOMING, vmid, STE_S2T0SZ_44, STE_S2SL0_4KL0_L1,  STE_S2IR0_NC, STE_S2OR0_NC,  STE_S2SH0_OS, STE_S2TG_4K, STE_S2PS_48BITS ,STE_S2AA64_AARCH64, STE_S2ENDI_LITTLE, STE_S2AFFD_FAULT, STE_S2PTW_PROTECT_OFF, STE_S2HD_DISABLE, STE_S2HA_DISABLE, STE_S2S_OFF, STE_S2R_ON, s2ttb);

  	return;
}

void VVDRV_qsmmuv3_writeSTE_basic_el3(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb) {

int       mtcfg = (config == STE_TYPE_STAGE2) ? 1 : 0;
STE_NSCfg nscfg = (config == STE_TYPE_STAGE2) ? STE_NSCFG_NONSECURE : STE_NSCFG_INCOMING;

  	VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, STE_VALID, config, STE_S1FMT_LINEAR, s1contextptr, 0, STE_DSS_DISABLED, STE_CxR_NC, STE_CxR_NC, STE_CSH_OUTER, 0, STE_PPAR_NO_PASID_TLP, STE_MEV_OFF, STE_STALLD_STALL, STE_EATS_TERMINATE, STE_STRW_EL3, STE_MEMATTR_NORMAL_WB, mtcfg, STE_ALLOCCFG_RA_WA, STE_SHCFG_INCOMING, nscfg, STE_PRIVCFG_INCOMING, STE_INSTCFG_INCOMING, 0, STE_S2T0SZ_44, STE_S2SL0_4KL0_L1,  STE_S2IR0_NC, STE_S2OR0_NC,  STE_S2SH0_OS, STE_S2TG_4K, STE_S2PS_48BITS ,STE_S2AA64_AARCH64, STE_S2ENDI_LITTLE, STE_S2AFFD_FAULT, STE_S2PTW_PROTECT_OFF, STE_S2HD_DISABLE, STE_S2HA_DISABLE, STE_S2S_OFF, STE_S2R_ON, s2ttb);

  	return;
}

void VVDRV_qsmmuv3_writeSTE_basic_32bitVA(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb) {

int       mtcfg = (config == STE_TYPE_STAGE2) ? 1 : 0;
STE_NSCfg nscfg = (config == STE_TYPE_STAGE2) ? STE_NSCFG_NONSECURE : STE_NSCFG_INCOMING;

  	VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, STE_VALID, config, STE_S1FMT_LINEAR, s1contextptr, 0, STE_DSS_DISABLED, STE_CxR_NC, STE_CxR_NC, STE_CSH_OUTER, 0, STE_PPAR_NO_PASID_TLP, STE_MEV_OFF, STE_STALLD_STALL, STE_EATS_TERMINATE, STE_STRW_NS_EL1, STE_MEMATTR_NORMAL_WB, mtcfg, STE_ALLOCCFG_RA_WA, STE_SHCFG_INCOMING, nscfg, STE_PRIVCFG_INCOMING, STE_INSTCFG_INCOMING, 0, STE_S2T0SZ_32, STE_S2SL0_4KL1_L2,  STE_S2IR0_NC, STE_S2OR0_NC,  STE_S2SH0_OS, STE_S2TG_4K, STE_S2PS_48BITS ,STE_S2AA64_AARCH64, STE_S2ENDI_LITTLE, STE_S2AFFD_FAULT, STE_S2PTW_PROTECT_OFF, STE_S2HD_DISABLE, STE_S2HA_DISABLE, STE_S2S_OFF, STE_S2R_ON, s2ttb);

  	return;
}
void VVDRV_qsmmuv3_writeSTE_basic_v7L(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb) {

  return;
}
void VVDRV_qsmmuv3_writeSTE_basic_weak(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb) {

  return;
}
void VVDRV_qsmmuv3_writeSTE_basic_weak_WrThru(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb) {

  return;
}
void VVDRV_qsmmuv3_writeSTE_data(uint64_t ste_base, int ste_index, STE_Type config, uint64_t s1contextptr, uint64_t s2ttb) {
VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, STE_VALID, config, STE_S1FMT_LINEAR, s1contextptr, 0, STE_DSS_DISABLED, STE_CxR_NC, STE_CxR_NC, STE_CSH_OUTER, 0, STE_PPAR_NO_PASID_TLP, STE_MEV_OFF, STE_STALLD_STALL, STE_EATS_TERMINATE, STE_STRW_NS_EL1, STE_MEMATTR_DEVICE_nGnRnE, 0, STE_ALLOCCFG_INCOMING, STE_SHCFG_INCOMING, STE_NSCFG_INCOMING, STE_PRIVCFG_INCOMING, STE_INSTCFG_DATA, 0, 0, STE_S2SL0_4KL0_L1,  STE_S2IR0_NC, STE_S2OR0_NC,  STE_S2SH0_OS, STE_S2TG_4K, STE_S2PS_48BITS ,STE_S2AA64_AARCH64, STE_S2ENDI_LITTLE, STE_S2AFFD_FAULT, STE_S2PTW_PROTECT_OFF, STE_S2HD_DISABLE, STE_S2HA_DISABLE, STE_S2S_OFF, STE_S2R_OFF, 0);

  return;
}

void VVDRV_qsmmuv3_writeSTE_invalid(uint64_t ste_base, int ste_index) {

  VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, STE_INVALID, 0, STE_S1FMT_LINEAR, 0, 0, STE_DSS_DISABLED, STE_CxR_NC, STE_CxR_NC, STE_CSH_OUTER, 0, STE_PPAR_NO_PASID_TLP, STE_MEV_OFF, STE_STALLD_STALL, STE_EATS_TERMINATE, STE_STRW_NS_EL1, STE_MEMATTR_DEVICE_nGnRnE, 1, STE_ALLOCCFG_INCOMING, STE_SHCFG_INCOMING, STE_NSCFG_INCOMING, STE_PRIVCFG_INCOMING, STE_INSTCFG_INCOMING, 0, 0, STE_S2SL0_4KL0_L1,  STE_S2IR0_NC, STE_S2OR0_NC,  STE_S2SH0_OS, STE_S2TG_4K, STE_S2PS_48BITS ,STE_S2AA64_AARCH64, STE_S2ENDI_LITTLE, STE_S2AFFD_FAULT, STE_S2PTW_PROTECT_OFF, STE_S2HD_DISABLE, STE_S2HA_DISABLE, STE_S2S_OFF, STE_S2R_ON, 0);

  return;
}

void VVDRV_qsmmuv3_writeSTE_bypass(uint64_t ste_base, int ste_index, uint32_t s1vmid, uint64_t s2ttb) {

  VVDRV_qsmmuv3_writeSTE_full(ste_base, ste_index, STE_VALID, STE_TYPE_BYPASS, STE_S1FMT_LINEAR, 0, 0, STE_DSS_DISABLED, STE_CxR_NC, STE_CxR_NC, STE_CSH_OUTER, 0, STE_PPAR_NO_PASID_TLP, STE_MEV_OFF, STE_STALLD_STALL, STE_EATS_TERMINATE, STE_STRW_NS_EL1, STE_MEMATTR_DEVICE_nGnRnE, 1, STE_ALLOCCFG_INCOMING, STE_SHCFG_INCOMING, STE_NSCFG_INCOMING, STE_PRIVCFG_INCOMING, STE_INSTCFG_INCOMING, 0, 0, STE_S2SL0_4KL0_L1,  STE_S2IR0_NC, STE_S2OR0_NC,  STE_S2SH0_OS, STE_S2TG_4K, STE_S2PS_48BITS ,STE_S2AA64_AARCH64, STE_S2ENDI_LITTLE, STE_S2AFFD_FAULT, STE_S2PTW_PROTECT_OFF, STE_S2HD_DISABLE, STE_S2HA_DISABLE, STE_S2S_OFF, STE_S2R_ON, s2ttb);

  return;
}
