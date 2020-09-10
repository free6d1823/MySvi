#include <stdio.h>
#include <string.h>
#include <target/dsr.h>
#include <target/cmdline.h>
#include <target/console.h>
#include <target/irq.h>
#include <target/memory.h>
#include <target/timer.h>

static void mem_info(void)
{
	printf("TEXT %0.8x - %0.8x (%dKB)\n",
			TEXT_START, TEXT_END, (TEXT_END - TEXT_START) >> 10);
	printf("DATA %0.8x - %0.8x (%dKB)\n",
			DATA_START, DATA_END, (DATA_END - DATA_START) >> 10);
	printf("    bss %0.8x - %0.8x (%dKB)\n",
			__bss_start, __bss_end, (__bss_end - __bss_start) >> 10);
}


/* soc_early_init will be defined in board.c if any */
__weak int soc_early_init()
{
	return 0;
}


int main(void)
{
	soc_early_init();

	console_early_init();
	puts("\nHello SVI\n");
	mem_info();

	dsr_init();
	tick_init();
	irq_init();

	console_late_init();
	timer_init();
	cmd_init();
	dsr_loop();

	return 0;
}
