#ifndef __HAL_TSENS_H__
#define __HAL_TSENS_H__
/*============================================================================
  @file HALtsens.h

  This is the internal hardware abstraction layer for Tsens

                Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/
/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
//#include "com_dtypes.h"     /* Definitions for byte, word, etc.     */
#include <stdbool.h>
#include <stdint.h>

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef enum
{
   HAL_TSENS_TH_LOWER,
   HAL_TSENS_TH_UPPER,
   HAL_TSENS_TH_CRITICAL,
} HAL_tsens_tm_Threshold;

typedef enum
{
   HAL_TSENS_TH_MIN,
   HAL_TSENS_TH_MAX,
} HAL_tsens_srot_Threshold;

typedef enum
{
   HAL_TSENS_INTERNAL,
   HAL_TSENS_EXTERNAL,
} HAL_tsens_srot_ADCClkSrc;

typedef enum
{
   HAL_TSENS_DISABLE,
   HAL_TSENS_ENABLE
} HAL_tsens_srot_State;

typedef enum
{
   HAL_TSENS_RESULT_TYPE_ADC_CODE,
   HAL_TSENS_RESULT_TYPE_DECI_DEG_C,
} HAL_tsens_srot_ResultType;

typedef enum
{
   HAL_TSENS_CAL_NOT_CALIBRATED = 0,
   HAL_TSENS_CAL_ONE_POINT      = 2,
   HAL_TSENS_CAL_TWO_POINT      = 3,
} HAL_tsens_Calibration;

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Get temperature measurement - TM
 * -------------------------------------------------------------------------*/
bool HAL_tsens_tm_GetChannelPrevTemp(uint8_t *pucTsensTMAddr, uint32_t uChannel, int32_t *pnDeciDegC);
void HAL_tsens_tm_GetMaxTemp(uint8_t *pucTsensTMAddr, uint32_t *puSensorID, int32_t *pnMaxDeciDegC);

/*----------------------------------------------------------------------------
 * Interrupts - TM
 * -------------------------------------------------------------------------*/
void HAL_tsens_tm_EnableUpperLowerInterrupt(uint8_t *pucTsensTMAddr);
void HAL_tsens_tm_DisableUpperLowerInterrupt(uint8_t *pucTsensTMAddr);
void HAL_tsens_tm_EnableCriticalInterrupt(uint8_t *pucTsensTMAddr);
void HAL_tsens_tm_DisableCriticalInterrupt(uint8_t *pucTsensTMAddr);
void HAL_tsens_tm_SetInterruptEn(uint8_t *pucTsensTMAddr, uint32_t uChannelEnMask, HAL_tsens_tm_Threshold eThreshold);

/*----------------------------------------------------------------------------
 * Interrupts - SROT
 * -------------------------------------------------------------------------*/
void HAL_tsens_srot_EnableInterrupt(uint8_t *pucTsensSROTAddr, uint32_t uChannel, HAL_tsens_srot_Threshold eThreshold);
void HAL_tsens_srot_DisableInterrupt(uint8_t *pucTsensSROTAddr, uint32_t uChannel, HAL_tsens_srot_Threshold eThreshold);

/*----------------------------------------------------------------------------
 * Thresholds
 * -------------------------------------------------------------------------*/
int32_t HAL_tsens_GetMaxTemp(void);
int32_t HAL_tsens_GetMinTemp(void);

/*----------------------------------------------------------------------------
 * Thresholds - TM
 * -------------------------------------------------------------------------*/
void HAL_tsens_tm_SetThreshold(uint8_t *pucTsensTMAddr, uint32_t uChannel, HAL_tsens_tm_Threshold eThreshold, int32_t nThreshold);

/*----------------------------------------------------------------------------
 * Thresholds - SROT
 * -------------------------------------------------------------------------*/
void HAL_tsens_srot_SetThreshold(uint8_t *pucTsensSROTAddr, uint32_t uChannel, HAL_tsens_srot_Threshold eThreshold, int32_t nThreshold);

/*----------------------------------------------------------------------------
 * Measurement period - SROT
 * -------------------------------------------------------------------------*/
void HAL_tsens_srot_SetPeriodActive(uint8_t *pucTsensSROTAddr, uint32_t uTime);
void HAL_tsens_srot_SetPeriodSleep(uint8_t *pucTsensSROTAddr, uint32_t uTime);
void HAL_tsens_srot_SetAutoAdjustPeriodEn(uint8_t *pucTsensSROTAddr, bool bEnable);

/*----------------------------------------------------------------------------
 * Channel enable / disable - SROT
 * -------------------------------------------------------------------------*/
void HAL_tsens_srot_SetChannelsEnabled(uint8_t *pucTsensSROTAddr, uint32_t uChannelEnMask);

/*----------------------------------------------------------------------------
 * Main enable / disable - SROT
 * -------------------------------------------------------------------------*/
void HAL_tsens_srot_SetState(uint8_t *pucTsensSROTAddr, HAL_tsens_srot_State eTsensState);

/*----------------------------------------------------------------------------
 * Software reset - SROT
 * -------------------------------------------------------------------------*/
void HAL_tsens_srot_Reset(uint8_t *pucTsensSROTAddr);

/*----------------------------------------------------------------------------
 * Config - SROT
 * -------------------------------------------------------------------------*/
uint32_t HAL_tsens_srot_GetControllerVersion(uint8_t *pucTsensSROTAddr);
void HAL_tsens_srot_SetPSHoldResetEn(uint8_t *pucTsensSROTAddr, bool bEnable);
void HAL_tsens_srot_SetResultFormat(uint8_t *pucTsensSROTAddr, HAL_tsens_srot_ResultType eResultType);
void HAL_tsens_srot_SelectADCClkSrc(uint8_t *pucTsensSROTAddr, HAL_tsens_srot_ADCClkSrc eADCClkSrc);
void HAL_tsens_srot_SetConversionFactors(uint8_t *pucTsensSROTAddr, uint32_t uChannel, uint32_t uShift, uint32_t uShiftedSlope, uint32_t uCodeAtZero);
void HAL_tsens_srot_SetSensorID(uint8_t *pucTsensSROTAddr, uint32_t uChannel, uint32_t uSensorID);
void HAL_tsens_srot_SetAnalogParameters(uint8_t *pucTsensSROTAddr, uint32_t uControl, uint32_t uConfig);
void HAL_tsens_srot_SetPWMEn(uint8_t *pucTsensSROTAddr, bool bEnable);

/*----------------------------------------------------------------------------
 * LMh - SROT
 * -------------------------------------------------------------------------*/
void HAL_tsens_srot_SetSidebandChannelsEnabled(uint8_t *pucTsensSROTAddr, uint32_t uChannelEnMask);

/*----------------------------------------------------------------------------
 * Char data
 * -------------------------------------------------------------------------*/
bool HAL_tsens_UseRedundant(void);
HAL_tsens_Calibration HAL_tsens_CalSelect(bool bUseRedundant);
bool HAL_tsens_PartialGoodsEnabled(bool bUseRedundant);
uint32_t HAL_tsens_GetBase1(bool bUseRedundant, uint32_t uController);
uint32_t HAL_tsens_GetBase2(bool bUseRedundant, uint32_t uController);
uint32_t HAL_tsens_GetOffset1(bool bUseRedundant, uint32_t uFuseIdx);
uint32_t HAL_tsens_TestSecurity(bool bUseRedundant);
#endif /* #ifndef __HAL_TSENS_H__ */

