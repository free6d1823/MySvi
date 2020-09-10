/*
 */
#ifndef __IRQ_CORTEXM4_H_INCLUDE__
#define __IRQ_CORTEXM4_H_INCLUDE__

#include <target/barrier.h>

/* IRQ NUMBER */
#define IRQ__UART0	104
#define UART_CON_IRQ	(1)
#define DW_WDT_TRQ(n)	(10 + n)
#define DW_TMR_TRQ(uid,tid)	(71+uid*SUPPORT_TIMER_INTER_MAX_NUM+ tid)
#define DW_PWM_TRQ(uid)		(90+uid)

#define NR_IRQS		(240)

#ifdef CONFIG_IRQ_POLLING
#define do_idle()
#else
#define do_idle()
#endif

#endif  /* __IRQ_CORTEXM4_H_INCLUDE__ */
