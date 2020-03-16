#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <target/cmdline.h>
#include <hdts/Base.h>
#include <asm/mach/hal/HALspiHWIO.h>

#include "spi_slave_api.h"
#include "spi_slave_hwio.h"
#include "spi_slave_config.h"


/*---------------------------Structure Definitions----------------------------*/
typedef struct
{
    uint32_t uGpio_SckCfg;  // GPIO Cfg for SCK
    uint32_t uGpio_MosiCfg; // GPIO Cfg for MOSI
    uint32_t uGpio_MisoCfg; // GPIO Cfg for MISO
    uint32_t uGpio_SsCfg;   // GPIO Cfg for SS
    uint32_t uIrqId;        // Interrupt Number
    uint32_t uIrqEn;        // Are interrupts enabled?
    uint64_t uBaseAddr;     // Base address of the SPI Slave core
    uint64_t uExtAddr;      // Base address used by SPI Slave core during R/W
    uint32_t uCfgData;      // Settings for the SPI_SLAVE_CONFIG register
    uint32_t uTrnsLen;      // Transfer length (1<N<64k)
} spi_slave_config;

/*---------------------------Local Variables----------------------------------*/
static BOOLEAN init_done;

/*---------------------------Local Functions----------------------------------*/
static spi_slave_status spi_slave_ConfigGpios(spi_slave_config * sCfg)
{
    uint32_t gpioCfg[SPI_SLAVE_GPIO_COUNT];
    uint32_t i;
    gpioCfg[0] = sCfg->uGpio_SckCfg;
    gpioCfg[1] = sCfg->uGpio_MosiCfg;
    gpioCfg[2] = sCfg->uGpio_MisoCfg;
    gpioCfg[3] = sCfg->uGpio_SsCfg;

    for(i=0; i<SPI_SLAVE_GPIO_COUNT; i++)
    {
        if(gpioCfg[0]==0)
        {
            continue;
        }
        uint32_t cfg   = gpioCfg[i];
        uint32_t func  = cfg & 0x0F;
        uint32_t pull  = (cfg >> 15) & 0x3;
        uint32_t drive = (cfg >> 17) & 0xF;
        uint64_t gpio  = (cfg >> 4)  & 0x3FF;

        GPIO_SET_FUNC(gpio, func);
        GPIO_SET_STR(gpio, drive);
        GPIO_SET_PULL(gpio, pull);
        GPIO_OUT_EN(gpio);
    }
    return SPI_SLAVE_SUCCESS;
}

static spi_slave_status spi_slave_ReadConfig(spi_slave_config * sCfg)
{
    sCfg->uIrqEn        = SPI_SLAVE_IRQ_ENABLED;
    sCfg->uIrqId        = SPI_SLAVE_CHIP_IRQ_ID;
    sCfg->uGpio_SckCfg  = SPI_SLAVE_GPIO_CFG_SCK;
    sCfg->uGpio_MosiCfg = SPI_SLAVE_GPIO_CFG_MOSI;
    sCfg->uGpio_MisoCfg = SPI_SLAVE_GPIO_CFG_MISO;
    sCfg->uGpio_SsCfg   = SPI_SLAVE_GPIO_CFG_SS;
    sCfg->uBaseAddr     = SPI_SLAVE_CHIP_BASE_ADDR;
    sCfg->uExtAddr      = SPI_SLAVE_EXT_BASE_ADDR;
    sCfg->uCfgData      = SPI_SLAVE_CONFIG;
    sCfg->uTrnsLen      = SPI_SLAVE_TRNS_LEN;
    return SPI_SLAVE_SUCCESS;
}

// dis=1 = Disable Core.  dis=0 = Enable core
static void spi_slave_SetDisable(spi_slave_config * sCfg, uint32_t dis)
{
    WRITE_REGISTER32(HWIO_SPI_SLAVE_CONFIG_ADDR,
                    ~HWIO_SPI_SLAVE_CONFIG_CORE_DIS_BMSK,
                     dis);
}

static spi_slave_status spi_slave_SetupInterrupts(spi_slave_config * sCfg)
{
    uint32_t register_mask;
    if(sCfg->uIrqEn)
    {
        return SPI_SLAVE_ERR_NOT_SUPPORTED;
    }
    else
    {
        register_mask = HWIO_SPI_SLAVE_IRQ_STATUS_TXREG_UERR_BMSK     |
                        HWIO_SPI_SLAVE_IRQ_EN_TXFIFO_UERR_IRQ_EN_BMSK |
                        HWIO_SPI_SLAVE_IRQ_EN_RXFIFO_OERR_IRQ_EN_BMSK |
                        HWIO_SPI_SLAVE_IRQ_EN_HRESPERR_IRQ_EN_BMSK    |
                        HWIO_SPI_SLAVE_IRQ_EN_SW_RESET_IRQ_EN_BMSK;

        WRITE_REGISTER32(HWIO_SPI_SLAVE_IRQ_EN_ADDR, ~register_mask, 0);

        /* Clear all IRQs */
        WRITE_ONLY_REGISTER32(HWIO_SPI_SLAVE_IRQ_CLR_ADDR, 0xF0000000);
    }
    return SPI_SLAVE_SUCCESS;
}

// Set up the SLAVE_CONFIG and TRNS_LEN register
static void spi_slave_SetConfig(spi_slave_config * sCfg)
{
    uint32_t register_mask = HWIO_SPI_SLAVE_CONFIG_HOST_CTRL_BMSK     |
                           HWIO_SPI_SLAVE_CONFIG_N_DUMMY_BMSK       |
                           HWIO_SPI_SLAVE_CONFIG_ADDR_BYTE_LEN_BMSK |
                           HWIO_SPI_SLAVE_CONFIG_ACC_SIZE_BMSK;
    WRITE_REGISTER32(HWIO_SPI_SLAVE_CONFIG_ADDR,
                    ~register_mask,
                     sCfg->uCfgData);

    register_mask = HWIO_SPI_SLAVE_TRNS_LEN_LENGTH_BMSK;
    WRITE_REGISTER32(HWIO_SPI_SLAVE_TRNS_LEN_ADDR,
                    ~register_mask,
                     sCfg->uTrnsLen);
}

// Set the Slave Initialized Bit
static void spi_slave_SetInit(spi_slave_config * sCfg)
{
    uint32_t register_mask = HWIO_SPI_SLAVE_CONFIG_INIT_BMSK;
    WRITE_REGISTER32(HWIO_SPI_SLAVE_CONFIG_ADDR, ~register_mask, register_mask);
}

// Set the Slave External Base Address register
static void spi_slave_SetExtBaseAddr(spi_slave_config * sCfg)
{
    WRITE_REGISTER32(HWIO_SPI_SLAVE_EXT_BASE_ADDR_ADDR,
                    ~HWIO_SPI_SLAVE_EXT_BASE_ADDR_RMSK,
                     sCfg->uExtAddr >> 16);
}
static spi_slave_status spi_slave_CheckSanity()
{
    if( SPI_SLAVE_SANITY_VALUE != READ_REGISTER32(HWIO_SPI_SLAVE_SANITY_ADDR) )
    {
        return SPI_SLAVE_ERR_SANITY;
    }
    else
    {
        return SPI_SLAVE_SUCCESS;
    }
}

/** @brief Initialize Clocks

    @param[in]  None
    @param[out] None
  */
static void initialize_spi_slave_clocks()
{
    /* Clocks are already initialized */
}
/*---------------------------Global Functions---------------------------------*/
static spi_slave_status core_initialize(spi_slave_init_params * params)
{
    /* Local Variables */
    spi_slave_config sCfg;
    spi_slave_status status;

    if( SPI_SLAVE_INTERRUPT_MODE == params->dmaMode)
    {
        return SPI_SLAVE_ERR_NOT_SUPPORTED;
    }

    /* Check if init already done */
    if( TRUE == init_done )
    {
        return SPI_SLAVE_SUCCESS;
    }

    /* Initialize SPI Slave Clocks */
    initialize_spi_slave_clocks();

    if(SPI_SLAVE_SUCCESS != (status = spi_slave_CheckSanity()))
    {
        return status;
    }
    if(SPI_SLAVE_SUCCESS != (status = spi_slave_ReadConfig(&sCfg)))
    {
        return status;
    }
    if(SPI_SLAVE_SUCCESS != (status = spi_slave_ConfigGpios(&sCfg)))
    {
        return status;
    }

    /* Initialize Slave Core */
    spi_slave_SetDisable(&sCfg, 1);

    spi_slave_SetConfig(&sCfg);
    spi_slave_SetupInterrupts(&sCfg);
    spi_slave_SetInit(&sCfg);
    spi_slave_SetExtBaseAddr(&sCfg);

    spi_slave_SetDisable(&sCfg, 0);

    /* Core is now ready */
    init_done = TRUE;
    return SPI_SLAVE_SUCCESS;
}

spi_slave_status spi_slave_init()
{
    /* Local Variable */
    spi_slave_init_params   ssip={SPI_SLAVE_DMA_MODE};

    spi_slave_status status;

    /* Initialize Core */
    status = core_initialize(&ssip);

    return status;
}


int do_spi_slave(int argc, char *argv[])
{
    int ret = 0;

    if (strcmp("init", argv[1]) == 0)
    {
       if(spi_slave_init() != 0)
       {
           printf("spi slave init failed! \n");
           ret = -1;
       }
       printf("spi slave has been initialized! \n");
    }

    return ret;
}

MK_CMD(spi_slave, do_spi_slave, "spi slave init",
    "\n"
    " spi_slave {init} \n"
    "    -Initialize the spi slave core  \n"
);





