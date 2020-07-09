#include <target/utils.h>
#include "vc8000e.h"
#include <stdio.h>
#include <target/cmdline.h>
#include <target/memory.h>
#include <target/irq.h>
#include <target/irqc.h>

/*************************************************
** VC8000E IP specific definitions
**************************************************/
#define CORE_0_IO_ADDR		0xe7830000
#define CORE_0_IO_SIZE		(272*4)
#define INT_PIN_CORE_0		410

#define SADEC_AFBC_BASE 0xe7840000
#define SADEC_AFBC_SIZE 0x204
#define AFBC_DECODER_ID 0x0301

/*************************************************
** VC8000E definitions
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
	{(uintptr_t)CORE_0_IO_ADDR, CORE_0_IO_SIZE, INT_PIN_CORE_0, false},
};

static void encoder_isr(short unsigned int irq, void *dev_id)
{
	long i = (long)dev_id;
	uintptr_t base = core_array[i].base_addr;
	uint32_t irq_status = readl((uintptr_t)(base + SWREG1));
	uint32_t wClr;
	printf("VC8000 core %d received interrupt, ISR status: %0x0X\n", i, irq_status);
	if (irq_status & SW_ENC_IRQ) {
		/*	Disable HW when buffer over-flow happen
		*  HW behavior changed in over-flow
		*    in-pass, HW cleanup HWIF_ENC_E auto
		*    new version:  ask SW cleanup HWIF_ENC_E when buffer over-flow
		*/
		if(irq_status & SW_ENC_BUFFER_FULL)
			writel(0, (uintptr_t)(base + SWREG5));
	}
	/* clear int */
	/* SW_ENC_SLICE_RDY_STATUS|
	   SW_ENC_IRQ_LINE_BUFFER| SW_ENC_TIMEOUT|SW_ENC_BUFFER_FULL|SW_ENC_SW_RESET
	   SW_ENC_BUS_ERROR_STATUS|SW_ENC_BUS_ERROR_FRAME_RDY_STATUS| SW_ENC_IRQ */
	wClr = irq_status & (~0x1FD);
	writel(wClr, (uintptr_t)(base + SWREG1));

	irqc_clear_irq((irq_t)core_array[i].irq );
}

int vc8000e_start(int id)
{
	uint32_t value;
	uintptr_t base = core_array[id].base_addr;
	long data = (long)id;

	printf("VC8000E core %d: init interrupt %d\n", id, core_array[id].irq);
	irqc_configure_irq(core_array[id].irq, 32, IRQ_LEVEL_TRIGGERED);
	irq_register_vector((sirq_t)core_array[id].irq, encoder_isr, (void*) data);

	printf("VC8000E core %d: enable interrupt %d\n", id, core_array[id].irq);
	irqc_enable_irq((irq_t) core_array[id].irq);
	/* start frame */
	value = SW_ENC_TIMEOUT_INT|SW_ENC_IRQ;
	writel(value, (uintptr_t)(base + SWREG1));
	return 0;
}
int vc8000e_init(int id)
{
	int i;
	total_core_number = sizeof(core_array)/sizeof(core_array[0]);
	printf("VC8000E init: %d cores\n", total_core_number);

	for (i=0; i< total_core_number; i++) {
		uintptr_t base = core_array[i].base_addr;
		uint32_t hwid;
		uint32_t prod_id;

		printf("VC8000E core %d:\n", i);
		hwid = readl((uintptr_t)(base + SWREG0));
		prod_id = PRODUCT_ID(hwid);
		if ( prod_id != ENC_HW_ID1 || prod_id != ENC_HW_ID2) {
			printf("  0x%X is not a valid ID\n", hwid);
			continue;
		}

		printf("Product ID =%x, Ver %d.%d\n", prod_id,
				MAJOR_NUMBER(hwid), MINOR_NUMBER(hwid));
		core_array[i].valid = true;
	}

	return 0;
}

int vc8000e_dump(int id)
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

int vc8000e_afbc(int id)
{
	(void) id; /* current test one AFBC enc only */
	uintptr_t base = SADEC_AFBC_BASE;
	uint32_t hwid;
	uint32_t value;

	value = readl((uintptr_t)(base + REG_BLOCK_ID));
	hwid = ((value>>16) &0x0000ffff);
	if (AFBC_DECODER_ID != hwid) {
		printf("0x%x is not a valid AFBC decoder ID\n", value);
		return -1;
	}
	printf("AFBC decoder ID 0x%x, version %d.%d r%d\n", hwid,
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
	printf("~ AFBC decoder test done ~\n");
	return 0;
}

static int cmd_vc8000e(int argc, char **argv)
{
	int core_id = 0;
	if (argc < 2)
		return -EUSAGE;
	if (argc >= 3)
		core_id = argv[2][0] - '0';

	if (argv[1][0] == 'i') {
		vc8000e_init(core_id);
	} else if (argv[1][0] == 'd') {
		vc8000e_dump(core_id);
	} else if (argv[1][0] == 's') {
		vc8000e_start(core_id);
	} else if (argv[1][0] == 'a') {
		vc8000e_afbc(core_id);
	} else {
		return -EUSAGE;
	}

	return 0;
}

MK_CMD(vc8e, cmd_vc8000e, "VSI VC8000E test",
	"VC8000E test cases\n"
	"vc8e [init|dump|start|afbc] core_id\n"
	"    init    - show IP information\n"
	"    dump    - dump all registers\n"
	"    afbc    - afbc decoder test\n"
	"    start   - start encode one frame, check interrupt\n"
	"    core_id - [0:1] core number. Default 0\n"
);

