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


#include <assert.h>
#include "dwc_cinit.h"
#include "bit_macros.h"
#include "dwc_cinit_macros.h"
    
#ifdef PHYINIT
// PHYINT functions used here but defined in PHYINT

extern int dwc_ddrphy_phyinit_setMb (int ps, char *field, int value, int Train2D);
extern int dwc_ddrphy_phyinit_setUserInput (char *field, int value);
extern int dwc_ddrphy_phyinit_log();

#endif // PHYINIT

void phyinit_setUserInput(SubsysHdlr_t *hdlr, char *field, int value) {
#ifdef PHYINIT

  LOG_MESSAGE(hdlr, 1, ("phyinit_setUserInput(OTHER)(%s=%d)\n",field,value));
  dwc_ddrphy_phyinit_setUserInput(field, value);

#endif // PHYINIT

}

void phyinit_setMb(SubsysHdlr_t *hdlr, int ps, char *field, int value, int Train2D) {
#ifdef PHYINIT

  dwc_ddrphy_phyinit_setMb(ps, field, value, Train2D); 

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
  uint32_t num_dbyte,dram_type,dimm_type, cs_present_cha, cs_present_chb,
           enabled_dq_cha, enabled_dq_chb, dfi_mode,
           pllbypass; 
  uint32_t num_active_dbyte_dfi0, num_active_dbyte_dfi1;
  uint32_t mr0[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr1[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr2[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr3[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr4[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr5[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr6[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr11[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr12[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr13[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr14[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr22[hdlr->num_pstates][hdlr->num_dch];  
  uint32_t mr0_cl[hdlr->num_pstates][hdlr->num_dch];
  uint32_t mr2_cwl[hdlr->num_pstates][hdlr->num_dch];
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
  train_2d=0;
  pllbypass=0;
  cs_presentD0=0;
  cs_presentD1=0;
    
  //  dwc_ddrphy_phyinit_setDefault(0);

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
      else if(IS_DDR4) {
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
                SETREGBITFILD(mr5[ii][jj],0,0x7,0);	//C/A Parity Latency Mode
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
  } else if(IS_LPDDR4) {
      dram_type=DWC_LPDDR4;
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
  phyinit_setUserInput (hdlr, "NumRank_dfi0",hdlr->spdData_m.num_ranks);
  uint8_t DisablePhyUpdate= (regs->REGB_DDRC_CH0_DFIUPD0_reg.dfi_phyupd_en==1) ? 0 : 1;
  phyinit_setUserInput (hdlr, "DisablePhyUpdate",DisablePhyUpdate);  

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
    phyinit_setUserInput(hdlr, "Dfi1Exists",0);
    dfi_mode=5;
  #endif
#endif


  phyinit_setUserInput(hdlr, "DfiMode",dfi_mode);
  phyinit_setUserInput (hdlr, "NumActiveDbyteDfi0", num_active_dbyte_dfi0);
  phyinit_setUserInput (hdlr, "NumActiveDbyteDfi1", num_active_dbyte_dfi1);
  phyinit_setUserInput (hdlr, "DimmType", dimm_type); 
  phyinit_setUserInput (hdlr, "NumAnib", hdlr->num_anibs );  
  phyinit_setUserInput (hdlr, "NumDbyte", num_dbyte);
  // check that DramDataWidth is setup correctly
  if( IS_LPDDR4 ) {
      CONSTRAIN_NE(hdlr->spdData_m.sdram_width_bits,4);
      /*CONSTRAIN_NE(hdlr->spdData_m.sdram_width_bits,32);*/
  }
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
  uint8_t rd_dbi_enable=0;  
#ifdef MEMC_DDR4_OR_LPDDR4
  rd_dbi_enable=regs->REGB_DDRC_CH0_DBICTL_reg.rd_dbi_en;
#endif
  phyinit_setUserInput(hdlr, "ReadDBIEnable[0]",rd_dbi_enable);
  phyinit_setUserInput(hdlr, "ReadDBIEnable[1]",rd_dbi_enable);
#ifdef UMCTL2_FREQUENCY_NUM_GT_2
  phyinit_setUserInput(hdlr, "ReadDBIEnable[2]",rd_dbi_enable);
#endif
#ifdef UMCTL2_FREQUENCY_NUM_GT_3
  phyinit_setUserInput(hdlr, "ReadDBIEnable[3]",rd_dbi_enable);
#endif

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
  if(IS_DDR4) {
    phyinit_setUserInput(hdlr, "PllBypass[0]", regs->REGB_DDRC_CH0_MSTR0_reg.dll_off_mode);  
    phyinit_setUserInput(hdlr, "PllBypass[1]", 0);  // TODO
    phyinit_setUserInput(hdlr, "PllBypass[2]", 0);  // TODO
    phyinit_setUserInput(hdlr, "PllBypass[3]", 0);  // TODO
  }
  else if(IS_LPDDR4) {
    phyinit_setUserInput(hdlr, "PllBypass[0]",pllbypass);	
    phyinit_setUserInput(hdlr, "PllBypass[1]",pllbypass); 
#ifdef UMCTL2_FREQUENCY_NUM_GT_2
    phyinit_setUserInput(hdlr, "PllBypass[2]",pllbypass);
#endif
#ifdef UMCTL2_FREQUENCY_NUM_GT_3
    phyinit_setUserInput(hdlr, "PllBypass[3]",pllbypass);
#endif    
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
  

  phyinit_setUserInput(hdlr, "WDQSExt", 1); // TODO add some variable to control this
  
  phyinit_setUserInput(hdlr, "Lp4RxPreambleMode[0]",0); //static preamble  
  phyinit_setUserInput(hdlr, "Lp4RxPreambleMode[1]",0); //static preamble
  phyinit_setUserInput(hdlr, "Lp4PostambleExt[0]",mr->mr3.wr_postamble );
  phyinit_setUserInput(hdlr, "Lp4PostambleExt[1]",mr->mr3.wr_postamble);
      
#ifdef UMCTL2_FREQUENCY_NUM_GT_2
  phyinit_setUserInput(hdlr, "Lp4RxPreambleMode[2]",0); //static preamble
  phyinit_setUserInput(hdlr, "Lp4PostambleExt[2]",mr->mr3.wr_postamble);
#endif //UMCTL2_FREQUENCY_NUM_GT_2
#ifdef UMCTL2_FREQUENCY_NUM_GT_3
  phyinit_setUserInput(hdlr, "Lp4RxPreambleMode[3]",0); //static preamble
  phyinit_setUserInput(hdlr, "Lp4PostambleExt[3]",mr->mr3.wr_postamble);
#endif //UMCTL2_FREQUENCY_NUM_GT_3  
}
#endif //MEMC_LPDDR4
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
if( IS_DDR4 && hdlr->mr7_by_phy) {
  phyinit_setUserInput(hdlr, "SnpsUmctlOpt",1);
}

if(IS_LPDDR4) {

  for(int i=0;i<hdlr->num_pstates;i++) {
    for(int j=0;j<1;j++) {  // Hardcode 1 as PHY supports only 1 channel
      char field[20];
      sprintf(field, "Lp4RL[%0d]",i);
      phyinit_setUserInput(hdlr, field ,SNPS_GETREGBITFIELD(mr2[i][j],0,0x7));

      sprintf(field, "Lp4WL[%0d]",i);
      phyinit_setUserInput(hdlr, field, SNPS_GETREGBITFIELD(mr2[i][j],3,0x38));

      sprintf(field, "Lp4WLS[%0d]",i);
      phyinit_setUserInput(hdlr, field, SNPS_GETBIT(mr2[i][j],6));

      sprintf(field, "Lp4DbiRd[%0d]",i);
      phyinit_setUserInput(hdlr, field,SNPS_GETBIT(mr3[i][j],6));

      sprintf(field, "Lp4DbiWr[%0d]",i);
      phyinit_setUserInput(hdlr, field,SNPS_GETBIT(mr3[i][j],7));
    }
  }
}
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
#endif //MEMC_LPDDR4
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

      }
      if(IS_DDR4) {
          phyinit_setMb (hdlr, i, "CsPresent", cs_present_cha, 0);
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
      }
      if(IS_LPDDR4) {
          //LPDDR3 and LPDDR4 1D
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
          // SequenceCtrl[10]	= 0	RFU, must be zero
          // SequenceCtrl[11]	= 0	RFU, must be zero
          //
          // SequenceCtrl[12]	= 1	Run LPCA - CA Training
          // SequenceCtrl[13]	= 0	RFU, must be zero
          // SequenceCtrl[14]	= 0	RFU, must be zero
          // SequenceCtrl[15]	= 0	RFU, must be zero
        //  if(hdlr->use_pub_training) {
              phyinit_setMb (hdlr, i, "SequenceCtrl", 0x131f, 0);
      //    } else {
     //       phyinit_setMb (hdlr, i, "SequenceCtrl", 0x0001, 0);   //Run DevInit only
      //    }

      } else if (IS_LRDIMM) {
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
          if(hdlr->phy_training==0) {
              phyinit_setMb (hdlr, i, "SequenceCtrl", 0x3f1f, 0);
          } else {
              phyinit_setMb (hdlr, i, "SequenceCtrl", 0x0001, 0);	 //Run DevInit only
          }
      }  else {
          phyinit_setMb (hdlr, i, "SequenceCtrl", 0x0001, 0);    //Run DevInit only
      }      

    } // for num_dch
  } // for num_pstates
  // For LPDDR4 byte mode, X8Mode must be set to 1 in all PStates to avoid the error message
  // from dwc_ddrphy_phyinit_calcMb() function.
  if(IS_LPDDR4) {
      if(hdlr->spdData_m.sdram_width_bits==8) {
          for(int ii=0;ii<4;ii++) {
            phyinit_setMb (hdlr, ii, "X8Mode", 0xf, train_2d);
          }
      }
  }

#endif // PHYINIT

}


