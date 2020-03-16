/** @file ddr_reg_logging.c

  Functions for logging various memory subsystem registers on memory state change

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
**/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include <stddef.h>
#include <errno.h>
#include <target/ddr.h>

#define HWIO_SPARE3_ADDR(x)                                ((x) + 0x00090000)
/*===========================================================================
                                 DATA
===========================================================================*/ 
/* Base Addresses of Hardware Blocks */
size_t memory_controller_base_addresses[NUM_MEMORY_CONTROLLERS] =
                                            {
                                                D0_DDRSS_BASE,
                                                D1_DDRSS_BASE,
                                                D2_DDRSS_BASE,
                                                D3_DDRSS_BASE,
                                                D4_DDRSS_BASE,
                                                D5_DDRSS_BASE
                                            };

size_t l3_cache_base_addresses[NUM_L3_CACHES] = 
                                            {
                                                APCS_L3U00_HML3_CSR_REG_BASE,
                                                APCS_L3U01_HML3_CSR_REG_BASE,
                                                APCS_L3U02_HML3_CSR_REG_BASE,
                                                APCS_L3U03_HML3_CSR_REG_BASE,
                                                APCS_L3U04_HML3_CSR_REG_BASE,
                                                APCS_L3U05_HML3_CSR_REG_BASE,
                                                APCS_L3U06_HML3_CSR_REG_BASE,
                                                APCS_L3U07_HML3_CSR_REG_BASE
                                            };

size_t memory_controller_register_offsets[] =
                                            {
                                                HWIO_D0_ERR_STATUS_OFFS
                                            };
size_t l3_cache_register_offsets[] =  
                                            {
                                                HWIO_APCS_L3U00_HML3_FIRA_OFFS
                                            };
size_t other_register_addresses[] =
                                            {
                                                HWIO_SPARE3_ADDR(TCSR_REGS_REG_BASE)
                                            };

/*===========================================================================
                      FUNCTION DEFINITONS
===========================================================================*/ 
/* ============================================================================
**  Function : log_memory_status_registers
** ============================================================================
*/
/*!
*   @brief
*   This function initializes the necessary pieces to log memory registers.
*   
*   @details
*   This function takes in partial goods information to ensure that the register 
*   logging function doesn't try and access any hardware parts that did not yield.
*   
*   @param l3_pg   -  [IN] A partial goods mask for L3 Caches
*   @param mc_pg   -  [IN] A partial goods mask for Memory Controllers
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
int log_registers_init(uint64_t l3_pg, uint64_t mc_pg)
{
    int i;

    // Check L3 partial goods
    for(i = 0; i < (sizeof(l3_cache_base_addresses) / sizeof(size_t)); i++)
    {
        // If this hardware hasn't yield, set the address to NULL in our list of 
        // base addresses
        if(((l3_pg >> (i * 2)) & 0x3) == 0x0)
        {
            l3_cache_base_addresses[i] = 0x0; // NULL
        }
    }

    // Check Memory Controller partial goods
    for(i = 0; i < (sizeof(memory_controller_base_addresses) / sizeof(size_t)); i++)
    {
        // If this hardware hasn't yield, set the address to NULL in our list of 
        // base addresses
        if(((mc_pg >> i) & 0x1) == 0x0)
        {
            memory_controller_base_addresses[i] = 0x0; // NULL
        }
    }

    return 0;
}

/* ============================================================================
**  Function : log_memory_status_registers
** ============================================================================
*/
/*!
*   @brief
*   This function will log the set of registers defined in ddr_reg_logging.h
*   for debugging purposes.
*   
*   @details
*   This function is intended to capture debug information about various
*   memory subsystems. It is intended to be called in a before/after paradigm
*   where the faulting operation or memory state change is triggered in between
*   the two function calls.
*   
*   @param reg_snapshot   -  [IN] A pointer the structure where we will store the register
*                                 data.
*   
*   @par Dependencies
*   None
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
int log_memory_status_registers(register_snapshot* reg_snapshot)
{
    uint8_t memory_controller, l3_cache, reg;

    if(reg_snapshot == NULL)
    {
        return -EINVAL;
    }

    // Log registers for each memory controller
    for(memory_controller = 0; memory_controller < (sizeof(memory_controller_base_addresses) / sizeof(size_t)); memory_controller++)
    {
        // If the base address is NULL, it means the hardware block is bad and hasn't been initialized
        if(memory_controller_base_addresses[memory_controller] != 0x0)
        {
            // Log all of the per instance registers
            for(reg = 0; reg < (sizeof(memory_controller_register_offsets) / sizeof(size_t)); reg++)
            {
               reg_snapshot->mc_vals[memory_controller].values_array[reg] = in_dword(memory_controller_base_addresses[memory_controller] + memory_controller_register_offsets[reg]);
            }
        }
    }

    // Log registers for each L3 cache
    for(l3_cache = 0; l3_cache < (sizeof(l3_cache_base_addresses) / sizeof(size_t)); l3_cache++)
    {
        // If the base address is NULL, it means the hardware block is bad and hasn't been initialized
        if(l3_cache_base_addresses[l3_cache] != 0x0)
        {
            // Log all of the per instance registers
            for(reg = 0; reg < (sizeof(l3_cache_register_offsets) / sizeof(size_t)); reg++)
            {
               reg_snapshot->l3_vals[l3_cache].values_array[reg] = in_dword(l3_cache_base_addresses[l3_cache] + l3_cache_register_offsets[reg]);
            }
        }
    }

    // Log any other "one off" registers
    for(reg = 0; reg < (sizeof(other_register_addresses) / sizeof(size_t)); reg++)
    {
        reg_snapshot->other_vals.values_array[reg] = in_dword(other_register_addresses[reg]);
    }

    return 0;
}

