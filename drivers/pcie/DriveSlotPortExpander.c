/** @file

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

**/
//#include <PiDxe.h>
//#include <Library/UefiBootServicesTableLib.h>
//#include <Library/DebugLib.h>
//#include <Protocol/PcieConfigProtocol.h>
#include "DriveSlotPortExpander.h"
//#include "PcieConfigDxe.h"
#include "PcieI2cIo.h"
//#include "hdts_shell.h"
//#include <UefiBaseType.h>



#define PIN_POWER                 0
#define PIN_PRSNT                 1
#define PIN_PERST                 2
#define PIN_ATTENTION_LED         3

#define PIN_POWER_MASK            (1 << (PIN_POWER * 2)) //active low
#define PIN_PERST_MASK            (1 << (PIN_PERST * 2)) //active low
#define PIN_PRSNT_MASK            (1 << (PIN_PRSNT * 2)) //active low
#define PIN_ATTENTION_LED_MASK    (1 << (PIN_ATTENTION_LED * 2)) //active low

typedef enum {
  SignalOff = 0,
  SignalOn = 1,
  SignalToggling = 2
} SLOT_SIGNAL_STATE;

#pragma pack(1)
typedef struct {
  UINT8 Address;
  UINT8 Value;
} PE_REGISTER;
#pragma pack(0)
/**
  Set up port expander operation

  @param[in]     Address    I2C slave address

  @retval EFI_STATUS Indicating success or failure
**/

STATIC CONST UINT8 PeInitSequence[] = {
  //control word including first register address in sequence
  (REG_PCA9551_PSC0 | AUTO_INCREMENT),
  //data to init sequence
  //Frequence prescaler 0 - 1 Hz
  0x25,
  //Pulse Width Modulation 0 - 50%
  0x80,
  //Frequency Prescaler 1 - 2Hz
  0x16,
  //Pulse Width Modulation 1 - 50%
  0x80,
  //LED selector 0
  (PIN_PRSNT_MASK | PIN_ATTENTION_LED_MASK),
  //LED selector 1
  (PIN_PRSNT_MASK | PIN_ATTENTION_LED_MASK)
};

EFI_STATUS DriveSlotPortExpander_Configure(UINTN Address)
{
  return PcieI2cIoWrite(Address, (UINT8*)PeInitSequence, sizeof(PeInitSequence));
}

/**
Set a pins state (on/off/toggling)

@param[in]     Address    I2C slave address and port bank encoded address
@param[in]     State      PinOn/PinOff/PinToggling
@param[in]     Pin        Pin id (0-7)

@retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS DriveSlotPortExpander_SetPinState(UINTN Address, SLOT_SIGNAL_STATE State, UINT8 Pin)
{
  EFI_STATUS Status;
  UINT8 Port;
  UINTN SlaveAddress;
  PE_REGISTER Register;

  if (Pin > PIN_ATTENTION_LED) {
    return EFI_INVALID_PARAMETER;
  }
  //Extract the port and slave address
  Port = (Address & 0x01);
  SlaveAddress = (Address >> 1);

  //Read the current port value
  Register.Address = REG_PCA9551_LS0 + Port;
  Status = PcieI2cIoWriteRead(SlaveAddress,
    &Register.Address,
    sizeof(Register.Address),
    &Register.Value,
    sizeof(Register.Value));
  if (!EFI_ERROR(Status)) {
    //AndThenOr
    Register.Value &= ~(3 << (Pin << 1));
    Register.Value |= (State << (Pin << 1));
    //Write back
    Status = PcieI2cIoWrite(SlaveAddress,
      (UINT8*)&Register,
      sizeof(Register));
  }
  return Status;
}

//QCOM_PCIE_CONFIG_SLOT_SIGNAL_PROTOCOL implementation

EFI_STATUS
EFIAPI
DriveSlotAttentionIndicator(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
)
{

  return DriveSlotPortExpander_SetPinState(SlotSignalPortAddress,
    Enable ? SignalOn : SignalOff,
    PIN_ATTENTION_LED);
}

EFI_STATUS
EFIAPI
DriveSlotPowerIndicator(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
)
{
  return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
DriveSlotPERST(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
)
{

  return DriveSlotPortExpander_SetPinState(SlotSignalPortAddress,
    Enable ? SignalOff : SignalOn,
    PIN_PERST);
}

EFI_STATUS
EFIAPI
DriveSlotPower(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
)
{
  EFI_STATUS Status;

  Status = DriveSlotPortExpander_SetPinState(SlotSignalPortAddress,
    (Enable ? SignalOn : SignalOff),
    PIN_POWER);
  return Status;
}

EFI_STATUS
EFIAPI
DriveSlotPRSNT(
  IN UINTN SlotSignalPortAddress ,
  OUT BOOLEAN *Enable
)
{
  EFI_STATUS Status;
  UINT8 Port;
  UINTN SlaveAddress;
  PE_REGISTER Register;

  if (Enable == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //Extract the port and slave address
  Port = (SlotSignalPortAddress & 0x01);
  SlaveAddress = (SlotSignalPortAddress >> 1);

  //Read the current port value
  Register.Address = REG_PCA9551_INPUT;
  Status = PcieI2cIoWriteRead(SlaveAddress,
    &Register.Address,
    sizeof(Register.Address),
    &Register.Value,
    sizeof(Register.Value));
  if (!EFI_ERROR(Status)) {
    *Enable = !((BOOLEAN)(Register.Value & (1 << (PIN_PRSNT + (Port * 4) ))));
  }

  return Status;
}

EFI_STATUS
EFIAPI
DriveSlotPowerFault(
  IN UINTN SlotSignalPortAddress ,
  OUT BOOLEAN                           *Enable
)
{
  if (Enable == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  //PowerFault not handled
  *Enable = FALSE;
  return EFI_SUCCESS;
}
