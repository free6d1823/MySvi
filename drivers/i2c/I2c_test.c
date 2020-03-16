#include "i2c_api.h"
#include "I2cConfig.h"
#include "I2cError.h"
#include <stdio.h>
#include "I2c_test.h"
#include <Library/BaseMemoryLib.h>

#define X_MAX_OPERATIONS         2
#define X_MAX_TRANSACTION_LEN    (8)
#define X_I2C_DATA_OFFSET        0X60    
#define I2C_FLAG_NONE            (0 << 0)
#define I2C_FLAG_WRITE           (1 << 0)
#define I2C_FLAG_READ            (1 << 1)
#define min(a,b) ((a<b) ? a : b)
#define memscpy(d,dc,s,sc) (CopyMem(d, s, min(sc,dc)))

typedef struct
{
    uint32_t length;
    uint32_t flags;
} XSingleOperation;
typedef struct
{
    XSingleOperation op[X_MAX_OPERATIONS];
} XLocalParameters;

typedef struct
{
    I2cBuffDesc      *pBuff;    // IO Buffer
    uint32_t          uTrSize;  // Transfer total number of bytes
    I2cTransferConfig tranCfg;  // Transfer configuration (slave addr)
    I2cClientConfig   clientCfg;// Client configuration (bus frequency/timeout)
    uint8_t           offset;
    I2cIoResult      *pIoRes;   // I2C IO Result for deeper command parsing
    uint8_t           bBlockReadStartsWithLength;// Some of our clients send the
                                // length of the transaction (following SMBus
                                //   spec). Others don't.
} XTransfer;

static I2cResult I2C_batch_process(I2cDevice dev,
                               XTransfer *xfer,
                               XLocalParameters *params)
{
    I2cTransfer i2cXfer[X_MAX_OPERATIONS];
    I2cSequence i2cSeq;
    I2cIoResult i2cIoResult;
    I2cIoResult *pIoRes = (xfer->pIoRes==NULL) ? &i2cIoResult : xfer->pIoRes;
    I2cResult   i2cRes;
    uint8_t     buff[X_MAX_OPERATIONS][X_MAX_TRANSACTION_LEN+1];
    I2cBuffDesc buffDesc[X_MAX_OPERATIONS];
    int i;

    i2cSeq.pTransfer = i2cXfer;
    if(I2C_NUM_DEVICES <= dev || NULL == xfer || NULL == xfer->pBuff
        || NULL == params)
    {
        return -1; //error 
    }
    i2cXfer[0].eTranCtxt = I2cTrCtxSeqStart;
    i2cXfer[1].eTranCtxt = I2cTrCtxSeqEnd;
    for(i=0; i<X_MAX_OPERATIONS; i++)
    {
        uint32_t buffIndex = 0;
        i2cXfer[i].uIsSmbus      = 0;
        i2cXfer[i].uIsSmbusBlock = 0;
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
        //if(i2cXfer[i].uIsSmbus)
        if (params->op[i].flags == X_I2C_DATA_OFFSET) //data offset
        {
            buff[i][0] = xfer->offset;
            buffIndex++;
        }
        i2cXfer[i].pI2cBuffDesc   = &buffDesc[i];
        i2cXfer[i].pI2cBuffDesc->pBuff = buff[i];
        i2cXfer[i].pI2cBuffDesc->uBuffSize = sizeof(buff[i]);
        memscpy(&(i2cXfer[i].pI2cBuffDesc->pBuff[buffIndex]), params->op[i].length,
                xfer->pBuff->pBuff, X_MAX_TRANSACTION_LEN);
        if(I2C_FLAG_READ & params->op[i].flags)
        {
            i2cXfer[i].eTranDirection = I2cTranDirIn;
        }
        else
        {
            i2cXfer[i].eTranDirection = I2cTranDirOut;
        }
    }

    i2cRes = I2C_BatchTransfer((I2cDevice)dev, &i2cSeq,
                        &(xfer->clientCfg), pIoRes);

    if(I2C_RES_SUCCESS != i2cRes)
    {
        return i2cRes;
    }
    for(i=0; i<X_MAX_OPERATIONS; i++)
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
    return I2C_RES_SUCCESS;
}


I2cResult I2C_Basic_Read(
		I2cDevice dev,
		uint32_t slaveAddr,
		uint32_t offset,
		void *pIoBuffer,
		size_t BufferSize
)
{
	//todo need to add block process later
	if (BufferSize > 2) return -1;

	XTransfer XTransaction;
	I2cBuffDesc IoBufferDescriptor;

	// Setup the output buffer descriptor
	IoBufferDescriptor.pBuff = (uint8_t*) pIoBuffer;
	IoBufferDescriptor.uBuffSize = BufferSize;

	// Set up the client config
	XTransaction.clientCfg.uBusFreqKhz = 400;
	XTransaction.clientCfg.uByteTransferTimeoutUs = 20000;

	// Setup the transaction
	XTransaction.tranCfg.uSlaveAddr = slaveAddr;
	XTransaction.pBuff = &IoBufferDescriptor;
	XTransaction.uTrSize = BufferSize;
	XTransaction.offset = offset;
	XTransaction.pIoRes  = NULL;
	XTransaction.bBlockReadStartsWithLength = FALSE;

    XLocalParameters params;
    params.op[0].length = 1;
    params.op[0].flags  = X_I2C_DATA_OFFSET;
    params.op[1].length = BufferSize;
    params.op[1].flags  = I2C_FLAG_READ;
    return I2C_batch_process(dev, &XTransaction, &params);

}

I2cResult I2C_Basic_Write(
		I2cDevice dev,
		uint32_t slaveAddr,
		uint32_t offset,
		void *pIoBuffer,
		size_t BufferSize
)
{
	//todo need to add block process later
	if (BufferSize > 2) return -1;

	XTransfer XTransaction;
	I2cBuffDesc IoBufferDescriptor;

    // Setup the output buffer descriptor
    IoBufferDescriptor.pBuff = (uint8_t*) pIoBuffer;
    IoBufferDescriptor.uBuffSize = BufferSize;

    // Set up the client config
    XTransaction.clientCfg.uBusFreqKhz = 400;
    XTransaction.clientCfg.uByteTransferTimeoutUs = 20000;

    // Setup the transaction
    XTransaction.tranCfg.uSlaveAddr = slaveAddr;
    XTransaction.pBuff = &IoBufferDescriptor;
    XTransaction.uTrSize = BufferSize;
    XTransaction.offset = offset;
    XTransaction.pIoRes  = NULL;
    XTransaction.bBlockReadStartsWithLength = FALSE;


    XLocalParameters params;
    params.op[0].length = BufferSize + 1;
    params.op[0].flags  = X_I2C_DATA_OFFSET;
    params.op[1].length = 0;
    params.op[1].flags  = I2C_FLAG_NONE;
    return I2C_batch_process(dev, &XTransaction, &params);

}


I2cResult I2C_Basic_Attach(I2cDevice id)
{
	I2cResult i2cRes = I2C_RES_SUCCESS;

	do {
		i2cRes = I2C_Attach(id);
		if(i2cRes != I2C_RES_SUCCESS) break;		
		i2cRes = I2C_Open(id);
		if(i2cRes != I2C_RES_SUCCESS) break;
		i2cRes = I2C_Reset(id);
		if(i2cRes != I2C_RES_SUCCESS) break;
	} while (0);

	return i2cRes;
}

I2cResult I2C_Basic_Detach(I2cDevice id)
{
	I2cResult i2cRes = I2C_RES_SUCCESS;

	do {
		i2cRes = I2C_Close(id);
		if(i2cRes != I2C_RES_SUCCESS) break;

		i2cRes = I2C_Detach(id);
		if(i2cRes != I2C_RES_SUCCESS) break;

	} while (0);

	return i2cRes;
}

#define TEST_SLAVE_ADDRESS   0x42
#define TEST_I2C_DEVICE_ID   I2C_DEVICE_5

void test_I2CTest_Basic_Read()
{
	I2cResult i2cRes;

    uint8_t buff[20+1] = {0};
	I2cDevice id = TEST_I2C_DEVICE_ID;
	uint32_t slaveAddr = TEST_SLAVE_ADDRESS;
	uint32_t offset = 0x02;
	void *pIoBuffer = buff;
	size_t BufferSize = 2;
        int i;


	i2cRes = I2C_Basic_Attach(id);		
	if(i2cRes != I2C_RES_SUCCESS) return;

	i2cRes = I2C_Basic_Read(id, slaveAddr, offset, pIoBuffer, BufferSize);
	if(i2cRes != I2C_RES_SUCCESS) 
	{
		printf("I2C_Basic_read error %d\n", i2cRes);
		return;
	}

	printf("read data: ");
	for (i = 0; i < BufferSize; i++) 
	{		
		printf(" 0x%x ", buff[i]);
	}

	printf("\n");

	i2cRes = I2C_Basic_Detach(id);		
	if(i2cRes != I2C_RES_SUCCESS) return;

}

void test_I2CTest_Basic_Write()
{
	I2cResult i2cRes;

    uint8_t buff[20+1] = {0};
	I2cDevice id = TEST_I2C_DEVICE_ID;
	uint32_t slaveAddr = TEST_SLAVE_ADDRESS;
	uint32_t offset = 0x02;
	void *pIoBuffer = buff;
	size_t BufferSize = 2;
        int i;


	i2cRes = I2C_Basic_Attach(id);		
	if(i2cRes != I2C_RES_SUCCESS) return;

	i2cRes = I2C_Basic_Write(id, slaveAddr, offset, pIoBuffer, BufferSize);
	if(i2cRes != I2C_RES_SUCCESS) 
	{
		printf("I2C_Basic_Write error %d\n", i2cRes);
		return;
	}

	printf("write data: ");
	for (i = 0; i < BufferSize; i++) 
	{		
		printf(" 0x%x ", buff[i]);
	}

	printf("\n");

	i2cRes = I2C_Basic_Detach(id);		
	if(i2cRes != I2C_RES_SUCCESS) return;

}


