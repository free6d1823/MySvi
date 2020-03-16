/*==============================================================================
#      Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#
#    Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
#    All Rights Reserved.
#    Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
#=============================================================================*/
/** @file   Pmbus.c
 *  @brief  Implementation of a subset of the PMBUS protocol
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <target/pmbus.h>
#include <target/cmdline.h>
#include <asm/mach/tlmm_boot.h>

/*  PmbusDefaults.h  */
#define DEFAULT_PMBUS_PMBUS_DEVICE_ID PMBUS_DEVICE_ID_1
#define DEFAULT_PMBUS_SMBUS_DEVICE_ID SMBUS_DEVICE_4
#define DEFAULT_PMBUS_SLAVE_ADDRESS   0x64

static PMBUS_HANDLE_TYPE hPmbusDeviceHandle = {0};
PMBUS_DEVICE_MAPPING_TYPE  gPmbusDeviceMap = {0};
PMBUS_HOB_DATA_TYPE        gPmbusHobData   = {0};
PPMBUS_HOB_DATA_TYPE       gpPmbusHobData = NULL;

void PmbusInitMap (void)
{
    gPmbusDeviceMap.PmbusDeviceId = DEFAULT_PMBUS_PMBUS_DEVICE_ID;
    gPmbusDeviceMap.SmbusDeviceId = DEFAULT_PMBUS_SMBUS_DEVICE_ID;
    gPmbusDeviceMap.DeviceAddress = DEFAULT_PMBUS_SLAVE_ADDRESS;
    gPmbusDeviceMap.bDeviceInUse  = false;
    gPmbusHobData.uCount = 1;
    gPmbusHobData.pMap = &gPmbusDeviceMap;
    gpPmbusHobData = &gPmbusHobData;
}

/** @brief Opens a connection to a PMBUS device.

    @param PmbusDeviceId            PMBUS device ID.
    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusOpen
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle
)
{
    PPMBUS_DEVICE_MAPPING_TYPE  pPmbusDeviceMapping = NULL;

    // handle must be empty
    if (!hPmbusDeviceHandle || hPmbusDeviceHandle->pDeviceMapping)
    {
        return PMBUS_STATUS_INVALID_HANDLE;
    }

    if (NULL == gpPmbusHobData)
    {
        PmbusInitMap();
    }

    boot_tlmm_init();

    // clear the data in the device handle
    memset(hPmbusDeviceHandle, 0, sizeof(PMBUS_HANDLE_TYPE));

    pPmbusDeviceMapping = &(gpPmbusHobData->pMap[0]);

    if (NULL == pPmbusDeviceMapping)
    {
        return PMBUS_STATUS_DEVICE_NOT_FOUND;
    }
    if (true == pPmbusDeviceMapping->bDeviceInUse)
    {
        return PMBUS_STATUS_BUS_BUSY;
    }

    // Attach to the SMBUS
    if (SMBUS_SUCCESS != SmbusAttach(pPmbusDeviceMapping->SmbusDeviceId))
    {
        return PMBUS_STATUS_BUS_INITIALIZATION_FAILURE;
    }

    hPmbusDeviceHandle->pDeviceMapping = pPmbusDeviceMapping;
    hPmbusDeviceHandle->pDeviceMapping->bDeviceInUse = true;

    return PMBUS_STATUS_SUCCESS;
}


/** @brief Close a connection with a PMBUS device.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @return                     PMBUS_STATUS_INVALID_HANDLE if the device handle is invalid.
    @return                     PMBUS_STATUS_SUCCESS if successful.
 */
PMBUS_STATUS_ENUM PmbusClose
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle
)
{
    if (!hPmbusDeviceHandle || !hPmbusDeviceHandle->pDeviceMapping)
    {
        return PMBUS_STATUS_INVALID_HANDLE;
    }

    SmbusDetach(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId);

    hPmbusDeviceHandle->pDeviceMapping->bDeviceInUse   = false;

    // clear the mapping data in the device handle
    memset(hPmbusDeviceHandle, 0, sizeof(PMBUS_HANDLE_TYPE));

    return PMBUS_STATUS_SUCCESS;
}


/** @brief Performs a generic read command

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param Command              PMBUS command.
    @param pIoBuffer            Pointer to the input/output buffer.
    @param BufferSize           I/O buffer size.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusGenericRead
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    uint32_t            Command,
    void                *pIoBuffer,
    size_t              BufferSize
)
{
    SmbusTransfer SmbusTransaction;
    I2cBuffDesc IoBufferDescriptor;
    SmbusResult SmbusStatus;

    if (!hPmbusDeviceHandle || !hPmbusDeviceHandle->pDeviceMapping)
    {
        return PMBUS_STATUS_INVALID_HANDLE;
    }

    if (NULL == pIoBuffer)
    {
        return PMBUS_STATUS_INVALID_BUFFER;
    }

    // Setup the output buffer descriptor
    IoBufferDescriptor.pBuff = (uint8_t*) pIoBuffer;
    IoBufferDescriptor.uBuffSize = BufferSize;

    // Set up the client config
    SmbusTransaction.clientCfg.uBusFreqKhz = 400;
    SmbusTransaction.clientCfg.uByteTransferTimeoutUs = 20000;

    // Setup the transaction
    SmbusTransaction.tranCfg.uSlaveAddr = hPmbusDeviceHandle->pDeviceMapping->DeviceAddress;
    SmbusTransaction.pBuff = &IoBufferDescriptor;
    SmbusTransaction.uTrSize = BufferSize;
    SmbusTransaction.command = Command;
    SmbusTransaction.pIoRes  = NULL;
    SmbusTransaction.bBlockReadStartsWithLength = false;

    switch(BufferSize)
    {
        case 0:
        {
            SmbusStatus = SmbusReceiveByte(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId, &SmbusTransaction);
            break;
        }
        case 1:
        {
            SmbusStatus = SmbusReadDataByte(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId, &SmbusTransaction);
            break;
        }
        case 2:
        {
            SmbusStatus = SmbusReadDataWord(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId, &SmbusTransaction);
            break;
        }
        default:
        {
            SmbusStatus = SmbusBlockRead(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId, &SmbusTransaction);
            break;
        }
    }

    if (SmbusStatus == SMBUS_SUCCESS)
    {
        return PMBUS_STATUS_SUCCESS;
    }
    return (PMBUS_STATUS_ENUM)ENCODE_PMBUS_STATUS(PMBUS_STATUS_BUS_READ_FAILURE, SmbusStatus);
}


/** @brief Performs a generic read command

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param Command              PMBUS command.
    @param pIoBuffer            Pointer to the input/output buffer.
    @param BufferSize           I/O buffer size.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusGenericWrite
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    uint32_t            Command,
    void                *pIoBuffer,
    size_t              BufferSize
)
{
    SmbusTransfer SmbusTransaction;
    I2cBuffDesc IoBufferDescriptor;
    SmbusResult SmbusStatus;

    if (!hPmbusDeviceHandle || !hPmbusDeviceHandle->pDeviceMapping)
    {
        return PMBUS_STATUS_INVALID_HANDLE;
    }

    // Setup the output buffer descriptor
    IoBufferDescriptor.pBuff = (uint8_t*) pIoBuffer;
    IoBufferDescriptor.uBuffSize = BufferSize;

    // Set up the client config
    SmbusTransaction.clientCfg.uBusFreqKhz = 400;
    SmbusTransaction.clientCfg.uByteTransferTimeoutUs = 20000;

    // Setup the transaction
    SmbusTransaction.tranCfg.uSlaveAddr = hPmbusDeviceHandle->pDeviceMapping->DeviceAddress;
    SmbusTransaction.pBuff = &IoBufferDescriptor;
    SmbusTransaction.uTrSize = BufferSize;
    SmbusTransaction.command = Command;
    SmbusTransaction.pIoRes  = NULL;
    SmbusTransaction.bBlockReadStartsWithLength = false;

    switch(BufferSize)
    {
        case 0:
        {
            SmbusStatus = SmbusSendByte(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId, &SmbusTransaction);
            break;
        }
        case 1:
        {
            SmbusStatus = SmbusWriteDataByte(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId, &SmbusTransaction);
            break;
        }
        case 2:
        {
            SmbusStatus = SmbusWriteDataWord(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId, &SmbusTransaction);
            break;
        }
        default:
        {
            SmbusStatus = SmbusBlockWrite(hPmbusDeviceHandle->pDeviceMapping->SmbusDeviceId, &SmbusTransaction);
            break;
        }
    }

    if (SmbusStatus == SMBUS_SUCCESS)
    {
        return PMBUS_STATUS_SUCCESS;
    }

    return (PMBUS_STATUS_ENUM)ENCODE_PMBUS_STATUS(PMBUS_STATUS_BUS_WRITE_FAILURE, SmbusStatus);
}


/** @brief Generic execute PMBUS command.

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pCommandInfo             Pointer to the command info
    @param pIoBuffer                Pointer to the input/output buffer
    @param pDevice                  Device page channel select and bus access type
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusGenericExecuteCommand
(
    PPMBUS_HANDLE_TYPE              hPmbusDeviceHandle,
    const PPMBUS_COMMAND_INFO_TYPE  pCommandInfo,
    void                            *pIoBuffer,
    PPMBUS_PAGE_CHANNEL_SELECT_TYPE pDevice
)
{
    PMBUS_STATUS_ENUM Status = PMBUS_STATUS_FAILURE;

    // verify there is a valid handle pointer
    if (NULL == hPmbusDeviceHandle)
    {
        return PMBUS_STATUS_INVALID_HANDLE;
    }

    // verify the parameters are valid
    if (NULL == pCommandInfo)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    if (0 < pCommandInfo->IoBufferSize && NULL == pIoBuffer)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_3;
    }

    if (NULL == pDevice)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_4;
    }

    // select the page channel
    if (pCommandInfo->ChannelSelect == PMBUS_CHANNEL_SELECT_PAGED
        && pCommandInfo->Command != PMBUS_PAGE_COMMAND
        && IS_PMBUS_STATUS_NOT_SUCCESS(Status = PmbusSelectPageChannel(hPmbusDeviceHandle, pDevice->PageChannelSelect)))
    {
        return Status;
    }

    // perform the command
    if (pDevice->BusAccessType == PMBUS_ACCESS_TYPE_READ
        && (pCommandInfo->BusAccessType & pDevice->BusAccessType) == PMBUS_ACCESS_TYPE_READ)
    {
        return PmbusGenericRead(hPmbusDeviceHandle,
                                pCommandInfo->Command,
                                pIoBuffer,
                                pCommandInfo->IoBufferSize);
    }

    if (pDevice->BusAccessType == PMBUS_ACCESS_TYPE_WRITE
        && (pCommandInfo->BusAccessType & pDevice->BusAccessType) == PMBUS_ACCESS_TYPE_WRITE)
    {
        return PmbusGenericWrite(hPmbusDeviceHandle,
                                pCommandInfo->Command,
                                pIoBuffer,
                                pCommandInfo->IoBufferSize);
    }


    return PMBUS_STATUS_INVALID_BUS_ACCESS_TYPE;
}


/** @brief Selects the page channel

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param PageChannel          The selected page channel.
    @return PMBUS_STATUS_ENUM.
 */
static __inline PMBUS_STATUS_ENUM PmbusSelectPageChannel
(
    PPMBUS_HANDLE_TYPE              hPmbusDeviceHandle,
    PMBUS_PAGE_CHANNEL_SELECT_ENUM  PageChannel
)
{
    return PmbusGenericWrite(hPmbusDeviceHandle, PMBUS_PAGE_COMMAND, &PageChannel, sizeof(PMBUS_BYTE_TYPE));
}


/** @brief Command: PAGE - Selects page channel 0, 1 or both.

    Selects Controller 0, Controller 1 or both Controllers 0 and 1 to receive commands.
    All commands following this command will be received and acted on by the selected
    controller or controllers.

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pPageChannelSelect       Pointer to the page channel.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PageChannelSelect
(
    PPMBUS_HANDLE_TYPE              hPmbusDeviceHandle,
    PPMBUS_PAGE_CHANNEL_SELECT_TYPE pPageChannelSelect
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(PAGE) };

    if (NULL == pPageChannelSelect)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pPageChannelSelect->PageChannelSelect,
                                        pPageChannelSelect);
}


/** @brief Command: OPERATION - Sets enable, disable and VOUT margin modes.

    Sets enable, disable and VOUT margin settings.  Data values of OPERATION that force
    margin high or low only take effect when the MGN pin is left open
    (i.e., in the nominal margin state).

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pOperationConfiguration  Pointer to the operation margin configuration
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM Operation
(
    PPMBUS_HANDLE_TYPE                  hPmbusDeviceHandle,
    PPMBUS_OPERATION_CONFIGURATION_TYPE pOperationConfiguration
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(OPERATION) };

    if (NULL == pOperationConfiguration)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOperationConfiguration->OperationMode,
                                        &pOperationConfiguration->Device);
}


/** @brief Command: ON_OFF_CONFIG - Configures the EN pin and PMBus commands to turn the unit ON/OFF.

    Configures the interpretation and coordination of the OPERATION command and the ENABLE pin (EN).

    @param hPmbusDeviceHandle               Pointer to a PMBUS device handle
    @param pOperationOutputConfiguration    Pointer to the operation output configuration
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OperationOutput
(
    PPMBUS_HANDLE_TYPE                          hPmbusDeviceHandle,
    PPMBUS_OPERATION_OUTPUT_CONFIGURATION_TYPE  pOperationOutputConfiguration
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(ON_OFF_CONFIG) };

    if (NULL == pOperationOutputConfiguration)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOperationOutputConfiguration->OperationOutput,
                                        &pOperationOutputConfiguration->Device);
}


/** @brief Command: CLEAR_FAULTS - Clears fault indications.

    Clears all fault bits in all registers and releases the SALRT pin(if asserted) simultaneously.
    If a fault condition still exists, the bit will reassert immediately.This command will not restart
    a device if it has shut down, it will only clear the faults.

    @param hPmbusDeviceHandle     Pointer to a PMBUS device handle
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM ClearFaults
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(CLEAR_FAULTS) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE };
    PMBUS_BYTE_TYPE Data = 0;

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, &Data, &Device);
}


/** @brief Command: PHASE - The PHASE command provides the ability to control multiple phase on one PMBus unit.

    The PHASE command provides the ability to configure, control, and monitor multiple
    phases on one PMBus unit.

    @param hPmbusDeviceHandle     Pointer to a PMBUS device handle
    @param pPhase                 Pointer to the phase.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM Phase
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_PHASE_TYPE   pPhase
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(PHASE) };

    if (NULL == pPhase)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pPhase->Phase,
                                        &pPhase->Device);
}


/** @brief Command: WRITE_PROTECT - The WRITE_PROTECT command provides the ability to control write protection to the configuration command..

    The WRITE_PROTECT command provides the ability to set the write protection of certain configuration commands.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pWriteProtect        Pointer to the write protect settings
    @param BusAccessType        Bus access type
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM WriteProtect
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle,
    PPMBUS_BYTE_TYPE        pWriteProtect,
    PMBUS_ACCESS_TYPE_ENUM  BusAccessType
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(WRITE_PROTECT) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, BusAccessType };

    if (NULL == pWriteProtect)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pWriteProtect, &Device);
}


/** @brief Command: VOUT_MODE - The VOUT_MODE command returns the supported VOUT mode.

    The VOUT_MODE command returns the supported VOUT mode.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pVoltageOutputMode   Pointer to the voltage output mode.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetVoltageOutputMode
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_BYTE_TYPE    pVoltageOutputMode
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_MODE) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pVoltageOutputMode)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pVoltageOutputMode, &Device);
}


/** @brief Command: VOUT_COMMAND - Sets the nominal value of the output voltage.

    This command sets or reports the target output voltage. This command cannot set a value higher
    than either VOUT_MAX or 110% of the pin-strap VOUT setting.

    @param hPmbusDeviceHandle           Pointer to a PMBUS device handle
    @param pVoltageOutputConfiguration  Poiner to the voltage output level configuration
    @return PMBUS_STATUS_ENUM.
    */
PMBUS_STATUS_ENUM VoltageOutput
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pVoltageOutputConfiguration
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_COMMAND) };

    if (NULL == pVoltageOutputConfiguration)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pVoltageOutputConfiguration->VoltageLevel,
                                        &pVoltageOutputConfiguration->Device);
}


/** @brief Command: VOUT_TRIM - Applies trim voltage to VOUT set-point.

    This command Sets a fixed trim voltage to the output voltage command value
    This command is typically used to calibrate a device in the application circuit.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pVoltageTrim         Poiner to the voltage trim.
    @return PMBUS_STATUS_ENUM.
    */
PMBUS_STATUS_ENUM VoltageTrim
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pVoltageTrim
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_TRIM) };

    if (NULL == pVoltageTrim)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pVoltageTrim->VoltageLevel,
                                        &pVoltageTrim->Device);
}


/** @brief Command: VOUT_CALL_OFFSET - Applies a fixed offset voltage to the VOUT_COMMAND.

    The VOUT_CAL_OFFSET command is used to apply a fixed offset voltage to the output voltage command
    value. This command is typically used by the user to calibrate a device in the application circuit.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pFixedVoltageOffset  Pointer to the voltage offset calibration
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageCalibrateOffset
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_VOUT_CAL_OFFSET_TYPE pFixedVoltageOffset
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_CAL_OFFSET) };

    if (NULL == pFixedVoltageOffset)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pFixedVoltageOffset->VoltageOffset,
                                        &pFixedVoltageOffset->Device);
}


/** @brief Command: VOUT_MAX - Sets the maximum possible value of Vout.

    The VOUT_ MAX command sets an upper limit on the output voltage the unit can command regardless of any other
    commands or combinations. The intent of this command is to provide a safeguard against a user accidentally
    setting the output voltage to a possibly destructive level rather than to be the primary output overprotection.
    Default value can be changed via PMBus.

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pMaximumOutputVoltage    Pointer to the maximum output voltage.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM MaximumOutputVoltage
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pMaximumOutputVoltage
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_MAX) };

    if (NULL == pMaximumOutputVoltage)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pMaximumOutputVoltage->VoltageLevel,
                                        &pMaximumOutputVoltage->Device);
}


/** @brief Command: VOUT_MARGIN_HIGH - Sets the value of the Vout during a marging high.

    Sets the value of the VOUT during a margin high. This VOUT_MARGIN_HIGH command loads the unit with the voltage
    to which the output is to be changed when the OPERATION command is set to "Margin High".

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pHighOutputVoltageMargin Pointer to the high output voltage margin.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageHighMargin
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle,
    PPMBUS_VOUT_MARGIN_TYPE pHighOutputVoltageMargin
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_MARGIN_HIGH) };

    if (NULL == pHighOutputVoltageMargin)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pHighOutputVoltageMargin->VoltageMargin,
                                        &pHighOutputVoltageMargin->Device);
}


/** @brief Command: VOUT_MARGIN_LOW - Sets the value of the Vout during a marging low.

    Sets the value of the VOUT during a margin low. This VOUT_MARGIN_LOW command loads
    the unit with the voltage to which the output is to be changed when the OPERATION
    command is set to "Margin Low".

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pLowOutputVoltageMargin  Pointer to the low output voltage margin.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageLowMargin
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle,
    PPMBUS_VOUT_MARGIN_TYPE pLowOutputVoltageMargin
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_MARGIN_LOW) };

    if (NULL == pLowOutputVoltageMargin)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pLowOutputVoltageMargin->VoltageMargin,
                                        &pLowOutputVoltageMargin->Device);
}


/** @brief Command: VOUT_TRANSITION_RATE - Sets the transition rate during margin or other change of Vout.

    Sets the rate at which the output should change voltage when the device receives an
    OPERATION command (marging high, marging low) which causes the output voltage to change.
    The maximum poissible positive value of the two data bytes indicates that the device
    should make the transition as quickly as possible.

    @param hPmbusDeviceHandle           Pointer to a PMBUS device handle
    @param pOutputVoltageTransitionRate Pointer to the output voltage transition rate.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageTransitionRate
(
    PPMBUS_HANDLE_TYPE                  hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_TRANSITION_RATE_TYPE pOutputVoltageTransitionRate
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_TRANSITION_RATE) };

    if (NULL == pOutputVoltageTransitionRate)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOutputVoltageTransitionRate->TransitionRate,
                                        &pOutputVoltageTransitionRate->Device);
}


/** @brief Command: VOUT_DROOP - Reads the loadline (V/I Slope) resistance for the rail.

    The VOUT_DROOP sets the effective load line (V/I slope) for the rail in which the device is used.
    It is the rate, in mV/A at which the output voltage decreases (or increases) with increasing
    (or decreasing) output current for use with adaptive voltage positioning schemes.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pOutputVoltageDroop  Pointer to the output voltage droop.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageDroop
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_DROOP_TYPE   pOutputVoltageDroop
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_DROOP) };

    if (NULL == pOutputVoltageDroop)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOutputVoltageDroop->VoltageDroop,
                                        &pOutputVoltageDroop->Device);
}


/** @brief Command: VOUT_MIN - Sets the minimum possible value of Vout.

    The VOUT_MIN command sets an lower limit on the output voltage the unit can command regardless of any other
    commands or combinations.

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pMinimumOutputVoltage    Pointer to the minimum output voltage.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM MinimumOutputVoltage
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pMinimumOutputVoltage
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_MIN) };

    if (NULL == pMinimumOutputVoltage)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pMinimumOutputVoltage->VoltageLevel,
                                        &pMinimumOutputVoltage->Device);
}


/** @brief Command: VOUT_OV_FAULT_LIMIT - Reads the Vout overvoltage fault threshold.

    Sets the Vout overvoltage fault threshold.

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pOvervoltageFaultLimit   Pointer to the over voltage fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OverVoltageFaultLimit
(
    PPMBUS_HANDLE_TYPE                  hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_THRESHOLD_TYPE   pOvervoltageFaultLimit
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_OV_FAULT_LIMIT) };

    if (NULL == pOvervoltageFaultLimit)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOvervoltageFaultLimit->Threshold,
                                        &pOvervoltageFaultLimit->Device);
}


/** @brief Command: VOUT_UV_FAULT_LIMIT - Reads the Vout undervoltage fault threshold.

    Sets the VOUT undervoltage fault threshold. This fault is masked during ramp or when disabled.

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pUnderVoltageFaultLimit  Pointer to the under voltage fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM UnderVoltageFaultLimit
(
    PPMBUS_HANDLE_TYPE                  hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_THRESHOLD_TYPE   pUnderVoltageFaultLimit
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VOUT_UV_FAULT_LIMIT) };

    if (NULL == pUnderVoltageFaultLimit)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pUnderVoltageFaultLimit->Threshold,
                                        &pUnderVoltageFaultLimit->Device);
}


/** @brief Command: OT_FAULT_LIMIT - Reads/Writes the over temperature fault threshold.

    Gets/Sets the over temperature fault threshold.

    @param hPmbusDeviceHandle          Pointer to a PMBUS device handle
    @param pOverTemperatureFaultLimit  Pointer to the over temperature fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OverTemperatureFaultLimit
(
    PPMBUS_HANDLE_TYPE                         hPmbusDeviceHandle,
    PPMBUS_TEMPERATURE_THRESHOLD_TYPE   pOverTemperatureFaultLimit
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(OT_FAULT_LIMIT) };

    if (NULL == pOverTemperatureFaultLimit)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOverTemperatureFaultLimit->Threshold,
                                        &pOverTemperatureFaultLimit->Device);
}


/** @brief Command: OT_WARN_LIMIT - Reads/Writes the over temperature warning threshold.

    Gets/Sets the over temperature warning threshold.

    @param hPmbusDeviceHandle       	Pointer to a PMBUS device handle
    @param pOverTemperatureWarningLimit Pointer to the over temperature fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OverTemperatureWarningLimit
(
    PPMBUS_HANDLE_TYPE                  hPmbusDeviceHandle,
    PPMBUS_TEMPERATURE_THRESHOLD_TYPE   pOverTemperatureWarningLimit
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(OT_WARN_LIMIT) };

    if (NULL == pOverTemperatureWarningLimit)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOverTemperatureWarningLimit->Threshold,
                                        &pOverTemperatureWarningLimit->Device);
}


/** @brief Command: VIN_OV_FAULT_LIMIT - Reads/Writes the intput overvoltage fault threshold.

    Gets/Sets the intput overvoltage fault threshold. Changes to this setting require a write
    to the APPLY_SETTINGS command before the change will take effect.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pThreshold           Pointer to the threshold fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM InputOvervoltageFaultLimit
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pThreshold
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VIN_OV_FAULT_LIMIT) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE };

    if (NULL == pThreshold)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pThreshold, &Device);
}


/** @brief Command: VIN_UV_FAULT_LIMIT - Reads/Writes the intput undervoltage fault threshold.

    Gets/Sets the intput undervoltage fault threshold. Changes to this setting require a write
    to the APPLY_SETTINGS command before the change will take effect.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pThreshold           Pointer to the threshold fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM InputUndervoltageFaultLimit
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pThreshold
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(VIN_UV_FAULT_LIMIT) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE };

    if (NULL == pThreshold)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pThreshold, &Device);
}


/** @brief Command: IIN_OC_FAULT_LIMIT - Reads/Writes the intput overcurrent fault threshold.

    Gets/Sets the intput overcurrent fault threshold. Changes to this setting require a write
    to the APPLY_SETTINGS command before the change will take effect.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pThreshold           Pointer to the threshold fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM InputOvercurrentFaultLimit
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pThreshold
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(IIN_OC_FAULT_LIMIT) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE };

    if (NULL == pThreshold)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pThreshold, &Device);
}


/** @brief Command: TON_DELAY - Reads/Writes the delay time of output voltage during enable.

    Gets/Sets the delay time of the output voltage during enable.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pTime                Pointer to the time delay.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PowerOnTimeDelay
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_TIME_TYPE    pTime
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(TON_DELAY) };

    if (NULL == pTime)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pTime->Time,
                                        &pTime->Device);
}


/** @brief Command: TON_RISE - Reads/Writes the rise time of output voltage during enable.

    Gets/Sets the rise time of output voltage during enable.
    Changes to this setting require a write to the APPLY_SETTINGS command before
    the change will take effect.
    This function uses the value of VOUT to calculate rise time, so APPLY_SETTINGS
    must be sent after any change to the VOUT target for accurate rise time.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pTime                Pointer to the rise time.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PowerOnRiseTime
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_TIME_TYPE    pTime
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(TON_RISE) };

    if (NULL == pTime)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pTime->Time,
                                        &pTime->Device);
}


/** @brief Command: TOFF_DELAY - Reads/Writes the delay time of output voltage during disable.

    Gets/Sets the delay time of the output voltage during disable.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pTime                Pointer to the time delay.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PowerOffTimeDelay
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_TIME_TYPE    pTime
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(TOFF_DELAY) };

    if (NULL == pTime)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pTime->Time,
                                        &pTime->Device);
}


/** @brief Command: TOFF_FALL - Reads/Writes the fall time of output voltage during diable.

    Gets/Sets the fall time of output voltage during diable.
    Changes to this setting require a write to the APPLY_SETTINGS command before
    the change will take effect.
    This function uses the value of VOUT to calculate rise time, so APPLY_SETTINGS
    must be sent after any change to the VOUT target for accurate rise time.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pTime                Pointer to the fall time.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PowerOffFallTime
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_TIME_TYPE    pTime
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(TOFF_FALL) };

    if (NULL == pTime)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pTime->Time,
                                        &pTime->Device);
}


/** @brief Command: STATUS_BYTE - Returns an abbreviated status for fast reads.

    The STATUS_BYTE command returns one byte of information with a summary of the most critical faults.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pUnitStatus          Pointer to the status of the unit's condition.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetUnitsShortStatus
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle,
    PPMBUS_STATUS_BYTE_TYPE pUnitStatus
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(STATUS_BYTE) };

    if (NULL == pUnitStatus)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pUnitStatus->Status,
                                        &pUnitStatus->Device);
}


/** @brief Command: STATUS_WORD - Returns information with a summary of the unit's fault condition.

    The STATUS_WORD command returns two bytes of information with a summary of the unit's fault condition.
    Based on the information in these bytes, the host can get more information by reading the appropriate
    status registers. The low byte of the STATUS_WORD is the same register as the STATUS_BYTE (78h) command.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pUnitStatus          Pointer to the status of the unit's condition.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetUnitsFullStatus
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle,
    PPMBUS_STATUS_WORD_TYPE pUnitStatus
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(STATUS_WORD) };

    if (NULL == pUnitStatus)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pUnitStatus->Status,
                                        &pUnitStatus->Device);
}


/** @brief Command: STATUS_VOUT - Returns the Vout specific status.

    The STATUS_VOUT command returns one data byte with the status of the output voltage.

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pOutputVoltageStatus     Pointer to the output voltage status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputVoltageStatus
(
    PPMBUS_HANDLE_TYPE                  hPmbusDeviceHandle,
    PPMBUS_OUTPUT_VOLTAGE_STATUS_TYPE   pOutputVoltageStatus
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(STATUS_VOUT) };

    if (NULL == pOutputVoltageStatus)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOutputVoltageStatus->Status,
                                        &pOutputVoltageStatus->Device);
}


/** @brief Command: STATUS_IOUT - Returns the Iout specific status.

    The STATUS_IOUT command returns one data byte with the status of the output current.

    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @param pOutputCurrentStatus     Pointer to the output current status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputCurrentStatus
(
    PPMBUS_HANDLE_TYPE                  hPmbusDeviceHandle,
    PPMBUS_OUTPUT_CURRENT_STATUS_TYPE   pOutputCurrentStatus
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(STATUS_IOUT) };

    if (NULL == pOutputCurrentStatus)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOutputCurrentStatus->Status,
                                        &pOutputCurrentStatus->Device);
}


/** @brief Command: STATUS_INPUT - Returns specific status specific to the input.

    The STATUS_INPUT command returns input voltage and input current status information.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pInputStatus         Pointer to the specific input status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetInputStatus
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_STATUS_INPUT_ENUM    pInputStatus
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(STATUS_INPUT) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pInputStatus)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pInputStatus, &Device);
}


/** @brief Command: STATUS_TEMPERATURE - Returns the temperature specific status.

    The STATUS_TEMPERATURE command returns one byte of information with a summary of any
    temperature related faults or warnings.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pTemperatureStatus   Pointer to the specific temperature status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetTemperatureStatus
(
    PPMBUS_HANDLE_TYPE              hPmbusDeviceHandle,
    PPMBUS_STATUS_TEMPERATURE_TYPE  pTemperatureStatus
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(STATUS_TEMPERATURE) };

    if (NULL == pTemperatureStatus)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pTemperatureStatus->Status,
                                        &pTemperatureStatus->Device);
}


/** @brief Command: STATUS_CML - Returns the communication, memory, and logic specific status.

    The STATUS_CML command returns one byte of information with a summary of any communications, logic
    and / or memory errors.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pCmlStatus           Pointer to the communication, memory, and logic specific status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetCmlStatus
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle,
    PPMBUS_STATUS_CML_ENUM  pCmlStatus
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(STATUS_CML) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pCmlStatus)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pCmlStatus, &Device);
}


/** @brief Command: STATUS_MFR_SPECIFIC - Returns the manufacturer specific status.

    The STATUS_MFR_SPECIFIC command returns one byte of information that is manufacturer specific.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pStatus              Pointer to the manufacturer specific status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetManufacturerSpecificStatus
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_BYTE_TYPE    pStatus
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(STATUS_MFR_SPECIFIC) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pStatus)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pStatus, &Device);
}


/** @brief Command: READ_VIN - Returns the input voltage reading.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pInputVoltage        Pointer to the read input voltage level in Volts.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetInputVoltageLevel
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pInputVoltage
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_VIN) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pInputVoltage)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pInputVoltage, &Device);
}


/** @brief Command: READ_IIN - Returns the input current reading.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pInputCurrent        Pointer to the read input current level in Amps.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetInputCurrentLevel
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pInputCurrent
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_IIN) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pInputCurrent)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pInputCurrent, &Device);
}


/** @brief Command: READ_VOUT - Returns the output voltage reading.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pOutputVoltage       Pointer to the read output voltage level in Volts.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputVoltageLevel
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pOutputVoltage
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_VOUT) };

    if (NULL == pOutputVoltage)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOutputVoltage->VoltageLevel,
                                        &pOutputVoltage->Device);
}


/** @brief Command: READ_IOUT - Returns the output current reading.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pOutputCurrent       Pointer to the read output current level in Amps.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputCurrentLevel
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_CURRENT_LEVEL_TYPE   pOutputCurrent
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_IOUT) };

    if (NULL == pOutputCurrent)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOutputCurrent->CurrentLevel,
                                        &pOutputCurrent->Device);
}


/** @brief Command: READ_TEMPERATURE_1 - Returns the controller junction temperature
                                         reading from internal temperature sensor.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pTemperature         Pointer to the read temperature from internal sensors
                                in degrees celcius.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetTemperatureMonitor1
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_TEMPERATURE_TYPE pTemperature
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_TEMPERATURE_1) };

    if (NULL == pTemperature)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pTemperature->Temperature,
                                        &pTemperature->Device);
}


/** @brief Command: READ_TEMPERATURE_2 - Returns the temperature reading from
                                         external source at CH-0.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pTemperature         Pointer to the read temperature in degrees celcius.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetTemperatureMonitor2
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pTemperature
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_TEMPERATURE_2) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pTemperature)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pTemperature, &Device);
}


/** @brief Command: READ_TEMPERATURE_3 - Returns the temperature reading from
                                         external source at CH-1.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pTemperature         Pointer to the read temperature in degrees celcius.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetTemperatureMonitor3
(
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pTemperature
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_TEMPERATURE_3) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pTemperature)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pTemperature, &Device);
}


/** @brief Command: READ_POUT - Returns the output power.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pOutputPower         Pointer to the read output power in Watts.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputPower
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_POWER_TYPE   pOutputPower
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_POUT) };

    if (NULL == pOutputPower)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pOutputPower->Power,
                                        &pOutputPower->Device);
}


/** @brief Command: READ_PIN - Returns the input power.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pInputPower          Pointer to the read input power in Watts.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetInputPower
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pInputPower
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(READ_PIN) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pInputPower)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pInputPower, &Device);
}


/** @brief Command: PMBUS_REVISION - Return's the device's PMBUS revision.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pDeviceRevision      Pointer to the read device's PMBUS revision.
    @return PMBUS_STATUS_ENUM.
*/
PMBUS_STATUS_ENUM GetPmbusRevision
(
    PPMBUS_HANDLE_TYPE          hPmbusDeviceHandle,
    PPMBUS_PMBUS_REVISION_TYPE  pPmbusRevision
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(PMBUS_REVISION) };

    if (NULL == pPmbusRevision)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pPmbusRevision->Revision,
                                        &pPmbusRevision->Device);
}


/** @brief Command: MFR_ID - Return's the device's manufacturer.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pManufacturerId      Pointer to the read manufacturer Id.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetManufacturerId
(
    PPMBUS_HANDLE_TYPE              hPmbusDeviceHandle,
    PPMBUS_MANUFACTURER_INFO_TYPE   pManufacturerId
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(MFR_ID) };

    if (NULL == pManufacturerId)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pManufacturerId->ManufacturerInfo,
                                        &pManufacturerId->Device);
}


/** @brief Command: MFR_MODEL - Return's the device's model.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pDeviceModel         Pointer to the read device's model.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetDeviceModel
(
    PPMBUS_HANDLE_TYPE              hPmbusDeviceHandle,
    PPMBUS_MANUFACTURER_INFO_TYPE   pDeviceModel
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(MFR_MODEL) };

    if (NULL == pDeviceModel)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pDeviceModel->ManufacturerInfo,
                                        &pDeviceModel->Device);
}


/** @brief Command: MFR_DATE - Return's the device's manufacturing date in YYMMDD format.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pManufacturingDate   Pointer to the read device's manufacturing date.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetManufacturingDate
(
    PPMBUS_HANDLE_TYPE              hPmbusDeviceHandle,
    PPMBUS_MANUFACTURER_INFO_TYPE   pManufacturingDate
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(MFR_DATE) };

    if (NULL == pManufacturingDate)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle,
                                        &CommandInfo,
                                        &pManufacturingDate->ManufacturerInfo,
                                        &pManufacturingDate->Device);
}



/** @brief Command: IC_DEVICE_ID - Return's the device Id.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pDeviceId            Pointer to the read device id.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetDeviceId
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_BLOCK_TYPE   pDeviceId
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(IC_DEVICE_ID) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pDeviceId)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pDeviceId, &Device);
}


/** @brief Command: IC_DEVICE_REV - Return's the device's revision.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pDeviceRevision      Pointer to the read device's revision.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetDeviceRevision
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_BLOCK_TYPE   pDeviceRevision
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(IC_DEVICE_REV) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ };

    if (NULL == pDeviceRevision)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pDeviceRevision, &Device);
}


/** @brief Command: APPLY_SETTINGS - Applies the updated settings.

    The APPLY_SETTINGS command instruct the controller to one byte of information that is manufacturer specific.

    The commands that require this are VOUT_TRANSITION_RATE, VOUT_DROOP, VOUT_OV_FAULT_LIMIT, VIN_OV_FAULT_LIMIT,
    VIN_UV_FAULT_LIMIT, IIN_OC_FAULT_LIMIT, TON_RISE, and TOFF_FALL.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pSettings            Pointer to the settings to be applied.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM ApplySettings
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_WORD_TYPE    pSettings
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(APPLY_SETTINGS) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE };

    if (NULL == pSettings)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pSettings, &Device);
}

/** @brief Command: RESTORE_CONFIG - Restore configuration from NVM.

    The RESTORE_CONFIG command identifies the configuration to be restored from NVM
    and loads the store's settings into the device's active memory.

    @param hPmbusDeviceHandle   Pointer to a PMBUS device handle
    @param pConfig              Pointer to the config to restore.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM RestoreConfig
(
    PPMBUS_HANDLE_TYPE  hPmbusDeviceHandle,
    PPMBUS_BYTE_TYPE    pConfig
)
{
    PMBUS_COMMAND_INFO_TYPE CommandInfo = { SET_PMBUS_COMMAND_INFO(APPLY_SETTINGS) };
    PMBUS_PAGE_CHANNEL_SELECT_TYPE Device = { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE };

    if (NULL == pConfig)
    {
        return PMBUS_STATUS_INVALID_PARAMETER_2;
    }

    // execute the command
    return PmbusGenericExecuteCommand(hPmbusDeviceHandle, &CommandInfo, pConfig, &Device);
}

/** @brief Command: PmbusConfigInit - configuration when booting.

    1. Sets the voltage for all CVR rails to nominal (930mV)
    2. Wait 500 uSec. It's use here is for demonstration purposes only.
    3. Enable all CVR rails
    4. Set APC's overvoltage limit to 1.355V
    5. Set VOUT_MAX to 1200mV
    6. Set APC's undervoltage limit to 450mV
    7. Set VOUT_MIN to 550mV
    8.  Set the control to AVSBus for PM_PMBUS_APC_RAIL_CBF
    9.  Set the control to AVSBus for PM_PMBUS_APC_RAIL_APC
 */

PMBUS_STATUS_ENUM PmbusConfigInit(PPMBUS_HANDLE_TYPE hPmbusDeviceHandle)
{
    if (!hPmbusDeviceHandle)
    {
        return PMBUS_STATUS_INVALID_HANDLE;
    }

    //set 930mv
    PMBUS_VOLTAGE_LEVEL_TYPE VoltageOutputConfigurationWrite = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, 930 };
    VoltageOutput(hPmbusDeviceHandle, &VoltageOutputConfigurationWrite);

    //debug to test if write good
    PMBUS_VOLTAGE_LEVEL_TYPE VoltageOutputConfigurationRead = { { PMBUS_PAGE_CHANNEL_SELECT_0, PMBUS_ACCESS_TYPE_READ }, 0 };
    VoltageOutput(hPmbusDeviceHandle, &VoltageOutputConfigurationRead);

    //enable all rails
    PMBUS_OPERATION_CONFIGURATION_TYPE OperationConfigurationWrite = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, PMBUS_OPERATION_ON_NOMINAL };
    OperationConfigurationWrite.OperationMode = PMBUS_OPERATION_ON_NOMINAL;
    Operation(hPmbusDeviceHandle, &OperationConfigurationWrite);

    //Set APC's overvoltage limit to 1.355V
    PMBUS_VOLTAGE_THRESHOLD_TYPE OvervoltageFaultLimitWrite = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, 1355 };
    OverVoltageFaultLimit(hPmbusDeviceHandle, &OvervoltageFaultLimitWrite);

    //debug
    PMBUS_VOLTAGE_THRESHOLD_TYPE OvervoltageFaultLimitRead = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ }, 0};
    OverVoltageFaultLimit(hPmbusDeviceHandle, &OvervoltageFaultLimitRead);

    //Set VOUT_MAX to 1200mV
    PMBUS_VOLTAGE_LEVEL_TYPE MaximumOutputVoltageWrite = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, 1200 };
    MaximumOutputVoltage(hPmbusDeviceHandle, &MaximumOutputVoltageWrite);

    //debug
    PMBUS_VOLTAGE_LEVEL_TYPE MaximumOutputVoltageRead = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ }, 0 };
    MaximumOutputVoltage(hPmbusDeviceHandle, &MaximumOutputVoltageRead);

    //Set APC's undervoltage limit to 450mV
    PMBUS_VOLTAGE_THRESHOLD_TYPE UnderVoltageFaultLimitWrite = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, 450 };
    UnderVoltageFaultLimit(hPmbusDeviceHandle, &UnderVoltageFaultLimitWrite);

    //debug
    PMBUS_VOLTAGE_THRESHOLD_TYPE UnderVoltageFaultLimitRead = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ }, 0 };
    UnderVoltageFaultLimit(hPmbusDeviceHandle, &UnderVoltageFaultLimitRead);

    //Set VOUT_MIN to 550mV
    PMBUS_VOLTAGE_LEVEL_TYPE MinimumOutputVoltageWrite = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, 550 };
    MinimumOutputVoltage(hPmbusDeviceHandle, &MinimumOutputVoltageWrite);

    //debug
    PMBUS_VOLTAGE_LEVEL_TYPE MinimumOutputVoltageRead = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ }, 0 };
    MinimumOutputVoltage(hPmbusDeviceHandle, &MinimumOutputVoltageRead);

    //Set control to AVSBus
    OperationConfigurationWrite.OperationMode = PMBUS_OPERATION_SWITCH_TO_AVSBUS_CONTROL;
    Operation(hPmbusDeviceHandle, &OperationConfigurationWrite);

    return PMBUS_STATUS_SUCCESS;
}

static int PmbusSetVoltage(int num, int voltage)
{
    PMBUS_PAGE_CHANNEL_SELECT_ENUM channel;
    channel = num==0?PMBUS_PAGE_CHANNEL_SELECT_0:PMBUS_PAGE_CHANNEL_SELECT_1;
    if(voltage == 0){
        PMBUS_VOLTAGE_LEVEL_TYPE VoltageOutputConfigurationRead = { { channel, PMBUS_ACCESS_TYPE_READ }, voltage };
        VoltageOutput(&hPmbusDeviceHandle, &VoltageOutputConfigurationRead);
        return VoltageOutputConfigurationRead.VoltageLevel;
    }else{
        PMBUS_VOLTAGE_LEVEL_TYPE VoltageOutputConfigurationWrite = { { channel, PMBUS_ACCESS_TYPE_WRITE }, voltage };
        VoltageOutput(&hPmbusDeviceHandle, &VoltageOutputConfigurationWrite);
        return VoltageOutputConfigurationWrite.VoltageLevel;
    }
    return 0;
}

static int PmbusSwitchMode(int num)
{
    PMBUS_OPERATION_ENUM mode = PMBUS_OPERATION_ON_NOMINAL;
    if(num == 0){
        PMBUS_OPERATION_CONFIGURATION_TYPE Operationmode = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ }, mode };
        Operation(&hPmbusDeviceHandle, &Operationmode);
        if(Operationmode.OperationMode == 136){
            printf("  pmbus controls cvr\n");
        }else if(Operationmode.OperationMode == 184){
            printf(" avsbus controls cvr\n");
        }
    }else if(num == 1){
        PMBUS_OPERATION_CONFIGURATION_TYPE Operationmode = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, PMBUS_OPERATION_ON_NOMINAL };
        Operation(&hPmbusDeviceHandle, &Operationmode);
        printf(" cvr control switchs to pmbus\n");
    }else if(num == 2){
        PMBUS_OPERATION_CONFIGURATION_TYPE Operationmode = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, PMBUS_OPERATION_SWITCH_TO_AVSBUS_CONTROL };
        Operation(&hPmbusDeviceHandle, &Operationmode);
        printf(" cvr control switchs to avsbus\n");
    }
    return 0;
}

int do_pmbus(int argc, char *argv[])
{
    int ret = 0, num = 0;
    PMBUS_PAGE_CHANNEL_SELECT_ENUM channel = PMBUS_PAGE_CHANNEL_SELECT_0;
    PMBUS_ACCESS_TYPE_ENUM access = PMBUS_ACCESS_TYPE_READ;
    PMBUS_OPERATION_ENUM mode = PMBUS_OPERATION_ON_NOMINAL;
    PMBUS_STATUS_ENUM result = PMBUS_STATUS_INVALID;

    int i = 0;
    for (i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "cbf") == 0) {
            channel = PMBUS_PAGE_CHANNEL_SELECT_0;
        }else if (strcmp(argv[i], "cpu") == 0){
            channel = PMBUS_PAGE_CHANNEL_SELECT_1;
        }else if (strcmp(argv[i], "all") == 0){
            channel = PMBUS_PAGE_CHANNEL_SELECT_ALL;
        }else if (strcmp(argv[i], "read") == 0){
            access = PMBUS_ACCESS_TYPE_READ;
        }else if (strcmp(argv[i], "write") == 0){
            access = PMBUS_ACCESS_TYPE_WRITE;
        }else if (strcmp(argv[i], "rw") == 0){
            access = PMBUS_ACCESS_TYPE_READ_WRITE;
        }else if (strcmp(argv[i], "nominal") == 0){
            mode = PMBUS_OPERATION_ON_NOMINAL;
        }else if (strcmp(argv[i], "avsbus") == 0){
            mode = PMBUS_OPERATION_SWITCH_TO_AVSBUS_CONTROL;
        }else if (strtoul(argv[i], NULL, 0) < 1500){
            num = strtoul(argv[i], NULL, 0);
        }else {
            printf("Unknown command '%s'\n\n", argv[i]);
            ret = -1;
        }
    }
    if (argc == 1) {
        printf("Unknown command '%s'\n\n", argv[0]);
    }else {
        if (strcmp(argv[1], "open") == 0) {
            result = PmbusOpen(&hPmbusDeviceHandle);
            if(result == PMBUS_STATUS_INVALID_HANDLE){
                printf(" pmbus is already open!\n");
            }else if(result == PMBUS_STATUS_SUCCESS){
                printf(" pmbus is open!\n");
            }
        }else if (strcmp(argv[1], "close") == 0){
            PmbusClose(&hPmbusDeviceHandle);
            printf(" pmbus is closed!\n");
        }else if (strcmp(argv[1], "APC") == 0){
            if(num > 1055){
                printf("APC Voltage %dmv is set too high!\n",num);
                ret = -1;
            }else{
                ret = PmbusSetVoltage(1,num);
                printf(" APC voltage is %d\n",ret);
            }
        }else if (strcmp(argv[1], "CBF") == 0){
            if(num > 1055){
                printf("CBF Voltage %dmv is set too high!\n",num);
                ret = -1;
            }else{
                ret = PmbusSetVoltage(0,num);
                printf(" CBF voltage is %d\n",ret);
            }
        }else if (strcmp(argv[1], "AVS") == 0){
            PmbusSwitchMode(num);
        }else if (strcmp(argv[1], "operation") == 0) {
            PMBUS_OPERATION_CONFIGURATION_TYPE Operationmode = { { channel, access }, mode };
            Operation(&hPmbusDeviceHandle, &Operationmode);
            printf(" pmbus margin mode is %d!\n",Operationmode.OperationMode);
        }else if (strcmp(argv[1], "onoff") == 0){
            PMBUS_OPERATION_OUTPUT_CONFIGURATION_TYPE OperationConfig = { { channel, access }, num };
            OperationOutput(&hPmbusDeviceHandle, &OperationConfig);
            printf(" EN pin and pmbus commands: %d turn the unit ON/OFF!\n", OperationConfig.OperationOutput);
        }else if (strcmp(argv[1], "page") == 0) {
            PMBUS_PAGE_CHANNEL_SELECT_TYPE command = { channel, access };
            PageChannelSelect(&hPmbusDeviceHandle, &command);
            printf(" set channel %d to %d \n", command.PageChannelSelect, command.BusAccessType);
        }else if (strcmp(argv[1], "clear") == 0) {
            ClearFaults(&hPmbusDeviceHandle);
            printf(" fault indications are clear!\n");
        }else if (strcmp(argv[1], "setvout") == 0) {
            PMBUS_VOLTAGE_LEVEL_TYPE VoltageOutputConfig = { { channel, access }, num };
            VoltageOutput(&hPmbusDeviceHandle, &VoltageOutputConfig);
            printf(" normal voltage %d is set\n", VoltageOutputConfig.VoltageLevel);
        }else if (strcmp(argv[1], "trim") == 0) {
            PMBUS_VOUT_CAL_OFFSET_TYPE FixedVoltageOffset = { { channel, access }, num };
            OutputVoltageCalibrateOffset(&hPmbusDeviceHandle, &FixedVoltageOffset);
            printf(" fiexed offset voltage %d is set\n", FixedVoltageOffset.VoltageOffset);
        }else if (strcmp(argv[1], "maxvout") == 0) {
            PMBUS_VOLTAGE_LEVEL_TYPE MaxOutputVolt = { { channel, access }, num };
            MaximumOutputVoltage(&hPmbusDeviceHandle, &MaxOutputVolt);
            printf(" max output voltage %d is set\n", MaxOutputVolt.VoltageLevel);
        }else if (strcmp(argv[1], "minvout") == 0) {
            PMBUS_VOLTAGE_LEVEL_TYPE MinOutputVolt = { { channel, access }, num };
            MinimumOutputVoltage(&hPmbusDeviceHandle, &MinOutputVolt);
            printf(" max output voltage %d is set\n", MinOutputVolt.VoltageLevel);
        }else if (strcmp(argv[1], "highmarg") == 0) {
            PMBUS_VOUT_MARGIN_TYPE HighOutputVoltageMargin = { { channel, access }, num };
            OutputVoltageHighMargin(&hPmbusDeviceHandle, &HighOutputVoltageMargin);
            printf(" high output voltage margin %d is set\n", HighOutputVoltageMargin.VoltageMargin);
        }else if (strcmp(argv[1], "lowmarg") == 0) {
            PMBUS_VOUT_MARGIN_TYPE LowOutputVoltageMargin = { { channel, access }, num };
            OutputVoltageLowMargin(&hPmbusDeviceHandle, &LowOutputVoltageMargin);
            printf(" low output voltage margin %d is set\n", LowOutputVoltageMargin.VoltageMargin);
        }else if (strcmp(argv[1], "rate") == 0) {
            PMBUS_VOLTAGE_TRANSITION_RATE_TYPE OutputVoltTransRate = { { channel, access }, num };
            OutputVoltageTransitionRate(&hPmbusDeviceHandle, &OutputVoltTransRate);
            printf(" TransRate %d is set\n", OutputVoltTransRate.TransitionRate);
        }else if (strcmp(argv[1], "ovout") == 0) {
            PMBUS_VOLTAGE_THRESHOLD_TYPE OvervoltFaultLimit = { { channel, access }, num };
            OverVoltageFaultLimit(&hPmbusDeviceHandle, &OvervoltFaultLimit);
            printf(" over faultlimit is %d\n", OvervoltFaultLimit.Threshold);
        }else if (strcmp(argv[1], "uvout") == 0) {
            PMBUS_VOLTAGE_THRESHOLD_TYPE UnderVoltFaultLimit = { { channel, access }, num };
            UnderVoltageFaultLimit(&hPmbusDeviceHandle, &UnderVoltFaultLimit);
            printf(" under faultlimit is %d\n", UnderVoltFaultLimit.Threshold);
        }else if (strcmp(argv[1], "status") == 0) {
            PMBUS_VOLTAGE_DROOP_TYPE OutputVoltDroop = { { channel, access }, num };
            OutputVoltageDroop(&hPmbusDeviceHandle, &OutputVoltDroop);
            printf(" droop info is %d\n", OutputVoltDroop.VoltageDroop);

            PMBUS_STATUS_BYTE_TYPE UnitStatus = { { channel, access }, num };
            GetUnitsShortStatus(&hPmbusDeviceHandle, &UnitStatus);
            printf(" ShortUnitStatus info is %d\n", UnitStatus.Status);

            PMBUS_STATUS_WORD_TYPE FullUnitStatus = { { channel, access }, num };
            GetUnitsFullStatus(&hPmbusDeviceHandle, &FullUnitStatus);
            printf(" FullUnitStatus info is %d\n", FullUnitStatus.Status);

            PMBUS_OUTPUT_VOLTAGE_STATUS_TYPE OutputVoltStatus = { { channel, access }, num };
            GetOutputVoltageStatus(&hPmbusDeviceHandle, &OutputVoltStatus);
            printf(" VoutStatus info is %d\n", OutputVoltStatus.Status);

            PMBUS_OUTPUT_CURRENT_STATUS_TYPE OutputCurrentStatus = { { channel, access }, num };
            GetOutputCurrentStatus(&hPmbusDeviceHandle, &OutputCurrentStatus);
            printf(" IoutStatus info is %d\n", OutputVoltStatus.Status);

            PMBUS_STATUS_INPUT_ENUM InputStatus = PMBUS_STATUS_INPUT_INVALID;
            GetInputStatus(&hPmbusDeviceHandle, &InputStatus);
            printf(" IputStatus info is %d\n", InputStatus);

            PMBUS_STATUS_TEMPERATURE_TYPE TemperatureStatus = { { channel, access }, num };
            GetTemperatureStatus(&hPmbusDeviceHandle, &TemperatureStatus);
            printf(" TemperatureStatus info is %d\n", TemperatureStatus.Status);

            PMBUS_STATUS_CML_ENUM CmlStatus = PMBUS_STATUS_CML_INVALID;
            GetCmlStatus(&hPmbusDeviceHandle, &CmlStatus);
            printf(" CmlStatus info is %d\n", CmlStatus);
        }else if (strcmp(argv[1], "info") == 0) {
            PMBUS_PMBUS_REVISION_TYPE PmbusRevision = { { channel, access }, num };
            GetPmbusRevision(&hPmbusDeviceHandle, &PmbusRevision);
            printf(" pmbus reversion is %u\n", PmbusRevision.Revision);

            PMBUS_MANUFACTURER_INFO_TYPE ManufacturingId = { { channel, access }, num };
            GetManufacturerId(&hPmbusDeviceHandle, &ManufacturingId);
            printf(" ManufacturingId is %u\n", ManufacturingId.ManufacturerInfo);

            PMBUS_MANUFACTURER_INFO_TYPE DeviceModel = { { channel, access }, num };
            GetDeviceModel(&hPmbusDeviceHandle, &DeviceModel);
            printf(" DeviceModel is %u\n", DeviceModel.ManufacturerInfo);

            PMBUS_MANUFACTURER_INFO_TYPE ManufacturingDate = { { channel, access }, num };
            GetManufacturingDate(&hPmbusDeviceHandle, &ManufacturingDate);
            printf(" ManufacturingDate is %u\n", ManufacturingDate.ManufacturerInfo);

            PMBUS_BLOCK_TYPE DeviceId = 0;
            GetDeviceId(&hPmbusDeviceHandle, &DeviceId);
            printf(" DeviceId is %u\n", DeviceId);

            PMBUS_BLOCK_TYPE DeviceRevision = 0;
            GetDeviceRevision(&hPmbusDeviceHandle, &DeviceRevision);
            printf(" DeviceRevision is %u\n", DeviceRevision);
        }else if (strcmp(argv[1], "vin") == 0) {
            PMBUS_WORD_TYPE InputVoltage = 0;
            GetInputVoltageLevel(&hPmbusDeviceHandle, &InputVoltage);
            printf(" input voltage is %d\n", InputVoltage);
        }else if (strcmp(argv[1], "iin") == 0) {
            PMBUS_WORD_TYPE InputCurrent = 0;
            GetInputCurrentLevel(&hPmbusDeviceHandle, &InputCurrent);
            printf(" input current is %d\n", InputCurrent);
        }else if (strcmp(argv[1], "vout") == 0) {
            PMBUS_VOLTAGE_LEVEL_TYPE OutputVoltage = { { channel, access }, num };
            GetOutputVoltageLevel(&hPmbusDeviceHandle, &OutputVoltage);
            printf(" output voltage is %d\n", OutputVoltage.VoltageLevel);
        }else if (strcmp(argv[1], "iout") == 0) {
            PMBUS_CURRENT_LEVEL_TYPE OutputCurrent = { { channel, access }, num };
            GetOutputCurrentLevel(&hPmbusDeviceHandle, &OutputCurrent);
            printf(" output current is %d\n", OutputCurrent.CurrentLevel);
        }else if (strcmp(argv[1], "temp") == 0) {
            PMBUS_TEMPERATURE_TYPE Temp1 = { { channel, access }, num };
            GetTemperatureMonitor1(&hPmbusDeviceHandle, &Temp1);
            printf(" Temperature1 is %d\n", Temp1.Temperature);
        }else if (strcmp(argv[1], "pout") == 0) {
            PMBUS_POWER_TYPE OutputPower = { { channel, access }, num };
            GetOutputPower(&hPmbusDeviceHandle, &OutputPower);
            printf(" OutputPower is %d\n", OutputPower.Power);
        }else if (strcmp(argv[1], "pin") == 0) {
            PMBUS_WORD_TYPE InputPower = 0;
            GetInputPower(&hPmbusDeviceHandle, &InputPower);
            printf(" InputPower is %d\n", InputPower);
        }else {
            printf("Unknown command\n\n");
            ret = -1;
        }
    }
    return ret;
}

int pmbus_init(void)
{
    PmbusOpen(&hPmbusDeviceHandle);

    /* FULL_FAULT STATUS */
    PMBUS_STATUS_WORD_TYPE FullUnitStatus = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_READ }, 0 };
    GetUnitsFullStatus(&hPmbusDeviceHandle, &FullUnitStatus);
    if (0x0 != FullUnitStatus.Status) {
        printf("PMBUS FullUnitStatus info is %d\n", FullUnitStatus.Status);
    }

    /* OPERATION NOMINAL */
    PMBUS_OPERATION_CONFIGURATION_TYPE OperationmodeNominal = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, PMBUS_OPERATION_ON_NOMINAL };
    Operation(&hPmbusDeviceHandle, &OperationmodeNominal);

    /* VOUT_OV_FAULT_LIMIT 1355mV */
    PMBUS_VOLTAGE_THRESHOLD_TYPE OvervoltFaultLimit = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, 1355 };
    OverVoltageFaultLimit(&hPmbusDeviceHandle, &OvervoltFaultLimit);

    /* VOUT_MARGIN_HIGH 950mV */
    PMBUS_VOUT_MARGIN_TYPE HighOutputVoltageMargin = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, 950 };
    OutputVoltageHighMargin(&hPmbusDeviceHandle, &HighOutputVoltageMargin);

    /* VOUT_MAX 1200mV */
    PMBUS_VOLTAGE_LEVEL_TYPE MaxOutputVolt = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, 1200 };
    MaximumOutputVoltage(&hPmbusDeviceHandle, &MaxOutputVolt);

    /* VOUT_COMMAND 1055mV */
    PMBUS_VOLTAGE_LEVEL_TYPE VoltageOutputConfigAPC = { { PMBUS_PAGE_CHANNEL_SELECT_1, PMBUS_ACCESS_TYPE_WRITE }, 1055 };
    VoltageOutput(&hPmbusDeviceHandle, &VoltageOutputConfigAPC);

    PMBUS_VOLTAGE_LEVEL_TYPE VoltageOutputConfigCBF = { { PMBUS_PAGE_CHANNEL_SELECT_0, PMBUS_ACCESS_TYPE_WRITE }, 1055 };
    VoltageOutput(&hPmbusDeviceHandle, &VoltageOutputConfigCBF);

    /* OPERATION AVSBUS */
    PMBUS_OPERATION_CONFIGURATION_TYPE OperationmodeAvsbus = { { PMBUS_PAGE_CHANNEL_SELECT_ALL, PMBUS_ACCESS_TYPE_WRITE }, PMBUS_OPERATION_SWITCH_TO_AVSBUS_CONTROL };
    Operation(&hPmbusDeviceHandle, &OperationmodeAvsbus);

    return 0;
}

MK_CMD(pmbus, do_pmbus, "pmbus initialization, set or get voltage, get temp or power",
    "pmbus open\n"
    "    - open pmbus\n"
    "pmbus close\n"
    "    - close pmbus\n"
    "pmbus APC voltage\n"
    "    - set APC rail voltage(mV)\n"
    "pmbus CBF voltage\n"
    "    - set CBF rail voltage(mV)\n"
    "pmbus AVS '1/2'\n"
    "    - 1:  pmbus controls cvr\n"
    "    - 2: avsbus controls cvr\n"
    "pmbus page\n"
    "    - selects page channel 0, 1 or both\n"
    "pmbus operation\n"
    "    - set enable, disable and Vout margin modes\n"
    "pmbus onoff\n"
    "    - configure the EN pin and pmbus commands to turn the unit ON/OFF\n"
    "pmbus clear\n"
    "    - clears fault indications\n"
    "pmbus setvout\n"
    "    - set the nominal value of the output voltage\n"
    "pmbus trim\n"
    "    - apply a fixed offset voltage to the output voltage command value\n"
    "pmbus maxvout\n"
    "    - set the maximum possible value of Vout\n"
    "pmbus highmarg\n"
    "    - set the value of the Vout during a marging high\n"
    "pmbus lowmarg\n"
    "    - set the value of the Vout during a marging low\n"
    "pmbus rate\n"
    "    - set the transition rate during margin or other change of Vout\n"
    "pmbus status\n"
    "    - read pmbus status\n"
    "pmbus minvout\n"
    "    - set the minimum possible value of Vout\n"
    "pmbus ovout\n"
    "    - read the Vout overvoltage fault threshold\n"
    "pmbus uvout\n"
    "    - read the Vout undervoltage fault threshold\n"
    "pmbus info\n"
    "	 - read pmbus revision\n"
    "pmbus vin\n"
    "	 - read input voltage \n"
    "pmbus iin\n"
    "	 - read input current \n"
    "pmbus vout\n"
    "	 - read output voltage \n"
    "pmbus iout\n"
    "	 - read output current \n"
    "pmbus temp\n"
    "	 - read pmbus temperature \n"
    "pmbus pin\n"
    "	 - read input power \n"
    "pmbus pout\n"
    "	 - read output power \n"
);
