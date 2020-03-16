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
* <I>This software may be subject to U.S. and international export, re-export,
* or transfer ("export") laws.  Diversion contrary to U.S. and international
* law is strictly prohibited.</I>
*
* @file mddr_phy_train.c
*
* @par Description:
*    This module provides the functionality to initialize the DDR PHYs
*    found in the Monaco DDR subsystem.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <target/ddr.h>

/******************************************************************************
* Defined Constants
******************************************************************************/
#define DDR_MAX_NUM_RANKS         4
#define MAX_CYCLE_ADJUST         15

#define P_STATE                   0
#define MAX_DFI_POLL_LOOPS     1000
#define PHY_MAX_READS       1000000

#define PHY_WORKAROUND_DBI  (1<<12)
#define PHY_WORKAROUND_WL   (1<<11)

#define PHY_MAX_MAJOR_STRINGS    16

#define DMEM_BYTE___S             8 // byte shift

#define DDR_CLKS_SEQ_DELAY      256

#define PHY_1D_TRAINING         0x1
#define PHY_2D_TRAINING         0x2
#define PHY_LP_STATE            0xF

#define PHY_CDD_TYPES   3
#define PHY_CDD_RW      0
#define PHY_CDD_WW      1
#define PHY_CDD_RR      2

#define APBONLY0_MICRORESET_RESETMC      0x9
#define APBONLY0_MICRORESET_HALT_PMU     0x1

#define PHY_FW_REV_MAJOR___S           3
#define PHY_FW_REV_MAJOR___M         0x3
#define PHY_FW_REV_MINOR___S           0
#define PHY_FW_REV_MINOR___M         0x7
#define PHY_FW_REV_MONTH___S          10
#define PHY_FW_REV_MONTH___M         0xF
#define PHY_FW_REV_DAY___S             5
#define PHY_FW_REV_DAY___M          0x1F
#define PHY_FW_REV_YEAR___S           14
#define PHY_FW_REV_YEAR___M          0x3
#define PHY_FW_REV_YEAR_OFFSET      2015

#define PHY_INPUT_VREF___M           0x1
#define PHY_INPUT_VREF___S            11

#define PHY_SKIPVREFUPD___M          0x1
#define PHY_SKIPVREFUPD___S           12

#define PHY_PSTATE___M               0x3
#define PHYDQVREF___M               0x7F
#define PHYDQVREF___S                  8

#define PHY_VREF_VAL             0x10000     // to enable PDA mode
#define PHY_VREF_CS0_DMEM             64     // starting dmem# for Vref CS0
#define PHY_VREF_MASK               0x3F

#define BITMASK                             0x1
#define SEQ_OR_SELECTDFIFREQTOGPRMUX___S    9
#define SEQ_OR_DISABLETERMINATEFLAG___S     8
#define SEQ_OR_BLOCKSEQ0BACK___S            7
#define SEQ_OR_BLOCKSEQ0BREQUESTS___S       6
#define SEQ_OR_FORCESEQ0BSTOP___S           5
#define SEQ_OR_FORCESEQ0BSTART___S          4
#define SEQ_OR_FORCESEQ0BSTARTVECTOR___S    0
#define SEQ_OR_FORCESEQ0BSTARTVECTOR___M    0xF

#define SELECTDFIFREQTOGPRMUX      0x1
#define DISABLETERMINATEFLAG       0x0
#define BLOCKSEQ0BACK              0x1
#define BLOCKSEQ0BREQUESTS         0x1
#define FORCESEQ0BSTOP             0x0
#define FORCESEQ0BSTART            0x1

#define MSG_ID_COMPLETE              7
#define MSG_ID_FAILED             0xFF
#define MAJORID_MSG___M           0xFF

#define STREAM_MAX_ARGS             40
#define STREAM_MSG                 0x8
#define STREAM_MSG_ARGS___M     0xFFFF
#define STREAM_MSG_STR___S          16
#define STREAM_MSG_STR___M      0xFFFF

#define PHY_MSB_MSG___M         0xFFFF
#define PHY_MSB_MSG___S             16
#define PHY_ACK_MSG                  0
#define PHY_ACK_RESET                1

// controller register fields
#define DFI_CMD0_DFI_FREQ___S               12
#define DFI_CMD0_DFI_FREQ___M             0x1F
#define DFI_CMD0_DFI_INIT_START___S          8

#define DDR_MANUAL_FENCE_DDR_PHY___S         2
#define DDR_MANUAL_FENCE_PHY_IN_RESET___S    4
#define DFI_STATUS2_DFI_INIT_COMPLETE___S   27

//Used in enhanced training
#define VREFDAC_BIT_STRIDE (DDRPHY_DBYTE0_VREFDAC0_R1_OFFSET - DDRPHY_DBYTE0_VREFDAC0_R0_OFFSET)
#define VREFDAC_BYTE_STRIDE (DDRPHY_DBYTE1_VREFDAC0_R0_OFFSET - DDRPHY_DBYTE0_VREFDAC0_R0_OFFSET)
#define RXPBDLY_RANK_STRIDE (DDRPHY_DBYTE0_RXPBDLYD1_R0_OFFSET - DDRPHY_DBYTE0_RXPBDLYD0_R0_OFFSET)
#define RXPBDLY_BIT_STRIDE (DDRPHY_DBYTE0_RXPBDLYD0_R1_OFFSET - DDRPHY_DBYTE0_RXPBDLYD0_R0_OFFSET)
#define RXPBDLY_BYTE_STRIDE (DDRPHY_DBYTE1_RXPBDLYD0_R0_OFFSET - DDRPHY_DBYTE0_RXPBDLYD0_R0_OFFSET)

/******************************************************************************
* Derived data types
******************************************************************************/

const char *major_str[PHY_MAX_MAJOR_STRINGS] = {
    "Device init completed",
    "WL (phase training) completed",
    "RD enable training completed",
    "Read 1D eye centering completed",
    "Write 1D eye centering completed",
    "End of 2D read delay / voltage center optimization",
    "End of 2D write delay / voltage center optimization",
    "All training completed",
    "Streaming message mode",
    "Max read latency training completed",
    "Read deskew training completed",
    "LCDL training completed",
    "LRDIMM training completed",
    "Read MPR based DQ/DQS training completed",
    "WL coarse training completed",
    "Error found"
};

/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the phy spacing found from
*    training.
*
* @par Members
*
*                                  <PRE>
*    dimm_wtr         Additional cycles from WR to RD different DIMMs
*    dimm_wtw         Additional cycles from WR to WR different DIMMs
*    dimm_rtw         Additional cycles from RD to WR different DIMMs
*    dimm_rtr         Additional cycles from RD to RD different DIMMs
*    cs_wtr           Additional cycles from WR to RD different chip selects
*    cs_wtw           Additional cycles from WR to WR different chip selects
*    cs_rtw           Additional cycles from RD to WR different chip selects
*    cs_rtr           Additional cycles from RD to RD different chip selects
*    rank_rtw         Additional cycles from RD to WR different ranks in a CS
*    srank_rtw        Additional cycles from RD to WR same rank
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t dimm_wtr;
    uint8_t dimm_wtw;
    uint8_t dimm_rtw;
    uint8_t dimm_rtr;
    uint8_t cs_wtr;
    uint8_t cs_wtw;
    uint8_t cs_rtw;
    uint8_t cs_rtr;
    uint8_t rank_rtw;
    uint8_t srank_rtw;
} mddr_phy_spacing_t;

/******************************************************************************
* Global Variables
******************************************************************************/
//Current physical channel undergoing training. This is used for
//printing phy training messages (set by mddr_phy_train)
uint8_t cphy_train_ddrss;
uint32_t ddrphy_mailbox_poll_delay = 2000000; //Default to 2ms delay
bool mddr_strings_available = false;
int32_t ddr_vref_max = 9000;
int32_t ddr_vref_min = 6500;
int32_t ddr_vref_inc = 500;
uint32_t mddr_dram_vref_trained[DDR_MAX_NUM_CHANS][4][5];   // [cs#][0:5]

/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/

uint32_t mddr_phy_get_fw_type (uint32_t fw_done);
void mddr_phy_config_fw(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan,
        uint32_t fw_type, uint8_t pstate, uint32_t mc_vref);
void mddr_phy_set_rcws_dbs(uint8_t ddr_chan);
unsigned mddr_phy_run_training_fw(uint64_t mddr_base_addr, uint32_t fw_done);
uint32_t mddr_phy_get_msg(uint64_t mddr_base_addr);
uint32_t mddr_phy_get_mail(uint64_t mddr_base_addr);
void mddr_phy_setup_sequencer(uint64_t mddr_base_addr, uint8_t pstate);
void mddr_phy_process_training(mddr_settings_t *mddr_settings_ptr,
        uint8_t ddr_chan, uint32_t fw_done);

void mddr_phy_print_fw_revision(uint64_t mddr_base_addr, uint32_t fw_type);
uint8_t mddr_phy_get_pos_2s_complement(uint8_t value);
void mddr_phy_update_cmd_spacing(mddr_settings_t *mddr_settings_ptr,
        uint8_t ddr_chan, uint8_t valid_cs_bm, uint8_t num_dimms_in_chan);

void mddr_phy_get_cmd_spacing(uint8_t ddr_chan,
        uint8_t cdd[PHY_CDD_TYPES][DDR_MAX_NUM_RANKS][DDR_MAX_NUM_RANKS]);

void mddr_phy_get_brd_spacing(uint8_t ddr_chan, uint8_t valid_cs_bm,
        mddr_phy_spacing_t *brd_spacing, uint8_t num_dimms_in_chan);

void mddr_phy_transfer_dram_vref(uint64_t mddr_base_addr, uint8_t valid_cs_bm);
void mddr_phy_post_training(uint64_t mddr_base_addr);
void mddr_phy_retrieve_dram_vref(uint8_t ddr_chan, uint8_t valid_cs_bm);


/******************************************************************************
* External Functions
******************************************************************************/


/*!****************************************************************************
*
* @par Description:
*    This function trains the DDR channel
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    The status indicating the level of success in PHY training.
*
* @author
*    mwuu
*
******************************************************************************/
unsigned mddr_phy_train(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan)
{
    unsigned status = COM_OK;
    uint64_t mddr_base_addr;

    if ((platform_mode == SILICON) && (
     (mddr_dimm_configs[ddr_chan][0].dev_type != SPD_DEVICE_TYPE_UNDEFINED) ||
     (mddr_dimm_configs[ddr_chan][1].dev_type != SPD_DEVICE_TYPE_UNDEFINED)))
    {

        mddr_base_addr = mddr_base_addrs[ddr_chan];

        monaco_log(LOW, "\n ------------------------------------------\n");
        monaco_log(CRITICAL,
                "| Performing the PHY Training on channel %1d |\n", hddrss[ddr_chan]);
        monaco_log(LOW, " ------------------------------------------\n");

        //------------------------------
        //      Start training
        //------------------------------

        uint8_t fw_type;
        phy_binary_fwtype_t load_fw_type = DDRPHY_FWTYPE_1DTRAINING;
        uint8_t fw_done = 0;
        uint8_t pstate = 0;

        // start with LSB of PHY_RUN_FW
        while (fw_done != PHY_RUN_FW)
        {
            fw_type = mddr_phy_get_fw_type(fw_done);

            if (fw_type == PHY_1D_TRAINING)
            {
                // for both, RDIMM (ignores LR portion)
                load_fw_type = DDRPHY_FWTYPE_1DTRAINING;
            }
            else if (fw_type == PHY_2D_TRAINING)
            {
                load_fw_type = DDRPHY_FWTYPE_2DTRAINING;
            }
            else
            {
                monaco_log(CRITICAL,
                "  Invalid FW type found on channel %1d\n", hddrss[ddr_chan]);
            }

            // load FW
            mddr_phy_load_fwtype(ddr_chan, load_fw_type);

            // config FW
            mddr_phy_config_fw(mddr_settings_ptr, ddr_chan, fw_type, pstate, si_data[ddr_chan].mc_vref);

            // run FW
            status = mddr_phy_run_training_fw(mddr_base_addr, fw_type);

            // POST code for PHY training fail
            if (status != COM_OK)
            {
            }

            // process FW results
            mddr_phy_process_training(mddr_settings_ptr, ddr_chan, fw_type);

            fw_done |= fw_type;
        }

        // post PHY training
        mddr_phy_post_training(mddr_base_addr);

    } // end if Silicon

    return status;
}

unsigned mddr_phy_run_training(uint8_t ddr_chan, mddr_settings_t *mddr_settings_ptr, uint8_t fw_type, int32_t mc_vref)
{
    unsigned status;
    uint64_t mddr_base_addr;
    phy_binary_fwtype_t load_fw_type;
    uint8_t pstate;

    mddr_base_addr = mddr_base_addrs[ddr_chan];
    if (fw_type == PHY_1D_TRAINING)
    {
        // for both, RDIMM (ignores LR portion)
        load_fw_type = DDRPHY_FWTYPE_1DTRAINING;
    }
    else if (fw_type == PHY_2D_TRAINING)
    {
        load_fw_type = DDRPHY_FWTYPE_2DTRAINING;
    }
    else
    {
        monaco_log(CRITICAL,
        "  Invalid FW type found on channel %1d\n", hddrss[ddr_chan]);
        status=COM_ERROR;
        return status;
    }
    pstate = 0;

    // load FW
    mddr_phy_load_fwtype(ddr_chan, load_fw_type);
    // config FW
    mddr_phy_config_fw(mddr_settings_ptr, ddr_chan, fw_type, pstate, (uint32_t) mc_vref);
    // run FW
    status = mddr_phy_run_training_fw(mddr_base_addr, fw_type);
    // process FW results
    mddr_phy_process_training(mddr_settings_ptr, ddr_chan, fw_type);

    return status;
}

uint32_t mddr_phy_get_average_vref(uint64_t mddr_base_addr)
{
    char reg_name[PHY_MAX_REG_NAME_LENGTH];
    uint8_t dbyte;
    uint8_t bit;
    uint32_t vrefdac0_val;
    uint64_t reg_addr;
    float vref_total;

    vref_total = 0;

    for(dbyte = 0; dbyte <= 8; dbyte++)
    {
        reg_addr = (mddr_base_addr + DDRPHY_DBYTE0_VREFDAC0_R0_OFFSET) + (dbyte * VREFDAC_BYTE_STRIDE);
        for(bit = 0; bit < 8; bit++)
        {
            snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH, "DDRPHY_DBYTE%d_VREFDAC0_R%d", dbyte, bit);
            vrefdac0_val = mddr_get_reg(reg_addr, reg_name);
            vref_total += ((0.510 + (vrefdac0_val * 0.00345)) * 10000);
            reg_addr += VREFDAC_BIT_STRIDE;
        }
    }

    return (uint32_t)(vref_total / 72);
}

void mddr_phy_training_cleanup(uint64_t mddr_base_addr, uint8_t ddr_chan)
{
    char reg_name[PHY_MAX_REG_NAME_LENGTH];
    uint8_t dbyte;
    uint8_t rank;
    uint8_t bit;
    uint64_t reg_addr;


    for(dbyte = 0; dbyte <= 8; dbyte++)
    {
        reg_addr = (mddr_base_addr + DDRPHY_DBYTE0_RXPBDLYD0_R0_OFFSET) + (dbyte * RXPBDLY_BYTE_STRIDE);
        for(bit = 0; bit < 8; bit++)
        {
            reg_addr += RXPBDLY_BIT_STRIDE * bit;

            for(rank = 0; rank < 4; rank++)
            {
                snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH, "DDRPHY_DBYTE%d_RXPBDLYD%d_R%d",
                         dbyte, rank, bit);
                mddr_set_reg(reg_addr, reg_name, 0);
                reg_addr += RXPBDLY_RANK_STRIDE;
            }

            reg_addr -= RXPBDLY_RANK_STRIDE * 4;
        }
    }

    mddr_phy_set_si_regs(ddr_chan);
}


unsigned mddr_phy_enhanced_training(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan)
{
    unsigned status = COM_OK;
    unsigned status_up_1d;
    unsigned status_up_2d;
    unsigned status_down_1d;
    unsigned status_down_2d;
    uint64_t mddr_base_addr;
    int32_t base_vref;
    int32_t max_vref_delta;
    int32_t vref_delta;
    int32_t current_vref_up;
    int32_t current_vref_down;
    int32_t ballpark_vref;
    int32_t adjusted_vref;

    if ((platform_mode == SILICON) && (
     (mddr_dimm_configs[ddr_chan][0].dev_type != SPD_DEVICE_TYPE_UNDEFINED) ||
     (mddr_dimm_configs[ddr_chan][1].dev_type != SPD_DEVICE_TYPE_UNDEFINED)))
    {

        status = COM_ERROR;

        // Get the base Vref value from the SI data structure
        base_vref = si_data[ddr_chan].mc_vref;

        // Apply the min and max bounds to the base Vref
        if(base_vref < ddr_vref_min)
        {
            base_vref = ddr_vref_min;
        }
        else if(base_vref > ddr_vref_max)
       {
            base_vref = ddr_vref_max;
        }

        max_vref_delta = COM_MAX(ddr_vref_max - base_vref, base_vref - ddr_vref_min);

        vref_delta = 0;

        cphy_train_ddrss = hddrss[ddr_chan];

        mddr_base_addr = mddr_base_addrs[ddr_chan];

        monaco_log(CRITICAL, "| Performing the Enhanced PHY Training on Channel %1d |\n", hddrss[ddr_chan]);

        if(mddr_settings_ptr->CA_margin_enabled)
        {
            // preset the delay of all CA to be at 1 UI
            // step for only CA margining tool
#if 0
            mddr_ca_set_ca_delay(mddr_base_addr, 0, 0x40);
#endif
        }

        //Vref Search
        while((status != COM_OK) && (vref_delta <= max_vref_delta))
        {
            current_vref_down = base_vref - vref_delta;
            current_vref_up = base_vref + vref_delta;
            monaco_log(MEDIUM, "| Configure passing Vref range upper %d lower %d|\n", current_vref_down, current_vref_up);

            // Lower Vref search
            if(current_vref_down >= ddr_vref_min)
            {
                monaco_log(MEDIUM, "| 1D training with downward Vref %d |\n", current_vref_down);
                status_down_1d = mddr_phy_run_training(ddr_chan, mddr_settings_ptr, PHY_1D_TRAINING, current_vref_down);

                if(status_down_1d == COM_OK)
                {
                    monaco_log(MEDIUM, "| 2D training with downward Vref %d |\n", current_vref_down);
                    status_down_2d = mddr_phy_run_training(ddr_chan, mddr_settings_ptr, PHY_2D_TRAINING, current_vref_down);

                    if(status_down_2d == COM_OK)
                    {
                        ballpark_vref = current_vref_down;
                        monaco_log(MEDIUM, "| Found lower Vref Boundary with Vref %d |\n", ballpark_vref);
                        status = COM_OK;
                    }
                    else
                        monaco_log(CRITICAL, "| 2D training FAILED!!  with downward Vref %d |\n", current_vref_down);
                }
                else
                    monaco_log(CRITICAL, "| 1D training FAILED!!  with downward Vref %d |\n", current_vref_down);

                mddr_phy_training_cleanup(mddr_base_addr, ddr_chan);
            }

            // Upper Vref search
            if((current_vref_up <= ddr_vref_max) && (status != COM_OK) && (current_vref_up != current_vref_down))
            {
                monaco_log(MEDIUM, "| 1D training with upward Vref %d |\n", current_vref_up);
                status_up_1d = mddr_phy_run_training(ddr_chan, mddr_settings_ptr, PHY_1D_TRAINING, current_vref_up);

                if(status_up_1d == COM_OK)
                {
                    monaco_log(MEDIUM, "| 2D training with upward Vref %d |\n", current_vref_up);

                    status_up_2d = mddr_phy_run_training(ddr_chan, mddr_settings_ptr, PHY_2D_TRAINING, current_vref_up);

                    if(status_up_2d == COM_OK)
                    {
                        ballpark_vref = current_vref_up;
                        monaco_log(MEDIUM, "| Found upper Vref Boundary with Vref %d |\n", ballpark_vref);
                        status = COM_OK;
                    }
                    else
                        monaco_log(CRITICAL, "| 2D training FAILED!!  with upward Vref %d |\n", current_vref_up);
                }
                else
                    monaco_log(CRITICAL, "| 1D training FAILED!!  with upward Vref %d |\n", current_vref_up);

                mddr_phy_training_cleanup(mddr_base_addr, ddr_chan);
            }
            vref_delta += ddr_vref_inc;
        }

        if(status == COM_OK)
        {
            adjusted_vref = mddr_phy_get_average_vref(mddr_base_addr);

            monaco_log(HIGH, "| 1D training with adjusted Vref %d |\n", adjusted_vref);

            status |= mddr_phy_run_training(ddr_chan, mddr_settings_ptr, PHY_1D_TRAINING, adjusted_vref);

            monaco_log(HIGH, "| 2D training with adjusted Vref %d |\n", adjusted_vref);

            status |= mddr_phy_run_training(ddr_chan, mddr_settings_ptr, PHY_2D_TRAINING, adjusted_vref);
        }
        else
        {
            monaco_log(CRITICAL, "| Unable to find operational Vref |\n");
        }

        //Post training
        mddr_phy_post_training(mddr_base_addr);
    }
    return status;
}


/******************************************************************************
* Local Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function gets the fw_type from the current ones we want to run.
*
*                                  @param
*    fw_done        Bit mask of completed training FW types.
*
* @return
*   fw_type         FW type to do next
*
* @author
*    mwuu
*
******************************************************************************/
uint32_t mddr_phy_get_fw_type (uint32_t done)
{
    uint32_t fw_type = PHY_1D_TRAINING;

    if (((PHY_1D_TRAINING & PHY_RUN_FW) > 0) &&
            ((done & PHY_1D_TRAINING) == 0))
    {
        fw_type = PHY_1D_TRAINING;
    }
    else if (((PHY_2D_TRAINING & PHY_RUN_FW) > 0) &&
            ((done & PHY_2D_TRAINING) == 0))
    {
        fw_type = PHY_2D_TRAINING;
    }
    else
    {
        monaco_log(CRITICAL,
                "       DDR-TRAIN: Unknown FW type detected!!\n");
    }

    return fw_type;
}


/*!****************************************************************************
*
* @par Description:
*    This function configures the PHY firmware for the training type.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    fw_type          Training type: 1D, 2D, or Diags
*
* @return
*    status           The status indicating the level of success in training.
*
* @author
*    mwuu/lchavani
*
******************************************************************************/
unsigned mddr_phy_run_training_fw(uint64_t mddr_base_addr, uint32_t fw_type)
{
    unsigned status = 0;

    char* fw_type_str = "";
    uint8_t p_state = P_STATE;
    uint32_t dfi_cmd_0_val = 0;
    uint32_t manual_cke_val, mask;
    uint8_t cke_sel = common_cfg.slots_cke_sel;
    bool training_complete = false;
    uint32_t msg_id, timeout_ms;


    if (fw_type == PHY_1D_TRAINING)
        fw_type_str = "1D";
    else if (fw_type == PHY_2D_TRAINING)
        fw_type_str = "2D";

    // setup mailbox registers
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_DCTWRITEPROT_OFFSET,
            "DDRPHY_APBONLY0_DCTWRITEPROT",0x1);
    mddr_set_reg(mddr_base_addr + DDRPHY_DRTUB0_UCTWRITEPROT_OFFSET,
            "DDRPHY_DRTUB0_UCTWRITEPROT",0x1);

    // set dfi_freq to current p_state
    dfi_cmd_0_val =
        (p_state & DFI_CMD0_DFI_FREQ___M) << DFI_CMD0_DFI_FREQ___S;

    mddr_set_reg(mddr_base_addr + MDDR_DDR_DFI_CMD_0_OFFSET,
            "DDR_DFI_CMD_0", dfi_cmd_0_val);

    // PHY to take control of CSRs
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_MICROCONTMUXSEL_OFFSET,
            "DDRPHY_APBONLY0_MICROCONTMUXSEL", 0x1);

    // setup sequencer to start training
    mddr_phy_setup_sequencer(mddr_base_addr, p_state);

    // deassert reset, select CKE clock groups
    manual_cke_val =
       (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;
    manual_cke_val |= (0x1 << MANUAL_CKE_RESET_OFF___S);

    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET,
            "DDR_MANUAL_CKE", manual_cke_val);

    // wait for reset deassert
    timeout_ms = 2;
    mask = cke_sel << DEVICE_STATE_RESET_IS_ON___S;
    mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, mask, 0, timeout_ms);

    // start training; resettomicro=0, testwakeup=0, stalltomicro=0
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_MICRORESET_OFFSET,
            "DDRPHY_APBONLY0_MICRORESET", 0x0);

    // poll for complete
    while (!training_complete)
    {
        msg_id = mddr_phy_get_msg(mddr_base_addr);

        if (msg_id == MSG_ID_COMPLETE)
        {
            training_complete = true;
            monaco_log(CRITICAL, "       DDR-TRAIN:  Training %s PASSED!!\n",
                    fw_type_str);
        }
        else if (msg_id == MSG_ID_FAILED)
        {
            training_complete = true;

            monaco_log(CRITICAL, "       DDR-TRAIN:  Training %s FAILED!!\n",
                    fw_type_str);
            status = COM_ERROR;
        }
    }

    // halt micro-controller; resettomicro=0, testwakeup=0, stalltomicro=1
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_MICRORESET_OFFSET,
            "DDRPHY_APBONLY0_MICRORESET", APBONLY0_MICRORESET_HALT_PMU);

    // reset micro-controller; resettomicro=1, testwakeup=0, stalltomicro=1
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_MICRORESET_OFFSET,
            "DDRPHY_APBONLY0_MICRORESET", APBONLY0_MICRORESET_RESETMC);

    // halt micro-controller; resettomicro=0, testwakeup=0, stalltomicro=1
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_MICRORESET_OFFSET,
            "DDRPHY_APBONLY0_MICRORESET", APBONLY0_MICRORESET_HALT_PMU);

    // put PHY into low-power state
    mddr_phy_setup_sequencer(mddr_base_addr, PHY_LP_STATE);

    // memory controller to take control of CSRs
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_MICROCONTMUXSEL_OFFSET, "DDRPHY_APBONLY0_MICROCONTMUXSEL", 0x0);

    // read PUB REV due to PHY artifact (do not move)
    mddr_get_reg(mddr_base_addr + DDRPHY_DRTUB0_PUBREV_OFFSET,
        "DDRPHY_DRTUB0_PUBREV");

    // clear PHY's internal dfi_init_complete
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIINITCOMPLETE_OFFSET, "DDRPHY_MASTER0_DFIINITCOMPLETE", 0x0);

    return status;
}


/*!****************************************************************************
*
* @par Description:
*    This function processes the PHY training after it has been run.
*    Prints current FW version(DMEM), calls mddr_phy_update_cmd_spacing for 1D,
*    mddr_phy_transfer_dram_vref for 2D.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    fw_type            Training type: 1D, 2D, or Diags
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_process_training
(
    mddr_settings_t *mddr_settings_ptr,
    uint8_t ddr_chan,
    uint32_t fw_type
)
{
    // debug level
    // print training results?

    uint64_t mddr_base_addr = mddr_base_addrs[ddr_chan];

    uint8_t valid_cs_bm = 0;
    uint8_t num_dimms_in_chan = 0;
    uint8_t d0_rank_bm = 0;
    uint8_t d1_rank_bm = 0;
    uint8_t d0_rank_cnt = 0;
    uint8_t d1_rank_cnt = 0;
    uint8_t enables_per_slot = DDR_MAX_RANKS_PER_SLOT;

    if (mddr_dimm_configs[ddr_chan][0].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
    {
        d0_rank_cnt = mddr_dimm_configs[ddr_chan][0].num_ranks;
        ++num_dimms_in_chan;
    }

    if (mddr_dimm_configs[ddr_chan][1].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
    {
        d1_rank_cnt = mddr_dimm_configs[ddr_chan][1].num_ranks;
        ++num_dimms_in_chan;
    }

    d0_rank_bm = 0xF >> (DDR_MAX_RANKS_PER_SLOT - d0_rank_cnt);
    d1_rank_bm = 0xF >> (DDR_MAX_RANKS_PER_SLOT - d1_rank_cnt);

    if (num_dimms_in_chan == DDR_MAX_NUM_SLOTS_PER_CHAN)
    {
        // d0 & d1 slots are both populated so split the enables.
        enables_per_slot /= 2;
        valid_cs_bm = (d1_rank_bm << enables_per_slot) | d0_rank_bm;
    }
    else
    {
        // Only one slot is populated
        // Either d0 or d1 owns all of the bits.
        if (d0_rank_cnt != 0)
        {
            // Only Slot 0 is populated.
            valid_cs_bm = d0_rank_bm;
        }
        else
        {
            // Only Slot 1 is populated.
            valid_cs_bm = d1_rank_bm;
        }
    }

    mddr_phy_print_fw_revision(mddr_base_addr, fw_type);

    if (fw_type == PHY_1D_TRAINING)
    {


        mddr_phy_update_cmd_spacing(mddr_settings_ptr, ddr_chan,
                valid_cs_bm, num_dimms_in_chan);
    }
    else if (fw_type == PHY_2D_TRAINING)
    {
        if(mddr_settings_ptr->CA_margin_enabled)
        {
            mddr_phy_retrieve_dram_vref(ddr_chan,valid_cs_bm);
        }

        mddr_phy_transfer_dram_vref(mddr_base_addr, valid_cs_bm);
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function transfers the Vref settings determined from 2D training to
*    memory controller registers.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    valid_cs_bm        Valid CS bits in current ddr_chan
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_transfer_dram_vref(uint64_t mddr_base_addr, uint8_t valid_cs_bm)
{
    uint8_t rank = 0;
    uint8_t v_ranks = valid_cs_bm;
    uint8_t rbase, idx, shift, byte;
    uint16_t val;
    char reg_name[PHY_MAX_REG_NAME_LENGTH];
    uint32_t mddr_dram_vrefdq[4][5] = {{0}};    // [cs#][0:5]
    uint64_t reg_addr;

    mddr_dram_vrefdq[0][2] = PHY_VREF_VAL;
    mddr_dram_vrefdq[1][2] = PHY_VREF_VAL;
    mddr_dram_vrefdq[2][2] = PHY_VREF_VAL;
    mddr_dram_vrefdq[3][2] = PHY_VREF_VAL;

    // DRAM Vref settings in DMEM 64-103; even=0,2,4,6,8; odd=1,3,5,7,9
    // DMEM_64 to  73, for CS0 [15:8]=odd, [7:0]=even nibbles
    // DMEM_74 to  83, for CS1 [15:8]=odd, [7:0]=even nibbles
    // DMEM_84 to  93, for CS2 [15:8]=odd, [7:0]=even nibbles
    // DMEM_94 to 103, for CS3 [15:8]=odd, [7:0]=even nibbles

    while (v_ranks > 0)
    {
        if ((v_ranks & 0x1) > 0)
        {
            rbase = (10 * rank) + PHY_VREF_CS0_DMEM;
            reg_addr = mddr_base_addr + DDRPHY_UCTL_DMEM_64_OFFSET +
                (4 * 10 * rank);

            for (byte = 0; byte < 9; byte++)
            {
                snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
                    "DDRPHY_UCTL_DMEM_%d", (rbase + byte));

                // get PHY even/odd value for current rank
                val = mddr_get_reg((reg_addr + (4 * byte)), reg_name);

                idx = byte / 4;             // each register holds 4 bytes
                shift = (byte % 4) * 8;     // vref val on multiples of 8

                // store x8 vref value
                mddr_dram_vrefdq[rank][idx] |=
                    ((val & PHY_VREF_MASK) << shift);

                // store x4 upper vref value
                // byte_8_x4 is in idx 2, starting at bit 8
                if (idx != 2)
                {
                    idx += 3;
                }
                else
                {
                    shift = 8;
                }

                mddr_dram_vrefdq[rank][idx] |= (
                    ((val >> 8) & PHY_VREF_MASK) << shift
                );
            }

            // write memory controller register for current rank
            for (idx = 0; idx < 5; idx++)
            {
                reg_addr = mddr_base_addr + MDDR_DRAM_VREFDQ_CS0_0_OFFSET +
                    (rank * 0x14) + (0x4 * idx);

                snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
                        "DRAM_VREFDQ_CS%d_%d", rank, idx);

                mddr_set_reg(reg_addr, reg_name, mddr_dram_vrefdq[rank][idx]);
            }
        }

        rank += 1;
        v_ranks = v_ranks >> 1;
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function prints the PHY firmware revision that was run.  FW must be
*    run before this function is called.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    fw_type          Training type: 1D, 2D, or Diags
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_print_fw_revision(uint64_t mddr_base_addr, uint32_t fw_type)
{
    char* fw_type_str = "";
    uint16_t revision;
    uint16_t minor, major, day, month, year;

    revision = mddr_get_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_1_OFFSET,
            "DDRPHY_UCTL_DMEM_1");

    if (fw_type == PHY_1D_TRAINING)
        fw_type_str = "1D";
    else if (fw_type == PHY_2D_TRAINING)
        fw_type_str = "2D";

    major = (revision >> PHY_FW_REV_MAJOR___S) & PHY_FW_REV_MAJOR___M;
    minor = (revision >> PHY_FW_REV_MINOR___S) & PHY_FW_REV_MINOR___M;
    month = (revision >> PHY_FW_REV_MONTH___S) & PHY_FW_REV_MONTH___M;
    day = (revision >> PHY_FW_REV_DAY___S) & PHY_FW_REV_DAY___M;
    year = ((revision >> PHY_FW_REV_YEAR___S) & PHY_FW_REV_YEAR___M) +
        PHY_FW_REV_YEAR_OFFSET;

    monaco_log(LOW,
        "DDR-TRAIN:  %s FW v%d.%d %d/%d/%d (0x%04x)\n",
        fw_type_str, major, minor, month, day, year, revision);
}


/*!****************************************************************************
*
* @par Description:
*    This function gets the command spacing found after 1D training has run.
*    Also known as critical delay differences(cdd) for each chip select.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    valid_cs_bm        Valid CS bits in current ddr_chan
*                                  @param
*    num_dimms          Number of DIMMs in channel
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_update_cmd_spacing(
        mddr_settings_t *mddr_settings_ptr,
        uint8_t ddr_chan,
        uint8_t valid_cs_bm,
        uint8_t num_dimms
)
{
    uint8_t ddrphy_diff_dimm_wtw, ddrphy_diff_dimm_rtr;
    uint8_t ddrphy_diff_dimm_wtr, ddrphy_diff_dimm_rtw;
    uint8_t ddrphy_diff_cs_rtr, ddrphy_diff_cs_wtw;
    uint8_t ddrphy_diff_cs_wtr, ddrphy_diff_cs_rtw;
    uint8_t ddrphy_diff_rank_rtw, ddrphy_srank_rtw;

    mddr_phy_spacing_t brd_spacing = {0};
    mddr_plat_cycle_adj_t *cycle_adj;

    // 4.14.2  Add spacing due to DDR PHY
    uint8_t phy_diff_dimm_wtw, phy_diff_cs_wtw;
    uint8_t phy_diff_dimm_rtr = 1;
    uint8_t phy_diff_cs_rtr = 1;
    bool wr_2t_pre = false;

    if ((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
        (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
            wr_2t_pre = true;

    // calulate spacing with CDD based on DIMMs and chip selects
    mddr_phy_get_brd_spacing(ddr_chan, valid_cs_bm, &brd_spacing, num_dimms);

    cycle_adj = &si_data[ddr_chan].cycle_adjusts;

    if (!wr_2t_pre)     // 1tck write preamble
    {
        phy_diff_dimm_wtw = 4;
        phy_diff_cs_wtw = 4;
    }
    else                    // 2tck, lower due to adjustment from controller
    {
        phy_diff_dimm_wtw = 3;
        phy_diff_cs_wtw = 3;
    }

    // values due to SI adjustments
    uint8_t si_diff_dimm_wtw, si_diff_dimm_rtr;
    uint8_t si_diff_dimm_wtr, si_diff_dimm_rtw;
    uint8_t si_diff_cs_rtr, si_diff_cs_wtw;
    uint8_t si_diff_cs_wtr, si_diff_cs_rtw;
    uint8_t si_srank_rtw, si_diff_rank_rtw;

    // populate SI values
    si_diff_dimm_wtw = cycle_adj->dimm_wtw;
    si_diff_dimm_rtr = cycle_adj->dimm_rtr;
    si_diff_dimm_wtr = cycle_adj->dimm_wtr;
    si_diff_dimm_rtw = cycle_adj->dimm_rtw;
    si_diff_cs_wtw = cycle_adj->cs_wtw;
    si_diff_cs_rtr = cycle_adj->cs_rtr;
    si_diff_cs_wtr = cycle_adj->cs_wtr;
    si_diff_cs_rtw = cycle_adj->cs_rtw;
    si_srank_rtw = cycle_adj->srank_rtw;
    si_diff_rank_rtw = cycle_adj->rank_rtw;

    // spacing from training, phy, and SI
    uint8_t brd_phy_si_diff_dimm_wtw, brd_phy_si_diff_dimm_rtr;
    uint8_t brd_phy_si_diff_dimm_wtr, brd_phy_si_diff_dimm_rtw;
    uint8_t brd_phy_si_diff_cs_rtr, brd_phy_si_diff_cs_wtw;
    uint8_t brd_phy_si_diff_cs_wtr, brd_phy_si_diff_cs_rtw;

    // combine with PHY delays and SI
    brd_phy_si_diff_dimm_wtw = brd_spacing.dimm_wtw +
        phy_diff_dimm_wtw + si_diff_dimm_wtw;

    brd_phy_si_diff_dimm_rtr = brd_spacing.dimm_rtr +
        phy_diff_dimm_rtr + si_diff_dimm_rtr;

    brd_phy_si_diff_dimm_wtr = brd_spacing.dimm_wtr + si_diff_dimm_wtr;
    brd_phy_si_diff_dimm_rtw = brd_spacing.dimm_rtw + si_diff_dimm_rtw;

    brd_phy_si_diff_cs_rtr = brd_spacing.cs_rtr +
        phy_diff_cs_rtr + si_diff_cs_rtr;

    brd_phy_si_diff_cs_wtw = brd_spacing.cs_wtw +
        phy_diff_cs_wtw + si_diff_cs_wtw;

    brd_phy_si_diff_cs_wtr = brd_spacing.cs_wtr + si_diff_cs_wtr;
    brd_phy_si_diff_cs_rtw = brd_spacing.cs_rtw + si_diff_cs_rtw;

    // 4.14.3  Command spacing due to ODT
// FIX combining ODT etc.
    uint8_t odt_diff_dimm_wtw = 3;
    uint8_t odt_diff_cs_wtw = 3;
    uint8_t odt_diff_dimm_rtr = 0;
    uint8_t odt_diff_cs_rtr = 0;
    uint8_t odt_diff_dimm_wtr = 1;
    uint8_t odt_diff_cs_wtr = 1;
    uint8_t odt_diff_dimm_rtw = 0;
    uint8_t odt_diff_cs_rtw = 0;


    uint32_t wrodt = mddr_reg_vals.ddr_odt_wr_cntl_val[ddr_chan];
    uint32_t rdodt = mddr_reg_vals.ddr_odt_rd_cntl_val[ddr_chan];

    uint8_t rtt_nom = si_data[ddr_chan].dimm_si[0].rank_si[0].rtt_nom;
    uint8_t rtt_wr = si_data[ddr_chan].dimm_si[0].rank_si[0].rtt_wr;
    uint8_t rtt_park = si_data[ddr_chan].dimm_si[0].rank_si[0].rtt_park;
    uint16_t mc_term = si_data[ddr_chan].mc_term;

    uint8_t total_ranks = mddr_dimm_configs[ddr_chan][0].num_ranks +
            mddr_dimm_configs[ddr_chan][1].num_ranks;

    bool rtt_park_effect;
    if ((rtt_park != 0) && (total_ranks > 1))
    {
        rtt_park_effect = true;
    }
    else
    {
        rtt_park_effect = false;
    }

    bool wrodt_en, rdodt_en, dram_rdodt_en;
    if (rtt_park_effect || (rtt_wr != 0) || ((wrodt != 0) && (rtt_nom != 0)))
    {
        wrodt_en = true;
    }
    else
    {
        wrodt_en = false;
    }

    if (rtt_park_effect || ((rdodt != 0) && (rtt_nom != 0)))
    {
        dram_rdodt_en = true;
    }
    else
    {
        dram_rdodt_en = false;
    }

    if (dram_rdodt_en || (mc_term != 0))
    {
        rdodt_en = true;
    }
    else
    {
        rdodt_en = false;
    }

    if (wrodt_en)       // write ODT's used
    {
        if (rdodt_en)   // read ODT's used
        {
            odt_diff_dimm_wtr = 2;
            odt_diff_cs_wtr = 2;
        }
        else
        {
            odt_diff_dimm_wtr = 1;
            odt_diff_cs_wtr = 1;
        }
/*
        ddrphy_diff_dimm_wtr = COM_MAX(
                odt_diff_dimm_wtr, ddrphy_diff_dimm_wtr);

        ddrphy_diff_cs_wtr = COM_MAX(
                odt_diff_cs_wtr, ddrphy_diff_cs_wtr);
*/
/*  Not needed since PHY spacing ODT dominates
        // different write ODT's asserted
        if (wrodt_diff_target)
        {
            uint8_t diff_wrodt_preamble;

            if (wr_2t_pre == 1)
            {
                diff_wrodt_preamble = 2;
            }
            else
            {
                diff_wrodt_preamble = 3;
            }

            odt_diff_dimm_wtw = diff_wrodt_preamble;
            odt_diff_cs_wtw = diff_wrodt_preamble;

            ddrphy_diff_dimm_wtw = COM_MAX(
                    odt_diff_dimm_wtw, ddrphy_diff_dimm_wtw);

            ddrphy_diff_cs_wtw = COM_MAX(
                    odt_diff_cs_wtw, ddrphy_diff_cs_wtw);
        }
*/
    }

    if (dram_rdodt_en)      // DRAM ODT's used on reads
    {
        odt_diff_dimm_rtr = 2;
        odt_diff_cs_rtr = 2;
/*
        ddrphy_diff_dimm_rtr = COM_MAX(
                odt_diff_dimm_rtr, ddrphy_diff_dimm_rtr);

        ddrphy_diff_cs_rtr = COM_MAX(
                odt_diff_cs_rtr, ddrphy_diff_cs_rtr);
*/    }

    // write ODT enabled and PHY ODT used on reads
    if (wrodt_en && (mc_term != 0))
    {
        odt_diff_dimm_rtw = 1;
        odt_diff_cs_rtw = 1;
/*
        ddrphy_diff_dimm_rtw = COM_MAX(
                odt_diff_dimm_rtw, ddrphy_diff_dimm_rtw);

        ddrphy_diff_cs_rtw = COM_MAX(
                odt_diff_cs_rtw, ddrphy_diff_cs_rtw);
*/    }

    // Combine and get max of it all...
    ddrphy_diff_dimm_wtw =
        COM_MAX(brd_phy_si_diff_dimm_wtw, odt_diff_dimm_wtw);

    ddrphy_diff_dimm_rtr =
        COM_MAX(brd_phy_si_diff_dimm_rtr, odt_diff_dimm_rtr);

    ddrphy_diff_dimm_wtr =
        COM_MAX(brd_phy_si_diff_dimm_wtr, odt_diff_dimm_wtr);

    ddrphy_diff_dimm_rtw =
        COM_MAX(brd_phy_si_diff_dimm_rtw, odt_diff_dimm_rtw);

    ddrphy_diff_cs_wtw = COM_MAX(brd_phy_si_diff_cs_wtw, odt_diff_cs_wtw);
    ddrphy_diff_cs_rtr = COM_MAX(brd_phy_si_diff_cs_rtr, odt_diff_cs_rtr);
    ddrphy_diff_cs_wtr = COM_MAX(brd_phy_si_diff_cs_wtr, odt_diff_cs_wtr);
    ddrphy_diff_cs_rtw = COM_MAX(brd_phy_si_diff_cs_rtw, odt_diff_cs_rtw);

    ddrphy_srank_rtw = brd_spacing.srank_rtw + si_srank_rtw;
    ddrphy_diff_rank_rtw = si_diff_rank_rtw;

    if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
    {
    // 4.14.4  Command spacing due to LRDIMM DB
        uint8_t lrdimm_diff_dimm_wtw, lrdimm_diff_cs_wtw;
        uint8_t lrdimm_diff_dimm_rtr, lrdimm_diff_cs_rtr;
        uint8_t lrdimm_diff_dimm_wtr, lrdimm_diff_cs_wtr;
        uint8_t lrdimm_diff_dimm_rtw, lrdimm_diff_cs_rtw;
        uint8_t lrdimm_diff_rank_rtw, lrdimm_same_rank_rtw;

        if (wr_2t_pre)   // 2tck write preamble, roundUp(1.8)
        {
            lrdimm_diff_dimm_wtw = 2;
            lrdimm_diff_dimm_wtr = 2;
            lrdimm_diff_cs_wtw = 2;
            lrdimm_diff_cs_wtr = 2;
        }
        else                        // 1tck write preamble, roundUp(2.7+0.5-1)
        {
            lrdimm_diff_dimm_wtw = 3;
            lrdimm_diff_dimm_wtr = 3;
            lrdimm_diff_cs_wtw = 3;
            lrdimm_diff_cs_wtr = 3;
        }

        lrdimm_diff_dimm_rtw = 6;     // 3 + roundUp(tpdm_RD + tpdm_WR)
        lrdimm_diff_cs_rtw = 6;

        lrdimm_diff_dimm_rtr = 2;     // roundUp(1.8)
        lrdimm_diff_cs_rtr = 2;

        lrdimm_diff_rank_rtw = 3;     // roundUp(tpdm_RD + tpdm_WR)
        lrdimm_same_rank_rtw = 3;

        ddrphy_diff_dimm_wtw =
            COM_MAX(ddrphy_diff_dimm_wtw, lrdimm_diff_dimm_wtw);

        ddrphy_diff_dimm_rtr =
            COM_MAX(ddrphy_diff_dimm_rtr, lrdimm_diff_dimm_rtr);

        ddrphy_diff_dimm_wtr =
            COM_MAX(ddrphy_diff_dimm_wtr, lrdimm_diff_dimm_wtr);

        ddrphy_diff_dimm_rtw =
            COM_MAX(ddrphy_diff_dimm_rtw, lrdimm_diff_dimm_rtw);

        ddrphy_diff_cs_wtw = COM_MAX(ddrphy_diff_cs_wtw, lrdimm_diff_cs_wtw);
        ddrphy_diff_cs_rtr = COM_MAX(ddrphy_diff_cs_rtr, lrdimm_diff_cs_rtr);
        ddrphy_diff_cs_wtr = COM_MAX(ddrphy_diff_cs_wtr, lrdimm_diff_cs_wtr);
        ddrphy_diff_cs_rtw = COM_MAX(ddrphy_diff_cs_rtw, lrdimm_diff_cs_rtw);

        ddrphy_srank_rtw = COM_MAX(ddrphy_srank_rtw, lrdimm_same_rank_rtw);
        ddrphy_diff_rank_rtw =
            COM_MAX(si_diff_rank_rtw, lrdimm_diff_rank_rtw);
    }

    ddrphy_diff_dimm_wtw = COM_MIN(ddrphy_diff_dimm_wtw, MAX_CYCLE_ADJUST);
    ddrphy_diff_dimm_rtr = COM_MIN(ddrphy_diff_dimm_rtr, MAX_CYCLE_ADJUST);
    ddrphy_diff_dimm_wtr = COM_MIN(ddrphy_diff_dimm_wtr, MAX_CYCLE_ADJUST);
    ddrphy_diff_dimm_rtw = COM_MIN(ddrphy_diff_dimm_rtw, MAX_CYCLE_ADJUST);

    ddrphy_diff_cs_wtw = COM_MIN(ddrphy_diff_cs_wtw, MAX_CYCLE_ADJUST);
    ddrphy_diff_cs_rtr = COM_MIN(ddrphy_diff_cs_rtr, MAX_CYCLE_ADJUST);
    ddrphy_diff_cs_wtr = COM_MIN(ddrphy_diff_cs_wtr, MAX_CYCLE_ADJUST);
    ddrphy_diff_cs_rtw = COM_MIN(ddrphy_diff_cs_rtw, MAX_CYCLE_ADJUST);

    ddrphy_srank_rtw = COM_MIN(ddrphy_srank_rtw, MAX_CYCLE_ADJUST);
    ddrphy_diff_rank_rtw = COM_MIN(ddrphy_diff_rank_rtw, MAX_CYCLE_ADJUST);

    uint64_t mddr_base_addr = mddr_base_addrs[ddr_chan];
    uint32_t adj_rdwr0_val, adj_rdwr1_val;

    adj_rdwr0_val = ddrphy_diff_dimm_wtw << ADJ_RDWR0_DIMM_WTW___S;
    adj_rdwr0_val |= ddrphy_diff_dimm_rtr << ADJ_RDWR0_DIMM_RTR___S;
    adj_rdwr0_val |= ddrphy_diff_dimm_wtr << ADJ_RDWR0_DIMM_WTR___S;
    adj_rdwr0_val |= ddrphy_diff_dimm_rtw << ADJ_RDWR0_DIMM_RTW___S;
    adj_rdwr0_val |= ddrphy_diff_cs_wtw << ADJ_RDWR0_CS_WTW___S;
    adj_rdwr0_val |= ddrphy_diff_cs_rtr << ADJ_RDWR0_CS_RTR___S;
    adj_rdwr0_val |= ddrphy_diff_cs_wtr << ADJ_RDWR0_CS_WTR___S;
    adj_rdwr0_val |= ddrphy_diff_cs_rtw << ADJ_RDWR0_CS_RTW___S;

    adj_rdwr1_val =  cycle_adj->rank_wtw << ADJ_RDWR1_RANK_WTW___S;
    adj_rdwr1_val |= cycle_adj->rank_rtr << ADJ_RDWR1_RANK_RTR___S;
    adj_rdwr1_val |= cycle_adj->rank_wtr << ADJ_RDWR1_RANK_WTR___S;
    adj_rdwr1_val |= ddrphy_diff_rank_rtw << ADJ_RDWR1_RANK_RTW___S;
    adj_rdwr1_val |= cycle_adj->srank_wtw << ADJ_RDWR1_SRANK_WTW___S;
    adj_rdwr1_val |= cycle_adj->srank_rtr << ADJ_RDWR1_SRANK_RTR___S;
    adj_rdwr1_val |= cycle_adj->srank_wtr << ADJ_RDWR1_SRANK_WTR___S;
    adj_rdwr1_val |= ddrphy_srank_rtw << ADJ_RDWR1_SRANK_RTW___S;

    mddr_set_reg(mddr_base_addr + MDDR_TIMING_ADJ_RDWR_0_OFFSET,
            "TIMING_ADJ_RDWR_0", adj_rdwr0_val);
    mddr_set_reg(mddr_base_addr + MDDR_TIMING_ADJ_RDWR_1_OFFSET,
            "TIMING_ADJ_RDWR_1", adj_rdwr1_val);
    mddr_set_reg(mddr_base_addr + MDDR_CSR_CNTL_OFFSET, "CSR_CNTL", 0x1);

/*
    // store either MAX_CYCLE_ADJUST or value back
    cycle_adj->dimm_wtw = COM_MIN(ddrphy_diff_dimm_wtw, MAX_CYCLE_ADJUST);
    cycle_adj->dimm_rtr = COM_MIN(ddrphy_diff_dimm_rtr, MAX_CYCLE_ADJUST);
    cycle_adj->dimm_wtr = COM_MIN(ddrphy_diff_dimm_wtr, MAX_CYCLE_ADJUST);
    cycle_adj->dimm_rtw = COM_MIN(ddrphy_diff_dimm_rtw, MAX_CYCLE_ADJUST);

    cycle_adj->cs_wtw = COM_MIN(ddrphy_diff_cs_wtw, MAX_CYCLE_ADJUST);
    cycle_adj->cs_rtr = COM_MIN(ddrphy_diff_cs_rtr, MAX_CYCLE_ADJUST);
    cycle_adj->cs_wtr = COM_MIN(ddrphy_diff_cs_wtr, MAX_CYCLE_ADJUST);
    cycle_adj->cs_rtw = COM_MIN(ddrphy_diff_cs_rtw, MAX_CYCLE_ADJUST);

    cycle_adj->srank_rtw = COM_MIN(ddrphy_srank_rtw, MAX_CYCLE_ADJUST);
    cycle_adj->rank_rtw = COM_MIN(ddrphy_diff_rank_rtw, MAX_CYCLE_ADJUST);
*/
}


/*!****************************************************************************
*
* @par Description:
*    This function gets the command spacing found after 1D training has run.
*    Also known as critical delay differences(cdd) for each chip select.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    cdd[][][]          CDD array where the command spacing is stored.
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_get_cmd_spacing
(
    uint8_t ddr_chan,
    uint8_t cdd[PHY_CDD_TYPES][DDR_MAX_NUM_RANKS][DDR_MAX_NUM_RANKS]
)
{
    uint16_t reg_data;
    uint8_t reg_num;
    // cdd [type][src_rank][tgt_rank]
    // types: 0=RW, 1=WW, 2=RR
    uint8_t type, src_rank, tgt_rank;

    uint8_t num_ranks_both = mddr_dimm_configs[ddr_chan][0].num_ranks +
        mddr_dimm_configs[ddr_chan][1].num_ranks;

    uint64_t mddr_base_addr = mddr_base_addrs[ddr_chan];
    uint64_t reg_addr = mddr_base_addr + DDRPHY_UCTL_DMEM_34_OFFSET;
    uint64_t end_addr = mddr_base_addr + DDRPHY_UCTL_DMEM_15_OFFSET;
    char reg_name[PHY_MAX_REG_NAME_LENGTH];

    // handle odd balls first
    if (num_ranks_both >= DDR_MAX_NUM_RANKS)
    {
        reg_data = mddr_get_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_15_OFFSET,
                "DDRPHY_UCTL_DMEM_15");

        cdd[PHY_CDD_RR][3][2] = mddr_phy_get_pos_2s_complement(reg_data >> 8);
    }

    reg_data = mddr_get_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_35_OFFSET,
            "DDRPHY_UCTL_DMEM_35");

    cdd[PHY_CDD_RW][0][0] = mddr_phy_get_pos_2s_complement(reg_data & 0xFF);


    type = 0;
    src_rank = 0;
    tgt_rank = 1;
    reg_num = 34;
    // process [DMEM_34 to DMEM_16]
    while (reg_addr > end_addr)
    {
        snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
                "DDRPHY_UCTL_DMEM_%d", reg_num);

        reg_data = mddr_get_reg(reg_addr, reg_name);

        if (type != 0)
        {
            if (tgt_rank == 4)
            {
                tgt_rank = 0;
                src_rank += 1;
            }

            if (src_rank == tgt_rank)
            {
                tgt_rank += 1;
            }
        }

        type = COM_MIN(type, (PHY_CDD_TYPES-1));
        src_rank = COM_MIN(src_rank, (DDR_MAX_NUM_RANKS-1));
        tgt_rank = COM_MIN(tgt_rank, (DDR_MAX_NUM_RANKS-1));
        cdd[type][src_rank][tgt_rank] =
            mddr_phy_get_pos_2s_complement(reg_data >> 8);

        if (tgt_rank == 3)
        {
            if (src_rank == 3)
            {
                src_rank = 0;
                tgt_rank = 0;
                type += 1;
            }
            else
            {
                src_rank += 1;
                tgt_rank = 0;
            }
        }
        else
        {
            tgt_rank += 1;
        }

        if ((type != 0) && (src_rank == tgt_rank))
        {
            if (tgt_rank == 3)
            {
                if (src_rank == 3)
                {
                    src_rank = 0;
                    tgt_rank = 1;
                    type += 1;
                }
                else
                {
                    src_rank += 1;
                    tgt_rank = 0;
                }
            }
            else
            {
                tgt_rank += 1;
            }
        }

        type = COM_MIN(type, (PHY_CDD_TYPES-1));
        src_rank = COM_MIN(src_rank, (DDR_MAX_NUM_RANKS-1));
        tgt_rank = COM_MIN(tgt_rank, (DDR_MAX_NUM_RANKS-1));
        cdd[type][src_rank][tgt_rank] =
            mddr_phy_get_pos_2s_complement(reg_data & 0xFF);

        tgt_rank += 1;
        reg_num -= 1;
        reg_addr -= 4;
    }

    /************************************************
     * for debug of delays
    src_rank=0;
    while (src_rank < DDR_MAX_NUM_RANKS)
    {
        tgt_rank=0;
        while (tgt_rank < DDR_MAX_NUM_RANKS)
        {
            monaco_log(INFORMATIONAL, "  CDD_RW_%i_%i = %2i, "
                    "CDD_WW_%i_%i = %2i, CDD_RR_%i_%i = %2i\n",
                    src_rank, tgt_rank, cdd[0][src_rank][tgt_rank],
                    src_rank, tgt_rank, cdd[1][src_rank][tgt_rank],
                    src_rank, tgt_rank, cdd[2][src_rank][tgt_rank]);

            tgt_rank++;
        }
        src_rank++;
    }
    ************************************************/
}


/*!****************************************************************************
*
* @par Description:
*    This function returns the positive 2's complement value.  Returns 0 if the
*    value is negative.
*
*                                  @param
*    value            An 8bit value to be evaluated
*
* @return
*    pos_val          Positive value of 2's complement
*
* @author
*    mwuu
*
******************************************************************************/
uint8_t mddr_phy_get_pos_2s_complement(uint8_t value)
{
    if ((value & 0x80) > 0)
    {
        return 0;
    }
    else
    {
        return (value & 0xFF);
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function gets the command spacing found after 1D training has run.
*    Also known as critical delay differences(cdd) for each chip select.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    valid_cs_bm        Valid CS bits in current ddr_chan
*                                  @param
*    *brd_spacing       Spacing the training found from PHY and due to number
*                       of DIMMs and chip selects
*                                  @param
*    num_dimms_in_chan  Number of DIMMs in current ddr_chan
*
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_get_brd_spacing
(
    uint8_t ddr_chan,
    uint8_t valid_cs_bm,
    mddr_phy_spacing_t *brd_spacing,
    uint8_t num_dimms_in_chan
)
{
    // wtr uses setting from wtw
    uint8_t brd_diff_dimm_wtw = 0;
    uint8_t brd_diff_dimm_rtr = 0;
    uint8_t brd_diff_dimm_rtw = 0;

    uint8_t brd_diff_cs_wtw = 0;
    uint8_t brd_diff_cs_rtr = 0;
    uint8_t brd_diff_cs_rtw = 0;

    uint8_t brd_same_rank_rtw = 0;

    // [type][src_rank][tgt_rank]
    // types: 0=RW, 1=WW, 2=RR
    uint8_t cdd[PHY_CDD_TYPES][DDR_MAX_NUM_RANKS][DDR_MAX_NUM_RANKS] = {{{0}}};

    // get CDD from PHY
    mddr_phy_get_cmd_spacing(ddr_chan, cdd);

    if (valid_cs_bm == 0x1)          // single rank
    {
        brd_same_rank_rtw = cdd[0][0][0];       // RW 0,0
    }
    else if (valid_cs_bm == 0x3)     // dual rank
    {
        uint8_t rtw00, rtw11;
        uint8_t rtw01, rtw10;
        uint8_t wtw01, wtw10;
        uint8_t rtr01, rtr10;

        // RTW
        rtw01 = cdd[0][0][1];
        rtw10 = cdd[0][1][0];
        brd_diff_cs_rtw = COM_MAX(rtw01, rtw10);

        rtw00 = cdd[0][0][0];
        rtw11 = cdd[0][1][1];
        brd_same_rank_rtw = COM_MAX(rtw00, rtw11);

        // WTW
        wtw01 = cdd[1][0][1];
        wtw10 = cdd[1][1][0];
        brd_diff_cs_wtw = COM_MAX(wtw01, wtw10);

        // RTR
        rtr01 = cdd[2][0][1];
        rtr10 = cdd[2][1][0];
        brd_diff_cs_rtr = COM_MAX(rtr01, rtr10);
    }
    else if ((valid_cs_bm == 0x5) || (valid_cs_bm == 0x7) || (valid_cs_bm == 0xD))
    {
    // single rank (2 DIMMs)
    // or S0: dual rank; S1: single rank
        uint8_t rtw02, rtw20;
        uint8_t rtw00, rtw22;
        uint8_t wtw02, wtw20;
        uint8_t rtr02, rtr20;

        rtw20 = cdd[0][2][0];
        rtw02 = cdd[0][0][2];
        brd_diff_dimm_rtw = COM_MAX(rtw02, rtw20);

        rtw00 = cdd[0][0][0];
        rtw22 = cdd[0][2][2];
        brd_same_rank_rtw = COM_MAX(rtw00, rtw22);

        wtw20 = cdd[1][2][0];
        wtw02 = cdd[1][0][2];
        brd_diff_dimm_wtw = COM_MAX(wtw02, wtw20);

        rtr20 = cdd[2][2][0];
        rtr02 = cdd[2][0][2];
        brd_diff_dimm_rtr = COM_MAX(rtr02, rtr20);

        if (valid_cs_bm == 0x7)
        {
            uint8_t tmp0;
            uint8_t rtw11;
            uint8_t rtw12, rtw21;
            uint8_t wtw12, wtw21;
            uint8_t rtr12, rtr21;
            uint8_t rtw01, rtw10;
            uint8_t wtw01, wtw10;
            uint8_t rtr01, rtr10;

            rtw12 = cdd[0][1][2];
            rtw21 = cdd[0][2][1];

            tmp0 = COM_MAX(rtw12, rtw21);
            brd_diff_dimm_rtw = COM_MAX(tmp0, brd_diff_dimm_rtw);

            rtw11 = cdd[0][1][1];

            brd_same_rank_rtw = COM_MAX(rtw11, brd_same_rank_rtw);

            wtw12 = cdd[1][1][2];
            wtw21 = cdd[1][2][1];

            tmp0 = COM_MAX(wtw12, wtw21);
            brd_diff_dimm_wtw = COM_MAX(tmp0, brd_diff_dimm_wtw);

            rtr12 = cdd[2][1][2];
            rtr21 = cdd[2][2][1];

            tmp0 = COM_MAX(rtr12, rtr21);
            brd_diff_dimm_rtr = COM_MAX(tmp0, brd_diff_dimm_rtr);

            // RTW
            rtw01 = cdd[0][0][1];
            rtw10 = cdd[0][1][0];
            brd_diff_cs_rtw = COM_MAX(rtw01, rtw10);

            // WTW
            wtw01 = cdd[1][0][1];
            wtw10 = cdd[1][1][0];
            brd_diff_cs_wtw = COM_MAX(wtw01, wtw10);

            // RTR
            rtr01 = cdd[2][0][1];
            rtr10 = cdd[2][1][0];
            brd_diff_cs_rtr = COM_MAX(rtr01, rtr10);
        }
        else if (valid_cs_bm == 0xD)
        {
            uint8_t tmp0;
            uint8_t rtw33;
            uint8_t rtw03, rtw30;
            uint8_t wtw03, wtw30;
            uint8_t rtr03, rtr30;
            uint8_t rtw23, rtw32;
            uint8_t wtw23, wtw32;
            uint8_t rtr23, rtr32;

            rtw03 = cdd[0][0][3];
            rtw30 = cdd[0][3][0];

            tmp0 = COM_MAX(rtw03, rtw30);
            brd_diff_dimm_rtw = COM_MAX(tmp0, brd_diff_dimm_rtw);

            rtw33 = cdd[0][3][3];

            brd_same_rank_rtw = COM_MAX(rtw33, brd_same_rank_rtw);

            wtw03 = cdd[1][0][3];
            wtw30 = cdd[1][3][0];

            tmp0 = COM_MAX(wtw03, wtw30);
            brd_diff_dimm_wtw = COM_MAX(tmp0, brd_diff_dimm_wtw);

            rtr03 = cdd[2][0][3];
            rtr30 = cdd[2][3][0];

            tmp0 = COM_MAX(rtr03, rtr30);
            brd_diff_dimm_rtr = COM_MAX(tmp0, brd_diff_dimm_rtr);

            // RTW
            rtw23 = cdd[0][2][3];
            rtw32 = cdd[0][3][2];
            brd_diff_cs_rtw = COM_MAX(rtw23, rtw32);

            // WTW
            wtw23 = cdd[1][2][3];
            wtw32 = cdd[1][3][2];
            brd_diff_cs_wtw = COM_MAX(wtw23, wtw32);

            // RTR
            rtr23 = cdd[2][2][3];
            rtr32 = cdd[2][3][2];
            brd_diff_cs_rtr = COM_MAX(rtr23, rtr32);
        }
    }
    // dual rank (2 DIMMs), or quad rank
    else if (valid_cs_bm == 0xF)
    {
        uint8_t tmp0, tmp1, tmp2, tmp3;
        uint8_t rtw02, rtw03, rtw12, rtw13;
        uint8_t rtw20, rtw21, rtw30, rtw31;
        uint8_t wtw02, wtw03, wtw12, wtw13;
        uint8_t wtw20, wtw21, wtw30, wtw31;
        uint8_t rtr02, rtr03, rtr12, rtr13;
        uint8_t rtr20, rtr21, rtr30, rtr31;
        uint8_t rtw01, rtw10, rtw32, rtw23;
        uint8_t wtw01, wtw10, wtw32, wtw23;
        uint8_t rtr01, rtr10, rtr32, rtr23;
        uint8_t rtw00, rtw11, rtw22, rtw33;

        rtw00 = cdd[0][0][0];
        rtw11 = cdd[0][1][1];
        rtw22 = cdd[0][2][2];
        rtw33 = cdd[0][3][3];

        tmp0 = COM_MAX(rtw00, rtw11);
        tmp1 = COM_MAX(rtw22, rtw33);
        brd_same_rank_rtw = COM_MAX(tmp0, tmp1);


        if (num_dimms_in_chan==2) // 2 DIMM
        {
            rtw02 = cdd[0][0][2];
            rtw03 = cdd[0][0][3];
            rtw12 = cdd[0][1][2];
            rtw13 = cdd[0][1][3];
            rtw20 = cdd[0][2][0];
            rtw21 = cdd[0][2][1];
            rtw30 = cdd[0][3][0];
            rtw31 = cdd[0][3][1];

            tmp0 = COM_MAX(rtw02, rtw03);
            tmp1 = COM_MAX(rtw12, rtw13);
            tmp2 = COM_MAX(tmp0, tmp1);
            tmp0 = COM_MAX(rtw20, rtw21);
            tmp1 = COM_MAX(rtw30, rtw31);
            tmp3 = COM_MAX(tmp0, tmp1);
            brd_diff_dimm_rtw = COM_MAX(tmp2, tmp3);

            wtw02 = cdd[1][0][2];
            wtw03 = cdd[1][0][3];
            wtw12 = cdd[1][1][2];
            wtw13 = cdd[1][1][3];
            wtw20 = cdd[1][2][0];
            wtw21 = cdd[1][2][1];
            wtw30 = cdd[1][3][0];
            wtw31 = cdd[1][3][1];

            tmp0 = COM_MAX(wtw02, wtw03);
            tmp1 = COM_MAX(wtw12, wtw13);
            tmp2 = COM_MAX(tmp0, tmp1);
            tmp0 = COM_MAX(wtw20, wtw21);
            tmp1 = COM_MAX(wtw30, wtw31);
            tmp3 = COM_MAX(tmp0, tmp1);
            brd_diff_dimm_wtw = COM_MAX(tmp2, tmp3);

            rtr02 = cdd[2][0][2];
            rtr03 = cdd[2][0][3];
            rtr12 = cdd[2][1][2];
            rtr13 = cdd[2][1][3];
            rtr20 = cdd[2][2][0];
            rtr21 = cdd[2][2][1];
            rtr30 = cdd[2][3][0];
            rtr31 = cdd[2][3][1];

            tmp0 = COM_MAX(rtr02, rtr03);
            tmp1 = COM_MAX(rtr12, rtr13);
            tmp2 = COM_MAX(tmp0, tmp1);

            tmp0 = COM_MAX(rtr20, rtr21);
            tmp1 = COM_MAX(rtr30, rtr31);
            tmp3 = COM_MAX(tmp0, tmp1);
            brd_diff_dimm_rtr = COM_MAX(tmp2, tmp3);
        }

        rtw01 = cdd[0][0][1];
        rtw10 = cdd[0][1][0];
        rtw32 = cdd[0][3][2];
        rtw23 = cdd[0][2][3];

        tmp0 = COM_MAX(rtw01, rtw10);
        tmp1 = COM_MAX(rtw32, rtw23);
        brd_diff_cs_rtw = COM_MAX(tmp0, tmp1);

        wtw01 = cdd[1][0][1];
        wtw10 = cdd[1][1][0];
        wtw32 = cdd[1][3][2];
        wtw23 = cdd[1][2][3];

        tmp0 = COM_MAX(wtw01, wtw10);
        tmp1 = COM_MAX(wtw32, wtw23);
        brd_diff_cs_wtw = COM_MAX(tmp0, tmp1);

        rtr01 = cdd[2][0][1];
        rtr10 = cdd[2][1][0];
        rtr32 = cdd[2][3][2];
        rtr23 = cdd[2][2][3];

        tmp0 = COM_MAX(rtr01, rtr10);
        tmp1 = COM_MAX(rtr32, rtr23);
        brd_diff_cs_rtr = COM_MAX(tmp0, tmp1);
    }

    // wtr uses setting from wtw
    brd_spacing->dimm_wtr = brd_diff_dimm_wtw;
    brd_spacing->dimm_wtw = brd_diff_dimm_wtw;
    brd_spacing->dimm_rtr = brd_diff_dimm_rtr;
    brd_spacing->dimm_rtw = brd_diff_dimm_rtw;

    // wtr uses setting from wtw
    brd_spacing->cs_wtr = brd_diff_cs_wtw;
    brd_spacing->cs_wtw = brd_diff_cs_wtw;
    brd_spacing->cs_rtr = brd_diff_cs_rtr;
    brd_spacing->cs_rtw = brd_diff_cs_rtw;
    brd_spacing->srank_rtw = brd_same_rank_rtw;
}


/*!****************************************************************************
*
* @par Description:
*    This function configures the PHY firmware for the training type.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan         Current channel to perform config on.
*                                  @param
*    fw_type          Training type: 1D, 2D
*                                  @param
*    pstate           frequency selector
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_config_fw(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan,
         uint32_t fw_type, uint8_t pstate, uint32_t mc_vref)
{
    uint64_t mddr_base_addr = mddr_base_addrs[ddr_chan];
    uint16_t val;
    uint16_t mr5_val;

    // let memory controller to take control of CSRs
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_MICROCONTMUXSEL_OFFSET,
        "DDRPHY_APBONLY0_MICROCONTMUXSEL", 0x0);

    // exec PDA Vref update at end of training
    val = (PHY_INPUT_VREF & PHY_INPUT_VREF___M) << PHY_INPUT_VREF___S;
    val |= (PHY_SKIPVREFUPD & PHY_SKIPVREFUPD___M) << PHY_SKIPVREFUPD___S;

    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_0_OFFSET,
        "DDRPHY_UCTL_DMEM_0", val);

    // pstate in [7:0], phyvref in [15:8]
    // VDDq * PhyDqVref[6:0] / 128
    // mc_term in % of Vref * 100 * 100, eg. 72.5% Vref -> mcterm = 7250
    // to get PhyDqVref = (mcterm * 128) / 10000 = (mcterm * 8) / 625
    uint32_t numerator, denominator;
    numerator = mc_vref * 8;
    denominator = 625;

    val = com_ceil_div(numerator, denominator) & PHYDQVREF___M;
    val = val << PHYDQVREF___S;
    val |= (pstate & PHY_PSTATE___M);

    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_2_OFFSET,
        "DDRPHY_UCTL_DMEM_2", val);

    // dmem3: dimm_type, number of dq bits
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_3_OFFSET,
        "DDRPHY_UCTL_DMEM_3", mddr_reg_vals.phy_regs.dmem3_val);

    // dmem4: CS present overall, CS on dimm0
    uint16_t dmem4_val;
    uint8_t cs_present, cs_dimm0, cs_dimm1;

    uint8_t slot0_ranks, slot0_rank_bm;
    uint8_t slot1_ranks, slot1_rank_bm;

    slot0_ranks = mddr_dimm_configs[ddr_chan][0].num_ranks;
    slot1_ranks = mddr_dimm_configs[ddr_chan][1].num_ranks;

    slot0_rank_bm = (0xF >> (4 - slot0_ranks));
    slot1_rank_bm = (0xF >> (4 - slot1_ranks));

    cs_present = ((slot1_rank_bm & 0x3) << 2) | slot0_rank_bm;

    if (slot0_ranks == 4)
    {
        cs_dimm0 = 0xF;
        cs_dimm1 = 0x0;
    }
    else
    {
        cs_dimm0 = cs_present & 0x3;
        cs_dimm1 = cs_present & 0xC;
    }

    dmem4_val = (cs_dimm0 << DMEM_BYTE___S) | cs_present;

    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_4_OFFSET,
        "DDRPHY_UCTL_DMEM_4", dmem4_val);

    // dmem5: CS on dimm1, address mirror
    uint16_t dmem5_val;
    uint8_t mirror = 0;
    uint8_t dimm_slot = 0;
    uint8_t slot0_mirror = 0;

    // mirror on odd ranks
    if (common_cfg.slot_config[0].num_ranks == DDR_RANKS_QUAD_CS_DIMM)
    {
        if (common_cfg.slot_config[0].ca_mirrored)
        {
            slot0_mirror = 1;
        }

        mirror = (slot0_mirror << 1) | (slot0_mirror << 3);    // use slot 0 and then copy from ranks 0 to 3 to ranks 4 to 7
    }
    else    // for dual ranks
    {
        for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            if (common_cfg.slot_config[dimm_slot].ca_mirrored)
            {
                mirror += (2 << (dimm_slot * 2));     // bit 3:0 = CS 3:0    // copy from rank 1 to 5 & copy from rank 3 to 7
            }
        }
    }

    mirror += (mirror << 4);

    dmem5_val = (mirror << DMEM_BYTE___S) | cs_dimm1;

    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_5_OFFSET,
        "DDRPHY_UCTL_DMEM_5", dmem5_val);

    // dmem6: CS test fail indicator, phy config (1T, 2T)
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_6_OFFSET,
        "DDRPHY_UCTL_DMEM_6", mddr_reg_vals.phy_regs.dmem6_val);

    // dmem7: sequence control
    uint8_t debug_msg = DDRPHY_DEBUG_MSG;

    if (fw_type == PHY_1D_TRAINING)
    {
        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_7_OFFSET,
            "DDRPHY_UCTL_DMEM_7", TRAINING_1D_STEPS);
    }
    else if (fw_type == PHY_2D_TRAINING)
    {
        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_7_OFFSET,
            "DDRPHY_UCTL_DMEM_7", TRAINING_2D_STEPS);
        debug_msg = DDRPHY_DEBUG_2D_MSG;
    }

    // dmem8: vebosity control, Rx 2D training option
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_8_OFFSET,
        "DDRPHY_UCTL_DMEM_8", mddr_reg_vals.phy_regs.dmem8_val | debug_msg);

    // dmem9: Tx 2D training option, share 2D Vref result flag
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_9_OFFSET,
        "DDRPHY_UCTL_DMEM_9", mddr_reg_vals.phy_regs.dmem9_val);

    // dmem10: delay weight 2D, voltage weight 2D
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_10_OFFSET,
        "DDRPHY_UCTL_DMEM_10", mddr_reg_vals.phy_regs.dmem10_val);

    // dmem11: MT/s for current pstate
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_11_OFFSET,
        "DDRPHY_UCTL_DMEM_11", ddr_rate);

    // dmem14:
    // Step back for read enable (RxEnStepBack)
    // crosstalkOffset
    uint16_t dmem14_val;

    // normally 1tck preamble = 32, 2tck preamble = 64
    uint8_t RxEnStepBack = (26 & 0xFF);

    int8_t crosstalkOffset = (0 & 0xFF);

    dmem14_val =  (crosstalkOffset << 8)| RxEnStepBack;
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_14_OFFSET,
        "DDRPHY_UCTL_DMEM_14", dmem14_val);

    // dmem15: Margin added to passing trained DFI max read latency
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_15_OFFSET,
        "DDRPHY_UCTL_DMEM_15", mddr_reg_vals.phy_regs.dmem15_val);

    if (fw_type == PHY_1D_TRAINING)
    {
        // dmem43: Workarounds for DBI and WL
        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_43_OFFSET,
                     "DDRPHY_UCTL_DMEM_43", (PHY_WORKAROUND_DBI | PHY_WORKAROUND_WL));
    }

    // dmem40-43: Registers only for 2D training
    if (fw_type == PHY_2D_TRAINING)
    {

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_40_OFFSET,
                     "DDRPHY_UCTL_DMEM_40", mddr_reg_vals.phy_regs.dmem40_val);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_41_OFFSET,
                     "DDRPHY_UCTL_DMEM_41", mddr_reg_vals.phy_regs.dmem41_val);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_42_OFFSET,
                     "DDRPHY_UCTL_DMEM_42", mddr_reg_vals.phy_regs.dmem42_val);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_43_OFFSET,
                     "DDRPHY_UCTL_DMEM_43", mddr_reg_vals.phy_regs.dmem43_val);
    }

    // dmem44-50: load mode registers
    if ((fw_type == PHY_1D_TRAINING) || (fw_type == PHY_2D_TRAINING))
    {
        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_44_OFFSET,
                "DDRPHY_UCTL_DMEM_44",
                mddr_reg_vals.mode_regs[ddr_chan][0].mr0_data);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_45_OFFSET,
                "DDRPHY_UCTL_DMEM_45",
                mddr_reg_vals.mode_regs[ddr_chan][0].mr1_data);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_46_OFFSET,
                "DDRPHY_UCTL_DMEM_46",
                mddr_reg_vals.mode_regs[ddr_chan][0].mr2_data);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_47_OFFSET,
                "DDRPHY_UCTL_DMEM_47",
                mddr_reg_vals.mode_regs[ddr_chan][0].mr3_data);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_48_OFFSET,
                "DDRPHY_UCTL_DMEM_48",
                mddr_reg_vals.mode_regs[ddr_chan][0].mr4_data);

        mr5_val = mddr_reg_vals.mode_regs[ddr_chan][0].mr5_data;

        // Disable parity latency during 1D training
        if (fw_type == PHY_1D_TRAINING)
        {
            mr5_val &= 0xFFF8;
        }

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_49_OFFSET,
                "DDRPHY_UCTL_DMEM_49", mr5_val);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_50_OFFSET,
                "DDRPHY_UCTL_DMEM_50",
                mddr_reg_vals.mode_regs[ddr_chan][0].mr6_data);
    }

    // dmem60-62: load ODTs, should depend on channel
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_60_OFFSET,
        "DDRPHY_UCTL_DMEM_60",
        mddr_reg_vals.phy_regs.odt_dmem_6x[ddr_chan][0]);

    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_61_OFFSET,
        "DDRPHY_UCTL_DMEM_61",
        mddr_reg_vals.phy_regs.odt_dmem_6x[ddr_chan][1]);

    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_62_OFFSET,
        "DDRPHY_UCTL_DMEM_62",
        mddr_reg_vals.phy_regs.odt_dmem_6x[ddr_chan][2]);

    mddr_phy_set_rcws_dbs(ddr_chan);

    uint16_t alt_cas_l_val=0;
    uint16_t alt_wcas_l_val=0;
    uint16_t cl_adj, mr0_cl;

    if (ddr_rate < 2132)
    {
        cl_adj = latencies.cl - 2;
    }
    else
    {
        cl_adj = latencies.cl - 3;
    }

    if (cl_adj <= 9)
    {
        mr0_cl = 0x0;
    }
    else
    {
        switch (cl_adj) {

            case 10 :
                mr0_cl = 0x4;
                break;
            case 11 :
                mr0_cl = 0x10;
                break;
            case 12 :
                mr0_cl = 0x14;
                break;
            case 13 :
                mr0_cl = 0x20;
                break;
            case 14 :
                mr0_cl = 0x24;
                break;
            case 15 :
                mr0_cl = 0x30;
                break;
            case 16 :
                mr0_cl = 0x34;
                break;
            case 17 :
                mr0_cl = 0x64;
                break;
            case 18 :
                mr0_cl = 0x40;
                break;
            case 19 :
                mr0_cl = 0x70;
                break;
            case 20 :
                mr0_cl = 0x44;
                break;
            case 21 :
                mr0_cl = 0x74;
                break;
            case 22 :
                mr0_cl = 0x50;
                break;
            case 23 :
                mr0_cl = 0x60;
                break;
            case 24 :
                mr0_cl = 0x54;
                break;
            case 25 :
                mr0_cl = 0x1000;
                break;
            case 26 :
                mr0_cl = 0x1004;
                break;
            case 27 :
                mr0_cl = 0x1010;
                break;
            case 28 :
                mr0_cl = 0x1014;
                break;
            case 29 :
                mr0_cl = 0x1020;
                break;
            case 30 :
                mr0_cl = 0x1024;
                break;
            case 31 :
                mr0_cl = 0x1030;
                break;
            default :
                mr0_cl = 0x1034;
        }
    }

    alt_cas_l_val = mr0_cl;

    // if valid read DBI, enable alt_cas_l
    if ((common_cfg.sdram_width == SPD_SDRAM_WIDTH_X8) &&
        ((mddr_settings_ptr->dbi_mode == DDR_DBI_READ) ||
        (mddr_settings_ptr->dbi_mode == DDR_DBI_READ_WRITE)))
    {
        alt_cas_l_val |= 0x1;
    }

    // if 2tCK WR preamble
    if ((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
        (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
    {
        uint16_t cwl_adj;
        uint16_t mr2_cwl = 0;

        if (latencies.cwl >= 9)             // cwl with 2tCK WR added is valid
        {
            cwl_adj = latencies.cwl - 2;    // remove adder for 2tCK WR preamble

            if (cwl_adj == 12)
            {
                mr2_cwl = 0x3;
            }
            else if (cwl_adj == 14)
            {
                mr2_cwl = 0x4;
            }
            else if (cwl_adj == 16)
            {
                mr2_cwl = 0x5;
            }

            // valid adjusted cwl, then enable
            if (mr2_cwl != 0)
            {
                alt_wcas_l_val = 0x1 | (mr2_cwl << 3);
            }
        }
    }
    else
    {
        alt_wcas_l_val = latencies.mc_mr2_cwl << 3;
    }

    // ALT_CAS_L for rd_dbi
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_504_OFFSET,
        "DDRPHY_UCTL_DMEM_504", alt_cas_l_val);

    // ALT_WCAS_L for 2tck
    mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_505_OFFSET,
        "DDRPHY_UCTL_DMEM_505", alt_wcas_l_val);
}


/*!****************************************************************************
*
* @par Description:
*    This function sets the dmem region for the register control words found
*    in RDIMM and LRDIMMs.
*
*                                  @param
*    ddr_chan         Current channel to perform config on.
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_set_rcws_dbs(uint8_t ddr_chan)
{
    uint64_t mddr_base_addr = mddr_base_addrs[ddr_chan];

    uint16_t rc01_00, rc03_02, rc05_04, rc07_06;
    uint16_t rc09_08, rc0b_0a, rc0d_0c, rc0f_0e;
    uint16_t rc2x_1x, rc4x_3x, rc6x_5x, rc8x_7x;
    uint16_t rcax_9x, f1rc00_f0rcbx;

    uint64_t rcw0f_00, rcw7x_0x, f1rc00_f0rcbx_8x;

    // dmem104-117: load register control words (RCW)
    if ((common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM) ||
            (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM))
    {
        rcw0f_00 = mddr_reg_vals.rcw_regs[ddr_chan][0].rcw0f_00;
        rcw7x_0x = mddr_reg_vals.rcw_regs[ddr_chan][0].rcw7x_0x;
        f1rc00_f0rcbx_8x = mddr_reg_vals.rcw_regs[ddr_chan][0].f1rc00_f0rcbx_8x;

        rc01_00 = (((rcw0f_00 >> (4 * 1)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 0)) & 0xF);
        rc03_02 = (((rcw0f_00 >> (4 * 3)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 2)) & 0xF);
        rc05_04 = (((rcw0f_00 >> (4 * 5)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 4)) & 0xF);
        rc07_06 = (((rcw0f_00 >> (4 * 7)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 6)) & 0xF);
        rc09_08 = (((rcw0f_00 >> (4 * 9)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 8)) & 0xF);

        // Always enable A17 during training
        //rc09_08 = rc09_08 & 0xFFF7;

        rc0b_0a = (((rcw0f_00 >> (4 * 11)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 10)) & 0xF);
        rc0d_0c = (((rcw0f_00 >> (4 * 13)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 12)) & 0xF);
        rc0f_0e = (((rcw0f_00 >> (4 * 15)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 14)) & 0xF);

        rc2x_1x = (((rcw7x_0x >> (8 * 2)) & 0xFF) << 8) |
            ((rcw7x_0x >> (8 * 1)) & 0xFF);
        rc4x_3x = (((rcw7x_0x >> (8 * 4)) & 0xFF) << 8) |
            ((rcw7x_0x >> (8 * 3)) & 0xFF);
        rc6x_5x = (((rcw7x_0x >> (8 * 6)) & 0xFF) << 8) |
            ((rcw7x_0x >> (8 * 5)) & 0xFF);
        rc8x_7x = (((f1rc00_f0rcbx_8x >> (8 * 0)) & 0xFF) << 8) |
            ((rcw7x_0x >> (8 * 7)) & 0xFF);
        rcax_9x = (((f1rc00_f0rcbx_8x >> (8 * 2)) & 0xFF) << 8) |
            ((f1rc00_f0rcbx_8x >> (8 * 1)) & 0xFF);
        f1rc00_f0rcbx = (((f1rc00_f0rcbx_8x >> (8 * 4)) & 0xF) << 8) |
            ((f1rc00_f0rcbx_8x >> (8 * 3)) & 0xFF);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_104_OFFSET,
            "DDRPHY_UCTL_DMEM_104", rc01_00);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_105_OFFSET,
            "DDRPHY_UCTL_DMEM_105", rc03_02);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_106_OFFSET,
            "DDRPHY_UCTL_DMEM_106", rc05_04);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_107_OFFSET,
            "DDRPHY_UCTL_DMEM_107", rc07_06);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_108_OFFSET,
            "DDRPHY_UCTL_DMEM_108", rc09_08);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_109_OFFSET,
            "DDRPHY_UCTL_DMEM_109", rc0b_0a);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_110_OFFSET,
            "DDRPHY_UCTL_DMEM_110", rc0d_0c);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_111_OFFSET,
            "DDRPHY_UCTL_DMEM_111", rc0f_0e);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_112_OFFSET,
            "DDRPHY_UCTL_DMEM_112", rc2x_1x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_113_OFFSET,
            "DDRPHY_UCTL_DMEM_113", rc4x_3x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_114_OFFSET,
            "DDRPHY_UCTL_DMEM_114", rc6x_5x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_115_OFFSET,
            "DDRPHY_UCTL_DMEM_115", rc8x_7x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_116_OFFSET,
            "DDRPHY_UCTL_DMEM_116", rcax_9x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_117_OFFSET,
            "DDRPHY_UCTL_DMEM_117", f1rc00_f0rcbx);

        if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
        {
            uint64_t bc0f_00, f5bc6x_5x_f0bc6x;
            uint16_t bc01_00, bc03_02, bc05_04, bc07_06;
            uint16_t bc09_08, bc0b_0a, bc0d_0c, bc6x_0e, f5bc6x_5x;

            bc0f_00 = mddr_reg_vals.rcw_regs[ddr_chan][0].bc0f_00;
            f5bc6x_5x_f0bc6x = mddr_reg_vals.rcw_regs[ddr_chan][0].f5bc6x_5x_f0bc6x;

            bc01_00 = (((bc0f_00 >> (4 * 1)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 0)) & 0xF);
            bc03_02 = (((bc0f_00 >> (4 * 3)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 2)) & 0xF);
            bc05_04 = (((bc0f_00 >> (4 * 5)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 4)) & 0xF);
            bc07_06 = (((bc0f_00 >> (4 * 7)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 6)) & 0xF);
            bc09_08 = (((bc0f_00 >> (4 * 9)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 8)) & 0xF);
            bc0b_0a = (((bc0f_00 >> (4 * 11)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 10)) & 0xF);
            bc0d_0c = (((bc0f_00 >> (4 * 13)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 12)) & 0xF);
            bc6x_0e = (((f5bc6x_5x_f0bc6x >> (8 * 0)) & 0xFF) << 8) |
                ((bc0f_00 >> (4 * 14)) & 0xF);

            f5bc6x_5x = (((f5bc6x_5x_f0bc6x >> (8 * 2)) & 0xFF) << 8) |
                ((f5bc6x_5x_f0bc6x >> (8 * 1)) & 0xFF);

            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_158_OFFSET,
                "DDRPHY_UCTL_DMEM_158", bc01_00);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_159_OFFSET,
                "DDRPHY_UCTL_DMEM_159", bc03_02);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_160_OFFSET,
                "DDRPHY_UCTL_DMEM_160", bc05_04);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_161_OFFSET,
                "DDRPHY_UCTL_DMEM_161", bc07_06);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_162_OFFSET,
                "DDRPHY_UCTL_DMEM_162", bc09_08);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_163_OFFSET,
                "DDRPHY_UCTL_DMEM_163", bc0b_0a);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_164_OFFSET,
                "DDRPHY_UCTL_DMEM_164", bc0d_0c);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_165_OFFSET,
                "DDRPHY_UCTL_DMEM_165", bc6x_0e);

            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_314_OFFSET,
                "DDRPHY_UCTL_DMEM_314", f5bc6x_5x);
        }
    }

    // if slot 1 is valid
    if (mddr_dimm_configs[ddr_chan][1].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
    {
        rcw0f_00 = mddr_reg_vals.rcw_regs[ddr_chan][1].rcw0f_00;
        rcw7x_0x = mddr_reg_vals.rcw_regs[ddr_chan][1].rcw7x_0x;
        f1rc00_f0rcbx_8x = mddr_reg_vals.rcw_regs[ddr_chan][1].f1rc00_f0rcbx_8x;

        rc01_00 = (((rcw0f_00 >> (4 * 1)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 0)) & 0xF);
        rc03_02 = (((rcw0f_00 >> (4 * 3)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 2)) & 0xF);
        rc05_04 = (((rcw0f_00 >> (4 * 5)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 4)) & 0xF);
        rc07_06 = (((rcw0f_00 >> (4 * 7)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 6)) & 0xF);
        rc09_08 = (((rcw0f_00 >> (4 * 9)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 8)) & 0xF);

        // Always enable A17 during training
        //rc09_08 = rc09_08 & 0xFFF7;

        rc0b_0a = (((rcw0f_00 >> (4 * 11)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 10)) & 0xF);
        rc0d_0c = (((rcw0f_00 >> (4 * 13)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 12)) & 0xF);
        rc0f_0e = (((rcw0f_00 >> (4 * 15)) & 0xF) << 8) |
            ((rcw0f_00 >> (4 * 14)) & 0xF);

        rc2x_1x = (((rcw7x_0x >> (8 * 2)) & 0xFF) << 8) |
            ((rcw7x_0x >> (8 * 1)) & 0xFF);
        rc4x_3x = (((rcw7x_0x >> (8 * 4)) & 0xFF) << 8) |
            ((rcw7x_0x >> (8 * 3)) & 0xFF);
        rc6x_5x = (((rcw7x_0x >> (8 * 6)) & 0xFF) << 8) |
            ((rcw7x_0x >> (8 * 5)) & 0xFF);
        rc8x_7x = (((f1rc00_f0rcbx_8x >> (8 * 0)) & 0xFF) << 8) |
            ((rcw7x_0x >> (8 * 7)) & 0xFF);
        rcax_9x = (((f1rc00_f0rcbx_8x >> (8 * 2)) & 0xFF) << 8) |
            ((f1rc00_f0rcbx_8x >> (8 * 1)) & 0xFF);
        f1rc00_f0rcbx = (((f1rc00_f0rcbx_8x >> (8 * 4)) & 0xF) << 8) |
            ((f1rc00_f0rcbx_8x >> (8 * 3)) & 0xFF);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_131_OFFSET,
            "DDRPHY_UCTL_DMEM_131", rc01_00);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_132_OFFSET,
            "DDRPHY_UCTL_DMEM_132", rc03_02);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_133_OFFSET,
            "DDRPHY_UCTL_DMEM_133", rc05_04);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_134_OFFSET,
            "DDRPHY_UCTL_DMEM_134", rc07_06);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_135_OFFSET,
            "DDRPHY_UCTL_DMEM_135", rc09_08);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_136_OFFSET,
            "DDRPHY_UCTL_DMEM_136", rc0b_0a);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_137_OFFSET,
            "DDRPHY_UCTL_DMEM_137", rc0d_0c);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_138_OFFSET,
            "DDRPHY_UCTL_DMEM_138", rc0f_0e);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_139_OFFSET,
            "DDRPHY_UCTL_DMEM_139", rc2x_1x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_140_OFFSET,
            "DDRPHY_UCTL_DMEM_140", rc4x_3x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_141_OFFSET,
            "DDRPHY_UCTL_DMEM_141", rc6x_5x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_142_OFFSET,
            "DDRPHY_UCTL_DMEM_142", rc8x_7x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_143_OFFSET,
            "DDRPHY_UCTL_DMEM_143", rcax_9x);

        mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_144_OFFSET,
            "DDRPHY_UCTL_DMEM_144", f1rc00_f0rcbx);

        if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
        {
            uint64_t bc0f_00, f5bc6x_5x_f0bc6x;
            uint16_t bc01_00, bc03_02, bc05_04, bc07_06;
            uint16_t bc09_08, bc0b_0a, bc0d_0c, bc6x_0e, f5bc6x_5x;

            bc0f_00 = mddr_reg_vals.rcw_regs[ddr_chan][1].bc0f_00;
            f5bc6x_5x_f0bc6x = mddr_reg_vals.rcw_regs[ddr_chan][1].f5bc6x_5x_f0bc6x;

            bc01_00 = (((bc0f_00 >> (4 * 1)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 0)) & 0xF);
            bc03_02 = (((bc0f_00 >> (4 * 3)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 2)) & 0xF);
            bc05_04 = (((bc0f_00 >> (4 * 5)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 4)) & 0xF);
            bc07_06 = (((bc0f_00 >> (4 * 7)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 6)) & 0xF);
            bc09_08 = (((bc0f_00 >> (4 * 9)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 8)) & 0xF);
            bc0b_0a = (((bc0f_00 >> (4 * 11)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 10)) & 0xF);
            bc0d_0c = (((bc0f_00 >> (4 * 13)) & 0xF) << 8) |
                ((bc0f_00 >> (4 * 12)) & 0xF);
            bc6x_0e = (((f5bc6x_5x_f0bc6x >> (8 * 0)) & 0xFF) << 8) |
                ((bc0f_00 >> (4 * 14)) & 0xF);

            f5bc6x_5x = (((f5bc6x_5x_f0bc6x >> (8 * 2)) & 0xFF) << 8) |
                ((f5bc6x_5x_f0bc6x >> (8 * 1)) & 0xFF);

            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_331_OFFSET,
                "DDRPHY_UCTL_DMEM_331", bc01_00);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_332_OFFSET,
                "DDRPHY_UCTL_DMEM_332", bc03_02);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_333_OFFSET,
                "DDRPHY_UCTL_DMEM_333", bc05_04);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_334_OFFSET,
                "DDRPHY_UCTL_DMEM_334", bc07_06);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_335_OFFSET,
                "DDRPHY_UCTL_DMEM_335", bc09_08);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_336_OFFSET,
                "DDRPHY_UCTL_DMEM_336", bc0b_0a);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_337_OFFSET,
                "DDRPHY_UCTL_DMEM_337", bc0d_0c);
            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_338_OFFSET,
                "DDRPHY_UCTL_DMEM_338", bc6x_0e);

            mddr_set_reg(mddr_base_addr + DDRPHY_UCTL_DMEM_487_OFFSET,
                "DDRPHY_UCTL_DMEM_487", f5bc6x_5x);
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function returns the control back to the memory controller after
*    training has run.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_post_training(uint64_t mddr_base_addr)
{
    uint16_t seq_override_val;
    uint32_t ddr_manual_val;
    uint32_t ddr_dfi_cmd0_val;
    uint32_t ddr_dfi_status2_val;
    uint32_t dfi_init_complete = 0;
    uint16_t poll_count =0;
    uint32_t num_ns;

    seq_override_val = 0x1 << SEQ_OR_SELECTDFIFREQTOGPRMUX___S;

    // set to mission mode
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_SEQUENCEROVERRIDE_OFFSET,
            "DDRPHY_APBONLY0_SEQUENCEROVERRIDE", seq_override_val);

    // clear disable flags
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG0_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG0", 0x0);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG1_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG1", 0x0);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG2_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG2", 0x0);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG3_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG3", 0x0);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG4_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG4", 0x0);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG6_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG6", 0x0);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG7_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG7", 0x0);

    // read PUB REV due to PHY artifact (do not move)
    mddr_get_reg(mddr_base_addr + DDRPHY_DRTUB0_PUBREV_OFFSET,
        "DDRPHY_DRTUB0_PUBREV");

    // disable PHY microcontroller clocks
    mddr_set_reg(mddr_base_addr + DDRPHY_DRTUB0_UCCLKHCLKENABLES_OFFSET,
        "DDRPHY_DRTUB0_UCCLKHCLKENABLES", 0x0);

    // get ddr_manual register
    ddr_manual_val = mddr_get_reg(
        mddr_base_addr + MDDR_DDR_MANUAL_OFFSET,
        "DDR_MANUAL");

    // remove blocking DFI control signals from PHY to memory controller
    // fence_ddr_phy = 0
    ddr_manual_val &= (~(0x1 << DDR_MANUAL_FENCE_DDR_PHY___S));
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OFFSET,
        "DDR_MANUAL", ddr_manual_val);

    // fence_phy_in_reset = 0
    ddr_manual_val &= (~(0x1 << DDR_MANUAL_FENCE_PHY_IN_RESET___S));
    mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OFFSET,
        "DDR_MANUAL", ddr_manual_val);

    // get ddr_dfi_cmd_0 register
    ddr_dfi_cmd0_val = mddr_get_reg(
        mddr_base_addr + MDDR_DDR_DFI_CMD_0_OFFSET,
        "DDR_DFI_CMD_0");

    // assert dfi_init_start to bring PHY out of low-power state
    ddr_dfi_cmd0_val |= (0x1 << DFI_CMD0_DFI_INIT_START___S);

    mddr_set_reg(mddr_base_addr + MDDR_DDR_DFI_CMD_0_OFFSET,
        "DDR_DFI_CMD_0", ddr_dfi_cmd0_val);

    num_ns = com_ceil_div(DDR_CLKS_SEQ_DELAY * NANO_SEC_PER_MICRO_SEC, mem_freq_mhz);

    // poll till dfi_init_complete
    while ((dfi_init_complete == 0) && (poll_count < MAX_DFI_POLL_LOOPS))
    {
        mddr_mc_wait_ns(mddr_base_addr, num_ns);

        ddr_dfi_status2_val = mddr_get_reg(
            mddr_base_addr + MDDR_DDR_DFI_STATUS_2_OFFSET,
            "DDR_DFI_STATUS_2");

        dfi_init_complete = ((
            ddr_dfi_status2_val >> DFI_STATUS2_DFI_INIT_COMPLETE___S) & 0x1);
        poll_count += 1;
    }

    if ((poll_count == MAX_DFI_POLL_LOOPS) && (dfi_init_complete == 0))
    {
        monaco_log(LOW,
        "       DDR-POST-TRAIN:  MDDR DFI init did not complete in time...\n");
    }

    // deassert dfi_init_start to complete handshake
    ddr_dfi_cmd0_val &= (~(0x1 << DFI_CMD0_DFI_INIT_START___S));

    mddr_set_reg(mddr_base_addr + MDDR_DDR_DFI_CMD_0_OFFSET,
            "DDR_DFI_CMD_0", ddr_dfi_cmd0_val);
}


/*!****************************************************************************
*
* @par Description:
*    This function configures the PHY sequencer for p_state, or low power.
*    Polls DFIINITCOMPLETESHADOW for done.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*                                  @param
*    pstate           P-state for various frequencies
*                     Set to 0xF for low power state.
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_setup_sequencer(uint64_t mddr_base_addr, uint8_t pstate)
{
    uint32_t seq_override_val = 0;
    uint32_t num_ns;

    // low-power = 0xF = p_state, else training
    uint8_t forceseq0bstartvector = pstate;

    seq_override_val =
    (
        (SELECTDFIFREQTOGPRMUX & BITMASK)
        << SEQ_OR_SELECTDFIFREQTOGPRMUX___S
    );

    seq_override_val |=
    (
        (DISABLETERMINATEFLAG & BITMASK)
        << SEQ_OR_DISABLETERMINATEFLAG___S
    );

    seq_override_val |= (
            (BLOCKSEQ0BACK & BITMASK) << SEQ_OR_BLOCKSEQ0BACK___S);

    seq_override_val |= (
            (BLOCKSEQ0BREQUESTS & BITMASK) << SEQ_OR_BLOCKSEQ0BREQUESTS___S);

    seq_override_val |= (
            (FORCESEQ0BSTOP & BITMASK) << SEQ_OR_FORCESEQ0BSTOP___S);

    seq_override_val |= (
            (FORCESEQ0BSTART & BITMASK) << SEQ_OR_FORCESEQ0BSTART___S);

    seq_override_val |=
    (
        (forceseq0bstartvector & SEQ_OR_FORCESEQ0BSTARTVECTOR___M)
        << SEQ_OR_FORCESEQ0BSTARTVECTOR___S
    );

    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_SEQUENCEROVERRIDE_OFFSET,
            "DDRPHY_APBONLY0_SEQUENCEROVERRIDE", seq_override_val);

    // poll for DFI init complete
    uint32_t dfi_init_complete = 0;
    uint16_t poll_count = 0;

    // wait 128 DFI clocks (256 DDR clocks)
    num_ns = com_ceil_div(DDR_CLKS_SEQ_DELAY * NANO_SEC_PER_MICRO_SEC, mem_freq_mhz);

    while ((dfi_init_complete == 0) && (poll_count < MAX_DFI_POLL_LOOPS))
    {
        mddr_mc_wait_ns(mddr_base_addr, num_ns);

        dfi_init_complete = mddr_get_reg (
                mddr_base_addr + DDRPHY_APBONLY0_DFIINITCOMPLETESHADOW_OFFSET,
                "DDRPHY_APBONLY0_DFIINITCOMPLETESHADOW"
        );

        poll_count = poll_count + 1;
    }

    if ((poll_count == MAX_DFI_POLL_LOOPS) && (dfi_init_complete == 0))
    {
        monaco_log(CRITICAL,
            "       DDR-TRAIN:  PHY DFI init did not complete in time...\n");
    }

    // stop sequencer
    uint32_t stop_seq_override_val = seq_override_val;

    stop_seq_override_val &= (~(BITMASK << SEQ_OR_FORCESEQ0BSTART___S));

    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_SEQUENCEROVERRIDE_OFFSET,
        "DDRPHY_APBONLY0_SEQUENCEROVERRIDE", stop_seq_override_val);
}


/*!****************************************************************************
*
* @par Description:
*    Get message ID from FW training.  Will process streaming messages via
*    mddr_phy_get_mail function.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*
* @return
*    msg_id           Message ID status
*
* @author
*    mwuu
*
******************************************************************************/
uint32_t mddr_phy_get_msg(uint64_t mddr_base_addr)
{
    uint32_t mail = mddr_phy_get_mail(mddr_base_addr);

    uint8_t msg_id = mail & MAJORID_MSG___M;

    if (msg_id == STREAM_MSG)
    {
        uint32_t stream_msg = mddr_phy_get_mail(mddr_base_addr);

        uint16_t num_args = stream_msg & STREAM_MSG_ARGS___M;

        uint16_t str_id =
                ((stream_msg >> STREAM_MSG_STR___S) & STREAM_MSG_STR___M);

        monaco_log(LOW, "DDR-TRAIN-STREAM:  0x%08x : id=0x%04x\n",
                stream_msg, str_id);

        uint16_t i = 0;
        uint16_t num_print_args;
        int32_t data;
        int32_t argv[STREAM_MAX_ARGS];

        while (i < num_args)
        {
            data = mddr_phy_get_mail(mddr_base_addr);

            if (i < STREAM_MAX_ARGS)    // store only if it fits in array
            {
                argv[i] = data;
            }
            else    // larger than array size, print it now
            {
                // data could be negative, print value
                monaco_log(LOW, "[%d] = 0x%08x (%d)\n", i, data, data);
            }

            i++;
        }

        if (num_args > STREAM_MAX_ARGS)
        {
            num_print_args = STREAM_MAX_ARGS;
        }
        else
        {
            num_print_args = num_args;
        }

        // print what is in array
        i = 0;
        while (i < num_print_args)
        {
            // data could be negative, print value
            monaco_log(LOW, "[%d] = 0x%08x (%d)\n", i, argv[i], argv[i]);
            i++;
        }

    }
    else    // major message
    {
        monaco_log(LOW, "DDR-TRAIN:  %s\n", major_str[(msg_id & 0xF)]);
    }

    return msg_id;
}


/*!****************************************************************************
*
* @par Description:
*    Get mailbox message for FW training.  Processes streaming messages.
*
*                                  @param
*    mddr_base_addr   The base address of the configuration registers for
*                     the memory controller.
*
* @return
*    msg_id           Message ID status
*
* @author
*    mwuu
*
******************************************************************************/
uint32_t mddr_phy_get_mail(uint64_t mddr_base_addr)
{
    uint32_t msg_id = 0xFF;
    uint32_t i = 0;
    uint32_t uct_shadow_val = 0x1;

    while (((uct_shadow_val & 0x1) != 0) && (i < PHY_MAX_READS))
    {
        uct_shadow_val = mddr_get_reg
        (
            mddr_base_addr + DDRPHY_APBONLY0_UCTSHADOWREGS_OFFSET,
            "DDRPHY_APBONLY0_UCTSHADOWREGS"
        );

        // wait since we're going to timeout
        // if taking too long (1ms * PHY_MAX_READS)
        mddr_mc_wait_us(mddr_base_addr, 1000);
        i++;
    }

    if (((uct_shadow_val & 0x1) != 0) && (i == PHY_MAX_READS))
    {
        monaco_log(CRITICAL, "DDR-TRAIN:  Warning timed out polling for mailbox\n");
    }
    else    // msg available
    {
        msg_id = mddr_get_reg
        (
            mddr_base_addr + DDRPHY_APBONLY0_UCTWRITEONLYSHADOW_OFFSET,
            "DDRPHY_APBONLY0_UCTWRITEONLYSHADOW"
        );

        uint32_t msb_msg = mddr_get_reg
        (
            mddr_base_addr + DDRPHY_APBONLY0_UCTDATWRITEONLYSHADOW_OFFSET,
            "DDRPHY_APBONLY0_UCTDATWRITEONLYSHADOW"
        );

        msg_id |= ((msb_msg & PHY_MSB_MSG___M) << PHY_MSB_MSG___S);

        // ack message
        mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_DCTWRITEPROT_OFFSET,
                "DDRPHY_APBONLY0_DCTWRITEPROT", PHY_ACK_MSG);

        i = 0;
        // confirm msg ack'd
        while (((uct_shadow_val & 0x1) == 0) && (i < PHY_MAX_READS))
        {
            uct_shadow_val = mddr_get_reg
            (
                mddr_base_addr + DDRPHY_APBONLY0_UCTSHADOWREGS_OFFSET,
                "DDRPHY_APBONLY0_UCTSHADOWREGS"
            );

            i++;
        }

        if (((uct_shadow_val & 0x1) == 0) && (i == PHY_MAX_READS))
        {
            monaco_log(CRITICAL,
                    "DDR-TRAIN:  Warning timed out on ACK confirmation\n");
        }

        // reset ack
        mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_DCTWRITEPROT_OFFSET,
                "DDRPHY_APBONLY0_DCTWRITEPROT", PHY_ACK_RESET);
    }

    return msg_id;
}


/*!****************************************************************************
*
* @par Description:
*    This function read and cache the Vref settings determined from 2D training.
*
*                                  @param
*    ddr_chan         Current channel to perform config on.
*                                  @param
*    valid_cs_bm        Valid CS bits in current ddr_chan
*
* @return
*    none
*
* @author
*    jihyunl
*
******************************************************************************/
void mddr_phy_retrieve_dram_vref(uint8_t ddr_chan, uint8_t valid_cs_bm)
{
    uint8_t rank = 0;
    uint8_t v_ranks = valid_cs_bm;
    uint8_t rbase, idx, shift, byte;
    uint16_t val;
    char reg_name[PHY_MAX_REG_NAME_LENGTH];
    uint64_t reg_addr, mddr_base_addr;

    // DRAM Vref settings in DMEM 64-103; even=0,2,4,6,8; odd=1,3,5,7,9
    // DMEM_64 to  73, for CS0 [15:8]=odd, [7:0]=even nibbles
    // DMEM_74 to  83, for CS1 [15:8]=odd, [7:0]=even nibbles
    // DMEM_84 to  93, for CS2 [15:8]=odd, [7:0]=even nibbles
    // DMEM_94 to 103, for CS3 [15:8]=odd, [7:0]=even nibbles

    memset(&mddr_dram_vref_trained[ddr_chan], 0x00, sizeof(uint32_t)* 4*5);
    mddr_base_addr = mddr_base_addrs[ddr_chan];

    mddr_dram_vref_trained[ddr_chan][0][2] = PHY_VREF_VAL;
    mddr_dram_vref_trained[ddr_chan][1][2] = PHY_VREF_VAL;
    mddr_dram_vref_trained[ddr_chan][2][2] = PHY_VREF_VAL;
    mddr_dram_vref_trained[ddr_chan][3][2] = PHY_VREF_VAL;

    while (v_ranks > 0)
    {
        if ((v_ranks & 0x1) > 0)
        {
            rbase = (10 * rank) + PHY_VREF_CS0_DMEM;
            reg_addr = mddr_base_addr + DDRPHY_UCTL_DMEM_64_OFFSET +
                (4 * 10 * rank);

            for (byte = 0; byte < 9; byte++)
            {
                snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
                    "DDRPHY_UCTL_DMEM_%d", (rbase + byte));

                // get PHY even/odd value for current rank
                val = mddr_get_reg((reg_addr + (4 * byte)), reg_name);
                monaco_log(INFORMATIONAL, "--- MDDR_%-25s (0x%08X) = 0x%08X\n",
                         reg_name, reg_addr+ (4 * byte), val);

                idx = byte / 4;             // each register holds 4 bytes
                shift = (byte % 4) * 8;     // vref val on multiples of 8

                // store x8 vref value
                mddr_dram_vref_trained[ddr_chan][rank][idx] |=
                    ((val & PHY_VREF_MASK) << shift);

                // store x4 upper vref value
                // byte_8_x4 is in idx 2, starting at bit 8
                if (idx != 2)
                {
                    idx += 3;
                }
                else
                {
                    shift = 8;
                }

                mddr_dram_vref_trained[ddr_chan][rank][idx] |= (
                    ((val >> 8) & PHY_VREF_MASK) << shift
                );
            }
        }
        rank += 1;
        v_ranks = v_ranks >> 1;
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function returns avrage Vref value from trained Vref per nibble.
*
*                                  @param
*    ddr_chan         Current channel to perform config on.
*                                  @param
*    cs               Valid CS bits in current ddr_chan
*
* @return
*    averaged Vref for specific channel and cs
*
* @author
*    jihyunl
*
******************************************************************************/
uint16_t mddr_phy_get_average_dram_vref(uint8_t ddr_chan, uint8_t cs)
{

    uint16_t vref_val;
    uint16_t avrg_vref;
    uint8_t index, byte, num_bytes;

    vref_val =0;

    for (index= 0; index < 5; index++)
    {
        if(index==2)
            num_bytes=2;
        else
            num_bytes=4;

        for (byte= 0; byte < num_bytes; byte++)
        {
            vref_val += (mddr_dram_vref_trained[ddr_chan][cs][index]>>(byte*8))&PHY_VREF_MASK;
            // Currently range bit is not populated in training
//          rng_val = (mddr_dram_vref_trained[ddr_chan][cs][index]>>(byte*8))&0x40;
        }
    }

    avrg_vref = vref_val/18;
    monaco_log(INFORMATIONAL, "*+++ Average Vref for ch%d cs%d = 0x%x\n", hddrss[ddr_chan], cs, avrg_vref);

    return avrg_vref;
}

//==============================================================================
