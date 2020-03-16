#ifndef __LAUNCH_H_INCLUDE__
#define __LAUNCH_H_INCLUDE__
#include <stdint.h>

/* if modified the base address and page_size */
/* someone should also modify acpi.c in acpi project. */

#define MERGED_IMAGE_START (0x9010000ULL)
#define page_size 0x1000
#define MEMMAP_IMAGE_START MERGED_IMAGE_START
#define APIC_IMAGE_START (MEMMAP_IMAGE_START + 2 * page_size)
#define PPTT_IMAGE_START (APIC_IMAGE_START + page_size)

void memmap_generate(uint64_t ddr_real_size);
void apic_generate(uint64_t partial_good);
void pptt_generate(uint64_t cpu_partial_good, uint64_t l3_partial_good);
int boot_jump_linux(int argc, char *argv[]);
extern void spin_table();
extern void secondary_cpu_switch_to_el2(uint64_t addr, int flag);
int check_secondary_entry(void);

#endif
