/*
 */
#ifndef __CORTEXR52_MEMORY_H_INCLUDE__
#define __CORTEXR52_MEMORY_H_INCLUDE__

#include <target/compiler.h>
#include <target/cpus.h>

#define R52_ROM_BASE 0x10000000
#define R52_RAM_BASE 0x60000000


#define PAGE_SIZE			4096

#ifndef HEAP_START
#define HEAP_START	0x20000000
#define HEAP_END	0x20000000
#endif

#define CFGPERIPHBASE       0xAE000000

#define GICD_gic3_BASE		CFGPERIPHBASE
#define GICR_gic3_BASE		(CFGPERIPHBASE+0x100000)
#define GICR_GIC3_CPU_SHIFT		17

#define UART_BASE(n)		0xC1210000

#endif /* __CORTEXR52_MEMORY_H_INCLUDE__ */
