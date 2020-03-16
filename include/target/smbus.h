/*==============================================================================
#  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
#  All rights reserved.
#  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
#  Copyright (c) 2014 Qualcomm Technologies, Inc.  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   smbus.h
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2014.06.06
 *  @brief  Public API and related functions for SMBUS driver
 */

#ifndef SMBUS_H
#define SMBUS_H

#include <target/i2c.h>

#define SMBUS_WRITE_ADDR(addr) ((addr << 1) | 0)
#define SMBUS_READ_ADDR(addr)  ((addr << 1) | 1)

typedef struct
{
    I2cBuffDesc      *pBuff;    // IO Buffer
    uint32_t          uTrSize;  // Transfer total number of bytes
    I2cTransferConfig tranCfg;  // Transfer configuration (slave addr)
    I2cClientConfig   clientCfg;// Client configuration (bus frequency/timeout)
    uint8_t           command;  // SMBus Command Code (slave-specific)
    I2cIoResult      *pIoRes;   // I2C IO Result for deeper command parsing
    uint8_t           bBlockReadStartsWithLength;// Some of our clients send the
                                // length of the transaction (following SMBus
                                //   spec). Others don't.
    uint8_t           bPecCheck;// Use the Packet Error Checking protocol
} SmbusTransfer;

#define SMBUS_QUEUE_TIMEOUT        2
#define I2C_DEFAULT_TIMEOUT_MS     5
#define I2C_DEFAULT_CLOCK_FREQ_KHZ 100

typedef enum
{
    SMBUS_SUCCESS                      = 0,
    SMBUS_ERROR_INVALID_PARAMETER      = -24,
    SMBUS_ERROR_NOT_INITIALIZED        = -40,
    SMBUS_ERROR_NOT_SUPPORTED          = -42,
    SMBUS_ERROR_OUT_OF_RANGE_PARAMETER = -100,
    SMBUS_ERROR_BUSY_RESOURCE          = -120,

    // SMBus-specific errors
    SMBUS_ERROR_SPEC_BASE              = (int32_t) 0x80000000,
    SMBUS_ERROR_ADDR_NACKED,
    SMBUS_ERROR_DATA_NACKED,
    SMBUS_ERROR_TIMEOUT,
    SMBUS_ERROR_DEVICE_ERROR,
    SMBUS_ERROR_DRIVER_ERROR,
    SMBUS_ERROR_I2C_PLATFORM_ERROR,
    SMBUS_ERROR_OS_ERROR,
    SMBUS_ERROR_UNKNOWN_I2C_ERROR
} SmbusResult;

typedef enum
{
    SMBUS_DEVICE_1 = I2C_DEVICE_1,
    SMBUS_DEVICE_2,
    SMBUS_DEVICE_3,
    SMBUS_DEVICE_4,
    SMBUS_DEVICE_5,
    SMBUS_DEVICE_6,
    SMBUS_DEVICE_7,
    SMBUS_DEVICE_8,
    SMBUS_NUM_DEVICES
} SmbusDevice;

typedef SmbusResult (*SmbusOpFunction)(SmbusDevice, SmbusTransfer*);

/* Function Headers */

/**
 * These parameters are shared amongst many or all of the commands.  Any generic
 * parameter will be described up here, parameters with command-specific
 * functionality will be described below
 *
 * For full descriptions on what each of the commands do, refer to the SMBUS
 *  specification (V2.0), in the Bus Protocols section.
 *
 * @param[in]   SmbusDevice    The index of the SMBus Device to do the transfer
 * @param[in]   SmbusTransfer  A structure containing transfer specific info
 * @return      SmbusResult    Return status for executed command
 **/

 /**
 * Initializes the SMBUS driver
 */
void SmbusInit();

/**
 * Deinitializes the SMBUS driver.
 */
void SmbusDeInit();

/**
 * Check to see if a device has been attached to yet
 */
bool SmbusIsAttached(SmbusDevice dev);

/**
 * Sets up local variables, and prepares an SMBus device for use
 */
SmbusResult SmbusAttach(SmbusDevice dev);

/**
 * Cleans up, and detaches from and SMBUS device to allow others to use it.
 */
SmbusResult SmbusDetach(SmbusDevice dev);

/**
 * Executes an SMBUS Quick Read command (no data sent or received, just pokes
 *   an address)
 */
SmbusResult SmbusQuickRead        (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Quick Write command (no data sent or received, just pokes
 *   an address)
 */
SmbusResult SmbusQuickWrite       (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Receive Byte command (for command-based SMBUS interfaces)
 */
SmbusResult SmbusReceiveByte      (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Send Byte command (for command-based SMBUS interfaces)
 */
SmbusResult SmbusSendByte         (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Read Byte command (Sends read command to device then
 *   receives data)
 */
SmbusResult SmbusReadDataByte     (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Write Byte command (Sends write command to device then data)
 */
SmbusResult SmbusWriteDataByte    (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Read Word command (Sends read command to device then
 *   receives data)
 */
SmbusResult SmbusReadDataWord     (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Write Word command (Sends write command to device then data)
 */
SmbusResult SmbusWriteDataWord    (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Process Call command (Sends command with data to device,
 *   then waits for device to process the data and send a response)
 */
SmbusResult SmbusProcessCall      (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Block Read command (Reads a maximum of 32 bytes from the
 *   device)
 */
SmbusResult SmbusBlockRead        (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Executes an SMBUS Block Write command (Writes a maximum of 32 bytes to the
 *   device)
 */
SmbusResult SmbusBlockWrite       (SmbusDevice dev, SmbusTransfer *xfer);

/**
 * Not supported.
 */
SmbusResult SmbusBlockProcessCall (SmbusDevice dev, SmbusTransfer *xfer);

//------------From fw/uefi/MdePkg/Include/Pi/PiI2c.h--------------------
///
/// QuickRead:          OperationCount=1,
///     Operation0:     LengthInBytes=0,   Flags=I2C_FLAG_READ
/// QuickWrite:         OperationCount=1,
///     Operation0:     LengthInBytes=0,   Flags=I2C_FLAG_WRITE
///
///
/// ReceiveByte:        OperationCount=1,
///     Operation0:     LengthInBytes=1,   Flags=I2C_FLAG_SMBUS_OPERATION
///                                            | I2C_FLAG_READ
///
/// SendByte:           OperationCount=1,
///     Operation0:     LengthInBytes=1,   Flags=I2C_FLAG_SMBUS_OPERATION
///
/// ReadDataByte:       OperationCount=2,
///     Operation0:     LengthInBytes=1,   Flags=I2C_FLAG_SMBUS_OPERATION
///     Operation1:     LengthInBytes=1,   Flags=I2C_FLAG_READ
///
/// WriteDataByte:      OperationCount=1,
///     Operation0:     LengthInBytes=2,   Flags=I2C_FLAG_SMBUS_OPERATION
///
/// ReadDataWord:       OperationCount=2,
///     Operation0:     LengthInBytes=1,   Flags=I2C_FLAG_SMBUS_OPERATION
///     Operation1:     LengthInBytes=2,   Flags=I2C_FLAG_READ
///
/// WriteDataWord:      OperationCount=1,
///     Operation0:     LengthInBytes=3,   Flags=I2C_FLAG_SMBUS_OPERATION
///
/// ReadBlock:          OperationCount=2,
///     Operation0:     LengthInBytes=1,   Flags=I2C_FLAG_SMBUS_OPERATION
///                                            | I2C_FLAG_SMBUS_BLOCK
///     Operation1:     LengthInBytes=33,  Flags=I2C_FLAG_READ
///
/// WriteBlock:         OperationCount=1,
///     Operation0:     LengthInBytes=N+2, Flags=I2C_FLAG_SMBUS_OPERATION
///                                            | I2C_FLAG_SMBUS_BLOCK
///
/// ProcessCall:        OperationCount=2,
///     Operation0:     LengthInBytes=3,   Flags=I2C_FLAG_SMBUS_OPERATION
///                                            | I2C_FLAG_SMBUS_PROCESS_CALL
///     Operation1:     LengthInBytes=2,   Flags=I2C_FLAG_READ
///
/// BlkProcessCall:     OperationCount=2,
///     Operation0:     LengthInBytes=N+2, Flags=I2C_FLAG_SMBUS_OPERATION
///                                            | I2C_FLAG_SMBUS_PROCESS_CALL
///                                            | I2C_FLAG_SMBUS_BLOCK
///     Operation1:     LengthInBytes=33,  Flags=I2C_FLAG_READ

#endif /* SMBUS_H */
