/*============================================================================
  FILE:         TsensLoader.c

  OVERVIEW:     Implementation of TSENS supporting XBL loader.

  DEPENDENCIES: None

         Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
         All Rights Reserved.
         Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

         Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
         All Rights Reserved.
         Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <asm/mach-qdf2400/tsens/TsensBsp.h>
#include <target/delay.h>
#include <target/cmdline.h>
//#include "tlmm.h"
//#include "thermal_combiner_hwio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define MinThreshold          -50
#define MaxThreshold          150
#define PWM_GPIO 123

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef struct
{
   uint32_t bChannelIsDead;
   uint32_t uCodeAtZero;
   uint32_t uShiftedSlope;
} TsensChannelType;

typedef struct
{
   TsensChannelType aChannels[TSENS_MAX_NUM_CHANNELS_PER_CONTROLLER];
   uint8_t *pucTsensSROTAddr;
   uint8_t *pucTsensTMAddr;
   uint32_t uVersion;
   uint32_t uNumChannelsEnabled;
   uint32_t uChannelEnableMask;
   uint32_t uLowerEnableMask;
   uint32_t uUpperEnableMask;
   uint32_t uCriticalEnableMask;
   uint32_t bBroadcastEnabled;
   int32_t nBase1;
   int32_t nBase2;
   int32_t nShiftedSlope;
} TsensControllerType;

typedef struct
{
   const TsensBspType *pTsensBsp;
   TsensControllerType *paControllers;
   int32_t nLastTempDeciDegC;
   uint32_t uLastSensor;
   int32_t nThresholdMax;
   int32_t nThresholdMin;
} TsensDevCtxtType;

typedef struct
{
   int32_t nDegC;      /**< Temperature in degrees Celsius */
   int32_t nDeciDegC;  /**< Temperature in deci degrees Celsius */
} TsensTempType;

typedef enum TSENS_THRESHOLD_TYPE_ENUM
{
   TSENS_MIN_THRESHOLD = 0,
   TSENS_LOWER_THRESHOLD,
   TSENS_CRITICAL_THRESHOLD,
   TSENS_UPPER_THRESHOLD,
   TSENS_MAX_THRESHOLD,
   TSENS_UNKNOW_THRESHOLD
} TSENS_THRESHOLD_TYPE;

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
TsensDevCtxtType gTsensDevCtxt = {0};
extern const TsensBspType TsensBsp[];
extern TsensSensorCfgType gaTsensSensorCfgs[];
TsensControllerType TsensController[99];
uint32_t gbTsensInitialized = false;

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/
static uint64_t contoller2mask(int x)
{
   return ((uint64_t)1 << x);
}

static uint8_t* Tsens_MapHWIORegion(uint8_t *puPhysical, uint32_t uSize)
{
   return puPhysical;
}

/* ============================================================================
**
**  MaxTempOverGpioAsPWM
**
**  Description:
**    Enables the thermal combiner to output the max temp on a GPIO as PWM
**
**  Parameters: None
**
**  Return: 0 on success
**
**  Dependencies: None
**
** ========================================================================= */
static void MaxTempOverGpioAsPWM()
{
  /* Therm combiner settings */
  HWIO_TLMM_THERM_COMBINER_CFG1_OUTM(HWIO_TLMM_THERM_COMBINER_CFG1_PWMDIV16_BMSK, (0x0) << HWIO_TLMM_THERM_COMBINER_CFG1_PWMDIV16_SHFT); /* PWM_AT_THERM_CLK_X_2_10 */
  HWIO_TLMM_THERM_COMBINER_CFG1_OUTM(HWIO_TLMM_THERM_COMBINER_CFG1_RAW_DATA_BMSK, (0x0) << HWIO_TLMM_THERM_COMBINER_CFG1_RAW_DATA_SHFT); /* CELCIUS_12_BIT */
  HWIO_TLMM_THERM_COMBINER_CFG1_OUTM(HWIO_TLMM_THERM_COMBINER_CFG1_HOLD_BMSK, (0x8) << HWIO_TLMM_THERM_COMBINER_CFG1_HOLD_SHFT);     /* Hold for 8 cycles */
  HWIO_TLMM_THERM_COMBINER_CFG1_OUTM(HWIO_TLMM_THERM_COMBINER_CFG1_OUTSEL_BMSK, (0x0) << HWIO_TLMM_THERM_COMBINER_CFG1_OUTSEL_SHFT);   /* MAX_OUT */
  HWIO_TLMM_THERM_COMBINER_CFG1_OUTM(HWIO_TLMM_THERM_COMBINER_CFG1_OUTSEL_BMSK, (0x0) << HWIO_TLMM_THERM_COMBINER_CFG1_OUTSEL_SHFT);   /* XO_CLK */

  /* GPIO Configuration */
  GPIO_SET_FUNC(PWM_GPIO, 0x0);
  GPIO_OUT_EN(PWM_GPIO);

  /* PWM output from combiner */
  HWIO_TLMM_THERM_COMBINER_CFG2_OUTM(HWIO_TLMM_THERM_COMBINER_CFG2_SPL_COND_BMSK, (0x1) << HWIO_TLMM_THERM_COMBINER_CFG2_SPL_COND_SHFT);
}

static int32_t Tsens_DivideWithRounding(int32_t nNum, int32_t nDen)
{
   int32_t nOffset = nDen / 2;

   if (nNum < 0)
   {
      nOffset *= -1;
   }

   return (nNum + nOffset) / nDen;
}

static int32_t Tsens_CheckThreshold(int32_t nThreshold)
{
   if (nThreshold > gTsensDevCtxt.nThresholdMax)
   {
      return gTsensDevCtxt.nThresholdMax;
   }
   else if (nThreshold < gTsensDevCtxt.nThresholdMin)
   {
      return gTsensDevCtxt.nThresholdMin;
   }
   else
   {
      return nThreshold;
   }
}

static TsensResultType Tsens_WaitForFirstRead(void)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   const TsensControllerType *paControllers = gTsensDevCtxt.paControllers;
   uint32_t uMaxNumChannelsEnabled = 0;
   uint32_t uNumChannelsEnabled;
   uint32_t uController;
   uint32_t uWaitTime_us;

   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      uNumChannelsEnabled = paControllers[uController].uNumChannelsEnabled;

      if (uNumChannelsEnabled > uMaxNumChannelsEnabled)
      {
         uMaxNumChannelsEnabled = uNumChannelsEnabled;
      }
   }

   uWaitTime_us = pBsp->uSensorConvTime_us * uMaxNumChannelsEnabled;

   udelay(uWaitTime_us);

   return TSENS_SUCCESS;
}

static TsensResultType Tsens_GetCalibration(void)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   const int32_t nCalPoint1DeciDegC = pBsp->nCalPoint1DeciDegC;
   const int32_t nCalPoint2DeciDegC = pBsp->nCalPoint2DeciDegC;
   const int32_t nDeltaDeciDegC = nCalPoint2DeciDegC - nCalPoint1DeciDegC;
   const int32_t nShiftedSlopeNum = nDeltaDeciDegC << pBsp->uShift;
   const TsensSensorCfgType *pSensorCfg;
   HAL_tsens_Calibration eSensorCalType = HAL_TSENS_CAL_NOT_CALIBRATED;
   TsensControllerType *paControllers = gTsensDevCtxt.paControllers;
   TsensControllerType *pController;
   HAL_tsens_Calibration eCalType;
   bool bUseRedundant;
   bool bPartialGoods;
   TsensChannelType *pChannel;
   uint32_t uSensor;
   uint32_t uController;
   uint32_t uChannel;
   int32_t nCode1;
   int32_t nNum;
   int32_t nDen;

   bUseRedundant = HAL_tsens_UseRedundant();

   eCalType = HAL_tsens_CalSelect(bUseRedundant);
   bPartialGoods = HAL_tsens_PartialGoodsEnabled(bUseRedundant);

   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      pController = &paControllers[uController];
      pController->uChannelEnableMask = 0;

      /* Get the base points as applicable */
      switch (eCalType)
      {
         case HAL_TSENS_CAL_ONE_POINT:
            pController->nBase1 = (int32_t)HAL_tsens_GetBase1(bUseRedundant, uController);
            break;

         case HAL_TSENS_CAL_TWO_POINT:
            pController->nBase1 = (int32_t)HAL_tsens_GetBase1(bUseRedundant, uController);
            pController->nBase2 = (int32_t)HAL_tsens_GetBase2(bUseRedundant, uController);

            // uShiftedSlope = ((T2 - T1) << N) / (C2 - C1)
            nDen = pController->nBase2 - pController->nBase1;
            pController->nShiftedSlope = Tsens_DivideWithRounding(nShiftedSlopeNum, nDen);
            break;

         default:
            break;
      }
   }

   /* Get the cal data per sensor */
   for (uSensor = 0; uSensor < pBsp->uNumSensors; uSensor++)
   {
      pSensorCfg = &pBsp->paSensorCfgs[uSensor];
      uController = pSensorCfg->uController;
      uChannel = pSensorCfg->uChannel;
      pController = &paControllers[uController];
      pChannel = &pController->aChannels[uChannel];
      pChannel->bChannelIsDead = false;

      if (bPartialGoods == true)
      {
         if (0xf == HAL_tsens_GetOffset1(bUseRedundant, pSensorCfg->uFuseIdx))
         {
            pChannel->bChannelIsDead = true;
            continue;
         }
      }

      /* Check to see if default calibration is being forced */
      switch (pSensorCfg->eCal)
      {
         case TSENS_BSP_SENSOR_CAL_NORMAL:
            /* Use the normal method */
            eSensorCalType = eCalType;
            break;

         case TSENS_BSP_SENSOR_CAL_IGNORE_DEVICE_CAL:
            /* Force default char data */
            eSensorCalType = HAL_TSENS_CAL_NOT_CALIBRATED;
            break;

         default:
            return TSENS_ERROR;
      }

      switch (eSensorCalType)
      {
         case HAL_TSENS_CAL_ONE_POINT:
            nCode1 = pController->nBase1 + (int32_t)HAL_tsens_GetOffset1(bUseRedundant, pSensorCfg->uFuseIdx);

            // uCodeAtZero = C1 - T1 * slope
            nNum = nCalPoint1DeciDegC * (pSensorCfg->nCalPoint2CodeDefault - pSensorCfg->nCalPoint1CodeDefault);
            pChannel->uCodeAtZero = (uint32_t)(nCode1 - Tsens_DivideWithRounding(nNum, nDeltaDeciDegC));

            // uShiftedSlope = ((T2 - T1) << N) / (C2 - C1)
            nDen = pSensorCfg->nCalPoint2CodeDefault - pSensorCfg->nCalPoint1CodeDefault;
            pChannel->uShiftedSlope = (uint32_t)Tsens_DivideWithRounding(nShiftedSlopeNum, nDen);
            break;

         case HAL_TSENS_CAL_TWO_POINT:
            nCode1 = pController->nBase1 + (int32_t)HAL_tsens_GetOffset1(bUseRedundant, pSensorCfg->uFuseIdx);

            // uCodeAtZero = C1 - T1 * slope
            nNum = nCalPoint1DeciDegC * (pController->nBase2 - pController->nBase1);
            pChannel->uCodeAtZero = (uint32_t)(nCode1 - Tsens_DivideWithRounding(nNum, nDeltaDeciDegC));

            // uShiftedSlope
            pChannel->uShiftedSlope = pController->nShiftedSlope;
            break;

         default:
            // uCodeAtZero = ((T1 * (C1 - C2)) / (T2 - T1)) + C1
            nNum = (pSensorCfg->nCalPoint1CodeDefault - pSensorCfg->nCalPoint2CodeDefault) * nCalPoint1DeciDegC;
            pChannel->uCodeAtZero = (uint32_t)(Tsens_DivideWithRounding(nNum, nDeltaDeciDegC) + pSensorCfg->nCalPoint1CodeDefault);

            // uShiftedSlope = ((T2 - T1) << N) / (C2 - C1)
            nDen = pSensorCfg->nCalPoint2CodeDefault - pSensorCfg->nCalPoint1CodeDefault;
            pChannel->uShiftedSlope = (uint32_t)Tsens_DivideWithRounding(nShiftedSlopeNum, nDen);
            break;
      }

      pController->uChannelEnableMask |= 1 << uChannel;
      pController->uNumChannelsEnabled++;
   }

   return TSENS_SUCCESS;
}

static TsensResultType Tsens_EnableControllers(uint64_t controller_mask)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   const TsensControllerType *paControllers = gTsensDevCtxt.paControllers;
   uint32_t uController;

   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      if (paControllers[uController].uChannelEnableMask != 0)
      {
          if (contoller2mask(uController) & controller_mask) {
              HAL_tsens_srot_SetState(paControllers[uController].pucTsensSROTAddr, HAL_TSENS_ENABLE);
          }
      }
   }

   return TSENS_SUCCESS;
}

static TsensResultType Tsens_DisableControllers(void)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   const TsensControllerType *paControllers = gTsensDevCtxt.paControllers;
   uint32_t uController;

   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      HAL_tsens_srot_SetState(paControllers[uController].pucTsensSROTAddr, HAL_TSENS_DISABLE);
   }

   return TSENS_SUCCESS;
}

static TsensResultType Tsens_ConfigureControllers(void)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   const TsensControllerCfgType *pControllerCfg;
   TsensControllerType *pController;
   uint8_t *pucTsensSROTAddr;
   uint32_t uController;
   uint32_t uSidebandEnMask;

   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      pControllerCfg = &pBsp->paControllerCfgs[uController];
      pController = &gTsensDevCtxt.paControllers[uController];
      pucTsensSROTAddr = pController->pucTsensSROTAddr;

      pController->bBroadcastEnabled = false;

      if (pController->uChannelEnableMask != 0)
      {
         HAL_tsens_srot_Reset(pucTsensSROTAddr);
         HAL_tsens_srot_SetPSHoldResetEn(pucTsensSROTAddr, pControllerCfg->bPSHoldResetEn);
         HAL_tsens_srot_SetResultFormat(pucTsensSROTAddr, HAL_TSENS_RESULT_TYPE_DECI_DEG_C);
         HAL_tsens_srot_SetPeriodActive(pucTsensSROTAddr, pControllerCfg->uPeriodActive);
         HAL_tsens_srot_SetPeriodSleep(pucTsensSROTAddr, pControllerCfg->uPeriodSleep);
         HAL_tsens_srot_SetAutoAdjustPeriodEn(pucTsensSROTAddr, pControllerCfg->bAutoAdjustPeriod);
         HAL_tsens_srot_SelectADCClkSrc(pucTsensSROTAddr, HAL_TSENS_INTERNAL);
         HAL_tsens_srot_SetChannelsEnabled(pucTsensSROTAddr, pController->uChannelEnableMask);
         HAL_tsens_srot_SetAnalogParameters(pucTsensSROTAddr, pControllerCfg->uTSControl, pControllerCfg->uTSConfig);
         HAL_tsens_srot_SetPWMEn(pucTsensSROTAddr, pControllerCfg->bPWMEn);

         uSidebandEnMask = pControllerCfg->uSidebandEnMask & pController->uChannelEnableMask;
         if (pController->uVersion == 0x20000000)
         {
            HAL_tsens_srot_SetSidebandChannelsEnabled(pController->pucTsensTMAddr, uSidebandEnMask);
         }
         else
         {
            HAL_tsens_srot_SetSidebandChannelsEnabled(pucTsensSROTAddr, uSidebandEnMask);
         }

         if (pControllerCfg->bStandAlone == true)
         {
            HAL_tsens_srot_SelectADCClkSrc(pucTsensSROTAddr, HAL_TSENS_EXTERNAL);
         }
         else
         {
            HAL_tsens_srot_SelectADCClkSrc(pucTsensSROTAddr, HAL_TSENS_INTERNAL);
         }
      }
   }

   return TSENS_SUCCESS;
}

static TsensResultType Tsens_ConfigureSensors(void)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   const TsensSensorCfgType *pSensorCfg;
   const TsensChannelType *pChannel;
   const int32_t nThresholdMin = gTsensDevCtxt.nThresholdMin;
   const int32_t nThresholdMax = gTsensDevCtxt.nThresholdMax;
   TsensControllerType *pController;
   uint8_t *pucTsensSROTAddr;
   uint8_t *pucTsensTMAddr;
   uint32_t uSensor;
   uint32_t uController;
   uint32_t uChannel;
   int32_t nThreshold;

   for (uSensor = 0; uSensor < pBsp->uNumSensors; uSensor++)
   {
      pSensorCfg = &pBsp->paSensorCfgs[uSensor];
      uController = pSensorCfg->uController;
      uChannel = pSensorCfg->uChannel;
      pController = &gTsensDevCtxt.paControllers[uController];
      pucTsensSROTAddr = pController->pucTsensSROTAddr;
      pucTsensTMAddr = pController->pucTsensTMAddr;
      pChannel = &pController->aChannels[uChannel];

      if (pChannel->bChannelIsDead == false)
      {
         /* Set up sensor ID */
         HAL_tsens_srot_SetSensorID(pucTsensSROTAddr, uChannel, pSensorCfg->uSensorID);

         /* Set up scaling parameters */
         HAL_tsens_srot_SetConversionFactors(pucTsensSROTAddr,
                                             uChannel,
                                             gTsensDevCtxt.pTsensBsp->uShift,
                                             pChannel->uShiftedSlope,
                                             pChannel->uCodeAtZero);

         /* Min threshold configuration */
         if (pSensorCfg->nThresholdMinDeciDegC != TSENS_THRESHOLD_DISABLED)
         {
            nThreshold = Tsens_CheckThreshold(pSensorCfg->nThresholdMinDeciDegC);
            HAL_tsens_srot_SetThreshold(pucTsensSROTAddr, uChannel, HAL_TSENS_TH_MIN, nThreshold);
            HAL_tsens_srot_EnableInterrupt(pucTsensSROTAddr, uChannel, HAL_TSENS_TH_MIN);
         }
         else
         {
            HAL_tsens_srot_SetThreshold(pucTsensSROTAddr, uChannel, HAL_TSENS_TH_MIN, nThresholdMin);
            HAL_tsens_srot_DisableInterrupt(pucTsensSROTAddr, uChannel, HAL_TSENS_TH_MIN);
         }

         /* Lower threshold configuration */
         if (pSensorCfg->nThresholdLowerDeciDegC != TSENS_THRESHOLD_DISABLED)
         {
            nThreshold = Tsens_CheckThreshold(pSensorCfg->nThresholdLowerDeciDegC);
            HAL_tsens_tm_SetThreshold(pucTsensTMAddr, uChannel, HAL_TSENS_TH_LOWER, nThreshold);
            pController->uLowerEnableMask |= 1 << uChannel;
         }
         else
         {
            HAL_tsens_tm_SetThreshold(pucTsensTMAddr, uChannel, HAL_TSENS_TH_LOWER, nThresholdMin);
         }

         /* Upper threshold configuration */
         if (pSensorCfg->nThresholdUpperDeciDegC != TSENS_THRESHOLD_DISABLED)
         {
            nThreshold = Tsens_CheckThreshold(pSensorCfg->nThresholdUpperDeciDegC);
            HAL_tsens_tm_SetThreshold(pucTsensTMAddr, uChannel, HAL_TSENS_TH_UPPER, nThreshold);
            pController->uUpperEnableMask |= 1 << uChannel;
         }
         else
         {
            HAL_tsens_tm_SetThreshold(pucTsensTMAddr, uChannel, HAL_TSENS_TH_UPPER, nThresholdMax);
         }

         /* Critical threshold configuration */
         if (pSensorCfg->nThresholdCriticalDeciDegC != TSENS_THRESHOLD_DISABLED)
         {
            nThreshold = Tsens_CheckThreshold(pSensorCfg->nThresholdCriticalDeciDegC);
            HAL_tsens_tm_SetThreshold(pucTsensTMAddr, uChannel, HAL_TSENS_TH_CRITICAL, nThreshold);
            pController->uCriticalEnableMask |= 1 << uChannel;
         }
         else
         {
            HAL_tsens_tm_SetThreshold(pucTsensTMAddr, uChannel, HAL_TSENS_TH_CRITICAL, nThresholdMax);
         }

         /* Max threshold configuration */
         if (pSensorCfg->nThresholdMaxDeciDegC != TSENS_THRESHOLD_DISABLED)
         {
            nThreshold = Tsens_CheckThreshold(pSensorCfg->nThresholdMaxDeciDegC);
            HAL_tsens_srot_SetThreshold(pucTsensSROTAddr, uChannel, HAL_TSENS_TH_MAX, nThreshold);
            HAL_tsens_srot_EnableInterrupt(pucTsensSROTAddr, uChannel, HAL_TSENS_TH_MAX);
         }
         else
         {
            HAL_tsens_srot_SetThreshold(pucTsensSROTAddr, uChannel, HAL_TSENS_TH_MAX, nThresholdMax);
            HAL_tsens_srot_DisableInterrupt(pucTsensSROTAddr, uChannel, HAL_TSENS_TH_MAX);
         }
      }
   }

   /* Enable / Disable TM thresholds */
   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      pController = &gTsensDevCtxt.paControllers[uController];
      pucTsensTMAddr = pController->pucTsensTMAddr;

      HAL_tsens_tm_SetInterruptEn(pucTsensTMAddr, pController->uLowerEnableMask, HAL_TSENS_TH_LOWER);
      HAL_tsens_tm_SetInterruptEn(pucTsensTMAddr, pController->uUpperEnableMask, HAL_TSENS_TH_UPPER);
      HAL_tsens_tm_SetInterruptEn(pucTsensTMAddr, pController->uCriticalEnableMask, HAL_TSENS_TH_CRITICAL);

      if ((pController->uLowerEnableMask | pController->uUpperEnableMask) != 0)
      {
         HAL_tsens_tm_EnableUpperLowerInterrupt(pucTsensTMAddr);
      }
      else
      {
         HAL_tsens_tm_DisableUpperLowerInterrupt(pucTsensTMAddr);
      }

      if (pController->uCriticalEnableMask != 0)
      {
         HAL_tsens_tm_EnableCriticalInterrupt(pucTsensTMAddr);
      }
      else
      {
         HAL_tsens_tm_DisableCriticalInterrupt(pucTsensTMAddr);
      }
   }

   return TSENS_SUCCESS;
}

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
TsensResultType Tsens_Init(uint64_t controller_mask)
{
   const TsensControllerCfgType *pControllerCfg;
   const TsensBspType *pBsp;
   TsensControllerType *pController;
   TsensResultType result;
   uint32_t uController;

   /* allocate address */
   pBsp = TsensBsp;
   gTsensDevCtxt.pTsensBsp = pBsp;
   gTsensDevCtxt.paControllers = TsensController;

   /* Map physical to virtual addresses */
   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      //pBsp->paControllerCfgs与paControllers中uController ID一一对应
      pControllerCfg = &pBsp->paControllerCfgs[uController];
      pController = &gTsensDevCtxt.paControllers[uController];

      pController->pucTsensSROTAddr = Tsens_MapHWIORegion(pControllerCfg->pucTsensSROTPhys,
                                                          pControllerCfg->uTsensSROTSize);
      if (pController->pucTsensSROTAddr == NULL)
      {
         return TSENS_ERROR;
      }

      pController->pucTsensTMAddr = Tsens_MapHWIORegion(pControllerCfg->pucTsensTMPhys,
                                                        pControllerCfg->uTsensTMSize);
      if (pController->pucTsensSROTAddr == NULL)
      {
         return TSENS_ERROR;
      }
   }

   /* Get the controller version */
   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      pController = &gTsensDevCtxt.paControllers[uController];
      pController->uVersion = HAL_tsens_srot_GetControllerVersion(pController->pucTsensSROTAddr);
   }

   /* Obtain the max and min thresholds */
   gTsensDevCtxt.nThresholdMax = HAL_tsens_GetMaxTemp();
   gTsensDevCtxt.nThresholdMin = HAL_tsens_GetMinTemp();

   result = Tsens_GetCalibration();
   if (result != TSENS_SUCCESS)
   {
      return result;
   }

   result = Tsens_DisableControllers();
   if (result != TSENS_SUCCESS)
   {
      return result;
   }

   result = Tsens_ConfigureControllers();
   if (result != TSENS_SUCCESS)
   {
      return result;
   }

   result = Tsens_ConfigureSensors();
   if (result != TSENS_SUCCESS)
   {
      return result;
   }

   result = Tsens_EnableControllers(controller_mask);
   if (result != TSENS_SUCCESS)
   {
      return result;
   }

   result = Tsens_WaitForFirstRead();
   if (result != TSENS_SUCCESS)
   {
      return result;
   }

   gbTsensInitialized = true;

   return TSENS_SUCCESS;
}

TsensResultType Tsens_GetTemp(uint32_t uSensor)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   const TsensSensorCfgType *pSensorCfg;
   const TsensChannelType *pChannel;
   uint8_t *pucTsensTMAddr;
   uint8_t *pucTsensSROTAddr;
   int32_t nDeciDegC = 0;
   int32_t nDeciDegCTry1 = 0;
   int32_t nDeciDegCTryDec = 0;
   int32_t nDeciDegCTry2;
   int32_t nDeciDegCTry3;
   uint32_t bValid;
   uint32_t uController;
   uint32_t uChannel;

   if (gbTsensInitialized != true)
   {
      return TSENS_ERROR_NOT_INITIALIZED;
   }

   if (uSensor >= pBsp->uNumSensors)
   {
      return TSENS_ERROR;
   }

   /* find channel by sensor number */
   pSensorCfg = &pBsp->paSensorCfgs[uSensor];
   uController = pSensorCfg->uController;
   uChannel = pSensorCfg->uChannel;
   pChannel = &gTsensDevCtxt.paControllers[uController].aChannels[uChannel];
   pucTsensTMAddr = gTsensDevCtxt.paControllers[uController].pucTsensTMAddr;
   pucTsensSROTAddr = gTsensDevCtxt.paControllers[uController].pucTsensSROTAddr;

   if (pChannel->bChannelIsDead == true)
   {
      return TSENS_ERROR_SENSOR_NOT_AVAILABLE;
   }

   /* Read the ADC code and DEC code*/
   HAL_tsens_srot_SetResultFormat(pucTsensSROTAddr, HAL_TSENS_RESULT_TYPE_ADC_CODE);
   udelay(1000);
   HAL_tsens_tm_GetChannelPrevTemp(pucTsensTMAddr, uChannel, &nDeciDegCTryDec);
   printf(" %3d ", nDeciDegCTryDec);

   HAL_tsens_srot_SetResultFormat(pucTsensSROTAddr, HAL_TSENS_RESULT_TYPE_DECI_DEG_C);
   udelay(1000);
   bValid = HAL_tsens_tm_GetChannelPrevTemp(pucTsensTMAddr, uChannel, &nDeciDegCTry1);
   printf("  %3d ", nDeciDegCTry1);

   if (bValid == true)
   {
      nDeciDegC = nDeciDegCTry1;
   }
   else
   {
      HAL_tsens_srot_SetResultFormat(pucTsensSROTAddr, HAL_TSENS_RESULT_TYPE_DECI_DEG_C);
      bValid = HAL_tsens_tm_GetChannelPrevTemp(pucTsensTMAddr, uChannel, &nDeciDegCTry2);
      if (bValid == true)
      {
         nDeciDegC = nDeciDegCTry2;
      }
      else
      {
         HAL_tsens_srot_SetResultFormat(pucTsensSROTAddr, HAL_TSENS_RESULT_TYPE_DECI_DEG_C);
         bValid = HAL_tsens_tm_GetChannelPrevTemp(pucTsensTMAddr, uChannel, &nDeciDegCTry3);
         if (bValid == true)
         {
            nDeciDegC = nDeciDegCTry3;
         }
         else if (nDeciDegCTry1 == nDeciDegCTry2)
         {
            nDeciDegC = nDeciDegCTry1;
         }
         else if (nDeciDegCTry2 == nDeciDegCTry3)
         {
            nDeciDegC = nDeciDegCTry2;
         }
         else
         {
            nDeciDegC = nDeciDegCTry1;
         }
      }
   }

   gTsensDevCtxt.nLastTempDeciDegC = nDeciDegC;
   gTsensDevCtxt.uLastSensor = uSensor;

   return TSENS_SUCCESS;
}

TsensResultType Tsens_GetMaxTemp(int32_t *pnMaxDeciDegC)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   int32_t nMaxDeciDegC = 0;
   uint32_t bFirst = true;
   uint8_t *pucTsensTMAddr;
   uint32_t uController;
   int32_t nDeciDegC;
   uint32_t uSensorID;

   if (gbTsensInitialized != true)
   {
      return TSENS_ERROR_NOT_INITIALIZED;
   }

   for (uController = 0; uController < pBsp->uNumControllers; uController++)
   {
      pucTsensTMAddr = gTsensDevCtxt.paControllers[uController].pucTsensTMAddr;

      HAL_tsens_tm_GetMaxTemp(pucTsensTMAddr, &uSensorID, &nDeciDegC);

      if (bFirst == true)
      {
         nMaxDeciDegC = nDeciDegC;
         bFirst = false;
      }
      else
      {
         if (nDeciDegC > nMaxDeciDegC)
         {
            nMaxDeciDegC = nDeciDegC;
         }
      }
   }

   *pnMaxDeciDegC = nMaxDeciDegC;

   return TSENS_SUCCESS;
}

TsensResultType tsens_all_temp (void)
{
   const TsensBspType *pBsp = gTsensDevCtxt.pTsensBsp;
   int i;

   /* update sensors temp */
   printf("--------------------------------------------------------------------------------\n");
   printf("  Tsens | ADC | DEC | Tsens | ADC | DEC | Tsens | ADC | DEC | Tsens | ADC | DEC \n");
   printf("--------------------------------------------------------------------------------\n");
   for (i = 0; i < pBsp->uNumSensors; i++) {
        if(0 == (i % 4) && (0 != i)) {
            printf("\n");
        }
        printf("|  %2d   |", i);
        Tsens_GetTemp(i);
   }
   printf("\n--------------------------------------------------------------------------------\n");
   return TSENS_SUCCESS;
}

TsensResultType tsens_max_temp (void)
{
   TsensResultType dal_err;
   int32_t max_temp;
   /* Update MAX SOC temperature */
   dal_err = Tsens_GetMaxTemp(&max_temp);
   if (dal_err == TSENS_SUCCESS)
       printf(" Tsens MaxTemp: %d \n", max_temp);
   return TSENS_SUCCESS;
}

int tsens_fuses(void)
{
    const TsensBspType *pBsp = TsensBsp;
    const TsensSensorCfgType *pSensorCfg;
    HAL_tsens_Calibration eCalType;
    bool bUseRedundant;
    bool bPartialGoods;
    uint32_t bTestSecurity;
    uint32_t uSensor;
    uint32_t uController;
    uint32_t sController;
    const char* res[2] = {"false", "true"};
    const char* CalMode[4] = {"NOT CALIBRATED","","ONE POINT","TWO POINT"};

    bUseRedundant = HAL_tsens_UseRedundant();
    printf("UseRedundant:    %s\n",res[bUseRedundant]);
    eCalType = HAL_tsens_CalSelect(bUseRedundant);
    printf("CalibrateMode:   %s\n",CalMode[eCalType]);
    bTestSecurity = HAL_tsens_TestSecurity(bUseRedundant);
    printf("TestSecurity:    %x\n",bTestSecurity);
    bPartialGoods = HAL_tsens_PartialGoodsEnabled(bUseRedundant);
    printf("PartialGoods:    %x\n",bPartialGoods);
    printf("-----------------------------------------------------\n");
    printf("Controller | Base_30 | Base_120 | 0 1 2 3 4 5 6 7 8 9\n");
    printf("-----------------------------------------------------\n");
    for (uController = 0; uController < pBsp->uNumControllers; uController++) {
        /* Get the base points as applicable */
        printf("    %2d     |", uController);
        printf("   %d   |", (int32_t)HAL_tsens_GetBase1(bUseRedundant, uController));
        printf("    %d   |", (int32_t)HAL_tsens_GetBase2(bUseRedundant, uController));

        /* Get the cal data per sensor */
        for (uSensor = 0; uSensor < pBsp->uNumSensors; uSensor++) {
            pSensorCfg = &pBsp->paSensorCfgs[uSensor];
            sController = pSensorCfg->uController;
            if (sController == uController)
                printf(" %x", HAL_tsens_GetOffset1(bUseRedundant, pSensorCfg->uFuseIdx));
        }
        printf("\n");
    }
    printf("-----------------------------------------------------\n");

    return 0;
}

int tsens_threshold(TSENS_THRESHOLD_TYPE ThresholdType, int32_t ThresholdValue)
{
    TsensSensorCfgType *pSensorCfg = gaTsensSensorCfgs;
    uint32_t uSensor;
    for (uSensor = 0; uSensor < 99; uSensor++) {
        if (TSENS_MIN_THRESHOLD == ThresholdType) {
            pSensorCfg->nThresholdMinDeciDegC = ThresholdValue;
        } else if (TSENS_LOWER_THRESHOLD == ThresholdType) {
            pSensorCfg->nThresholdLowerDeciDegC = ThresholdValue;
        } else if (TSENS_CRITICAL_THRESHOLD == ThresholdType) {
            pSensorCfg->nThresholdCriticalDeciDegC = ThresholdValue;
        } else if (TSENS_UPPER_THRESHOLD == ThresholdType) {
            pSensorCfg->nThresholdUpperDeciDegC = ThresholdValue;
        } else if (TSENS_MAX_THRESHOLD == ThresholdType) {
            pSensorCfg->nThresholdMaxDeciDegC = ThresholdValue;
        } else {
            printf("Wrong Threshold Type: %d\n", ThresholdType);
            return -1;
        }
        pSensorCfg++;
    }
    return 0;
}

int do_tsens(int argc, char *argv[])
{
    int i, ret = 0;
    uint64_t contoller_mask = 0;

    if (argc == 1) {
        printf("Unknown command '%s'\n\n", argv[0]);
    }else {
        if (strcmp(argv[1], "init") == 0) {
            for(i = 2; i < argc; i++) {
                if (strtoul(argv[i], NULL, 0) > 0 && strtoul(argv[i], NULL, 0) < 12) {
                    contoller_mask |= contoller2mask(strtoul(argv[i], NULL, 0)-1);
                }
            }
            if (contoller_mask){
                Tsens_Init(contoller_mask);
            } else {
                Tsens_Init(0x7FF);
            }
            printf(" Controllers and Tsens are Init! \n");
        } else if (strcmp(argv[1], "all") == 0) {
            tsens_all_temp();
        } else if (strcmp(argv[1], "max") == 0) {
            tsens_max_temp();
        } else if (strcmp(argv[1], "fuse") == 0) {
            tsens_fuses();
        } else if (strcmp(argv[1], "pwm") == 0) {
            MaxTempOverGpioAsPWM();
        } else if (strcmp(argv[1], "T") == 0) {
            TSENS_THRESHOLD_TYPE ThresholdType = TSENS_UNKNOW_THRESHOLD;
            int32_t ThresholdValue = 0;
            if (strcmp(argv[2], "MIN") == 0) {
                ThresholdType = TSENS_MIN_THRESHOLD;
            } else if (strcmp(argv[2], "LOWER") == 0) {
                ThresholdType = TSENS_LOWER_THRESHOLD;
            } else if (strcmp(argv[2], "CRITICAL") == 0) {
                ThresholdType = TSENS_CRITICAL_THRESHOLD;
            } else if (strcmp(argv[2], "UPPER") == 0) {
                ThresholdType = TSENS_UPPER_THRESHOLD;
            } else if (strcmp(argv[2], "MAX") == 0) {
                ThresholdType = TSENS_MAX_THRESHOLD;
            } else {
                ThresholdType = TSENS_UNKNOW_THRESHOLD;
            }
            if (argv[3]) {
                ThresholdValue = strtoul(argv[3], NULL, 0);
                if (ThresholdValue > MinThreshold && ThresholdValue < MaxThreshold) {
                    ret = tsens_threshold(ThresholdType, ThresholdValue*10);
                    if (ret == 0) {
                        printf("Success, Set %s Threshold is %dC\n", argv[2], ThresholdValue);
                    }
                } else {
                    printf("Failed, Threshold Value is from %dC to %dC\n", MinThreshold, MaxThreshold);
                }
            } else {
                printf("Failed, Threshold value must be provided!\n");
                ret = -1;
            }
        } else if (strtoul(argv[1], NULL, 0) < 99) {
            Tsens_GetTemp(strtoul(argv[1], NULL, 0));
            printf("\n");
        } else {
            printf("Unknown command '%s'\n\n", argv[1]);
            ret = -1;
        }
    }
    return ret;
}

MK_CMD(tsens, do_tsens, "configure controllers and sensors before get temperature",
    "\n"
    "tsens T {MIN|LOWER|CRITICAL|UPPER|MAX} <-50-150>\n"
    "  -set tsens {MIN|LOWER|CRITICAL|UPPER|MAX} Threshold from -50 to 150\n"
    "  -this command will work after tsens init finishs\n"
    "tsens init [1-11]\n"
    "  -configure [1-11] controller and sensors(default init all contollers)\n"
    "tsens <0-99>\n"
    "  -read temprature of [0-99] sensors\n"
    "tsens all\n"
    "  -read temprature of 99 sensors\n"
    "tsens max\n"
    "  -read max temprature in all alive sensors\n"
    "tsens fuse\n"
    "  -read tsens fuses\n"
);
