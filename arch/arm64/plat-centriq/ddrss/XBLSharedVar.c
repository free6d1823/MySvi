/*===========================================================================

                        Boot Shared Variables

GENERAL DESCRIPTION
  This header file contains the definition of
  the shared variables.

Copyright (c) 2016-2018 Qualcomm Datacenter Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.

============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <asm/mach/platform_def.h>
#include <target/ddr.h>

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/
/* Structure to track location and size of variable store. */
shared_variable_info variable_store;

/* Structure to track variable security policy. */
shared_variable_security variable_security;

/* Shared Variables GUID */
extern GUID gSharedVariablesPartitionGuid;

/* Internal Variables GUID */
extern GUID gInternalSharedVariablesGuid;

/* boot_boolean data type used for boolean variables shared with pbl*/
typedef  unsigned int       boot_boolean;     /* uint32 Boolean value type. */

/*===========================================================================

**  Function :  boot_variable_compare_guids

** ==========================================================================
*/
/*!
*
* @brief
*    Compare GUIDs
*
* @param[in]
*   GUID* g1
*   GUID* g2
*
*
* @par Dependencies
*   None
*
* @retval
*   boolean
*
* @par Side Effects
*   None
*/
bool boot_variable_compare_guids (GUID* g1, GUID* g2)
{
  uint32_t *d, *s;

  if(g1 == NULL || g2 == NULL)
  {
	return false;
  }

  d = (uint32_t*)g1;
  s = (uint32_t*)g2;

  return d[0] == s[0] && d[1] == s[1] && d[2] == s[2] && d[3] == s[3];
}


/*===========================================================================

**  Function :  boot_verify_store_header

** ==========================================================================
*/
/*!
*
* @brief
*    Verify store header
*
* @param[in]
*   variable_store_header *header
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
bool boot_verify_store_header (variable_store_header *header)
{
  if(header == NULL ||
     header->Size == 0 ||
     header->Format != VARIABLE_STORE_FORMATTED ||
     header->State != VARIABLE_STORE_HEALTHY)
  {
    return false;
  }

  return true;
}


/*===========================================================================

**  Function :  boot_verify_variable_header

** ==========================================================================
*/
/*!
*
* @brief
*    Verify variable header
*
* @param[in]
*   variable_header *header
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
bool boot_verify_variable_header (variable_header *header)
{
  if(header == NULL ||
     header->StartId != VARIABLE_DATA ||
     (header->State != VAR_ADDED && header->State != (VAR_IN_DELETED_TRANSITION & VAR_ADDED)) ||
     header->NameSize == 0 ||
     header->DataSize == 0)
  {
    return false;
  }

  return true;
}


/*===========================================================================

**  Function :  boot_is_variable_readonly

** ==========================================================================
*/
/*!
*
* @brief
*    Get variable readonly status
*
* @param[in]
*   variable_header *header
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
bool boot_is_variable_readonly (variable_header *header)
{
  if((header->Reserved & VAR_READONLY) == VAR_READONLY)
  {
    return true;
  }
  return false;
}


/*===========================================================================

**  Function :  boot_get_variable_name_size

** ==========================================================================
*/
/*!
*
* @brief
*    Get variable name size
*
* @param[in]
*   variable_header *header
*
* @par Dependencies
*   None
*
* @retval
*   uint32_t
*
* @par Side Effects
*   None
*/
uint32_t boot_get_variable_name_size (variable_header *header)
{
  return header->NameSize;
}


/*===========================================================================

**  Function :  boot_get_variable_data_size

** ==========================================================================
*/
/*!
*
* @brief
*    Get variable data size
*
* @param[in]
*   variable_header *header
*
* @par Dependencies
*   None
*
* @retval
*   uint32_t
*
* @par Side Effects
*   None
*/
uint32_t boot_get_variable_data_size (variable_header *header)
{
  return header->DataSize;
}


/*===========================================================================

**  Function :  boot_get_variable_name_ptr

** ==========================================================================
*/
/*!
*
* @brief
*    Get variable name pointer
*
* @param[in]
*   variable_header *header
*
* @par Dependencies
*   None
*
* @retval
*   uint16_t *
*
* @par Side Effects
*   None
*/
uint16_t* boot_get_variable_name_ptr (variable_header *header)
{
  return (uint16_t *) (header + 1);
}


/*===========================================================================

**  Function :  boot_get_variable_data_ptr

** ==========================================================================
*/
/*!
*
* @brief
*    Get variable data pointer
*
* @param[in]
*   variable_header *header
*
* @par Dependencies
*   None
*
* @retval
*   void *
*
* @par Side Effects
*   None
*/
void* boot_get_variable_data_ptr (variable_header *header)
{
  unsigned long value;

  value = (unsigned long)boot_get_variable_name_ptr (header);
  value += boot_get_variable_name_size(header);

  return (void*)value;
}


/*===========================================================================

**  Function :  boot_get_next_variable_ptr

** ==========================================================================
*/
/*!
*
* @brief
*    Get next variable pointer
*
* @param[in]
*   variable_header *header
*
* @par Dependencies
*   None
*
* @retval
*   variable_header *
*
* @par Side Effects
*   None
*/
variable_header* boot_get_next_variable_ptr (variable_header *header)
{
  unsigned long value;

  value = (unsigned long)boot_get_variable_data_ptr (header);
  value += boot_get_variable_data_size (header);

  return (variable_header*)HEADER_ALIGN(value);
}


/*===========================================================================

**  Function :  boot_get_start_variable_ptr

** ==========================================================================
*/
/*!
*
* @brief
*    Get start variable pointer
*
* @param[in]
*   variable_store_header *header
*
* @par Dependencies
*   None
*
* @retval
*   variable_header *
*
* @par Side Effects
*   None
*/
variable_header* boot_get_start_variable_ptr (variable_store_header *header)
{
  return (variable_header*) HEADER_ALIGN(header + 1);
}


/*===========================================================================

**  Function :  boot_get_end_variable_ptr

** ==========================================================================
*/
/*!
*
* @brief
*    Get start variable pointer
*
* @param[in]
*   variable_store_header *header
*
* @par Dependencies
*   None
*
* @retval
*   variable_header *
*
* @par Side Effects
*   None
*/
variable_header* boot_get_end_variable_ptr (variable_store_header *header)
{
	return (variable_header*) HEADER_ALIGN((unsigned long)header + header->Size);
}


/*===========================================================================

**  Function :  boot_init_boot_variables

** ==========================================================================
*/
/*!
*
* @brief
*    Read the boot variables from flash.
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
#ifdef HARVEST
extern unsigned char default_variables_bin[];
extern unsigned char shared_variables_bin[];
void boot_init_boot_variables(void)
{
    variable_store.default_variable = (boot_variables *)default_variables_bin;
    variable_store.default_variable_size = SCL_DEFAULT_VARIABLES_TEMP_BUF_SIZE;

    /* Initialize shared variables if not in deep recovery mode. */
    variable_store.shared_variable = (boot_variables *)shared_variables_bin;
    variable_store.shared_variable_size = SCL_SHARED_VARIABLES_TEMP_BUF_SIZE;

    variable_store.shared_variables_found = true;
}
#endif

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
bool boot_get_shared_variable(uint16_t* VariableName, void** data, uint32_t* DataSize, variable_security_level security_level)
{
  variable_pointer_track variable_track;
  void *data_ptr = NULL;
  uint32_t data_size = 0;
  bool data_readonly = false;
  bool shared_variable_allowed = true;
  GUID *variable_guid = NULL;
  boot_boolean IsDebugEnabled = false;

  if(VariableName == NULL)
  {
    return false;
  }

  switch(security_level)
  {
    case VARIABLE_DEFAULT_SECURITY:
      variable_guid = &gSharedVariablesPartitionGuid;
      break;
    case VARIABLE_INTERNAL_SECURITY:
      if(!variable_security.internal_variables || IsDebugEnabled == false )
      {
        shared_variable_allowed = false;
      }
      variable_guid = &gInternalSharedVariablesGuid;
      break;
    case VARIABLE_INVALID_SECURITY:
    default:
      return false;
       break;
  }

  /* Search for variable in default store */
  variable_track.StartPtr = boot_get_start_variable_ptr(&(variable_store.default_variable->Header));
  variable_track.EndPtr = boot_get_end_variable_ptr(&(variable_store.default_variable->Header));

  for(variable_track.CurrPtr = variable_track.StartPtr;
      variable_track.CurrPtr < variable_track.EndPtr;
      variable_track.CurrPtr = boot_get_next_variable_ptr(variable_track.CurrPtr))
  {
    if(boot_verify_variable_header(variable_track.CurrPtr) &&
       boot_variable_compare_guids(&(((variable_header *)variable_track.CurrPtr)->VendorGuid), variable_guid))
    {
      if (bByteCompare((uint8_t*)VariableName, (uint8_t*)boot_get_variable_name_ptr(variable_track.CurrPtr),
                       boot_get_variable_name_size(variable_track.CurrPtr)) == 0)
      {
        data_size = boot_get_variable_data_size(variable_track.CurrPtr);
        data_ptr = boot_get_variable_data_ptr(variable_track.CurrPtr);
        data_readonly = boot_is_variable_readonly(variable_track.CurrPtr);
        break;
      }
    }
  }

  /* Search for variable in shared store */
  if((variable_store.shared_variables_found) &&
     (shared_variable_allowed) &&
     (!data_readonly))
  {
    variable_track.StartPtr = boot_get_start_variable_ptr(&(variable_store.shared_variable->Header));
    variable_track.EndPtr = boot_get_end_variable_ptr(&(variable_store.shared_variable->Header));

    for(variable_track.CurrPtr = variable_track.StartPtr;
        variable_track.CurrPtr < variable_track.EndPtr;
        variable_track.CurrPtr = boot_get_next_variable_ptr(variable_track.CurrPtr))
    {
      if(boot_verify_variable_header(variable_track.CurrPtr) &&
         boot_variable_compare_guids(&(((variable_header *)variable_track.CurrPtr)->VendorGuid), variable_guid))
      {
        if (bByteCompare((uint8_t*)VariableName, (uint8_t*)boot_get_variable_name_ptr(variable_track.CurrPtr),
                         boot_get_variable_name_size(variable_track.CurrPtr)) == 0)
        {
          data_size = boot_get_variable_data_size(variable_track.CurrPtr);
          data_ptr = boot_get_variable_data_ptr(variable_track.CurrPtr);
          break;
        }
      }
    }
  }

  if(data_ptr)
  {
    *data = data_ptr;
    *DataSize = data_size;
    return true;
  }
  else
  {
    return false;
  }
}
