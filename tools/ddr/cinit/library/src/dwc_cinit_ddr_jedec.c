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

#include <string.h>
#include <assert.h>
#include <math.h>

#include "log.h"
#include "dwc_cinit.h"
#ifdef MEMC_DDR4
// --------------------------------------------------------------------------
// Name        : ddr4::set_clk_speed()
// Description : set the sg_tck_ps value in the hdlr->timingParams_m structure
// Params      : hdlr
// Returns     : none
// --------------------------------------------------------------------------
void ddr4_set_clk_speed(SubsysHdlr_t* hdlr, uint32_t p)
{
  dwc_ddr4_speed_grade_e sg = hdlr->spdData_m.ddr4_sg;
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);

  switch (sg) {
    case DWC_DDR4_1600J :
    case DWC_DDR4_1600K :
    case DWC_DDR4_1600L :
      timing->sg_tck_ps = 1250;
      break;
    case DWC_DDR4_1866L :
    case DWC_DDR4_1866M :
    case DWC_DDR4_1866N :
      #if (MEMORYMODELS > 0)
        timing->sg_tck_ps = 1071;
      #else
        timing->sg_tck_ps = 1072;
      #endif
      break;
    case DWC_DDR4_2133N :
    case DWC_DDR4_2133P :
    case DWC_DDR4_2133R :
      timing->sg_tck_ps = 938;
      break;
    case DWC_DDR4_2400P :
    case DWC_DDR4_2400R :
    case DWC_DDR4_2400T :
    case DWC_DDR4_2400U :
      timing->sg_tck_ps = 833;
      break;
    case DWC_DDR4_2666T :
    case DWC_DDR4_2666U :
    case DWC_DDR4_2666V :
    case DWC_DDR4_2666W :
      timing->sg_tck_ps = 750;
      break;
    case DWC_DDR4_2933V :
    case DWC_DDR4_2933W :
    case DWC_DDR4_2933Y :
    case DWC_DDR4_2933AA :
      timing->sg_tck_ps = 682;
      break;
    case DWC_DDR4_3200W :
    case DWC_DDR4_3200AA :
    case DWC_DDR4_3200AC :
      timing->sg_tck_ps = 625;
      break;
    // DDR4 3DS
    case DWC_DDR4_1600J_3DS2B :
    case DWC_DDR4_1600K_3DS2B :
    case DWC_DDR4_1600L_3DS2B :
      timing->sg_tck_ps = 1250;
      break;
    case DWC_DDR4_1866L_3DS2B :
    case DWC_DDR4_1866M_3DS2B :
    case DWC_DDR4_1866N_3DS2B :
      #if (MEMORYMODELS > 0)
        timing->sg_tck_ps = 1071;
      #else
        timing->sg_tck_ps = 1072;
      #endif
      break;
    case DWC_DDR4_2133P_3DS2A :
    case DWC_DDR4_2133P_3DS3A :
    case DWC_DDR4_2133R_3DS4A :
      timing->sg_tck_ps = 938;
      break;
    case DWC_DDR4_2400P_3DS3B :
    case DWC_DDR4_2400T_3DS2A :
    case DWC_DDR4_2400U_3DS2A :
    case DWC_DDR4_2400U_3DS4A :
      timing->sg_tck_ps = 833;
      break;
    case DWC_DDR4_2666T_3DS3A :
    case DWC_DDR4_2666V_3DS3A :
    case DWC_DDR4_2666W_3DS4A :
      timing->sg_tck_ps = 750;
      break;
    case DWC_DDR4_3200W_3DS4A :
    case DWC_DDR4_3200AA_3DS4A :
    case DWC_DDR4_3200AC_3DS4A :
      timing->sg_tck_ps = 625;
      break;
    default:
      ERROR_MESSAGE(("Error: Ddr4.pm::set_clk_speed() - unknown speed grade, sg = %d\n", sg));
      break;
  }

  //TODO
  //// depending on the speed grade, set the tck value
  //if ( self->{dll_off_init} == 1 ) {
  //    // TODO: PHY doesn't support the PUB training if SDRAM clock period is greater than 4ns.
  //    //self->{tck} = 8000; // Minimum value of tCK is 8ns with DLL-off mode
  //    if (self->{TestName} == TEST_DDRC_PUB_TRAINING) {
  //        self->{tck} = 4000; // Maximum value of tCK is 4ns with DLL-off mode in running the PUB traininig scenario
  //    } else {
  //        self->{tck} = 8000; // Minimum value of tCK is 8ns with DLL-off mode
  //    }
  //} else {
  //    self->{tck} = timing->sg_tck_ps;
  //}
}

// --------------------------------------------------------------------------
// Name        : ddr4_set_default_timing_micron()
// Description : set all the default values for Micron model
// Returns     : none
// --------------------------------------------------------------------------
void ddr4_set_default_timing_micron(SubsysHdlr_t* hdlr, uint32_t p)
{
  TRACE();

  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[p];
  uint32_t sdram_width_bits = hdlr->spdData_m.sdram_width_bits;
  uint32_t sdram_capacity_mbits = hdlr->spdData_m.sdram_capacity_mbits;
  dwc_ddr4_speed_grade_e  sg = hdlr->spdData_m.ddr4_sg;
  uint32_t dll_off_init = DLL_OFF_MODE(p);
  uint8_t gd_en = hdlr->memCtrlr_m.ddr4_mr[p].mr3.geardown;
  uint32_t parity_en = hdlr->memCtrlr_m.ddr4_mr[p].mr5.parity_latency_mode;

  switch (timing->sg_tck_ps) {
  case 1250:  //DDR4 1600
    timing->ddr4_tcke_ps      = 5000;
    timing->ddr4_tpl_tck      = 4;
    timing->ddr4_wcl_tck      = 4;
    timing->ddr4_cal_tck      = 3;
    timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
    timing->ddr4_tccd_l_tck     = 5;
    timing->ddr4_tccd_dlr_tck   = 4;
    timing->ddr4_txsdll_tck     = 597;
    timing->ddr4_twtr_l_crc_dm_tck  = 5;
    timing->ddr4_twtr_s_crc_dm_tck  = 5;
    timing->ddr4_twtr_l_tck     = 6;
    timing->ddr4_twtr_s_tck     = 2;
    timing->ddr4_tcrc_alert_pw_tck  = 10;
    timing->ddr4_tcrc_alert_ps    = 13000;
    timing->ddr4_tpar_alert_pw_tck  = 96;
    timing->trcd_ps         = 15000;
    timing->trp_ps          = 12500;
    timing->trc_ps          = 50000;
    timing->ddr4_tras_min_ps    = 35000;
    break;

  case 1072:  //DDR4 1866
    timing->ddr4_tcke_ps      = 5000;
    timing->ddr4_tpl_tck      = 4;
    timing->ddr4_wcl_tck      = 5;
    timing->ddr4_cal_tck      = 4;
    timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
    timing->ddr4_tccd_l_tck     = 5;
    timing->ddr4_tccd_dlr_tck   = 4;
    timing->ddr4_txsdll_tck     = 597;
    timing->ddr4_twtr_l_tck     = 7;
    timing->ddr4_twtr_s_tck     = 3;
    timing->ddr4_twtr_l_crc_dm_tck  = 5;
    timing->ddr4_twtr_s_crc_dm_tck  = 5;
    timing->ddr4_tcrc_alert_pw_tck  = 10;
    timing->ddr4_tcrc_alert_ps    = 13000;
    timing->ddr4_tpar_alert_pw_tck  = 112;
    timing->trcd_ps         = 15000;
    timing->trp_ps          = 12850;
    timing->trc_ps          = 49000;
    timing->ddr4_tras_min_ps    = 34000;
    break;

  case 938:
    timing->ddr4_tcke_ps      = 5000;
    timing->ddr4_tpl_tck      = 4;
    timing->ddr4_wcl_tck      = 5;
    timing->ddr4_cal_tck      = 4;
    timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
    timing->ddr4_tccd_l_tck     = 6;
    timing->ddr4_tccd_dlr_tck   = 5;
    timing->ddr4_txsdll_tck     = 768;
    timing->ddr4_twtr_l_tck     = 8;
    timing->ddr4_twtr_s_tck     = 3;
    timing->ddr4_twtr_l_crc_dm_tck  = 5;
    timing->ddr4_twtr_s_crc_dm_tck  = 5;
    timing->ddr4_tcrc_alert_pw_tck  = 10;
    timing->ddr4_tcrc_alert_ps    = 13000;
    timing->ddr4_tpar_alert_pw_tck  = 128;
    timing->trcd_ps         = 13130;
    timing->trp_ps          = 13130;
    timing->trc_ps          = 46130;
    timing->ddr4_tras_min_ps    = 33000;
    break;

  case 833:
    timing->ddr4_tcke_ps      = 5000;
    timing->ddr4_tpl_tck      = 5;
    timing->ddr4_wcl_tck      = 5;
    timing->ddr4_cal_tck      = 5;
    timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
    timing->ddr4_tccd_l_tck     = 6;
    timing->ddr4_tccd_dlr_tck   = 5;
    timing->ddr4_txsdll_tck     = 768;
    // In case of SNPS VIP which speedbin is sg083/sg083R/sg083U, twtr_l_tck(twtr_s_tck) should be set to 10(4) instead of 9(3) to meet JEDEC, or the VIP checker will report error. See bug3221, comment49
    timing->ddr4_twtr_l_tck     = 9;
    timing->ddr4_twtr_s_tck     = 3;
    timing->ddr4_twtr_l_crc_dm_tck  = 5;
    timing->ddr4_twtr_s_crc_dm_tck  = 5;
    timing->ddr4_tcrc_alert_pw_tck  = 10;
    timing->ddr4_tcrc_alert_ps    = 13000;
    timing->ddr4_tpar_alert_pw_tck  = 144;
    timing->trcd_ps         = 12500;
    timing->trp_ps          = 12500;
    timing->trc_ps          = 44500;
    timing->ddr4_tras_min_ps    = 32000;
    break;

  case 750:
    timing->ddr4_tcke_ps      = 5000;
    timing->ddr4_tpl_tck      = 5;
    timing->ddr4_wcl_tck      = 5;  //Micron model (Datasheet) does not directly mention this value, but it can be inferred
                        //from other CRC and DM related parameters, such as tWTR_S_CRC_DM.
    timing->ddr4_cal_tck      = 5;
    timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps; // tMOD(min) + tCPDED(min) (Micron Datasheet)
    timing->ddr4_tccd_l_tck     = 7;
    timing->ddr4_tccd_dlr_tck   = 5;          // TBD
    timing->ddr4_txsdll_tck     = 768;
    timing->ddr4_twtr_l_tck     = 10;
    timing->ddr4_twtr_s_tck     = 4;
    timing->ddr4_twtr_l_crc_dm_tck  = 5;
    timing->ddr4_twtr_s_crc_dm_tck  = 6;
    timing->ddr4_tcrc_alert_pw_tck  = 10;
    timing->ddr4_tcrc_alert_ps    = 13000;
    timing->ddr4_tpar_alert_pw_tck  = 160;
    timing->trcd_ps         = 12500;
    timing->trp_ps          = 12500;
    timing->trc_ps          = 44500;
    timing->ddr4_tras_min_ps    = 32000;
    break;

  case 682:
    timing->ddr4_tcke_ps      = 5000;
    timing->ddr4_tpl_tck      = 6;  //TBD
    timing->ddr4_wcl_tck      = 6;  //TBD
    timing->ddr4_cal_tck      = 6;  //TBD
    timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps; // tMOD(min) + tCPDED(min) (Micron Datasheet)
    timing->ddr4_tccd_l_tck     = 8;
    timing->ddr4_tccd_dlr_tck   = 5;  // TBD
    timing->ddr4_txsdll_tck     = 768;
    timing->ddr4_twtr_l_tck     = 11;
    timing->ddr4_twtr_s_tck     = 4;
    timing->ddr4_twtr_l_crc_dm_tck  = 6;
    timing->ddr4_twtr_s_crc_dm_tck  = 6;
    timing->ddr4_tcrc_alert_pw_tck  = 10;
    timing->ddr4_tcrc_alert_ps    = 13000;
    timing->ddr4_tpar_alert_pw_tck  = 176;
    timing->trcd_ps         = 12500;
    timing->trp_ps          = 12575;
    timing->trc_ps          = 44500;
    timing->ddr4_tras_min_ps    = 32000;
    break;

  case 625:
    timing->ddr4_tcke_ps      = 5000;
    timing->ddr4_tpl_tck      = 6;    // Micron Datasheet
    timing->ddr4_wcl_tck      = 6;
    timing->ddr4_cal_tck      = 6;    // Micron Datasheet
    timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
    timing->ddr4_tccd_l_tck     = 8;    // Micron Model (Micron Datasheet: =max(5nCK, 5ns)=8)
    timing->ddr4_tccd_dlr_tck   = 5;    // TBD
    timing->ddr4_txsdll_tck     = 768;    // Micron Model (Micron Datasheet: =tDLLK(min)=1024)
    timing->ddr4_twtr_l_tck     = 12;   // max(4nCK, 7.5ns) (Micron Datasheet)
    timing->ddr4_twtr_s_tck     = 4;    // max(2nCK, 2.5ns) (Micron Datasheet)
    timing->ddr4_twtr_l_crc_dm_tck  = 6;    // The definition of this parameter is tWTR_L+max(5nCK, 3.75ns) (Micron Datasheet).
                          // But, in ddrc_cfg.sv, this is used as the delta between tWTR_L and tWTR_L_CRC_DM.
    timing->ddr4_twtr_s_crc_dm_tck  = 6;    // The definition of this parameter is tWTR_S+max(5nCK, 3.75ns) (Micron Datasheet).
                          // But, in ddrc_cfg.sv, this is used as the delta between tWTR_S and tWTR_S_CRC_DM
    timing->ddr4_tcrc_alert_pw_tck  = 10;   // CRC_ALERT_PWmax (Micron Datasheet)
    timing->ddr4_tcrc_alert_ps    = 13000;  // tCRC_ALERTmax (Micron Datasheet)
    timing->ddr4_tpar_alert_pw_tck  = 192;    // tPAR_Alert_PWmax (Micron Datasheet)
    timing->trcd_ps         = 12500;  // Micron Model
    timing->trp_ps          = 12500;  // Micron Model
    timing->trc_ps          = 44500;
    timing->ddr4_tras_min_ps    = 32000;
    break;

  default:
    ERROR_MESSAGE(("Error: Ddr4.pm::set_default_values_micron() - unknown speed grade, tck_ps = %d\n", timing->sg_tck_ps));
    break;
  }

  // in shareac mode, don't support CAL is ODD value
  // so, plus 1 if CAL value is ODD. (so far, cal can be 3 or 5)
  #ifdef UMCTL2_DUAL_DATA_CHANNEL
    if (timing->ddr4_cal_tck == 3) {
      timing->ddr4_cal_tck = 4;
    } else if (timing->ddr4_cal_tck == 5) {
      timing->ddr4_cal_tck = 6;
    }
  #endif

  if (gd_en) {
    if (timing->ddr4_cal_tck % 2 != 0) { timing->ddr4_cal_tck = timing->ddr4_cal_tck + 1; }
    if (timing->ddr4_tpl_tck % 2 != 0) { timing->ddr4_tpl_tck = timing->ddr4_tpl_tck + 1; }
  }

  if (parity_en == 0) {
    timing->ddr4_tpl_tck = 0;
  }

  if (sdram_width_bits == 16) {
    switch (timing->sg_tck_ps) {
    case 1250:  //DDR4 1600
      timing->trrd_l_tck = 6;
      timing->trrd_s_tck = 5;
      timing->ddr4_tfaw_ps = 35000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 1072:  //DDR4 1866
      timing->trrd_l_tck = 6;
      timing->trrd_s_tck = 5;
      timing->ddr4_tfaw_ps = 30000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 938:
      timing->trrd_l_tck = 7;
      timing->trrd_s_tck = 6;
      timing->ddr4_tfaw_ps = 30000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 833:
      timing->trrd_l_tck = 8;
      timing->trrd_s_tck = 7;
      timing->ddr4_tfaw_ps = 30000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 750:
      timing->trrd_l_tck = 9;
      timing->trrd_s_tck = 8;
      timing->ddr4_tfaw_ps = 30000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 682:
      timing->trrd_l_tck = 10;
      timing->trrd_s_tck = 8;
      timing->ddr4_tfaw_ps = 30000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 625:
      timing->trrd_l_tck = 11;     // max(4nCK, 6.4ns) Micron Datasheet
      timing->trrd_s_tck = 9;      // max(4nCK, 5.3ns) Micron Datasheet
      timing->ddr4_tfaw_ps = 30000;  // Max(28nCK, 30ns) Micron Datasheet
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    default:
      ERROR_MESSAGE(("Error: Ddr4.pm::set_default_values_micron() - unknown speed grade, tck_ps = %d\n", timing->sg_tck_ps));
      break;
    }

  } else if (sdram_width_bits == 8) {
    switch (timing->sg_tck_ps) {
    case 1250:
      timing->trrd_l_tck = 5;
      timing->trrd_s_tck = 4;
      timing->ddr4_tfaw_ps = 25000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 1072:
      timing->trrd_l_tck = 5;
      timing->trrd_s_tck = 4;
      timing->ddr4_tfaw_ps = 23000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 938:
      timing->trrd_l_tck = 6;
      timing->trrd_s_tck = 4;
      timing->ddr4_tfaw_ps = 21000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 833:
      timing->trrd_l_tck = 6;
      timing->trrd_s_tck = 4;
      timing->ddr4_tfaw_ps = 21000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 750:
      timing->trrd_l_tck = 7;
      timing->trrd_s_tck = 5;
      timing->ddr4_tfaw_ps = 21000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 682:
      timing->trrd_l_tck = 8;
      timing->trrd_s_tck = 5;
      timing->ddr4_tfaw_ps = 21000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
    break;

    case 625:
      timing->trrd_l_tck = 8;      // max(4nCK, 4.9ns) Micron Datasheet
      timing->trrd_s_tck = 6; // 3300ps Micron Model (Open) (This is discrepant with Micron Datasheet (max(4nCK, 2.3ns).)
      timing->ddr4_tfaw_ps = 21000;  // Max(20nCK, 21ns) Micron Datasheet
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
    break;

    default:
      ERROR_MESSAGE(("Error: Ddr4.pm::set_default_values_micron() - unknown speed grade, tck_ps = %d\n", timing->sg_tck_ps));
      break;
    }

  } else if (sdram_width_bits == 4) {
    switch (timing->sg_tck_ps) {
    case 1250:
      timing->trrd_l_tck = 5;
      timing->trrd_s_tck = 4;
      timing->ddr4_tfaw_ps = 20000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 1072:
      timing->trrd_l_tck = 5;
      timing->trrd_s_tck = 4;
      timing->ddr4_tfaw_ps = 17000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 938:
      timing->trrd_l_tck = 6;
      timing->trrd_s_tck = 4;
      timing->ddr4_tfaw_ps = 15000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;\
      break;

    case 833:
      timing->trrd_l_tck = 6;
      timing->trrd_s_tck = 4;
      timing->ddr4_tfaw_ps = 13000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 750:
      timing->trrd_l_tck = 7;
      timing->trrd_s_tck = 5;
      timing->ddr4_tfaw_ps = 13000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 682:
      timing->trrd_l_tck = 8;
      timing->trrd_s_tck = 5;
      timing->ddr4_tfaw_ps = 13000;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    case 625:
      timing->trrd_l_tck = 8;      // max(4nCK, 4.9ns) Micron Datasheet
      timing->trrd_s_tck = 6;     // 3300ps Micron Model (Open) (This is discrepant with Micron Datasheet (max(4nCK, 2.3ns).)
      timing->ddr4_tfaw_ps = 13000; // Max(16nCK, 13ns) Micron Datasheet
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_tfaw_dlr_tck = 16;
      break;

    default:
      ERROR_MESSAGE(("Error: Ddr4.pm::set_default_values_micron() - unknown speed grade, tck_ps = %d\n", timing->sg_tck_ps));
      break;

    }
  } else {
    ERROR_MESSAGE(("Error: Ddr4.pm::set_default_values_micron() - unknown bus width, bus_width = %d\n", sdram_width_bits));
  }

  // Round up t_ccd_l if gd_en=1
  if (gd_en && (timing->ddr4_tccd_l_tck % 2) != 0) {
    timing->ddr4_tccd_l_tck = timing->ddr4_tccd_l_tck + 1;
  }

  // Round up t_ccd_dlr if gd_en=1
  if (gd_en && (timing->ddr4_tccd_dlr_tck % 2) != 0) {
    timing->ddr4_tccd_dlr_tck = timing->ddr4_tccd_dlr_tck + 1;
  }

  // for tccd_s, default to 4 clks
  timing->ddr4_tccd_s_tck = 4;


  timing->ddr4_tmrd_tck = 8;


  // for tmod, default TMOD_TCK is 24 clocks, so adjust the TMOD to this value
  timing->ddr4_tmod_ps = 24 * tck_ps;  // max(24nCK, 15ns) (Micron Datasheet)

  // tISmin + tIHmin
  timing->ddr4_tmpx_s_tck = 2;  // tISmin + tIHmin (Micron Datasheet)
              // tIS(base)min = 115 - 60[ps], tIS(Vref)min = 215 - 150[ps], tIH(base)min = 140 - 85[ps], tIH(Vref)min = 215 - 150[ps]
              // Not clear how 2 was derived.

  // for tMPX_LH, default to 12000 ps
  timing->ddr4_tmpx_lh_ps = 12000;  // tMPX_LHmin = 12 [ns] (Micron Datasheet)

  // for trtp, default to 7500 ps
  // for sg above 2400, tRTP is 6000 ps so need to change
  timing->ddr4_trtp_ps = 7500;  // max(4nCK, 7.5ns) (Micron Datasheet)

  // for twr, default to 15000 ps
  timing->ddr4_twr_ps = 15000;  // (Micron Datasheet)

  // set the following in terms of ps
  timing->ddr4_tras_max_ps = 70200000;  // 9 * tREFI, tREFI = 7.8 [ns] (0 C <= T <= 85 C) (Micron Datasheet)

  // set the following in terms of ps
  if (sdram_capacity_mbits == 2048) {
    timing->ddr4_trfc_min_ps = 160000;  // Micron Model
    timing->ddr4_trfc_min2_ps = 110000;  // Micron Model
    timing->ddr4_trfc_min4_ps = 90000;  // Micron Model
    timing->ddr4_trfc_dlr_ps = (uint32_t)((timing->ddr4_trfc_min_ps + 2) / 3);  // Micron Model
    timing->ddr4_trfc_dlr2_ps = (uint32_t)((timing->ddr4_trfc_min2_ps + 2) / 3); // Micron Model
    timing->ddr4_trfc_dlr4_ps = (uint32_t)((timing->ddr4_trfc_min4_ps + 2) / 3); // Micron Model
  }
  if (sdram_capacity_mbits == 4096) {
    timing->ddr4_trfc_min_ps = 260000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_min2_ps = 160000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_min4_ps = 110000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_dlr_ps = (uint32_t)((timing->ddr4_trfc_min_ps + 2) / 3);  // Micron Model
    timing->ddr4_trfc_dlr2_ps = (uint32_t)((timing->ddr4_trfc_min2_ps + 2) / 3); // Micron Model
    timing->ddr4_trfc_dlr4_ps = (uint32_t)((timing->ddr4_trfc_min4_ps + 2) / 3); // Micron Model
  }
  if (sdram_capacity_mbits == 8192) {
    timing->ddr4_trfc_min_ps = 350000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_min2_ps = 260000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_min4_ps = 160000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_dlr_ps = (uint32_t)((timing->ddr4_trfc_min_ps + 2) / 3);  // Micron Model
    timing->ddr4_trfc_dlr2_ps = (uint32_t)((timing->ddr4_trfc_min2_ps + 2) / 3); // Micron Model
    timing->ddr4_trfc_dlr4_ps = (uint32_t)((timing->ddr4_trfc_min4_ps + 2) / 3); // Micron Model
  }
  if (sdram_capacity_mbits == 16384) {
    timing->ddr4_trfc_min_ps = 550000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_min2_ps = 405000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_min4_ps = 250000;  // Micron Model, Micron Datasheet
    timing->ddr4_trfc_dlr_ps = (uint32_t)((timing->ddr4_trfc_min_ps + 2) / 3);  // Micron Model
    timing->ddr4_trfc_dlr2_ps = (uint32_t)((timing->ddr4_trfc_min2_ps + 2) / 3); // Micron Model
    timing->ddr4_trfc_dlr4_ps = (uint32_t)((timing->ddr4_trfc_min4_ps + 2) / 3); // Micron Model
  }
  timing->ddr4_trfc_max_ps = 70200000;
  timing->trpa_ps = timing->trp_ps + tck_ps;

  // set the following dependent on other params
  // tREFI = 7.8us = 7800000ps in all speed grades
  //timing->ddr4_trefi_ps = (7800000 / (timing->tck_ps * 32));
  //timing->ddr4_trefi_ps = (timing->ddr4_trefi_ps*timing->tck_ps);
  //timing->ddr4_trefi_ps = (uint32_t)(timing->ddr4_trefi_ps);
  timing->ddr4_trefi_ps = (7800000 / 32);

  // set the following in terms of clks
  timing->ddr4_tzqinit_tck = 1024;  // Micron Datasheet
  timing->ddr4_tzqoper_tck = 512;   // Micron Datasheet
  timing->ddr4_tzqcs_tck = 128;   // Micron Datasheet

  // set the tXP in terms of ps --- max(4nCK, 6ns) (Micron Datasheet)
  if (tck_ps > 1500) {
    timing->ddr4_txp_ps = tck_ps * 4;
  } else {
    timing->ddr4_txp_ps = 6000;
  }

  // set the tXPDLL in terms of ps
  timing->ddr4_txpdll_ps = 24000;  // Micron Model

  // set the CAS Latency and the CAS Write Latency (dependent on the speed grade)
  timing->ddr4_tcl_tck = ddr4_get_cas_latency(p,hdlr,gd_en,dll_off_init);
  timing->ddr4_tcl_rdbi_tck = ddr4_get_cas_latency_rdbi(p,hdlr,gd_en,dll_off_init);
  timing->ddr4_tcwl_1st_set_tck = ddr4_get_CWL_1st_set(p,hdlr,dll_off_init);
  timing->ddr4_tcwl_2nd_set_tck = ddr4_get_CWL_2nd_set(p,hdlr,dll_off_init);

  // geardown
  timing->ddr4_tsync_gear_tck = timing->ddr4_tmod_ps / tck_ps + 4;
  timing->ddr4_tcmd_gear_tck = timing->ddr4_tmod_ps / tck_ps;
  timing->ddr4_tgear_setup_tck = 2;
  timing->ddr4_tgear_hold_tck = 2;

  // for twr_crc_dm
  timing->ddr4_twr_crc_dm_tck = timing->ddr4_wcl_tck; // The definition of this parameter is tWR + WCL,
                            // where WCL=max(NnCK, 3.75ns) (N=4 for 1600, N=5 for higher speeds (Micron Datasheet))
                            // But, in ddrc_cfg.sv, this is treated as only WCL portion.

  // CA parity timing
  timing->ddr4_tpar_unknown_ps = timing->ddr4_tpl_tck * tck_ps;  // PL (Micron Datasheet)
  timing->ddr4_tpar_alert_on_ps = (timing->ddr4_tpl_tck * tck_ps) + 6000;  // PL + 6ns (Micron Datasheet)

  // Update timing parameters if DLL-off mode is enabled during SDRAM initialization.
  if (dll_off_init) {
    timing->trrd_l_tck = 4;
    timing->trrd_s_tck = 4;
    timing->ddr4_trrd_dlr_tck = 4;
    timing->ddr4_twtr_l_tck = 4;
    timing->ddr4_twtr_s_tck = 2;
    timing->ddr4_tcke_ps = tck_ps * 3;
    timing->ddr4_trtp_ps = tck_ps * 4;
  }

  // Micron model's tDQSCK (DLL-off) value is 5.8ns.
  timing->ddr4_tdqsck_dll_off_ps = 5800;  // Micron Model

  timing->ddr4_tstab_ps = 5000000; // JEDEC value 5us
}

// --------------------------------------------------------------------------
// Name        : ddr4_set_default_timing_vip()
// Description : set all the default values for SNPS VIP
// Returns     : none
// --------------------------------------------------------------------------
void ddr4_set_default_timing_vip(SubsysHdlr_t* hdlr, uint32_t p)
{
  TRACE();

  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[p];
  uint32_t sdram_width_bits = hdlr->spdData_m.sdram_width_bits;
  uint32_t sdram_capacity_mbits = hdlr->spdData_m.sdram_capacity_mbits;
  dwc_ddr4_speed_grade_e sg = hdlr->spdData_m.ddr4_sg;
  uint32_t dll_off_init = DLL_OFF_MODE(p);
  uint8_t gd_en = hdlr->memCtrlr_m.ddr4_mr[p].mr3.geardown;
  uint32_t ca_parity_en = hdlr->memCtrlr_m.ddr4_mr[p].mr5.parity_latency_mode;

  if (dll_off_init == 1) {
    timing->ddr4_tcke_ps      = tck_ps * 3;
    timing->ddr4_tpl_tck      = 4;
    timing->ddr4_wcl_tck      = 4;
    timing->ddr4_cal_tck      = 3;
    timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
    timing->ddr4_tccd_l_tck     = 4;
    timing->ddr4_tccd_dlr_tck   = 4;
    timing->ddr4_txsdll_tck     = 597;
    timing->ddr4_twtr_l_crc_dm_tck  = 4;
    timing->ddr4_twtr_s_crc_dm_tck  = 4;
    timing->ddr4_twtr_l_tck     = 4;
    timing->ddr4_twtr_s_tck     = 2;
    timing->ddr4_tcrc_alert_pw_tck  = 10;
    timing->ddr4_tpar_alert_pw_tck  = 96;
  } else {
    switch (tck_ps) {
    case 1250 : // DDR4-1600
      timing->ddr4_tcke_ps      = 5000;
      timing->ddr4_tpl_tck      = 4;
      timing->ddr4_wcl_tck      = 4;
      timing->ddr4_cal_tck      = 3;
      timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
      timing->ddr4_tccd_l_tck     = 5;
      timing->ddr4_tccd_dlr_tck   = 4;
      timing->ddr4_txsdll_tck     = 597;
      timing->ddr4_twtr_l_crc_dm_tck  = 4;
      timing->ddr4_twtr_s_crc_dm_tck  = 4;
      timing->ddr4_twtr_l_tck     = 6;
      timing->ddr4_twtr_s_tck     = 2;
      timing->ddr4_tcrc_alert_pw_tck  = 10;
      timing->ddr4_tpar_alert_pw_tck  = 96;
      break;
    case 1071 ... 1072 :  // DDR4-1866
      timing->ddr4_tcke_ps      = 5000;
      timing->ddr4_tpl_tck      = 4;
      timing->ddr4_wcl_tck      = 5;
      timing->ddr4_cal_tck      = 4;
      timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
      timing->ddr4_tccd_l_tck     = 5;
      timing->ddr4_tccd_dlr_tck   = 4;
      timing->ddr4_txsdll_tck     = 597;
      timing->ddr4_twtr_l_tck     = 8;
      timing->ddr4_twtr_s_tck     = 3;
      timing->ddr4_twtr_l_crc_dm_tck  = 5;
      timing->ddr4_twtr_s_crc_dm_tck  = 5;
      timing->ddr4_tcrc_alert_pw_tck  = 10;
      timing->ddr4_tpar_alert_pw_tck  = 112;
      break;

    case 938: // DDR4-2133
      timing->ddr4_tcke_ps      = 5000;
      timing->ddr4_tpl_tck      = 4;
      timing->ddr4_wcl_tck      = 5;
      timing->ddr4_cal_tck      = 4;
      timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
      timing->ddr4_tccd_l_tck     = 6;
      timing->ddr4_tccd_dlr_tck   = 5;
      timing->ddr4_txsdll_tck     = 768;
      timing->ddr4_twtr_l_tck     = 8;
      timing->ddr4_twtr_s_tck     = 3;
      timing->ddr4_twtr_l_crc_dm_tck  = 5;
      timing->ddr4_twtr_s_crc_dm_tck  = 5;
      timing->ddr4_tcrc_alert_pw_tck  = 10;
      timing->ddr4_tpar_alert_pw_tck  = 128;
      break;

    case 833 :  // DDR4-2400
      timing->ddr4_tcke_ps      = 5000;
      timing->ddr4_tpl_tck      = 5;
      timing->ddr4_wcl_tck      = 5;
      timing->ddr4_cal_tck      = 5;
      timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps;  // tMOD(min) + tCPDED(min) (Micron Datasheet)
      timing->ddr4_tccd_l_tck     = 6;
      timing->ddr4_tccd_dlr_tck   = 5;
      timing->ddr4_txsdll_tck     = 768;
      // In case of SNPS VIP which speedbin is sg083/sg083R/sg083T/sg083U, twtr_l_tck(twtr_s_tck) should be set to 10(4) instead of 9(3) to meet JEDEC, or the VIP checker will report error. See bug3221, comment49
      timing->ddr4_twtr_l_tck     = 10;
      timing->ddr4_twtr_s_tck     = 4;
      timing->ddr4_twtr_l_crc_dm_tck  = 5;
      timing->ddr4_twtr_s_crc_dm_tck  = 5;
      timing->ddr4_tcrc_alert_pw_tck  = 10;
      timing->ddr4_tpar_alert_pw_tck  = 144;
      break;

    case 750 : // DDR4-2666
      timing->ddr4_tcke_ps      = 5000;
      timing->ddr4_tpl_tck      = 5;
      timing->ddr4_wcl_tck      = 6; // use value same with SNPS VIP
      timing->ddr4_cal_tck      = 5;
      timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps; // tMOD(min) + tCPDED(min) (Micron Datasheet)
      timing->ddr4_tccd_l_tck     = 7;
      timing->ddr4_tccd_dlr_tck   = 5; // TODO. TBD. This has not been defined in JEDEC v095c1f
      timing->ddr4_txsdll_tck     = 854;    // Jedec JESD79-4B
      timing->ddr4_twtr_l_tck     = 10;
      timing->ddr4_twtr_s_tck     = 4;
      timing->ddr4_twtr_l_crc_dm_tck  = 5;
      timing->ddr4_twtr_s_crc_dm_tck  = 5;
      timing->ddr4_tcrc_alert_pw_tck  = 10;
      timing->ddr4_tpar_alert_pw_tck  = 160;
      break;

    case 682:
      //values taken from Micron model; JEDEC spec not yet available
      timing->ddr4_tcke_ps      = 5000;
      timing->ddr4_tpl_tck      = 6; //TBD
      timing->ddr4_wcl_tck      = 6; //TBD
      timing->ddr4_cal_tck      = 6; //TBD
      timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps; // tMOD(min) + tCPDED(min) (Micron Datasheet)
      timing->ddr4_tccd_l_tck     = 8;
      timing->ddr4_tccd_dlr_tck   = 5; //TBD
      timing->ddr4_txsdll_tck     = 940;    // Jedec JESD79-4B
      timing->ddr4_twtr_l_tck     = 11;
      timing->ddr4_twtr_s_tck     = 4;
      timing->ddr4_twtr_l_crc_dm_tck  = 6;
      timing->ddr4_twtr_s_crc_dm_tck  = 6;
      timing->ddr4_tcrc_alert_pw_tck  = 10;
      timing->ddr4_tpar_alert_pw_tck  = 176;
      break;

    case 625 :  // DDR4-3200
      timing->ddr4_tcke_ps      = 5000;
      timing->ddr4_tpl_tck      = 6;
      timing->ddr4_wcl_tck      = 6; // use value same with SNPS VIP
      timing->ddr4_cal_tck      = 6; // Micrion Datasheet
      timing->ddr4_tckmpe_ps      = (24 + 4) * tck_ps; // tMOD(min) + tCPDED(min) (Micron Datasheet)
      timing->ddr4_tccd_l_tck     = 8;          // Micron Model (Micron Datasheet: =max(5nCK, 5ns)=8)
      timing->ddr4_tccd_dlr_tck   = 5; // TODO. TBD. This has not been defined in JEDEC v095c1f
      timing->ddr4_txsdll_tck     = 1024;       // Jedec JESD79-4B
      timing->ddr4_twtr_l_tck     = 12;         // max(4nCK, 7.5ns) (Micron Datasheet)
      timing->ddr4_twtr_s_tck     = 4;          // max(2nCK, 2.5ns) (Micron Datasheet)
      timing->ddr4_twtr_l_crc_dm_tck  = 6;       // The definition of this parameter is tWTR_L+max(5nCK, 3.75ns) (Micron Datasheet).
                            // But, in ddrc_cfg.sv, this is used as the delta between tWTR_L and tWTR_L_CRC_DM.
      timing->ddr4_twtr_s_crc_dm_tck  = 6;  // The definition of this parameter is tWTR_S+max(5nCK, 3.75ns) (Micron Datasheet).
                          // But, in ddrc_cfg.sv, this is used as the delta between tWTR_S and tWTR_S_CRC_DM
      timing->ddr4_tcrc_alert_pw_tck  = 10;      // CRC_ALERT_PWmax (Micron Datasheet)
      timing->ddr4_tpar_alert_pw_tck  = 192;     // tPAR_Alert_PWmax (Micron Datasheet)
      break;

    default :                                // DLL-off mode
      ERROR_MESSAGE(("Error: set_default_values_vip() - unknown speed grade, tck_ps = %d\n", tck_ps));
      break;
    }
  }

  switch (sg) {
  case DWC_DDR4_1600J:
    timing->trcd_ps       = 12500;
    timing->trp_ps        = 12500;
    timing->trc_ps        = 47500;
    timing->ddr4_tras_min_ps  = 35000;
    break;
  case DWC_DDR4_1600K :
    timing->trcd_ps       = 13750;
    timing->trp_ps        = 13750;
    timing->trc_ps        = 48750;
    timing->ddr4_tras_min_ps  = 35000;
    break;
  case DWC_DDR4_1600L :
    timing->trcd_ps       = 15000;
    timing->trc_ps        = 50000;
    timing->ddr4_tras_min_ps  = 35000;
    timing->trp_ps        = 15000;
    break;
  case DWC_DDR4_1866L:
    timing->trcd_ps       = 12850;
    timing->trp_ps        = 12850;
    timing->trc_ps        = 46850;
    timing->ddr4_tras_min_ps  = 34000;
    break;
  case DWC_DDR4_1866M :
    timing->trcd_ps       = 13920;
    timing->trp_ps        = 13920;
    timing->trc_ps        = 47920;
    timing->ddr4_tras_min_ps  = 34000;
    break;
  case DWC_DDR4_1866N :
    timing->trcd_ps       = 15000;
    timing->trc_ps        = 49000;
    timing->ddr4_tras_min_ps  = 34000;
    timing->trp_ps        = 15000;
    break;
  case DWC_DDR4_2133N :
    timing->trcd_ps       = 13130;
    timing->trp_ps        = 13130;
    timing->trc_ps        = 46130;
    timing->ddr4_tras_min_ps  = 33000;
    break;
  case DWC_DDR4_2133P :
    timing->trcd_ps       = 14060;
    timing->trp_ps        = 14060;
    timing->trc_ps        = 47060;
    timing->ddr4_tras_min_ps  = 33000;
    break;
  case DWC_DDR4_2133R :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 15000;
    timing->trc_ps        = 48000;
    timing->ddr4_tras_min_ps  = 33000;
    break;
  case DWC_DDR4_2400P:
    timing->trcd_ps       = 12500;
    timing->trp_ps        = 12500;
    timing->trc_ps        = 44500;
    timing->ddr4_tras_min_ps  = 32000;
    break;

  case DWC_DDR4_2400R :
    timing->trcd_ps       = 13320;
    timing->trp_ps        = 13320;
    timing->trc_ps        = 45320;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2400T :
    timing->trcd_ps       = 14160;
    timing->trp_ps        = 14160;
    timing->trc_ps        = 46160;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2400U :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 15000;
    timing->trc_ps        = 47000;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2666T :
    timing->trcd_ps       = 12750;
    timing->trp_ps        = 12750;
    timing->trc_ps        = 44750;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2666U :
    timing->trcd_ps       = 13500;
    timing->trp_ps        = 13500;
    timing->trc_ps        = 45500;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2666V :
    timing->trcd_ps       = 14250;
    timing->trp_ps        = 14250;
    timing->trc_ps        = 46250;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2666W :
    timing->trcd_ps       = 15000; // Micrion Datasheet, Standard Spec Proposal
    timing->trp_ps        = 15000; // Micrion Datasheet, Standard Spec Proposal
    timing->trc_ps        = 47000;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2933V :
    timing->trcd_ps       = 12960;
    timing->trp_ps        = 12960;// use the value same with VIP L-2016.09
    timing->trc_ps        = 44960;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2933W :
    timing->trcd_ps       = 13640;
    timing->trp_ps        = 13640;// use the value same with VIP L-2016.09
    timing->trc_ps        = 45640;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2933Y :
    timing->trcd_ps       = 14320;
    timing->trp_ps        = 14320;// use the value same with VIP L-2016.09
    timing->trc_ps        = 46320;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_2933AA :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 15000;// use the value same with VIP L-2016.09
    timing->trc_ps        = 47000;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_3200W :
    timing->trcd_ps       = 12500; // Micrion Datasheet, Standard Spec Proposal
    timing->trp_ps        = 12500; // Micrion Datasheet, Standard Spec Proposal
    timing->trc_ps        = 44500;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_3200AA :
    timing->trcd_ps       = 13750; // Micrion Datasheet, Standard Spec Proposal
    timing->trp_ps        = 13750; // Micrion Datasheet, Standard Spec Proposal
    timing->trc_ps        = 45750;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  case DWC_DDR4_3200AC :
    timing->trcd_ps       = 15000; // Micrion Datasheet, Standard Spec Proposal
    timing->trp_ps        = 15000; // Micrion Datasheet, Standard Spec Proposal
    timing->trc_ps        = 47000;
    timing->ddr4_tras_min_ps  = 32000;
    break;
  // DDR4 3DS
  case DWC_DDR4_1600J_3DS2B :
    timing->trcd_ps       = 13750;
    timing->trp_ps        = 12500;
    timing->ddr4_tras_min_ps  = 35000;
    timing->trc_ps        = 47500;
    break;
  case DWC_DDR4_1600K_3DS2B :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 13750;
    timing->ddr4_tras_min_ps  = 35000;
    timing->trc_ps        = 48750;
    break;
  case DWC_DDR4_1600L_3DS2B :
    timing->trcd_ps       = 16250;
    timing->trp_ps        = 15000;
    timing->ddr4_tras_min_ps  = 35000;
    timing->trc_ps        = 50000;
    break;
  case DWC_DDR4_1866L_3DS2B :
    timing->trcd_ps       = 13920;
    timing->trp_ps        = 12850;
    timing->ddr4_tras_min_ps  = 34000;
    timing->trc_ps        = 46850;
    break;
  case DWC_DDR4_1866M_3DS2B :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 13920;
    timing->ddr4_tras_min_ps  = 34000;
    timing->trc_ps        = 47920;
    break;
  case DWC_DDR4_1866N_3DS2B :
    timing->trcd_ps       = 16070;
    timing->trp_ps        = 15000;
    timing->ddr4_tras_min_ps  = 34000;
    timing->trc_ps        = 49000;
    break;
  case DWC_DDR4_2133P_3DS2A :
    timing->trcd_ps       = 14060;
    // timing->trp_ps     = 13750; // 13750 is optional according to 3DS JEDEC
    timing->trp_ps        = 14060;
    timing->ddr4_tras_min_ps  = 33000;
    timing->trc_ps        = 47060;
    break;
  case DWC_DDR4_2133P_3DS3A :
    timing->trcd_ps       = 14060;
    timing->trp_ps        = 14060;
    timing->ddr4_tras_min_ps  = 33000;
    timing->trc_ps        = 47060;
    break;
  case DWC_DDR4_2133R_3DS4A :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 15000;
    timing->ddr4_tras_min_ps  = 33000;
    timing->trc_ps        = 48000;
    break;
  case DWC_DDR4_2400P_3DS3B :
    timing->trcd_ps       = 13330;
    timing->trp_ps        = 12500;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 44500;
    break;
  case DWC_DDR4_2400T_3DS2A :
    timing->trcd_ps       = 14160;
    timing->trp_ps        = 14160;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 46160;
    break;
  case DWC_DDR4_2400U_3DS2A :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 15000;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 47000;
    break;
  case DWC_DDR4_2400U_3DS4A :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 15000;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 47000;
    break;
  case DWC_DDR4_2666T_3DS3A :
    timing->trcd_ps       = 12750;
    timing->trp_ps        = 12750;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 44750;
    break;
  case DWC_DDR4_2666V_3DS3A :
    timing->trcd_ps       = 14250;
    timing->trp_ps        = 14250;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 46250;
    break;
  case DWC_DDR4_2666W_3DS4A :
    timing->trcd_ps       = 15000;
    timing->trp_ps        = 15000;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 47000;
    break;
  case DWC_DDR4_3200W_3DS4A :
    timing->trcd_ps       = 12500;
    timing->trp_ps        = 12500;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 44500;
    break;
  case DWC_DDR4_3200AA_3DS4A :
    timing->trcd_ps       = 13270;
    timing->trp_ps        = 13270;
    timing->ddr4_tras_min_ps  = 32000;
    timing->trc_ps        = 45270;
    break;
  case DWC_DDR4_3200AC_3DS4A :
    timing->trcd_ps = 15000;
    timing->trp_ps = 15000;
    timing->ddr4_tras_min_ps = 32000;
    timing->trc_ps = 47000;
    break;
  default :
    ERROR_MESSAGE(("Error: Ddr4.pm::set_default_values_vip() - unknown speed grade, sg = %d\n", sg));
    break;
  }

  // in shareac mode, don't support CAL is ODD value
  // so, plus 1 if CAL value is ODD. (so far, cal can be 3 or 5)
  #ifdef UMCTL2_DUAL_DATA_CHANNEL
    if ( timing->ddr4_cal_tck == 3) {
      timing->ddr4_cal_tck = 4;
    } else if ( timing->ddr4_cal_tck == 5) {
      timing->ddr4_cal_tck = 6;
    }
  #endif

  if (gd_en == 1) {
    if (timing->ddr4_cal_tck%2!=0) { timing->ddr4_cal_tck = timing->ddr4_cal_tck+1;}
    if (timing->ddr4_tpl_tck%2!=0) { timing->ddr4_tpl_tck = timing->ddr4_tpl_tck+1;}
  }


  if ( ca_parity_en == 0) {
    timing->ddr4_tpl_tck = 0;
  }

    if (sdram_width_bits == 16) {
      if (dll_off_init == 1) {
        timing->trrd_l_tck    = 4;
        timing->trrd_s_tck    = 4;
      } else {
        switch (tck_ps) {
        case 1250 : // DDR4-1600
          timing->trrd_l_tck    = 6;
          timing->trrd_s_tck    = 5;
          break;
        case 1071 ... 1072 :  // DDR4-1866
          timing->trrd_l_tck    = 6;
          timing->trrd_s_tck    = 5;
          break;
        case 938 :  // DDR4-2133
          timing->trrd_l_tck    = 7;
          timing->trrd_s_tck    = 6;
          break;
        case 833 : // DDR4-2400
          timing->trrd_l_tck    = 8;
          timing->trrd_s_tck    = 7;
          break;
        case 750 : // DDR4-2666
          timing->trrd_l_tck    = 9;
          timing->trrd_s_tck    = 8;
          break;
        case 682 :  // DDR4-2933
          timing->trrd_l_tck    = 10;
          timing->trrd_s_tck    = 8;
          break;
        case 625: // DDR4-3200
          timing->trrd_l_tck    = 11;     // max(4nCK, 6.4ns) Micron Datasheet
          timing->trrd_s_tck    = 9;      // max(4nCK, 5.3ns) Micron Datasheet
          break;
        default :
          ERROR_MESSAGE(("Error: set_default_values_vip() - unknown speed grade, tck = %d\n", tck_ps));
        break;
      } // end if x16
      }
    } else if (sdram_width_bits == 8) {
      if (dll_off_init == 1) {
        timing->trrd_l_tck      = 4;
        timing->trrd_s_tck      = 4;
        timing->ddr4_trrd_dlr_tck = 4;
        timing->ddr4_tfaw_dlr_tck = 16;
      } else {
        switch(tck_ps) {
        case 1250 :  // DDR4-1600
          timing->trrd_l_tck      = 5;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 1071 ... 1072 :  // DDR4-1866
          timing->trrd_l_tck      = 5;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 938  :  // DDR4-2133
          timing->trrd_l_tck      = 6;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 833 :   // DDR4-2400
          timing->trrd_l_tck      = 6;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 750 :   // DDR4-2666
          timing->trrd_l_tck      = 7;
          timing->trrd_s_tck      = 4; // max(4nCK,3 ns) (JESD79-4A_r0 Table 131)
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 682 :    // DDR4-2933
          timing->trrd_l_tck      = 8;
          timing->trrd_s_tck      = 5;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 625 :   // DDR4-3200
          timing->trrd_l_tck      = 8;      // max(4nCK, 4.9ns) Micron Datasheet
          timing->trrd_s_tck      = 4; // max(4nCK,2.5 ns) (JESD79-4A_r0 Table 131)
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        default:
          ERROR_MESSAGE(("Error: set_default_values_vip() - unknown speed grade, tck = %d\n", tck_ps));
          break;
        }
      }

    } else if (sdram_width_bits == 4) {
      if (dll_off_init == 1) {
          timing->trrd_l_tck      = 4;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
      } else {
        switch (tck_ps) {
        case 1250 :  // DDR4-1600
          timing->trrd_l_tck      = 5;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 1071 ... 1072:  // DDR4-1866
          timing->trrd_l_tck      = 5;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 938:   // DDR4-2133
          timing->trrd_l_tck      = 6;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 833 :   // DDR4-2400
          timing->trrd_l_tck      = 6;
          timing->trrd_s_tck      = 4;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 750 :   // DDR4-2666
          timing->trrd_l_tck      = 7;
          timing->trrd_s_tck      = 4; // max(4nCK, 3 ns) (JESD79-4A_r0 Table 131)
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 682 :    // DDR4-2933
          timing->trrd_l_tck      = 8;
          timing->trrd_s_tck      = 5;
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;
        case 625 :   // DDR4-3200
          timing->trrd_l_tck      = 8;      // max(4nCK, 4.9ns) Micron Datasheet
          timing->trrd_s_tck      = 4; // max(4nCK, 2.5 ns) (JESD79-4A_r0 Table 131)
          timing->ddr4_trrd_dlr_tck = 4;
          timing->ddr4_tfaw_dlr_tck = 16;
          break;

        default:
          ERROR_MESSAGE(("Error: Ddr4.pm::set_default_values_vip() - unknown speed grade, tck = %d\n", tck_ps));
          break;
        }
      }
    } else {
      ERROR_MESSAGE(("Error: Ddr4.pm::set_default_values_vip() - unknown bus width, bus_width = %d\n", sdram_width_bits));
    }

    //Calculate tFAW
    if (dll_off_init == 1) {
      timing->ddr4_tfaw_ps = (sdram_width_bits == 16) ? 35000 :(sdram_width_bits == 8) ? 25000 : 20000;
    } else {
      switch (timing->sg_tck_ps) {
      case 1250 :   // DDR4-1600
        timing->ddr4_tfaw_ps = (sdram_width_bits == 16) ? 35000 :(sdram_width_bits == 8) ? 25000 : 20000;
        break;
      case 1071 ... 1072 :  // DDR4-1866
        timing->ddr4_tfaw_ps = (sdram_width_bits == 16) ? 30000 :(sdram_width_bits == 8) ? 23000 : 17000;
        break;
      case 938 :  // DDR4-2133
        timing->ddr4_tfaw_ps = (sdram_width_bits == 16) ? 30000 :(sdram_width_bits == 8) ? 21000 : 15000;
        break;
      case 833 :  // DDR4-2400
        timing->ddr4_tfaw_ps = (sdram_width_bits == 16) ? 30000 :(sdram_width_bits == 8) ? 21000 : 13000;
        break;
      case 750 :  // DDR4-2666
        timing->ddr4_tfaw_ps = (sdram_width_bits == 16) ? 30000 :(sdram_width_bits == 8) ? 21000 : 12000; // max(16nCK, 12ns) (JESD79-4A_r0 Table 131)
        break;
      case 682 :  // DDR4-2933
        timing->ddr4_tfaw_ps = (sdram_width_bits == 16) ? 30000 :(sdram_width_bits == 8) ? 21000 : 13000;
        break;
      case 625 :  // DDR4-3200
        timing->ddr4_tfaw_ps = (sdram_width_bits == 16) ? 30000 :(sdram_width_bits == 8) ? 21000 : 10000; // max(16nCK, 10ns) (JESD79-4A_r0 Table 131)
        break;
      default:
        ERROR_MESSAGE(("Error: set_default_values_vip() - unknown sg_tck_ps = %0d\n",timing->sg_tck_ps));
        break;
      }
    }

    // Round up t_ccd_l if gd_en=1
    if ((gd_en == 1) && ((timing->ddr4_tccd_l_tck%2)!=0)) {
      timing->ddr4_tccd_l_tck = timing->ddr4_tccd_l_tck + 1;
    }

    // Round up t_ccd_dlr if gd_en=1
    if ((gd_en == 1) && ((timing->ddr4_tccd_dlr_tck%2)!=0)) {
      timing->ddr4_tccd_dlr_tck = timing->ddr4_tccd_dlr_tck + 1;
    }

    // for tccd_s, default to 4 clks
    timing->ddr4_tccd_s_tck = 4;

    timing->ddr4_tmrd_tck = 8;

    //Assign tcrc_alert value in ps
    timing->ddr4_tcrc_alert_ps = 13000;

    // for tmod, default TMOD_TCK is 24 clocks, so adjust the TMOD to this value
    timing->ddr4_tmod_ps = 24 * tck_ps;  // max(24nCK, 15ns) (Micron Datasheet)

    // tISmin + tIHmin
    timing->ddr4_tmpx_s_tck   = 2;    // tISmin + tIHmin (Micron Datasheet)
                      // tIS(base)min = 115 - 60[ps], tIS(Vref)min = 215 - 150[ps], tIH(base)min = 140 - 85[ps], tIH(Vref)min = 215 - 150[ps]
                      // Not clear how 2 was derived.

    // for tMPX_LH, default to 12000 ps
    timing->ddr4_tmpx_lh_ps = 12000;  // tMPX_LHmin = 12 [ns] (Micron Datasheet)

    // for trtp, default to 7500 ps
    // for sg above 2400, tRTP is 6000 ps so need to change
    timing->ddr4_trtp_ps = 7500;  // max(4nCK, 7.5ns) (Micron Datasheet)

    // for twr, default to 15000 ps
    timing->ddr4_twr_ps = 15000;  // (Micron Datasheet)

    // set the following in terms of ps
    timing->ddr4_tras_max_ps = 70200000;  // 9 * tREFI, tREFI = 7.8 [ns] (0 C <= T <= 85 C) (Micron Datasheet)

    // set the following in terms of ps
    if (sdram_capacity_mbits == 2048){
      timing->ddr4_trfc_min_ps  = 160000;  // Micron Model
      timing->ddr4_trfc_min2_ps = 110000;  // Micron Model
      timing->ddr4_trfc_min4_ps =  90000;  // Micron Model
    }

    if (sdram_capacity_mbits == 4096) {
      timing->ddr4_trfc_min_ps  = 260000;  // Micron Model, Micron Datasheet
      timing->ddr4_trfc_min2_ps = 160000;  // Micron Model, Micron Datasheet
      timing->ddr4_trfc_min4_ps = 110000;  // Micron Model, Micron Datasheet
      timing->ddr4_trfc_dlr_ps  = 90000;
      timing->ddr4_trfc_dlr2_ps = 55000;
      timing->ddr4_trfc_dlr4_ps = 40000;
    }

    if (sdram_capacity_mbits == 8192) {
      timing->ddr4_trfc_min_ps  = 350000;  // Micron Model, Micron Datasheet
      timing->ddr4_trfc_min2_ps = 260000;  // Micron Model, Micron Datasheet
      timing->ddr4_trfc_min4_ps = 160000;  // Micron Model, Micron Datasheet
      timing->ddr4_trfc_dlr_ps  = 120000;
      timing->ddr4_trfc_dlr2_ps = 90000;
      timing->ddr4_trfc_dlr4_ps = 55000;
    }

    if (sdram_capacity_mbits == 16384) {
      timing->ddr4_trfc_min_ps  = 550000;  // Use value of JESD79-4B.
      timing->ddr4_trfc_min2_ps = 350000;  // Use value of JESD79-4B.
      timing->ddr4_trfc_min4_ps = 260000;  // Use value of JESD79-4B.
      timing->ddr4_trfc_dlr_ps  = 120000;  // Use value of JESD79-4B.
      timing->ddr4_trfc_dlr2_ps = 90000;   // Use value of JESD79-4B.
      timing->ddr4_trfc_dlr4_ps = 55000;   // Use value of JESD79-4B.
    }

    timing->ddr4_trfc_max_ps = 70200000;

    timing->trpa_ps = timing->trp_ps + tck_ps;

    // set the following dependent on other params
    // tREFI = 7.8us = 7800000ps in all speed grades
    //timing->ddr4_trefi_ps = (7800000/(spd->tck_ps*32));
    //timing->ddr4_trefi_ps = (timing->ddr4_trefi_ps*spd->tck_ps);
    //timing->ddr4_trefi_ps = int (timing->ddr4_trefi);
    timing->ddr4_trefi_ps = 7800000;

    // set the following in terms of clks
    timing->ddr4_tzqinit_tck  = 1024;  // Micron Datasheet
    timing->ddr4_tzqoper_tck  = 512;   // Micron Datasheet
    timing->ddr4_tzqcs_tck    = 128;   // Micron Datasheet

    // set the tXP in terms of ps --- max(4nCK, 6ns) (Micron Datasheet)
    if (tck_ps > 1500) {
      timing->ddr4_txp_ps = tck_ps * 4;
    } else {
      timing->ddr4_txp_ps = 6000;
    }

    // set the tXPDLL in terms of ps
    timing->ddr4_txpdll_ps = 24000;  // Micron Model

    // set the CAS Latency and the CAS Write Latency (dependent on the speed grade/tck)
    timing->ddr4_tcl_tck          = ddr4_get_cas_latency(p,hdlr,gd_en,dll_off_init);
    timing->ddr4_tcl_rdbi_tck     = ddr4_get_cas_latency_rdbi(p,hdlr,gd_en,dll_off_init);
    timing->ddr4_tcwl_1st_set_tck = ddr4_get_CWL_1st_set(p,hdlr,dll_off_init);
    timing->ddr4_tcwl_2nd_set_tck = ddr4_get_CWL_2nd_set(p,hdlr,dll_off_init);

    // geardown
    timing->ddr4_tsync_gear_tck  = timing->ddr4_tmod_ps / tck_ps+4;
    timing->ddr4_tcmd_gear_tck   = timing->ddr4_tmod_ps / tck_ps;
    timing->ddr4_tgear_setup_tck = 2;
    timing->ddr4_tgear_hold_tck  = 2;

    // for twr_crc_dm
    timing->ddr4_twr_crc_dm_tck = timing->ddr4_wcl_tck;   // The definition of this parameter is tWR + WCL,
                                // where WCL=max(NnCK, 3.75ns) (N=4 for 1600, N=5 for higher speeds (Micron Datasheet))
                                // But, in ddrc_cfg.sv, this is treated as only WCL portion.

    // CA parity timing
    timing->ddr4_tpar_unknown_ps  = timing->ddr4_tpl_tck * tck_ps;  // PL (Micron Datasheet)
    timing->ddr4_tpar_alert_on_ps = (timing->ddr4_tpl_tck * tck_ps) + 6000;  // PL + 6ns (Micron Datasheet)

    // Update timing parameters if DLL-off mode is enabled during SDRAM initialization.
    if (dll_off_init == 1) {
      timing->trrd_l_tck      = 4;
      timing->trrd_s_tck      = 4;
      timing->ddr4_trrd_dlr_tck = 4;
      timing->ddr4_twtr_l_tck   = 4;
      timing->ddr4_twtr_s_tck   = 2;
      timing->ddr4_tcke_ps    = tck_ps * 3;
      timing->ddr4_trtp_ps    = tck_ps * 4;
    }

    // Micron model's tDQSCK (DLL-off) value is 5.8ns.
    timing->ddr4_tdqsck_dll_off_ps = 5800;  // Micron Model

    timing->ddr4_tstab_ps = 5000000; // JEDEC value 5us
}

// --------------------------------------------------------------------------
// Name        : ddr4_get_cas_latency()
// Description : depending on the speed grade/tck, pick a CAS latency
// Params      : pstate, SubsysHdlr_t* hdlr, gd_en, dll_off_mode
// Returns     : CAS Latency value
// --------------------------------------------------------------------------
uint32_t ddr4_get_cas_latency(bool pstate, SubsysHdlr_t* hdlr, bool gd_en, bool dll_off_mode)
{
  dwc_ddr4_speed_grade_e sg = hdlr->spdData_m.ddr4_sg;
  uint32_t cas_latency;
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[pstate];

  // SPN_DEBUG - need to update this function to put proper random ranges, for
  //             now, just use some default values

  // depending on the speed grade, pick from an allowed value of CAS Latencies

  if (dll_off_mode == 1) {
    cas_latency = 10; // CL must be set to 10 with DLL-off mode
  } else {
              //Set cas_latency if pstate = 0 and if tck_ps is not changed for other pstates, then don't change cas_latency
              if(pstate == 0 || (pstate != 0 && (hdlr->spdData_m.tck_ps[0] == hdlr->spdData_m.tck_ps[pstate]))) {
    switch(sg) {
    case DWC_DDR4_1600J: cas_latency = 10; break;
    case DWC_DDR4_1600K: cas_latency = 11; break;
    case DWC_DDR4_1600L: cas_latency = 12; break;
    case DWC_DDR4_1866L: cas_latency = 12; break;
    case DWC_DDR4_1866M: cas_latency = 13; break;
    case DWC_DDR4_1866N: cas_latency = 14; break;
    case DWC_DDR4_2133N: cas_latency = 14; break;
    case DWC_DDR4_2133P: cas_latency = 15; break;
    case DWC_DDR4_2133R: cas_latency = 16; break;
    case DWC_DDR4_2400P: cas_latency = 15; break;
    case DWC_DDR4_2400R: cas_latency = 16; break;
    case DWC_DDR4_2400T: cas_latency = 17; break;
    case DWC_DDR4_2400U: cas_latency = 18; break;
    case DWC_DDR4_2666T: cas_latency = 17; break;
    case DWC_DDR4_2666U: cas_latency = 18; break;
    case DWC_DDR4_2666V: cas_latency = 19; break;
    case DWC_DDR4_2666W: cas_latency = 20; break;
    case DWC_DDR4_2933V: cas_latency = 19; break;
    case DWC_DDR4_2933W: cas_latency = 20; break;
    case DWC_DDR4_2933Y: cas_latency = 21; break;
    case DWC_DDR4_2933AA: cas_latency = 22; break;
    case DWC_DDR4_3200W: cas_latency = 20; break;
    case DWC_DDR4_3200AA: cas_latency = 22; break;
    case DWC_DDR4_3200AC: cas_latency = 24; break;

    // DDR4 3DS
    case DWC_DDR4_1600J_3DS2B: cas_latency = 12; break;
    case DWC_DDR4_1600K_3DS2B: cas_latency = 13; break;
    case DWC_DDR4_1600L_3DS2B: cas_latency = 14; break;
    case DWC_DDR4_1866L_3DS2B: cas_latency = 14; break;
    case DWC_DDR4_1866M_3DS2B: cas_latency = 15; break;
    case DWC_DDR4_1866N_3DS2B: cas_latency = 16; break;
    case DWC_DDR4_2133P_3DS2A: cas_latency = 17; break;
    case DWC_DDR4_2133P_3DS3A: cas_latency = 18; break;
    case DWC_DDR4_2133R_3DS4A: cas_latency = 20; break;
    case DWC_DDR4_2400P_3DS3B: cas_latency = 18; break;
    case DWC_DDR4_2400T_3DS2A: cas_latency = 19; break;
    case DWC_DDR4_2400U_3DS2A: cas_latency = 20; break;
    case DWC_DDR4_2400U_3DS4A: cas_latency = 22; break;
    case DWC_DDR4_2666T_3DS3A: cas_latency = 20; break;
    case DWC_DDR4_2666V_3DS3A: cas_latency = 22; break;
    case DWC_DDR4_2666W_3DS4A: cas_latency = 24; break;
    case DWC_DDR4_3200W_3DS4A: cas_latency = 24; break;
    case DWC_DDR4_3200AA_3DS4A: cas_latency = 26; break;
    case DWC_DDR4_3200AC_3DS4A: cas_latency = 28; break;
    default:
      ERROR_MESSAGE(("Error: ddr4_get_cas_latency() - unknown speed grade, sg = %d\n", sg));
      break;
    }
        } else {
    switch(tck_ps) {
    case 1250          : cas_latency = 12; break; //1600
    case 1071 ... 1072 : cas_latency = 14; break; //1866
    case 938           : cas_latency = 16; break; //2133
    case 833           : cas_latency = 18; break; //2400
    case 750           : cas_latency = 20; break; //2666
    case 682           : cas_latency = 22; break; //2933
    case 625           : cas_latency = 24; break; //3200
    default:
      ERROR_MESSAGE(("Error: ddr4_get_cas_latency() - unknown tck_ps[%0d] = %0d\n", pstate,tck_ps));
      break;
    }
              }
  }

  if (gd_en == 1 && (cas_latency % 2) != 0) {
    cas_latency = cas_latency + 1;
  }

  // return the CAS Latency
  return cas_latency;
}

//--------------------------------------------------------------------------
// Name        : ddr4_get_CWL_1st_set
// Description : depending on the speed grade/tck and CAS Latency, pick the lower CAS Write Latency value
// Params      : pstate, SubsysHdlr_t* hdlr, dll_off_init
// Returns     : lower possible CAS Write Latency value
//--------------------------------------------------------------------------
uint32_t ddr4_get_CWL_1st_set (bool pstate, SubsysHdlr_t* hdlr, bool dll_off_init)
{
  dwc_ddr4_speed_grade_e sg = hdlr->spdData_m.ddr4_sg;
  uint32_t cas_write_latency_1st_set = 0;
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[pstate];

  if (dll_off_init) {
    cas_write_latency_1st_set = 9; //CWL must be set to 9 with DLL-off mode
  } else {
             //Set cas_write_latency_1st_set if pstate = 0. If tck_ps is not changed for other pstates, then don't change cas_write_latency_1st_set
             if(pstate == 0 || (pstate != 0 && (hdlr->spdData_m.tck_ps[0] == hdlr->spdData_m.tck_ps[pstate]))) {
    switch (sg) {
    case DWC_DDR4_1600J: cas_write_latency_1st_set = 9; break;
    case DWC_DDR4_1600K: cas_write_latency_1st_set = 9; break;
    case DWC_DDR4_1600L: cas_write_latency_1st_set = 9; break;
    case DWC_DDR4_1866L: cas_write_latency_1st_set = 10; break;
    case DWC_DDR4_1866M: cas_write_latency_1st_set = 10; break;
    case DWC_DDR4_1866N: cas_write_latency_1st_set = 10; break;
    case DWC_DDR4_2133N: cas_write_latency_1st_set = 11; break;
    case DWC_DDR4_2133P: cas_write_latency_1st_set = 11; break;
    case DWC_DDR4_2133R: cas_write_latency_1st_set = 11; break;
    case DWC_DDR4_2400P: cas_write_latency_1st_set = 12; break;
    case DWC_DDR4_2400R: cas_write_latency_1st_set = 12; break;
    case DWC_DDR4_2400U: cas_write_latency_1st_set = 12; break;
    case DWC_DDR4_2400T: cas_write_latency_1st_set = 12; break;
    case DWC_DDR4_2666T: cas_write_latency_1st_set = 14; break;
    case DWC_DDR4_2666U: cas_write_latency_1st_set = 14; break;
    case DWC_DDR4_2666V: cas_write_latency_1st_set = 14; break;
    case DWC_DDR4_2666W: cas_write_latency_1st_set = 14; break;
    case DWC_DDR4_2933V: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_2933W: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_2933Y: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_2933AA: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_3200W: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_3200AA: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_3200AC: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_1600J_3DS2B: cas_write_latency_1st_set = 9; break;
    case DWC_DDR4_1600K_3DS2B: cas_write_latency_1st_set = 9; break;
    case DWC_DDR4_1600L_3DS2B: cas_write_latency_1st_set = 9; break;
    case DWC_DDR4_1866L_3DS2B: cas_write_latency_1st_set = 10; break;
    case DWC_DDR4_1866M_3DS2B: cas_write_latency_1st_set = 10; break;
    case DWC_DDR4_1866N_3DS2B: cas_write_latency_1st_set = 10; break;
    case DWC_DDR4_2133P_3DS2A: cas_write_latency_1st_set = 11; break;
    case DWC_DDR4_2133P_3DS3A: cas_write_latency_1st_set = 11; break;
    case DWC_DDR4_2133R_3DS4A: cas_write_latency_1st_set = 11; break;
    case DWC_DDR4_2400P_3DS3B: cas_write_latency_1st_set = 12; break;
    case DWC_DDR4_2400T_3DS2A: cas_write_latency_1st_set = 12; break;
    case DWC_DDR4_2400U_3DS2A: cas_write_latency_1st_set = 12; break;
    case DWC_DDR4_2400U_3DS4A: cas_write_latency_1st_set = 12; break;
    case DWC_DDR4_2666T_3DS3A: cas_write_latency_1st_set = 14; break;
    case DWC_DDR4_2666V_3DS3A: cas_write_latency_1st_set = 14; break;
    case DWC_DDR4_2666W_3DS4A: cas_write_latency_1st_set = 14; break;
    case DWC_DDR4_3200W_3DS4A: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_3200AA_3DS4A: cas_write_latency_1st_set = 16; break;
    case DWC_DDR4_3200AC_3DS4A: cas_write_latency_1st_set = 16; break;
    default:
      ERROR_MESSAGE(("Unknown speed grade\n"));
      break;
    }
       } else {
    switch(tck_ps) {
    case 1250          : cas_write_latency_1st_set =  9; break; //1600
    case 1071 ... 1072 : cas_write_latency_1st_set = 10; break; //1866
    case 938           : cas_write_latency_1st_set = 11; break; //2133
    case 833           : cas_write_latency_1st_set = 12; break; //2400
    case 750           : cas_write_latency_1st_set = 14; break; //2666
    case 682           : cas_write_latency_1st_set = 16; break; //2933
    case 625           : cas_write_latency_1st_set = 16; break; //3200
    default:
      ERROR_MESSAGE(("Error: ddr4_get_CWL_1st_set() - unknown tck_ps[%0d] = %0d\n", pstate,tck_ps));
      break;
    }
       }
  }
  return cas_write_latency_1st_set;
}

// --------------------------------------------------------------------------
// Name        : ddr4_get_CWL_2nd_set
// Description : depending on the speed grade/tck and CAS Latency, pick a the upper CAS Write Latency value
// Params      : pstate, SubsysHdlr_t* hdlr, dll_off_init
// Returns     : upper possible CAS Write Latency value
// --------------------------------------------------------------------------
uint32_t ddr4_get_CWL_2nd_set(bool pstate, SubsysHdlr_t* hdlr, bool dll_off_init)
{
  dwc_ddr4_speed_grade_e sg = hdlr->spdData_m.ddr4_sg;
  uint32_t cas_write_latency_2nd_set = 0;
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[pstate];

  if (dll_off_init) {
    cas_write_latency_2nd_set = 9; //CWL must be set to 9 with DLL-off mode
  } else {
             //Set cas_write_latency_2nd_set if pstate = 0. If tck_ps is not changed for other pstates, then don't change cas_write_latency_2nd_set
             if(pstate == 0 || (pstate != 0 && (hdlr->spdData_m.tck_ps[0] == hdlr->spdData_m.tck_ps[pstate]))) {
    switch (sg) {
    case DWC_DDR4_1600J: cas_write_latency_2nd_set = 11; break;
    case DWC_DDR4_1600K: cas_write_latency_2nd_set = 11; break;
    case DWC_DDR4_1600L: cas_write_latency_2nd_set = 11; break;
    case DWC_DDR4_1866L: cas_write_latency_2nd_set = 12; break;
    case DWC_DDR4_1866M: cas_write_latency_2nd_set = 12; break;
    case DWC_DDR4_1866N: cas_write_latency_2nd_set = 12; break;
    case DWC_DDR4_2133N: cas_write_latency_2nd_set = 14; break;
    case DWC_DDR4_2133P: cas_write_latency_2nd_set = 14; break;
    case DWC_DDR4_2133R: cas_write_latency_2nd_set = 14; break;
    case DWC_DDR4_2400P: cas_write_latency_2nd_set = 16; break;
    case DWC_DDR4_2400R: cas_write_latency_2nd_set = 16; break;
    case DWC_DDR4_2400U: cas_write_latency_2nd_set = 16; break;
    case DWC_DDR4_2400T: cas_write_latency_2nd_set = 16; break;
    case DWC_DDR4_2666T: cas_write_latency_2nd_set = 18; break;
    case DWC_DDR4_2666U: cas_write_latency_2nd_set = 18; break;
    case DWC_DDR4_2666V: cas_write_latency_2nd_set = 18; break;
    case DWC_DDR4_2666W: cas_write_latency_2nd_set = 18; break;
    case DWC_DDR4_2933V: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_2933W: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_2933Y: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_2933AA: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_3200W: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_3200AA: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_3200AC: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_1600J_3DS2B: cas_write_latency_2nd_set = 11; break;
    case DWC_DDR4_1600K_3DS2B: cas_write_latency_2nd_set = 11; break;
    case DWC_DDR4_1600L_3DS2B: cas_write_latency_2nd_set = 11; break;
    case DWC_DDR4_1866L_3DS2B: cas_write_latency_2nd_set = 12; break;
    case DWC_DDR4_1866M_3DS2B: cas_write_latency_2nd_set = 12; break;
    case DWC_DDR4_1866N_3DS2B: cas_write_latency_2nd_set = 12; break;
    case DWC_DDR4_2133P_3DS2A: cas_write_latency_2nd_set = 14; break;
    case DWC_DDR4_2133P_3DS3A: cas_write_latency_2nd_set = 14; break;
    case DWC_DDR4_2133R_3DS4A: cas_write_latency_2nd_set = 14; break;
    case DWC_DDR4_2400P_3DS3B: cas_write_latency_2nd_set = 16; break;
    case DWC_DDR4_2400T_3DS2A: cas_write_latency_2nd_set = 16; break;
    case DWC_DDR4_2400U_3DS2A: cas_write_latency_2nd_set = 16; break;
    case DWC_DDR4_2400U_3DS4A: cas_write_latency_2nd_set = 16; break;
    case DWC_DDR4_2666T_3DS3A: cas_write_latency_2nd_set = 18; break;
    case DWC_DDR4_2666V_3DS3A: cas_write_latency_2nd_set = 18; break;
    case DWC_DDR4_2666W_3DS4A: cas_write_latency_2nd_set = 18; break;
    case DWC_DDR4_3200W_3DS4A: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_3200AA_3DS4A: cas_write_latency_2nd_set = 20; break;
    case DWC_DDR4_3200AC_3DS4A: cas_write_latency_2nd_set = 20; break;
    default:
      ERROR_MESSAGE(("Unknown speed grade\n"));
      break;
    }
       } else {
    switch(tck_ps) {
    case 1250          : cas_write_latency_2nd_set =  9; break; //1600
    case 1071 ... 1072 : cas_write_latency_2nd_set = 10; break; //1866
    case 938           : cas_write_latency_2nd_set = 11; break; //2133
    case 833           : cas_write_latency_2nd_set = 12; break; //2400
    case 750           : cas_write_latency_2nd_set = 14; break; //2666
    case 682           : cas_write_latency_2nd_set = 16; break; //2933
    case 625           : cas_write_latency_2nd_set = 16; break; //3200
    default:
      ERROR_MESSAGE(("Error: ddr4_get_CWL_2nd_set() - unknown tck_ps[%0d] = %0d\n", pstate,tck_ps));
      break;
    }
       }
  }
  return cas_write_latency_2nd_set;
}

// --------------------------------------------------------------------------
// Name        : ddr4_get_cas_latency_rdbi()
// Description : depending on the speed grade/tck, pick a CAS latency
// Params      :
// Returns     : CAS Latency value with Read DBI
// --------------------------------------------------------------------------
uint32_t ddr4_get_cas_latency_rdbi(bool pstate, SubsysHdlr_t* hdlr, bool gd_en, bool dll_off_mode)
{
  dwc_ddr4_speed_grade_e sg = hdlr->spdData_m.ddr4_sg;
  uint32_t cas_latency_rdbi;
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[pstate];

  // SPN_DEBUG - need to update this function to put proper random ranges, for
  //             now, just use some default values

  // depending on the speed grade, pick from an allowed value of CAS Latencies

  if (dll_off_mode == 1) {
    cas_latency_rdbi = 10; // CL must be set to 10 with DLL-off mode (CL_DBI will be 10 as well)
  } else {
             //Set cas_latency_rdbi if pstate = 0. If tck_ps is not changed for other pstates, then don't change cas_latency_rdbi
             if(pstate == 0 || (pstate != 0 && (hdlr->spdData_m.tck_ps[0] == hdlr->spdData_m.tck_ps[pstate]))) {
    switch (sg) {
    case DWC_DDR4_1600J: cas_latency_rdbi = 12; break;
    case DWC_DDR4_1600K: cas_latency_rdbi = 13; break;
    case DWC_DDR4_1600L: cas_latency_rdbi = 14; break;
    case DWC_DDR4_1866L: cas_latency_rdbi = 14; break;
    case DWC_DDR4_1866M: cas_latency_rdbi = 15; break;
    case DWC_DDR4_1866N: cas_latency_rdbi = 16; break;
    case DWC_DDR4_2133N: cas_latency_rdbi = 17; break;
    case DWC_DDR4_2133P: cas_latency_rdbi = 18; break;
    case DWC_DDR4_2133R: cas_latency_rdbi = 19; break;
    case DWC_DDR4_2400P: cas_latency_rdbi = 18; break;
    case DWC_DDR4_2400R: cas_latency_rdbi = 19; break;
    case DWC_DDR4_2400T: cas_latency_rdbi = 20; break;
    case DWC_DDR4_2400U: cas_latency_rdbi = 21; break;
    case DWC_DDR4_2666T: cas_latency_rdbi = 20; break;
    case DWC_DDR4_2666U: cas_latency_rdbi = 21; break;
    case DWC_DDR4_2666V: cas_latency_rdbi = 22; break;
    case DWC_DDR4_2666W: cas_latency_rdbi = 23; break;
    case DWC_DDR4_2933V: cas_latency_rdbi = 23; break;
    case DWC_DDR4_2933W: cas_latency_rdbi = 24; break;
    case DWC_DDR4_2933Y: cas_latency_rdbi = 26; break;
    case DWC_DDR4_2933AA: cas_latency_rdbi = 26; break;
    case DWC_DDR4_3200W: cas_latency_rdbi = 24; break;
    case DWC_DDR4_3200AA: cas_latency_rdbi = 26; break;
    case DWC_DDR4_3200AC: cas_latency_rdbi = 28; break;

    // DDR4 3DS
    //does not support DBI for now, set to CAS Latency value
    case DWC_DDR4_1600J_3DS2B:
    case DWC_DDR4_1600K_3DS2B:
    case DWC_DDR4_1600L_3DS2B:
    case DWC_DDR4_1866L_3DS2B:
    case DWC_DDR4_1866M_3DS2B:
    case DWC_DDR4_1866N_3DS2B:
    case DWC_DDR4_2133P_3DS2A:
    case DWC_DDR4_2133P_3DS3A:
    case DWC_DDR4_2133R_3DS4A:
    case DWC_DDR4_2400P_3DS3B:
    case DWC_DDR4_2400T_3DS2A:
    case DWC_DDR4_2400U_3DS2A:
    case DWC_DDR4_2400U_3DS4A:
    case DWC_DDR4_2666T_3DS3A:
    case DWC_DDR4_2666V_3DS3A:
    case DWC_DDR4_2666W_3DS4A:
    case DWC_DDR4_3200W_3DS4A:
    case DWC_DDR4_3200AA_3DS4A:
    case DWC_DDR4_3200AC_3DS4A:
      cas_latency_rdbi = ddr4_get_cas_latency(pstate,hdlr,gd_en,dll_off_mode);
      break;
    default:
      ERROR_MESSAGE(("Error: Ddr4.pm::set_clk_speed() - unknown speed grade, sg = %d\n", sg));
      break;
    }
       } else {
                if(sg >= DWC_DDR4_1600J_3DS2B && sg <= DWC_DDR4_3200AC_3DS4A) {
      //DDR4 3DS
      //does not support DBI for now, set to CAS Latency value
                  cas_latency_rdbi = ddr4_get_cas_latency(pstate,hdlr,gd_en,dll_off_mode);
                } else {
    switch(tck_ps) {
      case 1250          : cas_latency_rdbi = 14; break; //1600
      case 1071 ... 1072 : cas_latency_rdbi = 16; break; //1866
      case 938           : cas_latency_rdbi = 19; break; //2133
      case 833           : cas_latency_rdbi = 21; break; //2400
      case 750           : cas_latency_rdbi = 23; break; //2666
      case 682           : cas_latency_rdbi = 26; break; //2933
      case 625           : cas_latency_rdbi = 28; break; //3200
      default:
        ERROR_MESSAGE(("Error: ddr4_get_cas_latency_rdbi() - unknown tck_ps[%0d] = %0d\n", pstate,tck_ps));
        break;
      }
    }
             }
  }

  if (gd_en == 1 && (cas_latency_rdbi % 2) != 0) {
    cas_latency_rdbi = cas_latency_rdbi + 1;
  }

  // return the CAS Latency with Read DBI
  return cas_latency_rdbi;
}

// --------------------------------------------------------------------------
// Name        : ddr5::set_clk_speed()
// Description : set the sg_tck_ps value in the hdlr->timingParams_m structure
// Params      : hdlr
// Returns     : none
// --------------------------------------------------------------------------
void ddr5_set_clk_speed(SubsysHdlr_t* hdlr, uint32_t p)
{
  dwc_ddr5_speed_grade_e sg = hdlr->spdData_m.ddr5_sg;
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);

  switch (sg) {
    case DWC_DDR5_3200A :
    case DWC_DDR5_3200B :
    case DWC_DDR5_3200C :
    case DWC_DDR5_3200A_3DS :
    case DWC_DDR5_3200B_3DS :
    case DWC_DDR5_3200C_3DS :
      timing->sg_tck_ps = 625;
      break;
    case DWC_DDR5_3600A :
    case DWC_DDR5_3600B :
    case DWC_DDR5_3600C :
      timing->sg_tck_ps = 555;
      break;
    //TODO : should make tck of mono and 3DS device aligned to 555
    case DWC_DDR5_3600A_3DS :
    case DWC_DDR5_3600B_3DS :
    case DWC_DDR5_3600C_3DS :
      timing->sg_tck_ps = 556;
      break;
    case DWC_DDR5_4000A :
    case DWC_DDR5_4000B :
    case DWC_DDR5_4000C :
    case DWC_DDR5_4000A_3DS :
    case DWC_DDR5_4000B_3DS :
    case DWC_DDR5_4000C_3DS :
      timing->sg_tck_ps = 500;
      break;
    case DWC_DDR5_4400A :
    case DWC_DDR5_4400B :
    case DWC_DDR5_4400C :
      timing->sg_tck_ps  = 454;
      break;
    //TODO : should make tck of mono and 3DS device aligned to 555
    case DWC_DDR5_4400A_3DS :
    case DWC_DDR5_4400B_3DS :
    case DWC_DDR5_4400C_3DS :
      timing->sg_tck_ps = 455;
      break;
    case DWC_DDR5_4800A :
    case DWC_DDR5_4800B :
    case DWC_DDR5_4800C :
    case DWC_DDR5_4800A_3DS :
    case DWC_DDR5_4800B_3DS :
    case DWC_DDR5_4800C_3DS :
      timing->sg_tck_ps = 417;
      break;
    case DWC_DDR5_5200A :
    case DWC_DDR5_5200B :
    case DWC_DDR5_5200C :
      timing->sg_tck_ps = 384;
      break;
    case DWC_DDR5_5600A :
    case DWC_DDR5_5600B :
    case DWC_DDR5_5600C :
      timing->sg_tck_ps = 357;
      break;
    case DWC_DDR5_6000A :
    case DWC_DDR5_6000B :
    case DWC_DDR5_6000C :
      timing->sg_tck_ps = 333;
      break;
    case DWC_DDR5_6400A :
    case DWC_DDR5_6400B :
    case DWC_DDR5_6400C :
      timing->sg_tck_ps = 312;
      break;
    default:
      ERROR_MESSAGE(("Error: Ddr5.pm::set_clk_speed() - unknown speed grade, sg = %d\n", sg));
      break;
  }

}

// --------------------------------------------------------------------------
// Name        : ddr5_set_default_timing()
// Description : set all the default values for SNPS VIP
// Returns     : none
// --------------------------------------------------------------------------
/** @brief method to setup timing parameter for ddr5
  *  @note there are JEDEC timing values: COMMITTEE LETTER BALLOT Item #
  *   Committee: JC42.3 , Committee Item Number : 1848.99A
  */
void ddr5_set_default_timing(SubsysHdlr_t* hdlr, uint32_t p)
{
  TRACE();

  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  dwc_ddr5_speed_grade_e sg = hdlr->spdData_m.ddr5_sg;

  uint32_t tck_ps = hdlr->spdData_m.tck_ps[p];
  if(hdlr->spdData_m.tck_ps[p]!=timing->sg_tck_ps) {
    dwc_cinit_print("tck_ps (%0d ps) selected is not min JEDEC TCK value(%0d)\n",
      hdlr->spdData_m.tck_ps[p], timing->sg_tck_ps);
  }

  uint32_t sdram_width_bits = hdlr->spdData_m.sdram_width_bits;
  uint32_t cid_width = hdlr->spdData_m.cid_width;
  uint32_t sdram_capacity_mbits = hdlr->spdData_m.sdram_capacity_mbits;
  uint8_t sdram_burst_len = 2*cfg->burst_rdwr;

  timing->ddr5_trefi1_ps = 3900000;
  timing->ddr5_trefi2_ps = 1950000;

  LOG_MESSAGE(hdlr, 0, ("sdram_capacity_mbits=%d\n",sdram_capacity_mbits));

  if(sdram_capacity_mbits == 8192) {
    timing->ddr5_trfc1_ps    = 195000;
    timing->ddr5_trfc2_ps    = 130000;
    timing->ddr5_trfcsb_ps   = 115000;
    timing->ddr5_trefsbrd_ps = 30000;
    timing->ddr5_trfc1_dlr_ps = 65000;
    timing->ddr5_trfc2_dlr_ps = 43333;
    timing->ddr5_trfcsb_dlr_ps = 38333;
    timing->ddr5_trefsbrd_dlr_ps= 15000;
  } else if (sdram_capacity_mbits == 16384) {
    timing->ddr5_trfc1_ps    = 295000;
    timing->ddr5_trfc2_ps    = 160000;
    timing->ddr5_trfcsb_ps   = 130000;
    timing->ddr5_trefsbrd_ps = 30000;
    timing->ddr5_trfc1_dlr_ps = 98333;
    timing->ddr5_trfc2_dlr_ps = 53333;
    timing->ddr5_trfcsb_dlr_ps = 43333;
    timing->ddr5_trefsbrd_dlr_ps= 15000;
  // DDR5 Full Spec Draft Rev0.83 does not define the trfc related timing for 24Gb,32Gb and 64Gb,
  // temporarily use the value of 16Gb
  } else if (sdram_capacity_mbits == 24576) {
    timing->ddr5_trfc1_ps    = 295000;
    timing->ddr5_trfc2_ps    = 160000;
    timing->ddr5_trfcsb_ps   = 130000;
    timing->ddr5_trefsbrd_ps = 30000;
    timing->ddr5_trfc1_dlr_ps = 98333;
    timing->ddr5_trfc2_dlr_ps = 53333;
    timing->ddr5_trfcsb_dlr_ps = 43333;
    timing->ddr5_trefsbrd_dlr_ps= 15000;
  } else if (sdram_capacity_mbits == 32768) {
    timing->ddr5_trfc1_ps    = 295000;
    timing->ddr5_trfc2_ps    = 160000;
    timing->ddr5_trfcsb_ps   = 130000;
    timing->ddr5_trefsbrd_ps = 30000;
    timing->ddr5_trfc1_dlr_ps = 98333;
    timing->ddr5_trfc2_dlr_ps = 53333;
    timing->ddr5_trfcsb_dlr_ps = 43333;
    timing->ddr5_trefsbrd_dlr_ps= 15000;
  } else if (sdram_capacity_mbits == 65536){
    timing->ddr5_trfc1_ps    = 295000;
    timing->ddr5_trfc2_ps    = 160000;
    timing->ddr5_trfcsb_ps   = 130000;
    timing->ddr5_trefsbrd_ps = 30000;
    timing->ddr5_trfc1_dlr_ps = 98333;
    timing->ddr5_trfc2_dlr_ps = 53333;
    timing->ddr5_trfcsb_dlr_ps = 43333;
    timing->ddr5_trefsbrd_dlr_ps= 15000;
  }
  //zqcal
  timing->ddr5_tzqcal_ps = 1000000; // 1us
  timing->ddr5_tzqlat_ps = max(30000,8*tck_ps);
  //power down
  timing->ddr5_tcpded_ps = max(5000,8*tck_ps);
  timing->ddr5_tpd_ps = max(5000,8*tck_ps);
  timing->ddr5_txp_ps = max(7500,5*tck_ps);
  timing->ddr5_tactpden_tck = 2;
  timing->ddr5_tprpden_tck  = 2;
  timing->ddr5_trefpden_tck = 2;

  //self-refresh
  timing->ddr5_tcsl_ps = 10000; //10ns
  timing->ddr5_tcsh_srexit_ps =10000; //10ns
  timing->ddr5_tcsl_srexit_tck = 3;
  timing->ddr5_tcksrx_ps = 2500;//2.5ns
  timing->ddr5_tcklcs_tck = CEIL(timing->ddr5_tcpded_ps,tck_ps) + 1;
  timing->ddr5_tcasrx_ps = 4 * tck_ps;
  timing->ddr5_txs_dll_ps = 0; //TBD

  //mode register
  timing->ddr5_tmrr_tck = max(CEIL(14000,tck_ps),16);
  timing->ddr5_tmrr_p_tck = 8;
  timing->ddr5_tmrw_tck  = max(CEIL(5000,tck_ps),8);
  timing->ddr5_tmrd_tck = max(CEIL(14000,tck_ps),16);
  //MPSM
  timing->ddr5_tmpsmx_ps = max(14000,16*tck_ps);
  timing->ddr5_tmpdpdact_ps = 0; //TBD
  //MPC
  timing->ddr5_tmpc_delay_tck = timing->ddr5_tmrd_tck;
  timing->ddr5_tmc_mpc_setup_tck = 3;
  timing->ddr5_tmc_mpc_hold_tck  = 3;
  timing->ddr5_tmpc_cs_min_tck = 4; //JEDEC 4 tck
  timing->ddr5_tmpc_cs_max_tck = 8;
  //PDA
  timing->ddr5_tpda_latch_min_ps = 0; //TBD
  timing->ddr5_tpda_dqs_delay_min_ps = 5000;
  timing->ddr5_tpda_dqs_delay_max_ps = 18000;
  timing->ddr5_tpda_delay_ps = timing->ddr5_tpda_dqs_delay_max_ps + 1000*sdram_burst_len/2 + 19000;
  timing->ddr5_tpda_s_tck = 3;
  timing->ddr5_tpda_h_tck = 3;

  timing->ddr5_tras_max_ps = 19500000; // 5*tREFI1 , tREFI1 = 3.9[us], 0<=TCASE<=85

  //timing parameters for DDR5-3200 to DDR5-4000
  //TODO : more speedbin support
  timing->ddr5_tccd_l_tck = max(CEIL(5000,tck_ps),8);
  timing->ddr5_tccd_l_wr_tck = max(CEIL(20000,tck_ps),32);
  timing->ddr5_tccd_s_tck = 8;
  timing->trrd_s_tck = 8;
  timing->trrd_l_tck = max(CEIL(5000,tck_ps),8);
  timing->ddr5_twtr_s_tck = CEIL(2500,tck_ps);
  timing->ddr5_twtr_l_tck = CEIL(10000,tck_ps);
  timing->ddr5_trtp_ps = 7500;
  timing->ddr5_tppd_tck = 2;
  timing->ddr5_twr_ps = 30000;
  timing->ddr5_trrd_dlr_tck = 4;

  timing->ddr5_tccd_l_wr_ps = 20000;
  /**@brief tCCD_L_WR2 : write to write same bank group second write not partial write
   *  Based on DDR5 VIP O-2018.06, tccd_l_wr2 should be equal to tccd_l_wr;
   *  So here temporarily set ddr5_tccd_l_wr2_ps = ddr5_tccd_l_wr_ps = 20ns
   *  When JC-42.3C-18 Ballot is accepted by JEDEC, change it to corresponding value
   * */
  timing->ddr5_tccd_l_wr2_ps = 20000;

  //tfaw_dlr/tfaw_slr
  timing->ddr5_tfaw_dlr_tck = 16;
  timing->ddr5_tfaw_slr_tck = 32; //  max(32ntck, xxxns);

  if(sdram_width_bits == 4) {
    if((cid_width == 1) || (cid_width == 2)) {
      switch (sg) {
        case DWC_DDR5_3200A_3DS:
        case DWC_DDR5_3200B_3DS:
        case DWC_DDR5_3200C_3DS: timing->ddr5_tfaw_slr_tck = max(CEIL(20000,tck_ps),32); break;
        case DWC_DDR5_3600A_3DS:
        case DWC_DDR5_3600B_3DS:
        case DWC_DDR5_3600C_3DS: timing->ddr5_tfaw_slr_tck = max(CEIL(17700,tck_ps),32); break;
        case DWC_DDR5_4000A_3DS:
        case DWC_DDR5_4000B_3DS:
        case DWC_DDR5_4000C_3DS: timing->ddr5_tfaw_slr_tck = max(CEIL(16000,tck_ps),32); break;
        case DWC_DDR5_4400A_3DS:
        case DWC_DDR5_4400B_3DS:
        case DWC_DDR5_4400C_3DS: timing->ddr5_tfaw_slr_tck = max(CEIL(14540,tck_ps),32); break;
        case DWC_DDR5_4800A_3DS:
        case DWC_DDR5_4800B_3DS:
        case DWC_DDR5_4800C_3DS: timing->ddr5_tfaw_slr_tck = max(CEIL(13300,tck_ps),32); break;
        default:
        ERROR_MESSAGE(("Error: ddr5::set_default_timing tfaw_slr - unknown speed grade, sg = %d\n", sg));
        break;

      }
    } else {
      timing->ddr5_tfaw_slr_tck = 32; //TODO : 8H and 16H are TBD
    }
  } else {
    timing->ddr5_tfaw_slr_tck = 32; //TODO : X8 device are TBD
  }

  if(cid_width == 0) {
    if(sdram_width_bits == 16) {
      switch (sg) {
        case DWC_DDR5_3200A:
        case DWC_DDR5_3200B:
        case DWC_DDR5_3200C: timing->ddr5_tfaw_tck = max(CEIL(25000,tck_ps),40); break;
        case DWC_DDR5_3600A:
        case DWC_DDR5_3600B:
        case DWC_DDR5_3600C: timing->ddr5_tfaw_tck = max(CEIL(22220,tck_ps),40); break;
        case DWC_DDR5_4000A:
        case DWC_DDR5_4000B:
        case DWC_DDR5_4000C: timing->ddr5_tfaw_tck = max(CEIL(22220,tck_ps),40); break;
        //TODO: Not defined in SPEC for about 4400
        case DWC_DDR5_4400A:
        case DWC_DDR5_4400B:
        case DWC_DDR5_4400C: timing->ddr5_tfaw_tck = max(CEIL(22220,tck_ps),40); break;
        case DWC_DDR5_4800A:
        case DWC_DDR5_4800B:
        case DWC_DDR5_4800C: timing->ddr5_tfaw_tck = max(CEIL(22220,tck_ps),40); break;
        default:
        ERROR_MESSAGE(("Error: ddr5::set_default_timing tfaw - unknown speed grade = %d\n", sg));
        break;
      }
    } else {
      switch (sg) {
        case DWC_DDR5_3200A:
        case DWC_DDR5_3200B:
        case DWC_DDR5_3200C: timing->ddr5_tfaw_tck = max(CEIL(20000,tck_ps),32); break;
        case DWC_DDR5_3600A:
        case DWC_DDR5_3600B:
        case DWC_DDR5_3600C: timing->ddr5_tfaw_tck = max(CEIL(17770,tck_ps),32); break;
        case DWC_DDR5_4000A:
        case DWC_DDR5_4000B:
        case DWC_DDR5_4000C: timing->ddr5_tfaw_tck = max(CEIL(16000,tck_ps),32); break;
        //TODO: Not defined in SPEC for above 4400
        case DWC_DDR5_4400A:
        case DWC_DDR5_4400B:
        case DWC_DDR5_4400C: timing->ddr5_tfaw_tck = max(CEIL(16000,tck_ps),40); break;
        case DWC_DDR5_4800A:
        case DWC_DDR5_4800B:
        case DWC_DDR5_4800C: timing->ddr5_tfaw_tck = max(CEIL(16000,tck_ps),40); break;
        default:
        ERROR_MESSAGE(("Error: ddr5::set_default_timing tfaw() - unknown speed grade, tck_ps = %d\n", sg));
        break;
      }
    }
  }

  switch (sg) {
    case DWC_DDR5_3200A:
      timing->trcd_ps = 13750;
      timing->trp_ps  = 13750;
      timing->trc_ps  = 45750;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3200B:
      timing->trcd_ps = 16250;
      timing->trp_ps  = 16250;
      timing->trc_ps  = 48250;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3200C:
      timing->trcd_ps = 17500;
      timing->trp_ps  = 17500;
      timing->trc_ps  = 49500;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3600A:
      timing->trcd_ps = 14444;
      timing->trp_ps  = 14444;
      timing->trc_ps  = 46444;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3600B:
      timing->trcd_ps = 16667;
      timing->trp_ps  = 16667;
      timing->trc_ps  = 48667;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3600C:
      timing->trcd_ps = 17778;
      timing->trp_ps  = 17778;
      timing->trc_ps  = 49778;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4000A:
      timing->trcd_ps = 14000;
      timing->trp_ps  = 14000;
      timing->trc_ps  = 46000;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4000B:
      timing->trcd_ps = 16000;
      timing->trp_ps  = 16000;
      timing->trc_ps  = 48500;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4000C:
      timing->trcd_ps = 18000;
      timing->trp_ps  = 18000;
      timing->trc_ps  = 50000;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4400A:
      timing->trcd_ps = 14545;
      timing->trp_ps  = 14545;
      timing->trc_ps  = 46545;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4400B:
      timing->trcd_ps = 16364;
      timing->trp_ps  = 16364;
      timing->trc_ps  = 48364;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4400C:
      timing->trcd_ps = 18182;
      timing->trp_ps  = 18182;
      timing->trc_ps  = 50182;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4800A:
      timing->trcd_ps = 14167;
      timing->trp_ps  = 14167;
      timing->trc_ps  = 46167;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4800B:
      timing->trcd_ps = 16667;
      timing->trp_ps  = 16667;
      timing->trc_ps  = 48667;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4800C:
      timing->trcd_ps = 18330;
      timing->trp_ps  = 18330;
      timing->trc_ps  = 50330;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3200A_3DS:
      timing->trcd_ps = 13750;
      timing->trp_ps  = 13750;
      timing->trc_ps  = 45750;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3200B_3DS:
      timing->trcd_ps = 16250;
      timing->trp_ps  = 16250;
      timing->trc_ps  = 48250;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3200C_3DS:
      timing->trcd_ps = 17500;
      timing->trp_ps  = 17500;
      timing->trc_ps  = 49500;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3600A_3DS:
      timing->trcd_ps = 14444;
      timing->trp_ps  = 14444;
      timing->trc_ps  = 46444;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3600B_3DS:
      timing->trcd_ps = 16667;
      timing->trp_ps  = 16667;
      timing->trc_ps  = 48667;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_3600C_3DS:
      timing->trcd_ps = 17778;
      timing->trp_ps  = 17778;
      timing->trc_ps  = 49778;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4000A_3DS:
      timing->trcd_ps = 14000;
      timing->trp_ps  = 14000;
      timing->trc_ps  = 46000;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4000B_3DS:
      timing->trcd_ps = 16000;
      timing->trp_ps  = 16000;
      timing->trc_ps  = 48500;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4000C_3DS:
      timing->trcd_ps = 18000;
      timing->trp_ps  = 18000;
      timing->trc_ps  = 50000;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4400A_3DS:
      timing->trcd_ps = 14545;
      timing->trp_ps  = 14545;
      timing->trc_ps  = 46545;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4400B_3DS:
      timing->trcd_ps = 16364;
      timing->trp_ps  = 16364;
      timing->trc_ps  = 48364;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4400C_3DS:
      timing->trcd_ps = 18182;
      timing->trp_ps  = 18182;
      timing->trc_ps  = 50182;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4800A_3DS:
      timing->trcd_ps = 14167;
      timing->trp_ps  = 14167;
      timing->trc_ps  = 46167;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4800B_3DS:
      timing->trcd_ps = 16667;
      timing->trp_ps  = 16667;
      timing->trc_ps  = 48667;
      timing->ddr5_tras_min_ps = 32000;
      break;
    case DWC_DDR5_4800C_3DS:
      timing->trcd_ps = 17500;
      timing->trp_ps  = 17500;
      timing->trc_ps  = 49500;
      timing->ddr5_tras_min_ps = 32000;
      break;

    default :
      ERROR_MESSAGE(("Error: ddr5::set_default_values_vip() - unknown speed grade = %d\n", sg));
      break;
  }

  //Get cas_latency and calculate cwl_latency.
  timing->ddr5_tcl_tck  = ddr5_get_cas_latency(p,hdlr);
  timing->ddr5_tcwl_tck = timing->ddr5_tcl_tck - 2;

  //power down
  timing->ddr5_trdpden_tck = timing->ddr5_tcl_tck + sdram_burst_len/2 + 1;
  timing->ddr5_twrpden_tck = timing->ddr5_tcwl_tck + sdram_burst_len/2 + CEIL(timing->ddr5_twr_ps,tck_ps) + 1;
  timing->ddr5_twrapden_tck = timing->ddr5_tcwl_tck + sdram_burst_len/2 + CEIL(timing->ddr5_twr_ps,tck_ps) + 1;
  timing->ddr5_tmrrpden_tck = timing->ddr5_tcl_tck + 8 + 1;
  timing->ddr5_tmrwpden_tck = timing->ddr5_tmrd_tck;
  timing->ddr5_tmpcpden_tck = 0; //TBD
  //Initialization
  timing->ddr5_tinit4_ps = 2000000;
  timing->ddr5_tinit5_tck = 3;

  //VrefCA
  timing->ddr5_tvrefca_delay_tck = timing->ddr5_tmrd_tck;
  timing->ddr5_tvrefca_cs_min_tck = 4; //JEDEC 3.5 tck
  timing->ddr5_tvrefca_cs_max_tck = 8;

  //OSC TBD
  timing->ddr5_tosco_ps = 0;

  //CRC TBD
  timing->ddr5_tcrc_alert_ps = 0;
  timing->ddr5_tcrc_alert_pw_ps = 0;
  
  // RCD
  if(IS_RDIMM){
    timing->ddr5_rcd_tstab01_ps = 0; // TBD
    timing->ddr5_rcd_tpdex_ps = max(10000,16*tck_ps);
    timing->ddr5_rcd_tcssr_ps = max(15000,24*tck_ps);
    timing->ddr5_rcd_tcpded2srx_tck = max(CEIL(10000,tck_ps),16);
    timing->ddr5_rcd_tsrx2srx_tck   = max(CEIL(10000,tck_ps),16);
    timing->ddr5_rcd_tckoff_ps = max(15000,24*tck_ps);
    timing->ddr5_rcd_tckact_tck = 16;
    timing->ddr5_rcd_tcsalt_tck = 8;
    
  }
  else{
    timing->ddr5_rcd_tstab01_ps = 0;
    timing->ddr5_rcd_tpdex_ps = 0;
    timing->ddr5_rcd_tcssr_ps = 0;
    timing->ddr5_rcd_tcpded2srx_tck = 0;
    timing->ddr5_rcd_tsrx2srx_tck = 0;
    timing->ddr5_rcd_tckoff_ps = 0;
    timing->ddr5_rcd_tckact_tck = 0;
    timing->ddr5_rcd_tcsalt_tck = 0;
  }
  LOG_MESSAGE(hdlr, 0, ("End\n"));
}

// --------------------------------------------------------------------------
// Name        : ddr5_get_cas_latency()
// Description : depending on the speed grade/tck, pick a CAS latency
// Params      : pstate, SubsysHdlr_t* hdlr
// Returns     : CAS Latency value
// --------------------------------------------------------------------------
uint32_t ddr5_get_cas_latency(bool pstate, SubsysHdlr_t* hdlr)
{
  dwc_ddr5_speed_grade_e sg = hdlr->spdData_m.ddr5_sg;
  uint32_t cid_width = hdlr->spdData_m.cid_width;
  uint32_t ddr5_cas_latency;
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[pstate];

  //Set cas_latency if pstate = 0 and if tck_ps is not changed for other pstates, then don't change cas_latency
  if(pstate == 0 || (pstate != 0 && (hdlr->spdData_m.tck_ps[0] == hdlr->spdData_m.tck_ps[pstate]))) {
    switch(sg) {
      case DWC_DDR5_3200A:  ddr5_cas_latency = 22;  break;
      case DWC_DDR5_3200B:  ddr5_cas_latency = 26;  break;
      case DWC_DDR5_3200C:  ddr5_cas_latency = 28;  break;
      case DWC_DDR5_3600A:  ddr5_cas_latency = 26;  break;
      case DWC_DDR5_3600B:  ddr5_cas_latency = 30;  break;
      case DWC_DDR5_3600C:  ddr5_cas_latency = 32;  break;
      case DWC_DDR5_4000A:  ddr5_cas_latency = 28;  break;
      case DWC_DDR5_4000B:  ddr5_cas_latency = 32;  break;
      case DWC_DDR5_4000C:  ddr5_cas_latency = 36;  break;
      case DWC_DDR5_4400A:  ddr5_cas_latency = 32;  break;
      case DWC_DDR5_4400B:  ddr5_cas_latency = 36;  break;
      case DWC_DDR5_4400C:  ddr5_cas_latency = 40;  break;
      case DWC_DDR5_4800A:  ddr5_cas_latency = 34;  break;
      case DWC_DDR5_4800B:  ddr5_cas_latency = 40;  break;
      case DWC_DDR5_4800C:  ddr5_cas_latency = 44;  break;
      case DWC_DDR5_3200A_3DS:  ddr5_cas_latency = 26;  break;
      case DWC_DDR5_3200B_3DS:  ddr5_cas_latency = 30;  break;
      case DWC_DDR5_3200C_3DS:  ddr5_cas_latency = 32;  break;
      case DWC_DDR5_3600A_3DS:  ddr5_cas_latency = 30;  break;
      case DWC_DDR5_3600B_3DS:  ddr5_cas_latency = 34;  break;
      case DWC_DDR5_3600C_3DS:  ddr5_cas_latency = 36;  break;
      case DWC_DDR5_4000A_3DS:  ddr5_cas_latency = 32;  break;
      case DWC_DDR5_4000B_3DS:  ddr5_cas_latency = 38;  break;
      case DWC_DDR5_4000C_3DS:  ddr5_cas_latency = 40;  break;
      case DWC_DDR5_4400A_3DS:  ddr5_cas_latency = 36;  break;
      case DWC_DDR5_4400B_3DS:  ddr5_cas_latency = 42;  break;
      case DWC_DDR5_4400C_3DS:  ddr5_cas_latency = 44;  break;
      case DWC_DDR5_4800A_3DS:  ddr5_cas_latency = 40;  break;
      case DWC_DDR5_4800B_3DS:  ddr5_cas_latency = 46;  break;
      case DWC_DDR5_4800C_3DS:  ddr5_cas_latency = 48;  break;
      default :
        ERROR_MESSAGE(("Error: ddr5::set_default_values_vip() - unknown speed grade = %d\n", sg));
        break;
    }
  } else {
    switch(tck_ps) {
      //Reference: DDR5_Spec Rev082. Table 189 — DDR5-4800 Speed Bins and Operations
      case 625 : ddr5_cas_latency = (cid_width == 0)? 30: 32; break; //3200
      case 555 : ddr5_cas_latency = (cid_width == 0)? 36: 36; break; //3600
      case 500 : ddr5_cas_latency = (cid_width == 0)? 40: 40; break; //4000
      case 454 : ddr5_cas_latency = (cid_width == 0)? 40: 44; break; //4400
      case 417 : ddr5_cas_latency = (cid_width == 0)? 44: 48; break; //4800
      //5200 to 6400 speedbin not yet supported
      //case 384 : ddr5_cas_latency = (cid_width == 0)? : ; break; //5200
      //case 357 : ddr5_cas_latency = (cid_width == 0)? : ; break; //5600
      //case 333 : ddr5_cas_latency = (cid_width == 0)? : ; break; //6000
      //case 312 : ddr5_cas_latency = (cid_width == 0)? : ; break; //6400
      default:
        ERROR_MESSAGE(("Error: ddr5_get_cas_latency() - unknown tck_ps[%0d] = %0d\n", pstate,tck_ps));
        break;
    }
  }
  // return the CAS Latency
  return ddr5_cas_latency;
}

#endif // MEMC_DDR4
