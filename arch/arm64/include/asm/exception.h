#ifndef __AARCH64_EXCEPTION_H_INCLUDE__
#define __AARCH64_EXCEPTION_H_INCLUDE__

#define FALKOR_MIDR (0x510fc000)
#define FALKOR_MIDR_HXT1 (0x680F4000)

struct pt_regs {
    unsigned long x0;
    unsigned long spsr;
    unsigned long elr;
    unsigned long regs[31];
};

void bad_mode(struct pt_regs *regs, unsigned int esr, int reason);
void std_svc_handler(struct pt_regs * regs, unsigned int esr, int reason);

#endif /* __AARCH64_EXCEPTION_H_INCLUDE__ */
