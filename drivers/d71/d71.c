#include <target/utils.h>
#include "d71.h"
#include <stdio.h>
#include <target/cmdline.h>
#include <target/memory.h>

#define DEFAULT_PREPRETCH_LINE 5

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


static int gcu_init(void __iomem *base)
{
	u32 core_id;

	core_id = readl(base + GLB_CORE_ID);
	printf("D71 PRODUCT_ID 0x%x\n", GLB_CORE_ID_PRODUCT_ID(core_id));

	/* Software reset request */
	__raw_setl(GCU_CONTROL_SRST, base + GCU_CONTROL);
	while (readl(base + GCU_CONTROL) & GCU_CONTROL_SRST);

	/* Operation mode request */
	writel(MODE_DO01_ACTIVE, base + GCU_CONTROL);

	return 0;
}

static int gcu_dump(void __iomem *base)
{
	printf("GLB_IRQ_STATUS = 0x%x\n", readl(base + GLB_IRQ_STATUS));
	printf("GCU_IRQ_RAW_STATUS = 0x%x\n", readl(base + GCU_IRQ_RAW_STATUS));
	printf("GCU_STATUS = 0x%x\n", readl(base + GCU_STATUS));
	printf("GCU_CONTROL = 0x%x\n", readl(base + GCU_CONTROL));
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

	/* Bacground color: white color */
	writel(0x3fffffff, base + CU_BG_COLOR);

	return 0;
}

static int cu_input(void __iomem *base, int input)
{
	base += input * PER_CU_INPUT;

	writel(HV_SIZE(640, 480), base + CU_INPUT_SIZE);
	writel(HV_OFFSET(0, 0), base + CU_INPUT_OFFSET);
	__raw_setl(CU_INPUT_CONTROL_EN | CU_INPUT_CONTROL_PAD, base + CU_INPUT_CONTROL);

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

static int lpu_layer_init(void __iomem *base, uintptr_t fb)
{
	writel((u32)fb, base + L_P0_PTR_LOW);
	writel((fb >> 16) >> 16, base + L_P0_PTR_HIGH);

	writel(640 * 4, base + L_P0_STRIDE);

	/* __raw_setl(L_AD_CONTROL_AEN, base + L_AD_CONTROL); */

	writel(HV_SIZE(640, 480), base + L_IN_SIZE);
	writel(FORMAT_XR24, base + L_FORMAT);
	writel(L_CONTROL_EN, base + L_CONTROL);

	return 0;
}

static int lpu_dump(void __iomem *base)
{
	printf("LPU_IRQ_RAW_STATUS = 0x%x\n", readl(base + LPU_IRQ_RAW_STATUS));
	printf("LPU_STATUS = 0x%x\n", readl(base + LPU_STATUS));
	printf("LPU_TBU_STATUS = 0x%x\n", readl(base + LPU_TBU_STATUS));
	return 0;
}


static int d71_bind(void __iomem *out, int oidx, void __iomem *in, int iidx)
{
	u16 id;

	id = readl(out + OUTPUT_ID + 4 * oidx);
	writel(id, in + INPUT_ID + 4 * iidx);

	return 0;
}


static int dou_dump(void __iomem *base)
{
	printf("DOU_IRQ_RAW_STATUS = 0x%x\n", readl(base + DOU_IRQ_RAW_STATUS));
	printf("DOU_STATUS = 0x%x\n", readl(base + DOU_STATUS));

	return 0;
}


static int ips_init(void __iomem *base)
{
	/* writel(IPS_CONTROL_RGB, base + IPS_CONTROL); */
	writel(HV_SIZE(640, 480), base + IPS_SIZE);
	writel(0x8, base + IPS_DEPTH);

	return 0;
}


int d71_init(void __iomem *base)
{
	gcu_init(base + GCU);

	bs_init(base + DOU0_BS);

	lpu_layer_init(base + LPU0_LAYER0, 0x60000000);

	cu_init(base + CU0);
	cu_input(base + CU0, 0);

	ips_init(base + DOU0_IPS);

	d71_bind(base + LPU0_LAYER0, 0, base + CU0, 0);
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

static int cmd_d71(int argc, char **argv)
{
	if (argc < 2)
		return -EUSAGE;

	if (argv[1][0] == 'i') {
		d71_init((void __iomem *)D71_REG_BASE);
	} else if (argv[1][0] == 'i') {
		d71_dump((void __iomem *)D71_REG_BASE);
	} else {
		return -EUSAGE;
	}

	return 0;
}


MK_CMD(d71, cmd_d71, "Control ARM D71",
	"d71 init\n"
	"    - initialize d71 with fb @0x60000000\n"
	"d71 dump\n"
	"    - dump the register of d71\n"
);

