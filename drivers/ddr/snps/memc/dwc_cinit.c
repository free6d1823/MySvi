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
 * @file cinit.c
 * @brief Controller initialization software library.
 */
 
#include <assert.h>
#include "dwc_cinit.h"


FILE *outFilePtr;

extern void* dwc_ddrphy_phyinit_configAlloc(void);

// Declare the version of this software.
#ifndef FW_VERSION
  #define FW_VERSION "3.20a"
#endif

char *g_cinit_version=FW_VERSION;

/// Create an array of string to print PHY type (debug only)
const char* phyTypeStr[]={
            "DDR54_PHY", // 1
            "LPDDR54_PHY",// 2
            "DDR43_PHY", // 3
            "LPDDR4X_MULTIPHY"// 4
               };

const char* protocolTypeStr[]={
    "DWC_DDR4"  ,     //!<DDR4 SDRAM
    "DWC_DDR5"  ,     //!<DDR5 SDRAM
    "DWC_LPDDR4",     //!<LPDDR4 SDRAM
    "DWC_LPDDR5"      //!<LPDDR5 SDRAM
    "DWC_DDR3"  ,     //!<DDR3 SDRAM
    "DWC_LPDDR3",     //!<LPDDR3 SDRAM
};

/** @brief The register defaults are applied to the C structures.
 * @note The body of this method is automated.
 */                                       
void dwc_cinit_reg_defaults(SubsysHdlr_t *hdlr) {
    SubsysHdlr_t *cfg;
    cfg=hdlr;
#include "dwc_cinit_defaults.h"
}

/** @brief Function called from simulation env to initialize the CINIT structures. 
 * The memory clock must be set prior to this function call
 * To set the operational clock frequencies use the following methods:
 * 
 *  dwc_cinit_get_jedec_clk_speed(g_mctl_cfg);
 *  dwc_cinit_set_operational_clk_period(g_mctl_cfg);
 *  
 * @param hdlr pointer to SubsysHdlr_t
 * @note in simulation mode the SubsysHdlr_t memory is allocated in the UVM env.
 *
 **/
void dwc_cinit_setup(SubsysHdlr_t *hdlr) {
  TRACE();  
  // apply reset values to the registers
  dwc_cinit_reg_defaults(hdlr);
  dwc_cinit_ddr_set_timing(hdlr);
  dwc_cinit_print_initial_msg(hdlr );
}


/** @brief function to set the operational clock period
 * @note dwc_cinit_ddr_set_timing must be call prior to this function.
 * if enable_non_jedec_tck is set then it is assumed that 
 * hdlr->spdData_m.tck_ps[] set been set externally.
 */ 
void dwc_cinit_set_operational_clk_period(SubsysHdlr_t *hdlr) {
  TRACE();
  for(int p=0; p<UMCTL2_FREQUENCY_NUM; p++) {
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);

    if(hdlr->enable_non_jedec_tck) {
      // check that the period as been set by user.
      ASSERT(hdlr->spdData_m.tck_ps[p]!=0);
    } else {

      if(hdlr->spdData_m.tck_ps[p]==0) {
        // get the clock period from JEDEC timing library. In LPDDR, other frequency(tck_ps[1]) will be set in lpddr_sdram_cfg
        hdlr->spdData_m.tck_ps[p] = timing->sg_tck_ps;
      }

#ifdef MEMC_DDR3_OR_4
      if(IS_DDR4) {
        if (DLL_OFF_MODE(0) == 1) {   
          // in DLL off mode the min TCK period is 8ns 
          // JESD79-4A spec Table 103
          hdlr->spdData_m.tck_ps[p]=8000;
        }
      }
#endif
    }
  }

#ifdef DDRCTL_LPDDR
  //Map tck_ps[pstate] to data_rate[pstate]
  dwc_cinit_map_tck_ps_to_data_rate(hdlr);
#endif
}

#ifndef SIM_MODE 
/** @brief */
void break_b4_exit()
{
	uint32_t i;
	i=0;		//just somewhere to place a breakpoint
}
#endif

/** @brief utility function to print an initial debug message. */
void dwc_cinit_print_initial_msg(SubsysHdlr_t *hdlr)
{
  LOG_MESSAGE(hdlr, 0, ("CINIT version %s\n",
               g_cinit_version ));

  LOG_MESSAGE(hdlr, 0, ("Protocol=%d\n",hdlr->spdData_m.sdram_protocol));
  LOG_MESSAGE(hdlr, 0, ("PHY Type=%d\n",hdlr->ddrPhyType_m));
  
  LOG_MESSAGE(hdlr, 0, ("protocol=%d\n", hdlr->spdData_m.sdram_protocol));
  LOG_MESSAGE(hdlr, 0, ("phy type=%d\n", hdlr->ddrPhyType_m));

  LOG_MESSAGE(hdlr, 0, ("Protocol=%s, PHY Type=%s, min TCK=%d\n",
               protocolTypeStr[hdlr->spdData_m.sdram_protocol],
               phyTypeStr[hdlr->ddrPhyType_m-1],
               hdlr->spdData_m.tck_ps[0] ));    
} 

/** @brief method to print debug information to cinit log file .
 */
void dwc_cinit_log_timing(SubsysHdlr_t *hdlr,uint32_t p, uint32_t dch)
{
  TRACE();
    ddrTimingParameters_t* timing = &(hdlr->timingParams_m[p]);
    mctl_pre_cfg* pre_cfg=&(hdlr->memCtrlr_m.pre_cfg);

    dwc_cinit_print("\n########################################\n");
    dwc_cinit_print("JEDEC Timing for FREQ%0d CH%0d\n",p, dch);
	  dwc_cinit_print("tck_ps[%0d]=%0d ps\n",p,hdlr->spdData_m.tck_ps[p] );
#ifdef MEMC_LPDDR4
      if(IS_LPDDR4) {
        dwc_cinit_print("lpddr4_trfcab_ps=%0d\n",timing->lpddr4_trfcab);

      }
      else if(IS_LPDDR5) {
        dwc_cinit_print("wl=%0d\n",pre_cfg->wl[p][dch]);
        dwc_cinit_print("rl=%0d\n",pre_cfg->rl[p][dch]);
        dwc_cinit_print("wr2rd=%0d\n",pre_cfg->wr2rd[p][dch]);
        dwc_cinit_print("wr2rd_s=%0d\n",pre_cfg->wr2rd_s[p][dch]);
        dwc_cinit_print("rd2wr=%0d\n",pre_cfg->rd2wr[p][dch]);
        dwc_cinit_print("rd2wr_s=%0d\n",pre_cfg->rd2wr_s[p][dch]);
        dwc_cinit_print("wra2pre=%0d\n",pre_cfg->wra2pre[p][dch]);
        dwc_cinit_print("rda2pre=%0d\n",pre_cfg->rda2pre[p][dch]);
        dwc_cinit_print("lpddr5_tccd_s_tck=%0d\n",timing->lpddr5_tccd_s_tck);
        dwc_cinit_print("lpddr5_tccd_l_tck=%0d\n",timing->lpddr5_tccd_l_tck);
        dwc_cinit_print("lpddr5_twtr_s_ps=%0d\n",timing->lpddr5_twtr_s_ps );
        dwc_cinit_print("lpddr5_twtr_l_ps=%0d\n",timing->lpddr5_twtr_l_ps );
        dwc_cinit_print("lpddr5_bl_n_min_tck=%0d\n",timing->lpddr5_bl_n_min_tck );
        dwc_cinit_print("lpddr5_bl_n_max_tck=%0d\n",timing->lpddr5_bl_n_max_tck );
        dwc_cinit_print("lpddr5_rl_tck=%0d\n",timing->lpddr5_rl_tck);
        dwc_cinit_print("lpddr5_wl_tck=%0d\n",timing->lpddr5_wl_tck);
        dwc_cinit_print("lpddr5_wckpre_static_tck=%0d\n",timing->lpddr5_wckpre_static_tck );
        dwc_cinit_print("lpddr5_twck_pst_wck=%0d\n",timing->lpddr5_twck_pst_wck );
        dwc_cinit_print("lpddr5_wckenl_rd_tck=%0d\n",timing->lpddr5_wckenl_rd_tck  );
        dwc_cinit_print("lpddr5_wckenl_wr_tck=%0d\n",timing->lpddr5_wckenl_wr_tck  );
        dwc_cinit_print("lpddr5_wckenl_fs_tck=%0d\n",timing->lpddr5_wckenl_fs_tck  );
        dwc_cinit_print("lpddr5_trfcab_ps=%0d\n",timing->lpddr5_trfcab_ps  );
        dwc_cinit_print("lpddr5_trfcpb_ps=%0d\n",timing->lpddr5_trfcpb_ps  );
        dwc_cinit_print("lpddr5_nrbtp_ps=%0d\n",timing->lpddr5_nrbtp_ps  );
        dwc_cinit_print("lpddr5_nrtp=%0d\n",timing->lpddr5_nrtp  );
        dwc_cinit_print("lpddr5_twr_ps=%0d\n",timing->lpddr5_twr_ps );

        dwc_cinit_print("dfi_twck_en_rd=%0d\n",pre_cfg->dfi_twck_en_rd[p][dch]);
        dwc_cinit_print("dfi_twck_en_wr=%0d\n",pre_cfg->dfi_twck_en_wr[p][dch]);
        dwc_cinit_print("dfi_twck_en_fs=%0d\n",pre_cfg->dfi_twck_en_fs[p][dch]);
        dwc_cinit_print("dfi_twck_dis=%0d\n",pre_cfg->dfi_twck_dis[p][dch]);
        dwc_cinit_print("dfi_twck_fast_toggle=%0d\n",pre_cfg->dfi_twck_fast_toggle[p][dch]);
        dwc_cinit_print("dfi_twck_toggle=%0d\n",pre_cfg->dfi_twck_toggle[p][dch]);
        dwc_cinit_print("dfi_twck_toggle_cs=%0d\n",pre_cfg->dfi_twck_toggle_cs[p][dch]);
        dwc_cinit_print("dfi_twck_toggle_post=%0d\n",pre_cfg->dfi_twck_toggle_post[p][dch]);
        dwc_cinit_print("max_wr_sync=%0d\n",pre_cfg->max_wr_sync[p][dch]);
        dwc_cinit_print("max_rd_sync=%0d\n",pre_cfg->max_rd_sync[p][dch]);

#ifdef MEMC_NUM_RANKS_GT_1
        dwc_cinit_print("rd2wr_dr=%0d\n",pre_cfg->rd2wr_dr[p][dch]);
        dwc_cinit_print("rd2wr_dr_odt=%0d\n",pre_cfg->rd2wr_dr_odt[p][dch]);
        dwc_cinit_print("rd2wr_dr_wck_on=%0d\n",pre_cfg->rd2wr_dr_wck_on[p][dch]);
        dwc_cinit_print("rd2wr_dr_wck_on_odt=%0d\n",pre_cfg->rd2wr_dr_wck_on_odt[p][dch]);

        dwc_cinit_print("wr2rd_dr=%0d\n",pre_cfg->wr2rd_dr[p][dch]);
        dwc_cinit_print("wr2rd_dr_odt=%0d\n",pre_cfg->wr2rd_dr_odt[p][dch]);
        dwc_cinit_print("wr2rd_dr_wck_on=%0d\n",pre_cfg->wr2rd_dr_wck_on[p][dch]);
        dwc_cinit_print("wr2rd_dr_wck_on_odt=%0d\n",pre_cfg->wr2rd_dr_wck_on_odt[p][dch]);

        dwc_cinit_print("diff_rank_rd_gap=%0d\n",pre_cfg->diff_rank_rd_gap[p][dch]);
        dwc_cinit_print("diff_rank_rd_gap_odt=%0d\n",pre_cfg->diff_rank_rd_gap_odt[p][dch]);
        dwc_cinit_print("diff_rank_rd_gap_wck_on=%0d\n",pre_cfg->diff_rank_rd_gap_wck_on[p][dch]);
        dwc_cinit_print("diff_rank_rd_gap_wck_on_odt=%0d\n",pre_cfg->diff_rank_rd_gap_wck_on_odt[p][dch]);

        dwc_cinit_print("diff_rank_wr_gap=%0d\n",pre_cfg->diff_rank_wr_gap[p][dch]);
        dwc_cinit_print("diff_rank_wr_gap_odt=%0d\n",pre_cfg->diff_rank_wr_gap_odt[p][dch]);
        dwc_cinit_print("diff_rank_wr_gap_wck_on=%0d\n",pre_cfg->diff_rank_wr_gap_wck_on[p][dch]);
        dwc_cinit_print("diff_rank_wr_gap_wck_on_odt=%0d\n",pre_cfg->diff_rank_wr_gap_wck_on_odt[p][dch]);
#endif // MEMC_NUM_RANKS_GT_1
      }
#endif // MEMC_LPDDR4  
#ifdef MEMC_DDR4
    if(IS_DDR4){

    } else if(IS_DDR5){
      dwc_cinit_print("tras_min=%0d\n",pre_cfg->t_ras_min[p][dch]);
      dwc_cinit_print("tras_max=%0d\n",pre_cfg->t_ras_max[p][dch]);
      dwc_cinit_print("t_faw=%0d\n",pre_cfg->tfaw[p][dch]);
      dwc_cinit_print("t_rc=%0d\n",pre_cfg->t_rc[p][dch]);
      dwc_cinit_print("t_rcd=%0d\n",pre_cfg->t_rcd[p][dch]);
      dwc_cinit_print("t_rrd=%0d\n",pre_cfg->t_rrd[p][dch]);
      dwc_cinit_print("t_rrd_s=%0d\n",timing->trrd_s_tck);
      dwc_cinit_print("write_latency=%0d\n",pre_cfg->cwl_x[p]);
      dwc_cinit_print("read_latency=%0d\n",pre_cfg->cl[p]);
      dwc_cinit_print("t_ccd_w=%0d\n",pre_cfg->t_ccd_w[p][dch]);
      dwc_cinit_print("t_ccd_w_s=%0d\n",timing->ddr5_tccd_s_tck);
      dwc_cinit_print("t_ccd_w2=%0d\n",pre_cfg->t_ccd_w2[p][dch]);
      dwc_cinit_print("t_ccd_r=%0d\n",timing->ddr5_tccd_l_tck);
      dwc_cinit_print("t_ccd_r_s=%0d\n",timing->ddr5_tccd_s_tck);
      dwc_cinit_print("t_rd2wr_l=%0d\n",pre_cfg->rd2wr[p][dch]);
      dwc_cinit_print("t_wr2rd_l=%0d\n",pre_cfg->wr2rd[p][dch]);
      dwc_cinit_print("t_wr2rd_s=%0d\n",pre_cfg->wr2rd_s[p][dch]);
      dwc_cinit_print("t_wr2rd_dpr=%0d\n",pre_cfg->t_wr2rd_dpr[p][dch]);
      dwc_cinit_print("t_rd2wr_dpr=%0d\n",pre_cfg->t_rd2wr_dpr[p][dch]);
      dwc_cinit_print("t_rp=%0d\n",pre_cfg->t_rp[p][dch]);
      dwc_cinit_print("t_ppd=%0d\n",timing->ddr5_tppd_tck);
      dwc_cinit_print("t_pd=%0d\n",pre_cfg->t_pd[p][dch]);
      dwc_cinit_print("t_mr=%0d\n",pre_cfg->t_mr[p][dch]);
      dwc_cinit_print("t_mpsmx=%0d\n",pre_cfg->t_mpsmx[p][dch]);
      dwc_cinit_print("t_mpdpxact=%0d\n",pre_cfg->t_mpdpxact[p][dch]);
      dwc_cinit_print("t_pda_latch=%0d\n",pre_cfg->t_pda_latch[p][dch]);
      dwc_cinit_print("t_pda_delay=%0d\n",pre_cfg->t_pda_delay[p][dch]);
      dwc_cinit_print("t_pda_dqs_delay=%0d\n",pre_cfg->t_pda_dqs_delay[p][dch]);
      dwc_cinit_print("t_pda_s=%0d\n",pre_cfg->t_pda_s[p][dch]);
      dwc_cinit_print("t_pda_h=%0d\n",pre_cfg->t_pda_h[p][dch]);
      dwc_cinit_print("t_cpded=%0d\n",pre_cfg->t_cpded[p][dch]);
      dwc_cinit_print("t_casrx=%0d\n",pre_cfg->t_casrx[p][dch]);
      dwc_cinit_print("t_csh_srexit=%0d\n",pre_cfg->t_csh_srexit[p][dch]);
      dwc_cinit_print("t_csl_srexit=%0d\n",pre_cfg->t_csl_srexit[p][dch]);
      dwc_cinit_print("t_mpc_cs=%0d\n",pre_cfg->t_mpc_cs[p][dch]);
      dwc_cinit_print("t_mpc_setup=%0d\n",pre_cfg->t_mpc_setup[p][dch]);
      dwc_cinit_print("t_mpc_delay=%0d\n",pre_cfg->t_mpc_delay[p][dch]);
      dwc_cinit_print("t_vrefca_cs=%0d\n",pre_cfg->t_vrefca_cs[p][dch]);
      dwc_cinit_print("t_osco=%0d\n",pre_cfg->t_osco_ddr5[p][dch]);
   }
#endif

    dwc_cinit_print("########################################\n");
    dwc_cinit_print("DFI Timings for FREQ%0d CH%0d\n",p,dch);
    dwc_cinit_print("dfi_t_dram_clk_disable=%0d\n",pre_cfg->dfi_t_dram_clk_disable[p][dch]);
    dwc_cinit_print("dfi_t_dram_clk_enable=%0d\n",pre_cfg->dfi_t_dram_clk_enable[p][dch]);
    
    dwc_cinit_print("dfi_tphy_wrlat=%0d\n",pre_cfg->dfi_tphy_wrlat[p][dch] );
    //dwc_cinit_print("=%0d\n",pre_cfg-> );
    dwc_cinit_print("dfi_t_rddata_en=%0d\n",pre_cfg->dfi_t_rddata_en[p][dch] );
    
    dwc_cinit_print("########################################\n");

}
