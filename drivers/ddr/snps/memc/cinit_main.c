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


#include "dwc_cinit.h"
#define DWC_CINIT_USE_ARB_TCK
// This test is to compile CINIT standalone and to generate an
// executable.
//
// NB this test can only be compiled in the workspace
// The flow is setup a configuration in  g_mctl_cfg->spdData_m
// initialize all the registers to reset values
// get and run-time options
// setup the address map
// calculate Jedec timings
// 
SubsysHdlr_t _mctl_cfg, *g_mctl_cfg ;

/**
 * Main function.
 */
int snps_memc_init()
{  
    char *printf_header;
    printf_header = "// [dwc_cinit_main]";
    dwc_cinit_print ("%s Start of main()\n", printf_header);

    //g_mctl_cfg=(SubsysHdlr_t *)malloc(sizeof(SubsysHdlr_t));
    g_mctl_cfg = &(_mctl_cfg);
	
    g_mctl_cfg->ddrPhyType_m=DWC_LPDDR54_PHY;
    g_mctl_cfg->spdData_m.sdram_protocol=DWC_LPDDR4;
    g_mctl_cfg->spdData_m.lpddr4_data_rate=DWC_LPDDR4_1600;
    g_mctl_cfg->spdData_m.sdram_module_type=DWC_NODIMM;
    g_mctl_cfg->spdData_m.num_ranks=1;
    g_mctl_cfg->enable_non_jedec_tck=0;
    g_mctl_cfg->spdData_m.sdram_width_bits=16;
    g_mctl_cfg->spdData_m.sdram_capacity_mbits=4096;

    g_mctl_cfg->spdData_m.module_width_bits=32;
    g_mctl_cfg->logLevel_m=1;
    g_mctl_cfg->is_constraint_assert_set=1;
    g_mctl_cfg->num_pstates=UMCTL2_FREQUENCY_NUM;
    g_mctl_cfg->num_dch=UMCTL2_NUM_DATA_CHANNEL;

    for( int ii=0;ii<=UMCTL2_FREQUENCY_NUM; ii++) {
      g_mctl_cfg->memCtrlr_m.static_cfg.active_ranks=1;
      g_mctl_cfg->memCtrlr_m.static_cfg.pre_cke_x1024[0]=10;
      for(uint32_t dch=0; dch<g_mctl_cfg->num_dch; dch++) {
      g_mctl_cfg->memCtrlr_m.qdyn_cfg.mr4_read_interval[ii][dch]=ii+1;
      g_mctl_cfg->memCtrlr_m.qdyn_cfg.t_xsr[ii][dch]=0xffe;
      g_mctl_cfg->memCtrlr_m.qdyn_cfg.diff_rank_rd_gap[ii][dch]=7;
      g_mctl_cfg->memCtrlr_m.qdyn_cfg.diff_rank_wr_gap[ii][dch]=7;
      g_mctl_cfg->memCtrlr_m.static_cfg.dfi_t_ctrlup_max[ii][dch]=25;
      g_mctl_cfg->memCtrlr_m.static_cfg.dfi_t_ctrlup_min[ii][dch]=0x30;
      g_mctl_cfg->memCtrlr_m.static_cfg.dfi_t_ctrlupd_interval_max_x1024[ii][dch]=0x3;
      g_mctl_cfg->memCtrlr_m.qdyn_cfg.w_max_starve[ii][dch]=0x1;
      }
    }
    for( int ii=0;ii<=UMCTL2_A_NPORTS; ii++) {
      g_mctl_cfg->memCtrlr_m.qdyn_cfg.rqos_map_level1[ii]=0x2;
      g_mctl_cfg->memCtrlr_m.qdyn_cfg.rqos_map_level2[ii]=0x2;
      g_mctl_cfg->memCtrlr_m.qdyn_cfg.rqos_map_region2[ii]=0x2;
    }

    g_mctl_cfg->memCtrlr_m.dyn_cfg.scrub_burst_length_normal=0x4;  
    g_mctl_cfg->memCtrlr_m.dyn_cfg.scrub_burst_length_lp=0x4;  
    g_mctl_cfg->memCtrlr_m.static_cfg.burst_rdwr=0x08;  
    g_mctl_cfg->memCtrlr_m.qdyn_cfg.dqsosc_runtime=0x800;
    g_mctl_cfg->memCtrlr_m.qdyn_cfg.wck2dqo_runtime=0x800;

 /*   g_mctl_cfg->memCtrlr_m.lpddr4_mr[0].mr3.read_dbi=1;
    g_mctl_cfg->memCtrlr_m.lpddr4_mr[0].mr3.write_dbi=1;
    g_mctl_cfg->memCtrlr_m.lpddr4_mr[0].mr13.data_mask=1;
    g_mctl_cfg->memCtrlr_m.lpddr4_mr[0].mr11.dq_odt=6;*/

    // get min tck value for jedec lookup table
    dwc_cinit_get_jedec_clk_speed(g_mctl_cfg);
#ifdef DWC_CINIT_USE_ARB_TCK
	g_mctl_cfg->enable_non_jedec_tck=1;	
	// reduce tck by 100ps
	g_mctl_cfg->spdData_m.tck_ps[0]=g_mctl_cfg->timingParams_m[0].sg_tck_ps-100;
#endif	
	// example setting alternative frequencies
	if(UMCTL2_FREQUENCY_NUM>1) {
		uint32_t tck_ps=(g_mctl_cfg->enable_non_jedec_tck==0) ? g_mctl_cfg->timingParams_m[0].sg_tck_ps :
		 g_mctl_cfg->spdData_m.tck_ps[0];
		// set each frequency to be 10% slower than the previous
		
		for(int ii=1;ii<UMCTL2_FREQUENCY_NUM;ii++) {
		  tck_ps=tck_ps-(tck_ps*0.1);
	          g_mctl_cfg->spdData_m.tck_ps[ii]=tck_ps;
		  printf("setting g_mctl_cfg>spdData_m.tck_ps[%0d] to %0d\n",ii,tck_ps);
		}
	}
    dwc_cinit_set_operational_clk_period(g_mctl_cfg);
    dwc_cinit_setup(g_mctl_cfg);
    dwc_cinit_setup_mmap(g_mctl_cfg);
    dwc_cinit_print("%s test_dwc_ddrctl_cinit_sa completed", printf_header);

	return 0;
}


