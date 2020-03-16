/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2018 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file mddr_mc_init.c
*
* @par Description:
*    This module provides the functionality to initialize the memory
*    controllers found in the Monaco DDR subsystem.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <target/ddr.h>

/******************************************************************************
* Defined Constants
******************************************************************************/

#define PDA_MASK_INVALID                  0x00000000

// Compression related defines which are not configurable through xBL.
#define CDE_COMP_WR_IMPACT_ACT    0x0
#define CDE_COMP_WR_IMPACT_PCHG    0x0

#define CDE_BCQ_THRESHOLD       0x0
#define CDE_BCQ_THRESHOLD_RD    0x0
#define CDE_BCQ_THRESHOLD_WR    0x0
#define CDE_BCQ_THRESHOLD_EN    0x0
#define CDE_BCQ_THRESHOLD_RD_EN    0x0
#define CDE_BCQ_THRESHOLD_WR_EN    0x0
#define CDE_RD_CYCLE_EN    0x0
#define CDE_WR_CYCLE_EN    0x0
#define CDE_OH_CYCLE_EN    0x0

#define CDE_BUSY_HI_THRESHOLD    0x0
#define CDE_BUSY_LO_THRESHOLD    0x0

#define CDE_BUSY_WINDOW_SIZE    0x0
#define CDE_BUSY_HIST_THRESHOLD    0x0
#define CDE_BUSY_HIST_SIZE    0x0
#define CDE_NOT_BUSY_EN    0x0
#define CDE_NOT_BUSY_SEL    0x0

// Per table 38 of JEDEC spec
// VrefDQ training mode entry and exit timing
#define MIN_TVREFDQE_DDR4 150000 //ps
#define MIN_TVREFDQX_DDR4 150000 //ps

/******************************************************************************
* Derived data types
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/
// Compression related variables which are not configurable through xBL.
uint16_t cde_busy_window_size = CDE_BUSY_WINDOW_SIZE;
uint16_t cde_busy_hist_threshold = CDE_BUSY_HIST_THRESHOLD;
uint16_t cde_busy_hist_size = CDE_BUSY_HIST_SIZE;
uint8_t  cde_not_busy_en = CDE_NOT_BUSY_EN;
uint8_t  cde_not_busy_sel = CDE_NOT_BUSY_SEL;
bool CA_margin_enabled=false;

extern mddr_lr_db_si_chan_t lr_db_si_data[DDR_MAX_NUM_CHANS];

/******************************************************************************
* Function Prototypes
******************************************************************************/

void mddr_mc_ecc_scrub_init(uint64_t mddr_base_addr, uint8_t ddr_chan);
void mddr_mc_get_timing_reg_vals(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr, mddr_latencies_t *latencies_ptr);


uint32_t mddr_mc_build_dimm_tech_reg_val(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_dimm_slot_config_reg_val(mddr_common_cfg_t *common_cfg_ptr, uint8_t slot);
uint32_t mddr_mc_build_dimm_slot_addr_reg_val(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr, uint8_t slot);
uint32_t mddr_mc_build_dataflow_cntl_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_dataflow_cde_cntl_0_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_dataflow_cde_cntl_1_reg(void);
uint32_t mddr_mc_build_dataflow_cde_cntl_2_reg(void);
uint32_t mddr_mc_build_dataflow_cde_cntl_3_reg(void);
uint32_t mddr_mc_build_dataflow_cde_cntl_4_reg(void);
uint32_t mddr_mc_build_dataflow_cde_cntl_5_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_dataflow_cde_cntl_6_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_ddr_odt_wr_cntl_reg(uint8_t ddr_chan);
uint32_t mddr_mc_build_ddr_odt_rd_cntl_reg(uint8_t ddr_chan);
uint32_t mddr_mc_build_cmd_exec_cntl_0_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_cmd_exec_cntl_1_reg(void);
uint32_t mddr_mc_build_cmd_exec_cntl_2_reg(void);
uint32_t mddr_mc_build_cmd_exec_cntl_3_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_cmd_exec_cntl_4_reg(void);
uint32_t mddr_mc_build_cmd_exec_cntl_5_reg(void);
uint32_t mddr_mc_build_cmd_exec_cntl_6_reg(void);
uint32_t mddr_mc_build_cmd_exec_cntl_7_reg(void);

uint32_t mddr_mc_build_addr_decode_cntl_reg(soc_hw_version_t soc_hw_version, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_wdb_flush_cntl_reg(void);
uint32_t mddr_mc_build_wdb_flush_ph_reg(void);

uint32_t mddr_mc_build_wdb_flush_wm_reg(void);

uint32_t mddr_mc_build_int0_cntl_reg(    mddr_settings_t *mddr_settings_ptr   );
uint32_t mddr_mc_build_int1_cntl_reg(void);
uint32_t mddr_mc_build_err_cntl_reg(mddr_common_cfg_t *common_cfg_ptr,      mddr_settings_t *mddr_settings_ptr   );
uint32_t mddr_mc_build_err_cap_cntl_reg(void);
uint32_t mddr_mc_build_ecc_err_cntl_1_reg(mddr_settings_t *mddr_settings_ptr);

uint32_t mddr_mc_build_rd_wr_pref_cntl_reg(void);
uint32_t mddr_mc_build_tn_token_cnt_reg(void);
uint32_t mddr_mc_build_ddr_dfi_cntl_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_ddr_dfi_cntl_1_reg(mddr_settings_t *mddr_settings_ptr);

uint32_t mddr_mc_build_ddr_phy_cntl_reg(void);
uint32_t mddr_mc_build_ddr_self_ref_cntl_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_ddr_power_down_cntl_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_ddr_ca_bus_cntl_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_ddr_dq_bus_cntl_reg(mddr_common_cfg_t *common_cfg_ptr);

uint32_t mddr_mc_build_thermal_cntl_0_reg(mddr_therm_throttle_settings_t *therm_throttle_settings_ptr);
uint32_t mddr_mc_build_thermal_cntl_1_reg(mddr_therm_throttle_settings_t *therm_throttle_settings_ptr);
uint32_t mddr_mc_build_thermal_cntl_2_reg(mddr_therm_throttle_settings_t *therm_throttle_settings_ptr);
uint32_t mddr_mc_build_thermal_cntl_3_reg(mddr_therm_throttle_settings_t *therm_throttle_settings_ptr);
uint32_t mddr_mc_build_thermal_cntl_4_reg(mddr_therm_throttle_settings_t *therm_throttle_settings_ptr);


uint32_t mddr_mc_build_busy_dcvs_cnt_reg(mddr_bum_event_settings_t *bum_event_settings_ptr);
uint32_t mddr_mc_build_bcqfull_dcvs_cnt_reg(mddr_bum_event_settings_t *bum_event_settings_ptr);

uint32_t mddr_mc_build_dcvs_high_threshold_reg(mddr_bum_event_settings_t *bum_event_settings_ptr, uint8_t ddr_bum_perf_idx);
uint32_t mddr_mc_build_dcvs_low_threshold_reg(mddr_bum_event_settings_t *bum_event_settings_ptr, uint8_t ddr_bum_perf_idx);

void mddr_mc_ecc_scrub_start_init(uint64_t mddr_base_addr);
void mddr_mc_ecc_scrub_stop_init(uint64_t mddr_base_addr);
void mddr_mc_ecc_scrub_start(uint64_t mddr_base_addr, uint8_t ddr_chan);
void mddr_mc_ecc_scrub_setup_wdb(uint64_t mddr_base_addr);
void mddr_mc_ecc_scrub_check_complete(uint64_t mddr_base_addr, uint8_t ddr_chan);
uint8_t mddr_mc_ecc_scrub_get_cmd_timer_seed(uint8_t ddr_chan);


uint32_t mddr_mc_get_avail_ranks(void);
unsigned mddr_mc_set_rank_cntl_reg(uint64_t mddr_base_addr, uint16_t num_slots_populated, uint8_t ddr_chan);

void mddr_mc_set_dimm_slot_regs(uint64_t mddr_base_addr, uint8_t slot, uint32_t dimm_slot_config_val, uint32_t dimm_slot_addr_val);
void mddr_mc_disable_unused_clocks(uint64_t mddr_base_addr);
void mddr_mc_build_dimm_init(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan, uint8_t slot);
void mddr_mc_exec_dimm_init(uint8_t ddr_chan, uint8_t slot);
void mddr_mc_build_ddr3_rcw(uint8_t ddr_chan, uint8_t slot);
void mddr_mc_build_ddr4_rcw(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan, uint8_t slot);
void mddr_mc_build_ddr4_db(uint8_t ddr_chan, uint8_t slot);
void mddr_mc_build_ddr3_mr(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan, uint8_t slot, uint8_t rank_num);
void mddr_mc_build_ddr4_mr(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan, uint8_t slot, uint8_t rank_num);
uint8_t mddr_mc_get_vref_range(uint16_t vref);
void mddr_mc_exec_ddr3_rcw(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t slot);
void mddr_mc_exec_ddr4_rcw(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t slot);
void mddr_mc_exec_ddr3_mr(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t rank_num, uint8_t rank_indicator);
void mddr_mc_exec_ddr4_mr(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t rank_num, uint8_t rank_indicator);
void mddr_mc_vref_write(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t rank_num, uint32_t rank_id);
void mddr_mc_mr_write(uint64_t mddr_base_addr, uint32_t ranks, uint8_t mr_addr, uint16_t mr_data, uint32_t mask);
void mddr_mc_cw_write(uint64_t mddr_base_addr, uint8_t slot, uint8_t cw_addr, uint16_t cw_data);
void mddr_mc_zqcal(uint64_t mddr_base_addr, uint32_t ranks, zq_cal_type_t zq_type);
void mddr_mc_enable_periodic_zqcal(uint64_t mddr_base_addr, mddr_settings_t *mddr_settings_ptr);
void mddr_mc_slot_ready(uint64_t mddr_base_addr, uint8_t slot);
void mddr_mc_check_status(uint64_t mddr_base_addr);
void mddr_mc_wait_ns(uint64_t mddr_base_addr, uint16_t num_ns);


/******************************************************************************
* External Functions
******************************************************************************/


/*!****************************************************************************
*
* @par Description:
*    This function initializes  the memory controllers found in the Monaco
*    DDR subsystem based on SPD information extracted from the populated DIMMs
*    and specified configuration options
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
*
* @return
*    The status indicating the level of success in initializing the memory controllers.
*
* @author
*    gkowis
*
******************************************************************************/
unsigned mddr_mc_init(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan)
{
    unsigned status = COM_OK;
    uint8_t dimm_slot;
    spd_dimm_config_t *cfg_ptr;
    uint64_t mddr_base_addr;
    uint16_t slot_bitmap;
    uint16_t num_slots_populated = 0;


    mddr_base_addr = mddr_base_addrs[ddr_chan];
    slot_bitmap = 0x0;


    for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

        if(cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            if (dimm_slot == 0)
            {
                monaco_log(LOW, "\n ==========================================\n");
                monaco_log(CRITICAL, "| Initializing channel %1d Memory Controller |\n", hddrss[ddr_chan]);
                monaco_log(LOW, " ==========================================\n");
            }

            mddr_mc_set_dimm_slot_regs(mddr_base_addr, dimm_slot,
                                       mddr_reg_vals.dimm_slot_config_val[dimm_slot],
                                       mddr_reg_vals.dimm_slot_addr_val[dimm_slot]);

            // Fill in the map of populated DIMM slots for the channel.
            slot_bitmap |= 0x1 << dimm_slot;
            ++num_slots_populated;
        }
    }


    // Skip channels that have no DIMMs.
    if(slot_bitmap != 0)
    {
        // Disable unused clocks.
        mddr_mc_disable_unused_clocks(mddr_base_addr);

        mddr_set_reg(mddr_base_addr + MDDR_DIMM_TECH_OFFSET,         "DIMM_TECH",        mddr_reg_vals.dimm_tech_val);
        mddr_set_reg(mddr_base_addr + MDDR_ADDR_DECODE_CNTL_OFFSET,  "ADDR_DECODE_CNTL", mddr_reg_vals.addr_decode_cntl_val);

        mddr_set_reg(mddr_base_addr + MDDR_WDB_FLUSH_WM_OFFSET,      "WDB_FLUSH_WM",     mddr_reg_vals.wdb_flush_wm_val);
        mddr_set_reg(mddr_base_addr + MDDR_WDB_FLUSH_CNTL_OFFSET,    "WDB_FLUSH_CNTL",   mddr_reg_vals.wdb_flush_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_WDB_FLUSH_PH_OFFSET,      "WDB_FLUSH_PH",     mddr_reg_vals.wdb_flush_ph_val);

        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_0_OFFSET,   "CMD_EXEC_CNTL_0",  mddr_reg_vals.cmd_exec_cntl_0_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_1_OFFSET,   "CMD_EXEC_CNTL_1",  mddr_reg_vals.cmd_exec_cntl_1_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_2_OFFSET,   "CMD_EXEC_CNTL_2",  mddr_reg_vals.cmd_exec_cntl_2_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_3_OFFSET,   "CMD_EXEC_CNTL_3",  mddr_reg_vals.cmd_exec_cntl_3_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_4_OFFSET,   "CMD_EXEC_CNTL_4",  mddr_reg_vals.cmd_exec_cntl_4_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_5_OFFSET,   "CMD_EXEC_CNTL_5",  mddr_reg_vals.cmd_exec_cntl_5_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_6_OFFSET,   "CMD_EXEC_CNTL_6",  mddr_reg_vals.cmd_exec_cntl_6_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_7_OFFSET,   "CMD_EXEC_CNTL_7",  mddr_reg_vals.cmd_exec_cntl_7_val);

        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CNTL_OFFSET,     "DATAFLOW_CNTL",    mddr_reg_vals.dataflow_cntl_val);

        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_0_OFFSET,  "DATAFLOW_CDE_CNTL_0", mddr_reg_vals.dataflow_cde_cntl_0_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_1_OFFSET,  "DATAFLOW_CDE_CNTL_1", mddr_reg_vals.dataflow_cde_cntl_1_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_2_OFFSET,  "DATAFLOW_CDE_CNTL_2", mddr_reg_vals.dataflow_cde_cntl_2_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_3_OFFSET,  "DATAFLOW_CDE_CNTL_3", mddr_reg_vals.dataflow_cde_cntl_3_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_4_OFFSET,  "DATAFLOW_CDE_CNTL_4", mddr_reg_vals.dataflow_cde_cntl_4_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_5_OFFSET,  "DATAFLOW_CDE_CNTL_5", mddr_reg_vals.dataflow_cde_cntl_5_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_6_OFFSET,  "DATAFLOW_CDE_CNTL_6", mddr_reg_vals.dataflow_cde_cntl_6_val);

        mddr_set_reg(mddr_base_addr + MDDR_DDR_ODT_WR_CNTL_OFFSET,   "DDR_ODT_WR_CNTL",  mddr_reg_vals.ddr_odt_wr_cntl_val[ddr_chan]);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_ODT_RD_CNTL_OFFSET,   "DDR_ODT_RD_CNTL",  mddr_reg_vals.ddr_odt_rd_cntl_val[ddr_chan]);

        mddr_set_reg(mddr_base_addr + MDDR_DDR_AUTO_REF_CNTL_OFFSET, "DDR_AUTO_REF_CNTL", mddr_reg_vals.timing_regs.auto_ref_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_RD_WR_PREF_CNTL_OFFSET,   "RD_WR_PREF_CNTL",  mddr_reg_vals.rd_wr_pref_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_TN_TOKEN_CNT_OFFSET,      "TN_TOKEN_CNT",     mddr_reg_vals.tn_token_cnt_val);
#ifdef CONFIG_TESTOS_EMU
        mddr_set_reg(mddr_base_addr + MDDR_DDR_DFI_CNTL_OFFSET,      "DDR_DFI_CNTL",     0x1e40);
#else
        mddr_set_reg(mddr_base_addr + MDDR_DDR_DFI_CNTL_OFFSET,      "DDR_DFI_CNTL",     mddr_reg_vals.ddr_dfi_cntl_val);
#endif
        mddr_set_reg(mddr_base_addr + MDDR_DDR_DFI_CNTL_1_OFFSET,    "DDR_DFI_CNTL_1",   mddr_reg_vals.ddr_dfi_cntl_1_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_ZQCAL_CNTL_OFFSET,    "DDR_ZQCAL_CNTL",   mddr_reg_vals.timing_regs.zqcal_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_PHY_CNTL_OFFSET,      "DDR_PHY_CNTL",     mddr_reg_vals.ddr_phy_cntl_val);

        mddr_set_reg(mddr_base_addr + MDDR_DDR_CA_BUS_CNTL_OFFSET,   "DDR_CA_BUS_CNTL",  mddr_reg_vals.ddr_ca_bus_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_DQ_BUS_CNTL_OFFSET,   "DDR_DQ_BUS_CNTL",  mddr_reg_vals.ddr_dq_bus_cntl_val);

        // Setup error control mask
        mddr_set_reg(mddr_base_addr + MDDR_ERR_CNTL_OFFSET,         "ERR_CNTL",        mddr_reg_vals.err_cntl_val);

        if(mddr_reg_vals.err_cntl_val != 0)    // clear error out from status
        {
            mddr_set_reg(mddr_base_addr + MDDR_ERR_CLR_OFFSET,         "ERR_CLR",        mddr_reg_vals.err_cntl_val);
        }

        mddr_set_reg(mddr_base_addr + MDDR_ERR_CAP_CNTL_OFFSET,      "ERR_CAP_CNTL",    mddr_reg_vals.err_cap_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_ECC_ERR_CNTL_1_OFFSET,    "ECC_ERR_CNTL1",   mddr_reg_vals.ecc_err_cntl_1_val);

        // Enable interrupt sources.
        mddr_set_reg(mddr_base_addr + MDDR_INT0_CNTL_OFFSET,        "INT0_CNTL",       mddr_reg_vals.int0_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_INT1_CNTL_OFFSET,        "INT1_CNTL",       mddr_reg_vals.int1_cntl_val);

        // Set the timing registers
        mddr_mc_set_timing_reg_vals(mddr_base_addr, ddr_chan);

        // Set the Rank control register
        status = mddr_mc_set_rank_cntl_reg(mddr_base_addr, num_slots_populated, ddr_chan);

        // Build the RCW and MR values based on valid ranks.
        for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

            if(cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                mddr_mc_build_dimm_init(mddr_settings_ptr, ddr_chan, dimm_slot);
            }
        }
    }

    return status;
}


/*!****************************************************************************
*
* @par Description:
*    This function initializes  the memory controllers found in the Monaco
*    DDR subsystem based on SPD information extracted from the populated DIMMs
*    and specified configuration options
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
*
* @return
*    The status indicating the level of success in initializing the memory controllers.
*
* @author
*    gkowis
*
******************************************************************************/
unsigned mddr_mc_wd_init(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan)
{
    unsigned status = COM_OK;
    uint8_t dimm_slot;
    spd_dimm_config_t *cfg_ptr;
    uint64_t mddr_base_addr;
    uint16_t slot_bitmap;
    uint16_t num_slots_populated = 0;


    mddr_base_addr = mddr_base_addrs[ddr_chan];
    slot_bitmap = 0x0;


    for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

        if(cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            if (dimm_slot == 0)
            {
                monaco_log(LOW, "\n ==========================================\n");
                monaco_log(CRITICAL, "| Initializing channel %1d Memory Controller |\n", hddrss[ddr_chan]);
                monaco_log(LOW, " ==========================================\n");
            }

            mddr_mc_set_dimm_slot_regs(mddr_base_addr, dimm_slot,
                                       mddr_reg_vals.dimm_slot_config_val[dimm_slot],
                                       mddr_reg_vals.dimm_slot_addr_val[dimm_slot]);

            // Fill in the map of populated DIMM slots for the channel.
            slot_bitmap |= 0x1 << dimm_slot;
            ++num_slots_populated;
        }
    }


    // Skip channels that have no DIMMs.
    if(slot_bitmap != 0)
    {
        mddr_set_reg(mddr_base_addr + MDDR_DIMM_TECH_OFFSET,         "DIMM_TECH",        mddr_reg_vals.dimm_tech_val);
        mddr_set_reg(mddr_base_addr + MDDR_ADDR_DECODE_CNTL_OFFSET,  "ADDR_DECODE_CNTL", mddr_reg_vals.addr_decode_cntl_val);

        mddr_set_reg(mddr_base_addr + MDDR_WDB_FLUSH_WM_OFFSET,      "WDB_FLUSH_WM",     mddr_reg_vals.wdb_flush_wm_val);
        mddr_set_reg(mddr_base_addr + MDDR_WDB_FLUSH_CNTL_OFFSET,    "WDB_FLUSH_CNTL",   mddr_reg_vals.wdb_flush_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_WDB_FLUSH_PH_OFFSET,      "WDB_FLUSH_PH",     mddr_reg_vals.wdb_flush_ph_val);

        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_0_OFFSET,   "CMD_EXEC_CNTL_0",  mddr_reg_vals.cmd_exec_cntl_0_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_1_OFFSET,   "CMD_EXEC_CNTL_1",  mddr_reg_vals.cmd_exec_cntl_1_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_2_OFFSET,   "CMD_EXEC_CNTL_2",  mddr_reg_vals.cmd_exec_cntl_2_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_3_OFFSET,   "CMD_EXEC_CNTL_3",  mddr_reg_vals.cmd_exec_cntl_3_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_4_OFFSET,   "CMD_EXEC_CNTL_4",  mddr_reg_vals.cmd_exec_cntl_4_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_5_OFFSET,   "CMD_EXEC_CNTL_5",  mddr_reg_vals.cmd_exec_cntl_5_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_6_OFFSET,   "CMD_EXEC_CNTL_6",  mddr_reg_vals.cmd_exec_cntl_6_val);
        mddr_set_reg(mddr_base_addr + MDDR_CMD_EXEC_CNTL_7_OFFSET,   "CMD_EXEC_CNTL_7",  mddr_reg_vals.cmd_exec_cntl_7_val);

        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CNTL_OFFSET,     "DATAFLOW_CNTL",    mddr_reg_vals.dataflow_cntl_val);

        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_0_OFFSET,  "DATAFLOW_CDE_CNTL_0", mddr_reg_vals.dataflow_cde_cntl_0_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_1_OFFSET,  "DATAFLOW_CDE_CNTL_1", mddr_reg_vals.dataflow_cde_cntl_1_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_2_OFFSET,  "DATAFLOW_CDE_CNTL_2", mddr_reg_vals.dataflow_cde_cntl_2_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_3_OFFSET,  "DATAFLOW_CDE_CNTL_3", mddr_reg_vals.dataflow_cde_cntl_3_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_4_OFFSET,  "DATAFLOW_CDE_CNTL_4", mddr_reg_vals.dataflow_cde_cntl_4_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_5_OFFSET,  "DATAFLOW_CDE_CNTL_5", mddr_reg_vals.dataflow_cde_cntl_5_val);
        mddr_set_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_CNTL_6_OFFSET,  "DATAFLOW_CDE_CNTL_6", mddr_reg_vals.dataflow_cde_cntl_6_val);

        mddr_set_reg(mddr_base_addr + MDDR_DDR_ODT_WR_CNTL_OFFSET,   "DDR_ODT_WR_CNTL",  mddr_reg_vals.ddr_odt_wr_cntl_val[ddr_chan]);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_ODT_RD_CNTL_OFFSET,   "DDR_ODT_RD_CNTL",  mddr_reg_vals.ddr_odt_rd_cntl_val[ddr_chan]);

        mddr_set_reg(mddr_base_addr + MDDR_DDR_AUTO_REF_CNTL_OFFSET, "DDR_AUTO_REF_CNTL", mddr_reg_vals.timing_regs.auto_ref_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_RD_WR_PREF_CNTL_OFFSET,   "RD_WR_PREF_CNTL",  mddr_reg_vals.rd_wr_pref_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_TN_TOKEN_CNT_OFFSET,      "TN_TOKEN_CNT",     mddr_reg_vals.tn_token_cnt_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_DFI_CNTL_OFFSET,      "DDR_DFI_CNTL",     mddr_reg_vals.ddr_dfi_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_DFI_CNTL_1_OFFSET,    "DDR_DFI_CNTL_1",   mddr_reg_vals.ddr_dfi_cntl_1_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_ZQCAL_CNTL_OFFSET,    "DDR_ZQCAL_CNTL",   mddr_reg_vals.timing_regs.zqcal_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_PHY_CNTL_OFFSET,      "DDR_PHY_CNTL",     mddr_reg_vals.ddr_phy_cntl_val);

        mddr_set_reg(mddr_base_addr + MDDR_DDR_SELF_REF_CNTL_OFFSET, "DDR_SELF_REF_CNTL", mddr_reg_vals.ddr_self_ref_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_CA_BUS_CNTL_OFFSET,  "DDR_CA_BUS_CNTL",  mddr_reg_vals.ddr_ca_bus_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_DDR_DQ_BUS_CNTL_OFFSET,  "DDR_DQ_BUS_CNTL",  mddr_reg_vals.ddr_dq_bus_cntl_val);

        // Setup error control mask
        mddr_set_reg(mddr_base_addr + MDDR_ERR_CNTL_OFFSET,         "ERR_CNTL",        mddr_reg_vals.err_cntl_val);

        mddr_set_reg(mddr_base_addr + MDDR_ERR_CAP_CNTL_OFFSET,      "ERR_CAP_CNTL",    mddr_reg_vals.err_cap_cntl_val);

        // Enable interrupt sources.
        mddr_set_reg(mddr_base_addr + MDDR_INT0_CNTL_OFFSET,        "INT0_CNTL",       mddr_reg_vals.int0_cntl_val);
        mddr_set_reg(mddr_base_addr + MDDR_INT1_CNTL_OFFSET,        "INT1_CNTL",       mddr_reg_vals.int1_cntl_val);

        // Set the timing registers
        mddr_mc_set_timing_reg_vals(mddr_base_addr, ddr_chan);

        // Get the valid ranks for the memory controller.
        mddr_valid_ranks = mddr_mc_get_avail_ranks();


        //  Adjust rank values to account for combining of ranks for other register formatting where rank bits are combined.
        if(num_slots_populated == 2)
        {
            // Combine the 2 chip selects from the 1st slot with the 2 chip selects from 2nd slot.
            //  PHY only supports 4 chip selects so they have to be combined this way for specific
            //  MC register writes to align it with the PHY. Other rank related accesses including
            //  SI data follow nominal uncombined scheme.
            mddr_combined_valid_ranks = (mddr_valid_ranks & 0x3) | ((mddr_valid_ranks >> 0x2) & 0xC);
        }
        else
        {
            mddr_combined_valid_ranks = mddr_valid_ranks;
        }

        // Enable all valid ranks.
        mddr_set_reg(mddr_base_addr + MDDR_RANK_EN_CNTL_OFFSET,     "RANK_EN_CNTL",     mddr_combined_valid_ranks);


        // Build the RCW and MR values based on valid ranks.
        for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

            if(cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                mddr_mc_build_dimm_init(mddr_settings_ptr, ddr_chan, dimm_slot);
            }
        }
    }

    return status;
}

/*!****************************************************************************
*
* @par Description:
*    This function performs DIMM intialization (mode register writes and
*    register control word writes).
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
*
* @return
*    The status indicating the level of success in initializing the memory controllers.
*
* @author
*    mwuu
*
******************************************************************************/
unsigned mddr_mc_dram_init(uint8_t ddr_chan)
{
  unsigned status = COM_OK;
  uint8_t dimm_slot=0;
  uint64_t mddr_base_addr;
  uint16_t slot_bitmap;
  uint16_t working_slot_bitmap;

    mddr_base_addr = mddr_base_addrs[ddr_chan];

    if (mddr_dimm_configs[ddr_chan][0].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
    {
        slot_bitmap=0x1;
    }
    else
    {
        slot_bitmap=0x0;
    }

    if (mddr_dimm_configs[ddr_chan][1].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
    {
        slot_bitmap |= 0x2;
    }

    // valid channel
    if(slot_bitmap != 0)
    {
        monaco_log(LOW, "\n ========================\n");
        monaco_log(CRITICAL, "| DRAM Init on channel %1d |\n", hddrss[ddr_chan]);
        monaco_log(LOW, " ========================\n");

        // Release reset, assert CKE
        mddr_mc_enable_clocks(mddr_base_addr);

        // Unfence PHY
        mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OFFSET, "DDR_MANUAL", 0x00000000);

        // Initialize the memories.
        dimm_slot = 0;
        working_slot_bitmap = slot_bitmap;


        while (working_slot_bitmap > 0)
        {
            if ((working_slot_bitmap & 0x1) == 0x1)
            {
                  mddr_mc_exec_dimm_init(ddr_chan, dimm_slot);
            }

            ++dimm_slot;
            working_slot_bitmap = working_slot_bitmap >> 1;
        }
    }

    return status;
}


/*!****************************************************************************
*
* @par Description:
*    This function performs post controller intialization (scrub, periodic, auto
*    self refresh, auto power down, thermal throttle, etc.).
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    The status indicating the level of success in initializing the memory controllers.
*
* @author
*    mwuu
*
******************************************************************************/
unsigned mddr_mc_post_init(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan)
{
    unsigned status = COM_OK;
    uint8_t dimm_slot;
    uint64_t mddr_base_addr;
    uint16_t slot_bitmap;

    mddr_base_addr = mddr_base_addrs[ddr_chan];

    slot_bitmap=0;
    // enable slot
    // set slot ready
    for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        if (mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            slot_bitmap |= (0x1 << dimm_slot);
        }
    }

    // valid channel
    if(slot_bitmap != 0)
    {
        monaco_log(LOW, "\n===================================\n");
        monaco_log(CRITICAL, "| Controller post-Init on channel %1d |\n", hddrss[ddr_chan]);
        monaco_log(LOW, " ===================================\n");

        // Enable periodic auto refreshes on all valid ranks.
        mddr_set_reg(mddr_base_addr + MDDR_DDR_AUTO_REF_EN_OFFSET,  "DDR_AUTO_REF_EN", mddr_combined_valid_ranks);

        mddr_mc_enable_periodic_zqcal(mddr_base_addr, mddr_settings_ptr);

        // Enable self refresh if it is configured. The register value is already set appropriately.
#ifdef CONFIG_TESTOS_EMU
        mddr_set_reg(mddr_base_addr + MDDR_DDR_SELF_REF_CNTL_OFFSET, "DDR_SELF_REF_CNTL", 0x00a91620);
#else
        mddr_set_reg(mddr_base_addr + MDDR_DDR_SELF_REF_CNTL_OFFSET, "DDR_SELF_REF_CNTL", mddr_reg_vals.ddr_self_ref_cntl_val);
#endif

        // Enable power down if it is configured. The register value is already set appropriately.
        mddr_set_reg(mddr_base_addr + MDDR_DDR_PWR_DOWN_CNTL_OFFSET, "DDR_PWR_DOWN_CNTL", mddr_reg_vals.ddr_power_down_cntl_val);

        // Setup thermal control
        mddr_mc_set_thermal_control_reg_vals(mddr_base_addr);

        // Optionally enable thermal throttling after all settings are established.
        if (mddr_settings_ptr->therm_throttle_en)
        {
            mddr_mc_enable_thermal_control(mddr_base_addr);
        }

        // Setup Bus Utilization Monitor (BUM) control
        mddr_mc_set_bum_reg_vals(mddr_base_addr);

        if (common_cfg.has_ecc)
        {
            // If ECC is enabled, scrub and initialize
            if (mddr_settings_ptr->disable_ecc == false)
            {
                mddr_mc_ecc_scrub_init(mddr_base_addr, ddr_chan);
            }

            if (mddr_settings_ptr->disable_patrol_scrub == false)
            {
                // Start ECC Patrol Scrub..
                mddr_mc_ecc_scrub_start(mddr_base_addr, ddr_chan);
            }
        }

        if ((slot_bitmap & 0x1) > 0)
        {
            mddr_mc_slot_ready(mddr_base_addr, 0);
        }

        if (((slot_bitmap >> 1) & 0x1) > 0)
        {
            mddr_mc_slot_ready(mddr_base_addr, 1);
        }
    }

  return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the values for the registers found in a DDR
*    memory controller. This includes only the register whose value is fixed
*    and common accross all memory controllers.
*
*                                  @param
*    soc_hw_version         Provides the HW version of the target SoC.
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*                                  @param
*    latencies_ptr          The pointer to the structure containing the latency
*                             information.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_get_reg_vals
(
    soc_hw_version_t soc_hw_version,
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr,
    mddr_latencies_t *latencies_ptr
)
{
    uint8_t slot;
    uint8_t ddr_chan;
    mddr_therm_throttle_settings_t therm_throttle_settings;

    // Configure the default thermal throttling settings
    // values from HPG, DDR Command Thermal Throttling
    if (platform_mode != SILICON)
    {
        therm_throttle_settings.read_bl8_weight = THERM_WEIGHT_READ_BL8_EMU;
        therm_throttle_settings.read_bc4_weight = THERM_WEIGHT_READ_BC4_EMU;
        therm_throttle_settings.write_bl8_weight = THERM_WEIGHT_WRITE_BL8_EMU;
        therm_throttle_settings.write_bc4_weight = THERM_WEIGHT_WRITE_BC4_EMU;
        therm_throttle_settings.pchg_weight = THERM_WEIGHT_PCHG_EMU;
        therm_throttle_settings.act_weight = THERM_WEIGHT_ACT_EMU;
        therm_throttle_settings.throttle_high_wm = THERM_THROTTLE_HIGH_WM_EMU;
        therm_throttle_settings.throttle_low_wm = THERM_THROTTLE_LOW_WM_EMU;
        therm_throttle_settings.sum_deplete_val = THERM_LEAK_AMOUNT_EMU;
        therm_throttle_settings.sum_deplete_interval = THERM_LEAK_INTERVAL_EMU;
    }
    else
    {
        therm_throttle_settings.read_bl8_weight = THERM_WEIGHT_READ_BL8_SIL;
        therm_throttle_settings.read_bc4_weight = THERM_WEIGHT_READ_BC4_SIL;
        therm_throttle_settings.write_bl8_weight = THERM_WEIGHT_WRITE_BL8_SIL;
        therm_throttle_settings.write_bc4_weight = THERM_WEIGHT_WRITE_BC4_SIL;
        therm_throttle_settings.pchg_weight = THERM_WEIGHT_PCHG_SIL;
        therm_throttle_settings.act_weight = THERM_WEIGHT_ACT_SIL;
        therm_throttle_settings.throttle_high_wm = THERM_THROTTLE_HIGH_WM_SIL;
        therm_throttle_settings.throttle_low_wm = THERM_THROTTLE_LOW_WM_SIL;
        therm_throttle_settings.sum_deplete_val = THERM_LEAK_AMOUNT_SIL;
        therm_throttle_settings.sum_deplete_interval = THERM_LEAK_INTERVAL_SIL;
    }


    mddr_mc_get_timing_reg_vals(common_cfg_ptr, mddr_settings_ptr, latencies_ptr);

    for(slot = 0; slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++slot)
    {
        if (common_cfg.slot_config[slot].num_ranks != SPD_INVALID_RANK_COUNT)
        {
            mddr_reg_vals.dimm_slot_config_val[slot]  = mddr_mc_build_dimm_slot_config_reg_val(common_cfg_ptr, slot);
            mddr_reg_vals.dimm_slot_addr_val[slot]    = mddr_mc_build_dimm_slot_addr_reg_val(common_cfg_ptr, mddr_settings_ptr, slot);
        }
    }


    mddr_reg_vals.dimm_tech_val         = mddr_mc_build_dimm_tech_reg_val(common_cfg_ptr, mddr_settings_ptr);
    mddr_reg_vals.dataflow_cntl_val     = mddr_mc_build_dataflow_cntl_reg(common_cfg_ptr, mddr_settings_ptr);

    mddr_reg_vals.dataflow_cde_cntl_0_val     = mddr_mc_build_dataflow_cde_cntl_0_reg(common_cfg_ptr, mddr_settings_ptr);
    mddr_reg_vals.dataflow_cde_cntl_1_val     = mddr_mc_build_dataflow_cde_cntl_1_reg();
    mddr_reg_vals.dataflow_cde_cntl_2_val     = mddr_mc_build_dataflow_cde_cntl_2_reg();
    mddr_reg_vals.dataflow_cde_cntl_3_val     = mddr_mc_build_dataflow_cde_cntl_3_reg();
    mddr_reg_vals.dataflow_cde_cntl_4_val     = mddr_mc_build_dataflow_cde_cntl_4_reg();
    mddr_reg_vals.dataflow_cde_cntl_5_val     = mddr_mc_build_dataflow_cde_cntl_5_reg(mddr_settings_ptr);
    mddr_reg_vals.dataflow_cde_cntl_6_val     = mddr_mc_build_dataflow_cde_cntl_6_reg(mddr_settings_ptr);

    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        mddr_reg_vals.ddr_odt_wr_cntl_val[ddr_chan]   = mddr_mc_build_ddr_odt_wr_cntl_reg(ddr_chan);
        mddr_reg_vals.ddr_odt_rd_cntl_val[ddr_chan]   = mddr_mc_build_ddr_odt_rd_cntl_reg(ddr_chan);
    }

    mddr_reg_vals.cmd_exec_cntl_0_val   = mddr_mc_build_cmd_exec_cntl_0_reg(common_cfg_ptr, mddr_settings_ptr);
    mddr_reg_vals.cmd_exec_cntl_1_val   = mddr_mc_build_cmd_exec_cntl_1_reg();
    mddr_reg_vals.cmd_exec_cntl_2_val   = mddr_mc_build_cmd_exec_cntl_2_reg();
    mddr_reg_vals.cmd_exec_cntl_3_val   = mddr_mc_build_cmd_exec_cntl_3_reg(mddr_settings_ptr);
    mddr_reg_vals.cmd_exec_cntl_4_val   = mddr_mc_build_cmd_exec_cntl_4_reg();
    mddr_reg_vals.cmd_exec_cntl_5_val   = mddr_mc_build_cmd_exec_cntl_5_reg();
    mddr_reg_vals.cmd_exec_cntl_6_val   = mddr_mc_build_cmd_exec_cntl_6_reg();
    mddr_reg_vals.cmd_exec_cntl_7_val   = mddr_mc_build_cmd_exec_cntl_7_reg();
    mddr_reg_vals.addr_decode_cntl_val  = mddr_mc_build_addr_decode_cntl_reg(soc_hw_version, mddr_settings_ptr);


    mddr_reg_vals.wdb_flush_wm_val      = mddr_mc_build_wdb_flush_wm_reg();
    mddr_reg_vals.wdb_flush_cntl_val    = mddr_mc_build_wdb_flush_cntl_reg();
    mddr_reg_vals.wdb_flush_ph_val      = mddr_mc_build_wdb_flush_ph_reg();
    mddr_reg_vals.int0_cntl_val         = mddr_mc_build_int0_cntl_reg(mddr_settings_ptr);
    mddr_reg_vals.int1_cntl_val         = mddr_mc_build_int1_cntl_reg();
    mddr_reg_vals.err_cntl_val          = mddr_mc_build_err_cntl_reg(common_cfg_ptr, mddr_settings_ptr);
    mddr_reg_vals.err_cap_cntl_val      = mddr_mc_build_err_cap_cntl_reg();
    mddr_reg_vals.ecc_err_cntl_1_val    = mddr_mc_build_ecc_err_cntl_1_reg(mddr_settings_ptr);
    mddr_reg_vals.rd_wr_pref_cntl_val   = mddr_mc_build_rd_wr_pref_cntl_reg();
    mddr_reg_vals.tn_token_cnt_val      = mddr_mc_build_tn_token_cnt_reg();
    mddr_reg_vals.ddr_dfi_cntl_val      = mddr_mc_build_ddr_dfi_cntl_reg(mddr_settings_ptr);
    mddr_reg_vals.ddr_dfi_cntl_1_val    = mddr_mc_build_ddr_dfi_cntl_1_reg(mddr_settings_ptr);
    mddr_reg_vals.ddr_phy_cntl_val      = mddr_mc_build_ddr_phy_cntl_reg();
    mddr_reg_vals.ddr_self_ref_cntl_val = mddr_mc_build_ddr_self_ref_cntl_reg(mddr_settings_ptr);
    mddr_reg_vals.ddr_power_down_cntl_val = mddr_mc_build_ddr_power_down_cntl_reg(mddr_settings_ptr);
    mddr_reg_vals.ddr_ca_bus_cntl_val   = mddr_mc_build_ddr_ca_bus_cntl_reg(common_cfg_ptr, mddr_settings_ptr);
    mddr_reg_vals.ddr_dq_bus_cntl_val   = mddr_mc_build_ddr_dq_bus_cntl_reg(common_cfg_ptr);

    mddr_mc_get_thermal_control_reg_vals(&therm_throttle_settings);

    mddr_mc_get_bum_reg_vals(mddr_settings_ptr);

}



/*!****************************************************************************
*
* @par Description:
*    This function flushed the memory controller write data buffer for
*     watchdog reset in preperation for the 2nd reset.
*     WD reset sequence step 27.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_wd_flush_write_data_buff
(
    uint64_t mddr_base_addr
)
{
    // Flush the write data buffer in the controller
    //    D{0..5}_MDDR_DDR_MANUAL[FLUSH_WDB] = 1
    //    D{0..5}_MDDR_DDR_MANUAL[others] = 0
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OFFSET, "DDR_MANUAL", 0x1 << MANUAL_FLUSH_WDB___S);

}



/*!****************************************************************************
*
* @par Description:
*    This function waits until the write data buffer status indicates that
*     all the data has been written to memory for a single DDR channel for
*     watchdog reset.
*     WD reset sequence step 28.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    Timeout varies depending on target. 90ms for silicon and 1s for emulation.
*
******************************************************************************/
void mddr_mc_wd_wdb_clean_check_complete
(
    uint64_t mddr_base_addr
)
{
    uint32_t wait;
    uint32_t dev_state_mask;
    uint32_t exp_dev_state_val;


    if (platform_mode != SILICON)
    {
        wait = MILLI_SEC_PER_SEC;
    }
    else
    {
        wait = 90 * MILLI_SEC_PER_SEC;
    }


    dev_state_mask = SCRUB_STATUS_WDB_CLEAN___M << SCRUB_STATUS_WDB_CLEAN___S;
    exp_dev_state_val = SCRUB_STATUS_WDB_CLEAN_SET << SCRUB_STATUS_WDB_CLEAN___S;

    mddr_rd_chk_reg(mddr_base_addr, MDDR_SCRUB_STATUS_OFFSET,
                    dev_state_mask, exp_dev_state_val, wait);
}



/*!****************************************************************************
*
* @par Description:
*    This function puts the DRAM into self-refresh for watchdog reset.
*     WD reset sequence step 29.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_wd_enter_self_refresh
(
    uint64_t mddr_base_addr
)
{
    uint8_t cke_sel;
    uint32_t manual_cke_val;
    uint32_t dev_state_mask;
    uint32_t exp_dev_state_val;


    cke_sel = common_cfg.slots_cke_sel;

    // Enter self-refresh.
    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;
    manual_cke_val |= 0x1 << MANUAL_CKE_ENTER_SELF_REF_ASAP___S;

    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);

    // Wait for entry into self-refresh.
    dev_state_mask = DEVICE_STATE_CKE_IN_SELF_REF___M << DEVICE_STATE_CKE_IN_SELF_REF___S;
    exp_dev_state_val = cke_sel << DEVICE_STATE_CKE_IN_SELF_REF___S;
    mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, dev_state_mask, exp_dev_state_val, 30);
}



/*!****************************************************************************
*
* @par Description:
*    This function removes the DRAM from self-refresh for watchdog reset.
*     WD reset sequence step 19.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_wd_exit_self_refresh
(
    uint64_t mddr_base_addr
)
{
    uint8_t cke_sel;
    uint32_t manual_cke_val;
    uint32_t dev_state_mask;
    uint32_t exp_dev_state_val;


    cke_sel = common_cfg.slots_cke_sel;

    // Exit self-refresh.
    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;
    manual_cke_val |= 0x1 << MANUAL_CKE_EXIT_SELF_REF___S;

    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);

    // Wait for exit from self-refresh.
    dev_state_mask = DEVICE_STATE_CKE_IN_SELF_REF___M << DEVICE_STATE_CKE_IN_SELF_REF___S;
    exp_dev_state_val = 0x0 << DEVICE_STATE_CKE_IN_SELF_REF___S;
    mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, dev_state_mask, exp_dev_state_val, 30);
}



/*!****************************************************************************
*
* @par Description:
*    This function performs watchdog reset post controller reintialization
*     WD reset sequence steps 24 & 25.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    Based on mddr_mc_post_init()
*
******************************************************************************/
void mddr_mc_wd_post_reinit(uint8_t ddr_chan)
{
    uint8_t dimm_slot;
    uint64_t mddr_base_addr;
    uint16_t slot_bitmap;

    mddr_base_addr = mddr_base_addrs[ddr_chan];

    slot_bitmap=0;

    // enable slot
    // set slot ready
    for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        if (mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            slot_bitmap |= (0x1 << dimm_slot);
        }
    }

    // valid channel
    if(slot_bitmap != 0)
    {
        monaco_log(INFORMATIONAL, "\n ===========================================\n");
        monaco_log(CRITICAL, "| Controller Watchdog post-Init on channel %1d |\n", hddrss[ddr_chan]);
        monaco_log(INFORMATIONAL, " ===========================================\n");

        // Unfence PHY
        mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OFFSET, "DDR_MANUAL", 0x00000000);

        if ((slot_bitmap & 0x1) > 0)
        {
            mddr_mc_slot_ready(mddr_base_addr, 0);
        }

        if (((slot_bitmap >> 1) & 0x1) > 0)
        {
            mddr_mc_slot_ready(mddr_base_addr, 1);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function waits for a channel to enter self-refresh for watchdog reset.
*     WD reset sequence step 3.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_wd_wait_for_self_refresh
(
    uint64_t mddr_base_addr
)
{
    uint8_t cke_sel;
    uint32_t dev_state_mask;
    uint32_t exp_dev_state_val;


    // Get the active chip selects.
    cke_sel = common_cfg.slots_cke_sel;

    // Wait for entry into self-refresh.
    dev_state_mask = DEVICE_STATE_CKE_IN_SELF_REF___M << DEVICE_STATE_CKE_IN_SELF_REF___S;
    exp_dev_state_val = cke_sel << DEVICE_STATE_CKE_IN_SELF_REF___S;
    mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, dev_state_mask, exp_dev_state_val, 30);
}



/*!****************************************************************************
*
* @par Description:
*    Enable periodic auto refreshes on all valid ranks.
*      Auto-refresh should be re-enabled before step 10. This guarantees that
*      when the controller pulls the DRAM out of the SR later on, the
*      auto-refresh can be immediately picked up.
*      WD reset sequence between steps 9 & 10.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*   Must occur after mddr_mc_init() for mddr_combined_valid_ranks to be valid!!
*
******************************************************************************/
void mddr_mc_wd_enable_periodic_auto_refresh
(
    uint64_t mddr_base_addr
)
{
    // Enable periodic auto refreshes on all valid ranks.
    mddr_set_reg(mddr_base_addr + MDDR_DDR_AUTO_REF_EN_OFFSET,  "DDR_AUTO_REF_EN", mddr_combined_valid_ranks);
}



/******************************************************************************
* Local Functions
******************************************************************************/


/*!****************************************************************************
*
* @par Description:
*    This function sets the values for the timing registers found in a DDR
*    memory controller and enables their use.
*
*                                  @param
*    mddr_base_addr        The base address of the configuration registers for
*                           the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_set_timing_reg_vals
(
    uint64_t mddr_base_addr,
    uint8_t ddr_chan
)
{
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_RCD_OFFSET,              "TIMING_RCD",             mddr_reg_vals.timing_regs.rcd_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_RDWR_0_OFFSET,      "TIMING_DRAM_RDWR_0",     mddr_reg_vals.timing_regs.timing_rdwr0_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_RDWR_1_OFFSET,      "TIMING_DRAM_RDWR_1",     mddr_reg_vals.timing_regs.timing_rdwr1_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_RDWR_2_OFFSET,      "TIMING_DRAM_RDWR_2",     mddr_reg_vals.timing_regs.timing_rdwr2_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_RDWR_3_OFFSET,      "TIMING_DRAM_RDWR_3",     mddr_reg_vals.timing_regs.timing_rdwr3_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_RDWR_4_OFFSET,      "TIMING_DRAM_RDWR_4",     mddr_reg_vals.timing_regs.timing_rdwr4_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_ADJ_RDWR_0_OFFSET,       "TIMING_ADJ_RDWR_0",      mddr_reg_vals.timing_regs.adj_rdwr0_val[ddr_chan]);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_ADJ_RDWR_1_OFFSET,       "TIMING_ADJ_RDWR_1",      mddr_reg_vals.timing_regs.adj_rdwr1_val[ddr_chan]);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_AUTO_REF_0_OFFSET,  "TIMING_DRAM_AUTO_REF_0", mddr_reg_vals.timing_regs.auto_ref0_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_AUTO_REF_1_OFFSET,  "TIMING_DRAM_AUTO_REF_1", mddr_reg_vals.timing_regs.auto_ref1_val);
    // MDDR_TIMING_DRAM_AUTO_REF_2_OFFSET not in short init.
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_AUTO_REF_2_OFFSET,  "TIMING_DRAM_AUTO_REF_2", mddr_reg_vals.timing_regs.auto_ref2_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_ADJ_AUTO_REF_OFFSET,     "TIMING_ADJ_AUTO_REF",    mddr_reg_vals.timing_regs.adj_auto_ref_val[ddr_chan]);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_PWR_DOWN_0_OFFSET,  "TIMING_DRAM_PWR_DOWN_0", mddr_reg_vals.timing_regs.pwr_down0_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_PWR_DOWN_1_OFFSET,  "TIMING_DRAM_PWR_DOWN_1", mddr_reg_vals.timing_regs.pwr_down1_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_SELF_REF_0_OFFSET,  "TIMING_DRAM_SELF_REF_0", mddr_reg_vals.timing_regs.self_ref0_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_SELF_REF_1_OFFSET,  "TIMING_DRAM_SELF_REF_1", mddr_reg_vals.timing_regs.self_ref1_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_SELF_REF_2_OFFSET,  "TIMING_DRAM_SELF_REF_2", mddr_reg_vals.timing_regs.self_ref2_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_MPSM_OFFSET,        "TIMING_DRAM_MPSM",       mddr_reg_vals.timing_regs.mpsm_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_ZQ_0_OFFSET,        "TIMING_DRAM_ZQ_0",       mddr_reg_vals.timing_regs.zq0_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_ZQ_1_OFFSET,        "TIMING_DRAM_ZQ_1",       mddr_reg_vals.timing_regs.zq1_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_ADJ_ZQ_OFFSET,           "TIMING_ADJ_ZQ",          mddr_reg_vals.timing_regs.zq_adj_val[ddr_chan]);

    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_MR_0_OFFSET,        "TIMING_DRAM_MR_0",       mddr_reg_vals.timing_regs.mr0_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_MR_1_OFFSET,        "TIMING_DRAM_MR_1",       mddr_reg_vals.timing_regs.mr1_val);
#ifdef CONFIG_TESTOS_EMU
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DQ_BUS_OFFSET,           "TIMING_DQ_BUS",          0x12);
#else
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DQ_BUS_OFFSET,           "TIMING_DQ_BUS",          mddr_reg_vals.timing_regs.dq_bus_val);
#endif
#ifdef CONFIG_TESTOS_EMU
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DFI_0_OFFSET,            "TIMING_DFI_0",           0x00011313);
#else
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DFI_0_OFFSET,            "TIMING_DFI_0",           mddr_reg_vals.timing_regs.dfi_0_val);
#endif
    // MDDR_TIMING_DFI_1_OFFSET not in short init.
#ifdef CONFIG_TESTOS_EMU
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DFI_1_OFFSET,            "TIMING_DFI_1",           0x00a409ec);
#else
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DFI_1_OFFSET,            "TIMING_DFI_1",           mddr_reg_vals.timing_regs.dfi_1_val);
#endif
#ifdef CONFIG_TESTOS_EMU
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DFI_2_OFFSET,            "TIMING_DFI_2",           0x00000611);
#else
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DFI_2_OFFSET,            "TIMING_DFI_2",           mddr_reg_vals.timing_regs.dfi_2_val);
#endif
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_ODT_OFFSET,              "TIMING_ODT",             mddr_reg_vals.timing_regs.odt_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_GEAR_DOWN_OFFSET,        "TIMING_GEAR_DOWN",       mddr_reg_vals.timing_regs.gear_down_val);

    monaco_log(INFORMATIONAL, "     Enabling controller timing settings\n\n");

    // enables timing values
    mddr_set_reg(mddr_base_addr + MDDR_CSR_CNTL_OFFSET,                "CSR_CNTL",       0x00000001);

}



/*!****************************************************************************
*
* @par Description:
*    This function initializes and starts ECC scrubbing for a single DDR
*     channel.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*                                  @param
*    ddr_chan               DDR channel to perform function on.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_ecc_scrub_init
(
    uint64_t mddr_base_addr,
    uint8_t ddr_chan
)
{

    // Start filling of ECC and memory for initial scrub state.
    mddr_mc_ecc_scrub_start_init(mddr_base_addr);

    // Wait with timeout for filling of ECC and memory to complete.
    mddr_mc_ecc_scrub_check_complete(mddr_base_addr, ddr_chan);

    // Stop filling once filling has finished.
    mddr_mc_ecc_scrub_stop_init(mddr_base_addr);

}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the values for the thermal throttling control
*    registers found in a DDR memory controller. This includes only the
*    settings with the enable intentionally cleared to disable throttling.
*
*                                  @param
*    therm_throttle_settings_ptr       The pointer to the structure containing the
*                                       thermal settings information.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_get_thermal_control_reg_vals
(
     mddr_therm_throttle_settings_t *therm_throttle_settings_ptr
)
{
    mddr_reg_vals.thermal_regs.ddr_thermal_cntl_0_val = mddr_mc_build_thermal_cntl_0_reg(therm_throttle_settings_ptr);
    mddr_reg_vals.thermal_regs.ddr_thermal_cntl_1_val = mddr_mc_build_thermal_cntl_1_reg(therm_throttle_settings_ptr);
    mddr_reg_vals.thermal_regs.ddr_thermal_cntl_2_val = mddr_mc_build_thermal_cntl_2_reg(therm_throttle_settings_ptr);
    mddr_reg_vals.thermal_regs.ddr_thermal_cntl_3_val = mddr_mc_build_thermal_cntl_3_reg(therm_throttle_settings_ptr);
    mddr_reg_vals.thermal_regs.ddr_thermal_cntl_4_val = mddr_mc_build_thermal_cntl_4_reg(therm_throttle_settings_ptr);
}



/*!****************************************************************************
*
* @par Description:
*    This function sets the values for the thermal throttling control registers
*    found in a DDR memory controller. Throttling will always be disabled by
*    this call since the stored settings always have the enable clear.
*
*                                  @param
*    mddr_base_addr        The base address of the configuration registers for
*                           the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_set_thermal_control_reg_vals
(
    uint64_t mddr_base_addr
)
{
    // Thermal control 0 is set first with enable off to disable the controls
    //  before updating the other settings.
    mddr_set_reg(mddr_base_addr + MDDR_DDR_THERMAL_CNTL_1_OFFSET, "DDR_THERMAL_CNTL_1", mddr_reg_vals.thermal_regs.ddr_thermal_cntl_1_val);
    mddr_set_reg(mddr_base_addr + MDDR_DDR_THERMAL_CNTL_2_OFFSET, "DDR_THERMAL_CNTL_2", mddr_reg_vals.thermal_regs.ddr_thermal_cntl_2_val);
    mddr_set_reg(mddr_base_addr + MDDR_DDR_THERMAL_CNTL_3_OFFSET, "DDR_THERMAL_CNTL_3", mddr_reg_vals.thermal_regs.ddr_thermal_cntl_3_val);
    mddr_set_reg(mddr_base_addr + MDDR_DDR_THERMAL_CNTL_4_OFFSET, "DDR_THERMAL_CNTL_4", mddr_reg_vals.thermal_regs.ddr_thermal_cntl_4_val);
    // Do last since enable bit is here
    mddr_set_reg(mddr_base_addr + MDDR_DDR_THERMAL_CNTL_0_OFFSET, "DDR_THERMAL_CNTL_0", mddr_reg_vals.thermal_regs.ddr_thermal_cntl_0_val);
}



/*!****************************************************************************
*
* @par Description:
*    This function enables the thermal throttling controls found in a DDR
*    memory controller.
*
*                                  @param
*    mddr_base_addr        The base address of the configuration registers for
*                           the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_enable_thermal_control
(
    uint64_t mddr_base_addr
)
{
    uint32_t thermal_cntl_0_val;
    uint32_t en_throttling = 0x1;


    // The stored settings always have the enable clear.
    thermal_cntl_0_val = mddr_reg_vals.thermal_regs.ddr_thermal_cntl_0_val;
    thermal_cntl_0_val |= en_throttling & THERMAL_CNTL_0_EN_THROTTLING___M << THERMAL_CNTL_0_EN_THROTTLING___S;

    mddr_set_reg(mddr_base_addr + MDDR_DDR_THERMAL_CNTL_0_OFFSET, "DDR_THERMAL_CNTL_0", thermal_cntl_0_val);
}



/*!****************************************************************************
*
* @par Description:
*    This function disables the thermal throttling controls found in a DDR
*    memory controller.
*
*                                  @param
*    mddr_base_addr        The base address of the configuration registers for
*                           the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_disable_thermal_control
(
    uint64_t mddr_base_addr
)
{
    // The stored settings always have the enable clear.
    mddr_set_reg(mddr_base_addr + MDDR_DDR_THERMAL_CNTL_0_OFFSET, "DDR_THERMAL_CNTL_0",
                 mddr_reg_vals.thermal_regs.ddr_thermal_cntl_0_val);
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the values for the Bus Utilization Monitor (BUM)
*     registers found in a DDR memory controller.
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            BUM settings information.
*
* @return
*    None
*
* @author
*    anthonyf
*
******************************************************************************/
void mddr_mc_get_bum_reg_vals
(
     mddr_settings_t *mddr_settings_ptr
)
{
    uint8_t ddr_bum_perf_idx;

    // Start by setting disable bits for all events
    mddr_reg_vals.bum_regs.dcvs_cntl_val = DCVS_CNTL_ALL_CNT_DISABLE___M<<DCVS_CNTL_ALL_CNT_DISABLE___S;


    // Build DCVS Threshold register values for BCQ Full Event

    monaco_log(MEDIUM, "Checking Bus Utilization Monitor threshhold limits for BCQ Full event.\n");

    for (ddr_bum_perf_idx = 0; ddr_bum_perf_idx < DDR_BUM_PERF_IDX_MAX; ddr_bum_perf_idx++)
    {
        mddr_mc_check_bum_thresholds(&mddr_settings_ptr->bum_settings.bcqfull, ddr_bum_perf_idx);

        mddr_reg_vals.bum_regs.dcvs_bcqfull_high_threshold_val[ddr_bum_perf_idx] = mddr_mc_build_dcvs_high_threshold_reg(&mddr_settings_ptr->bum_settings.bcqfull, ddr_bum_perf_idx);
        mddr_reg_vals.bum_regs.dcvs_bcqfull_low_threshold_val[ddr_bum_perf_idx]  = mddr_mc_build_dcvs_low_threshold_reg(&mddr_settings_ptr->bum_settings.bcqfull, ddr_bum_perf_idx);
    }

    mddr_reg_vals.bum_regs.dcvs_cntl_val = mddr_mc_build_bcqfull_dcvs_cnt_reg(&mddr_settings_ptr->bum_settings.bcqfull);


    // Build DCVS Threshold register values for Busy Event

    monaco_log(MEDIUM, "Checking Bus Utilization Monitor threshhold limits for Busy event.\n");

    for (ddr_bum_perf_idx = 0; ddr_bum_perf_idx < DDR_BUM_PERF_IDX_MAX; ddr_bum_perf_idx++)
    {

        mddr_mc_check_bum_thresholds(&mddr_settings_ptr->bum_settings.busy, ddr_bum_perf_idx);

        mddr_reg_vals.bum_regs.dcvs_busy_high_threshold_val[ddr_bum_perf_idx]    = mddr_mc_build_dcvs_high_threshold_reg(&mddr_settings_ptr->bum_settings.busy, ddr_bum_perf_idx);
        mddr_reg_vals.bum_regs.dcvs_busy_low_threshold_val[ddr_bum_perf_idx]     = mddr_mc_build_dcvs_low_threshold_reg(&mddr_settings_ptr->bum_settings.busy, ddr_bum_perf_idx);
    }

    mddr_reg_vals.bum_regs.dcvs_cntl_val = mddr_mc_build_busy_dcvs_cnt_reg(&mddr_settings_ptr->bum_settings.busy);

}


/*!****************************************************************************
*
* @par Description:
*    This function sets the values for the Bus Utilization Monitor (BUM)
*    registers found in a DDR memory controller.
*
*                                  @param
*    mddr_base_addr        The base address of the configuration registers for
*                           the memory controller.
*
* @return
*    None
*
* @author
*    anthonyf
*
******************************************************************************/
void mddr_mc_set_bum_reg_vals
(
    uint64_t mddr_base_addr
)
{
    uint8_t ddr_bum_perf_idx;

    uint32_t bcqfull_high_threshold_val;
    uint32_t bcqfull_low_threshold_val;
    uint32_t busy_high_threshold_val;
    uint32_t busy_low_threshold_val;


    // Thresholds are set first with enable off to disable the controls
    for (ddr_bum_perf_idx = 0; ddr_bum_perf_idx < DDR_BUM_PERF_IDX_MAX; ddr_bum_perf_idx++)
    {
        bcqfull_high_threshold_val = mddr_reg_vals.bum_regs.dcvs_bcqfull_high_threshold_val[ddr_bum_perf_idx];
        bcqfull_low_threshold_val = mddr_reg_vals.bum_regs.dcvs_bcqfull_low_threshold_val[ddr_bum_perf_idx];
        busy_high_threshold_val = mddr_reg_vals.bum_regs.dcvs_busy_high_threshold_val[ddr_bum_perf_idx];
        busy_low_threshold_val = mddr_reg_vals.bum_regs.dcvs_busy_low_threshold_val[ddr_bum_perf_idx];

        if (ddr_bum_perf_idx == 3)
        {
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BCQFULL_HIGH_THRESHOLD_4_OFFSET, "DCVS_BCQFULL_HIGH_THRESHOLD_4", bcqfull_high_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BCQFULL_LOW_THRESHOLD_4_OFFSET, "DCVS_BCQFULL_LOW_THRESHOLD_4", bcqfull_low_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BUSY_HIGH_THRESHOLD_4_OFFSET, "DCVS_BUSY_HIGH_THRESHOLD_4", busy_high_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BUSY_LOW_THRESHOLD_4_OFFSET, "DCVS_BUSY_LOW_THRESHOLD_4", busy_low_threshold_val);
        }
        else if (ddr_bum_perf_idx == 2)
        {
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BCQFULL_HIGH_THRESHOLD_3_OFFSET, "DCVS_BCQFULL_HIGH_THRESHOLD_3", bcqfull_high_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BCQFULL_LOW_THRESHOLD_3_OFFSET, "DCVS_BCQFULL_LOW_THRESHOLD_3", bcqfull_low_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BUSY_HIGH_THRESHOLD_3_OFFSET, "DCVS_BUSY_HIGH_THRESHOLD_3", busy_high_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BUSY_LOW_THRESHOLD_3_OFFSET, "DCVS_BUSY_LOW_THRESHOLD_3", busy_low_threshold_val);
        }
        else if (ddr_bum_perf_idx == 1)
        {
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BCQFULL_HIGH_THRESHOLD_2_OFFSET, "DCVS_BCQFULL_HIGH_THRESHOLD_2", bcqfull_high_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BCQFULL_LOW_THRESHOLD_2_OFFSET, "DCVS_BCQFULL_LOW_THRESHOLD_2", bcqfull_low_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BUSY_HIGH_THRESHOLD_2_OFFSET, "DCVS_BUSY_HIGH_THRESHOLD_2", busy_high_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BUSY_LOW_THRESHOLD_2_OFFSET, "DCVS_BUSY_LOW_THRESHOLD_2", busy_low_threshold_val);
        }
        else
        {
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BCQFULL_HIGH_THRESHOLD_1_OFFSET, "DCVS_BCQFULL_HIGH_THRESHOLD_1", bcqfull_high_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BCQFULL_LOW_THRESHOLD_1_OFFSET, "DCVS_BCQFULL_LOW_THRESHOLD_1", bcqfull_low_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BUSY_HIGH_THRESHOLD_1_OFFSET, "DCVS_BUSY_HIGH_THRESHOLD_1", busy_high_threshold_val);
            mddr_set_reg(mddr_base_addr + MDDR_DCVS_BUSY_LOW_THRESHOLD_1_OFFSET, "DCVS_BUSY_LOW_THRESHOLD_1", busy_low_threshold_val);
        }
    }

    // Do last since enable bit is here
    mddr_set_reg(mddr_base_addr + MDDR_DCVS_CNTL_OFFSET, "DCVS_CNTL", mddr_reg_vals.bum_regs.dcvs_cntl_val);
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the DIMM tech register value using the provided
*    configuration.
*
*                                  @param
*    common_cfg_ptr     The pointer to the structure containing the
*                       configuration information.
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                       settings information.
*
*
* @return
*    The DIMM tech register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_dimm_tech_reg_val
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t dimm_tech_val = 0x00000000;
    uint8_t dimm_tech_device;
    char *type_name;


    if (mddr_settings_ptr->num_dimm_slots == 2)
    {
        dimm_tech_val = dimm_tech_val | (DIMM_TECH_NUM_DIMM_SLOTS_2 << DIMM_TECH_NUM_DIMM_SLOTS___S);
    }

    // shared DIMM clock
    if (mddr_settings_ptr->shared_dimm_clk == true)
    {
        dimm_tech_val = dimm_tech_val | (DIMM_TECH_SHARED_DIMM_CLK_YES << DIMM_TECH_SHARED_DIMM_CLK___S);
    }

    // device type
    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR3)
    {
        dimm_tech_device = DIMM_TECH_DEVICE_DDR3;
        type_name = "DDR3";
    }
    else    // DDR4
    {
        dimm_tech_device = DIMM_TECH_DEVICE_DDR4;
        type_name = "DDR4";
    }

    dimm_tech_val = dimm_tech_val | dimm_tech_device;

    // width
    if (common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X4)
    {
        dimm_tech_val=dimm_tech_val|(DIMM_TECH_DRAM_WIDTH_X4 << DIMM_TECH_DRAM_WIDTH___S);
    }
    else if((common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X8) || (common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X16))
    {
        dimm_tech_val = dimm_tech_val |(DIMM_TECH_DRAM_WIDTH_X8_X16 << DIMM_TECH_DRAM_WIDTH___S);
    }
    else    // if (sdram_width == SPD_SDRAM_WIDTH_X32)
    {
        monaco_log(HIGH, "   ERROR x32 device detected\n");
    }

    // module type
    if (common_cfg_ptr->mod_type == SPD_MODULE_TYPE_RDIMM)
    {
        dimm_tech_val = dimm_tech_val | (DIMM_TECH_DIMM_TYPE_RDIMM << DIMM_TECH_DIMM_TYPE___S);
    }
    else if (common_cfg_ptr->mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
    {
        dimm_tech_val = dimm_tech_val|(DIMM_TECH_DIMM_TYPE_LRDIMM << DIMM_TECH_DIMM_TYPE___S);
    }
    else if (common_cfg_ptr->mod_type == SPD_MODULE_TYPE_UDIMM)
    {
        dimm_tech_val = dimm_tech_val|(DIMM_TECH_DIMM_TYPE_UDIMM << DIMM_TECH_DIMM_TYPE___S);
    }
    //May need the following for emulation experiments
    #if 0
    else if ((common_cfg_ptr->mod_type == SPD_MODULE_SOUDIMM) ||
             (common_cfg_ptr->mod_type == SPD_MODULE_SODIMM))
    {
        dimm_tech_val = dimm_tech_val | (DIMM_TECH_DIMM_TYPE_UDIMM << DIMM_TECH_DIMM_TYPE___S);
    }
    #endif
    else
    {
        monaco_log(HIGH, "   ERROR unrecognized %s Device (0x%2.2x)\n", type_name , common_cfg_ptr->mod_type);
    }

    return dimm_tech_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the DIMM slot config register value using the
*    provided configuration.
*
*                                  @param
*    common_cfg_ptr     The pointer to the structure containing the
*                       configuration information.
*                                  @param
*    slot               DIMM slot associated to the register value being
*                        built.
*
*
* @return
*    The slot config register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_dimm_slot_config_reg_val
(
    mddr_common_cfg_t *common_cfg_ptr,
    uint8_t slot
)
{
    uint32_t dimm_slot_config_val = 0x00000000;
    uint32_t num_rows;


    // slot enable bit 27
    dimm_slot_config_val = 0x1 << SLOT_CONFIG_SLOT_EN___S;

    // mirror bit 26

    if(common_cfg_ptr->slot_config[slot].ca_mirrored)
    {
        dimm_slot_config_val = dimm_slot_config_val | (0x01 << SLOT_CONFIG_CA_MIRROR___S);
    }

    // device package 25:24
    if (common_cfg_ptr->is_3DS)
    {
        dimm_slot_config_val = dimm_slot_config_val | (0x1 << SLOT_CONFIG_3DS___S);

        // sub ranks at 13:12 for 3DS
        // Invalid die counts already filtered by mddr_verify_dimms()
        if (common_cfg_ptr->slot_config[slot].die_count == 8)   // set 8 sub ranks
        {
            dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_SUB_RANKS_8 << SLOT_CONFIG_SUB_RANKS___S);
        }
        else if (common_cfg_ptr->slot_config[slot].die_count == 4)   // set 4 sub ranks
        {
            dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_SUB_RANKS_4 << SLOT_CONFIG_SUB_RANKS___S);
        }
        else if (common_cfg_ptr->slot_config[slot].die_count == 2)   // set 2 sub ranks
        {
            dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_SUB_RANKS_2 << SLOT_CONFIG_SUB_RANKS___S);
        }
        else
        {
            // default single die device.
        }
    }

    // num clk per dimm at bit 20 (0=1 clock, 1=2 clocks)
    if ((common_cfg_ptr->slot_config[slot].num_ranks > 1) && (common_cfg_ptr->mod_type == SPD_MODULE_TYPE_UDIMM))
    {
        dimm_slot_config_val = dimm_slot_config_val | (0x1 << SLOT_CONFIG_NUM_CLK___S);
    }

    // num chip selects at 17:16
    if (common_cfg_ptr->slot_config[slot].num_ranks == 4)
    {
        dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_NUM_CS_4 << SLOT_CONFIG_NUM_CS___S);
    }
    else if (common_cfg_ptr->slot_config[slot].num_ranks == 2)
    {
        dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_NUM_CS_2 << SLOT_CONFIG_NUM_CS___S);
    }
    else if (common_cfg_ptr->slot_config[slot].num_ranks == 1)
    {
        dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_NUM_CS_1 << SLOT_CONFIG_NUM_CS___S);
    }

    // row bits at 10:8
    num_rows = common_cfg_ptr->slot_config[slot].num_rows - SLOT_CONFIG_ROWS_SCALE_OFFSET;
    dimm_slot_config_val = dimm_slot_config_val | (num_rows << SLOT_CONFIG_ROW___S);

    // column bits at 5:4
    if (common_cfg_ptr->slot_config[slot].num_columns == 10)
    {
        dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_COL_10 << SLOT_CONFIG_COL___S);
    }
    else if (common_cfg_ptr->slot_config[slot].num_columns == 11)
    {
        dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_COL_11 << SLOT_CONFIG_COL___S);
    }
    else if (common_cfg_ptr->slot_config[slot].num_columns == 12)
    {
        dimm_slot_config_val = dimm_slot_config_val | (SLOT_CONFIG_COL_12 << SLOT_CONFIG_COL___S);
    }

    // banks/bank group bits at 1:0
    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        if (common_cfg_ptr->slot_config[slot].num_bank_groups == 4)     // if 4 bank groups
        {
            // 16 banks total
            dimm_slot_config_val = dimm_slot_config_val | SLOT_CONFIG_BANK_GROUP_BITS_2;
        }
    }

    monaco_log(INFORMATIONAL, "          rows = %d, cols = %d, die_count = %d, mirrored = %d\n",
                common_cfg_ptr->slot_config[slot].num_rows, common_cfg_ptr->slot_config[slot].num_columns,
                common_cfg_ptr->slot_config[slot].die_count, common_cfg_ptr->slot_config[slot].ca_mirrored);


    return dimm_slot_config_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the DIMM slot address register value using the
*    provided configuration.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    slot                   DIMM slot associated to the register value being
*                            built.
*
*
* @return
*    The slot address register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_dimm_slot_addr_reg_val
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr,
    uint8_t slot
)
{
    uint32_t dimm_slot_addr_val;
    uint32_t capacity;
    uint32_t previous_size_gb;
    uint32_t mc_slot_base_addr;


    // Capacity is the log2 representation of DIMM size in GB.
    capacity = common_cfg_ptr->slot_config[slot].dimm_size_mb / MB_PER_GB;
    capacity = com_log2(capacity);


    // Dependent on the interleave mode when dual slot.

    // Base_Address(N) = [Capacity * (MDDR_ADDR_DECODE_CNTL[ADDR_INTERLEAVE_MODE]+1) * 2 * (MDDR_ADDR_DECODE_CNTL[EN_INTERLEAVE_DIMM] + 1) *N]
    //  where N = 0, 1, 2, 3... such that the DIMM remains in the DRAM QSB address space.

    if ((mddr_settings_ptr->dimm_intlv_en) || (slot == 0))
    {
        mc_slot_base_addr = QSB_MEM_BASE_MSB;
    }
    else
    {
        //
        // Slot 1 with interleaving disabled.
        //

        // Amount of memory provided by all slot 0 DIMMs in GB.
        previous_size_gb  = common_cfg_ptr->slot_config[0].dimm_size_mb / MB_PER_GB;
        previous_size_gb *= num_chans_poped;

        //  Use << 2 to align to bits 31:28 since the reg starts with bit 28 of the QSB address.
        mc_slot_base_addr = QSB_MEM_BASE_MSB + (previous_size_gb << 2);
    }


    dimm_slot_addr_val  = (capacity & SLOT_ADDR_CAPACITY___M) << SLOT_ADDR_CAPACITY___S;
    dimm_slot_addr_val |= (mc_slot_base_addr & SLOT_ADDR_BASE_ADDR___M) << SLOT_ADDR_BASE_ADDR___S;


    return dimm_slot_addr_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the dataflow control register value using the
*    provided configuration.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
*
* @return
*    The dataflow control register value.
*
* @author
*    gkowis
*
* @par Notes:
*    The configuration reflects what DIMMs are present in the system and the
*    settings reflect the desired configurable options.
*
******************************************************************************/
uint32_t mddr_mc_build_dataflow_cntl_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t dataflow_cntl_val;
    mddr_ddr_dbi_t dbi_mode;
    uint8_t dbi_val = DATAFLOW_CNTL_DBI_OFF;


    dataflow_cntl_val = 0x00000000;

    // x4 requires RMW
    // DM and RMW are mutually exclusive
    // ECC requires RMW, and no data scramble
    // DM requires no DBI write, x8, no ECC, no RMW
    // DBI requires DDR4 and x8 or x16
    // DBI write requires no DM (mutually exclusive)

    // priority  x4 (set RMW)>>scrambling>>ECC>>tdqs>>DBI>>DM??
    // if ECC available and ECC desired, and RS enable=0, compression=0
    if ((common_cfg_ptr->has_ecc) && (mddr_settings_ptr->disable_ecc == false) &&
       ((mddr_settings_ptr->ecc_wrrd_mode & 0x0C) == 0x0) && (mddr_settings_ptr->comp_settings.comp_mode == DDR_COMP_DISABLED))
    {
        dataflow_cntl_val |= DATAFLOW_CNTL_EN_ECC;
    }

    // spec to be updated to reflect that scrambling is independent of all other settings
    if (mddr_settings_ptr->mddr_scrambling_en)
    {
        dataflow_cntl_val |= 0x1 << DATAFLOW_CNTL_EN_SCRAMBLING___S;
    }


    dbi_mode = mddr_settings_ptr->dbi_mode;

    if (dbi_mode != DDR_DBI_OFF)
    {
        if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR3)
        {
            monaco_log(HIGH, "ERROR, DBI is not available on DDR3, overriding MDDR_DBI_WR_RD_EN = %u setting.\n",mddr_settings_ptr->dbi_mode);
            mddr_settings_ptr->dbi_mode = DDR_DBI_OFF;
        }
        else if (common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X4)
        {
            monaco_log(HIGH, "ERROR, DBI is not available on x4 DRAM devices, overriding DBI setting");
            mddr_settings_ptr->dbi_mode = DDR_DBI_OFF;
        }
        else    // DDR4 and x8
        {
            if(dbi_mode == DDR_DBI_READ)
            {
                dbi_val = DATAFLOW_CNTL_DBI_RD;
            }
            else if(dbi_mode == DDR_DBI_WRITE)
            {
                dbi_val = DATAFLOW_CNTL_DBI_WR;
            }
            else
            {
                // DDR_DBI_READ_WRITE
                dbi_val = DATAFLOW_CNTL_DBI_RW;
            }
        }
    }

    dataflow_cntl_val |= dbi_val << DATAFLOW_CNTL_EN_DBI___S;


    return dataflow_cntl_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the dataflow cde control 0 register value using the
*    provided configuration.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
*
* @return
*    The dataflow cde control 0 register value.
*
* @author
*    lchavani/anthonyf
*
* @par Notes:
*    The configuration reflects what DIMMs are present in the system and the
*    settings reflect the desired configurable options.
*
******************************************************************************/
uint32_t mddr_mc_build_dataflow_cde_cntl_0_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t dataflow_cde_cntl_0_val;
    uint32_t en_rs_wr;
    uint32_t en_rs_rd;
    uint32_t en_comp;
    uint32_t en_decomp;
    uint32_t decomp_fn_dis = 0x0;
    uint32_t dis_nwdb_entry = 0x0;
    uint32_t dis_rx_clean = 0x0;
    uint32_t tx_clean = 0x0;
    uint32_t snp_rslt_clean = 0x0;

    if (mddr_settings_ptr->comp_settings.comp_mode)
    {
        en_comp = 0x1;
        en_decomp = 0x1;

        // Setting this bit is essential for performance improvement with compression.
        // If this bit isn't set, the controller will perform a R/M/W for any non-full line QSB write, as it will not be
        // storing clean data received from the L3, and this would definitely lower the performance with compression enabled.
        dis_rx_clean = 0x1;
    }
    else
    {
        en_comp = 0x0;
        en_decomp = 0x0;
        dis_rx_clean = 0x0;
    }


    if ((common_cfg_ptr->has_ecc) &&                                           // DIMMs have ECC
        (mddr_settings_ptr->disable_ecc == false) &&                           // and ECC is enabled
        ((mddr_settings_ptr->ecc_wrrd_mode & (RS_WR | RS_RD)) > 0x0))          // and ECC is Reed-Solomon
    {
        en_rs_wr = (mddr_settings_ptr->ecc_wrrd_mode & RS_WR) >> 0x02;
        en_rs_rd = (mddr_settings_ptr->ecc_wrrd_mode & RS_RD) >> 0x03;
    }
    else
    {
        en_rs_wr = 0x0;
        en_rs_rd = 0x0;
    }

    dataflow_cde_cntl_0_val  = en_rs_wr << DATAFLOW_CDE_CNTL_0_EN_RS_WR___S;
    dataflow_cde_cntl_0_val |= en_rs_rd << DATAFLOW_CDE_CNTL_0_EN_RS_RD___S;
    dataflow_cde_cntl_0_val |= en_comp << DATAFLOW_CDE_CNTL_0_EN_COMP___S;
    dataflow_cde_cntl_0_val |= en_decomp << DATAFLOW_CDE_CNTL_0_EN_DECOMP___S;
    dataflow_cde_cntl_0_val |= (mddr_settings_ptr->rs_quad_det_en & DATAFLOW_CDE_CNTL___M) << DATAFLOW_CDE_CNTL_0_DBL_QUAD_DET___S;
    dataflow_cde_cntl_0_val |= (decomp_fn_dis & DATAFLOW_CDE_CNTL___M) << DATAFLOW_CDE_CNTL_0_DECOMP_FN_DIS___S;
    dataflow_cde_cntl_0_val |= (dis_nwdb_entry & DATAFLOW_CDE_CNTL_0_DIS_NWDB_ENTRY___M) << DATAFLOW_CDE_CNTL_0_DIS_NWDB_ENTRY___S;
    dataflow_cde_cntl_0_val |= (dis_rx_clean & DATAFLOW_CDE_CNTL___M) << DATAFLOW_CDE_CNTL_0_DIS_RX_CLEAN___S;
    dataflow_cde_cntl_0_val |= (tx_clean & DATAFLOW_CDE_CNTL___M) << DATAFLOW_CDE_CNTL_0_TX_CLEAN___S;
    dataflow_cde_cntl_0_val |= (snp_rslt_clean & DATAFLOW_CDE_CNTL___M) << DATAFLOW_CDE_CNTL_0_SNP_RSLT_CLEAN___S;

    return dataflow_cde_cntl_0_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the dataflow cde control 1 register value using the
*    provided configuration.
*
* @return
*    The dataflow cde control 1 register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_dataflow_cde_cntl_1_reg(void)
{
    uint32_t dataflow_cde_cntl_1_val = 0x0;

    dataflow_cde_cntl_1_val  = CDE_COMP_WR_IMPACT_PCHG << DATAFLOW_CDE_CNTL_1_COMP_WR_IMPACT_PCHG___S;
    dataflow_cde_cntl_1_val |= CDE_COMP_WR_IMPACT_ACT << DATAFLOW_CDE_CNTL_1_COMP_WR_IMPACT_ACT___S;

    return dataflow_cde_cntl_1_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the dataflow cde control 2 register value using the
*    provided configuration.
*
* @return
*    The dataflow cde control 2 register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_dataflow_cde_cntl_2_reg(void)
{
    uint32_t dataflow_cde_cntl_2_val = 0x0;

    dataflow_cde_cntl_2_val  = CDE_BCQ_THRESHOLD << DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD___S;
    dataflow_cde_cntl_2_val |= CDE_BCQ_THRESHOLD_RD << DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_RD___S;
    dataflow_cde_cntl_2_val |= CDE_BCQ_THRESHOLD_WR << DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_WR___S;
    dataflow_cde_cntl_2_val |= CDE_BCQ_THRESHOLD_EN << DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_EN___S;
    dataflow_cde_cntl_2_val |= CDE_BCQ_THRESHOLD_RD_EN << DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_RD_EN___S;
    dataflow_cde_cntl_2_val |= CDE_BCQ_THRESHOLD_WR_EN << DATAFLOW_CDE_CNTL_2_BCQ_THRESHOLD_WR_EN___S;
    dataflow_cde_cntl_2_val |= CDE_RD_CYCLE_EN << DATAFLOW_CDE_CNTL_2_RD_CYCLE_EN___S;
    dataflow_cde_cntl_2_val |= CDE_WR_CYCLE_EN << DATAFLOW_CDE_CNTL_2_WR_CYCLE_EN___S;
    dataflow_cde_cntl_2_val |= CDE_OH_CYCLE_EN << DATAFLOW_CDE_CNTL_2_OH_CYCLE_EN___S;

    return dataflow_cde_cntl_2_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the dataflow cde control 3 register value using the
*    provided configuration.
*
* @return
*    The dataflow cde control 3 register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_dataflow_cde_cntl_3_reg(void)
{
    uint32_t dataflow_cde_cntl_3_val = 0x0;
    uint16_t cde_busy_hi_threshold = CDE_BUSY_HI_THRESHOLD;
    uint16_t cde_busy_lo_threshold = CDE_BUSY_LO_THRESHOLD;

    cde_busy_hi_threshold &= DATAFLOW_CDE_CNTL_3_BUSY_HI_THRESHOLD___M;
    cde_busy_lo_threshold &= DATAFLOW_CDE_CNTL_3_BUSY_LO_THRESHOLD___M;

    cde_busy_window_size &= DATAFLOW_CDE_CNTL_4_BUSY_WINDOW_SIZE___M;
    cde_busy_hist_threshold &= DATAFLOW_CDE_CNTL_4_BUSY_HIST_THRESHOLD___M;
    cde_busy_hist_size &= DATAFLOW_CDE_CNTL_4_BUSY_HIST_SIZE___M;
    cde_not_busy_en &= DATAFLOW_CDE_CNTL___M;
    cde_not_busy_sel &= DATAFLOW_CDE_CNTL___M;

    // check busy values if enabled
    if(cde_not_busy_en == 0x1)
    {
        // check busy window size
        if(cde_busy_window_size == 0x0)
        {
            cde_busy_window_size = 0x30;

            monaco_log(HIGH, "WARNING: Compression BUSY_WINDOW_SIZE = 0 and NOT_BUSY_EN = 1, changing BUSY_WINDOW_SIZE to %u\n",
                       cde_busy_window_size);
        }

        // check busy history size
        if(cde_busy_hist_size == 0x0)
        {
            cde_busy_hist_size = 0x4;

            monaco_log(HIGH, "WARNING: Compression BUSY_HIST_SIZE = 0 is invalid, valid values are 1 to %u, changing BUSY_HIST_SIZE to %u\n",
                       cde_busy_hist_size, cde_busy_hist_size);
        }
        else if(cde_busy_hist_size > MAX_BUSY_HIST_SIZE)
        {
            monaco_log(HIGH, "WARNING: Compression BUSY_HIST_SIZE = %u is invalid, valid values are 1 to %u, changing BUSY_HIST_SIZE to %u\n",
                       cde_busy_hist_size, MAX_BUSY_HIST_SIZE, MAX_BUSY_HIST_SIZE);

            cde_busy_hist_size = MAX_BUSY_HIST_SIZE;
        }

        // check busy history threshold
        if(cde_busy_hist_threshold > cde_busy_hist_size)
        {
            monaco_log(HIGH, "WARNING: Compression BUSY_HIST_THRESHOLD = %u > BUSY_HIST_SIZE = %u, changing BUSY_HIST_THRESHOLD to %u\n",
                       cde_busy_hist_threshold, cde_busy_hist_size, cde_busy_hist_size);

            cde_busy_hist_threshold = cde_busy_hist_size;
        }

        // checks for compare thresholds; lo_threshold < hi_threshold <= window_size
        if(cde_busy_hi_threshold > cde_busy_window_size)
        {
            monaco_log(HIGH, "WARNING: Compression BUSY_HI_THRESHOLD = %u > BUSY_WINDOW_SIZE = %u, changing BUSY_HI_THRESHOLD to %u\n",
                       cde_busy_hi_threshold, cde_busy_window_size, cde_busy_window_size);

            cde_busy_hi_threshold = cde_busy_window_size;
        }
        else if(cde_busy_hi_threshold == 0x0)
        {
            monaco_log(HIGH, "WARNING: Compression BUSY_HI_THRESHOLD = 0, changing BUSY_HI_THRESHOLD to %u (BUSY_WINDOW_SIZE)\n",
                       cde_busy_window_size);

            cde_busy_hi_threshold = cde_busy_window_size;
        }

        if(cde_busy_lo_threshold >= cde_busy_hi_threshold)
        {
            monaco_log(HIGH, "WARNING: Compression BUSY_LO_THRESHOLD = %u >= BUSY_HI_THRESHOLD = %u, changing BUSY_LO_THRESHOLD to (BUSY_HI_THRESHOLD-1))\n",
                cde_busy_lo_threshold, cde_busy_hi_threshold);

            cde_busy_lo_threshold = cde_busy_hi_threshold - 0x1;
        }
    }


    dataflow_cde_cntl_3_val  = cde_busy_hi_threshold << DATAFLOW_CDE_CNTL_3_BUSY_HI_THRESHOLD___S;
    dataflow_cde_cntl_3_val |= cde_busy_lo_threshold << DATAFLOW_CDE_CNTL_3_BUSY_LO_THRESHOLD___S;

    return dataflow_cde_cntl_3_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the dataflow cde control 4 register value using the
*    provided configuration.
*
* @return
*    The dataflow cde control 4 register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_dataflow_cde_cntl_4_reg(void)
{
    uint32_t dataflow_cde_cntl_4_val = 0x0;

    dataflow_cde_cntl_4_val  = cde_busy_window_size << DATAFLOW_CDE_CNTL_4_BUSY_WINDOW_SIZE___S;
    dataflow_cde_cntl_4_val |= cde_busy_hist_threshold << DATAFLOW_CDE_CNTL_4_BUSY_HIST_THRESHOLD___S;
    dataflow_cde_cntl_4_val |= cde_busy_hist_size << DATAFLOW_CDE_CNTL_4_BUSY_HIST_SIZE___S;
    dataflow_cde_cntl_4_val |= cde_not_busy_en << DATAFLOW_CDE_CNTL_4_NOT_BUSY_EN___S;
    dataflow_cde_cntl_4_val |= cde_not_busy_sel << DATAFLOW_CDE_CNTL_4_NOT_BUSY_SEL___S;

    return dataflow_cde_cntl_4_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the dataflow cde control 5 register value using the
*    provided configuration.
*
* @return
*    The dataflow cde control 5 register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_dataflow_cde_cntl_5_reg
(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t dataflow_cde_cntl_5_val = 0x0;

    mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold &= DATAFLOW_CDE_CNTL_5_COMPRD_HI_THRESHOLD___M;
    mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold &= DATAFLOW_CDE_CNTL_5_COMPRD_LO_THRESHOLD___M;

    mddr_settings_ptr->comp_settings.cde_rd_window_size &= DATAFLOW_CDE_CNTL_6_RD_WINDOW_SIZE___M;
    mddr_settings_ptr->comp_settings.cde_rd_hist_threshold &= DATAFLOW_CDE_CNTL_6_RD_HIST_THRESHOLD___M;
    mddr_settings_ptr->comp_settings.cde_rd_hist_size &= DATAFLOW_CDE_CNTL_6_RD_HIST_SIZE___M;

    mddr_settings_ptr->comp_settings.cde_wdb_rd_mode &= DATAFLOW_CDE_CNTL_6_WDB_RD_MODE___M;
    mddr_settings_ptr->comp_settings.cde_qsb_rd_mode &= DATAFLOW_CDE_CNTL_6_QSB_RD_MODE___M;


    // Check for valid combinations Window/History/Thresholds when Adaptive Compression is enabled and override if necessary
    if(((mddr_settings_ptr->comp_settings.cde_wdb_rd_mode & 0x0C) != 0x0) ||
       ((mddr_settings_ptr->comp_settings.cde_qsb_rd_mode & 0x0C) != 0x0))
    {
        // Check read window size
        if(mddr_settings_ptr->comp_settings.cde_rd_window_size < CDE_RD_WINDOW_SIZE_MIN)
        {
            monaco_log(CRITICAL, "WARNING: Compression RD_WINDOW_SIZE=%u is invalid, valid values are %u to %u, changing RD_WINDOW_SIZE to %u\n",
                   mddr_settings_ptr->comp_settings.cde_rd_window_size,
                   CDE_RD_WINDOW_SIZE_MIN,
                   CDE_RD_WINDOW_SIZE_MAX,
                   CDE_RD_WINDOW_SIZE_MIN);

            mddr_settings_ptr->comp_settings.cde_rd_window_size = CDE_RD_WINDOW_SIZE_MIN;
        }
#if ((CDE_RD_WINDOW_SIZE_MAX) != (UINT16_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
        else if(mddr_settings_ptr->comp_settings.cde_rd_window_size > ((CDE_RD_WINDOW_SIZE_MAX)) )
        {
            monaco_log(CRITICAL, "WARNING: Compression RD_WINDOW_SIZE=%u is invalid, valid values are %u to %u, changing RD_WINDOW_SIZE to %u\n",
                   mddr_settings_ptr->comp_settings.cde_rd_window_size,
                   CDE_RD_WINDOW_SIZE_MIN,
                   CDE_RD_WINDOW_SIZE_MAX,
                   CDE_RD_WINDOW_SIZE_MAX);

            mddr_settings_ptr->comp_settings.cde_rd_window_size = CDE_RD_WINDOW_SIZE_MAX;
        }
#endif


        // Check read history size
        if(mddr_settings_ptr->comp_settings.cde_rd_hist_size < CDE_RD_HIST_SIZE_MIN)
        {
            monaco_log(CRITICAL, "WARNING: Compression RD_HIST_SIZE = %u is invalid, valid values are %u to %u, changing RD_HIST_SIZE to %u\n",
                       mddr_settings_ptr->comp_settings.cde_rd_hist_size,
                       CDE_RD_HIST_SIZE_MIN,
                       CDE_RD_HIST_SIZE_MAX,
                       CDE_RD_HIST_SIZE_MIN);

            mddr_settings_ptr->comp_settings.cde_rd_hist_size = CDE_RD_HIST_SIZE_MIN;
        }
        else if(mddr_settings_ptr->comp_settings.cde_rd_hist_size > CDE_RD_HIST_SIZE_MAX)
        {
            monaco_log(CRITICAL, "WARNING: Compression RD_HIST_SIZE = %u is invalid, valid values are %u to %u, changing RD_HIST_SIZE to %u\n",
                       mddr_settings_ptr->comp_settings.cde_rd_hist_size,
                       CDE_RD_HIST_SIZE_MIN,
                       CDE_RD_HIST_SIZE_MAX,
                       CDE_RD_HIST_SIZE_MAX);

            mddr_settings_ptr->comp_settings.cde_rd_hist_size = CDE_RD_HIST_SIZE_MAX;
        }


        // Check read history threshold
        if(mddr_settings_ptr->comp_settings.cde_rd_hist_threshold > mddr_settings_ptr->comp_settings.cde_rd_hist_size)
        {
            monaco_log(CRITICAL, "WARNING: Compression RD_HIST_THRESHOLD = %u is invalid, valid values are %u to %u, changing RD_HIST_THRESHOLD to %u\n",
                       mddr_settings_ptr->comp_settings.cde_rd_hist_threshold,
                       CDE_RD_HIST_THRESHOLD_MIN,
                       mddr_settings_ptr->comp_settings.cde_rd_hist_size,
                       mddr_settings_ptr->comp_settings.cde_rd_hist_size);

            mddr_settings_ptr->comp_settings.cde_rd_hist_threshold = mddr_settings_ptr->comp_settings.cde_rd_hist_size;
        }
#if ((CDE_RD_HIST_THRESHOLD_MIN) != 0)    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
        else if(mddr_settings_ptr->comp_settings.cde_rd_hist_threshold < ((CDE_RD_HIST_THRESHOLD_MIN)) )
        {
            monaco_log(CRITICAL, "WARNING: Compression RD_HIST_THRESHOLD = %u is invalid, valid values are %u to %u, changing RD_HIST_THRESHOLD to %u\n",
                       mddr_settings_ptr->comp_settings.cde_rd_hist_threshold,
                       CDE_RD_HIST_THRESHOLD_MIN,
                       mddr_settings_ptr->comp_settings.cde_rd_hist_size,
                       CDE_RD_HIST_THRESHOLD_MIN);

            mddr_settings_ptr->comp_settings.cde_rd_hist_threshold = CDE_RD_HIST_THRESHOLD_MIN;
        }
#endif


        // Checks for compare thresholds; lo_threshold < hi_threshold <= rd_window_size
        if(mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold > mddr_settings_ptr->comp_settings.cde_rd_window_size)
        {
            monaco_log(CRITICAL, "WARNING: Compression COMPRD_HI_THRESHOLD = %u > RD_WINDOW_SIZE = %u is invalid, changing COMPRD_HI_THRESHOLD to %u\n",
                       mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold,
                       mddr_settings_ptr->comp_settings.cde_rd_window_size,
                       mddr_settings_ptr->comp_settings.cde_rd_window_size);

            mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold = mddr_settings_ptr->comp_settings.cde_rd_window_size;
        }
        else if(mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold < CDE_COMPRD_HI_THRESHOLD_MIN)
        {
            monaco_log(CRITICAL, "WARNING: Compression COMPRD_HI_THRESHOLD = %u < %u is invalid, changing COMPRD_HI_THRESHOLD to %u\n",
                       mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold,
                       CDE_COMPRD_HI_THRESHOLD_MIN,
                       CDE_COMPRD_HI_THRESHOLD_MIN);

            mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold = CDE_COMPRD_HI_THRESHOLD_MIN;
        }


        if(mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold >= mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold)
        {
            monaco_log(CRITICAL, "WARNING: Compression COMPRD_LO_THRESHOLD = %u >= COMPRD_HI_THRESHOLD = %u is invalid, changing COMPRD_LO_THRESHOLD to %u\n",
                       mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold,
                       mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold,
                       mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold - 1);

            mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold = mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold - 1;
        }
    }


    dataflow_cde_cntl_5_val  = mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold << DATAFLOW_CDE_CNTL_5_COMPRD_HI_THRESHOLD___S;
    dataflow_cde_cntl_5_val |= mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold << DATAFLOW_CDE_CNTL_5_COMPRD_LO_THRESHOLD___S;

    return dataflow_cde_cntl_5_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the dataflow cde control 6 register value using the
*    provided configuration.
*
* @return
*    The dataflow cde control 6 register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_dataflow_cde_cntl_6_reg
(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t dataflow_cde_cntl_6_val = 0x0;

    dataflow_cde_cntl_6_val  = mddr_settings_ptr->comp_settings.cde_rd_window_size << DATAFLOW_CDE_CNTL_6_RD_WINDOW_SIZE___S;
    dataflow_cde_cntl_6_val |= mddr_settings_ptr->comp_settings.cde_rd_hist_threshold << DATAFLOW_CDE_CNTL_6_RD_HIST_THRESHOLD___S;
    dataflow_cde_cntl_6_val |= mddr_settings_ptr->comp_settings.cde_rd_hist_size << DATAFLOW_CDE_CNTL_6_RD_HIST_SIZE___S;
    dataflow_cde_cntl_6_val |= mddr_settings_ptr->comp_settings.cde_wdb_rd_mode << DATAFLOW_CDE_CNTL_6_WDB_RD_MODE___S;
    dataflow_cde_cntl_6_val |= mddr_settings_ptr->comp_settings.cde_qsb_rd_mode << DATAFLOW_CDE_CNTL_6_QSB_RD_MODE___S;

    return dataflow_cde_cntl_6_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR ODT write control register value using the
*    provided configuration.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    The DDR ODT write control register value.
*
* @author
*    gkowis
*
* @par Notes:
*    Only CS0:3 are valid fields for this register
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_odt_wr_cntl_reg(uint8_t ddr_chan)
{
    uint32_t ddr_odt_wr_cntl_val = 0x0;
    uint8_t dimm_slot;
    uint8_t rank;
    uint8_t slot_rank_cnt;
    uint8_t max_ranks_per_dimm_2dpc = DDR_RANKS_DUAL_CS_DIMM;
    uint8_t wr_odt_setting;
    uint8_t rank_shift;

    // Emulation defaults to no ODT
    if (platform_mode == SILICON)
    {
        // All unused rank ODTs in the register are 0 by default.
        for(dimm_slot = 0; dimm_slot < num_dimms_per_chan_poped; ++dimm_slot)
        {
            slot_rank_cnt = common_cfg.slot_config[dimm_slot].num_ranks;
            if (slot_rank_cnt != SPD_INVALID_RANK_COUNT)
            {
                for (rank = 0; rank < max_ranks_per_dimm_2dpc; ++rank)
                {
                    rank_shift = (dimm_slot * max_ranks_per_dimm_2dpc + rank) * EN_ODT_WR_CS_WIDTH;

                    wr_odt_setting = si_data[ddr_chan].dimm_si[dimm_slot].rank_si[rank].odt_wr;
                    ddr_odt_wr_cntl_val  |= ((uint32_t)(wr_odt_setting & EN_ODT_WR_CS___M)) << rank_shift;
                }
            }
        }
    }

    return ddr_odt_wr_cntl_val;

}




/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR ODT read control register value using the
*    provided configuration.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    The DDR ODT read control register value.
*
* @author
*    gkowis
*
* @par Notes:
*    Only CS0:3 are valid fields for this register
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_odt_rd_cntl_reg(uint8_t ddr_chan)
{
    uint32_t ddr_odt_rd_cntl_val = 0x0;
    uint8_t dimm_slot;
    uint8_t rank;
    uint8_t slot_rank_cnt;
    uint8_t max_ranks_per_dimm_2dpc = DDR_RANKS_DUAL_CS_DIMM;
    uint8_t rd_odt_setting;
    uint8_t rank_shift;

    // Emulation defaults to no ODT
    if (platform_mode == SILICON)
    {
        // All unused rank ODTs in the register are 0 by default.
        for(dimm_slot = 0; dimm_slot < num_dimms_per_chan_poped; ++dimm_slot)
        {
            slot_rank_cnt = common_cfg.slot_config[dimm_slot].num_ranks;
            if (slot_rank_cnt != SPD_INVALID_RANK_COUNT)
            {
                for (rank = 0; rank < max_ranks_per_dimm_2dpc; ++rank)
                {
                    rank_shift = (dimm_slot * max_ranks_per_dimm_2dpc + rank) * EN_ODT_RD_CS_WIDTH;

                    rd_odt_setting = si_data[ddr_chan].dimm_si[dimm_slot].rank_si[rank].odt_rd;
                    ddr_odt_rd_cntl_val  |= ((uint32_t)(rd_odt_setting & EN_ODT_RD_CS___M)) << rank_shift;
                }
            }
        }
    }

    return ddr_odt_rd_cntl_val;

}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the command execution control 0 register value
*    using the provided configuration and settings.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
*
* @return
*    The command execution control 0 register value.
*
* @author
*    gkowis
*
* @par Notes:
*    The configuration reflects what DIMMs are present in the system and the
*    settings reflect the desired configurable options.
*
******************************************************************************/
uint32_t mddr_mc_build_cmd_exec_cntl_0_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t cmd_exec_cntl_0_val;
    bool dbi_wr = false;

    if ((common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4) &&
        (common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X8) &&
        ((mddr_settings_ptr->dbi_mode == DDR_DBI_WRITE) ||
         (mddr_settings_ptr->dbi_mode == DDR_DBI_READ_WRITE)))
    {
        dbi_wr = true;
    }
    else
    {
        // Override write DBI if it is set since it is not valid unless DDR4 and x8
        if(mddr_settings_ptr->dbi_mode == DDR_DBI_WRITE)
        {
            mddr_settings_ptr->dbi_mode = DDR_DBI_OFF;
        }
        else
        {
            if(mddr_settings_ptr->dbi_mode == DDR_DBI_READ_WRITE)
            {
                mddr_settings_ptr->dbi_mode = DDR_DBI_READ;
            }
        }
    }

    // priority  x4 (set RMW), ECC >> DBI >> DM
    cmd_exec_cntl_0_val  = EN_NO_RETRY << CMD_EXEC_CNTL0_EN_NO_RETRY___S;
    cmd_exec_cntl_0_val |= DIS_WDB_READ << CMD_EXEC_CNTL0_DIS_WDB_SOURCE_RD___S;
    cmd_exec_cntl_0_val |= RETRY_WRWR_HAZ << CMD_EXEC_CNTL0_RETRY_WRWR_HAZ___S;
    cmd_exec_cntl_0_val |= RETRY_ORWRORWR_HAZ << CMD_EXEC_CNTL0_RETRY_ORWRORWR_HAZ___S;
    cmd_exec_cntl_0_val |= NO_RETRY_MODE_IGN_POR_TMREL << CMD_EXEC_CNTL0_NO_RETRY_MODE_IGN_PORTMREL___S;
    cmd_exec_cntl_0_val |= EN_CLK_ON << CMD_EXEC_CNTL0_EN_CLK_ON___S;


    // if x4 or (DBI WR and DDR4) or (ECC is there and not disabled)
    if ((common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X4) ||
        (dbi_wr) || ((common_cfg_ptr->has_ecc) && ((mddr_settings_ptr->disable_ecc == false) ||
        (mddr_settings_ptr->comp_settings.comp_mode) || ((mddr_settings_ptr->ecc_wrrd_mode & 0x0C) > 0x0))))
    {
        cmd_exec_cntl_0_val |= 0x1 << CMD_EXEC_CNTL0_EN_RMW___S;
    }

    return cmd_exec_cntl_0_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the command execution control 1 register value.
*
* @return
*    The command execution control 1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_cmd_exec_cntl_1_reg(void)
{
    uint32_t cmd_exec_cntl_1_val;

    cmd_exec_cntl_1_val  = (BCQ_TH & CMD_EXEC_CNTL1_BCQ_TH___M) << CMD_EXEC_CNTL1_BCQ_TH___S;
    cmd_exec_cntl_1_val |= (BCQ_TH_WR & CMD_EXEC_CNTL1_BCQ_TH_WR___M) << CMD_EXEC_CNTL1_BCQ_TH_WR___S;
    cmd_exec_cntl_1_val |= (RCQ_TH & CMD_EXEC_CNTL1_RCQ_TH___M) << CMD_EXEC_CNTL1_RCQ_TH___S;
    cmd_exec_cntl_1_val |= (CBQ_TH & CMD_EXEC_CNTL1_CBQ_TH___M) << CMD_EXEC_CNTL1_CBQ_TH___S;

    return cmd_exec_cntl_1_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the command execution control 2 register value.
*
* @return
*    The command execution control 2 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_cmd_exec_cntl_2_reg(void)
{
    uint32_t cmd_exec_cntl_2_val;

    cmd_exec_cntl_2_val  = (DIS_RCQ & CMD_EXEC_CNTL2_DIS_RCQ___M) << CMD_EXEC_CNTL2_DIS_RCQ___S;
    cmd_exec_cntl_2_val |= (DIS_WDB & CMD_EXEC_CNTL2_DIS_WDB___M) << CMD_EXEC_CNTL2_DIS_WDB___S;
    cmd_exec_cntl_2_val |= (DIS_RD_RESP_FIFO & CMD_EXEC_CNTL2_DIS_RD_RESP_FIFO___M) << CMD_EXEC_CNTL2_DIS_RD_RESP_FIFO___S;
    cmd_exec_cntl_2_val |= (DIS_RD_DATA_FIFO & CMD_EXEC_CNTL2_DIS_RD_DATA_FIFO___M) << CMD_EXEC_CNTL2_DIS_RD_DATA_FIFO___S;


    return cmd_exec_cntl_2_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the command execution control 3 register value
*    using the provided settings.
*
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
*
* @return
*    The command execution control 3 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_cmd_exec_cntl_3_reg
(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t cmd_exec_cntl_3_val;
    uint32_t en_auto_pchg = DISABLE_AUTO_PCHG;
    uint32_t dq_burst_len = BURST_LEN_BL8;
    uint32_t page_policy;


    if (mddr_settings_ptr->page_settings.enable_auto_pchg)
    {
        en_auto_pchg = ENABLE_AUTO_PCHG;
    }


    if (mddr_settings_ptr->page_settings.burst_len_mode != DB_BURST_LEN_BL8)
    {
        // OTF - Use BL8 or Burst Chop 4 (BC4). BC4 alone is not supported.
        dq_burst_len = BURST_LEN_OTF;
    }

    if (mddr_settings_ptr->page_settings.page_policy == DDR_PAGE_POLICY_TIMER)
    {
        page_policy = PAGE_POLICY_TIMER;
    }
    else if(mddr_settings_ptr->page_settings.page_policy == DDR_PAGE_POLICY_OPEN)
    {
        page_policy = PAGE_POLICY_OPEN;
    }
    else
    {
        // DDR_PAGE_POLICY_CLOSED
        page_policy = PAGE_POLICY_CLOSED;
    }


    cmd_exec_cntl_3_val  = (en_auto_pchg & CMD_EXEC_CNTL3_EN_AUTO_PCHG___M) << CMD_EXEC_CNTL3_EN_AUTO_PCHG___S;
    cmd_exec_cntl_3_val |= (dq_burst_len & CMD_EXEC_CNTL3_DQ_BURST_LEN___M) << CMD_EXEC_CNTL3_DQ_BURST_LEN___S;
    cmd_exec_cntl_3_val |= (DIS_OPT_ENTRY & CMD_EXEC_CNTL3_DIS_OPT_ENTRY___M) << CMD_EXEC_CNTL3_DIS_OPT_ENTRY___S;
    cmd_exec_cntl_3_val |= (page_policy & CMD_EXEC_CNTL3_PAGE_POLICY___M) << CMD_EXEC_CNTL3_PAGE_POLICY___S;
    cmd_exec_cntl_3_val |= (mddr_settings_ptr->page_settings.page_idle_timer & CMD_EXEC_CNTL3_PAGE_IDLE_TIMER___M) << CMD_EXEC_CNTL3_PAGE_IDLE_TIMER___S;

    return cmd_exec_cntl_3_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the command execution control 4 register value.
*
* @return
*    The command execution control 4 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_cmd_exec_cntl_4_reg(void)
{
    uint8_t dimm_slot;
    uint32_t cmd_exec_cntl_4_val = 0x0;
    uint32_t serialize_mnt_cmd = 0x0;
    uint32_t disable_cmd_interleave = 0x0;
    bool ca_mirrored = 0x0;

    for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        ca_mirrored += common_cfg.slot_config[dimm_slot].ca_mirrored;
    }

    if ((common_cfg.mod_type != SPD_MODULE_TYPE_UDIMM) || ca_mirrored || (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR3))
    {
        serialize_mnt_cmd = 1;
    }


    cmd_exec_cntl_4_val  = disable_cmd_interleave << CMD_EXEC_CNTL4_DISABLE_CMD_INTERLEAVE___S;
    cmd_exec_cntl_4_val |= serialize_mnt_cmd << CMD_EXEC_CNTL4_SERIAL_MNT_CMD___S;

    return cmd_exec_cntl_4_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the command execution control 5 register value.
*
* @return
*    The command execution control 5 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_cmd_exec_cntl_5_reg(void)
{
    uint32_t cmd_exec_cntl_5_val;


    cmd_exec_cntl_5_val = PRIO_ELEVATION_TH & CMD_EXEC_CNTL5_PRIO_ELEVATION_TH___M;

    return cmd_exec_cntl_5_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the command execution control 6 register value.
*
* @return
*    The command execution control 6 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_cmd_exec_cntl_6_reg(void)
{
    uint32_t cmd_exec_cntl_6_val;


    if (platform_mode != SILICON)
    {
        // Turn off Read/Write preference for Emulation
        cmd_exec_cntl_6_val = 0x0;
    }
    else
    {
        cmd_exec_cntl_6_val  = WR_PREFER_EN << CMD_EXEC_CNTL6_WR_PREFER_EN___S;
        cmd_exec_cntl_6_val |= BCQ_ALL_HI << CMD_EXEC_CNTL6_BCQ_ALL___S;
        cmd_exec_cntl_6_val |= BCQ_WM_EN_HI << CMD_EXEC_CNTL6_BCQ_WM_EN___S;
        cmd_exec_cntl_6_val |= BCQ_DBE_BOTH_HI << CMD_EXEC_CNTL6_BCQ_DBE_BOTH___S;
        cmd_exec_cntl_6_val |= DBE_WM_EN_HI << CMD_EXEC_CNTL6_DBE_WM_EN___S;
        cmd_exec_cntl_6_val |= (BCQ_WM_HI & CMD_EXEC_CNTL6_BCQ_WM_HI___M) << CMD_EXEC_CNTL6_BCQ_WM_HI___S;
        cmd_exec_cntl_6_val |= (DBE_WM_HI & CMD_EXEC_CNTL6_DBE_WM_HI___M) << CMD_EXEC_CNTL6_DBE_WM_HI___S;
    }

    return cmd_exec_cntl_6_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the command execution control 7 register value.
*
* @return
*    The command execution control 7 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_cmd_exec_cntl_7_reg(void)
{
    uint32_t cmd_exec_cntl_7_val;


    if (platform_mode != SILICON)
    {
        // Turn off Read/Write preference for Emulation
        cmd_exec_cntl_7_val = 0x0;
    }
    else
    {
        cmd_exec_cntl_7_val  = BCQ_ALL_LO << CMD_EXEC_CNTL7_BCQ_ALL___S;
        cmd_exec_cntl_7_val |= BCQ_WM_EN_LO << CMD_EXEC_CNTL7_BCQ_WM_EN___S;
        cmd_exec_cntl_7_val |= BCQ_DBE_BOTH_LO << CMD_EXEC_CNTL7_BCQ_DBE_BOTH___S;
        cmd_exec_cntl_7_val |= DBE_WM_EN_LO << CMD_EXEC_CNTL7_DBE_WM_EN___S;
        cmd_exec_cntl_7_val |= (BCQ_WM_LO & CMD_EXEC_CNTL7_BCQ_WM_LO___M) << CMD_EXEC_CNTL7_BCQ_WM_LO___S;
        cmd_exec_cntl_7_val |= (DBE_WM_LO & CMD_EXEC_CNTL7_DBE_WM_LO___M) << CMD_EXEC_CNTL7_DBE_WM_LO___S;
    }

    return cmd_exec_cntl_7_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the address decode control register value
*    using the provided settings.
*
*                                  @param
*    soc_hw_version          Provides the HW version of the target SoC.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
*
* @return
*    The address decode control register value.
*
* @author
*    gkowis, lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_addr_decode_cntl_reg
(
    soc_hw_version_t soc_hw_version,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t addr_decode_cntl_val= 0x00000000;

    uint8_t mddr_addr_interleave_mode;
    uint8_t mddr_bg_decode = ADDR_DECODE_CNTL_BG_DECODE_MCA_16_15;    // default for DDR3
    uint8_t mddr_addr_interleave_bndry = ADDR_DECODE_CNTL_ADDR_INTLV_BNDRY_256B;

    if (!(mddr_settings_ptr->dimm_intlv_en))
    {
        monaco_log(INFORMATIONAL,"DIMMs are not being interleaved.\n");
    }
    else
    {
        monaco_log(INFORMATIONAL,"DIMMs are being interleaved.\n");
        addr_decode_cntl_val = addr_decode_cntl_val | (0x1 << ADDR_DECODE_CNTL_EN_INT_DIMM___S);
    }

    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        if (mddr_settings_ptr->bank_group_decode == ADDR_DECODE_BG_MCA_16_15)
        {
            mddr_bg_decode = ADDR_DECODE_CNTL_BG_DECODE_MCA_16_15;
        }
        else if(mddr_settings_ptr->bank_group_decode == ADDR_DECODE_BG_MCA_8_7)
        {
            mddr_bg_decode = ADDR_DECODE_CNTL_BG_DECODE_MCA_8_7;
        }
        else if(mddr_settings_ptr->bank_group_decode == ADDR_DECODE_BG_MCA_16_7)
        {
            mddr_bg_decode = ADDR_DECODE_CNTL_BG_DECODE_MCA_16_7;
        }
        else if(mddr_settings_ptr->bank_group_decode == ADDR_DECODE_BG_R_C_RK_B_BG)
        {
            mddr_bg_decode = ADDR_DECODE_CNTL_BG_DECODE_R_C_RK_B_BG;
        }

        if ((soc_hw_version.major_version < SOC_HW_MAJOR_VERSION_2) &&
            (mddr_settings_ptr->bank_group_decode == ADDR_DECODE_BG_R_C_RK_B_BG))
        {
            monaco_log(CRITICAL,"Warning: Requested bank group decode value is %d which is supported only on HV2.0, setting it to %d\n\n",
                                mddr_settings_ptr->bank_group_decode, (uint8_t)ADDR_DECODE_CNTL_BG_DECODE_MCA_16_7);
            mddr_bg_decode = ADDR_DECODE_CNTL_BG_DECODE_MCA_16_7;
        }
    }


    // Other population counts already rejected.
    if(num_chans_poped == 6)
    {
        mddr_addr_interleave_mode = ADDR_DECODE_CNTL_ADDR_INTLV_MODE_DIV_3;
    }
    else if(num_chans_poped == 4)
    {
        mddr_addr_interleave_mode = ADDR_DECODE_CNTL_ADDR_INTLV_MODE_DIV_2;
    }
    else
    {
        // mddr_settings_ptr->num_chans_poped == 2
        mddr_addr_interleave_mode = ADDR_DECODE_CNTL_ADDR_INTLV_MODE_DIV_1;
    }


    // There is no restriction on the interleave boundary based on no. of channels
    if(mddr_settings_ptr->ddr_granule == DDR_DIST_GRANULE_4KB)
    {
        mddr_addr_interleave_bndry = ADDR_DECODE_CNTL_ADDR_INTLV_BNDRY_4KB;
    }
    else if(mddr_settings_ptr->ddr_granule == DDR_DIST_GRANULE_8KB)
    {
        mddr_addr_interleave_bndry = ADDR_DECODE_CNTL_ADDR_INTLV_BNDRY_8KB;
    }


    // OR'in the address interleave mode
    addr_decode_cntl_val = addr_decode_cntl_val | (mddr_addr_interleave_mode << ADDR_DECODE_CNTL_ADDR_INT_MODE___S);

    // OR'in the address interleave boundary
    addr_decode_cntl_val = addr_decode_cntl_val | (mddr_addr_interleave_bndry << ADDR_DECODE_CNTL_ADDR_INT_BNDRY___S);

    // OR'in the DDR4 Bank Group decoding
    addr_decode_cntl_val = addr_decode_cntl_val | (mddr_bg_decode & ADDR_DECODE_CNTL_BG_DECODE___M);


    return addr_decode_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the write data buffer flush control register
*    value.
*
* @return
*    The WDB flush control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_wdb_flush_cntl_reg()
{
    uint32_t wdb_flush_cntl_val;

    wdb_flush_cntl_val  = (WDB_FLUSH_CNTL_IDLE_DELAY & WDB_FLUSH_CNTL_IDLE_DELAY___M) << WDB_FLUSH_CNTL_IDLE_DELAY___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_WR_DELAY & WDB_FLUSH_CNTL_WR_DELAY___M) << WDB_FLUSH_CNTL_WR_DELAY___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_BCQ_DIST & WDB_FLUSH_CNTL_BCQ_DIST___M) << WDB_FLUSH_CNTL_BCQ_DIST___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_FL_WM_INC_WR & WDB_FLUSH_CNTL_FL_WM_INC_WR___M) << WDB_FLUSH_CNTL_FL_WM_INC_WR___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_FL_WM_EN & WDB_FLUSH_CNTL_FL_WM_EN___M) << WDB_FLUSH_CNTL_FL_WM_EN___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_WR_WM_EN & WDB_FLUSH_CNTL_WR_WM_EN___M) << WDB_FLUSH_CNTL_WR_WM_EN___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_PH_OPT_EN & WDB_FLUSH_CNTL_PH_OPT_EN___M) << WDB_FLUSH_CNTL_PH_OPT_EN___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_ML_SEL & WDB_FLUSH_CNTL_ML_SEL___M) << WDB_FLUSH_CNTL_ML_SEL___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_RD_FULL & WDB_FLUSH_CNTL_RD_FULL___M) << WDB_FLUSH_CNTL_RD_FULL___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_INVALIDATE & WDB_FLUSH_CNTL_INVALIDATE___M) << WDB_FLUSH_CNTL_INVALIDATE___S;
    wdb_flush_cntl_val |= (WDB_FLUSH_CNTL_DISABLE & WDB_FLUSH_CNTL_DISABLE___M) << WDB_FLUSH_CNTL_DISABLE___S;


    return wdb_flush_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the write data buffer flush watermark register
*    value.
*
* @return
*    The WDB flush watermark register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_wdb_flush_wm_reg()
{
    uint32_t wdb_flush_wm_val;


    wdb_flush_wm_val  = (WDB_FLUSH_WM_FL_WM_HI & WDB_FLUSH_WM_FL_WM_HI___M) << WDB_FLUSH_WM_FL_WM_HI___S;
    wdb_flush_wm_val |= (WDB_FLUSH_WM_FL_WM_LO & WDB_FLUSH_WM_FL_WM_LO___M) << WDB_FLUSH_WM_FL_WM_LO___S;
    wdb_flush_wm_val |= (WDB_FLUSH_WM_WR_WM_HI & WDB_FLUSH_WM_WR_WM_HI___M) << WDB_FLUSH_WM_WR_WM_HI___S;
    wdb_flush_wm_val |= (WDB_FLUSH_WM_WR_WM_LO & WDB_FLUSH_WM_WR_WM_LO___M) << WDB_FLUSH_WM_WR_WM_LO___S;

    return wdb_flush_wm_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the write data buffer flush ph register
*    value.
*
* @return
*    The WDB flush ph register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_wdb_flush_ph_reg()
{
    uint32_t wdb_flush_ph_val;


    wdb_flush_ph_val  = (WDB_FLUSH_PH_HIT_VAL & WDB_FLUSH_PH_HIT_VAL___M) << WDB_FLUSH_PH_HIT_VAL___S;
    wdb_flush_ph_val |= (WDB_FLUSH_PH_HIT_INC & WDB_FLUSH_PH_HIT_INC___M) << WDB_FLUSH_PH_HIT_INC___S;
    wdb_flush_ph_val |= (WDB_FLUSH_PH_CONFLICT_DEC & WDB_FLUSH_PH_CONFLICT_DEC___M) << WDB_FLUSH_PH_CONFLICT_DEC___S;

    return wdb_flush_ph_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the interrupt 0 control register.
*
* @return
*    The interrupt 0 control register value.
*
* @author
*    gkowis/lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_int0_cntl_reg
(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t int0_cntl_val = 0x0;

    // Enabled all the interrupt bits for INT0 control register
    int0_cntl_val = INT_CNTL___M << INT_CNTL_ECC_UE_QSB_RD___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_POISON_QSB_RD___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_UE_RMW___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_POISON_RMW___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_UE_SCRUB___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_POISON_SCRUB___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_QSB_ADDR_DECODE_ERR0___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_QSB_ADDR_DECODE_ERR1___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ERR_OUT_ALERT___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_EVENT___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_INVALID_CMD___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_CE_CNTR_THRESHOLD___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_UE_CNTR_THRESHOLD___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_WDB_UE_READ___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_DCF_NEMPTY_END_INTERVAL___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_CE_CNTR_TOTAL_THRESHOLD___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_UE_CNTR_TOTAL_THRESHOLD___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_ERR_DFI_RDDATA_VALID___S;
    int0_cntl_val |= INT_CNTL___M << INT_CNTL_PHY_UPD_REQ___S;

    // When ECC CE threshold is configured, not enable individual CE interrupts
    if(mddr_settings_ptr->ecc_ce_threshold==0)
    {
        int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_CE_QSB_RD___S;
        int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_CE_RMW___S;
        int0_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_CE_SCRUB___S;
    }
    return int0_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the interrupt 1 control register.
*
* @return
*    The interrupt 1 control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_int1_cntl_reg(void)
{
    uint32_t int1_cntl_val = 0x0;

    // fatal
    //------------------------------------
    // 19 ECC_UE_CNTR_TOTAL_THRESHOLD
    // 15 ECC_UE_CNTR_THRESHOLD
    // 13 INVALID_CMD
    // 11 ERR_OUT_ALERT
    // 10 QSB_ADDR_DECODE_ERR1
    //  9 QSB_ADDR_DECODE_ERR0
    //  5 ECC_POISON_RMW         // due to read WDB enabled
    //  4 ECC_UE_RMW             // due to read WDB enabled
    //  2 ECC_POISON_QSB_RD
    //  1 ECC_UE_QSB_RD

    // INT1 for Uncorrectable Errors(UE) or fatal errors
    int1_cntl_val  = INT_CNTL___M << INT_CNTL_ECC_UE_QSB_RD___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_POISON_QSB_RD___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_UE_RMW___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_POISON_RMW___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_QSB_ADDR_DECODE_ERR0___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_QSB_ADDR_DECODE_ERR1___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_ERR_OUT_ALERT___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_INVALID_CMD___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_UE_CNTR_THRESHOLD___S;
    int1_cntl_val |= INT_CNTL___M << INT_CNTL_ECC_UE_CNTR_TOTAL_THRESHOLD___S;

    return int1_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the error mask control register.
*
* @return
*    The error mask control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_err_cntl_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t err_cntl_val = 0x0;
    uint32_t dfi_rddata_valid = 0x0;
    uint32_t ecc_ue_cntr_total_th = 0x0;
    uint32_t ecc_ce_cntr_total_th = 0x0;
    uint32_t dcf_nempty_end_int = 0x0;
    uint32_t wdb_ue_read = 0x0;
    uint32_t ecc_ue_cntr_th = 0x0;
    uint32_t ecc_ce_cntr_th = 0x0;
    uint32_t invalid_cmd = 0x0;
    uint32_t event = 0x0;
    uint32_t err_out_alert = 0x0;
    uint32_t qsb_addr_decode_err1 = 0x0;
    uint32_t qsb_addr_decode_err0 = 0x0;
    uint32_t ecc_poison_scrub = 0x0;
    uint32_t ecc_ue_scrub = 0x0;
    uint32_t ecc_ce_scrub = 0x0;
    uint32_t ecc_poison_rmw = 0x0;
    uint32_t ecc_ue_rmw = 0x0;
    uint32_t ecc_ce_rmw = 0x0;
    uint32_t ecc_poison_qsb_rd = 0x0;
    uint32_t ecc_ue_qsb_rd = 0x0;
    uint32_t ecc_ce_qsb_rd = 0x0;
    uint32_t phy_upd_req = 0x0;


    if ((platform_mode != SILICON) && (common_cfg_ptr->mod_type == SPD_MODULE_TYPE_UDIMM))
    {
        err_out_alert = 0x1;
    }

    if(mddr_settings_ptr->ecc_ce_threshold!=0)
    {
        ecc_ce_scrub = 0x1;
        ecc_ce_rmw = 0x1;
        ecc_ce_qsb_rd = 0x1;
    }

    err_cntl_val |= (ecc_ce_qsb_rd & ERR_CNTL___M) << ERR_CNTL_ECC_CE_QSB_RD___S;
    err_cntl_val |= (ecc_ue_qsb_rd & ERR_CNTL___M) << ERR_CNTL_ECC_UE_QSB_RD___S;
    err_cntl_val |= (ecc_poison_qsb_rd & ERR_CNTL___M) << ERR_CNTL_ECC_POISON_QSB_RD___S;
    err_cntl_val |= (ecc_ce_rmw & ERR_CNTL___M) << ERR_CNTL_ECC_CE_RMW___S;
    err_cntl_val |= (ecc_ue_rmw & ERR_CNTL___M) << ERR_CNTL_ECC_UE_RMW___S;
    err_cntl_val |= (ecc_poison_rmw & ERR_CNTL___M) << ERR_CNTL_ECC_POISON_RMW___S;
    err_cntl_val |= (ecc_ce_scrub & ERR_CNTL___M) << ERR_CNTL_ECC_CE_SCRUB___S;
    err_cntl_val |= (ecc_ue_scrub & ERR_CNTL___M) << ERR_CNTL_ECC_UE_SCRUB___S;
    err_cntl_val |= (ecc_poison_scrub & ERR_CNTL___M) << ERR_CNTL_ECC_POISON_SCRUB___S;
    err_cntl_val |= (qsb_addr_decode_err0 & ERR_CNTL___M) << ERR_CNTL_QSB_ADDR_DECODE_ERR0___S;
    err_cntl_val |= (qsb_addr_decode_err1 & ERR_CNTL___M) << ERR_CNTL_QSB_ADDR_DECODE_ERR1___S;
    err_cntl_val |= (err_out_alert & ERR_CNTL___M) << ERR_CNTL_ERR_OUT_ALERT___S;
    err_cntl_val |= (event & ERR_CNTL___M) << ERR_CNTL_EVENT___S;
    err_cntl_val |= (invalid_cmd & ERR_CNTL___M) << ERR_CNTL_INVALID_CMD___S;
    err_cntl_val |= (ecc_ce_cntr_th & ERR_CNTL___M) << ERR_CNTL_ECC_CE_CNTR_THRESHOLD___S;
    err_cntl_val |= (ecc_ue_cntr_th & ERR_CNTL___M) << ERR_CNTL_ECC_UE_CNTR_THRESHOLD___S;
    err_cntl_val |= (wdb_ue_read & ERR_CNTL___M) << ERR_CNTL_WDB_UE_READ___S;
    err_cntl_val |= (dcf_nempty_end_int & ERR_CNTL___M) << ERR_CNTL_DCF_NEMPTY_END_INTERVAL___S;
    err_cntl_val |= (ecc_ce_cntr_total_th & ERR_CNTL___M) << ERR_CNTL_ECC_CE_CNTR_TOTAL_THRESHOLD___S;
    err_cntl_val |= (ecc_ue_cntr_total_th & ERR_CNTL___M) << ERR_CNTL_ECC_UE_CNTR_TOTAL_THRESHOLD___S;
    err_cntl_val |= (dfi_rddata_valid & ERR_CNTL___M) << ERR_CNTL_ERR_DFI_RDDATA_VALID___S;
    err_cntl_val |= (phy_upd_req & ERR_CNTL___M) << ERR_CNTL_PHY_UPD_REQ___S;

    return err_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the error capture control register.
*
* @return
*    The error capture control register value.
*
* @author
*    anthonyf
*
******************************************************************************/
uint32_t mddr_mc_build_err_cap_cntl_reg(void)
{
    uint32_t err_cap_cntl_val;
    uint32_t capture_last_err = 0x0;
    uint32_t capture_last_err_frz = 0x0;


    err_cap_cntl_val = (capture_last_err & ERR_CAP_CNTL_CAPTURE_LAST_ERR___M) << ERR_CAP_CNTL_CAPTURE_LAST_ERR___S;
    err_cap_cntl_val |= (capture_last_err_frz & ERR_CAP_CNTL_CAPTURE_LAST_ERR_FRZ___M) << ERR_CAP_CNTL_CAPTURE_LAST_ERR_FRZ___S;


    return err_cap_cntl_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the ecc error control register.
*
* @return
*    The ecc error control register value.
*
* @author
*    jihyunl
*
******************************************************************************/
uint32_t mddr_mc_build_ecc_err_cntl_1_reg(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t ecc_err_cntl_val;
    uint32_t ce_total_cnt = 0x0;
    uint32_t ue_total_cnt = 0x0;

    ce_total_cnt = mddr_settings_ptr->ecc_ce_threshold;

    ecc_err_cntl_val = (ce_total_cnt & ECC_ERR_CNTL_1_CE_CNTR_TOTAL_THRESHOLD___M) << ECC_ERR_CNTL_1_CE_CNTR_TOTAL_THRESHOLD___S;
    ecc_err_cntl_val |= (ue_total_cnt & ECC_ERR_CNTL_1_UE_CNTR_TOTAL_THRESHOLD___M) << ECC_ERR_CNTL_1_UE_CNTR_TOTAL_THRESHOLD___S;


    return ecc_err_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the read / write preference control register in
*    a DDR memory controller.
*
* @return
*    The read / write preference control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_rd_wr_pref_cntl_reg(void)
{
    uint32_t rd_wr_pref_cntl_val;
    uint32_t preftimer = RD_WR_PREF_PREFTIMER;
    uint32_t priothreshold = RD_WR_PREF_PRIOTHRESHOLD;
    uint32_t pref_level = RD_WR_PREF_PREF_LEVEL;


    if (platform_mode != SILICON)
    {
        // Turn off Read/Write preference for Emulation
        rd_wr_pref_cntl_val = 0x0;
    }
    else
    {
        rd_wr_pref_cntl_val  = (pref_level & RD_WR_PREF_CNTL_PREF_LEVEL___M) << RD_WR_PREF_CNTL_PREF_LEVEL___S;
        rd_wr_pref_cntl_val |= (priothreshold & RD_WR_PREF_CNTL_PRIOTHRESHOLD___M) << RD_WR_PREF_CNTL_PRIOTHRESHOLD___S;
        rd_wr_pref_cntl_val |= (preftimer & RD_WR_PREF_CNTL_PREFTIMER___M) << RD_WR_PREF_CNTL_PREFTIMER___S;
    }


    return rd_wr_pref_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the TN token count register in a DDR
*    memory controller.
*
* @return
*    The TN token count register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_tn_token_cnt_reg(void)
{
    uint32_t tn_token_cnt_val;
    uint32_t rdat_ch = 0x6;
    uint32_t rslt_ch = 0x6;


    tn_token_cnt_val  = (rdat_ch & TN_TOKEN_CNT_RDAT_CH___M) << TN_TOKEN_CNT_RDAT_CH___S;
    tn_token_cnt_val |= (rslt_ch & TN_TOKEN_CNT_RSLT_CH___M) << TN_TOKEN_CNT_RSLT_CH___S;


    return tn_token_cnt_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR DFI control register in
*    a DDR memory controller.
*
* @return
*    The DDR DFI control register value.
*
* @author
*    gkowis/anthonyf
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_dfi_cntl_reg
(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint8_t ddr_dfi_cntl_val;
    uint8_t en_dfi_phyupd_ack = 0x0;
    uint8_t en_dfi_ctrlupd_req = 0x0;
    uint8_t en_dfi_lp_req_in_pd;
    uint8_t en_dfi_lp_req_in_sr;
    uint8_t dfi_ctrlupd_mode = 0x0;
    uint8_t en_dfi_fc_req_in_sr;
    uint8_t dfi_freq_ratio = 0x0;
    uint8_t dfi_ctrlupd_period = DFI_CTRLUPD_PERIOD;
    uint8_t dfi_lp_wakeup_from_pd = 0x0;
    uint8_t dfi_lp_wakeup_from_sr = 0x0;
    uint8_t dfi_phyupd_mode_type0 = 0x0;
    uint8_t dfi_phyupd_mode_type1 = 0x0;
    uint8_t dfi_phyupd_mode_type2 = 0x0;
    uint8_t dfi_phyupd_mode_type3 = 0x0;

    // TODO: Consider moving emulation override here

    if(mddr_settings_ptr->dfi_lp_mode == DFI_LP_SR_PD_ENA_LP2_ENA)
    {
        en_dfi_lp_req_in_sr = 0x1;
        en_dfi_lp_req_in_pd = 0x1;
        en_dfi_fc_req_in_sr = 0x1;
    }
    else if(mddr_settings_ptr->dfi_lp_mode == DFI_LP_SR_ENA_LP2_ENA)
    {
        en_dfi_lp_req_in_sr = 0x1;
        en_dfi_lp_req_in_pd = 0x0;
        en_dfi_fc_req_in_sr = 0x1;
    }
    else if(mddr_settings_ptr->dfi_lp_mode == DFI_LP_SR_PD_ENA)
    {
        en_dfi_lp_req_in_sr = 0x1;
        en_dfi_lp_req_in_pd = 0x1;
        en_dfi_fc_req_in_sr = 0x0;
    }
    else if(mddr_settings_ptr->dfi_lp_mode == DFI_LP_SR_ENA)
    {
        en_dfi_lp_req_in_sr = 0x1;
        en_dfi_lp_req_in_pd = 0x0;
        en_dfi_fc_req_in_sr = 0x0;
    }
    else    // DFI_LP_DISABLED
    {
        en_dfi_lp_req_in_sr = 0x0;
        en_dfi_lp_req_in_pd = 0x0;
        en_dfi_fc_req_in_sr = 0x0;
    }

    ddr_dfi_cntl_val  = (en_dfi_phyupd_ack & DDR_DFI_CNTL_EN_DFI_PHYUPD_ACK___M) << DDR_DFI_CNTL_EN_DFI_PHYUPD_ACK___S;
    ddr_dfi_cntl_val |= (en_dfi_ctrlupd_req & DDR_DFI_CNTL_EN_DFI_CTRLUPD_REQ___M) << DDR_DFI_CNTL_EN_DFI_CTRLUPD_REQ___S;
    ddr_dfi_cntl_val |= (en_dfi_lp_req_in_pd & DDR_DFI_CNTL_EN_DFI_LP_REQ_IN_PD___M) << DDR_DFI_CNTL_EN_DFI_LP_REQ_IN_PD___S;
    ddr_dfi_cntl_val |= (en_dfi_lp_req_in_sr & DDR_DFI_CNTL_EN_DFI_LP_REQ_IN_SR___M) << DDR_DFI_CNTL_EN_DFI_LP_REQ_IN_SR___S;
    ddr_dfi_cntl_val |= (dfi_ctrlupd_mode & DDR_DFI_CNTL_DFI_CTRLUPD_MODE___M) << DDR_DFI_CNTL_DFI_CTRLUPD_MODE___S;
    ddr_dfi_cntl_val |= (en_dfi_fc_req_in_sr & DDR_DFI_CNTL_EN_DFI_FC_REQ_IN_SR___M) << DDR_DFI_CNTL_EN_DFI_FC_REQ_IN_SR___S;
    ddr_dfi_cntl_val |= (dfi_freq_ratio & DDR_DFI_CNTL_DFI_FREQ_RATIO___M) << DDR_DFI_CNTL_DFI_FREQ_RATIO___S;
    ddr_dfi_cntl_val |= (dfi_ctrlupd_period & DDR_DFI_CNTL_DFI_CTRLUPD_PERIOD___M) << DDR_DFI_CNTL_DFI_CTRLUPD_PERIOD___S;
    ddr_dfi_cntl_val |= (dfi_lp_wakeup_from_pd & DDR_DFI_CNTL_DFI_LP_WAKEUP_FROM_PD___M) << DDR_DFI_CNTL_DFI_LP_WAKEUP_FROM_PD___S;
    ddr_dfi_cntl_val |= (dfi_lp_wakeup_from_sr & DDR_DFI_CNTL_DFI_LP_WAKEUP_FROM_SR___M) << DDR_DFI_CNTL_DFI_LP_WAKEUP_FROM_SR___S;
    ddr_dfi_cntl_val |= (dfi_phyupd_mode_type0 & DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE0___M) << DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE0___S;
    ddr_dfi_cntl_val |= (dfi_phyupd_mode_type1 & DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE1___M) << DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE1___S;
    ddr_dfi_cntl_val |= (dfi_phyupd_mode_type2 & DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE2___M) << DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE2___S;
    ddr_dfi_cntl_val |= (dfi_phyupd_mode_type3 & DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE3___M) << DDR_DFI_CNTL_DFI_PHYUPD_MODE_TYPE3___S;
#ifdef CONFIG_TESTOS_EMU
    ddr_dfi_cntl_val |= 0x40;
#endif

    return ddr_dfi_cntl_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR DFI control 1 register in
*    a DDR memory controller.
*
* @return
*    The DDR DFI control 1 register value.
*
* @author
*    lchavani/anthonyf
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_dfi_cntl_1_reg
(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t ddr_dfi_cntl_1_val;
    uint16_t fc_entry_idle_delay;

    // Use <= to avoid compiler warning when constant DFI_LP2_ENTRY_IDLE_DELAY_MIN is set to 0
    if(mddr_settings_ptr->dfi_lp2_entry_idle_delay <= DFI_LP2_ENTRY_IDLE_DELAY_MIN)
    {
        // Do not print warning when values are equal
        if (mddr_settings_ptr->dfi_lp2_entry_idle_delay != DFI_LP2_ENTRY_IDLE_DELAY_MIN)
        {
            monaco_log(MEDIUM, "   Low threshold for PHY DFI-LP2 entry idle delay outside range, setting to minimum = %#8.8x\n",
                DFI_LP2_ENTRY_IDLE_DELAY_MIN);
            mddr_settings_ptr->dfi_lp2_entry_idle_delay = DFI_LP2_ENTRY_IDLE_DELAY_MIN;
        }
    }

    // Use >= to avoid compiler warning when constant DFI_LP2_ENTRY_IDLE_DELAY_MAX is set to max value
    if(mddr_settings_ptr->dfi_lp2_entry_idle_delay >= DFI_LP2_ENTRY_IDLE_DELAY_MAX)
    {
        // Do not print warning when values are equal
        if (mddr_settings_ptr->dfi_lp2_entry_idle_delay != DFI_LP2_ENTRY_IDLE_DELAY_MAX)
        {
            monaco_log(MEDIUM, "   High threshold for PHY DFI-LP2 entry idle delay outside range, setting to maximum = %#8.8x\n",
                DFI_LP2_ENTRY_IDLE_DELAY_MAX);
            mddr_settings_ptr->dfi_lp2_entry_idle_delay = DFI_LP2_ENTRY_IDLE_DELAY_MAX;
        }
    }

    fc_entry_idle_delay = mddr_settings_ptr->dfi_lp2_entry_idle_delay;

    ddr_dfi_cntl_1_val  = (fc_entry_idle_delay & DFI_CNTL1_FC_ENTRY_IDLE_DELAY___M) << DFI_CNTL1_FC_ENTRY_IDLE_DELAY___S;

    return ddr_dfi_cntl_1_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR PHY control register in
*    a DDR memory controller.
*
* @return
*    The DDR PHY control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_phy_cntl_reg(void)
{
    uint32_t ddr_phy_cntl_val = 0x0;
    uint32_t en_dfi_clk_in_lp2 = 0x0;
    uint32_t en_ac_pdd = 0x1;

    ddr_phy_cntl_val  = (en_dfi_clk_in_lp2 & PHY_CNTL_EN_DFI_CLK_IN_LP2___M) << PHY_CNTL_EN_DFI_CLK_IN_LP2___S;
    ddr_phy_cntl_val |= (en_ac_pdd & PHY_CNTL_EN_AC_PDD___M) << PHY_CNTL_EN_AC_PDD___S;

    return ddr_phy_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR self refresh control register in
*    a DDR memory controller.
*
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                             settings information.
*
* @return
*    The DDR self refresh control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_self_ref_cntl_reg(mddr_settings_t *mddr_settings_ptr)
{
    uint32_t self_ref_cntl_val = 0x0;
    uint32_t sr_entry_idle_delay = mddr_settings_ptr->sr_entry_idle_delay;  // HPG default. Changeable at runtime using mddr_auto_self_refresh_enable()
    uint32_t en_sr_abort = 0x0;
    uint32_t en_sr_concurrent = 0x0;       // 0=no concurrency, 1=two CKE groups within a DIMM can both enter, 2=all CKE concurrent
    uint32_t en_sr_auto = 0xF;             // cke groups to enable self refresh on. Enable of all CKE, uses only valid CKEs

    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        // can use sr_abort
        en_sr_abort = 0x1;
    }

    // These settings could be optimized further based on the WRODT and RDODT SI settings implemented,
    // however, we are choosing to implement a more simplified approach here
    if ((common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM) && (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR3))
    {
        en_sr_concurrent = 0x3;   // Serialize self-refresh entry of CKE groups (required for DDR3 RDIMM per HPG)
    }
    else if (num_dimms_per_chan_poped > 1)
    {
        en_sr_concurrent = 0x2;   // All CKE's must be able to go into SR before SR happens
    }
    else
    {
        en_sr_concurrent = 0x1;   // Both CKE's on a single DIMM must be able to go into SR before SR happens
    }

    self_ref_cntl_val  = (sr_entry_idle_delay & SELF_REF_CNTL_SR_ENTRY_IDLE_DELAY___M) << SELF_REF_CNTL_SR_ENTRY_IDLE_DELAY___S;
    self_ref_cntl_val |= (en_sr_abort & SELF_REF_CNTL_EN_SR_ABORT___M) << SELF_REF_CNTL_EN_SR_ABORT___S;
    self_ref_cntl_val |= (en_sr_concurrent & SELF_REF_CNTL_EN_SR_CONCURRENT___M) << SELF_REF_CNTL_EN_SR_CONCURRENT___S;

    if(mddr_settings_ptr->auto_self_refresh_en)
    {
        self_ref_cntl_val |= (en_sr_auto & SELF_REF_CNTL_EN_SR_AUTO___M) << SELF_REF_CNTL_EN_SR_AUTO___S;
    }


    return self_ref_cntl_val;
}




/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR power-down control register in
*    a DDR memory controller.
*
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                             settings information.
*
* @return
*    The power-down control register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_power_down_cntl_reg(mddr_settings_t *mddr_settings_ptr)
{
    uint32_t auto_power_cntl_val = 0x0;
    uint32_t pd_entry_idle_delay = mddr_settings_ptr->pd_entry_idle_delay;  // HPG default. Changeable at runtime using mddr_auto_power_down_enable()

    auto_power_cntl_val = (pd_entry_idle_delay & PWR_DOWN_CNTL_PD_ENTRY_IDLE_DELAY___M) << PWR_DOWN_CNTL_PD_ENTRY_IDLE_DELAY___S;

    if(mddr_settings_ptr->auto_power_down_en)
    {
        auto_power_cntl_val |= (common_cfg.slots_cke_sel & PWR_DOWN_CNTL_EN_PD_ACT___M) << PWR_DOWN_CNTL_EN_PD_ACT___S;
    }

    return auto_power_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR CA bus control register in
*    a DDR memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*
* @return
*    The DDR CA bus control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_ca_bus_cntl_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t ca_bus_cntl_val;

    uint32_t en_output_inversion = 0;             // only for DDR4 RDIMM/LRDIMM?
    uint32_t inv_ca_par = 0;
    uint32_t en_ca_par = 0;
    uint32_t ck_always_on = 0;
    uint32_t en_gear_down = 0;
    uint32_t ca_stretch;


    ca_stretch = mddr_settings_ptr->ca_stretch;


    if(common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        // polarity of data mask, 0=positive(DDR3), 1=negative(DDR4)
        // enable output inversion for DDR4 RDIMM/LRDIMM
        if (common_cfg_ptr->mod_type != SPD_MODULE_TYPE_UDIMM)
        {
            en_output_inversion = 1;
        }

        if (mddr_settings_ptr->ca_parity != CA_PARITY_DISABLE)
        {
            if ((common_cfg_ptr->mod_type == SPD_MODULE_TYPE_UDIMM) &&
                ((mddr_settings_ptr->ca_parity == CA_PARITY_DRAM) ||
                 (mddr_settings_ptr->ca_parity == CA_PARITY_DRAM_DIMM)))
            {
                en_ca_par = 1; // ignore RCD parity if UDIMM
            }
            else
            {
                if (mddr_settings_ptr->ca_parity == CA_PARITY_DRAM)
                {
                    if (ddr_rate <= 2400)    // RCD latency = 0
                    {
                       en_ca_par = 1;
                    }
                    else                     // RCD latency != 0
                    {
                       en_ca_par = 3;
                    }
                }
                else
                {
                  en_ca_par = mddr_settings_ptr->ca_parity & 0x3;
                }
            }

            // if ((mddr_settings_ptr->ca_parity == CA_PARITY_DRAM) ||
            //     (mddr_settings_ptr->ca_parity == CA_PARITY_DRAM_DIMM))
            // set PL in RDWR_0, set MR5 A[2:0]
        }
    }
    else
    {
        if ((common_cfg_ptr->mod_type != SPD_MODULE_TYPE_UDIMM) &&
            ((mddr_settings_ptr->ca_parity == CA_PARITY_DIMM) ||
             (mddr_settings_ptr->ca_parity == CA_PARITY_DRAM_DIMM)))
        {
            //  Must enable DIMM parity for DDR3 L/RDIMMs
            en_ca_par = 1;
        }
        else    // DDR3 UDIMM
        {
            if(mddr_settings_ptr->ca_parity != CA_PARITY_DISABLE)
            {
                monaco_log(HIGH, "  !!   WARNING, command/address parity not available but configured. Overriding\n");
                mddr_settings_ptr->ca_parity = CA_PARITY_DISABLE;
            }

            ck_always_on = 0;
        }
    }


    ca_bus_cntl_val  = (ca_stretch & CA_STRETCH___M) << CA_STRETCH___S;
    ca_bus_cntl_val |= (en_gear_down & EN_GEAR_DOWN___M) << EN_GEAR_DOWN___S;
    ca_bus_cntl_val |= (ck_always_on & CK_ALWAYS_ON___M) << CK_ALWAYS_ON___S;
    ca_bus_cntl_val |= (en_ca_par & EN_CA_PAR___M) << EN_CA_PAR___S;
    ca_bus_cntl_val |= (inv_ca_par & INV_CA_PAR___M)<< INV_CA_PAR___S;
    ca_bus_cntl_val |= (en_output_inversion & EN_OUTPUT_INVERSION___M) << EN_OUTPUT_INVERSION___S;


    return ca_bus_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR DQ bus control register in
*    a DDR memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The DDR DQ bus control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_dq_bus_cntl_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t ddr_dq_bus_cntl_val;
    uint32_t wr_mask_polarity = 0x0;

    // polarity of data mask, 0=positive(DDR3), 1=negative(DDR4)
    if(common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        wr_mask_polarity = 0x1;
    }

    ddr_dq_bus_cntl_val  = (wr_mask_polarity & WR_MASK_POLARITY___M) << WR_MASK_POLARITY___S;


    return ddr_dq_bus_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the thermal throttling control 0 register in
*    a DDR memory controller. This includes only the settings with the enable
*    cleared indicating throttling is disabled.
*
*                                  @param
*    therm_throttle_settings_ptr       The pointer to the structure containing the
*                                       thermal settings information.
*
* @return
*    The thermal throttling control 0 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_thermal_cntl_0_reg
(
    mddr_therm_throttle_settings_t *therm_throttle_settings_ptr
)
{
    uint32_t thermal_cntl_0_val;

    uint32_t weight_act = therm_throttle_settings_ptr->act_weight;
    uint32_t weight_pchg = therm_throttle_settings_ptr->pchg_weight;
    uint32_t weight_write_bc4 = therm_throttle_settings_ptr->write_bc4_weight;
    uint32_t weight_write_bl8 = therm_throttle_settings_ptr->write_bl8_weight;
    uint32_t weight_read_bc4 = therm_throttle_settings_ptr->read_bc4_weight;
    uint32_t weight_read_bl8 = therm_throttle_settings_ptr->read_bl8_weight;


    thermal_cntl_0_val  = (weight_act & THERMAL_CNTL_0_WEIGHT_ACT___M) << THERMAL_CNTL_0_WEIGHT_ACT___S;
    thermal_cntl_0_val |= (weight_pchg & THERMAL_CNTL_0_WEIGHT_PCHG___M) << THERMAL_CNTL_0_WEIGHT_PCHG___S;
    thermal_cntl_0_val |= (weight_write_bc4 & THERMAL_CNTL_0_WEIGHT_WRITE_BC4___M) << THERMAL_CNTL_0_WEIGHT_WRITE_BC4___S;
    thermal_cntl_0_val |= (weight_write_bl8 & THERMAL_CNTL_0_WEIGHT_WRITE_BL8___M) << THERMAL_CNTL_0_WEIGHT_WRITE_BL8___S;
    thermal_cntl_0_val |= (weight_read_bc4 & THERMAL_CNTL_0_WEIGHT_READ_BC4___M) << THERMAL_CNTL_0_WEIGHT_READ_BC4___S;
    thermal_cntl_0_val |= (weight_read_bl8 & THERMAL_CNTL_0_WEIGHT_READ_BL8___M) << THERMAL_CNTL_0_WEIGHT_READ_BL8___S;


    return thermal_cntl_0_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the thermal throttling control 1 register in
*    a DDR memory controller.
*
*                                  @param
*    therm_throttle_settings_ptr       The pointer to the structure containing the
*                                       thermal settings information.
*
* @return
*    The thermal throttling control 1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_thermal_cntl_1_reg
(
    mddr_therm_throttle_settings_t *therm_throttle_settings_ptr
)
{
    uint32_t thermal_cntl_1_val;
    uint32_t throttle_high_wm = therm_throttle_settings_ptr->throttle_high_wm;


    thermal_cntl_1_val = throttle_high_wm & THERMAL_CNTL_1_THROTTLE_HIGH_WM___M;

    return thermal_cntl_1_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the thermal throttling control 2 register in
*    a DDR memory controller.
*
*                                  @param
*    therm_throttle_settings_ptr       The pointer to the structure containing the
*                                       thermal settings information.
*
* @return
*    The thermal throttling control 2 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_thermal_cntl_2_reg
(
    mddr_therm_throttle_settings_t *therm_throttle_settings_ptr
)
{
    uint32_t thermal_cntl_2_val;
    uint32_t throttle_low_wm = therm_throttle_settings_ptr->throttle_low_wm;


    thermal_cntl_2_val = throttle_low_wm & THERMAL_CNTL_2_THROTTLE_LOW_WM___M;

    return thermal_cntl_2_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the thermal throttling control 3 register in
*    a DDR memory controller.
*
*                                  @param
*    therm_throttle_settings_ptr       The pointer to the structure containing the
*                                       thermal settings information.
*
* @return
*    The thermal throttling control 3 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_thermal_cntl_3_reg
(
    mddr_therm_throttle_settings_t *therm_throttle_settings_ptr
)
{
    uint32_t thermal_cntl_3_val;
    uint32_t leak_amount = therm_throttle_settings_ptr->sum_deplete_val;


    thermal_cntl_3_val = leak_amount & THERMAL_CNTL_3_LEAK_AMOUNT___M;

    return thermal_cntl_3_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the thermal throttling control 4 register in
*    a DDR memory controller.
*
*                                  @param
*    therm_throttle_settings_ptr       The pointer to the structure containing the
*                                       thermal settings information.
*
* @return
*    The thermal throttling control 4 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_thermal_cntl_4_reg
(
    mddr_therm_throttle_settings_t *therm_throttle_settings_ptr
)
{
    uint32_t thermal_cntl_4_val;
    uint32_t leak_interval = therm_throttle_settings_ptr->sum_deplete_interval;


    thermal_cntl_4_val = leak_interval & THERMAL_CNTL_4_LEAK_INTERVAL___M;

    return thermal_cntl_4_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the Bus Utilization Monitor (BUM) DCVS
*    control register value in a DDR memory controller for the Busy event.
*
*                                  @param
*    bum_event_settings_ptr     The pointer to the structure containing the
*                                BUM event settings information.
*
* @return
*    The Bus Utilization Monitor (BUM) DCVS Control register value
*
* @author
*    anthonyf
*
******************************************************************************/
uint32_t mddr_mc_build_busy_dcvs_cnt_reg
(
    mddr_bum_event_settings_t *bum_event_settings_ptr
)
{
    uint32_t dcvs_cnt_val = mddr_reg_vals.bum_regs.dcvs_cntl_val;

    if (bum_event_settings_ptr->enable == true)
    {
        // Clear the appropriate disable bits in the register
        dcvs_cnt_val &= ~(DCVS_CNTL_BUSY_CNT_DISABLE___M<<DCVS_CNTL_BUSY_CNT_DISABLE___S);
    }
    else
    {
        // Set the appropriate disable bits in the register
        dcvs_cnt_val |= (DCVS_CNTL_BUSY_CNT_DISABLE___M<<DCVS_CNTL_BUSY_CNT_DISABLE___S);
    }

    return dcvs_cnt_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the Bus Utilization Monitor (BUM) DCVS
*    control register value in a DDR memory controller for the BCQ Full event.
*
*                                  @param
*    bum_event_settings_ptr     The pointer to the structure containing the
*                                BUM event settings information.
*
* @return
*    The Bus Utilization Monitor (BUM) DCVS Control register value
*
* @author
*    anthonyf
*
******************************************************************************/
uint32_t mddr_mc_build_bcqfull_dcvs_cnt_reg
(
    mddr_bum_event_settings_t *bum_event_settings_ptr
)
{
    uint32_t dcvs_cnt_val = mddr_reg_vals.bum_regs.dcvs_cntl_val;

    if (bum_event_settings_ptr->enable == true)
    {
        // Clear the appropriate disable bits in the register
        dcvs_cnt_val &= ~(DCVS_CNTL_BCQFULL_CNT_DISABLE___M<<DCVS_CNTL_BCQFULL_CNT_DISABLE___S);
    }
    else
    {
        // Set the appropriate disable bits in the register
        dcvs_cnt_val |= (DCVS_CNTL_BCQFULL_CNT_DISABLE___M<<DCVS_CNTL_BCQFULL_CNT_DISABLE___S);
    }

    return dcvs_cnt_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function checks the limits for the Bus Utilization Monitor (BUM)
*     threshholds selected by the user.
*
*                                  @param
*    mddr_settings_ptr          The pointer to the structure containing the
*                                BUM settings information.
*    ddr_bum_perf_idx           The index into the array holding low threshholds
*                                values for each performance index.
*
* @return
*    None
*
* @author
*    anthonyf
*
******************************************************************************/
void mddr_mc_check_bum_thresholds
(
    mddr_bum_event_settings_t *bum_event_settings_ptr,
    uint8_t ddr_bum_perf_idx
)
{
    if(bum_event_settings_ptr->lo_threshold[ddr_bum_perf_idx] > bum_event_settings_ptr->hi_threshold[ddr_bum_perf_idx])
    {
        uint32_t new_lo_threshold = bum_event_settings_ptr->hi_threshold[ddr_bum_perf_idx];
        uint32_t new_hi_threshold = bum_event_settings_ptr->lo_threshold[ddr_bum_perf_idx];

        monaco_log(MEDIUM, "   Low threshold %#8.8x exceeds high threshold %#8.8x, switching low and high.\n",
            bum_event_settings_ptr->lo_threshold[ddr_bum_perf_idx],
            bum_event_settings_ptr->hi_threshold[ddr_bum_perf_idx]);

        bum_event_settings_ptr->hi_threshold[ddr_bum_perf_idx] = new_hi_threshold;
        bum_event_settings_ptr->lo_threshold[ddr_bum_perf_idx] = new_lo_threshold;
    }

    // Use <= to avoid compiler warning when constant DDR_BUM_LO_THRESHOLD_MIN is set to 0
    //  when DDR_BUM_LO_THRESHOLD_MIN is defined as zero.
    if(bum_event_settings_ptr->lo_threshold[ddr_bum_perf_idx] <= DDR_BUM_LO_THRESHOLD_MIN)
    {
        // Do not print warning when values are equal
        if (bum_event_settings_ptr->lo_threshold[ddr_bum_perf_idx] != DDR_BUM_LO_THRESHOLD_MIN)
        {
            monaco_log(MEDIUM, "   Low threshold for perf index %d outside range, setting to minimum = %#8.8x\n",
                ddr_bum_perf_idx,
                DDR_BUM_LO_THRESHOLD_MIN);
            bum_event_settings_ptr->lo_threshold[ddr_bum_perf_idx] = DDR_BUM_LO_THRESHOLD_MIN;
        }
    }

    // Use >= to avoid compiler warning when constant DDR_BUM_HI_THRESHOLD_MAX is set to max value
    if(bum_event_settings_ptr->hi_threshold[ddr_bum_perf_idx] >= DDR_BUM_HI_THRESHOLD_MAX)
    {
        // Do not print warning when values are equal
        if (bum_event_settings_ptr->hi_threshold[ddr_bum_perf_idx] != DDR_BUM_HI_THRESHOLD_MAX)
        {
            monaco_log(MEDIUM, "   High threshold for perf index %d outside range, setting to maximum = %#8.8x\n",
                ddr_bum_perf_idx,
                DDR_BUM_HI_THRESHOLD_MAX);
            bum_event_settings_ptr->hi_threshold[ddr_bum_perf_idx] = DDR_BUM_HI_THRESHOLD_MAX;
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the Bus Utilization Monitor (BUM) DCVS
*    high threshhold register for the given event and performance threshold in a
*    DDR memory controller.
*
*                                  @param
*    bum_event_settings_ptr     The pointer to the structure containing the
*                                BUM event settings information.
*    ddr_bum_perf_idx           The index into the array holding low threshholds
*                                values for each performance index.
*
* @return
*    The BCQFULL event, high threshhold, performance index 1, register value.
*
* @author
*    anthonyf
*
******************************************************************************/
uint32_t mddr_mc_build_dcvs_high_threshold_reg
(
    mddr_bum_event_settings_t *bum_event_settings_ptr,
    uint8_t ddr_bum_perf_idx
)
{
    uint32_t dcvs_high_threshold_val = 0;
    uint32_t threshold = bum_event_settings_ptr->hi_threshold[ddr_bum_perf_idx];

    dcvs_high_threshold_val = (threshold & DCVS_HIGH_THRESHOLD___M) << DCVS_HIGH_THRESHOLD___S;

    return dcvs_high_threshold_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the Bus Utilization Monitor (BUM) DCVS
*    low threshhold register for the given event and performance threshold in a
*    DDR memory controller.
*
*                                  @param
*    bum_event_settings_ptr     The pointer to the structure containing the
*                                BUM event settings information.
*    ddr_bum_perf_idx           The index into the array holding low threshholds
*                                values for each performance index.
*
* @return
*    The BCQFULL event, low threshhold, performance index 1, register value.
*
* @author
*    anthonyf
*
******************************************************************************/
uint32_t mddr_mc_build_dcvs_low_threshold_reg
(
    mddr_bum_event_settings_t *bum_event_settings_ptr,
    uint8_t ddr_bum_perf_idx
)
{
    uint32_t dcvs_low_threshold_val = 0;
    uint32_t threshold = bum_event_settings_ptr->lo_threshold[ddr_bum_perf_idx];

    dcvs_low_threshold_val = (threshold & DCVS_LOW_THRESHOLD___M) << DCVS_LOW_THRESHOLD___S;

    return dcvs_low_threshold_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function starts the scrub engine initializing the memory to the
*     scrubbing start state for a single DDR channel.
*
*                                  @param
*    mddr_base_addr             The base address of the configuration registers for
*                                the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_ecc_scrub_start_init
(
    uint64_t mddr_base_addr
)
{
    uint32_t scrub_addr_wr0_val=0x0;  // Start with the first addr
    uint32_t scrub_addr_wr1_val=0x0;

    uint32_t scrub_cmd_cntl_val;
    uint32_t scrub_exec_cntl_val;
    uint32_t scrub_cmd_single_val;


    monaco_log(CRITICAL, "  Starting scrub initialization...\n");

    scrub_cmd_cntl_val  = (SCRUB_CMD_CNTL_RESET_DCF_PTRS_CLR & SCRUB_CMD_CNTL_RESET_DCF_PTRS___M) << SCRUB_CMD_CNTL_RESET_DCF_PTRS___S;
    scrub_cmd_cntl_val |= (SCRUB_CMD_CNTL_WDB_ENTRY_WRSRC    & SCRUB_CMD_CNTL_NWDB_NOT_WDB___M)   << SCRUB_CMD_CNTL_NWDB_NOT_WDB___S;
    scrub_cmd_cntl_val |= (SCRUB_CMD_CNTL_CMD_TYPE_W         & SCRUB_CMD_CNTL_CMD_TYPE___M)       << SCRUB_CMD_CNTL_CMD_TYPE___S;
    scrub_cmd_cntl_val |= (SCRUB_CMD_CNTL_START_SEG_FIRST    & SCRUB_CMD_CNTL_START_SEG___M)      << SCRUB_CMD_CNTL_START_SEG___S;
    scrub_cmd_cntl_val |= (SCRUB_CMD_CNTL_DATA_SEG_ALL       & SCRUB_CMD_CNTL_DATA_SEG___M)       << SCRUB_CMD_CNTL_DATA_SEG___S;

    scrub_cmd_single_val  = (SCRUB_CMD_SINGLE_READ_RD_LFSR                & SCRUB_CMD_SINGLE_READ_RD_LFSR___M)           << SCRUB_CMD_SINGLE_READ_RD_LFSR___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_SEED_RD_LFSR_IGNR           & SCRUB_CMD_SINGLE_SEED_RD_LFSR___M)           << SCRUB_CMD_SINGLE_SEED_RD_LFSR___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_SEED_WR_LFSR_IGNR           & SCRUB_CMD_SINGLE_SEED_WR_LFSR___M)           << SCRUB_CMD_SINGLE_SEED_WR_LFSR___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE_IGNR & SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE___M) << SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_CLR_ADDR_MAX_SET            & SCRUB_CMD_SINGLE_CLR_ADDR_MAX___M)           << SCRUB_CMD_SINGLE_CLR_ADDR_MAX___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_WRITE_ONLY_DIS              & SCRUB_CMD_SINGLE_WRITE_ONLY___M)             << SCRUB_CMD_SINGLE_WRITE_ONLY___S;

    scrub_exec_cntl_val  = (SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN_YES & SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN___M) << SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_CMD_FIFO_EN_YES       & SCRUB_EXEC_CNTL_CMD_FIFO_EN___M)       << SCRUB_EXEC_CNTL_CMD_FIFO_EN___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_RESP_DIS_NO           & SCRUB_EXEC_CNTL_RESP_DIS___M)          << SCRUB_EXEC_CNTL_RESP_DIS___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_FIFO_LOOP_DIS         & SCRUB_EXEC_CNTL_FIFO_LOOP___M)         << SCRUB_EXEC_CNTL_FIFO_LOOP___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_ADDR_MAX_HALT_YES     & SCRUB_EXEC_CNTL_ADDR_MAX_HALT___M)     << SCRUB_EXEC_CNTL_ADDR_MAX_HALT___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_NUM_CMDS_1            & SCRUB_EXEC_CNTL_NUM_CMDS___M)          << SCRUB_EXEC_CNTL_NUM_CMDS___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_CMD_TIMER_SEED_NONE   & SCRUB_EXEC_CNTL_CMD_TIMER_SEED___M)    << SCRUB_EXEC_CNTL_CMD_TIMER_SEED___S;


    mddr_mc_ecc_scrub_setup_wdb(mddr_base_addr);


    // row, msb_col
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_ADDR_WR_0_OFFSET, "SCRUB_ADDR_WR_0", scrub_addr_wr0_val);

    // wdb_ndx, dimm, cid, rank, bank
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_ADDR_WR_1_OFFSET, "SCRUB_ADDR_WR_1", scrub_addr_wr1_val);

    // cmd_type=write, all 4 data segments
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_CMD_CNTL_OFFSET, "SCRUB_CMD_CNTL", scrub_cmd_cntl_val);

    // clear halt cmd
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_CMD_SINGLE_OFFSET, "SCRUB_CMD_SINGLE", scrub_cmd_single_val);
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_CMD_SINGLE_OFFSET, "SCRUB_CMD_SINGLE", 0x0);

    // Start scrub init
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_EXEC_CNTL_OFFSET, "SCRUB_EXEC_CNTL", scrub_exec_cntl_val);
}



/*!****************************************************************************
*
* @par Description:
*    This function stops the scrub engine from initializing the memory to the
*     scrubbing start state for a single DDR channel.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_ecc_scrub_stop_init
(
    uint64_t mddr_base_addr
)
{
    uint32_t scrub_exec_cntl_val;
    uint32_t scrub_cmd_single_val;


    monaco_log(CRITICAL, "  Stopping scrub init, clearing halt at max address\n");

    scrub_exec_cntl_val  = (SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN_NO  & SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN___M) << SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_CMD_FIFO_EN_NO        & SCRUB_EXEC_CNTL_CMD_FIFO_EN___M)       << SCRUB_EXEC_CNTL_CMD_FIFO_EN___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_RESP_DIS_NO           & SCRUB_EXEC_CNTL_RESP_DIS___M)          << SCRUB_EXEC_CNTL_RESP_DIS___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_FIFO_LOOP_DIS         & SCRUB_EXEC_CNTL_FIFO_LOOP___M)         << SCRUB_EXEC_CNTL_FIFO_LOOP___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_ADDR_MAX_HALT_NO      & SCRUB_EXEC_CNTL_ADDR_MAX_HALT___M)     << SCRUB_EXEC_CNTL_ADDR_MAX_HALT___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_NUM_CMDS_0            & SCRUB_EXEC_CNTL_NUM_CMDS___M)          << SCRUB_EXEC_CNTL_NUM_CMDS___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_CMD_TIMER_SEED_NONE   & SCRUB_EXEC_CNTL_CMD_TIMER_SEED___M)    << SCRUB_EXEC_CNTL_CMD_TIMER_SEED___S;

    scrub_cmd_single_val  = (SCRUB_CMD_SINGLE_READ_RD_LFSR                & SCRUB_CMD_SINGLE_READ_RD_LFSR___M)           << SCRUB_CMD_SINGLE_READ_RD_LFSR___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_SEED_RD_LFSR_IGNR           & SCRUB_CMD_SINGLE_SEED_RD_LFSR___M)           << SCRUB_CMD_SINGLE_SEED_RD_LFSR___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_SEED_WR_LFSR_IGNR           & SCRUB_CMD_SINGLE_SEED_WR_LFSR___M)           << SCRUB_CMD_SINGLE_SEED_WR_LFSR___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE_IGNR & SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE___M) << SCRUB_CMD_SINGLE_CLR_RD_LFSR_MISCOMPARE___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_CLR_ADDR_MAX_SET            & SCRUB_CMD_SINGLE_CLR_ADDR_MAX___M)           << SCRUB_CMD_SINGLE_CLR_ADDR_MAX___S;
    scrub_cmd_single_val |= (SCRUB_CMD_SINGLE_WRITE_ONLY_DIS              & SCRUB_CMD_SINGLE_WRITE_ONLY___M)             << SCRUB_CMD_SINGLE_WRITE_ONLY___S;

    // stop scrub init
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_EXEC_CNTL_OFFSET, "SCRUB_EXEC_CNTL", scrub_exec_cntl_val);

    // clear halt on max address
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_CMD_SINGLE_OFFSET, "SCRUB_CMD_SINGLE", scrub_cmd_single_val);
}



/*!****************************************************************************
*
* @par Description:
*    This function starts the ECC based scrubbing of DDR for a single DDR
*     channel.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    None
*
* @author
*    gkowis, lchavani
*
******************************************************************************/
void mddr_mc_ecc_scrub_start
(
    uint64_t mddr_base_addr,
    uint8_t ddr_chan
)
{
    uint32_t scrub_cmd_cntl_val;
    uint32_t scrub_exec_cntl_val;
    uint8_t cmd_timer_seed;

    monaco_log(MEDIUM, "  Starting periodic scrubs\n");

    scrub_cmd_cntl_val  = (SCRUB_CMD_CNTL_RESET_DCF_PTRS_CLR & SCRUB_CMD_CNTL_RESET_DCF_PTRS___M) << SCRUB_CMD_CNTL_RESET_DCF_PTRS___S;
    scrub_cmd_cntl_val |= (SCRUB_CMD_CNTL_CMD_TYPE_R         & SCRUB_CMD_CNTL_CMD_TYPE___M)       << SCRUB_CMD_CNTL_CMD_TYPE___S;
    scrub_cmd_cntl_val |= (SCRUB_CMD_CNTL_START_SEG_FIRST    & SCRUB_CMD_CNTL_START_SEG___M)      << SCRUB_CMD_CNTL_START_SEG___S;
    scrub_cmd_cntl_val |= (SCRUB_CMD_CNTL_DATA_SEG_ALL       & SCRUB_CMD_CNTL_DATA_SEG___M)       << SCRUB_CMD_CNTL_DATA_SEG___S;

    scrub_exec_cntl_val  = (SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN_YES & SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN___M) << SCRUB_EXEC_CNTL_DRAM_MULTI_CMD_EN___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_CMD_FIFO_EN_YES       & SCRUB_EXEC_CNTL_CMD_FIFO_EN___M)       << SCRUB_EXEC_CNTL_CMD_FIFO_EN___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_RESP_DIS_NO           & SCRUB_EXEC_CNTL_RESP_DIS___M)          << SCRUB_EXEC_CNTL_RESP_DIS___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_FIFO_LOOP_DIS         & SCRUB_EXEC_CNTL_FIFO_LOOP___M)         << SCRUB_EXEC_CNTL_FIFO_LOOP___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_ADDR_MAX_HALT_NO      & SCRUB_EXEC_CNTL_ADDR_MAX_HALT___M)     << SCRUB_EXEC_CNTL_ADDR_MAX_HALT___S;
    scrub_exec_cntl_val |= (SCRUB_EXEC_CNTL_NUM_CMDS_16           & SCRUB_EXEC_CNTL_NUM_CMDS___M)          << SCRUB_EXEC_CNTL_NUM_CMDS___S;

    // Obtain the command timer seed value to be programmed
    cmd_timer_seed = mddr_mc_ecc_scrub_get_cmd_timer_seed(ddr_chan);

    scrub_exec_cntl_val |= (cmd_timer_seed & SCRUB_EXEC_CNTL_CMD_TIMER_SEED___M)    << SCRUB_EXEC_CNTL_CMD_TIMER_SEED___S;


    // set for periodic scrub read
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_CMD_CNTL_OFFSET, "SCRUB_CMD_CNTL", scrub_cmd_cntl_val);

    // start periodic scrub reads
    mddr_set_reg(mddr_base_addr + MDDR_SCRUB_EXEC_CNTL_OFFSET, "SCRUB_EXEC_CNTL", scrub_exec_cntl_val);


}


/*!****************************************************************************
*
* @par Description:
*    This function waits until the scrub status indicates that all the maximum
*     dram address has been reached for a single DDR channel.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*                                  @param
*    ddr_chan               DDR channel to perform function on.
*
*
* @return
*    None
*
* @author
*    gkowis, lchavani
*
* @par Notes:
*    Timeout varies depending on target. 10ms for silicon and 1s for emulation.
*
******************************************************************************/
void mddr_mc_ecc_scrub_check_complete
(
    uint64_t mddr_base_addr,
    uint8_t ddr_chan
)
{
    uint32_t scrub_status_val;
    uint32_t wait;
    uint32_t lfsr_miscompare = 0x0;


    if (platform_mode != SILICON)
    {
        // TODO: wait should be increased for emulation, however
        // TODO:   timeouts in the loader scripts need adjusting as well.
        wait = MILLI_SEC_PER_SEC;
    }
    else
    {
        wait = 90 * MILLI_SEC_PER_SEC;
    }

    monaco_log(LOW, "######################################\n");
    monaco_log(LOW, " Prepping memory for ECC operation.\n");
    monaco_log(LOW, "   This will take a while to complete\n");
    monaco_log(LOW, "######################################\n");

    mddr_rd_chk_reg(mddr_base_addr, MDDR_SCRUB_STATUS_OFFSET,
                    (SCRUB_STATUS_ADDR_MAX___M << SCRUB_STATUS_ADDR_MAX___S),
                    SCRUB_STATUS_ADDR_MAX_SET, wait);

    scrub_status_val = mddr_get_reg(mddr_base_addr + MDDR_SCRUB_STATUS_OFFSET, "SCRUB_STATUS");
    lfsr_miscompare = (scrub_status_val >> SCRUB_STATUS_RD_LFSR_MISCOMPARE___S) & SCRUB_STATUS_RD_LFSR_MISCOMPARE___M;

    if (lfsr_miscompare != 0x0)
    {
        monaco_log(CRITICAL, "ERROR - read LFSR miscompared on HDDRSS = %u\n", hddrss[ddr_chan]);
    }

}



/*!****************************************************************************
*
* @par Description:
*    This function sets the memory controller write data buffer to a state
*     suitable for initializing memory for scrub for a single DDR channel.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_ecc_scrub_setup_wdb
(
    uint64_t mddr_base_addr
)
{
    uint32_t data_pattern = 0x0;
    uint32_t strobes = 0xFFFFFFFF;
    uint32_t error_bits = 0x0;
    unsigned cl_num;
    unsigned segment;
    uint32_t cmd_wdb_access_val;


    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD00_OFFSET, "CMD_WR_DATA_WORD00", data_pattern);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD01_OFFSET, "CMD_WR_DATA_WORD01", data_pattern);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD02_OFFSET, "CMD_WR_DATA_WORD02", data_pattern);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD03_OFFSET, "CMD_WR_DATA_WORD03", data_pattern);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD04_OFFSET, "CMD_WR_DATA_WORD04", data_pattern);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD05_OFFSET, "CMD_WR_DATA_WORD05", data_pattern);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD06_OFFSET, "CMD_WR_DATA_WORD06", data_pattern);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD07_OFFSET, "CMD_WR_DATA_WORD07", data_pattern);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD08_OFFSET, "CMD_WR_DATA_WORD08", strobes);
    mddr_set_reg(mddr_base_addr + MDDR_CMD_WR_DATA_WORD09_OFFSET, "CMD_WR_DATA_WORD09", error_bits);

    for(cl_num = 0; cl_num < MDDR_NUM_WDB_CACHE_LINES; ++cl_num)
    {
        for(segment = 0; segment < MDDR_NUM_SEGMENTS_WDB_CACHE_LINE; ++segment)
        {
            cmd_wdb_access_val  = (cl_num & CMD_WDB_ACCESS_WDB_DATA_NDX___M) << CMD_WDB_ACCESS_WDB_DATA_NDX___S;
            cmd_wdb_access_val |= (segment & CMD_WDB_ACCESS_WDB_SEG_NDX___M) << CMD_WDB_ACCESS_WDB_SEG_NDX___S;
            cmd_wdb_access_val |= (CMD_WDB_ACCESS_WRITE_WDB & CMD_WDB_ACCESS_WRITE_N_READ_WDB___M) << CMD_WDB_ACCESS_WRITE_N_READ_WDB___S;

            mddr_set_reg(mddr_base_addr + MDDR_CMD_WDB_ACCESS_OFFSET, "CMD_WDB_ACCESS", cmd_wdb_access_val);
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function calculates the Command Timer Seed value for the
*     DDR Scrub Engine command timer based on the specified time to scrub
*     all memory.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
*
* @return
*    The value of the command timer seed to be programmed into
*     MDDR_SCRUB_EXEC_CNTL register
*
* @author
*    lchavani
*
* @par Notes:
*    The total time to scrub all memory per channel is currently fixed
*    at 24 hours.
*
******************************************************************************/
uint8_t mddr_mc_ecc_scrub_get_cmd_timer_seed(uint8_t ddr_chan)
{
    uint8_t dimm_slot;
    uint64_t ddr_size_mb = 0;
    uint64_t ddr_size_bytes = 0;
    uint64_t cmd_timer_seed;
    uint64_t cts_numerator;
    uint64_t cts_denominator;

    //=============================================================================================
    // Formula to calculate the time to scrub all memory per channel:
    // Time to scrub all of memory =
    // Memory Size x
    // (1 cacheline / 128 Bytes ) x
    // (1 Scrub Timer Interval / NUM_CMDS) x
    // ((2^16 DRAM clock cycles x (CMD_TIMER_SEED + 1)) / 1 Scrub Timer Interval ) x
    // (DRAM clock period / 1 DRAM clock cycle)

    // Hence, with time to scrub set to 24 hours, the formula for CMD_TIMER_SEED is:
    // CMD_TIMER_SEED =
    // [86400 (Time to scrub all of memory) x
    // (128 / 1 cacheline) x
    // (NUM_CMDS / 1 Scrub Timer Interval) x
    // (1 / 2^16 DRAM clock cycles) x
    // (1 DRAM clock cycle / DRAM clock period) x
    // (1 / Memory Size) ] - 1
    //=============================================================================================

    // Calculate the total memory populated per channel
    for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        if(mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            ddr_size_mb += mddr_dimm_configs[ddr_chan][dimm_slot].dimm_size_mb;
        }
    }

    // Obtain the total memory per channel in bytes
    ddr_size_bytes = ddr_size_mb * KB_PER_MB * BYTES_PER_KB;

    // Command Timer seed calculation - Numerator
    cts_numerator = (SCRUB_EXEC_CNTL_TIME_TO_SCRUB_ALLMEM * SCRUB_EXEC_CNTL_BYTES_PER_CACHELINE *
           SCRUB_EXEC_CNTL_NUM_CMDS_16 * (uint64_t)mem_freq_mhz * KHZ_PER_MHZ * HZ_PER_KHZ);

    // Command Timer seed calculation - Denominator
    cts_denominator = ((uint64_t)ddr_size_bytes * SCRUB_EXEC_CNTL_DRAM_CLK_CYCLES_MULT_SEED);

    if ((cts_numerator < cts_denominator) || (cts_denominator == 0))
    {
        cmd_timer_seed = 1;    // Note that CMD_TIMER_SEED = 0 is also a valid value. Here, we have set it to the min value of 1.
    }
    else
    {
        cmd_timer_seed = com_ceil_div_64(cts_numerator, cts_denominator);

        // Subtract 1 to obtain the final value of the CMD_TIMER_SEED
        cmd_timer_seed -=1;
    }

    // Check for the CMD_TIMER_SEED upper bound
    if (cmd_timer_seed > SCRUB_EXEC_CNTL_CMD_TIMER_SEED_MAX)
        cmd_timer_seed = SCRUB_EXEC_CNTL_CMD_TIMER_SEED_MAX;

    return cmd_timer_seed;
}


/*!****************************************************************************
*
* @par Description:
*    This function gets the indication of available ranks for a DDR channel.
*
* @return
*    The set of flags indicating which ranks are valid for the memory controller.
*
* @author
*    gkowis
*
* @par Notes:
*    The indication provided by the HW is based on prior SW configuration.
*
******************************************************************************/
uint32_t mddr_mc_get_avail_ranks(void)
{
    uint32_t valid_ranks;


    // Get slot 0 ranks
    valid_ranks = 0xF >> (DDR_MAX_RANKS_PER_SLOT - common_cfg.slot_config[0].num_ranks);

    if (common_cfg.slot_config[1].num_ranks != SPD_INVALID_RANK_COUNT)
    {
        // Slot 1 is populated so include its ranks.
        valid_ranks |= (0xF >> (DDR_MAX_RANKS_PER_SLOT - common_cfg.slot_config[1].num_ranks)) << DDR_MAX_RANKS_PER_SLOT;
    }

    /*
    valid_ranks = read32(mddr_base_addr + MDDR_DDR_RANK_AVAIL_OFFSET);

    if (valid_ranks == 0)
    {
        valid_ranks = 0x3;            // 2 ranks single slot0
        monaco_log(MEDIUM, "       *** NOTE:  DDR_RANK_AVAIL = 0, using sim value of  0x%8.8x\n", valid_ranks);
    }
    */

    return valid_ranks;
}


/*!****************************************************************************
*
* @par Description:
*    This function calculates and sets the rank control register
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*                                  @param
*    num_slots_populated    Number of slots populated in the given channel
*                                  @param
*    ddr_chan               DDR channel to perform function on.
*
* @return
*    None
*
* @author
*    anthonyf, lchavani
*
******************************************************************************/
unsigned mddr_mc_set_rank_cntl_reg(uint64_t mddr_base_addr, uint16_t num_slots_populated, uint8_t ddr_chan)
{
    unsigned status = COM_OK;
    uint32_t rank_avail;
    uint8_t dimm_slot;
    //spd_dimm_config_t *cfg_ptr;

    uint32_t all_ranks;
    uint8_t count;

    // Get the valid ranks for the memory controller.
    mddr_valid_ranks = mddr_mc_get_avail_ranks();

    //  Adjust rank values to account for combining of ranks for other register formatting where rank bits are combined.
    if(num_slots_populated == 2)
    {
        // Combine the 2 chip selects from the 1st slot with the 2 chip selects from 2nd slot.
        //  PHY only supports 4 chip selects so they have to be combined this way for specific
        //  MC register writes to align it with the PHY. Other rank related accesses including
        //  SI data follow nominal uncombined scheme.
        mddr_combined_valid_ranks = (mddr_valid_ranks & 0x3) | ((mddr_valid_ranks >> 0x2) & 0xC);
    }
    else
    {
        for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            if(mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                if (mddr_dimm_configs[ddr_chan][dimm_slot].num_ranks == DDR_RANKS_QUAD_CS_DIMM)
                {
                    mddr_combined_valid_ranks = 0x33;
                }
                else
                {
                    mddr_combined_valid_ranks = mddr_valid_ranks;
                }
            }
        }
    }

    // Check for 3DS
    all_ranks = mddr_combined_valid_ranks & 0x0F;
    count = 0x1;

    for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        if(mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            if((common_cfg.is_3DS) && (common_cfg.slot_config[dimm_slot].die_count > 1))
            {
                while(count < common_cfg.slot_config[dimm_slot].die_count)
                {
                    mddr_combined_valid_ranks |= (all_ranks << (count*4));
                    count++;
                }
            }
        }
    }

    // Get the ranks available
    rank_avail = mddr_get_reg(mddr_base_addr + MDDR_DDR_RANK_AVAIL_OFFSET, "DDR_RANK_AVAIL");

    // Compare the ranks available (configured earlier) with the ranks calculated
    if ((rank_avail == 0x0) && (platform_mode != SILICON))
    {
        monaco_log(HIGH, "WARNING: DDR_RANK_AVAIL = 0x0, using calculated value to set MDDR_RANK_EN_CNTL\n");
    }
    else if (rank_avail != mddr_combined_valid_ranks)
    {
        monaco_log(CRITICAL, "ERROR: DDR_RANK_AVAIL does not match calculated value\n");
        mddr_combined_valid_ranks = rank_avail;

        status = COM_ERROR;
    }

    // Enable all valid ranks.
    mddr_set_reg(mddr_base_addr + MDDR_RANK_EN_CNTL_OFFSET,     "RANK_EN_CNTL",     mddr_combined_valid_ranks);

    return status;

}


/*!****************************************************************************
*
* @par Description:
*    This function sets the slot config and addr registers in a DDR memory
*    controller for the given slot.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*                                  @param
*    slot                   The controller slot being targeted.
*                                  @param
*    dimm_slot_config_val   The value to store into the slot config register.
*                                  @param
*    dimm_slot_addr_val     The value to store into the slot address register.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_set_dimm_slot_regs
(
    uint64_t mddr_base_addr,
    uint8_t  slot,
    uint32_t dimm_slot_config_val,
    uint32_t dimm_slot_addr_val
)
{

    if (slot == 0)
    {
        // slot 0
        mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT0_CONFIG_OFFSET, "DIMM_SLOT0_CONFIG", dimm_slot_config_val);
        mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT0_ADDR_OFFSET, "DIMM_SLOT0_ADDR", dimm_slot_addr_val);
    }
    else
    {
        // slot 1
        mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT1_CONFIG_OFFSET, "DIMM_SLOT1_CONFIG", dimm_slot_config_val);
        mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT1_ADDR_OFFSET, "DIMM_SLOT1_ADDR", dimm_slot_addr_val);
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function disables unused clocks.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*
*
* @return
*    None
*
* @author
*    lchavani
*
******************************************************************************/
void mddr_mc_disable_unused_clocks(uint64_t mddr_base_addr)
{
    uint8_t ck_sel;
    uint8_t ck_off = 0x1;
    uint32_t manual_cke_val;

    ck_sel = common_cfg.slots_ck_sel;

    manual_cke_val  = ((~ck_sel) & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;
    manual_cke_val |= ck_off << MANUAL_CKE_CK_OFF___S;

    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);

}


/*!****************************************************************************
*
* @par Description:
*    This function asserts reset, disable CKE, turn on clocks, unfence PHY as
*     the first step described in the HPG POR sequence.
*
*                                  @param
*    mddr_base_addr          The base address of the configuration registers for
*                           the memory controller.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    This is supposed to come up by default and may be unnecessary.
*
******************************************************************************/
void mddr_mc_assert_reset(uint64_t mddr_base_addr)
{
    uint8_t ck_sel;
    uint8_t cke_sel;
    uint32_t manual_cke_val;
    uint32_t manual_cke_val1;


    ck_sel = common_cfg.slots_ck_sel;
    cke_sel = common_cfg.slots_cke_sel;

    // 1. assert reset, enable CK, disable CKE's

    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;

    if (cke_sel != ck_sel)
    {
        manual_cke_val1  = (ck_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;
        manual_cke_val1 |= 0x1 << MANUAL_CKE_CK_ON___S;

        mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val1);
    }
    else
    {
        manual_cke_val |= 0x1 << MANUAL_CKE_CK_ON___S;
    }

    manual_cke_val |= 0x1 << MANUAL_CKE_RESET_ON___S;
    manual_cke_val |= 0x1 << MANUAL_CKE_CKE_OFF___S;

    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);


    // Note clocks not running to DDR bus till after PHY_INIT
}



/*!****************************************************************************
*
* @par Description:
*    This function sets clocks and deassert reset.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    - All populated DDR channels are filled in a uniform fashion and so each
*      channel has the same slots populated.
*
******************************************************************************/
void mddr_mc_enable_clocks
(
    uint64_t mddr_base_addr
)
{
    uint8_t cke_sel;
//    uint8_t ck_sel;

    uint32_t manual_cke_val;
    uint32_t dev_state_mask;
    uint32_t exp_dev_state_val;

    uint32_t txpr;
    uint32_t txpr_5clk_ns;


    cke_sel = common_cfg.slots_cke_sel;
//    ck_sel = common_cfg.slots_ck_sel;


    // 2. wait 200us
    mddr_mc_wait_us(mddr_base_addr, 200);


    // 3. Start clocks
    //      select CKE clock groups
    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;   // use cke_sel for now
    //    manual_cke_val = (ck_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;


    //      deassert reset
    manual_cke_val |= 0x1 << MANUAL_CKE_RESET_OFF___S;
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);


    // wait for reset deassert
    dev_state_mask = cke_sel << DEVICE_STATE_RESET_IS_ON___S;
    exp_dev_state_val = 0x0;
    mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, dev_state_mask, exp_dev_state_val, 30);


    // 4. wait 500us
    mddr_mc_wait_us(mddr_base_addr, 500);


    // 5. Enable CKE
    //      select CKE
    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;

    //      turn CKE on
    manual_cke_val |= 0x1 << MANUAL_CKE_CKE_ON___S;
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);


    // wait for CKE ON
    dev_state_mask = DEVICE_STATE_CKE_IS_ON___M << DEVICE_STATE_CKE_IS_ON___S;
    exp_dev_state_val = cke_sel << DEVICE_STATE_CKE_IS_ON___S;
    mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, dev_state_mask, exp_dev_state_val, 10);


    // convert txs_clk to ns
    txpr = com_ceil_div(mddr_timing_vals.txs_clk * mem_freq_ps, PICO_SEC_PER_NANO_SEC);

    // convert 5clk to ns
    txpr_5clk_ns = com_ceil_div(5 * mem_freq_ps, PICO_SEC_PER_NANO_SEC);

    // Wait tXPR max(5nCK, tXS)
    txpr = COM_MAX(txpr, txpr_5clk_ns);
    mddr_mc_wait_ns(mddr_base_addr, txpr);
}



/*!****************************************************************************
*
* @par Description:
*    This function sets clocks and deassert reset without waiting for cke on.
*    This is used in watchdog reset re-initialization since the DDR is not
*    active and so cannot indicate CKE on but the memory controller needs to
*    be configured to align with the evenual state of the DDR.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    - All populated DDR channels are filled in a uniform fashion and so each
*      channel has the same slots populated.
*
******************************************************************************/
void mddr_mc_wd_enable_clocks
(
    uint64_t mddr_base_addr
)
{
    uint8_t cke_sel;
//    uint8_t ck_sel;

    uint32_t manual_cke_val;
    uint32_t dev_state_mask;
    uint32_t exp_dev_state_val;


    cke_sel = common_cfg.slots_cke_sel;
//    ck_sel = common_cfg.slots_ck_sel;


    //  Start clocks
    //      select CKE clock groups
    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;   // use cke_sel for now
    //    manual_cke_val = (ck_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;

    //  wait 200us
    mddr_mc_wait_us(mddr_base_addr, 200);


    //      deassert reset
    manual_cke_val |= 0x1 << MANUAL_CKE_RESET_OFF___S;
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);


    // wait for reset deassert
    dev_state_mask = cke_sel << DEVICE_STATE_RESET_IS_ON___S;
    exp_dev_state_val = 0x0;
    mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, dev_state_mask, exp_dev_state_val, 30);


    //  wait 500us
    mddr_mc_wait_us(mddr_base_addr, 500);


    // Enable CKE
    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;

    //      turn CKE on
    manual_cke_val |= 0x1 << MANUAL_CKE_CKE_ON___S;
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);
}


/*!****************************************************************************
*
* @par Description:
*    This function initializes the DIMM by doing the he mode register writes
*    and, for an RDIMM, the register control word writes.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    slot               The DIMM slot in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    Each rank has an independent set of mode register values. MR fields per
*    tables in 3.4.2 of JEDEC Standard No. 79-3F
*
******************************************************************************/
void mddr_mc_build_dimm_init(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan, uint8_t slot)
{
    uint8_t ranks;
    uint8_t rank_num;
    uint32_t rank_indicator;


    // Access only the ranks for the given slot / DIMM.
    //  Uses the uncombined ranks to access the correct rank specific data
    if (slot == 0)
    {
        ranks = mddr_valid_ranks & MDDR_SLOT0_RANK_MASK;
    }
    else
    {
        ranks = mddr_valid_ranks & MDDR_SLOT1_RANK_MASK;
    }


    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR3)
    {
        // Build the register control words
        mddr_mc_build_ddr3_rcw(ddr_chan, slot);

        for(rank_num = 0; rank_num < DDR_MAX_RANKS_PER_CHAN; ++rank_num)
        {
            // Extract the mode register rank indicator for the target rank.
            rank_indicator = ranks & (0x1 << rank_num);

            // Don't bother with unused ranks.
            if(rank_indicator != 0)
            {
                // Get the MR values for the rank
                mddr_mc_build_ddr3_mr(mddr_settings_ptr, ddr_chan, slot, rank_num);
            }
        }
    }
    else
    {
        if (common_cfg.mod_type != SPD_MODULE_TYPE_UDIMM)
        {
            // Build the register control words
            mddr_mc_build_ddr4_rcw(mddr_settings_ptr, ddr_chan, slot);

            if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
            {
                mddr_mc_build_ddr4_db(ddr_chan, slot);
            }
        }

        for(rank_num = 0; rank_num < DDR_MAX_RANKS_PER_CHAN; ++rank_num)
        {
            // Extract the mode register rank indicator for the target rank.
            rank_indicator = ranks & (0x1 << rank_num);

            // Don't bother with unused ranks.
            if(rank_indicator != 0)
            {
                // Get the MR values for the rank
                mddr_mc_build_ddr4_mr(mddr_settings_ptr, ddr_chan, slot, rank_num);
            }
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function initializes the DIMM by doing the he mode register writes
*    and, for an RDIMM, the register control word writes.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    slot               The DIMM slot in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    Each rank has an independent set of mode register values. MR fields per
*    tables in 3.4.2 of JEDEC Standard No. 79-3F
*
******************************************************************************/
void mddr_mc_exec_dimm_init(uint8_t ddr_chan, uint8_t slot)
{
    uint64_t mddr_base_addr;
    uint8_t ranks;
    uint8_t extract_shift;
    uint8_t rank_num;
    uint8_t rank_indicator;
    uint8_t combined_rank_indicator;
#if 0
    uint32_t tDLLK_delay_us;
#endif

    mddr_base_addr = mddr_base_addrs[ddr_chan];

    // Access only the ranks for the given slot / DIMM.
    if (slot == 0)
    {
        ranks = mddr_valid_ranks & MDDR_SLOT0_RANK_MASK;
        extract_shift = 0;
    }
    else
    {
        ranks = mddr_valid_ranks & MDDR_SLOT1_RANK_MASK;
        extract_shift = 2;
    }

    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR3)
    {

        if (common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM)
        {
            // Set the register control words
            mddr_mc_exec_ddr3_rcw(mddr_base_addr, ddr_chan, slot);
        }


        for(rank_num = 0; rank_num < DDR_MAX_RANKS_PER_CHAN; ++rank_num)
        {
            // Extract the rank indicator for the target rank.
            rank_indicator = ranks & (0x1 << rank_num);

            // Don't access nonexistant ranks.
            if(rank_indicator != 0)
            {
                if(common_cfg.slot_config[slot].num_ranks == DDR_RANKS_QUAD_CS_DIMM)
                {
                    combined_rank_indicator = 0x33;
                }
                else
                {
                    // mode register rank indicator is from the combined ranks
                    combined_rank_indicator = rank_indicator >> extract_shift;
                }

                mddr_mc_exec_ddr3_mr(mddr_base_addr, ddr_chan, rank_num, combined_rank_indicator);
            }
        }

    }
    else
    {
        if (common_cfg.mod_type != SPD_MODULE_TYPE_UDIMM)
        {
            // Set the register control words
            mddr_mc_exec_ddr4_rcw(mddr_base_addr, ddr_chan, slot);
        }


        for(rank_num = 0; rank_num < DDR_MAX_RANKS_PER_CHAN; ++rank_num)
        {
            // Extract the rank indicator for the target rank.
            rank_indicator = ranks & (0x1 << rank_num);

            // Don't access nonexistant ranks.
            if(rank_indicator != 0)
            {
                if(common_cfg.slot_config[slot].num_ranks == DDR_RANKS_QUAD_CS_DIMM)
                {
                    combined_rank_indicator = 0x33;
                }
                else
                {
                    // mode register rank indicator is from the combined ranks
                    combined_rank_indicator = rank_indicator >> extract_shift;
                }

                mddr_mc_exec_ddr4_mr(mddr_base_addr, ddr_chan, rank_num, combined_rank_indicator);
            }
        }
    }

    if(common_cfg.slot_config[slot].num_ranks == DDR_RANKS_QUAD_CS_DIMM)
    {
        ranks = 0x33;
    }
    else
    {
        // mode register rank indicator is from the combined ranks
        ranks = ranks >> extract_shift;
    }

    // Do initial ZQcal for the ranks of the given slot. Uses the combined ranks
    //  to adjust to the PHY limit of 4 ranks per channel.
    mddr_mc_zqcal(mddr_base_addr, ranks, ZQ_INIT);

    // Wait tDLLK = 512 clocks
    mddr_mc_set_hw_timer(mddr_base_addr, 512, false);

#if 0
    // Wait tDLLK = 512 clocks
    tDLLK_delay_us = com_ceil_div(512 * mem_freq_ps, PICO_SEC_PER_MICRO_SEC);
    mddr_mc_wait_us(mddr_base_addr, tDLLK_delay_us);
#endif
}


/*!****************************************************************************
*
* @par Description:
*    This function builds the register control words for DDR3 RDIMM.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    slot               The DIMM slot in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_build_ddr3_rcw(uint8_t ddr_chan, uint8_t slot)
{
    //     Building of the register control words is not necessary since
    //      they are taken from the SPD but it still needs to be made available.
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 = common_cfg.slot_config[slot].rcw0f_00;
}



/*!****************************************************************************
*
* @par Description:
*    This function builds the register control words for DDR4 RDIMM and LRDIMM.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    slot               The DIMM slot in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_build_ddr4_rcw(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan, uint8_t slot)
{
    uint64_t out_drv_ck_y13;
    uint64_t out_drv_ck_y02;
    uint64_t out_drv_ctl_cke;
    uint64_t out_drv_ctl_odt;
    uint64_t out_drv_ctl_ca;
    uint64_t out_drv_ctl_cs;
    uint64_t io_config = 0x0;
    uint64_t power_saving = 0x0;
    uint64_t rdimm_op_speed = 0x0;
    uint64_t dimm_config = 0x0;         // dualCS
    uint64_t parity_ctrl_word = 0x0;    // disable parity checking
    uint64_t cmd_lat_adder = 0x0;       // latency=+1 cycle to QCA, 0 to QPAR
    uint64_t fg_op_speed = 0x0;
    uint64_t input_bus_term = 0x0;
    uint16_t ibt_val = 0x0;
    uint8_t ibt_sel=0;
    uint8_t enc_ohms;

    // LRDIMM related
    uint64_t db_id_ctrl = 0x0;
    uint64_t lrdm_db_drv_ck_bcom_bodt_bcke = 0x0;
    uint64_t lrdm_db_drv_ck_bck = 0x0;


    //   RC03, CA and CS signals driver characteristics
    //   RC04, ODT and CKE signals driver characteristics
    //   RC05, clock driver characteristics
    out_drv_ctl_ca = common_cfg.slot_config[slot].out_drv_ctl_ca;
    out_drv_ctl_cs = common_cfg.slot_config[slot].out_drv_ctl_cs;
    out_drv_ctl_odt = common_cfg.slot_config[slot].out_drv_ctl_odt;
    out_drv_ctl_cke = common_cfg.slot_config[slot].out_drv_ctl_cke;
    out_drv_ck_y02 = common_cfg.slot_config[slot].out_drv_ck_y02;
    out_drv_ck_y13 = common_cfg.slot_config[slot].out_drv_ck_y13;


    //
    //   RC08, input/output configuration
    //
    if (!common_cfg.is_3DS)
    {
        // for quad rank DIMMs need C1, C0
        if (common_cfg.slot_config[slot].num_ranks == 4)
        {
            io_config |= 0x1;   // QxC[1:0] enabled, QxC2 disabled
        }
        else
        {
            io_config |= 0x3;   // disable QxC[2:0]
        }
    }
    else if (common_cfg.slot_config[slot].die_count != 8)
    {
        if (common_cfg.slot_config[slot].die_count == 2)
        {
            if (common_cfg.slot_config[slot].num_ranks != 4)
            {
                io_config |= 0x2;   // QxC[2:1] disabled, QxC0 enabled
            }
            // else for Quad-CS mode need C1 & C0 for CS and
            // C2 to select stack (val=0; QxC[2:0] outputs enabled)
        }
        else if (common_cfg.slot_config[slot].die_count == 4)
        {
            io_config |= 0x1;   // QxC[1:0] enabled, QxC2 disabled
        }
    }

    if ((mddr_settings_ptr->ca_parity == CA_PARITY_DISABLE) ||
        (mddr_settings_ptr->ca_parity == CA_PARITY_DIMM))
    {
        io_config |= 0x4;    //disable QPAR output
    }

    if (common_cfg.slot_config[slot].num_rows != SPD_MAX_ROWS)
    {
        io_config |= 0x8;
    }


    //
    //   RC09, power saving settings
    //
    if (common_cfg.slot_config[slot].num_ranks == 1)
    {
        power_saving |= 0xB;
    }
    else
    {
        power_saving |= 0x8;  // enable
    }


    //
    //   RC0A, RDIMM operating speed
    //
    if (ddr_rate <= 1600)
    {
        rdimm_op_speed = 0;
    }
    else if (ddr_rate <= 1866)
    {
        rdimm_op_speed = 1;
    }
    else if (ddr_rate <= 2133)
    {
        rdimm_op_speed = 2;
    }
    else if (ddr_rate <= 2400)
    {
        rdimm_op_speed = 3;
    }
    else if (ddr_rate <= 2666)
    {
        rdimm_op_speed = 4;
    }
    else
    {
        rdimm_op_speed = 5;
    }


    //
    //   RC0D, DIMM configuration
    //

    // 0=direct dualCS. 1=direct quadCS. 3=encoded quadCS which is not supported.
    if (common_cfg.slot_config[slot].num_ranks == DDR_RANKS_QUAD_CS_DIMM)
    {
        dimm_config |= 0x1;      // direct quad  (CS0,CS1,CS2[C0],CS3[C1])
    }

    // For RDIMM, LRDIMM DA2 = 0
    if (common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM)
    {
        dimm_config |= 0x4;
    }

    if (common_cfg.slot_config[slot].ca_mirrored)
    {
        dimm_config |= 0x8;
    }



    //
    //   RC0E, parity control word
    //
    if ((mddr_settings_ptr->ca_parity != CA_PARITY_DISABLE) &&
        (mddr_settings_ptr->ca_parity != CA_PARITY_DRAM))
    {
        parity_ctrl_word = 1;      // either DRAM or DIMM parity
    }


    //
    //   RC0F, command latency adder
    //
    // latency=+1 cycle by default
    if (ddr_rate > 2400)
    {
        cmd_lat_adder = 0x1;   // latency=+2 cycles to QCA, +1 to QPAR
    }



    // Build the rcw0f_00 register control word from the SPD values.
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00  = out_drv_ctl_ca << DDR4_RCW_CK_CTL_CA___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= out_drv_ctl_cs << DDR4_RCW_CK_CTL_CS___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= out_drv_ctl_odt << DDR4_RCW_CK_CTL_ODT___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= out_drv_ctl_cke << DDR4_RCW_CK_CTL_CKE___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= out_drv_ck_y02 << DDR4_RCW_CK_Y02___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= out_drv_ck_y13 << DDR4_RCW_CK_Y13___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= io_config << DDR4_RCW_IO_CONFIG___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= power_saving << DDR4_RCW_POWER_SAVING___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= rdimm_op_speed << DDR4_RCW_RDIMM_OP_SPEED___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= dimm_config << DDR4_RCW_DIMM_CONFIG___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= parity_ctrl_word << DDR4_RCW_PARITY_CTRL_WORD___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00 |= cmd_lat_adder << DDR4_RCW_CMD_LAT_ADDER___S;


    //
    // RC3x, fine granularity RDIMM operating speed
    //
    if (ddr_rate <= 1260)
    {
        fg_op_speed = 0x0;
    }
    else if (ddr_rate > 3180)
    {
        fg_op_speed = 0x61;
    }
    else
    {
        fg_op_speed = com_ceil_div((ddr_rate - 1260), 20);
    }

    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw7x_0x  = fg_op_speed << DDR4_RCW_CMD_FG_OP_SPEED___S;

    //
    // RC7x, input bus termination
    //
    // Build the rcw7x_0x register control word.

    while (ibt_sel < 4)
    {
        ibt_val = si_data[ddr_chan].dimm_si[slot].ibt[ibt_sel];

        if (ibt_val == 150)
            enc_ohms = 1;
        else if (ibt_val == 300)
            enc_ohms = 2;
        else if (ibt_val == 0)
            enc_ohms = 3;
        else                // ibt_val = 100
            enc_ohms = 0;

        input_bus_term |= (uint64_t)(enc_ohms << (2 * ibt_sel));

        ibt_sel += 1;
    }

    mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw7x_0x |= input_bus_term << DDR4_RCW_CMD_INPUT_BUS_TERM_LAT___S;

    //
    // F1RC00, Data buffer interface driver controls
    //
    lrdm_db_drv_ck_bcom_bodt_bcke = common_cfg.slot_config[slot].lrdm_db_drv_ck_bcom_bodt_bcke;
    lrdm_db_drv_ck_bck = common_cfg.slot_config[slot].lrdm_db_drv_ck_bck;

    if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
    {
        db_id_ctrl = lrdm_db_drv_ck_bcom_bodt_bcke << DDR4_RCW_CK_BCOM_BODT_BCKE___S;    // bcom, bodt, bcke (0=med, 1=strong)
        db_id_ctrl |= lrdm_db_drv_ck_bck << DDR4_RCW_CK_BCK___S;    // bck

    }

    // Build the f1rc00_f0rcbx_8x register control word.
    mddr_reg_vals.rcw_regs[ddr_chan][slot].f1rc00_f0rcbx_8x = db_id_ctrl;
}


/*!****************************************************************************
*
* @par Description:
*    This function builds the data buffer control words for DDR4 LRDIMM.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    slot               The DIMM slot in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    lchavani
*
******************************************************************************/
void mddr_mc_build_ddr4_db(uint8_t ddr_chan, uint8_t slot)
{
    uint64_t host_dq_rtt_nom = 0x0;
    uint64_t host_dq_rtt_wr = 0x0;
    uint64_t host_dq_rtt_park = 0x0;
    uint64_t host_dq_ron = 0x0;
    uint64_t dram_db_mdq_term = 0x0;
    uint64_t dram_db_mdq_ron = 0x0;
    uint64_t cmd_spc_val = 0x0;
    uint64_t pkg_rank_dis = 0x0;
    uint64_t cke_pwrdn_enable = 0x0;
    uint64_t lr_op_speed = 0x0;
    uint64_t fg_lr_op_speed = 0x0;
    uint64_t host_db_vref = 0x0;
    uint64_t host_db_vref_range = 0x0;
    uint64_t dram_db_mdq_vref = 0x0;
    uint64_t dram_db_mdq_vref_range = 0x0;
    uint64_t mdq_vref_range_val = 0x0;

    uint8_t freq_idx = 0x0;

    // Get the frequency index (for LRDIMM SI) based on
    // the current DDR operating speed
    if (ddr_rate <= 1866)
    {
        freq_idx = 0x0;
    }
    else if (ddr_rate <= 2400)
    {
        freq_idx = 0x1;
    }
    else    // <= 3200
    {
        freq_idx = 0x2;
    }

    //----------------------------------------------------------------------
    // BC00, Host Interface DQ RTT_NOM termination
    host_dq_rtt_nom = lr_db_si_data[ddr_chan].lr_host_db_si[slot].lr_host_db_rtt_nom;

    if (host_dq_rtt_nom == 0)
    {
        host_dq_rtt_nom = 0x0;
    }
    else if (host_dq_rtt_nom == 60)
    {
        host_dq_rtt_nom = 0x1;
    }
    else if (host_dq_rtt_nom == 120)
    {
        host_dq_rtt_nom = 0x2;
    }
    else if (host_dq_rtt_nom == 40)
    {
        host_dq_rtt_nom = 0x3;
    }
    else if (host_dq_rtt_nom == 240)
    {
        host_dq_rtt_nom = 0x4;
    }
    else if (host_dq_rtt_nom == 48)
    {
        host_dq_rtt_nom = 0x5;
    }
    else if (host_dq_rtt_nom == 80)
    {
        host_dq_rtt_nom = 0x6;
    }
    else if (host_dq_rtt_nom == 34)
    {
        host_dq_rtt_nom = 0x7;
    }
    else
    {
        monaco_log(CRITICAL, "ERROR: Invalid value for rtt_nom = %d, setting to disabled\n", (uint8_t)host_dq_rtt_nom);
        host_dq_rtt_nom = 0x0;
    }

    //--------------------------------------------------------------------
    // BC01, Host Interface DQ RTT_WR termination
    host_dq_rtt_wr = lr_db_si_data[ddr_chan].lr_host_db_si[slot].lr_host_db_rtt_wr;

    if (host_dq_rtt_wr == 0)
    {
        host_dq_rtt_wr = 0x0;
    }
    else if (host_dq_rtt_wr == 60)
    {
        host_dq_rtt_wr = 0x1;
    }
    else if (host_dq_rtt_wr == 120)
    {
        host_dq_rtt_wr = 0x2;
    }
    else if (host_dq_rtt_wr == 240)
    {
        host_dq_rtt_wr = 0x4;
    }
    else if (host_dq_rtt_wr == 80)
    {
        host_dq_rtt_wr = 0x6;
    }
    else if (host_dq_rtt_wr == 1)
    {
        host_dq_rtt_wr = 0x7;
    }
    else
    {
        monaco_log(CRITICAL, "ERROR: Invalid value for rtt_wr = %d, setting to 80\n", (uint8_t)host_dq_rtt_wr);
        host_dq_rtt_wr = 0x6;
    }

    //----------------------------------------------------------------------
    // BC02, Host Interface DQ RTT_PARK termination
    host_dq_rtt_park = lr_db_si_data[ddr_chan].lr_host_db_si[slot].lr_host_db_rtt_park;

    if (host_dq_rtt_park == 0)
    {
        host_dq_rtt_park = 0x0;
    }
    else if (host_dq_rtt_park == 60)
    {
        host_dq_rtt_park = 0x1;
    }
    else if (host_dq_rtt_park == 120)
    {
        host_dq_rtt_park = 0x2;
    }
    else if (host_dq_rtt_park == 40)
    {
        host_dq_rtt_park = 0x3;
    }
    else if (host_dq_rtt_park == 240)
    {
        host_dq_rtt_park = 0x4;
    }
    else if (host_dq_rtt_park == 48)
    {
        host_dq_rtt_park = 0x5;
    }
    else if (host_dq_rtt_park == 80)
    {
        host_dq_rtt_park = 0x6;
    }
    else if (host_dq_rtt_park == 34)
    {
        host_dq_rtt_park = 0x7;
    }
    else
    {
        monaco_log(CRITICAL, "ERROR: Invalid value for rtt_park = %d, setting to 240\n", (uint8_t)host_dq_rtt_park);
        host_dq_rtt_park = 0x4;
    }

    //----------------------------------------------------------------------
    // BC03, Host Interface DQ Driver
    host_dq_ron = lr_db_si_data[ddr_chan].lr_host_db_si[slot].lr_host_db_ron;

    if (host_dq_ron == 40)
    {
        host_dq_ron = 0x0;
    }
    else if (host_dq_ron == 34)
    {
        host_dq_ron = 0x1;
    }
    else if (host_dq_ron == 48)
    {
        host_dq_ron = 0x2;
    }
    else if (host_dq_ron == 30)
    {
        host_dq_ron = 0x3;
    }
    else
    {
        monaco_log(CRITICAL, "ERROR: Invalid value for db to host drive strength = %d, setting to 34\n", (uint8_t)host_dq_ron);
        host_dq_ron = 0x1;
    }

    //----------------------------------------------------------------------
    // BC04, DRAM interface MDQ termination
    dram_db_mdq_term = lr_db_si_data[ddr_chan].lr_spd_db_si[slot].lr_spd_db_mdq_term[freq_idx];

    //----------------------------------------------------------------------
    // BC05, DRAM interface MDQ driver
    dram_db_mdq_ron = lr_db_si_data[ddr_chan].lr_spd_db_si[slot].lr_spd_db_mdq_ron[freq_idx];

    //----------------------------------------------------------------------
    // BC06, command space
    // reset clock DLL circuits, perform long I/O cal, perform short I/O cal, clear parity/seq error status, clear all internal registers
    cmd_spc_val = 0xF;

    //----------------------------------------------------------------------
    // BC07, rank presence (1 to disable)
    if (common_cfg.slot_config[slot].num_ranks > 3)
    {
        pkg_rank_dis = 0x0;
    }
    else if (common_cfg.slot_config[slot].num_ranks > 1)
    {
        pkg_rank_dis = 0xC;
    }
    else
    {
        pkg_rank_dis = 0xE;
    }

    //----------------------------------------------------------------------
    // BC09 - power saving settings
    cke_pwrdn_enable = 0x8;

    //----------------------------------------------------------------------
    // BC0A, LRDIMM operating speed
    if (ddr_rate <= 1600)
    {
        lr_op_speed = 0x0;
    }
    else if (ddr_rate <= 1866)
    {
        lr_op_speed = 0x1;
    }
    else if (ddr_rate <= 2133)
    {
        lr_op_speed = 0x2;
    }
    else if (ddr_rate <= 2400)
    {
        lr_op_speed = 0x3;
    }
    else if (ddr_rate <= 2666)
    {
        lr_op_speed = 0x4;
    }
    else if (ddr_rate <= 2933)
    {
        lr_op_speed = 0x5;
    }
    else
    {
        lr_op_speed = 0x6;
    }

    //===============================================================
    // f0BC6x, fine granularity LRDIMM operating speed
    if (ddr_rate <= 1260)
    {
        fg_lr_op_speed = 0x0;
    }
    else if (ddr_rate > 3180)
    {
        fg_lr_op_speed = 0x61;
    }
    else
    {
        fg_lr_op_speed = com_ceil_div((ddr_rate - 1260), 20);
    }

    //===============================================================
    // F5BC5x, Host interface VREF
    host_db_vref = lr_db_si_data[ddr_chan].lr_host_db_si[slot].lr_host_db_vrefdq;

    host_db_vref_range = mddr_mc_get_vref_range(host_db_vref);

    if (host_db_vref_range == 0)
    {
        host_db_vref = com_ceil_div((host_db_vref - 6000), 65);
    }
    else
    {
        host_db_vref = com_ceil_div((host_db_vref - 4500), 65);
    }

    //===============================================================
    // F5BC6x, DRAM interface VREF
    dram_db_mdq_vref = lr_db_si_data[ddr_chan].lr_spd_db_si[slot].lr_spd_db_mdq_vrefdq;

    //================================================================
    // F6BC4x   Vref range - DB mdq vrefdq range
    dram_db_mdq_vref_range = lr_db_si_data[ddr_chan].lr_spd_db_si[slot].lr_spd_db_mdq_vrefdq_range;

    if ((host_db_vref_range == 1) || (dram_db_mdq_vref_range == 1))
    {
        mdq_vref_range_val  = host_db_vref_range << 1;
        mdq_vref_range_val |= dram_db_mdq_vref_range << 2;
    }


    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00   = host_dq_rtt_nom << DDR4_LR_RCW_HOST_DQ_RTT_NOM___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= host_dq_rtt_wr << DDR4_LR_RCW_HOST_DQ_RTT_WR___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= host_dq_rtt_park << DDR4_LR_RCW_HOST_DQ_RTT_PARK___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= host_dq_ron << DDR4_LR_RCW_HOST_DQ_RON___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= dram_db_mdq_term << DDR4_LR_RCW_DRAM_DB_MDQ_TERM___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= dram_db_mdq_ron << DDR4_LR_RCW_DRAM_DB_MDQ_RON___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= cmd_spc_val << DDR4_LR_RCW_CMD_SPACE___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= pkg_rank_dis << DDR4_LR_RCW_RANK_PRESENCE___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= cke_pwrdn_enable << DDR4_LR_RCW_PWR_SAV_SETTINGS___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].bc0f_00  |= lr_op_speed << DDR4_LR_RCW_OP_SPEED___S;

    mddr_reg_vals.rcw_regs[ddr_chan][slot].f5bc6x_5x_f0bc6x  = fg_lr_op_speed << DDR4_LR_RCW_FG_OP_SPEED___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].f5bc6x_5x_f0bc6x |= host_db_vref << DDR4_LR_RCW_HOST_DB_VREF___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].f5bc6x_5x_f0bc6x |= dram_db_mdq_vref << DDR4_LR_RCW_DRAM_DB_VREF___S;
    mddr_reg_vals.rcw_regs[ddr_chan][slot].f5bc6x_5x_f0bc6x |= mdq_vref_range_val << DDR4_LR_RCW_DRAM_DB_MDQ_VREF_RNG___S;

}


/*!****************************************************************************
*
* @par Description:
*    This function builds the DDR3 mode register write values.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    slot               The DIMM slot in the DDR channel to target.
*                                  @param
*    rank_num           The rank number in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_build_ddr3_mr(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan, uint8_t slot, uint8_t rank_num)
{
    uint8_t slot_rank;

    // data = A15:A0
    uint16_t mr0_data;
    uint16_t mr1_data;
    uint16_t mr2_data;
    uint16_t mr3_data;

    uint16_t rtt_wr;
    uint16_t rtt_nom;
    uint8_t dimm_out_imp;
    uint16_t mr1_rtt_nom;
    uint16_t out_drv_imp;
    uint16_t mr1_disable_dll;
    uint16_t mr0_bl;
    uint16_t mr0_cl;
    uint16_t mr0_wr;
    uint16_t mr0_fast_exit;
    uint16_t mr0_dll_reset;

    uint32_t cl;


    // Get the relative rank within the slot
    slot_rank = rank_num % DDR_MAX_RANKS_PER_SLOT;


    rtt_wr = si_data[ddr_chan].dimm_si[slot].rank_si[slot_rank].rtt_wr;
    rtt_nom = si_data[ddr_chan].dimm_si[slot].rank_si[slot_rank].rtt_nom;
    dimm_out_imp = si_data[ddr_chan].dimm_si[slot].rank_si[slot_rank].ron;



    // if (mem_freq_ps >= 5000)    //check freq too? less than 200 MHz clock, assuming DLL off mode
    if (platform_mode != SILICON)
    {
        // special DLL off mode
        mr1_disable_dll = 1;
        mr0_fast_exit = 0;
        mr0_dll_reset = 0;
    }
    else                // real HW
    {

        mr1_disable_dll = 0;
        mr0_fast_exit = 1;
        mr0_dll_reset = 1;
    }


    //------------------------------------------------------------------------------------
    // build mode register 2
    // RTT_WR, SRT=0, ASR=0, CWL, PASR
    // &sim_mr2=0x0008     ; CWL=6, CWL=5 not available for DLL_off?
    // &reg_mr2=0x0018     ; rtt_wr=0, cwl

    mr2_data  = (latencies.mc_mr2_cwl & MR2_CWL___M) << MR2_CWL___S;    // set cwl
    mr2_data |= (rtt_wr & MR2_RTT_WR___M) << MR2_RTT_WR___S;              // set rtt_wr


    //------------------------------------------------------------------------------------
    // build mode register 3
    // MPR, MPR_location
    mr3_data = 0x0000;        // Normal operation, predefined pattern


    //------------------------------------------------------------------------------------
    // build mode register 1
    // Qoff, tDQS_en, RTT_NOM, WL_en, Out_drv_imp, AL, disable_DLL
    // &sim_mr1=0x0001      ; disable dll
    // &reg_mr1=0x0018      ; dll=on, rtt_nom, odic=40


    if (rtt_nom == 0)
    {
        mr1_rtt_nom = 0x0;
    }
    else if (rtt_nom == 60)
    {
        mr1_rtt_nom = 0x1;
    }
    else if (rtt_nom == 120)
    {
        mr1_rtt_nom = 0x10;
    }
    else if (rtt_nom == 40)
    {
        mr1_rtt_nom = 0x11;
    }
    else if (rtt_nom == 20)
    {
        mr1_rtt_nom = 0x80;
    }
    else if (rtt_nom == 30)
    {
        mr1_rtt_nom = 0x81;
    }
    else
    {
        mr1_rtt_nom = 0;
        monaco_log(HIGH, "ERROR processing rtt_nom = 0x%4.4x\n", rtt_nom);
    }


    if (dimm_out_imp == 40)
    {
        out_drv_imp = 0;
    }
    else if (dimm_out_imp == 34)
    {
        out_drv_imp = 1;
    }
    else
    {
        out_drv_imp = 0;
        monaco_log(HIGH, "ERROR processing DIMM_output_impedance = 0x%4.4x\n", dimm_out_imp);
    }


    // tDQS is always disabled since the memory controller doesn't support mixed of x4 & x8 in same channel
    mr1_data  = (mr1_rtt_nom & MR1_RTT_NOM_DDR3___M) << MR1_RTT_NOM_DDR3___S;
    mr1_data |= (out_drv_imp & MR1_ODIC_DDR3___M) << MR1_ODIC___S;
    mr1_data |= (mr1_disable_dll & MR1_DLL___M) << MR1_DLL___S;



    //------------------------------------------------------------------------------------
    // build mode register 0
    // FAST_EXIT, WR, Reset_DLL, Mode, CL, RD_TYPE, BL
    // sim_mr0=0x0220  ; Fast=OFF, nWR=5, DLL_reset=no, mode=normal, CL=6, Nibble seq, BL=8_FIXED

    if (mddr_settings_ptr->page_settings.burst_len_mode == DB_BURST_LEN_BL8)
    {
        mr0_bl = 0;
    }
    else if (mddr_settings_ptr->page_settings.burst_len_mode == DB_BURST_LEN_OTF)
    {
        mr0_bl = 1;
    }
    else
    {
        mr0_bl = 0;
        monaco_log(HIGH, "ERROR processing burst length, burst_len_mode = %d 0=OTF, using BL8\n",
                mddr_settings_ptr->page_settings.burst_len_mode);
    }


    cl = latencies.cl;

    if (cl < 5)
    {
        mr0_cl = 0x4;
        monaco_log(HIGH, "ERROR CAS latency is out of bounds, less than 5, CL = %d, using 5\n", cl);
    }
    else if (cl == 5)
    {
        mr0_cl = 0x4;
    }
    else if (cl == 6)
    {
        mr0_cl = 0x8;
    }
    else if (cl == 7)
    {
        mr0_cl = 0xC;
    }
    else if (cl == 8)
    {
        mr0_cl = 0x10;
    }
    else if (cl== 9)
    {
        mr0_cl = 0x14;
    }
    else if (cl == 10)
    {
        mr0_cl = 0x18;
    }
    else if (cl == 11)
    {
        mr0_cl = 0x1C;
    }
    else if (cl == 12)
    {
        mr0_cl = 0x1;
    }
    else if (cl == 13)
    {
        mr0_cl = 0x5;
    }
    else if (cl == 14)
    {
        mr0_cl = 0x9;
    }
    else
    {
        // (cl > 14)
        mr0_cl = 0x9;
        monaco_log(HIGH, "ERROR CAS latency is out of bounds, greater than 14, CL = %d, using 14\n", cl);
    }



    // Other tWR (clock cycles) is restricted to appropriate values by
    //  mddr_mc_build_timing_rdwr4_reg() during creation of the related field of the MC.
    if (mddr_timing_vals.mr_wr_clk <= 5)
    {
        mr0_wr = 1;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 6)
    {
        mr0_wr = 2;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 7)
    {
        mr0_wr = 3;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 8)
    {
        mr0_wr = 4;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 10)
    {
        mr0_wr = 5;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 12)
    {
        mr0_wr = 6;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 14)
    {
        mr0_wr = 7;
    }
    else // tWR clock cycles == 16
    {
        mr0_wr = 0;
    }


    mr0_data  = (mr0_bl & MR0_BL___M) << MR0_BL___S;
    mr0_data |= (mr0_cl & MR0_CL_DDR3___M) << MR0_CL_DDR3___S;
    mr0_data |= (mr0_dll_reset & MR0_DLL_RESET___M) << MR0_DLL_RESET___S;
    mr0_data |= (mr0_wr & MR0_WR_DDR3___M) << MR0_WR___S;
    mr0_data |= (mr0_fast_exit & MR0_FAST_EXIT___M) << MR0_FAST_EXIT___S;


    // The mode registers for a channel are targeted by rank accross both slots.
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr0_data = mr0_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr1_data = mr1_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr2_data = mr2_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr3_data = mr3_data;
}



/*!****************************************************************************
*
* @par Description:
*    This function builds the DDR4 mode register write values.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    slot               The DIMM slot in the DDR channel to target.
*                                  @param
*    rank_num           The rank number in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_build_ddr4_mr(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan, uint8_t slot, uint8_t rank_num)
{
    uint8_t slot_rank;

    uint16_t mr0_data;
    uint16_t mr1_data;
    uint16_t mr2_data;
    uint16_t mr3_data;
    uint16_t mr4_data;
    uint16_t mr5_data;
    uint16_t mr6_data;

    uint16_t rtt_wr;
    uint16_t rtt_nom;
    uint16_t rtt_park;
    uint8_t dimm_out_imp;
    mddr_ddr_dbi_t dbi_mode;
    uint32_t tdllkmin_clk;
    uint32_t tccdlmin_clk;
    uint8_t wr_cmd_lat;
    uint32_t vref;


    uint8_t mr6_tccdl;
    uint16_t mr6_value;
    uint8_t mr6_range;

    uint16_t mr5_rtt_park;
    uint16_t dbi_rd = 0x0;
    uint16_t dbi_wr = 0x0;
    uint16_t dm = 0x0;

    uint16_t wr_pre = 0x0;
    uint16_t rd_pre = 0x0;
    uint16_t sr_abort = 0x1;    // self refresh abort enable
    uint16_t temp_ref = 0x0;    // temp controlled refresh mode enable

    uint16_t mr2_rtt_wr;
    uint16_t mr2_lpasr_mode;

    uint16_t mr1_rtt_nom;
    uint16_t mr1_odic;
    uint16_t mr1_enable_dll;

    uint16_t mr0_bl;
    uint16_t mr0_cl;
    uint16_t mr0_dll_reset;
    uint16_t mr0_wr;

    uint32_t cl;


    // Get the relative rank within the slot
    slot_rank = rank_num % DDR_MAX_RANKS_PER_SLOT;

    rtt_park = si_data[ddr_chan].dimm_si[slot].rank_si[slot_rank].rtt_park;
    rtt_wr = si_data[ddr_chan].dimm_si[slot].rank_si[slot_rank].rtt_wr;
    rtt_nom = si_data[ddr_chan].dimm_si[slot].rank_si[slot_rank].rtt_nom;
    dimm_out_imp = si_data[ddr_chan].dimm_si[slot].rank_si[slot_rank].ron;
    vref = si_data[ddr_chan].dimm_si[slot].rank_si[slot_rank].vref[0];
    dbi_mode = mddr_settings_ptr->dbi_mode;
    tdllkmin_clk = mddr_timing_vals.tdllk_min_clk;
    tccdlmin_clk = mddr_timing_vals.tccdl_min_clk;


    //------------------------------------------------------------------------------------
    // build mode register 3
    // MPR read format, write cmd lat, fine gran refresh, temp sensor, per dram addr, geardown, mpr enable, mpr page sel.

    if (mem_freq_mhz <= 800)
    {
        wr_cmd_lat = 4;
    }
    else if (mem_freq_mhz <= 1200)
    {
        wr_cmd_lat = 5;
    }
    else
    {
        wr_cmd_lat = 6;
    }

    mr3_data = (mddr_settings_ptr->rfc_mode & MR3_FINE_GRAN___M) << MR3_FINE_GRAN___S;
    mr3_data |= (wr_cmd_lat & MR3_WR_CMD_LAT___M) << MR3_WR_CMD_LAT___S;


    //------------------------------------------------------------------------------------
    // build mode register 6
    // tCCD_l/tDLLK, VrefDQ Train, VrefDQ range, VrefDQ training value

    if (tccdlmin_clk > 8)
    {
        mr6_tccdl = 0x4;
    }
    else if (tccdlmin_clk < 4)
    {
        mr6_tccdl = 0x0;
    }
    else
    {
        mr6_tccdl = tccdlmin_clk - 4;
    }

    // check tDLLK
    if (tdllkmin_clk > 768)
    {
        if (tdllkmin_clk > 1024)
        {
            monaco_log(MEDIUM, "WARN: tDLLK is larger than 1024, tDLLK = %d\n", tdllkmin_clk);
        }

        if ( mr6_tccdl < 3)
        {
            monaco_log(MEDIUM, "WARN: tCCD_L (%d) < 7, and tDLLK (%d) > 768\n", tccdlmin_clk, tdllkmin_clk);
            //mr6_tccdl = 3;
        }
    }
    else if (tdllkmin_clk > 597)
    {
        if (mr6_tccdl < 2)
        {
            monaco_log(MEDIUM, "WARN: tCCD_L (%d) < 6, and tDLLK (%d) > 597\n", tccdlmin_clk, tdllkmin_clk);
            //mr6_tccdl = 6;
        }
    }

    mr6_range = mddr_mc_get_vref_range(vref);

    if (mr6_range == 1)
    {
        mr6_value = vref - 4500;
    }
    else
    {
        mr6_value = vref - 6000;
    }

    mr6_value = com_ceil_div(mr6_value, 65);

    if (mr6_value > MR6_VALUE_MAX)
    {
        monaco_log(HIGH, "ERROR: Vref value greater than MR6 field, value=&mr6_value, setting to max (%d)", MR6_VALUE_MAX);
        mr6_value = MR6_VALUE_MAX;
    }

    mr6_data = (mr6_tccdl & MR6_TCCDL___M) << MR6_TCCDL___S;
    mr6_data |= (mr6_range & MR6_RANGE___M) << MR6_RANGE___S;
    mr6_data |= (mr6_value & MR6_VALUE___M) << MR6_VALUE___S;

    if(mddr_settings_ptr->CA_margin_enabled)
        CA_margin_enabled = true;
    else
        CA_margin_enabled = false;

    //------------------------------------------------------------------------------------
    // build mode register 5
    // rDBI, wDBI, DM, parity persist, RTT_PARK, ODT in PD, parity error status, CRC clear, CA PL

// Do we need this?
    if (rtt_park == 0)         // RZQ/4
    {
        mr5_rtt_park = 0x0;
    }
    else if (rtt_park == 60)   // RZQ/4
    {
        mr5_rtt_park = 0x1;
    }
    else if (rtt_park == 120)   // RZQ/2
    {
        mr5_rtt_park = 0x2;
    }
    else if (rtt_park == 40)    // RZQ/6
    {
        mr5_rtt_park = 0x3;
    }
    else if (rtt_park == 240)   // RZQ/1
    {
        mr5_rtt_park = 0x4;
    }
    else if (rtt_park == 48)    // RZQ/5
    {
        mr5_rtt_park = 0x5;
    }
    else if (rtt_park == 80)   // RZQ/3
    {
        mr5_rtt_park = 0x6;
    }
    else if (rtt_park == 34)   // RZQ/7
    {
        mr5_rtt_park = 0x7;
    }
    else
    {
        mr5_rtt_park = 0x0;
        monaco_log(HIGH, "Warning rtt_park is a unsupported value! Defaulting mr5_rtt_park to 0x%x\n", mr5_rtt_park);
    }


    // for dbi / dm, priority goes to WR_DBI >> DM
    if (common_cfg.sdram_width == SPD_SDRAM_WIDTH_X8)      // dbi & dm only valid if x8
    {
        // read DBI valid with or without ECC
        if((dbi_mode == DDR_DBI_READ) || (dbi_mode == DDR_DBI_READ_WRITE))
        {
            dbi_rd = 0x1;
        }

        if((dbi_mode == DDR_DBI_WRITE) || (dbi_mode == DDR_DBI_READ_WRITE))
        {
            dbi_wr = 0x1;
        }
        else
        {
            if ((!common_cfg.has_ecc)||(mddr_settings_ptr->disable_ecc))
            {
                // no ECC
                dm = 0x1;
            }
        }
    }


    mr5_data = 0x0;       // CA parity persist disable, ODT in PD active, CA parity clear, CRC clear
    mr5_data |= dbi_rd << MR5_RD_DBI___S;
    mr5_data |= dbi_wr << MR5_WR_DBI___S;
    mr5_data |= dm << MR5_DM___S;
    mr5_data |= mr5_rtt_park << MR5_RTT_PARK___S;
    mr5_data |= (latencies.mc_mr5_pl & MR5_CA_PL___M);



    //------------------------------------------------------------------------------------
    // build mode register 4
    // ppr, wr_preamble, rd_preamble, rd_pre_train, SR_abort, tCAL, VrefDQ_mon, temp_ref_mode, temp_ref_range, max_pd

    if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
       (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
    {
        wr_pre = 0x1;
    }

    if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_READ) ||
       (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
    {
        rd_pre = 0x1;
    }

    // temperature controlled refresh must be disabled if using fine grain refresh
    if (mddr_settings_ptr->rfc_mode != DDR_REFRESH_1X)
    {
        temp_ref = 0x0;
    }

    mr4_data = 0x0;
    mr4_data |= sr_abort << MR4_SR_ABORT___S;
    mr4_data |= temp_ref << MR4_TEMP_REF___S;
    mr4_data |= rd_pre << MR4_RD_PRE___S;
    mr4_data |= wr_pre << MR4_WR_PRE___S;


    //------------------------------------------------------------------------------------
    // build mode register 2
    // trr, wr_crc, rtt_wr, trr_mode_bg, asr, cwl, trr_mode_ba
    // A13,  A12,  A11:9,   A8,A2,      A7:6, A5:3, A1:0

    if (rtt_wr == 0)
    {
        mr2_rtt_wr = 0x0;
    }
    else if (rtt_wr == 120)     // RZQ/2
    {
        mr2_rtt_wr = 0x200;
    }
    else if (rtt_wr == 240)     // RZQ/1
    {
        mr2_rtt_wr = 0x400;
    }
    else if (rtt_wr == 80)      // RZQ/3
    {
        mr2_rtt_wr = 0x800;
    }
    else                        // Hi-Z
    {
        mr2_rtt_wr = 0x600;
    }


    mr2_lpasr_mode = 0x3 << 6;  // 3 = auto; rest are manual: 2=extended, 1=reduced, 0=normal temp modes
    mr2_data  = mr2_rtt_wr | mr2_lpasr_mode;
    mr2_data |= (latencies.mc_mr2_cwl & MR2_CWL___M) << MR2_CWL___S;

    // !! NOT supported in the controller
    if (mddr_settings_ptr->ddr4_wr_crc_en)
    {
        monaco_log(HIGH, "WARNING: WRITE CRC not supported by controller, not enabling!\n");
        //mr2_data |= 0x1 << MR2_WR_CRC___S;
    }


    // if (mem_freq_ps >= 5000)    //check freq too? less than 200 MHz clock, assuming DLL off mode
    if (platform_mode != SILICON)
    {
        // special DLL off mode
        mr1_enable_dll = 0;
        mr0_dll_reset = 0;
    }
    else                // real HW
    {

        mr1_enable_dll = 1;
        mr0_dll_reset = 1;
    }


    //------------------------------------------------------------------------------------
    // build mode register 1
    // Qoff, tDQS_en, RTT_NOM, WL_en, Out_drv_imp, AL, disable_DLL
    // &sim_mr1=0x0001      ; disable dll
    // &reg_mr1=0x0018      ; dll=on, rtt_nom, odic=40


    if (rtt_nom == 0)
    {
        mr1_rtt_nom = 0x0;
    }
    else if (rtt_nom == 60)
    {
        mr1_rtt_nom = 0x1;
    }
    else if (rtt_nom == 120)
    {
        mr1_rtt_nom = 0x2;
    }
    else if (rtt_nom == 40)
    {
        mr1_rtt_nom = 0x3;
    }
    else if (rtt_nom == 240)
    {
        mr1_rtt_nom = 0x4;
    }
    else if (rtt_nom == 48)
    {
        mr1_rtt_nom = 0x5;
    }
    else if (rtt_nom == 80)
    {
        mr1_rtt_nom = 0x6;
    }
    else if (rtt_nom == 34)
    {
        mr1_rtt_nom = 0x7;
    }
    else
    {
        mr1_rtt_nom = 0;
        monaco_log(HIGH, "ERROR processing rtt_nom = 0x%4.4x\n", rtt_nom);
    }


    if (dimm_out_imp == 34)
    {
        mr1_odic = 0;
    }
    else if ((dimm_out_imp == 40) || (dimm_out_imp == 48))
    {
        mr1_odic = 1;
    }
    else
    {
        mr1_odic = 0;
        monaco_log(HIGH, "ERROR processing DIMM_output_impedance = 0x%4.4x\n", dimm_out_imp);
    }


     // tDQS is always disabled since the memory controller doesn't support mixed of x4 & x8 in same channel
     mr1_data  = (mr1_rtt_nom & MR1_RTT_NOM_DDR4___M) << MR1_RTT_NOM_DDR4___S;
     mr1_data |= (mr1_odic & MR1_ODIC_DDR4___M) << MR1_ODIC___S;
     mr1_data |= (mr1_enable_dll & MR1_DLL___M) << MR1_DLL___S;



     //------------------------------------------------------------------------------------
     // build mode register 0
     // FAST_EXIT, WR, Reset_DLL, Mode, CL, RD_TYPE, BL
     // sim_mr0=0x0220  ; Fast=OFF, nWR=5, DLL_reset=no, mode=normal, CL=6, Nibble seq, BL=8_FIXED

     if (mddr_settings_ptr->page_settings.burst_len_mode == DB_BURST_LEN_BL8)
     {
         mr0_bl = 0;
     }
     else if (mddr_settings_ptr->page_settings.burst_len_mode == DB_BURST_LEN_OTF)
     {
         mr0_bl = 1;
     }
     else
     {
         mr0_bl = 0;
         monaco_log(HIGH, "ERROR processing burst length, burst_len_mode = %d 0=OTF, using BL8\n",
                 mddr_settings_ptr->page_settings.burst_len_mode);
     }


     cl = latencies.cl;


    if (cl < 9)
    {
        mr0_cl = 0x0;
        monaco_log(HIGH, "ERROR CAS latency is out of bounds, less than 5, CL = %d, using 5\n", cl);
    }
    else if (cl == 9)
    {
        mr0_cl = 0x0;
    }
    else if (cl == 10)
    {
        mr0_cl = 0x4;
    }
    else if (cl == 11)
    {
        mr0_cl = 0x10;
    }
    else if (cl == 12)
    {
        mr0_cl = 0x14;
    }
    else if (cl== 13)
    {
        mr0_cl = 0x20;
    }
    else if (cl == 14)
    {
        mr0_cl = 0x24;
    }
    else if (cl == 15)
    {
        mr0_cl = 0x30;
    }
    else if (cl == 16)
    {
        mr0_cl = 0x34;
    }
    else if (cl == 17)
    {
        mr0_cl = 0x64;
    }
    else if (cl == 18)
    {
        mr0_cl = 0x40;
    }
    else if (cl == 19)
    {
        mr0_cl = 0x70;
    }
    else if (cl == 20)
    {
        mr0_cl = 0x44;
    }
    else if (cl == 21)
    {
        mr0_cl = 0x74;
    }
    else if (cl == 22)
    {
        mr0_cl = 0x50;
    }
    else if (cl == 23)
    {
        mr0_cl = 0x50;
    }
    else if (cl == 24)
    {
        mr0_cl = 0x54;
    }
    else if (cl == 25)
    {
        mr0_cl = 0x1000;
    }
    else if (cl == 26)
    {
        mr0_cl = 0x1004;
    }
    else if (cl == 27)
    {
        mr0_cl = 0x1010;
    }
    else if (cl == 28)
    {
        mr0_cl = 0x1014;
    }
    else if (cl == 29)
    {
        mr0_cl = 0x1020;
    }
    else if (cl == 30)
    {
        mr0_cl = 0x1024;
    }
    else if (cl == 31)
    {
        mr0_cl = 0x1030;
    }
    else
    {
        // (cl > 32) or an intermediate illegal value
        mr0_cl = 0x1034;
        monaco_log(HIGH, "ERROR CAS latency is out of bounds, greater than 32, CL = %d, using 32\n", cl);
    }



    // Other tWR (clock cycles) are restricted to appropriate values by
    //  mddr_mc_build_timing_rdwr4_reg() during creation of the related field of the MC.

    // Values for mr_wr_clk 22, 24, and 26 were added in JESD79-4A_r0_FM9 using previously
    //  reserved fields, which is why they do not follow the same pattern as the values
    //  for mr_wr_clk 10 through 24.
    if (mddr_timing_vals.mr_wr_clk <= 10)
    {
        mr0_wr = 0;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 20)
    {
        mr0_wr = com_ceil_div(mddr_timing_vals.mr_wr_clk, 2) - 5;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 22)
    {
        mr0_wr = 7;
    }
    else if (mddr_timing_vals.mr_wr_clk <= 24)
    {
        mr0_wr = 6;
    }
    else // tWR clock cycles == 26
    {
        mr0_wr = 16;
    }


    mr0_data  = (mr0_bl & MR0_BL___M) << MR0_BL___S;
    mr0_data |= (mr0_cl & MR0_CL_DDR4___M) << MR0_CL_DDR4___S;
    mr0_data |= (mr0_dll_reset & MR0_DLL_RESET___M) << MR0_DLL_RESET___S;
    mr0_data |= (mr0_wr & MR0_WR_DDR4___M) << MR0_WR___S;



#ifdef CONFIG_TESTOS_EMU
	mr2_data = 0x38;
#endif

    // The mode registers for a channel are targeted by rank across both slots.
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr0_data = mr0_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr1_data = mr1_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr2_data = mr2_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr3_data = mr3_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr4_data = mr4_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr5_data = mr5_data;
    mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr6_data = mr6_data;
}


/*!****************************************************************************
*
* @par Description:
*    This function determines the VREF range based on the current VrefDQ.
*
*                                  @param
*    vref            Current VrefDQ value.
*
*
* @return
*    vref range: 0 if range1, or 1 for range2 for valid VREF in JEDEC
*
* @author
*    lchavani
*
******************************************************************************/
uint8_t mddr_mc_get_vref_range(uint16_t vref)
{
    uint8_t vref_range;
    uint8_t step_mod;

    if (vref < 6000)
    {
        vref_range = 1;
    }
    else if (vref > 7750)
    {
        vref_range = 0;
    }
    else
    {
        step_mod = (vref - 6000) % 65;

        if (step_mod == 0)
        {
            vref_range = 0;
        }
        else
        {
            step_mod = (vref - 4500) % 65;

            if (step_mod == 0)
            {
                vref_range = 1;
            }
            else
            {
                monaco_log(HIGH, "Warning : Non-standard JEDEC Vref, using Vref Range 1\n");
                vref_range = 0;
            }
        }
    }

    return vref_range;
}


/*!****************************************************************************
*
* @par Description:
*    This function sets the register control words for a DDR3 RDIMM.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    slot             The DIMM slot in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_exec_ddr3_rcw(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t slot)
{
    uint8_t rcw_num;
    uint8_t rcw_data;
    uint64_t slot_rcw_data;
    uint8_t slot_rcw_mask;


    slot_rcw_mask = 0x0F;
    slot_rcw_data = mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00;


    for(rcw_num = 0; rcw_num < NUM_DDR3_RDIMM_RCW; ++rcw_num)
    {
        rcw_data = slot_rcw_data & slot_rcw_mask;

        mddr_mc_cw_write(mddr_base_addr, slot, rcw_num, rcw_data);

        slot_rcw_data = slot_rcw_data >> 4;
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function sets the register control words for a DDR4.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    ddr_chan         DDR channel to perform function on.
*                                  @param
*    slot             The DIMM slot in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_exec_ddr4_rcw(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t slot)
{
    uint8_t tstab = 5;            // 5us from RCD spec for speeds up to 2933MT/s
                                  // change to frequency band 2 needs 15us
    uint8_t rcw_num;
    uint64_t set_rcw_bm = 0xE738; // currently F,E,D,A,9,8,5,4,3
    uint8_t rcw_data;
    uint64_t slot_rcw_data;
    uint8_t slot_rcw_mask;


    slot_rcw_mask = 0x0F;

    // Start with the first set of control words
    slot_rcw_data = mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw0f_00;

    rcw_num = 0;

    while(set_rcw_bm != 0x0)
    {
        if ((set_rcw_bm & 0x1) == 0x1)
        {
            rcw_data = slot_rcw_data & slot_rcw_mask;

            mddr_mc_cw_write(mddr_base_addr, slot, rcw_num, rcw_data);

            if ((rcw_num == 2) || (rcw_num == 6) || (rcw_num == 10))
            {
                mddr_mc_wait_us(mddr_base_addr, tstab);
            }
        }

        set_rcw_bm = set_rcw_bm >> 1;
        slot_rcw_data = slot_rcw_data >> 4;
        ++rcw_num;
    }


    // Move to the 2nd set of control words.
    slot_rcw_data = mddr_reg_vals.rcw_regs[ddr_chan][slot].rcw7x_0x;

    // RC3x
    rcw_num = 3;
    rcw_data = (0xFF & (slot_rcw_data >> (rcw_num*8)));
    rcw_num = rcw_num * 16;
    mddr_mc_cw_write(mddr_base_addr, slot, rcw_num, rcw_data);

    mddr_mc_wait_us(mddr_base_addr, tstab);


    // RC7x
    rcw_num = 7;
    rcw_data = (0xFF & (slot_rcw_data >> (rcw_num*8)));
    rcw_num = rcw_num * 16;
    mddr_mc_cw_write(mddr_base_addr, slot, rcw_num, rcw_data);


    // RCBx
    // Move to the 2nd set of control words.
    // slot_rcw_data = mddr_reg_vals.rcw_regs[ddr_chan][slot].f1rc00_f0rcbx_8x;
    // rcw_num = 11;
    // rcw_data = (0xFF & (slot_rcw_data >> ((rcw_num-8)*8)));
    // rcw_num = rcw_num * 16;
    // mddr_mc_cw_write(mddr_base_addr, slot, rcw_num, rcw_data);
}




/*!****************************************************************************
*
* @par Description:
*    This function builds the DDR3 mode register write values.
*
*                                  @param
*    mddr_base_addr     The base address of the configuration registers for
*                        the memory controller.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    rank_num           The rank number in the DDR channel to target.
*                                  @param
*    rank_indicator     The rank number in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_exec_ddr3_mr(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t rank_num, uint8_t rank_indicator)
{
    // addr = BG1, BG0(BA2), BA1, BA0
    uint8_t mr0_addr = 0x0;
    uint8_t mr1_addr = 0x1;
    uint8_t mr2_addr = 0x2;
    uint8_t mr3_addr = 0x3;


    // Unique per rank
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr2_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr2_data, PDA_MASK_INVALID);   // rtt_wr, srt, asr
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr3_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr3_data, PDA_MASK_INVALID);
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr1_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr1_data, PDA_MASK_INVALID);   // rtt_nom, out_imp, qoff, wrlvl
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr0_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr0_data, PDA_MASK_INVALID);
}



/*!****************************************************************************
*
* @par Description:
*    This function builds the DDR3 mode register write values.
*
*                                  @param
*    mddr_base_addr     The base address of the configuration registers for
*                        the memory controller.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    rank_num           The rank number in the DDR channel to target.
*                                  @param
*    rank_indicator     The rank number in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_exec_ddr4_mr(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t rank_num, uint8_t rank_indicator)
{
    // addr = BG1, BG0(BA2), BA1, BA0
    uint8_t mr0_addr = 0x0;
    uint8_t mr1_addr = 0x1;
    uint8_t mr2_addr = 0x2;
    uint8_t mr3_addr = 0x3;
    uint8_t mr4_addr = 0x4;
    uint8_t mr5_addr = 0x5;
    uint8_t mr6_addr = 0x6;
    bool Atomic_vredq_update = false;


    // Unique per rank
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr3_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr3_data, PDA_MASK_INVALID);

    // Set these if not SILICON or not using 2D training
    if ((platform_mode != SILICON) || (TRAINING_2D_STEPS == 0))
    {
        // MR6 Vref sequence to properly set DRAM Vref.
        mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr6_addr, (mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr6_data | 0x80), PDA_MASK_INVALID);
        mddr_mc_wait_us(mddr_base_addr, 1);
        mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr6_addr, (mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr6_data | 0x80), PDA_MASK_INVALID);
        mddr_mc_wait_us(mddr_base_addr, 1);
        mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr6_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr6_data, PDA_MASK_INVALID);
        mddr_mc_wait_us(mddr_base_addr, 1);
    }

    if(CA_margin_enabled)
    {
        if(!Atomic_vredq_update)
        {
            uint16_t mr6_trained;
            uint8_t rank_id, cs_id;

            // Map rank number to CS , assuming one rank per CS
            // 3DS RAM need double check.
            rank_id = rank_indicator;
            cs_id = 0;
            while(rank_id != 1)
            {
                rank_id = rank_id>>1;
                cs_id++;
            }

            // in CA margining mode, write trained Vref value to MR6
            mr6_trained = mddr_phy_get_average_dram_vref(ddr_chan, cs_id);
            mr6_trained |= mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr6_data & 0xFF00;

            mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr6_addr, (mr6_trained| 0x80), PDA_MASK_INVALID);
            mddr_mc_wait_us(mddr_base_addr, 1);
            mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr6_addr, (mr6_trained| 0x80), PDA_MASK_INVALID);
            mddr_mc_wait_us(mddr_base_addr, 1);
            mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr6_addr, mr6_trained, PDA_MASK_INVALID);
            mddr_mc_wait_us(mddr_base_addr, 1);
        }
        else
        {
            // Atomic DRAM Vref update
            mddr_mc_vref_write(mddr_base_addr, ddr_chan, rank_indicator, rank_num);
        }
    }

    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr5_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr5_data, PDA_MASK_INVALID);
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr4_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr4_data, PDA_MASK_INVALID);
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr2_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr2_data, PDA_MASK_INVALID);   // rtt_wr, srt, asr
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr1_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr1_data, PDA_MASK_INVALID);   // rtt_nom, out_imp, qoff, wrlvl
    mddr_mc_mr_write(mddr_base_addr, rank_indicator, mr0_addr, mddr_reg_vals.mode_regs[ddr_chan][rank_num].mr0_data, PDA_MASK_INVALID);

}





/*!****************************************************************************
*
* @par Description:
*    This function does a mode register write and waits for the operation to
*    complete.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    ranks            Indication of the ranks to target.
*                                  @param
*    mr_addr          The mode register address to target.
*                                  @param
*    mr_data          The 16-bit mode register data to write.
*                                  @param
*    mask             PDA mask when PDA mode is being set for DDR4. Should
*                     be PDA_MASK_INVALID when PDA mode is not resuired
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_mr_write(uint64_t mddr_base_addr, uint32_t ranks, uint8_t mr_addr, uint16_t mr_data, uint32_t mask)
{
    uint32_t reg_val;


    // set target ranks
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OPT_0_OFFSET, "DDR_MANUAL_OPT_0", ranks);

    // setup address
    reg_val  = (mr_addr & MANUAL_OPT1_ADDR___M) << MANUAL_OPT1_ADDR___S;

    // setup data
    reg_val |= (mr_data & MANUAL_OPT1_DATA___M) << MANUAL_OPT1_DATA___S;

    // set address + data
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OPT_1_OFFSET, "DDR_MANUAL_OPT_1", reg_val);


    // DDR4 PDA, Per DRAM Addressability, mask when LRDIMMs are supported.
    // set pda mask if valid mask parameter & dev=ddr4
    if ((mask != PDA_MASK_INVALID) && (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4))
    {
        reg_val = mddr_get_reg(mddr_base_addr + MDDR_DDR_MANUAL_OPT_2_OFFSET, "DDR_MANUAL_OPT_2");

        // Clear out previous PDA mode info.
        reg_val &= ~(MANUAL_OPT2_PDA_MASK___M << MANUAL_OPT2_PDA_MASK___S);
        reg_val &= ~(MANUAL_OPT2_PDA_MODE___M << MANUAL_OPT2_PDA_MODE___S);

        // Set new PDA mode info.
        reg_val |= (mask & MANUAL_OPT2_PDA_MASK___M) << MANUAL_OPT2_PDA_MASK___S;
        reg_val |= (0x1 & MANUAL_OPT2_PDA_MODE___M) << MANUAL_OPT2_PDA_MODE___S;

        mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OPT_2_OFFSET, "DDR_MANUAL_OPT_2", reg_val);
    }


    // issue mode register write
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_RANK_OFFSET, "DDR_MANUAL_RANK", 0x1 << MANUAL_RANK_MR_WRITE___S);

    // wait for the operation to complete.
    mddr_mc_check_status(mddr_base_addr);
}


/*!****************************************************************************
*
* @par Description:
*    This function perform atomic DRAM vrefdq update following HPG 4.1.6 for recovering
*           Vref settings of all DRAM devices
*
*                                  @param
*    mddr_base_addr     The base address of the configuration registers for
*                        the memory controller.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    rank_num           The rank number in the DDR channel to target.
*                                  @param
*    rank_id            The rank number in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    jihyunl
*
******************************************************************************/
void mddr_mc_vref_write(uint64_t mddr_base_addr, uint8_t ddr_chan, uint8_t rank_num, uint32_t rank_id)
{
    uint32_t tmod;
    uint32_t mr0_val, opt1_val;

    // Match the current DRAM's MR3
    mddr_set_reg(mddr_base_addr + MDDR_DRAM_MR_3_OFFSET, "DRAM_MR_3", mddr_reg_vals.mode_regs[ddr_chan][rank_id].mr3_data);

    // Match the current DRAM's MR6
    opt1_val = (6 & MANUAL_OPT1_ADDR___M) << MANUAL_OPT1_ADDR___S;
    opt1_val |= (mddr_reg_vals.mode_regs[ddr_chan][rank_id].mr6_data & MANUAL_OPT1_DATA___M) << MANUAL_OPT1_DATA___S;
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OPT_1_OFFSET, "DDR_MANUAL_OPT_1", opt1_val);

    //TO-DO: For DDR4 LRDIMM, ensure the following CSR value matches the current value of DB word F0BC1x

    // set target ranks
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OPT_0_OFFSET, "DDR_MANUAL_OPT_0", rank_num);

    // Set tMRD,tMOD,tMRD_PDA,tMOD_PDA =max(tVREFDQE,tVREFDQX)
    tmod = mddr_get_num_clocks(((MIN_TVREFDQE_DDR4>MIN_TVREFDQX_DDR4)?MIN_TVREFDQE_DDR4:MIN_TVREFDQX_DDR4), mem_freq_ps);
    mr0_val  = (tmod & MR_0_TMOD___M) << MR_0_TMOD___S;
    mr0_val |= (tmod & MR_0_TMRD___M) << MR_0_TMRD___S;
    mr0_val |= (tmod & MR_0_TMOD_PDA___M) << MR_0_TMOD_PDA___S;
    mr0_val |= (tmod & MR_0_TMRD_PDA___M) << MR_0_TMRD_PDA___S;
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_MR_0_OFFSET, "TIMING_DRAM_MR_0", mr0_val);

    // Load new timing paramter
    mddr_set_reg(mddr_base_addr + MDDR_CSR_CNTL_OFFSET, "CSR_CNTL", 0x1);

    // issue a NOP command
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_RANK_OFFSET, "DDR_MANUAL_RANK", 0x1 << MANUAL_RANK_NOP___S);

    // issue the VREFDQ command
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_RANK_OFFSET, "DDR_MANUAL_RANK", 0x1 << MANUAL_RANK_SET_VREFDQ_PDA___S);

    // wait for the operation to complete.
    mddr_mc_check_status(mddr_base_addr);

    // Restore tMRD,tMOD parameter
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_DRAM_MR_0_OFFSET, "TIMING_DRAM_MR_0", mddr_reg_vals.timing_regs.mr0_val);

    // Load new timing paramter
    mddr_set_reg(mddr_base_addr + MDDR_CSR_CNTL_OFFSET, "CSR_CNTL", 0x1);

}


/*!****************************************************************************
*
* @par Description:
*    This function does a DDR3 control word write to RCD on DIMM and waits for
*    the operation to complete.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    slot             The DIMM slot in the DDR channel to target.
*                                  @param
*    cw_addr          The control word address to target.
*                                  @param
*    cw_data          The 16-bit control word data to write.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_cw_write(uint64_t mddr_base_addr, uint8_t slot, uint8_t cw_addr, uint16_t cw_data)
{
    uint32_t reg_val;
    uint32_t cke;


    // setup address
    reg_val  = (cw_addr & MANUAL_OPT1_ADDR___M) << MANUAL_OPT1_ADDR___S;

    // setup data
    reg_val |= (cw_data & MANUAL_OPT1_DATA___M) << MANUAL_OPT1_DATA___S;

    // set address + data
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OPT_1_OFFSET, "DDR_MANUAL_OPT_1", reg_val);

    // select DIMM slot
    if (slot == 0)
    {
        cke = 0x1;
    }
    else
    {
        cke = 0x4;
    }


    reg_val  = (cke & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;

    // set cw write bit
    reg_val |= 0x1 << MANUAL_CKE_CW_WRITE___S;

    // issue control word write
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", reg_val);

    monaco_log(INFORMATIONAL, "    CW_WRITE 0x%2.2x = 0x%4.4x\n", cw_addr, cw_data);

    // wait for the operation to complete.
    mddr_mc_check_status(mddr_base_addr);
}



/*!****************************************************************************
*
* @par Description:
*    This function initiates a ZQ calibration of the given type on the memory
*    controller.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    ranks            The set of flags indicating which ranks are valid for the
*                     memory controller.
*                                  @param
*    zq_type          The type of ZQ calibration to perform.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_zqcal(uint64_t mddr_base_addr, uint32_t ranks, zq_cal_type_t zq_type)
{

    uint32_t manual_rank_zq;


    // setup ranks to do ZQCAL on
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OPT_0_OFFSET, "DDR_MANUAL_OPT_0", ranks);


    // setup corresponding ZQ command
    if (zq_type == ZQ_SHORT)
    {
        manual_rank_zq = 0x1 << MANUAL_RANK_ZQ_SHORT___S;
    }
    else if (zq_type == ZQ_LONG)
    {
        manual_rank_zq = 0x1 << MANUAL_RANK_ZQ_LONG___S;
    }
    else
    {
        // ZQ_INIT
        manual_rank_zq = 0x1 << MANUAL_RANK_ZQ_INIT___S;
    }

    monaco_log(MEDIUM, "  Performing ZQcal 0x%2.2x on ranks 0x%8.8x\n  MANUAL_RANK = 0x%8.8x\n",
               zq_type, ranks, manual_rank_zq);

    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_RANK_OFFSET, "DDR_MANUAL_RANK", manual_rank_zq);

    mddr_mc_check_status(mddr_base_addr);
}



/*!****************************************************************************
*
* @par Description:
*    This function enables periodic ZQ calibration on the memory controller.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_enable_periodic_zqcal(uint64_t mddr_base_addr, mddr_settings_t *mddr_settings_ptr)
{

    if (mddr_settings_ptr->periodic_zq_cal_en)
    {
        mddr_set_reg(mddr_base_addr + MDDR_DDR_ZQCAL_EN_OFFSET, "DDR_ZQCAL_EN", mddr_combined_valid_ranks);

        monaco_log(MEDIUM, "  Enabling periodic ZQcal on available ranks\n");
        monaco_log(INFORMATIONAL, "   Setting DDR_ZQCAL_EN = %x\n", mddr_combined_valid_ranks);
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function enables the DIMM slot making it available to the system.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    slot             The DIMM slot in the DDR channel to target.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_slot_ready(uint64_t mddr_base_addr, uint8_t slot)
{
    uint64_t reg_addr;
    uint32_t reg_val;


    reg_val = mddr_reg_vals.dimm_slot_config_val[slot];
    reg_val |= 0x1 << SLOT_CONFIG_SLOT_READY___S;

    if (slot == 0)
    {
        reg_addr = mddr_base_addr + MDDR_DIMM_SLOT0_CONFIG_OFFSET;
        mddr_set_reg(reg_addr, "DIMM_SLOT0_CONFIG", reg_val);
    }
    else
    {
        reg_addr = mddr_base_addr + MDDR_DIMM_SLOT1_CONFIG_OFFSET;
        mddr_set_reg(reg_addr, "DIMM_SLOT1_CONFIG", reg_val);
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function waits for a manual command to complete.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_check_status(uint64_t mddr_base_addr)
{
    uint64_t reg_addr;
    uint32_t reg_val;
    uint32_t complete_mask;
    uint32_t timeout_mask;
    uint32_t rejected_mask;
    uint32_t expired_mask;
    uint32_t status_mask;
    uint8_t max_loops = 1;


    reg_addr = mddr_base_addr + MDDR_DDR_CMD_STATUS_OFFSET;
    complete_mask = (CMD_STATUS_COMPLETE___M << CMD_STATUS_COMPLETE___S);
    timeout_mask = (CMD_STATUS_TIMEOUT___M << CMD_STATUS_TIMEOUT___S);
    rejected_mask = (CMD_STATUS_REJECTED___M << CMD_STATUS_REJECTED___S);
    expired_mask = (CMD_STATUS_EXPIRED___M << CMD_STATUS_EXPIRED___S);
    status_mask =  complete_mask | timeout_mask | rejected_mask | expired_mask;


    // wait for complete
    mddr_wait_for_set(mddr_base_addr, reg_addr, status_mask, max_loops);
    reg_val = read32(reg_addr);


    monaco_log(INFORMATIONAL, "        DDR_CMD_STATUS = 0x%8.8x\n", reg_val);

    if ((reg_val & timeout_mask) != 0x0)
    {
        monaco_log(MEDIUM, "  ERROR command timed out!\n");
    }

    if ((reg_val & rejected_mask) != 0x0)
    {
        monaco_log(MEDIUM, "  ERROR command rejected out!\n");
    }

    if (((reg_val & expired_mask) != 0x0) && (verbose_mode))
    {
        monaco_log(INFORMATIONAL, "          HW timer expired\n");
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function delays for the given number of nanoseconds using the
*    DDR clock.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*                                  @param
*    num_ns                 The number of nanoseconds to delay.
*
*
* @return
*    None
*
* @author
*    gkowis
******************************************************************************/
void mddr_mc_wait_ns(uint64_t mddr_base_addr, uint16_t num_ns)
{
    uint16_t num_cycles;


    num_cycles = mddr_get_num_clocks(num_ns * PICO_SEC_PER_NANO_SEC, mem_freq_ps);

    // use DDR clock
    mddr_mc_set_hw_timer(mddr_base_addr, num_cycles, false);
}


/*!****************************************************************************
*
* @par Description:
*    This function delays for the given number of microseconds using the
*    DDR clock.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*                                  @param
*    num_us                 The number of microseconds to delay.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_wait_us(uint64_t mddr_base_addr, uint16_t num_us)
{
    uint16_t max_timer_delay = 0xFFFF;
    uint32_t num_cycles;
    uint32_t timer_delay_num;
    uint32_t num_max_timer_delays;
    uint16_t remining_timer_delay;


    // At 1 MHz a cycle takes 1 usec.
    num_cycles = num_us * mem_freq_mhz;

    // The HW timer has a maximum of 0xFFFF cycles so a larger delay requires
    //  multiple max HW delays. A delay can be a fraction of max cycles or may
    //  not be evenly divisable by the max.
    num_max_timer_delays = num_cycles / max_timer_delay;
    remining_timer_delay = num_cycles % max_timer_delay;

    for(timer_delay_num = 0; timer_delay_num < num_max_timer_delays; ++timer_delay_num)
    {
        mddr_mc_set_hw_timer(mddr_base_addr, max_timer_delay, false);
    }

    if(remining_timer_delay != 0)
    {
        // Do any fraction
        mddr_mc_set_hw_timer(mddr_base_addr, remining_timer_delay, false);
    }
}


#if 0

/*!****************************************************************************
*
* @par Description:
*    This function delays for the given number of nanoseconds using the
*    DDR clock.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller. Unused provided for compatability.
*                                  @param
*    num_ns                 The number of nanoseconds to delay. Unused provided
*                            for compatability.
*
*
* @return
*    None
*
* @author
*    gkowis
******************************************************************************/
void mddr_mc_wait_ns(UNUSED_PARAM uint64_t mddr_base_addr, UNUSED_PARAM uint16_t num_ns)
{
    volatile int i;
    volatile int loops = 25;

    // HACK!!- Spin to replace the timer for bare-metal
    for(i = 0; i < loops; ++i);
}



/*!****************************************************************************
*
* @par Description:
*    This function delays for the given number of microseconds. For boot code
*     it uses the the CoreBSP delay drivers. The drivers are packaged in the
*     CoreBSP single instance wrapper to allow the selection based on IMC boot
*     versus IMC runtime context. For baremetal it is a simple spin loop and
*     does not actuly provide a varaint delay.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller. Unused provided for compatability.
*                                  @param
*    num_us                 The number of microseconds to delay. Unused provided
*                            for compatability.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_wait_us(UNUSED_PARAM uint64_t mddr_base_addr, UNUSED_PARAM uint16_t num_us)
{
    volatile int i;
    volatile int loops = 100 * num_us;
//    volatile int loops = 50000;  // Double for now, probably ok as was but just in case for up to 320MHz.

    // HACK!!- Long spin to replace the timer for bare-metal
    for(i = 0; i < loops; ++i);
}

#endif


/*!****************************************************************************
*
* @par Description:
*    This function uses the HW timer from the memory controller to delay for
*    the given number of clock cycles. The clock is selectable and is either
*    the DDR or XO clock.
*
*
*                                  @param
*    mddr_base_addr          The base address of the configuration registers for
*                           the memory controller.
*                                  @param
*    delay_clocks           The number of clock cycles to wait.
*                                  @param
*    use_XO                 Boolean used to indicate if the XO clock should
*                           be used instead of the DDR clock.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_set_hw_timer(uint64_t mddr_base_addr, uint16_t delay_clocks, bool use_XO)
{
    uint32_t reg_val;
    uint16_t domain;

    if (use_XO)
    {
        domain = HW_TIMER_DOMAIN_XO_CLK;
    }
    else
    {
        domain = HW_TIMER_DOMAIN_DDR_CLK;
    }


    reg_val  = (delay_clocks & HW_TIMER_TIME___M) << HW_TIMER_TIME___S;
    reg_val |= (domain & HW_TIMER_DOMAIN___M) << HW_TIMER_DOMAIN___S;

    monaco_log(INFORMATIONAL, "    Setting HW_TIMER = %x\n", reg_val);

    write32(mddr_base_addr + MDDR_HW_TIMER_OFFSET, reg_val);

    // Wait for the timer to expire.
    do
    {
        reg_val  = read32(mddr_base_addr + MDDR_DDR_CMD_STATUS_OFFSET);
        reg_val &= CMD_STATUS_EXPIRED___M;
    } while(reg_val != CMD_STATUS_EXPIRED___M);
}


#if 0
/*!****************************************************************************
*
* @par Description:
*    This function uses the HW timer from the memory controller to delay for
*    the given number of clock cycles. The clock is selectable and is either
*    the DDR or XO clock.
*
*
*                                  @param
*    mddr_base_addr          The base address of the configuration registers for
*                           the memory controller.
*                                  @param
*    delay_clocks           The number of clock cycles to wait.
*                                  @param
*    use_XO                 Boolean used to indicate if the XO clock should
*                           be used instead of the DDR clock.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_mc_set_hw_timer(UNUSED_PARAM uint64_t mddr_base_addr, UNUSED_PARAM uint16_t delay_clocks, UNUSED_PARAM bool use_XO)
{
    volatile int i;
    volatile int loops = 25000;

    #ifdef __BAREMETAL__
        // HACK!!- Long spin to replace the timer for bare-metal
        for(i = 0; i < loops; ++i);

    #else
        // Eventually the CoreBSP busy wait for IMC will get called here for boot code
        //  but for now just have a long spin like bare-metal.
        for(i = 0; i < loops; ++i);
    #endif

}
#endif


