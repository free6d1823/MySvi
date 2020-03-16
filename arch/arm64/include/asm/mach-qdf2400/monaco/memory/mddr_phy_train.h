#ifndef _MODULE_MDDR_PHY_TRAIN_H_
#define _MODULE_MDDR_PHY_TRAIN_H_

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
* @file mddr_phy_train.h
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
#define PHY_RUN_FW              0x3 // bit 0 = 1D, bit 1 = 2D
#define TRAINING_1D_STEPS    0x3F9F // PHY training steps
#define TRAINING_2D_STEPS      0x61 // 2D training steps
#define DDRPHY_DEBUG_MSG       0xC8 // PHY debug verbosity - 0xFF=pass/fail, 0xC8=stage completion & assertion streaming msgs, 0x1=full
#define DDRPHY_DEBUG_2D_MSG    0xC8 // PHY debug verbosity for 2D - 0xFF=pass/fail, 0xC8=stage completion & assertion streaming msgs, 0x1=full

#define PHY_INPUT_VREF            0     // 0 use MR6, 1 use VrefDqR*Nib*
#define PHY_SKIPVREFUPD           1     // 1 skip writing VrefDq at end


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

unsigned mddr_phy_train(mddr_settings_t *mddr_settings_ptr, uint8_t chan);
unsigned mddr_phy_enhanced_training(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan);

/*****************************************************************************/
#endif

