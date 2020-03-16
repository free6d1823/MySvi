#ifndef SPI_SLAVE_API_H
#define SPI_SLAVE_API_H

#include <bits/alltypes.h>

typedef enum
{
    SPI_SLAVE_SUCCESS,
    SPI_SLAVE_ERR_NOT_SUPPORTED,
    SPI_SLAVE_ERR_SANITY
}spi_slave_status;

typedef enum
{
    // Supported by Hawker(SPI_SLAVE core), and 8996v3 (QUPv2.6)
    SPI_SLAVE_DMA_MODE,
    // Supported by 8996v3 (QUPv2.6)
    SPI_SLAVE_INTERRUPT_MODE
}spi_slave_dma_mode;



typedef struct
{
    // Does this use DMA mode, or interrupt-based mode
    uint32_t dmaMode;
}spi_slave_init_params;

#endif /* SPI_SLAVE_API_H */

