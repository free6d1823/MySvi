/*
 * =====================================================================================
 *
 *       Filename:  i2cs.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/16/2018 10:38:36 AM
 *
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  dusc ()
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <asm/mach/i2cs.h>
#include <target/irq.h>
#include <target/delay.h>
#include <target/cmdline.h>

i2cs_config_t i2cs_configs[] = {
    { .devid      = 0,
      .gpios      = {0x3001c0e2, 0x3001c0f2}, // GPIO 14-15
      .irq        = 152,
      .slave_addr = 0x23,
      .block_addr = I2C_S_DEVICE_ADDR(0),
    },
    { .devid      = 0,
      .gpios      = {0x3001c0c2, 0x3001c0d2}, //  GPIO 12-13
      .irq        = 153,
      .slave_addr = 0x24,
      .block_addr = I2C_S_DEVICE_ADDR(1),
    },
    { .devid      = 0,
      .gpios      = {0x3001c062, 0x3001c072},  // GPIO 6-7
      .irq        = 154,
      .slave_addr = 0x25,
      .block_addr = I2C_S_DEVICE_ADDR(2),
    },
    { .devid      = 0,
      .gpios      = {0x3001c042, 0x3001c052},  // GPIO 4-5
      .irq        = 155,
      .slave_addr = 0x26,
      .block_addr = I2C_S_DEVICE_ADDR(3),
    }
};

static I2CS_Device pDev;

static void I2CS_EnableInterrupts(void)
{
    I2C_S_SVRW(pDev.coreIdx, IRQ_EN, RX_DATA_AVAIL,1);
    I2C_S_SVRW(pDev.coreIdx, IRQ_EN, STRCH_RD,1);
    I2C_S_SVRW(pDev.coreIdx, IRQ_EN, STRCH_WR,1);
    I2C_S_SVRW(pDev.coreIdx, IRQ_EN, STOP_DETECTED,1);
    I2C_S_SVRW(pDev.coreIdx, IRQ_EN, CLOCK_LOW_TIMEOUT,1);
}

static void I2CS_DisableInterrupts(void)
{
    I2C_S_SVRW(pDev.coreIdx, IRQ_EN, CLOCK_LOW_TIMEOUT,1);
}

static void I2CS_SetCoreParameters(void)
{
    I2C_S_SET_ADDR(pDev.coreIdx, pDev.config->slave_addr);
    I2C_S_SPV(pDev.coreIdx, IRQ_CLR, 0x3FF);
    I2CS_EnableInterrupts();
    I2C_S_SBWO(pDev.coreIdx, CONTROL, CLEAR_TX_FIFO, 1);
    I2C_S_SBWO(pDev.coreIdx, CONTROL, CLEAR_RX_FIFO, 1);
    I2C_S_SVRW(pDev.coreIdx, CLK_LOW_TIMEOUT, TIMER_MODE, 1);
}

static void I2CS_EnableCore(void)
{
    I2C_S_SVRW(pDev.coreIdx, CONFIG, GCA_SUPPORTED, 1);
    I2C_S_SVRW(pDev.coreIdx, CONFIG,EN, 1);
}

static void I2CS_ResetDevice(void)
{
    I2C_S_SBWO(pDev.coreIdx, SW_RESET_REG, SW_RESET, 1);
}

uint32_t data_t = 0;
static void I2CS_Isr(void)
{
    uint32_t              register_data;
    uint32_t              enabled_ints;

    enabled_ints = GMASK(ERR_CONDITION) |
                   GMASK(STOP_DETECTED) |
                   GMASK(RX_DATA_AVAIL) |
                   GMASK(STRCH_RD)      |
                   GMASK(STRCH_WR)      |
                   GMASK(CLOCK_LOW_TIMEOUT);

    while(((register_data = I2C_S_GPV(pDev.coreIdx, IRQ_STATUS)) & enabled_ints)) {
        if(register_data & GMASK(CLOCK_LOW_TIMEOUT)) {
#ifdef I2CS_DEBUG
            printf("\ntimeout:0x%x\n",register_data);
#endif
            I2C_S_SPV(pDev.coreIdx, IRQ_CLR, register_data);
            break;
        }
        if(register_data & GMASK(STRCH_RD)) {
#ifdef I2CS_DEBUG
            printf("\nrd\n");
#endif
            /* I2C_S_SFWO(pDev.coreIdx,TX_FIFO,TX_FIFO_REG,0xaa); */
            I2C_S_TX(pDev.coreIdx, data_t);
            I2C_S_SBWO(pDev.coreIdx, CONTROL, ACK_RESUME, 1);
            I2C_S_SBWO(pDev.coreIdx, IRQ_CLR, STRCH_RD, 1);
        }
        if(register_data & GMASK(RX_DATA_AVAIL)) {
            uint32_t rx_data = 0xFF & I2C_S_GPV(pDev.coreIdx, RX_FIFO);
            data_t = rx_data;
#ifdef I2CS_DEBUG
            printf("\nrx_data=0x%x\n",rx_data);
#endif
            I2C_S_SBWO(pDev.coreIdx, IRQ_CLR, RX_DATA_AVAIL, 1);
            I2C_S_SBWO(pDev.coreIdx, CONTROL, ACK_RESUME, 1);
        }
        if(register_data & GMASK(STOP_DETECTED)) {
#ifdef I2CS_DEBUG
            printf("\nstop\n");
#endif
            I2C_S_SBWO(pDev.coreIdx, IRQ_CLR, STOP_DETECTED, 1);
        }
        if(register_data & GMASK(STRCH_WR)) {
#ifdef I2CS_DEBUG
            uint32_t wr_data = 0xFF & I2C_S_GPV(pDev.coreIdx, RX_FIFO);
            printf("\nwr_data = 0x%x\n",wr_data);
#endif
            I2C_S_SBWO(pDev.coreIdx, IRQ_CLR, STRCH_WR, 1);
            I2C_S_SBWO(pDev.coreIdx, CONTROL, ACK_RESUME, 1);
        }
        if(register_data & GMASK(ERR_CONDITION)) {
#ifdef I2CS_DEBUG
            printf("\nerr\n");
#endif
            I2CS_ResetDevice();
            I2CS_SetCoreParameters();
            I2CS_EnableCore();
            I2C_S_SBWO(pDev.coreIdx, IRQ_CLR, ERR_CONDITION, 1);
            I2C_S_SBWO(pDev.coreIdx, CONTROL, NACK, 1);
        }
    }
}

static void I2CS_GetDeviceById(uint8_t dev_index)
{
    pDev.config = &i2cs_configs[dev_index];
    pDev.coreIdx = dev_index;
}

static void I2CS_ConfigureGpios(void)
{
    uint32_t i;

    for(i = 0; i < I2CS_CONFIG_NUM_GPIOS; i ++) {
        uint32_t cfg   = pDev.config->gpios[i];
        uint64_t gpio  = (cfg >> 4)  & 0x3FF;

        _SET_WORD(I2C_S_HWIO_TLMM_GPIO_CFGn_ADDR(gpio),0x20b);
    }
}

static void arch_handle_i2cs(irq_t irq, void *ctx)
{
    I2CS_Isr();
}

static void  I2CS_RegisterIsr(void)
{
     irq_t irq = pDev.config->irq;
     irqc_configure_irq(irq, 0, IRQ_LEVEL_TRIGGERED);
     irq_register_vector(irq, arch_handle_i2cs, NULL);
     irqc_enable_irq(irq);
}

static void I2CS_SetCallbackFuncs(void)
{
    I2CS_ResetDevice();

    I2CS_SetCoreParameters();

    I2CS_RegisterIsr();

    I2CS_ConfigureGpios();

    I2CS_EnableCore();
}

void I2CS_AddDevice(int dev_index)
{
    I2CS_GetDeviceById(dev_index);
    I2CS_SetCallbackFuncs();
}

static void I2CS_Init(int num)
{
    printf("\nnum = %d\n",num);
    I2CS_AddDevice(num);
}

static int do_i2cs(int argc, char * argv[])
{
    int num;
    if (argc < 2) {
        return -1;
    }
    num = strtoul(argv[1], 0, 0);
    I2CS_Init(num);
    return 1;
}

MK_CMD(i2cs, do_i2cs, "initialize I2CSn",
    " \n"
    "initialize I2CSn\n"
    "   - i2cs {n}\n"
);
