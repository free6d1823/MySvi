#include <stdio.h>
#include <asm/psci.h>
#include <asm/context.h>
#include <asm/exception.h>
#include <asm/platform_arch.h>

#define SMC_UNK 0xFFFFFFFF
#define ESR_EC_SHIFT        26
#define ESR_EC_MASK         0x3f

unsigned long  psci_smc_handler(struct pt_regs *regs);

/*
* Top-level Standard Service SMC handler. This handler will in turn dispatch
* calls to PSCI SMC handler
*/
void std_svc_smc_handler(struct pt_regs *regs, unsigned int esr, int reason)
{
    uint64_t ret;
    uint64_t smc_fid = regs->regs[0];

    if (is_psci_fid(smc_fid)) {
        ret = psci_smc_handler(regs);
        regs->regs[0] = ret;
    } else {
        printf("Unknown call!\n");
        regs->regs[0] = SMC_UNK;
    }
}