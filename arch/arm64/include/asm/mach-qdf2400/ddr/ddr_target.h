#ifndef __DDR_TARGET_H__
#define __DDR_TARGET_H__

/**
 * @file ddr_target.h
 * @brief
 * Header file for a specific DDR target

 Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

 Copyright (c) 2016 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.

==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <stdarg.h>
#include <asm/plat-centriq/ddr/mddr.h>
#include <asm/mach/monaco/common/DDRTargetLib.h>
#include <target/ddr/ddr_common.h>
#include <asm/mach/monaco/common/monaco_init.h>
#include <asm/mach/monaco/common/common_defs.h>
#include <target/smbus.h>

#define EFI_RESOURCE_ATTRIBUTE_PRESENT                  0x00000001
#define EFI_RESOURCE_ATTRIBUTE_INITIALIZED              0x00000002
#define EFI_RESOURCE_ATTRIBUTE_TESTED                   0x00000004
#define EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE              0x00000400
#define EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE        0x00000800
#define EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE  0x00001000
#define EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE     0x00002000

#define MDDR_CONFIG_ENHANCED_TRAINING					1

/*!****************************************************************************
*
* @defgroup hddrss_base_addrs Hydra DDR Sub-System (HDDRSS) Base Addresses
*
* @par Description
*    These are the HDDRSS base addresses that provide access to the
*    configuration registers for the DDR memory controllers and PHYs.
*
* @{
******************************************************************************/
#define MDDR_HDDRSS2_ADDR                  0xFF04000000  // Chan 0, MCSU0
#define MDDR_HDDRSS3_ADDR                  0xFF06000000  // Chan 1, MCSU1
#define MDDR_HDDRSS5_ADDR                  0xFF20000000  // Chan 2, MCSU3
#define MDDR_HDDRSS4_ADDR                  0xFF0A000000  // Chan 3, MCSU2
#define MDDR_HDDRSS0_ADDR                  0xFF1C000000  // Chan 4, MCSU4
#define MDDR_HDDRSS1_ADDR                  0xFF1A000000  // Chan 5, MCSU5

/* @} */
//DDR default frequency definition
#define DDR_MAX_SPEED_1DPC 1333
#define DDR_MAX_SPEED_2DPC 1200
#define DDR_MAX_SPEED_RECOVERY 800
#define DDR_MAX_SPEED_EMU 800
/*==========================================================================
                             DEFINED CONSTANTS
===========================================================================*/
/*==========================================================================
  @par Description
     DDR PHY image version information.
===========================================================================*/
#define PHY_IMG_VER "0.94a"

/*==========================================================================
  @par Description
     The lower 8 bits of the TCSR_SPARE3 register contain the platform ID
     information.
===========================================================================*/
#define EMULATION_PLATFORM_ID_MASK 0xFF

/*==========================================================================
  @par Description
     Real silicon is identified by the below value in the TSCR_SPARE3
     register.
===========================================================================*/
#define PLATFORM_SILICON 0x00

/*==========================================================================
  @par Description
     The Simulation platform is identified by the below value in the TSCR_SPARE3
     register.
===========================================================================*/
#define PLATFORM_SIM 0x10

/*==========================================================================
  @par Description
     The SUFI platform is identified by the below value in the TSCR_SPARE3
     register.
===========================================================================*/
#define PLATFORM_SUFI_42 0x42

/*==========================================================================
  @par Description
     The RUMI48 platform is identified by the below value in the TSCR_SPARE3
     register.
===========================================================================*/
#define PLATFORM_RUMI_48 0x48

/*==========================================================================
  @par Description
     The top 4 bits of the JTAG_ID register contain revision information.
===========================================================================*/
#define SILICON_REVISION_SHFT 28
#define SILICON_REVISION_MASK 0xF

/*==========================================================================
  @par Description
     Number of Memory Controllers and L3 Caches on the system
===========================================================================*/
#define NUM_MEMORY_CONTROLLERS 6
#define NUM_L3_CACHES 8

/*==========================================================================
  @par Description
     Base address of the DDR region on this target.
===========================================================================*/
#define DDR_REGION_BASE_ADDRESS 0x0

/*==========================================================================
  @par Description
     Attributes of the system memory.
===========================================================================*/
#define SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES \
                EFI_RESOURCE_ATTRIBUTE_PRESENT |                 \
                EFI_RESOURCE_ATTRIBUTE_INITIALIZED |             \
                EFI_RESOURCE_ATTRIBUTE_TESTED |                  \
                EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |             \
                EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |       \
                EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE | \
                EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE

/*==========================================================================
  @par Description
    SMBus SPD Software Command Addresses:
      These addresses address all SPD chips on a bus simultaneously.
      The general command format is [Addr Byte | Don't Care 1 | Don't Care 2]
      The slaves communicate back solely using ACKs and NACKs
===========================================================================*/
// Size of pages in SPD
#define SPD_PAGE_SIZE 256
// EEPROM Address Mask
#define SPD_EEPROM_ADDRESS_MASK 0b1010000
// SPD Logical Serial Address Bit Mask
#define SPD_ADDRESS_LSA_MASK 0b0000111

/* Reads to these addresses give you the Write Protection Status
   of a given block in the EEPROM
     If read NACKed, SWP has been set on the given block
     If read ACKed, SWP has not been set on the given block

  Writes to this address will enable Write Protection on the given block in EEPROM */

#define SPD_SW_COMMAND_WP_BLOCK0_ADDR           0x31
#define SPD_SW_COMMAND_WP_BLOCK1_ADDR           0x34
#define SPD_SW_COMMAND_WP_BLOCK2_ADDR           0x35
#define SPD_SW_COMMAND_WP_BLOCK3_ADDR           0x30

// Write to this address to clear all write protection
#define SPD_SW_COMMAND_CWP_ADDR                 0x33

// EE Page Address commands -
// SPA0 - Set EE Page Address to 0 -- Write only
#define SPD_SW_COMMAND_SPA0_ADDR                0x36
// SPA0 - Set EE Page Address to 1 -- Write only
#define SPD_SW_COMMAND_SPA1_ADDR                0x37
// RPA - Read EE Page Address
//   Reads to this address are either ACKed (SPD Page is 0), or NACKed (SPD Page is 1)
#define SPD_SW_COMMAND_RPA_ADDR                 0x36

//  length of  Identity string of combined DDR FW image
#define DDR4_FWIMG_ID_SIZE 8
//  padding size of DDR Firmware image
#define DDR4_FWIMG_SIZE_PAD 7

/*==============================================================================
                                  STRUCTURE
==============================================================================*/
/* Structure */
typedef struct {
    int16_t dimm_temps[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
    bool dimm_temp_event[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];
} ddr_thermal_info;

/*  == DDR FW image header ==
 ident      // 8bytes  // Identification string
 num_image  // 4bytes  // number of binary images packaged
 size_hdr   // 4bytes  // size of header chunk
 size_image // 4bytes  // size of binary data chunk
 start_image// 4bytes  // start offset of binary data chunk
 leng_ver;  // 4bytes  //length of version string
 leng_desc  // 4bytes  //length of description string
 binsize1   // 4bytes  // binary size of ddr4_rdimm_pmu_train_imem.bin
 binsize2   // 4bytes  // binary size of ddr4_rdimm_pmu_train_dmem.bin
 binsize3   // 4bytes  // binary size of ddr4_lrdimm_pmu_train_imem.bin
 binsize4   // 4bytes  // binary size of ddr4_lrdimm_pmu_train_dmem.bin
 binsize5   // 4bytes  // binary size of ddr4_pmu_train2D_imem.bin
 binsize6   // 4bytes  // binary size of ddr4_pmu_train2D_dimem.bin
 binsize7   // 4bytes  // binary size of ddr4_diags_imem.bin
 binsize8   // 4bytes  // binary size of ddr4_diags_dmem.bin
 binsize9   // 4bytes  // binary size of ddr4_pmu_ate_imem.bin
 binsize10  // 4bytes  // binary size of ddr4_pmu_ate_dmem.bin
 binsize11  // 4bytes  // binary size of ddr4_udimm_pmu_train_imem.bin
 binsize12  // 4bytes  // binary size of ddr4_udimm_pmu_train_dimem.bin
 binsize13  // 4bytes  // no bin defined
 binsize14  // 4bytes  // no bin defined
 binsize15  // 4bytes  // no bin defined
 binsize16  // 4bytes  // no bin defined
 binsize17  // 4bytes  // no bin defined
 binsize18  // 4bytes  // no bin defined
 binsize19  // 4bytes  // no bin defined
 binsize20  // 4bytes  // no bin defined
 Version String
 Description String
*/
typedef struct
{
    char ident[DDR4_FWIMG_ID_SIZE];
    uint32_t num_image;   //number of images combined
    uint32_t size_hdr;    //size of header
    uint32_t size_image;  //size of total images
    uint32_t start_image; //start offset of image block
    uint32_t leng_ver;    //length of version string
    uint32_t leng_desc;   //length of description string
    uint32_t binsize[DDR4_NUM_IMAGE];  //size of each images
}ddr4_fwimg_hdr_type;

typedef struct
{
    uint64_t binoffset[DDR4_NUM_IMAGE];  //size of each images
    bool bInit;                     // DDR FW does exist or not
}ddr4_fwimg_offset_type;

/*==========================================================================
*
* @par Description
*    This type serves MDDR Configuration Parameters stored in HOB.
*
* @par Members
*
*                                  <PRE>
*                                  </PRE>
*
===========================================================================*/
typedef struct {
    uint32_t mddr_var32[1];
       // ddr_pagesettings_burst_len
    uint8_t mddr_var8[1];
       // ddr_shared_dimm_clk
} MddrHobData_t;

/*==========================================================================
* @par Description
*    This type serves DDR SI Data Header and Data Table.
*
===========================================================================*/
//  length of  Identity string of combined DDR FW image
#define DDRSIIMG_ID_SIZE 8

typedef struct {
    char ident[DDR4_FWIMG_ID_SIZE];    // Header ID
    char platform[DDR4_FWIMG_ID_SIZE]; // Platform name
    uint16_t hdsize;                     // size of header chunck
    uint8_t  silMinver;                  // Silicon version
    uint8_t  silMajver;                  // Silicon version
    uint32_t freq;                       // DDR freqeuncy
    uint16_t DPCconfig;                  // Board DPC configuration
    uint16_t DIMMconfig;                 // number of DIMM populated
    uint16_t RANKconfig[2];              // RAnk configuration, FAR=0, NEAR=1
    uint64_t reserved[6];                // reserved for header expansion
} DDRSIDataHdr_t;

/*===========================================================================
                                 DATA
===========================================================================*/

/*===========================================================================
                         FUNCTION DECLARATIONS
===========================================================================*/
int monaco_initialize_target(monaco_init_t* monaco_init_ptr, bool cold_boot);
int monaco_margin_init_target(monaco_init_t* monaco_init_ptr);
void monaco_spd_cached_init(dimm_slot_smbus_info_t *smbus_info_p, uint64_t spd_base);
bool set_ddr_mem_info(ddr_info* info, ddr_size_partition* partition, ddr_size_info* size);
void get_thermal_info(ddr_thermal_info* thermal_info);
void enable_thermal_mitigation(uint8_t perf_percentage);
void disable_thermal_mitigation();
void enter_self_refresh_all();
void exit_self_refresh_all();
void auto_refresh_rate_adj(    mddr_dimm_refresh_rate_t adj_ref_dimm0,
    mddr_dimm_refresh_rate_t adj_ref_dimm1);
void auto_self_refresh_enable_all(uint32_t idle_delay);
void auto_self_refresh_disable_all();
void auto_power_down_enable_all(uint32_t idle_delay);
void auto_power_down_disable_all();

/* Helper functions */
target_mode_e get_platform_id();
int set_spd_page(SmbusDevice device, uint8_t page);

/* SMBUS Functions for XBL Loader */
dimm_slot_smbus_info_t *get_monaco_smbus_information(void);
int xbl_smbus_read_data_byte(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint8_t* out_data);
int xbl_smbus_read_data_word(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint16_t* out_data);
int xbl_smbus_read_generic(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, void* out_buffer, size_t buffer_size);
int xbl_smbus_read_cached_data_byte(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint8_t* out_data);
int xbl_smbus_read_cached_data_word(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint16_t* out_data);
int xbl_smbus_read_cached_generic(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, void* out_buffer, size_t buffer_size);
int xbl_smbus_write_generic(uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, void* in_buffer, size_t buffer_size);
int xbl_smbus_write_data_byte(uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, uint8_t value);
int xbl_smbus_write_data_word(uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, uint16_t value);

/* Clock Functions for XBL Loader */
bool xbl_prepare_clock_change(uint32_t nMDDRChannel, uint32_t nFreqKHz);
bool xbl_apply_clock_change(uint32_t nMDDRChannel, mddr_clk_type_t clk_type);
bool xbl_clean_up_clock_change(uint32_t nMDDRChannel);

/* Clock Functions for XBL Loader */
bool xbl_wait_us(uint32_t us_to_wait);
int xbl_printf(const char * fmt, va_list vargs);
void xbl_rs_bum_read_counter(rs_type_e su_type, uint32_t su_id, rs_bum_cntr_t *bum_cnt);
void xbl_ddr_bum_read_counter(mddr_bum_info_t *mddr_bum_info_ptr);
void xbl_ddr_get_state_info(mddr_state_info_t* ddr_state);

#endif
