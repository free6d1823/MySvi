#include "hy_sysini_config.inc"
#include "qc_sysini_port.h"

        EXPORT      SYSINI_CONFIG_CPU
        EXPORT      SYSINI_CONFIG_GLOBAL
        EXPORT      L2_INIT_SEMAPHORE_LOC
        EXPORT      Size_CPU_Config_Table

        EXPORT      CPU_STATE
        EXPORT      cpu0_state
        EXPORT      cpu0_dbg_state
        EXPORT      cpu0_etm_state
        EXPORT      cpu0_cpu_state
        EXPORT      cpu1_state
        EXPORT      cpu1_dbg_state
        EXPORT      cpu1_etm_state
        EXPORT      cpu1_cpu_state

        // Include the sysini macros
        //INCLUDE     "hy_sysini_config.inc"

//------------------------------------------------------------------------------
        //AREA sysini_config_global, DATA, READWRITE, ALIGN=7
        //AREA sysini_config_global, "w"
	//.align 7
	.section sysini_config_global , "aw"; .align 7
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// L2 initialization semaphores for 32 CPU duplexes,
// The exclusive reservation granule is 128 bytes (CTR_EL0[ERG])
// Put 2 semaphores in each granule.
//------------------------------------------------------------------------------
L2_INIT_SEMAPHORE_LOC:

        ALIGN 64
                                DCD     0x03   // duplex 0
        ALIGN 64
                                DCD     0x03   // duplex 1
        ALIGN 64
                                DCD     0x03   // duplex 2
        ALIGN 64
                                DCD     0x03   // duplex 3
        ALIGN 64
                                DCD     0x03   // duplex 4
        ALIGN 64
                                DCD     0x03   // duplex 5
        ALIGN 64
                                DCD     0x03   // duplex 6
        ALIGN 64
                                DCD     0x03   // duplex 7
        ALIGN 64
                                DCD     0x03   // duplex 8
        ALIGN 64
                                DCD     0x03   // duplex 9
        ALIGN 64
                                DCD     0x03   // duplex 10
        ALIGN 64
                                DCD     0x03   // duplex 11
        ALIGN 64
                                DCD     0x03   // duplex 12
        ALIGN 64
                                DCD     0x03   // duplex 13
        ALIGN 64
                                DCD     0x03   // duplex 14
        ALIGN 64
                                DCD     0x03   // duplex 15
        ALIGN 64
                                DCD     0x03   // duplex 16
        ALIGN 64
                                DCD     0x03   // duplex 17
        ALIGN 64
                                DCD     0x03   // duplex 18
        ALIGN 64
                                DCD     0x03   // duplex 19
        ALIGN 64
                                DCD     0x03   // duplex 20
        ALIGN 64
                                DCD     0x03   // duplex 21
        ALIGN 64
                                DCD     0x03   // duplex 22
        ALIGN 64
                                DCD     0x03   // duplex 23
        ALIGN 64
                                DCD     0x03   // duplex 24
        ALIGN 64
                                DCD     0x03   // duplex 25
        ALIGN 64
                                DCD     0x03   // duplex 26
        ALIGN 64
                                DCD     0x03   // duplex 27
        ALIGN 64
                                DCD     0x03   // duplex 28
        ALIGN 64
                                DCD     0x03   // duplex 29
        ALIGN 64
                                DCD     0x03   // duplex 30
        ALIGN 64
                                DCD     0x03   // duplex 31
        ALIGN 64



SYSINI_CONFIG_GLOBAL:

//------------------------------------------------------------------------------
// To initialize L2 cache:
//     Set L2_Cache_Init = L2_Init_Flag
//------------------------------------------------------------------------------

L2_Cache_Init:                  DCB     L2_Init_Flag
                                DCB     0x00             // spare
                                DCB     0x00             // spare
                                DCB     0x00             // spare

// Reserve 512B for each CPU
// First 32B is for boot-time parameters
// Remainder is used for warm boot static save area

// Matches size of a CPU config block below

Size_CPU_Config_Table:           DCD    0x200

        ALIGN 0x20  // 32B alignment


//------------------------------------------------------------------------------
        //AREA sysini_config, DATA, READWRITE, ALIGN=5
        //AREA sysini_config, "w"
	//.align 5
	.section sysini_config, "aw"; .align 5
//------------------------------------------------------------------------------

SYSINI_CONFIG_CPU:

// 512 Bytes for each CPU - 32B of parameters + rest as warm boot data storage
SYSINI_CONFIG_CPU0:
CPU0_DBG_RestoreAddress:     DCD     0 // Not used and too large to fit: cpu0_dbg_state
CPU0_ETM_RestoreAddress:     DCD     0 // Not used and too large to fit: cpu0_etm_state
CPU0_CPU_RestoreAddress:     DCD     0 // Not used and too large to fit: cpu0_cpu_state
CPU0_CpsrInitValue:          DCD     0x00000000 // NOT USED in AArch64
CPU0_SkipDeterministicInit:  DCB     0x01       // Disabled for now in sim
CPU0_Cache_Init:             DCB     0x00       // Enabled in sim (0)
CPU0_MMU_Init:               DCB     0x00       // Enabled in sim (0)
CPU0_DBG_Init:               DCB     HYDRA_ASM_INIT_DBG       // Enabled in sim (1)
CPU0_ETM_Init:               DCB     HYDRA_ASM_INIT_ETM       // Enable ETM @init as for CPU sim
CPU0_CpuRestoreAndResume:    DCB     0x00
CPU0_NoFPInit:               DCB     0x00       // Now enabled in sim
CPU0_Unused:                 DCB     0x00
CPU0_Environment:            DCB     Environment_Silicon
CPU0_IU_Init:                DCB     HYDRA_ASM_INIT_IU      // Init IU resources for CPU sim
CPU0_PERF_MON_INIT:          DCB     HYDRA_ASM_INIT_PERF_MON// Init performance monitor resources for CPU sim
        ALIGN 0x20  // 32B alignment
CPU0_WarmBootData:               SPACE   0x1E0


SYSINI_CONFIG_CPU1:
CPU1_DBG_RestoreAddress:     DCD     0 // Not used and too large to fit: cpu1_dbg_state
CPU1_ETM_RestoreAddress:     DCD     0 // Not used and too large to fit: cpu1_etm_state
CPU1_CPU_RestoreAddress:     DCD     0 // Not used and too large to fit: cpu1_cpu_state
CPU1_CpsrInitValue:          DCD     0x00000000 // NOT USED in AArch64
CPU1_SkipDeterministicInit:  DCB     0x01       // Disabled for now in sim
CPU1_Cache_Init:             DCB     0x00       // Enabled in sim (0)
CPU1_MMU_Init:               DCB     0x00       // Enabled in sim (0)
CPU1_DBG_Init:               DCB     HYDRA_ASM_INIT_DBG       // Enabled in sim (1)
CPU1_ETM_Init:               DCB     HYDRA_ASM_INIT_ETM       // Enable ETM @init as for CPU sim
CPU1_CpuRestoreAndResume:    DCB     0x00
CPU1_NoFPInit:               DCB     0x00       // Now enabled in sim
CPU1_Unused:                 DCB     0x00
CPU1_Environment:            DCB     Environment_Silicon
CPU1_IU_Init:                DCB     HYDRA_ASM_INIT_IU      // Init IU resources for CPU sim
CPU1_PERF_MON_INIT:          DCB     HYDRA_ASM_INIT_PERF_MON// Init performance monitor resources for CPU sim
        ALIGN 0x20  // 32B alignment
CPU1_WarmBootData:               SPACE   0x1E0


/*
//------------------------------------------------------------------------------
       // AREA cpu_state, DATA, READWRITE
        //AREA cpu_state,"w"
        .section cpu_state, "w"
//------------------------------------------------------------------------------
// Reserve 4KB to store each CPU state for power collapse/restore
// Some day we'll move some of this to the OS stack for potentially better L2
// cache hit rate.

CPU_STATE:
cpu0_state:
cpu0_dbg_state:      SPACE 0x400
cpu0_etm_state:      SPACE 0x400
cpu0_cpu_state:      SPACE 0x800

cpu1_state:
cpu1_dbg_state:      SPACE 0x400
cpu1_etm_state:      SPACE 0x400
cpu1_cpu_state:      SPACE 0x800
*/

        END
