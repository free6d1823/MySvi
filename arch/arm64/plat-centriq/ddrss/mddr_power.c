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
* @file mddr_power.c
*
* @par Description:
*    This module provides the power related feature controls for the MDDR
*     subsystem. This includes such things as self-refresh controls and
*     thermal throttling controls.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
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



/******************************************************************************
* External Functions
******************************************************************************/

/*!****************************************************************************
*
* @par Description:
*    This function adjusts the thermal throttling settings for all active DDR
*     channels. If throttling is active at the time this call is made, it will
*     be temproarily disabled while the settings are adjusted and then
*     re-enabled.
*
*                                  @param
*    throttle_adj_ptr      Pointer to the structure containing the user
*                           adjustable parameters used to control thermal
*                           throttling.
*
* @return
*    None
*
* @author
*    gkowis/anthonyf
*
* @par Notes:
*    This will force all other thermal throttling controls to the defaults.
*
* @par
*    A leaky bucket algorithm is employed to throttle/un-throttle commands based
*     on an estimated heat buildup. A list of command types are assigned a
*     thermal weight (read_bl8_weight, read_bc4_weight, write_bl8_weight,
*     write_bc4_weight, pchg_weight, act_weight). An internal weighted sum
*     counter will accumulate thermal weights as commands are sent to a
*     particular DIMM, while in parallel a leaky bucket timer will continuously
*     count through a programmable time interval (sum_deplete_interval) and will
*     deplete a pre-set amount
*
* @par
*   This feature must be tuned in order to achieve an acceptable performance vs.
*    temperature balance. A simple tuning technique:
*     - If the user wishes to sacrifice performance in order to improve
*        temperature, sum_deplete_interval can be increased.
*     - If the user wishes to improve performance by sacrificing temperature
*        benefits, sum_deplete_interval can be decreased.
*
******************************************************************************/
void mddr_therm_throttle_adj(mddr_therm_throttle_adj_t *throttle_adj_ptr)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;
    mddr_therm_throttle_settings_t therm_throttle_settings;


    // Use  the default thermal throttling settings for everything
    if (platform_mode != SILICON)
    {
        therm_throttle_settings.read_bl8_weight = THERM_WEIGHT_READ_BL8_EMU;
        therm_throttle_settings.read_bc4_weight = THERM_WEIGHT_READ_BC4_EMU;
        therm_throttle_settings.write_bl8_weight = THERM_WEIGHT_WRITE_BL8_EMU;
        therm_throttle_settings.write_bc4_weight = THERM_WEIGHT_WRITE_BC4_EMU;
        therm_throttle_settings.pchg_weight = THERM_WEIGHT_PCHG_EMU;
        therm_throttle_settings.act_weight = THERM_WEIGHT_ACT_EMU;
        therm_throttle_settings.throttle_high_wm = THERM_THROTTLE_HIGH_WM_EMU;
        therm_throttle_settings.throttle_low_wm = THERM_THROTTLE_LOW_WM_EMU;
    }
    else
    {
        // values from HPG section 3, DDR Command Thermal Throttling
        therm_throttle_settings.read_bl8_weight = THERM_WEIGHT_READ_BL8_SIL;
        therm_throttle_settings.read_bc4_weight = THERM_WEIGHT_READ_BC4_SIL;
        therm_throttle_settings.write_bl8_weight = THERM_WEIGHT_WRITE_BL8_SIL;
        therm_throttle_settings.write_bc4_weight = THERM_WEIGHT_WRITE_BC4_SIL;
        therm_throttle_settings.pchg_weight = THERM_WEIGHT_PCHG_SIL;
        therm_throttle_settings.act_weight = THERM_WEIGHT_ACT_SIL;
        therm_throttle_settings.throttle_high_wm = THERM_THROTTLE_HIGH_WM_SIL;
        therm_throttle_settings.throttle_low_wm = THERM_THROTTLE_LOW_WM_SIL;
    }

    // Apply the leak amount and interval.
    therm_throttle_settings.sum_deplete_val = throttle_adj_ptr->sum_deplete_val;
    therm_throttle_settings.sum_deplete_interval = throttle_adj_ptr->sum_deplete_interval;

    // Update the saved thermal controls.
    mddr_mc_get_thermal_control_reg_vals(&therm_throttle_settings);

    // Set the controls for all active channels.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            mddr_base_addr = mddr_base_addrs[ddr_chan];

            // If throttling had been enabled, disable thermal throttling
            //  until after all settings are established.
            if (mddr_settings.therm_throttle_en)
            {
                mddr_mc_disable_thermal_control(mddr_base_addr);
            }

            // Update the thermal controls for the channel. The settings
            //   exclude the enable so that all settings can be changed
            //   cleanly.
            mddr_mc_set_thermal_control_reg_vals(mddr_base_addr);

            // If throttling had been enabled, re-enable enable thermal throttling
            //  after all settings are established.
            if (mddr_settings.therm_throttle_en)
            {
                mddr_mc_enable_thermal_control(mddr_base_addr);
            }
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function sets the values for the thermal throttling control registers
*     found in all active DDR memory controllers. If throttling is active at the
*     time this call is made, it will be temproarily disabled while the settings
*     are adjusted and then re-enabled.
*
*                                  @param
*    throttle_settings_ptr  Pointer to the structure containing the settings to
*                            be applied to the thermal throttling hardware.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    This function is intended for experimental purposes only and is not
*     exposed by default.
*
******************************************************************************/
void mddr_therm_throttle_exp_adj(mddr_therm_throttle_settings_t *throttle_settings_ptr)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;


    // Update the saved thermal controls.
    mddr_mc_get_thermal_control_reg_vals(throttle_settings_ptr);

    // Set the controls for all active channels.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {

            // Update the thermal controls for the channel.
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_mc_set_thermal_control_reg_vals(mddr_base_addr);

            // If throttling had been enabled, re-enable enable thermal throttling
            //  after all settings are established.
            if (mddr_settings.therm_throttle_en)
            {
                mddr_mc_enable_thermal_control(mddr_base_addr);
            }
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function enables thermal throttling for all active DDR channels.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_therm_throttle_enable(void)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;

    // Update the settings to reflect the current throttling state.
    mddr_settings.therm_throttle_en = true;

    // Set the controls for all active channels.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Update the thermal controls for the channel.
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_mc_enable_thermal_control(mddr_base_addr);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function disables thermal throttling for all active DDR channels.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_therm_throttle_disable(void)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;


    // Update the settings to reflect the current throttling state.
    mddr_settings.therm_throttle_en = false;

    // Set the controls for all active channels.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Update the thermal controls for the channel.
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_mc_disable_thermal_control(mddr_base_addr);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function enables auto power-down mode for the MDDR subsystem. This
*      allows the subsystem to conserve power based on the current usage pattern.
*
*                                  @param
*    idle_delay      The number of DDR clocks a channel should be idle before
*                     the MDDR susbsytem puts the memory into power down.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    Although the delay value is the same for all DDR channels, each channel
*     is independent. The implication is that the channels will enter and exit
*     power-down based on their own conditions and are unlikely to enter / exit
*     power-down at the same time.
*
******************************************************************************/
void mddr_auto_power_down_enable(uint32_t idle_delay)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;
    uint32_t auto_power_cntl_val;

        auto_power_cntl_val = mddr_reg_vals.ddr_power_down_cntl_val;

        // Clear out the old auto power-down fields
        auto_power_cntl_val &= ~(PWR_DOWN_CNTL_PD_ENTRY_IDLE_DELAY___M << PWR_DOWN_CNTL_PD_ENTRY_IDLE_DELAY___S);
        auto_power_cntl_val &= ~(PWR_DOWN_CNTL_EN_PD_ACT___M << PWR_DOWN_CNTL_EN_PD_ACT___S);

        auto_power_cntl_val |= (idle_delay & PWR_DOWN_CNTL_PD_ENTRY_IDLE_DELAY___M) << PWR_DOWN_CNTL_PD_ENTRY_IDLE_DELAY___S;
        auto_power_cntl_val |= (common_cfg.slots_cke_sel & PWR_DOWN_CNTL_EN_PD_ACT___M) << PWR_DOWN_CNTL_EN_PD_ACT___S;

        mddr_reg_vals.ddr_power_down_cntl_val = auto_power_cntl_val;

        // Set the controls for all active channels.
        for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
        {
            chan_populated = mddr_check_chan_populated(ddr_chan);

            if(chan_populated)
            {
                // Tell channel to enable auto power-down
                mddr_base_addr = mddr_base_addrs[ddr_chan];
                mddr_set_reg(mddr_base_addr + MDDR_DDR_PWR_DOWN_CNTL_OFFSET, "DDR_PWR_DOWN_CNTL", mddr_reg_vals.ddr_power_down_cntl_val);
            }
        }
}



/*!****************************************************************************
*
* @par Description:
*    This function disables auto power-down mode for the MDDR subsystem.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_auto_power_down_disable(void)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;
    uint32_t auto_power_cntl_val;

    auto_power_cntl_val = mddr_reg_vals.ddr_power_down_cntl_val;

    // Disable auto power-down, but leave the delay field untouched
    auto_power_cntl_val &= ~(PWR_DOWN_CNTL_EN_PD_ACT___M << PWR_DOWN_CNTL_EN_PD_ACT___S);

    mddr_reg_vals.ddr_power_down_cntl_val = auto_power_cntl_val;

    // Set the controls for all active channels.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Tell channel to disable auto power-down
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_set_reg(mddr_base_addr + MDDR_DDR_PWR_DOWN_CNTL_OFFSET, "DDR_PWR_DOWN_CNTL", mddr_reg_vals.ddr_power_down_cntl_val);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function enables auto self-refresh mode for the MDDR subsystem. This
*      allows the subsystem to conserve power based on the current usage pattern.
*
*                                  @param
*    idle_delay      The number of DDR clocks a channel should be idle before
*                     the MDDR susbsytem puts the meory into self-refresh.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    Thought the delay value is the same for all DDR channels, each channel
*     is independent. The implication is that the channels will enter and exit
*     self-refresh based on their own conditions and are unlikely to enter /
*     exit self-refresh at the same time.
*
******************************************************************************/
void mddr_auto_self_refresh_enable(uint32_t idle_delay)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;
    uint32_t self_ref_cntl_val;
    uint32_t en_sr_auto = 0xF;             // cke groups to enable self refresh on. Enable of all CKE, uses only valid CKEs


    self_ref_cntl_val = mddr_reg_vals.ddr_self_ref_cntl_val;

    // Clear out the old auto self-refresh fields
    self_ref_cntl_val &= ~(SELF_REF_CNTL_SR_ENTRY_IDLE_DELAY___M << SELF_REF_CNTL_SR_ENTRY_IDLE_DELAY___S);
    self_ref_cntl_val &= ~(SELF_REF_CNTL_EN_SR_AUTO___M << SELF_REF_CNTL_EN_SR_AUTO___S);

    self_ref_cntl_val |= (idle_delay & SELF_REF_CNTL_SR_ENTRY_IDLE_DELAY___M) << SELF_REF_CNTL_SR_ENTRY_IDLE_DELAY___S;
    self_ref_cntl_val |= (en_sr_auto & SELF_REF_CNTL_EN_SR_AUTO___M) << SELF_REF_CNTL_EN_SR_AUTO___S;

    mddr_reg_vals.ddr_self_ref_cntl_val = self_ref_cntl_val;


    // Set the controls for all active channels.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Tell channel to enable auto self-refresh
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_set_reg(mddr_base_addr + MDDR_DDR_SELF_REF_CNTL_OFFSET, "DDR_SELF_REF_CNTL", mddr_reg_vals.ddr_self_ref_cntl_val);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function disables auto self-refresh mode for the MDDR subsystem.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_auto_self_refresh_disable(void)
{
    uint8_t ddr_chan;
    bool chan_populated;
    uint64_t mddr_base_addr;
    uint32_t self_ref_cntl_val;


    self_ref_cntl_val = mddr_reg_vals.ddr_self_ref_cntl_val;

    // Disable auto self-refresh, but leave the delay field untouched
    self_ref_cntl_val &= ~(SELF_REF_CNTL_EN_SR_AUTO___M << SELF_REF_CNTL_EN_SR_AUTO___S);

    mddr_reg_vals.ddr_self_ref_cntl_val = self_ref_cntl_val;


    // Set the controls for all active channels.
    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Tell channel to disable auto self-refresh
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_set_reg(mddr_base_addr + MDDR_DDR_SELF_REF_CNTL_OFFSET, "DDR_SELF_REF_CNTL", mddr_reg_vals.ddr_self_ref_cntl_val);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function enables manual self-refresh mode for the MDDR subsystem.
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_enter_self_refresh(void)
{
    uint8_t ddr_chan;
    uint64_t mddr_base_addr;
    bool chan_populated;
    uint8_t cke_sel;
    uint32_t manual_cke_val;
    uint32_t dev_state_mask;
    uint32_t exp_dev_state_val;


    cke_sel = common_cfg.slots_cke_sel;

    // Enter self-refresh.
    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;
    manual_cke_val |= 0x1 << MANUAL_CKE_ENTER_SELF_REF_ASAP___S;

    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Tell channel to enter self-refresh
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);

            // Wait for entry into self-refresh.
            dev_state_mask = DEVICE_STATE_CKE_IN_SELF_REF___M << DEVICE_STATE_CKE_IN_SELF_REF___S;
            exp_dev_state_val = cke_sel << DEVICE_STATE_CKE_IN_SELF_REF___S;
            mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, dev_state_mask, exp_dev_state_val, 30);
        }
    }
}



/*!****************************************************************************
*
* @par Description:
*    This function disables manual self-refresh mode for the MDDR subsystem.
*
* @return
*    None
*
* @author
*    gkowis
*
* @par Notes:
*    Even when self-refresh mode is exited, the DIMMs may still be in
*     self-refresh if automatic self-refresh mode is enabled. If it is
*     necessary to force the DIMMs out of self-refresh, auto self-refresh must
*     also be disabled using mddr_auto_self_refresh_disable() before invoking
*     this function.
*
******************************************************************************/
void mddr_exit_self_refresh(void)
{
    uint8_t ddr_chan;
    uint64_t mddr_base_addr;
    bool chan_populated;
    uint8_t cke_sel;
    uint32_t manual_cke_val;
    uint32_t dev_state_mask;
    uint32_t exp_dev_state_val;


    cke_sel = common_cfg.slots_cke_sel;

    // Exit self-refresh.
    manual_cke_val = (cke_sel & MANUAL_CKE_CKE_SEL___M) << MANUAL_CKE_CKE_SEL___S;
    manual_cke_val |= 0x1 << MANUAL_CKE_EXIT_SELF_REF___S;

    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            // Tell channel to exit self-refresh
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_set_reg(mddr_base_addr + MDDR_DDR_MANUAL_CKE_OFFSET, "DDR_MANUAL_CKE", manual_cke_val);

            // Wait for exit from self-refresh.
            dev_state_mask = DEVICE_STATE_CKE_IN_SELF_REF___M << DEVICE_STATE_CKE_IN_SELF_REF___S;
            exp_dev_state_val = 0x0 << DEVICE_STATE_CKE_IN_SELF_REF___S;
            mddr_rd_chk_reg(mddr_base_addr, MDDR_DDR_DEVICE_STATE_OFFSET, dev_state_mask, exp_dev_state_val, 30);
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function adjusts the values for the Periodic Auto Refresh DIMM Refresh
*     Rate Adjustment setting.
*
*                                  @param
*    adj_ref_dimm0  Refresh rate adjustment for DIMM 0.
*    adj_ref_dimm1  Refresh rate adjustment for DIMM 1.
*
* @return
*    None
*
* @author
*    anthonyf
*
* @par Notes:
*    These settings can be changed dynamically. Based on the setting, the
*     controller changes the actual refresh rate.
*
******************************************************************************/
void mddr_periodic_auto_refresh_adj
(
    mddr_dimm_refresh_rate_t adj_ref_dimm0,
    mddr_dimm_refresh_rate_t adj_ref_dimm1
)
{
    uint8_t ddr_chan;
    uint64_t mddr_base_addr;
    bool chan_populated;
    uint32_t reg_value;

    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            monaco_log(MEDIUM, "Auto Refresh Rate Adjust requested on chan %u. DIMM0: %u and DIMM1: %u\n",
                       hddrss[ddr_chan],
                       adj_ref_dimm0,
                       adj_ref_dimm1);

            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_mc_wait_us(mddr_base_addr, 1);

            // Get the current value of the register
            reg_value = read32(mddr_base_addr + MDDR_DDR_AUTO_REF_CNTL_OFFSET);
            monaco_log(LOW, "    Auto Refresh Control reg val : chan %u  Got 0x%8.8x\n", hddrss[ddr_chan], reg_value);

            if((adj_ref_dimm0 == DIMM_REFRESH_RATE_ONE_QUARTER ) ||
               (adj_ref_dimm0 == DIMM_REFRESH_RATE_ONE_HALF ) ||
               (adj_ref_dimm0 == DIMM_REFRESH_RATE_1x ) ||
               (adj_ref_dimm0 == DIMM_REFRESH_RATE_2x ) ||
               (adj_ref_dimm0 == DIMM_REFRESH_RATE_4x ))
            {
                reg_value &= ~(AUTO_REF_CNTL_ADJ_DIMM0___M << AUTO_REF_CNTL_ADJ_DIMM0___S);
                reg_value |= (adj_ref_dimm0 & AUTO_REF_CNTL_ADJ_DIMM0___M) << AUTO_REF_CNTL_ADJ_DIMM0___S;
            }
            else
            {
                monaco_log(HIGH, "    WARNING: Invalid rate adj = %u requested on chan %u DIMM0, ignoring request.\n",
                           adj_ref_dimm0,
                           hddrss[ddr_chan]);
            }

            if((adj_ref_dimm1 == DIMM_REFRESH_RATE_ONE_QUARTER ) ||
               (adj_ref_dimm1 == DIMM_REFRESH_RATE_ONE_HALF ) ||
               (adj_ref_dimm1 == DIMM_REFRESH_RATE_1x ) ||
               (adj_ref_dimm1 == DIMM_REFRESH_RATE_2x ) ||
               (adj_ref_dimm1 == DIMM_REFRESH_RATE_4x ))
            {
                reg_value &= ~(AUTO_REF_CNTL_ADJ_DIMM1___M << AUTO_REF_CNTL_ADJ_DIMM1___S);
                reg_value |= (adj_ref_dimm1 & AUTO_REF_CNTL_ADJ_DIMM1___M) << AUTO_REF_CNTL_ADJ_DIMM1___S;
            }
            else
            {
                monaco_log(HIGH, "    WARNING: Invalid rate adj = %u requested on chan %u DIMM1, ignoring request.\n",
                           adj_ref_dimm1,
                           hddrss[ddr_chan]);
            }

            mddr_set_reg(mddr_base_addr + MDDR_DDR_AUTO_REF_CNTL_OFFSET, "DDR_AUTO_REF_CNTL", reg_value);
        }
    }
}


/*!****************************************************************************
*
* @par Description:
*    This function retrieves the set of configured DDR operating frequencies
*    mapping between the logical IDs / names and the actual frequencies in MHz.
*
*                                  @param
*    freq_map       Array filled in with the frequencies. Indexed by the
*                    frequency ID / name.
*
*
* @return
*    Count of the number of configured operating frequencies.
*
* @author
*    gkowis
*
* @par Notes:
*    Entries for unused IDs/names will contain the marker value
*     DDR_FREQ_INVALID.
*
******************************************************************************/
uint8_t mddr_get_freq_map(uint32_t freq_map[])
{
    uint8_t num_freqs = 0;
    uint8_t target_freq = DDR_FREQ_1;


    // Fill in the map array with the configured / provisioned frequencies by mddr_freq_ind_t
    for(target_freq = DDR_FREQ_1;  target_freq < DDR_FREQ_ID_MAX; ++target_freq)
    {
        if(target_freq < DDR_MAX_FREQ_POOL_TARGET)
        {
            freq_map[target_freq] =  mddr_settings.mem_freq_mhz[target_freq];

            if(freq_map[target_freq] != DDR_FREQ_INVALID)
            {
                ++num_freqs;
            }
        }
        else
        {
            freq_map[target_freq] = DDR_FREQ_INVALID;
        }
    }


    return num_freqs;
}



/*!****************************************************************************
*
* @par Description:
*    This function reports the contents of the device state register for all
*     active channels. This allows for debug checks of mode ... settings such
*     as behavior of self-refresh, auto self-refresh and auto power-down.
*
*
* @return
*    None
*
* @author
*    gkowis
*
******************************************************************************/
void mddr_dump_device_state_regs(void)
{
    uint8_t ddr_chan;
    uint64_t mddr_base_addr;
    bool chan_populated;
    uint32_t reg_value;


    for(ddr_chan = 0; ddr_chan < DDR_MAX_NUM_CHANS; ++ddr_chan)
    {
        chan_populated = mddr_check_chan_populated(ddr_chan);

        if(chan_populated)
        {
            mddr_base_addr = mddr_base_addrs[ddr_chan];
            mddr_mc_wait_us(mddr_base_addr, 1);

            reg_value = read32(mddr_base_addr + MDDR_DDR_DEVICE_STATE_OFFSET);
            monaco_log(LOW, "    Device state reg val : chan %u  Got 0x%8.8x\n", hddrss[ddr_chan], reg_value);
        }
    }
}


/******************************************************************************
* Local Functions
******************************************************************************/



