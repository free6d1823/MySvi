#ifndef _MODULE_MDDR_PHY_LOADER_H_
#define _MODULE_MDDR_PHY_LOADER_H_

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
* @file mddr_phy_loader.h
*
* @par Description:
*
*    This header contains the driver internal prototypes, derived data types,
*    etc. to allow the cooperation of the MDDR sub-system modules / components.
*    This module is associated with loading the DDR PHY firmware into the
*    corresponding DMEM and IMEM registers.
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
#define DDRPHY_NUM_IMAGES    8      // Number of DDR PHY images for all the different configurations.


/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    This type defines the DDR PHY binary firmware type for each of the images.
*    Each firmware type has two associated images: IMEM and DMEM.
*    Based on the firmware type, the firmware id is ascertained.
*
******************************************************************************/
typedef enum
{
    DDRPHY_FWTYPE_ATE,
    DDRPHY_FWTYPE_1DTRAINING,
    DDRPHY_FWTYPE_2DTRAINING,
    DDRPHY_FWTYPE_DIAGS,
} phy_binary_fwtype_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the DDR PHY binary firmware id for each of the images.
*    Each firmware type has two associated images: IMEM and DMEM.
*
* @par Notes:
*    For each image, this enum type should have a IMEM followed by a DMEM.
*    The sequence here should exactly match with the sequence of the firmware
*     images loaded into IMC IMEM.
*
******************************************************************************/
typedef enum
{
    DDR4_RDIMM_TRAIN_IMEM,
    DDR4_RDIMM_TRAIN_DMEM,
    DDR4_LRDIMM_TRAIN_IMEM,
    DDR4_LRDIMM_TRAIN_DMEM,
    DDR4_PMU_TRAIN2D_IMEM,
    DDR4_PMU_TRAIN2D_DMEM,
    DDR4_DIAG_IMEM,
    DDR4_DIAG_DMEM,
} phy_binary_fwid_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the parameters associated with
*     each PHY binary firmware image. This header conveys the required info
*     to load the PHY binary into the specific register offsets.
*
* @par Members
*
*                                  <PRE>
*    bin_start_addr      The start address of the PHY firmware binary image
*    bin_size            The size of the PHY firmware binary image
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint64_t bin_start_addr;
    uint32_t bin_size;
} phy_binary_hdr_t;


/******************************************************************************
* Function Prototypes
******************************************************************************/
void mddr_phy_load_fwtype(uint8_t ddr_chan, phy_binary_fwtype_t fwtype);


#endif    //_MODULE_MDDR_PHY_LOADER_H_

