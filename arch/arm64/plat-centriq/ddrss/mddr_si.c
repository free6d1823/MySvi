/*!****************************************************************************
*
* @copyright Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file mddr_si.c
*
* @par Description:
*    This module provides the functionality to configure and load the SI data
*    corresponding to the given configuration.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <tgmath.h>
#include <target/ddr.h>

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
extern mddr_common_cfg_t common_cfg;
extern mddr_lr_db_si_chan_t lr_db_si_data[DDR_MAX_NUM_CHANS];

/* @} */



/******************************************************************************
* External Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function configures the SI for LRDIMM Databuffer. This configures the
*    Host, databuffer and DRAM interface SI values.
*
*                                  @param
*    si_data_ptr       The pointer to the structure used to collect platform specific
*                       SI adjustments for each DDR channel.
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
void mddr_si_configure_lrdimm_db(mddr_si_chan_t *si_data_ptr, uint8_t ddr_chan)
{
    uint8_t dimm_slot;
    uint8_t rank = 0;
    uint8_t dram = 0;

    // LRDIMM DRAM
    uint8_t rtt_nom;
    uint8_t rtt_wr;
    uint8_t rtt_park;
    uint8_t ron;
    uint16_t vrefdq;

    uint8_t freq_idx = 0x0;
    uint16_t spd_val;

    // Related to RTT_PARK algorithm
    float rtt_park01;
    float rtt_park23;
    float rtt_park_ex;
    float wr_term_ideal;
    float rd_term_ideal;
    float wr_term_ex;
    float rd_term_ex;
    uint8_t nchecked = 0;
    float total_diff;
    float min_total_diff;
    uint8_t rtt_park_ndx;
    uint8_t rtt_park_min_ndx = 0;

    uint8_t vrefdq_val;
    uint8_t vrefdq_range;


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


    for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        // Configure the LRDIMM DB Host side interface values
        lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_rtt_park = si_data_ptr->dimm_si[dimm_slot].rank_si[0].rtt_park;
        lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_rtt_wr = si_data_ptr->dimm_si[dimm_slot].rank_si[0].rtt_wr;
        lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_rtt_nom = si_data_ptr->dimm_si[dimm_slot].rank_si[0].rtt_nom;
        lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_ron = si_data_ptr->dimm_si[dimm_slot].rank_si[0].ron;
        lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_vrefdq = si_data_ptr->dimm_si[dimm_slot].rank_si[0].vref[0];

        for (rank = 0; rank < DDR_MAX_RANKS_PER_SLOT; ++rank)
        {
            // Configure the LRDIMM DRAM side interface values
            //
            // ------------------------ ron ------------------------
            //
            spd_val = lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_ron[freq_idx];
            if (spd_val == 0x0)
            {
                ron = 34;
            }
            else    // if (spd_val == 0x1)
            {
                ron = 48;
            }

            si_data_ptr->dimm_si[dimm_slot].rank_si[rank].ron = ron;

            //
            // ------------------------ rtt_nom ------------------------
            //
            spd_val = lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_rtt_nom[freq_idx];

            rtt_nom = mddr_si_rtt_to_ohms((uint8_t)spd_val);

            if (common_cfg.slot_config[0].num_ranks == DDR_RANKS_QUAD_CS_DIMM)
            {
                rtt_nom = 0;
            }

            si_data_ptr->dimm_si[dimm_slot].rank_si[rank].rtt_nom = rtt_nom;

            //
            // ------------------------ rtt_wr ------------------------
            //
            spd_val = lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_rtt_wr[freq_idx];

            if (spd_val == 0x0)
            {
                rtt_wr = 0;
            }
            else if (spd_val == 0x1)
            {
                rtt_wr = 120;
            }
            else if (spd_val == 0x2)
            {
                rtt_wr = 240;
            }
            else if (spd_val == 0x3)
            {
                rtt_wr = 1;    // HI-Z
            }
            else //if (spd_val == 0x4)
            {
                rtt_wr = 80;
            }

            si_data_ptr->dimm_si[dimm_slot].rank_si[rank].rtt_wr = rtt_wr;

            //
            // ------------------------ rtt_park ------------------------
            //
            /* The JEDEC DDR4 SPD specification provides LRDIMM specific values for
            for termination and drive strength for the DRAM/Data Buffer interface.
            Bytes 152-154 (three frequency bins) define two values for DRAM RTT_PARK:
            one for package ranks 0 & 1 and the other for package ranks 2 & 3.

            Although the DDR controller allows for independent rank MR writes, the
            Amberwing DDR PHY during training is limited to one value for each of the
            six MRs for all ranks present in the channel.

            This RTT_PARK algorithm works around the limitation by first calculating the
            effective ideal resistance during writes and reads to/from the more
            strongly terminated ranks using SPD bytes 152-154. Then for each
            available RTT_PARK value, it calculates effective resistance
            Eventually this will obtain the RTT_PARK value that produces the
            smallest absolute difference from the SPD recommened ("ideal") resistance. */

            spd_val = lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_rtt_park01[freq_idx];
            rtt_park01 = (float)mddr_si_rtt_to_ohms(spd_val);

            if (common_cfg.slot_config[0].num_ranks <= DDR_RANKS_DUAL_CS_DIMM)
            {
                rtt_park = (uint8_t)rtt_park01;
            }
            else
            {
                spd_val = lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_rtt_park23[freq_idx];
                rtt_park23 = (float)mddr_si_rtt_to_ohms(spd_val);

                if (rtt_park01 == 0 || rtt_park23 == 0)
                {
                    monaco_log(HIGH, "Warning : For ddr chan %u, LRDIMM DRAM recommended rtt_park 0\n", hddrss[ddr_chan]);
                }

                if (rtt_park01 <= rtt_park23)
                {
                    wr_term_ideal = 1 / ((1/rtt_park23) * 2 + (1/rtt_park01) + (1/rtt_wr));
                    rd_term_ideal = 1 / ((1/rtt_park23) * 2 + (1/rtt_park01));
                }
                else
                {
                    wr_term_ideal = 1 / ((1/rtt_park01) * 2 + (1/rtt_park23) + (1/rtt_wr));
                    rd_term_ideal = 1 / ((1/rtt_park01) * 2 + (1/rtt_park23));
                }

                nchecked = 0;

                for(rtt_park_ndx = 0; rtt_park_ndx < 8; rtt_park_ndx++)
                {
                    rtt_park_ex = (float)mddr_si_rtt_to_ohms(rtt_park_ndx);

                    if(rtt_park_ex != 0)
                    {
                        wr_term_ex = 1 / ( ((1/rtt_park_ex) * 3) + (1/rtt_wr));
                        rd_term_ex = rtt_park_ex / 3;

                        total_diff = (fabs(wr_term_ideal - wr_term_ex) +
                                      fabs(rd_term_ideal - rd_term_ex));

                        if((nchecked == 0) || (total_diff < min_total_diff))
                        {
                            min_total_diff = total_diff;
                            rtt_park_min_ndx = rtt_park_ndx;
                        }
                        nchecked++;
                    }
                }

                rtt_park = mddr_si_rtt_to_ohms(rtt_park_min_ndx);

            }

            si_data_ptr->dimm_si[dimm_slot].rank_si[rank].rtt_park = rtt_park;

            //
            // ------------------------ vrefdq ------------------------
            //
            vrefdq_val = lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_vrefdq[rank];
            vrefdq_range = lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_vrefdq_range[rank];
            vrefdq = mddr_si_get_vrefdq_percentage(vrefdq_val, vrefdq_range);

            for (dram = 0; dram < DDR_MAX_DRAMS_PER_RANK; ++dram)
            {
                si_data_ptr->dimm_si[dimm_slot].rank_si[rank].vref[dram] = vrefdq;     // 0:17
            }

            //
            // ------------------------ WR and RD ODT ------------------------
            //
            if (common_cfg.slot_config[0].num_ranks == DDR_RANKS_QUAD_CS_DIMM)
            {
                si_data_ptr->dimm_si[dimm_slot].rank_si[rank].odt_wr = si_data_ptr->dimm_si[0].rank_si[0].odt_wr;
                si_data_ptr->dimm_si[dimm_slot].rank_si[rank].odt_rd = si_data_ptr->dimm_si[0].rank_si[0].odt_rd;
            }
            else if (rank < DDR_RANKS_DUAL_CS_DIMM)
            {
                si_data_ptr->dimm_si[dimm_slot].rank_si[rank].odt_wr = si_data_ptr->dimm_si[dimm_slot].rank_si[0].odt_wr;
                si_data_ptr->dimm_si[dimm_slot].rank_si[rank].odt_rd = si_data_ptr->dimm_si[dimm_slot].rank_si[0].odt_rd;
            }

        }

        // Log all the configured SI for populated channels
        if (mddr_check_chan_populated(ddr_chan))
        {
            monaco_log(INFORMATIONAL,"============= For DDR chan = %d & dimm_slot = %d ============\n", hddrss[ddr_chan], dimm_slot);
            monaco_log(INFORMATIONAL,"------------- LRDIMM: Host to Databuffer SI -------------\n");
            monaco_log(INFORMATIONAL,"lr_host_db_rtt_park = %u\n", lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_rtt_park);
            monaco_log(INFORMATIONAL,"lr_host_db_rtt_wr = %u\n", lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_rtt_wr);
            monaco_log(INFORMATIONAL,"lr_host_db_rtt_nom = %u\n", lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_rtt_nom);
            monaco_log(INFORMATIONAL,"lr_host_db_ron = %u\n", lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_ron);
            monaco_log(INFORMATIONAL,"lr_host_db_vrefdq = %u\n", lr_db_si_data[ddr_chan].lr_host_db_si[dimm_slot].lr_host_db_vrefdq);

            monaco_log(INFORMATIONAL,"------------- LRDIMM: Databuffer to DRAM SI read from SPD-------------\n");
            monaco_log(INFORMATIONAL,"lr_spd_db_dq_dfe = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_dq_dfe);
            monaco_log(INFORMATIONAL,"lr_spd_db_dq_gain_adj = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_dq_gain_adj);
            monaco_log(INFORMATIONAL,"lr_spd_db_mdq_ron = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_mdq_ron[freq_idx]);
            monaco_log(INFORMATIONAL,"lr_spd_db_mdq_term = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_mdq_term[freq_idx]);
            monaco_log(INFORMATIONAL,"lr_spd_db_mdq_vrefdq = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_mdq_vrefdq);
            monaco_log(INFORMATIONAL,"lr_spd_db_mdq_vrefdq_range = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_mdq_vrefdq_range);

            monaco_log(INFORMATIONAL,"------------- LRDIMM: DRAM SI read from SPD-------------\n");
            monaco_log(INFORMATIONAL,"lr_spd_db_rtt_park01 = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_rtt_park01[freq_idx]);
            monaco_log(INFORMATIONAL,"lr_spd_db_rtt_park23 = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_rtt_park23[freq_idx]);
            monaco_log(INFORMATIONAL,"lr_spd_db_rtt_wr = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_rtt_wr[freq_idx]);
            monaco_log(INFORMATIONAL,"lr_spd_db_rtt_nom = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_rtt_nom[freq_idx]);
            monaco_log(INFORMATIONAL,"lr_spd_db_ron = %u\n", lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_ron[freq_idx]);
            for (rank = 0; rank < DDR_MAX_RANKS_PER_SLOT; ++rank)
            {
                monaco_log(INFORMATIONAL,"lr_spd_db_vrefdq[%d] = %u\n", rank, lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_vrefdq[rank]);
                monaco_log(INFORMATIONAL,"lr_spd_db_vrefdq_range[%d] = %u\n", rank, lr_db_si_data[ddr_chan].lr_spd_db_si[dimm_slot].lr_spd_db_vrefdq_range[rank]);
            }

            monaco_log(INFORMATIONAL,"------------- LRDIMM final configured SI -------------\n");
            monaco_log(INFORMATIONAL,"slew_ca=%u slew_dq=%u imp_ca=%u imp_dq=%u term=%u mc_vrefdq=%u\n",
                si_data_ptr->mc_slew[0], si_data_ptr->mc_slew[1], si_data_ptr->mc_imp[0], si_data_ptr->mc_imp[1], si_data_ptr->mc_term, si_data_ptr->mc_vref);
            monaco_log(INFORMATIONAL,"ibt=%u\n", si_data_ptr->dimm_si[dimm_slot].ibt[0]);
            for (rank = 0; rank < DDR_MAX_RANKS_PER_SLOT; ++rank)
            {
                monaco_log(INFORMATIONAL,"ron[%d]=%u\n", rank, si_data_ptr->dimm_si[dimm_slot].rank_si[rank].ron);
                monaco_log(INFORMATIONAL,"rtt_nom[%d]=%u\n", rank, si_data_ptr->dimm_si[dimm_slot].rank_si[rank].rtt_nom);
                monaco_log(INFORMATIONAL,"rtt_wr[%d]=%u\n", rank, si_data_ptr->dimm_si[dimm_slot].rank_si[rank].rtt_wr);
                monaco_log(INFORMATIONAL,"rtt_park[%d]=%u\n", rank, si_data_ptr->dimm_si[dimm_slot].rank_si[rank].rtt_park);
                monaco_log(INFORMATIONAL,"odt_wr[%d]=%u\n", rank, si_data_ptr->dimm_si[dimm_slot].rank_si[rank].odt_wr);
                monaco_log(INFORMATIONAL,"odt_rd[%d]=%u\n", rank, si_data_ptr->dimm_si[dimm_slot].rank_si[rank].odt_rd);
                monaco_log(INFORMATIONAL,"vrefdq[%d]=%u\n", rank, si_data_ptr->dimm_si[dimm_slot].rank_si[rank].vref[0]);
            }
            monaco_log(INFORMATIONAL,"============================================================\n\n");
        }

    }
}


/*!****************************************************************************
*
* @par Description:
*    This function converts the MR5 encoded register values for RTT_PARK to the
*    real termination values.
*
*                                  @param
*    rtt_val       MR5 encoded register values for RTT_PARK
*
* @return
*    RTT_PARK termination value in ohms.
*
* @author
*    lchavani
*
******************************************************************************/
uint8_t mddr_si_rtt_to_ohms(uint8_t rtt_val)
{
    uint8_t rtt_ohms;

    if (rtt_val == 0x0)
    {
        rtt_ohms = 0;
    }
    else if (rtt_val == 0x1)
    {
        rtt_ohms = 60;
    }
    else if (rtt_val == 0x2)
    {
        rtt_ohms = 120;
    }
    else if (rtt_val == 0x3)
    {
        rtt_ohms = 40;
    }
    else if (rtt_val == 0x4)
    {
        rtt_ohms = 240;
    }
    else if (rtt_val == 0x5)
    {
        rtt_ohms = 48;
    }
    else if (rtt_val == 0x6)
    {
        rtt_ohms = 80;
    }
    else //if (rtt_val == 0x7)
    {
        rtt_ohms = 34;
    }

    return rtt_ohms;
}


/*!****************************************************************************
*
* @par Description:
*    This function converts the input VrefDQ value into percentage based on the
*    input VrefDQ range.
*
*                                  @param
*    vrefdq_val       Current VrefDQ value.
*                                  @param
*    vrefdq_range     Current VrefDQ range.
*
* @return
*    VrefDQ in percentage times 100.
*
* @author
*    lchavani
*
******************************************************************************/
uint16_t mddr_si_get_vrefdq_percentage(uint8_t vrefdq_val, uint8_t vrefdq_range)
{
    uint16_t vrefdq_percent;

    if(vrefdq_range == 0)
    {
        // if range bit is 0, 60.0% + vstep *0.65%
        vrefdq_percent = (vrefdq_val * 65) + 6000;
    }
    else
    {
        // if range bit is 1, 45.0% + vstep *0.65%
        vrefdq_percent = (vrefdq_val * 65) + 4500;
    }

    return vrefdq_percent;
}


