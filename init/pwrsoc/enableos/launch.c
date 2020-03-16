#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "system.h"
#include <target/cmdline.h>
#include <target/irq.h>
#include <target/smp.h>
#include <target/launch.h>
#include <target/uart.h>
#include <asm/mmu.h>
#include <asm/barrier.h>
#include <asm/psci.h>

void icache_disable(void)
{
    set_sctlr(get_sctlr() & ~CR_I);
}

void invalidate_icache_all(void)
{
    __asm_invalidate_icache_all();
}

void flush_dcache_all(void)
{
    __asm_flush_dcache_all();
}

/*
 * Performs a invalidation of the entire data cache at all levels
 */
void invalidate_dcache_all(void)
{
    __asm_invalidate_dcache_all();
}

void dcache_disable(void)
{
    unsigned int sctlr;
    sctlr = get_sctlr();

    /* if cache isn't enabled no need to disable */
    if (!(sctlr & CR_C))
        return;

    /* use assembly code to avoid touching dcache */
    disable_mmu_flush_dcache();
}

void dcache_enable(void)
{
    unsigned int sctlr;
    sctlr = get_sctlr();

    /* if cache is enabled no need to enable */
    if (sctlr & CR_C)
        return;

    invalidate_dcache_all();
    set_sctlr(sctlr | (CR_C|CR_M));
}

void disable_interrupts()
{
    irq_local_disable();
}

int cleanup_before_linux(void)
{
    /*
     * disable interrupt and turn off caches etc ...
     * configure all irq from group 0 to group1NS before jumping
     */
    uart_irq_init(false);

    disable_interrupts();

    flush_dcache_all();

    irqc_init();/*move to group1NS*/

    return 0;
}

#if 0
/* switch to EL1 */
static void switch_to_el1(void)
{
    armv8_switch_to_el1((uint64_t)dtb_entry, 0, 0, 0,
                    (uint64_t)kernel_entry, ES_TO_AARCH64);
}
#endif

int check_secondary_entry(void)
{
#ifdef CONFIG_PSCI
	if (entry_addr)
		armv8_switch_to_el2(0, 0, 0, 0,	entry_addr, ES_TO_AARCH64);
#endif
	return 0;
}

int boot_jump_linux(int argc, char *argv[])
{
    uint64_t kernel_entry;
    uint64_t dtb_entry;

    if (argc < 3)
        return -EUSAGE;

    kernel_entry = strtoull(argv[1], 0, 0);
    dtb_entry = strtoull(argv[2], 0, 0);

    cleanup_before_linux();

    armv8_switch_to_el2((uint64_t)dtb_entry, 0, 0, 0,
                            (uint64_t)kernel_entry, ES_TO_AARCH64);

    return 0;
}

MK_CMD(kernel, boot_jump_linux, "Launch kernel with the address of kernel/dtb",
    "kernel <kernel address> <dtb address>\n"
    "    - jump into linux kernel.\n"
);


static int do_cache(int argc, char *argv[])
{
    if (argc < 2)
        return -EUSAGE;

    if (strncmp(argv[1], "ii", 2) == 0) {
        invalidate_icache_all();
    } else if (strncmp(argv[1], "di", 2) == 0) {
        invalidate_dcache_all();
    } else if (strncmp(argv[1], "df", 2) == 0) {
        flush_dcache_all();
    } else if (strncmp(argv[1], "dd", 2) == 0) {
        dcache_disable();
    } else if (strncmp(argv[1], "de", 2) == 0) {
        dcache_enable();
    } else
        return -EUSAGE;

    return 0;
}

MK_CMD(cache, do_cache, "Do various cache operations",
    "cache ii/iinvalidate\n"
    "cache di/dinvalidate\n"
    "cache df/dflush\n"
    "cache dd/ddisable\n"
    "cache de/denable\n"
);
