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
* @file l3_init.c
*
* @par Description:
*   This module configures the Monaco L3 caches for access.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <target/l3.h>
#include <asm/mach/hal/HALvbuHWIO.h>
#include <asm/mach/hal/HALsysdbgHWIO.h>
#include <asm/hal/HALhwio.h>
#include "l3_defs.h"

#define __printf(pri, fmt, ...)

/******************************************************************************
* Defined Constants
******************************************************************************/

/******************************************************************************
* Derived data types
******************************************************************************/

/******************************************************************************
* Global Variables
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*     Flag used to control enable of the snoop filter functionality.
*
******************************************************************************/
bool snoop_fltr_en = true;

/*!****************************************************************************
*
* @par Description
*     Used to control the logical L3 instance selection: Affinity mode or
*      Spread Mode.
*
******************************************************************************/
bool affinity = false;

/*!****************************************************************************
*
* @par Description
*     Flag used to control enable of LiveLock Data and Address phase Queries.
*
******************************************************************************/
bool LL_query_en = true;

/*!****************************************************************************
*
* @par Description
*     Flag used to control enable of LiveLock Breaker to attempt to break out
*      a suspected livelock/starvation condition.
*
******************************************************************************/
bool LL_breaker_en = true;

/*!****************************************************************************
*
* @par Description
*     Flag used to control enable of the L3 Dynamic Clock Tree Gating.
*
******************************************************************************/
bool auto_gate_CLK_tree_en = false;

/*!****************************************************************************
*
* @par Description
*     Global used to control the number of cycles L3 is idle before interleave
*      clock is turned off.
*
******************************************************************************/
uint32_t clockoff_cyc_cnt = PSCRB_CLKOFF_CNT;

/*!****************************************************************************
*
* @par Description
*     Used to select the cache replacement policy i.e., the algorithm that
*      determines what cache block is to be replaced by another block that needs
*      to be brought in.
*
******************************************************************************/
l3_replacement_policy_e replacement_policy = LRU;

/*!****************************************************************************
*
* @par Description
*     Flag used to control enable of the address hashing.
*
******************************************************************************/
bool addr_hash_en = true;

/*!****************************************************************************
*
* @par Description
*     Flag used to control enable of the Cache Capacity Monitoring (CCM) hardware.
*
******************************************************************************/
bool cache_cap_mon_en = true;

/*!****************************************************************************
*
* @par Description
*     Contains the physical map of active L3 interleaves per node from the partial
*       goods.
*
******************************************************************************/
volatile l3intlv_t l3_yield = L3_MAP;

/*!****************************************************************************
*
* @par Description
*  At-Speed-Trace (AST): bit map selecting the interleaves to be partitioned and
*   how much (percentage) of these interleaves to be partitioned (0%, 25% or 50%).
*
******************************************************************************/
l3_ring_trace_cfg_t l3_ast_cfg = { 0x0, ALLOCATE_0_PERCENT };

/*!****************************************************************************
*
* @par Description
*     Init the struct holding the partial good values: first_even_inst_num,
*       first_odd_inst_num, num_even, num_odd
*
******************************************************************************/
l3_pg_t l3_pg_yields = { 0x0, 0x0, 0x0, 0x0 };

/*!****************************************************************************
*
* @par Description
*    The L3 functional version number: upper 16 bits of HML3_HW_VERSION specify
*      the major and the minor versions.
*
******************************************************************************/
uint32_t l3_hw_ver_maj_min = 0;

/*!****************************************************************************
*
* @par Description
*    The L3 FATCM start address
*
******************************************************************************/
uint64_t fatcm_start_addr;

/*!****************************************************************************
*
* @par Description
*    The L3 FATCM size(MB)
*
******************************************************************************/
uint64_t fatcm_size;


/******************************************************************************
* Macros
******************************************************************************/

/******************************************************************************
* Function Prototypes
******************************************************************************/
void instance_init( target_mode_e platform, uint32_t inst_num, uint64_t inst_qll_base );
void setup_POS( uint64_t inst_qll_base );
void setup_SFT_mode( uint64_t inst_qll_base );
void setup_SFT_pg( uint64_t inst_qll_base, uint32_t even_flag, uint32_t odd_flag );
uint32_t get_first_good_even( void );
uint32_t get_first_good_odd( void );
void perform_faic_function( l3_faic_function_e faic_function, uint64_t inst_qll_base, uint32_t even_flag, uint32_t odd_flag );
void wait_faic_idle( uint64_t inst_qll_base, uint32_t even_flag, uint32_t odd_flag );
void assign_BAR_DVM_POS_on_even( uint64_t inst_qll_base );
void assign_BAR_DVM_POS_on_odd( uint64_t inst_qll_base );
void assign_LL_QB_POS_on_even( uint64_t inst_qll_base );
void assign_LL_QB_POS_on_odd( uint64_t inst_qll_base );
void set_data_array_controls( uint64_t inst_base );
void set_misc_config_bits( uint64_t inst_qll_base );
void turn_lfsr_on( uint64_t inst_qll_base );
void instance_wd_reset_reinit( uint32_t inst_num, uint64_t inst_qll_base );
bool instance_report_errors( uint32_t inst_num, uint64_t inst_qll_base );
void clear_error_status( uint64_t inst_qll_base );
void setup_info_ints( uint64_t inst_qll_base );
void setup_fatal_ints( uint64_t inst_qll_base );
void disable_DCIALL( uint64_t inst_qll_base );
void override_alloc( uint64_t inst_base );
void setup_L3_CLK_tree_gating_counter( uint64_t inst_qll_base );
void enable_CLK_tree_gating( uint64_t inst_qll_base );
void lockdown_reg_groups_for_non_secure_access( uint64_t inst_qll_base );
void detect_livelock( target_mode_e platform, uint64_t inst_qll_base );
void enable_livelock_breaker( uint64_t inst_qll_base );
void get_AST_support(uint32_t inst_num, uint32_t *inst_ast_flag, uint32_t *even_ast_flag, uint32_t *odd_ast_flag);
void set_AST_partition( uint64_t inst_qll_base, uint32_t even_ast_flag, uint32_t odd_ast_flag );
void prepare_for_unexp_POS_req( uint64_t inst_qll_base );
//void mask_and_disable_ways( uint64_t inst_qll_base, uint32_t even_flag, uint32_t odd_flag );
uint32_t get_alloc_val_bar0( uint32_t inst_index, uint32_t num_interleaves );
uint32_t get_alloc_val_bar12( uint32_t inst_index, uint32_t num_interleaves );
void enable_lookups( uint64_t inst_qll_base, uint32_t even_flag, uint32_t odd_flag );
void enable_affinity_mode( uint64_t inst_qll_base );
void setup_qosid_ccm( uint64_t inst_qll_base );
void set_qosbeacon_dly( target_mode_e platform, uint64_t inst_qll_base );
void instance_invalidate_all( uint32_t inst_num, uint64_t inst_qll_base );
void faic_invalidate_all( uint64_t inst_qll_base, uint32_t even_flag, uint32_t odd_flag );
void instance_clean( uint32_t inst_num, uint64_t inst_qll_base );
void instance_flush( uint32_t inst_num, uint64_t inst_qll_base );
void instance_clear_errors( uint32_t inst_num, uint64_t inst_qll_base );
bool check_I1_CLK_tree_gating_en( uint64_t inst_qll_base );
void handle_I1_CLK_tree_gating( uint64_t inst_qll_base, bool enable_gating );
void get_inst_availability( uint32_t inst_num, uint32_t *node_flag, uint32_t *even_itlv_flag, uint32_t *odd_itlv_flag);
void write_reg( uint64_t inst_qll_base, uint64_t reg_offset, uint32_t write_val );
void read_modify_write_reg( uint64_t inst_qll_base, uint64_t reg_offset, uint32_t mask, uint32_t shift, uint32_t write_val );
uint32_t read_reg( uint64_t inst_qll_base, uint64_t reg_offset );
void VVDRV_hmss_tcm_setup_with_size(uint32_t l3_pg, uint64_t start_addr, uint32_t size_in_mb, unsigned char nsprot);
void VVDRV_hmss_tcm_setup(uint32_t l3_pg, uint32_t faiccra0_val, uint32_t faiccrb0_val, uint32_t faiccra1_val, uint32_t faiccrb1_val);
void VVDRV_hmss_l3_poll_dciall(uint32_t l3_pg);
int l3_fatcm_init(uint32_t l3_pg, uint64_t start_addr, uint64_t size_in_mb, uint8_t faiccrb_nsprot);
int l3_fatcm_test();

/******************************************************************************
* External Functions
******************************************************************************/
/*!****************************************************************************
*
* @par Description:
*    Prepare and start executing the L3 init sequence: translate the partial
*    goods bulk info into simpler/more meaningful yield values by Instances &
*    Interleaves to be used by each of the init steps(cmds) then execute these
*    commands
* @param
*    mode:               The execution platform/target (e.g., SILICON)
* @param
*    l3_pg:              Partial Goods yield for the L3 cache where the even
*                         bits denote the presence of L3 instances on the even
*                         interleave (I0) and the odd bits for the odd
*                         interleave, I1. Each L3 instance is represented via
*                         2 consecutive bits starting with bit 0, one for each
*                         interleave.
* @param
*    settings_ptr:       Pointer to a structure that contains all for the
*                        high-level config controls available to characterize
*                        the L3.
* @par Globals:
*    l3_yield:           Physical map of the active L3 interleave instances
*                         per node.
*    snoop_fltr_en:      Control enable the snoop filter (SFT) functionality.
*    affinity:           Control of the logical L3 instance selection.
*    LL_query_en:        Control enable of LiveLock Data and Address phase
*                         queries.
*    LL_breaker_en:      Control enable for LiveLock breaker.
*    auto_gate_CLK_tree_en:  Control enable of the L3 Dynamic Clock Tree Gating.
*    clockoff_cyc_cnt:   Number of cycles L3 is idle before interlv clk is
*                         turned off.
*    replacement_policy: Algorithm (LRU or RANDOM) that determines what cache
*                         block is to be replaced by another block that needs
*                         to be brought in.
*    addr_hash_en:       Control enable of the address hashing.
*    l3_pg_yields:       Partial good struct indicating the num of the node
*                         hosting the first good even interleave instance, same
*                         for the odd interleave, the number of the good even
*                         interleave instances and the number of the good odd
*                         interleave instances.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
********************************************************************************/
void l3_init( target_mode_e mode, uint32_t l3_pg, l3_settings_t *settings_ptr )
{
    uint32_t inst_ix;  // index through all L3 instances
    uint32_t l3_hw_ver;

    // Physical map of the active interleaves per each L3 instance.
    l3_yield = l3_pg;

    // SFT (snoop filter) on/off
    snoop_fltr_en = settings_ptr->snoop_fltr_en;
//    __printf(LOW, "\n<<<< L3 Caches - START Init >>>>\n");
    //__printf(MEDIUM, "\n<<<< L3 Caches - START Init >>>>\n");

    // LiveLock query on/off
    LL_query_en = settings_ptr->LL_query_en;

    // Logical L3 instance selection: Affinity mode vs Spread Mode.
    affinity = settings_ptr->affinity;
    // LiveLock breaker on/off
    LL_breaker_en = settings_ptr->LL_breaker_en;

    // CLK gating on/off
    auto_gate_CLK_tree_en = settings_ptr->auto_gate_clk_en;
    // Number of CBF cycles before turning interleave clock off if clk gating is on.
    clockoff_cyc_cnt = settings_ptr->auto_gate_idle_clk_cyc_cnt;

    // Replacement policy
    replacement_policy = settings_ptr->rplcmnt_policy;

    // Address hashing on/off
    addr_hash_en = settings_ptr->addr_hash_en;

    // Cache Capacity Monitoring (CCM) on/off.
    cache_cap_mon_en = settings_ptr->cache_cap_mon_en;

    __printf(LOW, "    Snoop filter is: %s \n", snoop_fltr_en ? "on" : "off" );

    __printf(LOW, "    LL query is: %s \n", LL_query_en ? "on" : "off" );
    __printf(LOW, "    LL breaker is: %s \n", LL_breaker_en ? "on" : "off" );

    __printf(LOW, "    Log L3 instance sel mode: %s \n", affinity ? "Affinity" : "Spread" );

    __printf(LOW, "    Addr Hashing is: %s \n", addr_hash_en ? "on" : "off" );

    __printf(LOW, "    Replacement Policy is: %s \n", replacement_policy ? "RANDOM" : "LRU" );

    __printf(LOW, "    Clk Tree Gating is: %s \n", auto_gate_CLK_tree_en ? "enabled" : "disabled" );
    if(auto_gate_CLK_tree_en)
    {
        __printf(LOW, "      L3 clock off counts (cycles): %d \n", clockoff_cyc_cnt );
    }

    __printf(LOW, "    Cache Capacity Monitoring (CCM) is: %s \n", cache_cap_mon_en ? "enabled" : "disabled" );

    // AST params reflecting what interleaves are to be partitioned and at what %
    l3_ast_cfg.trace_interleaves = settings_ptr->trace_settings.trace_interleaves;
    l3_ast_cfg.allocation = settings_ptr->trace_settings.allocation;

    // Get the number of even/odd interleaves online
    l3_pg_yields.num_even = l3_get_num_even();
    l3_pg_yields.num_odd = l3_get_num_odd();
//    __printf(LOW,"    Number of even interleave instances: %d \n", l3_pg_yields.num_even );
//    __printf(LOW,"    Number of odd interleave instances:  %d \n", l3_pg_yields.num_odd );


    // Get the number of the first instance with a "good" even/odd interleave
    l3_pg_yields.first_even_inst_num = get_first_good_even();
    l3_pg_yields.first_odd_inst_num = get_first_good_odd();

    __printf(LOW, "    POS on I0 is on instance number: %d \n",
                                                       l3_pg_yields.first_even_inst_num );
    __printf(LOW, "    POS on I1 is on instance number:  %d \n",
                                                       l3_pg_yields.first_odd_inst_num );

    // Initialize the L3 caches.
    for( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        // Get the L3 hardware version; this will allow us to switch amongst versions
        //  to support multiple server L3 releases
        if(( inst_ix==l3_pg_yields.first_even_inst_num ) || ( inst_ix==l3_pg_yields.first_odd_inst_num))
        {
            l3_hw_ver = read_reg( (L3_0_QLL_BASE + (0x100000 * inst_ix)), HML3_HW_VERSION_OFFSET );
            l3_hw_ver_maj_min = ( l3_hw_ver >> 16 ) & 0xFFFF;

            if(( l3_hw_ver_maj_min != 0x1001 ) && ( l3_hw_ver_maj_min != 0x1002 ))
            {
                __printf(HIGH, " ERROR: Wrong L3 Version read back from the HML3_HW_VERSION reg! \n");
                return;
            }
        }

        // Initialize each of the available L3 cache nodes.
        instance_init( mode, inst_ix, (L3_0_QLL_BASE + (0x100000 * inst_ix)));
    }

    //__printf(MEDIUM, "<<<< L3 Caches - DONE Init >>>>\n");

    if(settings_ptr->fatcm)
    {
        unsigned char nsprot=1;

        HWIO_IMC_MSA_CTRL_OUT(0x1);

        fatcm_start_addr = 0xFFF8000000LL;
        fatcm_size = settings_ptr->size_in_mb;

        l3_fatcm_init(l3_pg, fatcm_start_addr, settings_ptr->size_in_mb, nsprot);
    }

    // Setup auto clock gating if the CLK tree gating feature is enabled.
    if(auto_gate_CLK_tree_en)
    {
        for( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
        {
            uint64_t instance_base = L3_0_QLL_BASE + (0x100000 * inst_ix);

            if ( !((l3_yield >> (inst_ix << 1)) & 3) )
                    continue;

            // Setup L3 CLK tree gating counter to the desired timeout value.
            setup_L3_CLK_tree_gating_counter( instance_base );

            // Enable CLK tree gating to permit the L3 to gate its clock
            //  when idle.
            // Note the connection between the LL POS and the CLK gating (below).
            enable_CLK_tree_gating( instance_base );
        }
    }
    return;
}

/*!****************************************************************************
*
* @par Description:
*    Clear the error status and reporting bits on the available L3 caches.
* @param
*    None
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
******************************************************************************/
void l3_clear_errors(void)
{
    uint32_t inst_ix;

    // Invalidate the L3 and SFT tag arrays for all available L3s.
    for ( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        instance_clear_errors( inst_ix, (L3_0_QLL_BASE + (0x100000 * inst_ix)));
    }

    __printf(LOW, " << L3 Caches - Clear Errors: Done  >>\n");
}

/*!****************************************************************************
*
* @par Description:
*    Invalidate both the L3 tags and the SFT tags of the available L3 caches.
* @param
*    None
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
******************************************************************************/
void l3_invalidate_all(void)
{
    uint32_t inst_ix;

    // Invalidate the L3 and SFT tag arrays for all available L3s.
    for ( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        instance_invalidate_all( inst_ix, (L3_0_QLL_BASE + (0x100000 * inst_ix)));
    }

    __printf(LOW, " << L3 Caches - Invalidate All: Done  >>\n");
}

/*!****************************************************************************
*
* @par Description:
*    Clean the available L3 caches.
* @param
*    None
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
******************************************************************************/
void l3_clean( void )
{
    uint32_t inst_ix;

    // Clean all the available L3 caches.
    for ( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        instance_clean( inst_ix, (L3_0_QLL_BASE + (0x100000 * inst_ix)));
    }

    __printf(LOW, " << L3 Caches - Clean (via FAIC): Done  >>\n");
}

/*!****************************************************************************
*
* @par Description:
*    Flush (i.e., Clean and Invalidate) the available L3 caches.
* @param
*    None
* @par Globals:
*    qll_offsets:      L3 instance offsets in the QLL space.
*    max_l3_inst:      Max number of L3 nodes (aka L3 instances).
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
******************************************************************************/
void l3_flush( void )
{
    uint32_t inst_ix;

    // Flush (Clean & Invalidate) the L3 tag arrays for all available L3s
    for ( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        instance_flush( inst_ix, (L3_0_QLL_BASE + (0x100000 * inst_ix)));
    }

    __printf(LOW, " << L3 Caches - Flush (via FAIC): Done  >>\n");
}

/*!****************************************************************************
*
* @par Description:
*    Read the HML3_FIRA regs and if any of them has a non-zero value return
*    the reported error(s).
* @param
*    None
* @return
*    Reported error(s).
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
******************************************************************************/
bool l3_report_errors (void)
{
    uint32_t inst_ix;
    bool any_error = false;

    // Check all L3 nodes for errors
    for ( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        any_error |= instance_report_errors( inst_ix, (L3_0_QLL_BASE + (0x100000 * inst_ix)));
    }

    if( any_error )
    {
        any_error = true;
    }

    return any_error;
}

/*!****************************************************************************
*
* @par Description:
*    Sequence to reconfigure L3 after a watchdog timeout has occurred.
* @param
*    l3_pg (UNUSED_PARAM) :  Partial Goods yield for the L3 cache where the even
*                        bits denote the presence of L3 instances on the even
*                        interleave (I0) and the odd bits on the odd interleave, I1.
*                        Each L3 instance is represented via 2 consecutive bits
*                        starting with bit 0, one for each interleave.
*                                  @param
*    settings_ptr:      Pointer to a structure that contains all for the
*                        high-level configuration controls available to characterize
*                        the L3.
* @par Globals:
*    l3_ast_cfg.*:      At-Speed-Trace (AST) params indicating the interleaves
*                        to be partitioned(trace_interleaves) and at what
*                        percentage (allocation).
* @return
*    Nothing.
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
******************************************************************************/
void l3_wd_reset_reinit
(
    UNUSED_PARAM volatile uint32_t l3_pg,
    l3_settings_t *settings_ptr
)
{
    uint32_t inst_ix;  // go through all L3 instances

    // AST params reflecting what interleaves are to be partitioned and at what %
    l3_ast_cfg.trace_interleaves = settings_ptr->trace_settings.trace_interleaves;
    l3_ast_cfg.allocation = settings_ptr->trace_settings.allocation;

    __printf(LOW, "<< L3 Caches - Start WD Reset Re-init >>\n");

    // Reinitialize the L3 caches after the Watchdog reset
    for ( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        instance_wd_reset_reinit( inst_ix, (L3_0_QLL_BASE + (0x100000 * inst_ix)));
    }

    __printf(LOW, " << L3 Caches - Done WD Reset Re-init >>\n");
}

/*!****************************************************************************
*
* @par Description:
*    Determine the number of live instances on the even interleave (I0).
* @param
*    None
* @par Globals:
*    l3_yield:         Physical map of active L3 interleave instances per node.
* @return
*    The number of L3 instances online on the even interleave (I0).
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
******************************************************************************/
uint32_t l3_get_num_even( void )
{

    uint32_t inst_ix;  // Physical instance index
    uint32_t num_even = 0;

    for( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        if ((( l3_yield >> ( inst_ix * 2 )) & 0x1 ) != 0x0 )
        {
            num_even++;
        }
    }

    return num_even;
}

/*!****************************************************************************
*
* @par Description:
*    Determine the number of live instances on the odd interleave (I1).
* @param
*    None
* @par Globals:
*    l3_yield:    Physical map of active L3 interleave instances per node.
* @return
*    The number of L3 instances online on the odd interleave (I1).
* @author
*    cbucsan
* @par Notes:
*    This is an API function.
*
******************************************************************************/
uint32_t l3_get_num_odd( void )
{
    uint32_t inst_ix;  // Physical instance index
    uint32_t num_odd = 0;

    for( inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++ )
    {
        if ((( l3_yield >> ( inst_ix * 2 )) & 0x2 ) != 0x0 )
        {
            num_odd++;
        }

    }

    return num_odd;
}

/******************************************************************************
* Local Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    Walk through all the L3 nodes and initialize each of the available L3 nodes.
*    An available L3 node (aka instance) may have either one or both interleaves
*    online.
* @param
*    mode:               The execution platform/target (e.g., SILICON)
* @param
*    inst_num:        Number from 0 to the max number of L3 instances.
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                      i.e., including the Monaco ring switch address.
* @par Globals:
*    snoop_fltr_en:   Control enable the snoop filter (SFT) functionality.
*    LL_query_en:     Control enable of LiveLock Data and Address phase Queries.
* @return
*    Nothing
* @author
*    cbucsan
*
******************************************************************************/
void instance_init( target_mode_e mode, uint32_t inst_num, uint64_t inst_base )
{
    uint32_t inst_flag;  // whether this instance is available
    uint32_t even_flag;  // whether this even interleave is available
    uint32_t odd_flag;   // whether this odd interleave is available
    uint32_t inst_ast_flag;  // whether this instance is available for AST
    uint32_t even_ast_flag;  // whether this even interleave is to be partitioned for AST
    uint32_t odd_ast_flag;   // whether this odd interleave is to be partitioned for AST

    // Determine from the partial goods whether this L3 node's interleaves
    // are available; if either interleave instance is online then the L3 node
    // is considered to be available.
    get_inst_availability(inst_num, &inst_flag, &even_flag, &odd_flag);

    // Determine the AST support.
    get_AST_support(inst_num, &inst_ast_flag, &even_ast_flag, &odd_ast_flag);

    if( inst_flag )
    {
        __printf(LOW,  "L3_%d \n", inst_num );
    }

    // Start initializing the available L3s.
    if( inst_flag !=0x0 )
    {
        // Config POS parameters for this available instance.
        setup_POS( inst_base );

        // Setup Snoop Filter (SFT) to be either disabled or enabled for
        //  "fine-grained" mode.
        setup_SFT_mode( inst_base );
        // If SFT is enabled: configure the SFT "partial goods" control interleave
        //  registers and TCM Alloc Address regs (even if we don't setup TCM).
        if( snoop_fltr_en )
        {

            __printf(LOW, "  L3 physical instance: %d\n", inst_num);

            setup_SFT_pg( inst_base, even_flag, odd_flag);
        }

        // Invalidate the L3 tag arrays and snoop filter tag arrays in all the good L3s
        // There are 2 options to accomplish this:
        // 1. Use DCIALL (implementation defined) to all instances and interleaves.
        //   This is not a valid option when initializing from IMC (our case), i.e.
        //   not from our cpus.
        // 2. Use the FAIC (Flush-Allocation-Invalidation Control) function and execute
        //   both the Invalidate L3 tag arrays and Invalidate SFT tag arrays commands;
        //   ensure the FAIC machine is idle between the 2 steps. To initiate these
        //   ops use the interleave regs HML3_FAICCRB0 and HML3_FAICCRB1.
        // We will pursue option 2:
        faic_invalidate_all( inst_base, even_flag, odd_flag );

        // Configure the Barrier/DVM/LiveLock/QoS Beacon Point(s) of Serialization (POS) L3.
        // Each POS is designated per interleave and so the POS may be either the same L3
        //   instance for both interleaves or a different L3 instance on each interleave.
        // Note that during the system init the Monaco config script
        //   has already decided that the first good L3 instance from each interleave
        //   was the POS for both BAR and DVM. It's up to this script though to decide
        //   upon the LiveLock(LL) and QoS POS: we will designate the same
        //   L3(s) to be the LL/QoS POS besides being the BAR/DVM POS.
        // Note that assigning the LiveLock POS does not turn the LiveLock Detection
        //   and Correction on, these are independent steps.
        // Note that only the DVM-related barriers are broadcast to POS. Given
        //   that these barriers, the DVM ops and the LL/QoS ops are infrequent
        //   choosing the first available L3 to cover for all POS types is acceptable
        //   from a performance standpoint.
        //
        // Start by writing HML3_POSCRC to 0x0 for all available L3 instances to ensure
        //   that errors get generated if a non-POS L3 receives a POS-specific request.
        prepare_for_unexp_POS_req(inst_base);

        // Assign the BAR/DVM POS on the first even/odd instances.
        if( l3_pg_yields.first_even_inst_num == inst_num )
        {
            assign_BAR_DVM_POS_on_even( inst_base );
        }

        if( l3_pg_yields.first_odd_inst_num == inst_num )
        {
            assign_BAR_DVM_POS_on_odd( inst_base );
        }

        // Preparations prior to assigning the LL/QB POS.
        // Configure the QoS Beacon periods.
        if(( l3_pg_yields.first_even_inst_num == inst_num ) || ( l3_pg_yields.first_odd_inst_num == inst_num ))
        {
            set_qosbeacon_dly( mode, inst_base );
        }
        // Setup LiveLock (LL) Detection and Correction (LL backoff).
        // If the LiveLock queries (data and address phases) are to be turned on then
        //   set the LL query frequencies and enable the LL queries.
        if( LL_query_en )
        {
            if(( l3_pg_yields.first_even_inst_num == inst_num ) || ( l3_pg_yields.first_odd_inst_num == inst_num ))
            {
                detect_livelock( mode, inst_base );

                if( LL_breaker_en )
                {
                    enable_livelock_breaker( inst_base );
                }
            }
        }

        // Assign the LL/QB POS on the first even/odd instances.
        if( l3_pg_yields.first_even_inst_num == inst_num )
        {
            assign_LL_QB_POS_on_even( inst_base );
        }

        if( l3_pg_yields.first_odd_inst_num == inst_num )
        {
            assign_LL_QB_POS_on_odd( inst_base );
        }


        // Enable the QoSID-based Cache Capacity Monitoring (CCM-C).
        setup_qosid_ccm( inst_base );

        // Set data array controls.
        set_data_array_controls( inst_base );

        // Set miscellaneous configuration bits in HML3_HCRA and HML3_CRA.
        set_misc_config_bits( inst_base );
        // Ensure that the LFSR(linear feedback shift reg) is on for the LL POS L3.
        if( LL_query_en )
        {
            if(( l3_pg_yields.first_even_inst_num == inst_num ) || ( l3_pg_yields.first_odd_inst_num == inst_num ))
            {
                turn_lfsr_on( inst_base );
            }

        }

        // Optional Bring-up step: Prevent usage of certain portions of the L3
        //   arrays (e.g. in case of yield issues). Normally the reset value is
        //   fine meaning that all the L3 arrays are functional.
        // Currently not needed, see HPG.
//        mask_and_disable_ways( inst_base, even_flag, odd_flag );

        // Restore normal operation (enable tag/SFT lookups) after FAIC invalidate.
        // Note that FAIC invalidate includes the waiting for the FAIC machine to
        //  become idle.
        enable_lookups( inst_base, even_flag, odd_flag );

        // Switch to Affinity Mode if needed. Note that this setting
        //  only works only in conjunction with the appropriate Monaco routing
        //  register programming.
        if ( affinity )
        {
            enable_affinity_mode( inst_base);
        }

        // Clear Error status and reporting bits.
        clear_error_status( inst_base);

        // Configure behavior upon non-fatal interrupts: decide which masked
        //   errors get reported as informational (non-fatal) interrupts.
        setup_info_ints( inst_base );

        // Configure behavior upon fatal interrupts: decide which masked errors
        //  cause fatal interrupts.
        setup_fatal_ints( inst_base );

        // Disable DCIALL for L3.
        disable_DCIALL( inst_base );

        // Override L3 Allocation Control if replacement policy needs to be
        //  changed from pseudo-LRU.
        override_alloc( inst_base );

        // Setup AST given the AST map is non-zero
        if( inst_ast_flag !=0x0 )  // one/both interleaves on this node to be partitioned for AST
        {
            __printf(LOW,  "  AST: L3_%d: ", inst_num);

            set_AST_partition( inst_base, even_ast_flag, odd_ast_flag );
        }

        // Lock down the L3 register groups that non-secure code does not truly
        //   need access to. Not implemented at this time; relying on reset value
//        lockdown_reg_groups_for_non_secure_access( inst_base );
    } // available L3s
} // end init by instance

/*!****************************************************************************
*
* @par Description:
*    Determine the number of the first live instance on the even interleave (I0).
* @param
*    None
* @par Globals:
*    l3_yield:    Physical map of the active L3 interleave instances per node.
* @return
*    The number of the first L3 instance online on the even interleave (I0).
* @author
*    cbucsan
*
******************************************************************************/
uint32_t get_first_good_even( void )
{
    uint32_t inst_ix = 0;
    uint32_t first_inst_num = MAX_L3_NODES + 1;  // init to incorrect val

    // Look for the first instance with a good EVEN interleave. Stop if the max
    //   number of L3s is reached
    while(( first_inst_num > MAX_L3_NODES ) && (inst_ix < MAX_L3_NODES))
    {
        if ((( l3_yield >> (inst_ix * 2)) & 0x1 ) != 0 )
        {
            first_inst_num = inst_ix;
        }
        else
        {
            inst_ix++;
        }
    }
    return first_inst_num;
}

/*!****************************************************************************
*
* @par Description:
*    Determine the number of the first live instance on the odd interleave (I1).
* @param
*    None
* @par Globals:
*    l3_yield:     Physical map of the active L3 interleave instances per node.

* @return
*    The number of the first L3 instance online on the odd interleave (I1).
* @author
*    cbucsan
*
******************************************************************************/
uint32_t get_first_good_odd( void )
{
    uint32_t inst_ix = 0;
    uint32_t first_inst_num = MAX_L3_NODES + 1;  // init to incorrect val

    // Look for the first instance with a good ODD interleave. Stop if the max
    //   number of L3s is reached
    while(( first_inst_num > MAX_L3_NODES ) && (inst_ix < MAX_L3_NODES))
    {
        if ((( l3_yield >> ( inst_ix * 2 )) & 0x2 ) != 0 )
        {
            first_inst_num = inst_ix;
        }
        else
        {
            inst_ix++;
        }
    }

    return first_inst_num;
}

/*!****************************************************************************
*
* @par Description:
*    Configure POS (Point of Serialization) in this L3 instance. Each interleave
*     has its own POS; same L3 instance may be the POS for both interleaves.
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                      i.e., including the Monaco ring switch address.
* @par Globals:
*    snoop_fltr_en:    Control enable the snoop filter (SFT) functionality.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Register (common) to configure: HML3_POSCRA, L3 POS Control Reg A.
*
******************************************************************************/
void setup_POS( uint64_t inst_base )
{
    // Write value to setup POS per HPG doc.

    __printf(LOW,  " Setup POS: \n" );
    __printf(LOW,  "  Write HML3_POSCRA ");

    if(snoop_fltr_en)
    {
        write_reg( inst_base, HML3_POSCRA_OFFSET, POSCRA_ENABLE_SFT_VAL );
    }
    else
    {
        write_reg( inst_base, HML3_POSCRA_OFFSET, POSCRA_DISABLE_SFT_VAL );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Control the snoop filter (SFT) logic for this L3 instance.
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                      i.e., including the Monaco ring switch address.
* @par Globals:
*    snoop_fltr_en:    Control enable the snoop filter (SFT) functionality.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Register (common) to configure: HML3_SFTCR, W/R - L3 Snoop Filter Control Reg.
*
******************************************************************************/
void setup_SFT_mode( uint64_t inst_base )
{
    __printf(LOW,  " Setup SFT Mode: \n" );
    __printf(LOW,  "  Write HML3_SFTCR ");

    if(snoop_fltr_en)
    {
        // Enable the Snoop Filter
        write_reg( inst_base, HML3_SFTCR_OFFSET, SFTCR_ENABLE_SFT_VAL );
    }
    else
    {
        // Disable the Snoop Filter
        write_reg( inst_base, HML3_SFTCR_OFFSET, SFTCR_DISABLE_SFT_VAL);
    }
}

/*!****************************************************************************
*
* @par Description:
*    Control the configuration of the snoop filter (SFT) based on the spare
*    capacity of the SFT arrays for partial good scenarios.
* @param
*    inst_base:      The absolute address of the L3 instance in the QLL space
*                     i.e., including the Monaco ring switch address.
* @param
*    even_flag:      If not 0 the even instance is present in this node.
* @param
*    odd_flag:       If not 0 the odd instance is present in this node.
* @par Globals:
*    l3_pg_yields.*: Holds certain partial good values of interest:
*                     first_even_inst_num,first_odd_inst_num, num_even, num_odd.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Registers (interleave) to configure: HML3_SFTPGC0/1, L3 Snoop Filter
*     Partial Good Control Regs for I0/I1 for each present logical instance.
*     The value of HML3_SFTPGC0/1.SFT_PG_MODE field is identical for all of the
*     L3 instances that are online.
*     HML3_TCMAACA0/1 and HML3_TCMAACB0/1, TCM Allocation Address Control regs:
*     these regs are to be set to ensure correct snoop pre-filter functionality
*     even if TCM is not used.
*    This step is to be done before invalidating the tags in the next step.
*
******************************************************************************/
void setup_SFT_pg( uint64_t inst_base, uint32_t even_flag, uint32_t odd_flag)
{
    // Intermediate val of HML3_SFTPGCi for the SFT PG mode and enable fields
    uint32_t sftpgc_inter_val;
    // Value to be written to the HML3_SFTPGCi regs
    uint32_t sftpgc_val;
    // Fewest instances on either interleave is needed to build the sftpg_val
    uint32_t min_num_inst;
    static uint32_t even_ix;  // indexes the available logical even instances
    static uint32_t odd_ix;   // indexes the available logical odd instances

    // Value to be written to the HML3_TCMAACAi/Bi regs
    uint32_t tcmaac_val;

    // Get the number of L3s from the interleave with the least L3s.
    if (l3_pg_yields.num_even < l3_pg_yields.num_odd)
    {
        min_num_inst = l3_pg_yields.num_even;
    }
    else
    {
        min_num_inst = l3_pg_yields.num_odd;
    }

    // Build the value to be written to the SFTPGCn reg.
    // Firstly - the SFT Partial Good Mode (SFT_PG_MODE) and the SFT address space
    //   control (SFT_PG_EN). These fields must be set the same across interleaves
    //   and must reflect the interleave with the fewest L3s.
    if (min_num_inst > 3)
    {
        sftpgc_inter_val = 0x1;
    }
    else if ( min_num_inst > 1 )
    {
        sftpgc_inter_val = 0x3;
    }
    else
    {
        sftpgc_inter_val = 0x5;
    }

    __printf(LOW,  " Setup SFT PG: \n" );

    // Secondly - include the BAR_PA10_8 field to the val to write to the SFTPGCi
    //   regs and write to the HML3_TCMAACAi/Bi regs.
    // For the even interleave, if available.
    if(( even_flag != 0 ) && ( even_ix < l3_pg_yields.num_even ))
    {
        // Write the HML3_SFTPGC0 reg.
        sftpgc_val = ( even_ix << 8 ) | sftpgc_inter_val;

//        __printf(LOW,  "  Even logical instance %d SFTPGC0 ", even_ix );

        write_reg( inst_base, HML3_SFTPGC0_OFFSET, sftpgc_val );

        // Write the HML3_TCMAACA0/B0 regs i.e.,
        //  L3BAR0_PRIM/L3BAR0_PRIM_MASK,
        //  L3BAR1_EN/L3BAR1_PRIM/L3BAR1_SEC/L3BAR1_SEC_MASK and
        //  L3BAR2_EN/L3BAR2_PRIM/L3BAR2_SEC/L3BAR2_SEC_MASK fields based on the
        //  partial goods.

        // Determine the value to be written to the I0's HML3_TCMAACA0.
        tcmaac_val = get_alloc_val_bar0( even_ix, l3_pg_yields.num_even );
        // Write this value to HML3_TCMAACA0.

        __printf(LOW,  "  Write HML3_TCMAACA0 ");

        write_reg( inst_base, HML3_TCMAACA0_OFFSET, tcmaac_val );

        // Determine the value to be written to HML3_TCMAACB0.
        tcmaac_val = get_alloc_val_bar12( even_ix, l3_pg_yields.num_even );
        // Write this value to HML3_TCMAACB0.

        __printf(LOW,  "  Write HML3_TCMAACB0 ");

        write_reg( inst_base, HML3_TCMAACB0_OFFSET, tcmaac_val);

        even_ix++;   // prepare for the next iteration i.e. next good even interlv, if any
    }

    // And for the odd interleave, if available.
    if(( odd_flag != 0 ) && ( odd_ix < l3_pg_yields.num_odd ))
    {
        sftpgc_val = (odd_ix << 8) | sftpgc_inter_val;

//        __printf(LOW,  "  Odd logical instance %d SFTPGC1", odd_ix );

        write_reg( inst_base, HML3_SFTPGC1_OFFSET, sftpgc_val);

        // Write the HML3_TCMAACA1/B1 odd interleave regs i.e.,
        //  L3BAR0_PRIM/L3BAR0_PRIM_MASK,
        //  L3BAR1_EN/L3BAR1_PRIM/L3BAR1_SEC/L3BAR1_SEC_MASK and
        //  L3BAR2_EN/L3BAR2_PRIM/L3BAR2_SEC/L3BAR2_SEC_MASK fields based on the
        //  partial goods.

        // Determine the value to be written to HML3_TCMAACA1.
        tcmaac_val = get_alloc_val_bar0( odd_ix, l3_pg_yields.num_odd );
        // Write this value to HML3_TCMAACA1.

        __printf(LOW,  "  Write HML3_TCMAACA1 ");

        write_reg( inst_base, HML3_TCMAACA1_OFFSET, tcmaac_val );

        // Determine the value to be written to HML3_TCMAACB1.
        tcmaac_val = get_alloc_val_bar12( odd_ix, l3_pg_yields.num_odd );
        // Write this value to HML3_TCMAACB1.

        __printf(LOW,  "  Write HML3_TCMAACB1 ");

        write_reg( inst_base, HML3_TCMAACB1_OFFSET, tcmaac_val);

        odd_ix++;   // prepare for the next iteration i.e. next good odd interlv, if any
    }
}

/*!****************************************************************************
*
* @par Description:
*    Invalidate both the L3 and SFT tag arrays of this L3 instance.
* @param
*    inst_base:      The absolute address of the L3 instance in the QLL space
*                     i.e., including the Monaco ring switch address.
* @param
*    even_flag:      If not 0 the even instance is present in this node.
* @param
*    odd_flag:       If not 0 the odd instance is present in this node.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    The invalidation is achieved by means of the L3 FAIC (Flush-Allocate-
*    Invalidate-Clean) machine INVALIDATE function.
*
******************************************************************************/
void faic_invalidate_all
(
    uint64_t inst_base,
    uint32_t even_flag,
    uint32_t odd_flag
)
{
    // Invalidate the L3 tag arrays
    __printf(LOW,  " Perform FAIC Function: INVALIDATE_L3 \n" );

    perform_faic_function( FAIC_INVALIDATE_L3, inst_base, even_flag, odd_flag );

    // Invalidate the SFT tags
    __printf(LOW,  " Perform FAIC Function: INVALIDATE_SFT \n" );

    // Invalidate the SFT tag arrays
    perform_faic_function( FAIC_INVALIDATE_SFT, inst_base, even_flag, odd_flag );
}

/*!****************************************************************************
*
* @par Description:
*    Perform the selected FAIC function (e.g. clean, invalidate, flush etc.).
* @param
*    faic_function:    One of the FAIC machine functions.
* @param
*    inst_base:        The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @param
*    even_flag:        If not 0 the even instance is present in this node.
* @param
*    odd_flag:         If not 0 the odd instance is present in this node.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (interleave) to configure: HML3_FAICCRB0/1, L3 FAIC Control reg B,
*    for interleaves 0 and 1.
*    Apply the FAIC workaround, HML3_S erratum 0023, if Interleave 1 is present
*    and the clock tree gating is enabled on this interleave.
*
******************************************************************************/
void perform_faic_function
(
    l3_faic_function_e faic_function,
    uint64_t inst_base,
    uint32_t even_flag,
    uint32_t odd_flag
)
{
    uint32_t faic_function_mask = FAICCRBn_FAIC_FUNCTION__M;
    uint32_t faic_function_shift = FAICCRBn_FAIC_FUNCTION__S;
    // Check if workaround for the erratum item on FAIC writes with
    //  I1 CLK gating enabled is needed.
    bool is_faic_workaround_needed = false;

    // Check if this even interleave, I0, is enabled.
    if( even_flag != 0 )
    {
        // Perform the FAIC function on I0; this is a read-modify-write to
        //  the HML3_FAICCRB0 reg.
        __printf(LOW,  "  RMW HML3_FAICCRB0 ");

        read_modify_write_reg( inst_base, HML3_FAICCRB0_OFFSET,
                               faic_function_mask, faic_function_shift,
                               (uint32_t)faic_function );

        // Wait for the FAIC machine to become idle on I0 to ensure FAIC function
        //  is done.
        wait_faic_idle( inst_base, even_flag, 0 );
    }

    // Check if this odd interleave, I1, is enabled.
    if( odd_flag != 0 )
    {
        // The workaround is necessary if the CLK tree gating is enabled on I1.
        if( check_I1_CLK_tree_gating_en( inst_base ))
        {
            // Turn on the workaround needed flag
            is_faic_workaround_needed = true;
            // START Workaround by disabling the CLK gating on Interleave 1.
            handle_I1_CLK_tree_gating( inst_base, false );
        }

        // Perform the FAIC function on I1; this is a read-modify-write to
        //  the HML3_FAICCRB1 reg.
        __printf(LOW,  "  RMW HML3_FAICCRB1 ");

        read_modify_write_reg( inst_base, HML3_FAICCRB1_OFFSET,
                               faic_function_mask, faic_function_shift,
                               (uint32_t)faic_function );

        // Wait for the FAIC machine to become idle on I1 to ensure FAIC function
        //  is done.
        wait_faic_idle( inst_base, 0, odd_flag );

        // If the I1 CLK tree gating was disabled as part of the workaround
        //  now that the write to the HML3_FAICCRB is complete re-enable the
        //  I1 CLK tree gating.
        if( is_faic_workaround_needed )  // I1 CLK tree gating was turned off
        {
            // END Workaround by restoring(re-enabling) the dynamic CLK tree
            //  gating for I1.
            handle_I1_CLK_tree_gating( inst_base, true );
        }
    }
}

/*!****************************************************************************
*
* @par Description:
*    Check whether Interleave 1's CLK tree gating is enabled.
* @param
*    inst_base:        The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    This is a helper function to implement workaround for HML3-S erratum,
*    "FAIC Machine Access for Interleave 1".
*    Register (common) to access:
*    HML3_PSCRA, L3 Power State Control reg A.
*
******************************************************************************/
bool check_I1_CLK_tree_gating_en( uint64_t inst_base )
{
    uint32_t read_val;
    bool is_gating_enabled = false;

    read_val = read32( inst_base + HML3_PSCRA_OFFSET );
    // If the CLK tree gating on Interleave 1 is enabled set the flag.
    if((( read_val & PSCRA_EL3DCCLKG1__M ) >> PSCRA_EL3DCCLKG1__S ))
    {
        is_gating_enabled = true;
    }

    return is_gating_enabled;
}

/*!****************************************************************************
*
* @par Description:
*    Disable I1's CLK tree gating.
* @param
*    inst_base:     The absolute address of the L3 instance in the QLL space
*                    i.e., including the Monaco ring switch address.
* @param
*    enable_gating: If true, L3 Dynamic Clock Tree gating, I1, is enabled;
*                    if false, L3 Dynamic Clock Tree gating, I1, is disabled.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    This is a helper function to implement workaround for HML3-S erratum item,
*    "FAIC Machine Access for Interleave 1".
*    Register (common) to access:
*    HML3_PSCRA, L3 Power State Control reg A.
*
******************************************************************************/
void handle_I1_CLK_tree_gating( uint64_t inst_base, bool enable_gating )
{
    __printf(LOW, "  RMW HML3_PSCRA ");

    // Disable the CLK tree gating.
    read_modify_write_reg( inst_base, HML3_PSCRA_OFFSET,
                               PSCRA_EL3DCCLKG1__M, PSCRA_EL3DCCLKG1__S,
                               enable_gating );
}

/*!****************************************************************************
*
* @par Description:
*    Assign the Barrier(BAR)/Distributed Virtual Memory(DVM)
*    Point of Serialization (POS) L3 for the even interleave (I0).
* @param
*    inst_base:     The absolute address of the L3 instance in the QLL space
*                    i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Reg (common) to configure: HML3_POSCRC, R/W - L3 POS Control Reg C.
*
******************************************************************************/
void assign_BAR_DVM_POS_on_even( uint64_t inst_base )
{
    __printf(LOW, " Assign the BAR/DVM POS on I0: \n" );

    // Barrier POS: Set HML3_POSCRC.BAR_OP_IV0_EN to 1
    // DVM POS: Set HML3_POSCRC.TLBI_OP_IV0_EN to 1
    // i.e., write 0x3 to the composite field POSCRC_TLBI_BAR_IV0_EN
    // Read-modify-write the 2-bit field to configure the 2 POS's
    __printf(LOW, "  RMW HML3_POSCRC ");
    read_modify_write_reg( inst_base, HML3_POSCRC_OFFSET, POSCRC_TLBI_BAR_IV0_EN__M,
                          POSCRC_TLBI_BAR_IV0_EN__S, POSCRC_TLBI_BAR_IV0_EN );
}

/*!****************************************************************************
*
* @par Description:
*    Assign the Barrier(BAR)/Distributed Virtual Memory(DVM)
*    Point of Serialization (POS) L3 for the odd interleave (I1).
* @param
*    inst_base:     The absolute address of the L3 instance in the QLL space
*                    i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Reg (common) to configure: HML3_POSCRC, R/W - L3 POS Control Reg C.
*
******************************************************************************/
void assign_BAR_DVM_POS_on_odd( uint64_t inst_base )
{
    __printf(LOW,  " Assign the BAR/DVM POS on I1: \n" );

    // Barrier POS: Set HML3_POSCRC.BAR_OP_IV1_EN to 1
    // DVM POS: Set HML3_POSCRC.TLBI_OP_IV1_EN to 1
    // i.e., write 0x3 to the composite field POSCRC_TLBI_BAR_IV1_EN
    // Read-modify-write the 3-bit field to configure the 3 POS's
    __printf(LOW,  "  RMW HML3_POSCRC ");
    read_modify_write_reg( inst_base, HML3_POSCRC_OFFSET, POSCRC_TLBI_BAR_IV1_EN__M,
                          POSCRC_TLBI_BAR_IV1_EN__S, POSCRC_TLBI_BAR_IV1_EN );
}

/*!****************************************************************************
*
* @par Description:
*    Assign the LiveLock/QoS Beacon
*    Point of Serialization (POS) L3 for the even interleave (I0).
* @param
*    inst_base:     The absolute address of the L3 instance in the QLL space
*                    i.e., including the Monaco ring switch address.
* @par Globals:
*    LL_query_en: Control enable for LL address/data queries.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Reg (common) to configure: HML3_POSCRC, R/W - L3 POS Control Reg C.
*
******************************************************************************/
void assign_LL_QB_POS_on_even( uint64_t inst_base )
{
    if( LL_query_en )
    {

        __printf(LOW,  " Assign the LL/QoS POS on I0: \n" );
        // Read-modify-write the reg to configure the LL and QoS Beacon POS's.
        __printf(LOW,  "  RMW HML3_POSCRC ");
        read_modify_write_reg( inst_base, HML3_POSCRC_OFFSET, POSCRC_LLBC_QB_IV0_EN__M,
                          POSCRC_LLBC_QB_IV0_EN__S, POSCRC_LLBC_QB_IV0_EN );
    }
    else  // LL address/data queries are disabled
    {
        __printf(LOW,  " Assign the QoS POS on I0: \n" );
        // Read-modify-write the reg to configure the QoS Beacon POS's.
        __printf(LOW,  "  RMW HML3_POSCRC ");
        read_modify_write_reg( inst_base, HML3_POSCRC_OFFSET, POSCRC_QB_IV0_EN__M,
                          POSCRC_QB_IV0_EN__S, POSCRC_QB_IV0_EN );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Assign the LiveLock/QoS Beacon
*    Point of Serialization (POS) L3 for the odd interleave (I1).
* @param
*    inst_base:     The absolute address of the L3 instance in the QLL space
*                    i.e., including the Monaco ring switch address.
* @par Globals:
*    LL_query_en: Control enable for LL address/data queries.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Reg (common) to configure: HML3_POSCRC, R/W - L3 POS Control Reg C.
*
******************************************************************************/
void assign_LL_QB_POS_on_odd( uint64_t inst_base )
{
    if( LL_query_en )
    {
        __printf(LOW,  " Assign the LL/QoS POS on I1: \n" );
        // Read-modify-write the reg to configure the LL and QoS Beacon POS's.
        __printf(LOW,  "  RMW HML3_POSCRC ");
        read_modify_write_reg( inst_base, HML3_POSCRC_OFFSET, POSCRC_LLBC_QB_IV1_EN__M,
                          POSCRC_LLBC_QB_IV1_EN__S, POSCRC_LLBC_QB_IV1_EN );

    }
    else  // LL address/data queries are disabled
    {
        __printf(LOW,  " Assign the QoS POS on I1: \n" );
        // Read-modify-write the reg to configure the QoS Beacon POS's.
        __printf(LOW,  "  RMW HML3_POSCRC ");
        read_modify_write_reg( inst_base, HML3_POSCRC_OFFSET, POSCRC_QB_IV1_EN__M,
                          POSCRC_QB_IV1_EN__S, POSCRC_QB_IV1_EN );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Prepare the ground for raising an error when the wrong L3 receives a
*     BAR/DVM request.
* @param
*    inst_base:     The absolute address of the L3 instance in the QLL space
*                    i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Reg (common) to configure: HML3_POSCRC, R/W - L3 POS Control Reg C.
*    The reset value of the HML3_POSCRC register is 0x33 meaning that no
*    error is raised when the wrong L3 receives the BAR/DVM request; write 0x0
*    to HML3_POSCRC before any POS assignment to ensure the bit fields meant
*    to enable the BAR/TLBI ops are properly configured to generate the
*    UNEXP_REQ error in the HML3_FIRA reg.
*
******************************************************************************/
void prepare_for_unexp_POS_req( uint64_t inst_base )
{
    __printf(LOW, " Prepare for Unexpected POS Request: \n" );
    __printf(LOW, "  Write HML3_POSCRC ");

    write_reg( inst_base, HML3_POSCRC_OFFSET, 0x0);
}

/*!****************************************************************************
*
* @par Description:
*    Set data array controls.
* @param
*    inst_base:     The absolute address of the L3 instance in the QLL space
*                    i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Reg (common) to configure:
*    HML3_ARYCC, R/W - L3 Array Control, reg C.
*
******************************************************************************/
void set_data_array_controls( uint64_t inst_base )
{
    __printf(LOW, " Set Data Array Controls: \n" );
    __printf(LOW, "  Write HML3_ARYCC ");

    write_reg( inst_base, HML3_ARYCC_OFFSET, ARYCC_DARY_ACC_LAT );
}

/*!****************************************************************************
*
* @par Description:
*    Set miscellaneous configuration bits.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @par Globals:
*    addr_hash_en: Control enable for address hashing.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_HCRA, R/W - L3 Hidden Config reg A (includes hash control override),
*    HML3_CRA, R/W - L3 Config Control reg A.
*
******************************************************************************/
void set_misc_config_bits( uint64_t inst_base)
{
    // Write required value to HML3_HCRA.

    __printf(LOW, " Set Misc Config Bits: \n" );
    __printf(LOW, "  Write HML3_HCRA ");

    if( addr_hash_en )
    {
        write_reg( inst_base, HML3_HCRA_OFFSET, HCRA_HASH_ENABLED_VAL );
    }
    else
    {
        write_reg( inst_base, HML3_HCRA_OFFSET, HCRA_HASH_DISABLED_VAL );
    }

    // Write to HML3_CRA
    __printf(LOW, "  Write HML3_CRA ");
    write_reg( inst_base, HML3_CRA_OFFSET, CRA_VAL );
}

#if 0
/*!****************************************************************************
*
* @par Description:
*    Setup L3 way masking and way disabling if necessary.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @param
*    even_flag:    If not 0 the even instance is present in this node.
* @param
*    odd_flag:     If not 0 the odd instance is present in this node.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    This is a bring-up only (i.e., not production) step.
*    Regs (interleave) to configure: HML3_WMCR0/1, R/W, L3 Way Mask Control reg,
*     I0/I1 and HML3_WDCR0/1, R/W, l3 Way Disable Control reg, I0/I1.
*    If all arrays are good this step is not necessary as the value to
*     be written to HML3_WMCR0/1 and HML3_WDCR0/1 is 0x0 i.e., the reset value.
*
******************************************************************************/
void mask_and_disable_ways
(
    uint64_t inst_base,
    uint32_t even_flag,
    uint32_t odd_flag
)
{
//    __printf(LOW, " Mask and Disable Ways: \n" );

    // If the even interleave of this L3 instance is online write the registers
    if( even_flag != 0 )
    {
        // Write HML3_WMCR0, the L3 Way Mask Control reg

        __printf(LOW, "  Write HML3_WMCR0 ");

        write_reg( inst_base, HML3_WMCR0_OFFSET, 0x00000000 );

        // Write HML3_WDCR0, the L3 Way Disable Control reg

        __printf(LOW, "  Write HML3_WDCR0 ");

        write_reg( inst_base, HML3_WDCR0_OFFSET, 0x00000000 );
    }

    // Check if the odd interleave of this L3 instance is online.
    if( odd_flag != 0 )
    {
         // Write HML3_WMCR1, the L3 Way Mask Control reg
        __printf(LOW, "  Write HML3_WMCR1 ");

        write_reg( inst_base, HML3_WMCR1_OFFSET, 0x00000000 );

        // Write HML3_WDCR1, the L3 Way Disable Control reg
        __printf(LOW, "  Write HML3_WDCR1 ");

        write_reg( inst_base, HML3_WDCR1_OFFSET, 0x00000000 );
    }
}
#endif // this is not needed, see HPG

/*!****************************************************************************
*
* @par Description:
*    Enable the Affinity Mode to control the Logical L3 instance selection.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure: HML3_CRA, R/W, L3 Config Control reg. Bit 19
*     controls the Affinity Mode (0x1) vs. Spread Mode (0x0).
*
******************************************************************************/
void enable_affinity_mode( uint64_t inst_base )
{
    __printf(LOW, " Enable the Affinity Mode: \n" );
    __printf(LOW,  "  RMW HML3_CRA ");

    // Set bit 19, HML3_CRA.AMVSMC, to 1 to enable the Affinity mode to
    //  control the Logical L3 instance selection.
    read_modify_write_reg( inst_base, HML3_CRA_OFFSET,
                               CRA_AMVSMC__M, CRA_AMVSMC__S, 0x1 );
}

/*!****************************************************************************
*
* @par Description:
*    Enable/disable the QoSID-based Cache Capacity Monitoring
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure: HML3_QCCMCR, R/W, L3 QoS Cache Capacity
*     Monitoring Read Control Register.
*
******************************************************************************/
void setup_qosid_ccm( uint64_t inst_base )
{
    if(cache_cap_mon_en)   // Enable CCM
    {
        __printf(LOW, " Enable the QoSID-based CCM: \n" );
        // Ensure bit[1], CCMC_SS, CCM counter snapshot/copy initiate, is 0 (disable)
        //    and bit[0], DSBL_CCMC, disable CCM HW, is 0 to enable the CCM HW.
        __printf(LOW, "  Write HML3_QCCMCR ");
        write_reg( inst_base, HML3_QCCMCR_OFFSET, 0x00000000 );
    }
    else   // Disable CCM
    {
        __printf(LOW, " Disable the QoSID-based CCM: \n" );
        // Set bit[0], DSBL_CCMC, disable CCM HW, is 1 to disable the CCM HW.
        __printf(LOW, "  Write HML3_QCCMCR ");
        write_reg( inst_base, HML3_QCCMCR_OFFSET, 0x00000001 );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Set the number of XO clock cycles between QoS Beacons
* @param
*    mode:               The execution platform/target (e.g., SILICON)
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure: HML3_QBCR, R/W, L3 QoS Beacon Control reg.
*
******************************************************************************/
void set_qosbeacon_dly( target_mode_e mode, uint64_t inst_base )
{
    uint32_t QoS_beacon_spacing = 0x28;  // reset val

    __printf(LOW, " Set the QoS Beacon rate: \n" );
    __printf(LOW, "  Read-Modify_Write HML3_QBCR ");

    if(( mode == RUMI42 ) || (mode == RUMI48 ))
    {
        QoS_beacon_spacing = QBCR_QOSBEACON_DLY_RUMI_VAL;
    }
    else if( mode == SILICON )
    {
        QoS_beacon_spacing = QBCR_QOSBEACON_DLY_SILICON_VAL;
    }

    // Set the period of the QoS Beacon commands.
    read_modify_write_reg( inst_base, HML3_QBCR_OFFSET,
                               QBCR_QOSBEACON_DLY__M, QBCR_QOSBEACON_DLY__S,
                               QoS_beacon_spacing );
}

/*!****************************************************************************
*
* @par Description:
*    Clear the Error status and reporting bits.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_FIRAC reg, W/Clear - L3 Fault Isolation & Reporting Clear reg A. Writes
*    (setting bits to 1) to this reg clear the HML3_FIRA, Read-Only - L3 Fault
*    Isolation & Reporting reg A.
*    HML3_FIRSYNA/B/C/D regs, R/W - L3 Fault Isolation Syndrome reg A/B/C/D.
*    HML3_FIRSYNA.FIRSYN_FROZEN, bit0, must be cleared first.
*    HML3_CRC - L3 Config Control Register C
*
******************************************************************************/
void clear_error_status( uint64_t inst_base )
{
//    __printf(LOW, " Clear Error Status and Reporting bits: \n" );

    __printf(LOW, "  Write HML3_CRC ");
    write_reg( inst_base, HML3_CRC_OFFSET, 0x7F );

    __printf(LOW, "  Write HML3_FIRSYNA ");
    write_reg( inst_base, HML3_FIRSYNA_OFFSET, 0x00000000 );

    __printf(LOW, "  Write HML3_FIRSYNB ");
    write_reg( inst_base, HML3_FIRSYNB_OFFSET, 0x00000000 );

    __printf(LOW, "  Write HML3_FIRSYNC ");
    write_reg( inst_base, HML3_FIRSYNC_OFFSET, 0x00000000 );

    __printf(LOW, "  Write HML3_FIRSYND ");
    write_reg( inst_base, HML3_FIRSYND_OFFSET, 0x00000000 );

    __printf(LOW, "  Write HML3_FIRAC ");
    write_reg( inst_base, HML3_FIRAC_OFFSET, 0xFFFFFFFF );
}

/*!****************************************************************************
*
* @par Description:
*    Decide what masked error bits (see HML3_FIRA reg) to set to report
*    non-fatal interrupts.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_FIRAT0S, Write/Set - L3 FIR Type 0 Set reg.
*    Writing to HML3_FIRAT0S sets the corresponding bits in HML3_FIRAT0, W/R -
*    L3 FIRA Type 0 (non-fatal ints) reg.
*
******************************************************************************/
void setup_info_ints( uint64_t inst_base )
{
    // Set the individual bits for the FIRAT0 reg to control what masked errors will cause
    //  non-fatal interrupts

    __printf(LOW, " Setup Info Interrupts:  \n");
    __printf(LOW, "  Write HML3_FIRAT0S ");

    write_reg( inst_base, HML3_FIRAT0S_OFFSET, FIRAT0S_VAL );
}

/*!****************************************************************************
*
* @par Description:
*    Decide what masked error bits (see HML3_FIRA) to set to report
*    fatal interrupts.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_FIRAT1S, Write/Set - L3 FIR Type 1 Set reg.
*    Writing to HML3_FIRAT1S sets the corresponding bits in HML3_FIRAT1, W/R -
*    L3 FIRA Type 1 (fatal ints) reg.
*
******************************************************************************/
void setup_fatal_ints( uint64_t inst_base )
{
    // Set the individual bits for the FIRAT1 reg to control what masked errors will cause
    //  fatal interrupts

    __printf(LOW, " Setup Fatal Interrupts:  \n");
    __printf(LOW, "  Write HML3_FIRAT1S ");

    write_reg( inst_base, HML3_FIRAT1S_OFFSET, FIRAT1S_VAL );
}

/*!****************************************************************************
*
* @par Description:
*    Disable DCIALL usage for all L3 instances.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_CRD, R/W - L3 Configuration Control reg D.
*    DCIALL is an implementation defined instruction and can't be used by pure
*    ARM cpu's like IMC.
*
******************************************************************************/
void disable_DCIALL( uint64_t inst_base )
{
    // Set to 1 the Disable DCIALL bit to further ignore the implementation-defined
    //  command DCIALL.
    __printf(LOW, " Disable DCIALL : \n" );
    __printf(LOW, "  Write HML3_CRD ");

    write_reg( inst_base, HML3_CRD_OFFSET, CRD_DDCIALL_NOP );
}

/*!****************************************************************************
*
* @par Description:
*    Restore normal operation flow after invalidation.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_CR0/1, R/W - L3 Control reg 0 (I0) and 1 (for I1).
*
******************************************************************************/
void enable_lookups( uint64_t inst_base, uint32_t even_flag, uint32_t odd_flag )
{
    __printf(LOW, " Enable lookups : \n" );

    // Set HML3_CRi.FLMNA to 0 to ensure normal operation flow (i.e. tag/SFT lookups).
    // If the even interleave of this L3 instance is online write the register
    if( even_flag != 0 )
    {
        __printf(LOW, "  Write HML3_CR0 ");
        write_reg( inst_base, HML3_CR0_OFFSET, 0x00000000 );
    }

    // Check if the odd interleave of this L3 instance is online.
    if( odd_flag != 0 )
    {
        __printf(LOW, "  Write HML3_CR1 ");
        write_reg( inst_base, HML3_CR1_OFFSET, 0x00000000 );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Control the L3 cache line allocation via the line replacement policy.
* @param
*    inst_base:    The absolute address of the L3 instance in the QLL space
*                   i.e., including the Monaco ring switch address.
* @par Globals:
*    replacement_policy:  Either LRU (psudo-LRU) or RANDOM as directed by user.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_ALOCR, R/W - L3 Allocation Override Control reg.
*    The user setting (LRU or RANDOM) is translated into a meaningful reg value
*    i.e., b'00 or b'10.
*
******************************************************************************/
void override_alloc( uint64_t inst_base )
{
    uint32_t repl_policy_val = ALOCR_REPL_POLICY_LRU;  // default is pseudo-LRU

    if( replacement_policy == LRU )
    {
        repl_policy_val = ALOCR_REPL_POLICY_LRU;
    }
    else if( replacement_policy == RANDOM )
    {
        repl_policy_val = ALOCR_REPL_POLICY_RANDOM;
    }
    else
    {
        __printf(HIGH, "   ERROR: unknown Replacement Policy, defaulting to LRU\n");
    }

    __printf(LOW, " Override L3 Allocations: \n" );
    __printf(LOW, "  RMW HML3_ALOCR ");

    // Set the replacement policy.
    read_modify_write_reg( inst_base, HML3_ALOCR_OFFSET,
                               ALOCR_REPL_POLICY__M, ALOCR_REPL_POLICY__S,
                               repl_policy_val );
}

/*!****************************************************************************
*
* @par Description:
*    Setup L3 CLK tree gating counter to the desired timeout value.
* @param
*    inst_base:         The absolute address of the L3 instance in the QLL space
*                        i.e., including the Monaco ring switch address.
* @par Globals:
*    clockoff_cyc_cnt:  The CLK tree gating timeout value chosen by the user.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_PSCRB, R/W - L3 Power State Control reg B.
*    The user setting for the HML3_PSCRB.L3_CLKOFF_CNT field, is relevant if
*    clock gating gets enabled in the next step.
*
******************************************************************************/
void setup_L3_CLK_tree_gating_counter( uint64_t inst_base )
{
    __printf(LOW, " Setup the Clk Tree Gating Timer:  \n" );
    __printf(LOW, "  RMW HML3_PSCRB ");

    read_modify_write_reg( inst_base, HML3_PSCRB_OFFSET, PSCRB_CLKOFF_CNT__M,
                                       PSCRB_CLKOFF_CNT__S, clockoff_cyc_cnt );
}

/*!****************************************************************************
*
* @par Description:
*    Enable Clock tree gating to allow the L3 to gate its clock when idle.
* @param
*    inst_base:         The absolute address of the L3 instance in the QLL space
*                        i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_PSCRA, R/W - L3 Power State Control reg A
*
******************************************************************************/
void enable_CLK_tree_gating( uint64_t inst_base )
{
    // Enable the CLK tree gating on both interleaves.

    __printf(LOW, " Enable the Clk Tree Gating:  \n" );
    __printf(LOW, "  Write HML3_PSCRA ");

    // Enable CLK tree gating on both interleaves. Depending on the L3 ver the
    //  auto-gating of the clk is enabled on the LL POS L3.
    if( l3_hw_ver_maj_min == 0x1001 )
    {
        write_reg( inst_base, HML3_PSCRA_OFFSET, PSCRA_NO_POS_GATING_VAL );
    }
    else // (l3_hw_ver_maj_min==0x1002)
    {
        write_reg( inst_base, HML3_PSCRA_OFFSET, PSCRA_POS_GATING_VAL );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Lock down register groups to prevent access from non-secure code.
* @param
*    inst_base:         The absolute address of the L3 instance in the QLL space
*                        i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_RSCTL, R/W - L3 Register Security Control reg.
*
******************************************************************************/
void lockdown_reg_groups_for_non_secure_access( UNUSED_PARAM uint64_t inst_base )
{
    // the reset value, 0x00000FFF, is OK for now
}

/*!****************************************************************************
*
* @par Description:
*    Setup LiveLock i.e., select the query periods for both the address and data
*    phase queries; enable both the address and data phase queries.
* @param
*    mode:               The execution platform/target (e.g., SILICON)
* @param
*    inst_base:         The absolute address of the L3 instance in the QLL space
*                        i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (common) to configure:
*    HML3_LLBQF, R/W - L3 LiveLock Breaker Query Frequency register.
*    HML3_LLBCR, R/W - L3 LiveLock Breaker Control register.
*    The LL Backoff (aka correction/livelock breaker) is turned off.
*    The LL POS has been previously configured in the assign_POS... step.
*    Once the POS is setup for LL ops and the query(ies) are enabled the CLK
*     tree gating is disabled for the LL POS L3.
*
******************************************************************************/
void detect_livelock( target_mode_e mode, uint64_t inst_base )
{
    uint32_t LL_query_spacing = 0x000F000F;  // reset val

    __printf(LOW, " Setup LL Detection:  \n" );

    // Set the number of cycles (timeouts) between data and address phase queries.
    __printf(LOW, "  Write HML3_LLBQF ");

    if(( mode == RUMI42) || (mode == RUMI48 ))
    {
        LL_query_spacing =  LLBQF_LLQ_DLY_RUMI_VAL;
    }
    else if( mode == SILICON )
    {
        LL_query_spacing =  LLBQF_LLQ_DLY_SILICON_VAL;
    }

    write_reg( inst_base, HML3_LLBQF_OFFSET, LL_query_spacing );

    // Enable both Data and Address Phase LL queries.
    __printf(LOW, "  Write HML3_LLBCR ");
    write_reg( inst_base, HML3_LLBCR_OFFSET, LLBCR_QUERY_VAL );
}

// LL Breaker may be turned on only on Falkor-based builds
void enable_livelock_breaker( uint64_t inst_base )
{
     __printf(LOW, " Enable LiveLock Breaker:  \n" );

     // Turn on the LL breaker.
     __printf(LOW, "  RMW HML3_LLBCR ");
     read_modify_write_reg( inst_base, HML3_LLBCR_OFFSET, LLBCR_LL_BREAK__M,
                                       LLBCR_LL_BREAK__S, LLBCR_LL_BREAK_EN_VAL );
     // Control how many LL query ops should be sent before incrementing to the
     //  next deeper LL breaker mode.
     __printf(LOW, " Enable LiveLock Breaker: set level spacing \n" );
     __printf(LOW, "  RMW HML3_LLBCR ");
     read_modify_write_reg( inst_base, HML3_LLBCR_OFFSET, LLBCR_LL_BRKR_LVL_SPACING__M,
                         LLBCR_LL_BRKR_LVL_SPACING__S, LLBCR_LL_BRKR_LVL_SPACING_VAL);

     // Turn the LL trace tag on.
     __printf(LOW, " Enable LiveLock Breaker: turn the trace tag on \n" );
     __printf(LOW, "  RMW HML3_LLBCR ");
     read_modify_write_reg( inst_base, HML3_LLBCR_OFFSET, LLBCR_LL_TTAG__M,
                                      LLBCR_LL_TTAG__S, LLBCR_LL_TTAG_EN_VAL );
}

/*!****************************************************************************
* @par Description:
*    Wait until the L3 FAIC machine becomes idle.
* @param
*    inst_base:         The absolute address of the L3 instance in the QLL space
*                        i.e., including the Monaco ring switch address.
* @param
*    even_flag:         If not 0 the even instance is present in this node.
* @param
*    odd_flag:          If not 0 the odd instance is present in this node.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Regs (interleave) to access:
*    HML3_FAICSR0/1, R only - L3 Flush Allocation Invalidation Status reg, I0/I1
*
*******************************************************************************/
void wait_faic_idle( uint64_t inst_base, uint32_t even_flag, uint32_t odd_flag )
{
    uint32_t wait_val;

    __printf(LOW, " Wait for FAIC Machine Idle  \n");

    // Check if the even interleave, I0, is enabled.
    if( even_flag != 0 )
    {

        // Check if FAIC machine is idle i.e. read field FAIC_MACH_STAT of
        //  HML3_FAICSR0 for as long as the FAIC_MACH_STAT field is 1 (busy)

        // Wait for as long as the field val equals the wait val.
        do
        {

            wait_val = (read32( inst_base + HML3_FAICSR0_OFFSET ) & FAICSRn_FAIC_MACH_STAT__M) >> FAICSRn_FAIC_MACH_STAT__S;

        } while( wait_val == 1 );
    }

    // Check if this odd interleave, I1, is enabled.
    if( odd_flag != 0 )
    {

        // Check if FAIC machine is idle i.e. read field FAIC_MACH_STAT of
        //  HML3_FAICSR1 for as long as the FAIC_MACH_STAT field is 1 (busy)
        do
        {

            wait_val = (read32( inst_base + HML3_FAICSR1_OFFSET ) & FAICSRn_FAIC_MACH_STAT__M) >> FAICSRn_FAIC_MACH_STAT__S;

        } while( wait_val == 1 );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Clear the L3 error status and reporting bits on this L3 instance.
* @param
*    inst_num:        The L3 instance physical number (0 to MAX_L3_NODES).
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
*
******************************************************************************/
void instance_clear_errors( uint32_t inst_num, uint64_t inst_base )
{
    uint32_t inst_flag;  // whether this instance is available
    uint32_t even_flag;  // whether this even interleave is available
    uint32_t odd_flag;   // whether this odd interleave is available

    // Determine from the partial goods whether this instance (its interleaves)
    //  is online.
    get_inst_availability(inst_num, &inst_flag, &even_flag, &odd_flag);

    // Perform the clearing of the error status and reporting bits for the available L3s:
    if( inst_flag !=0x0 )
    {
        clear_error_status( inst_base );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Invalidate the L3 tags and the SFT tags of this instance using the FAIC
*    machine INVALIDATE_L3/INVALIDATE_SFT functions.
* @param
*    inst_num:        The L3 instance physical number (0 to MAX_L3_NODES).
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
*
******************************************************************************/
void instance_invalidate_all( uint32_t inst_num, uint64_t inst_base )
{
    uint32_t inst_flag;  // whether this instance is available
    uint32_t even_flag;  // whether this even interleave is available
    uint32_t odd_flag;   // whether this odd interleave is available

    // Determine from the partial goods whether this instance (its interleaves)
    //  is online.
    get_inst_availability(inst_num, &inst_flag, &even_flag, &odd_flag);

    // Start invalidating the available L3s:
    if( inst_flag !=0x0 )
    {
        // Perform the invalidation using the POR sequence on each available L3.
        faic_invalidate_all( inst_base, even_flag, odd_flag );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Clean this L3 instance using the FAIC machine CLEAN function.
* @param
*    inst_num:        The L3 instance number (0 to MAX_L3_NODES).
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
*
******************************************************************************/
void instance_clean( uint32_t inst_num, uint64_t inst_base )
{
    uint32_t inst_flag;  // whether this instance is available
    uint32_t even_flag;  // whether the instance's even interleave is available
    uint32_t odd_flag;   // whether the instance's odd interleave is available

    // Determine from the partial goods whether this instance (based on its
    //  interleave availability) is online.
    get_inst_availability(inst_num, &inst_flag, &even_flag, &odd_flag);

    // Start cleaning the L3's available interleave instance(s).
    if( inst_flag !=0x0 )
    {
        // Clean L3 via FAIC: FAIC machine walks through all L3 sets and ways;
        //  each line marked dirty in the tag array is written to memory;
        //  every tag for a dirty line is marked CLEAN.
        //  The snoop filter and data array contents are not affected.
        // Regs (interleave) to configure: HML3_FAICCRB0/1, L3 Flush Allocation
        //  Invalidation Control reg B, for interleaves 0 and 1.
        perform_faic_function( FAIC_CLEAN, inst_base, even_flag, odd_flag );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Flush this L3 instance using the FAIC machine FLUSH function.
* @param
*    inst_num:        The L3 instance number (0 to MAX_L3_NODES).
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    A cache Flush involves a cache Clean and a cache Invalidate.
*
******************************************************************************/
void instance_flush( uint32_t inst_num, uint64_t inst_base )
{
    uint32_t inst_flag;  // whether this instance is available
    uint32_t even_flag;  // whether the instance's even interleave is available
    uint32_t odd_flag;   // whether the instance's odd interleave is available

    // Determine from the partial goods whether this instance (based on its
    //  interleave availability) is online.
    get_inst_availability(inst_num, &inst_flag, &even_flag, &odd_flag);

    // Start flushing the L3's available interleave instance(s).
    if( inst_flag !=0x0 )
    {
        // Flush L3 via FAIC: FAIC machine walks through all L3 sets and ways;
        //  each line marked dirty in the tag array is written to memory;
        //  every tag regardless of the clean/dirty state is marked INVALID.
        //  The snoop filter and data array contents are not affected.
        perform_faic_function( FAIC_FLUSH, inst_base, even_flag, odd_flag );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Check whether this instance has reported any errors in its individual
*    Fault Isolation and Reporting register, HML3_FIRA.
* @param
*    inst_num:        The L3 instance number (0 to MAX_L3_NODES).
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @return
*    True if errors have been reported on this instance; false otherwise.
* @author
*    cbucsan
* @par Notes:
*    Reg (common) to access:
*    HML3_FIRA, R only - L3 Fault Isolation and Reporting register A.
*
******************************************************************************/
bool instance_report_errors( uint32_t inst_num, uint64_t inst_base )
{
    uint32_t fira_val;
    bool is_faulty = false;
    uint32_t inst_flag;  // whether this instance is available
    uint32_t even_flag;  // whether the instance's even interleave is available
    uint32_t odd_flag;   // whether the instance's odd interleave is available

    // Determine from the partial goods whether this instance (by means of its
    //  interleaves) is online.
    get_inst_availability(inst_num, &inst_flag, &even_flag, &odd_flag);

    // Read the HML3_FIRA regs of the available L3s
    if( inst_flag !=0x0 )
    {
        // Read the current val of the HML3_FIRA reg
        fira_val = read32( inst_base + HML3_FIRA_OFFSET );

        if( fira_val > 0 )
        {
            is_faulty = true;
            __printf(LOW, "     L3_%d reports errors: HML3_FIRA = %08X \n", inst_num, fira_val);
        }

    }

    return is_faulty;
}

/*!****************************************************************************
* @par Description:
*    Retrieve the At-Speed-Trace (AST) support.
* @param
*    inst_num:            The L3 instance number (from 0 to MAX_L3_NODES).
* @param
*    inst_ast_flag:       [Out Param] Pointer to the instance AST flag
* @param
*    even_ast_flag:       [Out Param] Pointer to the even interleave AST flag
*                             for this instance.
* @param
*    odd_ast_flag:        [Out Param] Pointer to the odd interleave AST flag
*                             for this instance.
* @par Globals:
*    l3_ast_cfg.trace_interleaves: Bit map representing the interleaves to be
*                             partitioned for AST.
* @return
*    Nothing
* @author
*    cbucsan
*
*******************************************************************************/
void get_AST_support
(
    uint32_t inst_num,
    uint32_t *inst_ast_flag,
    uint32_t *even_ast_flag,
    uint32_t *odd_ast_flag
)
{
    uint32_t inst_mask = 0x3;  // instance mask: each instance accounts for 2 interleaves
    uint32_t even_mask = 0x1;  // even interleave (I0) mask
    uint32_t odd_mask = 0x2;   // odd interleave (I1) mask

    __printf(LOW, " Get the AST Config:  \n" );

    *inst_ast_flag = (l3_ast_cfg.trace_interleaves >> (inst_num * 2)) & inst_mask;
    *even_ast_flag = (l3_ast_cfg.trace_interleaves >> (inst_num * 2)) & even_mask;
    *odd_ast_flag = (l3_ast_cfg.trace_interleaves >> (inst_num * 2)) & odd_mask;
}

/*!****************************************************************************
* @par Description:
*    Setup AST partitioning at specified percentage following the interleave map.
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @param
*    even_ast_flag:   If not 0 the even interleave is to be partitioned.
* @param
*    odd_ast_flag:    If not 0 the odd interleave is to be partitioned.
* @par Globals:
*    l3_ast_cfg.allocation: Percentage representing the portion of interleave
*                         to be partitioned for AST.
* @return
*    Nothing
* @author
*    cbucsan
* @par Notes:
*    Only 0%, 25% and 50% allocations are currently supported. 0% means no AST
*     partitioning at all i.e. AST is disabled.
*    Regs to access:
*     HML3_CRA, R/W, L3 Configuration Control reg. A, to check on the Affinity
*      Mode vs. Spread Mode for L3 allocations; AST works in Spread Mode only.
*     HML3_WMCR0/1, R/W, L3 Way Mask Control regs., I0/I1. Bits[19:0] represent
*      the waymask.
*
*******************************************************************************/
// Setup AST partitioning at specified percentage following the interleave map.
//   Only 0%, 25% and 50% are currently supported.
//   0% means no AST partitioning at all i.e. AST disabled.
// Note that Column 0 of the L3 Data Arrays must be available for AST to operate.
void set_AST_partition( uint64_t inst_base, uint32_t even_ast_flag, uint32_t odd_ast_flag )
{
    uint32_t waymask_val = 0;

    // Check the logical L3 allocation mode: spread (not affinity) mode only is allowed for AST.
    if(( read32( inst_base + HML3_CRA_OFFSET ) >> CRA_AMVSMC__S ) & 0x1)
    {
        __printf(HIGH, "   ERROR: AST: Affinity Mode is enabled, disable before continuing... \n");
        return;
    }

    // Check whether this even interleave is to be partitioned for AST.
    if( even_ast_flag != 0 )
    {
        __printf(LOW, "  RMW HML3_WMCR0 ");

        // Modify the HML3_WMCR0 register mask value depending on the portion of
        //  the L3 to be allocated.
        if( l3_ast_cfg.allocation == ALLOCATE_25_PERCENT )
        {
            // Allocate way[0:3] i.e. column 0.
            waymask_val = WMCR_WAYMASK_25_VAL;
        }
        else if( l3_ast_cfg.allocation == ALLOCATE_50_PERCENT )
        {
            // Allocate way[0:7] i.e. columns 0 and 1.
            waymask_val = WMCR_WAYMASK_50_VAL;
        }

        read_modify_write_reg( inst_base, HML3_WMCR0_OFFSET, WMCR_WAYMASK__M, WMCR_WAYMASK__S, waymask_val );
    }

    // Check whether the odd (I1) interleave is to be partitioned for AST.
    if( odd_ast_flag != 0 )
    {
        __printf(LOW, "  RMW HML3_WMCR1 ");

        // Modify the HML3_WMCR0 register mask value depending on the portion of
        //  the L3 to be allocated.
        if( l3_ast_cfg.allocation == ALLOCATE_25_PERCENT )
        {
            // Allocate ways[0:3] i.e. column 0.
            waymask_val = WMCR_WAYMASK_25_VAL;
        }
        else if( l3_ast_cfg.allocation == ALLOCATE_50_PERCENT )
        {
            // Allocate ways[0:7] i.e. columns 0 and 1.
            waymask_val = WMCR_WAYMASK_50_VAL;
        }

        read_modify_write_reg( inst_base, HML3_WMCR1_OFFSET, WMCR_WAYMASK__M, WMCR_WAYMASK__S, waymask_val );
    }
}

/*!****************************************************************************
*
* @par Description:
*    Reinitialize each of the available L3 instances after the watchdog reset.
* @param
*    inst_num:        The L3 instance number (0 to MAX_L3_NODES).
* @param
*    inst_base:       The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @return
*    Nothing
* @author
*    cbucsan
*
******************************************************************************/
void instance_wd_reset_reinit( uint32_t inst_num, uint64_t inst_base )
{
    uint32_t inst_flag;      // whether this instance is available
    uint32_t even_flag;      // whether this even interleave is available
    uint32_t odd_flag;       // whether this odd interleave is available
    uint32_t inst_ast_flag;  // whether this instance is available for AST
    uint32_t even_ast_flag;  // whether this even interleave is to be partitioned for AST
    uint32_t odd_ast_flag;   // whether this odd interleave is to be partitioned for AST

    // Determine from the partial goods whether this instance/its interleaves are online.
    get_inst_availability(inst_num, &inst_flag, &even_flag, &odd_flag);

    // Retrieve the AST support.
    get_AST_support(inst_num, &inst_ast_flag, &even_ast_flag, &odd_ast_flag);

    // Start re-initializing the available L3s.
    if( inst_flag !=0x0 )
    {
        // Set data array controls
        set_data_array_controls( inst_base );

        // Set miscellaneous configuration bits in HML3_HCRA and HML3_CRA
        set_misc_config_bits( inst_base );

        // Remap tag banks given yield issues on data arrays - bring-up only
        //   (i.e. not production) step

//        mask_and_disable_ways( inst_base, even_flag, odd_flag );

        // Setup AST given the AST map is non-zero
        if( inst_ast_flag !=0x0 )  // one or both interleaves on this instance to be partitioned for AST
        {
            __printf(LOW, "  AST: L3_%d: ", inst_num);
            set_AST_partition( inst_base, even_ast_flag, odd_ast_flag );
        }
    }
}

/*!****************************************************************************
*
* @par Description:
*    Determine the value to be written to the HML3_TCMAACAi (i.e. for either I0
*     or I1) regs to help the L3 instance calculate which addresses belong to
*     it when executing the FAIC-Allocate function.
* @param
*    inst_log_index:           The index of the available logical even
*                               interleave instance.
* @param
*    num_inst_per_interleave:  The number of L3 nodes(instances) with good even
*                               interleaves.
* @return
*    The value to be written to the HML3_TCMAACAi reg.
* @author
*    cbucsan
* @par Notes:
*    Registers (interleave) of interest:
*     HML3_TCMAACA0/1, TCM Allocation Address Control reg A, I0/I1.
*     Fields of interest:
*     L3BAR0_PRIM field, bits [31:28], primary inst select bit match (PA[11:8]
*     in spread mode and PA[15:12] in affinity mode).
*     L3BAR0_PRIM_MASK, bits[27:24], the AND mask for new address before
*     comparing with L3BAR0_PRIM field
*
******************************************************************************/
uint32_t get_alloc_val_bar0
(
    uint32_t inst_log_index,
    uint32_t num_inst_per_interleave
)
{
    uint32_t bar0_prim_mask;  // HML3_TCMAACAi.L3BAR0_PRIM_MASK, bits[27:24]
    uint32_t reg_val;         // final value to be written to HML3_TCMAACAi reg

    // Determine the L3BAR0_PRIM_MASK from the provided HPG tables.
    if(( num_inst_per_interleave >= 9 ) && ( num_inst_per_interleave <= 12 ))
    {
        bar0_prim_mask = 0x0F000000;
    }
    else if(( num_inst_per_interleave >= 5 ) && ( num_inst_per_interleave <= 8 ))
    {
        bar0_prim_mask = 0x07000000;
    }
    else if(( num_inst_per_interleave == 4 ) || ( num_inst_per_interleave == 3 ))
    {
        bar0_prim_mask = 0x03000000;
    }
    else if( num_inst_per_interleave == 2 )
    {
        bar0_prim_mask = 0x01000000;
    }
    else // there is 1 instance per interleave only.
    {
        bar0_prim_mask = 0x0;
    }

    // Put together the composite field (L3BAR0_PRIM field and L3BAR0_PRIM_MASK field)
    //  value to be written to the HML3_TCMAACAi reg.
    reg_val = bar0_prim_mask | (( inst_log_index << 28 ) & 0xF0000000);

    return reg_val;
}

/*!****************************************************************************
*
* @par Description:
*    Determine the value to be written to the HML3_TCMAACBi (i.e. for either I0
*     or I1) regs to help the L3 instance calculate which addresses belong to
*     it when executing the FAIC-Allocate function.
* @param
*    inst_log_index:           The index of the available logical even
*                               interleave instance.
* @param
*    num_inst_per_interleave:  The number of L3 nodes(instances) with good even
*                               interleaves.
* @return
*    The value to be written to the HML3_TCMAACBi reg.
* @author
*    cbucsan
* @par Notes:
*    Registers (interleave) of interest:
*     HML3_TCMAACB0/1, TCM Allocation Address Control reg B, I0/I1.
*     Fields of interest:
*     L3BAR1_EN, bit[26].
*     L3BAR1_PRIM, bits[25:22], primary compare val: PA[11:8] in spread,
*     PA[15:12] in affinity.
*     L3BAR1_SEC, bits[21:18], secondary compare val: PA[15:12] in spread,
*     PA[11:8] in affinity.
*     L3BAR1_SEC_MASK, bits[17:14], AND mask to apply to address before
*     perfoming the compare with BAR1_SEC.
*     L3BAR2_EN, bit[12].
*     L3BAR2_PRIM, bits[11:8].
*     L3BAR2_SEC, bits[7:4].
*     L3BAR2_SEC_MASK, bits[3:0].
*
******************************************************************************/
uint32_t get_alloc_val_bar12
(
    uint32_t inst_log_index,
    uint32_t num_inst_per_interleave
)
{
    uint32_t reg_val;     // value to be written to HML3_TCMAACBi reg

    // Determine the HML3_TCMAACB0/1 reg value from the provided HPG tables.
    if( num_inst_per_interleave == 12 )
    {
        reg_val = twelve_good_inst[inst_log_index];
    }
    else if( num_inst_per_interleave == 11 )
    {
        reg_val = eleven_good_inst[inst_log_index];
    }
    else if( num_inst_per_interleave == 10 )
    {
        reg_val = ten_good_inst[inst_log_index];
    }
    else if( num_inst_per_interleave == 9 )
    {
        reg_val = nine_good_inst[inst_log_index];
    }
    else if( num_inst_per_interleave == 8 )
    {
        reg_val = 0x0;
    }
    else if( num_inst_per_interleave == 7 )
    {
        reg_val = seven_good_inst[inst_log_index];
    }
    else if( num_inst_per_interleave == 6 )
    {
        reg_val = six_good_inst[inst_log_index];
    }
    else if( num_inst_per_interleave == 5 )
    {
        reg_val = five_good_inst[inst_log_index];
    }
    else if( num_inst_per_interleave == 4 )
    {
        reg_val = 0x0;
    }
    else if( num_inst_per_interleave == 3 )
    {
        reg_val = three_good_inst[inst_log_index];
    }
    else // 1 or 2 instances per interleave
    {
        reg_val = 0x0;
    }

    return reg_val;
}

/*!****************************************************************************
* @par Description:
*    Turn on LFSR in the LL POS to run at any time the CBF clock is running.
* @param
*    inst_num:        The L3 instance number (from 0 to MAX_L3_NODES).
* @return
*    Nothing
* @author
*    cbucsan
*
*******************************************************************************/
void turn_lfsr_on( uint64_t inst_base )
{
    __printf(LOW, "  RMW HML3_HCRA ");
    read_modify_write_reg( inst_base, HML3_HCRA_OFFSET, HCRA_FLFSRON__M,
                              HCRA_FLFSRON__S, HCRA_FLFSRON_VAL );
}

/*!****************************************************************************
* @par Description:
*    Determine from the partial goods whether this node's interleaves are
*    online.
* @param
*    inst_num:        The L3 instance number (from 0 to MAX_L3_NODES).
* @param
*    node_flag:       [Out Param] Pointer to the instance flag
* @param
*    even_itlv_flag:  [Out Param] Pointer to the even interleave flag for this node (instance).
* @param
*    odd_itlv_flag:   [Out Param] Pointer to the odd interleave flag for this node (instance).
* @par Globals:
*    l3_yield:        Bit map representing the L3 node/interleave availability.
* @return
*    Nothing
* @author
*    cbucsan
*
*******************************************************************************/
void get_inst_availability
(
    uint32_t inst_num,
    uint32_t *node_flag,
    uint32_t *even_itlv_flag,
    uint32_t *odd_itlv_flag
)
{
    uint32_t inst_mask = 0x3;  // instance mask: each instance accounts for 2 interleaves
    uint32_t even_mask = 0x1;  // even interleave (I0) mask
    uint32_t odd_mask = 0x2;   // odd interleave (I1) mask

    // Determine whether the instance/interleave is online
    *node_flag = (l3_yield >> (inst_num * 2)) & inst_mask;
    *even_itlv_flag = (l3_yield >> (inst_num * 2)) & even_mask;
    *odd_itlv_flag = (l3_yield >> (inst_num * 2)) & odd_mask;
}

/*!****************************************************************************
* @par Description:
*    Utility function to write a 32-bit value to a 32-bit register located at
*     a 64-bit address.
* @param
*    inst_base:   The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @param
*    reg_offset:  The register offset in the QLL space.
* @param
*    write_val:   The value to be written to the register whose offset is
*                   specified in reg_offset.
* @par Globals:
*    None
* @return
*    Nothing
* @author
*    cbucsan
*
*******************************************************************************/
void write_reg( uint64_t inst_base, uint64_t reg_offset, uint32_t write_val )
{
    uint64_t reg_addr;

    // Calculate the register address.
    reg_addr = inst_base + reg_offset;

    __printf(LOW, " Addr: %lX value: %08X \n", reg_addr, write_val );

    // Perform the write to the calculated register address.
    write32( reg_addr, write_val );
}

/*!****************************************************************************
* @par Description:
*    Utility function to Write-Read-Modify a 32-bit register located at a 64-bit
*     address calculated from the inst_base and reg_offset parameters below.
* @param
*    inst_base:   The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @param
*    reg_offset:  The register offset in the QLL space.
* @param
*    field_mask:  The bit mask of the field that needs to bew updated.
* @param
*    field_shift: The bit shift of the field that needs to bew updated.
* @param
*    field_val:   The value of the field that the reg is to be updated with.
* @par Globals:
*    None
* @return
*    Nothing
* @author
*    cbucsan
*
*******************************************************************************/
void read_modify_write_reg( uint64_t inst_base,
                            uint64_t reg_offset,
                            uint32_t field_mask,
                            uint32_t field_shift,
                            uint32_t field_val )
{
    uint64_t reg_addr;
    uint32_t read_val;   // the value read back from the register
    uint32_t write_val;

    // Calculate the register address
    reg_addr = inst_base + reg_offset;

    // Read the register
    read_val = read32( reg_addr );

    // Determine the value to be written to the register: clear the field of interest
    //  while leaving everything else unchanged then construct the write value
    write_val = ( read_val & ( ~field_mask ));
    write_val |= ( field_val << field_shift );

    // Write the value to the register
    write32( reg_addr, write_val );

    __printf(LOW, " Addr: %lX Mask: %X Val: %X Shift: %X", reg_addr, field_mask, field_val, field_shift );
    __printf(LOW, " Read val: %X Write after Modify val: %X \n", read_val, write_val );
}

/*!****************************************************************************
* @par Description:
*    Utility function to read a 32-bit value from a 32-bit register located at
*     a 64-bit address.
* @param
*    inst_base:   The absolute address of the L3 instance in the QLL space
*                       i.e., including the Monaco ring switch address.
* @param
*    reg_offset:  The register offset in the QLL space.
* @par Globals:
*    None
* @return
*    read_val
* @author
*    cbucsan
*
*******************************************************************************/
uint32_t read_reg( uint64_t inst_base,
                   uint64_t reg_offset )
{
    uint64_t reg_addr;
    uint32_t read_val;

    // Calculate the register address.
    reg_addr = inst_base + reg_offset;

    // Read the register
    read_val = read32( reg_addr );

    __printf(LOW, " Addr: %lX Read val: %X \n", reg_addr, read_val );

    return read_val;
}

static void _l3_fatcm_poll_faicstatus(uint32_t l3_pg)
{
    int inst_ix;
    uint64_t inst_base;
    uint32_t faic_status, l3_faic_status = 0;

    do {
        for (inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++) {
            inst_base = L3_0_QLL_BASE + (0x100000 * inst_ix);
            /* check interleave 0 */
            if (l3_pg & (0x1UL << (inst_ix*2))) {
                faic_status = read_reg(inst_base, HML3_FAICSR0_OFFSET);
                if ((faic_status & FAICSRn_FAIC_MACH_STAT__M) == FAICSRn_FAIC_MACH_STAT_IDLE) {
                    l3_faic_status = l3_faic_status | (0x1UL << (inst_ix*2));
                } else if (faic_status & FAICSRn_FAIC_ALLOCF_FAIL__M) {
                    printf("l3[%d:0] alloc failed\n", inst_ix);
                }
            }

            /* check interleave 1 */
            if (l3_pg & (0x1UL << (inst_ix*2+1))) {
                faic_status = read_reg(inst_base, HML3_FAICSR1_OFFSET);
                if ((faic_status & FAICSRn_FAIC_MACH_STAT__M) == FAICSRn_FAIC_MACH_STAT_IDLE) {
                    l3_faic_status = l3_faic_status | (0x1UL << (inst_ix*2+1));
                } else if (faic_status & FAICSRn_FAIC_ALLOCF_FAIL__M) {
                    printf("l3[%d:1] alloc failed\n", inst_ix);
                }
            }
        }
    } while (l3_faic_status != l3_pg);

}

static void _l3_fatcm_do_faic(uint32_t l3_pg, uint32_t faiccra0, uint32_t faiccrb0, uint32_t faiccra1, uint32_t faiccrb1)
{
    int inst_ix;
    uint64_t inst_base;

    /* loop for each instance */
    for (inst_ix = 0; inst_ix < MAX_L3_NODES; inst_ix++) {
        inst_base = L3_0_QLL_BASE + (0x100000 * inst_ix);

        /* allocate in interleave 0 */
        if (l3_pg & (0x1UL << (inst_ix*2))) {
            write_reg(inst_base, HML3_FAICCRA0_OFFSET, faiccra0);
            write_reg(inst_base, HML3_FAICCRB0_OFFSET, faiccrb0);
        }
        /* allocate in interleave 1 */
        if (l3_pg & (0x1UL << (inst_ix*2+1))) {
            write_reg(inst_base, HML3_FAICCRA1_OFFSET, faiccra1);
            write_reg(inst_base, HML3_FAICCRB1_OFFSET, faiccrb1);
        }
    }

    /* poll until all instance faic idle */
    _l3_fatcm_poll_faicstatus(l3_pg);
}

int l3_fatcm_init(uint32_t l3_pg, uint64_t start_addr, uint64_t size_in_mb, uint8_t faiccrb_nsprot)
{
    uint32_t faiccra = 0, faiccrb = 0;
	uint32_t chuncks = 0;

    /* build HML3_CFG_FAICCRA, HML3_CFG_FAICCRB value */
    faiccra = (((start_addr >> 16) & 0xFFFFFFF) << FAICCRAn_ALLOC_ADDR_HI__S) & FAICCRAn_ALLOC_ADDR_HI__M ;

    faiccrb = ( (0x2UL << FAICCRBn_FAIC_FUNCTION__S) & FAICCRBn_FAIC_FUNCTION__M ) |
              ( (((start_addr >> 4) & 0xFFF) << FAICCRBn_FAIC_ALLOC_ADDR__S) & FAICCRBn_FAIC_ALLOC_ADDR__M ) |
              ( (0x3f << FAICCRBn_FAIC_ALLOC_BLK_CNT__S) & FAICCRBn_FAIC_ALLOC_BLK_CNT__M ) |                 /* 64 blocks */
              ( (0x1 << FAICCRBn_FAIC_ALLOC_BLK_SIZE__S) & FAICCRBn_FAIC_ALLOC_BLK_SIZE__M ) |                /* 4k per block */
              ( (0x1 << FAICCRBn_FAIC_ALLOC_NOBACK__S) & FAICCRBn_FAIC_ALLOC_NOBACK__M ) |
              ( (0x1 << FAICCRBn_FAIC_ALLOC_LLK__S) & FAICCRBn_FAIC_ALLOC_LLK__M ) |                          /* set line lock bit */
              ( (faiccrb_nsprot << FAICCRBn_FAIC_ALLOC_NSPROT__S) & FAICCRBn_FAIC_ALLOC_NSPROT__M );

    /* allocate cache lines, (64*4)K per interleave, (64*4*2)K per instance */
    for (int i = 0; i < (size_in_mb * 2); i++)
    {
        _l3_fatcm_do_faic(l3_pg, faiccra, faiccrb, faiccra, faiccrb);
        faiccra += 0x8;
    }

    return 0;
}

int l3_fatcm_test()
{
    uint64_t *p, pattern = 0x1122334455667788;
    int ret = 0;

    printf("Fill data begin\n");

    for (p=(uint64_t*)fatcm_start_addr; p<(uint64_t*)(fatcm_start_addr+fatcm_size*1024*1024); p++) {
        *p = pattern;
    }

    printf("verify data begin\n");

    for (p=(uint64_t*)fatcm_start_addr; p<(uint64_t*)(fatcm_start_addr+fatcm_size*1024*1024); p++) {
        if (*p != pattern) {
            printf("Failed @0x%x : *p\n", (uint64_t)p, *p);
            ret = -1;
        }
    }

    return ret;
}
