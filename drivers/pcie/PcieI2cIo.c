/** @file

Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

**/

// #include <PiDxe.h>
// #include <Library/UefiBootServicesTableLib.h>
#include "NXPPCA9641.h"
#include "Semtech1509B.h"
#include "PcieI2cIo.h"
//#include "hdts_shell.h"

#define I2C_ARBITER_ADDRESS 0x08
#define I2C_BUS_FREQ (100 * 1000) //100KHz
#define PCIE_SLOT_I2C_CONTROLLER  2

EFI_STATUS PcieI2cIoDeinitialize(void)
{
	I2cDevice dev = PCIE_SLOT_I2C_CONTROLLER;
	// I2cResult i2cResult;
	EFI_STATUS Status = 0;

	I2C_Close(dev);
	I2C_Detach(dev);
	return Status;
}
/**
Initialize I2C master controller for HP port expanders

@param[in]     Controller   Controller Id

@retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieI2cIoInitialize(void)
{
  I2cDevice dev = PCIE_SLOT_I2C_CONTROLLER;
  I2cResult i2cResult;
  EFI_STATUS Status = 0;

  i2cResult = I2C_Attach(dev);
  if (I2C_RES_SUCCESS != i2cResult)
  {
    return EFI_NOT_READY;
  }
  i2cResult = I2C_Open(dev);
  if (I2C_RES_SUCCESS != i2cResult)
  {
    I2C_Detach(dev);
    return EFI_NOT_READY;
  }

  i2cResult = I2C_Reset(dev);
  if (I2C_RES_SUCCESS != i2cResult)
  {
    I2C_Close(dev);
    I2C_Detach(dev);
    return EFI_NOT_READY;
  }

  Status = PcieI2cIoRequestLock();

  return Status;
}

EFI_STATUS PcieI2cIoRequestLock(void)
{
  EFI_STATUS Status = 0;
  UINT8 lockRequest[] = {REG_PCA9641_CTRL, 0x85};
  UINT8 ctrlRegValue = 0;

  Status = PcieI2cIoWrite(I2C_ARBITER_ADDRESS, lockRequest, sizeof(lockRequest));
  //Todo: need to handle graceful fail here
  while (!EFI_ERROR(Status) && ((ctrlRegValue & 0x02) == 0)) {
    Status = PcieI2cIoWriteRead(I2C_ARBITER_ADDRESS, lockRequest, 1, &ctrlRegValue, sizeof(ctrlRegValue));
  }
  // shell_msg("ctrlReg = 0x%x\r\n", ctrlRegValue);
  return Status;
}

EFI_STATUS PcieI2cIoReleaseLock(void)
{
  EFI_STATUS Status = 0;
  UINT8 lockRelease[] = {REG_PCA9641_CTRL, 0x80};
  UINT8 ctrlRegValue = 0x02;

  Status = PcieI2cIoWrite(I2C_ARBITER_ADDRESS, lockRelease, sizeof(lockRelease));
  //Todo: need to handle graceful fail with timout here
  while (!EFI_ERROR(Status) && ((ctrlRegValue & 0x02))) {
    Status = PcieI2cIoWriteRead(I2C_ARBITER_ADDRESS, lockRelease, sizeof(lockRelease), &ctrlRegValue, sizeof(ctrlRegValue));
  }
  return Status;
}

/**
Read port expander register(s)

@param[in]     Address      I2C slave address of the port expander
@param[in]     WriteBuffer  port expander register, see Semtech1509B.h
@param[in]     ReadBuffer  Read buffer for register data
@param[in]     Length     Number of bytes/registers to read

@retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieI2cIoWriteRead(UINTN Address,
  UINT8* WriteBuffer,
  UINTN WriteLength,
  UINT8* ReadBuffer,
  UINTN ReadLength)
{
  EFI_I2C_REQUEST_PACKET Request;

  Request.OperationCount = 2;
  Request.Operation[0].Flags = 0; //WRITE operation
  Request.Operation[0].LengthInBytes = WriteLength;
  Request.Operation[0].Buffer = WriteBuffer;
  Request.Operation[1].Flags = 1; //read operation
  Request.Operation[1].LengthInBytes = ReadLength;
  Request.Operation[1].Buffer = ReadBuffer;
  return PcieI2cIoRequest(Address, (EFI_I2C_REQUEST_PACKET*)&Request);
}
/**
Write port expander register(s)

@param[in]     Address    I2C slave address of the port expander
@param[in]     Register   port expander register, see Semtech1509B.h
@param[in]     Buffer     buffer containing write register data
@param[in]     Length     Number of bytes/registers to write

@retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieI2cIoWrite(UINTN Address, UINT8* Buffer, UINTN Length)
{
  EFI_I2C_REQUEST_PACKET Request;

  Request.OperationCount = 1;
  Request.Operation[0].Flags = 0; //WRITE operation
  Request.Operation[0].LengthInBytes = Length;
  Request.Operation[0].Buffer = Buffer;
  return PcieI2cIoRequest(Address, (EFI_I2C_REQUEST_PACKET*)&Request);
}

EFI_STATUS PcieI2cIoRequest(UINTN Address, EFI_I2C_REQUEST_PACKET* Request)
{
  EFI_STATUS Status = 0;
  I2cDevice dev = PCIE_SLOT_I2C_CONTROLLER;
  I2cResult i2cResult;
  I2cClientConfig ClntCfg;
  I2cSequence sequence;
  I2cTransfer transfer[2];
  I2cIoResult ioResult;
  I2cBuffDesc buffDesc[2];
  I2cTransferConfig tranCfg;
  uint32_t uNumCompleted;

  ClntCfg.uBusFreqKhz = 100;
  ClntCfg.uByteTransferTimeoutUs = 200;

  tranCfg.uSlaveAddr = Address;

  if (1 == Request->OperationCount)
  {
    if (0 == Request->Operation[0].Flags) //WRITE operation
    {
      buffDesc[0].pBuff = Request->Operation[0].Buffer;
      buffDesc[0].uBuffSize = Request->Operation[0].LengthInBytes;
      transfer[0].pI2cBuffDesc = &buffDesc[0];
      transfer[0].uTrSize = Request->Operation[0].LengthInBytes;
      transfer[0].tranCfg = tranCfg;
      transfer[0].eTranDirection = I2cTranDirOut;
      transfer[0].eTranCtxt = I2cTrCtxNotASequence;
      transfer[0].uIsSmbus = 0;
      transfer[0].uIsSmbusBlock = 0;
      transfer[0].uIsSmbusPEC = 0;

      i2cResult = I2C_Write(dev, &transfer[0], &ClntCfg, &uNumCompleted);
      if (I2C_RES_SUCCESS != i2cResult)
      {
        return EFI_DEVICE_ERROR;
      }
    }
    else  //READ operation
    {
      buffDesc[0].pBuff = Request->Operation[0].Buffer;
      buffDesc[0].uBuffSize = Request->Operation[0].LengthInBytes;
      transfer[0].pI2cBuffDesc = &buffDesc[0];
      transfer[0].uTrSize = Request->Operation[0].LengthInBytes;
      transfer[0].tranCfg = tranCfg;
      transfer[0].eTranDirection = I2cTranDirIn;
      transfer[0].eTranCtxt = I2cTrCtxNotASequence;
      transfer[0].uIsSmbus = 0;
      transfer[0].uIsSmbusBlock = 0;
      transfer[0].uIsSmbusPEC = 0;

      i2cResult = I2C_Read(dev, &transfer[0], &ClntCfg, &uNumCompleted);
      if (I2C_RES_SUCCESS != i2cResult)
      {
        return EFI_DEVICE_ERROR;
      }
    }
  }
  else if (2 == Request->OperationCount)
  {
    buffDesc[0].pBuff = Request->Operation[0].Buffer;
    buffDesc[0].uBuffSize = Request->Operation[0].LengthInBytes;
    transfer[0].pI2cBuffDesc = &buffDesc[0];
    transfer[0].uTrSize = Request->Operation[0].LengthInBytes;
    transfer[0].tranCfg = tranCfg;
    transfer[0].eTranDirection = Request->Operation[0].Flags?I2cTranDirIn:I2cTranDirOut;
    transfer[0].eTranCtxt = I2cTrCtxSeqStart;
    transfer[0].uIsSmbus = 0;
    transfer[0].uIsSmbusBlock = 0;
    transfer[0].uIsSmbusPEC = 0;

    buffDesc[1].pBuff = Request->Operation[1].Buffer;
    buffDesc[1].uBuffSize = Request->Operation[1].LengthInBytes;
    transfer[1].pI2cBuffDesc = &buffDesc[1];
    transfer[1].uTrSize = Request->Operation[1].LengthInBytes;
    transfer[1].tranCfg = tranCfg;
    transfer[1].eTranDirection = Request->Operation[1].Flags?I2cTranDirIn:I2cTranDirOut;
    transfer[1].eTranCtxt = I2cTrCtxSeqEnd;
    transfer[1].uIsSmbus = 0;
    transfer[1].uIsSmbusBlock = 0;
    transfer[1].uIsSmbusPEC = 0;

    sequence.pTransfer = transfer;
    sequence.uNumTransfers = 2;

    i2cResult = I2C_BatchTransfer(dev, &sequence, &ClntCfg, &ioResult);
    if (I2C_RES_SUCCESS != i2cResult)
    {
      return EFI_DEVICE_ERROR;
    }
  }
  else  // MAX 2 operation supported
  {
    return EFI_UNSUPPORTED;
  }

  return Status;
}
