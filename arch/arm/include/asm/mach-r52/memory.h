/*
 */
#ifndef __CORTEXR52_MEMORY_H_INCLUDE__
#define __CORTEXR52_MEMORY_H_INCLUDE__

#include <target/compiler.h>

#ifndef __ASSEMBLY__
extern unsigned int cfgperiphbase;
#endif

#define R52_ROM_BASE		0x10000000

#define R52_RAM_START		0x60000000
#define R52_RAM_SIZE		0x60000
#define R52_RAM_END		R52_RAM_START + R52_RAM_SIZE

#define SVI_TEXT_BASE		R52_RAM_START
#define SVI_RAM_END		R52_RAM_END


#define PAGE_SIZE		4096

#define CFGPERIPHBASE		cfgperiphbase

#define GICD_gic3_BASE		CFGPERIPHBASE
#define GICR_gic3_BASE		(CFGPERIPHBASE+0x100000)
#define GICR_GIC3_CPU_SHIFT	17

#define UART_BASE(n)		0x0E94A0000
#define DW_I2C_REG_BASE(n)		(0x0E9020000 + (n*0x10000))
#define DW_SPI_REG_BASE(n)		(0x0E96E0000 + (n*0x10000))
#define DW_SPI_SLAVE_REG_BASE(n)		(0x0E96D0000 + (n*0x10000))

#define CLK_RESET_REG_BASE			0x58100000

#define ARCH_TIMER_FREQUENCY 200000000

#endif /* __CORTEXR52_MEMORY_H_INCLUDE__ */
