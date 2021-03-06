// coreBuilder: This is an automated C header file. DO NOT EDIT.
#ifndef __CINIT_QDYN_STRUCT__H__
#define __CINIT_QDYN_STRUCT__H__ 
/** @brief Structure to hold programming intent for the quasi-dynamic register fields. */ 
typedef struct tag_mctl_qdyn_cfg_t {
   uint32_rnd_t dll_off_mode;
   uint32_rnd_t target_frequency;
   uint32_rnd_t geardown_mode[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wck_on[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t derate_mr4_tuf_dis;
   uint32_rnd_t derate_low_temp_limit;
   uint32_rnd_t derate_high_temp_limit;
   uint32_rnd_t hw_lp_en[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t same_bank_refresh;
   uint32_rnd_t tcr_refab_thr;
   uint32_rnd_t fgr_mode;
   uint32_rnd_t dis_srx_zqcl;
   uint32_rnd_t dqsosc_runtime;
   uint32_rnd_t wck2dqo_runtime;
   uint32_rnd_t dis_dqsosc_srx;
   uint32_rnd_t dis_opt_wrecc_collision_flush;
   uint32_rnd_t pageclose;
   uint32_rnd_t rdwr_switch_policy_sel;
   uint32_rnd_t opt_wrcam_fill_level;
   uint32_rnd_t dis_opt_ntt_by_act;
   uint32_rnd_t dis_opt_ntt_by_pre;
   uint32_rnd_t autopre_rmw;
   uint32_rnd_t lpr_num_entries;
   uint32_rnd_t opt_vprw_sch;
   uint32_rnd_t delay_switch_write;
   uint32_rnd_t visible_window_limit_wr;
   uint32_rnd_t visible_window_limit_rd;
   uint32_rnd_t page_hit_limit_wr;
   uint32_rnd_t page_hit_limit_rd;
   uint32_rnd_t wrcam_lowthresh;
   uint32_rnd_t wrcam_highthresh;
   uint32_rnd_t wr_pghit_num_thresh;
   uint32_rnd_t rd_pghit_num_thresh;
   uint32_rnd_t rd_act_idle_gap;
   uint32_rnd_t wr_act_idle_gap;
   uint32_rnd_t rd_page_exp_cycles;
   uint32_rnd_t wr_page_exp_cycles;
   uint32_rnd_t wrecc_cam_lowthresh;
   uint32_rnd_t wrecc_cam_highthresh;
   uint32_rnd_t dis_opt_loaded_wrecc_cam_fill_level;
   uint32_rnd_t dis_opt_valid_wrecc_cam_fill_level;
   uint32_rnd_t dis_auto_ctrlupd_srx;
   uint32_rnd_t dis_auto_ctrlupd;
   uint32_rnd_t dfi_init_complete_en;
   uint32_rnd_t dfi_init_start;
   uint32_rnd_t dis_dyn_adr_tri;
   uint32_rnd_t lp_optimized_write;
   uint32_rnd_t dfi_frequency;
   uint32_rnd_t ecc_region_map;
   uint32_rnd_t blk_channel_idle_time_x32;
   uint32_rnd_t data_poison_en;
   uint32_rnd_t data_poison_bit;
   uint32_rnd_t poison_chip_en;
   uint32_rnd_t ecc_region_parity_lock;
   uint32_rnd_t ecc_region_waste_lock;
   uint32_rnd_t active_blk_channel;
   uint32_rnd_t ecc_syndrome_sel;
   uint32_rnd_t ecc_err_symbol_sel;
   uint32_rnd_t ecc_poison_beats_sel;
   uint32_rnd_t ecc_poison_data_31_0;
   uint32_rnd_t ecc_poison_data_63_32;
   uint32_rnd_t ecc_poison_data_71_64;
   uint32_rnd_t ecc_poison_data_79_72;
   uint32_rnd_t oc_parity_en[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t oc_parity_type[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t par_wdata_slverr_en[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t par_rdata_slverr_en[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t par_addr_slverr_en[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t par_poison_en;
   uint32_rnd_t par_poison_loc_rd_dfi;
   uint32_rnd_t par_poison_loc_rd_iecc_type;
   uint32_rnd_t par_poison_loc_rd_port;
   uint32_rnd_t par_poison_loc_wr_port;
   uint32_rnd_t par_poison_byte_num;
   uint32_rnd_t ocsap_par_en;
   uint32_rnd_t ocsap_poison_en;
   uint32_rnd_t wdataram_addr_poison_loc;
   uint32_rnd_t rdataram_addr_poison_loc;
   uint32_rnd_t wdataram_addr_poison_ctl;
   uint32_rnd_t rdataram_addr_poison_ctl;
   uint32_rnd_t rdataram_addr_poison_port;
   uint32_rnd_t ocecc_en;
   uint32_rnd_t ocecc_fec_en;
   uint32_rnd_t ocecc_wdata_slverr_en;
   uint32_rnd_t ocecc_rdata_slverr_en;
   uint32_rnd_t ocecc_poison_en;
   uint32_rnd_t ocecc_poison_egen_mr_rd_0;
   uint32_rnd_t ocecc_poison_egen_mr_rd_0_byte_num;
   uint32_rnd_t ocecc_poison_egen_xpi_rd_out;
   uint32_rnd_t ocecc_poison_port_num;
   uint32_rnd_t ocecc_poison_egen_mr_rd_1;
   uint32_rnd_t ocecc_poison_egen_mr_rd_1_byte_num;
   uint32_rnd_t ocecc_poison_egen_xpi_rd_0;
   uint32_rnd_t ocecc_poison_ecc_corr_uncorr;
   uint32_rnd_t ocecc_poison_pgen_rd;
   uint32_rnd_t ocecc_poison_pgen_mr_wdata;
   uint32_rnd_t ocecc_poison_pgen_mr_ecc;
   uint32_rnd_t occap_en;
   uint32_rnd_t rd_crc_enable;
   uint32_rnd_t wr_crc_enable;
   uint32_rnd_t retry_add_rd_lat_en;
   uint32_rnd_t retry_add_rd_lat;
   uint32_rnd_t dfi_t_phy_rdlat;
   uint32_rnd_t wr_link_ecc_enable[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd_link_ecc_enable[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd_link_ecc_err_byte_sel[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd_link_ecc_err_rank_sel[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t selfref_wo_ref_pending[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dis_max_rank_rd_opt;
   uint32_rnd_t dis_max_rank_wr_opt;
   uint32_rnd_t rcd_weak_drive;
   uint32_rnd_t dm_en[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr_dbi_en[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd_dbi_en[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd_data_copy_en;
   uint32_rnd_t wr_data_copy_en;
   uint32_rnd_t wr_data_x_en;
   uint32_rnd_t skip_dram_init[UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t read_reorder_bypass_en[UMCTL2_A_NPORTS];
   uint32_rnd_t rdwr_ordered_en[UMCTL2_A_NPORTS];
   uint32_rnd_t id_mask[UMCTL2_A_NPORTS][16];
   uint32_rnd_t id_value[UMCTL2_A_NPORTS][16];
   uint32_rnd_t rqos_map_level1[UMCTL2_A_NPORTS];
   uint32_rnd_t rqos_map_level2[UMCTL2_A_NPORTS];
   uint32_rnd_t rqos_map_region0[UMCTL2_A_NPORTS];
   uint32_rnd_t rqos_map_region1[UMCTL2_A_NPORTS];
   uint32_rnd_t rqos_map_region2[UMCTL2_A_NPORTS];
   uint32_rnd_t rqos_map_timeoutb[UMCTL2_A_NPORTS];
   uint32_rnd_t rqos_map_timeoutr[UMCTL2_A_NPORTS];
   uint32_rnd_t wqos_map_level1[UMCTL2_A_NPORTS];
   uint32_rnd_t wqos_map_level2[UMCTL2_A_NPORTS];
   uint32_rnd_t wqos_map_region0[UMCTL2_A_NPORTS];
   uint32_rnd_t wqos_map_region1[UMCTL2_A_NPORTS];
   uint32_rnd_t wqos_map_region2[UMCTL2_A_NPORTS];
   uint32_rnd_t wqos_map_timeout1[UMCTL2_A_NPORTS];
   uint32_rnd_t wqos_map_timeout2[UMCTL2_A_NPORTS];
   uint32_rnd_t t_ras_min[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ras_max[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_faw[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr2pre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rc[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd2pre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr2rd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd2wr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t read_latency[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t write_latency[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr2mr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd2mr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rrd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rcd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_cke[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ckesr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_cksre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_cksrx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ckcsx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_csh[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xs_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xs_dll_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xs_abort_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xs_fast_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr2rd_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rrd_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ddr4_wr_preamble[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_gear_hold[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_gear_setup[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_cmd_gear[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_sync_gear[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ckmpe[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mpx_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mpx_lh[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t post_mpsm_gap_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mrd_pda[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_cmdcke[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr_mpr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ppd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_w2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_mw[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t odtloff[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xsr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_osco[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_stab_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t en_hwffc_t_stab[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t en_dfi_lp_t_stab[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rrd_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_faw_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rp_ca_parity[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_vrcg_disable[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_vrcg_enable[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mpdpxact[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mpsmx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_pd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_pda_h[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_pda_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_pda_dqs_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_pda_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_pda_latch[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_csl_srexit[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_csh_srexit[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_casrx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_cpded[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_osco_ddr5[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_vrefca_cs[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mpc_hold[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mpc_setup[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mpc_cs[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_csl[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_dpr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_dpr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t max_wr_sync[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t max_rd_sync[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd2wr_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t bank_org[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rda2pre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wra2pre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t lpddr4_diff_bank_rwa2pre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_r[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_w[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_r_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_w_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mrr2mpc[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_srx2srx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_cpded2srx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_cssr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ckact[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ckoff[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mrr2rd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mrr2wr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mrr2mrw[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_r_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_w_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_r_s_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_w_s_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ras_min_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_faw_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2pre_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rc_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd2pre_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr2rd_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd2wr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_dpr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_dlr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_dpr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_dlr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rp_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rrd_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rcd_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr2rd_s_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rrd_s_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ppd_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_w2_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ccd_dlr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rrd_dlr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_faw_dlr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rp_ca_parity_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xs_x32_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xs_dll_x32_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xs_abort_x32_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_xs_fast_x32_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mr_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_mrr2mpc_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r0r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r1r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r0r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r1r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r0r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r1r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r0r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r1r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r0r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r2r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r0r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r2r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r0r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r2r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r0r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r2r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r0r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r3r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r0r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r3r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r0r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r3r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r0r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r3r0[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r1r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r2r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r1r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r2r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r1r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r2r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r1r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r2r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r1r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r3r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r1r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r3r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r1r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r3r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r1r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r3r1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r2r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2rd_gap_r3r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r2r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2rd_gap_r3r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r2r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rd2wr_gap_r3r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r2r3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_wr2wr_gap_r3r2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_ras_min_mram[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_faw_mram[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rc_mram[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rp_mram[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rrd_mram[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rcd_mram[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_rrd_s_mram[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t emr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t emr3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t emr2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mr5[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mr4[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mr6[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mr22[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_tphy_wrlat[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_tphy_wrdata[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_rddata_en[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_ctrl_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_dram_clk_enable[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_dram_clk_disable[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_wrdata_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_parin_lat[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_cmd_lat[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_tphy_wrcslat[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_tphy_rdcslat[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_geardown_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_twck_dis[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_twck_en_fs[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_twck_en_wr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_twck_en_rd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_twck_toggle_post[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_twck_toggle_cs[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_twck_toggle[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_twck_fast_toggle[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t dfi_t_2n_mode_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ctrl_word_1[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ctrl_word_2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ctrl_word_3[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ctrl_word_4[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ctrl_word_5[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ctrl_word_6[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ctrl_word_7[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t ctrl_word_8[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t mr4_read_interval[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t derated_t_rrd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t derated_t_rp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t derated_t_ras_min[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t derated_t_rcd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t derated_t_rc[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t hw_lp_idle_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t hpr_max_starve[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t hpr_xact_run_length[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t lpr_max_starve[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t lpr_xact_run_length[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t w_max_starve[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t w_xact_run_length[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t diff_rank_rd_gap[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t diff_rank_wr_gap[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr2rd_dr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd2wr_dr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t powerdown_to_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t selfref_to_x32[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd_odt_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t rd_odt_hold[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr_odt_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t wr_odt_hold[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t retry_fifo_max_hold_timer_x4[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_crc_alert_pw_max[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_par_alert_pw_max[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
   uint32_rnd_t t_csalt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
} mctl_qdyn_cfg_t;
#endif

