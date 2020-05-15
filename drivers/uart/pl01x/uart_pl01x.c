/*
 */
#include <target/uart.h>
#include <target/console.h>
#include <target/regdef.h>
#include "uart_pl01x.h"


//#define UART_CON_ID 0

#ifndef CONFIG_PL01X_SBSA
/* compute the baud rate divisor
 * BRDDIV = BRDi + BRDf = CLK_UART / (16 * baudrate)
 *
 * we will compute 64*BRDDIV+0.5 to get DIVINT & DIVFRAC value
 * DIVINT  = (64*BRDi+0.5) / 64
 * DIVFRAC = (64*BRDf+0.5) % 64
 *
 * DIVCFG = 64*BRDDIV+0.5
 *        = ((64 * CLK_UART * 1000) / (16 * baudrate)) + 0.5
 *        = ((CLK_UART * 64000) / (16 * baudrate)) + 0.5
 *        = ((CLK_UART * 4000) / (baudrate)) + 0.5
 *        = (((CLK_UART * 20) / (baudrate/400)) + 1) / 2
 */
/* Since fractional part is based on the 64 (2^6) times of the BRD,
 * 6 is define as FBRD offset here.
 */
#define PL01X_BRDDIV_OFFSET	6
#define PL01X_BRDDIV_MASK	((1<<PL01X_BRDDIV_OFFSET)-1)


void pl01x_config_baudrate(uint8_t n, uint32_t src_clk, uint32_t baudrate)
{
	uint32_t cfg;

	cfg = (1 + (((src_clk / 1000) * 20) / (baudrate / 400))) / 2;
	__raw_writew(cfg >> PL01X_BRDDIV_OFFSET, UARTIBRD(n));
	__raw_writeb(cfg  & PL01X_BRDDIV_MASK, UARTFBRD(n));
}

void pl01x_config_params(uint8_t n, uint8_t params)
{
	uint8_t cfg;

	cfg = UART_WLEN(uart_bits(params)-5);
	switch (uart_parity(params)) {
	case UART_PARITY_EVEN:
		cfg |= UART_EPS;
	case UART_PARITY_ODD:
		cfg |= UART_PEN;
		break;
	}
	if (uart_stopb(params))
		cfg |= UART_STP2;
	__raw_writeb_mask(cfg, 0xEE, UARTLCR_H(n));
}
#endif


static void pl01x_write_byte(uint8_t byte)
{
	while (pl01x_write_full(UART_CON_ID));
	pl01x_write_data(UART_CON_ID, byte);
	//while (!pl01x_write_empty(UART_CON_ID));
}


static bool pl01x_read_poll(void)
{
	return !pl01x_read_empty(UART_CON_ID);
}


static uint8_t pl01x_read_byte(void)
{
	return pl01x_read_data(UART_CON_ID);
}

static void pl01x_handle_irq(irq_t irq, void *ctx)
{
	//irqc_disable_irq(uart_irq);
	pl01x_clear_irq(UART_CON_ID, pl01x_irq_status(UART_CON_ID));
	//pl01x_unmask_irq(UART_CON_ID, UART_RXI | UART_RTI);
	console_handle_irq();
}

static void pl01x_irq_init(bool enable)
{
	irq_t uart_irq = UART_CON_IRQ;

	if (enable == false) {
		pl01x_disable_all_irqs(UART_CON_ID);
		irqc_disable_irq(uart_irq);
	} else {
		pl01x_disable_all_irqs(UART_CON_ID);
		irqc_configure_irq(uart_irq, 32, IRQ_LEVEL_TRIGGERED);
		irq_register_vector(uart_irq, pl01x_handle_irq, NULL);
		irqc_enable_irq(uart_irq);
		pl01x_mask_irq(UART_CON_ID, UART_RXI | UART_RTI);
	}
}

void pl01x_irq_exit(void)
{
	irq_t uart_irq = UART_CON_IRQ;

	pl01x_disable_all_irqs(UART_CON_ID);
	irqc_disable_irq(uart_irq);
}

static void pl01x_irq_ack(void)
{
	//pl01x_mask_irq(UART_CON_ID, UART_RXI | UART_RTI);
	//irqc_enable_irq(uart_irq);
}

static void pl01x_init()
{
#ifndef CONFIG_PL01X_SBSA
	pl01x_config_params(UART_CON_ID, UART_DEF_PARAMS);
	pl01x_config_baudrate(UART_CON_ID, 100000000, UART_CON_BAUDRATE);
#endif
	pl01x_uart_enable(UART_CON_ID);
	pl01x_ctrl_enable(UART_CON_ID);
}

uart_driver pl01x_uart_drvtable =
{
	"pl01x",
	pl01x_read_byte,
	pl01x_write_byte,
	pl01x_read_poll,
	pl01x_init,
	pl01x_irq_init,
	pl01x_irq_ack,
};
