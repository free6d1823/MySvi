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
//
// The following constants are used to directly manipulate GCC HW funcionality ouside the MDDR
//  Subsystem. These need to be removed once the appropriate external hooks have been
//  implemented to allow running when not in a baremetal environment.
//
//! @todo -GPK- Direct GCC block accesses : Replace with appropriate external hooks for CoreBSP integration

#define GCCMW_MDDR_PWROK                              0xFF01100600     // for all controllers

// reset=0x80000000; clk_off=1, clk_enable=0
#define GCCMW_MDDR0_AHB_CBCR                          0xFF01520000     // hddrss0
#define GCCMW_MDDR1_AHB_CBCR                          0xFF01520004     // hddrss1
#define GCCMW_MDDR2_AHB_CBCR                          0xFF01510000     // hddrss2
#define GCCMW_MDDR3_AHB_CBCR                          0xFF01510004     // hddrss3
#define GCCE_MDDR4_AHB_CBCR                           0xFF22450004     // hddrss4
#define GCCE_MDDR5_AHB_CBCR                           0xFF224E0004     // hddrss5

#define GCCMS_MDDR2_AHB_CBCR_CLK_EN___M               0x1


// reset=0x80000000; clk_off=1, clk_enable=0
#define N_GCCMS_MDDR0_2X_CBCR                         0xFF082A0020     // hddrss2
#define N_GCCMS_MDDR1_2X_CBCR                         0xFF082B0020     // hddrss3
#define N_GCCMS_MDDR2_2X_CBCR                         0xFF082C0020     // hddrss4
#define S_GCCMS_MDDR0_2X_CBCR                         0xFF1E4A0020     // hddrss0
#define S_GCCMS_MDDR1_2X_CBCR                         0xFF1E4B0020     // hddrss1
#define S_GCCMS_MDDR2_2X_CBCR                         0xFF1E4C0020     // hddrss5

#define GCCMS_MDDRN_2X_CBCR_CLK_ENABLE___M            0x1


// reset=0x80000001; clk_off=1, clk_enable=1
#define N_GCCMS_MDDR0_XO_CBCR                         0xFF082A0044     // hddrss2
#define N_GCCMS_MDDR1_XO_CBCR                         0xFF082B0044     // hddrss3
#define N_GCCMS_MDDR2_XO_CBCR                         0xFF082C0044     // hddrss4
#define S_GCCMS_MDDR0_XO_CBCR                         0xFF1E4A0044     // hddrss0
#define S_GCCMS_MDDR1_XO_CBCR                         0xFF1E4B0044     // hddrss1
#define S_GCCMS_MDDR2_XO_CBCR                         0xFF1E4C0044     // hddrss5


// Mux(glitch-free) select register, reset=0x0
// bit 8 = root_en, bit 7:4 = mux_sel_status, bit 1:0 = mux_sel
// mux_sel: 0 = XO, 1 = clkgen, 2 = pll1, 3 = test
#define N_GCCMS_MDDR_0_CGF4R                          0xFF082A0018     // hddrss2
#define N_GCCMS_MDDR_1_CGF4R                          0xFF082B0048     // hddrss3
#define N_GCCMS_MDDR_2_CGF4R                          0xFF082C0048     // hddrss4
#define S_GCCMS_MDDR_0_CGF4R                          0xFF1E4A0018     // hddrss0
#define S_GCCMS_MDDR_1_CGF4R                          0xFF1E4B0048     // hddrss1
#define S_GCCMS_MDDR_2_CGF4R                          0xFF1E4C0048     // hddrss5

#define GCCMS_MDDRN_CGF4R_MUX_SEL___M               0xFF
#define GCCMS_MDDRN_CGF4R_ROOT_EN___S               0x8
#define GCCMS_MDDRN_CGF4R_ROOT_EN___M               0x1
#define GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___S        0x4
#define GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___M        0xF


// pwrdn_b (active low), reset=0x0
#define N_GCCMS_MDDR0_CLKGEN_MISC                     0xFF082A0038     // hddrss2
#define N_GCCMS_MDDR1_CLKGEN_MISC                     0xFF082B0038     // hddrss3
#define N_GCCMS_MDDR2_CLKGEN_MISC                     0xFF082C0038     // hddrss4
#define S_GCCMS_MDDR0_CLKGEN_MISC                     0xFF1E4A0038     // hddrss0
#define S_GCCMS_MDDR1_CLKGEN_MISC                     0xFF1E4B0038     // hddrss1
#define S_GCCMS_MDDR2_CLKGEN_MISC                     0xFF1E4C0038     // hddrss5


// {N,S}_GCCMS_MDDR{0..2}_RESETR, reset=0x3
// bit 2 = core_ares, bit 1 = apb_ares, bit 0 = phy_ares
#define N_GCCMS_MDDR0_RESETR                          0xFF082A0014     // hddrss2
#define N_GCCMS_MDDR1_RESETR                          0xFF082B0014     // hddrss3
#define N_GCCMS_MDDR2_RESETR                          0xFF082C0014     // hddrss4
#define S_GCCMS_MDDR0_RESETR                          0xFF1E4A0014     // hddrss0
#define S_GCCMS_MDDR1_RESETR                          0xFF1E4B0014     // hddrss1
#define S_GCCMS_MDDR2_RESETR                          0xFF1E4C0014     // hddrss5

#define GCCMS_MDDRN_RESETR_APB_ARES___M               0x2
#define GCCMS_MDDRN_RESETR_PHY_ARES___M               0x1


#define N_GCCMS_SPARE_0                               0xFF082F0000     // controls hddrss 0, 1, 5
#define S_GCCMS_SPARE_0                               0xFF1E4F0000     // controls hddrss 2, 3, 4


/******************************************************************************
* Defined Constants
******************************************************************************/
//    DIMMS for DDR HDDRSS 4,2,3 are on SMBus 0 (BLSP1_I2C0)
//    DIMMS for DDR HDDRSS 5,1,0 are on SMBus 1 (BLSP1_I2C1)
#define SPD_BLSP1_I2C0                          0
#define SPD_BLSP1_I2C1                          1

//
// SMBus DIMM SPD EEPROM Slot address map.
//
//   Addresses can be duplicated since the channels are split between two SMBuses.
//   The addresses do not necessarily follow a numbering pattern since each is
//   driven by a 3 pin address selector on the given platform.
//
//   These are the JEDEC EEPROM addresses each comprising of the 7-bit slave address and
//    the R/W bit (reset to 0 as for a Write).
//   Note that the SMBus protocol specifies that a bit value of 0 is for Write
//    and a bit value of 1 is for Read.
//
#define SPD_EEPROM_SMBUS_HDDRSS0_SLOT0_ADDR     0xA8
#define SPD_EEPROM_SMBUS_HDDRSS0_SLOT1_ADDR     0xAA
#define SPD_EEPROM_SMBUS_HDDRSS1_SLOT0_ADDR     0xA4
#define SPD_EEPROM_SMBUS_HDDRSS1_SLOT1_ADDR     0xA6
#define SPD_EEPROM_SMBUS_HDDRSS2_SLOT0_ADDR     0xA4
#define SPD_EEPROM_SMBUS_HDDRSS2_SLOT1_ADDR     0xA6
#define SPD_EEPROM_SMBUS_HDDRSS3_SLOT0_ADDR     0xA8
#define SPD_EEPROM_SMBUS_HDDRSS3_SLOT1_ADDR     0xAA
#define SPD_EEPROM_SMBUS_HDDRSS4_SLOT0_ADDR     0xA0
#define SPD_EEPROM_SMBUS_HDDRSS4_SLOT1_ADDR     0xA2
#define SPD_EEPROM_SMBUS_HDDRSS5_SLOT0_ADDR     0xA0
#define SPD_EEPROM_SMBUS_HDDRSS5_SLOT1_ADDR     0xA2

// SMBus DIMM SPD Thermal Sensor Slot address map.
//
//   Addresses can be duplicated since the channels are split between two SMBuses.
//   The addresses do not necessarily follow a numbering pattern since each is
//   driven by a 3 pin address selector on the given platform.
//
//   These are the write addresses, read addresses for a DIMM are 1 more than the write addresses.
//
#define SPD_TS_SMBUS_HDDRSS0_SLOT0_ADDR         0x38
#define SPD_TS_SMBUS_HDDRSS0_SLOT1_ADDR         0x3A
#define SPD_TS_SMBUS_HDDRSS1_SLOT0_ADDR         0x34
#define SPD_TS_SMBUS_HDDRSS1_SLOT1_ADDR         0x36
#define SPD_TS_SMBUS_HDDRSS2_SLOT0_ADDR         0x34
#define SPD_TS_SMBUS_HDDRSS2_SLOT1_ADDR         0x36
#define SPD_TS_SMBUS_HDDRSS3_SLOT0_ADDR         0x38
#define SPD_TS_SMBUS_HDDRSS3_SLOT1_ADDR         0x3A
#define SPD_TS_SMBUS_HDDRSS4_SLOT0_ADDR         0x30
#define SPD_TS_SMBUS_HDDRSS4_SLOT1_ADDR         0x32
#define SPD_TS_SMBUS_HDDRSS5_SLOT0_ADDR         0x30
#define SPD_TS_SMBUS_HDDRSS5_SLOT1_ADDR         0x32

// SMBus DIMM SPD Command Slot address map.
//
//   Addresses can be duplicated since the channels are split between two SMBuses.
//   The addresses do not necessarily follow a numbering pattern since each is
//   driven by a 3 pin address selector on the given platform.
//
//   These are the write addresses; read addresses for a DIMM are 1 more than the write addresses.
//
#define SPD_CMD_SMBUS_HDDRSS0_SLOT0_ADDR         0x68
#define SPD_CMD_SMBUS_HDDRSS0_SLOT1_ADDR         0x6A
#define SPD_CMD_SMBUS_HDDRSS1_SLOT0_ADDR         0x64
#define SPD_CMD_SMBUS_HDDRSS1_SLOT1_ADDR         0x66
#define SPD_CMD_SMBUS_HDDRSS2_SLOT0_ADDR         0x64
#define SPD_CMD_SMBUS_HDDRSS2_SLOT1_ADDR         0x66
#define SPD_CMD_SMBUS_HDDRSS3_SLOT0_ADDR         0x68
#define SPD_CMD_SMBUS_HDDRSS3_SLOT1_ADDR         0x6A
#define SPD_CMD_SMBUS_HDDRSS4_SLOT0_ADDR         0x60
#define SPD_CMD_SMBUS_HDDRSS4_SLOT1_ADDR         0x62
#define SPD_CMD_SMBUS_HDDRSS5_SLOT0_ADDR         0x60
#define SPD_CMD_SMBUS_HDDRSS5_SLOT1_ADDR         0x62

// SMBus DIMM RCD Config Registers Slot address map.
//
//   Addresses can be duplicated since the channels are split between two SMBuses.
//   The addresses do not necessarily follow a numbering pattern since each is
//   driven by a 3 pin address selector on the given platform.
//
//   These are the write addresses; read addresses for a DIMM are 1 more than the write addresses.
//
#define RCD_SMBUS_HDDRSS0_SLOT0_ADDR         0xB8
#define RCD_SMBUS_HDDRSS0_SLOT1_ADDR         0xBA
#define RCD_SMBUS_HDDRSS1_SLOT0_ADDR         0xB4
#define RCD_SMBUS_HDDRSS1_SLOT1_ADDR         0xB6
#define RCD_SMBUS_HDDRSS2_SLOT0_ADDR         0xB4
#define RCD_SMBUS_HDDRSS2_SLOT1_ADDR         0xB6
#define RCD_SMBUS_HDDRSS3_SLOT0_ADDR         0xB8
#define RCD_SMBUS_HDDRSS3_SLOT1_ADDR         0xBA
#define RCD_SMBUS_HDDRSS4_SLOT0_ADDR         0xB0
#define RCD_SMBUS_HDDRSS4_SLOT1_ADDR         0xB2
#define RCD_SMBUS_HDDRSS5_SLOT0_ADDR         0xB0
#define RCD_SMBUS_HDDRSS5_SLOT1_ADDR         0xB2

/*!****************************************************************************
*
* @par Description
*    Structure used to collect platform specific SI adjustments for each DDR
*    channel. Pre-initialized with data for SOD single DIMM @1866 MTS or less.
*
******************************************************************************/
mddr_si_chan_t si_data[DDR_MAX_NUM_CHANS] =
{
    // Chan 0
    {
        {0, 0}, {34, 34}, 60, 7475,
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x5, 0x0, 0x10, 0x10},
        {
            // DIMM 0
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            },


            // DIMM 1
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            }
        }
    },

    // Chan 1
    {
        {0, 0}, {34, 34}, 60, 7475,
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x5, 0x0, 0x10, 0x10},
        {
            // DIMM 0
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            },


            // DIMM 1
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            }
        }
    },

    // Chan 2
    {
        {0, 0}, {34, 34}, 60, 7475,
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x5, 0x0, 0x10, 0x10},
        {
            // DIMM 0
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            },


            // DIMM 1
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            }
        }
    },

    // Chan 3
    {
        {0, 0}, {34, 34}, 60, 7475,
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x5, 0x0, 0x10, 0x10},
        {
            // DIMM 0
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            },


            // DIMM 1
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            }
        }
    },

    // Chan 4
    {
        {0, 0}, {34, 34}, 60, 7475,
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x5, 0x0, 0x10, 0x10},
        {
            // DIMM 0
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            },


            // DIMM 1
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            }
        }
    },

    // Chan 5
    {
        {0, 0}, {34, 34}, 60, 7475,
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x5, 0x0, 0x10, 0x10},
        {
            // DIMM 0
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            },


            // DIMM 1
            {
                {150, 150, 150, 150},     // ibt_ca/cs/cke/odt
                {
                    // DIMM 0 - Rank 0
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 1
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 2
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    },

                    // DIMM 0 - Rank 3
                    {
                        0, 80, 0, 34, 0, 0,
                        {7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750,7750}
                    }
                }
            }
        }
    }
};


/*!****************************************************************************
*
* @par Description
*    Array used to associate the HDDRSS base addresses to the DDR channels.
*    The array is indexed by channel number.
*
* @par Notes:
*    A logical DDR channel reflects the default address walk order found
*    in the Monaco bus. Each logical channel maps to a single MCSU and
*    HDDRSS.
*
* @verbatim
*    Logical     MCSU        HDDRSS     Switch
*    Channel    Instance    Instance      ID      Interleave
*    -------    --------    --------    ------    ----------
*      0           0           2         0x00       Even
*      1           1           3         0x04       Odd
*      2           3           5         0x0C       Even
*      3           2           4         0x08       Odd
*      4           4           0         0x10       Even
*      5           5           1         0x14       Odd
* @endverbatim
*
******************************************************************************/
uint64_t mddr_base_addrs[DDR_MAX_NUM_CHANS] = {
                                MDDR_HDDRSS2_ADDR,
                                MDDR_HDDRSS3_ADDR,
                                MDDR_HDDRSS5_ADDR,
                                MDDR_HDDRSS4_ADDR,
                                MDDR_HDDRSS0_ADDR,
                                MDDR_HDDRSS1_ADDR
                           };

uint8_t hddrss[DDR_MAX_NUM_CHANS] = {
                                2,
                                3,
                                5,
                                4,
                                0,
                                1,
                          };


// Default values for SMBUS I2C addresses
dimm_slot_smbus_info_t smbus_default_val[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN]=
{
    {
        {SPD_BLSP1_I2C0,SPD_EEPROM_SMBUS_HDDRSS2_SLOT0_ADDR,SPD_TS_SMBUS_HDDRSS2_SLOT0_ADDR,SPD_CMD_SMBUS_HDDRSS2_SLOT0_ADDR,RCD_SMBUS_HDDRSS2_SLOT0_ADDR},
        {SPD_BLSP1_I2C0,SPD_EEPROM_SMBUS_HDDRSS2_SLOT1_ADDR,SPD_TS_SMBUS_HDDRSS2_SLOT1_ADDR,SPD_CMD_SMBUS_HDDRSS2_SLOT1_ADDR,RCD_SMBUS_HDDRSS2_SLOT1_ADDR}
    },
    {
        {SPD_BLSP1_I2C0,SPD_EEPROM_SMBUS_HDDRSS3_SLOT0_ADDR,SPD_TS_SMBUS_HDDRSS3_SLOT0_ADDR,SPD_CMD_SMBUS_HDDRSS3_SLOT0_ADDR,RCD_SMBUS_HDDRSS3_SLOT0_ADDR},
        {SPD_BLSP1_I2C0,SPD_EEPROM_SMBUS_HDDRSS3_SLOT1_ADDR,SPD_TS_SMBUS_HDDRSS3_SLOT1_ADDR,SPD_CMD_SMBUS_HDDRSS3_SLOT1_ADDR,RCD_SMBUS_HDDRSS3_SLOT1_ADDR}
    },
    {
        {SPD_BLSP1_I2C1,SPD_EEPROM_SMBUS_HDDRSS5_SLOT0_ADDR,SPD_TS_SMBUS_HDDRSS5_SLOT0_ADDR,SPD_CMD_SMBUS_HDDRSS5_SLOT0_ADDR,RCD_SMBUS_HDDRSS5_SLOT0_ADDR},
        {SPD_BLSP1_I2C1,SPD_EEPROM_SMBUS_HDDRSS5_SLOT1_ADDR,SPD_TS_SMBUS_HDDRSS5_SLOT1_ADDR,SPD_CMD_SMBUS_HDDRSS5_SLOT1_ADDR,RCD_SMBUS_HDDRSS5_SLOT1_ADDR}
    },
    {
        {SPD_BLSP1_I2C0,SPD_EEPROM_SMBUS_HDDRSS4_SLOT0_ADDR,SPD_TS_SMBUS_HDDRSS4_SLOT0_ADDR,SPD_CMD_SMBUS_HDDRSS4_SLOT0_ADDR,RCD_SMBUS_HDDRSS4_SLOT0_ADDR},
        {SPD_BLSP1_I2C0,SPD_EEPROM_SMBUS_HDDRSS4_SLOT1_ADDR,SPD_TS_SMBUS_HDDRSS4_SLOT1_ADDR,SPD_CMD_SMBUS_HDDRSS4_SLOT1_ADDR,RCD_SMBUS_HDDRSS4_SLOT1_ADDR}
    },
    {
        {SPD_BLSP1_I2C1,SPD_EEPROM_SMBUS_HDDRSS0_SLOT0_ADDR,SPD_TS_SMBUS_HDDRSS0_SLOT0_ADDR,SPD_CMD_SMBUS_HDDRSS0_SLOT0_ADDR,RCD_SMBUS_HDDRSS0_SLOT0_ADDR},
        {SPD_BLSP1_I2C1,SPD_EEPROM_SMBUS_HDDRSS0_SLOT1_ADDR,SPD_TS_SMBUS_HDDRSS0_SLOT1_ADDR,SPD_CMD_SMBUS_HDDRSS0_SLOT1_ADDR,RCD_SMBUS_HDDRSS0_SLOT1_ADDR}
    },
    {
        {SPD_BLSP1_I2C1,SPD_EEPROM_SMBUS_HDDRSS1_SLOT0_ADDR,SPD_TS_SMBUS_HDDRSS1_SLOT0_ADDR,SPD_CMD_SMBUS_HDDRSS1_SLOT0_ADDR,RCD_SMBUS_HDDRSS1_SLOT0_ADDR},
        {SPD_BLSP1_I2C1,SPD_EEPROM_SMBUS_HDDRSS1_SLOT1_ADDR,SPD_TS_SMBUS_HDDRSS1_SLOT1_ADDR,SPD_CMD_SMBUS_HDDRSS1_SLOT1_ADDR,RCD_SMBUS_HDDRSS1_SLOT1_ADDR}
    }
};

/*!****************************************************************************
*
* @par Description:
*    This function initializes  the memory controllers found in the Monaco
*    DDR subsystem based on SPD information extracted from the populated DIMMs
*    and specified configuration options
*     This function is used only during the DDR Margining mode. It does not perform
*    any post PHY training functions. It returns immediately after PHY training.
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
*    lchavani
*
******************************************************************************/
unsigned mddr_margining_init(target_mode_e mode, soc_hw_version_t soc_hw_version, mddr_settings_t *mddr_settings_ptr)
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

    // Reset MDDR PwrOkIn signal
    // This is required whenever we run a second/subsuqent mddr margining init sequence without resetting the PHY.
    mddr_set_reg(GCCMW_MDDR_PWROK, "GCCMW_MDDR_PWROK", 0x0);

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
            monaco_log(CRITICAL,"¥n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n");
            monaco_log(CRITICAL,"ADJUST: 1 DIMM per channel populated, software max DDR Clock reduced to %d MHz.¥n", max_1dpc_freq_hw);
            monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n¥n");

            mddr_settings_ptr->max_1dimm_freq_mhz = max_1dpc_freq_hw;
        }

        // Choose the minimum of desired DDR clock and software DDR clock max
        if (mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] > mddr_settings_ptr->max_1dimm_freq_mhz)
        {
            monaco_log(CRITICAL,"¥n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n");
            monaco_log(CRITICAL,"ADJUST: 1 DIMM per channel populated, desired DDR Clock (%d MHz) exceeds software max DDR Clock (%d MHz) ¥n",
                                  mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1], mddr_settings_ptr->max_1dimm_freq_mhz);
            monaco_log(CRITICAL,"DDR Clock reduced to %d MHz.¥n", mddr_settings_ptr->max_1dimm_freq_mhz);
            monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n¥n");

            mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] = mddr_settings_ptr->max_1dimm_freq_mhz;
        }
    }
    else if (num_dimms_per_chan_poped > 1)
    {
        // Choose the minimum of software DDR clock max and hardware supported DDR clock max
        if (mddr_settings_ptr->max_2dimm_freq_mhz > max_2dpc_freq_hw)
        {
            monaco_log(CRITICAL,"¥n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n");
            monaco_log(CRITICAL,"ADJUST: 2 DIMMs per channel populated, software max DDR Clock reduced to %d MHz.¥n", max_2dpc_freq_hw);
            monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n¥n");

            mddr_settings_ptr->max_2dimm_freq_mhz = max_2dpc_freq_hw;
        }

        // Choose the minimum of desired DDR clock and software DDR clock max
        if (mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1] > mddr_settings_ptr->max_2dimm_freq_mhz)
        {
            monaco_log(CRITICAL,"¥n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n");
            monaco_log(CRITICAL,"ADJUST: 2 DIMMs per channel populated, desired DDR Clock (%d MHz) exceeds software max DDR Clock (%d MHz) ¥n",
                                  mddr_settings_ptr->mem_freq_mhz[DDR_FREQ_1], mddr_settings_ptr->max_2dimm_freq_mhz);
            monaco_log(CRITICAL,"DDR Clock reduced to %d MHz.¥n", mddr_settings_ptr->max_2dimm_freq_mhz);
            monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n¥n");

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
        monaco_log(CRITICAL,"¥n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n");
        monaco_log(CRITICAL,"ADJUST: DIMMs speed grade below requested frequency. DDR Clock reduced to %d MHz.¥n", max_dimm_freq);
        monaco_log(CRITICAL,"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^¥n¥n");
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
           monaco_log(HIGH, "Ignoring write/read 2T preamble feature since data rate<2400, data rate = %d¥n", ddr_rate);
           // write/read 2tCK preamble (0=disable, 1=2T read, 2=2T write, 3=2T write & read)
           mddr_settings_ptr->ddr4_2t_preamble_mode = DDR4_2T_DISABLE;
        }
    }
    else
    {
        if (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_DISABLE)
        {
            monaco_log(HIGH,"¥nSetting DDR4 2T Preamble to READ configuration since data rate>=2400, data rate = %d¥n", ddr_rate);
            mddr_settings_ptr->ddr4_2t_preamble_mode = DDR4_2T_READ;
        }
        else if (mddr_settings_ptr->ddr4_2t_preamble_mode == DDR4_2T_WRITE)
        {
            monaco_log(HIGH,"¥nSetting DDR4 2T Preamble to WRITE_READ configuration since data rate>=2400, data rate = %d¥n", ddr_rate);
            mddr_settings_ptr->ddr4_2t_preamble_mode = DDR4_2T_WRITE_READ;
        }
     }

    // Get the SI data for the platform.
#ifndef CONFIG_TESTOS_EMU
    mddr_get_si(mddr_settings_ptr);
#endif

    if(status == COM_OK)
    {
        // Force disable DDR4 modes that are frequency dependent.
        //  Table 106, pg 204 JEDEC 79-4A
        if(common_cfg.dev_type == SPD_DEVICE_TYPE_DDR4)
        {
            if(ddr_rate < 2666)
            {
                if (mddr_settings_ptr->ddr4_wr_crc_en)
                {
                    monaco_log(HIGH, "Ignoring write CRC enable feature since data rate<2666, data rate = %d¥n", ddr_rate);
                    mddr_settings_ptr->ddr4_wr_crc_en = false;
                }

                if (mddr_settings_ptr->ddr4_geardown_mode_en)
                {
                    monaco_log(HIGH, "Ignoring geardown mode since data rate<2666, data rate = %d¥n", ddr_rate);
                    mddr_settings_ptr->ddr4_geardown_mode_en = false;
                }
            }
        }

        if ((!common_cfg.has_ecc) && (mddr_settings_ptr->disable_ecc == false))
        {
            monaco_log(HIGH, "Ignoring ECC feature since DIMMs do not support ECC¥n");
            mddr_settings_ptr->disable_ecc = true;
        }

        if((common_cfg.mod_type == SPD_MODULE_TYPE_RDIMM)&&(mddr_settings_ptr->ca_parity == CA_PARITY_DRAM))
        {
            monaco_log(HIGH, "Ignoring DRAM CA Parity feature with DIMM CA Parity disabled for RDIMMs¥n");
            mddr_settings_ptr->ca_parity = CA_PARITY_DISABLE;
        }

        // This setting is ignored by hardware whenever 1 pair of channels is
        //  populated, however, we only print a warning and if a setting other
        //  than the default is detected.
        if((num_chans_poped <= 2)&&(mddr_settings_ptr->ddr_granule != DDR_DIST_GRANULE_256B))
        {
            monaco_log(HIGH, "Ignoring channel interleaving granule setting when only one pair of channels is populated¥n");
            // Warn and ignore but do not override because the Ring Switches have already been programmed
        }

        // DIMM interleaving is only valid if both slots populated and they have the same amount of memory.
        if ((mddr_settings_ptr->dimm_intlv_en) && (num_dimms_per_chan_poped != DDR_MAX_NUM_SLOTS_PER_CHAN))
        {
            // Override the interleaving setting
            monaco_log(HIGH,"Ignoring DIMM Interleave mode since only 1 DIMM is populated per channel¥n");
            mddr_settings_ptr->dimm_intlv_en = false;
        }

        if ((mddr_settings_ptr->dimm_intlv_en) && (common_cfg.slot_config[0].dimm_size_mb != common_cfg.slot_config[1].dimm_size_mb))
        {
            // Override the interleaving setting
            monaco_log(HIGH,"Ignoring DIMM Interleave mode since populated DIMMs have different amounts of memory¥n");
            mddr_settings_ptr->dimm_intlv_en = false;
        }

        if (platform_mode != SILICON)
        {
            if(mddr_settings_ptr->periodic_zq_cal_en)
            {
                monaco_log(HIGH, "Ignoring periodic ZQ cal enable setting on emulation¥n");
                mddr_settings_ptr->periodic_zq_cal_en = false;
            }

            if(mddr_settings_ptr->dfi_lp_mode == DFI_LP_SR_ENA_LP2_ENA)
            {
                monaco_log(HIGH, "Ignoring DFI LP2 enable setting on emulation¥n");
                mddr_settings_ptr->dfi_lp_mode = DFI_LP_SR_ENA;
            }

            if(mddr_settings_ptr->dfi_lp_mode == DFI_LP_SR_PD_ENA_LP2_ENA)
            {
                monaco_log(HIGH, "Ignoring DFI LP2 enable setting on emulation¥n");
                mddr_settings_ptr->dfi_lp_mode = DFI_LP_SR_PD_ENA;
            }

            if(mddr_settings_ptr->therm_throttle_en)
            {
                monaco_log(HIGH, "Ignoring Thermal Throttle enable setting on emulation¥n");
                mddr_settings_ptr->therm_throttle_en = false;
            }
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

        // Self-refresh is disabled before we run margining. It might be turned ON during the regular init.
        // Hence, explicitly disabling self-refresh here
        mddr_auto_self_refresh_disable();

        for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
        {
            if (mddr_check_chan_populated(ddr_chan))
            {

                // Initialize the memory controller
                status |= mddr_mc_init(mddr_settings_ptr, ddr_chan);

                // Initialize the PHY
                status |= mddr_phy_init(ddr_chan);

                // PHY training
#if MDDR_CONFIG_ENHANCED_TRAINING
				status |= mddr_phy_enhanced_training(mddr_settings_ptr, ddr_chan);
#else
                status |= mddr_phy_train(mddr_settings_ptr, ddr_chan);
#endif


                // Enable DIMM Critical Temperature event_n [CR65]
                status |= spd_ts_smbus_init(mddr_settings_ptr, ddr_chan);

            }
            else
            {
                mddr_lockdown_unused_chan(ddr_chan);
            }
        }
    }
    else
    {
        monaco_log(CRITICAL, " ERROR : The MDDR Subsystem could not be initialized. ¥n");
    }

    // Copy the initialization settings. Follows the sub-component initializiations
    //  to reflect any overrides imposed during initialization.
    mddr_record_init_parms(mddr_settings_ptr);

    return status;
}




/*!****************************************************************************
*
* @par Description:
*    This function sets the SI data given the mode.  Should also take into
*    account the frequency, number of slots populated (including ranks per
*    slot), type of dimm, and possibly channel and number of slots available.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
*
* @return
*    None
*
* @author
*    gkowis/lchavani
*
******************************************************************************/
void mddr_get_si(mddr_settings_t *mddr_settings_ptr)
{
    mddr_si_selector_t selector;
    uint8_t ddr_chan;
    uint8_t dimm_slot;

    uint8_t rank_rtw_3ds  = 0x3;    // Cycle adjust for 3ds diff rank RTW
    uint8_t srank_rtw_3ds = 0x5;    // Cycle adjust for 3ds same rank RTW
    uint8_t srank_rtw_lr  = 0x4;    // Cycle adjust for LRDIMM same rank RTW
    uint8_t srank_rtr_lr  = 0x4;    // Cycle adjust for LRDIMM same rank RTR

    for (ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        selector.ddr_chan = ddr_chan;
        selector.mem_freq_mhz = mem_freq_mhz;
        selector.num_dimm_slots = mddr_settings_ptr->num_dimm_slots;
        selector.num_dimm_slots_pop = 0;


        for (dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            selector.num_ranks_slot[dimm_slot] = common_cfg.slot_config[dimm_slot].num_ranks;

            if (selector.num_ranks_slot[dimm_slot] != SPD_INVALID_RANK_COUNT)
            {
                ++selector.num_dimm_slots_pop;

                // In case of LRDIMM, due to the DB, it needs to a single rank config
                // when we obtain the SI.
                if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
                {
                    selector.num_ranks_slot[dimm_slot] = DDR_RANKS_SINGLE_CS_DIMM;
                }
            }
        }

        #ifdef __BAREMETAL__
            // This is the simplified SI function to set/load the SI data structure
            mddr_get_sdp_si(&selector, &si_data[ddr_chan]);

            // This function parses and sets/loads the SI data structure based on the consolidated SI binary file
            // provided. The SI binary file is expected to have the SI data for all possible configurations.
            //mddr_load_si(&selector, &si_data[ddr_chan]);
        #else
            ddr_get_si(&selector, &si_data[ddr_chan]);
        #endif

        // Configure the LRDIMM SI for Host and DRAM interface
        if (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM)
        {
            mddr_si_configure_lrdimm_db(&si_data[ddr_chan], ddr_chan);
        }

        // In case of 3DS DIMMs, increment only the applicable gaps to the values specified here
        if((platform_mode == SILICON) && (common_cfg.is_3DS))
        {
            si_data[ddr_chan].cycle_adjusts.rank_rtw += rank_rtw_3ds;
            if (si_data[ddr_chan].cycle_adjusts.rank_rtw > DDR_CYCLES_ADJ_RDWR_MAX)
            {
                si_data[ddr_chan].cycle_adjusts.rank_rtw = DDR_CYCLES_ADJ_RDWR_MAX;
            }

            si_data[ddr_chan].cycle_adjusts.srank_rtw += srank_rtw_3ds;
            if (si_data[ddr_chan].cycle_adjusts.srank_rtw > DDR_CYCLES_ADJ_RDWR_MAX)
            {
                si_data[ddr_chan].cycle_adjusts.srank_rtw = DDR_CYCLES_ADJ_RDWR_MAX;
            }

            monaco_log(MEDIUM,"¥n ** Detected 3DS DIMM: Increasing the applicable gaps by the values specified below: **¥n");
            monaco_log(MEDIUM,"Increased additional DDR cycles from RD to WR targeting different ranks in a chip select by %d¥n", rank_rtw_3ds);
            monaco_log(MEDIUM,"Increased additional DDR cycles from RD to WR targeting the same rank by %d¥n", srank_rtw_3ds);
        }

        // In case of LRDIMMs, increment only the applicable gaps to the values specified here
        if((platform_mode == SILICON) && (common_cfg.mod_type == SPD_MODULE_TYPE_DDR4_LRDIMM) &&
            (mddr_settings_ptr->ddr4_2t_preamble_mode & (DDR4_2T_READ | DDR4_2T_WRITE_READ)))
        {
            si_data[ddr_chan].cycle_adjusts.srank_rtw += srank_rtw_lr;
            if (si_data[ddr_chan].cycle_adjusts.srank_rtw > DDR_CYCLES_ADJ_RDWR_MAX)
            {
                si_data[ddr_chan].cycle_adjusts.srank_rtw = DDR_CYCLES_ADJ_RDWR_MAX;
            }

            si_data[ddr_chan].cycle_adjusts.srank_rtr += srank_rtr_lr;
            if (si_data[ddr_chan].cycle_adjusts.srank_rtr > DDR_CYCLES_ADJ_RDWR_MAX)
            {
                si_data[ddr_chan].cycle_adjusts.srank_rtr = DDR_CYCLES_ADJ_RDWR_MAX;
            }

            monaco_log(MEDIUM,"¥n ** Detected LRDIMM with 2TCK Read: Increasing the applicable gaps by the values specified below: **¥n");
            monaco_log(MEDIUM,"Increased additional DDR cycles from RD to WR targeting the same rank by %d¥n", srank_rtw_lr);
            monaco_log(MEDIUM,"Increased additional DDR cycles from RD to RD targeting the same rank by %d¥n", srank_rtr_lr);
        }
    }
}

#ifdef CONFIG_TESTOS_EMU
void mddr_presil_set_ddr_clk_mux(uint8_t ddr_chan)
{
    uint32_t val = 2;
    uint32_t mask = GCCMS_MDDRN_CGF4R_MUX_SEL___M;



    if (ddr_chan == 0)
    {
        mddr_rmw_reg(N_GCCMS_MDDR_0_CGF4R, "N_GCCMS_MDDR_0_CGF4R", mask, val);  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_rmw_reg(N_GCCMS_MDDR_1_CGF4R, "N_GCCMS_MDDR_0_CGF4R", mask, val);  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_rmw_reg(S_GCCMS_MDDR_2_CGF4R, "N_GCCMS_MDDR_0_CGF4R", mask, val);  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_rmw_reg(N_GCCMS_MDDR_2_CGF4R, "N_GCCMS_MDDR_0_CGF4R", mask, val);  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_rmw_reg(S_GCCMS_MDDR_0_CGF4R, "N_GCCMS_MDDR_0_CGF4R", mask, val);  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_rmw_reg(S_GCCMS_MDDR_1_CGF4R, "N_GCCMS_MDDR_0_CGF4R", mask, val);  // hddrss1
    }
}
#endif


/*!****************************************************************************
*
* @par Description:
*    This function is to release the GCC reset for the specified DDR channel.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*
* @return
*    None
*
* @author
*    gkowis, lchavani
*
******************************************************************************/
void mddr_release_chan_gcc_resetr(mddr_settings_t *mddr_settings_ptr)
{
    uint8_t ddr_chan;
    uint64_t mddr_base_addr;
    uint8_t dimm_slot;

// 1
    // assert clkgenx areset for all controllers
    monaco_log(HIGH, "Asserting CLKGENx areset for HDDRSS 0, 1, 5¥n");
    mddr_set_reg(N_GCCMS_SPARE_0, "N_GCCMS_SPARE_0", 0x7);

    monaco_log(HIGH, "Asserting CLKGENx areset for HDDRSS 2, 3, 4¥n");
    mddr_set_reg(S_GCCMS_SPARE_0, "N_GCCMS_SPARE_0", 0x7);
// 2
    // deassert clkgenx areset for all controllers
    monaco_log(HIGH, "Deasserting CLKGENx areset for HDDRSS 0, 1, 5¥n");
    mddr_set_reg(N_GCCMS_SPARE_0, "N_GCCMS_SPARE_0", 0x0);

    monaco_log(HIGH, "Deasserting CLKGENx areset for HDDRSS 2, 3, 4¥n");
    mddr_set_reg(S_GCCMS_SPARE_0, "N_GCCMS_SPARE_0", 0x0);

    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {

#if defined(CONFIG_PRE_S1) || defined(CONFIG_PRE_HAPS)
        if(ddr_chan == 1 || ddr_chan == 4)
            ;
        else
            continue;
#endif

        mddr_base_addr = mddr_base_addrs[ddr_chan];

// 3
        mddr_deassert_clkgen_pwrdn_b(ddr_chan);
// 4
        mddr_enable_chan_gcc_ahb_clock(ddr_chan);
// 5

#ifdef CONFIG_TESTOS_EMU
        mddr_presil_set_ddr_clk_mux(ddr_chan);
#endif

        if (platform_mode == SILICON)
        {
            if (mddr_settings_ptr->clk_type == CLK_INTERNAL_CLKGEN)
            {
                mddr_clkgen_init(mddr_settings_ptr, mddr_base_addr, ddr_chan);
                mddr_set_ddr_clk_mux(mddr_settings_ptr, ddr_chan);
            }
            else if (mddr_settings_ptr->clk_type == CLK_EXTERNAL_AGERA)
            {
                // For CLK_EXTERNAL_AGERA, currently for Baremetal,
                // the clocks are initialized outside the scope of the driver
            }
            else
            {
                monaco_log(CRITICAL, "ERROR: Clock type is invalid¥n");
            }
        }
// 6
        mddr_enable_chan_gcc_2x_clock(ddr_chan);
// 7
        mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT0_CONFIG_OFFSET, "DIMM_SLOT0_CONFIG", (0x1 << SLOT_CONFIG_SLOT_EN___S));
        mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT1_CONFIG_OFFSET, "DIMM_SLOT1_CONFIG", (0x1 << SLOT_CONFIG_SLOT_EN___S));
// 8
        // assert reset, enable clocks, disable cke
        mddr_mc_assert_reset(mddr_base_addr);
// 9
        if (platform_mode == SILICON)
        {
            //  wait 1 ms; need to verify timer finished
            mddr_mc_wait_us(mddr_base_addr, 1000);
        }
        monaco_log(HIGH, "Assert MDDR PwrOkIn signal¥n");
        mddr_rmw_reg(GCCMW_MDDR_PWROK, "GCCMW_MDDR_PWROK", (0x1<<hddrss[ddr_chan]), (0x1<<hddrss[ddr_chan]));
// 10
        if (platform_mode == SILICON)
        {
            //  wait 1 ms; 128 DRAM clocks
            mddr_mc_wait_us(mddr_base_addr, 1000);
        }
        mddr_deassert_chan_gcc_apb_reset(ddr_chan);
        mddr_deassert_chan_gcc_phy_areset(ddr_chan);
// 11
        monaco_log(HIGH, "Remove Fence: APB and dfi_init_complete inputs from the DDR PHY¥n");
        mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_OFFSET, "DDR_MANUAL", 0x4);
// Slot config
        if (mddr_check_chan_populated(ddr_chan))
        {
             if (num_dimms_per_chan_poped == 1)
             {
                 for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
                 {
                     // set SLOT_EN=0 for the slot that is unused
                     if(mddr_dimm_configs[ddr_chan][dimm_slot].dev_type == SPD_DEVICE_TYPE_UNDEFINED)
                     {
                         if (dimm_slot == 0)
                            mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT0_CONFIG_OFFSET, "DIMM_SLOT0_CONFIG", 0x0);
                         else
                            mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT1_CONFIG_OFFSET, "DIMM_SLOT1_CONFIG", 0x0);
                     }
                 }
             }
        }
        else    // controller not used
        {
            mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT0_CONFIG_OFFSET, "DIMM_SLOT0_CONFIG", 0x0);
            mddr_set_reg(mddr_base_addr + MDDR_DIMM_SLOT1_CONFIG_OFFSET, "DIMM_SLOT1_CONFIG", 0x0);
        }
    }

    monaco_log(CRITICAL, "Setting DDR clock to %d MHz¥n", mem_freq_mhz);
}

//
// The following functions directly manipulate GCC HW funcionality ouside the MDDR
//  Subsystem. These need to be replaced with the appropriate external hooks when not
//  running in a baremetal environment.
//
//! @todo -GPK- Direct GCC block accesses : Replace with appropriate external hooks for CoreBSP integration


/*!****************************************************************************
*
* @par Description:
*    This function is to releases the APB reset for the specified DDR channel.
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
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_deassert_chan_gcc_apb_reset(uint8_t ddr_chan)
{
    uint32_t val = 0;
    uint32_t mask = GCCMS_MDDRN_RESETR_APB_ARES___M;


    if (ddr_chan == 0)
    {
        mddr_rmw_reg(N_GCCMS_MDDR0_RESETR, "N_GCCMS_MDDR0_RESETR", mask, val);  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_rmw_reg(N_GCCMS_MDDR1_RESETR, "N_GCCMS_MDDR1_RESETR", mask, val);  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_rmw_reg(S_GCCMS_MDDR2_RESETR, "S_GCCMS_MDDR2_RESETR", mask, val);  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_rmw_reg(N_GCCMS_MDDR2_RESETR, "N_GCCMS_MDDR2_RESETR", mask, val);  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_rmw_reg(S_GCCMS_MDDR0_RESETR, "S_GCCMS_MDDR0_RESETR", mask, val);  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_rmw_reg(S_GCCMS_MDDR1_RESETR, "S_GCCMS_MDDR1_RESETR", mask, val);  // hddrss1
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function is to release the PHY Areset for the specified DDR channel.
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
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_deassert_chan_gcc_phy_areset(uint8_t ddr_chan)
{
    uint32_t val = 0;
    uint32_t mask = GCCMS_MDDRN_RESETR_PHY_ARES___M;


    if (ddr_chan == 0)
    {
        mddr_rmw_reg(N_GCCMS_MDDR0_RESETR, "N_GCCMS_MDDR0_RESETR", mask, val);  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_rmw_reg(N_GCCMS_MDDR1_RESETR, "N_GCCMS_MDDR1_RESETR", mask, val);  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_rmw_reg(S_GCCMS_MDDR2_RESETR, "S_GCCMS_MDDR2_RESETR", mask, val);  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_rmw_reg(N_GCCMS_MDDR2_RESETR, "N_GCCMS_MDDR2_RESETR", mask, val);  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_rmw_reg(S_GCCMS_MDDR0_RESETR, "S_GCCMS_MDDR0_RESETR", mask, val);  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_rmw_reg(S_GCCMS_MDDR1_RESETR, "S_GCCMS_MDDR1_RESETR", mask, val);  // hddrss1
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function is to release OR assert the GCC reset for the specified DDR channel.
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*                                  @param
*    val                Value to release OR asset the GCC reset for that channel.
*
* @return
*    None
*
* @author
*    gkowis, lchavani
*
* @par Notes:
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_update_chan_gcc_reset(uint8_t ddr_chan, uint32_t val)
{

    if (ddr_chan == 0)
    {
        mddr_set_reg(N_GCCMS_MDDR0_RESETR, "N_GCCMS_MDDR0_RESETR", val);  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_set_reg(N_GCCMS_MDDR1_RESETR, "N_GCCMS_MDDR1_RESETR", val);  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_set_reg(S_GCCMS_MDDR2_RESETR, "S_GCCMS_MDDR2_RESETR", val);  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_set_reg(N_GCCMS_MDDR2_RESETR, "N_GCCMS_MDDR2_RESETR", val);  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_set_reg(S_GCCMS_MDDR0_RESETR, "S_GCCMS_MDDR0_RESETR", val);  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_set_reg(S_GCCMS_MDDR1_RESETR, "S_GCCMS_MDDR1_RESETR", val);  // hddrss1
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function is to disable AHB clock for the specified DDR channel.
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
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_disable_chan_gcc_ahb_clock(uint8_t ddr_chan)
{
    uint32_t val  = 0x0;
    uint32_t mask = GCCMS_MDDR2_AHB_CBCR_CLK_EN___M;


    if (ddr_chan == 0)
    {
        mddr_rmw_reg(GCCMW_MDDR2_AHB_CBCR, "GCCMW_MDDR2_AHB_CBCR", mask, val);  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_rmw_reg(GCCMW_MDDR3_AHB_CBCR, "GCCMW_MDDR3_AHB_CBCR", mask, val);  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_rmw_reg(GCCE_MDDR5_AHB_CBCR, "GCCE_MDDR5_AHB_CBCR", mask, val);  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_rmw_reg(GCCE_MDDR4_AHB_CBCR, "GCCE_MDDR4_AHB_CBCR", mask, val);  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_rmw_reg(GCCMW_MDDR0_AHB_CBCR, "GCCMW_MDDR0_AHB_CBCR", mask, val);  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_rmw_reg(GCCMW_MDDR1_AHB_CBCR, "GCCMW_MDDR1_AHB_CBCR", mask, val);  // hddrss1
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function is to enable AHB clock for the specified DDR channel.
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
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_enable_chan_gcc_ahb_clock(uint8_t ddr_chan)
{
    uint32_t val  = GCCMS_MDDR2_AHB_CBCR_CLK_EN___M;
    uint32_t mask = GCCMS_MDDR2_AHB_CBCR_CLK_EN___M;


    if (ddr_chan == 0)
    {
        mddr_rmw_reg(GCCMW_MDDR2_AHB_CBCR, "GCCMW_MDDR2_AHB_CBCR", mask, val);  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_rmw_reg(GCCMW_MDDR3_AHB_CBCR, "GCCMW_MDDR3_AHB_CBCR", mask, val);  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_rmw_reg(GCCE_MDDR5_AHB_CBCR, "GCCE_MDDR5_AHB_CBCR", mask, val);  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_rmw_reg(GCCE_MDDR4_AHB_CBCR, "GCCE_MDDR4_AHB_CBCR", mask, val);  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_rmw_reg(GCCMW_MDDR0_AHB_CBCR, "GCCMW_MDDR0_AHB_CBCR", mask, val);  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_rmw_reg(GCCMW_MDDR1_AHB_CBCR, "GCCMW_MDDR1_AHB_CBCR", mask, val);  // hddrss1
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function is to disable 2X clock for the specified DDR channel.
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
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_disable_chan_gcc_2x_clock(uint8_t ddr_chan)
{
    uint32_t val = 0x0;
    uint32_t mask = GCCMS_MDDRN_2X_CBCR_CLK_ENABLE___M;


    if (ddr_chan == 0)
    {
        mddr_rmw_reg(N_GCCMS_MDDR0_2X_CBCR, "N_GCCMS_MDDR0_2X_CBCR", mask, val);  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_rmw_reg(N_GCCMS_MDDR1_2X_CBCR, "N_GCCMS_MDDR1_2X_CBCR", mask, val);  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_rmw_reg(S_GCCMS_MDDR2_2X_CBCR, "S_GCCMS_MDDR2_2X_CBCR", mask, val);  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_rmw_reg(N_GCCMS_MDDR2_2X_CBCR, "N_GCCMS_MDDR2_2X_CBCR", mask, val);  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_rmw_reg(S_GCCMS_MDDR0_2X_CBCR, "S_GCCMS_MDDR0_2X_CBCR", mask, val);  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_rmw_reg(S_GCCMS_MDDR1_2X_CBCR, "S_GCCMS_MDDR1_2X_CBCR", mask, val);  // hddrss1
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function is to enable 2X clock for the specified DDR channel.
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
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_enable_chan_gcc_2x_clock(uint8_t ddr_chan)
{


    if (ddr_chan == 0)
    {
        mddr_cbc_enable(N_GCCMS_MDDR0_2X_CBCR, "N_GCCMS_MDDR0_2X_CBCR");  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_cbc_enable(N_GCCMS_MDDR1_2X_CBCR, "N_GCCMS_MDDR1_2X_CBCR");  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_cbc_enable(S_GCCMS_MDDR2_2X_CBCR, "S_GCCMS_MDDR2_2X_CBCR");  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_cbc_enable(N_GCCMS_MDDR2_2X_CBCR, "N_GCCMS_MDDR2_2X_CBCR");  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_cbc_enable(S_GCCMS_MDDR0_2X_CBCR, "S_GCCMS_MDDR0_2X_CBCR");  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_cbc_enable(S_GCCMS_MDDR1_2X_CBCR, "S_GCCMS_MDDR1_2X_CBCR");  // hddrss1
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function is to deassert power down control for the PCIe clock gen
*     for the specified DDR channel. This is an active low signal
*
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    None
*
* @author
*    lchavani
*
* @par Notes:
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_deassert_clkgen_pwrdn_b(uint8_t ddr_chan)
{
    uint32_t val = 1;

    if (ddr_chan == 0)
    {
        mddr_set_reg(N_GCCMS_MDDR0_CLKGEN_MISC, "N_GCCMS_MDDR0_CLKGEN_MISC", val);  // hddrss2
    }
    else if (ddr_chan == 1)
    {
        mddr_set_reg(N_GCCMS_MDDR1_CLKGEN_MISC, "N_GCCMS_MDDR1_CLKGEN_MISC", val);  // hddrss3
    }
    else if (ddr_chan == 2)
    {
        mddr_set_reg(S_GCCMS_MDDR2_CLKGEN_MISC, "S_GCCMS_MDDR2_CLKGEN_MISC", val);  // hddrss5
    }
    else if (ddr_chan == 3)
    {
        mddr_set_reg(N_GCCMS_MDDR2_CLKGEN_MISC, "N_GCCMS_MDDR2_CLKGEN_MISC", val);  // hddrss4
    }
    else if (ddr_chan == 4)
    {
        mddr_set_reg(S_GCCMS_MDDR0_CLKGEN_MISC, "S_GCCMS_MDDR0_CLKGEN_MISC", val);  // hddrss0
    }
    else if (ddr_chan == 5)
    {
        mddr_set_reg(S_GCCMS_MDDR1_CLKGEN_MISC, "S_GCCMS_MDDR1_CLKGEN_MISC", val);  // hddrss1
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function configures the clock mux based on the clock source
*     for the specified DDR channel.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
* @return
*    None
*
* @author
*    lchavani
*
* @par Notes:
*    The manipulates MDDR specific controls in the GCC block outside of
*     the MDDR subsystem.
*
******************************************************************************/
void mddr_set_ddr_clk_mux(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan)
{
    uint32_t val = 0x0;
    uint32_t reg_val = 0x0;
    uint32_t select = 0x0;
    uint32_t mask = GCCMS_MDDRN_CGF4R_MUX_SEL___M;
    uint32_t root_en;

    // mux_sel: 0 = XO, 1 = clkgen, 2 = pll1, 3 = test
    if (mddr_settings_ptr->clk_type == CLK_EXTERNAL_AGERA)
    {
        select = 0x2;    // pll1
    }
    else  // CLKGEN
    {
        select = 0x1;    // clkgen
    }

    root_en = (uint32_t)GCCMS_MDDRN_CGF4R_ROOT_EN___M << GCCMS_MDDRN_CGF4R_ROOT_EN___S;
    val = root_en | select;


    if (ddr_chan == 0)
    {
        mddr_rmw_reg(N_GCCMS_MDDR_0_CGF4R, "N_GCCMS_MDDR_0_CGF4R", mask, val);  // hddrss2
        while(((reg_val >> 4) & 0xF) != (select << 1))
        {
            reg_val = mddr_get_reg(N_GCCMS_MDDR_0_CGF4R, "N_GCCMS_MDDR_0_CGF4R");
        }

    }
    else if (ddr_chan == 1)
    {
        mddr_rmw_reg(N_GCCMS_MDDR_1_CGF4R, "N_GCCMS_MDDR_1_CGF4R", mask, val);  // hddrss3
        while(((reg_val >> GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___S) & GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___M) != (select << 1))
        {
            reg_val = mddr_get_reg(N_GCCMS_MDDR_1_CGF4R, "N_GCCMS_MDDR_1_CGF4R");
        }
    }
    else if (ddr_chan == 2)
    {
        mddr_rmw_reg(S_GCCMS_MDDR_2_CGF4R, "S_GCCMS_MDDR_2_CGF4R", mask, val);  // hddrss5
        while(((reg_val >> GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___S) & GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___M) != (select << 1))
        {
            reg_val = mddr_get_reg(S_GCCMS_MDDR_2_CGF4R, "S_GCCMS_MDDR_2_CGF4R");
        }
    }
    else if (ddr_chan == 3)
    {
        mddr_rmw_reg(N_GCCMS_MDDR_2_CGF4R, "N_GCCMS_MDDR_2_CGF4R", mask, val);  // hddrss4
        while(((reg_val >> GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___S) & GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___M) != (select << 1))
        {
            reg_val = mddr_get_reg(N_GCCMS_MDDR_2_CGF4R, "N_GCCMS_MDDR_2_CGF4R");
        }
    }
    else if (ddr_chan == 4)
    {
        mddr_rmw_reg(S_GCCMS_MDDR_0_CGF4R, "S_GCCMS_MDDR_0_CGF4R", mask, val);  // hddrss0
        while(((reg_val >> GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___S) & GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___M) != (select << 1))
        {
            reg_val = mddr_get_reg(S_GCCMS_MDDR_0_CGF4R, "S_GCCMS_MDDR_0_CGF4R");
        }
    }
    else if (ddr_chan == 5)
    {
        mddr_rmw_reg(S_GCCMS_MDDR_1_CGF4R, "S_GCCMS_MDDR_1_CGF4R", mask, val);  // hddrss1
        while(((reg_val >> GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___S) & GCCMS_MDDRN_CGF4R_MUX_SEL_STATUS___M) != (select << 1))
        {
            reg_val = mddr_get_reg(S_GCCMS_MDDR_1_CGF4R, "S_GCCMS_MDDR_1_CGF4R");
        }
    }
}
