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
* @file mddr_init.c
*
* @par Description:
*    This module provides the top level functionality to initialize the Monaco
*    DDR subsystem. Includes MDDR common utilities that are to be used across
*    MDDR subcomponents.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <target/ddr.h>
//#include <target/clk.h>

/******************************************************************************
* Defined Constants
******************************************************************************/
#define GCCMS_MDDRN_2X_CBCR_CLK_ENABLE___M            0x1

// JESD21-C 8.1.21 table 45 and 46
#define DDR3_CL_START                     0x4         // min CAS Latency for DDR3
#define DDR4_CL_START_LR                  0x7         // min CAS Latency for DDR4 low range
#define DDR4_CL_START_HR                  0x17        // min CAS Latency for DDR4 high range

#define DDR3_CL_MAX                       0x18        // max CAS Latency for DDR3
#define DDR4_CL_MAX_LR                    0x24        // max CAS Latency for DDR4 low range
#define DDR4_CL_MAX_HR                    0x34        // max CAS Latency for DDR4 high range

#define DDR3_TAAMAX                       (20 * PICO_SEC_PER_NANO_SEC)    // 20ns in ps
#define DDR4_TAAMAX                       (18 * PICO_SEC_PER_NANO_SEC)    // 18ns in ps

#define DDR3_DEFAULT_CAS_LATENCY          6
#ifdef CONFIG_PRE_Z1
#define DDR4_DEFAULT_CAS_LATENCY          20
#else
#define DDR4_DEFAULT_CAS_LATENCY          10
#endif


#define CKE_SINGLE                        0x1
#define CKE_MULTI                         0x3
#define CKE_PER_SLOT                      0x2


#define DUMMY_VAL                         0x0

#define SLOW_DDR_CHAN                     1           // Logical channel 1 maps to HDDRSS2 which did not close timing
                                                      //  at 1200MHz and should not be operated above 1066MHz.
/******************************************************************************
* Global Variables
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    Internal copy of the structure that provided all the high-level
*     configuration controls used to adjust the MDDR subsystem initialization.
*
******************************************************************************/
mddr_settings_t mddr_settings;


/*!****************************************************************************
*
* @par Description
*    Scratch pad buffer used to temporarily store SPD data while it is being
*    processed. The allocation is twice the block size since DDR4 uses two
*    256 byte blocks of Serial EEPROM.
*
******************************************************************************/
uint8_t spd_scratch_pad[SPD_MAX_SERIAL_EEPROM_SIZE];


/*!****************************************************************************
*
* @par Description
*    Array used to collect the SPD based configuration information for all
*    DIMMs populated in the MDDR sub-system.
*
******************************************************************************/
spd_dimm_config_t mddr_dimm_configs[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];


/*!****************************************************************************
*
* @par Description
*    Coalesced version of the SPD based configuration information common for all
*    DIMMs populated in the MDDR sub-system.
*
******************************************************************************/
mddr_common_cfg_t common_cfg;


/*!****************************************************************************
*
* @par Description
*    Structure used to collect timing values based on the timing parameters
*    extracted from the SPD of the DIMMs populated in the MDDR sub-system.
*
******************************************************************************/
mddr_timing_values_t mddr_timing_vals;



/*!****************************************************************************
*
* @par Description
*    Structure used to collect the values to be written to the memory
*    controller registers. This includes only the register whose value is
*    fixed and common accross all memory controllers.
*
******************************************************************************/
mddr_register_values_t mddr_reg_vals;



/*!****************************************************************************
*
* @par Description
*    Structure used to collect DDR latencies derived from the DIMM
*    configurations and memory controller settings.
*
******************************************************************************/
mddr_latencies_t latencies;


/*!****************************************************************************
*
* @par Description
*    Structure used to collect platform specific SI adjustments for each DDR
*    channel. Pre-initialized with data for SOD single DIMM @1866 MTS or less.
*
******************************************************************************/
extern mddr_si_chan_t si_data[DDR_MAX_NUM_CHANS];

/*!****************************************************************************
*
* @par Description
*    Structure used to collect LRDIMM Host, databuffer and DRAM interface
*    SI values. This is defined for the maxinum number of supported DDR channels.
*
******************************************************************************/
mddr_lr_db_si_chan_t lr_db_si_data[DDR_MAX_NUM_CHANS];


/*!****************************************************************************
*
* @par Description
*    Clkgen SSC, Non-SSC initialization for the frequency pool
*
******************************************************************************/
// Non SSC Values                                                     625   660   800   933   1066  1200  1333  1467  1600
static const uint32_t reg_dec_start_mode0[DDR_FREQ_IDX_MAX]       = { 0xEA, 0xF7, 0xC8, 0xE9, 0x0A, 0x2C, 0x2B, 0xDC, 0xF0 };
static const uint32_t reg_dec_start_msb_mode0[DDR_FREQ_IDX_MAX]   = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00 };
static const uint32_t reg_div_frac_start1_mode0[DDR_FREQ_IDX_MAX] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCD, 0xCD, 0x00 };
static const uint32_t reg_div_frac_start2_mode0[DDR_FREQ_IDX_MAX] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0x00 };
static const uint32_t reg_div_frac_start3_mode0[DDR_FREQ_IDX_MAX] = { 0x06, 0x08, 0x00, 0x04, 0x08, 0x00, 0x0E, 0x00, 0x00 };
static const uint32_t reg_hsclk_sel1[DDR_FREQ_IDX_MAX]            = { 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x05, 0x01, 0x01 };
static const uint32_t reg_lock_cmp1_mode0[DDR_FREQ_IDX_MAX]       = { 0x80, 0x33, 0x00, 0xA8, 0x51, 0x00, 0xA8, 0x56, 0x00 };
static const uint32_t reg_lock_cmp2_mode0[DDR_FREQ_IDX_MAX]       = { 0x0C, 0x0D, 0x10, 0x12, 0x15, 0x18, 0x1A, 0x1D, 0x20 };

// SSC Values                                                         625   660   800   933   1066  1200  1333  1467  1600
static const uint32_t ssc_dec_start_mode0[DDR_FREQ_IDX_MAX]       = { 0xEA, 0xF7, 0xC8, 0xE9, 0x0A, 0x2B, 0x2B, 0xDC, 0xEF };
static const uint32_t ssc_dec_start_msb_mode0[DDR_FREQ_IDX_MAX]   = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00 };
static const uint32_t ssc_div_frac_start1_mode0[DDR_FREQ_IDX_MAX] = { 0x00, 0x3F, 0x29, 0xEC, 0xAF, 0x3D, 0x1A, 0x89, 0x64 };
static const uint32_t ssc_div_frac_start2_mode0[DDR_FREQ_IDX_MAX] = { 0x40, 0x35, 0x5C, 0x40, 0x25, 0x0A, 0xD7, 0x18, 0x3B };
static const uint32_t ssc_div_frac_start3_mode0[DDR_FREQ_IDX_MAX] = { 0x05, 0x07, 0x0F, 0x03, 0x07, 0x0F, 0x0D, 0x00, 0x0F };
static const uint32_t ssc_hsclk_sel1[DDR_FREQ_IDX_MAX]            = { 0x06, 0x06, 0x02, 0x02, 0x02, 0x02, 0x05, 0x01, 0x01 };
static const uint32_t ssc_lock_cmp1_mode0[DDR_FREQ_IDX_MAX]       = { 0x80, 0x33, 0x00, 0xA8, 0x51, 0x00, 0xA8, 0x56, 0x00 };
static const uint32_t ssc_lock_cmp2_mode0[DDR_FREQ_IDX_MAX]       = { 0x0C, 0x0D, 0x10, 0x12, 0x15, 0x18, 0x1A, 0x1D, 0x20 };

// SSC Specific Values                                                625   660   800   933   1066  1200  1333  1467  1600
static const uint32_t ssc_en_center[DDR_FREQ_IDX_MAX]             = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
static const uint32_t ssc_step_size1[DDR_FREQ_IDX_MAX]            = { 0x65, 0x17, 0x93, 0x56, 0x18, 0xDD, 0xDC, 0xA3, 0xB1 };
static const uint32_t ssc_step_size2[DDR_FREQ_IDX_MAX]            = { 0x0C, 0x0D, 0x0A, 0x0C, 0x0E, 0x0F, 0x0F, 0x0B, 0x0C };
static const uint32_t ssc_step_size3[DDR_FREQ_IDX_MAX]            = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint32_t ssc_per1[DDR_FREQ_IDX_MAX]                  = { 0x4D, 0x4D, 0x4D, 0x4D, 0x4D, 0x4D, 0x4D, 0x4D, 0x4D };
static const uint32_t ssc_per2[DDR_FREQ_IDX_MAX]                  = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };


extern uint64_t mddr_base_addrs[DDR_MAX_NUM_CHANS];
extern uint8_t hddrss[DDR_MAX_NUM_CHANS];

/*!****************************************************************************
*
* @par Description
*    The Number of channels populated in the MDDR sub-system.
*
******************************************************************************/
uint8_t num_chans_poped = 0;


/*!****************************************************************************
*
* @par Description
*    The Number of channels populated in the MDDR sub-system.
*
******************************************************************************/
uint8_t num_dimms_per_chan_poped = 0;


/*!****************************************************************************
*
* @par Description
*    Set of flags used to indicate the available ranks in a channel. The same
*    ranks must be present in all active channels.
*
******************************************************************************/
uint32_t mddr_valid_ranks;


/*!****************************************************************************
*
* @par Description
*    Combined set of flags used to indicate the available ranks in a channel.
*    Combines two chip selects from the 1st slot with the 2 chip selects from
*    2nd slot. The PHY only supports 4 chip selects so they have to be combined
*    this way for specific MC register writes to align it with the PHY.
*
******************************************************************************/
uint32_t mddr_combined_valid_ranks;


/*!****************************************************************************
*
* @par Description
*    Memory frequency in MHz.
*
******************************************************************************/
uint32_t mem_freq_mhz;


/*!****************************************************************************
*
* @par Description
*    DDR rate in MT/s.
*
******************************************************************************/
uint32_t ddr_rate;


/*!****************************************************************************
*
* @par Description
*    Memory frequency in picoseconds.
*
******************************************************************************/
uint32_t mem_freq_ps;


/*!****************************************************************************
*
* @par Description
*    xo frequency in MHz.
*
******************************************************************************/
uint32_t mddr_xo_freq_khz;


/*!****************************************************************************
*
* @par Description
*    Flag indicating if register accesses reporting should be formatted to
*     match the scripts.
*
******************************************************************************/
bool reg_report = false;


/*!****************************************************************************
*
* @par Description
*    Local copy of the indication of the platform being executed on. Provided
*     during initialization.
*
******************************************************************************/
target_mode_e platform_mode;


/******************************************************************************
* Macros
******************************************************************************/



/******************************************************************************
* Function Prototypes
******************************************************************************/

unsigned mddr_verify_dimms(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_get_clock_period_timing_val(void);
uint32_t mddr_get_derived_txs_timing_val(uint32_t trfc_min_ps);
uint32_t mddr_get_derived_txsdll_timing_val(void);
uint32_t mddr_get_derived_tdllkmin_timing_val(void);
uint32_t mddr_get_derived_tstab_timing_val(void);
uint32_t mddr_get_derived_tckevmin_timing_val(void);
uint32_t mddr_get_cas_latency(mddr_common_cfg_t *common_cfg_ptr);

//
// The following prototypes are for functions that directly manipulate GCC HW funcionality
//  ouside the MDDR Subsystem. These need to be replaced with the appropriate external
//  hooks when not running in a baremetal environment.
//
//! @todo -GPK- Direct GCC block accesses : Replace with appropriate external hooks for CoreBSP integration
void mddr_enable_chan_gcc_ahb_clock(uint8_t ddr_chan);
#ifdef CONFIG_TESTOS_EMU
void mddr_presil_set_ddr_clk_mux(uint8_t ddr_chan);
#endif
void mddr_verify_clk_on(uint64_t reg_addr, char *reg_name_str);
void mddr_clkgen_init(mddr_settings_t *mddr_settings_ptr, uint64_t mddr_base_addr, uint8_t ddr_chan);


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
*    mode               Mode of the target being executed on. Used to provide
*                        simulated SPD for Emulation and simulation environments.
*                        [SILICON|RUMI42|RUMI48|SIM|SIM_RUMI42|SIM_RUMI48]
*                                  @param
*    soc_hw_version     Provides the HW version of the target SoC.
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
*
* @return
*    The status indicating the level of success in initializing the memory controllers.
*
* @author
*    gkowis, lchavani
*
******************************************************************************/
unsigned mddr_init(target_mode_e mode, soc_hw_version_t soc_hw_version, mddr_settings_t *mddr_settings_ptr)
{
    unsigned status = COM_OK;
    uint8_t ddr_chan;
    uint16_t max_1dpc_freq_hw = MAX_1DPC_CLK;    // Max clock for 1DIMM per ch poped supported by hardware
    uint16_t max_2dpc_freq_hw = MAX_2DPC_CLK;    // Max clock for 2DIMMs per ch poped supported by hardware
    uint16_t max_dimm_freq;

    // Check for invalid MDDR settings input arguments.  Invalid combinations that
    //  result in overrides will be checked later.
    status |= mddr_validate_input(mddr_settings_ptr);

    //  Record the platform being executed on.
    platform_mode = mode;

    // Get the DIMM configuration info from SPD
    mddr_get_dimm_configs();

    // Release the GCC reset for all the populated channels
    if (platform_mode != SILICON)
    {
        for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
        {
            if (mddr_check_chan_populated(ddr_chan))
            {
                mddr_update_chan_gcc_reset(ddr_chan, (uint8_t)DEASSERT_GCC_RESET);
            }
        }
    }

    num_dimms_per_chan_poped = mddr_get_dimm_per_chan_cnt();


    // Determine the DDR frequency to be used
    if (num_dimms_per_chan_poped == 1)
    {
        // Choose the minimum of software DDR clock max and hardware supported DDR clock max
        if (mddr_settings_ptr->max_1dimm_freq_mhz > max_1dpc_freq_hw)
        {
            monaco_log(CRITICAL,"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            monaco_log(CRITICAL,"ADJUST: 1 DIMM per channel populated, software max DDR Clock reduced to %d MHz.\n", max_1dpc_freq_hw);
            monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");

            mddr_settings_ptr->max_1dimm_freq_mhz = max_1dpc_freq_hw;
        }

        // Choose the minimum of desired DDR clock and software DDR clock max
        if (mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] > mddr_settings_ptr->max_1dimm_freq_mhz)
        {
            monaco_log(CRITICAL,"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            monaco_log(CRITICAL,"ADJUST: 1 DIMM per channel populated, desired DDR Clock (%d MHz) exceeds software max DDR Clock (%d MHz) \n",
                                  mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1], mddr_settings_ptr->max_1dimm_freq_mhz);
            monaco_log(CRITICAL,"DDR Clock reduced to %d MHz.\n", mddr_settings_ptr->max_1dimm_freq_mhz);
            monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");

            mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] = mddr_settings_ptr->max_1dimm_freq_mhz;
        }
    }
    else if (num_dimms_per_chan_poped > 1)
    {
        // Choose the minimum of software DDR clock max and hardware supported DDR clock max
        if (mddr_settings_ptr->max_2dimm_freq_mhz > max_2dpc_freq_hw)
        {
            monaco_log(CRITICAL,"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            monaco_log(CRITICAL,"ADJUST: 2 DIMMs per channel populated, software max DDR Clock reduced to %d MHz.\n", max_2dpc_freq_hw);
            monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");

            mddr_settings_ptr->max_2dimm_freq_mhz = max_2dpc_freq_hw;
        }

        // Choose the minimum of desired DDR clock and software DDR clock max
        if (mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] > mddr_settings_ptr->max_2dimm_freq_mhz)
        {
            monaco_log(CRITICAL,"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
            monaco_log(CRITICAL,"ADJUST: 2 DIMMs per channel populated, desired DDR Clock (%d MHz) exceeds software max DDR Clock (%d MHz) \n",
                                  mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1], mddr_settings_ptr->max_2dimm_freq_mhz);
            monaco_log(CRITICAL,"DDR Clock reduced to %d MHz.\n", mddr_settings_ptr->max_2dimm_freq_mhz);
            monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");

            mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] = mddr_settings_ptr->max_2dimm_freq_mhz;
        }
    }


    // Get the greatest common DIMM clock rate supported.
    max_dimm_freq = mddr_get_dimms_max_clk();

    // Downshift the frequency to the highest common clock rate supported
    //  by the populated DIMMs as long as the overclocking override has not
    //  been enabled.
    if((mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] > max_dimm_freq) &&
       (!mddr_settings_ptr->allow_overclocking))
    {
        // The speed grade for the populated DIMMs is below the requested frequency so
        //  drop the overall DDR clock rate to the highest supported by all DIMMs.
        monaco_log(CRITICAL,"\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        monaco_log(CRITICAL,"ADJUST: DIMMs speed grade below requested frequency. DDR Clock reduced to %d MHz.\n", max_dimm_freq);
        monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
        mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] = max_dimm_freq;
    }


    //
    // Setup common clock values
    //
    status |= mddr_set_clock_frequency(mddr_settings_ptr);


    // Use the first frequency for now since dynamic frequency switch is not supported yet.
    mem_freq_mhz = mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1];

    // Set up the other top level frequency parameters
    mddr_xo_freq_khz = mddr_settings_ptr->mddr_xo_freq_khz;
    mem_freq_ps = MDDR_MHZ_TO_PS(mem_freq_mhz);
    ddr_rate = mem_freq_mhz * 2;

    status |= mddr_verify_dimm_combination_configs(mddr_settings_ptr);


    // All the 2TCK related overides are to be done here before we obtain the SI since LRDIMM gap spacings
    // are dependant on 2TCK
    if(ddr_rate < 2400)
    {
       if (mddr_settings_ptr->ddr4_2t_preamble_mode != DDR4_2T_DISABLE)
        {
           monaco_log(HIGH, "Ignoring write/read 2T preamble feature since data rate<2400, data rate = %d\n", ddr_rate);
           // write/read 2tCK preamble (0=disable, 1=2T read, 2=2T write, 3=2T write & read)
           mddr_settings_ptr->ddr4_2t_preamble_mode = DDR4_2T_DISABLE;
        }
    }
    else
    {
        if (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_DISABLE)
        {
            monaco_log(HIGH,"\nSetting DDR4 2T Preamble to READ configuration since data rate>=2400, data rate = %d\n", ddr_rate);
            mddr_settings_ptr->ddr4_2t_preamble_mode = DDR4_2T_READ;
        }
        else if (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE)
        {
            monaco_log(HIGH,"\nSetting DDR4 2T Preamble to WRITE_READ configuration since data rate>=2400, data rate = %d\n", ddr_rate);
            mddr_settings_ptr->ddr4_2t_preamble_mode = DDR4_2T_WRITE_READ;
        }
     }

    // Get the SI data for the platform.
    if (platform_mode != PALLADIUM_Z1)
        mddr_get_si(mddr_settings_ptr);

    if(status == COM_OK)
    {
        // Force disable DDR4 modes that are frequency dependent.
        //  Table 106, pg 204 JEDEC 79-4A
        if(common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
        {
            if(ddr_rate < 2666)
            {
                if (mddr_settings_ptr->ddr4_wr_crc_en)      // TODO: In Table 140 of JEDEC 79-4B, write CRC is supported
                {
                    monaco_log(HIGH, "Ignoring write CRC enable feature since data rate<2666, data rate = %d\n", ddr_rate);
                    mddr_settings_ptr->ddr4_wr_crc_en = false;
                }

                if (mddr_settings_ptr->ddr4_geardown_mode_en)
                {
                    monaco_log(HIGH, "Ignoring geardown mode since data rate<2666, data rate = %d\n", ddr_rate);
                    mddr_settings_ptr->ddr4_geardown_mode_en = false;
                }
            }
        }

        if ((!common_cfg.has_ecc) && (mddr_settings_ptr->disable_ecc == false))
        {
            monaco_log(HIGH, "Ignoring ECC feature since DIMMs do not support ECC\n");
            mddr_settings_ptr->disable_ecc = true;
        }

        if((common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM)&&(mddr_settings_ptr->ca_parity == CA_PARITY_DRAM))
        {
            monaco_log(HIGH, "Ignoring DRAM CA Parity feature with DIMM CA Parity disabled for RDIMMs\n");
            mddr_settings_ptr->ca_parity = CA_PARITY_DISABLE;
        }

        // This setting is ignored by hardware whenever 1 pair of channels is
        //  populated, however, we only print a warning and if a setting other
        //  than the default is detected.
        if((num_chans_poped <= 2)&&(mddr_settings_ptr->ddr_granule != DDR_DIST_GRANULE_256B))
        {
            monaco_log(HIGH, "Ignoring channel interleaving granule setting when only one pair of channels is populated\n");
            // Warn and ignore but do not override because the Ring Switches have already been programmed
        }

        // DIMM interleaving is only valid if both slots populated and they have the same amount of memory.
        if ((mddr_settings_ptr->dimm_intlv_en) && (num_dimms_per_chan_poped != DDR_MAX_NUM_SLOTS_PER_CHAN))
        {
            // Override the interleaving setting
            monaco_log(HIGH,"Ignoring DIMM Interleave mode since only 1 DIMM is populated per channel\n");
            mddr_settings_ptr->dimm_intlv_en = false;
        }

        if ((mddr_settings_ptr->dimm_intlv_en) && (common_cfg.slot_config[0].dimm_size_mb != common_cfg.slot_config[1].dimm_size_mb))
        {
            // Override the interleaving setting
            monaco_log(HIGH,"Ignoring DIMM Interleave mode since populated DIMMs have different amounts of memory\n");
            mddr_settings_ptr->dimm_intlv_en = false;
        }

        if (platform_mode != SILICON)
        {
            if(mddr_settings_ptr->periodic_zq_cal_en)
            {
                monaco_log(HIGH, "Ignoring periodic ZQ cal enable setting on emulation\n");
                mddr_settings_ptr->periodic_zq_cal_en = false;
            }

            if(mddr_settings_ptr->dfi_lp_mode == DFI_LP_SR_ENA_LP2_ENA)
            {
                monaco_log(HIGH, "Ignoring DFI LP2 enable setting on emulation\n");
                mddr_settings_ptr->dfi_lp_mode = DFI_LP_SR_ENA;
            }

            if(mddr_settings_ptr->dfi_lp_mode == DFI_LP_SR_PD_ENA_LP2_ENA)
            {
                monaco_log(HIGH, "Ignoring DFI LP2 enable setting on emulation\n");
                mddr_settings_ptr->dfi_lp_mode = DFI_LP_SR_PD_ENA;
            }

            if(mddr_settings_ptr->therm_throttle_en)
            {
                monaco_log(HIGH, "Ignoring Thermal Throttle enable setting on emulation\n");
                mddr_settings_ptr->therm_throttle_en = false;
            }

			if(!mddr_settings_ptr->disable_ecc)
            {
                monaco_log(HIGH, "ECC scrub disabled for emulation due to the time consumedn\n");
                mddr_settings_ptr->disable_ecc = true;
            }
            // Disabled for Emulation
            mddr_settings_ptr->auto_self_refresh_en = false;
            mddr_settings_ptr->auto_power_down_en = false;
            // mddr_settings_ptr->therm_throttle_en = false;    // remove redundant setting


        }


        mddr_get_combined_timing_vals(mem_freq_ps);
        mddr_get_latency_vals(&common_cfg, mddr_settings_ptr, &latencies);

        // Get the clock enables for the manual CKE operations.
        mddr_get_slots_ck_cke();

        // Releases the resets to allow for clean PHY reset.
        mddr_release_chan_gcc_resetr(mddr_settings_ptr);

        // Update the compression settings (do this before building the registers)
        mddr_update_compression_settings(&common_cfg, mddr_settings_ptr);

        // Get common fixed register values.
        mddr_mc_get_reg_vals(soc_hw_version, &common_cfg, mddr_settings_ptr, &latencies);

        mddr_phy_get_reg_vals(mddr_settings_ptr);

        for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
        {
            if (mddr_check_chan_populated(ddr_chan))
            {

#ifndef CONFIG_PRE_HAPS
                // Initialize the memory controller
                status |= mddr_mc_init(mddr_settings_ptr, ddr_chan);
#endif

#ifndef CONFIG_TESTOS_EMU
                // Initialize the PHY
                status |= mddr_phy_init(ddr_chan);

                // PHY training
#if MDDR_CONFIG_ENHANCED_TRAINING
				status |= mddr_phy_enhanced_training(mddr_settings_ptr, ddr_chan);
#else
                status |= mddr_phy_train(mddr_settings_ptr, ddr_chan);
#endif
#endif

#ifndef CONFIG_PRE_HAPS
                // Controller DRAM initialization
                status |= mddr_mc_dram_init(ddr_chan);
#endif

                if (soc_hw_version.major_version < SOC_HW_MAJOR_VERSION_2)
                {
                    // Workaround for QDF2400 Erratum 62.
                    // Enable Patrol Scrub if Compression is enabled.
                    // Patrol Scrub clears the internal state that prevents entering Self-Refresh and Power Down modes.
                    if ((mddr_settings_ptr->comp_settings.comp_mode != DDR_COMP_DISABLED) && (mddr_settings_ptr->disable_patrol_scrub))
                    {
                        monaco_log(HIGH, "Enabling patrol scrub to workaround QDF2400 Erratum 62.\n");
                        mddr_settings_ptr->disable_patrol_scrub = false;
                    }
                }

                // Enable DIMM Critical Temperature event_n [CR65]
                status |= spd_ts_smbus_init(mddr_settings_ptr, ddr_chan);

#ifndef CONFIG_PRE_HAPS
                // Controller post initialization
                status |= mddr_mc_post_init(mddr_settings_ptr, ddr_chan);
#endif
            }
            else
            {
                mddr_lockdown_unused_chan(ddr_chan);
            }
        }
    }
    else
    {
        monaco_log(CRITICAL, " ERROR : The MDDR Subsystem could not be initialized. \n");
    }

    // Copy the initialization settings. Follows the sub-component initializiations
    //  to reflect any overrides imposed during initialization.
    mddr_record_init_parms(mddr_settings_ptr);

    return status;
}


#if 0
/*!****************************************************************************
*
* @par Description:
*    This function performs the watchdog reset graceful stop sequence.
*     WD reset sequence steps 3 through 5.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_wd_reset_graceful_stop(void)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;


    if(common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM)
    {
        for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
        {
            chan_populated = mddr_check_chan_populated(ddr_chan);

            if(chan_populated)
            {
                // Get the base address for the channel
                mddr_base_addr = mddr_base_addrs[ddr_chan];

                // 3. Wait for self-refresh
                mddr_mc_wd_wait_for_self_refresh(mddr_base_addr);

                // 4. (For RDIMM) Need to place both DIMM's CK and CK_b to low when the clock is stopped
                mddr_phy_wd_graceful_stop(mddr_base_addr);

                // 5. (For RDIMM) Disable CK driver. This will make both CK and CK_b be pulled to low.
                mddr_phy_wd_disable_ck(mddr_base_addr);

                // -GPK- This looks to have been missing in the HPG since it is reenabled later.
                //   Per Liyong it was skipped intentionally to limit SW interactions is a time limited sequence.
                //   May need to be removed to speed up the sequence.
                // same as 33. Pause DDR PHY's MDL calibrations
                //    D{0..5}_DDRPHY_PIR[DCALPSE] = 1
                mddr_phy_wd_pause_mdl_cal(mddr_base_addr);

                // Don't need since it inhibited normally per default overrides from Vishal
                // 34. Enable DDR PHY's VT inhibit
                //    D{0..5}_DDRPHY_PGCR6[INHVT] = 1
                //mddr_phy_enable_vt_inhibit(mddr_base_addr);
            }
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function performs the watchdog reset phy reactivation.
*     WD reset sequence steps 12 through 25 and 41 through 54.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_wd_reset_phy_reactivate(void)
{

    uint8_t ddr_chan;
    uint64_t mddr_base_addr;
    bool chan_populated;


    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Get the base address for the channel
            mddr_base_addr = mddr_base_addrs[ddr_chan];

            // 12. Relock DDR PHY's PLL
            // D{0..5}_DDRPHY_PLLCR[GSHIFT] = 0
            // D{0..5}_DDRPHY_PLLCR[RGSHIFT] = 0
            mddr_phy_wd_relock_pll(mddr_base_addr);

            // 13. Wait max(t_relock1, t_relock2) time. The t_relock1 is TBD. The t_relock2 is TBD. The maximum of them is expected to be less than 2us.
            mddr_mc_wait_us(mddr_base_addr, 2);


            // 14. Re-enable the MDL calibration.
            mddr_phy_wd_reenable_mdl_cal(mddr_base_addr);


            // 15. Disable VT inhibit
            // Don't need since it inhibited normally per default overrides from Vishal
            //mddr_phy_disable_vt_inhibit(mddr_base_addr);


            // 16. (For RDIMM) Enable CK driver to toggle CK and CK_b
            mddr_phy_wd_enable_ck(mddr_base_addr);


            // 17. (For RDIMM) Disable CK ODT pulldown to enable clock toggles
            //     D{0..5}_DDRPHY_ACIOCR0[CKODT] = 0
            mddr_phy_wd_disable_ck_odt(mddr_base_addr); // undo part of mddr_phy_wd_graceful_stop()



            // 18. Restore the overriden ODT impedance values
            //      D{0..5}_DDRPHY_ZQ{0..1}DR[ZDATA][27:21] =
            //      D{0..5}_DDRPHY_ZQ{0..1}DR[13:7] *
            //          (desired pullup drive strength in ohms /
            //           desired pullup ODT termination in ohms);
            //      D{0..5}_DDRPHY_ZQ{0..1}DR[ZDATA][20:14] = 0
            mddr_phy_set_zqndr(mddr_base_addr, ddr_chan); // undo other part of mddr_phy_wd_graceful_stop()


            // 19. Exit the DRAM from the self-refresh mode. See section 1.19.5.
            mddr_mc_wd_exit_self_refresh(mddr_base_addr);


            // 20. Assert reset to the DDR PHY's read data FIFOs
            //  D{0..5}_DDRPHY_PGCR0[PHYFRST] = 0
            mddr_phy_assert_read_data_fifo_reset(mddr_base_addr);


            // 21. Wait at least 16 DDR clock cycles, disable DDR PHY's static read response
            mddr_phy_wd_disable_static_read_response(mddr_base_addr);


            // 22. Deassert the DDR PHY's read FIFOs reset
            //  D{0..5}_DDRPHY_PGCR0[PHYFRST] = 1
            mddr_phy_deassert_read_data_fifo_reset(mddr_base_addr);


            // 23. Enable DDR PHY's static read mode
            //  D{0..5}_DDRPHY_PGCR3[RDMODE] = 'b01
            mddr_phy_wd_enable_static_read_mode(mddr_base_addr);

            // 24. Enable the memory controller to accept DFI control signals from the DDR PHY.
            // 25. Enable the memory controller to accept QSB commands. Set the following fields based on the availability of the DIMM slots.
            mddr_mc_wd_post_reinit(ddr_chan);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function performs the watchdog reset preparation for reset.
*     WD reset sequence steps 27 through 34.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_wd_reset_prep_for_reset(void)
{
    uint8_t ddr_chan;
    uint64_t mddr_base_addr;
    bool chan_populated;

    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Get the base address for the channel
            mddr_base_addr = mddr_base_addrs[ddr_chan];


            // 27. Software now needs to prepare for the 2nd reset. Flush the write data buffer in the controller
            //    D{0..5}_MDDR_DDR_MANUAL[FLUSH_WDB] = 1
            //    D{0..5}_MDDR_DDR_MANUAL[others] = 0
            // Flush the write data buffer in the controller
            mddr_mc_wd_flush_write_data_buff(mddr_base_addr);

            // 28. Poll the write data buffer to ensure all the data are written to memory
            //    D{0..5}_MDDR_SCRUB_STATUS[WDB_CLEAN] = 1
            mddr_mc_wd_wdb_clean_check_complete(mddr_base_addr);


            // 29. Put the memory controller into self-refresh state by following the steps in section 1.19.4.
            mddr_mc_wd_enter_self_refresh(mddr_base_addr);

            // 30. (For RDIMM) Need to place both DIMM's CK and CK_b to low. Use the CK ODT pulldowns.
            //    D{0..5}_DDRPHY_ZQ{1..0}DR[ZDATA][27:21] = 0
            //    D{0..5}_DDRPHY_ZQ{1..0}DR[ZDATA][20:14] = 'h1C
            //    D{0..5}_DDRPHY_ACIOCR0[CKODT] = 'b1111
            mddr_phy_wd_graceful_stop(mddr_base_addr);


            // 31. (For RDIMM) Disable CK driver. Both CK and CK_b should be pulled to low.
            //    D{0..5}_DDRPHY_ACIOCR3[CKOEMODE] = 'hAA
            mddr_phy_wd_disable_ck(mddr_base_addr);


            // 32. Disable DDR PHY's DQS drift detection - Removed since DQS drift detection is disabled
            //    D{0..5}_DDRPHY_DQSDR0[DFTDTEN] = 0


            // 33. Pause DDR PHY's MDL calibrations
            //    D{0..5}_DDRPHY_PIR[DCALPSE] = 1
            mddr_phy_wd_pause_mdl_cal(mddr_base_addr);


            // 34. Enable DDR PHY's VT inhibit
            //    D{0..5}_DDRPHY_PGCR6[INHVT] = 1
            // Don't need since it inhibited normally per default overrides from Vishal
            // mddr_phy_enable_vt_inhibit(mddr_base_addr);

        }
    }
}
#endif // 0



/*!****************************************************************************
*
* @par Description:
*    This function performs the reinitialization of the memory controllers
*    without disturbing the PHYs or memory for watchdog reset.
*     WD reset sequence steps 8 through 10 and 37 through 39.
*
*                                  @param
*    mode               Mode of the target being executed on. Used to provide
*                        simulated SPD for Emulation and simulation environments.
*                        [SILICON|RUMI42|RUMI48|SIM|SIM_RUMI42|SIM_RUMI48]
*                                  @param
*    soc_hw_version     Provides the HW version of the target SoC.
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    Based on mddr_init()
*
******************************************************************************/
unsigned mddr_wd_reset_reinit(target_mode_e mode, soc_hw_version_t soc_hw_version, mddr_settings_t *mddr_settings_ptr)
{
    unsigned status = COM_OK;
    uint8_t ddr_chan;
    uint64_t mddr_base_addr;

    // Check for invalid MDDR settings input arguments.  Invalid combinations that
    //  result in overrides will be checked later.
    status |= mddr_validate_input(mddr_settings_ptr);

    //  Record the platform being executed on.
    platform_mode = mode;

    // Get the DIMM configuration info from SPD
    mddr_get_dimm_configs();

    //
    // Setup common clock values
    //
    status = mddr_set_clock_frequency(mddr_settings_ptr);


    // Use the first frequency for now since dynamic frequency switch is not supported yet.
    mem_freq_mhz = mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1];

    // Set up the other top level frequency parameters
    mddr_xo_freq_khz = mddr_settings_ptr->mddr_xo_freq_khz;
    mem_freq_ps = MDDR_MHZ_TO_PS(mem_freq_mhz);
    ddr_rate = mem_freq_mhz * 2;

    status |= mddr_verify_dimm_combination_configs(mddr_settings_ptr);

    // Get the SI data for the platform.
    mddr_get_si(mddr_settings_ptr);

    if(status == COM_OK)
    {
        // Force disable DDR4 modes that are frequency dependent.
        //  Table 106, pg 204 JEDEC 79-4A
        if((common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4) && (ddr_rate < 2666))
        {
            if (mddr_settings_ptr->ddr4_wr_crc_en)
            {
                monaco_log(HIGH, "Ignoring write CRC enable feature since data rate<2666, data rate = %d\n", ddr_rate);
                mddr_settings_ptr->ddr4_wr_crc_en = false;
            }

            if (mddr_settings_ptr->ddr4_2t_preamble_mode != DDR4_2T_DISABLE)
            {
                monaco_log(HIGH, "Ignoring write/read 2T preamble feature since data rate<2666, data rate = %d\n", ddr_rate);
                mddr_settings_ptr->ddr4_2t_preamble_mode = DDR4_2T_DISABLE;
            }

            if (mddr_settings_ptr->ddr4_geardown_mode_en)
            {
                monaco_log(HIGH, "Ignoring geardown mode since data rate<2666, data rate = %d\n", ddr_rate);
                mddr_settings_ptr->ddr4_geardown_mode_en = false;
            }
        }


        mddr_get_combined_timing_vals(mem_freq_ps);
        mddr_get_latency_vals(&common_cfg, mddr_settings_ptr, &latencies);

        // Get the clock enables for the manual CKE operations.
        mddr_get_slots_ck_cke();


        // Get common fixed register values.
        mddr_mc_get_reg_vals(soc_hw_version, &common_cfg, mddr_settings_ptr, &latencies);


        for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
        {
            if (mddr_check_chan_populated(ddr_chan))
            {

                // 8. Initialize the DDR controller
                status |= mddr_mc_wd_init(mddr_settings_ptr, ddr_chan);

                mddr_base_addr = mddr_base_addrs[ddr_chan];

                // 9. Restore CKE and RESET state
                mddr_mc_wd_enable_clocks(mddr_base_addr);

                // Enable periodic auto refreshes on all valid ranks.
                // Must follow mddr_mc_init() for mddr_valid_ranks to be valid!!
                //
                // Auto-refresh should be re-enabled before step 10. This guarantees that when the controller pulls the DRAM out of the SR later on, the auto-refresh can be immediately picked up.
                mddr_mc_wd_enable_periodic_auto_refresh(mddr_base_addr );
            }
        }

        // 10. Put the memory controllers into self-refresh state by following the steps in section 1.19.4. This is to make the memory controller state match the PHY and DRAM state.
        mddr_enter_self_refresh();
    }
    else
    {
        monaco_log(CRITICAL, " ERROR : The MDDR Subsystem could not be re-initialized. \n");
    }

    return status;
}



/******************************************************************************
* Local Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function validates all MDDR settings arguments passed to the MDDR
*     initialization routine.  Any arguments that are out of range result in an
*     error.  Invalid combinations of values are not checked here, as those
*     checks are performed later in the driver and overridden whenever possible.
*
* @return
*    The status indicating the if the arguments are valid.  COM_OK if the
*     arguments are acceptable, COM_ERROR otherwise.
*
* @author
*    anthonyf
*
******************************************************************************/
unsigned mddr_validate_input(mddr_settings_t *mddr_settings_ptr)
{

    unsigned status = COM_OK;
    uint8_t i;



    for(i = DDR_FREQ_1; i < DDR_FREQ_ID_MAX; ++i)
    {
        if(mddr_settings_ptr->mem_freq_mhz[i] > 1600 )  // Maximum JEDEC Frequency
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = %d is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->mem_freq_mhz[i]),
                       mddr_settings_ptr->mem_freq_mhz[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }
    }



    if((mddr_settings_ptr->max_1dimm_freq_mhz > MAX_1DIMM_FREQ_MHZ_SILICON) &&
       (mddr_settings_ptr->max_1dimm_freq_mhz > MAX_1DIMM_FREQ_MHZ_RUMI))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = %d is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->max_1dimm_freq_mhz),
                   mddr_settings_ptr->max_1dimm_freq_mhz);
    }



    if((mddr_settings_ptr->max_2dimm_freq_mhz > MAX_2DIMM_FREQ_MHZ_SILICON) &&
       (mddr_settings_ptr->max_2dimm_freq_mhz > MAX_2DIMM_FREQ_MHZ_RUMI))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = %d is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->max_2dimm_freq_mhz),
                   mddr_settings_ptr->max_2dimm_freq_mhz);
    }



    if((mddr_settings_ptr->mddr_xo_freq_khz != MDDR_XO_FREQ_KHZ_SILICON) &&
       (mddr_settings_ptr->mddr_xo_freq_khz != MDDR_XO_FREQ_KHZ_RUMI))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = %d is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->mddr_xo_freq_khz),
                   mddr_settings_ptr->mddr_xo_freq_khz);
    }



    if((mddr_settings_ptr->allow_overclocking != 0) &&
       (mddr_settings_ptr->allow_overclocking != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->allow_overclocking),
                   mddr_settings_ptr->allow_overclocking);
    }


    if((mddr_settings_ptr->disable_ecc != 0) &&
       (mddr_settings_ptr->disable_ecc != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->disable_ecc),
                   mddr_settings_ptr->disable_ecc);
    }



    if((mddr_settings_ptr->ecc_wrrd_mode & (ECC_WR | ECC_RD | RS_WR | RS_RD )) == 0)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->ecc_wrrd_mode),
                   mddr_settings_ptr->ecc_wrrd_mode);
    }



    if(mddr_settings_ptr->rs_quad_det_en >= RS_QUAD_DET_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->rs_quad_det_en),
                   mddr_settings_ptr->rs_quad_det_en);
    }



    if((mddr_settings_ptr->disable_patrol_scrub != 0) &&
       (mddr_settings_ptr->disable_patrol_scrub != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->disable_patrol_scrub),
                   mddr_settings_ptr->disable_patrol_scrub);
    }


    if(mddr_settings_ptr->comp_settings.comp_mode >= DDR_COMP_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.comp_mode),
                   mddr_settings_ptr->comp_settings.comp_mode);
    }

    if(mddr_settings_ptr->comp_settings.decomp_comp >= COMP_DECOMP_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.decomp_comp),
                   mddr_settings_ptr->comp_settings.decomp_comp);
    }



    if(mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold < CDE_COMPRD_HI_THRESHOLD_MIN)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold),
                   mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold);
    }

#if ((CDE_COMPRD_HI_THRESHOLD_MAX) != (UINT16_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold > ((CDE_COMPRD_HI_THRESHOLD_MAX)) )
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold),
                   mddr_settings_ptr->comp_settings.cde_comprd_hi_threshold);
    }
#endif



#if ((CDE_COMPRD_LO_THRESHOLD_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold < ((CDE_COMPRD_LO_THRESHOLD_MIN)) )
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold),
                   mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold);
    }
#endif

    if(mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold > CDE_COMPRD_LO_THRESHOLD_MAX)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold),
                   mddr_settings_ptr->comp_settings.cde_comprd_lo_threshold);
    }



    if(mddr_settings_ptr->comp_settings.cde_rd_window_size < CDE_RD_WINDOW_SIZE_MIN)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_rd_window_size),
                   mddr_settings_ptr->comp_settings.cde_rd_window_size);
    }

#if ((CDE_RD_WINDOW_SIZE_MAX) != (UINT16_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->comp_settings.cde_rd_window_size > ((CDE_RD_WINDOW_SIZE_MAX)) )
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_rd_window_size),
                   mddr_settings_ptr->comp_settings.cde_rd_window_size);
    }
#endif



#if ((CDE_RD_HIST_THRESHOLD_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->comp_settings.cde_rd_hist_threshold < ((CDE_RD_HIST_THRESHOLD_MIN)) )
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_rd_hist_threshold),
                   mddr_settings_ptr->comp_settings.cde_rd_hist_threshold);
    }
#endif

    if(mddr_settings_ptr->comp_settings.cde_rd_hist_threshold > CDE_RD_HIST_THRESHOLD_MAX)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_rd_hist_threshold),
                   mddr_settings_ptr->comp_settings.cde_rd_hist_threshold);
    }



    if((mddr_settings_ptr->comp_settings.cde_rd_hist_size < CDE_RD_HIST_SIZE_MIN) ||
       (mddr_settings_ptr->comp_settings.cde_rd_hist_size > CDE_RD_HIST_SIZE_MAX))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_rd_hist_size),
                   mddr_settings_ptr->comp_settings.cde_rd_hist_size);
    }



    if((mddr_settings_ptr->comp_settings.cde_wdb_rd_mode != RD_UNCOMPRESSED) &&
       (mddr_settings_ptr->comp_settings.cde_wdb_rd_mode != RD_COMPRESSED) &&
       (mddr_settings_ptr->comp_settings.cde_wdb_rd_mode != RD_GLBL_ADAPTIVE_TRK_QSB) &&
       (mddr_settings_ptr->comp_settings.cde_wdb_rd_mode != RD_GLBL_ADAPTIVE_TRK_WDB) &&
       (mddr_settings_ptr->comp_settings.cde_wdb_rd_mode != RD_GLBL_ADAPTIVE_TRK_QSB_WDB))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_wdb_rd_mode),
                   mddr_settings_ptr->comp_settings.cde_wdb_rd_mode);
    }



    if((mddr_settings_ptr->comp_settings.cde_qsb_rd_mode != RD_UNCOMPRESSED) &&
       (mddr_settings_ptr->comp_settings.cde_qsb_rd_mode != RD_COMPRESSED) &&
       (mddr_settings_ptr->comp_settings.cde_qsb_rd_mode != RD_ADAPTIVE_PER_MASTER) &&
       (mddr_settings_ptr->comp_settings.cde_qsb_rd_mode != RD_ADAPTIVE_PER_MASTER_UNCOMP) &&
       (mddr_settings_ptr->comp_settings.cde_qsb_rd_mode != RD_ADAPTIVE_PER_MASTER_COMP) &&
       (mddr_settings_ptr->comp_settings.cde_qsb_rd_mode != RD_GLBL_ADAPTIVE_TRK_QSB) &&
       (mddr_settings_ptr->comp_settings.cde_qsb_rd_mode != RD_GLBL_ADAPTIVE_TRK_WDB) &&
       (mddr_settings_ptr->comp_settings.cde_qsb_rd_mode != RD_GLBL_ADAPTIVE_TRK_QSB_WDB))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->comp_settings.cde_qsb_rd_mode),
                   mddr_settings_ptr->comp_settings.cde_qsb_rd_mode);
    }



    if((mddr_settings_ptr->mddr_scrambling_en != 0) &&
       (mddr_settings_ptr->mddr_scrambling_en != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->mddr_scrambling_en),
                   mddr_settings_ptr->mddr_scrambling_en);
    }



    if(mddr_settings_ptr->dbi_mode >= DDR_DBI_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->dbi_mode),
                   mddr_settings_ptr->dbi_mode);
    }



    if(mddr_settings_ptr->ca_parity >= CA_PARITY_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->ca_parity),
                   mddr_settings_ptr->ca_parity);
    }



    if((mddr_settings_ptr->page_settings.enable_auto_pchg != 0) &&
       (mddr_settings_ptr->page_settings.enable_auto_pchg != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->page_settings.enable_auto_pchg),
                   mddr_settings_ptr->page_settings.enable_auto_pchg);
    }



    if(mddr_settings_ptr->page_settings.burst_len_mode >= DB_BURST_LEN_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->page_settings.burst_len_mode),
                   mddr_settings_ptr->page_settings.burst_len_mode);
    }



    if(mddr_settings_ptr->page_settings.page_policy >= DDR_PAGE_POLICY_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->page_settings.page_policy),
                   mddr_settings_ptr->page_settings.page_policy);
    }



#if ((MDDR_PAGE_IDLE_TIMER_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->page_settings.page_idle_timer < MDDR_PAGE_IDLE_TIMER_MIN)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->page_settings.page_idle_timer),
                   mddr_settings_ptr->page_settings.page_idle_timer);
    }
#endif

    if(mddr_settings_ptr->page_settings.page_idle_timer > MDDR_PAGE_IDLE_TIMER_MAX)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->page_settings.page_idle_timer),
                   mddr_settings_ptr->page_settings.page_idle_timer);
    }



    if(mddr_settings_ptr->ddr_granule >= DDR_DIST_GRANULE_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->ddr_granule),
                   mddr_settings_ptr->ddr_granule);
    }



    if((mddr_settings_ptr->dimm_intlv_en != 0) &&
       (mddr_settings_ptr->dimm_intlv_en != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->dimm_intlv_en),
                   mddr_settings_ptr->dimm_intlv_en);
    }



    if((mddr_settings_ptr->rfc_mode != DDR_REFRESH_1X) &&
       (mddr_settings_ptr->rfc_mode != DDR_REFRESH_2X) &&
       (mddr_settings_ptr->rfc_mode != DDR_REFRESH_4X))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->rfc_mode),
                   mddr_settings_ptr->rfc_mode);
    }



    if((mddr_settings_ptr->auto_self_refresh_en != 0) &&
       (mddr_settings_ptr->auto_self_refresh_en != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->auto_self_refresh_en),
                   mddr_settings_ptr->auto_self_refresh_en);
    }



#if ((SR_ENTRY_IDLE_DELAY_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->sr_entry_idle_delay < SR_ENTRY_IDLE_DELAY_MIN)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->sr_entry_idle_delay),
                   mddr_settings_ptr->sr_entry_idle_delay);
    }
#endif

#if ((SR_ENTRY_IDLE_DELAY_MAX) != (UINT16_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->sr_entry_idle_delay > SR_ENTRY_IDLE_DELAY_MAX)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->sr_entry_idle_delay),
                   mddr_settings_ptr->sr_entry_idle_delay);
    }
#endif



    if((mddr_settings_ptr->auto_power_down_en != 0) &&
       (mddr_settings_ptr->auto_power_down_en != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->auto_power_down_en),
                   mddr_settings_ptr->auto_power_down_en);
    }



#if ((PD_ENTRY_IDLE_DELAY_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
        if(mddr_settings_ptr->pd_entry_idle_delay < PD_ENTRY_IDLE_DELAY_MIN)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->pd_entry_idle_delay),
                       mddr_settings_ptr->pd_entry_idle_delay);
        }
#endif

#if ((PD_ENTRY_IDLE_DELAY_MAX) != (UINT16_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
        if(mddr_settings_ptr->pd_entry_idle_delay > PD_ENTRY_IDLE_DELAY_MAX)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->pd_entry_idle_delay),
                       mddr_settings_ptr->pd_entry_idle_delay);
        }
#endif



    if((mddr_settings_ptr->adj_ref_dimm0 != DIMM_REFRESH_RATE_ONE_QUARTER) &&
       (mddr_settings_ptr->adj_ref_dimm0 != DIMM_REFRESH_RATE_ONE_HALF) &&
       (mddr_settings_ptr->adj_ref_dimm0 != DIMM_REFRESH_RATE_1x) &&
       (mddr_settings_ptr->adj_ref_dimm0 != DIMM_REFRESH_RATE_2x) &&
       (mddr_settings_ptr->adj_ref_dimm0 != DIMM_REFRESH_RATE_4x))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->adj_ref_dimm0),
                   mddr_settings_ptr->adj_ref_dimm0);
    }



    if((mddr_settings_ptr->adj_ref_dimm1 != DIMM_REFRESH_RATE_ONE_QUARTER) &&
       (mddr_settings_ptr->adj_ref_dimm1 != DIMM_REFRESH_RATE_ONE_HALF) &&
       (mddr_settings_ptr->adj_ref_dimm1 != DIMM_REFRESH_RATE_1x) &&
       (mddr_settings_ptr->adj_ref_dimm1 != DIMM_REFRESH_RATE_2x) &&
       (mddr_settings_ptr->adj_ref_dimm1 != DIMM_REFRESH_RATE_4x))
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->adj_ref_dimm1),
                       mddr_settings_ptr->adj_ref_dimm1);
        }



    if(mddr_settings_ptr->dfi_lp_mode >= DFI_LP_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->dfi_lp_mode),
                   mddr_settings_ptr->dfi_lp_mode);
    }



#if ((DFI_LP2_ENTRY_IDLE_DELAY_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->dfi_lp2_entry_idle_delay < DFI_LP2_ENTRY_IDLE_DELAY_MIN)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->dfi_lp2_entry_idle_delay),
                   mddr_settings_ptr->dfi_lp2_entry_idle_delay);
    }
#endif

#if ((DFI_LP2_ENTRY_IDLE_DELAY_MAX) != (UINT16_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->dfi_lp2_entry_idle_delay > DFI_LP2_ENTRY_IDLE_DELAY_MAX)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->dfi_lp2_entry_idle_delay),
                   mddr_settings_ptr->dfi_lp2_entry_idle_delay);
    }
#endif



    if(mddr_settings_ptr->ddr4_2t_preamble_mode >= DDR4_2T_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->ddr4_2t_preamble_mode),
                   mddr_settings_ptr->ddr4_2t_preamble_mode);
    }



    if((mddr_settings_ptr->num_dimm_slots < NUM_DIMM_SLOTS_MIN) ||
       (mddr_settings_ptr->num_dimm_slots > NUM_DIMM_SLOTS_MAX))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = %d is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->num_dimm_slots),
                   mddr_settings_ptr->num_dimm_slots);
    }



    if((mddr_settings_ptr->periodic_zq_cal_en != 0) &&
       (mddr_settings_ptr->periodic_zq_cal_en != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->periodic_zq_cal_en),
                   mddr_settings_ptr->periodic_zq_cal_en);
    }



    if((mddr_settings_ptr->shared_dimm_clk != 0) &&
       (mddr_settings_ptr->shared_dimm_clk != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->shared_dimm_clk),
                   mddr_settings_ptr->shared_dimm_clk);
    }



#if ((PROP_DELAY_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->prop_delay < PROP_DELAY_MIN)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->prop_delay),
                   mddr_settings_ptr->prop_delay);
    }
#endif

#if ((PROP_DELAY_MAX) != (UINT8_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->prop_delay > PROP_DELAY_MAX)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->prop_delay),
                   mddr_settings_ptr->prop_delay);
    }
#endif



#if ((EXTRA_DQS_TOGGLE_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->extra_dqs_toggle < EXTRA_DQS_TOGGLE_MIN)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->extra_dqs_toggle),
                   mddr_settings_ptr->extra_dqs_toggle);
    }
#endif

    if(mddr_settings_ptr->extra_dqs_toggle > EXTRA_DQS_TOGGLE_MAX)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->extra_dqs_toggle),
                   mddr_settings_ptr->extra_dqs_toggle);
    }



    if((mddr_settings_ptr->ca_stretch != CA_STRETCH_1T) &&
       (mddr_settings_ptr->ca_stretch != CA_STRETCH_2T) &&
       (mddr_settings_ptr->ca_stretch != CA_STRETCH_3T) &&
       (mddr_settings_ptr->ca_stretch != CA_STRETCH_4T))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->ca_stretch),
                   mddr_settings_ptr->ca_stretch);
    }


    // CAL mode is deprecated on QDF2400
    if(mddr_settings_ptr->ddr4_cal_mode_en != 0)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->ddr4_cal_mode_en),
                   mddr_settings_ptr->ddr4_cal_mode_en);
    }



    // Geardown mode is deprecated on QDF2400
    if(mddr_settings_ptr->ddr4_geardown_mode_en != 0)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->ddr4_geardown_mode_en),
                   mddr_settings_ptr->ddr4_geardown_mode_en);
    }



    // Write CRC mode is deprecated on QDF2400
    if(mddr_settings_ptr->ddr4_wr_crc_en != 0)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->ddr4_wr_crc_en),
                   mddr_settings_ptr->ddr4_wr_crc_en);
    }



    if((mddr_settings_ptr->therm_throttle_en != 0) &&
       (mddr_settings_ptr->therm_throttle_en != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->therm_throttle_en),
                   mddr_settings_ptr->therm_throttle_en);
    }



    if(mddr_settings_ptr->clk_type >= CLK_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->clk_type),
                   mddr_settings_ptr->clk_type);
    }



    if((mddr_settings_ptr->clkgen_ssc_en != 0) &&
       (mddr_settings_ptr->clkgen_ssc_en != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->clkgen_ssc_en),
                   mddr_settings_ptr->clkgen_ssc_en);
    }


    if(mddr_settings_ptr->bank_group_decode >= ADDR_DECODE_BG_NUM_TYPES)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->bank_group_decode),
                   mddr_settings_ptr->bank_group_decode);
    }



    if((mddr_settings_ptr->bum_settings.busy.enable != 0) &&
       (mddr_settings_ptr->bum_settings.busy.enable != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.busy.enable),
                   mddr_settings_ptr->bum_settings.busy.enable);
    }



    if((mddr_settings_ptr->bum_settings.bcqfull.enable != 0) &&
       (mddr_settings_ptr->bum_settings.bcqfull.enable != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.bcqfull.enable),
                   mddr_settings_ptr->bum_settings.bcqfull.enable);
    }



    for (i = 0; i < DDR_BUM_PERF_IDX_MAX; i++)
    {

#if ((DDR_BUM_LO_THRESHOLD_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
        if(mddr_settings_ptr->bum_settings.busy.lo_threshold[i] < DDR_BUM_LO_THRESHOLD_MIN)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.busy.lo_threshold[i]),
                       mddr_settings_ptr->bum_settings.busy.lo_threshold[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }


        if(mddr_settings_ptr->bum_settings.bcqfull.lo_threshold[i]  < DDR_BUM_LO_THRESHOLD_MIN)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.bcqfull.lo_threshold[i]),
                       mddr_settings_ptr->bum_settings.bcqfull.lo_threshold[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }
#endif



#if ((DDR_BUM_LO_THRESHOLD_MAX) != (UINT32_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
        if(mddr_settings_ptr->bum_settings.busy.lo_threshold[i] > DDR_BUM_LO_THRESHOLD_MAX)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.busy.lo_threshold[i]),
                       mddr_settings_ptr->bum_settings.busy.lo_threshold[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }


        if(mddr_settings_ptr->bum_settings.bcqfull.lo_threshold[i]  > DDR_BUM_LO_THRESHOLD_MAX)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.bcqfull.lo_threshold[i]),
                       mddr_settings_ptr->bum_settings.bcqfull.lo_threshold[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }
#endif



#if ((DDR_BUM_HI_THRESHOLD_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
        if(mddr_settings_ptr->bum_settings.busy.hi_threshold[i] < DDR_BUM_HI_THRESHOLD_MIN)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.busy.hi_threshold[i]),
                       mddr_settings_ptr->bum_settings.busy.hi_threshold[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }


        if(mddr_settings_ptr->bum_settings.bcqfull.hi_threshold[i] < DDR_BUM_HI_THRESHOLD_MIN)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.bcqfull.hi_threshold[i]),
                       mddr_settings_ptr->bum_settings.bcqfull.hi_threshold[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }
#endif



#if ((DDR_BUM_HI_THRESHOLD_MAX) != (UINT32_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
        if(mddr_settings_ptr->bum_settings.busy.hi_threshold[i] > DDR_BUM_HI_THRESHOLD_MAX)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.busy.hi_threshold[i]),
                       mddr_settings_ptr->bum_settings.busy.hi_threshold[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }


        if(mddr_settings_ptr->bum_settings.bcqfull.hi_threshold[i] > DDR_BUM_HI_THRESHOLD_MAX)
        {
            status |= COM_ERROR;

            monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid (%s = %d).\n",
                       MDDR_GET_VAR_NAME(mddr_settings_ptr->bum_settings.bcqfull.hi_threshold[i]),
                       mddr_settings_ptr->bum_settings.bcqfull.hi_threshold[i],
                       MDDR_GET_VAR_NAME(i),
                       i);
        }
#endif
    }



    if((mddr_settings_ptr->tcrit_event_en != 0) &&
       (mddr_settings_ptr->tcrit_event_en != 1))
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = 0x%X is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->tcrit_event_en),
                   mddr_settings_ptr->tcrit_event_en);
    }



#if ((TCRIT_THRESHHOLD_MIN) != (0))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->tcrit_threshhold < TCRIT_THRESHHOLD_MIN)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = %u is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->tcrit_threshhold),
                   mddr_settings_ptr->tcrit_threshhold);
    }
#endif



#if ((TCRIT_THRESHHOLD_MAX) != (UINT8_MAX))    // Avoid GCC [-Wtype-limits] bug when limit comes from a macro - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=51712#c3
    if(mddr_settings_ptr->tcrit_threshhold > TCRIT_THRESHHOLD_MAX)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = %u is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->tcrit_threshhold),
                   mddr_settings_ptr->tcrit_threshhold);
    }
#endif


    if(mddr_settings_ptr->phy_config.ddrphy_xcnt > 0xF)
    {
        status |= COM_ERROR;

        monaco_log(CRITICAL, " ERROR : The MDDR setting %s = %u is invalid.\n",
                   MDDR_GET_VAR_NAME(mddr_settings_ptr->phy_config.ddrphy_xcnt),
                   mddr_settings_ptr->phy_config.ddrphy_xcnt);
    }

    return status;

}


/*!****************************************************************************
*
* @par Description:
*    This function collects the SPD based configuration information for all
*    DIMMs populated in the MDDR sub-system.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_get_dimm_configs(void)
{
    unsigned status;
    uint64_t spd_base;
    uint8_t ddr_chan;
    uint8_t dimm_slot;
    unsigned bytes_total;


    spd_base = (uint64_t)spd_scratch_pad;


    // Go through each DIMM SPD and get the associated SPD information.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            monaco_log(INFORMATIONAL, "Scanning DDR Chan %u  DIMM slot %u\n", hddrss[ddr_chan], dimm_slot);

            // Default to indicating the channel is unpopulated
            mddr_dimm_configs[ddr_chan][dimm_slot].dev_type = SPD_DEVICE_TYPE_UNDEFINED;

            // Need to get number of bytes total in the serial EEPROM for the correct load size.
            //  The SPD field Bytes Total is used instead of Bytes Used because the interpretation
            //  of bytes used differs between DDR3 and DDR4.
            bytes_total = spd_read_dimm_spd_bytes_total(ddr_chan, dimm_slot);

            if((bytes_total > 0) && (bytes_total <= SPD_MAX_SERIAL_EEPROM_SIZE))
            {
                monaco_log(HIGH, "   >> Found DIMM in Channel %u\n", hddrss[ddr_chan]);

                // Read the block of SPD data into memory for the given channel/slot.
                status = spd_read_dimm_nbytes(ddr_chan, dimm_slot, spd_base, bytes_total);

                if(status == COM_OK)
                {
                    spd_get_dimm_config(ddr_chan, dimm_slot, spd_base, &(mddr_dimm_configs[ddr_chan][dimm_slot]));
                }
            }
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function verifies the SPD configuration collected from all
*    populated DIMMs and coalesces the configuration into a common configuration.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
* @return
*    The status indicating the if the SPD configurations is good or bad. COM_OK
*    if the configurations are acceptable, COM_ERROR otherwise.
*
* @author
*    gkowis
*
* @par Notes:
*    DIMMs within a channel can differ but all populated channels are expected
*    to be populated identically.
*
******************************************************************************/
unsigned mddr_verify_dimm_combination_configs(mddr_settings_t *mddr_settings_ptr)
{
    unsigned status = COM_ERROR;
    uint8_t ddr_chan;
    uint8_t baseline_chan;
    bool found_baseline_chan = false;
    uint8_t dimm_slot;
    spd_dimm_config_t *cfg_ptr;
    uint8_t max_num_columns = 0;


    // Start with an indication that no DIMMs are present.
    common_cfg.dev_type = SPD_DEVICE_TYPE_UNDEFINED;

    //
    // Establish the common configuration.
    //
    // Find the baseline channel and record the configuration that should be common
    //  to all slots of all populated channels. The first populated channel is
    //  considered the baseline and all other channels should be populated.
    ddr_chan = 0;
    found_baseline_chan = false;
    baseline_chan = 0;    // Set baseline_chan to 0 to start with

    do
    {
        dimm_slot = 0;

        do
        {
            cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

            if(cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                found_baseline_chan = true;
                baseline_chan = ddr_chan;

                // Record the common config for the baseline channel that applies accross
                //  all slots of all channels.
                common_cfg.dev_type = cfg_ptr->dev_type;
                common_cfg.sdram_width = cfg_ptr->sdram_width;
                common_cfg.has_ecc = cfg_ptr->has_ecc;
                common_cfg.mod_type = cfg_ptr->mod_type;
                common_cfg.is_3DS = cfg_ptr->is_3DS;
            }

            ++dimm_slot;
        } while((dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN) && (!found_baseline_chan));

        ++ddr_chan;
    } while((ddr_chan < DDR_MAX_NUM_CHANS) && (!found_baseline_chan));



    if(found_baseline_chan)
    {

        // Record the slot dependent pieces of the common config taken from the baseline channel.
        common_cfg.num_slots_populated = 0;
        dimm_slot = 0;

        do
        {
            cfg_ptr = &(mddr_dimm_configs[baseline_chan][dimm_slot]);

            // Ensure the configuration is sane for all slots of a populated channel!!
            if(cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                // Record the number of slots populated in the baseline channel
                ++common_cfg.num_slots_populated;

                // Record the common config for the the slot.
                common_cfg.slot_config[dimm_slot].num_ranks = cfg_ptr->num_ranks;
                common_cfg.slot_config[dimm_slot].num_bank_groups = cfg_ptr->num_bank_groups;
                common_cfg.slot_config[dimm_slot].num_rows = cfg_ptr->num_rows;
                common_cfg.slot_config[dimm_slot].num_columns = cfg_ptr->num_columns;
                common_cfg.slot_config[dimm_slot].die_count = cfg_ptr->die_count;
                common_cfg.slot_config[dimm_slot].dimm_size_mb = cfg_ptr->dimm_size_mb;
                common_cfg.slot_config[dimm_slot].ca_mirrored = cfg_ptr->ca_mirrored;

                // Common RDIMM and LRDIMM Values
                common_cfg.slot_config[dimm_slot].out_drv_ck_y13 = cfg_ptr->out_drv_ck_y13;
                common_cfg.slot_config[dimm_slot].out_drv_ck_y02 = cfg_ptr->out_drv_ck_y02;

                // DDR3 Only RDIMM Values
                common_cfg.slot_config[dimm_slot].rdm_out_drv_ctl_a = cfg_ptr->rdm_out_drv_ctl_a;
                common_cfg.slot_config[dimm_slot].rdm_out_drv_ctl_b = cfg_ptr->rdm_out_drv_ctl_b;
                common_cfg.slot_config[dimm_slot].rdm_out_drv_ca_a = cfg_ptr->rdm_out_drv_ca_a;
                common_cfg.slot_config[dimm_slot].rdm_out_drv_ca_b = cfg_ptr->rdm_out_drv_ca_b;
                common_cfg.slot_config[dimm_slot].rcw0f_00 = cfg_ptr->rdm_ddr3_cw15_0;

                // DDR4 RDIMM / LRDIMM Values
                common_cfg.slot_config[dimm_slot].out_drv_ctl_cke = cfg_ptr->out_drv_ctl_cke;
                common_cfg.slot_config[dimm_slot].out_drv_ctl_odt = cfg_ptr->out_drv_ctl_odt;
                common_cfg.slot_config[dimm_slot].out_drv_ctl_ca = cfg_ptr->out_drv_ctl_ca;
                common_cfg.slot_config[dimm_slot].out_drv_ctl_cs = cfg_ptr->out_drv_ctl_cs;

                // DDR4 Only LRDIMM Values
                common_cfg.slot_config[dimm_slot].lrdm_db_drv_ck_bcom_bodt_bcke = cfg_ptr->lrdm_db_drv_ck_bcom_bodt_bcke;
                common_cfg.slot_config[dimm_slot].lrdm_db_drv_ck_bck = cfg_ptr->lrdm_db_drv_ck_bck;

                // The DIMMs in different slots could have different number of columns so pick the max from
                //  populated slots to get the largest page size.
                if (cfg_ptr->num_columns > max_num_columns)
                {
                    max_num_columns = cfg_ptr->num_columns;
                }
            }
            else
            {
                // Mark the configuration for empty slots as invalid.
                common_cfg.slot_config[dimm_slot].num_ranks = SPD_INVALID_RANK_COUNT;
            }

            ++dimm_slot;
        } while(dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN);


        //
        // Find page size, 0 means < 1K i.e. 512B
        //
        common_cfg.max_page_size_kb = (max_num_columns * common_cfg.sdram_width / BITS_PER_BYTE) / BYTES_PER_KB;


        //
        // Go through the DIMMs and verify the are supported and conform to the baseline channel.
        //
        status = mddr_verify_dimms(mddr_settings_ptr);
    }

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function verifies the SPD configuration collected from all
*    populated DIMMs.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
* @return
*    The status indicating the if the SPD configurations is good or bad. COM_OK
*    if the configurations are acceptable, COM_ERROR otherwise.
*
* @author
*    gkowis
*
* @par Notes:
*    DIMMs within a channel can differ but all populated channels are expected
*    to be populated identically.
*
******************************************************************************/
unsigned mddr_verify_dimms(mddr_settings_t *mddr_settings_ptr)
{
    unsigned status = COM_OK;
    uint8_t ddr_chan;
    uint8_t dimm_slot;
    uint8_t num_even_chans = 0;
    uint8_t num_odd_chans = 0;
    spd_dimm_config_t *cfg_ptr;
    bool chan_populated;
    uint8_t num_slots_populated;
    uint32_t channel_size_gb;

    // Reset value to allow for reentrancy for watchdog reset
    num_chans_poped = 0;

    // Go through each DIMM SPD and check the associated SPD information.
    //  The DIMMs (slots) within a single channel can have a level of variation,
    //  but at the channel level all channels should match the common configuration
    //  of the baseline.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        // Track populated channels to support counting the number of channels populated in each interleave.
        chan_populated = false;
        num_slots_populated = 0;
        channel_size_gb = 0;

        for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

            if (cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                chan_populated = true;

                channel_size_gb += ((mddr_dimm_configs[ddr_chan][dimm_slot].dimm_size_mb) / MB_PER_GB);
                ++num_slots_populated;
            }
        }

        // This is a per channel check to ensure that, in a 2DPC, slot 1 cannot be populated without slot 0.
        // If Slot 0 is empty, and Slot 1 is populated, we report an error.
        if ((chan_populated == true) && (num_slots_populated == 1))
        {
            if (mddr_dimm_configs[ddr_chan][0].dev_type == SPD_DEVICE_TYPE_UNDEFINED)
            {

                monaco_log(CRITICAL, "ERROR:  In Chan %u, Found DIMM in slot 0 but, not in slot 1. Slot 0 must be populated before slot 1\n",
                       hddrss[ddr_chan]);
                status = COM_ERROR;

            }
        }

        // Perform the per slot checks only when the per channel check is OK.
        if (status == COM_OK)
        {
            for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
            {

                cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

                if(cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
                {
                    // Start by determining if the individual DIMM is supportable.
                    if ((cfg_ptr->dev_type != SPD_DEVICE_TYPE_DDR3) && (cfg_ptr->dev_type != SPD_DEVICE_TYPE_DDR4))
                    {
                        monaco_log(CRITICAL, "ERROR:  Unrecognized Device Type 0x%2.2x in Chan %u  Slot %u\n", cfg_ptr->dev_type, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if ((cfg_ptr->mod_type != SPD_MODULE_TYPE_UDIMM) && (cfg_ptr->mod_type != SPD_MODULE_TYPE_RDIMM) &&
                        (cfg_ptr->mod_type != SPD_MODULE_SODIMM) && (cfg_ptr->mod_type != SPD_MODULE_SOUDIMM) && (cfg_ptr->mod_type != SPD_MODULE_TYPE_DDR4_LRDIMM))
                    {
                        monaco_log(CRITICAL, "ERROR:  Unrecognized Module Type 0x%2.2x in Chan %u  Slot %u\n", cfg_ptr->mod_type, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if ((num_slots_populated == DDR_MAX_NUM_SLOTS_PER_CHAN) && (cfg_ptr->mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM))
                    {
                        monaco_log(CRITICAL, "ERROR:  In 2DPC, for module type LRDIMM, more than 1 DIMM per channel populated is not supported\n");
                        status = COM_ERROR;
                    }
                    else if ((cfg_ptr->num_ranks > SPD_MAX_RANKS_SUPPORTED) || ((cfg_ptr->num_ranks == SPD_UNSUPPORTED_RANK_VAL)))
                    {
                        monaco_log(CRITICAL, "ERROR:  Invalid number of chip selects(CS)= %u in Chan %u  Slot %u\n", cfg_ptr->num_ranks, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if ((num_slots_populated == DDR_MAX_NUM_SLOTS_PER_CHAN) && (cfg_ptr->num_ranks > SPD_MAX_RANKS_SUPPORTED_2DPC))
                    {
                        monaco_log(CRITICAL, "ERROR:  In 2DPC, Invalid number of chip selects (CS) = %u in Chan %u  Slot %u\n", cfg_ptr->num_ranks, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if ((cfg_ptr->sdram_width != SPD_SDRAM_WIDTH_X4) && (cfg_ptr->sdram_width != SPD_SDRAM_WIDTH_X8))
                    {
                        monaco_log(CRITICAL, "ERROR:  Unsupported device width 0x%2.2x in Chan %u  Slot %u\n", cfg_ptr->sdram_width, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if (cfg_ptr->dimm_module_width != SPD_MODULE_WIDTH)
                    {
                        monaco_log(CRITICAL, "ERROR:  Invalid DIMM module width 0x%2.2x in Chan %u  Slot %u\n", cfg_ptr->dimm_module_width, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if ((cfg_ptr->num_rows < SPD_MIN_ROWS) || (cfg_ptr->num_rows > SPD_MAX_ROWS))
                    {
                        monaco_log(CRITICAL, "ERROR:  Invalid number of row addresses= %u in Chan %u  Slot %u\n", cfg_ptr->num_rows, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if ((cfg_ptr->num_columns < SPD_MIN_COLUMNS) || (cfg_ptr->num_columns > SPD_MAX_COLUMNS))
                    {
                        monaco_log(CRITICAL, "ERROR:  Invalid number of column addresses= %u in Chan %u  Slot %u\n", cfg_ptr->num_columns, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if ((cfg_ptr->die_count != 1) && (cfg_ptr->die_count != 2) &&
                              (cfg_ptr->die_count != 4) && (cfg_ptr->die_count != 8))
                    {
                        // MC supports only specific die counts for stacked devices.
                        monaco_log(CRITICAL, "ERROR:  Invalid number of dies 0x%2.2x in Chan %u  Slot %u\n", cfg_ptr->die_count, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if (cfg_ptr->is_voltage_ok == false)
                    {
                        monaco_log(CRITICAL, "ERROR:  DIMM does not support required voltage in Chan %u  Slot %u\n", hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if (cfg_ptr->mtb_ps == 0)
                    {
                        monaco_log(CRITICAL, "ERROR:  Time base is 0 in Chan %u  Slot %u\n", hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if (cfg_ptr->dimm_size_mb < SPD_MIN_DIMM_SIZE)
                    {
                        monaco_log(CRITICAL, "ERROR: DIMM size is less than %d GB, size = %d GB in Chan %u  Slot %u\n",
                               SPD_MIN_DIMM_SIZE / MB_PER_GB, cfg_ptr->dimm_size_mb / MB_PER_GB, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if (cfg_ptr->dimm_size_mb > SPD_MAX_DIMM_SIZE)
                    {
                        monaco_log(CRITICAL, "ERROR: DIMM size is greater than SPD_MAX_DIMM_SIZE GB, size = %d GB in Chan %u  Slot %u\n",
                               SPD_MAX_DIMM_SIZE / MB_PER_GB, cfg_ptr->dimm_size_mb / MB_PER_GB, hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if(cfg_ptr->is_rank_mix)    // asymmetrical ranks
                    {
                        monaco_log(CRITICAL, "ERROR: Asymmetrical ranks detected, in Chan %u\n", hddrss[ddr_chan]);
                        status = COM_ERROR;
                    }
                    else if ((num_slots_populated == DDR_MAX_NUM_SLOTS_PER_CHAN) && (cfg_ptr->dimm_size_mb > SPD_MAX_DIMM_SIZE_2DPC))
                    {
                        monaco_log(CRITICAL, "ERROR: DIMM size is greater than %d GB in 2DPC, size = %d GB in Chan %u  Slot %u\n",
                               SPD_MAX_DIMM_SIZE_2DPC / MB_PER_GB, cfg_ptr->dimm_size_mb / MB_PER_GB , hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else if(channel_size_gb > SPD_MAX_CHANNEL_SIZE)
                    {
                        monaco_log(CRITICAL, "ERROR: Channel size is greater than %d GB, size = %d GB in Chan %u\n",
                               SPD_MAX_CHANNEL_SIZE / MB_PER_GB, channel_size_gb, hddrss[ddr_chan]);
                        status = COM_ERROR;
                    }
                    else if ((cfg_ptr->num_ranks == DDR_RANKS_QUAD_CS_DIMM) && (cfg_ptr->is_3DS))
                    {
                        monaco_log(CRITICAL, "ERROR: Cannot support Quad rank(CS) TSV DIMM, in Chan %u  Slot %u\n", hddrss[ddr_chan], dimm_slot);
                        status = COM_ERROR;
                    }
                    else
                    {
                        // The individual DIMM is supportable. Now check that it is
                        //  consistant with the population of the baseline channel.

                        if(num_slots_populated != common_cfg.num_slots_populated)
                        {
                            monaco_log(CRITICAL, "ERROR:  Number of DIMMs in each populated channel not the same, \
                                                  expected 0x%2.2x got 0x%2.2x in Chan %u\n",
                                   common_cfg.num_slots_populated, num_slots_populated, hddrss[ddr_chan]);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->dev_type != common_cfg.dev_type)
                        {
                            monaco_log(CRITICAL, "ERROR:  Device type mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.dev_type, cfg_ptr->dev_type, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->sdram_width != common_cfg.sdram_width)
                        {
                            monaco_log(CRITICAL, "ERROR:  Device width mismatch, DIMMs with different width populated, \
                                                  expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.sdram_width, cfg_ptr->sdram_width, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if ((cfg_ptr->has_ecc != common_cfg.has_ecc) && (mddr_settings_ptr->disable_ecc == false))
                        {
                            monaco_log(CRITICAL, "ERROR:  ECC mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.has_ecc, cfg_ptr->has_ecc, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->mod_type != common_cfg.mod_type)
                        {
                            monaco_log(CRITICAL, "ERROR:  Module type mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.mod_type, cfg_ptr->mod_type, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->is_3DS != common_cfg.is_3DS)
                        {
                            monaco_log(CRITICAL, "ERROR:  Device 3DS mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.is_3DS, cfg_ptr->is_3DS, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->ca_mirrored != common_cfg.slot_config[dimm_slot].ca_mirrored)
                        {
                            monaco_log(CRITICAL, "ERROR:  Device CA mirroring mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.slot_config[dimm_slot].ca_mirrored, cfg_ptr->ca_mirrored, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->num_ranks != common_cfg.slot_config[dimm_slot].num_ranks)
                        {
                            monaco_log(CRITICAL, "ERROR:  Number of ranks mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.slot_config[dimm_slot].num_ranks, cfg_ptr->num_ranks, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->num_bank_groups != common_cfg.slot_config[dimm_slot].num_bank_groups)
                        {
                            monaco_log(CRITICAL, "ERROR:  Number of bank groups mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.slot_config[dimm_slot].num_bank_groups, cfg_ptr->num_bank_groups, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->num_rows != common_cfg.slot_config[dimm_slot].num_rows)
                        {
                            monaco_log(CRITICAL, "ERROR:  Number of row addresses mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.slot_config[dimm_slot].num_rows, cfg_ptr->num_rows, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->num_columns != common_cfg.slot_config[dimm_slot].num_columns)
                        {
                            monaco_log(CRITICAL, "ERROR:  Number of column address mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.slot_config[dimm_slot].num_columns, cfg_ptr->num_columns, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->die_count != common_cfg.slot_config[dimm_slot].die_count)
                        {
                            monaco_log(CRITICAL, "ERROR:  Device die count mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                   common_cfg.slot_config[dimm_slot].die_count, cfg_ptr->die_count, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (cfg_ptr->dimm_size_mb != common_cfg.slot_config[dimm_slot].dimm_size_mb)
                        {
                            monaco_log(CRITICAL, "ERROR:  DIMM size mismatch, capacity of all populated DIMMs not the same, \
                                                  expected %uMB got %uMB in Chan %u  Slot %u\n",
                                   common_cfg.slot_config[dimm_slot].dimm_size_mb, cfg_ptr->dimm_size_mb, hddrss[ddr_chan], dimm_slot);
                            status = COM_ERROR;
                        }
                        else if (common_cfg.slot_config[dimm_slot].dimm_size_mb > common_cfg.slot_config[0].dimm_size_mb)
                        {
                            // DDR Sub-System (DDRSS) Hardware Programming Guide - January 20, 2017 - Section 4.17.1.4
                            //  When a memory channel contains two DIMMs, and the two DIMMs are of different size,
                            //  capacity, the larger DIMM must be populated in slot 0.

                            monaco_log(CRITICAL, "ERROR:  The DIMM in slot %d (%d GB) is larger than the DIMM in slot 0 (%d GB) in Chan %u\n",
                                   dimm_slot, cfg_ptr->dimm_size_mb / MB_PER_GB, common_cfg.slot_config[0].dimm_size_mb / MB_PER_GB, hddrss[ddr_chan]);
                            status = COM_ERROR;
                        }
                        else
                        {
                            if (common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM)
                            {
                                if (cfg_ptr->out_drv_ck_y13 != common_cfg.slot_config[dimm_slot].out_drv_ck_y13)
                                {
                                    // Common accross DDR3 & DDR4 RDIMMs
                                    monaco_log(CRITICAL, "ERROR:  RDIMM output drive CK 13 Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                           common_cfg.slot_config[dimm_slot].out_drv_ck_y13, cfg_ptr->out_drv_ck_y13, hddrss[ddr_chan], dimm_slot);
                                    status = COM_ERROR;
                                }
                                else if (cfg_ptr->out_drv_ck_y02 != common_cfg.slot_config[dimm_slot].out_drv_ck_y02)
                                {
                                    // Common accross DDR3 & DDR4 RDIMMs
                                    monaco_log(CRITICAL, "ERROR:  RDIMM output drive CK 02 Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                           common_cfg.slot_config[dimm_slot].out_drv_ck_y02, cfg_ptr->out_drv_ck_y02, hddrss[ddr_chan], dimm_slot);
                                    status = COM_ERROR;
                                }

                                // Verify DDR3 Specifics
                                if(common_cfg.dev_type == SPD_DEVICE_TYPE_DDR3)
                                {
                                    if (cfg_ptr->rdm_out_drv_ctl_a != common_cfg.slot_config[dimm_slot].rdm_out_drv_ctl_a)
                                    {
                                        // DDR3 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR3 RDIMM output drive control A Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                               common_cfg.slot_config[dimm_slot].rdm_out_drv_ctl_a, cfg_ptr->rdm_out_drv_ctl_a, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                    else if (cfg_ptr->rdm_out_drv_ctl_b != common_cfg.slot_config[dimm_slot].rdm_out_drv_ctl_b)
                                    {
                                        // DDR3 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR3 RDIMM output drive control B Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                               common_cfg.slot_config[dimm_slot].rdm_out_drv_ctl_b, cfg_ptr->rdm_out_drv_ctl_b, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                    else if (cfg_ptr->rdm_out_drv_ca_a != common_cfg.slot_config[dimm_slot].rdm_out_drv_ca_a)
                                    {
                                        // DDR3 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR3 RDIMM output drive command/address A Mismatch, expected 0x%16.16x got 0x%16.16x in Chan %u  Slot %u\n",
                                               common_cfg.slot_config[dimm_slot].rdm_out_drv_ca_a, cfg_ptr->rdm_out_drv_ca_a, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                    else if (cfg_ptr->rdm_out_drv_ca_b != common_cfg.slot_config[dimm_slot].rdm_out_drv_ca_b)
                                    {
                                        // DDR3 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR3 RDIMM output drive command/address B Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                               common_cfg.slot_config[dimm_slot].rdm_out_drv_ca_b, cfg_ptr->rdm_out_drv_ca_b, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                    else if (cfg_ptr->rdm_ddr3_cw15_0 != common_cfg.slot_config[dimm_slot].rcw0f_00)
                                    {
                                        // DDR3 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR3 RDIMM RC words Mismatch, expected 0x%16.16llx got 0x%16.16llx in Chan %u  Slot %u\n",
                                               (long long unsigned int)common_cfg.slot_config[dimm_slot].rcw0f_00,
                                               (long long unsigned int)cfg_ptr->rdm_ddr3_cw15_0, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                }


                                // Verify DDR4 Specifics
                                if(common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
                                {
                                    if (cfg_ptr->out_drv_ctl_cke != common_cfg.slot_config[dimm_slot].out_drv_ctl_cke)
                                    {
                                        // DDR4 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR4 RDIMM output drive control CKE Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                               common_cfg.slot_config[dimm_slot].out_drv_ctl_cke, cfg_ptr->out_drv_ctl_cke, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                    else if (cfg_ptr->out_drv_ctl_odt != common_cfg.slot_config[dimm_slot].out_drv_ctl_odt)
                                    {
                                        // DDR4 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR4 RDIMM output drive control ODT Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                               common_cfg.slot_config[dimm_slot].out_drv_ctl_odt, cfg_ptr->out_drv_ctl_odt, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                    else if (cfg_ptr->out_drv_ctl_ca != common_cfg.slot_config[dimm_slot].out_drv_ctl_ca)
                                    {
                                        // DDR4 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR4 RDIMM output drive control command/address Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                               common_cfg.slot_config[dimm_slot].out_drv_ctl_ca, cfg_ptr->out_drv_ctl_ca, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                    else if (cfg_ptr->out_drv_ctl_cs != common_cfg.slot_config[dimm_slot].out_drv_ctl_cs)
                                    {
                                        // DDR4 Only RDIMM Value
                                        monaco_log(CRITICAL, "ERROR:  DDR4 RDIMM output drive control chip select Mismatch, expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                               common_cfg.slot_config[dimm_slot].out_drv_ctl_cs, cfg_ptr->out_drv_ctl_cs, hddrss[ddr_chan], dimm_slot);
                                        status = COM_ERROR;
                                    }
                                }
                            }

                            if ((common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4) && (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM))
                            {
                                if (cfg_ptr->lrdm_db_drv_ck_bcom_bodt_bcke != common_cfg.slot_config[dimm_slot].lrdm_db_drv_ck_bcom_bodt_bcke)
                                {
                                    // DDR4 Only LRDIMM Value
                                    monaco_log(CRITICAL, "ERROR:  LRDIMM SPD Output Drive Strength for Clock and Data Buffer, bcom, bodt, bcke Mismatch, \
                                                          expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                           common_cfg.slot_config[dimm_slot].lrdm_db_drv_ck_bcom_bodt_bcke, cfg_ptr->lrdm_db_drv_ck_bcom_bodt_bcke, hddrss[ddr_chan], dimm_slot);
                                    status = COM_ERROR;
                                }
                                else if (cfg_ptr->lrdm_db_drv_ck_bck != common_cfg.slot_config[dimm_slot].lrdm_db_drv_ck_bck)
                                {
                                    // DDR4 Only LRDIMM Value
                                    monaco_log(CRITICAL, "ERROR:  LRDIMM SPD Output Drive Strength for Clock and Data Buffer, bck Mismatch, \
                                                          expected 0x%2.2x got 0x%2.2x in Chan %u  Slot %u\n",
                                           common_cfg.slot_config[dimm_slot].lrdm_db_drv_ck_bck, cfg_ptr->lrdm_db_drv_ck_bck, hddrss[ddr_chan], dimm_slot);
                                    status = COM_ERROR;
                                }
                            }
                        }
                    }
                }
            }
        }


        if(chan_populated)
        {
            ++num_chans_poped;

            // Note: HDDRSS4 is considered odd, and HDDRSS5 is considered even
            if((ddr_chan % 2) == 0)
            {
                //Even channel
                ++num_even_chans;
            }
            else
            {
                //Odd channel
                ++num_odd_chans;
            }
        }
    }


    if(num_chans_poped == 0)
    {
        monaco_log(CRITICAL, "ERROR:  No DIMMS found!\n");
        status = COM_ERROR;
    }
    else if((num_even_chans != num_odd_chans))
    {
        monaco_log(CRITICAL, "ERROR:  Number of populated channels is not balanced, even=%d, odd=%d\n",
                num_even_chans, num_odd_chans);
        status = COM_ERROR;
    }


    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function gets the various timing values and combines / collects them
*    into a package.
*
*                                  @param
*    mem_freq_ps    The memory frequency expressed in picoseconds.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_get_combined_timing_vals(uint32_t mem_freq_ps)
{
    uint8_t ddr_chan;
    uint8_t dimm_slot;
    spd_dimm_config_t *cfg_ptr;

    uint8_t first_iter = 0x1;
    uint8_t new_cl_high_bit;
    uint8_t old_cl_high_bit;

    uint32_t dimm_trcd_min_clk;
    uint32_t dimm_trp_min_clk;
    uint32_t dimm_tras_min_clk;
    uint32_t dimm_trc_min_clk;
    uint32_t dimm_tfaw_min_clk;
    uint32_t dimm_twr_min_clk;
    uint32_t dimm_twtr_min_clk;

    // DDR3 Only
    uint32_t dimm_trrd_min_clk;
    uint32_t dimm_trtp_min_clk;

    // DDR4 Only
    uint32_t dimm_trrdl_min_clk;
    uint32_t dimm_trrds_min_clk;
    uint32_t dimm_tccdl_min_clk;
    uint32_t dimm_twtrs_min_clk;


    mddr_timing_vals.cas_lat_sup  = 0x0;

    mddr_timing_vals.taa_min_ps   = 0;
    mddr_timing_vals.tck_min_ps   = 0;
    mddr_timing_vals.tck_max_ps   = 0;

    mddr_timing_vals.trcd_min_clk = 0;
    mddr_timing_vals.trp_min_clk  = 0;
    mddr_timing_vals.tras_min_clk = 0;
    mddr_timing_vals.trc_min_clk  = 0;
    mddr_timing_vals.tfaw_min_clk = 0;

    mddr_timing_vals.trrd_min_clk = 0;
    mddr_timing_vals.twr_min_clk  = 0;
    mddr_timing_vals.twtr_min_clk = 0;
    mddr_timing_vals.trtp_min_clk = 0;
    mddr_timing_vals.trfc_min_ps = 0;

    mddr_timing_vals.trrdl_min_clk = 0;
    mddr_timing_vals.trrds_min_clk = 0;
    mddr_timing_vals.tccdl_min_clk = 0;
    mddr_timing_vals.trfc1_min_ps = 0;
    mddr_timing_vals.trfc2_min_ps = 0;
    mddr_timing_vals.trfc4_min_ps = 0;
    mddr_timing_vals.twtrs_min_clk = 0;

    mddr_timing_vals.tstab_clk = 0;
    mddr_timing_vals.tckev_min_clk = 0;

    // Go through each DIMM configuration and incorporate its timing values.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

            if(cfg_ptr->dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                // Get the timing values for the DIMM in clock cycles.
                dimm_trcd_min_clk = mddr_get_num_clocks(cfg_ptr->trcd_min_ps, mem_freq_ps);
                dimm_trp_min_clk  = mddr_get_num_clocks(cfg_ptr->trp_min_ps, mem_freq_ps);
                dimm_tras_min_clk = mddr_get_num_clocks(cfg_ptr->tras_min_ps, mem_freq_ps);
                dimm_trc_min_clk  = mddr_get_num_clocks(cfg_ptr->trc_min_ps, mem_freq_ps);
                dimm_tfaw_min_clk = mddr_get_num_clocks(cfg_ptr->tfaw_min_ps, mem_freq_ps);
                dimm_twr_min_clk  = mddr_get_num_clocks(cfg_ptr->twr_min_ps, mem_freq_ps);
                dimm_twtr_min_clk = mddr_get_num_clocks(cfg_ptr->twtr_min_ps, mem_freq_ps);

                if((cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4) && (cfg_ptr->revision <= SPD_REVISION_1_0))
                {
                    // twtr_l=max(4nCK, 7.5ns) up to 2400, rest is TBD
                    dimm_twtr_min_clk = COM_MAX(dimm_twtr_min_clk, 4);
                }

                dimm_trrd_min_clk = mddr_get_num_clocks(cfg_ptr->trrd_min_ps, mem_freq_ps);
                dimm_trtp_min_clk = mddr_get_num_clocks(cfg_ptr->trtp_min_ps, mem_freq_ps);


                dimm_trrdl_min_clk = mddr_get_num_clocks(cfg_ptr->trrdl_min_ps, mem_freq_ps);
                dimm_trrds_min_clk = mddr_get_num_clocks(cfg_ptr->trrds_min_ps, mem_freq_ps);
                dimm_tccdl_min_clk = mddr_get_num_clocks(cfg_ptr->tccdl_min_ps, mem_freq_ps);
                dimm_twtrs_min_clk = mddr_get_num_clocks(cfg_ptr->twtrs_min_ps, mem_freq_ps);

                if((cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4) && (cfg_ptr->revision <= SPD_REVISION_1_0))
                {
                    // twtr_s=max(2nCK, 2.5ns) up to 2400, rest is TBD
                    dimm_twtrs_min_clk = COM_MAX(dimm_twtrs_min_clk, 2);
                }


                // First iteration, assign the CAS latency value as found
                if (first_iter == 0x1)
                {
                    mddr_timing_vals.cas_lat_sup  = cfg_ptr->cas_lat_sup;
                    first_iter = 0x0;
                }
                // For subsequent iterations, high & low latencies need to be combined, choosing lower side
                else
                {
                    new_cl_high_bit = (cfg_ptr->cas_lat_sup >> SPD_CAL_RANGE_BIT___S) & 0x1;
                    old_cl_high_bit = (mddr_timing_vals.cas_lat_sup >> SPD_CAL_RANGE_BIT___S) & 0x1;

                    if (new_cl_high_bit != old_cl_high_bit)
                    {
                        // CL: 23 to 36 (14 bits) overlap between low range and high range CAS latency bytes.
                        // Hence, to determine the common usable range, when we have SPDs with low and high ranges,
                        // we pick the bits corresponding to Cl=23 thru CL=36.
                        if (new_cl_high_bit > 0x0)    // New SPD has high CAS latency range
                        {
                            // remove bits 14 and higher, shift up to 16 bits
                            cfg_ptr->cas_lat_sup = cfg_ptr->cas_lat_sup & 0x3FFF;
                            cfg_ptr->cas_lat_sup = cfg_ptr->cas_lat_sup << 16;
                        }
                        else                          // old SPD has high CAS latency range
                        {
                            // remove bits 14 and higher, shift up to 16 bits
                            mddr_timing_vals.cas_lat_sup = mddr_timing_vals.cas_lat_sup & 0x3FFF;
                            mddr_timing_vals.cas_lat_sup = mddr_timing_vals.cas_lat_sup << 16;
                        }
                    }

                    // AND in the CAS latency of each dimm to get the common CAS latency across all DIMMs
                    mddr_timing_vals.cas_lat_sup = mddr_timing_vals.cas_lat_sup & cfg_ptr->cas_lat_sup;
                }


                // Keep the highest values.
                mddr_timing_vals.taa_min_ps   = COM_MAX(cfg_ptr->taa_min_ps,  mddr_timing_vals.taa_min_ps);
                mddr_timing_vals.tck_min_ps   = COM_MAX(cfg_ptr->tck_min_ps,  mddr_timing_vals.tck_min_ps);
                mddr_timing_vals.tck_max_ps   = COM_MAX(cfg_ptr->tck_max_ps,  mddr_timing_vals.tck_max_ps);

                mddr_timing_vals.trcd_min_clk = COM_MAX(dimm_trcd_min_clk, mddr_timing_vals.trcd_min_clk);
                mddr_timing_vals.trp_min_clk  = COM_MAX(dimm_trp_min_clk,  mddr_timing_vals.trp_min_clk);
                mddr_timing_vals.tras_min_clk = COM_MAX(dimm_tras_min_clk, mddr_timing_vals.tras_min_clk);
                mddr_timing_vals.trc_min_clk  = COM_MAX(dimm_trc_min_clk,  mddr_timing_vals.trc_min_clk);
                mddr_timing_vals.tfaw_min_clk = COM_MAX(dimm_tfaw_min_clk, mddr_timing_vals.tfaw_min_clk);
                mddr_timing_vals.twr_min_clk  = COM_MAX(dimm_twr_min_clk,  mddr_timing_vals.twr_min_clk);
                mddr_timing_vals.twtr_min_clk = COM_MAX(dimm_twtr_min_clk, mddr_timing_vals.twtr_min_clk);

                mddr_timing_vals.trrd_min_clk = COM_MAX(dimm_trrd_min_clk, mddr_timing_vals.trrd_min_clk);
                mddr_timing_vals.trtp_min_clk = COM_MAX(dimm_trtp_min_clk, mddr_timing_vals.trtp_min_clk);
                mddr_timing_vals.trfc_min_ps = COM_MAX(cfg_ptr->trfc_min_ps, mddr_timing_vals.trfc_min_ps);

                mddr_timing_vals.trrdl_min_clk = COM_MAX(dimm_trrdl_min_clk, mddr_timing_vals.trrdl_min_clk);
                mddr_timing_vals.trrds_min_clk = COM_MAX(dimm_trrds_min_clk, mddr_timing_vals.trrds_min_clk);
                mddr_timing_vals.tccdl_min_clk = COM_MAX(dimm_tccdl_min_clk, mddr_timing_vals.tccdl_min_clk);
                mddr_timing_vals.trfc1_min_ps = COM_MAX(cfg_ptr->trfc1_min_ps, mddr_timing_vals.trfc1_min_ps);
                mddr_timing_vals.trfc2_min_ps = COM_MAX(cfg_ptr->trfc2_min_ps, mddr_timing_vals.trfc2_min_ps);
                mddr_timing_vals.trfc4_min_ps = COM_MAX(cfg_ptr->trfc4_min_ps, mddr_timing_vals.trfc4_min_ps);
                mddr_timing_vals.twtrs_min_clk = COM_MAX(dimm_twtrs_min_clk, mddr_timing_vals.twtrs_min_clk);

                if (mddr_dimm_configs[ddr_chan][dimm_slot].dev_type == SPD_DEVICE_TYPE_DDR4)
                {
                    mddr_timing_vals.trfc_min_ps = mddr_timing_vals.trfc1_min_ps;
                }
            }
        }
    }


    if(platform_mode != SILICON)
    {
        // Bump up trfc for emulation
        mddr_timing_vals.trfc_min_ps = COM_MAX(mddr_timing_vals.trfc_min_ps, 0x9EB100);

        // Bump up trfc2 for emulation
        mddr_timing_vals.trfc2_min_ps *= 3;

        // Bump up trfc4 for emulation
        mddr_timing_vals.trfc4_min_ps *= 3;
    }

    //
    // Get derived timing values. These are derived based on other configuration information and some are
    //  based in part on the the above SPD based timing values.
    //

    mddr_timing_vals.tck_ps = mddr_get_clock_period_timing_val();
    mddr_timing_vals.txs_clk = mddr_get_derived_txs_timing_val(mddr_timing_vals.trfc_min_ps);
    mddr_timing_vals.txsdll_min_clk = mddr_get_derived_txsdll_timing_val();
    mddr_timing_vals.tdllk_min_clk = mddr_get_derived_tdllkmin_timing_val();
    mddr_timing_vals.tstab_clk = mddr_get_derived_tstab_timing_val();
    mddr_timing_vals.tckev_min_clk = mddr_get_derived_tckevmin_timing_val();
}



/*!****************************************************************************
*
* @par Description:
*    This function determines the DDR latencies using the provided configuration
*    and settings.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*                                  @param
*    latencies_ptr          The pointer to the structure containing the latencies
*                             as calculated / determined by this function.
*
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    CAL and Control Gear Down modes are not supported in Rev 1. When supported
*    in Rev 2, they will be incorporated into the read latency (RL) and MR4 values
*    per Table 10, page 20 of JEDEC DDR4 Specification(JESD79-4) for
*    DDR4 configurations.
*
******************************************************************************/
void mddr_get_latency_vals
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr,
    mddr_latencies_t *latencies_ptr
)
{
    uint32_t cl;
    uint32_t orl;
    uint32_t rl;
    uint32_t wl;
    uint32_t cwl;
    uint32_t pl = 0;
    uint32_t tdbi = 0;
    uint32_t tcal = 0;
    uint8_t tmod;
    uint8_t tmrd;
    uint8_t mc_mr2_cwl;
    uint8_t mc_mr4_cal = 0;
    uint8_t mc_mr5_pl;
    uint8_t rcd_nladd = 0;


    // Get the CAS Latency.
    cl = mddr_get_cas_latency(common_cfg_ptr);

    //! @todo -GPK- AL to be added to both RL and WL if/when AL is supported.
    //    Write Latency = AL+CWL+PL. Read Latency = AL+CL+PL. Per
    //     Table 42, page 69 of JEDEC DDR4 Specification(JESD79-4)

    //! @todo -GPK- For Rev 2 when CAL and Geardown are supported include tcal and mc_mr4_cal.
    //    rl = rl + tpdm + tcal + tdbi + pl;
    rl = cl;


    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR3)
    {
        // CWL per Figure 11, page 30 of JEDEC DDR3 Specification(JESD79-3F_DDR3.pdf)

        if (mem_freq_ps >= 5000)    // less than 200 MHz clock, assuming DLL off mode
        {                           // JEDEC says if DLL=off only CWL=6 is guaranteed
            cwl = 6;
            mc_mr2_cwl = 1;
        }
        else if (mem_freq_ps >= 2500)
        {
            cwl = 5;
            mc_mr2_cwl = 0;
        }
        else if (mem_freq_ps >= 1875)
        {
            cwl = 6;
            mc_mr2_cwl = 1;
        }
        else if (mem_freq_ps >= 1500)
        {
            cwl = 7;
            mc_mr2_cwl = 2;
        }
        else if (mem_freq_ps >= 1250)
        {
            cwl = 8;
            mc_mr2_cwl = 3;
        }
        else if (mem_freq_ps >= 1070)
        {
            cwl = 9;
            mc_mr2_cwl = 4;
        }
        else if (mem_freq_ps >= 935)
        {
            cwl = 0xA;
            mc_mr2_cwl = 5;
        }
        else if (mem_freq_ps >= 833)
        {
            cwl = 0xB;
            mc_mr2_cwl = 6;
        }
        else if (mem_freq_ps >= 750)
        {
            cwl = 0xC;
            mc_mr2_cwl = 7;
        }
        else
        {
            // This should not possible but default just in case
            cwl = 0xC;
            mc_mr2_cwl = 7;
        }

        mc_mr5_pl = 0;


        if (common_cfg_ptr->mod_type == SPD_MODULE_TYPE_RDIMM)
        {
            rcd_nladd = 1;
            tmrd = 8;
        }
        else
        {
            tmrd = 4;
        }

        if (common_cfg_ptr->mod_type == SPD_MODULE_TYPE_DDR3_LRDIMM)
        {
            rcd_nladd = 2;
        }

        tmod = max_of_clk_ps(12, 15000, mem_freq_ps); // max of 12nCK, 15ns
    }
    else    //    if (&dev_type==&SPD_DEVICE_TYPE_DDR4)
    {
        // Invalid value used when no DRAM parity
        mc_mr5_pl = 0;

        tmod = max_of_clk_ps(24, 15000, mem_freq_ps); // max of 24nCK, 15ns
        tmrd = 8;

        //
        // From JESD79-4 - JEDEC DDR4 Specification
        //
        // DRAM parity
        if ((mddr_settings_ptr->ca_parity == CA_PARITY_DRAM) ||
            (mddr_settings_ptr->ca_parity == CA_PARITY_DRAM_DIMM))
        {
            // DRAM parity
            // PL per Table 42, page 69 of JEDEC DDR4 Specification(JESD79-4)
            if (ddr_rate <= 2133)
            {
                pl = 4;
                mc_mr5_pl = 1;
            }
            else if (ddr_rate <= 2666)
            {
                pl = 5;
                mc_mr5_pl = 2;
            }
            else if (ddr_rate <= 3200)
            {
                pl = 6;
                mc_mr5_pl = 3;
            }
            else        // RFU in Jedec Spec
            {
                pl = 8;
                mc_mr5_pl = 4;
            }
        }


        if (common_cfg_ptr->mod_type != SPD_MODULE_TYPE_UDIMM)
        {
            if (ddr_rate <= 2400)
            {
                rcd_nladd = 1;       // 1nCK latency addr
            }
            else
            {
                rcd_nladd = 2;       // 2nCK latency addr
            }
        }


        // tAA_DBI per Table 80, page 163 of JEDEC DDR4 Specification(JESD79-4)
        // DBI Read enabled
        if ((mddr_settings_ptr->dbi_mode == DDR_DBI_READ) ||
            (mddr_settings_ptr->dbi_mode == DDR_DBI_READ_WRITE))
        {
            if (ddr_rate < 2132) // handle half freq at 2133
            {
                tdbi = 2;   // tAA_DBI (tAA + tDBI) in clock cycles instead of ps. From table 107,108,JESD79-4B
            }
            else if (ddr_rate < 2932)  // handle half freq at 2133
            {
                tdbi = 3;   // From table 109 to 111,JESD79-4B
            }
            else
            {
                tdbi = 4;   // From table 112,113,JESD79-4B
            }


            // Adding tdbi to cl
            // if (common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X8)
            if ((common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X8) || (common_cfg_ptr->sdram_width == SPD_SDRAM_WIDTH_X16))
            {
                cl = cl + tdbi;
            }
        }

        // CWL per Table 6, page 16 of JEDEC DDR4 Specification(JESD79-4)
        if (ddr_rate <= 1600)
        {
            if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
               (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
            {
                cwl = 0xA;
                mc_mr2_cwl = 1;
            }
            else
            {
                cwl = 9;
                mc_mr2_cwl = 0;
            }
        }
        else if (ddr_rate <= 1866)
        {
            if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
               (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
            {
                cwl = 0xB;
                mc_mr2_cwl = 2;
            }
            else
            {
                cwl = 0xA;
                mc_mr2_cwl = 1;
            }
        }
        else if (ddr_rate <= 2133)
        {
            if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
               (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
            {
                cwl = 0xC;
                mc_mr2_cwl = 3;
            }
            else
            {
                cwl = 0xB;
                mc_mr2_cwl = 2;
            }
        }
        else if (ddr_rate <= 2400)
        {
            if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
               (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
            {
                cwl = 0xE;
                mc_mr2_cwl = 4;
            }
            else
            {
                cwl = 0xC;
                mc_mr2_cwl = 3;
            }
        }
        else if (ddr_rate <= 2666)
        {
            if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
               (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
            {
                cwl = 0x10;
                mc_mr2_cwl = 5;
            }
            else
            {
                cwl = 0xE;
                mc_mr2_cwl = 4;
            }
        }
        else // if (ddr_rate <= 3200)   // TBD in Jedec Spec
        {
            if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
               (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
            {
                cwl = 0x12;
                mc_mr2_cwl = 6;
            }
            else
            {
                cwl = 0x10;
                mc_mr2_cwl = 5;
            }
        }


        // DDR4 CAL mode related settings.

        // !! NOT supported in the controller
        if (mddr_settings_ptr->ddr4_cal_mode_en)
        {
            monaco_log(HIGH, "Command address latency not supported, not enabling!\n");
#if 0
            if (ddr_rate <= 1600)
            {
                tcal = 3;
                mc_mr4_cal = 1;
            }
            else if (ddr_rate <= 2133)
            {
                tcal = 4;
                mc_mr4_cal = 2;
            }
            else if (ddr_rate <= 2400)
            {
                tcal = 5;
                mc_mr4_cal = 3;
            }
            else if (ddr_rate <= 2666)   // TBD in Jedec Spec
            {
                tcal = 6;
                mc_mr4_cal = 4;
            }
            else // if (ddr_rate <= 3200)   // TBD in Jedec Spec
            {
                tcal = 8;
                mc_mr4_cal = 5;
            }

            // For Rev 2 when CAL and Geardown are supported add optional tcal to tmod.
            tmod += tcal;
#endif
        }


    // Geardown mode needs even CL, CWL, tCAL, PL, WR, rd2Pch
    if (mddr_settings_ptr->ddr4_geardown_mode_en)
        {

            if ((cl % 2) == 1)
            {
               ++cl;
            }

            if ((rl % 2) == 1)
            {
               ++rl;
            }

            // WR and rd2Pch needs to be even
            if ((cwl % 2) == 1)
            {                           // cwl={9 or 11}
               ++cwl;
               ++mc_mr2_cwl;
            }

            if ((tcal % 2) == 1)           // odd tcal
            {
                ++tcal;
                ++mc_mr4_cal;
            }

            if ((pl % 2) == 1)
            {
                ++pl;
                ++mc_mr5_pl;
            }

            // tRTP, tWR handled in other FNs
        }
    }



    orl = rl + rcd_nladd + tcal + tdbi + pl;


    //! @todo -GPK- AL to be added to both RL and WL if/when AL is supported.
    //    Write Latency = AL+CWL+PL. Read Latency = AL+CL+PL. Per
    //     Table 42, page 69 of JEDEC DDR4 Specification(JESD79-4)
    wl = cwl + pl;
#ifdef CONFIG_PRE_Z1
	pl = 5;
	cwl = 20;
	wl = 20;
	mc_mr2_cwl = 20;
#endif

    // Record all of the latencies.
    latencies_ptr->cl = cl;
    latencies_ptr->cwl = cwl;
    latencies_ptr->pl = pl;
    latencies_ptr->tcal = tcal;
    latencies_ptr->tmod = tmod;
    latencies_ptr->tmrd = tmrd;
    latencies_ptr->orl = orl;
    latencies_ptr->rl = rl;
    latencies_ptr->wl = wl;
    latencies_ptr->tdbi = tdbi;
    latencies_ptr->mc_mr2_cwl = mc_mr2_cwl;
    latencies_ptr->mc_mr5_pl = mc_mr5_pl;
    latencies_ptr->rcd_nladd = rcd_nladd; // Currently unused / unnecessary due to PHY & MC interactions

    monaco_log(INFORMATIONAL, "       RL = 0x%2.2x, WL = 0x%2.2x, PL = 0x%2.2x, tDBI = 0x%2.2x, tMOD = 0x%2.2x, tMRD = 0x%2.2x\n", rl, wl, pl, tdbi, tmod, tmrd);
    monaco_log(INFORMATIONAL, "         CWL = 0x%2.2x, MR2_CWL = 0x%2.2x, MR5_PL = 0x%2.2x, ORL= 0x%2.2x\n\n", cwl, mc_mr2_cwl, mc_mr5_pl, orl);
}




/*!****************************************************************************
*
* @par Description:
*    This function determines the vaue for the DDR clock period timing value.
*
* @return
*    The DDR clock period timing value in ps.
*
* @author
*    gkowis
*
* @par Notes:
*    per Tables 46 & 47 of JEDEC DDR3 Specification(JESD79-3F)
*    per Table 86 of JEDEC DDR4 Specification(JESD79-4A)
*
******************************************************************************/
uint32_t mddr_get_clock_period_timing_val(void)
{
    uint32_t tck_ps;


    if (ddr_rate >= 3200)
    {
        tck_ps = 625;                  // 0.625ns
    }
    else if (ddr_rate >= 2933)
    {
        tck_ps = 682;                  // 0.682ns
    }
    else if (ddr_rate >= 2666)
    {
        tck_ps = 750;                 // 0.750ns
    }
    else if (ddr_rate >= 2400)
    {
        tck_ps = 833;                 // 0.833ns
    }
    else if (ddr_rate >= 2133)
    {
        tck_ps = 938;                  // 0.938ns
    }
    else if (ddr_rate >= 1866)
    {
        tck_ps = 1071;                 // 1.071ns
    }
    else if (ddr_rate >= 1600)
    {
        tck_ps = 1250;                 // 1.250ns
    }
    else if (ddr_rate >= 1333)
    {
        tck_ps = 1500;                 // 1.500ns
    }
    else if (ddr_rate >= 1066)
    {
        tck_ps = 1875;                 // 1.875ns
    }
    else
    {
        tck_ps = 2500;                 // 2.500ns
    }


    return tck_ps;
}



/*!****************************************************************************
*
* @par Description:
*    This function determines the vaue for the tXS timing value. The time for
*     commands to exit self refresh without a locked DLL
*
*                                  @param
*    tRFC_min_ps            MAX across channels minimum tRFC in ps
*
* @return
*    The txs timing value, in clocks.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_get_derived_txs_timing_val(uint32_t trfc_min_ps)
{
    uint32_t txs_clk;

    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        txs_clk = mddr_get_num_clocks((trfc_min_ps + 10000), mem_freq_ps);
        txs_clk = COM_MAX(txs_clk, 5);  // tXS=max 5ck, trfc_min_clk + 10ns
    }
    else    // DDR3
    {
        if(platform_mode == SILICON)
        {
            txs_clk = mddr_get_num_clocks(mddr_timing_vals.trfc_min_ps, mem_freq_ps);
            txs_clk = COM_MAX(5, txs_clk);  // tXS=max 5ck, trfc_min_clk
        }
        else
        {
            txs_clk = 5;  // 5ck for emulation speeds
        }
    }


    return txs_clk;
}



/*!****************************************************************************
*
* @par Description:
*    This function determines the value for the tXSDLL timing value. The
*     minimum time for commands to exit self refresh with a locked DLL.
*
* @return
*    The tsxdll timing value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_get_derived_txsdll_timing_val(void)
{
    uint32_t txsdll_min_clk;


    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        // txsdll = tDLLKmin
        // JEDEC Standard No. 79-4B: Table 14 P. 26
        // JEDEC Standard No. 79-4B: Table 132, 133

        if (ddr_rate <= 1600)
        {
            txsdll_min_clk = 597;
        }
        else if (ddr_rate <= 1866)
        {
            txsdll_min_clk = 597;
        }
        else if (ddr_rate <= 2133)
        {
            txsdll_min_clk = 768;
        }
        else if (ddr_rate <= 2400)
        {
            txsdll_min_clk = 768;
        }
        else if (ddr_rate <= 2666)
        {
            txsdll_min_clk = 854;
        }
        else if (ddr_rate <= 2933)
        {
            txsdll_min_clk = 940;
        }
        else // ddr_rate <= 3200
        {
            txsdll_min_clk = 1024;
        }
    }
    else
    {
        // txsdll = tDLLKmin : 512 Clocks for DDR3
        txsdll_min_clk = 512;
    }


    return txsdll_min_clk;
}



/*!****************************************************************************
*
* @par Description:
*    This function determines the vaue for the tDLLKmin timing value. The
*     minimum DLL lock time.
*
* @return
*    The tsxdll timing value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_get_derived_tdllkmin_timing_val(void)
{
    uint32_t tdllkmin_clk;

    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        // JEDEC Standard No. 79-4B: Table 14 P. 26
        // JEDEC Standard No. 79-4B: Table 132, 133

        if (ddr_rate <= 1600)
        {
            tdllkmin_clk = 597;
        }
        else if (ddr_rate <= 1866)
        {
            tdllkmin_clk = 597;
        }
        else if (ddr_rate <= 2133)
        {
            tdllkmin_clk = 768;
        }
        else if (ddr_rate <= 2400)
        {
            tdllkmin_clk = 768;
        }
        else if (ddr_rate <= 2666)
        {
            tdllkmin_clk = 854;
        }
        else if (ddr_rate <= 2933)
        {
            tdllkmin_clk = 940;
        }
        else
        {
            // ddr_rate > 2666 (i.e. 3200)
            tdllkmin_clk = 1024;
        }
    }
    else
    {
        tdllkmin_clk = 512;
    }


    return tdllkmin_clk;
}


/*!****************************************************************************
*
* @par Description:
*    This function determines the vaue for the tstab timing value.
*     Stabilization time - command buffer chip.
*
* @return
*    The tstab timing value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_get_derived_tstab_timing_val(void)
{
    uint32_t tstab_clk = 0x0;

    // 5us
    tstab_clk = max_of_clk_ps(0, 0x4C4B40, mem_freq_ps);


    return tstab_clk;
}


/*!****************************************************************************
*
* @par Description:
*    This function determines the vaue for the tckevmin timing value.
*     Minimum number of DDR cycles to stay low when the CK_t/CK_c are pulled low.
*
* @return
*    The tckevmin timing value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_get_derived_tckevmin_timing_val(void)
{
    uint32_t tckev_min_clk = 0x0;

    if (ddr_rate < 2400)
    {
        tckev_min_clk = 0x4;
    }
    else if (ddr_rate < 2933)
    {
        tckev_min_clk = 0x6;
    }
    else
    {
        tckev_min_clk = 0x8;
    }

    return tckev_min_clk;
}


/*!****************************************************************************
*
* @par Description:
*    This function determines the manual CK and CKE values for the slots of a
*     DDR channel. The value is used in manual CKE writes to control the target
*     CKE groups.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    The CK and CKE values can differ between slots since the number of ranks
*     in the individual DIMMs can be different.
*
******************************************************************************/
void mddr_get_slots_ck_cke(void)
{
    uint8_t ck_sel;
    uint8_t cke_sel;
    uint8_t dimm_slot;


    ck_sel = 0x0;
    cke_sel = 0x0;

    for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        if (common_cfg.slot_config[dimm_slot].num_ranks != SPD_INVALID_RANK_COUNT)
        {
            // RDIMMs only use enable CK0
            if(common_cfg.slot_config[dimm_slot].num_ranks > 1)
            {
                cke_sel |= CKE_MULTI << (dimm_slot * CKE_PER_SLOT);    //enable both CKE's

                // Note: for RDIMM disable CK1 in the PHY
                ck_sel |= cke_sel;    // enable CK0 & CK1
            }
            else
            {
                cke_sel |= CKE_SINGLE << (dimm_slot * CKE_PER_SLOT);
                ck_sel |= cke_sel;
            }
        }
    }

    common_cfg.slots_ck_sel = ck_sel;
    common_cfg.slots_cke_sel = cke_sel;
}



/*!****************************************************************************
*
* @par Description:
*    This function determines the CAS latency using the provided configuration
*    and settings.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
*
* @return
*    The CAS latency in clock cycles.
*
* @author
*    gkowis
*
* @par Notes:
*    The configuration reflects what DIMMs are present in the system and the
*    settings reflect the desired configurable options.
*
* @verbatim
*     400   533   666   800    933   1066   1200   1333   1600 MHz clock
*     800  1066  1333  1600   1866   2133   2400   2666   3200 MT/s
*    (2.5, 1.876, 1.5, 1.25, 1.071, 0.938, 0.833, 0.750, 0.625 ns)
* @endverbatim
*
******************************************************************************/
uint32_t mddr_get_cas_latency
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t default_cas_latency;
    uint32_t max_cas_latency;
    uint32_t cl;
    unsigned status = COM_OK;
    uint32_t sup_cl_start;
    uint32_t cl_in_sup;
    uint32_t taamax_ps;
    bool found = false;


    //==============================================================================
    //  1. AND in the CAS_LAT_SUPPORTED of each dimm (get common CL)
    //  2. find largest tAAmin
    //  3. find largest tCKmin (common highest supported freq)
    //  4. if desired freq(tCKproposed) not standard JEDEC value
    //
    //   400   533   666   800    933   1066   1200   1333   1466   1600  MHz clock
    //   800  1066  1333  1600   1866   2133   2400   2666   2933   3200  MT/s
    //  (2.5, 1.876, 1.5, 1.25, 1.071, 0.938, 0.833, 0.750, 0.682, 0.625  ns) choose lower of the 2
    //  DDR3------------------------------------------------------------------------
    //    6     7     9     11     13     14  15-16?     ?                CAS latency
    //    5     6     7      8      9     10     11     12                CAS write latency
    //  DDR4------------------------------------------------------------------------
    //                      11     13     15  16-18  18-20  20-22  22-24  CAS latency
    //                       9     10     11    12      14     16     16  CAS write latency
    //
    //==============================================================================

    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR3)
    {
        // DDR3
        default_cas_latency = DDR3_DEFAULT_CAS_LATENCY;
        max_cas_latency = DDR3_CL_MAX;
        sup_cl_start = DDR3_CL_START;   // CL starts at 4
        taamax_ps = DDR3_TAAMAX;
    }
    else
    {
        // DDR4
        default_cas_latency = DDR4_DEFAULT_CAS_LATENCY;

        if ((mddr_timing_vals.cas_lat_sup >> 31) == 0x0)
        {
            // CAS Latency low range
            max_cas_latency = DDR4_CL_MAX_LR;
            sup_cl_start = DDR4_CL_START_LR;   // CL starts at 0x7
        }
        else
        {
            // CAS Latency high range
            max_cas_latency = DDR4_CL_MAX_HR;
            sup_cl_start = DDR4_CL_START_HR;   // CL starts at 0x17
        }

        taamax_ps = DDR4_TAAMAX;
    }


    if(platform_mode == SILICON)
    {
        cl = default_cas_latency;

        if (mem_freq_ps < 625)
        {
            monaco_log(HIGH, "Error too fast DIMM speed desired\n");
            status = COM_ERROR;
        }
        else if (mddr_timing_vals.tck_min_ps > mem_freq_ps)
        {
            monaco_log(HIGH, "ERROR : Desired frequency is faster than DIMMs support\n");
            status = COM_ERROR;
        }
        else if (mem_freq_ps > mddr_timing_vals.tck_max_ps)
        {
            monaco_log(HIGH, "Warning : Desired frequency is slower than DIMMs support\n");
            status = COM_ERROR;
        }
        else
        {
            cl = mddr_get_num_clocks(mddr_timing_vals.taa_min_ps, mem_freq_ps);
        }


        // Find the closest supported CAS latency.
        do
        {
            // Convert the CAS latency to match format in supported CAS Latency flags bitmap.
            cl_in_sup = (1 << (cl - sup_cl_start));

            if((cl_in_sup & (mddr_timing_vals.cas_lat_sup)) == 0)
            {
                // CAS latency is not in the common supported list so move to the next value
                ++cl;
            }
            else
            {
                found = true;
            }
        } while((cl < max_cas_latency) && (!found));


        // Check for CAS latency in CL supported bitmap(cas_lat_sup) to determine if it is a CL supported by the DIMMs.
        if (!found)
        {
            monaco_log(HIGH, "ERROR : Supported CAS Latency not found, supported bitmap=0x%8.8x\n",
                   mddr_timing_vals.cas_lat_sup);
            monaco_log(HIGH, "    ERROR :  Need to choose higher tCK (slower speed)\n");
            status = COM_ERROR;
        }
        else if (taamax_ps < (cl * mem_freq_ps))
        {
            monaco_log(HIGH, "ERROR TAAMAX exceeded for this CL & frequency combination\n");
            status = COM_ERROR;
        }

        if (status == COM_ERROR)
        {
            cl = default_cas_latency;   // default if in error.
            monaco_log(HIGH, "ERROR : Finding valid CAS Latency for freq, defaulting to %d\n", cl);
        }
    }
    else
    {
        cl = default_cas_latency;
    }

    monaco_log(INFORMATIONAL, "CAS Latency of %d selected for freq = %d MHz\n\n", cl, mem_freq_mhz);

    return cl;
}



/*!****************************************************************************
*
* @par Description:
*    This function finds max between a clock cycle value and a ps time value
*    based on frequency.
*
*                                  @param
*    i_clks         The number of clocks.
*                                  @param
*    i_ps           The number of picoseconds.
*                                  @param
*    freq_ps        The number of picoseconds per clock for a given frequency
*                   in MHz.
*
*
* @return
*    The number of clock cycles.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t max_of_clk_ps(uint32_t i_clks, uint32_t i_ps, uint32_t freq_ps)
{
    uint32_t num_clks;


    num_clks = mddr_get_num_clocks(i_ps, freq_ps);
    num_clks = COM_MAX(num_clks, i_clks);


    return num_clks;
}



/*!****************************************************************************
*
* @par Description:
*    This function calculates the number of clock cycles at a given frequency
*    that would occur for a given time in picoseconds.
*
*                                  @param
*    txx_ps         The number of picoseconds to translate into clock cycles.
*                                  @param
*    freq_ps        The number of picoseconds per clock for a given frequency
*                   in MHz.
*
*
* @return
*    The number of clock cycles.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_get_num_clocks(uint32_t txx_ps, uint32_t freq_ps)
{
    uint32_t num_clks;
    uint32_t remainder;
    uint64_t txx_ps_scaled;
    uint64_t freq_ps_scaled;


    // do guardband (-0.01 clk before ceiling FN)

    // Scale up so the frequency in ps can be used as the .01 guardband
    txx_ps_scaled = 100 * txx_ps;
    freq_ps_scaled = 100 * freq_ps;

    //  Make the adjustment for the guardband
    if (txx_ps_scaled >= freq_ps)
    {
        txx_ps_scaled -= freq_ps;
    }

    num_clks = txx_ps_scaled / freq_ps_scaled;
    remainder = txx_ps_scaled % freq_ps_scaled;

    if (remainder != 0)    //ceiling (round up if remainder)
    {
        num_clks = num_clks + 1;
    }

    return num_clks;
}



/*!****************************************************************************
*
* @par Description:
*    This function sets a value in a configuration / control register.
*
*                                  @param
*    mddr_reg_addr          The address of the configuration register to set.
*                                  @param
*    reg_name_str           String name of the register to use in displaying
*                           the register value in verbose mode.
*                                  @param
*    reg_val                The value to store into the register.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_set_reg
(
    uint64_t mddr_reg_addr,
    char *reg_name_str,
    uint32_t reg_val
)
{
    uint32_t mddr_reg_addr_low;

    mddr_reg_addr_low = (uint32_t)(mddr_reg_addr & 0xFFFFFFFF);

#ifdef __BAREMETAL__
    if (reg_report)
    {
        monaco_log(INFORMATIONAL, " MDDR_%-22s (0x%08X) = 0x%08X\n",
                 reg_name_str, mddr_reg_addr_low, reg_val);
    }
    else
    {
        monaco_log(INFORMATIONAL, "     Setting %-25s = 0x%x\n", reg_name_str, reg_val);
    }
#endif

    write32(mddr_reg_addr, reg_val);
}



/*!****************************************************************************
*
* @par Description:
*    This function gets a value from a configuration / control register.
*
*                                  @param
*    mddr_reg_addr          The address of the memory controller configuration
*                           register to set.
*                                  @param
*    reg_name_str           String name of the register to use in displaying
*                           the register value in verbose mode.
*
* @return
*    The value stored in the register.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_get_reg
(
    uint64_t mddr_reg_addr,
    char *reg_name_str
)
{
    uint32_t reg_val;
    uint32_t mddr_reg_addr_low;


    mddr_reg_addr_low = (uint32_t)(mddr_reg_addr & 0xFFFFFFFF);

    reg_val = read32(mddr_reg_addr);

#ifdef __BAREMETAL__
    if (reg_report)
    {
        monaco_log(INFORMATIONAL, " Reading MDDR_%-25s (0x%08X) = 0x%08X\n",
                 reg_name_str, mddr_reg_addr_low, reg_val);
    }
    else
    {
        monaco_log(INFORMATIONAL, "     Reading %-28s = 0x%08x\n", reg_name_str, reg_val);
    }
#endif

    return reg_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function manipulates specific fields of a configuration /
*     control register.
*
*                                  @param
*    mddr_reg_addr          The address of the memory controller configuration
*                           register to manipulate.
*                                  @param
*    reg_name_str           String name of the register to use in displaying
*                           the register value in verbose mode.
*                                  @param
*    mask
*                                  @param
*    set_bits
*
* @return
*    None.
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_rmw_reg
(
    uint64_t mddr_reg_addr,
    char *reg_name_str,
    uint32_t mask,
    uint32_t set_bits
)
{
    uint32_t reg_val;


    reg_val = mddr_get_reg(mddr_reg_addr, reg_name_str);

    // Clear out previous bits.
    reg_val &= ~(mask);
    reg_val |= set_bits;

    mddr_set_reg(mddr_reg_addr, reg_name_str, reg_val);
}



/*!****************************************************************************
*
* @par Description:
*    This function samples a register, waiting for a specific value for a set
*     of bits read from the register.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the memory controller.
*                                  @param
*    s_addr_offset          Address offset of the register to sample.
*                                  @param
*    mask                   Mask to apply to the data to isolate the bits of
*                            interest.
*                                  @param
*    value                  The value that should eventually be reflected in
*                            the bits being inspected.
*                                  @param
*    to_ms                  Timeout in ms.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_rd_chk_reg
(
    uint64_t mddr_base_addr,
    uint64_t s_addr_offset,
    uint64_t mask,
    uint32_t value,
    uint32_t to_ms
)
{
    uint32_t reg_value;
    uint32_t wait_time_us = 0;
    uint32_t wait_time_ms;
    uint32_t tick_marks = 0;


    do
    {
        // Delay for 1us before each read to avoid beating on the target register and
        //  to provide an easy way to track the time to allow the timeout.
        mddr_mc_wait_us(mddr_base_addr, 1);

        ++wait_time_us;
        wait_time_ms = wait_time_us / MICRO_SEC_PER_MILLI_SEC;

        // Provide feedback for long delays
        if((wait_time_us % 10000) == 0x0)
        {
            if(tick_marks == 20)
            {
                tick_marks = 0;
                monaco_log(LOW, ". \n");
            }
            else
            {
                ++tick_marks;
                monaco_log(LOW, ". ");
            }
        }

        // Extract only the bits of interest from the register.
        reg_value = read32(mddr_base_addr + s_addr_offset) & mask;
    } while((reg_value != value) && ( wait_time_ms < to_ms));

    monaco_log(LOW, "\n\n");

    if(reg_value != value)
    {
        monaco_log(HIGH, "    Timeout waiting on read val : Expected 0x%8.8x  Got 0x%8.8x\n", value, reg_value);
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function polls a field of a register until the field is cleared.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    mddr_reg_addr   The address of the memory controller configuration
*                     register to poll.
*                                  @param
*    reg_mask        The mask to apply to the register to isolate the target
*                     field.
*
*
* @return
*    None
*
* @author
*    gkowis, lchavani
*
******************************************************************************/
void mddr_wait_for_clear(uint64_t mddr_base_addr, uint64_t mddr_reg_addr, uint32_t reg_mask, uint8_t max_loops)
{
    uint32_t reg_val = 0x0;
    uint8_t i = 0;

    do
    {
        reg_val = read32(mddr_reg_addr);
        reg_val &= reg_mask;

        mddr_mc_wait_us(mddr_base_addr, 1);
        i++;
    } while((i < max_loops) && (reg_val == 0x0));
}



/*!****************************************************************************
*
* @par Description:
*    This function polls a field of a register until the field is set.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    mddr_reg_addr   The address of the memory controller configuration
*                     register to poll.
*                                  @param
*    reg_mask        The mask to apply to the register to isolate the target
*                     field.
*
*
* @return
*    None
*
* @author
*    gkowis, lchavani
*
******************************************************************************/
void mddr_wait_for_set(uint64_t mddr_base_addr, uint64_t mddr_reg_addr, uint32_t reg_mask, uint8_t max_loops)
{
    uint32_t reg_val = 0x0;
    uint8_t i = 0;

    do
    {
        reg_val = read32(mddr_reg_addr);
        reg_val &= reg_mask;

        mddr_mc_wait_us(mddr_base_addr, 1);
        i++;
    } while((i < max_loops) && (reg_val == 0x0));
}



/*!****************************************************************************
*
* @par Description:
*    This function checks the current configuration to determine if the channel
*     is populated with DIMMs.
*
*                                  @param
*    ddr_chan       The channel to check.
*
*
* @return
*    Boolean indication of if the channel has any DIMMs.
*
* @author
*    gkowis
*
******************************************************************************/
bool mddr_check_chan_populated(uint8_t ddr_chan)
{
    uint8_t dimm_slot;
    bool chan_populated;

    chan_populated = false;

    for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        if(mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            chan_populated = true;
        }
    }

    return chan_populated;
}



/*!****************************************************************************
*
* @par Description:
*    This function determines the number of DIMMs in a populated channel.
*    The count is expected to be the same for all populated channels.
*
* @return
*    Count of the number of DIMMs populated in first populated channel.
*
* @author
*    gkowis
*
******************************************************************************/
uint8_t mddr_get_dimm_per_chan_cnt(void)
{
    uint8_t ddr_chan;
    uint8_t dimm_slot;
    uint8_t num_dimm_slots_pop = 0;

    ddr_chan = 0;

    // Count the DIMMs in the first channel that is populated.
    while((num_dimm_slots_pop == 0) && (ddr_chan < DDR_MAX_NUM_CHANS))
    {
        // Check the channel's slots for DIMMs
        for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            // Slot populated, count it.
            if(mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                ++num_dimm_slots_pop;
            }
        }

        ++ddr_chan;
    }

    return num_dimm_slots_pop;
}



/*!****************************************************************************
*
* @par Description:
*    This function determines the maximum clock rate supported by all DIMMs
*     populated.
*
* @return
*    Highest common clock rate in MHz.
*
* @author
*    gkowis
*
******************************************************************************/
uint16_t mddr_get_dimms_max_clk(void)
{
    uint16_t max_clk = 1600;
    uint16_t dimm_clk;
    uint8_t ddr_chan;
    uint8_t dimm_slot;


    // Go through all channels and slots searching for the greatest common DIMM clock rate supported
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            // Check to see if there is a DIMM in the slot
            if(mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
            {
                // Get the max clock rate of the DIMM
                dimm_clk = MDDR_PS_TO_MHZ(mddr_dimm_configs[ddr_chan][dimm_slot].tck_min_ps);

                // Get the common clock rate.
                max_clk = COM_MIN(dimm_clk, max_clk);
            }
        }
    }


    // Align the rate to expected clock bins.
    if (max_clk >= 1333)
    {
        max_clk = 1333;
    }
    else if (max_clk >= 1200)
    {
        max_clk = 1200;
    }
    else if (max_clk >= 1066)
    {
        max_clk = 1066;
    }
    else if (max_clk >= 933)
    {
        max_clk = 933;
    }
    else if (max_clk >= 800)
    {
        max_clk = 800;
    }
    else
    {
        // The rate is less that the min bin expected so just take it as is.
    }

    return max_clk;
}



/*!****************************************************************************
*
* @par Description:
*    This function records the contents of the provided MDDR settings structure
*     into the internal MDDR settings.
*
*                                  @param
*    settings_ptr         Pointer to MDDR settings structure that is
*                          the destination of the copy.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_record_init_parms(mddr_settings_t *settings_ptr)
{
    uint16_t size_bytes;
    uint8_t *src_ptr;
    uint8_t *dst_ptr;

    size_bytes = sizeof(mddr_settings_t);
    src_ptr = (uint8_t *)settings_ptr;
    dst_ptr = (uint8_t *)&mddr_settings;

    com_blk_copy(src_ptr, dst_ptr, size_bytes);
}



#ifdef __BAREMETAL__

/*!****************************************************************************
*
* @par Description:
*    This function sets the DDR clock frequency using the bare-metal clock
*     driver.
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
*    gkowis
*
* @par Notes:
*    This is a place holder to allow eventual replacement of the script driver
*     with a C equivalent.
*
******************************************************************************/
unsigned mddr_set_clock_frequency(UNUSED_PARAM mddr_settings_t *mddr_settings_ptr)
{
    return COM_OK;
}
#endif


/*!****************************************************************************
*
* @par Description:
*    This locks down the hardware for unused channels.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_lockdown_unused_chan(uint8_t ddr_chan)
{
    if (platform_mode == SILICON)
    {
//        mddr_phy_lockout(ddr_chan);
    }

    mddr_update_chan_gcc_reset(ddr_chan, (uint8_t)ASSERT_GCC_RESET);
    mddr_disable_chan_gcc_2x_clock(ddr_chan);

}


/*!****************************************************************************
*
* @par Description:
*    This function performs the CLKGEN initialization.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    mddr_base_addr     The base address of the configuration registers for
*                        the memory controller.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    None
*
* @author
*    lchavani
*
******************************************************************************/
void mddr_clkgen_init(mddr_settings_t *mddr_settings_ptr, uint64_t mddr_base_addr, uint8_t ddr_chan)
{
    uint64_t reg_pll_ready_addr;
    uint32_t reg_pll_ready_val = 0x0;
    uint16_t max_loops_pll_ready = 63;    // Loop a total of 64 times
    uint16_t i=0;
    uint32_t clk_freq_idx;

    if (mem_freq_mhz <= 625)
        clk_freq_idx = 0;
    else if (mem_freq_mhz == 660)
        clk_freq_idx = 1;
    else if (mem_freq_mhz == 800)
        clk_freq_idx = 2;
    else if (mem_freq_mhz == 933)
        clk_freq_idx = 3;
    else if (mem_freq_mhz == 1066)
        clk_freq_idx = 4;
    else if (mem_freq_mhz == 1200)
        clk_freq_idx = 5;
    else if (mem_freq_mhz == 1333)
        clk_freq_idx = 6;
    else if (mem_freq_mhz == 1467)
        clk_freq_idx = 7;
    else  // (mem_freq_mhz == 1600)
        clk_freq_idx = 8;



    // Assert sw_reset from SWI
    mddr_set_reg(mddr_base_addr + DDRPLL_SW_RESET_OFFSET, "DDRPLL_SW_RESET", 0x1);

    // Start state machine
    mddr_set_reg(mddr_base_addr + DDRPLL_RESETSM_CNTRL_OFFSET, "DDRPLL_RESETSM_CNTRL", 0x4);

    // QMP mode
    mddr_set_reg(mddr_base_addr + DDRPLL_CMN_CONFIG_OFFSET, "DDRPLL_CMN_CONFIG", 0x2);

    // Select cmos pad as refclk input, swing = 2'b01
    mddr_set_reg(mddr_base_addr + DDRPLL_CLK_SELECT_OFFSET, "DDRPLL_CLK_SELECT", 0x22);

    // Select EP clk to CML output, override sysclk_en to 0
    mddr_set_reg(mddr_base_addr + DDRPLL_SYSCLK_EN_SEL_OFFSET, "DDRPLL_SYSCLK_EN_SEL", 0xA);

    // Enable EP clk
    mddr_set_reg(mddr_base_addr + DDRPLL_CLK_ENABLE1_OFFSET, "DDRPLL_CLK_ENABLE1", 0xE);

    mddr_set_reg(mddr_base_addr + DDRPLL_BIAS_EN_CLKBUFLR_EN_OFFSET, "DDRPLL_BIAS_EN_CLKBUFLR_EN", 0x1);

    // Bandgap trim setting
    mddr_set_reg(mddr_base_addr + DDRPLL_BGV_TRIM_OFFSET, "DDRPLL_BGV_TRIM", 0x20);

    // Bandgap trim setting
    mddr_set_reg(mddr_base_addr + DDRPLL_BGT_TRIM_OFFSET, "DDRPLL_BGT_TRIM", 0xF);

    // Current trim setting
    mddr_set_reg(mddr_base_addr + DDRPLL_CLK_IPTRIM_OFFSET, "DDRPLL_CLK_IPTRIM", 0x20);

    // Current trim setting
    mddr_set_reg(mddr_base_addr + DDRPLL_CLK_IETRIM_OFFSET, "DDRPLL_CLK_IETRIM", 0x20);

    // PLL VCO current setting
    mddr_set_reg(mddr_base_addr + DDRPLL_PLL_IVCO_OFFSET, "DDRPLL_PLL_IVCO", 0xF);

    mddr_set_reg(mddr_base_addr + DDRPLL_CMN_MODE_OFFSET, "DDRPLL_CMN_MODE", 0x5);

    // No ac_couple, no cm, terminate to cap
    mddr_set_reg(mddr_base_addr + DDRPLL_SYS_CLK_CTRL_OFFSET, "DDRPLL_SYS_CLK_CTRL", 0x1);

    mddr_set_reg(mddr_base_addr + DDRPLL_SYSCLK_BUF_ENABLE_OFFSET, "DDRPLL_SYSCLK_BUF_ENABLE", 0x6);

    // Bypass restrim, code override to 7'h5A
    mddr_set_reg(mddr_base_addr + DDRPLL_RESTRIM_CTRL_OFFSET, "DDRPLL_RESTRIM_CTRL", 0xB5);

    mddr_set_reg(mddr_base_addr + DDRPLL_CMN_RATE_OVERRIDE_OFFSET, "DDRPLL_CMN_RATE_OVERRIDE", 0x4);

    // Running on SVS setting for all frequency
    mddr_set_reg(mddr_base_addr + DDRPLL_SVS_MODE_CLK_SEL_OFFSET, "DDRPLL_SVS_MODE_CLK_SEL", 0x15);

    // Vco tune mapping setting, Single Frequency
    mddr_set_reg(mddr_base_addr + DDRPLL_VCO_TUNE_MAP_OFFSET, "DDRPLL_VCO_TUNE_MAP", 0x0);

    // Fbclk_div2 setting
    mddr_set_reg(mddr_base_addr + DDRPLL_CMN_CONFIG_2_OFFSET, "DDRPLL_CMN_CONFIG_2", 0x0);

    // Turn off auxclk from SWI
    mddr_set_reg(mddr_base_addr + DDRPLL_CORE_CLK_EN_OFFSET, "DDRPLL_CORE_CLK_EN", 0x2);

    // Bypass vco cal
    mddr_set_reg(mddr_base_addr + DDRPLL_VCO_TUNE_CTRL_OFFSET, "DDRPLL_VCO_TUNE_CTRL", 0x0);

    // Second cap of the loop filter setting
    mddr_set_reg(mddr_base_addr + DDRPLL_PLL_CCTRL_MODE0_OFFSET, "DDRPLL_PLL_CCTRL_MODE0", 0x34);

    // PLL RC loop filter setting
    mddr_set_reg(mddr_base_addr + DDRPLL_PLL_RCTRL_MODE0_OFFSET, "DDRPLL_PLL_RCTRL_MODE0", 0x16);

    // Charge pump setting
    mddr_set_reg(mddr_base_addr + DDRPLL_CP_CTRL_MODE0_OFFSET, "DDRPLL_CP_CTRL_MODE0", 0x8);


    if (mddr_settings_ptr->clkgen_ssc_en)
        {
    // PLL decimal divider setting
    mddr_set_reg(mddr_base_addr + DDRPLL_DEC_START_MODE0_OFFSET, "DDRPLL_DEC_START_MODE0", ssc_dec_start_mode0[clk_freq_idx]);

    // PLL decimal divider setting
    mddr_set_reg(mddr_base_addr + DDRPLL_DEC_START_MSB_MODE0_OFFSET, "DDRPLL_DEC_START_MSB_MODE0", ssc_dec_start_msb_mode0[clk_freq_idx]);

    // Fractional pll feedback divider setting
    mddr_set_reg(mddr_base_addr + DDRPLL_DIV_FRAC_START1_MODE0_OFFSET, "DDRPLL_DIV_FRAC_START1_MODE0", ssc_div_frac_start1_mode0[clk_freq_idx]);

    // Fractional pll feedback divider setting
    mddr_set_reg(mddr_base_addr + DDRPLL_DIV_FRAC_START2_MODE0_OFFSET, "DDRPLL_DIV_FRAC_START2_MODE0", ssc_div_frac_start2_mode0[clk_freq_idx]);

    // Fractional pll feedback divider setting
    mddr_set_reg(mddr_base_addr + DDRPLL_DIV_FRAC_START3_MODE0_OFFSET, "DDRPLL_DIV_FRAC_START3_MODE0", ssc_div_frac_start3_mode0[clk_freq_idx]);

        }
    else
        {
        // PLL decimal divider setting
        mddr_set_reg(mddr_base_addr + DDRPLL_DEC_START_MODE0_OFFSET, "DDRPLL_DEC_START_MODE0", reg_dec_start_mode0[clk_freq_idx]);

        // PLL decimal divider setting
        mddr_set_reg(mddr_base_addr + DDRPLL_DEC_START_MSB_MODE0_OFFSET, "DDRPLL_DEC_START_MSB_MODE0", reg_dec_start_msb_mode0[clk_freq_idx]);

        // Fractional pll feedback divider setting
        mddr_set_reg(mddr_base_addr + DDRPLL_DIV_FRAC_START1_MODE0_OFFSET, "DDRPLL_DIV_FRAC_START1_MODE0", reg_div_frac_start1_mode0[clk_freq_idx]);

        // Fractional pll feedback divider setting
        mddr_set_reg(mddr_base_addr + DDRPLL_DIV_FRAC_START2_MODE0_OFFSET, "DDRPLL_DIV_FRAC_START2_MODE0", reg_div_frac_start2_mode0[clk_freq_idx]);

        // Fractional pll feedback divider setting
        mddr_set_reg(mddr_base_addr + DDRPLL_DIV_FRAC_START3_MODE0_OFFSET, "DDRPLL_DIV_FRAC_START3_MODE0", reg_div_frac_start3_mode0[clk_freq_idx]);
        }



    // Integral loop setting
    mddr_set_reg(mddr_base_addr + DDRPLL_INTEGLOOP_GAIN0_MODE0_OFFSET, "DDRPLL_INTEGLOOP_GAIN0_MODE0", 0x3F);

    // Integral loop setting
    mddr_set_reg(mddr_base_addr + DDRPLL_INTEGLOOP_GAIN1_MODE0_OFFSET, "DDRPLL_INTEGLOOP_GAIN1_MODE0", 0x0);

    // Divider value for the core_clk
    mddr_set_reg(mddr_base_addr + DDRPLL_CORECLK_DIV_OFFSET, "DDRPLL_CORECLK_DIV", 0x5);

    if (mddr_settings_ptr->clkgen_ssc_en)
        {
    // High speed clk divider setting
    mddr_set_reg(mddr_base_addr + DDRPLL_HSCLK_SEL1_OFFSET, "DDRPLL_HSCLK_SEL1", ssc_hsclk_sel1[clk_freq_idx]);
        }
    else

        {
    // High speed clk divider setting
    mddr_set_reg(mddr_base_addr + DDRPLL_HSCLK_SEL1_OFFSET, "DDRPLL_HSCLK_SEL1", reg_hsclk_sel1[clk_freq_idx]);
        }



    if (mddr_settings_ptr->clkgen_ssc_en)
    {
        mddr_set_reg(mddr_base_addr + DDRPLL_SSC_EN_CENTER_OFFSET, "DDRPLL_SSC_EN_CENTER", ssc_en_center[clk_freq_idx]);
        mddr_set_reg(mddr_base_addr + DDRPLL_SSC_STEP_SIZE1_OFFSET, "DDRPLL_SSC_STEP_SIZE1", ssc_step_size1[clk_freq_idx]);
        mddr_set_reg(mddr_base_addr + DDRPLL_SSC_STEP_SIZE2_OFFSET, "DDRPLL_SSC_STEP_SIZE2", ssc_step_size2[clk_freq_idx]);
        mddr_set_reg(mddr_base_addr + DDRPLL_SSC_STEP_SIZE3_OFFSET, "DDRPLL_SSC_STEP_SIZE3", ssc_step_size3[clk_freq_idx]);
        mddr_set_reg(mddr_base_addr + DDRPLL_SSC_PER1_OFFSET, "DDRPLL_SSC_PER1", ssc_per1[2]);
        mddr_set_reg(mddr_base_addr + DDRPLL_SSC_PER2_OFFSET, "DDRPLL_SSC_PER2", ssc_per2[2]);
        mddr_set_reg(mddr_base_addr + DDRPLL_LOCK_CMP1_MODE0_OFFSET, "DDRPLL_LOCK_CMP1_MODE0", ssc_lock_cmp1_mode0[clk_freq_idx]);
        mddr_set_reg(mddr_base_addr + DDRPLL_LOCK_CMP2_MODE0_OFFSET, "DDRPLL_LOCK_CMP2_MODE0", ssc_lock_cmp2_mode0[clk_freq_idx]);
    }
    else
        {
        mddr_set_reg(mddr_base_addr + DDRPLL_LOCK_CMP1_MODE0_OFFSET, "DDRPLL_LOCK_CMP1_MODE0", reg_lock_cmp1_mode0[clk_freq_idx]);
        mddr_set_reg(mddr_base_addr + DDRPLL_LOCK_CMP2_MODE0_OFFSET, "DDRPLL_LOCK_CMP2_MODE0", reg_lock_cmp2_mode0[clk_freq_idx]);
        }

    // PLL lock counter setting
    mddr_set_reg(mddr_base_addr + DDRPLL_LOCK_CMP3_MODE0_OFFSET, "DDRPLL_LOCK_CMP3_MODE0", 0x0);

    if (mddr_settings_ptr->clkgen_ssc_en)
    {
        // PLL lock compare enable
        mddr_set_reg(mddr_base_addr + DDRPLL_LOCK_CMP_EN_OFFSET, "DDRPLL_LOCK_CMP_EN", 0x4);
    }

    // Bypass RSM restrim
    mddr_set_reg(mddr_base_addr + DDRPLL_RESETSM_CNTRL2_OFFSET, "DDRPLL_RESETSM_CNTRL2", 0x28);

    // De-assert sw_reset from SWI
    mddr_set_reg(mddr_base_addr + DDRPLL_SW_RESET_OFFSET, "DDRPLL_SW_RESET", 0x0);

    // Start RSM from SWI
    mddr_set_reg(mddr_base_addr + DDRPLL_RESETSM_CNTRL_OFFSET, "DDRPLL_RESETSM_CNTRL", 0x6);


    reg_pll_ready_addr = mddr_base_addr + DDRPLL_C_READY_STATUS_OFFSET;

    do
    {
        reg_pll_ready_val = read32(reg_pll_ready_addr);
        reg_pll_ready_val &= MDDR_DDRPLL_C_READY_STATUS___M;
        i++;

        // The for loop delay is used here since HW Timer
        // is not available at this point in the execution
        ddr_wait_us(1000);  // 1000us

    } while((i < max_loops_pll_ready) && (reg_pll_ready_val == 0x0));


    reg_pll_ready_val = read32(reg_pll_ready_addr);

    if (reg_pll_ready_val != 0x0)
    {
        monaco_log(LOW, "CLKGEN PLL configured for %dMHz operation  for channel %d\n", mem_freq_mhz, hddrss[ddr_chan]);
    }
    else
    {
        monaco_log(CRITICAL, "ERROR: CLKGEN PLL not ready for channel %d\n", hddrss[ddr_chan]);
    }

}


/*!****************************************************************************
*
* @par Description:
*    This function determines the DDR type which is used to distinguish
*     between DDR3 and DDR4.
*     DDR4 => MDDR_TEST_STATUS[27:24]  = 0x4
*     DDR3 => MDDR_TEST_STATUS[27:24] != 0x4
*
*                                  @param
*    mode           The mode of the target being executed on.
*                     [SILICON|RUMI42|RUMI48|SIM|SIM_RUMI42|SIM_RUMI48]
*                                  @param
*    ddr_chan       DDR channel to perform function on.
*
* @return
*    The DDR type based on DDR3 or DDR4 dimm type is ascertained.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_determine_ddr_type(target_mode_e mode, uint8_t ddr_chan)
{
    uint64_t mddr_base_addr;
    uint32_t ddr_type = 0x0;

    mddr_base_addr = mddr_base_addrs[ddr_chan];

    if (mode != SILICON)
    {
        ddr_type = mddr_get_reg(mddr_base_addr + MDDR_TEST_STATUS_OFFSET, "DDR_TEST_STATUS");
        ddr_type = (ddr_type >> MDDR_TEST_STATUS_DDR_TYPE___S) & MDDR_TEST_STATUS_DDR_TYPE___M;
    }

    return ddr_type;
}


/*!****************************************************************************
*
* @par Description:
*    This function updates the compression settings based on the fuse and ECC settings.
*    MDDR_DATAFLOW_CDE_STATUS_0[2] reflects the value of the compression disable fuse
*    input to the memory controller. If the fuse setting is set to disable compression,
*    the software setting for compression is overridden if it is enabled.
*
* @return
*    None
*
* @author
*    lchavani/anthonyf
*
******************************************************************************/
void mddr_update_compression_settings
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint8_t ddr_chan;
    uint64_t mddr_base_addr;
    uint8_t status_cur = 0x0;
    uint8_t status_prev = 0x0;
    uint8_t first_iter = 0x1;
    uint8_t dataflow_cde_status_0_val = 0x0;

    if (mddr_settings_ptr->comp_settings.comp_mode)                             // Compression enabled
    {

        // Update compression setting based on fuse setting
        for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
        {
            mddr_base_addr = mddr_base_addrs[ddr_chan];

            if (mddr_check_chan_populated(ddr_chan))
            {
                status_cur = mddr_get_reg(mddr_base_addr + MDDR_DATAFLOW_CDE_STATUS_0_OFFSET, "MDDR_DATAFLOW_CDE_STATUS_0");
                status_cur = (status_cur & FUSE_COMPRESSION_DISABLE___M) >> FUSE_COMPRESSION_DISABLE___S;

                if((status_cur != status_prev) && (first_iter == 0x0))
                {
                    monaco_log(HIGH, "WARNING: Compression Fuse setting mismatch between controllers\n");
                }

                status_prev = status_cur;
                first_iter = 0x0;

                dataflow_cde_status_0_val |= status_cur;
            }
        }

        if(dataflow_cde_status_0_val)
        {
            mddr_settings_ptr->comp_settings.comp_mode = DDR_COMP_DISABLED;
            monaco_log(CRITICAL, "WARNING: DDR Bandwidth Compression is disabled since fuse set to disable compression\n");
        }


        // Update compression setting based on ECC setting
        if ((common_cfg_ptr->has_ecc) && (mddr_settings_ptr->disable_ecc == false)) // ECC is enabled
        {
            if ((mddr_settings_ptr->ecc_wrrd_mode & (ECC_WR | ECC_RD)) > 0x0)      // and is Standard ECC (SECDED)
            {
                mddr_settings_ptr->comp_settings.comp_mode = DDR_COMP_DISABLED;
                monaco_log(CRITICAL, "WARNING: DDR Bandwidth Compression is disabled since standard ECC is enabled\n");
            }
        }
        else                                                                        // ECC is disabled
        {
            mddr_settings_ptr->comp_settings.comp_mode = DDR_COMP_DISABLED;
            monaco_log(CRITICAL, "WARNING: DDR Bandwidth Compression is disabled since ECC is disabled\n");
        }

    }


    // Update other settings based on compression setting
    switch(mddr_settings_ptr->comp_settings.comp_mode)
    {
        case DDR_COMP_ADAPTIVE:
            mddr_settings_ptr->comp_settings.decomp_comp = COMP_DECOMP_ON;
            mddr_settings_ptr->comp_settings.cde_wdb_rd_mode = RD_GLBL_ADAPTIVE_TRK_QSB_WDB;
            mddr_settings_ptr->comp_settings.cde_qsb_rd_mode = RD_GLBL_ADAPTIVE_TRK_QSB_WDB;
            break;

        case DDR_COMP_STATIC:
            mddr_settings_ptr->comp_settings.decomp_comp = COMP_DECOMP_ON;
            mddr_settings_ptr->comp_settings.cde_wdb_rd_mode = RD_COMPRESSED;
            mddr_settings_ptr->comp_settings.cde_qsb_rd_mode = RD_COMPRESSED;
            break;

        case DDR_COMP_DISABLED:
        default:
            mddr_settings_ptr->comp_settings.decomp_comp = COMP_DECOMP_OFF;

            if(mddr_settings_ptr->comp_settings.cde_wdb_rd_mode)
            {
                mddr_settings_ptr->comp_settings.cde_wdb_rd_mode = RD_UNCOMPRESSED;
                monaco_log(CRITICAL, "WARNING: DDR WDB Read Mode set to uncompressed since Bandwidth Compression is disabled\n");
            }

            if(mddr_settings_ptr->comp_settings.cde_qsb_rd_mode)
            {
                mddr_settings_ptr->comp_settings.cde_qsb_rd_mode = RD_UNCOMPRESSED;
                monaco_log(CRITICAL, "WARNING: DDR QSB Read Mode set to uncompressed since Bandwidth Compression is disabled\n");
            }

            if (!mddr_settings_ptr->disable_patrol_scrub)
            {
                mddr_settings_ptr->disable_patrol_scrub = true;
                monaco_log(CRITICAL, "WARNING: DDR Patrol Scrub is disabled since DDR Bandwidth Compression is disabled\n");
            }
            break;
    }

}


//------------------------------------------------------------------------------
// CBC_enable
//------------------------------------------------------------------------------
void mddr_cbc_enable
(
    uint64_t reg_addr,
    char *reg_name_str
)
{
    uint32_t val = GCCMS_MDDRN_2X_CBCR_CLK_ENABLE___M;
    uint32_t mask = GCCMS_MDDRN_2X_CBCR_CLK_ENABLE___M;

    mddr_rmw_reg(reg_addr, reg_name_str, mask, val); // <CBC_name>.CLK_ENABLE = 0x1

    mddr_verify_clk_on(reg_addr, reg_name_str);
}



//------------------------------------------------------------------------------
// verify_clk_on
//------------------------------------------------------------------------------
void mddr_verify_clk_on
(
    uint64_t reg_addr,
    char *reg_name_str
)
{
    uint32_t s_clk_off;
    uint32_t tries = 2000;
    uint32_t try_num = 0;

    do
    {
        // Wait a bit for <reg>.CLK_OFF to clear
        // WAIT (((data.long(zaxi:&addr))>>31.)==0x0) 50.ms
        s_clk_off = mddr_get_reg(reg_addr, reg_name_str) >> 31;
        ++try_num;
    } while((s_clk_off == 0x1) && (try_num < tries));

    // Check if the clocks turned on or wait timed out
    if (s_clk_off == 0x1)
    {
        monaco_log(HIGH, "    *** WARNING : %s.CLK_OFF is still set!\n", reg_name_str);
    }
}
