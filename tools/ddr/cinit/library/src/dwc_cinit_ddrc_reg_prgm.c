//  ------------------------------------------------------------------------
//
//                    (C) COPYRIGHT 2019 SYNOPSYS, INC.
//                            ALL RIGHTS RESERVED
//
//  This software and the associated documentation are confidential and
//  proprietary to Synopsys, Inc.  Your use or disclosure of this
//  software is subject to the terms and conditions of a written
//  license agreement between you, or your company, and Synopsys, Inc.
//
// The entire notice above must be reproduced on all authorized copies.
//
// Component Name   : DWC_ddrctl
// Component Version: 1.00a-ea00
// Release Type     : EA
//  ------------------------------------------------------------------------


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
void cinit_prgm_ddrc_regs(SubsysHdlr_t *hdlr) {
  TRACE();
  cinit_prgm_MSTR0(hdlr);
  cinit_prgm_MSTR1(hdlr);
  cinit_prgm_MSTR2(hdlr);
  cinit_prgm_DFIMISC(hdlr);
  cinit_prgm_DFIPHYMSTR(hdlr);
  cinit_prgm_RFSHCTL0(hdlr);
  cinit_prgm_RFSHMOD0(hdlr);
  cinit_prgm_RFSHMOD1(hdlr);
  cinit_prgm_ZQCTL0(hdlr);
  cinit_prgm_ZQCTL2(hdlr);
  cinit_prgm_SCHED0(hdlr);
  cinit_prgm_DERATECTL0(hdlr);
  cinit_prgm_DERATECTL1(hdlr);
  cinit_prgm_DERATECTL6(hdlr);
  cinit_prgm_RANKCTL(hdlr);
  cinit_prgm_ECCCFG0(hdlr);
  cinit_prgm_ECCCFG1(hdlr);
  cinit_prgm_ECCPOISONADDR0(hdlr);
  cinit_prgm_ECCPOISONADDR1(hdlr);
  cinit_prgm_ECCPOISONPAT0(hdlr); 
  cinit_prgm_ECCPOISONPAT1(hdlr); 
  cinit_prgm_ECCPOISONPAT2(hdlr);
  cinit_prgm_DIMMCTL(hdlr);
  cinit_prgm_OPCTRL0(hdlr);
  cinit_prgm_HWFFCCTL(hdlr);
  cinit_prgm_ADVECCINDEX (hdlr);
  cinit_prgm_OCPARCFG1 (hdlr);
  cinit_prgm_OCSAPCFG0 (hdlr);
  cinit_prgm_DQSOSCRUNTIME (hdlr);
  cinit_prgm_SCHED1 (hdlr);
  cinit_prgm_SCHED2 (hdlr);
  cinit_prgm_SCHED3 (hdlr);
  cinit_prgm_SCHED4 (hdlr);
  cinit_prgm_SCHED5 (hdlr);
  cinit_prgm_DFILPCFG0 (hdlr);
  cinit_prgm_DFIUPD0 (hdlr);
  cinit_prgm_DFIUPD1 (hdlr);
  cinit_prgm_CRCPARCTL1 (hdlr);
  cinit_prgm_CRCPARCTL2 (hdlr);
  cinit_prgm_DATACTL0 (hdlr);
  cinit_prgm_ODTMAPK (hdlr);
  cinit_prgm_SWCTL (hdlr);
  cinit_prgm_CHCTL (hdlr);
  cinit_prgm_OCECCCFG0 (hdlr);
  cinit_prgm_OCECCCFG1 (hdlr);
  cinit_prgm_OCCAPCFG (hdlr);
  cinit_prgm_DQMAP0 (hdlr);
  cinit_prgm_DQMAP1 (hdlr);
  cinit_prgm_DQMAP2 (hdlr);
  cinit_prgm_DQMAP3 (hdlr);
  cinit_prgm_DQMAP4 (hdlr);
  cinit_prgm_DQMAP5 (hdlr);
  cinit_prgm_REGPARCFG (hdlr);
  cinit_prgm_POISONCFG (hdlr);
  cinit_prgm_SWCTLSTATIC(hdlr);
  cinit_prgm_DQSOSCCFG0 (hdlr);

  for(uint32_t dch=0; dch<hdlr->num_dch; dch++) {
    cinit_prgm_MSTR3(hdlr,dch);
    cinit_prgm_PASCTL1(hdlr,dch);
    cinit_prgm_PASCTL3(hdlr,dch);
    cinit_prgm_MRCTRL0(hdlr ,dch);
    cinit_prgm_HWLPCTL(hdlr, dch);
    cinit_prgm_DERATECTL5(hdlr, dch);
    cinit_prgm_DBICTL(hdlr, dch);
    cinit_prgm_OPCTRL1(hdlr, dch);
    cinit_prgm_PWRCTL(hdlr,dch);
    cinit_prgm_ECCCTL(hdlr,dch); 
    cinit_prgm_INITTMG0(hdlr, dch);
    cinit_prgm_INITTMG1(hdlr, dch);
    cinit_prgm_INITTMG2(hdlr, dch);
    cinit_prgm_MSTR4 (hdlr, dch);
    cinit_prgm_MRCTRL1 (hdlr, dch);
    cinit_prgm_MRCTRL2 (hdlr, dch);
    cinit_prgm_MRCTRL3 (hdlr, dch);
    cinit_prgm_OCPARCFG0 (hdlr, dch);
    cinit_prgm_ZQCTL1 (hdlr, dch);
    cinit_prgm_CRCPARCTL0 (hdlr, dch);
    cinit_prgm_CRCPOISONCTL0 (hdlr, dch);
    cinit_prgm_CAPARPOISONCTL (hdlr, dch);
    cinit_prgm_LNKECCCTL0 (hdlr, dch);
    cinit_prgm_LNKECCCTL1 (hdlr, dch);
    cinit_prgm_LNKECCPOISONCTL0 (hdlr, dch);
    cinit_prgm_PASCTL0 (hdlr, dch);
    cinit_prgm_PASCTL2 (hdlr, dch);
    cinit_prgm_PASCTL4 (hdlr, dch);
    cinit_prgm_CMDCFG (hdlr, dch);
    cinit_prgm_CMDCTL (hdlr, dch);
    cinit_prgm_CMDEXTCTL (hdlr, dch);
    cinit_prgm_ODTMAP (hdlr, dch);
    cinit_prgm_OCCAPCFG1 (hdlr, dch);
    cinit_prgm_OPCTRLCMD (hdlr, dch);
    cinit_prgm_PASCTL5 (hdlr, dch);
    cinit_prgm_PASCTL6 (hdlr, dch);
    cinit_prgm_PASCTL7 (hdlr, dch);
    cinit_prgm_PASCTL8 (hdlr, dch);
    cinit_prgm_PASCTL9 (hdlr, dch);
    cinit_prgm_PASCTL10 (hdlr, dch);
    cinit_prgm_PASCTL11 (hdlr, dch);
    cinit_prgm_PASCTL12 (hdlr, dch);
    cinit_prgm_PASCTL13 (hdlr, dch);
    cinit_prgm_PASCTL14 (hdlr, dch);
    cinit_prgm_PASCTL15 (hdlr, dch);
    cinit_prgm_PASCTL16 (hdlr, dch);
    cinit_prgm_PASCTL17 (hdlr, dch);
    cinit_prgm_PASCTL18 (hdlr, dch);
    cinit_prgm_PASCTL20 (hdlr, dch);
    cinit_prgm_PASCTL21 (hdlr, dch);
    cinit_prgm_PASCTL22 (hdlr, dch);
    cinit_prgm_PASCTL23 (hdlr, dch);
    cinit_prgm_PASCTL24 (hdlr, dch);
    cinit_prgm_PASCTL24 (hdlr, dch);
    cinit_prgm_PASCTL25 (hdlr, dch);
    cinit_prgm_PASCTL26 (hdlr, dch);
    cinit_prgm_PASCTL27 (hdlr, dch);
    cinit_prgm_PASCTL28 (hdlr, dch);
    cinit_prgm_PASCTL29 (hdlr, dch);
    cinit_prgm_PASCTL30 (hdlr, dch);
    cinit_prgm_PASCTL31 (hdlr, dch);
    cinit_prgm_PASCTL32 (hdlr, dch);
    cinit_prgm_PASCTL33 (hdlr, dch);
    cinit_prgm_PASCTL34 (hdlr, dch);
    cinit_prgm_PASCTL35 (hdlr, dch);
    cinit_prgm_DU_CMDBUF_CTRL (hdlr, dch);
    cinit_prgm_LP_CMDBUF_CTRL (hdlr, dch);
  }
}

/** @brief function to setup the register field values for MSTR0. The
 * function works from MSB to LSB.
 * No actual value is written to the register itself.
 * This is just setting up register intent.
 * The macro APPLYREGFIELD will apply each register field to the 32 bit
 * register value.
 * */

void cinit_prgm_MSTR0(SubsysHdlr_t *hdlr) {
  TRACE();
  REGB_DDRC_CH0_MSTR0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_MSTR0_reg;
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.
  mctl_t* memCtrlr = &(hdlr->memCtrlr_m);

#ifdef DDRCTL_DDR
  if (IS_X4) {
      reg->device_config = 0;
  } else if (IS_X8) {
      reg->device_config = 1;
  } else if (IS_X16) {
      reg->device_config = 2;
  } else {
      reg->device_config = 3;
  }
  APPLYREGFIELD(reg->value,MSTR0,device_config,reg->device_config);
#endif // DDRCTL_DDR 

#ifdef MEMC_NUM_RANKS_GT_1
  reg->active_ranks=cfg->active_ranks;
  CONSTRAIN_NE(reg->active_ranks, 0);      
  CONSTRAIN_NE(reg->active_ranks, 2);      
  APPLYREGFIELD(reg->value,MSTR0,active_ranks ,reg->active_ranks);
#endif
  
#ifdef UMCTL2_CID_EN
  if(IS_CID_EN) {
      reg->active_logical_ranks = GET_CID_WIDTH;
  } else {
      reg->active_logical_ranks = 0;
  }
  LOG_MESSAGE(hdlr, 1, ("reg->active_logical_ranks=%d\n", reg->active_logical_ranks));
  APPLYREGFIELD(reg->value,MSTR0,active_logical_ranks,reg->active_logical_ranks);
#endif

  reg->burst_rdwr= cfg->burst_rdwr;
  APPLYREGFIELD(reg->value,MSTR0,burst_rdwr,reg->burst_rdwr );
  if( IS_LPDDR4 || IS_LPDDR5 ) {
    CONSTRAIN_INSIDE(reg->burst_rdwr, 0x8, 0x8);
  }
  
#ifdef MEMC_DDR3_OR_4
  if (IS_DDR4) {
      if (hdlr->memCtrlr_m.qdyn_cfg.dll_off_mode  == 1) {
          reg->dll_off_mode = 0x1; // must set to 1 if DLL-off mode is enabled
      } else {
          reg->dll_off_mode = 0x0;
      }
  } else {
      reg->dll_off_mode = 0x0;
  }
  APPLYREGFIELD(reg->value,MSTR0,dll_off_mode ,reg->dll_off_mode  );
#endif // MEMC_DDR3_OR_4


  if (memCtrlr->sdram_bus_width == DWC_BUSWIDTH_FULL){
    reg->data_bus_width = 0;
  } else if(memCtrlr->sdram_bus_width == DWC_BUSWIDTH_HALF){
    reg->data_bus_width = 1;
  } else {
    reg->data_bus_width = 2;
  }

  APPLYREGFIELD(reg->value,MSTR0,data_bus_width ,reg->data_bus_width   );

  // TODO reg->geardown_mode
  //
  //
  //
#ifndef MEMC_CMD_RTN2IDLE
  if (IS_LPDDR23) {
      reg->en_2t_timing_mode = 0;
  } else {
      if (reg->burst_rdwr == 1) // 2T not tested in BL2 mode
          reg->en_2t_timing_mode = 0;
#ifdef DDRCTL_DDR
#ifdef MEMC_FREQ_RATIO_2
      else if (hdlr->memCtrlr_m.qdyn_cfg.geardown_mode == 1) // 2T not tested in Geardown mode
          reg->en_2t_timing_mode = 0;
#endif // MEMC_FREQ_RATIO_2
#endif // DDRCTL_DDR
      else
#ifdef UMCTL2_SHARED_AC
#ifdef UMCTL2_PROGCHN
          if (cfg->dual_channel_en == 1)
#endif
              reg->en_2t_timing_mode = 1; //Shared AC mode always use the 2T mode.
#ifdef UMCTL2_PROGCHN
          else
              CONSTRAIN_INSIDE(reg->en_2t_timing_mode,0,1);
#endif
#else
      CONSTRAIN_INSIDE(reg->en_2t_timing_mode,0,1);
#endif
  }
  APPLYREGFIELD(reg->value,MSTR0,en_2t_timing_mode ,reg->en_2t_timing_mode    );
#endif

#ifdef DDRCTL_DDR
  reg->burstchop = cfg->burstchop; 
  CONSTRAIN_INSIDE(reg->burstchop, 0, 1);
  APPLYREGFIELD(reg->value,MSTR0,burstchop ,reg->burstchop );
#endif

#ifndef UMCTL2_INCL_ARB
  {
      if (IS_LPDDR3) {
          reg->burst_mode = 0;
      } else if (IS_LPDDR4) {
          reg->burst_mode = 0;
      } else {
          reg->burst_mode=cfg->burst_mode;
          CONSTRAIN_INSIDE(reg->burst_mode,0,1);
      }
  }
  APPLYREGFIELD(reg->value,MSTR0,burst_mode,reg->burst_mode);
#endif

#ifdef DDRCTL_LPDDR 
  if (IS_LPDDR5) {
      cfg->lpddr5 = 1;
  } else {
      cfg->lpddr5 = 0;
  }
  APPLY_CFG_TO_REGFIELD(cfg,MSTR0,lpddr5);
#endif // DDRCTL_LPDDR
	

	
#ifdef DDRCTL_DDR
  if (IS_DDR5) {
      reg->ddr5 = 1;
  } else {
      reg->ddr5 = 0;
  }
  APPLYREGFIELD(reg->value,MSTR0,ddr5,reg->ddr5);
#endif // DDRCTL_DDR
	
#ifdef DDRCTL_LPDDR
  if (IS_LPDDR4) {
      cfg->lpddr4 = 1;
  } else {
      cfg->lpddr4 = 0;
  }
  APPLY_CFG_TO_REGFIELD(cfg,MSTR0,lpddr4);
#endif // DDRCTL_LPDDR
	

	
#ifdef DDRCTL_DDR
  if (IS_DDR4) {
      reg->ddr4 = 1;
  } else {
      reg->ddr4 = 0;
  }
  APPLYREGFIELD(reg->value,MSTR0,ddr4,reg->ddr4);
#endif // DDRCTL_DDR
  
  LOG_MESSAGE(hdlr, 1, ("MSTR0= 0x%x\n",
               reg->value ));
}

/** @brief function to setup the register field values for MSTR1. 
 * */

void cinit_prgm_MSTR1(SubsysHdlr_t *hdlr) {
#ifdef UMCTL2_DDR4_MRAM_EN    
  TRACE();
  REGB_DDRC_CH0_MSTR1_struct_t
      *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_MSTR1_reg;

#ifdef UMCTL2_HET_RANK
  reg->alt_addrmap_en = VIRL_DRAM_MRAM_MIXED ? 0x1 : 0x0;
  APPLYREGFIELD(reg->value,MSTR1,alt_addrmap_en,reg->alt_addrmap_en);
#endif
  
  reg->rank_tmgreg_sel = 0x0;

  if (IS_DDR4) {
      if (VIRL_RANK0_MRAM) {
          reg->rank_tmgreg_sel |= 0x01;
      }

#ifdef MEMC_NUM_RANKS_GT_1
      if (VIRL_RANK1_MRAM) {
          reg->rank_tmgreg_sel |= 0x2;
      }
#endif

#ifdef MEMC_NUM_RANKS_GT_2
      if (VIRL_RANK2_MRAM) {
          reg->rank_tmgreg_sel |= 0x04;
      }

      if (VIRL_RANK3_MRAM) {
          reg->rank_tmgreg_sel |= 0x08;
      }
#endif
  }
  APPLYREGFIELD(reg->value,MSTR1,rank_tmgreg_sel,reg->rank_tmgreg_sel);

  LOG_MESSAGE(hdlr, 1, ("MSTR1= 0x%x\n",
               reg->value ));
#endif

}

/** @brief function to setup the register field values for MSTR2. */
void cinit_prgm_MSTR2(SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef UMCTL2_FREQUENCY_NUM_GT_1
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.
  REGB_DDRC_CH0_MSTR2_struct_t
      *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_MSTR2_reg;

  reg->target_frequency=qdyn->target_frequency;
  CONSTRAIN_MAX(reg->target_frequency, 3);
  APPLYREGFIELD(reg->value,MSTR2,target_frequency,reg->target_frequency );
  LOG_MESSAGE(hdlr, 1, ("MSTR2= 0x%x\n",
               reg->value ));
#endif // UMCTL2_FREQUENCY_NUM_GT_1

}

/** @brief function to setup the register field values for MSTR3
 * */
void cinit_prgm_MSTR3(SubsysHdlr_t *hdlr, uint32_t ch) {
#ifdef MEMC_DDR4
  TRACE();
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  DWC_DDRCTL_DECLARE_DCHC_DDRC_REG_PTRS(MSTR3)
  reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_MSTR3_reg;

  if(ch!=0) {
    DWC_DDRCTL_CAST_DDRC_REG_DCH(ch,MSTR3);
  }

#ifndef MEMC_CMD_RTN2IDLE
  else if(IS_DDR4) {
    APPLY_CFG_TO_REGFIELD_P(qdyn,MSTR3,geardown_mode,ch);
  }
#endif

  LOG_MESSAGE(hdlr, 1, ("MSTR3[%0d]= 0x%x\n",ch,reg->value ));

#endif
}
/** @brief function to setup the register field values for PASCTL1
 * */
void cinit_prgm_PASCTL1(SubsysHdlr_t *hdlr, uint32_t ch) {
#ifdef MEMC_DDR5
  TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to quasi-dynamic configuration options.
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to quasi-dynamic configuration options.

  DWC_DDRCTL_DECLARE_DCHC_DDRC_REG_PTRS(PASCTL1)
  reg =&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_PASCTL1_reg;

  if(ch!=0) {
    DWC_DDRCTL_CAST_DDRC_REG_DCH(ch,PASCTL1);
  }

  dyn->rd_min_gap[ch] = cinit_cal_ddr5_rd_min_gap(hdlr) - 1;
  dyn->wr_min_gap[ch] = cinit_cal_ddr5_wr_min_gap(hdlr) - 1;

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL1,rd_min_gap,ch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL1,wr_min_gap,ch);

  CONSTRAIN_INSIDE(reg->rd_min_gap,0,15);
  CONSTRAIN_INSIDE(reg->wr_min_gap,0,15);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL1,prank_tmgreg_set_sel,ch);
  APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL1,pre_ab_enable,ch);
  APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL1,pre_sb_enable,ch);

  LOG_MESSAGE(hdlr, 1, ("PASCTL1[%0d]= 0x%x\n",ch,reg->value ));

#endif
}

void cinit_prgm_PASCTL3(SubsysHdlr_t *hdlr, uint32_t ch) {
#ifdef MEMC_DDR5
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to quasi-dynamic configuration options.

  DWC_DDRCTL_DECLARE_DCHC_DDRC_REG_PTRS(PASCTL3)
  reg =&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_PASCTL3_reg;

  if(ch!=0) {
    DWC_DDRCTL_CAST_DDRC_REG_DCH(ch,PASCTL3);
  }

  APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL3,prank_bit_mask,ch);
  CONSTRAIN_INSIDE(reg->prank_bit_mask,0,3);

  APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL3,bg_bit_mask,ch);
  CONSTRAIN_INSIDE(reg->bg_bit_mask,0,3);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL3,bank_bit_mask,ch);
  CONSTRAIN_INSIDE(reg->bank_bit_mask,0,3);

  LOG_MESSAGE(hdlr, 1, ("PASCTL3[%0d]= 0x%x\n",ch,reg->value ));

#endif
}


/** @brief function to setup the register field values for DFIMISC
 */
void cinit_prgm_DFIMISC (SubsysHdlr_t *hdlr) { 
  TRACE();
  REGB_DDRC_CH0_DFIMISC_struct_t
  *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DFIMISC_reg; 
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD(qdyn,DFIMISC ,dfi_frequency);
  
#ifdef MEMC_DDR4
  APPLY_CFG_TO_REGFIELD(qdyn,DFIMISC ,dis_dyn_adr_tri);
#endif
  APPLY_CFG_TO_REGFIELD(qdyn,DFIMISC ,dfi_init_start);
#ifdef DDRCTL_LPDDR
  APPLY_CFG_TO_REGFIELD(cfg,DFIMISC ,dfi_channel_mode);
#endif
#ifdef UMCTL2_SHARED_AC
  // In SharedAC RDIMM mode, the dfi_dram_clk_disable must be shared by two channels.
  if(IS_RDIMM) { cfg->share_dfi_dram_clk_disable=1; }
  else { CONSTRAIN_INSIDE(cfg->share_dfi_dram_clk_disable,0,1); }
  APPLY_CFG_TO_REGFIELD(cfg,DFIMISC ,share_dfi_dram_clk_disable);
#endif
#ifdef UMCTL2_DFI_DATA_CS_EN
  APPLY_CFG_TO_REGFIELD(cfg,DFIMISC ,dfi_data_cs_polarity);
  CONSTRAIN_INSIDE(reg->dfi_data_cs_polarity,0,1);
#endif

#ifdef MEMC_DDR4_OR_LPDDR4
  APPLY_CFG_TO_REGFIELD(cfg,DFIMISC ,phy_dbi_mode);
  CONSTRAIN_INSIDE(reg->phy_dbi_mode,0,1);
#endif  
  APPLY_CFG_TO_REGFIELD(qdyn,DFIMISC ,dfi_init_complete_en);
  CONSTRAIN_INSIDE(reg->dfi_init_complete_en,0,1);

  LOG_MESSAGE(hdlr, 1, ("DFIMISC= 0x%x\n",reg->value ));
}

/** @brief function to setup the register field values for DFIPHYMSTR  
 */
void cinit_prgm_DFIPHYMSTR (SubsysHdlr_t *hdlr) { 
  TRACE();
  REGB_DDRC_CH0_DFIPHYMSTR_struct_t
      *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DFIPHYMSTR_reg;  

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  APPLY_CFG_TO_REGFIELD(cfg,DFIPHYMSTR ,dfi_phymstr_en);
  CONSTRAIN_INSIDE(reg->dfi_phymstr_en,0,1);
  LOG_MESSAGE(hdlr, 1, ("DFIPHYMSTR= 0x%x\n",reg->value ));
}

/** @brief function to setup the register field values for DFIUPD0
 */
void cinit_prgm_DFIUPD0 (SubsysHdlr_t *hdlr) { 
  TRACE();
  REGB_DDRC_CH0_DFIUPD0_struct_t
      *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DFIUPD0_reg; 

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
//  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD(qdyn,DFIUPD0 ,dis_auto_ctrlupd);
  APPLY_CFG_TO_REGFIELD(qdyn,DFIUPD0 ,dis_auto_ctrlupd_srx);
  APPLY_CFG_TO_REGFIELD(cfg,DFIUPD0 , ctrlupd_pre_srx);
  APPLY_CFG_TO_REGFIELD(cfg,DFIUPD0 ,dfi_phyupd_en);

  CONSTRAIN_INSIDE(reg->dis_auto_ctrlupd,0,1);
  CONSTRAIN_INSIDE(reg->dis_auto_ctrlupd_srx,0,1);
  CONSTRAIN_INSIDE(reg->ctrlupd_pre_srx,0,1);
  CONSTRAIN_INSIDE(reg->dfi_phyupd_en,0,1);
  LOG_MESSAGE(hdlr, 1, ("DFIUPD0= 0x%x\n",reg->value ));
}

/** @brief function to setup the register field values for RFSHCTL0. 
 * */
void cinit_prgm_RFSHCTL0 (SubsysHdlr_t *hdlr) { 
  TRACE();
  REGB_DDRC_CH0_RFSHCTL0_struct_t* reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_RFSHCTL0_reg;
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

#ifdef UMCTL2_DDR4_MRAM_EN  
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  APPLY_CFG_TO_REGFIELD(cfg, RFSHCTL0, rank_dis_refresh );
#endif

  APPLY_CFG_TO_REGFIELD(dyn, RFSHCTL0, refresh_update_level );

  APPLY_CFG_TO_REGFIELD(dyn, RFSHCTL0, dis_auto_refresh );
  CONSTRAIN_INSIDE(reg->dis_auto_refresh, 0, 1);


  LOG_MESSAGE(hdlr, 1, ("RFSHCTL0= 0x%x\n",reg->value ));

}

/** @brief function to setup the register field values for RFSHMOD0. 
 * */
void cinit_prgm_RFSHMOD0 (SubsysHdlr_t *hdlr) { 
  TRACE();
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_DDRC_CH0_RFSHMOD0_struct_t* reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_RFSHMOD0_reg;

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
#ifdef DDRCTL_LPDDR
  APPLY_CFG_TO_REGFIELD(cfg,RFSHMOD0 ,per_bank_refresh);
#endif

  APPLY_CFG_TO_REGFIELD(dyn,RFSHMOD0 ,refresh_burst);

  {
      if (hdlr->phy_training) {
          CONSTRAIN_INSIDE(reg->refresh_burst,0,7);
      } else {
          if (IS_DDR4) {
              // refresh_burst, reg->refresh_timer_start_value_x32, cfg->MRCTRL0.reg->pda_en
              // Fixed 4x
              if (qdyn->fgr_mode == 2) {
                  // Need to ensure that a phy update, coming near the end of a refresh burst, does not cause a tRFCmax violation
                  // Calculate maximum time for a phy update, divide by tREFI4 (= 7.8/4 us) to find how many tREFI4 periods are needed for
                  // a phy update. The refresh burst should then be a maximum of 32 - that number.
                  CONSTRAIN_INSIDE(reg->refresh_burst,0,31);
                  // Fixed 2x
              } else if (qdyn->fgr_mode == 1) {
                  // Need to ensure that a phy update, coming near the end of a refresh burst, does not cause a tRFCmax violation
                  // Calculate maximum time for a phy update, divide by tREFI2 (= 7.8/2 us) to find how many tREFI2 periods are needed for
                  // a phy update. The refresh burst should then be a maximum of 16 - that number.
                  CONSTRAIN_INSIDE(reg->refresh_burst,0,15);
                  // Fixed 1x
              } else {
                  // Need to ensure that a phy update, coming near the end of a refresh burst, does not cause a tRFCmax violation
                  // Calculate maximum time for a phy update, divide by tREFI (= 7.8us) to find how many tREFI periods are needed for
                  // a phy update. The refresh burst should then be a maximum of 7 - that number.
                  CONSTRAIN_INSIDE(reg->refresh_burst,0,7);
              }
          } else if (IS_LPDDR4 || IS_LPDDR5) {
              if (cfg->per_bank_refresh) {
                  // Need to ensure that a phy update, coming near the end of a refresh burst, does not cause a tRFCmax violation
                  // Calculate maximum time for a phy update, divide by tREFIpb to find how many tREFIpb periods are needed for
                  // a phy update. The refresh burst should then be a maximum of 8 - that number.
                  CONSTRAIN_INSIDE(reg->refresh_burst,0,63);
              } else {  
                  // Need to ensure that a phy update, coming near the end of a refresh burst, does not cause a tRFCmax violation
                  // Calculate maximum time for a phy update, divide by tREFIab to find how many tREFIab periods are needed for
                  // a phy update. The refresh burst should then be a maximum of 8 - that number.
                  CONSTRAIN_INSIDE(reg->refresh_burst,0,7);
              }
          } else {
              // Need to ensure that a phy update, coming near the end of a refresh burst, does not cause a tRFCmax violation
              // Calculate maximum time for a phy update, divide by tREFI (= 7.8us) to find how many tREFI periods are needed for
              // a phy update. The refresh burst should then be a maximum of 8 - that number.
              CONSTRAIN_INSIDE(reg->refresh_burst,0,7);
          } // IS_DDR4
      }
  }

  LOG_MESSAGE(hdlr, 1, ("RFSHMOD0= 0x%x\n", reg->value ));
}

/** @brief function to setup the register field values for RFSHMOD1. 
 * */
void cinit_prgm_RFSHMOD1 (SubsysHdlr_t *hdlr) { 
  TRACE();
#ifdef MEMC_DDR4  
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  REGB_DDRC_CH0_RFSHMOD1_struct_t* reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_RFSHMOD1_reg;

  APPLY_CFG_TO_REGFIELD(qdyn, RFSHMOD1, fgr_mode );
  CONSTRAIN_MAX(reg->fgr_mode, 2);

  LOG_MESSAGE(hdlr, 1, ("RFSHMOD1= 0x%x\n", reg->value ));
#endif
}

void cinit_prgm_ZQCTL0 (SubsysHdlr_t *hdlr) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  REGB_DDRC_CH0_ZQCTL0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ZQCTL0_reg;

  APPLY_CFG_TO_REGFIELD(dyn,ZQCTL0,dis_auto_zq);
#ifdef MEMC_DDR4
    APPLY_CFG_TO_REGFIELD(cfg,ZQCTL0,dis_mpsmx_zqcl);
#endif
  APPLY_CFG_TO_REGFIELD(cfg,ZQCTL0,zq_resistor_shared);
  LOG_MESSAGE(hdlr, 1, ("ZQCTL0= 0x%x\n",reg->value ));
}

void cinit_prgm_ZQCTL2 (SubsysHdlr_t *hdlr) { 
  TRACE();
  REGB_DDRC_CH0_ZQCTL2_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ZQCTL2_reg;
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD(qdyn,ZQCTL2,dis_srx_zqcl);
  LOG_MESSAGE(hdlr, 1, ("ZQCTL2= 0x%x\n",reg->value ));
}

void cinit_prgm_SCHED0 (SubsysHdlr_t *hdlr) { 
  TRACE();
  REGB_DDRC_CH0_SCHED0_struct_t
      *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_SCHED0_reg; 

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

#ifdef UMCTL2_VPRW_EN
#ifdef MEMC_ENH_RDWR_SWITCH 
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,opt_vprw_sch);
  CONSTRAIN_INSIDE(qdyn->opt_vprw_sch,0,1);
#endif // MEMC_ENH_RDWR_SWITCH 
#endif // UMCTL2_VPRW_EN

  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,lpr_num_entries);
#ifdef MEMC_USE_RMW  
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,autopre_rmw);
#endif
#ifdef MEMC_NTT_UPD_PRE  
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,dis_opt_ntt_by_pre);
#endif
#ifdef MEMC_NTT_UPD_ACT  
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,dis_opt_ntt_by_act);
#endif
#ifdef MEMC_ENH_RDWR_SWITCH
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,opt_wrcam_fill_level);
#endif
#ifdef MEMC_RDWR_SWITCH_POL_SEL
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,rdwr_switch_policy_sel);
#endif
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,pageclose);
#ifdef MEMC_INLINE_ECC
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED0,dis_opt_wrecc_collision_flush);
#endif // MEMC_INLINE_ECC
  APPLY_CFG_TO_REGFIELD(cfg,SCHED0,prefer_write);
  
  LOG_MESSAGE(hdlr, 1, ("SCHED0= 0x%x\n",reg->value ));
}

void cinit_prgm_HWLPCTL (SubsysHdlr_t *hdlr, uint32_t ch) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  DWC_DDRCTL_FREQ_REG_STRUCT( , 0, REGB_DDRC, HWLPCTL, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, HWLPCTL)
  DWC_DDRCTL_CAST_REG_DCHC(ch, REGB_DDRC, HWLPCTL, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(cfg,HWLPCTL,hw_lp_exit_idle_en, ch);
  APPLY_CFG_TO_REGFIELD_P(qdyn,HWLPCTL,hw_lp_en, ch);
  CONSTRAIN_INSIDE(reg->hw_lp_en,0,1);
  CONSTRAIN_INSIDE(reg->hw_lp_exit_idle_en,0,1);

  LOG_MESSAGE(hdlr, 1, ("HWLPCTL= 0x%x\n",reg->value ));
}

/** @brief function to setup the register field values for DERATEEN. 
 * 
 */
void cinit_prgm_DERATECTL0(SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef MEMC_LPDDR4
  REGB_DDRC_CH0_DERATECTL0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DERATECTL0_reg;
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to dynamic configuration options.

  APPLY_CFG_TO_REGFIELD(dyn, DERATECTL0,derate_enable);
  APPLY_CFG_TO_REGFIELD(dyn, DERATECTL0,derate_mr4_pause_fc);

  LOG_MESSAGE(hdlr, 1, ("DERATECTL0= 0x%x\n",
               reg->value ));
  
#endif
}

void cinit_prgm_RANKCTL (SubsysHdlr_t *hdlr) { 
#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
  TRACE();
  REGB_DDRC_CH0_RANKCTL_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_RANKCTL_reg;

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  //comment as not used
  //mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

#ifdef UMCTL2_CID_EN
  APPLY_CFG_TO_REGFIELD(cfg,RANKCTL,max_logical_rank_wr);
  CONSTRAIN_INSIDE(reg->max_logical_rank_wr,0,15);
  APPLY_CFG_TO_REGFIELD(cfg,RANKCTL,max_logical_rank_rd);
  CONSTRAIN_INSIDE(reg->max_logical_rank_rd,0,15);
#endif // UMCTL2_CID_EN  

#ifdef MEMC_NUM_RANKS_GT_1
  APPLY_CFG_TO_REGFIELD(cfg,RANKCTL,max_rank_rd);
  CONSTRAIN_INSIDE(reg->max_rank_rd,0,15);
  APPLY_CFG_TO_REGFIELD(cfg,RANKCTL,max_rank_wr);
  CONSTRAIN_INSIDE(reg->max_rank_wr,0,15);
#endif // MEMC_NUM_RANKS_GT_1  

  LOG_MESSAGE(hdlr, 1, ("RANKCTL= 0x%x\n",reg->value ));
#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1   
}

/** @brief  function to setup the register field values for DERATECTL1.*/
void cinit_prgm_DERATECTL1(SubsysHdlr_t *hdlr)
{
  TRACE();
#ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
  REGB_DDRC_CH0_DERATECTL1_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DERATECTL1_reg;
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); 
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to dynamic configuration options.
  if (IS_X16) {
    if(MEMC_DRAM_DATA_WIDTH==16) { cfg->active_derate_byte_rank0=1 ;} 
    else if(MEMC_DRAM_DATA_WIDTH==32) { cfg->active_derate_byte_rank0=0x5 ;}
    else if(MEMC_DRAM_DATA_WIDTH==64) { cfg->active_derate_byte_rank0=0x55 ;}
  } else if (IS_X8) {
    // byte mode
    if(MEMC_DRAM_DATA_WIDTH==16) { cfg->active_derate_byte_rank0=0x3 ;} 
    else if(MEMC_DRAM_DATA_WIDTH==32) { cfg->active_derate_byte_rank0=0xf ;}
    else if(MEMC_DRAM_DATA_WIDTH==64) { cfg->active_derate_byte_rank0=0xff ;}
  }

#ifdef DDRCTL_LPDDR
  if(dyn->derate_enable) {
    // All "0s" illegal if derating is enabled
    CONSTRAIN_MIN(cfg->active_derate_byte_rank0, 1);
  }
#endif

  APPLY_CFG_TO_REGFIELD(cfg, DERATECTL1, active_derate_byte_rank0);
      

  LOG_MESSAGE(hdlr, 1, ("DERATECTL1= 0x%x\n",reg->value ));

#endif
}

/** @brief function to setup the register field values for MRCTRL0. 
 *  @note we only conigure the static register fields here
 */

void cinit_prgm_MRCTRL0(SubsysHdlr_t *hdlr, uint32_t ch) {
#ifdef UMCTL2_CID_EN
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, MRCTRL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, MRCTRL0)
  DWC_DDRCTL_CAST_REG_DCHC(ch, REGB_DDRC, MRCTRL0, reg, _CH); 

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.
 
  if(IS_DDR4){
    APPLY_CFG_TO_REGFIELD_P(cfg, MRCTRL0,mr_cid,ch);
    CONSTRAIN_MAX(reg->mr_cid, ((GET_CID_WIDTH >> 1) & 0x1));
  }
  LOG_MESSAGE(hdlr, 1, ("MRCTRL0= 0x%x\n",
               reg->value ));
#endif
}

void cinit_prgm_ECCCFG0 (SubsysHdlr_t *hdlr) { 
  TRACE();
#ifdef MEMC_ECC_SUPPORT_GT_0
  REGB_DDRC_CH0_ECCCFG0_struct_t
    *reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ECCCFG0_reg;

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG0,ecc_mode);
  CONSTRAIN_INSIDE(reg->ecc_mode,0,5);
#ifndef UMCTL2_INCL_ARB
  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG0,test_mode);
  CONSTRAIN_INSIDE(reg->test_mode,0,1);
#endif
#ifdef MEMC_USE_RMW  
  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG0,dis_scrub);
  CONSTRAIN_INSIDE(reg->dis_scrub,0,1);
#endif
#ifdef MEMC_ECCAP
  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG0,ecc_ap_en);
  CONSTRAIN_INSIDE(reg->ecc_ap_en,0,1);
  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG0,ecc_ap_err_threshold);
  CONSTRAIN_INSIDE(reg->ecc_ap_err_threshold,0,MEMC_MAX_INLINE_ECC_PER_BURST-1);
#endif
#ifdef MEMC_INLINE_ECC
  APPLY_CFG_TO_REGFIELD(qdyn,ECCCFG0,ecc_region_map);
  CONSTRAIN_INSIDE(reg->ecc_region_map,0,127);
  APPLY_CFG_TO_REGFIELD(qdyn,ECCCFG0,blk_channel_idle_time_x32);
  CONSTRAIN_INSIDE(reg->blk_channel_idle_time_x32,0,63);
  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG0,ecc_region_map_granu);
  CONSTRAIN_INSIDE(reg->ecc_region_map_granu,0,3);
  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG0,ecc_region_map_other);
  CONSTRAIN_INSIDE(reg->ecc_region_map_other,0,1);
  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG0,ecc_region_remap_en);
  CONSTRAIN_INSIDE(reg->ecc_region_remap_en,0,1);
#endif
  LOG_MESSAGE(hdlr, 1, ("ECCCFG0= 0x%x\n",reg->value ));
#endif
}

void cinit_prgm_ECCCFG1 (SubsysHdlr_t *hdlr) { 
  TRACE();
#ifdef MEMC_ECC_SUPPORT_GT_0
  REGB_DDRC_CH0_ECCCFG1_struct_t
    *reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ECCCFG1_reg;
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  APPLY_CFG_TO_REGFIELD(qdyn,ECCCFG1,data_poison_en);
  CONSTRAIN_INSIDE(reg->data_poison_en,0,1);

  APPLY_CFG_TO_REGFIELD(qdyn,ECCCFG1,data_poison_bit);
  CONSTRAIN_INSIDE(reg->data_poison_bit,0,1);
#ifdef MEMC_ECC_SUPPORT_2
  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG1,poison_chip_en);
  CONSTRAIN_INSIDE(reg->poison_chip_en,0,1);
#endif
#ifdef MEMC_INLINE_ECC
  APPLY_CFG_TO_REGFIELD(qdyn,ECCCFG1,ecc_region_parity_lock);
  CONSTRAIN_INSIDE(reg->ecc_region_parity_lock,0,1);
  APPLY_CFG_TO_REGFIELD(qdyn,ECCCFG1,ecc_region_waste_lock);
  CONSTRAIN_INSIDE(reg->ecc_region_waste_lock,0,1);

  APPLY_CFG_TO_REGFIELD(cfg,ECCCFG1,blk_channel_active_term);
  CONSTRAIN_INSIDE(reg->blk_channel_active_term,0,1);
  APPLY_CFG_TO_REGFIELD(qdyn,ECCCFG1,active_blk_channel);
#endif
  LOG_MESSAGE(hdlr, 1, ("ECCCFG1= 0x%x\n",reg->value ));
#endif
}

/** @brief  function to setup the register field values for ECCCTL.*/
void cinit_prgm_ECCCTL (SubsysHdlr_t *hdlr, uint32_t ch) { 
  TRACE();
#ifdef MEMC_ECC_SUPPORT_GT_0
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); 
  
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, ECCCTL, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, ECCCTL)
  DWC_DDRCTL_CAST_REG_DCHC(ch, REGB_DDRC, ECCCTL, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,ECCCTL,ecc_corrected_err_intr_en,ch);

  APPLY_CFG_TO_REGFIELD_P(dyn,ECCCTL,ecc_uncorrected_err_intr_en,ch);

#ifdef MEMC_ECCAP
  APPLY_CFG_TO_REGFIELD_P(dyn,ECCCTL,ecc_ap_err_intr_en,ch);
#endif

  LOG_MESSAGE(hdlr, 1, ("ECCCTL= 0x%x\n",reg->value ));
#endif
}

/** @brief  function to setup the register field values for ECCPOISONADDR0.*/
void cinit_prgm_ECCPOISONADDR0 (SubsysHdlr_t *hdlr) { 
  TRACE();
#ifdef MEMC_ECC_SUPPORT_GT_0
  REGB_DDRC_CH0_ECCPOISONADDR0_struct_t
    *reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ECCPOISONADDR0_reg;

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); 
  mctl_t* memCtrlr = &(hdlr->memCtrlr_m);
  uint32_t l_ecc_poison_col;

  APPLY_CFG_TO_REGFIELD(cfg,ECCPOISONADDR0,ecc_poison_col);
  if (memCtrlr->sdram_bus_width == DWC_BUSWIDTH_FULL){
    l_ecc_poison_col = (reg->ecc_poison_col & 0x7);              //To compare only ecc_poison_col[2:0]
  } else if(memCtrlr->sdram_bus_width == DWC_BUSWIDTH_HALF){
    l_ecc_poison_col = (reg->ecc_poison_col & 0xF);              //To compare only ecc_poison_col[3:0]
  } else if(memCtrlr->sdram_bus_width == DWC_BUSWIDTH_QUARTER){
    l_ecc_poison_col = (reg->ecc_poison_col & 0x1F);             //To compare only ecc_poison_col[4:0]
  }
  CONSTRAIN_INSIDE(l_ecc_poison_col,0,0);

#ifdef UMCTL2_CID_EN
  APPLY_CFG_TO_REGFIELD(cfg,ECCPOISONADDR0,ecc_poison_cid);
  if(GET_CID_WIDTH == 0){
    CONSTRAIN_INSIDE(reg->ecc_poison_cid,0,0);
  }
#endif
#ifdef MEMC_NUM_RANKS_GT_1
  APPLY_CFG_TO_REGFIELD(cfg,ECCPOISONADDR0,ecc_poison_rank);
#endif
  LOG_MESSAGE(hdlr, 1, ("ECCPOISONADDR0= 0x%x\n",reg->value ));
#endif
}

/** @brief  function to setup the register field values for ECCPOISONADDR1.*/
void cinit_prgm_ECCPOISONADDR1 (SubsysHdlr_t *hdlr) { 
  TRACE();
#ifdef MEMC_ECC_SUPPORT_GT_0
  REGB_DDRC_CH0_ECCPOISONADDR1_struct_t
    *reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ECCPOISONADDR1_reg;

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); 

  APPLY_CFG_TO_REGFIELD(cfg,ECCPOISONADDR1,ecc_poison_row);

  APPLY_CFG_TO_REGFIELD(cfg,ECCPOISONADDR1,ecc_poison_bank);

#ifdef MEMC_DDR4                                                    
  APPLY_CFG_TO_REGFIELD(cfg,ECCPOISONADDR1,ecc_poison_bg);
#endif
  LOG_MESSAGE(hdlr, 1, ("ECCPOISONADDR1= 0x%x\n",reg->value));
#endif
}

/** @brief  function to setup the register field values for ECCPOISONPAT0.*/
void cinit_prgm_ECCPOISONPAT0 (SubsysHdlr_t *hdlr) { 
  TRACE();
#ifdef MEMC_ECC_SUPPORT_GT_0
  REGB_DDRC_CH0_ECCPOISONPAT0_struct_t
    *reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ECCPOISONPAT0_reg;

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD(qdyn,ECCPOISONPAT0,ecc_poison_data_31_0);

  LOG_MESSAGE(hdlr, 1, ("ECCPOISONPAT0= 0x%x\n",reg->value ));
#endif
}

/** @brief  function to setup the register field values for ECCPOISONPAT1.*/
void cinit_prgm_ECCPOISONPAT1 (SubsysHdlr_t *hdlr) { 
  TRACE();
#if defined(MEMC_ECC_SUPPORT_GT_0) && defined(MEMC_DRAM_DATA_WIDTH_64)
  REGB_DDRC_CH0_ECCPOISONPAT1_struct_t
    *reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ECCPOISONPAT1_reg;

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD(qdyn,ECCPOISONPAT1,ecc_poison_data_63_32);

  LOG_MESSAGE(hdlr, 1, ("ECCPOISONPAT1= 0x%x\n",reg->value ));
#endif
}

/** @brief  function to setup the register field values for ECCPOISONPAT2.*/
void cinit_prgm_ECCPOISONPAT2 (SubsysHdlr_t *hdlr) { 
  TRACE();
#ifdef MEMC_ECC_SUPPORT_GT_0
  REGB_DDRC_CH0_ECCPOISONPAT2_struct_t
    *reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ECCPOISONPAT2_reg;

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD(qdyn,ECCPOISONPAT2,ecc_poison_data_71_64);

  LOG_MESSAGE(hdlr, 1, ("ECCPOISONPAT2= 0x%x\n",reg->value ));
#endif
}

void cinit_prgm_DBICTL (SubsysHdlr_t *hdlr, uint32_t ch) { 
  TRACE();
#ifdef MEMC_DDR4_OR_LPDDR4
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, DBICTL, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, DBICTL)
  DWC_DDRCTL_CAST_REG_DCHC(ch, REGB_DDRC, DBICTL, reg, _CH); 

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
#ifdef MEMC_LPDDR4
  if( IS_LPDDR4) {
    APPLY_CFG_TO_REGFIELD_P(qdyn,DBICTL ,rd_dbi_en, ch);
    APPLY_CFG_TO_REGFIELD_P(qdyn,DBICTL ,wr_dbi_en, ch);
  }
  else if(IS_LPDDR5) {
    APPLY_CFG_TO_REGFIELD_P(qdyn,DBICTL ,rd_dbi_en, ch);
    APPLY_CFG_TO_REGFIELD_P(qdyn,DBICTL ,wr_dbi_en, ch);
  }
  APPLY_CFG_TO_REGFIELD_P(qdyn,DBICTL ,dm_en, ch);
#endif
#ifdef MEMC_DDR4
  if( IS_DDR4) {
    APPLY_CFG_TO_REGFIELD_P(qdyn,DBICTL ,rd_dbi_en, ch);
    APPLY_CFG_TO_REGFIELD_P(qdyn,DBICTL ,wr_dbi_en, ch);
  }
  APPLY_CFG_TO_REGFIELD_P(qdyn,DBICTL ,dm_en, ch);
#endif   
  LOG_MESSAGE(hdlr, 1, ("DBICTL= 0x%x\n",reg->value ));
#endif
}

void cinit_prgm_DIMMCTL (SubsysHdlr_t *hdlr) { 
  TRACE();
  REGB_DDRC_CH0_DIMMCTL_struct_t
      *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DIMMCTL_reg;    

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

#ifdef MEMC_DDR4
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamci configuration options.
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL,rcd_b_output_disabled );
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL,rcd_a_output_disabled );
  APPLY_CFG_TO_REGFIELD(qdyn,DIMMCTL,rcd_weak_drive );
#ifdef UMCTL2_HWFFC_EN
  uint8_t rcd_num;
  if (USE_RCD) {
      cfg->rcd_num = 0; // @todo replace NUM_RCDS;
  } else  {// Not RDIMM
      cfg->rcd_num = 0;
  } // USE_RCD  
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL,rcd_num );
#endif

  if(IS_LRDIMM) {
      cfg->lrdimm_bcom_cmd_prot = 1;
  } else {
      cfg->lrdimm_bcom_cmd_prot = 0;
  }  
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL,lrdimm_bcom_cmd_prot );

  if(DEV_DQ_WIDTH==16) {
      cfg->dimm_dis_bg_mirroring = 1;
  } else {
      cfg->dimm_dis_bg_mirroring = 0;
  } // _X16
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL,dimm_dis_bg_mirroring);
  
  if (DEV_DQ_WIDTH==16) {
      // PHY parity calculation always includes BG1.
      if ( hdlr->phy_training ) {
          cfg->mrs_bg1_en = 1;
      } else { // Not UMCTL2_PUB_FIRMWARE
          cfg->mrs_bg1_en = 0; // Not to include BG1 (BG0 of odd ranks) for parity calculation
      } 
  } else {
      cfg->mrs_bg1_en = 1;
  } // 
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL,mrs_bg1_en );


  if (IS_X4) {
      if(IS_DENS_16GBIT) {
          cfg->mrs_a17_en = 1;
      } else {
          cfg->mrs_a17_en = 0;
      } // IS_DENS_16GBIT
  } else {
      cfg->mrs_a17_en = 0;
  } // IS_X4  
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL,mrs_a17_en );
  //
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL, dimm_output_inv_en);
  
#endif // MEMC_DDR4
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL, dimm_addr_mirr_en);
  APPLY_CFG_TO_REGFIELD(cfg,DIMMCTL, dimm_stagger_cs_en);
  if (IS_UDIMM) {
    CONSTRAIN_MIN(reg->dimm_stagger_cs_en, 0);// No DDR4 staggering for UDIMM
#ifdef MEMC_NUM_RANKS_1
    CONSTRAIN_MIN(reg->dimm_addr_mirr_en, 0);  // no address mirroring for single rank
    CONSTRAIN_MIN(reg->dimm_dis_bg_mirroring, 0);
#endif
  }
  LOG_MESSAGE(hdlr, 1, ("DIMMCTL= 0x%x\n",reg->value ));
}

void cinit_prgm_OPCTRL0 (SubsysHdlr_t *hdlr) { 
  TRACE();
  REGB_DDRC_CH0_OPCTRL0_struct_t
      *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_OPCTRL0_reg;  

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  APPLY_CFG_TO_REGFIELD(cfg,OPCTRL0,dis_collision_page_opt);
#ifdef MEMC_BYPASS  
  APPLY_CFG_TO_REGFIELD(cfg,OPCTRL0,dis_act_bypass);
  CONSTRAIN_INSIDE(reg->dis_act_bypass, 0, 1);

  APPLY_CFG_TO_REGFIELD(cfg,OPCTRL0,dis_rd_bypass);
  CONSTRAIN_INSIDE(reg->dis_rd_bypass, 0, 1);
#endif // MEMC_BYPASS
  APPLY_CFG_TO_REGFIELD(cfg,OPCTRL0,dis_wc);
  CONSTRAIN_INSIDE(reg->dis_wc, 0, 1);
  LOG_MESSAGE(hdlr, 1, ("OPCTRL0= 0x%x\n",reg->value ));
}

void cinit_prgm_OPCTRL1 (SubsysHdlr_t *hdlr, uint32_t ch) { 
  TRACE();
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, OPCTRL1, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, OPCTRL1)
  DWC_DDRCTL_CAST_REG_DCHC(ch, REGB_DDRC, OPCTRL1, reg, _CH); 
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,OPCTRL1 ,dis_hif,ch );
  APPLY_CFG_TO_REGFIELD_P(dyn,OPCTRL1 ,dis_dq,ch );
  LOG_MESSAGE(hdlr, 1, ("ch=%0d, OPCTRL1= 0x%x\n",ch, reg->value ));
}

/** @brief  function to setup the register field values for PWRCTL. */
void cinit_prgm_PWRCTL(SubsysHdlr_t *hdlr, uint32_t ch) {
  TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to dynamic configuration options.
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PWRCTL, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PWRCTL)
  DWC_DDRCTL_CAST_REG_DCHC(ch, REGB_DDRC, PWRCTL, reg, _CH); 
#ifdef MEMC_LPDDR4
  APPLY_CFG_TO_REGFIELD_P(dyn,PWRCTL,lpddr4_sr_allowed,ch);
  CONSTRAIN_INSIDE(reg->lpddr4_sr_allowed, 0, 1);
#endif  
  APPLY_CFG_TO_REGFIELD_P(dyn,PWRCTL,dis_cam_drain_selfref,ch);
  CONSTRAIN_INSIDE(reg->dis_cam_drain_selfref, 0, 1);

#ifdef MEMC_LPDDR4
  APPLY_CFG_TO_REGFIELD_P(dyn,PWRCTL,stay_in_selfref,ch);
  CONSTRAIN_INSIDE(reg->stay_in_selfref , 0, 1);
#endif  

  APPLY_CFG_TO_REGFIELD_P(dyn,PWRCTL,selfref_sw,ch);
  CONSTRAIN_INSIDE(reg->selfref_sw, 0, 1);

#ifdef MEMC_DDR4
  APPLY_CFG_TO_REGFIELD_P(dyn,PWRCTL,mpsm_en,ch);
  CONSTRAIN_INSIDE(reg->mpsm_en, 0, 1);
#endif  

  APPLY_CFG_TO_REGFIELD_P(dyn,PWRCTL,en_dfi_dram_clk_disable,ch);
  CONSTRAIN_INSIDE(reg->en_dfi_dram_clk_disable, 0, 1);

  APPLY_CFG_TO_REGFIELD_P(dyn, PWRCTL,powerdown_en,ch);
  CONSTRAIN_INSIDE(reg->powerdown_en, 0, 1);

  APPLY_CFG_TO_REGFIELD_P(dyn,PWRCTL,selfref_en,ch);
  CONSTRAIN_INSIDE(reg->selfref_en, 0, 1);
  
  LOG_MESSAGE(hdlr, 1, ("PWRCTL= 0x%x\n",
               reg->value ));
  
}

/** @brief 
 * @note this function makes some decides of its own if MR7_BY_PHY is
 * set.
 * */
void cinit_prgm_HWFFCCTL (SubsysHdlr_t *hdlr) { 
#ifdef UMCTL2_HWFFC_EN
  TRACE();
  REGB_DDRC_CH0_HWFFCCTL_struct_t
      *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_HWFFCCTL_reg;

  /*mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);*/
 // mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  //mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
#ifdef MEMC_DDR4

  if(IS_DDR4) {
      if(IS_RDIMM) {
          if( MR7_BY_PHY) {
              // RDIMM: RCD01 or RCD02 Sequence A
              APPLYREGFIELD(reg->value,HWFFCCTL,init_vrcg ,1);
              APPLYREGFIELD(reg->value,HWFFCCTL,target_vrcg ,1);
              APPLYREGFIELD(reg->value,HWFFCCTL,ctrl_word_num ,0);
              APPLYREGFIELD(reg->value,HWFFCCTL,cke_power_down_mode ,0);
              APPLYREGFIELD(reg->value,HWFFCCTL,power_saving_ctrl_word ,0);
              //reg->init_vrcg = 1; // 1: CKE Power down mode in F0RC09 needs to be disabled BEFORE FFC
              //reg->target_vrcg = 1; // 1: CKE Power down mode in F0RC09 needs to be ensabled AFTER FFC
              //reg->ctrl_word_num = 0; // uMCTL2 does not send any MRS commands for RCD (MR7: Control Word)
              //reg->cke_power_down_mode = 1; //
              //reg->power_saving_ctrl_word = 0;	// [3] TODO: To be removed (actually RTL does not use this bit)
              // [2] 0: CKE powerdown with IBT ON                , 1: IBT OFF
              // [1] 0: DCS1 Input Buffer & QxCS1 Outputs Enabled, 1: Disabled
              // [0] 0: DCS1 Input Bus Termination        Enabled, 1: Disabled
          } else {// MR7_BY_PHY
              // RDIMM: RCD02 Sequence B
              APPLYREGFIELD(reg->value,HWFFCCTL,init_vrcg ,0);

              //reg->init_vrcg = 0;
              APPLY_CFG_TO_REGFIELD(dyn,HWFFCCTL ,ctrl_word_num );
              CONSTRAIN_INSIDE(reg->ctrl_word_num,2,8); // F0RC5x, F0RC3x and another commands are dummy for coverage.
              APPLYREGFIELD(reg->value,HWFFCCTL,cke_power_down_mode ,0);
              APPLYREGFIELD(reg->value,HWFFCCTL,power_saving_ctrl_word ,0);

              //reg->cke_power_down_mode = 0; // RCD02 Sequence B
              //reg->power_saving_ctrl_word = 0;
          } // MR7_BY_PHY
      } else { // IS_RDIMM
          // NODIMM, UDIMM
          APPLYREGFIELD(reg->value,HWFFCCTL,init_vrcg ,0);
          //reg->init_vrcg = 0;
          APPLY_CFG_TO_REGFIELD(dyn,HWFFCCTL ,ctrl_word_num );

          CONSTRAIN_INSIDE(reg->ctrl_word_num,0,1); // dummy command for coverage.
          APPLYREGFIELD(reg->value,HWFFCCTL,cke_power_down_mode ,0);
          APPLYREGFIELD(reg->value,HWFFCCTL,power_saving_ctrl_word ,0);
          
       //   reg->cke_power_down_mode = 0;
       //   reg->power_saving_ctrl_word = 0;
      } // IS_RDIMM
  } else { // IS_DDR4
      // For LPDDR4 : TODO this should be randomized if possible
      reg->init_vrcg = 0;
  } // IS_DDR4
}

#endif
  LOG_MESSAGE(hdlr, 1, ("HWFFCCTL= 0x%x\n",reg->value ));
#endif
}

/** @brief function to setup the register field values for INITTMG0 
 * */
void cinit_prgm_INITTMG0 (SubsysHdlr_t *hdlr,uint32_t dch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT( , 0, REGB_DDRC, INITTMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, INITTMG0)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, INITTMG0, reg, _CH); 

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  //
  APPLY_CFG_TO_REGFIELD_P(qdyn,INITTMG0 ,skip_dram_init,dch);
  CONSTRAIN_INSIDE(reg->skip_dram_init, 0, 3);
  ASSERT(reg->skip_dram_init!=2); // 2'b10 is reserved value


  APPLY_CFG_TO_REGFIELD_P(cfg,INITTMG0 ,pre_cke_x1024 ,dch);
  // define pre_cke_x1024 to be a minimum of 2 in the following cases :
  // ------------------------------------------------------
  // if reg->pre_cke_x1024 = 1, the actual time is between 1 and 1023.
  // When TI_RCD, CK is not stabled at beginning, and VIOLATION: cmdPDX are issued.
  if (USE_TI_RCD) {
    CONSTRAIN_MIN(reg->pre_cke_x1024, 2);
  }
  if(hdlr->use_snps_vip_timing) {
      if (IS_LPDDR4 || IS_LPDDR5 ) {
        CONSTRAIN_MIN(reg->pre_cke_x1024, 2);
      }

      if (IS_DDR4) {
        if (!hdlr->use_jedec_init) {
          CONSTRAIN_MIN(reg->pre_cke_x1024, 2);
        }
      }
  }
  if(hdlr->use_jedec_init) {
      // Ensure Real Initialization Timing
      if (IS_DDR4) {
          // after reset is de-ASSERTed, wait for 500us
          cfg->pre_cke_x1024[dch] = 500000000/(GET_TCK(0) * MEMC_FREQ_RATIO * 1024) + 1;
      } else if (IS_LPDDR4 || IS_LPDDR5 ) {
          // after reset is de-ASSERTed, wait for 2 ms (tINITTMG2)
          // use tCKb instead of tCK when the slow boot clock is enabled (Bugzilla 4012)
          cfg->pre_cke_x1024[dch] = 2000000000/(GET_TCK(0) * MEMC_FREQ_RATIO * 1024) + 1;
          // tINITTMG0 ? or tINITTMG0 + tINITTMG1 ?
      } else if (IS_LPDDR23) {
          // CKE must remain LOW for 100 ns (tINITTMG1 - LPDDR23)
          cfg->pre_cke_x1024[dch] = 100000/(GET_TCK(0) * MEMC_FREQ_RATIO * 1024) + 1;
      } 
     APPLY_CFG_TO_REGFIELD_P(cfg,INITTMG0 ,pre_cke_x1024 ,dch);

  } else {
      CONSTRAIN_INSIDE(reg->pre_cke_x1024,2,4095);
  }  
  
//
// post_cke_x1024
  if (hdlr->use_jedec_init) {
#ifdef MEMC_DDR4
      // Ensure Real Initialization Timing
      if (IS_DDR4) {
          // after CKE is high, wait tXPR ( tXPR = max (5tCK, tXS)), before issuing the first MRS
          // tXS = tRFCmin + 10ns
          cfg->post_cke_x1024[dch] = (TRFC_MIN(0) + 10000)/(1024 * GET_TCK(0) * MEMC_FREQ_RATIO) + 1;
      }
#endif
#ifdef MEMC_LPDDR4
      if (IS_LPDDR4 || IS_LPDDR5 ) {
          // LPDDR4 : after CKE is high, wait tINITTMG5 (2 us), before issuing the MRR or MRW
          // use tCKb instead of tCK when the slow boot clock is enabled (Bugzilla 4012)
          cfg->post_cke_x1024[dch] = 2000000/(GET_TCK(0) * MEMC_FREQ_RATIO * 1024) +1;
      } 
#endif
     APPLY_CFG_TO_REGFIELD_P(cfg,INITTMG0 ,pre_cke_x1024 ,dch);

  } else {


      if (IS_LPDDR23) {
          // For LPDDR2, need to ensure must be > tXP = 10ns
          //reg->post_cke_x1024 > 10000/(1024 * GET_TCK(0) * MEMC_FREQ_RATIO) + 1;
          CONSTRAIN_MIN(reg->post_cke_x1024, 10000/(1024 * GET_TCK(0) * MEMC_FREQ_RATIO));
      }
  }
  APPLY_CFG_TO_REGFIELD_P(cfg,INITTMG0 , post_cke_x1024,dch);
  LOG_MESSAGE(hdlr, 1, ("INITTMG0[%0d]= 0x%x\n",dch, reg->value ));
}

void cinit_prgm_INITTMG1 (SubsysHdlr_t *hdlr,uint32_t dch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT( , 0, REGB_DDRC, INITTMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, INITTMG1)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, INITTMG1, reg, _CH); 

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  // Ensure Real Initialization Timing
  if (hdlr->use_jedec_init) {
      // reset should be maintained for 200us
      // use tCKb instead of tCK when the slow boot clock is enabled (Bugzilla 4012)
      cfg->dram_rstn_x1024[dch] = 200000000/(GET_TCK(0) * MEMC_FREQ_RATIO * 1024) + 1;
  } 
  //dwc_cinit_print("hdlr->use_jedec_init =%0d\n",hdlr->use_jedec_init );
  //dwc_cinit_print("cfg->dram_rstn_x1024=%0d\n", cfg->dram_rstn_x1024);
  APPLY_CFG_TO_REGFIELD_P(cfg,INITTMG1 ,dram_rstn_x1024,dch);
  if(hdlr->use_snps_vip_timing) {
      CONSTRAIN_NE(reg->dram_rstn_x1024, 0);      
  }  

  LOG_MESSAGE(hdlr, 1, ("INITTMG1[%0d]= 0x%x\n",dch, reg->value ));
}

/** @brief Setup register values for INITTMG2 */
void cinit_prgm_INITTMG2 (SubsysHdlr_t *hdlr,uint32_t dch){
  TRACE();
#ifdef MEMC_DDR4
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_FREQ_REG_STRUCT( , 0, REGB_DDRC, INITTMG2, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, INITTMG2)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, INITTMG2, reg, _CH); 

  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[0]);
  if(IS_DDR4) {
    cfg->dev_zqinit_x32[dch] = timing->ddr4_tzqinit_tck/32 + 1;
  } else if(IS_DDR5) {
    cfg->dev_zqinit_x32[dch] = 0;
  }
  APPLY_CFG_TO_REGFIELD_P(cfg,INITTMG2,dev_zqinit_x32,dch);
  CONSTRAIN_MAX(reg->dev_zqinit_x32,255);
  LOG_MESSAGE(hdlr,1,("INITTMG2[%0d]=0x%x\n",dch,reg->value));
#endif
}

void cinit_prgm_MSTR4 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_LPDDR
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, MSTR4, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, MSTR4)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, MSTR4, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(qdyn,MSTR4,wck_on,dch);
  // mode register are per frequency but MSTR4 is per channel
  CONSTRAIN_EQ(reg->wck_on , hdlr->memCtrlr_m.lpddr5_mr[0].mr18.wck_on);

  LOG_MESSAGE(hdlr,1,("MSTR4[%0d]=0x%x\n",dch,reg->value));
#endif //DDRCTL_LPDDR

}
void cinit_prgm_MRCTRL1 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); 
  
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, MRCTRL1, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, MRCTRL1)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, MRCTRL1, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,MRCTRL1,mr_data,dch);

  LOG_MESSAGE(hdlr, 1, ("MRCTRL1[%0d]= 0x%x\n",dch,reg->value ));

}
void cinit_prgm_MRCTRL2 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_DDR
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); 
  
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, MRCTRL2, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, MRCTRL2)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, MRCTRL2, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,MRCTRL2,mr_device_sel,dch);

  LOG_MESSAGE(hdlr, 1, ("MRCTRL2[%0d]= 0x%x\n",dch,reg->value ));
#endif //DDRCTL_DDR

}
void cinit_prgm_MRCTRL3 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifndef MEMC_NUM_RANKS_1_OR_2_OR_4 
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); 
  
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, MRCTRL3, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, MRCTRL3)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, MRCTRL3, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,MRCTRL3,mr_rank_sel,dch);

  LOG_MESSAGE(hdlr, 1, ("MRCTRL3[%0d]= 0x%x\n",dch,reg->value ));
#endif //!MEMC_NUM_RANKS_1_OR_2_OR_4

}
void cinit_prgm_ADVECCINDEX (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef MEMC_ECC_SUPPORT_GT_0
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.
  mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);

  REGB_DDRC_CH0_ADVECCINDEX_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ADVECCINDEX_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,ADVECCINDEX,ecc_poison_beats_sel);
  APPLY_CFG_TO_REGFIELD(qdyn,ADVECCINDEX,ecc_err_symbol_sel);    
  //ADVECCSTAT.advecc_num_err_symbol is read only field so will be constrained in mss_config_constraint.svh
  APPLY_CFG_TO_REGFIELD(qdyn,ADVECCINDEX,ecc_syndrome_sel);   

  LOG_MESSAGE(hdlr,1,("ADVECCINDEX=0x%x\n",reg->value));
#endif //MEMC_ECC_SUPPORT_GT_0

}
void cinit_prgm_OCPARCFG0 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef UMCTL2_OCPAR_OR_OCECC_EN_1
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.
  mctl_dyn_cfg_t* dyn   = &(hdlr->memCtrlr_m.dyn_cfg); 

  REGB_DDRC_CH0_OCPARCFG0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_OCPARCFG0_reg;

  APPLY_CFG_TO_REGFIELD_P(qdyn,OCPARCFG0,oc_parity_en,dch);
  APPLY_CFG_TO_REGFIELD_P(qdyn,OCPARCFG0,oc_parity_type,dch);
#ifdef UMCTL2_OCPAR_EN_1
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_wdata_err_intr_en,dch);
  APPLY_CFG_TO_REGFIELD_P(qdyn,OCPARCFG0,par_wdata_slverr_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_wdata_err_intr_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_wdata_err_intr_force,dch);
  APPLY_CFG_TO_REGFIELD_P(qdyn,OCPARCFG0,par_rdata_slverr_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_rdata_err_intr_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_rdata_err_intr_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_rdata_err_intr_force,dch);
#endif //UMCTL2_OCPAR_EN_1
  APPLY_CFG_TO_REGFIELD_P(qdyn,OCPARCFG0,par_addr_slverr_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_waddr_err_intr_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_waddr_err_intr_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_raddr_err_intr_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_raddr_err_intr_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_waddr_err_intr_force,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,OCPARCFG0,par_raddr_err_intr_force,dch);

  LOG_MESSAGE(hdlr,1,("OCPARCFG0[%0d]=0x%x\n",dch,reg->value));
#endif //UMCTL2_OCPAR_OR_OCECC_EN_1

}
void cinit_prgm_OCSAPCFG0 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_OCSAP_EN_1
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  REGB_DDRC_CH0_OCSAPCFG0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_OCSAPCFG0_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,OCSAPCFG0,ocsap_par_en);
  APPLY_CFG_TO_REGFIELD(qdyn,OCSAPCFG0,ocsap_poison_en);
  APPLY_CFG_TO_REGFIELD(qdyn,OCSAPCFG0,wdataram_addr_poison_loc);
  APPLY_CFG_TO_REGFIELD(qdyn,OCSAPCFG0,rdataram_addr_poison_loc);
  APPLY_CFG_TO_REGFIELD(qdyn,OCSAPCFG0,wdataram_addr_poison_ctl);
  APPLY_CFG_TO_REGFIELD(qdyn,OCSAPCFG0,rdataram_addr_poison_ctl);
  APPLY_CFG_TO_REGFIELD(qdyn,OCSAPCFG0,rdataram_addr_poison_port);

  LOG_MESSAGE(hdlr,1,("OCSAPCFG0=0x%x\n",reg->value));
#endif //DDRCTL_OCSAP_EN_1

}
void cinit_prgm_OCPARCFG1 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef UMCTL2_OCPAR_EN_1
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  REGB_DDRC_CH0_OCPARCFG1_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_OCPARCFG1_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,OCPARCFG1,par_poison_en);
  APPLY_CFG_TO_REGFIELD(qdyn,OCPARCFG1,par_poison_loc_rd_dfi);
#ifdef MEMC_INLINE_ECC
  APPLY_CFG_TO_REGFIELD(qdyn,OCPARCFG1,par_poison_loc_rd_iecc_type);
#endif //MEMC_INLINE_ECC
  APPLY_CFG_TO_REGFIELD(qdyn,OCPARCFG1,par_poison_loc_rd_port);
  APPLY_CFG_TO_REGFIELD(qdyn,OCPARCFG1,par_poison_loc_wr_port);
#ifndef MEMC_INLINE_ECC
  APPLY_CFG_TO_REGFIELD(qdyn,OCPARCFG1,par_poison_byte_num);
#endif //!MEMC_INLINE_ECC

  LOG_MESSAGE(hdlr,1,("OCPARCFG1=0x%x\n",reg->value));
#endif //UMCTL2_OCPAR_EN_1

}

/** @brief  function to setup the register field values for DERATECTL5.*/
void cinit_prgm_DERATECTL5(SubsysHdlr_t *hdlr, uint32_t ch) {
  TRACE();
#ifdef MEMC_LPDDR2
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, DERATECTL5, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, DERATECTL5)
  DWC_DDRCTL_CAST_REG_DCHC(ch, REGB_DDRC, DERATECTL5, reg, _CH); 

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to quasi-dynamci configuration options.
  APPLY_CFG_TO_REGFIELD_P(cfg, DERATECTL5, derate_temp_limit_intr_en, ch);
      
  //reg->derate_temp_limit_intr_en=cfg->derate_temp_limit_intr_en;
  //APPLYREGFIELD(reg->value,DERATECTL5,derate_temp_limit_intr_en,reg->derate_temp_limit_intr_en);

  LOG_MESSAGE(hdlr, 1, ("DERATECTL5[%0d]= 0x%x\n",
               ch,reg->value ));

#endif
}

void cinit_prgm_DERATECTL6 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_LPDDR
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  REGB_DDRC_CH0_DERATECTL6_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DERATECTL6_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,DERATECTL6,derate_mr4_tuf_dis);

  LOG_MESSAGE(hdlr,1,("DERATECTL6=0x%x\n",reg->value));
#endif //DDRCTL_LPDDR
}

void cinit_prgm_ZQCTL1 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_LPDDR
  mctl_dyn_cfg_t* dyn   = &(hdlr->memCtrlr_m.dyn_cfg); 

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, ZQCTL1, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, ZQCTL1)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, ZQCTL1, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,ZQCTL1,zq_reset,dch);

  LOG_MESSAGE(hdlr,1,("ZQCTL1[%0d]=0x%x\n",dch,reg->value));
#endif //DDRCTL_LPDDR

}
void cinit_prgm_DQSOSCRUNTIME (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef LPDDR45_DQSOSC_EN
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  REGB_DDRC_CH0_DQSOSCRUNTIME_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DQSOSCRUNTIME_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,DQSOSCRUNTIME,dqsosc_runtime); 
  CONSTRAIN_INSIDE(reg->dqsosc_runtime,1,255); //Ranges from 16 to 8K DRAM clock cycles
  APPLY_CFG_TO_REGFIELD(qdyn,DQSOSCRUNTIME,wck2dqo_runtime);
  CONSTRAIN_INSIDE(reg->wck2dqo_runtime,1,255); //Ranges from 16 to 8K DRAM clock cycles

  LOG_MESSAGE(hdlr,1,("DQSOSCRUNTIME=0x%x\n",reg->value));
#endif //LPDDR45_DQSOSC_EN
}
void cinit_prgm_SCHED1 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef MEMC_ENH_CAM_PTR
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  REGB_DDRC_CH0_SCHED1_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_SCHED1_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,SCHED1,page_hit_limit_rd);
  CONSTRAIN_INSIDE(reg->page_hit_limit_rd,0,4); 
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED1,page_hit_limit_wr);
  CONSTRAIN_INSIDE(reg->page_hit_limit_wr,0,4); 
#ifdef UMCTL2_VPR_EN
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED1,visible_window_limit_rd);
  CONSTRAIN_INSIDE(reg->visible_window_limit_rd,0,4); 
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED1,visible_window_limit_wr);
  CONSTRAIN_INSIDE(reg->visible_window_limit_wr,0,4); 
#endif //UMCTL2_VPR_EN
#ifdef MEMC_ENH_RDWR_SWITCH
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED1,delay_switch_write);
#endif //MEMC_ENH_RDWR_SWITCH
  LOG_MESSAGE(hdlr,1,("SCHED1=0x%x\n",reg->value));
#endif //MEMC_ENH_CAM_PTR
}
void cinit_prgm_SCHED2 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef UMCTL2_DYN_BSM
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);
  REGB_DDRC_CH0_SCHED2_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_SCHED2_reg;

  uint32_t min_val;

  APPLY_CFG_TO_REGFIELD(scfg,SCHED2,dealloc_num_bsm_m1);          
  APPLY_CFG_TO_REGFIELD(scfg,SCHED2,dealloc_bsm_thr);
  min_val = (UMCTL2_NUM_BSM/2)+1 ;//Minimum supported value is UMCTL2_NUM_BSM/2+1
  CONSTRAIN_MIN(reg->dealloc_bsm_thr,min_val);
  APPLY_CFG_TO_REGFIELD(scfg,SCHED2,dyn_bsm_mode);

  LOG_MESSAGE(hdlr,1,("SCHED2=0x%x\n",reg->value));
#endif //UMCTL2_DYN_BSM
}
void cinit_prgm_SCHED3 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef MEMC_ENH_RDWR_SWITCH
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  REGB_DDRC_CH0_SCHED3_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_SCHED3_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,SCHED3,rd_pghit_num_thresh);
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED3,wr_pghit_num_thresh);
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED3,wrcam_highthresh);
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED3,wrcam_lowthresh);
  CONSTRAIN_MIN(reg->wrcam_lowthresh,reg->wrcam_highthresh);

  LOG_MESSAGE(hdlr,1,("SCHED3=0x%x\n",reg->value));
#endif //MEMC_ENH_RDWR_SWITCH
}
void cinit_prgm_SCHED4 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef MEMC_ENH_RDWR_SWITCH
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  REGB_DDRC_CH0_SCHED4_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_SCHED4_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,SCHED4,wr_page_exp_cycles);
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED4,rd_page_exp_cycles);;
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED4,wr_act_idle_gap);
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED4,rd_act_idle_gap);;

  LOG_MESSAGE(hdlr,1,("SCHED4=0x%x\n",reg->value));
#endif //MEMC_ENH_RDWR_SWITCH
}
void cinit_prgm_SCHED5 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef MEMC_ENH_RDWR_SWITCH
#ifdef MEMC_INLINE_ECC
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  REGB_DDRC_CH0_SCHED5_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_SCHED5_reg;

  APPLY_CFG_TO_REGFIELD(qdyn,SCHED5,wrecc_cam_highthresh);
  CONSTRAIN_MAX(reg->wrecc_cam_highthresh,((1<<(MEMC_WRCMD_ENTRY_BITS-1))-1));
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED5,wrecc_cam_lowthresh);
  CONSTRAIN_MIN(reg->wrecc_cam_lowthresh,reg->wrecc_cam_highthresh);
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED5,dis_opt_valid_wrecc_cam_fill_level);
  CONSTRAIN_INSIDE(reg->dis_opt_valid_wrecc_cam_fill_level,0,1);
  APPLY_CFG_TO_REGFIELD(qdyn,SCHED5,dis_opt_loaded_wrecc_cam_fill_level);
  CONSTRAIN_INSIDE(reg->dis_opt_loaded_wrecc_cam_fill_level,0,1);

  LOG_MESSAGE(hdlr,1,("SCHED5=0x%x\n",reg->value));
#endif //MEMC_INLINE_ECC
#endif //MEMC_ENH_RDWR_SWITCH
}
void cinit_prgm_DFILPCFG0 (SubsysHdlr_t *hdlr) {
  TRACE();
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_DFILPCFG0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DFILPCFG0_reg;

  APPLY_CFG_TO_REGFIELD(scfg,DFILPCFG0,dfi_lp_data_req_en);
  APPLY_CFG_TO_REGFIELD(scfg,DFILPCFG0,dfi_lp_en_data);
#ifdef DDRCTL_DDR
  APPLY_CFG_TO_REGFIELD(scfg,DFILPCFG0,dfi_lp_en_mpsm);
  APPLY_CFG_TO_REGFIELD(scfg,DFILPCFG0,dfi_lp_extra_gap_wr);
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
  APPLY_CFG_TO_REGFIELD(scfg,DFILPCFG0,dfi_lp_en_dsm);
#endif //DDRCTL_LPDDR
  APPLY_CFG_TO_REGFIELD(scfg,DFILPCFG0,dfi_lp_en_sr);
  APPLY_CFG_TO_REGFIELD(scfg,DFILPCFG0,dfi_lp_en_pd);
  LOG_MESSAGE(hdlr,1,("DFILPCFG0=0x%x\n",reg->value));

}
void cinit_prgm_DFIUPD1 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef UMCTL2_DFI_PHYUPD_WAIT_IDLE
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_DFIUPD1_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DFIUPD1_reg;

  APPLY_CFG_TO_REGFIELD(scfg,DFIUPD1,dfi_phyupd_type3_wait_idle);
  APPLY_CFG_TO_REGFIELD(scfg,DFIUPD1,dfi_phyupd_type2_wait_idle);
  APPLY_CFG_TO_REGFIELD(scfg,DFIUPD1,dfi_phyupd_type1_wait_idle);
  APPLY_CFG_TO_REGFIELD(scfg,DFIUPD1,dfi_phyupd_type0_wait_idle);

  LOG_MESSAGE(hdlr,1,("DFIUPD1=0x%x\n",reg->value));
#endif //UMCTL2_DFI_PHYUPD_WAIT_IDLE
}
void cinit_prgm_CRCPARCTL0 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef UMCTL2_CRC_PARITY_RETRY
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);
#endif //UMCTL2_CRC_PARITY_RETRY
  mctl_dyn_cfg_t* dyn     = &(hdlr->memCtrlr_m.dyn_cfg); 

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, CRCPARCTL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, CRCPARCTL0)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, CRCPARCTL0, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPARCTL0,rd_crc_err_cnt_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPARCTL0,rd_crc_err_max_reached_int_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPARCTL0,rd_crc_err_max_reached_int_en,dch);
#ifdef UMCTL2_CRC_PARITY_RETRY
  APPLY_CFG_TO_REGFIELD_P(scfg,CRCPARCTL0,retry_ctrlupd_wait,dch);
  APPLY_CFG_TO_REGFIELD_P(scfg,CRCPARCTL0,retry_ctrlupd_enable,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPARCTL0,dfi_alert_err_max_reached_int_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPARCTL0,dfi_alert_err_fatl_int_clr,dch);
#endif //UMCTL2_CRC_PARITY_RETRY
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPARCTL0,dfi_alert_err_cnt_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPARCTL0,dfi_alert_err_int_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPARCTL0,dfi_alert_err_int_en,dch);

  LOG_MESSAGE(hdlr,1,("CRCPARCTL0[%0d]=0x%x\n",dch,reg->value));
}
void cinit_prgm_CRCPARCTL1 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_DDR
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_CRCPARCTL1_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_CRCPARCTL1_reg;
#ifdef UMCTL2_CRC_PARITY_RETRY
  APPLY_CFG_TO_REGFIELD(qdyn,CRCPARCTL1,dfi_t_phy_rdlat);
#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef UMCTL2_RETRY_MAX_ADD_RD_LAT_EN
  APPLY_CFG_TO_REGFIELD(qdyn,CRCPARCTL1,retry_add_rd_lat);
  APPLY_CFG_TO_REGFIELD(qdyn,CRCPARCTL1,retry_add_rd_lat_en);
#endif //UMCTL2_RETRY_MAX_ADD_RD_LAT_EN
  APPLY_CFG_TO_REGFIELD(scfg,CRCPARCTL1,caparity_disable_before_sr);
#ifdef UMCTL2_CRC_PARITY_RETRY
  APPLY_CFG_TO_REGFIELD(scfg,CRCPARCTL1,alert_wait_for_sw);
  APPLY_CFG_TO_REGFIELD(scfg,CRCPARCTL1,crc_parity_retry_enable);
#endif //UMCTL2_CRC_PARITY_RETRY
  APPLY_CFG_TO_REGFIELD(scfg,CRCPARCTL1,crc_inc_dm);
  APPLY_CFG_TO_REGFIELD(qdyn,CRCPARCTL1,wr_crc_enable);
#ifdef MEMC_DDR5
  APPLY_CFG_TO_REGFIELD(qdyn,CRCPARCTL1,rd_crc_enable);
#endif //MEMC_DDR5
  APPLY_CFG_TO_REGFIELD(scfg,CRCPARCTL1,parity_enable);

  LOG_MESSAGE(hdlr,1,("CRCPARCTL1=0x%x\n",reg->value));
#endif //DDRCTL_DDR
}
void cinit_prgm_CRCPARCTL2 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_DDR
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_CRCPARCTL2_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_CRCPARCTL2_reg;

  APPLY_CFG_TO_REGFIELD(scfg,CRCPARCTL2,rd_crc_err_max_reached_th);  
  CONSTRAIN_NE(reg->rd_crc_err_max_reached_th,0);//0 is an illegal setting for this register
#ifdef UMCTL2_CRC_PARITY_RETRY
  APPLY_CFG_TO_REGFIELD(scfg,CRCPARCTL2,dfi_alert_err_max_reached_th);  
  CONSTRAIN_NE(reg->dfi_alert_err_max_reached_th,0);//0 is an illegal setting for this register
#endif //UMCTL2_CRC_PARITY_RETRY

  LOG_MESSAGE(hdlr,1,("CRCPARCTL2=0x%x\n",reg->value));
#endif //DDRCTL_DDR
}
void cinit_prgm_CRCPOISONCTL0 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_DDR
  mctl_dyn_cfg_t* dyn     = &(hdlr->memCtrlr_m.dyn_cfg); 

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, CRCPOISONCTL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, CRCPOISONCTL0)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, CRCPOISONCTL0, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPOISONCTL0,crc_poison_nibble,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPOISONCTL0,crc_poison_type,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,CRCPOISONCTL0,crc_poison_inject_en,dch);

  LOG_MESSAGE(hdlr,1,("CRCPOISONCTL0[%0d]=0x%x\n",dch,reg->value));
#endif //DDRCTL_DDR
}
void cinit_prgm_CAPARPOISONCTL (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
  mctl_dyn_cfg_t* dyn     = &(hdlr->memCtrlr_m.dyn_cfg); 

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, CAPARPOISONCTL, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, CAPARPOISONCTL)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, CAPARPOISONCTL, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,CAPARPOISONCTL,capar_poison_cmdtype,dch);  //TOD value 3 is reserved
  APPLY_CFG_TO_REGFIELD_P(dyn,CAPARPOISONCTL,capar_poison_inject_en,dch);

  LOG_MESSAGE(hdlr,1,("CAPARPOISONCTL[%0d]=0x%x\n",dch,reg->value));
#endif //UMCTL2_CRC_PARITY_RETRY
#endif //DDRCTL_DDR
}

void cinit_prgm_LNKECCCTL0 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef MEMC_LINK_ECC
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, LNKECCCTL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, LNKECCCTL0)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, LNKECCCTL0, reg, _CH);

  APPLY_CFG_TO_REGFIELD_P(qdyn,LNKECCCTL0,rd_link_ecc_enable,dch);
  APPLY_CFG_TO_REGFIELD_P(qdyn,LNKECCCTL0,wr_link_ecc_enable,dch);

  LOG_MESSAGE(hdlr,1,("LNKECCCTL0[%0d]=0x%x\n",dch,reg->value));
#endif // MEMC_LINK_ECC
}
void cinit_prgm_LNKECCCTL1 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef MEMC_LINK_ECC
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to quasi-dynamic configuration options.

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, LNKECCCTL1, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, LNKECCCTL1)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, LNKECCCTL1, reg, _CH);

  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCCTL1,rd_link_ecc_uncorr_cnt_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCCTL1,rd_link_ecc_uncorr_intr_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCCTL1,rd_link_ecc_uncorr_intr_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCCTL1,rd_link_ecc_corr_cnt_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCCTL1,rd_link_ecc_corr_intr_clr,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCCTL1,rd_link_ecc_corr_intr_en,dch);

  LOG_MESSAGE(hdlr,1,("LNKECCCTL1[%0d]=0x%x\n",dch,reg->value));
#endif // MEMC_LINK_ECC
}
void cinit_prgm_LNKECCPOISONCTL0 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef MEMC_LINK_ECC
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to quasi-dynamic configuration options.

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, LNKECCPOISONCTL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, LNKECCPOISONCTL0)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, LNKECCPOISONCTL0, reg, _CH);

  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCPOISONCTL0,linkecc_poison_byte_sel,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCPOISONCTL0,linkecc_poison_dmi_sel,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCPOISONCTL0,linkecc_poison_rw,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCPOISONCTL0,linkecc_poison_type,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,LNKECCPOISONCTL0,linkecc_poison_inject_en,dch);

  LOG_MESSAGE(hdlr,1,("LNKECCPOISONCTL0[%0d]=0x%x\n",dch,reg->value));
#endif // MEMC_LINK_ECC
}
void cinit_prgm_LNKECCINDEX (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef MEMC_LINK_ECC
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, LNKECCINDEX, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, LNKECCINDEX)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, LNKECCINDEX, reg, _CH);
#ifdef MEMC_NUM_RANKS_GT_1
  APPLY_CFG_TO_REGFIELD_P(qdyn,LNKECCINDEX,rd_link_ecc_err_rank_sel,dch);
#endif
  APPLY_CFG_TO_REGFIELD_P(qdyn,LNKECCINDEX,rd_link_ecc_err_byte_sel,dch);

  LOG_MESSAGE(hdlr,1,("LNKECCINDEX[%0d]=0x%x\n",dch,reg->value));
#endif // MEMC_LINK_ECC
}
void cinit_prgm_PASCTL0 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  mctl_dyn_cfg_t* dyn     = &(hdlr->memCtrlr_m.dyn_cfg); 

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL0)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL0, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL0,bist_st_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL0,dbg_st_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL0,init_done,dch);

  LOG_MESSAGE(hdlr,1,("PASCTL0[%0d]=0x%x\n",dch,reg->value));
#endif //MEMC_DDR5
}
void cinit_prgm_PASCTL2 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5

  mctl_dyn_cfg_t* dyn     = &(hdlr->memCtrlr_m.dyn_cfg); 

  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL2, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL2)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL2, reg, _CH); 

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL2,t_ppd_cnt_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL2,lrank_wr2rd_gap,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL2,lrank_rd2wr_gap,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL2,lrank_wr2wr_gap,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL2,lrank_rd2rd_gap,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL2,active_prank_bitmap,dch);

  LOG_MESSAGE(hdlr,1,("PASCTL2[%0d]=0x%x\n",dch,reg->value));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL4(SubsysHdlr_t *hdlr, uint32_t ch) {
#ifdef MEMC_DDR5
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.

  DWC_DDRCTL_DECLARE_DCHC_DDRC_REG_PTRS(PASCTL4)
  reg =&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_PASCTL4_reg;

  if(ch!=0) {
    DWC_DDRCTL_CAST_DDRC_REG_DCH(ch,PASCTL4);
  }

  APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL4,ci_mrr_des1,ch);
  
  APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL4,ci_mrr_des2,ch);

  APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL4,ci_mrw_des1,ch);
  
  APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL4,ci_mrw_des2,ch);

  LOG_MESSAGE(hdlr, 1, ("PASCTL4[%0d]= 0x%x\n",ch,reg->value ));

#endif
}

void cinit_prgm_CMDCFG (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
}
void cinit_prgm_CMDCTL (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
}
void cinit_prgm_CMDEXTCTL (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
}
void cinit_prgm_SWCTL (SubsysHdlr_t *hdlr) { 
  TRACE();
}
void cinit_prgm_SWCTLSTATIC (SubsysHdlr_t *hdlr) {
  TRACE();
}
void cinit_prgm_CHCTL (SubsysHdlr_t *hdlr) {
  TRACE();
  #ifdef DDRCTL_CHCTL
  REGB_DDRC_CH0_MSTR0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_CHCTL_reg;
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.
  
  APPLY_CFG_TO_REGFIELD_P(cfg,CHCTL,dual_channel_en);
  #endif
}
void cinit_prgm_ODTMAP (SubsysHdlr_t *hdlr, uint32_t dch) {
#ifdef MEMC_DDR5
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);  
  DWC_DDRCTL_DECLARE_DCHC_DDRC_REG_PTRS(ODTMAP)
  reg = &hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_ODTMAP_reg;

  if(dch!=0){
    DWC_DDRCTL_CAST_DDRC_REG_DCH(dch,ODTMAP);
  }

  APPLY_CFG_TO_REGFIELD_P(cfg,ODTMAP,rank0_wr_odt,dch);
  APPLY_CFG_TO_REGFIELD_P(cfg,ODTMAP,rank0_rd_odt,dch);

#ifdef MEMC_NUM_RANKS_GT_1 
  APPLY_CFG_TO_REGFIELD_P(cfg,ODTMAP,rank1_wr_odt,dch);
  APPLY_CFG_TO_REGFIELD_P(cfg,ODTMAP,rank1_rd_odt,dch);
#endif

#ifdef MEMC_NUM_RANKS_GT_2 
  APPLY_CFG_TO_REGFIELD_P(cfg,ODTMAP,rank2_wr_odt,dch);
  APPLY_CFG_TO_REGFIELD_P(cfg,ODTMAP,rank2_rd_odt,dch);
  APPLY_CFG_TO_REGFIELD_P(cfg,ODTMAP,rank3_wr_odt,dch);
  APPLY_CFG_TO_REGFIELD_P(cfg,ODTMAP,rank3_rd_odt,dch);
#endif
  
  LOG_MESSAGE(hdlr,1,("ODTMAP[%0d] = 0x%x\n",dch,reg->value));

#endif
}

void cinit_prgm_DQSOSCCFG0 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef LPDDR45_DQSOSC_EN
  REGB_DDRC_CH0_DQSOSCCFG0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DQSOSCCFG0_reg;
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD(qdyn,DQSOSCCFG0,dis_dqsosc_srx);

  LOG_MESSAGE(hdlr, 1, ("DQSOSCCFG0 = 0x%x\n",reg->value ));
#endif //LPDDR45_DQSOSC_EN
}

void cinit_prgm_PASCTL5 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL5, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL5)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL5, reg, _CH);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL5,base_timer_en,dch);

  LOG_MESSAGE(hdlr, 1, ("PASCTL5 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL6 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL6, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL6)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL6, reg, _CH);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL6,base_timer,dch);

  LOG_MESSAGE(hdlr, 1, ("PASCTL6 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL7 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL7, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL7)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL7, reg, _CH);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL7,glb_blk0_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL7,glb_blk1_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL7,glb_blk2_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL7,glb_blk3_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL7,glb_blk4_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL7,glb_blk5_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL7,glb_blk6_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL7,glb_blk7_en,dch);

  LOG_MESSAGE(hdlr, 1, ("PASCTL7 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL8 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL8, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL8)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL8, reg, _CH);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk0_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk1_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk2_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk3_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk4_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk5_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk6_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk7_en,dch);
#ifdef MEMC_NUM_RANKS_GT_1
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk8_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk9_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk10_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk11_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk12_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk13_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk14_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk15_en,dch);
#endif //MEMC_NUM_RANKS_GT_1

#ifdef MEMC_NUM_RANKS_GT_2
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk16_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk17_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk18_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk19_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk20_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk21_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk22_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk23_en,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk24_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk25_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk26_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk27_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk28_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk29_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk30_en,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL8,rank_blk31_en,dch);
#endif //MEMC_NUM_RANKS_GT_2
  LOG_MESSAGE(hdlr, 1, ("PASCTL8 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL9 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL9, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL9)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL9, reg, _CH);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL9,glb_blk0_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL9,glb_blk1_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL9,glb_blk2_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL9,glb_blk3_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL9,glb_blk4_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL9,glb_blk5_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL9,glb_blk6_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL9,glb_blk7_trig,dch);

  LOG_MESSAGE(hdlr, 1, ("PASCTL9 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL10 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL10, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL10)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL10, reg, _CH);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk0_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk1_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk2_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk3_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk4_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk5_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk6_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk7_trig,dch);
#ifdef MEMC_NUM_RANKS_GT_1
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk8_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk9_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk10_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk11_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk12_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk13_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk14_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk15_trig,dch);
#endif //MEMC_NUM_RANKS_GT_1

#ifdef MEMC_NUM_RANKS_GT_2
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk16_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk17_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk18_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk19_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk20_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk21_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk22_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk23_trig,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk24_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk25_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk26_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk27_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk28_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk29_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk30_trig,dch);
  APPLY_CFG_TO_REGFIELD_P(dyn,PASCTL10,rank_blk31_trig,dch);
#endif //MEMC_NUM_RANKS_GT_2

  LOG_MESSAGE(hdlr, 1, ("PASCTL10 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL11 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL11, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL11)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL11, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL11,powerdown_entry_size_0,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL11,powerdown_entry_ba_0,dch);

  LOG_MESSAGE(hdlr, 1, ("PASCTL11 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL12 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL12, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL12)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL12, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL12,powerdown_exit_size_0,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL12,powerdown_exit_ba_0,dch);

  LOG_MESSAGE(hdlr, 1, ("PASCTL12 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL13 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL13, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL13)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL13, reg, _CH);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL13,powerdown_entry_size_1,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL13,powerdown_entry_ba_1,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL13 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL14 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL14, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL14)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL14, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL14,powerdown_exit_size_1,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL14,powerdown_exit_ba_1,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL14 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL15 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL15, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL15)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL15, reg, _CH);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL15,powerdown_entry_size_2,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL15,powerdown_entry_ba_2,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL15 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL16 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL16, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL16)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL16, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL16,powerdown_exit_size_2,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL16,powerdown_exit_ba_2,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL16 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL17 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL17, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL17)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL17, reg, _CH);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL17,powerdown_entry_size_3,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL17,powerdown_entry_ba_3,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL17 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL18 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL18, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL18)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL18, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL18,powerdown_exit_size_3,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL18,powerdown_exit_ba_3,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL18 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL20 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL20, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL20)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL20, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  if(IS_RDIMM){
    APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL20,selfref_entry1_size_0,dch);

    APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL20,selfref_entry1_ba_0,dch);
  }

  LOG_MESSAGE(hdlr, 1, ("PASCTL20 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL21 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL21, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL21)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL21, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  if(IS_RDIMM){
    APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL21,selfref_entry2_size_0,dch);

    APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL21,selfref_entry2_ba_0,dch);
  }

  LOG_MESSAGE(hdlr, 1, ("PASCTL21 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL22 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL22, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL22)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL22, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  if(IS_RDIMM){
    APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL22,selfref_exit1_size_0,dch);

    APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL22,selfref_exit1_ba_0,dch);
  }

  LOG_MESSAGE(hdlr, 1, ("PASCTL22 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL23 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL23, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL23)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL23, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  if(IS_RDIMM){
    APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL23,selfref_exit2_size_0,dch);

    APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL23,selfref_exit2_ba_0,dch);
  }

  LOG_MESSAGE(hdlr, 1, ("PASCTL23 = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL24 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL24, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL24)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL24, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL24,selfref_entry1_size_1,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL24,selfref_entry1_ba_1,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL24 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL25 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL25, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL25)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL25, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL25,selfref_entry2_size_1,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL25,selfref_entry2_ba_1,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL25 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL26 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL26, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL26)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL26, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL26,selfref_exit1_size_1,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL26,selfref_exit1_ba_1,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL26 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL27 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL27, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL27)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL27, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL27,selfref_exit2_size_1,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL27,selfref_exit2_ba_1,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL27 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL28 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL28, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL28)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL28, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL28,selfref_entry1_size_2,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL28,selfref_entry1_ba_2,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL28 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL29 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL29, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL29)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL29, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL29,selfref_entry2_size_2,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL29,selfref_entry2_ba_2,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL29 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL30 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL30, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL30)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL30, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL30,selfref_exit1_size_2,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL30,selfref_exit1_ba_2,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL30 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL31 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL31, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL31)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL31, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL31,selfref_exit2_size_2,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL31,selfref_exit2_ba_2,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL31 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL32 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL32, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL32)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL32, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL32,selfref_entry1_size_3,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL32,selfref_entry1_ba_3,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL32 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL33 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL33, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL33)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL33, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL33,selfref_entry2_size_3,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL33,selfref_entry2_ba_3,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL33 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL34 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL34, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL34)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL34, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL34,selfref_exit1_size_3,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL34,selfref_exit1_ba_3,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL34 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}

void cinit_prgm_PASCTL35 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
#ifdef DDRCTL_PERRANK_LP
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, PASCTL35, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, PASCTL35)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, PASCTL35, reg, _CH);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL35,selfref_exit2_size_3,dch);

  //APPLY_CFG_TO_REGFIELD_P(cfg,PASCTL35,selfref_exit2_ba_3,dch);


  LOG_MESSAGE(hdlr, 1, ("PASCTL35 = 0x%x\n",reg->value ));
#endif //DDRCTL_PERRANK_LP
#endif // MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
}


void cinit_prgm_DU_CMDBUF_CTRL (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, DU_CMDBUF_CTRL, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, DU_CMDBUF_CTRL)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, DU_CMDBUF_CTRL, reg, _CH);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,DU_CMDBUF_CTRL,du_cmdbuf_rw_start,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,DU_CMDBUF_CTRL,du_cmdbuf_rw_type,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,DU_CMDBUF_CTRL,du_cmdbuf_op_mode,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,DU_CMDBUF_CTRL,du_cmdbuf_select,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,DU_CMDBUF_CTRL,du_cmdbuf_addr,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,DU_CMDBUF_CTRL,du_cmdbuf_wdata,dch);

  LOG_MESSAGE(hdlr, 1, ("DU_CMDBUF_CTRL = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_LP_CMDBUF_CTRL (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_DCHC_REG_STRUCT(0, REGB_DDRC, LP_CMDBUF_CTRL, _CH) * reg;
  DWC_DDRCTL_DECLARE_DCHC_REG_PTRS(REGB_DDRC, LP_CMDBUF_CTRL)
  DWC_DDRCTL_CAST_REG_DCHC(dch, REGB_DDRC, LP_CMDBUF_CTRL, reg, _CH);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P(dyn,LP_CMDBUF_CTRL,lp_cmdbuf_rw_start,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,LP_CMDBUF_CTRL,lp_cmdbuf_rw_type,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,LP_CMDBUF_CTRL,lp_cmdbuf_op_mode,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,LP_CMDBUF_CTRL,lp_cmdbuf_addr,dch);

  APPLY_CFG_TO_REGFIELD_P(dyn,LP_CMDBUF_CTRL,lp_cmdbuf_wdata,dch);

  LOG_MESSAGE(hdlr, 1, ("LP_CMDBUF_CTRL = 0x%x\n",reg->value ));
#endif //MEMC_DDR5
}

void cinit_prgm_DATACTL0 (SubsysHdlr_t *hdlr) {
  TRACE();
}
void cinit_prgm_ODTMAPK (SubsysHdlr_t *hdlr) {
  TRACE();
}
void cinit_prgm_OCECCCFG0 (SubsysHdlr_t *hdlr) {
  TRACE();
}
void cinit_prgm_OCECCCFG1 (SubsysHdlr_t *hdlr) {
  TRACE();
}
void cinit_prgm_OCCAPCFG (SubsysHdlr_t *hdlr) {
  TRACE();
}
void cinit_prgm_OCCAPCFG1 (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
}
void cinit_prgm_OPCTRLCMD (SubsysHdlr_t *hdlr, uint32_t dch) {
  TRACE();
}
void cinit_prgm_DQMAP0 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_DQMAP0_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DQMAP0_reg;

  APPLY_CFG_TO_REGFIELD(scfg,DQMAP0,dq_nibble_map_12_15);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP0,dq_nibble_map_8_11);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP0,dq_nibble_map_4_7);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP0,dq_nibble_map_0_3);

  LOG_MESSAGE(hdlr,1,("DQMAP0=0x%x\n",reg->value));
#endif //UMCTL2_DQ_MAPPING
#endif // DDRCTL_DDR 
}
void cinit_prgm_DQMAP1 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
#ifdef MEMC_DRAM_DATA_WIDTH_GT_23
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_DQMAP1_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DQMAP1_reg;

  APPLY_CFG_TO_REGFIELD(scfg,DQMAP1,dq_nibble_map_28_31);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP1,dq_nibble_map_24_27);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP1,dq_nibble_map_20_23);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP1,dq_nibble_map_16_19);

  LOG_MESSAGE(hdlr,1,("DQMAP1=0x%x\n",reg->value));
#endif // MEMC_DRAM_DATA_WIDTH_23
#endif //UMCTL2_DQ_MAPPING
#endif // DDRCTL_DDR 
}
void cinit_prgm_DQMAP2 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
#ifdef MEMC_DRAM_DATA_WIDTH_GT_39
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_DQMAP2_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DQMAP2_reg;

  APPLY_CFG_TO_REGFIELD(scfg,DQMAP2,dq_nibble_map_44_47);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP2,dq_nibble_map_40_43);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP2,dq_nibble_map_36_39);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP2,dq_nibble_map_32_35);

  LOG_MESSAGE(hdlr,1,("DQMAP2=0x%x\n",reg->value));
#endif // MEMC_DRAM_DATA_WIDTH_39
#endif //UMCTL2_DQ_MAPPING
#endif // DDRCTL_DDR 
}
void cinit_prgm_DQMAP3 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
#ifdef MEMC_DRAM_DATA_WIDTH_GT_55
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_DQMAP3_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DQMAP3_reg;

  APPLY_CFG_TO_REGFIELD(scfg,DQMAP3,dq_nibble_map_60_63);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP3,dq_nibble_map_56_59);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP3,dq_nibble_map_52_55);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP3,dq_nibble_map_48_51);

  LOG_MESSAGE(hdlr,1,("DQMAP3=0x%x\n",reg->value));
#endif // MEMC_DRAM_DATA_WIDTH_55
#endif //UMCTL2_DQ_MAPPING
#endif // DDRCTL_DDR 
}
void cinit_prgm_DQMAP4 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
#ifdef MEMC_DRAM_DATA_WIDTH_72_OR_MEMC_SIDEBAND_ECC
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_DQMAP4_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DQMAP4_reg;

  APPLY_CFG_TO_REGFIELD(scfg,DQMAP4,dq_nibble_map_cb_4_7);
  APPLY_CFG_TO_REGFIELD(scfg,DQMAP4,dq_nibble_map_cb_0_3);

  LOG_MESSAGE(hdlr,1,("DQMAP4=0x%x\n",reg->value));
#endif // MEMC_DRAM_DATA_WIDTH_72_OR_MEMC_SIDEBAND_ECC
#endif //UMCTL2_DQ_MAPPING
#endif // DDRCTL_DDR 
}
void cinit_prgm_DQMAP5 (SubsysHdlr_t *hdlr) {
  TRACE();
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
  mctl_static_cfg_t* scfg = &(hdlr->memCtrlr_m.static_cfg);

  REGB_DDRC_CH0_DQMAP5_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DQMAP5_reg;

  APPLY_CFG_TO_REGFIELD(scfg,DQMAP5,dis_dq_rank_swap);

  LOG_MESSAGE(hdlr,1,("DQMAP5=0x%x\n",reg->value));
#endif //UMCTL2_DQ_MAPPING
#endif // DDRCTL_DDR 
}
void cinit_prgm_REGPARCFG (SubsysHdlr_t *hdlr) {
  TRACE();
}
void cinit_prgm_POISONCFG (SubsysHdlr_t *hdlr) {
  TRACE();
}


