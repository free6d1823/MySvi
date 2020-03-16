#ifndef __TSENS_BSP_H__
#define __TSENS_BSP_H__
/*============================================================================
  @file TsensBsp.h

  Tsens BSP file.

                Copyright (c) 2014-2015 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/
/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
#define TSENS_THRESHOLD_DISABLED 0x7fffffff
#define TSENS_MAX_NUM_CHANNELS_PER_CONTROLLER 16
#define TSENS_MAX_NUM_TBCB_CLIENTS_PER_CONTROLLER 16
#define THERMAL_ZONE_TSENS_PER_CPU          1
#define THERMAL_ZONE_CPU_START_IDX         (0)
#define PLATFORM_RAIL_COUNT                 8
#define PLATFORM_CLUSTERS_PER_RAIL          3
#define PLATFORM_CORES_PER_CLUSTER          2
#define PLATFORM_CORES_PER_RAIL             (PLATFORM_CLUSTERS_PER_RAIL * PLATFORM_CORES_PER_CLUSTER)
#define PLATFORM_CLUSTER_COUNT              (PLATFORM_RAIL_COUNT * PLATFORM_CLUSTERS_PER_RAIL)
#define PLATFORM_CORE_COUNT                 (PLATFORM_CLUSTER_COUNT * PLATFORM_CORES_PER_CLUSTER)
#define SUCCESS                             0
#define INT32_MIN                           (-1-0x7fffffff)

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
//#include "DALStdDef.h"
//#include "com_dtypes.h"
#include <stdint.h>
#include "thermal_combiner_hwio.h"

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/
typedef enum
{
   TSENS_BSP_SENSOR_CAL_NORMAL = 0,        /* Normal method, i.e. use QFPROM if
                                            * avail else use default char data */
   TSENS_BSP_SENSOR_CAL_IGNORE_DEVICE_CAL  /* Force using default char data */
} TsensBspSensorCalType;

typedef struct
{
   uint32_t bPSHoldResetEn;     /* Whether to enable PS_HOLD reset */
   uint32_t uPeriodActive;       /* Active period */
   uint32_t uPeriodSleep;        /* Sleep period */
   uint32_t bAutoAdjustPeriod;  /* Whether to adjust period on sleep */
   uint32_t uTSControl;          /* Analog TS control setting */
   uint32_t uTSConfig;           /* Analog TS config setting */
   uint32_t bStandAlone;        /* Whether this is a stand alone controller */
   uint32_t uSidebandEnMask;     /* Mask of sideband sensors to enable */
   uint32_t bPWMEn;             /* Whether to enable PWM */
   uint8_t *pucTsensSROTPhys;    /* SROT region physical base address */
   uint32_t uTsensSROTSize;      /* Size of SROT region */
   uint8_t *pucTsensTMPhys;      /* TM region physical base address */
   uint32_t uTsensTMSize;        /* Size of TM region */
} TsensControllerCfgType;

typedef struct
{
   uint32_t uController;                /* Controller index */
   uint32_t uChannel;                   /* Channel index */
   uint32_t uSensorID;                  /* Sensor ID for TBCB */
   uint32_t uFuseIdx;                   /* Which fuse corresponds to this sensor */
   TsensBspSensorCalType eCal;        /* Which cal type to use */
   int32_t nCalPoint1CodeDefault;       /* Default TSENS code at calibration point nCalPoint1DeciDegC */
   int32_t nCalPoint2CodeDefault;       /* Default TSENS code at calibration point nCalPoint2DeciDegC */
   int32_t nThresholdMinDeciDegC;       /* Minimum temperature threshold for critical shutdown
                                       * or use TSENS_THRESHOLD_DISABLED to disable */
   int32_t nThresholdLowerDeciDegC;     /* Default lower threshold for software interrupt or
                                       * or use TSENS_THRESHOLD_DISABLED to disable */
   int32_t nThresholdUpperDeciDegC;     /* Default upper threshold for software interrupt or
                                       * or use TSENS_THRESHOLD_DISABLED to disable */
   int32_t nThresholdCriticalDeciDegC;  /* Default critical threshold for software interrupt or
                                       * use TSENS_THRESHOLD_DISABLED to disable */
   int32_t nThresholdMaxDeciDegC;       /* Maximum temperature threshold for critical shutdown
                                       * or use TSENS_THRESHOLD_DISABLED to disable */
} TsensSensorCfgType;

typedef struct
{
   const TsensControllerCfgType *paControllerCfgs;  /* Array of controller configs */
   uint32_t uNumControllers;                          /* Number of controllers */
   const TsensSensorCfgType *paSensorCfgs;          /* Array of sensor configs */
   uint32_t uNumSensors;                              /* Number of sensors */
   uint32_t uSensorConvTime_us;                       /* Sensor conversion time in us */
   int32_t nCalPoint1DeciDegC;                        /* Calibration point 1 in deci deg C */
   int32_t nCalPoint2DeciDegC;                        /* Calibration point 2 in deci deg C */
   uint32_t uShift;                                   /* Shift value */
} TsensBspType;

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
typedef enum
{
   TSENS_SUCCESS,
   TSENS_ERROR,
   TSENS_ERROR_INVALID_CALIBRATION,
   TSENS_ERROR_TIMEOUT,
   TSENS_ERROR_NOT_INITIALIZED,
   TSENS_ERROR_SENSOR_NOT_AVAILABLE
} TsensResultType;

#endif /* #ifndef __TSENS_BSP_H__ */

