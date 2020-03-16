#ifndef _MODULE_L3_INIT_H_
#define _MODULE_L3_INIT_H_

/*!****************************************************************************
*
* @copyright Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
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
* @file l3_init.h
*
* @par Description:
*    This header contains the prototypes, derived data types, etc. to allow the
*   initialization of the Monaco L3 Caches.
*
******************************************************************************/


/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <asm/mach/monaco/common/monaco_extra_defs.h>


/******************************************************************************
* Defined Constants
******************************************************************************/


/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    L3 cache replacement policies. Indicates the policy used to select which
*     way that is selected to be replaced when a new allocation must be cached.
*
* @par Members
*                                  <PRE>
*    LRU:         Pseudo-LRU. Select as victim the cache ‘way’ that was
*                  accessed least recently from among the unlocked ways.
*    RANDOM:      Select as victim a randomly selected cache ‘way’ from among
*                  the unlocked ways.
*                                  </PRE>
*
******************************************************************************/
typedef enum
{
    LRU,
    RANDOM
} l3_replacement_policy_e;


/*!****************************************************************************
*
* @par Description
*    L3 cache trace allocation reserve. Indicates the portion of the selected
*     L3 interleaves that is reverved for ring trace purposes.
*
* @par Members
*                                  <PRE>
*    ALLOCATE_50_PERCENT:    50% of each targeted L3 interleave is reserved
*                            for tracing.
*    ALLOCATE_25_PERCENT:    25% of each targeted L3 interleave is reserved
*                            for tracing.
*    ALLOCATE_0_PERCENT:     0% of each targeted L3 interleave is reserved
*                            for tracing i.e. no tracing
*                                  </PRE>
*
******************************************************************************/
typedef enum
{
    ALLOCATE_50_PERCENT = 50,
    ALLOCATE_25_PERCENT = 25,
    ALLOCATE_0_PERCENT  =  0
} l3_trace_allocation_e;


/*!****************************************************************************
*
* @par Description
*    This type provides a container to group all for the ring trace
*    configuration controls available to adjust the L3 cache initialization.
*
* @par Members
*
*                                       <PRE>
*    trace_interleaves      L3 trace interleaves.
*    allocation             L3 trace allocation.
*                                       </PRE>
*
******************************************************************************/
typedef struct
{
    uint32_t trace_interleaves;         //!< Each bit represents a single L3 cache interleave to be partitioned for tracing. Zero mask indicates no tracing.
    l3_trace_allocation_e allocation;   //!< Indication of the portion of the target interleaves to use for tracing.
}l3_ring_trace_cfg_t;


/*!****************************************************************************
*
* @par Description
*    L3 cache FAIC machine functions available to be executed.
*
*
* @par Members
*                                  <PRE>
*    FAIC_PUSH            Write dirty data to memory, do not update tag
*    FAIC_ALLOCATE        Force line(s) into L3 if not already there
*    FAIC_CLEAN           Write dirty data to memory and mark line(s) clean
*    FAIC_FLUSH           Write dirty data to memory and mark line(s) invalid.
*    FAIC_INVALIDATE_L3   Mark lines invalid regardless of current state
*    FAIC_INVALIDATE_SFT  Invalidate the snoop filter tag arrays
*                                  </PRE>
*
******************************************************************************/
typedef enum
{
    FAIC_PUSH = 0x1,
    FAIC_ALLOCATE = 0x2,
    FAIC_CLEAN = 0x3,
    FAIC_FLUSH = 0x5,
    FAIC_INVALIDATE_L3 = 0x6,
    FAIC_INVALIDATE_SFT = 0x7
}
l3_faic_function_e;

/*!****************************************************************************
*
* @par Description
*    This type provides a container to group all for the high-level
*    configuration controls available to adjust the L3 cache initialization.
*    Include both the hardware dependent settings and the selectable /
*    configurable options.
*
* @par Members
*
*                                       <PRE>
*    snoop_fltr_en:                  Snoop filter enable.
*    affinity:                       L3 Affinity indicator.
*    auto_gate_clk_en:             Automatic clock gate enable. There is the erratum
*                                  HML3-S_0023 "FAIC Machine Access for Interleave1"
*                                  where writes to regs HML3_FAICCRA and HML3_FAICCRB
*                                  may be lost if the clock tree for Interleave1 had
*                                  been gated off. The workaround is to ensure that
*                                  Interleave1 clock tree is running at the time of
*                                  the FAIC machine access for Interleave1.
*    auto_gate_idle_clk_cyc_cnt:   Gate idle clock cycle count.
*    rplcmnt_policy:               Cache replacement policy.
*    trace_settings:               Settings used to configure the L3 for trace.
*    LL_query_en:                  LiveLock address and data queries enable. The LL
*                                  is turned on as a workaround for a VBU problem
*                                  depicted by CR QCTDD02725905.
*    LL_breaker_en:                LiveLock POS attempts to break a livelock.
*    addr_hash_en:                 L3 address hashing enabled.
*                                       </PRE>
*
******************************************************************************/
typedef struct
{
    bool snoop_fltr_en;                     //!< Flag used to indicate if the L3 snoop filter is to be enabled. Debug only control.
    bool affinity;                          //!< Flag used to indicate if the L3 affinity mode is to be enabled. Debug only control.
    bool auto_gate_clk_en;                  //!< Flag used to indicate if the L3 is allowed to automatically clock gate when idle.
    uint32_t auto_gate_idle_clk_cyc_cnt;    //!< Idle clock cycle count after which the L3 is allowed to automatically clock gate. Cycles are on L3’s main clock
    l3_replacement_policy_e rplcmnt_policy; //!< Indication of which cache replacement policy to use.
    l3_ring_trace_cfg_t trace_settings;     //!< Controls for configuring the L3 to support ring trace.
    bool LL_query_en;                       //!< Flag used to indicate if the L3 LiveLock data and address phase queries are turned on.
    bool LL_breaker_en;                     //!< Flag used to indicate if the L3 POS tries to break up a suspected livelock/starvation.
    bool addr_hash_en;                      //!< Flag used to indicate if the L3 address hashing is turned on.
    bool cache_cap_mon_en;                  //!< Flag used to indicate if the L3 cache capacity monitoring (CCM) hardware is enabled.
    bool fatcm;                             //!< Flag used to indicate if configurating L3 cache as FATCM.
    uint32_t size_in_mb;                    //!< The size of configurating L3 cache as FATCM. Now it can be 4MB, 8MB, 16MB or 32MB.
}l3_settings_t;


/******************************************************************************
* Global Variables
******************************************************************************/



/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/

void l3_init(target_mode_e mode, uint32_t l3_interleaves, l3_settings_t *settings_ptr);
void l3_invalidate_all(void);
uint32_t l3_get_num_even( void );
uint32_t l3_get_num_odd( void );
void l3_wd_reset_reinit(uint32_t l3_interleaves, l3_settings_t *settings_ptr);
void l3_clean(void);
void l3_flush(void);
bool l3_report_errors (void);
void l3_clear_errors(void);

/*****************************************************************************/
#endif


