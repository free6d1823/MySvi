#include <target/utils.h>
#include "d71.h"
#include <stdio.h>
#include <target/cmdline.h>
#include <target/memory.h>
#include <std/string.h>
#include <stdlib.h>

#define DEFAULT_PREPRETCH_LINE 5
static uintptr_t d71_addr = D71_REG_BASE;
static uintptr_t lpu0_layer1_addr = 0x60000000;
static uintptr_t lpu0_layer0_addr = 0x602c0000;
static uintptr_t update_addr = 0x60160000;
static uintptr_t lpu1_layer0_addr = 0x60400000;
static uintptr_t lpu_layer_wb = 0x60800000;

struct dpu_pipe d71_pipe;
#define writel_mask(v,m,a) __raw_writel_mask(v,m,a)

static int bs_init(void __iomem *base)
{
	/*
	  VPW: Vsync Pulse Width
	  VBP: Vsync Back Porch
	  VFP: Vsync Front Porch
	  HPW: Hsync Pulse Width
	  HBP: Hsync Back Porch
	  HFP: Hsync Front Porch
	*/
	writel(HV_SIZE(640, 480), base + BS_ACTIVESIZE);
	writel(HINTERVALS(0x010, 0x030), base + BS_HINTERVALS);
	writel(VINTERVALS(0x000A, 0x21), base + BS_VINTERVALS);
	writel(HV_SYNCWIDTH(0x060, 0x02), base + BS_SYNC);

	writel(DEFAULT_PREPRETCH_LINE - 1, base + BS_PROG_LINE);
	writel(DEFAULT_PREPRETCH_LINE, base + BS_PREFETCH_LINE);

	/* Test mode (color bars) enable
	__raw_setl(BS_CONTROL_TM, base + BS_CONTROL);
	*/

	/* Bacground color: white color
	writel(0x3fffffff, base + BS_BG_COLOR);
	*/

	/* Display backend timing enable */
	__raw_setl(BS_CONTROL_VM | BS_CONTROL_EN, base + BS_CONTROL);

	return 0;
}

static int dou_pipe_update(void __iomem *base, int index, struct dpu_pipe * pipe)
{
	u32 hactive, hfront_porch, hback_porch, hsync_len;
	u32 vactive, vfront_porch, vback_porch, vsync_len;
	u32 value;
	void __iomem *bs_base = base + DOU_BS_START;
	//void __iomem *bs_ips  = base + DOU_IPS_START;

	/* update BS */
	hactive = pipe->dou_blocks[index].active_size.hsize;
	hfront_porch = pipe->dou_blocks[index].hstart - hactive;
	hsync_len = pipe->dou_blocks[index].hend - pipe->dou_blocks[index].hstart;
	hback_porch = pipe->dou_blocks[index].htotal - pipe->dou_blocks[index].hend;

	vactive = pipe->dou_blocks[index].active_size.vsize;
	vfront_porch = pipe->dou_blocks[index].vstart - vactive;
	vsync_len = pipe->dou_blocks[index].vend - pipe->dou_blocks[index].vstart;
	vback_porch = pipe->dou_blocks[index].vtotal - pipe->dou_blocks[index].vend;

	writel(HV_SIZE(hactive, vactive), bs_base + BS_ACTIVESIZE);
	writel(HINTERVALS(hfront_porch,hback_porch), bs_base + BS_HINTERVALS);
	writel(VINTERVALS(vfront_porch,vback_porch), bs_base + BS_VINTERVALS);

	value = BS_SYNC_VSW(vsync_len) | BS_SYNC_HSW(hsync_len);
	value |= pipe->dou_blocks[index].vsync_polar ? BS_SYNC_VSP : 0;
	value |= pipe->dou_blocks[index].hsync_polar ? BS_SYNC_HSP : 0;
	writel(value, bs_base + BS_SYNC);

	writel(D71_DEFAULT_PREPRETCH_LINE - 1, bs_base + BS_PROG_LINE);
	writel(D71_DEFAULT_PREPRETCH_LINE,     bs_base + BS_PREFETCH_LINE);

	/* configure bs control register */
	value = BS_CONTROL_EN;
	if(pipe->dou_blocks[index].video_mode)
	     value |= BS_CONTROL_VM;
	if (pipe->dou_blocks[index].dual_link) {
		writel(hfront_porch + 16, bs_base + BS_DRIFT_TO);
		value |= BS_CONTROL_DL;
	}

	writel(value, bs_base + BS_CONTROL);

	/* Update IPS */
	/* TODO: if post-processing of the composed image is needed */
	return 0;
}

static int gcu_init(void __iomem *base)
{
	u32 core_id;

	core_id = readl(base + GLB_CORE_ID);
	printf("D71 PRODUCT_ID 0x%x\n", GLB_CORE_ID_PRODUCT_ID(core_id));

	/* Software reset request */
	__raw_setl(GCU_CONTROL_SRST, base + BLK_CONTROL);
	while (readl(base + BLK_CONTROL) & GCU_CONTROL_SRST);

	/* Operation mode request */
	writel(MODE_DO01_ACTIVE, base + BLK_CONTROL);

	return 0;
}

static int gcu_dump(void __iomem *base)
{
	printf("GLB_IRQ_STATUS = 0x%x\n", readl(base + GLB_IRQ_STATUS));
	printf("GCU_IRQ_RAW_STATUS = 0x%x\n", readl(base + GCU_IRQ_RAW_STATUS));
	printf("GCU_STATUS = 0x%x\n", readl(base + BLK_STATUS));
	printf("GCU_CONTROL = 0x%x\n", readl(base + BLK_CONTROL));
	return 0;
}

static int gcu_flush(void __iomem *base, int pipe)
{
	/* Configuration valid flag for display output */
	if (pipe == 0)
		writel(GCU_CVAL, base + GCU_CONFIG_VALID0);
	else
		writel(GCU_CVAL, base + GCU_CONFIG_VALID1);

	return 0;
}

static int cu_init(void __iomem *base)
{
	/* Composition size */
	writel(HV_SIZE(640, 480), base + CU_SIZE);

	/* Bacground color: green color */
	writel(0x00ff0000, base + CU_BG_COLOR);

	return 0;
}

static int cu_input(void __iomem *base, int input)
{
	base += input * PER_CU_INPUT;
	writel(HV_SIZE(640, 480), base + CU_INPUT_SIZE);
	writel(HV_OFFSET(0, 0), base + CU_INPUT_OFFSET);
	__raw_setl(CU_INPUT_CONTROL_EN , base + CU_INPUT_CONTROL);

	return 0;
}

static int cu_pipe_update(void __iomem *base, int index, struct dpu_pipe *pipe)
{
	int i;
	struct lpu_layers * l_layers = &(pipe->layer_group[index]);
	struct layer_layout_param * l_param;
	int ctrl;

	if(pipe->cu_index[index]) {
		for(i = 0; i < 4; i++) {
			if(l_layers->lpu_layer_index[i] == index) {
				l_param = &l_layers->layer_param[i];
				ctrl = (l_param->alpha_type | (l_param->alpha_value << 8) | CU_INPUT_CONTROL_EN);
				writel(l_layers->lpu_layer_id[i], base + CU_INPUT_ID0 + i*4);
				writel(HV_SIZE(l_param->width, l_param->height), base + CU_INPUT_SIZE + i* 0x10);
				writel(HV_OFFSET(l_param->h_offset, l_param->v_offset), base + CU_INPUT_OFFSET + i*0x10);
				writel(ctrl, base + CU_INPUT_CONTROL + i*0x10);
			}
		}
		writel(HV_SIZE(pipe->cu_blocks[index].size.hsize, pipe->cu_blocks[index].size.vsize), base + CU_SIZE);
	}

	return 0;
}


static int cu_dump(void __iomem *base)
{
	printf("CU_IRQ_RAW_STATUS = 0x%x\n", readl(base + CU_IRQ_RAW_STATUS));
	printf("CU_STATUS = 0x%x\n", readl(base + CU_STATUS));

	printf("INPUT_ID = 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\n", readl(base + INPUT_ID),
			readl(base + INPUT_ID + 4), readl(base + INPUT_ID + 8),
			readl(base + INPUT_ID + 12), readl(base + INPUT_ID + 16));

	return 0;
}

static void cu_disable(void __iomem *base, int index)
{
	void __iomem *cu_base = base + (index * 0x2000);
	int i;
	writel(0, cu_base+BLK_CONTROL);
	for(i=0; i<4; i++) {
		writel(0, cu_base+CU_INPUT_ID0+(i<<2));
		writel(CU_INPUT_CTRL_ALPHA(0xFF),cu_base+CU_INPUT_CONTROL+(i<<4));
	}
}

static int d71_bind(void __iomem *out, int oidx, void __iomem *in, int iidx)
{
	u16 id;

	id = readl(out + OUTPUT_ID + 4 * oidx);
	writel(id, in + INPUT_ID + 4 * iidx);

	return 0;
}

static int lpu_layer_init(void __iomem *base, uintptr_t fb)
{
	writel((u32)fb, base + L_P0_PTR_LOW);
	writel((fb >> 16) >> 16, base + L_P0_PTR_HIGH);

	writel(640 * 4, base + L_P0_STRIDE);

	/* __raw_setl(L_AD_CONTROL_AEN, base + L_AD_CONTROL); */

	writel(HV_SIZE(640, 480), base + L_IN_SIZE);
	writel(FORMAT_ARGB_8888, base + L_FORMAT);
	writel(L_CONTROL_EN, base + BLK_CONTROL);

	return 0;
}

static int d71_wb_layer_init(void __iomem *base, uintptr_t fb, int lpu_i)
{
	void __iomem *layer_wb_addr = base + LPU0_LAYER_WR + lpu_i * 0x2000;
	void __iomem *cu = base + CU0 + lpu_i * 0x2000;

	writel((u32)fb, layer_wb_addr + L_P0_PTR_LOW);
	writel((fb >> 16) >> 16, layer_wb_addr + L_P0_PTR_HIGH);

	writel(640 * 4, layer_wb_addr + L_P0_STRIDE);

	/* __raw_setl(L_AD_CONTROL_AEN, base + L_AD_CONTROL); */

	writel(HV_SIZE(640, 480), layer_wb_addr + L_IN_SIZE);
	writel(FORMAT_ARGB_8888, layer_wb_addr + L_FORMAT);

	__raw_setl(L_CONTROL_EN , layer_wb_addr + BLK_CONTROL);

	d71_bind(cu, 0, layer_wb_addr, 0);

	return 0;
}


static int lpu_layer_pipe_update(void __iomem *base, int lpu_i, struct dpu_pipe * pipe)
{
	struct lpu_layers * l_layers = &pipe->layer_group[lpu_i];
	int i;
	for (i=0; i<4; i++) {
		if(l_layers->lpu_layer_index[i] != -1 ) {
			struct layer_layout_param * l_param = &l_layers->layer_param[i];
			writel((u32)l_param->fb, base + L_P0_PTR_LOW + i * 0x200);
	        writel((l_param->fb >> 16) >> 16, base + L_P0_PTR_HIGH + i * 0x200);

	        l_layers->lpu_layer_id[i] = readl(base + i * 0x200) & 0xFFF0;

	        writel((l_param->stride * 4), base + L_P0_STRIDE + i * 0x200);

	        writel(HV_SIZE(l_param->width, l_param->height), base + L_IN_SIZE + i* 0x200);
	        writel(l_param->format, base + L_FORMAT + i * 0x200);
	        writel(L_CONTROL_EN | L_HFLIP | L_VFLIP, base + BLK_CONTROL + i * 0x200);
		}
	}

	return 0;
}

static int lpu_layers_fb_update(void __iomem *base, int lpu_i, struct layer_layout_param *l_param, struct dpu_pipe * pipe)
{
	int i;
	for(i=0; i<4; i++) {
		if(l_param[i].fb != pipe->layer_group[lpu_i].layer_param[i].fb) {
			pipe->layer_group[lpu_i].layer_param[i].fb = l_param[i].fb;
			writel((u32)l_param->fb, base + L_P0_PTR_LOW + i * 0x200);
			writel((l_param->fb >> 16) >> 16, base + L_P0_PTR_HIGH + i * 0x200);
		}
	}
	return 0;
}

static void lpu_layer_disable(void __iomem *base)
{
	writel_mask(0, L_CONTROL_EN, base);
}

static void lpu_layers_disable(void __iomem *base)
{
	int i;
	for(i=0; i<4; i++) {
		lpu_layer_disable(base + i*0x200);
	}
}

static int lpu_dump(void __iomem *base)
{
	printf("LPU_IRQ_RAW_STATUS = 0x%x\n", readl(base + LPU_IRQ_RAW_STATUS));
	printf("LPU_STATUS = 0x%x\n", readl(base + LPU_STATUS));
	printf("LPU_TBU_STATUS = 0x%x\n", readl(base + LPU_TBU_STATUS));
	return 0;
}

static int dou_dump(void __iomem *base)
{
	printf("DOU_IRQ_RAW_STATUS = 0x%x\n", readl(base + DOU_IRQ_RAW_STATUS));
	printf("DOU_STATUS = 0x%x\n", readl(base + DOU_STATUS));

	return 0;
}

static void dou_disable(void __iomem *base, int index)
{
	int i;
	void __iomem * dou_base=base+DOU_BS_START+index*0x2000;
	writel_mask(0, BS_CONTROL_EN, dou_base + DOU0_BS + BS_CONTROL);	//disable bs timing

	dou_base = base + DOU_IPS_START + (index * 0x2000);
	writel(0, dou_base+BLK_CONTROL);                                    //disable ips
	for(i=0; i<2; i++) {
		writel(0, dou_base+CU_INPUT_ID0+(i<<2));
	}
}

static int ips_init(void __iomem *base)
{
	/* writel(IPS_CONTROL_RGB, base + IPS_CONTROL); */
	writel(HV_SIZE(640, 480), base + IPS_SIZE);
	writel(0x8, base + IPS_DEPTH);

	return 0;
}


int d71_lpu0_layer1_init(void __iomem *base, uintptr_t fb)
{
	bs_init(base + DOU0_BS);

	lpu_layer_init(base + LPU0_LAYER1, fb);

	cu_init(base + CU0);
	cu_input(base + CU0, 0);

	ips_init(base + DOU0_IPS);

	d71_bind(base + LPU0_LAYER1, 0, base + CU0, 0);
	d71_bind(base + CU0, 0, base + DOU0_IPS, 0);

	gcu_flush(base + GCU, 0);

	return 0;
}

int d71_dump(void __iomem *base)
{
	dou_dump(base + DOU0);
	cu_dump(base + CU0);
	lpu_dump(base + LPU0);
	gcu_dump(base + GCU);

	return 0;
}

static int d71_update_pipe(void __iomem *base, struct dpu_pipe * pipe)
{
	int ret = 0;
	printf("d71_update_pipe\n");
	ret = lpu_layer_pipe_update(base + LPU0_LAYER0, 0, pipe);
	ret += cu_pipe_update(base + CU0, 0, pipe);
	ret += dou_pipe_update(base + DOU0, 0, pipe);
	ret += gcu_flush(base + GCU, 0);                     //Configuration of DO0 is validated
	return ret;
}

static int d71_update_1st_layer(void __iomem *base, uintptr_t new_fb)
{
	struct layer_layout_param ls_param[4];
	int ret;
	memcpy(&ls_param[0], &d71_pipe.layer_group[0].layer_param[0],sizeof(struct layer_layout_param));
	memcpy(&ls_param[1], &d71_pipe.layer_group[0].layer_param[1],sizeof(struct layer_layout_param));
	memcpy(&ls_param[2], &d71_pipe.layer_group[0].layer_param[2],sizeof(struct layer_layout_param));
	memcpy(&ls_param[3], &d71_pipe.layer_group[0].layer_param[3],sizeof(struct layer_layout_param));

	ls_param[0].fb = new_fb;  //switch lpu0 layer 0 fb

	ret = lpu_layers_fb_update(base + LPU0_LAYER0, 0, &ls_param[0], &d71_pipe);
	ret += gcu_flush(base + GCU, 0);
	return ret;
}

static void d71_pipe_case_0_init(uintptr_t lpu0_layer0_fb, uintptr_t lpu0_layer1_fb)
{
	memset(&d71_pipe, 0, sizeof(struct dpu_pipe));
	d71_pipe.lpu_index[0]=1;
	d71_pipe.layer_group[0].lpu_layer_index[0]=0; //lpu 0 layer 0 output to cu 0
	d71_pipe.layer_group[0].lpu_layer_index[1]=0; //lpu 0 layer 1 output to cu 0
	d71_pipe.layer_group[0].lpu_layer_index[2]=-1; //lpu 0 layer 2 not in use
	d71_pipe.layer_group[0].lpu_layer_index[3]=-1; //lpu 0 layer 3 not in use
	d71_pipe.layer_group[1].lpu_layer_index[0]=-1; //lpu 1 layer 0 not in use
	d71_pipe.layer_group[1].lpu_layer_index[1]=-1; //lpu 1 layer 1 not in use
	d71_pipe.layer_group[1].lpu_layer_index[2]=-1; //lpu 1 layer 2 not in use
	d71_pipe.layer_group[1].lpu_layer_index[3]=-1; //lpu 1 layer 3 not in use
	d71_pipe.layer_group[0].layer_param[0].alpha_type = 0;
	d71_pipe.layer_group[0].layer_param[0].alpha_value = 0x80;
	d71_pipe.layer_group[0].layer_param[0].fb = lpu0_layer0_fb;
	d71_pipe.layer_group[0].layer_param[0].format = FORMAT_ARGB_8888;
	d71_pipe.layer_group[0].layer_param[0].height = 480;
	d71_pipe.layer_group[0].layer_param[0].width = 640;
	d71_pipe.layer_group[0].layer_param[0].stride = 640;
	d71_pipe.layer_group[0].layer_param[0].h_offset = 0;
	d71_pipe.layer_group[0].layer_param[0].v_offset = 0;
	d71_pipe.layer_group[0].layer_param[1].alpha_type = 0;
	d71_pipe.layer_group[0].layer_param[1].alpha_value = 0xFF;
	d71_pipe.layer_group[0].layer_param[1].fb = lpu0_layer1_fb;
	d71_pipe.layer_group[0].layer_param[1].format = FORMAT_ARGB_8888;
	d71_pipe.layer_group[0].layer_param[1].height = 480;
	d71_pipe.layer_group[0].layer_param[1].width = 640;
	d71_pipe.layer_group[0].layer_param[1].stride = 640;
	d71_pipe.layer_group[0].layer_param[1].h_offset = 0;
	d71_pipe.layer_group[0].layer_param[1].v_offset = 0;

	d71_pipe.cu_index[0]=1;                                 //composition input layer enable
	d71_pipe.cu_blocks[0].size.hsize=640;
	d71_pipe.cu_blocks[0].size.vsize=480;

	d71_pipe.dou_index[0]=1;
	d71_pipe.dou_blocks[0].active_size.hsize=640;
	d71_pipe.dou_blocks[0].active_size.vsize=480;
	d71_pipe.dou_blocks[0].video_mode=1;
	d71_pipe.dou_blocks[0].htotal=722;
	d71_pipe.dou_blocks[0].hstart=656;
	d71_pipe.dou_blocks[0].hend=706;
	d71_pipe.dou_blocks[0].hsync_polar=1;
	d71_pipe.dou_blocks[0].vstart=488;
	d71_pipe.dou_blocks[0].vend=538;
	d71_pipe.dou_blocks[0].vtotal=546;
}

static void d71_lpu1_layer0_init(void __iomem *base, uintptr_t fb)
{
	bs_init(base + DOU1_BS);

	lpu_layer_init(base + LPU1_LAYER0, fb);

	cu_init(base + CU1);
	cu_input(base + CU1, 0);

	ips_init(base + DOU1_IPS);

	d71_bind(base + LPU1_LAYER0, 0, base + CU1, 0);
	d71_bind(base + CU1, 0, base + DOU1_IPS, 0);

	gcu_flush(base + GCU, 1);

}

static void d71_disable(void __iomem *base)
{
	lpu_layers_disable(base + LPU0_LAYER0);
	lpu_layers_disable(base + LPU1_LAYER0);
	cu_disable(base+CU0, 0);
	dou_disable(base+DOU0, 0);
}

static void d71_init(void __iomem *base)
{
	gcu_init(base + GCU);
}

static int cmd_d71(int argc, char **argv)
{
	int i = 0;

	if (argc < 2)
		return -EUSAGE;

	if (argv[1][0] == 'i') {
		if (argc == 3) {
			d71_addr = strtoul(argv[2], 0, 0);
		}

		d71_init((void __iomem *)d71_addr);

	} else if (argv[1][0] == 'w') {
		if (argc ==4) {
			i = strtoul(argv[2], 0, 0);
			lpu_layer_wb = strtoul(argv[3], 0, 0);
		}
		d71_wb_layer_init((void __iomem *)d71_addr, lpu_layer_wb, i);

	} else if (argv[1][1] == '0') {
		if (argc == 3)
			lpu0_layer1_addr = strtoul(argv[2], 0, 0);

		d71_lpu0_layer1_init((void __iomem *)d71_addr, lpu0_layer1_addr);

	} else if (argv[1][1] == '1') {
		if (argc == 3)
			lpu1_layer0_addr = strtoul(argv[2], 0, 0);

		d71_lpu1_layer0_init((void __iomem *)d71_addr, lpu1_layer0_addr);

	} else if (argv[1][0] == 'd') {
		d71_dump((void __iomem *)d71_addr);

	} else if (argv[1][0] == 'p') {

		if (argc == 3)
			lpu0_layer0_addr = strtoul(argv[2], 0, 0);

		d71_pipe_case_0_init(lpu0_layer0_addr, lpu0_layer1_addr);
		d71_update_pipe((void __iomem *)d71_addr,&d71_pipe);

	} else if (argv[1][0] == 'u') {
		if (argc == 3)
			update_addr = strtoul(argv[2], 0, 0);

		d71_update_1st_layer((void __iomem *)d71_addr, update_addr);

	} else if (argv[1][0] == 's') {
		d71_disable((void __iomem *)d71_addr);
	} else {
		return -EUSAGE;
	}

	return 0;

}

MK_CMD(d71, cmd_d71, "Control ARM D71",
	"d71 init [d71_addr]\n"
	"    - initialize the specific d71 with fb @addr\n"
	"d71 wb index [lpu_layer_addr]\n"
	"    - enable write-back function of lpu[index]\n"
	"d71 l01\n"
	"    - initialize the lpu0_layer1 of the specific d71 with fb @addr, default addr is 0x60000000\n"
	"d71 l10 [addr]\n"
	"    - initialize the lpu1_layer0 of the specific d71 with fb @addr, default addr is 0x60400000\n"
	"d71 dump\n"
	"    - dump the register of d71\n"
	"d71 pipe [addr]\n"
	"    - initialize the lpu0_layer0 with fb @addr, default addr is 0x602c0000\n"
	"d71 update [addr]\n"
	"    - update lpu0_layer0 with new fb @addr, default addr is 0x60160000\n"
	"d71 shutdown\n"
	"    - disable d71 functio\n"
);


