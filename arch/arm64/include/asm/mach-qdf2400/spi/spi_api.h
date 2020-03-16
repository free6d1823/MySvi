/*==============================================================================
# Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
# Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_api.h
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2016.02.18
 *  @brief  Adapted from //components/rel/core.io/1.0/v1/
 */

#ifndef SPI_API_H
#define SPI_API_H

#include <bits/alltypes.h>
#include "spi_core.h"
#include "spi_defs.h"
#include "spi_clk_cfg.h"
#include "spi_cfg.h"
#include "spi_qup.h"


/*==============================================================================
                              FUNCTION DEFINITIONS
==============================================================================*/
/**
 * @brief Opens an instance of the SPI Master interface
 *
 * @parameter[in]  instance   - The instance to open. See spi_cfg.h for QUP map
 * @parameter[out] spi_handle - The handle for spi_open to set up
 *
 * @return - SPI_SUCCESS - spi_handle should be ready to go
 *           SPI_ERROR_INVALID_PARAM - One of the parameters is invalid
 **/
spi_status_t spi_open(spi_instance_t instance, SPI_HANDLE *spi_handle);
/**
 * @brief Coses a handle to the SPI Master interface
 *
 * Note: This will set the handle to NULL
 * Note: This will call spi_power_off if the caller failed to do so
 *
 * @parameter[out] spi_handle - The handle for spi_close to destroy
 *
 * @return - SPI_SUCCESS - spi_handle was successfully destroyed
 *           SPI_ERROR_INVALID_PARAM - spi_handle is null
 **/
spi_status_t spi_close(SPI_HANDLE spi_handle);

/**
 * @brief Turns on all clocks and GPIOs, initializes the core
 *
 * @parameter[in]  spi_handle - A handle which was given from spi_open
 *
 * @return - SPI_SUCCESS - SPI Master core was powered on successfully
 *         - SPI_ERROR_INVALID_PARAM - spi_handle has not been initialized
 *         - SPI_ERROR_CLK_ENABLE_FAIL - Clock enabling failed
 *         - SPI_ERROR_GPIO_ENABLE_FAIL - GPIO configuration failed
 *         - SPI_ERROR_QUP_STATE_INVALID - Unknown error
 **/
spi_status_t spi_power_on(SPI_HANDLE spi_handle);
/**
 * @brief Turns off all clocks, deinitializes the core
 *
 * @parameter[in]  spi_handle - A handle which was given from spi_open
 *
 * @return - SPI_SUCCESS - SPI Master core was powered off successfully
 *         - SPI_ERROR_INVALID_PARAM - spi_handle has not been initialized
 *         - SPI_ERROR_CLK_DISABLE_FAIL - Clock disabling failed
 *         - SPI_ERROR_GPIO_DISABLE_FAIL - GPIO configuration failed
 *         - SPI_ERROR_QUP_STATE_INVALID - Unknown error
 **/
spi_status_t spi_power_off(SPI_HANDLE spi_handle);

/**
 * @brief Configure the core in preparation for SPI transactions
 *
 * @parameter[in] spi_handle - A handle which has been opened and powered on
 * @parameter[in] config     - Configuration parameters for the SPI transaction
 * @parameter[in] ignore_clocks - Some platforms don't support clocks
 *
 * @return - SPI_SUCCESS - The transfer completed successfully
 *         - SPI_ERROR_INVALID_PARAM - One of the given parameters is invalid
 *         - SPI_ERROR_NOT_INITIALIZED - spi_handle has not been initialized
 *         - SPI_ERROR_QUP_STATE_INVALID - Unknown error
 *         - SPI_ERROR_CORE_ERROR - Unknown error
 **/
spi_status_t spi_configure(SPI_HANDLE          spi_handle,
                           spi_config_t        *config,
                           bool             ignore_clocks);
/**
 * @brief Perform full duplex, duplex, or simplex transfer
 *        For a write only transfer, set rx_info to NULL
 *        For a read only transfer,  set tx_info to NULL
 * A full duplex transfer can be asymmetric (tx and rx lengths can be unequal)
 *
 * @parameter[in] spi_handle - A handle which has been opened and powered on
 * @parameter[in] config     - Configuration parameters for the SPI transaction
 * @parameter[in] tx_info    - Pointer to the transmit buffer descriptor
 * @parameter[inout] rx_info - Pointer to the receive  buffer descriptor
 *
 * @return - SPI_SUCCESS - The transfer completed successfully
 *         - SPI_ERROR_INVALID_PARAM - One of the given parameters is invalid
 *         - SPI_ERROR_NOT_CONFIGURED - spi_configure has not been run yet
 *         - SPI_ERROR_QUP_STATE_INVALID - Unknown error
 *         - SPI_ERROR_TRANSFER_TIMEOUT - The SPI transfer timed out
 *         - SPI_ERROR_CORE_ERROR - Unknown error
 **/
spi_status_t spi_full_duplex(SPI_HANDLE          spi_handle,
                             spi_transfer_t     *tx_info,
                             spi_transfer_t     *rx_info);

#endif /* SPI_API_H */
