#ifndef __DDR_FUNC_TBL_H__
#define __DDR_FUNC_TBL_H__


/**
 * @file ddr_func_tbl.h
 * @brief
 * Header file that contains shared function table structure for XBL and RPM to
 * use common ddr library

 Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc

 Copyright (c) 2016 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.

==============================================================================*/
/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <asm/mach/ddr/ddr_target.h>

/*==========================================================================
                             DEFINED CONSTANTS
===========================================================================*/
/*==========================================================================
  @par Description
     The version of the function table defined in this file.
===========================================================================*/
#define DDR_FUNC_TABLE_VERSION 11

typedef enum
{
    XBL,
    IMC,
    // EMULATION PLATFORMS
    XBL_SUFI,
    IMC_SUFI,
    XBL_RUMI,
    IMC_RUMI,
    // SIMULATION PLATFORMS
    XBL_SIM,
    IMC_SIM,
} active_platform;

/*==============================================================================
                                  STRUCTURE
==============================================================================*/
typedef struct
{
    /* SMBUS functions */
    int (*read_data_byte) (uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint8_t* out_data);
    int (*read_data_word) (uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint16_t* out_data);
    int (*block_read) (uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, void* out_buffer, size_t buffer_size);
    int (*write_data_byte) (uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, uint8_t value);
    int (*write_data_word) (uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, uint16_t value);
    int (*block_write) (uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, void* in_buffer, size_t buffer_size);
} smbus_wrapper;

typedef struct
{
    /* Clock functions */
    bool (*prepare_clock_change) (uint32_t nMDDRChannel, uint32_t nFreqKHz);
    bool (*apply_clock_change) (uint32_t nMDDRChannel, uint32_t clk_type);
    bool (*clean_up_clock_change) (uint32_t nMDDRChannel);
} clock_wrapper;

typedef struct
{
    /* Util functions */
    bool (*wait_us) (uint32_t us_to_wait);
    int (*printf) (const char * fmt, va_list vargs);
} util_wrapper;

typedef struct
{
    /* dcvs functions */
    void (*read_bum_counter) (rs_type_e su_type, uint32_t su_id, rs_bum_cntr_t *bum_cnt);
} rs_dcvs_wrapper;

typedef struct
{
    /* dcvs functions */
    void (*read_ddr_bcqfull_counter)(mddr_bum_info_t *mddr_bum_info_ptr);
    void (*read_ddr_busy_counter)(mddr_bum_info_t *mddr_bum_info_ptr);
} ddr_dcvs_wrapper;

/* function table for XBL and RPM to share */
typedef struct
{
    /* Data */
    active_platform platform;
    uint8_t even_chan_insts[DDR_MAX_NUM_CHANS/2];
    uint8_t odd_chan_insts[DDR_MAX_NUM_CHANS/2];

    /* thermal api */
    void (*get_thermal_info) (ddr_thermal_info* thermal_info);
    void (*enable_thermal_mitigation) (uint8_t perf_percentage);
    void (*disable_thermal_mitigation) ();

    /* self refresh api */
    void (*enter_self_refresh_all) ();
    void (*exit_self_refresh_all) ();
    void (*auto_refresh_rate_adj)
    (mddr_dimm_refresh_rate_t adj_ref_dimm0, mddr_dimm_refresh_rate_t adj_ref_dimm1);

    /* voltage switch api */
    void (*auto_self_refresh_enable_all) (uint32_t idle_delay);
    void (*auto_self_refresh_disable_all) ();

    /* power collapse api */
    void (*auto_power_down_enable_all) (uint32_t idle_delay);
    void (*auto_power_down_disable_all) ();

    /* slot information api */
    void (*get_active_channels) (ddr_dimm_pop_map* map);

    /* EXTERNAL APIs */
    /* smbus */
    smbus_wrapper smbus;
    /* clock driver */
    clock_wrapper clock;
    /* utilities */
    util_wrapper util;
    /* ring switch dcvs wrapper */
    rs_dcvs_wrapper rsdcvs;
    /* ddr dcvs wrapper */
    ddr_dcvs_wrapper ddrdcvs;

    /* get ddr channel state */
    void (*get_ddr_state) (mddr_state_info_t *mddr_state_info_ptr);

} ddr_func_tbl;

/*===========================================================================
                                 DATA
===========================================================================*/

#endif
