/*
 */
#ifndef __IRQ_CORTEXM4_H_INCLUDE__
#define __IRQ_CORTEXM4_H_INCLUDE__

#include <target/barrier.h>

/* IRQ NUMBER */
#define IRQ__UART0	104
#define UART_CON_IRQ	(1)

#define NR_IRQS		(240)

#ifdef CONFIG_IRQ_POLLING
#define do_idle()
#else
#define do_idle()
#endif

#endif  /* __IRQ_CORTEXM4_H_INCLUDE__ */
