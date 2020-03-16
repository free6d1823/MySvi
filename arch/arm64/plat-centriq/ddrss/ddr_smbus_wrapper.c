/** @file ddr_smbus_wrapper.c

  SMBus wrapper functions for supporting a single instance DDR driver.

  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

  Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
**/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include <stddef.h>
#include <errno.h>
#include <target/ddr.h>

/*===========================================================================
                                 DATA
===========================================================================*/
extern ddr_func_tbl ddr_function_table;

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/
/* ============================================================================
**  Function : ddr_smbus_read_data_byte
** ===========================================================================*/
int ddr_smbus_read_data_byte(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint8_t* out_data)
{
    if(ddr_function_table.smbus.read_data_byte != NULL)
    {
        return ddr_function_table.smbus.read_data_byte(smbus_id, smb_address>>1, read_offset, out_data);
    }
    else
    {
        return -EINVAL;
    }
}

/* ============================================================================
**  Function : ddr_smbus_read_data_word
** ===========================================================================*/
int ddr_smbus_read_data_word(uint32_t smbus_id, uint32_t smb_address, uint16_t read_offset, uint16_t* out_data)
{
    int status = 0;
    uint16_t output_v;

    if(ddr_function_table.smbus.read_data_word != NULL)
    {
        status=ddr_function_table.smbus.read_data_word(smbus_id, smb_address>>1, read_offset, &output_v);
        // Byte swapping since I2C driver returns read data as n byte streaming
        *out_data = ((output_v&0xFF00)>>8) | ((output_v&0xFF) <<8);

        return status;
    }
    else
    {
        return -EINVAL;
    }
}

/* ============================================================================
**  Function : ddr_smbus_block_read
** ===========================================================================*/
int ddr_smbus_block_read(uint32_t smbus_id, uint32_t smb_address, uint8_t spd_bank_num, uint16_t spd_reg_id, void* out_buffer, uint32_t buffer_size)
{
    uint16_t read_offset;

    if(ddr_function_table.smbus.block_read != NULL)
    {
        read_offset = (uint16_t)spd_bank_num*SPD_PAGE_SIZE + spd_reg_id;
        return ddr_function_table.smbus.block_read(smbus_id, smb_address>>1, read_offset, out_buffer, buffer_size);
    }
    else
    {
        return -EINVAL;
    }
}

/* ============================================================================
**  Function : ddr_smbus_write_data_byte
** ===========================================================================*/
int ddr_smbus_write_data_byte(uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, uint8_t value)
{
    if(ddr_function_table.smbus.write_data_byte != NULL)
    {
        return ddr_function_table.smbus.write_data_byte(smbus_id, smb_address>>1, write_offset, value);
    }
    else
    {
        return -EINVAL;
    }
}

/* ============================================================================
**  Function : ddr_smbus_write_data_word
** ===========================================================================*/
int ddr_smbus_write_data_word(uint32_t smbus_id, uint32_t smb_address, uint16_t write_offset, uint16_t value)
{
    uint16_t output_v;

    if(ddr_function_table.smbus.write_data_word != NULL)
    {
        output_v = ((value&0xFF00)>>8) | ((value&0xFF) <<8);
        return ddr_function_table.smbus.write_data_word(smbus_id, smb_address>>1, write_offset, output_v);
    }
    else
    {
        return -EINVAL;
    }
}

/* ============================================================================
**  Function : ddr_smbus_block_write
** ===========================================================================*/
int ddr_smbus_block_write(uint32_t smbus_id, uint32_t smb_address, uint8_t spd_bank_num, uint16_t spd_reg_id, void* in_buffer, uint32_t buffer_size)
{
    uint16_t write_offset;

    if(ddr_function_table.smbus.block_write != NULL)
    {
        write_offset = (uint16_t)spd_bank_num*SPD_PAGE_SIZE + spd_reg_id;
        return ddr_function_table.smbus.block_write(smbus_id, smb_address>>1, write_offset, in_buffer, buffer_size);
    }
    else
    {
        return -EINVAL;
    }
}

