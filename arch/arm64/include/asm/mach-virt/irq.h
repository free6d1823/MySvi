/*
 */
#ifndef __IRQ_QDF2400_H_INCLUDE__
#define __IRQ_QDF2400_H_INCLUDE__

#include <target/barrier.h>

/* =================================================================
 * QGICv2 IRQs (IMC IRQS)
 * ================================================================= */
/* BAM UART */
#define IRQ_UART0	104
#define IRQ_UART1	105
#define IRQ_UART2	106
#define IRQ_UART3	107
#define IRQ_UART8	130
#define IRQ_UART9	131
#define IRQ_UART10	132
#define IRQ_UART11	133

#define ARCH_TIMER_FREQUENCY	62500000
#define UART_CON_IRQ			(31+2)

/* IMEM error capture */
#define IRQ_SYS_IMEM	167
#define IRQ_MSG_IMEM	283
#define IRQ_RAM_0_IMEM	320
#define IRQ_RAM_1_IMEM	322
#define IRQ_RAM_2_IMEM	324
#define IRQ_RAM_3_IMEM	439
#define IRQ_RAM_4_IMEM	441
#define IRQ_RAM_5_IMEM	446

#define NR_QGIC2_IRQS	512

/* =================================================================
 * QGICv3 IRQs (APC IRQS)
 * ================================================================= */
#define NR_QGIC3_IRQS	1024

#define NR_IRQS		(NR_QGIC2_IRQS + NR_QGIC3_IRQS)

#ifdef CONFIG_IRQ_POLLING
#define do_idle()
#else
#define do_idle()	wfi()
#endif

#endif  /* __IRQ_QDF2400_H_INCLUDE__ */
