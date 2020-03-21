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

int gdc_dump_features(int id)
{
	uint32_t reg;
	uint32_t value;
	uintptr_t base = core_array[id].base_addr;
	printf("GDC core %d supported features:\n", id);
	reg = readl((uintptr_t)(base + GDC_REG_SUPPORTS));
	if (reg & GDC_FEATURE_8BIT_DATA)
		printf(" - 8 bit data supported \n");
	if (reg & GDC_FEATURE_10BIT_DATA)
		printf(" - 10 bit data supported \n");
 	if (reg & GDC_FEATURE_GRAYSCALE)
		printf(" - Ggrayscale supported \n");
	if (reg & GDC_FEATURE_RGBA888)
		printf(" - RGBA8:8:8/YUV4:4:4 mode supported \n");
	
	if (reg & GDC_FEATURE_RGB_PLANAR)
		printf(" - RGB/YUV444 planar modes supported \n");
	if (reg & GDC_FEATURE_YUV_SEMIPLANAR)
		printf(" - YUV semiplanar modes supported \n");
	if (reg & GDC_FEATURE_YUV422_LINEAR)
		printf(" - YUV4:2:2 linear mode supported (16 bit/pixel) \n");
	if (reg & GDC_FEATURE_RGB10_10_10)
		printf(" - RGB10:10:10 mode supported\n");
	if (reg & GDC_FEATURE_BICUBIC_INTERPOLATION)
		printf(" - 4 Tap Bicubic interpolation supported\n");
	if (reg & GDC_FEATURE_BILINEAR_MODE1)
		printf(" - Bilinear interpolation mode 1 supported {for U,V components}\n");
	if (reg & GDC_FEATURE_BILINEAR_MODE2)
		printf(" - Bilinear interpolation mode 2 supported {for U,V components}\n");
	if (reg & GDC_FEATURE_OUTPUT_INTERPOLATION)
		printf(" - Output of interpolation coordinates is supported\n");
	value = ((reg & GDC_FEATURE_OUTPUT_CACHE_SIZE )>>16)
	printf(" - Size of output cache = %d lines\n", (1<< (value+5)));
	value = ((reg & GDC_FEATURE_TILE_CACHE_SIZE )>>19))
	printf(" - Size of tile cache = %d of 16x16-clusters\n", (1<< (value)));	
	value = ((reg & GDC_FEATURE_POLYPHASS_FILTER )>>24))
	printf(" - Number of polyphase filter banks = %d\n", (1<< (value)));	 
	value = ((reg & GDC_FEATURE_AXI_DATA_WIDTH )>>27))
	printf(" - AXI data width  = 0x%X\n", (1<< (value)));	  

}
int gdc_start(int id)
{

	return 0;
}
int gdc_init()
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
		gdc_dump_features(i);
	}

	return 0;
}

int gdc_dump(int id)
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
	int core = 0;
	if (argc < 1)
		return -EUSAGE;
	
	if (argc > 2)
		core = argv[2][0] - '0';
	if (argv[1][0] == 'i') {
		gdc_init();
	} else if (argv[1][0] == 'd') {
		gdc_dump(core);
	} else if (argv[1][0] == 's') {
		gdc_start(core);
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

