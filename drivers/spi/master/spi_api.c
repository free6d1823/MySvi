/*==============================================================================
#  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
#  All rights reserved.
#  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
#  Copyright (c) 2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_api.c
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2016.02.18
 */

#include <asm/mach-qdf2400/spi/spi_core.h>
#include <asm/mach-qdf2400/spi/spi_defs.h>
#include <asm/mach-qdf2400/spi/spi_qup.h>
#include <std/stddef.h>

spi_status_t spi_open(spi_instance_t instance, SPI_HANDLE *spi_handle)
{
    static spi_hw_ctxt _ctxts[SPI_INSTANCE_MAX - SPI_INSTANCE_1];
    spi_hw_ctxt *h_ctxt;

    if((instance > spi_plat_get_num_cores()) || (spi_handle == NULL))
    {
        return SPI_ERROR_INVALID_PARAM;
    }

    h_ctxt = _ctxts + instance - SPI_INSTANCE_1;

    h_ctxt->hw.core_index = (uint8_t)instance;
    spi_plat_get_props(h_ctxt);
    h_ctxt->hw.base_addr = spi_plat_get_base_addr(h_ctxt);

    h_ctxt->hw.initialized = false;

    *spi_handle = h_ctxt;

    return SPI_SUCCESS;
}

spi_status_t spi_power_on(SPI_HANDLE spi_handle)
{
    spi_hw_ctxt *h_ctxt = (spi_hw_ctxt *)spi_handle;
    spi_status_t status = SPI_SUCCESS;

    if(spi_handle == NULL)
    {
        return SPI_ERROR_INVALID_PARAM;
    }

    if(spi_plat_gpio_enable(h_ctxt) == false)
    {
        return SPI_ERROR_GPIO_ENABLE_FAIL;
    }

    status = spi_core_sw_reset(&(h_ctxt->hw));
    SPI_ERR_CHECK(status);

    spi_core_init(h_ctxt);
    return SPI_SUCCESS;
}

spi_status_t spi_power_off(SPI_HANDLE spi_handle)
{
    spi_hw_ctxt *h_ctxt = (spi_hw_ctxt *)spi_handle;

    if(spi_handle == NULL)
    {
        return SPI_ERROR_INVALID_PARAM;
    }

    if(spi_plat_clock_disable(h_ctxt) == false)
    {
        return SPI_ERROR_CLK_DISABLE_FAIL;
    }
    if(spi_plat_gpio_disable(h_ctxt) == false)
    {
        return SPI_ERROR_GPIO_DISABLE_FAIL;
    }

    spi_core_deinit(h_ctxt);
    return SPI_SUCCESS;
}

spi_status_t spi_close(SPI_HANDLE spi_handle)
{
    spi_hw_ctxt *h_ctxt;
    if(spi_handle == NULL)
    {
        return SPI_ERROR_INVALID_PARAM;
    }

    h_ctxt = (spi_hw_ctxt *)spi_handle;

    //Close was called before properly powering off. Do it for the client.
    if(h_ctxt->hw.initialized)
    {
        (void)spi_power_off(spi_handle);
    }

    spi_handle = NULL; //so a client cannot mistakenly reuse a stale handle
    return SPI_SUCCESS;
}

spi_status_t spi_configure(SPI_HANDLE          spi_handle,
                           spi_config_t        *config,
                           bool             ignore_clocks)
{
    spi_status_t status = SPI_SUCCESS;

    spi_hw_ctxt   *h_ctxt;
    spi_hw_info   *hw;

    if((spi_handle == NULL) || (config == NULL) ||
            ((config->bits_per_word < 4) || (config->bits_per_word > 32)) ||
            (config->loopback_mode && config->hs_mode) ||
            (config->slave_index > 3))
    {
        return SPI_ERROR_INVALID_PARAM;
    }

    h_ctxt = (spi_hw_ctxt *)spi_handle;
    h_ctxt->config = config;

    if(h_ctxt->hw.initialized == false)
    {
        return SPI_ERROR_NOT_INITIALIZED;
    }
    hw     = &(h_ctxt->hw);

    status = spi_core_sw_reset(&(h_ctxt->hw));
    SPI_ERR_CHECK(status);

    // Set SPI frequency
#if 0
    /* Todo: Joe needs to fix the clock issue.
     * Currently the clocks are already enabled in XBL. */

    h_ctxt->real_freq = spi_plat_clock_set_freq(h_ctxt,
                        config->max_slave_freq_hz,
                        config->min_slave_freq_hz);
    if((!ignore_clocks) && (h_ctxt->real_freq == 0))
    {
        return SPI_ERROR_CLK_SET_FREQ_FAIL;
    }
#else
    h_ctxt->real_freq = 20*1000*1000; /* Need to update Loader and this to 25MHz */
#endif
    spi_core_configure(h_ctxt);

    return SPI_SUCCESS;
}

spi_status_t spi_full_duplex(SPI_HANDLE          spi_handle,
                             spi_transfer_t     *tx_info,
                             spi_transfer_t     *rx_info)
{
    spi_status_t status = SPI_SUCCESS;

    spi_hw_ctxt   *h_ctxt;
    transfer_ctxt *t_ctxt;
    spi_hw_info   *hw;

    if( spi_handle == NULL || ((tx_info == NULL) && (rx_info == NULL)) )
    {
        return SPI_ERROR_INVALID_PARAM;
    }
    h_ctxt = (spi_hw_ctxt *)spi_handle;
    hw     = &(h_ctxt->hw);
    t_ctxt = &(h_ctxt->t_ctxt);
    if(h_ctxt->config == NULL)
    {
        return SPI_ERROR_NOT_CONFIGURED;
    }

    t_ctxt->rx_done      = (rx_info == NULL || rx_info->buf_len == 0);
    t_ctxt->tx_done      = (tx_info == NULL || tx_info->buf_len == 0);
    t_ctxt->rx_info      = rx_info;
    t_ctxt->tx_info      = tx_info;
    t_ctxt->rx_bytes     = 0;
    t_ctxt->tx_bytes     = 0;

    spi_core_runtime_configure(h_ctxt);

    status = spi_core_set_state(hw, SPI_CORE_STATE_RUN);
    SPI_ERR_CHECK(status);

    status = spi_core_wait_for_completion(h_ctxt);
    SPI_ERR_CHECK(status);

    return SPI_SUCCESS;
}

