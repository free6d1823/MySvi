#include <stdint.h>
#include <stdlib.h>
#include <target/i2c.h>

#define DEFAULT_APP_CLK_FREQ_KHZ 50000  //I2cDefaults.h equal to hob.xml i2c config

static i2c_config_t i2c_devices[] =
{
    // Bus 0 - DIMM Channels 2,3,4
    {0, (uint8_t *) I1_BLSP_QUP0_REG_BASE_PHYS, {0x2005C001, 0x2005C011},
        "/dev/i2c1", LOG_DISABLED, APP_CLK_FRQ_KHZ, true, false},
    // Bus 1 - DIMM Channels 0,1,5
    {1, (uint8_t *) I1_BLSP_QUP1_REG_BASE_PHYS, {0x2005C021, 0x2005C031},
        "/dev/i2c2", LOG_DISABLED, APP_CLK_FRQ_KHZ, true, false},
    // Bus 2 - PCIe controllers/port expanders
    {2, (uint8_t *) I1_BLSP_QUP2_REG_BASE_PHYS, {0x2005C041, 0x2005C051},
        "/dev/i2c3", LOG_DISABLED, APP_CLK_FRQ_KHZ, false, true},
    // Bus 3 - PCIe Bus Arbiter, PMBus
    {3, (uint8_t *) I1_BLSP_QUP3_REG_BASE_PHYS, {0x20004061, 0x2005C071},
        "/dev/i2c4", LOG_DISABLED, APP_CLK_FRQ_KHZ, true, false},
    // Bus 4 - I2C/SMBus/SSIF Master to BMC Slave
    {4, (uint8_t *) I2_BLSP_QUP0_REG_BASE_PHYS, {0x2005C081, 0x2005C091},
        "/dev/i2c5", LOG_DISABLED, APP_CLK_FRQ_KHZ, false, true},
    // Bus 5 - Spare Bus
    {5, (uint8_t *) I2_BLSP_QUP1_REG_BASE_PHYS, {0x2005C0a1, 0x2005C0b1},
        "/dev/i2c6", LOG_DISABLED, APP_CLK_FRQ_KHZ, false, true},
    // Bus 6 - BMC CPLD
    {6, (uint8_t *) I2_BLSP_QUP2_REG_BASE_PHYS, {0x2005C0c1, 0x2005C0d1},
        "/dev/i2c7", LOG_DISABLED, APP_CLK_FRQ_KHZ, false, true},
    // Bus 7 - BMC Master/IMC Slave
    {7, (uint8_t *) I2_BLSP_QUP3_REG_BASE_PHYS, {0x2005C0e1, 0x2005C0f1},
        "/dev/i2c8", LOG_DISABLED, APP_CLK_FRQ_KHZ, false, false},
};

static UINT32 TlmmConfigurationTable[] = {
  //           gpio func dir          pull          drive
  DAL_GPIO_CFG(0,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP1_I2C0_SDA
  DAL_GPIO_CFG(1,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP1_I2C0_SCL
  DAL_GPIO_CFG(2,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP1_I2C1_SDA
  DAL_GPIO_CFG(3,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP1_I2C1_SCL
  DAL_GPIO_CFG(4,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP1_I2C2_SDA
  DAL_GPIO_CFG(5,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP1_I2C2_SCL
  DAL_GPIO_CFG(6,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA), // BLSP1_I2C3_SDA
  DAL_GPIO_CFG(7,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP1_I2C3_SCL
  DAL_GPIO_CFG(8,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP2_I2C0_SDA
  DAL_GPIO_CFG(9,   1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP2_I2C0_SCL
  DAL_GPIO_CFG(10,  1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP2_I2C1_SDA
  DAL_GPIO_CFG(11,  1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP2_I2C1_SCL
  DAL_GPIO_CFG(12,  1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP2_I2C2_SDA
  DAL_GPIO_CFG(13,  1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP2_I2C2_SCL
  DAL_GPIO_CFG(14,  1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP2_I2C3_SDA
  DAL_GPIO_CFG(15,  1,   DAL_GPIO_OUTPUT, DAL_GPIO_PULL_UP, DAL_GPIO_6MA), // BLSP2_I2C3_SCL

  DAL_GPIO_CFG(133, 0,   DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA),
  DAL_GPIO_CFG(134, 0,   DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA),
  DAL_GPIO_CFG(135, 0,   DAL_GPIO_OUTPUT, DAL_GPIO_NO_PULL, DAL_GPIO_2MA),
};

i2c_config_t *i2c_get_device(uint32_t idx)
{
    if(idx >= I2C_NUM_DEVICES) return NULL;

	i2c_devices[idx].appClkFreqKhz = DEFAULT_APP_CLK_FREQ_KHZ;

    return &i2c_devices[idx];
}

void boot_tlmm_init( void )
{
  uint32_t Idx;
  for (Idx = 0 ; Idx < (sizeof(TlmmConfigurationTable) /
                        sizeof(TlmmConfigurationTable[0])) ; Idx++) {
    HAL_tlmm_ConfigGpio(TlmmConfigurationTable[Idx]);
  }
  #if 0
  for (Idx = 0 ; Idx < (sizeof(TlmmInterruptConfigTable) /
                        sizeof(TlmmInterruptConfigTable[0])) ; Idx++) {
    HAL_tlmm_ConfigGpioIntr(TlmmInterruptConfigTable[Idx]);
  }
  for (Idx = 0 ; Idx < (sizeof(TlmmInterruptDirConfigTable) /
                        sizeof(TlmmInterruptDirConfigTable[0])) ; Idx++) {
    HAL_tlmm_ConfigGpioIntrDir(TlmmInterruptDirConfigTable[Idx]);
  }
  #endif
}
