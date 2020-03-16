#ifndef _MODULE_MONACO_INIT_H_
#define _MODULE_MONACO_INIT_H_

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
* @file monaco_init.h
*
* @par Description:
*    This header contains the prototypes, derived data types, etc. to allow the
*    initialization of the Monaco Subsystem (Monaco ring, L3 cache and MDDR).
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <asm/mach/monaco/common/monaco_defs.h>
#include <asm/plat-centriq/ddr/mddr.h>
#include <asm/mach/monaco/cache/l3_init.h>
#include <asm/plat-centriq/ddr/mddr_power.h>
#include <asm/plat-centriq/monaco_su.h>

/******************************************************************************
* Defined Constants
******************************************************************************/


/*!****************************************************************************
*
* @par Description:
*    Version string for the Monaco Driver.
*
******************************************************************************/
#define MONACO_DRV_VER              "AW2.3_V1.1_2017_12_19"


/*!****************************************************************************
*
* @par Description:
*    Defined values for the SOC hardware version.
*
******************************************************************************/
#define  SOC_HW_MAJOR_VERSION_1        1
#define  SOC_HW_MAJOR_VERSION_2        2

#define  SOC_HW_MINOR_VERSION_0        0
#define  SOC_HW_MINOR_VERSION_1        1
#define  SOC_HW_MINOR_VERSION_2        2

#define  SOC_AUX_VERSION_0             0
#define  SOC_AUX_VERSION_1             1

/*!****************************************************************************
*
* @par Description:
*    Marker value used to indicate unused/populated HDDRSS instances for
*     channel assignments.
*
******************************************************************************/
#define MDDR_INVALID_INSTANCE       0xFF



/******************************************************************************
* Derived data types
******************************************************************************/


/*!****************************************************************************
*
* @par Description
*    Provides a common carrier for passing around the extracted partial
*    goods information.
*
* @par Members
*
*                                  <PRE>
*    hydra_cores        Hydra Partial Goods bits.
*    l3_interleaves     L3 Partial Goods bits.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    cpucore_t hydra_cores;      //!< Each bit represents a single Hydra core.
    l3intlv_t l3_interleaves;   //!< Each bit represents a single L3 cache interleave.
} partial_goods_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group all of the high-level
*    configuration controls available to adjust the Monaco driver
*    initialization.
*
* @par Members
*
*                                  <PRE>
*    soc_hw_version         SOC HW version.
*    goods                  Partial goods indications.
*    rs_settings            Ring Switch settings.
*    l3_settings            L3 cache settings.
*    mddr_settings          MDDR settings.
*    mode                   Execution target mode.
*    log_level              Verbosity.
*    spd_smbus_info         Map of SMBus IDs and addresses.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    soc_hw_version_t soc_hw_version;            //!< Indicates the SOC HW Version that has been detected.
    partial_goods_t goods;                      //!< Flags used to indicate which Hydra cores and L3 interleaves yielded.
    rs_settings_t rs_settings;                  //!< Indicates the configurable Ring settings to use.
    l3_settings_t l3_settings;                  //!< Indicates the configurable L3 settings to use.
    mddr_settings_t mddr_settings;              //!< Indicates the configurable DDR settings to use.
    target_mode_e mode;                         //!< Allows adaptation based on the type of execution target.
    importance_t log_level;                     //!< Indication of the level of reporting of initialization details.
    dimm_slot_smbus_info_t spd_smbus_info[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];   //!< Provides the map of platform defined SMBus addresses to the specific DIMMs based on chan and slot.
} monaco_init_t;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group the DDR instance assignments by
*     ring.
*
* @par Members
*
*                                  <PRE>
*    even_chan_insts        Even ring DDR channel instances.
*    odd_chan_insts         Odd ring DDR channel instances.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t even_chan_insts[DDR_MAX_NUM_CHANS/2];   //!< List of the HDDRSS instances for the populated DDR channels on the even ring by assigned ordering.
    uint8_t odd_chan_insts[DDR_MAX_NUM_CHANS/2];    //!< List of the HDDRSS instances for the populated DDR channels on the odd ring  by assigned ordering
} monaco_chan_assignments_t;



/******************************************************************************
* Global Variables
******************************************************************************/


/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/

unsigned monaco_init(monaco_init_t *init_parms_ptr);
unsigned int rs_init(monaco_init_t *init_parms_ptr);


/*****************************************************************************/
#endif


