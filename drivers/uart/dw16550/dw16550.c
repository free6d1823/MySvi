#include <target/uart.h>
#include <target/console.h>
#include <errno.h>
#include <target/utils.h>
#include "dw16550.h"

#define UART_LCRVAL UART_LCR_8N1		/* 8 data, 1 stop, no parity */
#define UART_MCRVAL (UART_MCR_DTR | \
		     UART_MCR_RTS)		/* RTS/DTR */


#define serial_out(x, y)	__raw_writel(x, y) //which register width should be used
#define serial_in(y)		__raw_readl(y)

static DW16550_t g_com_port;

#ifndef CONFIG_SYS_DW16550_IER
#define CONFIG_SYS_DW16550_IER  0x00
#endif /* CONFIG_SYS_DW16550_IER */

static u32 DW16550_getfcr(DW16550_t port)
{
	return UART_FCR_DEFVAL;
}


static int DW16550_calc_divisor(DW16550_t port, int clock, int baudrate)
{
	const unsigned int mode_x_div = 16;

	return DIV_ROUND_CLOSEST(clock, mode_x_div * baudrate);
}

static void DW16550_setbrg(DW16550_t com_port, int baud_divisor)
{
	/* to keep serial format, read lcr before writing DLAB */
	int lcr_val = serial_in(&com_port->lcr) & ~UART_LCR_DLAB;

	serial_out(UART_LCR_DLAB | lcr_val, &com_port->lcr);
	serial_out(baud_divisor & 0xff, &com_port->dll);
	serial_out((baud_divisor >> 8) & 0xff, &com_port->dlh);
	serial_out(lcr_val, &com_port->lcr);

	/*clear DLAB, let IER accessable*/
	serial_out(~UART_LCR_DLAB & lcr_val, &com_port->lcr);
}

static void DW16550_init(DW16550_t com_port)
{
	while (!(serial_in(&com_port->lsr) & UART_LSR_TEMT))
		;

	serial_out(CONFIG_SYS_DW16550_IER, &com_port->ier);

	serial_out(UART_MCRVAL, &com_port->mcr);
	serial_out(DW16550_getfcr(com_port), &com_port->fcr);
	/* initialize serial config to 8N1 before writing baudrate */
	serial_out(UART_LCRVAL, &com_port->lcr);
}

void DW16550_putc(DW16550_t com_port, char c)
{
	while ((serial_in(&com_port->lsr) & UART_LSR_THRE) == 0)
		;
	serial_out(c, &com_port->thr);
}

char DW16550_getc(DW16550_t com_port)
{
	return serial_in(&com_port->rbr);
}

static int DW16550_serial_putc(DW16550_t client_com_port, const char ch)
{
	struct NS16550 *const com_port = client_com_port;
	/*
	 * UART_LSR_THRE bit is set whenever data is transferred from the THR
	 * or TX FIFO to the transmitter shift register and no new data has
	 * been written to the THR or TX FIFO.
	 * when the FIFO is full results in the write data being lost.
	 */
	while (!(serial_in(&com_port->lsr) & UART_LSR_THRE))
		;
	serial_out(ch, &com_port->thr);

	return 0;
}

static int DW16550_serial_pending(DW16550_t client_com_port, bool input)
{
	struct NS16550 *const com_port = client_com_port;

	if (input)
		return (serial_in(&com_port->lsr) & UART_LSR_DR) ? 1 : 0;
	else
		return (serial_in(&com_port->lsr) & UART_LSR_THRE) ? 0 : 1;
}

static int DW16550_serial_getc(DW16550_t client_com_port)
{
	struct NS16550 *const com_port = client_com_port;

	if (!(serial_in(&com_port->lsr) & UART_LSR_DR))
		return -EAGAIN;

	return serial_in(&com_port->rbr);
}

static int DW16550_serial_setbrg(DW16550_t client_com_port, int clock, int baudrate)
{
	struct NS16550 *const com_port = client_com_port;

	int clock_divisor;

	clock_divisor = DW16550_calc_divisor(com_port, clock, baudrate);

	DW16550_setbrg(com_port, clock_divisor);

	return 0;
}

static int DW16550_serial_setconfig(DW16550_t client_com_port, uint serial_config)
{
	struct NS16550 *const com_port = client_com_port;
	int lcr_val = UART_LCR_WLS_8;
	uint parity = uart_parity(serial_config);
	uint bits = uart_bits(serial_config);
	uint stop = uart_stopb(serial_config);

	/*
	 * only parity config is implemented, check if other serial settings
	 * are the default one.
	 */
	if (bits != 8 || stop != UART_STOPB_ONE)
		return -ENOTSUP; /* not supported in driver*/

	switch (parity) {
	case UART_PARITY_NONE:
		/* no bits to add */
		break;
	case UART_PARITY_ODD:
		lcr_val |= UART_LCR_PEN;
		break;
	case UART_PARITY_EVEN:
		lcr_val |= UART_LCR_PEN | UART_LCR_EPS;
		break;
	default:
		return -ENOTSUP; /* not supported in driver*/
	}

	serial_out(lcr_val, &com_port->lcr);
	return 0;
}

static uint8_t uart_dw_read_byte(void)
{
	return DW16550_getc(g_com_port);
}

#define dw_uart_clk 25000000//need to confirm with HW,25MHz suppose
static void uart_dw_ctrl_init(void)
{
	g_com_port = (DW16550_t)UART_BASE(0);
	DW16550_init(g_com_port);
	DW16550_serial_setconfig(g_com_port, UART_DEF_PARAMS);
	DW16550_serial_setbrg(g_com_port, dw_uart_clk, UART_CON_BAUDRATE);
}

static void uart_dw_write_byte(uint8_t byte)
{
	DW16550_serial_putc(g_com_port, byte);
}

static bool uart_dw_read_poll(void)
{
	return DW16550_serial_pending(g_com_port, true);
}

static void dw_disable_all_irqs(DW16550_t client_com_port)
{
	struct NS16550 *const com_port = client_com_port;
	serial_out(0, &com_port->ier);
}

static void dw_mask_irq(DW16550_t client_com_port, int irq)
{
	struct NS16550 *const com_port = client_com_port;
	serial_out(irq, &com_port->ier);
}

/*not sure how to clear the irq. need the data sheet*/
#define RECEIVED_DATA_AVAILABLE 0x4
static void dw_check_irq(DW16550_t client_com_port, int irq)
{
	struct NS16550 *const com_port = client_com_port;

	int int_value =	serial_in(&com_port->iir);

	switch (irq) {
		case UART_IER_RDI:
			if (RECEIVED_DATA_AVAILABLE != (int_value & UART_IIR_RDI))
				printf("uart interrupt value 0x%x is not expected\n",int_value);
			break;
		default:
			break;
	}
}

static void dw_handle_irq(void)
{
	dw_check_irq(g_com_port, UART_IER_RDI);

	/*Disable all irq directly to mask data ready bit*/
	dw_disable_all_irqs(g_com_port);

	console_handle_irq();
}

static void uart_dw_irq_init(bool enable)
{
	irq_t uart_irq = UART_CON_IRQ;

	if (enable == false) {
		dw_disable_all_irqs(g_com_port);
		irqc_disable_irq(uart_irq);
	} else {
		dw_disable_all_irqs(g_com_port);
		irqc_configure_irq(uart_irq, 32, IRQ_LEVEL_TRIGGERED);
		irq_register_vector(uart_irq, dw_handle_irq);
		irqc_enable_irq(uart_irq);
		dw_mask_irq(g_com_port, UART_IER_RDI);
	}
}

static void uart_dw_irq_ack(void)
{
	dw_mask_irq(g_com_port, UART_IER_RDI);//enable interrupt again
}

uart_driver dw16550_uart_drvtable =
{
	"dw16550",
	uart_dw_read_byte,
	uart_dw_write_byte,
	uart_dw_read_poll,
	uart_dw_ctrl_init,
	uart_dw_irq_init,
	uart_dw_irq_ack,
};
