//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2019] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#ifndef __SYSTEM_EXT_MEM_IO_H__
#define __SYSTEM_EXT_MEM_IO_H__

#include "system_types.h"

typedef struct _SMemDescriptor {
    uint32_t offset;
    uint32_t size;
    uint32_t cached;
} SMemDescriptor;


typedef struct _SMemContext {
    SMemDescriptor dsr;
    void *ptr;
} SMemContext;

/**
 *   Initialize external memory access
 *
 *   This function should initialze external memory access.
 *
 *   @param  dsr - input memory descriptor
 *   @param  ctx - output memory context
 *
 *   @return 0 - on success
 *          -1 - on error
 */
int32_t system_ext_mem_init( SMemDescriptor *dsr, SMemContext *ctx );


/**
 *   Close external memory access
 *
 *   This function should close external memory access.
 *
 *   @param  ctx - memory context
 *
 *   @return 0 - on success
 *          -1 - on error
 */
int32_t system_ext_mem_terminate( SMemContext *ctx );


/**
 *   Read 32 bit word from external memory
 *
 *   This function returns a 32 bits word from external memory with a given offset.
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory to read 32 bits word.
 *                 Correct values from 0 to ACAMERA_ISP_MAX_EXT_ADDR
 *
 *   @return 32 bits memory value
 */
uint32_t system_ext_mem_read_32( SMemContext *ctx, uint32_t offset );


/**
 *   Read 16 bit word from external memory
 *
 *   This function returns a 16 bits word from external memory with a given offset.
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory to read 16 bits word.
 *                 Correct values from 0 to max available memory size
 *
 *   @return 16 bits memory value
 */
uint16_t system_ext_mem_read_16( SMemContext *ctx, uint32_t offset );


/**
 *   Read 8 bit word from external memory
 *
 *   This function returns a 8 bits word from external memory with a given offset.
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory to read 8 bits word.
 *                 Correct values from 0 to max available memory size
 *
 *   @return 8 bits memory value
 */
uint8_t system_ext_mem_read_8( SMemContext *ctx, uint32_t offset );


/**
 *   Copies the content of the external memory into the given memory area
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory.
 *                 Correct values from 0 to max available memory size
 *   @param  buffer - destination memory area.
 *   @param  count - the size of area to be copied.
 *                Correct values from 0 to max available memory size minus offset.
 */
void system_ext_mem_read_buffer( SMemContext *ctx, uint32_t offset, uint8_t *buffer, uint32_t count );


/**
 *   Write 32 bits word to external memory
 *
 *   This function writes a 32 bits word to external memory with a given offset.
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory to write data.
 *                 Correct values from 0 to ACAMERA_ISP_MAX_EXT_ADDR.
 *   @param  data - data to be written
 */
void system_ext_mem_write_32( SMemContext *ctx, uint32_t offset, uint32_t data );


/**
 *   Write 16 bits word to external memory
 *
 *   This function writes a 16 bits word to external memory with a given offset.
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory to write data.
 *                 Correct values from 0 to ACAMERA_ISP_MAX_EXT_ADDR.
 *   @param  data - data to be written
 */
void system_ext_mem_write_16( SMemContext *ctx, uint32_t offset, uint16_t data );


/**
 *   Write 8 bits word to external memory
 *
 *   This function writes a 8 bits word to external memory with a given offset.
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory to write data.
 *                 Correct values from 0 to ACAMERA_ISP_MAX_EXT_ADDR.
 *   @param  data - data to be written
 */
void system_ext_mem_write_8( SMemContext *ctx, uint32_t offset, uint8_t data );


/**
 *   Copies the content of the memory area to the external memory
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory.
 *                 Correct values from 0 to max available memory size
 *   @param  buffer - source memory area.
 *   @param  count - the size of area to be copied.
 *                Correct values from 0 to max available memory size minus offset.
 */
void system_ext_mem_write_buffer( SMemContext *ctx, uint32_t offset, const uint8_t *buffer, uint32_t count );


/**
 *   Fill external memory area with zeroes
 *
 *   @param  ctx - memory context.
 *   @param  offset - the offset in external memory.
 *                 Correct values from 0 to max available memory size
 *   @param  count - the size of area to be copied.
 *                Correct values from 0 to max available memory size minus offset.
 */
void system_ext_mem_write_zero( SMemContext *ctx, uint32_t offset, uint32_t count );

#endif /* __SYSTEM_EXT_MEM_IO_H__ */
