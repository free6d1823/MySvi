/*
 */
#ifndef __UART_PL01X_H_INCLUDE__
#define __UART_PL01X_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>
#include <asm/io.h>


/* PrimeCell UART (PL011) Technical Reference Manual */
#define UART_REG(n, offset)	(UART_BASE(n)+(offset))
#define UART_FV(name, value)	_FV(UART_##name, value)
/* Register map */
/* ARM Server Base Architecture 5.0 Platform Design Document (DEN_0029B)
 * B.2 Generic UART register frame
 */
#define UARTDR(n)		UART_REG(n, 0x000) /* Data Register */
#define UARTDER(n)		(UARTDR(n)+1)	   /* Error part of UARTDR */
#define UARTRSR(n)		UART_REG(n, 0x004) /* Receive status and error clear register */
#define UARTECR(n)		UART_REG(n, 0x004) /* Receive status and error clear register */
#define UARTFR(n)		UART_REG(n, 0x018) /* Flag Register */
#define UARTRIS(n)		UART_REG(n, 0x03C) /* Raw Interrupt Status Register */
#define UARTMIS(n)		UART_REG(n, 0x040) /* Masked Interrupt Status Register */
#define UARTIMSC(n)		UART_REG(n, 0x038) /* Interrupt the current mask status */
#define UARTICR(n)		UART_REG(n, 0x044) /* Interrupt Clear Register */

/* Register field values */
/* UARTER/UARTRSR/UARTECR */
#define UART_FE			_BV(0)
#define UART_PE			_BV(1)
#define UART_BE			_BV(2)
#define UART_OE			_BV(3)

/* UARTFR */
#define UART_BUSY		_BV(3)
#define UART_RXFE		_BV(4)
#define UART_TXFF		_BV(5)
#define UART_RXFF		_BV(6)
#define UART_TXFE		_BV(7)

/* UARTIMSC/UARTRIS/UARTMIS/UARTICR */
#define UART_RXI		_BV(4)
#define UART_TXI		_BV(5)
#define UART_RTI		_BV(6)
#define UART_FEI		_BV(7)
#define UART_PEI		_BV(8)
#define UART_BEI		_BV(9)
#define UART_OEI		_BV(10)

#define pl01x_read_data(n)	__raw_readw(UARTDR(n))
#define pl01x_write_data(n, v)	__raw_writeb(v, UARTDR(n))
#define pl01x_read_error(n)	__raw_readb(UARTRSR(n))
#define pl01x_clear_error(n)	__raw_writeb(0, UARTECR(n))
#define pl01x_read_dataw(n, error)		\
	(uint16_t w = __raw_readw(UARTDR(n)),	\
	  *error = (uint8_t)((w) >> 8),		\
	 (uint8_t)((w) & 0xFF))
#define pl01x_write_full(n)	(__raw_readw(UARTFR(n)) & UART_TXFF)
#define pl01x_write_empty(n)	(__raw_readw(UARTFR(n)) & UART_TXFE)
#define pl01x_read_empty(n)	(__raw_readw(UARTFR(n)) & UART_RXFE)
#define pl01x_mask_irq(n, irq)		__raw_setw(irq, UARTIMSC(n))
#define pl01x_unmask_irq(n, irq)	__raw_clearw(irq, UARTIMSC(n))
#define pl01x_clear_irq(n, irq)		__raw_writew(irq, UARTICR(n))
#define pl01x_irq_status(n)		__raw_readw(UARTRIS(n))
#define pl01x_disable_all_irqs(n)	__raw_writew(0, UARTIMSC(n))

/* PrimeCell UART (PL011) Revision r1p5 Technical Reference Manual */
#ifndef CONFIG_PL01X_SBSA
#define UARTILPR(n)		UART_REG(n, 0x020)
#define UARTIBRD(n)		UART_REG(n, 0x024)
#define UARTFBRD(n)		UART_REG(n, 0x028)
#define UARTLCR_H(n)		UART_REG(n, 0x02C)
#define UARTCR(n)		UART_REG(n, 0x030)
#define UARTIFLS(n)		UART_REG(n, 0x034)
#define UARTDMACR(n)		UART_REG(n, 0x048)

#define UARTPeriphID0(n)	UART_REG(n, 0xFE0)
#define UARTPeriphID1(n)	UART_REG(n, 0xFE4)
#define UARTPeriphID2(n)	UART_REG(n, 0xFE8)
#define UARTPeriphID3(n)	UART_REG(n, 0xFEC)
#define UARTPCellID0(n)		UART_REG(n, 0xFF0)
#define UARTPCellID1(n)		UART_REG(n, 0xFF4)
#define UARTPCellID2(n)		UART_REG(n, 0xFF8)
#define UARTPCellID3(n)		UART_REG(n, 0xFFC)

/* Register field values */
/* UARTFR */
#define UART_CTS		_BV(0)
#define UART_DSR		_BV(1)
#define UART_DCD		_BV(2)
#define UART_RI			_BV(8)

/* UARTLCR_H */
#define UART_BRK		_BV(0)
#define UART_PEN		_BV(1)
#define UART_EPS		_BV(2)
#define UART_STP2		_BV(3)
#define UART_FEN		_BV(4)
#define UART_WLEN_OFFSET	5
#define UART_WLEN_MASK		0x03
#define UART_WLEN(value)	UART_FV(WLEN, value)
#define UART_SPS		_BV(7)

/* UARTCR */
#define UART_EN			_BV(0)
#define UART_SIREN		_BV(1)
#define UART_SIRLP		_BV(2)
#define UART_LBE		_BV(7)
#define UART_TXE		_BV(8)
#define UART_RXE		_BV(9)
#define UART_DTR		_BV(10)
#define UART_RTS		_BV(11)
#define UART_OUT1		_BV(12)
#define UART_OUT2		_BV(13)
#define UART_RTSEN		_BV(14)
#define UART_CTSEN		_BV(15)

/* UARTIFLS */
#define UART_TXIFLSEL_OFFSET	0
#define UART_TXIFLSEL_MASK	0x07
#define UART_TXIFLSEL(value)	UART_FV(TXIFLSEL, value)
#define UART_RXIFLSEL_OFFSET	3
#define UART_RXIFLSEL_MASK	0x07
#define UART_RXIFLSE(value)	UART_FV(RXIFLSEL, value)

/* UARTIMSC/UARTRIS/UARTMIS/UARTICR */
#define UART_RII		_BV(0)
#define UART_CTSI		_BV(1)
#define UART_DCDI		_BV(2)
#define UART_DSRI		_BV(3)

/* UARTDMACR */
#define UART_RXDMAE		_BV(0)
#define UART_TXDMAE		_BV(1)
#define UART_DMAONERR		_BV(2)

#define pl01x_ctrl_enable(n)					\
	do {							\
		__raw_setw(UART_FEN, UARTLCR_H(n));		\
		__raw_setw(UART_EN, UARTCR(n));			\
	} while (0)
#define pl01x_ctrl_disable(n)					\
	do {							\
		__raw_clearw(UART_EN, UARTCR(n));		\
		while (__raw_readw(UARTFR(n)) & UART_BUSY);	\
		__raw_clearw(UART_FEN, UARTLCR_H(n));		\
	} while (0)
#define pl01x_ctrl_disable_all(n)	__raw_writew(0, UARTCR(n))
#define pl01x_uart_enable(n)	__raw_setw(UART_TXE | UART_RXE, UARTCR(n))
#define pl01x_uart_disable(n)	__raw_clearw(UART_TXE | UART_RXE, UARTCR(n))

void pl01x_config_baudrate(uint8_t n, uint32_t src_clk, uint32_t baudrate);
void pl01x_config_params(uint8_t n, uint8_t params);
#endif /* CONFIG_PL01X_SBSA */

#endif /* __UART_PL01X_H_INCLUDE__ */
