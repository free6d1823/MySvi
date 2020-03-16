/** @file

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

**/
//#include <PiDxe.h>
//#include <Library/UefiBootServicesTableLib.h>
//#include <Library/DebugLib.h>
//#include <Protocol/PcieConfigProtocol.h>
//#include "PcieConfigDxe.h"
#include "PcieI2cIo.h"
#include "PcieSlotPortExpander.h"
#include <target/uefi_wrapper.h>



#define PIN_POWER                 0
#define PIN_PERST                 1
#define PIN_POWER_FAULT           2
#define PIN_MRL                   3
#define PIN_ATTENTION_BUTTON      4
#define PIN_PRSNT                 5
#define PIN_ATTENTION_LED         6
#define PIN_POWER_LED             7

#define PIN_POWER_MASK            (1 << PIN_POWER)
#define PIN_PERST_MASK            (1 << PIN_PERST)
#define PIN_POWER_FAULT_MASK      (1 << PIN_POWER_FAULT)
#define PIN_MRL_MASK              (1 << PIN_MRL)
#define PIN_ATTENTION_BUTTON_MASK (1 << PIN_ATTENTION_BUTTON)
#define PIN_PRSNT_MASK            (1 << PIN_PRSNT)
#define PIN_ATTENTION_LED_MASK    (1 << PIN_ATTENTION_LED)
#define PIN_POWER_LED_MASK        (1 << PIN_POWER_LED)

typedef enum {
  SignalOn,
  SignalOff,
  SignalToggling
} SLOT_SIGNAL_STATE;

typedef struct {
  UINT8 RegTOn;
  UINT8 RegTOff;
} LED_PIN_REG;

#pragma pack(1)
typedef struct {
  UINT8 Address;
  UINT8 Value;
} PE_REGISTER;
#pragma pack(0)

LED_PIN_REG gLedPinReg[16] = {
  {REG_TON0, REG_OFF0},
  {REG_TON1, REG_OFF1},
  {REG_TON2, REG_OFF2},
  {REG_TON3, REG_OFF3},
  {REG_TON4, REG_OFF4},
  {REG_TON5, REG_OFF5},
  {REG_TON6, REG_OFF6},
  {REG_TON7, REG_OFF7},
  {REG_TON8, REG_OFF8},
  {REG_TON9, REG_OFF9},
  {REG_TON10, REG_OFF10},
  {REG_TON11, REG_OFF11},
  {REG_TON12, REG_OFF12},
  {REG_TON13, REG_OFF13},
  {REG_TON14, REG_OFF14},
  {REG_TON15, REG_OFF15}
};

PE_REGISTER mPeInit[] = {
  //Set clock @Internal 2MHz, no output
  {REG_CLOCK, 0x40},
  //Enable LED clk
  {REG_MISC, 0x20},
  //Enable inputbuffer for all pins
  {REG_INPUTDISABLE_A, 0x00},
  {REG_INPUTDISABLE_B, 0x00},
  //Set open drain for LEDs
  {REG_OPENDRAIN_A, (PIN_ATTENTION_LED_MASK | PIN_POWER_LED_MASK)},
  {REG_OPENDRAIN_B, (PIN_ATTENTION_LED_MASK | PIN_POWER_LED_MASK)},
  //Set LED driver enable
  {REG_LEDDRIVERENABLE_A, (PIN_ATTENTION_LED_MASK | PIN_POWER_LED_MASK)},
  {REG_LEDDRIVERENABLE_B, (PIN_ATTENTION_LED_MASK | PIN_POWER_LED_MASK)},
  //Set data register, LED's and PERST are active low, POWER active high/
  {REG_DATA_A, (PIN_ATTENTION_LED_MASK | PIN_POWER_MASK)},
  {REG_DATA_B, (PIN_ATTENTION_LED_MASK | PIN_POWER_MASK)},
  //Set direction register
  {REG_DIR_A, (PIN_POWER_FAULT_MASK | PIN_MRL_MASK | PIN_ATTENTION_BUTTON_MASK | PIN_PRSNT_MASK)},
  {REG_DIR_B, (PIN_POWER_FAULT_MASK | PIN_MRL_MASK | PIN_ATTENTION_BUTTON_MASK | PIN_PRSNT_MASK)},
  //Set interrupt mask
  {REG_INTERRUPTMASK_A, ~(PIN_POWER_FAULT_MASK | PIN_MRL_MASK | PIN_ATTENTION_BUTTON_MASK | PIN_PRSNT_MASK)},
  {REG_INTERRUPTMASK_B, ~(PIN_POWER_FAULT_MASK | PIN_MRL_MASK | PIN_ATTENTION_BUTTON_MASK | PIN_PRSNT_MASK)},
  //Set interrupt sense
  {REG_SENSEHIGH_A, 0x0A},
  {REG_SENSELOW_A, 0x0A},
  {REG_SENSEHIGH_B, 0x0A},
  {REG_SENSELOW_B, 0x0A},
  //Set debounce
  {REG_DEBOUNCEENABLE_A, (PIN_ATTENTION_BUTTON_MASK | PIN_MRL_MASK)},
  {REG_DEBOUNCEENABLE_B, (PIN_ATTENTION_BUTTON_MASK | PIN_MRL_MASK)},
  //Set debounce cfg debounce 8ms
  {REG_DEBOUNCECONFIG, 0x04}
};


EFI_STATUS PcieSlotPortExpander_WriteRegister(UINTN Address, UINT8 RegisterAddress, UINT8 Value)
{
  PE_REGISTER Register;

  Register.Address = RegisterAddress;
  Register.Value = Value;

  return PcieI2cIoWrite(Address, (UINT8*)&Register, sizeof(Register));
}

EFI_STATUS PcieSlotPortExpander_ReadRegister(UINTN Address, UINT8 RegisterAddress, UINT8* Value)
{
  return PcieI2cIoWriteRead(Address,
    (UINT8*)&RegisterAddress,
    sizeof(RegisterAddress),
    Value,
    1);
}

/**
  Reset port expander

  @param[in]     SlaveAddress   I2C slave address of the port expander

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_Reset (UINTN SlaveAddress)
{
  EFI_STATUS Status;
  UINT8 resetSequence[] = {0x7d, 0x12, 0x7d, 0x34};
  EFI_I2C_REQUEST_PACKET Request;

  Request.OperationCount = 2;
  Request.Operation[0].Flags = 0; //WRITE operation
  Request.Operation[0].LengthInBytes = 2;
  Request.Operation[0].Buffer = &resetSequence[0];
  Request.Operation[1].Flags = 0; //WRITE operation
  Request.Operation[1].LengthInBytes = 2;
  Request.Operation[1].Buffer = &resetSequence[2];

  Status = PcieI2cIoRequest(SlaveAddress, (EFI_I2C_REQUEST_PACKET*)&Request);
  if (!EFI_ERROR(Status)) {
    //Wait 2.5ms after reset before adressing the device/bus
    extern void busywait ( UINT32 pause_time_us );
    busywait(20000);
  }

  return Status;
}
/**
  Set a pins state (on/off/toggling)

  @param[in]     Address    I2C slave address and port bank encoded address
  @param[in]     State      SignalOn/SignalOff/PinToggling
  @param[in]     Pin        Pin id (0-7)

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_SetPinState (PORTADDRESS Address, SLOT_SIGNAL_STATE State, UINT8 Pin)
{
  EFI_STATUS Status;
  UINT8 PortValue;
  UINT8 Port;
  UINTN SlaveAddress;
  if (Pin > 7) {
    return EFI_INVALID_PARAMETER;
  }
  //Extract the port and slave address
  Port = (Address & 0x01);
  SlaveAddress = (Address >> 1);
  //Read the current port value
  Status = PcieSlotPortExpander_ReadRegister(SlaveAddress,
    REG_DATA(Port),
    &PortValue);
  if (EFI_ERROR (Status)) {
    goto done;
  }
  if (State == SignalToggling) {
    //blink mode
    //Set TOn/Toff registers
    Status = PcieSlotPortExpander_WriteRegister(SlaveAddress,
      gLedPinReg[Pin + (PORT(Address) * 8)].RegTOn,
      0x0f);
    if (EFI_ERROR (Status)) {
      goto done;
    }
    Status = PcieSlotPortExpander_WriteRegister(SlaveAddress,
      gLedPinReg[Pin + (PORT(Address) * 8)].RegTOff,
      (0x0f << 3));
    if (EFI_ERROR (Status)) {
      goto done;
    }
    //Data register low to enable blink.
    PortValue &= ~ (1 << Pin);
  } else {
    //Clear TOn/Toff registers
    Status = PcieSlotPortExpander_WriteRegister(SlaveAddress,
      gLedPinReg[Pin + (PORT(Address) * 8)].RegTOn,
      0);
    if (EFI_ERROR (Status)) {
      goto done;
    }
    Status = PcieSlotPortExpander_WriteRegister(SlaveAddress,
      gLedPinReg[Pin + (PORT(Address) * 8)].RegTOff,
      0);
    if (EFI_ERROR (Status)) {
      goto done;
    }
    //Turn ON or OFF
    switch (State) {
    case SignalOff:
      PortValue &= ~ (1 << Pin);
      break;
    case SignalOn:
      PortValue |= (1 << Pin);
      break;
    default:
      break;
    }
  }
  Status = PcieSlotPortExpander_WriteRegister(SlaveAddress,
    REG_DATA(Port),
    PortValue);
done:
  return Status;
}
/**
  Set up port expander bank for HP operation

  @param[in]     Address    I2C slave address and port bank encoded address

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_Configure(UINTN Address)
{
  EFI_STATUS Status;
  UINT32 RegisterIndex;

  for (RegisterIndex = 0; RegisterIndex < (sizeof(mPeInit) / sizeof(mPeInit[0])); RegisterIndex++) {
    Status = PcieI2cIoWrite(Address, (UINT8*)&mPeInit[RegisterIndex], sizeof(PE_REGISTER));
    if (EFI_ERROR(Status)) {
      break;
    }
  }

  return Status;
}

/**
  Read port interrupt state

  @param[in]     Address          I2C slave address and port bank encoded address
  @param[out]    InterruptStatus  bitmask indicating which pin(s) generated an interrupt

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_ReadInterruptStatus (PORTADDRESS Address, UINT8* InterruptStatus)
{
  return PcieSlotPortExpander_ReadRegister (SLAVE_ADDRESS (Address),
    REG_INTERRUPTSOURCE (PORT (Address)),
    InterruptStatus);
}
/**
  Clear port interrupt state
  Note: both banks must have cleared all interrupts before NINT will go high

  @param[in]     Address          I2C slave address and port bank encoded address
  @param[out]    InterruptMask    bitmask indicating which interrupts to clear

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_ClearInterruptStatus (PORTADDRESS Address, UINT8 InterruptMask)
{
  return PcieSlotPortExpander_WriteRegister (SLAVE_ADDRESS (Address),
    REG_INTERRUPTSOURCE (PORT (Address)),
    InterruptMask);
}

//QCOM_PCIE_CONFIG_SLOT_SIGNAL_PROTOCOL implementation

EFI_STATUS
EFIAPI
PcieSlotAttentionIndicator(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
)
{

  return PcieSlotPortExpander_SetPinState(SlotSignalPortAddress,
    Enable ? SignalOn : SignalOff,
    PIN_ATTENTION_LED);
}

EFI_STATUS
EFIAPI
PcieSlotPowerIndicator(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
)
{

  return PcieSlotPortExpander_SetPinState(SlotSignalPortAddress,
    Enable ? SignalOn : SignalOff,
    PIN_POWER_LED);
}

EFI_STATUS
EFIAPI
PcieSlotPERST(
  IN UINTN SlotSignalPortAddress,
  IN BOOLEAN Enable
)
{
  return PcieSlotPortExpander_SetPinState(SlotSignalPortAddress,
    Enable ? SignalOff : SignalOn,
    PIN_PERST);
}

EFI_STATUS
EFIAPI
PcieSlotPower(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
)
{
  EFI_STATUS Status;

  Status = PcieSlotPortExpander_SetPinState(SlotSignalPortAddress,
    (Enable ? SignalOn : SignalOff),
    PIN_POWER);
  if (!EFI_ERROR(Status)) {
    Status = PcieSlotPortExpander_SetPinState(SlotSignalPortAddress,
      (Enable ? SignalOff : SignalOn),
      PIN_POWER_LED);
  }
  return Status;
}

EFI_STATUS
EFIAPI
PcieSlotPRSNT(
  IN UINTN SlotSignalPortAddress ,
  OUT BOOLEAN *Enable
)
{
  EFI_STATUS Status;
  UINT8 PortValue;

  if (Enable == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  Status = PcieSlotPortExpander_ReadRegister(SLAVE_ADDRESS(SlotSignalPortAddress),
    REG_DATA(PORT(SlotSignalPortAddress)),
    &PortValue);
  if (!EFI_ERROR(Status)) {
    *Enable = !((BOOLEAN)(PortValue & (1 << PIN_PRSNT)));
  }
  return Status;
}

EFI_STATUS
EFIAPI
PcieSlotPowerFault(
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
