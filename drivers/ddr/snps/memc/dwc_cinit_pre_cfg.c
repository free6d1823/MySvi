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

/** @brief Do some pre-calculations before cinit_prgm_regs is called.
 * */
void cinit_pre_cfg(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  ddrSpdData_t* spd = &(hdlr->spdData_m);
#ifdef MEMC_DDR4
  uint32_t t_mod,txpdll,t_mrr,t_mrw;
#endif
#ifdef MEMC_DDR5
  ddr5_control_words_t* ddr5_cw = &(hdlr->ddr5_cw);
#endif
 mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
 uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
 uint32_t twr,tfaw, tras_max, tras_min,trtp,txp,cl, t_rc, cl_dbi;
 uint32_t twtr, t_mr;
 uint32_t ratio;

 uint32_t trcd, trrd, trp;
 cinit_cal_cwlx(hdlr, p, ch);
 // lookup the timing parameters based on the protocol enabled.
 switch(hdlr->spdData_m.sdram_protocol) {

#ifdef MEMC_DDR4     
     case DWC_DDR4 :
      twr=timing->ddr4_twr_ps;
      tfaw=timing->ddr4_tfaw_ps;
      tras_max=timing->ddr4_tras_max_ps;
      tras_min=timing->ddr4_tras_min_ps;
      trtp=timing->ddr4_trtp_ps;
      txp=timing->ddr4_txp_ps;
      txpdll=timing->ddr4_txpdll_ps;
      cl=timing->ddr4_tcl_tck;
      t_rc=timing->trc_ps;
      cl_dbi=timing->ddr4_tcl_rdbi_tck;
      twtr= (qdyn->ddr4_wr_preamble[p][ch]) ? timing->ddr4_twtr_l_tck+1 : timing->ddr4_twtr_l_tck ;
      pre_cfg->twtr_s[p][ch]= (qdyn->ddr4_wr_preamble[p][ch]) ? timing->ddr4_twtr_s_tck+1 : timing->ddr4_twtr_s_tck ;
      t_mr=timing->ddr4_tmrd_tck;
      t_mod=cinit_ps_to_tck( timing->ddr4_tmod_ps, tck_ps );
      trcd=timing->trcd_ps;
      if(timing->ddr4_tccd_l_tck==5 && qdyn->ddr4_wr_preamble[p][ch] ) {
        pre_cfg->t_ccd[p][ch]=timing->ddr4_tccd_l_tck+1;
      } else {
        pre_cfg->t_ccd[p][ch]=timing->ddr4_tccd_l_tck;
      }
      trrd=timing->trrd_l_tck;
      trp=timing->trp_ps;
      pre_cfg->t_cksre[p][ch]= cinit_ps_to_tck(10000,tck_ps);  
      pre_cfg->t_cksrx[p][ch]=2;  
      pre_cfg->t_ckesr[p][ch]=cinit_ps_to_tck(timing->ddr4_tcke_ps,tck_ps)+1; 
      if(timing->ddr4_tpl_tck!=0) {
        pre_cfg->t_ckesr[p][ch]+=timing->ddr4_tpl_tck;
      }
      pre_cfg->t_cke[p][ch]=timing->ddr4_tcke_ps;
      pre_cfg->t_mrd_pda[p][ch]= cinit_ps_to_tck(10000,tck_ps);
      // tXS_FAST
      pre_cfg->t_xs_fast_min[p][ch]=(((timing->ddr4_trfc_min4_ps+10000)/tck_ps)+timing->ddr4_cal_tck+timing->ddr4_tpl_tck)/32 +1;
      pre_cfg->t_xs_min[p][ch]= (((timing->ddr4_trfc_min_ps+10000)/tck_ps)+timing->ddr4_cal_tck+timing->ddr4_tpl_tck)/32 +1;
#ifdef UMCTL2_CID_EN
      if(GET_CID_WIDTH > 0) {
       if(timing->ddr4_tccd_dlr_tck==5 && qdyn->ddr4_wr_preamble[p][ch] ) {
         pre_cfg->t_ccd_dlr[p][ch]=timing->ddr4_tccd_dlr_tck+1;
       } else {
         pre_cfg->t_ccd_dlr[p][ch]=timing->ddr4_tccd_dlr_tck;
       }
       pre_cfg->t_rrd_dlr[p][ch] = timing->ddr4_trrd_dlr_tck;
       pre_cfg->t_faw_dlr[p][ch] = timing->ddr4_tfaw_dlr_tck;

      }        
#endif
      break;

    case DWC_DDR5:
     twr=timing->ddr5_twr_ps;
     tfaw=timing->ddr5_tfaw_tck;
     tras_max=timing->ddr5_tras_max_ps;
     tras_min=timing->ddr5_tras_min_ps;
     trtp=timing->ddr5_trtp_ps;
     txp=timing->ddr5_txp_ps;
     cl=timing->ddr5_tcl_tck; //consider the effect of dbi
     t_rc=timing->trc_ps;
     twtr=timing->ddr5_twtr_l_tck; // consider the effect of preamble, no detail in JEDEC
     pre_cfg->twtr_s[p][ch]=timing->ddr5_twtr_s_tck;// consider the effect of preamble, no detail in JEDEC
     t_mr=timing->ddr5_tmrd_tck;
     t_mrr=timing->ddr5_tmrr_tck;
     t_mrw=timing->ddr5_tmrw_tck;
         
     trcd=timing->trcd_ps;
     pre_cfg->t_ccd[p][ch] = timing->ddr5_tccd_l_tck;
     tfaw = GET_CID_WIDTH ? timing->ddr5_tfaw_slr_tck : timing->ddr5_tfaw_tck;
#ifdef UMCTL2_CID_EN
     pre_cfg->t_rrd_dlr[p][ch] = timing->ddr5_trrd_dlr_tck;
     pre_cfg->t_faw_dlr[p][ch] = timing->ddr5_tfaw_dlr_tck;
     pre_cfg->t_ccd_dlr[p][ch] = timing->ddr5_tccd_s_tck;
     pre_cfg->t_refsbrd_dlr[p][ch] = cinit_ps_to_tck(timing->ddr5_trefsbrd_dlr_ps,tck_ps);
     pre_cfg->t_rfcsb_dlr[p][ch] = cinit_ps_to_tck(timing->ddr5_trfcsb_dlr_ps,tck_ps);

#endif //UMCTL2_CID_EN
     trrd=timing->trrd_l_tck;
     trp=timing->trp_ps;
         
      // RCD Parameters
      pre_cfg->t_stab01[p][ch]    = cinit_ps_to_tck(timing->ddr5_rcd_tstab01_ps,tck_ps);
      pre_cfg->t_cssr[p][ch]      = cinit_ps_to_tck(timing->ddr5_rcd_tcssr_ps,tck_ps);
      pre_cfg->t_cpded2srx[p][ch] = timing->ddr5_rcd_tcpded2srx_tck;
      pre_cfg->t_srx2srx[p][ch]   = timing->ddr5_rcd_tsrx2srx_tck;
      pre_cfg->t_ckoff[p][ch]     = cinit_ps_to_tck(timing->ddr5_rcd_tckoff_ps,tck_ps);
      pre_cfg->t_ckact[p][ch]     = timing->ddr5_rcd_tckact_tck;
      pre_cfg->t_csalt[p][ch]     = timing->ddr5_rcd_tcsalt_tck;

     break;
#endif
#ifdef MEMC_LPDDR4
     case DWC_LPDDR4 :
         twr=timing->lpddr4_twr;
         tfaw=timing->lpddr4_tfaw;
         tras_max=timing->lpddr4_tras_max;
         tras_min=timing->lpddr4_tras_min;
         trtp=timing->lpddr4_trtp;
         txp=timing->lpddr4_txp;
         cl=timing->lpddr4_cl;
         t_rc=timing->lpddr4_trc;
         cl_dbi=timing->lpddr4_cl_dbi;
         twtr=timing->lpddr4_twtr;
         t_mr=timing->lpddr4_tmrd;
         trcd=timing->lpddr4_trcd;
         pre_cfg->t_ccd[p][ch]=timing->lpddr4_tccd;
         trrd=timing->lpddr4_trrd;
         trp=timing->lpddr4_trp;
         pre_cfg->derated_t_rcd[p][ch]=cinit_ps_to_tck(timing->lpddr4_derated_trcd, tck_ps);
         pre_cfg->derated_t_ras_min[p][ch]=cinit_ps_to_tck(timing->lpddr4_derated_tras_min, tck_ps);
         pre_cfg->derated_t_rp[p][ch]=cinit_ps_to_tck(timing->lpddr4_derated_trp, tck_ps);
         pre_cfg->derated_t_rrd[p][ch]=cinit_ps_to_tck(timing->lpddr4_derated_trrd, tck_ps);
         pre_cfg->derated_t_rc[p][ch]=cinit_ps_to_tck(timing->lpddr4_derated_trc, tck_ps);
         pre_cfg->t_cksrx[p][ch]= cinit_ps_to_tck(timing->lpddr4_tckckeh, tck_ps);
         pre_cfg->t_cksre[p][ch]=cinit_ps_to_tck(timing->lpddr4_tckelck ,tck_ps );

         if(timing->lpddr4_tsr < timing->lpddr4_tcke ) {
             pre_cfg->t_ckesr[p][ch]=cinit_ps_to_tck(timing->lpddr4_tcke,tck_ps); 
         }  else {
             pre_cfg->t_ckesr[p][ch]=cinit_ps_to_tck(timing->lpddr4_tsr,tck_ps); 
         }
         pre_cfg->t_cke[p][ch]=timing->lpddr4_tcke;
         pre_cfg->t_cmdcke[p][ch] = cinit_ps_to_tck(timing->lpddr4_tcmdcke, tck_ps);
         pre_cfg->t_vrcg_enable[p][ch]=cinit_ps_to_tck(timing->lpddr4_tvrcg_enable,tck_ps);
         pre_cfg->t_vrcg_disable[p][ch]=cinit_ps_to_tck(timing->lpddr4_tvrcg_disable,tck_ps);
         pre_cfg->lpddr4_diff_bank_rwa2pre[p][ch]=2;
         pre_cfg->t_pbr2pbr[p][ch] = CEIL(timing->lpddr4_tpbr2pbr,tck_ps);
         pre_cfg->wl[p][ch] = (hdlr->memCtrlr_m.lpddr4_mr[p].mr2.wls==0) ?  timing->lpddr4_cwl_seta : timing->lpddr4_cwl_setb; // write latency
         pre_cfg->rl[p][ch] = (hdlr->memCtrlr_m.lpddr4_mr[p].mr3.read_dbi==0) ?  cl : cl_dbi; // read latency
         pre_cfg->nwr[p][ch] = timing->lpddr4_nwr;
         pre_cfg->nrtp[p][ch] = timing->lpddr4_nrtp;

         //LPDDR4: WL + 1 + BL/2 + max(RU(7.5ns/tCK),8nCK) + nWR
         pre_cfg->wr2mr[p][ch]= pre_cfg->wl[p][ch] + 1 + cfg->burst_rdwr + max(CEIL(7500, tck_ps),8) + CEIL(timing->lpddr4_twr,tck_ps);
         //LPDDR4: RL + BL/2 + RU(tDQSCKmax/tCK) + RD(tRPST) + max(RU(7.5ns/tCK),8nCK) + nRTP - 8
         uint32_t tdqsck_max= cinit_ps_to_tck(timing->lpddr4_tdqsck_max, hdlr->spdData_m.tck_ps[p]);
         uint32_t trpst_int= (hdlr->memCtrlr_m.lpddr4_mr[p].mr1.rd_postamble) ? 1 : 0;
         pre_cfg->rd2mr[p][ch]=  pre_cfg->rl[p][ch] + cfg->burst_rdwr + tdqsck_max + trpst_int + max(CEIL(7500, tck_ps),8) + cinit_ps_to_tck(trtp,tck_ps) - 8;
         pre_cfg->wra2pre[p][ch]=pre_cfg->wl[p][ch]+cfg->burst_rdwr+pre_cfg->nwr[p][ch]+1;
         pre_cfg->rda2pre[p][ch]=cfg->burst_rdwr - 8 + pre_cfg->nrtp[p][ch];
         pre_cfg->t_osco[p][ch]=cinit_ps_to_tck(timing->lpddr4_tosco,tck_ps);
         
         break;
     case DWC_LPDDR5 : 
         ratio=(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 2 : 4;
         twr=timing->lpddr5_twr_ps;
         tfaw=timing->lpddr5_tfaw_ps;
         // min(9 * tREFI * Refresh Rate, 70.2) us
         // refresh rate = 01001B: 1x refresh
         tras_max=cinit_get_lpddr5_tras_max(hdlr, (cfg->per_bank_refresh) ? timing->lpddr5_trefipb_ps : timing->lpddr5_trefi_ps,9,p);
         tras_min=timing->lpddr5_tras_min_ps;
         txp=timing->lpddr5_txp_ps;
         //tRBTP = [1:1:2] Max(7.5ns,4nCK) - 4nCK [1:1:4] Max(7.5ns,2nCK) - 2nCK
         pre_cfg->t_rbtp[p][ch]=cinit_ps_to_tck(timing->lpddr5_trtp_ps,tck_ps) - ((spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) ? 2 : 4);
         pre_cfg->t_rrd_s[p][ch]=CEIL(timing->lpddr5_trrd_s_ps,tck_ps);
         if(cfg->per_bank_refresh ) {
           // tRAS + tRPpb with per-bank precharge
           t_rc=timing->lpddr5_trc_ppb_ps; 
           pre_cfg->derated_t_rc[p][ch]=cinit_ps_to_tck(timing->lpddr5_derated_trcpb_ps, tck_ps);
           pre_cfg->derated_t_rp[p][ch]=cinit_ps_to_tck(timing->lpddr5_derated_trppb_ps, tck_ps);
         } else {
               // tRAS + tRPab with all-bank precharge
           t_rc=timing->lpddr5_trc_pab_ps; 
           pre_cfg->derated_t_rc[p][ch]=cinit_ps_to_tck(timing->lpddr5_derated_trcab_ps, tck_ps);
           pre_cfg->derated_t_rp[p][ch]=cinit_ps_to_tck(timing->lpddr5_derated_trpab_ps, tck_ps);
           }
         pre_cfg->wl[p][ch]=timing->lpddr5_wl_tck;
         pre_cfg->rl[p][ch]=timing->lpddr5_rl_tck;
         pre_cfg->nwr[p][ch]=timing->lpddr5_nwr;
         pre_cfg->nrtp[p][ch] = timing->lpddr5_nrtp;
         pre_cfg->nrbtp[p][ch] = cinit_ps_to_tck(timing->lpddr5_nrbtp_ps, tck_ps);

         if(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1 ) {
           timing->lpddr5_odtloff_tck=pre_cfg->wl[p][ch]+5;
         } else {
           timing->lpddr5_odtloff_tck=pre_cfg->wl[p][ch]+3;
         }
         timing->lpddr5_odtlon_tck=cal_lpddr5_odtlon(hdlr,p,ch); 
         trp=timing->lpddr5_trpab_ps; /// TODO check this ( using all bank )
         twtr=timing->lpddr5_twtr_ps;
         t_mr=cinit_ps_to_tck(timing->lpddr5_tmrd_ps, tck_ps) ;
         trcd=timing->lpddr5_trcd_ps;
         pre_cfg->t_ccd[p][ch]=timing->lpddr5_tccd_l_tck;
         trrd=timing->lpddr5_trrd_l_ps;  // same as lpddr5_trrd_s_ps
         pre_cfg->derated_t_rcd[p][ch]=cinit_ps_to_tck(timing->lpddr5_derated_trcd_ps, tck_ps);
         pre_cfg->derated_t_ras_min[p][ch]=cinit_ps_to_tck(timing->lpddr5_derated_tras_min_ps, tck_ps);
         pre_cfg->derated_t_rrd[p][ch]=cinit_ps_to_tck(timing->lpddr5_derated_trrd_ps, tck_ps);
         pre_cfg->t_cksrx[p][ch]= cinit_ps_to_tck(timing->lpddr5_tckcsh_ps,tck_ps);
         pre_cfg->t_cksre[p][ch]= cinit_ps_to_tck(timing->lpddr5_tcslck_ps,tck_ps); 
         pre_cfg->t_ckesr[p][ch]= max(timing->lpddr5_tsr_ps, timing->lpddr5_tcspd_ps);
         pre_cfg->t_ckesr[p][ch]= cinit_ps_to_tck(pre_cfg->t_ckesr[p][ch],tck_ps);
         pre_cfg->t_cke[p][ch]=cinit_ps_to_tck(timing->lpddr5_tcspd_ps, tck_ps);
         pre_cfg->t_csh[p][ch]=CEIL(timing->lpddr5_tcsh_ps, tck_ps);

         pre_cfg->t_cmdcke[p][ch] = max(timing->lpddr5_tcmdpd_ps,timing->lpddr5_tescke_ps ) ;
         pre_cfg->t_cmdcke[p][ch] = cinit_ps_to_tck(pre_cfg->t_cmdcke[p][ch],tck_ps);
         pre_cfg->t_vrcg_enable[p][ch]=cinit_ps_to_tck(timing->lpddr5_tvrcg_enable_ps,tck_ps);
         pre_cfg->t_vrcg_disable[p][ch]=cinit_ps_to_tck(timing->lpddr5_tvrcg_disable_ps,tck_ps);
         // WL + BL/n_min + 1 + nWR
         pre_cfg->wra2pre[p][ch]=pre_cfg->wl[p][ch]+timing->lpddr5_bl_n_min_tck + 1 + pre_cfg->nwr[p][ch];
         // BL/n_min + nRBTP
         //pre_cfg->rda2pre[p][ch]=CEIL(timing->lpddr5_twr_ps,tck_ps) + timing->lpddr5_bl_n_min_tck + pre_cfg->nrbtp[p][ch];
         pre_cfg->rda2pre[p][ch]= timing->lpddr5_bl_n_min_tck + pre_cfg->nrbtp[p][ch];
         
         pre_cfg->t_pbr2pbr[p][ch] = cinit_ps_to_tck(timing->lpddr5_tpbr2pbr_ps , hdlr->spdData_m.tck_ps[p]);
         pre_cfg->t_pbr2act[p][ch] = cinit_ps_to_tck(timing->lpddr5_tpbr2act_ps , hdlr->spdData_m.tck_ps[p]);
         
         
         pre_cfg->max_rd_sync[p][ch]=pre_cfg->rl[p][ch]+ timing->lpddr5_bl_n_max_tck + timing->lpddr5_twck_pst_wck/ratio;
         pre_cfg->max_wr_sync[p][ch]=pre_cfg->wl[p][ch]+ timing->lpddr5_bl_n_max_tck + timing->lpddr5_twck_pst_wck/ratio;
         int tmp=timing->lpddr5_wckenl_rd_tck*ratio;
         if(tmp <= 4 ) {
             ERROR_MESSAGE(("PHY does not support zero or negative lpddr5_wckenl_rd_tck value"));
         }
         tmp=timing->lpddr5_wckenl_wr_tck*ratio;
         if(tmp <= 4 ) {
             ERROR_MESSAGE(("PHY does not support zero or negative lpddr5_wckenl_wr_tck value"));
         }

         pre_cfg->dfi_twck_en_rd[p][ch]= (timing->lpddr5_wckenl_rd_tck==0) ? 0 : (timing->lpddr5_wckenl_rd_tck*ratio) - 4;
         pre_cfg->dfi_twck_en_wr[p][ch]= (timing->lpddr5_wckenl_wr_tck==0) ? 0 : (timing->lpddr5_wckenl_wr_tck*ratio) - 4;
         pre_cfg->dfi_twck_en_fs[p][ch]= (timing->lpddr5_wckenl_fs_tck==0) ? 0 : (timing->lpddr5_wckenl_fs_tck*ratio) - 4;
         // LPDDR54 utility PUB data-book states dfi_twck_dis is always 0
         pre_cfg->dfi_twck_dis[p][ch]= (qdyn->wck_on[ch] == 1) ? timing->lpddr5_twck_pst_wck : 0;
         //pre_cfg->dfi_twck_fast_toggle[p][ch]=4; // LPDDR54 utility PUB data-book
         pre_cfg->dfi_twck_fast_toggle[p][ch]=(spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 0 : 4;
         pre_cfg->dfi_twck_toggle[p][ch]=timing->lpddr5_wckpre_static_tck*ratio;
         pre_cfg->dfi_twck_toggle_cs[p][ch]=0;

         // temporary value : max(tWCK_PST, (BL/n_max - BL/n_min + RU(tWCK_PST/tCK)) * ratio)
         // See https://ca09sg-mantis.internal.synopsys.com/production/current/view.php?id=38917
         pre_cfg->dfi_twck_toggle_post[p][ch]= (qdyn->wck_on[ch] == 1) ? timing->lpddr5_twck_pst_wck :
               (spd->lpddr5_bk_bg_org== DWC_LPDDR5_4BK_4BG) ? (timing->lpddr5_bl_n_max_tck - timing->lpddr5_bl_n_min_tck + timing->lpddr5_twck_pst_wck/ratio - 1)*ratio : (timing->lpddr5_twck_pst_wck - ratio);

         // RL + RU(tWCKDQO(max)/tCK)) + BL/n_max + MAX[RU(7.5ns/tCK),4nCK] + nRBTP
         pre_cfg->rd2mr[p][ch]= pre_cfg->rl[p][ch] + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps)+timing->lpddr5_bl_n_max_tck + max(CEIL(7500, tck_ps),4) + pre_cfg->t_rbtp[p][ch];

         // WL + BL/n_max + MAX[RU(7.5ns/tCK),4nCK] + nWR
         pre_cfg->wr2mr[p][ch]=pre_cfg->wl[p][ch] + timing->lpddr5_bl_n_max_tck + max(CEIL(7500, tck_ps),4) + CEIL(timing->lpddr5_twr_ps,tck_ps);

         // PHY parameter
         pre_cfg->tphy_wckcsgap = (spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 3*2 : 1*4;
         pre_cfg->lpddr5_cdd = 1;   // temporary
         break;
#endif
    default:
      ERROR_MESSAGE(("cinit_pre_cfg dram type %0d not yet supported.",hdlr->spdData_m.sdram_protocol));
      break;
 }
  pre_cfg->cl[p]=cl;
  pre_cfg->cl_dbi[p]=cl_dbi;

  pre_cfg->twr[p][ch]= cinit_ps_to_tck(twr,tck_ps);
  if (IS_DDR4){
    pre_cfg->twr[p][ch] = (pre_cfg->twr[p][ch] % 2) ? (pre_cfg->twr[p][ch] + 1) : pre_cfg->twr[p][ch];
  }
  else if(IS_DDR5) {
    pre_cfg->twr[p][ch] = (pre_cfg->twr[p][ch] % 6) ? (pre_cfg->twr[p][ch] + 6 - pre_cfg->twr[p][ch] % 6) : pre_cfg->twr[p][ch];
  }

  if(IS_DDR4 || IS_DDR5) {
    pre_cfg->twtr[p][ch]=twtr;
  } else {
    pre_cfg->twtr[p][ch]=cinit_ps_to_tck(twtr, tck_ps);
  }

#ifdef MEMC_DDR4  
  pre_cfg->txpdll[p][ch]=cinit_ps_to_tck(txpdll,tck_ps);
#endif
 pre_cfg->t_rtp[p][ch]=cinit_ps_to_tck(trtp,tck_ps);
#ifdef MEMC_LPDDR4
 pre_cfg->odton_min[p][ch]=cinit_ps_to_tck( timing->lpddr4_todton_min,tck_ps);
#endif

 if (hdlr->spdData_m.sdram_protocol != DWC_DDR5) {
   pre_cfg->tfaw[p][ch]=cinit_ps_to_tck(tfaw,tck_ps);
 } else {
   pre_cfg->tfaw[p][ch]=tfaw;
 }
 pre_cfg->t_ras_max[p][ch]=(tras_max/tck_ps)/1024;
 if(pre_cfg->t_ras_max[p][ch]> 255) {pre_cfg->t_ras_max[p][ch]=255; };
 pre_cfg->t_ras_min[p][ch]=cinit_ps_to_tck(tras_min,tck_ps);
 pre_cfg->txp[p][ch]=CEIL(txp,tck_ps);
 pre_cfg->t_rc[p][ch]=cinit_ps_to_tck(t_rc,tck_ps);

#ifdef MEMC_DDR4
  //MEMC_DDR5
  if(IS_DDR5 && IS_RDIMM){
    pre_cfg->t_pd[p][ch] = max(cinit_ps_to_tck(timing->ddr5_tpd_ps,tck_ps),cinit_ps_to_tck(timing->ddr5_rcd_tpdex_ps,tck_ps));
  }
  else{
 pre_cfg->t_pd[p][ch] = cinit_ps_to_tck(timing->ddr5_tpd_ps,tck_ps);
  }
 pre_cfg->t_mpsmx[p][ch] = cinit_ps_to_tck(timing->ddr5_tmpsmx_ps,tck_ps);
 pre_cfg->t_mpdpxact[p][ch] = cinit_ps_to_tck(timing->ddr5_tmpdpdact_ps,tck_ps);

 pre_cfg->t_pda_latch[p][ch] = cinit_ps_to_tck(timing->ddr5_tpda_latch_min_ps,tck_ps);
 pre_cfg->t_pda_delay[p][ch] = cinit_ps_to_tck(timing->ddr5_tpda_delay_ps,tck_ps);
 pre_cfg->t_pda_dqs_delay[p][ch] = cinit_ps_to_tck(timing->ddr5_tpda_dqs_delay_min_ps,tck_ps);
 pre_cfg->t_pda_s[p][ch] = timing->ddr5_tpda_s_tck;
 pre_cfg->t_pda_h[p][ch] = timing->ddr5_tpda_h_tck;

 pre_cfg->t_cpded[p][ch] = cinit_ps_to_tck(timing->ddr5_tcpded_ps,tck_ps);
 pre_cfg->t_casrx[p][ch] = cinit_ps_to_tck(timing->ddr5_tcasrx_ps,tck_ps);
 pre_cfg->t_csh_srexit[p][ch] = cinit_ps_to_tck(timing->ddr5_tcsh_srexit_ps,tck_ps);
 pre_cfg->t_csl_srexit[p][ch] = timing->ddr5_tcsl_srexit_tck;

 pre_cfg->t_mpc_cs[p][ch] = timing->ddr5_tmpc_cs_min_tck;

 pre_cfg->t_mpc_setup[p][ch] = timing->ddr5_tmc_mpc_setup_tck;
 pre_cfg->t_mpc_hold[p][ch] = timing->ddr5_tmc_mpc_hold_tck;
 pre_cfg->t_vrefca_cs[p][ch] = timing->ddr5_tvrefca_cs_min_tck;
 pre_cfg->t_osco_ddr5[p][ch] = cinit_ps_to_tck(timing->ddr5_tosco_ps,tck_ps);
 pre_cfg->t_ccd_w[p][ch] = cinit_ps_to_tck(timing->ddr5_tccd_l_wr_ps,tck_ps);
 pre_cfg->t_wr2rd_dpr[p][ch]= timing->ddr5_tccd_s_tck;
 pre_cfg->t_rd2wr_dpr[p][ch]= timing->ddr5_tccd_s_tck;


 if(IS_DDR5) {
   if(GET_CID_WIDTH == 0) {
     if(qdyn->fgr_mode) {
       pre_cfg->t_xs_min[p][ch] = cinit_ps_to_tck(timing->ddr5_trfc1_ps,tck_ps)/32 + 1;
     } else {
       pre_cfg->t_xs_min[p][ch] = cinit_ps_to_tck(timing->ddr5_trfc1_ps,tck_ps)/32 + 1;
     }
   } else {
      pre_cfg->t_xs_min[p][ch] = cinit_ps_to_tck(timing->ddr5_trfc1_ps + 10000,tck_ps)/32 + 1;
   }
 }

 pre_cfg->t_ccd_w2[p][ch] = cinit_ps_to_tck(timing->ddr5_tccd_l_wr2_ps,tck_ps);
#endif

// TODO pre_cfg->odton[p]
//
#ifdef MEMC_LPDDR2
  pre_cfg->tINITTMG1[ch]=100;
  pre_cfg->tINIT2=5;
  pre_cfg->tINIT3=200;
  pre_cfg->tINIT4[p]= ((10000000/(tck_ps * MEMC_FREQ_RATIO))/32) ;
  if(((10000000/(tck_ps * MEMC_FREQ_RATIO)) % 32) !=0 ) {
    pre_cfg->tINIT4[p]++;
  }
  
  pre_cfg->tINITTMG3[ch]= ((10000000/(tck_ps * MEMC_FREQ_RATIO))/1024) ;
  if( ((10000000/(tck_ps * MEMC_FREQ_RATIO)) % 1024) !=0 ) {
      pre_cfg->tINITTMG3[ch]++;
  }
#endif
#ifdef MEMC_LPDDR4
  uint32_t wdqs_on = (hdlr->memCtrlr_m.lpddr4_mr[p].mr2.wls==0) ? timing->lpddr4_wdqson_seta : timing->lpddr4_wdqson_seta;
  
  pre_cfg->wdqspreext[p][ch]=pre_cfg->cwl_x[p] - wdqs_on;
#endif //MEMC_LPDDR4

  cinit_cal_rd2wr(hdlr,p,ch);
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4) {
    pre_cfg->t_mrw[p][ch]=timing->lpddr4_tmrwckel/tck_ps;
    if( pre_cfg->t_mrw[p][ch] < timing->lpddr4_tmrw  ) {
      pre_cfg->t_mrw[p][ch] = timing->lpddr4_tmrw  ;
    }
  } else if(IS_LPDDR5) {
    /// @todo check MRWCKEL is same as MRWPD ?
    uint32_t tmrwpd=  cinit_ps_to_tck(timing->lpddr5_tmrwpd_ps, tck_ps);
    uint32_t tmrw=cinit_ps_to_tck(timing->lpddr5_tmrw_ps, tck_ps);
    pre_cfg->t_mrw[p][ch]=max(tmrw,tmrwpd);
  }  
#endif
#ifdef MEMC_DDR4
  if(IS_DDR5){
    pre_cfg->t_mrw[p][ch] = timing->ddr5_tmrw_tck;
  }
#endif // MEMC_DDR5
  pre_cfg->t_mr[p][ch] = t_mr;
#ifdef MEMC_DDR4
  pre_cfg->t_mod[p][ch]=t_mod;
  // min is 12 cycles.
  if(pre_cfg->t_mod[p][ch]<12) { pre_cfg->t_mod[p][ch]=12; }
  if( hdlr->memCtrlr_m.ddr4_mr[p].mr4.cal!=0) {
    uint32_t cal_cycles;
    cal_cycles=get_cal_cycles(hdlr->memCtrlr_m.ddr4_mr[p].mr4.cal);
    pre_cfg->t_mr[p][ch] += cal_cycles;
    pre_cfg->t_mod[p][ch] += cal_cycles;
  }

  if(timing->ddr4_tpl_tck!=0) {
    pre_cfg->t_mod[p][ch] +=timing->ddr4_tpl_tck;
  }
#endif
  pre_cfg->t_rcd[p][ch]=cinit_ps_to_tck(trcd,tck_ps);
  { 
    uint32_t rcd_min; 
      rcd_min=2;
    if( (pre_cfg->t_rcd[p][ch] > hdlr->spdData_m.tAL) && ( (pre_cfg->t_rcd[p][ch] - hdlr->spdData_m.tAL) > rcd_min)) {
      pre_cfg->t_rcd[p][ch] =pre_cfg->t_rcd[p][ch] - hdlr->spdData_m.tAL;
    } else {
      pre_cfg->t_rcd[p][ch] =rcd_min;
    }
  }
      
#ifdef MEMC_DDR4     
  pre_cfg->t_rrd[p][ch] = timing->trrd_l_tck;
#else
  pre_cfg->t_rrd[p][ch] = cinit_ps_to_tck(trrd,tck_ps);
#endif
  pre_cfg->t_rp[p][ch] = cinit_ps_to_tck(trp,tck_ps);
  pre_cfg->t_cke[p][ch]=cinit_ps_to_tck(pre_cfg->t_cke[p][ch],tck_ps);
  if(IS_LPDDR4 && (pre_cfg->t_ckesr[p][ch]>pre_cfg->t_cke[p][ch]) ) {
    pre_cfg->t_cke[p][ch]= pre_cfg->t_ckesr[p][ch];
  }
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4) {
      // check write latency set
    pre_cfg->odtloff[p][ch] = (hdlr->memCtrlr_m.lpddr4_mr[p].mr2.wls==0) ?
      timing->lpddr4_odtloff_latency_seta:
      timing->lpddr4_odtloff_latency_setb;
    pre_cfg->odtlon[p][ch] = (hdlr->memCtrlr_m.lpddr4_mr[p].mr2.wls==0) ?
      timing->lpddr4_odtlon_latency_seta:
      timing->lpddr4_odtlon_latency_setb;

  } else if(IS_LPDDR5) {
    pre_cfg->odtloff[p][ch] =timing->lpddr5_odtloff_tck;
    pre_cfg->odtlon[p][ch]=timing->lpddr5_odtlon_tck;
  }
#endif
  if(hdlr->ddrPhyType_m==DWC_LPDDR4X_MULTIPHY) {
    cinit_cal_lpddr4x_multiphy_dfi_timings(hdlr,p,ch);
  }
  else if( hdlr->ddrPhyType_m==DWC_LPDDR54_PHY ) {
   cinit_cal_lpddr54_dfi_timings(hdlr,p,ch);   
  } 
  else if(hdlr->ddrPhyType_m==DWC_DDR43_PHY) {
   cinit_cal_ddr43_dfi_timings(hdlr,p,ch);   
  }
  else if(hdlr->ddrPhyType_m==DWC_DDR54_PHY) {
    cinit_cal_ddr54_dfi_timings(hdlr,p,ch);         
  } else {
    ERROR_MESSAGE(("Unknown PhyType to calculate dfi_timing parameters"));
  }

  if(IS_RDIMM) {
    pre_cfg->cmd_lat_adder[p][ch]= (tck_ps<833) ? 2 : 1;
  } 
  cinit_cal_wr2rd(hdlr,p,ch);
  cinit_encode_wr_recovery(hdlr,p,ch);
  cinit_encode_rl_wl(hdlr,p,ch);
#ifdef MEMC_DDR4
  cinit_encode_cas_latency(hdlr,p);
  if(IS_DDR4){
    cinit_encode_cas_write_latency(hdlr,p);
    if(hdlr->memCtrlr_m.ddr4_mr[p].mr2.write_crc && hdlr->memCtrlr_m.ddr4_mr[p].mr5.data_mask){
      cinit_encode_write_cmd_latency(hdlr,p);
    }
  }
  if(IS_DDR5){
    cinit_encode_ddr5_trtp_latency(hdlr,p,ch);
  }
  cinit_encode_tccd_l_latency(hdlr,p,ch);
#endif //MEMC_DDR4

#ifdef MEMC_NUM_RANKS_GT_1
  cinit_cal_rd2wr_dr(hdlr,p,ch);
  cinit_cal_wr2rd_dr(hdlr,p,ch);
  cinit_cal_diff_rank_rd_gap(hdlr,p,ch);
  cinit_cal_diff_rank_wr_gap(hdlr,p,ch);
#endif // MEMC_NUM_RANKS_GT_1  

#ifdef MEMC_LPDDR4
  if(IS_LPDDR5) {
    cinit_cal_mrr2rdwr(hdlr,p,ch);
  }
#endif


}
/** @brief Calculate CWL adjusted. 
 * for DDR4 write preamble, CWL is increased by 2 if VIRL_DDR4_WR_PREAMBLE==2
 */
void cinit_cal_cwlx(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
#ifdef MEMC_DDR4
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  if(IS_DDR4) {
    uint32_t tcwl_tck;
    tcwl_tck= (hdlr->spdData_m.use_ddr4_tcwl_1st_set ) ? timing->ddr4_tcwl_1st_set_tck : timing->ddr4_tcwl_2nd_set_tck;
    if( qdyn->ddr4_wr_preamble[p][ch] ) {
      tcwl_tck=tcwl_tck+2;
    }
      pre_cfg->cwl_x[p]=tcwl_tck ;

  } else if (IS_DDR5) {
    pre_cfg->cwl_x[p] = timing->ddr5_tcwl_tck;
  }
#endif
#ifdef MEMC_LPDDR4
  if (IS_LPDDR4) {
    if( hdlr->memCtrlr_m.lpddr4_mr[p].mr2.wls==0) {
      pre_cfg->cwl_x[p]= timing->lpddr4_cwl_seta;
    } else {
      pre_cfg->cwl_x[p]= timing->lpddr4_cwl_setb;
    }
  }
#endif
}

/** @brief function to pre-calculate wr2rd
 * */
void cinit_cal_wr2rd(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
#ifdef MEMC_DDR4
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  uint32_t twtr_l_crc_dm,twtr_s_crc_dm;
#ifdef MEMC_FREQ_RATIO_2
  twtr_l_crc_dm=timing->ddr4_twtr_l_crc_dm_tck;
  twtr_s_crc_dm=timing->ddr4_twtr_s_crc_dm_tck;
#else
  twtr_l_crc_dm=0;
  twtr_s_crc_dm=0;
#endif // MEMC_FREQ_RATIO_2
  if(IS_DDR4) {
    pre_cfg->wr2rd[p][ch]=pre_cfg->cwl_x[p] + timing->ddr4_tpl_tck + twtr_l_crc_dm+ pre_cfg->twtr[p][ch] + cfg->burst_rdwr;
    pre_cfg->wr2rd_s[p][ch]=pre_cfg->cwl_x[p] + timing->ddr4_tpl_tck + twtr_s_crc_dm + pre_cfg->twtr_s[p][ch] + cfg->burst_rdwr;  
  }
  else if (IS_DDR5) {
    pre_cfg->wr2rd[p][ch] = pre_cfg->cwl_x[p] + cfg->burst_rdwr +  pre_cfg->twtr[p][ch];
    pre_cfg->wr2rd_s[p][ch] = pre_cfg->cwl_x[p] + cfg->burst_rdwr +  pre_cfg->twtr_s[p][ch];
#ifdef UMCTL2_CID_EN
    pre_cfg->t_wr2rd_dlr[p][ch] = pre_cfg->cwl_x[p] + cfg->burst_rdwr + pre_cfg->twtr_s[p][ch];
#endif // UMCTL2_CID_EN
  }
#endif // MEMC_DDR4
#ifdef MEMC_LPDDR4  
  if(IS_LPDDR4) {
    pre_cfg->wr2rd[p][ch]=pre_cfg->cwl_x[p]+pre_cfg->twtr[p][ch] + pre_cfg->wdqspreext[p][ch] + cfg->burst_rdwr + 1;
  } else if (IS_LPDDR5) {
    uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
    // wr2rd		= WL + BL/n_max + RU(tWTR_L/tCK)
    pre_cfg->wr2rd[p][ch]=pre_cfg->wl[p][ch]+timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_twtr_l_ps, tck_ps);
    // WL + BL/n_min + RU(tWTR_S/tCK)
    /// @todo see bugzilla 7142, using BL/n_max for now in wr2rd_s
    //dwc_cinit_print("wr2rd_s: WL=%0d, BL/n_min=%0d RU(tWTR_S/tCK)=%0d\n", pre_cfg->wl[p], timing->lpddr5_bl_n_max_tck , CEIL(timing->lpddr5_twtr_s_ps, tck_ps));
    pre_cfg->wr2rd_s[p][ch]=pre_cfg->wl[p][ch]+timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_twtr_s_ps, tck_ps);
  }
#endif // MEMC_LPDDR4
}

/** @brief function to pre-calculate rd2wr
 */
void cinit_cal_rd2wr(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  uint32_t read_dbi=0;
  uint32_t cl= (read_dbi==1) ?pre_cfg->cl_dbi[p] : pre_cfg->cl[p];
#ifdef MEMC_LPDDR4
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  if(IS_LPDDR4) {
      uint32_t twpre_int, trpst_int;
      uint32_t tdqsck_max;
      read_dbi=hdlr->memCtrlr_m.lpddr4_mr[p].mr3.read_dbi;
      twpre_int= (hdlr->memCtrlr_m.lpddr4_mr[p].mr1.wr_preamble) ? 2 : 1;
      trpst_int= (hdlr->memCtrlr_m.lpddr4_mr[p].mr1.rd_postamble) ? 1 : 0;
      tdqsck_max= cinit_ps_to_tck(timing->lpddr4_tdqsck_max, hdlr->spdData_m.tck_ps[p]);
     
      pre_cfg->rd2wr[p][ch]=(hdlr->spdData_m.tAL + cl + cfg->burst_rdwr + tdqsck_max  + twpre_int + trpst_int - (hdlr->spdData_m.tAL +  pre_cfg->cwl_x[p])) + pre_cfg->wdqspreext[p][ch];
      pre_cfg->rd2wr_odt[p][ch]=(hdlr->spdData_m.tAL + cl + cfg->burst_rdwr + tdqsck_max + trpst_int - pre_cfg->odton[p][ch] - pre_cfg->odton_min[p][ch] ) + pre_cfg->wdqspreext[p][ch];
  } else if(IS_LPDDR5) {
    uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
    // DQ ODT enabled
    //  RL + BL/n_max + RU(tWCKDQO(max)/tCK) + RD(tRPST/tCK) - ODTLon - RD(tODTon(min)/tCK) + 1
    pre_cfg->rd2wr_odt[p][ch]=pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps) + timing->lpddr5_trpst/tck_ps - timing->lpddr5_odtlon_tck - timing->lpddr5_odton_min_ps/tck_ps + 1;

    // DQ ODT disabled
    // RL + BL/n_max + RU(tWCKDQO(max)/tCK) -WL
    //dwc_cinit_print("RL=%0d, lpddr5_bl_n_max_tck=%0d,  CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps)=%0f WL=%0d \n", 
        //pre_cfg->rl[p][ch],  timing->lpddr5_bl_n_max_tck,  CEIL(timing->lpddr5_wckdqo_max_ps , tck_ps),pre_cfg->wl[p] );
    pre_cfg->rd2wr[p][ch]= pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_wckdqo_max_ps , tck_ps)  - pre_cfg->wl[p][ch];

    // DQ ODT disabled
    // RL + BL/n_min + RU(tWCKDQO(max) /tCK) - WL
    pre_cfg->rd2wr_s[p][ch]=pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_min_tck + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps) - pre_cfg->wl[p][ch];
    // DQ ODT enabled
    // RL + BL/n_min + RU(tWCKDQO(max)/tCK) + RD(tRPST/tCK) - ODTLon - RD(tODTon(min)/tCK) + 1
    pre_cfg->rd2wr_s_odt[p][ch]=pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_min_tck + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps) + timing->lpddr5_trpst/tck_ps - timing->lpddr5_odtlon_tck - timing->lpddr5_odton_min_ps/tck_ps + 1;

  }

#endif //MEMC_LPDDR4
#ifdef MEMC_DDR4
  mctl_qdyn_cfg_t* qdyn = &(hdlr->memCtrlr_m.qdyn_cfg);
  if (IS_DDR4) {
      read_dbi=hdlr->memCtrlr_m.ddr4_mr[p].mr5.read_dbi;
      // TODO add VIRL_VIP_LRDIMM
      pre_cfg->rd2wr[p][ch]=(hdlr->spdData_m.tAL + cl + cfg->burst_rdwr + 1 + ((qdyn->ddr4_wr_preamble[p][ch]) ? 2 : 1) - (hdlr->spdData_m.tAL +  pre_cfg->cwl_x[p]));     
  }  
  else if (IS_DDR5) {
    ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[p]);
    
    uint32_t rd_dqs_offset = cinit_get_ddr5_t_rd_dqs_offset(hdlr,p);
    uint32_t tWPRE = cinit_get_ddr5_twpre(hdlr,p);
    pre_cfg->rd2wr[p][ch]=pre_cfg->cl[p] + cfg->burst_rdwr + 2 + tWPRE 
                      + ((mregs->mr8.rd_postamble)? 1 : 0) - 
                      rd_dqs_offset - pre_cfg->cwl_x[p];
#ifdef UMCTL2_CID_EN
    pre_cfg->t_rd2wr_dlr[p][ch]=pre_cfg->cl[p] + cfg->burst_rdwr + 2 + tWPRE 
                      + ((mregs->mr8.rd_postamble)? 1 : 0) - 
                      rd_dqs_offset - pre_cfg->cwl_x[p];
#endif //UMCTL2_CID_EN
  }
#endif //MEMC_DDR4
}

#ifdef MEMC_NUM_RANKS_GT_1
/** @brief function to pre-calculate rd2wr_dr
 */
void cinit_cal_rd2wr_dr(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  uint32_t read_dbi=0;
  uint32_t cl= (read_dbi==1) ?pre_cfg->cl_dbi[p] : pre_cfg->cl[p];
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  ddrSpdData_t* spd = &(hdlr->spdData_m);

#ifdef MEMC_LPDDR4
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[p];
  uint32_t ratio  = (spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 2 : 4;

  if(IS_LPDDR5) {
   // (RL + BL/n_min + RU(tWCK2DQO(max)/tCK) -  ODTLon -  RD(tODTon(min)/tCK) + 1) + tphy_wckcsgap + LP5 CDD
   pre_cfg->rd2wr_dr_wck_on_odt[p][ch] = (pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_min_tck + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps) -
                                           pre_cfg->odtlon[p][ch] - timing->lpddr5_odton_min_ps/tck_ps + 1) +
                                          pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;

   // (RL + BL/n_max + RU((tWCKPST -0.5*tWCK)/tCK) - min[(ODTLon + RD(tODTon(min)/tCK)), tWCKENL_WR]) + tphy_wckcsgap + LP5 CDD
   pre_cfg->rd2wr_dr_odt[p][ch] = (pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_twck_pst_wck, ratio) -
                                    min(pre_cfg->odtlon[p][ch] + timing->lpddr5_odton_min_ps/tck_ps, timing->lpddr5_wckenl_wr_tck)) +
                                   pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
   
   // (RL + BL/n_min + RU(tWCK2DQO(max)/tCK) + RU((tRPST -0.5*tWCK)/tCK) - WL) + tphy_wckcsgap + LP5 CDD
   pre_cfg->rd2wr_dr_wck_on[p][ch] = (pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_min_tck + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps) +
                                       CEIL(timing->lpddr5_twck_pst_wck, ratio) - pre_cfg->wl[p][ch]) +
                                      pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;

   // (RL + BL/n_max + RU((tWCKPST -0.5*tWCK)/tCK) - tWCKENL_WR) + tphy_wckcsgap + LP5 CDD
   pre_cfg->rd2wr_dr[p][ch] = (pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_twck_pst_wck, ratio) - timing->lpddr5_wckenl_wr_tck) +
                               pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
   } else
#endif // MEMC_LPDDR4
   {
      pre_cfg->rd2wr_dr[p][ch]=pre_cfg->rd2wr[p][ch];
   }
}
#endif // MEMC_NUM_RANKS_GT_1  

#ifdef MEMC_NUM_RANKS_GT_1
/** @brief function to pre-calculate wr2rd_dr
 */
void cinit_cal_wr2rd_dr(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  uint32_t read_dbi=0;
  uint32_t cl= (read_dbi==1) ?pre_cfg->cl_dbi[p] : pre_cfg->cl[p];
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  ddrSpdData_t* spd = &(hdlr->spdData_m);

#ifdef MEMC_LPDDR4
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[p];
  uint32_t ratio  = (spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 2 : 4;

  if(IS_LPDDR5) {
   int wr2rd_dr;
   // (ODTLoff + RU(tODToff(max)/tCK) - RL) + tphy_wckcsgap + LP5 CDD
   wr2rd_dr = pre_cfg->odtloff[p][ch] + CEIL(timing->lpddr5_odtoff_max_ps, tck_ps) - pre_cfg->rl[p][ch];
   pre_cfg->wr2rd_dr_wck_on_odt[p][ch] = max(0, wr2rd_dr) + pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;

   // (WL + BL/n_max + max[RU(tODToff(max)/ tCK), RU((tWCKPST -0.5*tWCK)/tCK)] - tWCKENL_RD) + tphy_wckcsgap + LP5 CDD
   wr2rd_dr = pre_cfg->wl[p][ch] + timing->lpddr5_bl_n_max_tck + max(CEIL(timing->lpddr5_odtoff_max_ps, tck_ps), CEIL(timing->lpddr5_twck_pst_wck, ratio)) - timing->lpddr5_wckenl_rd_tck;
   pre_cfg->wr2rd_dr_odt[p][ch] = max(0, wr2rd_dr) + pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
   // (WL + BL/n_min + 1 - RL) + tphy_wckcsgap + LP5 CDD
   wr2rd_dr = pre_cfg->wl[p][ch] + timing->lpddr5_bl_n_min_tck + 1 - pre_cfg->rl[p][ch];
   pre_cfg->wr2rd_dr_wck_on[p][ch] = max(0, wr2rd_dr) + pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
   // (WL + BL/n_max + RU((tWCKPST -0.5*tWCK)/tCK) - tWCKENL_RD) + tphy_wckcsgap + LP5 CDD
   wr2rd_dr = pre_cfg->wl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_twck_pst_wck, ratio) - timing->lpddr5_wckenl_rd_tck;
   pre_cfg->wr2rd_dr[p][ch] = max(0, wr2rd_dr) + pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
   } else
#endif // MEMC_LPDDR4
   {
      pre_cfg->wr2rd_dr[p][ch]=pre_cfg->wr2rd[p][ch];
   }
}
#endif // MEMC_NUM_RANKS_GT_1  

#ifdef MEMC_NUM_RANKS_GT_1
/** @brief function to pre-calculate diff_rank_rd_gap
 */
void cinit_cal_diff_rank_rd_gap(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  uint32_t read_dbi=0;
  uint32_t cl= (read_dbi==1) ?pre_cfg->cl_dbi[p] : pre_cfg->cl[p];
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  ddrSpdData_t* spd = &(hdlr->spdData_m);

#ifdef MEMC_LPDDR4
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[p];
  uint32_t ratio  = (spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 2 : 4;

  if(IS_LPDDR5) {
      uint32_t trpre_wck = hdlr->memCtrlr_m.lpddr5_mr[p].mr10.rdqs_pre > 3 ? 6 : 4;
      uint32_t trpst_wck = hdlr->memCtrlr_m.lpddr5_mr[p].mr10.rdqs_pst == 0 ? 0 :
                           hdlr->memCtrlr_m.lpddr5_mr[p].mr10.rdqs_pst == 1 ? 2 : 4;
      // (BL/n_min + 1 + RU((tRPST+tRPRE - 0.5*tWCK)/tCK)) + tphy_wckcsgap + LP5 CDD
      pre_cfg->diff_rank_rd_gap_wck_on_odt[p][ch] = (timing->lpddr5_bl_n_min_tck + 1 + CEIL(trpst_wck + trpre_wck, ratio)) +
                                                    pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
      // (RL + BL/n_max + RU((tWCKPST - 0.5*tWCK)/tCK) - tWCKENL_RD) + tphy_wckcsgap + LP5 CDD
      pre_cfg->diff_rank_rd_gap_odt[p][ch] = (pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_twck_pst_wck, ratio) - timing->lpddr5_wckenl_rd_tck) +
                                             pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
      // (BL/n_min + 1 + RU((tRPST+tRPRE - 0.5*tWCK)/tCK)) + tphy_wckcsgap + LP5 CDD
      pre_cfg->diff_rank_rd_gap_wck_on[p][ch] = (timing->lpddr5_bl_n_min_tck + 1 + CEIL(trpst_wck + trpre_wck, ratio)) +
                                                pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
      // (RL + BL/n_max + RU((tWCKPST - 0.5*tWCK)/tCK) - tWCKENL_RD) + tphy_wckcsgap + LP5 CDD
      pre_cfg->diff_rank_rd_gap[p][ch] = (pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_twck_pst_wck, ratio) - timing->lpddr5_wckenl_rd_tck) +
                                         pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
  }
#endif // MEMC_LPDDR4
}
#endif // MEMC_NUM_RANKS_GT_1  

#ifdef MEMC_NUM_RANKS_GT_1
/** @brief function to pre-calculate diff_rank_wr_gap
 */
void cinit_cal_diff_rank_wr_gap(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  uint32_t read_dbi=0;
  uint32_t cl= (read_dbi==1) ?pre_cfg->cl_dbi[p] : pre_cfg->cl[p];
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  ddrSpdData_t* spd = &(hdlr->spdData_m);

#ifdef MEMC_LPDDR4
  uint32_t tck_ps = hdlr->spdData_m.tck_ps[p];
  uint32_t ratio  = (spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 2 : 4;

  if(IS_LPDDR5) {
      // (ODTLoff + RU(tODToff(max)/tCK) - ODTLon) + tphy_wckcsgap + LP5 CDD
      pre_cfg->diff_rank_wr_gap_wck_on_odt[p][ch] = (pre_cfg->odtloff[p][ch] + CEIL(timing->lpddr5_odtoff_max_ps, tck_ps) - pre_cfg->odtlon[p][ch]) +
                                                    pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
      // (WL + BL/n_max + max[RU(tODToff(max)/ tCK), RU((tWCKPST -0.5*tWCK)/tCK)] - tWCKENL_WR) + tphy_wckcsgap + LP5 CDD
      pre_cfg->diff_rank_wr_gap_odt[p][ch] = (pre_cfg->wl[p][ch] + timing->lpddr5_bl_n_max_tck +
                                              max(CEIL(timing->lpddr5_odtoff_max_ps, tck_ps), CEIL(timing->lpddr5_twck_pst_wck, ratio)) - timing->lpddr5_wckenl_wr_tck) +
                                             pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
      // (BL/n_min + 1) + tphy_wckcsgap + LP5 CDD
      pre_cfg->diff_rank_wr_gap_wck_on[p][ch] = (timing->lpddr5_bl_n_max_tck + 1) +
                                                pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
      // (WL + BL/n_max + RU((tWCKPST -0.5*tWCK)/tCK) - tWCKENL_WR) + tphy_wckcsgap + LP5 CDD
      pre_cfg->diff_rank_wr_gap[p][ch] = (pre_cfg->wl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_twck_pst_wck, ratio) - timing->lpddr5_wckenl_wr_tck) +
                                         pre_cfg->tphy_wckcsgap/ratio + pre_cfg->lpddr5_cdd;
  }
#endif // MEMC_LPDDR4
}
#endif // MEMC_NUM_RANKS_GT_1  

#ifdef MEMC_LPDDR4
void cinit_cal_mrr2rdwr(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_static_cfg_t* cfg = &(hdlr->memCtrlr_m.static_cfg);
  uint32_t read_dbi=0;
  uint32_t cl= (read_dbi==1) ?pre_cfg->cl_dbi[p] : pre_cfg->cl[p];
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  ddrSpdData_t* spd = &(hdlr->spdData_m);

  uint32_t tck_ps = hdlr->spdData_m.tck_ps[p];
  uint32_t ratio  = (spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) ? 2 : 4;

  // MRR to RD
  // RL + BL/n_max + RD(tWCKPST/tCK) + 2
  pre_cfg->mrr2rd[p][ch] = pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + timing->lpddr5_twck_pst_wck/ratio + 2;

  // MRR to WR
  // RL + BL/n_max + RU(tWCKDQO(max)/tCK) - WL + 2
  pre_cfg->mrr2wr[p][ch]=pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps) - pre_cfg->wl[p][ch] + 2;

  // RL + RU(tWCKDQO(max)/tCK) + BL/n_max-ODTLon - RD(tODTon(min)/tCK) + 2
  pre_cfg->mrr2wr_odt[p][ch]=pre_cfg->rl[p][ch] + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps) + timing->lpddr5_bl_n_max_tck - timing->lpddr5_odtlon_tck - timing->lpddr5_odton_min_ps/tck_ps + 2;

  // MRR to MRW
  // RL + BL/n_max + RU(tWCKDQO(max)/tCK) + 2
  pre_cfg->mrr2wr[p][ch]=pre_cfg->rl[p][ch] + timing->lpddr5_bl_n_max_tck + CEIL(timing->lpddr5_wckdqo_max_ps, tck_ps) + 2;

}
#endif // MEMC_LPDDR4



/** @brief Convert a timing parameter from ps to TCK cycles.
 *@param timing parameter in picoseconds
 *@param TCK clock period in picoseconds
 *@returns number of TCK cycles (rounded up). 
 */
uint32_t cinit_ps_to_tck(uint32_t param_ps, uint32_t tck_ps) {
  uint32_t tck_cycles;
  tck_cycles=param_ps/tck_ps;
  if(param_ps%tck_ps !=0) {
      tck_cycles++;
  }
  return tck_cycles;
}

uint8_t get_cal_cycles(uint8_t cal_mode) {
  uint8_t cycles;
  switch(cal_mode) {
    case 0 : 
      cycles= 0;
      break;
    case 1 : 
      cycles= 3;
      break;
    case 2 : 
      cycles= 4;
      break;
    case 3 : 
      cycles= 5;
      break;
    case 4: 
      cycles= 6;
      break;
    case 5 : 
      cycles=8; 
      break;
    default:
      ERROR_MESSAGE(("cal_mode= %0d not yet supported.",cal_mode));
      break;
  }
  return cycles;
}

/** @brief function to encode write recovery parameters for write to
 * mode register. */
void cinit_encode_wr_recovery(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4 ) {
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
    uint32_t twr_tck;
    uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
    lpddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.lpddr4_mr[p]);
    twr_tck=CEIL(timing->lpddr4_twr,tck_ps);
    if(twr_tck==11 || twr_tck==15 || twr_tck==27 || twr_tck==29 ||
       twr_tck==39 || twr_tck==43 ) {
      twr_tck++;
    } 
    // TODO twr_tck==8 & x16 => 10, x8 => 12
    if (hdlr->spdData_m.sdram_width_bits == 16 )
    {
    // C does not support ranges so use fall through cases
      switch (twr_tck)
      {

        case 0  ... 6 :  mregs->mr1.wr_recovery = 0; break;
        case 7 ... 10: mregs->mr1.wr_recovery = 1; break;
        case 11 ... 16:  mregs->mr1.wr_recovery = 2; break;
        case 17 ... 20:  mregs->mr1.wr_recovery = 3; break;
        case 21 ... 24:  mregs->mr1.wr_recovery = 4; break;
        case 25 ... 30:  mregs->mr1.wr_recovery = 5; break;
        case 31 ... 34:  mregs->mr1.wr_recovery = 6; break;
        case 35 ... 40:  mregs->mr1.wr_recovery = 7; break;
        default: 
          LOG_MESSAGE(hdlr,0, ("cinit_encode_wr_recovery illegal wr_recovery value %d passed in configuration!", twr_tck) ); 
          mregs->mr1.wr_recovery=7;// TEMP
          break;
      }

    } 
    else 
    {
      switch (twr_tck)
      {
        case 0 ... 6 : mregs->mr1.wr_recovery = 0; break;
        case 7 ...  12 : mregs->mr1.wr_recovery = 1; break;
        case 13 ... 16 : mregs->mr1.wr_recovery = 2; break;
        case 17 ... 22 : mregs->mr1.wr_recovery = 3; break;
        case 23 ... 28 : mregs->mr1.wr_recovery = 4; break;
        case 29 ... 32 : mregs->mr1.wr_recovery = 5; break;
        case 33 ... 38 : mregs->mr1.wr_recovery = 6; break;
        case 39 ... 44 : mregs->mr1.wr_recovery = 7; break;
        default: 
          ERROR_MESSAGE( ("cinit_encode_wr_recovery illegal wr_recovery value %d passed in configuration!", twr_tck) ); 
          break;
      }
    }
    LOG_MESSAGE(hdlr, 0, ("mr1.wr_recovery= 0x%x\n", mregs->mr1.wr_recovery));
  } else if(IS_LPDDR5) {
      ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
      uint32_t twr_tck;
      uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
      lpddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.lpddr5_mr[p]);
      twr_tck=CEIL(timing->lpddr5_twr_ps,tck_ps);
      uint8_t x16=(hdlr->spdData_m.sdram_width_bits==16) ? 1 : 0;
      uint8_t dvfsc_enable=(hdlr->memCtrlr_m.lpddr5_mr[p].mr19.dvfsc==1) ? 1 : 0;      
      uint8_t wr_lecc=hdlr->memCtrlr_m.lpddr5_mr[p].mr22.wecc;
      ddrSpdData_t* spd = &(hdlr->spdData_m);
      // encoding taken from Samsung LPDDR5 Draft09 ;
      if (x16 &&  dvfsc_enable==0 &&
              spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
         switch (twr_tck)
         {
             case 0 ... 5 : mregs->mr2.nwr = 0; break;
             case 6 ... 10 : mregs->mr2.nwr = 1; break;
             case 11 ... 15 : mregs->mr2.nwr = 2; break;
             case 16 ... 20 : mregs->mr2.nwr = 3; break;
             case 21 ... 25 : mregs->mr2.nwr = 4; break;
             case 26 ... 29 : mregs->mr2.nwr = 5; break;
             default: 
                    ERROR_MESSAGE( ("cinit_encode_wr_recovery illegal twr_tck value %0d passed in configuration!", twr_tck) );                   
                    break;
           
         }
      } // x16, w/o DVFSC, 2:1
      else if (x16 &&  dvfsc_enable==0 &&
              spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
         if (wr_lecc==0) {
            switch (twr_tck)
            {
                case 0 ... 3 : mregs->mr2.nwr = 0; break;
                case 4 ... 5 : mregs->mr2.nwr = 1; break;
                case 6 ... 8 : mregs->mr2.nwr = 2; break;
                case 9 ... 10 : mregs->mr2.nwr = 3; break;
                case 12 ... 13 : mregs->mr2.nwr = 4; break;
                case 14 ... 15 : mregs->mr2.nwr = 5; break;
                case 16 ... 17 : mregs->mr2.nwr = 6; break;
                case 18 ... 20 : mregs->mr2.nwr = 7; break;
                case 21 ... 22 : mregs->mr2.nwr = 8; break;
                case 23 ... 25 : mregs->mr2.nwr = 9; break;
                case 26 ... 27 : mregs->mr2.nwr = 10; break;
                case 28 ... 32 : mregs->mr2.nwr = 11; break;
                default: 
                       ERROR_MESSAGE( ("cinit_encode_wr_recovery illegal twr_tck value %0d passed in configuration!", twr_tck) );                   
                       break;
            }
         } else {
            switch (twr_tck)
            {
                case 18 : mregs->mr2.nwr = 6; break;
                case 21 : mregs->mr2.nwr = 7; break;
                case 23 : mregs->mr2.nwr = 8; break;
              //case 27 : mregs->mr2.nwr = 9; break;
                case 26 : mregs->mr2.nwr = 9; break;
                case 29 : mregs->mr2.nwr = 10; break;
                case 31 : mregs->mr2.nwr = 11; break;
                default: 
                       ERROR_MESSAGE( ("cinit_encode_wr_recovery illegal twr_tck value %0d passed in configuration!", twr_tck) );                   
                       break;
            }
         }
       //dwc_cinit_print("nWR twr_tck=%0d, mregs->mr2.nwr =%0d\n",twr_tck, mregs->mr2.nwr );
       }

  }
#endif //MEMC_LPDDR4
#ifdef MEMC_DDR4
  if(IS_DDR4 ) {
    ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
    mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);

    uint32_t twr_tck = pre_cfg->twr[p][ch];
    if(twr_tck % 2 ==1)
    {
      twr_tck++;
    }
    switch (twr_tck)
    {
      case 10:  mregs->mr0.wr_recovery = 0; break;
      case 12:  mregs->mr0.wr_recovery = 1; break;
      case 14:  mregs->mr0.wr_recovery = 2; break;
      case 16:  mregs->mr0.wr_recovery = 3; break;
      case 18:  mregs->mr0.wr_recovery = 4; break;
      case 20:  mregs->mr0.wr_recovery = 5; break;
      case 22:  mregs->mr0.wr_recovery = 7; break;
      case 24:  mregs->mr0.wr_recovery = 6; break;
      case 26:  mregs->mr0.wr_recovery = 8; break;
      default: 
        ERROR_MESSAGE( ("cinit_encode_wr_recovery illegal wr_recovery value %d passed in configuration!", twr_tck) ); 
        break;
    }
    LOG_MESSAGE(hdlr, 0, ("mr0.wr_recovery= 0x%x\n", mregs->mr0.wr_recovery));
  } else if(IS_DDR5) {
    ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[p]);
    mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
    uint32_t twr_tck = pre_cfg->twr[p][ch];
    if (twr_tck % 6 !=0)
    {
      twr_tck = twr_tck + 6 - twr_tck % 6;
    }
    switch (twr_tck)
    {
      case 48:  mregs->mr6.wr_recovery = 0; break;
      case 54:  mregs->mr6.wr_recovery = 1; break;
      case 60:  mregs->mr6.wr_recovery = 2; break;
      case 66:  mregs->mr6.wr_recovery = 3; break;
      case 72:  mregs->mr6.wr_recovery = 4; break;
      case 78:  mregs->mr6.wr_recovery = 5; break;
      case 84:  mregs->mr6.wr_recovery = 6; break;
      case 90:  mregs->mr6.wr_recovery = 7; break;
      case 96:  mregs->mr6.wr_recovery = 8; break;
      default: 
        ERROR_MESSAGE( ("cinit_encode_wr_recovery illegal wr_recovery value %d passed in configuration!", twr_tck) ); 
        break;
    }
    LOG_MESSAGE(hdlr, 0, ("mr0.wr_recovery= 0x%x\n", mregs->mr6.wr_recovery));
  }
#endif //MEMC_DDR4
}

/** @brief Function to encode mr0 CAS latency.
 * @note see JESD79-4B table 3
 * */
void cinit_encode_cas_latency(SubsysHdlr_t *hdlr,uint32_t p) {
  TRACE();
#ifdef MEMC_DDR4
  if(IS_DDR4) {
    ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
    uint32_t cas_latency = (hdlr->memCtrlr_m.ddr4_mr[p].mr5.read_dbi)?timing->ddr4_tcl_rdbi_tck:timing->ddr4_tcl_tck;
    switch (cas_latency){
      case 9 : mregs->mr0.cl = 0;  break;
      case 10: mregs->mr0.cl = 1;  break;
      case 11: mregs->mr0.cl = 2;  break;
      case 12: mregs->mr0.cl = 3;  break;
      case 13: mregs->mr0.cl = 4;  break;
      case 14: mregs->mr0.cl = 5;  break;
      case 15: mregs->mr0.cl = 6;  break;
      case 16: mregs->mr0.cl = 7;  break;
      case 17: mregs->mr0.cl = 13; break;
      case 18: mregs->mr0.cl = 8;  break;
      case 19: mregs->mr0.cl = 14; break;
      case 20: mregs->mr0.cl = 9;  break;
      case 21: mregs->mr0.cl = 15; break;
      case 22: mregs->mr0.cl = 10; break;
      case 23: mregs->mr0.cl = 12; break;
      case 24: mregs->mr0.cl = 11; break;
      case 26: mregs->mr0.cl = 17; break;
      case 28: mregs->mr0.cl = 19; break;
      case 30: mregs->mr0.cl = 21; break;
      case 32: mregs->mr0.cl = 23; break;
      default:
        ERROR_MESSAGE(("cinit_encode_cas_latency illegal cl value %0d passed in configuration!",cas_latency));
        break;
    } 
  } else if(IS_DDR5) {
    ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[p]);
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
    uint32_t cas_latency = timing->ddr5_tcl_tck;
    switch (cas_latency){
      case 22: mregs->mr0.cl = 0;  break;
      case 24: mregs->mr0.cl = 1;  break;
      case 26: mregs->mr0.cl = 2;  break;
      case 28: mregs->mr0.cl = 3;  break;
      case 30: mregs->mr0.cl = 4;  break;
      case 32: mregs->mr0.cl = 5;  break;
      case 34: mregs->mr0.cl = 6;  break;
      case 36: mregs->mr0.cl = 7;  break;
      case 38: mregs->mr0.cl = 8;  break;
      case 40: mregs->mr0.cl = 9;  break;
      case 42: mregs->mr0.cl = 10; break;
      case 44: mregs->mr0.cl = 11; break;
      case 46: mregs->mr0.cl = 12; break;
      case 48: mregs->mr0.cl = 13; break;
      case 50: mregs->mr0.cl = 14; break;
      default:
        ERROR_MESSAGE(("cinit_encode_cas_latency illegal cl value %0d passed in configuration!",cas_latency));
        break;
    }
    LOG_MESSAGE(hdlr,0,("mr0.cl= 0x%x\n",mregs->mr0.cl));
  }
#endif //MEMC_DDR4
}

/** @brief Function to encode mr2 CAS write latency.
 * @note see JEDEC79-4B table 7.
 * */
void cinit_encode_cas_write_latency(SubsysHdlr_t *hdlr,uint32_t p) {
  TRACE();
#ifdef MEMC_DDR4
  if(IS_DDR4) {
    ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
    mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
    switch(pre_cfg->cwl_x[p]){
      case 9 :mregs->mr2.cwl = 0; break;
      case 10:mregs->mr2.cwl = 1; break;
      case 11:mregs->mr2.cwl = 2; break;
      case 12:mregs->mr2.cwl = 3; break;
      case 14:mregs->mr2.cwl = 4; break;
      case 16:mregs->mr2.cwl = 5; break;
      case 18:mregs->mr2.cwl = 6; break;
      case 20:mregs->mr2.cwl = 7; break;
      default:
        ERROR_MESSAGE(("cinit_encode_cas_write_latency illegal cwl value %0d passed in configuration!",pre_cfg->cwl_x[p]));
        break;
    }
    LOG_MESSAGE(hdlr,0,("mr2.cwl=0x%x\n",mregs->mr2.cwl));
  }
#endif //MEMC_DDR4
}
 /**@brief Function to encode mr6 tccd_l latency.
  * @note see JEDEC79-4B 14
  * */
void cinit_encode_tccd_l_latency(SubsysHdlr_t *hdlr,uint32_t p, uint32_t ch) {
  TRACE();
#ifdef MEMC_DDR4
  if(IS_DDR4) {
    ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
    mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
    
    switch(pre_cfg->t_ccd[p][ch]){
      case 4: mregs->mr6.tccd_l = 0; break;
      case 5: mregs->mr6.tccd_l = 1; break;
      case 6: mregs->mr6.tccd_l = 2; break;
      case 7: mregs->mr6.tccd_l = 3; break;
      case 8: mregs->mr6.tccd_l = 4; break;
      default:
        ERROR_MESSAGE(("cinit_encode_tccd_l_latency ddr4 illegal tccd_l value %0d passed in configuration!",pre_cfg->t_ccd[p][ch]));
        break;
    }
  }else if (IS_DDR5) {
    ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[p]);
    mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);

    switch(pre_cfg->t_ccd[p][ch]) {
      case 8 :mregs->mr13.tccd_l = 0;break;
      case 9 :mregs->mr13.tccd_l = 1;break;
      case 10:mregs->mr13.tccd_l = 2;break;
      case 11:mregs->mr13.tccd_l = 3;break;
      case 12:mregs->mr13.tccd_l = 4;break;
      case 13:mregs->mr13.tccd_l = 5;break;
      case 14:mregs->mr13.tccd_l = 6;break;
      case 15:mregs->mr13.tccd_l = 7;break;
      case 16:mregs->mr13.tccd_l = 8;break;
      default:
        ERROR_MESSAGE(("cinit_encode_tccd_l_latency ddr5 illegal tccd_l value %0d passed in configuration!",pre_cfg->t_ccd[p][ch]));
        break;
    }
    LOG_MESSAGE(hdlr,0,("mr13.tccd_l=0x%x\n",mregs->mr13.tccd_l));
  }
  
#endif //MEMC_DDR4
}

/**@brief Function to encode write cmd latency when CRC and DM are enabled.
 * @note see JEDEC79-4B table 9.
 * */
void cinit_encode_write_cmd_latency(SubsysHdlr_t *hdlr, uint32_t p) {
  TRACE();
#ifdef MEMC_DDR4
  if(IS_DDR4) {
    ddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr4_mr[p]);
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
    switch (timing->ddr4_wcl_tck) {
      case 4: mregs->mr3.wcl = 0;break;
      case 5: mregs->mr3.wcl = 1;break;
      case 6: mregs->mr3.wcl = 2;break;
      default:
        ERROR_MESSAGE(("cinit_encode_write_cmd_latency illegal wcl value %0d passed in configuration!",timing->ddr4_wcl_tck));
        break;
    }
    LOG_MESSAGE(hdlr,0,("mr3.wcl=0x%0x\n",mregs->mr3.wcl));
  }
#endif //MEMC_DDR4
}

/** @brief Function to encode mr2 rl_wl value.
 * @note  see JESD209-4C table 28-1 and table 28-2
 * */
void cinit_encode_rl_wl(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();
#ifdef MEMC_LPDDR4
  if(IS_LPDDR4 ) {
    mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);      
    lpddr4_mode_registers_t* mregs = &(hdlr->memCtrlr_m.lpddr4_mr[p]);
    uint32_t read_dbi=hdlr->memCtrlr_m.lpddr4_mr[p].mr3.read_dbi;
    uint32_t rl = (read_dbi)? pre_cfg->cl_dbi[p] : pre_cfg->cl[p];
    uint32_t wl = (hdlr->memCtrlr_m.lpddr4_mr[p].mr2.wls==0) ?  timing->lpddr4_cwl_seta : timing->lpddr4_cwl_setb; // write latency
    uint32_t mr2_rl, mr2_wl;
    uint32_t x16 = (hdlr->spdData_m.sdram_width_bits==16) ? 1 : 0;
    uint32_t rl_row, wl_row;
    LOG_MESSAGE(hdlr,0,("rl=%0d, wl=%0d read_dbi=%0d, x16=%0d, wls=%0d\n",rl,wl,read_dbi,x16, hdlr->memCtrlr_m.lpddr4_mr[p].mr2.wls ));
    rl_row=cinit_get_rl_row(rl,x16,read_dbi);
    wl_row=cinit_get_wl_row(wl,x16, hdlr->memCtrlr_m.lpddr4_mr[p].mr2.wls);
    mr2_rl=rl_row;
    mr2_wl=wl_row;
    mregs->mr2.rl_wl=(mr2_wl<<3) | mr2_rl;
    LOG_MESSAGE(hdlr, 0, ("mr2.rl_wl= 0x%x\n", mregs->mr2.rl_wl ));
    CONSTRAIN_INSIDE(mregs->mr2.rl_wl, 0,0x3f); // 6 bits
  } else if (IS_LPDDR5) {
    cinit_encode_lpddr5_rl_wl(hdlr,p,ch);
  }
#endif //MEMC_LPDDR4
}



/** @brief Implement a lookup table for nRTP, the row number is the
 * lookup index
 * @note see JESD209-4C table 28-1 and table 28-2.
 * For nRTP x16 and x8 are the same
 * */
uint32_t cinit_get_nrtp(uint8_t row) {
  TRACE();
  uint32_t ret;
  static const uint32_t nrtp[8] = { 8,8,8,8,10,12,14,16};
  ret=nrtp[row];
  return ret;
}



// define a helper macro for the next few functions.
#define FIND_VAL_IN_ARRAY(_val,_array) \
            for(i=0;i<sizeof( _array );i++) { \
                if( _array[i]== _val ) {\
                    ret=i;break;\
                }\
            }\

uint32_t cinit_get_rl_row(uint8_t rl, uint8_t x16, uint8_t dbi) {
  TRACE();
    uint32_t ret,i;
    static const uint32_t x16_rl_nodbi[8] = {6,10,14,20,24,28,32,36};
    static const uint32_t x16_rl_dbi[8]   = {6,12,16,22,28,32,36,40};

    static const uint32_t x8_rl_nodbi[8] = {6,10,16,22,26,32,36,40};
    static const uint32_t x8_rl_dbi[8]   = {6,12,18,24,30,36,40,44};
    ret=0;
    if(x16==1) {
        if(dbi==1) {
            FIND_VAL_IN_ARRAY(rl, x16_rl_dbi)
        } else {
            FIND_VAL_IN_ARRAY(rl, x16_rl_nodbi)
        }
    } else { // x8
        if(dbi==1) {
            FIND_VAL_IN_ARRAY(rl, x8_rl_dbi)
        } else {
            FIND_VAL_IN_ARRAY(rl, x8_rl_nodbi)
        }
   }
   if(ret==0 || ret>8) {
     ERROR_MESSAGE(("cinit_get_rl_row  rl=%0d, x16=%0d, dbi=%0d is invalid",rl,x16,dbi));
   } else {
    // printf("cinit_get_rl_row ret=%0d\n",ret);
   }
   return ret;
}

/** @brief */
uint32_t cinit_get_wl_row(uint8_t wl, uint8_t x16, uint8_t wls) {
  TRACE();
  uint32_t ret,i;
  static const uint32_t x16_wl_seta[8]  = {4,6,8,10,12,14,16,18};
  static const uint32_t x16_wl_setb[8]  = {4,8,12,18,22,26,30,34};
  // values look the same
  static const uint32_t x8_wl_seta[8]  = {4,6,8,10,12,14,16,18};
  static const uint32_t x8_wl_setb[8]  = {4,8,12,18,22,26,30,34};
  ret=0;
  if(x16==1) {
    if(wls==1) {
        FIND_VAL_IN_ARRAY(wl, x16_wl_setb)
    } else {
        FIND_VAL_IN_ARRAY(wl, x16_wl_seta)
    }
  } else {
    if(wls==1) {
        FIND_VAL_IN_ARRAY(wl, x8_wl_setb)
    } else {
        if(wls==1) {
            FIND_VAL_IN_ARRAY(wl, x8_wl_setb)
        } else {
            FIND_VAL_IN_ARRAY(wl, x8_wl_seta)
        }
    }
  }
 if(ret==0) {
   ERROR_MESSAGE(("cinit_get_wl_row  wl=%0d, x16=%0d, wls=%0d is invalid",wl,x16,wls));
 } else {
   // printf("cinit_get_wl_row ret=%0d\n",ret);
 }

 return ret;
}
/** @brief method to return the min value for t_xsr.
 * This is used by simulation env to set the min value in a SV constraint.
 * */
uint32_t dwc_cinit_get_min_t_xsr( SubsysHdlr_t *hdlr, uint32_t tck_ps) {
  TRACE();
  uint32_t ret=0;
#ifdef MEMC_LPDDR4
  if( IS_LPDDR4 ) {
    uint32_t trfcab = dwc_cinit_get_lpddr4_trfcab(hdlr);
    uint32_t lpddr4_txsr_ps;
    lpddr4_txsr_ps=max( (trfcab+7500), 2*tck_ps);
    ret=cinit_ps_to_tck( lpddr4_txsr_ps, tck_ps );
  } else if (IS_LPDDR5) {
    uint32_t trfcab, lpddr5_txsr_ps;
    trfcab=dwc_cinit_get_lpddr5_trfcab(hdlr);
    lpddr5_txsr_ps= max(7500,2*tck_ps)+trfcab;
     ret=  cinit_ps_to_tck( lpddr5_txsr_ps, tck_ps );
  }
#endif //MEMC_LPDDR4
  return ret;
}

uint32_t dwc_cinit_get_min_t_xp( SubsysHdlr_t *hdlr, uint32_t p) {
  TRACE();
  if(hdlr->is_timing_set[p]==0) {
    dwc_cinit_print("Timing is not set so calling here\n");
    dwc_cinit_ddr_set_timing(hdlr);
  }
  uint32_t ret=0;
#ifdef MEMC_LPDDR4
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  if( IS_LPDDR4 ) {
    ret = timing->lpddr4_txp;

  }
  if( IS_LPDDR5 ) {
    ret = timing->lpddr5_txp_ps;
  }  
#endif //MEMC_LPDDR4

  return ret;
}
/** @brief method to encode MR1 OP[7:4] for LPDDR5 */
void cinit_encode_lpddr5_rl_wl(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
#ifdef MEMC_LPDDR4
  TRACE();
  uint32_t wl=hdlr->memCtrlr_m.pre_cfg.wl[p][ch];
  uint8_t wl_op, rl_nrtp;
  uint8_t x16=(hdlr->spdData_m.sdram_width_bits==16) ? 1 : 0;
  uint8_t dvfsc_enable=(hdlr->memCtrlr_m.lpddr5_mr[p].mr19.dvfsc==1) ? 1 : 0;      
  uint8_t wl_seta= (hdlr->memCtrlr_m.lpddr5_mr[p].mr3.wls==0) ? 1 : 0;
  ddrSpdData_t* spd = &(hdlr->spdData_m);
  dwc_cinit_print("wl=%0d,x16=%0d, wl_seta=%0d, dvfsc_enable=%0d, lpddr5_wckck_ratio=%0d\n",wl,x16, wl_seta, dvfsc_enable,spd->lpddr5_wckck_ratio );
  if (x16 && wl_seta && dvfsc_enable==0 && spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    switch (wl)
    {
        case 4 : wl_op  = 0; break;
        case 6 : wl_op  = 2; break;
        case 8 : wl_op  = 3; break;
        case 10 : wl_op  = 5; break;
        default : wl_op  = 0; break;
    }
  }
  else if (x16 && !wl_seta && dvfsc_enable==0 && spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    switch (wl)
    {
        case 4 : wl_op  = 0; break;
        case 6 : wl_op  = 1; break;
        case 8 : wl_op  = 2; break;
        case 10 : wl_op  = 3; break;
        case 14 : wl_op  = 4; break;
        case 16 : wl_op  = 5; break;
        default : wl_op  = 0; break;
    }
  }else if (x16 && wl_seta && dvfsc_enable==0 && spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    switch (wl)
    {   // set A
        case 2 : wl_op  = 1; break;
        case 3 : wl_op  = 2; break;
        case 4 : wl_op  = 4; break;
        case 5 : wl_op  = 5; break;
        case 6 : wl_op  = 6; break;
        case 7 : wl_op  = 8; break;
        case 8 : wl_op  = 9; break;
        case 9 : wl_op  = 10; break;
        default : wl_op  = 0; break;
    }
  }
  else if (x16 && !wl_seta && dvfsc_enable==0 && spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    switch (wl)
    {   // set B
        case 3 : wl_op  = 1; break;
        case 4 : wl_op  = 2; break;
        case 5 : wl_op  = 3; break;
        case 7 : wl_op  = 4; break;
        case 8 : wl_op  = 5; break;
        case 9 : wl_op  = 6; break;
        case 11 : wl_op  = 7; break;
        case 12 : wl_op  = 8; break;
        case 14 : wl_op  = 9; break;
        case 15 : wl_op  = 10; break;
        case 16 : wl_op  = 11; break;
        default : wl_op  = 0; break;
    }
  }
  else if(!x16 && wl_seta && !dvfsc_enable &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    // x8/ch set A
      switch (wl) {   
          case 2 : wl_op = 0; break;
          case 3 : wl_op = 2; break;
          case 4 : wl_op = 3; break;
          case 5 : wl_op = 5; break;
          case 6 : wl_op = 6; break;
          case 7 : wl_op = 8; break;
          case 8 : wl_op = 9; break;
          case 9 : wl_op = 10; break;
          default : wl_op  = 0; break;
        
      }
  }
  else if(!x16 && !wl_seta && !dvfsc_enable &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    // x8/ch set B
      switch (wl) {   
        case 2 : wl_op  = 0; break;
        case 3 : wl_op  = 1; break;
        case 4 : wl_op  = 2; break;
        case 5 : wl_op  = 3; break;
        case 7 : wl_op  = 4; break;
        case 8 : wl_op  = 5; break;
        case 9 : wl_op  = 6; break;
        case 11 : wl_op  = 7; break;
        case 12 : wl_op  = 8; break;
        case 14 : wl_op  = 9; break;
        case 15 : wl_op  = 10; break;
        case 16 : wl_op  = 11; break;
        default : wl_op  = 0; break;        
      }
  }
  else if(!x16 && !wl_seta && !dvfsc_enable &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    // x8/ch set B
      switch (wl) {   
        case 4 : wl_op  = 0; break;
        case 6 : wl_op  = 1; break;
        case 8 : wl_op  = 2; break;
        case 10 : wl_op  = 3; break;
        case 14 : wl_op  = 4; break;
        case 16 : wl_op  = 5; break;
        default : wl_op  = 0; break;        
      }
  }  
  else if (x16 && wl_seta && dvfsc_enable==1 && spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    switch (wl) {
        case 4 : wl_op  = 1; break;
        case 6 : wl_op  = 2; break;
        default : wl_op  = 0; break;
    }
  }
  else if (x16 && wl_seta && dvfsc_enable==1 && spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    switch (wl) {      
        case 2 : wl_op  = 1; break;
        case 3 : wl_op  = 2; break;
        default : wl_op = 0; break;
    }
  }
  else if (x16 && !wl_seta && dvfsc_enable==1 && spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    switch (wl) {
        case 4 : wl_op  = 0; break;
        case 6 : wl_op  = 1; break;
        case 8 : wl_op  = 2; break;
        default : wl_op  = 0; break;
    }
  }
  else if (x16 && !wl_seta && dvfsc_enable==1 && spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    switch (wl) {      
        case 2 : wl_op  = 0; break;
        case 3 : wl_op  = 1; break;
        case 4 : wl_op  = 2; break;
        default : wl_op = 0; break;
    }
  }
  else if (!x16 && wl_seta && dvfsc_enable==1 && spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    switch (wl) {
        case 4 : wl_op  = 1; break;
        case 6 : wl_op  = 2; break;
        default : wl_op  = 0; break;
    }
  }
  else if (!x16 && wl_seta && dvfsc_enable==1 && spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    switch (wl) {      
        case 2 : wl_op  = 1; break;
        case 3 : wl_op  = 2; break;
        default : wl_op = 0; break;
    }
  }
  else if (!x16 && !wl_seta && dvfsc_enable==1 && spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    switch (wl) {
        case 4 : wl_op  = 0; break;
        case 6 : wl_op  = 1; break;
        case 8 : wl_op  = 2; break;
        default : wl_op  = 0; break;
    }
  }
  else if (!x16 && !wl_seta && dvfsc_enable==1 && spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    switch (wl) {      
        case 2 : wl_op  = 0; break;
        case 3 : wl_op  = 1; break;
        case 4 : wl_op  = 2; break;
        default : wl_op = 0; break;
    }
  }
  else {
	ERROR_MESSAGE(("cinit_encode_lpddr5_rl_wl setting not yet supported for wl_op."));
  }
  hdlr->memCtrlr_m.lpddr5_mr[p].mr1.write_latency=wl_op;
  uint8_t read_dbi=hdlr->memCtrlr_m.lpddr5_mr[p].mr3.read_dbi;
  uint8_t rd_lecc=hdlr->memCtrlr_m.lpddr5_mr[p].mr22.recc;

  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
 
  // Next encode mr2.rl_nrtp
  if (x16 && dvfsc_enable==0 &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    if(read_dbi==0) {
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 6 : rl_nrtp=0;break;
           case 7 ... 8 : rl_nrtp=1;break;
           case 9 ... 10 : rl_nrtp=2;break;
           case 11 ... 12 : rl_nrtp=3;break;
           case 13 ... 16 : rl_nrtp=4;break;
           case 17 ... 18 : rl_nrtp=5;break;
           default : rl_nrtp=0;break;
       }
    } else {
       // DBI-RD enabled
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 6 : rl_nrtp=0;break;
           case 7 ... 8 : rl_nrtp=1;break;
           case 9 ... 10 : rl_nrtp=2;break;
           case 11 ... 14 : rl_nrtp=3;break;
           case 15 ... 16 : rl_nrtp=4;break;
           case 17 ... 20 : rl_nrtp=5;break;
           default : rl_nrtp=0;break;
       }

    }
  }
  else if (x16 && dvfsc_enable==0 &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    if(read_dbi==0) {
       if(rd_lecc==0) {
          switch(timing->lpddr5_rl_tck) {
              case 0 ... 3 : rl_nrtp=0;break;
              case 4 : rl_nrtp=1;break;
              case 5 : rl_nrtp=2;break;
              case 6 : rl_nrtp=3;break;
              case 7 ... 8 : rl_nrtp=4;break;
              case 9 : rl_nrtp=5;break;
              case 10 ... 11 : rl_nrtp=6;break;
              case 12 ... 13 : rl_nrtp=(timing->lpddr5_nrtp==4) ? 7 : 8;break;
              case 14 ... 15 : rl_nrtp=(timing->lpddr5_nrtp==5) ? 9 : 9;break;
              case 16 : rl_nrtp=(timing->lpddr5_nrtp==5) ? 10: 10;break;
              case 17 : rl_nrtp=(timing->lpddr5_nrtp==6) ? 11: 10;break;
              case 18 : rl_nrtp=11;break;
              default : rl_nrtp=0; ERROR_MESSAGE(("default case for rl_nrtp should not be reached"));
              break;
          }
       } else {
          switch(timing->lpddr5_rl_tck) {
              case 12 : rl_nrtp=6;break;
              case 13 : rl_nrtp=7;break;
              case 15 : rl_nrtp=8;break;
              case 17 : rl_nrtp=9;break;
              case 18 : rl_nrtp=10;break;
              case 19 : rl_nrtp=11;break;
              default : rl_nrtp=0; ERROR_MESSAGE(("default case for rl_nrtp should not be reached"));
              break;
          }
       }
    } else {
       // DBI-RD enabled
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 3 : rl_nrtp=0;break;
           case 4 : rl_nrtp=1;break;
           case 5 : rl_nrtp=2;break;
           case 6 ... 8 : rl_nrtp=4;break;
           case 9 ... 10 : rl_nrtp=5;break;
           case 11 : rl_nrtp=6;break;
           case 12 ... 13 : rl_nrtp= 7;break;
           case 14 ... 15 : rl_nrtp= 8;break;
           case 16 : rl_nrtp=9;break;
           case 17 : rl_nrtp=10;break;
           case 18 : rl_nrtp=11;break;
           default : rl_nrtp=0; ERROR_MESSAGE(("default case for rl_nrtp should not be reached"));
           break;
       }

    }
  } else if(!x16 && !dvfsc_enable &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    if(read_dbi==0) {
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 6 : rl_nrtp=0;break;
           case 7 ... 8 : rl_nrtp=1;break;
           case 9 ... 10 : rl_nrtp=2;break;
           case 11 ... 14 : rl_nrtp=3;break;
           case 15 ... 16 : rl_nrtp=4;break;
           case 17 ... 20 : rl_nrtp=5;break;
           default : rl_nrtp=0;break;
       }
    } else {
       // DBI-RD enabled
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 6 : rl_nrtp=0;break;
           case 7 ... 8 : rl_nrtp=1;break;
           case 9 ... 12 : rl_nrtp=2;break;
           case 13 ... 14 : rl_nrtp=3;break;
           case 15 ... 18 : rl_nrtp=4;break;
           case 19 ... 20 : rl_nrtp=5;break;         
           default : rl_nrtp=0;break;
       }

    }
    
  }
  else if(!x16 && !dvfsc_enable &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    if(read_dbi==0) {
       if(rd_lecc==0) {
          switch(timing->lpddr5_rl_tck) {
              case 3 : rl_nrtp=0;break;
              case 4 : rl_nrtp=1;break;
              case 5 : rl_nrtp=2;break;
              case 7 : rl_nrtp=3;break;
              case 8 : rl_nrtp=4;break;
              case 10 : rl_nrtp=5;break;
              case 11 : rl_nrtp=6;break;
              case 13 : rl_nrtp=7;break;
              case 14 : rl_nrtp=8;break;
              case 16 : rl_nrtp=9;break;
              case 17 : rl_nrtp=10;break;
              case 18 : rl_nrtp=11;break;
              default : rl_nrtp=0;break;
          }
       } else {
          switch(timing->lpddr5_rl_tck) {
              case 13 : rl_nrtp=6;break;
              case 14 : rl_nrtp=7;break;
              case 16 : rl_nrtp=8;break;
              case 18 : rl_nrtp=9;break;
              case 20 : rl_nrtp=10;break;
              case 21 : rl_nrtp=11;break;
              default : rl_nrtp=0;break;
          }
       }
    }
    else {
       // DBI-RD enabled
       switch(timing->lpddr5_rl_tck) {
           case 3 : rl_nrtp=0;break;
           case 4 : rl_nrtp=1;break;
           case 6 : rl_nrtp=2;break;
           case 7 : rl_nrtp=3;break;
           case 9 : rl_nrtp=4;break;
           case 10 : rl_nrtp=5;break;
           case 12 : rl_nrtp=6;break;
           case 14 : rl_nrtp=7;break;
           case 15 : rl_nrtp=8;break;
           case 17 : rl_nrtp=9;break;
           case 19 : rl_nrtp=10;break;
           case 20 : rl_nrtp=11;break;
           default : rl_nrtp=0;break;

       }
       
    }
  }
  else if (x16 && dvfsc_enable==1 &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    if(read_dbi==0) {
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 6 : rl_nrtp=0;break;
           case 7 ... 8 : rl_nrtp=1;break;
           case 9 ... 12 : rl_nrtp=2;break;
           default : rl_nrtp=0;break;
       }
    } else {
       // DBI-RD enabled
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 6 : rl_nrtp=0;break;
           case 7 ... 10 : rl_nrtp=1;break;
           case 11 ... 12 : rl_nrtp=2;break;
           default : rl_nrtp=0;break;
       }

    }
  }
  else if (x16 && dvfsc_enable==1 &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    if(read_dbi==0) {
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 3 : rl_nrtp=0;break;
           case 4 : rl_nrtp=1;break;
           case 5 ... 6 : rl_nrtp=2;break;
           default : rl_nrtp=0; ERROR_MESSAGE(("default case for rl_nrtp should not be reached"));
           break;
       }
    } else {
       // DBI-RD enabled
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 3 : rl_nrtp=0;break;
           case 4 ... 5 : rl_nrtp=1;break;
           case 6 : rl_nrtp=2;break;
           default : rl_nrtp=0; ERROR_MESSAGE(("default case for rl_nrtp should not be reached"));
           break;
       }

    }
  } else if(!x16 && (dvfsc_enable==1) &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_2_1) {
    if(read_dbi==0) {
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 6 : rl_nrtp=0;break;
           case 7 ... 10 : rl_nrtp=1;break;
           case 11 ... 12 : rl_nrtp=2;break;
           default : rl_nrtp=0;break;
       }
    } else {
       // DBI-RD enabled
       switch(timing->lpddr5_rl_tck) {
           case 0 ... 6 : rl_nrtp=0;break;
           case 7 ... 10 : rl_nrtp=1;break;
           case 11 ... 14 : rl_nrtp=2;break;
           default : rl_nrtp=0;break;
       }

    }
    
  }
  else if(!x16 && dvfsc_enable==1 &&
          spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) {
    if(read_dbi==0) {
       switch(timing->lpddr5_rl_tck) {
           case 3 : rl_nrtp=0;break;
           case 4 ... 5 : rl_nrtp=1;break;
           case 6 : rl_nrtp=2;break;
           default : rl_nrtp=0;break;

       }
    }
    else {
       // DBI-RD enabled
       switch(timing->lpddr5_rl_tck) {
           case 3 : rl_nrtp=0;break;
           case 4 ... 5: rl_nrtp=1;break;
           case 6 ... 7: rl_nrtp=2;break;
           default : rl_nrtp=0;break;

       }
       
    }
  }
  else {
    ERROR_MESSAGE(("cinit_encode_lpddr5_rl_wl setting not yet supported."));
  }
  hdlr->memCtrlr_m.lpddr5_mr[p].mr2.rl_nrtp=rl_nrtp;
#endif // MEMC_LPDDR4
}
/** @brief function to pre-calculate DFI timings such as dfi_t_rddata_en
 * and dfi_tphy_wrlat.
 * @note Only supports ddrPhyType_m = DWC_LPDDR4X_MULTIPHY
 */
void cinit_cal_lpddr4x_multiphy_dfi_timings(SubsysHdlr_t *hdlr, uint32_t p,uint32_t ch) {
  TRACE();
#ifdef MEMC_LPDDR4
  uint32_t DFI_RL_SUB, DFI_WL_SUB, trddata_en_pipe,tphy_wrlat_pipe;
  uint32_t dfi_t_rddata_en_int,dfi_tphy_wrlat_int;
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  // values here come from DWC LPDDR4 multiPHY V2 databook.
  DFI_RL_SUB=5;
  DFI_WL_SUB=5;
  trddata_en_pipe=2*(hdlr->phy_timing_params.pipe_dfi_misc-
          hdlr->phy_timing_params.pipe_dfi_rd);

  tphy_wrlat_pipe=2*(hdlr->phy_timing_params.pipe_dfi_misc-
          hdlr->phy_timing_params.pipe_dfi_wr);

  dfi_t_rddata_en_int=pre_cfg->cl[p]+hdlr->spdData_m.tAL-DFI_RL_SUB;
  dfi_tphy_wrlat_int=pre_cfg->cwl_x[p]+hdlr->spdData_m.tAL-DFI_WL_SUB;

   if( IS_LPDDR4 ) {
      if(hdlr->memCtrlr_m.lpddr4_mr[p].mr3.read_dbi==1) {
          pre_cfg->dfi_t_rddata_en[p][ch]=dfi_t_rddata_en_int-
              (pre_cfg->cl[p] - pre_cfg->cl_dbi[p]) + trddata_en_pipe;          
      } else {
          pre_cfg->dfi_t_rddata_en[p][ch]=dfi_t_rddata_en_int+trddata_en_pipe;

      }
      pre_cfg->dfi_tphy_wrlat[p][ch]=dfi_tphy_wrlat_int+tphy_wrlat_pipe+1;
  }
  // Specific to PHY Type 6,7,8
  pre_cfg->dfi_t_dram_clk_disable[p][ch]=5 +
      (2*hdlr->phy_timing_params.pipe_dfi_misc) -2;
  pre_cfg->dfi_t_dram_clk_enable[p][ch]=5+
      (2*hdlr->phy_timing_params.pipe_dfi_misc);
#endif
}

/** @brief method to caluclate DFI timing parameters  
 * Based on information from DesignWare Cores LPDDR54 PHY, PUB 1.0 Design Specification V1.2
 * PclkPtrInitVal default value should be 5 UI which is 2.5 MEMCLKs
 */
void cinit_cal_lpddr54_dfi_timings(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE(); 
#ifdef DDRCTL_LPDDR
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_dyn_cfg_t* dyn = &(hdlr->memCtrlr_m.dyn_cfg); // A handle to dynamic configuration options.
  uint32_t tck_ps=hdlr->spdData_m.tck_ps[p];
  uint32_t DFI_WL_SUB;
  if( IS_LPDDR4 ) {
    // where WL=DRAM_WL+AL+PL+tDQSSnom (tDQSSnom= 1tck)
    // garrigan pre_cfg->dfi_tphy_wrlat[p][ch]= pre_cfg->cwl_x[p] + 1 - DFI_WL_SUB ;
    // DFI_WL_SUB=5 when (core_ddrc_core_clk < = 800 Mhz)
    // DFI_WL_SUB=7 when (core_ddrc_core_clk >  800 Mhz)
    #ifdef MEMC_FREQ_RATIO_4
       DFI_WL_SUB = (tck_ps*(dyn->frequency_ratio[p][ch]+1)*2 < 1250) ? 7 : 5 ;
    #else
      DFI_WL_SUB =  (tck_ps*2 < 1250) ? 7 : 5 ;
     #endif
     pre_cfg->dfi_tphy_wrlat[p][ch]= pre_cfg->cwl_x[p] + 1 - DFI_WL_SUB ;
    // trddata_en=RL-5
    // where 1. RL = DRAM_RL + AL + PL 
    if(hdlr->memCtrlr_m.lpddr4_mr[p].mr3.read_dbi==1) {
      pre_cfg->dfi_t_rddata_en[p][ch]=pre_cfg->cl[p]-5-
            (pre_cfg->cl[p] - pre_cfg->cl_dbi[p]);          
      } else {
      pre_cfg->dfi_t_rddata_en[p][ch]=pre_cfg->cl[p]-5;
    }
  }
  else if(IS_LPDDR5) {
    DFI_WL_SUB=5;
    ddrSpdData_t* spd = &(hdlr->spdData_m);
    uint32_t ratio =  (spd->lpddr5_wckck_ratio==DWC_WCKCK_4_1) ? 4 : 2;
    pre_cfg->dfi_tphy_wrlat[p][ch]= (pre_cfg->wl[p][ch]*ratio)-DFI_WL_SUB;
    pre_cfg->dfi_t_rddata_en[p][ch]=(pre_cfg->rl[p][ch]*ratio)-5;
  }

 // default values for now.
 pre_cfg->dfi_t_dram_clk_disable[p][ch]=5;
 pre_cfg->dfi_t_dram_clk_enable[p][ch]=5;
#endif
}

/** @brief function  */
void cinit_cal_ddr43_dfi_timings(SubsysHdlr_t *hdlr, uint32_t p, uint32_t ch) {
  TRACE();   
#ifdef MEMC_DDR4  
  uint32_t DFI_RL_SUB, DFI_WL_SUB, trddata_en_pipe,t_dqsck,tphy_wrlat_pipe;
  uint32_t dfi_t_rddata_en_int,dfi_tphy_wrlat_int;
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  // values here come from DWC LPDDR4 multiPHY V2 databook.
  DFI_RL_SUB=5;
  DFI_WL_SUB=5;
  t_dqsck=0; // TODO 
  trddata_en_pipe=2*(hdlr->phy_timing_params.pipe_dfi_misc-
          hdlr->phy_timing_params.pipe_dfi_rd);

  tphy_wrlat_pipe=2*(hdlr->phy_timing_params.pipe_dfi_misc-
          hdlr->phy_timing_params.pipe_dfi_wr);

  dfi_t_rddata_en_int=pre_cfg->cl[p]+hdlr->spdData_m.tAL-DFI_RL_SUB;
  dfi_tphy_wrlat_int=pre_cfg->cwl_x[p]+hdlr->spdData_m.tAL-DFI_WL_SUB;  
  if(hdlr->ddrPhyType_m==DWC_DDR43_PHY) { dfi_t_rddata_en_int+=t_dqsck; }
  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  if(IS_DDR4) {
      if(hdlr->memCtrlr_m.ddr4_mr[p].mr5.read_dbi ==1) {
          pre_cfg->dfi_t_rddata_en[p][ch]=dfi_t_rddata_en_int+(timing->ddr4_tcl_rdbi_tck -pre_cfg->cl[p])+
              (hdlr->spdData_m.tAL_RDBI - hdlr->spdData_m.tAL ) + trddata_en_pipe;
    
        pre_cfg->dfi_tphy_wrlat[p][ch]=(hdlr->spdData_m.tAL_RDBI+pre_cfg->cwl_x[p]-DFI_WL_SUB)+tphy_wrlat_pipe;
      } else {
          pre_cfg->dfi_t_rddata_en[p][ch]=dfi_t_rddata_en_int+trddata_en_pipe;
          pre_cfg->dfi_tphy_wrlat[p][ch]=dfi_tphy_wrlat_int+tphy_wrlat_pipe;
      }
  }
  // Specific to PHY Type 6,7,8
  pre_cfg->dfi_t_dram_clk_disable[p][ch]=5 +
      (2*hdlr->phy_timing_params.pipe_dfi_misc) -2;
  pre_cfg->dfi_t_dram_clk_enable[p][ch]=5+
      (2*hdlr->phy_timing_params.pipe_dfi_misc);
#endif
}

/** @brief function  */
void cinit_cal_ddr54_dfi_timings(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();   
#ifdef MEMC_DDR4
  uint32_t DFI_RL_SUB, DFI_WL_SUB, trddata_en_pipe,tphy_wrlat_pipe;
  uint32_t dfi_t_rddata_en_int,dfi_tphy_wrlat_int;
  mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);
  mctl_qdyn_cfg_t* qdyn=&(hdlr->memCtrlr_m.qdyn_cfg);
  TRACE();
  // values here come from DWC LPDDR4 multiPHY V2 databook.
  if(IS_DDR5) {
    DFI_RL_SUB=9;
    DFI_WL_SUB=9;
  }else if(IS_DDR4){
    DFI_RL_SUB=5;
    DFI_WL_SUB=5;
  }

  trddata_en_pipe=2*(hdlr->phy_timing_params.pipe_dfi_misc-
          hdlr->phy_timing_params.pipe_dfi_rd);

  tphy_wrlat_pipe=2*(hdlr->phy_timing_params.pipe_dfi_misc-
          hdlr->phy_timing_params.pipe_dfi_wr);

  dfi_t_rddata_en_int=pre_cfg->cl[p]+hdlr->spdData_m.tAL-DFI_RL_SUB;

  dfi_tphy_wrlat_int=pre_cfg->cwl_x[p]+hdlr->spdData_m.tAL-DFI_WL_SUB;

  ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
  if(IS_DDR4) {
    if(hdlr->memCtrlr_m.ddr4_mr[p].mr5.read_dbi ==1) {
      pre_cfg->dfi_t_rddata_en[p][dch]=dfi_t_rddata_en_int+(timing->ddr4_tcl_rdbi_tck -pre_cfg->cl[p])+
          (hdlr->spdData_m.tAL_RDBI - hdlr->spdData_m.tAL ) + trddata_en_pipe;
  
      pre_cfg->dfi_tphy_wrlat[p][dch]=(hdlr->spdData_m.tAL_RDBI+pre_cfg->cwl_x[p]-DFI_WL_SUB)+tphy_wrlat_pipe;
    } else {
      pre_cfg->dfi_t_rddata_en[p][dch]=dfi_t_rddata_en_int+trddata_en_pipe;
      pre_cfg->dfi_tphy_wrlat[p][dch]=dfi_tphy_wrlat_int+tphy_wrlat_pipe;
    }
  } else if(IS_DDR5) {
    pre_cfg->dfi_t_rddata_en[p][dch] = dfi_t_rddata_en_int + trddata_en_pipe;
    pre_cfg->dfi_tphy_wrlat[p][dch] = dfi_tphy_wrlat_int + tphy_wrlat_pipe;
  }
  /** @brief Table 5-12 of phy databook 1.00a, unit : DFI clock */
  pre_cfg->dfi_t_dram_clk_disable[p][dch]= qdyn->dfi_t_ctrl_delay[p][dch];
  pre_cfg->dfi_t_dram_clk_enable[p][dch]= qdyn->dfi_t_ctrl_delay[p][dch];

#endif
    
}

/** @brief method to calculate rd_min_gap based on ddr5 mr8 read pre/post_ample setting */
uint32_t cinit_cal_ddr5_rd_min_gap(SubsysHdlr_t *hdlr) {
  TRACE();
  uint32_t rd_min_gap = 0;
#ifdef MEMC_DDR5  
  ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[0]);
  uint32_t t_rd_preamble, t_rd_postample;
  switch(mregs->mr8.rd_preamble)
  {
    case 0: t_rd_preamble = 1; break;
    case 1 ... 2: t_rd_preamble = 2; break;
    case 3: t_rd_preamble = 3; break;
    case 4: t_rd_preamble = 4; break;
    default :
      LOG_MESSAGE(hdlr,0,("cinit_cal_ddr5_rd_min_gap illegal mr8.rd_preamble value %0d passed in configuration!",mregs->mr8.rd_preamble));
      break;
  }
  switch(mregs->mr8.rd_postamble)
  {
    case 0: t_rd_postample = 1; break;
    case 1: t_rd_postample = 2; break;
    default :
      LOG_MESSAGE(hdlr,0,("cinit_cal_ddr5_rd_min_gap illegal mr8.rd_postamble value %0d passed in configuration!",mregs->mr8.rd_postamble));
      break;
  }
  rd_min_gap = t_rd_preamble + t_rd_postample;

#endif //MEMC_DDR5
  return rd_min_gap;
}

/** @brief method to calculate wr_min_gap based on ddr5 mr8 write pre/post_ample setting */
uint32_t cinit_cal_ddr5_wr_min_gap(SubsysHdlr_t *hdlr) {
  TRACE();
  uint32_t wr_min_gap = 0;
#ifdef MEMC_DDR5  
  ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[0]);
  uint32_t t_wr_postample;
  uint32_t t_wr_preamble = cinit_get_ddr5_twpre(hdlr,0);
  switch(mregs->mr8.wr_postamble)
  {
    case 0: t_wr_postample = 1; break;
    case 1: t_wr_postample = 2; break;
    default :
      LOG_MESSAGE(hdlr,0,("cinit_cal_ddr5_wr_min_gap illegal mr8.wr_postamble value %0d passed in configuration!",mregs->mr8.wr_postamble));
      break;
  }
  wr_min_gap = t_wr_preamble + t_wr_postample;

#endif //MEMC_DDR5
  return wr_min_gap;
}

/** @brief method to get twpre bsed on ddr5 mr8 write preamble setting */
uint32_t cinit_get_ddr5_twpre(SubsysHdlr_t *hdlr,uint32_t p) {
  TRACE();
  uint8_t t_wr_preamble = 0;
#ifdef MEMC_DDR5
  ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[p]);
  switch(mregs->mr8.wr_preamble)
  {
    case 1: t_wr_preamble = 2; break;
    case 2: t_wr_preamble = 3; break;
    case 3: t_wr_preamble = 4; break;
    default :
      LOG_MESSAGE(hdlr,0,("cinit_get_ddr5_twpre illegal mr8.wr_preamble value %0d passed in configuration!",mregs->mr8.wr_preamble));
      break;
  }

#endif
  return t_wr_preamble;
  
}

/** @brief method to get twpre bsed on ddr5 mr40 read DQS offset setting */
uint32_t cinit_get_ddr5_t_rd_dqs_offset(SubsysHdlr_t *hdlr, uint32_t p) {
  TRACE();
  uint8_t t_rd_dqs_offset = 0;
#ifdef MEMC_DDR5
  ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[p]);
  switch(mregs->mr40.rd_dqs_offset)
  {
    case 0: t_rd_dqs_offset = 0; break;
    case 1: t_rd_dqs_offset = 1; break;
    case 2: t_rd_dqs_offset = 2; break;
    case 3: t_rd_dqs_offset = 3; break;
    default :
      LOG_MESSAGE(hdlr,0,("cinit_get_ddr5_t_rd_dqs_offset illegal mr4.rd_dqs_offset value %0d passed in configuration!",mregs->mr40.rd_dqs_offset));
      break;
  }

#endif
  return t_rd_dqs_offset;
  
}

/** @brief method to encode ddr5 tRTP latency */
void cinit_encode_ddr5_trtp_latency(SubsysHdlr_t *hdlr, uint32_t p, uint32_t dch) {
  TRACE();
#ifdef MEMC_DDR5
  ddr5_mode_registers_t* mregs = &(hdlr->memCtrlr_m.ddr5_mr[p]);
  mctl_pre_cfg* pre_cfg = &(hdlr->memCtrlr_m.pre_cfg);
  uint32_t t_rtp = pre_cfg->t_rtp[p][dch];
  if(t_rtp == 13 || t_rtp == 16 || t_rtp == 19 || t_rtp == 22 || t_rtp == 25 ){
    t_rtp--;
  }
  switch (t_rtp)
  {
    case 12: mregs->mr6.trtp = 0;break;
    case 14: mregs->mr6.trtp = 1;break;
    case 15: mregs->mr6.trtp = 2;break;
    case 17: mregs->mr6.trtp = 3;break;
    case 18: mregs->mr6.trtp = 4;break;
    case 20: mregs->mr6.trtp = 5;break;
    case 21: mregs->mr6.trtp = 6;break;
    case 23: mregs->mr6.trtp = 7;break;
    case 24: mregs->mr6.trtp = 8;break;
    default :
      LOG_MESSAGE(hdlr,0,("cinit_encode_wr_recovery illegal mr6.trtp value %0d passed in configuration!",t_rtp));
      break;
  }
  LOG_MESSAGE(hdlr,0,(" mr6.trtp[%0d] = %0d ",p,mregs->mr6.trtp));

#endif
}
