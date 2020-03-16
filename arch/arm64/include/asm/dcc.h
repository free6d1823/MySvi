/*
 */
#ifndef __ARM64_DCC_H_INCLUDE__
#define __ARM64_DCC_H_INCLUDE__

#include <stdbool.h>
#include <asm/reg.h>

unsigned long __dcc_status(void);
void __dcc_write(unsigned long dbg_data);
unsigned long __dcc_read(void);

int dcc_getchar(void);
int dcc_putchar(int c);
int dcc_getchar_async(void);
int dcc_putchar_async(int c);
bool dcc_poll(void);

#endif /* __ARM64_DCC_H_INCLUDE__ */
