/*==============================================================================
#      Copyright (c) 2016-2017 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_plat.c
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2016.02.18
 */

#include <asm/mach/spi/spi_defs.h>
#include <asm/mach/spi/spi_qup.h>
#include <asm/mach/spi/spi_cfg.h>

bool spi_plat_get_props(spi_hw_ctxt *h)
{
    h->props.spi_base_addr = (uint8_t *) SPI_CFG_BASE_ADDR(h->hw.core_index);
    if(BAD_SPI_DEVICE == (uint64_t) h->props.spi_base_addr)
    {
        return false;
    }
    h->props.irq_num       = SPI_CFG_IRQ_NUM(h->hw.core_index);

    h->props.gpio_cs.pin    = SPI_CFG_CS_PIN(h->hw.core_index);
    h->props.gpio_clk.pin   = SPI_CFG_CLK_PIN(h->hw.core_index);
    h->props.gpio_mosi.pin  = SPI_CFG_MOSI_PIN(h->hw.core_index);
    h->props.gpio_miso.pin  = SPI_CFG_MISO_PIN(h->hw.core_index);

    h->props.gpio_cs.func   = SPI_CFG_CS_FUNC(h->hw.core_index);
    h->props.gpio_clk.func  = SPI_CFG_CLK_FUNC(h->hw.core_index);
    h->props.gpio_mosi.func = SPI_CFG_MOSI_FUNC(h->hw.core_index);
    h->props.gpio_miso.func = SPI_CFG_MISO_FUNC(h->hw.core_index);

    return true;
}

uint32_t spi_plat_get_num_cores(void)
{
    return SPI_CFG_NUM_CORES;
}

uint8_t *spi_plat_get_base_addr(spi_hw_ctxt *h)
{
    return h->props.spi_base_addr;
}

bool spi_plat_clock_enable(spi_hw_ctxt *h)
{
    bool res = true;
    return res;
}
bool spi_plat_clock_disable(spi_hw_ctxt *h)
{
//    bool res = true;
    return false;
}
uint32_t spi_plat_clock_set_freq(spi_hw_ctxt *h,
                                uint32_t max_freq_in_hz, uint32_t min_freq_in_hz)
{
      return 0;
}

bool spi_plat_gpio_enable(spi_hw_ctxt *h)
{
    GPIO_SET_FUNC(h->props.gpio_mosi.pin, h->props.gpio_mosi.func);
    GPIO_SET_STR( h->props.gpio_mosi.pin, SPI_CFG_GPIO_DRV_STR);

    GPIO_SET_FUNC(h->props.gpio_miso.pin, h->props.gpio_miso.func);
    GPIO_SET_STR( h->props.gpio_miso.pin, SPI_CFG_GPIO_DRV_STR);

    GPIO_SET_FUNC(h->props.gpio_clk.pin,  h->props.gpio_clk.func);
    GPIO_SET_STR( h->props.gpio_clk.pin,  SPI_CFG_GPIO_DRV_STR);

    if (h->props.gpio_cs.pin != SPI_UNASSIGNED_CS) {
        GPIO_SET_FUNC(h->props.gpio_cs.pin,   h->props.gpio_cs.func);
        GPIO_SET_STR( h->props.gpio_cs.pin,   SPI_CFG_GPIO_DRV_STR);
    }
    return true;
}

bool spi_plat_gpio_disable(spi_hw_ctxt *h)
{
    return true;
}

uint32_t spi_plat_get_spi_irq(spi_hw_ctxt *h)
{
    return h->props.irq_num;
}

