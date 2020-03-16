/*==============================================================================
# Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
# Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_defs.h
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2016.02.18
 *  @brief  Pulled from //components/rel/core.io/1.0/v1/
 */

#ifndef __SPI_DEFS_H__
#define __SPI_DEFS_H__

#include <asm/mach-qdf2400/hal/HALspiHWIO.h>
#include <bits/alltypes.h>
#include <stdbool.h>

#define SPI_SUCCESS(x)  (x == SPI_SUCCESS)
#define SPI_ERROR(x)    (x != SPI_SUCCESS)

typedef void* SPI_HANDLE;

typedef enum
{
    SPI_INSTANCE_1 = 1,
    SPI_INSTANCE_2,
    SPI_INSTANCE_3,
    SPI_INSTANCE_4,
    SPI_INSTANCE_MAX,
} spi_instance_t;

/* Function status codes. */
typedef enum
{
    SPI_SUCCESS  = 0x0000,
    SPI_ERROR,
    SPI_ERROR_INVALID_PARAM,
    SPI_ERROR_MEM_ALLOC,
    SPI_ERROR_TRANSFER_TIMEOUT,
    SPI_ERROR_CLK_ENABLE_FAIL,
    SPI_ERROR_GPIO_ENABLE_FAIL,
    SPI_ERROR_CLK_DISABLE_FAIL,
    SPI_ERROR_GPIO_DISABLE_FAIL,
    SPI_ERROR_CLK_SET_FREQ_FAIL,
    SPI_ERROR_QUP_STATE_INVALID,
    SPI_ERROR_INTERRUPT_REGISTER,
    SPI_ERROR_NOT_INITIALIZED,
    SPI_ERROR_CORE_ERROR,
    SPI_ERROR_NOT_CONFIGURED
    /**< SW code errors. */
} spi_status_t;

typedef enum
{
    SPI_CLK_NORMAL=0,      // Turns off SPI CLK during idle state
    SPI_CLK_ALWAYS_ON,     // Runs SPI CLK during idle state
    SPI_CLK_INVALID
} spi_clk_mode_t;

typedef enum
{
    SPI_CLK_IDLE_LOW=0,    // CLK signal is low  when idle
    SPI_CLK_IDLE_HIGH,     // CLK signal is high when idle
    SPI_CLK_IDLE_INVALID
} spi_clk_polarity_t;

typedef enum SpiShiftModeType
{
    SPI_INPUT_FIRST_MODE=0,// Input  bit is shifted in first
    SPI_OUTPUT_FIRST_MODE, // Output bit is shifted in first
    SPI_SHIFT_INVALID
} spi_shift_mode_t;

typedef enum
{
    SPI_CS_ACTIVE_LOW=0,   // During run state CS line is held low
    SPI_CS_ACTIVE_HIGH,    // During run state CS line is held high
    SPI_CS_ACTIVE_INVALID
} spi_cs_polarity_t;

typedef enum
{
    SPI_CS_DEASSERT,       // CS is deasserted in-between transactions
    SPI_CS_KEEP_ASSERTED,  // CS is asserted as long as the core is in Run state
    SPI_CS_MODE_INVALID = 0x7FFFFFFF
} spi_cs_mode_t;

typedef struct
{
    // Add note to timing diagram here.
    spi_clk_polarity_t clk_polarity;
    spi_shift_mode_t   shift_mode;
    spi_cs_polarity_t  cs_polarity;
    spi_cs_mode_t      cs_mode;
    spi_clk_mode_t     clk_mode;
    // SPI bits per word, any value from 3 to 31
    uint8_t              bits_per_word;

    // Slave index, beginning at 0, if mulitple SPI devices are
    //   connected to the same master
    uint8_t              slave_index;

    // Host will set the SPI clk frequency to max_slave_freq_hz, or to the
    //   nearest supported frequency greater than min_slave_freq_hz
    uint32_t  min_slave_freq_hz;
    uint32_t  max_slave_freq_hz;
    // The minimum delay between two word(N-bit) transfers
    uint32_t  deassertion_time_ns;

    bool loopback_mode;
    bool hs_mode;
} spi_config_t;

typedef struct
{
    uint32_t  *buf_addr;   // This MUST be 32-bit word aligned
    uint16_t buf_len;    // Buffer size in bytes (used for sanity checking)
    uint16_t word_count; // Number of words to read/write
} spi_transfer_t;

/****************************************************************/

#define SPI_ERR_CHECK(s) do {if(SPI_ERROR(s)) return s; } while(0)

typedef enum
{
    SPI_CORE_STATE_RESET = 0,
    SPI_CORE_STATE_RUN   = 1,
    SPI_CORE_STATE_PAUSE = 3,
} spi_core_state;

typedef struct
{
    uint8_t       *base_addr;
    spi_instance_t core_index;
    bool        initialized;
    spi_core_state state;
} spi_hw_info;

typedef struct
{
    bool         rx_done;
    bool         tx_done;
    uint32_t        rx_bytes;
    uint32_t        tx_bytes;
    spi_transfer_t *rx_info;
    spi_transfer_t *tx_info;
    uint32_t        status;
} transfer_ctxt;

typedef struct
{
    uint32_t pin;
    uint32_t func;
} gpiocfg;

typedef struct
{
    uint8_t         *spi_base_addr;
    uint32_t         irq_num;

    gpiocfg          gpio_mosi;
    gpiocfg          gpio_miso;
    gpiocfg          gpio_cs;
    gpiocfg          gpio_clk;

    void            *h_clock;
    void            *apps_id;
    void            *i2cspi_id;
} spi_properties;

typedef struct
{
    spi_hw_info    hw;
    transfer_ctxt  t_ctxt;
    spi_config_t  *config;
    uint32_t       real_freq;
    spi_properties props;
} spi_hw_ctxt;

#endif
