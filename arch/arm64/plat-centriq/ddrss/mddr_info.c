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
* @file mddr_info.c
*
* @par Description:
*    This module collects and makes available MDDR component, sub-system and
*    configuration information.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
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

extern mddr_settings_t mddr_settings;


/******************************************************************************
* Macros
******************************************************************************/



/******************************************************************************
* Function Prototypes
******************************************************************************/

void mddr_copy_dimm_spd_info(spd_dimm_config_t *src_spd_info_ptr, spd_dimm_config_t *dst_spd_info_ptr);
void mddr_copy_init_setting(mddr_settings_t *settings_ptr);
uint32_t mddr_read_dcvs_bcqfull_shadow_reg(uint8_t chan_num);
uint32_t mddr_read_dcvs_busy_shadow_reg(uint8_t chan_num);
bool mddr_dcvs_bcqfull_enabled(uint8_t chan_num);
bool mddr_dcvs_busy_enabled(uint8_t chan_num);



/******************************************************************************
* External Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    The mddr_get_cfg_info() function is used to get the configuration
*     information for all DDR channels. The only parameter is a pointer to a
*     mddr_cfg_t structure. The structure, provided by the caller, will be
*     populated by the function. A channel that does not have any DIMMs will
*     have a count of 0 in the field num_slots_populated found in the channels
*     specific entry in the chan_cfg[] array.
*
*                                  @param
*    mddr_cfg_ptr        Pointer to the MDDR configuration information
*                         structure populated by this function.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
void mddr_get_cfg_info(mddr_cfg_t *mddr_cfg_ptr)
{
    uint8_t chan_num;
    uint8_t num_chans_active = 0;
    uint8_t chan_map = 0x0;


    for(chan_num = 0; chan_num < DDR_MAX_NUM_CHANS; ++chan_num)
    {
        mddr_get_chan_cfg_info(chan_num, &(mddr_cfg_ptr->chan_cfg[chan_num]));

        if(mddr_cfg_ptr->chan_cfg[chan_num].num_slots_populated != 0)
        {
            ++num_chans_active;
            chan_map |= 0x1 << chan_num;
        }
    }

    mddr_cfg_ptr->num_chans_supported = DDR_MAX_NUM_CHANS;
    mddr_cfg_ptr->chan_map = chan_map;
    mddr_cfg_ptr->num_chans_active = num_chans_active;
    mddr_copy_init_setting(&(mddr_cfg_ptr->mddr_settings));
}


/*!****************************************************************************
*
* @par Description:
*    This function is used to get the configuration information for a specific
*     DDR channel. The parameters are the number of the channel and a pointer
*     to a mddr_chan_cfg_t structure. The structure, provided by the caller,
*     will be populated by the function. A channel that does not have any DIMMs
*     will have a count of 0 in the field num_slots_populated.
*
*                                  @param
*    chan_num            The DDR channel to inspect.
*                                  @param
*    mddr_chan_cfg_ptr   Pointer to the channel configuration information
*                         structure populated by this function.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
void mddr_get_chan_cfg_info(uint8_t chan_num, mddr_chan_cfg_t *mddr_chan_cfg_ptr)
{
    uint8_t slot_num;
    uint8_t num_slots_populated = 0;
    uint8_t slot_map = 0x0;
    uint32_t ddr_size_mb = 0;


    for(slot_num = 0; slot_num < DDR_MAX_NUM_SLOTS_PER_CHAN; ++slot_num)
    {
        if(mddr_dimm_configs[chan_num][slot_num].dev_type != SPD_DEVICE_TYPE_UNDEFINED)
        {
            ddr_size_mb += mddr_dimm_configs[chan_num][slot_num].dimm_size_mb;
            ++num_slots_populated;
            slot_map |= 0x1 << slot_num;
        }
    }

    mddr_chan_cfg_ptr->num_slots_supported = mddr_settings.num_dimm_slots;
    mddr_chan_cfg_ptr->num_slots_populated = num_slots_populated;
    mddr_chan_cfg_ptr->slot_map = slot_map;
    mddr_chan_cfg_ptr->mem_size_gb = ddr_size_mb / MB_PER_GB;
}



/*!****************************************************************************
*
* @par Description:
*    This function gets the translated SPD information for all populated
*     DIMMs.
*
*                                  @param
*    spd_info_ptr        Pointer to the SPD information structure populated
*                         by this function.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
void mddr_get_spd_info(mddr_spd_info_t *spd_info_ptr)
{
    uint8_t chan_num;
    uint8_t slot_num;


    for(chan_num = 0; chan_num < DDR_MAX_NUM_CHANS; ++chan_num)
    {
        for(slot_num = 0; slot_num < DDR_MAX_NUM_SLOTS_PER_CHAN; ++slot_num)
        {
            mddr_copy_dimm_spd_info(&(mddr_dimm_configs[chan_num][slot_num]),
                                    &(spd_info_ptr->dimm_spd[chan_num][slot_num]));
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function gets the translated SPD information for the indicated
*     DIMM.
*
*                                  @param
*    chan_num           The DDR channel number of the DIMM.
*                                  @param
*    slot_num           The slot number in the DDR channel of the DIMM.
*                                  @param
*    spd_info_ptr       Pointer to the DIMM SPD configuration structure
*                         populated by this function.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
void mddr_get_dimm_spd_info
(
    uint8_t chan_num,
    uint8_t slot_num,
    spd_dimm_config_t *spd_info_ptr
)
{
    mddr_copy_dimm_spd_info(&(mddr_dimm_configs[chan_num][slot_num]), spd_info_ptr);
}



/*!****************************************************************************
*
* @par Description:
*    This function collects the DIMM temperatures from all populated DIMMs.
*
*                                  @param
*    dimm_therm_ptr     Pointer to the DIMM thermal information structure
*                        populated by this function.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    The DIMM temps for slots that are unpopulated, or which lack a temperature
*    sensor, will be MDDR_DIMM_TEMP_INVALID and the DIMM event asserted status
*    will be false.
*
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
void mddr_get_therm_info(mddr_dimm_therm_t *dimm_therm_ptr)
{
    uint8_t chan_num;
    uint8_t slot_num;

    for(chan_num = 0; chan_num < DDR_MAX_NUM_CHANS; ++chan_num)
    {
        for(slot_num = 0; slot_num < DDR_MAX_NUM_SLOTS_PER_CHAN; ++slot_num)
        {
            dimm_therm_ptr->dimm_temps[chan_num][slot_num] = mddr_get_dimm_temp(chan_num, slot_num);
            dimm_therm_ptr->dimm_eventn_asserted[chan_num][slot_num] = mddr_get_dimm_eventn_asserted(chan_num, slot_num);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function gets the DIMM temperature from the indicated DIMM.
*
*                                  @param
*    chan_num           The DDR channel number of the DIMM.
*                                  @param
*    slot_num           The slot number in the DDR channel of the DIMM.
*
*
* @return
*    The temperature from a specific DIMM in degrees C. DIMM temperatureis a
*     signed 13 bit 2's complement integer value where the low order 4 bits are
*     the fractional degree componentas defined by JEDEC Standard No. 21-C
*     Release 24, Page 4.1.6 – 23 section 2.22. Where bit-0 => 0.0625;
*     bit-1=> 0.125; bit-2=> 0.25; bit-3> 0.5. The value will be
*     MDDR_DIMM_TEMP_INVALID for slots that are unpopulated or whose
*     DIMM lacks a thermal sensor.
*
* @author
*    gkowis
*
* @par Notes:
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
int16_t mddr_get_dimm_temp(uint8_t chan_num, uint8_t slot_num)
{
    int16_t dimm_temp = MDDR_DIMM_TEMP_INVALID;

    // Read the temp if the DIMM has a thermal sensor.
    if((mddr_dimm_configs[chan_num][slot_num].dev_type != SPD_DEVICE_TYPE_UNDEFINED) &&
       (mddr_dimm_configs[chan_num][slot_num].has_therm_sensor))
    {
        dimm_temp = spd_get_dimm_temp(chan_num, slot_num);
    }

    return dimm_temp;
}



/*!****************************************************************************
*
* @par Description:
*    This function gets the DIMM EVENT_n signal from the indicated DIMM.
*
*                                  @param
*    chan_num           The DDR channel number of the DIMM.
*                                  @param
*    slot_num           The slot number in the DDR channel of the DIMM.
*
*
* @return
*    The status from the DIMM Temperature Sensor (TS) indicating whether the
*     EVENT_n signal is asserted.  Use of this signal is described by JEDEC
*     Standard No. 21-C Release 26, Page 4.1.6 – 16 section 2.17.  The value
*     will be false for slots that are unpopulated or whose DIMM lacks a thermal
*     sensor.
*
* @author
*    anthonyf
*
* @par Notes:
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
bool mddr_get_dimm_eventn_asserted(uint8_t chan_num, uint8_t slot_num)
{
    bool eventn_status = false;

    // Read the event_n status if the DIMM has a thermal sensor.
    if((mddr_dimm_configs[chan_num][slot_num].dev_type != SPD_DEVICE_TYPE_UNDEFINED) &&
       (mddr_dimm_configs[chan_num][slot_num].has_therm_sensor))
    {
        eventn_status = spd_get_dimm_eventn_asserted(chan_num, slot_num);
    }

    return eventn_status;
}



/*!****************************************************************************
*
* @par Description:
*    This function collects Bus Utilization Monitor (BUM) information for all
*     BUM events.
*
*                                  @param
*    dimm_bum_info_ptr   Pointer to the BUM utilization information structure
*                         populated by this function.  The array is populated
*                         based on physical channel number and event number.
*
* @return
*    None
*
* @author
*    anthonyf
*
* @par Notes:
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
void mddr_get_bum_info(mddr_bum_info_t *mddr_bum_info_ptr)
{
    uint8_t chan_num;
    uint8_t physical_chan_num;
    bool chan_populated;
    uint64_t mddr_base_addr;

    for(chan_num = 0; chan_num < DDR_MAX_NUM_CHANS; ++chan_num)
    {
        physical_chan_num=hddrss[chan_num];

        chan_populated = mddr_check_chan_populated(chan_num);
        if(chan_populated)
        {
            mddr_bum_info_ptr->ddr_bum_counts[physical_chan_num][DDR_BUM_EVENT_BCQFULL] = mddr_read_dcvs_bcqfull_shadow_reg(chan_num);
            mddr_bum_info_ptr->ddr_bum_enables[physical_chan_num][DDR_BUM_EVENT_BCQFULL] = mddr_dcvs_bcqfull_enabled(chan_num);

            mddr_bum_info_ptr->ddr_bum_counts[physical_chan_num][DDR_BUM_EVENT_BUSY] = mddr_read_dcvs_busy_shadow_reg(chan_num);
            mddr_bum_info_ptr->ddr_bum_enables[physical_chan_num][DDR_BUM_EVENT_BUSY] = mddr_dcvs_busy_enabled(chan_num);

            mddr_base_addr = mddr_base_addrs[chan_num];
            mddr_mc_wait_us(mddr_base_addr, 1);     // Protect against back to back reads of shadow registers
        }
        else
        {
            // Report zero/false for unpopulated channels
            mddr_bum_info_ptr->ddr_bum_counts[physical_chan_num][DDR_BUM_EVENT_BCQFULL] = 0;
            mddr_bum_info_ptr->ddr_bum_enables[physical_chan_num][DDR_BUM_EVENT_BCQFULL] = false;

            mddr_bum_info_ptr->ddr_bum_counts[physical_chan_num][DDR_BUM_EVENT_BUSY] = 0;
            mddr_bum_info_ptr->ddr_bum_enables[physical_chan_num][DDR_BUM_EVENT_BUSY] = false;
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function collects DDR sub-system state information, including
*     Power-Down and Self-Refresh.
*
*                                  @param
*    mddr_state_info_ptr  Pointer to the DDR State Information structure
*                          populated by this function.  The array is populated
*                          based on physical channel number.
*
* @return
*    None
*
* @author
*    anthonyf
*
* @par Notes:
*    The call should be made only after the driver has been initialized
*    successfully.
*
******************************************************************************/
void get_ddr_state(mddr_state_info_t *mddr_state_info_ptr)
{
    uint8_t ddr_chan;
    uint8_t dimm_slot;

    uint64_t mddr_base_addr;
    bool chan_populated;

    uint32_t device_state;
    uint8_t cke_in_pwr_down;
    uint8_t cke_in_self_ref;

    uint32_t auto_ref_cntl;
    uint8_t ref_rate_adj_dimm_0;
    uint8_t ref_rate_adj_dimm_1;

    spd_dimm_config_t *cfg_ptr;


    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);
        mddr_base_addr = mddr_base_addrs[ddr_chan];

        if(chan_populated)
        {
            mddr_mc_wait_us(mddr_base_addr, 1);
            device_state = read32(mddr_base_addr + MDDR_DDR_DEVICE_STATE_OFFSET);

            mddr_mc_wait_us(mddr_base_addr, 1);
            auto_ref_cntl = read32(mddr_base_addr + MDDR_DDR_AUTO_REF_CNTL_OFFSET);

        }
        else
        {
            device_state = 0x0;
            auto_ref_cntl = 0x0;
        }

        cke_in_pwr_down = (device_state >> DEVICE_STATE_CKE_IN_PWR_DOWN___S) & DEVICE_STATE_CKE_IN_PWR_DOWN___M;
        cke_in_self_ref = (device_state >> DEVICE_STATE_CKE_IN_SELF_REF___S) & DEVICE_STATE_CKE_IN_SELF_REF___M;

        ref_rate_adj_dimm_0 = (auto_ref_cntl >> AUTO_REF_CNTL_ADJ_DIMM0___S) & AUTO_REF_CNTL_ADJ_DIMM0___M;
        ref_rate_adj_dimm_1 = (auto_ref_cntl >> AUTO_REF_CNTL_ADJ_DIMM1___S) & AUTO_REF_CNTL_ADJ_DIMM1___M;


        for(dimm_slot = 0; dimm_slot < DDR_MAX_NUM_SLOTS_PER_CHAN; ++dimm_slot)
        {
            cfg_ptr = &(mddr_dimm_configs[ddr_chan][dimm_slot]);

            if (cfg_ptr->num_ranks == DDR_RANKS_QUAD_CS_DIMM)   // Direct Quad-CS DIMM
            {
                mddr_state_info_ptr->dimm_in_pd[ddr_chan][dimm_slot] = cke_in_pwr_down & 0xF;
                mddr_state_info_ptr->dimm_in_sr[ddr_chan][dimm_slot] = cke_in_self_ref & 0xF;
            }
            else // DDR_RANKS_DUAL_CS_DIMM or DDR_RANKS_SINGLE_CS_DIMM
            {
                mddr_state_info_ptr->dimm_in_pd[ddr_chan][dimm_slot] = cke_in_pwr_down & (0x3 << dimm_slot*2);
                mddr_state_info_ptr->dimm_in_sr[ddr_chan][dimm_slot] = cke_in_self_ref & (0x3 << dimm_slot*2);
            }

            if (dimm_slot == 0)
            {
                mddr_state_info_ptr->dimm_ref_rate_adj[ddr_chan][dimm_slot] = ref_rate_adj_dimm_0;
            }
            else
            {
                mddr_state_info_ptr->dimm_ref_rate_adj[ddr_chan][dimm_slot] = ref_rate_adj_dimm_1;
            }

        }
    }
}


/******************************************************************************
* Local Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function copies a DIMM SPD information structure, spd_dimm_config_t,
*     to another DIMM SPD information structure. Used to get a copy of internal
*     data and make it available to higher level / application software.
*
*                                  @param
*    src_spd_info_ptr     Pointer to DIMM SPD information structure that is
*                          the source of the copy.
*                                  @param
*    dst_spd_info_ptr     Pointer to DIMM SPD information structure that is
*                          the destination of the copy.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_copy_dimm_spd_info(spd_dimm_config_t *src_spd_info_ptr, spd_dimm_config_t *dst_spd_info_ptr)
{
    uint16_t size_bytes;
    uint8_t *src_ptr;
    uint8_t *dst_ptr;

    size_bytes = sizeof(spd_dimm_config_t);
    src_ptr = (uint8_t *)src_spd_info_ptr;
    dst_ptr = (uint8_t *)dst_spd_info_ptr;

    com_blk_copy(src_ptr, dst_ptr, size_bytes);
}



/*!****************************************************************************
*
* @par Description:
*    This function copies the contents of the internal MDDR settings to the
*     provided MDDR settings structure.
*
*                                  @param
*    settings_ptr         Pointer to MDDR settings structure that is
*                          the destination of the copy.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_copy_init_setting(mddr_settings_t *settings_ptr)
{
    uint16_t size_bytes;
    uint8_t *src_ptr;
    uint8_t *dst_ptr;

    size_bytes = sizeof(mddr_settings_t);
    src_ptr = (uint8_t *)&mddr_settings;
    dst_ptr = (uint8_t *)settings_ptr;

    com_blk_copy(src_ptr, dst_ptr, size_bytes);
}


/*!****************************************************************************
*
* @par Description:
*    This function reports the contents of a Bus Utilization Monitor (BUM)
*     Shadow Count Register for the BCQ Full event.
*
*
* @return
*    Shadow Count Register value
*
* @author
*    anthonyf
*
******************************************************************************/
uint32_t mddr_read_dcvs_bcqfull_shadow_reg(uint8_t chan_num)
{
    uint64_t mddr_base_addr;
    uint32_t reg_value = 0xDEADBEEF;

    mddr_base_addr = mddr_base_addrs[chan_num];
    reg_value = read32(mddr_base_addr + MDDR_DCVS_BCQFULL_SHADOW_OFFSET);

    return reg_value;
}


/*!****************************************************************************
*
* @par Description:
*    This function reports the contents of a Bus Utilization Monitor (BUM)
*     Shadow Count Register for the Busy event.
*
*
* @return
*    Shadow Count Register value
*
* @author
*    anthonyf
*
******************************************************************************/
uint32_t mddr_read_dcvs_busy_shadow_reg(uint8_t chan_num)
{
    uint64_t mddr_base_addr;
    uint32_t reg_value = 0xDEADBEEF;

    mddr_base_addr = mddr_base_addrs[chan_num];
    reg_value = read32(mddr_base_addr + MDDR_DCVS_BUSY_SHADOW_OFFSET);

    return reg_value;
}


/*!****************************************************************************
*
* @par Description:
*    This function reports whether the Bus Utilization Monitor (BUM)
*     BCQ Full event counter is enabled in the DDR controller.
*
*
* @return
*    true if enabled and false if disabled
*
* @author
*    anthonyf
*
******************************************************************************/
bool mddr_dcvs_bcqfull_enabled(uint8_t chan_num)
{
    uint64_t mddr_base_addr;
    uint32_t reg_value;
    bool is_enabled = false;

    mddr_base_addr = mddr_base_addrs[chan_num];
    reg_value = read32(mddr_base_addr + MDDR_DCVS_CNTL_OFFSET);

    is_enabled = ~(reg_value>>DCVS_CNTL_BCQFULL_CNT_DISABLE___S) & DCVS_CNTL_BCQFULL_CNT_DISABLE___M;

    return is_enabled;
}


/*!****************************************************************************
*
* @par Description:
*    This function reports whether the Bus Utilization Monitor (BUM)
*     Busy event counter is enabled in the DDR controller.
*
*
* @return
*    true if enabled and false if disabled
*
* @author
*    anthonyf
*
******************************************************************************/
bool mddr_dcvs_busy_enabled(uint8_t chan_num)
{
    uint64_t mddr_base_addr;
    uint32_t reg_value;
    bool is_enabled = false;

    mddr_base_addr = mddr_base_addrs[chan_num];
    reg_value = read32(mddr_base_addr + MDDR_DCVS_CNTL_OFFSET);

    is_enabled = ~(reg_value>>DCVS_CNTL_BUSY_CNT_DISABLE___S) & DCVS_CNTL_BUSY_CNT_DISABLE___M;

    return is_enabled;
}


