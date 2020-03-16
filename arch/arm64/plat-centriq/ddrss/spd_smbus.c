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
* @file spd_smbus.c
*
* @par Description:
*    This module provides functionality to use the SMBus to get access the SPD
*     information from a specific DIMM slot.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/
#include <stdint.h>
#include <string.h>
#include <target/ddr.h>

/******************************************************************************
* Defined Constants
******************************************************************************/

/******************************************************************************
* Derived data types
******************************************************************************/



/******************************************************************************
* Global Variables
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    Maps SMBus ID and addresses based on chan and slot
*
******************************************************************************/

dimm_slot_smbus_info_t spd_smbus_info[DDR_MAX_NUM_CHANS][DDR_MAX_NUM_SLOTS_PER_CHAN];


/******************************************************************************
* Macros
******************************************************************************/



/******************************************************************************
* Function Prototypes
******************************************************************************/

unsigned spd_smbus_check_CRC(uint64_t orig_dst_buff_addr, uint32_t block_size);
uint16_t check_crc16(void* addr, int count);


/******************************************************************************
* External Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function initializes the SMBuses to allow for retrieval of SPD
*     information from the DIMMs.
*
* @return
*    None
*
* @author
*    gkowis/cbucsan
*
* @par Notes:
*    Initialize the SMBus: setup TLMM and QUP subsystems
*
******************************************************************************/
void spd_smbus_init(void)
{
    #ifdef __BAREMETAL__
    spd_smbus_setup_tlmm(); // Setup TLMM (SDA/SCL GPIO's etc.)
    spd_smbus_init_qups();  // Setup the QUP subsystems
    #endif

}


/*!****************************************************************************
*
* @par Description:
*    This function  gets the smbus information for a specific DIMM slot.
*
*                                  @param
*    ddr_chan         DDR channel of the DIMM to inspect.
*                                  @param
*    dimm_slot        Slot in the DDR channel of the DIMM to inspect.
*                                  @param
*    smbus_info_ptr   Pointer to a structure filled in with the SMBus
*                      information for the indicated DIMM slot.
*
* @return
*    An indication of the level of success.
*
* @author
*    gkowis
*
******************************************************************************/
unsigned spd_smbus_get_dimm_slot_info
(
    unsigned ddr_chan,
    unsigned dimm_slot,
    dimm_slot_smbus_info_t *smbus_info_ptr
)
{
    unsigned status = COM_ERROR;


    if ((ddr_chan <= 5) && (dimm_slot <= 1))
    {
        status = COM_OK;

        smbus_info_ptr->smbus_id = spd_smbus_info[ddr_chan][dimm_slot].smbus_id;
        smbus_info_ptr->spd_eeprom_bus_addr = spd_smbus_info[ddr_chan][dimm_slot].spd_eeprom_bus_addr;
        smbus_info_ptr->spd_ts_bus_addr = spd_smbus_info[ddr_chan][dimm_slot].spd_ts_bus_addr;
        smbus_info_ptr->spd_cmd_bus_addr = spd_smbus_info[ddr_chan][dimm_slot].spd_cmd_bus_addr;
        smbus_info_ptr->rcd_bus_addr = spd_smbus_info[ddr_chan][dimm_slot].rcd_bus_addr;
    }

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function initializes the Serial Presence Detect (SPD) Temperature
*     Sensor found on certain DIMMs, utilizing the System Management Bus (SMBUS)
*     Protocol.
*
*                                  @param
*    mddr_settings_ptr  The pointer to the structure containing the
*                        settings information.
*                                  @param
*    ddr_chan           DDR channel to perform function on.
*
*
* @return
*    The status indicating the level of success in initializing the SPD TS.
*
* @author
*    anthonyf
*
******************************************************************************/
unsigned spd_ts_smbus_init(mddr_settings_t *mddr_settings_ptr, uint8_t ddr_chan)
{
    unsigned status = COM_OK;
    uint8_t dimm_slot;
    dimm_slot_smbus_info_t smbus_info;

    uint16_t configuration;
    uint16_t tcrit_limit;

    for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
    {
        if(mddr_dimm_configs[ddr_chan][dimm_slot].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            // Find the SMBus information for the DIMM slot.
            status |= spd_smbus_get_dimm_slot_info(ddr_chan, dimm_slot, &smbus_info);

            if (status == COM_OK)   // valid chan & slot combination
            {
                if (mddr_dimm_configs[ddr_chan][dimm_slot].has_therm_sensor)
                {

                    // Clear Critical Temperature and Event Output enables.
                    //  This is required to be done prior to changing other settings in the configuration register.
                    //  Additionally, the event output setting survives a system reset, therefore it needs to be explicitly
                    //  disabled in case it was enabled on the previous boot.

                    monaco_log(LOW, "Disabling Critical Temperature and Event Output enables on channel %u slot %u.\n",
                               hddrss[ddr_chan],
                               dimm_slot);

                    status |= spd_smbus_get_word((uint32_t) smbus_info.smbus_id,
                                                 (uint32_t) smbus_info.spd_ts_bus_addr,
                                                 (uint16_t) SPD_TS_CONFIGURATION,
                                                 &configuration);

                    configuration &= ~((SPD_TS_CONFIGURATION_TCRIT_ONLY___M<<SPD_TS_CONFIGURATION_TCRIT_ONLY___S) |
                                      (SPD_TS_CONFIGURATION_EVENT_CTRL___M<<SPD_TS_CONFIGURATION_EVENT_CTRL___S));

                    monaco_log(INFORMATIONAL, "Setting SPD_TS_CONFIGURATION to 0x%016x.\n", configuration);
                    status |= spd_smbus_set_word((uint32_t) smbus_info.smbus_id,
                                                 (uint32_t) smbus_info.spd_ts_bus_addr,
                                                 (uint16_t) SPD_TS_CONFIGURATION,
                                                 configuration);



                    if (mddr_settings_ptr->tcrit_event_en)
                    {
                        monaco_log(LOW, "Enabling Critical Temperature Event for %d C on channel %u slot %u.\n",
                                   mddr_settings_ptr->tcrit_threshhold,
                                   hddrss[ddr_chan],
                                   dimm_slot);


                        // Set Critical Temperature Limit.

                        tcrit_limit = (mddr_settings_ptr->tcrit_threshhold & SPD_TS_TCRIT_LIMIT_TEMP_WHOLE___M)<<SPD_TS_TCRIT_LIMIT_TEMP_WHOLE___S;

                        monaco_log(INFORMATIONAL, "Setting SPD_TS_TCRIT_LIMIT register to 0x%016x.\n", tcrit_limit);
                        status |= spd_smbus_set_word((uint32_t) smbus_info.smbus_id,
                                                     (uint32_t) smbus_info.spd_ts_bus_addr,
                                                     (uint16_t) SPD_TS_TCRIT_LIMIT,
                                                     tcrit_limit);


                        // Set Critical Temperature and Event Output enables.

                        configuration |= ((SPD_TS_CONFIGURATION_TCRIT_ONLY___M<<SPD_TS_CONFIGURATION_TCRIT_ONLY___S) |
                                          (SPD_TS_CONFIGURATION_EVENT_CTRL___M<<SPD_TS_CONFIGURATION_EVENT_CTRL___S));

                        monaco_log(INFORMATIONAL, "Setting SPD_TS_CONFIGURATION to 0x%016x.\n", configuration);
                        status |= spd_smbus_set_word((uint32_t) smbus_info.smbus_id,
                                                     (uint32_t) smbus_info.spd_ts_bus_addr,
                                                     (uint16_t) SPD_TS_CONFIGURATION,
                                                     configuration);

                    }

                }
                else // DIMM has no thermal sensor
                {
                    if (mddr_settings_ptr->tcrit_event_en)
                    {
                        monaco_log(HIGH, "Ignoring DIMM TCRIT Event enable on on channel %u slot %u because TS not detected.\n",
                                   hddrss[ddr_chan],
                                   dimm_slot);
                    }
                }
            }
        }
    }

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function reads a block of SPD information.
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be retrieved.
*                                  @param
*    block_size       Size of the block of SPD information to retrieve.
*                                  @param
*    dst_buff_addr    Address of the buffer to receive the SPD information.
*
*
* @return
*    An indication of the level of success.
*
* @author
*    gkowis/cbucsan
*
* @par Notes:
*    Dispatcher to both the simulated SMBus and the real SMBus.
*
******************************************************************************/
unsigned spd_smbus_get_spd_block
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    unsigned block_size,
    uint64_t dst_buff_addr
)
{
    unsigned status = COM_OK;
    unsigned xfer_block_size;
    unsigned spd_reg_id = 0x0;    // Start with the first register in the SPD.
    unsigned curr_block_size;
    uint8_t spd_bank_num = 0;
    uint64_t orig_dst_buff_addr;

    curr_block_size = block_size;
    orig_dst_buff_addr = dst_buff_addr;

    // The SMBus transfers are limited by the size of the I2C FIFO
    // So getting the complete block must be broken down into smaller
    //  blocks that can fit in the FIFO.
    do
    {
        if (curr_block_size > SPD_SMBUS_MAX_FIFO_BLOCK_SIZE)
        {
            xfer_block_size = SPD_SMBUS_MAX_FIFO_BLOCK_SIZE;
        }
        else
        {
            xfer_block_size = curr_block_size;
        }

        if (spd_use_simulated_spd == true)
        {
            status = spd_simm_get_spd_block(smbus_id, spd_bus_addr, spd_reg_id, xfer_block_size, dst_buff_addr);
        }
        else
        {
        #ifdef __BAREMETAL__
            status = spd_smbus_dimm_get_block(smbus_id, spd_bus_addr, spd_bank_num, spd_reg_id, xfer_block_size, (void*) dst_buff_addr);
        #else
            // registers are a byte wide
            int result = ddr_smbus_block_read((uint32_t)smbus_id, spd_bus_addr, spd_bank_num, spd_reg_id, (void*) dst_buff_addr, xfer_block_size);
            status = (result == 0) ? COM_OK : COM_ERROR;
        #endif
        }

        if(status == COM_ERROR)
        {
            return status;
        }

        spd_reg_id = spd_reg_id + xfer_block_size;

        if (spd_reg_id >= SPD_BLOCK_SIZE)
        {
            spd_reg_id -= SPD_BLOCK_SIZE;
            spd_bank_num = 1;
        }

        dst_buff_addr = dst_buff_addr + xfer_block_size;
        curr_block_size = curr_block_size - xfer_block_size;
    } while ((curr_block_size > 0) && (status == COM_OK));

    // Perform a CRC check for the first 256 B
    status = spd_smbus_check_CRC(orig_dst_buff_addr, block_size);

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function reads a 16-bit word from the indicated SMBus target.
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be retrieved.
*                                  @param
*    spd_reg_id       The SPD register id of the start of the information to
*                                  @param
*    spd_data_ptr     Pointer to where the SPD data word is to be stored.
*
* @return
*    Status indicating if the data could be retrieved from the indicated SMBus.
*
* @author
*    gkowis
*
* @par Notes:
*    Dispatcher to both the simulated SMBus and the real SMBus.
*
******************************************************************************/
unsigned spd_smbus_get_word
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint16_t spd_reg_id,
    uint16_t *spd_data_ptr
)
{
    unsigned status = COM_ERROR;

    if (spd_use_simulated_spd == true)
    {
        status = spd_simm_get_word(smbus_id, spd_bus_addr, spd_reg_id, spd_data_ptr);
    }
    else
    {
    #ifdef __BAREMETAL__
        status = spd_smbus_dimm_get_word(smbus_id, spd_bus_addr, spd_reg_id, spd_data_ptr);
    #else
        int result = ddr_smbus_read_data_word((uint32_t)smbus_id, spd_bus_addr, spd_reg_id, spd_data_ptr);
        status = (result == 0) ? COM_OK : COM_ERROR;
    #endif
    }


    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function reads an 8-bit byte from the indicated SMBus target.
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be retrieved.
*                                  @param
*    spd_reg_id       The SPD register id of the start of the information to
*                      be retrieved.
*                                  @param
*    spd_data_ptr     Pointer to where the SPD data byte is to be stored.
*
* @return
*    Status indicating if the data could be retrieved from the indicated SMBus.
*
* @author
*    gkowis
*
* @par Notes:
*    Dispatcher to both the simulated SMBus and the real SMBus.
*
******************************************************************************/
unsigned spd_smbus_get_byte
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint16_t spd_reg_id,
    uint8_t *spd_data_ptr
)
{
    unsigned status = COM_ERROR;

    if (spd_use_simulated_spd == true)
    {
        status = spd_simm_get_byte(smbus_id, spd_bus_addr, spd_reg_id, spd_data_ptr);
    }
    else
    {
    #ifdef __BAREMETAL__
        status = spd_smbus_dimm_get_byte(smbus_id, spd_bus_addr, spd_reg_id, spd_data_ptr);
    #else
        int result = ddr_smbus_read_data_byte((uint32_t)smbus_id, spd_bus_addr, spd_reg_id, spd_data_ptr);
        status = (result == 0) ? COM_OK : COM_ERROR;
    #endif
    }

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function writes a block of SPD information.
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be retrieved.
*                                  @param
*    block_size       Size of the block of SPD information to retrieve.
*                                  @param
*    src_buff_addr    Address of the buffer to source the SPD information.
*
*
* @return
*    An indication of the level of success.
*
* @author
*    lchavani/anthonyf
*
******************************************************************************/
unsigned spd_smbus_set_spd_block
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    unsigned block_size,
    uint64_t src_buff_addr
)
{
    unsigned status = COM_ERROR;

    // TODO: This is just a stub until the actual function contents are implemented.
    monaco_log(CRITICAL, "WARNING: SPD Block Write functionality does not exist yet! Just printing out the arguments instead.\n");
    monaco_log(LOW, "   %s = 0x%X.\n", MDDR_GET_VAR_NAME(smbus_id), smbus_id);
    monaco_log(LOW, "   %s = 0x%X.\n", MDDR_GET_VAR_NAME(spd_bus_addr), spd_bus_addr);
    monaco_log(LOW, "   %s = 0x%X.\n", MDDR_GET_VAR_NAME(block_size), block_size);
    monaco_log(LOW, "   %s = 0x%X.\n", MDDR_GET_VAR_NAME(src_buff_addr), src_buff_addr);
    status = COM_OK;

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function writes a 16-bit word to the indicated SMBus target.
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be set.
*                                  @param
*    spd_reg_id       The SPD register id of the start of the information to
*                      be set.
*                                  @param
*    spd_data         The SPD data to be written.
*
* @return
*    Status indicating if the data could be written to the indicated SMBus.
*
* @author
*    lchavani/anthonyf
*
* @par Notes:
*    Dispatcher to both the simulated SMBus and the real SMBus.
*
******************************************************************************/
unsigned spd_smbus_set_word
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint16_t spd_reg_id,
    uint16_t spd_data
)
{
    unsigned status = COM_ERROR;

    if (spd_use_simulated_spd == true)
    {
        status = spd_simm_set_word(smbus_id, spd_bus_addr, spd_reg_id, spd_data);
    }
    else
    {
    #ifdef __BAREMETAL__
        status = spd_smbus_dimm_set_word(smbus_id, spd_bus_addr, spd_reg_id, spd_data);
    #else
        int result = ddr_smbus_write_data_word((uint32_t)smbus_id, spd_bus_addr, spd_reg_id, spd_data);
        status = (result == 0) ? COM_OK : COM_ERROR;
    #endif
    }

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function writes an 8-bit byte to the indicated SMBus target.
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be set.
*                                  @param
*    spd_reg_id       The SPD register id of the start of the information to
*                      be set.
*                                  @param
*    spd_data         The SPD data to be written.
*
* @return
*    Status indicating if the data could be written to the indicated SMBus.
*
* @author
*    lchavani/anthonyf
*
* @par Notes:
*    Dispatcher to both the simulated SMBus and the real SMBus.
*
******************************************************************************/
unsigned spd_smbus_set_byte
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint16_t spd_reg_id,
    uint8_t spd_data
)
{
    unsigned status = COM_ERROR;

    if (spd_use_simulated_spd == true)
    {
        status = spd_simm_set_byte(smbus_id, spd_bus_addr, spd_reg_id, spd_data);
    }
    else
    {
    #ifdef __BAREMETAL__
        status = spd_smbus_dimm_set_byte(smbus_id, spd_bus_addr, spd_reg_id, spd_data);
    #else
        int result = ddr_smbus_write_data_byte((uint32_t)smbus_id, spd_bus_addr, spd_reg_id, spd_data);
        status = (result == 0) ? COM_OK : COM_ERROR;
    #endif
    }

    return status;
}



/******************************************************************************
* Internal Functions
******************************************************************************/

/*!****************************************************************************
* @par Description:
*     Checks the CRC of the SPD info, both sections if available
*
*
*                                  @param
*    addr             The starting location of the SPD info
*
*                                  @param
*    block_size       The size of the SPD block retrieved from the EEPROM.
*
*
* @return
*    Success or fail
*
* @author
*    mwuu/cbucsan
*
* @par Notes:
*    This function is used to compare 2 calculated CRC16s with the following
*     2 two-byte fields located in the SPD info:
*    1. Byte 126 is the CRC for the Base Config Section, LSB and byte 127 is
*     the CRC16 for the Base Config Section, MSB.
*    2. Byte 254 is the CRC for module specific Section, LSB and byte 255 is
*     the CRC for the module Specific Section, MSB.
*
******************************************************************************/
unsigned spd_smbus_check_CRC(uint64_t addr, uint32_t block_size)
{

    unsigned status = COM_OK;
    uint32_t  from_spd, sec_chk;
    uint16_t chk_size, crc_size, crc16;


    // The CRC bytes are located at 0x7E and 0x7F, so if
    //  the load size is less than that we can't check
    if (block_size >= 0x7F)
    {

        crc_size = read8(addr);

        if ((crc_size >> 7) == 0x1)
        {
            chk_size = 0x74;      // for DDR3 only
            sec_chk = 0;
        }
        else
        {
            chk_size = 0x7D;      // DDR4 is always like this
            sec_chk = 1;
        }

        from_spd = read32(addr + 0x7C) >> 16;

        crc16 = check_crc16((void*) addr, chk_size);


        if (from_spd != crc16)
        {
            status=COM_ERROR;

            monaco_log(CRITICAL, "ERROR: SPD failed 1st CRC check! \n");
        }

        // 2nd part, extended region; bytes 128~253 (0x80~0xFD)
        if ((block_size >= 0xFF) && (status == COM_OK) && (sec_chk == 1))
        {
            uint64_t sec_addr;

            sec_addr = addr + 0x80;
            chk_size = 0xFD - 0x80;
            from_spd= read32( addr + 0xFC) >>16;

            crc16 = check_crc16((void*) sec_addr, chk_size);


            if (from_spd != crc16)
            {
                status=COM_ERROR;

                monaco_log(CRITICAL, "ERROR: SPD failed 2nd CRC check! \n");
            }
        }
    }

    return status;
}



/*!****************************************************************************
* @par Description:
*    CRC16 calculation following the algorithm in the device spec.
*
*
*                                  @param
*    addr             Pointer to the starting location of the SPD info
*
*                                  @param
*    count           The number of bytes to calculate the CRC16 from.
*
*
* @return
*    Success or fail
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
uint16_t check_crc16(void* addr, int count)
{

    uint16_t crc, i;
    crc = 0;
    char *ptr = addr;
    int data16;
    uint16_t new_count = count + 1;

    while (new_count--)
    {
        data16 = (int)*ptr++;
//        crc = crc ^ (int)*ptr++ << 8;
        crc = crc ^ data16 << 8;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        }
    }

    return (crc & 0xFFFF);
}

