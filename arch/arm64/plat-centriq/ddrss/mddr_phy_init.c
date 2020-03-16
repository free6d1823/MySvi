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
* <I>This software may be subject to U.S. and international export, re-export,
* or transfer ("export") laws.  Diversion contrary to U.S. and international
* law is strictly prohibited.</I>
*
* @file mddr_phy_init.c
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
#include <target/ddr.h>

/******************************************************************************
* Defined Constants
******************************************************************************/
#define NUM_PS_IN_HALF_US           500000 // number of ps in 0.5us
#define NUM_PS_IN_ONE_US           1000000 // number of ps in 1us
#define NUM_PS_IN_10_US           10000000 // number of ps in 10us
#define NUM_PS_IN_25_US           25000000 // number of ps in 25us
#define NUM_SEQ0BDLYS                    4 // number of delay registers
#define MAX_NUM_BYTES                    9 // max number of bytes

#define DFI_RATIO                        2 // DFI ratio to DDR clock
#define PHY_POLL_TIMEOUT_MS             10 // timeout in mS

#define PHY_DISABLE_UPDATE_CNTR        0x0

#define PHY_PLLTESTMODE_VAL          0x124 // PHY PLL test mode
#define PHY_CTRL_DRAM_RESET              1 // PHY controls DRAM reset_n
#define PHY_MEMALERTCONTROL         0x7840 // ALERT_N pullup impedance set to 120 ohms
#define PHY_CALMISC2_VAL            0x2007 // num votes=7, round disable=1
#define PHY_START_IMP_CAL             0x11 // kicks off impedance cal
#define PHY_STOP_IMP_CAL               0x1 // stops impedance cal

#define PHY_DQ_BITS___S                  8 // dq bit shift for dmem3
#define PHY_DDR4_RDIMM_TYPE            0x4 // PHY RDIMM type
#define PHY_DDR4_LRDIMM_TYPE           0x5 // PHY LRDIMM type
#define PHY_ECC_BITS                     8 // PHY ECC bits
#define PHY_DATA_BITS                   64 // PHY DATA bits

#define DMEM_NIBBLE___S                  8 // nibble shift
#define DMEM8_RX2D_OPT___M            0xFF // mask for RX 2D option
#define DMEM9_TX2D_OPT___M            0xFF // mask for TX 2D option
#define DELAY_WEIGHT___M              0xFF // mask for delay weight
#define VOLT_WEIGHT___M               0xFF // mask for voltage weight
#define SHARE_2D_VREF_RESULT           0xF // use per lane Vref vs global
#define DFI_MRL_MARGIN                 0x1 // DFI clocks, max read latency

#define DDRPHY_VREF2D_OPT           0x0100 // Tx_2D_opt[15:8],Rx_2D_opt[7:0]
                                           // bit0=DFE enable, bit8=FFE enable
#define DDRPHY_WEIGHT_2D            0x0104 // [7:0] = delay, [15:8] = voltage


#define DDRPHY_DMEM43___M           0xFFF0
#define DDRPHY_DMEM43_XCNT___M      0xF    // mask for XCNT


#define ODT_BITS                         4
#define PHY_ODD_ODT_RD___S              12
#define PHY_ODD_ODT_WR___S               8
#define PHY_EVEN_ODT_RD___S              4
#define PHY_ODT___M                    0xF

#define MAX_NUM_PHY_IMP_VALS                  18
#define MAX_PHY_IMP_VAL                      480
#define MIN_PHY_IMP_VAL                       28
#define MAX_NUM_PHY_ODT_VALS                  18
#define MAX_PHY_ODT_VAL                      480
#define MIN_PHY_ODT_VAL                       28

#define PROCODTALWAYSON                        1
#define PROCODTALWAYSOFF                       0

#define PROCODTTIMECTL_STARTDELAYDQS___S      12
#define PROCODTTIMECTL_STARTDELAYDQS___M     0xF
#define PROCODTTIMECTL_TAILWIDTHDQS___S        4
#define PROCODTTIMECTL_TAILWIDTHDQS___M      0xF

#define PROCODTTIMECTL_STARTDELAYDQS         0x0    // from AK, prev=1
#define PROCODTTIMECTL_TAILWIDTHDQS          0x3    // from AK, prev=2

#define TXEQMODE_OFF                         0x0
#define TXEQMODE_PREV                        0x1
#define TXEQMODE_NEXT                        0x2
#define TXEQUALIZATIONMODE_TXEQMODE___M      0x3

#define TXEQIMPEDANCE_DRVSTRENFSDQN___S        6
#define TXEQIMPEDANCE_DRVSTRENFSDQP___M     0x3F
#define TXODTDRVSTREN_ODTSTRENN___S            6
#define TXODTDRVSTREN_ODTSTRENP___M         0x3F

#define TXSLEWRATE___M                       0xF
#define TXSLEWRATE_TXPREN___S                  4
#define TXSLEWRATE_TXPREDRV_MODE___M         0x7
#define TXSLEWRATE_TXPREDRV_MODE___S           8

#define TXSLEWRATE_TXPREDRV                  0x2

#define DQDQSRCVCNTRL_SELANALOGVREF___S        0
#define DQDQSRCVCNTRL_SELANALOGVREF___M      0x1
#define DQDQSRCVCNTRL_EXTVREFRANGE___S         1
#define DQDQSRCVCNTRL_EXTVREFRANGE___M       0x1
#define DQDQSRCVCNTRL_DFECTRL___S              2
#define DQDQSRCVCNTRL_DFECTRL___M            0x3
#define DQDQSRCVCNTRL_MAJORMODEDBYTE___S       4
#define DQDQSRCVCNTRL_MAJORMODEDBYTE___M     0x7
#define DQDQSRCVCNTRL_GAINCURRADJ___S          7
#define DQDQSRCVCNTRL_GAINCURRADJ___M       0x1F

#define DQDQSRCVCNTRL_SELANALOGVREF            0
#define DQDQSRCVCNTRL_EXTVREFRANGE             0
#define DQDQSRCVCNTRL_DFECTRL                  0
#define DQDQSRCVCNTRL_GAINCURRADJ            0xB
#define DQDQSRCVCNTRL_MAJORMODEDBYTE_DDR4    0x3
#define DQDQSRCVCNTRL_MAJORMODEDBYTE_DDR3    0x0

#define ATXIMPEDANCE_ADRVSTRENP___M         0x1F
#define ATXIMPEDANCE_ADRVSTRENN___S            5

#define ATXSLEWRATE_ATXPREP___M              0xF
#define ATXSLEWRATE_ATXPREN___S                4
#define ATXSLEWRATE_ATXPREDRV_MODE___M       0x7
#define ATXSLEWRATE_ATXPREDRV_MODE___S         8

#define ATXSLEWRATE_ATXPREDRV_MODE             3
#define CK_ATXSLEWRATE_ATXPREDRV_MODE          0

#define ANIB_CK0_1_INSTANCE                    4
#define ANIB_CK2_3_INSTANCE                    5

/******************************************************************************
* Derived data types
******************************************************************************/

/******************************************************************************
* Global Variables
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/
#define DFI_FREQ_KHZ(ddr_freq_mhz)  ((ddr_freq_mhz * 1000) / DFI_RATIO)

/******************************************************************************
* Function Prototypes
******************************************************************************/
void mddr_phy_build_caluclkinfo_regs
    (mddr_settings_t *mddr_settings_ptr, uint16_t *reg_ptr);

void mddr_phy_build_seq0bdly_regs(mddr_settings_t *mddr_settings_ptr,
        mddr_phy_register_values_t *phy_regs_ptr);

void mddr_phy_build_plltestmode_regs
    (mddr_settings_t *mddr_settings_ptr, uint16_t *reg_ptr);

void mddr_phy_build_pllctrl2_regs
    (mddr_settings_t *mddr_settings_ptr, uint16_t *reg_ptr);

void mddr_phy_build_dllgainctl_regs
    (mddr_settings_t *mddr_settings_ptr, uint16_t *reg_ptr);

void mddr_phy_build_ardptrinitval_regs
    (mddr_settings_t *mddr_settings_ptr, uint16_t *reg_ptr);

void mddr_phy_build_dqspreamblecontrol_regs
    (mddr_settings_t *mddr_settings_ptr, uint16_t *reg_ptr);

void mddr_phy_build_tristatemodeca_regs
    (mddr_settings_t *mddr_settings_ptr, uint16_t *reg_ptr);

uint16_t mddr_phy_build_dfidatacsdestmap_reg(uint8_t chan);
uint16_t mddr_phy_build_masterx4config_reg(void);
uint16_t mddr_phy_build_enablecsmulticast_reg(uint8_t chan);
uint16_t mddr_phy_build_dbytedllmodecntrl_reg(void);
uint16_t mddr_phy_build_hwtcamode_reg(void);
void mddr_phy_build_odt_regs
    (uint16_t odt_reg[DDR_MAX_NUM_CHANS][PHY_ODT_REGS]);

void mddr_phy_init_seq(uint64_t mddr_base_addr);
void mddr_phy_set_seq0bdly_regs(uint64_t mddr_base_addr);

unsigned mddr_phy_poll_calbusy(uint64_t mddr_base_addr, uint32_t to_ms);

void mddr_phy_build_dmem_regs(mddr_settings_t *mddr_settings_ptr);

void mddr_phy_set_si_regs(uint8_t ddr_chan);

/******************************************************************************
* External Functions
******************************************************************************/


/*!****************************************************************************
*
* @par Description:
*    This function is to build the common PHY register values.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
* @return
*    None
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_get_reg_vals(mddr_settings_t *mddr_settings_ptr)
{
//      mddr_reg_vals.phy_regs.memresetl_val = mddr_phy_build_memresetl_reg();

    mddr_phy_build_caluclkinfo_regs(mddr_settings_ptr,
            &mddr_reg_vals.phy_regs.caluclkinfo_val[0]);
    mddr_phy_build_seq0bdly_regs(mddr_settings_ptr, &mddr_reg_vals.phy_regs);
    mddr_phy_build_plltestmode_regs(mddr_settings_ptr,
            &mddr_reg_vals.phy_regs.plltestmode_val[0]);
    mddr_phy_build_pllctrl2_regs(mddr_settings_ptr,
            &mddr_reg_vals.phy_regs.pllctrl2_val[0]);

    mddr_phy_build_dllgainctl_regs(mddr_settings_ptr,
            &mddr_reg_vals.phy_regs.dllgainctl_val[0]);

    mddr_phy_build_ardptrinitval_regs(mddr_settings_ptr,
            &mddr_reg_vals.phy_regs.ardptrinitval_val[0]);

//  mddr_reg_vals.phy_regs.memalertcontrol_val =
//      mddr_phy_build_memalertcontrol_reg();

    mddr_reg_vals.phy_regs.masterx4config_val =
        mddr_phy_build_masterx4config_reg();

    mddr_reg_vals.phy_regs.dbytedllmodecntrl_val =
        mddr_phy_build_dbytedllmodecntrl_reg();

    mddr_phy_build_dqspreamblecontrol_regs(mddr_settings_ptr,
            &mddr_reg_vals.phy_regs.dqspreamblecontrol_val[0]);

    mddr_reg_vals.phy_regs.hwtcamode_val = mddr_phy_build_hwtcamode_reg();

    mddr_phy_build_tristatemodeca_regs(mddr_settings_ptr,
            &mddr_reg_vals.phy_regs.tristatemodeca_val[0]);

    mddr_phy_build_odt_regs(mddr_reg_vals.phy_regs.odt_dmem_6x);

    mddr_phy_build_dmem_regs(mddr_settings_ptr);
}


/*!****************************************************************************
*
* @par Description:
*    This function initializes the PHYs found in the Monaco
*    DDR subsystem
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
*
* @return
*    The status indicating the level of success in initializing the PHY.
*
* @author
*    mwuu
*
******************************************************************************/
unsigned mddr_phy_init(uint8_t ddr_chan)
{
  unsigned status = COM_OK;

  if ((platform_mode == SILICON) && (
    (mddr_dimm_configs[ddr_chan][0].dev_type != SPD_DEVICE_TYPE_UNDEFINED) ||
    (mddr_dimm_configs[ddr_chan][1].dev_type != SPD_DEVICE_TYPE_UNDEFINED)))
  {
      uint64_t mddr_base_addr = mddr_base_addrs[ddr_chan];
      uint16_t dfidatacsdestmap_val;

      monaco_log(LOW, "\n ------------------------------------\n");
      monaco_log
          (CRITICAL, "| Initializing the PHY for channel %1d |\n", hddrss[ddr_chan]);
      monaco_log(LOW, " ------------------------------------\n");

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIPHYUPD_OFFSET,
              "DDRPHY_MASTER0_DFIPHYUPD", PHY_DISABLE_UPDATE_CNTR);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_MEMRESETL_OFFSET,
              "DDRPHY_MASTER0_MEMRESETL", PHY_CTRL_DRAM_RESET);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_CALUCLKINFO_P0_OFFSET, "DDRPHY_MASTER0_CALUCLKINFO_P0", mddr_reg_vals.phy_regs.caluclkinfo_val[0]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_CALUCLKINFO_P1_OFFSET, "DDRPHY_MASTER0_CALUCLKINFO_P1", mddr_reg_vals.phy_regs.caluclkinfo_val[1]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_CALUCLKINFO_P2_OFFSET, "DDRPHY_MASTER0_CALUCLKINFO_P2", mddr_reg_vals.phy_regs.caluclkinfo_val[2]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_CALUCLKINFO_P3_OFFSET, "DDRPHY_MASTER0_CALUCLKINFO_P3", mddr_reg_vals.phy_regs.caluclkinfo_val[3]);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_CALMISC2_OFFSET,
              "DDRPHY_MASTER0_CALMISC2", PHY_CALMISC2_VAL);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_CALRATE_OFFSET,
              "DDRPHY_MASTER0_CALRATE", PHY_START_IMP_CAL);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_CALRATE_OFFSET,
              "DDRPHY_MASTER0_CALRATE", PHY_STOP_IMP_CAL);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_PLLTESTMODE_P0_OFFSET,
              "DDRPHY_MASTER0_PLLTESTMODE_P0",
              mddr_reg_vals.phy_regs.plltestmode_val[0]);
/*
      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_PLLTESTMODE_P1_OFFSET,
              "DDRPHY_MASTER0_PLLTESTMODE_P1",
              mddr_reg_vals.phy_regs.plltestmode_val[1]);
      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_PLLTESTMODE_P2_OFFSET,
              "DDRPHY_MASTER0_PLLTESTMODE_P2",
              mddr_reg_vals.phy_regs.plltestmode_val[2]);
      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_PLLTESTMODE_P3_OFFSET,
              "DDRPHY_MASTER0_PLLTESTMODE_P3",
              mddr_reg_vals.phy_regs.plltestmode_val[3]);
*/
      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_PLLCTRL2_P0_OFFSET,
              "DDRPHY_MASTER0_PLLCTRL2_P0",
              mddr_reg_vals.phy_regs.pllctrl2_val[0]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_PLLCTRL2_P1_OFFSET, "DDRPHY_MASTER0_PLLCTRL2_P1", mddr_reg_vals.phy_regs.pllctrl2_val[1]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_PLLCTRL2_P2_OFFSET, "DDRPHY_MASTER0_PLLCTRL2_P2", mddr_reg_vals.phy_regs.pllctrl2_val[2]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_PLLCTRL2_P3_OFFSET, "DDRPHY_MASTER0_PLLCTRL2_P3", mddr_reg_vals.phy_regs.pllctrl2_val[3]);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DLLGAINCTL_P0_OFFSET, "DDRPHY_MASTER0_DLLGAINCTL_P0", mddr_reg_vals.phy_regs.dllgainctl_val[0]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DLLGAINCTL_P1_OFFSET, "DDRPHY_MASTER0_DLLGAINCTL_P1", mddr_reg_vals.phy_regs.dllgainctl_val[1]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DLLGAINCTL_P2_OFFSET, "DDRPHY_MASTER0_DLLGAINCTL_P2", mddr_reg_vals.phy_regs.dllgainctl_val[2]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DLLGAINCTL_P3_OFFSET, "DDRPHY_MASTER0_DLLGAINCTL_P3", mddr_reg_vals.phy_regs.dllgainctl_val[3]);

      dfidatacsdestmap_val = mddr_phy_build_dfidatacsdestmap_reg(ddr_chan);
      mddr_set_reg(
        mddr_base_addr + DDRPHY_MASTER0_DFIWRDATACSDESTMAP_P0_OFFSET,
        "DDRPHY_MASTER0_DFIWRDATACSDESTMAP_P0", dfidatacsdestmap_val);
//      mddr_set_reg(
//          mddr_base_addr + DDRPHY_MASTER0_DFIWRDATACSDESTMAP_P1_OFFSET,
//          "DDRPHY_MASTER0_DFIWRDATACSDESTMAP_P1", dfidatacsdestmap_val);
//      mddr_set_reg(
//      mddr_base_addr + DDRPHY_MASTER0_DFIWRDATACSDESTMAP_P2_OFFSET,
//      "DDRPHY_MASTER0_DFIWRDATACSDESTMAP_P2", dfidatacsdestmap_val);
//      mddr_set_reg(
//      mddr_base_addr + DDRPHY_MASTER0_DFIWRDATACSDESTMAP_P3_OFFSET,
//      "DDRPHY_MASTER0_DFIWRDATACSDESTMAP_P3", dfidatacsdestmap_val);

      mddr_set_reg(
              mddr_base_addr + DDRPHY_MASTER0_DFIRDDATACSDESTMAP_P0_OFFSET,
              "DDRPHY_MASTER0_DFIRDDATACSDESTMAP_P0", dfidatacsdestmap_val);
//      mddr_set_reg(
//          mddr_base_addr + DDRPHY_MASTER0_DFIRDDATACSDESTMAP_P1_OFFSET,
//          "DDRPHY_MASTER0_DFIRDDATACSDESTMAP_P1", dfidatacsdestmap_val);
//      mddr_set_reg(
//          mddr_base_addr + DDRPHY_MASTER0_DFIRDDATACSDESTMAP_P2_OFFSET,
//          "DDRPHY_MASTER0_DFIRDDATACSDESTMAP_P2", dfidatacsdestmap_val);
//      mddr_set_reg(
//          mddr_base_addr + DDRPHY_MASTER0_DFIRDDATACSDESTMAP_P3_OFFSET,
//          "DDRPHY_MASTER0_DFIRDDATACSDESTMAP_P3", dfidatacsdestmap_val);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_ARDPTRINITVAL_P0_OFFSET,
              "DDRPHY_MASTER0_ARDPTRINITVAL_P0",
              mddr_reg_vals.phy_regs.ardptrinitval_val[0]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_ARDPTRINITVAL_P1_OFFSET,
//          "DDRPHY_MASTER0_ARDPTRINITVAL_P1",
//          mddr_reg_vals.phy_regs.ardptrinitval_val[1]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_ARDPTRINITVAL_P2_OFFSET,
//          "DDRPHY_MASTER0_ARDPTRINITVAL_P2",
//          mddr_reg_vals.phy_regs.ardptrinitval_val[2]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_ARDPTRINITVAL_P3_OFFSET,
//          "DDRPHY_MASTER0_ARDPTRINITVAL_P3",
//          mddr_reg_vals.phy_regs.ardptrinitval_val[3]);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_MEMALERTCONTROL_OFFSET,
              "DDRPHY_MASTER0_MEMALERTCONTROL", PHY_MEMALERTCONTROL);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_MASTERX4CONFIG_OFFSET,
              "DDRPHY_MASTER0_MASTERX4CONFIG",
              mddr_reg_vals.phy_regs.masterx4config_val);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_ENABLECSMULTICAST_OFFSET,
              "DDRPHY_MASTER0_ENABLECSMULTICAST",
              mddr_phy_build_enablecsmulticast_reg(ddr_chan));

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DBYTEDLLMODECNTRL_OFFSET,
              "DDRPHY_MASTER0_DBYTEDLLMODECNTRL",
              mddr_reg_vals.phy_regs.dbytedllmodecntrl_val);

      mddr_set_reg(mddr_base_addr +
              DDRPHY_MASTER0_DQSPREAMBLECONTROL_P0_OFFSET,
              "DDRPHY_MASTER0_DQSPREAMBLECONTROL_P0",
              mddr_reg_vals.phy_regs.dqspreamblecontrol_val[0]);
//      mddr_set_reg(mddr_base_addr +
//          DDRPHY_MASTER0_DQSPREAMBLECONTROL_P1_OFFSET,
//          "DDRPHY_MASTER0_DQSPREAMBLECONTROL_P1",
//          mddr_reg_vals.phy_regs.dqspreamblecontrol_val[1]);
//      mddr_set_reg(mddr_base_addr +
//          DDRPHY_MASTER0_DQSPREAMBLECONTROL_P2_OFFSET,
//          "DDRPHY_MASTER0_DQSPREAMBLECONTROL_P2",
//          mddr_reg_vals.phy_regs.dqspreamblecontrol_val[2]);
//      mddr_set_reg(mddr_base_addr +
//          DDRPHY_MASTER0_DQSPREAMBLECONTROL_P3_OFFSET,
//          "DDRPHY_MASTER0_DQSPREAMBLECONTROL_P3",
//          mddr_reg_vals.phy_regs.dqspreamblecontrol_val[3]);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_HWTCAMODE_OFFSET,
            "DDRPHY_MASTER0_HWTCAMODE", mddr_reg_vals.phy_regs.hwtcamode_val);

      mddr_phy_set_si_regs(ddr_chan);

//-- poll calbusy
      mddr_phy_poll_calbusy(mddr_base_addr, PHY_POLL_TIMEOUT_MS);

// enable periodic impedance calibration
      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_CALRATE_OFFSET,
              "DDRPHY_MASTER0_CALRATE", PHY_START_IMP_CAL);

// call setup phy init seq
      mddr_phy_init_seq(mddr_base_addr);

      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_TRISTATEMODECA_P0_OFFSET,
              "DDRPHY_MASTER0_TRISTATEMODECA_P0",
              mddr_reg_vals.phy_regs.tristatemodeca_val[0]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_TRISTATEMODECA_P1_OFFSET,
//          "DDRPHY_MASTER0_TRISTATEMODECA_P1",
//          mddr_reg_vals.phy_regs.tristatemodeca_val[1]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_TRISTATEMODECA_P2_OFFSET,
//          "DDRPHY_MASTER0_TRISTATEMODECA_P2",
//          mddr_reg_vals.phy_regs.tristatemodeca_val[2]);
//      mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_TRISTATEMODECA_P3_OFFSET,
//          "DDRPHY_MASTER0_TRISTATEMODECA_P3",
//          mddr_reg_vals.phy_regs.tristatemodeca_val[3]);

  } // end if Silicon

  return status;
}


/******************************************************************************
* Local Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function builds the caluclkinfo registers for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*                                  @param
*    *caluclkinfo           Pointer for the caluclkinfo[freq]
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_caluclkinfo_regs
(
    mddr_settings_t *mddr_settings_ptr,
    uint16_t *caluclkinfo
)
{
    uint16_t dfi_ticks_per_us;
    uint8_t ddr_freq_itr;

    for(ddr_freq_itr = 0;
            ddr_freq_itr < DDR_MAX_FREQ_POOL_TARGET; ++ddr_freq_itr)
    {
        dfi_ticks_per_us = com_ceil_div(NUM_PS_IN_ONE_US,
              MDDR_MHZ_TO_PS(mddr_settings_ptr->mem_freq_mhz[ddr_freq_itr])
              * DFI_RATIO
        );

        caluclkinfo[ddr_freq_itr] = dfi_ticks_per_us;
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function builds seq0bdly registers for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*                                  @param
*    phy_regs_ptr           Pointer for the PHY registers, contains:
*                            seq0bdlyX_val[] {X=0..3}
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_seq0bdly_regs
(
    mddr_settings_t *mddr_settings_ptr,
    mddr_phy_register_values_t *phy_regs_ptr
)
{
    uint8_t ddr_freq_itr;
    uint32_t dfi_div4_ps_dom;

    // pstates
    for (ddr_freq_itr=0;
            ddr_freq_itr < DDR_MAX_FREQ_POOL_TARGET; ddr_freq_itr++)
    {
        dfi_div4_ps_dom = DFI_RATIO * 4 *
            MDDR_MHZ_TO_PS(mddr_settings_ptr->mem_freq_mhz[ddr_freq_itr]);

        phy_regs_ptr->seq0bdly0_val[ddr_freq_itr] =
            com_ceil_div(NUM_PS_IN_HALF_US, dfi_div4_ps_dom);
        phy_regs_ptr->seq0bdly1_val[ddr_freq_itr] =
            com_ceil_div(NUM_PS_IN_ONE_US, dfi_div4_ps_dom);
        phy_regs_ptr->seq0bdly2_val[ddr_freq_itr] =
            com_ceil_div(NUM_PS_IN_10_US, dfi_div4_ps_dom);
        phy_regs_ptr->seq0bdly3_val[ddr_freq_itr] =
            com_ceil_div(NUM_PS_IN_25_US, dfi_div4_ps_dom);
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function builds plltestmode register for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*                                  @param
*    *plltestmode           Pointer for the plltestmode[freq]
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_plltestmode_regs
(
    mddr_settings_t *mddr_settings_ptr,
    uint16_t *plltestmode
)
{
    uint8_t ddr_freq_itr;
    uint32_t dfi_freq_khz;

    for(ddr_freq_itr = 0;
            ddr_freq_itr < DDR_MAX_FREQ_POOL_TARGET; ++ddr_freq_itr)
    {
        dfi_freq_khz =
            DFI_FREQ_KHZ(mddr_settings_ptr->mem_freq_mhz[ddr_freq_itr]);

        if (dfi_freq_khz > 0)   // place holder if we need to change
        {
            plltestmode[ddr_freq_itr] = PHY_PLLTESTMODE_VAL;
        }
        else
        {
            plltestmode[ddr_freq_itr] = PHY_PLLTESTMODE_VAL;
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function builds pllctrl2 register for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*                                  @param
*    *pllctrl2              Pointer for the pllctrl2[freq]
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_pllctrl2_regs
(
    mddr_settings_t *mddr_settings_ptr,
    uint16_t *pllctrl2
)
{
    uint8_t ddr_freq_itr;
    uint32_t dfi_freq_khz;
    uint16_t pll_ctrl2_val;

    for(ddr_freq_itr = 0;
            ddr_freq_itr < DDR_MAX_FREQ_POOL_TARGET; ++ddr_freq_itr)
    {
        dfi_freq_khz =
            DFI_FREQ_KHZ(mddr_settings_ptr->mem_freq_mhz[ddr_freq_itr]);

        if (dfi_freq_khz > 937500)  // >937.5MHz
        {
            pll_ctrl2_val = PLL_CTRL2_GT_937p5_MHZ;
        }
        else if (dfi_freq_khz > 625000)  // >625MHz
        {
            pll_ctrl2_val = PLL_CTRL2_GT_625_MHZ;
        }
        else if (dfi_freq_khz > 468750)  // >468.75MHz
        {
            pll_ctrl2_val = PLL_CTRL2_GT_468p75_MHZ;
        }
        else if (dfi_freq_khz > 312500)  // >312.5MHz
        {
            pll_ctrl2_val = PLL_CTRL2_GT_312p5_MHZ;
        }
        else if (dfi_freq_khz > 234400)  // >234.4MHz
        {
            pll_ctrl2_val = PLL_CTRL2_GT_234p4_MHZ;
        }
        else // if (dfi_freq_khz > 166000)  // >166MHz
        {
            pll_ctrl2_val = PLL_CTRL2_LT_234p4_MHZ;
        }


        pllctrl2[ddr_freq_itr] = pll_ctrl2_val;
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function builds dllgainctl register for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*                                  @param
*    *dllgainctl            Pointer for the dllgainctl[freq]
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_dllgainctl_regs
(
    mddr_settings_t *mddr_settings_ptr,
    uint16_t *dllgainctl
)
{
    uint16_t dllgainiv;
    uint16_t dllgainctl_val;
    uint8_t ddr_freq_itr;

    for(ddr_freq_itr = 0;
            ddr_freq_itr < DDR_MAX_FREQ_POOL_TARGET; ++ddr_freq_itr)
    {
        if (mddr_settings_ptr->mem_freq_mhz[ddr_freq_itr] < 667)
        {
            dllgainiv = DLLGAINIV_LT_667MHZ;
        }
        else if (mddr_settings_ptr->mem_freq_mhz[ddr_freq_itr] < 933)
        {
            dllgainiv = DLLGAINIV_LT_933MHZ;
        }
        else
        {
            dllgainiv = DLLGAINIV_GT_933MHZ;
        }

        dllgainctl_val = dllgainiv & DLLGAINIV___M;
        dllgainctl_val |= ((DLLGAINTV & DLLGAINTV___M) << DLLGAINTV___S);

        dllgainctl[ddr_freq_itr] = dllgainctl_val;
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function builds ardptrinitval register for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*                                  @param
*    *ardptrinitval         Pointer for the ardptrinitval[freq]
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_ardptrinitval_regs
(
    mddr_settings_t *mddr_settings_ptr,
    uint16_t *ardptrinitval
)
{
    uint16_t ardptrinitval_val;
    uint8_t ddr_freq_itr;

    for(ddr_freq_itr = 0;
            ddr_freq_itr < DDR_MAX_FREQ_POOL_TARGET; ++ddr_freq_itr)
    {
        if (mddr_settings_ptr->mem_freq_mhz[ddr_freq_itr] < 933)
        {
            ardptrinitval_val = ARDPTRINITVAL_LT_933MHZ_UI;
        }
        else
        {
            ardptrinitval_val = ARDPTRINITVAL_GT_933MHZ_UI;
        }

        ardptrinitval[ddr_freq_itr] = ardptrinitval_val;
// OVERRIDE... Fix this later
        ardptrinitval[ddr_freq_itr] = 0x3;
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function builds dqspreamblecontrol register for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*                                  @param
*    *dqspreamblecontrol    Pointer for the dqspreamblecontrol[freq]
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_dqspreamblecontrol_regs
(
    mddr_settings_t *mddr_settings_ptr,
    uint16_t *dqspreamblecontrol
)
{
    uint16_t dqs_preamble_val;
    uint8_t ddr_freq_itr;

    for(ddr_freq_itr = 0;
            ddr_freq_itr < DDR_MAX_FREQ_POOL_TARGET; ++ddr_freq_itr)
    {
        dqs_preamble_val = POSITIONDFEINIT << POSITIONDFEINIT___S;

// TODO preamble control in SI per freq?...
        if(mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_READ)
        {
            dqs_preamble_val |= (0x1 << TWOTCKRXDQSPRE___S);
        }

        if(mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE)
        {
            dqs_preamble_val |= (0x1 << TWOTCKTXDQSPRE___S);
        }

        dqspreamblecontrol[ddr_freq_itr] = dqs_preamble_val;
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function builds tristatemodeca register for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr      The pointer to the structure containing the
*                            settings information.
*                                  @param
*    *tristatemodeca        Pointer for the tristatemode[freq]
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_tristatemodeca_regs
(
    mddr_settings_t *mddr_settings_ptr,
    uint16_t *tristatemodeca
)
{
    uint16_t tristatemodeca_val;
    uint8_t ddr_freq_itr;

// TODO CA stretch control in SI per freq?... also tristatemodeca, dynadrtri,
    for(ddr_freq_itr = 0;
            ddr_freq_itr < DDR_MAX_FREQ_POOL_TARGET; ++ddr_freq_itr)
    {
        tristatemodeca_val = DISDYNADRTRI & DISDYNADRTRI___M;

        // set CA bus timing
        if (mddr_settings_ptr->ca_stretch == CA_STRETCH_2T)
        {
            tristatemodeca_val |=
                ((CA_2T_MODE & CA_2T_MODE___M) << CA_2T_MODE___S);
        }

        tristatemodeca_val |= ((CLKDISVAL & CLKDISVAL___M) << CLKDISVAL___S);

        tristatemodeca[ddr_freq_itr] = tristatemodeca_val;
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function builds dfidatacsdestmap register.
*
*                                  @param
*    ddr_chan           Current DDR channel
*
* @return
*    Value of register to be set
*
* @author
*    mwuu
*
******************************************************************************/
uint16_t mddr_phy_build_dfidatacsdestmap_reg(uint8_t ddr_chan)
{
    uint16_t dfidatacsdestmap_val;

    if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
    {
        if (mddr_dimm_configs[ddr_chan][1].dev_type
                != SPD_DEVICE_TYPE_UNDEFINED)
        {
            // map 0,1 to CS0; 2,3 to CS1
            dfidatacsdestmap_val = CS_DELAY_MAPPING_LRDIMM_DUAL_SLOT;
        }
        else
        {
            // map all to CS0
            dfidatacsdestmap_val = CS_DELAY_MAPPING_LRDIMM_SINGLE_SLOT;
        }
    }
    else
    {
        // 1:1 mapping of CS
        dfidatacsdestmap_val = CS_DELAY_MAPPING_NOT_LRDIMM;
    }

    return dfidatacsdestmap_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function builds masterx4config register.
*
* @return
*    Value of register to be set
*
* @author
*    mwuu
*
******************************************************************************/
uint16_t mddr_phy_build_masterx4config_reg()
{
    uint16_t masterx4config_val;

    if (common_cfg.sdram_width == SPD_SDRAM_WIDTH_X4)
    {
        masterx4config_val = X4_CONFIG_TRUE;
    }
    else
    {
        masterx4config_val = X4_CONFIG_FALSE;
    }

    return masterx4config_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function builds enablecsmulticast register.
*
*                                  @param
*    ddr_chan           Current DDR channel
*
* @return
*    Value of register to be set
*
* @author
*    mwuu
*
******************************************************************************/
uint16_t mddr_phy_build_enablecsmulticast_reg(uint8_t ddr_chan)
{
    uint16_t enablecsmulticast_val;

    if (mddr_dimm_configs[ddr_chan][0].num_ranks == 4)
    {
        enablecsmulticast_val = 1;
    }
    else
    {
        enablecsmulticast_val = 0;
    }

    return enablecsmulticast_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function builds dbytedllmodecntrl register.
*
* @return
*    Value of register to be set
*
* @author
*    mwuu
*
******************************************************************************/
uint16_t mddr_phy_build_dbytedllmodecntrl_reg()
{
    uint16_t dbytedllmodecntrl_val;

    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        dbytedllmodecntrl_val = PREAMBLE_MODE_DDR4;
    }
    else
    {
        dbytedllmodecntrl_val = PREAMBLE_MODE_NOT_DDR4;
    }

    return dbytedllmodecntrl_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function builds hwtcamode register.
*
* @return
*    Value of register to be set
*
* @author
*    mwuu
*
******************************************************************************/
uint16_t mddr_phy_build_hwtcamode_reg(void)
{
    uint16_t hwtcamode_val;

    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        hwtcamode_val = CA_MODE_DDR4;
    }
    else
    {
        hwtcamode_val = CA_MODE_NOT_DDR4;
    }

    return hwtcamode_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function poll for the PHY register to return the expected
*    value within timeout specified.
*
*                                  @param
*    mddr_base_addr    The base address of the configuration registers for
*                       the memory controller.
*                             @param
*    exp_val           Expected bits to be set in the register
*                             @param
*    mask              Mask to extract the expected bits to be set in the
*                       register.
*                             @param
*    emask             Mask to extract the error bits from the register data.
*                             @param
*    to_ms             Timeout in ms.
*
* @return
*   status                  COM_OK or COM_ERROR;
*
* @author
*    mwuu
******************************************************************************/
unsigned mddr_phy_poll_calbusy
(
    uint64_t mddr_base_addr,
    uint32_t to_ms
)
{
    unsigned status = COM_OK;
    uint32_t expected_data;
    uint32_t reg_value;
    uint32_t wait_time_us=0;
    uint32_t wait_time_ms;

    do
    {
        // Delay for 100us before each read to avoid beating on the target
        // register and to provide an easy way to track the time to allow
        // the timeout.
        mddr_mc_wait_us(mddr_base_addr, 100);

        // Keep track of how long we have waited
        wait_time_us += 100;
        wait_time_ms = wait_time_us / MICRO_SEC_PER_MILLI_SEC;

        // Extract only the bits of interest from the register.
        reg_value = mddr_get_reg(mddr_base_addr +
                DDRPHY_MASTER0_CALBUSY_OFFSET, "DDRPHY_MASTER0_CALBUSY");

        expected_data = reg_value & ~MASTER0_CALBUSY;

        // exit on error or wait till done bit?
    } while(
        (expected_data != reg_value) &&
        (wait_time_ms < to_ms)
    );

    if(wait_time_ms >= to_ms)
    {
        monaco_log(LOW, "   Timeout waiting on reading DDRPHY_MASTER0_CALBUSY"
               " : Expected 0x%8.8x  Got 0x%8.8x\n", expected_data, reg_value);
        status = COM_ERROR;
    }

    return status;
}


/*!****************************************************************************
*
* @par Description:
*    This function builds the ODT registers for the PHY, DMEM[62:61].
*
*                                  @param
*    odt_dmem_6x    ODT array[ddr_chan][4], one per rank
*
* @return
*    None
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_odt_regs
(
    uint16_t odt_dmem_6x[DDR_MAX_NUM_CHANS][PHY_ODT_REGS]
)
{
    uint16_t d0_rwcs1_rwcs0;    // dmem 60
    uint16_t d0_rwcs3_rwcs2;    // dmem 61
    uint16_t d1_rwcs1_rwcs0;    // dmem 62

    uint8_t ddr_chan;

    // max 4 ranks supported by PHY currently
    // dimm0 (cs0, cs1)
    // dimm1 (cs2, cs3)
    //   or
    // dimm0 (cs0:3)

    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        // rd/wr cs1, rd/wr cs0
        d0_rwcs1_rwcs0 = (
            (((mddr_reg_vals.ddr_odt_rd_cntl_val[ddr_chan] >> (ODT_BITS * 1))
                & PHY_ODT___M) << PHY_ODD_ODT_RD___S)
            | (((mddr_reg_vals.ddr_odt_wr_cntl_val[ddr_chan] >> (ODT_BITS * 1))
                & PHY_ODT___M) << PHY_ODD_ODT_WR___S)
            | ((mddr_reg_vals.ddr_odt_rd_cntl_val[ddr_chan]
                & PHY_ODT___M) << PHY_EVEN_ODT_RD___S)
            | (mddr_reg_vals.ddr_odt_wr_cntl_val[ddr_chan] & PHY_ODT___M));

        // rd/wr cs3, rd/wr cs2
        d0_rwcs3_rwcs2 = (
            (((mddr_reg_vals.ddr_odt_rd_cntl_val[ddr_chan] >> (ODT_BITS * 3))
                & PHY_ODT___M) << PHY_ODD_ODT_RD___S)
            | (((mddr_reg_vals.ddr_odt_wr_cntl_val[ddr_chan] >> (ODT_BITS * 3))
                & PHY_ODT___M) << PHY_ODD_ODT_WR___S)
            | (((mddr_reg_vals.ddr_odt_rd_cntl_val[ddr_chan] >> (ODT_BITS * 2))
                & PHY_ODT___M) << PHY_EVEN_ODT_RD___S)
            | ((mddr_reg_vals.ddr_odt_wr_cntl_val[ddr_chan] >> (ODT_BITS * 2))
                & PHY_ODT___M));

        if (mddr_dimm_configs[ddr_chan][1].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            // rd/wr cs3, rd/wr cs2
            d1_rwcs1_rwcs0 = d0_rwcs3_rwcs2;
        }
        else
        {
            d1_rwcs1_rwcs0 = 0;
        }

        odt_dmem_6x[ddr_chan][0] = d0_rwcs1_rwcs0;
        odt_dmem_6x[ddr_chan][1] = d0_rwcs3_rwcs2;
        odt_dmem_6x[ddr_chan][2] = d1_rwcs1_rwcs0;
    }
}


/*!****************************************************************************
*
* @par Description:
*    PHY initialization of PMU
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the MDDR block.
*
* @return
*    None.
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_init_seq
(
    uint64_t mddr_base_addr
)
{
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY0_P0_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY0_P0", DDRPHY_INIT_ENGINE_DELAY_VAL0);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY1_P0_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY1_P0", DDRPHY_INIT_ENGINE_DELAY_VAL1);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY2_P0_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY2_P0", DDRPHY_INIT_ENGINE_DELAY_VAL2);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY3_P0_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY3_P0", DDRPHY_INIT_ENGINE_DELAY_VAL3);

    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY0_P1_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY0_P1", DDRPHY_INIT_ENGINE_DELAY_VAL0);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY1_P1_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY1_P1", DDRPHY_INIT_ENGINE_DELAY_VAL1);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY2_P1_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY2_P1", DDRPHY_INIT_ENGINE_DELAY_VAL2);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY3_P1_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY3_P1", DDRPHY_INIT_ENGINE_DELAY_VAL3);

    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY0_P2_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY0_P2", DDRPHY_INIT_ENGINE_DELAY_VAL0);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY1_P2_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY1_P2", DDRPHY_INIT_ENGINE_DELAY_VAL1);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY2_P2_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY2_P2", DDRPHY_INIT_ENGINE_DELAY_VAL2);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY3_P2_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY3_P2", DDRPHY_INIT_ENGINE_DELAY_VAL3);

    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY0_P3_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY0_P3", DDRPHY_INIT_ENGINE_DELAY_VAL0);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY1_P3_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY1_P3", DDRPHY_INIT_ENGINE_DELAY_VAL1);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY2_P3_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY2_P3", DDRPHY_INIT_ENGINE_DELAY_VAL2);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY3_P3_OFFSET,
        "DDRPHY_MASTER0_SEQ0BDLY3_P3", DDRPHY_INIT_ENGINE_DELAY_VAL3);

    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_PRESEQUENCEREG0B0S0_OFFSET,
        "DDRPHY_INITENG0_PRESEQUENCEREG0B0S0",
        DDRPHY_INITENG0_PRESEQUENCEREG0B0S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_PRESEQUENCEREG0B0S1_OFFSET,
        "DDRPHY_INITENG0_PRESEQUENCEREG0B0S1",
        DDRPHY_INITENG0_PRESEQUENCEREG0B0S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_PRESEQUENCEREG0B0S2_OFFSET,
        "DDRPHY_INITENG0_PRESEQUENCEREG0B0S2",
        DDRPHY_INITENG0_PRESEQUENCEREG0B0S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_PRESEQUENCEREG0B1S0_OFFSET,
        "DDRPHY_INITENG0_PRESEQUENCEREG0B1S0",
        DDRPHY_INITENG0_PRESEQUENCEREG0B1S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_PRESEQUENCEREG0B1S1_OFFSET,
        "DDRPHY_INITENG0_PRESEQUENCEREG0B1S1",
        DDRPHY_INITENG0_PRESEQUENCEREG0B1S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_PRESEQUENCEREG0B1S2_OFFSET,
        "DDRPHY_INITENG0_PRESEQUENCEREG0B1S2",
        DDRPHY_INITENG0_PRESEQUENCEREG0B1S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B0S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B0S0",
        DDRPHY_INITENG0_SEQUENCEREG0B0S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B0S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B0S1",
        DDRPHY_INITENG0_SEQUENCEREG0B0S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B0S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B0S2",
        DDRPHY_INITENG0_SEQUENCEREG0B0S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B1S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B1S0",
        DDRPHY_INITENG0_SEQUENCEREG0B1S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B1S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B1S1",
        DDRPHY_INITENG0_SEQUENCEREG0B1S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B1S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B1S2",
        DDRPHY_INITENG0_SEQUENCEREG0B1S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B2S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B2S0",
        DDRPHY_INITENG0_SEQUENCEREG0B2S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B2S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B2S1",
        DDRPHY_INITENG0_SEQUENCEREG0B2S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B2S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B2S2",
        DDRPHY_INITENG0_SEQUENCEREG0B2S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B3S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B3S0",
        DDRPHY_INITENG0_SEQUENCEREG0B3S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B3S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B3S1",
        DDRPHY_INITENG0_SEQUENCEREG0B3S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B3S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B3S2",
        DDRPHY_INITENG0_SEQUENCEREG0B3S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B4S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B4S0",
        DDRPHY_INITENG0_SEQUENCEREG0B4S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B4S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B4S1",
        DDRPHY_INITENG0_SEQUENCEREG0B4S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B4S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B4S2",
        DDRPHY_INITENG0_SEQUENCEREG0B4S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B5S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B5S0",
        DDRPHY_INITENG0_SEQUENCEREG0B5S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B5S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B5S1",
        DDRPHY_INITENG0_SEQUENCEREG0B5S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B5S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B5S2",
        DDRPHY_INITENG0_SEQUENCEREG0B5S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B6S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B6S0",
        DDRPHY_INITENG0_SEQUENCEREG0B6S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B6S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B6S1",
        DDRPHY_INITENG0_SEQUENCEREG0B6S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B6S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B6S2",
        DDRPHY_INITENG0_SEQUENCEREG0B6S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B7S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B7S0",
        DDRPHY_INITENG0_SEQUENCEREG0B7S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B7S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B7S1",
        DDRPHY_INITENG0_SEQUENCEREG0B7S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B7S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B7S2",
        DDRPHY_INITENG0_SEQUENCEREG0B7S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B8S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B8S0",
        DDRPHY_INITENG0_SEQUENCEREG0B8S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B8S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B8S1",
        DDRPHY_INITENG0_SEQUENCEREG0B8S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B8S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B8S2",
        DDRPHY_INITENG0_SEQUENCEREG0B8S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B9S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B9S0",
        DDRPHY_INITENG0_SEQUENCEREG0B9S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B9S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B9S1",
        DDRPHY_INITENG0_SEQUENCEREG0B9S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B9S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B9S2",
        DDRPHY_INITENG0_SEQUENCEREG0B9S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B10S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B10S0",
        DDRPHY_INITENG0_SEQUENCEREG0B10S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B10S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B10S1",
        DDRPHY_INITENG0_SEQUENCEREG0B10S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B10S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B10S2",
        DDRPHY_INITENG0_SEQUENCEREG0B10S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B11S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B11S0",
        DDRPHY_INITENG0_SEQUENCEREG0B11S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B11S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B11S1",
        DDRPHY_INITENG0_SEQUENCEREG0B11S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B11S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B11S2",
        DDRPHY_INITENG0_SEQUENCEREG0B11S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B12S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B12S0",
        DDRPHY_INITENG0_SEQUENCEREG0B12S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B12S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B12S1",
        DDRPHY_INITENG0_SEQUENCEREG0B12S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B12S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B12S2",
        DDRPHY_INITENG0_SEQUENCEREG0B12S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B13S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B13S0",
        DDRPHY_INITENG0_SEQUENCEREG0B13S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B13S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B13S1",
        DDRPHY_INITENG0_SEQUENCEREG0B13S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B13S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B13S2",
        DDRPHY_INITENG0_SEQUENCEREG0B13S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B14S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B14S0",
        DDRPHY_INITENG0_SEQUENCEREG0B14S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B14S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B14S1",
        DDRPHY_INITENG0_SEQUENCEREG0B14S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B14S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B14S2",
        DDRPHY_INITENG0_SEQUENCEREG0B14S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B15S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B15S0",
        DDRPHY_INITENG0_SEQUENCEREG0B15S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B15S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B15S1",
        DDRPHY_INITENG0_SEQUENCEREG0B15S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B15S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B15S2",
        DDRPHY_INITENG0_SEQUENCEREG0B15S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B16S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B16S0",
        DDRPHY_INITENG0_SEQUENCEREG0B16S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B16S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B16S1",
        DDRPHY_INITENG0_SEQUENCEREG0B16S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B16S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B16S2",
        DDRPHY_INITENG0_SEQUENCEREG0B16S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B17S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B17S0",
        DDRPHY_INITENG0_SEQUENCEREG0B17S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B17S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B17S1",
        DDRPHY_INITENG0_SEQUENCEREG0B17S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B17S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B17S2",
        DDRPHY_INITENG0_SEQUENCEREG0B17S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B18S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B18S0",
        DDRPHY_INITENG0_SEQUENCEREG0B18S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B18S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B18S1",
        DDRPHY_INITENG0_SEQUENCEREG0B18S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B18S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B18S2",
        DDRPHY_INITENG0_SEQUENCEREG0B18S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B19S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B19S0",
        DDRPHY_INITENG0_SEQUENCEREG0B19S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B19S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B19S1",
        DDRPHY_INITENG0_SEQUENCEREG0B19S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B19S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B19S2",
        DDRPHY_INITENG0_SEQUENCEREG0B19S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B20S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B20S0",
        DDRPHY_INITENG0_SEQUENCEREG0B20S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B20S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B20S1",
        DDRPHY_INITENG0_SEQUENCEREG0B20S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B20S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B20S2",
        DDRPHY_INITENG0_SEQUENCEREG0B20S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B21S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B21S0",
        DDRPHY_INITENG0_SEQUENCEREG0B21S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B21S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B21S1",
        DDRPHY_INITENG0_SEQUENCEREG0B21S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B21S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B21S2",
        DDRPHY_INITENG0_SEQUENCEREG0B21S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B22S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B22S0",
        DDRPHY_INITENG0_SEQUENCEREG0B22S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B22S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B22S1",
        DDRPHY_INITENG0_SEQUENCEREG0B22S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B22S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B22S2",
        DDRPHY_INITENG0_SEQUENCEREG0B22S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B23S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B23S0",
        DDRPHY_INITENG0_SEQUENCEREG0B23S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B23S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B23S1",
        DDRPHY_INITENG0_SEQUENCEREG0B23S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B23S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B23S2",
        DDRPHY_INITENG0_SEQUENCEREG0B23S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B24S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B24S0",
        DDRPHY_INITENG0_SEQUENCEREG0B24S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B24S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B24S1",
        DDRPHY_INITENG0_SEQUENCEREG0B24S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B24S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B24S2",
        DDRPHY_INITENG0_SEQUENCEREG0B24S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B25S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B25S0",
        DDRPHY_INITENG0_SEQUENCEREG0B25S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B25S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B25S1",
        DDRPHY_INITENG0_SEQUENCEREG0B25S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B25S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B25S2",
        DDRPHY_INITENG0_SEQUENCEREG0B25S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B26S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B26S0",
        DDRPHY_INITENG0_SEQUENCEREG0B26S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B26S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B26S1",
        DDRPHY_INITENG0_SEQUENCEREG0B26S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B26S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B26S2",
        DDRPHY_INITENG0_SEQUENCEREG0B26S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B27S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B27S0",
        DDRPHY_INITENG0_SEQUENCEREG0B27S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B27S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B27S1",
        DDRPHY_INITENG0_SEQUENCEREG0B27S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B27S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B27S2",
        DDRPHY_INITENG0_SEQUENCEREG0B27S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B28S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B28S0",
        DDRPHY_INITENG0_SEQUENCEREG0B28S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B28S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B28S1",
        DDRPHY_INITENG0_SEQUENCEREG0B28S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B28S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B28S2",
        DDRPHY_INITENG0_SEQUENCEREG0B28S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B29S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B29S0",
        DDRPHY_INITENG0_SEQUENCEREG0B29S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B29S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B29S1",
        DDRPHY_INITENG0_SEQUENCEREG0B29S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B29S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B29S2",
        DDRPHY_INITENG0_SEQUENCEREG0B29S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B30S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B30S0",
        DDRPHY_INITENG0_SEQUENCEREG0B30S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B30S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B30S1",
        DDRPHY_INITENG0_SEQUENCEREG0B30S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B30S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B30S2",
        DDRPHY_INITENG0_SEQUENCEREG0B30S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B31S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B31S0",
        DDRPHY_INITENG0_SEQUENCEREG0B31S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B31S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B31S1",
        DDRPHY_INITENG0_SEQUENCEREG0B31S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B31S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B31S2",
        DDRPHY_INITENG0_SEQUENCEREG0B31S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B32S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B32S0",
        DDRPHY_INITENG0_SEQUENCEREG0B32S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B32S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B32S1",
        DDRPHY_INITENG0_SEQUENCEREG0B32S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B32S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B32S2",
        DDRPHY_INITENG0_SEQUENCEREG0B32S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B33S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B33S0",
        DDRPHY_INITENG0_SEQUENCEREG0B33S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B33S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B33S1",
        DDRPHY_INITENG0_SEQUENCEREG0B33S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B33S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B33S2",
        DDRPHY_INITENG0_SEQUENCEREG0B33S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B34S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B34S0",
        DDRPHY_INITENG0_SEQUENCEREG0B34S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B34S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B34S1",
        DDRPHY_INITENG0_SEQUENCEREG0B34S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B34S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B34S2",
        DDRPHY_INITENG0_SEQUENCEREG0B34S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B35S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B35S0",
        DDRPHY_INITENG0_SEQUENCEREG0B35S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B35S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B35S1",
        DDRPHY_INITENG0_SEQUENCEREG0B35S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B35S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B35S2",
        DDRPHY_INITENG0_SEQUENCEREG0B35S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B36S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B36S0",
        DDRPHY_INITENG0_SEQUENCEREG0B36S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B36S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B36S1",
        DDRPHY_INITENG0_SEQUENCEREG0B36S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B36S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B36S2",
        DDRPHY_INITENG0_SEQUENCEREG0B36S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B37S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B37S0",
        DDRPHY_INITENG0_SEQUENCEREG0B37S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B37S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B37S1",
        DDRPHY_INITENG0_SEQUENCEREG0B37S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B37S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B37S2",
        DDRPHY_INITENG0_SEQUENCEREG0B37S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B38S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B38S0",
        DDRPHY_INITENG0_SEQUENCEREG0B38S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B38S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B38S1",
        DDRPHY_INITENG0_SEQUENCEREG0B38S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B38S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B38S2",
        DDRPHY_INITENG0_SEQUENCEREG0B38S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B39S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B39S0",
        DDRPHY_INITENG0_SEQUENCEREG0B39S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B39S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B39S1",
        DDRPHY_INITENG0_SEQUENCEREG0B39S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B39S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B39S2",
        DDRPHY_INITENG0_SEQUENCEREG0B39S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B40S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B40S0",
        DDRPHY_INITENG0_SEQUENCEREG0B40S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B40S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B40S1",
        DDRPHY_INITENG0_SEQUENCEREG0B40S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B40S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B40S2",
        DDRPHY_INITENG0_SEQUENCEREG0B40S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B41S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B41S0",
        DDRPHY_INITENG0_SEQUENCEREG0B41S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B41S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B41S1",
        DDRPHY_INITENG0_SEQUENCEREG0B41S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B41S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B41S2",
        DDRPHY_INITENG0_SEQUENCEREG0B41S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B42S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B42S0",
        DDRPHY_INITENG0_SEQUENCEREG0B42S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B42S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B42S1",
        DDRPHY_INITENG0_SEQUENCEREG0B42S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B42S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B42S2",
        DDRPHY_INITENG0_SEQUENCEREG0B42S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B43S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B43S0",
        DDRPHY_INITENG0_SEQUENCEREG0B43S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B43S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B43S1",
        DDRPHY_INITENG0_SEQUENCEREG0B43S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B43S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B43S2",
        DDRPHY_INITENG0_SEQUENCEREG0B43S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B44S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B44S0",
        DDRPHY_INITENG0_SEQUENCEREG0B44S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B44S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B44S1",
        DDRPHY_INITENG0_SEQUENCEREG0B44S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B44S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B44S2",
        DDRPHY_INITENG0_SEQUENCEREG0B44S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B45S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B45S0",
        DDRPHY_INITENG0_SEQUENCEREG0B45S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B45S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B45S1",
        DDRPHY_INITENG0_SEQUENCEREG0B45S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B45S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B45S2",
        DDRPHY_INITENG0_SEQUENCEREG0B45S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B46S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B46S0",
        DDRPHY_INITENG0_SEQUENCEREG0B46S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B46S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B46S1",
        DDRPHY_INITENG0_SEQUENCEREG0B46S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B46S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B46S2",
        DDRPHY_INITENG0_SEQUENCEREG0B46S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B47S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B47S0",
        DDRPHY_INITENG0_SEQUENCEREG0B47S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B47S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B47S1",
        DDRPHY_INITENG0_SEQUENCEREG0B47S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B47S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B47S2",
        DDRPHY_INITENG0_SEQUENCEREG0B47S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B48S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B48S0",
        DDRPHY_INITENG0_SEQUENCEREG0B48S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B48S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B48S1",
        DDRPHY_INITENG0_SEQUENCEREG0B48S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B48S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B48S2",
        DDRPHY_INITENG0_SEQUENCEREG0B48S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B49S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B49S0",
        DDRPHY_INITENG0_SEQUENCEREG0B49S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B49S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B49S1",
        DDRPHY_INITENG0_SEQUENCEREG0B49S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B49S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B49S2",
        DDRPHY_INITENG0_SEQUENCEREG0B49S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B50S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B50S0",
        DDRPHY_INITENG0_SEQUENCEREG0B50S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B50S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B50S1",
        DDRPHY_INITENG0_SEQUENCEREG0B50S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B50S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B50S2",
        DDRPHY_INITENG0_SEQUENCEREG0B50S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B51S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B51S0",
        DDRPHY_INITENG0_SEQUENCEREG0B51S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B51S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B51S1",
        DDRPHY_INITENG0_SEQUENCEREG0B51S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B51S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B51S2",
        DDRPHY_INITENG0_SEQUENCEREG0B51S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B52S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B52S0",
        DDRPHY_INITENG0_SEQUENCEREG0B52S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B52S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B52S1",
        DDRPHY_INITENG0_SEQUENCEREG0B52S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B52S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B52S2",
        DDRPHY_INITENG0_SEQUENCEREG0B52S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B53S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B53S0",
        DDRPHY_INITENG0_SEQUENCEREG0B53S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B53S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B53S1",
        DDRPHY_INITENG0_SEQUENCEREG0B53S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B53S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B53S2",
        DDRPHY_INITENG0_SEQUENCEREG0B53S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B54S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B54S0",
        DDRPHY_INITENG0_SEQUENCEREG0B54S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B54S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B54S1",
        DDRPHY_INITENG0_SEQUENCEREG0B54S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B54S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B54S2",
        DDRPHY_INITENG0_SEQUENCEREG0B54S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B55S0_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B55S0",
        DDRPHY_INITENG0_SEQUENCEREG0B55S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B55S1_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B55S1",
        DDRPHY_INITENG0_SEQUENCEREG0B55S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQUENCEREG0B55S2_OFFSET,
        "DDRPHY_INITENG0_SEQUENCEREG0B55S2",
        DDRPHY_INITENG0_SEQUENCEREG0B55S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_POSTSEQUENCEREG0B0S0_OFFSET,
        "DDRPHY_INITENG0_POSTSEQUENCEREG0B0S0",
        DDRPHY_INITENG0_POSTSEQUENCEREG0B0S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_POSTSEQUENCEREG0B0S1_OFFSET,
        "DDRPHY_INITENG0_POSTSEQUENCEREG0B0S1",
        DDRPHY_INITENG0_POSTSEQUENCEREG0B0S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_POSTSEQUENCEREG0B0S2_OFFSET,
        "DDRPHY_INITENG0_POSTSEQUENCEREG0B0S2",
        DDRPHY_INITENG0_POSTSEQUENCEREG0B0S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_POSTSEQUENCEREG0B1S0_OFFSET,
        "DDRPHY_INITENG0_POSTSEQUENCEREG0B1S0",
        DDRPHY_INITENG0_POSTSEQUENCEREG0B1S0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_POSTSEQUENCEREG0B1S1_OFFSET,
        "DDRPHY_INITENG0_POSTSEQUENCEREG0B1S1",
        DDRPHY_INITENG0_POSTSEQUENCEREG0B1S1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_POSTSEQUENCEREG0B1S2_OFFSET,
        "DDRPHY_INITENG0_POSTSEQUENCEREG0B1S2",
        DDRPHY_INITENG0_POSTSEQUENCEREG0B1S2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_APBONLY0_SEQUENCEROVERRIDE_OFFSET,
        "DDRPHY_APBONLY0_SEQUENCEROVERRIDE",
        DDRPHY_APBONLY0_SEQUENCEROVERRIDE_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_STARTVECTOR0B0_OFFSET,
        "DDRPHY_INITENG0_STARTVECTOR0B0",
        DDRPHY_INITENG0_STARTVECTOR0B0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_STARTVECTOR0B15_OFFSET,
        "DDRPHY_INITENG0_STARTVECTOR0B15",
        DDRPHY_INITENG0_STARTVECTOR0B15_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIFREQXLAT0_OFFSET,
        "DDRPHY_MASTER0_DFIFREQXLAT0", DDRPHY_MASTER0_DFIFREQXLAT0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIFREQXLAT1_OFFSET,
        "DDRPHY_MASTER0_DFIFREQXLAT1", DDRPHY_MASTER0_DFIFREQXLAT1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIFREQXLAT2_OFFSET,
        "DDRPHY_MASTER0_DFIFREQXLAT2", DDRPHY_MASTER0_DFIFREQXLAT2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIFREQXLAT3_OFFSET,
        "DDRPHY_MASTER0_DFIFREQXLAT3", DDRPHY_MASTER0_DFIFREQXLAT3_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIFREQXLAT4_OFFSET,
        "DDRPHY_MASTER0_DFIFREQXLAT4", DDRPHY_MASTER0_DFIFREQXLAT4_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIFREQXLAT5_OFFSET,
        "DDRPHY_MASTER0_DFIFREQXLAT5", DDRPHY_MASTER0_DFIFREQXLAT5_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIFREQXLAT6_OFFSET,
        "DDRPHY_MASTER0_DFIFREQXLAT6", DDRPHY_MASTER0_DFIFREQXLAT6_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_MASTER0_DFIFREQXLAT7_OFFSET,
        "DDRPHY_MASTER0_DFIFREQXLAT7", DDRPHY_MASTER0_DFIFREQXLAT7_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG0_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG0",
        DDRPHY_INITENG0_SEQ0BDISABLEFLAG0_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG1_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG1",
        DDRPHY_INITENG0_SEQ0BDISABLEFLAG1_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG2_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG2",
        DDRPHY_INITENG0_SEQ0BDISABLEFLAG2_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG3_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG3",
        DDRPHY_INITENG0_SEQ0BDISABLEFLAG3_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG4_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG4",
        DDRPHY_INITENG0_SEQ0BDISABLEFLAG4_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG5_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG5",
        DDRPHY_INITENG0_SEQ0BDISABLEFLAG5_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG6_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG6",
        DDRPHY_INITENG0_SEQ0BDISABLEFLAG6_VAL);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG7_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG7",
        DDRPHY_INITENG0_SEQ0BDISABLEFLAG7_VAL);

    mddr_phy_set_seq0bdly_regs(mddr_base_addr);

    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG4_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG4", 0x0);
    mddr_set_reg(mddr_base_addr + DDRPHY_INITENG0_SEQ0BDISABLEFLAG5_OFFSET,
        "DDRPHY_INITENG0_SEQ0BDISABLEFLAG5", 0xFFFF);

}


/*!****************************************************************************
*
* @par Description:
*    This function builds dmem register for all valid frequencies
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_build_dmem_regs(mddr_settings_t *mddr_settings_ptr)
{
    //---------------------------------------------------------------
    // dmem3: dimm_type, number of dq bits
    uint8_t dimm_type, dq_bits;
    dimm_type = PHY_DDR4_RDIMM_TYPE;

    if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
    {
        dimm_type = PHY_DDR4_LRDIMM_TYPE;
    }
    else if (common_cfg.mod_type != SPD_MODULE_TYPE_RDIMM)
    {
        // ToDo: handle error in this case?
        // monaco_log(CRITICAL, "  Error invalid module type detected, using "
        //         "RDIMM for channel %d.\n", hddrss[ddr_chan]);
    }

    if (common_cfg.has_ecc)
    {
        dq_bits = PHY_DATA_BITS + PHY_ECC_BITS;
    }
    else
    {
        dq_bits = PHY_DATA_BITS;
    }

    mddr_reg_vals.phy_regs.dmem3_val =
        (dq_bits << PHY_DQ_BITS___S) | dimm_type;


    //---------------------------------------------------------------
    // dmem6: CS test fail indicator, phy config (1T, 2T)
// TODO CA stretch control in SI per freq?... also dmem, dynadrtri,
    uint16_t dmem6_val = 0;

    if (mddr_settings_ptr->ca_stretch == CA_STRETCH_2T)
    {
        dmem6_val = 0x1 << DMEM_NIBBLE___S;
    }

    mddr_reg_vals.phy_regs.dmem6_val = dmem6_val;

    //---------------------------------------------------------------
    // dmem8: vebosity control, Rx 2D training option
    uint8_t rx2d_opt = DDRPHY_VREF2D_OPT & DMEM8_RX2D_OPT___M;

    uint16_t dmem8_val = (rx2d_opt << DMEM_NIBBLE___S);

    mddr_reg_vals.phy_regs.dmem8_val = dmem8_val;

    //---------------------------------------------------------------
    // dmem9: Tx 2D training option, share 2D Vref result flag
    uint8_t tx2d_opt =
        (DDRPHY_VREF2D_OPT >> DMEM_NIBBLE___S) & DMEM9_TX2D_OPT___M;

    uint16_t dmem9_val = (SHARE_2D_VREF_RESULT << DMEM_NIBBLE___S) | tx2d_opt;

    mddr_reg_vals.phy_regs.dmem9_val = dmem9_val;

    //---------------------------------------------------------------
    // dmem10: delay weight 2D, voltage weight 2D
    uint16_t dmem10_val, delay_weight, volt_weight;

    delay_weight = DDRPHY_WEIGHT_2D & DELAY_WEIGHT___M;

    volt_weight = (DDRPHY_WEIGHT_2D >> DMEM_NIBBLE___S) & VOLT_WEIGHT___M;

    dmem10_val = (volt_weight << DMEM_NIBBLE___S) | delay_weight;

    mddr_reg_vals.phy_regs.dmem10_val = dmem10_val;

    //---------------------------------------------------------------
    // dmem15: Margin added to passing trained DFI max read latency
    mddr_reg_vals.phy_regs.dmem15_val = DFI_MRL_MARGIN;

    //---------------------------------------------------------------
    // dmem40:
    mddr_reg_vals.phy_regs.dmem40_val = mddr_settings_ptr->phy_config.ddrphy_mem40;

    //---------------------------------------------------------------
    // dmem41:
    mddr_reg_vals.phy_regs.dmem41_val = mddr_settings_ptr->phy_config.ddrphy_mem41;

    //---------------------------------------------------------------
    // dmem42:
    mddr_reg_vals.phy_regs.dmem42_val = mddr_settings_ptr->phy_config.ddrphy_mem42;

    //---------------------------------------------------------------
    // dmem43:
    mddr_reg_vals.phy_regs.dmem43_val = (mddr_settings_ptr->phy_config.ddrphy_mem43 & DDRPHY_DMEM43___M)
                                        | (mddr_settings_ptr->phy_config.ddrphy_xcnt & DDRPHY_DMEM43_XCNT___M);

    //---------------------------------------------------------------
    // dmem504: alternate cas latency without tDBI
    uint8_t cl_adj;
    uint16_t alt_cas_l_val, mr0_cl;

    cl_adj = latencies.cl - latencies.tdbi;

    if (cl_adj <= 9)
    {
        mr0_cl = 0x0;
    }
    else if (cl_adj == 10)
    {
        mr0_cl = 0x4;
    }
    else if (cl_adj == 11)
    {
        mr0_cl = 0x10;
    }
    else if (cl_adj == 12)
    {
        mr0_cl = 0x14;
    }
    else if (cl_adj == 13)
    {
        mr0_cl = 0x20;
    }
    else if (cl_adj == 14)
    {
        mr0_cl = 0x24;
    }
    else if (cl_adj == 15)
    {
        mr0_cl = 0x30;
    }
    else if (cl_adj == 16)
    {
        mr0_cl = 0x34;
    }
    else if (cl_adj == 17)
    {
        mr0_cl = 0x64;
    }
    else if (cl_adj == 18)
    {
        mr0_cl = 0x40;
    }
    else if (cl_adj == 19)
    {
        mr0_cl = 0x70;
    }
    else if (cl_adj == 20)
    {
        mr0_cl = 0x44;
    }
    else if (cl_adj == 21)
    {
        mr0_cl = 0x74;
    }
    else if (cl_adj == 22)
    {
        mr0_cl = 0x50;
    }
    else if (cl_adj == 22)
    {
        mr0_cl = 0x50;
    }
    else if (cl_adj == 23)
    {
        mr0_cl = 0x60;
    }
    else if (cl_adj == 24)
    {
        mr0_cl = 0x54;
    }
    else if (cl_adj == 25)
    {
        mr0_cl = 0x1000;
    }
    else if (cl_adj == 26)
    {
        mr0_cl = 0x1004;
    }
    else if (cl_adj == 27)
    {
        mr0_cl = 0x1010;
    }
    else if (cl_adj == 28)
    {
        mr0_cl = 0x1014;
    }
    else if (cl_adj == 29)
    {
        mr0_cl = 0x1020;
    }
    else if (cl_adj == 30)
    {
        mr0_cl = 0x1024;
    }
    else if (cl_adj == 31)
    {
        mr0_cl = 0x1030;
    }
    else //if (cl_adj == 32)
    {
        mr0_cl = 0x1034;
    }

    alt_cas_l_val = mr0_cl;

    // if valid read DBI, enable alt_cas_l
    if ((common_cfg.sdram_width == SPD_SDRAM_WIDTH_X8) &&
       ((mddr_settings_ptr->dbi_mode == DDR_DBI_READ) ||
            (mddr_settings_ptr->dbi_mode == DDR_DBI_READ_WRITE)))
    {
        alt_cas_l_val |= 0x1;      // set enable bit
    }

    mddr_reg_vals.phy_regs.dmem504_val = alt_cas_l_val;

    //---------------------------------------------------------------
    // dmem505: alternate write cas latency 2tCK WR preamble

    uint16_t alt_wcas_l_val = 0;

    // if 2tCK WR preamble
    if ((mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE) ||
       (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE_READ))
    {
        uint8_t cwl = latencies.cwl;
        uint8_t cwl_adj;
        uint16_t mr2_cwl = 0;

        if (cwl >= 9)           // cwl with 2tCK WR added is valid
        {
            cwl_adj = cwl - 2;  // remove adder for 2tCK WR preamble

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
                alt_wcas_l_val = 0x1 | (mr2_cwl << 3);     // enable
            }
        }
    }
    else
    {
        alt_wcas_l_val = latencies.mc_mr2_cwl << 3;
    }

    mddr_reg_vals.phy_regs.dmem505_val = alt_wcas_l_val;
}


/*!****************************************************************************
*
* @par Description:
*    This function sets the PHY sequence delay register for valid pstates.
*
*                                  @param
*    mddr_base_addr         The base address of the configuration registers for
*                            the MDDR block.
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_set_seq0bdly_regs(uint64_t mddr_base_addr)
{
    char reg_name[PHY_MAX_REG_NAME_LENGTH];
    uint64_t reg_addr;
    uint32_t reg_offset;
    uint64_t seq0bdly0_base =
        mddr_base_addr + DDRPHY_MASTER0_SEQ0BDLY0_P0_OFFSET;

    uint8_t p, d;   // pstates, delay #
    for (p=0; p < DDR_MAX_FREQ_POOL_TARGET; p++)
    {
        for (d=0; d < NUM_SEQ0BDLYS; d++)
        {
            reg_offset = (0x400000 * p) + (0x4 * d);
            reg_addr = seq0bdly0_base + reg_offset;

            snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
              "DDRPHY_MASTER0_SEQ0BDLY%d_P%d", d, p);

            switch (d)
            {
                case 0:
                    mddr_set_reg(reg_addr, reg_name,
                        mddr_reg_vals.phy_regs.seq0bdly0_val[p]);
                    break;
                case 1:
                    mddr_set_reg(reg_addr, reg_name,
                        mddr_reg_vals.phy_regs.seq0bdly1_val[p]);
                    break;
                case 2:
                    mddr_set_reg(reg_addr, reg_name,
                        mddr_reg_vals.phy_regs.seq0bdly2_val[p]);
                    break;
                case 3:
                    mddr_set_reg(reg_addr, reg_name,
                        mddr_reg_vals.phy_regs.seq0bdly3_val[p]);
                    break;
                default:
                    break;
            }
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function sets the PHY signal integrity registers for the current
*    DDR channel.
*
*                                  @param
*    ddr_chan           Current DDR channel
*
* @return
*    none
*
* @author
*    mwuu
*
******************************************************************************/
void mddr_phy_set_si_regs(uint8_t ddr_chan)
{
    const uint8_t imp_val[MAX_NUM_PHY_IMP_VALS] = {
      0x0,  0x1, 0x2, 0x3, 0x6, 0x7, 0xA, 0xB, 0xE,
      0xF, 0x1A,0x1B,0x1E,0x1F,0x3A,0x3B,0x3E,0x3F
    };

    const uint8_t odt_val[MAX_NUM_PHY_ODT_VALS] = {
       0x0,  0x1, 0x2, 0x3, 0x8, 0x9, 0xA, 0xB,0x18,
       0x19,0x1A,0x1B,0x38,0x39,0x3A,0x3B,0x3E,0x3F
    };

    uint64_t mddr_base_addr =  mddr_base_addrs[ddr_chan];

// ODT timing control, always on/off
    uint16_t procodtctl_val = PROCODTALWAYSOFF;

// ODT start delay DQS/DQ, ODT tail width DQS/DQ
    uint16_t procodttimectl_val;
    uint8_t startdelaydqs, tailwidthdqs;

    startdelaydqs = PROCODTTIMECTL_STARTDELAYDQS;
    tailwidthdqs = PROCODTTIMECTL_TAILWIDTHDQS;

    procodttimectl_val = (
        startdelaydqs & PROCODTTIMECTL_STARTDELAYDQS___M
    ) << PROCODTTIMECTL_STARTDELAYDQS___S;

    procodttimectl_val |= (
        tailwidthdqs & PROCODTTIMECTL_TAILWIDTHDQS___M
    ) << PROCODTTIMECTL_TAILWIDTHDQS___S;

// TX impedance dq
    uint16_t txeqimpedancedq_val, dq_imp;
    uint8_t idx, imp_n, imp_p;

    dq_imp = si_data[ddr_chan].mc_imp[1];

    // drive strength w/o equalization, register misnamed
    if ((dq_imp == 0) || (dq_imp > MAX_PHY_IMP_VAL))
    {
        idx = 0;
    }
    else if (dq_imp <= MIN_PHY_IMP_VAL)
    {
        idx = MAX_NUM_PHY_IMP_VALS - 1;
    }
    else
    {
        // 480/dq_imp; x_val[idx] = reg_val
        // round to nearest int
        idx = (MAX_PHY_IMP_VAL + (dq_imp / 2)) / dq_imp;

        if (idx >= MAX_NUM_PHY_IMP_VALS)
            idx = MAX_NUM_PHY_IMP_VALS - 1;
    }

    imp_p = imp_val[idx];
    imp_p = imp_p & TXEQIMPEDANCE_DRVSTRENFSDQP___M;
    imp_n = imp_p;

    txeqimpedancedq_val = imp_p;
    txeqimpedancedq_val |= imp_n << TXEQIMPEDANCE_DRVSTRENFSDQN___S;

// Data receiver termination, ODT
    uint16_t txodtdrvstren_val, dq_term;
    uint8_t term_n, term_p;

    dq_term = si_data[ddr_chan].mc_term;

    if ((dq_term == 0) || (dq_term > MAX_PHY_ODT_VAL))
    {
        idx = 0;
    }
    else if (dq_term <= MIN_PHY_ODT_VAL)
    {
        idx = MAX_NUM_PHY_ODT_VALS - 1;
    }
    else
    {
        // 480/dq_term; x_val[idx] = reg_val
        // round to nearest int
        idx = (MAX_PHY_ODT_VAL + (dq_term / 2)) / dq_term;

        if (idx >= MAX_NUM_PHY_ODT_VALS)
            idx = MAX_NUM_PHY_ODT_VALS - 1;
    }

    term_p = odt_val[idx];
    term_p = term_p & TXODTDRVSTREN_ODTSTRENP___M;
    term_n = 0;     // Hi-Z since this is DDR4

    txodtdrvstren_val = term_p;
    txodtdrvstren_val |= term_n << TXODTDRVSTREN_ODTSTRENN___S;

// Slew rate for data drivers, Tx slew rate
    uint16_t txslewrate_val;
    uint8_t dqslew_p, dqslew_n, dqslew;
    uint8_t txpredrvmode;

    dqslew = si_data[ddr_chan].mc_slew[1];
    dqslew_p = dqslew & TXSLEWRATE___M;
    txpredrvmode = TXSLEWRATE_TXPREDRV;

    dqslew_n = (dqslew >> TXSLEWRATE_TXPREN___S) & TXSLEWRATE___M;
    txpredrvmode = txpredrvmode & TXSLEWRATE_TXPREDRV_MODE___M;

    txslewrate_val = (dqslew_n << TXSLEWRATE_TXPREN___S) | dqslew_p;
    txslewrate_val |= (txpredrvmode << TXSLEWRATE_TXPREDRV_MODE___S);

// Tx equalization mode
    uint16_t txequalizationmode_val;
    uint8_t txeqmode;

    txeqmode=TXEQMODE_OFF;
    txequalizationmode_val = txeqmode & TXEQUALIZATIONMODE_TXEQMODE___M;

// Data receiver controls
    uint16_t dqdqsrcvcntrl_val;
    uint8_t selanalogvref, extvrefrange, dfectrl, majormodedbyte, gaincurradj;

    selanalogvref = DQDQSRCVCNTRL_SELANALOGVREF;
    extvrefrange = DQDQSRCVCNTRL_EXTVREFRANGE;
    dfectrl = DQDQSRCVCNTRL_DFECTRL;
    gaincurradj = DQDQSRCVCNTRL_GAINCURRADJ;

    if (common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
    {
        majormodedbyte = DQDQSRCVCNTRL_MAJORMODEDBYTE_DDR4;
    }
    else
    {
        majormodedbyte = DQDQSRCVCNTRL_MAJORMODEDBYTE_DDR3;
    }

    dqdqsrcvcntrl_val = (
        selanalogvref & DQDQSRCVCNTRL_SELANALOGVREF___M
    ) << DQDQSRCVCNTRL_SELANALOGVREF___S;

    dqdqsrcvcntrl_val |= (
        extvrefrange & DQDQSRCVCNTRL_EXTVREFRANGE___M
    ) << DQDQSRCVCNTRL_EXTVREFRANGE___S;

    dqdqsrcvcntrl_val |= (
        dfectrl & DQDQSRCVCNTRL_DFECTRL___M
    ) << DQDQSRCVCNTRL_DFECTRL___S;

    dqdqsrcvcntrl_val |= (
        majormodedbyte & DQDQSRCVCNTRL_MAJORMODEDBYTE___M
    ) << DQDQSRCVCNTRL_MAJORMODEDBYTE___S;

    dqdqsrcvcntrl_val |= (
        gaincurradj & DQDQSRCVCNTRL_GAINCURRADJ___M
    ) << DQDQSRCVCNTRL_GAINCURRADJ___S;

// Address/command impedance
    uint16_t atximpedance_val;
    uint8_t aimp_p, aimp_n, aimp;

    aimp = si_data[ddr_chan].mc_imp[0];

    if (aimp >= 120)
    {
        aimp_p = 0;
    }
    else if (aimp >= 60)
    {
        aimp_p = 0x1;
    }
    else if (aimp >= 40)
    {
        aimp_p = 0x3;
    }
    else if (aimp >= 30)
    {
        aimp_p = 0x7;
    }
    else if (aimp >= 24)
    {
        aimp_p = 0xF;
    }
    else    // 20 ohms
    {
        aimp_p = 0x1F;
    }

    aimp_p = aimp_p & ATXIMPEDANCE_ADRVSTRENP___M;
    aimp_n = aimp_p;

    atximpedance_val = (aimp_n << ATXIMPEDANCE_ADRVSTRENN___S) | aimp_p;

// Address/command slew
    uint16_t atxslewrate_val, ck_atxslewrate_val;
    uint8_t aslew_p, aslew_n, aslew;
    uint8_t atxpredrvmode, ckpredrvmode;

    aslew = si_data[ddr_chan].mc_slew[0];
    aslew_p = aslew & ATXSLEWRATE_ATXPREP___M;
    aslew_n = (aslew >> ATXSLEWRATE_ATXPREN___S) & ATXSLEWRATE_ATXPREP___M;
    atxpredrvmode =
        ATXSLEWRATE_ATXPREDRV_MODE & ATXSLEWRATE_ATXPREDRV_MODE___M;
    ckpredrvmode =
        CK_ATXSLEWRATE_ATXPREDRV_MODE & ATXSLEWRATE_ATXPREDRV_MODE___M;

    atxslewrate_val = (aslew_n << ATXSLEWRATE_ATXPREN___S) | aslew_p;
    ck_atxslewrate_val = atxslewrate_val;
    atxslewrate_val |= (atxpredrvmode << ATXSLEWRATE_ATXPREDRV_MODE___S);
    ck_atxslewrate_val |= (ckpredrvmode << ATXSLEWRATE_ATXPREDRV_MODE___S);

    ///////////  Write registers  ///////////////////////////////
    uint8_t p, b, n, a;

    uint8_t num_valid_pstates = 1;
    uint8_t num_drams_per_byte;
    uint64_t reg_addr;
    char reg_name[PHY_MAX_REG_NAME_LENGTH];

    uint64_t procodtctl_base =
        mddr_base_addr + DDRPHY_DBYTE0_PROCODTCTL_P0_OFFSET;

    uint64_t procodttimectl_base =
        mddr_base_addr + DDRPHY_DBYTE0_PROCODTTIMECTL_P0_OFFSET;

    uint64_t txequalizationmode_base =
        mddr_base_addr + DDRPHY_DBYTE0_TXEQUALIZATIONMODE_P0_OFFSET;

    uint64_t txodtdrvstren_base =
        mddr_base_addr + DDRPHY_DBYTE0_TXODTDRVSTREN_B0_P0_OFFSET;

    uint64_t txslewrate_base =
        mddr_base_addr + DDRPHY_DBYTE0_TXSLEWRATE_B0_P0_OFFSET;

    uint64_t txeqimpedancedq_base =
        mddr_base_addr + DDRPHY_DBYTE0_TXEQIMPEDANCEDQ_B0_P0_OFFSET;

    uint64_t dqdqsrcvcntrl_base =
        mddr_base_addr + DDRPHY_DBYTE0_DQDQSRCVCNTRL_B0_P0_OFFSET;

    uint64_t atximpedance_base =
        mddr_base_addr + DDRPHY_ANIB0_ATXIMPEDANCE_OFFSET;

    uint64_t atxslewrate_base =
        mddr_base_addr + DDRPHY_ANIB0_ATXSLEWRATE_OFFSET;

    uint64_t pb_base, pbn_base;

    num_drams_per_byte = 0x2;

    for (p=0; p < num_valid_pstates; p++)   // pstates
    {
        for (b=0; b < MAX_NUM_BYTES; b++)   // bytes
        {
            pb_base = (0x400000 * p) + (0x4000 * b);

            snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
              "DDRPHY_DBYTE%d_PROCODTCTL_P%d", b, p);

            reg_addr = procodtctl_base + pb_base;
            mddr_set_reg(reg_addr, reg_name, procodtctl_val);

            snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
              "DDRPHY_DBYTE%d_PROCODTTIMECTL_P%d", b, p);

            reg_addr = procodttimectl_base + pb_base;
            mddr_set_reg(reg_addr, reg_name, procodttimectl_val);

            snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
              "DDRPHY_DBYTE%d_TXEQUALIZATIONMODE_P%d", b, p);

            reg_addr = txequalizationmode_base + pb_base;
            mddr_set_reg(reg_addr, reg_name, txequalizationmode_val);

            for (n=0; n < num_drams_per_byte; n++)   // nibbles
            {
                pbn_base = pb_base + (0x400 * n);
                snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
                  "DDRPHY_DBYTE%d_TXODTDRVSTREN_B%d_P%d", b, n, p);

                reg_addr = txodtdrvstren_base + pbn_base;
                mddr_set_reg(reg_addr, reg_name, txodtdrvstren_val);

                snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
                  "DDRPHY_DBYTE%d_TXSLEWRATE_B%d_P%d", b, n, p);

                reg_addr = txslewrate_base + pbn_base;
                mddr_set_reg(reg_addr, reg_name, txslewrate_val);

                snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
                  "DDRPHY_DBYTE%d_TXEQIMPEDANCEDQ_B%d_P%d", b, n, p);

                reg_addr = txeqimpedancedq_base + pbn_base;
                mddr_set_reg(reg_addr, reg_name, txeqimpedancedq_val);

                snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
                  "DDRPHY_DBYTE%d_DQDQSRCVCNTRL_B%d_P%d", b, n, p);

                reg_addr = dqdqsrcvcntrl_base + pbn_base;
                mddr_set_reg(reg_addr, reg_name, dqdqsrcvcntrl_val);
            }
        }
    }

    uint8_t num_anib = 12;
    for (a=0; a < num_anib; a++)    // ANIB #
    {
        pbn_base = (0x4000 * a);

        snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
          "DDRPHY_ANIB%d_ATXIMPEDANCE", a);

        reg_addr = atximpedance_base + pbn_base;
        mddr_set_reg(reg_addr, reg_name, atximpedance_val);

        snprintf(reg_name, PHY_MAX_REG_NAME_LENGTH,
          "DDRPHY_ANIB%d_ATXSLEWRATE", a);

        reg_addr = atxslewrate_base + pbn_base;

        if ((a == ANIB_CK0_1_INSTANCE) || (a == ANIB_CK2_3_INSTANCE))
        {
            mddr_set_reg(reg_addr, reg_name, ck_atxslewrate_val);
        }
        else
        {
            mddr_set_reg(reg_addr, reg_name, atxslewrate_val);
        }
    }
}
