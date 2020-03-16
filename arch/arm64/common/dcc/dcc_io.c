/*
 */
#include <stdint.h>
#include <stdbool.h>
#include <asm/dcc.h>

int dcc_putchar_async(int c)
{
    __dcc_write(c);
    return 0;
}

int dcc_getchar_async(void)
{
    return (int)__dcc_read();
}

int dcc_putchar(int c)
{
    int timeout_count = 0;

    while ((__dcc_status() & MDCCSR_TXFULL) != 0) {
        if (0xFFFF == ++timeout_count)
            return 0xFFFF;
    }
    __dcc_write(c);
    return 0;
}

int dcc_getchar(void)
{
    while ((__dcc_status() & MDCCSR_RXFULL) == 0) {
    }
    return (int)__dcc_read();
}

bool dcc_poll(void)
{
    uint32_t dscr_flag = __dcc_status();

    return !!(!(dscr_flag & MDCCSR_RXFULL));
}
