#include <target/utils.h>
#include "vc8000d.h"
#include <stdio.h>
#include <target/cmdline.h>
#include <target/memory.h>
#include <target/irq.h>
#include <target/irqc.h>

/*************************************************
** VC8000E IP specific definitions
**************************************************/
#define CORE_0_IO_ADDR		0xe7800000
#define CORE_0_IO_SIZE		(437*4)
#define CORE_L2_IO_ADDR		0xe7810000
#define VPU_DEC_INTR		408
#define VPU_DEC_L2_INTR		409

#define SAENC_AFBC_BASE 0xe7820000
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

static void decoder_isr(short unsigned int irq, void *dev_id)
{
	long i = (long)dev_id;
	uintptr_t base = core_array[i].base_addr;
	uint32_t irq_status = readl((uintptr_t)(base + HANTRODEC_IRQ_STAT_DEC*4));
	
	printf("VC8000 core %d received interrupt, ISR status: %0x0X\n", i, irq_status);
	if (irq_status & SW_DEC_IRQ) {
		irq_status = 0;
		writel(irq_status, (uintptr_t)(base + HANTRODEC_IRQ_STAT_DEC*4));
	}

	irqc_clear_irq((irq_t)core_array[i].irq );
}

int vc8000d_start(int id)
{
	uint32_t value;
	long data = (long)id;
	uintptr_t base = core_array[id].base_addr;

	printf("VC8000D core %d: init interrupt %d\n", id, core_array[id].irq);
	irqc_configure_irq(core_array[id].irq, 32, IRQ_LEVEL_TRIGGERED);
	irq_register_vector((sirq_t)core_array[id].irq, decoder_isr, (void*)data);
	
	printf("VC8000D core %d: enable interrupt %d\n", id, core_array[id].irq);
	irqc_enable_irq((irq_t) core_array[id].irq);
	/* start frame */
	value = SW_DEC_E;
	writel(value, (uintptr_t)(base + HANTRODEC_IRQ_STAT_DEC*4));
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
		reg = readl((uintptr_t)(base + HANTRODEC_ID_REGISTER*4));
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

int vc8000d_l2cache(int id)
{
	(void) id; /* current only one L2CacheShaper */
	uintptr_t base = CORE_L2_IO_ADDR;
	uint32_t hwid;
	uint32_t value;
	uint32_t type1;
	uint32_t type2;
	uint32_t type3;

	value = readl((uintptr_t)(base + L2_PRODUCT_VERSION));
	hwid  = ((value>>20) &0x00000fff);
	type1 = ((value>>16) &0x0000000f);
	type2 = ((value>>12) &0x0000000f);
	type3 = ((value>>4) &0x0000000f);
	printf("L2CacheShaper ID 0x%x, type= %d, version %d.%d\n", hwid,
			type1, type2, type3);

	printf("Write shaper configuration:\n");
	value = readl((uintptr_t)(base + L2_WRITE_CONFIGURATION));
	type1 = (value &0x0000ffff);
	printf(" - max_burst_length = %d\n", type1);
	type1 = ((value>>24) &0x000000ff);
	printf(" - bus_timeout_reg = %d\n", type1);
	value = readl((uintptr_t)(base + L2_WRITE_STATUS));
	type1 = (value &0x0000000f);
	printf(" - num_chnn = %d\n", type1);
	type1 = ((value>>4) &0x0000000f);
	printf(" - num_ids = %d\n", type1);
	type1 = ((value>>8) &0x000000ff);
	printf(" - alignment = %d\n", type1);

	printf("Read cache configuration:\n");
	value = readl((uintptr_t)(base + L2_READ_CONFIGURATION));
	printf(" - sw_cache_all_e = %d\n", (value &0x00000001));
	printf(" - sw_cache_execpt_er_e = %d\n", ((value>>1) &0x00000001));
	printf(" - sw_axi_rd_id_e = %d\n", ((value>>3) &0x00000001));
	printf(" - base_id = 0x%04x\n", ((value>>4) &0x000000ff));
	printf(" - sw_timeout_cycles = %d\n", ((value>>16) &0x0000ffff));
	value = readl((uintptr_t)(base + L2_READ_STATUS));
	printf(" - cache_chn_num = %d\n", (value &0x0000000f));
	printf(" - cache_except_list_num = 0x%04x\n", ((value>>4) &0x000003ff));
	printf(" - cache_line_size = %d\n", ((value>>10) &0x000000ff));
	printf(" - num_ids = %d\n", ((value>>18) &0x0000000f));

	printf("~ L2CacheShaper test done ~\n");
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
	} else if (argv[1][0] == 'l') {
		vc8000d_l2cache(core_id);
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
	"    l2cache - l2cacheshaper test\n"
	"    core_id - [0:1] core number. Default 0\n"
);

