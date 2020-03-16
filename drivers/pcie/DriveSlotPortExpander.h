/** @file

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.



**/
#ifndef _DRIVE_SLOT_PORT_EXPANDER_H_
#define _DRIVE_SLOT_PORT_EXPANDER_H_

#include "NXPPCA9551.h"
#include <target/uefi_wrapper.h>

typedef enum {
  PinOn,
  PinOff,
  PinToggling
} PE_PIN_STATE;


EFI_STATUS DriveSlotPortExpander_Configure(UINTN Address);

EFI_STATUS
EFIAPI
DriveSlotAttentionIndicator(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
);

EFI_STATUS
EFIAPI
DriveSlotPowerIndicator(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
);

EFI_STATUS
EFIAPI
DriveSlotPERST(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
);

EFI_STATUS
EFIAPI
DriveSlotPower(
  IN UINTN SlotSignalPortAddress ,
  IN BOOLEAN Enable
);

EFI_STATUS
EFIAPI
DriveSlotPRSNT(
  IN UINTN SlotSignalPortAddress ,
  OUT BOOLEAN *Enable
);

EFI_STATUS
EFIAPI
DriveSlotPowerFault(
  IN UINTN SlotSignalPortAddress ,
  OUT BOOLEAN                           *Enable
);

#endif //_DRIVE_SLOT_PORT_EXPANDER_H_