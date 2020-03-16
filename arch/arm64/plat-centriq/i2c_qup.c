#include <stdint.h>
#include <stdlib.h>
#include <target/delay.h>
#include <target/i2c.h>
#include <asm/hal/HALhwio.h>
#include <asm/mach-qdf2400/hal/HALtlmmHWIO.h>

#define MAX_DATA_SEGMENT_LENGTH       255
#define I2CDEVQUP_DEFAULT_BUS_FREQ_KHZ               100
#define I2CDEVQUP_DEFAULT_BYTE_TRANSFER_TIMEOUT_US   200
#define QUP_RUN_STATE_CHANGE_TIME_OUT_US     100
#define QUP_I2C_MASTER_BUS_CLEAR_TIME_OUT_US (500*1000)
#define QUP_BUSY_WAIT_STEP_US                 5


#define DEFAULT_APP_CLK_FREQ_KHZ 50000  //I2cDefaults.h equal to hob.xml i2c config



static int32_t I2CDEV_AbortTransfer(I2CDEVQUP_Device *pDev);

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
typedef enum I2CPLATDEV_PowerStates {
    I2CPLATDEV_POWER_STATE_0,/* Bus and clocks off */
    I2CPLATDEV_POWER_STATE_1,/* Bus on clocks off */
    I2CPLATDEV_POWER_STATE_2,/* Bus on clocks on */
} I2CPLATDEV_PowerStates;

/*-------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * ----------------------------------------------------------------------*/
static I2cResult I2CPLATDEV_InitGpios(I2CDEVQUP_Device *pDev)
{
    uint32_t i;

    for(i=0; i<NUM_I2C_GPIO; i++)
    {
        // GPIO CFG defined in I2cConfig.c
        uint32_t cfg   = pDev->config->gpioCfgArr[i];
        uint32_t func  = cfg & 0x0F;
        uint32_t pull  = (cfg >> 15) & 0x3;
        uint32_t drive = (cfg >> 17) & 0xF;
        uint64_t gpio  = (cfg >> 4)  & 0x3FF;

        // Encode into TLMM config and write to register
        uint32_t gpioCfg = func  << HWIO_TLMM_GPIO_CFGn_FUNC_SEL_SHFT     |
                           pull  << HWIO_TLMM_GPIO_CFGn_GPIO_PULL_SHFT    |
                           drive << HWIO_TLMM_GPIO_CFGn_DRV_STRENGTH_SHFT |
                           1     << HWIO_TLMM_GPIO_CFGn_GPIO_OE_SHFT;
        HWIO_OUTI(TLMM_GPIO_CFGn, gpio, gpioCfg);
    }

    return I2C_RES_SUCCESS;
}

static I2cResult I2CPLATDEV_DeInitGpios(I2CDEVQUP_Device *pDev)
{
    return I2C_RES_SUCCESS;
}

static I2cResult __attribute__ ((noinline))
I2CPLATDEV_InitClocks(I2CDEVQUP_Device *pDev)
{
    // Per-device clock initialization has been deprecated by the clock driver
    return I2C_RES_SUCCESS;
}

static I2cResult I2CPLATDEV_DeInitClocks(I2CDEVQUP_Device *pDev)
{
    // Per-device clock initialization has been deprecated by the clock driver
    return I2C_RES_SUCCESS;
}

static I2cResult __attribute__ ((noinline))
I2CPLATDEV_EnableClocks(I2CDEVQUP_Device *pDev)
{
    // Per-device clock initialization has been deprecated by the clock driver
    return I2C_RES_SUCCESS;
}

static I2cResult I2CPLATDEV_DisableClocks(I2CDEVQUP_Device *pDev)
{
    // Per-device clock initialization has been deprecated by the clock driver
    return I2C_RES_SUCCESS;
}

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/
I2cResult I2CPLATDEV_SetPowerState(I2CDEVQUP_Device *pDev,
                                   uint32_t state)
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

I2cResult I2CPLATDEV_GetPowerState(I2CDEVQUP_Device *pDev,
                                   uint32_t *pState)
{
    if ( NULL == pDev  || NULL == pState )
        return I2CPLATSVC_ERROR_NULL_POINTER;
    *pState = pDev->tmpPowerState;
    return I2C_RES_SUCCESS;
}

I2cResult I2CPLATDEV_InitTarget(I2CDEVQUP_Device *pDev)
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

I2cResult I2CPLATDEV_DeInitTarget(I2CDEVQUP_Device *pDev)
{
    int32_t res ;
    if ( NULL == pDev ) return I2CPLATSVC_ERROR_NULL_POINTER;

    res  = I2CPLATDEV_DeInitClocks(pDev);
    I2CPLATDEV_DeInitGpios(pDev);
    return res;
}

static void QUP_UpdateTransferCnt(I2CDEVQUP_Device *pDev)
{
   I2CDEVQUP_QupInfo              *pQupInfo;
   I2CDEVQUP_OutSeqInfo           *pOutSeqInfo;
   I2CDEVQUP_InSeqInfo            *pInSeqInfo;

   pQupInfo    = &pDev->qupInfo;
   pOutSeqInfo = &pDev->seqInfo.outSeqInfo;
   pInSeqInfo  = &pDev->seqInfo.inSeqInfo;

   pQupInfo->uCurOutTransfers =
         HAL_qupe_GetOutTransferCountCurrentExt(
                           pDev->config->virtBlockAddr,
                           pQupInfo->eOutFifoMode,
                           pOutSeqInfo->uTotalOutBytes);
   pQupInfo->uCurInTransfers =
         HAL_qupe_GetInTransferCountCurrentExt(
                           pDev->config->virtBlockAddr,
                           pQupInfo->eInFifoMode,
                           pInSeqInfo->uTotalInBytes);
}

static int32_t I2CDEVQUP_WaitForRunStateValid(uint8_t *pQupAddr)
{
   uint32_t uWaitTimeUs = QUP_RUN_STATE_CHANGE_TIME_OUT_US;

   while( (!HAL_qupe_RunStateIsValid(pQupAddr)) && (0 != uWaitTimeUs) ) {
      udelay(QUP_BUSY_WAIT_STEP_US);
      uWaitTimeUs -= QUP_BUSY_WAIT_STEP_US;
   }
   if( 0 == uWaitTimeUs ) {
      return I2CDEVQUP_ERR_INVALID_RUNSTATE;
   }

   return I2C_RES_SUCCESS;
}

static int32_t I2CDEVQUP_ResetQupCore(I2CDEVQUP_Device *pDev)
{
   int32_t               res;

   HAL_qupe_Reset(pDev->config->virtBlockAddr);
   HAL_qupe_Configure(pDev->config->virtBlockAddr, pDev->miniCfg == MINICORE_SMBUS);

   res = I2CDEVQUP_WaitForRunStateValid(pDev->config->virtBlockAddr);

   return res;
}

static int32_t I2CDEVQUP_SetRunState(uint8_t *pQupAddr,
                                     const HAL_qupe_RunStateType eNewRunState)
{
   uint32_t uWaitTimeUs = QUP_RUN_STATE_CHANGE_TIME_OUT_US;
   HAL_qupe_RunStateType eRunState;

   HAL_qupe_SetRunStateExt(pQupAddr, eNewRunState);
   eRunState = HAL_qupe_GetRunState(pQupAddr);
   while ( ( 0 != uWaitTimeUs ) && ( eNewRunState != eRunState ) ) {
      udelay(QUP_BUSY_WAIT_STEP_US);
      uWaitTimeUs -= QUP_BUSY_WAIT_STEP_US;
      eRunState = HAL_qupe_GetRunState(pQupAddr);
   }
   if( 0 == uWaitTimeUs ) {
      return I2CDEVQUP_ERR_RUNSTATE_CHANGE_TIMEOUT;
   }

   return I2C_RES_SUCCESS;
}

static int32_t I2CDEVQUP_SetRunStateIfValid(uint8_t *pQupAddr,
                                            const HAL_qupe_RunStateType eNewRunState)
{
   uint32_t uWaitTimeUs = QUP_RUN_STATE_CHANGE_TIME_OUT_US;
   HAL_qupe_RunStateType eRunState;

   eRunState = HAL_qupe_GetRunState(pQupAddr);
   while( (HAL_QUPE_RUNSTATE_INVALID == eRunState) &&
          (0 != uWaitTimeUs) ) {
      udelay(QUP_BUSY_WAIT_STEP_US);
      uWaitTimeUs -= QUP_BUSY_WAIT_STEP_US;
      eRunState = HAL_qupe_GetRunState(pQupAddr);
   }
   if( 0 == uWaitTimeUs ) {
      return I2CDEVQUP_ERR_INVALID_RUNSTATE;
   }

   if ( eRunState == eNewRunState) {
      return I2C_RES_SUCCESS;
   }

   return I2CDEVQUP_SetRunState(pQupAddr, eNewRunState);
}

static void I2CDEVQUP_QupHwEvtQueue_Init(I2CDEVQUP_QupHwEvtQueue *pHwEvtQ)
{
   pHwEvtQ->pHead = pHwEvtQ->aHwEvt;
   pHwEvtQ->pTail = pHwEvtQ->aHwEvt;
}

static bool I2CDEVQUP_QupHwEvtQueue_IsFull(I2CDEVQUP_QupHwEvtQueue *pHwEvtQ)
{
   I2CDEVQUP_QupIsrHwEvt *pNext;

   pNext = pHwEvtQ->pHead + 1; /* advance the pointer by 1 slot. */
   if ( pNext == (pHwEvtQ->aHwEvt + I2CDEVQUP_HW_EVT_QUE_MAX) ) {
      pNext = pHwEvtQ->aHwEvt;
   }
   return (pNext == pHwEvtQ->pTail);
}

static bool I2CDEVQUP_QupHwEvtQueue_IsEmpty(I2CDEVQUP_QupHwEvtQueue *pHwEvtQ)
{
   return (pHwEvtQ->pHead == pHwEvtQ->pTail);
}

static void __attribute__ ((noinline))
I2CDEVQUP_QupHwEvtQueue_TailNext(I2CDEVQUP_QupHwEvtQueue *pHwEvtQ)
{
   I2CDEVQUP_QupIsrHwEvt *pNext;

   pNext = pHwEvtQ->pTail + 1; /* advance the pointer by 1 slot. */
   if ( pNext == (pHwEvtQ->aHwEvt + I2CDEVQUP_HW_EVT_QUE_MAX) ) {
      pNext = pHwEvtQ->aHwEvt;
   }
   pHwEvtQ->pTail = pNext;
}

static void __attribute__ ((noinline))
I2CDEVQUP_QupHwEvtQueue_HeadNext(I2CDEVQUP_QupHwEvtQueue *pHwEvtQ)
{
   I2CDEVQUP_QupIsrHwEvt *pNext;

   pNext = pHwEvtQ->pHead + 1; /* advance the pointer by 1 slot. */
   if ( pNext == (pHwEvtQ->aHwEvt + I2CDEVQUP_HW_EVT_QUE_MAX) ) {
      pNext = pHwEvtQ->aHwEvt;
   }
   pHwEvtQ->pHead = pNext;
}

static void __attribute__ ((noinline))
I2CDEVQUP_QupHwEvtQueue_ProcessIsrEvt(I2CDEVQUP_Device *pDev,
                                      I2CDEVQUP_QupIsrHwEvt *pIsrEvt)
{
   I2CDEVQUP_QupInfo              *pQupInfo;
   I2CDEVQUP_OutSeqInfo           *pOutSeqInfo;
   I2CDEVQUP_SequenceIOInfo       *pSeqInfo;
   I2cTransfer                    *pTransfer;

   pSeqInfo = &pDev->seqInfo;
   pTransfer = pSeqInfo->pTransfer;

   pQupInfo = &pDev->qupInfo;
   pOutSeqInfo = &pDev->seqInfo.outSeqInfo;

   pQupInfo->uQupErrors                |= pIsrEvt->uQupErrors;
   pQupInfo->uOperational              |= pIsrEvt->uOperational;

   /* OR the RawStatus only  and not the line state */
   pQupInfo->i2cStatus.uRawLineState    = pIsrEvt->i2cStatus.uRawLineState;
   pQupInfo->i2cStatus.uRawStatus      |= pIsrEvt->i2cStatus.uRawStatus &
       HAL_QUPE_I2C_OP_STATUS_ERROR_FIELD;

   pQupInfo->uCurOutTransfers = pIsrEvt->uOutTranCnt;
   pQupInfo->uCurInTransfers  = pIsrEvt->uInTranCnt;

   /* If output service then fill the output queue with another block.       */
   if ( pIsrEvt->uOperational & HAL_QUPE_OPSTATE_OUTPUT_SERVICE ) {
      if ( (HAL_QUPE_IO_MODE_BLOCK == pQupInfo->eOutFifoMode) &&
       (pIsrEvt->uOperational & HAL_QUPE_OPSTATE_OUT_BLOCK_WRITE_REQ) ) {
         pQupInfo->uOutFreeSlotReqCnt += pDev->devHwInfo.uNumOutputBlockSlots;
      }
      /* In fifo mode the OUTPUT_SERVICE is set and the MAX_OUTPUT_DONE
       * is not set at the same time. */
      if ( HAL_QUPE_IO_MODE_FIFO == pQupInfo->eOutFifoMode ) {
         pOutSeqInfo->eOutputState = I2CDEVQUP_OUTPUT_TRANSMIT_DONE;
      }
   }
   if ( pIsrEvt->uOperational & HAL_QUPE_OPSTATE_MAX_OUTPUT_DONE ) {
      pOutSeqInfo->eOutputState = I2CDEVQUP_OUTPUT_TRANSMIT_DONE;
   }

   if (((pTransfer->eTranCtxt == I2cTrCtxSeqStart) || (pTransfer->eTranCtxt == I2cTrCtxSeqContinue)) &&
        (pSeqInfo->uNumTransfers == 1)) {
      if ( pIsrEvt->uOperational & HAL_QUPE_OPSTATE_MAX_INPUT_DONE ) {
         pOutSeqInfo->eOutputState = I2CDEVQUP_OUTPUT_TRANSMIT_DONE;
      }
   }

   /* If input service then get the blocks from queue.                       */
   if ( pIsrEvt->uOperational & HAL_QUPE_OPSTATE_INPUT_SERVICE ) {
      if ( (HAL_QUPE_IO_MODE_BLOCK == pQupInfo->eInFifoMode) &&
           (pIsrEvt->uOperational & HAL_QUPE_OPSTATE_IN_BLOCK_READ_REQ) ) {
         /* last block gets this as well as normal block requests. */
         pQupInfo->uInFreeSlotReqCnt += pDev->devHwInfo.uNumInputBlockSlots;
      }
      else {
         pQupInfo->uInFreeSlotReqCnt +=
            HAL_qupe_GetInFifoOccupiedSlotsCount(pDev->config->virtBlockAddr);
      //   pQupInfo->bRxDone = true;
      }
   }
   if ( pIsrEvt->i2cStatus.uRawStatus & HAL_QUPE_I2C_OP_STATUS_ERROR_FIELD ) {
      /* Don't continue filling the output fifo if there is an error. */
      pOutSeqInfo->eOutputState = I2CDEVQUP_OUTPUT_ERROR;
   }

   return;
}

void I2CDEVQUP_CalcTransferInOutSize(I2cTransfer *pTransfer,
                                     uint32_t *puNumInBytes,
                                     uint32_t *puNumOutBytes)
{
   uint32_t uNumDataSegments;
   uint32_t uTransferSize = pTransfer->uTrSize;

   uNumDataSegments = uTransferSize/MAX_DATA_SEGMENT_LENGTH;
   if ( uTransferSize % MAX_DATA_SEGMENT_LENGTH ) {
      uNumDataSegments++;
   }
   if ( I2cTranDirIn == pTransfer->eTranDirection ) {
      /* read:
         st_tag + sl_addr + {dt_tag + bt_cnt} * n */
      *puNumOutBytes = 2 +  uNumDataSegments*2;
      if (pTransfer->uIsSmbusBlock)
      {
          *puNumOutBytes = *puNumOutBytes - 2;
      }
      /* {dt_tag + bt_cnt} * n + data_len               */
      *puNumInBytes  =  uNumDataSegments*2 + uTransferSize;
   }
   else {
      /* write:
         st_tag + sl_addr + {dt_tag + bt_cnt} * n + data_len */
      *puNumOutBytes = 2 +  uNumDataSegments*2 + uTransferSize;
      *puNumInBytes  = 0;
   }
}

static void I2CDEVQUP_CalcTransferredDataBytes(I2CDEVQUP_Device *pDev)
{
   uint32_t uNumDataSegments;
   I2CDEVQUP_SequenceIOInfo *pSeqInfo;
   I2CDEVQUP_QupInfo *pQupInfo;
   uint32_t uOutByteCnt;
   uint32_t uInByteCnt;
   uint32_t uNumInTrBytes;
   uint32_t uNumOutTrBytes;
   I2CDEVQUP_OutSeqInfo *pOutSeqInfo;
   I2CDEVQUP_InSeqInfo *pInSeqInfo;
   I2cTransfer *pTransfer;
   uint32_t uTrIndex;
   bool bOutComplete;
   bool bInComplete;

   pSeqInfo    = &pDev->seqInfo;
   pOutSeqInfo = &pDev->seqInfo.outSeqInfo;
   pInSeqInfo  = &pDev->seqInfo.inSeqInfo;
   pQupInfo    = &pDev->qupInfo;

   if (I2C_RES_SUCCESS == pSeqInfo->ioRes.nOperationResult) {
      pSeqInfo->ioRes.uInByteCnt  = pInSeqInfo->uNumInDtBytes;
      pSeqInfo->ioRes.uOutByteCnt = pOutSeqInfo->uNumOutDtBytes;
      return;
   }

   uInByteCnt   = pQupInfo->uCurInTransfers;
   uOutByteCnt  = pQupInfo->uCurOutTransfers;
   pSeqInfo->ioRes.uInByteCnt  = 0;
   pSeqInfo->ioRes.uOutByteCnt = 0;
   bOutComplete = bInComplete = false;

   if ( uOutByteCnt != 0 ) {
      uTrIndex = 0;
      do {
         pTransfer = &pSeqInfo->pTransfer[uTrIndex];
         I2CDEVQUP_CalcTransferInOutSize(pTransfer,&uNumInTrBytes, &uNumOutTrBytes);

         if ( uOutByteCnt >= uNumOutTrBytes ) {
            uOutByteCnt -= uNumOutTrBytes;
            if ( 0 == uOutByteCnt ) {
               bOutComplete = true;/* full output last */
            }
         }
         else {
            break;/* partial output do not count this transfer */
         }

         if ( uInByteCnt >= uNumInTrBytes ) {
            uInByteCnt -= uNumInTrBytes;
            if ( 0 == uInByteCnt ) {
               bInComplete = true;/* full input last */
            }
         }
         else {
            break;/* partial input do not count this */
         }

         if ( I2cTranDirIn == pTransfer->eTranDirection ) {
            pSeqInfo->ioRes.uInByteCnt += pTransfer->uTrSize;
         }
         else {
            pSeqInfo->ioRes.uOutByteCnt += pTransfer->uTrSize;
         }

         ++uTrIndex;
      } while( (uTrIndex < pSeqInfo->uNumTransfers) &&
               (!bOutComplete || !bInComplete) );
   }

   if ( !bOutComplete || !bInComplete ) {
      if ( I2cTranDirIn == pOutSeqInfo->pTransfer->eTranDirection ) {
         /* read
             {bt_cnt} * n + data_len */
         uNumDataSegments = uInByteCnt/(MAX_DATA_SEGMENT_LENGTH + 1);
         if (uInByteCnt % (MAX_DATA_SEGMENT_LENGTH + 1)) {
            uNumDataSegments++;
         }
         /* count out the formating overhead, 1 byte per segment */
         pSeqInfo->ioRes.uInByteCnt += (uInByteCnt - uNumDataSegments);
      }
      else {
         /* write
             st_tag + sl_addr + {dt_tag + bt_cnt} * n + data_segment */
         if (uOutByteCnt > 4) {
            uOutByteCnt -= 2; /* drop st_tag + sl_addr */
            uNumDataSegments = uOutByteCnt/(MAX_DATA_SEGMENT_LENGTH + 2);
            if (uOutByteCnt % (MAX_DATA_SEGMENT_LENGTH + 2)) {
               uNumDataSegments++;
            }
            /* count out the formating overhead, 2 bytes per segment */
            pSeqInfo->ioRes.uOutByteCnt += (uOutByteCnt - uNumDataSegments*2);
         }
      }
   }
}

static bool QUP_WaitForI2cBusFree(I2CDEVQUP_Device *pDev)
{
   uint32_t uTimeout;
   I2CDEVQUP_QupInfo *pQupInfo;
   const uint32_t cuTimeStep = QUP_BUSY_WAIT_STEP_US; /* 5 us */

   pQupInfo = &pDev->qupInfo;
   /* Check stored state. */
   if (!HAL_qupe_IsI2CStateBusy(&pQupInfo->i2cStatus)) {
      return true;
   }
   /* Checks the actual bus state. */
   if ( !HAL_qupe_IsI2CBusBusy(pDev->config->virtBlockAddr) ) {
      return true;
   }

   uTimeout = pDev->clntCfg.uByteTransferTimeoutUs;
   do{
      udelay(cuTimeStep);
      if ( uTimeout > cuTimeStep ) {
         uTimeout -= cuTimeStep;
      }
      else {
         uTimeout = 0;
      }
   } while ( uTimeout && HAL_qupe_IsI2CBusBusy(pDev->config->virtBlockAddr) );

   return (!HAL_qupe_IsI2CBusBusy(pDev->config->virtBlockAddr));
}

static bool QUP_WaitForI2cBusClkForcedLow(I2CDEVQUP_Device *pDev)
{
   uint32_t uTimeout;
   const uint32_t cuTimeStep = QUP_BUSY_WAIT_STEP_US; /* 5 us */

   if (HAL_qupe_IsI2CBusClkForcedLow (pDev->config->virtBlockAddr)) {
      return true;
   }

   uTimeout = pDev->clntCfg.uByteTransferTimeoutUs;
   do{
      udelay(cuTimeStep);
      if ( uTimeout > cuTimeStep ) {
         uTimeout -= cuTimeStep;
      }
      else {
         uTimeout = 0;
      }
   } while ( uTimeout && !HAL_qupe_IsI2CBusClkForcedLow(pDev->config->virtBlockAddr) );

   return (HAL_qupe_IsI2CBusClkForcedLow(pDev->config->virtBlockAddr));
}

static int32_t QUP_WaitForI2cBusClear(I2CDEVQUP_Device *pDev)
{
    uint32_t uWaitTimeUs = QUP_I2C_MASTER_BUS_CLEAR_TIME_OUT_US;
    while( (!HAL_qupe_IsI2CBusClear(pDev->config->virtBlockAddr)) &&
           (0 != uWaitTimeUs) )
    {
        udelay(QUP_BUSY_WAIT_STEP_US);
        uWaitTimeUs -= QUP_BUSY_WAIT_STEP_US;
    }
    if( 0 == uWaitTimeUs )
    {
        return I2CDEVQUP_ERR_BUS_BUSY;
    }
    return I2C_RES_SUCCESS;
}

static int32_t
QUP_ForceClearBus(I2CDEVQUP_Device *pDev)
{
    int32_t res;
    // qup_sw_reset
    HAL_qupe_Reset(pDev->config->virtBlockAddr);
    // qup_state valid
    res = I2CDEVQUP_WaitForRunStateValid(pDev->config->virtBlockAddr);
    if (I2C_RES_SUCCESS != res) return res;
    // qup_config
    HAL_qupe_Configure_ConfigOnly(pDev->config->virtBlockAddr);
    // i2c_master_clk_ctl
    res = HAL_qupe_SetI2cConfig(pDev->config->virtBlockAddr,
            HAL_QUPE_I2C_TAGS_V2,
            pDev->config->appClkFreqKhz,
            pDev->clntCfg.uBusFreqKhz);
    if (I2C_RES_SUCCESS != res) return res;
    // i2c_master_config
    HAL_qupe_Configure_I2cMasterConfig(pDev->config->virtBlockAddr);
    res = I2CDEVQUP_SetRunState(pDev->config->virtBlockAddr,
            HAL_QUPE_RUNSTATE_RUN);
    if (I2C_RES_SUCCESS != res) return res;
    res = I2CDEVQUP_WaitForRunStateValid(pDev->config->virtBlockAddr);
    if (I2C_RES_SUCCESS != res) return res;
    HAL_qupe_ClearI2CBus(pDev->config->virtBlockAddr);
        res = QUP_WaitForI2cBusClear(pDev);
    return res;
}

static void QUP_Completion(I2CDEVQUP_Device *pDev)
{
   I2CDEVQUP_SequenceIOInfo *pSeqInfo;
   I2cTransfer *pTransfer;
   bool bSplitTransfer = false;
   int32_t  res;
   /* If this is an asynchronous transfer then set results and
      dispatch callback else just signal the waiting thread. */

   pSeqInfo = &pDev->seqInfo;
   pTransfer = pSeqInfo->pTransfer;

   /* Before we calculate the counts, we must wait for the bus to be either idle
    * or forced low */
   if (((pTransfer->eTranCtxt == I2cTrCtxSeqStart) ||
        (pTransfer->eTranCtxt == I2cTrCtxSeqContinue)) &&
        (pSeqInfo->uNumTransfers == 1)) {
      bSplitTransfer = true;
   }

   /* Before we calculate the counts, we must wait for the bus to be either idle
    * or forced low */
   if (bSplitTransfer) {
       /* Wait for FORCED LOW state on CLK STATE */
       if ( !QUP_WaitForI2cBusClkForcedLow(pDev) ) {
           if ( I2C_RES_SUCCESS == pDev->seqInfo.ioRes.nOperationResult ) {
               pDev->seqInfo.ioRes.nOperationResult = I2CDEVQUP_ERR_BUS_CLK_NOT_FORCED_LOW;
           }
       }
   } else {
      /*
         QCTDD00352568.
         The driver needs to wait for bus idle before in sets the runstate
         to RESET.
       */
      if ( !QUP_WaitForI2cBusFree(pDev) ) {
         if ( I2C_RES_SUCCESS == pDev->seqInfo.ioRes.nOperationResult ) {
            pDev->seqInfo.ioRes.nOperationResult = I2CDEVQUP_ERR_BUS_NOT_RELEASED;
         }
      }
   }

   I2CDEVQUP_CalcTransferredDataBytes(pDev);

   if (!bSplitTransfer) {
      /* Reset the state */
      res = I2CDEVQUP_SetRunStateIfValid(pDev->config->virtBlockAddr,
               HAL_QUPE_RUNSTATE_RESET);

      if( I2C_RES_SUCCESS != res ) {
         I2CDEVQUP_ResetQupCore(pDev);
         if ( I2C_RES_SUCCESS == pDev->seqInfo.ioRes.nOperationResult ) {
            pDev->seqInfo.ioRes.nOperationResult = res;
         }
      }

      /* After doing the above reset, the bus will be in one of the below states:
         1. Bus is idle. This state can occur in 2 cases
            a) If this is NOT a split transfer and the above code waits until the
               bus is idle.
            b) If this is a SPLIT TRANSFER and slave is not stretching the clock
               after the last byte.
         2. Bus is NOT IDLE. It means the slave is stretching the clock. This can
            occur in 2 cases
            a) If this is NOT a split transfer and the above code waits until the
               bus is idle, but the slave is stretching the clock beyond the
               configured value. Solution: Slave/Client must increase the clk
               stretch timeout.
            b) If this is a SPLIT TRANSFER and slave is stretching the clock after
               the last byte. In this case, we will wait for the bus idle or the
               configured clock stretch timeout (whichever occurs first).
       */
      /* Execute 2b in above comment */
      if (bSplitTransfer) {
         QUP_WaitForI2cBusFree(pDev);
      }
   }
}

void I2CDEVQUP_ProcesQupHwEvts(I2CDEVQUP_Device *pDev)
{
   I2CDEVQUP_QupInfo *pQupInfo;
   I2CDEVQUP_QupIsrHwEvt *pIsrEvt;

   /* I2CPLATDEV_AcquireIntLock(pDev->hDevTgt); */
   pQupInfo = &pDev->qupInfo;

   while ( !I2CDEVQUP_QupHwEvtQueue_IsEmpty(&pQupInfo->hwEvtQueue) ) {
      /* Tail is modified the I2CDEVQUP_QupHwEvtQueue_TailNext. */
      pIsrEvt  = pQupInfo->hwEvtQueue.pTail;
      I2CDEVQUP_QupHwEvtQueue_ProcessIsrEvt(pDev, pIsrEvt);
      I2CDEVQUP_QupHwEvtQueue_TailNext(&pQupInfo->hwEvtQueue);
   }
   /* I2CPLATDEV_ReleaseIntLock(pDev->hDevTgt); */
}

static void QUP_PerformOutput(I2CDEVQUP_Device *pDev);
static void QUP_PerformInput(I2CDEVQUP_Device *pDev);

static void
QUP_PerformInputOutput(I2CDEVQUP_Device *pDev)
{
   I2CDEVQUP_QupInfo *pQupInfo;
   I2CDEVQUP_SequenceIOInfo *pSeqInfo;
   I2CDEVQUP_OutSeqInfo *pOutSeqInfo;
   I2CDEVQUP_InSeqInfo *pInSeqInfo;
   bool bComplete;
   uint32_t uWhileOnce = 0;

   pQupInfo = &pDev->qupInfo;
   pSeqInfo = &pDev->seqInfo;
   pOutSeqInfo = &pDev->seqInfo.outSeqInfo;
   pInSeqInfo  = &pDev->seqInfo.inSeqInfo;

   bComplete = false;

   do {

      I2CDEVQUP_ProcesQupHwEvts(pDev);
      if ( I2CDEVQUP_SEQSTATE_INPUT_OUTPUT != pSeqInfo->eSeqState ) {
         break;
      }

      /* Check for qup hw errors. This should not happen.
         It indicates most likely a programming error.
       */
      if ( pQupInfo->uQupErrors & HAL_QUPE_ERRSTATE_FIELD ) {
         pSeqInfo->ioRes.nOperationResult = I2C_RES_ERROR_CLS_QUP_DEV |
                     (pQupInfo->uQupErrors & HAL_QUPE_ERRSTATE_FIELD);
         I2CDEVQUP_ResetQupCore(pDev);
         bComplete = true;
         break;
      }

      /* Check if there is a transfer to be placed on the out fifo. */
      if ( I2CDEVQUP_OUTPUT_FILL_FIFO == pOutSeqInfo->eOutputState ) {
         QUP_PerformOutput(pDev);
      }

      /* Input sequence handling.
         If there is an error collect as much input as possible.
         All the data in the input fifo.
       */
      if ( I2CDEVQUP_INPUT_RECEIVE_FROM_INPUT_FIFO == pInSeqInfo->eInSeqState ) {
         QUP_PerformInput(pDev);
      }

      /* Process any I2C errors */
      if ( pQupInfo->i2cStatus.uRawStatus & HAL_QUPE_I2C_OP_STATUS_ERROR_FIELD ) {
         pSeqInfo->ioRes.nOperationResult = I2C_RES_ERROR_CLS_I2C_CORE;
         pSeqInfo->ioRes.nOperationResult |=
             HAL_QUPE_PACK28_I2C_STATE(pQupInfo->i2cStatus.uRawStatus,
                                       pQupInfo->i2cStatus.uRawLineState);
         /* Handle the case where the slave stretches the clock after NACK */
         if (pQupInfo->i2cStatus.uRawStatus & HAL_QUPE_I2C_OP_STATUS_PACKET_NACKED) {
             QUP_WaitForI2cBusFree(pDev);
         }

         I2CDEVQUP_ResetQupCore(pDev);
         bComplete = true;
         break;
      }

      /* When we get an I2C error interrupt in BAM mode, we should not push
       * descriptors */
      if ( I2CDEVQUP_INPUT_PUSH_DESCRIPTORS == pInSeqInfo->eInSeqState ) {
          QUP_PerformInput(pDev);
      }

      if ( I2C_RES_SUCCESS != pSeqInfo->ioRes.nOperationResult ) {
         bComplete = true;
         break;
      }

      /* If the transfer has already finished do completion. */
      if ( (I2CDEVQUP_OUTPUT_TRANSMIT_DONE == pOutSeqInfo->eOutputState) &&
           (0 == pInSeqInfo->uTotalInBytes) ) {
         bComplete = true;
         break;
      }

      if ( (I2CDEVQUP_INPUT_RECEIVE_DONE == pInSeqInfo->eInSeqState) &&
           (I2CDEVQUP_OUTPUT_TRANSMIT_DONE == pOutSeqInfo->eOutputState) ) {
         bComplete = true;
         break;
      }
   } while ( uWhileOnce );

   if ( bComplete ) {
      pSeqInfo->eSeqState = I2CDEVQUP_SEQSTATE_COMPLETING;
      QUP_Completion(pDev);
   }

   return;
}

static void QUP_OutSeqInitTransfer(I2CDEVQUP_OutSeqInfo *pOutSeqInfo)
{
   pOutSeqInfo->outTr.uNextDataSegIndex = 0;
   pOutSeqInfo->outTr.uDataIndex = 0;

   // Case where there is a SMBus block read
   if (( 1 == pOutSeqInfo->pTransfer->uIsSmbus ) &&
       ( 1 == pOutSeqInfo->pTransfer->uIsSmbusBlock ) &&
       ( I2cTranDirIn == pOutSeqInfo->pTransfer->eTranDirection )){
      pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_RD_DATA_TAG;
   }
   else {
      pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_START_TAG;
   }

   if ( I2cTranDirOut == pOutSeqInfo->pTransfer->eTranDirection ) {
      pOutSeqInfo->outTr.pTrIOVec  = pOutSeqInfo->pTransfer->pI2cBuffDesc;
      pOutSeqInfo->outTr.IoVecBuffIndex = 0;
   }
   else { /* input transfer. */
      /* The current byte offset into the slot being prepared.
       * If the next transfer is single byte read then we need to pad
       * in order to avoid reading more than required by the transfer
       * due to tag splitting over different slots. */
      if ( 1 == pOutSeqInfo->pTransfer->uTrSize ) {
         if ( pOutSeqInfo->uCurOutBytes & 0x3 ) { /* pad 3 bytes. */
            pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_PAD_OUTPUT;
         }
      }
   }
}

static void QUP_InSeqInitTransfer(I2CDEVQUP_InSeqInfo *pInSeqInfo)
{
    pInSeqInfo->inTr.eInTrState = I2CDEVQUP_TR_STATE_RD_DATA_TAG;
    pInSeqInfo->inTr.uDataIndex = 0;
    pInSeqInfo->inTr.uNextDataSegIndex = 0;

    pInSeqInfo->inTr.pTrIOVec   = pInSeqInfo->pTransfer->pI2cBuffDesc;
    pInSeqInfo->inTr.IoVecBuffIndex = 0;
}

/******************************************************************************
 * The next group of functions handle output sequence/transfer state
 * transitions.
 *****************************************************************************/
static void QUP_OutFsm_MoveNextTransfer(I2CDEVQUP_OutSeqInfo *pOutSeqInfo)
{
   pOutSeqInfo->uTrIndex++;
   if ( pOutSeqInfo->uTrIndex == pOutSeqInfo->pSeq->uNumTransfers ) {
      /* all data has been pushed into the output fifo. */
      /*
       * QCTDD00309260 prevents the driver from adding a FLUSH_STOP tag to
       * terminate the transfer if fifo/block mode.
       * QCTDD00309260:
       * When using i2c version2 tags in non-BAM mode, MAX_OUTPUT_DONE_FLAG
       * is not asserted if the last tag is not DATA_WR_*, DATA_RD_* or
       * NOP_WAIT.
       */
      /* Do not add FLUSH_STOP to handle QCTDD00352578.
       *  See issue above  QCTDD00309260
       */
      pOutSeqInfo->eOutputState = I2CDEVQUP_OUTPUT_FILL_FIFO_DONE;

   }
   else { /* initialize next transfer.*/
      pOutSeqInfo->pTransfer++; /* move to next transfer. */
      QUP_OutSeqInitTransfer(pOutSeqInfo);
   }
}

static void
QUP_OutFsm_PadOutputTagNext(I2CDEVQUP_OutSeqInfo *pOutSeqInfo,
                            uint8_t *pData)
{
   uint32_t   uSlotByteOffset;

   uSlotByteOffset = pOutSeqInfo->uCurOutBytes & 0x3;
   if ( 3 == uSlotByteOffset ){
      pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_START_TAG;
   }

   *pData = HAL_QUPE_TAG_FLUSH_STOP;

   pOutSeqInfo->uCurOutBytes++;
}

static void
QUP_OutFsm_StartTagNext(I2CDEVQUP_OutSeqInfo *pOutSeqInfo,
                        uint8_t* pData)
{
   if ( (I2cTranDirOut == pOutSeqInfo->pTransfer->eTranDirection ) &&
        (0 == pOutSeqInfo->pTransfer->uTrSize) ){
      *pData = HAL_QUPE_TAG_START_STOP;
   }
   else {
      *pData = HAL_QUPE_TAG_START;
   }
   pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_SLAVE_ADDR;
   pOutSeqInfo->uCurOutBytes++;
}

static void
QUP_OutFsm_SlaveAddressNext(I2CDEVQUP_OutSeqInfo *pOutSeqInfo,
                            uint8_t* pData)
{
   uint8_t utmpVal;

   utmpVal =  (uint8_t) (pOutSeqInfo->pTransfer->tranCfg.uSlaveAddr<<1);
   if ( I2cTranDirIn == pOutSeqInfo->pTransfer->eTranDirection ) {
      utmpVal |=    1;
      pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_RD_DATA_TAG;
   }
   else if ( 0 == pOutSeqInfo->pTransfer->uTrSize ) {
      QUP_OutFsm_MoveNextTransfer(pOutSeqInfo);
   }
   else {
      pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_WR_DATA_TAG;
   }
   pOutSeqInfo->uCurOutBytes++;
   *pData = utmpVal;
}

static void QUP_OutFsm_RdDataTagNext(I2CDEVQUP_OutSeqInfo *pOutSeqInfo,
                                     uint8_t* pData)
{
   uint8_t utmpVal;
   uint32_t uBytesLeft;

   if ( (pOutSeqInfo->pTransfer->uTrSize -
         pOutSeqInfo->outTr.uNextDataSegIndex) >
                     MAX_DATA_SEGMENT_LENGTH ) {
      pOutSeqInfo->outTr.uNextDataSegIndex +=MAX_DATA_SEGMENT_LENGTH;
      utmpVal =    HAL_QUPE_TAG_DATA_READ;
      /* add special condition to handle the last 1 byte segment
         make the previous segment shorter and leave 2 bytes on the last
         segment. */
      uBytesLeft = pOutSeqInfo->pTransfer->uTrSize - pOutSeqInfo->outTr.uNextDataSegIndex -1;
      if ( 1 == uBytesLeft ) {
         pOutSeqInfo->outTr.uNextDataSegIndex--;
      }
   }
   else {
      pOutSeqInfo->outTr.uNextDataSegIndex =
              pOutSeqInfo->pTransfer->uTrSize;

      if ((I2cTrCtxSeqStart == pOutSeqInfo->pTransfer->eTranCtxt) ||
          (I2cTrCtxSeqContinue == pOutSeqInfo->pTransfer->eTranCtxt)) {
         utmpVal = HAL_QUPE_TAG_DATA_READ;
      }
      else {
         utmpVal = HAL_QUPE_TAG_DATA_READ_STOP;
      }
   }
   pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_DATA_CNT;
   pOutSeqInfo->uCurOutBytes++;
   *pData = utmpVal;
}

/** @brief This function handles transfer transition from WrDataTag.

    @param[in, out] pOutSeqInfo   Pointer to output sequence info structure.
    @param[out]     pData         Data produced from this state-transition.
    @return         Nothing.
  */
static void
QUP_OutFsm_WrDataTagNext
(
   I2CDEVQUP_OutSeqInfo *pOutSeqInfo,uint8_t* pData
)
{
   uint8_t utmpVal;
   if ( (pOutSeqInfo->pTransfer->uTrSize -
         pOutSeqInfo->outTr.uNextDataSegIndex) >
                     MAX_DATA_SEGMENT_LENGTH) {// shift the next segment
      pOutSeqInfo->outTr.uNextDataSegIndex +=MAX_DATA_SEGMENT_LENGTH;
      utmpVal =    HAL_QUPE_TAG_DATA_WRITE;
   }
   else {
      pOutSeqInfo->outTr.uNextDataSegIndex =
                        pOutSeqInfo->pTransfer->uTrSize;
      if ( (I2cTrCtxSeqStart == pOutSeqInfo->pTransfer->eTranCtxt)   ||
           (I2cTrCtxSeqContinue == pOutSeqInfo->pTransfer->eTranCtxt) ) {
         utmpVal =    HAL_QUPE_TAG_DATA_WRITE;
      }
      else {
         utmpVal = HAL_QUPE_TAG_DATA_WRITE_STOP;
      }
   }
   pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_DATA_CNT;
   pOutSeqInfo->uCurOutBytes++;
   *pData = utmpVal;
}



/** @brief This function handles transfer transition from DataCnt.

    @param[in, out] pOutSeqInfo   Pointer to output sequence info structure.
    @param[out]     pData         Data produced from this state-transition.
    @return         Nothing.
  */
static void
QUP_OutFsm_DataCntNext
(
   I2CDEVQUP_OutSeqInfo *pOutSeqInfo,uint8_t* pData
)
{
   uint8_t uByteCnt;

   uByteCnt = (uint8_t) (pOutSeqInfo->outTr.uNextDataSegIndex -
                            pOutSeqInfo->outTr.uDataIndex);
   if ( 0 == uByteCnt ) {
      QUP_OutFsm_MoveNextTransfer(pOutSeqInfo);
   }
   else if ( I2cTranDirIn == pOutSeqInfo->pTransfer->eTranDirection ) {
      pOutSeqInfo->outTr.uDataIndex += uByteCnt;
      if ( pOutSeqInfo->outTr.uDataIndex == pOutSeqInfo->pTransfer->uTrSize ) {
          QUP_OutFsm_MoveNextTransfer(pOutSeqInfo);
      }
      else {
         pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_RD_DATA_TAG;
      }
   }
   else {
      pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_DATA_VALUE;
   }
   pOutSeqInfo->uCurOutBytes++;
   *pData = uByteCnt;
}

/** @brief This function handles transfer transition from DataValue.

    @param[in, out] pOutSeqInfo   Pointer to output sequence info structure.
    @param[out]     pData         Data produced from this state-transition.
    @return         Nothing.
  */
static void
QUP_OutFsm_DataValueNext
(
   I2CDEVQUP_OutSeqInfo *pOutSeqInfo,uint8_t* pData
)
{
   uint8_t utmpVal;

   if ( pOutSeqInfo->outTr.IoVecBuffIndex == pOutSeqInfo->outTr.pTrIOVec->uBuffSize ) {
      /* get next buffer. */
      pOutSeqInfo->outTr.pTrIOVec++;
      pOutSeqInfo->outTr.IoVecBuffIndex = 0;
   }
   /* gather index. */
   utmpVal = pOutSeqInfo->outTr.pTrIOVec->pBuff[pOutSeqInfo->outTr.IoVecBuffIndex++];
   pOutSeqInfo->outTr.uDataIndex++;
   pOutSeqInfo->uCurOutBytes++;
   *pData = utmpVal;

   if ( pOutSeqInfo->outTr.uDataIndex == pOutSeqInfo->pTransfer->uTrSize ) {
      QUP_OutFsm_MoveNextTransfer(pOutSeqInfo);
   }
   else if ( pOutSeqInfo->outTr.uDataIndex ==
             pOutSeqInfo->outTr.uNextDataSegIndex ) {
      /* next segment. */
      pOutSeqInfo->outTr.eOutTrState = I2CDEVQUP_TR_STATE_WR_DATA_TAG;
   }
}

/** @brief This function drives output seq state transitions.

    It advances the output sequence one slot at the time.
    This function is used to fill the output fifo in fifo/block mode.

    @param[in, out] pOutSeqInfo   Pointer to output sequence info structure.
    @param[out]     pData         Data produced from this state-transition.
    @return         Nothing.
  */
static uint32_t
QUP_GetNextOutSeqSlot
(
   I2CDEVQUP_OutSeqInfo           *pOutSeqInfo
)
{
   uint32_t                          uSlot;
   uint32_t                          uSlotByteIndex;
   uint8_t                           uByteVal;

   uSlot = 0;
   uSlotByteIndex = 0;

   /* create slot. */
   while ( (uSlotByteIndex < 4) &&
            (pOutSeqInfo->eOutputState != I2CDEVQUP_OUTPUT_FILL_FIFO_DONE) ) {

      switch ( pOutSeqInfo->outTr.eOutTrState ) {
         case I2CDEVQUP_TR_STATE_PAD_OUTPUT       : /* start of a transfer. */
               QUP_OutFsm_PadOutputTagNext(pOutSeqInfo,&uByteVal);
               break;
         case I2CDEVQUP_TR_STATE_START_TAG       : /* start of a transfer. */
               QUP_OutFsm_StartTagNext(pOutSeqInfo,&uByteVal);
               break;
         case I2CDEVQUP_TR_STATE_SLAVE_ADDR      :
               QUP_OutFsm_SlaveAddressNext(pOutSeqInfo,&uByteVal);
               break;
         case I2CDEVQUP_TR_STATE_RD_DATA_TAG     :
               QUP_OutFsm_RdDataTagNext(pOutSeqInfo,&uByteVal);
               break;
         case I2CDEVQUP_TR_STATE_WR_DATA_TAG     :
               QUP_OutFsm_WrDataTagNext(pOutSeqInfo,&uByteVal);
               break;
         case I2CDEVQUP_TR_STATE_DATA_CNT        :
               QUP_OutFsm_DataCntNext(pOutSeqInfo,&uByteVal);
               break;
         case I2CDEVQUP_TR_STATE_DATA_VALUE      :
               QUP_OutFsm_DataValueNext(pOutSeqInfo,&uByteVal);
               break;

         default:
              /*TODO: set error sate of invalid output seq state. */
              return 0;
      }
      uSlot |= (((uint32_t)uByteVal ) << (uSlotByteIndex * 8));
      uSlotByteIndex++;
   }
   return uSlot;
}

/**
    This function performs output on the output fifo if there are free slots.

    @param[in, out] pDev  Pointer to qup device structure.
    @return         Nothing.
  */
static void __attribute__ ((noinline))
QUP_PerformOutput
(
   I2CDEVQUP_Device               *pDev
)
{
   I2CDEVQUP_QupInfo              *pQupInfo;
   I2CDEVQUP_OutSeqInfo           *pOutSeqInfo;
   uint32_t                          uSlot;

   pQupInfo = &pDev->qupInfo;
   pOutSeqInfo = &pDev->seqInfo.outSeqInfo;


   I2CDEVQUP_SetRunStateIfValid(pDev->config->virtBlockAddr,
        HAL_QUPE_RUNSTATE_PAUSE);

   /* If output is done update the state of the output sequence. */
   while ( (I2CDEVQUP_OUTPUT_FILL_FIFO == pOutSeqInfo->eOutputState) &&
          (pQupInfo->uOutFreeSlotReqCnt > pQupInfo->uOutFreeSlotServicedCnt) ) {
      uSlot = QUP_GetNextOutSeqSlot(pOutSeqInfo);
      /* push slot into output fifo. */
      HAL_qupe_PutWordIntoOutFifo(pDev->config->virtBlockAddr, uSlot);
      pQupInfo->uOutFreeSlotServicedCnt++;
   }
   I2CDEVQUP_SetRunStateIfValid(pDev->config->virtBlockAddr,
        HAL_QUPE_RUNSTATE_RUN);
}

/******************************************************************************
 * The next group of functions handle input sequence/transfer state
 * transitions.
 *****************************************************************************/

/** @brief This function moves the input transfer pointer to next transfer.

    @param[in, out] pInSeqInfo    Pointer to input sequence info structure.
    @return         Nothing.
  */
static void
QUP_InFsm_MoveNextTransfer
(
   I2CDEVQUP_InSeqInfo            *pInSeqInfo
)
{
   pInSeqInfo->uInTrCnt--;
   if ( 0 == pInSeqInfo->uInTrCnt ) {
      /* all data has been read from input fifo */
      pInSeqInfo->inTr.eInTrState = I2CDEVQUP_TR_STATE_NOT_IN_TRANSFER;
      return;
   }

   do {
      pInSeqInfo->uTrIndex++;
      pInSeqInfo->pTransfer = &pInSeqInfo->pSeq->pTransfer[pInSeqInfo->uTrIndex];
      if ( I2cTranDirIn == pInSeqInfo->pTransfer->eTranDirection ) {
         break;
      }
   } while(pInSeqInfo->uTrIndex != pInSeqInfo->uLastTrIndex);

   QUP_InSeqInitTransfer(pInSeqInfo);
}

/** @brief This function handles transfer transition from RdDataTag.

    @param[in, out] pInSeqInfo    Pointer to input sequence info structure.
    @return         Nothing.
  */
static void
QUP_InFsm_RdDataTagNext
(
   I2CDEVQUP_InSeqInfo *pInSeqInfo
)
{
   uint32_t uBytesLeft;

   if ( (pInSeqInfo->pTransfer->uTrSize -
         pInSeqInfo->inTr.uNextDataSegIndex) >
                     MAX_DATA_SEGMENT_LENGTH ) {
      pInSeqInfo->inTr.uNextDataSegIndex +=MAX_DATA_SEGMENT_LENGTH;
      /* add special condition to handle the last 1 byte segment
         make the previous segment shorter and leave 2 bytes on the last
         segment. */
      uBytesLeft = pInSeqInfo->pTransfer->uTrSize - pInSeqInfo->inTr.uNextDataSegIndex -1;
      if (1 == uBytesLeft) {
         pInSeqInfo->inTr.uNextDataSegIndex--;
      }
   }
   else {
      pInSeqInfo->inTr.uNextDataSegIndex =
              pInSeqInfo->pTransfer->uTrSize;
   }
   pInSeqInfo->inTr.eInTrState = I2CDEVQUP_TR_STATE_DATA_CNT;
}

/** @brief This function handles transfer transition from RdDataCntTag.

    @param[in, out] pInSeqInfo    Pointer to input sequence info structure.
    @return         Nothing.
  */
static void
QUP_InFsm_RdDataCntTagNext
(
   I2CDEVQUP_InSeqInfo *pInSeqInfo
)
{
   uint8_t utmpVal;

   utmpVal = (uint8_t)(pInSeqInfo->inTr.uNextDataSegIndex -
                            pInSeqInfo->inTr.uDataIndex);
   if ( 0 == utmpVal ) {
      QUP_InFsm_MoveNextTransfer(pInSeqInfo);
   } else {
      pInSeqInfo->inTr.eInTrState = I2CDEVQUP_TR_STATE_DATA_VALUE;
   }
}

/** @brief This function handles transfer transition from RdDataValue one byte at a time.

    @param[in, out] pInSeqInfo    Pointer to input sequence info structure.
    @param[out]     uByte         Data with this single byte read from this state-transition.
    @return         Nothing.
  */
static void
QUP_InFsm_RdDataValueSingleNext
(
   I2CDEVQUP_InSeqInfo *pInSeqInfo,uint8_t uByte
)
{
   uint8_t *pVal;

   if ( pInSeqInfo->inTr.IoVecBuffIndex == pInSeqInfo->inTr.pTrIOVec->uBuffSize ) {
      /* get next buffer. */
      pInSeqInfo->inTr.pTrIOVec++;
      pInSeqInfo->inTr.IoVecBuffIndex = 0;
   }
   /* gather index. */
   pVal = &pInSeqInfo->inTr.pTrIOVec->pBuff[pInSeqInfo->inTr.IoVecBuffIndex++];
   *pVal = uByte;
   pInSeqInfo->inTr.uDataIndex++;
   if ( pInSeqInfo->inTr.uDataIndex == pInSeqInfo->pTransfer->uTrSize ) {
      QUP_InFsm_MoveNextTransfer(pInSeqInfo);
   }
   else if ( pInSeqInfo->inTr.uDataIndex ==
             pInSeqInfo->inTr.uNextDataSegIndex ) {
      /* next segment. */
      pInSeqInfo->inTr.eInTrState = I2CDEVQUP_TR_STATE_RD_DATA_TAG;
   }
}

/** @brief This function advances input sequence one slot at a time.

    @param[in, out] pInSeqInfo    Pointer to input sequence info structure.
    @param[in]      uSlot         Data slot received.
    @return         Nothing.
  */
static void
QUP_ProcessNextInputSlot
(
   I2CDEVQUP_InSeqInfo            *pInSeqInfo,
   uint32_t                          uSlot
)
{
   uint32_t                          uSlotByteIndex;
   uint32_t                          uByteVal;

   uSlotByteIndex = 0;

   /* unpack slot. */
   while ( (uSlotByteIndex < 4) &&
           (I2CDEVQUP_TR_STATE_NOT_IN_TRANSFER != pInSeqInfo->inTr.eInTrState) ) {
      uByteVal = (uSlot >> (uSlotByteIndex * 8)) &0xFF;
      uSlotByteIndex++;
      switch (pInSeqInfo->inTr.eInTrState) {
         case I2CDEVQUP_TR_STATE_RD_DATA_TAG        :
               QUP_InFsm_RdDataTagNext(pInSeqInfo);
               break;
         case I2CDEVQUP_TR_STATE_DATA_CNT        :
               QUP_InFsm_RdDataCntTagNext(pInSeqInfo);
               break;
         case I2CDEVQUP_TR_STATE_DATA_VALUE      :
               QUP_InFsm_RdDataValueSingleNext(pInSeqInfo, (uint8_t) uByteVal);
               break;
         default:
               /* TODO: set error sate of invalid output seq state. */
               return;
      }
   } /* end of slot processing. */

   pInSeqInfo->uNumInBytesReceived += 4;

   if ((pInSeqInfo->uNumInBytesReceived >= pInSeqInfo->uTotalInBytes) ||
       (0 == pInSeqInfo->uInTrCnt))    {
      pInSeqInfo->eInSeqState = I2CDEVQUP_INPUT_RECEIVE_DONE;
   }
}

/**
    This function empties the input queue in block/fifo mode.

    @param[in, out] pDev  Pointer to qup device structure.
    @return         Nothing.
  */
static void
QUP_PerformInput
(
   I2CDEVQUP_Device               *pDev
)
{
   I2CDEVQUP_QupInfo              *pQupInfo;
   I2CDEVQUP_InSeqInfo            *pInSeqInfo;
   uint32_t                          uSlot;

   pQupInfo    = &pDev->qupInfo;
   pInSeqInfo  = &pDev->seqInfo.inSeqInfo;

   while ((I2CDEVQUP_INPUT_RECEIVE_FROM_INPUT_FIFO == pInSeqInfo->eInSeqState) &&
          (pQupInfo->uInFreeSlotReqCnt > pQupInfo->uInFreeSlotServicedCnt) ) {
      HAL_qupe_GetWordFromInFifo(pDev->config->virtBlockAddr, &uSlot); /* get slot from fifo. */
      QUP_ProcessNextInputSlot(pInSeqInfo, uSlot);
      pQupInfo->uInFreeSlotServicedCnt++;
   }
}

/** @brief This function Performs qup servicing.

    This function is the main entry point for qup servicing.
    It is called when events happen.

    @param[in, out] pDev   Pointer to qup device structure.
    @return         Nothing.
  */
static void
QUP_ServiceQUP
(
   I2CDEVQUP_Device *pDev
)
{
   I2CDEVQUP_QupInfo              *pQupInfo;
   I2CDEVQUP_OutSeqInfo           *pOutSeqInfo;
   I2CDEVQUP_InSeqInfo            *pInSeqInfo;
   I2CDEVQUP_QupIsrHwEvt          *pIsrEvt;
   uint32_t                        uQupErrors;
   uint32_t                        uOperational;
   uint32_t                        uOperationaSvcFlags;
   HAL_qupe_I2cStatus              i2cStatus;

   pQupInfo = &pDev->qupInfo;
   pOutSeqInfo = &pDev->seqInfo.outSeqInfo;
   pInSeqInfo  = &pDev->seqInfo.inSeqInfo;
   pIsrEvt  = pQupInfo->hwEvtQueue.pHead;


   if( I2CDEV_POWER_STATE_2 != pDev->devPowerState ) {
      return;
   }
   /* Check operating and error status.                                      */
   /* According to the HW designer both the QUP error flags and the minicore
      status register need to be read and then the interrupts can be cleared.
      If status registers are not read then the interrupt will remain set.
      I have seen this happen for the interrupts asserted by the minicore.   */
   uQupErrors   = HAL_qupe_GetErrStatusFlags(pDev->config->virtBlockAddr);
   uOperational = HAL_qupe_GetOpStatusFlags(pDev->config->virtBlockAddr);
   HAL_qupe_GetI2cState(pDev->config->virtBlockAddr, &i2cStatus);

   uOperationaSvcFlags =
       (uOperational &
       (HAL_QUPE_OPSTATE_OUTPUT_SERVICE | HAL_QUPE_OPSTATE_INPUT_SERVICE));

   /* Check if service events are set return if not. */
   if ( (!(uQupErrors & HAL_QUPE_ERRSTATE_FIELD)) &&
        (!(i2cStatus.uRawStatus & HAL_QUPE_I2C_OP_STATUS_ERROR_FIELD)) &&
        (!uOperationaSvcFlags)
      )
   {
      return;
   }

   pQupInfo->uIrqCnt++; /* Count interrupts */
   pIsrEvt->uIrqCnt = pQupInfo->uIrqCnt;
   pIsrEvt->uQupErrors   = uQupErrors;
   pIsrEvt->uOperational = uOperational;
   pIsrEvt->i2cStatus    = i2cStatus;
   pIsrEvt->uOutTranCnt  =
           HAL_qupe_GetOutTransferCountCurrentExt(
                           pDev->config->virtBlockAddr,
                           pQupInfo->eOutFifoMode,
                           pOutSeqInfo->uTotalOutBytes);
   /* do not read the current input count if no input is programmed. */
   if (pInSeqInfo->uTotalInBytes) {
      pIsrEvt->uInTranCnt   =
           HAL_qupe_GetInTransferCountCurrentExt(
                           pDev->config->virtBlockAddr,
                           pQupInfo->eInFifoMode,
                           pInSeqInfo->uTotalInBytes);
   }
   else {
      pIsrEvt->uInTranCnt   = 0;
   }

   if ( !I2CDEVQUP_QupHwEvtQueue_IsFull(&pQupInfo->hwEvtQueue) ) {
      I2CDEVQUP_QupHwEvtQueue_HeadNext(&pQupInfo->hwEvtQueue);
   }

   /* Check for errors.                                                      */
   if ( uQupErrors & HAL_QUPE_ERRSTATE_FIELD ){
      HAL_qupe_ClearErrStatusFlags(pDev->config->virtBlockAddr, uQupErrors);
   }

   if( i2cStatus.uRawStatus & HAL_QUPE_I2C_OP_STATUS_ERROR_FIELD ) {
      /* Should reset the core to protect against re-entering the ISR due to
         the same error condition being set.                              */

      HAL_qupe_ClearI2cErrors(
            pDev->config->virtBlockAddr,
            (i2cStatus.uRawStatus & HAL_QUPE_I2C_OP_STATUS_ERROR_FIELD));
   }
   if ( uOperationaSvcFlags ) {
      HAL_qupe_ClearOpStatusFlags(
          pDev->config->virtBlockAddr,
          uOperationaSvcFlags);
   }
}

/** @brief Configures the device.

    This function configures the device

    @param[in] pDev         Pointer to device

    @return          int32_t .
  */
static int32_t
I2CDEVQUP_SetupHw
(
   I2CDEVQUP_Device *pDev
)
{
   int32_t res;

   HAL_qupe_Init(pDev->config->virtBlockAddr, NULL);

   res = I2CDEVQUP_WaitForRunStateValid(pDev->config->virtBlockAddr);
   if ( I2C_RES_SUCCESS != res ) {
      return res;
   }

   HAL_qupe_GetHwInfo(pDev->config->virtBlockAddr, &pDev->devHwInfo);

   HAL_qupe_Configure(pDev->config->virtBlockAddr, pDev->miniCfg == MINICORE_SMBUS);

   pDev->devInitState |= I2CDEVQUP_InitState_HardwareInit_Done;

   return I2C_RES_SUCCESS;
}

static bool QUP_FreeI2cBus
(
   I2CDEVQUP_Device               *pDev
)
{
   if ( !HAL_qupe_IsI2CBusBusy(pDev->config->virtBlockAddr) ) {
      return true;
   }
   /* clear bus resets the core in virtio. */
   HAL_qupe_ClearI2CBus(pDev->config->virtBlockAddr);
   udelay(pDev->clntCfg.uByteTransferTimeoutUs);
   HAL_qupe_Configure(pDev->config->virtBlockAddr, pDev->miniCfg == MINICORE_SMBUS);
   return (!HAL_qupe_IsI2CBusBusy(pDev->config->virtBlockAddr));
}

static bool
QUP_IsTransferFinished(I2CDEVQUP_Device *pDev,
                       I2CDEVQUP_SequenceIOInfo *pSeqInfo)
{
   if ( I2C_RES_SUCCESS != pDev->seqInfo.ioRes.nOperationResult ) {
      return true;
   }
   else if ( (I2CDEVQUP_OUTPUT_TRANSMIT_DONE ==
              pSeqInfo->outSeqInfo.eOutputState) &&
             (0 == pSeqInfo->inSeqInfo.uTotalInBytes) ) {
      return true;
   }
   else if ( (I2CDEVQUP_OUTPUT_TRANSMIT_DONE ==
              pSeqInfo->outSeqInfo.eOutputState) &&
             (I2CDEVQUP_INPUT_RECEIVE_DONE ==
              pSeqInfo->inSeqInfo.eInSeqState) ) {
      return true;
   }

   return false;
}

/** @brief Initializes output sequence info structures.

    Initializes output sequence info structures.

    @param[out] pOutSeqInfo   Pointer to out sequence struct.

    @return                   Nothing.
  */
void
I2CDEVQUP_InitOutSeqInfo
(
   I2CDEVQUP_OutSeqInfo           *pOutSeqInfo
)
{
   pOutSeqInfo->pTransfer    = NULL;
   pOutSeqInfo->uOutTrCnt    = 0;
   pOutSeqInfo->uTrIndex     = 0;
   pOutSeqInfo->eOutputState = I2CDEVQUP_OUTPUT_FILL_FIFO;
   pOutSeqInfo->uCurOutBytes  = 0;
   pOutSeqInfo->uNumOutDtBytes = 0;
   pOutSeqInfo->uTotalOutBytes = 0;
}

/** @brief Initializes input sequence info structures.

    Initializes input sequence info structures.

    @param[out] pInSeqInfo    Pointer to input info sequence.

    @return                   Nothing.
  */
void
I2CDEVQUP_InitInSeqInfo
(
   I2CDEVQUP_InSeqInfo            *pInSeqInfo
)
{
   pInSeqInfo->uNumInBytesReceived      = 0;
   pInSeqInfo->eInSeqState              = I2CDEVQUP_INPUT_IDLE;
   pInSeqInfo->pTransfer                = NULL;
   pInSeqInfo->uInTrCnt                 = 0;
   pInSeqInfo->uTrIndex                 = 0;
   pInSeqInfo->uLastTrIndex             = 0;
   pInSeqInfo->uNumInDtBytes            = 0;
   pInSeqInfo->uTotalInBytes            = 0;
   pInSeqInfo->uInPadCnt                = 0;
}

void I2CDEVQUP_ConfigureSequenceTransferIo(I2CDEVQUP_Device *pDev,
                                           I2cSequence *pSeq)
{
   I2CDEVQUP_SequenceIOInfo *pSeqInfo;
   I2CDEVQUP_OutSeqInfo *pOutSeqInfo;
   I2CDEVQUP_InSeqInfo *pInSeqInfo;
   uint32_t uTranIndex;
   I2cTransfer *pTransfer;
   uint32_t uNumInBytes, uNumOutBytes;
   uint32_t uPadCnt;
#if 0
   bool bSplitTransfer = false;
#endif

   pSeqInfo = &pDev->seqInfo;
   pOutSeqInfo = &pDev->seqInfo.outSeqInfo;
   pInSeqInfo  = &pDev->seqInfo.inSeqInfo;

   pSeqInfo->pTransfer              = pSeq->pTransfer;
   pSeqInfo->uNumTransfers          = pSeq->uNumTransfers;
   pSeqInfo->ioRes.uInByteCnt       = pSeqInfo->ioRes.uOutByteCnt = 0;
   pSeqInfo->ioRes.nOperationResult = I2C_RES_SUCCESS;

   pSeqInfo->eSeqState              = I2CDEVQUP_SEQSTATE_INPUT_OUTPUT;

   I2CDEVQUP_InitOutSeqInfo(pOutSeqInfo);
   pOutSeqInfo->pTransfer       = pSeqInfo->pTransfer;
   pOutSeqInfo->uOutTrCnt       = pSeqInfo->uNumTransfers;
   QUP_OutSeqInitTransfer(pOutSeqInfo);

   I2CDEVQUP_InitInSeqInfo(pInSeqInfo);

   pTransfer = pOutSeqInfo->pTransfer; /* get first transfer. */

#if 0
   if ((pTransfer->eTranCtxt != I2cTrCtxNotASequence) &&
       (pSeqInfo->uNumTransfers == 1)) {
      bSplitTransfer = true;
   }
#endif

   for (uTranIndex = 0; uTranIndex < pSeqInfo->uNumTransfers; uTranIndex++) {
      pTransfer = &pSeq->pTransfer[uTranIndex]; /* get transfer */

      if ( I2cTranDirIn == pTransfer->eTranDirection ) {
         pInSeqInfo->uInTrCnt++;
         if ( 1 == pInSeqInfo->uInTrCnt ) { /* first read of the sequence. */
            pInSeqInfo->pTransfer   = pTransfer;  /* first read transfer. */
            pInSeqInfo->eInSeqState = I2CDEVQUP_INPUT_RECEIVE_FROM_INPUT_FIFO;
            pInSeqInfo->uTrIndex    = uTranIndex;
            QUP_InSeqInitTransfer(pInSeqInfo);
         }
         /* If single byte input transfer then pad so that it starts at
          * slot boundary */
         if ( (1 == pTransfer->uTrSize) && (pOutSeqInfo->uTotalOutBytes & 0x3)
            ) {
            /* Pad to slot boundary. */
            uPadCnt = ((4 - (pOutSeqInfo->uTotalOutBytes & 0x3)) & 0x3);
            pOutSeqInfo->uTotalOutBytes += uPadCnt;
            //pInSeqInfo->uTotalInBytes   += uPadCnt;
         }
         pInSeqInfo->uLastTrIndex = uTranIndex;
         pInSeqInfo->uNumInDtBytes += pTransfer->uTrSize;
      }
      else {
         pOutSeqInfo->uNumOutDtBytes += pTransfer->uTrSize;
      }
      I2CDEVQUP_CalcTransferInOutSize(pTransfer,&uNumInBytes, &uNumOutBytes);
      pInSeqInfo->uTotalInBytes   += uNumInBytes;
      pOutSeqInfo->uTotalOutBytes += uNumOutBytes;
   }

   pSeqInfo->uSeqTimeoutUs =
         (pInSeqInfo->uTotalInBytes + pOutSeqInfo->uTotalOutBytes) *
         (9000/pDev->clntCfg.uBusFreqKhz);
   // 25ms timeout for SMBus
   if ( 1 == pDev->seqInfo.pTransfer->uIsSmbus ) {
      pSeqInfo->uSeqTimeoutUs += (25*1000);
   }
   else {
      pSeqInfo->uSeqTimeoutUs += pDev->clntCfg.uByteTransferTimeoutUs;
   }
}

/** @brief Waits for completion.
    @param[in] pDev         Pointer to qup device structure.
    @return                 Nothing.
  */
static void QUP_WaitForCompletion(I2CDEVQUP_Device *pDev)
{
    I2CDEVQUP_SequenceIOInfo *pSeqInfo;
    uint32_t uTmpTimeout;
    bool bTimeout = false;

    pSeqInfo = &pDev->seqInfo;
    uTmpTimeout = pSeqInfo->uSeqTimeoutUs;
    // loop until either an event happens or timeout
    while( (!QUP_IsTransferFinished(pDev, pSeqInfo)) &&
            (!bTimeout) ) {
        QUP_ServiceQUP(pDev);

        QUP_PerformInputOutput(pDev);
        if ( I2C_RES_SUCCESS != pDev->seqInfo.ioRes.nOperationResult ) {
            break;
        }

        udelay(QUP_BUSY_WAIT_STEP_US);
        if ( uTmpTimeout > QUP_BUSY_WAIT_STEP_US ) {
            uTmpTimeout -= QUP_BUSY_WAIT_STEP_US;
        }
        else {
            bTimeout = true;
        }
    }

    if ( bTimeout ) { // set error code.
        I2CDEV_AbortTransfer(pDev);
    }
}

I2cResult I2CDEVQUP_ConfigureQupIo(I2CDEVQUP_Device *pDev)
{
    int32_t res;
    I2CDEVQUP_OutSeqInfo *pOutSeqInfo;
    I2CDEVQUP_InSeqInfo *pInSeqInfo;
    I2CDEVQUP_QupInfo *pQupInfo;
    I2CDEVQUP_SequenceIOInfo *pSeqInfo;
    I2cTransfer *pTransfer;
    bool bSplitTransfer = false;
    bool bConfigureDuringRun = false;

    pQupInfo = &pDev->qupInfo;
    pOutSeqInfo = &pDev->seqInfo.outSeqInfo;
    pInSeqInfo  = &pDev->seqInfo.inSeqInfo;
    pSeqInfo = &pDev->seqInfo;
    pTransfer = pSeqInfo->pTransfer;

    if ((pTransfer->eTranCtxt != I2cTrCtxNotASequence) &&
            (pSeqInfo->uNumTransfers == 1)) {
        bSplitTransfer = true;
        if (pTransfer->eTranCtxt != I2cTrCtxSeqStart)
        {
            bConfigureDuringRun = true;
        }
    }

    if (!bSplitTransfer) {
        /* Set Reset run state. */
        res = I2CDEVQUP_SetRunStateIfValid(pDev->config->virtBlockAddr,
                HAL_QUPE_RUNSTATE_RESET);
        if( I2C_RES_SUCCESS != res ) {
            I2CDEVQUP_ResetQupCore(pDev);
            return res;
        }
    }

   I2CDEVQUP_QupHwEvtQueue_Init(&pQupInfo->hwEvtQueue);
   pQupInfo->uIrqCnt                           = 0;

    pQupInfo->uInFreeSlotReqCnt                 = 0;
    pQupInfo->uOutFreeSlotReqCnt                = 0;
    pQupInfo->uQupErrors                        = 0;
    pQupInfo->uOperational                      = 0;
    pQupInfo->i2cStatus.uRawStatus              = 0;
    pQupInfo->i2cStatus.uRawLineState           = 0;

    pQupInfo->uInFreeSlotServicedCnt            = 0;
    pQupInfo->uOutFreeSlotServicedCnt           = 0;

    /* We use block mode for transfers that are sent separately to the core
     * and we need to end them without a stop. When we have only one transfer
     * and it is not of type NotASequence, it means that we are dealing with
     * separate transfers that require to end without a STOP. This condition
     * is checked for both INPUT and OUTPUT mode configurations */

    if ((((pOutSeqInfo->uTotalOutBytes+3)/4) > pDev->devHwInfo.uNumOutputSlots) ||
            bSplitTransfer) {
        /* block mode. */
        pQupInfo->eOutFifoMode = HAL_QUPE_IO_MODE_BLOCK;
    }
    else {
        /* fifo mode. */
        pQupInfo->eOutFifoMode = HAL_QUPE_IO_MODE_FIFO;
        pQupInfo->uOutFreeSlotReqCnt  = pDev->devHwInfo.uNumOutputSlots;
        pQupInfo->uOutFreeSlotReqCnt = pDev->devHwInfo.uNumOutputSlots;
    }

    if ((((pInSeqInfo->uTotalInBytes+3)/4) > pDev->devHwInfo.uNumInputSlots) ||
            bSplitTransfer) {
        pQupInfo->eInFifoMode = HAL_QUPE_IO_MODE_BLOCK;
    }
    else {
        pQupInfo->eInFifoMode = HAL_QUPE_IO_MODE_FIFO;
    }

    // TODO: Call a HAL API
    if (bSplitTransfer && (I2cTranDirOut == pTransfer->eTranDirection))
    {
        QUPE_OUTF(pDev->config->virtBlockAddr, QUP_CONFIG, NO_INPUT, 1);
    }
    else
    {
        QUPE_OUTF(pDev->config->virtBlockAddr, QUP_CONFIG, NO_INPUT, 0);
    }

    HAL_qupe_SetIoModeExt(pDev->config->virtBlockAddr,
            pQupInfo->eOutFifoMode, pQupInfo->eInFifoMode,
            false, true, true);

    res = HAL_qupe_SetOutTransferCountExt(pDev->config->virtBlockAddr,
            pQupInfo->eOutFifoMode,
            pOutSeqInfo->uTotalOutBytes,
            bConfigureDuringRun);
    if ( I2C_RES_SUCCESS != res ) {
        return res;
    }

    res = HAL_qupe_SetInTransferCountExt(pDev->config->virtBlockAddr,
            pQupInfo->eInFifoMode,
            pInSeqInfo->uTotalInBytes,
            bConfigureDuringRun);
    if ( I2C_RES_SUCCESS != res ) {
        return res;
    }

      /* enable interrupts. */
      HAL_qupe_SetIrqMask(pDev->config->virtBlockAddr,0);

    res = HAL_qupe_SetI2cConfig(pDev->config->virtBlockAddr,
            HAL_QUPE_I2C_TAGS_V2,
            pDev->config->appClkFreqKhz,
            pDev->clntCfg.uBusFreqKhz);
    if( I2C_RES_SUCCESS != res )
    {
        I2CDEVQUP_ResetQupCore(pDev);
        I2CDEVQUP_SetRunStateIfValid(pDev->config->virtBlockAddr,
                HAL_QUPE_RUNSTATE_RESET);
        return res;
    }

    /* The state is reset as set at the beggining of the function.
     * This avoids an extra register read. */
    res = I2CDEVQUP_SetRunState(pDev->config->virtBlockAddr,
            HAL_QUPE_RUNSTATE_RUN);
    if( I2C_RES_SUCCESS != res )
    {
        pSeqInfo->eSeqState = I2CDEVQUP_SEQSTATE_QUP_STATE_ERROR;
        I2CDEVQUP_ResetQupCore(pDev);
        I2CDEVQUP_SetRunStateIfValid(pDev->config->virtBlockAddr,
                HAL_QUPE_RUNSTATE_RESET);
        return res;
    }

    return I2C_RES_SUCCESS;
}

// Attempt to parse registers to give more clarity into return codes
static I2cResult UpdateResultWithData(uint32_t nOpResult)
{
    if ( 0 != (I2C_RES_ERROR_CLS_I2C_CORE & nOpResult) )
    {
        switch ((HAL_QUPE_I2C_OP_STATUS_FAILED & nOpResult) >> 6)
        {
            case 0x00: // No error
                return nOpResult;
            case 0x01: // Byte n transmitted successfully, byte n+1 errored:
                       // type of error indicated in other STATUS bits.
                       //   (queued invalid write, for example)
            case 0x02: // Byte n errored: type of error indicated in other
                       // STATUS bits, byte n+1 to begin transmission
                       // (byte n+1 would have to be a valid address byte for
                       //   this condition to occur)
            case 0x03: // Byte n errored: type of error indicated in other
                       //STATUS bits, byte n+1 discarded as well
                       // (if the byte was a data byte destined for a NACKed
                       //   address, data is useless, therefore discarded)
                if (nOpResult & HAL_QUPE_I2C_OP_STATUS_PACKET_NACKED)
                    return I2CDEVQUP_ERR_PACKET_NACKED;
                if (nOpResult & HAL_QUPE_I2C_OP_STATUS_INVALID_READ_ADDR)
                    return I2CDEVQUP_ERR_NACK_IN_TRANSFER;
                if (nOpResult & HAL_QUPE_I2C_OP_STATUS_BUS_ERROR)
                    return I2CDEVQUP_ERR_UNEXPECTED_START_STOP;
                if (nOpResult & HAL_QUPE_I2C_OP_STATUS_INVALID_WRITE)
                    return I2CDEVQUP_ERR_INVALID_WRITE;
                return nOpResult;
        }
    }
    return nOpResult;
}

/*-------------------------------------------------------------------------
 * Externalized Function Definitions
 * ----------------------------------------------------------------------*/
I2cResult I2CDEV_Read(I2CDEVQUP_Device *pDev,
                      I2cTransfer *pTransfer,
                      I2cClientConfig *pClntCfg,
                      uint32_t *puNumCompleted)
{
   int32_t res = I2C_RES_SUCCESS;
   uint32_t uWhileOnce = 0;
   I2cSequence seq;

   do {
      if ( pTransfer->eTranDirection != I2cTranDirIn ) {
         res = I2CDEVQUP_ERR_INVALID_TRANSFER_DIRECTION;
         break;
      }

      if( I2CDEV_POWER_STATE_2 != pDev->devPowerState ) {
        res = I2CDEVQUP_ERR_INVALID_POWER_STATE;
        break;
      }
      if ( 0 == (pDev->devInitState & I2CDEVQUP_InitState_HardwareInit_Done) ) {
         res = I2CDEVQUP_SetupHw(pDev);
         if ( I2C_RES_SUCCESS != res ) {
            break;
         }
      }

      // Run free i2c  bus if this isn't a split transfer
      if (pTransfer->eTranCtxt == I2cTrCtxNotASequence) {
         if ( !QUP_FreeI2cBus(pDev) ) {
            res = I2CDEVQUP_ERR_BUS_BUSY;
            break;
         }
      }

      /* check if client configuration changed. */
      if ( NULL != pClntCfg ) {
         pDev->clntCfg = *pClntCfg;
      }

      seq.pTransfer = pTransfer;
      seq.uNumTransfers = 1;
      I2CDEVQUP_ConfigureSequenceTransferIo(pDev, &seq);
      res = I2CDEVQUP_ConfigureQupIo(pDev);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
      QUP_PerformInputOutput(pDev);
      QUP_WaitForCompletion(pDev);
      *puNumCompleted = pDev->seqInfo.ioRes.uInByteCnt;
   } while(uWhileOnce);

   if ( I2C_RES_SUCCESS != res ) {
     pDev->seqInfo.ioRes.nOperationResult = res;
   }

   return UpdateResultWithData(pDev->seqInfo.ioRes.nOperationResult);
}

I2cResult I2CDEV_DeInit(I2CDEVQUP_Device *pDev)
{
    int32_t res = I2C_RES_SUCCESS;

    if ( NULL == pDev ) {
        return I2C_RES_SUCCESS;
    }

    res = I2CPLATDEV_DeInitTarget(pDev);
    return res;
}

I2cResult I2CDEV_Init(I2CDEVQUP_Device *pDev)
{
   int32_t res = I2C_RES_SUCCESS;
   uint32_t uWhileOnce = 0;

   pDev->devInitState = I2CDEVQUP_InitState_Uninitialized;

   do {


      pDev->config = i2c_get_device(pDev->dev);
          if ( NULL == pDev->config ) {
              res = I2CPLATSVC_ERROR_INVALID_DEV_ID;
          }

      if ( I2C_RES_SUCCESS != res ) {
         break;
      }

      pDev->seqInfo.outSeqInfo.pSeq        = &pDev->seqInfo;
      pDev->seqInfo.inSeqInfo.pSeq         = &pDev->seqInfo;
      pDev->clntCfg.uBusFreqKhz            = I2CDEVQUP_DEFAULT_BUS_FREQ_KHZ;
      pDev->clntCfg.uByteTransferTimeoutUs =
         I2CDEVQUP_DEFAULT_BYTE_TRANSFER_TIMEOUT_US;
      pDev->devInitState |= I2CDEVQUP_InitState_DeviceInit_Done;
      pDev->devPowerState = I2CDEV_POWER_STATE_0;
   } while ( uWhileOnce );

   if ( I2C_RES_SUCCESS != res ) { /* in case of error undo initialization. */
      I2CDEV_DeInit(pDev);
   }
   return res;
}

I2cResult I2CDEV_Write(I2CDEVQUP_Device *pDev,
                       I2cTransfer *pTransfer,
                       // if null keep previous
                       I2cClientConfig *pClntCfg,
                       uint32_t *puNumCompleted)
{
   int32_t res = I2C_RES_SUCCESS;
   uint32_t uWhileOnce = 0;
   I2cSequence seq;

   do {
      if ( pTransfer->eTranDirection != I2cTranDirOut ) {
         res = I2CDEVQUP_ERR_INVALID_TRANSFER_DIRECTION;
         break;
      }

      if( I2CDEV_POWER_STATE_2 != pDev->devPowerState ) {
        res = I2CDEVQUP_ERR_INVALID_POWER_STATE;
        break;
      }

      if ( 0 == (pDev->devInitState & I2CDEVQUP_InitState_HardwareInit_Done) ) {
         res = I2CDEVQUP_SetupHw(pDev);
         if ( I2C_RES_SUCCESS != res ) {
            break;
         }
      }

      // Run free i2c  bus if this isn't a split transfer
      if (pTransfer->eTranCtxt == I2cTrCtxNotASequence) {
          if ( !QUP_FreeI2cBus(pDev) ) {
             res = I2CDEVQUP_ERR_BUS_BUSY;
             break;
          }
      }

      /* check if client configuration changed. */
      if ( NULL != pClntCfg ) {
         pDev->clntCfg = *pClntCfg;
      }

      seq.pTransfer = pTransfer;
      seq.uNumTransfers = 1;
      I2CDEVQUP_ConfigureSequenceTransferIo(pDev, &seq);
      res = I2CDEVQUP_ConfigureQupIo(pDev);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
      QUP_PerformInputOutput(pDev);
      QUP_WaitForCompletion(pDev);
      *puNumCompleted = pDev->seqInfo.ioRes.uOutByteCnt;
   } while ( uWhileOnce );

   if ( I2C_RES_SUCCESS != res ) {
     pDev->seqInfo.ioRes.nOperationResult = res;
   }

   return UpdateResultWithData(pDev->seqInfo.ioRes.nOperationResult);
}

I2cResult I2CDEV_BatchTransfer(I2CDEVQUP_Device *pDev,
                               I2cSequence *pSequence,
                               // if null keep previous
                               I2cClientConfig *pClntCfg,
                               I2cIoResult *pIoRes)
{
   int res = I2C_RES_SUCCESS;
   uint32_t uWhileOnce = 0;

   pDev->miniCfg = pSequence->pTransfer->uIsSmbus ?
       MINICORE_SMBUS : MINICORE_I2C;
   HAL_qupe_Configure(pDev->config->virtBlockAddr, pDev->miniCfg == MINICORE_SMBUS);

   do {
      if ( I2CDEV_POWER_STATE_2 != pDev->devPowerState ) {
        res =  I2CDEVQUP_ERR_INVALID_POWER_STATE ;
        break;
      }
      if ( 0 == (pDev->devInitState & I2CDEVQUP_InitState_HardwareInit_Done) ) {
         res = I2CDEVQUP_SetupHw(pDev);
         if ( I2C_RES_SUCCESS != res ) {
            break;
         }
      }

      // Run free i2c  bus if this isn't a split transfer
      if (pSequence->pTransfer->eTranCtxt == I2cTrCtxNotASequence) {
         if ( !QUP_FreeI2cBus(pDev) ) {
            res = I2CDEVQUP_ERR_BUS_BUSY;
            break;
         }
      }

      /* check if client configuration changed. */
      if ( NULL != pClntCfg ) {
         pDev->clntCfg = *pClntCfg;
      }

      I2CDEVQUP_ConfigureSequenceTransferIo(pDev, pSequence);
      res = I2CDEVQUP_ConfigureQupIo(pDev);
      if ( I2C_RES_SUCCESS != res ) {
         break;
      }
      QUP_PerformInputOutput(pDev);
      QUP_WaitForCompletion(pDev);
      *pIoRes = pDev->seqInfo.ioRes;
   } while ( uWhileOnce );

   if ( I2C_RES_SUCCESS != res ) {
     pDev->seqInfo.ioRes.nOperationResult = res;
   }

   return UpdateResultWithData(pDev->seqInfo.ioRes.nOperationResult);
}

static int32_t I2CDEV_AbortTransfer(I2CDEVQUP_Device *pDev)
{
   I2CDEVQUP_SequenceIOInfo *pSeqInfo;
   I2cTransfer *pTransfer;
   HAL_qupe_RunStateType eRunState;
   bool bSkipBusClear = false;

   pSeqInfo = &pDev->seqInfo;
   pTransfer = pSeqInfo->pTransfer;

   eRunState = HAL_qupe_GetRunState(pDev->config->virtBlockAddr);

   /* No point of all this if we are already in RESET state */
   if ((eRunState != HAL_QUPE_RUNSTATE_RESET) &&
       (pSeqInfo->eSeqState != I2CDEVQUP_SEQSTATE_COMPLETE))
   {
      /* Try to gracefully stop at data boundary. */
      I2CDEVQUP_SetRunState(pDev->config->virtBlockAddr,
            HAL_QUPE_RUNSTATE_PAUSE);

      /* CHECK: We still see a Bus Clear and STOP on the fly. If multiple
       * transfers are queued and we paused the core just around the end of one
       * of the transfers, then the bus may already be idle, but we do not know
       * what condition to query to determine that. If you see a stray bus clear
       * and STOP without any START bit, you need to add a logic here */

      /* A PAUSE will let core transfer a couple more bytes and CLK goes to
       * FORCED_LOW_STATE. Note that if we did not reach FORCED_LOW, it means
       * that we have already waited for the clock-stretch amount of time that
       * wsa configured */
      QUP_WaitForI2cBusClkForcedLow(pDev);

      QUP_UpdateTransferCnt(pDev);
      I2CDEVQUP_CalcTransferredDataBytes(pDev);
      pDev->seqInfo.ioRes.nOperationResult = I2C_RES_ERROR_CLS_QUP_DEV_TIMEOUT |
         HAL_qupe_Pack28_OperationalState(pDev->config->virtBlockAddr);

      /* I see that slave stretches the clock here right after the address is
       * sent out on the bus. In this case, we may prematurely put the core into
       * RUN state and that results in BUS ERROR. We must wait for the clock
       * stretch amount of time before doing anything. DATA_STATE is
       * TX_ADDR_STATE at this point. We will check for that.  Note that in this
       * case the core does send out 9 clocks irrespective or a read/write
       * transfer, so we will skip the bus clear.
       */

      if (HAL_qupe_GetI2cDataState(pDev->config->virtBlockAddr) ==
          HAL_QUPE_I2C_DATA_TX_ADDR_STATE)
      {
         udelay(pDev->clntCfg.uByteTransferTimeoutUs);
         bSkipBusClear = true;
      }

      I2CDEVQUP_SetRunState(pDev->config->virtBlockAddr,
            HAL_QUPE_RUNSTATE_RESET);

      QUP_WaitForI2cBusFree(pDev);

      if ((pTransfer->eTranDirection == I2cTranDirIn) &&
          (bSkipBusClear == false))
      {
         /* Bus Clear will not work if core is not in RUN STATE */
         I2CDEVQUP_SetRunState(pDev->config->virtBlockAddr,
               HAL_QUPE_RUNSTATE_RUN);

         /* We need to do Bus Clear especially to handle Read termination */
         HAL_qupe_ClearI2CBus(pDev->config->virtBlockAddr);

         QUP_WaitForI2cBusFree(pDev);
      }
   }
   else
   {
      pSeqInfo->ioRes.nOperationResult = I2C_RES_ERROR_CLS_QUP_DEV_TIMEOUT |
         HAL_qupe_Pack28_OperationalState(pDev->config->virtBlockAddr);
   }

   pSeqInfo->eSeqState = I2CDEVQUP_SEQSTATE_COMPLETE;
   return I2C_RES_SUCCESS;
}

I2cResult I2CDEV_SetPowerState(I2CDEVQUP_Device *pDev,
                               I2CDEV_PowerStates ePowerState)
{
   int32_t res  = I2C_RES_SUCCESS;
   uint32_t uWhileOnce = 0;

   if( NULL == pDev) {
      return I2CDEVQUP_ERR_INVALID_DEV_HANDLE;
   }

   do
   {
      res = I2CPLATDEV_SetPowerState(pDev, ePowerState);
      if ( I2C_RES_SUCCESS == res ) {
         pDev->devPowerState = ePowerState;
      }
   } while ( uWhileOnce );
   return res;
}

int32_t I2CDEV_GetPowerState(I2CDEVQUP_Device *pDev,
                             I2CDEV_PowerStates *pePowerState)
{
   int32_t res = I2C_RES_SUCCESS;

   if (NULL == pDev) {
      return I2CDEVQUP_ERR_INVALID_DEV_HANDLE;
   }

   *pePowerState = pDev->devPowerState;
   return res;
}

int32_t I2CDEV_Reset(I2CDEVQUP_Device *pDev)
{
    return QUP_ForceClearBus(pDev);
}

#define HAL_QUPE_ASSERT(...)
#define HAL_QUPE_TRANSFER_SIZE                          8
#define HAL_QUPE_TRANSFER_SIZE_SMBUS                    8
#define HAL_QUPE_MIN_FS_DIV_VAL                         3
#define HAL_QUPE_MIN_HS_DIV_VAL                         3

void
HAL_qupe_Configure_ConfigOnly
(
    uint8_t *pQupAddr
)
{
    QUPE_OUTF(pQupAddr, QUP_CONFIG, MINI_CORE, HAL_QUPE_MINI_CORE_I2C_MASTER);
    QUPE_OUTF(pQupAddr, QUP_CONFIG, N, (HAL_QUPE_TRANSFER_SIZE - 1));
}
void
HAL_qupe_Configure_I2cMasterConfig
(
    uint8_t *pQupAddr
)
{
    QUPE_OUTF(pQupAddr, I2C_MASTER_CONFIG, EN_VERSION_TWO_TAG, 1);
}
/** @brief Configures the mini core for smbus use.
    @param[in]  pQupAddr Qup Block address.
    @return Nothing.
  */
void
HAL_qupe_Configure
(
    uint8_t                      *pQupAddr,
    uint32_t                     SMBusEnabled
)
{
    SMBusEnabled = 0; //Temporarily disable SMBus mode until we get it fully working
    if ( 1 == SMBusEnabled ) {
        QUPE_OUTF(pQupAddr, QUP_CONFIG, MINI_CORE, HAL_QUPE_MINI_CORE_SMBUS_MASTER);
        QUPE_OUTF(pQupAddr, QUP_CONFIG, N, (HAL_QUPE_TRANSFER_SIZE_SMBUS - 1));
    }
    else {
        QUPE_OUTF(pQupAddr, QUP_CONFIG, MINI_CORE, HAL_QUPE_MINI_CORE_I2C_MASTER);

        QUPE_OUTF(pQupAddr, QUP_CONFIG, N, (HAL_QUPE_TRANSFER_SIZE - 1));
    }

    QUPE_OUTF(pQupAddr, QUP_IO_MODES, OUTPUT_BIT_SHIFT_EN, 0);
    QUPE_OUTF(pQupAddr, QUP_IO_MODES, PACK_EN, 1);
    QUPE_OUTF(pQupAddr, QUP_IO_MODES, UNPACK_EN, 1);
    QUPE_OUTF(pQupAddr, QUP_CONFIG, EN_EXT_OUT_FLAG, 0);
    QUPE_OUTF(pQupAddr, QUP_CONFIG, FIFO_CLK_GATE_EN, 1);
    QUPE_OUTF(pQupAddr, QUP_CONFIG, CORE_CLK_ON_EN, 1);
    QUPE_OUTF(pQupAddr, QUP_CONFIG, APP_CLK_ON_EN, 1);
    QUPE_OUTF(pQupAddr, QUP_OPERATIONAL_MASK, INPUT_SERVICE_MASK, 0); //en QUP irqs
    QUPE_OUTF(pQupAddr, QUP_OPERATIONAL_MASK, OUTPUT_SERVICE_MASK, 0); //en QUP irqs
    QUPE_OUTF(pQupAddr, I2C_MASTER_CONFIG, EN_VERSION_TWO_TAG, 1);

    HAL_qupe_SetOutputFifoEnabled(pQupAddr,1);
    HAL_qupe_SetInputFifoEnabled(pQupAddr,1);
}

/** @brief Performs flush for i2c use.
    @param[in]  pQupAddr Qup Block address.
    @return success.
  */
HAL_qupe_ResultType
HAL_qupe_I2cFlush
(
    uint8_t *pQupAddr
)
{
    QUPE_OUTF(pQupAddr, QUP_STATE, I2C_FLUSH, 1);
    return HAL_QUPE_RESULT_SUCCESS;
}

/** @brief Sets the fast standard clock given the input clock freq in KHz.
    @param[in]  pQupAddr Qup Block address.
    @param[in]  eI2cTags       Tag version.
    @param[in]  uInputClockKhz Input clock to the i2c core in KHz.
    @param[in]  uI2cBusClockReqKhz Requested clock in KHz.
                I2C freq in KHz.

    @return HAL_QUPE_RESULT_SUCCESS if successful, error code otherwise.
  */
HAL_qupe_ResultType
HAL_qupe_SetI2cConfig
(
    uint8_t                      *pQupAddr,
    const HAL_qupe_I2cTagType  eI2cTags,
    const uint32_t               uInputClockKhz,
    const uint32_t               uI2cBusClockReqKhz
)
{
    uint32_t uRegVal;
    uint32_t uFsDivider, uHsDivider;
    uint32_t uNoiseRejection;
    uint32_t uFSBusFreqKHz;
    uint32_t uRem;
    uint32_t uDenominator;


   uRegVal = 0;

   if ( uI2cBusClockReqKhz > HAL_QUPE_HS_FREQ_KHZ_MAX ) {
       return HAL_QUPE_RESULT_INVALID_I2C_FREQ;
   }

   uNoiseRejection = (1 << QUPE_SHFT(I2C_MASTER_CLK_CTL, SDA_NOISE_REJECTION)) |
                     (1 << QUPE_SHFT(I2C_MASTER_CLK_CTL, SCL_NOISE_REJECTION));

   if ( uI2cBusClockReqKhz <= HAL_QUPE_FS_FREQ_KHZ_MAX ) {
      uFSBusFreqKHz = uI2cBusClockReqKhz;
   }
   else {
      uFSBusFreqKHz = 400; // default master code freq
      uDenominator = 3*uI2cBusClockReqKhz;
      uHsDivider = uInputClockKhz/uDenominator - 1;
      uRem       = uInputClockKhz % uDenominator;
      if (2*uRem > uDenominator) { // bigger than 1/2 then adjust
         uHsDivider++;
      }

      if ( uHsDivider < HAL_QUPE_MIN_HS_DIV_VAL ) {
         return HAL_QUPE_RESULT_INVALID_HS_DIVIDER;
      }
      uRegVal |= (uHsDivider << QUPE_SHFT(I2C_MASTER_CLK_CTL, HS_DIVIDER_VALUE) &
                QUPE_FMSK(I2C_MASTER_CLK_CTL, HS_DIVIDER_VALUE));
   }

   uFsDivider = uInputClockKhz/(2*uFSBusFreqKHz) - 3;

   /* The lowest scaler should be 3 */
   if ( uFsDivider < HAL_QUPE_MIN_FS_DIV_VAL ) {
      return HAL_QUPE_RESULT_INVALID_FS_DIVIDER;
   }

    uRegVal |= (uFsDivider << QUPE_SHFT(I2C_MASTER_CLK_CTL, FS_DIVIDER_VALUE) &
                QUPE_FMSK(I2C_MASTER_CLK_CTL, FS_DIVIDER_VALUE));

    uRegVal |= uNoiseRejection;

    QUPE_OUT(pQupAddr, I2C_MASTER_CLK_CTL, uRegVal);

    return HAL_QUPE_RESULT_SUCCESS;
}

/** @brief Issues bus clear cmd that is 9 clock cycles.
    @param[in]  pQupAddr index of the qup.
    @return Nothing.
  */
void
HAL_qupe_ClearI2CBus
(
    uint8_t  *pQupAddr
)
{
    QUPE_OUT(pQupAddr, I2C_MASTER_BUS_CLEAR, 1);
}

bool
HAL_qupe_IsI2CBusClear
(
    uint8_t *pQupAddr
)
{
    return (0==(HWIO_I2C_MASTER_BUS_CLEAR_CLEAR_BMSK &
               QUPE_IN(pQupAddr, I2C_MASTER_BUS_CLEAR)));
}

/** @brief Checks if bus is clear.
    @param[in]  pQupAddr index of the qup.
    @return Nothing.
  */
bool
HAL_qupe_IsI2CBusClkForcedLow
(
    uint8_t  *pQupAddr
)
{
    uint32_t uClkState, uBusActive, uOutFsmState, uI2cMasterReg;

    uI2cMasterReg = QUPE_IN(pQupAddr, I2C_MASTER_STATUS);

    uBusActive = (uI2cMasterReg &
                  (QUPE_FMSK(I2C_MASTER_STATUS, BUS_ACTIVE))) >>
                 QUPE_SHFT(I2C_MASTER_STATUS, BUS_ACTIVE);

    uOutFsmState = (uI2cMasterReg &
                    (QUPE_FMSK(I2C_MASTER_STATUS, OUTPUT_FSM_STATE))) >>
                   QUPE_SHFT(I2C_MASTER_STATUS, OUTPUT_FSM_STATE);

    uClkState = (uI2cMasterReg &
                 (QUPE_FMSK(I2C_MASTER_STATUS, CLK_STATE))) >>
                QUPE_SHFT(I2C_MASTER_STATUS, CLK_STATE);

    return (
               (HAL_QUPE_I2C_CLOCK_FORCED_LOW_STATE == uClkState) &&
               (
                   (HAL_QUPE_I2C_OUT_FSM_IDLE_STATE  == uOutFsmState) ||
                   (HAL_QUPE_I2C_OUT_FSM_MIREC_STATE == uOutFsmState)
               )
           ) || (!uBusActive);
}

/** @brief Checks if bus is clear.
    @param[in]  pQupAddr index of the qup.
    @return Nothing.
  */
bool
HAL_qupe_IsI2CBusBusy
(
    uint8_t  *pQupAddr
)
{
    uint32_t uActiveField, uI2cMasterReg;

    uI2cMasterReg = QUPE_IN(pQupAddr, I2C_MASTER_STATUS);
    uActiveField  = (uI2cMasterReg &
                     (QUPE_FMSK(I2C_MASTER_STATUS, BUS_ACTIVE)) )>>
                    QUPE_SHFT(I2C_MASTER_STATUS, BUS_ACTIVE);

    return (bool) uActiveField;
}

/** @brief Checks if bus state given by the pointer is clear.
    @param[in]  pI2cStatus  Pointer to i2c status stored with HAL_qupe_GetI2cState.
    @return true if bus busy false otherwise.
  */
bool
HAL_qupe_IsI2CStateBusy
(
    HAL_qupe_I2cStatus  *pI2cStatus
)
{
    uint32_t uActiveField, uI2cMasterReg;

    uI2cMasterReg = pI2cStatus->uRawStatus;
    uActiveField  = (uI2cMasterReg &
                     (QUPE_FMSK(I2C_MASTER_STATUS, BUS_ACTIVE)) )>>
                    QUPE_SHFT(I2C_MASTER_STATUS, BUS_ACTIVE);

    // since this is a stored state do extra checks

    return (bool) (uActiveField ||
                      (!(uI2cMasterReg & QUPE_FMSK(I2C_MASTER_STATUS, I2C_SCL))) ||
                      (!(uI2cMasterReg & QUPE_FMSK(I2C_MASTER_STATUS, I2C_SDA)))
                     );
}

/** @brief Gets the state of the I2C.
    @param[in]  pQupAddr index of the qup.
    @param[out] pI2cStatus pointer to a location to store status struct.
    @return     Nothing.
  */
void
HAL_qupe_GetI2cState
(
    uint8_t               *pQupAddr,
    HAL_qupe_I2cStatus  *pI2cStatus
)
{
    HAL_QUPE_ASSERT(NULL == pI2cStatus);

    pI2cStatus->uRawStatus    = QUPE_IN(pQupAddr, I2C_MASTER_STATUS);
}

/** @brief Gets the data state of the I2C.
    @param[in]  pQupAddr index of the qup.
    @return     Data State
  */
uint32_t
HAL_qupe_GetI2cDataState
(
    uint8_t               *pQupAddr
)
{
    uint32_t I2cDataState = 0;

    I2cDataState = (QUPE_IN(pQupAddr, I2C_MASTER_STATUS) &
                    QUPE_FMSK(I2C_MASTER_STATUS, DATA_STATE)) >>
                   QUPE_SHFT(I2C_MASTER_STATUS, DATA_STATE);

    return I2cDataState;
}

/** @brief Clears I2c errors.
    @param[in]  pQupAddr index of the qup.
    @param[in]  uErrMask error mask to clear.
    @return     Nothing.
  */
void
HAL_qupe_ClearI2cErrors
(
    uint8_t               *pQupAddr,
    uint32_t              uErrMask
)
{
    QUPE_OUT(pQupAddr,I2C_MASTER_STATUS,uErrMask);
}
