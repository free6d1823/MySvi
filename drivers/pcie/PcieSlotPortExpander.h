/** @file

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

**/
#ifndef _PCIE_SLOT_PORT_EXPANDER_H_
#define _PCIE_SLOT_PORT_EXPANDER_H_

#include "Semtech1509B.h"
//#include "hdts_shell.h"
#include <target/uefi_wrapper.h>




typedef UINTN PORTADDRESS;

// PORTADDRESS is ((Slave Address << 1) | Port)
// Where Port is 0 for port A, 1 for port B
#define PORT_A                0
#define PORT_B                1
#define PORT_ADDRESS(sa, p)   ((sa << 1) | p)
#define SLAVE_ADDRESS(pa)     (pa >> 1)
#define PORT(pa)              (pa & 0x01)

// macros for port A/B register access
#define REG_INPUTDISABLE(port)    (REG_INPUTDISABLE_A - port)
#define REG_DATA(port)            (REG_DATA_A - port)
#define REG_DIR(port)             (REG_DIR_A - port)
#define REG_INTERRUPTMASK(port)   (REG_INTERRUPTMASK_A - port)
#define REG_INTERRUPTSOURCE(port) (REG_INTERRUPTSOURCE_A - port)
#define REG_LEDDRIVERENABLE(port) (REG_LEDDRIVERENABLE_A - port)
#define REG_DEBOUNCEENABLE(port)  (REG_DEBOUNCEENABLE_A - port)
#define REG_OPENDRAIN(port)       (REG_OPENDRAIN_A - port)
#define REG_OPENDRAIN(port)       (REG_OPENDRAIN_A - port)

/**
  Reset port expander

  @param[in]     SlaveAddress   I2C slave address of the port expander

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_Reset (UINTN SlaveAddress);
/**
  Set up port expander bank for HP operation

  @param[in]     Address    I2C slave address and port bank encoded address

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_Configure (UINTN Address);
/**
  Read port interrupt state

  @param[in]     Address          I2C slave address and port bank encoded address
  @param[out]    InterruptStatus  bitmask indicating which pin(s) generated an interrupt

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_ReadInterruptStatus (PORTADDRESS Address, UINT8* InterruptStatus);
/**
  Clear port interrupt state
  Note: both banks must have cleared all interrupts before NINT will go high

  @param[in]     Address          I2C slave address and port bank encoded address
  @param[out]    InterruptMask    bitmask indicating which interrupts to clear

  @retval EFI_STATUS Indicating success or failure
**/
EFI_STATUS PcieSlotPortExpander_ClearInterruptStatus (PORTADDRESS Address, UINT8 InterruptMask);

//QCOM_PCIE_CONFIG_SLOT_SIGNAL_PROTOCOL implementation

EFI_STATUS
EFIAPI
PcieSlotAttentionIndicator(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN                            Enable
);

EFI_STATUS
EFIAPI
PcieSlotPowerIndicator(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN                            Enable
);

EFI_STATUS
EFIAPI
PcieSlotPERST(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN                            Enable
);

EFI_STATUS
EFIAPI
PcieSlotPower(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN                            Enable
);

EFI_STATUS
EFIAPI
PcieSlotPRSNT(
  IN UINTN SlotSignalPortAddress ,
  OUT BOOLEAN                           *Enable
);

EFI_STATUS
EFIAPI
PcieSlotPowerFault(
  IN UINTN SlotSignalPortAddress ,
  OUT BOOLEAN                           *Enable
);


#endif //_PCIE_SLOT_PORT_EXPANDER_H_

