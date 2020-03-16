/*==============================================================================
#      Copyright (c) 2016-2017 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_cfg.h
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2016.02.19
 *  @brief  Config file for SPI Master platform-specifics
 *
 *  Currently, all important defines are the same for Hawker and Amberwing. If
 *    any platforms require different settings, we can move this file into a
 *    platform-specific subfolder and include it conditionally then
 */
#ifndef SPI_CFG_H
#define SPI_CFG_H
#include <asm/mach-qdf2400/hal/msmhwiobase.h>
#include "spi_clk_cfg.h"

#define BAD_SPI_DEVICE          0xDEADDEADull
#define SPI_CFG_NUM_CORES       0x4

/*
 * On some uses of SPI (ex:AVSBus) CS will be unassigned, in such
 * scenarios we need to set the GPIO num to below
 */
#define SPI_UNASSIGNED_CS       0xFFFFFFFF

#define SPI_CFG_BASE_ADDR(dev) (dev == SPI_INSTANCE_1 ? I0_BLSP_QUP0_REG_BASE_PHYS:\
                                dev == SPI_INSTANCE_2 ? I0_BLSP_QUP1_REG_BASE_PHYS:\
                                dev == SPI_INSTANCE_3 ? I3_BLSP_QUP0_REG_BASE_PHYS:\
                                dev == SPI_INSTANCE_4 ? I3_BLSP_QUP1_REG_BASE_PHYS:\
                                BAD_SPI_DEVICE)

#define SPI_CFG_IRQ_NUM(dev)   (dev == SPI_INSTANCE_1 ? 104 : \
                                dev == SPI_INSTANCE_2 ? 105 : \
                                dev == SPI_INSTANCE_3 ? 130 : \
                                dev == SPI_INSTANCE_4 ? 131 : \
                                BAD_SPI_DEVICE)

#define SPI_CFG_MISO_PIN(dev)  (dev == SPI_INSTANCE_1 ? 40 : \
                                dev == SPI_INSTANCE_2 ? 44 : \
                                dev == SPI_INSTANCE_3 ? 32 : \
                                dev == SPI_INSTANCE_4 ? 36 : \
                                BAD_SPI_DEVICE)
#define SPI_CFG_MOSI_PIN(dev)  (dev == SPI_INSTANCE_1 ? 41 : \
                                dev == SPI_INSTANCE_2 ? 45 : \
                                dev == SPI_INSTANCE_3 ? 33 : \
                                dev == SPI_INSTANCE_4 ? 37 : \
                                BAD_SPI_DEVICE)
#define SPI_CFG_CLK_PIN(dev)   (dev == SPI_INSTANCE_1 ? 42 : \
                                dev == SPI_INSTANCE_2 ? 46 : \
                                dev == SPI_INSTANCE_3 ? 34 : \
                                dev == SPI_INSTANCE_4 ? 38 : \
                                BAD_SPI_DEVICE)
#define SPI_CFG_CS_PIN(dev)    (dev == SPI_INSTANCE_1 ? 43 : \
                                dev == SPI_INSTANCE_2 ? SPI_UNASSIGNED_CS : /*Unused*/  \
                                dev == SPI_INSTANCE_3 ? 89 : \
                                dev == SPI_INSTANCE_4 ? 39 : \
                                BAD_SPI_DEVICE)

#define SPI_CFG_CS_FUNC(dev)   (dev == SPI_INSTANCE_1 ? 1 : \
                                dev == SPI_INSTANCE_2 ? 1 : \
                                dev == SPI_INSTANCE_3 ? 1 : \
                                dev == SPI_INSTANCE_4 ? 1 : \
                                BAD_SPI_DEVICE)
#define SPI_CFG_CLK_FUNC(dev)  (dev == SPI_INSTANCE_1 ? 1 : \
                                dev == SPI_INSTANCE_2 ? 1 : \
                                dev == SPI_INSTANCE_3 ? 2 : \
                                dev == SPI_INSTANCE_4 ? 1 : \
                                BAD_SPI_DEVICE)
#define SPI_CFG_MOSI_FUNC(dev) (dev == SPI_INSTANCE_1 ? 1 : \
                                dev == SPI_INSTANCE_2 ? 1 : \
                                dev == SPI_INSTANCE_3 ? 2 : \
                                dev == SPI_INSTANCE_4 ? 1 : \
                                BAD_SPI_DEVICE)
#define SPI_CFG_MISO_FUNC(dev) (dev == SPI_INSTANCE_1 ? 1 : \
                                dev == SPI_INSTANCE_2 ? 1 : \
                                dev == SPI_INSTANCE_3 ? 2 : \
                                dev == SPI_INSTANCE_4 ? 1 : \
                                BAD_SPI_DEVICE)

#define SPI_CFG_GPIO_DRV_STR    GPIO_DRV_16_MA

#endif /* SPI_CFG_H */

