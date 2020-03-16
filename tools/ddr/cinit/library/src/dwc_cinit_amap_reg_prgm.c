//------------------------------------------------------------------------------
//
// Copyright 2019 Synopsys, INC.
//
// This Synopsys IP and all associated documentation are proprietary to
// Synopsys, Inc. and may only be used pursuant to the terms and conditions of a
// written license agreement with Synopsys, Inc. All other use, reproduction,
// modification, or distribution of the Synopsys IP or the associated
// documentation is strictly prohibited.
//
// Component Name   : DWC_ddrctl
// Component Version: 1.00a-ea06
// Release Type     : EA
//------------------------------------------------------------------------------


/**
 *
 * @detail The purpose of the functions in this file are to take the setting passed in structures in SubsysHdlr_t
 * and apply them to each of the registers in the controller memory map.
 * After each function is called a 32-bit value is ready to be written into the controller register map.
 * No APB bus cycles are actually executed by calling this methods.
 *
 */
#include <assert.h>
#include "dwc_cinit.h"
#include "bit_macros.h"


/** @brief iterate through all DDRC registers setting up a 32-bit value to
 * be programmed into each writable register. 
 */
void cinit_prgm_amap_regs(SubsysHdlr_t *hdlr) {
  TRACE();

  /* ADDRMAP0 and ADDRMAP12 not required amap=1 */ 
  cinit_prgm_ADDRMAP0(hdlr);
  cinit_prgm_ADDRMAP12(hdlr);
  
  for(uint32_t amap=0; amap<hdlr->num_amap; amap++) {
    cinit_prgm_ADDRMAP1(hdlr, amap);
    cinit_prgm_ADDRMAP2(hdlr, amap);
    cinit_prgm_ADDRMAP3(hdlr, amap);
    cinit_prgm_ADDRMAP4(hdlr, amap);
    cinit_prgm_ADDRMAP5(hdlr, amap);
    cinit_prgm_ADDRMAP6(hdlr, amap);
    cinit_prgm_ADDRMAP7(hdlr, amap);
    cinit_prgm_ADDRMAP8(hdlr, amap);
    cinit_prgm_ADDRMAP9(hdlr, amap);
    cinit_prgm_ADDRMAP10(hdlr, amap);
    cinit_prgm_ADDRMAP11(hdlr, amap);
  }
}

void cinit_prgm_ADDRMAP0 (SubsysHdlr_t *hdlr) { 
  TRACE();
#ifdef UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1 
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP0, _MAP) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTR(0,REGB_ADDR, ADDRMAP0, reg, _MAP)
  DWC_DDRCTL_CAST_REG_DCHC_MUX(0, REGB_ADDR, ADDRMAP0, reg, _MAP); 

  APPLY_CFG_TO_REGFIELD(cfg,ADDRMAP0 ,addrmap_dch_bit0);

  LOG_MESSAGE(hdlr, 1, ("ADDRMAP0= 0x%x\n",reg->value ));
#endif

}

void cinit_prgm_ADDRMAP1 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
#ifdef MEMC_NUM_RANKS_GT_1
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP1, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP1)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP1, reg, _MAP); 

#ifdef MEMC_NUM_RANKS_GT_8
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP1 ,addrmap_cs_bit3, amap);
  (CONSTRAIN_INSIDE(reg->addrmap_cs_bit3,0, 26) || CONSTRAIN_EQ(reg->addrmap_cs_bit3,31));
#endif
#ifdef MEMC_NUM_RANKS_GT_4
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP1 ,addrmap_cs_bit2 , amap);
  (CONSTRAIN_INSIDE(reg->addrmap_cs_bit2,0, 27) || CONSTRAIN_EQ(reg->addrmap_cs_bit2,31));
#endif
#ifdef MEMC_NUM_RANKS_GT_2
   if (amap==0) {
     APPLY_CFG_TO_REGFIELD(cfg,ADDRMAP1 ,addrmap_cs_bit1);
   } 
#endif // MEMC_NUM_RANKS_GT_2
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP1 ,addrmap_cs_bit0, amap );

  LOG_MESSAGE(hdlr, 1, ("ADDRMAP1[%0d]= 0x%x\n",amap, reg->value ));
#endif 

}

void cinit_prgm_ADDRMAP2 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
#ifdef UMCTL2_CID_WIDTH_GT_0
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP2, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP2)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP2, reg, _MAP); 
#ifdef UMCTL2_CID_WIDTH_GT_1 
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP2 ,addrmap_cid_b1, amap);
#endif // UMCTL2_CID_WIDTH_GT_1
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP2 ,addrmap_cid_b0, amap);

  LOG_MESSAGE(hdlr, 1, ("ADDRMAP2[%0d]= 0x%x\n",amap, reg->value ));
#endif // UMCTL2_CID_WIDTH_GT_0

}

void cinit_prgm_ADDRMAP3 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP3, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP3)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP3, reg, _MAP); 

#ifdef DDRCTL_LPDDR
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP3 ,addrmap_bank_b2, amap);
#endif
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP3 ,addrmap_bank_b1, amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP3 ,addrmap_bank_b0, amap);


  LOG_MESSAGE(hdlr, 1, ("ADDRMAP3[%0d]= 0x%x\n",amap, reg->value ));

}


void cinit_prgm_ADDRMAP4 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP4, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP4)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP4, reg, _MAP); 

#ifdef DDRCTL_DDR
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP4 ,addrmap_bg_b2 , amap);
#endif
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP4 ,addrmap_bg_b1 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP4 ,addrmap_bg_b0  , amap);


  LOG_MESSAGE(hdlr, 1, ("ADDRMAP4[%0d]= 0x%x\n",amap, reg->value ));

}

void cinit_prgm_ADDRMAP5 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP5, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP5)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP5, reg, _MAP); 

  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP5 ,addrmap_col_b10 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP5 ,addrmap_col_b9  , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP5 ,addrmap_col_b8 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP5 ,addrmap_col_b7 , amap);


  LOG_MESSAGE(hdlr, 1, ("ADDRMAP5[%0d]= 0x%x\n",amap, reg->value ));

}

void cinit_prgm_ADDRMAP6 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP6, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP6)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP6, reg, _MAP); 

  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP6 ,addrmap_col_b6 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP6 ,addrmap_col_b5  , amap);
  CONSTRAIN_MAX(reg->addrmap_col_b5 , 0xf);

  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP6 ,addrmap_col_b4 , amap);
  CONSTRAIN_MAX(reg->addrmap_col_b4 , 0xf);

  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP6 ,addrmap_col_b3 , amap);
  CONSTRAIN_MAX(reg->addrmap_col_b3 , 0xf);

  LOG_MESSAGE(hdlr, 1, ("ADDRMAP6[%0d]= 0x%x\n",amap, reg->value ));

}

void cinit_prgm_ADDRMAP7 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP7, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP7)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP7, reg, _MAP); 

  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP7 ,addrmap_row_b17 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP7 ,addrmap_row_b16 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP7 ,addrmap_row_b15 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP7 ,addrmap_row_b14 , amap);

  LOG_MESSAGE(hdlr, 1, ("ADDRMAP7[%0d]= 0x%x\n",amap, reg->value ));
}

void cinit_prgm_ADDRMAP8 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP8, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP8)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP8, reg, _MAP); 

  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP8 ,addrmap_row_b13 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP8 ,addrmap_row_b12 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP8 ,addrmap_row_b11 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP8 ,addrmap_row_b10 , amap);
  LOG_MESSAGE(hdlr, 1, ("ADDRMAP8[%0d]= 0x%x\n",amap, reg->value ));

}


void cinit_prgm_ADDRMAP9 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP9, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP9)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP9, reg, _MAP); 

  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP9 , addrmap_row_b9, amap);
  CONSTRAIN_MAX(reg->addrmap_row_b9 , 0x1f);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP9 , addrmap_row_b8, amap);
  CONSTRAIN_MAX(reg->addrmap_row_b8 , 0x1f);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP9 , addrmap_row_b7, amap);
  CONSTRAIN_MAX(reg->addrmap_row_b7 , 0x1f);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP9 , addrmap_row_b6, amap);
  CONSTRAIN_MAX(reg->addrmap_row_b6 , 0x1f);


  LOG_MESSAGE(hdlr, 1, ("ADDRMAP9[%0d]= 0x%x\n",amap, reg->value ));

}

void cinit_prgm_ADDRMAP10 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP10, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP10)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP10, reg, _MAP); 

  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP10 , addrmap_row_b5, amap);
  CONSTRAIN_MAX(reg->addrmap_row_b5 , 0x1f);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP10 , addrmap_row_b4, amap);
  CONSTRAIN_MAX(reg->addrmap_row_b4 , 0x1f);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP10 , addrmap_row_b3, amap);
  CONSTRAIN_MAX(reg->addrmap_row_b3 , 0x1f);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP10 , addrmap_row_b2, amap);
  CONSTRAIN_MAX(reg->addrmap_row_b2 , 0x1f);

  LOG_MESSAGE(hdlr, 1, ("ADDRMAP10[%0d]= 0x%x\n",amap, reg->value ));

}


void cinit_prgm_ADDRMAP11 (SubsysHdlr_t *hdlr, uint32_t amap) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP11, _MAP) * reg;
  DWC_DDRCTL_DECLARE_AMAP_REG_PTRS(REGB_ADDR, ADDRMAP11)
  DWC_DDRCTL_CAST_REG_AMAP(amap, REGB_ADDR, ADDRMAP11, reg, _MAP); 


  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP11 ,addrmap_row_b1 , amap);
  APPLY_CFG_TO_REGFIELD_P(cfg,ADDRMAP11 ,addrmap_row_b0 , amap);

  LOG_MESSAGE(hdlr, 1, ("ADDRMAP11[%0d]= 0x%x\n",amap, reg->value ));

}

void cinit_prgm_ADDRMAP12 (SubsysHdlr_t *hdlr) {
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_ADDR, ADDRMAP12, _MAP) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTR(0, REGB_ADDR, ADDRMAP12, reg, _MAP)
  DWC_DDRCTL_CAST_REG_DCHC_MUX(0, REGB_ADDR, ADDRMAP12, reg, _MAP); 

  APPLY_CFG_TO_REGFIELD(cfg,ADDRMAP12 ,nonbinary_device_density);

  LOG_MESSAGE(hdlr, 1, ("ADDRMAP12= 0x%x\n",reg->value ));
}
