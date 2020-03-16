#ifndef SPI_NOR_H
#define SPI_NOR_H

/**********************************************************************
 * SpiNor.h
 *
 * Public interface declaration for the Spi-Nor Library
 *
 * Copyright (c) 2008-2010,2012, 2015 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 **********************************************************************/

/** Flash client device data */
typedef struct
{
  UINT32 BlockCount;                   /**< Number of total blocks in device */
  UINT32 PagesPerBlock;                /**< Number of pages in a block */
  UINT32 PageSizeBytes;                /**< Page size in bytes */
} SPI_NOR_DEVICE_INFO;

/**
 * Gets flash device information. Flash driver assumes that the memory for returned
 * information is allocated by the driver client. It is
 * client's responsibility to typecast the void* parameter
 * to the appropriate type. \n
 * \n
 *  Info Type                  \t  -  Data Structure Associated\n \n
 *
 * @param DeviceInfo [OUT]
 *   Pointer to the client's flash device info data.
 *
 * @param BusNumber [IN]
 *   Spi Port to talk to.
 *
 * @return EFI_STATUS [OUT]
 *   Result of the operation.
 *
 */
EFI_STATUS SpiNorGetDeviceInfo (SPI_NOR_DEVICE_INFO *DeviceInfo, UINT32 BusNumber);

/**
 * Erases given flash blocks
 *
 * @param StartBlock [IN]
 *   A starting block for a number of blocks to erase.
 *
 * @param BlockCount [IN]
 *   Number of blocks to erase
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EFI_STATUS SpiNorEraseBlocks(UINTN StartBlock, UINTN BlockCount);

/**
 * Flash write page API. This API allows writing single/multiple pages
 * within a block.
 *
 * @Buffer [IN]
 *   Data buffer for flash write operation.
 */

/**
 * For optimum performance, pass DMA friendly (physically contiguous,
 * non-cached) buffer. If the passed memory is not DMA friendly,
 * the DAL will allocate DMA friendly memory and may result in
 * low performance. @n
*/

/**
 *
 * @param StartPage [IN]
 *   Logical start page to begin write operation of data
 *
 * @param PageCount [IN]
 *   Number of pages to write data.
 *
 * @return EFI_STATUS [OUT]
 *   Result of the operation.
 *
 * @note
 *   IMPORTANT: Ensure that the given start page and page count range
 *   falls in one block. It is NOT allowed to write pages that span
 *   across multiple blocks in a single API call.
 *
 */
EFI_STATUS SpiNorWritePages(VOID *Buffer,
                            UINTN StartPage,
                            UINTN PageCount);

/**
 * Flash read page API. This API allows to read single/multiple pages
 * within a block.
 *
 * @Buffer [OUT]
 *   Data buffer for a flash read operation.
 */

/**
 * For optimum performance, pass DMA friendly (physically contiguous,
 * non-cached) buffer. If the passed memory is not DMA friendly, then
 * the DAL will allocate DMA friendly memory and may result in
 * low performance.
*/

/**
 *
 * @param StartPage [IN]
 *   Logical start page to begin read operation of data
 *
 * @param PageCount [IN]
 *   Number of pages to read data.
 *
 * @return EFI_STATUS [OUT]
 *   Result of the operation.
 */
EFI_STATUS SpiNorReadPages (VOID *Buffer,
                            UINTN StartPage,
                            UINTN PageCount);

/**
 *
 * @return int [OUT]
 *   Result of the operation.
 */
typedef EFI_STATUS (*CONVERT_VIRTUAL_FUNCTION)(
  void **Address
  );

EFI_STATUS SpiNorConvertVirtual(CONVERT_VIRTUAL_FUNCTION convert);

#endif /* #ifndef SPI_NOR_H */
