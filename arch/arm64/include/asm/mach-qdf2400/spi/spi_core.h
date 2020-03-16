/*==============================================================================
#      Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_core.h
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2016.02.19
 *  @brief  Functions for dealing with internal core functionality
 */

#ifndef SPI_CORE_H
#define SPI_CORE_H
#include "spi_defs.h"

/**
 * @brief Resets the core via the SW Reset command
 * @parameter[in]  hw - Hardware Info struct set up in spi_open
 * @return - SPI_SUCCESS - The core has successfully been reset
 *           SPI_ERROR_QUP_STATE_INVALID - Unknown error
 **/
spi_status_t spi_core_sw_reset(spi_hw_info *hw);
/**
 * @brief Sets the QUP_STATE register to new_state
 * @parameter[in]  hw - Hardware Info struct set up in spi_open
 * @parameter[in]  new_state - The state to set QUP_STATE to
 * @return - SPI_SUCCESS - The core has successfully transitioned state
 *           SPI_ERROR_QUP_STATE_INVALID - Unknown error
 **/
spi_status_t spi_core_set_state(spi_hw_info *hw, spi_core_state new_state);

/**
 * @brief Performs basic initialization of the QUP Core for SPI mode
 * @parameter[in]  hw - Hardware Info struct set up in spi_open
 **/
void         spi_core_init(spi_hw_ctxt *h_ctxt);
/**
 * @brief Deinitializes the QUP core
 * @parameter[in]  hw - Hardware Info struct set up in spi_open
 **/
void         spi_core_deinit(spi_hw_ctxt *h_ctxt);

/**
 * @brief Configure the core with parameters that can be used
 *            across multiple transactions
 * @parameter[in]  h_ctxt - Core context for the SPI driver
 **/
void         spi_core_configure(spi_hw_ctxt *h_ctxt);
/**
 * @brief Configure the core with parameters that need to be set
 *            for each transaction
 * @parameter[in]  h_ctxt - Core context for the SPI driver
 **/
void         spi_core_runtime_configure(spi_hw_ctxt *h_ctxt);
/**
 * @brief After configuration, spin and wait for the transaction to finish,
 *            supplying more data as needed
 * @parameter[in]  h_ctxt - Core context for the SPI driver
 * @return - SPI_SUCCESS - The transaction has completed successfully
 *           SPI_ERROR_TRANSFER_TIMEOUT  -
 *           SPI_ERROR_CORE_ERROR - Internal core error.
 *                                  See h_ctxt->t_ctxt->status
 *           SPI_ERROR_QUP_STATE_INVALID - Unknown error
 **/
spi_status_t spi_core_wait_for_completion(spi_hw_ctxt *h_ctxt);

#endif /* SPI_CORE_H */
