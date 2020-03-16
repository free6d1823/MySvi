/*==============================================================================
#    Copyright (c) 2014,2016 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#
#    Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
#    All Rights Reserved.
#    Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
#=============================================================================*/
/** @file   smbus.c
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2014.12.01
 *  @brief  Smbus wrapper for I2C
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <target/irq.h>
#include <target/smbus.h>
#include <target/bitops.h>
#include <target/gpio.h>
#include <target/cmdline.h>

#ifdef IMC_BUILD
#include <stringl/stringl.h>
#endif

#define I2C_FLAG_NONE               (0 << 0)
#define I2C_FLAG_WRITE              (1 << 0)
#define I2C_FLAG_READ               (1 << 1)
#define I2C_FLAG_SMBUS              (1 << 2)
#define I2C_FLAG_SMBUS_PROCESS_CALL (1 << 3)
#define I2C_FLAG_SMBUS_BLOCK        (1 << 4)

#define SMBUS_MAX_OPERATIONS         2
#define SMBUS_MAX_TRANSACTION_LEN    (256)

// Synchronization construct for shared driver resources
// BEGIN shared driver resources
static bool in_use[SMBUS_NUM_DEVICES] = { 0 };
static qurt_mutex_t smbus_crit_sect;
static int SlaveAddr = 0;
static int id = 0;
// END shared driver resources

/* The I2C master controller driver is not an asynchronous
 * driver. When it is used to communicate with the I2C slave
 * handled by our own I2CS driver, the IRQ must be enabled to
 * allow the I2CS IRQs interrupts the I2C master transfers.
 */
#ifdef CONFIG_LOOPBACK_I2CS
static inline void I2C_EnableIrq(void)
{
    irq_local_enable();
}
static inline void I2C_DisableIrq(void)
{
    irq_local_disable();
}
#else
static inline void I2C_EnableIrq(void) {}
static inline void I2C_DisableIrq(void) {}
#endif

void smbus_init()
{
    // Needed for RCINIT to be happy. Does nothing.
    return;
}

typedef struct
{
    uint32_t length;
    uint32_t flags;
} SmbusSingleOperation;
typedef struct
{
    SmbusSingleOperation op[SMBUS_MAX_OPERATIONS];
} SmbusLocalParameters;

static SmbusResult SmbusConvertI2cResult(I2cResult i2cRes)
{
    switch (i2cRes)
    {
        case I2C_RES_SUCCESS:
            return SMBUS_SUCCESS;
        case I2CDEVQUP_ERR_PACKET_NACKED:
            return SMBUS_ERROR_ADDR_NACKED;
        case I2CDEVQUP_ERR_NACK_IN_TRANSFER:
            return SMBUS_ERROR_DATA_NACKED;
        case I2CDEVQUP_ERR_UNEXPECTED_START_STOP:
        case I2CDEVQUP_ERR_INVALID_WRITE:
            return SMBUS_ERROR_DEVICE_ERROR;
        case I2C_RES_ERROR_CLS_QUP_DEV_TIMEOUT:
            return SMBUS_ERROR_TIMEOUT;
        case I2CDRV_ERR_INVALID_DEV_IDX:
        case I2CDRV_ERR_INVALID_TRANSFER_POINTER:
        case I2CDRV_ERR_INVALID_SEQUENCE_POINTER:
        case I2CDRV_ERR_INVALID_IO_RES_POINTER:
        case I2CDRV_ERR_INVALID_NUMCOMPLETED_POINTER:
            return SMBUS_ERROR_INVALID_PARAMETER;
        default:
            if (i2cRes & I2C_RES_ERROR_CLS_QUP_DEV)
                return SMBUS_ERROR_DEVICE_ERROR;
            if (i2cRes & I2C_RES_ERROR_CLS_I2C_DRV)
                return SMBUS_ERROR_DRIVER_ERROR;
            if (i2cRes & I2C_RES_ERROR_CLS_DEV_PLATFORM)
                return SMBUS_ERROR_I2C_PLATFORM_ERROR;
            if (i2cRes & I2C_RES_ERROR_CLS_DEV_OS)
                return SMBUS_ERROR_OS_ERROR;
            return SMBUS_ERROR_UNKNOWN_I2C_ERROR;
    }
    return SMBUS_ERROR_UNKNOWN_I2C_ERROR;
}

static SmbusResult SmbusBlockReadWrapper
(
    SmbusDevice      dev,
    I2cSequence     *pSequence,
    I2cClientConfig *pClntCfg,
    I2cIoResult     *pIoRes
)
{
    I2cResult   i2cRes;
    SmbusResult smbusRes;
    I2cTransfer *pTrans;

    pTrans = pSequence->pTransfer;
    pTrans->eTranCtxt = I2cTrCtxSeqStart;

    i2cRes =  I2C_Write((I2cDevice)dev, pTrans, pClntCfg, &(pIoRes->uOutByteCnt));
    pIoRes->nOperationResult = i2cRes;
    if(I2C_RES_SUCCESS != i2cRes)
    {
        return SmbusConvertI2cResult(i2cRes);
    }

    pTrans++;
    if(pTrans->uIsSmbusPEC == 1)
    {
        pTrans->uTrSize += 1;
    }
    if (pTrans->uTrSize == 0)
    { // TODO add code here to handle block reads of arbitrary length
        return SMBUS_ERROR_NOT_SUPPORTED;
    }
    else
    {
        // If the user passed in the number of bytes to read, trust that and roll with it
        pTrans->uIsSmbusBlock = 0;
        i2cRes = I2C_Read((I2cDevice)dev, pTrans, pClntCfg, &(pIoRes->uInByteCnt));
        pIoRes->nOperationResult = i2cRes;
    }

    smbusRes =  SmbusConvertI2cResult(i2cRes);
    if (smbusRes == SMBUS_ERROR_DATA_NACKED &&
        pIoRes->uInByteCnt == pTrans->uTrSize)
    {
        return SMBUS_SUCCESS;
    }
    return smbusRes;
}

static SmbusResult sendCommand(SmbusDevice dev,
                               SmbusTransfer *xfer,
                               SmbusLocalParameters *params)
{
    I2cTransfer i2cXfer[SMBUS_MAX_OPERATIONS] = {0};
    I2cSequence i2cSeq;
    I2cIoResult i2cIoResult;
    I2cIoResult *pIoRes = (xfer->pIoRes==NULL) ? &i2cIoResult : xfer->pIoRes;
    I2cResult   i2cRes;
    SmbusResult smbusRes;
    uint8_t     buff[SMBUS_MAX_OPERATIONS][SMBUS_MAX_TRANSACTION_LEN+1];
    I2cBuffDesc buffDesc[SMBUS_MAX_OPERATIONS];
    int i;

    i2cSeq.pTransfer = i2cXfer;
    if(SMBUS_NUM_DEVICES <= dev || NULL == xfer || NULL == xfer->pBuff
        || NULL == params)
    {
        return SMBUS_ERROR_INVALID_PARAMETER;
    }
    i2cXfer[0].eTranCtxt = I2cTrCtxSeqStart;
    i2cXfer[1].eTranCtxt = I2cTrCtxSeqEnd;
    for(i=0; i<SMBUS_MAX_OPERATIONS; i++)
    {
        uint32_t buffIndex = 0;
        i2cXfer[i].uIsSmbus      = ((params->op[i].flags & I2C_FLAG_SMBUS) != 0);
        i2cXfer[i].uIsSmbusBlock = ((params->op[i].flags & I2C_FLAG_SMBUS_BLOCK) != 0);
        i2cXfer[i].tranCfg       = xfer->tranCfg;
        if(params->op[i].flags  == I2C_FLAG_NONE &&
           params->op[i].length == 0)
        {
            i2cXfer[0].eTranCtxt      = I2cTrCtxNotASequence;
            i2cXfer[i].pI2cBuffDesc   = NULL;
            i2cXfer[i].uTrSize        = 0;
            i2cXfer[i].eTranDirection = I2cTranDirOut;
            break;
        }
        i2cSeq.uNumTransfers      = i+1;
        i2cXfer[i].uTrSize        = params->op[i].length;
        if(i2cXfer[i].uIsSmbus)
        {
            buff[i][0] = xfer->command;
            buffIndex++;
            if(i2cXfer[i].uIsSmbusBlock)
            {
                buff[i][1] = xfer->uTrSize;
                buffIndex++;
            }
        }
        i2cXfer[i].pI2cBuffDesc   = &buffDesc[i];
        i2cXfer[i].pI2cBuffDesc->pBuff = buff[i];
        i2cXfer[i].pI2cBuffDesc->uBuffSize = sizeof(buff[i]);
        memscpy(&(i2cXfer[i].pI2cBuffDesc->pBuff[buffIndex]), params->op[i].length,
                xfer->pBuff->pBuff, SMBUS_MAX_TRANSACTION_LEN);
        if(I2C_FLAG_READ & params->op[i].flags)
        {
            i2cXfer[i].eTranDirection = I2cTranDirIn;
        }
        else
        {
            i2cXfer[i].eTranDirection = I2cTranDirOut;
        }
    }

    if (((I2C_FLAG_SMBUS | I2C_FLAG_SMBUS_BLOCK) == params->op[0].flags ) &&
         (I2C_FLAG_READ == params->op[1].flags )){
        I2C_EnableIrq();
        smbusRes =  SmbusBlockReadWrapper(dev, &i2cSeq, &(xfer->clientCfg),
                                     pIoRes);
        I2C_DisableIrq();
    }
    else {
        I2C_EnableIrq();
        i2cRes = I2C_BatchTransfer((I2cDevice)dev, &i2cSeq,
                            &(xfer->clientCfg), pIoRes);
        I2C_DisableIrq();
        smbusRes = SmbusConvertI2cResult(i2cRes);
    }

    if(SMBUS_SUCCESS != smbusRes)
    {
        return smbusRes;
    }
    for(i=0; i<SMBUS_MAX_OPERATIONS; i++)
    {
        if(I2cTranDirIn == i2cXfer[i].eTranDirection)
        {
            uint8_t offset = 0;
            if (xfer->bBlockReadStartsWithLength != 0) {
                offset = 1;
                pIoRes->uInByteCnt = i2cXfer[i].pI2cBuffDesc->pBuff[0];
            }
            memscpy(xfer->pBuff->pBuff, xfer->pBuff->uBuffSize,
                    ((uint8_t *) i2cXfer[i].pI2cBuffDesc->pBuff) + offset,
                    pIoRes->uInByteCnt);
            break;
        }
    }
    return SMBUS_SUCCESS;
}

void SmbusInit()
{
    qurt_pimutex_init(&smbus_crit_sect);
}

void SmbusDeInit()
{
}

bool SmbusIsAttached(SmbusDevice dev)
{
    if (dev < SMBUS_NUM_DEVICES)
    {
        return in_use[dev];
    }
    return false;
}

SmbusResult SmbusAttach(SmbusDevice dev)
{
    bool dev_in_use;
    SmbusResult res;

    SmbusInit();

    if (dev >= SMBUS_NUM_DEVICES)
    {
        return SMBUS_ERROR_OUT_OF_RANGE_PARAMETER;
    }

    qurt_pimutex_lock(&smbus_crit_sect);
    dev_in_use = in_use[dev];
    if (false == in_use[dev]) in_use[dev] = true;
    qurt_pimutex_unlock(&smbus_crit_sect);

    if (dev_in_use)
    {
        return SMBUS_SUCCESS;
    }

    res = SmbusConvertI2cResult(I2C_Attach((I2cDevice)dev));
    if(SMBUS_SUCCESS != res)
    {
        return res;
    }

    res = SmbusConvertI2cResult(I2C_Open((I2cDevice)dev));
    if(SMBUS_SUCCESS != res)
    {
        return res;
    }

    return SmbusConvertI2cResult(I2C_Reset((I2cDevice)dev));
}

SmbusResult SmbusDetach(SmbusDevice dev)
{
    bool dev_in_use;

    if (dev >= SMBUS_NUM_DEVICES)
    {
        return SMBUS_ERROR_OUT_OF_RANGE_PARAMETER;
    }

    qurt_pimutex_lock(&smbus_crit_sect);
    dev_in_use = in_use[dev];
    if (true == in_use[dev]) in_use[dev] = false;
    qurt_pimutex_unlock(&smbus_crit_sect);

    if (!dev_in_use)
    {
        return SMBUS_ERROR_BUSY_RESOURCE;
    }

    I2C_Close((I2cDevice)dev);
    I2C_Detach((I2cDevice)dev);
    return SMBUS_SUCCESS;
}

SmbusResult SmbusQuickRead         (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 0;
    params.op[0].flags  = I2C_FLAG_READ;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusQuickWrite        (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 0;
    params.op[0].flags  = I2C_FLAG_WRITE;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusReceiveByte       (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 1;
    params.op[0].flags  = I2C_FLAG_SMBUS | I2C_FLAG_READ;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusSendByte          (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 1;
    params.op[0].flags  = I2C_FLAG_SMBUS;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusReadDataByte     (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 1;
    params.op[0].flags  = I2C_FLAG_SMBUS;
    params.op[1].length = 1;
    params.op[1].flags  = I2C_FLAG_READ;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusWriteDataByte    (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 2;
    params.op[0].flags  = I2C_FLAG_SMBUS;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusReadDataWord     (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 1;
    params.op[0].flags  = I2C_FLAG_SMBUS;
    params.op[1].length = 2;
    params.op[1].flags  = I2C_FLAG_READ;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusWriteDataWord    (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 3;
    params.op[0].flags  = I2C_FLAG_SMBUS;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusProcessCall       (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 3;
    params.op[0].flags  = I2C_FLAG_SMBUS | I2C_FLAG_SMBUS_PROCESS_CALL;
    params.op[1].length = 2;
    params.op[1].flags  = I2C_FLAG_READ;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusBlockRead         (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    params.op[0].length = 1;
    params.op[0].flags  = I2C_FLAG_SMBUS | I2C_FLAG_SMBUS_BLOCK;
    params.op[1].length = xfer->uTrSize +
        ((xfer->bBlockReadStartsWithLength == 0) ? 0 : 1);
    params.op[1].flags  = I2C_FLAG_READ;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusBlockWrite        (SmbusDevice dev, SmbusTransfer *xfer)
{
    SmbusLocalParameters params;
    if(xfer == NULL)
    {
        return SMBUS_ERROR_INVALID_PARAMETER;
    }
    params.op[0].length = 2 + xfer->uTrSize;
    params.op[0].flags  = I2C_FLAG_SMBUS | I2C_FLAG_SMBUS_BLOCK;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return sendCommand(dev, xfer, &params);
}

SmbusResult SmbusBlockProcessCall (SmbusDevice dev, SmbusTransfer *xfer)
{
    return SMBUS_ERROR_NOT_SUPPORTED;
}

SmbusResult I2C_Command(
                SmbusDevice dev,
                uint32_t SlaveAddr,
                uint32_t comm,
                void *pIoBuffer,
                size_t BufferSize,
                SmbusLocalParameters params
)
{
    SmbusTransfer XTransaction = {0};
    I2cBuffDesc IoBufferDescriptor = {0};

    // Setup the buffer descriptor
    IoBufferDescriptor.pBuff = (uint8_t*) pIoBuffer;
    IoBufferDescriptor.uBuffSize = BufferSize;

    // Set up the client config
    XTransaction.clientCfg.uBusFreqKhz = 400;
    XTransaction.clientCfg.uByteTransferTimeoutUs = 20000;

    // Setup the transaction
    XTransaction.tranCfg.uSlaveAddr = SlaveAddr;
    XTransaction.pBuff = &IoBufferDescriptor;
    XTransaction.uTrSize = BufferSize;
    XTransaction.command = comm;
    XTransaction.pIoRes  = NULL;
    XTransaction.bBlockReadStartsWithLength = false;

    return sendCommand(dev, &XTransaction, &params);
}

SmbusResult I2cQuickRead(
                SmbusDevice id,
                uint32_t addr,
                uint32_t comm,
                void *pIoBuffer,
                size_t BufferSize
)
{
    SmbusLocalParameters params;
    params.op[0].length = 1;//not support 0
    params.op[0].flags  = I2C_FLAG_READ;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return I2C_Command(id,addr,0,pIoBuffer,BufferSize,params);
}

SmbusResult I2cRead(
                SmbusDevice id,
                uint32_t addr,
                uint32_t comm,
                void *pIoBuffer,
                size_t BufferSize
)
{
    SmbusLocalParameters params;
    params.op[0].length = BufferSize;
    params.op[0].flags  = I2C_FLAG_READ;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return I2C_Command(id,addr,0,pIoBuffer,BufferSize,params);
}

SmbusResult I2cBlockRead(
                SmbusDevice id,
                uint32_t addr,
                uint32_t comm,
                void *pIoBuffer,
                size_t BufferSize
)
{
    SmbusLocalParameters params;
    params.op[0].length = 1;
    params.op[0].flags  = I2C_FLAG_SMBUS;
    params.op[1].length = BufferSize;
    params.op[1].flags  = I2C_FLAG_READ;
    return I2C_Command(id,addr,comm,pIoBuffer,BufferSize,params);
}

SmbusResult I2cBlockWrite(
                SmbusDevice id,
                uint32_t addr,
                uint32_t comm,
                void *pIoBuffer,
                size_t BufferSize
)
{
    SmbusLocalParameters params;
    params.op[0].length = 1 + BufferSize;
    params.op[0].flags  = I2C_FLAG_SMBUS;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return I2C_Command(id,addr,comm,pIoBuffer,BufferSize,params);
}

void i2c_print(uint8_t *buff, size_t BufferSize)
{
    int i;

    printf("   ");
    for (i = 0; i < 16; i++)
        printf("  %X", i);
    printf("\n");
    for (i = 0; i < BufferSize; i++)
    {
        if (0 == (i & 0xf)) {
            if(i) printf("\n");
            printf("%02X:", i);
        }
        printf(" %02X", buff[i]);
    }

    printf("\n");
}

int do_i2c(int argc, char *argv[])
{
    int i, ret = 0;
    SmbusResult res = 0;
    uint8_t buff[256] = {0};
    uint8_t DetectBuff;
    uint32_t comm = 0;
    void *pIoBuffer = buff;
    size_t BufferSize = 256;

    if (argc == 1) {
        printf("Unknown command '%s'\n", argv[0]);
        return -1;
    }
    for (i=0; i < argc; i++){
        if (strcmp(argv[i], "-") == 0) {
            if (argv[i+1]) {
                BufferSize = strtoul(argv[i+1], NULL, 0);
                break;
            }else {
                printf("Number must be after '-l'!\n");
                return -1;
            }
        }
    }
    if (strcmp(argv[1], "open") == 0) {
        boot_tlmm_init();
        id = strtoul(argv[2], NULL, 0);
        if ((id > -1) && (id < 8)) {
            if (true == SmbusIsAttached(id)){
                printf("i2c %d is already attached!\n", id);
            }else {
                if (SMBUS_SUCCESS == SmbusAttach(id)){
                    printf("Attach i2c %d success!\n", id);
                }else {
                    printf("Attach i2c %d fail!\n", id);
                }
            }
        }else {
            printf("Check your import i2c id %d!\n", id);
        }
    }else if (strcmp(argv[1], "close") == 0) {
        id = strtoul(argv[2], NULL, 0);
        if (id >= 0 && id < 8) {
            if (SMBUS_SUCCESS == SmbusDetach(id)){
                printf("Detach i2c %d success!\n", id);
            }else {
                printf("Detach i2c %d fail!\n", id);
            }
        }else {
            printf("Check your import i2c id %d!\n", id);
        }
    }else if (strcmp(argv[1], "d") == 0) {
        pIoBuffer = &DetectBuff;
        BufferSize = 1;
        comm = 0x0;
        memset(buff,255,sizeof(buff));
        if (argc == 2) {
            int addr;
            for (addr = 0; addr < 128; addr++) {
                res = I2cQuickRead(id,addr,0,pIoBuffer,BufferSize);
                if (SMBUS_SUCCESS == res) {
                    buff[addr] = addr;
                }
            }
            printf("i2c device: \n");
            i2c_print(buff,128);
        }else if (argc == 3) {
            SlaveAddr = strtoul(argv[2], NULL, 0);
            if (SlaveAddr >= 0 && SlaveAddr < 128) {
                res = I2cQuickRead(id,SlaveAddr,0,pIoBuffer,BufferSize);
                if (SMBUS_SUCCESS == res) {
                    printf("Find i2c device: 0x%X\n", SlaveAddr);
                }else {
                    printf("Not find i2c device: 0x%X\n", SlaveAddr);
                }
            }
        }else {
            printf("Unknown command '%s'\n", argv[0]);
            return -1;
        }
    }else if (strcmp(argv[1], "w") == 0) {
        if (argc == 3) {
            BufferSize = 0;
            SlaveAddr = strtoul(argv[2], NULL, 0);
            comm = 0;
            res = I2cBlockWrite(id,SlaveAddr,comm,pIoBuffer,BufferSize);
        }else if (argc > 3) {
            int i;
            BufferSize = argc - 4;//outbuff = total arg - 4
            for (i = 0; i < BufferSize; i++) {
                buff[i] = strtoul(argv[i+4], NULL, 0);
            }
            SlaveAddr = strtoul(argv[2], NULL, 0);
            comm = strtoul(argv[3], NULL, 0);
            res = I2cBlockWrite(id,SlaveAddr,comm,pIoBuffer,BufferSize);
        }else {
            printf("Unknown command '%s'\n", argv[0]);
            return -1;
        }
        if (SMBUS_SUCCESS == res) {
            printf("i2c write register 0x%X \n", comm);
        }else {
            printf("I2C write error: 0x%X\n", res);
        }
    }else if (strcmp(argv[1], "r") == 0) {
        if (argc == 2) {
            printf("Unknown command '%s'\n", argv[0]);
            return -1;
        }else if (argc == 3) {
            SlaveAddr = strtoul(argv[2], NULL, 0);
            comm = 0;
            res = I2cRead(id,SlaveAddr,comm,pIoBuffer,BufferSize);
        }else if (argc == 4) {
            SlaveAddr = strtoul(argv[2], NULL, 0);
            comm = strtoul(argv[3], NULL, 0);
            res = I2cBlockRead(id,SlaveAddr,comm,pIoBuffer,BufferSize);
        }else if (argc == 5 && BufferSize != 256) {
            SlaveAddr = strtoul(argv[2], NULL, 0);
            comm = 0;
            res = I2cRead(id,SlaveAddr,comm,pIoBuffer,BufferSize);
        }else if (argc == 6 && BufferSize != 256) {
            SlaveAddr = strtoul(argv[2], NULL, 0);
            comm = strtoul(argv[3], NULL, 0);
            res = I2cBlockRead(id,SlaveAddr,comm,pIoBuffer,BufferSize);
        }else {
            SlaveAddr = strtoul(argv[2], NULL, 0);
            comm = strtoul(argv[3], NULL, 0);
            res = I2cBlockRead(id,SlaveAddr,comm,pIoBuffer,BufferSize);
        }
        if (SMBUS_SUCCESS == res) {
            printf("i2c read 0x%X data: \n", comm);
            i2c_print(pIoBuffer,BufferSize);
        }else {
            printf("I2C read error: 0x%X\n", res);
        }
    }else {
        printf("Unknown command '%s'\n", argv[0]);
        return -1;
    }

    return ret;
}

MK_CMD(i2c, do_i2c, "use i2c master to attach slave",
    " i2c {open} <id> \n"
    "    -Attach i2c master id. \n"
    " i2c {close} <id> \n"
    "    -Detach i2c master id. \n"
    " i2c {d} \n"
    "    -Detect all of slave. \n"
    " i2c {d} [slave addr] \n"
    "    -Detect if slave exists. \n"
    " i2c {w} <slave addr> [comm]\n"
    "    -Set comm(default=0). \n"
    " i2c {w} <slave addr> <comm> [value1] [value2] ... \n"
    "    -Write values to comm. \n"
    " i2c {r} <slave addr> [comm] \n"
    "    -Read 256 values from [comm]. \n"
    " i2c {r} <slave addr> [comm] [- len] \n"
    "    -Read [len] values from [comm]. \n"
);
