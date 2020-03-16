#ifndef _MODULE_MDDR_INIT_H_
#define _MODULE_MDDR_INIT_H_

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
* @file mddr_init.h
*
* @par Description:
*
*    This header contains the driver internal prototypes, derived data types,
*    etc. to allow the cooperation of the MDDR sub-system modules / components .
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <asm/mach/monaco/memory/spd.h>
#include <asm/mach/monaco/memory/mddr_si.h>
#include <asm/mach/monaco/memory/mddr_phy_init.h>
#include <asm/mach/monaco/memory/mddr_phy_train.h>

/******************************************************************************
* Defined Constants
******************************************************************************/

#define QSB_MEM_BASE_MSB                          0x0000  // bits 43:28 of QSB, memory starts a 256GB (bit 38)
#define NUM_DDR3_RDIMM_RCW                        16      // Number of DDR3 RDIMM register control words


#define DDR4_RCW_CMD_LAT_ADDER___S                60      // Register control word shift of the command latency adder value.
#define DDR4_RCW_PARITY_CTRL_WORD___S             56      // Register control word shift of the parity control word value.
#define DDR4_RCW_DIMM_CONFIG___S                  52      // Register control word shift of the DIMM configuration value.
#define DDR4_RCW_RDIMM_OP_SPEED___S               40      // Register control word shift of the RDIMM operating speed value.
#define DDR4_RCW_POWER_SAVING___S                 36      // Register control word shift of the power saving settings value.
#define DDR4_RCW_IO_CONFIG___S                    32      // Register control word shift of the input/output configuration value.
#define DDR4_RCW_CK_Y13___S                       22      // Register control word shift of the CK_Y13 SPD value.
#define DDR4_RCW_CK_Y02___S                       20      // Register control word shift of the CK_Y02 SPD value.
#define DDR4_RCW_CK_CTL_CKE___S                   18      // Register control word shift of the CK_CTL_CKE SPD value.
#define DDR4_RCW_CK_CTL_ODT___S                   16      // Register control word shift of the CK_CTL_ODT SPD value.
#define DDR4_RCW_CK_CTL_CS___S                    14      // Register control word shift of the CK_CTL_CS SPD value.
#define DDR4_RCW_CK_CTL_CA___S                    12      // Register control word shift of the CK_CTL_CA SPD value.
#define DDR4_RCW_INTL_VREFCA___S                  8       // Register control word shift of the Internal VrefCA Control Word.

#define DDR4_RCW_CMD_FG_OP_SPEED___S              24      // Register control word shift of the fine granularity operating speed value.
#define DDR4_RCW_CMD_INPUT_BUS_TERM_LAT___S       56      // Register control word shift of the input bus termination value.

#define DDR4_RCW_CK_BCOM_BODT_BCKE___S            32      // Register control word shift of the CK_BCOM_BODT_BCKE SPD value.
#define DDR4_RCW_CK_BCK___S                       34      // Register control word shift of the CK_BCK SPD value.

#define DDR4_LR_RCW_HOST_DQ_RTT_NOM___S           0       // Register control word shift of the LRDIMM Host Interface DQ RTT_NOM term value.
#define DDR4_LR_RCW_HOST_DQ_RTT_WR___S            4       // Register control word shift of the LRDIMM Host Interface DQ RTT_WR term value.
#define DDR4_LR_RCW_HOST_DQ_RTT_PARK___S          8       // Register control word shift of the LRDIMM Host Interface DQ RTT_PARK term value.
#define DDR4_LR_RCW_HOST_DQ_RON___S               12      // Register control word shift of the LRDIMM Host Interface DQ Driver value.
#define DDR4_LR_RCW_DRAM_DB_MDQ_TERM___S          16      // Register control word shift of the LRDIMM DRAM interface MDQ term value.
#define DDR4_LR_RCW_DRAM_DB_MDQ_RON___S           20      // Register control word shift of the LRDIMM DRAM interface MDQ driver value.
#define DDR4_LR_RCW_CMD_SPACE___S                 24      // Register control word shift of the LRDIMM cmd space values for clk, I/O cal, parity.
#define DDR4_LR_RCW_RANK_PRESENCE___S             28      // Register control word shift of the LRDIMM rank presence value.
#define DDR4_LR_RCW_PWR_SAV_SETTINGS___S          36      // Register control word shift of the LRDIMM power saving settings value.
#define DDR4_LR_RCW_OP_SPEED___S                  40      // Register control word shift of the LRDIMM operating speed value.

#define DDR4_LR_RCW_FG_OP_SPEED___S               0       // Register control word shift of the LRDIMM fine granularity operating speed value.
#define DDR4_LR_RCW_HOST_DB_VREF___S              8       // Register control word shift of the LRDIMM Host interface VREF value.
#define DDR4_LR_RCW_DRAM_DB_VREF___S              16      // Register control word shift of the LRDIMM DRAM interface VREF value.
#define DDR4_LR_RCW_DRAM_DB_MDQ_VREF_RNG___S      24      // Register control word shift of the LRDIMM DRAM DB mdq vrefdq range value.

#define DDR4_RCW_4BITRCW___S                      4       // Register control word 4-bit shift
#define DDR4_RCW_4BITRCW___M                      0xF     // Register control word 4-bit mask
#define DDR4_RCW_8BITRCW___M                      0xFF    // Register control word 8-bit mask

/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    This type is used to collect the translated DIMM SPD information that is
*     expected to be common accross all populated DDR channels but can differ
*     between the slots of a channel. I.e. The same slot in each channel is
*     populated with like DIMMs but the slots in a channel can differ is some
*     ways.
*
* @par Members
*
*                                  <PRE>
*    num_ranks            Number of ranks on the the DIMM.
*    num_bank_groups      Bank group indication value. DDR4 only.
*    num_rows             Number of rows.
*    num_columns          Number of columns.
*    die_count            Number of dies on the DIMM.
*    dimm_size_mb         Size of the DIMM in MB.
*    ca_mirrored          Boolean indication of if the DIMMs are CA mirrored.
*
*    rcw0f_00             RDIMM configuration words.
*    out_drv_ck_y13       RDIMM / LRDIMM clock driver Y13 signal output strength.
*    out_drv_ck_y02       RDIMM / LRDIMM clock driver Y02 signal output strength.
*
*    rdm_out_drv_ctl_a    RDIMM driver output strength for control signal A. DDR3 only.
*    rdm_out_drv_ctl_b    RDIMM driver output strength for control signal B. DDR3 only.
*    rdm_out_drv_ca_a     RDIMM drive output strength for commands/addresses signal A. DDR3 only.
*    rdm_out_drv_ca_b     RDIMM drive output strength for commands/addresses signal B. DDR3 only.
*
*    out_drv_ctl_cke      RDIMM / LRDIMM drive output strength for the CKE signal. DDR4 only.
*    out_drv_ctl_odt      RDIMM / LRDIMM drive output strength for the ODT signal. DDR4 only.
*    out_drv_ctl_ca       RDIMM / LRDIMM drive output strength for the commands/addresses signal. DDR4 only.
*    out_drv_ctl_cs       RDIMM / LRDIMM drive output strength for the chip select signal. DDR4 only.
*
*    lrdm_db_drv_ck_bcom_bodt_bcke    LRDIMM output drive strength for clock and data buffer ctrl. DDR4 only.
*    lrdm_db_drv_ck_bck               LRDIMM output drive strength for clock and data buffer ctrl. DDR4 only.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t num_ranks;
    uint8_t num_bank_groups;
    uint8_t num_rows;
    uint8_t num_columns;
    uint8_t die_count;
    uint32_t dimm_size_mb;
    bool ca_mirrored;

    // Common RDIMM / LRDIMM Values
    uint8_t out_drv_ck_y13;
    uint8_t out_drv_ck_y02;
    uint64_t rcw0f_00;


    // DDR3 Only RDIMM Values
    uint8_t rdm_out_drv_ctl_a;
    uint8_t rdm_out_drv_ctl_b;
    uint8_t rdm_out_drv_ca_a;
    uint8_t rdm_out_drv_ca_b;

    // DDR4 RDIMM / LRDIMM Values
    uint8_t out_drv_ctl_cke;
    uint8_t out_drv_ctl_odt;
    uint8_t out_drv_ctl_ca;
    uint8_t out_drv_ctl_cs;

    // DDR4 Only LRDIMM Values
    uint8_t lrdm_db_drv_ck_bcom_bodt_bcke;
    uint8_t lrdm_db_drv_ck_bck;
}mddr_slot_cfg_t;


/*!****************************************************************************
*
* @par Description
*    This type is used to collect the translated DIMM SPD information that is
*     expected to be common accross all populated DDR channels. Each populated
*     channel will be be populated alike.
*
* @par Members
*
*                                  <PRE>
*    dev_type             Device type. DDR3 or DDR4.
*    mod_type             DIMM module type. UDIMM, RDIMM, SODIMM or SOUDIMM.
*    sdram_width          SDRAM device width indicator.
*    max_page_size_kb     Largest page size from all DIMMs
*    has_ecc              Boolean indication of if the DIMMs have ECC.
*    is_3DS               Boolean indication of if the DIMMs are 3DS stacked.
*    slots_ck_sel         Combined manual CK (CKE groups clock) selects for
*                          the slots of a channel. The slots can have
*                          different values.
*    slots_cke_sel        Combined manual CKE groups selects for the DIMM
*                          slots of a channel. The slots can have
*                          different values.
*    slot_config          Array containing the configurations that can differ
*                           between the slots of a channel.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t         dev_type;
    uint8_t         mod_type;
    uint8_t         sdram_width;
    uint32_t        max_page_size_kb;
    bool            has_ecc;
    bool            is_3DS;
    uint8_t         slots_ck_sel;
    uint8_t         slots_cke_sel;
    uint8_t         num_slots_populated;
    mddr_slot_cfg_t slot_config[DDR_MAX_NUM_SLOTS_PER_CHAN];
}mddr_common_cfg_t;


/*!****************************************************************************
*
* @par Description
*    This type is used to collect the timing values based on the timing
*    parameters extracted from the SPD of the populated DIMMs and platform
*    specific settings.
*
* @par Members
*
*                                  <PRE>
*    cas_lat_sup         CAS latencies supported flags.
*    taa_min_ps          Minimum CAS Latency Time in ps.
*    tck_min_ps          SDRAM Minimum Cycle Time in ps.
*    tck_max_ps          SDRAM Maximum Cycle Time in ps.
*    tck_ps              DDR Clock period in ps.
*    tcke_clk            Minimum CKE pulse width in clock ticks.
*
*    trcd_min_clk        Minimum RAS to CAS Delay Time in clock ticks.
*    trp_min_clk         Minimum Row Precharge Delay Time in clock ticks.
*    trtp_min_clk        Minimum Internal Read to Precharge Command Delay Time in clock ticks. SPD is DDR3 only derived for DDR4.
*    tras_min_clk        Minimum Active to Precharge Delay Time in clock ticks.
*    trc_min_clk         Minimum Active to Active/Refresh Delay Time in clock ticks.
*    tfaw_min_clk        Minimum Four Activate Window Time in clock ticks.
*    txs_clk             Time for commands to exit self refresh without a locked DLL.
*                         (Refresh Recovery Delay Time in clock ticks plus 10ns).
*    txp_clk             Exit power down with DLL on to any valid command.
*    txsdll_min_clk      Minimum time for commands to exit self refresh with a locked DLL.
*    tdllk_min_clk       Minimum DLL lock time.
*    twr_min_clk         Minimum Write Recovery Time in clock ticks.
*    twtr_min_clk        Minimum Internal Write to Read Command Delay Time in clock ticks.
*    mr_wr_clk           MR bounded version of twr_min_clk, Write Recovery Time.
*    tstab_clk           Stabilization time - command buffer chip.
*    tckev_min_clk       Minimum number of DDR cycles to stay low when the CK_t/CK_c are pulled low.
*
*    trrd_min_clk        Minimum Row Active to Row Active Delay Time in clock ticks.  DDR3 only.
*    trfc_min_ps         Minimum Refresh Recovery Delay Time in clock ticks.  DDR3 only.
*
*    trrdl_min_clk       Minimum Activate to Activate Delay Time, same bank group, in clock ticks.  DDR4 only.
*    trrds_min_clk       Minimum Activate to Activate Delay Time, different bank group in clock ticks.  DDR4 only.
*    tccdl_min_clk       Minimum CAS to CAS Delay Time (Long), same bank group.  DDR4 only.
*    trfc1_min_ps        Minimum Refresh Recovery Delay Time - RFC1 in clock ticks.  DDR4 only.
*    trfc2_min_ps        Minimum Refresh Recovery Delay Time - RFC2 in clock ticks.  DDR4 only.
*    trfc4_min_ps        Minimum Refresh Recovery Delay Time - RFC4 in clock period.  DDR4 only.
*    twtrs_min_clk       Delay from start of internal write trans-action to internal read command
*                         for dif-ferent bank group. DDR4 only.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    // Common
    uint32_t cas_lat_sup;
    uint32_t taa_min_ps;
    uint32_t tck_min_ps;
    uint32_t tck_max_ps;
    uint32_t tck_ps;
    uint32_t tcke_clk;

    uint32_t trcd_min_clk;
    uint32_t trp_min_clk;
    uint32_t trtp_min_clk;
    uint32_t tras_min_clk;
    uint32_t trc_min_clk;
    uint32_t tfaw_min_clk;
    uint32_t txs_clk;
    uint32_t txp_clk;
    uint32_t txsdll_min_clk;
    uint32_t tdllk_min_clk;
    uint32_t twr_min_clk;
    uint32_t twtr_min_clk;
    uint32_t mr_wr_clk; // AKA &mc_wr in scripts
    uint32_t tstab_clk;
    uint32_t tckev_min_clk;

    // DDR3 Only
    uint32_t trrd_min_clk;
    uint32_t trfc_min_ps;

    // DDR4 Only
    uint32_t trrdl_min_clk;
    uint32_t trrds_min_clk;
    uint32_t tccdl_min_clk;
    uint32_t trfc1_min_ps;
    uint32_t trfc2_min_ps;
    uint32_t trfc4_min_ps;
    uint32_t twtrs_min_clk;
} mddr_timing_values_t;



/*!****************************************************************************
*
* @par Description
*    This type is used to collect the calculated latency values.
*
* @par Members
*
*                                  <PRE>
*    cl                  CAS latency.
*    cwl                 CAS write latency.
*    rl                  Read latency.
*    orl                 Overall read latency.
*    wl                  Write latency.
*    pl                  Parity latency.
*    tcal                CS to Command/Address Latency.
*    tdbi                DBI induced read latency. tAA_DBI in clock cycles
*                         instead of ps.
*    tpdm                RDIMM induced read latency.
*    tmod                mode register set command update delay
*    tmrd                mode register set command cycle time
*    mc_mr2_cwl          CAS Write Latency MR2 format / value.
*    mc_mr5_pl           Parity Latency MR2 format / value.
*    rcd_nladd           RDIMM/LRDIMM command buffer chip timing parameter.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint32_t cl;
    uint32_t cwl;
    uint32_t rl;
    uint32_t orl;
    uint32_t wl;
    uint32_t pl;
    uint32_t tcal;
    uint32_t tdbi;
    uint32_t tpdm;
    uint8_t tmod;
    uint8_t tmrd;
    uint8_t mc_mr2_cwl;
    uint8_t mc_mr5_pl;
    uint8_t rcd_nladd;
} mddr_latencies_t;


/*!****************************************************************************
*
* @par Description
*    This type is used to collect the values to be written to the timing
*    registers.
*
* @par Members
*
*                                  <PRE>
*    rcd_val            The timing RCD register value.
*    timing_rdwr0_val   The timing dram read write 0 register value.
*    timing_rdwr1_val   The timing dram read write 1 register value.
*    timing_rdwr2_val   The timing dram read write 2 register value.
*    timing_rdwr3_val   The timing dram read write 3 register value.
*    timing_rdwr4_val   The timing dram read write 4 register value.
*    adj_rdwr0_val      The timing adjust read write 0 register value.
*    adj_rdwr1_val      The timing adjust read write 1 register value.
*    auto_ref0_val      The timing DRAM auto refresh 0 register value.
*    auto_ref1_val      The timing DRAM auto refresh 1 register value.
*    auto_ref2_val      The timing DRAM auto refresh 2 register value.
*    adj_auto_ref_val   The timing adjust auto refresh register value.
*    auto_ref_cntl_val  The DDR auto refresh control register value.
*    pwr_down0_val      The timing DRAM power down 0 register value.
*    pwr_down1_val      The timing DRAM power down 1 register value.
*    self_ref0_val      The timing DRAM self refresh 0 register value.
*    self_ref1_val      The timing DRAM self refresh 1 register value.
*    self_ref2_val      The timing DRAM self refresh 2 register value.
*    mpsm_val           The timing DRAM MPSM register value.
*    zq0_val            The timing DRAM ZQ 0 register value.
*    zq1_val            The timing DRAM ZQ 1 register value.
*    zq_adj_val         The timing adjust ZQ register value.
*    zqcal_cntl_val     The ZQ Calibration control register value.
*    mr0_val            The timing DRAM MR0 register value.
*    mr1_val            The timing DRAM MR1 register value.
*    dq_bus_val         The timing DQ Bus register value.
*    dfi_0_val          The timing DFI 0 register value.
*    dfi_1_val          The timing DFI 1 register value.
*    odt_val            The timing ODT register value.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint32_t rcd_val;
    uint32_t timing_rdwr0_val;
    uint32_t timing_rdwr1_val;
    uint32_t timing_rdwr2_val;
    uint32_t timing_rdwr3_val;
    uint32_t timing_rdwr4_val;
    uint32_t adj_rdwr0_val[DDR_MAX_NUM_CHANS];
    uint32_t adj_rdwr1_val[DDR_MAX_NUM_CHANS];
    uint32_t auto_ref0_val;
    uint32_t auto_ref1_val;
    uint32_t auto_ref2_val;
    uint32_t adj_auto_ref_val[DDR_MAX_NUM_CHANS];
    uint32_t auto_ref_cntl_val;
    uint32_t pwr_down0_val;
    uint32_t pwr_down1_val;
    uint32_t self_ref0_val;
    uint32_t self_ref1_val;
    uint32_t self_ref2_val;
    uint32_t mpsm_val;
    uint32_t zq0_val;
    uint32_t zq1_val;
    uint32_t zq_adj_val[DDR_MAX_NUM_CHANS];
    uint32_t zqcal_cntl_val;
    uint32_t mr0_val;
    uint32_t mr1_val;
    uint32_t dq_bus_val;
    uint32_t dfi_0_val;
    uint32_t dfi_1_val;
    uint32_t dfi_2_val;
    uint32_t odt_val;
    uint32_t gear_down_val;
} mddr_timing_reg_vals_t;


/*!****************************************************************************
*
* @par Description
*    This type is used to collect the values to be written to the thermal
*    throttling control registers.
*
* @par Members
*
*                                  <PRE>
*    ddr_thermal_cntl_0_val   The thermal control 0 register value.
*    ddr_thermal_cntl_1_val   The thermal control 1 register value.
*    ddr_thermal_cntl_2_val   The thermal control 2 register value.
*    ddr_thermal_cntl_3_val   The thermal control 3 register value.
*    ddr_thermal_cntl_4_val   The thermal control 4 register value.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint32_t ddr_thermal_cntl_0_val;
    uint32_t ddr_thermal_cntl_1_val;
    uint32_t ddr_thermal_cntl_2_val;
    uint32_t ddr_thermal_cntl_3_val;
    uint32_t ddr_thermal_cntl_4_val;
} mddr_thermal_reg_vals_t;


/*!****************************************************************************
*
* @par Description
*    This type is used to collect the values to be written to the Bus
*    Utilization Monitor (BUM) control registers.
*
* @par Members
*
*                                  <PRE>
*     dcvs_cntl_val                       The DCVS control register value.
*
*     dcvs_bcqfull_high_threshold_1_val   The BCQFULL event, high threshhold, register values for each performance index.
*     dcvs_bcqfull_low_threshold_1_val    The BCQFULL event, low threshhold, register values for each performance index.
*
*     dcvs_busy_high_threshold_1_val      The BUSY event, high threshhold, register values for each performance index.
*     dcvs_busy_low_threshold_1_val       The BUSY event, low threshhold, register values for each performance index.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint32_t dcvs_cntl_val;

    uint32_t dcvs_bcqfull_high_threshold_val[DDR_BUM_PERF_IDX_MAX];
    uint32_t dcvs_bcqfull_low_threshold_val[DDR_BUM_PERF_IDX_MAX];

    uint32_t dcvs_busy_high_threshold_val[DDR_BUM_PERF_IDX_MAX];
    uint32_t dcvs_busy_low_threshold_val[DDR_BUM_PERF_IDX_MAX];
} mddr_bum_reg_vals_t;


/*!****************************************************************************
*
* @par Description
*    This type is used to collect the values to be written to the DDR
*     Control Word registers.
*
* @par Members
*
*                                  <PRE>
*    rcw0f_00          The RDIMM register control word 0f_00 value.
*    rcw7x_0x          The L/RDIMM register control word 7x_0x register value.
*    f1rc00_f0rcbx_8x  The L/RDIMM register control word fx_8x register value.
*    bc0f_00           The DB register control word BC0F-00 for LRDIMM.
*    f5bc6x_5x_f0bc6x  The DB register control word for f0bc6x, f5bc6x, f5bc5x.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint64_t rcw0f_00;
    uint64_t rcw7x_0x;
    uint64_t f1rc00_f0rcbx_8x;
    uint64_t bc0f_00;
    uint64_t f5bc6x_5x_f0bc6x;
} mddr_rcw_reg_vals_t;



/*!****************************************************************************
*
* @par Description
*    This type is used to collect the values to be written to the DDR
*    MR registers. Unique by rank in a channel.
*
* @par Members
*
*                                  <PRE>
*    mr0_data       The MR 0 register value.
*    mr1_data       The MR 1 register value.
*    mr2_data       The MR 2 register value.
*    mr3_data       The MR 3 register value.
*    mr4_data       The MR 4 register value. DDR4 0nly.
*    mr5_data       The MR 5 register value. DDR4 0nly.
*    mr6_data       The MR 6 register value. DDR4 0nly.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint16_t mr0_data;
    uint16_t mr1_data;
    uint16_t mr2_data;
    uint16_t mr3_data;
    uint16_t mr4_data;
    uint16_t mr5_data;
    uint16_t mr6_data;
} mddr_mr_reg_vals_t;



/*!****************************************************************************
*
* @par Description
*    This type is used to collect the values to be written to the memory
*    controller registers. This includes only the registers whose value is fixed
*    and common accross all memory controllers.
*
* @par Members
*
*                                  <PRE>
*    timing_regs            Structure used to collect values to be written to the
*                           timing registers.
*    dimm_slot_config_val
*    dimm_slot_addr_val
*    dimm_tech_val
*    dataflow_cntl_val
*    ddr_odt_wr_cntl_val
*    ddr_odt_rd_cntl_val
*    cmd_exec_cntl_0_val
*    cmd_exec_cntl_1_val
*    cmd_exec_cntl_2_val
*    cmd_exec_cntl_3_val
*    cmd_exec_cntl_4_val
*    cmd_exec_cntl_5_val
*    cmd_exec_cntl_6_val
*    cmd_exec_cntl_7_val
*    addr_decode_cntl_val
*    wdb_flush_wm_val
*    wdb_flush_cntl_val
*    wdb_flush_ph_val
*    int0_cntl_val
*    int1_cntl_val
*    err_cntl_val
*    err_cap_cntl_val
*    tn_token_cnt_val
*    rd_wr_pref_cntl_val
*    ddr_dfi_cntl_val
*    ddr_phy_cntl_val
*    ddr_self_ref_cntl_val
*    ddr_power_down_cntl_val
*    ddr_ca_bus_cntl_val
*    ddr_dq_bus_cntl_val
*    thermal_regs           Structure used to collect values to be written to
*                            the thermal throttling control registers.
*    bum_regs               Structure used to collect values to be written to
*                            the Bus Utilization Monitor (BUM) registers.
*    mode_regs              Structure array used to collect the values to be
*                            written to the mode registers for each rank of
*                            each channel spread accross the DIMMs.
*    phy_regs               Structure used to collect values to be written to
*                            the Phy registers.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    mddr_timing_reg_vals_t timing_regs;
    uint32_t dimm_slot_config_val[DDR_MAX_NUM_SLOTS_PER_CHAN];
    uint32_t dimm_slot_addr_val[DDR_MAX_NUM_SLOTS_PER_CHAN];
    uint32_t dimm_tech_val;
    uint32_t dataflow_cntl_val;
    uint32_t dataflow_cde_cntl_0_val;
    uint32_t dataflow_cde_cntl_1_val;
    uint32_t dataflow_cde_cntl_2_val;
    uint32_t dataflow_cde_cntl_3_val;
    uint32_t dataflow_cde_cntl_4_val;
    uint32_t dataflow_cde_cntl_5_val;
    uint32_t dataflow_cde_cntl_6_val;
    uint32_t ddr_odt_wr_cntl_val[DDR_MAX_NUM_CHANS];
    uint32_t ddr_odt_rd_cntl_val[DDR_MAX_NUM_CHANS];
    uint32_t cmd_exec_cntl_0_val;
    uint32_t cmd_exec_cntl_1_val;
    uint32_t cmd_exec_cntl_2_val;
    uint32_t cmd_exec_cntl_3_val;
    uint32_t cmd_exec_cntl_4_val;
    uint32_t cmd_exec_cntl_5_val;
    uint32_t cmd_exec_cntl_6_val;
    uint32_t cmd_exec_cntl_7_val;
    uint32_t addr_decode_cntl_val;
    uint32_t wdb_flush_wm_val;
    uint32_t wdb_flush_cntl_val;
    uint32_t wdb_flush_ph_val;
    uint32_t int0_cntl_val;
    uint32_t int1_cntl_val;
    uint32_t err_cntl_val;
    uint32_t err_cap_cntl_val;
    uint32_t ecc_err_cntl_1_val;
    uint32_t tn_token_cnt_val;
    uint32_t rd_wr_pref_cntl_val;
    uint32_t ddr_dfi_cntl_val;
    uint32_t ddr_dfi_cntl_1_val;
    uint32_t ddr_phy_cntl_val;
    uint32_t ddr_self_ref_cntl_val;
    uint32_t ddr_power_down_cntl_val;
    uint32_t ddr_ca_bus_cntl_val;
    uint32_t ddr_dq_bus_cntl_val;
    mddr_thermal_reg_vals_t thermal_regs;
    mddr_bum_reg_vals_t bum_regs;
    mddr_rcw_reg_vals_t rcw_regs[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
    mddr_mr_reg_vals_t mode_regs[DDR_MAX_NUM_CHANS][DDR_MAX_RANKS_PER_CHAN];

    // PHY register values
    mddr_phy_register_values_t phy_regs;
} mddr_register_values_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the possible configurations for the ZQ calibration type.
*
******************************************************************************/
typedef enum
{
    ZQ_SHORT,  //!< Selects a short ZQ calibration.
    ZQ_LONG,   //!< Selects a long ZQ calibration.
    ZQ_INIT    //!< Selects an ZQ initialization calibration.
}zq_cal_type_t;




/******************************************************************************
* Global Variables
******************************************************************************/

/*!****************************************************************************
*
* @defgroup mddr_internal_globals MDDR Internal Globals
*
* @par Description
*    Get access to the internal global variables.
*
* @{
******************************************************************************/
extern spd_dimm_config_t mddr_dimm_configs[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
extern mddr_common_cfg_t common_cfg;
extern mddr_timing_values_t mddr_timing_vals;
extern mddr_register_values_t mddr_reg_vals;
extern mddr_latencies_t latencies;
extern mddr_si_chan_t si_data[DDR_MAX_NUM_CHANS];

extern uint64_t mddr_base_addrs[DDR_MAX_NUM_CHANS];
extern uint8_t hddrss[DDR_MAX_NUM_CHANS];
extern uint8_t num_chans_poped;
extern uint8_t num_dimms_per_chan_poped;
extern uint32_t mddr_valid_ranks;
extern uint32_t mddr_combined_valid_ranks;
extern uint32_t mem_freq_mhz;
extern uint32_t ddr_rate;
extern uint32_t mem_freq_ps;
extern uint32_t mddr_xo_freq_khz;
extern target_mode_e platform_mode;

/* @} */


/******************************************************************************
* Macros
******************************************************************************/

/*!****************************************************************************
*
* @defgroup mddr_clk_converters MDDR Clock Converters
*
* @par Description
*    Set of macros to convert between clock rates and time.
*
* @{
******************************************************************************/
#define MDDR_MHZ_TO_PS(freq_mhz)(COM_MHZ_TO_PS(freq_mhz))
#define MDDR_KHZ_TO_PS(freq_khz)(COM_KHZ_TO_PS(freq_khz))
#define MDDR_PS_TO_MHZ(ps)(COM_PS_TO_MHZ(ps))
#define MDDR_PS_TO_KHZ(ps)(COM_PS_TO_KHZ(ps))
/* @} */



/******************************************************************************
* Function Prototypes
******************************************************************************/

// mddr_init.c
uint32_t max_of_clk_ps(uint32_t i_clks, uint32_t i_ps, uint32_t freq_ps);
uint32_t mddr_get_num_clocks(uint32_t txx_ps, uint32_t freq_ps);
void mddr_set_reg(uint64_t mddr_reg_addr, char *reg_name_str, uint32_t reg_val);
uint32_t mddr_get_reg(uint64_t mddr_reg_addr, char *reg_name_str);
void mddr_rmw_reg(uint64_t mddr_reg_addr, char *reg_name_str, uint32_t mask, uint32_t set_bits);
void mddr_rd_chk_reg(uint64_t mddr_base_addr, uint64_t s_addr_offset, uint64_t mask, uint32_t value, uint32_t to_ms);
void mddr_wait_for_clear(uint64_t mddr_base_addr, uint64_t mddr_reg_addr, uint32_t reg_mask, uint8_t max_loops);
void mddr_wait_for_set(uint64_t mddr_base_addr, uint64_t mddr_reg_addr, uint32_t reg_mask, uint8_t max_loops);
bool mddr_check_chan_populated(uint8_t ddr_chan);
uint8_t mddr_get_dimm_per_chan_cnt(void);


// mddr_mc_init.c
unsigned mddr_mc_init(mddr_settings_t *mddr_settings_ptr, uint8_t channel);
unsigned mddr_mc_wd_init(mddr_settings_t *mddr_settings_ptr, uint8_t channel);
unsigned mddr_mc_dram_init(uint8_t channel);
unsigned mddr_mc_post_init(mddr_settings_t *mddr_settings_ptr, uint8_t channel);
void mddr_mc_get_reg_vals(soc_hw_version_t soc_hw_version, mddr_common_cfg_t *common_ptr,
                                  mddr_settings_t *mddr_settings_ptr, mddr_latencies_t *latencies_ptr);
void mddr_mc_assert_reset(uint64_t mddr_base_addr);

void mddr_mc_get_thermal_control_reg_vals(mddr_therm_throttle_settings_t *therm_throttle_settings_ptr);
void mddr_mc_set_thermal_control_reg_vals(uint64_t mddr_base_addr);
void mddr_mc_enable_thermal_control(uint64_t mddr_base_addr);
void mddr_mc_disable_thermal_control(uint64_t mddr_base_addr);

void mddr_mc_get_bum_reg_vals(mddr_settings_t *mddr_settings_ptr);
void mddr_mc_set_bum_reg_vals(uint64_t mddr_base_addr);
void mddr_mc_check_bum_thresholds(mddr_bum_event_settings_t *bum_event_settings_ptr, uint8_t ddr_bum_perf_idx);

void mddr_mc_wait_us(uint64_t mddr_base_addr, uint16_t num_us);
void mddr_mc_wait_ns(uint64_t mddr_base_addr, uint16_t num_ns);
void mddr_mc_set_hw_timer(uint64_t mddr_base_addr, uint16_t delay_clocks, bool use_XO);

void mddr_mc_exec_dimm_init(uint8_t ddr_chan, uint8_t slot);
void mddr_mc_set_dimm_slot_regs(uint64_t mddr_base_addr, uint8_t slot, uint32_t dimm_slot_config_val, uint32_t dimm_slot_addr_val);
void mddr_mc_slot_ready(uint64_t mddr_base_addr, uint8_t slot);
void mddr_mc_cw_write(uint64_t mddr_base_addr, uint8_t slot, uint8_t cw_addr, uint16_t cw_data);

void mddr_mc_wd_flush_write_data_buff(uint64_t mddr_base_addr);
void mddr_mc_wd_wdb_clean_check_complete(uint64_t mddr_base_addr);
void mddr_mc_wd_enter_self_refresh(uint64_t mddr_base_addr);
void mddr_mc_wd_exit_self_refresh(uint64_t mddr_base_addr);
void mddr_mc_wd_post_reinit(uint8_t ddr_chan);
void mddr_mc_wd_wait_for_self_refresh(uint64_t mddr_base_addr);
void mddr_mc_wd_enable_periodic_auto_refresh(uint64_t mddr_base_addr);


// mddr_mc_timing.c
void mddr_mc_set_timing_reg_vals(uint64_t mddr_base_addr, uint8_t ddr_chan);


// mddr_phy_init.c
void mddr_phy_get_reg_vals(mddr_settings_t *mddr_settings_ptr);

// mddr_phy_train.c
uint16_t mddr_phy_get_average_dram_vref(uint8_t ddr_chan, uint8_t cs);


/*****************************************************************************/
#endif
