/*
 */
#ifndef __UART_QDF2400_H_INCLUDE__
#define __UART_QDF2400_H_INCLUDE__

#include <stdint.h>
#include <target/gpio.h>
#include <target/irq.h>
#include <asm/reg.h>
#include <asm/mach/clk.h>

/* Only support BLSP0 and BLSP3 on Qualcomm boards:
 * UART 0-3:  BLSP0 QUART
 * UART 4-5:  BLSP1 <- not implemented
 * UART 6-7:  BLSP2 <- not implemented
 * UART 8-11: BLSP3 ACUART
 */
#define QUART_BLSP0_BASE	ULL(0x0FF792D0000)
#define QUART_BLSP0_ID0		0
#define QUART_BLSP0_PCC		PCC_BLSP0_AHB_CBCR
#define QUART_BLSP3_BASE	ULL(0x0FF78ED0000)
#define QUART_BLSP3_ID0		8
#define QUART_BLSP3_PCC		PCC_BLSP3_AHB_CBCR

/* PCC clock block ID */
#define QUART_PCC_UART0		PCC_BLSP0_UART0 /* pcc_blsp0_uart0_apps_clk */
#define QUART_PCC_UART1		PCC_BLSP0_UART1 /* pcc_blsp0_uart1_apps_clk */
#define QUART_PCC_UART2		PCC_BLSP0_UART2 /* pcc_blsp0_uart2_apps_clk */
#define QUART_PCC_UART3		PCC_BLSP0_UART3 /* pcc_blsp0_uart3_apps_clk */
#define QUART_PCC_UART8		PCC_BLSP3_UART0 /* pcc_blsp3_uart0_apps_clk */
#define QUART_PCC_UART9		PCC_BLSP3_UART1 /* pcc_blsp3_uart1_apps_clk */
#define QUART_PCC_UART10	PCC_BLSP3_UART2 /* pcc_blsp3_uart2_apps_clk */
#define QUART_PCC_UART11	PCC_BLSP3_UART3 /* pcc_blsp3_uart3_apps_clk */

/* GPIO definitions, TX/RX/CTS/RTS use same multiplexer selection value,
 * So we needn't define each of them.
 */
#define QUART_GPIO_MUX_UART0	GPIO24_FUNC_BLSP0_Q_UART0_TX
#define QUART_GPIO_MUX_UART1	GPIO28_FUNC_BLSP0_Q_UART1_TX
#define QUART_GPIO_MUX_UART2	GPIO16_FUNC_BLSP0_Q_UART2_TX
#define QUART_GPIO_MUX_UART3	GPIO20_FUNC_BLSP0_Q_UART3_TX
#define QUART_GPIO_MUX_UART8	GPIO16_FUNC_BLSP3_AC_UART0_TX
#define QUART_GPIO_MUX_UART9	GPIO24_FUNC_BLSP3_AC_UART1_TX
#define QUART_GPIO_MUX_UART10	GPIO28_FUNC_BLSP3_AC_UART2_TX
#define QUART_GPIO_MUX_UART11	GPIO124_FUNC_BLSP3_AC_UART3_TX

#define QUART_GPIO_TX_UART0	24
#define QUART_GPIO_RX_UART0	25
#define QUART_GPIO_RTS_UART0	26
#define QUART_GPIO_CTS_UART0	27
#define QUART_GPIO_TX_UART1	28
#define QUART_GPIO_RX_UART1	29
#define QUART_GPIO_RTS_UART1	30
#define QUART_GPIO_CTS_UART1	31
#define QUART_GPIO_TX_UART2	16
#define QUART_GPIO_RX_UART2	17
#define QUART_GPIO_RTS_UART2	18
#define QUART_GPIO_CTS_UART2	19
#define QUART_GPIO_TX_UART3	20
#define QUART_GPIO_RX_UART3	21
#define QUART_GPIO_RTS_UART3	22
#define QUART_GPIO_CTS_UART3	23
#define QUART_GPIO_TX_UART8	16
#define QUART_GPIO_RX_UART8	17
#define QUART_GPIO_RTS_UART8	18
#define QUART_GPIO_CTS_UART8	19
#define QUART_GPIO_TX_UART9	24
#define QUART_GPIO_RX_UART9	25
#define QUART_GPIO_RTS_UART9	26
#define QUART_GPIO_CTS_UART9	27
#define QUART_GPIO_TX_UART10	28
#define QUART_GPIO_RX_UART10	29
#define QUART_GPIO_RTS_UART10	30
#define QUART_GPIO_CTS_UART10	31
#define QUART_GPIO_TX_UART11	124
#define QUART_GPIO_RX_UART11	125
#define QUART_GPIO_RTS_UART11	126
#define QUART_GPIO_CTS_UART11	127

#define QUART_TYPE_QUART	0x00
#define QUART_TYPE_ACUART	0x01
#define QUART_ACUART_BASE	8

/* Definitions to implement QUART */
#define UART_DM_BLOCK_SHIFT	16
#define UART_DM_ID(n)				\
	((n) < 4 ? ((n) - QUART_BLSP0_ID0) :	\
	((n) - QUART_BLSP3_ID0))
#define UART_DM_BASE(n)				\
	((n) < 4 ? QUART_BLSP0_BASE :		\
	QUART_BLSP3_BASE)
#define UART_DM_PCC_BLSP(n)			\
	((n) < 4 ? QUART_BLSP0_PCC :		\
	QUART_BLSP3_PCC)
#define UART_DM_PCC_UART(n)		QUART_PCC_UART##n
#define UART_DM_GPIO_MUX_UART(n)	QUART_GPIO_MUX_UART##n
#define UART_DM_GPIO_TX_UART(n)		QUART_GPIO_TX_UART##n
#define UART_DM_GPIO_RX_UART(n)		QUART_GPIO_RX_UART##n
#define UART_DM_GPIO_RTS_UART(n)	QUART_GPIO_RTS_UART##n
#define UART_DM_GPIO_CTS_UART(n)	QUART_GPIO_CTS_UART##n
#define UART_DM_IRQ(n)			IRQ_UART##n
#define UART_DM_TYPE(n)			QUART_TYPE_UART##__stringify(n)

#include <asm/mach/quart.h>

/* Definitions to implement ACUART */
#define UART_BASE(n)			(UART_DM_BASE(n) + 0x1000)
#define UART_CON_IRQ			(IRQ_UART8+UART_CON_ID-QUART_BLSP3_ID0)


void uart_hw_ctrl_init(void);
#ifdef CONFIG_CONSOLE_OUTPUT
void uart_hw_con_write(uint8_t byte);
#endif
#ifdef CONFIG_CONSOLE_INPUT
uint8_t uart_hw_con_read(void);
bool uart_hw_con_poll(void);
void uart_hw_irq_init(void);
void uart_hw_irq_ack(void);
#endif

#endif /* __UART_QDF2400_H_INCLUDE__ */
