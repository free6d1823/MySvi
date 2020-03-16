#ifndef I2CPLATSVC_H
#define I2CPLATSVC_H
/*=============================================================================

  @file   I2cPlatSvc.h

   This file contains the API for the platform services.

   Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
   All rights reserved.
   Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
   Copyright (c) 2011, 2016 Qualcomm Technologies, Inc.
   All Rights Reserved.
   Confidential and Proprietary - Qualcomm Technologies, Inc.

=============================================================================*/

#include "com_dtypes.h"
#include "busywait.h"
#include "I2cError.h"
#include "I2cConfig.h"
#include "I2cDevice.h"
#include "i2c_api.h"

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/

/** @brief Releases data structures necessary to support the target calls.

    @param[in] hPlatDev platform device handle.
  */
I2cResult
I2CPLATDEV_DeInitTarget
(
    I2CDEVQUP_Device *pDev
);

/** @brief Initializes data structures necessary to support the target calls.

    @param[in] uPlatDevId platform target id to platform device handle.
    @param[in] phPlatDev pointer to platform device handle.
  */
I2cResult
I2CPLATDEV_InitTarget
(
    I2CDEVQUP_Device *pDev
);

/** @brief Resets resources like bam pipes following a qup core reset.

    @param[in] hPlatDev platform device handle.
  */
I2cResult
I2CPLATDEV_ResetTarget
(
    I2CDEVQUP_Device *pDev
);

/** @brief Sets the power state of the device.

    @param[in] hPlatDev platform device handle.
    @param[in] state    new power state.
  */
I2cResult
I2CPLATDEV_SetPowerState
(
    I2CDEVQUP_Device *pDev,
    uint32_t            state
);

/** @brief Gets the power state of the device.

    @param[in]  hPlatDev platform device handle.
    @param[out] pState   pointer to state.
  */
I2cResult
I2CPLATDEV_GetPowerState
(
    I2CDEVQUP_Device *pDev,
    uint32_t           *pState
);

#endif /* #ifndef I2CPLATSVC_H */

