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
void cinit_prgm_freq_regs(SubsysHdlr_t *hdlr) {
  TRACE();
  for(uint32_t dch=0; dch<hdlr->num_dch; dch++) {
    cinit_prgm_DFIUPDTMG0(hdlr, dch);
    cinit_prgm_DFILPTMG0 (hdlr,dch);
    cinit_prgm_DFILPTMG1 (hdlr,dch);
  }

  for(uint32_t pstate=0; pstate<hdlr->num_pstates; pstate++) {
    cinit_prgm_TMGCFG(hdlr, pstate, 0);
    for(uint32_t dch=0; dch<hdlr->num_dch; dch++) {
      cinit_prgm_DRAMSET1TMG0(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG1(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG2(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG3(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG4(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG5(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG6(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG7(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG8(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG9(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG10(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG12(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG13(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG14(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG16(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG17(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG18(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG19(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG20(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG21(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG22(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG24(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG25(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG26(hdlr, pstate, dch);
      cinit_prgm_DRAMSET1TMG30(hdlr, pstate, dch);
      cinit_prgm_RANK_SWITCH_TIMING_CONTROL0(hdlr, pstate, dch);
      cinit_prgm_RANK_SWITCH_TIMING_CONTROL1(hdlr, pstate, dch);
      cinit_prgm_RANK_SWITCH_TIMING_CONTROL2(hdlr, pstate, dch);
      cinit_prgm_RANK_SWITCH_TIMING_CONTROL3(hdlr, pstate, dch);
      cinit_prgm_RANK_SWITCH_TIMING_CONTROL4(hdlr, pstate, dch);
      cinit_prgm_RANK_SWITCH_TIMING_CONTROL5(hdlr, pstate, dch);
      cinit_prgm_DRAMSET2TMG0(hdlr, pstate, dch);
      cinit_prgm_DRAMSET2TMG1(hdlr, pstate, dch);
      cinit_prgm_RFSHSET1TMG0(hdlr, pstate, dch);
      cinit_prgm_RFSHSET1TMG1(hdlr, pstate, dch);
      cinit_prgm_RFSHSET1TMG2(hdlr, pstate, dch);
      cinit_prgm_RFSHSET1TMG3(hdlr, pstate, dch);
      cinit_prgm_RFSHSET1TMG4(hdlr, pstate, dch);
      cinit_prgm_RFSHSET1TMG5(hdlr, pstate, dch);
      cinit_prgm_RFSHSET1TMG6(hdlr, pstate, dch);
      cinit_prgm_ZQSET1TMG0(hdlr, pstate, dch);
      cinit_prgm_ZQSET1TMG1(hdlr, pstate, dch);
      cinit_prgm_PWRTMG(hdlr, pstate, dch);
      cinit_prgm_TMGCFG(hdlr, pstate, dch);
      cinit_prgm_PERFLPR1(hdlr, pstate, dch);
      cinit_prgm_HWLPTMG0(hdlr, pstate, dch);
      cinit_prgm_DERATEVAL0(hdlr,pstate,dch);
      cinit_prgm_DERATEVAL1(hdlr,pstate,dch);
      cinit_prgm_DERATEINT(hdlr,pstate,dch);
      cinit_prgm_RANKTMG0(hdlr,pstate,dch);
      cinit_prgm_DFITMG0(hdlr, pstate, dch);
      cinit_prgm_DFITMG1(hdlr, pstate, dch);
      cinit_prgm_DFITMG2(hdlr, pstate, dch);
      cinit_prgm_DFITMG4(hdlr, pstate, dch);
      cinit_prgm_DFITMG5(hdlr, pstate, dch);
      cinit_prgm_INITMR0(hdlr,pstate,dch);
      cinit_prgm_INITMR1(hdlr,pstate,dch);
      cinit_prgm_INITMR2(hdlr,pstate,dch);
      cinit_prgm_INITMR3(hdlr,pstate,dch);
      cinit_prgm_DRAMSET1TMG11 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET1TMG15 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET1TMG23 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET1TMG28 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET1TMG29 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG2 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG3 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG4 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG5 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG6 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG7 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG8 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG9 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG10 (hdlr,pstate,dch);
      cinit_prgm_SCHEDTMG0(hdlr,pstate,dch);
      cinit_prgm_MRAMTMG0 (hdlr,pstate,dch);
      cinit_prgm_MRAMTMG1 (hdlr,pstate,dch);
      cinit_prgm_MRAMTMG2 (hdlr,pstate,dch);
      cinit_prgm_MRAMTMG3 (hdlr,pstate,dch);
      cinit_prgm_DFITMG3 (hdlr,pstate,dch);
      cinit_prgm_DFIUPDTMG1 (hdlr,pstate,dch);
      cinit_prgm_RCDINIT1 (hdlr,pstate,dch);
      cinit_prgm_RCDINIT2 (hdlr,pstate,dch);
      cinit_prgm_RCDINIT3 (hdlr,pstate,dch);
      cinit_prgm_RCDINIT4 (hdlr,pstate,dch);
      cinit_prgm_DQSOSCCTL0 (hdlr,pstate,dch);
      cinit_prgm_RANKTMG1 (hdlr,pstate,dch);
      cinit_prgm_ODTCFG (hdlr,pstate,dch);
      cinit_prgm_CRCPARTMG0 (hdlr,pstate,dch);
      cinit_prgm_CRCPARTMG1 (hdlr,pstate,dch);
      cinit_prgm_PERFHPR1 (hdlr,pstate,dch);
      cinit_prgm_PERFWR1 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET1TMG27 (hdlr,pstate,dch);
      cinit_prgm_DRAMSET2TMG11 (hdlr,pstate,dch);
      cinit_prgm_DFITMG7 (hdlr,pstate,dch);
      cinit_prgm_RFSHSET1TMG7 (hdlr,pstate,dch);
      cinit_prgm_RFSHSET1TMG8 (hdlr,pstate,dch);
      cinit_prgm_RFSHSET2TMG3 (hdlr,pstate,dch);
      cinit_prgm_ZQSET2TMG0 (hdlr,pstate,dch);
    }
  }

}

/** @brief */
void cinit_prgm_DRAMSET1TMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG0); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);

  qdyn->wr2pre[p][dch] = hdlr->spdData_m.tAL + pre_cfg->cwl_x[p]+
      cfg->burst_rdwr + pre_cfg->twr[p][dch] + 1;
#ifdef MEMC_LPDDR4  
if(IS_LPDDR4) {
    qdyn->wr2pre[p][dch] = pre_cfg->wl[p][dch] + cfg->burst_rdwr + pre_cfg->twr[p][dch] + 1;
  }
if(IS_LPDDR5) {
    qdyn->wr2pre[p][dch] = pre_cfg->wl[p][dch] + timing->lpddr5_bl_n_min_tck + pre_cfg->twr[p][dch] + 1;
  }
#endif
#ifdef MEMC_DDR4
  if(IS_DDR5) {
    qdyn->wr2pre[p][dch] = pre_cfg->cwl_x[p]+ cfg->burst_rdwr + pre_cfg->twr[p][dch] + qdyn->wr_crc_enable;
  }
#endif
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG0 ,wr2pre,p, dch);

  qdyn->t_faw[p][dch]=pre_cfg->tfaw[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG0 ,t_faw,p, dch);

  
  qdyn->t_ras_max[p][dch]=pre_cfg->t_ras_max[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG0 ,t_ras_max,p,dch);
  CONSTRAIN_MIN(reg->t_ras_max,1); // cannot be zero
  qdyn->t_ras_min[p][dch]=pre_cfg->t_ras_min[p][dch];
   
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG0 ,t_ras_min,p,dch);
  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG0[%0d]= 0x%x\n",p,reg->value ));
}

void cinit_prgm_DRAMSET1TMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG1); 
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->t_xp[p][dch]=pre_cfg->txp[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG1 ,t_xp,p, dch);
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4) {
      qdyn->rd2pre[p][dch]=cfg->burst_rdwr - 8 + pre_cfg->t_rtp[p][dch];
  }
  if(IS_LPDDR5) {
      qdyn->rd2pre[p][dch]=timing->lpddr5_bl_n_min_tck + pre_cfg->t_rbtp[p][dch];
  }
#endif
#ifdef MEMC_DDR4
  if(IS_DDR4) {
      uint32_t ddr4_eq1_rd2pre,ddr4_eq2_rd2pre;
      // JEDEC DDR4: Read to predcharge = tAL + max (4 *nCK, tRTP)
      // rd2pre is max of following two equations:
      // - AL + max(trtp,4)
      // - RL + BL/2 - trp  (RL=AL+CL)    
      ddr4_eq1_rd2pre = hdlr->spdData_m.tAL + max(pre_cfg->t_rtp[p][dch], 4);
      ddr4_eq2_rd2pre = hdlr->spdData_m.tAL + pre_cfg->cl[p]+ cfg->burst_rdwr - pre_cfg->t_rp[p][dch];
      qdyn->rd2pre[p][dch]=max( ddr4_eq1_rd2pre, ddr4_eq2_rd2pre);
      LOG_MESSAGE(hdlr, 1, ("pre_cfg->cl[p]= 0x%x\n", pre_cfg->cl[p]));
      LOG_MESSAGE(hdlr, 1, ("hdlr->spdData_m.tAL = 0x%x\n", hdlr->spdData_m.tAL));
      LOG_MESSAGE(hdlr, 1, ("pre_cfg->t_rtp[%0d][%0d] = 0x%x\n", p,dch, pre_cfg->t_rtp[p][dch]));
      LOG_MESSAGE(hdlr, 1, ("pre_cfg->rl[%0d][%0d] = 0x%x\n", p,dch,pre_cfg->rl[p][dch]));
      LOG_MESSAGE(hdlr, 1, ("pre_cfg->t_rp[%0d][%0d] = 0x%x\n", p,dch,pre_cfg->t_rp[p][dch]));
      LOG_MESSAGE(hdlr, 1, ("cfg->burst_rdwr = 0x%x\n", cfg->burst_rdwr));
      LOG_MESSAGE(hdlr, 1, ("ddr4_eq1_rd2pre = 0x%x\n", ddr4_eq1_rd2pre));
      LOG_MESSAGE(hdlr, 1, ("ddr4_eq2_rd2pre = 0x%x\n", ddr4_eq2_rd2pre));
  }
  else if (IS_DDR5) {
    uint32_t ddr5_eq1_rd2pre, ddr5_eq2_rd2pre;
    ddr5_eq1_rd2pre = pre_cfg->t_rtp[p][dch];
    ddr5_eq2_rd2pre = pre_cfg->cl[p]+ cfg->burst_rdwr - pre_cfg->t_rp[p][dch];

    qdyn->rd2pre[p][dch] = max(ddr5_eq1_rd2pre,ddr5_eq2_rd2pre);
  }
#endif

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG1 ,rd2pre,p,dch);

  qdyn->t_rc[p][dch]= pre_cfg->t_rc[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG1 ,t_rc,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG1[%d]= 0x%x\n",p,reg->value ));
}

/** @brief */
void cinit_prgm_DRAMSET1TMG2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG2, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG2)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG2)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG2); 
#ifdef MEMC_LPDDR4
  // write latency
 if(IS_LPDDR4) {
     qdyn->write_latency[p][dch]=pre_cfg->wl[p][dch];
 } else if(IS_LPDDR5) {
     qdyn->write_latency[p][dch]=pre_cfg->wl[p][dch];
 }
#endif
#ifdef MEMC_DDR4
  if(IS_DDR4)  {
    if( hdlr->memCtrlr_m.ddr4_mr[p].mr5.read_dbi==1) {
      qdyn->write_latency[p][dch]= hdlr->spdData_m.tAL_RDBI + pre_cfg->cwl_x[p];
    } else {
      qdyn->write_latency[p][dch]= hdlr->spdData_m.tAL + pre_cfg->cwl_x[p];
    }
  } else if (IS_DDR5) {
    qdyn->write_latency[p][dch] = pre_cfg->cwl_x[p];
  } else
  {
    qdyn->write_latency[p][dch]= hdlr->spdData_m.tAL + pre_cfg->cwl_x[p];
  }
#endif      
  
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG2 ,write_latency,p,dch);
#ifdef MEMC_LPDDR4
 if(IS_LPDDR4) {
   if(hdlr->memCtrlr_m.lpddr4_mr[p].mr3.read_dbi==1) {
    qdyn->read_latency[p][dch] = pre_cfg->cl_dbi[p];
   } else {
     qdyn->read_latency[p][dch] = pre_cfg->cl[p];
   }
 } else if(IS_LPDDR5) {
     qdyn->read_latency[p][dch]=pre_cfg->rl[p][dch];
 }
#endif
#ifdef MEMC_DDR4 
  if(IS_DDR4) {
   qdyn->read_latency[p][dch]=hdlr->spdData_m.tAL + pre_cfg->cl[p];
 } else if(IS_DDR5) {
   qdyn->read_latency[p][dch]=pre_cfg->cl[p];
 } 
  
#endif
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG2 ,read_latency,p,dch);
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4 && (hdlr->memCtrlr_m.lpddr4_mr[p].mr11.dq_odt>0)) {
   qdyn->rd2wr[p][dch]=pre_cfg->rd2wr_odt[p][dch];
  } else if (IS_LPDDR5 && (hdlr->memCtrlr_m.lpddr5_mr[p].mr11.dq_odt>0)) {
   qdyn->rd2wr[p][dch]=pre_cfg->rd2wr_odt[p][dch];
  } else 
#endif
  {
   qdyn->rd2wr[p][dch]=pre_cfg->rd2wr[p][dch];
  }
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG2 ,rd2wr,p,dch);
  CONSTRAIN_INSIDE(reg->rd2wr, 0, 63); // 6 bits

  qdyn->wr2rd[p][dch]=pre_cfg->wr2rd[p][dch];
  
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG2 ,wr2rd,p,dch);
  
  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG2[%d][%0d]= 0x%x\n",p,dch,reg->value ));
}

void cinit_prgm_DRAMSET1TMG18 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
  mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG18, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG18)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG18)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG18); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->t_pd[p][dch] = pre_cfg->t_pd[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG18 ,t_pd,p, dch);

  qdyn->t_mpsmx[p][dch] = pre_cfg->t_mpsmx[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG18 ,t_mpsmx,p, dch);

  qdyn->t_mpdpxact[p][dch] = pre_cfg->t_mpdpxact[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG18 ,t_mpdpxact,p, dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG18[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
}

void cinit_prgm_DRAMSET1TMG19 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
  mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG19, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG19)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG19)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG19); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->t_pda_latch[p][dch] = pre_cfg->t_pda_latch[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG19 ,t_pda_latch,p, dch);

  qdyn->t_pda_delay[p][dch] = pre_cfg->t_pda_delay[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG19 ,t_pda_delay,p, dch);

  qdyn->t_pda_dqs_delay[p][dch] = pre_cfg->t_pda_dqs_delay[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG19 ,t_pda_dqs_delay,p, dch);

  qdyn->t_pda_s[p][dch] = pre_cfg->t_pda_s[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG19 ,t_pda_s,p, dch);

  qdyn->t_pda_h[p][dch] = pre_cfg->t_pda_h[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG19 ,t_pda_h,p, dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG19[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
}

void cinit_prgm_DRAMSET1TMG20 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
  mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG20, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG20)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG20)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG20); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->t_cpded[p][dch] = pre_cfg->t_cpded[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG20 ,t_cpded,p, dch);

  qdyn->t_casrx[p][dch] = pre_cfg->t_casrx[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG20 ,t_casrx,p, dch);

  qdyn->t_csh_srexit[p][dch] = pre_cfg->t_csh_srexit[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG20 ,t_csh_srexit,p, dch);

  qdyn->t_csl_srexit[p][dch] = pre_cfg->t_csl_srexit[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG20 ,t_csl_srexit,p, dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG20[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
}

void cinit_prgm_DRAMSET1TMG21 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
  mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG21, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG21)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG21)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG21); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->t_mpc_cs[p][dch] = pre_cfg->t_mpc_cs[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG21 ,t_mpc_cs,p, dch);

  qdyn->t_mpc_setup[p][dch] = pre_cfg->t_mpc_setup[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG21 ,t_mpc_setup,p, dch);

  qdyn->t_mpc_hold[p][dch] = pre_cfg->t_mpc_hold[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG21 ,t_mpc_hold,p, dch);

  qdyn->t_vrefca_cs[p][dch] = pre_cfg->t_vrefca_cs[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG21 ,t_vrefca_cs,p, dch);

  qdyn->t_osco_ddr5[p][dch] = pre_cfg->t_osco_ddr5[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG21 ,t_osco_ddr5,p, dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG21[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
}

void cinit_prgm_DRAMSET1TMG22 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
  mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG22, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG22)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG22)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG22); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->t_wr2rd_dpr[p][dch] = pre_cfg->t_wr2rd_dpr[p][dch];

  qdyn->t_rd2wr_dpr[p][dch] = pre_cfg->t_rd2wr_dpr[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG22 ,t_wr2rd_dpr,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG22 ,t_rd2wr_dpr,p, dch);

#ifdef UMCTL2_CID_EN
  qdyn->t_wr2rd_dlr[p][dch] = pre_cfg->t_wr2rd_dlr[p][dch];
  qdyn->t_rd2wr_dlr[p][dch] = pre_cfg->t_rd2wr_dlr[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG22 ,t_wr2rd_dlr,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG22 ,t_rd2wr_dlr,p, dch);
#endif


  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG22[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
}

void cinit_prgm_DRAMSET1TMG26 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
  mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG26, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG26)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG26)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG26); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);

  qdyn->t_ccd_w_s[p][dch] = (qdyn->wr_crc_enable == 0) ? timing->ddr5_tccd_s_tck : timing->ddr5_tccd_s_tck + 1;
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG26 ,t_ccd_w_s,p, dch);

  qdyn->t_ccd_r_s[p][dch] = (qdyn->rd_crc_enable == 0) ? timing->ddr5_tccd_s_tck : timing->ddr5_tccd_s_tck + 1;
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG26 ,t_ccd_r_s,p, dch);

  qdyn->t_ccd_w[p][dch] = pre_cfg->t_ccd_w[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG26 ,t_ccd_w,p, dch);

  qdyn->t_ccd_r[p][dch] = timing->ddr5_tccd_l_tck;
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG26 ,t_ccd_r,p, dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG26[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
}

void cinit_prgm_RANK_SWITCH_TIMING_CONTROL0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RANK_SWITCH_TIMING_CONTROL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL0); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  //prank0/1 wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL0 ,t_wr2wr_gap_r1r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL0 ,t_wr2wr_gap_r0r1,p, dch);
  //prank0/1 rd/wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL0 ,t_rd2wr_gap_r1r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL0 ,t_rd2wr_gap_r0r1,p, dch);
  //prank0/1 wr/rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL0 ,t_wr2rd_gap_r1r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL0 ,t_wr2rd_gap_r0r1,p, dch);
  //prank0/1 rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL0 ,t_rd2rd_gap_r1r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL0 ,t_rd2rd_gap_r0r1,p, dch);

  LOG_MESSAGE(hdlr, 1, ("RANK_SWITCH_TIMING_CONTROL0[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
#endif
}

void cinit_prgm_RANK_SWITCH_TIMING_CONTROL1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RANK_SWITCH_TIMING_CONTROL1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL1); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  //prank0/2 wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL1 ,t_wr2wr_gap_r2r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL1 ,t_wr2wr_gap_r0r2,p, dch);
  //prank0/2 rd/wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL1 ,t_rd2wr_gap_r2r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL1 ,t_rd2wr_gap_r0r2,p, dch);
  //prank0/2 wr/rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL1 ,t_wr2rd_gap_r2r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL1 ,t_wr2rd_gap_r0r2,p, dch);
  //prank0/2 rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL1 ,t_rd2rd_gap_r2r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL1 ,t_rd2rd_gap_r0r2,p, dch);

  LOG_MESSAGE(hdlr, 1, ("RANK_SWITCH_TIMING_CONTROL1[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
#endif
}

void cinit_prgm_RANK_SWITCH_TIMING_CONTROL2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RANK_SWITCH_TIMING_CONTROL2, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL2)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL2)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL2); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  //prank0/3 wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL2 ,t_wr2wr_gap_r3r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL2 ,t_wr2wr_gap_r0r3,p, dch);
  //prank0/3 rd/wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL2 ,t_rd2wr_gap_r3r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL2 ,t_rd2wr_gap_r0r3,p, dch);
  //prank0/3 wr/rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL2 ,t_wr2rd_gap_r3r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL2 ,t_wr2rd_gap_r0r3,p, dch);
  //prank0/3 rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL2 ,t_rd2rd_gap_r3r0,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL2 ,t_rd2rd_gap_r0r3,p, dch);

  LOG_MESSAGE(hdlr, 1, ("RANK_SWITCH_TIMING_CONTROL2[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
#endif
}

void cinit_prgm_RANK_SWITCH_TIMING_CONTROL3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RANK_SWITCH_TIMING_CONTROL3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL3)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL3); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  //prank2/1 wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL3 ,t_wr2wr_gap_r2r1,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL3 ,t_wr2wr_gap_r1r2,p, dch);
  //prank2/1 rd/wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL3 ,t_rd2wr_gap_r2r1,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL3 ,t_rd2wr_gap_r1r2,p, dch);
  //prank2/1 wr/rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL3 ,t_wr2rd_gap_r2r1,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL3 ,t_wr2rd_gap_r1r2,p, dch);
  //prank2/1 rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL3 ,t_rd2rd_gap_r2r1,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL3 ,t_rd2rd_gap_r1r2,p, dch);

  LOG_MESSAGE(hdlr, 1, ("RANK_SWITCH_TIMING_CONTROL3[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
#endif
}

void cinit_prgm_RANK_SWITCH_TIMING_CONTROL4 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RANK_SWITCH_TIMING_CONTROL4, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL4)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL4)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL4); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  //prank3/1 wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL4 ,t_wr2wr_gap_r3r1,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL4 ,t_wr2wr_gap_r1r3,p, dch);
  //prank3/1 rd/wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL4 ,t_rd2wr_gap_r3r1,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL4 ,t_rd2wr_gap_r1r3,p, dch);
  //prank3/1 wr/rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL4 ,t_wr2rd_gap_r3r1,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL4 ,t_wr2rd_gap_r1r3,p, dch);
  //prank3/1 rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL4 ,t_rd2rd_gap_r3r1,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL4 ,t_rd2rd_gap_r1r3,p, dch);

  LOG_MESSAGE(hdlr, 1, ("RANK_SWITCH_TIMING_CONTROL4[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
#endif
}

void cinit_prgm_RANK_SWITCH_TIMING_CONTROL5 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RANK_SWITCH_TIMING_CONTROL5, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL5)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL5)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RANK_SWITCH_TIMING_CONTROL5); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  //prank3/2 wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL5 ,t_wr2wr_gap_r3r2,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL5 ,t_wr2wr_gap_r2r3,p, dch);
  //prank3/2 rd/wr switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL5 ,t_rd2wr_gap_r3r2,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL5 ,t_rd2wr_gap_r2r3,p, dch);
  //prank3/2 wr/rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL5 ,t_wr2rd_gap_r3r2,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL5 ,t_wr2rd_gap_r2r3,p, dch);
  //prank3/2 rd switch
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL5 ,t_rd2rd_gap_r3r2,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANK_SWITCH_TIMING_CONTROL5 ,t_rd2rd_gap_r2r3,p, dch);

  LOG_MESSAGE(hdlr, 1, ("RANK_SWITCH_TIMING_CONTROL5[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
#endif
}

void cinit_prgm_DRAMSET1TMG3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG3)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG3); 

  if(IS_DDR4) {
    qdyn->t_mr[p][dch]=pre_cfg->t_mod[p][dch];
  } else if(IS_DDR5){
    qdyn->t_mr[p][dch] = pre_cfg->t_mr[p][dch];
  } else {
    qdyn->t_mr[p][dch]=pre_cfg->t_mr[p][dch];
  }

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG3 ,t_mr,p,dch);

#ifdef MEMC_LPDDR4
  qdyn->rd2mr[p][dch]=pre_cfg->rd2mr[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG3 ,rd2mr,p,dch);

  qdyn->wr2mr[p][dch]=pre_cfg->wr2mr[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG3 ,wr2mr,p,dch);
#endif // MEMC_LPDDR4

  // @todo add rd2mr and wr2mr
  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG3[%0d]= 0x%x\n",p,reg->value ));
}

/** @brief function to setup the register field values for DRAMSET1TMG4
 */
void cinit_prgm_DRAMSET1TMG4 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG4, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG4)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG4)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG4); 

  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  
  qdyn->t_rcd[p][dch]=pre_cfg->t_rcd[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG4 ,t_rcd,p,dch);
  CONSTRAIN_INSIDE(reg->t_rcd,1,0x7f); // cannot be zero, 7 bits 

  qdyn->t_ccd[p][dch]=pre_cfg->t_ccd[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG4 ,t_ccd,p,dch);

  qdyn->t_rrd[p][dch]=pre_cfg->t_rrd[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG4 ,t_rrd,p,dch);
  
  qdyn->t_rp[p][dch]=pre_cfg->t_rp[p][dch];
  qdyn->t_rp[p][dch]=qdyn->t_rp[p][dch]+1; //TODO: tempfix for bugzilla 6578
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG4 ,t_rp,p,dch);
  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG4[%0d]= 0x%x\n",p,reg->value ));
}

/** @brief function to setup the register field values for DRAMSET1TMG5
 */

void cinit_prgm_DRAMSET1TMG5 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch) { 
  TRACE();

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG5, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG5)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG5)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG5); 

  qdyn->t_cksrx[p][dch]=pre_cfg->t_cksrx[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG5 ,t_cksrx,p,dch);
  CONSTRAIN_INSIDE(reg->t_cksrx, 0, 15); // 4 bits

  qdyn->t_cksre[p][dch]=pre_cfg->t_cksre[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG5 ,t_cksre,p,dch);

  qdyn->t_ckesr[p][dch]=pre_cfg->t_ckesr[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG5 ,t_ckesr,p,dch);

  qdyn->t_cke[p][dch]=pre_cfg->t_cke[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG5 ,t_cke,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG5[%d]= 0x%x\n",p,reg->value ));
}
/** @brief function to setup the register field values for DRAMSET1TMG6
 */
void cinit_prgm_DRAMSET1TMG6 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef DDRCTL_LPDDR
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG6, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG6)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG6)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG6); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);

  qdyn->t_ckcsx[p][dch]=0;

  if(IS_mDDR) { qdyn->t_ckcsx[p][dch]=1;} 

  if(IS_LPDDR4 || IS_LPDDR5) {
    qdyn->t_ckcsx[p][dch]=pre_cfg->txp[p][dch]+2;
  }
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG6 ,t_ckcsx,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG6[%0d]= 0x%x\n",p,reg->value ));

#endif // DDRCTL_LPDDR
}

void cinit_prgm_DRAMSET1TMG7 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef DDRCTL_LPDDR
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG7, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG7)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG7)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG7); 

  if(IS_LPDDR5) {
    qdyn->t_csh[p][dch]=pre_cfg->t_csh[p][dch];
    APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG7 ,t_csh,p,dch);
  }

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG7[%d]= 0x%x\n",p,reg->value ));
#endif // DDRCTL_LPDDR
}

void cinit_prgm_DRAMSET1TMG8 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG8, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG8)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG8)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG8); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  
  qdyn->t_xs_dll_x32[p][dch]=0x44; /// @todo finish t_xs_dll_x32 calculation
  qdyn->t_xs_x32[p][dch]=pre_cfg->t_xs_min[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG8 ,t_xs_dll_x32,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG8 ,t_xs_x32,p,dch);
 
#ifdef MEMC_DDR4
  qdyn->t_xs_fast_x32[p][dch]=pre_cfg->t_xs_fast_min[p][dch];
  qdyn->t_xs_abort_x32[p][dch]=pre_cfg->t_xs_fast_min[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG8 ,t_xs_fast_x32,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG8 ,t_xs_abort_x32,p,dch);
  //must be less than or equal to t_xs_x32
  CONSTRAIN_MAX(reg->t_xs_fast_x32, reg->t_xs_x32); 
#endif //MEMC_DDR4
 
  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG8[%d]= 0x%x\n",p,reg->value ));
}


void cinit_prgm_DRAMSET1TMG9 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG9, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG9)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG9)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG9); 

#ifdef MEMC_DDR4

  if(IS_DDR4){
    //wr_preamble
    APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG9,ddr4_wr_preamble,p,dch);
    qdyn->t_ccd_s[p][dch] = timing->ddr4_tccd_s_tck;
    qdyn->t_rrd_s[p][dch] = timing->trrd_s_tck;
    qdyn->wr2rd_s[p][dch] = pre_cfg->wr2rd_s[p][dch];
    // Calculate wr2rd_s
  } else if(IS_DDR5) {
    qdyn->t_ccd_s[p][dch] = timing->ddr5_tccd_s_tck;
    qdyn->t_rrd_s[p][dch] = timing->trrd_s_tck;
    qdyn->wr2rd_s[p][dch] = pre_cfg->wr2rd_s[p][dch];
    //TODO : wr2rd_s
  }

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG9,wr2rd_s,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG9,t_ccd_s,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG9,t_rrd_s,p,dch);
#endif

#ifdef DDRCTL_LPDDR
  if(IS_LPDDR5) {
    qdyn->t_ccd_s[p][dch]=timing->lpddr5_bl_n_min_tck;
    APPLY_CFG_TO_REGFIELD_P_CH(qdyn, DRAMSET1TMG9 ,t_ccd_s ,p, dch);
  }
  qdyn->t_rrd_s[p][dch]=pre_cfg->t_rrd_s[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, DRAMSET1TMG9 ,t_rrd_s ,p, dch);  
#endif // DDRCTL_LPDDR

  qdyn->wr2rd_s[p][dch]=pre_cfg->wr2rd_s[p][dch] + qdyn->wr_crc_enable;
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, DRAMSET1TMG9 ,wr2rd_s ,p,dch);
  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG9[%0d] = 0x%x\n",p,reg->value ));
}



void cinit_prgm_DRAMSET1TMG10 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR4
#ifndef MEMC_CMD_RTN2IDLE
//comment as not used
//  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
//  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
//  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG10, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG10)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG10)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG10); 
  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG10= 0x%x\n",p,reg->value ));
#endif // !MEMC_CMD_RTN2IDLE
#endif // MEMC_DDR4
}

void cinit_prgm_DRAMSET1TMG12 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG12, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG12)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG12)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG12); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
#ifdef MEMC_LPDDR4
  qdyn->t_cmdcke[p][dch] = pre_cfg->t_cmdcke[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG12 ,t_cmdcke,p,dch);
#endif

#ifdef MEMC_DDR4
  if (IS_DDR4) {
    qdyn->t_mrd_pda[p][dch]=pre_cfg->t_mrd_pda[p][dch];
    if( qdyn->t_mrd_pda[p][dch]<16 ) {
        qdyn->t_mrd_pda[p][dch]=16;
    }
  } else if(IS_DDR5) {
    qdyn->t_mrd_pda[p][dch]=0;
  }
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG12 ,t_mrd_pda,p,dch);

  LOG_MESSAGE(hdlr, 1, ("TMGCFG[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG12[%d]= 0x%x\n",p,reg->value ));
}

void cinit_prgm_DRAMSET1TMG13 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch) { 
  TRACE();
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG13, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG13)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG13)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG13); 

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

#ifdef MEMC_LPDDR4
  qdyn->odtloff[p][dch]=pre_cfg->odtloff[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG13 ,odtloff,p,dch);
  if(IS_LPDDR4) {
    qdyn->t_ccd_mw[p][dch]=timing->lpddr4_tccdmw;
  } else if(IS_LPDDR5) {
    qdyn->t_ccd_mw[p][dch]=timing->lpddr5_tccdmw_tck;
  }
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG13 ,t_ccd_mw,p,dch);

  if(IS_LPDDR4) {
      qdyn->t_ppd[p][dch]=timing->lpddr4_tppd;
  } else if(IS_LPDDR5) {
      qdyn->t_ppd[p][dch]=timing->lpddr5_tppd_tck;
  }
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG13 ,t_ppd,p,dch);
#endif // MEMC_LPDDR4
#ifdef MEMC_DDR5
  qdyn->t_ccd_w2[p][dch] = pre_cfg->t_ccd_w2[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG13,t_ccd_w2,p,dch);

  if(IS_DDR5) {
    qdyn->t_ppd[p][dch] = timing->ddr5_tppd_tck;
    APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG13 ,t_ppd,p,dch);
  }
#endif // MEMC_DDR5
  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG13[%d]= 0x%x\n",p,reg->value ));
}

void cinit_prgm_DRAMSET1TMG14 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef DDRCTL_LPDDR
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG14, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG14)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG14)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG14); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG14 ,t_xsr,p,dch);

  if(hdlr->enable_non_jedec_tck==0 ) {
    uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
    uint32_t min_t_xsr=dwc_cinit_get_min_t_xsr(hdlr,tck_ps );
    CONSTRAIN_MIN(reg->t_xsr, min_t_xsr);
  }
#ifdef LPDDR45_DQSOSC_EN  
  if(IS_LPDDR4) {
    mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
    qdyn->t_osco[p][dch]=pre_cfg->t_osco[p][dch];
    APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG14 ,t_osco,p,dch);
  }
#endif

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG14= 0x%x\n",p,reg->value ));
#endif //DDRCTL_LPDDR
}

void cinit_prgm_DRAMSET1TMG16 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef UMCTL2_CID_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG16, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG16)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG16)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG16);

  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->t_ccd_dlr[p][dch] = pre_cfg->t_ccd_dlr[p][dch];
  qdyn->t_rrd_dlr[p][dch] = pre_cfg->t_rrd_dlr[p][dch];
  qdyn->t_faw_dlr[p][dch] = pre_cfg->t_faw_dlr[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG16,t_ccd_dlr,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG16,t_rrd_dlr,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG16,t_faw_dlr,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG16[%0d]= 0x%x\n",p,reg->value ));
#endif //UMCTL2_CID_EN
}

void cinit_prgm_DRAMSET1TMG17 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef UMCTL2_HWFFC_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG17, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG17)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG17)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG17); 

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  qdyn->t_vrcg_enable[p]=pre_cfg->t_vrcg_enable[p];
  qdyn->t_vrcg_disable[p]=pre_cfg->t_vrcg_disable[p];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG17 ,t_vrcg_enable,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG17 ,t_vrcg_disable,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG17 p=%0d= 0x%x\n",p,reg->value ));
#endif
}

/** @brief SDRAM Timing Register 24 */
void cinit_prgm_DRAMSET1TMG24 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef MEMC_LPDDR5
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG24, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ ,DRAMSET1TMG24)
  DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(p, 0, REGB_FREQ, DRAMSET1TMG24);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  // 8Bank is not allowed
  qdyn->bank_org[p][dch]=(spd->lpddr5_bk_bg_org== DWC_LPDDR5_4BK_4BG) ? 0 : 2; 
  qdyn->max_rd_sync[p][dch]=pre_cfg->max_rd_sync[p][dch];
  qdyn->max_wr_sync[p][dch]=pre_cfg->max_wr_sync[p][dch];
  if (IS_LPDDR5 && (hdlr->memCtrlr_m.lpddr5_mr[p].mr11.dq_odt>0)) {
    qdyn->rd2wr_s[p][dch]=pre_cfg->rd2wr_s_odt[p][dch];
  } else {
    qdyn->rd2wr_s[p][dch]=pre_cfg->rd2wr_s[p][dch];
  }

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG24 ,bank_org,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG24 ,rd2wr_s,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG24 ,max_rd_sync,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG24 ,max_wr_sync,p, dch);

  LOG_MESSAGE(hdlr, 1, ("FREQ%0d CH%0d DRAMSET1TMG24= 0x%x\n",p, dch, reg->value ));

#endif // MEMC_LPDDR5
}


/** @brief SDRAM Timing Register 25 */
void cinit_prgm_DRAMSET1TMG25 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG25, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ ,DRAMSET1TMG25)
  DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(p, 0, REGB_FREQ, DRAMSET1TMG25);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
#ifdef MEMC_LPDDR4
  qdyn->lpddr4_diff_bank_rwa2pre[p][dch]=pre_cfg->lpddr4_diff_bank_rwa2pre[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG25,lpddr4_diff_bank_rwa2pre,p, dch);
#endif
  qdyn->wra2pre[p][dch]=pre_cfg->wra2pre[p][dch];
  qdyn->rda2pre[p][dch]=pre_cfg->rda2pre[p][dch];
#ifdef MEMC_DDR4
  if(IS_DDR4) {
    qdyn->wra2pre[p][dch]=qdyn->wr2pre[p][dch];
    qdyn->rda2pre[p][dch]=qdyn->rd2pre[p][dch];
  }
#endif
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG25,wra2pre,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG25,rda2pre,p, dch);
  LOG_MESSAGE(hdlr, 1, ("FREQ%0d CH%0d DRAMSET1TMG25= 0x%x\n",p, dch, reg->value ));
}

/** @brief SDRAM Timing Register 30 */
void cinit_prgm_DRAMSET1TMG30 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef MEMC_LPDDR5
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG30, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ ,DRAMSET1TMG30)
  DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(p, 0, REGB_FREQ, DRAMSET1TMG30);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  // 8Bank is not allowed
  if (IS_LPDDR5 && (hdlr->memCtrlr_m.lpddr5_mr[p].mr11.dq_odt>0)) {
    qdyn->mrr2wr[p][dch]=pre_cfg->mrr2wr_odt[p][dch];
  } else {
    qdyn->mrr2wr[p][dch]=pre_cfg->mrr2wr[p][dch];
  }

  qdyn->mrr2rd[p][dch]=pre_cfg->mrr2rd[p][dch];
  qdyn->mrr2mrw[p][dch]=pre_cfg->mrr2mrw[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG30 ,mrr2rd,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG30 ,mrr2wr,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG30 ,mrr2mrw,p, dch);

  LOG_MESSAGE(hdlr, 1, ("FREQ%0d CH%0d DRAMSET1TMG30= 0x%x\n",p, dch, reg->value ));

#endif // MEMC_LPDDR5
}

/** @brief function to setup the register field values for DFIUPDTMG0
 */
void cinit_prgm_DFIUPDTMG0 (SubsysHdlr_t *hdlr, uint32_t dch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFIUPDTMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(0, 0, REGB_FREQ, DFIUPDTMG0, reg, _CH)
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(0, 1, REGB_FREQ, DFIUPDTMG0, reg, _CH)
  if(dch==0) {
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(0, 0, REGB_FREQ, DFIUPDTMG0, reg, _CH)
  }
  else if(dch==1) {
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(0, 1, REGB_FREQ, DFIUPDTMG0, reg, _CH)
  }

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFIUPDTMG0 ,dfi_t_ctrlup_max,0,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFIUPDTMG0 ,dfi_t_ctrlup_min,0,dch);
  if( hdlr->ddrPhyType_m==DWC_LPDDR54_PHY) {
    // Table 5-6 LPDDR54 Utility block (PUB) databook (in DfiClks)
    CONSTRAIN_MIN(reg->dfi_t_ctrlup_max ,24); // min value
    CONSTRAIN_MIN(reg->dfi_t_ctrlup_min ,1); // min value
  } else {
    CONSTRAIN_MIN(reg->dfi_t_ctrlup_max ,0xb); // min value
    CONSTRAIN_MIN(reg->dfi_t_ctrlup_min ,0x1); // min value
  }
  LOG_MESSAGE(hdlr, 1, ("DFIUPDTMG0= 0x%x\n",reg->value ));
}

void cinit_prgm_DFITMG0 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DFITMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DFITMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DFITMG0); 

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG0 ,dfi_t_ctrl_delay,p,dch);
  CONSTRAIN_MAX(reg->dfi_t_ctrl_delay , 0x1f);


  // grab the pre-calculated vale
  qdyn->dfi_t_rddata_en[p][dch]=pre_cfg->dfi_t_rddata_en[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG0,dfi_t_rddata_en,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG0,dfi_tphy_wrdata,p,dch);

  // grab the pre-calculated vale
  qdyn->dfi_tphy_wrlat[p][dch]=pre_cfg->dfi_tphy_wrlat[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG0,dfi_tphy_wrlat,p,dch);

  if(hdlr->ddrPhyType_m==DWC_LPDDR4X_MULTIPHY) {
    CONSTRAIN_MAX(reg->dfi_t_rddata_en , 0x7f);
    CONSTRAIN_MAX(reg->dfi_tphy_wrdata , 8);
    CONSTRAIN_MAX(reg->dfi_tphy_wrlat , 60);
  }
  LOG_MESSAGE(hdlr, 1, ("DFITMG0[%d]= 0x%x\n",p,reg->value ));
  
}

/** @brief Program DFI timing register.
 * @note supports PHY type 6,7 and 8 only. 
 */
void cinit_prgm_DFITMG1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DFITMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DFITMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DFITMG1); 

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
#ifdef MEMC_DDR4
  // calculate value dfi_t_cmd_lat
  // TODO doubl dcheck CAL mode
  if(IS_DDR4) {
    if( hdlr->memCtrlr_m.ddr4_mr[p].mr4.cal==0) {
      qdyn->dfi_t_cmd_lat[p][dch]=0;
    } else {
      uint32_t cal_cycles;
      cal_cycles=get_cal_cycles(hdlr->memCtrlr_m.ddr4_mr[p].mr4.cal);
      if(IS_RDIMM) {
        qdyn->dfi_t_cmd_lat[p][dch]=cal_cycles + pre_cfg->cmd_lat_adder[p][dch]; 
      }
      else {
        qdyn->dfi_t_cmd_lat[p][dch]=cal_cycles;
      }
    }  
  } else {
    qdyn->dfi_t_cmd_lat[p][dch] = 0;
  }

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG1 ,dfi_t_cmd_lat,p,dch);
  CONSTRAIN_INSIDE(reg->dfi_t_cmd_lat, 0, 8);  

  // calculate value dfi_t_parin_lat 
  if(IS_DDR4) {
      ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
      if(IS_RDIMM) {
          qdyn->dfi_t_parin_lat[p][dch]=1;
      } else {
          if(timing->ddr4_tpl_tck==0) {
              // can be 0-3 ??
              CONSTRAIN_INSIDE(qdyn->dfi_t_parin_lat[p][dch], 0, 3);
          } else {
          qdyn->dfi_t_parin_lat[p][dch]=0;
          }
      }
  } 
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG1 ,dfi_t_parin_lat,p,dch);
#endif // MEMC_DDR4

  // calculate value dfi_t_wrdata_delay 
  // This is specific to PHY Type 6,7,8
  uint32_t Trained_TxDQSDly=0;
  uint32_t tSTAOFF=0;

  if(IS_DDR5) {
    qdyn->dfi_t_wrdata_delay[p][dch]= 4 * qdyn->dfi_t_ctrl_delay[p][dch] + 10 +
        cfg->burst_rdwr + Trained_TxDQSDly;
  } else if(IS_DDR4) {
    qdyn->dfi_t_wrdata_delay[p][dch]= 2 * qdyn->dfi_t_ctrl_delay[p][dch] + 6 +
        cfg->burst_rdwr + Trained_TxDQSDly;
  } else {
    qdyn->dfi_t_wrdata_delay[p][dch]= qdyn->dfi_t_ctrl_delay[p][dch] + 6 +
        cfg->burst_rdwr + Trained_TxDQSDly;

  }
  if(IS_RDIMM) { qdyn->dfi_t_wrdata_delay[p][dch]+=tSTAOFF; }

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG1 ,dfi_t_wrdata_delay,p,dch);

  // Note scaling for freq ratio already taken care of in cinit_cal_dfi_timings
  qdyn->dfi_t_dram_clk_disable[p][dch]= pre_cfg->dfi_t_dram_clk_disable[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG1 ,dfi_t_dram_clk_disable,p,dch);
  qdyn->dfi_t_dram_clk_enable[p][dch]= pre_cfg->dfi_t_dram_clk_enable[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG1 ,dfi_t_dram_clk_enable,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DFITMG1[%d]= 0x%x\n",p,reg->value ));
}

/** @brief function to setup the register field values for DFITMG2 
 * @note DFITMG0 and DFITMG1 must be configured prior to this register.
 */
void cinit_prgm_DFITMG2 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG2, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DFITMG2)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DFITMG2)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DFITMG2); 
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG0, _CH)
      *dfitmg0_reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_FREQ_REG_EL(0,0,REGB_FREQ,DFITMG0, _CH);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG1, _CH)
      *dfitmg1_reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_FREQ_REG_EL(0,0,REGB_FREQ,DFITMG1, _CH);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  if(IS_DDR4) {
    qdyn->dfi_tphy_wrcslat[p][dch] = dfitmg0_reg->dfi_tphy_wrlat +
       dfitmg1_reg->dfi_t_cmd_lat;
    qdyn->dfi_tphy_rdcslat[p][dch] = dfitmg0_reg->dfi_t_rddata_en +
        dfitmg1_reg->dfi_t_cmd_lat;
  } else {
      qdyn->dfi_tphy_wrcslat[p][dch] = dfitmg0_reg->dfi_tphy_wrlat;
      qdyn->dfi_tphy_rdcslat[p][dch] = dfitmg0_reg->dfi_t_rddata_en;
  }
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG2 ,dfi_tphy_rdcslat,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG2 ,dfi_tphy_wrcslat,p,dch);
  LOG_MESSAGE(hdlr, 1, ("DFITMG2[%d]= 0x%x\n",p,reg->value ));
}

/** @brief function to setup the register field values for TMGCFG. The
 * function works from MSB to LSB.
 * No actual value is written to the register itself.
 * This is just setting up register intent.
 * The macro APPLY_CFG_TO_REGFIELD_P_CH will apply eadch register field to the 32 bit
 * register value.
 * */

void cinit_prgm_TMGCFG(SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) {
  TRACE();
#ifdef MEMC_PROG_FREQ_RATIO_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,TMGCFG, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, TMGCFG)
  DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(p, 0, REGB_FREQ, TMGCFG); 

  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to dynamic configuration options.

  APPLY_CFG_TO_REGFIELD_P_CH(dyn, TMGCFG, frequency_ratio,p,0);
#endif

  LOG_MESSAGE(hdlr, 1, ("TMGCFG[%0d]= 0x%x\n",p,
               reg->value ));
}




void cinit_prgm_DFITMG4 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_LPDDR5
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG4, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ ,DFITMG4)
  DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(p, 0, REGB_FREQ,DFITMG4 );
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  qdyn->dfi_twck_en_rd[p][dch]=pre_cfg->dfi_twck_en_rd[p][dch];
  qdyn->dfi_twck_en_wr[p][dch]=pre_cfg->dfi_twck_en_wr[p][dch];
  qdyn->dfi_twck_dis[p][dch]=pre_cfg->dfi_twck_dis[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG4,dfi_twck_en_rd,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG4,dfi_twck_en_wr,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG4,dfi_twck_dis,p, dch);

#ifdef MEMC_NUM_RANKS_GT_1
  qdyn->dfi_twck_en_fs[p][dch]=pre_cfg->dfi_twck_en_fs[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG4,dfi_twck_en_fs,p, dch);
#endif

  LOG_MESSAGE(hdlr, 1, ("FREQ%0d CH%0d DFITMG4= 0x%x\n",p, dch, reg->value ));

#endif // MEMC_LPDDR5
}

void cinit_prgm_DFITMG5 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_LPDDR5
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG5, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ ,DFITMG5)
  DWC_DDRCTL_CAST_REG_FREQP_DCHC_MUX(p, 0, REGB_FREQ,DFITMG5);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->dfi_twck_fast_toggle[p][dch]=pre_cfg->dfi_twck_fast_toggle[p][dch];
  qdyn->dfi_twck_toggle[p][dch]=pre_cfg->dfi_twck_toggle[p][dch];
  qdyn->dfi_twck_toggle_cs[p][dch]=pre_cfg->dfi_twck_toggle_cs[p][dch];
  qdyn->dfi_twck_toggle_post[p][dch]=pre_cfg->dfi_twck_toggle_post[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG5,dfi_twck_fast_toggle,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG5,dfi_twck_toggle,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG5,dfi_twck_toggle_cs,p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG5,dfi_twck_toggle_post,p, dch);

#endif // MEMC_LPDDR5
}

/** @brief function to setup the register field values for RFSHSET1TMG0. 
 * */
void cinit_prgm_RFSHSET1TMG0 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch ) { 
  TRACE();
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG0); 

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG0 ,t_refi_x1_x32,p,dch);

#ifdef MEMC_LPDDR4
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG0 ,t_refi_x1_sel,p,dch);
  CONSTRAIN_INSIDE(reg->t_refi_x1_sel,0,1);

  if(IS_LPDDR4) {
    /*dwc_cinit_print("p=%0d,num_dch=%0d tck_ps=%0d\n",p,dch,hdlr->spdData_m.tck_ps[p]);*/
     dyn->t_refi_x1_x32[p][dch] = (cfg->per_bank_refresh) ? timing->lpddr4_trfipb : timing->lpddr4_trfiab;
     dyn->t_refi_x1_x32[p][dch] = dyn->t_refi_x1_x32[p][dch]/hdlr->spdData_m.tck_ps[p];
     dyn->t_refi_x1_x32[p][dch] = (dyn->t_refi_x1_sel[p][dch]) ?  dyn->t_refi_x1_x32[p][dch] :  dyn->t_refi_x1_x32[p][dch]/32;
  }
  else if(IS_LPDDR5) {
   float tck= hdlr->spdData_m.tck_ps[p];
   float trefi_ps= (cfg->per_bank_refresh) ? timing->lpddr5_trefipb_ps : timing->lpddr5_trefi_ps;
   tck= (dyn->t_refi_x1_sel[p][dch]) ? tck : tck*32;
   dyn->t_refi_x1_x32[p][dch]=DIVIDE_ROUNDDOWN(trefi_ps,tck);
  }

  if (IS_LPDDR5 || IS_LPDDR4) {  
    if(dyn->derate_enable) {
        if(dyn->t_refi_x1_sel[p][dch] && cfg->per_bank_refresh) {
          /*dwc_cinit_print("dyn->refresh_margin=%0d, max=%0d\n",dyn->refresh_margin[p][dch], (dyn->t_refi_x1_x32[p][dch] >> 7) - 1);*/
          CONSTRAIN_MAX(dyn->refresh_margin[p][dch],
                  (dyn->t_refi_x1_x32[p][dch] >> 7) - 1);
        } else {
          /*dwc_cinit_print("dyn->refresh_margin=%0d, max=%0d\n",dyn->refresh_margin[p][dch], (dyn->t_refi_x1_x32[p][dch] >> 2) - 1);*/
          CONSTRAIN_MAX(dyn->refresh_margin[p][dch], (dyn->t_refi_x1_x32[p][dch] >> 2) - 1);  
        }
    } else {
        // no de-rating dcheck
        if(dyn->t_refi_x1_sel[p][dch] && cfg->per_bank_refresh) {
          CONSTRAIN_MAX(dyn->refresh_margin[p][dch],
                  (dyn->t_refi_x1_x32[p][dch] >> 5) - 1);
        } else {
          CONSTRAIN_MAX(dyn->refresh_margin[p][dch],
                  (dyn->t_refi_x1_x32[p][dch] >> 1) - 1);  
        }        
    }
  } 


#endif //MEMC_LPDDR4 

#ifdef MEMC_DDR4 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  if(IS_DDR5) {
    uint32_t t_refi = (timing->ddr5_trefi1_ps / hdlr->spdData_m.tck_ps[p]) / 32;
    dyn->t_refi_x1_x32[p][dch] = t_refi; // set tREFI1 always
  }
  else if(IS_DDR4) {
    uint32_t t_refi = (timing->ddr4_trefi_ps / hdlr->spdData_m.tck_ps[p]) / 32;
    dyn->t_refi_x1_x32[p][dch] = (qdyn->fgr_mode == 2) ? (t_refi >> 2) : ((qdyn->fgr_mode == 1) ? (t_refi >> 1) : t_refi);
  }
#endif //MEMC_DDR4 

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG0 ,t_refi_x1_x32 ,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG0 ,refresh_margin ,p,dch);
/*  if(IS_LPDDR5) {
   float tck= hdlr->spdData_m.tck_ps[p];
   tck=(tck/1000)*32;
   uint32_t div=tck;
    dyn->refresh_to_x1_x32[p]=CEIL(timing->lpddr5_trefi_ps,div);
    /// @todo workaround until register bit width is expanded
    if(dyn->refresh_to_x1_x32[p]>31) {
      dwc_cinit_print("WARNING setting refresh_to_x1_x32 to 31 as a workaround\n");
      dyn->refresh_to_x1_x32[p]=31;
    }
  }*/
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG0 ,refresh_to_x1_x32 ,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG0[%0d]= 0x%x\n",p, reg->value ));
}

/** @brief function to setup the register field values for RFSHSET1TMG
 * @note t_rfc_min is calculated by ddr_timing.c and is not  
 * */
void cinit_prgm_RFSHSET1TMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG1); 
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  
#ifdef MEMC_DDR4 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  if (IS_DDR4) {
    if (qdyn->fgr_mode == 2) {
      dyn->t_rfc_min[p][dch]=CEIL( timing->ddr4_trfc_min4_ps, hdlr->spdData_m.tck_ps[p]);
    } else if (qdyn->fgr_mode == 1) {
      dyn->t_rfc_min[p][dch]=CEIL( timing->ddr4_trfc_min2_ps, hdlr->spdData_m.tck_ps[p]);
    } else {
      dyn->t_rfc_min[p][dch]=CEIL( timing->ddr4_trfc_min_ps, hdlr->spdData_m.tck_ps[p]);
    }
  } else if (IS_DDR5) { 
    ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[p]);
    if(mregs->mr4.refresh_trfc_mode == 0) {
      dyn->t_rfc_min[p][dch] = CEIL(timing->ddr5_trfc1_ps,hdlr->spdData_m.tck_ps[p]);
    } else if(mregs->mr4.refresh_trfc_mode == 1) {
      dyn->t_rfc_min[p][dch] = CEIL(timing->ddr5_trfc2_ps,hdlr->spdData_m.tck_ps[p]);
    }
  }
#endif
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4) {
    if (cfg->per_bank_refresh){
      dyn->t_rfc_min[p][dch]= cinit_ps_to_tck(timing->lpddr4_trfcpb,hdlr->spdData_m.tck_ps[p]);
    } else {
      dyn->t_rfc_min[p][dch]= cinit_ps_to_tck(timing->lpddr4_trfcab,hdlr->spdData_m.tck_ps[p]);
    }
  } else if( IS_LPDDR5 ) {
    if (cfg->per_bank_refresh){
      dyn->t_rfc_min[p][dch]=cinit_ps_to_tck(timing->lpddr5_trfcpb_ps,hdlr->spdData_m.tck_ps[p]);
    } else {
      dyn->t_rfc_min[p][dch]=cinit_ps_to_tck(timing->lpddr5_trfcab_ps,hdlr->spdData_m.tck_ps[p]);
    }
  }
#endif
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG1 ,t_rfc_min ,p,dch);
  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG1[%0d]= 0x%x\n",p,reg->value ));
}


/** @brief function to setup the register field values for RFSHSET1TMG1
 *  @note tpbr2pbr and t_rfc_min_dlr are calculated and do not take
 * values from mctl_static_cfg_t or mctl_dyn_cfg_t
 * */
void cinit_prgm_RFSHSET1TMG2 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN    
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG2, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG2)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG2)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG2); 
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
#ifdef DDRCTL_LPDDR
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  dyn->t_pbr2act[p][dch] = pre_cfg->t_pbr2act[p][dch]; 
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG2,t_pbr2act,p,dch);
  dyn->t_pbr2pbr[p][dch] = pre_cfg->t_pbr2pbr[p][dch]; 
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG2,t_pbr2pbr,p,dch);

#endif // DDRCTL_LPDDR

#ifdef UMCTL2_CID_EN
  uint32_t t_rfc_min_dlr;
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  if(IS_DDR4){
    if( qdyn->fgr_mode == 2 ) {
      dyn->t_rfc_min_dlr[p][dch]=CEIL(timing->ddr4_trfc_dlr4_ps, hdlr->spdData_m.tck_ps[p]);
    } else if(qdyn->fgr_mode == 1) {
      dyn->t_rfc_min_dlr[p][dch]=CEIL(timing->ddr4_trfc_dlr2_ps, hdlr->spdData_m.tck_ps[p]);
    } else {
      dyn->t_rfc_min_dlr[p][dch]=CEIL(timing->ddr4_trfc_dlr_ps, hdlr->spdData_m.tck_ps[p]);
    }
  } else if(IS_DDR5) {
    if(qdyn->fgr_mode == 1) {
      dyn->t_rfc_min_dlr[p][dch]=CEIL(timing->ddr5_trfc2_dlr_ps, hdlr->spdData_m.tck_ps[p]);
    } else {
      dyn->t_rfc_min_dlr[p][dch]=CEIL(timing->ddr5_trfc1_dlr_ps, hdlr->spdData_m.tck_ps[p]);
    }
  }
  CONSTRAIN_INSIDE(dyn->t_rfc_min_dlr[p][dch],0,1024);
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG2,t_rfc_min_dlr,p,dch);

#endif // UMCTL2_CID_EN
  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG2[%0d]= 0x%x\n",p,reg->value ));
#endif 
}

void cinit_prgm_RFSHSET1TMG4 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
#ifdef MEMC_NUM_RANKS_GT_1
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG4, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG4)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG4)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG4); 
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn, RFSHSET1TMG4 ,refresh_timer1_start_value_x32 ,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(dyn, RFSHSET1TMG4 ,refresh_timer0_start_value_x32 ,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG4= 0x%x\n",reg->value ));
#endif  
}
void cinit_prgm_RFSHSET1TMG5 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
#ifdef MEMC_NUM_RANKS_GT_2
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG5, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG5)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG5)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG5); 
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG5 ,refresh_timer2_start_value_x32 ,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG5 ,refresh_timer3_start_value_x32 ,p,dch);
  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG5= 0x%x\n",reg->value ));
#endif  
}

void cinit_prgm_RFSHSET1TMG6 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
#ifdef UMCTL2_CID_EN
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG6, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG6)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG6)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG6); 

  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,RFSHSET1TMG6 ,refresh_timer_lr_offset_x32,p,dch);
  // TODO ADD CONSTRAINT to dcheck value.
  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG6= 0x%x\n",reg->value ));
#endif
}

void cinit_prgm_ZQSET1TMG0 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,ZQSET1TMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, ZQSET1TMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, ZQSET1TMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, ZQSET1TMG0); 
#ifdef MEMC_LPDDR4
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  if( IS_LPDDR4 ) {
    cfg->t_zq_short_nop[p][dch]=timing->lpddr4_tzqcs;
    cfg->t_zq_long_nop[p][dch]=timing->lpddr4_tzqcl;
  } else if(IS_LPDDR5) {
      cfg->t_zq_short_nop[p][dch]=cinit_ps_to_tck(timing->lpddr5_tzqlat_ps,hdlr->spdData_m.tck_ps[p]);
      // Bug 8603: Add a margin of 10 cycles to account for internal DUT delays
      cfg->t_zq_long_nop[p][dch]=CEIL(timing->lpddr5_tzqcal_ps,hdlr->spdData_m.tck_ps[p]) + 10;
  }
#endif //MEMC_LPDDR4
#ifdef MEMC_DDR4
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  if( IS_DDR4 ) {
    cfg->t_zq_short_nop[p][dch]=timing->ddr4_tzqcs_tck;
    cfg->t_zq_long_nop[p][dch]=timing->ddr4_tzqoper_tck;
  }
  else if(IS_DDR5){ 
    cfg->t_zq_short_nop[p][dch]=cinit_ps_to_tck(timing->ddr5_tzqlat_ps,hdlr->spdData_m.tck_ps[p]);
    cfg->t_zq_long_nop[p][dch]=CEIL(timing->ddr5_tzqcal_ps,hdlr->spdData_m.tck_ps[p]);
  } 
#endif //MEMC_DDR4
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,ZQSET1TMG0,t_zq_short_nop,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,ZQSET1TMG0,t_zq_long_nop,p,dch);
  LOG_MESSAGE(hdlr, 1, ("ZQSET1TMG0[%0d]= 0x%x\n",p,reg->value ));
}

void cinit_prgm_ZQSET1TMG1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) { 
  TRACE();
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,ZQSET1TMG1,_CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, ZQSET1TMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, ZQSET1TMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, ZQSET1TMG1); 

#ifdef MEMC_LPDDR4
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[0]);
  if(IS_LPDDR4) {
    cfg->t_zq_reset_nop[p][dch]=timing->lpddr4_tzqreset;
  } else if(IS_LPDDR5) {
    cfg->t_zq_reset_nop[p][dch]=cinit_ps_to_tck(timing->lpddr5_tzqreset_ps, hdlr->spdData_m.tck_ps[0]);
  }
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,ZQSET1TMG1,t_zq_reset_nop,p,dch);
#endif //MEMC_LPDDR4
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,ZQSET1TMG1,t_zq_short_interval_x1024,p,dch);

  LOG_MESSAGE(hdlr, 1, ("ZQSET1TMG1= 0x%x\n",reg->value ));
}

/** @brief  function to setup the register field values for PWRTMG. */
void cinit_prgm_PWRTMG(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch ) {
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,PWRTMG, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, PWRTMG)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, PWRTMG)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, PWRTMG); 

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamci configuration options.

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PWRTMG,selfref_to_x32, p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, PWRTMG,powerdown_to_x32, p, dch);

  LOG_MESSAGE(hdlr, 1, ("PWRTMG= 0x%x\n",
               reg->value ));
}

void cinit_prgm_SCHEDTMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, SCHEDTMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, SCHEDTMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, SCHEDTMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, SCHEDTMG0); 
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamci configuration options.

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,SCHEDTMG0,rdwr_idle_gap,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,SCHEDTMG0,pageclose_timer,p,dch);


  LOG_MESSAGE(hdlr, 1, ("SCHEDTMG0= 0x%x\n",reg->value ));
}

void cinit_prgm_PERFLPR1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, PERFLPR1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, PERFLPR1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, PERFLPR1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, PERFLPR1); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PERFLPR1, lpr_xact_run_length, p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PERFLPR1, lpr_max_starve, p, dch);
  LOG_MESSAGE(hdlr, 1, ("PERFLPR1= 0x%x\n",reg->value ));
}

void cinit_prgm_HWLPTMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, HWLPTMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, HWLPTMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, HWLPTMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, HWLPTMG0); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);


  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,HWLPTMG0,hw_lp_idle_x32,p,dch);
  CONSTRAIN_INSIDE(reg->hw_lp_idle_x32, 0, 0xFFF);

  LOG_MESSAGE(hdlr, 1, ("HWLPTMG0= 0x%x\n",reg->value ));
}

/** @brief function to setup the register field values for DERATEVAL0.
 * 
 */
void cinit_prgm_DERATEVAL0(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_LPDDR4
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DERATEVAL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DERATEVAL0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DERATEVAL0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DERATEVAL0); 

  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->derated_t_rcd[p][dch]=pre_cfg->derated_t_rcd[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DERATEVAL0 ,derated_t_rcd,p,dch);
  CONSTRAIN_INSIDE(reg->derated_t_rcd, 1, 0xff); // cannot be zerom 8bits 

  qdyn->derated_t_ras_min[p][dch]=pre_cfg->derated_t_ras_min[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DERATEVAL0 ,derated_t_ras_min,p,dch);
  CONSTRAIN_INSIDE(reg->derated_t_ras_min, 1, 0xff); // cannot be zerom 8bits 

  qdyn->derated_t_rp[p][dch]=pre_cfg->derated_t_rp[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DERATEVAL0 ,derated_t_rp,p,dch);
  CONSTRAIN_INSIDE(reg->derated_t_rp, 1, 0x7f); // cannot be zerom 7bits 

  qdyn->derated_t_rrd[p][dch]=pre_cfg->derated_t_rrd[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DERATEVAL0 ,derated_t_rrd,p,dch);
  CONSTRAIN_INSIDE(reg->derated_t_rrd, 1, 0x3f); // cannot be zerom 6bits 


  LOG_MESSAGE(hdlr, 1, ("DERATEVAL0[%0d]= 0x%x\n",p,
               reg->value ));
  
#endif
}

/** @brief function to setup the register field values for DERATEVAL1.
 * 
 */
void cinit_prgm_DERATEVAL1(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_LPDDR4
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DERATEVAL1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DERATEVAL1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DERATEVAL1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DERATEVAL1); 

  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  qdyn->derated_t_rc[p][dch]=pre_cfg->derated_t_rc[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DERATEVAL1 ,derated_t_rc,p,dch);
  CONSTRAIN_INSIDE(reg->derated_t_rc, 1, 0xff); // cannot be zerom 8bits 

  LOG_MESSAGE(hdlr, 1, ("DERATEVAL1[%0d]= 0x%x\n",p,
               reg->value ));
  
#endif
}

/** @brief function to setup the register field values for DERATEINT. */
void cinit_prgm_DERATEINT(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_LPDDR2
  //mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg); // A handle to static configuration options.
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to static configuration options.
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DERATEINT, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DERATEINT)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DERATEINT)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DERATEINT); 

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DERATEINT,mr4_read_interval,p,dch);
  CONSTRAIN_MIN(reg->mr4_read_interval,1); // cannot be zero

  LOG_MESSAGE(hdlr, 1, ("DERATEINT[%0d]= 0x%x\n",p,
               reg->value ));
#endif  
}

void cinit_prgm_RANKTMG0 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RANKTMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RANKTMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RANKTMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RANKTMG0); 
  
#ifdef MEMC_NUM_RANKS_GT_1
#ifdef MEMC_LPDDR4
  uint32_t wr_gap_min, rd_gap_min;
  uint32_t ratio;
  uint32_t trpre_wck;
  uint32_t trpst_wck;
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  if(IS_LPDDR4) {
      wr_gap_min=pre_cfg->odtloff[p][dch]-pre_cfg->odtlon[p][dch]-
          cfg->burst_rdwr + 1;
      rd_gap_min= 4 +hdlr->memCtrlr_m.lpddr4_mr[p].mr1.rd_postamble;

      // dcheck if min is being violated.
      // then overwrite with min
      if(wr_gap_min> qdyn->diff_rank_wr_gap[p][dch]) {
          dwc_cinit_print("%0d:  attempt to set diff_rank_wr_gap=%0d less than min\n",
                  p, qdyn->diff_rank_wr_gap[p][dch]  );
          qdyn->diff_rank_wr_gap[p][dch]=wr_gap_min;
      }
      if( rd_gap_min> qdyn->diff_rank_rd_gap[p][dch]) {
          qdyn->diff_rank_rd_gap[p][dch]=rd_gap_min;
      }
  } else if(IS_LPDDR5) {
      if (hdlr->memCtrlr_m.lpddr5_mr[p].mr11.dq_odt>0) {    // ODT ON
         if (qdyn->wck_on[dch] == 1) {                      // WCK_ON = 1
            qdyn->diff_rank_wr_gap[p][dch] = pre_cfg->diff_rank_wr_gap_wck_on_odt[p][dch];
            qdyn->diff_rank_rd_gap[p][dch] = pre_cfg->diff_rank_rd_gap_wck_on_odt[p][dch];
         } else {                                           // WCK_ON = 0
            qdyn->diff_rank_wr_gap[p][dch] = pre_cfg->diff_rank_wr_gap_odt[p][dch];
            qdyn->diff_rank_rd_gap[p][dch] = pre_cfg->diff_rank_rd_gap_odt[p][dch];
         }
      } else {                                              // ODT OFF
         if (qdyn->wck_on[dch] == 1) {                      // WCK_ON = 1
            qdyn->diff_rank_wr_gap[p][dch] = pre_cfg->diff_rank_wr_gap_wck_on[p][dch];
            qdyn->diff_rank_rd_gap[p][dch] = pre_cfg->diff_rank_rd_gap_wck_on[p][dch];
         } else {                                           // WCK_ON = 0
            qdyn->diff_rank_wr_gap[p][dch] = pre_cfg->diff_rank_wr_gap[p][dch];
            qdyn->diff_rank_rd_gap[p][dch] = pre_cfg->diff_rank_rd_gap[p][dch];
         }
      }
  }
#endif //MEMC_LPDDR4
  /// @todo write constraint for diff_rank_rd_gap DDR4/5
  /// @todo write constraint for diff_rank_rd_gap LPDDR5

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANKTMG0,diff_rank_rd_gap, p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANKTMG0,diff_rank_wr_gap, p, dch);
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4) {
    CONSTRAIN_INSIDE(reg->diff_rank_rd_gap,3,15);
    CONSTRAIN_INSIDE(reg->diff_rank_wr_gap,wr_gap_min,15);
  }
#endif //MEMC_LPDDR4

#endif // MEMC_NUM_RANKS_GT_1  

  LOG_MESSAGE(hdlr, 1, ("RANKTMG0[%d]= 0x%x\n",p,reg->value ));
#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1   
}

void cinit_prgm_RFSHSET1TMG3 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG3)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG3); 
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  
  dyn->t_rfcsb[p][dch] = CEIL(timing->ddr5_trfcsb_ps,hdlr->spdData_m.tck_ps[p]);
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG3 ,t_rfcsb,p, dch);

  dyn->t_refsbrd[p][dch] = CEIL(timing->ddr5_trefsbrd_ps,hdlr->spdData_m.tck_ps[p]);
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG3 ,t_refsbrd,p, dch);

  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG3[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif
}

void cinit_prgm_DRAMSET2TMG0 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG0); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  // SDRAM Timig register set 2 has the same value as set 1
  qdyn->t_ccd_w_s_2[p][dch] = qdyn->t_ccd_w_s[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG0 ,t_ccd_w_s_2,p, dch);

  qdyn->t_ccd_r_s_2[p][dch] = qdyn->t_ccd_r_s[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG0 ,t_ccd_r_s_2,p, dch);

  qdyn->t_ccd_w_2[p][dch] = qdyn->t_ccd_w[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG0 ,t_ccd_w_2,p, dch);

  qdyn->t_ccd_r_2[p][dch] = qdyn->t_ccd_r[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG0 ,t_ccd_r_2,p, dch);
  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG0[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif // DDRCTL_TWO_TIMING_SETS_EN
#endif // MEMC_DDR5
}

void cinit_prgm_DRAMSET2TMG1 (SubsysHdlr_t *hdlr,uint32_t p,uint32_t dch) { 
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG1); 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  // SDRAM Timig register set 2 has the same value as set 1
  qdyn->t_wr2pre_2[p][dch] = qdyn->wr2pre[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG1 ,t_wr2pre_2,p, dch);

  qdyn->t_faw_2[p][dch] = qdyn->t_faw[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG1 ,t_faw_2,p, dch);

  qdyn->t_ras_min_2[p][dch] = qdyn->t_ras_min[p][dch];
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG1 ,t_ras_min_2,p, dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG1[p%d][dch%0d]= 0x%x\n",p,dch,reg->value ));
#endif // DDRCTL_TWO_TIMING_SETS_EN
#endif // MEMC_DDR5
}

/** @brief Setup register values for INITMR0.
 * @note only DDR4 or LPDDR4 supported here.
 */
void cinit_prgm_INITMR0 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR0)
  DWC_DDRCTL_CAST_REG_FREQP(p, ch, REGB_FREQ, INITMR0); 
  
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
#ifdef MEMC_DDR4
  if(IS_DDR4) {
      ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
      qdyn->mr[p][ch] = 
          SNPS_SETREGBITFIELDSHIFT((mregs->mr0.wr_recovery >> 3), 1, 13) |	//4'b0 mr0[15:12]
          SNPS_SETREGBITFIELDSHIFT((mregs->mr0.cl >> 4), 1, 12) |	//4'b0 mr0[15:12]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr0.wr_recovery, 3, 9) |	//mr0_wr_recovery  mr0[11:9]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr0.dll_reset , 1, 8)	|	//mr0[8] :DLL Reset
          SNPS_SETREGBITFIELDSHIFT(0, 1, 7) |	//mr0[7] :TM=0
          SNPS_SETREGBITFIELDSHIFT((mregs->mr0.cl >> 1), 3, 4) |	//mr0_cl[3:1]  mr0[6:4]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr0.burst_type, 1, 3)	|	//mr0_burst_type  mr0[3:3]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr0.cl, 1, 2)	|	//mr0_cl[0]  mr0[2:2]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr0.burst_length, 2, 0);     	//mr0_burst_length  mr0[1:0]

     qdyn->emr[p][ch] = SNPS_SETREGBITFIELDSHIFT(0, 5, 11) |	//5'b0  mr1[15:11]
         SNPS_SETREGBITFIELDSHIFT(mregs->mr1.rtt_nom, 3, 8) |	//mr1_rtt[2:0]  mr1[10:8]
         SNPS_SETREGBITFIELDSHIFT(0, 3, 5) |	//3'b0   mr1[7:5]
         SNPS_SETREGBITFIELDSHIFT(mregs->mr1.al, 2, 3) |	//mr1_al  mr1[4:3]
         SNPS_SETREGBITFIELDSHIFT(mregs->mr1.output_driver_impedance, 2, 1)	|	//mr1_output_driver_impedance  mr1[2:1]
         SNPS_SETREGBITFIELDSHIFT(mregs->mr1.dll_enable, 1, 0);	      
  } else if(IS_DDR5) {
    // dont care
    qdyn->mr[p][ch] = 0;
    qdyn->emr[p][ch] = 0;
  }
#endif  
#ifdef MEMC_LPDDR4  
  if(IS_LPDDR4) {
      lpddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.lpddr4_mr[p]);
      mregs->mr1.wr_preamble=1; // required

          //To configure MR1 of LPDDR4
      qdyn->mr[p][ch] = SNPS_SETREGBITFIELDSHIFT(0, 8, 8) | // mr1[15:8]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr1.rd_postamble, 1, 7) |    // mr1[7]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr1.wr_recovery, 2, 4) |    // mr1[6:4] 
          SNPS_SETREGBITFIELDSHIFT(mregs->mr1.rd_preamble, 1, 3) |    // mr1[3] 
          SNPS_SETREGBITFIELDSHIFT(mregs->mr1.wr_preamble, 1, 2) |    // mr1[2] 
          SNPS_SETREGBITFIELDSHIFT(mregs->mr1.burst_length, 2, 0); // mr1[1:0]

          //To configure MR2 of LPDDR4
    qdyn->emr[p][ch] =  SNPS_SETREGBITFIELDSHIFT(0, 9, 7)    |    // mr2[15:7]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr2.wls, 1, 6) |    // mr2[6]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr2.rl_wl, 6, 0);   // mr2[5:0]
  } else if(IS_LPDDR5) {
      // dont care
      qdyn->mr[p][ch] = 0;
      qdyn->emr[p][ch] = 0;
  }
#endif
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, INITMR0, mr, p, ch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, INITMR0, emr, p, ch);
  LOG_MESSAGE(hdlr, 1, ("INITMR0[%d]= 0x%x\n",p,reg->value ));
}

/** @brief Setup register values for INITMR1. */
void cinit_prgm_INITMR1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) { 
  TRACE();

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR1)
  DWC_DDRCTL_CAST_REG_FREQP(p, ch, REGB_FREQ, INITMR1); 
 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

#ifdef MEMC_DDR4
  REGB_DDRC_CH0_RFSHMOD1_struct_t
      *rfshmod1_reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_RFSHMOD1_reg;  
  if(IS_DDR4) {
   ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
   qdyn->emr2[p][ch] =   SNPS_SETREGBITFIELDSHIFT(0, 3, 13) | // mr2[15:13]
     SNPS_SETREGBITFIELDSHIFT(mregs->mr2.write_crc, 1, 12)    | // mr2[12]
     SNPS_SETREGBITFIELDSHIFT(0, 4, 8)                  | // mr2[11:8]
     SNPS_SETREGBITFIELDSHIFT(mregs->mr2.auto_self_ref, 2, 6)  | // mr2[7:6]
     SNPS_SETREGBITFIELDSHIFT(mregs->mr2.cwl, 3, 3)            | // mr2[5:3]
     SNPS_SETREGBITFIELDSHIFT(0, 3, 0);                   // mr2[2:0]

   qdyn->emr3[p][ch] = SNPS_SETREGBITFIELDSHIFT(0, 5, 11)     | // mr3[15:11]
     SNPS_SETREGBITFIELDSHIFT(mregs->mr3.wcl, 2, 9)              | // mr3[10:9]
     SNPS_SETREGBITFIELDSHIFT(rfshmod1_reg->fgr_mode, 2, 6) | // mr3[8:6]
     SNPS_SETREGBITFIELDSHIFT(0, 2, 4) | // mr3[5:4]
     SNPS_SETREGBITFIELDSHIFT(mregs->mr3.geardown, 2, 3) | // mr3[3]
     SNPS_SETREGBITFIELDSHIFT(0, 3, 0); // mr3[2:0]
  } else if(IS_DDR5) {
    // dont care
    qdyn->emr2[p][ch] = 0;
    qdyn->emr3[p][ch] = 0;
  }
#endif
#ifdef MEMC_LPDDR4
  DWC_DDRCTL_DCHC_REG_STRUCT(0,REGB_DDRC,INITTMG0, _CH)
      *inittmg0_reg=&hdlr->memCtrlr_m.regs.DWC_DDRCTL_DCHC_REG_EL(0,REGB_DDRC,INITTMG0, _CH);

  if(IS_LPDDR4) {
   lpddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.lpddr4_mr[p]);
   mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
   CONSTRAIN_EQ(mregs->mr3.write_dbi, qdyn->wr_dbi_en[0]);
   CONSTRAIN_EQ(mregs->mr3.read_dbi, qdyn->rd_dbi_en[0]);
   //To configure MR3 of LPDDR4
   qdyn->emr2[p][ch] =   SNPS_SETREGBITFIELDSHIFT(0, 8, 8) | // mr3[15:8]
       SNPS_SETREGBITFIELDSHIFT(mregs->mr3.write_dbi, 1, 7) |   // mr3[7] : DBI-WR
       SNPS_SETREGBITFIELDSHIFT(mregs->mr3.read_dbi, 1, 6) |    // mr3[6] : DBI-RD
       SNPS_SETREGBITFIELDSHIFT(0, 3, 3)          |    // mr3[5:3] : PDDS
       SNPS_SETREGBITFIELDSHIFT(0, 1, 2)          |   // mr3[2] : RFU
       SNPS_SETREGBITFIELDSHIFT(mregs->mr3.wr_postamble, 1, 1)  |   // mr3[1] : WR-PST
       SNPS_SETREGBITFIELDSHIFT(mregs->mr3.pu_cal, 1, 0);           // mr3[0] : PU-CA
          //To configure MR13 of LPDDR4   
   qdyn->emr3[p][ch] = SNPS_SETREGBITFIELDSHIFT(0, 8, 8)     | // mr13[15:8]
       SNPS_SETREGBITFIELDSHIFT(mregs->mr13.fsp_op, 1, 7)        | // mr13[7] : FSP-OP
       SNPS_SETREGBITFIELDSHIFT(mregs->mr13.fsp_wr, 1, 6)        | // mr13[6] : FSP-WR
       SNPS_SETREGBITFIELDSHIFT(mregs->mr13.dmd, 1, 5) | // mr13[5] : DMD 
       SNPS_SETREGBITFIELDSHIFT(0, 1, 4)                 | // mr13[4]
       SNPS_SETREGBITFIELDSHIFT(inittmg0_reg->skip_dram_init>>1, 1, 3) | // mr13[3]
       SNPS_SETREGBITFIELDSHIFT(0, 3, 0); // // mr13[2:0]
  } else if (IS_LPDDR5) { 
      qdyn->emr2[p][ch] = 0;
      qdyn->emr3[p][ch] = 0;
  }
#endif
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, INITMR1, emr2, p, ch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, INITMR1, emr3, p, ch);
  LOG_MESSAGE(hdlr, 1, ("INITMR1[%d]= 0x%x\n",p,reg->value ));

}
/** @brief Setup register values for INITMR2. */
void cinit_prgm_INITMR2 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR2, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR2)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR2)
  DWC_DDRCTL_CAST_REG_FREQP(p, ch, REGB_FREQ, INITMR2); 
 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
#ifdef MEMC_DDR4
  if(IS_DDR4) {   
   ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
      qdyn->mr4[p][ch] = SNPS_SETREGBITFIELDSHIFT(0, 3, 13)  | // mr4[15:13]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr4.wr_preamble,1,12) | // mr4[12]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr4.rd_preamble,1,11) | // mr4[11]
          SNPS_SETREGBITFIELDSHIFT(0,1,10)               | // mr4[10]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr4.selfref_abort,1,9) |// mr4[9]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr4.cal,2,6)          |// mr4[8:6]
          SNPS_SETREGBITFIELDSHIFT(0,2,4)               | // mr4[4]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr4.fgr_mode,1,3) | // mr4[3]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr4.refresh_range,1,2) | // mr4[2]
          SNPS_SETREGBITFIELDSHIFT(0,2,0); // mr4[1:0] 

      qdyn->mr5[p][ch] = SNPS_SETREGBITFIELDSHIFT(0, 3, 13)  | // mr5[15:13]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr5.read_dbi,1,12) | // mr5[12]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr5.write_dbi,1,11) | // mr5[11]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr5.data_mask,1,10) | // mr5[10]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr5.ca_parity_persistent,1,9) | // mr5[9]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr5.rtt_park,3,6) | // mr5[8:6]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr5.dis_odt_input_buf_in_pd,1,5) | // mr5[5]
          SNPS_SETREGBITFIELDSHIFT(0,2,3) | // mr4[4:3]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr5.parity_latency_mode,3,0); // mr5[2:0]
  } else if (IS_DDR5) { 
      qdyn->mr4[p][ch] = 0;
      qdyn->mr5[p][ch] = 0;
  }
#endif  
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4 ) {
   lpddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.lpddr4_mr[p]);
      qdyn->mr4[p][ch] = SNPS_SETREGBITFIELDSHIFT(0, 8, 8)  | // mr11[15:8]
          SNPS_SETREGBITFIELDSHIFT(0, 1, 7)  | // mr11[7] RFU
          SNPS_SETREGBITFIELDSHIFT(mregs->mr11.ca_odt, 3, 4)  | // mr11[6:4] TUF
          SNPS_SETREGBITFIELDSHIFT(0, 1, 3)  | // mr11[3] RFU
          SNPS_SETREGBITFIELDSHIFT(mregs->mr11.dq_odt, 3, 0); // mr11[2:0] DQ ODT

      qdyn->mr5[p][ch] = SNPS_SETREGBITFIELDSHIFT(0, 9, 7)  | // mr12[15:7]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr12.vr_ca, 1, 6)  | // mr12[6] VR-CA
          SNPS_SETREGBITFIELDSHIFT(mregs->mr12.vref_ca, 6, 0)  ; // mr12[5:0] VR-CA

  } else if(IS_LPDDR5) {
      qdyn->mr4[p][ch] = 0;
      qdyn->mr5[p][ch] = 0;

  }
#endif
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, INITMR2, mr4, p, ch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, INITMR2, mr5, p, ch);
  LOG_MESSAGE(hdlr, 1, ("INITMR2[%d]= 0x%x\n",p,reg->value ));

}
void cinit_prgm_INITMR3 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) { 
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR3)
  DWC_DDRCTL_CAST_REG_FREQP(p, ch, REGB_FREQ, INITMR3); 
 
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
#ifdef MEMC_DDR4  
  if(IS_DDR4) {
   ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
    
      qdyn->mr6[p][ch] =SNPS_SETREGBITFIELDSHIFT(0, 3, 13)  | // mr6[15:13]
          SNPS_SETREGBITFIELDSHIFT(mregs->mr6.tccd_l,3,10) | // mr6[12]
          SNPS_SETREGBITFIELDSHIFT(0, 10, 0);
      qdyn->mr22[p][ch]=0;
  } else if (IS_DDR5) { 
      qdyn->mr6[p][ch] = 0;
      qdyn->mr22[p][ch] = 0;
  }
#endif
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4) {
   lpddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.lpddr4_mr[p]);

      qdyn->mr6[p][ch] =SNPS_SETREGBITFIELDSHIFT(0, 8, 8)         | // mr14[15:8]
          SNPS_SETREGBITFIELDSHIFT(0,1,7)                     | // mr14[7] RFU
          SNPS_SETREGBITFIELDSHIFT(mregs->mr14.vr_dq,1,6)     | // mr14[6] VR(DQ)
          SNPS_SETREGBITFIELDSHIFT(mregs->mr14.vref_dq,6,0)   ; //mr14[5:0] VREF(DQ)
       
      qdyn->mr22[p][ch]= SNPS_SETREGBITFIELDSHIFT(0, 8, 8)  | // mr22[15:8] : not used
          SNPS_SETREGBITFIELDSHIFT(mregs->mr22.odtd,2,6)     |// mr22[7:6]  : ODTD for x8_2ch(byte) mode
          SNPS_SETREGBITFIELDSHIFT(mregs->mr22.odtd_ca,1,5)     |// mr22[5] : ODTD-CA
          SNPS_SETREGBITFIELDSHIFT(mregs->mr22.odtd_cs,1,4)     |// mr22[4] : ODTD-CS
          SNPS_SETREGBITFIELDSHIFT(mregs->mr22.odtd_ck,1,3)     |// mr22[3] : ODTD-CK
          SNPS_SETREGBITFIELDSHIFT(mregs->mr22.soc_odt,3,0)    ;// mr22[3] : SOC ODTD

  } else if(IS_LPDDR5) {
   lpddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.lpddr5_mr[p]);
      // dont care
      qdyn->mr6[p][ch] =0;
      qdyn->mr22[p][ch]=0;
#ifdef MEMC_LINK_ECC
      qdyn->mr22[p][ch]= SNPS_SETREGBITFIELDSHIFT(0, 8, 8)                | // mr22[15:8] : not used
                         SNPS_SETREGBITFIELDSHIFT(mregs->mr22.recc, 2, 6) | // mr22[ 7:6] : Read link ECC
                         SNPS_SETREGBITFIELDSHIFT(mregs->mr22.wecc, 2, 4) | // mr22[ 5:4] : Writr link ECC
                         SNPS_SETREGBITFIELDSHIFT(0, 4, 0);                 // mr22[ 3:0] : not used
#endif
  }
#endif
#ifdef MEMC_LPDDR4
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, INITMR3, mr22, p, ch);
#endif
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn, INITMR3, mr6, p, ch);
  LOG_MESSAGE(hdlr, 1, ("INITMR3[%d]= 0x%x\n",p,reg->value ));
}

void cinit_prgm_DRAMSET1TMG11 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_DDR
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG11, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG11)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG11)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG11);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG11,post_mpsm_gap_x32,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG11,t_mpx_lh,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG11,t_mpx_s,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG11,t_ckmpe,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG11[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_DDR
}

void cinit_prgm_DRAMSET1TMG15 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_DDR
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG15, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG15)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG15)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG15);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG15,en_dfi_lp_t_stab,p,dch);

#ifdef UMCTL2_HWFFC_EN
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG15,en_hwffc_t_stab,p,dch);
#endif // UMCTL2_HWFFC_EN

  if(IS_DDR5 && IS_RDIMM)qdyn->t_stab_x32[p][dch]= CEIL(pre_cfg->t_stab01[p][dch],1024);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG15,t_stab_x32,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG15[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_DDR
}

void cinit_prgm_DRAMSET1TMG23 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_LPDDR
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG23, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG23)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG23)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG23);

  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  dyn->t_xsr_dsm_x1024[p][dch]= CEIL((timing->lpddr5_txsr_dsm_us*1000000/hdlr->spdData_m.tck_ps[p]),1024);
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,DRAMSET1TMG23,t_xsr_dsm_x1024,p,dch);
  if(hdlr->phy_training==0) {
    // full training so use normal jedec value
    dyn->t_pdn_dsm_x1024[p][dch]=(timing->lpddr5_tpdn_dsm_ms*1000000000/hdlr->spdData_m.tck_ps[p])/1024;
  } else {
    // simulation mode, use us instead of ms
    dyn->t_pdn_dsm_x1024[p][dch]=CEIL((timing->lpddr5_tpdn_dsm_ms*1000000/hdlr->spdData_m.tck_ps[p]),1024);
  }
  APPLY_CFG_TO_REGFIELD_P_CH(dyn,DRAMSET1TMG23,t_pdn_dsm_x1024,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,DRAMSET1TMG23,t_pdn,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG23[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_LPDDR
}

void cinit_prgm_DRAMSET2TMG2 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG2, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG2)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG2)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG2);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG2,rd2pre_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG2,t_rc_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG2[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN
#endif // MEMC_DDR5
}

void cinit_prgm_DRAMSET2TMG3 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG3)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG3);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG3,rd2wr_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG3,wr2rd_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG3[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif // MEMC_DDR5
}

void cinit_prgm_DRAMSET2TMG4 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG4, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG4)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG4)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG4);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG4,t_wr2rd_dlr_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG4,t_wr2rd_dpr_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG4,t_rd2wr_dlr_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG4,t_rd2wr_dpr_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG4[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif // MEMC_DDR5
}

void cinit_prgm_DRAMSET2TMG5 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG5, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG5)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG5)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG5);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG5,t_rcd_2,p,dch);
  CONSTRAIN_MIN(reg->t_rcd_2,1); 

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG5,t_ccd_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG5,t_rrd_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG5,t_rp_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG5[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif // MEMC_DDR5
}

void cinit_prgm_DRAMSET2TMG6 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG6, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG6)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG6)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG6);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG6,t_rrd_s_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG6,wr2rd_s_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG6[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif // MEMC_DDR5
}

void cinit_prgm_DRAMSET2TMG7 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG7, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG7)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG7)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG7);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG7,t_ccd_w2_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG7,t_ppd_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG7[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif // MEMC_DDR5
}

void cinit_prgm_DRAMSET2TMG8 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#if defined(MEMC_DDR5) && defined(UMCTL2_CID_EN)
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG8, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG8)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG8)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG8);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG8,t_ccd_dlr_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG8,t_rrd_dlr_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG8,t_faw_dlr_2,p,dch);
#ifdef UMCTL2_CRC_PARITY_RETRY
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG8,t_rp_ca_parity_2,p,dch);
#endif

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG8[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif // MEMC_DDR5 && UMCTL2_CID_EN
}

void cinit_prgm_DRAMSET2TMG9 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG9, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG9)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG9)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG9);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG9,t_xs_x32_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG9,t_xs_dll_x32_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG9,t_xs_abort_x32_2,p,dch);
  CONSTRAIN_MAX(reg->t_xs_abort_x32_2,reg->t_xs_x32_2);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG9,t_xs_fast_x32_2,p,dch);
  CONSTRAIN_MAX(reg->t_xs_fast_x32_2,reg->t_xs_x32_2);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG9[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif // MEMC_DDR5
}

void cinit_prgm_DRAMSET2TMG10 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG10, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG10)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG10)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG10);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG10,t_mr_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG10[%d]= 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif // MEMC_DDR5
}

void cinit_prgm_MRAMTMG0 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef UMCTL2_DDR4_MRAM_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,MRAMTMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, MRAMTMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, MRAMTMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, MRAMTMG0);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,MRAMTMG0,t_faw_mram,p,dch);
  #ifdef MEMC_NUM_TOTAL_BANKS_4 
    CONSTRAIN_EQ(reg->t_faw_mram,0x1); //In a 4-bank design, set this register to 0x1 independent of the frequency ratio mode.
  #endif // MEMC_NUM_TOTAL_BANKS_4

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,MRAMTMG0,t_ras_min_mram,p,dch);

  LOG_MESSAGE(hdlr, 1, ("MRAMTMG0[%d]= 0x%x\n",p,reg->value));
#endif // UMCTL2_DDR4_MRAM_EN
}

void cinit_prgm_MRAMTMG1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef UMCTL2_DDR4_MRAM_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,MRAMTMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, MRAMTMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, MRAMTMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, MRAMTMG1);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,MRAMTMG1,t_rc_mram,p,dch);

  LOG_MESSAGE(hdlr, 1, ("MRAMTMG1[%d]= 0x%x\n",p,reg->value));
#endif // UMCTL2_DDR4_MRAM_EN
}

void cinit_prgm_MRAMTMG2 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef UMCTL2_DDR4_MRAM_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,MRAMTMG2, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, MRAMTMG2)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, MRAMTMG2)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, MRAMTMG2);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,MRAMTMG2,t_rcd_mram,p,dch);
  #ifdef MEMC_FREQ_RATIO_2
    CONSTRAIN_MIN(reg->t_rcd_mram,2); //Minimum value allowed for this register is 2 when the controller is operating in 1:2 frequency ratio mode
  #endif //MEMC_FREQ_RATIO_2

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,MRAMTMG2,t_rrd_mram,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,MRAMTMG2,t_rp_mram,p,dch);

  LOG_MESSAGE(hdlr, 1, ("MRAMTMG2[%d]= 0x%x\n",p,reg->value));
#endif // UMCTL2_DDR4_MRAM_EN
}

void cinit_prgm_MRAMTMG3 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef UMCTL2_DDR4_MRAM_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,MRAMTMG3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, MRAMTMG3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, MRAMTMG3)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, MRAMTMG3);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,MRAMTMG3,t_rrd_s_mram,p,dch);

  LOG_MESSAGE(hdlr, 1, ("MRAMTMG3[%d]= 0x%x\n",p,reg->value));
#endif // UMCTL2_DDR4_MRAM_EN
}

void cinit_prgm_DFITMG3 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DFITMG3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DFITMG3)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DFITMG3);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG3,dfi_t_geardown_delay,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DFITMG3[%d]= 0x%x\n",p,reg->value));
#endif // MEMC_CMD_RTN2IDLE
#endif // DDRCTL_DDR
}

void cinit_prgm_DFIUPDTMG1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFIUPDTMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DFIUPDTMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DFIUPDTMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DFIUPDTMG1);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFIUPDTMG1,dfi_t_ctrlupd_interval_min_x1024,p,dch);
  CONSTRAIN_MIN(reg->dfi_t_ctrlupd_interval_min_x1024,0x1);

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFIUPDTMG1,dfi_t_ctrlupd_interval_max_x1024,p,dch);
  CONSTRAIN_MIN(reg->dfi_t_ctrlupd_interval_max_x1024,0x1);

  LOG_MESSAGE(hdlr, 1, ("DFIUPDTMG1[%d]= 0x%x\n",p,reg->value));
}

void cinit_prgm_RCDINIT1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#if defined(UMCTL2_HWFFC_EN) && defined(DDRCTL_DDR)
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RCDINIT1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RCDINIT1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RCDINIT1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RCDINIT1);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RCDINIT1,ctrl_word_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RCDINIT1,ctrl_word_1,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RCDINIT1[%d]= 0x%x\n",p,reg->value));
#endif // (UMCTL2_HWFFC_EN) && (DDRCTL_DDR)
}

void cinit_prgm_RCDINIT2 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#if defined(UMCTL2_HWFFC_EN) && defined(DDRCTL_DDR)
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RCDINIT2, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RCDINIT2)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RCDINIT2)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RCDINIT2);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RCDINIT2,ctrl_word_4,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RCDINIT2,ctrl_word_3,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RCDINIT2[%d]= 0x%x\n",p,reg->value));
#endif // (UMCTL2_HWFFC_EN) && (DDRCTL_DDR)
}

void cinit_prgm_RCDINIT3 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#if defined(UMCTL2_HWFFC_EN) && defined(DDRCTL_DDR)
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RCDINIT3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RCDINIT3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RCDINIT3)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RCDINIT3);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RCDINIT3,ctrl_word_6,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RCDINIT3,ctrl_word_5,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RCDINIT3[%d]= 0x%x\n",p,reg->value));
#endif // (UMCTL2_HWFFC_EN) && (DDRCTL_DDR)
}

void cinit_prgm_RCDINIT4 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#if defined(UMCTL2_HWFFC_EN) && defined(DDRCTL_DDR)
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RCDINIT4, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RCDINIT4)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RCDINIT4)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RCDINIT4);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RCDINIT4,ctrl_word_8,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RCDINIT4,ctrl_word_7,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RCDINIT4[%d]= 0x%x\n",p,reg->value));
#endif // (UMCTL2_HWFFC_EN) && (DDRCTL_DDR)
}

void cinit_prgm_DQSOSCCTL0 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef LPDDR45_DQSOSC_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DQSOSCCTL0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DQSOSCCTL0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DQSOSCCTL0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DQSOSCCTL0);

  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,DQSOSCCTL0,dqsosc_interval,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,DQSOSCCTL0,dqsosc_interval_unit,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,DQSOSCCTL0,dqsosc_enable,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DQSOSCCTL0[%d]= 0x%x\n",p,reg->value));
#endif // LPDDR45_DQSOSC_EN
}

void cinit_prgm_RANKTMG1 (SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch) { 
  TRACE();
#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg); // A handle to quasi-dynamic configuration options.
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RANKTMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RANKTMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RANKTMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RANKTMG1); 
  
#ifdef MEMC_NUM_RANKS_GT_1
#ifdef MEMC_LPDDR4
  if(IS_LPDDR5) {
      uint32_t ratio;
      uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
      ratio = (spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 2 : 4;
      if (hdlr->memCtrlr_m.lpddr5_mr[p].mr11.dq_odt>0) {    // ODT ON
         if (qdyn->wck_on[dch] == 1) {                      // WCK_ON = 1
            qdyn->wr2rd_dr[p][dch] = pre_cfg->wr2rd_dr_wck_on_odt[p][dch];
            qdyn->rd2wr_dr[p][dch] = pre_cfg->rd2wr_dr_wck_on_odt[p][dch];
         } else {                                           // WCK_ON = 0
            qdyn->wr2rd_dr[p][dch] = pre_cfg->wr2rd_dr_odt[p][dch];
            qdyn->rd2wr_dr[p][dch] = pre_cfg->rd2wr_dr_odt[p][dch];
         }
      } else {                                              // ODT OFF
         if (qdyn->wck_on[dch] == 1) {                      // WCK_ON = 1
            qdyn->wr2rd_dr[p][dch] = pre_cfg->wr2rd_dr_wck_on[p][dch];
            qdyn->rd2wr_dr[p][dch] = pre_cfg->rd2wr_dr_wck_on[p][dch];
         } else {                                           // WCK_ON = 0
            qdyn->wr2rd_dr[p][dch] = pre_cfg->wr2rd_dr[p][dch];
            qdyn->rd2wr_dr[p][dch] = pre_cfg->rd2wr_dr[p][dch];
         }
      }
   } else
#endif // MEMC_LPDDR4  
   {
      qdyn->wr2rd_dr[p][dch]=qdyn->wr2rd[p][dch];
      qdyn->rd2wr_dr[p][dch]=qdyn->rd2wr[p][dch];
   }

  /// @todo write correct constraint

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANKTMG1,wr2rd_dr, p, dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,RANKTMG1,rd2wr_dr, p, dch);

#endif // MEMC_NUM_RANKS_GT_1  

  LOG_MESSAGE(hdlr, 1, ("RANKTMG1[%d]= 0x%x\n",p,reg->value ));
#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1   
}

void cinit_prgm_DRAMSET1TMG27 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG27, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG27)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG27)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG27);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG27,t_mrr2mpc,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG27[%d] = 0x%x\n",p,reg->value));
#endif //MEMC_DDR5
}

void cinit_prgm_DRAMSET1TMG28 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef IS_DDR5_RDIMM
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG28, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG28)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG28)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG28);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  qdyn->t_srx2srx[p][dch]   = pre_cfg->t_srx2srx[p][dch];
  qdyn->t_cpded2srx[p][dch] = pre_cfg->t_cpded2srx[p][dch];
  qdyn->t_cssr[p][dch]      = pre_cfg->t_cssr[p][dch];
  
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG28,t_srx2srx,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG28,t_cpded2srx,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG28,t_cssr,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG28[%d] = 0x%x\n",p,reg->value));

#endif //IS_DDR5_RDIMM
}

void cinit_prgm_DRAMSET1TMG29 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef IS_DDR5_RDIMM

  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET1TMG29, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET1TMG29)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET1TMG29)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET1TMG29);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  
  qdyn->t_ckact[p][dch] = pre_cfg->t_ckact[p][dch];
  qdyn->t_ckoff[p][dch] = pre_cfg->t_ckoff[p][dch];
  
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG29,t_ckact,p,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET1TMG29,t_ckoff,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET1TMG29[%d] = 0x%x\n",p,reg->value));
#endif //IS_DDR5_RDIMM
}

void cinit_prgm_DRAMSET2TMG11 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DRAMSET2TMG11, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DRAMSET2TMG11)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DRAMSET2TMG11)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DRAMSET2TMG11);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DRAMSET2TMG11,t_mrr2mpc_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DRAMSET2TMG11[%d] = 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif //MEMC_DDR5
}

void cinit_prgm_DFITMG7 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFITMG7, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, DFITMG7)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, DFITMG7)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, DFITMG7);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,DFITMG7,dfi_t_2n_mode_delay,p,dch);

  LOG_MESSAGE(hdlr, 1, ("DFITMG7[%d] = 0x%x\n",p,reg->value));
#endif //MEMC_DDR5
}

void cinit_prgm_RFSHSET1TMG7 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG7, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG7)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG7)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG7);

  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);

  dyn->t_refsbrd_dlr[p][dch] = pre_cfg->t_refsbrd_dlr[p][dch];
  dyn->t_rfcsb_dlr[p][dch] = pre_cfg->t_rfcsb_dlr[p][dch];

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG7,t_refsbrd_dlr,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG7,t_rfcsb_dlr,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG7[%d] = 0x%x\n",p,reg->value));
#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
}

void cinit_prgm_RFSHSET1TMG8 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef UMCTL2_HET_RANK_RFC
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET1TMG8, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET1TMG8)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET1TMG8)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET1TMG8);

  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET1TMG8,t_rfc_min_het,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RFSHSET1TMG8[%d] = 0x%x\n",p,reg->value));
#endif //UMCTL2_HET_RANK_RFC
}

void cinit_prgm_RFSHSET2TMG3 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
#ifdef UMCTL2_CID_EN
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,RFSHSET2TMG3, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, RFSHSET2TMG3)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, RFSHSET2TMG3)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, RFSHSET2TMG3);

  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET2TMG3,t_refsbrd_dlr_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(dyn,RFSHSET2TMG3,t_rfcsb_dlr_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("RFSHSET2TMG3[%d] = 0x%x\n",p,reg->value));
#endif //UMCTL2_CID_EN
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif //MEMC_DDR5
}

void cinit_prgm_ZQSET2TMG0 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,ZQSET2TMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, ZQSET2TMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, ZQSET2TMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, ZQSET2TMG0);

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,ZQSET2TMG0,t_zq_short_nop_2,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,ZQSET2TMG0,t_zq_long_nop_2,p,dch);

  LOG_MESSAGE(hdlr, 1, ("ZQSET2TMG0[%d] = 0x%x\n",p,reg->value));
#endif // DDRCTL_TWO_TIMING_SETS_EN  
#endif //MEMC_DDR5
}

void cinit_prgm_ODTCFG (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef DDRCTL_DDR
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,ODTCFG, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, ODTCFG)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, ODTCFG)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, ODTCFG);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,ODTCFG,wr_odt_hold,p,dch);
  CONSTRAIN_MIN(reg->wr_odt_hold,0x2);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,ODTCFG,wr_odt_delay,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,ODTCFG,rd_odt_hold,p,dch);
  CONSTRAIN_MIN(reg->rd_odt_hold,0x2);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,ODTCFG,rd_odt_delay,p,dch);

  LOG_MESSAGE(hdlr, 1, ("ODTCFG[%d]= 0x%x\n",p,reg->value));
#endif //DDRCTL_DDR
}

void cinit_prgm_CRCPARTMG0 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef UMCTL2_CRC_PARITY_RETRY
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,CRCPARTMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, CRCPARTMG0)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, CRCPARTMG0)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, CRCPARTMG0);

  bool             l_rd_crc_enable = 0;
  uint8_t          l_fifo_depth_offset;
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_t*          memCtrlr = &(hdlr->memCtrlr_m);
#ifdef MEMC_DDR5
  l_rd_crc_enable = qdyn->rd_crc_enable;
#endif

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,CRCPARTMG0,t_par_alert_pw_max,p,dch);
  //This value must be greater than CRCPARTMG0.t_crc_alert_pw_max. Values of 0, 1 and 2 are illegal
  (CONSTRAIN_MIN(reg->t_par_alert_pw_max,(reg->t_crc_alert_pw_max+1)) && CONSTRAIN_MIN(reg->t_par_alert_pw_max,0x3)); 

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,CRCPARTMG0,t_crc_alert_pw_max,p,dch);
  //This value must be less than CRCPARTMG0.t_par_alert_pw_max. Values of 0, 1 and 2 are illegal
  CONSTRAIN_MIN(reg->t_crc_alert_pw_max,0x3); 

  l_fifo_depth_offset = MEMC_BURST_LENGTH == 16 ? (memCtrlr->sdram_bus_width == DWC_BUSWIDTH_FULL ? ((qdyn->wr_crc_enable == 0 && l_rd_crc_enable == 0) ? 2 : 3) : 
                                                   memCtrlr->sdram_bus_width == DWC_BUSWIDTH_HALF ? ((qdyn->wr_crc_enable == 0 && l_rd_crc_enable == 0) ? 4 : 6) : 
                                                                                                    ((qdyn->wr_crc_enable == 0 && l_rd_crc_enable == 0) ? 8 : 12) ) :
                                                  (memCtrlr->sdram_bus_width == DWC_BUSWIDTH_FULL ? ((qdyn->wr_crc_enable == 0 && l_rd_crc_enable == 0) ? 1 : 2) : 
                                                   memCtrlr->sdram_bus_width == DWC_BUSWIDTH_HALF ? ((qdyn->wr_crc_enable == 0 && l_rd_crc_enable == 0) ? 2 : 3) : 
                                                                                                    ((qdyn->wr_crc_enable == 0 && l_rd_crc_enable == 0) ? 4 : 6)  ) ;
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,CRCPARTMG0,retry_fifo_max_hold_timer_x4,p,dch);
  //Values of 0, 1 and 2 are illegal
  CONSTRAIN_MIN(reg->retry_fifo_max_hold_timer_x4,0x3); 
  CONSTRAIN_MAX(reg->retry_fifo_max_hold_timer_x4,(UMCTL2_RETRY_CMD_FIFO_DEPTH - l_fifo_depth_offset));

  LOG_MESSAGE(hdlr, 1, ("CRCPARTMG0[%d]= 0x%x\n",p,reg->value));
#endif // UMCTL2_CRC_PARITY_RETRY
}

void cinit_prgm_CRCPARTMG1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef IS_DDR5_RDIMM
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,CRCPARTMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, CRCPARTMG1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, CRCPARTMG1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, CRCPARTMG1);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  
  qdyn->t_csalt[p][dch] = pre_cfg->t_csalt[p][dch];
  
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,CRCPARTMG1,t_csalt,p,dch);

  LOG_MESSAGE(hdlr, 1, ("CRCPARTMG1[%d] = 0x%x\n",p,reg->value));
#endif //IS_DDR5_RDIMM
}

void cinit_prgm_PERFHPR1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,PERFHPR1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, PERFHPR1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, PERFHPR1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, PERFHPR1);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PERFHPR1,hpr_xact_run_length,p,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PERFHPR1,hpr_max_starve,p,dch);

  LOG_MESSAGE(hdlr, 1, ("PERFHPR1[%d]= 0x%x\n",p,reg->value));
}

void cinit_prgm_PERFWR1 (SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,PERFWR1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, PERFWR1)
  DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, PERFWR1)
  DWC_DDRCTL_CAST_REG_FREQP(p, dch, REGB_FREQ, PERFWR1);

  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PERFWR1,w_xact_run_length,p,dch);
  
  APPLY_CFG_TO_REGFIELD_P_CH(qdyn,PERFWR1,w_max_starve,p,dch);
  CONSTRAIN_MIN(reg->w_max_starve,1); //The minimum valid functional value for this register is 0x1

  LOG_MESSAGE(hdlr, 1, ("PERFWR1[%d]= 0x%x\n",p,reg->value));
}

void cinit_prgm_DFILPTMG0 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFILPTMG0, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(0, 0, REGB_FREQ, DFILPTMG0, reg, _CH)
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(0, 1, REGB_FREQ, DFILPTMG0, reg, _CH)
  if(dch==0) {
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(0, 0, REGB_FREQ, DFILPTMG0, reg, _CH)
  }
  else if(dch==1) {
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(0, 1, REGB_FREQ, DFILPTMG0, reg, _CH)
  }

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

#ifdef DDRCTL_DDR
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFILPTMG0 ,dfi_lp_wakeup_mpsm,0,dch);
#endif //DDRCTL_DDR

#ifdef DDRCTL_LPDDR
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFILPTMG0 ,dfi_lp_wakeup_dsm,0,dch);
#endif //DDRCTL_LPDDR

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFILPTMG0 ,dfi_lp_wakeup_sr,0,dch);

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFILPTMG0 ,dfi_lp_wakeup_pd,0,dch);

  LOG_MESSAGE(hdlr, 1, ("DFILPTMG0= 0x%x\n",reg->value ));
}

void cinit_prgm_DFILPTMG1 (SubsysHdlr_t *hdlr,uint32_t dch) {
  TRACE();
  
  DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ,DFILPTMG1, _CH) * reg;
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(0, 0, REGB_FREQ, DFILPTMG1, reg, _CH)
  DWC_DDRCTL_DECLARE_FREQP_DCHC_REG_PTRS(0, 1, REGB_FREQ, DFILPTMG1, reg, _CH)
  if(dch==0) {
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(0, 0, REGB_FREQ, DFILPTMG1, reg, _CH)
  }
  else if(dch==1) {
    DWC_DDRCTL_CAST_REG_FREQP_DCHC(0, 1, REGB_FREQ, DFILPTMG1, reg, _CH)
  }

  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);

  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFILPTMG1 ,dfi_lp_wakeup_data,0,dch);
  APPLY_CFG_TO_REGFIELD_P_CH(cfg,DFILPTMG1 ,dfi_tlp_resp,0,dch);

  LOG_MESSAGE(hdlr, 1, ("DFILPTMG1= 0x%x\n",reg->value ));
}
