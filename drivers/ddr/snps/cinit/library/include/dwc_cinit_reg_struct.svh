// coreBuilder: This is an automated C header file. DO NOT EDIT.
`ifndef __DWC_CINIT_REG_STRUCT__H__
`define __DWC_CINIT_REG_STRUCT__H__
typedef struct  {
   int unsigned ddr4;
   int unsigned lpddr4;
   int unsigned ddr5;
   int unsigned lpddr5;
   int unsigned burst_mode;
   int unsigned burstchop;
   int unsigned en_2t_timing_mode;
   int unsigned data_bus_width;
   int unsigned dll_off_mode;
   int unsigned burst_rdwr;
   int unsigned active_logical_ranks;
   int unsigned active_ranks;
   int unsigned device_config;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR0_struct_t;

`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned rank_tmgreg_sel;
   int unsigned rfc_tmgreg_sel;
   int unsigned alt_addrmap_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_FREQUENCY_NUM_GT_1
typedef struct  {
   int unsigned target_frequency;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR2_struct_t;

`endif //UMCTL2_FREQUENCY_NUM_GT_1
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned geardown_mode;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR3_struct_t;

`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned wck_on;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR4_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned mr_type;
   int unsigned mpr_en;
   int unsigned pda_en;
   int unsigned sw_init_int;
   int unsigned mr_rank;
   int unsigned mr_addr;
   int unsigned mr_cid;
   int unsigned mrr_done_clr;
   int unsigned pba_mode;
   int unsigned mr_wr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MRCTRL0_struct_t;

typedef struct  {
   int unsigned mr_data;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MRCTRL1_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned mr_device_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MRCTRL2_struct_t;

`endif //DDRCTL_DDR
`ifndef MEMC_NUM_RANKS_1_OR_2_OR_4
typedef struct  {
   int unsigned mr_rank_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_MRCTRL3_struct_t;

`endif //MEMC_NUM_RANKS_1_OR_2_OR_4
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derate_enable;
   int unsigned lpddr4_refresh_mode;
   int unsigned derate_mr4_pause_fc;
   int unsigned dis_trefi_x6x8;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct  {
   int unsigned active_derate_byte_rank0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL1_struct_t;

`endif //DDRCTL_DDR_OR_MEMC_LPDDR4
`ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned active_derate_byte_rank1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_DDR_OR_MEMC_LPDDR4
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned active_derate_byte_rank2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned active_derate_byte_rank3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct  {
   int unsigned derate_temp_limit_intr_en;
   int unsigned derate_temp_limit_intr_clr;
   int unsigned derate_temp_limit_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL5_struct_t;

`endif //DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct  {
   int unsigned derate_mr4_tuf_dis;
   int unsigned derate_low_temp_limit;
   int unsigned derate_high_temp_limit;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL6_struct_t;

`ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct  {
   int unsigned dbg_mr4_grp_sel;
   int unsigned dbg_mr4_rank_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATEDBGCTL_struct_t;

`endif //DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct  {
   int unsigned selfref_en;
   int unsigned powerdown_en;
   int unsigned actv_pd_en;
   int unsigned en_dfi_dram_clk_disable;
   int unsigned mpsm_en;
   int unsigned selfref_sw;
   int unsigned stay_in_selfref;
   int unsigned dis_cam_drain_selfref;
   int unsigned lpddr4_sr_allowed;
   int unsigned dsm_en;
   int unsigned srpd_en;
   int unsigned mpsm_pd_en;
   int unsigned mpsm_deep_pd_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PWRCTL_struct_t;

typedef struct  {
   int unsigned hw_lp_en;
   int unsigned hw_lp_exit_idle_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_HWLPCTL_struct_t;

typedef struct  {
   int unsigned refresh_burst;
   int unsigned per_bank_refresh;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_RFSHMOD0_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned same_bank_refresh;
   int unsigned tcr_refab_thr;
   int unsigned fgr_mode;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_RFSHMOD1_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned dis_auto_refresh;
   int unsigned refresh_update_level;
   int unsigned rank_dis_refresh;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_RFSHCTL0_struct_t;

typedef struct  {
   int unsigned dis_mpsmx_zqcl;
   int unsigned zq_resistor_shared;
   int unsigned dis_auto_zq;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ZQCTL0_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned zq_reset;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ZQCTL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned dis_srx_zqcl;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ZQCTL2_struct_t;

`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_runtime;
   int unsigned wck2dqo_runtime;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQSOSCRUNTIME_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dis_dqsosc_srx;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQSOSCCFG0_struct_t;

`endif //LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dis_opt_wrecc_collision_flush;
   int unsigned prefer_write;
   int unsigned pageclose;
   int unsigned rdwr_switch_policy_sel;
   int unsigned opt_wrcam_fill_level;
   int unsigned dis_opt_ntt_by_act;
   int unsigned dis_opt_ntt_by_pre;
   int unsigned autopre_rmw;
   int unsigned lpr_num_entries;
   int unsigned lpddr4_opt_act_timing;
   int unsigned opt_vprw_sch;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED0_struct_t;

`ifdef MEMC_ENH_CAM_PTR
typedef struct  {
   int unsigned delay_switch_write;
   int unsigned visible_window_limit_wr;
   int unsigned visible_window_limit_rd;
   int unsigned page_hit_limit_wr;
   int unsigned page_hit_limit_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED1_struct_t;

`endif //MEMC_ENH_CAM_PTR
`ifdef UMCTL2_DYN_BSM
typedef struct  {
   int unsigned dyn_bsm_mode;
   int unsigned dealloc_bsm_thr;
   int unsigned dealloc_num_bsm_m1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED2_struct_t;

`endif //UMCTL2_DYN_BSM
`ifdef MEMC_ENH_RDWR_SWITCH
typedef struct  {
   int unsigned wrcam_lowthresh;
   int unsigned wrcam_highthresh;
   int unsigned wr_pghit_num_thresh;
   int unsigned rd_pghit_num_thresh;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED3_struct_t;

`endif //MEMC_ENH_RDWR_SWITCH
`ifdef MEMC_ENH_RDWR_SWITCH
typedef struct  {
   int unsigned rd_act_idle_gap;
   int unsigned wr_act_idle_gap;
   int unsigned rd_page_exp_cycles;
   int unsigned wr_page_exp_cycles;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED4_struct_t;

`endif //MEMC_ENH_RDWR_SWITCH
`ifdef MEMC_ENH_RDWR_SWITCH
`ifdef MEMC_INLINE_ECC
typedef struct  {
   int unsigned wrecc_cam_lowthresh;
   int unsigned wrecc_cam_highthresh;
   int unsigned dis_opt_loaded_wrecc_cam_fill_level;
   int unsigned dis_opt_valid_wrecc_cam_fill_level;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED5_struct_t;

`endif //MEMC_INLINE_ECC
`endif //MEMC_ENH_RDWR_SWITCH
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned hwffc_en;
   int unsigned init_fsp;
   int unsigned init_vrcg;
   int unsigned target_vrcg;
   int unsigned cke_power_down_mode;
   int unsigned power_saving_ctrl_word;
   int unsigned ctrl_word_num;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_HWFFCCTL_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
`ifdef UMCTL2_DQ_MAPPING
typedef struct  {
   int unsigned dq_nibble_map_0_3;
   int unsigned dq_nibble_map_4_7;
   int unsigned dq_nibble_map_8_11;
   int unsigned dq_nibble_map_12_15;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP0_struct_t;

`endif //UMCTL2_DQ_MAPPING
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
`ifdef UMCTL2_DQ_MAPPING
`ifdef MEMC_DRAM_DATA_WIDTH_GT_23
typedef struct  {
   int unsigned dq_nibble_map_16_19;
   int unsigned dq_nibble_map_20_23;
   int unsigned dq_nibble_map_24_27;
   int unsigned dq_nibble_map_28_31;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP1_struct_t;

`endif //MEMC_DRAM_DATA_WIDTH_GT_23
`endif //UMCTL2_DQ_MAPPING
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
`ifdef UMCTL2_DQ_MAPPING
`ifdef MEMC_DRAM_DATA_WIDTH_GT_39
typedef struct  {
   int unsigned dq_nibble_map_32_35;
   int unsigned dq_nibble_map_36_39;
   int unsigned dq_nibble_map_40_43;
   int unsigned dq_nibble_map_44_47;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP2_struct_t;

`endif //MEMC_DRAM_DATA_WIDTH_GT_39
`endif //UMCTL2_DQ_MAPPING
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
`ifdef UMCTL2_DQ_MAPPING
`ifdef MEMC_DRAM_DATA_WIDTH_GT_55
typedef struct  {
   int unsigned dq_nibble_map_48_51;
   int unsigned dq_nibble_map_52_55;
   int unsigned dq_nibble_map_56_59;
   int unsigned dq_nibble_map_60_63;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP3_struct_t;

`endif //MEMC_DRAM_DATA_WIDTH_GT_55
`endif //UMCTL2_DQ_MAPPING
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
`ifdef UMCTL2_DQ_MAPPING
`ifdef MEMC_DRAM_DATA_WIDTH_72_OR_MEMC_SIDEBAND_ECC
typedef struct  {
   int unsigned dq_nibble_map_cb_0_3;
   int unsigned dq_nibble_map_cb_4_7;
   int unsigned dq_nibble_map_cb_8_11;
   int unsigned dq_nibble_map_cb_12_15;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP4_struct_t;

`endif //MEMC_DRAM_DATA_WIDTH_72_OR_MEMC_SIDEBAND_ECC
`endif //UMCTL2_DQ_MAPPING
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
`ifdef UMCTL2_DQ_MAPPING
typedef struct  {
   int unsigned dis_dq_rank_swap;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP5_struct_t;

`endif //UMCTL2_DQ_MAPPING
`endif //DDRCTL_DDR
typedef struct  {
   int unsigned dfi_lp_en_pd;
   int unsigned dfi_lp_en_sr;
   int unsigned dfi_lp_en_dsm;
   int unsigned dfi_lp_en_mpsm;
   int unsigned dfi_lp_en_data;
   int unsigned dfi_lp_data_req_en;
   int unsigned dfi_lp_extra_gap_wr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFILPCFG0_struct_t;

typedef struct  {
   int unsigned dfi_phyupd_en;
   int unsigned ctrlupd_pre_srx;
   int unsigned dis_auto_ctrlupd_srx;
   int unsigned dis_auto_ctrlupd;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFIUPD0_struct_t;

`ifdef UMCTL2_DFI_PHYUPD_WAIT_IDLE
typedef struct  {
   int unsigned dfi_phyupd_type0_wait_idle;
   int unsigned dfi_phyupd_type1_wait_idle;
   int unsigned dfi_phyupd_type2_wait_idle;
   int unsigned dfi_phyupd_type3_wait_idle;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFIUPD1_struct_t;

`endif //UMCTL2_DFI_PHYUPD_WAIT_IDLE
typedef struct  {
   int unsigned dfi_init_complete_en;
   int unsigned phy_dbi_mode;
   int unsigned dfi_data_cs_polarity;
   int unsigned share_dfi_dram_clk_disable;
   int unsigned dfi_init_start;
   int unsigned dis_dyn_adr_tri;
   int unsigned lp_optimized_write;
   int unsigned dfi_frequency;
   int unsigned dfi_channel_mode;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFIMISC_struct_t;

typedef struct  {
   int unsigned dfi_phymstr_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFIPHYMSTR_struct_t;

typedef struct  {
   int unsigned dfi0_ctrlmsg_data;
   int unsigned dfi0_ctrlmsg_cmd;
   int unsigned dfi0_ctrlmsg_tout_clr;
   int unsigned dfi0_ctrlmsg_req;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFI0MSGCTL0_struct_t;

`ifdef UMCTL2_INCL_ARB
`ifdef UMCTL2_A_AXI
typedef struct  {
   int unsigned wr_poison_slverr_en;
   int unsigned wr_poison_intr_en;
   int unsigned wr_poison_intr_clr;
   int unsigned rd_poison_slverr_en;
   int unsigned rd_poison_intr_en;
   int unsigned rd_poison_intr_clr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_POISONCFG_struct_t;

`endif //UMCTL2_A_AXI
`endif //UMCTL2_INCL_ARB
`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned ecc_mode;
   int unsigned test_mode;
   int unsigned dis_scrub;
   int unsigned ecc_ap_en;
   int unsigned ecc_region_remap_en;
   int unsigned ecc_region_map;
   int unsigned blk_channel_idle_time_x32;
   int unsigned ecc_ap_err_threshold;
   int unsigned ecc_region_map_other;
   int unsigned ecc_region_map_granu;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCCFG0_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned data_poison_en;
   int unsigned data_poison_bit;
   int unsigned poison_chip_en;
   int unsigned ecc_region_parity_lock;
   int unsigned ecc_region_waste_lock;
   int unsigned blk_channel_active_term;
   int unsigned active_blk_channel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCCFG1_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned ecc_corrected_err_clr;
   int unsigned ecc_uncorrected_err_clr;
   int unsigned ecc_corr_err_cnt_clr;
   int unsigned ecc_uncorr_err_cnt_clr;
   int unsigned ecc_ap_err_intr_clr;
   int unsigned ecc_corrected_err_intr_en;
   int unsigned ecc_uncorrected_err_intr_en;
   int unsigned ecc_ap_err_intr_en;
   int unsigned ecc_corrected_err_intr_force;
   int unsigned ecc_uncorrected_err_intr_force;
   int unsigned ecc_ap_err_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCCTL_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned ecc_poison_col;
   int unsigned ecc_poison_cid;
   int unsigned ecc_poison_rank;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONADDR0_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned ecc_poison_row;
   int unsigned ecc_poison_bank;
   int unsigned ecc_poison_bg;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONADDR1_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned ecc_syndrome_sel;
   int unsigned ecc_err_symbol_sel;
   int unsigned ecc_poison_beats_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ADVECCINDEX_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned ecc_poison_data_31_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONPAT0_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_DRAM_DATA_WIDTH_64
typedef struct  {
   int unsigned ecc_poison_data_63_32;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONPAT1_struct_t;

`endif //MEMC_DRAM_DATA_WIDTH_64
`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned ecc_poison_data_71_64;
   int unsigned ecc_poison_data_79_72;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONPAT2_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef UMCTL2_OCPAR_OR_OCECC_EN_1
typedef struct  {
   int unsigned oc_parity_en;
   int unsigned oc_parity_type;
   int unsigned par_wdata_err_intr_en;
   int unsigned par_wdata_slverr_en;
   int unsigned par_wdata_err_intr_clr;
   int unsigned par_wdata_err_intr_force;
   int unsigned par_rdata_slverr_en;
   int unsigned par_rdata_err_intr_en;
   int unsigned par_rdata_err_intr_clr;
   int unsigned par_rdata_err_intr_force;
   int unsigned par_addr_slverr_en;
   int unsigned par_waddr_err_intr_en;
   int unsigned par_waddr_err_intr_clr;
   int unsigned par_raddr_err_intr_en;
   int unsigned par_raddr_err_intr_clr;
   int unsigned par_waddr_err_intr_force;
   int unsigned par_raddr_err_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCPARCFG0_struct_t;

`endif //UMCTL2_OCPAR_OR_OCECC_EN_1
`ifdef UMCTL2_OCPAR_EN_1
typedef struct  {
   int unsigned par_poison_en;
   int unsigned par_poison_loc_rd_dfi;
   int unsigned par_poison_loc_rd_iecc_type;
   int unsigned par_poison_loc_rd_port;
   int unsigned par_poison_loc_wr_port;
   int unsigned par_poison_byte_num;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCPARCFG1_struct_t;

`endif //UMCTL2_OCPAR_EN_1
`ifdef DDRCTL_OCSAP_EN_1
typedef struct  {
   int unsigned ocsap_par_en;
   int unsigned ocsap_poison_en;
   int unsigned wdataram_addr_poison_loc;
   int unsigned rdataram_addr_poison_loc;
   int unsigned wdataram_addr_poison_ctl;
   int unsigned rdataram_addr_poison_ctl;
   int unsigned rdataram_addr_poison_port;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCSAPCFG0_struct_t;

`endif //DDRCTL_OCSAP_EN_1
`ifdef UMCTL2_OCECC_EN_1
typedef struct  {
   int unsigned ocecc_en;
   int unsigned ocecc_fec_en;
   int unsigned ocecc_uncorrected_err_intr_en;
   int unsigned ocecc_wdata_slverr_en;
   int unsigned ocecc_uncorrected_err_intr_clr;
   int unsigned ocecc_uncorrected_err_intr_force;
   int unsigned ocecc_corrected_err_intr_en;
   int unsigned ocecc_rdata_slverr_en;
   int unsigned ocecc_corrected_err_intr_clr;
   int unsigned ocecc_corrected_err_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCECCCFG0_struct_t;

`endif //UMCTL2_OCECC_EN_1
`ifdef UMCTL2_OCECC_EN_1
typedef struct  {
   int unsigned ocecc_poison_en;
   int unsigned ocecc_poison_egen_mr_rd_0;
   int unsigned ocecc_poison_egen_mr_rd_0_byte_num;
   int unsigned ocecc_poison_egen_xpi_rd_out;
   int unsigned ocecc_poison_port_num;
   int unsigned ocecc_poison_egen_mr_rd_1;
   int unsigned ocecc_poison_egen_mr_rd_1_byte_num;
   int unsigned ocecc_poison_egen_xpi_rd_0;
   int unsigned ocecc_poison_ecc_corr_uncorr;
   int unsigned ocecc_poison_pgen_rd;
   int unsigned ocecc_poison_pgen_mr_wdata;
   int unsigned ocecc_poison_pgen_mr_ecc;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCECCCFG1_struct_t;

`endif //UMCTL2_OCECC_EN_1
`ifdef UMCTL2_OCCAP_EN_1
typedef struct  {
   int unsigned occap_en;
   int unsigned occap_arb_intr_en;
   int unsigned occap_arb_intr_clr;
   int unsigned occap_arb_intr_force;
   int unsigned occap_arb_cmp_poison_seq;
   int unsigned occap_arb_cmp_poison_parallel;
   int unsigned occap_arb_cmp_poison_err_inj;
   int unsigned occap_arb_raq_poison_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCCAPCFG_struct_t;

`endif //UMCTL2_OCCAP_EN_1
`ifdef UMCTL2_OCCAP_EN_1
typedef struct  {
   int unsigned occap_ddrc_data_intr_en;
   int unsigned occap_ddrc_data_intr_clr;
   int unsigned occap_ddrc_data_intr_force;
   int unsigned occap_ddrc_data_poison_seq;
   int unsigned occap_ddrc_data_poison_parallel;
   int unsigned occap_ddrc_data_poison_err_inj;
   int unsigned occap_ddrc_ctrl_intr_en;
   int unsigned occap_ddrc_ctrl_intr_clr;
   int unsigned occap_ddrc_ctrl_intr_force;
   int unsigned occap_ddrc_ctrl_poison_seq;
   int unsigned occap_ddrc_ctrl_poison_parallel;
   int unsigned occap_ddrc_ctrl_poison_err_inj;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCCAPCFG1_struct_t;

`endif //UMCTL2_OCCAP_EN_1
typedef struct  {
   int unsigned dfi_alert_err_int_en;
   int unsigned dfi_alert_err_int_clr;
   int unsigned dfi_alert_err_cnt_clr;
   int unsigned dfi_alert_err_fatl_int_clr;
   int unsigned dfi_alert_err_max_reached_int_clr;
   int unsigned retry_ctrlupd_enable;
   int unsigned retry_ctrlupd_wait;
   int unsigned rd_crc_err_max_reached_int_en;
   int unsigned rd_crc_err_max_reached_int_clr;
   int unsigned rd_crc_err_cnt_clr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CRCPARCTL0_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned parity_enable;
   int unsigned rd_crc_enable;
   int unsigned wr_crc_enable;
   int unsigned crc_inc_dm;
   int unsigned crc_parity_retry_enable;
   int unsigned alert_wait_for_sw;
   int unsigned caparity_disable_before_sr;
   int unsigned retry_add_rd_lat_en;
   int unsigned retry_add_rd_lat;
   int unsigned dfi_t_phy_rdlat;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CRCPARCTL1_struct_t;

`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned dfi_alert_err_max_reached_th;
   int unsigned rd_crc_err_max_reached_th;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CRCPARCTL2_struct_t;

`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY_OR_DDRCTL_CA_PARITY
typedef struct  {
   int unsigned capar_poison_inject_en;
   int unsigned capar_poison_cmdtype;
   int unsigned capar_poison_position;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CAPARPOISONCTL_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY_OR_DDRCTL_CA_PARITY
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned crc_poison_inject_en;
   int unsigned crc_poison_type;
   int unsigned crc_poison_nibble;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CRCPOISONCTL0_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_REGPAR_EN_1
typedef struct  {
   int unsigned reg_par_en;
   int unsigned reg_par_err_intr_en;
   int unsigned reg_par_err_intr_clr;
   int unsigned reg_par_err_intr_force;
   int unsigned reg_par_poison_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_REGPARCFG_struct_t;

`endif //UMCTL2_REGPAR_EN_1
`ifdef MEMC_LINK_ECC
typedef struct  {
   int unsigned wr_link_ecc_enable;
   int unsigned rd_link_ecc_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_LNKECCCTL0_struct_t;

`endif //MEMC_LINK_ECC
`ifdef MEMC_LINK_ECC
typedef struct  {
   int unsigned rd_link_ecc_corr_intr_en;
   int unsigned rd_link_ecc_corr_intr_clr;
   int unsigned rd_link_ecc_corr_cnt_clr;
   int unsigned rd_link_ecc_corr_intr_force;
   int unsigned rd_link_ecc_uncorr_intr_en;
   int unsigned rd_link_ecc_uncorr_intr_clr;
   int unsigned rd_link_ecc_uncorr_cnt_clr;
   int unsigned rd_link_ecc_uncorr_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_LNKECCCTL1_struct_t;

`endif //MEMC_LINK_ECC
`ifdef MEMC_LINK_ECC
typedef struct  {
   int unsigned linkecc_poison_inject_en;
   int unsigned linkecc_poison_type;
   int unsigned linkecc_poison_rw;
   int unsigned linkecc_poison_dmi_sel;
   int unsigned linkecc_poison_byte_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_LNKECCPOISONCTL0_struct_t;

`endif //MEMC_LINK_ECC
`ifdef MEMC_LINK_ECC
typedef struct  {
   int unsigned rd_link_ecc_err_byte_sel;
   int unsigned rd_link_ecc_err_rank_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_LNKECCINDEX_struct_t;

`endif //MEMC_LINK_ECC
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned init_done;
   int unsigned dbg_st_en;
   int unsigned bist_st_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL0_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned pre_sb_enable;
   int unsigned pre_ab_enable;
   int unsigned pre_slot_config;
   int unsigned wr_min_gap;
   int unsigned rd_min_gap;
   int unsigned prank_tmgreg_set_sel;
   int unsigned non_dyn_sched_en;
   int unsigned selfref_wo_ref_pending;
   int unsigned dfi_alert_assertion_mode;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL1_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned active_prank_bitmap;
   int unsigned pads0_rsvd0;
   int unsigned lrank_rd2rd_gap;
   int unsigned lrank_wr2wr_gap;
   int unsigned lrank_rd2wr_gap;
   int unsigned lrank_wr2rd_gap;
   int unsigned pads0_rsvd1;
   int unsigned t_ppd_cnt_en;
   int unsigned pads0_rsvd2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL2_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned bg_bit_mask;
   int unsigned bank_bit_mask;
   int unsigned lrank_bit_mask;
   int unsigned prank_bit_mask;
   int unsigned pads1_rsvd1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned ci_mrr_des1;
   int unsigned ci_mrr_des2;
   int unsigned ci_mrw_des1;
   int unsigned ci_mrw_des2;
   int unsigned ci_mpc_des1;
   int unsigned ci_mpc_des2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL4_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned base_timer_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL5_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned base_timer;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL6_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned glb_blk0_en;
   int unsigned glb_blk1_en;
   int unsigned glb_blk2_en;
   int unsigned glb_blk3_en;
   int unsigned glb_blk4_en;
   int unsigned glb_blk5_en;
   int unsigned glb_blk6_en;
   int unsigned glb_blk7_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL7_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned rank_blk0_en;
   int unsigned rank_blk1_en;
   int unsigned rank_blk2_en;
   int unsigned rank_blk3_en;
   int unsigned rank_blk4_en;
   int unsigned rank_blk5_en;
   int unsigned rank_blk6_en;
   int unsigned rank_blk7_en;
   int unsigned rank_blk8_en;
   int unsigned rank_blk9_en;
   int unsigned rank_blk10_en;
   int unsigned rank_blk11_en;
   int unsigned rank_blk12_en;
   int unsigned rank_blk13_en;
   int unsigned rank_blk14_en;
   int unsigned rank_blk15_en;
   int unsigned rank_blk16_en;
   int unsigned rank_blk17_en;
   int unsigned rank_blk18_en;
   int unsigned rank_blk19_en;
   int unsigned rank_blk20_en;
   int unsigned rank_blk21_en;
   int unsigned rank_blk22_en;
   int unsigned rank_blk23_en;
   int unsigned rank_blk24_en;
   int unsigned rank_blk25_en;
   int unsigned rank_blk26_en;
   int unsigned rank_blk27_en;
   int unsigned rank_blk28_en;
   int unsigned rank_blk29_en;
   int unsigned rank_blk30_en;
   int unsigned rank_blk31_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL8_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned glb_blk0_trig;
   int unsigned glb_blk1_trig;
   int unsigned glb_blk2_trig;
   int unsigned glb_blk3_trig;
   int unsigned glb_blk4_trig;
   int unsigned glb_blk5_trig;
   int unsigned glb_blk6_trig;
   int unsigned glb_blk7_trig;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL9_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned rank_blk0_trig;
   int unsigned rank_blk1_trig;
   int unsigned rank_blk2_trig;
   int unsigned rank_blk3_trig;
   int unsigned rank_blk4_trig;
   int unsigned rank_blk5_trig;
   int unsigned rank_blk6_trig;
   int unsigned rank_blk7_trig;
   int unsigned rank_blk8_trig;
   int unsigned rank_blk9_trig;
   int unsigned rank_blk10_trig;
   int unsigned rank_blk11_trig;
   int unsigned rank_blk12_trig;
   int unsigned rank_blk13_trig;
   int unsigned rank_blk14_trig;
   int unsigned rank_blk15_trig;
   int unsigned rank_blk16_trig;
   int unsigned rank_blk17_trig;
   int unsigned rank_blk18_trig;
   int unsigned rank_blk19_trig;
   int unsigned rank_blk20_trig;
   int unsigned rank_blk21_trig;
   int unsigned rank_blk22_trig;
   int unsigned rank_blk23_trig;
   int unsigned rank_blk24_trig;
   int unsigned rank_blk25_trig;
   int unsigned rank_blk26_trig;
   int unsigned rank_blk27_trig;
   int unsigned rank_blk28_trig;
   int unsigned rank_blk29_trig;
   int unsigned rank_blk30_trig;
   int unsigned rank_blk31_trig;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL10_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned powerdown_entry_ba_0;
   int unsigned powerdown_entry_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL11_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned powerdown_exit_ba_0;
   int unsigned powerdown_exit_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL12_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_entry_ba_1;
   int unsigned powerdown_entry_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL13_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_exit_ba_1;
   int unsigned powerdown_exit_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL14_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned powerdown_entry_ba_2;
   int unsigned powerdown_entry_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL15_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned powerdown_exit_ba_2;
   int unsigned powerdown_exit_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL16_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned powerdown_entry_ba_3;
   int unsigned powerdown_entry_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL17_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned powerdown_exit_ba_3;
   int unsigned powerdown_exit_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL18_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned selfref_entry1_ba_0;
   int unsigned selfref_entry1_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned selfref_entry2_ba_0;
   int unsigned selfref_entry2_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned selfref_exit1_ba_0;
   int unsigned selfref_exit1_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL22_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned selfref_exit2_ba_0;
   int unsigned selfref_exit2_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL23_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned selfref_entry1_ba_1;
   int unsigned selfref_entry1_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL24_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned selfref_entry2_ba_1;
   int unsigned selfref_entry2_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL25_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned selfref_exit1_ba_1;
   int unsigned selfref_exit1_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL26_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned selfref_exit2_ba_1;
   int unsigned selfref_exit2_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL27_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_entry1_ba_2;
   int unsigned selfref_entry1_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL28_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_entry2_ba_2;
   int unsigned selfref_entry2_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL29_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_exit1_ba_2;
   int unsigned selfref_exit1_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL30_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_exit2_ba_2;
   int unsigned selfref_exit2_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL31_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_entry1_ba_3;
   int unsigned selfref_entry1_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL32_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_entry2_ba_3;
   int unsigned selfref_entry2_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL33_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_exit1_ba_3;
   int unsigned selfref_exit1_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL34_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_exit2_ba_3;
   int unsigned selfref_exit2_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL35_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP_EN
typedef struct  {
   int unsigned powerdown_idle_ctrl_0;
   int unsigned powerdown_idle_ctrl_1;
   int unsigned selfref_idle_ctrl_0;
   int unsigned selfref_idle_ctrl_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL36_struct_t;

`endif //DDRCTL_PERRANK_LP_EN
`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned dch_sync_mode;
   int unsigned dch_stagger_sel;
   int unsigned t_dch_stagger_delay;
   int unsigned t_selfref_exit_stagger;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL37_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_BWL_EN
typedef struct  {
   int unsigned bwl_win_len;
   int unsigned bwl_en_len;
   int unsigned bwl_ctrl;
   int unsigned bwl_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL38_struct_t;

`endif //DDRCTL_DDR_BWL_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned cmd_type;
   int unsigned multi_cyc_cs_en;
   int unsigned cmd_timer_x32;
   int unsigned mrr_grp_sel;
   int unsigned dram_dq_width;
   int unsigned ctrlupd_retry_thr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CMDCFG_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned cmd_ctrl;
   int unsigned cmd_code;
   int unsigned cmd_seq_last;
   int unsigned cmd_start;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CMDCTL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned cmd_ext_ctrl;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CMDEXTCTL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned swcmd_err_intr_en;
   int unsigned swcmd_err_intr_clr;
   int unsigned swcmd_err_intr_force;
   int unsigned ducmd_err_intr_en;
   int unsigned ducmd_err_intr_clr;
   int unsigned ducmd_err_intr_force;
   int unsigned lccmd_err_intr_en;
   int unsigned lccmd_err_intr_clr;
   int unsigned lccmd_err_intr_force;
   int unsigned ctrlupd_err_intr_en;
   int unsigned ctrlupd_err_intr_clr;
   int unsigned ctrlupd_err_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASINTCTL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned du_cfgbuf_wdata;
   int unsigned du_cfgbuf_addr;
   int unsigned du_cfgbuf_select;
   int unsigned du_cfgbuf_op_mode;
   int unsigned du_cfgbuf_rw_type;
   int unsigned du_cfgbuf_rw_start;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DU_CFGBUF_CTRL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned du_cmdbuf_wdata;
   int unsigned du_cmdbuf_addr;
   int unsigned du_cmdbuf_select;
   int unsigned du_cmdbuf_op_mode;
   int unsigned du_cmdbuf_rw_type;
   int unsigned du_cmdbuf_rw_start;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DU_CMDBUF_CTRL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned lp_cmdbuf_wdata;
   int unsigned lp_cmdbuf_addr;
   int unsigned lp_cmdbuf_op_mode;
   int unsigned lp_cmdbuf_rw_type;
   int unsigned lp_cmdbuf_rw_start;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_LP_CMDBUF_CTRL_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dis_wc;
   int unsigned dis_rd_bypass;
   int unsigned dis_act_bypass;
   int unsigned dis_collision_page_opt;
   int unsigned dis_max_rank_rd_opt;
   int unsigned dis_max_rank_wr_opt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OPCTRL0_struct_t;

typedef struct  {
   int unsigned dis_dq;
   int unsigned dis_hif;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OPCTRL1_struct_t;

typedef struct  {
   int unsigned rank0_refresh;
   int unsigned rank1_refresh;
   int unsigned rank2_refresh;
   int unsigned rank3_refresh;
   int unsigned rank4_refresh;
   int unsigned rank5_refresh;
   int unsigned rank6_refresh;
   int unsigned rank7_refresh;
   int unsigned rank8_refresh;
   int unsigned rank9_refresh;
   int unsigned rank10_refresh;
   int unsigned rank11_refresh;
   int unsigned rank12_refresh;
   int unsigned rank13_refresh;
   int unsigned rank14_refresh;
   int unsigned rank15_refresh;
   int unsigned zq_calib_short;
   int unsigned ctrlupd;
   int unsigned hw_ref_zq_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_OPCTRLCMD_struct_t;

typedef struct  {
   int unsigned sw_done;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_SWCTL_struct_t;

typedef struct  {
   int unsigned dimm_stagger_cs_en;
   int unsigned dimm_addr_mirr_en;
   int unsigned dimm_output_inv_en;
   int unsigned mrs_a17_en;
   int unsigned mrs_bg1_en;
   int unsigned dimm_dis_bg_mirroring;
   int unsigned lrdimm_bcom_cmd_prot;
   int unsigned rcd_num;
   int unsigned dimm_type;
   int unsigned rcd_weak_drive;
   int unsigned rcd_a_output_disabled;
   int unsigned rcd_b_output_disabled;
   int unsigned dimm_selfref_clock_stop_mode;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DIMMCTL_struct_t;

`ifdef DDRCTL_PROG_CHCTL
typedef struct  {
   int unsigned dual_channel_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_CHCTL_struct_t;

`endif //DDRCTL_PROG_CHCTL
`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned max_rank_rd;
   int unsigned max_rank_wr;
   int unsigned max_logical_rank_rd;
   int unsigned max_logical_rank_wr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_RANKCTL_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned dm_en;
   int unsigned wr_dbi_en;
   int unsigned rd_dbi_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DBICTL_struct_t;

typedef struct  {
   int unsigned rank0_wr_odt;
   int unsigned rank0_rd_odt;
   int unsigned rank1_wr_odt;
   int unsigned rank1_rd_odt;
   int unsigned rank2_wr_odt;
   int unsigned rank2_rd_odt;
   int unsigned rank3_wr_odt;
   int unsigned rank3_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAP_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned rd_data_copy_en;
   int unsigned wr_data_copy_en;
   int unsigned wr_data_x_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DATACTL0_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned sw_static_unlock;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_SWCTLSTATIC_struct_t;

`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k0_wr_odt;
   int unsigned k0_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK0_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k1_wr_odt;
   int unsigned k1_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK1_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k2_wr_odt;
   int unsigned k2_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK2_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k3_wr_odt;
   int unsigned k3_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK3_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k4_wr_odt;
   int unsigned k4_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK4_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k5_wr_odt;
   int unsigned k5_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK5_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k6_wr_odt;
   int unsigned k6_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK6_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k7_wr_odt;
   int unsigned k7_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK7_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k8_wr_odt;
   int unsigned k8_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK8_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k9_wr_odt;
   int unsigned k9_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK9_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k10_wr_odt;
   int unsigned k10_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK10_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k11_wr_odt;
   int unsigned k11_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK11_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k12_wr_odt;
   int unsigned k12_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK12_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k13_wr_odt;
   int unsigned k13_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK13_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k14_wr_odt;
   int unsigned k14_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK14_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k15_wr_odt;
   int unsigned k15_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK15_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
typedef struct  {
   int unsigned pre_cke_x1024;
   int unsigned post_cke_x1024;
   int unsigned skip_dram_init;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_INITTMG0_struct_t;

typedef struct  {
   int unsigned dram_rstn_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_INITTMG1_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned dev_zqinit_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_INITTMG2_struct_t;

`endif //DDRCTL_DDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dbg_bsm_sel_ctrl;
   int unsigned dbg_lrsm_sel_ctrl;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH0_DS_DBG_CTRL0_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned geardown_mode;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_MSTR3_struct_t;

`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned wck_on;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_MSTR4_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned mr_type;
   int unsigned mpr_en;
   int unsigned pda_en;
   int unsigned sw_init_int;
   int unsigned mr_rank;
   int unsigned mr_addr;
   int unsigned mr_cid;
   int unsigned mrr_done_clr;
   int unsigned pba_mode;
   int unsigned mr_wr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_MRCTRL0_struct_t;

typedef struct  {
   int unsigned mr_data;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_MRCTRL1_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned mr_device_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_MRCTRL2_struct_t;

`endif //DDRCTL_DDR
`ifndef MEMC_NUM_RANKS_1_OR_2_OR_4
typedef struct  {
   int unsigned mr_rank_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_MRCTRL3_struct_t;

`endif //MEMC_NUM_RANKS_1_OR_2_OR_4
`ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct  {
   int unsigned derate_temp_limit_intr_en;
   int unsigned derate_temp_limit_intr_clr;
   int unsigned derate_temp_limit_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_DERATECTL5_struct_t;

`endif //DDRCTL_DDR_OR_MEMC_LPDDR4
`ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct  {
   int unsigned dbg_mr4_grp_sel;
   int unsigned dbg_mr4_rank_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_DERATEDBGCTL_struct_t;

`endif //DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct  {
   int unsigned selfref_en;
   int unsigned powerdown_en;
   int unsigned actv_pd_en;
   int unsigned en_dfi_dram_clk_disable;
   int unsigned mpsm_en;
   int unsigned selfref_sw;
   int unsigned stay_in_selfref;
   int unsigned dis_cam_drain_selfref;
   int unsigned lpddr4_sr_allowed;
   int unsigned dsm_en;
   int unsigned srpd_en;
   int unsigned mpsm_pd_en;
   int unsigned mpsm_deep_pd_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PWRCTL_struct_t;

typedef struct  {
   int unsigned hw_lp_en;
   int unsigned hw_lp_exit_idle_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_HWLPCTL_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned zq_reset;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ZQCTL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi0_ctrlmsg_data;
   int unsigned dfi0_ctrlmsg_cmd;
   int unsigned dfi0_ctrlmsg_tout_clr;
   int unsigned dfi0_ctrlmsg_req;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_DFI0MSGCTL0_struct_t;

`ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct  {
   int unsigned ecc_corrected_err_clr;
   int unsigned ecc_uncorrected_err_clr;
   int unsigned ecc_corr_err_cnt_clr;
   int unsigned ecc_uncorr_err_cnt_clr;
   int unsigned ecc_ap_err_intr_clr;
   int unsigned ecc_corrected_err_intr_en;
   int unsigned ecc_uncorrected_err_intr_en;
   int unsigned ecc_ap_err_intr_en;
   int unsigned ecc_corrected_err_intr_force;
   int unsigned ecc_uncorrected_err_intr_force;
   int unsigned ecc_ap_err_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ECCCTL_struct_t;

`endif //MEMC_ECC_SUPPORT_GT_0
`ifdef UMCTL2_OCPAR_OR_OCECC_EN_1
typedef struct  {
   int unsigned oc_parity_en;
   int unsigned oc_parity_type;
   int unsigned par_wdata_err_intr_en;
   int unsigned par_wdata_slverr_en;
   int unsigned par_wdata_err_intr_clr;
   int unsigned par_wdata_err_intr_force;
   int unsigned par_rdata_slverr_en;
   int unsigned par_rdata_err_intr_en;
   int unsigned par_rdata_err_intr_clr;
   int unsigned par_rdata_err_intr_force;
   int unsigned par_addr_slverr_en;
   int unsigned par_waddr_err_intr_en;
   int unsigned par_waddr_err_intr_clr;
   int unsigned par_raddr_err_intr_en;
   int unsigned par_raddr_err_intr_clr;
   int unsigned par_waddr_err_intr_force;
   int unsigned par_raddr_err_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_OCPARCFG0_struct_t;

`endif //UMCTL2_OCPAR_OR_OCECC_EN_1
`ifdef UMCTL2_OCCAP_EN_1
typedef struct  {
   int unsigned occap_ddrc_data_intr_en;
   int unsigned occap_ddrc_data_intr_clr;
   int unsigned occap_ddrc_data_intr_force;
   int unsigned occap_ddrc_data_poison_seq;
   int unsigned occap_ddrc_data_poison_parallel;
   int unsigned occap_ddrc_data_poison_err_inj;
   int unsigned occap_ddrc_ctrl_intr_en;
   int unsigned occap_ddrc_ctrl_intr_clr;
   int unsigned occap_ddrc_ctrl_intr_force;
   int unsigned occap_ddrc_ctrl_poison_seq;
   int unsigned occap_ddrc_ctrl_poison_parallel;
   int unsigned occap_ddrc_ctrl_poison_err_inj;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_OCCAPCFG1_struct_t;

`endif //UMCTL2_OCCAP_EN_1
typedef struct  {
   int unsigned dfi_alert_err_int_en;
   int unsigned dfi_alert_err_int_clr;
   int unsigned dfi_alert_err_cnt_clr;
   int unsigned dfi_alert_err_fatl_int_clr;
   int unsigned dfi_alert_err_max_reached_int_clr;
   int unsigned retry_ctrlupd_enable;
   int unsigned retry_ctrlupd_wait;
   int unsigned rd_crc_err_max_reached_int_en;
   int unsigned rd_crc_err_max_reached_int_clr;
   int unsigned rd_crc_err_cnt_clr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_CRCPARCTL0_struct_t;

`ifdef DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY_OR_DDRCTL_CA_PARITY
typedef struct  {
   int unsigned capar_poison_inject_en;
   int unsigned capar_poison_cmdtype;
   int unsigned capar_poison_position;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_CAPARPOISONCTL_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY_OR_DDRCTL_CA_PARITY
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned crc_poison_inject_en;
   int unsigned crc_poison_type;
   int unsigned crc_poison_nibble;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_CRCPOISONCTL0_struct_t;

`endif //DDRCTL_DDR
`ifdef MEMC_LINK_ECC
typedef struct  {
   int unsigned wr_link_ecc_enable;
   int unsigned rd_link_ecc_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_LNKECCCTL0_struct_t;

`endif //MEMC_LINK_ECC
`ifdef MEMC_LINK_ECC
typedef struct  {
   int unsigned rd_link_ecc_corr_intr_en;
   int unsigned rd_link_ecc_corr_intr_clr;
   int unsigned rd_link_ecc_corr_cnt_clr;
   int unsigned rd_link_ecc_corr_intr_force;
   int unsigned rd_link_ecc_uncorr_intr_en;
   int unsigned rd_link_ecc_uncorr_intr_clr;
   int unsigned rd_link_ecc_uncorr_cnt_clr;
   int unsigned rd_link_ecc_uncorr_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_LNKECCCTL1_struct_t;

`endif //MEMC_LINK_ECC
`ifdef MEMC_LINK_ECC
typedef struct  {
   int unsigned linkecc_poison_inject_en;
   int unsigned linkecc_poison_type;
   int unsigned linkecc_poison_rw;
   int unsigned linkecc_poison_dmi_sel;
   int unsigned linkecc_poison_byte_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_LNKECCPOISONCTL0_struct_t;

`endif //MEMC_LINK_ECC
`ifdef MEMC_LINK_ECC
typedef struct  {
   int unsigned rd_link_ecc_err_byte_sel;
   int unsigned rd_link_ecc_err_rank_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_LNKECCINDEX_struct_t;

`endif //MEMC_LINK_ECC
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned init_done;
   int unsigned dbg_st_en;
   int unsigned bist_st_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL0_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned pre_sb_enable;
   int unsigned pre_ab_enable;
   int unsigned pre_slot_config;
   int unsigned wr_min_gap;
   int unsigned rd_min_gap;
   int unsigned prank_tmgreg_set_sel;
   int unsigned non_dyn_sched_en;
   int unsigned selfref_wo_ref_pending;
   int unsigned dfi_alert_assertion_mode;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL1_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned active_prank_bitmap;
   int unsigned pads0_rsvd0;
   int unsigned lrank_rd2rd_gap;
   int unsigned lrank_wr2wr_gap;
   int unsigned lrank_rd2wr_gap;
   int unsigned lrank_wr2rd_gap;
   int unsigned pads0_rsvd1;
   int unsigned t_ppd_cnt_en;
   int unsigned pads0_rsvd2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL2_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned bg_bit_mask;
   int unsigned bank_bit_mask;
   int unsigned lrank_bit_mask;
   int unsigned prank_bit_mask;
   int unsigned pads1_rsvd1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned ci_mrr_des1;
   int unsigned ci_mrr_des2;
   int unsigned ci_mrw_des1;
   int unsigned ci_mrw_des2;
   int unsigned ci_mpc_des1;
   int unsigned ci_mpc_des2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL4_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned base_timer_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL5_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned base_timer;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL6_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned glb_blk0_en;
   int unsigned glb_blk1_en;
   int unsigned glb_blk2_en;
   int unsigned glb_blk3_en;
   int unsigned glb_blk4_en;
   int unsigned glb_blk5_en;
   int unsigned glb_blk6_en;
   int unsigned glb_blk7_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL7_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned rank_blk0_en;
   int unsigned rank_blk1_en;
   int unsigned rank_blk2_en;
   int unsigned rank_blk3_en;
   int unsigned rank_blk4_en;
   int unsigned rank_blk5_en;
   int unsigned rank_blk6_en;
   int unsigned rank_blk7_en;
   int unsigned rank_blk8_en;
   int unsigned rank_blk9_en;
   int unsigned rank_blk10_en;
   int unsigned rank_blk11_en;
   int unsigned rank_blk12_en;
   int unsigned rank_blk13_en;
   int unsigned rank_blk14_en;
   int unsigned rank_blk15_en;
   int unsigned rank_blk16_en;
   int unsigned rank_blk17_en;
   int unsigned rank_blk18_en;
   int unsigned rank_blk19_en;
   int unsigned rank_blk20_en;
   int unsigned rank_blk21_en;
   int unsigned rank_blk22_en;
   int unsigned rank_blk23_en;
   int unsigned rank_blk24_en;
   int unsigned rank_blk25_en;
   int unsigned rank_blk26_en;
   int unsigned rank_blk27_en;
   int unsigned rank_blk28_en;
   int unsigned rank_blk29_en;
   int unsigned rank_blk30_en;
   int unsigned rank_blk31_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL8_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned glb_blk0_trig;
   int unsigned glb_blk1_trig;
   int unsigned glb_blk2_trig;
   int unsigned glb_blk3_trig;
   int unsigned glb_blk4_trig;
   int unsigned glb_blk5_trig;
   int unsigned glb_blk6_trig;
   int unsigned glb_blk7_trig;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL9_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned rank_blk0_trig;
   int unsigned rank_blk1_trig;
   int unsigned rank_blk2_trig;
   int unsigned rank_blk3_trig;
   int unsigned rank_blk4_trig;
   int unsigned rank_blk5_trig;
   int unsigned rank_blk6_trig;
   int unsigned rank_blk7_trig;
   int unsigned rank_blk8_trig;
   int unsigned rank_blk9_trig;
   int unsigned rank_blk10_trig;
   int unsigned rank_blk11_trig;
   int unsigned rank_blk12_trig;
   int unsigned rank_blk13_trig;
   int unsigned rank_blk14_trig;
   int unsigned rank_blk15_trig;
   int unsigned rank_blk16_trig;
   int unsigned rank_blk17_trig;
   int unsigned rank_blk18_trig;
   int unsigned rank_blk19_trig;
   int unsigned rank_blk20_trig;
   int unsigned rank_blk21_trig;
   int unsigned rank_blk22_trig;
   int unsigned rank_blk23_trig;
   int unsigned rank_blk24_trig;
   int unsigned rank_blk25_trig;
   int unsigned rank_blk26_trig;
   int unsigned rank_blk27_trig;
   int unsigned rank_blk28_trig;
   int unsigned rank_blk29_trig;
   int unsigned rank_blk30_trig;
   int unsigned rank_blk31_trig;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL10_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned powerdown_entry_ba_0;
   int unsigned powerdown_entry_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL11_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned powerdown_exit_ba_0;
   int unsigned powerdown_exit_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL12_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_entry_ba_1;
   int unsigned powerdown_entry_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL13_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_exit_ba_1;
   int unsigned powerdown_exit_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL14_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned powerdown_entry_ba_2;
   int unsigned powerdown_entry_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL15_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned powerdown_exit_ba_2;
   int unsigned powerdown_exit_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL16_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned powerdown_entry_ba_3;
   int unsigned powerdown_entry_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL17_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned powerdown_exit_ba_3;
   int unsigned powerdown_exit_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL18_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned selfref_entry1_ba_0;
   int unsigned selfref_entry1_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned selfref_entry2_ba_0;
   int unsigned selfref_entry2_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned selfref_exit1_ba_0;
   int unsigned selfref_exit1_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL22_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned selfref_exit2_ba_0;
   int unsigned selfref_exit2_size_0;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL23_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned selfref_entry1_ba_1;
   int unsigned selfref_entry1_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL24_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned selfref_entry2_ba_1;
   int unsigned selfref_entry2_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL25_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned selfref_exit1_ba_1;
   int unsigned selfref_exit1_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL26_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned selfref_exit2_ba_1;
   int unsigned selfref_exit2_size_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL27_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_entry1_ba_2;
   int unsigned selfref_entry1_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL28_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_entry2_ba_2;
   int unsigned selfref_entry2_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL29_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_exit1_ba_2;
   int unsigned selfref_exit1_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL30_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_exit2_ba_2;
   int unsigned selfref_exit2_size_2;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL31_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_entry1_ba_3;
   int unsigned selfref_entry1_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL32_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_entry2_ba_3;
   int unsigned selfref_entry2_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL33_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_exit1_ba_3;
   int unsigned selfref_exit1_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL34_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned selfref_exit2_ba_3;
   int unsigned selfref_exit2_size_3;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL35_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //DDRCTL_PERRANK_LP
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_PERRANK_LP_EN
typedef struct  {
   int unsigned powerdown_idle_ctrl_0;
   int unsigned powerdown_idle_ctrl_1;
   int unsigned selfref_idle_ctrl_0;
   int unsigned selfref_idle_ctrl_1;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL36_struct_t;

`endif //DDRCTL_PERRANK_LP_EN
`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned dch_sync_mode;
   int unsigned dch_stagger_sel;
   int unsigned t_dch_stagger_delay;
   int unsigned t_selfref_exit_stagger;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL37_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_BWL_EN
typedef struct  {
   int unsigned bwl_win_len;
   int unsigned bwl_en_len;
   int unsigned bwl_ctrl;
   int unsigned bwl_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL38_struct_t;

`endif //DDRCTL_DDR_BWL_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned cmd_type;
   int unsigned multi_cyc_cs_en;
   int unsigned cmd_timer_x32;
   int unsigned mrr_grp_sel;
   int unsigned dram_dq_width;
   int unsigned ctrlupd_retry_thr;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_CMDCFG_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned cmd_ctrl;
   int unsigned cmd_code;
   int unsigned cmd_seq_last;
   int unsigned cmd_start;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_CMDCTL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned cmd_ext_ctrl;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_CMDEXTCTL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned swcmd_err_intr_en;
   int unsigned swcmd_err_intr_clr;
   int unsigned swcmd_err_intr_force;
   int unsigned ducmd_err_intr_en;
   int unsigned ducmd_err_intr_clr;
   int unsigned ducmd_err_intr_force;
   int unsigned lccmd_err_intr_en;
   int unsigned lccmd_err_intr_clr;
   int unsigned lccmd_err_intr_force;
   int unsigned ctrlupd_err_intr_en;
   int unsigned ctrlupd_err_intr_clr;
   int unsigned ctrlupd_err_intr_force;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASINTCTL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned du_cfgbuf_wdata;
   int unsigned du_cfgbuf_addr;
   int unsigned du_cfgbuf_select;
   int unsigned du_cfgbuf_op_mode;
   int unsigned du_cfgbuf_rw_type;
   int unsigned du_cfgbuf_rw_start;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_DU_CFGBUF_CTRL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned du_cmdbuf_wdata;
   int unsigned du_cmdbuf_addr;
   int unsigned du_cmdbuf_select;
   int unsigned du_cmdbuf_op_mode;
   int unsigned du_cmdbuf_rw_type;
   int unsigned du_cmdbuf_rw_start;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_DU_CMDBUF_CTRL_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned lp_cmdbuf_wdata;
   int unsigned lp_cmdbuf_addr;
   int unsigned lp_cmdbuf_op_mode;
   int unsigned lp_cmdbuf_rw_type;
   int unsigned lp_cmdbuf_rw_start;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_LP_CMDBUF_CTRL_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dis_dq;
   int unsigned dis_hif;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_OPCTRL1_struct_t;

typedef struct  {
   int unsigned rank0_refresh;
   int unsigned rank1_refresh;
   int unsigned rank2_refresh;
   int unsigned rank3_refresh;
   int unsigned rank4_refresh;
   int unsigned rank5_refresh;
   int unsigned rank6_refresh;
   int unsigned rank7_refresh;
   int unsigned rank8_refresh;
   int unsigned rank9_refresh;
   int unsigned rank10_refresh;
   int unsigned rank11_refresh;
   int unsigned rank12_refresh;
   int unsigned rank13_refresh;
   int unsigned rank14_refresh;
   int unsigned rank15_refresh;
   int unsigned zq_calib_short;
   int unsigned ctrlupd;
   int unsigned hw_ref_zq_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_OPCTRLCMD_struct_t;

typedef struct  {
   int unsigned dm_en;
   int unsigned wr_dbi_en;
   int unsigned rd_dbi_en;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_DBICTL_struct_t;

typedef struct  {
   int unsigned rank0_wr_odt;
   int unsigned rank0_rd_odt;
   int unsigned rank1_wr_odt;
   int unsigned rank1_rd_odt;
   int unsigned rank2_wr_odt;
   int unsigned rank2_rd_odt;
   int unsigned rank3_wr_odt;
   int unsigned rank3_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAP_struct_t;

`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k0_wr_odt;
   int unsigned k0_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK0_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k1_wr_odt;
   int unsigned k1_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK1_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k2_wr_odt;
   int unsigned k2_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK2_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k3_wr_odt;
   int unsigned k3_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK3_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k4_wr_odt;
   int unsigned k4_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK4_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k5_wr_odt;
   int unsigned k5_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK5_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k6_wr_odt;
   int unsigned k6_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK6_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_4
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k7_wr_odt;
   int unsigned k7_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK7_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_4
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k8_wr_odt;
   int unsigned k8_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK8_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k9_wr_odt;
   int unsigned k9_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK9_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k10_wr_odt;
   int unsigned k10_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK10_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k11_wr_odt;
   int unsigned k11_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK11_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k12_wr_odt;
   int unsigned k12_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK12_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k13_wr_odt;
   int unsigned k13_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK13_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k14_wr_odt;
   int unsigned k14_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK14_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
`ifdef MEMC_NUM_RANKS_GT_8
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned k15_wr_odt;
   int unsigned k15_rd_odt;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK15_struct_t;

`endif //DDRCTL_DDR
`endif //MEMC_NUM_RANKS_GT_8
typedef struct  {
   int unsigned pre_cke_x1024;
   int unsigned post_cke_x1024;
   int unsigned skip_dram_init;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_INITTMG0_struct_t;

typedef struct  {
   int unsigned dram_rstn_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_INITTMG1_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned dev_zqinit_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_INITTMG2_struct_t;

`endif //DDRCTL_DDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dbg_bsm_sel_ctrl;
   int unsigned dbg_lrsm_sel_ctrl;
  int unsigned value; // full 32-bit register value.
  } REGB_DDRC_CH1_DS_DBG_CTRL0_struct_t;

`endif //MEMC_DDR5
`ifdef UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
typedef struct  {
   int unsigned addrmap_dch_bit0;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP0_struct_t;

`endif //UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned addrmap_cs_bit0;
   int unsigned addrmap_cs_bit1;
   int unsigned addrmap_cs_bit2;
   int unsigned addrmap_cs_bit3;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef UMCTL2_CID_WIDTH_GT_0
typedef struct  {
   int unsigned addrmap_cid_b0;
   int unsigned addrmap_cid_b1;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP2_struct_t;

`endif //UMCTL2_CID_WIDTH_GT_0
typedef struct  {
   int unsigned addrmap_bank_b0;
   int unsigned addrmap_bank_b1;
   int unsigned addrmap_bank_b2;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP3_struct_t;

typedef struct  {
   int unsigned addrmap_bg_b0;
   int unsigned addrmap_bg_b1;
   int unsigned addrmap_bg_b2;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP4_struct_t;

typedef struct  {
   int unsigned addrmap_col_b7;
   int unsigned addrmap_col_b8;
   int unsigned addrmap_col_b9;
   int unsigned addrmap_col_b10;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP5_struct_t;

typedef struct  {
   int unsigned addrmap_col_b3;
   int unsigned addrmap_col_b4;
   int unsigned addrmap_col_b5;
   int unsigned addrmap_col_b6;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP6_struct_t;

typedef struct  {
   int unsigned addrmap_row_b14;
   int unsigned addrmap_row_b15;
   int unsigned addrmap_row_b16;
   int unsigned addrmap_row_b17;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP7_struct_t;

typedef struct  {
   int unsigned addrmap_row_b10;
   int unsigned addrmap_row_b11;
   int unsigned addrmap_row_b12;
   int unsigned addrmap_row_b13;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP8_struct_t;

typedef struct  {
   int unsigned addrmap_row_b6;
   int unsigned addrmap_row_b7;
   int unsigned addrmap_row_b8;
   int unsigned addrmap_row_b9;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP9_struct_t;

typedef struct  {
   int unsigned addrmap_row_b2;
   int unsigned addrmap_row_b3;
   int unsigned addrmap_row_b4;
   int unsigned addrmap_row_b5;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP10_struct_t;

typedef struct  {
   int unsigned addrmap_row_b0;
   int unsigned addrmap_row_b1;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP11_struct_t;

typedef struct  {
   int unsigned nonbinary_device_density;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP12_struct_t;

`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned addrmap_cs_bit0;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef UMCTL2_CID_WIDTH_GT_0
typedef struct  {
   int unsigned addrmap_cid_b0;
   int unsigned addrmap_cid_b1;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP2_struct_t;

`endif //UMCTL2_CID_WIDTH_GT_0
typedef struct  {
   int unsigned addrmap_bank_b0;
   int unsigned addrmap_bank_b1;
   int unsigned addrmap_bank_b2;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP3_struct_t;

typedef struct  {
   int unsigned addrmap_bg_b0;
   int unsigned addrmap_bg_b1;
   int unsigned addrmap_bg_b2;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP4_struct_t;

typedef struct  {
   int unsigned addrmap_col_b7;
   int unsigned addrmap_col_b8;
   int unsigned addrmap_col_b9;
   int unsigned addrmap_col_b10;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP5_struct_t;

typedef struct  {
   int unsigned addrmap_col_b3;
   int unsigned addrmap_col_b4;
   int unsigned addrmap_col_b5;
   int unsigned addrmap_col_b6;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP6_struct_t;

typedef struct  {
   int unsigned addrmap_row_b14;
   int unsigned addrmap_row_b15;
   int unsigned addrmap_row_b16;
   int unsigned addrmap_row_b17;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP7_struct_t;

typedef struct  {
   int unsigned addrmap_row_b10;
   int unsigned addrmap_row_b11;
   int unsigned addrmap_row_b12;
   int unsigned addrmap_row_b13;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP8_struct_t;

typedef struct  {
   int unsigned addrmap_row_b6;
   int unsigned addrmap_row_b7;
   int unsigned addrmap_row_b8;
   int unsigned addrmap_row_b9;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP9_struct_t;

typedef struct  {
   int unsigned addrmap_row_b2;
   int unsigned addrmap_row_b3;
   int unsigned addrmap_row_b4;
   int unsigned addrmap_row_b5;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP10_struct_t;

typedef struct  {
   int unsigned addrmap_row_b0;
   int unsigned addrmap_row_b1;
  int unsigned value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP11_struct_t;

typedef struct  {
   int unsigned go2critical_en;
   int unsigned pagematch_limit;
   int unsigned dch_density_ratio;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCCFG_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_0
`ifdef UMCTL2_PORT_CH0_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_0
`ifdef UMCTL2_PORT_CH1_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_0
`ifdef UMCTL2_PORT_CH1_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_0
`ifdef UMCTL2_PORT_CH2_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_0
`ifdef UMCTL2_PORT_CH2_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_0
`ifdef UMCTL2_PORT_CH3_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_0
`ifdef UMCTL2_PORT_CH3_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_0
`ifdef UMCTL2_PORT_CH4_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_0
`ifdef UMCTL2_PORT_CH4_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_0
`ifdef UMCTL2_PORT_CH5_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_0
`ifdef UMCTL2_PORT_CH5_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_0
`ifdef UMCTL2_PORT_CH6_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_0
`ifdef UMCTL2_PORT_CH6_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_0
`ifdef UMCTL2_PORT_CH7_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_0
`ifdef UMCTL2_PORT_CH7_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_0
`ifdef UMCTL2_PORT_CH8_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_0
`ifdef UMCTL2_PORT_CH8_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_0
`ifdef UMCTL2_PORT_CH9_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_0
`ifdef UMCTL2_PORT_CH9_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_0
`ifdef UMCTL2_PORT_CH10_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_0
`ifdef UMCTL2_PORT_CH10_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_0
`ifdef UMCTL2_PORT_CH11_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_0
`ifdef UMCTL2_PORT_CH11_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_0
`ifdef UMCTL2_PORT_CH12_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_0
`ifdef UMCTL2_PORT_CH12_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_0
`ifdef UMCTL2_PORT_CH13_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_0
`ifdef UMCTL2_PORT_CH13_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_0
`ifdef UMCTL2_PORT_CH14_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_0
`ifdef UMCTL2_PORT_CH14_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_0
`ifdef UMCTL2_PORT_CH15_0
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_0
`ifdef UMCTL2_PORT_CH15_0
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_0
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGWQOS1_struct_t;

`ifdef UMCTL2_A_SAR_0
typedef struct  {
   int unsigned base_addr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARBASE0_struct_t;

`endif //UMCTL2_A_SAR_0
`ifdef UMCTL2_A_SAR_0
typedef struct  {
   int unsigned nblocks;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARSIZE0_struct_t;

`endif //UMCTL2_A_SAR_0
`ifdef UMCTL2_A_SAR_1
typedef struct  {
   int unsigned base_addr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARBASE1_struct_t;

`endif //UMCTL2_A_SAR_1
`ifdef UMCTL2_A_SAR_1
typedef struct  {
   int unsigned nblocks;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARSIZE1_struct_t;

`endif //UMCTL2_A_SAR_1
`ifdef UMCTL2_A_SAR_2
typedef struct  {
   int unsigned base_addr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARBASE2_struct_t;

`endif //UMCTL2_A_SAR_2
`ifdef UMCTL2_A_SAR_2
typedef struct  {
   int unsigned nblocks;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARSIZE2_struct_t;

`endif //UMCTL2_A_SAR_2
`ifdef UMCTL2_A_SAR_3
typedef struct  {
   int unsigned base_addr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARBASE3_struct_t;

`endif //UMCTL2_A_SAR_3
`ifdef UMCTL2_A_SAR_3
typedef struct  {
   int unsigned nblocks;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARSIZE3_struct_t;

`endif //UMCTL2_A_SAR_3
`ifdef UMCTL2_SBR_EN_1
typedef struct  {
   int unsigned scrub_en;
   int unsigned scrub_during_lowpower;
   int unsigned scrub_en_dch1;
   int unsigned scrub_burst_length_normal;
   int unsigned scrub_interval;
   int unsigned scrub_cmd_type;
   int unsigned gen_rmw;
   int unsigned scrub_burst_length_lp;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRCTL_struct_t;

`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
typedef struct  {
   int unsigned scrub_pattern0;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRWDATA0_struct_t;

`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
`ifdef MEMC_DRAM_DATA_WIDTH_64
typedef struct  {
   int unsigned scrub_pattern1;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRWDATA1_struct_t;

`endif //MEMC_DRAM_DATA_WIDTH_64
`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
typedef struct  {
   int unsigned sbr_address_start_mask_0;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRSTART0_struct_t;

`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
typedef struct  {
   int unsigned sbr_address_start_mask_1;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRSTART1_struct_t;

`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
typedef struct  {
   int unsigned sbr_address_range_mask_0;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRRANGE0_struct_t;

`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
typedef struct  {
   int unsigned sbr_address_range_mask_1;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRRANGE1_struct_t;

`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
`ifdef UMCTL2_DUAL_DATA_CHANNEL
typedef struct  {
   int unsigned sbr_address_start_mask_dch1_0;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRSTART0DCH1_struct_t;

`endif //UMCTL2_DUAL_DATA_CHANNEL
`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
`ifdef UMCTL2_DUAL_DATA_CHANNEL
typedef struct  {
   int unsigned sbr_address_start_mask_dch1_1;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRSTART1DCH1_struct_t;

`endif //UMCTL2_DUAL_DATA_CHANNEL
`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
`ifdef UMCTL2_DUAL_DATA_CHANNEL
typedef struct  {
   int unsigned sbr_address_range_mask_dch1_0;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRRANGE0DCH1_struct_t;

`endif //UMCTL2_DUAL_DATA_CHANNEL
`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_SBR_EN_1
`ifdef UMCTL2_DUAL_DATA_CHANNEL
typedef struct  {
   int unsigned sbr_address_range_mask_dch1_1;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRRANGE1DCH1_struct_t;

`endif //UMCTL2_DUAL_DATA_CHANNEL
`endif //UMCTL2_SBR_EN_1
`ifdef UMCTL2_DUAL_DATA_CHANNEL
`ifndef UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
typedef struct  {
   int unsigned port_data_channel_0;
   int unsigned port_data_channel_1;
   int unsigned port_data_channel_2;
   int unsigned port_data_channel_3;
   int unsigned port_data_channel_4;
   int unsigned port_data_channel_5;
   int unsigned port_data_channel_6;
   int unsigned port_data_channel_7;
   int unsigned port_data_channel_8;
   int unsigned port_data_channel_9;
   int unsigned port_data_channel_10;
   int unsigned port_data_channel_11;
   int unsigned port_data_channel_12;
   int unsigned port_data_channel_13;
   int unsigned port_data_channel_14;
   int unsigned port_data_channel_15;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT0_PDCH_struct_t;

`endif //UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
`endif //UMCTL2_DUAL_DATA_CHANNEL
typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_1
`ifdef UMCTL2_PORT_CH0_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_1
`ifdef UMCTL2_PORT_CH1_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_1
`ifdef UMCTL2_PORT_CH1_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_1
`ifdef UMCTL2_PORT_CH2_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_1
`ifdef UMCTL2_PORT_CH2_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_1
`ifdef UMCTL2_PORT_CH3_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_1
`ifdef UMCTL2_PORT_CH3_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_1
`ifdef UMCTL2_PORT_CH4_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_1
`ifdef UMCTL2_PORT_CH4_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_1
`ifdef UMCTL2_PORT_CH5_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_1
`ifdef UMCTL2_PORT_CH5_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_1
`ifdef UMCTL2_PORT_CH6_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_1
`ifdef UMCTL2_PORT_CH6_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_1
`ifdef UMCTL2_PORT_CH7_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_1
`ifdef UMCTL2_PORT_CH7_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_1
`ifdef UMCTL2_PORT_CH8_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_1
`ifdef UMCTL2_PORT_CH8_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_1
`ifdef UMCTL2_PORT_CH9_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_1
`ifdef UMCTL2_PORT_CH9_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_1
`ifdef UMCTL2_PORT_CH10_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_1
`ifdef UMCTL2_PORT_CH10_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_1
`ifdef UMCTL2_PORT_CH11_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_1
`ifdef UMCTL2_PORT_CH11_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_1
`ifdef UMCTL2_PORT_CH12_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_1
`ifdef UMCTL2_PORT_CH12_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_1
`ifdef UMCTL2_PORT_CH13_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_1
`ifdef UMCTL2_PORT_CH13_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_1
`ifdef UMCTL2_PORT_CH14_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_1
`ifdef UMCTL2_PORT_CH14_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_1
`ifdef UMCTL2_PORT_CH15_1
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_1
`ifdef UMCTL2_PORT_CH15_1
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_1
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_2
`ifdef UMCTL2_PORT_CH0_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_2
`ifdef UMCTL2_PORT_CH1_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_2
`ifdef UMCTL2_PORT_CH1_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_2
`ifdef UMCTL2_PORT_CH2_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_2
`ifdef UMCTL2_PORT_CH2_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_2
`ifdef UMCTL2_PORT_CH3_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_2
`ifdef UMCTL2_PORT_CH3_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_2
`ifdef UMCTL2_PORT_CH4_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_2
`ifdef UMCTL2_PORT_CH4_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_2
`ifdef UMCTL2_PORT_CH5_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_2
`ifdef UMCTL2_PORT_CH5_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_2
`ifdef UMCTL2_PORT_CH6_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_2
`ifdef UMCTL2_PORT_CH6_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_2
`ifdef UMCTL2_PORT_CH7_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_2
`ifdef UMCTL2_PORT_CH7_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_2
`ifdef UMCTL2_PORT_CH8_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_2
`ifdef UMCTL2_PORT_CH8_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_2
`ifdef UMCTL2_PORT_CH9_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_2
`ifdef UMCTL2_PORT_CH9_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_2
`ifdef UMCTL2_PORT_CH10_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_2
`ifdef UMCTL2_PORT_CH10_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_2
`ifdef UMCTL2_PORT_CH11_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_2
`ifdef UMCTL2_PORT_CH11_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_2
`ifdef UMCTL2_PORT_CH12_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_2
`ifdef UMCTL2_PORT_CH12_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_2
`ifdef UMCTL2_PORT_CH13_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_2
`ifdef UMCTL2_PORT_CH13_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_2
`ifdef UMCTL2_PORT_CH14_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_2
`ifdef UMCTL2_PORT_CH14_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_2
`ifdef UMCTL2_PORT_CH15_2
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_2
`ifdef UMCTL2_PORT_CH15_2
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_2
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_3
`ifdef UMCTL2_PORT_CH0_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_3
`ifdef UMCTL2_PORT_CH1_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_3
`ifdef UMCTL2_PORT_CH1_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_3
`ifdef UMCTL2_PORT_CH2_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_3
`ifdef UMCTL2_PORT_CH2_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_3
`ifdef UMCTL2_PORT_CH3_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_3
`ifdef UMCTL2_PORT_CH3_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_3
`ifdef UMCTL2_PORT_CH4_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_3
`ifdef UMCTL2_PORT_CH4_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_3
`ifdef UMCTL2_PORT_CH5_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_3
`ifdef UMCTL2_PORT_CH5_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_3
`ifdef UMCTL2_PORT_CH6_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_3
`ifdef UMCTL2_PORT_CH6_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_3
`ifdef UMCTL2_PORT_CH7_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_3
`ifdef UMCTL2_PORT_CH7_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_3
`ifdef UMCTL2_PORT_CH8_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_3
`ifdef UMCTL2_PORT_CH8_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_3
`ifdef UMCTL2_PORT_CH9_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_3
`ifdef UMCTL2_PORT_CH9_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_3
`ifdef UMCTL2_PORT_CH10_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_3
`ifdef UMCTL2_PORT_CH10_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_3
`ifdef UMCTL2_PORT_CH11_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_3
`ifdef UMCTL2_PORT_CH11_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_3
`ifdef UMCTL2_PORT_CH12_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_3
`ifdef UMCTL2_PORT_CH12_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_3
`ifdef UMCTL2_PORT_CH13_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_3
`ifdef UMCTL2_PORT_CH13_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_3
`ifdef UMCTL2_PORT_CH14_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_3
`ifdef UMCTL2_PORT_CH14_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_3
`ifdef UMCTL2_PORT_CH15_3
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_3
`ifdef UMCTL2_PORT_CH15_3
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_3
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_4
`ifdef UMCTL2_PORT_CH0_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_4
`ifdef UMCTL2_PORT_CH1_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_4
`ifdef UMCTL2_PORT_CH1_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_4
`ifdef UMCTL2_PORT_CH2_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_4
`ifdef UMCTL2_PORT_CH2_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_4
`ifdef UMCTL2_PORT_CH3_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_4
`ifdef UMCTL2_PORT_CH3_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_4
`ifdef UMCTL2_PORT_CH4_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_4
`ifdef UMCTL2_PORT_CH4_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_4
`ifdef UMCTL2_PORT_CH5_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_4
`ifdef UMCTL2_PORT_CH5_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_4
`ifdef UMCTL2_PORT_CH6_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_4
`ifdef UMCTL2_PORT_CH6_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_4
`ifdef UMCTL2_PORT_CH7_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_4
`ifdef UMCTL2_PORT_CH7_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_4
`ifdef UMCTL2_PORT_CH8_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_4
`ifdef UMCTL2_PORT_CH8_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_4
`ifdef UMCTL2_PORT_CH9_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_4
`ifdef UMCTL2_PORT_CH9_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_4
`ifdef UMCTL2_PORT_CH10_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_4
`ifdef UMCTL2_PORT_CH10_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_4
`ifdef UMCTL2_PORT_CH11_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_4
`ifdef UMCTL2_PORT_CH11_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_4
`ifdef UMCTL2_PORT_CH12_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_4
`ifdef UMCTL2_PORT_CH12_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_4
`ifdef UMCTL2_PORT_CH13_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_4
`ifdef UMCTL2_PORT_CH13_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_4
`ifdef UMCTL2_PORT_CH14_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_4
`ifdef UMCTL2_PORT_CH14_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_4
`ifdef UMCTL2_PORT_CH15_4
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_4
`ifdef UMCTL2_PORT_CH15_4
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_4
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_5
`ifdef UMCTL2_PORT_CH0_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_5
`ifdef UMCTL2_PORT_CH1_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_5
`ifdef UMCTL2_PORT_CH1_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_5
`ifdef UMCTL2_PORT_CH2_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_5
`ifdef UMCTL2_PORT_CH2_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_5
`ifdef UMCTL2_PORT_CH3_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_5
`ifdef UMCTL2_PORT_CH3_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_5
`ifdef UMCTL2_PORT_CH4_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_5
`ifdef UMCTL2_PORT_CH4_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_5
`ifdef UMCTL2_PORT_CH5_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_5
`ifdef UMCTL2_PORT_CH5_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_5
`ifdef UMCTL2_PORT_CH6_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_5
`ifdef UMCTL2_PORT_CH6_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_5
`ifdef UMCTL2_PORT_CH7_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_5
`ifdef UMCTL2_PORT_CH7_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_5
`ifdef UMCTL2_PORT_CH8_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_5
`ifdef UMCTL2_PORT_CH8_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_5
`ifdef UMCTL2_PORT_CH9_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_5
`ifdef UMCTL2_PORT_CH9_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_5
`ifdef UMCTL2_PORT_CH10_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_5
`ifdef UMCTL2_PORT_CH10_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_5
`ifdef UMCTL2_PORT_CH11_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_5
`ifdef UMCTL2_PORT_CH11_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_5
`ifdef UMCTL2_PORT_CH12_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_5
`ifdef UMCTL2_PORT_CH12_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_5
`ifdef UMCTL2_PORT_CH13_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_5
`ifdef UMCTL2_PORT_CH13_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_5
`ifdef UMCTL2_PORT_CH14_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_5
`ifdef UMCTL2_PORT_CH14_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_5
`ifdef UMCTL2_PORT_CH15_5
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_5
`ifdef UMCTL2_PORT_CH15_5
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_5
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_6
`ifdef UMCTL2_PORT_CH0_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_6
`ifdef UMCTL2_PORT_CH1_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_6
`ifdef UMCTL2_PORT_CH1_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_6
`ifdef UMCTL2_PORT_CH2_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_6
`ifdef UMCTL2_PORT_CH2_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_6
`ifdef UMCTL2_PORT_CH3_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_6
`ifdef UMCTL2_PORT_CH3_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_6
`ifdef UMCTL2_PORT_CH4_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_6
`ifdef UMCTL2_PORT_CH4_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_6
`ifdef UMCTL2_PORT_CH5_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_6
`ifdef UMCTL2_PORT_CH5_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_6
`ifdef UMCTL2_PORT_CH6_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_6
`ifdef UMCTL2_PORT_CH6_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_6
`ifdef UMCTL2_PORT_CH7_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_6
`ifdef UMCTL2_PORT_CH7_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_6
`ifdef UMCTL2_PORT_CH8_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_6
`ifdef UMCTL2_PORT_CH8_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_6
`ifdef UMCTL2_PORT_CH9_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_6
`ifdef UMCTL2_PORT_CH9_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_6
`ifdef UMCTL2_PORT_CH10_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_6
`ifdef UMCTL2_PORT_CH10_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_6
`ifdef UMCTL2_PORT_CH11_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_6
`ifdef UMCTL2_PORT_CH11_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_6
`ifdef UMCTL2_PORT_CH12_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_6
`ifdef UMCTL2_PORT_CH12_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_6
`ifdef UMCTL2_PORT_CH13_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_6
`ifdef UMCTL2_PORT_CH13_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_6
`ifdef UMCTL2_PORT_CH14_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_6
`ifdef UMCTL2_PORT_CH14_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_6
`ifdef UMCTL2_PORT_CH15_6
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_6
`ifdef UMCTL2_PORT_CH15_6
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_6
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_7
`ifdef UMCTL2_PORT_CH0_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_7
`ifdef UMCTL2_PORT_CH1_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_7
`ifdef UMCTL2_PORT_CH1_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_7
`ifdef UMCTL2_PORT_CH2_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_7
`ifdef UMCTL2_PORT_CH2_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_7
`ifdef UMCTL2_PORT_CH3_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_7
`ifdef UMCTL2_PORT_CH3_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_7
`ifdef UMCTL2_PORT_CH4_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_7
`ifdef UMCTL2_PORT_CH4_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_7
`ifdef UMCTL2_PORT_CH5_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_7
`ifdef UMCTL2_PORT_CH5_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_7
`ifdef UMCTL2_PORT_CH6_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_7
`ifdef UMCTL2_PORT_CH6_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_7
`ifdef UMCTL2_PORT_CH7_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_7
`ifdef UMCTL2_PORT_CH7_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_7
`ifdef UMCTL2_PORT_CH8_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_7
`ifdef UMCTL2_PORT_CH8_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_7
`ifdef UMCTL2_PORT_CH9_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_7
`ifdef UMCTL2_PORT_CH9_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_7
`ifdef UMCTL2_PORT_CH10_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_7
`ifdef UMCTL2_PORT_CH10_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_7
`ifdef UMCTL2_PORT_CH11_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_7
`ifdef UMCTL2_PORT_CH11_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_7
`ifdef UMCTL2_PORT_CH12_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_7
`ifdef UMCTL2_PORT_CH12_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_7
`ifdef UMCTL2_PORT_CH13_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_7
`ifdef UMCTL2_PORT_CH13_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_7
`ifdef UMCTL2_PORT_CH14_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_7
`ifdef UMCTL2_PORT_CH14_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_7
`ifdef UMCTL2_PORT_CH15_7
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_7
`ifdef UMCTL2_PORT_CH15_7
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_7
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_8
`ifdef UMCTL2_PORT_CH0_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_8
`ifdef UMCTL2_PORT_CH1_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_8
`ifdef UMCTL2_PORT_CH1_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_8
`ifdef UMCTL2_PORT_CH2_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_8
`ifdef UMCTL2_PORT_CH2_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_8
`ifdef UMCTL2_PORT_CH3_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_8
`ifdef UMCTL2_PORT_CH3_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_8
`ifdef UMCTL2_PORT_CH4_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_8
`ifdef UMCTL2_PORT_CH4_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_8
`ifdef UMCTL2_PORT_CH5_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_8
`ifdef UMCTL2_PORT_CH5_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_8
`ifdef UMCTL2_PORT_CH6_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_8
`ifdef UMCTL2_PORT_CH6_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_8
`ifdef UMCTL2_PORT_CH7_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_8
`ifdef UMCTL2_PORT_CH7_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_8
`ifdef UMCTL2_PORT_CH8_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_8
`ifdef UMCTL2_PORT_CH8_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_8
`ifdef UMCTL2_PORT_CH9_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_8
`ifdef UMCTL2_PORT_CH9_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_8
`ifdef UMCTL2_PORT_CH10_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_8
`ifdef UMCTL2_PORT_CH10_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_8
`ifdef UMCTL2_PORT_CH11_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_8
`ifdef UMCTL2_PORT_CH11_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_8
`ifdef UMCTL2_PORT_CH12_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_8
`ifdef UMCTL2_PORT_CH12_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_8
`ifdef UMCTL2_PORT_CH13_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_8
`ifdef UMCTL2_PORT_CH13_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_8
`ifdef UMCTL2_PORT_CH14_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_8
`ifdef UMCTL2_PORT_CH14_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_8
`ifdef UMCTL2_PORT_CH15_8
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_8
`ifdef UMCTL2_PORT_CH15_8
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_8
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_9
`ifdef UMCTL2_PORT_CH0_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_9
`ifdef UMCTL2_PORT_CH1_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_9
`ifdef UMCTL2_PORT_CH1_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_9
`ifdef UMCTL2_PORT_CH2_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_9
`ifdef UMCTL2_PORT_CH2_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_9
`ifdef UMCTL2_PORT_CH3_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_9
`ifdef UMCTL2_PORT_CH3_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_9
`ifdef UMCTL2_PORT_CH4_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_9
`ifdef UMCTL2_PORT_CH4_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_9
`ifdef UMCTL2_PORT_CH5_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_9
`ifdef UMCTL2_PORT_CH5_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_9
`ifdef UMCTL2_PORT_CH6_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_9
`ifdef UMCTL2_PORT_CH6_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_9
`ifdef UMCTL2_PORT_CH7_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_9
`ifdef UMCTL2_PORT_CH7_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_9
`ifdef UMCTL2_PORT_CH8_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_9
`ifdef UMCTL2_PORT_CH8_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_9
`ifdef UMCTL2_PORT_CH9_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_9
`ifdef UMCTL2_PORT_CH9_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_9
`ifdef UMCTL2_PORT_CH10_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_9
`ifdef UMCTL2_PORT_CH10_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_9
`ifdef UMCTL2_PORT_CH11_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_9
`ifdef UMCTL2_PORT_CH11_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_9
`ifdef UMCTL2_PORT_CH12_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_9
`ifdef UMCTL2_PORT_CH12_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_9
`ifdef UMCTL2_PORT_CH13_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_9
`ifdef UMCTL2_PORT_CH13_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_9
`ifdef UMCTL2_PORT_CH14_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_9
`ifdef UMCTL2_PORT_CH14_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_9
`ifdef UMCTL2_PORT_CH15_9
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_9
`ifdef UMCTL2_PORT_CH15_9
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_9
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_10
`ifdef UMCTL2_PORT_CH0_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_10
`ifdef UMCTL2_PORT_CH1_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_10
`ifdef UMCTL2_PORT_CH1_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_10
`ifdef UMCTL2_PORT_CH2_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_10
`ifdef UMCTL2_PORT_CH2_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_10
`ifdef UMCTL2_PORT_CH3_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_10
`ifdef UMCTL2_PORT_CH3_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_10
`ifdef UMCTL2_PORT_CH4_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_10
`ifdef UMCTL2_PORT_CH4_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_10
`ifdef UMCTL2_PORT_CH5_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_10
`ifdef UMCTL2_PORT_CH5_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_10
`ifdef UMCTL2_PORT_CH6_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_10
`ifdef UMCTL2_PORT_CH6_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_10
`ifdef UMCTL2_PORT_CH7_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_10
`ifdef UMCTL2_PORT_CH7_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_10
`ifdef UMCTL2_PORT_CH8_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_10
`ifdef UMCTL2_PORT_CH8_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_10
`ifdef UMCTL2_PORT_CH9_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_10
`ifdef UMCTL2_PORT_CH9_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_10
`ifdef UMCTL2_PORT_CH10_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_10
`ifdef UMCTL2_PORT_CH10_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_10
`ifdef UMCTL2_PORT_CH11_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_10
`ifdef UMCTL2_PORT_CH11_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_10
`ifdef UMCTL2_PORT_CH12_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_10
`ifdef UMCTL2_PORT_CH12_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_10
`ifdef UMCTL2_PORT_CH13_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_10
`ifdef UMCTL2_PORT_CH13_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_10
`ifdef UMCTL2_PORT_CH14_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_10
`ifdef UMCTL2_PORT_CH14_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_10
`ifdef UMCTL2_PORT_CH15_10
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_10
`ifdef UMCTL2_PORT_CH15_10
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_10
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_11
`ifdef UMCTL2_PORT_CH0_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_11
`ifdef UMCTL2_PORT_CH1_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_11
`ifdef UMCTL2_PORT_CH1_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_11
`ifdef UMCTL2_PORT_CH2_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_11
`ifdef UMCTL2_PORT_CH2_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_11
`ifdef UMCTL2_PORT_CH3_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_11
`ifdef UMCTL2_PORT_CH3_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_11
`ifdef UMCTL2_PORT_CH4_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_11
`ifdef UMCTL2_PORT_CH4_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_11
`ifdef UMCTL2_PORT_CH5_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_11
`ifdef UMCTL2_PORT_CH5_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_11
`ifdef UMCTL2_PORT_CH6_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_11
`ifdef UMCTL2_PORT_CH6_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_11
`ifdef UMCTL2_PORT_CH7_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_11
`ifdef UMCTL2_PORT_CH7_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_11
`ifdef UMCTL2_PORT_CH8_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_11
`ifdef UMCTL2_PORT_CH8_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_11
`ifdef UMCTL2_PORT_CH9_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_11
`ifdef UMCTL2_PORT_CH9_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_11
`ifdef UMCTL2_PORT_CH10_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_11
`ifdef UMCTL2_PORT_CH10_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_11
`ifdef UMCTL2_PORT_CH11_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_11
`ifdef UMCTL2_PORT_CH11_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_11
`ifdef UMCTL2_PORT_CH12_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_11
`ifdef UMCTL2_PORT_CH12_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_11
`ifdef UMCTL2_PORT_CH13_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_11
`ifdef UMCTL2_PORT_CH13_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_11
`ifdef UMCTL2_PORT_CH14_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_11
`ifdef UMCTL2_PORT_CH14_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_11
`ifdef UMCTL2_PORT_CH15_11
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_11
`ifdef UMCTL2_PORT_CH15_11
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_11
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_12
`ifdef UMCTL2_PORT_CH0_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_12
`ifdef UMCTL2_PORT_CH1_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_12
`ifdef UMCTL2_PORT_CH1_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_12
`ifdef UMCTL2_PORT_CH2_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_12
`ifdef UMCTL2_PORT_CH2_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_12
`ifdef UMCTL2_PORT_CH3_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_12
`ifdef UMCTL2_PORT_CH3_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_12
`ifdef UMCTL2_PORT_CH4_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_12
`ifdef UMCTL2_PORT_CH4_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_12
`ifdef UMCTL2_PORT_CH5_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_12
`ifdef UMCTL2_PORT_CH5_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_12
`ifdef UMCTL2_PORT_CH6_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_12
`ifdef UMCTL2_PORT_CH6_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_12
`ifdef UMCTL2_PORT_CH7_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_12
`ifdef UMCTL2_PORT_CH7_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_12
`ifdef UMCTL2_PORT_CH8_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_12
`ifdef UMCTL2_PORT_CH8_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_12
`ifdef UMCTL2_PORT_CH9_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_12
`ifdef UMCTL2_PORT_CH9_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_12
`ifdef UMCTL2_PORT_CH10_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_12
`ifdef UMCTL2_PORT_CH10_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_12
`ifdef UMCTL2_PORT_CH11_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_12
`ifdef UMCTL2_PORT_CH11_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_12
`ifdef UMCTL2_PORT_CH12_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_12
`ifdef UMCTL2_PORT_CH12_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_12
`ifdef UMCTL2_PORT_CH13_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_12
`ifdef UMCTL2_PORT_CH13_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_12
`ifdef UMCTL2_PORT_CH14_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_12
`ifdef UMCTL2_PORT_CH14_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_12
`ifdef UMCTL2_PORT_CH15_12
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_12
`ifdef UMCTL2_PORT_CH15_12
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_12
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_13
`ifdef UMCTL2_PORT_CH0_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_13
`ifdef UMCTL2_PORT_CH1_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_13
`ifdef UMCTL2_PORT_CH1_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_13
`ifdef UMCTL2_PORT_CH2_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_13
`ifdef UMCTL2_PORT_CH2_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_13
`ifdef UMCTL2_PORT_CH3_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_13
`ifdef UMCTL2_PORT_CH3_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_13
`ifdef UMCTL2_PORT_CH4_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_13
`ifdef UMCTL2_PORT_CH4_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_13
`ifdef UMCTL2_PORT_CH5_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_13
`ifdef UMCTL2_PORT_CH5_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_13
`ifdef UMCTL2_PORT_CH6_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_13
`ifdef UMCTL2_PORT_CH6_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_13
`ifdef UMCTL2_PORT_CH7_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_13
`ifdef UMCTL2_PORT_CH7_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_13
`ifdef UMCTL2_PORT_CH8_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_13
`ifdef UMCTL2_PORT_CH8_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_13
`ifdef UMCTL2_PORT_CH9_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_13
`ifdef UMCTL2_PORT_CH9_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_13
`ifdef UMCTL2_PORT_CH10_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_13
`ifdef UMCTL2_PORT_CH10_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_13
`ifdef UMCTL2_PORT_CH11_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_13
`ifdef UMCTL2_PORT_CH11_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_13
`ifdef UMCTL2_PORT_CH12_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_13
`ifdef UMCTL2_PORT_CH12_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_13
`ifdef UMCTL2_PORT_CH13_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_13
`ifdef UMCTL2_PORT_CH13_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_13
`ifdef UMCTL2_PORT_CH14_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_13
`ifdef UMCTL2_PORT_CH14_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_13
`ifdef UMCTL2_PORT_CH15_13
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_13
`ifdef UMCTL2_PORT_CH15_13
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_13
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_14
`ifdef UMCTL2_PORT_CH0_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_14
`ifdef UMCTL2_PORT_CH1_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_14
`ifdef UMCTL2_PORT_CH1_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_14
`ifdef UMCTL2_PORT_CH2_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_14
`ifdef UMCTL2_PORT_CH2_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_14
`ifdef UMCTL2_PORT_CH3_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_14
`ifdef UMCTL2_PORT_CH3_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_14
`ifdef UMCTL2_PORT_CH4_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_14
`ifdef UMCTL2_PORT_CH4_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_14
`ifdef UMCTL2_PORT_CH5_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_14
`ifdef UMCTL2_PORT_CH5_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_14
`ifdef UMCTL2_PORT_CH6_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_14
`ifdef UMCTL2_PORT_CH6_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_14
`ifdef UMCTL2_PORT_CH7_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_14
`ifdef UMCTL2_PORT_CH7_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_14
`ifdef UMCTL2_PORT_CH8_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_14
`ifdef UMCTL2_PORT_CH8_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_14
`ifdef UMCTL2_PORT_CH9_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_14
`ifdef UMCTL2_PORT_CH9_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_14
`ifdef UMCTL2_PORT_CH10_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_14
`ifdef UMCTL2_PORT_CH10_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_14
`ifdef UMCTL2_PORT_CH11_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_14
`ifdef UMCTL2_PORT_CH11_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_14
`ifdef UMCTL2_PORT_CH12_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_14
`ifdef UMCTL2_PORT_CH12_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_14
`ifdef UMCTL2_PORT_CH13_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_14
`ifdef UMCTL2_PORT_CH13_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_14
`ifdef UMCTL2_PORT_CH14_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_14
`ifdef UMCTL2_PORT_CH14_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_14
`ifdef UMCTL2_PORT_CH15_14
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_14
`ifdef UMCTL2_PORT_CH15_14
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_14
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned rd_port_priority;
   int unsigned read_reorder_bypass_en;
   int unsigned rd_port_aging_en;
   int unsigned rd_port_urgent_en;
   int unsigned rd_port_pagematch_en;
   int unsigned rdwr_ordered_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGR_struct_t;

typedef struct  {
   int unsigned wr_port_priority;
   int unsigned wr_port_aging_en;
   int unsigned wr_port_urgent_en;
   int unsigned wr_port_pagematch_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGW_struct_t;

`ifdef UMCTL2_PORT_CH0_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH0_struct_t;

`endif //UMCTL2_PORT_CH0_15
`ifdef UMCTL2_PORT_CH0_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH0_struct_t;

`endif //UMCTL2_PORT_CH0_15
`ifdef UMCTL2_PORT_CH1_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH1_struct_t;

`endif //UMCTL2_PORT_CH1_15
`ifdef UMCTL2_PORT_CH1_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH1_struct_t;

`endif //UMCTL2_PORT_CH1_15
`ifdef UMCTL2_PORT_CH2_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH2_struct_t;

`endif //UMCTL2_PORT_CH2_15
`ifdef UMCTL2_PORT_CH2_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH2_struct_t;

`endif //UMCTL2_PORT_CH2_15
`ifdef UMCTL2_PORT_CH3_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH3_struct_t;

`endif //UMCTL2_PORT_CH3_15
`ifdef UMCTL2_PORT_CH3_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH3_struct_t;

`endif //UMCTL2_PORT_CH3_15
`ifdef UMCTL2_PORT_CH4_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH4_struct_t;

`endif //UMCTL2_PORT_CH4_15
`ifdef UMCTL2_PORT_CH4_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH4_struct_t;

`endif //UMCTL2_PORT_CH4_15
`ifdef UMCTL2_PORT_CH5_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH5_struct_t;

`endif //UMCTL2_PORT_CH5_15
`ifdef UMCTL2_PORT_CH5_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH5_struct_t;

`endif //UMCTL2_PORT_CH5_15
`ifdef UMCTL2_PORT_CH6_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH6_struct_t;

`endif //UMCTL2_PORT_CH6_15
`ifdef UMCTL2_PORT_CH6_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH6_struct_t;

`endif //UMCTL2_PORT_CH6_15
`ifdef UMCTL2_PORT_CH7_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH7_struct_t;

`endif //UMCTL2_PORT_CH7_15
`ifdef UMCTL2_PORT_CH7_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH7_struct_t;

`endif //UMCTL2_PORT_CH7_15
`ifdef UMCTL2_PORT_CH8_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH8_struct_t;

`endif //UMCTL2_PORT_CH8_15
`ifdef UMCTL2_PORT_CH8_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH8_struct_t;

`endif //UMCTL2_PORT_CH8_15
`ifdef UMCTL2_PORT_CH9_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH9_struct_t;

`endif //UMCTL2_PORT_CH9_15
`ifdef UMCTL2_PORT_CH9_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH9_struct_t;

`endif //UMCTL2_PORT_CH9_15
`ifdef UMCTL2_PORT_CH10_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH10_struct_t;

`endif //UMCTL2_PORT_CH10_15
`ifdef UMCTL2_PORT_CH10_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH10_struct_t;

`endif //UMCTL2_PORT_CH10_15
`ifdef UMCTL2_PORT_CH11_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH11_struct_t;

`endif //UMCTL2_PORT_CH11_15
`ifdef UMCTL2_PORT_CH11_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH11_struct_t;

`endif //UMCTL2_PORT_CH11_15
`ifdef UMCTL2_PORT_CH12_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH12_struct_t;

`endif //UMCTL2_PORT_CH12_15
`ifdef UMCTL2_PORT_CH12_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH12_struct_t;

`endif //UMCTL2_PORT_CH12_15
`ifdef UMCTL2_PORT_CH13_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH13_struct_t;

`endif //UMCTL2_PORT_CH13_15
`ifdef UMCTL2_PORT_CH13_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH13_struct_t;

`endif //UMCTL2_PORT_CH13_15
`ifdef UMCTL2_PORT_CH14_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH14_struct_t;

`endif //UMCTL2_PORT_CH14_15
`ifdef UMCTL2_PORT_CH14_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH14_struct_t;

`endif //UMCTL2_PORT_CH14_15
`ifdef UMCTL2_PORT_CH15_15
typedef struct  {
   int unsigned id_mask;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH15_struct_t;

`endif //UMCTL2_PORT_CH15_15
`ifdef UMCTL2_PORT_CH15_15
typedef struct  {
   int unsigned id_value;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH15_struct_t;

`endif //UMCTL2_PORT_CH15_15
typedef struct  {
   int unsigned port_en;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCTRL_struct_t;

typedef struct  {
   int unsigned rqos_map_level1;
   int unsigned rqos_map_level2;
   int unsigned rqos_map_region0;
   int unsigned rqos_map_region1;
   int unsigned rqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGQOS0_struct_t;

typedef struct  {
   int unsigned rqos_map_timeoutb;
   int unsigned rqos_map_timeoutr;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGQOS1_struct_t;

typedef struct  {
   int unsigned wqos_map_level1;
   int unsigned wqos_map_level2;
   int unsigned wqos_map_region0;
   int unsigned wqos_map_region1;
   int unsigned wqos_map_region2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGWQOS0_struct_t;

typedef struct  {
   int unsigned wqos_map_timeout1;
   int unsigned wqos_map_timeout2;
  int unsigned value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGWQOS1_struct_t;

typedef struct  {
   int unsigned t_ras_min;
   int unsigned t_ras_max;
   int unsigned t_faw;
   int unsigned wr2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rc;
   int unsigned rd2pre;
   int unsigned t_xp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG1_struct_t;

typedef struct  {
   int unsigned wr2rd;
   int unsigned rd2wr;
   int unsigned read_latency;
   int unsigned write_latency;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG2_struct_t;

typedef struct  {
   int unsigned wr2mr;
   int unsigned rd2mr;
   int unsigned t_mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG3_struct_t;

typedef struct  {
   int unsigned t_rp;
   int unsigned t_rrd;
   int unsigned t_ccd;
   int unsigned t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG4_struct_t;

typedef struct  {
   int unsigned t_cke;
   int unsigned t_ckesr;
   int unsigned t_cksre;
   int unsigned t_cksrx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG5_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_ckcsx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG6_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_csh;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG7_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xs_x32;
   int unsigned t_xs_dll_x32;
   int unsigned t_xs_abort_x32;
   int unsigned t_xs_fast_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG8_struct_t;

typedef struct  {
   int unsigned wr2rd_s;
   int unsigned t_rrd_s;
   int unsigned t_ccd_s;
   int unsigned ddr4_wr_preamble;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG9_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned t_gear_hold;
   int unsigned t_gear_setup;
   int unsigned t_cmd_gear;
   int unsigned t_sync_gear;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG10_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_ckmpe;
   int unsigned t_mpx_s;
   int unsigned t_mpx_lh;
   int unsigned post_mpsm_gap_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG11_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned t_mrd_pda;
   int unsigned t_cmdcke;
   int unsigned t_wr_mpr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG12_struct_t;

typedef struct  {
   int unsigned t_ppd;
   int unsigned t_ccd_w2;
   int unsigned t_ccd_mw;
   int unsigned odtloff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG13_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xsr;
   int unsigned t_osco;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG14_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_stab_x32;
   int unsigned en_hwffc_t_stab;
   int unsigned en_dfi_lp_t_stab;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG15_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr;
   int unsigned t_rrd_dlr;
   int unsigned t_faw_dlr;
   int unsigned t_rp_ca_parity;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG16_struct_t;

`endif //UMCTL2_CID_EN
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned t_vrcg_disable;
   int unsigned t_vrcg_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG17_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mpdpxact;
   int unsigned t_mpsmx;
   int unsigned t_pd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG18_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_pda_h;
   int unsigned t_pda_s;
   int unsigned t_pda_dqs_delay;
   int unsigned t_pda_delay;
   int unsigned t_pda_latch;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG19_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_csl_srexit;
   int unsigned t_csh_srexit;
   int unsigned t_casrx;
   int unsigned t_cpded;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_osco_ddr5;
   int unsigned t_vrefca_cs;
   int unsigned t_mpc_hold;
   int unsigned t_mpc_setup;
   int unsigned t_mpc_cs;
   int unsigned t_csl;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rd2wr_dpr;
   int unsigned t_rd2wr_dlr;
   int unsigned t_wr2rd_dpr;
   int unsigned t_wr2rd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG22_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_pdn;
   int unsigned t_pdn_dsm_x1024;
   int unsigned t_xsr_dsm_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG23_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned max_wr_sync;
   int unsigned max_rd_sync;
   int unsigned rd2wr_s;
   int unsigned bank_org;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG24_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned rda2pre;
   int unsigned wra2pre;
   int unsigned lpddr4_diff_bank_rwa2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG25_struct_t;

`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_ccd_r;
   int unsigned t_ccd_w;
   int unsigned t_ccd_r_s;
   int unsigned t_ccd_w_s;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG26_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mrr2mpc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG27_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_srx2srx;
   int unsigned t_cpded2srx;
   int unsigned t_cssr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG28_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ckact;
   int unsigned t_ckoff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG29_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mrr2rd;
   int unsigned mrr2wr;
   int unsigned mrr2mrw;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG30_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ccd_r_2;
   int unsigned t_ccd_w_2;
   int unsigned t_ccd_r_s_2;
   int unsigned t_ccd_w_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ras_min_2;
   int unsigned t_faw_2;
   int unsigned t_wr2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG1_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rc_2;
   int unsigned rd2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_2;
   int unsigned rd2wr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG3_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rd2wr_dpr_2;
   int unsigned t_rd2wr_dlr_2;
   int unsigned t_wr2rd_dpr_2;
   int unsigned t_wr2rd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG4_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rp_2;
   int unsigned t_rrd_2;
   int unsigned t_ccd_2;
   int unsigned t_rcd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG5_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_s_2;
   int unsigned t_rrd_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG6_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ppd_2;
   int unsigned t_ccd_w2_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG7_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr_2;
   int unsigned t_rrd_dlr_2;
   int unsigned t_faw_dlr_2;
   int unsigned t_rp_ca_parity_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG8_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_xs_x32_2;
   int unsigned t_xs_dll_x32_2;
   int unsigned t_xs_abort_x32_2;
   int unsigned t_xs_fast_x32_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG9_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG10_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mrr2mpc_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG11_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned t_rd2rd_gap_r0r1;
   int unsigned t_rd2rd_gap_r1r0;
   int unsigned t_wr2rd_gap_r0r1;
   int unsigned t_wr2rd_gap_r1r0;
   int unsigned t_rd2wr_gap_r0r1;
   int unsigned t_rd2wr_gap_r1r0;
   int unsigned t_wr2wr_gap_r0r1;
   int unsigned t_wr2wr_gap_r1r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL0_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r2;
   int unsigned t_rd2rd_gap_r2r0;
   int unsigned t_wr2rd_gap_r0r2;
   int unsigned t_wr2rd_gap_r2r0;
   int unsigned t_rd2wr_gap_r0r2;
   int unsigned t_rd2wr_gap_r2r0;
   int unsigned t_wr2wr_gap_r0r2;
   int unsigned t_wr2wr_gap_r2r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL1_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r3;
   int unsigned t_rd2rd_gap_r3r0;
   int unsigned t_wr2rd_gap_r0r3;
   int unsigned t_wr2rd_gap_r3r0;
   int unsigned t_rd2wr_gap_r0r3;
   int unsigned t_rd2wr_gap_r3r0;
   int unsigned t_wr2wr_gap_r0r3;
   int unsigned t_wr2wr_gap_r3r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r2;
   int unsigned t_rd2rd_gap_r2r1;
   int unsigned t_wr2rd_gap_r1r2;
   int unsigned t_wr2rd_gap_r2r1;
   int unsigned t_rd2wr_gap_r1r2;
   int unsigned t_rd2wr_gap_r2r1;
   int unsigned t_wr2wr_gap_r1r2;
   int unsigned t_wr2wr_gap_r2r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r3;
   int unsigned t_rd2rd_gap_r3r1;
   int unsigned t_wr2rd_gap_r1r3;
   int unsigned t_wr2rd_gap_r3r1;
   int unsigned t_rd2wr_gap_r1r3;
   int unsigned t_rd2wr_gap_r3r1;
   int unsigned t_wr2wr_gap_r1r3;
   int unsigned t_wr2wr_gap_r3r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r2r3;
   int unsigned t_rd2rd_gap_r3r2;
   int unsigned t_wr2rd_gap_r2r3;
   int unsigned t_wr2rd_gap_r3r2;
   int unsigned t_rd2wr_gap_r2r3;
   int unsigned t_rd2wr_gap_r3r2;
   int unsigned t_wr2wr_gap_r2r3;
   int unsigned t_wr2wr_gap_r3r2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_ras_min_mram;
   int unsigned t_faw_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_MRAMTMG0_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rc_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_MRAMTMG1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rp_mram;
   int unsigned t_rrd_mram;
   int unsigned t_rcd_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_MRAMTMG2_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rrd_s_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_MRAMTMG3_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned emr;
   int unsigned mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_INITMR0_struct_t;

typedef struct  {
   int unsigned emr3;
   int unsigned emr2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_INITMR1_struct_t;

typedef struct  {
   int unsigned mr5;
   int unsigned mr4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_INITMR2_struct_t;

typedef struct  {
   int unsigned mr6;
   int unsigned mr22;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_INITMR3_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrlat;
   int unsigned dfi_tphy_wrdata;
   int unsigned dfi_t_rddata_en;
   int unsigned dfi_t_ctrl_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_dram_clk_enable;
   int unsigned dfi_t_dram_clk_disable;
   int unsigned dfi_t_wrdata_delay;
   int unsigned dfi_t_parin_lat;
   int unsigned dfi_t_cmd_lat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG1_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrcslat;
   int unsigned dfi_tphy_rdcslat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG2_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned dfi_t_geardown_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG3_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_dis;
   int unsigned dfi_twck_en_fs;
   int unsigned dfi_twck_en_wr;
   int unsigned dfi_twck_en_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG4_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_toggle_post;
   int unsigned dfi_twck_toggle_cs;
   int unsigned dfi_twck_toggle;
   int unsigned dfi_twck_fast_toggle;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG5_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_2n_mode_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG7_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dfi_lp_wakeup_pd;
   int unsigned dfi_lp_wakeup_sr;
   int unsigned dfi_lp_wakeup_dsm;
   int unsigned dfi_lp_wakeup_mpsm;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFILPTMG0_struct_t;

typedef struct  {
   int unsigned dfi_lp_wakeup_data;
   int unsigned dfi_tlp_resp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFILPTMG1_struct_t;

typedef struct  {
   int unsigned dfi_t_ctrlup_min;
   int unsigned dfi_t_ctrlup_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFIUPDTMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_ctrlupd_interval_max_x1024;
   int unsigned dfi_t_ctrlupd_interval_min_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFIUPDTMG1_struct_t;

typedef struct  {
   int unsigned dfi_t_ctrlmsg_resp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFIMSGTMG0_struct_t;

typedef struct  {
   int unsigned t_refi_x1_x32;
   int unsigned refresh_to_x1_x32;
   int unsigned refresh_margin;
   int unsigned t_refi_x1_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rfc_min;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG1_struct_t;

`ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr;
   int unsigned t_pbr2pbr;
   int unsigned t_pbr2act;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG2_struct_t;

`endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rfcsb;
   int unsigned t_refsbrd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned refresh_timer0_start_value_x32;
   int unsigned refresh_timer1_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG4_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned refresh_timer2_start_value_x32;
   int unsigned refresh_timer3_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned refresh_timer_lr_offset_x32;
   int unsigned refresh_timer_rank_offset_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG6_struct_t;

`endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr;
   int unsigned t_refsbrd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG7_struct_t;

`endif //UMCTL2_CID_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HET_RANK_RFC
typedef struct  {
   int unsigned t_rfc_min_het;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG8_struct_t;

`endif //UMCTL2_HET_RANK_RFC
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfc_min_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET2TMG1_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfcsb_2;
   int unsigned t_refsbrd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr_2;
   int unsigned t_refsbrd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET2TMG3_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
typedef struct  {
   int unsigned t_zq_long_nop;
   int unsigned t_zq_short_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_ZQSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_zq_short_interval_x1024;
   int unsigned t_zq_reset_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_ZQSET1TMG1_struct_t;

`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_zq_long_nop_2;
   int unsigned t_zq_short_nop_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_ZQSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_1;
   int unsigned ctrl_word_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RCDINIT1_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_3;
   int unsigned ctrl_word_4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RCDINIT2_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_5;
   int unsigned ctrl_word_6;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RCDINIT3_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_7;
   int unsigned ctrl_word_8;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RCDINIT4_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_enable;
   int unsigned dqsosc_interval_unit;
   int unsigned dqsosc_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DQSOSCCTL0_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mr4_read_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DERATEINT_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rrd;
   int unsigned derated_t_rp;
   int unsigned derated_t_ras_min;
   int unsigned derated_t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DERATEVAL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DERATEVAL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned hw_lp_idle_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_HWLPTMG0_struct_t;

typedef struct  {
   int unsigned pageclose_timer;
   int unsigned rdwr_idle_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_SCHEDTMG0_struct_t;

typedef struct  {
   int unsigned hpr_max_starve;
   int unsigned hpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_PERFHPR1_struct_t;

typedef struct  {
   int unsigned lpr_max_starve;
   int unsigned lpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_PERFLPR1_struct_t;

typedef struct  {
   int unsigned w_max_starve;
   int unsigned w_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_PERFWR1_struct_t;

typedef struct  {
   int unsigned frequency_ratio;
   int unsigned dfi_freq_fsp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_TMGCFG_struct_t;

`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned diff_rank_rd_gap;
   int unsigned diff_rank_wr_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANKTMG0_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned wr2rd_dr;
   int unsigned rd2wr_dr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANKTMG1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_to_x32;
   int unsigned selfref_to_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_PWRTMG_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned rd_odt_delay;
   int unsigned rd_odt_hold;
   int unsigned wr_odt_delay;
   int unsigned wr_odt_hold;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_ODTCFG_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct  {
   int unsigned retry_fifo_max_hold_timer_x4;
   int unsigned t_crc_alert_pw_max;
   int unsigned t_par_alert_pw_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_CRCPARTMG0_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_csalt;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH0_CRCPARTMG1_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ras_min;
   int unsigned t_ras_max;
   int unsigned t_faw;
   int unsigned wr2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rc;
   int unsigned rd2pre;
   int unsigned t_xp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG1_struct_t;

typedef struct  {
   int unsigned wr2rd;
   int unsigned rd2wr;
   int unsigned read_latency;
   int unsigned write_latency;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG2_struct_t;

typedef struct  {
   int unsigned wr2mr;
   int unsigned rd2mr;
   int unsigned t_mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG3_struct_t;

typedef struct  {
   int unsigned t_rp;
   int unsigned t_rrd;
   int unsigned t_ccd;
   int unsigned t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG4_struct_t;

typedef struct  {
   int unsigned t_cke;
   int unsigned t_ckesr;
   int unsigned t_cksre;
   int unsigned t_cksrx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG5_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_ckcsx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG6_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_csh;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG7_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xs_x32;
   int unsigned t_xs_dll_x32;
   int unsigned t_xs_abort_x32;
   int unsigned t_xs_fast_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG8_struct_t;

typedef struct  {
   int unsigned wr2rd_s;
   int unsigned t_rrd_s;
   int unsigned t_ccd_s;
   int unsigned ddr4_wr_preamble;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG9_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned t_gear_hold;
   int unsigned t_gear_setup;
   int unsigned t_cmd_gear;
   int unsigned t_sync_gear;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG10_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_ckmpe;
   int unsigned t_mpx_s;
   int unsigned t_mpx_lh;
   int unsigned post_mpsm_gap_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG11_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned t_mrd_pda;
   int unsigned t_cmdcke;
   int unsigned t_wr_mpr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG12_struct_t;

typedef struct  {
   int unsigned t_ppd;
   int unsigned t_ccd_w2;
   int unsigned t_ccd_mw;
   int unsigned odtloff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG13_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xsr;
   int unsigned t_osco;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG14_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_stab_x32;
   int unsigned en_hwffc_t_stab;
   int unsigned en_dfi_lp_t_stab;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG15_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr;
   int unsigned t_rrd_dlr;
   int unsigned t_faw_dlr;
   int unsigned t_rp_ca_parity;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG16_struct_t;

`endif //UMCTL2_CID_EN
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned t_vrcg_disable;
   int unsigned t_vrcg_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG17_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mpdpxact;
   int unsigned t_mpsmx;
   int unsigned t_pd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG18_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_pda_h;
   int unsigned t_pda_s;
   int unsigned t_pda_dqs_delay;
   int unsigned t_pda_delay;
   int unsigned t_pda_latch;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG19_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_csl_srexit;
   int unsigned t_csh_srexit;
   int unsigned t_casrx;
   int unsigned t_cpded;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_osco_ddr5;
   int unsigned t_vrefca_cs;
   int unsigned t_mpc_hold;
   int unsigned t_mpc_setup;
   int unsigned t_mpc_cs;
   int unsigned t_csl;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rd2wr_dpr;
   int unsigned t_rd2wr_dlr;
   int unsigned t_wr2rd_dpr;
   int unsigned t_wr2rd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG22_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_pdn;
   int unsigned t_pdn_dsm_x1024;
   int unsigned t_xsr_dsm_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG23_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned max_wr_sync;
   int unsigned max_rd_sync;
   int unsigned rd2wr_s;
   int unsigned bank_org;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG24_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned rda2pre;
   int unsigned wra2pre;
   int unsigned lpddr4_diff_bank_rwa2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG25_struct_t;

`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_ccd_r;
   int unsigned t_ccd_w;
   int unsigned t_ccd_r_s;
   int unsigned t_ccd_w_s;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG26_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mrr2mpc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG27_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_srx2srx;
   int unsigned t_cpded2srx;
   int unsigned t_cssr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG28_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ckact;
   int unsigned t_ckoff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG29_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mrr2rd;
   int unsigned mrr2wr;
   int unsigned mrr2mrw;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG30_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ccd_r_2;
   int unsigned t_ccd_w_2;
   int unsigned t_ccd_r_s_2;
   int unsigned t_ccd_w_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ras_min_2;
   int unsigned t_faw_2;
   int unsigned t_wr2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG1_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rc_2;
   int unsigned rd2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_2;
   int unsigned rd2wr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG3_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rd2wr_dpr_2;
   int unsigned t_rd2wr_dlr_2;
   int unsigned t_wr2rd_dpr_2;
   int unsigned t_wr2rd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG4_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rp_2;
   int unsigned t_rrd_2;
   int unsigned t_ccd_2;
   int unsigned t_rcd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG5_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_s_2;
   int unsigned t_rrd_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG6_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ppd_2;
   int unsigned t_ccd_w2_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG7_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr_2;
   int unsigned t_rrd_dlr_2;
   int unsigned t_faw_dlr_2;
   int unsigned t_rp_ca_parity_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG8_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_xs_x32_2;
   int unsigned t_xs_dll_x32_2;
   int unsigned t_xs_abort_x32_2;
   int unsigned t_xs_fast_x32_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG9_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG10_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mrr2mpc_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG11_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned t_rd2rd_gap_r0r1;
   int unsigned t_rd2rd_gap_r1r0;
   int unsigned t_wr2rd_gap_r0r1;
   int unsigned t_wr2rd_gap_r1r0;
   int unsigned t_rd2wr_gap_r0r1;
   int unsigned t_rd2wr_gap_r1r0;
   int unsigned t_wr2wr_gap_r0r1;
   int unsigned t_wr2wr_gap_r1r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL0_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r2;
   int unsigned t_rd2rd_gap_r2r0;
   int unsigned t_wr2rd_gap_r0r2;
   int unsigned t_wr2rd_gap_r2r0;
   int unsigned t_rd2wr_gap_r0r2;
   int unsigned t_rd2wr_gap_r2r0;
   int unsigned t_wr2wr_gap_r0r2;
   int unsigned t_wr2wr_gap_r2r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL1_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r3;
   int unsigned t_rd2rd_gap_r3r0;
   int unsigned t_wr2rd_gap_r0r3;
   int unsigned t_wr2rd_gap_r3r0;
   int unsigned t_rd2wr_gap_r0r3;
   int unsigned t_rd2wr_gap_r3r0;
   int unsigned t_wr2wr_gap_r0r3;
   int unsigned t_wr2wr_gap_r3r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r2;
   int unsigned t_rd2rd_gap_r2r1;
   int unsigned t_wr2rd_gap_r1r2;
   int unsigned t_wr2rd_gap_r2r1;
   int unsigned t_rd2wr_gap_r1r2;
   int unsigned t_rd2wr_gap_r2r1;
   int unsigned t_wr2wr_gap_r1r2;
   int unsigned t_wr2wr_gap_r2r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r3;
   int unsigned t_rd2rd_gap_r3r1;
   int unsigned t_wr2rd_gap_r1r3;
   int unsigned t_wr2rd_gap_r3r1;
   int unsigned t_rd2wr_gap_r1r3;
   int unsigned t_rd2wr_gap_r3r1;
   int unsigned t_wr2wr_gap_r1r3;
   int unsigned t_wr2wr_gap_r3r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r2r3;
   int unsigned t_rd2rd_gap_r3r2;
   int unsigned t_wr2rd_gap_r2r3;
   int unsigned t_wr2rd_gap_r3r2;
   int unsigned t_rd2wr_gap_r2r3;
   int unsigned t_rd2wr_gap_r3r2;
   int unsigned t_wr2wr_gap_r2r3;
   int unsigned t_wr2wr_gap_r3r2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_ras_min_mram;
   int unsigned t_faw_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_MRAMTMG0_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rc_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_MRAMTMG1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rp_mram;
   int unsigned t_rrd_mram;
   int unsigned t_rcd_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_MRAMTMG2_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rrd_s_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_MRAMTMG3_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned emr;
   int unsigned mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_INITMR0_struct_t;

typedef struct  {
   int unsigned emr3;
   int unsigned emr2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_INITMR1_struct_t;

typedef struct  {
   int unsigned mr5;
   int unsigned mr4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_INITMR2_struct_t;

typedef struct  {
   int unsigned mr6;
   int unsigned mr22;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_INITMR3_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrlat;
   int unsigned dfi_tphy_wrdata;
   int unsigned dfi_t_rddata_en;
   int unsigned dfi_t_ctrl_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_dram_clk_enable;
   int unsigned dfi_t_dram_clk_disable;
   int unsigned dfi_t_wrdata_delay;
   int unsigned dfi_t_parin_lat;
   int unsigned dfi_t_cmd_lat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG1_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrcslat;
   int unsigned dfi_tphy_rdcslat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG2_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned dfi_t_geardown_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG3_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_dis;
   int unsigned dfi_twck_en_fs;
   int unsigned dfi_twck_en_wr;
   int unsigned dfi_twck_en_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG4_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_toggle_post;
   int unsigned dfi_twck_toggle_cs;
   int unsigned dfi_twck_toggle;
   int unsigned dfi_twck_fast_toggle;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG5_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_2n_mode_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG7_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dfi_lp_wakeup_pd;
   int unsigned dfi_lp_wakeup_sr;
   int unsigned dfi_lp_wakeup_dsm;
   int unsigned dfi_lp_wakeup_mpsm;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFILPTMG0_struct_t;

typedef struct  {
   int unsigned dfi_lp_wakeup_data;
   int unsigned dfi_tlp_resp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFILPTMG1_struct_t;

typedef struct  {
   int unsigned dfi_t_ctrlup_min;
   int unsigned dfi_t_ctrlup_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFIUPDTMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_ctrlupd_interval_max_x1024;
   int unsigned dfi_t_ctrlupd_interval_min_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFIUPDTMG1_struct_t;

typedef struct  {
   int unsigned dfi_t_ctrlmsg_resp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFIMSGTMG0_struct_t;

typedef struct  {
   int unsigned t_refi_x1_x32;
   int unsigned refresh_to_x1_x32;
   int unsigned refresh_margin;
   int unsigned t_refi_x1_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rfc_min;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG1_struct_t;

`ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr;
   int unsigned t_pbr2pbr;
   int unsigned t_pbr2act;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG2_struct_t;

`endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rfcsb;
   int unsigned t_refsbrd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned refresh_timer0_start_value_x32;
   int unsigned refresh_timer1_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG4_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned refresh_timer2_start_value_x32;
   int unsigned refresh_timer3_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned refresh_timer_lr_offset_x32;
   int unsigned refresh_timer_rank_offset_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG6_struct_t;

`endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr;
   int unsigned t_refsbrd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG7_struct_t;

`endif //UMCTL2_CID_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HET_RANK_RFC
typedef struct  {
   int unsigned t_rfc_min_het;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG8_struct_t;

`endif //UMCTL2_HET_RANK_RFC
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfc_min_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET2TMG1_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfcsb_2;
   int unsigned t_refsbrd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr_2;
   int unsigned t_refsbrd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET2TMG3_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
typedef struct  {
   int unsigned t_zq_long_nop;
   int unsigned t_zq_short_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_ZQSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_zq_short_interval_x1024;
   int unsigned t_zq_reset_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_ZQSET1TMG1_struct_t;

`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_zq_long_nop_2;
   int unsigned t_zq_short_nop_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_ZQSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_1;
   int unsigned ctrl_word_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RCDINIT1_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_3;
   int unsigned ctrl_word_4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RCDINIT2_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_5;
   int unsigned ctrl_word_6;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RCDINIT3_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_7;
   int unsigned ctrl_word_8;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RCDINIT4_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_enable;
   int unsigned dqsosc_interval_unit;
   int unsigned dqsosc_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DQSOSCCTL0_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mr4_read_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DERATEINT_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rrd;
   int unsigned derated_t_rp;
   int unsigned derated_t_ras_min;
   int unsigned derated_t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DERATEVAL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DERATEVAL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned hw_lp_idle_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_HWLPTMG0_struct_t;

typedef struct  {
   int unsigned pageclose_timer;
   int unsigned rdwr_idle_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_SCHEDTMG0_struct_t;

typedef struct  {
   int unsigned hpr_max_starve;
   int unsigned hpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_PERFHPR1_struct_t;

typedef struct  {
   int unsigned lpr_max_starve;
   int unsigned lpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_PERFLPR1_struct_t;

typedef struct  {
   int unsigned w_max_starve;
   int unsigned w_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_PERFWR1_struct_t;

`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned diff_rank_rd_gap;
   int unsigned diff_rank_wr_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANKTMG0_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned wr2rd_dr;
   int unsigned rd2wr_dr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANKTMG1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_to_x32;
   int unsigned selfref_to_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_PWRTMG_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned rd_odt_delay;
   int unsigned rd_odt_hold;
   int unsigned wr_odt_delay;
   int unsigned wr_odt_hold;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_ODTCFG_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct  {
   int unsigned retry_fifo_max_hold_timer_x4;
   int unsigned t_crc_alert_pw_max;
   int unsigned t_par_alert_pw_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_CRCPARTMG0_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_csalt;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ0_CH1_CRCPARTMG1_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ras_min;
   int unsigned t_ras_max;
   int unsigned t_faw;
   int unsigned wr2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rc;
   int unsigned rd2pre;
   int unsigned t_xp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG1_struct_t;

typedef struct  {
   int unsigned wr2rd;
   int unsigned rd2wr;
   int unsigned read_latency;
   int unsigned write_latency;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG2_struct_t;

typedef struct  {
   int unsigned wr2mr;
   int unsigned rd2mr;
   int unsigned t_mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG3_struct_t;

typedef struct  {
   int unsigned t_rp;
   int unsigned t_rrd;
   int unsigned t_ccd;
   int unsigned t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG4_struct_t;

typedef struct  {
   int unsigned t_cke;
   int unsigned t_ckesr;
   int unsigned t_cksre;
   int unsigned t_cksrx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG5_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_ckcsx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG6_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_csh;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG7_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xs_x32;
   int unsigned t_xs_dll_x32;
   int unsigned t_xs_abort_x32;
   int unsigned t_xs_fast_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG8_struct_t;

typedef struct  {
   int unsigned wr2rd_s;
   int unsigned t_rrd_s;
   int unsigned t_ccd_s;
   int unsigned ddr4_wr_preamble;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG9_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned t_gear_hold;
   int unsigned t_gear_setup;
   int unsigned t_cmd_gear;
   int unsigned t_sync_gear;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG10_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_ckmpe;
   int unsigned t_mpx_s;
   int unsigned t_mpx_lh;
   int unsigned post_mpsm_gap_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG11_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned t_mrd_pda;
   int unsigned t_cmdcke;
   int unsigned t_wr_mpr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG12_struct_t;

typedef struct  {
   int unsigned t_ppd;
   int unsigned t_ccd_w2;
   int unsigned t_ccd_mw;
   int unsigned odtloff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG13_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xsr;
   int unsigned t_osco;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG14_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_stab_x32;
   int unsigned en_hwffc_t_stab;
   int unsigned en_dfi_lp_t_stab;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG15_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr;
   int unsigned t_rrd_dlr;
   int unsigned t_faw_dlr;
   int unsigned t_rp_ca_parity;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG16_struct_t;

`endif //UMCTL2_CID_EN
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned t_vrcg_disable;
   int unsigned t_vrcg_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG17_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mpdpxact;
   int unsigned t_mpsmx;
   int unsigned t_pd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG18_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_pda_h;
   int unsigned t_pda_s;
   int unsigned t_pda_dqs_delay;
   int unsigned t_pda_delay;
   int unsigned t_pda_latch;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG19_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_csl_srexit;
   int unsigned t_csh_srexit;
   int unsigned t_casrx;
   int unsigned t_cpded;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_osco_ddr5;
   int unsigned t_vrefca_cs;
   int unsigned t_mpc_hold;
   int unsigned t_mpc_setup;
   int unsigned t_mpc_cs;
   int unsigned t_csl;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rd2wr_dpr;
   int unsigned t_rd2wr_dlr;
   int unsigned t_wr2rd_dpr;
   int unsigned t_wr2rd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG22_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_pdn;
   int unsigned t_pdn_dsm_x1024;
   int unsigned t_xsr_dsm_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG23_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned max_wr_sync;
   int unsigned max_rd_sync;
   int unsigned rd2wr_s;
   int unsigned bank_org;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG24_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned rda2pre;
   int unsigned wra2pre;
   int unsigned lpddr4_diff_bank_rwa2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG25_struct_t;

`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_ccd_r;
   int unsigned t_ccd_w;
   int unsigned t_ccd_r_s;
   int unsigned t_ccd_w_s;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG26_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mrr2mpc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG27_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_srx2srx;
   int unsigned t_cpded2srx;
   int unsigned t_cssr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG28_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ckact;
   int unsigned t_ckoff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG29_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mrr2rd;
   int unsigned mrr2wr;
   int unsigned mrr2mrw;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG30_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ccd_r_2;
   int unsigned t_ccd_w_2;
   int unsigned t_ccd_r_s_2;
   int unsigned t_ccd_w_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ras_min_2;
   int unsigned t_faw_2;
   int unsigned t_wr2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG1_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rc_2;
   int unsigned rd2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_2;
   int unsigned rd2wr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG3_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rd2wr_dpr_2;
   int unsigned t_rd2wr_dlr_2;
   int unsigned t_wr2rd_dpr_2;
   int unsigned t_wr2rd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG4_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rp_2;
   int unsigned t_rrd_2;
   int unsigned t_ccd_2;
   int unsigned t_rcd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG5_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_s_2;
   int unsigned t_rrd_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG6_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ppd_2;
   int unsigned t_ccd_w2_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG7_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr_2;
   int unsigned t_rrd_dlr_2;
   int unsigned t_faw_dlr_2;
   int unsigned t_rp_ca_parity_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG8_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_xs_x32_2;
   int unsigned t_xs_dll_x32_2;
   int unsigned t_xs_abort_x32_2;
   int unsigned t_xs_fast_x32_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG9_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG10_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mrr2mpc_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG11_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned t_rd2rd_gap_r0r1;
   int unsigned t_rd2rd_gap_r1r0;
   int unsigned t_wr2rd_gap_r0r1;
   int unsigned t_wr2rd_gap_r1r0;
   int unsigned t_rd2wr_gap_r0r1;
   int unsigned t_rd2wr_gap_r1r0;
   int unsigned t_wr2wr_gap_r0r1;
   int unsigned t_wr2wr_gap_r1r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL0_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r2;
   int unsigned t_rd2rd_gap_r2r0;
   int unsigned t_wr2rd_gap_r0r2;
   int unsigned t_wr2rd_gap_r2r0;
   int unsigned t_rd2wr_gap_r0r2;
   int unsigned t_rd2wr_gap_r2r0;
   int unsigned t_wr2wr_gap_r0r2;
   int unsigned t_wr2wr_gap_r2r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL1_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r3;
   int unsigned t_rd2rd_gap_r3r0;
   int unsigned t_wr2rd_gap_r0r3;
   int unsigned t_wr2rd_gap_r3r0;
   int unsigned t_rd2wr_gap_r0r3;
   int unsigned t_rd2wr_gap_r3r0;
   int unsigned t_wr2wr_gap_r0r3;
   int unsigned t_wr2wr_gap_r3r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r2;
   int unsigned t_rd2rd_gap_r2r1;
   int unsigned t_wr2rd_gap_r1r2;
   int unsigned t_wr2rd_gap_r2r1;
   int unsigned t_rd2wr_gap_r1r2;
   int unsigned t_rd2wr_gap_r2r1;
   int unsigned t_wr2wr_gap_r1r2;
   int unsigned t_wr2wr_gap_r2r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r3;
   int unsigned t_rd2rd_gap_r3r1;
   int unsigned t_wr2rd_gap_r1r3;
   int unsigned t_wr2rd_gap_r3r1;
   int unsigned t_rd2wr_gap_r1r3;
   int unsigned t_rd2wr_gap_r3r1;
   int unsigned t_wr2wr_gap_r1r3;
   int unsigned t_wr2wr_gap_r3r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r2r3;
   int unsigned t_rd2rd_gap_r3r2;
   int unsigned t_wr2rd_gap_r2r3;
   int unsigned t_wr2rd_gap_r3r2;
   int unsigned t_rd2wr_gap_r2r3;
   int unsigned t_rd2wr_gap_r3r2;
   int unsigned t_wr2wr_gap_r2r3;
   int unsigned t_wr2wr_gap_r3r2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_ras_min_mram;
   int unsigned t_faw_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_MRAMTMG0_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rc_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_MRAMTMG1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rp_mram;
   int unsigned t_rrd_mram;
   int unsigned t_rcd_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_MRAMTMG2_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rrd_s_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_MRAMTMG3_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned emr;
   int unsigned mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_INITMR0_struct_t;

typedef struct  {
   int unsigned emr3;
   int unsigned emr2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_INITMR1_struct_t;

typedef struct  {
   int unsigned mr5;
   int unsigned mr4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_INITMR2_struct_t;

typedef struct  {
   int unsigned mr6;
   int unsigned mr22;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_INITMR3_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrlat;
   int unsigned dfi_tphy_wrdata;
   int unsigned dfi_t_rddata_en;
   int unsigned dfi_t_ctrl_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_dram_clk_enable;
   int unsigned dfi_t_dram_clk_disable;
   int unsigned dfi_t_wrdata_delay;
   int unsigned dfi_t_parin_lat;
   int unsigned dfi_t_cmd_lat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG1_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrcslat;
   int unsigned dfi_tphy_rdcslat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG2_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned dfi_t_geardown_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG3_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_dis;
   int unsigned dfi_twck_en_fs;
   int unsigned dfi_twck_en_wr;
   int unsigned dfi_twck_en_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG4_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_toggle_post;
   int unsigned dfi_twck_toggle_cs;
   int unsigned dfi_twck_toggle;
   int unsigned dfi_twck_fast_toggle;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG5_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_2n_mode_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG7_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_ctrlupd_interval_max_x1024;
   int unsigned dfi_t_ctrlupd_interval_min_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFIUPDTMG1_struct_t;

typedef struct  {
   int unsigned t_refi_x1_x32;
   int unsigned refresh_to_x1_x32;
   int unsigned refresh_margin;
   int unsigned t_refi_x1_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rfc_min;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG1_struct_t;

`ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr;
   int unsigned t_pbr2pbr;
   int unsigned t_pbr2act;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG2_struct_t;

`endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rfcsb;
   int unsigned t_refsbrd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned refresh_timer0_start_value_x32;
   int unsigned refresh_timer1_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG4_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned refresh_timer2_start_value_x32;
   int unsigned refresh_timer3_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned refresh_timer_lr_offset_x32;
   int unsigned refresh_timer_rank_offset_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG6_struct_t;

`endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr;
   int unsigned t_refsbrd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG7_struct_t;

`endif //UMCTL2_CID_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HET_RANK_RFC
typedef struct  {
   int unsigned t_rfc_min_het;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG8_struct_t;

`endif //UMCTL2_HET_RANK_RFC
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfc_min_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET2TMG1_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfcsb_2;
   int unsigned t_refsbrd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr_2;
   int unsigned t_refsbrd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET2TMG3_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
typedef struct  {
   int unsigned t_zq_long_nop;
   int unsigned t_zq_short_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_ZQSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_zq_short_interval_x1024;
   int unsigned t_zq_reset_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_ZQSET1TMG1_struct_t;

`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_zq_long_nop_2;
   int unsigned t_zq_short_nop_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_ZQSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_1;
   int unsigned ctrl_word_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RCDINIT1_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_3;
   int unsigned ctrl_word_4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RCDINIT2_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_5;
   int unsigned ctrl_word_6;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RCDINIT3_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_7;
   int unsigned ctrl_word_8;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RCDINIT4_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_enable;
   int unsigned dqsosc_interval_unit;
   int unsigned dqsosc_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DQSOSCCTL0_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mr4_read_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DERATEINT_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rrd;
   int unsigned derated_t_rp;
   int unsigned derated_t_ras_min;
   int unsigned derated_t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DERATEVAL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DERATEVAL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned hw_lp_idle_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_HWLPTMG0_struct_t;

typedef struct  {
   int unsigned pageclose_timer;
   int unsigned rdwr_idle_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_SCHEDTMG0_struct_t;

typedef struct  {
   int unsigned hpr_max_starve;
   int unsigned hpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_PERFHPR1_struct_t;

typedef struct  {
   int unsigned lpr_max_starve;
   int unsigned lpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_PERFLPR1_struct_t;

typedef struct  {
   int unsigned w_max_starve;
   int unsigned w_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_PERFWR1_struct_t;

typedef struct  {
   int unsigned frequency_ratio;
   int unsigned dfi_freq_fsp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_TMGCFG_struct_t;

`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned diff_rank_rd_gap;
   int unsigned diff_rank_wr_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANKTMG0_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned wr2rd_dr;
   int unsigned rd2wr_dr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANKTMG1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_to_x32;
   int unsigned selfref_to_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_PWRTMG_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned rd_odt_delay;
   int unsigned rd_odt_hold;
   int unsigned wr_odt_delay;
   int unsigned wr_odt_hold;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_ODTCFG_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct  {
   int unsigned retry_fifo_max_hold_timer_x4;
   int unsigned t_crc_alert_pw_max;
   int unsigned t_par_alert_pw_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_CRCPARTMG0_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_csalt;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH0_CRCPARTMG1_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ras_min;
   int unsigned t_ras_max;
   int unsigned t_faw;
   int unsigned wr2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rc;
   int unsigned rd2pre;
   int unsigned t_xp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG1_struct_t;

typedef struct  {
   int unsigned wr2rd;
   int unsigned rd2wr;
   int unsigned read_latency;
   int unsigned write_latency;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG2_struct_t;

typedef struct  {
   int unsigned wr2mr;
   int unsigned rd2mr;
   int unsigned t_mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG3_struct_t;

typedef struct  {
   int unsigned t_rp;
   int unsigned t_rrd;
   int unsigned t_ccd;
   int unsigned t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG4_struct_t;

typedef struct  {
   int unsigned t_cke;
   int unsigned t_ckesr;
   int unsigned t_cksre;
   int unsigned t_cksrx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG5_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_ckcsx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG6_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_csh;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG7_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xs_x32;
   int unsigned t_xs_dll_x32;
   int unsigned t_xs_abort_x32;
   int unsigned t_xs_fast_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG8_struct_t;

typedef struct  {
   int unsigned wr2rd_s;
   int unsigned t_rrd_s;
   int unsigned t_ccd_s;
   int unsigned ddr4_wr_preamble;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG9_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned t_gear_hold;
   int unsigned t_gear_setup;
   int unsigned t_cmd_gear;
   int unsigned t_sync_gear;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG10_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_ckmpe;
   int unsigned t_mpx_s;
   int unsigned t_mpx_lh;
   int unsigned post_mpsm_gap_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG11_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned t_mrd_pda;
   int unsigned t_cmdcke;
   int unsigned t_wr_mpr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG12_struct_t;

typedef struct  {
   int unsigned t_ppd;
   int unsigned t_ccd_w2;
   int unsigned t_ccd_mw;
   int unsigned odtloff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG13_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xsr;
   int unsigned t_osco;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG14_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_stab_x32;
   int unsigned en_hwffc_t_stab;
   int unsigned en_dfi_lp_t_stab;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG15_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr;
   int unsigned t_rrd_dlr;
   int unsigned t_faw_dlr;
   int unsigned t_rp_ca_parity;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG16_struct_t;

`endif //UMCTL2_CID_EN
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned t_vrcg_disable;
   int unsigned t_vrcg_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG17_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mpdpxact;
   int unsigned t_mpsmx;
   int unsigned t_pd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG18_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_pda_h;
   int unsigned t_pda_s;
   int unsigned t_pda_dqs_delay;
   int unsigned t_pda_delay;
   int unsigned t_pda_latch;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG19_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_csl_srexit;
   int unsigned t_csh_srexit;
   int unsigned t_casrx;
   int unsigned t_cpded;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_osco_ddr5;
   int unsigned t_vrefca_cs;
   int unsigned t_mpc_hold;
   int unsigned t_mpc_setup;
   int unsigned t_mpc_cs;
   int unsigned t_csl;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rd2wr_dpr;
   int unsigned t_rd2wr_dlr;
   int unsigned t_wr2rd_dpr;
   int unsigned t_wr2rd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG22_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_pdn;
   int unsigned t_pdn_dsm_x1024;
   int unsigned t_xsr_dsm_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG23_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned max_wr_sync;
   int unsigned max_rd_sync;
   int unsigned rd2wr_s;
   int unsigned bank_org;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG24_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned rda2pre;
   int unsigned wra2pre;
   int unsigned lpddr4_diff_bank_rwa2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG25_struct_t;

`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_ccd_r;
   int unsigned t_ccd_w;
   int unsigned t_ccd_r_s;
   int unsigned t_ccd_w_s;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG26_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mrr2mpc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG27_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_srx2srx;
   int unsigned t_cpded2srx;
   int unsigned t_cssr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG28_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ckact;
   int unsigned t_ckoff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG29_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mrr2rd;
   int unsigned mrr2wr;
   int unsigned mrr2mrw;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG30_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ccd_r_2;
   int unsigned t_ccd_w_2;
   int unsigned t_ccd_r_s_2;
   int unsigned t_ccd_w_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ras_min_2;
   int unsigned t_faw_2;
   int unsigned t_wr2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG1_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rc_2;
   int unsigned rd2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_2;
   int unsigned rd2wr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG3_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rd2wr_dpr_2;
   int unsigned t_rd2wr_dlr_2;
   int unsigned t_wr2rd_dpr_2;
   int unsigned t_wr2rd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG4_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rp_2;
   int unsigned t_rrd_2;
   int unsigned t_ccd_2;
   int unsigned t_rcd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG5_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_s_2;
   int unsigned t_rrd_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG6_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ppd_2;
   int unsigned t_ccd_w2_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG7_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr_2;
   int unsigned t_rrd_dlr_2;
   int unsigned t_faw_dlr_2;
   int unsigned t_rp_ca_parity_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG8_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_xs_x32_2;
   int unsigned t_xs_dll_x32_2;
   int unsigned t_xs_abort_x32_2;
   int unsigned t_xs_fast_x32_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG9_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG10_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mrr2mpc_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG11_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned t_rd2rd_gap_r0r1;
   int unsigned t_rd2rd_gap_r1r0;
   int unsigned t_wr2rd_gap_r0r1;
   int unsigned t_wr2rd_gap_r1r0;
   int unsigned t_rd2wr_gap_r0r1;
   int unsigned t_rd2wr_gap_r1r0;
   int unsigned t_wr2wr_gap_r0r1;
   int unsigned t_wr2wr_gap_r1r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL0_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r2;
   int unsigned t_rd2rd_gap_r2r0;
   int unsigned t_wr2rd_gap_r0r2;
   int unsigned t_wr2rd_gap_r2r0;
   int unsigned t_rd2wr_gap_r0r2;
   int unsigned t_rd2wr_gap_r2r0;
   int unsigned t_wr2wr_gap_r0r2;
   int unsigned t_wr2wr_gap_r2r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL1_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r3;
   int unsigned t_rd2rd_gap_r3r0;
   int unsigned t_wr2rd_gap_r0r3;
   int unsigned t_wr2rd_gap_r3r0;
   int unsigned t_rd2wr_gap_r0r3;
   int unsigned t_rd2wr_gap_r3r0;
   int unsigned t_wr2wr_gap_r0r3;
   int unsigned t_wr2wr_gap_r3r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r2;
   int unsigned t_rd2rd_gap_r2r1;
   int unsigned t_wr2rd_gap_r1r2;
   int unsigned t_wr2rd_gap_r2r1;
   int unsigned t_rd2wr_gap_r1r2;
   int unsigned t_rd2wr_gap_r2r1;
   int unsigned t_wr2wr_gap_r1r2;
   int unsigned t_wr2wr_gap_r2r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r3;
   int unsigned t_rd2rd_gap_r3r1;
   int unsigned t_wr2rd_gap_r1r3;
   int unsigned t_wr2rd_gap_r3r1;
   int unsigned t_rd2wr_gap_r1r3;
   int unsigned t_rd2wr_gap_r3r1;
   int unsigned t_wr2wr_gap_r1r3;
   int unsigned t_wr2wr_gap_r3r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r2r3;
   int unsigned t_rd2rd_gap_r3r2;
   int unsigned t_wr2rd_gap_r2r3;
   int unsigned t_wr2rd_gap_r3r2;
   int unsigned t_rd2wr_gap_r2r3;
   int unsigned t_rd2wr_gap_r3r2;
   int unsigned t_wr2wr_gap_r2r3;
   int unsigned t_wr2wr_gap_r3r2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_ras_min_mram;
   int unsigned t_faw_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_MRAMTMG0_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rc_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_MRAMTMG1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rp_mram;
   int unsigned t_rrd_mram;
   int unsigned t_rcd_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_MRAMTMG2_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rrd_s_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_MRAMTMG3_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned emr;
   int unsigned mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_INITMR0_struct_t;

typedef struct  {
   int unsigned emr3;
   int unsigned emr2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_INITMR1_struct_t;

typedef struct  {
   int unsigned mr5;
   int unsigned mr4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_INITMR2_struct_t;

typedef struct  {
   int unsigned mr6;
   int unsigned mr22;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_INITMR3_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrlat;
   int unsigned dfi_tphy_wrdata;
   int unsigned dfi_t_rddata_en;
   int unsigned dfi_t_ctrl_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_dram_clk_enable;
   int unsigned dfi_t_dram_clk_disable;
   int unsigned dfi_t_wrdata_delay;
   int unsigned dfi_t_parin_lat;
   int unsigned dfi_t_cmd_lat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG1_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrcslat;
   int unsigned dfi_tphy_rdcslat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG2_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned dfi_t_geardown_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG3_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_dis;
   int unsigned dfi_twck_en_fs;
   int unsigned dfi_twck_en_wr;
   int unsigned dfi_twck_en_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG4_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_toggle_post;
   int unsigned dfi_twck_toggle_cs;
   int unsigned dfi_twck_toggle;
   int unsigned dfi_twck_fast_toggle;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG5_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_2n_mode_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG7_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_ctrlupd_interval_max_x1024;
   int unsigned dfi_t_ctrlupd_interval_min_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFIUPDTMG1_struct_t;

typedef struct  {
   int unsigned t_refi_x1_x32;
   int unsigned refresh_to_x1_x32;
   int unsigned refresh_margin;
   int unsigned t_refi_x1_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rfc_min;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG1_struct_t;

`ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr;
   int unsigned t_pbr2pbr;
   int unsigned t_pbr2act;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG2_struct_t;

`endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rfcsb;
   int unsigned t_refsbrd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned refresh_timer0_start_value_x32;
   int unsigned refresh_timer1_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG4_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned refresh_timer2_start_value_x32;
   int unsigned refresh_timer3_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned refresh_timer_lr_offset_x32;
   int unsigned refresh_timer_rank_offset_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG6_struct_t;

`endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr;
   int unsigned t_refsbrd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG7_struct_t;

`endif //UMCTL2_CID_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HET_RANK_RFC
typedef struct  {
   int unsigned t_rfc_min_het;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG8_struct_t;

`endif //UMCTL2_HET_RANK_RFC
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfc_min_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET2TMG1_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfcsb_2;
   int unsigned t_refsbrd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr_2;
   int unsigned t_refsbrd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET2TMG3_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
typedef struct  {
   int unsigned t_zq_long_nop;
   int unsigned t_zq_short_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_ZQSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_zq_short_interval_x1024;
   int unsigned t_zq_reset_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_ZQSET1TMG1_struct_t;

`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_zq_long_nop_2;
   int unsigned t_zq_short_nop_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_ZQSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_1;
   int unsigned ctrl_word_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RCDINIT1_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_3;
   int unsigned ctrl_word_4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RCDINIT2_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_5;
   int unsigned ctrl_word_6;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RCDINIT3_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_7;
   int unsigned ctrl_word_8;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RCDINIT4_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_enable;
   int unsigned dqsosc_interval_unit;
   int unsigned dqsosc_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DQSOSCCTL0_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mr4_read_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DERATEINT_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rrd;
   int unsigned derated_t_rp;
   int unsigned derated_t_ras_min;
   int unsigned derated_t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DERATEVAL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DERATEVAL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned hw_lp_idle_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_HWLPTMG0_struct_t;

typedef struct  {
   int unsigned pageclose_timer;
   int unsigned rdwr_idle_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_SCHEDTMG0_struct_t;

typedef struct  {
   int unsigned hpr_max_starve;
   int unsigned hpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_PERFHPR1_struct_t;

typedef struct  {
   int unsigned lpr_max_starve;
   int unsigned lpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_PERFLPR1_struct_t;

typedef struct  {
   int unsigned w_max_starve;
   int unsigned w_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_PERFWR1_struct_t;

`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned diff_rank_rd_gap;
   int unsigned diff_rank_wr_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANKTMG0_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned wr2rd_dr;
   int unsigned rd2wr_dr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANKTMG1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_to_x32;
   int unsigned selfref_to_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_PWRTMG_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned rd_odt_delay;
   int unsigned rd_odt_hold;
   int unsigned wr_odt_delay;
   int unsigned wr_odt_hold;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_ODTCFG_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct  {
   int unsigned retry_fifo_max_hold_timer_x4;
   int unsigned t_crc_alert_pw_max;
   int unsigned t_par_alert_pw_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_CRCPARTMG0_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_csalt;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ1_CH1_CRCPARTMG1_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ras_min;
   int unsigned t_ras_max;
   int unsigned t_faw;
   int unsigned wr2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rc;
   int unsigned rd2pre;
   int unsigned t_xp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG1_struct_t;

typedef struct  {
   int unsigned wr2rd;
   int unsigned rd2wr;
   int unsigned read_latency;
   int unsigned write_latency;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG2_struct_t;

typedef struct  {
   int unsigned wr2mr;
   int unsigned rd2mr;
   int unsigned t_mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG3_struct_t;

typedef struct  {
   int unsigned t_rp;
   int unsigned t_rrd;
   int unsigned t_ccd;
   int unsigned t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG4_struct_t;

typedef struct  {
   int unsigned t_cke;
   int unsigned t_ckesr;
   int unsigned t_cksre;
   int unsigned t_cksrx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG5_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_ckcsx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG6_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_csh;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG7_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xs_x32;
   int unsigned t_xs_dll_x32;
   int unsigned t_xs_abort_x32;
   int unsigned t_xs_fast_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG8_struct_t;

typedef struct  {
   int unsigned wr2rd_s;
   int unsigned t_rrd_s;
   int unsigned t_ccd_s;
   int unsigned ddr4_wr_preamble;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG9_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned t_gear_hold;
   int unsigned t_gear_setup;
   int unsigned t_cmd_gear;
   int unsigned t_sync_gear;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG10_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_ckmpe;
   int unsigned t_mpx_s;
   int unsigned t_mpx_lh;
   int unsigned post_mpsm_gap_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG11_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned t_mrd_pda;
   int unsigned t_cmdcke;
   int unsigned t_wr_mpr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG12_struct_t;

typedef struct  {
   int unsigned t_ppd;
   int unsigned t_ccd_w2;
   int unsigned t_ccd_mw;
   int unsigned odtloff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG13_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xsr;
   int unsigned t_osco;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG14_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_stab_x32;
   int unsigned en_hwffc_t_stab;
   int unsigned en_dfi_lp_t_stab;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG15_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr;
   int unsigned t_rrd_dlr;
   int unsigned t_faw_dlr;
   int unsigned t_rp_ca_parity;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG16_struct_t;

`endif //UMCTL2_CID_EN
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned t_vrcg_disable;
   int unsigned t_vrcg_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG17_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mpdpxact;
   int unsigned t_mpsmx;
   int unsigned t_pd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG18_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_pda_h;
   int unsigned t_pda_s;
   int unsigned t_pda_dqs_delay;
   int unsigned t_pda_delay;
   int unsigned t_pda_latch;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG19_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_csl_srexit;
   int unsigned t_csh_srexit;
   int unsigned t_casrx;
   int unsigned t_cpded;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_osco_ddr5;
   int unsigned t_vrefca_cs;
   int unsigned t_mpc_hold;
   int unsigned t_mpc_setup;
   int unsigned t_mpc_cs;
   int unsigned t_csl;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rd2wr_dpr;
   int unsigned t_rd2wr_dlr;
   int unsigned t_wr2rd_dpr;
   int unsigned t_wr2rd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG22_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_pdn;
   int unsigned t_pdn_dsm_x1024;
   int unsigned t_xsr_dsm_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG23_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned max_wr_sync;
   int unsigned max_rd_sync;
   int unsigned rd2wr_s;
   int unsigned bank_org;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG24_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned rda2pre;
   int unsigned wra2pre;
   int unsigned lpddr4_diff_bank_rwa2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG25_struct_t;

`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_ccd_r;
   int unsigned t_ccd_w;
   int unsigned t_ccd_r_s;
   int unsigned t_ccd_w_s;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG26_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mrr2mpc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG27_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_srx2srx;
   int unsigned t_cpded2srx;
   int unsigned t_cssr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG28_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ckact;
   int unsigned t_ckoff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG29_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mrr2rd;
   int unsigned mrr2wr;
   int unsigned mrr2mrw;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG30_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ccd_r_2;
   int unsigned t_ccd_w_2;
   int unsigned t_ccd_r_s_2;
   int unsigned t_ccd_w_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ras_min_2;
   int unsigned t_faw_2;
   int unsigned t_wr2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG1_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rc_2;
   int unsigned rd2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_2;
   int unsigned rd2wr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG3_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rd2wr_dpr_2;
   int unsigned t_rd2wr_dlr_2;
   int unsigned t_wr2rd_dpr_2;
   int unsigned t_wr2rd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG4_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rp_2;
   int unsigned t_rrd_2;
   int unsigned t_ccd_2;
   int unsigned t_rcd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG5_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_s_2;
   int unsigned t_rrd_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG6_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ppd_2;
   int unsigned t_ccd_w2_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG7_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr_2;
   int unsigned t_rrd_dlr_2;
   int unsigned t_faw_dlr_2;
   int unsigned t_rp_ca_parity_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG8_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_xs_x32_2;
   int unsigned t_xs_dll_x32_2;
   int unsigned t_xs_abort_x32_2;
   int unsigned t_xs_fast_x32_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG9_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG10_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mrr2mpc_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG11_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned t_rd2rd_gap_r0r1;
   int unsigned t_rd2rd_gap_r1r0;
   int unsigned t_wr2rd_gap_r0r1;
   int unsigned t_wr2rd_gap_r1r0;
   int unsigned t_rd2wr_gap_r0r1;
   int unsigned t_rd2wr_gap_r1r0;
   int unsigned t_wr2wr_gap_r0r1;
   int unsigned t_wr2wr_gap_r1r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL0_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r2;
   int unsigned t_rd2rd_gap_r2r0;
   int unsigned t_wr2rd_gap_r0r2;
   int unsigned t_wr2rd_gap_r2r0;
   int unsigned t_rd2wr_gap_r0r2;
   int unsigned t_rd2wr_gap_r2r0;
   int unsigned t_wr2wr_gap_r0r2;
   int unsigned t_wr2wr_gap_r2r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL1_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r3;
   int unsigned t_rd2rd_gap_r3r0;
   int unsigned t_wr2rd_gap_r0r3;
   int unsigned t_wr2rd_gap_r3r0;
   int unsigned t_rd2wr_gap_r0r3;
   int unsigned t_rd2wr_gap_r3r0;
   int unsigned t_wr2wr_gap_r0r3;
   int unsigned t_wr2wr_gap_r3r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r2;
   int unsigned t_rd2rd_gap_r2r1;
   int unsigned t_wr2rd_gap_r1r2;
   int unsigned t_wr2rd_gap_r2r1;
   int unsigned t_rd2wr_gap_r1r2;
   int unsigned t_rd2wr_gap_r2r1;
   int unsigned t_wr2wr_gap_r1r2;
   int unsigned t_wr2wr_gap_r2r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r3;
   int unsigned t_rd2rd_gap_r3r1;
   int unsigned t_wr2rd_gap_r1r3;
   int unsigned t_wr2rd_gap_r3r1;
   int unsigned t_rd2wr_gap_r1r3;
   int unsigned t_rd2wr_gap_r3r1;
   int unsigned t_wr2wr_gap_r1r3;
   int unsigned t_wr2wr_gap_r3r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r2r3;
   int unsigned t_rd2rd_gap_r3r2;
   int unsigned t_wr2rd_gap_r2r3;
   int unsigned t_wr2rd_gap_r3r2;
   int unsigned t_rd2wr_gap_r2r3;
   int unsigned t_rd2wr_gap_r3r2;
   int unsigned t_wr2wr_gap_r2r3;
   int unsigned t_wr2wr_gap_r3r2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_ras_min_mram;
   int unsigned t_faw_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_MRAMTMG0_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rc_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_MRAMTMG1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rp_mram;
   int unsigned t_rrd_mram;
   int unsigned t_rcd_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_MRAMTMG2_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rrd_s_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_MRAMTMG3_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned emr;
   int unsigned mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_INITMR0_struct_t;

typedef struct  {
   int unsigned emr3;
   int unsigned emr2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_INITMR1_struct_t;

typedef struct  {
   int unsigned mr5;
   int unsigned mr4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_INITMR2_struct_t;

typedef struct  {
   int unsigned mr6;
   int unsigned mr22;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_INITMR3_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrlat;
   int unsigned dfi_tphy_wrdata;
   int unsigned dfi_t_rddata_en;
   int unsigned dfi_t_ctrl_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_dram_clk_enable;
   int unsigned dfi_t_dram_clk_disable;
   int unsigned dfi_t_wrdata_delay;
   int unsigned dfi_t_parin_lat;
   int unsigned dfi_t_cmd_lat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG1_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrcslat;
   int unsigned dfi_tphy_rdcslat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG2_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned dfi_t_geardown_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG3_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_dis;
   int unsigned dfi_twck_en_fs;
   int unsigned dfi_twck_en_wr;
   int unsigned dfi_twck_en_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG4_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_toggle_post;
   int unsigned dfi_twck_toggle_cs;
   int unsigned dfi_twck_toggle;
   int unsigned dfi_twck_fast_toggle;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG5_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_2n_mode_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG7_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_ctrlupd_interval_max_x1024;
   int unsigned dfi_t_ctrlupd_interval_min_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFIUPDTMG1_struct_t;

typedef struct  {
   int unsigned t_refi_x1_x32;
   int unsigned refresh_to_x1_x32;
   int unsigned refresh_margin;
   int unsigned t_refi_x1_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rfc_min;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG1_struct_t;

`ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr;
   int unsigned t_pbr2pbr;
   int unsigned t_pbr2act;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG2_struct_t;

`endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rfcsb;
   int unsigned t_refsbrd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned refresh_timer0_start_value_x32;
   int unsigned refresh_timer1_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG4_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned refresh_timer2_start_value_x32;
   int unsigned refresh_timer3_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned refresh_timer_lr_offset_x32;
   int unsigned refresh_timer_rank_offset_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG6_struct_t;

`endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr;
   int unsigned t_refsbrd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG7_struct_t;

`endif //UMCTL2_CID_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HET_RANK_RFC
typedef struct  {
   int unsigned t_rfc_min_het;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG8_struct_t;

`endif //UMCTL2_HET_RANK_RFC
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfc_min_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET2TMG1_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfcsb_2;
   int unsigned t_refsbrd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr_2;
   int unsigned t_refsbrd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET2TMG3_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
typedef struct  {
   int unsigned t_zq_long_nop;
   int unsigned t_zq_short_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_ZQSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_zq_short_interval_x1024;
   int unsigned t_zq_reset_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_ZQSET1TMG1_struct_t;

`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_zq_long_nop_2;
   int unsigned t_zq_short_nop_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_ZQSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_1;
   int unsigned ctrl_word_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RCDINIT1_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_3;
   int unsigned ctrl_word_4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RCDINIT2_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_5;
   int unsigned ctrl_word_6;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RCDINIT3_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_7;
   int unsigned ctrl_word_8;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RCDINIT4_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_enable;
   int unsigned dqsosc_interval_unit;
   int unsigned dqsosc_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DQSOSCCTL0_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mr4_read_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DERATEINT_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rrd;
   int unsigned derated_t_rp;
   int unsigned derated_t_ras_min;
   int unsigned derated_t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DERATEVAL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DERATEVAL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned hw_lp_idle_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_HWLPTMG0_struct_t;

typedef struct  {
   int unsigned pageclose_timer;
   int unsigned rdwr_idle_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_SCHEDTMG0_struct_t;

typedef struct  {
   int unsigned hpr_max_starve;
   int unsigned hpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_PERFHPR1_struct_t;

typedef struct  {
   int unsigned lpr_max_starve;
   int unsigned lpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_PERFLPR1_struct_t;

typedef struct  {
   int unsigned w_max_starve;
   int unsigned w_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_PERFWR1_struct_t;

typedef struct  {
   int unsigned frequency_ratio;
   int unsigned dfi_freq_fsp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_TMGCFG_struct_t;

`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned diff_rank_rd_gap;
   int unsigned diff_rank_wr_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANKTMG0_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned wr2rd_dr;
   int unsigned rd2wr_dr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANKTMG1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_to_x32;
   int unsigned selfref_to_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_PWRTMG_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned rd_odt_delay;
   int unsigned rd_odt_hold;
   int unsigned wr_odt_delay;
   int unsigned wr_odt_hold;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_ODTCFG_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct  {
   int unsigned retry_fifo_max_hold_timer_x4;
   int unsigned t_crc_alert_pw_max;
   int unsigned t_par_alert_pw_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_CRCPARTMG0_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_csalt;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH0_CRCPARTMG1_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ras_min;
   int unsigned t_ras_max;
   int unsigned t_faw;
   int unsigned wr2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rc;
   int unsigned rd2pre;
   int unsigned t_xp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG1_struct_t;

typedef struct  {
   int unsigned wr2rd;
   int unsigned rd2wr;
   int unsigned read_latency;
   int unsigned write_latency;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG2_struct_t;

typedef struct  {
   int unsigned wr2mr;
   int unsigned rd2mr;
   int unsigned t_mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG3_struct_t;

typedef struct  {
   int unsigned t_rp;
   int unsigned t_rrd;
   int unsigned t_ccd;
   int unsigned t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG4_struct_t;

typedef struct  {
   int unsigned t_cke;
   int unsigned t_ckesr;
   int unsigned t_cksre;
   int unsigned t_cksrx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG5_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_ckcsx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG6_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_csh;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG7_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xs_x32;
   int unsigned t_xs_dll_x32;
   int unsigned t_xs_abort_x32;
   int unsigned t_xs_fast_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG8_struct_t;

typedef struct  {
   int unsigned wr2rd_s;
   int unsigned t_rrd_s;
   int unsigned t_ccd_s;
   int unsigned ddr4_wr_preamble;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG9_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned t_gear_hold;
   int unsigned t_gear_setup;
   int unsigned t_cmd_gear;
   int unsigned t_sync_gear;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG10_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_ckmpe;
   int unsigned t_mpx_s;
   int unsigned t_mpx_lh;
   int unsigned post_mpsm_gap_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG11_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned t_mrd_pda;
   int unsigned t_cmdcke;
   int unsigned t_wr_mpr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG12_struct_t;

typedef struct  {
   int unsigned t_ppd;
   int unsigned t_ccd_w2;
   int unsigned t_ccd_mw;
   int unsigned odtloff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG13_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xsr;
   int unsigned t_osco;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG14_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_stab_x32;
   int unsigned en_hwffc_t_stab;
   int unsigned en_dfi_lp_t_stab;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG15_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr;
   int unsigned t_rrd_dlr;
   int unsigned t_faw_dlr;
   int unsigned t_rp_ca_parity;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG16_struct_t;

`endif //UMCTL2_CID_EN
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned t_vrcg_disable;
   int unsigned t_vrcg_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG17_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mpdpxact;
   int unsigned t_mpsmx;
   int unsigned t_pd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG18_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_pda_h;
   int unsigned t_pda_s;
   int unsigned t_pda_dqs_delay;
   int unsigned t_pda_delay;
   int unsigned t_pda_latch;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG19_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_csl_srexit;
   int unsigned t_csh_srexit;
   int unsigned t_casrx;
   int unsigned t_cpded;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_osco_ddr5;
   int unsigned t_vrefca_cs;
   int unsigned t_mpc_hold;
   int unsigned t_mpc_setup;
   int unsigned t_mpc_cs;
   int unsigned t_csl;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rd2wr_dpr;
   int unsigned t_rd2wr_dlr;
   int unsigned t_wr2rd_dpr;
   int unsigned t_wr2rd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG22_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_pdn;
   int unsigned t_pdn_dsm_x1024;
   int unsigned t_xsr_dsm_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG23_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned max_wr_sync;
   int unsigned max_rd_sync;
   int unsigned rd2wr_s;
   int unsigned bank_org;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG24_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned rda2pre;
   int unsigned wra2pre;
   int unsigned lpddr4_diff_bank_rwa2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG25_struct_t;

`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_ccd_r;
   int unsigned t_ccd_w;
   int unsigned t_ccd_r_s;
   int unsigned t_ccd_w_s;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG26_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mrr2mpc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG27_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_srx2srx;
   int unsigned t_cpded2srx;
   int unsigned t_cssr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG28_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ckact;
   int unsigned t_ckoff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG29_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mrr2rd;
   int unsigned mrr2wr;
   int unsigned mrr2mrw;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG30_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ccd_r_2;
   int unsigned t_ccd_w_2;
   int unsigned t_ccd_r_s_2;
   int unsigned t_ccd_w_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ras_min_2;
   int unsigned t_faw_2;
   int unsigned t_wr2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG1_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rc_2;
   int unsigned rd2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_2;
   int unsigned rd2wr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG3_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rd2wr_dpr_2;
   int unsigned t_rd2wr_dlr_2;
   int unsigned t_wr2rd_dpr_2;
   int unsigned t_wr2rd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG4_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rp_2;
   int unsigned t_rrd_2;
   int unsigned t_ccd_2;
   int unsigned t_rcd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG5_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_s_2;
   int unsigned t_rrd_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG6_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ppd_2;
   int unsigned t_ccd_w2_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG7_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr_2;
   int unsigned t_rrd_dlr_2;
   int unsigned t_faw_dlr_2;
   int unsigned t_rp_ca_parity_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG8_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_xs_x32_2;
   int unsigned t_xs_dll_x32_2;
   int unsigned t_xs_abort_x32_2;
   int unsigned t_xs_fast_x32_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG9_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG10_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mrr2mpc_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG11_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned t_rd2rd_gap_r0r1;
   int unsigned t_rd2rd_gap_r1r0;
   int unsigned t_wr2rd_gap_r0r1;
   int unsigned t_wr2rd_gap_r1r0;
   int unsigned t_rd2wr_gap_r0r1;
   int unsigned t_rd2wr_gap_r1r0;
   int unsigned t_wr2wr_gap_r0r1;
   int unsigned t_wr2wr_gap_r1r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL0_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r2;
   int unsigned t_rd2rd_gap_r2r0;
   int unsigned t_wr2rd_gap_r0r2;
   int unsigned t_wr2rd_gap_r2r0;
   int unsigned t_rd2wr_gap_r0r2;
   int unsigned t_rd2wr_gap_r2r0;
   int unsigned t_wr2wr_gap_r0r2;
   int unsigned t_wr2wr_gap_r2r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL1_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r3;
   int unsigned t_rd2rd_gap_r3r0;
   int unsigned t_wr2rd_gap_r0r3;
   int unsigned t_wr2rd_gap_r3r0;
   int unsigned t_rd2wr_gap_r0r3;
   int unsigned t_rd2wr_gap_r3r0;
   int unsigned t_wr2wr_gap_r0r3;
   int unsigned t_wr2wr_gap_r3r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r2;
   int unsigned t_rd2rd_gap_r2r1;
   int unsigned t_wr2rd_gap_r1r2;
   int unsigned t_wr2rd_gap_r2r1;
   int unsigned t_rd2wr_gap_r1r2;
   int unsigned t_rd2wr_gap_r2r1;
   int unsigned t_wr2wr_gap_r1r2;
   int unsigned t_wr2wr_gap_r2r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r3;
   int unsigned t_rd2rd_gap_r3r1;
   int unsigned t_wr2rd_gap_r1r3;
   int unsigned t_wr2rd_gap_r3r1;
   int unsigned t_rd2wr_gap_r1r3;
   int unsigned t_rd2wr_gap_r3r1;
   int unsigned t_wr2wr_gap_r1r3;
   int unsigned t_wr2wr_gap_r3r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r2r3;
   int unsigned t_rd2rd_gap_r3r2;
   int unsigned t_wr2rd_gap_r2r3;
   int unsigned t_wr2rd_gap_r3r2;
   int unsigned t_rd2wr_gap_r2r3;
   int unsigned t_rd2wr_gap_r3r2;
   int unsigned t_wr2wr_gap_r2r3;
   int unsigned t_wr2wr_gap_r3r2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_ras_min_mram;
   int unsigned t_faw_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_MRAMTMG0_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rc_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_MRAMTMG1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rp_mram;
   int unsigned t_rrd_mram;
   int unsigned t_rcd_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_MRAMTMG2_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rrd_s_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_MRAMTMG3_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned emr;
   int unsigned mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_INITMR0_struct_t;

typedef struct  {
   int unsigned emr3;
   int unsigned emr2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_INITMR1_struct_t;

typedef struct  {
   int unsigned mr5;
   int unsigned mr4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_INITMR2_struct_t;

typedef struct  {
   int unsigned mr6;
   int unsigned mr22;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_INITMR3_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrlat;
   int unsigned dfi_tphy_wrdata;
   int unsigned dfi_t_rddata_en;
   int unsigned dfi_t_ctrl_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_dram_clk_enable;
   int unsigned dfi_t_dram_clk_disable;
   int unsigned dfi_t_wrdata_delay;
   int unsigned dfi_t_parin_lat;
   int unsigned dfi_t_cmd_lat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG1_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrcslat;
   int unsigned dfi_tphy_rdcslat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG2_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned dfi_t_geardown_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG3_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_dis;
   int unsigned dfi_twck_en_fs;
   int unsigned dfi_twck_en_wr;
   int unsigned dfi_twck_en_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG4_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_toggle_post;
   int unsigned dfi_twck_toggle_cs;
   int unsigned dfi_twck_toggle;
   int unsigned dfi_twck_fast_toggle;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG5_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_2n_mode_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG7_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_ctrlupd_interval_max_x1024;
   int unsigned dfi_t_ctrlupd_interval_min_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFIUPDTMG1_struct_t;

typedef struct  {
   int unsigned t_refi_x1_x32;
   int unsigned refresh_to_x1_x32;
   int unsigned refresh_margin;
   int unsigned t_refi_x1_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rfc_min;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG1_struct_t;

`ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr;
   int unsigned t_pbr2pbr;
   int unsigned t_pbr2act;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG2_struct_t;

`endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rfcsb;
   int unsigned t_refsbrd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned refresh_timer0_start_value_x32;
   int unsigned refresh_timer1_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG4_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned refresh_timer2_start_value_x32;
   int unsigned refresh_timer3_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned refresh_timer_lr_offset_x32;
   int unsigned refresh_timer_rank_offset_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG6_struct_t;

`endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr;
   int unsigned t_refsbrd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG7_struct_t;

`endif //UMCTL2_CID_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HET_RANK_RFC
typedef struct  {
   int unsigned t_rfc_min_het;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG8_struct_t;

`endif //UMCTL2_HET_RANK_RFC
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfc_min_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET2TMG1_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfcsb_2;
   int unsigned t_refsbrd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr_2;
   int unsigned t_refsbrd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET2TMG3_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
typedef struct  {
   int unsigned t_zq_long_nop;
   int unsigned t_zq_short_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_ZQSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_zq_short_interval_x1024;
   int unsigned t_zq_reset_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_ZQSET1TMG1_struct_t;

`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_zq_long_nop_2;
   int unsigned t_zq_short_nop_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_ZQSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_1;
   int unsigned ctrl_word_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RCDINIT1_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_3;
   int unsigned ctrl_word_4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RCDINIT2_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_5;
   int unsigned ctrl_word_6;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RCDINIT3_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_7;
   int unsigned ctrl_word_8;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RCDINIT4_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_enable;
   int unsigned dqsosc_interval_unit;
   int unsigned dqsosc_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DQSOSCCTL0_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mr4_read_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DERATEINT_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rrd;
   int unsigned derated_t_rp;
   int unsigned derated_t_ras_min;
   int unsigned derated_t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DERATEVAL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DERATEVAL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned hw_lp_idle_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_HWLPTMG0_struct_t;

typedef struct  {
   int unsigned pageclose_timer;
   int unsigned rdwr_idle_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_SCHEDTMG0_struct_t;

typedef struct  {
   int unsigned hpr_max_starve;
   int unsigned hpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_PERFHPR1_struct_t;

typedef struct  {
   int unsigned lpr_max_starve;
   int unsigned lpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_PERFLPR1_struct_t;

typedef struct  {
   int unsigned w_max_starve;
   int unsigned w_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_PERFWR1_struct_t;

`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned diff_rank_rd_gap;
   int unsigned diff_rank_wr_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANKTMG0_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned wr2rd_dr;
   int unsigned rd2wr_dr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANKTMG1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_to_x32;
   int unsigned selfref_to_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_PWRTMG_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned rd_odt_delay;
   int unsigned rd_odt_hold;
   int unsigned wr_odt_delay;
   int unsigned wr_odt_hold;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_ODTCFG_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct  {
   int unsigned retry_fifo_max_hold_timer_x4;
   int unsigned t_crc_alert_pw_max;
   int unsigned t_par_alert_pw_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_CRCPARTMG0_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_csalt;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ2_CH1_CRCPARTMG1_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ras_min;
   int unsigned t_ras_max;
   int unsigned t_faw;
   int unsigned wr2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rc;
   int unsigned rd2pre;
   int unsigned t_xp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG1_struct_t;

typedef struct  {
   int unsigned wr2rd;
   int unsigned rd2wr;
   int unsigned read_latency;
   int unsigned write_latency;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG2_struct_t;

typedef struct  {
   int unsigned wr2mr;
   int unsigned rd2mr;
   int unsigned t_mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG3_struct_t;

typedef struct  {
   int unsigned t_rp;
   int unsigned t_rrd;
   int unsigned t_ccd;
   int unsigned t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG4_struct_t;

typedef struct  {
   int unsigned t_cke;
   int unsigned t_ckesr;
   int unsigned t_cksre;
   int unsigned t_cksrx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG5_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_ckcsx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG6_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_csh;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG7_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xs_x32;
   int unsigned t_xs_dll_x32;
   int unsigned t_xs_abort_x32;
   int unsigned t_xs_fast_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG8_struct_t;

typedef struct  {
   int unsigned wr2rd_s;
   int unsigned t_rrd_s;
   int unsigned t_ccd_s;
   int unsigned ddr4_wr_preamble;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG9_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned t_gear_hold;
   int unsigned t_gear_setup;
   int unsigned t_cmd_gear;
   int unsigned t_sync_gear;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG10_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_ckmpe;
   int unsigned t_mpx_s;
   int unsigned t_mpx_lh;
   int unsigned post_mpsm_gap_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG11_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned t_mrd_pda;
   int unsigned t_cmdcke;
   int unsigned t_wr_mpr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG12_struct_t;

typedef struct  {
   int unsigned t_ppd;
   int unsigned t_ccd_w2;
   int unsigned t_ccd_mw;
   int unsigned odtloff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG13_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xsr;
   int unsigned t_osco;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG14_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_stab_x32;
   int unsigned en_hwffc_t_stab;
   int unsigned en_dfi_lp_t_stab;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG15_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr;
   int unsigned t_rrd_dlr;
   int unsigned t_faw_dlr;
   int unsigned t_rp_ca_parity;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG16_struct_t;

`endif //UMCTL2_CID_EN
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned t_vrcg_disable;
   int unsigned t_vrcg_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG17_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mpdpxact;
   int unsigned t_mpsmx;
   int unsigned t_pd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG18_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_pda_h;
   int unsigned t_pda_s;
   int unsigned t_pda_dqs_delay;
   int unsigned t_pda_delay;
   int unsigned t_pda_latch;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG19_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_csl_srexit;
   int unsigned t_csh_srexit;
   int unsigned t_casrx;
   int unsigned t_cpded;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_osco_ddr5;
   int unsigned t_vrefca_cs;
   int unsigned t_mpc_hold;
   int unsigned t_mpc_setup;
   int unsigned t_mpc_cs;
   int unsigned t_csl;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rd2wr_dpr;
   int unsigned t_rd2wr_dlr;
   int unsigned t_wr2rd_dpr;
   int unsigned t_wr2rd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG22_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_pdn;
   int unsigned t_pdn_dsm_x1024;
   int unsigned t_xsr_dsm_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG23_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned max_wr_sync;
   int unsigned max_rd_sync;
   int unsigned rd2wr_s;
   int unsigned bank_org;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG24_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned rda2pre;
   int unsigned wra2pre;
   int unsigned lpddr4_diff_bank_rwa2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG25_struct_t;

`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_ccd_r;
   int unsigned t_ccd_w;
   int unsigned t_ccd_r_s;
   int unsigned t_ccd_w_s;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG26_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mrr2mpc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG27_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_srx2srx;
   int unsigned t_cpded2srx;
   int unsigned t_cssr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG28_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ckact;
   int unsigned t_ckoff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG29_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mrr2rd;
   int unsigned mrr2wr;
   int unsigned mrr2mrw;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG30_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ccd_r_2;
   int unsigned t_ccd_w_2;
   int unsigned t_ccd_r_s_2;
   int unsigned t_ccd_w_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ras_min_2;
   int unsigned t_faw_2;
   int unsigned t_wr2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG1_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rc_2;
   int unsigned rd2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_2;
   int unsigned rd2wr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG3_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rd2wr_dpr_2;
   int unsigned t_rd2wr_dlr_2;
   int unsigned t_wr2rd_dpr_2;
   int unsigned t_wr2rd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG4_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rp_2;
   int unsigned t_rrd_2;
   int unsigned t_ccd_2;
   int unsigned t_rcd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG5_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_s_2;
   int unsigned t_rrd_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG6_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ppd_2;
   int unsigned t_ccd_w2_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG7_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr_2;
   int unsigned t_rrd_dlr_2;
   int unsigned t_faw_dlr_2;
   int unsigned t_rp_ca_parity_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG8_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_xs_x32_2;
   int unsigned t_xs_dll_x32_2;
   int unsigned t_xs_abort_x32_2;
   int unsigned t_xs_fast_x32_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG9_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG10_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mrr2mpc_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG11_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned t_rd2rd_gap_r0r1;
   int unsigned t_rd2rd_gap_r1r0;
   int unsigned t_wr2rd_gap_r0r1;
   int unsigned t_wr2rd_gap_r1r0;
   int unsigned t_rd2wr_gap_r0r1;
   int unsigned t_rd2wr_gap_r1r0;
   int unsigned t_wr2wr_gap_r0r1;
   int unsigned t_wr2wr_gap_r1r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL0_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r2;
   int unsigned t_rd2rd_gap_r2r0;
   int unsigned t_wr2rd_gap_r0r2;
   int unsigned t_wr2rd_gap_r2r0;
   int unsigned t_rd2wr_gap_r0r2;
   int unsigned t_rd2wr_gap_r2r0;
   int unsigned t_wr2wr_gap_r0r2;
   int unsigned t_wr2wr_gap_r2r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL1_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r3;
   int unsigned t_rd2rd_gap_r3r0;
   int unsigned t_wr2rd_gap_r0r3;
   int unsigned t_wr2rd_gap_r3r0;
   int unsigned t_rd2wr_gap_r0r3;
   int unsigned t_rd2wr_gap_r3r0;
   int unsigned t_wr2wr_gap_r0r3;
   int unsigned t_wr2wr_gap_r3r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r2;
   int unsigned t_rd2rd_gap_r2r1;
   int unsigned t_wr2rd_gap_r1r2;
   int unsigned t_wr2rd_gap_r2r1;
   int unsigned t_rd2wr_gap_r1r2;
   int unsigned t_rd2wr_gap_r2r1;
   int unsigned t_wr2wr_gap_r1r2;
   int unsigned t_wr2wr_gap_r2r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r3;
   int unsigned t_rd2rd_gap_r3r1;
   int unsigned t_wr2rd_gap_r1r3;
   int unsigned t_wr2rd_gap_r3r1;
   int unsigned t_rd2wr_gap_r1r3;
   int unsigned t_rd2wr_gap_r3r1;
   int unsigned t_wr2wr_gap_r1r3;
   int unsigned t_wr2wr_gap_r3r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r2r3;
   int unsigned t_rd2rd_gap_r3r2;
   int unsigned t_wr2rd_gap_r2r3;
   int unsigned t_wr2rd_gap_r3r2;
   int unsigned t_rd2wr_gap_r2r3;
   int unsigned t_rd2wr_gap_r3r2;
   int unsigned t_wr2wr_gap_r2r3;
   int unsigned t_wr2wr_gap_r3r2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_ras_min_mram;
   int unsigned t_faw_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_MRAMTMG0_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rc_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_MRAMTMG1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rp_mram;
   int unsigned t_rrd_mram;
   int unsigned t_rcd_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_MRAMTMG2_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rrd_s_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_MRAMTMG3_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned emr;
   int unsigned mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_INITMR0_struct_t;

typedef struct  {
   int unsigned emr3;
   int unsigned emr2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_INITMR1_struct_t;

typedef struct  {
   int unsigned mr5;
   int unsigned mr4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_INITMR2_struct_t;

typedef struct  {
   int unsigned mr6;
   int unsigned mr22;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_INITMR3_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrlat;
   int unsigned dfi_tphy_wrdata;
   int unsigned dfi_t_rddata_en;
   int unsigned dfi_t_ctrl_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_dram_clk_enable;
   int unsigned dfi_t_dram_clk_disable;
   int unsigned dfi_t_wrdata_delay;
   int unsigned dfi_t_parin_lat;
   int unsigned dfi_t_cmd_lat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG1_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrcslat;
   int unsigned dfi_tphy_rdcslat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG2_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned dfi_t_geardown_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG3_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_dis;
   int unsigned dfi_twck_en_fs;
   int unsigned dfi_twck_en_wr;
   int unsigned dfi_twck_en_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG4_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_toggle_post;
   int unsigned dfi_twck_toggle_cs;
   int unsigned dfi_twck_toggle;
   int unsigned dfi_twck_fast_toggle;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG5_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_2n_mode_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG7_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_ctrlupd_interval_max_x1024;
   int unsigned dfi_t_ctrlupd_interval_min_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFIUPDTMG1_struct_t;

typedef struct  {
   int unsigned t_refi_x1_x32;
   int unsigned refresh_to_x1_x32;
   int unsigned refresh_margin;
   int unsigned t_refi_x1_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rfc_min;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG1_struct_t;

`ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr;
   int unsigned t_pbr2pbr;
   int unsigned t_pbr2act;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG2_struct_t;

`endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rfcsb;
   int unsigned t_refsbrd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned refresh_timer0_start_value_x32;
   int unsigned refresh_timer1_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG4_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned refresh_timer2_start_value_x32;
   int unsigned refresh_timer3_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned refresh_timer_lr_offset_x32;
   int unsigned refresh_timer_rank_offset_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG6_struct_t;

`endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr;
   int unsigned t_refsbrd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG7_struct_t;

`endif //UMCTL2_CID_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HET_RANK_RFC
typedef struct  {
   int unsigned t_rfc_min_het;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG8_struct_t;

`endif //UMCTL2_HET_RANK_RFC
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfc_min_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET2TMG1_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfcsb_2;
   int unsigned t_refsbrd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr_2;
   int unsigned t_refsbrd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET2TMG3_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
typedef struct  {
   int unsigned t_zq_long_nop;
   int unsigned t_zq_short_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_ZQSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_zq_short_interval_x1024;
   int unsigned t_zq_reset_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_ZQSET1TMG1_struct_t;

`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_zq_long_nop_2;
   int unsigned t_zq_short_nop_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_ZQSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_1;
   int unsigned ctrl_word_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RCDINIT1_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_3;
   int unsigned ctrl_word_4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RCDINIT2_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_5;
   int unsigned ctrl_word_6;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RCDINIT3_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_7;
   int unsigned ctrl_word_8;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RCDINIT4_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_enable;
   int unsigned dqsosc_interval_unit;
   int unsigned dqsosc_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DQSOSCCTL0_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mr4_read_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DERATEINT_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rrd;
   int unsigned derated_t_rp;
   int unsigned derated_t_ras_min;
   int unsigned derated_t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DERATEVAL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DERATEVAL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned hw_lp_idle_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_HWLPTMG0_struct_t;

typedef struct  {
   int unsigned pageclose_timer;
   int unsigned rdwr_idle_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_SCHEDTMG0_struct_t;

typedef struct  {
   int unsigned hpr_max_starve;
   int unsigned hpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_PERFHPR1_struct_t;

typedef struct  {
   int unsigned lpr_max_starve;
   int unsigned lpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_PERFLPR1_struct_t;

typedef struct  {
   int unsigned w_max_starve;
   int unsigned w_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_PERFWR1_struct_t;

typedef struct  {
   int unsigned frequency_ratio;
   int unsigned dfi_freq_fsp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_TMGCFG_struct_t;

`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned diff_rank_rd_gap;
   int unsigned diff_rank_wr_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANKTMG0_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned wr2rd_dr;
   int unsigned rd2wr_dr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANKTMG1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_to_x32;
   int unsigned selfref_to_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_PWRTMG_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned rd_odt_delay;
   int unsigned rd_odt_hold;
   int unsigned wr_odt_delay;
   int unsigned wr_odt_hold;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_ODTCFG_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct  {
   int unsigned retry_fifo_max_hold_timer_x4;
   int unsigned t_crc_alert_pw_max;
   int unsigned t_par_alert_pw_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_CRCPARTMG0_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_csalt;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH0_CRCPARTMG1_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ras_min;
   int unsigned t_ras_max;
   int unsigned t_faw;
   int unsigned wr2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rc;
   int unsigned rd2pre;
   int unsigned t_xp;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG1_struct_t;

typedef struct  {
   int unsigned wr2rd;
   int unsigned rd2wr;
   int unsigned read_latency;
   int unsigned write_latency;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG2_struct_t;

typedef struct  {
   int unsigned wr2mr;
   int unsigned rd2mr;
   int unsigned t_mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG3_struct_t;

typedef struct  {
   int unsigned t_rp;
   int unsigned t_rrd;
   int unsigned t_ccd;
   int unsigned t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG4_struct_t;

typedef struct  {
   int unsigned t_cke;
   int unsigned t_ckesr;
   int unsigned t_cksre;
   int unsigned t_cksrx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG5_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_ckcsx;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG6_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_csh;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG7_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xs_x32;
   int unsigned t_xs_dll_x32;
   int unsigned t_xs_abort_x32;
   int unsigned t_xs_fast_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG8_struct_t;

typedef struct  {
   int unsigned wr2rd_s;
   int unsigned t_rrd_s;
   int unsigned t_ccd_s;
   int unsigned ddr4_wr_preamble;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG9_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned t_gear_hold;
   int unsigned t_gear_setup;
   int unsigned t_cmd_gear;
   int unsigned t_sync_gear;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG10_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_ckmpe;
   int unsigned t_mpx_s;
   int unsigned t_mpx_lh;
   int unsigned post_mpsm_gap_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG11_struct_t;

`endif //DDRCTL_DDR
typedef struct  {
   int unsigned t_mrd_pda;
   int unsigned t_cmdcke;
   int unsigned t_wr_mpr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG12_struct_t;

typedef struct  {
   int unsigned t_ppd;
   int unsigned t_ccd_w2;
   int unsigned t_ccd_mw;
   int unsigned odtloff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG13_struct_t;

`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_xsr;
   int unsigned t_osco;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG14_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned t_stab_x32;
   int unsigned en_hwffc_t_stab;
   int unsigned en_dfi_lp_t_stab;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG15_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr;
   int unsigned t_rrd_dlr;
   int unsigned t_faw_dlr;
   int unsigned t_rp_ca_parity;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG16_struct_t;

`endif //UMCTL2_CID_EN
`ifdef UMCTL2_HWFFC_EN
typedef struct  {
   int unsigned t_vrcg_disable;
   int unsigned t_vrcg_enable;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG17_struct_t;

`endif //UMCTL2_HWFFC_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mpdpxact;
   int unsigned t_mpsmx;
   int unsigned t_pd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG18_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_pda_h;
   int unsigned t_pda_s;
   int unsigned t_pda_dqs_delay;
   int unsigned t_pda_delay;
   int unsigned t_pda_latch;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG19_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_csl_srexit;
   int unsigned t_csh_srexit;
   int unsigned t_casrx;
   int unsigned t_cpded;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG20_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_osco_ddr5;
   int unsigned t_vrefca_cs;
   int unsigned t_mpc_hold;
   int unsigned t_mpc_setup;
   int unsigned t_mpc_cs;
   int unsigned t_csl;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG21_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rd2wr_dpr;
   int unsigned t_rd2wr_dlr;
   int unsigned t_wr2rd_dpr;
   int unsigned t_wr2rd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG22_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned t_pdn;
   int unsigned t_pdn_dsm_x1024;
   int unsigned t_xsr_dsm_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG23_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned max_wr_sync;
   int unsigned max_rd_sync;
   int unsigned rd2wr_s;
   int unsigned bank_org;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG24_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned rda2pre;
   int unsigned wra2pre;
   int unsigned lpddr4_diff_bank_rwa2pre;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG25_struct_t;

`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_ccd_r;
   int unsigned t_ccd_w;
   int unsigned t_ccd_r_s;
   int unsigned t_ccd_w_s;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG26_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_mrr2mpc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG27_struct_t;

`endif //MEMC_DDR5
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_srx2srx;
   int unsigned t_cpded2srx;
   int unsigned t_cssr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG28_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_ckact;
   int unsigned t_ckoff;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG29_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mrr2rd;
   int unsigned mrr2wr;
   int unsigned mrr2mrw;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG30_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ccd_r_2;
   int unsigned t_ccd_w_2;
   int unsigned t_ccd_r_s_2;
   int unsigned t_ccd_w_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ras_min_2;
   int unsigned t_faw_2;
   int unsigned t_wr2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG1_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rc_2;
   int unsigned rd2pre_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_2;
   int unsigned rd2wr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG3_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rd2wr_dpr_2;
   int unsigned t_rd2wr_dlr_2;
   int unsigned t_wr2rd_dpr_2;
   int unsigned t_wr2rd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG4_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rp_2;
   int unsigned t_rrd_2;
   int unsigned t_ccd_2;
   int unsigned t_rcd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG5_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned wr2rd_s_2;
   int unsigned t_rrd_s_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG6_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_ppd_2;
   int unsigned t_ccd_w2_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG7_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_ccd_dlr_2;
   int unsigned t_rrd_dlr_2;
   int unsigned t_faw_dlr_2;
   int unsigned t_rp_ca_parity_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG8_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_xs_x32_2;
   int unsigned t_xs_dll_x32_2;
   int unsigned t_xs_abort_x32_2;
   int unsigned t_xs_fast_x32_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG9_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG10_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_mrr2mpc_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG11_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned t_rd2rd_gap_r0r1;
   int unsigned t_rd2rd_gap_r1r0;
   int unsigned t_wr2rd_gap_r0r1;
   int unsigned t_wr2rd_gap_r1r0;
   int unsigned t_rd2wr_gap_r0r1;
   int unsigned t_rd2wr_gap_r1r0;
   int unsigned t_wr2wr_gap_r0r1;
   int unsigned t_wr2wr_gap_r1r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL0_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r2;
   int unsigned t_rd2rd_gap_r2r0;
   int unsigned t_wr2rd_gap_r0r2;
   int unsigned t_wr2rd_gap_r2r0;
   int unsigned t_rd2wr_gap_r0r2;
   int unsigned t_rd2wr_gap_r2r0;
   int unsigned t_wr2wr_gap_r0r2;
   int unsigned t_wr2wr_gap_r2r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL1_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r0r3;
   int unsigned t_rd2rd_gap_r3r0;
   int unsigned t_wr2rd_gap_r0r3;
   int unsigned t_wr2rd_gap_r3r0;
   int unsigned t_rd2wr_gap_r0r3;
   int unsigned t_rd2wr_gap_r3r0;
   int unsigned t_wr2wr_gap_r0r3;
   int unsigned t_wr2wr_gap_r3r0;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL2_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r2;
   int unsigned t_rd2rd_gap_r2r1;
   int unsigned t_wr2rd_gap_r1r2;
   int unsigned t_wr2rd_gap_r2r1;
   int unsigned t_rd2wr_gap_r1r2;
   int unsigned t_rd2wr_gap_r2r1;
   int unsigned t_wr2wr_gap_r1r2;
   int unsigned t_wr2wr_gap_r2r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL3_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r1r3;
   int unsigned t_rd2rd_gap_r3r1;
   int unsigned t_wr2rd_gap_r1r3;
   int unsigned t_wr2rd_gap_r3r1;
   int unsigned t_rd2wr_gap_r1r3;
   int unsigned t_rd2wr_gap_r3r1;
   int unsigned t_wr2wr_gap_r1r3;
   int unsigned t_wr2wr_gap_r3r1;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL4_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned t_rd2rd_gap_r2r3;
   int unsigned t_rd2rd_gap_r3r2;
   int unsigned t_wr2rd_gap_r2r3;
   int unsigned t_wr2rd_gap_r3r2;
   int unsigned t_rd2wr_gap_r2r3;
   int unsigned t_rd2wr_gap_r3r2;
   int unsigned t_wr2wr_gap_r2r3;
   int unsigned t_wr2wr_gap_r3r2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`endif //MEMC_DDR5
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_ras_min_mram;
   int unsigned t_faw_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_MRAMTMG0_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rc_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_MRAMTMG1_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rp_mram;
   int unsigned t_rrd_mram;
   int unsigned t_rcd_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_MRAMTMG2_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
`ifdef UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned t_rrd_s_mram;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_MRAMTMG3_struct_t;

`endif //UMCTL2_DDR4_MRAM_EN
typedef struct  {
   int unsigned emr;
   int unsigned mr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_INITMR0_struct_t;

typedef struct  {
   int unsigned emr3;
   int unsigned emr2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_INITMR1_struct_t;

typedef struct  {
   int unsigned mr5;
   int unsigned mr4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_INITMR2_struct_t;

typedef struct  {
   int unsigned mr6;
   int unsigned mr22;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_INITMR3_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrlat;
   int unsigned dfi_tphy_wrdata;
   int unsigned dfi_t_rddata_en;
   int unsigned dfi_t_ctrl_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG0_struct_t;

typedef struct  {
   int unsigned dfi_t_dram_clk_enable;
   int unsigned dfi_t_dram_clk_disable;
   int unsigned dfi_t_wrdata_delay;
   int unsigned dfi_t_parin_lat;
   int unsigned dfi_t_cmd_lat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG1_struct_t;

typedef struct  {
   int unsigned dfi_tphy_wrcslat;
   int unsigned dfi_tphy_rdcslat;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG2_struct_t;

`ifdef DDRCTL_DDR
`ifndef MEMC_CMD_RTN2IDLE
typedef struct  {
   int unsigned dfi_t_geardown_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG3_struct_t;

`endif //MEMC_CMD_RTN2IDLE
`endif //DDRCTL_DDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_dis;
   int unsigned dfi_twck_en_fs;
   int unsigned dfi_twck_en_wr;
   int unsigned dfi_twck_en_rd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG4_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned dfi_twck_toggle_post;
   int unsigned dfi_twck_toggle_cs;
   int unsigned dfi_twck_toggle;
   int unsigned dfi_twck_fast_toggle;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG5_struct_t;

`endif //DDRCTL_LPDDR
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_2n_mode_delay;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG7_struct_t;

`endif //MEMC_DDR5
typedef struct  {
   int unsigned dfi_t_ctrlupd_interval_max_x1024;
   int unsigned dfi_t_ctrlupd_interval_min_x1024;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFIUPDTMG1_struct_t;

typedef struct  {
   int unsigned t_refi_x1_x32;
   int unsigned refresh_to_x1_x32;
   int unsigned refresh_margin;
   int unsigned t_refi_x1_sel;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_rfc_min;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG1_struct_t;

`ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr;
   int unsigned t_pbr2pbr;
   int unsigned t_pbr2act;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG2_struct_t;

`endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
typedef struct  {
   int unsigned t_rfcsb;
   int unsigned t_refsbrd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG3_struct_t;

`endif //MEMC_DDR5
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned refresh_timer0_start_value_x32;
   int unsigned refresh_timer1_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG4_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
`ifdef MEMC_NUM_RANKS_GT_2
typedef struct  {
   int unsigned refresh_timer2_start_value_x32;
   int unsigned refresh_timer3_start_value_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG5_struct_t;

`endif //MEMC_NUM_RANKS_GT_2
`ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct  {
   int unsigned refresh_timer_lr_offset_x32;
   int unsigned refresh_timer_rank_offset_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG6_struct_t;

`endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
`ifdef MEMC_DDR5
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr;
   int unsigned t_refsbrd_dlr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG7_struct_t;

`endif //UMCTL2_CID_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HET_RANK_RFC
typedef struct  {
   int unsigned t_rfc_min_het;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG8_struct_t;

`endif //UMCTL2_HET_RANK_RFC
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfc_min_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfc_min_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET2TMG1_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_rfcsb_2;
   int unsigned t_refsbrd_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET2TMG2_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
`ifdef UMCTL2_CID_EN
typedef struct  {
   int unsigned t_rfcsb_dlr_2;
   int unsigned t_refsbrd_dlr_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET2TMG3_struct_t;

`endif //UMCTL2_CID_EN
`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
typedef struct  {
   int unsigned t_zq_long_nop;
   int unsigned t_zq_short_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_ZQSET1TMG0_struct_t;

typedef struct  {
   int unsigned t_zq_short_interval_x1024;
   int unsigned t_zq_reset_nop;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_ZQSET1TMG1_struct_t;

`ifdef MEMC_DDR5
`ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct  {
   int unsigned t_zq_long_nop_2;
   int unsigned t_zq_short_nop_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_ZQSET2TMG0_struct_t;

`endif //DDRCTL_TWO_TIMING_SETS_EN
`endif //MEMC_DDR5
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_1;
   int unsigned ctrl_word_2;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RCDINIT1_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_3;
   int unsigned ctrl_word_4;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RCDINIT2_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_5;
   int unsigned ctrl_word_6;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RCDINIT3_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef UMCTL2_HWFFC_EN
`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned ctrl_word_7;
   int unsigned ctrl_word_8;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RCDINIT4_struct_t;

`endif //DDRCTL_DDR
`endif //UMCTL2_HWFFC_EN
`ifdef LPDDR45_DQSOSC_EN
typedef struct  {
   int unsigned dqsosc_enable;
   int unsigned dqsosc_interval_unit;
   int unsigned dqsosc_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DQSOSCCTL0_struct_t;

`endif //LPDDR45_DQSOSC_EN
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned mr4_read_interval;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DERATEINT_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rrd;
   int unsigned derated_t_rp;
   int unsigned derated_t_ras_min;
   int unsigned derated_t_rcd;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DERATEVAL0_struct_t;

`endif //DDRCTL_LPDDR
`ifdef DDRCTL_LPDDR
typedef struct  {
   int unsigned derated_t_rc;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DERATEVAL1_struct_t;

`endif //DDRCTL_LPDDR
typedef struct  {
   int unsigned hw_lp_idle_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_HWLPTMG0_struct_t;

typedef struct  {
   int unsigned pageclose_timer;
   int unsigned rdwr_idle_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_SCHEDTMG0_struct_t;

typedef struct  {
   int unsigned hpr_max_starve;
   int unsigned hpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_PERFHPR1_struct_t;

typedef struct  {
   int unsigned lpr_max_starve;
   int unsigned lpr_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_PERFLPR1_struct_t;

typedef struct  {
   int unsigned w_max_starve;
   int unsigned w_xact_run_length;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_PERFWR1_struct_t;

`ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct  {
   int unsigned diff_rank_rd_gap;
   int unsigned diff_rank_wr_gap;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANKTMG0_struct_t;

`endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
`ifdef MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned wr2rd_dr;
   int unsigned rd2wr_dr;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANKTMG1_struct_t;

`endif //MEMC_NUM_RANKS_GT_1
typedef struct  {
   int unsigned powerdown_to_x32;
   int unsigned selfref_to_x32;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_PWRTMG_struct_t;

`ifdef DDRCTL_DDR
typedef struct  {
   int unsigned rd_odt_delay;
   int unsigned rd_odt_hold;
   int unsigned wr_odt_delay;
   int unsigned wr_odt_hold;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_ODTCFG_struct_t;

`endif //DDRCTL_DDR
`ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct  {
   int unsigned retry_fifo_max_hold_timer_x4;
   int unsigned t_crc_alert_pw_max;
   int unsigned t_par_alert_pw_max;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_CRCPARTMG0_struct_t;

`endif //UMCTL2_CRC_PARITY_RETRY
`ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct  {
   int unsigned t_csalt;
  int unsigned value; // full 32-bit register value.
  } REGB_FREQ3_CH1_CRCPARTMG1_struct_t;

`endif //DDRCTL_DDR_DUAL_CHANNEL
`endif

