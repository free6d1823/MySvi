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


#ifndef __CINIT_CFG_H__
#define __CINIT_CFG_H__

/** @note this header will be converted to systemverilog for usage in
 * simulations. 
 * */

/**
 * @brief Type definition of structure describing attached memory type and topology
 *
 */
typedef struct tag_ddrSpdData_t {
  dwc_sdram_module_type sdram_module_type;
#ifdef MEMC_LPDDR4  
  dwc_lpddr4_data_rate_e lpddr4_data_rate;     //!< Max Data rate of attached LPDDR4 DRAM
  dwc_lpddr5_data_rate_e lpddr5_data_rate;     //!< Max Data rate of attached LPDDR5 DRAM
  dwc_lpddr5_wckck_ratio_e lpddr5_wckck_ratio; //!< Select 1:2 or 4:1 WCK:CK ratio
  dwc_lpddr5_bk_bg_org_e lpddr5_bk_bg_org;     //!< Bank/BankGroup Organization.
#endif
#ifdef MEMC_DDR4  
  dwc_ddr4_speed_grade_e ddr4_sg;
  dwc_ddr5_speed_grade_e ddr5_sg;
#endif
  dwc_sdram_protocol sdram_protocol;    //!< Basic memory type
  dwc_sdram_module_type  module_type;   //!< SDRAM Module type

  uint32_t tck_ps[UMCTL2_FREQUENCY_NUM];        //!< Operating clock period ps
  uint32_t num_ranks;             //!<Number of ranks
  uint32_t sdram_width_bits;      //!<SDRAM width (bits) [x4, x8, x16, x32]
  uint32_t module_width_bits;     //!<Module width (bits)
  uint32_t sdram_capacity_mbits;  //!<SDRAM capacity (megabits)
  uint8_t ecc_supported;          //!<ECC supported (0-not supported, 1-supported)
  uint8_t addr_mirror;            //!<Address mirroring support (0-not supported, 1-supported)
  uint8_t shared_ac;
  mramUseCase_e mram_use_case;    //!<SDRAM / MRAM combination for ranks
  uint32_t cid_width;             //Number of 3DS CIDs in use 1-2H 2-4H per phyisical rank

  //The following structure members are calculated for you in the subsys_SetSpd() function. No need to set them
  uint32_t dram_raw;          //!<Row address bits
  uint32_t dram_caw;          //!<Column address bits
  uint32_t dram_baw;          //!<Bank address bits
  uint32_t dram_bgw;          //!<Bank group address bits

  uint32_t mram_raw;          //!<Row address bits
  uint32_t mram_caw;          //!<Column address bits
  uint32_t mram_baw;          //!<Bank address bits
  uint32_t mram_bgw;          //!<Bank group address bits

  uint8_t  use_ti_rcd;
  uint8_t  num_rcds;                //!< Number of registered clock drivers (when using RDIMMs)
  uint8_t  num_ranks_per_dimm;      //!< 
  uint8_t  use_ddr4_tcwl_1st_set;   //!< When calculating cwl_x use the lower set of values for tcwl
  uint8_rnd_t  tAL;                 //!< Additive Latency can be 0, CL-1, CL-2
  uint8_t  tAL_RDBI;                //!< Read DBI Additive Latency 
  uint8_rnd_t  use_lpddr4x;         //!< The SDRAM is a variant of LPDDR4

} ddrSpdData_t;

/**
 * @brief Type definition of structure describing everything to
 * configure the memory controller.
 *
 */
  typedef struct tag_umctl2_t {
#ifdef MEMC_LPDDR4
    lpddr4_mode_registers_t lpddr4_mr[UMCTL2_FREQUENCY_NUM]; //!< variables that program LPDDR4 mode registers
    lpddr5_mode_registers_t lpddr5_mr[UMCTL2_FREQUENCY_NUM]; //!< variables that program LPDDR5 mode registers
#endif     
#ifdef MEMC_DDR4
    ddr4_mode_registers_t ddr4_mr[UMCTL2_FREQUENCY_NUM];     //!< variables that program DDR4 mode registers
    ddr5_mode_registers_t ddr5_mr[UMCTL2_FREQUENCY_NUM];     //!< variables that program DDR5 mode registers
#endif

    mctl_static_cfg_t static_cfg;  //!< variables that program static register fields
    mctl_qdyn_cfg_t qdyn_cfg;      //!< variables that are affect quasi-dynamic fields
    mctl_dyn_cfg_t dyn_cfg;        //!< variables that are affect dynamic fields
    mctl_regs_t  regs;             //!< A hierarchical struct of register programming intent after applying sdram options, static and qdyn configuration values.
    dwc_sdram_bus_width_e sdram_bus_width;
    mctl_pre_cfg pre_cfg; //!< A with some pre-calculations used in programming some register fields.
  } mctl_t;

/**
 * @brief Type definition of structure describing misc parameters to
 * configure the phyinit software.
 *
 */
  typedef struct tag_phy_timing_params_t {
    uint32_t pipe_dfi_wr;    //!<
    uint32_t pipe_dfi_rd;    //!<
    uint32_t pipe_dfi_misc;  //!< specifics the term MISC in calculation of tPHY_WRCSLAT and tPHY_RDCSLAT.
  } phy_timing_params_t;

 /** @brief This is the main structure for initializing the DDR Subsystem handler. This acts as a container for all the required structures.
  *
  */
  struct SubsysHdlr_priv {
    uint8_t logLevel_m;                                         //!< Current log verbosity level
    uint8_rnd_t  enable_non_jedec_tck;                          //!< Allow a out of range TCK value. The value spdData_m.tck_ps must be manually specified in this mode.
    uint8_rnd_t  use_snps_vip_timing;                           //!< Adjust timings for Synopsys VIP
    uint8_rnd_t  use_jedec_init;                                //!< Use JEDEC timings for initialization.
    uint8_rnd_t  num_pstates;                                   //!< Number of frequencies to setup 
    uint8_rnd_t  num_amap;                                      //!< Number of address maps 
    uint8_rnd_t  num_dch;                                       //!< Number of data channels to setup 
     
    ddrSpdData_t  spdData_m;                                    //!< The SDRAM memory descriptor.
#ifdef MEMC_DDR5
    ddr5_control_words_t  ddr5_cw;                              //!< variables that program DDR5 RCD Control Words 
#endif

// Bug7444 Single element arrays are treated differently between C and simulator
    ddrTimingParameters_t timingParams_m[UMCTL2_FREQUENCY_NUM+1]; //!< timing parameters
    mctl_t  memCtrlr_m;                                           //!< Structures to configure umctl register field values.
    uint32_t mCtrlBaseAddr_m;                                     //!< Memory controller base address
    // PHY options
    phy_timing_params_t phy_timing_params;                        //!< PHY specific timing parameters.
    uint32_rnd_t num_anibs;                                       //!< Number of PHY address nibbles
    uint8_rnd_t  lpddr4_pop_support;
    uint8_rnd_t  lpddr4_first_boot;
    uint8_rnd_t  lpddr4_bootclk_en;
    // HdtCtrl
    //    0x05 = Detailed debug messages (e.g. Eye delays)
    //    0x0A = Coarse debug messages (e.g. rank information)
    //    0xC8 = Stage completion
    //    0xC9 = Assertion messages
    //    0xFF = Firmware completion messages only     
    uint8_rnd_t  HdtCtrl;            //!< Used in setting up PUB message block (Hardware Debug Trace Control)
    ddrPhyType_e ddrPhyType_m;       //!< PHY type
    uint32_t phyBaseAddr_m;          //!< PHY utility block (PUB) base address
    uint32_rnd_t mr7_by_phy;
    uint32_t mr0_pdx_time;
    uint32_rnd_t phy_training;       //!<  0 - full training, 1 - skip training, 2 - dev_inti 
    uint32_t dwc_pub_rid;
    // Some control on behaviour of CINIT library
    uint8_t is_constraint_assert_set;             //!< enable inline checking of controller register values.
    uint8_t is_timing_set[UMCTL2_FREQUENCY_NUM];  //!< The JEDEC timings have been calculated.
    uint8_t is_tck_set[UMCTL2_FREQUENCY_NUM];     //!< The operational clk frequency has been set.

    void *phy_config; //!< A pointer to PHYINT meta structure that holds other PHYINT structures 

  }; // fwd SubsysHdlr_t
  // NB the above comment is used by c_to_sv.pl, do not remove it.
#endif // __CINIT_CFG_H__
