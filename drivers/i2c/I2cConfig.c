//Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
//All Rights Reserved.
//Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.

#include "I2cConfig.h"
#include "i2c_api.h"
#include "msmhwiobase.h"

#define DEFAULT_APP_CLK_FREQ_KHZ 50000  //I2cDefaults.h equal to hob.xml i2c config


static i2c_config_t i2c_devices[] =
{
    // Bus 0 - DIMM Channels 2,3,4
    {0, (uint8_t *) I1_BLSP_QUP0_REG_BASE_PHYS, {0x2005C001, 0x2005C011},
        "/dev/i2c1", LOG_DISABLED, APP_CLK_FRQ_KHZ, TRUE, FALSE},
    // Bus 1 - DIMM Channels 0,1,5
    {1, (uint8_t *) I1_BLSP_QUP1_REG_BASE_PHYS, {0x2005C021, 0x2005C031},
        "/dev/i2c2", LOG_DISABLED, APP_CLK_FRQ_KHZ, TRUE, FALSE},
    // Bus 2 - PCIe controllers/port expanders
    {2, (uint8_t *) I1_BLSP_QUP2_REG_BASE_PHYS, {0x2005C041, 0x2005C051},
        "/dev/i2c3", LOG_DISABLED, APP_CLK_FRQ_KHZ, FALSE, TRUE},
    // Bus 3 - PCIe Bus Arbiter, PMBus
    {3, (uint8_t *) I1_BLSP_QUP3_REG_BASE_PHYS, {0x20004061, 0x2005C071},
        "/dev/i2c4", LOG_DISABLED, APP_CLK_FRQ_KHZ, TRUE, FALSE},
    // Bus 4 - I2C/SMBus/SSIF Master to BMC Slave
    {4, (uint8_t *) I2_BLSP_QUP0_REG_BASE_PHYS, {0x2005C081, 0x2005C091},
        "/dev/i2c5", LOG_DISABLED, APP_CLK_FRQ_KHZ, FALSE, TRUE},
    // Bus 5 - Spare Bus
    {5, (uint8_t *) I2_BLSP_QUP1_REG_BASE_PHYS, {0x2005C0a1, 0x2005C0b1},
        "/dev/i2c6", LOG_DISABLED, APP_CLK_FRQ_KHZ, FALSE, TRUE},
    // Bus 6 - BMC CPLD
    {6, (uint8_t *) I2_BLSP_QUP2_REG_BASE_PHYS, {0x2005C0c1, 0x2005C0d1},
        "/dev/i2c7", LOG_DISABLED, APP_CLK_FRQ_KHZ, FALSE, TRUE},
    // Bus 7 - BMC Master/IMC Slave
    {7, (uint8_t *) I2_BLSP_QUP3_REG_BASE_PHYS, {0x2005C0e1, 0x2005C0f1},
        "/dev/i2c8", LOG_DISABLED, APP_CLK_FRQ_KHZ, FALSE, FALSE},
};




i2c_config_t *i2c_get_device(uint32_t idx)
{
    if(idx >= I2C_NUM_DEVICES) return NULL;

	i2c_devices[idx].appClkFreqKhz = DEFAULT_APP_CLK_FREQ_KHZ;

    return &i2c_devices[idx];
}


