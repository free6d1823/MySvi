/*
 * Copyright (c) 2015 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 *
 */


#ifndef __DDR_COMMON_LIB_H__
#define __DDR_COMMON_LIB_H__

#include <stdint.h>
#include <stdbool.h>

/*==========================================================================
*
* @par Description
*    This type provides the necessary SPD information to UEFI, so it can
*    populate the SMBIOS tables appropriately.
*
* @par Members
*
*                                  <PRE>
*    populated              Boolean indicating if this slot is populated with a DIMM
*    device_locator         Identifies the physical socket or board position for a DIMM (e.g. DIMM 3)
*    bank_locator           Identifies the physically labeled bank where the device is located (e.g. Bank 0)
*    device_set             Identifies a set of DIMMS that have to have the same type/size
*    total_width            Total width in bits of this memory device including error correction bits
*    data_width             Total width minus error correction bits
*    memory_size            Size of the memory device/DIMM
*    form_factor            DIMM, SO-DIMM, etc...
*    memory_type            Type of memory (DRAM, ROM, RAM, EEPROM) - hardcode to DRAM
*    type_detail            Bit field that contains memory attributes (e.g. fast-paged, Cache DRAM, etc…)
*    max_clk_speed          Maximum speed of the memory (MHz)
*    manufacturer_id        ID specifying the memory manufacturer
*    serial_number          UINT32 specifying the serial number of the memory device
*    part_number[20]        Byte array specifying the part number
*    configured_clk_speed   Configured speed for the memory
*    attributes             Rank set in bits[3:0]
*    reserved               Reserved
*                                  </PRE>
*
===========================================================================*/
typedef struct {
       bool populated;                  //!< boolean indicating if this slot is populated with a DIMM
       uint8_t device_locator;          //!< identifies the physical socket or board position for a DIMM (e.g. DIMM 3)
       uint8_t bank_locator;            //!< identifies the physically labeled bank where the device is located (e.g. Bank 0)
       uint8_t device_set;              //!< identifies a set of DIMMS that have to have the same type/size
       uint16_t total_width;            //!< total width in bits of this memory device including error correction bits
       uint16_t data_width;             //!< total width minus error correction bits
       uint64_t memory_size;            //!< size of the memory device/DIMM
       uint8_t form_factor;             //!< DIMM, SO-DIMM, etc...
       uint8_t memory_type;             //!< Type of memory (DRAM, ROM, RAM, EEPROM) - hardcode to DRAM
       uint16_t type_detail;            //!< bit field that contains memory attributes (e.g. fast-paged, Cache DRAM, etc…)
       uint16_t max_clk_speed;          //!< maximum speed of the memory (MHz)
       uint16_t manufacturer_id;        //!< ID specifying the memory manufacturer
       uint32_t serial_number;          //!< UINT32 specifying the serial number of the memory device
       uint8_t part_number[20];         //!< Byte array specifying the part number
       uint16_t configured_clk_speed;   //!< configured speed for the memory
       uint8_t attributes;              //!<  rank set in bits[3:0]
       uint8_t reserved[5];             //!< Reserved
} spd_info_per_dimm;

#endif
