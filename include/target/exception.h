#ifndef __TESTOS_EXCEPTION_H_INCLUDE__
#define __TESTOS_EXCEPTION_H_INCLUDE__

#include <asm/exception.h>

/* special for apc exception handler */
typedef void (*ex_handler)(const char* msg);

void do_irq(struct pt_regs *pt_regs);
void register_exception_handler(ex_handler entry);
void std_svc_smc_handler(struct pt_regs *regs, unsigned int esr, int reason);


#endif /* __TESTOS_EXCEPTION_H_INCLUDE__ */
