// coreBuilder: This is an automated C header file. DO NOT EDIT.
#ifndef __DWC_CINIT_REG_STRUCT__H__
#define __DWC_CINIT_REG_STRUCT__H__
typedef struct tag_REGB_DDRC_CH0_MSTR0_struct {
   uint32_t ddr4;
   uint32_t lpddr4;
   uint32_t ddr5;
   uint32_t lpddr5;
   uint32_t burst_mode;
   uint32_t burstchop;
   uint32_t en_2t_timing_mode;
   uint32_t data_bus_width;
   uint32_t dll_off_mode;
   uint32_t burst_rdwr;
   uint32_t active_logical_ranks;
   uint32_t active_ranks;
   uint32_t device_config;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR0_struct_t;

#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_DDRC_CH0_MSTR1_struct {
   uint32_t rank_tmgreg_sel;
   uint32_t rfc_tmgreg_sel;
   uint32_t alt_addrmap_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_FREQUENCY_NUM_GT_1
typedef struct tag_REGB_DDRC_CH0_MSTR2_struct {
   uint32_t target_frequency;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR2_struct_t;

#endif //UMCTL2_FREQUENCY_NUM_GT_1
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_MSTR3_struct {
   uint32_t geardown_mode;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR3_struct_t;

#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH0_MSTR4_struct {
   uint32_t wck_on;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MSTR4_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH0_MRCTRL0_struct {
   uint32_t mr_type;
   uint32_t mpr_en;
   uint32_t pda_en;
   uint32_t sw_init_int;
   uint32_t mr_rank;
   uint32_t mr_addr;
   uint32_t mr_cid;
   uint32_t mrr_done_clr;
   uint32_t pba_mode;
   uint32_t mr_wr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MRCTRL0_struct_t;

typedef struct tag_REGB_DDRC_CH0_MRCTRL1_struct {
   uint32_t mr_data;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MRCTRL1_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_MRCTRL2_struct {
   uint32_t mr_device_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MRCTRL2_struct_t;

#endif //DDRCTL_DDR
#ifndef MEMC_NUM_RANKS_1_OR_2_OR_4
typedef struct tag_REGB_DDRC_CH0_MRCTRL3_struct {
   uint32_t mr_rank_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_MRCTRL3_struct_t;

#endif //MEMC_NUM_RANKS_1_OR_2_OR_4
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH0_DERATECTL0_struct {
   uint32_t derate_enable;
   uint32_t lpddr4_refresh_mode;
   uint32_t derate_mr4_pause_fc;
   uint32_t dis_trefi_x6x8;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct tag_REGB_DDRC_CH0_DERATECTL1_struct {
   uint32_t active_derate_byte_rank0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL1_struct_t;

#endif //DDRCTL_DDR_OR_MEMC_LPDDR4
#ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH0_DERATECTL2_struct {
   uint32_t active_derate_byte_rank1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_DDR_OR_MEMC_LPDDR4
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_DERATECTL3_struct {
   uint32_t active_derate_byte_rank2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_DERATECTL4_struct {
   uint32_t active_derate_byte_rank3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct tag_REGB_DDRC_CH0_DERATECTL5_struct {
   uint32_t derate_temp_limit_intr_en;
   uint32_t derate_temp_limit_intr_clr;
   uint32_t derate_temp_limit_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL5_struct_t;

#endif //DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct tag_REGB_DDRC_CH0_DERATECTL6_struct {
   uint32_t derate_mr4_tuf_dis;
   uint32_t derate_low_temp_limit;
   uint32_t derate_high_temp_limit;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATECTL6_struct_t;

#ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct tag_REGB_DDRC_CH0_DERATEDBGCTL_struct {
   uint32_t dbg_mr4_grp_sel;
   uint32_t dbg_mr4_rank_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DERATEDBGCTL_struct_t;

#endif //DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct tag_REGB_DDRC_CH0_PWRCTL_struct {
   uint32_t selfref_en;
   uint32_t powerdown_en;
   uint32_t actv_pd_en;
   uint32_t en_dfi_dram_clk_disable;
   uint32_t mpsm_en;
   uint32_t selfref_sw;
   uint32_t stay_in_selfref;
   uint32_t dis_cam_drain_selfref;
   uint32_t lpddr4_sr_allowed;
   uint32_t dsm_en;
   uint32_t srpd_en;
   uint32_t mpsm_pd_en;
   uint32_t mpsm_deep_pd_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PWRCTL_struct_t;

typedef struct tag_REGB_DDRC_CH0_HWLPCTL_struct {
   uint32_t hw_lp_en;
   uint32_t hw_lp_exit_idle_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_HWLPCTL_struct_t;

typedef struct tag_REGB_DDRC_CH0_RFSHMOD0_struct {
   uint32_t refresh_burst;
   uint32_t per_bank_refresh;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_RFSHMOD0_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_RFSHMOD1_struct {
   uint32_t same_bank_refresh;
   uint32_t tcr_refab_thr;
   uint32_t fgr_mode;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_RFSHMOD1_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_RFSHCTL0_struct {
   uint32_t dis_auto_refresh;
   uint32_t refresh_update_level;
   uint32_t rank_dis_refresh;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_RFSHCTL0_struct_t;

typedef struct tag_REGB_DDRC_CH0_ZQCTL0_struct {
   uint32_t dis_mpsmx_zqcl;
   uint32_t zq_resistor_shared;
   uint32_t dis_auto_zq;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ZQCTL0_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH0_ZQCTL1_struct {
   uint32_t zq_reset;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ZQCTL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH0_ZQCTL2_struct {
   uint32_t dis_srx_zqcl;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ZQCTL2_struct_t;

#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_DDRC_CH0_DQSOSCRUNTIME_struct {
   uint32_t dqsosc_runtime;
   uint32_t wck2dqo_runtime;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQSOSCRUNTIME_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_DDRC_CH0_DQSOSCCFG0_struct {
   uint32_t dis_dqsosc_srx;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQSOSCCFG0_struct_t;

#endif //LPDDR45_DQSOSC_EN
typedef struct tag_REGB_DDRC_CH0_SCHED0_struct {
   uint32_t dis_opt_wrecc_collision_flush;
   uint32_t prefer_write;
   uint32_t pageclose;
   uint32_t rdwr_switch_policy_sel;
   uint32_t opt_wrcam_fill_level;
   uint32_t dis_opt_ntt_by_act;
   uint32_t dis_opt_ntt_by_pre;
   uint32_t autopre_rmw;
   uint32_t lpr_num_entries;
   uint32_t lpddr4_opt_act_timing;
   uint32_t opt_vprw_sch;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED0_struct_t;

#ifdef MEMC_ENH_CAM_PTR
typedef struct tag_REGB_DDRC_CH0_SCHED1_struct {
   uint32_t delay_switch_write;
   uint32_t visible_window_limit_wr;
   uint32_t visible_window_limit_rd;
   uint32_t page_hit_limit_wr;
   uint32_t page_hit_limit_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED1_struct_t;

#endif //MEMC_ENH_CAM_PTR
#ifdef UMCTL2_DYN_BSM
typedef struct tag_REGB_DDRC_CH0_SCHED2_struct {
   uint32_t dyn_bsm_mode;
   uint32_t dealloc_bsm_thr;
   uint32_t dealloc_num_bsm_m1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED2_struct_t;

#endif //UMCTL2_DYN_BSM
#ifdef MEMC_ENH_RDWR_SWITCH
typedef struct tag_REGB_DDRC_CH0_SCHED3_struct {
   uint32_t wrcam_lowthresh;
   uint32_t wrcam_highthresh;
   uint32_t wr_pghit_num_thresh;
   uint32_t rd_pghit_num_thresh;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED3_struct_t;

#endif //MEMC_ENH_RDWR_SWITCH
#ifdef MEMC_ENH_RDWR_SWITCH
typedef struct tag_REGB_DDRC_CH0_SCHED4_struct {
   uint32_t rd_act_idle_gap;
   uint32_t wr_act_idle_gap;
   uint32_t rd_page_exp_cycles;
   uint32_t wr_page_exp_cycles;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED4_struct_t;

#endif //MEMC_ENH_RDWR_SWITCH
#ifdef MEMC_ENH_RDWR_SWITCH
#ifdef MEMC_INLINE_ECC
typedef struct tag_REGB_DDRC_CH0_SCHED5_struct {
   uint32_t wrecc_cam_lowthresh;
   uint32_t wrecc_cam_highthresh;
   uint32_t dis_opt_loaded_wrecc_cam_fill_level;
   uint32_t dis_opt_valid_wrecc_cam_fill_level;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_SCHED5_struct_t;

#endif //MEMC_INLINE_ECC
#endif //MEMC_ENH_RDWR_SWITCH
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_DDRC_CH0_HWFFCCTL_struct {
   uint32_t hwffc_en;
   uint32_t init_fsp;
   uint32_t init_vrcg;
   uint32_t target_vrcg;
   uint32_t cke_power_down_mode;
   uint32_t power_saving_ctrl_word;
   uint32_t ctrl_word_num;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_HWFFCCTL_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
typedef struct tag_REGB_DDRC_CH0_DQMAP0_struct {
   uint32_t dq_nibble_map_0_3;
   uint32_t dq_nibble_map_4_7;
   uint32_t dq_nibble_map_8_11;
   uint32_t dq_nibble_map_12_15;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP0_struct_t;

#endif //UMCTL2_DQ_MAPPING
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
#ifdef MEMC_DRAM_DATA_WIDTH_GT_23
typedef struct tag_REGB_DDRC_CH0_DQMAP1_struct {
   uint32_t dq_nibble_map_16_19;
   uint32_t dq_nibble_map_20_23;
   uint32_t dq_nibble_map_24_27;
   uint32_t dq_nibble_map_28_31;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP1_struct_t;

#endif //MEMC_DRAM_DATA_WIDTH_GT_23
#endif //UMCTL2_DQ_MAPPING
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
#ifdef MEMC_DRAM_DATA_WIDTH_GT_39
typedef struct tag_REGB_DDRC_CH0_DQMAP2_struct {
   uint32_t dq_nibble_map_32_35;
   uint32_t dq_nibble_map_36_39;
   uint32_t dq_nibble_map_40_43;
   uint32_t dq_nibble_map_44_47;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP2_struct_t;

#endif //MEMC_DRAM_DATA_WIDTH_GT_39
#endif //UMCTL2_DQ_MAPPING
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
#ifdef MEMC_DRAM_DATA_WIDTH_GT_55
typedef struct tag_REGB_DDRC_CH0_DQMAP3_struct {
   uint32_t dq_nibble_map_48_51;
   uint32_t dq_nibble_map_52_55;
   uint32_t dq_nibble_map_56_59;
   uint32_t dq_nibble_map_60_63;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP3_struct_t;

#endif //MEMC_DRAM_DATA_WIDTH_GT_55
#endif //UMCTL2_DQ_MAPPING
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
#ifdef MEMC_DRAM_DATA_WIDTH_72_OR_MEMC_SIDEBAND_ECC
typedef struct tag_REGB_DDRC_CH0_DQMAP4_struct {
   uint32_t dq_nibble_map_cb_0_3;
   uint32_t dq_nibble_map_cb_4_7;
   uint32_t dq_nibble_map_cb_8_11;
   uint32_t dq_nibble_map_cb_12_15;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP4_struct_t;

#endif //MEMC_DRAM_DATA_WIDTH_72_OR_MEMC_SIDEBAND_ECC
#endif //UMCTL2_DQ_MAPPING
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
#ifdef UMCTL2_DQ_MAPPING
typedef struct tag_REGB_DDRC_CH0_DQMAP5_struct {
   uint32_t dis_dq_rank_swap;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DQMAP5_struct_t;

#endif //UMCTL2_DQ_MAPPING
#endif //DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_DFILPCFG0_struct {
   uint32_t dfi_lp_en_pd;
   uint32_t dfi_lp_en_sr;
   uint32_t dfi_lp_en_dsm;
   uint32_t dfi_lp_en_mpsm;
   uint32_t dfi_lp_en_data;
   uint32_t dfi_lp_data_req_en;
   uint32_t dfi_lp_extra_gap_wr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFILPCFG0_struct_t;

typedef struct tag_REGB_DDRC_CH0_DFIUPD0_struct {
   uint32_t dfi_phyupd_en;
   uint32_t ctrlupd_pre_srx;
   uint32_t dis_auto_ctrlupd_srx;
   uint32_t dis_auto_ctrlupd;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFIUPD0_struct_t;

#ifdef UMCTL2_DFI_PHYUPD_WAIT_IDLE
typedef struct tag_REGB_DDRC_CH0_DFIUPD1_struct {
   uint32_t dfi_phyupd_type0_wait_idle;
   uint32_t dfi_phyupd_type1_wait_idle;
   uint32_t dfi_phyupd_type2_wait_idle;
   uint32_t dfi_phyupd_type3_wait_idle;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFIUPD1_struct_t;

#endif //UMCTL2_DFI_PHYUPD_WAIT_IDLE
typedef struct tag_REGB_DDRC_CH0_DFIMISC_struct {
   uint32_t dfi_init_complete_en;
   uint32_t phy_dbi_mode;
   uint32_t dfi_data_cs_polarity;
   uint32_t share_dfi_dram_clk_disable;
   uint32_t dfi_init_start;
   uint32_t dis_dyn_adr_tri;
   uint32_t lp_optimized_write;
   uint32_t dfi_frequency;
   uint32_t dfi_channel_mode;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFIMISC_struct_t;

typedef struct tag_REGB_DDRC_CH0_DFIPHYMSTR_struct {
   uint32_t dfi_phymstr_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFIPHYMSTR_struct_t;

typedef struct tag_REGB_DDRC_CH0_DFI0MSGCTL0_struct {
   uint32_t dfi0_ctrlmsg_data;
   uint32_t dfi0_ctrlmsg_cmd;
   uint32_t dfi0_ctrlmsg_tout_clr;
   uint32_t dfi0_ctrlmsg_req;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DFI0MSGCTL0_struct_t;

#ifdef UMCTL2_INCL_ARB
#ifdef UMCTL2_A_AXI
typedef struct tag_REGB_DDRC_CH0_POISONCFG_struct {
   uint32_t wr_poison_slverr_en;
   uint32_t wr_poison_intr_en;
   uint32_t wr_poison_intr_clr;
   uint32_t rd_poison_slverr_en;
   uint32_t rd_poison_intr_en;
   uint32_t rd_poison_intr_clr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_POISONCFG_struct_t;

#endif //UMCTL2_A_AXI
#endif //UMCTL2_INCL_ARB
#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH0_ECCCFG0_struct {
   uint32_t ecc_mode;
   uint32_t test_mode;
   uint32_t dis_scrub;
   uint32_t ecc_ap_en;
   uint32_t ecc_region_remap_en;
   uint32_t ecc_region_map;
   uint32_t blk_channel_idle_time_x32;
   uint32_t ecc_ap_err_threshold;
   uint32_t ecc_region_map_other;
   uint32_t ecc_region_map_granu;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCCFG0_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH0_ECCCFG1_struct {
   uint32_t data_poison_en;
   uint32_t data_poison_bit;
   uint32_t poison_chip_en;
   uint32_t ecc_region_parity_lock;
   uint32_t ecc_region_waste_lock;
   uint32_t blk_channel_active_term;
   uint32_t active_blk_channel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCCFG1_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH0_ECCCTL_struct {
   uint32_t ecc_corrected_err_clr;
   uint32_t ecc_uncorrected_err_clr;
   uint32_t ecc_corr_err_cnt_clr;
   uint32_t ecc_uncorr_err_cnt_clr;
   uint32_t ecc_ap_err_intr_clr;
   uint32_t ecc_corrected_err_intr_en;
   uint32_t ecc_uncorrected_err_intr_en;
   uint32_t ecc_ap_err_intr_en;
   uint32_t ecc_corrected_err_intr_force;
   uint32_t ecc_uncorrected_err_intr_force;
   uint32_t ecc_ap_err_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCCTL_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH0_ECCPOISONADDR0_struct {
   uint32_t ecc_poison_col;
   uint32_t ecc_poison_cid;
   uint32_t ecc_poison_rank;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONADDR0_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH0_ECCPOISONADDR1_struct {
   uint32_t ecc_poison_row;
   uint32_t ecc_poison_bank;
   uint32_t ecc_poison_bg;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONADDR1_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH0_ADVECCINDEX_struct {
   uint32_t ecc_syndrome_sel;
   uint32_t ecc_err_symbol_sel;
   uint32_t ecc_poison_beats_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ADVECCINDEX_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH0_ECCPOISONPAT0_struct {
   uint32_t ecc_poison_data_31_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONPAT0_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_DRAM_DATA_WIDTH_64
typedef struct tag_REGB_DDRC_CH0_ECCPOISONPAT1_struct {
   uint32_t ecc_poison_data_63_32;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONPAT1_struct_t;

#endif //MEMC_DRAM_DATA_WIDTH_64
#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH0_ECCPOISONPAT2_struct {
   uint32_t ecc_poison_data_71_64;
   uint32_t ecc_poison_data_79_72;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ECCPOISONPAT2_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef UMCTL2_OCPAR_OR_OCECC_EN_1
typedef struct tag_REGB_DDRC_CH0_OCPARCFG0_struct {
   uint32_t oc_parity_en;
   uint32_t oc_parity_type;
   uint32_t par_wdata_err_intr_en;
   uint32_t par_wdata_slverr_en;
   uint32_t par_wdata_err_intr_clr;
   uint32_t par_wdata_err_intr_force;
   uint32_t par_rdata_slverr_en;
   uint32_t par_rdata_err_intr_en;
   uint32_t par_rdata_err_intr_clr;
   uint32_t par_rdata_err_intr_force;
   uint32_t par_addr_slverr_en;
   uint32_t par_waddr_err_intr_en;
   uint32_t par_waddr_err_intr_clr;
   uint32_t par_raddr_err_intr_en;
   uint32_t par_raddr_err_intr_clr;
   uint32_t par_waddr_err_intr_force;
   uint32_t par_raddr_err_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCPARCFG0_struct_t;

#endif //UMCTL2_OCPAR_OR_OCECC_EN_1
#ifdef UMCTL2_OCPAR_EN_1
typedef struct tag_REGB_DDRC_CH0_OCPARCFG1_struct {
   uint32_t par_poison_en;
   uint32_t par_poison_loc_rd_dfi;
   uint32_t par_poison_loc_rd_iecc_type;
   uint32_t par_poison_loc_rd_port;
   uint32_t par_poison_loc_wr_port;
   uint32_t par_poison_byte_num;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCPARCFG1_struct_t;

#endif //UMCTL2_OCPAR_EN_1
#ifdef DDRCTL_OCSAP_EN_1
typedef struct tag_REGB_DDRC_CH0_OCSAPCFG0_struct {
   uint32_t ocsap_par_en;
   uint32_t ocsap_poison_en;
   uint32_t wdataram_addr_poison_loc;
   uint32_t rdataram_addr_poison_loc;
   uint32_t wdataram_addr_poison_ctl;
   uint32_t rdataram_addr_poison_ctl;
   uint32_t rdataram_addr_poison_port;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCSAPCFG0_struct_t;

#endif //DDRCTL_OCSAP_EN_1
#ifdef UMCTL2_OCECC_EN_1
typedef struct tag_REGB_DDRC_CH0_OCECCCFG0_struct {
   uint32_t ocecc_en;
   uint32_t ocecc_fec_en;
   uint32_t ocecc_uncorrected_err_intr_en;
   uint32_t ocecc_wdata_slverr_en;
   uint32_t ocecc_uncorrected_err_intr_clr;
   uint32_t ocecc_uncorrected_err_intr_force;
   uint32_t ocecc_corrected_err_intr_en;
   uint32_t ocecc_rdata_slverr_en;
   uint32_t ocecc_corrected_err_intr_clr;
   uint32_t ocecc_corrected_err_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCECCCFG0_struct_t;

#endif //UMCTL2_OCECC_EN_1
#ifdef UMCTL2_OCECC_EN_1
typedef struct tag_REGB_DDRC_CH0_OCECCCFG1_struct {
   uint32_t ocecc_poison_en;
   uint32_t ocecc_poison_egen_mr_rd_0;
   uint32_t ocecc_poison_egen_mr_rd_0_byte_num;
   uint32_t ocecc_poison_egen_xpi_rd_out;
   uint32_t ocecc_poison_port_num;
   uint32_t ocecc_poison_egen_mr_rd_1;
   uint32_t ocecc_poison_egen_mr_rd_1_byte_num;
   uint32_t ocecc_poison_egen_xpi_rd_0;
   uint32_t ocecc_poison_ecc_corr_uncorr;
   uint32_t ocecc_poison_pgen_rd;
   uint32_t ocecc_poison_pgen_mr_wdata;
   uint32_t ocecc_poison_pgen_mr_ecc;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCECCCFG1_struct_t;

#endif //UMCTL2_OCECC_EN_1
#ifdef UMCTL2_OCCAP_EN_1
typedef struct tag_REGB_DDRC_CH0_OCCAPCFG_struct {
   uint32_t occap_en;
   uint32_t occap_arb_intr_en;
   uint32_t occap_arb_intr_clr;
   uint32_t occap_arb_intr_force;
   uint32_t occap_arb_cmp_poison_seq;
   uint32_t occap_arb_cmp_poison_parallel;
   uint32_t occap_arb_cmp_poison_err_inj;
   uint32_t occap_arb_raq_poison_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCCAPCFG_struct_t;

#endif //UMCTL2_OCCAP_EN_1
#ifdef UMCTL2_OCCAP_EN_1
typedef struct tag_REGB_DDRC_CH0_OCCAPCFG1_struct {
   uint32_t occap_ddrc_data_intr_en;
   uint32_t occap_ddrc_data_intr_clr;
   uint32_t occap_ddrc_data_intr_force;
   uint32_t occap_ddrc_data_poison_seq;
   uint32_t occap_ddrc_data_poison_parallel;
   uint32_t occap_ddrc_data_poison_err_inj;
   uint32_t occap_ddrc_ctrl_intr_en;
   uint32_t occap_ddrc_ctrl_intr_clr;
   uint32_t occap_ddrc_ctrl_intr_force;
   uint32_t occap_ddrc_ctrl_poison_seq;
   uint32_t occap_ddrc_ctrl_poison_parallel;
   uint32_t occap_ddrc_ctrl_poison_err_inj;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OCCAPCFG1_struct_t;

#endif //UMCTL2_OCCAP_EN_1
typedef struct tag_REGB_DDRC_CH0_CRCPARCTL0_struct {
   uint32_t dfi_alert_err_int_en;
   uint32_t dfi_alert_err_int_clr;
   uint32_t dfi_alert_err_cnt_clr;
   uint32_t dfi_alert_err_fatl_int_clr;
   uint32_t dfi_alert_err_max_reached_int_clr;
   uint32_t retry_ctrlupd_enable;
   uint32_t retry_ctrlupd_wait;
   uint32_t rd_crc_err_max_reached_int_en;
   uint32_t rd_crc_err_max_reached_int_clr;
   uint32_t rd_crc_err_cnt_clr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CRCPARCTL0_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_CRCPARCTL1_struct {
   uint32_t parity_enable;
   uint32_t rd_crc_enable;
   uint32_t wr_crc_enable;
   uint32_t crc_inc_dm;
   uint32_t crc_parity_retry_enable;
   uint32_t alert_wait_for_sw;
   uint32_t caparity_disable_before_sr;
   uint32_t retry_add_rd_lat_en;
   uint32_t retry_add_rd_lat;
   uint32_t dfi_t_phy_rdlat;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CRCPARCTL1_struct_t;

#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_CRCPARCTL2_struct {
   uint32_t dfi_alert_err_max_reached_th;
   uint32_t rd_crc_err_max_reached_th;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CRCPARCTL2_struct_t;

#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY_OR_DDRCTL_CA_PARITY
typedef struct tag_REGB_DDRC_CH0_CAPARPOISONCTL_struct {
   uint32_t capar_poison_inject_en;
   uint32_t capar_poison_cmdtype;
   uint32_t capar_poison_position;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CAPARPOISONCTL_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY_OR_DDRCTL_CA_PARITY
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_CRCPOISONCTL0_struct {
   uint32_t crc_poison_inject_en;
   uint32_t crc_poison_type;
   uint32_t crc_poison_nibble;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CRCPOISONCTL0_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_REGPAR_EN_1
typedef struct tag_REGB_DDRC_CH0_REGPARCFG_struct {
   uint32_t reg_par_en;
   uint32_t reg_par_err_intr_en;
   uint32_t reg_par_err_intr_clr;
   uint32_t reg_par_err_intr_force;
   uint32_t reg_par_poison_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_REGPARCFG_struct_t;

#endif //UMCTL2_REGPAR_EN_1
#ifdef MEMC_LINK_ECC
typedef struct tag_REGB_DDRC_CH0_LNKECCCTL0_struct {
   uint32_t wr_link_ecc_enable;
   uint32_t rd_link_ecc_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_LNKECCCTL0_struct_t;

#endif //MEMC_LINK_ECC
#ifdef MEMC_LINK_ECC
typedef struct tag_REGB_DDRC_CH0_LNKECCCTL1_struct {
   uint32_t rd_link_ecc_corr_intr_en;
   uint32_t rd_link_ecc_corr_intr_clr;
   uint32_t rd_link_ecc_corr_cnt_clr;
   uint32_t rd_link_ecc_corr_intr_force;
   uint32_t rd_link_ecc_uncorr_intr_en;
   uint32_t rd_link_ecc_uncorr_intr_clr;
   uint32_t rd_link_ecc_uncorr_cnt_clr;
   uint32_t rd_link_ecc_uncorr_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_LNKECCCTL1_struct_t;

#endif //MEMC_LINK_ECC
#ifdef MEMC_LINK_ECC
typedef struct tag_REGB_DDRC_CH0_LNKECCPOISONCTL0_struct {
   uint32_t linkecc_poison_inject_en;
   uint32_t linkecc_poison_type;
   uint32_t linkecc_poison_rw;
   uint32_t linkecc_poison_dmi_sel;
   uint32_t linkecc_poison_byte_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_LNKECCPOISONCTL0_struct_t;

#endif //MEMC_LINK_ECC
#ifdef MEMC_LINK_ECC
typedef struct tag_REGB_DDRC_CH0_LNKECCINDEX_struct {
   uint32_t rd_link_ecc_err_byte_sel;
   uint32_t rd_link_ecc_err_rank_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_LNKECCINDEX_struct_t;

#endif //MEMC_LINK_ECC
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL0_struct {
   uint32_t init_done;
   uint32_t dbg_st_en;
   uint32_t bist_st_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL0_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL1_struct {
   uint32_t pre_sb_enable;
   uint32_t pre_ab_enable;
   uint32_t pre_slot_config;
   uint32_t wr_min_gap;
   uint32_t rd_min_gap;
   uint32_t prank_tmgreg_set_sel;
   uint32_t non_dyn_sched_en;
   uint32_t selfref_wo_ref_pending;
   uint32_t dfi_alert_assertion_mode;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL1_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL2_struct {
   uint32_t active_prank_bitmap;
   uint32_t pads0_rsvd0;
   uint32_t lrank_rd2rd_gap;
   uint32_t lrank_wr2wr_gap;
   uint32_t lrank_rd2wr_gap;
   uint32_t lrank_wr2rd_gap;
   uint32_t pads0_rsvd1;
   uint32_t t_ppd_cnt_en;
   uint32_t pads0_rsvd2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL2_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL3_struct {
   uint32_t bg_bit_mask;
   uint32_t bank_bit_mask;
   uint32_t lrank_bit_mask;
   uint32_t prank_bit_mask;
   uint32_t pads1_rsvd1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL4_struct {
   uint32_t ci_mrr_des1;
   uint32_t ci_mrr_des2;
   uint32_t ci_mrw_des1;
   uint32_t ci_mrw_des2;
   uint32_t ci_mpc_des1;
   uint32_t ci_mpc_des2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL4_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL5_struct {
   uint32_t base_timer_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL5_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL6_struct {
   uint32_t base_timer;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL6_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL7_struct {
   uint32_t glb_blk0_en;
   uint32_t glb_blk1_en;
   uint32_t glb_blk2_en;
   uint32_t glb_blk3_en;
   uint32_t glb_blk4_en;
   uint32_t glb_blk5_en;
   uint32_t glb_blk6_en;
   uint32_t glb_blk7_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL7_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL8_struct {
   uint32_t rank_blk0_en;
   uint32_t rank_blk1_en;
   uint32_t rank_blk2_en;
   uint32_t rank_blk3_en;
   uint32_t rank_blk4_en;
   uint32_t rank_blk5_en;
   uint32_t rank_blk6_en;
   uint32_t rank_blk7_en;
   uint32_t rank_blk8_en;
   uint32_t rank_blk9_en;
   uint32_t rank_blk10_en;
   uint32_t rank_blk11_en;
   uint32_t rank_blk12_en;
   uint32_t rank_blk13_en;
   uint32_t rank_blk14_en;
   uint32_t rank_blk15_en;
   uint32_t rank_blk16_en;
   uint32_t rank_blk17_en;
   uint32_t rank_blk18_en;
   uint32_t rank_blk19_en;
   uint32_t rank_blk20_en;
   uint32_t rank_blk21_en;
   uint32_t rank_blk22_en;
   uint32_t rank_blk23_en;
   uint32_t rank_blk24_en;
   uint32_t rank_blk25_en;
   uint32_t rank_blk26_en;
   uint32_t rank_blk27_en;
   uint32_t rank_blk28_en;
   uint32_t rank_blk29_en;
   uint32_t rank_blk30_en;
   uint32_t rank_blk31_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL8_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL9_struct {
   uint32_t glb_blk0_trig;
   uint32_t glb_blk1_trig;
   uint32_t glb_blk2_trig;
   uint32_t glb_blk3_trig;
   uint32_t glb_blk4_trig;
   uint32_t glb_blk5_trig;
   uint32_t glb_blk6_trig;
   uint32_t glb_blk7_trig;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL9_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL10_struct {
   uint32_t rank_blk0_trig;
   uint32_t rank_blk1_trig;
   uint32_t rank_blk2_trig;
   uint32_t rank_blk3_trig;
   uint32_t rank_blk4_trig;
   uint32_t rank_blk5_trig;
   uint32_t rank_blk6_trig;
   uint32_t rank_blk7_trig;
   uint32_t rank_blk8_trig;
   uint32_t rank_blk9_trig;
   uint32_t rank_blk10_trig;
   uint32_t rank_blk11_trig;
   uint32_t rank_blk12_trig;
   uint32_t rank_blk13_trig;
   uint32_t rank_blk14_trig;
   uint32_t rank_blk15_trig;
   uint32_t rank_blk16_trig;
   uint32_t rank_blk17_trig;
   uint32_t rank_blk18_trig;
   uint32_t rank_blk19_trig;
   uint32_t rank_blk20_trig;
   uint32_t rank_blk21_trig;
   uint32_t rank_blk22_trig;
   uint32_t rank_blk23_trig;
   uint32_t rank_blk24_trig;
   uint32_t rank_blk25_trig;
   uint32_t rank_blk26_trig;
   uint32_t rank_blk27_trig;
   uint32_t rank_blk28_trig;
   uint32_t rank_blk29_trig;
   uint32_t rank_blk30_trig;
   uint32_t rank_blk31_trig;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL10_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL11_struct {
   uint32_t powerdown_entry_ba_0;
   uint32_t powerdown_entry_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL11_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL12_struct {
   uint32_t powerdown_exit_ba_0;
   uint32_t powerdown_exit_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL12_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH0_PASCTL13_struct {
   uint32_t powerdown_entry_ba_1;
   uint32_t powerdown_entry_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL13_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH0_PASCTL14_struct {
   uint32_t powerdown_exit_ba_1;
   uint32_t powerdown_exit_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL14_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL15_struct {
   uint32_t powerdown_entry_ba_2;
   uint32_t powerdown_entry_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL15_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL16_struct {
   uint32_t powerdown_exit_ba_2;
   uint32_t powerdown_exit_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL16_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL17_struct {
   uint32_t powerdown_entry_ba_3;
   uint32_t powerdown_entry_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL17_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL18_struct {
   uint32_t powerdown_exit_ba_3;
   uint32_t powerdown_exit_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL18_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL20_struct {
   uint32_t selfref_entry1_ba_0;
   uint32_t selfref_entry1_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL21_struct {
   uint32_t selfref_entry2_ba_0;
   uint32_t selfref_entry2_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL22_struct {
   uint32_t selfref_exit1_ba_0;
   uint32_t selfref_exit1_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL22_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASCTL23_struct {
   uint32_t selfref_exit2_ba_0;
   uint32_t selfref_exit2_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL23_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH0_PASCTL24_struct {
   uint32_t selfref_entry1_ba_1;
   uint32_t selfref_entry1_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL24_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH0_PASCTL25_struct {
   uint32_t selfref_entry2_ba_1;
   uint32_t selfref_entry2_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL25_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH0_PASCTL26_struct {
   uint32_t selfref_exit1_ba_1;
   uint32_t selfref_exit1_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL26_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH0_PASCTL27_struct {
   uint32_t selfref_exit2_ba_1;
   uint32_t selfref_exit2_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL27_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL28_struct {
   uint32_t selfref_entry1_ba_2;
   uint32_t selfref_entry1_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL28_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL29_struct {
   uint32_t selfref_entry2_ba_2;
   uint32_t selfref_entry2_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL29_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL30_struct {
   uint32_t selfref_exit1_ba_2;
   uint32_t selfref_exit1_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL30_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL31_struct {
   uint32_t selfref_exit2_ba_2;
   uint32_t selfref_exit2_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL31_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL32_struct {
   uint32_t selfref_entry1_ba_3;
   uint32_t selfref_entry1_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL32_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL33_struct {
   uint32_t selfref_entry2_ba_3;
   uint32_t selfref_entry2_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL33_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL34_struct {
   uint32_t selfref_exit1_ba_3;
   uint32_t selfref_exit1_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL34_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH0_PASCTL35_struct {
   uint32_t selfref_exit2_ba_3;
   uint32_t selfref_exit2_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL35_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP_EN
typedef struct tag_REGB_DDRC_CH0_PASCTL36_struct {
   uint32_t powerdown_idle_ctrl_0;
   uint32_t powerdown_idle_ctrl_1;
   uint32_t selfref_idle_ctrl_0;
   uint32_t selfref_idle_ctrl_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL36_struct_t;

#endif //DDRCTL_PERRANK_LP_EN
#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_DDRC_CH0_PASCTL37_struct {
   uint32_t dch_sync_mode;
   uint32_t dch_stagger_sel;
   uint32_t t_dch_stagger_delay;
   uint32_t t_selfref_exit_stagger;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL37_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_BWL_EN
typedef struct tag_REGB_DDRC_CH0_PASCTL38_struct {
   uint32_t bwl_win_len;
   uint32_t bwl_en_len;
   uint32_t bwl_ctrl;
   uint32_t bwl_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASCTL38_struct_t;

#endif //DDRCTL_DDR_BWL_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_CMDCFG_struct {
   uint32_t cmd_type;
   uint32_t multi_cyc_cs_en;
   uint32_t cmd_timer_x32;
   uint32_t mrr_grp_sel;
   uint32_t dram_dq_width;
   uint32_t ctrlupd_retry_thr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CMDCFG_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_CMDCTL_struct {
   uint32_t cmd_ctrl;
   uint32_t cmd_code;
   uint32_t cmd_seq_last;
   uint32_t cmd_start;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CMDCTL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_CMDEXTCTL_struct {
   uint32_t cmd_ext_ctrl;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CMDEXTCTL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_PASINTCTL_struct {
   uint32_t swcmd_err_intr_en;
   uint32_t swcmd_err_intr_clr;
   uint32_t swcmd_err_intr_force;
   uint32_t ducmd_err_intr_en;
   uint32_t ducmd_err_intr_clr;
   uint32_t ducmd_err_intr_force;
   uint32_t lccmd_err_intr_en;
   uint32_t lccmd_err_intr_clr;
   uint32_t lccmd_err_intr_force;
   uint32_t ctrlupd_err_intr_en;
   uint32_t ctrlupd_err_intr_clr;
   uint32_t ctrlupd_err_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_PASINTCTL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_DU_CFGBUF_CTRL_struct {
   uint32_t du_cfgbuf_wdata;
   uint32_t du_cfgbuf_addr;
   uint32_t du_cfgbuf_select;
   uint32_t du_cfgbuf_op_mode;
   uint32_t du_cfgbuf_rw_type;
   uint32_t du_cfgbuf_rw_start;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DU_CFGBUF_CTRL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_DU_CMDBUF_CTRL_struct {
   uint32_t du_cmdbuf_wdata;
   uint32_t du_cmdbuf_addr;
   uint32_t du_cmdbuf_select;
   uint32_t du_cmdbuf_op_mode;
   uint32_t du_cmdbuf_rw_type;
   uint32_t du_cmdbuf_rw_start;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DU_CMDBUF_CTRL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_LP_CMDBUF_CTRL_struct {
   uint32_t lp_cmdbuf_wdata;
   uint32_t lp_cmdbuf_addr;
   uint32_t lp_cmdbuf_op_mode;
   uint32_t lp_cmdbuf_rw_type;
   uint32_t lp_cmdbuf_rw_start;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_LP_CMDBUF_CTRL_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_OPCTRL0_struct {
   uint32_t dis_wc;
   uint32_t dis_rd_bypass;
   uint32_t dis_act_bypass;
   uint32_t dis_collision_page_opt;
   uint32_t dis_max_rank_rd_opt;
   uint32_t dis_max_rank_wr_opt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OPCTRL0_struct_t;

typedef struct tag_REGB_DDRC_CH0_OPCTRL1_struct {
   uint32_t dis_dq;
   uint32_t dis_hif;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OPCTRL1_struct_t;

typedef struct tag_REGB_DDRC_CH0_OPCTRLCMD_struct {
   uint32_t rank0_refresh;
   uint32_t rank1_refresh;
   uint32_t rank2_refresh;
   uint32_t rank3_refresh;
   uint32_t rank4_refresh;
   uint32_t rank5_refresh;
   uint32_t rank6_refresh;
   uint32_t rank7_refresh;
   uint32_t rank8_refresh;
   uint32_t rank9_refresh;
   uint32_t rank10_refresh;
   uint32_t rank11_refresh;
   uint32_t rank12_refresh;
   uint32_t rank13_refresh;
   uint32_t rank14_refresh;
   uint32_t rank15_refresh;
   uint32_t zq_calib_short;
   uint32_t ctrlupd;
   uint32_t hw_ref_zq_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_OPCTRLCMD_struct_t;

typedef struct tag_REGB_DDRC_CH0_SWCTL_struct {
   uint32_t sw_done;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_SWCTL_struct_t;

typedef struct tag_REGB_DDRC_CH0_DIMMCTL_struct {
   uint32_t dimm_stagger_cs_en;
   uint32_t dimm_addr_mirr_en;
   uint32_t dimm_output_inv_en;
   uint32_t mrs_a17_en;
   uint32_t mrs_bg1_en;
   uint32_t dimm_dis_bg_mirroring;
   uint32_t lrdimm_bcom_cmd_prot;
   uint32_t rcd_num;
   uint32_t dimm_type;
   uint32_t rcd_weak_drive;
   uint32_t rcd_a_output_disabled;
   uint32_t rcd_b_output_disabled;
   uint32_t dimm_selfref_clock_stop_mode;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DIMMCTL_struct_t;

#ifdef DDRCTL_PROG_CHCTL
typedef struct tag_REGB_DDRC_CH0_CHCTL_struct {
   uint32_t dual_channel_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_CHCTL_struct_t;

#endif //DDRCTL_PROG_CHCTL
#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_DDRC_CH0_RANKCTL_struct {
   uint32_t max_rank_rd;
   uint32_t max_rank_wr;
   uint32_t max_logical_rank_rd;
   uint32_t max_logical_rank_wr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_RANKCTL_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_DDRC_CH0_DBICTL_struct {
   uint32_t dm_en;
   uint32_t wr_dbi_en;
   uint32_t rd_dbi_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DBICTL_struct_t;

typedef struct tag_REGB_DDRC_CH0_ODTMAP_struct {
   uint32_t rank0_wr_odt;
   uint32_t rank0_rd_odt;
   uint32_t rank1_wr_odt;
   uint32_t rank1_rd_odt;
   uint32_t rank2_wr_odt;
   uint32_t rank2_rd_odt;
   uint32_t rank3_wr_odt;
   uint32_t rank3_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAP_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH0_DATACTL0_struct {
   uint32_t rd_data_copy_en;
   uint32_t wr_data_copy_en;
   uint32_t wr_data_x_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DATACTL0_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH0_SWCTLSTATIC_struct {
   uint32_t sw_static_unlock;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_SWCTLSTATIC_struct_t;

#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK0_struct {
   uint32_t k0_wr_odt;
   uint32_t k0_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK0_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK1_struct {
   uint32_t k1_wr_odt;
   uint32_t k1_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK1_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK2_struct {
   uint32_t k2_wr_odt;
   uint32_t k2_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK2_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK3_struct {
   uint32_t k3_wr_odt;
   uint32_t k3_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK3_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK4_struct {
   uint32_t k4_wr_odt;
   uint32_t k4_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK4_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK5_struct {
   uint32_t k5_wr_odt;
   uint32_t k5_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK5_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK6_struct {
   uint32_t k6_wr_odt;
   uint32_t k6_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK6_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK7_struct {
   uint32_t k7_wr_odt;
   uint32_t k7_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK7_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK8_struct {
   uint32_t k8_wr_odt;
   uint32_t k8_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK8_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK9_struct {
   uint32_t k9_wr_odt;
   uint32_t k9_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK9_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK10_struct {
   uint32_t k10_wr_odt;
   uint32_t k10_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK10_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK11_struct {
   uint32_t k11_wr_odt;
   uint32_t k11_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK11_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK12_struct {
   uint32_t k12_wr_odt;
   uint32_t k12_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK12_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK13_struct {
   uint32_t k13_wr_odt;
   uint32_t k13_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK13_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK14_struct {
   uint32_t k14_wr_odt;
   uint32_t k14_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK14_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_ODTMAPK15_struct {
   uint32_t k15_wr_odt;
   uint32_t k15_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_ODTMAPK15_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
typedef struct tag_REGB_DDRC_CH0_INITTMG0_struct {
   uint32_t pre_cke_x1024;
   uint32_t post_cke_x1024;
   uint32_t skip_dram_init;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_INITTMG0_struct_t;

typedef struct tag_REGB_DDRC_CH0_INITTMG1_struct {
   uint32_t dram_rstn_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_INITTMG1_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH0_INITTMG2_struct {
   uint32_t dev_zqinit_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_INITTMG2_struct_t;

#endif //DDRCTL_DDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH0_DS_DBG_CTRL0_struct {
   uint32_t dbg_bsm_sel_ctrl;
   uint32_t dbg_lrsm_sel_ctrl;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH0_DS_DBG_CTRL0_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_MSTR3_struct {
   uint32_t geardown_mode;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_MSTR3_struct_t;

#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH1_MSTR4_struct {
   uint32_t wck_on;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_MSTR4_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH1_MRCTRL0_struct {
   uint32_t mr_type;
   uint32_t mpr_en;
   uint32_t pda_en;
   uint32_t sw_init_int;
   uint32_t mr_rank;
   uint32_t mr_addr;
   uint32_t mr_cid;
   uint32_t mrr_done_clr;
   uint32_t pba_mode;
   uint32_t mr_wr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_MRCTRL0_struct_t;

typedef struct tag_REGB_DDRC_CH1_MRCTRL1_struct {
   uint32_t mr_data;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_MRCTRL1_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_MRCTRL2_struct {
   uint32_t mr_device_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_MRCTRL2_struct_t;

#endif //DDRCTL_DDR
#ifndef MEMC_NUM_RANKS_1_OR_2_OR_4
typedef struct tag_REGB_DDRC_CH1_MRCTRL3_struct {
   uint32_t mr_rank_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_MRCTRL3_struct_t;

#endif //MEMC_NUM_RANKS_1_OR_2_OR_4
#ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct tag_REGB_DDRC_CH1_DERATECTL5_struct {
   uint32_t derate_temp_limit_intr_en;
   uint32_t derate_temp_limit_intr_clr;
   uint32_t derate_temp_limit_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_DERATECTL5_struct_t;

#endif //DDRCTL_DDR_OR_MEMC_LPDDR4
#ifdef DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct tag_REGB_DDRC_CH1_DERATEDBGCTL_struct {
   uint32_t dbg_mr4_grp_sel;
   uint32_t dbg_mr4_rank_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_DERATEDBGCTL_struct_t;

#endif //DDRCTL_DDR_OR_MEMC_LPDDR4
typedef struct tag_REGB_DDRC_CH1_PWRCTL_struct {
   uint32_t selfref_en;
   uint32_t powerdown_en;
   uint32_t actv_pd_en;
   uint32_t en_dfi_dram_clk_disable;
   uint32_t mpsm_en;
   uint32_t selfref_sw;
   uint32_t stay_in_selfref;
   uint32_t dis_cam_drain_selfref;
   uint32_t lpddr4_sr_allowed;
   uint32_t dsm_en;
   uint32_t srpd_en;
   uint32_t mpsm_pd_en;
   uint32_t mpsm_deep_pd_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PWRCTL_struct_t;

typedef struct tag_REGB_DDRC_CH1_HWLPCTL_struct {
   uint32_t hw_lp_en;
   uint32_t hw_lp_exit_idle_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_HWLPCTL_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH1_ZQCTL1_struct {
   uint32_t zq_reset;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ZQCTL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_DDRC_CH1_DFI0MSGCTL0_struct {
   uint32_t dfi0_ctrlmsg_data;
   uint32_t dfi0_ctrlmsg_cmd;
   uint32_t dfi0_ctrlmsg_tout_clr;
   uint32_t dfi0_ctrlmsg_req;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_DFI0MSGCTL0_struct_t;

#ifdef MEMC_ECC_SUPPORT_GT_0
typedef struct tag_REGB_DDRC_CH1_ECCCTL_struct {
   uint32_t ecc_corrected_err_clr;
   uint32_t ecc_uncorrected_err_clr;
   uint32_t ecc_corr_err_cnt_clr;
   uint32_t ecc_uncorr_err_cnt_clr;
   uint32_t ecc_ap_err_intr_clr;
   uint32_t ecc_corrected_err_intr_en;
   uint32_t ecc_uncorrected_err_intr_en;
   uint32_t ecc_ap_err_intr_en;
   uint32_t ecc_corrected_err_intr_force;
   uint32_t ecc_uncorrected_err_intr_force;
   uint32_t ecc_ap_err_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ECCCTL_struct_t;

#endif //MEMC_ECC_SUPPORT_GT_0
#ifdef UMCTL2_OCPAR_OR_OCECC_EN_1
typedef struct tag_REGB_DDRC_CH1_OCPARCFG0_struct {
   uint32_t oc_parity_en;
   uint32_t oc_parity_type;
   uint32_t par_wdata_err_intr_en;
   uint32_t par_wdata_slverr_en;
   uint32_t par_wdata_err_intr_clr;
   uint32_t par_wdata_err_intr_force;
   uint32_t par_rdata_slverr_en;
   uint32_t par_rdata_err_intr_en;
   uint32_t par_rdata_err_intr_clr;
   uint32_t par_rdata_err_intr_force;
   uint32_t par_addr_slverr_en;
   uint32_t par_waddr_err_intr_en;
   uint32_t par_waddr_err_intr_clr;
   uint32_t par_raddr_err_intr_en;
   uint32_t par_raddr_err_intr_clr;
   uint32_t par_waddr_err_intr_force;
   uint32_t par_raddr_err_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_OCPARCFG0_struct_t;

#endif //UMCTL2_OCPAR_OR_OCECC_EN_1
#ifdef UMCTL2_OCCAP_EN_1
typedef struct tag_REGB_DDRC_CH1_OCCAPCFG1_struct {
   uint32_t occap_ddrc_data_intr_en;
   uint32_t occap_ddrc_data_intr_clr;
   uint32_t occap_ddrc_data_intr_force;
   uint32_t occap_ddrc_data_poison_seq;
   uint32_t occap_ddrc_data_poison_parallel;
   uint32_t occap_ddrc_data_poison_err_inj;
   uint32_t occap_ddrc_ctrl_intr_en;
   uint32_t occap_ddrc_ctrl_intr_clr;
   uint32_t occap_ddrc_ctrl_intr_force;
   uint32_t occap_ddrc_ctrl_poison_seq;
   uint32_t occap_ddrc_ctrl_poison_parallel;
   uint32_t occap_ddrc_ctrl_poison_err_inj;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_OCCAPCFG1_struct_t;

#endif //UMCTL2_OCCAP_EN_1
typedef struct tag_REGB_DDRC_CH1_CRCPARCTL0_struct {
   uint32_t dfi_alert_err_int_en;
   uint32_t dfi_alert_err_int_clr;
   uint32_t dfi_alert_err_cnt_clr;
   uint32_t dfi_alert_err_fatl_int_clr;
   uint32_t dfi_alert_err_max_reached_int_clr;
   uint32_t retry_ctrlupd_enable;
   uint32_t retry_ctrlupd_wait;
   uint32_t rd_crc_err_max_reached_int_en;
   uint32_t rd_crc_err_max_reached_int_clr;
   uint32_t rd_crc_err_cnt_clr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_CRCPARCTL0_struct_t;

#ifdef DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY_OR_DDRCTL_CA_PARITY
typedef struct tag_REGB_DDRC_CH1_CAPARPOISONCTL_struct {
   uint32_t capar_poison_inject_en;
   uint32_t capar_poison_cmdtype;
   uint32_t capar_poison_position;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_CAPARPOISONCTL_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY_OR_DDRCTL_CA_PARITY
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_CRCPOISONCTL0_struct {
   uint32_t crc_poison_inject_en;
   uint32_t crc_poison_type;
   uint32_t crc_poison_nibble;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_CRCPOISONCTL0_struct_t;

#endif //DDRCTL_DDR
#ifdef MEMC_LINK_ECC
typedef struct tag_REGB_DDRC_CH1_LNKECCCTL0_struct {
   uint32_t wr_link_ecc_enable;
   uint32_t rd_link_ecc_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_LNKECCCTL0_struct_t;

#endif //MEMC_LINK_ECC
#ifdef MEMC_LINK_ECC
typedef struct tag_REGB_DDRC_CH1_LNKECCCTL1_struct {
   uint32_t rd_link_ecc_corr_intr_en;
   uint32_t rd_link_ecc_corr_intr_clr;
   uint32_t rd_link_ecc_corr_cnt_clr;
   uint32_t rd_link_ecc_corr_intr_force;
   uint32_t rd_link_ecc_uncorr_intr_en;
   uint32_t rd_link_ecc_uncorr_intr_clr;
   uint32_t rd_link_ecc_uncorr_cnt_clr;
   uint32_t rd_link_ecc_uncorr_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_LNKECCCTL1_struct_t;

#endif //MEMC_LINK_ECC
#ifdef MEMC_LINK_ECC
typedef struct tag_REGB_DDRC_CH1_LNKECCPOISONCTL0_struct {
   uint32_t linkecc_poison_inject_en;
   uint32_t linkecc_poison_type;
   uint32_t linkecc_poison_rw;
   uint32_t linkecc_poison_dmi_sel;
   uint32_t linkecc_poison_byte_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_LNKECCPOISONCTL0_struct_t;

#endif //MEMC_LINK_ECC
#ifdef MEMC_LINK_ECC
typedef struct tag_REGB_DDRC_CH1_LNKECCINDEX_struct {
   uint32_t rd_link_ecc_err_byte_sel;
   uint32_t rd_link_ecc_err_rank_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_LNKECCINDEX_struct_t;

#endif //MEMC_LINK_ECC
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL0_struct {
   uint32_t init_done;
   uint32_t dbg_st_en;
   uint32_t bist_st_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL0_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL1_struct {
   uint32_t pre_sb_enable;
   uint32_t pre_ab_enable;
   uint32_t pre_slot_config;
   uint32_t wr_min_gap;
   uint32_t rd_min_gap;
   uint32_t prank_tmgreg_set_sel;
   uint32_t non_dyn_sched_en;
   uint32_t selfref_wo_ref_pending;
   uint32_t dfi_alert_assertion_mode;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL1_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL2_struct {
   uint32_t active_prank_bitmap;
   uint32_t pads0_rsvd0;
   uint32_t lrank_rd2rd_gap;
   uint32_t lrank_wr2wr_gap;
   uint32_t lrank_rd2wr_gap;
   uint32_t lrank_wr2rd_gap;
   uint32_t pads0_rsvd1;
   uint32_t t_ppd_cnt_en;
   uint32_t pads0_rsvd2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL2_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL3_struct {
   uint32_t bg_bit_mask;
   uint32_t bank_bit_mask;
   uint32_t lrank_bit_mask;
   uint32_t prank_bit_mask;
   uint32_t pads1_rsvd1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL4_struct {
   uint32_t ci_mrr_des1;
   uint32_t ci_mrr_des2;
   uint32_t ci_mrw_des1;
   uint32_t ci_mrw_des2;
   uint32_t ci_mpc_des1;
   uint32_t ci_mpc_des2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL4_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL5_struct {
   uint32_t base_timer_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL5_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL6_struct {
   uint32_t base_timer;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL6_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL7_struct {
   uint32_t glb_blk0_en;
   uint32_t glb_blk1_en;
   uint32_t glb_blk2_en;
   uint32_t glb_blk3_en;
   uint32_t glb_blk4_en;
   uint32_t glb_blk5_en;
   uint32_t glb_blk6_en;
   uint32_t glb_blk7_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL7_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL8_struct {
   uint32_t rank_blk0_en;
   uint32_t rank_blk1_en;
   uint32_t rank_blk2_en;
   uint32_t rank_blk3_en;
   uint32_t rank_blk4_en;
   uint32_t rank_blk5_en;
   uint32_t rank_blk6_en;
   uint32_t rank_blk7_en;
   uint32_t rank_blk8_en;
   uint32_t rank_blk9_en;
   uint32_t rank_blk10_en;
   uint32_t rank_blk11_en;
   uint32_t rank_blk12_en;
   uint32_t rank_blk13_en;
   uint32_t rank_blk14_en;
   uint32_t rank_blk15_en;
   uint32_t rank_blk16_en;
   uint32_t rank_blk17_en;
   uint32_t rank_blk18_en;
   uint32_t rank_blk19_en;
   uint32_t rank_blk20_en;
   uint32_t rank_blk21_en;
   uint32_t rank_blk22_en;
   uint32_t rank_blk23_en;
   uint32_t rank_blk24_en;
   uint32_t rank_blk25_en;
   uint32_t rank_blk26_en;
   uint32_t rank_blk27_en;
   uint32_t rank_blk28_en;
   uint32_t rank_blk29_en;
   uint32_t rank_blk30_en;
   uint32_t rank_blk31_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL8_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL9_struct {
   uint32_t glb_blk0_trig;
   uint32_t glb_blk1_trig;
   uint32_t glb_blk2_trig;
   uint32_t glb_blk3_trig;
   uint32_t glb_blk4_trig;
   uint32_t glb_blk5_trig;
   uint32_t glb_blk6_trig;
   uint32_t glb_blk7_trig;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL9_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL10_struct {
   uint32_t rank_blk0_trig;
   uint32_t rank_blk1_trig;
   uint32_t rank_blk2_trig;
   uint32_t rank_blk3_trig;
   uint32_t rank_blk4_trig;
   uint32_t rank_blk5_trig;
   uint32_t rank_blk6_trig;
   uint32_t rank_blk7_trig;
   uint32_t rank_blk8_trig;
   uint32_t rank_blk9_trig;
   uint32_t rank_blk10_trig;
   uint32_t rank_blk11_trig;
   uint32_t rank_blk12_trig;
   uint32_t rank_blk13_trig;
   uint32_t rank_blk14_trig;
   uint32_t rank_blk15_trig;
   uint32_t rank_blk16_trig;
   uint32_t rank_blk17_trig;
   uint32_t rank_blk18_trig;
   uint32_t rank_blk19_trig;
   uint32_t rank_blk20_trig;
   uint32_t rank_blk21_trig;
   uint32_t rank_blk22_trig;
   uint32_t rank_blk23_trig;
   uint32_t rank_blk24_trig;
   uint32_t rank_blk25_trig;
   uint32_t rank_blk26_trig;
   uint32_t rank_blk27_trig;
   uint32_t rank_blk28_trig;
   uint32_t rank_blk29_trig;
   uint32_t rank_blk30_trig;
   uint32_t rank_blk31_trig;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL10_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL11_struct {
   uint32_t powerdown_entry_ba_0;
   uint32_t powerdown_entry_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL11_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL12_struct {
   uint32_t powerdown_exit_ba_0;
   uint32_t powerdown_exit_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL12_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH1_PASCTL13_struct {
   uint32_t powerdown_entry_ba_1;
   uint32_t powerdown_entry_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL13_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH1_PASCTL14_struct {
   uint32_t powerdown_exit_ba_1;
   uint32_t powerdown_exit_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL14_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL15_struct {
   uint32_t powerdown_entry_ba_2;
   uint32_t powerdown_entry_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL15_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL16_struct {
   uint32_t powerdown_exit_ba_2;
   uint32_t powerdown_exit_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL16_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL17_struct {
   uint32_t powerdown_entry_ba_3;
   uint32_t powerdown_entry_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL17_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL18_struct {
   uint32_t powerdown_exit_ba_3;
   uint32_t powerdown_exit_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL18_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL20_struct {
   uint32_t selfref_entry1_ba_0;
   uint32_t selfref_entry1_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL21_struct {
   uint32_t selfref_entry2_ba_0;
   uint32_t selfref_entry2_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL22_struct {
   uint32_t selfref_exit1_ba_0;
   uint32_t selfref_exit1_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL22_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASCTL23_struct {
   uint32_t selfref_exit2_ba_0;
   uint32_t selfref_exit2_size_0;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL23_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH1_PASCTL24_struct {
   uint32_t selfref_entry1_ba_1;
   uint32_t selfref_entry1_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL24_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH1_PASCTL25_struct {
   uint32_t selfref_entry2_ba_1;
   uint32_t selfref_entry2_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL25_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH1_PASCTL26_struct {
   uint32_t selfref_exit1_ba_1;
   uint32_t selfref_exit1_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL26_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_DDRC_CH1_PASCTL27_struct {
   uint32_t selfref_exit2_ba_1;
   uint32_t selfref_exit2_size_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL27_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL28_struct {
   uint32_t selfref_entry1_ba_2;
   uint32_t selfref_entry1_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL28_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL29_struct {
   uint32_t selfref_entry2_ba_2;
   uint32_t selfref_entry2_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL29_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL30_struct {
   uint32_t selfref_exit1_ba_2;
   uint32_t selfref_exit1_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL30_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL31_struct {
   uint32_t selfref_exit2_ba_2;
   uint32_t selfref_exit2_size_2;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL31_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL32_struct {
   uint32_t selfref_entry1_ba_3;
   uint32_t selfref_entry1_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL32_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL33_struct {
   uint32_t selfref_entry2_ba_3;
   uint32_t selfref_entry2_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL33_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL34_struct {
   uint32_t selfref_exit1_ba_3;
   uint32_t selfref_exit1_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL34_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_DDRC_CH1_PASCTL35_struct {
   uint32_t selfref_exit2_ba_3;
   uint32_t selfref_exit2_size_3;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL35_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //DDRCTL_PERRANK_LP
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_PERRANK_LP_EN
typedef struct tag_REGB_DDRC_CH1_PASCTL36_struct {
   uint32_t powerdown_idle_ctrl_0;
   uint32_t powerdown_idle_ctrl_1;
   uint32_t selfref_idle_ctrl_0;
   uint32_t selfref_idle_ctrl_1;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL36_struct_t;

#endif //DDRCTL_PERRANK_LP_EN
#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_DDRC_CH1_PASCTL37_struct {
   uint32_t dch_sync_mode;
   uint32_t dch_stagger_sel;
   uint32_t t_dch_stagger_delay;
   uint32_t t_selfref_exit_stagger;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL37_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_BWL_EN
typedef struct tag_REGB_DDRC_CH1_PASCTL38_struct {
   uint32_t bwl_win_len;
   uint32_t bwl_en_len;
   uint32_t bwl_ctrl;
   uint32_t bwl_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASCTL38_struct_t;

#endif //DDRCTL_DDR_BWL_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_CMDCFG_struct {
   uint32_t cmd_type;
   uint32_t multi_cyc_cs_en;
   uint32_t cmd_timer_x32;
   uint32_t mrr_grp_sel;
   uint32_t dram_dq_width;
   uint32_t ctrlupd_retry_thr;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_CMDCFG_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_CMDCTL_struct {
   uint32_t cmd_ctrl;
   uint32_t cmd_code;
   uint32_t cmd_seq_last;
   uint32_t cmd_start;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_CMDCTL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_CMDEXTCTL_struct {
   uint32_t cmd_ext_ctrl;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_CMDEXTCTL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_PASINTCTL_struct {
   uint32_t swcmd_err_intr_en;
   uint32_t swcmd_err_intr_clr;
   uint32_t swcmd_err_intr_force;
   uint32_t ducmd_err_intr_en;
   uint32_t ducmd_err_intr_clr;
   uint32_t ducmd_err_intr_force;
   uint32_t lccmd_err_intr_en;
   uint32_t lccmd_err_intr_clr;
   uint32_t lccmd_err_intr_force;
   uint32_t ctrlupd_err_intr_en;
   uint32_t ctrlupd_err_intr_clr;
   uint32_t ctrlupd_err_intr_force;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_PASINTCTL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_DU_CFGBUF_CTRL_struct {
   uint32_t du_cfgbuf_wdata;
   uint32_t du_cfgbuf_addr;
   uint32_t du_cfgbuf_select;
   uint32_t du_cfgbuf_op_mode;
   uint32_t du_cfgbuf_rw_type;
   uint32_t du_cfgbuf_rw_start;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_DU_CFGBUF_CTRL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_DU_CMDBUF_CTRL_struct {
   uint32_t du_cmdbuf_wdata;
   uint32_t du_cmdbuf_addr;
   uint32_t du_cmdbuf_select;
   uint32_t du_cmdbuf_op_mode;
   uint32_t du_cmdbuf_rw_type;
   uint32_t du_cmdbuf_rw_start;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_DU_CMDBUF_CTRL_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_LP_CMDBUF_CTRL_struct {
   uint32_t lp_cmdbuf_wdata;
   uint32_t lp_cmdbuf_addr;
   uint32_t lp_cmdbuf_op_mode;
   uint32_t lp_cmdbuf_rw_type;
   uint32_t lp_cmdbuf_rw_start;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_LP_CMDBUF_CTRL_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_OPCTRL1_struct {
   uint32_t dis_dq;
   uint32_t dis_hif;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_OPCTRL1_struct_t;

typedef struct tag_REGB_DDRC_CH1_OPCTRLCMD_struct {
   uint32_t rank0_refresh;
   uint32_t rank1_refresh;
   uint32_t rank2_refresh;
   uint32_t rank3_refresh;
   uint32_t rank4_refresh;
   uint32_t rank5_refresh;
   uint32_t rank6_refresh;
   uint32_t rank7_refresh;
   uint32_t rank8_refresh;
   uint32_t rank9_refresh;
   uint32_t rank10_refresh;
   uint32_t rank11_refresh;
   uint32_t rank12_refresh;
   uint32_t rank13_refresh;
   uint32_t rank14_refresh;
   uint32_t rank15_refresh;
   uint32_t zq_calib_short;
   uint32_t ctrlupd;
   uint32_t hw_ref_zq_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_OPCTRLCMD_struct_t;

typedef struct tag_REGB_DDRC_CH1_DBICTL_struct {
   uint32_t dm_en;
   uint32_t wr_dbi_en;
   uint32_t rd_dbi_en;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_DBICTL_struct_t;

typedef struct tag_REGB_DDRC_CH1_ODTMAP_struct {
   uint32_t rank0_wr_odt;
   uint32_t rank0_rd_odt;
   uint32_t rank1_wr_odt;
   uint32_t rank1_rd_odt;
   uint32_t rank2_wr_odt;
   uint32_t rank2_rd_odt;
   uint32_t rank3_wr_odt;
   uint32_t rank3_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAP_struct_t;

#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK0_struct {
   uint32_t k0_wr_odt;
   uint32_t k0_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK0_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK1_struct {
   uint32_t k1_wr_odt;
   uint32_t k1_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK1_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK2_struct {
   uint32_t k2_wr_odt;
   uint32_t k2_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK2_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK3_struct {
   uint32_t k3_wr_odt;
   uint32_t k3_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK3_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK4_struct {
   uint32_t k4_wr_odt;
   uint32_t k4_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK4_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK5_struct {
   uint32_t k5_wr_odt;
   uint32_t k5_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK5_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK6_struct {
   uint32_t k6_wr_odt;
   uint32_t k6_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK6_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_4
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK7_struct {
   uint32_t k7_wr_odt;
   uint32_t k7_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK7_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_4
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK8_struct {
   uint32_t k8_wr_odt;
   uint32_t k8_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK8_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK9_struct {
   uint32_t k9_wr_odt;
   uint32_t k9_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK9_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK10_struct {
   uint32_t k10_wr_odt;
   uint32_t k10_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK10_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK11_struct {
   uint32_t k11_wr_odt;
   uint32_t k11_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK11_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK12_struct {
   uint32_t k12_wr_odt;
   uint32_t k12_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK12_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK13_struct {
   uint32_t k13_wr_odt;
   uint32_t k13_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK13_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK14_struct {
   uint32_t k14_wr_odt;
   uint32_t k14_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK14_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
#ifdef MEMC_NUM_RANKS_GT_8
#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_ODTMAPK15_struct {
   uint32_t k15_wr_odt;
   uint32_t k15_rd_odt;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_ODTMAPK15_struct_t;

#endif //DDRCTL_DDR
#endif //MEMC_NUM_RANKS_GT_8
typedef struct tag_REGB_DDRC_CH1_INITTMG0_struct {
   uint32_t pre_cke_x1024;
   uint32_t post_cke_x1024;
   uint32_t skip_dram_init;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_INITTMG0_struct_t;

typedef struct tag_REGB_DDRC_CH1_INITTMG1_struct {
   uint32_t dram_rstn_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_INITTMG1_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_DDRC_CH1_INITTMG2_struct {
   uint32_t dev_zqinit_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_INITTMG2_struct_t;

#endif //DDRCTL_DDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_DDRC_CH1_DS_DBG_CTRL0_struct {
   uint32_t dbg_bsm_sel_ctrl;
   uint32_t dbg_lrsm_sel_ctrl;
  uint32_t value; // full 32-bit register value.
  } REGB_DDRC_CH1_DS_DBG_CTRL0_struct_t;

#endif //MEMC_DDR5
#ifdef UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
typedef struct tag_REGB_ADDR_MAP0_ADDRMAP0_struct {
   uint32_t addrmap_dch_bit0;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP0_struct_t;

#endif //UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_ADDR_MAP0_ADDRMAP1_struct {
   uint32_t addrmap_cs_bit0;
   uint32_t addrmap_cs_bit1;
   uint32_t addrmap_cs_bit2;
   uint32_t addrmap_cs_bit3;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef UMCTL2_CID_WIDTH_GT_0
typedef struct tag_REGB_ADDR_MAP0_ADDRMAP2_struct {
   uint32_t addrmap_cid_b0;
   uint32_t addrmap_cid_b1;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP2_struct_t;

#endif //UMCTL2_CID_WIDTH_GT_0
typedef struct tag_REGB_ADDR_MAP0_ADDRMAP3_struct {
   uint32_t addrmap_bank_b0;
   uint32_t addrmap_bank_b1;
   uint32_t addrmap_bank_b2;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP3_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP4_struct {
   uint32_t addrmap_bg_b0;
   uint32_t addrmap_bg_b1;
   uint32_t addrmap_bg_b2;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP4_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP5_struct {
   uint32_t addrmap_col_b7;
   uint32_t addrmap_col_b8;
   uint32_t addrmap_col_b9;
   uint32_t addrmap_col_b10;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP5_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP6_struct {
   uint32_t addrmap_col_b3;
   uint32_t addrmap_col_b4;
   uint32_t addrmap_col_b5;
   uint32_t addrmap_col_b6;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP6_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP7_struct {
   uint32_t addrmap_row_b14;
   uint32_t addrmap_row_b15;
   uint32_t addrmap_row_b16;
   uint32_t addrmap_row_b17;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP7_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP8_struct {
   uint32_t addrmap_row_b10;
   uint32_t addrmap_row_b11;
   uint32_t addrmap_row_b12;
   uint32_t addrmap_row_b13;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP8_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP9_struct {
   uint32_t addrmap_row_b6;
   uint32_t addrmap_row_b7;
   uint32_t addrmap_row_b8;
   uint32_t addrmap_row_b9;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP9_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP10_struct {
   uint32_t addrmap_row_b2;
   uint32_t addrmap_row_b3;
   uint32_t addrmap_row_b4;
   uint32_t addrmap_row_b5;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP10_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP11_struct {
   uint32_t addrmap_row_b0;
   uint32_t addrmap_row_b1;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP11_struct_t;

typedef struct tag_REGB_ADDR_MAP0_ADDRMAP12_struct {
   uint32_t nonbinary_device_density;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP0_ADDRMAP12_struct_t;

#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_ADDR_MAP1_ADDRMAP1_struct {
   uint32_t addrmap_cs_bit0;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef UMCTL2_CID_WIDTH_GT_0
typedef struct tag_REGB_ADDR_MAP1_ADDRMAP2_struct {
   uint32_t addrmap_cid_b0;
   uint32_t addrmap_cid_b1;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP2_struct_t;

#endif //UMCTL2_CID_WIDTH_GT_0
typedef struct tag_REGB_ADDR_MAP1_ADDRMAP3_struct {
   uint32_t addrmap_bank_b0;
   uint32_t addrmap_bank_b1;
   uint32_t addrmap_bank_b2;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP3_struct_t;

typedef struct tag_REGB_ADDR_MAP1_ADDRMAP4_struct {
   uint32_t addrmap_bg_b0;
   uint32_t addrmap_bg_b1;
   uint32_t addrmap_bg_b2;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP4_struct_t;

typedef struct tag_REGB_ADDR_MAP1_ADDRMAP5_struct {
   uint32_t addrmap_col_b7;
   uint32_t addrmap_col_b8;
   uint32_t addrmap_col_b9;
   uint32_t addrmap_col_b10;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP5_struct_t;

typedef struct tag_REGB_ADDR_MAP1_ADDRMAP6_struct {
   uint32_t addrmap_col_b3;
   uint32_t addrmap_col_b4;
   uint32_t addrmap_col_b5;
   uint32_t addrmap_col_b6;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP6_struct_t;

typedef struct tag_REGB_ADDR_MAP1_ADDRMAP7_struct {
   uint32_t addrmap_row_b14;
   uint32_t addrmap_row_b15;
   uint32_t addrmap_row_b16;
   uint32_t addrmap_row_b17;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP7_struct_t;

typedef struct tag_REGB_ADDR_MAP1_ADDRMAP8_struct {
   uint32_t addrmap_row_b10;
   uint32_t addrmap_row_b11;
   uint32_t addrmap_row_b12;
   uint32_t addrmap_row_b13;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP8_struct_t;

typedef struct tag_REGB_ADDR_MAP1_ADDRMAP9_struct {
   uint32_t addrmap_row_b6;
   uint32_t addrmap_row_b7;
   uint32_t addrmap_row_b8;
   uint32_t addrmap_row_b9;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP9_struct_t;

typedef struct tag_REGB_ADDR_MAP1_ADDRMAP10_struct {
   uint32_t addrmap_row_b2;
   uint32_t addrmap_row_b3;
   uint32_t addrmap_row_b4;
   uint32_t addrmap_row_b5;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP10_struct_t;

typedef struct tag_REGB_ADDR_MAP1_ADDRMAP11_struct {
   uint32_t addrmap_row_b0;
   uint32_t addrmap_row_b1;
  uint32_t value; // full 32-bit register value.
  } REGB_ADDR_MAP1_ADDRMAP11_struct_t;

typedef struct tag_REGB_ARB_PORT0_PCCFG_struct {
   uint32_t go2critical_en;
   uint32_t pagematch_limit;
   uint32_t dch_density_ratio;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCCFG_struct_t;

typedef struct tag_REGB_ARB_PORT0_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT0_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_0
#ifdef UMCTL2_PORT_CH0_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_0
#ifdef UMCTL2_PORT_CH1_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_0
#ifdef UMCTL2_PORT_CH1_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_0
#ifdef UMCTL2_PORT_CH2_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_0
#ifdef UMCTL2_PORT_CH2_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_0
#ifdef UMCTL2_PORT_CH3_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_0
#ifdef UMCTL2_PORT_CH3_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_0
#ifdef UMCTL2_PORT_CH4_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_0
#ifdef UMCTL2_PORT_CH4_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_0
#ifdef UMCTL2_PORT_CH5_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_0
#ifdef UMCTL2_PORT_CH5_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_0
#ifdef UMCTL2_PORT_CH6_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_0
#ifdef UMCTL2_PORT_CH6_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_0
#ifdef UMCTL2_PORT_CH7_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_0
#ifdef UMCTL2_PORT_CH7_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_0
#ifdef UMCTL2_PORT_CH8_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_0
#ifdef UMCTL2_PORT_CH8_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_0
#ifdef UMCTL2_PORT_CH9_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_0
#ifdef UMCTL2_PORT_CH9_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_0
#ifdef UMCTL2_PORT_CH10_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_0
#ifdef UMCTL2_PORT_CH10_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_0
#ifdef UMCTL2_PORT_CH11_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_0
#ifdef UMCTL2_PORT_CH11_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_0
#ifdef UMCTL2_PORT_CH12_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_0
#ifdef UMCTL2_PORT_CH12_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_0
#ifdef UMCTL2_PORT_CH13_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_0
#ifdef UMCTL2_PORT_CH13_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_0
#ifdef UMCTL2_PORT_CH14_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_0
#ifdef UMCTL2_PORT_CH14_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_0
#ifdef UMCTL2_PORT_CH15_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_0
#ifdef UMCTL2_PORT_CH15_0
typedef struct tag_REGB_ARB_PORT0_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_0
typedef struct tag_REGB_ARB_PORT0_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT0_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT0_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT0_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT0_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PCFGWQOS1_struct_t;

#ifdef UMCTL2_A_SAR_0
typedef struct tag_REGB_ARB_PORT0_SARBASE0_struct {
   uint32_t base_addr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARBASE0_struct_t;

#endif //UMCTL2_A_SAR_0
#ifdef UMCTL2_A_SAR_0
typedef struct tag_REGB_ARB_PORT0_SARSIZE0_struct {
   uint32_t nblocks;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARSIZE0_struct_t;

#endif //UMCTL2_A_SAR_0
#ifdef UMCTL2_A_SAR_1
typedef struct tag_REGB_ARB_PORT0_SARBASE1_struct {
   uint32_t base_addr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARBASE1_struct_t;

#endif //UMCTL2_A_SAR_1
#ifdef UMCTL2_A_SAR_1
typedef struct tag_REGB_ARB_PORT0_SARSIZE1_struct {
   uint32_t nblocks;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARSIZE1_struct_t;

#endif //UMCTL2_A_SAR_1
#ifdef UMCTL2_A_SAR_2
typedef struct tag_REGB_ARB_PORT0_SARBASE2_struct {
   uint32_t base_addr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARBASE2_struct_t;

#endif //UMCTL2_A_SAR_2
#ifdef UMCTL2_A_SAR_2
typedef struct tag_REGB_ARB_PORT0_SARSIZE2_struct {
   uint32_t nblocks;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARSIZE2_struct_t;

#endif //UMCTL2_A_SAR_2
#ifdef UMCTL2_A_SAR_3
typedef struct tag_REGB_ARB_PORT0_SARBASE3_struct {
   uint32_t base_addr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARBASE3_struct_t;

#endif //UMCTL2_A_SAR_3
#ifdef UMCTL2_A_SAR_3
typedef struct tag_REGB_ARB_PORT0_SARSIZE3_struct {
   uint32_t nblocks;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SARSIZE3_struct_t;

#endif //UMCTL2_A_SAR_3
#ifdef UMCTL2_SBR_EN_1
typedef struct tag_REGB_ARB_PORT0_SBRCTL_struct {
   uint32_t scrub_en;
   uint32_t scrub_during_lowpower;
   uint32_t scrub_en_dch1;
   uint32_t scrub_burst_length_normal;
   uint32_t scrub_interval;
   uint32_t scrub_cmd_type;
   uint32_t gen_rmw;
   uint32_t scrub_burst_length_lp;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRCTL_struct_t;

#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
typedef struct tag_REGB_ARB_PORT0_SBRWDATA0_struct {
   uint32_t scrub_pattern0;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRWDATA0_struct_t;

#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
#ifdef MEMC_DRAM_DATA_WIDTH_64
typedef struct tag_REGB_ARB_PORT0_SBRWDATA1_struct {
   uint32_t scrub_pattern1;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRWDATA1_struct_t;

#endif //MEMC_DRAM_DATA_WIDTH_64
#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
typedef struct tag_REGB_ARB_PORT0_SBRSTART0_struct {
   uint32_t sbr_address_start_mask_0;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRSTART0_struct_t;

#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
typedef struct tag_REGB_ARB_PORT0_SBRSTART1_struct {
   uint32_t sbr_address_start_mask_1;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRSTART1_struct_t;

#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
typedef struct tag_REGB_ARB_PORT0_SBRRANGE0_struct {
   uint32_t sbr_address_range_mask_0;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRRANGE0_struct_t;

#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
typedef struct tag_REGB_ARB_PORT0_SBRRANGE1_struct {
   uint32_t sbr_address_range_mask_1;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRRANGE1_struct_t;

#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
#ifdef UMCTL2_DUAL_DATA_CHANNEL
typedef struct tag_REGB_ARB_PORT0_SBRSTART0DCH1_struct {
   uint32_t sbr_address_start_mask_dch1_0;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRSTART0DCH1_struct_t;

#endif //UMCTL2_DUAL_DATA_CHANNEL
#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
#ifdef UMCTL2_DUAL_DATA_CHANNEL
typedef struct tag_REGB_ARB_PORT0_SBRSTART1DCH1_struct {
   uint32_t sbr_address_start_mask_dch1_1;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRSTART1DCH1_struct_t;

#endif //UMCTL2_DUAL_DATA_CHANNEL
#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
#ifdef UMCTL2_DUAL_DATA_CHANNEL
typedef struct tag_REGB_ARB_PORT0_SBRRANGE0DCH1_struct {
   uint32_t sbr_address_range_mask_dch1_0;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRRANGE0DCH1_struct_t;

#endif //UMCTL2_DUAL_DATA_CHANNEL
#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_SBR_EN_1
#ifdef UMCTL2_DUAL_DATA_CHANNEL
typedef struct tag_REGB_ARB_PORT0_SBRRANGE1DCH1_struct {
   uint32_t sbr_address_range_mask_dch1_1;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_SBRRANGE1DCH1_struct_t;

#endif //UMCTL2_DUAL_DATA_CHANNEL
#endif //UMCTL2_SBR_EN_1
#ifdef UMCTL2_DUAL_DATA_CHANNEL
#ifndef UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
typedef struct tag_REGB_ARB_PORT0_PDCH_struct {
   uint32_t port_data_channel_0;
   uint32_t port_data_channel_1;
   uint32_t port_data_channel_2;
   uint32_t port_data_channel_3;
   uint32_t port_data_channel_4;
   uint32_t port_data_channel_5;
   uint32_t port_data_channel_6;
   uint32_t port_data_channel_7;
   uint32_t port_data_channel_8;
   uint32_t port_data_channel_9;
   uint32_t port_data_channel_10;
   uint32_t port_data_channel_11;
   uint32_t port_data_channel_12;
   uint32_t port_data_channel_13;
   uint32_t port_data_channel_14;
   uint32_t port_data_channel_15;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT0_PDCH_struct_t;

#endif //UMCTL2_DATA_CHANNEL_INTERLEAVE_EN_1
#endif //UMCTL2_DUAL_DATA_CHANNEL
typedef struct tag_REGB_ARB_PORT1_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT1_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_1
#ifdef UMCTL2_PORT_CH0_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_1
#ifdef UMCTL2_PORT_CH1_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_1
#ifdef UMCTL2_PORT_CH1_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_1
#ifdef UMCTL2_PORT_CH2_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_1
#ifdef UMCTL2_PORT_CH2_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_1
#ifdef UMCTL2_PORT_CH3_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_1
#ifdef UMCTL2_PORT_CH3_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_1
#ifdef UMCTL2_PORT_CH4_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_1
#ifdef UMCTL2_PORT_CH4_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_1
#ifdef UMCTL2_PORT_CH5_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_1
#ifdef UMCTL2_PORT_CH5_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_1
#ifdef UMCTL2_PORT_CH6_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_1
#ifdef UMCTL2_PORT_CH6_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_1
#ifdef UMCTL2_PORT_CH7_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_1
#ifdef UMCTL2_PORT_CH7_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_1
#ifdef UMCTL2_PORT_CH8_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_1
#ifdef UMCTL2_PORT_CH8_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_1
#ifdef UMCTL2_PORT_CH9_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_1
#ifdef UMCTL2_PORT_CH9_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_1
#ifdef UMCTL2_PORT_CH10_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_1
#ifdef UMCTL2_PORT_CH10_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_1
#ifdef UMCTL2_PORT_CH11_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_1
#ifdef UMCTL2_PORT_CH11_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_1
#ifdef UMCTL2_PORT_CH12_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_1
#ifdef UMCTL2_PORT_CH12_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_1
#ifdef UMCTL2_PORT_CH13_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_1
#ifdef UMCTL2_PORT_CH13_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_1
#ifdef UMCTL2_PORT_CH14_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_1
#ifdef UMCTL2_PORT_CH14_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_1
#ifdef UMCTL2_PORT_CH15_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_1
#ifdef UMCTL2_PORT_CH15_1
typedef struct tag_REGB_ARB_PORT1_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_1
typedef struct tag_REGB_ARB_PORT1_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT1_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT1_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT1_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT1_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT1_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT2_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT2_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_2
#ifdef UMCTL2_PORT_CH0_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_2
#ifdef UMCTL2_PORT_CH1_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_2
#ifdef UMCTL2_PORT_CH1_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_2
#ifdef UMCTL2_PORT_CH2_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_2
#ifdef UMCTL2_PORT_CH2_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_2
#ifdef UMCTL2_PORT_CH3_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_2
#ifdef UMCTL2_PORT_CH3_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_2
#ifdef UMCTL2_PORT_CH4_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_2
#ifdef UMCTL2_PORT_CH4_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_2
#ifdef UMCTL2_PORT_CH5_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_2
#ifdef UMCTL2_PORT_CH5_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_2
#ifdef UMCTL2_PORT_CH6_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_2
#ifdef UMCTL2_PORT_CH6_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_2
#ifdef UMCTL2_PORT_CH7_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_2
#ifdef UMCTL2_PORT_CH7_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_2
#ifdef UMCTL2_PORT_CH8_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_2
#ifdef UMCTL2_PORT_CH8_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_2
#ifdef UMCTL2_PORT_CH9_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_2
#ifdef UMCTL2_PORT_CH9_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_2
#ifdef UMCTL2_PORT_CH10_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_2
#ifdef UMCTL2_PORT_CH10_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_2
#ifdef UMCTL2_PORT_CH11_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_2
#ifdef UMCTL2_PORT_CH11_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_2
#ifdef UMCTL2_PORT_CH12_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_2
#ifdef UMCTL2_PORT_CH12_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_2
#ifdef UMCTL2_PORT_CH13_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_2
#ifdef UMCTL2_PORT_CH13_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_2
#ifdef UMCTL2_PORT_CH14_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_2
#ifdef UMCTL2_PORT_CH14_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_2
#ifdef UMCTL2_PORT_CH15_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_2
#ifdef UMCTL2_PORT_CH15_2
typedef struct tag_REGB_ARB_PORT2_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_2
typedef struct tag_REGB_ARB_PORT2_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT2_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT2_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT2_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT2_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT2_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT3_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT3_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_3
#ifdef UMCTL2_PORT_CH0_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_3
#ifdef UMCTL2_PORT_CH1_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_3
#ifdef UMCTL2_PORT_CH1_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_3
#ifdef UMCTL2_PORT_CH2_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_3
#ifdef UMCTL2_PORT_CH2_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_3
#ifdef UMCTL2_PORT_CH3_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_3
#ifdef UMCTL2_PORT_CH3_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_3
#ifdef UMCTL2_PORT_CH4_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_3
#ifdef UMCTL2_PORT_CH4_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_3
#ifdef UMCTL2_PORT_CH5_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_3
#ifdef UMCTL2_PORT_CH5_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_3
#ifdef UMCTL2_PORT_CH6_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_3
#ifdef UMCTL2_PORT_CH6_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_3
#ifdef UMCTL2_PORT_CH7_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_3
#ifdef UMCTL2_PORT_CH7_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_3
#ifdef UMCTL2_PORT_CH8_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_3
#ifdef UMCTL2_PORT_CH8_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_3
#ifdef UMCTL2_PORT_CH9_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_3
#ifdef UMCTL2_PORT_CH9_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_3
#ifdef UMCTL2_PORT_CH10_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_3
#ifdef UMCTL2_PORT_CH10_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_3
#ifdef UMCTL2_PORT_CH11_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_3
#ifdef UMCTL2_PORT_CH11_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_3
#ifdef UMCTL2_PORT_CH12_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_3
#ifdef UMCTL2_PORT_CH12_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_3
#ifdef UMCTL2_PORT_CH13_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_3
#ifdef UMCTL2_PORT_CH13_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_3
#ifdef UMCTL2_PORT_CH14_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_3
#ifdef UMCTL2_PORT_CH14_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_3
#ifdef UMCTL2_PORT_CH15_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_3
#ifdef UMCTL2_PORT_CH15_3
typedef struct tag_REGB_ARB_PORT3_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_3
typedef struct tag_REGB_ARB_PORT3_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT3_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT3_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT3_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT3_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT3_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT4_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT4_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_4
#ifdef UMCTL2_PORT_CH0_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_4
#ifdef UMCTL2_PORT_CH1_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_4
#ifdef UMCTL2_PORT_CH1_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_4
#ifdef UMCTL2_PORT_CH2_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_4
#ifdef UMCTL2_PORT_CH2_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_4
#ifdef UMCTL2_PORT_CH3_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_4
#ifdef UMCTL2_PORT_CH3_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_4
#ifdef UMCTL2_PORT_CH4_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_4
#ifdef UMCTL2_PORT_CH4_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_4
#ifdef UMCTL2_PORT_CH5_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_4
#ifdef UMCTL2_PORT_CH5_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_4
#ifdef UMCTL2_PORT_CH6_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_4
#ifdef UMCTL2_PORT_CH6_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_4
#ifdef UMCTL2_PORT_CH7_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_4
#ifdef UMCTL2_PORT_CH7_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_4
#ifdef UMCTL2_PORT_CH8_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_4
#ifdef UMCTL2_PORT_CH8_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_4
#ifdef UMCTL2_PORT_CH9_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_4
#ifdef UMCTL2_PORT_CH9_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_4
#ifdef UMCTL2_PORT_CH10_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_4
#ifdef UMCTL2_PORT_CH10_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_4
#ifdef UMCTL2_PORT_CH11_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_4
#ifdef UMCTL2_PORT_CH11_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_4
#ifdef UMCTL2_PORT_CH12_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_4
#ifdef UMCTL2_PORT_CH12_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_4
#ifdef UMCTL2_PORT_CH13_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_4
#ifdef UMCTL2_PORT_CH13_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_4
#ifdef UMCTL2_PORT_CH14_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_4
#ifdef UMCTL2_PORT_CH14_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_4
#ifdef UMCTL2_PORT_CH15_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_4
#ifdef UMCTL2_PORT_CH15_4
typedef struct tag_REGB_ARB_PORT4_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_4
typedef struct tag_REGB_ARB_PORT4_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT4_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT4_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT4_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT4_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT4_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT5_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT5_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_5
#ifdef UMCTL2_PORT_CH0_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_5
#ifdef UMCTL2_PORT_CH1_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_5
#ifdef UMCTL2_PORT_CH1_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_5
#ifdef UMCTL2_PORT_CH2_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_5
#ifdef UMCTL2_PORT_CH2_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_5
#ifdef UMCTL2_PORT_CH3_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_5
#ifdef UMCTL2_PORT_CH3_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_5
#ifdef UMCTL2_PORT_CH4_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_5
#ifdef UMCTL2_PORT_CH4_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_5
#ifdef UMCTL2_PORT_CH5_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_5
#ifdef UMCTL2_PORT_CH5_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_5
#ifdef UMCTL2_PORT_CH6_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_5
#ifdef UMCTL2_PORT_CH6_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_5
#ifdef UMCTL2_PORT_CH7_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_5
#ifdef UMCTL2_PORT_CH7_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_5
#ifdef UMCTL2_PORT_CH8_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_5
#ifdef UMCTL2_PORT_CH8_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_5
#ifdef UMCTL2_PORT_CH9_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_5
#ifdef UMCTL2_PORT_CH9_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_5
#ifdef UMCTL2_PORT_CH10_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_5
#ifdef UMCTL2_PORT_CH10_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_5
#ifdef UMCTL2_PORT_CH11_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_5
#ifdef UMCTL2_PORT_CH11_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_5
#ifdef UMCTL2_PORT_CH12_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_5
#ifdef UMCTL2_PORT_CH12_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_5
#ifdef UMCTL2_PORT_CH13_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_5
#ifdef UMCTL2_PORT_CH13_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_5
#ifdef UMCTL2_PORT_CH14_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_5
#ifdef UMCTL2_PORT_CH14_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_5
#ifdef UMCTL2_PORT_CH15_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_5
#ifdef UMCTL2_PORT_CH15_5
typedef struct tag_REGB_ARB_PORT5_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_5
typedef struct tag_REGB_ARB_PORT5_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT5_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT5_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT5_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT5_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT5_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT6_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT6_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_6
#ifdef UMCTL2_PORT_CH0_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_6
#ifdef UMCTL2_PORT_CH1_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_6
#ifdef UMCTL2_PORT_CH1_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_6
#ifdef UMCTL2_PORT_CH2_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_6
#ifdef UMCTL2_PORT_CH2_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_6
#ifdef UMCTL2_PORT_CH3_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_6
#ifdef UMCTL2_PORT_CH3_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_6
#ifdef UMCTL2_PORT_CH4_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_6
#ifdef UMCTL2_PORT_CH4_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_6
#ifdef UMCTL2_PORT_CH5_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_6
#ifdef UMCTL2_PORT_CH5_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_6
#ifdef UMCTL2_PORT_CH6_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_6
#ifdef UMCTL2_PORT_CH6_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_6
#ifdef UMCTL2_PORT_CH7_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_6
#ifdef UMCTL2_PORT_CH7_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_6
#ifdef UMCTL2_PORT_CH8_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_6
#ifdef UMCTL2_PORT_CH8_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_6
#ifdef UMCTL2_PORT_CH9_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_6
#ifdef UMCTL2_PORT_CH9_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_6
#ifdef UMCTL2_PORT_CH10_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_6
#ifdef UMCTL2_PORT_CH10_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_6
#ifdef UMCTL2_PORT_CH11_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_6
#ifdef UMCTL2_PORT_CH11_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_6
#ifdef UMCTL2_PORT_CH12_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_6
#ifdef UMCTL2_PORT_CH12_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_6
#ifdef UMCTL2_PORT_CH13_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_6
#ifdef UMCTL2_PORT_CH13_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_6
#ifdef UMCTL2_PORT_CH14_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_6
#ifdef UMCTL2_PORT_CH14_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_6
#ifdef UMCTL2_PORT_CH15_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_6
#ifdef UMCTL2_PORT_CH15_6
typedef struct tag_REGB_ARB_PORT6_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_6
typedef struct tag_REGB_ARB_PORT6_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT6_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT6_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT6_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT6_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT6_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT7_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT7_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_7
#ifdef UMCTL2_PORT_CH0_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_7
#ifdef UMCTL2_PORT_CH1_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_7
#ifdef UMCTL2_PORT_CH1_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_7
#ifdef UMCTL2_PORT_CH2_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_7
#ifdef UMCTL2_PORT_CH2_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_7
#ifdef UMCTL2_PORT_CH3_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_7
#ifdef UMCTL2_PORT_CH3_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_7
#ifdef UMCTL2_PORT_CH4_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_7
#ifdef UMCTL2_PORT_CH4_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_7
#ifdef UMCTL2_PORT_CH5_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_7
#ifdef UMCTL2_PORT_CH5_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_7
#ifdef UMCTL2_PORT_CH6_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_7
#ifdef UMCTL2_PORT_CH6_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_7
#ifdef UMCTL2_PORT_CH7_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_7
#ifdef UMCTL2_PORT_CH7_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_7
#ifdef UMCTL2_PORT_CH8_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_7
#ifdef UMCTL2_PORT_CH8_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_7
#ifdef UMCTL2_PORT_CH9_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_7
#ifdef UMCTL2_PORT_CH9_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_7
#ifdef UMCTL2_PORT_CH10_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_7
#ifdef UMCTL2_PORT_CH10_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_7
#ifdef UMCTL2_PORT_CH11_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_7
#ifdef UMCTL2_PORT_CH11_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_7
#ifdef UMCTL2_PORT_CH12_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_7
#ifdef UMCTL2_PORT_CH12_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_7
#ifdef UMCTL2_PORT_CH13_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_7
#ifdef UMCTL2_PORT_CH13_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_7
#ifdef UMCTL2_PORT_CH14_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_7
#ifdef UMCTL2_PORT_CH14_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_7
#ifdef UMCTL2_PORT_CH15_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_7
#ifdef UMCTL2_PORT_CH15_7
typedef struct tag_REGB_ARB_PORT7_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_7
typedef struct tag_REGB_ARB_PORT7_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT7_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT7_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT7_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT7_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT7_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT8_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT8_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_8
#ifdef UMCTL2_PORT_CH0_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_8
#ifdef UMCTL2_PORT_CH1_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_8
#ifdef UMCTL2_PORT_CH1_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_8
#ifdef UMCTL2_PORT_CH2_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_8
#ifdef UMCTL2_PORT_CH2_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_8
#ifdef UMCTL2_PORT_CH3_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_8
#ifdef UMCTL2_PORT_CH3_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_8
#ifdef UMCTL2_PORT_CH4_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_8
#ifdef UMCTL2_PORT_CH4_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_8
#ifdef UMCTL2_PORT_CH5_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_8
#ifdef UMCTL2_PORT_CH5_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_8
#ifdef UMCTL2_PORT_CH6_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_8
#ifdef UMCTL2_PORT_CH6_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_8
#ifdef UMCTL2_PORT_CH7_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_8
#ifdef UMCTL2_PORT_CH7_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_8
#ifdef UMCTL2_PORT_CH8_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_8
#ifdef UMCTL2_PORT_CH8_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_8
#ifdef UMCTL2_PORT_CH9_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_8
#ifdef UMCTL2_PORT_CH9_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_8
#ifdef UMCTL2_PORT_CH10_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_8
#ifdef UMCTL2_PORT_CH10_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_8
#ifdef UMCTL2_PORT_CH11_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_8
#ifdef UMCTL2_PORT_CH11_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_8
#ifdef UMCTL2_PORT_CH12_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_8
#ifdef UMCTL2_PORT_CH12_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_8
#ifdef UMCTL2_PORT_CH13_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_8
#ifdef UMCTL2_PORT_CH13_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_8
#ifdef UMCTL2_PORT_CH14_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_8
#ifdef UMCTL2_PORT_CH14_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_8
#ifdef UMCTL2_PORT_CH15_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_8
#ifdef UMCTL2_PORT_CH15_8
typedef struct tag_REGB_ARB_PORT8_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_8
typedef struct tag_REGB_ARB_PORT8_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT8_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT8_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT8_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT8_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT8_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT9_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT9_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_9
#ifdef UMCTL2_PORT_CH0_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_9
#ifdef UMCTL2_PORT_CH1_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_9
#ifdef UMCTL2_PORT_CH1_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_9
#ifdef UMCTL2_PORT_CH2_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_9
#ifdef UMCTL2_PORT_CH2_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_9
#ifdef UMCTL2_PORT_CH3_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_9
#ifdef UMCTL2_PORT_CH3_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_9
#ifdef UMCTL2_PORT_CH4_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_9
#ifdef UMCTL2_PORT_CH4_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_9
#ifdef UMCTL2_PORT_CH5_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_9
#ifdef UMCTL2_PORT_CH5_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_9
#ifdef UMCTL2_PORT_CH6_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_9
#ifdef UMCTL2_PORT_CH6_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_9
#ifdef UMCTL2_PORT_CH7_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_9
#ifdef UMCTL2_PORT_CH7_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_9
#ifdef UMCTL2_PORT_CH8_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_9
#ifdef UMCTL2_PORT_CH8_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_9
#ifdef UMCTL2_PORT_CH9_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_9
#ifdef UMCTL2_PORT_CH9_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_9
#ifdef UMCTL2_PORT_CH10_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_9
#ifdef UMCTL2_PORT_CH10_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_9
#ifdef UMCTL2_PORT_CH11_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_9
#ifdef UMCTL2_PORT_CH11_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_9
#ifdef UMCTL2_PORT_CH12_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_9
#ifdef UMCTL2_PORT_CH12_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_9
#ifdef UMCTL2_PORT_CH13_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_9
#ifdef UMCTL2_PORT_CH13_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_9
#ifdef UMCTL2_PORT_CH14_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_9
#ifdef UMCTL2_PORT_CH14_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_9
#ifdef UMCTL2_PORT_CH15_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_9
#ifdef UMCTL2_PORT_CH15_9
typedef struct tag_REGB_ARB_PORT9_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_9
typedef struct tag_REGB_ARB_PORT9_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT9_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT9_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT9_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT9_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT9_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT10_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT10_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_10
#ifdef UMCTL2_PORT_CH0_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_10
#ifdef UMCTL2_PORT_CH1_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_10
#ifdef UMCTL2_PORT_CH1_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_10
#ifdef UMCTL2_PORT_CH2_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_10
#ifdef UMCTL2_PORT_CH2_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_10
#ifdef UMCTL2_PORT_CH3_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_10
#ifdef UMCTL2_PORT_CH3_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_10
#ifdef UMCTL2_PORT_CH4_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_10
#ifdef UMCTL2_PORT_CH4_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_10
#ifdef UMCTL2_PORT_CH5_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_10
#ifdef UMCTL2_PORT_CH5_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_10
#ifdef UMCTL2_PORT_CH6_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_10
#ifdef UMCTL2_PORT_CH6_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_10
#ifdef UMCTL2_PORT_CH7_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_10
#ifdef UMCTL2_PORT_CH7_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_10
#ifdef UMCTL2_PORT_CH8_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_10
#ifdef UMCTL2_PORT_CH8_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_10
#ifdef UMCTL2_PORT_CH9_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_10
#ifdef UMCTL2_PORT_CH9_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_10
#ifdef UMCTL2_PORT_CH10_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_10
#ifdef UMCTL2_PORT_CH10_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_10
#ifdef UMCTL2_PORT_CH11_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_10
#ifdef UMCTL2_PORT_CH11_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_10
#ifdef UMCTL2_PORT_CH12_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_10
#ifdef UMCTL2_PORT_CH12_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_10
#ifdef UMCTL2_PORT_CH13_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_10
#ifdef UMCTL2_PORT_CH13_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_10
#ifdef UMCTL2_PORT_CH14_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_10
#ifdef UMCTL2_PORT_CH14_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_10
#ifdef UMCTL2_PORT_CH15_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_10
#ifdef UMCTL2_PORT_CH15_10
typedef struct tag_REGB_ARB_PORT10_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_10
typedef struct tag_REGB_ARB_PORT10_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT10_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT10_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT10_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT10_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT10_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT11_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT11_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_11
#ifdef UMCTL2_PORT_CH0_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_11
#ifdef UMCTL2_PORT_CH1_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_11
#ifdef UMCTL2_PORT_CH1_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_11
#ifdef UMCTL2_PORT_CH2_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_11
#ifdef UMCTL2_PORT_CH2_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_11
#ifdef UMCTL2_PORT_CH3_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_11
#ifdef UMCTL2_PORT_CH3_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_11
#ifdef UMCTL2_PORT_CH4_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_11
#ifdef UMCTL2_PORT_CH4_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_11
#ifdef UMCTL2_PORT_CH5_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_11
#ifdef UMCTL2_PORT_CH5_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_11
#ifdef UMCTL2_PORT_CH6_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_11
#ifdef UMCTL2_PORT_CH6_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_11
#ifdef UMCTL2_PORT_CH7_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_11
#ifdef UMCTL2_PORT_CH7_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_11
#ifdef UMCTL2_PORT_CH8_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_11
#ifdef UMCTL2_PORT_CH8_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_11
#ifdef UMCTL2_PORT_CH9_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_11
#ifdef UMCTL2_PORT_CH9_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_11
#ifdef UMCTL2_PORT_CH10_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_11
#ifdef UMCTL2_PORT_CH10_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_11
#ifdef UMCTL2_PORT_CH11_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_11
#ifdef UMCTL2_PORT_CH11_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_11
#ifdef UMCTL2_PORT_CH12_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_11
#ifdef UMCTL2_PORT_CH12_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_11
#ifdef UMCTL2_PORT_CH13_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_11
#ifdef UMCTL2_PORT_CH13_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_11
#ifdef UMCTL2_PORT_CH14_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_11
#ifdef UMCTL2_PORT_CH14_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_11
#ifdef UMCTL2_PORT_CH15_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_11
#ifdef UMCTL2_PORT_CH15_11
typedef struct tag_REGB_ARB_PORT11_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_11
typedef struct tag_REGB_ARB_PORT11_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT11_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT11_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT11_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT11_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT11_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT12_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT12_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_12
#ifdef UMCTL2_PORT_CH0_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_12
#ifdef UMCTL2_PORT_CH1_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_12
#ifdef UMCTL2_PORT_CH1_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_12
#ifdef UMCTL2_PORT_CH2_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_12
#ifdef UMCTL2_PORT_CH2_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_12
#ifdef UMCTL2_PORT_CH3_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_12
#ifdef UMCTL2_PORT_CH3_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_12
#ifdef UMCTL2_PORT_CH4_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_12
#ifdef UMCTL2_PORT_CH4_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_12
#ifdef UMCTL2_PORT_CH5_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_12
#ifdef UMCTL2_PORT_CH5_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_12
#ifdef UMCTL2_PORT_CH6_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_12
#ifdef UMCTL2_PORT_CH6_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_12
#ifdef UMCTL2_PORT_CH7_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_12
#ifdef UMCTL2_PORT_CH7_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_12
#ifdef UMCTL2_PORT_CH8_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_12
#ifdef UMCTL2_PORT_CH8_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_12
#ifdef UMCTL2_PORT_CH9_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_12
#ifdef UMCTL2_PORT_CH9_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_12
#ifdef UMCTL2_PORT_CH10_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_12
#ifdef UMCTL2_PORT_CH10_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_12
#ifdef UMCTL2_PORT_CH11_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_12
#ifdef UMCTL2_PORT_CH11_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_12
#ifdef UMCTL2_PORT_CH12_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_12
#ifdef UMCTL2_PORT_CH12_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_12
#ifdef UMCTL2_PORT_CH13_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_12
#ifdef UMCTL2_PORT_CH13_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_12
#ifdef UMCTL2_PORT_CH14_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_12
#ifdef UMCTL2_PORT_CH14_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_12
#ifdef UMCTL2_PORT_CH15_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_12
#ifdef UMCTL2_PORT_CH15_12
typedef struct tag_REGB_ARB_PORT12_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_12
typedef struct tag_REGB_ARB_PORT12_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT12_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT12_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT12_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT12_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT12_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT13_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT13_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_13
#ifdef UMCTL2_PORT_CH0_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_13
#ifdef UMCTL2_PORT_CH1_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_13
#ifdef UMCTL2_PORT_CH1_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_13
#ifdef UMCTL2_PORT_CH2_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_13
#ifdef UMCTL2_PORT_CH2_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_13
#ifdef UMCTL2_PORT_CH3_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_13
#ifdef UMCTL2_PORT_CH3_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_13
#ifdef UMCTL2_PORT_CH4_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_13
#ifdef UMCTL2_PORT_CH4_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_13
#ifdef UMCTL2_PORT_CH5_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_13
#ifdef UMCTL2_PORT_CH5_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_13
#ifdef UMCTL2_PORT_CH6_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_13
#ifdef UMCTL2_PORT_CH6_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_13
#ifdef UMCTL2_PORT_CH7_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_13
#ifdef UMCTL2_PORT_CH7_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_13
#ifdef UMCTL2_PORT_CH8_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_13
#ifdef UMCTL2_PORT_CH8_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_13
#ifdef UMCTL2_PORT_CH9_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_13
#ifdef UMCTL2_PORT_CH9_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_13
#ifdef UMCTL2_PORT_CH10_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_13
#ifdef UMCTL2_PORT_CH10_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_13
#ifdef UMCTL2_PORT_CH11_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_13
#ifdef UMCTL2_PORT_CH11_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_13
#ifdef UMCTL2_PORT_CH12_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_13
#ifdef UMCTL2_PORT_CH12_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_13
#ifdef UMCTL2_PORT_CH13_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_13
#ifdef UMCTL2_PORT_CH13_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_13
#ifdef UMCTL2_PORT_CH14_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_13
#ifdef UMCTL2_PORT_CH14_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_13
#ifdef UMCTL2_PORT_CH15_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_13
#ifdef UMCTL2_PORT_CH15_13
typedef struct tag_REGB_ARB_PORT13_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_13
typedef struct tag_REGB_ARB_PORT13_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT13_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT13_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT13_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT13_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT13_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT14_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT14_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_14
#ifdef UMCTL2_PORT_CH0_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_14
#ifdef UMCTL2_PORT_CH1_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_14
#ifdef UMCTL2_PORT_CH1_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_14
#ifdef UMCTL2_PORT_CH2_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_14
#ifdef UMCTL2_PORT_CH2_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_14
#ifdef UMCTL2_PORT_CH3_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_14
#ifdef UMCTL2_PORT_CH3_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_14
#ifdef UMCTL2_PORT_CH4_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_14
#ifdef UMCTL2_PORT_CH4_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_14
#ifdef UMCTL2_PORT_CH5_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_14
#ifdef UMCTL2_PORT_CH5_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_14
#ifdef UMCTL2_PORT_CH6_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_14
#ifdef UMCTL2_PORT_CH6_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_14
#ifdef UMCTL2_PORT_CH7_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_14
#ifdef UMCTL2_PORT_CH7_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_14
#ifdef UMCTL2_PORT_CH8_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_14
#ifdef UMCTL2_PORT_CH8_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_14
#ifdef UMCTL2_PORT_CH9_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_14
#ifdef UMCTL2_PORT_CH9_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_14
#ifdef UMCTL2_PORT_CH10_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_14
#ifdef UMCTL2_PORT_CH10_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_14
#ifdef UMCTL2_PORT_CH11_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_14
#ifdef UMCTL2_PORT_CH11_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_14
#ifdef UMCTL2_PORT_CH12_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_14
#ifdef UMCTL2_PORT_CH12_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_14
#ifdef UMCTL2_PORT_CH13_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_14
#ifdef UMCTL2_PORT_CH13_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_14
#ifdef UMCTL2_PORT_CH14_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_14
#ifdef UMCTL2_PORT_CH14_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_14
#ifdef UMCTL2_PORT_CH15_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_14
#ifdef UMCTL2_PORT_CH15_14
typedef struct tag_REGB_ARB_PORT14_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_14
typedef struct tag_REGB_ARB_PORT14_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT14_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT14_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT14_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT14_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT14_PCFGWQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT15_PCFGR_struct {
   uint32_t rd_port_priority;
   uint32_t read_reorder_bypass_en;
   uint32_t rd_port_aging_en;
   uint32_t rd_port_urgent_en;
   uint32_t rd_port_pagematch_en;
   uint32_t rdwr_ordered_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGR_struct_t;

typedef struct tag_REGB_ARB_PORT15_PCFGW_struct {
   uint32_t wr_port_priority;
   uint32_t wr_port_aging_en;
   uint32_t wr_port_urgent_en;
   uint32_t wr_port_pagematch_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGW_struct_t;

#ifdef UMCTL2_PORT_CH0_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH0_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH0_struct_t;

#endif //UMCTL2_PORT_CH0_15
#ifdef UMCTL2_PORT_CH0_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH0_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH0_struct_t;

#endif //UMCTL2_PORT_CH0_15
#ifdef UMCTL2_PORT_CH1_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH1_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH1_struct_t;

#endif //UMCTL2_PORT_CH1_15
#ifdef UMCTL2_PORT_CH1_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH1_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH1_struct_t;

#endif //UMCTL2_PORT_CH1_15
#ifdef UMCTL2_PORT_CH2_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH2_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH2_struct_t;

#endif //UMCTL2_PORT_CH2_15
#ifdef UMCTL2_PORT_CH2_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH2_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH2_struct_t;

#endif //UMCTL2_PORT_CH2_15
#ifdef UMCTL2_PORT_CH3_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH3_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH3_struct_t;

#endif //UMCTL2_PORT_CH3_15
#ifdef UMCTL2_PORT_CH3_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH3_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH3_struct_t;

#endif //UMCTL2_PORT_CH3_15
#ifdef UMCTL2_PORT_CH4_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH4_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH4_struct_t;

#endif //UMCTL2_PORT_CH4_15
#ifdef UMCTL2_PORT_CH4_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH4_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH4_struct_t;

#endif //UMCTL2_PORT_CH4_15
#ifdef UMCTL2_PORT_CH5_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH5_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH5_struct_t;

#endif //UMCTL2_PORT_CH5_15
#ifdef UMCTL2_PORT_CH5_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH5_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH5_struct_t;

#endif //UMCTL2_PORT_CH5_15
#ifdef UMCTL2_PORT_CH6_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH6_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH6_struct_t;

#endif //UMCTL2_PORT_CH6_15
#ifdef UMCTL2_PORT_CH6_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH6_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH6_struct_t;

#endif //UMCTL2_PORT_CH6_15
#ifdef UMCTL2_PORT_CH7_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH7_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH7_struct_t;

#endif //UMCTL2_PORT_CH7_15
#ifdef UMCTL2_PORT_CH7_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH7_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH7_struct_t;

#endif //UMCTL2_PORT_CH7_15
#ifdef UMCTL2_PORT_CH8_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH8_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH8_struct_t;

#endif //UMCTL2_PORT_CH8_15
#ifdef UMCTL2_PORT_CH8_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH8_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH8_struct_t;

#endif //UMCTL2_PORT_CH8_15
#ifdef UMCTL2_PORT_CH9_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH9_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH9_struct_t;

#endif //UMCTL2_PORT_CH9_15
#ifdef UMCTL2_PORT_CH9_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH9_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH9_struct_t;

#endif //UMCTL2_PORT_CH9_15
#ifdef UMCTL2_PORT_CH10_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH10_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH10_struct_t;

#endif //UMCTL2_PORT_CH10_15
#ifdef UMCTL2_PORT_CH10_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH10_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH10_struct_t;

#endif //UMCTL2_PORT_CH10_15
#ifdef UMCTL2_PORT_CH11_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH11_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH11_struct_t;

#endif //UMCTL2_PORT_CH11_15
#ifdef UMCTL2_PORT_CH11_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH11_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH11_struct_t;

#endif //UMCTL2_PORT_CH11_15
#ifdef UMCTL2_PORT_CH12_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH12_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH12_struct_t;

#endif //UMCTL2_PORT_CH12_15
#ifdef UMCTL2_PORT_CH12_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH12_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH12_struct_t;

#endif //UMCTL2_PORT_CH12_15
#ifdef UMCTL2_PORT_CH13_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH13_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH13_struct_t;

#endif //UMCTL2_PORT_CH13_15
#ifdef UMCTL2_PORT_CH13_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH13_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH13_struct_t;

#endif //UMCTL2_PORT_CH13_15
#ifdef UMCTL2_PORT_CH14_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH14_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH14_struct_t;

#endif //UMCTL2_PORT_CH14_15
#ifdef UMCTL2_PORT_CH14_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH14_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH14_struct_t;

#endif //UMCTL2_PORT_CH14_15
#ifdef UMCTL2_PORT_CH15_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDMASKCH15_struct {
   uint32_t id_mask;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDMASKCH15_struct_t;

#endif //UMCTL2_PORT_CH15_15
#ifdef UMCTL2_PORT_CH15_15
typedef struct tag_REGB_ARB_PORT15_PCFGIDVALUECH15_struct {
   uint32_t id_value;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGIDVALUECH15_struct_t;

#endif //UMCTL2_PORT_CH15_15
typedef struct tag_REGB_ARB_PORT15_PCTRL_struct {
   uint32_t port_en;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCTRL_struct_t;

typedef struct tag_REGB_ARB_PORT15_PCFGQOS0_struct {
   uint32_t rqos_map_level1;
   uint32_t rqos_map_level2;
   uint32_t rqos_map_region0;
   uint32_t rqos_map_region1;
   uint32_t rqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT15_PCFGQOS1_struct {
   uint32_t rqos_map_timeoutb;
   uint32_t rqos_map_timeoutr;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGQOS1_struct_t;

typedef struct tag_REGB_ARB_PORT15_PCFGWQOS0_struct {
   uint32_t wqos_map_level1;
   uint32_t wqos_map_level2;
   uint32_t wqos_map_region0;
   uint32_t wqos_map_region1;
   uint32_t wqos_map_region2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGWQOS0_struct_t;

typedef struct tag_REGB_ARB_PORT15_PCFGWQOS1_struct {
   uint32_t wqos_map_timeout1;
   uint32_t wqos_map_timeout2;
  uint32_t value; // full 32-bit register value.
  } REGB_ARB_PORT15_PCFGWQOS1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG0_struct {
   uint32_t t_ras_min;
   uint32_t t_ras_max;
   uint32_t t_faw;
   uint32_t wr2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG1_struct {
   uint32_t t_rc;
   uint32_t rd2pre;
   uint32_t t_xp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG2_struct {
   uint32_t wr2rd;
   uint32_t rd2wr;
   uint32_t read_latency;
   uint32_t write_latency;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG2_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG3_struct {
   uint32_t wr2mr;
   uint32_t rd2mr;
   uint32_t t_mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG3_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG4_struct {
   uint32_t t_rp;
   uint32_t t_rrd;
   uint32_t t_ccd;
   uint32_t t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG4_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG5_struct {
   uint32_t t_cke;
   uint32_t t_ckesr;
   uint32_t t_cksre;
   uint32_t t_cksrx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG5_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG6_struct {
   uint32_t t_ckcsx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG6_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG7_struct {
   uint32_t t_csh;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG7_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG8_struct {
   uint32_t t_xs_x32;
   uint32_t t_xs_dll_x32;
   uint32_t t_xs_abort_x32;
   uint32_t t_xs_fast_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG8_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG9_struct {
   uint32_t wr2rd_s;
   uint32_t t_rrd_s;
   uint32_t t_ccd_s;
   uint32_t ddr4_wr_preamble;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG9_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG10_struct {
   uint32_t t_gear_hold;
   uint32_t t_gear_setup;
   uint32_t t_cmd_gear;
   uint32_t t_sync_gear;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG10_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG11_struct {
   uint32_t t_ckmpe;
   uint32_t t_mpx_s;
   uint32_t t_mpx_lh;
   uint32_t post_mpsm_gap_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG11_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG12_struct {
   uint32_t t_mrd_pda;
   uint32_t t_cmdcke;
   uint32_t t_wr_mpr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG12_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG13_struct {
   uint32_t t_ppd;
   uint32_t t_ccd_w2;
   uint32_t t_ccd_mw;
   uint32_t odtloff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG13_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG14_struct {
   uint32_t t_xsr;
   uint32_t t_osco;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG14_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG15_struct {
   uint32_t t_stab_x32;
   uint32_t en_hwffc_t_stab;
   uint32_t en_dfi_lp_t_stab;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG15_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG16_struct {
   uint32_t t_ccd_dlr;
   uint32_t t_rrd_dlr;
   uint32_t t_faw_dlr;
   uint32_t t_rp_ca_parity;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG16_struct_t;

#endif //UMCTL2_CID_EN
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG17_struct {
   uint32_t t_vrcg_disable;
   uint32_t t_vrcg_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG17_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG18_struct {
   uint32_t t_mpdpxact;
   uint32_t t_mpsmx;
   uint32_t t_pd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG18_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG19_struct {
   uint32_t t_pda_h;
   uint32_t t_pda_s;
   uint32_t t_pda_dqs_delay;
   uint32_t t_pda_delay;
   uint32_t t_pda_latch;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG19_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG20_struct {
   uint32_t t_csl_srexit;
   uint32_t t_csh_srexit;
   uint32_t t_casrx;
   uint32_t t_cpded;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG21_struct {
   uint32_t t_osco_ddr5;
   uint32_t t_vrefca_cs;
   uint32_t t_mpc_hold;
   uint32_t t_mpc_setup;
   uint32_t t_mpc_cs;
   uint32_t t_csl;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG22_struct {
   uint32_t t_rd2wr_dpr;
   uint32_t t_rd2wr_dlr;
   uint32_t t_wr2rd_dpr;
   uint32_t t_wr2rd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG22_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG23_struct {
   uint32_t t_pdn;
   uint32_t t_pdn_dsm_x1024;
   uint32_t t_xsr_dsm_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG23_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG24_struct {
   uint32_t max_wr_sync;
   uint32_t max_rd_sync;
   uint32_t rd2wr_s;
   uint32_t bank_org;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG24_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG25_struct {
   uint32_t rda2pre;
   uint32_t wra2pre;
   uint32_t lpddr4_diff_bank_rwa2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG25_struct_t;

#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG26_struct {
   uint32_t t_ccd_r;
   uint32_t t_ccd_w;
   uint32_t t_ccd_r_s;
   uint32_t t_ccd_w_s;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG26_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG27_struct {
   uint32_t t_mrr2mpc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG27_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG28_struct {
   uint32_t t_srx2srx;
   uint32_t t_cpded2srx;
   uint32_t t_cssr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG28_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG29_struct {
   uint32_t t_ckact;
   uint32_t t_ckoff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG29_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DRAMSET1TMG30_struct {
   uint32_t mrr2rd;
   uint32_t mrr2wr;
   uint32_t mrr2mrw;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET1TMG30_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG0_struct {
   uint32_t t_ccd_r_2;
   uint32_t t_ccd_w_2;
   uint32_t t_ccd_r_s_2;
   uint32_t t_ccd_w_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG1_struct {
   uint32_t t_ras_min_2;
   uint32_t t_faw_2;
   uint32_t t_wr2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG1_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG2_struct {
   uint32_t t_rc_2;
   uint32_t rd2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG3_struct {
   uint32_t wr2rd_2;
   uint32_t rd2wr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG3_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG4_struct {
   uint32_t t_rd2wr_dpr_2;
   uint32_t t_rd2wr_dlr_2;
   uint32_t t_wr2rd_dpr_2;
   uint32_t t_wr2rd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG4_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG5_struct {
   uint32_t t_rp_2;
   uint32_t t_rrd_2;
   uint32_t t_ccd_2;
   uint32_t t_rcd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG5_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG6_struct {
   uint32_t wr2rd_s_2;
   uint32_t t_rrd_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG6_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG7_struct {
   uint32_t t_ppd_2;
   uint32_t t_ccd_w2_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG7_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG8_struct {
   uint32_t t_ccd_dlr_2;
   uint32_t t_rrd_dlr_2;
   uint32_t t_faw_dlr_2;
   uint32_t t_rp_ca_parity_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG8_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG9_struct {
   uint32_t t_xs_x32_2;
   uint32_t t_xs_dll_x32_2;
   uint32_t t_xs_abort_x32_2;
   uint32_t t_xs_fast_x32_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG9_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG10_struct {
   uint32_t t_mr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG10_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_DRAMSET2TMG11_struct {
   uint32_t t_mrr2mpc_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DRAMSET2TMG11_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL0_struct {
   uint32_t t_rd2rd_gap_r0r1;
   uint32_t t_rd2rd_gap_r1r0;
   uint32_t t_wr2rd_gap_r0r1;
   uint32_t t_wr2rd_gap_r1r0;
   uint32_t t_rd2wr_gap_r0r1;
   uint32_t t_rd2wr_gap_r1r0;
   uint32_t t_wr2wr_gap_r0r1;
   uint32_t t_wr2wr_gap_r1r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL0_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL1_struct {
   uint32_t t_rd2rd_gap_r0r2;
   uint32_t t_rd2rd_gap_r2r0;
   uint32_t t_wr2rd_gap_r0r2;
   uint32_t t_wr2rd_gap_r2r0;
   uint32_t t_rd2wr_gap_r0r2;
   uint32_t t_rd2wr_gap_r2r0;
   uint32_t t_wr2wr_gap_r0r2;
   uint32_t t_wr2wr_gap_r2r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL1_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL2_struct {
   uint32_t t_rd2rd_gap_r0r3;
   uint32_t t_rd2rd_gap_r3r0;
   uint32_t t_wr2rd_gap_r0r3;
   uint32_t t_wr2rd_gap_r3r0;
   uint32_t t_rd2wr_gap_r0r3;
   uint32_t t_rd2wr_gap_r3r0;
   uint32_t t_wr2wr_gap_r0r3;
   uint32_t t_wr2wr_gap_r3r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL3_struct {
   uint32_t t_rd2rd_gap_r1r2;
   uint32_t t_rd2rd_gap_r2r1;
   uint32_t t_wr2rd_gap_r1r2;
   uint32_t t_wr2rd_gap_r2r1;
   uint32_t t_rd2wr_gap_r1r2;
   uint32_t t_rd2wr_gap_r2r1;
   uint32_t t_wr2wr_gap_r1r2;
   uint32_t t_wr2wr_gap_r2r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL4_struct {
   uint32_t t_rd2rd_gap_r1r3;
   uint32_t t_rd2rd_gap_r3r1;
   uint32_t t_wr2rd_gap_r1r3;
   uint32_t t_wr2rd_gap_r3r1;
   uint32_t t_rd2wr_gap_r1r3;
   uint32_t t_rd2wr_gap_r3r1;
   uint32_t t_wr2wr_gap_r1r3;
   uint32_t t_wr2wr_gap_r3r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL5_struct {
   uint32_t t_rd2rd_gap_r2r3;
   uint32_t t_rd2rd_gap_r3r2;
   uint32_t t_wr2rd_gap_r2r3;
   uint32_t t_wr2rd_gap_r3r2;
   uint32_t t_rd2wr_gap_r2r3;
   uint32_t t_rd2wr_gap_r3r2;
   uint32_t t_wr2wr_gap_r2r3;
   uint32_t t_wr2wr_gap_r3r2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANK_SWITCH_TIMING_CONTROL5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH0_MRAMTMG0_struct {
   uint32_t t_ras_min_mram;
   uint32_t t_faw_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_MRAMTMG0_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH0_MRAMTMG1_struct {
   uint32_t t_rc_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_MRAMTMG1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH0_MRAMTMG2_struct {
   uint32_t t_rp_mram;
   uint32_t t_rrd_mram;
   uint32_t t_rcd_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_MRAMTMG2_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH0_MRAMTMG3_struct {
   uint32_t t_rrd_s_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_MRAMTMG3_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH0_INITMR0_struct {
   uint32_t emr;
   uint32_t mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_INITMR0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_INITMR1_struct {
   uint32_t emr3;
   uint32_t emr2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_INITMR1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_INITMR2_struct {
   uint32_t mr5;
   uint32_t mr4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_INITMR2_struct_t;

typedef struct tag_REGB_FREQ0_CH0_INITMR3_struct {
   uint32_t mr6;
   uint32_t mr22;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_INITMR3_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DFITMG0_struct {
   uint32_t dfi_tphy_wrlat;
   uint32_t dfi_tphy_wrdata;
   uint32_t dfi_t_rddata_en;
   uint32_t dfi_t_ctrl_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DFITMG1_struct {
   uint32_t dfi_t_dram_clk_enable;
   uint32_t dfi_t_dram_clk_disable;
   uint32_t dfi_t_wrdata_delay;
   uint32_t dfi_t_parin_lat;
   uint32_t dfi_t_cmd_lat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DFITMG2_struct {
   uint32_t dfi_tphy_wrcslat;
   uint32_t dfi_tphy_rdcslat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG2_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ0_CH0_DFITMG3_struct {
   uint32_t dfi_t_geardown_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG3_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DFITMG4_struct {
   uint32_t dfi_twck_dis;
   uint32_t dfi_twck_en_fs;
   uint32_t dfi_twck_en_wr;
   uint32_t dfi_twck_en_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG4_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DFITMG5_struct {
   uint32_t dfi_twck_toggle_post;
   uint32_t dfi_twck_toggle_cs;
   uint32_t dfi_twck_toggle;
   uint32_t dfi_twck_fast_toggle;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG5_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DFITMG7_struct {
   uint32_t dfi_t_2n_mode_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFITMG7_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_DFILPTMG0_struct {
   uint32_t dfi_lp_wakeup_pd;
   uint32_t dfi_lp_wakeup_sr;
   uint32_t dfi_lp_wakeup_dsm;
   uint32_t dfi_lp_wakeup_mpsm;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFILPTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DFILPTMG1_struct {
   uint32_t dfi_lp_wakeup_data;
   uint32_t dfi_tlp_resp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFILPTMG1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DFIUPDTMG0_struct {
   uint32_t dfi_t_ctrlup_min;
   uint32_t dfi_t_ctrlup_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFIUPDTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DFIUPDTMG1_struct {
   uint32_t dfi_t_ctrlupd_interval_max_x1024;
   uint32_t dfi_t_ctrlupd_interval_min_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFIUPDTMG1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_DFIMSGTMG0_struct {
   uint32_t dfi_t_ctrlmsg_resp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DFIMSGTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG0_struct {
   uint32_t t_refi_x1_x32;
   uint32_t refresh_to_x1_x32;
   uint32_t refresh_margin;
   uint32_t t_refi_x1_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG1_struct {
   uint32_t t_rfc_min;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG1_struct_t;

#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG2_struct {
   uint32_t t_rfc_min_dlr;
   uint32_t t_pbr2pbr;
   uint32_t t_pbr2act;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG2_struct_t;

#endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG3_struct {
   uint32_t t_rfcsb;
   uint32_t t_refsbrd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG4_struct {
   uint32_t refresh_timer0_start_value_x32;
   uint32_t refresh_timer1_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG4_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG5_struct {
   uint32_t refresh_timer2_start_value_x32;
   uint32_t refresh_timer3_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG6_struct {
   uint32_t refresh_timer_lr_offset_x32;
   uint32_t refresh_timer_rank_offset_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG6_struct_t;

#endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG7_struct {
   uint32_t t_rfcsb_dlr;
   uint32_t t_refsbrd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG7_struct_t;

#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HET_RANK_RFC
typedef struct tag_REGB_FREQ0_CH0_RFSHSET1TMG8_struct {
   uint32_t t_rfc_min_het;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET1TMG8_struct_t;

#endif //UMCTL2_HET_RANK_RFC
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_RFSHSET2TMG0_struct {
   uint32_t t_rfc_min_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH0_RFSHSET2TMG1_struct {
   uint32_t t_rfc_min_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET2TMG1_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_RFSHSET2TMG2_struct {
   uint32_t t_rfcsb_2;
   uint32_t t_refsbrd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH0_RFSHSET2TMG3_struct {
   uint32_t t_rfcsb_dlr_2;
   uint32_t t_refsbrd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RFSHSET2TMG3_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH0_ZQSET1TMG0_struct {
   uint32_t t_zq_long_nop;
   uint32_t t_zq_short_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_ZQSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_ZQSET1TMG1_struct {
   uint32_t t_zq_short_interval_x1024;
   uint32_t t_zq_reset_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_ZQSET1TMG1_struct_t;

#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH0_ZQSET2TMG0_struct {
   uint32_t t_zq_long_nop_2;
   uint32_t t_zq_short_nop_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_ZQSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH0_RCDINIT1_struct {
   uint32_t ctrl_word_1;
   uint32_t ctrl_word_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RCDINIT1_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH0_RCDINIT2_struct {
   uint32_t ctrl_word_3;
   uint32_t ctrl_word_4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RCDINIT2_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH0_RCDINIT3_struct {
   uint32_t ctrl_word_5;
   uint32_t ctrl_word_6;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RCDINIT3_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH0_RCDINIT4_struct {
   uint32_t ctrl_word_7;
   uint32_t ctrl_word_8;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RCDINIT4_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_FREQ0_CH0_DQSOSCCTL0_struct {
   uint32_t dqsosc_enable;
   uint32_t dqsosc_interval_unit;
   uint32_t dqsosc_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DQSOSCCTL0_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DERATEINT_struct {
   uint32_t mr4_read_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DERATEINT_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DERATEVAL0_struct {
   uint32_t derated_t_rrd;
   uint32_t derated_t_rp;
   uint32_t derated_t_ras_min;
   uint32_t derated_t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DERATEVAL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_DERATEVAL1_struct {
   uint32_t derated_t_rc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_DERATEVAL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH0_HWLPTMG0_struct {
   uint32_t hw_lp_idle_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_HWLPTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_SCHEDTMG0_struct {
   uint32_t pageclose_timer;
   uint32_t rdwr_idle_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_SCHEDTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH0_PERFHPR1_struct {
   uint32_t hpr_max_starve;
   uint32_t hpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_PERFHPR1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_PERFLPR1_struct {
   uint32_t lpr_max_starve;
   uint32_t lpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_PERFLPR1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_PERFWR1_struct {
   uint32_t w_max_starve;
   uint32_t w_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_PERFWR1_struct_t;

typedef struct tag_REGB_FREQ0_CH0_TMGCFG_struct {
   uint32_t frequency_ratio;
   uint32_t dfi_freq_fsp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_TMGCFG_struct_t;

#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_FREQ0_CH0_RANKTMG0_struct {
   uint32_t diff_rank_rd_gap;
   uint32_t diff_rank_wr_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANKTMG0_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ0_CH0_RANKTMG1_struct {
   uint32_t wr2rd_dr;
   uint32_t rd2wr_dr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_RANKTMG1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ0_CH0_PWRTMG_struct {
   uint32_t powerdown_to_x32;
   uint32_t selfref_to_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_PWRTMG_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH0_ODTCFG_struct {
   uint32_t rd_odt_delay;
   uint32_t rd_odt_hold;
   uint32_t wr_odt_delay;
   uint32_t wr_odt_hold;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_ODTCFG_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct tag_REGB_FREQ0_CH0_CRCPARTMG0_struct {
   uint32_t retry_fifo_max_hold_timer_x4;
   uint32_t t_crc_alert_pw_max;
   uint32_t t_par_alert_pw_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_CRCPARTMG0_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ0_CH0_CRCPARTMG1_struct {
   uint32_t t_csalt;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH0_CRCPARTMG1_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG0_struct {
   uint32_t t_ras_min;
   uint32_t t_ras_max;
   uint32_t t_faw;
   uint32_t wr2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG1_struct {
   uint32_t t_rc;
   uint32_t rd2pre;
   uint32_t t_xp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG1_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG2_struct {
   uint32_t wr2rd;
   uint32_t rd2wr;
   uint32_t read_latency;
   uint32_t write_latency;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG2_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG3_struct {
   uint32_t wr2mr;
   uint32_t rd2mr;
   uint32_t t_mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG3_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG4_struct {
   uint32_t t_rp;
   uint32_t t_rrd;
   uint32_t t_ccd;
   uint32_t t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG4_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG5_struct {
   uint32_t t_cke;
   uint32_t t_ckesr;
   uint32_t t_cksre;
   uint32_t t_cksrx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG5_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG6_struct {
   uint32_t t_ckcsx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG6_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG7_struct {
   uint32_t t_csh;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG7_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG8_struct {
   uint32_t t_xs_x32;
   uint32_t t_xs_dll_x32;
   uint32_t t_xs_abort_x32;
   uint32_t t_xs_fast_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG8_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG9_struct {
   uint32_t wr2rd_s;
   uint32_t t_rrd_s;
   uint32_t t_ccd_s;
   uint32_t ddr4_wr_preamble;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG9_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG10_struct {
   uint32_t t_gear_hold;
   uint32_t t_gear_setup;
   uint32_t t_cmd_gear;
   uint32_t t_sync_gear;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG10_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG11_struct {
   uint32_t t_ckmpe;
   uint32_t t_mpx_s;
   uint32_t t_mpx_lh;
   uint32_t post_mpsm_gap_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG11_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG12_struct {
   uint32_t t_mrd_pda;
   uint32_t t_cmdcke;
   uint32_t t_wr_mpr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG12_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG13_struct {
   uint32_t t_ppd;
   uint32_t t_ccd_w2;
   uint32_t t_ccd_mw;
   uint32_t odtloff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG13_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG14_struct {
   uint32_t t_xsr;
   uint32_t t_osco;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG14_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG15_struct {
   uint32_t t_stab_x32;
   uint32_t en_hwffc_t_stab;
   uint32_t en_dfi_lp_t_stab;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG15_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG16_struct {
   uint32_t t_ccd_dlr;
   uint32_t t_rrd_dlr;
   uint32_t t_faw_dlr;
   uint32_t t_rp_ca_parity;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG16_struct_t;

#endif //UMCTL2_CID_EN
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG17_struct {
   uint32_t t_vrcg_disable;
   uint32_t t_vrcg_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG17_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG18_struct {
   uint32_t t_mpdpxact;
   uint32_t t_mpsmx;
   uint32_t t_pd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG18_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG19_struct {
   uint32_t t_pda_h;
   uint32_t t_pda_s;
   uint32_t t_pda_dqs_delay;
   uint32_t t_pda_delay;
   uint32_t t_pda_latch;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG19_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG20_struct {
   uint32_t t_csl_srexit;
   uint32_t t_csh_srexit;
   uint32_t t_casrx;
   uint32_t t_cpded;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG21_struct {
   uint32_t t_osco_ddr5;
   uint32_t t_vrefca_cs;
   uint32_t t_mpc_hold;
   uint32_t t_mpc_setup;
   uint32_t t_mpc_cs;
   uint32_t t_csl;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG22_struct {
   uint32_t t_rd2wr_dpr;
   uint32_t t_rd2wr_dlr;
   uint32_t t_wr2rd_dpr;
   uint32_t t_wr2rd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG22_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG23_struct {
   uint32_t t_pdn;
   uint32_t t_pdn_dsm_x1024;
   uint32_t t_xsr_dsm_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG23_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG24_struct {
   uint32_t max_wr_sync;
   uint32_t max_rd_sync;
   uint32_t rd2wr_s;
   uint32_t bank_org;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG24_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG25_struct {
   uint32_t rda2pre;
   uint32_t wra2pre;
   uint32_t lpddr4_diff_bank_rwa2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG25_struct_t;

#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG26_struct {
   uint32_t t_ccd_r;
   uint32_t t_ccd_w;
   uint32_t t_ccd_r_s;
   uint32_t t_ccd_w_s;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG26_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG27_struct {
   uint32_t t_mrr2mpc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG27_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG28_struct {
   uint32_t t_srx2srx;
   uint32_t t_cpded2srx;
   uint32_t t_cssr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG28_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG29_struct {
   uint32_t t_ckact;
   uint32_t t_ckoff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG29_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DRAMSET1TMG30_struct {
   uint32_t mrr2rd;
   uint32_t mrr2wr;
   uint32_t mrr2mrw;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET1TMG30_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG0_struct {
   uint32_t t_ccd_r_2;
   uint32_t t_ccd_w_2;
   uint32_t t_ccd_r_s_2;
   uint32_t t_ccd_w_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG1_struct {
   uint32_t t_ras_min_2;
   uint32_t t_faw_2;
   uint32_t t_wr2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG1_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG2_struct {
   uint32_t t_rc_2;
   uint32_t rd2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG3_struct {
   uint32_t wr2rd_2;
   uint32_t rd2wr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG3_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG4_struct {
   uint32_t t_rd2wr_dpr_2;
   uint32_t t_rd2wr_dlr_2;
   uint32_t t_wr2rd_dpr_2;
   uint32_t t_wr2rd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG4_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG5_struct {
   uint32_t t_rp_2;
   uint32_t t_rrd_2;
   uint32_t t_ccd_2;
   uint32_t t_rcd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG5_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG6_struct {
   uint32_t wr2rd_s_2;
   uint32_t t_rrd_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG6_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG7_struct {
   uint32_t t_ppd_2;
   uint32_t t_ccd_w2_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG7_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG8_struct {
   uint32_t t_ccd_dlr_2;
   uint32_t t_rrd_dlr_2;
   uint32_t t_faw_dlr_2;
   uint32_t t_rp_ca_parity_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG8_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG9_struct {
   uint32_t t_xs_x32_2;
   uint32_t t_xs_dll_x32_2;
   uint32_t t_xs_abort_x32_2;
   uint32_t t_xs_fast_x32_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG9_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG10_struct {
   uint32_t t_mr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG10_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_DRAMSET2TMG11_struct {
   uint32_t t_mrr2mpc_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DRAMSET2TMG11_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL0_struct {
   uint32_t t_rd2rd_gap_r0r1;
   uint32_t t_rd2rd_gap_r1r0;
   uint32_t t_wr2rd_gap_r0r1;
   uint32_t t_wr2rd_gap_r1r0;
   uint32_t t_rd2wr_gap_r0r1;
   uint32_t t_rd2wr_gap_r1r0;
   uint32_t t_wr2wr_gap_r0r1;
   uint32_t t_wr2wr_gap_r1r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL0_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL1_struct {
   uint32_t t_rd2rd_gap_r0r2;
   uint32_t t_rd2rd_gap_r2r0;
   uint32_t t_wr2rd_gap_r0r2;
   uint32_t t_wr2rd_gap_r2r0;
   uint32_t t_rd2wr_gap_r0r2;
   uint32_t t_rd2wr_gap_r2r0;
   uint32_t t_wr2wr_gap_r0r2;
   uint32_t t_wr2wr_gap_r2r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL1_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL2_struct {
   uint32_t t_rd2rd_gap_r0r3;
   uint32_t t_rd2rd_gap_r3r0;
   uint32_t t_wr2rd_gap_r0r3;
   uint32_t t_wr2rd_gap_r3r0;
   uint32_t t_rd2wr_gap_r0r3;
   uint32_t t_rd2wr_gap_r3r0;
   uint32_t t_wr2wr_gap_r0r3;
   uint32_t t_wr2wr_gap_r3r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL3_struct {
   uint32_t t_rd2rd_gap_r1r2;
   uint32_t t_rd2rd_gap_r2r1;
   uint32_t t_wr2rd_gap_r1r2;
   uint32_t t_wr2rd_gap_r2r1;
   uint32_t t_rd2wr_gap_r1r2;
   uint32_t t_rd2wr_gap_r2r1;
   uint32_t t_wr2wr_gap_r1r2;
   uint32_t t_wr2wr_gap_r2r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL4_struct {
   uint32_t t_rd2rd_gap_r1r3;
   uint32_t t_rd2rd_gap_r3r1;
   uint32_t t_wr2rd_gap_r1r3;
   uint32_t t_wr2rd_gap_r3r1;
   uint32_t t_rd2wr_gap_r1r3;
   uint32_t t_rd2wr_gap_r3r1;
   uint32_t t_wr2wr_gap_r1r3;
   uint32_t t_wr2wr_gap_r3r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL5_struct {
   uint32_t t_rd2rd_gap_r2r3;
   uint32_t t_rd2rd_gap_r3r2;
   uint32_t t_wr2rd_gap_r2r3;
   uint32_t t_wr2rd_gap_r3r2;
   uint32_t t_rd2wr_gap_r2r3;
   uint32_t t_rd2wr_gap_r3r2;
   uint32_t t_wr2wr_gap_r2r3;
   uint32_t t_wr2wr_gap_r3r2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANK_SWITCH_TIMING_CONTROL5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH1_MRAMTMG0_struct {
   uint32_t t_ras_min_mram;
   uint32_t t_faw_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_MRAMTMG0_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH1_MRAMTMG1_struct {
   uint32_t t_rc_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_MRAMTMG1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH1_MRAMTMG2_struct {
   uint32_t t_rp_mram;
   uint32_t t_rrd_mram;
   uint32_t t_rcd_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_MRAMTMG2_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH1_MRAMTMG3_struct {
   uint32_t t_rrd_s_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_MRAMTMG3_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ0_CH1_INITMR0_struct {
   uint32_t emr;
   uint32_t mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_INITMR0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_INITMR1_struct {
   uint32_t emr3;
   uint32_t emr2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_INITMR1_struct_t;

typedef struct tag_REGB_FREQ0_CH1_INITMR2_struct {
   uint32_t mr5;
   uint32_t mr4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_INITMR2_struct_t;

typedef struct tag_REGB_FREQ0_CH1_INITMR3_struct {
   uint32_t mr6;
   uint32_t mr22;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_INITMR3_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DFITMG0_struct {
   uint32_t dfi_tphy_wrlat;
   uint32_t dfi_tphy_wrdata;
   uint32_t dfi_t_rddata_en;
   uint32_t dfi_t_ctrl_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DFITMG1_struct {
   uint32_t dfi_t_dram_clk_enable;
   uint32_t dfi_t_dram_clk_disable;
   uint32_t dfi_t_wrdata_delay;
   uint32_t dfi_t_parin_lat;
   uint32_t dfi_t_cmd_lat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG1_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DFITMG2_struct {
   uint32_t dfi_tphy_wrcslat;
   uint32_t dfi_tphy_rdcslat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG2_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ0_CH1_DFITMG3_struct {
   uint32_t dfi_t_geardown_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG3_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DFITMG4_struct {
   uint32_t dfi_twck_dis;
   uint32_t dfi_twck_en_fs;
   uint32_t dfi_twck_en_wr;
   uint32_t dfi_twck_en_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG4_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DFITMG5_struct {
   uint32_t dfi_twck_toggle_post;
   uint32_t dfi_twck_toggle_cs;
   uint32_t dfi_twck_toggle;
   uint32_t dfi_twck_fast_toggle;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG5_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DFITMG7_struct {
   uint32_t dfi_t_2n_mode_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFITMG7_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_DFILPTMG0_struct {
   uint32_t dfi_lp_wakeup_pd;
   uint32_t dfi_lp_wakeup_sr;
   uint32_t dfi_lp_wakeup_dsm;
   uint32_t dfi_lp_wakeup_mpsm;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFILPTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DFILPTMG1_struct {
   uint32_t dfi_lp_wakeup_data;
   uint32_t dfi_tlp_resp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFILPTMG1_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DFIUPDTMG0_struct {
   uint32_t dfi_t_ctrlup_min;
   uint32_t dfi_t_ctrlup_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFIUPDTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DFIUPDTMG1_struct {
   uint32_t dfi_t_ctrlupd_interval_max_x1024;
   uint32_t dfi_t_ctrlupd_interval_min_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFIUPDTMG1_struct_t;

typedef struct tag_REGB_FREQ0_CH1_DFIMSGTMG0_struct {
   uint32_t dfi_t_ctrlmsg_resp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DFIMSGTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG0_struct {
   uint32_t t_refi_x1_x32;
   uint32_t refresh_to_x1_x32;
   uint32_t refresh_margin;
   uint32_t t_refi_x1_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG1_struct {
   uint32_t t_rfc_min;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG1_struct_t;

#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG2_struct {
   uint32_t t_rfc_min_dlr;
   uint32_t t_pbr2pbr;
   uint32_t t_pbr2act;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG2_struct_t;

#endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG3_struct {
   uint32_t t_rfcsb;
   uint32_t t_refsbrd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG4_struct {
   uint32_t refresh_timer0_start_value_x32;
   uint32_t refresh_timer1_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG4_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG5_struct {
   uint32_t refresh_timer2_start_value_x32;
   uint32_t refresh_timer3_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG6_struct {
   uint32_t refresh_timer_lr_offset_x32;
   uint32_t refresh_timer_rank_offset_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG6_struct_t;

#endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG7_struct {
   uint32_t t_rfcsb_dlr;
   uint32_t t_refsbrd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG7_struct_t;

#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HET_RANK_RFC
typedef struct tag_REGB_FREQ0_CH1_RFSHSET1TMG8_struct {
   uint32_t t_rfc_min_het;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET1TMG8_struct_t;

#endif //UMCTL2_HET_RANK_RFC
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_RFSHSET2TMG0_struct {
   uint32_t t_rfc_min_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH1_RFSHSET2TMG1_struct {
   uint32_t t_rfc_min_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET2TMG1_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_RFSHSET2TMG2_struct {
   uint32_t t_rfcsb_2;
   uint32_t t_refsbrd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ0_CH1_RFSHSET2TMG3_struct {
   uint32_t t_rfcsb_dlr_2;
   uint32_t t_refsbrd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RFSHSET2TMG3_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ0_CH1_ZQSET1TMG0_struct {
   uint32_t t_zq_long_nop;
   uint32_t t_zq_short_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_ZQSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_ZQSET1TMG1_struct {
   uint32_t t_zq_short_interval_x1024;
   uint32_t t_zq_reset_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_ZQSET1TMG1_struct_t;

#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ0_CH1_ZQSET2TMG0_struct {
   uint32_t t_zq_long_nop_2;
   uint32_t t_zq_short_nop_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_ZQSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH1_RCDINIT1_struct {
   uint32_t ctrl_word_1;
   uint32_t ctrl_word_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RCDINIT1_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH1_RCDINIT2_struct {
   uint32_t ctrl_word_3;
   uint32_t ctrl_word_4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RCDINIT2_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH1_RCDINIT3_struct {
   uint32_t ctrl_word_5;
   uint32_t ctrl_word_6;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RCDINIT3_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH1_RCDINIT4_struct {
   uint32_t ctrl_word_7;
   uint32_t ctrl_word_8;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RCDINIT4_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_FREQ0_CH1_DQSOSCCTL0_struct {
   uint32_t dqsosc_enable;
   uint32_t dqsosc_interval_unit;
   uint32_t dqsosc_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DQSOSCCTL0_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DERATEINT_struct {
   uint32_t mr4_read_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DERATEINT_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DERATEVAL0_struct {
   uint32_t derated_t_rrd;
   uint32_t derated_t_rp;
   uint32_t derated_t_ras_min;
   uint32_t derated_t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DERATEVAL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_DERATEVAL1_struct {
   uint32_t derated_t_rc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_DERATEVAL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ0_CH1_HWLPTMG0_struct {
   uint32_t hw_lp_idle_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_HWLPTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_SCHEDTMG0_struct {
   uint32_t pageclose_timer;
   uint32_t rdwr_idle_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_SCHEDTMG0_struct_t;

typedef struct tag_REGB_FREQ0_CH1_PERFHPR1_struct {
   uint32_t hpr_max_starve;
   uint32_t hpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_PERFHPR1_struct_t;

typedef struct tag_REGB_FREQ0_CH1_PERFLPR1_struct {
   uint32_t lpr_max_starve;
   uint32_t lpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_PERFLPR1_struct_t;

typedef struct tag_REGB_FREQ0_CH1_PERFWR1_struct {
   uint32_t w_max_starve;
   uint32_t w_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_PERFWR1_struct_t;

#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_FREQ0_CH1_RANKTMG0_struct {
   uint32_t diff_rank_rd_gap;
   uint32_t diff_rank_wr_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANKTMG0_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ0_CH1_RANKTMG1_struct {
   uint32_t wr2rd_dr;
   uint32_t rd2wr_dr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_RANKTMG1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ0_CH1_PWRTMG_struct {
   uint32_t powerdown_to_x32;
   uint32_t selfref_to_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_PWRTMG_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ0_CH1_ODTCFG_struct {
   uint32_t rd_odt_delay;
   uint32_t rd_odt_hold;
   uint32_t wr_odt_delay;
   uint32_t wr_odt_hold;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_ODTCFG_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct tag_REGB_FREQ0_CH1_CRCPARTMG0_struct {
   uint32_t retry_fifo_max_hold_timer_x4;
   uint32_t t_crc_alert_pw_max;
   uint32_t t_par_alert_pw_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_CRCPARTMG0_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ0_CH1_CRCPARTMG1_struct {
   uint32_t t_csalt;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ0_CH1_CRCPARTMG1_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG0_struct {
   uint32_t t_ras_min;
   uint32_t t_ras_max;
   uint32_t t_faw;
   uint32_t wr2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG1_struct {
   uint32_t t_rc;
   uint32_t rd2pre;
   uint32_t t_xp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG1_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG2_struct {
   uint32_t wr2rd;
   uint32_t rd2wr;
   uint32_t read_latency;
   uint32_t write_latency;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG2_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG3_struct {
   uint32_t wr2mr;
   uint32_t rd2mr;
   uint32_t t_mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG3_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG4_struct {
   uint32_t t_rp;
   uint32_t t_rrd;
   uint32_t t_ccd;
   uint32_t t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG4_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG5_struct {
   uint32_t t_cke;
   uint32_t t_ckesr;
   uint32_t t_cksre;
   uint32_t t_cksrx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG5_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG6_struct {
   uint32_t t_ckcsx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG6_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG7_struct {
   uint32_t t_csh;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG7_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG8_struct {
   uint32_t t_xs_x32;
   uint32_t t_xs_dll_x32;
   uint32_t t_xs_abort_x32;
   uint32_t t_xs_fast_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG8_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG9_struct {
   uint32_t wr2rd_s;
   uint32_t t_rrd_s;
   uint32_t t_ccd_s;
   uint32_t ddr4_wr_preamble;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG9_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG10_struct {
   uint32_t t_gear_hold;
   uint32_t t_gear_setup;
   uint32_t t_cmd_gear;
   uint32_t t_sync_gear;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG10_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG11_struct {
   uint32_t t_ckmpe;
   uint32_t t_mpx_s;
   uint32_t t_mpx_lh;
   uint32_t post_mpsm_gap_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG11_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG12_struct {
   uint32_t t_mrd_pda;
   uint32_t t_cmdcke;
   uint32_t t_wr_mpr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG12_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG13_struct {
   uint32_t t_ppd;
   uint32_t t_ccd_w2;
   uint32_t t_ccd_mw;
   uint32_t odtloff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG13_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG14_struct {
   uint32_t t_xsr;
   uint32_t t_osco;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG14_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG15_struct {
   uint32_t t_stab_x32;
   uint32_t en_hwffc_t_stab;
   uint32_t en_dfi_lp_t_stab;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG15_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG16_struct {
   uint32_t t_ccd_dlr;
   uint32_t t_rrd_dlr;
   uint32_t t_faw_dlr;
   uint32_t t_rp_ca_parity;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG16_struct_t;

#endif //UMCTL2_CID_EN
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG17_struct {
   uint32_t t_vrcg_disable;
   uint32_t t_vrcg_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG17_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG18_struct {
   uint32_t t_mpdpxact;
   uint32_t t_mpsmx;
   uint32_t t_pd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG18_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG19_struct {
   uint32_t t_pda_h;
   uint32_t t_pda_s;
   uint32_t t_pda_dqs_delay;
   uint32_t t_pda_delay;
   uint32_t t_pda_latch;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG19_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG20_struct {
   uint32_t t_csl_srexit;
   uint32_t t_csh_srexit;
   uint32_t t_casrx;
   uint32_t t_cpded;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG21_struct {
   uint32_t t_osco_ddr5;
   uint32_t t_vrefca_cs;
   uint32_t t_mpc_hold;
   uint32_t t_mpc_setup;
   uint32_t t_mpc_cs;
   uint32_t t_csl;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG22_struct {
   uint32_t t_rd2wr_dpr;
   uint32_t t_rd2wr_dlr;
   uint32_t t_wr2rd_dpr;
   uint32_t t_wr2rd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG22_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG23_struct {
   uint32_t t_pdn;
   uint32_t t_pdn_dsm_x1024;
   uint32_t t_xsr_dsm_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG23_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG24_struct {
   uint32_t max_wr_sync;
   uint32_t max_rd_sync;
   uint32_t rd2wr_s;
   uint32_t bank_org;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG24_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG25_struct {
   uint32_t rda2pre;
   uint32_t wra2pre;
   uint32_t lpddr4_diff_bank_rwa2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG25_struct_t;

#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG26_struct {
   uint32_t t_ccd_r;
   uint32_t t_ccd_w;
   uint32_t t_ccd_r_s;
   uint32_t t_ccd_w_s;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG26_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG27_struct {
   uint32_t t_mrr2mpc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG27_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG28_struct {
   uint32_t t_srx2srx;
   uint32_t t_cpded2srx;
   uint32_t t_cssr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG28_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG29_struct {
   uint32_t t_ckact;
   uint32_t t_ckoff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG29_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DRAMSET1TMG30_struct {
   uint32_t mrr2rd;
   uint32_t mrr2wr;
   uint32_t mrr2mrw;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET1TMG30_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG0_struct {
   uint32_t t_ccd_r_2;
   uint32_t t_ccd_w_2;
   uint32_t t_ccd_r_s_2;
   uint32_t t_ccd_w_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG1_struct {
   uint32_t t_ras_min_2;
   uint32_t t_faw_2;
   uint32_t t_wr2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG1_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG2_struct {
   uint32_t t_rc_2;
   uint32_t rd2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG3_struct {
   uint32_t wr2rd_2;
   uint32_t rd2wr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG3_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG4_struct {
   uint32_t t_rd2wr_dpr_2;
   uint32_t t_rd2wr_dlr_2;
   uint32_t t_wr2rd_dpr_2;
   uint32_t t_wr2rd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG4_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG5_struct {
   uint32_t t_rp_2;
   uint32_t t_rrd_2;
   uint32_t t_ccd_2;
   uint32_t t_rcd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG5_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG6_struct {
   uint32_t wr2rd_s_2;
   uint32_t t_rrd_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG6_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG7_struct {
   uint32_t t_ppd_2;
   uint32_t t_ccd_w2_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG7_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG8_struct {
   uint32_t t_ccd_dlr_2;
   uint32_t t_rrd_dlr_2;
   uint32_t t_faw_dlr_2;
   uint32_t t_rp_ca_parity_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG8_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG9_struct {
   uint32_t t_xs_x32_2;
   uint32_t t_xs_dll_x32_2;
   uint32_t t_xs_abort_x32_2;
   uint32_t t_xs_fast_x32_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG9_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG10_struct {
   uint32_t t_mr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG10_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_DRAMSET2TMG11_struct {
   uint32_t t_mrr2mpc_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DRAMSET2TMG11_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL0_struct {
   uint32_t t_rd2rd_gap_r0r1;
   uint32_t t_rd2rd_gap_r1r0;
   uint32_t t_wr2rd_gap_r0r1;
   uint32_t t_wr2rd_gap_r1r0;
   uint32_t t_rd2wr_gap_r0r1;
   uint32_t t_rd2wr_gap_r1r0;
   uint32_t t_wr2wr_gap_r0r1;
   uint32_t t_wr2wr_gap_r1r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL0_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL1_struct {
   uint32_t t_rd2rd_gap_r0r2;
   uint32_t t_rd2rd_gap_r2r0;
   uint32_t t_wr2rd_gap_r0r2;
   uint32_t t_wr2rd_gap_r2r0;
   uint32_t t_rd2wr_gap_r0r2;
   uint32_t t_rd2wr_gap_r2r0;
   uint32_t t_wr2wr_gap_r0r2;
   uint32_t t_wr2wr_gap_r2r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL1_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL2_struct {
   uint32_t t_rd2rd_gap_r0r3;
   uint32_t t_rd2rd_gap_r3r0;
   uint32_t t_wr2rd_gap_r0r3;
   uint32_t t_wr2rd_gap_r3r0;
   uint32_t t_rd2wr_gap_r0r3;
   uint32_t t_rd2wr_gap_r3r0;
   uint32_t t_wr2wr_gap_r0r3;
   uint32_t t_wr2wr_gap_r3r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL3_struct {
   uint32_t t_rd2rd_gap_r1r2;
   uint32_t t_rd2rd_gap_r2r1;
   uint32_t t_wr2rd_gap_r1r2;
   uint32_t t_wr2rd_gap_r2r1;
   uint32_t t_rd2wr_gap_r1r2;
   uint32_t t_rd2wr_gap_r2r1;
   uint32_t t_wr2wr_gap_r1r2;
   uint32_t t_wr2wr_gap_r2r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL4_struct {
   uint32_t t_rd2rd_gap_r1r3;
   uint32_t t_rd2rd_gap_r3r1;
   uint32_t t_wr2rd_gap_r1r3;
   uint32_t t_wr2rd_gap_r3r1;
   uint32_t t_rd2wr_gap_r1r3;
   uint32_t t_rd2wr_gap_r3r1;
   uint32_t t_wr2wr_gap_r1r3;
   uint32_t t_wr2wr_gap_r3r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL5_struct {
   uint32_t t_rd2rd_gap_r2r3;
   uint32_t t_rd2rd_gap_r3r2;
   uint32_t t_wr2rd_gap_r2r3;
   uint32_t t_wr2rd_gap_r3r2;
   uint32_t t_rd2wr_gap_r2r3;
   uint32_t t_rd2wr_gap_r3r2;
   uint32_t t_wr2wr_gap_r2r3;
   uint32_t t_wr2wr_gap_r3r2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANK_SWITCH_TIMING_CONTROL5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH0_MRAMTMG0_struct {
   uint32_t t_ras_min_mram;
   uint32_t t_faw_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_MRAMTMG0_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH0_MRAMTMG1_struct {
   uint32_t t_rc_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_MRAMTMG1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH0_MRAMTMG2_struct {
   uint32_t t_rp_mram;
   uint32_t t_rrd_mram;
   uint32_t t_rcd_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_MRAMTMG2_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH0_MRAMTMG3_struct {
   uint32_t t_rrd_s_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_MRAMTMG3_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH0_INITMR0_struct {
   uint32_t emr;
   uint32_t mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_INITMR0_struct_t;

typedef struct tag_REGB_FREQ1_CH0_INITMR1_struct {
   uint32_t emr3;
   uint32_t emr2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_INITMR1_struct_t;

typedef struct tag_REGB_FREQ1_CH0_INITMR2_struct {
   uint32_t mr5;
   uint32_t mr4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_INITMR2_struct_t;

typedef struct tag_REGB_FREQ1_CH0_INITMR3_struct {
   uint32_t mr6;
   uint32_t mr22;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_INITMR3_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DFITMG0_struct {
   uint32_t dfi_tphy_wrlat;
   uint32_t dfi_tphy_wrdata;
   uint32_t dfi_t_rddata_en;
   uint32_t dfi_t_ctrl_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DFITMG1_struct {
   uint32_t dfi_t_dram_clk_enable;
   uint32_t dfi_t_dram_clk_disable;
   uint32_t dfi_t_wrdata_delay;
   uint32_t dfi_t_parin_lat;
   uint32_t dfi_t_cmd_lat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG1_struct_t;

typedef struct tag_REGB_FREQ1_CH0_DFITMG2_struct {
   uint32_t dfi_tphy_wrcslat;
   uint32_t dfi_tphy_rdcslat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG2_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ1_CH0_DFITMG3_struct {
   uint32_t dfi_t_geardown_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG3_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DFITMG4_struct {
   uint32_t dfi_twck_dis;
   uint32_t dfi_twck_en_fs;
   uint32_t dfi_twck_en_wr;
   uint32_t dfi_twck_en_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG4_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DFITMG5_struct {
   uint32_t dfi_twck_toggle_post;
   uint32_t dfi_twck_toggle_cs;
   uint32_t dfi_twck_toggle;
   uint32_t dfi_twck_fast_toggle;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG5_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DFITMG7_struct {
   uint32_t dfi_t_2n_mode_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFITMG7_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_DFIUPDTMG1_struct {
   uint32_t dfi_t_ctrlupd_interval_max_x1024;
   uint32_t dfi_t_ctrlupd_interval_min_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DFIUPDTMG1_struct_t;

typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG0_struct {
   uint32_t t_refi_x1_x32;
   uint32_t refresh_to_x1_x32;
   uint32_t refresh_margin;
   uint32_t t_refi_x1_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG1_struct {
   uint32_t t_rfc_min;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG1_struct_t;

#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG2_struct {
   uint32_t t_rfc_min_dlr;
   uint32_t t_pbr2pbr;
   uint32_t t_pbr2act;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG2_struct_t;

#endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG3_struct {
   uint32_t t_rfcsb;
   uint32_t t_refsbrd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG4_struct {
   uint32_t refresh_timer0_start_value_x32;
   uint32_t refresh_timer1_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG4_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG5_struct {
   uint32_t refresh_timer2_start_value_x32;
   uint32_t refresh_timer3_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG6_struct {
   uint32_t refresh_timer_lr_offset_x32;
   uint32_t refresh_timer_rank_offset_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG6_struct_t;

#endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG7_struct {
   uint32_t t_rfcsb_dlr;
   uint32_t t_refsbrd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG7_struct_t;

#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HET_RANK_RFC
typedef struct tag_REGB_FREQ1_CH0_RFSHSET1TMG8_struct {
   uint32_t t_rfc_min_het;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET1TMG8_struct_t;

#endif //UMCTL2_HET_RANK_RFC
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_RFSHSET2TMG0_struct {
   uint32_t t_rfc_min_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH0_RFSHSET2TMG1_struct {
   uint32_t t_rfc_min_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET2TMG1_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_RFSHSET2TMG2_struct {
   uint32_t t_rfcsb_2;
   uint32_t t_refsbrd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH0_RFSHSET2TMG3_struct {
   uint32_t t_rfcsb_dlr_2;
   uint32_t t_refsbrd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RFSHSET2TMG3_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH0_ZQSET1TMG0_struct {
   uint32_t t_zq_long_nop;
   uint32_t t_zq_short_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_ZQSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH0_ZQSET1TMG1_struct {
   uint32_t t_zq_short_interval_x1024;
   uint32_t t_zq_reset_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_ZQSET1TMG1_struct_t;

#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH0_ZQSET2TMG0_struct {
   uint32_t t_zq_long_nop_2;
   uint32_t t_zq_short_nop_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_ZQSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH0_RCDINIT1_struct {
   uint32_t ctrl_word_1;
   uint32_t ctrl_word_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RCDINIT1_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH0_RCDINIT2_struct {
   uint32_t ctrl_word_3;
   uint32_t ctrl_word_4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RCDINIT2_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH0_RCDINIT3_struct {
   uint32_t ctrl_word_5;
   uint32_t ctrl_word_6;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RCDINIT3_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH0_RCDINIT4_struct {
   uint32_t ctrl_word_7;
   uint32_t ctrl_word_8;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RCDINIT4_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_FREQ1_CH0_DQSOSCCTL0_struct {
   uint32_t dqsosc_enable;
   uint32_t dqsosc_interval_unit;
   uint32_t dqsosc_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DQSOSCCTL0_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DERATEINT_struct {
   uint32_t mr4_read_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DERATEINT_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DERATEVAL0_struct {
   uint32_t derated_t_rrd;
   uint32_t derated_t_rp;
   uint32_t derated_t_ras_min;
   uint32_t derated_t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DERATEVAL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_DERATEVAL1_struct {
   uint32_t derated_t_rc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_DERATEVAL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH0_HWLPTMG0_struct {
   uint32_t hw_lp_idle_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_HWLPTMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH0_SCHEDTMG0_struct {
   uint32_t pageclose_timer;
   uint32_t rdwr_idle_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_SCHEDTMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH0_PERFHPR1_struct {
   uint32_t hpr_max_starve;
   uint32_t hpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_PERFHPR1_struct_t;

typedef struct tag_REGB_FREQ1_CH0_PERFLPR1_struct {
   uint32_t lpr_max_starve;
   uint32_t lpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_PERFLPR1_struct_t;

typedef struct tag_REGB_FREQ1_CH0_PERFWR1_struct {
   uint32_t w_max_starve;
   uint32_t w_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_PERFWR1_struct_t;

typedef struct tag_REGB_FREQ1_CH0_TMGCFG_struct {
   uint32_t frequency_ratio;
   uint32_t dfi_freq_fsp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_TMGCFG_struct_t;

#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_FREQ1_CH0_RANKTMG0_struct {
   uint32_t diff_rank_rd_gap;
   uint32_t diff_rank_wr_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANKTMG0_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ1_CH0_RANKTMG1_struct {
   uint32_t wr2rd_dr;
   uint32_t rd2wr_dr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_RANKTMG1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ1_CH0_PWRTMG_struct {
   uint32_t powerdown_to_x32;
   uint32_t selfref_to_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_PWRTMG_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH0_ODTCFG_struct {
   uint32_t rd_odt_delay;
   uint32_t rd_odt_hold;
   uint32_t wr_odt_delay;
   uint32_t wr_odt_hold;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_ODTCFG_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct tag_REGB_FREQ1_CH0_CRCPARTMG0_struct {
   uint32_t retry_fifo_max_hold_timer_x4;
   uint32_t t_crc_alert_pw_max;
   uint32_t t_par_alert_pw_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_CRCPARTMG0_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ1_CH0_CRCPARTMG1_struct {
   uint32_t t_csalt;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH0_CRCPARTMG1_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG0_struct {
   uint32_t t_ras_min;
   uint32_t t_ras_max;
   uint32_t t_faw;
   uint32_t wr2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG1_struct {
   uint32_t t_rc;
   uint32_t rd2pre;
   uint32_t t_xp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG1_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG2_struct {
   uint32_t wr2rd;
   uint32_t rd2wr;
   uint32_t read_latency;
   uint32_t write_latency;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG2_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG3_struct {
   uint32_t wr2mr;
   uint32_t rd2mr;
   uint32_t t_mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG3_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG4_struct {
   uint32_t t_rp;
   uint32_t t_rrd;
   uint32_t t_ccd;
   uint32_t t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG4_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG5_struct {
   uint32_t t_cke;
   uint32_t t_ckesr;
   uint32_t t_cksre;
   uint32_t t_cksrx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG5_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG6_struct {
   uint32_t t_ckcsx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG6_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG7_struct {
   uint32_t t_csh;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG7_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG8_struct {
   uint32_t t_xs_x32;
   uint32_t t_xs_dll_x32;
   uint32_t t_xs_abort_x32;
   uint32_t t_xs_fast_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG8_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG9_struct {
   uint32_t wr2rd_s;
   uint32_t t_rrd_s;
   uint32_t t_ccd_s;
   uint32_t ddr4_wr_preamble;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG9_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG10_struct {
   uint32_t t_gear_hold;
   uint32_t t_gear_setup;
   uint32_t t_cmd_gear;
   uint32_t t_sync_gear;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG10_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG11_struct {
   uint32_t t_ckmpe;
   uint32_t t_mpx_s;
   uint32_t t_mpx_lh;
   uint32_t post_mpsm_gap_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG11_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG12_struct {
   uint32_t t_mrd_pda;
   uint32_t t_cmdcke;
   uint32_t t_wr_mpr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG12_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG13_struct {
   uint32_t t_ppd;
   uint32_t t_ccd_w2;
   uint32_t t_ccd_mw;
   uint32_t odtloff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG13_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG14_struct {
   uint32_t t_xsr;
   uint32_t t_osco;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG14_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG15_struct {
   uint32_t t_stab_x32;
   uint32_t en_hwffc_t_stab;
   uint32_t en_dfi_lp_t_stab;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG15_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG16_struct {
   uint32_t t_ccd_dlr;
   uint32_t t_rrd_dlr;
   uint32_t t_faw_dlr;
   uint32_t t_rp_ca_parity;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG16_struct_t;

#endif //UMCTL2_CID_EN
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG17_struct {
   uint32_t t_vrcg_disable;
   uint32_t t_vrcg_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG17_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG18_struct {
   uint32_t t_mpdpxact;
   uint32_t t_mpsmx;
   uint32_t t_pd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG18_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG19_struct {
   uint32_t t_pda_h;
   uint32_t t_pda_s;
   uint32_t t_pda_dqs_delay;
   uint32_t t_pda_delay;
   uint32_t t_pda_latch;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG19_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG20_struct {
   uint32_t t_csl_srexit;
   uint32_t t_csh_srexit;
   uint32_t t_casrx;
   uint32_t t_cpded;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG21_struct {
   uint32_t t_osco_ddr5;
   uint32_t t_vrefca_cs;
   uint32_t t_mpc_hold;
   uint32_t t_mpc_setup;
   uint32_t t_mpc_cs;
   uint32_t t_csl;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG22_struct {
   uint32_t t_rd2wr_dpr;
   uint32_t t_rd2wr_dlr;
   uint32_t t_wr2rd_dpr;
   uint32_t t_wr2rd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG22_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG23_struct {
   uint32_t t_pdn;
   uint32_t t_pdn_dsm_x1024;
   uint32_t t_xsr_dsm_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG23_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG24_struct {
   uint32_t max_wr_sync;
   uint32_t max_rd_sync;
   uint32_t rd2wr_s;
   uint32_t bank_org;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG24_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG25_struct {
   uint32_t rda2pre;
   uint32_t wra2pre;
   uint32_t lpddr4_diff_bank_rwa2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG25_struct_t;

#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG26_struct {
   uint32_t t_ccd_r;
   uint32_t t_ccd_w;
   uint32_t t_ccd_r_s;
   uint32_t t_ccd_w_s;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG26_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG27_struct {
   uint32_t t_mrr2mpc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG27_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG28_struct {
   uint32_t t_srx2srx;
   uint32_t t_cpded2srx;
   uint32_t t_cssr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG28_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG29_struct {
   uint32_t t_ckact;
   uint32_t t_ckoff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG29_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DRAMSET1TMG30_struct {
   uint32_t mrr2rd;
   uint32_t mrr2wr;
   uint32_t mrr2mrw;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET1TMG30_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG0_struct {
   uint32_t t_ccd_r_2;
   uint32_t t_ccd_w_2;
   uint32_t t_ccd_r_s_2;
   uint32_t t_ccd_w_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG1_struct {
   uint32_t t_ras_min_2;
   uint32_t t_faw_2;
   uint32_t t_wr2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG1_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG2_struct {
   uint32_t t_rc_2;
   uint32_t rd2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG3_struct {
   uint32_t wr2rd_2;
   uint32_t rd2wr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG3_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG4_struct {
   uint32_t t_rd2wr_dpr_2;
   uint32_t t_rd2wr_dlr_2;
   uint32_t t_wr2rd_dpr_2;
   uint32_t t_wr2rd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG4_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG5_struct {
   uint32_t t_rp_2;
   uint32_t t_rrd_2;
   uint32_t t_ccd_2;
   uint32_t t_rcd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG5_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG6_struct {
   uint32_t wr2rd_s_2;
   uint32_t t_rrd_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG6_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG7_struct {
   uint32_t t_ppd_2;
   uint32_t t_ccd_w2_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG7_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG8_struct {
   uint32_t t_ccd_dlr_2;
   uint32_t t_rrd_dlr_2;
   uint32_t t_faw_dlr_2;
   uint32_t t_rp_ca_parity_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG8_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG9_struct {
   uint32_t t_xs_x32_2;
   uint32_t t_xs_dll_x32_2;
   uint32_t t_xs_abort_x32_2;
   uint32_t t_xs_fast_x32_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG9_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG10_struct {
   uint32_t t_mr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG10_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_DRAMSET2TMG11_struct {
   uint32_t t_mrr2mpc_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DRAMSET2TMG11_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL0_struct {
   uint32_t t_rd2rd_gap_r0r1;
   uint32_t t_rd2rd_gap_r1r0;
   uint32_t t_wr2rd_gap_r0r1;
   uint32_t t_wr2rd_gap_r1r0;
   uint32_t t_rd2wr_gap_r0r1;
   uint32_t t_rd2wr_gap_r1r0;
   uint32_t t_wr2wr_gap_r0r1;
   uint32_t t_wr2wr_gap_r1r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL0_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL1_struct {
   uint32_t t_rd2rd_gap_r0r2;
   uint32_t t_rd2rd_gap_r2r0;
   uint32_t t_wr2rd_gap_r0r2;
   uint32_t t_wr2rd_gap_r2r0;
   uint32_t t_rd2wr_gap_r0r2;
   uint32_t t_rd2wr_gap_r2r0;
   uint32_t t_wr2wr_gap_r0r2;
   uint32_t t_wr2wr_gap_r2r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL1_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL2_struct {
   uint32_t t_rd2rd_gap_r0r3;
   uint32_t t_rd2rd_gap_r3r0;
   uint32_t t_wr2rd_gap_r0r3;
   uint32_t t_wr2rd_gap_r3r0;
   uint32_t t_rd2wr_gap_r0r3;
   uint32_t t_rd2wr_gap_r3r0;
   uint32_t t_wr2wr_gap_r0r3;
   uint32_t t_wr2wr_gap_r3r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL3_struct {
   uint32_t t_rd2rd_gap_r1r2;
   uint32_t t_rd2rd_gap_r2r1;
   uint32_t t_wr2rd_gap_r1r2;
   uint32_t t_wr2rd_gap_r2r1;
   uint32_t t_rd2wr_gap_r1r2;
   uint32_t t_rd2wr_gap_r2r1;
   uint32_t t_wr2wr_gap_r1r2;
   uint32_t t_wr2wr_gap_r2r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL4_struct {
   uint32_t t_rd2rd_gap_r1r3;
   uint32_t t_rd2rd_gap_r3r1;
   uint32_t t_wr2rd_gap_r1r3;
   uint32_t t_wr2rd_gap_r3r1;
   uint32_t t_rd2wr_gap_r1r3;
   uint32_t t_rd2wr_gap_r3r1;
   uint32_t t_wr2wr_gap_r1r3;
   uint32_t t_wr2wr_gap_r3r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL5_struct {
   uint32_t t_rd2rd_gap_r2r3;
   uint32_t t_rd2rd_gap_r3r2;
   uint32_t t_wr2rd_gap_r2r3;
   uint32_t t_wr2rd_gap_r3r2;
   uint32_t t_rd2wr_gap_r2r3;
   uint32_t t_rd2wr_gap_r3r2;
   uint32_t t_wr2wr_gap_r2r3;
   uint32_t t_wr2wr_gap_r3r2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANK_SWITCH_TIMING_CONTROL5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH1_MRAMTMG0_struct {
   uint32_t t_ras_min_mram;
   uint32_t t_faw_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_MRAMTMG0_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH1_MRAMTMG1_struct {
   uint32_t t_rc_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_MRAMTMG1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH1_MRAMTMG2_struct {
   uint32_t t_rp_mram;
   uint32_t t_rrd_mram;
   uint32_t t_rcd_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_MRAMTMG2_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH1_MRAMTMG3_struct {
   uint32_t t_rrd_s_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_MRAMTMG3_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ1_CH1_INITMR0_struct {
   uint32_t emr;
   uint32_t mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_INITMR0_struct_t;

typedef struct tag_REGB_FREQ1_CH1_INITMR1_struct {
   uint32_t emr3;
   uint32_t emr2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_INITMR1_struct_t;

typedef struct tag_REGB_FREQ1_CH1_INITMR2_struct {
   uint32_t mr5;
   uint32_t mr4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_INITMR2_struct_t;

typedef struct tag_REGB_FREQ1_CH1_INITMR3_struct {
   uint32_t mr6;
   uint32_t mr22;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_INITMR3_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DFITMG0_struct {
   uint32_t dfi_tphy_wrlat;
   uint32_t dfi_tphy_wrdata;
   uint32_t dfi_t_rddata_en;
   uint32_t dfi_t_ctrl_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DFITMG1_struct {
   uint32_t dfi_t_dram_clk_enable;
   uint32_t dfi_t_dram_clk_disable;
   uint32_t dfi_t_wrdata_delay;
   uint32_t dfi_t_parin_lat;
   uint32_t dfi_t_cmd_lat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG1_struct_t;

typedef struct tag_REGB_FREQ1_CH1_DFITMG2_struct {
   uint32_t dfi_tphy_wrcslat;
   uint32_t dfi_tphy_rdcslat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG2_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ1_CH1_DFITMG3_struct {
   uint32_t dfi_t_geardown_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG3_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DFITMG4_struct {
   uint32_t dfi_twck_dis;
   uint32_t dfi_twck_en_fs;
   uint32_t dfi_twck_en_wr;
   uint32_t dfi_twck_en_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG4_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DFITMG5_struct {
   uint32_t dfi_twck_toggle_post;
   uint32_t dfi_twck_toggle_cs;
   uint32_t dfi_twck_toggle;
   uint32_t dfi_twck_fast_toggle;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG5_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DFITMG7_struct {
   uint32_t dfi_t_2n_mode_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFITMG7_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_DFIUPDTMG1_struct {
   uint32_t dfi_t_ctrlupd_interval_max_x1024;
   uint32_t dfi_t_ctrlupd_interval_min_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DFIUPDTMG1_struct_t;

typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG0_struct {
   uint32_t t_refi_x1_x32;
   uint32_t refresh_to_x1_x32;
   uint32_t refresh_margin;
   uint32_t t_refi_x1_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG1_struct {
   uint32_t t_rfc_min;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG1_struct_t;

#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG2_struct {
   uint32_t t_rfc_min_dlr;
   uint32_t t_pbr2pbr;
   uint32_t t_pbr2act;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG2_struct_t;

#endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG3_struct {
   uint32_t t_rfcsb;
   uint32_t t_refsbrd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG4_struct {
   uint32_t refresh_timer0_start_value_x32;
   uint32_t refresh_timer1_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG4_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG5_struct {
   uint32_t refresh_timer2_start_value_x32;
   uint32_t refresh_timer3_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG6_struct {
   uint32_t refresh_timer_lr_offset_x32;
   uint32_t refresh_timer_rank_offset_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG6_struct_t;

#endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG7_struct {
   uint32_t t_rfcsb_dlr;
   uint32_t t_refsbrd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG7_struct_t;

#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HET_RANK_RFC
typedef struct tag_REGB_FREQ1_CH1_RFSHSET1TMG8_struct {
   uint32_t t_rfc_min_het;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET1TMG8_struct_t;

#endif //UMCTL2_HET_RANK_RFC
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_RFSHSET2TMG0_struct {
   uint32_t t_rfc_min_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH1_RFSHSET2TMG1_struct {
   uint32_t t_rfc_min_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET2TMG1_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_RFSHSET2TMG2_struct {
   uint32_t t_rfcsb_2;
   uint32_t t_refsbrd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ1_CH1_RFSHSET2TMG3_struct {
   uint32_t t_rfcsb_dlr_2;
   uint32_t t_refsbrd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RFSHSET2TMG3_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ1_CH1_ZQSET1TMG0_struct {
   uint32_t t_zq_long_nop;
   uint32_t t_zq_short_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_ZQSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH1_ZQSET1TMG1_struct {
   uint32_t t_zq_short_interval_x1024;
   uint32_t t_zq_reset_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_ZQSET1TMG1_struct_t;

#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ1_CH1_ZQSET2TMG0_struct {
   uint32_t t_zq_long_nop_2;
   uint32_t t_zq_short_nop_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_ZQSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH1_RCDINIT1_struct {
   uint32_t ctrl_word_1;
   uint32_t ctrl_word_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RCDINIT1_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH1_RCDINIT2_struct {
   uint32_t ctrl_word_3;
   uint32_t ctrl_word_4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RCDINIT2_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH1_RCDINIT3_struct {
   uint32_t ctrl_word_5;
   uint32_t ctrl_word_6;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RCDINIT3_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH1_RCDINIT4_struct {
   uint32_t ctrl_word_7;
   uint32_t ctrl_word_8;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RCDINIT4_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_FREQ1_CH1_DQSOSCCTL0_struct {
   uint32_t dqsosc_enable;
   uint32_t dqsosc_interval_unit;
   uint32_t dqsosc_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DQSOSCCTL0_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DERATEINT_struct {
   uint32_t mr4_read_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DERATEINT_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DERATEVAL0_struct {
   uint32_t derated_t_rrd;
   uint32_t derated_t_rp;
   uint32_t derated_t_ras_min;
   uint32_t derated_t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DERATEVAL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_DERATEVAL1_struct {
   uint32_t derated_t_rc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_DERATEVAL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ1_CH1_HWLPTMG0_struct {
   uint32_t hw_lp_idle_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_HWLPTMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH1_SCHEDTMG0_struct {
   uint32_t pageclose_timer;
   uint32_t rdwr_idle_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_SCHEDTMG0_struct_t;

typedef struct tag_REGB_FREQ1_CH1_PERFHPR1_struct {
   uint32_t hpr_max_starve;
   uint32_t hpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_PERFHPR1_struct_t;

typedef struct tag_REGB_FREQ1_CH1_PERFLPR1_struct {
   uint32_t lpr_max_starve;
   uint32_t lpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_PERFLPR1_struct_t;

typedef struct tag_REGB_FREQ1_CH1_PERFWR1_struct {
   uint32_t w_max_starve;
   uint32_t w_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_PERFWR1_struct_t;

#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_FREQ1_CH1_RANKTMG0_struct {
   uint32_t diff_rank_rd_gap;
   uint32_t diff_rank_wr_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANKTMG0_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ1_CH1_RANKTMG1_struct {
   uint32_t wr2rd_dr;
   uint32_t rd2wr_dr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_RANKTMG1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ1_CH1_PWRTMG_struct {
   uint32_t powerdown_to_x32;
   uint32_t selfref_to_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_PWRTMG_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ1_CH1_ODTCFG_struct {
   uint32_t rd_odt_delay;
   uint32_t rd_odt_hold;
   uint32_t wr_odt_delay;
   uint32_t wr_odt_hold;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_ODTCFG_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct tag_REGB_FREQ1_CH1_CRCPARTMG0_struct {
   uint32_t retry_fifo_max_hold_timer_x4;
   uint32_t t_crc_alert_pw_max;
   uint32_t t_par_alert_pw_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_CRCPARTMG0_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ1_CH1_CRCPARTMG1_struct {
   uint32_t t_csalt;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ1_CH1_CRCPARTMG1_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG0_struct {
   uint32_t t_ras_min;
   uint32_t t_ras_max;
   uint32_t t_faw;
   uint32_t wr2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG1_struct {
   uint32_t t_rc;
   uint32_t rd2pre;
   uint32_t t_xp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG1_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG2_struct {
   uint32_t wr2rd;
   uint32_t rd2wr;
   uint32_t read_latency;
   uint32_t write_latency;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG2_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG3_struct {
   uint32_t wr2mr;
   uint32_t rd2mr;
   uint32_t t_mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG3_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG4_struct {
   uint32_t t_rp;
   uint32_t t_rrd;
   uint32_t t_ccd;
   uint32_t t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG4_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG5_struct {
   uint32_t t_cke;
   uint32_t t_ckesr;
   uint32_t t_cksre;
   uint32_t t_cksrx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG5_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG6_struct {
   uint32_t t_ckcsx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG6_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG7_struct {
   uint32_t t_csh;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG7_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG8_struct {
   uint32_t t_xs_x32;
   uint32_t t_xs_dll_x32;
   uint32_t t_xs_abort_x32;
   uint32_t t_xs_fast_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG8_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG9_struct {
   uint32_t wr2rd_s;
   uint32_t t_rrd_s;
   uint32_t t_ccd_s;
   uint32_t ddr4_wr_preamble;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG9_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG10_struct {
   uint32_t t_gear_hold;
   uint32_t t_gear_setup;
   uint32_t t_cmd_gear;
   uint32_t t_sync_gear;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG10_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG11_struct {
   uint32_t t_ckmpe;
   uint32_t t_mpx_s;
   uint32_t t_mpx_lh;
   uint32_t post_mpsm_gap_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG11_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG12_struct {
   uint32_t t_mrd_pda;
   uint32_t t_cmdcke;
   uint32_t t_wr_mpr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG12_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG13_struct {
   uint32_t t_ppd;
   uint32_t t_ccd_w2;
   uint32_t t_ccd_mw;
   uint32_t odtloff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG13_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG14_struct {
   uint32_t t_xsr;
   uint32_t t_osco;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG14_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG15_struct {
   uint32_t t_stab_x32;
   uint32_t en_hwffc_t_stab;
   uint32_t en_dfi_lp_t_stab;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG15_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG16_struct {
   uint32_t t_ccd_dlr;
   uint32_t t_rrd_dlr;
   uint32_t t_faw_dlr;
   uint32_t t_rp_ca_parity;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG16_struct_t;

#endif //UMCTL2_CID_EN
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG17_struct {
   uint32_t t_vrcg_disable;
   uint32_t t_vrcg_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG17_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG18_struct {
   uint32_t t_mpdpxact;
   uint32_t t_mpsmx;
   uint32_t t_pd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG18_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG19_struct {
   uint32_t t_pda_h;
   uint32_t t_pda_s;
   uint32_t t_pda_dqs_delay;
   uint32_t t_pda_delay;
   uint32_t t_pda_latch;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG19_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG20_struct {
   uint32_t t_csl_srexit;
   uint32_t t_csh_srexit;
   uint32_t t_casrx;
   uint32_t t_cpded;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG21_struct {
   uint32_t t_osco_ddr5;
   uint32_t t_vrefca_cs;
   uint32_t t_mpc_hold;
   uint32_t t_mpc_setup;
   uint32_t t_mpc_cs;
   uint32_t t_csl;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG22_struct {
   uint32_t t_rd2wr_dpr;
   uint32_t t_rd2wr_dlr;
   uint32_t t_wr2rd_dpr;
   uint32_t t_wr2rd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG22_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG23_struct {
   uint32_t t_pdn;
   uint32_t t_pdn_dsm_x1024;
   uint32_t t_xsr_dsm_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG23_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG24_struct {
   uint32_t max_wr_sync;
   uint32_t max_rd_sync;
   uint32_t rd2wr_s;
   uint32_t bank_org;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG24_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG25_struct {
   uint32_t rda2pre;
   uint32_t wra2pre;
   uint32_t lpddr4_diff_bank_rwa2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG25_struct_t;

#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG26_struct {
   uint32_t t_ccd_r;
   uint32_t t_ccd_w;
   uint32_t t_ccd_r_s;
   uint32_t t_ccd_w_s;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG26_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG27_struct {
   uint32_t t_mrr2mpc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG27_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG28_struct {
   uint32_t t_srx2srx;
   uint32_t t_cpded2srx;
   uint32_t t_cssr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG28_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG29_struct {
   uint32_t t_ckact;
   uint32_t t_ckoff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG29_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DRAMSET1TMG30_struct {
   uint32_t mrr2rd;
   uint32_t mrr2wr;
   uint32_t mrr2mrw;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET1TMG30_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG0_struct {
   uint32_t t_ccd_r_2;
   uint32_t t_ccd_w_2;
   uint32_t t_ccd_r_s_2;
   uint32_t t_ccd_w_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG1_struct {
   uint32_t t_ras_min_2;
   uint32_t t_faw_2;
   uint32_t t_wr2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG1_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG2_struct {
   uint32_t t_rc_2;
   uint32_t rd2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG3_struct {
   uint32_t wr2rd_2;
   uint32_t rd2wr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG3_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG4_struct {
   uint32_t t_rd2wr_dpr_2;
   uint32_t t_rd2wr_dlr_2;
   uint32_t t_wr2rd_dpr_2;
   uint32_t t_wr2rd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG4_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG5_struct {
   uint32_t t_rp_2;
   uint32_t t_rrd_2;
   uint32_t t_ccd_2;
   uint32_t t_rcd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG5_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG6_struct {
   uint32_t wr2rd_s_2;
   uint32_t t_rrd_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG6_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG7_struct {
   uint32_t t_ppd_2;
   uint32_t t_ccd_w2_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG7_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG8_struct {
   uint32_t t_ccd_dlr_2;
   uint32_t t_rrd_dlr_2;
   uint32_t t_faw_dlr_2;
   uint32_t t_rp_ca_parity_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG8_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG9_struct {
   uint32_t t_xs_x32_2;
   uint32_t t_xs_dll_x32_2;
   uint32_t t_xs_abort_x32_2;
   uint32_t t_xs_fast_x32_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG9_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG10_struct {
   uint32_t t_mr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG10_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_DRAMSET2TMG11_struct {
   uint32_t t_mrr2mpc_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DRAMSET2TMG11_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL0_struct {
   uint32_t t_rd2rd_gap_r0r1;
   uint32_t t_rd2rd_gap_r1r0;
   uint32_t t_wr2rd_gap_r0r1;
   uint32_t t_wr2rd_gap_r1r0;
   uint32_t t_rd2wr_gap_r0r1;
   uint32_t t_rd2wr_gap_r1r0;
   uint32_t t_wr2wr_gap_r0r1;
   uint32_t t_wr2wr_gap_r1r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL0_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL1_struct {
   uint32_t t_rd2rd_gap_r0r2;
   uint32_t t_rd2rd_gap_r2r0;
   uint32_t t_wr2rd_gap_r0r2;
   uint32_t t_wr2rd_gap_r2r0;
   uint32_t t_rd2wr_gap_r0r2;
   uint32_t t_rd2wr_gap_r2r0;
   uint32_t t_wr2wr_gap_r0r2;
   uint32_t t_wr2wr_gap_r2r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL1_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL2_struct {
   uint32_t t_rd2rd_gap_r0r3;
   uint32_t t_rd2rd_gap_r3r0;
   uint32_t t_wr2rd_gap_r0r3;
   uint32_t t_wr2rd_gap_r3r0;
   uint32_t t_rd2wr_gap_r0r3;
   uint32_t t_rd2wr_gap_r3r0;
   uint32_t t_wr2wr_gap_r0r3;
   uint32_t t_wr2wr_gap_r3r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL3_struct {
   uint32_t t_rd2rd_gap_r1r2;
   uint32_t t_rd2rd_gap_r2r1;
   uint32_t t_wr2rd_gap_r1r2;
   uint32_t t_wr2rd_gap_r2r1;
   uint32_t t_rd2wr_gap_r1r2;
   uint32_t t_rd2wr_gap_r2r1;
   uint32_t t_wr2wr_gap_r1r2;
   uint32_t t_wr2wr_gap_r2r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL4_struct {
   uint32_t t_rd2rd_gap_r1r3;
   uint32_t t_rd2rd_gap_r3r1;
   uint32_t t_wr2rd_gap_r1r3;
   uint32_t t_wr2rd_gap_r3r1;
   uint32_t t_rd2wr_gap_r1r3;
   uint32_t t_rd2wr_gap_r3r1;
   uint32_t t_wr2wr_gap_r1r3;
   uint32_t t_wr2wr_gap_r3r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL5_struct {
   uint32_t t_rd2rd_gap_r2r3;
   uint32_t t_rd2rd_gap_r3r2;
   uint32_t t_wr2rd_gap_r2r3;
   uint32_t t_wr2rd_gap_r3r2;
   uint32_t t_rd2wr_gap_r2r3;
   uint32_t t_rd2wr_gap_r3r2;
   uint32_t t_wr2wr_gap_r2r3;
   uint32_t t_wr2wr_gap_r3r2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANK_SWITCH_TIMING_CONTROL5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH0_MRAMTMG0_struct {
   uint32_t t_ras_min_mram;
   uint32_t t_faw_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_MRAMTMG0_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH0_MRAMTMG1_struct {
   uint32_t t_rc_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_MRAMTMG1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH0_MRAMTMG2_struct {
   uint32_t t_rp_mram;
   uint32_t t_rrd_mram;
   uint32_t t_rcd_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_MRAMTMG2_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH0_MRAMTMG3_struct {
   uint32_t t_rrd_s_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_MRAMTMG3_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH0_INITMR0_struct {
   uint32_t emr;
   uint32_t mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_INITMR0_struct_t;

typedef struct tag_REGB_FREQ2_CH0_INITMR1_struct {
   uint32_t emr3;
   uint32_t emr2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_INITMR1_struct_t;

typedef struct tag_REGB_FREQ2_CH0_INITMR2_struct {
   uint32_t mr5;
   uint32_t mr4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_INITMR2_struct_t;

typedef struct tag_REGB_FREQ2_CH0_INITMR3_struct {
   uint32_t mr6;
   uint32_t mr22;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_INITMR3_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DFITMG0_struct {
   uint32_t dfi_tphy_wrlat;
   uint32_t dfi_tphy_wrdata;
   uint32_t dfi_t_rddata_en;
   uint32_t dfi_t_ctrl_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DFITMG1_struct {
   uint32_t dfi_t_dram_clk_enable;
   uint32_t dfi_t_dram_clk_disable;
   uint32_t dfi_t_wrdata_delay;
   uint32_t dfi_t_parin_lat;
   uint32_t dfi_t_cmd_lat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG1_struct_t;

typedef struct tag_REGB_FREQ2_CH0_DFITMG2_struct {
   uint32_t dfi_tphy_wrcslat;
   uint32_t dfi_tphy_rdcslat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG2_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ2_CH0_DFITMG3_struct {
   uint32_t dfi_t_geardown_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG3_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DFITMG4_struct {
   uint32_t dfi_twck_dis;
   uint32_t dfi_twck_en_fs;
   uint32_t dfi_twck_en_wr;
   uint32_t dfi_twck_en_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG4_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DFITMG5_struct {
   uint32_t dfi_twck_toggle_post;
   uint32_t dfi_twck_toggle_cs;
   uint32_t dfi_twck_toggle;
   uint32_t dfi_twck_fast_toggle;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG5_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DFITMG7_struct {
   uint32_t dfi_t_2n_mode_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFITMG7_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_DFIUPDTMG1_struct {
   uint32_t dfi_t_ctrlupd_interval_max_x1024;
   uint32_t dfi_t_ctrlupd_interval_min_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DFIUPDTMG1_struct_t;

typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG0_struct {
   uint32_t t_refi_x1_x32;
   uint32_t refresh_to_x1_x32;
   uint32_t refresh_margin;
   uint32_t t_refi_x1_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG1_struct {
   uint32_t t_rfc_min;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG1_struct_t;

#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG2_struct {
   uint32_t t_rfc_min_dlr;
   uint32_t t_pbr2pbr;
   uint32_t t_pbr2act;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG2_struct_t;

#endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG3_struct {
   uint32_t t_rfcsb;
   uint32_t t_refsbrd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG4_struct {
   uint32_t refresh_timer0_start_value_x32;
   uint32_t refresh_timer1_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG4_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG5_struct {
   uint32_t refresh_timer2_start_value_x32;
   uint32_t refresh_timer3_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG6_struct {
   uint32_t refresh_timer_lr_offset_x32;
   uint32_t refresh_timer_rank_offset_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG6_struct_t;

#endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG7_struct {
   uint32_t t_rfcsb_dlr;
   uint32_t t_refsbrd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG7_struct_t;

#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HET_RANK_RFC
typedef struct tag_REGB_FREQ2_CH0_RFSHSET1TMG8_struct {
   uint32_t t_rfc_min_het;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET1TMG8_struct_t;

#endif //UMCTL2_HET_RANK_RFC
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_RFSHSET2TMG0_struct {
   uint32_t t_rfc_min_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH0_RFSHSET2TMG1_struct {
   uint32_t t_rfc_min_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET2TMG1_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_RFSHSET2TMG2_struct {
   uint32_t t_rfcsb_2;
   uint32_t t_refsbrd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH0_RFSHSET2TMG3_struct {
   uint32_t t_rfcsb_dlr_2;
   uint32_t t_refsbrd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RFSHSET2TMG3_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH0_ZQSET1TMG0_struct {
   uint32_t t_zq_long_nop;
   uint32_t t_zq_short_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_ZQSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH0_ZQSET1TMG1_struct {
   uint32_t t_zq_short_interval_x1024;
   uint32_t t_zq_reset_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_ZQSET1TMG1_struct_t;

#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH0_ZQSET2TMG0_struct {
   uint32_t t_zq_long_nop_2;
   uint32_t t_zq_short_nop_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_ZQSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH0_RCDINIT1_struct {
   uint32_t ctrl_word_1;
   uint32_t ctrl_word_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RCDINIT1_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH0_RCDINIT2_struct {
   uint32_t ctrl_word_3;
   uint32_t ctrl_word_4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RCDINIT2_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH0_RCDINIT3_struct {
   uint32_t ctrl_word_5;
   uint32_t ctrl_word_6;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RCDINIT3_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH0_RCDINIT4_struct {
   uint32_t ctrl_word_7;
   uint32_t ctrl_word_8;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RCDINIT4_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_FREQ2_CH0_DQSOSCCTL0_struct {
   uint32_t dqsosc_enable;
   uint32_t dqsosc_interval_unit;
   uint32_t dqsosc_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DQSOSCCTL0_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DERATEINT_struct {
   uint32_t mr4_read_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DERATEINT_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DERATEVAL0_struct {
   uint32_t derated_t_rrd;
   uint32_t derated_t_rp;
   uint32_t derated_t_ras_min;
   uint32_t derated_t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DERATEVAL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_DERATEVAL1_struct {
   uint32_t derated_t_rc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_DERATEVAL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH0_HWLPTMG0_struct {
   uint32_t hw_lp_idle_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_HWLPTMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH0_SCHEDTMG0_struct {
   uint32_t pageclose_timer;
   uint32_t rdwr_idle_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_SCHEDTMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH0_PERFHPR1_struct {
   uint32_t hpr_max_starve;
   uint32_t hpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_PERFHPR1_struct_t;

typedef struct tag_REGB_FREQ2_CH0_PERFLPR1_struct {
   uint32_t lpr_max_starve;
   uint32_t lpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_PERFLPR1_struct_t;

typedef struct tag_REGB_FREQ2_CH0_PERFWR1_struct {
   uint32_t w_max_starve;
   uint32_t w_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_PERFWR1_struct_t;

typedef struct tag_REGB_FREQ2_CH0_TMGCFG_struct {
   uint32_t frequency_ratio;
   uint32_t dfi_freq_fsp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_TMGCFG_struct_t;

#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_FREQ2_CH0_RANKTMG0_struct {
   uint32_t diff_rank_rd_gap;
   uint32_t diff_rank_wr_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANKTMG0_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ2_CH0_RANKTMG1_struct {
   uint32_t wr2rd_dr;
   uint32_t rd2wr_dr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_RANKTMG1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ2_CH0_PWRTMG_struct {
   uint32_t powerdown_to_x32;
   uint32_t selfref_to_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_PWRTMG_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH0_ODTCFG_struct {
   uint32_t rd_odt_delay;
   uint32_t rd_odt_hold;
   uint32_t wr_odt_delay;
   uint32_t wr_odt_hold;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_ODTCFG_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct tag_REGB_FREQ2_CH0_CRCPARTMG0_struct {
   uint32_t retry_fifo_max_hold_timer_x4;
   uint32_t t_crc_alert_pw_max;
   uint32_t t_par_alert_pw_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_CRCPARTMG0_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ2_CH0_CRCPARTMG1_struct {
   uint32_t t_csalt;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH0_CRCPARTMG1_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG0_struct {
   uint32_t t_ras_min;
   uint32_t t_ras_max;
   uint32_t t_faw;
   uint32_t wr2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG1_struct {
   uint32_t t_rc;
   uint32_t rd2pre;
   uint32_t t_xp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG1_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG2_struct {
   uint32_t wr2rd;
   uint32_t rd2wr;
   uint32_t read_latency;
   uint32_t write_latency;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG2_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG3_struct {
   uint32_t wr2mr;
   uint32_t rd2mr;
   uint32_t t_mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG3_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG4_struct {
   uint32_t t_rp;
   uint32_t t_rrd;
   uint32_t t_ccd;
   uint32_t t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG4_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG5_struct {
   uint32_t t_cke;
   uint32_t t_ckesr;
   uint32_t t_cksre;
   uint32_t t_cksrx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG5_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG6_struct {
   uint32_t t_ckcsx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG6_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG7_struct {
   uint32_t t_csh;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG7_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG8_struct {
   uint32_t t_xs_x32;
   uint32_t t_xs_dll_x32;
   uint32_t t_xs_abort_x32;
   uint32_t t_xs_fast_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG8_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG9_struct {
   uint32_t wr2rd_s;
   uint32_t t_rrd_s;
   uint32_t t_ccd_s;
   uint32_t ddr4_wr_preamble;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG9_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG10_struct {
   uint32_t t_gear_hold;
   uint32_t t_gear_setup;
   uint32_t t_cmd_gear;
   uint32_t t_sync_gear;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG10_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG11_struct {
   uint32_t t_ckmpe;
   uint32_t t_mpx_s;
   uint32_t t_mpx_lh;
   uint32_t post_mpsm_gap_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG11_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG12_struct {
   uint32_t t_mrd_pda;
   uint32_t t_cmdcke;
   uint32_t t_wr_mpr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG12_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG13_struct {
   uint32_t t_ppd;
   uint32_t t_ccd_w2;
   uint32_t t_ccd_mw;
   uint32_t odtloff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG13_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG14_struct {
   uint32_t t_xsr;
   uint32_t t_osco;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG14_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG15_struct {
   uint32_t t_stab_x32;
   uint32_t en_hwffc_t_stab;
   uint32_t en_dfi_lp_t_stab;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG15_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG16_struct {
   uint32_t t_ccd_dlr;
   uint32_t t_rrd_dlr;
   uint32_t t_faw_dlr;
   uint32_t t_rp_ca_parity;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG16_struct_t;

#endif //UMCTL2_CID_EN
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG17_struct {
   uint32_t t_vrcg_disable;
   uint32_t t_vrcg_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG17_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG18_struct {
   uint32_t t_mpdpxact;
   uint32_t t_mpsmx;
   uint32_t t_pd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG18_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG19_struct {
   uint32_t t_pda_h;
   uint32_t t_pda_s;
   uint32_t t_pda_dqs_delay;
   uint32_t t_pda_delay;
   uint32_t t_pda_latch;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG19_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG20_struct {
   uint32_t t_csl_srexit;
   uint32_t t_csh_srexit;
   uint32_t t_casrx;
   uint32_t t_cpded;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG21_struct {
   uint32_t t_osco_ddr5;
   uint32_t t_vrefca_cs;
   uint32_t t_mpc_hold;
   uint32_t t_mpc_setup;
   uint32_t t_mpc_cs;
   uint32_t t_csl;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG22_struct {
   uint32_t t_rd2wr_dpr;
   uint32_t t_rd2wr_dlr;
   uint32_t t_wr2rd_dpr;
   uint32_t t_wr2rd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG22_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG23_struct {
   uint32_t t_pdn;
   uint32_t t_pdn_dsm_x1024;
   uint32_t t_xsr_dsm_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG23_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG24_struct {
   uint32_t max_wr_sync;
   uint32_t max_rd_sync;
   uint32_t rd2wr_s;
   uint32_t bank_org;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG24_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG25_struct {
   uint32_t rda2pre;
   uint32_t wra2pre;
   uint32_t lpddr4_diff_bank_rwa2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG25_struct_t;

#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG26_struct {
   uint32_t t_ccd_r;
   uint32_t t_ccd_w;
   uint32_t t_ccd_r_s;
   uint32_t t_ccd_w_s;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG26_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG27_struct {
   uint32_t t_mrr2mpc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG27_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG28_struct {
   uint32_t t_srx2srx;
   uint32_t t_cpded2srx;
   uint32_t t_cssr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG28_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG29_struct {
   uint32_t t_ckact;
   uint32_t t_ckoff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG29_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DRAMSET1TMG30_struct {
   uint32_t mrr2rd;
   uint32_t mrr2wr;
   uint32_t mrr2mrw;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET1TMG30_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG0_struct {
   uint32_t t_ccd_r_2;
   uint32_t t_ccd_w_2;
   uint32_t t_ccd_r_s_2;
   uint32_t t_ccd_w_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG1_struct {
   uint32_t t_ras_min_2;
   uint32_t t_faw_2;
   uint32_t t_wr2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG1_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG2_struct {
   uint32_t t_rc_2;
   uint32_t rd2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG3_struct {
   uint32_t wr2rd_2;
   uint32_t rd2wr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG3_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG4_struct {
   uint32_t t_rd2wr_dpr_2;
   uint32_t t_rd2wr_dlr_2;
   uint32_t t_wr2rd_dpr_2;
   uint32_t t_wr2rd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG4_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG5_struct {
   uint32_t t_rp_2;
   uint32_t t_rrd_2;
   uint32_t t_ccd_2;
   uint32_t t_rcd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG5_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG6_struct {
   uint32_t wr2rd_s_2;
   uint32_t t_rrd_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG6_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG7_struct {
   uint32_t t_ppd_2;
   uint32_t t_ccd_w2_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG7_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG8_struct {
   uint32_t t_ccd_dlr_2;
   uint32_t t_rrd_dlr_2;
   uint32_t t_faw_dlr_2;
   uint32_t t_rp_ca_parity_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG8_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG9_struct {
   uint32_t t_xs_x32_2;
   uint32_t t_xs_dll_x32_2;
   uint32_t t_xs_abort_x32_2;
   uint32_t t_xs_fast_x32_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG9_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG10_struct {
   uint32_t t_mr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG10_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_DRAMSET2TMG11_struct {
   uint32_t t_mrr2mpc_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DRAMSET2TMG11_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL0_struct {
   uint32_t t_rd2rd_gap_r0r1;
   uint32_t t_rd2rd_gap_r1r0;
   uint32_t t_wr2rd_gap_r0r1;
   uint32_t t_wr2rd_gap_r1r0;
   uint32_t t_rd2wr_gap_r0r1;
   uint32_t t_rd2wr_gap_r1r0;
   uint32_t t_wr2wr_gap_r0r1;
   uint32_t t_wr2wr_gap_r1r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL0_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL1_struct {
   uint32_t t_rd2rd_gap_r0r2;
   uint32_t t_rd2rd_gap_r2r0;
   uint32_t t_wr2rd_gap_r0r2;
   uint32_t t_wr2rd_gap_r2r0;
   uint32_t t_rd2wr_gap_r0r2;
   uint32_t t_rd2wr_gap_r2r0;
   uint32_t t_wr2wr_gap_r0r2;
   uint32_t t_wr2wr_gap_r2r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL1_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL2_struct {
   uint32_t t_rd2rd_gap_r0r3;
   uint32_t t_rd2rd_gap_r3r0;
   uint32_t t_wr2rd_gap_r0r3;
   uint32_t t_wr2rd_gap_r3r0;
   uint32_t t_rd2wr_gap_r0r3;
   uint32_t t_rd2wr_gap_r3r0;
   uint32_t t_wr2wr_gap_r0r3;
   uint32_t t_wr2wr_gap_r3r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL3_struct {
   uint32_t t_rd2rd_gap_r1r2;
   uint32_t t_rd2rd_gap_r2r1;
   uint32_t t_wr2rd_gap_r1r2;
   uint32_t t_wr2rd_gap_r2r1;
   uint32_t t_rd2wr_gap_r1r2;
   uint32_t t_rd2wr_gap_r2r1;
   uint32_t t_wr2wr_gap_r1r2;
   uint32_t t_wr2wr_gap_r2r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL4_struct {
   uint32_t t_rd2rd_gap_r1r3;
   uint32_t t_rd2rd_gap_r3r1;
   uint32_t t_wr2rd_gap_r1r3;
   uint32_t t_wr2rd_gap_r3r1;
   uint32_t t_rd2wr_gap_r1r3;
   uint32_t t_rd2wr_gap_r3r1;
   uint32_t t_wr2wr_gap_r1r3;
   uint32_t t_wr2wr_gap_r3r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL5_struct {
   uint32_t t_rd2rd_gap_r2r3;
   uint32_t t_rd2rd_gap_r3r2;
   uint32_t t_wr2rd_gap_r2r3;
   uint32_t t_wr2rd_gap_r3r2;
   uint32_t t_rd2wr_gap_r2r3;
   uint32_t t_rd2wr_gap_r3r2;
   uint32_t t_wr2wr_gap_r2r3;
   uint32_t t_wr2wr_gap_r3r2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANK_SWITCH_TIMING_CONTROL5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH1_MRAMTMG0_struct {
   uint32_t t_ras_min_mram;
   uint32_t t_faw_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_MRAMTMG0_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH1_MRAMTMG1_struct {
   uint32_t t_rc_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_MRAMTMG1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH1_MRAMTMG2_struct {
   uint32_t t_rp_mram;
   uint32_t t_rrd_mram;
   uint32_t t_rcd_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_MRAMTMG2_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH1_MRAMTMG3_struct {
   uint32_t t_rrd_s_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_MRAMTMG3_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ2_CH1_INITMR0_struct {
   uint32_t emr;
   uint32_t mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_INITMR0_struct_t;

typedef struct tag_REGB_FREQ2_CH1_INITMR1_struct {
   uint32_t emr3;
   uint32_t emr2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_INITMR1_struct_t;

typedef struct tag_REGB_FREQ2_CH1_INITMR2_struct {
   uint32_t mr5;
   uint32_t mr4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_INITMR2_struct_t;

typedef struct tag_REGB_FREQ2_CH1_INITMR3_struct {
   uint32_t mr6;
   uint32_t mr22;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_INITMR3_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DFITMG0_struct {
   uint32_t dfi_tphy_wrlat;
   uint32_t dfi_tphy_wrdata;
   uint32_t dfi_t_rddata_en;
   uint32_t dfi_t_ctrl_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DFITMG1_struct {
   uint32_t dfi_t_dram_clk_enable;
   uint32_t dfi_t_dram_clk_disable;
   uint32_t dfi_t_wrdata_delay;
   uint32_t dfi_t_parin_lat;
   uint32_t dfi_t_cmd_lat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG1_struct_t;

typedef struct tag_REGB_FREQ2_CH1_DFITMG2_struct {
   uint32_t dfi_tphy_wrcslat;
   uint32_t dfi_tphy_rdcslat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG2_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ2_CH1_DFITMG3_struct {
   uint32_t dfi_t_geardown_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG3_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DFITMG4_struct {
   uint32_t dfi_twck_dis;
   uint32_t dfi_twck_en_fs;
   uint32_t dfi_twck_en_wr;
   uint32_t dfi_twck_en_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG4_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DFITMG5_struct {
   uint32_t dfi_twck_toggle_post;
   uint32_t dfi_twck_toggle_cs;
   uint32_t dfi_twck_toggle;
   uint32_t dfi_twck_fast_toggle;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG5_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DFITMG7_struct {
   uint32_t dfi_t_2n_mode_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFITMG7_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_DFIUPDTMG1_struct {
   uint32_t dfi_t_ctrlupd_interval_max_x1024;
   uint32_t dfi_t_ctrlupd_interval_min_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DFIUPDTMG1_struct_t;

typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG0_struct {
   uint32_t t_refi_x1_x32;
   uint32_t refresh_to_x1_x32;
   uint32_t refresh_margin;
   uint32_t t_refi_x1_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG1_struct {
   uint32_t t_rfc_min;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG1_struct_t;

#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG2_struct {
   uint32_t t_rfc_min_dlr;
   uint32_t t_pbr2pbr;
   uint32_t t_pbr2act;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG2_struct_t;

#endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG3_struct {
   uint32_t t_rfcsb;
   uint32_t t_refsbrd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG4_struct {
   uint32_t refresh_timer0_start_value_x32;
   uint32_t refresh_timer1_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG4_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG5_struct {
   uint32_t refresh_timer2_start_value_x32;
   uint32_t refresh_timer3_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG6_struct {
   uint32_t refresh_timer_lr_offset_x32;
   uint32_t refresh_timer_rank_offset_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG6_struct_t;

#endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG7_struct {
   uint32_t t_rfcsb_dlr;
   uint32_t t_refsbrd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG7_struct_t;

#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HET_RANK_RFC
typedef struct tag_REGB_FREQ2_CH1_RFSHSET1TMG8_struct {
   uint32_t t_rfc_min_het;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET1TMG8_struct_t;

#endif //UMCTL2_HET_RANK_RFC
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_RFSHSET2TMG0_struct {
   uint32_t t_rfc_min_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH1_RFSHSET2TMG1_struct {
   uint32_t t_rfc_min_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET2TMG1_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_RFSHSET2TMG2_struct {
   uint32_t t_rfcsb_2;
   uint32_t t_refsbrd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ2_CH1_RFSHSET2TMG3_struct {
   uint32_t t_rfcsb_dlr_2;
   uint32_t t_refsbrd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RFSHSET2TMG3_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ2_CH1_ZQSET1TMG0_struct {
   uint32_t t_zq_long_nop;
   uint32_t t_zq_short_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_ZQSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH1_ZQSET1TMG1_struct {
   uint32_t t_zq_short_interval_x1024;
   uint32_t t_zq_reset_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_ZQSET1TMG1_struct_t;

#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ2_CH1_ZQSET2TMG0_struct {
   uint32_t t_zq_long_nop_2;
   uint32_t t_zq_short_nop_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_ZQSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH1_RCDINIT1_struct {
   uint32_t ctrl_word_1;
   uint32_t ctrl_word_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RCDINIT1_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH1_RCDINIT2_struct {
   uint32_t ctrl_word_3;
   uint32_t ctrl_word_4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RCDINIT2_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH1_RCDINIT3_struct {
   uint32_t ctrl_word_5;
   uint32_t ctrl_word_6;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RCDINIT3_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH1_RCDINIT4_struct {
   uint32_t ctrl_word_7;
   uint32_t ctrl_word_8;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RCDINIT4_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_FREQ2_CH1_DQSOSCCTL0_struct {
   uint32_t dqsosc_enable;
   uint32_t dqsosc_interval_unit;
   uint32_t dqsosc_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DQSOSCCTL0_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DERATEINT_struct {
   uint32_t mr4_read_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DERATEINT_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DERATEVAL0_struct {
   uint32_t derated_t_rrd;
   uint32_t derated_t_rp;
   uint32_t derated_t_ras_min;
   uint32_t derated_t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DERATEVAL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_DERATEVAL1_struct {
   uint32_t derated_t_rc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_DERATEVAL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ2_CH1_HWLPTMG0_struct {
   uint32_t hw_lp_idle_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_HWLPTMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH1_SCHEDTMG0_struct {
   uint32_t pageclose_timer;
   uint32_t rdwr_idle_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_SCHEDTMG0_struct_t;

typedef struct tag_REGB_FREQ2_CH1_PERFHPR1_struct {
   uint32_t hpr_max_starve;
   uint32_t hpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_PERFHPR1_struct_t;

typedef struct tag_REGB_FREQ2_CH1_PERFLPR1_struct {
   uint32_t lpr_max_starve;
   uint32_t lpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_PERFLPR1_struct_t;

typedef struct tag_REGB_FREQ2_CH1_PERFWR1_struct {
   uint32_t w_max_starve;
   uint32_t w_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_PERFWR1_struct_t;

#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_FREQ2_CH1_RANKTMG0_struct {
   uint32_t diff_rank_rd_gap;
   uint32_t diff_rank_wr_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANKTMG0_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ2_CH1_RANKTMG1_struct {
   uint32_t wr2rd_dr;
   uint32_t rd2wr_dr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_RANKTMG1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ2_CH1_PWRTMG_struct {
   uint32_t powerdown_to_x32;
   uint32_t selfref_to_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_PWRTMG_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ2_CH1_ODTCFG_struct {
   uint32_t rd_odt_delay;
   uint32_t rd_odt_hold;
   uint32_t wr_odt_delay;
   uint32_t wr_odt_hold;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_ODTCFG_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct tag_REGB_FREQ2_CH1_CRCPARTMG0_struct {
   uint32_t retry_fifo_max_hold_timer_x4;
   uint32_t t_crc_alert_pw_max;
   uint32_t t_par_alert_pw_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_CRCPARTMG0_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ2_CH1_CRCPARTMG1_struct {
   uint32_t t_csalt;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ2_CH1_CRCPARTMG1_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG0_struct {
   uint32_t t_ras_min;
   uint32_t t_ras_max;
   uint32_t t_faw;
   uint32_t wr2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG1_struct {
   uint32_t t_rc;
   uint32_t rd2pre;
   uint32_t t_xp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG1_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG2_struct {
   uint32_t wr2rd;
   uint32_t rd2wr;
   uint32_t read_latency;
   uint32_t write_latency;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG2_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG3_struct {
   uint32_t wr2mr;
   uint32_t rd2mr;
   uint32_t t_mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG3_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG4_struct {
   uint32_t t_rp;
   uint32_t t_rrd;
   uint32_t t_ccd;
   uint32_t t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG4_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG5_struct {
   uint32_t t_cke;
   uint32_t t_ckesr;
   uint32_t t_cksre;
   uint32_t t_cksrx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG5_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG6_struct {
   uint32_t t_ckcsx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG6_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG7_struct {
   uint32_t t_csh;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG7_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG8_struct {
   uint32_t t_xs_x32;
   uint32_t t_xs_dll_x32;
   uint32_t t_xs_abort_x32;
   uint32_t t_xs_fast_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG8_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG9_struct {
   uint32_t wr2rd_s;
   uint32_t t_rrd_s;
   uint32_t t_ccd_s;
   uint32_t ddr4_wr_preamble;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG9_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG10_struct {
   uint32_t t_gear_hold;
   uint32_t t_gear_setup;
   uint32_t t_cmd_gear;
   uint32_t t_sync_gear;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG10_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG11_struct {
   uint32_t t_ckmpe;
   uint32_t t_mpx_s;
   uint32_t t_mpx_lh;
   uint32_t post_mpsm_gap_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG11_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG12_struct {
   uint32_t t_mrd_pda;
   uint32_t t_cmdcke;
   uint32_t t_wr_mpr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG12_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG13_struct {
   uint32_t t_ppd;
   uint32_t t_ccd_w2;
   uint32_t t_ccd_mw;
   uint32_t odtloff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG13_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG14_struct {
   uint32_t t_xsr;
   uint32_t t_osco;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG14_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG15_struct {
   uint32_t t_stab_x32;
   uint32_t en_hwffc_t_stab;
   uint32_t en_dfi_lp_t_stab;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG15_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG16_struct {
   uint32_t t_ccd_dlr;
   uint32_t t_rrd_dlr;
   uint32_t t_faw_dlr;
   uint32_t t_rp_ca_parity;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG16_struct_t;

#endif //UMCTL2_CID_EN
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG17_struct {
   uint32_t t_vrcg_disable;
   uint32_t t_vrcg_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG17_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG18_struct {
   uint32_t t_mpdpxact;
   uint32_t t_mpsmx;
   uint32_t t_pd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG18_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG19_struct {
   uint32_t t_pda_h;
   uint32_t t_pda_s;
   uint32_t t_pda_dqs_delay;
   uint32_t t_pda_delay;
   uint32_t t_pda_latch;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG19_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG20_struct {
   uint32_t t_csl_srexit;
   uint32_t t_csh_srexit;
   uint32_t t_casrx;
   uint32_t t_cpded;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG21_struct {
   uint32_t t_osco_ddr5;
   uint32_t t_vrefca_cs;
   uint32_t t_mpc_hold;
   uint32_t t_mpc_setup;
   uint32_t t_mpc_cs;
   uint32_t t_csl;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG22_struct {
   uint32_t t_rd2wr_dpr;
   uint32_t t_rd2wr_dlr;
   uint32_t t_wr2rd_dpr;
   uint32_t t_wr2rd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG22_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG23_struct {
   uint32_t t_pdn;
   uint32_t t_pdn_dsm_x1024;
   uint32_t t_xsr_dsm_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG23_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG24_struct {
   uint32_t max_wr_sync;
   uint32_t max_rd_sync;
   uint32_t rd2wr_s;
   uint32_t bank_org;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG24_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG25_struct {
   uint32_t rda2pre;
   uint32_t wra2pre;
   uint32_t lpddr4_diff_bank_rwa2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG25_struct_t;

#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG26_struct {
   uint32_t t_ccd_r;
   uint32_t t_ccd_w;
   uint32_t t_ccd_r_s;
   uint32_t t_ccd_w_s;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG26_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG27_struct {
   uint32_t t_mrr2mpc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG27_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG28_struct {
   uint32_t t_srx2srx;
   uint32_t t_cpded2srx;
   uint32_t t_cssr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG28_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG29_struct {
   uint32_t t_ckact;
   uint32_t t_ckoff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG29_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DRAMSET1TMG30_struct {
   uint32_t mrr2rd;
   uint32_t mrr2wr;
   uint32_t mrr2mrw;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET1TMG30_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG0_struct {
   uint32_t t_ccd_r_2;
   uint32_t t_ccd_w_2;
   uint32_t t_ccd_r_s_2;
   uint32_t t_ccd_w_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG1_struct {
   uint32_t t_ras_min_2;
   uint32_t t_faw_2;
   uint32_t t_wr2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG1_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG2_struct {
   uint32_t t_rc_2;
   uint32_t rd2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG3_struct {
   uint32_t wr2rd_2;
   uint32_t rd2wr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG3_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG4_struct {
   uint32_t t_rd2wr_dpr_2;
   uint32_t t_rd2wr_dlr_2;
   uint32_t t_wr2rd_dpr_2;
   uint32_t t_wr2rd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG4_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG5_struct {
   uint32_t t_rp_2;
   uint32_t t_rrd_2;
   uint32_t t_ccd_2;
   uint32_t t_rcd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG5_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG6_struct {
   uint32_t wr2rd_s_2;
   uint32_t t_rrd_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG6_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG7_struct {
   uint32_t t_ppd_2;
   uint32_t t_ccd_w2_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG7_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG8_struct {
   uint32_t t_ccd_dlr_2;
   uint32_t t_rrd_dlr_2;
   uint32_t t_faw_dlr_2;
   uint32_t t_rp_ca_parity_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG8_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG9_struct {
   uint32_t t_xs_x32_2;
   uint32_t t_xs_dll_x32_2;
   uint32_t t_xs_abort_x32_2;
   uint32_t t_xs_fast_x32_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG9_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG10_struct {
   uint32_t t_mr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG10_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_DRAMSET2TMG11_struct {
   uint32_t t_mrr2mpc_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DRAMSET2TMG11_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL0_struct {
   uint32_t t_rd2rd_gap_r0r1;
   uint32_t t_rd2rd_gap_r1r0;
   uint32_t t_wr2rd_gap_r0r1;
   uint32_t t_wr2rd_gap_r1r0;
   uint32_t t_rd2wr_gap_r0r1;
   uint32_t t_rd2wr_gap_r1r0;
   uint32_t t_wr2wr_gap_r0r1;
   uint32_t t_wr2wr_gap_r1r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL0_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL1_struct {
   uint32_t t_rd2rd_gap_r0r2;
   uint32_t t_rd2rd_gap_r2r0;
   uint32_t t_wr2rd_gap_r0r2;
   uint32_t t_wr2rd_gap_r2r0;
   uint32_t t_rd2wr_gap_r0r2;
   uint32_t t_rd2wr_gap_r2r0;
   uint32_t t_wr2wr_gap_r0r2;
   uint32_t t_wr2wr_gap_r2r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL1_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL2_struct {
   uint32_t t_rd2rd_gap_r0r3;
   uint32_t t_rd2rd_gap_r3r0;
   uint32_t t_wr2rd_gap_r0r3;
   uint32_t t_wr2rd_gap_r3r0;
   uint32_t t_rd2wr_gap_r0r3;
   uint32_t t_rd2wr_gap_r3r0;
   uint32_t t_wr2wr_gap_r0r3;
   uint32_t t_wr2wr_gap_r3r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL3_struct {
   uint32_t t_rd2rd_gap_r1r2;
   uint32_t t_rd2rd_gap_r2r1;
   uint32_t t_wr2rd_gap_r1r2;
   uint32_t t_wr2rd_gap_r2r1;
   uint32_t t_rd2wr_gap_r1r2;
   uint32_t t_rd2wr_gap_r2r1;
   uint32_t t_wr2wr_gap_r1r2;
   uint32_t t_wr2wr_gap_r2r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL4_struct {
   uint32_t t_rd2rd_gap_r1r3;
   uint32_t t_rd2rd_gap_r3r1;
   uint32_t t_wr2rd_gap_r1r3;
   uint32_t t_wr2rd_gap_r3r1;
   uint32_t t_rd2wr_gap_r1r3;
   uint32_t t_rd2wr_gap_r3r1;
   uint32_t t_wr2wr_gap_r1r3;
   uint32_t t_wr2wr_gap_r3r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL5_struct {
   uint32_t t_rd2rd_gap_r2r3;
   uint32_t t_rd2rd_gap_r3r2;
   uint32_t t_wr2rd_gap_r2r3;
   uint32_t t_wr2rd_gap_r3r2;
   uint32_t t_rd2wr_gap_r2r3;
   uint32_t t_rd2wr_gap_r3r2;
   uint32_t t_wr2wr_gap_r2r3;
   uint32_t t_wr2wr_gap_r3r2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANK_SWITCH_TIMING_CONTROL5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH0_MRAMTMG0_struct {
   uint32_t t_ras_min_mram;
   uint32_t t_faw_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_MRAMTMG0_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH0_MRAMTMG1_struct {
   uint32_t t_rc_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_MRAMTMG1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH0_MRAMTMG2_struct {
   uint32_t t_rp_mram;
   uint32_t t_rrd_mram;
   uint32_t t_rcd_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_MRAMTMG2_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH0_MRAMTMG3_struct {
   uint32_t t_rrd_s_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_MRAMTMG3_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH0_INITMR0_struct {
   uint32_t emr;
   uint32_t mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_INITMR0_struct_t;

typedef struct tag_REGB_FREQ3_CH0_INITMR1_struct {
   uint32_t emr3;
   uint32_t emr2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_INITMR1_struct_t;

typedef struct tag_REGB_FREQ3_CH0_INITMR2_struct {
   uint32_t mr5;
   uint32_t mr4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_INITMR2_struct_t;

typedef struct tag_REGB_FREQ3_CH0_INITMR3_struct {
   uint32_t mr6;
   uint32_t mr22;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_INITMR3_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DFITMG0_struct {
   uint32_t dfi_tphy_wrlat;
   uint32_t dfi_tphy_wrdata;
   uint32_t dfi_t_rddata_en;
   uint32_t dfi_t_ctrl_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DFITMG1_struct {
   uint32_t dfi_t_dram_clk_enable;
   uint32_t dfi_t_dram_clk_disable;
   uint32_t dfi_t_wrdata_delay;
   uint32_t dfi_t_parin_lat;
   uint32_t dfi_t_cmd_lat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG1_struct_t;

typedef struct tag_REGB_FREQ3_CH0_DFITMG2_struct {
   uint32_t dfi_tphy_wrcslat;
   uint32_t dfi_tphy_rdcslat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG2_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ3_CH0_DFITMG3_struct {
   uint32_t dfi_t_geardown_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG3_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DFITMG4_struct {
   uint32_t dfi_twck_dis;
   uint32_t dfi_twck_en_fs;
   uint32_t dfi_twck_en_wr;
   uint32_t dfi_twck_en_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG4_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DFITMG5_struct {
   uint32_t dfi_twck_toggle_post;
   uint32_t dfi_twck_toggle_cs;
   uint32_t dfi_twck_toggle;
   uint32_t dfi_twck_fast_toggle;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG5_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DFITMG7_struct {
   uint32_t dfi_t_2n_mode_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFITMG7_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_DFIUPDTMG1_struct {
   uint32_t dfi_t_ctrlupd_interval_max_x1024;
   uint32_t dfi_t_ctrlupd_interval_min_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DFIUPDTMG1_struct_t;

typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG0_struct {
   uint32_t t_refi_x1_x32;
   uint32_t refresh_to_x1_x32;
   uint32_t refresh_margin;
   uint32_t t_refi_x1_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG1_struct {
   uint32_t t_rfc_min;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG1_struct_t;

#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG2_struct {
   uint32_t t_rfc_min_dlr;
   uint32_t t_pbr2pbr;
   uint32_t t_pbr2act;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG2_struct_t;

#endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG3_struct {
   uint32_t t_rfcsb;
   uint32_t t_refsbrd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG4_struct {
   uint32_t refresh_timer0_start_value_x32;
   uint32_t refresh_timer1_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG4_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG5_struct {
   uint32_t refresh_timer2_start_value_x32;
   uint32_t refresh_timer3_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG6_struct {
   uint32_t refresh_timer_lr_offset_x32;
   uint32_t refresh_timer_rank_offset_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG6_struct_t;

#endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG7_struct {
   uint32_t t_rfcsb_dlr;
   uint32_t t_refsbrd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG7_struct_t;

#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HET_RANK_RFC
typedef struct tag_REGB_FREQ3_CH0_RFSHSET1TMG8_struct {
   uint32_t t_rfc_min_het;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET1TMG8_struct_t;

#endif //UMCTL2_HET_RANK_RFC
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_RFSHSET2TMG0_struct {
   uint32_t t_rfc_min_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH0_RFSHSET2TMG1_struct {
   uint32_t t_rfc_min_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET2TMG1_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_RFSHSET2TMG2_struct {
   uint32_t t_rfcsb_2;
   uint32_t t_refsbrd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH0_RFSHSET2TMG3_struct {
   uint32_t t_rfcsb_dlr_2;
   uint32_t t_refsbrd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RFSHSET2TMG3_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH0_ZQSET1TMG0_struct {
   uint32_t t_zq_long_nop;
   uint32_t t_zq_short_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_ZQSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH0_ZQSET1TMG1_struct {
   uint32_t t_zq_short_interval_x1024;
   uint32_t t_zq_reset_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_ZQSET1TMG1_struct_t;

#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH0_ZQSET2TMG0_struct {
   uint32_t t_zq_long_nop_2;
   uint32_t t_zq_short_nop_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_ZQSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH0_RCDINIT1_struct {
   uint32_t ctrl_word_1;
   uint32_t ctrl_word_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RCDINIT1_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH0_RCDINIT2_struct {
   uint32_t ctrl_word_3;
   uint32_t ctrl_word_4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RCDINIT2_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH0_RCDINIT3_struct {
   uint32_t ctrl_word_5;
   uint32_t ctrl_word_6;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RCDINIT3_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH0_RCDINIT4_struct {
   uint32_t ctrl_word_7;
   uint32_t ctrl_word_8;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RCDINIT4_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_FREQ3_CH0_DQSOSCCTL0_struct {
   uint32_t dqsosc_enable;
   uint32_t dqsosc_interval_unit;
   uint32_t dqsosc_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DQSOSCCTL0_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DERATEINT_struct {
   uint32_t mr4_read_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DERATEINT_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DERATEVAL0_struct {
   uint32_t derated_t_rrd;
   uint32_t derated_t_rp;
   uint32_t derated_t_ras_min;
   uint32_t derated_t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DERATEVAL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_DERATEVAL1_struct {
   uint32_t derated_t_rc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_DERATEVAL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH0_HWLPTMG0_struct {
   uint32_t hw_lp_idle_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_HWLPTMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH0_SCHEDTMG0_struct {
   uint32_t pageclose_timer;
   uint32_t rdwr_idle_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_SCHEDTMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH0_PERFHPR1_struct {
   uint32_t hpr_max_starve;
   uint32_t hpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_PERFHPR1_struct_t;

typedef struct tag_REGB_FREQ3_CH0_PERFLPR1_struct {
   uint32_t lpr_max_starve;
   uint32_t lpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_PERFLPR1_struct_t;

typedef struct tag_REGB_FREQ3_CH0_PERFWR1_struct {
   uint32_t w_max_starve;
   uint32_t w_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_PERFWR1_struct_t;

typedef struct tag_REGB_FREQ3_CH0_TMGCFG_struct {
   uint32_t frequency_ratio;
   uint32_t dfi_freq_fsp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_TMGCFG_struct_t;

#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_FREQ3_CH0_RANKTMG0_struct {
   uint32_t diff_rank_rd_gap;
   uint32_t diff_rank_wr_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANKTMG0_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ3_CH0_RANKTMG1_struct {
   uint32_t wr2rd_dr;
   uint32_t rd2wr_dr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_RANKTMG1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ3_CH0_PWRTMG_struct {
   uint32_t powerdown_to_x32;
   uint32_t selfref_to_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_PWRTMG_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH0_ODTCFG_struct {
   uint32_t rd_odt_delay;
   uint32_t rd_odt_hold;
   uint32_t wr_odt_delay;
   uint32_t wr_odt_hold;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_ODTCFG_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct tag_REGB_FREQ3_CH0_CRCPARTMG0_struct {
   uint32_t retry_fifo_max_hold_timer_x4;
   uint32_t t_crc_alert_pw_max;
   uint32_t t_par_alert_pw_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_CRCPARTMG0_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ3_CH0_CRCPARTMG1_struct {
   uint32_t t_csalt;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH0_CRCPARTMG1_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG0_struct {
   uint32_t t_ras_min;
   uint32_t t_ras_max;
   uint32_t t_faw;
   uint32_t wr2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG1_struct {
   uint32_t t_rc;
   uint32_t rd2pre;
   uint32_t t_xp;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG1_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG2_struct {
   uint32_t wr2rd;
   uint32_t rd2wr;
   uint32_t read_latency;
   uint32_t write_latency;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG2_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG3_struct {
   uint32_t wr2mr;
   uint32_t rd2mr;
   uint32_t t_mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG3_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG4_struct {
   uint32_t t_rp;
   uint32_t t_rrd;
   uint32_t t_ccd;
   uint32_t t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG4_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG5_struct {
   uint32_t t_cke;
   uint32_t t_ckesr;
   uint32_t t_cksre;
   uint32_t t_cksrx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG5_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG6_struct {
   uint32_t t_ckcsx;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG6_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG7_struct {
   uint32_t t_csh;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG7_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG8_struct {
   uint32_t t_xs_x32;
   uint32_t t_xs_dll_x32;
   uint32_t t_xs_abort_x32;
   uint32_t t_xs_fast_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG8_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG9_struct {
   uint32_t wr2rd_s;
   uint32_t t_rrd_s;
   uint32_t t_ccd_s;
   uint32_t ddr4_wr_preamble;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG9_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG10_struct {
   uint32_t t_gear_hold;
   uint32_t t_gear_setup;
   uint32_t t_cmd_gear;
   uint32_t t_sync_gear;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG10_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG11_struct {
   uint32_t t_ckmpe;
   uint32_t t_mpx_s;
   uint32_t t_mpx_lh;
   uint32_t post_mpsm_gap_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG11_struct_t;

#endif //DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG12_struct {
   uint32_t t_mrd_pda;
   uint32_t t_cmdcke;
   uint32_t t_wr_mpr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG12_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG13_struct {
   uint32_t t_ppd;
   uint32_t t_ccd_w2;
   uint32_t t_ccd_mw;
   uint32_t odtloff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG13_struct_t;

#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG14_struct {
   uint32_t t_xsr;
   uint32_t t_osco;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG14_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG15_struct {
   uint32_t t_stab_x32;
   uint32_t en_hwffc_t_stab;
   uint32_t en_dfi_lp_t_stab;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG15_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG16_struct {
   uint32_t t_ccd_dlr;
   uint32_t t_rrd_dlr;
   uint32_t t_faw_dlr;
   uint32_t t_rp_ca_parity;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG16_struct_t;

#endif //UMCTL2_CID_EN
#ifdef UMCTL2_HWFFC_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG17_struct {
   uint32_t t_vrcg_disable;
   uint32_t t_vrcg_enable;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG17_struct_t;

#endif //UMCTL2_HWFFC_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG18_struct {
   uint32_t t_mpdpxact;
   uint32_t t_mpsmx;
   uint32_t t_pd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG18_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG19_struct {
   uint32_t t_pda_h;
   uint32_t t_pda_s;
   uint32_t t_pda_dqs_delay;
   uint32_t t_pda_delay;
   uint32_t t_pda_latch;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG19_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG20_struct {
   uint32_t t_csl_srexit;
   uint32_t t_csh_srexit;
   uint32_t t_casrx;
   uint32_t t_cpded;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG20_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG21_struct {
   uint32_t t_osco_ddr5;
   uint32_t t_vrefca_cs;
   uint32_t t_mpc_hold;
   uint32_t t_mpc_setup;
   uint32_t t_mpc_cs;
   uint32_t t_csl;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG21_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG22_struct {
   uint32_t t_rd2wr_dpr;
   uint32_t t_rd2wr_dlr;
   uint32_t t_wr2rd_dpr;
   uint32_t t_wr2rd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG22_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG23_struct {
   uint32_t t_pdn;
   uint32_t t_pdn_dsm_x1024;
   uint32_t t_xsr_dsm_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG23_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG24_struct {
   uint32_t max_wr_sync;
   uint32_t max_rd_sync;
   uint32_t rd2wr_s;
   uint32_t bank_org;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG24_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG25_struct {
   uint32_t rda2pre;
   uint32_t wra2pre;
   uint32_t lpddr4_diff_bank_rwa2pre;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG25_struct_t;

#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG26_struct {
   uint32_t t_ccd_r;
   uint32_t t_ccd_w;
   uint32_t t_ccd_r_s;
   uint32_t t_ccd_w_s;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG26_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG27_struct {
   uint32_t t_mrr2mpc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG27_struct_t;

#endif //MEMC_DDR5
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG28_struct {
   uint32_t t_srx2srx;
   uint32_t t_cpded2srx;
   uint32_t t_cssr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG28_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG29_struct {
   uint32_t t_ckact;
   uint32_t t_ckoff;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG29_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DRAMSET1TMG30_struct {
   uint32_t mrr2rd;
   uint32_t mrr2wr;
   uint32_t mrr2mrw;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET1TMG30_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG0_struct {
   uint32_t t_ccd_r_2;
   uint32_t t_ccd_w_2;
   uint32_t t_ccd_r_s_2;
   uint32_t t_ccd_w_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG1_struct {
   uint32_t t_ras_min_2;
   uint32_t t_faw_2;
   uint32_t t_wr2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG1_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG2_struct {
   uint32_t t_rc_2;
   uint32_t rd2pre_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG3_struct {
   uint32_t wr2rd_2;
   uint32_t rd2wr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG3_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG4_struct {
   uint32_t t_rd2wr_dpr_2;
   uint32_t t_rd2wr_dlr_2;
   uint32_t t_wr2rd_dpr_2;
   uint32_t t_wr2rd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG4_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG5_struct {
   uint32_t t_rp_2;
   uint32_t t_rrd_2;
   uint32_t t_ccd_2;
   uint32_t t_rcd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG5_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG6_struct {
   uint32_t wr2rd_s_2;
   uint32_t t_rrd_s_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG6_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG7_struct {
   uint32_t t_ppd_2;
   uint32_t t_ccd_w2_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG7_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG8_struct {
   uint32_t t_ccd_dlr_2;
   uint32_t t_rrd_dlr_2;
   uint32_t t_faw_dlr_2;
   uint32_t t_rp_ca_parity_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG8_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG9_struct {
   uint32_t t_xs_x32_2;
   uint32_t t_xs_dll_x32_2;
   uint32_t t_xs_abort_x32_2;
   uint32_t t_xs_fast_x32_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG9_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG10_struct {
   uint32_t t_mr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG10_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_DRAMSET2TMG11_struct {
   uint32_t t_mrr2mpc_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DRAMSET2TMG11_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL0_struct {
   uint32_t t_rd2rd_gap_r0r1;
   uint32_t t_rd2rd_gap_r1r0;
   uint32_t t_wr2rd_gap_r0r1;
   uint32_t t_wr2rd_gap_r1r0;
   uint32_t t_rd2wr_gap_r0r1;
   uint32_t t_rd2wr_gap_r1r0;
   uint32_t t_wr2wr_gap_r0r1;
   uint32_t t_wr2wr_gap_r1r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL0_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL1_struct {
   uint32_t t_rd2rd_gap_r0r2;
   uint32_t t_rd2rd_gap_r2r0;
   uint32_t t_wr2rd_gap_r0r2;
   uint32_t t_wr2rd_gap_r2r0;
   uint32_t t_rd2wr_gap_r0r2;
   uint32_t t_rd2wr_gap_r2r0;
   uint32_t t_wr2wr_gap_r0r2;
   uint32_t t_wr2wr_gap_r2r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL1_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL2_struct {
   uint32_t t_rd2rd_gap_r0r3;
   uint32_t t_rd2rd_gap_r3r0;
   uint32_t t_wr2rd_gap_r0r3;
   uint32_t t_wr2rd_gap_r3r0;
   uint32_t t_rd2wr_gap_r0r3;
   uint32_t t_rd2wr_gap_r3r0;
   uint32_t t_wr2wr_gap_r0r3;
   uint32_t t_wr2wr_gap_r3r0;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL2_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL3_struct {
   uint32_t t_rd2rd_gap_r1r2;
   uint32_t t_rd2rd_gap_r2r1;
   uint32_t t_wr2rd_gap_r1r2;
   uint32_t t_wr2rd_gap_r2r1;
   uint32_t t_rd2wr_gap_r1r2;
   uint32_t t_rd2wr_gap_r2r1;
   uint32_t t_wr2wr_gap_r1r2;
   uint32_t t_wr2wr_gap_r2r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL3_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL4_struct {
   uint32_t t_rd2rd_gap_r1r3;
   uint32_t t_rd2rd_gap_r3r1;
   uint32_t t_wr2rd_gap_r1r3;
   uint32_t t_wr2rd_gap_r3r1;
   uint32_t t_rd2wr_gap_r1r3;
   uint32_t t_rd2wr_gap_r3r1;
   uint32_t t_wr2wr_gap_r1r3;
   uint32_t t_wr2wr_gap_r3r1;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL4_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL5_struct {
   uint32_t t_rd2rd_gap_r2r3;
   uint32_t t_rd2rd_gap_r3r2;
   uint32_t t_wr2rd_gap_r2r3;
   uint32_t t_wr2rd_gap_r3r2;
   uint32_t t_rd2wr_gap_r2r3;
   uint32_t t_rd2wr_gap_r3r2;
   uint32_t t_wr2wr_gap_r2r3;
   uint32_t t_wr2wr_gap_r3r2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANK_SWITCH_TIMING_CONTROL5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#endif //MEMC_DDR5
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH1_MRAMTMG0_struct {
   uint32_t t_ras_min_mram;
   uint32_t t_faw_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_MRAMTMG0_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH1_MRAMTMG1_struct {
   uint32_t t_rc_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_MRAMTMG1_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH1_MRAMTMG2_struct {
   uint32_t t_rp_mram;
   uint32_t t_rrd_mram;
   uint32_t t_rcd_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_MRAMTMG2_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
#ifdef UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH1_MRAMTMG3_struct {
   uint32_t t_rrd_s_mram;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_MRAMTMG3_struct_t;

#endif //UMCTL2_DDR4_MRAM_EN
typedef struct tag_REGB_FREQ3_CH1_INITMR0_struct {
   uint32_t emr;
   uint32_t mr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_INITMR0_struct_t;

typedef struct tag_REGB_FREQ3_CH1_INITMR1_struct {
   uint32_t emr3;
   uint32_t emr2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_INITMR1_struct_t;

typedef struct tag_REGB_FREQ3_CH1_INITMR2_struct {
   uint32_t mr5;
   uint32_t mr4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_INITMR2_struct_t;

typedef struct tag_REGB_FREQ3_CH1_INITMR3_struct {
   uint32_t mr6;
   uint32_t mr22;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_INITMR3_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DFITMG0_struct {
   uint32_t dfi_tphy_wrlat;
   uint32_t dfi_tphy_wrdata;
   uint32_t dfi_t_rddata_en;
   uint32_t dfi_t_ctrl_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DFITMG1_struct {
   uint32_t dfi_t_dram_clk_enable;
   uint32_t dfi_t_dram_clk_disable;
   uint32_t dfi_t_wrdata_delay;
   uint32_t dfi_t_parin_lat;
   uint32_t dfi_t_cmd_lat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG1_struct_t;

typedef struct tag_REGB_FREQ3_CH1_DFITMG2_struct {
   uint32_t dfi_tphy_wrcslat;
   uint32_t dfi_tphy_rdcslat;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG2_struct_t;

#ifdef DDRCTL_DDR
#ifndef MEMC_CMD_RTN2IDLE
typedef struct tag_REGB_FREQ3_CH1_DFITMG3_struct {
   uint32_t dfi_t_geardown_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG3_struct_t;

#endif //MEMC_CMD_RTN2IDLE
#endif //DDRCTL_DDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DFITMG4_struct {
   uint32_t dfi_twck_dis;
   uint32_t dfi_twck_en_fs;
   uint32_t dfi_twck_en_wr;
   uint32_t dfi_twck_en_rd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG4_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DFITMG5_struct {
   uint32_t dfi_twck_toggle_post;
   uint32_t dfi_twck_toggle_cs;
   uint32_t dfi_twck_toggle;
   uint32_t dfi_twck_fast_toggle;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG5_struct_t;

#endif //DDRCTL_LPDDR
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DFITMG7_struct {
   uint32_t dfi_t_2n_mode_delay;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFITMG7_struct_t;

#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_DFIUPDTMG1_struct {
   uint32_t dfi_t_ctrlupd_interval_max_x1024;
   uint32_t dfi_t_ctrlupd_interval_min_x1024;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DFIUPDTMG1_struct_t;

typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG0_struct {
   uint32_t t_refi_x1_x32;
   uint32_t refresh_to_x1_x32;
   uint32_t refresh_margin;
   uint32_t t_refi_x1_sel;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG1_struct {
   uint32_t t_rfc_min;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG1_struct_t;

#ifdef MEMC_LPDDR4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG2_struct {
   uint32_t t_rfc_min_dlr;
   uint32_t t_pbr2pbr;
   uint32_t t_pbr2act;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG2_struct_t;

#endif //MEMC_LPDDR4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG3_struct {
   uint32_t t_rfcsb;
   uint32_t t_refsbrd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG3_struct_t;

#endif //MEMC_DDR5
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG4_struct {
   uint32_t refresh_timer0_start_value_x32;
   uint32_t refresh_timer1_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG4_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
#ifdef MEMC_NUM_RANKS_GT_2
typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG5_struct {
   uint32_t refresh_timer2_start_value_x32;
   uint32_t refresh_timer3_start_value_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG5_struct_t;

#endif //MEMC_NUM_RANKS_GT_2
#ifdef MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG6_struct {
   uint32_t refresh_timer_lr_offset_x32;
   uint32_t refresh_timer_rank_offset_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG6_struct_t;

#endif //MEMC_NUM_RANKS_GT_4_OR_UMCTL2_CID_EN
#ifdef MEMC_DDR5
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG7_struct {
   uint32_t t_rfcsb_dlr;
   uint32_t t_refsbrd_dlr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG7_struct_t;

#endif //UMCTL2_CID_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HET_RANK_RFC
typedef struct tag_REGB_FREQ3_CH1_RFSHSET1TMG8_struct {
   uint32_t t_rfc_min_het;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET1TMG8_struct_t;

#endif //UMCTL2_HET_RANK_RFC
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_RFSHSET2TMG0_struct {
   uint32_t t_rfc_min_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH1_RFSHSET2TMG1_struct {
   uint32_t t_rfc_min_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET2TMG1_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_RFSHSET2TMG2_struct {
   uint32_t t_rfcsb_2;
   uint32_t t_refsbrd_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET2TMG2_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
#ifdef UMCTL2_CID_EN
typedef struct tag_REGB_FREQ3_CH1_RFSHSET2TMG3_struct {
   uint32_t t_rfcsb_dlr_2;
   uint32_t t_refsbrd_dlr_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RFSHSET2TMG3_struct_t;

#endif //UMCTL2_CID_EN
#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
typedef struct tag_REGB_FREQ3_CH1_ZQSET1TMG0_struct {
   uint32_t t_zq_long_nop;
   uint32_t t_zq_short_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_ZQSET1TMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH1_ZQSET1TMG1_struct {
   uint32_t t_zq_short_interval_x1024;
   uint32_t t_zq_reset_nop;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_ZQSET1TMG1_struct_t;

#ifdef MEMC_DDR5
#ifdef DDRCTL_TWO_TIMING_SETS_EN
typedef struct tag_REGB_FREQ3_CH1_ZQSET2TMG0_struct {
   uint32_t t_zq_long_nop_2;
   uint32_t t_zq_short_nop_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_ZQSET2TMG0_struct_t;

#endif //DDRCTL_TWO_TIMING_SETS_EN
#endif //MEMC_DDR5
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH1_RCDINIT1_struct {
   uint32_t ctrl_word_1;
   uint32_t ctrl_word_2;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RCDINIT1_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH1_RCDINIT2_struct {
   uint32_t ctrl_word_3;
   uint32_t ctrl_word_4;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RCDINIT2_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH1_RCDINIT3_struct {
   uint32_t ctrl_word_5;
   uint32_t ctrl_word_6;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RCDINIT3_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef UMCTL2_HWFFC_EN
#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH1_RCDINIT4_struct {
   uint32_t ctrl_word_7;
   uint32_t ctrl_word_8;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RCDINIT4_struct_t;

#endif //DDRCTL_DDR
#endif //UMCTL2_HWFFC_EN
#ifdef LPDDR45_DQSOSC_EN
typedef struct tag_REGB_FREQ3_CH1_DQSOSCCTL0_struct {
   uint32_t dqsosc_enable;
   uint32_t dqsosc_interval_unit;
   uint32_t dqsosc_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DQSOSCCTL0_struct_t;

#endif //LPDDR45_DQSOSC_EN
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DERATEINT_struct {
   uint32_t mr4_read_interval;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DERATEINT_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DERATEVAL0_struct {
   uint32_t derated_t_rrd;
   uint32_t derated_t_rp;
   uint32_t derated_t_ras_min;
   uint32_t derated_t_rcd;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DERATEVAL0_struct_t;

#endif //DDRCTL_LPDDR
#ifdef DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_DERATEVAL1_struct {
   uint32_t derated_t_rc;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_DERATEVAL1_struct_t;

#endif //DDRCTL_LPDDR
typedef struct tag_REGB_FREQ3_CH1_HWLPTMG0_struct {
   uint32_t hw_lp_idle_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_HWLPTMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH1_SCHEDTMG0_struct {
   uint32_t pageclose_timer;
   uint32_t rdwr_idle_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_SCHEDTMG0_struct_t;

typedef struct tag_REGB_FREQ3_CH1_PERFHPR1_struct {
   uint32_t hpr_max_starve;
   uint32_t hpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_PERFHPR1_struct_t;

typedef struct tag_REGB_FREQ3_CH1_PERFLPR1_struct {
   uint32_t lpr_max_starve;
   uint32_t lpr_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_PERFLPR1_struct_t;

typedef struct tag_REGB_FREQ3_CH1_PERFWR1_struct {
   uint32_t w_max_starve;
   uint32_t w_xact_run_length;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_PERFWR1_struct_t;

#ifdef UMCTL2_NUM_LRANKS_TOTAL_GT_1
typedef struct tag_REGB_FREQ3_CH1_RANKTMG0_struct {
   uint32_t diff_rank_rd_gap;
   uint32_t diff_rank_wr_gap;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANKTMG0_struct_t;

#endif //UMCTL2_NUM_LRANKS_TOTAL_GT_1
#ifdef MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ3_CH1_RANKTMG1_struct {
   uint32_t wr2rd_dr;
   uint32_t rd2wr_dr;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_RANKTMG1_struct_t;

#endif //MEMC_NUM_RANKS_GT_1
typedef struct tag_REGB_FREQ3_CH1_PWRTMG_struct {
   uint32_t powerdown_to_x32;
   uint32_t selfref_to_x32;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_PWRTMG_struct_t;

#ifdef DDRCTL_DDR
typedef struct tag_REGB_FREQ3_CH1_ODTCFG_struct {
   uint32_t rd_odt_delay;
   uint32_t rd_odt_hold;
   uint32_t wr_odt_delay;
   uint32_t wr_odt_hold;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_ODTCFG_struct_t;

#endif //DDRCTL_DDR
#ifdef UMCTL2_CRC_PARITY_RETRY
typedef struct tag_REGB_FREQ3_CH1_CRCPARTMG0_struct {
   uint32_t retry_fifo_max_hold_timer_x4;
   uint32_t t_crc_alert_pw_max;
   uint32_t t_par_alert_pw_max;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_CRCPARTMG0_struct_t;

#endif //UMCTL2_CRC_PARITY_RETRY
#ifdef DDRCTL_DDR_DUAL_CHANNEL
typedef struct tag_REGB_FREQ3_CH1_CRCPARTMG1_struct {
   uint32_t t_csalt;
  uint32_t value; // full 32-bit register value.
  } REGB_FREQ3_CH1_CRCPARTMG1_struct_t;

#endif //DDRCTL_DDR_DUAL_CHANNEL
#endif

