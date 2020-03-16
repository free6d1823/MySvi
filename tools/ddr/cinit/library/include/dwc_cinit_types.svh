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

`ifndef __CINIT_TYPES_H__
`define __CINIT_TYPES_H__
`ifdef  __cplusplus
extern "C" {
`endif
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
  typedef enum  {
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
  typedef enum  {
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
  typedef enum  {
    DWC_WCKCK_2_1=1,
    DWC_WCKCK_4_1
  } dwc_lpddr5_wckck_ratio_e;

  /*! \enum dwc_lpddr5_bk_bg_org_e
   * Encoding of LPDDDR5 back organization.
   */
  typedef enum  {
    DWC_LPDDR5_4BK_4BG=0,
    DWC_LPDDR5_8BK,
    DWC_LPDDR5_16BK
  } dwc_lpddr5_bk_bg_org_e;

  typedef enum  {
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

  typedef enum  {
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
  typedef enum  {
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
  typedef enum  {
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

  typedef enum  {
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

  typedef enum  {

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
  typedef enum  {
    DWC_LOCK_STEP=1,
    DWC_SERIAL,
    DWC_MULTI_CHAN,
    DWC_MULTI_CHAN_SHARED_AC
  } dwc_lpddr4_chan_mode_e;



  typedef enum  {
    DWC_NODIMM=1,
    DWC_RDIMM,
    DWC_LRDIMM,
    DWC_UDIMM
  } dwc_sdram_module_type;

  typedef enum  {
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
  typedef enum  {
    DWC_DDR4  ,        //!<DDR4 SDRAM
    DWC_DDR5  ,        //!<DDR5 SDRAM
    DWC_LPDDR4,        //!<LPDDR4 SDRAM
    DWC_LPDDR5         //!<LPDDR5 SDRAM
  } dwc_sdram_protocol;

  /**
    * @brief Enumerated type listing the sdram bus width bus width
    */
  typedef enum  {
    DWC_BUSWIDTH_FULL = 1,    //!< Full bus width
    DWC_BUSWIDTH_HALF = 2,    //!< Half bus width
    DWC_BUSWIDTH_QUARTER = 3  //!< Quarter bus width
  } dwc_sdram_bus_width_e;

/************************************************************************/


        /**
  * @brief Enum type for PHY types
  */
       typedef enum  {
    DWC_DDR54_PHY = 1,
    DWC_LPDDR54_PHY = 2,
    DWC_DDR43_PHY = 3,
    DWC_LPDDR4X_MULTIPHY = 4
  } ddrPhyType_e;


        typedef enum  {
            SLOW,
            TYP,
            FAST
        } speed_index_e;



  /**
   * @brief Enumerated type listing SDRAM/MRAM rank structures
   */
  typedef enum  {
    MRAM_UC_NONE = 0, //All ranks are SDRAM
    MRAM_UC_ALL,    //All ranks are MRAM
    MRAM_UC_MIXED   //SDRAM MRAM 50:50 split (lower ranks are SDRAM)
  } mramUseCase_e;

  /**
    * @brief Enumerated type listing bus width
    */
  typedef enum  {
    DDR_BUSWIDTH_FULL = 1,    //!< Full bus width
    DDR_BUSWIDTH_HALF = 2,    //!< Half bus width
    DDR_BUSWIDTH_QUARTER = 4, //!< Quarter bus width
    DDR_BUSWIDTH_MAX      //!< internal Not used
  } ddrBusWidth_e;


  typedef enum  {
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
  typedef struct  {
    //DRAM Timing Parameters
    int unsigned sg_tck_ps;   //!< Minimum Clock Cycle Time
    int unsigned trc_ps;    //!< Active to Active/Auto Refresh command time
    int unsigned trcd_ps;   //!< Active to Read/Write command time
    int unsigned trp_ps;    //!< Precharge command period
    int unsigned trpa_ps;   //!< ???
    int unsigned trrd_l_tck;  //!< Active bank a to Active bank b command time to same bank group
    int unsigned trrd_s_tck;  //!< Active bank a to Active bank b command time to different bank group
    int unsigned trrd_ps;   //!< Active bank a to Active bank b command time
`ifdef MEMC_DDR4
    //DDR4 Timing Parameters
    int unsigned ddr4_txp_ps;           //!< Exit power down to a valid command
    int unsigned ddr4_txpdll_ps;        //!< Exit precharge power down to READ or WRITE command (DLL-off mode)
    int unsigned ddr4_txsdll_tck;       //!< SelfRefresh to commands requiring a locked DLL
    int unsigned ddr4_tras_min_ps;      //!< Minimum Active to Precharge command time
    int unsigned ddr4_tras_max_ps;      //!< Maximum Active to Precharge command time
    int unsigned ddr4_trefi_ps;         //!< ???
    int unsigned ddr4_trfc_min_ps;      //!< Refresh to Refresh Command interval minimum value
    int unsigned ddr4_trfc_min2_ps;     //!< Refresh to Refresh Command interval minimum value
    int unsigned ddr4_trfc_min4_ps;     //!< Refresh to Refresh Command interval minimum value
    int unsigned ddr4_trfc_max_ps;      //!< Refresh to Refresh Command Interval maximum value
    int unsigned ddr4_twtr_l_tck;       //!< Write to Read command delay in clocks (sometimes higher than twtr/tck)
    int unsigned ddr4_twtr_s_tck;       //!< Write to Read command delay in clocks (sometimes higher than twtr/tck)
    int unsigned ddr4_tfaw_ps;          //!< Four Bank Activate window
    int unsigned ddr4_tzqinit_tck;      //!< ZQ Cal (Init) time
    int unsigned ddr4_tzqoper_tck;      //!< ZQ Cal (Long) time
    int unsigned ddr4_tzqcs_tck;        //!< ZQ Cal (Short) time
    int unsigned ddr4_tmrd_tck;         //!< Load Mode Register command cycle time
    int unsigned ddr4_tcke_ps;          //!< CKE minimum high or low pulse width
    int unsigned ddr4_tccd_l_tck;       //!< Cas to Cas command delay to same bank group
    int unsigned ddr4_tccd_s_tck;       //!< Cas to Cas command delay to different bank group
    int unsigned ddr4_tmod_ps;          //!< LOAD MODE to non-LOAD MODE command cycle time
    int unsigned ddr4_trtp_ps;          //!< Read to Precharge command delay
    int unsigned ddr4_twr_ps;           //!< Write recovery time
    int unsigned ddr4_tckmpe_ps;        //!< Valid clock requirement after MPSM entry
    int unsigned ddr4_tmpx_s_tck;       //!< CS setup time to CKE
    int unsigned ddr4_tmpx_lh_ps;       //!< CS_n Low hold time to CKE rising edge
    int unsigned ddr4_tpl_tck;          //!< C/A parity latency
    int unsigned ddr4_wcl_tck;          //!< Write Command Latency
    int unsigned ddr4_twr_crc_dm_tck;   //!< Write recovery time when CRC and DM are enabled (tWR_CRC_DM = twr + twr_crc_dm)
    int unsigned ddr4_twtr_l_crc_dm_tck;//!< tWTR_L's additional delay when CRC and DM are enabled (tWTR_L_CRC_DM = twtr_l_tck + twtr_l_crc_dm)
    int unsigned ddr4_twtr_s_crc_dm_tck;//!< tWTR_S's additional delay when CRC and DM are enabled (tWTR_S_CRC_DM = twtr_s_tck + twtr_s_crc_dm)
    int unsigned ddr4_tcrc_alert_pw_tck;//!< CRC ALERT_n pulse width (Max)
    int unsigned ddr4_tcrc_alert_ps;    //!< CRC error to ALERT_n pulse width
    int unsigned ddr4_tpar_alert_pw_tck;//!< Pulse width of ALERT_N signal when C/A Parity Error is detected (Max)
    int unsigned ddr4_tpar_unknown_ps;  //!< Commands not guaranteed to be executed during this time
    int unsigned ddr4_tpar_alert_on_ps; //!< Delay from errant command to ALERT_n assertion
    int unsigned ddr4_cal_tck;          //!< CS to Command Address Latency when cal mode is enabled (and not in geardown mode)
    int unsigned ddr4_tdqsck_dll_off_ps;//!< Read data Clock to Data Strobe relationship with DLL-off mode
    int unsigned ddr4_tstab_ps;         //!< ddr4 Stabilization time
    int unsigned ddr4_trfc_dlr_ps;      //!< Refresh to Refresh Command to different logical rank
    int unsigned ddr4_trfc_dlr2_ps;     //!< Refresh to Refresh Command to different logical rank
    int unsigned ddr4_trfc_dlr4_ps;     //!< Refresh to Refresh Command to different logical rank
    int unsigned ddr4_trrd_dlr_tck;     //!< Active bank a to Active bank b command time to different logical rank
    int unsigned ddr4_tfaw_dlr_tck;     //!< Four Bank Activate window to different logical rank
    int unsigned ddr4_tccd_dlr_tck;     //!< Cas to Cas command delay to different logical rank

    //int unsigned busWidthFractionDenominator;
    //int unsigned mr0WrRecovery;
    int unsigned mr1Rtt;
    int unsigned mr2AutoSelfRef;
    int unsigned mr4Refresh;
    int unsigned eccEncoding;
    int unsigned eccMode; //!< Also in spd_data
    int unsigned dllOffInit;

    int unsigned ddr4_tcwl_1st_set_tck;
    int unsigned ddr4_tcwl_2nd_set_tck;
    int unsigned ddr4_tcl_tck;
    int unsigned ddr4_tcmd_gear_tck;
    int unsigned ddr4_tsync_gear_tck;
    int unsigned ddr4_tgear_hold_tck;
    int unsigned ddr4_tgear_setup_tck;
    int unsigned ddr4_rankMap4;
    int unsigned ddr4_rankMap2;
    int unsigned ddr4_rankMap2i;
    int unsigned ddr4_tcl_rdbi_tck;

    //ddr5 timing parameters
    int unsigned ddr5_tcwl_tck;
    int unsigned ddr5_tcl_tck;
    int unsigned ddr5_tcl_rdbi_tck;


    int unsigned ddr5_tras_min_ps;    //!< minimum ACT to PRE command period
    int unsigned ddr5_tras_max_ps;    //!< minimum ACT to PRE command period
    int unsigned ddr5_tccd_l_tck;     //!< minimum CAS_n to CAS_n command delay for same bank group
    int unsigned ddr5_tccd_l_wr_tck;  //!< minimum Write CAS_n to CAS_n command delay for same bank group BL32 OTF
    int unsigned ddr5_tccd_s_tck;     //!< minimum CAS_n to CAS_n command delay for different bank group for BL16, and BC8(on-the-fly)
    int unsigned ddr5_tccd_l_wr_ps;   //!<write to write same bank group second write RMW
    int unsigned ddr5_tccd_l_wr2_ps;  //!<write to write same bank group second write not RMW

	  int unsigned ddr5_tfaw_2k_tck;   //!< minimum Four activate window for 2KB page size  // TODO summary to ddr5_tfaw_ps
	  int unsigned ddr5_tfaw_1k_tck;   //!< minimum Four activate window for 1KB page size  // TODO summary to ddr5_tfaw_ps
	  int unsigned ddr5_tfaw_512_tck;   //!< minimum Four activate window for 512B page size  // TODO summary to ddr5_tfaw_ps
	  int unsigned ddr5_tfaw_tck;   //!< minimum Four activate window 
	  int unsigned ddr5_twtr_l_tck; //!< minimum Delay from start of internal write transaction to internal read command for different bank group 
    int unsigned ddr5_tfaw_dlr_tck; //!<Four activate window to the different logical rank
    int unsigned ddr5_tfaw_slr_tck; //!<Four activate window to the same logical rank
	  int unsigned ddr5_twtr_s_tck; //!< minimum Delay from start of internal write transaction to internal read command for the same bank group 
	  int unsigned ddr5_trtp_ps;   //!< minimum Internal READ Command to PRECHARGE Command delay 
	  int unsigned ddr5_tppd_tck;   //!< minimum PRECHARGE (PRE) to PRECHARGE (PRE) delay , // TODO need to add it to VIP
	  int unsigned ddr5_twr_ps;    //!< minimum WRITE recovery time

    //mode register read/write AC timing
    int unsigned ddr5_tmrr_tck;   //!<minimum Mode Register Read command period
    int unsigned ddr5_tmrr_p_tck; //!<minimum Mode Register Read Pattern to Mode Register Read Pattern command spacing
    int unsigned ddr5_tmrw_tck;   //!< minimum Mode Register Write command period
    int unsigned ddr5_tmrd_tck;   //!< minimum Mode Register Set command delay

    //refresh timing parameter
    int unsigned ddr5_trefi1_ps;
    int unsigned ddr5_trefi2_ps;
    int unsigned ddr5_trfc1_ps;  //!<minimum Normal Refresh (REFab)
    int unsigned ddr5_trfc2_ps;  //!<minimum FGR Refresh (REFab)
    int unsigned ddr5_trfcsb_ps; //!<minimum Same Bank Refresh (REFab)

          //3ds refresh timing parameter
	  int unsigned ddr5_trefsbrd_ps;   //!<minimum Same Bank Refresh to ACT delay    

	  int unsigned ddr5_trfc1_dlr_ps; //!< minimum Normal Refresh with 3DS different logical rank 
	  int unsigned ddr5_trfc2_dlr_ps; //!<minimum Fine Granularity Refresh with 3DS different logical rank 
	  int unsigned ddr5_trfcsb_dlr_ps; //!<minimum Same Bank Refresh with 3DS different logical rank 
	  int unsigned ddr5_trefsbrd_dlr_ps;   //!<minimum 3ds Same Bank Refresh to ACT delay    
    int unsigned ddr5_trrd_dlr_tck;  //!<minimum 3ds ACTIVATE to ACTIVATE Command delay to different logical rank

	  // ZQ calibration timing parameters
	  int unsigned ddr5_tzqcal_ps; //!< minimum ZQ calibration timie
	  int unsigned ddr5_tzqlat_ps; //!< minimum ZQ calibration latch timie

	  //self refresh Timing parameters
	  /* int unsigned ddr5_tcpded_ps; //!< minimum Command pass disable delay */
	  int unsigned ddr5_tcsl_ps;   //!< minimum Self-Refresh CS_n low Pulse width
	  int unsigned ddr5_tcsh_srexit_ps; //!< minimum Self-Refresh exit CS_n High Pulse width
	  int unsigned ddr5_tcsl_srexit_tck;//!< minimum Self-Refresh exit CS_n Low Pulse width
	  int unsigned ddr5_tcksrx_ps;      //!< minimum Valid Clock Requirement before SRX
	  int unsigned ddr5_tcklcs_tck;     //!< minimum Valid Clock Requirement after SRE
	  int unsigned ddr5_tcasrx_ps;      //!< minimum Self-Refresh exit CS_n high
	  int unsigned ddr5_txs_ps;         //!< minimum Exit Self-Refresh to next valid command not requireing DLL
	  int unsigned ddr5_txs_dll_ps;     //!< minimum Exit Self-Refresh to next valid command needing a DLL TBD

	  // PDA timings parameters
          int unsigned ddr5_tpda_latch_min_ps;
	  int unsigned ddr5_tpda_delay_ps;  //!< minimum PDA Enumerate ID Command to any other command cycle time
	  int unsigned ddr5_tpda_dqs_delay_min_ps; //!< minimum Delay to rising strobe edge used for sampling DQ during PDA operation
	  int unsigned ddr5_tpda_dqs_delay_max_ps; //!< maximum Delay to rising strobe edge used for sampling DQ during PDA operation
	  int unsigned ddr5_tpda_s_tck;            //!< minimum DQ Setup Time during PDA operation
	  int unsigned ddr5_tpda_h_tck;            //!< minimum DQ Hold Time during PDA operation

	  //MPC command timings parameters
	  int unsigned ddr5_tmpc_delay_tck;   //!< minimum MPC to any other valid command delay
	  int unsigned ddr5_tmc_mpc_setup_tck;  //!<minimum time between stable MPC command and first falling CS edge (SETUP)
	  int unsigned ddr5_tmc_mpc_hold_tck;   //!<minimum time between first rising CS edge and stable MPC command (HOLD)
	  int unsigned ddr5_tmpc_cs_min_tck;    //!< minimum Time CS_n is held low to register MPC command
	  int unsigned ddr5_tmpc_cs_max_tck;    //!< maximum Time CS_n is held low to register MPC command

          // MPSM command timings parameters 
	  int unsigned ddr5_tmpsmx_ps;  //!< minimum MPSM exit to first valid command delay
	  int unsigned ddr5_tmpdpdact_ps; //!< minimum MPSM DPD exit to first ACT command delay

	  // Power down timing parameters;
	  int unsigned ddr5_tcpded_ps;    //!< minimum Command pass disable delay
          int unsigned ddr5_tpd_ps;       //!< Minimum Power Down Time
	  int unsigned ddr5_txp_ps;       //!< minimum Exit Power Down to next valid command
	  int unsigned ddr5_tactpden_tck; //!<minimum Timing of ACT command to Power Down Entry command
	  int unsigned ddr5_tprpden_tck;  //!<minimum Timing of PREab, PREsb or PREpb to Power Down Entry command
	  int unsigned ddr5_trdpden_tck;  //!<minimum Timing of RD or RD w/AP to Power Down Entry command
	  int unsigned ddr5_twrpden_tck;  //!<minimum Timing of WR to Power Down Entry command
	  int unsigned ddr5_twrapden_tck; //!<minimum Timing of WR w/AP to Power Down Entry command
	  int unsigned ddr5_trefpden_tck; //!<minimum Timing of REFab or REFsb command to Power Down Entry command
	  int unsigned ddr5_tmrrpden_tck; //!<minimum Timing of MRR to command to Power Down Entry command
	  int unsigned ddr5_tmrwpden_tck; //!<minimum Timing of MRW command to Power Down Entry command
	  int unsigned ddr5_tmpcpden_tck; //!<minimum Timing of MPC command to Power Down Entry command

	  //Initialization Timing parameters
	  int unsigned ddr5_tinit4_ps;    //!< minimum time for DRAM to register EXIT on CS with CMOS
	  int unsigned ddr5_tinit5_tck;   //!< minimum cycles required after CS_n HIGH
	  int unsigned ddr5_txpr_ps;      //!< minimum time from Exit Reset to first valid Configuration Command

	  //VrefCA command Timing parameters
	  int unsigned ddr5_tvrefca_delay_tck;  //!< minimum VrefCA command to any other valid command delay
	  int unsigned ddr5_tvrefca_cs_min_tck;     //!< minimum Time CS_n is held low to register VrefCA command
	  int unsigned ddr5_tvrefca_cs_max_tck;     //!< maximum Time CS_n is held low to register VrefCA command

	  //DQS interval OSCilator Read out Timing parameters
	  int unsigned ddr5_tosco_ps;  //!< minimum Delay time from OSC stop to Mode Register Readout

	  //CRC Error handling Timing parameters 
	  int unsigned ddr5_tcrc_alert_ps;     //!<CRC Alert Delay Time
	  int unsigned ddr5_tcrc_alert_pw_ps;  //!<CRC Alert Pulse Width

    // RCD timing parameters
    // For PHYINIT
    int unsigned ddr5_rcd_tstaoff_ps;
    int unsigned ddr5_rcd_tpdm_ps;
    // For Controller
    int unsigned ddr5_rcd_tstab01_ps;
    int unsigned ddr5_rcd_tpdex_ps;
    int unsigned ddr5_rcd_tcssr_ps;
    int unsigned ddr5_rcd_tcpded2srx_tck;
    int unsigned ddr5_rcd_tsrx2srx_tck;
    int unsigned ddr5_rcd_tckoff_ps;
    int unsigned ddr5_rcd_tckact_tck;
    int unsigned ddr5_rcd_tcsalt_tck;
`endif

`ifdef MEMC_LPDDR4
    // LPDDR4 Timing Parameters
    int unsigned lpddr4_tckb;     //!< Clock cycle time during boot
    int unsigned lpddr4_tpbr2pbr; //!< Per-bank refresh to Per-bank refresh different bank time
    int unsigned lpddr4_tras_min;
    int unsigned lpddr4_tras_max;
    int unsigned lpddr4_trfcab;
    int unsigned lpddr4_trfcpb;
    int unsigned lpddr4_trfiab;
    int unsigned lpddr4_trfipb;
    int unsigned lpddr4_twtr;
    int unsigned lpddr4_tfaw;
    int unsigned lpddr4_tzqreset;
    int unsigned lpddr4_tzqinit;
    int unsigned lpddr4_tzqcs;
    int unsigned lpddr4_tzqcsb;
    int unsigned lpddr4_tzqclb;
    int unsigned lpddr4_tzqcl;
    int unsigned lpddr4_tmrr;
    int unsigned lpddr4_tmrw;
    int unsigned lpddr4_tmrwb;
    int unsigned lpddr4_tmrd;
    int unsigned lpddr4_tmrdb;
    int unsigned lpddr4_tcke;
    int unsigned lpddr4_tckesr;
    int unsigned lpddr4_tccd;
    int unsigned lpddr4_tccdmw;
    int unsigned lpddr4_trtp;
    int unsigned lpddr4_twr;
    int unsigned lpddr4_tppd;
    int unsigned lpddr4_tdqsck;
    int unsigned lpddr4_tdqsck_max;
    int unsigned lpddr4_tdqsck_max_dr;
    int unsigned lpddr4_tosco;
    int unsigned lpddr4_tdqss;
    int unsigned lpddr4_tdqs2dq;
    int unsigned lpddr4_tdipw_ps;
    int unsigned lpddr4_trcd;
    int unsigned lpddr4_trp;
    int unsigned lpddr4_trpa;
    int unsigned lpddr4_trc;
    int unsigned lpddr4_cl;
    int unsigned lpddr4_cl_dbi;
    int unsigned lpddr4_cwl_seta;
    int unsigned lpddr4_cwl_setb;
    int unsigned lpddr4_nrtp;
    int unsigned lpddr4_nwr;
    int unsigned lpddr4_tcmdcke;
    int unsigned lpddr4_tmrwckel;
    int unsigned lpddr4_tmrwckelb;
    int unsigned lpddr4_tckckeh;
    int unsigned lpddr4_tckelck;
    int unsigned lpddr4_tsr;
    int unsigned lpddr4_todton_min;
    int unsigned lpddr4_tvrcg_enable;
    int unsigned lpddr4_tvrcg_disable;
    int unsigned lpddr4_txp;
    int unsigned lpddr4_trrd;
    int unsigned lpddr4_odtloff_latency_seta;
    int unsigned lpddr4_odtloff_latency_setb;
    int unsigned lpddr4_odtlon_latency_seta;
    int unsigned lpddr4_odtlon_latency_setb;
    int unsigned lpddr4_wdqson_seta;
    int unsigned lpddr4_wdqson_setb;
    int unsigned lpddr4_wdqsoff_seta;
    int unsigned lpddr4_wdqsoff_setb;
    int unsigned lpddr_tzqinit_min;
    int unsigned lpddr4_derated_trcd;
    int unsigned lpddr4_derated_tras_min;
    int unsigned lpddr4_derated_trp;
    int unsigned lpddr4_derated_trrd;
    int unsigned lpddr4_derated_trc;

    // LPDDR5 Timing Parameters (generally in ps)
    int unsigned lpddr5_wck_ps;
    int unsigned lpddr5_cl_ps;
    int unsigned lpddr5_cl_dbi_ps;
    int unsigned lpddr5_twtr_s_ps;
    int unsigned lpddr5_twtr_l_ps;
    int unsigned lpddr5_twtr_ps;
    int unsigned lpddr5_tpbr2pbr_ps;
    int unsigned lpddr5_tpbr2act_ps;
    int unsigned lpddr5_trcd_ps;
    int unsigned lpddr5_tccdmw_tck;
    int unsigned lpddr5_trp_ps;
    int unsigned lpddr5_tsr_ps;
    int unsigned lpddr5_txsr_ps;
    int unsigned lpddr5_trfcab_ps;
    int unsigned lpddr5_trfcpb_ps;
    int unsigned lpddr5_tcspd_ps;
    int unsigned lpddr5_tcmpd_ps;
    int unsigned lpddr5_tescke_ps;
    int unsigned lpddr5_tcmdpd_ps;
    int unsigned lpddr5_tcslck_ps;
    int unsigned lpddr5_tckcsh_ps;
    int unsigned lpddr5_txp_ps;
    int unsigned lpddr5_tcsh_ps;
    int unsigned lpddr5_tcsl_ps;
    int unsigned lpddr5_tmrwpd_ps;
    int unsigned lpddr5_tzqpd_ps;
    int unsigned lpddr5_trc_pab_ps;
    int unsigned lpddr5_trc_ppb_ps;
    int unsigned lpddr5_trpab_ps;
    int unsigned lpddr5_trppb_ps;
    int unsigned lpddr5_tras_min_ps;
    int unsigned lpddr5_tras_max_ps;
    int unsigned lpddr5_twr_ps;
    int unsigned lpddr5_tccd_l_tck;   //!< Cas to Cas command delay to same bank group
    int unsigned lpddr5_tccd_s_tck;   //!< Cas to Cas command delay to different bank group
    int unsigned lpddr5_tccd_ps;
    int unsigned lpddr5_trrd_l_ps;  //!< Active bank a to Active bank b command time to same bank group
    int unsigned lpddr5_trrd_s_ps;  //!< Active bank a to Active bank b command time to different bank group
    int unsigned lpddr5_trrd_ps;
    int unsigned lpddr5_tfaw_ps;
    int unsigned lpddr5_trtp_ps;
    int unsigned lpddr5_tppd_tck;
    int unsigned lpddr5_tmrr_tck;
    int unsigned lpddr5_tmrw_ps;
    int unsigned lpddr5_tmrd_ps;
    int unsigned lpddr5_odtloff_tck;
    int unsigned lpddr5_odtlon_tck;
    int unsigned lpddr5_odton_min_ps;
    int unsigned lpddr5_odton_max_ps;
    int unsigned lpddr5_odtoff_min_ps;
    int unsigned lpddr5_odtoff_max_ps;
    int unsigned lpddr5_tzqreset_ps;
    int unsigned lpddr5_tzqlat_ps;
    int unsigned lpddr5_tzqcal_ps;
    int unsigned lpddr5_tzqstop_ps;
    int unsigned lpddr5_tzqoff_us;
    int unsigned lpddr5_tvrcg_enable_ps;
    int unsigned lpddr5_tvrcg_disable_ps;
    // suffix _wck to indicate  units are tWCK
    int unsigned lpddr5_wckenl_rd_wck;
    int unsigned lpddr5_wckpre_rd_static_wck;
    int unsigned lpddr5_wckpre_rd_toggle_wck;
    int unsigned lpddr5_wckenl_wr_seta_wck;
    int unsigned lpddr5_wckenl_wr_setb_wck;
    int unsigned lpddr5_wckpre_wr_static_wck;
    int unsigned lpddr5_wckpre_wr_toggle_wck;
    int unsigned lpddr5_wckpre_static_tck;
    int unsigned lpddr5_wckpre_toggle_wr_tck;
    int unsigned lpddr5_wckpre_toggle_rd_tck;
    int unsigned lpddr5_wckenl_rd_tck;
    int unsigned lpddr5_wckenl_wr_tck;
    int unsigned lpddr5_wckenl_fs_tck;
    int unsigned lpddr5_twck_en_wck;
    int unsigned lpddr5_twck_toggle_en_wck;
    int unsigned lpddr5_twck_toggle_dis_wck;
    int unsigned lpddr5_tpdn_ps;
    int unsigned lpddr5_tpdn_dsm_ms;
    int unsigned lpddr5_txsr_dsm_us;
    int unsigned lpddr5_trbtp_ps;
    int unsigned lpddr5_tespd_ps;
    int unsigned lpddr5_wl_tck;
    int unsigned lpddr5_rl_tck;
    int unsigned lpddr5_nrtp;
    int unsigned lpddr5_nrbtp_ps; //!< READ Burst end to PRECHARGE command delay
    int unsigned lpddr5_nwr;
    int unsigned lpddr5_bl_n_min_tck; //!< Effective burst length
    int unsigned lpddr5_bl_n_max_tck; //!< Effective burst length
    int unsigned lpddr5_twck_pst_wck;
    int unsigned lpddr5_wckdqo_max_ps;
    int unsigned lpddr5_wckdqo_ps;
    int unsigned lpddr5_wckdqi_ps;
    int unsigned lpddr5_trpst;
    int unsigned lpddr5_trefi_ps; //!< all bank average refresh interval
    int unsigned lpddr5_trefipb_ps;  //!< per bank average refresh interval
    int unsigned lpddr5_derated_trcd_ps;
    int unsigned lpddr5_derated_tras_min_ps;
    int unsigned lpddr5_derated_trpab_ps;
    int unsigned lpddr5_derated_trppb_ps;
    int unsigned lpddr5_derated_trrd_ps;
    int unsigned lpddr5_derated_trcab_ps;
    int unsigned lpddr5_derated_trcpb_ps;

`endif
    int unsigned wr2pre;  //!< min time between write and precharge to the same bank


  } ddrTimingParameters_t;
  
  /**
    * @brief Structure containing parameters to program DWC DDR umctl registers.
          * The variables here are pre-calculated timings to help
          * program some register fields.
    */
        typedef struct  {
            int unsigned cl[`UMCTL2_FREQUENCY_NUM]; //! CL
            int unsigned cl_dbi[`UMCTL2_FREQUENCY_NUM]; //!<
            int unsigned cwl_x[`UMCTL2_FREQUENCY_NUM];    //!<  CWL adjusted.
            int unsigned twr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];      //!< Write recovery time
            int unsigned twtr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];     //!< Write to Read command delay
            int unsigned twtr_s[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];   //!<
            int unsigned tfaw[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];     //!< Four Bank Activate window
            int unsigned txp[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];      //!< Exit power down to a valid command
            int unsigned txpdll[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_ras_max[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_ras_min[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_rtp[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_rc[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned wr2rd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned wr2rd_s[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned rd2wr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned rd2wr_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned wdqspreext[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];

            int unsigned odton_min[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned odton[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_mrw[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Mode Register Write command period
            int unsigned t_mr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Load-mode command to next valid command period (tmrd >= tmrw)
            int unsigned t_mod[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_rcd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Active to Read/Write command time
            int unsigned t_ccd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Cas to Cas command delay
            int unsigned t_rrd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Active bank a to Active bank b command time
            int unsigned t_rp[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_cksrx[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_cksre[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_ckesr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_cke[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_csh[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_mrd_pda[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned odtloff[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned odtlon[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_t_rddata_en[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_tphy_wrlat[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned cmd_lat_adder[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_t_dram_clk_disable[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_t_dram_clk_enable[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];

`ifdef UMCTL2_CID_EN
            int unsigned t_ccd_dlr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_rrd_dlr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< ddr4 and ddr5
            int unsigned t_faw_dlr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_faw_slr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_wr2rd_dlr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];  //!< ddr5
            int unsigned t_rd2wr_dlr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< ddr5
            int unsigned t_refsbrd_dlr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_rfcsb_dlr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
`endif

`ifdef MEMC_LPDDR2
            int unsigned derated_t_rcd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned derated_t_ras_min[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned derated_t_rp[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned derated_t_rrd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned derated_t_rc[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned tINITTMG1[`UMCTL2_NUM_DATA_CHANNEL];  //!< min cke low time before RESET_n high
            int unsigned tINITTMG3[`UMCTL2_NUM_DATA_CHANNEL]; //!< min idle time before first MRW/MRR command.
            int unsigned t_pbr2pbr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_pbr2act[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned tINIT2;    //!<
            int unsigned tINIT3;  //!< used post_cke
            int unsigned tINIT4[`UMCTL2_FREQUENCY_NUM]; //!< min idle time before first CKE high.
            int unsigned t_rrd_s[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Activate command to different bank group than prior Activate command
            int unsigned t_osco[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
`endif          

            int unsigned wl[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< write latency
            int unsigned rl[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< read latency
            int unsigned t_rbtp[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< LPDDR5
            int unsigned t_cmdcke[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_vrcg_enable[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_vrcg_disable[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned lpddr4_diff_bank_rwa2pre[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Time between Read/Write/Masked Write/Act and Precharge to diff bank
            int unsigned wra2pre[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Time between write with AP and activate to same bank
            int unsigned rda2pre[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Time between write read AP and activate to same bank.
            int unsigned rd2wr_s[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Minimum time from read command to write command for different bank group
            int unsigned rd2wr_s_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!< Minimum time from read command to write command for different bank group
            int unsigned max_rd_sync[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< Maximum time between read commands without a new WCK2CK sync Start
            int unsigned max_wr_sync[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< Maximum time between write commands without a new WCK2CK sync start
            int unsigned nwr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< nWR
            int unsigned nrtp[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< nRTP
            int unsigned nrbtp[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< nRBTP
            int unsigned dfi_twck_en_rd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_twck_en_wr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_twck_en_fs[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_twck_dis[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_twck_fast_toggle[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_twck_toggle[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_twck_toggle_cs[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned dfi_twck_toggle_post[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned rd2mr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< Time from Read to MRW/MRR command
            int unsigned wr2mr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< Time from Write to MRW/MRR command
            int unsigned mrr2rd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< Time from MRR to Read command
            int unsigned mrr2wr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< Time from MRR to Write command
            int unsigned mrr2wr_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< Time from MRR to Write command
            int unsigned mrr2mrw[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!< Time from MRR to MRW command
            // ddr4
            int unsigned t_xs_fast_min[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned t_xs_min[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            //ddr5
            int unsigned t_pd[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!<tPD  ddr5
            int unsigned t_mpsmx[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!<tMPSMX ddr5
            int unsigned t_mpdpxact[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!<tMPDPADACT ddr5
            int unsigned t_pda_latch[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tPDA_LATCH ddr5
            int unsigned t_pda_delay[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tPDA_DELAY ddr5
            int unsigned t_pda_dqs_delay[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tPDA_DQS_DELAY ddr5
            int unsigned t_pda_s[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<t_pda_s ddr5
            int unsigned t_pda_h[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tPDA_H ddr5

            int unsigned t_cpded[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tCPDED ddr5
            int unsigned t_casrx[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tCASRX ddr5
            int unsigned t_csh_srexit[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tCSH_SRexit ddr5
            int unsigned t_csl_srexit[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tCSl_SRexit ddr5

            int unsigned t_mpc_cs[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!<tMPC_CS ddr5
            int unsigned t_mpc_setup[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tMPC_Setup  ddr5
            int unsigned t_mpc_hold[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!<tMPC_Hold ddr5
            int unsigned t_vrefca_cs[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tVrefCA_CS ddr5
            int unsigned t_mpc_delay[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tMPC_DELAY ddr5
            int unsigned t_osco_ddr5[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tOSCO ddr5
            int unsigned t_ccd_w[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];//!<tCCD_L_WR  write to write same bank group second write write RMW
            int unsigned t_ccd_w2[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!<tCCD_L_WR2 write to write same bank group second write not  RMW
            int unsigned t_wr2rd_dpr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!<wr2rd_dpr
            int unsigned t_rd2wr_dpr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL]; //!<rd2wr_dpr
`ifdef MEMC_NUM_RANKS_GT_1
            int unsigned wr2rd_dr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned rd2wr_dr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned diff_rank_rd_gap[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned diff_rank_wr_gap[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned wr2rd_dr_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned rd2wr_dr_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned diff_rank_rd_gap_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned diff_rank_wr_gap_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned wr2rd_dr_wck_on[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned rd2wr_dr_wck_on[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned diff_rank_rd_gap_wck_on[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned diff_rank_wr_gap_wck_on[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned wr2rd_dr_wck_on_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned rd2wr_dr_wck_on_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned diff_rank_rd_gap_wck_on_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
            int unsigned diff_rank_wr_gap_wck_on_odt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
`endif

    //ddr5 RCD
    int unsigned t_stab01[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
    int unsigned t_cssr[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
    int unsigned t_cpded2srx[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
    int unsigned t_srx2srx[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
    int unsigned t_ckoff[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
    int unsigned t_ckact[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];
    int unsigned t_csalt[`UMCTL2_FREQUENCY_NUM][`UMCTL2_NUM_DATA_CHANNEL];

            int unsigned lpddr5_cdd;
            int unsigned tphy_wckcsgap;

        } mctl_pre_cfg;
  /**
   * @brief Type definition of structure describing mode register fields.
   */

 typedef struct  {
     rand byte wr_recovery;
     rand byte dll_reset;
     rand byte cl;          //!< CAS Latency
     rand byte burst_type;
     rand byte burst_length;
   } ddr4_mr0_t;

 typedef struct  {
     rand byte rtt_nom;
     rand byte wr_leveling_enable;
     rand byte al;
     rand byte output_driver_impedance;
     rand byte dll_enable;
   } ddr4_mr1_t;

 typedef struct  {
     rand byte write_crc;
     rand byte rtt_wr;
     rand byte auto_self_ref;
     rand byte cwl;
   } ddr4_mr2_t;

  typedef struct  {
    rand byte wcl;
    rand byte geardown;
    rand byte mpr_op;
    rand byte mpr_ps;
    rand byte fine_granularity_refresh;
   } ddr4_mr3_t;

 typedef struct  {
   rand byte wr_preamble;
     rand byte rd_preamble;
     rand byte selfref_abort;
     rand byte cal;
     rand byte fgr_mode;
     rand byte refresh_range;
   } ddr4_mr4_t;

 typedef struct  {
     rand byte read_dbi;
     rand byte write_dbi;
     rand byte data_mask;
     rand byte ca_parity_persistent;
     rand byte rtt_park;
     rand byte dis_odt_input_buf_in_pd;
     rand byte parity_latency_mode;
   } ddr4_mr5_t;
 typedef struct  {
     rand byte tccd_l;
   } ddr4_mr6_t;

 // umctl5 ddr5
 ////////////////////////////////////
 typedef struct  {
     rand byte burst_length;
     rand byte cl;  //!<CAS latency
   } ddr5_mr0_t;

 typedef struct  {
     rand byte rd_preamble_enable;
     rand byte wr_leveling;
     rand byte ddr5_2n_mode;
     rand byte mpsm;
     rand byte cs_assertion_duration;
     rand byte dev15_mpsm;
     rand byte internal_wr_timing;
   } ddr5_mr2_t;

 typedef struct  {
     rand byte wr_leveling_internal_lower_byte;
     rand byte wr_leveling_internal_upper_byte;
   } ddr5_mr3_t;

 typedef struct  {
     rand byte refresh_trfc_mode;
     rand byte refresh_rate;
   } ddr5_mr4_t;

 typedef struct  {
     rand byte data_output_disable;
     rand byte pull_up_output_drv_impedance;
     rand byte tdqs_enable;
     rand byte dm_enable;
     rand byte pull_down_output_drv_impedance;
   } ddr5_mr5_t;

 typedef struct  {
     rand byte trtp;
     rand byte wr_recovery;
   } ddr5_mr6_t;

 typedef struct  {
     rand byte rd_preamble;
     rand byte wr_preamble;
     rand byte rd_postamble;
     rand byte wr_postamble;
   } ddr5_mr8_t;

 typedef struct  {
     rand byte tccd_l;
   } ddr5_mr13_t;

 typedef struct  {
     rand byte rtt_park;
     rand byte rtt_wr;
   } ddr5_mr34_t;

 typedef struct  {
     rand byte rtt_nom_wr;
     rand byte rtt_nom_rd;
   } ddr5_mr35_t;

 typedef struct  {
     rand byte odtlon_wr_offset;
     rand byte odtloff_wr_offset;
   } ddr5_mr37_t;

 typedef struct  {
     rand byte odtlon_wr_nt_offset;
     rand byte odtloff_wr_nt_offset;
   } ddr5_mr38_t;

 typedef struct  {
     rand byte odtlon_rd_nt_offset;
     rand byte odtloff_rd_nt_offset;
   } ddr5_mr39_t;

 typedef struct  {
     rand byte rd_dqs_offset;
   } ddr5_mr40_t;

 typedef struct  {
     rand byte osc_run_time;
   } ddr5_mr45_t;

 typedef struct  {
     rand byte rd_crc_enable;
     rand byte wr_crc_enable_lower_nibble;
     rand byte wr_crc_enable_upper_nibble;
     rand byte wr_crc_error_status;
     rand byte wr_crc_auto_disable_enable;
     rand byte wr_crc_auto_disable_status;
   } ddr5_mr50_t;

 typedef struct  {
     rand byte wr_crc_auto_disable_thre;
   } ddr5_mr51_t;

 typedef struct  {
     rand byte wr_crc_auto_disable_window;
   } ddr5_mr52_t;

 typedef struct  {
rand ddr5_mr0_t mr0;
rand ddr5_mr2_t mr2;
rand ddr5_mr3_t mr3;
rand ddr5_mr4_t mr4;
rand ddr5_mr5_t mr5;
rand ddr5_mr6_t mr6;
rand ddr5_mr8_t mr8;
rand ddr5_mr13_t mr13;
rand ddr5_mr34_t mr34;
rand ddr5_mr35_t mr35;
rand ddr5_mr37_t mr37;
rand ddr5_mr38_t mr38;
rand ddr5_mr39_t mr39;
rand ddr5_mr40_t mr40;
rand ddr5_mr45_t mr45;
rand ddr5_mr50_t mr50;
rand ddr5_mr51_t mr51;
rand ddr5_mr52_t mr52;
   } ddr5_mode_registers_t;

 ////////////////////////////////////
  typedef struct  {
    rand byte ca_rate; // 0: SDR, 1: DDR
  } ddr5_rw00_t;

  typedef struct  {
    rand byte parity_check;      // 0: disable, 1: enable
    rand byte alert_n_assertion; // 0: Static ALERT_n Assertion Mode 1: Pulsed ALERT_n Mode
    rand byte alert_n_reenable;  // 0: Parity checking remains disabled after ALERT_n pulse, 1: Parity Checking is re-enabled after ALERT_n pulse
  } ddr5_rw01_t;

  typedef struct  {
    rand byte operating_speed;
  } ddr5_rw05_t;

  typedef struct  {
    rand byte latency_adder_nladd_to_all_dram_cmd;
  } ddr5_rw11_t;

  typedef struct  {
    ddr5_rw00_t rw00;
    ddr5_rw01_t rw01;
    ddr5_rw05_t rw05;
    ddr5_rw11_t rw11;
  } ddr5_control_words_t;

  ////////////////////////////////////
 typedef struct  {
rand ddr4_mr0_t mr0;
rand ddr4_mr1_t mr1;
rand ddr4_mr2_t mr2;
rand ddr4_mr3_t mr3;
rand ddr4_mr4_t mr4;
rand ddr4_mr5_t mr5;
rand ddr4_mr6_t mr6;
 } ddr4_mode_registers_t;

 ////////////////////////////////////
  typedef struct  {
      rand byte rd_postamble;
      rand byte wr_recovery;
      rand byte rd_preamble;
      rand byte wr_preamble;
      rand byte burst_length;
   } lpddr4_mr1_t;

 typedef struct  {
     rand byte wls;
     rand byte rl_wl;
   } lpddr4_mr2_t;

  typedef struct  {
      rand byte write_dbi;
      rand byte read_dbi;
      rand byte wr_postamble;
      rand byte pu_cal;
   } lpddr4_mr3_t;

 typedef struct  {
   rand byte vr_ca;
   rand byte vref_ca;
   } lpddr4_mr12_t;

 typedef struct  {
   rand byte ca_odt;
   rand byte dq_odt;
   } lpddr4_mr11_t;

  typedef struct  {
   rand byte fsp_op;
   rand byte fsp_wr;
   rand byte dmd;
   } lpddr4_mr13_t;

 typedef struct  {
   rand byte vr_dq;
   rand byte vref_dq;
   } lpddr4_mr14_t;

  typedef struct  {
   rand byte odtd;
   rand byte odtd_ca;
   rand byte odtd_cs;
   rand byte odtd_ck;
   rand byte soc_odt;
   } lpddr4_mr22_t;

  typedef struct  {
	 rand byte dqs_interval;
   } lpddr4_mr23_t; 
   
  typedef struct  {
rand lpddr4_mr1_t mr1;
rand lpddr4_mr2_t mr2;
rand lpddr4_mr3_t mr3;
rand lpddr4_mr11_t mr11;
rand lpddr4_mr12_t mr12;
rand lpddr4_mr13_t mr13;
rand lpddr4_mr14_t mr14;
rand lpddr4_mr22_t mr22;
rand lpddr4_mr23_t mr23;
 } lpddr4_mode_registers_t;


  typedef struct  {
    rand byte write_latency;
    rand byte ck_mode;
    rand byte burst_length;
  } lpddr5_mr1_t;

  typedef struct  {
    rand byte nwr;
    rand byte rl_nrtp;
  } lpddr5_mr2_t;

  typedef struct  {
    rand byte write_dbi;
    rand byte read_dbi;
    rand byte wls;
    rand byte bk_bg_org;
    rand byte pdds;
  } lpddr5_mr3_t;

  typedef struct  {
    rand int unsigned rdqs_pst;
    rand int unsigned rdqs_pre;
    rand int unsigned wck_pst;
  } lpddr5_mr10_t;

  typedef struct  {
    rand byte ca_odt;
    rand byte nt_odt;
    rand byte dq_odt;
  } lpddr5_mr11_t;

  typedef struct  {
   rand byte vbs;
   rand byte vref_ca;
  } lpddr5_mr12_t;
  typedef struct  {
   rand byte dual_vdd2;
   rand byte dmd;
   rand byte vro;
   rand byte thermal_offset;
  } lpddr5_mr13_t;

  typedef struct  {
   rand byte vdlc;
   rand byte vref_dq;
  } lpddr5_mr14_t;

  typedef struct  {
   rand byte vref_dq;
  } lpddr5_mr15_t;

  typedef struct  {
   rand byte cbt;
   rand byte vrcg;
   rand byte fsp_op;
   rand byte fsp_wr;
  } lpddr5_mr16_t;

  typedef struct  {
   rand byte odtd;
   rand byte odtd_ca;
   rand byte odtd_ck;
   rand byte soc_odt;
  } lpddr5_mr17_t;

  typedef struct  {
   rand byte ckr;
   rand byte wck2ck_leveling;
   rand byte wck_sync;
   rand byte wck_on;
   rand byte wck_fm;
   rand byte wck_odt;
  } lpddr5_mr18_t;

  typedef struct  {
   rand byte dvfsq;
   rand byte dvfsc;
  } lpddr5_mr19_t;

  typedef struct  {
   rand byte wck_mode;
   rand byte rdqs;
  } lpddr5_mr20_t;
  typedef struct  {
   rand byte dcfe;
   rand byte wxfs;
  } lpddr5_mr21_t;
  typedef struct  {
   rand byte wecc;
   rand byte recc;
  } lpddr5_mr22_t;
  typedef struct  {
   rand byte pasr_mask;
  } lpddr5_mr23_t;
  typedef struct  {
   rand byte ck_bus_term;
   rand byte ca_bus_term;
   rand byte parc;
  } lpddr5_mr25_t;
  typedef struct  {
   rand byte zq_int;
   rand byte zq_stop;
   rand byte zq_reset;
  } lpddr5_mr28_t;
  typedef struct  {
    rand byte wck2dqi_runtime;
  }lpddr5_mr37_t;
  typedef struct  {
    rand byte wck2dqo_runtime;
  }lpddr5_mr40_t;
//todo mr29,mr30,mr31,mr32,mr33,mr34,mr37,mr40
  typedef struct  {
rand lpddr5_mr1_t mr1;
rand lpddr5_mr2_t mr2;
rand lpddr5_mr3_t mr3;
rand lpddr5_mr10_t mr10;
rand lpddr5_mr11_t mr11;
rand lpddr5_mr12_t mr12;
rand lpddr5_mr13_t mr13;
rand lpddr5_mr14_t mr14;
rand lpddr5_mr15_t mr15;
rand lpddr5_mr16_t mr16;
rand lpddr5_mr17_t mr17;
rand lpddr5_mr18_t mr18;
rand lpddr5_mr19_t mr19;
rand lpddr5_mr20_t mr20;
rand lpddr5_mr21_t mr21;
rand lpddr5_mr22_t mr22;
rand lpddr5_mr23_t mr23;
rand lpddr5_mr25_t mr25;
rand lpddr5_mr28_t mr28;
rand lpddr5_mr37_t mr37;
rand lpddr5_mr40_t mr40;
 } lpddr5_mode_registers_t;




`ifdef  __cplusplus
}
`endif
`endif  //__CINIT_TYPES_H__
