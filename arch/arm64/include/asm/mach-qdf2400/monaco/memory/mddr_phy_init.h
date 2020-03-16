#ifndef _MODULE_MDDR_PHY_INIT_H_
#define _MODULE_MDDR_PHY_INIT_H_

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
* @file mddr_phy_init.h
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


/******************************************************************************
* Defined Constants
******************************************************************************/
#define PHY_NUM_PSTATES                4
#define PHY_ODT_REGS                   3

#define PLL_CTRL2_GT_937p5_MHZ      0x18
#define PLL_CTRL2_GT_625_MHZ        0x19
#define PLL_CTRL2_GT_468p75_MHZ     0x0A
#define PLL_CTRL2_GT_312p5_MHZ      0x0B
#define PLL_CTRL2_GT_234p4_MHZ      0x06
#define PLL_CTRL2_LT_234p4_MHZ      0x07

#define MASTER0_CALBUSY              0x1

#define DLLGAINIV_LT_667MHZ          0x0
#define DLLGAINIV_LT_933MHZ          0x1
#define DLLGAINIV_GT_933MHZ          0x2

#define DLLGAINTV                    0xA
#define DLLGAINTV___S                  4
#define DLLGAINTV___M                0xF
#define DLLGAINIV___M                0xF

#define ARDPTRINITVAL_LT_933MHZ_UI     0
#define ARDPTRINITVAL_GT_933MHZ_UI     1

#define TWOTCKRXDQSPRE___S             0
#define TWOTCKTXDQSPRE___S             1
#define POSITIONDFEINIT___S            2
#define POSITIONDFEINIT              0x2

#define CLKDISVAL___S                  2
#define CLKDISVAL___M                0x3
#define CLKDISVAL                      1
#define CA_2T_MODE___S                 1
#define CA_2T_MODE___M               0x1
#define CA_2T_MODE                     1
#define DISDYNADRTRI___M             0x1
#define DISDYNADRTRI                   0

#define CS_DELAY_MAPPING_LRDIMM_DUAL_SLOT   0x50
#define CS_DELAY_MAPPING_LRDIMM_SINGLE_SLOT 0x00
#define CS_DELAY_MAPPING_NOT_LRDIMM         0xE4

#define X4_CONFIG_TRUE               0xF
#define X4_CONFIG_FALSE              0x0

#define PREAMBLE_MODE_DDR4           0x2
#define PREAMBLE_MODE_NOT_DDR4       0x0

#define CA_MODE_DDR4                 0x2
#define CA_MODE_NOT_DDR4             0x0

// below for init sequence
//------------------------------------------------------------
#define DDRPHY_INIT_ENGINE_DELAY_VAL0                     0x64
#define DDRPHY_INIT_ENGINE_DELAY_VAL1                     0xC8
#define DDRPHY_INIT_ENGINE_DELAY_VAL2                    0x7D0
#define DDRPHY_INIT_ENGINE_DELAY_VAL3                   0x1388

#define DDRPHY_INITENG0_PRESEQUENCEREG0B0S0_VAL     0x00000000
#define DDRPHY_INITENG0_PRESEQUENCEREG0B0S1_VAL     0x00000000
#define DDRPHY_INITENG0_PRESEQUENCEREG0B0S2_VAL     0x00000400
#define DDRPHY_INITENG0_PRESEQUENCEREG0B1S0_VAL     0x00000000
#define DDRPHY_INITENG0_PRESEQUENCEREG0B1S1_VAL     0x00000000
#define DDRPHY_INITENG0_PRESEQUENCEREG0B1S2_VAL     0x00000400
#define DDRPHY_INITENG0_SEQUENCEREG0B0S0_VAL        0x0000fff8
#define DDRPHY_INITENG0_SEQUENCEREG0B0S1_VAL        0x0000875f
#define DDRPHY_INITENG0_SEQUENCEREG0B0S2_VAL        0x00008c4f
#define DDRPHY_INITENG0_SEQUENCEREG0B1S0_VAL        0x0000000c
#define DDRPHY_INITENG0_SEQUENCEREG0B1S1_VAL        0x00008468
#define DDRPHY_INITENG0_SEQUENCEREG0B1S2_VAL        0x00008c17
#define DDRPHY_INITENG0_SEQUENCEREG0B2S0_VAL        0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B2S1_VAL        0x0000845a
#define DDRPHY_INITENG0_SEQUENCEREG0B2S2_VAL        0x00000c17
#define DDRPHY_INITENG0_SEQUENCEREG0B3S0_VAL        0x00000004
#define DDRPHY_INITENG0_SEQUENCEREG0B3S1_VAL        0x00008468
#define DDRPHY_INITENG0_SEQUENCEREG0B3S2_VAL        0x00008c17
#define DDRPHY_INITENG0_SEQUENCEREG0B4S0_VAL        0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B4S1_VAL        0x00008478
#define DDRPHY_INITENG0_SEQUENCEREG0B4S2_VAL        0x00008c17
#define DDRPHY_INITENG0_SEQUENCEREG0B5S0_VAL        0x0000000b
#define DDRPHY_INITENG0_SEQUENCEREG0B5S1_VAL        0x00008480
#define DDRPHY_INITENG0_SEQUENCEREG0B5S2_VAL        0x00008c17
#define DDRPHY_INITENG0_SEQUENCEREG0B6S0_VAL        0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B6S1_VAL        0x00008448
#define DDRPHY_INITENG0_SEQUENCEREG0B6S2_VAL        0x00009c17
#define DDRPHY_INITENG0_SEQUENCEREG0B7S0_VAL        0x00000002
#define DDRPHY_INITENG0_SEQUENCEREG0B7S1_VAL        0x00008010
#define DDRPHY_INITENG0_SEQUENCEREG0B7S2_VAL        0x00009c17
#define DDRPHY_INITENG0_SEQUENCEREG0B8S0_VAL        0x0000000f
#define DDRPHY_INITENG0_SEQUENCEREG0B8S1_VAL        0x000087c0
#define DDRPHY_INITENG0_SEQUENCEREG0B8S2_VAL        0x00009c17
#define DDRPHY_INITENG0_SEQUENCEREG0B9S0_VAL        0x00000147
#define DDRPHY_INITENG0_SEQUENCEREG0B9S1_VAL        0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B9S2_VAL        0x0000ac17
#define DDRPHY_INITENG0_SEQUENCEREG0B10S0_VAL       0x00000047
#define DDRPHY_INITENG0_SEQUENCEREG0B10S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B10S2_VAL       0x0000a417
#define DDRPHY_INITENG0_SEQUENCEREG0B11S0_VAL       0x0000004f
#define DDRPHY_INITENG0_SEQUENCEREG0B11S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B11S2_VAL       0x00009c17
#define DDRPHY_INITENG0_SEQUENCEREG0B12S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B12S1_VAL       0x000087c8
#define DDRPHY_INITENG0_SEQUENCEREG0B12S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B13S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B13S1_VAL       0x00000001
#define DDRPHY_INITENG0_SEQUENCEREG0B13S2_VAL       0x00000400
#define DDRPHY_INITENG0_SEQUENCEREG0B14S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B14S1_VAL       0x0000845a
#define DDRPHY_INITENG0_SEQUENCEREG0B14S2_VAL       0x00001c17
#define DDRPHY_INITENG0_SEQUENCEREG0B15S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B15S1_VAL       0x00008448
#define DDRPHY_INITENG0_SEQUENCEREG0B15S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B16S0_VAL       0x00000041
#define DDRPHY_INITENG0_SEQUENCEREG0B16S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B16S2_VAL       0x00009c17
#define DDRPHY_INITENG0_SEQUENCEREG0B17S0_VAL       0x00000001
#define DDRPHY_INITENG0_SEQUENCEREG0B17S1_VAL       0x00008618
#define DDRPHY_INITENG0_SEQUENCEREG0B17S2_VAL       0x00008c17
#define DDRPHY_INITENG0_SEQUENCEREG0B18S0_VAL       0x000040c0
#define DDRPHY_INITENG0_SEQUENCEREG0B18S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B18S2_VAL       0x0000a417
#define DDRPHY_INITENG0_SEQUENCEREG0B19S0_VAL       0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B19S1_VAL       0x00000004
#define DDRPHY_INITENG0_SEQUENCEREG0B19S2_VAL       0x00002400
#define DDRPHY_INITENG0_SEQUENCEREG0B20S0_VAL       0x00004040
#define DDRPHY_INITENG0_SEQUENCEREG0B20S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B20S2_VAL       0x0000a417
#define DDRPHY_INITENG0_SEQUENCEREG0B21S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B21S1_VAL       0x00000004
#define DDRPHY_INITENG0_SEQUENCEREG0B21S2_VAL       0x00002400
#define DDRPHY_INITENG0_SEQUENCEREG0B22S0_VAL       0x00000040
#define DDRPHY_INITENG0_SEQUENCEREG0B22S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B22S2_VAL       0x0000a417
#define DDRPHY_INITENG0_SEQUENCEREG0B23S0_VAL       0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B23S1_VAL       0x00000004
#define DDRPHY_INITENG0_SEQUENCEREG0B23S2_VAL       0x00001c00
#define DDRPHY_INITENG0_SEQUENCEREG0B24S0_VAL       0x00000010
#define DDRPHY_INITENG0_SEQUENCEREG0B24S1_VAL       0x00000004
#define DDRPHY_INITENG0_SEQUENCEREG0B24S2_VAL       0x00000c00
#define DDRPHY_INITENG0_SEQUENCEREG0B25S0_VAL       0x00000541
#define DDRPHY_INITENG0_SEQUENCEREG0B25S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B25S2_VAL       0x0000ac17
#define DDRPHY_INITENG0_SEQUENCEREG0B26S0_VAL       0x00000d41
#define DDRPHY_INITENG0_SEQUENCEREG0B26S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B26S2_VAL       0x0000ac17
#define DDRPHY_INITENG0_SEQUENCEREG0B27S0_VAL       0x00000944
#define DDRPHY_INITENG0_SEQUENCEREG0B27S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B27S2_VAL       0x0000ac17
#define DDRPHY_INITENG0_SEQUENCEREG0B28S0_VAL       0x00000442
#define DDRPHY_INITENG0_SEQUENCEREG0B28S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B28S2_VAL       0x0000a417
#define DDRPHY_INITENG0_SEQUENCEREG0B29S0_VAL       0x00000044
#define DDRPHY_INITENG0_SEQUENCEREG0B29S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B29S2_VAL       0x0000a417
#define DDRPHY_INITENG0_SEQUENCEREG0B30S0_VAL       0x00000004
#define DDRPHY_INITENG0_SEQUENCEREG0B30S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B30S2_VAL       0x0000a417
#define DDRPHY_INITENG0_SEQUENCEREG0B31S0_VAL       0x00000944
#define DDRPHY_INITENG0_SEQUENCEREG0B31S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B31S2_VAL       0x0000ac17
#define DDRPHY_INITENG0_SEQUENCEREG0B32S0_VAL       0x0000000c
#define DDRPHY_INITENG0_SEQUENCEREG0B32S1_VAL       0x00008468
#define DDRPHY_INITENG0_SEQUENCEREG0B32S2_VAL       0x00008c17
#define DDRPHY_INITENG0_SEQUENCEREG0B33S0_VAL       0x0000001f
#define DDRPHY_INITENG0_SEQUENCEREG0B33S1_VAL       0x000083c0
#define DDRPHY_INITENG0_SEQUENCEREG0B33S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B34S0_VAL       0x00000010
#define DDRPHY_INITENG0_SEQUENCEREG0B34S1_VAL       0x000083c0
#define DDRPHY_INITENG0_SEQUENCEREG0B34S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B35S0_VAL       0x0000000a
#define DDRPHY_INITENG0_SEQUENCEREG0B35S1_VAL       0x00008010
#define DDRPHY_INITENG0_SEQUENCEREG0B35S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B36S0_VAL       0x00000019
#define DDRPHY_INITENG0_SEQUENCEREG0B36S1_VAL       0x00008010
#define DDRPHY_INITENG0_SEQUENCEREG0B36S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B37S0_VAL       0x00000030
#define DDRPHY_INITENG0_SEQUENCEREG0B37S1_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B37S2_VAL       0x00000400
#define DDRPHY_INITENG0_SEQUENCEREG0B38S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B38S1_VAL       0x000083c0
#define DDRPHY_INITENG0_SEQUENCEREG0B38S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B39S0_VAL       0x00000003
#define DDRPHY_INITENG0_SEQUENCEREG0B39S1_VAL       0x00008010
#define DDRPHY_INITENG0_SEQUENCEREG0B39S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B40S0_VAL       0x00000007
#define DDRPHY_INITENG0_SEQUENCEREG0B40S1_VAL       0x000087c0
#define DDRPHY_INITENG0_SEQUENCEREG0B40S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B41S0_VAL       0x00000010
#define DDRPHY_INITENG0_SEQUENCEREG0B41S1_VAL       0x00008010
#define DDRPHY_INITENG0_SEQUENCEREG0B41S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B42S0_VAL       0x0000fff8
#define DDRPHY_INITENG0_SEQUENCEREG0B42S1_VAL       0x0000874f
#define DDRPHY_INITENG0_SEQUENCEREG0B42S2_VAL       0x0000944f
#define DDRPHY_INITENG0_SEQUENCEREG0B43S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B43S1_VAL       0x00008758
#define DDRPHY_INITENG0_SEQUENCEREG0B43S2_VAL       0x0000944f
#define DDRPHY_INITENG0_SEQUENCEREG0B44S0_VAL       0x00000010
#define DDRPHY_INITENG0_SEQUENCEREG0B44S1_VAL       0x00008720
#define DDRPHY_INITENG0_SEQUENCEREG0B44S2_VAL       0x0000944f
#define DDRPHY_INITENG0_SEQUENCEREG0B45S0_VAL       0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B45S1_VAL       0x000087c8
#define DDRPHY_INITENG0_SEQUENCEREG0B45S2_VAL       0x00008017
#define DDRPHY_INITENG0_SEQUENCEREG0B46S0_VAL       0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B46S1_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B46S2_VAL       0x00000400
#define DDRPHY_INITENG0_SEQUENCEREG0B47S0_VAL       0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B47S1_VAL       0x00008448
#define DDRPHY_INITENG0_SEQUENCEREG0B47S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B48S0_VAL       0x0000000f
#define DDRPHY_INITENG0_SEQUENCEREG0B48S1_VAL       0x000087c0
#define DDRPHY_INITENG0_SEQUENCEREG0B48S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B49S0_VAL       0x00000047
#define DDRPHY_INITENG0_SEQUENCEREG0B49S1_VAL       0x00008630
#define DDRPHY_INITENG0_SEQUENCEREG0B49S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B50S0_VAL       0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B50S1_VAL       0x00008618
#define DDRPHY_INITENG0_SEQUENCEREG0B50S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B51S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B51S1_VAL       0x000087c8
#define DDRPHY_INITENG0_SEQUENCEREG0B51S2_VAL       0x00008417
#define DDRPHY_INITENG0_SEQUENCEREG0B52S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B52S1_VAL       0x00008748
#define DDRPHY_INITENG0_SEQUENCEREG0B52S2_VAL       0x0000844f
#define DDRPHY_INITENG0_SEQUENCEREG0B53S0_VAL       0x0000fff8
#define DDRPHY_INITENG0_SEQUENCEREG0B53S1_VAL       0x0000875f
#define DDRPHY_INITENG0_SEQUENCEREG0B53S2_VAL       0x0000844f
#define DDRPHY_INITENG0_SEQUENCEREG0B54S0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQUENCEREG0B54S1_VAL       0x00000001
#define DDRPHY_INITENG0_SEQUENCEREG0B54S2_VAL       0x00000400
#define DDRPHY_INITENG0_SEQUENCEREG0B55S0_VAL       0x00000008
#define DDRPHY_INITENG0_SEQUENCEREG0B55S1_VAL       0x000087c8
#define DDRPHY_INITENG0_SEQUENCEREG0B55S2_VAL       0x00008017
#define DDRPHY_INITENG0_POSTSEQUENCEREG0B0S0_VAL    0x00000000
#define DDRPHY_INITENG0_POSTSEQUENCEREG0B0S1_VAL    0x00000000
#define DDRPHY_INITENG0_POSTSEQUENCEREG0B0S2_VAL    0x00000400
#define DDRPHY_INITENG0_POSTSEQUENCEREG0B1S0_VAL    0x00000000
#define DDRPHY_INITENG0_POSTSEQUENCEREG0B1S1_VAL    0x00000000
#define DDRPHY_INITENG0_POSTSEQUENCEREG0B1S2_VAL    0x00000000
#define DDRPHY_APBONLY0_SEQUENCEROVERRIDE_VAL       0x00000200
#define DDRPHY_INITENG0_STARTVECTOR0B0_VAL          0x00000000
#define DDRPHY_INITENG0_STARTVECTOR0B15_VAL         0x0000002e
#define DDRPHY_MASTER0_DFIFREQXLAT0_VAL             0x00000000
#define DDRPHY_MASTER0_DFIFREQXLAT1_VAL             0x00000000
#define DDRPHY_MASTER0_DFIFREQXLAT2_VAL             0x00000000
#define DDRPHY_MASTER0_DFIFREQXLAT3_VAL             0x00000000
#define DDRPHY_MASTER0_DFIFREQXLAT4_VAL             0x0000ffff
#define DDRPHY_MASTER0_DFIFREQXLAT5_VAL             0x0000ffff
#define DDRPHY_MASTER0_DFIFREQXLAT6_VAL             0x0000ffff
#define DDRPHY_MASTER0_DFIFREQXLAT7_VAL             0x0000ffff
#define DDRPHY_INITENG0_SEQ0BDISABLEFLAG0_VAL       0x00000000
#define DDRPHY_INITENG0_SEQ0BDISABLEFLAG1_VAL       0x00000000
#define DDRPHY_INITENG0_SEQ0BDISABLEFLAG2_VAL       0x0000ffff
#define DDRPHY_INITENG0_SEQ0BDISABLEFLAG3_VAL       0x0000ffff
#define DDRPHY_INITENG0_SEQ0BDISABLEFLAG4_VAL       0x00000000
#define DDRPHY_INITENG0_SEQ0BDISABLEFLAG5_VAL       0x00000000
#define DDRPHY_INITENG0_SEQ0BDISABLEFLAG6_VAL       0x00000000
#define DDRPHY_INITENG0_SEQ0BDISABLEFLAG7_VAL       0x00000000
//------------------------------------------------------------

/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    This type is used to collect the values to be written to the PHY
*    registers.
*
* @par Members
*
*                                  <PRE>
*    caluclkinfo_val        Calibration register about relationship to DFICLK
*                             and pstates
*    pllctrl2_val           PLL charge-pump settings of various pstates
*    dllgainctl_val         Controls for the DLL gain sequencing for locking
*    ardptrinitval_val      Read pointer offset for free running AC command
*                             FIFOs
*    masterx4config_val     Register to indicate x4 DRAMs being used
*    dbytedllmodecntrl_val  DLL mode control in data modules, RX preamble mode
*    dqspreamblecontrol_val Register to control DQS preamble, position DFE
*                             init
*    hwtcamode_val          Controls the PHY and HWT DRAM mode
*    tristatemodeca_val     Controls command/address tristate modes
*    seq0bdly[0:3]_val      DFI tick reference [0.5us, 1us, 10us, 25us]
*                             for all pstates
*    dmem3_val              Message block info:  DIMM type, # dq bits
*    dmem4_val              Message block info:  CS present, CS in DIMM0
*    dmem5_val              Message block info:  CS in DIMM1, Address mirror
*    dmem6_val              Message block info:  Test fail status, 1T/2T
*    dmem8_val              Message block info:  verbose option, Rx 2D option
*    dmem9_val              Message block info:  2D Tx option, share 2D Vref
*    dmem10_val             Message block info:  2D delay and voltage weight
*    dmem15_val             Message block info:  DFI max read latency margin
*    dmem40_val             Message block info:  MinRxHeight
*    dmem41_val             Message block info:  Rd2D Read Group
*    dmem42_val             Message block info:  Grid
*    dmem43_val             Message block info:  dbi/wl workaround
*    dmem504_val            Message block info:  cas latency without tDBI
*    dmem505_val            Message block info:  wcas latency without 2tCK WR
*    odt_dmem_6x[chan][3]   Message block info:  ODT for all ranks / channels
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    // for init
    uint16_t caluclkinfo_val[PHY_NUM_PSTATES];
    uint16_t plltestmode_val[PHY_NUM_PSTATES];
    uint16_t pllctrl2_val[PHY_NUM_PSTATES];
    uint16_t dllgainctl_val[PHY_NUM_PSTATES];
    uint16_t ardptrinitval_val[PHY_NUM_PSTATES];
    uint16_t masterx4config_val;
    uint16_t dbytedllmodecntrl_val;
    uint16_t dqspreamblecontrol_val[PHY_NUM_PSTATES];
    uint16_t hwtcamode_val;
    uint16_t tristatemodeca_val[PHY_NUM_PSTATES];

    // for training
    uint16_t seq0bdly0_val[PHY_NUM_PSTATES];
    uint16_t seq0bdly1_val[PHY_NUM_PSTATES];
    uint16_t seq0bdly2_val[PHY_NUM_PSTATES];
    uint16_t seq0bdly3_val[PHY_NUM_PSTATES];
    uint16_t dmem3_val;     // dimm type, # dq bits
//    uint16_t dmem4_val;     // cs present, cs d0
//    uint16_t dmem5_val;     // cs d1, addr mirror
    uint16_t dmem6_val;     // test fail, 1T/2T
    uint16_t dmem8_val;     // verbose, rx2dopt
    uint16_t dmem9_val;     // tx2dopt, share2dvref
    uint16_t dmem10_val;    // dlywt2d, voltwgt2d
    uint16_t dmem15_val;    // dfi_mrl_margin
    uint16_t dmem40_val;    // MinRxHeight
    uint16_t dmem41_val;    // Rd2D Read Group
    uint16_t dmem42_val;    // Grid
    uint16_t dmem43_val;    // dbi/wl workaround
    uint16_t dmem504_val;   // alt_cas_lat
    uint16_t dmem505_val;   // alt_wcas_lat
    // dmem60-61 ODT
    uint16_t odt_dmem_6x[DDR_MAX_NUM_CHANS][PHY_ODT_REGS];

} mddr_phy_register_values_t;

/******************************************************************************
* Global Variables
******************************************************************************/

/******************************************************************************
* Macros
******************************************************************************/

/******************************************************************************
* Function Prototypes
******************************************************************************/

unsigned mddr_phy_init(uint8_t chan);

void mddr_phy_get_reg_vals(mddr_settings_t *mddr_settings_ptr);
void mddr_phy_set_si_regs(uint8_t ddr_chan);

/*****************************************************************************/
#endif
