#include <target/utils.h>
#include "vc8000d.h"
#include <stdio.h>
#include <target/cmdline.h>
#include <target/memory.h>

/*************************************************
** VC8000E IP specific definitions
**************************************************/
#define CORE_0_IO_ADDR		VC8000D_REG_BASE
#define CORE_0_IO_SIZE		(437*4)

#define VPU_DEC_INTR		195
#define VPU_DEC_L2_INTR		196

#define SAENC_AFBC_BASE 0xbc020000
#define SAENC_AFBC_SIZE 0x204
#define AFBC_ENCODER_ID 0x0300

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
	{(uintptr_t)CORE_0_IO_ADDR, CORE_0_IO_SIZE, VPU_DEC_INTR, false},
};


int vc8000d_start(int id)
{

	return 0;
}
int vc8000d_init(int id)
{
	int i;
	total_core_number = sizeof(core_array)/sizeof(core_array[0]);
	printf("VC8000D init: %d cores\n", total_core_number);

	for (i=0; i< total_core_number; i++) {
		uintptr_t base = core_array[i].base_addr;
		uint32_t reg;
		uint32_t prod_id;

		printf("VC8000D core %d:\n", i);
		reg = readl((uintptr_t)(base + HANTRODEC_ID_REGISTER));
		prod_id = PRODUCT_ID(reg);
		if ( prod_id != DEC_HW_ID1) {
			printf("  0x%X is not a valid ID\n", reg);
			continue;
		}

		printf("Product ID =%x, Ver %d.%d\n", prod_id,
				MAJOR_NUMBER(reg), MINOR_NUMBER(reg));
		core_array[i].valid = true;

        /*check build ID */
        reg = readl((uintptr_t)(base + HANTRODEC_HW_BUILD_ID*4));
        printf("HW build ID: %08X\n", reg);
        /* check PP */
        reg = readl((uintptr_t)(base + HANTRODECPP_CFG_STAT*4));
        if(reg>> DWL_PP_E) {
            printf("PP supported: %08X\n", reg);
        }
	}

	return 0;
}

int vc8000d_dump(int id)
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

int vc8000d_features(int id)
{
    int c;
    for(c=0; c<total_core_number; c++) {
		uintptr_t base = core_array[c].base_addr;
        uint32_t cfg1, cfg2, cfg3;
        uint32_t tmp;
		printf("VC8000D core %d supported standards:\n", c); 

		cfg1 = readl((uintptr_t)(base + HANTRODEC_SYNTH_CFG * 4));
        cfg2 = readl((uintptr_t)(base + HANTRODEC_SYNTH_CFG2 * 4));
        cfg3 = readl((uintptr_t)(base + HANTRODEC_SYHTN_CFG3 * 4));

        printf("- HEVC (1:Main, 2:Main10): %d\n", ( cfg3 >> DWL_HEVC_E) & 0x3U);
        printf("- VP9 (1:Profile 0, 2:Profile1 10bits): %d\n", ( cfg3 >> DWL_VP9_E) & 0x3U);

        tmp = ( cfg1 >> DWL_H264_E) & 0x3U;
        printf("- H264 (1:baseline, 2:high-, 3:high): %d\n", tmp);
        tmp = ( cfg1 >> DWL_H264HIGH10_E) & 0x1U;
        printf("- H264 High10P: %d\n", tmp);
        tmp = ( cfg1 >> DWL_JPEG_E) & 0x1U;
        printf("- JPEG: %d\n", tmp);
        tmp = ( cfg1 >> DWL_MPEG4_E) & 0x3U;
        printf("- MPEG4 (1:simple, 2:advanced): %d\n", tmp);
        tmp = ( cfg1 >> DWL_VC1_E) & 0x3U;
        printf("- VC1 (1:simple, 2:main, 3:advanced): %d\n", tmp);
        tmp = ( cfg1 >> DWL_VP6_E) & 0x1U;
        printf("- VP6: %d\n", tmp);
        printf("- AVS2: %d\n", ( cfg1 >> DWL_AVS2_E) & 0x1U);

        printf("- DIVX: %d\n", ( cfg2 >> DWL_DIVX_E) & 0x1U);
        printf("- RV (1:support, 2:NA): %d\n", ( cfg2 >> DWL_RV_E) & 0x3U);
        printf("- VP7: %d\n", ( cfg2 >> DWL_VP7_E) & 0x1U);
        printf("- VP8: %d\n", ( cfg2 >> DWL_VP8_E) & 0x1U);
        printf("- AVS: %d\n", ( cfg2 >> DWL_AVS_E) & 0x1U);
        printf("- WEBP: %d\n", ( cfg2 >> DWL_WEBP_E) & 0x1U);
        printf("- H264 Pipeline: %d\n", ( cfg2 >> DWL_H264_PIPELINE_E) & 0x1U);
        printf("- JPEG Pipeline: %d\n", ( cfg2 >> DWL_JPEG_PIPELINE_E) & 0x1U);

        printf("Maximum supported decoder width: %d pixels\n", cfg1 &0x0000FFFF);
        printf("Maximum supported decoder height: %d pixels\n", cfg3 &0x0000FFFF);
    }
    return 0;
}
int vc8000d_afbc(int id)
{
    (void) id; /* current test one AFBC enc only */
	uintptr_t base = SAENC_AFBC_BASE;
	uint32_t hwid;
	uint32_t value;

	value = readl((uintptr_t)(base + REG_BLOCK_ID));
    hwid = ((value>>16) &0x0000ffff);
    if (AFBC_ENCODER_ID != hwid) {
        printf("0x%x is not a valid AFBC encoder ID\n", value);
        return -1;
    }
    printf("AFBC encoder ID 0x%x, version %d.%d r%d\n", hwid, 
            (value & 0x0000f000) >>12,
            (value & 0x00000ff0) >>4,
            value&0x0000000f);
 	value = readl((uintptr_t)(base + REG_IRQ_RAW_STATUS));
    printf(" - REG_IRQ_RAW_STATUS = 0x%X\n", value);
 	value = readl((uintptr_t)(base + REG_IRQ_CLEAR));
    printf(" - REG_IRQ_CLEAR = 0x%X\n", value);
 	value = readl((uintptr_t)(base + REG_IRQ_MASK));
    printf(" - REG_IRQ_MASK = 0x%X\n", value);
 	value = readl((uintptr_t)(base + REG_IRQ_STATUS));
    printf(" - REG_IRQ_STATUS = 0x%X\n", value);
 	value = readl((uintptr_t)(base + REG_COMMAND));
    printf(" - REG_COMMAND = 0x%X\n", value);   
 	value = readl((uintptr_t)(base + REG_STATUS));
    printf(" - REG_STATUS = 0x%X\n", value);   
    printf("~ AFBC encoder test done ~\n");
    return 0;
}

static int cmd_vc8000d(int argc, char **argv)
{
	int core_id = 0;
	if (argc < 2)
		return -EUSAGE;
	if (argc >= 3)
		core_id = argv[2][0] - '0';

	if (argv[1][0] == 'i') {
		vc8000d_init(core_id);
	} else if (argv[1][0] == 'd') {
		vc8000d_dump(core_id);
	} else if (argv[1][0] == 's') {
		vc8000d_start(core_id);
	} else if (argv[1][0] == 'f') {
		vc8000d_features(core_id);
	} else if (argv[1][0] == 'a') {
		vc8000d_afbc(core_id);
	} else {
		return -EUSAGE;
	}

	return 0;
}


MK_CMD(vc8d, cmd_vc8000d, "VSI VC8000D test",
	"VC8000D test cases\n"
	"vc8d [init|dump|feat|start|afbc] core_id\n"
    "    init    - show IP information\n"
	"    dump    - dump all registers\n"
	"    start   - start encode one frame\n"
	"    feat    - show IP features\n"
	"    afbc    - afbc encoder test\n"
	"    core_id - [0:1] core number. Default 0\n"
);

