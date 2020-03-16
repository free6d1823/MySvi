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
#ifdef DWC_PHYINIT_RID_GE201904
extern int dwc_ddrphy_phyinit_setMb (phyinit_config_t* phyctx, int ps, char *field, int value);
extern int dwc_ddrphy_phyinit_setUserInput (phyinit_config_t* phyctx, char *field, int value);
extern int dwc_ddrphy_phyinit_log();
#else
extern int dwc_ddrphy_phyinit_setMb (int ps, char *field, int value, int Train2D);
extern int dwc_ddrphy_phyinit_setUserInput (char *field, int value);
extern int dwc_ddrphy_phyinit_log();
#endif
#endif // PHYINIT

void phyinit_setUserInput(SubsysHdlr_t *hdlr, char *field, int value) {
#ifdef PHYINIT

  LOG_MESSAGE(hdlr, 1, ("phyinit_setUserInput(OTHER)(%s=%d)\n",field,value));
#ifdef DWC_PHYINIT_RID_GE201904
  dwc_ddrphy_phyinit_setUserInput(hdlr->phy_config, field, value);
#else
  dwc_ddrphy_phyinit_setUserInput(field, value);
#endif

#endif // PHYINIT

}

void phyinit_setMb(SubsysHdlr_t *hdlr, int ps, char *field, int value, int Train2D) {
#ifdef PHYINIT
#ifdef DWC_PHYINIT_RID_GE201904
  dwc_ddrphy_phyinit_setMb(hdlr->phy_config, ps, field, value);
#else
  dwc_ddrphy_phyinit_setMb(ps, field, value, Train2D);
#endif

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
  uint8_t is_geardown, train_2d;
  uint8_t is_2t_timing;
  uint8_t disabled_dbyte;
  uint8_t is_2n_mode;
  uint32_t num_dbyte,dram_type,dimm_type, cs_present_cha, dfi_mode; 
  uint32_t num_active_dbyte_dfi0, num_active_dbyte_dfi1;
  uint32_t mr0[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr1[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr2[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr3[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr4[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr5[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr6[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr8[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr13[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr34[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr35[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr37[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr38[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr39[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr50[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr0_cl[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr2_cwl[hdlr->num_pstates][hdlr->num_dch];
  uint8_t bl[hdlr->num_pstates][hdlr->num_dch], cl[hdlr->num_pstates][hdlr->num_dch],rd_preamble_enable[hdlr->num_pstates][hdlr->num_dch],wr_leveling[hdlr->num_pstates][hdlr->num_dch],ddr5_2n_mode[hdlr->num_pstates][hdlr->num_dch],cs_assertion_duration[hdlr->num_pstates][hdlr->num_dch], mpsm[hdlr->num_pstates][hdlr->num_dch],dev15_mpsm[hdlr->num_pstates][hdlr->num_dch],internal_wr_timing[hdlr->num_pstates][hdlr->num_dch], refresh_trfc_mode[hdlr->num_pstates][hdlr->num_dch], refresh_rate[hdlr->num_pstates][hdlr->num_dch], data_output_disable[hdlr->num_pstates][hdlr->num_dch], pull_up_output_drv_impedance[hdlr->num_pstates][hdlr->num_dch], tdqs_enable[hdlr->num_pstates][hdlr->num_dch], dm_enable[hdlr->num_pstates][hdlr->num_dch], pull_down_output_drv_impedance[hdlr->num_pstates][hdlr->num_dch], trtp[hdlr->num_pstates][hdlr->num_dch], wr_recovery[hdlr->num_pstates][hdlr->num_dch], rd_preamble[hdlr->num_pstates][hdlr->num_dch], wr_preamble[hdlr->num_pstates][hdlr->num_dch], rd_postamble[hdlr->num_pstates][hdlr->num_dch], wr_postamble[hdlr->num_pstates][hdlr->num_dch], tccd_l[hdlr->num_pstates][hdlr->num_dch],rtt_park[hdlr->num_pstates][hdlr->num_dch],rtt_wr[hdlr->num_pstates][hdlr->num_dch], rtt_nom_wr[hdlr->num_pstates][hdlr->num_dch], rtt_nom_rd[hdlr->num_pstates][hdlr->num_dch], odtlon_wr_offset[hdlr->num_pstates][hdlr->num_dch], odtloff_wr_offset[hdlr->num_pstates][hdlr->num_dch], odtlon_rd_nt_offset[hdlr->num_pstates][hdlr->num_dch], odtloff_rd_nt_offset[hdlr->num_pstates][hdlr->num_dch], odtlon_wr_nt_offset[hdlr->num_pstates][hdlr->num_dch], odtloff_wr_nt_offset[hdlr->num_pstates][hdlr->num_dch], rd_crc_enable[hdlr->num_pstates][hdlr->num_dch], wr_crc_enable_lower_nibble[hdlr->num_pstates][hdlr->num_dch], wr_crc_enable_upper_nibble[hdlr->num_pstates][hdlr->num_dch], wr_crc_error_status[hdlr->num_pstates][hdlr->num_dch], wr_crc_auto_disable_enable[hdlr->num_pstates][hdlr->num_dch], wr_crc_auto_disable_status[hdlr->num_pstates][hdlr->num_dch];
  uint32_t cs_presentD0;
  uint32_t cs_presentD1;  
  // RDIMM only
  uint32_t RC00_data[hdlr->num_pstates][hdlr->num_dch];
  uint32_t RC01_data[hdlr->num_pstates][hdlr->num_dch];
  uint32_t RC08_data[hdlr->num_pstates][hdlr->num_dch];
  uint32_t RC0A_data[hdlr->num_pstates][hdlr->num_dch];
  uint32_t RC0D_data[hdlr->num_pstates][hdlr->num_dch];
  uint32_t RC0E_data[hdlr->num_pstates][hdlr->num_dch];
  uint32_t RC0F_data[hdlr->num_pstates][hdlr->num_dch];
  uint32_t RC3x_data[hdlr->num_pstates][hdlr->num_dch];

  // LRDIMM only
  uint32_t BC0A_data[hdlr->num_pstates][hdlr->num_dch];
  uint32_t F0BC6x_data[hdlr->num_pstates][hdlr->num_dch];  
  mctl_regs_t*  regs =&(hdlr->memCtrlr_m.regs);

  is_geardown=0;
  is_2t_timing=0;
  is_2n_mode=0;
  train_2d=0;
  cs_presentD0=0;
  cs_presentD1=0;
  disabled_dbyte = 0;
    
  //  dwc_ddrphy_phyinit_setDefault(0);

  // Overwrite for DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_FREQ_RATIO_4
  LOG_MESSAGE(hdlr, 1, ("dwc_cinit_phyinit_setuserinput: MEMC_DDR5 MEMC_FREQ_RATIO_4 IS_DDR5=%d\n", IS_DDR5));
  if(IS_DDR5) {
    phyinit_setUserInput (hdlr, "DramType", DDR5);
    phyinit_setUserInput (hdlr, "NumPStates", hdlr->num_pstates);
    phyinit_setUserInput (hdlr, "Dfi1Exists", 1);

#ifdef DWC_PHYINIT_RID_GE201904
    phyinit_setUserInput (hdlr, "skip_train", 1);
#endif

#ifdef MEMC_SIDEBAND_ECC
    if(IS_RDIMM){
      num_dbyte = (DDRCTL_DFI_DATA_WIDTH/8/2);
    } else {
      num_dbyte = MEMC_DRAM_TOTAL_DATA_WIDTH/8;
    }
#else
    if(IS_RDIMM){
      if( hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_FULL ) {
        if(IS_DUAL_CHAN){
          num_dbyte = (MEMC_DRAM_DATA_WIDTH*2)/8;
        }
        else{
          num_dbyte = MEMC_DRAM_DATA_WIDTH/8;
        }
      } else if (hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_HALF) {
          if(IS_DUAL_CHAN){
            num_dbyte = MEMC_DRAM_DATA_WIDTH/8;
          }
          else{
            num_dbyte = MEMC_DRAM_DATA_WIDTH/8/2;
          }
      } else{ 
        if(IS_DUAL_CHAN){
          num_dbyte = MEMC_DRAM_DATA_WIDTH*2/8/4;
        }
        else {
          num_dbyte = MEMC_DRAM_DATA_WIDTH/8/4;
        }
      } 
    } else {
      if( hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_FULL ) {
        num_dbyte = (MEMC_DRAM_DATA_WIDTH/8)*2;
      } else if (hdlr->memCtrlr_m.sdram_bus_width==DWC_BUSWIDTH_HALF) {
        num_dbyte = (MEMC_DRAM_DATA_WIDTH/8/2)*2;
      } else {
        num_dbyte = (MEMC_DRAM_DATA_WIDTH/8/4)*2;
      }
    }
#endif // MEMC_SIDEBAND_ECC
    if(IS_RDIMM && IS_DUAL_CHAN){
      phyinit_setUserInput (hdlr, "NumActiveDbyteDfi0", (num_dbyte/2));
      phyinit_setUserInput (hdlr, "NumActiveDbyteDfi1", (num_dbyte/2));
      phyinit_setUserInput (hdlr, "NumRank_dfi0",hdlr->spdData_m.num_ranks);
      phyinit_setUserInput (hdlr, "NumRank_dfi1",hdlr->spdData_m.num_ranks);
    }else{
      phyinit_setUserInput (hdlr, "NumRank_dfi0", hdlr->spdData_m.num_ranks);
      phyinit_setUserInput (hdlr, "NumRank_dfi1", 0);
      #ifdef MEMC_SIDEBAND_ECC
      if (num_dbyte <= 5) {
        phyinit_setUserInput (hdlr, "NumActiveDbyteDfi0", num_dbyte);
        phyinit_setUserInput (hdlr, "NumActiveDbyteDfi1", 0);
      } else {
        phyinit_setUserInput (hdlr, "NumActiveDbyteDfi0", 5);
        phyinit_setUserInput (hdlr, "NumActiveDbyteDfi1", num_dbyte - 5);
      }
      #else
      if (num_dbyte <= 4) {
        phyinit_setUserInput (hdlr, "NumActiveDbyteDfi0", num_dbyte);
        phyinit_setUserInput (hdlr, "NumActiveDbyteDfi1", 0);
      } else {
        phyinit_setUserInput (hdlr, "NumActiveDbyteDfi0", 4);
        phyinit_setUserInput (hdlr, "NumActiveDbyteDfi1", num_dbyte - 4);
      }
      #endif
    }

      phyinit_setUserInput (hdlr, "NumAnib", hdlr->num_anibs);
      phyinit_setUserInput (hdlr, "NumDbyte", num_dbyte);

    #ifdef MEMC_SIDEBAND_ECC
    if(IS_UDIMM || IS_NODIMM){
      if(hdlr->memCtrlr_m.sdram_bus_width == DWC_BUSWIDTH_HALF) {
      #if defined(MEMC_DRAM_DATA_WIDTH_GT_63)
        disabled_dbyte = 0xf0;
      #elif defined(MEMC_DRAM_DATA_WIDTH_GT_31)
        disabled_dbyte = 0xec;
      #else
        disabled_dbyte = 0xfa;
      #endif
      }
      else if(hdlr->memCtrlr_m.sdram_bus_width == DWC_BUSWIDTH_QUARTER){
      #ifdef MEMC_DRAM_DATA_WIDTH_GT_63
        disabled_dbyte = 0xfc;
      #else
        disabled_dbyte = 0xee;
      #endif
      }
    }
    #endif
    if(IS_UDIMM ) {dimm_type=0;}
    if(IS_RDIMM ) {dimm_type=2;}
    if(IS_LRDIMM) {dimm_type=3;}
    if(IS_NODIMM) {dimm_type=4;} 
    phyinit_setUserInput (hdlr, "DimmType", dimm_type);

    phyinit_setUserInput (hdlr, "DramDataWidth", hdlr->spdData_m.sdram_width_bits);

    uint8_t freq_ratio=4;
    phyinit_setUserInput (hdlr, "DfiFreqRatio[0]",freq_ratio-1);
    phyinit_setUserInput (hdlr, "DfiFreqRatio[1]",freq_ratio-1);
    phyinit_setUserInput (hdlr, "DfiFreqRatio[2]",freq_ratio-1);
    phyinit_setUserInput (hdlr, "DfiFreqRatio[3]",freq_ratio-1);

    for(int p=0;p<hdlr->num_pstates;p++) {
        uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
        uint32_t freq=CEIL(1000000,tck_ps);
        if(p==0) {phyinit_setUserInput(hdlr, "Frequency[0]",freq);}
        if(p==1) {phyinit_setUserInput(hdlr, "Frequency[1]",freq);}
        if(p==2) {phyinit_setUserInput(hdlr, "Frequency[2]",freq);}
        if(p==3) {phyinit_setUserInput(hdlr, "Frequency[3]",freq);}
    }
    phyinit_setUserInput(hdlr, "PllBypass[0]", regs->REGB_DDRC_CH0_MSTR0_reg.dll_off_mode);
    phyinit_setUserInput(hdlr, "PllBypass[1]", 0);  // TODO
    phyinit_setUserInput(hdlr, "PllBypass[2]", 0);  // TODO
    phyinit_setUserInput(hdlr, "PllBypass[3]", 0);  // TODO
 
    //TODO: add for other frequencies
    phyinit_setUserInput(hdlr, "D5ReadCRCEnable", regs->REGB_DDRC_CH0_CRCPARCTL1_reg.rd_crc_enable);

  #ifndef DWC_PHYINIT_RID_GE201904
    phyinit_setUserInput(hdlr, "D5RxDqsPreambleCtrl[0]", 1); 
    phyinit_setUserInput(hdlr, "D5RxDqsPreambleCtrl[1]", 1); 
    phyinit_setUserInput(hdlr, "D5RxDqsPreambleCtrl[2]", 1); 
    phyinit_setUserInput(hdlr, "D5RxDqsPreambleCtrl[3]", 1); 
  #endif
  phyinit_setUserInput (hdlr, "DisablePmuEcc",1);//disabled the SRAM ECC feature temporarily
    if(IS_RDIMM || IS_LRDIMM) {
      if( hdlr->memCtrlr_m.ddr5_mr[0].mr2.ddr5_2n_mode ) { // 1N mode
        is_2n_mode=0;
      }
      else { // 2N mode
        is_2n_mode=1;
      }
      phyinit_setUserInput(hdlr, "D5RdimmSDRmode", is_2n_mode);
      
      for(int p=0;p<hdlr->num_pstates;p++) {
        int ddr5_rcd_tstaoff_ps=hdlr->timingParams_m[0].ddr5_rcd_tstaoff_ps + 2; // Adjust for TxDly
        if(p==0) {phyinit_setUserInput(hdlr, "tSTAOFF[0]",ddr5_rcd_tstaoff_ps);}
        if(p==1) {phyinit_setUserInput(hdlr, "tSTAOFF[1]",ddr5_rcd_tstaoff_ps);}
        if(p==2) {phyinit_setUserInput(hdlr, "tSTAOFF[2]",ddr5_rcd_tstaoff_ps);}
        if(p==3) {phyinit_setUserInput(hdlr, "tSTAOFF[3]",ddr5_rcd_tstaoff_ps);}
      }
      for(int p=0;p<hdlr->num_pstates;p++) {
        int ddr5_rcd_tpdm_ps=hdlr->timingParams_m[0].ddr5_rcd_tpdm_ps;
        if(p==0) {phyinit_setUserInput(hdlr, "tPDM[0]",ddr5_rcd_tpdm_ps);}
        if(p==1) {phyinit_setUserInput(hdlr, "tPDM[1]",ddr5_rcd_tpdm_ps);}
        if(p==2) {phyinit_setUserInput(hdlr, "tPDM[2]",ddr5_rcd_tpdm_ps);}
        if(p==3) {phyinit_setUserInput(hdlr, "tPDM[3]",ddr5_rcd_tpdm_ps);}
      }
      for(int p=0;p<hdlr->num_pstates;p++) {
        phyinit_setMb (hdlr, p, "MR8_A0", 9, 0); 
      }
      
      /// Work around for PHY get wrong read data in some case
      uint32_t tck_ps=hdlr->spdData_m.tck_ps[0];
      int tDQSCK_ps; // Adjust for RxDly
      if(tck_ps >= 625 ){
        tDQSCK_ps = 2;
      }
      else {
        tDQSCK_ps = 1;
      }
      phyinit_setUserInput(hdlr, "tDQSCK", tDQSCK_ps);
    }
  }
#endif // MEMC_FREQ_RATIO_4
#endif // MEMC_DDR5

  

#ifdef MEMC_CMD_RTN2IDLE 
  if( regs->REGB_DDRC_CH0_MSTR0_reg.en_2t_timing_mode==1 ) {
      is_2t_timing=1;
  }

#ifdef MEMC_DDR4
#ifdef MEMC_FREQ_RATIO_2
  if( regs->REGB_DDRC_CH0_MSTR3_reg.geardown_mode ==1 ) {
      is_geardown=1;
      is_2t_timing=1;
  }
#endif // MEMC_FREQ_RATIO_2
#endif // MEMC_DDR4
#endif // MEMC_CMD_RTN2IDLE

  // put the mode register settings into a format suitable for dwc_ddrphy_phyinit_setUserInput
  for (uint32_t ii=0; ii<hdlr->num_pstates; ii++) {
    for (uint32_t jj=0; jj<hdlr->num_dch; jj++) {
       if (IS_DDR4) {
          LOG_MESSAGE(hdlr, 1, ("dwc_cinit_phyinit_setuserinput: pstate=%d IS_DDR4=%d\n", ii, IS_DDR4));
          {
            DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR0, _CH) * reg;
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR0)
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR0)
            DWC_DDRCTL_CAST_REG_FREQP(ii, jj, REGB_FREQ, INITMR0);
            mr0[ii][jj]= reg->mr;
            mr1[ii][jj]= reg->emr;
          }
          {
            DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR1, _CH) * reg;
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR1)
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR1)
            DWC_DDRCTL_CAST_REG_FREQP(ii, jj, REGB_FREQ, INITMR1);
            mr2[ii][jj]= reg->emr2;
            mr3[ii][jj]= reg->emr3;
          }
          {
#ifdef MEMC_DDR4_OR_LPDDR4
            DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR2, _CH) * reg;
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR2)
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR2)
            DWC_DDRCTL_CAST_REG_FREQP(ii, jj, REGB_FREQ, INITMR2);
            mr4[ii][jj]= reg->mr4;
            mr5[ii][jj]= reg->mr5;
#endif
            // Geardown entry happens after SRX and it should be done with CA parity off
            // So if geardown is enabled, CA parity must be disabled before SRE
            if (is_geardown == 1) {
                SETREGBITFILD(mr5[ii][jj],0,0x7,0); //C/A Parity Latency Mode
            }            
          }
          {
#ifdef MEMC_DDR4_OR_LPDDR4
            DWC_DDRCTL_FREQ_REG_STRUCT(0,0,REGB_FREQ, INITMR3, _CH) * reg;
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(0, REGB_FREQ, INITMR3)
            DWC_DDRCTL_DECLARE_FREQP_REG_PTRS(1, REGB_FREQ, INITMR3)
            DWC_DDRCTL_CAST_REG_FREQP(ii, jj, REGB_FREQ, INITMR3);
            mr6[ii][jj]= reg->mr6;
#endif
          }
      }
      else if(IS_DDR5) {
          LOG_MESSAGE(hdlr, 1, ("dwc_cinit_phyinit_setuserinput: pstate=%d IS_DDR5=%d\n", ii, IS_DDR5));
          ddr5_mode_registers_t* mr = &(hdlr->memCtrlr_m.ddr5_mr[ii]);
          bl[ii][jj]= mr->mr0.burst_length;
          cl[ii][jj]= mr->mr0.cl;
          mr0[ii][jj] = (bl[ii][jj]&0x3) | ((cl[ii][jj]&0x1f)<<2);
          rd_preamble_enable[ii][jj]= mr->mr2.rd_preamble_enable;
          wr_leveling[ii][jj]= mr->mr2.wr_leveling;
          ddr5_2n_mode[ii][jj]=mr->mr2.ddr5_2n_mode;
          cs_assertion_duration[ii][jj]= mr->mr2.cs_assertion_duration;
          mpsm[ii][jj]= mr->mr2.mpsm;
          dev15_mpsm[ii][jj] = mr->mr2.dev15_mpsm;
          internal_wr_timing[ii][jj] = mr->mr2.internal_wr_timing;
          //mr3[ii][jj]= ((dll_reset[ii][jj]&0x1)<<7) | ((dll_enable[ii][jj]&0x1)<<6) | ((cs_assertion_duration[ii][jj]&0x1)<<2) | ((mpsm[ii][jj]&0x1)<<1);
          mr2[ii][jj]= ((internal_wr_timing[ii][jj]&0x1)<<7) | ((dev15_mpsm[ii][jj]&0x1)<<5) | ((cs_assertion_duration[ii][jj]&0x1)<<4) | ((mpsm[ii][jj]&0x1)<<3) | ((ddr5_2n_mode[ii][jj]&0x01)<<2) | ((wr_leveling[ii][jj]&0x1)<<1) | ((rd_preamble_enable[ii][jj]&0x1));
          refresh_trfc_mode[ii][jj]= mr->mr4.refresh_trfc_mode;
          refresh_rate[ii][jj]= mr->mr4.refresh_rate;
          mr4[ii][jj]= ((refresh_trfc_mode[ii][jj]&0x1)<<4) | (refresh_rate[ii][jj]&0x7);
          data_output_disable[ii][jj]= mr-> mr5.data_output_disable;
          pull_up_output_drv_impedance[ii][jj]= mr->mr5.pull_up_output_drv_impedance;
          tdqs_enable[ii][jj]= mr-> mr5.tdqs_enable;
          dm_enable[ii][jj]= mr-> mr5.dm_enable;
          pull_down_output_drv_impedance[ii][jj]= mr-> mr5.pull_down_output_drv_impedance;
          mr5[ii][jj]= (data_output_disable[ii][jj]&0x1) | ((pull_up_output_drv_impedance[ii][jj]&0x3)<<1) | ((tdqs_enable[ii][jj]&0x1)<<4) | ((dm_enable[ii][jj]&0x1)<<5) | ((pull_down_output_drv_impedance[ii][jj]&0x3)<<6);
          trtp[ii][jj]= mr-> mr6.trtp;
          wr_recovery[ii][jj]= mr-> mr6.wr_recovery;
          mr6[ii][jj]= ((trtp[ii][jj]&0xf)<<4) | (wr_recovery[ii][jj]&0xf);
          rd_preamble[ii][jj]=mr->mr8.rd_preamble;
          wr_preamble[ii][jj]=mr->mr8.wr_preamble;
          rd_postamble[ii][jj]=mr->mr8.rd_postamble;
          wr_postamble[ii][jj]=mr->mr8.wr_postamble;
          mr8[ii][jj]= (rd_preamble[ii][jj]&0x7) | ((wr_preamble[ii][jj]&0x3)<<3) | ((rd_postamble[ii][jj]&0x1)<<6) | ((wr_postamble[ii][jj]&0x1)<<7);
          tccd_l[ii][jj]=mr->mr13.tccd_l;
          mr13[ii][jj]= tccd_l[ii][jj]&0xf;
          rtt_park[ii][jj]=mr->mr34.rtt_park;
          rtt_wr[ii][jj]= mr->mr34.rtt_wr;
          mr34[ii][jj]= (rtt_wr[ii][jj]&0x7)<<3 | (rtt_park[ii][jj]&0x7);
          rtt_nom_wr[ii][jj]=mr->mr35.rtt_nom_wr;
          rtt_nom_rd[ii][jj]=mr->mr35.rtt_nom_rd;
          mr35[ii][jj]= (rtt_nom_wr[ii][jj]&0x7) | ((rtt_nom_rd[ii][jj]&0x7)<<3);
          odtlon_wr_offset[ii][jj]=mr->mr37.odtlon_wr_offset;
          odtloff_wr_offset[ii][jj]=mr->mr37.odtloff_wr_offset;
          mr37[ii][jj]= (odtlon_wr_offset[ii][jj]&0x7) | ((odtloff_wr_offset[ii][jj]&0x7)<<3);
          odtlon_wr_nt_offset[ii][jj]= mr->mr38.odtlon_wr_nt_offset;
          odtloff_wr_nt_offset[ii][jj]= mr->mr38.odtloff_wr_nt_offset;
          mr38[ii][jj]=(odtlon_wr_nt_offset[ii][jj]&0x7) | ((odtloff_wr_nt_offset[ii][jj]&0x7)<<3);
          odtlon_rd_nt_offset[ii][jj]= mr->mr39.odtlon_rd_nt_offset;
          odtloff_rd_nt_offset[ii][jj]=mr->mr39.odtloff_rd_nt_offset;
          mr39[ii][jj]= (odtlon_rd_nt_offset[ii][jj]&0x7) | ((odtloff_rd_nt_offset[ii][jj]&0x7)<<3);
          rd_crc_enable[ii][jj]= mr->mr50.rd_crc_enable;
          wr_crc_enable_lower_nibble[ii][jj]= mr->mr50.wr_crc_enable_lower_nibble;
          wr_crc_enable_upper_nibble[ii][jj]= mr->mr50.wr_crc_enable_upper_nibble;
          wr_crc_error_status[ii][jj]= mr->mr50.wr_crc_error_status;
          wr_crc_auto_disable_enable[ii][jj]=mr->mr50.wr_crc_auto_disable_enable;
          wr_crc_auto_disable_status[ii][jj]=mr->mr50.wr_crc_auto_disable_status;
          mr50[ii][jj]=(rd_crc_enable[ii][jj]&0x1) | ((wr_crc_enable_lower_nibble[ii][jj]&0x1)<<1) | ((wr_crc_enable_upper_nibble[ii][jj]&0x1)<<2) | ((wr_crc_error_status[ii][jj]&0x1)<<3) | ((wr_crc_auto_disable_enable[ii][jj]&0x1)<<4) | ((wr_crc_auto_disable_status[ii][jj]&0x1)<<5);
      }
      else {
        ERROR_MESSAGE(("sdram_protocol=%0d not yet supported.",hdlr->spdData_m.sdram_protocol));          
      }
 
#ifdef MEMC_DDR4
  if(IS_DDR4) {
      ddrTimingParameters_t* timing = &(hdlr->timingParams_m[ii]);
      switch (timing->ddr4_tcl_tck ) {
          case 9 : mr0_cl[ii][jj] = 0; break;
          case 10 : mr0_cl[ii][jj] = 1; break;
          case 11 : mr0_cl[ii][jj] = 2; break;
          case 12 : mr0_cl[ii][jj] = 3; break;
          case 13 : mr0_cl[ii][jj] = 4; break;
          case 14 : mr0_cl[ii][jj] = 5; break;
          case 15 : mr0_cl[ii][jj] = 6; break;
          case 16 : mr0_cl[ii][jj] = 7; break;
          case 17 : mr0_cl[ii][jj] = 13; break;
          case 18 : mr0_cl[ii][jj] = 8; break;
          case 19 : mr0_cl[ii][jj] = 14; break;
          case 20 : mr0_cl[ii][jj] = 9; break;
          case 21 : mr0_cl[ii][jj] = 15; break;
          case 22 : mr0_cl[ii][jj] = 10; break;
          case 23 : mr0_cl[ii][jj] = 12; break;
          case 24 : mr0_cl[ii][jj] = 11; break;
                    //case  25 : mr0_cl = 'b10000; break;	//only 3DS available - not supported by uMCTL2 yet
          case 26 : mr0_cl[ii][jj] = 17; break;
                    //case 27 : mr0_cl = 'b10010; break;	//only 3DS available - not supported by uMCTL2 yet
          case 28 : mr0_cl[ii][jj] = 19; break;
          case 30 : mr0_cl[ii][jj] = 21; break;
          case 32 : mr0_cl[ii][jj] = 23; break;
          default :
                    mr0_cl[ii][jj] = 0;
                    break;
      }
     ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[ii]);
     mr2_cwl[ii][jj]= mregs->mr2.cwl;
      if(IS_RDIMM){
          // RC00 
          // Output inversion MUST BE enable for training
          //RC00_data[0] = 0;
          //RC00_data[3:1] = 0;
          SETREGBITFILD(RC00_data[ii][jj], 0, 0xf, 0); 
          // RC01 
          // Only Y0_t/Y0_c clock is used in rank_mngr when TI RCD model is used
          if (IS_LRDIMM) {
              //RC01_data[3:0] = 0;
              SETREGBITFILD(RC01_data[ii][jj], 0, 0xf, 0);
          } else if (IS_VIP_RDIMM) {
              //RC01_data[3:0] = 0;
              SETREGBITFILD(RC01_data[ii][jj], 0, 0xf, 0);
          } else {
              //RC01_data[3:0] = 14;
              SETREGBITFILD(RC01_data[ii][jj], 0, 0xf, 14);
          }
          // RC08 
          if (hdlr->spdData_m.num_ranks_per_dimm  == 4) { // Direct Quad CS mode
              if (IS_CID_EN) {  // 3DS
                  //RC08_data[1:0] = 0; // QxC[2:0]enabled
                  SETREGBITFILD(RC08_data[ii][jj], 0, 0x3, 0);
              } else { // non-3DS
                  //RC08_data[1:0] = 1; // QxC[2]disabled, QxC0[1:0] enabled
                  SETREGBITFILD(RC08_data[ii][jj], 0, 0x3, 1);
              }
          } else { // Direct Dual CS mode
              if (hdlr->spdData_m.cid_width > 0) {
#ifdef UMCTL2_CID_EN
                  if (DRAM_NUM_3DS_LRANKS == 2) { // 2H
                      //RC08_data[1:0] = 2; // QxC[2:1]disabled, QxC0 enabled
                      SETREGBITFILD(RC08_data[ii][jj], 0, 0x3, 2);
                  } else if (DRAM_NUM_3DS_LRANKS == 4) { // 4H
                      //RC08_data[1:0] = 1; // QxC[2]disabled, QxC0[1:0] enabled
                      SETREGBITFILD(RC08_data[ii][jj], 0, 0x3, 1);
                  } else { // 8H
                      //RC08_data[1:0] = 0; // QxC[2:0]enabled
                      SETREGBITFILD(RC08_data[ii][jj], 0, 0x3, 0);
                  }
#endif
              } else { // non-3DS
                  //RC08_data[1:0] = 3; // QxC[2:0]disabled
                  SETREGBITFILD(RC08_data[ii][jj], 0, 0x3, 3);
              }
          }
          // QxPAR outputs disabled
          //RC08_data[2] = 0;
          SNPS_SETBIT(RC08_data[ii][jj], 2, 0);
          // QxPAR outputs disabled
          //RC08_data[2] = 0;
          SNPS_SETBIT(RC08_data[ii][jj], 2, 0);

          // DA17 Input Buffer and QxA17 outputs disabled
           REGB_DDRC_CH0_DIMMCTL_struct_t *reg=&hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DIMMCTL_reg;           
          SNPS_SETBIT(RC08_data[ii][jj], 3, reg->mrs_a17_en ? 0 : 1);
          // RC0A
          // Set PLL bypass mode temporarily to prevent SPEC_VIOLATION from happening due to the jitter generated by PLL
          // RDIMM Operating Speed
          switch (hdlr->spdData_m.tck_ps[ii]  ) {
              case 1250:
                  //RC0A_data[3:0] = 0; // DDR4-1600
                  SETREGBITFILD(RC0A_data[ii][jj], 0, 0xf, 0);
                  break;
              case 1071:
              case 1072:
                  //RC0A_data[3:0] = 1; // DDR4-1866
                  SETREGBITFILD(RC0A_data[ii][jj], 0, 0xf, 1);
                  break;
              case 938:
                  //RC0A_data[3:0] = 2; // DDR4-2133
                  SETREGBITFILD(RC0A_data[ii][jj], 0, 0xf, 2);
                  break;
              case 833:
                  //RC0A_data[3:0] = 3; // DDR4-2400
                  SETREGBITFILD(RC0A_data[ii][jj], 0, 0xf, 3);
                  break;
              case 750:
                  //RC0A_data[3:0] = 4; // DDR4-2666
                  SETREGBITFILD(RC0A_data[ii][jj], 0, 0xf, 4);
                  break;
              case 682:
                  //RC0A_data[3:0] = 5; // DDR4-2933
                  SETREGBITFILD(RC0A_data[ii][jj], 0, 0xf, 5);
                  break;
              case 625:
                  //RC0A_data[3:0] = 5; // DDR4-3200

                  //RCD01 spec
                  //SETREGBITFILD(RC0A_data[ii][jj],0,0xf,5);

                  //RCD02 spec
                  SETREGBITFILD(RC0A_data[ii][jj], 0, 0xf, 6);
                  break;
                  //  ---      : RC0A_data[3:0] = 4'b0110; // Reserved
              case 8000:
                  //RC0A_data[3:0] = 7; // PLL bypass mode
                  SETREGBITFILD(RC0A_data[ii][jj], 0, 0xf, 7);
                  break;
              default:
                  ERROR_MESSAGE(("[RDIMM] unknown speed grade for RCD model"));
          }
          // RC0D
          // CS mode
          if (hdlr->spdData_m.num_ranks_per_dimm == 4) { // Direct Quad CS mode
              //RC0D_data[1:0] = 1;
              SETREGBITFILD(RC0D_data[ii][jj], 0, 0x3, 1);
          } else { // Direct Dual CS mode
              //RC0D_data[1:0] = 0;
              SETREGBITFILD(RC0D_data[ii][jj], 0, 0x3, 0);
          }
          // DIMM Type
          if (!IS_LRDIMM) {
              //RC0D_data[2] = 1;
              SNPS_SETBIT(RC0D_data[ii][jj], 2, 1);
          } else {
              //RC0D_data[2] = 0;
              SNPS_SETBIT(RC0D_data[ii][jj], 2, 0);
          }
          // Address mirroring for MRS commands
          // TODO this code need to be reviewed!
#ifdef MEMC_NUM_RANKS_1
          //RC0D_data[3] = 0;
          SNPS_SETBIT(RC0D_data[ii][jj], 3, 0);
#else // Not MEMC_NUM_RANKS_1
          uint32_t active_ranks = hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_MSTR0_reg.active_ranks;
#ifdef MEMC_NUM_RANKS_GT_4
          uint32_t active_ranks_msb =
              hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_MSTR0_reg.active_ranks >>
              (hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_MSTR0_reg.active_ranks_msb - 1);
#endif
          uint32_t dimm_addr_mirr_en = hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DIMMCTL_reg.dimm_addr_mirr_en;
          uint32_t dimm_dis_bg_mirroring = hdlr->memCtrlr_m.regs.REGB_DDRC_CH0_DIMMCTL_reg.dimm_dis_bg_mirroring;

          if (dimm_addr_mirr_en && !dimm_dis_bg_mirroring
#ifdef MEMC_NUM_RANKS_GT_4
                  && ((active_ranks_msb == 1) || ((active_ranks_msb == 0) && (active_ranks != 1)))
#else
                  && (active_ranks != 1)
#endif // MEMC_NUM_RANKS_GT_4
             ) {
              //RC0D_data[3] = 1;
              SNPS_SETBIT(RC0D_data[ii][jj], 3, 1);
          } else {
              //RC0D_data[3] = 0;
              SNPS_SETBIT(RC0D_data[ii][jj], 3, 0);
          }
#endif // MEMC_NUM_RANKS_1

          // RC0E
          // Parity Enable
          // Even if parity checking is enable for RCD, it will not be enable during training, but only at the end of training
          // So just disable parity always for training
          //`ifdef UMCTL2_CRC_PARITY_RETRY
          //   mr_data[0] = cDdrcCfg.rcd_parity_en;
          //`else
          //   mr_data[0] = 1'b0;
          //`endif
          //RC0E_data[0] = 0;
          SNPS_SETBIT(RC0E_data[ii][jj], 0, 0);
          // Reserved
          //RC0E_data[1] = 0;
          SNPS_SETBIT(RC0E_data[ii][jj], 1, 0);
          // ALERT_n Assertion
          //RC0E_data[2] = 1;
          SNPS_SETBIT(RC0E_data[ii][jj], 2, 1);
          // ALERT_n Re-enable
          //RC0E_data[3] = 1;
          SNPS_SETBIT(RC0E_data[ii][jj], 3, 1);
          // RC0F
          // Latency adder nLadd to all DRAM commands
          if (hdlr->spdData_m.tck_ps[ii] < 833) {
              //RC0F_data[3:0] = 1;
              SETREGBITFILD(RC0F_data[ii][jj], 0, 0xF, 1);
          } else {
              //RC0F_data[3:0] = 0;
              SETREGBITFILD(RC0F_data[ii][jj], 0, 0xF, 0);
          }
          // RC3x
          // Set to a value consistent with DRAMFreq field value described above
          //RC3x_data = (GET_TCK(0) <= 620 ) ? 0 : (GET_TCK(0) - 621)/10;
          {
              uint32_t F = CEIL(2000000, hdlr->spdData_m.tck_ps[ii] );
              RC3x_data[ii][jj] = (hdlr->spdData_m.tck_ps[ii] <= 620) ? 0 : CEIL(F - 1260, 20);
          }
          
          // LRDIMM only
          // BC0A
          // LRDIMM Operating Speed
          switch (hdlr->spdData_m.tck_ps[ii]) {
              case 1250:
                  //BC0A_data[3:0] = 0; // DDR4-1600
                  SETREGBITFILD(BC0A_data[ii][jj], 0, 0xF, 0);
                  break;
              case 1071:
              case 1072:
                  //BC0A_data[3:0] = 1; // DDR4-1866
                  SETREGBITFILD(BC0A_data[ii][jj], 0, 0xF, 1);
                  break;
              case 938:
                  //BC0A_data[3:0] = 2; // DDR4-2133
                  SETREGBITFILD(BC0A_data[ii][jj], 0, 0xF, 2);
                  break;
              case 833:
                  //BC0A_data[3:0] = 3; // DDR4-2400
                  SETREGBITFILD(BC0A_data[ii][jj], 0, 0xF, 3);
                  break;
              case 750:
                  //BC0A_data[3:0] = 4; // DDR4-2666
                  SETREGBITFILD(BC0A_data[ii][jj], 0, 0xF, 4);
                  break;
              case 682:
                  //BC0A_data[3:0] = 5; // DDR4-2933
                  SETREGBITFILD(BC0A_data[ii][jj], 0, 0xF, 5);
                  break;
              case 625:
                  //BC0A_data[3:0] = 6; // DDR4-3200
                  SETREGBITFILD(BC0A_data[ii][jj], 0, 0xF, 6);
                  break;
              case 8000:
                  //BC0A_data[3:0] = 7; // Test frequency range
                  SETREGBITFILD(BC0A_data[ii][jj], 0, 0xF, 7);
                  break;
              default:
                  ERROR_MESSAGE(("[VIP_LRDIMM] unknown speed grade for VIP LRDIMM model"));
                  break;
          }
          // F0BC6x 
          // F0BC6x_data = (GET_TCK(0) <= 620 ) ? 0 : (GET_TCK(0) - 621)/10;
          {
              uint32_t F = CEIL(2000000, 625);
              F0BC6x_data[ii][jj] = (hdlr->spdData_m.tck_ps[ii] <= 620) ? 0 : CEIL(F - 1260, 20);
          }
      } // IS_RDIMM
  } // DDR4
#endif

  } // jj -> dch
  } // ii -> pstates

  if(IS_DDR4) {
      dram_type=DWC_DDR4;
  } else if(IS_DDR5) {
      dram_type=DWC_DDR5;
  } else {
    ERROR_MESSAGE(("sdram_protocol=%0d not yet supported.",hdlr->spdData_m.sdram_protocol));
  }
  if(IS_UDIMM) {dimm_type=0;}
  if(IS_RDIMM) {dimm_type=2;}
  if(IS_LRDIMM) {dimm_type=3;}
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
  } else  { 
    num_dbyte = MEMC_DRAM_DATA_WIDTH/8/4;
  } 
#endif

#ifdef MEMC_SIDEBAND_ECC
  if(hdlr->memCtrlr_m.sdram_bus_width == DWC_BUSWIDTH_HALF) {
  #if defined(MEMC_DRAM_DATA_WIDTH_GT_63)
    disabled_dbyte = 0xf0;
  #elif defined(MEMC_DRAM_DATA_WIDTH_GT_31)
    disabled_dbyte = 0xec;
  #else
    disabled_dbyte = 0xfa;
  #endif
  }
  else if(hdlr->memCtrlr_m.sdram_bus_width == DWC_BUSWIDTH_QUARTER){
  #ifdef MEMC_DRAM_DATA_WIDTH_GT_63
    disabled_dbyte = 0xfc;
  #else
    disabled_dbyte = 0xee;
  #endif
  }
#endif
  //#############################################################################
  //
  // Structure for basic (mandatory) user inputs
  //
  //#############################################################################
#ifdef MEMC_DDR4
if(IS_DDR4) {
  phyinit_setUserInput (hdlr, "DramType", dram_type);
  phyinit_setUserInput(hdlr, "NumPStates",hdlr->num_pstates);
  phyinit_setUserInput (hdlr, "NumRank_dfi0",hdlr->spdData_m.num_ranks);
  phyinit_setUserInput (hdlr, "DisablePmuEcc",1);//disabled the SRAM ECC feature temporarily
  #ifdef DWC_PHYINIT_RID_GE201904
  phyinit_setUserInput (hdlr, "skip_train", 1);
  #endif 

#ifdef DWC_DDRPHY_DFI1_EXISTS
  phyinit_setUserInput(hdlr, "Dfi1Exists",1);
  dfi_mode=5;
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
    phyinit_setUserInput(hdlr, "Dfi1Exists",0);
    dfi_mode=5;
#endif

  phyinit_setUserInput (hdlr, "NumActiveDbyteDfi0", num_active_dbyte_dfi0);

  phyinit_setUserInput (hdlr, "DimmType", dimm_type);
  
  phyinit_setUserInput (hdlr, "NumAnib", hdlr->num_anibs );  
  phyinit_setUserInput (hdlr, "NumDbyte", num_dbyte);
  phyinit_setUserInput (hdlr, "DramDataWidth", hdlr->spdData_m.sdram_width_bits);
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
}//DDR4
#endif

  if(IS_DDR4) {
    phyinit_setUserInput(hdlr, "PllBypass[0]", regs->REGB_DDRC_CH0_MSTR0_reg.dll_off_mode);  
    phyinit_setUserInput(hdlr, "PllBypass[1]", 0);  // TODO
    phyinit_setUserInput(hdlr, "PllBypass[2]", 0);  // TODO
    phyinit_setUserInput(hdlr, "PllBypass[3]", 0);  // TODO
  }
  
  uint32_t addr_mirror;
  if( hdlr->spdData_m.addr_mirror) {
      if(hdlr->spdData_m.num_ranks==4) {
        addr_mirror=0x4;
      } else if(hdlr->spdData_m.num_ranks==2) {
        addr_mirror=0x2;
      } else {
        addr_mirror=0;
      }
  } else {
      if(hdlr->spdData_m.shared_ac==1) {
        addr_mirror=2;
      } else {
        addr_mirror=0;
      }

  }
  
  if(hdlr->spdData_m.num_ranks==4) { cs_present_cha=0xf;}
  else if(hdlr->spdData_m.num_ranks==2) {cs_present_cha=0x3;}
  else {cs_present_cha=0x1; }
 
//#############################################################################
//
// Structure for advanced (optional) user inputs
// - if user does not enter a value for these parameters, a PHY recommended or
//   default value will be used
//
//############################################################################# 
#ifdef MEMC_DDR4
if(IS_DDR4) {
  uint32_t tck_ps=hdlr->spdData_m.tck_ps[1];
  ddr4_mode_registers_t* mr = &(hdlr->memCtrlr_m.ddr4_mr[0]);
  phyinit_setUserInput(hdlr, "D4RxPreambleLength[0]",mr->mr4.rd_preamble); 
  phyinit_setUserInput(hdlr, "D4TxPreambleLength[0]",mr->mr4.wr_preamble);
  if( tck_ps >= 938 ) {
      phyinit_setUserInput(hdlr, "D4RxPreambleLength[1]",0); 
      phyinit_setUserInput(hdlr, "D4TxPreambleLength[1]",0);	  
  } else {
      phyinit_setUserInput(hdlr, "D4RxPreambleLength[1]",mr->mr4.rd_preamble); 
      phyinit_setUserInput(hdlr, "D4TxPreambleLength[1]",mr->mr4.wr_preamble);      
  }

#ifdef UMCTL2_FREQUENCY_NUM_GT_2
  tck_ps=hdlr->spdData_m.tck_ps[2];
  if( tck_ps >= 938 ) {
      phyinit_setUserInput(hdlr, "D4RxPreambleLength[2]",0); 
      phyinit_setUserInput(hdlr, "D4TxPreambleLength[2]",0);	  
  } else {
      phyinit_setUserInput(hdlr, "D4RxPreambleLength[2]",mr->mr4.rd_preamble); 
      phyinit_setUserInput(hdlr, "D4TxPreambleLength[2]",mr->mr4.wr_preamble);      
  }
#endif // UMCTL2_FREQUENCY_NUM_GT_2
#ifdef UMCTL2_FREQUENCY_NUM_GT_3
  tck_ps=hdlr->spdData_m.tck_ps[3];
  if( tck_ps >= 938 ) {
      phyinit_setUserInput(hdlr, "D4RxPreambleLength[3]",0); 
      phyinit_setUserInput(hdlr, "D4TxPreambleLength[3]",0);	  
  } else {
      phyinit_setUserInput(hdlr, "D4RxPreambleLength[3]",mr->mr4.rd_preamble); 
      phyinit_setUserInput(hdlr, "D4TxPreambleLength[3]",mr->mr4.wr_preamble);      
  }
#endif // UMCTL2_FREQUENCY_NUM_GT_3


}
#endif // MEMC_DDR4

if(IS_DDR4) {
phyinit_setUserInput(hdlr, "Is2Ttiming[0]",is_2t_timing);
phyinit_setUserInput(hdlr, "Is2Ttiming[1]",is_2t_timing);
#ifdef UMCTL2_FREQUENCY_NUM_GT_2
phyinit_setUserInput(hdlr, "Is2Ttiming[2]",is_2t_timing);
#endif
#ifdef UMCTL2_FREQUENCY_NUM_GT_3
phyinit_setUserInput(hdlr, "Is2Ttiming[3]",is_2t_timing);
#endif
uint32_t dis_dynadrtri=1;
#ifdef MEMC_DDR4
  dis_dynadrtri=regs->REGB_DDRC_CH0_DFIMISC_reg.dis_dyn_adr_tri;
#endif
phyinit_setUserInput(hdlr, "DisDynAdrTri[0]", dis_dynadrtri);
phyinit_setUserInput(hdlr, "DisDynAdrTri[1]", dis_dynadrtri);
#ifdef UMCTL2_FREQUENCY_NUM_GT_2
phyinit_setUserInput(hdlr, "DisDynAdrTri[2]", dis_dynadrtri);
#endif
#ifdef UMCTL2_FREQUENCY_NUM_GT_3
phyinit_setUserInput(hdlr, "DisDynAdrTri[3]", dis_dynadrtri);
#endif
}
if( IS_DDR4 && hdlr->mr7_by_phy) {
  phyinit_setUserInput(hdlr, "SnpsUmctlOpt",1);
}

//#############################################################################
//
// Structure for user input simulation options
//
//#############################################################################

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
  for(int i=0;i<hdlr->num_pstates;i++) {
    for(int j=0;j<1;j++) {  // Hardcode 1 as PHY supports only 1 channel
      phyinit_setMb (hdlr, i, "MsgMisc", msgmisc, train_2d);
      phyinit_setMb (hdlr, i, "HdtCtrl",hdlr->HdtCtrl , train_2d); // Stage completion
      phyinit_setMb (hdlr, i, "DFIMRLMargin", 1, train_2d);
      if(IS_DDR4) {
          phyinit_setMb (hdlr, i, "CsPresent", cs_present_cha, 0);
          phyinit_setMb (hdlr, i, "DisabledDbyte", disabled_dbyte, train_2d);
          phyinit_setMb (hdlr, i, "AddrMirror", addr_mirror, 0);
          phyinit_setMb (hdlr, i, "MR0", (mr0[i][j] & 0xffff), 0);
          phyinit_setMb (hdlr, i, "MR1", (mr1[i][j] & 0xffff), 0);
          phyinit_setMb (hdlr, i, "MR2", (mr2[i][j] & 0xffff), 0);
          phyinit_setMb (hdlr, i, "MR3", (mr3[i][j] & 0xffff), 0);
          phyinit_setMb (hdlr, i, "MR4", (mr4[i][j] & 0xffff), 0);
          phyinit_setMb (hdlr, i, "MR5", (mr5[i][j] & 0xffff), 0);
          phyinit_setMb (hdlr, i, "MR6", (mr6[i][j] & 0xffff), 0); 
          phyinit_setMb (hdlr, i, "ALT_CAS_L",
                  (SNPS_GETBIT(mr0_cl[i][j],4) << 12) | (SNPS_GETBITMASK(mr0_cl[i][j],3,1)<<4) | (SNPS_GETBIT(mr0_cl[i][j],0)<<2) | 0x1,
                  0);
          phyinit_setMb (hdlr, i, "ALT_WCAS_L", (
                      (SNPS_GETBITMASK(mr2_cwl[i][j],2,0) << 3) |// mr2_cwl[2:0]
                      1 //ALT_WCAS_L[0] = 1: use value in ALT_WCAS_L,depends on MR4[12]
                      ),
                  0);
          if(IS_RDIMM) {
              // DDR4 RCD0
              phyinit_setMb (hdlr, i, "CsPresentD0", cs_presentD0, 0);
              phyinit_setMb (hdlr, i, "F0RC00_D0", RC00_data[i][j], 0);
              phyinit_setMb (hdlr, i, "F0RC01_D0", RC01_data[i][j], 0);
              phyinit_setMb (hdlr, i, "F0RC08_D0", RC08_data[i][j], 0);
              phyinit_setMb (hdlr, i, "F0RC0A_D0", RC0A_data[i][j], 0);
              phyinit_setMb (hdlr, i, "F0RC0D_D0", RC0D_data[i][j], 0);
              phyinit_setMb (hdlr, i, "F0RC0E_D0", RC0E_data[i][j], 0);
              phyinit_setMb (hdlr, i, "F0RC0F_D0", RC0F_data[i][j], 0);
              phyinit_setMb (hdlr, i, "F0RC3x_D0", RC3x_data[i][j], 0);

              if(IS_LRDIMM) {
                  phyinit_setMb (hdlr, i, "BC0A_D0", BC0A_data[i][j], 0);
                  phyinit_setMb (hdlr, i, "F0BC6x_D0", F0BC6x_data[i][j], 0);
              }

              // DDR4 RCD1
              if (hdlr->spdData_m.num_rcds  > 1) {
                  phyinit_setMb (hdlr, i, "CsPresentD1", cs_presentD1, 0);
                  phyinit_setMb (hdlr, i, "F0RC00_D1", RC00_data[i][j], 0);
                  phyinit_setMb (hdlr, i, "F0RC01_D1", RC01_data[i][j], 0);
                  phyinit_setMb (hdlr, i, "F0RC08_D1", RC08_data[i][j], 0);
                  phyinit_setMb (hdlr, i, "F0RC0A_D1", RC0A_data[i][j], 0);
                  phyinit_setMb (hdlr, i, "F0RC0D_D1", RC0D_data[i][j], 0);
                  phyinit_setMb (hdlr, i, "F0RC0E_D1", RC0E_data[i][j], 0);
                  phyinit_setMb (hdlr, i, "F0RC0F_D1", RC0F_data[i][j], 0);
                  phyinit_setMb (hdlr, i, "F0RC3x_D1", RC3x_data[i][j], 0);

                  if(IS_LRDIMM) {
                      phyinit_setMb (hdlr, i, "BC0A_D1", BC0A_data[i][j], 0);
                      phyinit_setMb (hdlr, i, "F0BC6x_D1", F0BC6x_data[i][j], 0);
                  }
              } // num_rcds              
          }
      } else if(IS_DDR5) {
             phyinit_setMb (hdlr, i, "MR0_A0", (mr0[i][j] & 0xffff), 0);
             phyinit_setMb (hdlr, i, "MR3_A0", (mr3[i][j] & 0xffff), 0);
             phyinit_setMb (hdlr, i, "MR4_A0", (mr4[i][j] & 0xffff), 0);
             phyinit_setMb (hdlr, i, "MR5_A0", (mr5[i][j] & 0xffff), 0);
             phyinit_setMb (hdlr, i, "MR6_A0", (mr6[i][j] & 0xffff), 0);
             phyinit_setMb (hdlr, i, "MR8_A0", (mr8[i][j] & 0xffff), 0);
             phyinit_setMb (hdlr, i, "MR12_A0", (mr13[i][j] & 0xffff), 0);   
             phyinit_setMb (hdlr, i, "MR34_A0", (mr34[i][j] & 0xffff), 0);   
             phyinit_setMb (hdlr, i, "MR35_A0", (mr35[i][j] & 0xffff), 0);   
             phyinit_setMb (hdlr, i, "MR37_A0", (mr37[i][j] & 0xffff), 0);   
             phyinit_setMb (hdlr, i, "MR38_A0", (mr38[i][j] & 0xffff), 0);   
             phyinit_setMb (hdlr, i, "MR39_A0", (mr39[i][j] & 0xffff), 0);   
             phyinit_setMb (hdlr, i, "MR50_A0", (mr50[i][j] & 0xffff), 0);   
             phyinit_setMb (hdlr, i, "UseBroadcastMR", 1, 0);   
             phyinit_setMb (hdlr, i, "CsPresentChA", cs_present_cha, 0);   
      } else {
           ERROR_MESSAGE(("sdram_protocol=%0d not yet supported.",hdlr->spdData_m.sdram_protocol)); 
      }
       if (IS_LRDIMM) {
          //DDR4 LRDIMM 1D
          // SequenceCtrl[0]	= 1	Run DevInit - Device/phy initialization. Should always be set.
          // SequenceCtrl[1]	= 1	Run WrLvl - Write leveling
          // SequenceCtrl[2]	= 1	Run RxEn - Read gate training
          // SequenceCtrl[3]	= 1	Run RdDQS1D - 1d read dqs training
          //
          // SequenceCtrl[4]	= 1	Run WrDQ1D - 1d write dq training
          // SequenceCtrl[5]	= 0	RFU, must be zero
          // SequenceCtrl[6]	= 0	RFU, must be zero
          // SequenceCtrl[7]	= 0	RFU, must be zero
          //
          // SequenceCtrl[8]	= 1	Run RdDeskew - Per lane read dq deskew training
          // SequenceCtrl[9]	= 1	Run MxRdLat - Max read latency training
          // SequenceCtrl[10]	= 1	Run DWL - LDRIMM DRAM Write Leveling
          // SequenceCtrl[11]	= 1	Run MREP - LRDIMM DRAM Interface MDQ Receive Enable Phase training
          //
          // SequenceCtrl[12]	= 1	Run MRD - DRAM-to-DB Read Delay training
          // SequenceCtrl[13]	= 1	Run MWD - DB-to-DRAM Write Delay training
          // SequenceCtrl[14]	= 0	RFU, must be zero
          // SequenceCtrl[15]	= 0	RFU, must be zero
          if(hdlr->phy_training==1) {
              phyinit_setMb (hdlr, i, "SequenceCtrl", 0x3f1f, 0);
          } else {
              phyinit_setMb (hdlr, i, "SequenceCtrl", 0x0001, 0);	 //Run DevInit only
          }
      }  else {
          if(hdlr->phy_training==1) {
              phyinit_setMb (hdlr, i, "SequenceCtrl", 0x31f, 0);
          } else {
              phyinit_setMb (hdlr, i, "SequenceCtrl", 0x0001, 0);	 //Run DevInit only
          }
      }      

    } // for num_dch
  } // for num_pstates
  
#endif // PHYINIT

}


