/*
	ARMv8 MMU Library special for VCS
	dumped pagetable is in arch/arm64/mach-se1000/pagetable.c
	the pagetable must be defined as:
		unsigned char page_table[] __attribute__((section(".pagetable"))) = {....}
*/
#include <stdio.h>
#include <asm/reg.h>
#include <asm/sysreg.h>
#include <target/barrier.h>
#include <asm/mmu.h>

#define VALUE_TTBR0_EL3 (CONFIG_HEAP_BASE)
#define VALUE_MAIR_EL3  (0x4ff4ffbb440c0400ULL)
#define VALUE_TCR_EL3   (0x80823510ULL)

void mmu_fast_initialize()
{
    tcr_elx_t tcr = {{0}};
	tcr.el3.TBI = 0;

	__asm__ volatile
	(
		"MSR TTBR0_EL3, %[zero] \n\t"
		"MSR TCR_EL3, %[tcr] \n\t"
		:
		: [zero]"r" (0UL), [tcr]"r" (tcr.el3)
	);
}

void mmu_fast_enable()
{
	write_sysreg(read_sysreg(SCTLR_EL3) |
		 SCTLR_M | SCTLR_C | SCTLR_I, SCTLR_EL3);
    isb();
}

void mmu_fast_switch_tables()
{
    uint64_t tcr_val = VALUE_TCR_EL3;
    uint64_t ttbr_val = VALUE_TTBR0_EL3;
	uint64_t mair_val = VALUE_MAIR_EL3;

	__asm__ volatile
	(
		"MSR TTBR0_EL3, %[ttbr0] \n\t"
		"MSR MAIR_EL3, %[mair] \n\t"
		"MSR TCR_EL3, %[tcr] \n\t"
		"ISB \n\t"
		:
		: [ttbr0]"r" (ttbr_val), [mair]"r" (mair_val), [tcr]"r" (tcr_val)
	);
}

void mmu_fast_invalidate_tlb_all()
{
    exception_level_t current_el, el;

    /* Ensure updates to the page tables have made it to memory */
    __asm__ volatile("DSB NSH \n\t");

	__asm__ volatile("TLBI ALLE3 \n\t");

	__asm__ volatile
	(
		"DSB NSH \n\t"
		"ISB \n\t"
	);
}

int mmu_fast_init(void)
{
	mmu_error_t error;
	printf("MMU FAST\n");

	/* Initialize the MMU (still disabled) */
	mmu_fast_initialize();

	/* Use the page tables dumped in pagetable.c
	 * Page tables are in inner-shareable memory, inner/outer writeback
	 * memory (only coherent on the A53 that we're running on)
	 */
	mmu_fast_invalidate_tlb_all();
	mmu_fast_switch_tables();

	/* Enable the MMU and address translation */
	mmu_fast_enable();

	return 0;
}


