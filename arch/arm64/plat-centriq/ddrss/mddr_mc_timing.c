/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file mddr_mc_timing.c
*
* @par Description:
*    This module provides the functionality to build the memory
*    controllers timing register values for the Monaco DDR subsystem.
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

#define TREFI_CONST_PS                    7800000 // 7.8us in ps
#define AUTO_REF_ADJ_CYCLES               0x4     // Additional cycles between auto refresh commands


/******************************************************************************
* Derived data types
******************************************************************************/


/******************************************************************************
* Global Variables
******************************************************************************/


/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/

void mddr_mc_set_timing_reg_vals(uint64_t mddr_base_addr, uint8_t ddr_chan);

uint32_t mddr_mc_build_timing_rcd_reg(void);
uint32_t mddr_mc_build_timing_rdwr0_reg(mddr_latencies_t *latencies_ptr);
uint32_t mddr_mc_build_timing_rdwr1_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_timing_rdwr2_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_latencies_t *latencies_ptr);
uint32_t mddr_mc_build_timing_rdwr3_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_timing_rdwr4_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_timing_adj_rdwr0_reg(uint8_t ddr_chan);
uint32_t mddr_mc_build_timing_adj_rdwr1_reg(uint8_t ddr_chan);
uint32_t mddr_mc_build_timing_dram_auto_ref0_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_dram_auto_ref1_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_dram_auto_ref2_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_adj_auto_ref_reg(uint8_t ddr_chan);
uint32_t mddr_mc_build_ddr_auto_ref_cntl_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_timing_pwr_down_0_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_pwr_down_1_reg(mddr_latencies_t *latencies_ptr);
uint32_t mddr_mc_build_timing_dram_self_ref_0_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr, mddr_latencies_t *latencies_ptr);
uint32_t mddr_mc_build_timing_dram_self_ref_1_reg(void);
uint32_t mddr_mc_build_timing_dram_self_ref_2_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_dram_mpsm_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_dram_zq_0_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_dram_zq_1_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_adj_zq_reg(uint8_t ddr_chan);
uint32_t mddr_mc_build_zqcal_cntl_reg(void);
uint32_t mddr_mc_build_timing_dram_mr_0_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_latencies_t *latencies_ptr);
uint32_t mddr_mc_build_timing_dram_mr_1_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_latencies_t *latencies_ptr);
uint32_t mddr_mc_build_timing_dq_bus_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_timing_dfi_0_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_dfi_1_reg(mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_timing_dfi_2_reg(mddr_common_cfg_t *common_cfg_ptr);
uint32_t mddr_mc_build_timing_odt_reg(mddr_common_cfg_t *common_cfg_ptr, mddr_settings_t *mddr_settings_ptr);
uint32_t mddr_mc_build_timing_gear_down_reg(void);


/******************************************************************************
* External Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function constructs the values for the timing registers found in a DDR
*    memory controller.
*
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
void mddr_mc_get_timing_reg_vals
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr,
    mddr_latencies_t *latencies_ptr
)
{
    uint8_t ddr_chan;

    mddr_reg_vals.timing_regs.rcd_val = mddr_mc_build_timing_rcd_reg();
    mddr_reg_vals.timing_regs.timing_rdwr0_val = mddr_mc_build_timing_rdwr0_reg(latencies_ptr);
    mddr_reg_vals.timing_regs.timing_rdwr1_val = mddr_mc_build_timing_rdwr1_reg(common_cfg_ptr, mddr_settings_ptr);
    mddr_reg_vals.timing_regs.timing_rdwr2_val = mddr_mc_build_timing_rdwr2_reg(common_cfg_ptr, latencies_ptr);
    mddr_reg_vals.timing_regs.timing_rdwr3_val = mddr_mc_build_timing_rdwr3_reg(common_cfg_ptr, mddr_settings_ptr);
    mddr_reg_vals.timing_regs.timing_rdwr4_val = mddr_mc_build_timing_rdwr4_reg(common_cfg_ptr, mddr_settings_ptr);

    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        mddr_reg_vals.timing_regs.adj_rdwr0_val[ddr_chan] = mddr_mc_build_timing_adj_rdwr0_reg(ddr_chan);
        mddr_reg_vals.timing_regs.adj_rdwr1_val[ddr_chan] = mddr_mc_build_timing_adj_rdwr1_reg(ddr_chan);
        mddr_reg_vals.timing_regs.adj_auto_ref_val[ddr_chan] = mddr_mc_build_timing_adj_auto_ref_reg(ddr_chan);
        mddr_reg_vals.timing_regs.zq_adj_val[ddr_chan] = mddr_mc_build_timing_adj_zq_reg(ddr_chan);
    }

    mddr_reg_vals.timing_regs.auto_ref0_val = mddr_mc_build_timing_dram_auto_ref0_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.auto_ref1_val = mddr_mc_build_timing_dram_auto_ref1_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.auto_ref2_val = mddr_mc_build_timing_dram_auto_ref2_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.auto_ref_cntl_val = mddr_mc_build_ddr_auto_ref_cntl_reg(mddr_settings_ptr);
    mddr_reg_vals.timing_regs.pwr_down0_val = mddr_mc_build_timing_pwr_down_0_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.pwr_down1_val = mddr_mc_build_timing_pwr_down_1_reg(latencies_ptr);
    mddr_reg_vals.timing_regs.self_ref0_val = mddr_mc_build_timing_dram_self_ref_0_reg(common_cfg_ptr, mddr_settings_ptr, latencies_ptr);
    mddr_reg_vals.timing_regs.self_ref1_val = mddr_mc_build_timing_dram_self_ref_1_reg();
    mddr_reg_vals.timing_regs.self_ref2_val = mddr_mc_build_timing_dram_self_ref_2_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.mpsm_val = mddr_mc_build_timing_dram_mpsm_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.zq0_val = mddr_mc_build_timing_dram_zq_0_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.zq1_val = mddr_mc_build_timing_dram_zq_1_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.zqcal_cntl_val = mddr_mc_build_zqcal_cntl_reg();
    mddr_reg_vals.timing_regs.mr0_val = mddr_mc_build_timing_dram_mr_0_reg(common_cfg_ptr, latencies_ptr);
    mddr_reg_vals.timing_regs.mr1_val = mddr_mc_build_timing_dram_mr_1_reg(common_cfg_ptr, latencies_ptr);
    mddr_reg_vals.timing_regs.dq_bus_val = mddr_mc_build_timing_dq_bus_reg(mddr_settings_ptr);
    mddr_reg_vals.timing_regs.dfi_0_val = mddr_mc_build_timing_dfi_0_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.dfi_1_val = mddr_mc_build_timing_dfi_1_reg(mddr_settings_ptr);
    mddr_reg_vals.timing_regs.dfi_2_val = mddr_mc_build_timing_dfi_2_reg(common_cfg_ptr);
    mddr_reg_vals.timing_regs.odt_val = mddr_mc_build_timing_odt_reg(common_cfg_ptr, mddr_settings_ptr);
    mddr_reg_vals.timing_regs.gear_down_val = mddr_mc_build_timing_gear_down_reg();
}


/******************************************************************************
* Local Functions
******************************************************************************/


/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing RCD register value.
*
* @return
*    The timing RCD register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_rcd_reg(void)
{
    uint32_t timing_rcd_val = 0x00000000;
    uint8_t nladd = 0x0; // HPG indicates to just set to 0 due to PHY and MC interactions


    //    timing_rcd_val |= (latencies_ptr->rcd_nladd & TIMING_RCD_TPDM___M) << TIMING_RCD_TPDM___S;
    timing_rcd_val  = (nladd & TIMING_RCD_NLADD___M) << TIMING_RCD_NLADD___S;
    timing_rcd_val |= (mddr_timing_vals.tstab_clk & TIMING_RCD_TSTAB___M) << TIMING_RCD_TSTAB___S;
    timing_rcd_val |= (mddr_timing_vals.tckev_min_clk & TIMING_RCD_TCKEV___M) << TIMING_RCD_TCKEV___S;

    return timing_rcd_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing dram read write 0 register value.
*
*                                  @param
*    latencies_ptr          The pointer to the structure containing the latency
*                             information.
*
* @return
*    The timing dram read write 0 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_rdwr0_reg
(
    mddr_latencies_t *latencies_ptr
)
{
    uint32_t timing_rdwr0_val = 0x00000000;


    timing_rdwr0_val |= latencies_ptr->rl << RDWR0_RL___S;
    timing_rdwr0_val |= latencies_ptr->cwl << RDWR0_WL___S;
    timing_rdwr0_val |= latencies_ptr->pl << RDWR0_PL___S;
    timing_rdwr0_val |= latencies_ptr->tcal << RDWR0_TCAL___S;
    timing_rdwr0_val |= latencies_ptr->tdbi << RDWR0_TDBI___S;

#ifdef CONFIG_PRE_Z1
	timing_rdwr0_val = 0x14140500;
#endif
    return timing_rdwr0_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing dram read write 1 register value.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
* @return
*    The timing dram read write 1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_rdwr1_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t timing_rdwr1_val;
    uint32_t tccds;   // CAS_n-to-CAS_n delay (short)
    uint32_t tccdl_check;
    uint32_t tccdl;   // CAS_n-to-CAS_n delay (long)
    uint32_t tfaw;
    uint32_t tfaw_dlr = 0;

    uint32_t tfaw_check_ps;
    uint32_t tfaw_check;
    bool check_tfaw = false;

    uint32_t rd_dqs_preamble = 1;    // default 1T for DDR4
    uint32_t wr_dqs_preamble = 1;


    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        tccds = 4;            // standard for DDR4 up to 3200.

        // Set tccdl per tCCD_L in table 102 of the DDR4 spec. Table 13
        // tCCD_L.min
        // JEDEC Standard No. 79-4: Table 13 P. 22

        // below from Jedec MR6 Table 14
        if (ddr_rate <= 1333)
        {
            tccdl_check = 4;
        }
        else if (ddr_rate <= 1866)
        {
            tccdl_check = 5;
        }
        else if (ddr_rate <= 2400)
        {
            tccdl_check = 6;
        }
        else if (ddr_rate <= 2666)
        {
            tccdl_check = 7;
        }
        else
        {
            // ddr_rate > 2666 (i.e. 3200)
            tccdl_check = 8;
        }

        if(((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
            (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ)) &&
           (tccdl_check == 5))
        {
            tccdl_check = 6;    // if preamble >= 2T, tccd of 5 is not allowed
        }

        if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_READ) ||
            (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
        {
            rd_dqs_preamble = 2;
        }

        if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
            (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
        {
            wr_dqs_preamble = 2;
        }

        // if DIMM SPD has worse specs then use it
        tccdl = COM_MAX(tccdl_check, mddr_timing_vals.tccdl_min_clk);


        // Set tfaw per tFAW_2K, tFAW_1K & tFAW_1/2K  in tables 103 & 104 of the DDR4 4A spec.
        //
        //    tFAW  Table
        //    -----------
        //    freq   Val at page size
        //    ----  ----------------
        //          1/2K    1K     2K
        //    ------------------------
        //    1600   20     25     35
        //    1866   17     23     30
        //    2133   15     21     30
        //    2400   13     21     30
        //    2666   TBD    TBD    TBD
        //    3200   TBD    TBD    TBD

        if (common_cfg.max_page_size_kb == 0)     // page size = 512B
        {
            if (ddr_rate >= 3200)
            {
                tfaw_check_ps = 10000;       // 10ns, DDR 3200 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2666)
            {
                tfaw_check_ps = 12000;       // 12ns, DDR 2666 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2400)
            {
                tfaw_check_ps = 13000;       // 13ns, DDR 2400
            }
            else if (ddr_rate >= 2133)
            {
                tfaw_check_ps = 15000;       // 15ns, DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                tfaw_check_ps = 17000;       // 17ns, DDR 1866
            }
            else
            {
                tfaw_check_ps = 20000;       // 20ns, DDR 1600
            }
        }
        else if (common_cfg.max_page_size_kb == 1)
        {
            if (ddr_rate >= 3200)
            {
                tfaw_check_ps = 21000;       // 21ns, DDR 3200 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2666)
            {
                tfaw_check_ps = 22000;       // 22ns, DDR 2666 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2400)
            {
                tfaw_check_ps = 21000;       // 21ns, DDR 2400
            }
            else if (ddr_rate >= 2133)
            {
                tfaw_check_ps = 21000;       // 21ns, DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                tfaw_check_ps = 23000;       // 23ns, DDR 1866
            }
            else
            {
                tfaw_check_ps = 25000;       // 25ns, DDR 1600
            }
        }
        else    // common_cfg.max_page_size_kb == 2
        {
            if (ddr_rate >= 3200)
            {
                tfaw_check_ps = 27500;       // 27.5ns, DDR 3200 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2666)
            {
                tfaw_check_ps = 30000;       // 30ns, DDR 2666 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2400)
            {
                tfaw_check_ps = 30000;       // 30ns, DDR 2400
            }
            else if (ddr_rate >= 2133)
            {
                tfaw_check_ps = 30000;       // 30ns, DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                tfaw_check_ps = 30000;       // 30ns, DDR 1866
            }
            else
            {
                tfaw_check_ps = 35000;       // 35ns, DDR 1600
            }
        }
    }
    else
    {
        tccdl = 4;            // standard for DDR3.
        tccds = tccdl;

        if(platform_mode != SILICON)
        {
            // set to 0 for emulation
            rd_dqs_preamble = 0;
            wr_dqs_preamble = 0;
        }

        // tFAW minimums by rate per Table 69, page 174 of JEDEC DDR3 Specification(JESD79-3F)

        if (common_cfg.max_page_size_kb == 1)
        {
            if (ddr_rate >= 2133)
            {
                tfaw_check_ps = 25000;    // 25ns,   DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                tfaw_check_ps = 27000;    // 27ns,   DDR 1866
            }
            else if (ddr_rate >= 1600)
            {
                tfaw_check_ps = 30000;    // 30ns,   DDR 1600
            }
            else if (ddr_rate >= 1333)
            {
                tfaw_check_ps = 30000;    // 30ns,   DDR 1333
            }
            else if (ddr_rate >= 1066)
            {
                tfaw_check_ps = 37500;    // 37.5ns, DDR 1066
            }
            else
            {
                tfaw_check_ps = 40000;    // 40ns,   DDR  800
            }
        }
        else    // common_cfg.max_page_size_kb == 2
        {
            if (ddr_rate >= 2133)
            {
                tfaw_check_ps = 35000;    // 35ns,   DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                tfaw_check_ps = 35000;    // 35ns,   DDR 1866
            }
            else if (ddr_rate >= 1600)
            {
                tfaw_check_ps = 40000;    // 40ns,   DDR 1600
            }
            else if (ddr_rate >= 1333)
            {
                tfaw_check_ps = 45000;    // 45ns,   DDR 1333
            }
            else if (ddr_rate >= 1066)
            {
                tfaw_check_ps = 50000;    // 50ns,   DDR 1066
            }
            else
            {
                tfaw_check_ps = 50000;    // 50ns,   DDR  800
            }
        }
    }


    tfaw = mddr_timing_vals.tfaw_min_clk;

    if(check_tfaw)
    {
        // ps to clk for tfaw_check
        tfaw_check = mddr_get_num_clocks(tfaw_check_ps, mem_freq_ps);

        // Use the DIMM minimum tFAW if it exceeds the minimum spec value.
        tfaw = COM_MAX(tfaw_check, tfaw);
    }

    // &spd_use_simulated_spd is the key in the scripts for emulation speeds
    if(platform_mode != SILICON)
    {
        tfaw = COM_MAX(tfaw, 16);
    }
    else
    {
        tfaw = COM_MAX(tfaw, 2);
    }

    if (common_cfg_ptr->is_3DS)
    {
        //! @todo -GPK- 3DS is not supported in Rev 1 silicon. Verify for Rev 2.
        tfaw_dlr = 1;      // Need to verify this.
    }

    // Update the saved values to reflect the actual value being used for config.
    mddr_timing_vals.tccdl_min_clk = tccdl;
    mddr_timing_vals.tfaw_min_clk = tfaw;


    timing_rdwr1_val  = (tccds & RDWR1_TCCDS___M) << RDWR1_TCCDS___S;
    timing_rdwr1_val |= (tccdl & RDWR1_TCCDL___M) << RDWR1_TCCDL___S;
    timing_rdwr1_val |= (tfaw  & RDWR1_TFAW___M) << RDWR1_TFAW___S;
    timing_rdwr1_val |= (tfaw_dlr & RDWR1_TFAW_DLR___M) << RDWR1_TFAW_DLR___S;
    timing_rdwr1_val |= (rd_dqs_preamble & RDWR_1_RD_DQS_PREAMBLE___M) << RDWR_1_RD_DQS_PREAMBLE___S;
    timing_rdwr1_val |= (wr_dqs_preamble & RDWR_1_WR_DQS_PREAMBLE___M) << RDWR_1_WR_DQS_PREAMBLE___S;


#ifdef CONFIG_PRE_Z1
	timing_rdwr1_val = 0x05471200;
#endif
    return timing_rdwr1_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing dram read write 2 register value.
*
*                                  @param
*    common_cfg_ptr          The pointer to the structure containing the
*                             configuration information.
*                                  @param
*    latencies_ptr          The pointer to the structure containing the latency
*                             information.
*
* @return
*    The timing dram read write 2 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_rdwr2_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_latencies_t *latencies_ptr
)
{
    uint32_t timing_rdwr2_val;
    uint32_t cl;
    uint32_t trasmin;
    uint32_t trcd;
    uint32_t trp;

    uint32_t trasmin_ps;
    uint32_t trcdmin_ps;
    bool check_tras_trcd = false;


    //---------------------------------------------------------------------
    // below is more a check with Jedec spec ranges, might not be needed.

    cl = latencies_ptr->cl;

    // tRAS & tRCD minimums by rate per Tables 62,63,64 & 65 with tCK per Tables 46 & 47 of JEDEC DDR3 Specification(JESD79-3F)
    //                                  Tables 82,83,84 & 85 with tCK per Table 86 of JEDEC DDR4 Specification(JESD79-4A)

    trcdmin_ps = mddr_timing_vals.tck_ps * cl;


    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        if (ddr_rate >= 3200)
        {
            trasmin_ps = 32000;                     // 32ns,   DDR 2400
            trcdmin_ps = trcdmin_ps + (cl / 3);
        }
        else if (ddr_rate >= 2666)
        {
            trasmin_ps = 32000;                     // 32ns,   DDR 2400
            trcdmin_ps = trcdmin_ps + (cl / 3);
        }
        else if (ddr_rate >= 2400)
        {
            trasmin_ps = 32000;                     // 32ns,   DDR 2400
            trcdmin_ps = trcdmin_ps + (cl / 3);
        }
        else if (ddr_rate >= 2132)
        {
            trasmin_ps = 33000;                     // 33ns,   DDR 2133
            trcdmin_ps = trcdmin_ps + (cl / 2);     // 14.062ns(CL=15), 15ns(CL=16)
        }
        else if (ddr_rate >= 1866)
        {
            trasmin_ps = 34000;                     // 34ns,   DDR 1866
        }
        else if (ddr_rate >= 1600)
        {
            trasmin_ps = 35000;                     // 35ns,   DDR 1600
        }
        else
        {
            trasmin_ps = 36000;                     // 36ns, May want to use 1600 number.
        }
    }
    else
    {
        if (ddr_rate >= 2132)
        {
            trasmin_ps = 33000;                     // 33ns,   DDR 2133
            trcdmin_ps = trcdmin_ps + (cl / 2);     // 14.062ns(CL=15), 15ns(CL=16)
        }
        else if (ddr_rate >= 1866)
        {
            trasmin_ps = 34000;                     // 34ns,   DDR 1866
        }
        else if (ddr_rate >= 1600)
        {
            trasmin_ps = 35000;                     // 35ns,   DDR 1600
        }
        else if (ddr_rate >= 1333)
        {
            trasmin_ps = 36000;                     // 36ns,   DDR 1333
        }
        else if (ddr_rate >= 1066)
        {
            trasmin_ps = 37500;                     // 37.5ns, DDR 1066
        }
        else
        {
            trasmin_ps = 37500;                     // 37.5ns, DDR  800
        }
    }


    if(check_tras_trcd)
    {
        // skip check
        trasmin = max_of_clk_ps(mddr_timing_vals.tras_min_clk, trasmin_ps, mem_freq_ps);
        trcd = max_of_clk_ps(mddr_timing_vals.trcd_min_clk, trcdmin_ps, mem_freq_ps);
        trp = max_of_clk_ps(mddr_timing_vals.trp_min_clk, trcdmin_ps, mem_freq_ps);
    }
    else
    {
        trasmin = mddr_timing_vals.tras_min_clk;
        trcd = mddr_timing_vals.trcd_min_clk;
        trp = mddr_timing_vals.trp_min_clk;
    }


    // &spd_use_simulated_spd is the key in the scripts for emulation speeds
    if(platform_mode != SILICON)
    {
        trasmin = COM_MAX(trasmin, 15);
        trcd = COM_MAX(trcd, 6);
        trp = COM_MAX(trp, 6);
    }
    else
    {
        trasmin = COM_MAX(trasmin, 2);
        trp = COM_MAX(trp, 2);
    }


    trasmin &= RDWR2_TRASMIN___M;
    trcd &= RDWR2_TRCD___M;
    trp &= RDWR2_TRP___M;

    // Update the saved values to reflect the actual value being used for config.
    mddr_timing_vals.tras_min_clk = trasmin;
    mddr_timing_vals.trcd_min_clk = trcd;
    mddr_timing_vals.trp_min_clk = trp;


    timing_rdwr2_val  = trasmin << RDWR2_TRASMIN___S;
    timing_rdwr2_val |= trcd << RDWR2_TRCD___S;
    timing_rdwr2_val |= trp << RDWR2_TRP___S;

#ifdef CONFIG_PRE_Z1
	timing_rdwr2_val = 0xf1414;
#endif
    return timing_rdwr2_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing dram read write 3 register value.
*
*                                  @param
*    common_cfg_ptr          The pointer to the structure containing the
*                             configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                             settings information.
*
* @return
*    The timing dram read write 3 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_rdwr3_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t timing_rdwr3_val;
    uint32_t trrdl_check_ps;    // tRRD_S for DDR4
    uint32_t trrds_check_ps;    // tRRD_L for DDR4
    uint32_t trrd_check_ps;     // tRRD for DDR3
    uint32_t trrds;             // tRRD for DDR3, tRRD_S for DDR4
    uint32_t trrdl;             // tRRD for DDR3, tRRD_L for DDR4
    uint32_t trrd_dlr;
    uint32_t trtp;


    // DDR3 has SPD tRTP value. Pick max of SPD, 4clocks and 7.5ns per Tables 68 and 69 of
    //  JEDEC DDR3 Specification(JESD79-3F)
    // DDR4 has no SPD tRTP value. Pick max of 4 clocks and 7.5ns per Tables 103 and 104
    //  of JEDEC DDR4 Specification(JESD79-4A)
    trtp = max_of_clk_ps(4, 7500, mem_freq_ps);

    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        //
        // tRRD_S tRRD_L  minimums by rate per Tables 103 and 104 of JEDEC DDR4 Specification(JESD79-4A)
        //
        if (common_cfg.max_page_size_kb == 0)     // page size = 512B
        {
            if (ddr_rate >= 3200)
            {
                trrds_check_ps = 3300;       // 3.3ns, DDR 3200 : NEED to check this since TBD in spec
                trrdl_check_ps = 4900;       // 4.9ns, DDR 3200 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2666)
            {
                trrds_check_ps = 3300;       // 3.3ns, DDR 2666 : NEED to check this since TBD in spec
                trrdl_check_ps = 4900;       // 4.9ns, DDR 2666 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2400)
            {
                trrds_check_ps = 3300;       // 3.3ns, DDR 2400
                trrdl_check_ps = 4900;       // 4.9ns, DDR 2400
            }
            else if (ddr_rate >= 2133)
            {
                trrds_check_ps = 3700;       // 3.7ns, DDR 2133
                trrdl_check_ps = 5300;       // 5.3ns, DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                trrds_check_ps = 4200;       // 4.2ns, DDR 1866
                trrdl_check_ps = 5300;       // 5.3ns, DDR 1866
            }
            else
            {
                trrds_check_ps = 5000;       // 5ns, DDR 1600
                trrdl_check_ps = 6000;       // 6ns, DDR 1600
            }
        }
        else if (common_cfg.max_page_size_kb == 1)
        {
            if (ddr_rate >= 3200)
            {
                trrds_check_ps = 3300;       // 3.3ns, DDR 3200 : NEED to check this since TBD in spec
                trrdl_check_ps = 4900;       // 4.9ns, DDR 3200 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2666)
            {
                trrds_check_ps = 3300;       // 3.3ns, DDR 2666 : NEED to check this since TBD in spec
                trrdl_check_ps = 4900;       // 4.9ns, DDR 2666 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2400)
            {
                trrds_check_ps = 3300;       // 3.3ns, DDR 2400
                trrdl_check_ps = 4900;       // 4.9ns, DDR 2400
            }
            else if (ddr_rate >= 2133)
            {
                trrds_check_ps = 3700;       // 3.7ns, DDR 2133
                trrdl_check_ps = 5300;       // 5.3ns, DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                trrds_check_ps = 4200;       // 4.2ns, DDR 1866
                trrdl_check_ps = 5300;       // 5.3ns, DDR 1866
            }
            else
            {
                trrds_check_ps = 5000;       // 5ns, DDR 1600
                trrdl_check_ps = 6000;       // 6ns, DDR 1600
            }
        }
        else    // common_cfg.max_page_size_kb == 2
        {
            if (ddr_rate >= 3200)
            {
                trrds_check_ps = 5300;       // 5.3ns, DDR 3200 : NEED to check this since TBD in spec
                trrdl_check_ps = 6400;       // 6.4ns, DDR 3200 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2666)
            {
                trrds_check_ps = 5300;       // 5.3ns, DDR 2666 : NEED to check this since TBD in spec
                trrdl_check_ps = 6400;       // 6.4ns, DDR 2666 : NEED to check this since TBD in spec
            }
            else if (ddr_rate >= 2400)
            {
                trrds_check_ps = 5300;       // 5.3ns, DDR 2400
                trrdl_check_ps = 6400;       // 6.4ns, DDR 2400
            }
            else if (ddr_rate >= 2133)
            {
                trrds_check_ps = 5300;       // 5.3ns, DDR 2133
                trrdl_check_ps = 6400;       // 6.4ns, DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                trrds_check_ps = 5300;       // 5.3ns, DDR 1866
                trrdl_check_ps = 6400;       // 6.4ns, DDR 1866
            }
            else
            {
                trrds_check_ps = 6000;       // 6ns, DDR 1600
                trrdl_check_ps = 7500;       // 7.5ns, DDR 1600
            }
        }



        // tRRD_S and tRRD_S minimums by rate per Tables 103 and 104 of JEDEC DDR4 Specification(JESD79-4A)
        trrds = max_of_clk_ps(4, trrds_check_ps, mem_freq_ps);
        trrds = COM_MAX(trrds, mddr_timing_vals.trrds_min_clk);

        trrdl = max_of_clk_ps(4, trrdl_check_ps, mem_freq_ps);
        trrdl = COM_MAX(trrdl, mddr_timing_vals.trrdl_min_clk);

        // NOTE: If geardown mode enabled tRTP must be even
        if (mddr_settings_ptr->ddr4_geardown_mode_en)
        {
            trtp += trtp % 2;
        }

        // Update the saved values to reflect the actual value being used for config.
        mddr_timing_vals.trrdl_min_clk = trrdl;
        mddr_timing_vals.trrds_min_clk = trrds;
        mddr_timing_vals.trtp_min_clk = trtp;

    }
    else
    {
        // tRRD minimums by rate per Table 68 & 69 of JEDEC DDR3 Specification(JESD79-3F)

        if (common_cfg.max_page_size_kb == 1)
        {
            if (ddr_rate >= 2133)
            {
                trrd_check_ps = 5000;     // 5ns,   DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                trrd_check_ps = 5000;     // 5ns,   DDR 1866
            }
            else if (ddr_rate >= 1600)
            {
                trrd_check_ps = 6000;     // 6ns,   DDR 1600
            }
            else if (ddr_rate >= 1333)
            {
                trrd_check_ps = 6000;     // 6ns,   DDR 1333
            }
            else if (ddr_rate >= 1066)
            {
                trrd_check_ps = 7500;     // 7.5ns, DDR 1066
            }
            else
            {
                trrd_check_ps = 10000;    // 10ns,   DDR  800
            }
        }
        else    // common_cfg.max_page_size_kb == 2
        {
            if (ddr_rate >= 2133)
            {
                trrd_check_ps = 6000;    // 6ns,   DDR 2133
            }
            else if (ddr_rate >= 1866)
            {
                trrd_check_ps = 6000;    // 6ns,   DDR 1866
            }
            else if (ddr_rate >= 1600)
            {
                trrd_check_ps = 7500;    // 7.5ns,   DDR 1600
            }
            else if (ddr_rate >= 1333)
            {
                trrd_check_ps = 7500;    // 7.5ns,   DDR 1333
            }
            else if (ddr_rate >= 1066)
            {
                trrd_check_ps = 10000;    // 10ns,   DDR 1066
            }
            else
            {
                trrd_check_ps = 10000;    // 10ns,   DDR  800
            }
        }

        // tRRD minimums by rate per Tables 68 and 69 of JEDEC DDR3 Specification(JESD79-3F)
        trrdl = max_of_clk_ps(4, trrd_check_ps, mem_freq_ps);
        trrdl = COM_MAX(trrdl, mddr_timing_vals.trrd_min_clk);
        trrds = trrdl;

        // DDR3 has SPD tRTP value. Pick max of SPD, 4clocks and 7.5ns per Tables 68 and 69 of
        //  JEDEC DDR3 Specification(JESD79-3F)
        trtp = COM_MAX(trtp, mddr_timing_vals.trtp_min_clk);

        // Update the saved values to reflect the actual value being used for config.
        mddr_timing_vals.trrd_min_clk = trrdl;
        mddr_timing_vals.trtp_min_clk = trtp;
    }




    if (common_cfg_ptr->is_3DS)
    {
        //! @todo -GPK- 3DS is not supported in Rev 1 silicon. Verify for Rev 2.
        trrd_dlr = 6;
    }
    else
    {
        trrd_dlr = 0;
    }


    //! @todo -NC- Overide for TRTP: the clock value to be decided based on PHY type
    if (platform_mode != SILICON)
    {
        if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
        {
            trtp = max_of_clk_ps(6, 7500, mem_freq_ps);
        }
    }

    timing_rdwr3_val  = (trtp & RDWR3_TRTP___M) << RDWR3_TRTP___S;
    timing_rdwr3_val |= (trrds & RDWR3_TRRDS___M) << RDWR3_TRRDS___S;
    timing_rdwr3_val |= (trrdl & RDWR3_TRRDL___M) << RDWR3_TRRDL___S;
    timing_rdwr3_val |= (trrd_dlr & RDWR3_TRRD_DLR___M) << RDWR3_TRRD_DLR___S;


    return timing_rdwr3_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing dram read write 4 register value.
*
*                                  @param
*    common_cfg_ptr          The pointer to the structure containing the
*                             configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                             settings information.
*
* @return
*    The timing dram read write 4 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_rdwr4_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t timing_rdwr4_val;
    uint32_t twr;
    uint32_t twtrs;
    uint32_t twtrl;
    uint32_t test_wr;

    // Get the pre-adjusted values
    twtrs = mddr_timing_vals.twtrs_min_clk;
    twtrl = mddr_timing_vals.twtr_min_clk;
    twr = mddr_timing_vals.twr_min_clk;


    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        if(twtrs < 2)
        {
            twtrs = 2;
        }

        if(twtrl < 4)
        {
            twtrl = 4;
        }

        // Note adjusting tWR to match mode register in JEDEC spec...
        if (twr < 10)
        {
            monaco_log(HIGH, "ERROR  Write recovery is less than 10 cycles for DDR4, using 10.\n");
            twr = 10;
        }
        else if (twr > 26)
        {
            monaco_log(HIGH, "ERROR  Write recovery is greater than 26 cycles for DDR4, using 26.\n");
            twr = 26;
        }

        // Set twr per MR0 WR table in 3.4.2 of JEDEC Standard No. 79-3F
        if ((twr % 2) == 1)   // odd twrmin_clk
        {
            ++twr;
        }

        if(twr < (mddr_timing_vals.trtp_min_clk * 2))
        {
            twr = mddr_timing_vals.trtp_min_clk * 2;
        }

        // Adjust for 2T write
        if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
           (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
        {
            ++twr;
            twtrl += 2;   // HPG says +2, was +1 before
            twtrs += 2;
        }

        // NOTE: If geardown mode enabled tWR & tRTP must be even
        if (mddr_settings_ptr->ddr4_geardown_mode_en)    // tRTP already even fixed to be even from previous FN
        {
            test_wr = mddr_timing_vals.trtp_min_clk * 2;

            if(twr > test_wr)
            {
                monaco_log(HIGH, "WARNING Need larger tWR value, trtp_min_clk=%d, twr_min_clk=%d, setting tWR=%d\n",
                                  mddr_timing_vals.trtp_min_clk,  twr, (test_wr + 2));
                twr = test_wr + 2;
            }
            else
            {
                twr = test_wr;
            }
        }
    }
    else
    {
        // Note adjusting tWR to match mode register in JEDEC spec...
        if (twr < 5)
        {
            twr = 5;

            if(platform_mode != SILICON)          // for emulation
            {
                monaco_log(HIGH, "\nERROR  Write recovery is less than 5 cycles for DDR3, using 5.\n\n");
            }
        }
        else if (twr > 16)
        {
            twr = 16;
            monaco_log(HIGH, "\nERROR  Write recovery is greater than 16 cycles for DDR3, using 16.\n\n");
        }

        // Set twr per MR0 WR table in 3.4.2 of JEDEC Standard No. 79-3F
        if (((twr % 2) == 1) && (twr != 5) && (twr != 7))   // odd twrmin_clk if not 5 or 7
        {
            ++twr;
        }

        if(twtrl < 4)
        {
            twtrl = 4;
        }

        twtrs = twtrl;
    }

    // Save the adjusted values
    mddr_timing_vals.twtrs_min_clk = twtrs;
    mddr_timing_vals.twtr_min_clk = twtrl;
    mddr_timing_vals.twr_min_clk = twr;
    mddr_timing_vals.mr_wr_clk = twr;

    timing_rdwr4_val  = (twr & RDWR4_TWR___M) << RDWR4_TWR___S;
    timing_rdwr4_val |= (twtrl & RDWR4_TWTRL___M) << RDWR4_TWTRL___S;
    timing_rdwr4_val |= (twtrs & RDWR4_TWTRS___M) << RDWR4_TWTRS___S;


    return timing_rdwr4_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing adjust read write 0 register value.
*
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                             settings information.
*
* @return
*    The timing adjust read write 0 register value.
*
* @author
*    gkowis, lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_timing_adj_rdwr0_reg
(
    uint8_t ddr_chan
)
{
    uint32_t adj_rdwr0_val = 0x0;      // tADJ_RDWRCS

    // Distinction between 1DPC and 2DPC is already done for cycle_adjusts when we obtain the SI
    adj_rdwr0_val  = (si_data[ddr_chan].cycle_adjusts.dimm_wtr & ADJ_RDWR0_DIMM_WTR___M) << ADJ_RDWR0_DIMM_WTR___S;
    adj_rdwr0_val |= (si_data[ddr_chan].cycle_adjusts.dimm_wtw & ADJ_RDWR0_DIMM_WTW___M) << ADJ_RDWR0_DIMM_WTW___S;
    adj_rdwr0_val |= (si_data[ddr_chan].cycle_adjusts.dimm_rtw & ADJ_RDWR0_DIMM_RTW___M) << ADJ_RDWR0_DIMM_RTW___S;
    adj_rdwr0_val |= (si_data[ddr_chan].cycle_adjusts.dimm_rtr & ADJ_RDWR0_DIMM_RTR___M) << ADJ_RDWR0_DIMM_RTR___S;
    adj_rdwr0_val |= (si_data[ddr_chan].cycle_adjusts.cs_wtr & ADJ_RDWR0_CS_WTR___M) << ADJ_RDWR0_CS_WTR___S;
    adj_rdwr0_val |= (si_data[ddr_chan].cycle_adjusts.cs_wtw & ADJ_RDWR0_CS_WTW___M) << ADJ_RDWR0_CS_WTW___S;
    adj_rdwr0_val |= (si_data[ddr_chan].cycle_adjusts.cs_rtw & ADJ_RDWR0_CS_RTW___M) << ADJ_RDWR0_CS_RTW___S;
    adj_rdwr0_val |= (si_data[ddr_chan].cycle_adjusts.cs_rtr & ADJ_RDWR0_CS_RTR___M) << ADJ_RDWR0_CS_RTR___S;

    return adj_rdwr0_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing adjust read write 1 register value.
*
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                             settings information.
*
* @return
*    The timing adjust read write 1 register value.
*
* @author
*    gkowis, lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_timing_adj_rdwr1_reg
(
    uint8_t ddr_chan
)
{
    uint32_t adj_rdwr1_val = 0x0;      // tADJ_RDWRINIT, tADJ_RDWROPER

    // Distinction between 1DPC and 2DPC is already done for cycle_adjusts when we obtain the SI
    adj_rdwr1_val  = (si_data[ddr_chan].cycle_adjusts.rank_wtr & ADJ_RDWR1_RANK_WTR___M) << ADJ_RDWR1_RANK_WTR___S;
    adj_rdwr1_val |= (si_data[ddr_chan].cycle_adjusts.rank_wtw & ADJ_RDWR1_RANK_WTW___M) << ADJ_RDWR1_RANK_WTW___S;
    adj_rdwr1_val |= (si_data[ddr_chan].cycle_adjusts.rank_rtw & ADJ_RDWR1_RANK_RTW___M) << ADJ_RDWR1_RANK_RTW___S;
    adj_rdwr1_val |= (si_data[ddr_chan].cycle_adjusts.rank_rtr & ADJ_RDWR1_RANK_RTR___M) << ADJ_RDWR1_RANK_RTR___S;
    adj_rdwr1_val |= (si_data[ddr_chan].cycle_adjusts.srank_wtr & ADJ_RDWR1_SRANK_WTR___M) << ADJ_RDWR1_SRANK_WTR___S;
    adj_rdwr1_val |= (si_data[ddr_chan].cycle_adjusts.srank_wtw & ADJ_RDWR1_SRANK_WTW___M) << ADJ_RDWR1_SRANK_WTW___S;
    adj_rdwr1_val |= (si_data[ddr_chan].cycle_adjusts.srank_rtw & ADJ_RDWR1_SRANK_RTW___M) << ADJ_RDWR1_SRANK_RTW___S;
    adj_rdwr1_val |= (si_data[ddr_chan].cycle_adjusts.srank_rtr & ADJ_RDWR1_SRANK_RTR___M) << ADJ_RDWR1_SRANK_RTR___S;

    return adj_rdwr1_val;
}




/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM auto refresh 0 register in a DDR
*    memory controller.
*
* @return
*    The timing DRAM auto refresh 0 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_auto_ref0_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t auto_ref0_val;
    uint32_t mem_xo_freq_ps;
    uint32_t trefi;
    uint32_t trfc;


    mem_xo_freq_ps = MDDR_KHZ_TO_PS(mddr_xo_freq_khz);


    if(platform_mode == SILICON)
    {
        trefi = mddr_get_num_clocks(TREFI_CONST_PS, mem_xo_freq_ps);
        trfc = mddr_get_num_clocks(mddr_timing_vals.trfc_min_ps, mem_freq_ps);
    }
    else
    {
        if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
        {
            trfc = 1;
        }
        else
        {
            trfc = 2;
        }

        trefi = 16; // -debug- Was 5
    }


#ifdef CONFIG_PRE_Z1
	trefi = 0x9a;
	trfc = 0x15a;
#endif
    auto_ref0_val  = (trefi & AUTO_REF0_TREFI___M) << AUTO_REF0_TREFI___S;
    auto_ref0_val |= (trfc & AUTO_REF0_TRFC___M) << AUTO_REF0_TRFC___S;

    return auto_ref0_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM auto refresh 1 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DRAM auto refresh 1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_auto_ref1_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t auto_ref1_val;
    uint32_t trfc;
    uint32_t trfc2;
    uint32_t trfc_dlr;


    if(platform_mode == SILICON)
    {
        if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
        {
            trfc = mddr_get_num_clocks(mddr_timing_vals.trfc1_min_ps, mem_freq_ps);
        }
        else
        {
            trfc = mddr_get_num_clocks(mddr_timing_vals.trfc_min_ps, mem_freq_ps);
        }
    }
    else
    {
        trfc = 2;    // +1
    }


    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        trfc2 = mddr_get_num_clocks(mddr_timing_vals.trfc2_min_ps, mem_freq_ps);
    }
    else
    {
        trfc2 = 0;
    }


    if (common_cfg_ptr->is_3DS)
    {
        //! @todo -GPK- 3DS is not supported in Rev 1 silicon. Verify for Rev 2.
        trfc_dlr = trfc + 2;
    }
    else
    {
        trfc_dlr = 0;                 // Is this a don't care?
    }

#ifdef CONFIG_PRE_Z1
	trfc2 = 0xd6;
#endif

    auto_ref1_val  = (trfc_dlr & AUTO_REF1_TRFCDLR___M) << AUTO_REF1_TRFCDLR___S;
    auto_ref1_val |= (trfc2 & AUTO_REF1_TRFC2___M) << AUTO_REF1_TRFC2___S;

    return auto_ref1_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM auto refresh 2 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DRAM auto refresh 2 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_auto_ref2_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t auto_ref2_val;
    uint32_t trfc4;

    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        // trfc4 = mddr_get_num_clocks(mddr_timing_vals.trfc4_min_ps, mem_freq_ps);
        trfc4 = mddr_get_num_clocks(mddr_timing_vals.trfc4_min_ps, mem_freq_ps);
    }
    else
    {
        trfc4 = 0;
    }

#ifdef CONFIG_PRE_Z1
	trfc4 = 0x93;
#endif

    auto_ref2_val = (trfc4 & AUTO_REF2_TRFC4___M) << AUTO_REF2_TRFC4___S;

    return auto_ref2_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing adjust auto refresh register in a DDR
*    memory controller.
*
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
* @return
*    The timing adjust auto refresh register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_adj_auto_ref_reg
(
    uint8_t ddr_chan
)
{
    uint32_t adj_auto_ref_val;


    // timing_adj_auto_ref optional additional ddr cycles from auto-ref to auto-ref
    adj_auto_ref_val = (si_data[ddr_chan].cycle_adjusts.ref_to_ref & ADJ_AUTO_REF_SPACE___M) << ADJ_AUTO_REF_SPACE___S;


    return adj_auto_ref_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the DDR auto refresh control register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
* @return
*    The DDR auto refresh control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_ddr_auto_ref_cntl_reg
(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t auto_ref_cntl_val = 0x0;
    uint32_t finegrain;
    uint32_t adj_dimm1 = 0;
    uint32_t adj_dimm0 = 0;

    uint32_t wm_high = 0x6;
    uint32_t wm_low = 0x2;

    finegrain = mddr_settings_ptr->rfc_mode;

    // TODO: -NC- Check the refresh watermarks and get vals for emulation and silicon.

    adj_dimm0 = mddr_settings_ptr->adj_ref_dimm0;
    adj_dimm1 = mddr_settings_ptr->adj_ref_dimm1;

    auto_ref_cntl_val  = (finegrain & AUTO_REF_CNTL_FINEGRAIN___M) << AUTO_REF_CNTL_FINEGRAIN___S;
    auto_ref_cntl_val |= (adj_dimm0 & AUTO_REF_CNTL_ADJ_DIMM0___M) << AUTO_REF_CNTL_ADJ_DIMM0___S;
    auto_ref_cntl_val |= (adj_dimm1 & AUTO_REF_CNTL_ADJ_DIMM1___M) << AUTO_REF_CNTL_ADJ_DIMM1___S;
    auto_ref_cntl_val |= (wm_high & AUTO_REF_CNTL_WM_HIGH___M) << AUTO_REF_CNTL_WM_HIGH___S;
    auto_ref_cntl_val |= (wm_low & AUTO_REF_CNTL_WM_LOW___M) << AUTO_REF_CNTL_WM_LOW___S;

    return auto_ref_cntl_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM power down 0 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DRAM power down 0 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_pwr_down_0_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t pwr_down0_val;      // tCPDED, tXP

    uint32_t tcpded;
    uint32_t txp;



    // NOTE: DDR4 settings up to 2400, above is TBD (Jedec79-4)

    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        tcpded = 4;

        txp = max_of_clk_ps(4, 6000, mem_freq_ps); // max of 4nCK, 6ns
    }
    else
    {
        if (ddr_rate < 1600)        // ddr3
        {
            tcpded = 1;
        }
        else
        {
            tcpded = 2;
        }

        if (ddr_rate < 1333)
        {
            txp = max_of_clk_ps(3, 7500, mem_freq_ps); // max of 3nCK, 7.5ns
        }
        else
        {
            txp = max_of_clk_ps(3, 6000, mem_freq_ps); // max of 3nCK, 6ns
        }
    }

    mddr_timing_vals.txp_clk = txp;
    tcpded += 8;         // Adder from HPG

    pwr_down0_val  = (tcpded & PWR_DOWN0_TCPDED___M) << PWR_DOWN0_TCPDED___S;
    pwr_down0_val |= (txp & PWR_DOWN0_TXP___M) << PWR_DOWN0_TXP___S;


    return pwr_down0_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM power down 1 register in a DDR
*    memory controller.
*
*                                  @param
*    latencies_ptr          The pointer to the structure containing the latency
*                             information.
*
* @return
*    The timing DRAM power down 1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_pwr_down_1_reg
(
    mddr_latencies_t *latencies_ptr
)
{
    uint32_t pwr_down1_val;      // tREFPDEN, tPRPDEN, tRDPDEN, tWRPDEN, tWRAPDEN

    uint32_t trefpden;
    uint32_t tprpden;
    uint32_t trdpden;
    uint32_t twrpden;
    uint32_t twrapden;


    if (ddr_rate <= 1866)
    {
        trefpden = 1;
        tprpden = 1;
    }
    else
    {
        trefpden = 2;
        tprpden = 2;
    }

    trdpden = latencies_ptr->cl + 5;

    twrpden = latencies_ptr->cwl + 4 + mddr_timing_vals.twr_min_clk;



    if(platform_mode != SILICON)          // for emulation speeds
    {
        if (twrpden < 15)
        {
            twrpden = 15;
        }
    }


    twrapden = latencies_ptr->cwl + 4 + mddr_timing_vals.mr_wr_clk + 1; // from JESD79-4A pg231


    pwr_down1_val  = (trefpden & PWR_DOWN1_TREFPDEN___M) << PWR_DOWN1_TREFPDEN___S;
    pwr_down1_val |= (tprpden & PWR_DOWN1_TPRPDEN___M) << PWR_DOWN1_TPRPDEN___S;
    pwr_down1_val |= (trdpden & PWR_DOWN1_TRDPDEN___M) << PWR_DOWN1_TRDPDEN___S;
    pwr_down1_val |= (twrpden & PWR_DOWN1_TWRPDEN___M) << PWR_DOWN1_TWRPDEN___S;
    pwr_down1_val |= (twrapden & PWR_DOWN1_TWRAPDEN___M) << PWR_DOWN1_TWRAPDEN___S;


    return pwr_down1_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM self refresh 0 register in a DDR
*    memory controller.
*
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
*    The timing DRAM self refresh 0 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_self_ref_0_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr,
    mddr_latencies_t *latencies_ptr
)
{
    uint32_t self_ref0_val;      // tCKE, tCKESR, tCKSRE, tCKSRX
    uint32_t tcke;
    uint32_t tckesr;
    uint32_t tcksre;
    uint32_t tcksrx;
    uint32_t cke_cmp_ps;



    // NOTE: DDR4 settings up to 2400, above is TBD (Jedec79-4)

    if (ddr_rate < 1066)
    {
        cke_cmp_ps = 7500;
    }
    else if (ddr_rate < 1600)
    {
        cke_cmp_ps = 5625;
    }
    else
    {
        cke_cmp_ps = 5000;
    }

    tcke = max_of_clk_ps(3, cke_cmp_ps, mem_freq_ps); // max of 3nCK, cke compare ps
    tckesr = tcke + 1;
    tcksre = max_of_clk_ps(5, 10000, mem_freq_ps); // max of 5nCK, 10ns
    tcksrx = tcksre;


    if ((common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4) &&
        ((mddr_settings_ptr->ca_parity == CA_PARITY_DRAM) ||
         (mddr_settings_ptr->ca_parity == CA_PARITY_DRAM_DIMM)))
    {
        // DRAM parity
        tcksre = tcksre + latencies_ptr->pl;
    }

    mddr_timing_vals.tcke_clk = tcke;

    // Adder from HPG
    tcksre += 8;

    self_ref0_val  = (tcke & SELF_REF0_TCKE___M) << SELF_REF0_TCKE___S;
    self_ref0_val |= (tckesr & SELF_REF0_TCKESR___M) << SELF_REF0_TCKESR___S;
    self_ref0_val |= (tcksre & SELF_REF0_TCKSRE___M) << SELF_REF0_TCKSRE___S;
    self_ref0_val |= (tcksrx & SELF_REF0_TCKSRX___M) << SELF_REF0_TCKSRX___S;


    return self_ref0_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM self refresh 1 register in a DDR
*    memory controller.
*
* @return
*    The timing DRAM self refresh 1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_self_ref_1_reg(void)
{
    uint32_t self_ref1_val;      // tXS, tXSDLL = tdllk_min

    self_ref1_val  = (mddr_timing_vals.txs_clk & SELF_REF1_TXS___M) << SELF_REF1_TXS___S;
    self_ref1_val |= (mddr_timing_vals.tdllk_min_clk & SELF_REF1_TXSDLL___M) << SELF_REF1_TXSDLL___S;


    return self_ref1_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM self refresh 2 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DRAM self refresh 2 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_self_ref_2_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t self_ref2_val;      // tXS_ABORT, tXS_FAST
    uint32_t txs_abort;
    uint32_t txs_fast;


    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
         // tRFC4min + 10ns
        txs_abort = mddr_get_num_clocks((mddr_timing_vals.trfc4_min_ps + 10000), mem_freq_ps);
        txs_fast = mddr_timing_vals.txs_clk;
    }
    else
    {
        txs_abort = mddr_timing_vals.txs_clk;
        txs_fast = mddr_timing_vals.txs_clk;
    }


    self_ref2_val  = (txs_abort & SELF_REF2_TXS_ABORT___M) << SELF_REF2_TXS_ABORT___S;
    self_ref2_val |= (txs_fast & SELF_REF2_TXS_FAST___M) << SELF_REF2_TXS_FAST___S;


    return self_ref2_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM MPSM register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DRAM MPSM register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_mpsm_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t mpsm_val;           // tXMP_DLL, tMPX_LH
    uint32_t txmp;
    uint32_t txmp_dll;
    uint32_t tmpx_lh;



    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        // Jedec 4.29.5 pg134 - JESD79-4A   Nov 2013
        if (ddr_rate < 2666)
        {
            //! @todo Need to fix this with later Jedec Spec...
            txmp = mddr_timing_vals.txs_clk;
            txmp_dll = mddr_timing_vals.tdllk_min_clk + txmp;
            tmpx_lh = mddr_get_num_clocks(12000, mem_freq_ps); // convert 12ns to clocks
        }
        else
        {
            //! @todo Need to fix this with later Jedec Spec...
            txmp = mddr_timing_vals.txs_clk+0xA;                     //! @todo Need to fix this TBD in Jedec spec. Made up number
            txmp_dll = mddr_timing_vals.tdllk_min_clk + txmp + 0xA;  //! @todo Need to fix this TBD in Jedec spec. Made up number
            tmpx_lh = 0xC+0xA;                                       //! @todo Need to fix this TBD in Jedec spec. Made up number
        }
    }
    else
    {
        txmp_dll = 0;
        tmpx_lh = 0;
    }


    mpsm_val  = (txmp_dll & MPSM_TXMP_DLL___M) << MPSM_TXMP_DLL___S;
    mpsm_val |= (tmpx_lh & MPSM_TMPX_LH___M) << MPSM_TMPX_LH___S;


    return mpsm_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM ZQ 0 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DRAM ZQ 0 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_zq_0_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t zq0_val;      // tZQCS
    uint32_t tzqcs;


    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        tzqcs = 128;
    }
    else        // DDR3
    {
        tzqcs = max_of_clk_ps(64, 80000, mem_freq_ps); // max of 64nCK, 80ns
    }


    zq0_val = (tzqcs & ZQ0_TZQCS___M) << ZQ0_TZQCS___S;


    return zq0_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM ZQ 1 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DRAM ZQ 1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_zq_1_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t zq1_val;      // tZQINIT, tZQOPER
    uint32_t tzqinit;
    uint32_t tzqoper;


    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        tzqinit = 1024;
        tzqoper = 512;
    }
    else        // DDR3
    {
        tzqinit = max_of_clk_ps(512, 640000, mem_freq_ps); // max of 512nCK, 640ns
        tzqoper = max_of_clk_ps(256, 320000, mem_freq_ps); // max of 256nCK, 320ns
    }



    zq1_val  = (tzqinit & ZQ1_TZQINIT___M) << ZQ1_TZQINIT___S;
    zq1_val |= (tzqoper & ZQ1_TZQOPER___M) << ZQ1_TZQOPER___S;


    return zq1_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing adjust ZQ register in a DDR
*    memory controller.
*
*                                  @param
*    mddr_settings_ptr       The pointer to the structure containing the
*                            settings information.
*
* @return
*    The timing adjust ZQ register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_adj_zq_reg
(
    uint8_t ddr_chan
)
{
    uint32_t zq_adj_val;


    zq_adj_val = (si_data[ddr_chan].cycle_adjusts.zq_to_zq & ZQ_ADJ_SPACE___M) << ZQ_ADJ_SPACE___S;


    return zq_adj_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the ZQ Calibration control register in a DDR
*    memory controller.
*
* @return
*    The ZQ Calibration control register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_zqcal_cntl_reg(void)
{
    uint32_t zqcal_cntl_val;
    uint32_t zq_seq_mode;
    uint32_t zq_interval;
    uint32_t dis_zq_on_sr_exit;
    uint32_t zq_exit_sr;


    dis_zq_on_sr_exit = 0x0;
    zq_seq_mode = 0x0;
    zq_interval = 0x1E;
    zq_exit_sr = 0x0;


    zqcal_cntl_val  = (zq_interval & ZQCAL_CNTL_ZQ_INTERVAL___M) << ZQCAL_CNTL_ZQ_INTERVAL___S;
    zqcal_cntl_val |= (zq_seq_mode & ZQCAL_CNTL_ZQ_SEQ_MODE___M) << ZQCAL_CNTL_ZQ_SEQ_MODE___S;
    zqcal_cntl_val |= (dis_zq_on_sr_exit & ZQCAL_CNTL_DIS_ZQ_ON_SR_EXIT___M) << ZQCAL_CNTL_DIS_ZQ_ON_SR_EXIT___S;
    zqcal_cntl_val |= (zq_exit_sr & ZQCAL_CNTL_ZQ_EXIT_SR___M) << ZQCAL_CNTL_ZQ_EXIT_SR___S;


    return zqcal_cntl_val;
}




/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM MR0 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    latencies_ptr          The pointer to the structure containing the latency
*                             information.
*
* @return
*    The timing DRAM MR0 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_mr_0_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_latencies_t *latencies_ptr
)
{
    uint32_t mr0_val;      // tMOD, tMRD, tMOD_PDA, tMRD_PDA

    uint32_t tmod;
    uint32_t tmrd;
    uint32_t tmod_pda;
    uint32_t tmrd_pda;


    tmod = latencies_ptr->tmod;
    tmrd = latencies_ptr->tmrd;

    // NOTE: DDR4 settings up to 2400, above is TBD (Jedec79-4)
    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        tmod_pda = tmod + latencies_ptr->wl + latencies_ptr->pl;
        tmrd_pda = max_of_clk_ps(16, 10000, mem_freq_ps);       // max of 16nCK, 10ns
        tmrd_pda += latencies_ptr->wl + latencies_ptr->pl;
    }
    else        // DDR3
    {
        tmod_pda = 0;
        tmrd_pda = 0;
    }


    mr0_val  = (tmod & MR_0_TMOD___M) << MR_0_TMOD___S;
    mr0_val |= (tmrd & MR_0_TMRD___M) << MR_0_TMRD___S;
    mr0_val |= (tmod_pda & MR_0_TMOD_PDA___M) << MR_0_TMOD_PDA___S;
    mr0_val |= (tmrd_pda & MR_0_TMRD_PDA___M) << MR_0_TMRD_PDA___S;


    return mr0_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DRAM MR1 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    latencies_ptr          The pointer to the structure containing the latency
*                             information.
*
* @return
*    The timing DRAM MR1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dram_mr_1_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_latencies_t *latencies_ptr
)
{
    uint32_t mr1_val;      // tMPRR, tWR_MPR
    uint32_t tmprr;
    uint32_t twr_mpr;


    tmprr = 1;        // common to both DDR3 & DDR4

    // NOTE: DDR4 settings up to 2400, above is TBD (Jedec79-4)
    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        twr_mpr = latencies_ptr->tmod;
    }
    else        // DDR3
    {
        twr_mpr = 0;
    }


    mr1_val  = (tmprr & MR_1_TMPRR___M) << MR_1_TMPRR___S;
    mr1_val |= (twr_mpr & MR_1_TWR_MPR___M) << MR_1_TWR_MPR___S;


    return mr1_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DQ Bus register in a DDR
*    memory controller.
*
* @return
*    The timing DQ Bus register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dq_bus_reg(mddr_settings_t *mddr_settings_ptr)
{
    uint32_t timing_dq_bus_val;


    timing_dq_bus_val  = (mddr_settings_ptr->prop_delay & DQ_BUS_PROP_DELAY___M) << DQ_BUS_PROP_DELAY___S;
    timing_dq_bus_val  |= (mddr_settings_ptr->extra_dqs_toggle & EXTRA_DQS_TOGGLE___M) << EXTRA_DQS_TOGGLE___S;

#ifdef CONFIG_PRE_Z1
	timing_dq_bus_val = 0x12;
#endif
    return timing_dq_bus_val;
}



/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DFI 0 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DFI 0 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dfi_0_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t timing_dfi_0_val;
    uint32_t tphy_wrdata;
    uint32_t trddata_en;
    uint32_t tphy_wrlat;


    if(platform_mode != SILICON)
    {
        // Emulation platform
        if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
        {
            // cl=10, cwl=9
            trddata_en = latencies.cl + latencies.pl + latencies.rcd_nladd - 0x3;    // 10+0+1-3=8
            tphy_wrlat = latencies.cwl + latencies.pl + latencies.rcd_nladd - 0x0;    // 9+0+1-0=0xA
            tphy_wrdata = 0x1;
        }
        else
        {
            // DDR3 simple PHY
            trddata_en = latencies.cl - 0x3;
            tphy_wrlat = latencies.cwl - 0x1;
            tphy_wrdata = 0x1;
        }

    }
    else
    {
        tphy_wrdata = 0x2;
        trddata_en = latencies.cl + latencies.pl + latencies.rcd_nladd - 0x5;
        tphy_wrlat = latencies.cwl + latencies.pl + latencies.rcd_nladd - 0x5;
    }

    timing_dfi_0_val  = (tphy_wrlat & TIMING_DFI_0_TPHY_WRLAT___M) << TIMING_DFI_0_TPHY_WRLAT___S;
    timing_dfi_0_val |= (trddata_en & TIMING_DFI_0_TRDDATA_EN___M) << TIMING_DFI_0_TRDDATA_EN___S;
    timing_dfi_0_val |= (tphy_wrdata & TIMING_DFI_0_TPHY_WRDATA___M) << TIMING_DFI_0_TPHY_WRDATA___S;

#ifdef CONFIG_PRE_Z1
	timing_dfi_0_val = 0x11313;
#endif
    return timing_dfi_0_val;
}




/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DFI 1 register in a DDR
*    memory controller.
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*
* @return
*    The timing DFI 1 register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dfi_1_reg
(
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t timing_dfi_1_val;
    uint32_t tlp_resp;
    uint32_t tctrlupd_max;
    uint32_t tctrlupd_max_msb;
    uint32_t tgeardown_delay;
    uint32_t tinit_start;
    uint32_t tctrl_delay;

    tgeardown_delay = 0x10;
    tinit_start = 0x10;
    tctrlupd_max = 0xF;       // max DFI cycles after dfi_ctrlupd_req signal can assert
    tlp_resp = 0x4;           // max DFI cycles after dfi_lp_ctrl_req or dfi_lp_data_req to assert dfi_lp_ack

    if (mddr_settings_ptr->ddr4_geardown_mode_en)
    {
        tctrl_delay = 0x3;
    }
    else
    {
        tctrl_delay = 0x4;
    }

    if(platform_mode != SILICON)
    {
        tgeardown_delay = 0;
        tctrl_delay = 0;
        tinit_start = 0;
        tlp_resp = 0x2;
    }

    if (tctrlupd_max > 0xF)
    {
        tctrlupd_max_msb = 0x1;
    }
    else
    {
        tctrlupd_max_msb = 0;
    }

    timing_dfi_1_val  = (tctrlupd_max & TIMING_DFI_1_TCTRLUPD_MAX___M) << TIMING_DFI_1_TCTRLUPD_MAX___S;
    timing_dfi_1_val |= (tlp_resp & TIMING_DFI_1_TLP_RESP___M) << TIMING_DFI_1_TLP_RESP___S;
    timing_dfi_1_val |= (tctrlupd_max_msb & TIMING_DFI_1_TCTRLUPD_MAX_MSB___M) << TIMING_DFI_1_TCTRLUPD_MAX_MSB___S;
    timing_dfi_1_val |= (tgeardown_delay & TIMING_DFI_1_TGEARDOWN_DELAY___M) << TIMING_DFI_1_TGEARDOWN_DELAY___S;
    timing_dfi_1_val |= (tctrl_delay & TIMING_DFI_1_TCTRL_DELAY___M) << TIMING_DFI_1_TCTRL_DELAY___S;
    timing_dfi_1_val |= (tinit_start & TIMING_DFI_1_TINIT_START___M) << TIMING_DFI_1_TINIT_START___S;

#ifdef CONFIG_PRE_Z1
	timing_dfi_1_val = 0xa409ec;
#endif
    return timing_dfi_1_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing DFI 2 register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*
* @return
*    The timing DFI 2 register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_timing_dfi_2_reg
(
    mddr_common_cfg_t *common_cfg_ptr
)
{
    uint32_t timing_dfi_2_val;
    uint32_t tphy_wrcslat;
    uint32_t tphy_rdcslat;

    if(platform_mode != SILICON)
    {
        // Emulation platform
        if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
        {
            tphy_rdcslat = latencies.cl + latencies.pl + latencies.rcd_nladd - 0x5;
            tphy_wrcslat = latencies.cwl + latencies.pl + latencies.rcd_nladd - 0x5;
        }
        else
        {
            // DDR3 simple PHY
            tphy_rdcslat = 0x1;
            tphy_wrcslat = 0x1;
        }
    }
    else
    {
        tphy_rdcslat = latencies.cl + latencies.pl + latencies.rcd_nladd - 0x5;
        tphy_wrcslat = latencies.cwl + latencies.pl + latencies.rcd_nladd - 0x5;
    }

    timing_dfi_2_val  = (tphy_wrcslat & TIMING_DFI_2_TPHY_WRCSLAT___M) << TIMING_DFI_2_TPHY_WRCSLAT___S;
    timing_dfi_2_val |= (tphy_rdcslat & TIMING_DFI_2_TPHY_RDCSLAT___M) << TIMING_DFI_2_TPHY_RDCSLAT___S;

#ifdef CONFIG_PRE_Z1
	timing_dfi_2_val = 0x611;
#endif
    return timing_dfi_2_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing ODT register in a DDR
*    memory controller.
*
*                                  @param
*    common_cfg_ptr         The pointer to the structure containing the
*                            configuration information.
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*
* @return
*    The timing odt register value.
*
* @author
*    gkowis
*
******************************************************************************/
uint32_t mddr_mc_build_timing_odt_reg
(
    mddr_common_cfg_t *common_cfg_ptr,
    mddr_settings_t *mddr_settings_ptr
)
{
    uint32_t timing_odt_val;

    uint32_t odt_latency_rd = 0;    // latency from read command to associated odt assertion
    uint32_t odth4_rd = 4;          // min odt assertion time for bl4 read
    uint32_t odth8_rd = 6;          // min odt assertion time for bl8 read
    uint32_t odt_latency_wr = 0;    // latency from write command to associated odt assertion
    uint32_t odth4_wr = 4;          // min odt assertion time for bl4 write
    uint32_t odth8_wr = 6;          // min odt assertion time for bl8 write

    odt_latency_rd = (latencies.cl - latencies.cwl);

    if (common_cfg_ptr->dev_type == SPD_DEVICE_TYPE_DDR4)
    {
/*
        if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_READ) ||
           (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
        {
            // read 2T preamble
            ++odth4_rd;
            ++odth8_rd;
        }


        if((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
           (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
        {
            // read 2T preamble
            ++odth4_wr;
            ++odth8_wr;
        }
*/

        // NOTE: need to double check if this is correct
        if (mddr_settings_ptr->ddr4_wr_crc_en)
        {
            // write CRC enabled
            ++odth4_wr;               // +1 for 2 beats of CRC
            ++odth8_wr;
        }
    }


    timing_odt_val  = (odth8_wr & ODTH8_WR___M) << ODTH8_WR___S;
    timing_odt_val |= (odth4_wr & ODTH4_WR___M) << ODTH4_WR___S;
    timing_odt_val |= (odt_latency_wr & ODT_LATENCY_WR___M) << ODT_LATENCY_WR___S;
    timing_odt_val |= (odth8_rd & ODTH8_RD___M) << ODTH8_RD___S;
    timing_odt_val |= (odth4_rd & ODTH4_RD___M) << ODTH4_RD___S;
    timing_odt_val |= (odt_latency_rd & ODT_LATENCY_RD___M) << ODT_LATENCY_RD___S;


    return timing_odt_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function constructs the timing GEAR_DOWN register in a DDR
*    memory controller.
*
* @return
*    The timing GEAR_DOWN register value.
*
* @author
*    lchavani
*
******************************************************************************/
uint32_t mddr_mc_build_timing_gear_down_reg(void)
{
    uint32_t timing_gear_down_val;
    uint32_t tgear_hold;
    uint32_t tgear_setup;
    uint32_t tsync_gear;

    tgear_setup = 0x2;
    tgear_hold = 0x2;
    //TODO:  Fix this value
    tsync_gear = 0x18;    // JEDEC has this as TBD...

    timing_gear_down_val  = (tsync_gear & GEAR_DOWN_TSYNC_GEAR___M) << GEAR_DOWN_TSYNC_GEAR___S;
    timing_gear_down_val |= (tgear_setup & GEAR_DOWN_TGEAR_SETUP___M) << GEAR_DOWN_TGEAR_SETUP___S;
    timing_gear_down_val |= (tgear_hold & GEAR_DOWN_TGEAR_HOLD___M) << GEAR_DOWN_TGEAR_HOLD___S;

    return timing_gear_down_val;
}


