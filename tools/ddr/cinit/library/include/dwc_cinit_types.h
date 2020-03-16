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

#ifndef __CINIT_TYPES_H__
#define __CINIT_TYPES_H__
#ifdef  __cplusplus
extern "C" {
#endif
  /*************************************************************************
   * T Y P E D E F S    &    D E F I N E S
   *************************************************************************/



/************************************************************************/

  // The following types are sensitive to the encoding defined in CC constants
  //
  //
  /*! \enum dwc_lpddr4_data_rate_e
   * Encodeing LPDDR4 SDRAM speed options in Mbps.
   * The encoding must match the encoding in the cc_constants file
   */
  typedef enum tag_dwc_lpddr4_data_rate_e {
    DWC_LPDDR4_533=1,
    DWC_LPDDR4_1066,
    DWC_LPDDR4_1600,
    DWC_LPDDR4_2133,
    DWC_LPDDR4_2667,
    DWC_LPDDR4_3200,
    DWC_LPDDR4_3733,
    DWC_LPDDR4_4267
  } dwc_lpddr4_data_rate_e;


  /*! \enum dwc_lpddr5_data_rate_e
   * Encoding of LPDDR5 data rates.
   */
  typedef enum tag_dwc_lpddr5_data_rate_e {
    DWC_LPDDR5_533=1,
    DWC_LPDDR5_1066,
    DWC_LPDDR5_1600,
    DWC_LPDDR5_2133,
    DWC_LPDDR5_2710, // 2750
    DWC_LPDDR5_3200,
    DWC_LPDDR5_3733,
    DWC_LPDDR5_4266, // 4267
    DWC_LPDDR5_4800,
    DWC_LPDDR5_5420, // 5500
    DWC_LPDDR5_6000,
    DWC_LPDDR5_6400
  } dwc_lpddr5_data_rate_e;

  /*! \enum dwc_lpddr5_wckck_ratio_e
   * Encoding of LPDDR5 WCK to CK ratio.
   */
  typedef enum tag_dwc_lpddr5_wckck_ratio_e {
    DWC_WCKCK_2_1=1,
    DWC_WCKCK_4_1
  } dwc_lpddr5_wckck_ratio_e;

  /*! \enum dwc_lpddr5_bk_bg_org_e
   * Encoding of LPDDDR5 back organization.
   */
  typedef enum tag_dwc_lpddr5_bk_bg_org_e {
    DWC_LPDDR5_4BK_4BG=0,
    DWC_LPDDR5_8BK,
    DWC_LPDDR5_16BK
  } dwc_lpddr5_bk_bg_org_e;

  typedef enum tag_dwc_ddr4_speed_grade_e {
        DWC_DDR4_1600J=1,
        DWC_DDR4_1600K,
        DWC_DDR4_1600L,
        DWC_DDR4_1866L,
        DWC_DDR4_1866M,
        DWC_DDR4_1866N,
        DWC_DDR4_2133N,
        DWC_DDR4_2133P,
        DWC_DDR4_2133R,
        DWC_DDR4_2400P,
        DWC_DDR4_2400R,
        DWC_DDR4_2400T,
        DWC_DDR4_2400U,
        DWC_DDR4_2666T,
        DWC_DDR4_2666U,
        DWC_DDR4_2666V,
        DWC_DDR4_2666W,
        DWC_DDR4_2933V,
        DWC_DDR4_2933W,
        DWC_DDR4_2933Y,
        DWC_DDR4_2933AA,
        DWC_DDR4_3200W,
        DWC_DDR4_3200AA,
        DWC_DDR4_3200AC,
        DWC_DDR4_1600J_3DS2B,
        DWC_DDR4_1600K_3DS2B,
        DWC_DDR4_1600L_3DS2B,
        DWC_DDR4_1866L_3DS2B,
        DWC_DDR4_1866M_3DS2B,
        DWC_DDR4_1866N_3DS2B,
        DWC_DDR4_2133P_3DS2A,
        DWC_DDR4_2133P_3DS3A,
        DWC_DDR4_2133R_3DS4A,
        DWC_DDR4_2400P_3DS3B,
        DWC_DDR4_2400T_3DS2A,
        DWC_DDR4_2400U_3DS2A,
        DWC_DDR4_2400U_3DS4A,
        DWC_DDR4_2666T_3DS3A,
        DWC_DDR4_2666V_3DS3A,
        DWC_DDR4_2666W_3DS4A,
        DWC_DDR4_3200W_3DS4A,
        DWC_DDR4_3200AA_3DS4A,
        DWC_DDR4_3200AC_3DS4A
  } dwc_ddr4_speed_grade_e;

  typedef enum tag_dwc_ddr5_speed_grade_e {
    DWC_DDR5_3200A=1,
    DWC_DDR5_3200B,
    DWC_DDR5_3200C,
    DWC_DDR5_3600A,
    DWC_DDR5_3600B,
    DWC_DDR5_3600C,
    DWC_DDR5_4000A,
    DWC_DDR5_4000B,
    DWC_DDR5_4000C,
    DWC_DDR5_4400A,
    DWC_DDR5_4400B,
    DWC_DDR5_4400C,
    DWC_DDR5_4800A,
    DWC_DDR5_4800B,
    DWC_DDR5_4800C,
    DWC_DDR5_5200A,
    DWC_DDR5_5200B,
    DWC_DDR5_5200C,
    DWC_DDR5_5600A,
    DWC_DDR5_5600B,
    DWC_DDR5_5600C,
    DWC_DDR5_6000A,
    DWC_DDR5_6000B,
    DWC_DDR5_6000C,
    DWC_DDR5_6400A,
    DWC_DDR5_6400B,
    DWC_DDR5_6400C,
    DWC_DDR5_3200A_3DS,
    DWC_DDR5_3200B_3DS,
    DWC_DDR5_3200C_3DS,
    DWC_DDR5_3600A_3DS,
    DWC_DDR5_3600B_3DS,
    DWC_DDR5_3600C_3DS,
    DWC_DDR5_4000A_3DS,
    DWC_DDR5_4000B_3DS,
    DWC_DDR5_4000C_3DS,
    DWC_DDR5_4400A_3DS,
    DWC_DDR5_4400B_3DS,
    DWC_DDR5_4400C_3DS,
    DWC_DDR5_4800A_3DS,
    DWC_DDR5_4800B_3DS,
    DWC_DDR5_4800C_3DS
  } dwc_ddr5_speed_grade_e;

  /*! \enum en_lpddr4_device
   * Encoding LPDDR4 SDRAM options.
   * The encoding must match the encoding in the cc_constants file
   */
  typedef enum tag_dwc_lpddr4_device_type_e {
   // DWC_LPDDR4_1GB_8MB_16DQ_8BK_PER_CHANNEL=1,
    DWC_LPDDR4_2GB_16MB_16DQ_8BK_PER_CHANNEL=1,
    DWC_LPDDR4_3GB_24MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_4GB_32MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_6GB_48MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_8GB_64MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_12GB_96MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_16GB_128MB_16DQ_8BK_PER_CHANNEL,
    //DWC_LPDDR4_1GB_16MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_2GB_32MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_3GB_48MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_4GB_64MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_6GB_96MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_8GB_128MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_12GB_192MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR4_16GB_256MB_8DQ_8BK_PER_CHANNEL
  } dwc_lpddr4_device_type_e;

  /*! \enum dwc_lpddr5_device_type_e
   * Encoding LPDDR5 SDRAM address options.
   * The bank organization is encoded in this enum also.
   * NB The encoding must match the encoding in the Simulate Activity file
   */
  typedef enum tag_dwc_lpddr5_device_type_e {
    // x16,4 Banks/4 Bank Groups
    DWC_LPDDR5_2GB_8MB_16DQ_4BK_4BG_PER_CHANNEL=1,
    DWC_LPDDR5_3GB_12MB_16DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_4GB_16MB_16DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_6GB_24MB_16DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_8GB_32MB_16DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_12GB_48MB_16DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_16GB_64MB_16DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_24GB_96MB_16DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_32GB_128MB_16DQ_4BK_4BG_PER_CHANNEL,
    //
    // byte-mode(x8), 4 Banks/4 Bank Groups
    DWC_LPDDR5_2GB_16MB_8DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_3GB_24MB_8DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_4GB_32MB_8DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_6GB_48MB_8DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_8GB_64MB_8DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_12GB_96MB_8DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_16GB_128MB_8DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_24GB_192MB_8DQ_4BK_4BG_PER_CHANNEL,
    DWC_LPDDR5_32GB_256MB_8DQ_4BK_4BG_PER_CHANNEL,

    // x16, 16 banks mode
    DWC_LPDDR5_2GB_8MB_16DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_3GB_12MB_16DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_4GB_16MB_16DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_6GB_24MB_16DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_8GB_32MB_16DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_12GB_48MB_16DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_16GB_64MB_16DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_24GB_96MB_16DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_32GB_128MB_16DQ_16BK_PER_CHANNEL,

    // byte-mode(x8), 16 banks mode
    DWC_LPDDR5_2GB_16MB_8DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_3GB_24MB_8DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_4GB_32MB_8DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_6GB_48MB_8DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_8GB_64MB_8DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_12GB_96MB_8DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_16GB_128MB_8DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_24GB_192MB_8DQ_16BK_PER_CHANNEL,
    DWC_LPDDR5_32GB_256MB_8DQ_16BK_PER_CHANNEL,

    // x16, 8 Banks mode
    DWC_LPDDR5_2GB_16MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_3GB_24MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_4GB_32MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_6GB_48MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_8GB_64MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_12GB_96MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_16GB_128MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_24GB_192MB_16DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_32GB_256MB_16DQ_8BK_PER_CHANNEL,

    // x8, 8 Banks mode
    DWC_LPDDR5_2GB_32MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_3GB_48MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_4GB_64MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_6GB_96MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_8GB_128MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_12GB_192MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_16GB_256MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_24GB_384MB_8DQ_8BK_PER_CHANNEL,
    DWC_LPDDR5_32GB_512MB_8DQ_8BK_PER_CHANNEL

  } dwc_lpddr5_device_type_e;

  typedef enum tag_dwc_ddr4_device_type_e {
    // 2 Gb
    DWC_DDR4_2GB_X_4DQ=1,
    DWC_DDR4_2GB_X_8DQ,
    DWC_DDR4_2GB_X_16DQ,
    // 4 Gb
    DWC_DDR4_4GB_X_4DQ,
    DWC_DDR4_4GB_X_8DQ,
    DWC_DDR4_4GB_X_16DQ,
    // 8 Gb
    DWC_DDR4_8GB_X_4DQ,
    DWC_DDR4_8GB_X_8DQ,
    DWC_DDR4_8GB_X_16DQ,
    // 16 Gb
    DWC_DDR4_16GB_X_4DQ,
    DWC_DDR4_16GB_X_8DQ,
    DWC_DDR4_16GB_X_16DQ
  } dwc_ddr4_device_type_e;

  typedef enum tag_dwc_ddr5_device_type_e {

    //8 Gb
    DWC_DDR5_8GB_X_4DQ=1,
    DWC_DDR5_8GB_X_8DQ,
    DWC_DDR5_8GB_X_16DQ,
    //16 Gb
    DWC_DDR5_16GB_X_4DQ,
    DWC_DDR5_16GB_X_8DQ,
    DWC_DDR5_16GB_X_16DQ,
    //24 Gb
    DWC_DDR5_24GB_X_4DQ,
    DWC_DDR5_24GB_X_8DQ,
    DWC_DDR5_24GB_X_16DQ,
    //32 Gb
    DWC_DDR5_32GB_X_4DQ,
    DWC_DDR5_32GB_X_8DQ,
    DWC_DDR5_32GB_X_16DQ,
    //64Gb
    DWC_DDR5_64GB_X_4DQ,
    DWC_DDR5_64GB_X_8DQ,
    DWC_DDR5_64GB_X_16DQ
  } dwc_ddr5_device_type_e;

  // TODO DELETE ME, not relevant to CINIT
  typedef enum tag_dwc_lpddr4_chan_mode_e {
    DWC_LOCK_STEP=1,
    DWC_SERIAL,
    DWC_MULTI_CHAN,
    DWC_MULTI_CHAN_SHARED_AC
  } dwc_lpddr4_chan_mode_e;



  typedef enum tag_dwc_sdram_module_type {
    DWC_NODIMM=1,
    DWC_RDIMM,
    DWC_LRDIMM,
    DWC_UDIMM
  } dwc_sdram_module_type;

  typedef enum tag_dwc_dram_density_e {
    DWC_DEN64M,                     // 64Mb
    DWC_DEN128M,                    // 128Mb
    DWC_DEN256M,                    // 256Mb
    DWC_DEN512M,                    // 512Mb
    DWC_DEN1G,                      // 1Gb
    DWC_DEN2G,                      // 2Gb
    DWC_DEN3G,                      // 3Gb
    DWC_DEN4G,                      // 4Gb
    DWC_DEN6G,                      // 6Gb
    DWC_DEN8G,                      // 8Gb
    DWC_DEN12G,                     // 12Gb
    DWC_DEN16G,                     // 16Gb
    DWC_DEN24G,                     // 24Gb
    DWC_DEN32G,                      // 32Gb
    DWC_DEN64G                      // 64Gb
  } dwc_dram_density_e;
  /**
   * @brief Enumerated type listing possible SDRAM types supported
   */
  typedef enum tag_dwc_sdram_protocol {
    DWC_DDR4  ,        //!<DDR4 SDRAM
    DWC_DDR5  ,        //!<DDR5 SDRAM
    DWC_LPDDR4,        //!<LPDDR4 SDRAM
    DWC_LPDDR5         //!<LPDDR5 SDRAM
  } dwc_sdram_protocol;

  /**
    * @brief Enumerated type listing the sdram bus width bus width
    */
  typedef enum tag_dwc_sdram_bus_width_e {
    DWC_BUSWIDTH_FULL = 1,    //!< Full bus width
    DWC_BUSWIDTH_HALF = 2,    //!< Half bus width
    DWC_BUSWIDTH_QUARTER = 3  //!< Quarter bus width
  } dwc_sdram_bus_width_e;

/************************************************************************/


        /**
  * @brief Enum type for PHY types
  */
       typedef enum tag_ddrPhyType_e {
    DWC_DDR54_PHY = 1,
    DWC_LPDDR54_PHY = 2,
    DWC_DDR43_PHY = 3,
    DWC_LPDDR4X_MULTIPHY = 4
  } ddrPhyType_e;


        typedef enum tag_speed_index_e {
            SLOW,
            TYP,
            FAST
        } speed_index_e;



  /**
   * @brief Enumerated type listing SDRAM/MRAM rank structures
   */
  typedef enum tag_mramUseCase_e {
    MRAM_UC_NONE = 0, //All ranks are SDRAM
    MRAM_UC_ALL,    //All ranks are MRAM
    MRAM_UC_MIXED   //SDRAM MRAM 50:50 split (lower ranks are SDRAM)
  } mramUseCase_e;

  /**
    * @brief Enumerated type listing bus width
    */
  typedef enum tag_ddrBusWidth_e {
    DDR_BUSWIDTH_FULL = 1,    //!< Full bus width
    DDR_BUSWIDTH_HALF = 2,    //!< Half bus width
    DDR_BUSWIDTH_QUARTER = 4, //!< Quarter bus width
    DDR_BUSWIDTH_MAX      //!< internal Not used
  } ddrBusWidth_e;


  typedef enum tag_dram_density_e {
    DEN128MB,
    DEN256MB,
    DEN512MB,
    DEN1024MB,
    DEN2048MB,
    DEN4096MB,
    DEN8192MB,
    DEN12288MB,
    DEN16384MB
  } dram_density_e;

  /**
    * @brief Structure containing DDR timing parameters.
          * @note the timing parameters are from JEDEC spec.
    */
  typedef struct tag_ddrTimingParameters_t {
    //DRAM Timing Parameters
    uint32_t sg_tck_ps;   //!< Minimum Clock Cycle Time
    uint32_t trc_ps;    //!< Active to Active/Auto Refresh command time
    uint32_t trcd_ps;   //!< Active to Read/Write command time
    uint32_t trp_ps;    //!< Precharge command period
    uint32_t trpa_ps;   //!< ???
    uint32_t trrd_l_tck;  //!< Active bank a to Active bank b command time to same bank group
    uint32_t trrd_s_tck;  //!< Active bank a to Active bank b command time to different bank group
    uint32_t trrd_ps;   //!< Active bank a to Active bank b command time
#ifdef MEMC_DDR4
    //DDR4 Timing Parameters
    uint32_t ddr4_txp_ps;           //!< Exit power down to a valid command
    uint32_t ddr4_txpdll_ps;        //!< Exit precharge power down to READ or WRITE command (DLL-off mode)
    uint32_t ddr4_txsdll_tck;       //!< SelfRefresh to commands requiring a locked DLL
    uint32_t ddr4_tras_min_ps;      //!< Minimum Active to Precharge command time
    uint32_t ddr4_tras_max_ps;      //!< Maximum Active to Precharge command time
    uint32_t ddr4_trefi_ps;         //!< ???
    uint32_t ddr4_trfc_min_ps;      //!< Refresh to Refresh Command interval minimum value
    uint32_t ddr4_trfc_min2_ps;     //!< Refresh to Refresh Command interval minimum value
    uint32_t ddr4_trfc_min4_ps;     //!< Refresh to Refresh Command interval minimum value
    uint32_t ddr4_trfc_max_ps;      //!< Refresh to Refresh Command Interval maximum value
    uint32_t ddr4_twtr_l_tck;       //!< Write to Read command delay in clocks (sometimes higher than twtr/tck)
    uint32_t ddr4_twtr_s_tck;       //!< Write to Read command delay in clocks (sometimes higher than twtr/tck)
    uint32_t ddr4_tfaw_ps;          //!< Four Bank Activate window
    uint32_t ddr4_tzqinit_tck;      //!< ZQ Cal (Init) time
    uint32_t ddr4_tzqoper_tck;      //!< ZQ Cal (Long) time
    uint32_t ddr4_tzqcs_tck;        //!< ZQ Cal (Short) time
    uint32_t ddr4_tmrd_tck;         //!< Load Mode Register command cycle time
    uint32_t ddr4_tcke_ps;          //!< CKE minimum high or low pulse width
    uint32_t ddr4_tccd_l_tck;       //!< Cas to Cas command delay to same bank group
    uint32_t ddr4_tccd_s_tck;       //!< Cas to Cas command delay to different bank group
    uint32_t ddr4_tmod_ps;          //!< LOAD MODE to non-LOAD MODE command cycle time
    uint32_t ddr4_trtp_ps;          //!< Read to Precharge command delay
    uint32_t ddr4_twr_ps;           //!< Write recovery time
    uint32_t ddr4_tckmpe_ps;        //!< Valid clock requirement after MPSM entry
    uint32_t ddr4_tmpx_s_tck;       //!< CS setup time to CKE
    uint32_t ddr4_tmpx_lh_ps;       //!< CS_n Low hold time to CKE rising edge
    uint32_t ddr4_tpl_tck;          //!< C/A parity latency
    uint32_t ddr4_wcl_tck;          //!< Write Command Latency
    uint32_t ddr4_twr_crc_dm_tck;   //!< Write recovery time when CRC and DM are enabled (tWR_CRC_DM = twr + twr_crc_dm)
    uint32_t ddr4_twtr_l_crc_dm_tck;//!< tWTR_L's additional delay when CRC and DM are enabled (tWTR_L_CRC_DM = twtr_l_tck + twtr_l_crc_dm)
    uint32_t ddr4_twtr_s_crc_dm_tck;//!< tWTR_S's additional delay when CRC and DM are enabled (tWTR_S_CRC_DM = twtr_s_tck + twtr_s_crc_dm)
    uint32_t ddr4_tcrc_alert_pw_tck;//!< CRC ALERT_n pulse width (Max)
    uint32_t ddr4_tcrc_alert_ps;    //!< CRC error to ALERT_n pulse width
    uint32_t ddr4_tpar_alert_pw_tck;//!< Pulse width of ALERT_N signal when C/A Parity Error is detected (Max)
    uint32_t ddr4_tpar_unknown_ps;  //!< Commands not guaranteed to be executed during this time
    uint32_t ddr4_tpar_alert_on_ps; //!< Delay from errant command to ALERT_n assertion
    uint32_t ddr4_cal_tck;          //!< CS to Command Address Latency when cal mode is enabled (and not in geardown mode)
    uint32_t ddr4_tdqsck_dll_off_ps;//!< Read data Clock to Data Strobe relationship with DLL-off mode
    uint32_t ddr4_tstab_ps;         //!< ddr4 Stabilization time
    uint32_t ddr4_trfc_dlr_ps;      //!< Refresh to Refresh Command to different logical rank
    uint32_t ddr4_trfc_dlr2_ps;     //!< Refresh to Refresh Command to different logical rank
    uint32_t ddr4_trfc_dlr4_ps;     //!< Refresh to Refresh Command to different logical rank
    uint32_t ddr4_trrd_dlr_tck;     //!< Active bank a to Active bank b command time to different logical rank
    uint32_t ddr4_tfaw_dlr_tck;     //!< Four Bank Activate window to different logical rank
    uint32_t ddr4_tccd_dlr_tck;     //!< Cas to Cas command delay to different logical rank

    //uint32_t busWidthFractionDenominator;
    //uint32_t mr0WrRecovery;
    uint32_t mr1Rtt;
    uint32_t mr2AutoSelfRef;
    uint32_t mr4Refresh;
    uint32_t eccEncoding;
    uint32_t eccMode; //!< Also in spd_data
    uint32_t dllOffInit;

    uint32_t ddr4_tcwl_1st_set_tck;
    uint32_t ddr4_tcwl_2nd_set_tck;
    uint32_t ddr4_tcl_tck;
    uint32_t ddr4_tcmd_gear_tck;
    uint32_t ddr4_tsync_gear_tck;
    uint32_t ddr4_tgear_hold_tck;
    uint32_t ddr4_tgear_setup_tck;
    uint32_t ddr4_rankMap4;
    uint32_t ddr4_rankMap2;
    uint32_t ddr4_rankMap2i;
    uint32_t ddr4_tcl_rdbi_tck;

    //ddr5 timing parameters
    uint32_t ddr5_tcwl_tck;
    uint32_t ddr5_tcl_tck;
    uint32_t ddr5_tcl_rdbi_tck;


    uint32_t ddr5_tras_min_ps;    //!< minimum ACT to PRE command period
    uint32_t ddr5_tras_max_ps;    //!< minimum ACT to PRE command period
    uint32_t ddr5_tccd_l_tck;     //!< minimum CAS_n to CAS_n command delay for same bank group
    uint32_t ddr5_tccd_l_wr_tck;  //!< minimum Write CAS_n to CAS_n command delay for same bank group BL32 OTF
    uint32_t ddr5_tccd_s_tck;     //!< minimum CAS_n to CAS_n command delay for different bank group for BL16, and BC8(on-the-fly)
    uint32_t ddr5_tccd_l_wr_ps;   //!<write to write same bank group second write RMW
    uint32_t ddr5_tccd_l_wr2_ps;  //!<write to write same bank group second write not RMW

	  uint32_t ddr5_tfaw_2k_tck;   //!< minimum Four activate window for 2KB page size  // TODO summary to ddr5_tfaw_ps
	  uint32_t ddr5_tfaw_1k_tck;   //!< minimum Four activate window for 1KB page size  // TODO summary to ddr5_tfaw_ps
	  uint32_t ddr5_tfaw_512_tck;   //!< minimum Four activate window for 512B page size  // TODO summary to ddr5_tfaw_ps
	  uint32_t ddr5_tfaw_tck;   //!< minimum Four activate window 
	  uint32_t ddr5_twtr_l_tck; //!< minimum Delay from start of internal write transaction to internal read command for different bank group 
    uint32_t ddr5_tfaw_dlr_tck; //!<Four activate window to the different logical rank
    uint32_t ddr5_tfaw_slr_tck; //!<Four activate window to the same logical rank
	  uint32_t ddr5_twtr_s_tck; //!< minimum Delay from start of internal write transaction to internal read command for the same bank group 
	  uint32_t ddr5_trtp_ps;   //!< minimum Internal READ Command to PRECHARGE Command delay 
	  uint32_t ddr5_tppd_tck;   //!< minimum PRECHARGE (PRE) to PRECHARGE (PRE) delay , // TODO need to add it to VIP
	  uint32_t ddr5_twr_ps;    //!< minimum WRITE recovery time

    //mode register read/write AC timing
    uint32_t ddr5_tmrr_tck;   //!<minimum Mode Register Read command period
    uint32_t ddr5_tmrr_p_tck; //!<minimum Mode Register Read Pattern to Mode Register Read Pattern command spacing
    uint32_t ddr5_tmrw_tck;   //!< minimum Mode Register Write command period
    uint32_t ddr5_tmrd_tck;   //!< minimum Mode Register Set command delay

    //refresh timing parameter
    uint32_t ddr5_trefi1_ps;
    uint32_t ddr5_trefi2_ps;
    uint32_t ddr5_trfc1_ps;  //!<minimum Normal Refresh (REFab)
    uint32_t ddr5_trfc2_ps;  //!<minimum FGR Refresh (REFab)
    uint32_t ddr5_trfcsb_ps; //!<minimum Same Bank Refresh (REFab)

          //3ds refresh timing parameter
	  uint32_t ddr5_trefsbrd_ps;   //!<minimum Same Bank Refresh to ACT delay    

	  uint32_t ddr5_trfc1_dlr_ps; //!< minimum Normal Refresh with 3DS different logical rank 
	  uint32_t ddr5_trfc2_dlr_ps; //!<minimum Fine Granularity Refresh with 3DS different logical rank 
	  uint32_t ddr5_trfcsb_dlr_ps; //!<minimum Same Bank Refresh with 3DS different logical rank 
	  uint32_t ddr5_trefsbrd_dlr_ps;   //!<minimum 3ds Same Bank Refresh to ACT delay    
    uint32_t ddr5_trrd_dlr_tck;  //!<minimum 3ds ACTIVATE to ACTIVATE Command delay to different logical rank

	  // ZQ calibration timing parameters
	  uint32_t ddr5_tzqcal_ps; //!< minimum ZQ calibration timie
	  uint32_t ddr5_tzqlat_ps; //!< minimum ZQ calibration latch timie

	  //self refresh Timing parameters
	  /* uint32_t ddr5_tcpded_ps; //!< minimum Command pass disable delay */
	  uint32_t ddr5_tcsl_ps;   //!< minimum Self-Refresh CS_n low Pulse width
	  uint32_t ddr5_tcsh_srexit_ps; //!< minimum Self-Refresh exit CS_n High Pulse width
	  uint32_t ddr5_tcsl_srexit_tck;//!< minimum Self-Refresh exit CS_n Low Pulse width
	  uint32_t ddr5_tcksrx_ps;      //!< minimum Valid Clock Requirement before SRX
	  uint32_t ddr5_tcklcs_tck;     //!< minimum Valid Clock Requirement after SRE
	  uint32_t ddr5_tcasrx_ps;      //!< minimum Self-Refresh exit CS_n high
	  uint32_t ddr5_txs_ps;         //!< minimum Exit Self-Refresh to next valid command not requireing DLL
	  uint32_t ddr5_txs_dll_ps;     //!< minimum Exit Self-Refresh to next valid command needing a DLL TBD

	  // PDA timings parameters
          uint32_t ddr5_tpda_latch_min_ps;
	  uint32_t ddr5_tpda_delay_ps;  //!< minimum PDA Enumerate ID Command to any other command cycle time
	  uint32_t ddr5_tpda_dqs_delay_min_ps; //!< minimum Delay to rising strobe edge used for sampling DQ during PDA operation
	  uint32_t ddr5_tpda_dqs_delay_max_ps; //!< maximum Delay to rising strobe edge used for sampling DQ during PDA operation
	  uint32_t ddr5_tpda_s_tck;            //!< minimum DQ Setup Time during PDA operation
	  uint32_t ddr5_tpda_h_tck;            //!< minimum DQ Hold Time during PDA operation

	  //MPC command timings parameters
	  uint32_t ddr5_tmpc_delay_tck;   //!< minimum MPC to any other valid command delay
	  uint32_t ddr5_tmc_mpc_setup_tck;  //!<minimum time between stable MPC command and first falling CS edge (SETUP)
	  uint32_t ddr5_tmc_mpc_hold_tck;   //!<minimum time between first rising CS edge and stable MPC command (HOLD)
	  uint32_t ddr5_tmpc_cs_min_tck;    //!< minimum Time CS_n is held low to register MPC command
	  uint32_t ddr5_tmpc_cs_max_tck;    //!< maximum Time CS_n is held low to register MPC command

          // MPSM command timings parameters 
	  uint32_t ddr5_tmpsmx_ps;  //!< minimum MPSM exit to first valid command delay
	  uint32_t ddr5_tmpdpdact_ps; //!< minimum MPSM DPD exit to first ACT command delay

	  // Power down timing parameters;
	  uint32_t ddr5_tcpded_ps;    //!< minimum Command pass disable delay
          uint32_t ddr5_tpd_ps;       //!< Minimum Power Down Time
	  uint32_t ddr5_txp_ps;       //!< minimum Exit Power Down to next valid command
	  uint32_t ddr5_tactpden_tck; //!<minimum Timing of ACT command to Power Down Entry command
	  uint32_t ddr5_tprpden_tck;  //!<minimum Timing of PREab, PREsb or PREpb to Power Down Entry command
	  uint32_t ddr5_trdpden_tck;  //!<minimum Timing of RD or RD w/AP to Power Down Entry command
	  uint32_t ddr5_twrpden_tck;  //!<minimum Timing of WR to Power Down Entry command
	  uint32_t ddr5_twrapden_tck; //!<minimum Timing of WR w/AP to Power Down Entry command
	  uint32_t ddr5_trefpden_tck; //!<minimum Timing of REFab or REFsb command to Power Down Entry command
	  uint32_t ddr5_tmrrpden_tck; //!<minimum Timing of MRR to command to Power Down Entry command
	  uint32_t ddr5_tmrwpden_tck; //!<minimum Timing of MRW command to Power Down Entry command
	  uint32_t ddr5_tmpcpden_tck; //!<minimum Timing of MPC command to Power Down Entry command

	  //Initialization Timing parameters
	  uint32_t ddr5_tinit4_ps;    //!< minimum time for DRAM to register EXIT on CS with CMOS
	  uint32_t ddr5_tinit5_tck;   //!< minimum cycles required after CS_n HIGH
	  uint32_t ddr5_txpr_ps;      //!< minimum time from Exit Reset to first valid Configuration Command

	  //VrefCA command Timing parameters
	  uint32_t ddr5_tvrefca_delay_tck;  //!< minimum VrefCA command to any other valid command delay
	  uint32_t ddr5_tvrefca_cs_min_tck;     //!< minimum Time CS_n is held low to register VrefCA command
	  uint32_t ddr5_tvrefca_cs_max_tck;     //!< maximum Time CS_n is held low to register VrefCA command

	  //DQS interval OSCilator Read out Timing parameters
	  uint32_t ddr5_tosco_ps;  //!< minimum Delay time from OSC stop to Mode Register Readout

	  //CRC Error handling Timing parameters 
	  uint32_t ddr5_tcrc_alert_ps;     //!<CRC Alert Delay Time
	  uint32_t ddr5_tcrc_alert_pw_ps;  //!<CRC Alert Pulse Width

    // RCD timing parameters
    // For PHYINIT
    uint32_t ddr5_rcd_tstaoff_ps;
    uint32_t ddr5_rcd_tpdm_ps;
    // For Controller
    uint32_t ddr5_rcd_tstab01_ps;
    uint32_t ddr5_rcd_tpdex_ps;
    uint32_t ddr5_rcd_tcssr_ps;
    uint32_t ddr5_rcd_tcpded2srx_tck;
    uint32_t ddr5_rcd_tsrx2srx_tck;
    uint32_t ddr5_rcd_tckoff_ps;
    uint32_t ddr5_rcd_tckact_tck;
    uint32_t ddr5_rcd_tcsalt_tck;
#endif

#ifdef MEMC_LPDDR4
    // LPDDR4 Timing Parameters
    uint32_t lpddr4_tckb;     //!< Clock cycle time during boot
    uint32_t lpddr4_tpbr2pbr; //!< Per-bank refresh to Per-bank refresh different bank time
    uint32_t lpddr4_tras_min;
    uint32_t lpddr4_tras_max;
    uint32_t lpddr4_trfcab;
    uint32_t lpddr4_trfcpb;
    uint32_t lpddr4_trfiab;
    uint32_t lpddr4_trfipb;
    uint32_t lpddr4_twtr;
    uint32_t lpddr4_tfaw;
    uint32_t lpddr4_tzqreset;
    uint32_t lpddr4_tzqinit;
    uint32_t lpddr4_tzqcs;
    uint32_t lpddr4_tzqcsb;
    uint32_t lpddr4_tzqclb;
    uint32_t lpddr4_tzqcl;
    uint32_t lpddr4_tmrr;
    uint32_t lpddr4_tmrw;
    uint32_t lpddr4_tmrwb;
    uint32_t lpddr4_tmrd;
    uint32_t lpddr4_tmrdb;
    uint32_t lpddr4_tcke;
    uint32_t lpddr4_tckesr;
    uint32_t lpddr4_tccd;
    uint32_t lpddr4_tccdmw;
    uint32_t lpddr4_trtp;
    uint32_t lpddr4_twr;
    uint32_t lpddr4_tppd;
    uint32_t lpddr4_tdqsck;
    uint32_t lpddr4_tdqsck_max;
    uint32_t lpddr4_tdqsck_max_dr;
    uint32_t lpddr4_tosco;
    uint32_t lpddr4_tdqss;
    uint32_t lpddr4_tdqs2dq;
    uint32_t lpddr4_tdipw_ps;
    uint32_t lpddr4_trcd;
    uint32_t lpddr4_trp;
    uint32_t lpddr4_trpa;
    uint32_t lpddr4_trc;
    uint32_t lpddr4_cl;
    uint32_t lpddr4_cl_dbi;
    uint32_t lpddr4_cwl_seta;
    uint32_t lpddr4_cwl_setb;
    uint32_t lpddr4_nrtp;
    uint32_t lpddr4_nwr;
    uint32_t lpddr4_tcmdcke;
    uint32_t lpddr4_tmrwckel;
    uint32_t lpddr4_tmrwckelb;
    uint32_t lpddr4_tckckeh;
    uint32_t lpddr4_tckelck;
    uint32_t lpddr4_tsr;
    uint32_t lpddr4_todton_min;
    uint32_t lpddr4_tvrcg_enable;
    uint32_t lpddr4_tvrcg_disable;
    uint32_t lpddr4_txp;
    uint32_t lpddr4_trrd;
    uint32_t lpddr4_odtloff_latency_seta;
    uint32_t lpddr4_odtloff_latency_setb;
    uint32_t lpddr4_odtlon_latency_seta;
    uint32_t lpddr4_odtlon_latency_setb;
    uint32_t lpddr4_wdqson_seta;
    uint32_t lpddr4_wdqson_setb;
    uint32_t lpddr4_wdqsoff_seta;
    uint32_t lpddr4_wdqsoff_setb;
    uint32_t lpddr_tzqinit_min;
    uint32_t lpddr4_derated_trcd;
    uint32_t lpddr4_derated_tras_min;
    uint32_t lpddr4_derated_trp;
    uint32_t lpddr4_derated_trrd;
    uint32_t lpddr4_derated_trc;

    // LPDDR5 Timing Parameters (generally in ps)
    uint32_t lpddr5_wck_ps;
    uint32_t lpddr5_cl_ps;
    uint32_t lpddr5_cl_dbi_ps;
    uint32_t lpddr5_twtr_s_ps;
    uint32_t lpddr5_twtr_l_ps;
    uint32_t lpddr5_twtr_ps;
    uint32_t lpddr5_tpbr2pbr_ps;
    uint32_t lpddr5_tpbr2act_ps;
    uint32_t lpddr5_trcd_ps;
    uint32_t lpddr5_tccdmw_tck;
    uint32_t lpddr5_trp_ps;
    uint32_t lpddr5_tsr_ps;
    uint32_t lpddr5_txsr_ps;
    uint32_t lpddr5_trfcab_ps;
    uint32_t lpddr5_trfcpb_ps;
    uint32_t lpddr5_tcspd_ps;
    uint32_t lpddr5_tcmpd_ps;
    uint32_t lpddr5_tescke_ps;
    uint32_t lpddr5_tcmdpd_ps;
    uint32_t lpddr5_tcslck_ps;
    uint32_t lpddr5_tckcsh_ps;
    uint32_t lpddr5_txp_ps;
    uint32_t lpddr5_tcsh_ps;
    uint32_t lpddr5_tcsl_ps;
    uint32_t lpddr5_tmrwpd_ps;
    uint32_t lpddr5_tzqpd_ps;
    uint32_t lpddr5_trc_pab_ps;
    uint32_t lpddr5_trc_ppb_ps;
    uint32_t lpddr5_trpab_ps;
    uint32_t lpddr5_trppb_ps;
    uint32_t lpddr5_tras_min_ps;
    uint32_t lpddr5_tras_max_ps;
    uint32_t lpddr5_twr_ps;
    uint32_t lpddr5_tccd_l_tck;   //!< Cas to Cas command delay to same bank group
    uint32_t lpddr5_tccd_s_tck;   //!< Cas to Cas command delay to different bank group
    uint32_t lpddr5_tccd_ps;
    uint32_t lpddr5_trrd_l_ps;  //!< Active bank a to Active bank b command time to same bank group
    uint32_t lpddr5_trrd_s_ps;  //!< Active bank a to Active bank b command time to different bank group
    uint32_t lpddr5_trrd_ps;
    uint32_t lpddr5_tfaw_ps;
    uint32_t lpddr5_trtp_ps;
    uint32_t lpddr5_tppd_tck;
    uint32_t lpddr5_tmrr_tck;
    uint32_t lpddr5_tmrw_ps;
    uint32_t lpddr5_tmrd_ps;
    uint32_t lpddr5_odtloff_tck;
    uint32_t lpddr5_odtlon_tck;
    uint32_t lpddr5_odton_min_ps;
    uint32_t lpddr5_odton_max_ps;
    uint32_t lpddr5_odtoff_min_ps;
    uint32_t lpddr5_odtoff_max_ps;
    uint32_t lpddr5_tzqreset_ps;
    uint32_t lpddr5_tzqlat_ps;
    uint32_t lpddr5_tzqcal_ps;
    uint32_t lpddr5_tzqstop_ps;
    uint32_t lpddr5_tzqoff_us;
    uint32_t lpddr5_tvrcg_enable_ps;
    uint32_t lpddr5_tvrcg_disable_ps;
    // suffix _wck to indicate  units are tWCK
    uint32_t lpddr5_wckenl_rd_wck;
    uint32_t lpddr5_wckpre_rd_static_wck;
    uint32_t lpddr5_wckpre_rd_toggle_wck;
    uint32_t lpddr5_wckenl_wr_seta_wck;
    uint32_t lpddr5_wckenl_wr_setb_wck;
    uint32_t lpddr5_wckpre_wr_static_wck;
    uint32_t lpddr5_wckpre_wr_toggle_wck;
    uint32_t lpddr5_wckpre_static_tck;
    uint32_t lpddr5_wckpre_toggle_wr_tck;
    uint32_t lpddr5_wckpre_toggle_rd_tck;
    uint32_t lpddr5_wckenl_rd_tck;
    uint32_t lpddr5_wckenl_wr_tck;
    uint32_t lpddr5_wckenl_fs_tck;
    uint32_t lpddr5_twck_en_wck;
    uint32_t lpddr5_twck_toggle_en_wck;
    uint32_t lpddr5_twck_toggle_dis_wck;
    uint32_t lpddr5_tpdn_ps;
    uint32_t lpddr5_tpdn_dsm_ms;
    uint32_t lpddr5_txsr_dsm_us;
    uint32_t lpddr5_trbtp_ps;
    uint32_t lpddr5_tespd_ps;
    uint32_t lpddr5_wl_tck;
    uint32_t lpddr5_rl_tck;
    uint32_t lpddr5_nrtp;
    uint32_t lpddr5_nrbtp_ps; //!< READ Burst end to PRECHARGE command delay
    uint32_t lpddr5_nwr;
    uint32_t lpddr5_bl_n_min_tck; //!< Effective burst length
    uint32_t lpddr5_bl_n_max_tck; //!< Effective burst length
    uint32_t lpddr5_twck_pst_wck;
    uint32_t lpddr5_wckdqo_max_ps;
    uint32_t lpddr5_wckdqo_ps;
    uint32_t lpddr5_wckdqi_ps;
    uint32_t lpddr5_trpst;
    uint32_t lpddr5_trefi_ps; //!< all bank average refresh interval
    uint32_t lpddr5_trefipb_ps;  //!< per bank average refresh interval
    uint32_t lpddr5_derated_trcd_ps;
    uint32_t lpddr5_derated_tras_min_ps;
    uint32_t lpddr5_derated_trpab_ps;
    uint32_t lpddr5_derated_trppb_ps;
    uint32_t lpddr5_derated_trrd_ps;
    uint32_t lpddr5_derated_trcab_ps;
    uint32_t lpddr5_derated_trcpb_ps;

#endif
    uint32_t wr2pre;  //!< min time between write and precharge to the same bank


  } ddrTimingParameters_t;
  
  /**
    * @brief Structure containing parameters to program DWC DDR umctl registers.
          * The variables here are pre-calculated timings to help
          * program some register fields.
    */
        typedef struct tag_mctl_pre_cfg {
            uint32_t cl[UMCTL2_FREQUENCY_NUM]; //! CL
            uint32_t cl_dbi[UMCTL2_FREQUENCY_NUM]; //!<
            uint32_t cwl_x[UMCTL2_FREQUENCY_NUM];    //!<  CWL adjusted.
            uint32_t twr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];      //!< Write recovery time
            uint32_t twtr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];     //!< Write to Read command delay
            uint32_t twtr_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];   //!<
            uint32_t tfaw[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];     //!< Four Bank Activate window
            uint32_t txp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];      //!< Exit power down to a valid command
            uint32_t txpdll[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_ras_max[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_ras_min[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_rtp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_rc[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t wr2rd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t wr2rd_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t rd2wr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t rd2wr_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t wdqspreext[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];

            uint32_t odton_min[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t odton[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_mrw[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Mode Register Write command period
            uint32_t t_mr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Load-mode command to next valid command period (tmrd >= tmrw)
            uint32_t t_mod[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_rcd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Active to Read/Write command time
            uint32_t t_ccd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Cas to Cas command delay
            uint32_t t_rrd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Active bank a to Active bank b command time
            uint32_t t_rp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_cksrx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_cksre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_ckesr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_cke[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_csh[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_mrd_pda[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t odtloff[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t odtlon[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_t_rddata_en[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_tphy_wrlat[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t cmd_lat_adder[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_t_dram_clk_disable[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_t_dram_clk_enable[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];

#ifdef UMCTL2_CID_EN
            uint32_t t_ccd_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_rrd_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< ddr4 and ddr5
            uint32_t t_faw_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_faw_slr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_wr2rd_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];  //!< ddr5
            uint32_t t_rd2wr_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< ddr5
            uint32_t t_refsbrd_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_rfcsb_dlr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
#endif

#ifdef MEMC_LPDDR2
            uint32_t derated_t_rcd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t derated_t_ras_min[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t derated_t_rp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t derated_t_rrd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t derated_t_rc[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t tINITTMG1[UMCTL2_NUM_DATA_CHANNEL];  //!< min cke low time before RESET_n high
            uint32_t tINITTMG3[UMCTL2_NUM_DATA_CHANNEL]; //!< min idle time before first MRW/MRR command.
            uint32_t t_pbr2pbr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_pbr2act[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t tINIT2;    //!<
            uint32_t tINIT3;  //!< used post_cke
            uint32_t tINIT4[UMCTL2_FREQUENCY_NUM]; //!< min idle time before first CKE high.
            uint32_t t_rrd_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Activate command to different bank group than prior Activate command
            uint32_t t_osco[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
#endif          

            uint32_t wl[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< write latency
            uint32_t rl[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< read latency
            uint32_t t_rbtp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< LPDDR5
            uint32_t t_cmdcke[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_vrcg_enable[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_vrcg_disable[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t lpddr4_diff_bank_rwa2pre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Time between Read/Write/Masked Write/Act and Precharge to diff bank
            uint32_t wra2pre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Time between write with AP and activate to same bank
            uint32_t rda2pre[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Time between write read AP and activate to same bank.
            uint32_t rd2wr_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Minimum time from read command to write command for different bank group
            uint32_t rd2wr_s_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!< Minimum time from read command to write command for different bank group
            uint32_t max_rd_sync[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< Maximum time between read commands without a new WCK2CK sync Start
            uint32_t max_wr_sync[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< Maximum time between write commands without a new WCK2CK sync start
            uint32_t nwr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< nWR
            uint32_t nrtp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< nRTP
            uint32_t nrbtp[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< nRBTP
            uint32_t dfi_twck_en_rd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_twck_en_wr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_twck_en_fs[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_twck_dis[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_twck_fast_toggle[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_twck_toggle[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_twck_toggle_cs[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t dfi_twck_toggle_post[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t rd2mr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< Time from Read to MRW/MRR command
            uint32_t wr2mr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< Time from Write to MRW/MRR command
            uint32_t mrr2rd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< Time from MRR to Read command
            uint32_t mrr2wr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< Time from MRR to Write command
            uint32_t mrr2wr_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< Time from MRR to Write command
            uint32_t mrr2mrw[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!< Time from MRR to MRW command
            // ddr4
            uint32_t t_xs_fast_min[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t t_xs_min[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            //ddr5
            uint32_t t_pd[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!<tPD  ddr5
            uint32_t t_mpsmx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!<tMPSMX ddr5
            uint32_t t_mpdpxact[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!<tMPDPADACT ddr5
            uint32_t t_pda_latch[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tPDA_LATCH ddr5
            uint32_t t_pda_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tPDA_DELAY ddr5
            uint32_t t_pda_dqs_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tPDA_DQS_DELAY ddr5
            uint32_t t_pda_s[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<t_pda_s ddr5
            uint32_t t_pda_h[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tPDA_H ddr5

            uint32_t t_cpded[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tCPDED ddr5
            uint32_t t_casrx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tCASRX ddr5
            uint32_t t_csh_srexit[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tCSH_SRexit ddr5
            uint32_t t_csl_srexit[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tCSl_SRexit ddr5

            uint32_t t_mpc_cs[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!<tMPC_CS ddr5
            uint32_t t_mpc_setup[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tMPC_Setup  ddr5
            uint32_t t_mpc_hold[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!<tMPC_Hold ddr5
            uint32_t t_vrefca_cs[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tVrefCA_CS ddr5
            uint32_t t_mpc_delay[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tMPC_DELAY ddr5
            uint32_t t_osco_ddr5[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tOSCO ddr5
            uint32_t t_ccd_w[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];//!<tCCD_L_WR  write to write same bank group second write write RMW
            uint32_t t_ccd_w2[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!<tCCD_L_WR2 write to write same bank group second write not  RMW
            uint32_t t_wr2rd_dpr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!<wr2rd_dpr
            uint32_t t_rd2wr_dpr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL]; //!<rd2wr_dpr
#ifdef MEMC_NUM_RANKS_GT_1
            uint32_t wr2rd_dr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t rd2wr_dr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t diff_rank_rd_gap[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t diff_rank_wr_gap[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t wr2rd_dr_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t rd2wr_dr_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t diff_rank_rd_gap_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t diff_rank_wr_gap_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t wr2rd_dr_wck_on[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t rd2wr_dr_wck_on[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t diff_rank_rd_gap_wck_on[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t diff_rank_wr_gap_wck_on[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t wr2rd_dr_wck_on_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t rd2wr_dr_wck_on_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t diff_rank_rd_gap_wck_on_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
            uint32_t diff_rank_wr_gap_wck_on_odt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
#endif

    //ddr5 RCD
    uint32_t t_stab01[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
    uint32_t t_cssr[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
    uint32_t t_cpded2srx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
    uint32_t t_srx2srx[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
    uint32_t t_ckoff[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
    uint32_t t_ckact[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];
    uint32_t t_csalt[UMCTL2_FREQUENCY_NUM][UMCTL2_NUM_DATA_CHANNEL];

            uint32_t lpddr5_cdd;
            uint32_t tphy_wckcsgap;

        } mctl_pre_cfg;
  /**
   * @brief Type definition of structure describing mode register fields.
   */

 typedef struct tag_ddr4_mr0_t {
     uint8_rnd_t wr_recovery;
     uint8_rnd_t dll_reset;
     uint8_rnd_t cl;          //!< CAS Latency
     uint8_rnd_t burst_type;
     uint8_rnd_t burst_length;
   } ddr4_mr0_t;

 typedef struct tag_ddr4_mr1_t {
     uint8_rnd_t rtt_nom;
     uint8_rnd_t wr_leveling_enable;
     uint8_rnd_t al;
     uint8_rnd_t output_driver_impedance;
     uint8_rnd_t dll_enable;
   } ddr4_mr1_t;

 typedef struct tag_ddr4_mr2_t {
     uint8_rnd_t write_crc;
     uint8_rnd_t rtt_wr;
     uint8_rnd_t auto_self_ref;
     uint8_rnd_t cwl;
   } ddr4_mr2_t;

  typedef struct tag_ddr4_mr3_t {
    uint8_rnd_t wcl;
    uint8_rnd_t geardown;
    uint8_rnd_t mpr_op;
    uint8_rnd_t mpr_ps;
    uint8_rnd_t fine_granularity_refresh;
   } ddr4_mr3_t;

 typedef struct tag_ddr4_mr4_t {
   uint8_rnd_t wr_preamble;
     uint8_rnd_t rd_preamble;
     uint8_rnd_t selfref_abort;
     uint8_rnd_t cal;
     uint8_rnd_t fgr_mode;
     uint8_rnd_t refresh_range;
   } ddr4_mr4_t;

 typedef struct tag_ddr4_mr5_t {
     uint8_rnd_t read_dbi;
     uint8_rnd_t write_dbi;
     uint8_rnd_t data_mask;
     uint8_rnd_t ca_parity_persistent;
     uint8_rnd_t rtt_park;
     uint8_rnd_t dis_odt_input_buf_in_pd;
     uint8_rnd_t parity_latency_mode;
   } ddr4_mr5_t;
 typedef struct tag_ddr4_mr6_t {
     uint8_rnd_t tccd_l;
   } ddr4_mr6_t;

 // umctl5 ddr5
 ////////////////////////////////////
 typedef struct tag_ddr5_mr0_t {
     uint8_rnd_t burst_length;
     uint8_rnd_t cl;  //!<CAS latency
   } ddr5_mr0_t;

 typedef struct tag_ddr5_mr2_t {
     uint8_rnd_t rd_preamble_enable;
     uint8_rnd_t wr_leveling;
     uint8_rnd_t ddr5_2n_mode;
     uint8_rnd_t mpsm;
     uint8_rnd_t cs_assertion_duration;
     uint8_rnd_t dev15_mpsm;
     uint8_rnd_t internal_wr_timing;
   } ddr5_mr2_t;

 typedef struct tag_ddr5_mr3_t {
     uint8_rnd_t wr_leveling_internal_lower_byte;
     uint8_rnd_t wr_leveling_internal_upper_byte;
   } ddr5_mr3_t;

 typedef struct tag_ddr5_mr4_t {
     uint8_rnd_t refresh_trfc_mode;
     uint8_rnd_t refresh_rate;
   } ddr5_mr4_t;

 typedef struct tag_ddr5_mr5_t {
     uint8_rnd_t data_output_disable;
     uint8_rnd_t pull_up_output_drv_impedance;
     uint8_rnd_t tdqs_enable;
     uint8_rnd_t dm_enable;
     uint8_rnd_t pull_down_output_drv_impedance;
   } ddr5_mr5_t;

 typedef struct tag_ddr5_mr6_t {
     uint8_rnd_t trtp;
     uint8_rnd_t wr_recovery;
   } ddr5_mr6_t;

 typedef struct tag_ddr5_mr8_t {
     uint8_rnd_t rd_preamble;
     uint8_rnd_t wr_preamble;
     uint8_rnd_t rd_postamble;
     uint8_rnd_t wr_postamble;
   } ddr5_mr8_t;

 typedef struct tag_ddr5_mr13_t {
     uint8_rnd_t tccd_l;
   } ddr5_mr13_t;

 typedef struct tag_ddr5_mr34_t {
     uint8_rnd_t rtt_park;
     uint8_rnd_t rtt_wr;
   } ddr5_mr34_t;

 typedef struct tag_ddr5_mr35_t {
     uint8_rnd_t rtt_nom_wr;
     uint8_rnd_t rtt_nom_rd;
   } ddr5_mr35_t;

 typedef struct tag_ddr5_mr37_t {
     uint8_rnd_t odtlon_wr_offset;
     uint8_rnd_t odtloff_wr_offset;
   } ddr5_mr37_t;

 typedef struct tag_ddr5_mr38_t {
     uint8_rnd_t odtlon_wr_nt_offset;
     uint8_rnd_t odtloff_wr_nt_offset;
   } ddr5_mr38_t;

 typedef struct tag_ddr5_mr39_t {
     uint8_rnd_t odtlon_rd_nt_offset;
     uint8_rnd_t odtloff_rd_nt_offset;
   } ddr5_mr39_t;

 typedef struct tag_ddr5_mr40_t {
     uint8_rnd_t rd_dqs_offset;
   } ddr5_mr40_t;

 typedef struct tag_ddr5_mr45_t {
     uint8_rnd_t osc_run_time;
   } ddr5_mr45_t;

 typedef struct tag_ddr5_mr50_t {
     uint8_rnd_t rd_crc_enable;
     uint8_rnd_t wr_crc_enable_lower_nibble;
     uint8_rnd_t wr_crc_enable_upper_nibble;
     uint8_rnd_t wr_crc_error_status;
     uint8_rnd_t wr_crc_auto_disable_enable;
     uint8_rnd_t wr_crc_auto_disable_status;
   } ddr5_mr50_t;

 typedef struct tag_ddr5_mr51_t {
     uint8_rnd_t wr_crc_auto_disable_thre;
   } ddr5_mr51_t;

 typedef struct tag_ddr5_mr52_t {
     uint8_rnd_t wr_crc_auto_disable_window;
   } ddr5_mr52_t;

 typedef struct tag_ddr5_mode_registers_t {
   ddr5_mr0_t mr0;
   ddr5_mr2_t mr2;
   ddr5_mr3_t mr3;
   ddr5_mr4_t mr4;
   ddr5_mr5_t mr5;
   ddr5_mr6_t mr6;
   ddr5_mr8_t mr8;
   ddr5_mr13_t mr13;
   ddr5_mr34_t mr34;
   ddr5_mr35_t mr35;
   ddr5_mr37_t mr37;
   ddr5_mr38_t mr38;
   ddr5_mr39_t mr39;
   ddr5_mr40_t mr40;
   ddr5_mr45_t mr45;
   ddr5_mr50_t mr50;
   ddr5_mr51_t mr51;
   ddr5_mr52_t mr52;
   } ddr5_mode_registers_t;

 ////////////////////////////////////
  typedef struct tag_ddr5_rcd_rw00_t {
    uint8_rnd_t ca_rate; // 0: SDR, 1: DDR
  } ddr5_rw00_t;

  typedef struct tag_ddr5_rcd_rw01_t {
    uint8_rnd_t parity_check;      // 0: disable, 1: enable
    uint8_rnd_t alert_n_assertion; // 0: Static ALERT_n Assertion Mode 1: Pulsed ALERT_n Mode
    uint8_rnd_t alert_n_reenable;  // 0: Parity checking remains disabled after ALERT_n pulse, 1: Parity Checking is re-enabled after ALERT_n pulse
  } ddr5_rw01_t;

  typedef struct tag_ddr5_rcd_rw05_t {
    uint8_rnd_t operating_speed;
  } ddr5_rw05_t;

  typedef struct tag_ddr5_rcd_rw11_t {
    uint8_rnd_t latency_adder_nladd_to_all_dram_cmd;
  } ddr5_rw11_t;

  typedef struct tag_ddr5_rcd_control_words_t {
    ddr5_rw00_t rw00;
    ddr5_rw01_t rw01;
    ddr5_rw05_t rw05;
    ddr5_rw11_t rw11;
  } ddr5_control_words_t;

  ////////////////////////////////////
 typedef struct tag_ddr4_mode_registers_t {
   ddr4_mr0_t mr0;
   ddr4_mr1_t mr1;
   ddr4_mr2_t mr2;
   ddr4_mr3_t mr3;
   ddr4_mr4_t mr4;
   ddr4_mr5_t mr5;
   ddr4_mr6_t mr6;
 } ddr4_mode_registers_t;

 ////////////////////////////////////
  typedef struct tag_lpddr4_mr1_t {
      uint8_rnd_t rd_postamble;
      uint8_rnd_t wr_recovery;
      uint8_rnd_t rd_preamble;
      uint8_rnd_t wr_preamble;
      uint8_rnd_t burst_length;
   } lpddr4_mr1_t;

 typedef struct tag_lpddr4_mr2_t {
     uint8_rnd_t wls;
     uint8_rnd_t rl_wl;
   } lpddr4_mr2_t;

  typedef struct tag_lpddr4_mr3_t {
      uint8_rnd_t write_dbi;
      uint8_rnd_t read_dbi;
      uint8_rnd_t wr_postamble;
      uint8_rnd_t pu_cal;
   } lpddr4_mr3_t;

 typedef struct tag_lpddr4_mr12_t {
   uint8_rnd_t vr_ca;
   uint8_rnd_t vref_ca;
   } lpddr4_mr12_t;

 typedef struct tag_lpddr4_mr11_t {
   uint8_rnd_t ca_odt;
   uint8_rnd_t dq_odt;
   } lpddr4_mr11_t;

  typedef struct tag_lpddr4_mr13_t {
   uint8_rnd_t fsp_op;
   uint8_rnd_t fsp_wr;
   uint8_rnd_t dmd;
   } lpddr4_mr13_t;

 typedef struct tag_lpddr4_mr14_t {
   uint8_rnd_t vr_dq;
   uint8_rnd_t vref_dq;
   } lpddr4_mr14_t;

  typedef struct tag_lpddr4_mr22_t {
   uint8_rnd_t odtd;
   uint8_rnd_t odtd_ca;
   uint8_rnd_t odtd_cs;
   uint8_rnd_t odtd_ck;
   uint8_rnd_t soc_odt;
   } lpddr4_mr22_t;

  typedef struct tag_lpddr4_mr23_t {
	 uint8_rnd_t dqs_interval;
   } lpddr4_mr23_t; 
   
  typedef struct tag_lpddr4_mode_registers_t {
	 lpddr4_mr1_t mr1;
	 lpddr4_mr2_t mr2;
	 lpddr4_mr3_t mr3;
	 lpddr4_mr11_t mr11;
	 lpddr4_mr12_t mr12;
	 lpddr4_mr13_t mr13;
	 lpddr4_mr14_t mr14;
	 lpddr4_mr22_t mr22;
	 lpddr4_mr23_t mr23;
 } lpddr4_mode_registers_t;


  typedef struct tag_lpddr5_mr1_t {
    uint8_rnd_t write_latency;
    uint8_rnd_t ck_mode;
    uint8_rnd_t burst_length;
  } lpddr5_mr1_t;

  typedef struct tag_lpddr5_mr2_t {
    uint8_rnd_t nwr;
    uint8_rnd_t rl_nrtp;
  } lpddr5_mr2_t;

  typedef struct tag_lpddr5_mr3_t {
    uint8_rnd_t write_dbi;
    uint8_rnd_t read_dbi;
    uint8_rnd_t wls;
    uint8_rnd_t bk_bg_org;
    uint8_rnd_t pdds;
  } lpddr5_mr3_t;

  typedef struct tag_lpddr5_mr10_t {
    uint32_rnd_t rdqs_pst;
    uint32_rnd_t rdqs_pre;
    uint32_rnd_t wck_pst;
  } lpddr5_mr10_t;

  typedef struct tag_lpddr5_mr11_t {
    uint8_rnd_t ca_odt;
    uint8_rnd_t nt_odt;
    uint8_rnd_t dq_odt;
  } lpddr5_mr11_t;

  typedef struct tag_lpddr5_mr12_t {
   uint8_rnd_t vbs;
   uint8_rnd_t vref_ca;
  } lpddr5_mr12_t;
  typedef struct tag_lpddr5_mr13_t {
   uint8_rnd_t dual_vdd2;
   uint8_rnd_t dmd;
   uint8_rnd_t vro;
   uint8_rnd_t thermal_offset;
  } lpddr5_mr13_t;

  typedef struct tag_lpddr5_mr14_t {
   uint8_rnd_t vdlc;
   uint8_rnd_t vref_dq;
  } lpddr5_mr14_t;

  typedef struct tag_lpddr5_mr15_t {
   uint8_rnd_t vref_dq;
  } lpddr5_mr15_t;

  typedef struct tag_lpddr5_mr16_t {
   uint8_rnd_t cbt;
   uint8_rnd_t vrcg;
   uint8_rnd_t fsp_op;
   uint8_rnd_t fsp_wr;
  } lpddr5_mr16_t;

  typedef struct tag_lpddr5_mr17_t {
   uint8_rnd_t odtd;
   uint8_rnd_t odtd_ca;
   uint8_rnd_t odtd_ck;
   uint8_rnd_t soc_odt;
  } lpddr5_mr17_t;

  typedef struct tag_lpddr5_mr18_t {
   uint8_rnd_t ckr;
   uint8_rnd_t wck2ck_leveling;
   uint8_rnd_t wck_sync;
   uint8_rnd_t wck_on;
   uint8_rnd_t wck_fm;
   uint8_rnd_t wck_odt;
  } lpddr5_mr18_t;

  typedef struct tag_lpddr5_mr19_t {
   uint8_rnd_t dvfsq;
   uint8_rnd_t dvfsc;
  } lpddr5_mr19_t;

  typedef struct tag_lpddr5_mr20_t {
   uint8_rnd_t wck_mode;
   uint8_rnd_t rdqs;
  } lpddr5_mr20_t;
  typedef struct tag_lpddr5_mr21_t {
   uint8_rnd_t dcfe;
   uint8_rnd_t wxfs;
  } lpddr5_mr21_t;
  typedef struct tag_lpddr5_mr22_t {
   uint8_rnd_t wecc;
   uint8_rnd_t recc;
  } lpddr5_mr22_t;
  typedef struct tag_lpddr5_mr23_t {
   uint8_rnd_t pasr_mask;
  } lpddr5_mr23_t;
  typedef struct tag_lpddr5_mr25_t {
   uint8_rnd_t ck_bus_term;
   uint8_rnd_t ca_bus_term;
   uint8_rnd_t parc;
  } lpddr5_mr25_t;
  typedef struct tag_lpddr5_mr28_t {
   uint8_rnd_t zq_int;
   uint8_rnd_t zq_stop;
   uint8_rnd_t zq_reset;
  } lpddr5_mr28_t;
  typedef struct tag_lpddr5_mr37_t {
    uint8_rnd_t wck2dqi_runtime;
  }lpddr5_mr37_t;
  typedef struct tag_lpddr5_mr40_t {
    uint8_rnd_t wck2dqo_runtime;
  }lpddr5_mr40_t;
//todo mr29,mr30,mr31,mr32,mr33,mr34,mr37,mr40
  typedef struct tag_lpddr5_mode_registers_t {
   lpddr5_mr1_t mr1;
   lpddr5_mr2_t mr2;
   lpddr5_mr3_t mr3;
   lpddr5_mr10_t mr10;
   lpddr5_mr11_t mr11;
   lpddr5_mr12_t mr12;
   lpddr5_mr13_t mr13;
   lpddr5_mr14_t mr14;
   lpddr5_mr15_t mr15;
   lpddr5_mr16_t mr16;
   lpddr5_mr17_t mr17;
   lpddr5_mr18_t mr18;
   lpddr5_mr19_t mr19;
   lpddr5_mr20_t mr20;
   lpddr5_mr21_t mr21;
   lpddr5_mr22_t mr22;
   lpddr5_mr23_t mr23;
   lpddr5_mr25_t mr25;
   lpddr5_mr28_t mr28;
   lpddr5_mr37_t mr37;
   lpddr5_mr40_t mr40;
 } lpddr5_mode_registers_t;




#ifdef  __cplusplus
}
#endif
#endif  //__CINIT_TYPES_H__
