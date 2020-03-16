#ifndef _SPD_SMBUS_IMPL_H
#define _SPD_SMBUS_IMPL_H

/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* Filename: spd_smbus_impl.h
*
* Description: Provides mini core bus related interfacing and functionality to
*               get access to the SPD information from a specific DIMM slot.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/
void spd_smbus_init_qups(void);
void spd_smbus_setup_tlmm(void);
unsigned spd_smbus_dimm_get_block(uint8_t smbus_id, uint8_t spd_bus_addr, uint8_t spd_bank_num, uint16_t spd_reg_id, uint32_t xfer_block_size, void * dst_buff_addr);
unsigned spd_smbus_dimm_get_byte(uint8_t smbus_id, uint8_t spd_bus_addr, uint32_t spd_reg_id, uint8_t *spd_data_ptr);
unsigned spd_smbus_dimm_get_word(uint8_t smbus_id, uint8_t spd_bus_addr, uint32_t spd_reg_id, uint16_t *spd_data_ptr);
unsigned spd_smbus_dimm_set_block(uint8_t smbus_id, uint8_t spd_bus_addr, uint8_t spd_bank_num, uint16_t spd_reg_id, void* in_buffer, size_t buffer_size);
unsigned spd_smbus_dimm_set_byte(uint8_t smbus_id, uint8_t spd_bus_addr, uint32_t spd_reg_id, uint8_t spd_data);
unsigned spd_smbus_dimm_set_word(uint8_t smbus_id, uint8_t spd_bus_addr, uint32_t spd_reg_id, uint16_t spd_data);

/******************************************************************************
* Defined Constants
******************************************************************************/

#endif
