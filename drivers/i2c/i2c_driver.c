#include <stdlib.h>
#include <target/i2c.h>

void i2c_init()
{
    // Needed for RCINIT to be happy. Does nothing.
    return;
}

static I2CDEVQUP_Device qupDev[I2C_NUM_DEVICES];

I2cResult I2C_Attach (I2cDevice dev)
{
    int32_t res = I2C_RES_SUCCESS;
    if (I2C_NUM_DEVICES <= dev) return I2CDRV_ERR_INVALID_DEV_IDX;
    if(qupDev[dev].uOpenCount > 0)
    {
        return I2C_RES_SUCCESS;
    }

    qurt_pimutex_init(&qupDev[dev].pCritSectMutex);

    qupDev[dev].dev        = dev;
    qupDev[dev].uOpenCount = 0;

    res = I2CDEV_Init(&(qupDev[dev]));
    if ( I2C_RES_SUCCESS != res ) {
        //qurt_pimutex_destroy(&qupDev[dev].pCritSectMutex);
        return res;
    }

    return I2C_RES_SUCCESS;
}

I2cResult I2C_Detach (I2cDevice dev)
{
    int32_t res = I2C_RES_SUCCESS;
    if (I2C_NUM_DEVICES <= dev) return I2CDRV_ERR_INVALID_DEV_IDX;
    if(qupDev[dev].uOpenCount > 0)
    {
        return I2CPLATSVC_ERROR_DEVICE_IN_USE;
    }

    res = I2CDEV_DeInit(&qupDev[dev]);
    qurt_pimutex_destroy(&qupDev[dev].pCritSectMutex);
    return res;
}

I2cResult I2C_Open (I2cDevice  dev)
{
    int32_t res = I2C_RES_SUCCESS;
    if (I2C_NUM_DEVICES <= dev) return I2CDRV_ERR_INVALID_DEV_IDX;

    qurt_pimutex_lock(&qupDev[dev].pCritSectMutex);

    if ( qupDev[dev].uOpenCount == 0 )
    {
        res = I2CDEV_SetPowerState(&(qupDev[dev]), I2CDEV_POWER_STATE_2);
    }
    if ( I2C_RES_SUCCESS == res ) qupDev[dev].uOpenCount++;

    qurt_pimutex_unlock(&qupDev[dev].pCritSectMutex);

    return res;
}

I2cResult I2C_Close (I2cDevice dev)
{
    int32_t res = I2C_RES_SUCCESS;
    if (I2C_NUM_DEVICES <= dev) return I2CDRV_ERR_INVALID_DEV_IDX;

    // add accounting
    qurt_pimutex_lock(&qupDev[dev].pCritSectMutex);

    if( 1 == qupDev[dev].uOpenCount ) {
        res = I2CDEV_SetPowerState(&(qupDev[dev]), I2CDEV_POWER_STATE_0);
    }
    if( I2C_RES_SUCCESS == res ) qupDev[dev].uOpenCount--;

    qurt_pimutex_unlock(&qupDev[dev].pCritSectMutex);

    return res;
}

I2cResult I2C_Read
(
        I2cDevice        dev,
        I2cTransfer     *pTransfer,
        I2cClientConfig *pClntCfg,
        uint32_t          *puNumCompleted
 )
{
    I2cResult res;
    if (I2C_NUM_DEVICES <= dev) return I2CDRV_ERR_INVALID_DEV_IDX;
    if (NULL == pTransfer)      return I2CDRV_ERR_INVALID_TRANSFER_POINTER;
    if (NULL == puNumCompleted) return I2CDRV_ERR_INVALID_NUMCOMPLETED_POINTER;

    qurt_pimutex_lock(&qupDev[dev].pCritSectMutex);
    res = I2CDEV_Read(&(qupDev[dev]),
            pTransfer,
            pClntCfg,
            puNumCompleted);
    qurt_pimutex_unlock(&qupDev[dev].pCritSectMutex);
    return res;
}

I2cResult I2C_Write
(
        I2cDevice        dev,
        I2cTransfer     *pTransfer,
        I2cClientConfig *pClntCfg,
        uint32_t          *puNumCompleted
        )
{
    I2cResult res;
    if (I2C_NUM_DEVICES <= dev) return I2CDRV_ERR_INVALID_DEV_IDX;
    if (NULL == pTransfer)      return I2CDRV_ERR_INVALID_TRANSFER_POINTER;
    if (NULL == puNumCompleted) return I2CDRV_ERR_INVALID_NUMCOMPLETED_POINTER;
    qurt_pimutex_lock(&qupDev[dev].pCritSectMutex);
    res = I2CDEV_Write(&(qupDev[dev]),
            pTransfer,
            pClntCfg,
            puNumCompleted);
    qurt_pimutex_unlock(&qupDev[dev].pCritSectMutex);
    return res;
}

I2cResult I2C_BatchTransfer (
        I2cDevice        dev,
        I2cSequence     *pSequence,
        I2cClientConfig *pClntCfg,
        I2cIoResult     *pIoRes
        )
{
    I2cResult res;
    if (I2C_NUM_DEVICES <= dev) return I2CDRV_ERR_INVALID_DEV_IDX;
    if (NULL == pSequence)      return I2CDRV_ERR_INVALID_SEQUENCE_POINTER;
    if (NULL == pIoRes)         return I2CDRV_ERR_INVALID_NUMCOMPLETED_POINTER;
    qurt_pimutex_lock(&qupDev[dev].pCritSectMutex);
    res = I2CDEV_BatchTransfer(&(qupDev[dev]),
            pSequence,
            pClntCfg,
            pIoRes);
    qurt_pimutex_unlock(&qupDev[dev].pCritSectMutex);
    return res;
}

I2cResult I2C_Reset (
        I2cDevice        dev
        )
{
    if (I2C_NUM_DEVICES <= dev) return I2CDRV_ERR_INVALID_DEV_IDX;
    return I2CDEV_Reset(&(qupDev[dev]));
}

