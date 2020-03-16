#ifndef _MODULE_DDR_TARGET_LIB_H_
#define _MODULE_DDR_TARGET_LIB_H_

/** @file DDRTargetLib.h

  External header File for DDRTargetLib

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
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <target/ddr/DDRCommonLib.h>
#include <target/ddr/SPDConfig.h>
#include <asm/mach/monaco/common/monaco_defs.h>
#include <asm/mach/monaco/memory/mddr_si.h>

/*==========================================================================
                             DEFINED CONSTANTS
===========================================================================*/
#define DDR_STATUS_SUCCESS 0
#define DDR_STATUS_FAILURE -1
#define DDR_STATUS_NO_MEMORY -2
#define DDR_INVALID_PARAMETER -3
#define DDR_INVALID_FIRMWARE -4

/*==========================================================================
  @par Description
     Number of DDR channels and slots per channel
===========================================================================*/
#define DDR_MAX_NUM_CHANS 6
#define DDR_MAX_NUM_SLOTS_PER_CHAN 2

/*==========================================================================
  @par Description
    Maximum number of frequencies in the DDR clock plan (used for static
    memory allocation)
===========================================================================*/
#define MAX_CLOCK_PLAN_SIZE 8

typedef uint32_t  EFI_RESOURCE_ATTRIBUTE_TYPE;
/*==========================================================================
                                  MACROS
===========================================================================*/

/*==========================================================================
                                DATA TYPES
===========================================================================*/
/*==========================================================================
*
* @par Description
*    This type provides the necessary single instance DDR information to
*    other systems.
*
* @par Members
*
*                                  <PRE>
*    version                Version information of the DDR function table
*    ddr_func_tbl_ptr       Pointer to the function table
*    size                   Size of the function table
*                                  </PRE>
*
===========================================================================*/
typedef struct
{
  uint32_t version;           //!< Version of function table
  void *ddr_func_tbl_ptr;     //!< Pointer to function table
  uint32_t size;              //!< Size of function table
} ddr_shared_params;


/*==========================================================================
*
* @par Description
*    This type serves as a package to indicate DIMM slot population info.
*
* @par Members
*
*                                  <PRE>
*    population_map      Boolean map that contains DIMM population info.
*                                  </PRE>
*
===========================================================================*/
typedef struct
{
    bool population_map[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
} ddr_dimm_pop_map;


/*==========================================================================
*
* @par Description
*    This type serves as a basic memory subsystem info structure.
*
* @par Members
*
*                                  <PRE>
*    base_ddr_address      The base address of the DDR memory region.
*    ddr_region_size       Size of the DDR memory region in Megabytes.
*    ddr_region_attributes A bitfield of the attributes of this DDR region.
*                                  </PRE>
*
===========================================================================*/
typedef struct
{
    uint64_t                    base_ddr_address;
    uint64_t                    ddr_region_size;
    EFI_RESOURCE_ATTRIBUTE_TYPE ddr_region_attributes;
} monaco_memory_info_t;

/*==========================================================================
*
* @par Description
*    This type serves ID of DDR PHY training Firmware
*
* @par Members
*
*    members of DDR Firmware ID
*
===========================================================================*/
#define     DDR4_NUM_IMAGE 20

/*==========================================================================
*
* @par Description
*    This type serves default value of DDR cycle adjustment
*
* @par Members
*
*    DDR cycle adjustment default value table ID
*
===========================================================================*/
typedef enum
{
    DDRCYCLE_EMU,
    DDRCYCLE_DEF_SIL,
    DDRCYCLE_LO_SIL,
    DDRCYCLE_HI_SIL,
} ddrcycle_table_id_type;

/*===========================================================================
                           GLOBAL VARIABLES
===========================================================================*/

/*===========================================================================
                         FUNCTION DECLARATIONS
===========================================================================*/

/*=========================================================================*/
/*======================= MONACO INIT FUNCTIONS ===========================*/
/*=========================================================================*/
/**
* Initializes the DDR training FW images
*
* @return Status of monaco initialization (success/failure)
*/
int monaco_init_ddr4_image(uint64_t ddr_fw_base);

/**
* get the offset and size of DDR training FW images
*
* @return address and size of ddr4 training image (success/failure)
*/
int monaco_get_ddr4_image_info(uint16_t fwid, uint64_t* out_addr, uint32_t* out_size);

/**
* Initializes the three Monaco components (MDDR, L3, and Monaco Bus)
*
* @return Status of monaco initialization (success/failure)
*/

int monaco_initialize_device(uint64_t cpu_pg, uint64_t l3_pg, uint64_t ddr_fw_base, uint64_t spd_base);
/**
* Reinitializes the three Monaco components (MDDR, L3, and Monaco Bus) after
* a watchdog reset (to allow a debug image to retrieve DDR contents after a WDOG reset)
*
* @return Status of monaco re-initialization (success/failure)
*/
int monaco_wdog_reinitialize_device(uint64_t cpu_pg, uint64_t l3_pg, uint64_t ddr_fw_base, uint64_t spd_base);

/**
* Returns some basic information about the memory subsystem.
*
* @return Structure containing basic memory information parameters.
*/
monaco_memory_info_t monaco_get_memory_info();

/**
* Returns revision number of QDF2432 SoC.
*
* @return revision number 0:SoC1.0/  1:SoC1.1  / 2:SoC1.2
*/
int get_silicon_revision(void);

/**
* enter DDR self refresh.
*
* @return None
*/
void enter_self_refresh_all(void);

/**
* Exit from self refresh mode.
*
* @return none
*/
void exit_self_refresh_all(void);

/*=========================================================================*/
/*====================== HOB RESOURCE FUNCTIONS ===========================*/
/*=========================================================================*/
/**
* Populates a DIMM map with boolean values based on which DIMMs are present.
*
* @return None.
*/
void get_active_channels(ddr_dimm_pop_map* map);

/**
* Reads the whole SPD for all populated DIMMs into Buffer.
*
* @return Status of the SPD retreival operation (success/failure)
*/
int get_spd_data(SPD_CONFIG_BUFFER_PROPS * spd_config_buffer);

/**
* Gets an array of SPD information structures (one per DIMM)
*
* @return Status of the SPD retreival operation (success/failure)
*/
int get_spd_smbios_information(spd_info_per_dimm* spd_info_array, size_t array_size);

/**
* Executes an SMBUS Read Byte command (Sends read command to device then
*   receives data)
*
* @return Status of the single instance parameter retreival operation (success/failure)
*/
void get_single_instance_information(ddr_shared_params* ddr_single_instance_params);

/*=============================================================================*/
/*============================= SMBUS FUNCTIONS ===============================*/
/*=============================================================================*/

/* ============================================================================
**  Function : ddr_smbus_read_data_byte
** ===========================================================================*/
int ddr_smbus_read_data_byte(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint8_t* out_data);

/* ============================================================================
**  Function : ddr_smbus_read_data_word
** ===========================================================================*/
int ddr_smbus_read_data_word(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint16_t* out_data);

/* ============================================================================
**  Function : ddr_smbus_block_read
** ===========================================================================*/
int ddr_smbus_block_read(uint32_t smbus_id, uint32_t smb_address, uint8_t spd_bank_num, uint16_t spd_reg_id, void* out_buffer, uint32_t buffer_size);

/* ============================================================================
**  Function : ddr_smbus_write_data_byte
** ===========================================================================*/
int ddr_smbus_write_data_byte(uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, uint8_t value);

/* ============================================================================
**  Function : ddr_smbus_write_data_word
** ===========================================================================*/
int ddr_smbus_write_data_word(uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, uint16_t value);

/* ============================================================================
**  Function : ddr_smbus_block_write
** ===========================================================================*/
int ddr_smbus_block_write(uint32_t smbus_id, uint32_t smb_address, uint8_t spd_bank_num, uint16_t spd_reg_id, void* oin_buffer, uint32_t buffer_size);

/*=============================================================================*/
/*============================= CLOCK FUNCTIONS ===============================*/
/*=============================================================================*/

/* ============================================================================
**  Function : ddr_prepare_clock_change
** ===========================================================================*/
bool ddr_prepare_clock_change(uint32_t nMDDRChannel, uint32_t nFreqKHz);

/* ============================================================================
**  Function : ddr_apply_clock_change
** ===========================================================================*/
bool ddr_apply_clock_change(uint32_t nMDDRChannel, uint32_t clk_type);

/* ============================================================================
**  Function : ddr_clean_up_clock_change
** ===========================================================================*/
bool ddr_clean_up_clock_change(uint32_t nMDDRChannel);

/* ============================================================================
**  Function : ddr_store_margining_result
** ===========================================================================*/
void ddr_store_margining_result(void);

/* ============================================================================
**  Function : ddr_check_margining_enable
** ===========================================================================*/
void ddr_check_margining_enable(unsigned long *ddrsi_base, void *margin_config_data, unsigned long *ddr_margining_result);
/*=============================================================================*/
/*============================= UTILITY FUNCTIONS =============================*/
/*=============================================================================*/

/* ============================================================================
**  Function : ddr_wait_us
** ===========================================================================*/
bool ddr_wait_us(uint32_t us_to_wait);

/* ============================================================================
**  Function : ddr_printf
** ===========================================================================*/
int ddr_printf(const char * fmt, va_list vargs);

/* ============================================================================
**  Function : ddr_get_si
** ===========================================================================*/
void ddr_get_si(mddr_si_selector_t *selector_ptr, mddr_si_chan_t *si_data_ptr);

#endif
