#include <target/utils.h>
#include "gdc.h"
#include <stdio.h>
#include <target/cmdline.h>
#include <target/memory.h>
#include <gdc/acamera_gdc_config.h>
#include <api/acamera_gdc_api.h>
#include <sys/system_log.h>
#include <sys/system_interrupts.h>
//gdc configuration sequences
#include "arm/app/gdc_config_seq_plane_y.h"
#if 0
#include "arm/app/gdc_config_seq_planar_yuv420.h"
#include "arm/app/gdc_config_seq_planar_rgb444.h"
#include "arm/app/gdc_config_seq_semiplanar_yuv420.h"
#endif

/*************************************************
** VC8000E IP specific definitions
**************************************************/
#define GDC_CORE0_REG_BASE			(0x00208000L)
#define GDC_CORE1_REG_BASE			(0x00209000L)

#define ACAMERA_GDC_SIZE (0x100)

#define GDC_CORE0_IRQ		198
#define GDC_CORE1_IRQ		198


/*************************************************
** GDC definitions
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

/*************************************************
** GDC Test Cases definitions
**************************************************/

//test cases available
enum test_cases{
	test_y_plane,
#if 0
	test_yuv420_semiplanar=0,
	test_yuv420_planar,
	test_rgb_444_planar,
	test_sequential_planes,
#endif
	max_gdc_test_cases
};

#define GDC_TEST_RUN	test_y_plane
struct _gdc_test_param{
	const unsigned char * gdc_sequence;
	uint32_t gdc_sequence_size;
	uint32_t total_planes;
	uint32_t input_addresses[ACAMERA_GDC_MAX_INPUT];
	uint8_t  sequential_mode;
	uint8_t  div_width; //use in dividing UV dimensions; actually a shift right
	uint8_t  div_height; //use in dividing UV dimensions; actually a shift right
};

//settings for each test case
struct _gdc_test_param gdc_test_param[max_gdc_test_cases]={
	{//test_y_plane
		.gdc_sequence=y_plane_1920x1080_seq, //gdc_sequence
		.gdc_sequence_size=sizeof(y_plane_1920x1080_seq),
		.total_planes=1,		//total_planes
		.input_addresses={0x1000000},//input_addresses
		.sequential_mode=0, 		//plane_sequential_processing
		.div_width=0,		//div_width
		.div_height=0		//div_height
	},
#if 0
	{//test_yuv420_semiplanar
		.gdc_sequence=semiplanar_yuv420_1920x1080_seq, //gdc_sequence
		.gdc_sequence_size=sizeof(semiplanar_yuv420_1920x1080_seq),
		.total_planes=2,		//total_planes
		.input_addresses={0x1000000, 0x2000000},//input_addresses
		.sequential_mode=0, 		//plane_sequential_processing
		.div_width=0,		//div_width
		.div_height=1		//div_height
	},
	{//test_yuv420_planar
		.gdc_sequence=planar_yuv420_1920x1080_seq, //gdc_sequence
		.gdc_sequence_size=sizeof(planar_yuv420_1920x1080_seq),
		.total_planes=3,		//total_planes
		.input_addresses={0x1000000, 0x2000000,0x3000000},//input_addresses
		.sequential_mode=0, 		//plane_sequential_processing
		.div_width=1,		//div_width
		.div_height=1		//div_height
	},
	{//test_rgb_444_planar
		.gdc_sequence=planar_rgb444_1920x1080_seq, //gdc_sequence
		.gdc_sequence_size=sizeof(planar_rgb444_1920x1080_seq),
		.total_planes=3,		//total_planes
		.input_addresses={0x1000000, 0x2000000,0x3000000},//input_addresses
		.sequential_mode=0, 		//plane_sequential_processing
		.div_width=0,		//div_width
		.div_height=0		//div_height
	},
	{//test_sequential_planes
		.gdc_sequence=y_plane_1920x1080_seq, //gdc_sequence is same as the single plane Y sequence
		.gdc_sequence_size=sizeof(y_plane_1920x1080_seq),
		.total_planes=3,		//total_planes
		.input_addresses={0x1000000, 0x2000000,0x3000000},//input_addresses
		.sequential_mode=1, 		//plane_sequential_processing
		.div_width=0,		//div_width
		.div_height=0		//div_height

	}
#endif
};

//This is a function callback provided to GDC to update frame buffer addresses and offsets
static void get_frame_buffer_callback(  uint32_t total_input, uint32_t * out_addr, uint32_t * out_lineoffset )
{
	printf("get_frame_buffer_callback: total_input=%d, out_addr=%p, out_lineoffset=%p\n", total_input, out_addr, out_lineoffset);
#if HAS_FPGA_WRAPPER
	//call frame reader to display
	acamera_fpga_update_frame_reader(total_input,out_addr,out_lineoffset);
#endif
}

//this is the main interrupt handler, for demo purposes gdc status and data are currently not passed

static void interrupt_handler( void *param, uint32_t mask )
{
	//handle the start of frame with acamera_gdc_process
	gdc_settings_t *gdc_settings = (gdc_settings_t *)param;

	//gdc block has finished processing
	if ( mask ) {
		//can filter mask
		//gdc will save the new frame reader settings
		//will update the frame reader settings via callback

		if ( acamera_gdc_get_frame( gdc_settings,gdc_test_param[GDC_TEST_RUN].total_planes ) != 0 ) {
			return;
		}

#if HAS_FPGA_WRAPPER
		//get gdc buffer input from fpga writer output
		uint32_t in_addr[gdc_test_param[GDC_TEST_RUN].total_planes];
		uint32_t in_lineoffset[gdc_test_param[GDC_TEST_RUN].total_planes];
		if(acamera_fpga_get_frame_writer( gdc_test_param[GDC_TEST_RUN].total_planes,in_addr,in_lineoffset )!=0){
			LOG( LOG_CRIT, "Cannot get frame_writer_addresses" );
		}else if( acamera_gdc_process( gdc_settings, gdc_test_param[GDC_TEST_RUN].total_planes,in_addr ) != 0 ) {
			LOG( LOG_CRIT, "GDC missed an interrupt" );
		}

#else
		if ( acamera_gdc_process( gdc_settings,gdc_test_param[GDC_TEST_RUN].total_planes, gdc_test_param[GDC_TEST_RUN].input_addresses) != 0 ) {
			LOG( LOG_CRIT, "GDC missed an interrupt" );
		}
#endif

	}
}

//we need to copy the gdc configuration sequence to the gdc config address
static uint32_t gdc_load_settings_to_memory( uint32_t * config_mem_start, uint32_t *config_settings_start, uint32_t config_size )
{
	uint32_t i = 0;
	system_memcpy( config_mem_start, config_settings_start, config_size * 4 );
	for ( i = 0; i < config_size; i++ ) {
		if ( config_mem_start[i] != config_settings_start[i] ) {
			LOG( LOG_CRIT, "GDC config mismatch index %ld, values %lX vs %lX\n", i, config_mem_start[i], config_settings_start[i] );
			return 0;
		}
	}

	return config_size * 4;
}

static int gdc_test(int id)
{
	gdc_settings_t gdc_settings = {0};
	system_interrupts_disable(id);
	//configure gdc config, buffer address and resolution
	gdc_settings.base_gdc = core_array[id].base_addr;
	gdc_settings.buffer_addr = 0x8000000;
	gdc_settings.buffer_size = 1920*1080*gdc_test_param[GDC_TEST_RUN].total_planes;
	gdc_settings.get_frame_buffer = get_frame_buffer_callback;
	gdc_settings.current_addr = gdc_settings.buffer_addr;
	gdc_settings.seq_planes_pos = 0;
	gdc_settings.ddr_mem = system_ddr_mem_init(); //opaque pointer to memory and system dependent
	acamera_gdc_stop( &gdc_settings );

	//set the gdc config
	gdc_settings.gdc_config.config_addr = 0x4000;
	gdc_settings.gdc_config.config_size = gdc_test_param[GDC_TEST_RUN].gdc_sequence_size / 4; //size of configuration in 4bytes
	gdc_settings.gdc_config.output_width = 1920;
	gdc_settings.gdc_config.output_height = 1080;
	gdc_settings.gdc_config.total_planes = gdc_test_param[GDC_TEST_RUN].total_planes;
	gdc_settings.gdc_config.sequential_mode=gdc_test_param[GDC_TEST_RUN].sequential_mode;
	gdc_settings.gdc_config.div_width = gdc_test_param[GDC_TEST_RUN].div_width;
	gdc_settings.gdc_config.div_height = gdc_test_param[GDC_TEST_RUN].div_height;

	uint32_t memory_used = gdc_load_settings_to_memory( (uint32_t *)((uintptr_t)gdc_settings.ddr_mem + gdc_settings.gdc_config.config_addr) , (uint32_t *)gdc_test_param[GDC_TEST_RUN].gdc_sequence, gdc_settings.gdc_config.config_size );
	if ( memory_used != gdc_settings.gdc_config.config_size * 4 ) {
		//memory config for gdc ifnitialization failed
		LOG( LOG_CRIT, "memory config for gdc initialization 1 failed" );
		return -1;
	}
	LOG( LOG_INFO, "Done gdc load..\n");

#if HAS_FPGA_WRAPPER
	//fpga initialization with resolution and intended buffers for dma writer output
	//YUV 420 demo
	uint32_t in_lineoffset[]={gdc_settings.gdc_config.output_width,gdc_settings.gdc_config.output_width};
	if ( acamera_fpga_init( gdc_settings.gdc_config.output_width,gdc_settings.gdc_config.output_height,gdc_settings.gdc_config.total_planes,gdc_test_param[GDC_TEST_RUN].input_addresses,in_lineoffset) != 0 ) {
		LOG( LOG_ERR, "Wrong initialisation parameters for fpga reader block" );
		return -1;
	}
#endif

	//initialise the gdc by the first configuration
	if ( acamera_gdc_init( &gdc_settings ) != 0 ) {
		LOG( LOG_ERR, "Failed to initialise GDC block" );
		return -1;
	}

	LOG( LOG_INFO, "Done gdc config..\n" );

	// set the interrupt handler. The last parameter may be used
	// to specify the context. The system must call this interrupt_handler
	// function whenever the interrupt happens.
	// This interrupt handling procedure is only advisable and is used in demo application.
	// It can be changed by a customer discretion.
	system_interrupt_set_handler(id, interrupt_handler, &gdc_settings );
	system_interrupts_init(id); //this is called before enable irq

	//enable the interrupts
	system_interrupts_enable(id);

	//start gdc process

	acamera_gdc_process( &gdc_settings,gdc_test_param[GDC_TEST_RUN].total_planes, gdc_test_param[GDC_TEST_RUN].input_addresses);

	return 0;
}

static int init_gdc_device()
{
	int i;
	for (i = 0; i< total_core_number; i++) {
		if (core_array[i].valid) {
			system_interrupts_set_irq(i, core_array[i].irq, 0x0014); /* IRQF_TRIGGER_HIGH|IRQF_TRIGGER_PROBE*/
		}
	}
	return 0;
}
static int gdc_release()
{
	int i;
	for (i = 0; i< total_core_number; i++) {
		if (core_array[i].valid){
			system_interrupts_deinit(i);
		}
		core_array[i].valid = false;
	}
	return 0;
}

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
	value = ((reg & GDC_FEATURE_OUTPUT_CACHE_SIZE )>>16);
	printf(" - Size of output cache = %d lines\n", (1<< (value+5)));
	value = ((reg & GDC_FEATURE_TILE_CACHE_SIZE )>>19);
	printf(" - Size of tile cache = %d of 16x16-clusters\n", (1<< (value)));
	value = ((reg & GDC_FEATURE_POLYPHASS_FILTER )>>24);
	printf(" - Number of polyphase filter banks = %d\n", (1<< (value))); 
	value = ((reg & GDC_FEATURE_AXI_DATA_WIDTH )>>27);
	printf(" - AXI data width  = 0x%X\n", (1<< (value)));

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

	/* gdc linux driver init the firmware in device probe stage, we manually call it here
	*/
	init_gdc_device();
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
	} else if (argv[1][0] == 't') {
		gdc_test(core);
	} else if (argv[1][0] == 'f') {
		gdc_release();
	} else {
		return -EUSAGE;
	}

	return 0;
}


MK_CMD(gdc, cmd_gdc, "Arm GDC test",
	"GDC test cases\n"
	"gdc [init|dump|test|free] core\n"
	"    init    - initilize all GDC devices\n"
	"    dump    - dump all registers\n"
	"    test    - start one GDC test case\n"
	"    free    - release all GDC device resources\n"
	"    core    - id of GDC core(0,1)\n"
);

