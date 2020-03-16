/**

  Functions for DDRdriver

  Copyright (c) 2017-2018 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

  Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

**/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include <string.h>
#include <target/ddr.h>
#include <asm/mach/chipinfo.h>
/*===========================================================================
                                 DATA
===========================================================================*/
/******************************************************************************
* type definition
******************************************************************************/
typedef union
{
    dimm_slot_smbus_info_t smbus_info;
    uint32_t smbus_val;
}dimm_slot_smbus_info_u;

// SPD SMBUS Address Variable bit shift position
#define SPD_BLSP_ADDR_SHFT       12
#define SPD_EEPROM_BUS_ADDR_SHFT 8
#define SPD_TS_BUS_ADDR_SHFT     4
#define SPD_CMD_BUS_ADDR_SHFT    0

// DDR maximum allowed clock speed (in MHz)
#define DDR_MAX_SPEED_JEDEC 1600
#define DDR_MAX_SPEED_1DPC 1333
#define DDR_MAX_SPEED_2DPC 1200

// DDR Temperature event threshold
#define DDR_TCRITIC_TEMP_DEFAULT 95
#define DDR_TCRITIC_TEMP_MAX 125
#define DDR_TCRITIC_TEMP_MIN 0

//Monaco Verbose Logging; 0-false, 1-true
#define MONACO_VERBOSE_LOGGING 0

/*====== Persistent Variable Names =======*/
/* Monaco Log level */
const uint16_t log_level_name[] = L"monaco_log_level";
/* MDDR Variables */
const uint16_t auto_self_refresh_name[] = L"ddr_enable_auto_self_refresh";
const uint16_t ddr_clk_speed_name[] = L"ddr_clock_speed";
const uint16_t ddr_xo_freq_name[] = L"mddr_xo_freq_khz";
const uint16_t extra_dqs_toggle_name[] = L"extra_dqs_toggle";
const uint16_t ddr_periodic_zq_cal_name[] = L"ddr_enable_periodic_zqcal";
const uint16_t ddr_prop_delay_name[] = L"prop_delay";
const uint16_t ddr_clkgen_ssc_enable_name[] = L"clkgen_ssc_en";
const uint16_t ddr_clk_type_name[] = L"clk_type";
const uint16_t ddr_def_1dimm_freq_name[] = L"max_1dimm_clock_speed";
const uint16_t ddr_def_2dimm_freq_name[] = L"max_2dimm_clock_speed";
const uint16_t allow_overclocking_name[] = L"allow_overclocking";
const uint16_t ddr_disable_ecc_name[] = L"disable_ecc";
const uint16_t ddr_ecc_wrrd_mode_name[] = L"ecc_wrrd_mode";
const uint16_t ddr_rs_quad_det_en_name[] = L"rs_quad_det_en";
const uint16_t ddr_patrol_scrub_name[] = L"ddr_disable_patrol_scrub";
const uint16_t ddr_psetting_autochg_name[] = L"ddr_pagesettings_enable_autopchg";
const uint16_t ddr_psetting_policy_name[] = L"ddr_pagesettings_policy";
const uint16_t ddr_psettings_idle_name[] = L"ddr_pagesettings_idle_timer";
const uint16_t ddr_granule_name[] = L"ddr_granule";
const uint16_t ddr_dimm_intlv_en[] = L"dimm_intlv_en";
const uint16_t ddr_rfc_mode_name[] = L"ddr_rfc_mode";
const uint16_t ddr_sr_entry_idle_delay_name[] = L"sr_entry_idle_delay";
const uint16_t ddr_auto_power_down_name[] = L"auto_power_down";
const uint16_t ddr_pd_entry_idle_delay_name[] = L"pd_entry_idle_delay";
const uint16_t ddr_adj_ref_name0[] = L"ddr_adj_ref_dimm0";
const uint16_t ddr_adj_ref_name1[] = L"ddr_adj_ref_dimm1";
const uint16_t ddr_dfi_lp_mode_name[] = L"dfi_lp_mode";
const uint16_t ddr_dfi_lp2_entry_idle_delay_name[] = L"dfi_lp2_entry_idle_delay";
const uint16_t ddr_thermal_throttle_name[] = L"ddr_thermal_throttle";
const uint16_t ddr_2t_preamble_name[] = L"ddr_2t_preamble_mode";
const uint16_t ddr_dbi_mode_name[] = L"ddr_dbi_mode";
const uint16_t ddr_ca_parity_name[] = L"ddr_ca_parity";
const uint16_t ddr_scrambling_name[] = L"ddr_enable_scrambling";
const uint16_t ddr_ca_stretch_name[] = L"ddr_ca_stretch";
const uint16_t ddr_bank_group_decode_name[] = L"bank_group_decode";
const uint16_t ddr_tcrit_event_en_name[] = L"tcrit_event_en";
const uint16_t ddr_tcrit_threshhold_name[] = L"tcrit_threshhold";
const uint16_t ddr_ecc_ce_threshold_name[] = L"ecc_ce_threshold";


const uint16_t ddr_phy_xcnt_name[] = L"XCNT";
const uint16_t ddr_phy_uctl_dmem_40_name[] = L"DDRPHY_UCTL_DMEM_40";
const uint16_t ddr_phy_uctl_dmem_41_name[] = L"DDRPHY_UCTL_DMEM_41";
const uint16_t ddr_phy_uctl_dmem_42_name[] = L"DDRPHY_UCTL_DMEM_42";
const uint16_t ddr_phy_uctl_dmem_43_name[] = L"DDRPHY_UCTL_DMEM_43";


const uint16_t ddr_bum_bcqfull_enable_name[] = L"ddr_bum_bcqfull_ena";
const uint16_t ddr_bum_bcqfull_hithresh_name[] = L"ddr_bum_bcqfull_hithresh";
const uint16_t ddr_bum_bcqfull_lothresh_name[] = L"ddr_bum_bcqfull_lothresh";
const uint16_t ddr_bum_busy_enable_name[] = L"ddr_bum_busy_ena";
const uint16_t ddr_bum_busy_hithresh_name[] = L"ddr_bum_busy_hithresh";
const uint16_t ddr_bum_busy_lothresh_name[] = L"ddr_bum_busy_lothresh";

/* DDR Compression Variables */
const uint16_t comp_mode_name[] = L"comp_mode";
const uint16_t decomp_comp_name[] = L"decomp_comp";
const uint16_t cde_comprd_hi_threshold_name[] = L"cde_comprd_hi_threshold";
const uint16_t cde_comprd_lo_threshold_name[] = L"cde_comprd_lo_threshold";
const uint16_t cde_rd_window_size_name[] = L"cde_rd_window_size";
const uint16_t cde_rd_hist_threshold_name[] = L"cde_rd_hist_threshold";
const uint16_t cde_rd_hist_size_name[] = L"cde_rd_hist_size";
const uint16_t cde_wdb_rd_mode_name[] = L"cde_wdb_rd_mode";
const uint16_t cde_qsb_rd_mode_name[] = L"cde_qsb_rd_mode";
/* Ring Switch Variables */
const uint16_t rs_sbrce_ena_name[]=L"rs_sbrce_ena";
const uint16_t rs_sbrlvl_name[]=L"rs_sbrlvl";
const uint16_t rs_sbrmsk_name[]=L"rs_sbrmsk";
const uint16_t rs_dlbu_ena_name[]=L"rs_dlbu_ena";
const uint16_t rs_eroute_ena_name[]=L"rs_eroute_ena";
const uint16_t rs_lfsr_ena_name[]=L"rs_lfsr_ena";
const uint16_t clkon_req_ena_name[] = L"clkon_req_ena";
const uint16_t clkon_delay_name[] = L"clkon_delay";
const uint16_t clkon_hysteresis_name[] = L"clkon_hysteresis";
const uint16_t rs_bum_ena_name[] = L"rs_bum_ena";
const uint16_t rs_perfndx_max_name[] = L"rs_perfndx_max";
const uint16_t rs_bum_mbsu_rx_hithresh_name[] = L"rs_bum_mbsu_rx_hithresh";
const uint16_t rs_bum_mbsu_rx_lothresh_name[] = L"rs_bum_mbsu_rx_lothresh";
const uint16_t rs_bum_mbsu_tx_hithresh_name[] = L"rs_bum_mbsu_tx_hithresh";
const uint16_t rs_bum_mbsu_tx_lothresh_name[] = L"rs_bum_mbsu_tx_lothresh";
const uint16_t rs_bum_dmsu_rx_hithresh_name[] = L"rs_bum_dmsu_rx_hithresh";
const uint16_t rs_bum_dmsu_rx_lothresh_name[] = L"rs_bum_dmsu_rx_lothresh";
const uint16_t rs_bum_dmsu_tx_hithresh_name[] = L"rs_bum_dmsu_tx_hithresh";
const uint16_t rs_bum_dmsu_tx_lothresh_name[] = L"rs_bum_dmsu_tx_lothresh";
const uint16_t rs_bum_pbsu_rx_hithresh_name[] = L"rs_bum_pbsu_rx_hithresh";
const uint16_t rs_bum_pbsu_rx_lothresh_name[] = L"rs_bum_pbsu_rx_lothresh";
const uint16_t rs_bum_pbsu_tx_hithresh_name[] = L"rs_bum_pbsu_tx_hithresh";
const uint16_t rs_bum_pbsu_tx_lothresh_name[] = L"rs_bum_pbsu_tx_lothresh";
const uint16_t rs_bum_mcsu_rx_hithresh_name[] = L"rs_bum_mcsu_rx_hithresh";
const uint16_t rs_bum_mcsu_rx_lothresh_name[] = L"rs_bum_mcsu_rx_lothresh";
const uint16_t rs_bum_mcsu_tx_hithresh_name[] = L"rs_bum_mcsu_tx_hithresh";
const uint16_t rs_bum_mcsu_tx_lothresh_name[] = L"rs_bum_mcsu_tx_lothresh";

/*  L3 variables   */
const uint16_t l3_snoop_fltr_name[] = L"l3_snoop_fltr_en";
const uint16_t l3_affirnity_name[] = L"l3_affinity";
const uint16_t l3_ll_query_name[] = L"l3_enable_ll_query";
const uint16_t l3_ll_breaker_name[] = L"l3_ll_breaker_en";
const uint16_t l3_addr_hash_en_name[] = L"l3_addr_hash_en";
const uint16_t l3_auto_clock_gating_name[] = L"l3_enable_auto_clock_gating";
const uint16_t l3_auto_clock_gating_cycle_name[] = L"l3_auto_clock_gating_cycles";
const uint16_t l3_rplcmnt_policy_name[] = L"l3_rplcmnt_policy";
const uint16_t l3_cache_cap_mon_en_name[] = L"l3_cache_cap_mon_en";
const uint16_t monaco_ast_interleaves_name[] = L"monaco_ast_intrlv";
const uint16_t monaco_ast_allocation[] = L"monaco_ast_l3_allocation";

const uint16_t ddr_margin_mode_ena_name[] = L"ddr_margining";

/******************************************************************************
* Global Variables
******************************************************************************/
ddr_func_tbl ddr_function_table;
monaco_init_t monaco_cfg;
bool ddr_margin_mode_ena=false;
// DDR Margining Result Base Address
unsigned long ddr_margining_result = 0;
// DDR SI Base Address
unsigned long ddrsi_base = 0;
// Default values for SMBUS I2C addresses
extern dimm_slot_smbus_info_t smbus_default_val[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];

// Default values for DDR Compression
static mddr_comp_settings_t comp_default_val[]=
{
    {DDR_COMP_DISABLED, COMP_DECOMP_OFF,
    0x1,0,0x20,0,0x4,
    RD_UNCOMPRESSED, RD_UNCOMPRESSED},

    {DDR_COMP_STATIC, COMP_DECOMP_ON,
    0x1,0,0x20,0,0x4,
    RD_COMPRESSED, RD_COMPRESSED},

    {DDR_COMP_ADAPTIVE, COMP_DECOMP_ON,
    0x1,0,0x20,0,0x4,
    RD_GLBL_ADAPTIVE_TRK_QSB_WDB, RD_GLBL_ADAPTIVE_TRK_QSB_WDB}
};

// Default values for Ring Switch BUM
static rs_bum_thresh_t rs_bum_thresh_default[4]=
{
    {{0x01,0x04,0x07,0x0A,0x0D,0x10,0x13},
    {0x03,0x06,0x09,0x0C,0x0F,0x12,0x15},
    {0x01,0x04,0x07,0x0A,0x0D,0x10,0x13},
    {0x03,0x06,0x09,0x0C,0x0F,0x12,0x15}},
    {{0x01,0x04,0x07,0x0A,0x0D,0x10,0x13},
    {0x03,0x06,0x09,0x0C,0x0F,0x12,0x15},
    {0x01,0x04,0x07,0x0A,0x0D,0x10,0x13},
    {0x03,0x06,0x09,0x0C,0x0F,0x12,0x15}},
    {{0x01,0x04,0x07,0x0A,0x0D,0x10,0x13},
    {0x03,0x06,0x09,0x0C,0x0F,0x12,0x15},
    {0x01,0x04,0x07,0x0A,0x0D,0x10,0x13},
    {0x03,0x06,0x09,0x0C,0x0F,0x12,0x15}},
    {{0x01,0x09,0x11,0x19,0x21,0x29,0x31},
    {0x08,0x10,0x18,0x20,0x28,0x30,0x38},
    {0x01,0x09,0x11,0x19,0x21,0x29,0x31},
    {0x08,0x10,0x18,0x20,0x28,0x30,0x38}}
};

// Default values for Ring Switch BUM
static uint32_t ddr_bum_thresh_default[DDR_BUM_PERF_IDX_MAX]=
{
    0x00,0x00,0x00,0x00
};

// Default values for DDR OEM Configuration
MddrHobData_t defaultMddrHobData=
{
    {
        DB_BURST_LEN_BL8   // ddr_pagesettings_burst_len
    },
    {
        false               // ddr_shared_dimm_clk
    }
};


// DDR Training Firmware header
ddr4_fwimg_hdr_type ddr4_fwimg_hdr;
ddr4_fwimg_offset_type ddr4_fwimg_offset;

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/
static void monaco_read_l3_configuration(l3_settings_t *l3_settings_p);
static void monaco_read_mddr_configuration(mddr_settings_t *mddr_settings_p);
static void monaco_read_comp_configuration(mddr_comp_settings_t *comp_settings_p);
static void monaco_read_ring_configuration(rs_settings_t *ring_settings_p);

#ifdef HARVEST
void monaco_read_smbus_configuration(dimm_slot_smbus_info_t *smbus_info_p);
#endif

static void monaco_read_log_level(importance_t *log_level);
void get_persistent_boolean(const uint16_t* name, bool* var, bool default_val);
void get_persistent_byte(const uint16_t* name, uint8_t* var, uint8_t default_val);
void get_persistent_uint16(const uint16_t* name, uint16_t* var, uint16_t default_val);
void get_persistent_uint32(const uint16_t* name, uint32_t* var, uint32_t default_val);
void get_persistent_uint64(const uint16_t* name, uint64_t* var, uint64_t default_val);
void get_persistent_block(const uint16_t* name, void* var, void* default_val, uint32_t var_size);
void get_secured_boolean(const uint16_t* name, bool* var, bool default_val);
void get_secured_byte(const uint16_t* name, uint8_t* var, uint8_t default_val);
void get_secured_uint16(const uint16_t* name, uint16_t* var, uint16_t default_val);
void get_secured_uint32(const uint16_t* name, uint32_t* var, uint32_t default_val);
void get_secured_uint64(const uint16_t* name, uint64_t* var, uint64_t default_val);
void get_secured_block(const uint16_t* name, void* var, void* default_val, uint32_t var_size);

#ifdef HARVEST
void get_smbus_configuration(monaco_init_t* init_parms, uint64_t spd_base)
{
    /* SMBus api */
    ddr_function_table.smbus.read_data_byte = &xbl_smbus_read_cached_data_byte;
    ddr_function_table.smbus.read_data_word = &xbl_smbus_read_cached_data_word;
    ddr_function_table.smbus.block_read = &xbl_smbus_read_cached_generic;

    monaco_read_smbus_configuration((dimm_slot_smbus_info_t*)init_parms->spd_smbus_info);
#ifndef CONFIG_TESTOS_EMU
    monaco_spd_cached_init((dimm_slot_smbus_info_t*)init_parms->spd_smbus_info, spd_base);
#endif
    spd_init(init_parms->mode, init_parms->spd_smbus_info);
}

/* ============================================================================
**  Function : ddr_initialize_common
** ============================================================================
*/
/*!
*   @brief
*   This function consolidates all of the common initialization of ddr.
*/
int ddr_initialize_common(uint64_t cpu_pg, uint64_t l3_pg, uint64_t ddr_fw_base, bool cold_boot)
{
    int ret;
    DIEINFO_PROPS DieInfo;

    get_socket_info(&DieInfo, 0);
    qmemset((void *)&monaco_cfg, 0x00, sizeof(monaco_init_t));
#ifdef CONFIG_TESTOS_EMU
    /*palladium is 1DPC*/
    monaco_cfg.mddr_settings.num_dimm_slots=1;
#else
    //now we are in rep platform ,so it is 2DPC, need to fix future.
    monaco_cfg.mddr_settings.num_dimm_slots=2;
#endif
    /* SMBus api */
    ddr_function_table.smbus.write_data_byte = &xbl_smbus_write_data_byte;
    ddr_function_table.smbus.write_data_word = &xbl_smbus_write_data_word;
    ddr_function_table.smbus.block_write = &xbl_smbus_write_generic;

    /* Util api */
    ddr_function_table.util.wait_us = &xbl_wait_us;

    /**********************************************************************/
    /* Read user configurable parameters from persistent variable storage */
    /**********************************************************************/
    monaco_read_l3_configuration(&monaco_cfg.l3_settings);
    monaco_read_mddr_configuration(&monaco_cfg.mddr_settings);
    monaco_read_comp_configuration(&monaco_cfg.mddr_settings.comp_settings);
    monaco_read_ring_configuration(&monaco_cfg.rs_settings);
    monaco_read_log_level(&monaco_cfg.log_level);

    /* Set Partial Goods information */
    monaco_cfg.goods.hydra_cores = cpu_pg;
    monaco_cfg.goods.l3_interleaves = l3_pg;

    /**********************************************************************/
    /* Read SOC HW Version */
    /**********************************************************************/
    monaco_cfg.soc_hw_version.major_version = DieInfo.MajorVersion;
    monaco_cfg.soc_hw_version.minor_version = DieInfo.MinorVersion;
    monaco_cfg.soc_hw_version.aux_version = DieInfo.PackageSubstrate;
#ifndef CONFIG_TESTOS_EMU
    /**********************************************************************/
    /* Initialize DDR Training Firmware */
    /**********************************************************************/
    monaco_init_ddr4_image(ddr_fw_base);
#endif
    ret= monaco_initialize_target(&monaco_cfg, cold_boot);

    return ret;
}
#endif

/*!****************************************************************************
*
* @par Description:
*    This function sets the DDR clock frequency using the CoreBSP clock drivers.
*     The clock drivers are packaged in the CoreBSP single instance wrapper to
*     allow the selection of clock driver based on IMC boot versus IMC runtime
*     context.
*
*                                  @param
*    settings_ptr         Pointer to MDDR settings structure that is
*                          the destination of the copy.
*
*
* @return
*    COM_OK on success; COM_ERROR otherwise
*
* @author
*    wils
*
******************************************************************************/
#ifdef HARVEST
unsigned mddr_set_clock_frequency(UNUSED_PARAM mddr_settings_t *mddr_settings_ptr)
{
    return COM_OK;
}
#endif

/* ============================================================================
**  Function : monaco_read_log_level
** ============================================================================
*/
/*!
*   @brief
*   This function read logl level from persistent storage.
*   If it doesn't exist, set the default value.
*/
static void monaco_read_log_level(importance_t *log_level)
{
    uint32_t log_level_temp;
    /* LOG_LEVEL */
    get_persistent_uint32(log_level_name, (uint32_t *)&log_level_temp, HIGH);

    if ((!MONACO_VERBOSE_LOGGING) && (log_level_temp < MEDIUM)) {
        *log_level = MEDIUM;
    } else {
        *log_level = log_level_temp;
    }
}

/* ============================================================================
**  Function : monaco_read_l3_configuration
** ============================================================================
*/
/*!
*   @brief
*   This function read l3 related configuration from persistent storage.
*   If it doesn't exist, set the default value.
*/
static void monaco_read_l3_configuration(l3_settings_t *l3_settings_p)
{
    uint8_t byte_temp;

    /**********  User MDDR Variable group **********/
    /* L3 AFFINITY */
    get_persistent_boolean(l3_affirnity_name, &l3_settings_p->affinity, false);
    /* L3 CLOCK AUTOGATING ENABLE */
    get_persistent_boolean(l3_auto_clock_gating_name, &l3_settings_p->auto_gate_clk_en, true);
    /* L3 CLOCK AUTOGATING CYCLE COUNT */
    get_persistent_uint32(l3_auto_clock_gating_cycle_name,&l3_settings_p->auto_gate_idle_clk_cyc_cnt, 0);
    /* L3 CACHE REPLACEMENT POLICY*/
    get_persistent_uint32(l3_rplcmnt_policy_name, (uint32_t *)&l3_settings_p->rplcmnt_policy, LRU);
    if (l3_settings_p->rplcmnt_policy != RANDOM
        && l3_settings_p->rplcmnt_policy != LRU)
    {
        monaco_log(CRITICAL,"Invalid L3 replacement policy %d, use default\n", l3_settings_p->rplcmnt_policy);
        l3_settings_p->rplcmnt_policy = LRU;
    }
    /* L3 ADDRESS HASH ENABLE*/
    get_persistent_boolean(l3_addr_hash_en_name, &l3_settings_p->addr_hash_en, true);
    /* L3 CACHE CAPACITY MONITOR  ENABLE */
    get_persistent_boolean(l3_cache_cap_mon_en_name, &l3_settings_p->cache_cap_mon_en, true);

    /**********  Internal MDDR Variable group  **********/
    /* L3 SNOOP FILTER ENABLE */
    get_secured_boolean(l3_snoop_fltr_name, &l3_settings_p->snoop_fltr_en, true);
    /* TRACE INTERLEAVES FOR AST */
    get_secured_uint32(monaco_ast_interleaves_name, &l3_settings_p->trace_settings.trace_interleaves, 0);
    /* INTERLEAVE ALLOCATION FOR AST */
    get_secured_byte(monaco_ast_allocation, &byte_temp, 0);
    // Convert the allocation percentage to a enum value
    if(byte_temp >= 50)
    {
        l3_settings_p->trace_settings.allocation = ALLOCATE_50_PERCENT;
    }
    else if (byte_temp >= 25)
    {
        l3_settings_p->trace_settings.allocation = ALLOCATE_25_PERCENT;
    }
    else
    {
        l3_settings_p->trace_settings.allocation = ALLOCATE_0_PERCENT;
    }
    /* L3 LIVE LOCK ADRESS PHASE QUERY ENABLE*/
    get_secured_boolean(l3_ll_query_name, &l3_settings_p->LL_query_en, true);
    /* L3 LIVE LOCK BREAKER ENABLE*/
    get_secured_boolean(l3_ll_breaker_name, &l3_settings_p->LL_breaker_en, true);
}

/* ============================================================================
**  Function : monaco_read_comp_configuration
** ============================================================================
*/
/*!
*   @brief
*   This function BW compression related configuration from persistent storage.
*   If it doesn't exist, set the default value.
*/
static void monaco_read_comp_configuration(mddr_comp_settings_t *comp_settings_p)
{
    /**********  User MDDR Variable group **********/
    /* COMPRESSION MODE */
    get_persistent_uint32(comp_mode_name, &comp_settings_p->comp_mode, DDR_COMP_DISABLED);
    if (comp_settings_p->comp_mode >= DDR_COMP_NUM_TYPES) {
        monaco_log(CRITICAL,"Invalid compression mode %d, use default\n", comp_settings_p->comp_mode);
        comp_settings_p->comp_mode = DDR_COMP_DISABLED;
    }
    /* COMPRESSION READ HI THRESHOLD */
    get_persistent_uint16(cde_comprd_hi_threshold_name, &comp_settings_p->cde_comprd_hi_threshold
        , comp_default_val[comp_settings_p->comp_mode].cde_comprd_hi_threshold);
    if (comp_settings_p->cde_comprd_hi_threshold < CDE_COMPRD_HI_THRESHOLD_MIN) {
        monaco_log(CRITICAL,"Invalid compression hi threshold %d, use default\n", comp_settings_p->cde_comprd_hi_threshold);
        comp_settings_p->cde_comprd_hi_threshold = comp_default_val[comp_settings_p->comp_mode].cde_comprd_hi_threshold;
    }
    /* COMPRESSION READ LO THRESHOLD */
    get_persistent_uint16(cde_comprd_lo_threshold_name, &comp_settings_p->cde_comprd_lo_threshold
        , comp_default_val[comp_settings_p->comp_mode].cde_comprd_lo_threshold);
    if (comp_settings_p->cde_comprd_lo_threshold > CDE_COMPRD_LO_THRESHOLD_MAX) {
        monaco_log(CRITICAL,"Invalid compression lo threshold %d, use default\n", comp_settings_p->cde_comprd_lo_threshold);
        comp_settings_p->cde_comprd_lo_threshold = comp_default_val[comp_settings_p->comp_mode].cde_comprd_lo_threshold;
    }
    /* COMPRESSION READ WINDOW SIZE */
    get_persistent_uint16(cde_rd_window_size_name, &comp_settings_p->cde_rd_window_size
        , comp_default_val[comp_settings_p->comp_mode].cde_rd_window_size);
    if (comp_settings_p->cde_rd_window_size < CDE_RD_WINDOW_SIZE_MIN) {
        monaco_log(CRITICAL,"Invalid compression read window %d, use default\n", comp_settings_p->cde_rd_window_size);
        comp_settings_p->cde_rd_window_size = comp_default_val[comp_settings_p->comp_mode].cde_rd_window_size;
    }
    /* COMPRESSION READ HISTORY THRESHOLD */
    get_persistent_uint16(cde_rd_hist_threshold_name, &comp_settings_p->cde_rd_hist_threshold
        , comp_default_val[comp_settings_p->comp_mode].cde_rd_hist_threshold);
    if (comp_settings_p->cde_rd_hist_threshold > CDE_RD_HIST_THRESHOLD_MAX) {
        monaco_log(CRITICAL,"Invalid compression history threshold %d, use default\n", comp_settings_p->cde_rd_hist_threshold);
        comp_settings_p->cde_rd_hist_threshold = comp_default_val[comp_settings_p->comp_mode].cde_rd_hist_threshold;
    }
    /* COMPRESSION READ HISTORY SIZE */
    get_persistent_uint16(cde_rd_hist_size_name, &comp_settings_p->cde_rd_hist_size
        , comp_default_val[comp_settings_p->comp_mode].cde_rd_hist_size);
    if (comp_settings_p->cde_rd_hist_size > CDE_RD_HIST_SIZE_MAX
       || comp_settings_p->cde_rd_hist_size < CDE_RD_HIST_SIZE_MIN)
    {
        monaco_log(CRITICAL,"Invalid compression history size %d, use default\n", comp_settings_p->cde_rd_hist_size);
        comp_settings_p->cde_rd_hist_size = comp_default_val[comp_settings_p->comp_mode].cde_rd_hist_size;
    }
    /**********  Internal MDDR Variable group  **********/
    /* DECOMPRESSION MODE */
    get_secured_uint32(decomp_comp_name, &comp_settings_p->decomp_comp
        , comp_default_val[comp_settings_p->comp_mode].decomp_comp);
    if (comp_settings_p->decomp_comp >= COMP_DECOMP_NUM_TYPES) {
        monaco_log(CRITICAL,"Invalid compression type %d, use default\n", comp_settings_p->decomp_comp);
        comp_settings_p->decomp_comp = comp_default_val[comp_settings_p->comp_mode].decomp_comp;
    }
    /* COMPRESSION WDB READ MORE SELECTION*/
        comp_settings_p->cde_wdb_rd_mode = comp_default_val[comp_settings_p->comp_mode].cde_wdb_rd_mode;
    /* COMPRESSION QSB READ MORE SELECTION*/
        comp_settings_p->cde_qsb_rd_mode = comp_default_val[comp_settings_p->comp_mode].cde_qsb_rd_mode;
    }

/* ============================================================================
**  Function : monaco_read_ring_configuration
** ============================================================================
*/
/*!
*   @brief
*   This function read ring related configuration from persistent storage.
*   If it doesn't exist, set the default value.
*/
static void monaco_read_ring_configuration(rs_settings_t *ring_settings_p)
{
    /**********  User MDDR Variable group **********/
    /* CLKON REQ_ENA */
    get_persistent_boolean(clkon_req_ena_name, &ring_settings_p->rs_clkon_req_ena, true);
    /* CLKON HYSTERESIS */
    get_persistent_uint32(clkon_hysteresis_name, &ring_settings_p->rs_clkon_hysteresis, 0x3FF);
    if (ring_settings_p->rs_clkon_hysteresis > 0x3FF) {
        monaco_log(CRITICAL,"Invalid clock on hysteresis %d, use 0x3FF\n", ring_settings_p->rs_clkon_hysteresis);
        ring_settings_p->rs_clkon_hysteresis = 0x3FF;
    }
    /* RS BUM ENABLE */
    get_persistent_boolean(rs_bum_ena_name, &ring_settings_p->rs_bum_ena, false);

    /**********  Internal MDDR Variable group  **********/
#ifdef CONFIG_TESTOS_EMU
    /* RS SECONDARY BACKOFF REQUEST ENABLE */
    ring_settings_p->rs_sbrce_ena = false;
    /* RS DEAD LOCK BREAKER ENABLE */
    ring_settings_p->rs_dlbu_ena = false;
    /* RS EROUTE ENABLE */
    ring_settings_p->rs_eroute_ena = true;
#else
    //silicon version name
    if(CHIPINFO_MAJOR_VERSION(get_version()) == 1)
    {
        /* RS SECONDARY BACKOFF REQUEST ENABLE */
        get_secured_boolean(rs_sbrce_ena_name, &ring_settings_p->rs_sbrce_ena, false);
        /* RS DEAD LOCK BREAKER ENABLE */
        get_secured_boolean(rs_dlbu_ena_name, &ring_settings_p->rs_dlbu_ena, false);
        /* RS EROUTE ENABLE */
        get_secured_boolean(rs_eroute_ena_name, &ring_settings_p->rs_eroute_ena, true);
    }
    else
    {
        /* RS SECONDARY BACKOFF REQUEST ENABLE */
        get_secured_boolean(rs_sbrce_ena_name, &ring_settings_p->rs_sbrce_ena, true);
        /* RS SECONDARY BACKOFF REQUEST LEVEL*/
        get_secured_uint32(rs_sbrlvl_name, &ring_settings_p->rs_sbrlvl, RS_SBRLVL_0);
        /* RS SECONDARY BACKOFF REQUEST MASK*/
        get_secured_uint32(rs_sbrmsk_name, &ring_settings_p->rs_sbrmsk, 0);
        /* RS DEAD LOCK BREAKER ENABLE */
        get_secured_boolean(rs_dlbu_ena_name, &ring_settings_p->rs_dlbu_ena, true);
        /* RS EROUTE ENABLE */
        get_secured_boolean(rs_eroute_ena_name, &ring_settings_p->rs_eroute_ena, false);
    }
#endif
    /* RS LFSR ENABLE */
    get_secured_boolean(rs_lfsr_ena_name, &ring_settings_p->rs_lfsr_ena, true);
    /* CLKON DELAY */
    get_secured_uint32(clkon_delay_name, &ring_settings_p->rs_clkon_delay, 0x5);
    /* RS PERFORMANCE INDEX MAX */
    get_secured_uint32(rs_perfndx_max_name, &ring_settings_p->rs_perfndx_max, RS_BUM_PERFNDX_MAX);
    /* RS BUM MBSU THRESHOLD */
    get_secured_block(rs_bum_mbsu_rx_hithresh_name, &ring_settings_p->rs_bum_thresh[0].rx_hi_thresh
                        ,&rs_bum_thresh_default[0].rx_hi_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_mbsu_rx_lothresh_name, &ring_settings_p->rs_bum_thresh[0].rx_lo_thresh
                        , &rs_bum_thresh_default[0].rx_lo_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_mbsu_tx_hithresh_name, &ring_settings_p->rs_bum_thresh[0].tx_hi_thresh
                        ,&rs_bum_thresh_default[0].tx_hi_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_mbsu_tx_lothresh_name, &ring_settings_p->rs_bum_thresh[0].tx_lo_thresh
                        , &rs_bum_thresh_default[0].tx_lo_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    /* RS BUM DMSU THRESHOLD */
    get_secured_block(rs_bum_dmsu_rx_hithresh_name, &ring_settings_p->rs_bum_thresh[1].rx_hi_thresh
                        , &rs_bum_thresh_default[1].rx_hi_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_dmsu_rx_lothresh_name, &ring_settings_p->rs_bum_thresh[1].rx_lo_thresh
                        , &rs_bum_thresh_default[1].rx_lo_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_dmsu_tx_hithresh_name, &ring_settings_p->rs_bum_thresh[1].tx_hi_thresh
                        , &rs_bum_thresh_default[1].tx_hi_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_dmsu_tx_lothresh_name, &ring_settings_p->rs_bum_thresh[1].tx_lo_thresh
                        , &rs_bum_thresh_default[1].tx_lo_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    /* RS BUM PBSU THRESHOLD */
    get_secured_block(rs_bum_pbsu_rx_hithresh_name, &ring_settings_p->rs_bum_thresh[2].rx_hi_thresh
                        , &rs_bum_thresh_default[2].rx_hi_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_pbsu_rx_lothresh_name, &ring_settings_p->rs_bum_thresh[2].rx_lo_thresh
                        , &rs_bum_thresh_default[2].rx_lo_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_pbsu_tx_hithresh_name, &ring_settings_p->rs_bum_thresh[2].tx_hi_thresh
                        , &rs_bum_thresh_default[2].tx_hi_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_pbsu_tx_lothresh_name, &ring_settings_p->rs_bum_thresh[2].tx_lo_thresh
                        , &rs_bum_thresh_default[2].tx_lo_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    /* RS BUM MCSU THRESHOLD */
    get_secured_block(rs_bum_mcsu_rx_hithresh_name, &ring_settings_p->rs_bum_thresh[3].rx_hi_thresh
                        , &rs_bum_thresh_default[3].rx_hi_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_mcsu_rx_lothresh_name, &ring_settings_p->rs_bum_thresh[3].rx_lo_thresh
                        , &rs_bum_thresh_default[3].rx_lo_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_mcsu_tx_hithresh_name, &ring_settings_p->rs_bum_thresh[3].tx_hi_thresh
                        , &rs_bum_thresh_default[3].tx_hi_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));
    get_secured_block(rs_bum_mcsu_tx_lothresh_name, &ring_settings_p->rs_bum_thresh[3].tx_lo_thresh
                        , &rs_bum_thresh_default[3].tx_lo_thresh, RS_BUM_PERFNDX_MAX*sizeof(uint32_t));

}

/* ============================================================================
**  Function : monaco_read_smbus_configuration
** ============================================================================
*/
/*!
*   @brief
*   This function read smbus related configuration from persistent storage.
*   If it doesn't exist, set the default value.
*/
#ifdef HARVEST
void monaco_read_smbus_configuration(dimm_slot_smbus_info_t *smbus_info_p)
{
    dimm_slot_smbus_info_t *hobData;
    hobData = &smbus_default_val[0][0];
    memcpy(smbus_info_p, hobData, sizeof(dimm_slot_smbus_info_t)* DDR_MAX_NUM_CHANS*DDR_MAX_NUM_SLOTS_PER_CHAN );
}
#endif

/* ============================================================================
**  Function : monaco_read_mddr_configuration
** ============================================================================
*/
/*!
*   @brief
*   This function read monaco ddr related configuration from persistent storage.
*   If it doesn't exist, set the default value.
*/
static void monaco_read_mddr_configuration(mddr_settings_t *mddr_settings_p)
{
#ifdef HARVEST
    mddr_settings_p->page_settings.burst_len_mode = DB_BURST_LEN_OTF;
    mddr_settings_p->shared_dimm_clk = false;

    /**********  Non-Varibale initialization  **********/
    /* DDR CALIBRATION MODE*/
    mddr_settings_p->ddr4_cal_mode_en=false;
    /* DDR GEAR DOWN MNODE ENABLE*/
    mddr_settings_p->ddr4_geardown_mode_en= false;
    /* DDR WRITE CRC ENABLE*/
    mddr_settings_p->ddr4_wr_crc_en = false;
#endif

    /**********  Internal MDDR Variable group  **********/
    /* ALLOW OVERCLOCKING */
    get_secured_boolean(allow_overclocking_name, &mddr_settings_p->allow_overclocking, false);
    /* MDDR XO FREQ */
    get_secured_uint16(ddr_xo_freq_name ,(uint16_t *)&mddr_settings_p->mddr_xo_freq_khz, 20000);
    /* MDDR EXTRA DQS TOGGLE */
    get_secured_byte(extra_dqs_toggle_name ,(uint8_t *)&mddr_settings_p->extra_dqs_toggle, 0);
    if (mddr_settings_p->extra_dqs_toggle > EXTRA_DQS_TOGGLE_MAX) {
        monaco_log(CRITICAL,"Invalid extra DQS toggle %d, use 0\n", mddr_settings_p->extra_dqs_toggle);
        mddr_settings_p->extra_dqs_toggle = 0;
    }
    /* DDR PERIODIC ZQ CAL */
    get_secured_boolean(ddr_periodic_zq_cal_name ,&mddr_settings_p->periodic_zq_cal_en, true);
    /* DDR PROPAGATION DELAY */
    get_secured_byte(ddr_prop_delay_name ,&mddr_settings_p->prop_delay, 0x10);
    /* DDR CLKGEN SSC ENABLE*/
    get_secured_boolean(ddr_clkgen_ssc_enable_name ,&mddr_settings_p->clkgen_ssc_en, true);
    /* DDR CLKGEN SSC ENABLE*/
    get_secured_uint32(ddr_clk_type_name ,&mddr_settings_p->clk_type, CLK_INTERNAL_CLKGEN);
    if (mddr_settings_p->clk_type >= CLK_NUM_TYPES) {
        monaco_log(CRITICAL,"Invalid clk type %d, use CLK_INTERNAL_CLKGEN\n", mddr_settings_p->clk_type);
        mddr_settings_p->clk_type = CLK_INTERNAL_CLKGEN;
    }
    /* DDR THERMAL THROTTLE ENABLE*/
    get_secured_boolean(ddr_thermal_throttle_name, &mddr_settings_p->therm_throttle_en, false);
    /* DDR ADDR DECEOD MODE*/
    get_secured_uint32(ddr_bank_group_decode_name, &mddr_settings_p->bank_group_decode,ADDR_DECODE_BG_MCA_16_7);
    if (mddr_settings_p->bank_group_decode >= ADDR_DECODE_BG_NUM_TYPES) {
        monaco_log(CRITICAL,"Invalid bank group decode value %d, use ADDR_DECODE_BG_MCA_16_7\n", mddr_settings_p->bank_group_decode);
        mddr_settings_p->bank_group_decode = ADDR_DECODE_BG_MCA_16_7;
    }

    /**********  DDR PHY configuration internal use only **********/
    /* DDR PHY TRAINING XCNT*/
    get_secured_uint16(ddr_phy_xcnt_name ,(uint16_t *)&mddr_settings_p->phy_config.ddrphy_xcnt, 2);
    if (mddr_settings_p->phy_config.ddrphy_xcnt != 0
        && mddr_settings_p->phy_config.ddrphy_xcnt != 2)
    {
        monaco_log(CRITICAL,"Invalid phy xcnt value %d, use 2\n", mddr_settings_p->phy_config.ddrphy_xcnt);
        mddr_settings_p->phy_config.ddrphy_xcnt = 2;
    }
    /* DDR PHY TRAINING DDRPHY_UCTL_DMEM_40*/
    get_secured_uint16(ddr_phy_uctl_dmem_40_name ,(uint16_t *)&mddr_settings_p->phy_config.ddrphy_mem40, 0);
    /* DDR PHY TRAINING DDRPHY_UCTL_DMEM_41*/
    get_secured_uint16(ddr_phy_uctl_dmem_41_name ,(uint16_t *)&mddr_settings_p->phy_config.ddrphy_mem41, 0x66);
    /* DDR PHY TRAINING DDRPHY_UCTL_DMEM_42*/
    get_secured_uint16(ddr_phy_uctl_dmem_42_name ,(uint16_t *)&mddr_settings_p->phy_config.ddrphy_mem42, 0x101);
    /* DDR PHY TRAINING DDRPHY_UCTL_DMEM_43*/
    get_secured_uint16(ddr_phy_uctl_dmem_43_name ,(uint16_t *)&mddr_settings_p->phy_config.ddrphy_mem43, 0x1812);

    /**********  User MDDR Variable group **********/
    //  Clear out all possible frequencies so that only the intended frequencies are provided to the driver.
    qmemset(&mddr_settings_p->mem_freq_mhz, DDR_FREQ_INVALID, DDR_FREQ_ID_MAX);
    /* DDR SPEED */
    get_persistent_uint16(ddr_clk_speed_name, &mddr_settings_p->mem_freq_mhz[DDR_FREQ_1], DDR_MAX_SPEED_1DPC);
    if(mddr_settings_p->mem_freq_mhz[DDR_FREQ_1] > DDR_MAX_SPEED_1DPC)
    {
        monaco_log(CRITICAL,"Invalid clock frequency value %x, use default\n", mddr_settings_p->mem_freq_mhz[DDR_FREQ_1]);
        mddr_settings_p->mem_freq_mhz[DDR_FREQ_1] = DDR_MAX_SPEED_1DPC;
    }
    /* DDR FREQUENCY DEFAULT FOR 1DPC BOARD */
    get_persistent_uint16(ddr_def_1dimm_freq_name,&mddr_settings_p->max_1dimm_freq_mhz, DDR_MAX_SPEED_1DPC);
    if(mddr_settings_p->max_1dimm_freq_mhz > DDR_MAX_SPEED_1DPC)
    {
        monaco_log(CRITICAL,"Invalid clock frequency limit for 1DPC value %x, use default\n", mddr_settings_p->max_1dimm_freq_mhz);
        mddr_settings_p->max_1dimm_freq_mhz = DDR_MAX_SPEED_1DPC;
    }
    /* DDR FREQUENCY DEFAULT FOR 2DPC BOARD */
    get_persistent_uint16(ddr_def_2dimm_freq_name,&mddr_settings_p->max_2dimm_freq_mhz, DDR_MAX_SPEED_2DPC);
    if(mddr_settings_p->max_2dimm_freq_mhz > DDR_MAX_SPEED_2DPC)
    {
        monaco_log(CRITICAL,"Invalid clock frequency limit for 2DPC value %x, use default\n", mddr_settings_p->max_2dimm_freq_mhz);
        mddr_settings_p->max_2dimm_freq_mhz = DDR_MAX_SPEED_2DPC;
    }
    /* DISABLE ECC */
#ifdef CONFIG_TESTOS_EMU
    mddr_settings_p->disable_ecc = true;
#else
    get_persistent_boolean(ddr_disable_ecc_name, &mddr_settings_p->disable_ecc, false);
#endif
    /* ECC WRRD MODE */
    get_persistent_uint32(ddr_ecc_wrrd_mode_name, (uint32_t *)&mddr_settings_p->ecc_wrrd_mode, (ECC_WR|ECC_RD));
    if((mddr_settings_p->ecc_wrrd_mode != (ECC_WR|ECC_RD))
        && (mddr_settings_p->ecc_wrrd_mode != (RS_WR|RS_RD)))
    {
        monaco_log(CRITICAL,"Invalid ecc_wrrd_mode value 0x%x, use ECC mode\n", mddr_settings_p->ecc_wrrd_mode);
        mddr_settings_p->ecc_wrrd_mode = (ECC_WR|ECC_RD);
    }
    /* RS QUAD DET EN */
    get_persistent_byte(ddr_rs_quad_det_en_name, &mddr_settings_p->rs_quad_det_en, RS_QUAD_DET_DISABLE);
    if(mddr_settings_p->rs_quad_det_en >= RS_QUAD_DET_NUM_TYPES)
    {
        monaco_log(CRITICAL,"Invalid rs_quad_det_en value 0x%x, use triple symbol detect mode\n", mddr_settings_p->rs_quad_det_en);
        mddr_settings_p->rs_quad_det_en = RS_QUAD_DET_DISABLE;
    }
    /* DDR ECC PATROL SCRUB DISABLE*/
    get_persistent_boolean(ddr_patrol_scrub_name, &mddr_settings_p->disable_patrol_scrub, true);
    /* DDR PAGE SETTING AUTO PRECHARGE ENABLE*/
    get_persistent_boolean(ddr_psetting_autochg_name, &mddr_settings_p->page_settings.enable_auto_pchg, false);
    /* DDR PAGE SETTING PAGE OPEN POLICY*/
    get_persistent_uint32(ddr_psetting_policy_name ,(uint32_t *)&mddr_settings_p->page_settings.page_policy, DDR_PAGE_POLICY_CLOSED);
    if(mddr_settings_p->page_settings.page_policy>=DDR_PAGE_POLICY_NUM_TYPES)
    {
        monaco_log(CRITICAL,"Invalid autoprecharge policy value 0x%x, use closed policy\n", mddr_settings_p->page_settings.page_policy);
        mddr_settings_p->page_settings.page_policy = DDR_PAGE_POLICY_CLOSED;
    }
    /* DDR PAGE SETTING PAGE IDLE TIMER*/
    get_persistent_uint16(ddr_psettings_idle_name ,(uint16_t *)&mddr_settings_p->page_settings.page_idle_timer, 0x0200);
    if(mddr_settings_p->page_settings.page_idle_timer>MDDR_PAGE_IDLE_TIMER_MAX)
    {
        monaco_log(CRITICAL,"Invalid auto precharge idle timer %x, use 0x200\n", mddr_settings_p->page_settings.page_idle_timer);
        mddr_settings_p->page_settings.page_idle_timer = 0x0200;
    }
    /* DDR GRANULE*/
    get_persistent_uint32(ddr_granule_name ,(uint32_t *)&mddr_settings_p->ddr_granule, DDR_DIST_GRANULE_256B);
    if(mddr_settings_p->ddr_granule>=DDR_DIST_GRANULE_NUM_TYPES)
    {
        monaco_log(CRITICAL,"Invalid ddr granule %x, use 256B\n", mddr_settings_p->ddr_granule);
        mddr_settings_p->ddr_granule = DDR_DIST_GRANULE_256B;
    }
    /* DDR DIMM INTERLEAVE ENABLE*/
    get_persistent_boolean(ddr_dimm_intlv_en ,&mddr_settings_p->dimm_intlv_en, false);
    /* DDR AUTO REFRESH COMMAND MODE*/
    get_persistent_uint32(ddr_rfc_mode_name ,(uint32_t *)&mddr_settings_p->rfc_mode, DDR_REFRESH_1X);
    if (mddr_settings_p->rfc_mode > DDR_REFRESH_4X) {
      monaco_log(CRITICAL,"Invalid ddr_rfc_mode value %d, use DDR_REFRESH_1X\n", mddr_settings_p->rfc_mode);
      mddr_settings_p->rfc_mode = DDR_REFRESH_1X;
    }
    /* DDR AUTO SELF-REFRESH ENABLE */
    get_persistent_boolean(auto_self_refresh_name, &mddr_settings_p->auto_self_refresh_en, false);
    /* DDR AUTO SELF REFRESH HYSTERISYS DELAY*/
    get_persistent_uint16(ddr_sr_entry_idle_delay_name ,&mddr_settings_p->sr_entry_idle_delay, 0xFFFF);
    /* DDR AUTO POWER DOWN MODE*/
    get_persistent_boolean(ddr_auto_power_down_name ,&mddr_settings_p->auto_power_down_en, false);
    /* DDR AUTO POWER DOWN HYSTERISYS DELAY*/
    get_persistent_uint16(ddr_pd_entry_idle_delay_name ,&mddr_settings_p->pd_entry_idle_delay, 0x2000);
    /* DDR DIMM 0 REFRESH ADJUSTMENT RATE */
    get_persistent_uint32(ddr_adj_ref_name0 ,(uint32_t *)&mddr_settings_p->adj_ref_dimm0, DIMM_REFRESH_RATE_1x);
    if (mddr_settings_p->adj_ref_dimm0 != DIMM_REFRESH_RATE_ONE_QUARTER
        && mddr_settings_p->adj_ref_dimm0 != DIMM_REFRESH_RATE_ONE_HALF
        && mddr_settings_p->adj_ref_dimm0 != DIMM_REFRESH_RATE_1x
        && mddr_settings_p->adj_ref_dimm0 != DIMM_REFRESH_RATE_2x
        && mddr_settings_p->adj_ref_dimm0 != DIMM_REFRESH_RATE_4x)
    {
        monaco_log(CRITICAL,"Invalid adj ref value %d from dimm 0, use DDR_REFRESH_1X\n", mddr_settings_p->adj_ref_dimm0);
        mddr_settings_p->adj_ref_dimm0 = DIMM_REFRESH_RATE_1x;
    }
    /* DDR DIMM 1 REFRESH ADJUSTMENT RATE */
    get_persistent_uint32(ddr_adj_ref_name1 ,(uint32_t *)&mddr_settings_p->adj_ref_dimm1, DIMM_REFRESH_RATE_1x);
    if (mddr_settings_p->adj_ref_dimm1 != DIMM_REFRESH_RATE_ONE_QUARTER
        && mddr_settings_p->adj_ref_dimm1 != DIMM_REFRESH_RATE_ONE_HALF
        && mddr_settings_p->adj_ref_dimm1 != DIMM_REFRESH_RATE_1x
        && mddr_settings_p->adj_ref_dimm1 != DIMM_REFRESH_RATE_2x
        && mddr_settings_p->adj_ref_dimm1 != DIMM_REFRESH_RATE_4x)
    {
        monaco_log(CRITICAL,"Invalid adj ref value %d from dimm 1, use DDR_REFRESH_1X\n", mddr_settings_p->adj_ref_dimm1);
        mddr_settings_p->adj_ref_dimm1 = DIMM_REFRESH_RATE_1x;
    }
    /* DDR DFI Low Power Mode */
    get_persistent_uint32(ddr_dfi_lp_mode_name ,(uint32_t *)&mddr_settings_p->dfi_lp_mode, DFI_LP_DISABLED);
    if (mddr_settings_p->dfi_lp_mode >= DFI_LP_NUM_TYPES) {
      monaco_log(CRITICAL,"Invalid dfi_lp_mode value %d, use DFI_LP_DISABLED\n", mddr_settings_p->dfi_lp_mode);
      mddr_settings_p->dfi_lp_mode = DFI_LP_DISABLED;
    }
    /* DDR DFI Low Power Mode ENTRY IDLE DELAY */
    get_persistent_uint16(ddr_dfi_lp2_entry_idle_delay_name ,(uint16_t *)&mddr_settings_p->dfi_lp2_entry_idle_delay, 0xFFFF);
    /* DDR 2T PREAMBLE MODE*/
    get_persistent_uint32(ddr_2t_preamble_name, &mddr_settings_p->ddr4_2t_preamble_mode, DDR4_2T_DISABLE);
    if (mddr_settings_p->ddr4_2t_preamble_mode >= DDR4_2T_NUM_TYPES) {
        monaco_log(CRITICAL,"Invalid 2t preamble value %d, use DDR4_2T_DISABLE\n", mddr_settings_p->ddr4_2t_preamble_mode);
        mddr_settings_p->ddr4_2t_preamble_mode = DDR4_2T_DISABLE;
    }
    /* DDR DBI MODE*/
    get_persistent_uint32(ddr_dbi_mode_name, &mddr_settings_p->dbi_mode, DDR_DBI_OFF);
    if (mddr_settings_p->dbi_mode >= DDR_DBI_NUM_TYPES) {
        monaco_log(CRITICAL,"Invalid DBI mode %d, use DDR_DBI_OFF\n", mddr_settings_p->dbi_mode);
        mddr_settings_p->dbi_mode = DDR_DBI_OFF;
    }
    /* DDR CA PARITY*/
    get_persistent_uint32(ddr_ca_parity_name, &mddr_settings_p->ca_parity, CA_PARITY_DIMM);
    if (mddr_settings_p->ca_parity >= CA_PARITY_NUM_TYPES) {
        monaco_log(CRITICAL,"Invalid ca parity mode %d, use CA_PARITY_DIMM\n", mddr_settings_p->ca_parity);
        mddr_settings_p->ca_parity = CA_PARITY_DIMM;
    }
    /* DDR SCRAMBLING ENABLE*/
#ifdef CONFIG_TESTOS_EMU
    mddr_settings_p->mddr_scrambling_en = false;
#else
    get_persistent_boolean(ddr_scrambling_name, &mddr_settings_p->mddr_scrambling_en, true);
#endif
    /* DDR CA STRETCH*/
    get_persistent_uint32(ddr_ca_stretch_name, &mddr_settings_p->ca_stretch, CA_STRETCH_1T);
    if (mddr_settings_p->ca_stretch > CA_STRETCH_4T) {
        monaco_log(CRITICAL,"Invalid ca stretch %d, use CA_STRETCH_1T\n", mddr_settings_p->ca_stretch);
        mddr_settings_p->ca_stretch = CA_STRETCH_1T;
    }
    /* DDR TEMP_CRITICAL_EVENT_ENABLE*/
    get_persistent_boolean(ddr_tcrit_event_en_name, &mddr_settings_p->tcrit_event_en, false);
    /* DDR TEMP_CRITICAL_THRESHOLD*/
    get_persistent_byte(ddr_tcrit_threshhold_name, &mddr_settings_p->tcrit_threshhold, DDR_TCRITIC_TEMP_DEFAULT);
    if (mddr_settings_p->tcrit_threshhold > DDR_TCRITIC_TEMP_MAX) {
        monaco_log(CRITICAL,"Critical threshold of DIMM temperature is out of Range: %d, use %d\n", mddr_settings_p->tcrit_threshhold,DDR_TCRITIC_TEMP_DEFAULT);
        mddr_settings_p->tcrit_threshhold = DDR_TCRITIC_TEMP_DEFAULT;
    }
    /* DDR ECC CE THRESHOLD*/
    get_persistent_uint16(ddr_ecc_ce_threshold_name, &mddr_settings_p->ecc_ce_threshold, 0);

    /* NEW CA MARGINING MODE */
    mddr_settings_p->CA_margin_enabled = false;

    /**********  DDR BUM Variables **********/
    /* DDR BUM BCQ FULL */
    get_secured_boolean(ddr_bum_bcqfull_enable_name, &mddr_settings_p->bum_settings.bcqfull.enable, false);
    get_secured_block(ddr_bum_bcqfull_hithresh_name, &mddr_settings_p->bum_settings.bcqfull.hi_threshold
                        ,&ddr_bum_thresh_default[0], DDR_BUM_PERF_IDX_MAX*sizeof(uint32_t));
    get_secured_block(ddr_bum_bcqfull_lothresh_name, &mddr_settings_p->bum_settings.bcqfull.lo_threshold
                        ,&ddr_bum_thresh_default[0], DDR_BUM_PERF_IDX_MAX*sizeof(uint32_t));
    /* DDR BUM BUSY */
    get_secured_boolean(ddr_bum_busy_enable_name, &mddr_settings_p->bum_settings.busy.enable, false);
    get_secured_block(ddr_bum_busy_hithresh_name, &mddr_settings_p->bum_settings.busy.hi_threshold
                        ,&ddr_bum_thresh_default[0], DDR_BUM_PERF_IDX_MAX*sizeof(uint32_t));
    get_secured_block(ddr_bum_busy_lothresh_name, &mddr_settings_p->bum_settings.busy.lo_threshold
                        ,&ddr_bum_thresh_default[0], DDR_BUM_PERF_IDX_MAX*sizeof(uint32_t));
}

/* ============================================================================
**  Function : get_single_instance_information
** ============================================================================
*/
/*!
*   @brief
*   This function will setup the single instance HOB with the appropriate parameters
*
*   @details
*   This function takes a pointer to the single instance parameter structure and fills
*   it out with the information for this instance of the DDR driver.
*
*   @par Dependencies
*   None
*
*   @par Side Effects
*   None
*
*   @retval  None
*
*   @sa None
*/
void get_single_instance_information(ddr_shared_params* ddr_single_instance_params)
{
    if(ddr_single_instance_params == NULL)
    {
        return;
    }

    ddr_single_instance_params->version = DDR_FUNC_TABLE_VERSION;
    ddr_single_instance_params->ddr_func_tbl_ptr = (void*) &ddr_function_table;
    ddr_single_instance_params->size = sizeof(ddr_function_table);
}

/* ============================================================================
**  Function : get_monaco_smbus_information
** ============================================================================
*/
#ifdef HARVEST
dimm_slot_smbus_info_t *get_monaco_smbus_information(void)
{
    return &smbus_default_val[0][0];
}
#endif

/***********************************/
/* HELPER FUNCTONS BELOW THIS LINE */
/***********************************/

/* =============================================================================
**  Function : get_persistent_boolean
** ============================================================================
*/
void get_persistent_boolean(const uint16_t* name, bool* var, bool default_val)
{
    uint8_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_DEFAULT_SECURITY) && var_size == sizeof(bool))
    {
        // If the variable is greater than zero, treat that as a true value
        *var = *persistent_var_ptr > 0 ? true : false;
    }
    else
    {
        *var = default_val;
    }
}

/* =============================================================================
**  Function : get_persistent_byte
** ============================================================================
*/
void get_persistent_byte(const uint16_t* name, uint8_t* var, uint8_t default_val)
{
    uint8_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_DEFAULT_SECURITY) && var_size == sizeof(uint8_t))
    {
        *var = *persistent_var_ptr;
    }
    else
    {
        *var = default_val;
    }
}

/* =============================================================================
**  Function : get_persistent_uint16
** ============================================================================
*/
void get_persistent_uint16(const uint16_t* name, uint16_t* var, uint16_t default_val)
{
    uint16_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_DEFAULT_SECURITY) && var_size == sizeof(uint16_t))
    {
        qmemcpy(var, persistent_var_ptr, sizeof(*var));
    }
    else
    {
        qmemcpy(var, &default_val, sizeof(*var));
    }
}

/* =============================================================================
**  Function : get_persistent_uint32
** ============================================================================
*/
void get_persistent_uint32(const uint16_t* name, uint32_t* var, uint32_t default_val)
{
    uint32_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_DEFAULT_SECURITY) && var_size == sizeof(uint32_t))
    {
        qmemcpy(var, persistent_var_ptr, sizeof(*var));
    }
    else
    {
        qmemcpy(var, &default_val, sizeof(*var));
    }
}

/* =============================================================================
**  Function : get_persistent_uint64
** ============================================================================
*/
void get_persistent_uint64(const uint16_t* name, uint64_t* var, uint64_t default_val)
{
    uint64_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_DEFAULT_SECURITY) && var_size == sizeof(uint64_t))
    {
        qmemcpy(var, persistent_var_ptr, sizeof(*var));
    }
    else
    {
        qmemcpy(var, &default_val, sizeof(*var));
    }
}

/* =============================================================================
**  Function : get_persistent_block
** ============================================================================
*/
void get_persistent_block(const uint16_t* name, void* var, void* default_val, uint32_t var_size)
{
    uint32_t* persistent_var_ptr = NULL;
    uint32_t ret_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &ret_size, VARIABLE_DEFAULT_SECURITY) && ret_size == var_size)
    {
        qmemcpy(var, persistent_var_ptr, ret_size);
    }
    else
    {
        qmemcpy(var, default_val, var_size);
    }
}

/* =============================================================================
**  Function : get_secured_boolean
** ============================================================================
*/
void get_secured_boolean(const uint16_t* name, bool* var, bool default_val)
{
    uint8_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_INTERNAL_SECURITY) && var_size == sizeof(bool))
    {
        // If the variable is greater than zero, treat that as a true value
        *var = *persistent_var_ptr > 0 ? true : false;
    }
    else
    {
        *var = default_val;
    }
}

/* =============================================================================
**  Function : get_secured_byte
** ============================================================================
*/
void get_secured_byte(const uint16_t* name, uint8_t* var, uint8_t default_val)
{
    uint8_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_INTERNAL_SECURITY) && var_size == sizeof(uint8_t))
    {
        *var = *persistent_var_ptr;
    }
    else
    {
        *var = default_val;
    }
}

/* =============================================================================
**  Function : get_secured_uint16
** ============================================================================
*/
void get_secured_uint16(const uint16_t* name, uint16_t* var, uint16_t default_val)
{
    uint16_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_INTERNAL_SECURITY) && var_size == sizeof(uint16_t))
    {
        qmemcpy(var, persistent_var_ptr, sizeof(*var));
    }
    else
    {
        qmemcpy(var, &default_val, sizeof(*var));
    }
}

/* =============================================================================
**  Function : get_secured_uint32
** ============================================================================
*/
void get_secured_uint32(const uint16_t* name, uint32_t* var, uint32_t default_val)
{
    uint32_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_INTERNAL_SECURITY) && var_size == sizeof(uint32_t))
    {
        qmemcpy(var, persistent_var_ptr, sizeof(*var));
    }
    else
    {
        qmemcpy(var, &default_val, sizeof(*var));
    }
}

/* =============================================================================
**  Function : get_secured_uint64
** ============================================================================
*/
void get_secured_uint64(const uint16_t* name, uint64_t* var, uint64_t default_val)
{
    uint64_t* persistent_var_ptr = NULL;
    uint32_t var_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &var_size, VARIABLE_INTERNAL_SECURITY) && var_size == sizeof(uint64_t))
    {
        qmemcpy(var, persistent_var_ptr, sizeof(*var));
    }
    else
    {
        qmemcpy(var, &default_val, sizeof(*var));
    }
}

/* =============================================================================
**  Function : get_secured_block
** ============================================================================
*/
void get_secured_block(const uint16_t* name, void* var, void* default_val, uint32_t var_size)
{
    uint32_t* persistent_var_ptr = NULL;
    uint32_t ret_size = 0;

    if(boot_get_shared_variable((uint16_t*) name, (void*) &persistent_var_ptr, &ret_size, VARIABLE_INTERNAL_SECURITY) && ret_size == var_size)
    {
        qmemcpy(var, persistent_var_ptr, ret_size);
    }
    else
    {
        qmemcpy(var, default_val, var_size);
    }
}

/* =============================================================================
**  Function : monaco_int_ddr4_image
** ============================================================================
*/
int monaco_init_ddr4_image(uint64_t ddr_fw_base)
{
    uint32_t i;
    uint64_t cur_bin_offset;
    uint64_t *DDRFW;

    // initialize header
    DDRFW = (uint64_t *)ddr_fw_base;
    ddr4_fwimg_offset.bInit = false;
    qmemset(&ddr4_fwimg_hdr, 0x00, sizeof(ddr4_fwimg_hdr_type));
    qmemset(&ddr4_fwimg_offset, 0x00, sizeof(ddr4_fwimg_offset_type));

    // initialize header
    qmemcpy(&ddr4_fwimg_hdr, DDRFW, sizeof(ddr4_fwimg_hdr_type));
    if(strcmp(ddr4_fwimg_hdr.ident, "DDR")!=0)
        return DDR_INVALID_FIRMWARE;

    // Build up offset of binaries
    cur_bin_offset = ddr4_fwimg_hdr.start_image;
    for(i=0;i<ddr4_fwimg_hdr.num_image;i++)
    {
        ddr4_fwimg_offset.binoffset[i] = cur_bin_offset+ddr_fw_base;
        cur_bin_offset += (ddr4_fwimg_hdr.binsize[i] + DDR4_FWIMG_SIZE_PAD)&~(DDR4_FWIMG_SIZE_PAD);
    }

    monaco_log(CRITICAL,"  DDR PHY VER: %s\n", PHY_IMG_VER);
    ddr4_fwimg_offset.bInit = true;
    return DDR_STATUS_SUCCESS;
}

/* =============================================================================
**  Function : monaco_read_ddr4_image
** ============================================================================
*/
int monaco_get_ddr4_image_info(uint16_t fwid, uint64_t* out_addr, uint32_t* out_size)
{
    if (!ddr4_fwimg_offset.bInit)
        return DDR_INVALID_FIRMWARE;

    if( out_addr ==0 || out_size==0)
        return DDR_INVALID_FIRMWARE;

    *out_addr = ddr4_fwimg_offset.binoffset[fwid];
    *out_size = ddr4_fwimg_hdr.binsize[fwid];
    return DDR_STATUS_SUCCESS;
}
