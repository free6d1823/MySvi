#ifndef _SPD_SIMM_H
#define _SPD_SIMM_H

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
* Filename: spd_simm.h
*
* Description: Provides interfacing and related functionality
*               to make use of the SPD simulation facilities.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <asm/mach/monaco/memory/spd.h>

/******************************************************************************
* Global Variables
******************************************************************************/
// Flags whether or not to use simulation at all or simulation in Silicon
// Emulation: there is no HW to support SPD so simulation will be used.
// Silicon: although there is HW to support SPD simulation is also an option.
// The simulation flags are defined in spd_simm.c
extern bool spd_use_simulated_spd;  // use simulation
extern bool spd_use_simm_in_sil;    // use simulation in Silicon

/******************************************************************************
* Function Prototypes
******************************************************************************/

void spd_simm_init(target_mode_e mode);
unsigned spd_simm_get_spd_block(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint32_t xfer_block_size, uint64_t dst_buff_addr);
unsigned spd_simm_get_word(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint16_t *spd_data_ptr);
unsigned spd_simm_get_byte(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint8_t *spd_data_ptr);
void spd_simm_get_sim_data(target_mode_e mode);
unsigned spd_simm_set_word(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint16_t spd_data);
unsigned spd_simm_set_byte(uint8_t smbus_id, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint8_t spd_data);


#endif
