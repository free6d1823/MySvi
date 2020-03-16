/*============================================================================
  FILE:         TsensBsp.c

  OVERVIEW:     BSP for Tsens.

  DEPENDENCIES: None

                Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/
/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <asm/mach-qdf2400/tsens/TsensBsp.h>
//#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
#define ARRAY_LENGTH(a) (sizeof(a) / sizeof((a)[0]))

/* Thresholds */
#define TSENS_THRESHOLD_MIN       -350
#define TSENS_THRESHOLD_LOWER     TSENS_THRESHOLD_DISABLED
#define TSENS_THRESHOLD_UPPER     TSENS_THRESHOLD_DISABLED
#define TSENS_THRESHOLD_CRITICAL  950
#define TSENS_THRESHOLD_MAX       1200

/* Calibration points */
#define POINT_1_DECI_DEG_C 300
#define POINT_2_DECI_DEG_C 1200

/* Default calibration values */
#define INTERPOLATE_FOR_Y(m,x,x1,y1) (((m) * ((x) - (x1))) + (y1))
#define CODE_PER_DECI_DEG_C 0.312
#define POINT_1_CODE 456
#define POINT_2_CODE (INTERPOLATE_FOR_Y(CODE_PER_DECI_DEG_C, POINT_2_DECI_DEG_C, POINT_1_DECI_DEG_C, POINT_1_CODE))

#if defined(USE_ANALOG_SENSOR_MODEL) && defined(CONFIG_TESTOS_EMU)
  /* On Rumi we do not have real sensors, so we can use the TS_CONFIG and
   * TS_CONTROL to enable the analog model for Tsens sensors. The below
   * configuration results in sensors on the same controller repoting
   * temperature in incresing order
   * Sensor 0 -> lowest temp & Sensor15 -> highest temp
   *
   * Using same values as real sensors on RUMI results in behavior where valid
   * bit will never get set and reported temperature(from GetTemp) will be 0
   */
  #define TS_CONTROL_VALUE 0x000001C2
  #define TS_CONFIG_VALUE 0x00
#else
  /* Real TS_CONFIG and TS_CONTROL values for actual sensors */
  #define TS_CONTROL_VALUE 0x01803020
  #define TS_CONFIG_VALUE 0x4B
#endif

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/
const TsensControllerCfgType gaTsensControllerCfgs[] =
{
   /* Controller 1 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS1_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS1_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS1_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS1_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 2 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS2_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS2_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS2_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS2_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 3 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS3_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS3_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS3_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS3_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 4 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS4_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS4_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS4_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS4_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 5 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS5_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS5_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS5_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS5_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 6 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS6_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS6_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS6_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS6_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 7 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS7_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS7_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS7_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS7_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 8 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS8_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS8_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS8_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS8_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 9 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS9_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS9_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS9_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS9_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 10 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = true,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)TS10_TSENS_SROT_REG_BASE_PHYS,
      .uTsensSROTSize     = TS10_TSENS_SROT_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)TS10_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = TS10_TSENS_TM_REG_BASE_SIZE
   },

   /* Controller 11 */
   {
      .bPSHoldResetEn     = true,
      .uPeriodActive      = 0,
      .uPeriodSleep       = 0,
      .bAutoAdjustPeriod  = false,
      .uTSControl         = TS_CONTROL_VALUE,
      .uTSConfig          = TS_CONFIG_VALUE,
      .bStandAlone        = false,
      .uSidebandEnMask    = 0xFFFF,
      .bPWMEn             = false,
      .pucTsensSROTPhys   = (uint8_t *)MPM_TSENS_REG_BASE_PHYS,
      .uTsensSROTSize     = MPM_TSENS_REG_BASE_SIZE,
      .pucTsensTMPhys     = (uint8_t *)MPM_TSENS_TM_REG_BASE_PHYS,
      .uTsensTMSize       = MPM_TSENS_TM_REG_BASE_SIZE
   },
};

TsensSensorCfgType gaTsensSensorCfgs[] =
{
   /* Sensor 0 */
   {
      .uController                 = 0,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 0,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 1 */
   {
      .uController                 = 0,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 1,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 2 */
   {
      .uController                 = 0,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 2,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 3 */
   {
      .uController                 = 0,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 3,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 4 */
   {
      .uController                 = 0,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 4,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 5 */
   {
      .uController                 = 0,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 5,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 6 */
   {
      .uController                 = 0,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 6,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 7 */
   {
      .uController                 = 0,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 7,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 8 */
   {
      .uController                 = 0,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 8,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 9 */
   {
      .uController                 = 0,
      .uChannel                    = 9,
      .uSensorID                   = 9,
      .uFuseIdx                    = 9,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 10 is unused */

   /* Sensor 10 */
   {
      .uController                 = 1,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 11,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 11 */
   {
      .uController                 = 1,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 12,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 12 */
   {
      .uController                 = 1,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 13,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 13 */
   {
      .uController                 = 1,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 14,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 14 */
   {
      .uController                 = 1,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 15,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 15 */
   {
      .uController                 = 1,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 16,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 16 */
   {
      .uController                 = 1,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 17,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 17 */
   {
      .uController                 = 1,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 18,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 18 */
   {
      .uController                 = 1,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 19,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 19 */
   {
      .uController                 = 1,
      .uChannel                    = 9,
      .uSensorID                   = 9,
      .uFuseIdx                    = 20,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 21 is unused*/

   /* Sensor 20 */
   {
      .uController                 = 2,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 22,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 21 */
   {
      .uController                 = 2,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 23,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 22 */
   {
      .uController                 = 2,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 24,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 23 */
   {
      .uController                 = 2,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 25,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 24 */
   {
      .uController                 = 2,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 26,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 25 */
   {
      .uController                 = 2,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 27,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 26 */
   {
      .uController                 = 2,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 28,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 27 */
   {
      .uController                 = 2,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 29,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 28 */
   {
      .uController                 = 2,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 30,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 29 */
   {
      .uController                 = 2,
      .uChannel                    = 9,
      .uSensorID                   = 9,
      .uFuseIdx                    = 31,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 32 unused */

   /* Sensor 30 */
   {
      .uController                 = 3,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 33,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 31 */
   {
      .uController                 = 3,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 34,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 32 */
   {
      .uController                 = 3,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 35,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 33 */
   {
      .uController                 = 3,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 36,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 34 */
   {
      .uController                 = 3,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 37,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 35 */
   {
      .uController                 = 3,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 38,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 36 */
   {
      .uController                 = 3,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 39,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 37 */
   {
      .uController                 = 3,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 40,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 38 */
   {
      .uController                 = 3,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 41,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 42, 43 unused */

   /* Sensor 39 */
   {
      .uController                 = 4,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 44,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 40 */
   {
      .uController                 = 4,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 45,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 41 */
   {
      .uController                 = 4,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 46,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 42 */
   {
      .uController                 = 4,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 47,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 43 */
   {
      .uController                 = 4,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 48,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 44 */
   {
      .uController                 = 4,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 49,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 45 */
   {
      .uController                 = 4,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 50,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 46 */
   {
      .uController                 = 4,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 51,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 47 */
   {
      .uController                 = 4,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 52,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 48 */
   {
      .uController                 = 4,
      .uChannel                    = 9,
      .uSensorID                   = 9,
      .uFuseIdx                    = 53,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 54 unused */

   /* Sensor 49 */
   {
      .uController                 = 5,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 55,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 50 */
   {
      .uController                 = 5,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 56,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 51 */
   {
      .uController                 = 5,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 57,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 52 */
   {
      .uController                 = 5,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 58,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 53 */
   {
      .uController                 = 5,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 59,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 54 */
   {
      .uController                 = 5,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 60,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 55 */
   {
      .uController                 = 5,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 61,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 56 */
   {
      .uController                 = 5,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 62,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 57 */
   {
      .uController                 = 5,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 63,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 58 */
   {
      .uController                 = 5,
      .uChannel                    = 9,
      .uSensorID                   = 9,
      .uFuseIdx                    = 64,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 65 unused */

   /* Sensor 59 */
   {
      .uController                 = 6,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 66,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 60 */
   {
      .uController                 = 6,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 67,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 61 */
   {
      .uController                 = 6,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 68,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 62 */
   {
      .uController                 = 6,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 69,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 63 */
   {
      .uController                 = 6,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 70,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 64 */
   {
      .uController                 = 6,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 71,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 65 */
   {
      .uController                 = 6,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 72,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 66 */
   {
      .uController                 = 6,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 73,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 67 */
   {
      .uController                 = 6,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 74,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 68 */
   {
      .uController                 = 6,
      .uChannel                    = 9,
      .uSensorID                   = 9,
      .uFuseIdx                    = 75,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 76 unused */

   /* Sensor 69 */
   {
      .uController                 = 7,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 77,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 70 */
   {
      .uController                 = 7,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 78,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 71 */
   {
      .uController                 = 7,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 79,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 72 */
   {
      .uController                 = 7,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 80,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 73 */
   {
      .uController                 = 7,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 81,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 74 */
   {
      .uController                 = 7,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 82,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 75 */
   {
      .uController                 = 7,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 83,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 76 */
   {
      .uController                 = 7,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 84,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 77 */
   {
      .uController                 = 7,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 85,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 78 */
   {
      .uController                 = 7,
      .uChannel                    = 9,
      .uSensorID                   = 9,
      .uFuseIdx                    = 86,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* fuseidx 87 unused */
   /* Sensor 79 */
   {
      .uController                 = 8,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 88,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 80 */
   {
      .uController                 = 8,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 89,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 81 */
   {
      .uController                 = 8,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 90,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 82 */
   {
      .uController                 = 8,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 91,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 83 */
   {
      .uController                 = 8,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 92,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 84 */
   {
      .uController                 = 8,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 93,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 85 */
   {
      .uController                 = 8,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 94,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 86 */
   {
      .uController                 = 8,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 95,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 87 */
   {
      .uController                 = 8,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 96,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 97, 98 unused */

   /* Sensor 88 */
   {
      .uController                 = 9,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 99,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },


   /* Sensor 89 */
   {
      .uController                 = 9,
      .uChannel                    = 1,
      .uSensorID                   = 1,
      .uFuseIdx                    = 100,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 90 */
   {
      .uController                 = 9,
      .uChannel                    = 2,
      .uSensorID                   = 2,
      .uFuseIdx                    = 101,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 91 */
   {
      .uController                 = 9,
      .uChannel                    = 3,
      .uSensorID                   = 3,
      .uFuseIdx                    = 102,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 92 */
   {
      .uController                 = 9,
      .uChannel                    = 4,
      .uSensorID                   = 4,
      .uFuseIdx                    = 103,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 93 */
   {
      .uController                 = 9,
      .uChannel                    = 5,
      .uSensorID                   = 5,
      .uFuseIdx                    = 104,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 94 */
   {
      .uController                 = 9,
      .uChannel                    = 6,
      .uSensorID                   = 6,
      .uFuseIdx                    = 105,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 95 */
   {
      .uController                 = 9,
      .uChannel                    = 7,
      .uSensorID                   = 7,
      .uFuseIdx                    = 106,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 96 */
   {
      .uController                 = 9,
      .uChannel                    = 8,
      .uSensorID                   = 8,
      .uFuseIdx                    = 107,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },

   /* Sensor 97 */
   {
      .uController                 = 9,
      .uChannel                    = 9,
      .uSensorID                   = 9,
      .uFuseIdx                    = 108,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   },
   /* FuseIdx 109 unused */

   /* Sensor 98 */
   {
      .uController                 = 10,
      .uChannel                    = 0,
      .uSensorID                   = 0,
      .uFuseIdx                    = 110,
      .eCal                        = TSENS_BSP_SENSOR_CAL_NORMAL,
      .nCalPoint1CodeDefault       = POINT_1_CODE,
      .nCalPoint2CodeDefault       = (int32_t)POINT_2_CODE,
      .nThresholdMinDeciDegC       = TSENS_THRESHOLD_MIN,
      .nThresholdLowerDeciDegC     = TSENS_THRESHOLD_LOWER,
      .nThresholdUpperDeciDegC     = TSENS_THRESHOLD_UPPER,
      .nThresholdCriticalDeciDegC  = TSENS_THRESHOLD_CRITICAL,
      .nThresholdMaxDeciDegC       = TSENS_THRESHOLD_MAX
   }
   /* All fuseIdx(111 till 120) are unused as there are no remote sensors */
};

const TsensBspType TsensBsp[] =
{
   {
      .paControllerCfgs    = gaTsensControllerCfgs,
      .uNumControllers     = ARRAY_LENGTH(gaTsensControllerCfgs),
      .paSensorCfgs        = gaTsensSensorCfgs,
      .uNumSensors         = ARRAY_LENGTH(gaTsensSensorCfgs),
      .uSensorConvTime_us  = 170,
      .nCalPoint1DeciDegC  = POINT_1_DECI_DEG_C,
      .nCalPoint2DeciDegC  = POINT_2_DECI_DEG_C,
      .uShift              = 10
   }
};

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/

