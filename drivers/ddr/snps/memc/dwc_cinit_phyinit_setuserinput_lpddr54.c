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


#include <assert.h>
#include "dwc_cinit.h"
#include "bit_macros.h"
#include "dwc_cinit_macros.h"
    
#ifdef PHYINIT
// PHYINT functions used here but defined in PHYINT

extern int  dwc_ddrphy_phyinit_sequence(phyinit_config_t* phyctx);
extern int  dwc_ddrphy_phyinit_setUserInput(phyinit_config_t* phyctx, char *field, int value);
extern int  dwc_ddrphy_phyinit_setMb(phyinit_config_t* phyctx, int ps, char *field, int value, int Train2D);
extern int dwc_ddrphy_phyinit_log();

#endif // PHYINIT

void phyinit_setUserInput(SubsysHdlr_t *hdlr, char *field, int value) {
#ifdef PHYINIT

  LOG_MESSAGE(hdlr, 1, ("phyinit_setUserInput(LPDDR54_PHY)(%s=%d)\n",field,value));
  dwc_ddrphy_phyinit_setUserInput (hdlr->phy_config, field, value); 

#endif // PHYINIT

}

void phyinit_setMb(SubsysHdlr_t *hdlr, int ps, char *field, int value, int Train2D) {
#ifdef PHYINIT

  dwc_ddrphy_phyinit_setMb (hdlr->phy_config, ps, field, value, Train2D); 
 
#endif // PHYINIT

}

/** @brief Function to call function need when configuring PHYINIT.
 * The follow steps are taken: 
 * - calculate some local variables to map to PHYINT requirements.
 * - Setup userInputBasic
 * - Setup userInputAdvanced
 * - Setup userInputSim
*/
void dwc_cinit_phyinit_setuserinput(SubsysHdlr_t *hdlr ) {
  TRACE();
#ifdef PHYINIT
  uint8_t train_2d;
  uint32_t num_dbyte,dram_type,dimm_type, cs_present_cha, cs_present_chb,
           enabled_dq_cha, enabled_dq_chb, dfi_mode,
           pllbypass; 
  uint32_t num_active_dbyte_dfi0, num_active_dbyte_dfi1;
  uint32_t num_ch, num_dbytes_per_ch, num_rank, dmi_dbi_en,cfg_pstates;
  uint32_t mr1[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr2[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr3[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr11[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr12[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr13[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr14[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr22[hdlr->num_pstates][hdlr->num_dch];  
  // Extra DDR5 MR Registers
  uint32_t mr10[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr15[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr16[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr17[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr18[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr19[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr20[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr23[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr25[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr28[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr37[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr40[hdlr->num_pstates][hdlr->num_dch];
  // MR1
  uint8_t write_latency[hdlr->num_pstates][hdlr->num_dch], ck_mode[hdlr->num_pstates][hdlr->num_dch];
  // MR2
  uint8_t nwr[hdlr->num_pstates][hdlr->num_dch], rl_nrtp[hdlr->num_pstates][hdlr->num_dch];
  // MR3
  uint8_t pdds[hdlr->num_pstates][hdlr->num_dch], bk_bg_org[hdlr->num_pstates][hdlr->num_dch], wls[hdlr->num_pstates][hdlr->num_dch], read_dbi[hdlr->num_pstates][hdlr->num_dch], write_dbi[hdlr->num_pstates][hdlr->num_dch];   
  // MR10
  uint8_t wck_pst[hdlr->num_pstates][hdlr->num_dch], rdqs_pre[hdlr->num_pstates][hdlr->num_dch], rdqs_pst[hdlr->num_pstates][hdlr->num_dch];
  // MR11
  uint8_t dq_odt[hdlr->num_pstates][hdlr->num_dch], ca_odt[hdlr->num_pstates][hdlr->num_dch];
  // MR12
  uint8_t vref_ca[hdlr->num_pstates][hdlr->num_dch], vbs[hdlr->num_pstates][hdlr->num_dch];
  // MR13
  uint8_t thermal_offset[hdlr->num_pstates][hdlr->num_dch], vro[hdlr->num_pstates][hdlr->num_dch], dmd[hdlr->num_pstates][hdlr->num_dch], dual_vdd2[hdlr->num_pstates][hdlr->num_dch];
  // MR14
  uint8_t vref_dq_lwr[hdlr->num_pstates][hdlr->num_dch], vdlc[hdlr->num_pstates][hdlr->num_dch];
  // MR15
  uint8_t vref_dq_upr[hdlr->num_pstates][hdlr->num_dch]; 
  // MR16
  uint8_t fsp_wr[hdlr->num_pstates][hdlr->num_dch], fsp_op[hdlr->num_pstates][hdlr->num_dch], cbt[hdlr->num_pstates][hdlr->num_dch], vrcg[hdlr->num_pstates][hdlr->num_dch];
  // MR17
  uint8_t soc_odt[hdlr->num_pstates][hdlr->num_dch], odtd_ck[hdlr->num_pstates][hdlr->num_dch], odtd_ca[hdlr->num_pstates][hdlr->num_dch], odtd[hdlr->num_pstates][hdlr->num_dch];
  // MR18
  uint8_t wck_odt[hdlr->num_pstates][hdlr->num_dch], wck_fm[hdlr->num_pstates][hdlr->num_dch], wck_on[hdlr->num_pstates][hdlr->num_dch], wck_sync[hdlr->num_pstates][hdlr->num_dch], wck2ck_leveling[hdlr->num_pstates][hdlr->num_dch], ckr[hdlr->num_pstates][hdlr->num_dch];
  // MR19
  uint8_t dvfsc[hdlr->num_pstates][hdlr->num_dch], dvfsq[hdlr->num_pstates][hdlr->num_dch];
  // MR20
  uint8_t rdqs[hdlr->num_pstates][hdlr->num_dch], wck_mode[hdlr->num_pstates][hdlr->num_dch];
  // MR22
  uint8_t wr_linkecc[hdlr->num_pstates][hdlr->num_dch];   
  // MR23
  uint8_t pasr_mask[hdlr->num_pstates][hdlr->num_dch];
  // MR25
  uint8_t ck_bus_term[hdlr->num_pstates][hdlr->num_dch], ca_bus_term[hdlr->num_pstates][hdlr->num_dch], parc[hdlr->num_pstates][hdlr->num_dch];
  // MR28
  uint8_t zq_reset[hdlr->num_pstates][hdlr->num_dch], zq_stop[hdlr->num_pstates][hdlr->num_dch], zq_int[hdlr->num_pstates][hdlr->num_dch];
  // MR37
  uint8_t wck2dqi_runtime[hdlr->num_pstates][hdlr->num_dch];
  // MR40
  uint8_t wck2dqo_runtime[hdlr->num_pstates][hdlr->num_dch];  

  mctl_regs_t*  regs =&(hdlr->memCtrlr_m.regs);

  train_2d=0;
  pllbypass=0;
    
  // put the mode register settings into a format suitable for dwc_ddrphy_phyinit_setUserInput
  for (uint32_t ii=0; ii<hdlr->num_pstates; ii++) {
    for (uint32_t jj=0; jj<hdlr->num_dch; jj++) {
      if(IS_LPDDR4) {
          LOG_MESSAGE(hdlr, 1, ("dwc_cinit_phyinit_setuserinput: pstate=%d IS_LPDDR4=%d\n", ii, IS_LPDDR4));
          {
            DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR0, _CH) * reg;
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR0)
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR0)
            DWC_DDRCTL_CAST_REG_FREQP(ii, jj, REGB_FREQ, INITMR0);
            mr1[ii][jj]= reg->mr;
            mr2[ii][jj]= reg->emr;
          }
          {
            DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR1, _CH) * reg;
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR1)
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR1)
            DWC_DDRCTL_CAST_REG_FREQP(ii, jj, REGB_FREQ, INITMR1);
            mr3[ii][jj]= reg->emr2;
            mr13[ii][jj]= reg->emr3;
          }
          {
#ifdef MEMC_DDR4_OR_LPDDR4
            DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR2, _CH) * reg;
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR2)
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR2)
            DWC_DDRCTL_CAST_REG_FREQP(ii, jj, REGB_FREQ, INITMR2);
            mr11[ii][jj]= reg->mr4;
            mr12[ii][jj]= reg->mr5;
#endif
          }
          {
#ifdef MEMC_DDR4_OR_LPDDR4
            DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR3, _CH) * reg;
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR3)
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR3)
            DWC_DDRCTL_CAST_REG_FREQP(ii, jj, REGB_FREQ, INITMR3);
            mr22[ii][jj]= reg->mr22;
#endif
          }
      }      
      else if(IS_LPDDR5) {
       LOG_MESSAGE(hdlr, 1, ("dwc_cinit_phyinit_setuserinput: pstate=%d IS_LPDDR5=%d\n", ii, IS_LPDDR5));
       lpddr5_mode_registers_t* mr = &(hdlr->memCtrlr_m.lpddr5_mr[ii]);
       //MR1
       write_latency[ii][jj]= mr->mr1.write_latency;
       ck_mode[ii][jj]= mr->mr1.ck_mode;
       mr1[ii][jj] = ((ck_mode[ii][jj]&0x1)<<3) | ((write_latency[ii][jj]&0xf)<<4);
       //MR2
       nwr[ii][jj]= mr->mr2.nwr;
       rl_nrtp[ii][jj]= mr->mr2.rl_nrtp;
       mr2[ii][jj] = (rl_nrtp[ii][jj]&0xf) | ((nwr[ii][jj]&0xf)<<4);
       //MR3
       pdds[ii][jj]= mr->mr3.pdds;
       bk_bg_org[ii][jj]= mr->mr3.bk_bg_org;
       wls[ii][jj]= mr->mr3.wls;
       read_dbi[ii][jj]= mr->mr3.read_dbi;
       write_dbi[ii][jj]= mr->mr3.write_dbi;
       mr3[ii][jj] = (pdds[ii][jj]&0x7) | ((bk_bg_org[ii][jj]&0x3)<<3) | ((wls[ii][jj]&0x1)<<5) | ((read_dbi[ii][jj]&0x1)<<6) | ((write_dbi[ii][jj]&0x1)<<7);
       //MR10
       wck_pst[ii][jj]= mr->mr10.wck_pst;
       rdqs_pre[ii][jj]= mr->mr10.rdqs_pre;
       rdqs_pst[ii][jj]= mr->mr10.rdqs_pst;
       mr10[ii][jj] = ((wck_pst[ii][jj]&0x3)<<2) | ((rdqs_pre[ii][jj]&0x3)<<4) | ((rdqs_pst[ii][jj]&0x3)<<6);
       //MR11
       dq_odt[ii][jj]= mr->mr11.dq_odt;
       ca_odt[ii][jj]= mr->mr11.ca_odt;
       mr11[ii][jj] = (dq_odt[ii][jj]&0x7) | ((ca_odt[ii][jj]&0x7)<<4);
       //MR12
       vref_ca[ii][jj]= mr->mr12.vref_ca;
       vbs[ii][jj]= mr->mr12.vbs;
       mr12[ii][jj] = (vref_ca[ii][jj]&0x7f) | ((vbs[ii][jj]&0x1)<<7);
       //MR13
       thermal_offset[ii][jj]= mr->mr13.thermal_offset;
       vro[ii][jj]= mr->mr13.vro;
       dmd[ii][jj]= mr->mr13.dmd;
       dual_vdd2[ii][jj]= mr->mr13.dual_vdd2;
       mr13[ii][jj] = (thermal_offset[ii][jj]&0x3) | ((vro[ii][jj]&0x1)<<2) | ((dmd[ii][jj]&0x1)<<5) | ((dual_vdd2[ii][jj]&0x1)<<7);
       //MR14
       vref_dq_lwr[ii][jj]= mr->mr14.vref_dq;
       vdlc[ii][jj]= mr->mr14.vdlc;
       mr14[ii][jj] = (vref_dq_lwr[ii][jj]&0x7f) | ((vdlc[ii][jj]&0x1)<<7);
       //MR15
       vref_dq_upr[ii][jj]= mr->mr15.vref_dq;
       mr15[ii][jj] = (vref_dq_upr[ii][jj]&0x7f);
       //MR16
       fsp_wr[ii][jj]= mr->mr16.fsp_wr;
       fsp_op[ii][jj]= mr->mr16.fsp_op;
       cbt[ii][jj]= mr->mr16.cbt;
       vrcg[ii][jj]= mr->mr16.vrcg;
       mr16[ii][jj] = (fsp_wr[ii][jj]&0x3) | ((fsp_op[ii][jj]&0x3)<<2) | ((cbt[ii][jj]&0x3)<<4) | ((vrcg[ii][jj]&0x1)<<6);
       //MR17
       soc_odt[ii][jj]= mr->mr17.soc_odt;
       odtd_ck[ii][jj]= mr->mr17.odtd_ck;
       odtd_ca[ii][jj]= mr->mr17.odtd_ca;
       odtd[ii][jj]= mr->mr17.odtd;
       mr17[ii][jj] = (soc_odt[ii][jj]&0x7) | ((odtd_ck[ii][jj]&0x1)<<3) | ((odtd_ca[ii][jj]&0x1)<<5) | ((odtd[ii][jj]&0x3)<<6);
       //MR18
       wck_odt[ii][jj]= mr->mr18.wck_odt;
       wck_fm[ii][jj]= mr->mr18.wck_fm;
       wck_on[ii][jj]= mr->mr18.wck_on;
       wck_sync[ii][jj]= mr->mr18.wck_sync;
       wck2ck_leveling[ii][jj]= mr->mr18.wck2ck_leveling;
       ckr[ii][jj]= mr->mr18.ckr;
       mr18[ii][jj] = (wck_odt[ii][jj]&0x7) | ((wck_fm[ii][jj]&0x1)<<3) | ((wck_on[ii][jj]&0x1)<<4) | ((wck2ck_leveling[ii][jj]&0x1)<<6) | ((ckr[ii][jj]&0x1)<<7);
       //MR19
       dvfsc[ii][jj]= mr->mr19.dvfsc;
       dvfsq[ii][jj]= mr->mr19.dvfsq;
       mr19[ii][jj] = (dvfsc[ii][jj]&0x3) | ((dvfsq[ii][jj]&0x3)<<2);
       //MR20
       rdqs[ii][jj]= mr->mr20.rdqs;
       wck_mode[ii][jj]= mr->mr20.wck_mode;
       mr20[ii][jj] = (rdqs[ii][jj]&0x3) | ((wck_mode[ii][jj]&0x3)<<2);
       //MR22
       wr_linkecc[ii][jj] = mr->mr22.wecc;
       mr22[ii][jj] = ((wr_linkecc[ii][jj]&0x3)<<4);
       //MR23
       pasr_mask[ii][jj]= mr->mr23.pasr_mask;
       mr23[ii][jj] = (pasr_mask[ii][jj]&0xff);
       //MR25
       ck_bus_term[ii][jj]= mr->mr25.ck_bus_term;
       ca_bus_term[ii][jj]= mr->mr25.ca_bus_term;
       parc[ii][jj]= mr->mr25.parc;
       mr25[ii][jj] = ((ck_bus_term[ii][jj]&0x1)<<4) | ((ca_bus_term[ii][jj]&0x1)<<5) | ((parc[ii][jj]&0x1)<<6);
       //MR28
       zq_reset[ii][jj]= mr->mr28.zq_reset;
       zq_stop[ii][jj]= mr->mr28.zq_stop;
       zq_int[ii][jj]= mr->mr28.zq_int;
       mr28[ii][jj] = (zq_reset[ii][jj]&0x1) | ((zq_stop[ii][jj]&0x1)<<1) | ((zq_int[ii][jj]&0x3)<<2);
       //MR37
       wck2dqi_runtime[ii][jj]= mr->mr37.wck2dqi_runtime;
       mr37[ii][jj] = (wck2dqi_runtime[ii][jj]&0xff);
       //MR40
       wck2dqo_runtime[ii][jj]= mr->mr40.wck2dqo_runtime;
       mr40[ii][jj] = (wck2dqo_runtime[ii][jj]&0xff);
      }     
      else {
        ERROR_MESSAGE(("sdram_protocol=%0d not yet supported.",hdlr->spdData_m.sdram_protocol));          
      }
 

  } // jj -> dch
  } // ii -> pstates

  if (IS_LPDDR4) {
      dram_type=DWC_LPDDR4;
  } else if(IS_LPDDR5) {
      dram_type=DWC_LPDDR5;
  } else {
    ERROR_MESSAGE(("sdram_protocol=%0d not yet supported.",hdlr->spdData_m.sdram_protocol));
  }
  if(IS_UDIMM) {dimm_type=0;}
  if(IS_NODIMM) {dimm_type=4;} 
  // When MEMC_SIDEBAND_ECC was defined, it indicates the ECC was enabled.
  // ECC byte always use the most significant byte, so both of num_dbyte and enabled_dq should been considered as FBW 
  // For HBW/QBW, disabled_dbyte should be used to skip the un-connected dbytes. 
  // But, for SNPS_DIMM, an extra define VIRL_DIMM_ECC_MODE_0 will be used to indicate the ECC device won't be used. 
  // So, when VIRL_DIMM_ECC_MODE_0 is defined, the num_dbyte shouldn't take into account ECC width.
#ifdef MEMC_SIDEBAND_ECC
  if( (hdlr->spdData_m.module_type == DWC_LRDIMM) &&
          (regs->REGB_DDRC_CH0_ECCCFG0_reg.ecc_mode==0) )
  {
      num_dbyte = MEMC_DRAM_DATA_WIDTH/8;
  } else {
      num_dbyte = MEMC_DRAM_TOTAL_DATA_WIDTH/8;
  }
#else
  if( hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_FULL ) {
      num_dbyte = MEMC_DRAM_DATA_WIDTH/8;
  } else if (hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_HALF) {
      num_dbyte = MEMC_DRAM_DATA_WIDTH/8/2;
  } else  { // QUARTER_BUS_WIDTH
      num_dbyte = MEMC_DRAM_DATA_WIDTH/8/4;
  } 
#endif
  //#############################################################################
  //
  // Structure for basic (mandatory) user inputs
  //
  //#############################################################################
  
  
#ifdef MEMC_LPDDR4
uint8_t LPDDR4X_Enable=(hdlr->spdData_m.use_lpddr4x==1) ? 1 : 0;
if(IS_LPDDR4) {
  phyinit_setUserInput (hdlr, "Lp4xMode", LPDDR4X_Enable);
  if(LPDDR4X_Enable==1) {
    phyinit_setUserInput(hdlr, "HardMacroVer",4);
  }
}
#endif //MEMC_LPDDR4
  phyinit_setUserInput (hdlr, "DramType", dram_type);
  phyinit_setUserInput(hdlr, "NumPStates",hdlr->num_pstates);
  if (hdlr->num_pstates==1) {
    cfg_pstates = 0x1;
  } else {
    cfg_pstates = 0x3;
  }
  phyinit_setUserInput(hdlr, "CfgPStates",cfg_pstates);                 //TODO Bug_7504, Comment_17
  phyinit_setUserInput (hdlr, "NumRank_dfi0",hdlr->spdData_m.num_ranks);
  uint8_t DisablePhyUpdate= (regs->REGB_DDRC_CH0_DFIUPD0_reg.dfi_phyupd_en==1) ? 0 : 1;
  phyinit_setUserInput (hdlr, "DisablePhyUpdate",DisablePhyUpdate);
  phyinit_setUserInput (hdlr, "DisablePmuEcc",1);

#ifdef DWC_DDRPHY_DFI1_EXISTS
  phyinit_setUserInput (hdlr, "NumRank_dfi1",hdlr->spdData_m.num_ranks);
  phyinit_setUserInput(hdlr, "Dfi1Exists",1);
  if(IS_LPDDR4 && (hdlr->lpddr4_pop_support==1)) {
      if(hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_FULL) {
        dfi_mode=3;
      } else {
        dfi_mode=1;
      }
  } 
  else {
    dfi_mode=5;
  }
  if(hdlr->lpddr4_pop_support == 1) {
  LOG_MESSAGE(hdlr, 1, ("lpddr4_pop_support=%d\n",hdlr->lpddr4_pop_support));
  }
  if(IS_LPDDR4) {
  LOG_MESSAGE(hdlr, 1, ("IS_LPDDR4,dfi_mode=%d\n",dfi_mode));
  }
  if(IS_LPDDR4 && (hdlr->lpddr4_pop_support == 1)) {
  LOG_MESSAGE(hdlr, 1, ("IS_LPDDR4 && pop\n"));
  }
  if(dfi_mode==5 && dram_type != 2) {
    num_active_dbyte_dfi0= num_dbyte; 
    num_active_dbyte_dfi1=0;
  } else {
    num_active_dbyte_dfi0= num_dbyte/2; 
    num_active_dbyte_dfi1=num_dbyte-num_dbyte/2;
  }
#else
  #ifdef DWC_DDRPHY_NUM_CHANNELS_2
    phyinit_setUserInput (hdlr, "NumRank_dfi1",hdlr->spdData_m.num_ranks);
    if(hdlr->lpddr4_pop_support==1) {
      if(hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_FULL) {
        dfi_mode=3;
      } else {
        dfi_mode=1;
      }
    } 
    else {
      dfi_mode=5;
    }
      if(hdlr->lpddr4_pop_support == 1) {
      LOG_MESSAGE(hdlr, 1, ("lpddr4_pop_support=%d\n",hdlr->lpddr4_pop_support));
    }
      LOG_MESSAGE(hdlr, 1, ("dfi_mode=%d\n",dfi_mode));
      if((hdlr->lpddr4_pop_support == 1)) {
      LOG_MESSAGE(hdlr, 1, ("Is pop\n"));
    }
    if(dfi_mode==5 && dram_type != 2) {
      num_active_dbyte_dfi0= num_dbyte; 
      num_active_dbyte_dfi1=0;
    } else {
      num_active_dbyte_dfi0= num_dbyte/2; 
      num_active_dbyte_dfi1=num_dbyte-num_dbyte/2;
    }

  #else
    num_active_dbyte_dfi0= num_dbyte; 
    num_active_dbyte_dfi1=0;
    phyinit_setUserInput (hdlr, "NumRank_dfi1",0);
    dfi_mode=5;
  #endif
#endif



  phyinit_setUserInput (hdlr, "NumActiveDbyteDfi0", num_active_dbyte_dfi0);
  phyinit_setUserInput (hdlr, "NumActiveDbyteDfi1", num_active_dbyte_dfi1);



  phyinit_setUserInput (hdlr, "DimmType", dimm_type);
    
  #ifdef DWC_DDRPHY_NUM_CHANNELS_1
     num_ch = 1;
  #else
     num_ch = 2;
  #endif
  #ifdef DWC_DDRPHY_NUM_RANKS_1
     num_rank = 1;
  #else
     num_rank = 2;
  #endif
  #ifdef DWC_DDRPHY_NUM_DBYTES_PER_CHANNEL_2
     num_dbytes_per_ch = 2;
  #else
     num_dbytes_per_ch = 4;
  #endif
 #ifdef DWC_DDRPHY_DBYTE_DMI_ENABLED
     dmi_dbi_en = 1;
  #else
     dmi_dbi_en = 0;
  #endif
  
  phyinit_setUserInput (hdlr, "NumCh", num_ch);
  phyinit_setUserInput (hdlr, "NumRank", num_rank);
  phyinit_setUserInput (hdlr, "NumDbytesPerCh", num_dbytes_per_ch);
  #ifndef DWC_PHYINIT_RID_GE201908
  phyinit_setUserInput (hdlr, "DmiDbiEn", dmi_dbi_en);
  #endif
  


  // check that DramDataWidth is setup correctly
  if( IS_LPDDR4 ) {
      CONSTRAIN_NE(hdlr->spdData_m.sdram_width_bits,4);
      /*CONSTRAIN_NE(hdlr->spdData_m.sdram_width_bits,32);*/
  }
  phyinit_setUserInput (hdlr, "DramDataWidth", hdlr->spdData_m.sdram_width_bits);
#ifdef DDRCTL_LPDDR
  phyinit_setUserInput(hdlr, "DisableFspOp", 1);
#endif
  uint8_t freq_ratio;
  #ifdef MEMC_FREQ_RATIO_4
  uint8_t sel_freq_ratio;
  #ifdef UMCTL2_FREQUENCY_NUM_GT_1
  if (regs->REGB_DDRC_CH0_MSTR2_reg.target_frequency == 0) {
   sel_freq_ratio = regs->REGB_FREQ0_CH0_TMGCFG_reg.frequency_ratio;
  } else if (regs->REGB_DDRC_CH0_MSTR2_reg.target_frequency == 1) {
   sel_freq_ratio = regs->REGB_FREQ1_CH0_TMGCFG_reg.frequency_ratio;
  } else if (regs->REGB_DDRC_CH0_MSTR2_reg.target_frequency == 2) {
   sel_freq_ratio = regs->REGB_FREQ2_CH0_TMGCFG_reg.frequency_ratio;
  } else if (regs->REGB_DDRC_CH0_MSTR2_reg.target_frequency == 3) {
   sel_freq_ratio = regs->REGB_FREQ3_CH0_TMGCFG_reg.frequency_ratio;
  } else {
   ERROR_MESSAGE(("Error: Invalid value of target frequency %0d", regs->REGB_DDRC_CH0_MSTR2_reg.target_frequency));
  }
  #else // only 1 frequency
   sel_freq_ratio = regs->REGB_FREQ0_CH0_TMGCFG_reg.frequency_ratio;
  #endif // UMCTL2_FREQUENCY_NUM_GT_1
  if( sel_freq_ratio ==1 ) {
      freq_ratio=3;
  } else {
      freq_ratio=2;
  }
  #else
    freq_ratio=2;
  #endif // MEMC_FREQ_RATIO_4
  phyinit_setUserInput(hdlr, "DfiFreqRatio[0]",freq_ratio-1);
  phyinit_setUserInput(hdlr, "DfiFreqRatio[1]",freq_ratio-1);
  phyinit_setUserInput(hdlr, "DfiFreqRatio[2]",freq_ratio-1);
  phyinit_setUserInput(hdlr, "DfiFreqRatio[3]",freq_ratio-1);

  if( IS_LPDDR4 && hdlr->lpddr4_bootclk_en==1 && hdlr->lpddr4_first_boot) {
    pllbypass=1;
    ERROR_MESSAGE(("LPDDR4 boot clock is not yet supported."));
  }
  else { 
    for(int p=0;p<hdlr->num_pstates;p++) {
        uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
        uint32_t freq=CEIL(1000000,tck_ps);
        /*printf("Setting Frequency[%d]=%0d\n",p, freq);*/
        // Memclk frequency in MHz round up to next highest integer
        if(p==0) {phyinit_setUserInput(hdlr, "Frequency[0]",freq);}
        if(p==1) {phyinit_setUserInput(hdlr, "Frequency[1]",freq);}
        if(p==2) {phyinit_setUserInput(hdlr, "Frequency[2]",freq);}
        if(p==3) {phyinit_setUserInput(hdlr, "Frequency[3]",freq);}    
    }
  }
   if(IS_LPDDR4) {
    phyinit_setUserInput(hdlr, "PllBypass[0]",pllbypass);	
    phyinit_setUserInput(hdlr, "PllBypass[1]",pllbypass); 
#ifdef UMCTL2_FREQUENCY_NUM_GT_2
    phyinit_setUserInput(hdlr, "PllBypass[2]",pllbypass);
#endif
#ifdef UMCTL2_FREQUENCY_NUM_GT_3
    phyinit_setUserInput(hdlr, "PllBypass[3]",pllbypass);
#endif    
  }

 
  if(hdlr->spdData_m.num_ranks==4) { cs_present_cha=0xf;}
  else if(hdlr->spdData_m.num_ranks==2) {cs_present_cha=0x3;}
  else {cs_present_cha=0x1; }
  cs_present_chb = 0;

  if(hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_FULL && dfi_mode==3) {
     cs_present_chb = cs_present_cha;
  } 


//#############################################################################
//
// Structure for advanced (optional) user inputs
// - if user does not enter a value for these parameters, a PHY recommended or
//   default value will be used
//
//############################################################################# 
#ifdef MEMC_LPDDR4
if(IS_LPDDR4) {
  lpddr4_mode_registers_t* mr = &(hdlr->memCtrlr_m.lpddr4_mr[0]);
  
  phyinit_setUserInput(hdlr, "WDQSExt", 0); // TODO add some variable to control this
   
}
#endif //MEMC_LPDDR4

//#############################################################################
//
// Structure for user input simulation options
//
//#############################################################################
#ifdef MEMC_LPDDR4
if(IS_LPDDR4) {
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[0]);
  phyinit_setUserInput(hdlr, "tDQS2DQ",timing->lpddr4_tdqs2dq); 
  phyinit_setUserInput(hdlr, "tDQSCK",timing->lpddr4_tdqsck);  
}
if(IS_LPDDR5) {
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[0]);
  // set tWCK2DQI & tWCK2DQO to SVT VIP values
  phyinit_setUserInput(hdlr, "tWCK2DQI",timing->lpddr5_wckdqi_ps);
  phyinit_setUserInput(hdlr, "tWCK2DQO",timing->lpddr5_wckdqo_ps); 
}
#endif //MEMC_LPDDR4


//#############################################################################
//
// Structure for RuntimeConfig options
//
//#############################################################################
if(hdlr->phy_training==0) {
  phyinit_setUserInput(hdlr, "initCtrl",0xf);
} else {
  phyinit_setUserInput(hdlr, "initCtrl",0x21);
}

//
//
// Setup the message block.
// MsgMisc[0]: MTESTEnable
// MsgMisc[1]: SimulationOnlyReset
// MsgMisc[2]: SimulationOnlyTraining
// MsgMisc[3]: UseDdr4PerDeviceVrefDq (DDR4 UDIMM/RDIMM only)
// MsgMisc[4]: Suppress streaming messages
// MsgMisc[5]: PerByteMaxRdLat
// MsgMisc[6]: PartialRank 
// MsgMisc[7]: RFU
//
  uint32_t msgmisc;
  msgmisc = 0;
  if(hdlr->use_jedec_init==0) { msgmisc |= 1 << 1; }
  msgmisc |= 1 << 2;
  if(IS_DDR4 && !(IS_LRDIMM) ) {
     msgmisc |= 1 << 3;      
  }
#ifdef UMCTL2_SHARED_AC
  msgmisc |= 1 << 6;
#endif
  enabled_dq_cha = num_active_dbyte_dfi0*8;
  enabled_dq_chb = num_active_dbyte_dfi1*8;    
  for(int i=0;i<hdlr->num_pstates;i++) {
    for(int j=0;j<1;j++) {  // Hardcode 1 as PHY supports only 1 channel
      phyinit_setMb (hdlr, i, "MsgMisc", msgmisc, train_2d);
      phyinit_setMb (hdlr, i, "HdtCtrl",hdlr->HdtCtrl , train_2d); // Stage completion
      phyinit_setMb (hdlr, i, "DFIMRLMargin", 1, train_2d);
      if(IS_LPDDR4) {
        phyinit_setMb (hdlr, i, "EnabledDQsChA", enabled_dq_cha, train_2d);
        phyinit_setMb (hdlr, i, "CsPresentChA", cs_present_cha, train_2d);
        phyinit_setMb (hdlr, i, "MR1_A0", (mr1[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR2_A0", (mr2[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR3_A0", (mr3[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR11_A0", (mr11[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR12_A0", (mr12[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR13_A0", (mr13[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR14_A0", (mr14[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR22_A0", (mr22[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR1_A1", (mr1[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR2_A1", (mr2[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR3_A1", (mr3[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR11_A1", (mr11[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR12_A1", (mr12[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR13_A1", (mr13[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR14_A1", (mr14[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR22_A1", (mr22[i][j] & 0xff), train_2d);

        phyinit_setMb (hdlr, i, "EnabledDQsChB", enabled_dq_chb, train_2d);
        phyinit_setMb (hdlr, i, "CsPresentChB", cs_present_chb, train_2d);
        phyinit_setMb (hdlr, i, "MR1_B0", (mr1[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR2_B0", (mr2[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR3_B0", (mr3[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR11_B0", (mr11[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR12_B0", (mr12[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR13_B0", (mr13[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR14_B0", (mr14[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR22_B0", (mr22[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR1_B1", (mr1[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR2_B1", (mr2[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR3_B1", (mr3[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR11_B1", (mr11[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR12_B1", (mr12[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR13_B1", (mr13[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR14_B1", (mr14[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR22_B1", (mr22[i][j] & 0xff), train_2d);
      } else if(IS_LPDDR5) {
	phyinit_setMb (hdlr, i, "EnabledDQsChA", enabled_dq_cha, train_2d);
        phyinit_setMb (hdlr, i, "CsPresentChA", cs_present_cha, train_2d);
        phyinit_setMb (hdlr, i, "MR1_A0", (mr1[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR2_A0", (mr2[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR3_A0", (mr3[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR10_A0", (mr10[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR11_A0", (mr11[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR12_A0", (mr12[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR13_A0", (mr13[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR14_A0", (mr14[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR15_A0", (mr15[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR16_A0", (mr16[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR17_A0", (mr17[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR18_A0", (mr18[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR19_A0", (mr19[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR20_A0", (mr20[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR22_A0", (mr22[i][j] & 0xff), train_2d);
        //phyinit_setMb (hdlr, i, "MR23_A0", (mr23[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR25_A0", (mr25[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR28_A0", (mr28[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR37_A0", (mr37[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR40_A0", (mr40[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR1_A1", (mr1[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR2_A1", (mr2[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR3_A1", (mr3[i][j] & 0xff), train_2d);
        
        
	phyinit_setMb (hdlr, i, "MR10_A1", (mr10[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR11_A1", (mr11[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR12_A1", (mr12[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR13_A1", (mr13[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR14_A1", (mr14[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR15_A1", (mr15[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR16_A1", (mr16[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR17_A1", (mr17[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR18_A1", (mr18[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR19_A1", (mr19[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR20_A1", (mr20[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR22_A1", (mr22[i][j] & 0xff), train_2d);
        //phyinit_setMb (hdlr, i, "MR23_A1", (mr23[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR25_A1", (mr25[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR28_A1", (mr28[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR37_A1", (mr37[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR40_A1", (mr40[i][j] & 0xff), train_2d);
	
        phyinit_setMb (hdlr, i, "EnabledDQsChB", enabled_dq_chb, train_2d);
        phyinit_setMb (hdlr, i, "CsPresentChB", cs_present_chb, train_2d);
	phyinit_setMb (hdlr, i, "MR1_B0", (mr1[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR2_B0", (mr2[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR3_B0", (mr3[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR10_B0", (mr10[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR11_B0", (mr11[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR12_B0", (mr12[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR13_B0", (mr13[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR14_B0", (mr14[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR15_B0", (mr15[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR16_B0", (mr16[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR17_B0", (mr17[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR18_B0", (mr18[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR19_B0", (mr19[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR20_B0", (mr20[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR22_B0", (mr22[i][j] & 0xff), train_2d);
        //phyinit_setMb (hdlr, i, "MR23_B0", (mr23[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR25_B0", (mr25[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR28_B0", (mr28[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR37_B0", (mr37[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR40_B0", (mr40[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR1_B1", (mr1[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR2_B1", (mr2[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR3_B1", (mr3[i][j] & 0xff), train_2d);
        
        
	phyinit_setMb (hdlr, i, "MR10_B1", (mr10[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR11_B1", (mr11[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR12_B1", (mr12[i][j] & 0xff), train_2d);
        phyinit_setMb (hdlr, i, "MR13_B1", (mr13[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR14_B1", (mr14[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR15_B1", (mr15[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR16_B1", (mr16[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR17_B1", (mr17[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR18_B1", (mr18[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR19_B1", (mr19[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR20_B1", (mr20[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR22_B1", (mr22[i][j] & 0xff), train_2d);
        //phyinit_setMb (hdlr, i, "MR23_B1", (mr23[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR25_B1", (mr25[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR28_B1", (mr28[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR37_B1", (mr37[i][j] & 0xff), train_2d);
	phyinit_setMb (hdlr, i, "MR40_B1", (mr40[i][j] & 0xff), train_2d);
      }
       //LPDDR3 and LPDDR4 1D
       // SequenceCtrl[0]    = 1     Run DevInit - Device/phy initialization. Should always be set.
       // SequenceCtrl[1]    = 1     Run WrLvl - Write leveling
       // SequenceCtrl[2]    = 1     Run RxEn - Read gate training
       // SequenceCtrl[3]    = 1     Run RdDQS1D - 1d read dqs training
       //
       // SequenceCtrl[4]    = 1     Run WrDQ1D - 1d write dq training
       // SequenceCtrl[5]    = 0     RFU, must be zero
       // SequenceCtrl[6]    = 0     RFU, must be zero
       // SequenceCtrl[7]    = 0     RFU, must be zero
       //
       // SequenceCtrl[8]    = 1     Run RdDeskew - Per lane read dq deskew training
       // SequenceCtrl[9]    = 1     Run MxRdLat - Max read latency training
       // SequenceCtrl[10]   = 0     RFU, must be zero
       // SequenceCtrl[11]   = 0     RFU, must be zero
       //
       // SequenceCtrl[12]   = 1     Run LPCA - CA Training
       // SequenceCtrl[13]   = 0     RFU, must be zero
       // SequenceCtrl[14]   = 0     RFU, must be zero
       // SequenceCtrl[15]   = 0     RFU, must be zero
        //  if(hdlr->use_pub_training) {
        //      phyinit_setMb (hdlr, i, "SequenceCtrl", 0x131f, 0);
      //    } else {
            phyinit_setMb (hdlr, i, "SequenceCtrl", 0x0001, 0);   //Run DevInit only
      //    }       
    } // for num_dch
  } // for num_pstates
  // For LPDDR4 byte mode, X8Mode must be set to 1 in all PStates to avoid the error message
  // from dwc_ddrphy_phyinit_calcMb() function.
  if(IS_LPDDR4 || IS_LPDDR5) {
      if(hdlr->spdData_m.sdram_width_bits==8) {
          for(int ii=0;ii<4;ii++) {
            phyinit_setMb (hdlr, ii, "X8Mode", 0xf, train_2d);
          }
      }
  }

#endif // PHYINIT

}


