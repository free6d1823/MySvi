#ifndef _MODULE_MONACO_DEFS_H_
#define _MODULE_MONACO_DEFS_H_

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
* @file monaco_defs.h
*
* @par Description:
*    This header provides a common set of Monaco specific definitions to be
*    used accross various Monaco related software components (also used to
*    create the linker file). It will be included as part of the definitions, etc.
*    made available to external software that needs to interact with the
*    Monaco related software components.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/
#include  <asm/mach/monaco/common/monaco_extra_defs.h>


/******************************************************************************
* Defined Constants
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    Maximum number of DDR frequencies that could be supported for runtime
*    selection on SOC. I.e. Dynamic frequency switch.
*
******************************************************************************/
#define DDR_MAX_FREQ_POOL_TARGET        1 // Two is the actual limit but for now only one is supported by the driver.


/*!****************************************************************************
*
* @par Description:
*    This constant provides the maximum number of DDR channels that can be
*    available in the DDR subsystem. Fewer channels may be available depending
*    on the actual DIMM population.
*
******************************************************************************/
#define DDR_MAX_NUM_CHANS               6


/*!****************************************************************************
*
* @par Description:
*    This constant provides the maximum number of DDR slots that can be
*    available in a single DDR channel in the DDR subsystem. Fewer slots may
*    be available depending on actual board configuration and available slots
*    may not be populated with DIMMs.
*
******************************************************************************/
#define DDR_MAX_NUM_SLOTS_PER_CHAN      2


/*!****************************************************************************
*
* @par Description:
*    This constant provides the number of byte lanes that are available
*    in a single DDR channel in the DDR subsystem. Generally 8 data bytes and
*    1 ECC byte.
*
******************************************************************************/
#define DDR_BYTE_LANES_PER_CHAN         9


/*!****************************************************************************
*
* @par Description:
*    This constant provides the maximum number of ranks that can be available
*    in a DDR slots in the DDR subsystem. Fewer ranks may be available depending
*    on actual board configuration and populated DIMMs.
*
******************************************************************************/
#define DDR_MAX_RANKS_PER_SLOT         4


/*!****************************************************************************
*
* @par Description:
*    This constant provides the maximum number of DRAMS that can be available
*    in a rank in the DDR subsystem. Fewer ranks may be available
*    depending on actual board configuration and populated DIMMs.
*
******************************************************************************/
#define DDR_MAX_DRAMS_PER_RANK         18


/*!****************************************************************************
*
* @par Description:
*    This constant provides the maximum number of ranks can be available in a
*    DDR channel that in the DDR subsystem. Fewer ranks may be available
*    depending on actual board configuration and populated DIMMs.
*
******************************************************************************/
#define DDR_MAX_RANKS_PER_CHAN         (DDR_MAX_NUM_SLOTS_PER_CHAN * DDR_MAX_RANKS_PER_SLOT)


/*!****************************************************************************
*
* @par Description:
*    This constant provides the maximum number of DIMMS that can be populated
*    in the DDR subsystem. The actual number of DIMMs can vary depending on the
*    actual number of slots present on the board and the number of DIMMs
*    populated in available slots.
*
* @par Notes:
*    The actual number of DIMMs will always be even since channels must be
*    populated in pairs and the populations must be symetric.
*
******************************************************************************/
#define DDR_MAX_NUM_DIMMS               (DDR_MAX_NUM_CHANS * DDR_MAX_NUM_SLOTS_PER_CHAN)


/*!****************************************************************************
*
* @par Description:
*    This constant provides the nominal number of CPU cores found in a CPU
*    Cluster. This represents the the maximum when cluster fully yields.
*    Fewer resources may be available as indicated by the partial goods
*    information.
*
******************************************************************************/
#define NUM_CORES_PER_CLUSTER           2


/*!****************************************************************************
*
* @par Description:
*    This constant provides the maximum number of CPU Clusters. This represents
*    the the maximum when all clusters yield at least one core. Fewer resources
*    may be available as indicated by the partial goods information.
*
******************************************************************************/
#define MAX_CLUSTERS                    24


/*!****************************************************************************
*
* @par Description:
*    This constant provides the nominal number of CPU cores found in a system.
*    Cluster. This represents the the maximum when all clusters fully yield.
*    Fewer resources may be available as indicated by the partial goods
*    information.
*
******************************************************************************/
#define MAX_CORES           (NUM_CORES_PER_CLUSTER * MAX_CLUSTERS)


/*!****************************************************************************
*
* @par Description:
*    This constant provides the nominal number of L3 caches found in a system.
*    Fewer resources may be available as indicated by the partial goods
*    information.
*
******************************************************************************/
#define MAX_L3_NODES                    12


/*!****************************************************************************
*
* @par Description:
*    This constant provides the nominal number of L3 interleaves found in
*    an L3 cache. This represents the the maximum when an L3 fully yields.
*    Fewer resources may be available as indicated by the partial goods
*    information.
*
******************************************************************************/
#define NUM_L3_INTERLEAVES_PER_NODE     2


/*!****************************************************************************
*
* @par Description:
*    This constant provides the maximum number of L3 interleaves found in
*    a system. This represents the the maximum when an L3 fully yields.
*    Fewer resources may be available as indicated by the partial goods
*    information.
*
******************************************************************************/
#define MAX_L3_INTERLEAVES              (MAX_L3_NODES * NUM_L3_INTERLEAVES_PER_NODE)


/*!****************************************************************************
*
* @par Description:
*    This constant provides the size of a single good L3 interleave found in
*    an L3 cache. This represents the the maximum when an interleave is not
*    used for ring trace storage. Ring trace can be configured to reserve
*    25% or 50% of the interleave reducing what is available for normal
*    cache operation.
*
******************************************************************************/
#define L3_INTERLEAVE_SIZE              0x00280000      // 2.5MB per interleave


/*!****************************************************************************
*
* @par Description:
*    This constant provides the nominal size of a complete L3 interleaves found
*    in an L3 cache. This represents the the maximum when an L3 fully yields
*    and is not used for ring trace. Ring trace can be configured to reserve
*    25% or 50% of the L3 reducing what is available for normal cache operation.
*    In addition, one or both interleaves may be unavailable as indicated by
*    the partial goods information.
*
******************************************************************************/
#define L3_SIZE              (NUM_L3_INTERLEAVES_PER_NODE * L3_INTERLEAVE_SIZE)


/*!****************************************************************************
*
* @par Description:
*    This constant provides the nominal number of CPU cores found in a system.
*    Cluster. This represents the the maximum when all clusters fully yield.
*    Fewer resources may be available as indicated by the partial goods
*    information.
*
******************************************************************************/
#define MAX_CPUS                MAX_CORES


/*!****************************************************************************
*
* @par Description:
*    This constant provides the total number of PBSUs within a system.
*
******************************************************************************/
#define MAX_PBSUS               5


/*!****************************************************************************
*
* @par Description:
*    This constant provides the Partial Goods default representing all CPUs are
*    good in all duplex clusters.
*
******************************************************************************/
#define HYDRA_MAP               (((1ULL) << MAX_CORES) - 1) // 0xFFFFFFFFFFFFull


/*!****************************************************************************
*
* @par Description:
*    Partial Goods Default: all L3 interleaves on all nodes are good.
*
******************************************************************************/
#define L3_MAP                  ((1 << MAX_L3_INTERLEAVES) - 1)  // 0x00FFFFFF


/*!****************************************************************************
*
* @par Description:
*    L1/L2 cache information
*
******************************************************************************/
#define L2_SIZE                 0x00080000        // 512KB
#define L1_SIZE                 0x00010000        // 64KB (data cache)
#define LINE_SIZE               128               // Cache line size in bytes


/*!****************************************************************************
*
* @par Description:
*    Base address of Ring Config Space
*
******************************************************************************/
#define RING_CONFIG_BASE        0x0FF80000000     // Monaco Config - QLL Base


/*!****************************************************************************
*
* @par Description:
*    Common defines for both the drivers and tests
*
******************************************************************************/
#define L3_0_QLL_OFFSET          0x00580000  // L3_0 offset from the ring
#define L3_0_QLL_BASE            (RING_CONFIG_BASE + L3_0_QLL_OFFSET)
#define L3_QLL_OFFSET_STRIDE     0x00100000  // Delta between 2 consecutive L3 offsets



// QLL: HML3 Region (CSR, CFG, PM, QoS) Offsets (on top of the Ring Config
//  Base, RING_CONFIG_BASE).
#define HML3_CSR_OFFSET          0x00000000
#define HML3_CFG_OFFSET          0x00010000  // CFG reg general offset
#define HML3_PM_OFFSET           0x00020000
#define HML3_QOS_OFFSET          0x00030000  // QOS reg general offset

// QoS Cache Capacity Monitoring (CCM) Read Control. Controls behaviour of QoS CCM funct.
#define HML3_CFG_QCCMCR_OFFSET       0x4050
// CFG Common: QoS Cache Capacity Enforcement Control
#define HML3_CFG_QCCECR_OFFSET       0x4060


#define HML3_QCCMCR_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_QCCMCR_OFFSET)
#define HML3_QCCECR_OFFSET       (HML3_CFG_OFFSET + HML3_CFG_QCCECR_OFFSET)

// L3 Performance Monitoring (QLL)
#define HML3_PM_QLL_EVCNTR0_OFFSET    0x8420  // Performance Monitor Event Counter 0
#define HML3_PM_QLL_EVCNTR1_OFFSET    0x8428  // Performance Monitor Event Counter 1
#define HML3_PM_QLL_EVCNTR2_OFFSET    0x8430  // Performance Monitor Event Counter 2
#define HML3_PM_QLL_EVCNTR3_OFFSET    0x8438  // Performance Monitor Event Counter 3
#define HML3_PM_QLL_EVCNTR4_OFFSET    0x8440  // Performance Monitor Event Counter 4
#define HML3_PM_QLL_EVCNTR5_OFFSET    0x8448  // Performance Monitor Event Counter 5
#define HML3_PM_QLL_EVCNTR6_OFFSET    0x8450  // Performance Monitor Event Counter 6
#define HML3_PM_QLL_EVCNTR7_OFFSET    0x8458  // Performance Monitor Event Counter 7

#define HML3_PM_EVCNTR0_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_EVCNTR0_OFFSET)
#define HML3_PM_EVCNTR1_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_EVCNTR1_OFFSET)
#define HML3_PM_EVCNTR2_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_EVCNTR2_OFFSET)
#define HML3_PM_EVCNTR3_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_EVCNTR3_OFFSET)
#define HML3_PM_EVCNTR4_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_EVCNTR4_OFFSET)
#define HML3_PM_EVCNTR5_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_EVCNTR5_OFFSET)
#define HML3_PM_EVCNTR6_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_EVCNTR6_OFFSET)
#define HML3_PM_EVCNTR7_OFFSET     (HML3_PM_OFFSET + HML3_PM_QLL_EVCNTR7_OFFSET)


// APB Space

// APB: L3 QDSS Region(CTIO, PMU, DBG) Offsets on top of (QDSS base + Ring base + MBSU 0ffsets above)
#define HML3_APB_CTIO_TOP_OFFSET      0x00050000
#define HML3_APB_PMU_TOP_OFFSET       0x00030000    // for both PMU_PERFMON and PMU_TPDMCS sub-regions below
#define HML3_APB_DBG_TOP_OFFSET       0x00020000

// APB: L3 QDSS Sub-region Offsets
#define HML3_APB_DBG_OFFSET           0xC000
#define HML3_APB_PMU_PERFMON_OFFSET   0xC000
#define HML3_APB_PMU_TPDMCS_OFFSET    0xCE00

// APB: L3_x Ring Switch (MBSUx) Offsets (on top of QDSS base and Ring Offset)
#define MBSU0_DBG_DBGCSR_OFFSET       0x00100000
#define MBSU1_DBG_DBGCSR_OFFSET       0x00180000
#define MBSU2_DBG_DBGCSR_OFFSET       0x00200000
#define MBSU3_DBG_DBGCSR_OFFSET       0x00280000
#define MBSU4_DBG_DBGCSR_OFFSET       0x00300000
#define MBSU5_DBG_DBGCSR_OFFSET       0x00380000
#define MBSU6_DBG_DBGCSR_OFFSET       0x00A80000
#define MBSU7_DBG_DBGCSR_OFFSET       0x00A00000
#define MBSU8_DBG_DBGCSR_OFFSET       0x00980000
#define MBSU9_DBG_DBGCSR_OFFSET       0x00900000
#define MBSU10_DBG_DBGCSR_OFFSET      0x00880000
#define MBSU11_DBG_DBGCSR_OFFSET      0x00800000

// APB: L3_x QDSS Base Addresses
#define L3_0_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU0_DBG_DBGCSR_OFFSET) //0xFF10000000+0x02000000+0x00100000=0xFF_1210_0000
#define L3_1_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU1_DBG_DBGCSR_OFFSET)
#define L3_2_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU2_DBG_DBGCSR_OFFSET)
#define L3_3_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU3_DBG_DBGCSR_OFFSET)
#define L3_4_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU4_DBG_DBGCSR_OFFSET)
#define L3_5_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU5_DBG_DBGCSR_OFFSET)
#define L3_6_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU6_DBG_DBGCSR_OFFSET)
#define L3_7_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU7_DBG_DBGCSR_OFFSET)
#define L3_8_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU8_DBG_DBGCSR_OFFSET)
#define L3_9_APB_BASE   (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU9_DBG_DBGCSR_OFFSET)
#define L3_10_APB_BASE  (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU10_DBG_DBGCSR_OFFSET)
#define L3_11_APB_BASE  (QDSS_APB_BASE + QDSS_RING_OFFSET + MBSU11_DBG_DBGCSR_OFFSET)

// L3 Performance Monitoring (APB)
#define HML3_PM_EVCNTR0_APB_OFFSET    0x220  // Performance Monitor Event Counter 0
#define HML3_PM_EVCNTR1_APB_OFFSET    0x228  // Performance Monitor Event Counter 1
#define HML3_PM_EVCNTR2_APB_OFFSET    0x230  // Performance Monitor Event Counter 2
#define HML3_PM_EVCNTR3_APB_OFFSET    0x238  // Performance Monitor Event Counter 3
#define HML3_PM_EVCNTR4_APB_OFFSET    0x240  // Performance Monitor Event Counter 4
#define HML3_PM_EVCNTR5_APB_OFFSET    0x248  // Performance Monitor Event Counter 5
#define HML3_PM_EVCNTR6_APB_OFFSET    0x250  // Performance Monitor Event Counter 6
#define HML3_PM_EVCNTR7_APB_OFFSET    0x258  // Performance Monitor Event Counter 7


#define HML3_PM_APB_EVCNTR0_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVCNTR0_APB_OFFSET)
#define HML3_PM_APB_EVCNTR1_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVCNTR1_APB_OFFSET)
#define HML3_PM_APB_EVCNTR2_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVCNTR2_APB_OFFSET)
#define HML3_PM_APB_EVCNTR3_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVCNTR3_APB_OFFSET)
#define HML3_PM_APB_EVCNTR4_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVCNTR4_APB_OFFSET)
#define HML3_PM_APB_EVCNTR5_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVCNTR5_APB_OFFSET)
#define HML3_PM_APB_EVCNTR6_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVCNTR6_APB_OFFSET)
#define HML3_PM_APB_EVCNTR7_OFFSET    (HML3_APB_PMU_TOP_OFFSET + HML3_APB_PMU_PERFMON_OFFSET + HML3_PM_EVCNTR7_APB_OFFSET)




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


/*****************************************************************************/
#endif  // _MODULE_MONACO_DEFS_H_

