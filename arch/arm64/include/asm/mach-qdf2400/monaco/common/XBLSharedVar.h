#ifndef BOOT_SHARED_VARIABLES
#define BOOT_SHARED_VARIABLES

/*===========================================================================

                  Boot Shared Variables Header File

GENERAL DESCRIPTION
  This header file contains the definition of the shared variables.

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <asm/mach/monaco/common/SharedVariables.h>

/*===========================================================================

                           MACRO DEFINITIONS

===========================================================================*/
#define VARIABLE_STORE_FORMATTED                0x5A
#define VARIABLE_STORE_HEALTHY                  0xFE

#define VARIABLE_DATA                           0x55AA

#define VAR_IN_DELETED_TRANSITION               0xFE
#define VAR_DELETED                             0xFD
#define VAR_HEADER_VALID_ONLY                   0x7F
#define VAR_ADDED                               0x3F

#define VAR_READONLY                            0x1
#define VAR_HIDDEN                              0x10

#define HEADER_ALIGNMENT  4
#define HEADER_ALIGN(Header)  (((uint64_t)(Header) + HEADER_ALIGNMENT - 1) & (~(HEADER_ALIGNMENT - 1)))


/*===========================================================================

                           DATE TYPE DEFINITIONS

===========================================================================*/
typedef enum {
  VARIABLE_DEFAULT_SECURITY,
  VARIABLE_INTERNAL_SECURITY,
  VARIABLE_INVALID_SECURITY
} variable_security_level;


/*===========================================================================

                           DATE TYPE DEFINITIONS

===========================================================================*/
typedef struct {
  uint16_t  Year;
  uint8_t   Month;
  uint8_t   Day;
  uint8_t   Hour;
  uint8_t   Minute;
  uint8_t   Second;
  uint8_t   Pad1;
  uint32_t  Nanosecond;
  uint16_t  TimeZone;
  uint8_t   Daylight;
  uint8_t   Pad2;
} efi_time;


#pragma pack (1)
typedef struct {
  uint16_t    StartId;
  uint8_t     State;
  uint8_t     Reserved;
  uint32_t    Attributes;
  uint64_t    MonotonicCount;
  efi_time    TimeStamp;
  uint32_t    PubKeyIndex;
  uint32_t    NameSize;
  uint32_t    DataSize;
  GUID        VendorGuid;
} variable_header;
#pragma pack ()


typedef struct {
  variable_header *CurrPtr;
  variable_header *EndPtr;
  variable_header *StartPtr;
} variable_pointer_track;


typedef struct {
  bool                internal_variables;
} shared_variable_security;


/*===========================================================================

**  Function :  boot_get_shared_variable

** ==========================================================================
*/
/*!
*
* @brief
*     Read the shared variables.
*
* @param[in]
*   uint16_t* VariableName
*   void* data
*   uint32_t* DataSize
*
* @par Dependencies
*   None
*
* @retval
*   bool
*
* @par Side Effects
*   None
*/
bool boot_get_shared_variable(uint16_t* VariableName, void** data, uint32_t* DataSize, variable_security_level security_level);


/*===========================================================================

**  Function :  boot_shared_variables_init

** ==========================================================================
*/
/*!
*
* @brief
*     Read the shared variables.
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*/
void boot_shared_variables_init(void);

#endif /* BOOT_SHARED_VARIABLES */
