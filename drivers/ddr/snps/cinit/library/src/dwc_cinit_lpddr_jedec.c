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
#ifdef MEMC_LPDDR4

//Local variables to which data_rate is assigned as per tck_ps
dwc_lpddr4_data_rate_e l_lpddr4_data_rate[UMCTL2_FREQUENCY_NUM];
dwc_lpddr5_data_rate_e l_lpddr5_data_rate[UMCTL2_FREQUENCY_NUM];

/** @brief Description : set the sg_tck_ps value in the hdlr->timingParams_m structure.
 * @note these are JEDEC timing values
 * */
void lpddr4_set_clk_speed(SubsysHdlr_t* hdlr, uint32_t p) 
{
    TRACE();
    dwc_lpddr4_data_rate_e sg = hdlr->spdData_m.lpddr4_data_rate;
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);

    
    switch (sg) {
        case DWC_LPDDR4_4267:
            timing->sg_tck_ps = 467;
            break;
        case DWC_LPDDR4_3733:
            timing->sg_tck_ps = 536;
            break;
        case DWC_LPDDR4_3200:
            timing->sg_tck_ps = 625;
            break;
        case DWC_LPDDR4_2667:
            timing->sg_tck_ps = 750;
            break;
        case DWC_LPDDR4_2133:
            timing->sg_tck_ps = 938;
            break;
        case  DWC_LPDDR4_1600:
            timing->sg_tck_ps = 1250;
            break;
        case DWC_LPDDR4_1066:
            timing->sg_tck_ps = 1875;
            break;
        case DWC_LPDDR4_533:
            timing->sg_tck_ps = 3750;
            break;
        default:
            ERROR_MESSAGE(("Error: lpddr4_set_clk_speed() - unknown date rate, sg = %d\n", sg));
            break;
        
    }
    // @todo setup clock time during boot, for now using tck
    timing->lpddr4_tckb=timing->sg_tck_ps;
}

/** @brief method to setup timing parameters for LPDDR4
  */
void lpddr4_set_default_timing(SubsysHdlr_t* hdlr, uint32_t p)
{
    TRACE();
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
	// tck_ps may or may not be min JEDEC value
	uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
	if(hdlr->spdData_m.tck_ps[p]!=timing->sg_tck_ps) {
		dwc_cinit_print("tck_ps (%0d ps) selected is not min JEDEC TCK value(%0d)\n",
		  hdlr->spdData_m.tck_ps[p], timing->sg_tck_ps);
	}
    ddrSpdData_t* spd = &(hdlr->spdData_m);
    uint32_t sdram_capacity_mbits = hdlr->spdData_m.sdram_capacity_mbits;
    if(sdram_capacity_mbits == 2048) {timing->lpddr4_tpbr2pbr=60000;}
    else {timing->lpddr4_tpbr2pbr=90000;}

    timing->lpddr4_trfcab=dwc_cinit_get_lpddr4_trfcab(hdlr);
    if (spd->sdram_capacity_mbits == 2048) { timing->lpddr4_trfcpb=60000;}
    if (spd->sdram_capacity_mbits == 3072) { timing->lpddr4_trfcpb=90000;}
    if (spd->sdram_capacity_mbits == 4096) { timing->lpddr4_trfcpb=90000;}
    if (spd->sdram_capacity_mbits == 6144) { timing->lpddr4_trfcpb=140000;}
    if (spd->sdram_capacity_mbits == 8192) { timing->lpddr4_trfcpb=140000;}
    if (spd->sdram_capacity_mbits > 8192) { timing->lpddr4_trfcpb=190000;}

    timing->lpddr4_tras_min= max(42000,3*tck_ps);
    timing->lpddr4_tras_max=70200000;
    timing->lpddr4_trfiab=3904000;
    timing->lpddr4_trfipb=488000;
    if(hdlr->spdData_m.sdram_width_bits == 8) {
      timing->lpddr4_twtr=max(12000, 8*tck_ps);
    } else {
      timing->lpddr4_twtr=max(10000, 8*tck_ps);
    }
    timing->lpddr4_tfaw=40000;
    timing->lpddr4_tzqreset=max( CEIL(50000,tck_ps),3);
    timing->lpddr4_tzqinit=CEIL(100000,tck_ps);

    timing->lpddr4_tzqcs=max( CEIL(30000,tck_ps), 8);
    timing->lpddr4_tzqcsb=max( CEIL(30000,timing->lpddr4_tckb), 8);
    timing->lpddr4_tzqclb=CEIL(1000000,timing->lpddr4_tckb);
    timing->lpddr4_tzqcl=CEIL(1000000,tck_ps);
    timing->lpddr4_tmrr=8;
    timing->lpddr4_tmrw=max(CEIL(10000,tck_ps), 10);
    timing->lpddr4_tmrwb=max(CEIL(10000,timing->lpddr4_tckb), 10);
    timing->lpddr4_tmrd=max(CEIL(14000,tck_ps), 10);
    timing->lpddr4_tmrdb=max(CEIL(14000,timing->lpddr4_tckb), 10);
    
    timing->lpddr4_tcke=max(7500, tck_ps* 4);
    timing->lpddr4_tckesr=15000;
    timing->lpddr4_tccd=8;
    timing->lpddr4_tccdmw=32;
    timing->lpddr4_trtp= max(7500, 8*tck_ps);
    if( hdlr->spdData_m.sdram_width_bits==8 ) {
     timing->lpddr4_twr=max(20000, 6*tck_ps); 
    } else {
     timing->lpddr4_twr=max(18000, 6*tck_ps); // x16
    }
    timing->lpddr4_tppd=4;
    timing->lpddr4_tdqsck=3000;
    timing->lpddr4_tdqsck_max=3500;
    timing->lpddr4_tdqsck_max_dr=3600;
    timing->lpddr4_tosco=max(40000,8*tck_ps);

    timing->lpddr4_tdqss=1;
    timing->lpddr4_tdqs2dq=450;
    timing->lpddr4_tdipw_ps=ceil( (tck_ps/2) * 0.45);
    timing->lpddr4_trcd=max(18000, 4*tck_ps);
    timing->lpddr4_trp=max(18000, 4*tck_ps);
    timing->lpddr4_trpa=max(21000, 4*tck_ps);
    timing->lpddr4_trc=timing->lpddr4_tras_min + timing->lpddr4_trp;
    timing->lpddr4_tcmdcke=max(1750, 3*tck_ps);
    timing->lpddr4_tmrwckel=max(14000,10*tck_ps);
    timing->lpddr4_tmrwckelb=max(14000,10*timing->lpddr4_tckb);
    timing->lpddr4_tckckeh=max(1750, 3*tck_ps);
    timing->lpddr4_tckelck=max(5000, 5*tck_ps);
    timing->lpddr4_tsr=max(15000, 3*tck_ps);
    timing->lpddr4_todton_min=1500;
    timing->lpddr4_tvrcg_enable=200000;
    timing->lpddr4_tvrcg_disable=100000;
    timing->lpddr4_derated_trcd=timing->lpddr4_trcd + 1875;
    timing->lpddr4_derated_tras_min=timing->lpddr4_tras_min + 1875;
    timing->lpddr4_derated_trp=timing->lpddr4_trp + 1875;
    timing->lpddr4_derated_trrd=timing->lpddr4_trrd + 1875;
    timing->lpddr4_derated_trc=timing->lpddr4_tras_min + timing->lpddr4_trp + 3750;

    timing->lpddr4_txp=max(7500, 5*tck_ps);
    switch (l_lpddr4_data_rate[0]) {      //tFAW,tRRD will be constant for the speed_bin in use
        case DWC_LPDDR4_4267 : 
            timing->lpddr4_tfaw=30000;
            timing->lpddr4_trrd=max(7500, 4*tck_ps);
            break;
        default :
            timing->lpddr4_tfaw=40000;
            timing->lpddr4_trrd=max(10000, 4*tck_ps);
            break;
    }
    if (hdlr->spdData_m.sdram_width_bits ==8 ) {
      switch (l_lpddr4_data_rate[p]) {
          case DWC_LPDDR4_4267 : 
              timing->lpddr4_cl=40;
              timing->lpddr4_cl_dbi=44;
              timing->lpddr4_nrtp=16;
              break;
          case DWC_LPDDR4_3733: 
              timing->lpddr4_cl=36;
              timing->lpddr4_cl_dbi=40;
              timing->lpddr4_nrtp=14;
              break;
          case DWC_LPDDR4_3200: 
              timing->lpddr4_cl=32;
              timing->lpddr4_cl_dbi=36;
              timing->lpddr4_nrtp=12;
              break;
          case DWC_LPDDR4_2667: 
              timing->lpddr4_cl=26;
              timing->lpddr4_cl_dbi=30;
              timing->lpddr4_nrtp=10;
              break;
          case DWC_LPDDR4_2133: 
              timing->lpddr4_cl=22;
              timing->lpddr4_cl_dbi=24;
              timing->lpddr4_nrtp=8;
              break;
          case DWC_LPDDR4_1600: 
              timing->lpddr4_cl=16;
              timing->lpddr4_cl_dbi=18;
              timing->lpddr4_nrtp=8;
              break;
          case DWC_LPDDR4_1066: 
              timing->lpddr4_cl=10;
              timing->lpddr4_cl_dbi=12;
              timing->lpddr4_nrtp=8;
              break;
          default:
              ERROR_MESSAGE(("Error: lpddr4_set_defaults() - unknown data rate, sg = %d\n", l_lpddr4_data_rate[p]));
              break;
      }
    } else {
      switch (l_lpddr4_data_rate[p]) {
          case DWC_LPDDR4_4267 : 
              timing->lpddr4_cl=36;
              timing->lpddr4_cl_dbi=40;
              timing->lpddr4_nrtp=16;
              break;
          case DWC_LPDDR4_3733: 
              timing->lpddr4_cl=32;
              timing->lpddr4_cl_dbi=36;
              timing->lpddr4_nrtp=14;
              break;
          case DWC_LPDDR4_3200: 
              timing->lpddr4_cl=28;
              timing->lpddr4_cl_dbi=32;
              timing->lpddr4_nrtp=12;
              break;
          case DWC_LPDDR4_2667: 
              timing->lpddr4_cl=24;
              timing->lpddr4_cl_dbi=28;
              timing->lpddr4_nrtp=10;
              break;
          case DWC_LPDDR4_2133: 
              timing->lpddr4_cl=20;
              timing->lpddr4_cl_dbi=22;
              timing->lpddr4_nrtp=8;
              break;
          case DWC_LPDDR4_1600: 
              timing->lpddr4_cl=14;
              timing->lpddr4_cl_dbi=16;
              timing->lpddr4_nrtp=8;
              break;
          case DWC_LPDDR4_1066: 
              timing->lpddr4_cl=10;
              timing->lpddr4_cl_dbi=12;
              timing->lpddr4_nrtp=8;
              break;

          default:
              ERROR_MESSAGE(("Error: lpddr4_set_defaults() - unknown speedgrade, sg = %d\n", l_lpddr4_data_rate[p]));
              break;
      }

    }
    if (hdlr->spdData_m.sdram_width_bits ==8 ) {
      switch(timing->lpddr4_cl) {
        case 6:
             timing->lpddr4_cwl_seta=4;
             timing->lpddr4_cwl_setb=4;
             timing->lpddr4_nwr=6;
             break;
        case 10:
             timing->lpddr4_cwl_seta=6;
             timing->lpddr4_cwl_setb=8;
             timing->lpddr4_nwr=12;
             break;
        case 16:
             timing->lpddr4_cwl_seta=8;
             timing->lpddr4_cwl_setb=12;
             timing->lpddr4_nwr=16;
             break;
        case 22:
             timing->lpddr4_cwl_seta=10;
             timing->lpddr4_cwl_setb=18;
             timing->lpddr4_nwr=22;
             break;
        case 26:
             timing->lpddr4_cwl_seta=12;
             timing->lpddr4_cwl_setb=22;
             timing->lpddr4_nwr=28;
             break;
        case 32:
             timing->lpddr4_cwl_seta=14;
             timing->lpddr4_cwl_setb=26;
             timing->lpddr4_nwr=32;
             break;
        case 36:
             timing->lpddr4_cwl_seta=16;
             timing->lpddr4_cwl_setb=30;
             timing->lpddr4_nwr=38;
             break;
        case 40:
             timing->lpddr4_cwl_seta=18;
             timing->lpddr4_cwl_setb=34;
             timing->lpddr4_nwr=44;
             break;
         default:
             ERROR_MESSAGE(("Error: lpddr4_set_defaults() - unknown cas,lpddr4_cl  = %d\n", timing->lpddr4_cl));
             break;
 
      }
    }else{
      switch(timing->lpddr4_cl) {
        case 6:
             timing->lpddr4_cwl_seta=4;
             timing->lpddr4_cwl_setb=4;
             timing->lpddr4_nwr=6;
             break;
        case 10:
             timing->lpddr4_cwl_seta=6;
             timing->lpddr4_cwl_setb=8;
             timing->lpddr4_nwr=10;
             break;
        case 14:
             timing->lpddr4_cwl_seta=8;
             timing->lpddr4_cwl_setb=12;
             timing->lpddr4_nwr=16;
             break;
        case 20:
             timing->lpddr4_cwl_seta=10;
             timing->lpddr4_cwl_setb=18;
             timing->lpddr4_nwr=20;
             break;
        case 24:
             timing->lpddr4_cwl_seta=12;
             timing->lpddr4_cwl_setb=22;
             timing->lpddr4_nwr=24;
             break;
        case 28:
             timing->lpddr4_cwl_seta=14;
             timing->lpddr4_cwl_setb=26;
             timing->lpddr4_nwr=30;
             break;
        case 32:
             timing->lpddr4_cwl_seta=16;
             timing->lpddr4_cwl_setb=30;
             timing->lpddr4_nwr=34;
             break;
        case 36:
             timing->lpddr4_cwl_seta=18;
             timing->lpddr4_cwl_setb=34;
             timing->lpddr4_nwr=40;
             break;
         default:
             ERROR_MESSAGE(("Error: lpddr4_set_defaults() - unknown cas,lpddr4_cl  = %d\n", timing->lpddr4_cl));
             break;
 
      }
    }



    switch (l_lpddr4_data_rate[p]) {
        case DWC_LPDDR4_4267 : 
            timing->lpddr4_odtloff_latency_seta =28;
            timing->lpddr4_odtloff_latency_setb =44;
            timing->lpddr4_odtlon_latency_seta=8;
            timing->lpddr4_odtlon_latency_setb=24;
            timing->lpddr4_wdqson_seta=8;
            timing->lpddr4_wdqson_setb=24;
            timing->lpddr4_wdqsoff_seta=36;
            timing->lpddr4_wdqsoff_setb=52;

            break;
        case DWC_LPDDR4_3733: 
            timing->lpddr4_odtloff_latency_seta =26;
            timing->lpddr4_odtloff_latency_setb =40;
            timing->lpddr4_odtlon_latency_seta=6;
            timing->lpddr4_odtlon_latency_setb=20;
            timing->lpddr4_wdqson_seta=6;
            timing->lpddr4_wdqson_setb=20;
            timing->lpddr4_wdqsoff_seta=33;
            timing->lpddr4_wdqsoff_setb=47;
            break;
        case DWC_LPDDR4_3200: 
            timing->lpddr4_odtloff_latency_seta =24;
            timing->lpddr4_odtloff_latency_setb =36;
            timing->lpddr4_odtlon_latency_seta=6;
            timing->lpddr4_odtlon_latency_setb=18;
            timing->lpddr4_wdqson_seta=6;
            timing->lpddr4_wdqson_setb=18;
            timing->lpddr4_wdqsoff_seta=30;
            timing->lpddr4_wdqsoff_setb=42;
            break;
        case DWC_LPDDR4_2667: 
            timing->lpddr4_odtloff_latency_seta =22;
            timing->lpddr4_odtloff_latency_setb =32;
            timing->lpddr4_odtlon_latency_seta=4;
            timing->lpddr4_odtlon_latency_setb=14;
            timing->lpddr4_wdqson_seta=4;
            timing->lpddr4_wdqson_setb=14;
            timing->lpddr4_wdqsoff_seta=27;
            timing->lpddr4_wdqsoff_setb=37;
            break;
        case DWC_LPDDR4_2133: 
            timing->lpddr4_odtloff_latency_seta =20;
            timing->lpddr4_odtloff_latency_setb =28;
            timing->lpddr4_odtlon_latency_seta=4;
            timing->lpddr4_odtlon_latency_setb=12;
            timing->lpddr4_wdqson_seta=4;
            timing->lpddr4_wdqson_setb=12;
            timing->lpddr4_wdqsoff_seta=24;
            timing->lpddr4_wdqsoff_setb=32;
            break;
        case DWC_LPDDR4_1600: 
            timing->lpddr4_odtloff_latency_seta =20;
            timing->lpddr4_odtloff_latency_setb =22;
            timing->lpddr4_odtlon_latency_seta=1;
            timing->lpddr4_odtlon_latency_setb=6;           
            timing->lpddr4_wdqson_seta=0;
            timing->lpddr4_wdqson_setb=6;
            timing->lpddr4_wdqsoff_seta=21;
            timing->lpddr4_wdqsoff_setb=25;
            break;
        case DWC_LPDDR4_1066: 
            timing->lpddr4_odtloff_latency_seta =20;
            timing->lpddr4_odtloff_latency_setb =22;
            timing->lpddr4_odtlon_latency_seta=1;
            timing->lpddr4_odtlon_latency_setb=6;           
            timing->lpddr4_wdqson_seta=0;
            timing->lpddr4_wdqson_setb=0;
            timing->lpddr4_wdqsoff_seta=18;
            timing->lpddr4_wdqsoff_setb=20;
            break;

        default:
            ERROR_MESSAGE(("Error: lpddr4_set_defaults() - unknown speedgrade, sg = %d\n", l_lpddr4_data_rate[p]));
            break;
    }

  // calculate tzqinit
  timing->lpddr_tzqinit_min= CEIL(timing->lpddr4_tzqinit,32);
}



/** @brief Description : set the sg_tck_ps value in the hdlr->timingParams_m structure.
 * @note these are JEDEC timing values, using data rate (WCK) and WCKCK
 * ratio the CK period is calculated.
 * */

void lpddr5_set_clk_speed(SubsysHdlr_t* hdlr, uint32_t p) 
{

    TRACE();
    dwc_lpddr5_data_rate_e sg = hdlr->spdData_m.lpddr5_data_rate;
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
    ddrSpdData_t* spd = &(hdlr->spdData_m);
    uint32_t wckck_4_1 = (spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) ? 1 :
        0; 

    switch (sg) {
        case DWC_LPDDR5_6400:
            timing->sg_tck_ps = 1250;
            break;
        case DWC_LPDDR5_6000 :
            timing->sg_tck_ps = 1333;
            break;
        case DWC_LPDDR5_5420 :
            timing->sg_tck_ps = 1474;
            break;
        case DWC_LPDDR5_4800 :
            timing->sg_tck_ps = 1667;
            break;
        case DWC_LPDDR5_4266:
            timing->sg_tck_ps = 1876;
            break;
        case DWC_LPDDR5_3733:
            timing->sg_tck_ps = 2140;
            break;
        case DWC_LPDDR5_3200:
            timing->sg_tck_ps = (wckck_4_1==1) ? 2500 : 1250;
            break;
        case DWC_LPDDR5_2710:
            timing->sg_tck_ps = (wckck_4_1==1) ? 2950 : 1475;
            break;
        case DWC_LPDDR5_2133:
            timing->sg_tck_ps = (wckck_4_1==1) ? 3745 : 1876;
            break;
        case DWC_LPDDR5_1600:
            timing->sg_tck_ps = (wckck_4_1==1) ? 5000 : 2500;
            break;
        case DWC_LPDDR5_1066:
            timing->sg_tck_ps = (wckck_4_1==1) ? 7520 : 3745;
            break;
        case DWC_LPDDR5_533:
            timing->sg_tck_ps = (wckck_4_1==1) ? 1493 : 7520 ;
            break;
        default:
            ERROR_MESSAGE(("Error: lpddr5_set_clk_speed() - unknown data rate, = %d\n", sg));
            break;
        
    }
    timing->lpddr5_wck_ps=(wckck_4_1==1) ? timing->sg_tck_ps/4 : timing->sg_tck_ps/2;
}
/** @brief method to setup timing parameters for LPDDR5
 * @note these are JEDEC timing values: COMMITTEE LETTER BALLOT Item #
 * JC-42.6-18xx.xx , Date: 2018/05/14
 *
    * */
void lpddr5_set_default_timing(SubsysHdlr_t* hdlr, uint32_t p)
{
    TRACE();
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
    // tck_ps may or may not be min JEDEC value
    uint32_t ratio;
	  uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
	  if(hdlr->spdData_m.tck_ps[p]!=timing->sg_tck_ps) {
		  dwc_cinit_print("tck_ps (%0d ps) selected is not min JEDEC TCK value(%0d)\n",
		  hdlr->spdData_m.tck_ps[p], timing->sg_tck_ps);
  	}
    uint8_t wl_seta= (hdlr->memCtrlr_m.lpddr5_mr[p].mr3.wls==0) ? 1 : 0;
    uint8_t x16=(hdlr->spdData_m.sdram_width_bits==16) ? 1 : 0;
    uint8_t dvfsc_enable=(hdlr->memCtrlr_m.lpddr5_mr[p].mr19.dvfsc==1) ?
        1 : 0;
    uint8_t read_dbi=hdlr->memCtrlr_m.lpddr5_mr[p].mr3.read_dbi;
    uint8_t rd_lecc=hdlr->memCtrlr_m.lpddr5_mr[p].mr22.recc;
    uint8_t wr_lecc=hdlr->memCtrlr_m.lpddr5_mr[p].mr22.wecc;
    
    ddrSpdData_t* spd = &(hdlr->spdData_m);
         ratio=(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 2 : 4;
    timing->lpddr5_trfcab_ps=dwc_cinit_get_lpddr5_trfcab(hdlr);
    timing->lpddr5_trfcpb_ps=dwc_cinit_get_lpddr5_trfcpb(hdlr);
    timing->lpddr5_tpbr2pbr_ps=dwc_cinit_get_lpddr5_tpbr2pbr(hdlr);
    timing->lpddr5_tpbr2act_ps=7500;
    // Using VIP default values for simulation.
    timing->lpddr5_wckdqo_ps=1000;
    timing->lpddr5_wckdqo_max_ps=1900;
    timing->lpddr5_wckdqi_ps=500;
    timing->lpddr5_trpst= 2.5 * (tck_ps/ratio); // 2.5 tWCK
    timing->lpddr5_tespd_ps=max(1750,2*tck_ps);
    timing->lpddr5_trbtp_ps=max(7500,2*tck_ps)-(2*tck_ps);
    timing->lpddr5_tsr_ps=max(15000,2*tck_ps);
    timing->lpddr5_txsr_ps=timing->lpddr5_trfcab_ps+max(7500,2*tck_ps);
    timing->lpddr5_tcspd_ps=10000+tck_ps;
    timing->lpddr5_tcmpd_ps=max(1500,2*tck_ps);
    timing->lpddr5_tescke_ps=max(1750,3*tck_ps);
    timing->lpddr5_tcmdpd_ps=3*tck_ps;
    timing->lpddr5_tcslck_ps=max(5000,3*tck_ps);
    timing->lpddr5_tckcsh_ps=2*tck_ps;
    timing->lpddr5_txp_ps=max(7500,3*tck_ps);
    timing->lpddr5_tcsh_ps=3000;
    timing->lpddr5_tcsl_ps=4000;
    timing->lpddr5_tmrwpd_ps=max(14000,6*tck_ps);
    timing->lpddr5_tzqpd_ps=max(1750,2*tck_ps);
    timing->lpddr5_tpdn_dsm_ms=4;
    timing->lpddr5_txsr_dsm_us=200; // in useconds
    timing->lpddr5_tras_min_ps=max(42000,3*tck_ps);
    timing->lpddr5_trefi_ps=3906000; 
    timing->lpddr5_tras_max_ps=70200000;
    timing->lpddr5_trefipb_ps=488000;     
    timing->lpddr5_trcd_ps=max(18000,2*tck_ps);
    timing->lpddr5_trpab_ps=max(21000,2*tck_ps);
    timing->lpddr5_trppb_ps=max(18000,2*tck_ps); 
    // ACTIVATE to ACTIVATE with all-bank precharge
    timing->lpddr5_trc_pab_ps=timing->lpddr5_tras_min_ps+timing->lpddr5_trpab_ps;
    // ACTIVATE to ACTIVATE with per-bank precharge
    timing->lpddr5_trc_ppb_ps=timing->lpddr5_tras_min_ps+timing->lpddr5_trppb_ps;
    if(spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
      timing->lpddr5_tccd_s_tck=2; 
      timing->lpddr5_tccd_l_tck= (spd->lpddr5_bk_bg_org== DWC_LPDDR5_4BK_4BG) ? 4 : 2; 
      timing->lpddr5_tccd_ps=2*tck_ps ;
    } else {
      timing->lpddr5_tccd_s_tck=4; 
      timing->lpddr5_tccd_l_tck= (spd->lpddr5_bk_bg_org== DWC_LPDDR5_4BK_4BG) ? 8 : 4; 
      timing->lpddr5_tccd_ps=4*tck_ps ;

    }

    timing->lpddr5_trrd_s_ps=max(5000,2*tck_ps);
    timing->lpddr5_trrd_l_ps=max(5000,2*tck_ps);
    timing->lpddr5_trrd_ps=max(10000,2*tck_ps); // 8Bank mode
    //timing->lpddr5_tfaw_ps= (spd->lpddr5_bk_bg_org== DWC_LPDDR5_4BK_4BG) ? 20000 : 40000;
    timing->lpddr5_tfaw_ps= 20000; // not supported 8Bank mode for now
    timing->lpddr5_trtp_ps = (spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) ? max(7500,2*tck_ps) :
        max(7500,4*tck_ps);

    timing->lpddr5_derated_trcd_ps=timing->lpddr5_trcd_ps + 1875;
    timing->lpddr5_derated_tras_min_ps=timing->lpddr5_tras_min_ps + 1875;
    timing->lpddr5_derated_trpab_ps=timing->lpddr5_trpab_ps + 1875;
    timing->lpddr5_derated_trppb_ps=timing->lpddr5_trppb_ps + 1875;
    timing->lpddr5_derated_trrd_ps=timing->lpddr5_trrd_ps + 1875;
    timing->lpddr5_derated_trcab_ps=timing->lpddr5_tras_min_ps + timing->lpddr5_trpab_ps + 3750;
    timing->lpddr5_derated_trcpb_ps=timing->lpddr5_tras_min_ps + timing->lpddr5_trppb_ps + 3750;

    if(hdlr->spdData_m.sdram_width_bits == 8) {
        if(wr_lecc == 0) {
           timing->lpddr5_twr_ps = max(36000,3*tck_ps);
           timing->lpddr5_twtr_s_ps=max(8250,4*tck_ps);
           timing->lpddr5_twtr_l_ps=max(14000,4*tck_ps);
           timing->lpddr5_twtr_ps=max(14000,4*tck_ps);
        } else {
           // Link-ECC is enabled
           timing->lpddr5_twr_ps = max(40000,3*tck_ps);
           timing->lpddr5_twtr_s_ps=max(12250,4*tck_ps);
           timing->lpddr5_twtr_l_ps=max(18000,4*tck_ps);
           timing->lpddr5_twtr_ps=max(18000,4*tck_ps);
        }
    } else {
        if(wr_lecc == 0) {
           timing->lpddr5_twr_ps = max(34000,3*tck_ps);
           timing->lpddr5_twtr_s_ps=max(6250,4*tck_ps);
           timing->lpddr5_twtr_l_ps=max(12000,4*tck_ps);
           timing->lpddr5_twtr_ps=max(12000,4*tck_ps);
        } else {
           // Link-ECC is enabled
           timing->lpddr5_twr_ps = max(38000,3*tck_ps);
           timing->lpddr5_twtr_s_ps=max(10250,4*tck_ps);
           timing->lpddr5_twtr_l_ps=max(16000,4*tck_ps);
           timing->lpddr5_twtr_ps=max(16000,4*tck_ps);
        }
    }
    timing->lpddr5_tppd_tck=2;
    timing->lpddr5_tccdmw_tck=4*timing->lpddr5_tccd_l_tck;
    timing->lpddr5_tmrr_tck=8;
    timing->lpddr5_tmrw_ps=max(10000,5*tck_ps);
    timing->lpddr5_tmrd_ps=max(14000,5*tck_ps);
    // Table 112 
    timing->lpddr5_odton_min_ps=1500;
    timing->lpddr5_odton_max_ps=3500;
    timing->lpddr5_odtoff_min_ps=1500;
    timing->lpddr5_odtoff_max_ps=3500;
    
    timing->lpddr5_tzqreset_ps=max(50000,3*tck_ps);
    timing->lpddr5_tzqlat_ps=max(30000,4*tck_ps);
    timing->lpddr5_tzqstop_ps=50000; //Ref Table :104 
    timing->lpddr5_tzqoff_us=50;
    timing->lpddr5_tzqcal_ps=1500000; // 1.5us - bug 8257
    timing->lpddr5_tvrcg_enable_ps=150000; /// @todo not sure where these values are coming from
    timing->lpddr5_tvrcg_disable_ps=100000;
    // 7.1 Effective Burst Length definition
    // here we do not account for 8B mode or BL32
    if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1){
        timing->lpddr5_bl_n_min_tck= 4;
        timing->lpddr5_bl_n_max_tck= 4;    
    } else {
      if(spd->lpddr5_bk_bg_org== DWC_LPDDR5_4BK_4BG) {
         timing->lpddr5_bl_n_min_tck= 2;
         timing->lpddr5_bl_n_max_tck= 4;  
      } else {
         timing->lpddr5_bl_n_min_tck= 2;
         timing->lpddr5_bl_n_max_tck= 2;          
      }
    }

    if(dvfsc_enable == 1) {
       if(x16==1) {
           if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1){
               switch (l_lpddr5_data_rate[p] ) {
                   case DWC_LPDDR5_533:
                       timing->lpddr5_rl_tck= 6;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=6;
                       break;
                   case DWC_LPDDR5_1066:
                       timing->lpddr5_rl_tck=(read_dbi==0)?8:10;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0)?0:2;
                       timing->lpddr5_wckpre_toggle_rd_tck=7;
                       break;
                   case DWC_LPDDR5_1600 :
                       timing->lpddr5_rl_tck=12;
                       timing->lpddr5_wckenl_rd_tck=3;
                       timing->lpddr5_wckpre_toggle_rd_tck=8;
                       break;
                   default:
                       ERROR_MESSAGE(("Error: lpddr5_set_default_timing RL () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                       break;
               }
           } else {
               // x16 DWC_WCKCK_4_1
               
               switch (l_lpddr5_data_rate[p] ) {
                   case DWC_LPDDR5_533:
                       timing->lpddr5_rl_tck=3;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=3;
                       break;
                   case DWC_LPDDR5_1066:
                       timing->lpddr5_rl_tck=(read_dbi==0)?4:5;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0)?0:1;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   case DWC_LPDDR5_1600 :
                       timing->lpddr5_rl_tck=6;
                       timing->lpddr5_wckenl_rd_tck=2;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   default:
                       ERROR_MESSAGE(("Error: lpddr5_set_default_timing x16 DWC_WCKCK_4_1 RL () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                       break;
               }                  
           }

       } // X16 
       else {
           // X8
           if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1){
               switch (l_lpddr5_data_rate[p] ) {
                   case DWC_LPDDR5_533:
                       timing->lpddr5_rl_tck= 6;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=6;
                       break;
                   case DWC_LPDDR5_1066:
                       timing->lpddr5_rl_tck=10;
                       timing->lpddr5_wckenl_rd_tck=2;
                       timing->lpddr5_wckpre_toggle_rd_tck=7;
                       break;
                   case DWC_LPDDR5_1600 :
                       timing->lpddr5_rl_tck=(read_dbi==0) ? 12: 14;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0)?3: 5;
                       timing->lpddr5_wckpre_toggle_rd_tck=8;
                       break;
                   default:
                       ERROR_MESSAGE(("Error: lpddr5_set_default_timing x8 RL () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                       break;
               }
           } else {
               // x8 DWC_WCKCK_4_1
               
               switch (l_lpddr5_data_rate[p] ) {
                   case DWC_LPDDR5_533:
                       timing->lpddr5_rl_tck= 3;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=3;
                       break;
                   case DWC_LPDDR5_1066:
                       timing->lpddr5_rl_tck= 5;
                       timing->lpddr5_wckenl_rd_tck=1;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   case DWC_LPDDR5_1600 :
                       timing->lpddr5_rl_tck= (read_dbi==0) ? 6 : 7;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0)?2:3;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   default:
                       ERROR_MESSAGE(("Error: lpddr5_set_default_timing x8 RL () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                       break;

               }                  
           }               
       }
    }
    else {
    // 
    // READ LATENCIES (DVFSC disabled first)
    //
       if(x16==1) {
           if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1){
               switch (l_lpddr5_data_rate[p] ) {
                   case DWC_LPDDR5_533:
                       timing->lpddr5_rl_tck= 6;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=6;
                       break;
                   case DWC_LPDDR5_1066:
                       timing->lpddr5_rl_tck=8;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=7;
                       break;
                   case DWC_LPDDR5_1600 :
                       timing->lpddr5_rl_tck=10;
                       timing->lpddr5_wckenl_rd_tck=1;
                       timing->lpddr5_wckpre_toggle_rd_tck=8;
                       break;
                   case DWC_LPDDR5_2133:
                       timing->lpddr5_rl_tck= (read_dbi==0) ?12:14;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0)
                           ?2:4;
                       timing->lpddr5_wckpre_toggle_rd_tck=8;
                       break;
                   case DWC_LPDDR5_2710:
                       timing->lpddr5_rl_tck=16;
                       timing->lpddr5_wckenl_rd_tck=3;
                       timing->lpddr5_wckpre_toggle_rd_tck=10;
                       break;
                   case DWC_LPDDR5_3200:
                       timing->lpddr5_rl_tck=(read_dbi==0) ?18:20;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0)?5:7;
                       timing->lpddr5_wckpre_toggle_rd_tck=10;
                       break;
                   default:
                       ERROR_MESSAGE(("Error: lpddr5_set_default_timing RL () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                       break;
               }
           } else {
               // x16 DWC_WCKCK_4_1
               
               switch (l_lpddr5_data_rate[p] ) {
                   case DWC_LPDDR5_533:
                       timing->lpddr5_rl_tck=3;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=3;
                       break;
                   case DWC_LPDDR5_1066:
                       timing->lpddr5_rl_tck=4;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   case DWC_LPDDR5_1600 :
                       timing->lpddr5_rl_tck=5;
                       timing->lpddr5_wckenl_rd_tck=1;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   case DWC_LPDDR5_2133:
                       timing->lpddr5_rl_tck=(read_dbi==0)?6:7;
                       timing->lpddr5_wckenl_rd_tck=
                           (read_dbi==0)?1:2;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   case DWC_LPDDR5_2710:
                       timing->lpddr5_rl_tck= 8;
                       timing->lpddr5_wckenl_rd_tck= 2;
                       timing->lpddr5_wckpre_toggle_rd_tck=5;
                       break;
                   case DWC_LPDDR5_3200:
                       timing->lpddr5_rl_tck= (read_dbi==0)?9: 10;
                       timing->lpddr5_wckenl_rd_tck=
                           (read_dbi==0)?3:4;
                       timing->lpddr5_wckpre_toggle_rd_tck=5;
                       break;
                   case DWC_LPDDR5_3733:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 10: 11;
                           timing->lpddr5_wckenl_rd_tck= (read_dbi==0)
                           ?3: 4;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 12;
                           timing->lpddr5_wckenl_rd_tck= 5;
                       }
                       timing->lpddr5_wckpre_toggle_rd_tck=5;
                       break;
                   case DWC_LPDDR5_4266:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 12: 13;
                           timing->lpddr5_wckenl_rd_tck= (read_dbi==0) ?
                           4: 5;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 13;
                           timing->lpddr5_wckenl_rd_tck= 5;
                       }
                       timing->lpddr5_wckpre_toggle_rd_tck=6;

                       break;
                   case DWC_LPDDR5_4800:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 13: 14;
                           timing->lpddr5_wckenl_rd_tck= (read_dbi==0) ?
                           5: 6;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 15;
                           timing->lpddr5_wckenl_rd_tck= 7;
                       }
                       timing->lpddr5_wckpre_toggle_rd_tck=6;

                       break;
                   case DWC_LPDDR5_5420:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 15: 16;
                           timing->lpddr5_wckenl_rd_tck= (read_dbi==0) ?
                           6: 7;
                       } else {
                       timing->lpddr5_wckpre_toggle_rd_tck=6;
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 17;
                           timing->lpddr5_wckenl_rd_tck= 8;
                       }
                       break;
                   case DWC_LPDDR5_6000:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 16: 17;
                           timing->lpddr5_wckenl_rd_tck= (read_dbi==0) ?
                           6: 7;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 18;
                           timing->lpddr5_wckenl_rd_tck= 8;
                       }
                       timing->lpddr5_wckpre_toggle_rd_tck=7;
                       break;
                   case DWC_LPDDR5_6400:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 17: 18;
                           timing->lpddr5_wckenl_rd_tck= (read_dbi==0) ?
                           7: 8;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 19;
                           timing->lpddr5_wckenl_rd_tck= 9;
                       }
                       timing->lpddr5_wckpre_toggle_rd_tck=7;
                       break;
                   default:
                       ERROR_MESSAGE(("Error: lpddr5_set_default_timing x16 DWC_WCKCK_4_1 RL () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                       break;
               }                  
           }

       } // X16 
       else {
           // X8
           if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1){
               switch (l_lpddr5_data_rate[p] ) {
                   case DWC_LPDDR5_533:
                       timing->lpddr5_rl_tck= 6;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=6;
                       break;
                   case DWC_LPDDR5_1066:
                       timing->lpddr5_rl_tck=8;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=7;
                       break;
                   case DWC_LPDDR5_1600 :
                       timing->lpddr5_rl_tck=(read_dbi==0) ? 10: 12;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0) ?
                           1: 3;
                       timing->lpddr5_wckpre_toggle_rd_tck=8;
                       break;
                   case DWC_LPDDR5_2133:
                       timing->lpddr5_rl_tck= 14;
                       timing->lpddr5_wckenl_rd_tck=4;
                       timing->lpddr5_wckpre_toggle_rd_tck=8;
                       
                       break;
                   case DWC_LPDDR5_2710:
                       timing->lpddr5_rl_tck=(read_dbi==0) ? 16 :18;
                       timing->lpddr5_wckenl_rd_tck= (read_dbi==0) ?
                           3:5;
                       timing->lpddr5_wckpre_toggle_rd_tck=10;
                       break;
                   case DWC_LPDDR5_3200:
                       timing->lpddr5_rl_tck= 20;
                       timing->lpddr5_wckenl_rd_tck=7;
                       timing->lpddr5_wckpre_toggle_rd_tck=10;
                       break;
                   default:
                       ERROR_MESSAGE(("Error: lpddr5_set_default_timing x8 RL () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                       break;
               }
           } else {
               // x8 DWC_WCKCK_4_1
               
               switch (l_lpddr5_data_rate[p] ) {
                   case DWC_LPDDR5_533:
                       timing->lpddr5_rl_tck= 3;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=3;
                       break;
                   case DWC_LPDDR5_1066:
                       timing->lpddr5_rl_tck= 4;
                       timing->lpddr5_wckenl_rd_tck=0;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   case DWC_LPDDR5_1600 :
                       timing->lpddr5_rl_tck= (read_dbi==0) ? 5 : 6;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0)
                           ? 1 :2 ;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       break;
                   case DWC_LPDDR5_2133:
                       timing->lpddr5_rl_tck= 7;
                       timing->lpddr5_wckenl_rd_tck=2;
                       timing->lpddr5_wckpre_toggle_rd_tck=4;
                       
                       break;
                   case DWC_LPDDR5_2710:
                       timing->lpddr5_rl_tck= (read_dbi==0) ? 8 : 9;
                       timing->lpddr5_wckenl_rd_tck=(read_dbi==0) ?
                           2:3;
                       timing->lpddr5_wckpre_toggle_rd_tck=5;
                       break;
                   case DWC_LPDDR5_3200:
                       timing->lpddr5_rl_tck=10;
                       timing->lpddr5_wckenl_rd_tck=4;
                       timing->lpddr5_wckpre_toggle_rd_tck=5;
                       break;
                   case DWC_LPDDR5_3733:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 11: 12;
                           timing->lpddr5_wckenl_rd_tck=(read_dbi==0)
                               ? 4 : 5;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 13;
                           timing->lpddr5_wckenl_rd_tck= 6;
                       }
                       timing->lpddr5_wckpre_toggle_rd_tck=5;
                       break;
                   case DWC_LPDDR5_4266:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 13: 14;
                           timing->lpddr5_wckenl_rd_tck=(read_dbi==0)
                               ? 5 : 6;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 14;
                           timing->lpddr5_wckenl_rd_tck= 6;
                       }
                       timing->lpddr5_wckpre_toggle_rd_tck=6;
                       break;
                   case DWC_LPDDR5_4800:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 14: 15;
                           timing->lpddr5_wckenl_rd_tck=(read_dbi==0)
                               ? 6 : 7;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 16;
                           timing->lpddr5_wckenl_rd_tck= 8;
                       }

                       timing->lpddr5_wckpre_toggle_rd_tck=6;
                       break;
                   case DWC_LPDDR5_5420:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 16: 17;
                           timing->lpddr5_wckenl_rd_tck=(read_dbi==0)
                               ? 7 : 8;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 18;
                           timing->lpddr5_wckenl_rd_tck= 9;
                       }
                       timing->lpddr5_wckpre_toggle_rd_tck=6;
                       break;
                   case DWC_LPDDR5_6000:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 17: 19;
                           timing->lpddr5_wckenl_rd_tck=(read_dbi==0)
                               ? 7 :9;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 20;
                           timing->lpddr5_wckenl_rd_tck= 10;
                       }

                       timing->lpddr5_wckpre_toggle_rd_tck=7;
                       break;
                   case DWC_LPDDR5_6400:
                       if(rd_lecc == 0) {
                           timing->lpddr5_rl_tck= (read_dbi==0) ? 18: 20;
                           timing->lpddr5_wckenl_rd_tck=(read_dbi==0)
                               ? 8: 10;
                       } else {
                           // Link-ECC is enabled.
                           timing->lpddr5_rl_tck= 21;
                           timing->lpddr5_wckenl_rd_tck= 11;
                       }

                       timing->lpddr5_wckpre_toggle_rd_tck=7;
                       break;
                   default:
                       ERROR_MESSAGE(("Error: lpddr5_set_default_timing x8 RL () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                       break;

               }                  
           }               
       }
    }



       // self checker

  CONSTRAIN_INSIDE(timing->lpddr5_rl_tck , 3, 21); 

    if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
        switch (l_lpddr5_data_rate[p] ) {
            case DWC_LPDDR5_533:
                timing->lpddr5_nrtp= 4;
                break;
            case DWC_LPDDR5_1066:
                timing->lpddr5_nrtp= 4;
                break;
            case DWC_LPDDR5_1600 :
                timing->lpddr5_nrtp= 4;
                break;
            case DWC_LPDDR5_2133:
                timing->lpddr5_nrtp= 4;
                break;
            case DWC_LPDDR5_2710:
                timing->lpddr5_nrtp= 6;
                break;
            case DWC_LPDDR5_3200:
                timing->lpddr5_nrtp= 6;
                break;
            default:
                ERROR_MESSAGE(("Error: lpddr5_set_default_timing x8 RL () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                break;
        }
        
    } else {
        // 4:1
       switch (l_lpddr5_data_rate[p] ) {
            case DWC_LPDDR5_533:
                timing->lpddr5_nrtp= 2;
                break;
            case DWC_LPDDR5_1066:
                timing->lpddr5_nrtp= 2;
                break;
            case DWC_LPDDR5_1600 :
                timing->lpddr5_nrtp= 2;
                break;
            case DWC_LPDDR5_2133:
                timing->lpddr5_nrtp= 2;
                break;
            case DWC_LPDDR5_2710:
                timing->lpddr5_nrtp= 3;
                break;
            case DWC_LPDDR5_3200:
                timing->lpddr5_nrtp= 3;
                break;
             case DWC_LPDDR5_3733:
                timing->lpddr5_nrtp= 4;
                break;
            case DWC_LPDDR5_4266:
                timing->lpddr5_nrtp= 4;
                break;
            case DWC_LPDDR5_4800:
                timing->lpddr5_nrtp= 5;
                break;
            case DWC_LPDDR5_5420:
                timing->lpddr5_nrtp= 6;
                break;
            case DWC_LPDDR5_6000:
                timing->lpddr5_nrtp= 6;
                break;
            case DWC_LPDDR5_6400:
                timing->lpddr5_nrtp= 6;
                break;   
            default:
                ERROR_MESSAGE(("Error: lpddr5_set_default_timing nRTP ()-unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                break;
        }
    }
    // 
    // WRITE LATENCIES
    //
    if(dvfsc_enable == 1) {
       if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
           // 2:1        
           switch (l_lpddr5_data_rate[p] ) {
               case DWC_LPDDR5_533:
                   timing->lpddr5_wl_tck= 4;
                   timing->lpddr5_wckenl_wr_tck=0;
                   break;
               case DWC_LPDDR5_1066:
                   timing->lpddr5_wl_tck= (wl_seta) ? 4 : 6;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 0 : 2;
                   break;
               case DWC_LPDDR5_1600 :
                   timing->lpddr5_wl_tck= (wl_seta) ? 6 : 8;
                   timing->lpddr5_wckenl_wr_tck= (wl_seta) ? 1 : 2;
                   break;
               default:
                   ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                   break;
             } 
           } else {
           // 4:1
           switch (l_lpddr5_data_rate[p] ) {
               case DWC_LPDDR5_533:
                   timing->lpddr5_wl_tck= 2;
                   timing->lpddr5_wckenl_wr_tck=0;
                   break;
               case DWC_LPDDR5_1066:
                   timing->lpddr5_wl_tck= (wl_seta) ? 2 : 3;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 0 : 1;
                   break;
               case DWC_LPDDR5_1600 :
                   timing->lpddr5_wl_tck= (wl_seta) ? 3: 4;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 1 : 2;
                   break;
               default:
                   ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                   break;

           }
       }
    }
    else {
       if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
           // 2:1        
           switch (l_lpddr5_data_rate[p] ) {
               case DWC_LPDDR5_533:
                   timing->lpddr5_wl_tck= 4;
                   timing->lpddr5_wckenl_wr_tck=0;
                   break;
               case DWC_LPDDR5_1066:
                   timing->lpddr5_wl_tck= (wl_seta) ? 4 : 6;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 0 : 2;
                   break;
               case DWC_LPDDR5_1600 :
                   timing->lpddr5_wl_tck= (wl_seta) ? 6 : 8;
                   timing->lpddr5_wckenl_wr_tck= (wl_seta) ? 1 : 2;
                   break;
               case DWC_LPDDR5_2133:
                   timing->lpddr5_wl_tck= (wl_seta) ? 8 : 10;
                   timing->lpddr5_wckenl_wr_tck= (wl_seta) ? 2 : 4;
                   break;
               case DWC_LPDDR5_2710:
                   timing->lpddr5_wl_tck= (wl_seta) ? 8 : 14;
                   timing->lpddr5_wckenl_wr_tck= (wl_seta) ? 1 : 7;
                   break;
               case DWC_LPDDR5_3200:
                   timing->lpddr5_wl_tck= (wl_seta) ? 10 : 16;
                   timing->lpddr5_wckenl_wr_tck= (wl_seta) ? 3 : 9;
                   break;
               default:
                   ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                   break;
             } 
           } else {
           // 4:1
           switch (l_lpddr5_data_rate[p] ) {
               case DWC_LPDDR5_533:
                   timing->lpddr5_wl_tck= 2;
                   timing->lpddr5_wckenl_wr_tck=0;
                   break;
               case DWC_LPDDR5_1066:
                   timing->lpddr5_wl_tck= (wl_seta) ? 2 : 3;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 0 : 1;
                   break;
               case DWC_LPDDR5_1600 :
                   timing->lpddr5_wl_tck= (wl_seta) ? 3: 4;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 1 : 2;
                   break;
               case DWC_LPDDR5_2133:
                   timing->lpddr5_wl_tck= (wl_seta) ? 4: 5;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 1 : 2;
                   break;
               case DWC_LPDDR5_2710:
                   timing->lpddr5_wl_tck= (wl_seta) ? 4: 7;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 1 : 4;
                   break;
               case DWC_LPDDR5_3200:
                   timing->lpddr5_wl_tck= (wl_seta) ? 5: 8;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 2 : 5;
                   break;
               case DWC_LPDDR5_3733:
                   timing->lpddr5_wl_tck= (wl_seta) ? 6: 9;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 2 : 5;
                   break;
               case DWC_LPDDR5_4266:
                   timing->lpddr5_wl_tck= (wl_seta) ? 6: 11;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 2 : 7;
                   break;
               case DWC_LPDDR5_4800:
                   timing->lpddr5_wl_tck= (wl_seta) ? 7: 12;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 3 : 8;
                   break;
               case DWC_LPDDR5_5420:
                   timing->lpddr5_wl_tck= (wl_seta) ? 8: 14;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 3 : 9;
                   break;
               case DWC_LPDDR5_6000:
                   timing->lpddr5_wl_tck= (wl_seta) ? 9: 15;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 4 : 10;
                   break;
               case DWC_LPDDR5_6400:
                   timing->lpddr5_wl_tck= (wl_seta) ? 9: 16;
                   timing->lpddr5_wckenl_wr_tck=(wl_seta) ? 4 : 11;
                   break;
               default:
                   ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                   break;

           }
       }
    }

    // 
    // tWCKENL_FS
    //
    if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
        // 2:1        
        switch (l_lpddr5_data_rate[p] ) {
            case DWC_LPDDR5_533:
                timing->lpddr5_wckenl_fs_tck = 0;
                break;
            case DWC_LPDDR5_1066:
                timing->lpddr5_wckenl_fs_tck = 0;
                break;
            case DWC_LPDDR5_1600 :
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_2133:
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_2710:
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_3200:
                timing->lpddr5_wckenl_fs_tck = 2;
                break;
            default:
                ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                break;
          } 
        } else {
        // 4:1
        switch (l_lpddr5_data_rate[p] ) {
            case DWC_LPDDR5_533:
                timing->lpddr5_wckenl_fs_tck = 0;
                break;
            case DWC_LPDDR5_1066:
                timing->lpddr5_wckenl_fs_tck = 0;
                break;
            case DWC_LPDDR5_1600 :
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_2133:
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_2710:
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_3200:
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_3733:
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_4266:
                timing->lpddr5_wckenl_fs_tck = 1;
                break;
            case DWC_LPDDR5_4800:
                timing->lpddr5_wckenl_fs_tck = 2;
                break;
            case DWC_LPDDR5_5420:
                timing->lpddr5_wckenl_fs_tck = 2;
                break;
            case DWC_LPDDR5_6000:
                timing->lpddr5_wckenl_fs_tck = 2;
                break;
            case DWC_LPDDR5_6400:
                timing->lpddr5_wckenl_fs_tck = 2;
                break;
            default:
                ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                break;

        }
    }

    // 
    // nWR LATENCIES
    //
    if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
        // 2:1        
        switch (l_lpddr5_data_rate[p] ) {
            case DWC_LPDDR5_533:
                timing->lpddr5_nwr= (dvfsc_enable) ? ((x16) ? 6 : 6) : ((x16) ? 5 : 5);
                break;
            case DWC_LPDDR5_1066:
                timing->lpddr5_nwr= (dvfsc_enable) ? ((x16) ? 11 : 12) : ((x16) ? 10 : 10);
                break;
            case DWC_LPDDR5_1600 :
                timing->lpddr5_nwr= (dvfsc_enable) ? ((x16) ? 17 : 18) : ((x16) ? 14 : 15);
                break;
            case DWC_LPDDR5_2133:
                timing->lpddr5_nwr= (x16) ? 19 : 20;
                break;
            case DWC_LPDDR5_2710:
                timing->lpddr5_nwr= (x16) ? 24 : 25;
                break;
            case DWC_LPDDR5_3200:
                timing->lpddr5_nwr= (x16) ? 28 : 29;
                break;
            default:
                ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                break;
          } 
        } else {
        // 4:1
        switch (l_lpddr5_data_rate[p] ) {
            case DWC_LPDDR5_533:
                timing->lpddr5_nwr= (dvfsc_enable) ? ((x16) ? 3 : 3) : ((x16) ? 3 : 3);
                break;
            case DWC_LPDDR5_1066:
                timing->lpddr5_nwr= (dvfsc_enable) ? ((x16) ? 6 : 6) : ((x16) ? 5 : 5);
                break;
            case DWC_LPDDR5_1600 :
                timing->lpddr5_nwr= (dvfsc_enable) ? ((x16) ? 9 : 9) : ((x16) ? 7 : 8);
                break;
            case DWC_LPDDR5_2133:
                timing->lpddr5_nwr= (x16) ? 10 : 10;
                break;
            case DWC_LPDDR5_2710:
                timing->lpddr5_nwr= (x16) ? 12 : 13;
                break;
            case DWC_LPDDR5_3200:
                timing->lpddr5_nwr= (x16) ? 14 : 15;
                break;
            case DWC_LPDDR5_3733:
                timing->lpddr5_nwr= (rd_lecc == 0) ? ((x16) ? 16 : 17) : ((x16) ? 18 : 19);
                break;
            case DWC_LPDDR5_4266:
                timing->lpddr5_nwr= (rd_lecc == 0) ? ((x16) ? 19 : 20) : ((x16) ? 21 : 22);
                break;
            case DWC_LPDDR5_4800:
                timing->lpddr5_nwr= (rd_lecc == 0) ? ((x16) ? 21 : 22) : ((x16) ? 23 : 24);
                break;
            case DWC_LPDDR5_5420:
                timing->lpddr5_nwr= (rd_lecc == 0) ? ((x16) ? 24 : 25) : ((x16) ? 27 : 28);
                break;
            case DWC_LPDDR5_6000:
                timing->lpddr5_nwr= (rd_lecc == 0) ? ((x16) ? 26 : 28) : ((x16) ? 29 : 31);
                break;
            case DWC_LPDDR5_6400:
                timing->lpddr5_nwr= (rd_lecc == 0) ? ((x16) ? 28 : 29) : ((x16) ? 31 : 32);
                break;
            default:
                ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                break;

        }
    }
    // 
    // WCKPRE and WCKENL_RD
    //
    if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
        // 2:1        
        switch (l_lpddr5_data_rate[p] ) {
            case DWC_LPDDR5_533:
                timing->lpddr5_wckpre_static_tck= 1;
                timing->lpddr5_wckpre_toggle_wr_tck=3 ;
                break;
            case DWC_LPDDR5_1066:
                timing->lpddr5_wckpre_static_tck= 2;
                timing->lpddr5_wckpre_toggle_wr_tck= 3;              
                break;
            case DWC_LPDDR5_1600 :
                timing->lpddr5_wckpre_static_tck= 2;
                timing->lpddr5_wckpre_toggle_wr_tck= 4;                
                break;
            case DWC_LPDDR5_2133:
                timing->lpddr5_wckpre_static_tck= 3;
                timing->lpddr5_wckpre_toggle_wr_tck= 4;                
                break;
            case DWC_LPDDR5_2710:
                timing->lpddr5_wckpre_static_tck= 4;
                timing->lpddr5_wckpre_toggle_wr_tck= 4;                
                break;
            case DWC_LPDDR5_3200:
                timing->lpddr5_wckpre_static_tck= 4;
                timing->lpddr5_wckpre_toggle_wr_tck= 4;                
                break;
            default:
                ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
                break;
          } 
        } else {
        // 4:1
        switch (l_lpddr5_data_rate[p] ) {
            case DWC_LPDDR5_533:
                timing->lpddr5_wckpre_static_tck= 1;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                
                break;
            case DWC_LPDDR5_1066:
                timing->lpddr5_wckpre_static_tck= 1;
                timing->lpddr5_wckpre_toggle_wr_tck=2;   
                break;
            case DWC_LPDDR5_1600 :
                 timing->lpddr5_wckpre_static_tck= 1;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                  
                break;
            case DWC_LPDDR5_2133:
                timing->lpddr5_wckpre_static_tck= 2;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                   
                break;
            case DWC_LPDDR5_2710:
                timing->lpddr5_wckpre_static_tck= 2;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                  
                break;
            case DWC_LPDDR5_3200:
                timing->lpddr5_wckpre_static_tck= 2;
                timing->lpddr5_wckpre_toggle_wr_tck=2;  
                break;
            case DWC_LPDDR5_3733:
                timing->lpddr5_wckpre_static_tck= 3;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                
                break;
            case DWC_LPDDR5_4266:
                timing->lpddr5_wckpre_static_tck= 3;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                 
                break;
            case DWC_LPDDR5_4800:
                timing->lpddr5_wckpre_static_tck= 3;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                
                break;
            case DWC_LPDDR5_5420:
                timing->lpddr5_wckpre_static_tck= 4;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                 
                break;
            case DWC_LPDDR5_6000:
                timing->lpddr5_wckpre_static_tck= 4;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                  
                break;
            case DWC_LPDDR5_6400:
                timing->lpddr5_wckpre_static_tck= 4;
                timing->lpddr5_wckpre_toggle_wr_tck=2;                  
                break;
            default:
                ERROR_MESSAGE(("Error: lpddr5_set_default_timing () -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
                break;

        }
    }
    switch(hdlr->memCtrlr_m.lpddr5_mr[p].mr10.wck_pst) {
        case 0:  timing->lpddr5_twck_pst_wck =2; break; // RD(2.5)
        case 1:  timing->lpddr5_twck_pst_wck=4; break; // RD(4.5)
        case 2:  timing->lpddr5_twck_pst_wck=6; break; // RD(6.5)
        default: ERROR_MESSAGE(("Unknown wck_pst (%0d) value",hdlr->memCtrlr_m.lpddr5_mr[p].mr10.wck_pst )); break;
    }
    if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
      timing->lpddr5_nrbtp_ps = max(7500, 4*tck_ps ) - 4*tck_ps;
    } else {
      timing->lpddr5_nrbtp_ps = max(7500, 2*tck_ps ) - 2*tck_ps;
    }
}

//Map tck_ps to local variables l_lpddr5/4_data_rate and l_ddr5/4_data_rate
void dwc_cinit_map_tck_ps_to_data_rate(SubsysHdlr_t* hdlr)
{
  TRACE();
  ddrSpdData_t* spd = &hdlr->spdData_m;
  LOG_MESSAGE(hdlr, 0, ("sdram_protocol=%d\n", spd->sdram_protocol));
  switch(spd->sdram_protocol) {
    case DWC_LPDDR4: map_tck_ps_to_l_lpddr4_data_rate(hdlr); break;  
    case DWC_LPDDR5: map_tck_ps_to_l_lpddr5_data_rate(hdlr); break; 
    default: ERROR_MESSAGE(("sdram_protocol=%0d not yet supported. ",spd->sdram_protocol)); break;
  }
}

//Map tck_ps to l_lpddr4_data_rate
dwc_lpddr4_data_rate_e map_tck_ps_to_l_lpddr4_data_rate(SubsysHdlr_t* hdlr) {
  TRACE();

  for(uint32_t p = 0; p < UMCTL2_FREQUENCY_NUM; p = p + 1) {
    switch(hdlr->spdData_m.tck_ps[p]) {
      case 3750 ... 3753 : l_lpddr4_data_rate[p] = DWC_LPDDR4_533;  break;
      case 1875 ... 3749 : l_lpddr4_data_rate[p] = DWC_LPDDR4_1066; break;
      case 1250 ... 1874 : l_lpddr4_data_rate[p] = DWC_LPDDR4_1600; break;
      case 938  ... 1249 : l_lpddr4_data_rate[p] = DWC_LPDDR4_2133; break;
      case 750  ... 937  : l_lpddr4_data_rate[p] = DWC_LPDDR4_2667; break;
      case 625  ... 749  : l_lpddr4_data_rate[p] = DWC_LPDDR4_3200; break;
      case 536  ... 624  : l_lpddr4_data_rate[p] = DWC_LPDDR4_3733; break;
      case 467  ... 535  : l_lpddr4_data_rate[p] = DWC_LPDDR4_4267; break;               // 1/((4267/2)*10^6) = 468.71ps
      default: ERROR_MESSAGE(("Invalid tck_ps[%0d] = %0d not supported",p,hdlr->spdData_m.tck_ps[p]));
    }
    dwc_cinit_print("map_tck_ps_to_l_lpddr4_data_rate:: tck_ps[%0d] = %0dps and l_lpddr4_data_rate[%0d] = 'd%0d\n",p,hdlr->spdData_m.tck_ps[p],p,l_lpddr4_data_rate[p]);
  }
}

//Map tck_ps to l_lpddr5_data_rate
dwc_lpddr5_data_rate_e map_tck_ps_to_l_lpddr5_data_rate(SubsysHdlr_t* hdlr) {
  TRACE();
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  uint32_t wckck_4_1 = (spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) ? 1 : 0;

  for(uint32_t p = 0; p < UMCTL2_FREQUENCY_NUM; p = p + 1) {
    if(wckck_4_1 && (hdlr->spdData_m.tck_ps[p] >= 2140 && hdlr->spdData_m.tck_ps[p] <= 15009)) {
      switch(hdlr->spdData_m.tck_ps[p]) {
        case 15009 ... 15010 : l_lpddr5_data_rate[p] = DWC_LPDDR5_533;  break;
        case 7520  ... 15008 : l_lpddr5_data_rate[p] = DWC_LPDDR5_1066; break;        //TODO 1/((1066/8)*10^6) = 7504.69ps
        case 5000  ... 7519  : l_lpddr5_data_rate[p] = DWC_LPDDR5_1600; break;
        case 3745  ... 4999  : l_lpddr5_data_rate[p] = DWC_LPDDR5_2133; break;
        case 2950  ... 3744  : l_lpddr5_data_rate[p] = DWC_LPDDR5_2710; break;
        case 2500  ... 2949  : l_lpddr5_data_rate[p] = DWC_LPDDR5_3200; break;
        case 2140  ... 2499  : l_lpddr5_data_rate[p] = DWC_LPDDR5_3733; break;        
        default: ERROR_MESSAGE(("Invalid tck_ps[%0d] = %0d",p,hdlr->spdData_m.tck_ps[p]));
      }
    }
    else if(wckck_4_1 == 0 && (hdlr->spdData_m.tck_ps[p] >= 1250 && hdlr->spdData_m.tck_ps[p] <= 7520)) {
      switch(hdlr->spdData_m.tck_ps[p]) {
        case 7505 ... 7520 : l_lpddr5_data_rate[p] = DWC_LPDDR5_533;  break;           //TODO 1/((533/4)*10^6) = 7504.69ps
        case 3745 ... 7504 : l_lpddr5_data_rate[p] = DWC_LPDDR5_1066; break;   
        case 2500 ... 3744 : l_lpddr5_data_rate[p] = DWC_LPDDR5_1600; break; 
        case 1876 ... 2499 : l_lpddr5_data_rate[p] = DWC_LPDDR5_2133; break;
        case 1475 ... 1875 : l_lpddr5_data_rate[p] = DWC_LPDDR5_2710; break;
        case 1250 ... 1474 : l_lpddr5_data_rate[p] = DWC_LPDDR5_3200; break;
        default: ERROR_MESSAGE(("Inv5lid tck_ps[%0d] = %0d",p,hdlr->spdData_m.tck_ps[p]));
      }
    }
    else {
      switch(hdlr->spdData_m.tck_ps[p]) {
        case 1876 ... 2139 : l_lpddr5_data_rate[p] = DWC_LPDDR5_4266; break; 
        case 1667 ... 1875 : l_lpddr5_data_rate[p] = DWC_LPDDR5_4800; break; 
        case 1474 ... 1666 : l_lpddr5_data_rate[p] = DWC_LPDDR5_5420; break;
        case 1333 ... 1473 : l_lpddr5_data_rate[p] = DWC_LPDDR5_6000; break;
        case 1250 ... 1332 : l_lpddr5_data_rate[p] = DWC_LPDDR5_6400; break;
        default: ERROR_MESSAGE(("Invalid tck_ps[%0d] = %0d",p,hdlr->spdData_m.tck_ps[p]));
      }
    }
    dwc_cinit_print("map_tck_ps_to_l_lpddr5_data_rate:: tck_ps[%0d] = %0dps and l_lpddr5_data_rate[%0d] = 'd%0d\n",p,hdlr->spdData_m.tck_ps[p],p,l_lpddr5_data_rate[p]);
  }
}

uint32_t dwc_cinit_get_lpddr4_trfcab(SubsysHdlr_t* hdlr) {
  TRACE();
  uint32_t ret;
  uint32_t sdram_capacity_mbits = hdlr->spdData_m.sdram_capacity_mbits;
  if(sdram_capacity_mbits == 2048) {ret=130000;} 
  else if (sdram_capacity_mbits <= 4096) {ret=180000; }     
  else if (sdram_capacity_mbits <= 6144) {ret=280000; }     
  else if (sdram_capacity_mbits <= 8192) {ret=280000; } 
  else {ret=380000; }
  return ret;
}


uint32_t dwc_cinit_get_lpddr5_trfcab(SubsysHdlr_t* hdlr) {
  TRACE();
  uint32_t ret;
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  if (spd->sdram_capacity_mbits == 2048) {ret=130000;}
  else if (spd->sdram_capacity_mbits == 3072) {ret=180000;}
  else if (spd->sdram_capacity_mbits == 4096) {ret=180000;}
  else if (spd->sdram_capacity_mbits == 6144) {ret=280000;}
  else {
    ret=280000; // other sizes are TBD
  }
 return ret; 
}


uint32_t dwc_cinit_get_lpddr5_trfcpb(SubsysHdlr_t* hdlr) {
  TRACE();
  uint32_t ret;
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  if (spd->sdram_capacity_mbits == 2048) {ret=60000;}
  else if (spd->sdram_capacity_mbits == 3072) {ret=90000;}
  else if (spd->sdram_capacity_mbits == 4096) {ret=90000;}
  else if (spd->sdram_capacity_mbits == 6144) {ret=140000;}
  else {
    ret=140000; // other sizes are TBD
  }
 return ret; 
}


uint32_t dwc_cinit_get_lpddr5_tpbr2pbr(SubsysHdlr_t* hdlr) {
  TRACE();
  uint32_t ret;
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  if (spd->sdram_capacity_mbits == 2048) {ret=60000;}
  else if (spd->sdram_capacity_mbits == 3072) {ret=90000;}
  else if (spd->sdram_capacity_mbits == 4096) {ret=90000;}
  else if (spd->sdram_capacity_mbits == 6144) {ret=90000;}
  else {
    ret=90000; // other sizes are TBD
  }
 return ret; 
}

/** @brief function  to omplement Table 111 for ODTLon */
uint32_t cal_lpddr5_odtlon(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  uint32_t odtlon;
  if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1 ) {
    switch (l_lpddr5_data_rate[p] ) {
      case DWC_LPDDR5_533:
        odtlon=pre_cfg->wl[p][dch]-1;
        break;
      case DWC_LPDDR5_1066:
        odtlon=pre_cfg->wl[p][dch]-2;
        break;
      case DWC_LPDDR5_1600 :
        odtlon=pre_cfg->wl[p][dch]-2;
        break;
      case DWC_LPDDR5_2133:
        odtlon=pre_cfg->wl[p][dch]-3;
        break;
      case DWC_LPDDR5_2710:
        odtlon=pre_cfg->wl[p][dch]-3;
        break;
      case DWC_LPDDR5_3200:
        odtlon=pre_cfg->wl[p][dch]-4;
        break;
      default:
        ERROR_MESSAGE(("Error: cal_lpddr5_odlton -unknown data rate = %d (WCK:CK 2:1) \n", l_lpddr5_data_rate[p]));
        break;
    }

  }
  else {
    switch (l_lpddr5_data_rate[p] ) {
      case DWC_LPDDR5_533:
        odtlon=pre_cfg->wl[p][dch]-1;
        break;
      case DWC_LPDDR5_1066:
        odtlon=pre_cfg->wl[p][dch]-1;
        break;
      case DWC_LPDDR5_1600:
        odtlon=pre_cfg->wl[p][dch]-1;
        break;
      case DWC_LPDDR5_2133:
        odtlon=pre_cfg->wl[p][dch]-2;
        break;
      case DWC_LPDDR5_2710:
        odtlon=pre_cfg->wl[p][dch]-2;
        break;
      case DWC_LPDDR5_3200:
        odtlon=pre_cfg->wl[p][dch]-2;
        break;
      case DWC_LPDDR5_3733:
        odtlon=pre_cfg->wl[p][dch]-2;
        break;
      case DWC_LPDDR5_4266:
        odtlon=pre_cfg->wl[p][dch]-3;
        break;
      case DWC_LPDDR5_4800:
        odtlon=pre_cfg->wl[p][dch]-3;
        break;
      case DWC_LPDDR5_5420:
        odtlon=pre_cfg->wl[p][dch]-3;
        break;
      case DWC_LPDDR5_6000:
        odtlon=pre_cfg->wl[p][dch]-3;
        break;
      case DWC_LPDDR5_6400:
        odtlon=pre_cfg->wl[p][dch]-3;
        break;
      default:
        ERROR_MESSAGE(("Error: cal_lpddr5_odtlon -unknown data rate = %d (WCK:CK 4:1) \n", l_lpddr5_data_rate[p]));
        break;
    }

  }

  return odtlon;
}
/** @brief helper method to return Tras max for LPDDR5 
 * refesh_rate refers to MR4.OP[4:0] */
float cinit_get_lpddr5_tras_max(SubsysHdlr_t *hdlr, uint32_t trefi_ps, uint32_t refesh_rate,uint32_t p ) {
  float tras_max_ps;
  uint32_t refresh;
  TRACE();
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  switch(refesh_rate) {
    case 1 : refresh=8;break;
    case 2 : refresh=6;break;
    case 3 : refresh=4;break;
    case 4 : refresh=3.3;break;
    case 5 : refresh=2.5;break;
    case 6 : refresh=2.0;break;
    case 7 : refresh=1.7;break;
    case 8 : refresh=1.3;break;
    case 9 : refresh=1.0;break;
    case 10 : refresh=0.7;break;
    case 11 : refresh=0.5;break;
    case 12 : refresh=0.25;break;
    case 13 : refresh=0.25;break;
    case 14 : refresh=0.125;break;
    case 15 : refresh=0.125;break;
    default : dwc_cinit_print("cinit_get_lpddr5_tras_max: MR4.OP[4:0] not supported using nominal refresh rate (x1).");refresh=1;break;
  }
  tras_max_ps=min(9*trefi_ps*refresh,timing->lpddr5_tras_max_ps);
  dwc_cinit_print("trefi_ps=%0d, refesh_rate=%0d, tras_max_ps=%0d\n",trefi_ps, refesh_rate, tras_max_ps);
  return tras_max_ps;

}

#endif // MEMC_LPDDR4

