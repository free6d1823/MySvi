//#include <testos.h>
#include <target/readline.h>
#include <target/cmdline.h>
#include <target/console.h>
#include <target/uart.h>

#include <errno.h>
#include <target/dsr.h>
static int debug_dsr;
static uint8_t debug_events;

#define DEBUG_POLL		0x01
#define DEBUG_IRQ 		0x02

static void console_output_handler(void)
{
    return;
}

static void console_input_handler(void)
{
    while ((!!uart_poll()))
        readline_async();
}

static void console_raise_event(uint8_t event)
{
    debug_events |= event;
    dsr_schedule(debug_dsr);
}

static void console_dsr_handler(void* ctx)
{
    uint8_t events = debug_events;

    debug_events = 0;
    if (events & DEBUG_POLL) {
       console_output_handler();
       console_input_handler();
       console_raise_event(DEBUG_POLL);
    }
    if (events & DEBUG_IRQ) {
       console_input_handler();
       uart_irq_ack();
    }
}


int console_early_init(void)
{
#if defined(CONFIG_CONSOLE_INPUT) || defined(CONFIG_CONSOLE_OUTPUT)
    uart_init();
#endif
    return 0;
}

int console_late_init(void)
{
    debug_dsr = dsr_register(console_dsr_handler, NULL);

#ifdef CONFIG_CONSOLE_INPUT

#ifdef CONFIG_IRQ_POLLING
    console_raise_event(DEBUG_POLL);
#else
    uart_irq_init(true);
#endif

    readline_init();
#endif
    return 0;
}

void console_handle_irq(void)
{
#if defined(CONFIG_CONSOLE_INPUT)
    console_raise_event(DEBUG_IRQ);
#endif
}

static void __putc(char c)
{
	volatile char *tube = (volatile char*)0xa00b0000U;
	*tube = c;
}

int putchar(int c)
{
#ifdef CONFIG_CONSOLE_OUTPUT
    uart_putchar(c);
    return c;
#else
    return -1;
#endif
}

int getchar(void)
{
#ifdef CONFIG_CONSOLE_INPUT
    return uart_getchar();
#else
    return -1;
#endif
}
