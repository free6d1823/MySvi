#ifndef __AFBC_REG_H__
#define __AFBC_REG_H__

#include <asm/memory.h>
#include <target/regdef.h>
#include <target/utils.h>

#define BLOCK_ID 					0x000
#define IRQ_RAW_STATUS 				0x004
#define IRQ_CLEAR 					0x008
#define IRQ_MASK 					0x00c
#define IRQ_STATUS					0x010
#define COMMAND						0x014
#define STATUS						0x018
#define SURFACE_CFG					0x01c
#define AXI_CFG						0x020
#define HEADER_BUF_ADDR_LOW			0x040
#define HEADER_BUF_ADDR_HIGH		0x044
#define BODY_BUF_ADDR_LOW			0x048
#define BODY_BUF_ADDR_HIGH			0x04c
#define FORMAT_SPECIFIER			0x050
#define BUFFER_WIDTH				0x054
#define BUFFER_HEIGHT				0x058
#define BOUNDING_BOX_X_START		0x05c
#define BOUNDING_BOX_X_END			0x060
#define BOUNDING_BOX_Y_START		0x064
#define BOUNDING_BOX_Y_END			0x068
#define INPUT_BUF_ADDR_LOW			0x06c
#define INPUT_BUF_ADDR_HIGH			0x070
#define INPUT_BUF_STRIDE			0x074
#define INPUT_BUFFER_WRITE_ORDER	0x078
#define INPUT_BUF_CHROMA_ADDR_LOW	0x0ec
#define INPUT_BUF_CHROMA_ADDR_HIGH	0x0f0
#define INPUT_BUF_CHROMA_STRIDE		0x0f4

#define AFBC_BASE 0xE80E0000

#define COLOR_FORMAT_RGBA_8888 0x5
#define COLOR_FORMAT_YUV420_8  0x9

#define SPARSE_MODE_ON 0x1
#define SPARSE_MODE_OFF 0x0

#define YUV_TRANSFORM_ON 0x1
#define YUV_TRANSFORM_OFF 0x0

#define DIRECT_SWAP 0x1

struct output_buf {
	uint32_t	header_buf_addr_low;
	uint32_t	header_buf_addr_high;
	uint32_t 	body_buf_addr_low;
	uint32_t 	body_buf_addr_high;
	void* 		virt_header_addr;
	void*		virt_body_addr;
};

struct input_buf {
	uint32_t	input_buf_addr_low;
	uint32_t	input_buf_addr_high;
	uint32_t	input_stride;
	uint32_t	input_buf_chroma_addr_low;
	uint32_t	input_buf_chroma_addr_high;
	uint32_t 	chroma_stride;
};

struct plane_cfg {
	uint32_t width;
	uint32_t height;
	uint32_t data_width;//plane data width
};
struct encoder_params {
	uint32_t frame_width;
	uint32_t frame_height;
	uint32_t color_format;
	uint32_t box_x_start;
	uint32_t box_x_end;
	uint32_t box_y_start;
	uint32_t box_y_end;
	uint32_t plane_num;	//plane num
	struct plane_cfg plane[2];
};


struct encoder_surface {
	uint32_t	format;
	uint32_t	buf_width;
	uint32_t	buf_height;
	uint32_t	x_start;
	uint32_t	x_end;
	uint32_t	y_start;
	uint32_t	y_end;
	uint32_t	write_order;
	struct input_buf  input;
	struct output_buf output;
};

//struct encoder_struct {
//	struct encoder_surface_struct surface[1];
//};

static void init_encoder_params();
static int init_encoder_surface(struct encoder_params params, struct encoder_surface *encoder);
void read_afbc_product_id_and_version();
int afbc_encoder_init();
int afbc_encoder_config(uint8_t idx);
void afbc_interrupt_init();
void afbc_interrupt_enable();
void afbc_swap_mode(int swap_mode);
int afbc_encode_period();
int afbc_init_yuv420();
int afbc_init_rgb32();
#endif
