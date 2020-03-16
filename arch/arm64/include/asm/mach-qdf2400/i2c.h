#ifndef _I2CDEVICE_H_
#define _I2CDEVICE_H_

typedef struct __I2CDEVQUP_Device I2CDEVQUP_Device;

#include <asm/mach/qupe.h>
#ifdef IMC_BUILD
#include "qurt_pimutex.h"
#else
#define qurt_mutex_t void*
#define qurt_pimutex_init(lock)
#define qurt_pimutex_destroy(lock)
#define qurt_pimutex_lock(lock)
#define qurt_pimutex_unlock(lock)
#define qurt_pimutex_try_lock(lock)
#endif

#define I2CDEVQUP_HW_EVT_QUE_MAX         (16)

typedef enum I2CDEV_PowerStates {
	/* Bus and clocks off */
	I2CDEV_POWER_STATE_0,
	/* Bus on clocks off */
	I2CDEV_POWER_STATE_1,
	/* Bus on clocks on */
	I2CDEV_POWER_STATE_2,
} I2CDEV_PowerStates;

typedef volatile struct I2CDEVQUP_QupIsrHwEvt {
	uint32_t uIrqCnt;
	uint32_t uQupErrors;
	uint32_t uOperational;
	uint32_t uOutTranCnt;
	uint32_t uInTranCnt;
	HAL_qupe_I2cStatus i2cStatus;
} I2CDEVQUP_QupIsrHwEvt;

typedef volatile struct I2CDEVQUP_QupHwEvtQueue {
	I2CDEVQUP_QupIsrHwEvt aHwEvt[I2CDEVQUP_HW_EVT_QUE_MAX];
	I2CDEVQUP_QupIsrHwEvt *pHead;
	I2CDEVQUP_QupIsrHwEvt *pTail;
} I2CDEVQUP_QupHwEvtQueue;

typedef enum I2CDEV_Command {
	I2CDEV_COMMAND_NULL,		/* Do nothing */
	I2CDEV_COMMAND_RESET_DEVICE,	/* Resets the device */
} I2CDEV_Command;

typedef struct I2CDEVQUP_SequenceIOInfo I2CDEVQUP_SequenceIOInfo;

typedef enum I2CDEVQUP_InitState {
	I2CDEVQUP_InitState_Uninitialized     = 0x0,
	I2CDEVQUP_InitState_TargetInit_Done   = 0x1,
	I2CDEVQUP_InitState_DeviceInit_Done   = 0x4,
	I2CDEVQUP_InitState_HardwareInit_Done = 0x8,
} I2CDEVQUP_InitState;

typedef struct I2CDEVQUP_QupInfo {
	uint32_t uIrqCnt;
	I2CDEVQUP_QupHwEvtQueue hwEvtQueue;
	uint32_t uInFreeSlotReqCnt;
	uint32_t uOutFreeSlotReqCnt;
	uint32_t uQupErrors;
	uint32_t uOperational;
	HAL_qupe_I2cStatus i2cStatus;
	uint32_t uInFreeSlotServicedCnt;
	uint32_t uOutFreeSlotServicedCnt;
	uint32_t uCurOutTransfers;
	uint32_t uCurInTransfers;
	HAL_qupe_IOModeType eOutFifoMode;
	HAL_qupe_IOModeType eInFifoMode;
} I2CDEVQUP_QupInfo;

typedef enum I2CDEVQUP_TransferState {
	I2CDEVQUP_TR_STATE_PAD_OUTPUT,
	I2CDEVQUP_TR_STATE_TIME_STAMP_TAG,
	I2CDEVQUP_TR_STATE_TIME_STAMP_VALUE,
	I2CDEVQUP_TR_STATE_START_TAG,
	I2CDEVQUP_TR_STATE_SLAVE_ADDR,
	I2CDEVQUP_TR_STATE_RD_DATA_TAG,
	I2CDEVQUP_TR_STATE_WR_DATA_TAG,
	I2CDEVQUP_TR_STATE_DATA_CNT,
	I2CDEVQUP_TR_STATE_EOT_TAG,
	I2CDEVQUP_TR_STATE_DATA_VALUE,
	I2CDEVQUP_TR_STATE_DATA_PAD,
	I2CDEVQUP_TR_STATE_NOT_IN_TRANSFER,
	I2CDEVQUP_TR_STATE_EXTEND = 0x7FFFFFFF
} I2CDEVQUP_TransferState;

typedef enum I2CDEVQUP_OutputState {
	I2CDEVQUP_OUTPUT_IDDLE,
	I2CDEVQUP_OUTPUT_STALLED,
	I2CDEVQUP_OUTPUT_FILL_FIFO,
	I2CDEVQUP_OUTPUT_FILL_FIFO_DONE,
	I2CDEVQUP_OUTPUT_TRANSMIT_DONE,
	I2CDEVQUP_OUTPUT_ERROR,
} I2CDEVQUP_OutputState;

typedef struct I2CDEVQUP_OutSeqInfo {
	I2CDEVQUP_OutputState eOutputState;
	I2cTransfer *pTransfer;
	uint32_t uTotalOutBytes;	/*data + format */
	uint32_t uCurOutBytes;		/* data + format */
	uint32_t uNumOutDtBytes;	/* data cnt */
	uint32_t uOutTrCnt;
	uint32_t uTrIndex;
	struct OutTransferInfo {
		I2CDEVQUP_TransferState eOutTrState;
		uint32_t uDataIndex;
		uint32_t uNextDataSegIndex;
		I2cBuffDesc *pTrIOVec;
		uint32_t IoVecBuffIndex;
	} outTr;
	I2CDEVQUP_SequenceIOInfo *pSeq;
} I2CDEVQUP_OutSeqInfo;

typedef enum I2CDEVQUP_InputState {
	I2CDEVQUP_INPUT_IDLE,
	I2CDEVQUP_INPUT_STALLED,
	I2CDEVQUP_INPUT_MEMORY_FLUSH,
	I2CDEVQUP_INPUT_RECEIVE_FROM_INPUT_FIFO,
	I2CDEVQUP_INPUT_PUSH_DESCRIPTORS,
	I2CDEVQUP_INPUT_WAIT_READ_DATA_READY,
	I2CDEVQUP_INPUT_RECEIVE_DONE,
	I2CDEVQUP_INPUT_ERROR,
} I2CDEVQUP_InputState;

typedef struct  I2CDEVQUP_InSeqInfo {
   I2CDEVQUP_InputState       eInSeqState;
   I2cTransfer               *pTransfer;
   uint32_t                     uTotalInBytes;//data + format
   uint32_t                     uNumInDtBytes;//data cnt
   uint32_t                     uInPadCnt;
   uint32_t                     uInTrCnt;
   uint32_t                     uTrIndex;
   uint32_t                     uLastTrIndex;
   uint32_t                     uNumInBytesReceived;
   struct InTransferInfo
   {
      I2CDEVQUP_TransferState eInTrState;
      uint32_t                  uDataIndex; //transfer data index
      uint32_t                  uNextDataSegIndex;
      I2cBuffDesc            *pTrIOVec;
      uint8_t                  *pIoVecBuff;
      uint32_t                  IoVecBuffIndex;
   } inTr;
   I2CDEVQUP_SequenceIOInfo  *pSeq;
} I2CDEVQUP_InSeqInfo;

typedef enum I2CDEVQUP_SequenceState
{
   I2CDEVQUP_SEQSTATE_IDLE,
   I2CDEVQUP_SEQSTATE_INPUT_OUTPUT,
   I2CDEVQUP_SEQSTATE_COMPLETING,
   I2CDEVQUP_SEQSTATE_COMPLETE,
   I2CDEVQUP_SEQSTATE_QUP_STATE_ERROR,
} I2CDEVQUP_SequenceState;

struct I2CDEVQUP_SequenceIOInfo
{
   I2cTransfer                     *pTransfer;
   uint32_t                           uNumTransfers;
   uint32_t                           uSeqTimeoutUs;
   I2CDEVQUP_OutSeqInfo             outSeqInfo;
   I2CDEVQUP_InSeqInfo              inSeqInfo;
   I2CDEVQUP_SequenceState          eSeqState;
   I2cIoResult                      ioRes;
};


typedef enum MiniCoreCfg
{
   MINICORE_UNDEF,
   MINICORE_SPI=1,
   MINICORE_I2C=2,
   MINICORE_SMBUS=3
} MiniCoreCfg;

struct __I2CDEVQUP_Device {
    I2cDevice dev;
    HAL_qupe_HwInfoType devHwInfo;
    uint32_t devInitState;
    I2CDEVQUP_SequenceIOInfo seqInfo;
    I2CDEVQUP_QupInfo qupInfo;
    I2CDEV_PowerStates devPowerState;
    qurt_mutex_t pCritSectMutex;
    uint32_t uOpenCount;
    MiniCoreCfg miniCfg;
    I2cClientConfig clntCfg;
    i2c_config_t *config;
    uint32_t tmpPowerState;//untill clocks are operational
};

I2cResult I2CDEV_Init(I2CDEVQUP_Device *pDev);
I2cResult I2CDEV_DeInit(I2CDEVQUP_Device *pDev);
I2cResult I2CDEV_Read(I2CDEVQUP_Device *pDev,
		      I2cTransfer *pTransfer,
		      I2cClientConfig *pClntCfg,
		      uint32_t *puNumCompleted);
I2cResult I2CDEV_Write(I2CDEVQUP_Device *pDev,
		       I2cTransfer *pTransfer,
		       I2cClientConfig *pClntCfg,
		       uint32_t *puNumCompleted);
I2cResult I2CDEV_BatchTransfer(I2CDEVQUP_Device *pDev,
			       I2cSequence *pSequence,
			       /* if null keep previous */
			       I2cClientConfig *pClntCfg,
			       I2cIoResult *pIoRes);
I2cResult I2CDEV_SetPowerState(I2CDEVQUP_Device *pDev,
			       I2CDEV_PowerStates ePowerState);
I2cResult I2CDEV_GetPowerState(I2CDEVQUP_Device *pDev,
			       I2CDEV_PowerStates *pePowerState);
I2cResult I2CDEV_Reset(I2CDEVQUP_Device *pDev);

#include <asm/mach/qupe.h>

#endif /* I2CDEVICE_H */
