#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <target/uart.h>


/* uart driver api interface table
*/
static uart_driver* all_uart_drvtable [] = {
#ifdef CONFIG_UART_PL01X
    &pl01x_uart_drvtable,
#endif
#ifdef CONFIG_UART_QUART
    &dm_uart_drvtable,
#endif
#ifdef CONFIG_UART_DW16550
    &dw16550_uart_drvtable
#endif
};


uart_driver* current_uart = NULL;

bool uart_console_select(const char* uart_driver_name)
{
    int i;
    int uart_nums = sizeof(all_uart_drvtable) / sizeof(all_uart_drvtable[0]);

    for (i=0; i<(uart_nums+1); i++) {
       if(0 == strcmp(uart_driver_name, all_uart_drvtable[i]->name))
           break;
    }

    if (i == uart_nums) {
        current_uart = NULL;
        return 0;
    }
    else
        current_uart = all_uart_drvtable[i];

    return 1;
}

int uart_init(void)
{
    if (NULL == current_uart) {
        /*Should dead here. workaroud for backward compatibility
        */
        current_uart = all_uart_drvtable[0];
    }

    if (current_uart && current_uart->hwinit) {
        current_uart->hwinit();
    }

	return 0;
}


void uart_putchar(uint8_t byte)
{
    if (current_uart->putchar)
        current_uart->putchar(byte);
}

bool uart_poll(void)
{
    if (current_uart->poll) {
        return current_uart->poll();
    }
    return 0;
}


uint8_t uart_getchar(void)
{
    if (current_uart->getchar)
        return current_uart->getchar();

    return 0;
}

void uart_irq_init(bool enable)
{
    if (current_uart->irq_init)
        current_uart->irq_init(enable);
}

void uart_irq_ack(void)
{
    if (current_uart->irq_ack)
        current_uart->irq_ack();
}