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

int main(void)
{
	dsr_init();
	tick_init();
	irq_init();
	console_early_init();
	printf("\nHello M4\n");
	mem_info();
	console_late_init();
	timer_init();
	cmd_init();
	dsr_loop();

	return 0;
}