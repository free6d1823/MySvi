#ifndef __I2C_TEST_H__
#define __I2C_TEST_H__

#include "i2c_api.h"

void test_I2CTest_DeviceAttach();

void test_I2CTest_BasicRead();

void test_I2CTest_Basic_Read();

void test_I2CTest_Basic_Write();

//i2c API
I2cResult I2C_Basic_Attach(I2cDevice id);
I2cResult I2C_Basic_Detach(I2cDevice id);
I2cResult I2C_Basic_Read(I2cDevice dev, uint32_t slaveAddr, uint32_t offset, void *pIoBuffer, size_t BufferSize);
I2cResult I2C_Basic_Write(I2cDevice dev, uint32_t slaveAddr, uint32_t offset, void *pIoBuffer, size_t BufferSize);





#endif
