/*
This file keep uart common information, such as uart bound rate,
which  uart device should be used.
 */
#ifndef __UART_H_INCLUDE__
#define __UART_H_INCLUDE__

#include <stdint.h>
#include <stdbool.h>
#include <target/irq.h>
#include <asm/reg.h>

#ifdef CONFIG_UART_PL01X_DEV0
#define UART_CON_ID		0
#endif
#ifdef CONFIG_UART_PL01X_DEV1
#define UART_CON_ID		1
#endif
#ifdef CONFIG_UART_PL01X_DEV2
#define UART_CON_ID		2
#endif


#ifdef CONFIG_UART_DUMMY_DEV0
#define UART_CON_ID		8 /* sample code for new added uart*/
#endif
#ifdef CONFIG_UART_DUMMY_DEV0
#define UART_CON_ID		9
#endif


#define UART_BITS_MASK		0x0F
#define UART_PARITY_MASK	0x30
#define UART_STOPB_MASK		0x40
#define uart_bits(p)		((p)&UART_BITS_MASK)
#define uart_parity(p)		((p)&UART_PARITY_MASK)
#define uart_stopb(p)		((p)&UART_STOPB_MASK)


#define UART_PARITY_NONE	0x00
#define UART_PARITY_ODD		0x10
#define UART_PARITY_EVEN	0x20

#define UART_STOPB_ONE		0x00
#define UART_STOPB_TWO		0x40

#define UART_DEF_PARAMS		(8 | UART_PARITY_NONE | UART_STOPB_ONE)

#ifdef CONFIG_UART_CON_BAUDRATE
#define UART_CON_BAUDRATE	 CONFIG_UART_CON_BAUDRATE
#else
#error "UART CON BAUDRATE not set"
#endif


typedef struct uart_driver {
    char    name[16];
    uint8_t (* getchar)(void);
    void (* putchar)(uint8_t byte);
    bool (* poll)(void);
    void (* hwinit)(void);
    void (* irq_init)(bool);
    void (* irq_ack)(void);
} uart_driver;



uint8_t uart_getchar(void);
bool uart_poll(void);
void uart_irq_init(bool);
void uart_irq_ack(void);
void uart_putchar(byte);
int uart_init(void);

/*when multiple uarts are available, select the uart drvier by name*/
bool uart_console_select(const char* uart_driver_name);


extern uart_driver pl01x_uart_drvtable;

extern uart_driver dw16550_uart_drvtable;

extern uart_driver dm_uart_drvtable;


#endif /* __TESTOS_UART_H_INCLUDE__ */
