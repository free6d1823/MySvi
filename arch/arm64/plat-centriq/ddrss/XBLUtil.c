/*=============================================================================

GENERAL DESCRIPTION     
  This module defines miscellaneous utility function for boot software.

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc. 
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

  Copyright (c) 2015 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include <target/ddr.h>

/*=========================================================================

                            FUNCTION DEFINITIONS

=========================================================================*/


/*===========================================================================

**  Function :  boot_strlen

** ==========================================================================
*/
/*!
* 
* @brief
* This funcion calculate the length of a string, excluding the NULL terminator.
*
* @param[in] str  start address of the string
*
* @par Dependencies
*   None
*   
* @retval
*   length of the string, excluding the NULL terminator.
* 
* @par Side Effects
*   None
* 
*/
uint32_t boot_strlen(char *str)
{
   char * ptr;

   for (ptr = str; *ptr; ptr++);

   return ptr - str;
}
/*boot_strlen*/


/*===========================================================================

**  Function : bload8

** ==========================================================================
*/
/*!
* 
* @brief
*   
*   This function takes a byte pointer and it returns the byte value in 
*   in 32 bits. 
*   
*   This function ensures that read opeartions from memory are 32 bit 
*   aligned.
* 
* @par Dependencies
*   None
* 
* @param
*   p        - a Byte  Pointer.
*   
* @retval
*   Byte value in 32 bits.
* 
* @par Side Effects
*   None
*/
uint32_t bLoad8 (const uint8_t* p)
{  
  /* align the address to 64 bits boundary */
  unsigned long aligned_p = ((uint64_t)p & (uint64_t)(~0x00000003)); 

  /* byte position in 64 bit address */  
  unsigned long index = ((uint64_t)p & (uint64_t) 0x00000003);
  /* - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - */

  /* return the byte in 32 bits after masking other bytes with zero */  
  return (( *((uint32_t*)(unsigned long) aligned_p) >> (index<<3)) &  0x000000FF ) ;
}
/*===========================================================================

**  Function : bstore8

** ==========================================================================
*/
/*!
* 
* @brief
*   
*   This function takes 32 bits input value and stores it at the address
*   pointed by the input byte pointer.
*   
*   This function ensures that write opeation to memory are 32 bit aligned.
* 
* @par Dependencies
*   None
* 
* @param
*   p        - Byte pointer.
*   val      - 32 bit data to be stored in memory.
* @retval
*  None.
* 
* @par Side Effects
*   None
*/
void bStor8 (uint8_t* p, uint32_t val)
{  
  /* align the address to 64 bits boundary */
  unsigned long aligned_p = ((unsigned long) p & (unsigned long)(~0x00000003));

  /* byte position in 64 bit address */  
  unsigned long index = ((unsigned long) p & (unsigned long)0x00000003);

  /* read the current data at 64 bit aligned address */
  uint32_t current_value = *((unsigned long*) aligned_p);
  /* - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - */

  /* ------------------------------------------------------------------ */
  /* store the input value after shifting it in the proper position and */
  /* ORing it with current_value after the target byte in 32 bit        */
  /* current_value is cleared by masking it with zero                   */
  /* ------------------------------------------------------------------ */
  *((uint32_t*)(unsigned long) aligned_p) =  ((current_value & ~(0xFF << (index<<3)))) | 
                             (val<< (index <<3));
}
/*===========================================================================

**  Function : bbytecompare

** ==========================================================================
*/
/*!
* 
* @brief
*   
*   This function compares two buffers byte by byte.
* 
*   This function replaces the memcmp utility in the C library and
*   ensures that read opeartions from memory are 32 bit aligned.
* 
*   Note: 
*   
*   Same optimization as bByteCopy could be applied here. but
*   this is not a high runner code in secure boot, optimization is 
*   left for future.
* 
* @par Dependencies
*   None
* 
* @param
*   value1_ptr  - Pointer to buffer 1.
*   value1_ptr  - Pointer to buffer 2.
*   byte_len    - Lenght to compare
* @retval
*  None.
* 
* @par Side Effects
*   None
*/
uint32_t bByteCompare
(
  const uint8_t*  value1_ptr,
  const uint8_t*  value2_ptr,
  const uint32_t  byte_len
)
{
  int   i;
  /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  for ( i=0; i< (int) byte_len; i++ )
  {
    if ( bLoad8((uint8_t*) (value1_ptr++)) != 
         bLoad8((uint8_t*) (value2_ptr++)) 
       ) 
      return (uint32_t)(i+1);
  }

  return 0;
} /* bByteCompare */

/*===========================================================================

**  Function : qmemcpy

** ==========================================================================
*/
/*!
* 
* @brief
*   
*   This function is now a wrapper for memscpy() and will be deprecated in future releases.  Please
*   Use qmemscpy() to replace.
* 
* @par Dependencies
*   None.
* 
* @param
*   source_ptr           - Pointer to source buffer.
*   destination_ptr      - Pointer to destination buffer.
*   len                  - Length to copy.
* 
* @retval
*   None.
* 
* @par Side Effects
*   None.
*/
void qmemcpy( void* destination_ptr, const void* source_ptr, uint32_t len )
{
  memscpy(destination_ptr, len, source_ptr, len);
}/* qmemcpy */


/*===========================================================================

**  Function : qmemscpy

** ==========================================================================
*/
/*!
* 
* @brief
*   
*   Currently a wrapper for memscpy(), can drop in optimized version of memscpy() as replacement 
*   when optimization is required.
* 
* @par Dependencies
*   None.
* 
* @param
*   destination_ptr      - Pointer to destination buffer.
*   dst_size                 - destination Length to copy.
*   source_ptr             - Pointer to source buffer.
*   src_size                 - source Length to copy.
* 
* @retval
*   None.
* 
* @par Side Effects
*   None.
*/
void qmemscpy( void* destination_ptr, uint32_t dst_size, const void* source_ptr, uint32_t src_size )
{
  memscpy(destination_ptr, dst_size, source_ptr, src_size);
} /* qmemscpy */


/*===========================================================================

**  Function : boot_count_set_bits

** ==========================================================================
*/
/*!
* 
* @brief
*    This function Counts the number of bits set in an uint32.
*   
* @param[in] input_val:  uint32 Input value whose set bits need to be 
*                        counted. 
* 
* @par Dependencies
*    None
* 
* @retval
*    count: uint32 Number of bits set to 1.
* 
* @par Side Effects
*    None
* 
*/
uint32_t boot_count_set_bits(uint32_t input_val)
{
  uint32_t count = 0;
  for(count = 0; input_val; count++)
  {
    input_val &= input_val - 1 ;
  }
  return count;
}

void qmemset (
  void* dst_ptr,
  uint32_t val,
  uint32_t len
)
{
  memset(dst_ptr, val, len);
}


