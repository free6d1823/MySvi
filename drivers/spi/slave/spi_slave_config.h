/** @file   spi_slave_config.h
 *  @brief  Configuration data for the SPI Slave driver
 *  */
#ifndef SPI_SLAVE_CONFIG_H
#define SPI_SLAVE_CONFIG_H

#include "spi_slave_hwio.h"

/*---------------------------Defines------------------------------------------*/
#define SPI_SLAVE_SANITY_VALUE   0xDEADBEEF

#define SPI_SLAVE_IRQ_ENABLED    0
#define SPI_SLAVE_CHIP_IRQ_ID    124

#define SPI_SLAVE_GPIO_CFG_SCK   0x30018671
#define SPI_SLAVE_GPIO_CFG_MOSI  0x30018681
#define SPI_SLAVE_GPIO_CFG_MISO  0x3001c691
#define SPI_SLAVE_GPIO_CFG_SS    0x300186a1
#define SPI_SLAVE_GPIO_COUNT     4

#define SPI_SLAVE_CHIP_BASE_ADDR 0xFF7B400000ull
//TODO This might need to be changed based on new memory map
#define SPI_SLAVE_EXT_BASE_ADDR  0xFF70000000ull

#define SPI_SLAVE_TRNS_LEN       0xFFFF0000

#define SPI_SLAVE_CONFIG ((0x1 << HWIO_SPI_SLAVE_CONFIG_HOST_CTRL_SHFT)    |\
                          (0x4 << HWIO_SPI_SLAVE_CONFIG_N_DUMMY_SHIFT)     |\
                          (0x1 << HWIO_SPI_SLAVE_CONFIG_SEQMOD_SHFT)       |\
                          (0x1 << HWIO_SPI_SLAVE_CONFIG_ADDR_BYTE_LEN_SHFT) )

#endif /* SPI_SLAVE_CONFIG_H */
