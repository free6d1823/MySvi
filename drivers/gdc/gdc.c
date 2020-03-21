#include <target/utils.h>
#include "gdc.h"
#include <stdio.h>
#include <target/cmdline.h>
#include <target/memory.h>

/*************************************************
** VC8000E IP specific definitions
**************************************************/
#define GDC_CORE0_REG_BASE			(0x00208000L)
#define GDC_CORE1_REG_BASE			(0x00209000L)

#define ACAMERA_GDC_SIZE (0x100)

#define GDC_CORE0_IRQ		198
#define GDC_CORE1_IRQ		198


/*************************************************
** VC8000D definitions
**************************************************/
typedef struct
{
	uintptr_t base_addr;
	unsigned int iosize;
	int irq;
	bool valid;
} CORE_CONFIG;

static int total_core_number = 0;
static CORE_CONFIG core_array[] = {
	{(uintptr_t)GDC_CORE0_REG_BASE, ACAMERA_GDC_SIZE, GDC_CORE0_IRQ, false},
	{(uintptr_t)GDC_CORE1_REG_BASE, ACAMERA_GDC_SIZE, GDC_CORE1_IRQ, false},
};


int gdc_start(int id)
{

	return 0;
}
int gdc_init(int id)
{
	int i;
	total_core_number = sizeof(core_array)/sizeof(core_array[0]);
	printf("GDC init: Support %d cores\n", total_core_number);

	for (i=0; i< total_core_number; i++) {
		uintptr_t base = core_array[i].base_addr;
		uint32_t reg;

		printf("GDC core %d:\n", i);
		reg = readl((uintptr_t)(base + GDC_REG_ID));
		if ( reg == 0 ) {
			printf("  Core %d is not available!\n", reg);
			continue;
		}

		printf("GDC ID =%x\n", reg);
		core_array[i].valid = true;

	}

	return 0;
}

int gdc_dump()
{
	int i;

	printf("Reg dump start\n");
	for (i=0; i< core_array[id].iosize; i+= 4) {
		uintptr_t base = core_array[id].base_addr;
		printf("\tOffset %02X = %08X\n", readl((uintptr_t)(base + i)));
	}
	printf("Reg dump end\n");
	return 0;
}

static int cmd_gdc(int argc, char **argv)
{
	if (argc < 1)
		return -EUSAGE;

	if (argv[1][0] == 'i') {
		gdc_init();
	} else if (argv[1][0] == 'd') {
		gdc_dump();
	} else if (argv[1][0] == 's') {
		gdc_start();
    } 	else {
		return -EUSAGE;
	}

	return 0;
}


MK_CMD(gdc, cmd_gdc, "Arm GDC test",
	"GDC test cases\n"
	"gdc [init|dump|start] core\n"
    "    init    - initilize IP information\n"
	"    dump    - dump all registers\n"
	"    start   - start GDC one frame\n"
	"    core    - id of GDC core(0,1)\n"
);

