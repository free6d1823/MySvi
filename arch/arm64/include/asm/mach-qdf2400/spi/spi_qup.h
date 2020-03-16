/*==============================================================================
#      Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_plat.h
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2016.02.18
 *  @brief  Platform-specific info, properties, and functions
 *  Adapted from //components/rel/core.io/1.0/v1/
 */

#ifndef __SPI_PLAT_H__
#define __SPI_PLAT_H__

#include <stdbool.h>
#include "spi_defs.h"

/**
 * @brief Enable the clocks for a given core
 * @parameter[in] h - Hardware Context that has been populated by get_props
 * @return - TRUE  - Clocks enabled successfully
 *           FALSE - Clocks enablement failed
 **/
bool spi_plat_clock_enable(spi_hw_ctxt *h);
/**
 * @brief Disable the clocks for a given core
 * @parameter[in] h - Hardware Context that has been populated by get_props
 * @return - TRUE  - Clocks disabled successfully
 *           FALSE - Clocks disabling failed
 **/
bool spi_plat_clock_disable(spi_hw_ctxt *h);
/**
 * @brief Set the clock frequency for the core
 *
 * Will get as close as possible to the max freq without going over
 * @parameter[in] h - Hardware Context that has been populated by get_props
 * @parameter[in] max_freq_in_hz - Maximum frequency (hz)
 * @parameter[in] min_freq_in_hz - Minimum frequency (hz)
 * @return - 0      - Clock setup failed
 *           uint32_t - Actual freq in hz
 **/
uint32_t spi_plat_clock_set_freq(spi_hw_ctxt *h,
                               uint32_t max_freq_in_hz,
                               uint32_t min_freq_in_hz);

/**
 * @brief Configure all GPIOs for a core
 * @parameter[in] h - Hardware Context that has been populated by get_props
 * @return - TRUE  - GPIOs configured successfully
 *           FALSE - GPIO configuration failed
 **/
bool spi_plat_gpio_enable(spi_hw_ctxt *h);
/**
 * @brief Configure all GPIOs for a core
 * @parameter[in] h - Hardware Context that has been populated by get_props
 * @return - TRUE  - GPIOs deconfigured successfully
 *           FALSE - GPIO configuration failed
 **/
bool spi_plat_gpio_disable(spi_hw_ctxt *h);

/**
 * @brief Get the number of cores in the system
 * @return - The number of SPI-Capable QUP cores in the system
 **/
uint32_t  spi_plat_get_num_cores(void);
/**
 * @brief Get the base address for the spi core
 * @parameter[in] h - Hardware Context that has been populated by get_props
 * @return - The pointer to the base of the spi core
 **/
uint8_t  *spi_plat_get_base_addr(spi_hw_ctxt *h);
/**
 * @brief Get the base address for the spi core
 * @parameter[in] h - Hardware Context that has been populated by get_props
 * @return - The pointer to the base of the spi core
 **/
uint32_t  spi_plat_get_spi_irq(spi_hw_ctxt *h);
/**
 * @brief Populate the properties handle inside of h
 * @parameter[in] h - Hardware Context to be populated
 * @return - TRUE  - Properties have been populated successfully
 *           FALSE - Property population failed
 **/
bool spi_plat_get_props(spi_hw_ctxt *h);

#endif //__SPI_PLAT_H__

