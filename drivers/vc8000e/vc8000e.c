#include <target/utils.h>
#include "vc8000e.h"
#include <stdio.h>
#include <target/cmdline.h>
#include <target/memory.h>

/*************************************************
** VC8000E IP specific definitions 
**************************************************/
#define CORE_0_IO_ADDR		VC8000E_REG_BASE
#define CORE_0_IO_SIZE		(272*4)
#define INT_PIN_CORE_0		197
#define SWREG0				0x0000
#define SWREG1				0x0004
#define SWREG4				0x0010
#define SWREG5				0x0014
#define SWREG80				0x0140
#define SWREG214			0x0358

/* SWREG0: ID Register */
#define PRODUCT_ID(id)		((id >> 16) & 0xFFFF)
#define ENC_HW_ID1			0x8000
#define ENC_HW_ID2			0x4832
#define MAJOR_NUMBER(id)	((id & 0x0000FF00) >>8)
#define MINOR_NUMBER(id)	(id & 0x000000FF)
/* SWREG1: Interrupt Register */
#define SW_ENC_TIMEOUT_INT		0x00000800	//enable timeout interrupt when 1
#define SW_ENC_IRQ_FUSE_ERROR	0x00000200	//Interrupt Interrupt status bit encoder. When this bit is high encoder has a FUSE error. SW try to setup feature but HW miss the feature set
#define SW_ENC_SLICE_RDY_STATUS	0x00000100	//Interrupt status bit encoder. When this bit is high encoder has encoded a slice.
#define SW_ENC_IRQ_LINE_BUFFER	0x00000080	//Interrupt status bit encoder linebuffer empty. When setting. Encoder has finished encoding input buffers.
#define SW_ENC_TIMEOUT 			0x00000040	//Interrupt status bit encoder timeout. When high the encoder has been idling for too long. Possible only if timeout interrupt is enabled
#define SW_ENC_BUFFER_FULL		0x00000020	//IRQ buffer full status bit. bufferFullInterrupt
#define SW_ENC_SW_RESET			0x00000010	//IRQ SW reset status bit.
#define SW_ENC_BUS_ERROR_STATUS 0x00000008	//Interrupt status bit bus. Error response from bus.
#define SW_ENC_FRAME_RDY_STATUS 0x00000004	//Interrupt status bit encoder. When this bit is high encoder has encoded a picture.
#define SW_ENC_IRQ_DIS			0x00000002	//Encoder IRQ disable. When high there are no interrupts concerning encoder from HW. Polling must be used to see the interrupt statuses.
#define SW_ENC_IRQ			0x00000001	//Encoder IRQ. When high encoder requests an interrupt. SW will reset this after interrupt is handled.
/* SWREG4: Control Register 0 */
#define SW_ENC_MODE				0xE0000000	//Encoding mode. streamType.1=hevc. 2=h264. 4=jpeg
#define SW_ENC_MIN_CB_SIZE		0x06000000	//RO min cb size:0-8x8:1-16x16:2-32x32:3-64x64:we only support 8x8
#define SW_ENC_MAX_CB_SIZE		0x01800000	//RO max cb size:0-8x8:1-16x16:2-32x32:3-64x64:we only support 64x64
#define SW_ENC_MIN_TRB_SIZE		0x00600000	//RO min tr block size:0-4x4:1-8x8:2-16x16:3-32x32:we only support 4x4
#define SW_ENC_MAX_TRB_SIZE		0x00180000	//RO max tr block size:0-4x4:1-8x8:2-16x16:3-32x32:we only support 16x16
#define SW_ENC_OUTPUT_STRIM_MODE	0x00040000 //output stream mode:0-byte stream:1-Nal stream
#define SW_ENC_CHROMA_QP_OFFSET		0x0003E000 //chroma qp offset[-12~12]
#define SW_ENC_STRONG_INTRA_SMOOTHING_ENABLED_FLAGE	0x00001000 //HEVC IntraTU32x32 strong intra smoothing filter enable flag

#define SW_ENC_SCALING_LIST_ENABLED_FLAG		0x00000100 //sw_enc_scaling_list_enabled_flag
#define SW_ENC_ACTIVE_OVERRIDE_FLAG				0x00000080	//active override flag
#define SW_ENC_SAO_ENABLE						0x00000040	//SAO enable
#define SW_ENC_MAX_TRANS_HIERARCHY_DEPTH_INTRA	0x00000038	//max transform hierarchy depth of intra
#define SW_ENC_MAX_TRANS_HIERARCHY_DEPTH_INTER	0x00000007	//max transform hierarchy depth of inter

/* SWREG5: Control Register 1 */
#define SW_ENC_JPEG_PIC_WIDTH	0xFFF00000	//Encoded jpeg width. jpgLumWidth(unit 8 pixels)
#define SW_ENC_JPEG_PIC_HEIGHT 	0x000FFF00	//Encoded jpeg height. jpgLumHeight(unit 8 pixels):Max width x height is 16384 x 16384
#define SW_ENC_PIC_WIDTH		0xFFC00000	//Encoded width. lumWidthLsb(unit 8 pixels). bit[9:0]
#define SW_ENC_PIC_HEIGHT		0x003FF800	//Encoded height. lumHeight(unit 8 pixels):Max width x height is 4096 x 4096
#define SW_ENC_PPS_DEBLOCKING_FILTER_OVERRIDE_ENABLED_FLAG	0x00000200	//deblocking filter override enable flag.0:disable 1:enable
#define SW_ENC_SLICE_DEBLOCKING_FILTER_OVERRIDE_FLAG		0x00000100	//slice deblocking filter override flag.0:no 1:yes
#define SW_ENC_OUTPUT_CU_INFO_ENABLED		0x00000040	//Enable dumping cu information to external memory.0:disable 1:enable
#define SW_ENC_BUFFER_FULL_CONTINUE			0x00000020	//Reserved for future. Not used now.
#define SW_ENC_REF_FRAMES					0x00000018	//Reserved for future. Not used now.
#define SW_ENC_FRAME_CODING_TYPE			0x00000006	//Encoded picture type. frameType.:1-I:0-P:2:B
#define SW_ENC_E				0x00000001	//encoder enable. Setting this bit high will start the encoding operation. HW will reset this when picture is processed or bus error or timeout interrupt is given.

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


int vc8000e_start(int id)
{

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
	} 	else {
		return -EUSAGE;
	}

	return 0;
}


MK_CMD(vc8e, cmd_vc8000e, "VSI VC8000E test",
	"VC8000E test cases\n"
	"vc8e [init|dump|start|stop] core_id\n"
    "    init    - show IP information\n"
	"    dump    - dump all registers\n"
	"    start   - start encode one frame\n"
	"    core_id - [0:1] core number. Default 0\n"
);

