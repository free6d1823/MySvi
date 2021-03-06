/*
 */
#ifndef __CORTEXM4_MEMORY_H_INCLUDE__
#define __CORTEXM4_MEMORY_H_INCLUDE__

#include <target/compiler.h>

/* sram: share memory and m4 only */
#define SHARED_SRAM_START   0x00000000
#define SHARED_SRAM_SIZE    0x10000
#define SHARED_SRAM_END     SHARED_SRAM_START + SHARED_SRAM_SIZE

#define PRIVATE_SRAM_START  0x1fff1000
#define PRIVATE_SRAM_SIZE   0x10000
#define PRIVATE_SRAM_END    PRIVATE_SRAM_START + PRIVATE_SRAM_SIZE


#define SVI_TEXT_BASE       SHARED_SRAM_START

#define SVI_RAM_END         PRIVATE_SRAM_END

/* external ddr region */

/* Memory mapping of Cortex-M0 Hardware */
#define SCS_BASE			(0xE000E000UL)			/*!< System Control Space Base Address */
#define SysTick_BASE			(SCS_BASE +  0x0010UL)		/*!< SysTick Base Address */
#define NVIC_BASE			(SCS_BASE +  0x0100UL)		/*!< NVIC Base Address */
#define SCB_BASE			(SCS_BASE +  0x0D00UL)		/*!< System Control Block Base Address */

#define PAGE_SIZE			4096

#define HEAP_START			PRIVATE_SRAM_START

#define UART_BASE(n)			0x0E94A0000
#define DW_WDT_REG_BASE(n)		(n < CONFIG_SUPPORT_SPU_WDT ? (0x0E9410000 + (n*0x10000)):0x040020000)
#define DW_I2C_REG_BASE(n)		(0x0E9020000 + (n*0x10000))
#define DW_SPI_REG_BASE(n)		(0x0E96E0000 + (n*0x10000))
#define DW_SPI_SLAVE_REG_BASE(n)		(0x0E96D0000 + (n*0x10000))

#define CLK_RESET_REG_BASE			0x58100000
#endif /* __CORTEXM4_MEMORY_H_INCLUDE__ */

