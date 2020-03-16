/* Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
   All Rights Reserved.
   Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc. */

#include <target/gpio.h>
#include <asm/mach/hal/HALtlmmHWIO.h>
#include <asm/hal/HALhwio.h>

/* The enumeration for GPIO value(high or low) type. */
typedef enum
{
    HAL_TLMM_LOW_VALUE  = 0,
    HAL_TLMM_HIGH_VALUE = 1
}HAL_tlmm_ValueType;

void HAL_tlmm_WriteConfig( UINTN nGpioNumber, UINTN nConfig )
{
    HWIO_OUTI(TLMM_GPIO_CFGn, nGpioNumber, nConfig);
}

#define HAL_GPIO_CONFIG_MASK(cfg)   \
((HAL_PULL_VAL(cfg)   << 0x0) | \
 (HAL_FUNC_VAL(cfg)   << 0x2) | \
 (HAL_DRVSTR_VAL(cfg) << 0x6) | \
 (HAL_DIR_VAL(cfg)    << 0x9) )

#define HAL_GPIO_NUMBER(config) \
         ((0x20000000&(config))?(((config)&0x3FF0)>>4):(((config)&0xFF00)>>8))

#define HAL_RMT_VAL(config)     \
         ((0x20000000&(config))?(((config)&0x1E00000)>>0x15):(((config)&0xF0)>>4))

#define HAL_DRVSTR_VAL(config) \
         ((0x20000000&(config))?(((config)&0x1E0000)>>17):(((config)&0x380000)>>19))

#define HAL_PULL_VAL(config)   \
         ((0x20000000&(config))?(((config)&0x18000)>>15):(((config)&0x60000)>>17))

#define HAL_DIR_VAL(config)    \
         ((0x20000000&(config))?(((config)&0x4000)>>14):(((config)&0x10000)>>16))

#define HAL_FUNC_VAL(config)  ((config)&0xF)

#define HAL_GPIO_OUTVAL HAL_RMT_VAL

#define HAL_TLMM_NUM_GPIO          150

void HAL_tlmm_ConfigGpio( uint32_t nWhichConfig )
{
  UINTN nWhichGpio = HAL_GPIO_NUMBER(nWhichConfig);

  if( nWhichGpio < HAL_TLMM_NUM_GPIO )
  {
    HAL_tlmm_WriteConfig(nWhichGpio, (uint32_t)HAL_GPIO_CONFIG_MASK(nWhichConfig));

    /* If an output value was specified. */
    if( HAL_RMT_VAL(nWhichConfig) == HAL_TLMM_OUTPUT_LOW )
    {
      HWIO_OUTMI(TLMM_GPIO_IN_OUTn, nWhichGpio, \
                 HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK, \
                 ~(1UL << HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT));
    }
    else if( HAL_RMT_VAL(nWhichConfig) == HAL_TLMM_OUTPUT_HIGH )
    {
            HWIO_OUTMI(TLMM_GPIO_IN_OUTn, nWhichGpio, \
                 HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_BMSK, \
                 (1UL << HWIO_TLMM_GPIO_IN_OUTn_GPIO_OUT_SHFT));
    }
  }
}
