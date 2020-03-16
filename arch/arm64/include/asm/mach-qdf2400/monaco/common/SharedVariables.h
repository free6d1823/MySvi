/*===========================================================================
                  Shared Variables Header File

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/
#ifndef SHARED_VARIABLES
#define SHARED_VARIABLES
#include <target/guid.h>
#include <stdint.h>
#include <stdbool.h>
#define BOOT_SHARED_VARIABLES_MAX_SIZE          (0x2000)   // SIZE 8KB


#pragma pack (1)
typedef struct {
  GUID      Signature;
  uint32_t  Size;
  uint8_t   Format;
  uint8_t   State;
  uint16_t  Reserved;
  uint32_t  Reserved1;
} variable_store_header;


typedef struct {
  variable_store_header  Header;
  uint8_t                  Data[BOOT_SHARED_VARIABLES_MAX_SIZE - sizeof(variable_store_header)];
} boot_variables;
#pragma pack ()


typedef struct {
  bool            shared_variables_found;
  boot_variables *shared_variable;
  uint32_t        shared_variable_size;
  bool            default_variables_found;
  boot_variables *default_variable;
  uint32_t        default_variable_size;
} shared_variable_info;


typedef struct {
  uint32_t         NameSz;
  uint32_t         DataSz;
} BootVariableHeaderType;


#endif /* SHARED_VARIABLES */
