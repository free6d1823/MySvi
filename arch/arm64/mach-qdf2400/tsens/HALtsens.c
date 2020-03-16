/*============================================================================
  FILE:         HALTsens.c

  OVERVIEW:     Implementation of the TSENS HAL

  DEPENDENCIES: None

                Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/
/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.

  $Header$$DateTime$$Author$

  when        who  what, where, why
  ----------  ---  -----------------------------------------------------------
  2015-07-09  jjo  Add thermal combinder support.
  2014-07-21  jjo  Initial revision.

============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
//#include "HALhwio.h"
#include <stdint.h>
#include <stdbool.h>
#include <asm/mach-qdf2400/hal/HALhwioTsens.h>
#include <asm/mach-qdf2400/hal/HALtsens.h>

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Get temperature measurement - TM
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_tm_GetChannelPrevTemp
**
**  Description:
**    Gets the previous TSENS temperature in deci deg C.
**
**  Parameters:
**    pucTsensTMAddr - address of controller's TM region
**    uChannel - which of the channels
**    pnDeciDegC - TSENS temperature in deci deg C
**
**  Return: true if reading is valid, else false
**
**  Dependencies: adc result must be generated already
**
** ========================================================================= */
bool HAL_tsens_tm_GetChannelPrevTemp(uint8_t *pucTsensTMAddr, uint32_t uChannel, int32_t *pnDeciDegC)
{
   uint32_t uTsensSnStatus;
   uint32_t uValidBit;
   int32_t nDeciDegC;

   uTsensSnStatus = HWIO_INXI(pucTsensTMAddr, TSENS_Sn_STATUS, uChannel);

   nDeciDegC = (int32_t)((uTsensSnStatus & HWIO_FMSK(TSENS_Sn_STATUS, LAST_TEMP)) >> HWIO_SHFT(TSENS_Sn_STATUS, LAST_TEMP));

   uValidBit = (uTsensSnStatus & HWIO_FMSK(TSENS_Sn_STATUS, VALID)) >> HWIO_SHFT(TSENS_Sn_STATUS, VALID);

   /* Temperature is a 12-bit number -- sign extend to 32 bits */
   if (nDeciDegC & 0x800)
   {
      nDeciDegC |= 0xFFFFF000;
   }

   *pnDeciDegC = nDeciDegC;

   if (uValidBit == 1)
   {
      return true;
   }
   else
   {
      return false;
   }
}

/* ============================================================================
**
**  HAL_tsens_tm_GetMaxTemp
**
**  Description:
**    Gets the maximum TSENS temperature for the last measurement period
**    in deci deg C.
**
**  Parameters:
**    pucTsensTMAddr - address of controller's TM region
**    puSensorID - sensor ID of the channel with the maximum temperature
**    pnMaxDeciDegC - max TSENS temperature in deci deg C
**
**  Return: None
**
**  Dependencies: adc result must be generated already
**
** ========================================================================= */
void HAL_tsens_tm_GetMaxTemp(uint8_t *pucTsensTMAddr, uint32_t *puSensorID, int32_t *pnMaxDeciDegC)
{
   uint32_t uReg;
   int32_t nDeciDegC;

   uReg = HWIO_INX(pucTsensTMAddr, TSENS_MAX_TEMP);

   nDeciDegC = (int32_t)((uReg & HWIO_FMSK(TSENS_MAX_TEMP, MAX_TEMP)) >> HWIO_SHFT(TSENS_MAX_TEMP, MAX_TEMP));

   *puSensorID = (uReg & HWIO_FMSK(TSENS_MAX_TEMP, MAX_TEMP_SENSOR_ID)) >> HWIO_SHFT(TSENS_MAX_TEMP, MAX_TEMP_SENSOR_ID);

   /* Temperature is a 12-bit number -- sign extend to 32 bits */
   if (nDeciDegC & 0x800)
   {
      nDeciDegC |= 0xFFFFF000;
   }

   *pnMaxDeciDegC = nDeciDegC;

   return;
}

/*----------------------------------------------------------------------------
 * Interrupts - TM
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_tm_EnableUpperLowerInterrupt
**
**  Description:
**    Main enable for upper / lower thresholds
**
**  Parameters:
**    pucTsensTMAddr - address of controller's TM region
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_tm_EnableUpperLowerInterrupt(uint8_t *pucTsensTMAddr)
{
   uint32_t uReg;

   uReg = HWIO_INX(pucTsensTMAddr, TSENS_TM_INT_EN);

   uReg &= ~HWIO_FMSK(TSENS_TM_INT_EN, LOWER_INT_EN);
   uReg &= ~HWIO_FMSK(TSENS_TM_INT_EN, UPPER_INT_EN);

   uReg |= HWIO_FVALV(TSENS_TM_INT_EN, LOWER_INT_EN, ENABLED);
   uReg |= HWIO_FVALV(TSENS_TM_INT_EN, UPPER_INT_EN, ENABLED);

   HWIO_OUTX(pucTsensTMAddr, TSENS_TM_INT_EN, uReg);
}

/* ============================================================================
**
**  HAL_tsens_tm_DisableUpperLowerInterrupt
**
**  Description:
**    Main disable for upper / lower thresholds
**
**  Parameters:
**    pucTsensTMAddr - address of controller's TM region
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_tm_DisableUpperLowerInterrupt(uint8_t *pucTsensTMAddr)
{
   uint32_t uReg;

   uReg = HWIO_INX(pucTsensTMAddr, TSENS_TM_INT_EN);

   uReg &= ~HWIO_FMSK(TSENS_TM_INT_EN, LOWER_INT_EN);
   uReg &= ~HWIO_FMSK(TSENS_TM_INT_EN, UPPER_INT_EN);

   uReg |= HWIO_FVALV(TSENS_TM_INT_EN, LOWER_INT_EN, DISABLED);
   uReg |= HWIO_FVALV(TSENS_TM_INT_EN, UPPER_INT_EN, DISABLED);

   HWIO_OUTX(pucTsensTMAddr, TSENS_TM_INT_EN, uReg);
}

/* ============================================================================
**
**  HAL_tsens_tm_EnableCriticalInterrupt
**
**  Description:
**    Main enable for critical thresholds
**
**  Parameters:
**    pucTsensTMAddr - address of controller's TM region
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_tm_EnableCriticalInterrupt(uint8_t *pucTsensTMAddr)
{
   HWIO_OUTXV(pucTsensTMAddr, TSENS_TM_INT_EN, CRITICAL_INT_EN, ENABLED);
}

/* ============================================================================
**
**  HAL_tsens_tm_DisableCriticalInterrupt
**
**  Description:
**    Main disable for critical thresholds
**
**  Parameters:
**    pucTsensTMAddr - address of controller's TM region
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_tm_DisableCriticalInterrupt(uint8_t *pucTsensTMAddr)
{
   HWIO_OUTXV(pucTsensTMAddr, TSENS_TM_INT_EN, CRITICAL_INT_EN, DISABLED);
}

/* ============================================================================
**
**  HAL_tsens_tm_SetInterruptEn
**
**  Description:
**    Sets an interrupt enabled / disabled corresponding to the channel mask
**
**  Parameters:
**    pucTsensTMAddr - address of controller's TM region
**    uChannelEnMask - channel enable mask
**    eThreshold - which threshold
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_tm_SetInterruptEn(uint8_t *pucTsensTMAddr, uint32_t uChannelEnMask, HAL_tsens_tm_Threshold eThreshold)
{
   switch (eThreshold)
   {
      case HAL_TSENS_TH_LOWER:
         HWIO_OUTXF(pucTsensTMAddr, TSENS_UPPER_LOWER_INT_MASK, LOWER_INT_MASK, ~uChannelEnMask);
         break;
      case HAL_TSENS_TH_UPPER:
         HWIO_OUTXF(pucTsensTMAddr, TSENS_UPPER_LOWER_INT_MASK, UPPER_INT_MASK, ~uChannelEnMask);
         break;
      case HAL_TSENS_TH_CRITICAL:
         HWIO_OUTXF(pucTsensTMAddr, TSENS_CRITICAL_INT_MASK, CRITICAL_INT_MASK, ~uChannelEnMask);
         break;
      default:
         break;
   }
}

/*----------------------------------------------------------------------------
 * Interrupts - SROT
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_srot_EnableInterrupt
**
**  Description:
**    Enable a threshold for a particular channel
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uChannel - which channel
**    eThreshold - which threshold
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_EnableInterrupt(uint8_t *pucTsensSROTAddr, uint32_t uChannel, HAL_tsens_srot_Threshold eThreshold)
{
   switch (eThreshold)
   {
      case HAL_TSENS_TH_MIN:
         HWIO_OUTXVI(pucTsensSROTAddr, TSENS_Sn_MAX_MIN_STATUS_CTRL, uChannel, MIN_STATUS_MASK, NORMAL_OPERATION);
         break;
      case HAL_TSENS_TH_MAX:
         HWIO_OUTXVI(pucTsensSROTAddr, TSENS_Sn_MAX_MIN_STATUS_CTRL, uChannel, MAX_STATUS_MASK, NORMAL_OPERATION);
         break;
      default:
         break;
   }
}

/* ============================================================================
**
**  HAL_tsens_srot_DisableInterrupt
**
**  Description:
**    Disable a threshold for a particular channel
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uChannel - which channel
**    eThreshold - which threshold
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_DisableInterrupt(uint8_t *pucTsensSROTAddr, uint32_t uChannel, HAL_tsens_srot_Threshold eThreshold)
{
   switch (eThreshold)
   {
      case HAL_TSENS_TH_MIN:
         HWIO_OUTXVI(pucTsensSROTAddr, TSENS_Sn_MAX_MIN_STATUS_CTRL, uChannel, MIN_STATUS_MASK, MASK_OFF_MIN_STATUS);
         break;
      case HAL_TSENS_TH_MAX:
         HWIO_OUTXVI(pucTsensSROTAddr, TSENS_Sn_MAX_MIN_STATUS_CTRL, uChannel, MAX_STATUS_MASK, MASK_OFF_MAX_STATUS);
         break;
      default:
         break;
   }
}

/*----------------------------------------------------------------------------
 * Thresholds
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_GetMaxTemp
**
**  Description:
**    Gets the maximum temperature in deci deg C
**
**  Parameters:
**    None
**
**  Return: Maximum temperature in deci deg C
**
**  Dependencies: None
**
** ========================================================================= */
int32_t HAL_tsens_GetMaxTemp(void)
{
   return 0x7FF;
}

/* ============================================================================
**
**  HAL_tsens_GetMinTemp
**
**  Description:
**    Gets the minimum temperature in deci deg C
**
**  Parameters:
**    None
**
**  Return: Minimum temperature in deci deg C
**
**  Dependencies: None
**
** ========================================================================= */
int32_t HAL_tsens_GetMinTemp(void)
{
   return 0xFFFFF800;
}

/*----------------------------------------------------------------------------
 * Thresholds - TM
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_tm_SetThreshold
**
**  Description:
**    Sets a given threshold
**
**  Parameters:
**    pucTsensTMAddr - address of controller's TM region
**    uChannel - which channel
**    eThreshold - which threshold
**    nThreshold - threshold in deci deg C
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_tm_SetThreshold(uint8_t *pucTsensTMAddr, uint32_t uChannel, HAL_tsens_tm_Threshold eThreshold, int32_t nThreshold)
{
   switch (eThreshold)
   {
      case HAL_TSENS_TH_LOWER:
         HWIO_OUTXFI(pucTsensTMAddr, TSENS_Sn_UPPER_LOWER_THRESHOLD, uChannel, LOWER_THRESHOLD, nThreshold);
         break;
      case HAL_TSENS_TH_UPPER:
         HWIO_OUTXFI(pucTsensTMAddr, TSENS_Sn_UPPER_LOWER_THRESHOLD, uChannel, UPPER_THRESHOLD, nThreshold);
         break;
      case HAL_TSENS_TH_CRITICAL:
         HWIO_OUTXFI(pucTsensTMAddr, TSENS_Sn_CRITICAL_THRESHOLD, uChannel, CRITICAL_THRESHOLD, nThreshold);
         break;
      default:
         break;
   }
}

/*----------------------------------------------------------------------------
 * Thresholds - SROT
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_srot_SetThreshold
**
**  Description:
**    Sets a given threshold
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uChannel - which channel
**    eThreshold - which threshold
**    nThreshold - threshold in deci deg C
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetThreshold(uint8_t *pucTsensSROTAddr, uint32_t uChannel, HAL_tsens_srot_Threshold eThreshold, int32_t nThreshold)
{
   switch (eThreshold)
   {
      case HAL_TSENS_TH_MIN:
         HWIO_OUTXFI(pucTsensSROTAddr, TSENS_Sn_MAX_MIN_STATUS_CTRL, uChannel, MIN_THRESHOLD, nThreshold);
         break;
      case HAL_TSENS_TH_MAX:
         HWIO_OUTXFI(pucTsensSROTAddr, TSENS_Sn_MAX_MIN_STATUS_CTRL, uChannel, MAX_THRESHOLD, nThreshold);
         break;
      default:
         break;
   }
}

/*----------------------------------------------------------------------------
 * Measurement period
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_srot_SetPeriodActive
**
**  Description:
**    Sets the period for the active case
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uTime
**     - 0x00 measures continiously
**     - 0x01-0xFE defines the length of sleep between two measurements
**                 approx equal to (upper 2bits) * 250ms + (lower 6bits) * 1.95ms
**     - 0xFF measures once
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetPeriodActive(uint8_t *pucTsensSROTAddr, uint32_t uTime)
{
   HWIO_OUTXF(pucTsensSROTAddr, TSENS_MEASURE_PERIOD, MAIN_MEASURE_PERIOD, uTime);
}

/* ============================================================================
**
**  HAL_tsens_srot_SetPeriodSleep
**
**  Description:
**    Sets the period for the sleep case
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uTime
**     - 0x00 measures continiously
**     - 0x01-0xFE defines the length of sleep between two measurements
**                 approx equal to (upper 2bits) * 250ms + (lower 6bits) * 1.95ms
**     - 0xFF measures once
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetPeriodSleep(uint8_t *pucTsensSROTAddr, uint32_t uTime)
{
   HWIO_OUTXF(pucTsensSROTAddr, TSENS_MEASURE_PERIOD, POWERDOWN_MEASURE_PERIOD, uTime);
}

/* ============================================================================
**
**  HAL_tsens_srot_SetAutoAdjustPeriodEn
**
**  Description:
**    Sets whether or not TSENS will auto-adjust the period going in and
**    out of sleep
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    bEnable - true / false
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetAutoAdjustPeriodEn(uint8_t *pucTsensSROTAddr, bool bEnable)
{
   if (bEnable == true)
   {
      HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, AUTO_ADJUST_PERIOD_EN, ENABLED);
   }
   else
   {
      HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, AUTO_ADJUST_PERIOD_EN, DISABLED);
   }
}

/*----------------------------------------------------------------------------
 * Channel enable / disable
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_srot_SetChannelsEnabled
**
**  Description:
**    Enable a set of channels based on a bitmask
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uChannelEnMask - channel enable mask
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetChannelsEnabled(uint8_t *pucTsensSROTAddr, uint32_t uChannelEnMask)
{
   uint32_t uReg;

   uReg = HWIO_INX(pucTsensSROTAddr, TSENS_CTRL);

   uReg &= ~(HWIO_FMSK(TSENS_CTRL, SENSOR0_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR1_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR2_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR3_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR4_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR5_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR6_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR7_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR8_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR9_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR10_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR11_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR12_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR13_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR14_EN) |
             HWIO_FMSK(TSENS_CTRL, SENSOR15_EN));

   uReg |= uChannelEnMask << HWIO_SHFT(TSENS_CTRL, SENSOR0_EN) &
           (HWIO_FMSK(TSENS_CTRL, SENSOR0_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR1_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR2_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR3_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR4_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR5_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR6_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR7_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR8_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR9_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR10_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR11_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR12_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR13_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR14_EN) |
            HWIO_FMSK(TSENS_CTRL, SENSOR15_EN));

   HWIO_OUTX(pucTsensSROTAddr, TSENS_CTRL , uReg);
}

/*----------------------------------------------------------------------------
 * Main enable / disable
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_srot_SetState
**
**  Description:
**    Enable or disable tsens
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    eTsensState - HAL_TSENS_ENABLE/HAL_TSENS_DISABLE
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetState(uint8_t *pucTsensSROTAddr, HAL_tsens_srot_State eTsensState)
{
   switch (eTsensState)
   {
      case HAL_TSENS_ENABLE:
         HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, TSENS_EN, ENABLED);
         break;
      case HAL_TSENS_DISABLE:
         HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, TSENS_EN, DISABLED);
         break;
      default:
         break;
   }
}

/*----------------------------------------------------------------------------
 * Software reset
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_srot_Reset
**
**  Description:
**    Resets TSENS.
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_Reset(uint8_t *pucTsensSROTAddr)
{
   HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, TSENS_SW_RST, RESET_ASSERTED);

   HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, TSENS_SW_RST, RESET_DEASSERTED);
}

/*----------------------------------------------------------------------------
 * Config
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_srot_GetControllerVersion
**
**  Description:
**    Gets the TSENS controller version
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**
**  Return: TSENS controller version
**
**  Dependencies: None
**
** ========================================================================= */
uint32_t HAL_tsens_srot_GetControllerVersion(uint8_t *pucTsensSROTAddr)
{
   return HWIO_INX(pucTsensSROTAddr, TSENS_HW_VER);
}

/* ============================================================================
**
**  HAL_tsens_srot_SetPSHoldResetEn
**
**  Description:
**    Enables / disables PS_HOLD reset functionality
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    bEnable - true / false
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetPSHoldResetEn(uint8_t *pucTsensSROTAddr, bool bEnable)
{
   if (bEnable == true)
   {
      HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, PSHOLD_ARES_EN, ENABLED);
   }
   else
   {
      HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, PSHOLD_ARES_EN, DISABLED);
   }
}

/* ============================================================================
**
**  HAL_tsens_srot_SetResultFormat
**
**  Description:
**    Sets whether the result will be in code or real temperature
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    eResultType - whether the result will be in code or real temperature
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetResultFormat(uint8_t *pucTsensSROTAddr, HAL_tsens_srot_ResultType eResultType)
{
   switch (eResultType)
   {
      case HAL_TSENS_RESULT_TYPE_ADC_CODE:
         HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, RESULT_FORMAT_CODE_OR_TEMP, ADC_CODE);
         break;
      case HAL_TSENS_RESULT_TYPE_DECI_DEG_C:
         HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, RESULT_FORMAT_CODE_OR_TEMP, REAL_TEMPERATURE);
         break;
      default:
         break;
   }
}

/* ============================================================================
**
**  HAL_tsens_srot_SelectADCClkSrc
**
**  Description:
**    Sets a given threshold
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    eADCClkSrc - internal clk or external clk
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SelectADCClkSrc(uint8_t *pucTsensSROTAddr, HAL_tsens_srot_ADCClkSrc eADCClkSrc)
{
   switch (eADCClkSrc)
   {
      case HAL_TSENS_INTERNAL:
         HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, TSENS_ADC_CLK_SEL, INTERNAL_OSCILLATOR);
         break;
      case HAL_TSENS_EXTERNAL:
         HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, TSENS_ADC_CLK_SEL, EXTERNAL_CLOCK_SOURCE);
         break;
      default:
         break;
   }
}

/* ============================================================================
**
**  HAL_tsens_srot_SetConversionFactors
**
**  Description:
**    Sets up the parameters needed to convert from code to deci deg C.
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uChannel - which channel
**    uShift - shift value of N = 7, 8, 9 or 10
**    uShiftedSlope - slope << N, i.e. (900 << N) / (C120 - C30)
**    uCodeAtZero - ADC code at zero degrees C
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetConversionFactors(uint8_t *pucTsensSROTAddr, uint32_t uChannel, uint32_t uShift, uint32_t uShiftedSlope, uint32_t uCodeAtZero)
{
   uint32_t uReg;

   switch (uShift)
   {
      case 7:
         uShift = 0;
         break;
      case 8:
         uShift = 1;
         break;
      case 9:
         uShift = 2;
         break;
      case 10:
         uShift = 3;
         break;
      default:
         break;
   }

   uReg = HWIO_INXI(pucTsensSROTAddr, TSENS_Sn_CONVERSION, uChannel);

   uReg &= ~HWIO_FMSK(TSENS_Sn_CONVERSION, SHIFT);
   uReg &= ~HWIO_FMSK(TSENS_Sn_CONVERSION, SLOPE);
   uReg &= ~HWIO_FMSK(TSENS_Sn_CONVERSION, CZERO);

   uReg |= HWIO_FVAL(TSENS_Sn_CONVERSION, SHIFT, uShift);
   uReg |= HWIO_FVAL(TSENS_Sn_CONVERSION, SLOPE, uShiftedSlope);
   uReg |= HWIO_FVAL(TSENS_Sn_CONVERSION, CZERO, uCodeAtZero);

   HWIO_OUTXI(pucTsensSROTAddr, TSENS_Sn_CONVERSION, uChannel, uReg);
}

/* ============================================================================
**
**  HAL_tsens_srot_SetSensorID
**
**  Description:
**    Sets the sensor ID for each channel
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uSensorID - the sensor ID
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetSensorID(uint8_t *pucTsensSROTAddr, uint32_t uChannel, uint32_t uSensorID)
{
   HWIO_OUTXFI(pucTsensSROTAddr, TSENS_Sn_ID_ASSIGNMENT, uChannel, SENSOR_ID, uSensorID);
}

/* ============================================================================
**
**  HAL_tsens_srot_SetAnalogParameters
**
**  Description:
**    Sets the analog TSENS parameters
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uControl - control register value
**    uConfig - config register value
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetAnalogParameters(uint8_t *pucTsensSROTAddr, uint32_t uControl, uint32_t uConfig)
{
   HWIO_OUTX(pucTsensSROTAddr, TS_CONTROL, uControl);

   HWIO_OUTX(pucTsensSROTAddr, TS_CONFIG, uConfig);
}

/* ============================================================================
**
**  HAL_tsens_srot_SetPWMEn
**
**  Description:
**    Enables / disables PWM functionality
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    bEnable - true / false
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetPWMEn(uint8_t *pucTsensSROTAddr, bool bEnable)
{
   if (bEnable == true)
   {
      HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, MAX_TEMP_PWM_EN, ENABLED);
   }
   else
   {
      HWIO_OUTXV(pucTsensSROTAddr, TSENS_CTRL, MAX_TEMP_PWM_EN, DISABLED);
   }
}

/* ============================================================================
**
**  HAL_tsens_srot_SetSidebandChannelsEnabled
**
**  Description:
**    Sets the sideband channels enabled
**
**  Parameters:
**    pucTsensSROTAddr - address of controller's SROT region
**    uChannelEnMask - bitmask of channels to enable
**
**  Return: None
**
**  Dependencies: None
**
** ========================================================================= */
void HAL_tsens_srot_SetSidebandChannelsEnabled(uint8_t *pucTsensSROTAddr, uint32_t uChannelEnMask)
{
   HWIO_OUTXF(pucTsensSROTAddr, TSENS_SIDEBAND_EN, SENSOR_EN, uChannelEnMask);
}

/*----------------------------------------------------------------------------
 * Char data
 * -------------------------------------------------------------------------*/
/* ============================================================================
**
**  HAL_tsens_UseRedundant
**
**  Description:
**    Whether or not to use the redundant region
**
**  Parameters:
**    None
**
**  Return: true: use redundant char data
**
**  Dependencies: None
**
** ========================================================================= */
bool HAL_tsens_UseRedundant(void)
{
   uint32_t uSwCalRedunSel;

   uSwCalRedunSel = HWIO_INF(QFPROM_CORR_CALIB_ROW22_MSB, SW_CAL_REDUN_SEL);

   if (uSwCalRedunSel & 0x2)
   {
      return true;
   }
   else
   {
      return false;
   }
}

/* ============================================================================
**
**  HAL_tsens_CalSelect
**
**  Description:
**    Determines whether there is 1) no cal data 2) single point cal data or
**    3) two point cal data
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**
**  Return: HAL_tsens_Calibration (not calibrated, one point, or two point)
**
**  Dependencies: None
**
** ========================================================================= */
HAL_tsens_Calibration HAL_tsens_CalSelect(bool bUseRedundant)
{
   if (bUseRedundant == false)
   {
      switch (HWIO_INF(QFPROM_CORR_TSENS_ROW11_LSB, TSENS_CALIBRATION_MODE) & 0x7)
      {
         case 2:
            return HAL_TSENS_CAL_ONE_POINT;
         case 3:
            return HAL_TSENS_CAL_TWO_POINT;
         default:
            return HAL_TSENS_CAL_NOT_CALIBRATED;
      }
   }
   else
   {
      switch (HWIO_INF(QFPROM_CORR_TSENS_ROW23_LSB, REDUN_TSENS_CALIBRATION_MODE) & 0x7)
      {
         case 2:
            return HAL_TSENS_CAL_ONE_POINT;
         case 3:
            return HAL_TSENS_CAL_TWO_POINT;
         default:
            return HAL_TSENS_CAL_NOT_CALIBRATED;
      }
   }
}

/* ==========================================================================*/
uint32_t HAL_tsens_TestSecurity(bool bUseRedundant)
{
   if (bUseRedundant == false)
   {
      return HWIO_INF(QFPROM_CORR_TSENS_ROW11_LSB, TSENS_TEST_SECURITY);
   }
   else
   {
      return HWIO_INF(QFPROM_CORR_TSENS_ROW23_LSB, REDUN_TSENS_TEST_SECURITY);
   }
}
/* ============================================================================
**
**  HAL_tsens_PartialGoodsEnabled
**
**  Description:
**    Determines whether or not partial goods encoding has been enabled
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**
**  Return: true / false
**
**  Dependencies: None
**
** ========================================================================= */
bool HAL_tsens_PartialGoodsEnabled(bool bUseRedundant)
{
   if (bUseRedundant == false)
   {
      if (HWIO_INF(QFPROM_CORR_TSENS_ROW11_LSB, TSENS_CALIBRATION_MODE) & 0x80)
      {
         return true;
      }
   }
   else
   {
      if (HWIO_INF(QFPROM_CORR_TSENS_ROW23_LSB, REDUN_TSENS_CALIBRATION_MODE) & 0x80)
      {
         return true;
      }
   }

   return false;
}

/* ============================================================================
**
**  HAL_tsens_GetBase1
**
**  Description:
**    Gets the Tsens base for cal point 1
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uController - which controller
**
**  Return: adc code
**
**  Dependencies: None
**
** ========================================================================= */
uint32_t HAL_tsens_GetBase1(bool bUseRedundant, uint32_t uController)
{
   if (bUseRedundant == false)
   {
      switch (uController)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_LSB, TSENS_MAIN0_REF_POINT0);
         case 1:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_LSB, TSENS_MAIN1_REF_POINT0);
         case 2:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_LSB, TSENS_MAIN2_REF_POINT0);
         case 3:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_LSB, TSENS_MAIN3_REF_POINT0);
         case 4:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_LSB, TSENS_MAIN4_REF_POINT0);
         case 5:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_LSB, TSENS_MAIN5_REF_POINT0);
         case 6:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_LSB, TSENS_MAIN6_REF_POINT0);
         case 7:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_LSB, TSENS_MAIN7_REF_POINT0);
         case 8:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_LSB, TSENS_MAIN8_REF_POINT0);
         case 9:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_LSB, TSENS_MAIN9_REF_POINT0);
         case 10:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_LSB, TSENS_MAIN10_REF_POINT0);
         default:
            break;
      }
   }
   else
   {
      switch (uController)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_LSB, REDUN_TSENS_MAIN0_REF_POINT0);
         case 1:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_LSB, REDUN_TSENS_MAIN1_REF_POINT0);
         case 2:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_LSB, REDUN_TSENS_MAIN2_REF_POINT0);
         case 3:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_LSB, REDUN_TSENS_MAIN3_REF_POINT0);
         case 4:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_LSB, REDUN_TSENS_MAIN4_REF_POINT0);
         case 5:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_LSB, REDUN_TSENS_MAIN5_REF_POINT0);
         case 6:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_LSB, REDUN_TSENS_MAIN6_REF_POINT0);
         case 7:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_LSB, REDUN_TSENS_MAIN7_REF_POINT0);
         case 8:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_LSB, REDUN_TSENS_MAIN8_REF_POINT0);
         case 9:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_LSB, REDUN_TSENS_MAIN9_REF_POINT0);
         case 10:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_LSB, REDUN_TSENS_MAIN10_REF_POINT0);
         default:
            break;
      }
   }

   return 0;
}

/* ============================================================================
**
**  HAL_tsens_GetBase2
**
**  Description:
**    Gets the Tsens base for cal point 2
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uController - which controller
**
**  Return: adc code
**
**  Dependencies: None
**
** ========================================================================= */
uint32_t HAL_tsens_GetBase2(bool bUseRedundant, uint32_t uController)
{
   if (bUseRedundant == false)
   {
      switch (uController)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_LSB, TSENS_MAIN0_REF_POINT1);
         case 1:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_LSB, TSENS_MAIN1_REF_POINT1);
         case 2:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_LSB, TSENS_MAIN2_REF_POINT1);
         case 3:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_LSB, TSENS_MAIN3_REF_POINT1);
         case 4:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_LSB, TSENS_MAIN4_REF_POINT1);
         case 5:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_LSB, TSENS_MAIN5_REF_POINT1);
         case 6:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_LSB, TSENS_MAIN6_REF_POINT1);
         case 7:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_LSB, TSENS_MAIN7_REF_POINT1);
         case 8:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_LSB, TSENS_MAIN8_REF_POINT1);
         case 9:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_LSB, TSENS_MAIN9_REF_POINT1);
         case 10:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_LSB, TSENS_MAIN10_REF_POINT1);
         default:
            break;
      }
   }
   else
   {
      switch (uController)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_LSB, REDUN_TSENS_MAIN0_REF_POINT1);
         case 1:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_LSB, REDUN_TSENS_MAIN1_REF_POINT1);
         case 2:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_LSB, REDUN_TSENS_MAIN2_REF_POINT1);
         case 3:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_LSB, REDUN_TSENS_MAIN3_REF_POINT1);
         case 4:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_LSB, REDUN_TSENS_MAIN4_REF_POINT1);
         case 5:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_LSB, REDUN_TSENS_MAIN5_REF_POINT1);
         case 6:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_LSB, REDUN_TSENS_MAIN6_REF_POINT1);
         case 7:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_LSB, REDUN_TSENS_MAIN7_REF_POINT1);
         case 8:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_LSB, REDUN_TSENS_MAIN8_REF_POINT1);
         case 9:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_LSB, REDUN_TSENS_MAIN9_REF_POINT1);
         case 10:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_LSB, REDUN_TSENS_MAIN10_REF_POINT1);
         default:
            break;
      }
   }

   return 0;
}

/* ============================================================================
**
**  HAL_tsens_GetOffset1
**
**  Description:
**    Gets Tsens uSensor offset for cal point 1
**
**  Parameters:
**    bUseRedundant - whether or not to use the redundant location
**    uint32_t uFuseIdx
**
**  Return: offset from base
**
**  Dependencies: None
**
** ========================================================================= */
uint32_t HAL_tsens_GetOffset1(bool bUseRedundant, uint32_t uFuseIdx)
{
   if (bUseRedundant == false)
   {
      switch (uFuseIdx)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_LSB, TSENS0_INTERCEPT);
         case 1:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_LSB, TSENS1_INTERCEPT);
         case 2:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_LSB, TSENS2_INTERCEPT);
         case 3:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_MSB, TSENS3_INTERCEPT);
         case 4:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_MSB, TSENS4_INTERCEPT);
         case 5:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_MSB, TSENS5_INTERCEPT);
         case 6:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_MSB, TSENS6_INTERCEPT);
         case 7:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_MSB, TSENS7_INTERCEPT);
         case 8:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_MSB, TSENS8_INTERCEPT);
         case 9:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_MSB, TSENS9_INTERCEPT);
         case 10:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW0_MSB, TSENS10_INTERCEPT);

         case 11:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_LSB, TSENS11_INTERCEPT);
         case 12:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_LSB, TSENS12_INTERCEPT);
         case 13:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_LSB, TSENS13_INTERCEPT);
         case 14:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_MSB, TSENS14_INTERCEPT);
         case 15:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_MSB, TSENS15_INTERCEPT);
         case 16:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_MSB, TSENS16_INTERCEPT);
         case 17:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_MSB, TSENS17_INTERCEPT);
         case 18:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_MSB, TSENS18_INTERCEPT);
         case 19:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_MSB, TSENS19_INTERCEPT);
         case 20:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_MSB, TSENS20_INTERCEPT);
         case 21:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW1_MSB, TSENS21_INTERCEPT);

         case 22:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_LSB, TSENS22_INTERCEPT);
         case 23:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_LSB, TSENS23_INTERCEPT);
         case 24:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_LSB, TSENS24_INTERCEPT);
         case 25:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_MSB, TSENS25_INTERCEPT);
         case 26:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_MSB, TSENS26_INTERCEPT);
         case 27:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_MSB, TSENS27_INTERCEPT);
         case 28:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_MSB, TSENS28_INTERCEPT);
         case 29:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_MSB, TSENS29_INTERCEPT);
         case 30:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_MSB, TSENS30_INTERCEPT);
         case 31:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_MSB, TSENS31_INTERCEPT);
         case 32:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW2_MSB, TSENS32_INTERCEPT);

         case 33:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_LSB, TSENS33_INTERCEPT);
         case 34:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_LSB, TSENS34_INTERCEPT);
         case 35:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_LSB, TSENS35_INTERCEPT);
         case 36:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_MSB, TSENS36_INTERCEPT);
         case 37:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_MSB, TSENS37_INTERCEPT);
         case 38:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_MSB, TSENS38_INTERCEPT);
         case 39:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_MSB, TSENS39_INTERCEPT);
         case 40:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_MSB, TSENS40_INTERCEPT);
         case 41:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_MSB, TSENS41_INTERCEPT);
         case 42:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_MSB, TSENS42_INTERCEPT);
         case 43:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW3_MSB, TSENS43_INTERCEPT);

         case 44:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_LSB, TSENS44_INTERCEPT);
         case 45:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_LSB, TSENS45_INTERCEPT);
         case 46:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_LSB, TSENS46_INTERCEPT);
         case 47:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_MSB, TSENS47_INTERCEPT);
         case 48:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_MSB, TSENS48_INTERCEPT);
         case 49:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_MSB, TSENS49_INTERCEPT);
         case 50:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_MSB, TSENS50_INTERCEPT);
         case 51:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_MSB, TSENS51_INTERCEPT);
         case 52:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_MSB, TSENS52_INTERCEPT);
         case 53:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_MSB, TSENS53_INTERCEPT);
         case 54:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW4_MSB, TSENS54_INTERCEPT);

         case 55:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_LSB, TSENS55_INTERCEPT);
         case 56:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_LSB, TSENS56_INTERCEPT);
         case 57:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_LSB, TSENS57_INTERCEPT);
         case 58:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_MSB, TSENS58_INTERCEPT);
         case 59:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_MSB, TSENS59_INTERCEPT);
         case 60:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_MSB, TSENS60_INTERCEPT);
         case 61:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_MSB, TSENS61_INTERCEPT);
         case 62:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_MSB, TSENS62_INTERCEPT);
         case 63:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_MSB, TSENS63_INTERCEPT);
         case 64:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_MSB, TSENS64_INTERCEPT);
         case 65:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW5_MSB, TSENS65_INTERCEPT);

         case 66:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_LSB, TSENS66_INTERCEPT);
         case 67:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_LSB, TSENS67_INTERCEPT);
         case 68:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_LSB, TSENS68_INTERCEPT);
         case 69:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_MSB, TSENS69_INTERCEPT);
         case 70:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_MSB, TSENS70_INTERCEPT);
         case 71:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_MSB, TSENS71_INTERCEPT);
         case 72:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_MSB, TSENS72_INTERCEPT);
         case 73:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_MSB, TSENS73_INTERCEPT);
         case 74:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_MSB, TSENS74_INTERCEPT);
         case 75:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_MSB, TSENS75_INTERCEPT);
         case 76:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW6_MSB, TSENS76_INTERCEPT);

         case 77:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_LSB, TSENS77_INTERCEPT);
         case 78:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_LSB, TSENS78_INTERCEPT);
         case 79:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_LSB, TSENS79_INTERCEPT);
         case 80:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_MSB, TSENS80_INTERCEPT);
         case 81:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_MSB, TSENS81_INTERCEPT);
         case 82:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_MSB, TSENS82_INTERCEPT);
         case 83:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_MSB, TSENS83_INTERCEPT);
         case 84:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_MSB, TSENS84_INTERCEPT);
         case 85:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_MSB, TSENS85_INTERCEPT);
         case 86:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_MSB, TSENS86_INTERCEPT);
         case 87:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW7_MSB, TSENS87_INTERCEPT);

         case 88:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_LSB, TSENS88_INTERCEPT);
         case 89:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_LSB, TSENS89_INTERCEPT);
         case 90:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_LSB, TSENS90_INTERCEPT);
         case 91:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_MSB, TSENS91_INTERCEPT);
         case 92:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_MSB, TSENS92_INTERCEPT);
         case 93:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_MSB, TSENS93_INTERCEPT);
         case 94:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_MSB, TSENS94_INTERCEPT);
         case 95:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_MSB, TSENS95_INTERCEPT);
         case 96:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_MSB, TSENS96_INTERCEPT);
         case 97:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_MSB, TSENS97_INTERCEPT);
         case 98:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW8_MSB, TSENS98_INTERCEPT);

         case 99:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_LSB, TSENS99_INTERCEPT);
         case 100:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_LSB, TSENS100_INTERCEPT);
         case 101:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_LSB, TSENS101_INTERCEPT);
         case 102:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_MSB, TSENS102_INTERCEPT);
         case 103:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_MSB, TSENS103_INTERCEPT);
         case 104:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_MSB, TSENS104_INTERCEPT);
         case 105:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_MSB, TSENS105_INTERCEPT);
         case 106:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_MSB, TSENS106_INTERCEPT);
         case 107:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_MSB, TSENS107_INTERCEPT);
         case 108:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_MSB, TSENS108_INTERCEPT);
         case 109:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW9_MSB, TSENS109_INTERCEPT);

         case 110:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_LSB, TSENS110_INTERCEPT);
         case 111:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_LSB, TSENS111_INTERCEPT);
         case 112:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_LSB, TSENS112_INTERCEPT);
         case 113:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_MSB, TSENS113_INTERCEPT);
         case 114:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_MSB, TSENS114_INTERCEPT);
         case 115:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_MSB, TSENS115_INTERCEPT);
         case 116:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_MSB, TSENS116_INTERCEPT);
         case 117:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_MSB, TSENS117_INTERCEPT);
         case 118:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_MSB, TSENS118_INTERCEPT);
         case 119:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_MSB, TSENS119_INTERCEPT);
         case 120:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW10_MSB, TSENS120_INTERCEPT);

         default:
            break;
      }
   }
   else
   {
      switch (uFuseIdx)
      {
         case 0:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_LSB, REDUN_TSENS0_INTERCEPT);
         case 1:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_LSB, REDUN_TSENS1_INTERCEPT);
         case 2:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_LSB, REDUN_TSENS2_INTERCEPT);
         case 3:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_MSB, REDUN_TSENS3_INTERCEPT);
         case 4:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_MSB, REDUN_TSENS4_INTERCEPT);
         case 5:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_MSB, REDUN_TSENS5_INTERCEPT);
         case 6:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_MSB, REDUN_TSENS6_INTERCEPT);
         case 7:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_MSB, REDUN_TSENS7_INTERCEPT);
         case 8:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_MSB, REDUN_TSENS8_INTERCEPT);
         case 9:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_MSB, REDUN_TSENS9_INTERCEPT);
         case 10:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW12_MSB, REDUN_TSENS10_INTERCEPT);

         case 11:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_LSB, REDUN_TSENS11_INTERCEPT);
         case 12:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_LSB, REDUN_TSENS12_INTERCEPT);
         case 13:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_LSB, REDUN_TSENS13_INTERCEPT);
         case 14:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_MSB, REDUN_TSENS14_INTERCEPT);
         case 15:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_MSB, REDUN_TSENS15_INTERCEPT);
         case 16:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_MSB, REDUN_TSENS16_INTERCEPT);
         case 17:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_MSB, REDUN_TSENS17_INTERCEPT);
         case 18:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_MSB, REDUN_TSENS18_INTERCEPT);
         case 19:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_MSB, REDUN_TSENS19_INTERCEPT);
         case 20:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_MSB, REDUN_TSENS20_INTERCEPT);
         case 21:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW13_MSB, REDUN_TSENS21_INTERCEPT);

         case 22:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_LSB, REDUN_TSENS22_INTERCEPT);
         case 23:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_LSB, REDUN_TSENS23_INTERCEPT);
         case 24:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_LSB, REDUN_TSENS24_INTERCEPT);
         case 25:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_MSB, REDUN_TSENS25_INTERCEPT);
         case 26:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_MSB, REDUN_TSENS26_INTERCEPT);
         case 27:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_MSB, REDUN_TSENS27_INTERCEPT);
         case 28:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_MSB, REDUN_TSENS28_INTERCEPT);
         case 29:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_MSB, REDUN_TSENS29_INTERCEPT);
         case 30:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_MSB, REDUN_TSENS30_INTERCEPT);
         case 31:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_MSB, REDUN_TSENS31_INTERCEPT);
         case 32:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW14_MSB, REDUN_TSENS32_INTERCEPT);

         case 33:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_LSB, REDUN_TSENS33_INTERCEPT);
         case 34:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_LSB, REDUN_TSENS34_INTERCEPT);
         case 35:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_LSB, REDUN_TSENS35_INTERCEPT);
         case 36:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_MSB, REDUN_TSENS36_INTERCEPT);
         case 37:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_MSB, REDUN_TSENS37_INTERCEPT);
         case 38:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_MSB, REDUN_TSENS38_INTERCEPT);
         case 39:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_MSB, REDUN_TSENS39_INTERCEPT);
         case 40:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_MSB, REDUN_TSENS40_INTERCEPT);
         case 41:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_MSB, REDUN_TSENS41_INTERCEPT);
         case 42:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_MSB, REDUN_TSENS42_INTERCEPT);
         case 43:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW15_MSB, REDUN_TSENS43_INTERCEPT);

         case 44:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_LSB, REDUN_TSENS44_INTERCEPT);
         case 45:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_LSB, REDUN_TSENS45_INTERCEPT);
         case 46:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_LSB, REDUN_TSENS46_INTERCEPT);
         case 47:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_MSB, REDUN_TSENS47_INTERCEPT);
         case 48:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_MSB, REDUN_TSENS48_INTERCEPT);
         case 49:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_MSB, REDUN_TSENS49_INTERCEPT);
         case 50:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_MSB, REDUN_TSENS50_INTERCEPT);
         case 51:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_MSB, REDUN_TSENS51_INTERCEPT);
         case 52:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_MSB, REDUN_TSENS52_INTERCEPT);
         case 53:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_MSB, REDUN_TSENS53_INTERCEPT);
         case 54:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW16_MSB, REDUN_TSENS54_INTERCEPT);

         case 55:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_LSB, REDUN_TSENS55_INTERCEPT);
         case 56:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_LSB, REDUN_TSENS56_INTERCEPT);
         case 57:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_LSB, REDUN_TSENS57_INTERCEPT);
         case 58:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_MSB, REDUN_TSENS58_INTERCEPT);
         case 59:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_MSB, REDUN_TSENS59_INTERCEPT);
         case 60:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_MSB, REDUN_TSENS60_INTERCEPT);
         case 61:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_MSB, REDUN_TSENS61_INTERCEPT);
         case 62:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_MSB, REDUN_TSENS62_INTERCEPT);
         case 63:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_MSB, REDUN_TSENS63_INTERCEPT);
         case 64:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_MSB, REDUN_TSENS64_INTERCEPT);
         case 65:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW17_MSB, REDUN_TSENS65_INTERCEPT);

         case 66:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_LSB, REDUN_TSENS66_INTERCEPT);
         case 67:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_LSB, REDUN_TSENS67_INTERCEPT);
         case 68:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_LSB, REDUN_TSENS68_INTERCEPT);
         case 69:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_MSB, REDUN_TSENS69_INTERCEPT);
         case 70:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_MSB, REDUN_TSENS70_INTERCEPT);
         case 71:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_MSB, REDUN_TSENS71_INTERCEPT);
         case 72:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_MSB, REDUN_TSENS72_INTERCEPT);
         case 73:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_MSB, REDUN_TSENS73_INTERCEPT);
         case 74:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_MSB, REDUN_TSENS74_INTERCEPT);
         case 75:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_MSB, REDUN_TSENS75_INTERCEPT);
         case 76:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW18_MSB, REDUN_TSENS76_INTERCEPT);

         case 77:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_LSB, REDUN_TSENS77_INTERCEPT);
         case 78:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_LSB, REDUN_TSENS78_INTERCEPT);
         case 79:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_LSB, REDUN_TSENS79_INTERCEPT);
         case 80:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_MSB, REDUN_TSENS80_INTERCEPT);
         case 81:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_MSB, REDUN_TSENS81_INTERCEPT);
         case 82:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_MSB, REDUN_TSENS82_INTERCEPT);
         case 83:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_MSB, REDUN_TSENS83_INTERCEPT);
         case 84:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_MSB, REDUN_TSENS84_INTERCEPT);
         case 85:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_MSB, REDUN_TSENS85_INTERCEPT);
         case 86:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_MSB, REDUN_TSENS86_INTERCEPT);
         case 87:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW19_MSB, REDUN_TSENS87_INTERCEPT);

         case 88:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_LSB, REDUN_TSENS88_INTERCEPT);
         case 89:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_LSB, REDUN_TSENS89_INTERCEPT);
         case 90:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_LSB, REDUN_TSENS90_INTERCEPT);
         case 91:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_MSB, REDUN_TSENS91_INTERCEPT);
         case 92:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_MSB, REDUN_TSENS92_INTERCEPT);
         case 93:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_MSB, REDUN_TSENS93_INTERCEPT);
         case 94:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_MSB, REDUN_TSENS94_INTERCEPT);
         case 95:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_MSB, REDUN_TSENS95_INTERCEPT);
         case 96:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_MSB, REDUN_TSENS96_INTERCEPT);
         case 97:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_MSB, REDUN_TSENS97_INTERCEPT);
         case 98:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW20_MSB, REDUN_TSENS98_INTERCEPT);

         case 99:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_LSB, REDUN_TSENS99_INTERCEPT);
         case 100:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_LSB, REDUN_TSENS100_INTERCEPT);
         case 101:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_LSB, REDUN_TSENS101_INTERCEPT);
         case 102:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_MSB, REDUN_TSENS102_INTERCEPT);
         case 103:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_MSB, REDUN_TSENS103_INTERCEPT);
         case 104:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_MSB, REDUN_TSENS104_INTERCEPT);
         case 105:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_MSB, REDUN_TSENS105_INTERCEPT);
         case 106:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_MSB, REDUN_TSENS106_INTERCEPT);
         case 107:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_MSB, REDUN_TSENS107_INTERCEPT);
         case 108:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_MSB, REDUN_TSENS108_INTERCEPT);
         case 109:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW21_MSB, REDUN_TSENS109_INTERCEPT);

         case 110:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_LSB, REDUN_TSENS110_INTERCEPT);
         case 111:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_LSB, REDUN_TSENS111_INTERCEPT);
         case 112:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_LSB, REDUN_TSENS112_INTERCEPT);
         case 113:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_MSB, REDUN_TSENS113_INTERCEPT);
         case 114:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_MSB, REDUN_TSENS114_INTERCEPT);
         case 115:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_MSB, REDUN_TSENS115_INTERCEPT);
         case 116:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_MSB, REDUN_TSENS116_INTERCEPT);
         case 117:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_MSB, REDUN_TSENS117_INTERCEPT);
         case 118:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_MSB, REDUN_TSENS118_INTERCEPT);
         case 119:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_MSB, REDUN_TSENS119_INTERCEPT);
         case 120:
            return HWIO_INF(QFPROM_CORR_TSENS_ROW22_MSB, REDUN_TSENS120_INTERCEPT);

         default:
            break;
      }
   }

   return 0;
}

