/*==============================================================================
#  Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
#  All rights reserved.
#  Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
#  Copyright (c) 2011-2014,2016 Qualcomm Technologies, Inc.
#  All Rights Reserved.
#  Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   I2cPlatSvc.c
 *  @Author CoreBSP(LK,MS)
 *  @brief  This file contains the implementation for the platform services.
 */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/
#include "I2cPlatSvc.h"
#include "com_dtypes.h"
#include "busywait.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
typedef enum I2CPLATDEV_PowerStates
{
    I2CPLATDEV_POWER_STATE_0,/**< Bus and clocks off. */
    I2CPLATDEV_POWER_STATE_1,/**< Bus on clocks off. */
    I2CPLATDEV_POWER_STATE_2,/**< Bus on clocks on. */
} I2CPLATDEV_PowerStates;

/*-------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * ----------------------------------------------------------------------*/
/** @brief Initializes the scl,sda gpios.

    @param[in] pDev     Pointer to platform device structure.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static I2cResult
I2CPLATDEV_InitGpios
(
    I2CDEVQUP_Device *pDev
)
{
    return I2C_RES_SUCCESS;
}

/** @brief Initializes the scl,sda gpios.

    @param[in] pDev     Pointer to platform device structure.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static I2cResult
I2CPLATDEV_DeInitGpios
(
    I2CDEVQUP_Device *pDev
)
{
    return I2C_RES_SUCCESS;
}

/** @brief Initializes the clocks for the qup core.

    @param[in] pDev     Pointer to platform device structure.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */


static I2cResult __attribute__ ((noinline))
I2CPLATDEV_InitClocks
(
    I2CDEVQUP_Device *pDev
)
{
    // Per-device clock initialization has been deprecated by the clock driver
    return I2C_RES_SUCCESS;
}

/** @brief Deinitializes the clocks for the qup core.

    @param[in] pDev     Pointer to platform device structure.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static I2cResult
I2CPLATDEV_DeInitClocks
(
    I2CDEVQUP_Device *pDev
)
{
    // Per-device clock initialization has been deprecated by the clock driver
    return I2C_RES_SUCCESS;
}

/** @brief Enables the clocks for the qup core.

    @param[in] pDev     Pointer to platform device structure.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static I2cResult __attribute__ ((noinline))
I2CPLATDEV_EnableClocks
(
    I2CDEVQUP_Device *pDev
)
{
    // Per-device clock initialization has been deprecated by the clock driver
    return I2C_RES_SUCCESS;
}

/** @brief Disables the clocks for the qup core.

    @param[in] pDev     Pointer to platform device structure.

    @return             I2C_RES_SUCCESS is successful, otherwise
                        I2CPLATSVC_Error.
  */
static I2cResult
I2CPLATDEV_DisableClocks
(
    I2CDEVQUP_Device *pDev
)
{
    // Per-device clock initialization has been deprecated by the clock driver
    return I2C_RES_SUCCESS;
}
/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/
I2cResult
I2CPLATDEV_SetPowerState
(
    I2CDEVQUP_Device *pDev,
    uint32_t            state
)
{
    int32_t res;
    if ( NULL == pDev ) return I2CPLATSVC_ERROR_NULL_POINTER;

    if ( I2CPLATDEV_POWER_STATE_0 == state ) {
        res = I2CPLATDEV_DisableClocks(pDev);
    }
    else if ( I2CPLATDEV_POWER_STATE_1 == state ) {
        res = I2CPLATDEV_DisableClocks(pDev); /*  bus state is powered. */
    }
    else if ( I2CPLATDEV_POWER_STATE_2 == state ) {
        res = I2CPLATDEV_EnableClocks(pDev); /* bus state is active. */
    }
    else {
        return I2CPLATSVC_ERROR_INVALID_POWER_STATE;
    }

    if ( I2C_RES_SUCCESS == res ) {
        pDev->tmpPowerState = state;
    }

    return res;
}

I2cResult
I2CPLATDEV_GetPowerState
(
    I2CDEVQUP_Device *pDev,
    uint32_t           *pState
)
{
    if ( NULL == pDev  || NULL == pState ) return I2CPLATSVC_ERROR_NULL_POINTER;
    *pState = pDev->tmpPowerState;
    return I2C_RES_SUCCESS;
}


I2cResult
I2CPLATDEV_InitTarget
(
   I2CDEVQUP_Device *pDev
)
{
    int32_t res;
    if ( NULL == pDev ) return I2CPLATSVC_ERROR_NULL_POINTER;

    pDev->config = i2c_get_device(pDev->dev);
    if ( NULL == pDev->config ) {
        return I2CPLATSVC_ERROR_INVALID_DEV_ID;
    }

    res = I2CPLATDEV_InitClocks(pDev);

    if ( I2C_RES_SUCCESS != res ) {
        return res;
    }

    res = I2CPLATDEV_InitGpios(pDev);
    if ( I2C_RES_SUCCESS != res ) {
        I2CPLATDEV_DeInitTarget(pDev);
    }
    return res;
}

I2cResult
I2CPLATDEV_DeInitTarget
(
    I2CDEVQUP_Device *pDev
)
{
    int32_t res ;
    if ( NULL == pDev ) return I2CPLATSVC_ERROR_NULL_POINTER;

    res  = I2CPLATDEV_DeInitClocks(pDev);
    I2CPLATDEV_DeInitGpios(pDev);

    return res;
}

