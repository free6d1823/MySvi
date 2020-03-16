//-------------------------------------------------------------------------------
//-- Copyright (c) 2013 Qualcomm Technologies, Inc.
//-- All Rights Reserved.
//-- Confidential and Proprietary - Qualcomm Technologies, Inc.
//--
//-- All data and information contained in or disclosed by this document are
//-- confidential and proprietary information of QUALCOMM Incorporated, and
//-- all rights therein are expressly reserved. By accepting this material,
//-- the recipient agrees that this material and the information contained
//-- therein are held in confidence and in trust and will not be used,
//-- copied, reproduced in whole or in part, nor its contents revealed in
//-- any manner to others without the express written permission of QUALCOMM
//-- Incorporated.
//--
//-- This technology was exported from the United States in accordance with
//-- the Export Administration Regulations. Diversion contrary to U.S. law
//-- prohibited.
//-------------------------------------------------------------------------------
//-- Revision : $Revision: /main/var_11/1 $
//-- ----------------------------------------------------------------------------
//-- TestName    : hy_sysini_config.inc
//-- Description : This file includes the assember version of the include file
//--               that defines the data structure used to manage the Hydra
//--               warm/cold boot and initialization.
//-------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Variables in the global memory block that control the startup process
// In hy_sysini_config.s, defines offsets from SYSINI_CONFIG_GLOBAL
//------------------------------------------------------------------------------

.equ Offset_L2_Cache_Init, 0x000
.equ L2_Init_Flag, 0x1

//------------------------------------------------------------------------------
// Variables in the per-CPU memory blocks that control the startup process
// In hy_sysini_config.s, defines offsets from SYSINI_CONFIG_CPU#
//------------------------------------------------------------------------------

// Addresses for save/restore buffers
// Eventually we might store most of this data on the stack to improve cache
// hit rate but for now it's in a fixed buffer location

.equ Offset_DBG_RestoreAddress, 0x00
.equ Offset_ETM_RestoreAddress, 0x04
.equ Offset_CPU_RestoreAddress, 0x08

// Initial value for the CPSR (e.g.. whether to enable interrupts or not)
//  NOT USED in AArch64

.equ Offset_CpsrInitValue, 0x0C

// 0 => do all deterministic initialization, 1 => skip it
// This is typically 0 for the simulation environment
// Should be 1 for code on h/w that doesn't care

.equ Offset_SkipDeterministicInit, 0x10

// cache setup parameters
// -- note that 0x00 means to initialize and enable all caches
//    No other parameters supported at this time.

.equ Offset_Cache_Init, 0x11

// MMU setup parameters
// 0 = MMU is enabled
// 1 = MMU is disabled

.equ Offset_MMU_Init, 0x12

// DBG state initialization selector
// 0 = unlock but leave registers uninitialized
// 1 = legacy mode for simulation
//     i.e.  unlock, clear breakpoint and watchpoint control registers

.equ Offset_DBG_Init, 0x13

// ETM state initialization selector
// 0 = unlock but leave ETM off, for power benchmarks
// 1 = legacy mode for simulation
//     i.e.  unlock, enable ETM for simulation checking

.equ Offset_ETM_Init, 0x14

// Warm vs. cold boot
// 0 = just initialize and call the usual entry point (e.g. main or csect)
// 1 = restore state from memory and resume execution at previous point

.equ Offset_CpuRestoreAndResume, 0x15

// These are really for the environment-specific initialization

.equ Offset_NoFPInit, 0x16
.equ Offset_Unused, 0x17
.equ Offset_Environment, 0x18
.equ Offset_IU_Init, 0x19
.equ Offset_PerfMon_Init, 0x1A

// Values for Offset_Environment variable:
.equ Environment_bootROM, 0x42   // ASCII 'B'
.equ Environment_Sim, 0x4D   // ASCII 'M'
.equ Environment_Silicon, 0x4C   // ASCII 'L'

// We've reserved 768B for each CPU
// First 32B is for boot-time parameters above (including spare space
// between 0x1B and 0x20)
// Remainder is used for warm boot static save area

.equ Offset_WarmBootData, 0x020
