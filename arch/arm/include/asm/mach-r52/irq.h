/*
 */
#ifndef __IRQ_CORTEXM4_H_INCLUDE__
#define __IRQ_CORTEXM4_H_INCLUDE__

#include <target/barrier.h>

#define IRQ_SGI_BASE	0
#define IRQ_PPI_BASE	16
#define IRQ_SPI_BASE	32

/* Special INTIDs */
#define IRQ_ACK_SEL1	1020 /* Acked IRQ should be handled at Secure EL1 */
#define IRQ_ACK_NSEL1	1021 /* Acked IRQ should be handled at Non-secure EL1 */
#define IRQ_ACK_NONE	1023 /* No pending IRQ with sufficient priority */

/* IRQ NUMBER */
#define IRQ__UART0	     33
#define UART_CON_IRQ	 35

#define NR_QGIC3_IRQS	1024
#define NR_IRQS			1024

#ifdef CONFIG_IRQ_POLLING
#define do_idle()
#else
#define do_idle()
#endif

#endif  /* __IRQ_CORTEXM4_H_INCLUDE__ */
