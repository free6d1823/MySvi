/** @file

Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

**/
#ifndef _PCIE_I2C_IO_H_
#define _PCIE_I2C_IO_H_

//#include <Protocol/I2cMaster.h>
#include <target/uefi_wrapper.h>
#include <target/i2c.h>

#define MAX_PCIE_I2C_OPERATIONS   2

///
/// I2C device operation
///
/// The EFI_I2C_OPERATION describes a subset of an I2C transaction in which
/// the I2C controller is either sending or receiving bytes from the bus.
/// Some transactions will consist of a single operation while others will
/// be two or more.
///
/// Note: Some I2C controllers do not support read or write ping (address
/// only) operation and will return EFI_UNSUPPORTED status when these
/// operations are requested.
///
/// Note: I2C controllers which do not support complex transactions requiring
/// multiple repeated start bits return EFI_UNSUPPORTED without processing
/// any of the transaction.
///
typedef struct {
  ///
  /// Flags to qualify the I2C operation.
  ///
  UINT32 Flags;

  ///
  /// Number of bytes to send to or receive from the I2C device.  A ping
  /// (address only byte/bytes)  is indicated by setting the LengthInBytes
  /// to zero.
  ///
  UINT32 LengthInBytes;

  ///
  /// Pointer to a buffer containing the data to send or to receive from
  /// the I2C device.  The Buffer must be at least LengthInBytes in size.
  ///
  UINT8 *Buffer;
} EFI_I2C_OPERATION;

typedef struct {
  UINTN OperationCount;
  EFI_I2C_OPERATION Operation[MAX_PCIE_I2C_OPERATIONS];
} EFI_I2C_REQUEST_PACKET;

EFI_STATUS PcieI2cIoInitialize(void);
EFI_STATUS PcieI2cIoDeinitialize(void);
EFI_STATUS PcieI2cIoRequestLock(void);
EFI_STATUS PcieI2cIoReleaseLock(void);
EFI_STATUS PcieI2cIoRequest(UINTN Address, EFI_I2C_REQUEST_PACKET* Request);
EFI_STATUS PcieI2cIoWriteRead(UINTN Address,
  UINT8* WriteBuffer,
  UINTN WriteLength,
  UINT8* ReadBuffer,
  UINTN ReadLength);
EFI_STATUS PcieI2cIoWrite(UINTN Address,
  UINT8* Buffer,
  UINTN Length);
EFI_STATUS PcieSlotPortExpander_Configure(UINTN Address);
EFI_STATUS DriveSlotPortExpander_Configure(UINTN Address);

#endif //_PCIE_I2C_IO_H_
