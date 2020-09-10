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

/**
 @file module_mcfe_hwif_buffer_access.h
 @brief      This is a space optimization register access for out and raw
             buffers. It was written to support microblaze bare metal which is
             very limited in terms of memory available for .text. The module
             abuses the fact that all 96 buffer register banks share the same
             physical layout and treats these banks as arrays. In the code you
             will see a define such as
             #ACAMERA_OUT_BUFFERS_OUT_BUFFERS_BUFFER_VALID_0_FIELD_OFFSET which
             refers to a particular bank (0 in this case) but can be reused for
             all buffers due to the property mentioned. THis module was hand
             written because the hardware description xml file at the time did
             not group the buffers making it impossible to generate shared code.
             The addresses and offsets are still extracted from the auto
             generated headers.
*/
#ifndef __MODULE_MCFE_HWIF_BUFFER_ACCESS_H__
#define __MODULE_MCFE_HWIF_BUFFER_ACCESS_H__

#include "system_assert.h"
#include "system_isp_io.h" //register io
#include "system_types.h"  //types
#include "acamera_configuration.h"
#include "acamera_out_buffers_config.h" //Out buffer address and offsets
#include "acamera_raw_buffers_config.h" //raw buffer address and offsets
#include "bitop.h"                      //Bit mask magic


/** defines a read/write register attribute */
#define __IO volatile

/** defines a read only register attribute */
#define __I volatile const

/** Number of out buffer register blocks */
#define ISP_OUT_BUFFER_NUM 64

/** Number of raw buffer register blocks*/
#define ISP_RAW_BUFFER_NUM 32


/**
 * @brief      Buffer register bank structure.
 * @note       this applies to both RAW_BUFFERS and OUT_BUFFERS
 */
typedef struct
{
    __IO uint32_t CFG;           /**< Various configuration bits. */
    __IO uint32_t BASE_ADDR;     /**< Frame base address */
    __IO uint32_t LINE_OFFSET;   /**< Offset in bytes between lines */
    __IO uint32_t ACTIVE_WIDTH;  /**< Active width in pixels */
    __IO uint32_t ACTIVE_HEIGHT; /**< Active height in pixels */
    __IO uint32_t HEIGHT_MODULO; /**< Number of lines in circular buffer. */
    __IO uint32_t STATUS;        /**< Buffer status. */
    __I uint32_t CRC;            /**< Buffer contents CRC */
} ISP_BUFFER_T;


/** Pointer to raw buffer register blocks */
#define ISP_RAW_BUFFERS ( (ISP_BUFFER_T *)( PHY_ADDR_ISP + ACAMERA_RAW_BUFFERS_BASE_ADDR ) )

/** Pointer to out buffer register blocks*/
#define ISP_OUT_BUFFERS ( (ISP_BUFFER_T *)( PHY_ADDR_ISP + ACAMERA_OUT_BUFFERS_BASE_ADDR ) )

/**
 * @brief      Sets or clears the buffer valid flag
 *
 * @param      buffer  The buffer pointer
 * @param[in]  onoff   Flag
 *
 */
static __inline void acamera_buffers_valid_write( ISP_BUFFER_T *buffer, const bool onoff )
{
    const uint32_t r = system_isp_read_32( (uintptr_t)&buffer->CFG );
    system_isp_write_32( (uintptr_t)&buffer->CFG,
                         BF_SET( r,
                                 onoff ? 1 : 0,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_BUFFER_VALID_0_FIELD_OFFSET,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_BUFFER_VALID_0_DATASIZE ) );
}

/**
 * @brief      Reads buffer valid flag
 *
 * @param      buffer  The buffer pointer
 *
 * @return     True if valid, false otherwise
 *
 */
static __inline bool acamera_buffers_valid_read( ISP_BUFFER_T *buffer )
{
    return (bool)BF_GET( system_isp_read_32( (uintptr_t)&buffer->CFG ),
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_BUFFER_VALID_0_FIELD_OFFSET,
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_BUFFER_VALID_0_DATASIZE );
}


/**
 * @brief      Sets/clears the clone flag
 *
 * @param      buffer  The buffer pointer
 * @param[in]  onoff   The flag
 *
 */
static __inline void acamera_buffers_clone_flag_write( ISP_BUFFER_T *buffer, const bool onoff )
{
    const uint32_t r = system_isp_read_32( (uintptr_t)&buffer->CFG );
    system_isp_write_32( (uintptr_t)&buffer->CFG,
                         BF_SET( r,
                                 onoff ? 1 : 0,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_CLONE_FLAG_0_FIELD_OFFSET,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_CLONE_FLAG_0_DATASIZE ) );
}


/**
 * @brief      Reads clone flag
 *
 * @param      buffer  The buffer pointer
 *
 * @return     True if set, false otherwise
 *
 */
static __inline bool acamera_buffers_clone_flag_read( ISP_BUFFER_T *buffer )
{
    return (bool)BF_GET( system_isp_read_32( (uintptr_t)&buffer->CFG ),
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_CLONE_FLAG_0_FIELD_OFFSET,
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_CLONE_FLAG_0_DATASIZE );
}


static __inline void acamera_buffers_pool_flag_write( ISP_BUFFER_T *buffer, const bool onoff )
{
    const uint32_t r = system_isp_read_32( (uintptr_t)&buffer->CFG );
    system_isp_write_32( (uintptr_t)&buffer->CFG,
                         BF_SET( r,
                                 onoff ? 1 : 0,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_POOL_FLAG_0_FIELD_OFFSET,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_POOL_FLAG_0_DATASIZE ) );
}

static __inline bool acamera_buffers_pool_flag_read( ISP_BUFFER_T *buffer )
{
    return (bool)BF_GET( system_isp_read_32( (uintptr_t)&buffer->CFG ),
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_POOL_FLAG_0_FIELD_OFFSET,
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_POOL_FLAG_0_DATASIZE );
}

static __inline void acamera_buffers_msb_align_flag_write( ISP_BUFFER_T *buffer, const bool onoff )
{
    system_isp_write_32( (uintptr_t)&buffer->CFG,
                         BF_SET( system_isp_read_32( (uintptr_t)&buffer->CFG ),
                                 onoff ? 1 : 0,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_MSB_ALIGN_0_FIELD_OFFSET,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_MSB_ALIGN_0_DATASIZE ) );
}

static __inline bool acamera_buffers_msb_align_flag_read( ISP_BUFFER_T *buffer )
{
    return (bool)BF_GET( system_isp_read_32( (uintptr_t)&buffer->CFG ),
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_MSB_ALIGN_0_FIELD_OFFSET,
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_MSB_ALIGN_0_DATASIZE );
}

static __inline void acamera_buffers_infinite_flag_write( ISP_BUFFER_T *buffer, const bool onoff )
{
    const uintptr_t raddr = (uintptr_t)&buffer->CFG;
    system_isp_write_32( raddr,
                         BF_SET( system_isp_read_32( raddr ),
                                 onoff ? 1 : 0,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_INFINITE_FLAG_0_FIELD_OFFSET,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_INFINITE_FLAG_0_DATASIZE ) );
}

static __inline bool acamera_buffers_infinite_flag_read( ISP_BUFFER_T *buffer )
{
    return (bool)BF_GET( system_isp_read_32( (uintptr_t)&buffer->CFG ),
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_INFINITE_FLAG_0_FIELD_OFFSET,
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_INFINITE_FLAG_0_DATASIZE );
}


static __inline void acamera_buffers_data_width_write( ISP_BUFFER_T *buffer, uint8_t data )
{
    const uint32_t r = system_isp_read_32( (uintptr_t)&buffer->CFG );
    system_isp_write_32( (uintptr_t)&buffer->CFG,
                         BF_SET( r,
                                 data,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_DATA_WIDTH_0_FIELD_OFFSET,
                                 ACAMERA_OUT_BUFFERS_OUT_BUFFERS_DATA_WIDTH_0_DATASIZE ) );
}

static __inline uint8_t acamera_buffers_data_width_read( ISP_BUFFER_T *buffer )
{
    return (bool)BF_GET( system_isp_read_32( (uintptr_t)&buffer->CFG ),
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_DATA_WIDTH_0_FIELD_OFFSET,
                         ACAMERA_OUT_BUFFERS_OUT_BUFFERS_DATA_WIDTH_0_DATASIZE );
}


static __inline void acamera_buffers_status_write( ISP_BUFFER_T *buffer, uint8_t data )
{
    // The rest of the register is reserved so we can just write the status
    system_isp_write_32( (uintptr_t)&buffer->STATUS, ( uint32_t )( data & ACAMERA_OUT_BUFFERS_OUT_BUFFERS_STATUS_0_FIELD_MASK ) );
}

static __inline uint8_t acamera_buffers_status_read( ISP_BUFFER_T *buffer )
{
    return system_isp_read_32( (uintptr_t)&buffer->STATUS ) & ACAMERA_OUT_BUFFERS_OUT_BUFFERS_STATUS_0_FIELD_MASK;
}

static __inline void acamera_buffers_base_address_write( ISP_BUFFER_T *buffer, uint32_t data )
{
    system_isp_write_32( (uintptr_t)&buffer->BASE_ADDR, data );
}
static __inline uint32_t acamera_buffers_base_address_read( ISP_BUFFER_T *buffer )
{
    return system_isp_read_32( (uintptr_t)&buffer->BASE_ADDR );
}


static __inline void acamera_buffers_line_offset_write( ISP_BUFFER_T *buffer, uint32_t data )
{
    system_isp_write_32( (uintptr_t)&buffer->LINE_OFFSET, data );
}

static __inline uint32_t acamera_buffers_line_offset_read( ISP_BUFFER_T *buffer )
{
    return system_isp_read_32( (uintptr_t)&buffer->LINE_OFFSET );
}

static __inline void acamera_buffers_active_width_write( ISP_BUFFER_T *buffer, uint16_t data )
{
    system_isp_write_32( (uintptr_t)&buffer->ACTIVE_WIDTH, data & ACAMERA_OUT_BUFFERS_OUT_BUFFERS_ACTIVE_WIDTH_0_FIELD_MASK );
}

static __inline uint16_t acamera_buffers_active_width_read( ISP_BUFFER_T *buffer )
{
    return system_isp_read_32( (uintptr_t)&buffer->ACTIVE_WIDTH ) & ACAMERA_OUT_BUFFERS_OUT_BUFFERS_ACTIVE_WIDTH_0_FIELD_MASK;
}

static __inline void acamera_buffers_active_height_write( ISP_BUFFER_T *buffer, uint16_t data )
{
    system_isp_write_32( (uintptr_t)&buffer->ACTIVE_HEIGHT, data & ACAMERA_OUT_BUFFERS_OUT_BUFFERS_ACTIVE_HEIGHT_0_FIELD_MASK );
}

static __inline uint16_t acamera_buffers_active_height_read( ISP_BUFFER_T *buffer )
{
    return system_isp_read_32( (uintptr_t)&buffer->ACTIVE_HEIGHT ) & ACAMERA_OUT_BUFFERS_OUT_BUFFERS_ACTIVE_HEIGHT_0_FIELD_MASK;
}

/**
 * @brief      Checks if the specified base address and index is a valid
 *             combination.
 *
 * @param      base   The base address 
 * @param[in]  index  The index
 *
 * @return     true if valid, false otherwise.
 *
 */
static __inline bool acamera_buffers_is_index_valid( ISP_BUFFER_T *base, const size_t index )
{
    if ( base == ISP_RAW_BUFFERS )
        return (bool)( index < ISP_RAW_BUFFER_NUM );
    else if ( base == ISP_OUT_BUFFERS )
        return (bool)( index < ISP_OUT_BUFFER_NUM );
    else
        return false;
}

/**
 * @brief      Helper function returning pointer to buffer register bank
 *
 * @param      base   The base address
 * @param[in]  index  The index
 *
 * @return     Pointer to #ISP_BUFFER_T
 *
 * @details    This function does not do any checking what's so ever. It is up
 *             to the user to call #acamera_buffers_is_index_valid to check if
 *             paramters are valid.
 */
static __inline ISP_BUFFER_T *acamera_buffers_get_ptr( ISP_BUFFER_T *base, const size_t index )
{
    return &base[index];
}


/**
 * @brief      This function ensure the registers have been placed at the
 *             correct addresses.
 *
 * @details    If the size of regsiters block is incorrect then padding has been
 *             inserted by the compiler, in that case use the 'packed' struct
 *             attribute.
 */
static __inline void acamera_out_verify_address( void )
{
    assert( sizeof( ISP_BUFFER_T ) == 0x20 );
    assert( ( ISP_OUT_BUFFER_NUM * sizeof( ISP_BUFFER_T ) ) == ACAMERA_OUT_BUFFERS_SIZE );
    assert( ( ISP_RAW_BUFFER_NUM * sizeof( ISP_BUFFER_T ) ) == ACAMERA_RAW_BUFFERS_SIZE );

    assert( (uintptr_t)ISP_RAW_BUFFERS == ( PHY_ADDR_ISP + ACAMERA_RAW_BUFFERS_RAW_BUFFERS_BUFFER_VALID_0_REG_ADDR ) );
    assert( (uintptr_t)&ISP_RAW_BUFFERS[ISP_RAW_BUFFER_NUM - 1] == ( PHY_ADDR_ISP + ACAMERA_RAW_BUFFERS_RAW_BUFFERS_BUFFER_VALID_31_REG_ADDR ) );

    assert( (uintptr_t)ISP_OUT_BUFFERS == ( PHY_ADDR_ISP + ACAMERA_OUT_BUFFERS_OUT_BUFFERS_BUFFER_VALID_0_REG_ADDR ) );
    assert( (uintptr_t)&ISP_OUT_BUFFERS[ISP_OUT_BUFFER_NUM - 1] == ( PHY_ADDR_ISP + ACAMERA_OUT_BUFFERS_OUT_BUFFERS_BUFFER_VALID_31_REG_ADDR ) );
}

#endif // __MODULE_MCFE_HWIF_BUFFER_ACCESS_H__
       /** @} */