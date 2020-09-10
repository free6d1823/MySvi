/*
 */
#ifndef __IRQ_SE1000_H_INCLUDE__
#define __IRQ_SE1000_H_INCLUDE__

#include <target/barrier.h>

#define UART_CON_IRQ			(90)
#define DW_WDT_TRQ(n)				(81 + n)
#define SPI_CON_IRQ(n)			(123 + n)
#define DW_TMR_TRQ(uid,tid)     	(70+uid*SUPPORT_TIMER_INTER_MAX_NUM+ tid)
#define DW_PWM_TRQ(uid)         	(89+uid)
#define GC355_IRQ	277
#define GC620_IRQ	276


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

//C71
#define C71_0_IRQ(n) (671+n)//(720 + n)
#define AFBC_ENC_IRQ 676//725
#endif  /* __IRQ_SE1000_H_INCLUDE__ */

