/*
 */
#ifndef __IRQ_SE1000_H_INCLUDE__
#define __IRQ_SE1000_H_INCLUDE__

#include <target/barrier.h>

#define UART_CON_IRQ			(111)
#define DW_WDT_TRQ(n)				(82 + n)

/* =================================================================
 * QGICv3 IRQs (APC IRQS)
 * ================================================================= */
#define NR_QGIC3_IRQS	1024
#define NR_IRQS		    NR_QGIC3_IRQS

#ifdef CONFIG_IRQ_POLLING
#define do_idle()
#else
#define do_idle()	wfi()
#endif

#endif  /* __IRQ_SE1000_H_INCLUDE__ */

