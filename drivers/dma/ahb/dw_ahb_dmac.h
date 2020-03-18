#ifndef __DW_AHB_DMAC_H_
#define __DW_AHB_DMAC_H_

#include <target/utils.h>

struct ahb_dma_chan
{
	struct ahb_dma_chip	*chip;
	void __iomem	*chan_regs;
	u8	id;
	u32	SRC_Addr;
	u32	DST_Addr;
	u32	BLOCK_TS;
	u32	SRC_TR_WIDTH;
	u32	SINC;
	u32	SRC_MSIZE;
	u32	SRC_SMS;
	u32	DST_TR_WIDTH;
	u32	DINC;
	u32	DST_MSIZE;
	u32	DST_DMS;
	u32	TT_FC;
};

struct ahb_dma_chip
{
	void __iomem	*regs;
	u32	nr_channels;
	struct ahb_dma_chan	*chan;
};

#define AHB_DMAC_MAX_CHANNELS		8
#define CHAN_REG_LEN			0x58

/* DMA channel registers offset */
#define CH_SAR				0x000 /* R/W Chan Source Address */
#define CH_DAR				0x008 /* R/W Chan Destination Address */

#define CH_CTL				0x018 /* R/W Chan Control */
#define CH_CTL_L			0x018 /* R/W Chan Control 00-31 */
#define CH_CTL_H			0x01C /* R/W Chan Control 32-63 */
#define CH_STAT				0x020 /* R/W Chan Status */

#define RAW_TFR_IRQ			0x2c0
#define RAW_BLOCK_IRQ			0x2c8
#define RAW_SRC_TRAN_IRQ		0x2d0
#define RAW_DST_TRAN_IRQ		0x2d8
#define RAW_ERR_IRQ			0x2e0
#define STAT_TFR_IRQ			0x2e8
#define STAT_BLOCK_IRQ			0x2f0
#define STAT_SRC_TRAN_IRQ		0x2f8
#define STAT_DST_TRAN_IRQ		0x300
#define STAT_ERR_IRQ			0x308
#define CLEAR_TFR_IRQ			0x338
#define CLEAR_BLOCK_IRQ			0x340
#define CLEAR_SRC_TRAN_IRQ		0x348
#define CLEAR_DST_TRAN_IRQ		0x350
#define CLEAR_ERR_IRQ			0x358

#define DMA_EN				0x398
#define DMAC_CHEN			0x3a0
#define DMAC_CHAN_EN_SHIFT		0
#define DMAC_CHAN_EN_WE_SHIFT		8

#endif	/* __DW_AHB_DMAC_H_ */



