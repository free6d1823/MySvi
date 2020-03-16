/*
 */
#ifndef __QDF2400_MEMORY_H_INCLUDE__
#define __QDF2400_MEMORY_H_INCLUDE__

#include <target/compiler.h>
#include <target/cpus.h>

#define RAM_START		0x40000000
#define RAM_SIZE		0x40000000
#define RAM_END			(RAM_START + RAM_SIZE)

#define SVI_TEXT_BASE	RAM_START
#define SVI_RAM_END		(RAM_START + 0x180000)

#define PAGE_SIZE			4096

#define SEC_SRAM_BASE		0x0e000000
#define CPU_HOLD_BASE		(SEC_SRAM_BASE)

#define UART_BASE(n)		(0x09000000)

#define GICD_gic3_BASE			ULL(0x08000000)
#define GICR_gic3_BASE			ULL(0x080A0000)
#define GICR_GIC3_CPU_SHIFT		17

#define SMMU_V3_BASE			ULL(0x09050000)


#endif /* __QDF2400_MEMORY_H_INCLUDE__ */
