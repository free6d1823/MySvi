#ifndef _MODULE_MDDR_POWER_H_
#define _MODULE_MDDR_POWER_H_

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
* @file mddr_power.h
*
* @par Description:
*    This header provides the specialized datatypes and function prototypes
*     to necessary access the controls for the power realted feature of the
*     MDDR subsystem. This includes such things as self-refresh controls and
*     thermal throttling controls.
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <stdbool.h>



/******************************************************************************
* Defined Constants
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    Special DDR frequency value used to indicate an invalid / unused frequency.
*
******************************************************************************/
#define DDR_FREQ_INVALID                          0


/*!****************************************************************************
*
* @par Description
*    Self-refresh idle time. This is the delay in number of DDR cycles from the
*     time that the controller is idle to the time that the controller puts the
*     DRAM into self-refresh mode.
*
******************************************************************************/
#define SR_ENTRY_IDLE_DELAY_MIN 0x0000  //!< Minimum self-refresh idle time supported by the driver.
#define SR_ENTRY_IDLE_DELAY_MAX 0xFFFF  //!< Maximum self-refresh idle time supported by the driver.


/*!****************************************************************************
*
* @par Description
*    Power-down idle time. This is the delay in number of DDR cycles from the
*     time that the controller is idle to the time that the controller puts the
*     DRAM into power down mode.
*
******************************************************************************/
#define PD_ENTRY_IDLE_DELAY_MIN 0x0000  //!< Minimum power-down idle time supported by the driver.
#define PD_ENTRY_IDLE_DELAY_MAX 0xFFFF  //!< Maximum power-down idle time supported by the driver.


/*!****************************************************************************
*
* @par Description
*    DDR PHY DFI Low Power Mode configuration
*
******************************************************************************/
#define DFI_CTRLUPD_PERIOD                0x1E      //!< Interval, in sleep clock cycles, that the controller issues periodic DFI controller update requests. (30 sleep clocks = 1mS)
#define DFI_LP2_ENTRY_IDLE_DELAY_MIN      0x0       //!< Minimum DFI-LP2 entry idle delay value supported by the driver.
#define DFI_LP2_ENTRY_IDLE_DELAY_MAX      0xFFFF    //!< Maximum DFI-LP2 entry idle delay value supported by the driver.


/*!****************************************************************************
*
* @defgroup therm_throttle_emu_defaults Default Emulation Thermal Throttling Settings
*
* @par Description
*    This set of constants provides the default settings for thermal throttling
*     on an emulation platform.
*
* @{
******************************************************************************/
#define THERM_WEIGHT_READ_BL8_EMU                 0xC
#define THERM_WEIGHT_READ_BC4_EMU                 0xA
#define THERM_WEIGHT_WRITE_BL8_EMU                0xF
#define THERM_WEIGHT_WRITE_BC4_EMU                0xD
#define THERM_WEIGHT_PCHG_EMU                     0x8
#define THERM_WEIGHT_ACT_EMU                      0x7
#define THERM_THROTTLE_HIGH_WM_EMU                0x0037A3FA        // must be > low_wm
#define THERM_THROTTLE_LOW_WM_EMU                 0x002C832E        // must be < high_wm
#define THERM_LEAK_AMOUNT_EMU                     0x00009E44
#define THERM_LEAK_INTERVAL_EMU                   0x0001D4F0
/* @} */



/*!****************************************************************************
*
* @defgroup therm_throttle_sil_defaults Default Silicon Thermal Throttling Settings
*
* @par Description
*    This set of constants provides the default settings for thermal throttling
*     on a silicon platform.
*
* @par Notes:
*    Ivalues from HPG section 3, DDR Command Thermal Throttling
*
* @{
******************************************************************************/
#define THERM_WEIGHT_READ_BL8_SIL                 0xC
#define THERM_WEIGHT_READ_BC4_SIL                 0x9
#define THERM_WEIGHT_WRITE_BL8_SIL                0x4
#define THERM_WEIGHT_WRITE_BC4_SIL                0x4
#define THERM_WEIGHT_PCHG_SIL                     0x0
#define THERM_WEIGHT_ACT_SIL                      0xF
#define THERM_THROTTLE_HIGH_WM_SIL                0x007B98A7      // must be > low_wm
#define THERM_THROTTLE_LOW_WM_SIL                 0x007B98A0      // must be < high_wm
#define THERM_LEAK_AMOUNT_SIL                     0x00000044
#define THERM_LEAK_INTERVAL_SIL                   0x0000000A
/* @} */



/******************************************************************************
* Derived data types
******************************************************************************/

/*!****************************************************************************
*
* @par Description
*    This type provides the recognizable names for target frequencies to use
*     for DDR dynamic frequenct switch.
*
* @par Notes:
*    Generic names are used because the actual operating frequencies are
*     determined at boot time.
*
* @par Members
*
*                                  <PRE>
*    DDR_FREQ_1         First of the target DDR operating frequencies.
*    DDR_FREQ_2         Second of the target DDR operating frequencies.
*    DDR_FREQ_3         Thrid of the target DDR operating frequencies.
*    DDR_FREQ_4         Fourth of the target DDR operating frequencies.
*    DDR_FREQ_5         Fifth of the target DDR operating frequencies.
*    DDR_FREQ_6         Sixth of the target DDR operating frequencies.
*    DDR_FREQ_7         Seventh of the target DDR operating frequencies.
*    DDR_FREQ_8         Eighth of the target DDR operating frequencies.
*    DDR_FREQ_9         Ninth of the target DDR operating frequencies.
*    DDR_FREQ_ID_MAX    Max number of identified/named target frequencies.
*                                  </PRE>
*
******************************************************************************/
typedef enum
{
    DDR_FREQ_1,
    DDR_FREQ_2,
    DDR_FREQ_3,
    DDR_FREQ_4,
    DDR_FREQ_5,
    DDR_FREQ_6,
    DDR_FREQ_7,
    DDR_FREQ_8,
    DDR_FREQ_9,
    DDR_FREQ_ID_MAX
}mddr_freq_ind_t;



/*!****************************************************************************
*
* @par Description
*    This type defines the DIMM refresh rate adjustment values.
*
* @par Notes
*    The rate to issue auto-refresh can be adjusted on the fly while the memory
*     traffic is running. The adjustment might be necessary when the DRAM device
*     temperature is high. The adjustment can be done on each DIMM individually.
*
* @par Members
*                                  <PRE>
*    DIMM_REFRESH_RATE_ONE_QUARTER
*    DIMM_REFRESH_RATE_ONE_HALF
*    DIMM_REFRESH_RATE_1x
*    DIMM_REFRESH_RATE_2x
*    DIMM_REFRESH_RATE_4x
*                                  </PRE>
*
******************************************************************************/
typedef enum
{
    DIMM_REFRESH_RATE_ONE_QUARTER   = 6,
    DIMM_REFRESH_RATE_ONE_HALF      = 7,
    DIMM_REFRESH_RATE_1x            = 0,
    DIMM_REFRESH_RATE_2x            = 1,
    DIMM_REFRESH_RATE_4x            = 2
} mddr_dimm_refresh_rate_t;


/*!****************************************************************************
*
* @par Description
*    This type defines the PHY DFI low power modes.
*
******************************************************************************/
typedef enum
{
    DFI_LP_DISABLED,            //!< Selects disable DFI-LP and DFI-LP2 states,
    DFI_LP_SR_ENA,              //!< Selects enable PHY DFI-LP when the DRAM is in self-refresh state.
    DFI_LP_SR_PD_ENA,           //!< Selects enable DFI-LP when the DRAM is in self-refresh or power-down states.
    DFI_LP_SR_ENA_LP2_ENA,      //!< Selects enable DFI-LP and DFI-LP2 when the DRAM is in self-refresh state.
    DFI_LP_SR_PD_ENA_LP2_ENA,   //!< Selects enable DFI-LP when the DRAM is in self-refresh or power-down states and enable DFI-LP2 when the DRAM is in self-refresh state.
    DFI_LP_NUM_TYPES            //!< Number of PHY DFI low power mode configuration options.
} mddr_dfi_lpm_t;


/*!****************************************************************************
*
* @par Description
*    This type provides the amount leaked from the leaky bucket and the frequency of
*    the leak. These parameters are used to control thermal throttling.
*
* @par Members
*
*                                  <PRE>
*    sum_deplete_val        Amount of weight sum to deplete over a time interval, 24-bit.
*                            Experimental suggestion: 0x9E44
*    sum_deplete_interval   Number of cycles to wait before depleting sum_deplete_val
*                            from the weighted sum, until the weighted sum is 0, 24-bit.
*                            Experimental suggestion: 0x1D4F0
*                                  </PRE>
******************************************************************************/
typedef struct
{
    uint32_t    sum_deplete_val;
    uint32_t    sum_deplete_interval;
}mddr_therm_throttle_adj_t;



/*!****************************************************************************
*
* @par Description
*    This type provides / exposes the raw thermal throttling controls to be
*    used for driver internal function and algorithmic experimentation.
*
* @par Notes
*    This type is intended for internal use and to allow expose the raw thermal
*     throttling controls for experimental algorithmic development
*     using mddr_therm_throttle_exp_adj() and is not expected to be used for
*     production level interfacing.
*
* @par Members
*
*                                  <PRE>
*    read_bl8_weight        Thermal Weight of a DDR burst length 8 read command, 4-bit.
*                             Experimental suggestion: 0x7
*    read_bc4_weight        Thermal weight of a Burst Chop 4 read command, 4-bit.
*                             Experimental suggestion: 0x6
*    write_bl8_weight       Thermal weight of a Burst Length 8 write command, 4-bit.
*                             Experimental suggestion: 0x8
*    write_bc4_weight       Thermal weight of a Burst Chop 4 write command, 4-bit.
*                             Experimental suggestion: 0x7
*    pchg_weight            Thermal Weight of a Precharge Command, 4-bit.
*                             Experimental suggestion: 0x3
*    act_weight             Thermal Weight of an Activate command, 4-bit.
*                             Experimental suggestion: 0x3
*    throttle_high_wm       Value of weighted sum at which point to start
*                             throttling commands, 24-bit.
*                             Experimental suggestion: 0x37A3FA
*    throttle_low_wm        Value of weighted sum that once throttling
*                             commands and depleted below, commands can resume, 24-bit.
*                             Experimental suggestion: 0x2C832E
*    sum_deplete_val        Amount of weight sum to deplete over a time interval, 24-bit.
*                             Experimental suggestion: 0x9E44
*    sum_deplete_interval   Number of cycles to wait before depleting sum_deplete_val
*                            from the weighted sum, until the weighted sum is 0, 24-bit.
*                            Experimental suggestion: 0x1D4F0
*                                  </PRE>
******************************************************************************/
typedef struct
{
    uint8_t     read_bl8_weight;
    uint8_t     read_bc4_weight;
    uint8_t     write_bl8_weight;
    uint8_t     write_bc4_weight;
    uint8_t     pchg_weight;
    uint8_t     act_weight;
    uint32_t    throttle_high_wm;
    uint32_t    throttle_low_wm;
    uint32_t    sum_deplete_val;
    uint32_t    sum_deplete_interval;
}mddr_therm_throttle_settings_t;



/*!****************************************************************************
*
* @par Description
*    This type provides the thermal limits used to control thermal event_n
*     generation.
*
* @par Members
*                                  <PRE>
*    tcrit_limit        Critical temperature. If the DIMM temperature reaches
*                        this level the event_n signal will assert and remain
*                        asserted until the temperature falls below this level.
*    high_limit         Temperature High Limit. If the DIMM temperature reaches
*                        this limit the event_n signal will assert but can be
*                        cleared to acknowledge the event.
*    low_limit          Temperature Low Limit. If the DIMM temperature reaches
*                        this limit the event_n signal will assert but can be
*                        cleared to acknowledge the event.
*                                  </PRE>
******************************************************************************/
typedef struct
{
    uint16_t    tcrit_limit;
    uint16_t    high_limit;
    uint16_t    low_limit;
}mddr_therm_event_adj_t;



/*!****************************************************************************
*
* @par Description
*    This type provides the recognizable names for the amount of thermal event
*      hysteresis to apply when recovering from crossing an event limit.
*
* @par Members
*                                  <PRE>
*    THERM_HYST_NONE    Don't use any hysteresis when crossing thermal event
*                        thresholds.
*    THERM_HYST_1_5     Use a 1.5 degree C hysteresis when crossing thermal
*                        event thresholds.
*    THERM_HYST_3       Use a 3 degree C hysteresis when crossing thermal
*                        event thresholds.
*    THERM_HYST_6       Use a 6 degree C hysteresis when crossing thermal
*                        event thresholds.
*                                  </PRE>
*
******************************************************************************/
typedef enum
{
    THERM_HYST_NONE,
    THERM_HYST_1_5,
    THERM_HYST_3,
    THERM_HYST_6
}mddr_therm_event_hyst_t;



/*!****************************************************************************
*
* @par Description
*    This type provides the boot time configuration information for the thermal
*     event_n settings for populated DIMMs.
*
* @par Notes
*    In interrupt mode an event_n is cleared by acknowledging the event using
*     mddr_therm_event_clear(). High and low limit crossings can be
*     acknowledged with the event condition still existing and another event
*     will be generated on recovery. A critical temperature event can only be
*     cleared once the condition no longer exists. In comparator mode event_n
*     will remain asserted as long as the condition exists and will be
*     deasserted automatically once the condition no longer exists.
*
* @par Members
*                                  <PRE>
*    active_high        Flag indicating if the event_n is to be active high
*                        instead of active low.
*    interrupt_mode     Flag indicating if interrupt mode is to be used instead
*                        of comparator mode.
*    crit_only          Flag used to indicate when event_n should only be
*                        asserted when crossing the critical threshold.
*                        High and low limits are ignored.
*    hysteresis         Indicator for the amount of hysteresis to use when
*                        recovering from crossing an event limit.
*                                  </PRE>
*
******************************************************************************/
typedef struct
{
    bool                    active_high;
    bool                    interrupt_mode;
    bool                    crit_only;
    mddr_therm_event_hyst_t hysteresis;
}mddr_therm_event_settings_t;


/******************************************************************************
* Global Variables
******************************************************************************/


/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/
void mddr_therm_throttle_adj(mddr_therm_throttle_adj_t *throttle_adj_ptr);
void mddr_therm_throttle_enable(void);
void mddr_therm_throttle_disable(void);

void mddr_auto_power_down_enable(uint32_t idle_delay);
void mddr_auto_power_down_disable(void);
void mddr_auto_self_refresh_enable(uint32_t idle_delay);
void mddr_auto_self_refresh_disable(void);
void mddr_enter_self_refresh(void);
void mddr_exit_self_refresh(void);
void mddr_periodic_auto_refresh_adj(mddr_dimm_refresh_rate_t adj_ref_dimm0, mddr_dimm_refresh_rate_t adj_ref_dimm1);

uint8_t mddr_get_freq_map(uint32_t freq_map[]);
void mddr_dump_device_state_regs(void);

// The thermal event support (event_n) is skeleton only place holders. Functionality will
//  added if / when there is a need post SOD.
void mddr_therm_event_init(mddr_therm_event_settings_t *event_settings_ptr);
void mddr_therm_event_adj(mddr_therm_event_adj_t *event_adj_ptr);
void mddr_therm_event_enable(void);
void mddr_therm_event_disable(void);
void mddr_therm_event_lock(void);
void mddr_therm_event_check(void);
void mddr_therm_event_clear(void);

/*****************************************************************************/
#endif
