#ifndef __TARGET_I2C_H_INCLUDE__
#define __TARGET_I2C_H_INCLUDE__

#include <stdint.h>

#define I2C_ERR_CLS_MASK	0xF0000000

typedef enum  I2cResult {
	I2C_RES_SUCCESS = 0,
	/* Error Classes */
	/* I2C core error */
	I2C_RES_ERROR_CLS_I2C_CORE            = (int32_t)0x10000000,
	/* I2C_RES_ERROR_CLS_I2C_CORE errors can be disassembled as such:
	 *  (I2C_RES_ERROR_CLS_I2C_CORE | I2C_MASTER_STATUS & 0x0FFFFFFC )
	 */
	/* I2C transaction timeout error */
	I2C_RES_ERROR_CLS_QUP_DEV_TIMEOUT     = (int32_t)0x20000000,
	/* I2C qup core error */
	I2C_RES_ERROR_CLS_QUP_DEV             = (int32_t)0x30000000,
	I2CDEVQUP_ERR_IN_SEQ_OUT_OF_SYNC,
	I2CDEVQUP_ERR_INVALID_RUNSTATE,
	I2CDEVQUP_ERR_RUNSTATE_CHANGE_TIMEOUT,
	I2CDEVQUP_ERR_NEW_RUNSTATE_INVALID,
	I2CDEVQUP_ERR_INVALID_POWER_STATE,
	I2CDEVQUP_ERR_BUS_BUSY,
	I2CDEVQUP_ERR_BUS_NOT_RELEASED,
	I2CDEVQUP_ERR_BUS_CLK_NOT_FORCED_LOW,
	I2CDEVQUP_ERR_INPUT_DONE_TRANSFERS_NOT,
	I2CDEVQUP_ERR_INVALID_DEV_HANDLE,
	I2CDEVQUP_ERR_INVALID_TRANSFER_HANDLE,
	I2CDEVQUP_ERR_INVALID_TRANSFER_OBJPTR,
	I2CDEVQUP_ERR_INVALID_SEQUENCE_HANDLE,
	I2CDEVQUP_ERR_INVALID_SEQUENCE_OBJPTR,
	I2CDEVQUP_ERR_INVALID_TRANSFER_DIRECTION,
	I2CDEVQUP_ERR_OUT_OF_OUTPUT_TAG_BUFFER,
	I2CDEVQUP_ERR_INPUT_DESC_BUFFER_ALLOC_FAILED,
	I2CDEVQUP_ERR_PACKET_NACKED,
	I2CDEVQUP_ERR_NACK_IN_TRANSFER,
	I2CDEVQUP_ERR_UNEXPECTED_START_STOP,
	I2CDEVQUP_ERR_INVALID_WRITE,
	/* driver error class */
	/* I2C driver error */
	I2C_RES_ERROR_CLS_I2C_DRV             = (int32_t)0x40000000,
	I2CDRV_ERR_INVALID_DEV_IDX,
	I2CDRV_ERR_INVALID_TRANSFER_POINTER,
	I2CDRV_ERR_INVALID_SEQUENCE_POINTER,
	I2CDRV_ERR_INVALID_IO_RES_POINTER,
	I2CDRV_ERR_INVALID_NUMCOMPLETED_POINTER,
	I2CDRV_ERR_FAILED_TO_CREATE_MUTEX,
	/* I2C platform error */
	I2C_RES_ERROR_CLS_DEV_PLATFORM       = (int32_t)0xE0000000,
	I2CPLATSVC_ERROR_ATTACH_TO_CLOCKS,
	I2CPLATSVC_ERROR_DETACH_FROM_CLOCKS,
	I2CPLATSVC_ERROR_GETTING_APPCLK_ID,
	I2CPLATSVC_ERROR_GETTING_HCLK_ID,
	I2CPLATSVC_ERROR_INVALID_DEV_ID,
	I2CPLATSVC_ERROR_INVALID_POWER_STATE,
	I2CPLATSVC_ERROR_DEVICE_IN_USE,
	I2CPLATSVC_ERROR_MALLOC_FAILED,
	I2CPLATSVC_ERROR_NULL_POINTER,
	/* I2C os layer error */
	I2C_RES_ERROR_CLS_DEV_OS             = (int32_t)0xF0000000,
} I2cResult;

typedef struct I2cClientConfig {
	uint32_t uBusFreqKhz;
	/* I2C bus frequency */
	uint32_t uByteTransferTimeoutUs;
	/* I2C byte timeout.
	 * The transfer timeout will be calculated from this value.
	 */
} I2cClientConfig;

typedef struct I2cTransferConfig {
	uint32_t uSlaveAddr;
	/* Seven bit address isleft shifted and the r/w bit added by the
	 * driver.
	 */
} I2cTransferConfig;

typedef struct I2cBuffDesc {
	uint8_t *pBuff;		/* Virtual address of the buffer */
	uint32_t uBuffSize;	/* Size of the buffer in bytes */
} I2cBuffDesc;

typedef enum _eTranDirection {
	I2cTranDirIn,		/* input from device */
	I2cTranDirOut		/* going to the device, a write */
} I2cTranDirection;

typedef enum _eTranCtxt {
	I2cTrCtxNotASequence,	/* Transfer is not part of a sequence */
	I2cTrCtxSeqStart,	/* Transfer is the first in a sequence */
	I2cTrCtxSeqContinue,	/* Transfer constinues a started sequence */
	I2cTrCtxSeqEnd		/* Transfer ends the sequence */
} I2cTranCtxt ;

typedef struct I2cTransfer {
	I2cBuffDesc *pI2cBuffDesc;	/* IO Vec Buffer */
	uint32_t uTrSize;		/* Transfer total number of bytes */
	I2cTransferConfig tranCfg;	/* Transfer configuration */
	I2cTranDirection eTranDirection;/* Transfer direction */
	I2cTranCtxt eTranCtxt;		/* Transfer context */
	uint32_t uIsSmbus;		/* Is this a smbus command? */
	uint32_t uIsSmbusBlock;		/* Is this a smbus block command? */
	uint32_t uIsSmbusPEC;		/* Is this a PEC transfer? */
} I2cTransfer;

typedef struct I2cIoResult {
	int32_t nOperationResult;	/* This is the operation result */
	uint32_t uOutByteCnt;		/* This indicates num bytes sent */
	uint32_t uInByteCnt;		/* This indicates num bytes received */
} I2cIoResult;

typedef struct I2cSequence {
	I2cTransfer *pTransfer;		/* Pointer to array of transfers */
	uint32_t uNumTransfers;		/* Number of transfers in this sequence */
} I2cSequence;

#define NUM_I2C_GPIO		2
#define I2C_CONFIG_STR_SIZE	32
#define DAL_GPIO_VERSION 0x20000000

#ifndef IMC_BUILD
    #define APP_CLK_FRQ_KHZ 0
#else
    #if (DAL_CONFIG_TARGET_ID==0x2400)
        #define APP_CLK_FRQ_KHZ 50000
    #elif (DAL_CONFIG_TARGET_ID==0x2432)
        #define APP_CLK_FRQ_KHZ 20000
    #else
        #error "Undefined MSM_ID. Defaulting to 50MHz for APP_CLK_FREQ_KHZ"
        #define APP_CLK_FRQ_KHZ 50000
    #endif
#endif


#define DAL_GPIO_CFG(gpio, func, dir, pull, drive) \
         (((gpio) & 0x3FF)<< 4 | \
          ((func) & 0xF)|        \
          ((dir)  & 0x1) << 14|  \
          ((pull) & 0x3) << 15|  \
          ((drive)& 0xF) << 17| DAL_GPIO_VERSION)

typedef enum {
	LOG_ENABLED,
	LOG_DISABLED
} eLogEn;

typedef struct {
	uint32_t chipBusIdx;
	uint8_t *virtBlockAddr;
	uint32_t gpioCfgArr[NUM_I2C_GPIO];
	char swDeviceName[I2C_CONFIG_STR_SIZE];
	eLogEn logEnabled;
	uint32_t appClkFreqKhz;
	uint8_t usedInImc;
	uint8_t usedInXbl;
} i2c_config_t;

/**
 * Gets the soc configuration for the I2C device <idx>
 */
i2c_config_t *i2c_get_device(uint32_t idx);

void HAL_tlmm_ConfigGpio( uint32_t nWhichConfig );

typedef enum {
	I2C_DEVICE_1 = 0,
	I2C_DEVICE_2,
	I2C_DEVICE_3,
	I2C_DEVICE_4,
	I2C_DEVICE_5,
	I2C_DEVICE_6,
	I2C_DEVICE_7,
	I2C_DEVICE_8,
	I2C_NUM_DEVICES
} I2cDevice;

typedef enum
{
  DAL_GPIO_INPUT  = 0,     /**< -- Set to INPUT. */
  DAL_GPIO_OUTPUT = 1,     /**< -- Set to OUTPUT. */

/** @cond */
  DAL_PLACEHOLDER_DALGpioDirectionType = 0x7fffffff
/**@endcond */

}DALGpioDirectionType;

typedef enum
{
  DAL_GPIO_2MA     = 0,    /**< -- Specify a 2 mA drive. */
  DAL_GPIO_4MA     = 0x1,  /**< -- Specify a 4 mA drive. */
  DAL_GPIO_6MA     = 0x2,  /**< -- Specify a 6 mA drive. */
  DAL_GPIO_8MA     = 0x3,  /**< -- Specify an 8 mA drive. */
  DAL_GPIO_10MA    = 0x4,  /**< -- Specify a 10 mA drive. */
  DAL_GPIO_12MA    = 0x5,  /**< -- Specify a 12 mA drive. */
  DAL_GPIO_14MA    = 0x6,  /**< -- Specify a 14 mA drive. */
  DAL_GPIO_16MA    = 0x7,  /**< -- Specify a 16 mA drive. */

/** @cond */
  DAL_PLACEHOLDER_DALGpioDriveType = 0x7fffffff
/** @endcond */

}DALGpioDriveType;

typedef enum
{
  DAL_GPIO_NO_PULL    = 0,   /**< -- Do not specify a pull. */
  DAL_GPIO_PULL_DOWN  = 0x1, /**< -- Pull the GPIO down. */
  DAL_GPIO_KEEPER     = 0x2, /**< -- Designate as a Keeper. */
  DAL_GPIO_PULL_UP    = 0x3, /**< -- Pull the GPIO up. */

/** @cond */
  DAL_PLACEHOLDER_DALGpioPullType = 0x7fffffff
/** @endcond */

}DALGpioPullType;

I2cResult I2C_Attach(I2cDevice dev);
I2cResult I2C_Detach(I2cDevice dev);
I2cResult I2C_Open(I2cDevice  dev);
I2cResult I2C_Close(I2cDevice  dev);
I2cResult I2C_Read(I2cDevice dev, I2cTransfer *pTransfer,
                   I2cClientConfig *pClntCfg, uint32_t *puNumCompleted);
I2cResult I2C_Write(I2cDevice dev, I2cTransfer *pTransfer,
                    I2cClientConfig *pClntCfg, uint32_t *puNumCompleted);
I2cResult I2C_BatchTransfer(I2cDevice dev, I2cSequence *pSequence,
                            I2cClientConfig *pClntCfg, I2cIoResult *IoRes);
I2cResult I2C_Reset(I2cDevice dev);

typedef struct {
	uint32_t BusClockKhz;
	uint32_t TimeoutMs;
	uint32_t DefaultAppsClkKhz;
} I2cDefaultHobData;

#include <asm/mach/i2c.h>

#endif /* __TARGET_I2C_H_INCLUDE__ */
