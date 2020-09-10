#include "afbc.h"
#include "system_isp_io.h"
#include "acamera_logger.h"
#include "system_cma.h"
uint32_t base = AFBC_BASE;
void read_afbc_product_id_and_version()
{
	uint32_t curr =	system_isp_read_32(base + BLOCK_ID);
	uint32_t product_id = (curr & 0xffff0000) >> 16;
	LOG(LOG_NOTICE, "AFBC product id = 0x%2x", product_id);
	uint32_t version_major = (curr & 0xf000) >> 12;
	uint32_t version_minor = (curr & 0xff0) >> 4;
	LOG(LOG_NOTICE, "AFBC version = R%dP%d", version_major, version_minor);
	uint32_t version_status = curr & 0xf;
	LOG(LOG_NOTICE, "AFBC version status = %d", version_status);
}

#define IMAGE_WIDTH 1280
#define IMAGE_HEIGHT 960
#define HEADER_ADDR 0x60100000
#define BODY_ADDR 	0x60120000
#define INPUT_ADDR	0xf0200000
#define INPUT_STRIDE IMAGE_WIDTH
#define CHROMA_ADDR 0xf0600000
#define CHROMA_STRIDE IMAGE_WIDTH

#define MAX_CHANNEL 1
struct encoder_params params[3];
struct encoder_surface g_encoder[3];

static void init_encoder_params()
{
	memset(&params[0], 0, sizeof(struct encoder_params));
	params[0].frame_width = IMAGE_WIDTH;
	params[0].frame_height = IMAGE_HEIGHT;
	params[0].color_format = COLOR_FORMAT_RGBA_8888;
	params[0].box_x_start = 0;
	params[0].box_x_end = IMAGE_WIDTH -1;
	params[0].box_y_start = 0;
	params[0].box_y_end = IMAGE_HEIGHT-1;
	params[0].plane_num = 1;
	params[0].plane[0].width = IMAGE_WIDTH;
	params[0].plane[0].height = IMAGE_HEIGHT;
	params[0].plane[0].data_width = 32;

	memset(&params[1], 0, sizeof(struct encoder_params));
	params[1].frame_width = 256;
	params[1].frame_height = 256;
	params[1].color_format = COLOR_FORMAT_YUV420_8;
	params[1].box_x_start = 0;
	params[1].box_x_end = 255;
	params[1].box_y_start = 0;
	params[1].box_y_end = 255;
	params[1].plane_num = 2;
	params[1].plane[0].width = 256;
	params[1].plane[0].height = 256;
	params[1].plane[0].data_width = 8;
	params[1].plane[1].width = 128;
	params[1].plane[1].height = 128;
	params[1].plane[1].data_width = 16;

	memset(&params[2], 0, sizeof(struct encoder_params));
	params[2].frame_width = 1920;
	params[2].frame_height = 1080;
	params[2].color_format = COLOR_FORMAT_RGBA_8888;
	params[2].box_x_start = 0;
	params[2].box_x_end = 1919;
	params[2].box_y_start = 0;
	params[2].box_y_end = 1079;
	params[2].plane_num = 1;
	params[2].plane[0].width = 1920;
	params[2].plane[0].height = 1080;
	params[2].plane[0].data_width = 32;
}

static int init_encoder_surface(struct encoder_params params, struct encoder_surface *encoder)
{
	if( params.color_format == COLOR_FORMAT_RGBA_8888)
		encoder->format = SPARSE_MODE_ON << 10 | YUV_TRANSFORM_ON << 8 | params.color_format << 0;
	else if (params.color_format == COLOR_FORMAT_YUV420_8)
		encoder->format = SPARSE_MODE_ON << 10 | params.color_format << 0;
	else
		return -1;
	encoder->buf_width = params.frame_width;//1280;
	encoder->buf_height = params.frame_height;//960;
	encoder->x_start = params.box_x_start;
	encoder->x_end = params.box_x_end;//1279;
	encoder->y_start = params.box_y_start;
	encoder->y_end = params.box_y_end;//959;
	encoder->write_order = 0;
	struct input_buf *inbuf;
	struct output_buf *outbuf;
	inbuf = &encoder->input;
	outbuf = &encoder->output;
	if (params.plane_num == 1)
	{
		inbuf->input_buf_addr_low = INPUT_ADDR;
		inbuf->input_buf_addr_high = 0;
		inbuf->input_stride = params.plane[0].width * params.plane[0].data_width/8;
	}
	else
	{
		inbuf->input_buf_addr_low = INPUT_ADDR;
		inbuf->input_buf_addr_high = 0;
		inbuf->input_stride = params.plane[0].width * (params.plane[0].data_width/8);
		inbuf->input_buf_chroma_addr_low = CHROMA_ADDR;
		inbuf->input_buf_chroma_addr_high = 0;
		inbuf->chroma_stride = params.plane[1].width * (params.plane[1].data_width/8);
	}
	uint32_t header_size = (params.frame_width/16 + ((params.frame_width%16 == 0) ? 0 : 1)) * (params.frame_height/16 + ((params.frame_height % 16 == 0) ? 0 :1)) * 16;
	int ret = system_cma_alloc(NULL, &outbuf->header_buf_addr_low, header_size);
	if (ret)
	{
		printf("system alloc failed, header size = 0x%2x.\n", header_size);
		return -1;
	}
	printf("header size: 0x%2x, header address: 0x%2x\n", header_size, outbuf->header_buf_addr_low);
	outbuf->header_buf_addr_high = 0;
	uint32_t body_size = 0;
	if (params.plane_num == 1)
		body_size = params.plane[0].width * params.plane[0].height * params.plane[0].data_width/8;
	else if (params.plane_num == 2)
	{
		for ( int i=0; i<params.plane_num; i++)
			body_size += params.plane[i].width * params.plane[i].height * params.plane[i].data_width/8;
	}
	ret = system_cma_alloc(NULL, &outbuf->body_buf_addr_low, body_size);//64-byte aligned
	if (ret)
	{
		printf("system alloc failed, body size = 0x%2x.\n", body_size);
		return -1;
	}
	printf("body size: 0x%2x, body address: 0x%2x\n", body_size, outbuf->body_buf_addr_low);
	outbuf->body_buf_addr_high = 0;
	return 0;
}

int afbc_encoder_init()
{
	init_encoder_params();
	//for (int i = 0; i < MAX_CHANNEL; i++)
	init_encoder_surface(params[2], &g_encoder[2]);
	return 0;
}

int afbc_encoder_config(uint8_t idx)
{
	struct encoder_surface *encoder = &g_encoder[idx];
	system_isp_write_32(base + BUFFER_WIDTH, encoder->buf_width);
	printf("buf_width=%d\n", encoder->buf_width);
	system_isp_write_32(base + BUFFER_HEIGHT, encoder->buf_height);
	printf("buf_height=%d\n", encoder->buf_height);
	system_isp_write_32(base + BOUNDING_BOX_X_START, encoder->x_start);
	printf("x_start=%d\n",encoder->x_start);
	system_isp_write_32(base + BOUNDING_BOX_X_END, encoder->x_end);
	printf("x_end=%d\n",encoder->x_end);
	system_isp_write_32(base + BOUNDING_BOX_Y_START, encoder->y_start);
	printf("y_start=%d\n",encoder->y_start);
	system_isp_write_32(base + BOUNDING_BOX_Y_END, encoder->y_end);
	printf("y_end=%d\n",encoder->y_end);
	system_isp_write_32(base + SURFACE_CFG, 0x1);	//enable surface
	//system_isp_write_32(base + IRQ_MASK, 0xf);
	system_isp_write_32(base + FORMAT_SPECIFIER, encoder->format);
	printf("format=0x%2x\n",encoder->format);
	system_isp_write_32(base + HEADER_BUF_ADDR_LOW, encoder->output.header_buf_addr_low);
	printf("header_buf_addr_low=0x%2x\n",encoder->output.header_buf_addr_low);
	system_isp_write_32(base + HEADER_BUF_ADDR_HIGH, encoder->output.header_buf_addr_high);
	printf("header_buf_addr_high=0x%2x\n", encoder->output.header_buf_addr_high);
	system_isp_write_32(base + BODY_BUF_ADDR_LOW, encoder->output.body_buf_addr_low); 
	printf("body_buf_addr_low=0x%2x\n",encoder->output.body_buf_addr_low);
	system_isp_write_32(base + BODY_BUF_ADDR_HIGH, encoder->output.body_buf_addr_high);
	printf("body_buf_addr_high=0x%2x\n",encoder->output.body_buf_addr_high);
	system_isp_write_32(base + INPUT_BUF_ADDR_LOW, encoder->input.input_buf_addr_low);
	printf("input_buf_addr_low=0x%2x\n",encoder->input.input_buf_addr_low);
	system_isp_write_32(base + INPUT_BUF_ADDR_HIGH, encoder->input.input_buf_addr_high);
	printf("input_buf_addr_high=0x%2x\n",encoder->input.input_buf_addr_high);
	system_isp_write_32(base + INPUT_BUF_STRIDE, encoder->input.input_stride);
	printf("input_stride=0x%2x\n",encoder->input.input_stride);
	system_isp_write_32(base + INPUT_BUF_CHROMA_ADDR_LOW, encoder->input.input_buf_chroma_addr_low);
	printf("input_buf_chroma_addr_low=0x%2x\n",encoder->input.input_buf_chroma_addr_low);
	system_isp_write_32(base + INPUT_BUF_CHROMA_ADDR_HIGH, encoder->input.input_buf_chroma_addr_high);
	printf("input_buf_chroma_addr_high=0x%2x\n",encoder->input.input_buf_chroma_addr_high);
	system_isp_write_32(base + INPUT_BUF_CHROMA_STRIDE, encoder->input.chroma_stride);
	printf("chroma_stride=0x%2x\n",encoder->input.chroma_stride);
	system_isp_write_32(base + COMMAND, DIRECT_SWAP);
	return 0;
}

void afbc_interrupt_init()
{
	//disable interrupt
	system_isp_write_32(base + IRQ_MASK, 0x0);
	//clear interrupt
	system_isp_write_32(base + IRQ_CLEAR, 0x1f);
}

void afbc_interrupt_enable()
{
	system_isp_write_32(base + IRQ_MASK, 0x1f);
}

void afbc_swap_mode(int swap_mode)
{
	system_isp_write_32(base + COMMAND, swap_mode);
}

int afbc_encode_period(int idx)
{
	if (idx >= MAX_CHANNEL)
	{
		LOG(LOG_LEVEL_ERROR, "AFBC index is out of range.");
		return -1;
	}
	//init_encoder_params();
	//afbc_encoder_surface_init(params[idx], &encoder[idx]);
	afbc_encoder_init();
	afbc_interrupt_init();
	afbc_interrupt_enable();
	afbc_encoder_config(idx);
	afbc_swap_mode(DIRECT_SWAP);
	return 0;
}

int afbc_init_yuv420()
{
	system_isp_write_32(base + BUFFER_WIDTH, IMAGE_WIDTH);
	system_isp_write_32(base + BUFFER_HEIGHT, IMAGE_HEIGHT);
	system_isp_write_32(base + BOUNDING_BOX_X_START, 0x0);
	system_isp_write_32(base + BOUNDING_BOX_X_END, IMAGE_WIDTH-1);
	system_isp_write_32(base + BOUNDING_BOX_Y_START, 0x0);
	system_isp_write_32(base + BOUNDING_BOX_Y_END, IMAGE_HEIGHT-1);
	system_isp_write_32(base + SURFACE_CFG, 0x1);
	system_isp_write_32(base + IRQ_MASK, 0xf);
	system_isp_write_32(base + FORMAT_SPECIFIER, 0x409);
	system_isp_write_32(base + HEADER_BUF_ADDR_LOW, HEADER_ADDR & 0xffffffff);
	system_isp_write_32(base + HEADER_BUF_ADDR_HIGH, 0x0);
	system_isp_write_32(base + BODY_BUF_ADDR_LOW, BODY_ADDR & 0xffffffff); 
	system_isp_write_32(base + BODY_BUF_ADDR_HIGH, 0x0);
	system_isp_write_32(base + INPUT_BUF_ADDR_LOW, INPUT_ADDR & 0xffffffff);
	system_isp_write_32(base + INPUT_BUF_ADDR_HIGH, 0x0);
	system_isp_write_32(base + INPUT_BUF_STRIDE, INPUT_STRIDE);
	system_isp_write_32(base + INPUT_BUF_CHROMA_ADDR_LOW, CHROMA_ADDR & 0xffffffff);
	system_isp_write_32(base + INPUT_BUF_CHROMA_ADDR_HIGH, 0x0);
	system_isp_write_32(base + INPUT_BUF_CHROMA_STRIDE, CHROMA_STRIDE);
	system_isp_write_32(base + COMMAND, 0x1);
	return 0;
}

int afbc_init_rgb32()
{
	system_isp_write_32(base + BUFFER_WIDTH, IMAGE_WIDTH);
	system_isp_write_32(base + BUFFER_HEIGHT, IMAGE_HEIGHT);
	system_isp_write_32(base + BOUNDING_BOX_X_START, 0x0);
	system_isp_write_32(base + BOUNDING_BOX_X_END, IMAGE_WIDTH-1);
	system_isp_write_32(base + BOUNDING_BOX_Y_START, 0x0);
	system_isp_write_32(base + BOUNDING_BOX_Y_END, IMAGE_HEIGHT-1);
	system_isp_write_32(base + SURFACE_CFG, 0x1);
	system_isp_write_32(base + IRQ_MASK, 0xf);
	system_isp_write_32(base + FORMAT_SPECIFIER, 0x505);
	system_isp_write_32(base + HEADER_BUF_ADDR_LOW, HEADER_ADDR & 0xffffffff);
	system_isp_write_32(base + HEADER_BUF_ADDR_HIGH, 0x0);
	system_isp_write_32(base + BODY_BUF_ADDR_LOW, BODY_ADDR & 0xffffffff);
	system_isp_write_32(base + BODY_BUF_ADDR_HIGH, 0x0);
	system_isp_write_32(base + INPUT_BUF_ADDR_LOW, INPUT_ADDR & 0xffffffff);
	system_isp_write_32(base + INPUT_BUF_ADDR_HIGH, 0x0);
	system_isp_write_32(base + INPUT_BUF_STRIDE, 1280 * 4);
	system_isp_write_32(base + COMMAND, 0x1);
	return 0;
}

