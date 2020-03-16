#ifndef _MODULE_MONACO_EXTRA_DEFS_H_
#define _MODULE_MONACO_EXTRA_DEFS_H_

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
* @file monaco_extra_defs.h
*
* @par Description:
*    This header provides an extra set of Monaco specific definitions to be
*    used accross various Monaco C-based software components. It will be
*    included as part of the definitions, etc. made available to external
*    software that needs to interact with the Monaco related software
*    components.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/
#include <stdint.h>


/*!****************************************************************************
*
* @par Description
*    Provides a common structure for identifying the SOC hardware version.
*
* @par Members
*
*                                  <PRE>
*    major_version      Major Version of the SOC.
*    minor_version      Minor Version of the SOC.
*    aux_version        Auxiliry Version of the SOC.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    uint8_t major_version;      //!< Major Version of the SOC.
    uint8_t minor_version;      //!< Minor Version of the SOC.
    uint8_t aux_version;        //!< Auxiliry of the SOC.
} soc_hw_version_t;

/*!****************************************************************************
*
* @par Description
*    Mode of the target execution configuration. Allows runtime adaptation
*    based on the desired/actual target configuration.
*
* @par Members
*                                  <PRE>
*    SILICON     for a development platform target.
*    SIM         for a special simulated target.
*    SIM_RUMI42  for a simulated RUMI42 emulation target.
*    SIM_RUMI48  for a simulated RUMI48 emulation target.
*    RUMI42      for a RUMI42 emulation target.
*    RUMI48      for a RUMI48 emulation target.
*    CHIPSIM     for a CHIPSIM environment target.
*                                  </PRE>
******************************************************************************/
typedef enum
{
    SILICON,
    SIM,
    SIM_RUMI42,
    SIM_RUMI48,
    RUMI42,
    RUMI48,
    PALLADIUM,
    PALLADIUM48,
    CHIPSIM,
    PALLADIUM_Z1
} target_mode_e;


/*!****************************************************************************
*
* @par Description
*    Log level used to clasify severity/priority of log messages. Used to
*     limit which mesages are logged/displayed.
*
* @par Members
*                                  <PRE>
*    INFORMATIONAL  All priority of messages should be displayed.
*    LOW            Only low priority messages and above should be displayed.
*    MEDIUM         Only medium priority messages and above should be displayed.
*    HIGH           Only high priority messages and above should be displayed.
*    CRITICAL       Only critical messages should be displayed. Normal release mode.
*    NO_LOGS        No logging should occur even for critical items. Debug only.
*                                  </PRE>
******************************************************************************/
typedef enum _importance_t
{
    INFORMATIONAL = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    CRITICAL = 4,
    NO_LOGS = 5
} importance_t;


/*!****************************************************************************
*
* @par Description
*    Abstraction for the number of CPU cores and L3 interleaves
*
******************************************************************************/
typedef uint64_t  cpucore_t;
typedef uint32_t  l3intlv_t;


#endif // _MODULE_MONACO_EXTRA_DEFS_H_
