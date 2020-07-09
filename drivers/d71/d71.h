#ifndef __D71_H__
#define __D71_H__

#include <target/regdef.h>
#include <std/stdbool.h>


/* This register block provides control of the global
 * control unit and information on its operation.
 */
#define GLB_ARCH_ID       0x0000
#define GLB_CORE_ID       0x0004
#define GLB_IRQ_STATUS    0x0010
#define OUTPUT_ID         0x0060
#define INPUT_ID          0x0080
#define GCU_IRQ_RAW_STATUS 0x00A0
#define BLK_STATUS        0x00B0
#define GCU_CONFIG_VALID0 0x00D4
#define GCU_CONFIG_VALID1 0x00D8
#define BLK_CONTROL       0x00D0

#define GLB_CORE_ID_PRODUCT_ID(v) (((v) >> 16) & REG_16BIT_MASK)
#define PRODUCT_ID        0x0071

#define GCU_STATUS_ACTIVE BIT(31)

#define GCU_CONTROL_SRST  BIT(16)

/* for GCU_STATUS, GCU_CONTROL */
#define GCU_MODE_MASK       REG_3BIT_MASK

#define MODE_INACTIVE       0x0
#define MODE_TBU_CONNECT    0x1
#define MODE_TBU_DISCONNECT 0x2
#define MODE_DO0_ACTIVE     0x3
#define MODE_DO1_ACTIVE     0x4
#define MODE_DO01_ACTIVE    0x5

/* for GCU_CONFIG_VALID0, GCU_CONFIG_VALID1 */
#define GCU_CVAL            BIT(0)


/* This register block provides layer processing unit
 * control and status functionality.
 */
#define LPU_IRQ_RAW_STATUS 0x00A0
#define LPU_STATUS         0x00B0
#define LPU_TBU_STATUS     0x00B4

#define LPU_STATUS_ACTIVE BIT(31)


/* This register block provides layer processing unit
 * rich & simple DMA layer control functionality.
 */
#define L_LAYER_INFO     0x00C0
#define L_FORMAT         0x00D8
#define L_IN_SIZE        0x00E0
#define L_P0_PTR_LOW     0x0100
#define L_P0_PTR_HIGH    0x0104
#define L_P0_STRIDE      0x0108
#define L_P1_PTR_LOW     0x0110
#define L_P1_PTR_HIGH    0x0114
#define L_P1_STRIDE      0x0118
#define L_AD_CONTROL     0x0160

#define L_LAYER_INFO_RF  BIT(0)

#define L_CONTROL_EN     BIT(0)
#define L_HFLIP			BIT(10)
#define L_VFLIP			BIT(11)


/* L_FORMAT, FourCC */
#define FORMAT_ARGB_2101010 0x00 /* ARGB_2101010, 10-bit sample, 2-bit alpha */
#define FORMAT_ABGR_2101010 0x00 /* ABGR_2101010, 10-bit sample, 2-bit alpha */
#define FORMAT_RGBA_2101010 0x00 /* RGBA_2101010, 10-bit sample, 2-bit alpha */
#define FORMAT_BGRA_2101010 0x00 /* BGRA_2101010, 10-bit sample, 2-bit alpha */

#define FORMAT_ARGB_8888 0x08 /* ARGB_8888, 8-bit sample, 8-bit alpha */
#define FORMAT_ABGR_8888 0x09 /* ABGR_8888, 8-bit sample, 8-bit alpha */
#define FORMAT_RGBA_8888 0x0A /* RGBA_8888, 8-bit sample, 8-bit alpha */
#define FORMAT_BGRA_8888 0x0B /* BGRA_8888, 8-bit sample, 8-bit alpha */

#define FORMAT_XRGB_8888 0x10 /* XRGB_8888, 8-bit sample, wasted byte (no alpha) */
#define FORMAT_XBGR_8888 0x11 /* XBGR_8888, 8-bit sample, wasted byte (no alpha) */
#define FORMAT_RGBX_8888 0x12 /* RGBX_8888, 8-bit sample, wasted byte (no alpha) */
#define FORMAT_BGRX_8888 0x13 /* BGRX_8888, 8-bit sample, wasted byte (no alpha) */

#define L_AD_CONTROL_AEN BIT(0)


/* This register block provides composition unit
 * control functionality.
 */
#define CU_INPUT_ID0      0x0080
#define CU_INPUT_ID1      0x0084
#define CU_INPUT_ID2      0x0088
#define CU_INPUT_ID3      0x008C
#define CU_INPUT_ID4      0x0090
#define CU_IRQ_RAW_STATUS 0x00A0
#define CU_STATUS         0x00B0
#define CU_SIZE           0x00D4
#define CU_BG_COLOR       0x00DC

#define CU_INPUT_SIZE    0x00E0
#define CU_INPUT_OFFSET  0x00E4
#define CU_INPUT_CONTROL 0x00E8
#define PER_CU_INPUT     0x0010

#define CU_STATUS_ACTIVE BIT(31)

#define HV_SIZE(h, v)      (((h) & 0x1FFF) + (((v) & 0x1FFF) << 16))
#define HV_OFFSET(h, v)		(((h) & 0xFFF) + (((v) & 0xFFF) << 16))

#define CU_INPUT_CONTROL_EN   BIT(0)
#define CU_INPUT_CONTROL_PAD  BIT(1)
#define CU_INPUT_CONTROL_PMUL BIT(2)
#define CU_INPUT_CTRL_ALPHA(x)	(((x) & 0xFF) << 8)



/* This register block provides display output unit
 * control and timing functionality.
 */
#define DOU_BS_START       0x0600
#define DOU_IPS_START      0x0200
#define DOU_IRQ_RAW_STATUS 0x00A0
#define DOU_STATUS         0x00B0

#define DOU_STATUS_ACTIVE  BIT(31)


/* This register block provides display output unit
 * image processing subsystem control functionality.
 */
#define IPS_SIZE      0x00D4
#define IPS_DEPTH     0x00D8

#define IPS_CONTROL_RGB    BIT(0)
#define IPS_CONTROL_FT     BIT(4)
#define IPS_CONTROL_YUV    BIT(8)
#define IPS_CONTROL_CHD422 BIT(9)
#define IPS_CONTROL_CHD420 BIT(10)
#define IPS_CONTROL_LPF    BIT(11)
#define IPS_CONTROL_DITH   BIT(12)
#define IPS_CONTROL_CLAMP  BIT(16)
#define IPS_CONTROL_SBS    BIT(17)


/* This register block provides registers for the
 * display output unit backend subsystem.
 */
#define BS_CONTROL        0x00D0
#define BS_PROG_LINE      0x00D4
#define BS_PREFETCH_LINE  0x00D8
#define BS_BG_COLOR       0x00DC
#define BS_ACTIVESIZE     0x00E0
#define BS_HINTERVALS     0x00E4
#define BS_VINTERVALS     0x00E8
#define BS_SYNC           0x00EC
#define BS_DRIFT_TO       0x0100

#define BS_CONTROL_DL	  BIT(16) /* dual link */
#define BS_CONTROL_TM     BIT(12) /* Test mode (color bars) enable */
#define BS_CONTROL_BM     BIT(2)  /* back pressure */
#define BS_CONTROL_VM     BIT(1) /* Video Mode enable */
#define BS_CONTROL_EN     BIT(0) /* Display backend timing enable */

#define BS_SYNC_HSW(x)		((x) & 0x3FF)
#define BS_SYNC_VSW(x)		(((x) & 0xFF) << 16)

#define HINTERVALS(hfp, hbp)  (((hfp) & 0xFFF) + (((hbp) & 0x3FF) << 16))
#define VINTERVALS(vfp, vbp)  (((vfp) & 0x3FFF) + (((vbp) & 0xFF) << 16))

#define BS_SYNC_HSP        BIT(12)
#define BS_SYNC_VSP        BIT(28)
#define HV_SYNCWIDTH(h, v) (((h) & 0x3FF) + (((v) & 0xFF) << 16))


#define GCU     0x0000  /* Global Control Unit */
#define LPU0    0x0200  /* Layer Processing Unit 0 */
#define LPU0_LAYER0 0x0400  /* LPU0 Layer 0 (Rich) */
#define LPU0_LAYER1 0x0600  /* LPU0 Layer 1 (Simple) */
#define LPU0_LAYER2 0x0800  /* LPU0 Layer 2 (Rich) */
#define LPU0_LAYER3 0x0A00  /* LPU0 Layer 3 (Simple) */
#define LPU0_LAYER_WR 0x0C00  /* LPU0 Write-back Layer */
#define CU0          0x0E00  /* Composition Unit 0 */
#define CU0_SPLITTER 0x1000  /* CU0 Line Splitter */
#define CU0_SCALER0  0x1200  /* CU0 Scaling Engine 0 */
#define CU0_SCALER1  0x1400  /* CU0 Scaling Engine 1 */
#define CU0_MERGER   0x1600  /* CU0 Line Merger */
#define DOU0     0x1800  /* Display Output Unit 0 */
#define DOU0_IPS 0x1A00  /* DOU0 Image Processing Subsystem */
#define DOU0_BS  0x1E00  /* DOU0 Backend Subsystem */
#define LPU1     0x2200  /* Layer Processing Unit 1 */
#define LPU1_LAYER0 0x2400  /* LPU1 Layer 0 (Rich) */
#define LPU1_LAYER1 0x2600  /* LPU1 Layer 1 (Simple) */
#define LPU1_LAYER2 0x2800  /* LPU1 Layer 2 (Rich) */
#define LPU1_LAYER3 0x2A00  /* LPU1 Layer 3 (Simple) */
#define CU1          0x2E00  /* Composition Unit 1 */
#define CU1_SPLITTER 0x3000  /* CU1 Line Splitter */
#define CU1_SCALER0  0x3200  /* CU1 Scaling Engine 0 */
#define CU1_SCALER1  0x3400  /* CU1 Scaling Engine 1 */
#define CU1_MERGER   0x3600  /* CU1 Line Merger */
#define DOU1     0x3800  /* Display Output Unit 1 */
#define DOU1_IPS 0x3A00  /* DOU1 Image Processing Subsystem */
#define DOU1_BS  0x3E00  /* DOU1 Backend Subsystem */


#define D71_DEFAULT_PREPRETCH_LINE	5

struct layer_layout_param {
    int width;
	int height;
	int stride;
	int format;
	int h_offset;
	int v_offset;
	int alpha_value;
	int alpha_type;
	uintptr_t fb;
};

struct lpu_layers {
	int lpu_layer_index[4];  //output cu index 0 or 1, -1 means disable this layer
	int lpu_layer_out[4];    //cu input index 0~4, -1 means no
	int lpu_layer_id[4];
	struct layer_layout_param layer_param[4];
};


struct cu_scalers {
	int scaler_index[2];    // output dou index 0 or 1, -1 means disable this scaler
	int scaler_id[2];
};

struct block_size {
	int hsize;
	int vsize;
};

struct cu_block_struct {
	int cu_id;
	struct cu_scalers scalers[2];
	struct block_size size;
};

struct dou_block_struct {//the parameters come from panel parameters
	int dou_id;
	struct block_size active_size;
	int hstart;
	int hend;
	int htotal;
	int vstart;
	int vend;
	int vtotal;
	bool vsync_polar;
	bool hsync_polar;
	bool video_mode;
	bool dual_link;
};

struct dpu_pipe {
	int lpu_index[2];  //1 means enable, 0 means disable
	int lpu_id[2];
	struct lpu_layers layer_group[2];
	int cu_index[2];   //1 means enable, 0 means disable
	struct cu_block_struct cu_blocks[2];
	int dou_index[2];
	struct dou_block_struct dou_blocks[2];
};


#endif /* __D71_H__ */
