#ifndef _SPD_DDR3_BLOCK_H
#define _SPD_DDR3_BLOCK_H

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
* Filename: spd_ddr3_block.h
*
* Description: Provides the DDR3 specific offsets / structure of an SPD block as
*               defined for DDR3 DIMMs.
*
******************************************************************************/

/******************************************************************************
* Defined Constants and Macros
******************************************************************************/
// SPD EEPROM Field Byte Offsets/IDs DDR3
#define SPD_OFFSET_DDR3_MODULE_NOM_VOLTAGE          0x06
#define SPD_OFFSET_DDR3_MODULE_ORGANIZATION         0x07
#define SPD_OFFSET_DDR3_MODULE_MEMORY_BUS_WIDTH     0x08
#define SPD_OFFSET_DDR3_FTB_DIVIDEND_DIVISOR        0x09
#define SPD_OFFSET_DDR3_MTB_DIVIDEND                0x0A
#define SPD_OFFSET_DDR3_MTB_DIVISOR                 0x0B
#define SPD_OFFSET_DDR3_TCKMIN_MTB                  0x0C
#define SPD_OFFSET_DDR3_TCKMIN_FTB                  0x22
#define SPD_OFFSET_DDR3_CAS_LAT_LSB                 0x0E
#define SPD_OFFSET_DDR3_CAS_LAT_MSB                 0x0F
#define SPD_OFFSET_DDR3_TAAMIN_MTB                  0x10
#define SPD_OFFSET_DDR3_TAAMIN_FTB                  0x23
#define SPD_OFFSET_DDR3_TWRMIN                      0x11
#define SPD_OFFSET_DDR3_TRCDMIN_MTB                 0x12
#define SPD_OFFSET_DDR3_TRCDMIN_FTB                 0x24
#define SPD_OFFSET_DDR3_TRRDMIN                     0x13
#define SPD_OFFSET_DDR3_TRPMIN_MTB                  0x14
#define SPD_OFFSET_DDR3_TRPMIN_FTB                  0x25
#define SPD_OFFSET_DDR3_TRC_TRAS_MSB                0x15
#define SPD_OFFSET_DDR3_TRAS_LSB                    0x16
#define SPD_OFFSET_DDR3_TRC_LSB                     0x17
#define SPD_OFFSET_DDR3_TRC_FTB                     0x26
#define SPD_OFFSET_DDR3_TRFCMIN_LSB                 0x18
#define SPD_OFFSET_DDR3_TRFCMIN_MSB                 0x19
#define SPD_OFFSET_DDR3_TWTRMIN                     0X1A
#define SPD_OFFSET_DDR3_TRTPMIN                     0X1B
#define SPD_OFFSET_DDR3_TFAWMIN_MSB                 0x1C
#define SPD_OFFSET_DDR3_TFAWMIN_LSB                 0x1D
#define SPD_OFFSET_DDR3_THERMAL_REFRESH_OPT         0x1F
#define SPD_OFFSET_DDR3_MODULE_THERMAL_SENSOR       0x20
#define SPD_OFFSET_DDR3_SDRAM_DEVICE_TYPE           0x21
#define SPD_OFFSET_DDR3_UDIMM_MIRROR                0x3F

// DDR3 RDIMM Specific
#define SPD_OFFSET_DDR3_RDIMM_RC1_RC0               0x45
#define SPD_OFFSET_DDR3_RDIMM_RC3_RC2               0x46
#define SPD_OFFSET_DDR3_RDIMM_RC5_RC4               0x47
#define SPD_OFFSET_DDR3_RDIMM_RC7_RC6               0x48
#define SPD_OFFSET_DDR3_RDIMM_RC9_RC8               0x49
#define SPD_OFFSET_DDR3_RDIMM_RC11_RC10             0x4A
#define SPD_OFFSET_DDR3_RDIMM_RC13_RC12             0x4B
#define SPD_OFFSET_DDR3_RDIMM_RC15_RC14             0x4C

// DDR3 Manufacturing Information
#define SPD_OFFSET_DDR3_MFG_ID_LSB                  0x75
#define SPD_OFFSET_DDR3_MFG_ID_MSB                  0x76
#define SPD_OFFSET_DDR3_MFG_SN_0                    0x7A
#define SPD_OFFSET_DDR3_MFG_SN_1                    0x7B
#define SPD_OFFSET_DDR3_MFG_SN_2                    0x7C
#define SPD_OFFSET_DDR3_MFG_SN_3                    0x7D
#define SPD_OFFSET_DDR3_PART_NUM_LSB                0x80  // 18 contigious bytes for part number.


// EEPROM Field / subfield access constants.
//
// Note: Some fields are stored as a power of 2 and are scaled to save bits.
//  I.e. Eliminating values that are smaller than the minimum value.
//

#define SPD_DDR3_DIE_COUNT___M                      0x00000007
#define SPD_DDR3_DIE_COUNT___S                      0x4
#define SPD_DDR3_DIE_COUNT_NA                       0x0
#define SPD_DDR3_DIE_COUNT_1                        0x1
#define SPD_DDR3_DIE_COUNT_2                        0x2
#define SPD_DDR3_DIE_COUNT_4                        0x3
#define SPD_DDR3_DIE_COUNT_8                        0x4

#define SPD_DDR3_SIGNAL_LOAD___M                    0x00000003
#define SPD_DDR3_SIGNAL_LOAD___S                    0x0
#define SPD_DDR3_SIGNAL_LOAD_SINGLE                 0x2

#define SPD_DDR3_SDRAM_DEVICE_TYPE___M              0x00000001
#define SPD_DDR3_SDRAM_DEVICE_TYPE___S              0x7
#define SPD_DDR3_SDRAM_DEVICE_TYPE_MONO             0x1

#define SPD_DDR3_MODULE_VDD_1_35_V_OPERABLE___M     0x00000001
#define SPD_DDR3_MODULE_VDD_1_35_V_OPERABLE___S     0x1
#define SPD_DDR3_MODULE_VDD_1_35_V_OPERABLE         0x1

#define SPD_DDR3_MODULE_VDD_1_35_V_OPERABLE___M     0x00000001
#define SPD_DDR3_MODULE_VDD_1_35_V_OPERABLE___S     0x1

#define SPD_DDR3_FTB_DIVIDEND___M                   0x0000000F
#define SPD_DDR3_FTB_DIVIDEND___S                   0x0
#define SPD_DDR3_FTB_DIVISOR___M                    0x0000000F
#define SPD_DDR3_FTB_DIVISOR___S                    0x4

#define SPD_DDR3_MTB_DIVIDEND___M                   0x000000FF
#define SPD_DDR3_MTB_DIVIDEND___S                   0x0
#define SPD_DDR3_MTB_DIVISOR___M                    0x000000FF
#define SPD_DDR3_MTB_DIVISOR___S                    0x0


#define SPD_DDR3_CAL_LAT_LSB___M                    0x000000FF
#define SPD_DDR3_CAL_LAT_LSB___S                    0x0
#define SPD_DDR3_CAL_LAT_MSB___M                    0x0000007F
#define SPD_DDR3_CAL_LAT_MSB___S                    0x0

#define SPD_DDR3_TXX_MTB___M                        0x000000FF
#define SPD_DDR3_TXX_MTB___S                        0x0
#define SPD_DDR3_TXX_FTB___M                        0x000000FF
#define SPD_DDR3_TXX_FTB___S                        0x0

#define SPD_DDR3_TRAS_MTB_MSN___M                   0x0000000F
#define SPD_DDR3_TRAS_MTB_MSN___S                   0x0

#define SPD_DDR3_TRC_MTB_MSN___M                    0x0000000F
#define SPD_DDR3_TRC_MTB_MSN___S                    0x4

#define SPD_DDR3_TRFC_MTB_MSB___M                   0x0000000F
#define SPD_DDR3_TRFC_MTB_MSB___S                   0x4


#define SPD_DDR3_TAAMAX                             0x14        // DDR3 tAAmax for all speeds in ns 20


#define SPD_DDR3_OUT_DRV_STRENGTH___M               0x00000003
#define SPD_DDR3_OUT_DRV_CK_Y13___S                 0x4
#define SPD_DDR3_OUT_DRV_CK_Y02___S                 0x6
#define SPD_DDR3_OUT_DRV_CTL_A___S                  0x0
#define SPD_DDR3_OUT_DRV_CTL_B___S                  0x2
#define SPD_DDR3_OUT_DRV_CA_A___S                   0x4
#define SPD_DDR3_OUT_DRV_CA_B___S                   0x6

#endif

