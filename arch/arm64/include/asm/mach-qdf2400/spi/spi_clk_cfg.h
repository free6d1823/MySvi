/*==============================================================================
#      Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_clk_cfg.h
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @brief  Config file for SPI Master Clocks
 */
#ifndef SPI_CLK_CFG_H
#define SPI_CLK_CFG_H

#define SPI_CFG_I2CSPI_CLK     ("pcc_pfab_i2cspi_fclk")

#define SPI_CFG_APPS_CLK(dev)  (dev == SPI_INSTANCE_1 ? "pcc_blsp0_qup0_spi_apps_clk":\
                                dev == SPI_INSTANCE_2 ? "pcc_blsp0_qup1_spi_apps_clk":\
                                dev == SPI_INSTANCE_3 ? "pcc_blsp3_qup0_spi_apps_clk":\
                                dev == SPI_INSTANCE_4 ? "pcc_blsp3_qup1_spi_apps_clk":\
                                "bad spi device")

#endif /* SPI_CLK_CFG_H */

