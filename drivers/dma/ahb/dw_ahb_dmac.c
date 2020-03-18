#include <std/string.h>
#include <std/stdlib.h>
#include <std/stdio.h>
#include <asm/memory.h>
#include <errno.h>
#include <target/irq.h>
#include <target/irqc.h>
#include <target/cmdline.h>
#include "dw_ahb_dmac.h"

static struct ahb_dma_chip dw_chip;
static struct ahb_dma_chan dmac_chan[AHB_DMAC_MAX_CHANNELS];

static void ahb_chan_iowrite32(struct ahb_dma_chan *chan, u32 reg, u32 val)
{
	writel(val, chan->chan_regs + reg);
}

static u32 ahb_chan_ioread32(struct ahb_dma_chan *chan, u32 reg)
{
	return readl(chan->chan_regs + reg);
}

static void ahb_chan_iowrite32And(struct ahb_dma_chan *chan, u32 reg, u32 val)
{
	u32 cfg;
	cfg = ahb_chan_ioread32(chan, reg);
	ahb_chan_iowrite32(chan, reg, (cfg & val));
}

static void ahb_chan_iowrite32Or(struct ahb_dma_chan *chan, u32 reg, u32 val)
{
	u32 cfg;
	cfg = ahb_chan_ioread32(chan, reg);
	ahb_chan_iowrite32(chan, reg, (cfg | val));
}

static void ahb_chan_iowrite64(struct ahb_dma_chan *chan, u32 reg, u64 val)
{
	/*
	 * We split one 64 bit write for two 32 bit write as some HW doesn't
	 * support 64 bit access.
	 */
	writel(lower_32_bits(val), chan->chan_regs + reg);
	writel(upper_32_bits(val), chan->chan_regs + reg + 4);
}

static void ahb_dma_iowrite32(struct ahb_dma_chip *chip, u32 reg, u32 val)
{
	writel(val, chip->regs + reg);
}

static u32 ahb_dma_ioread32(struct ahb_dma_chip *chip, u32 reg)
{
	return readl(chip->regs + reg);
}

static void dw_ahb_dmac_cfg(struct ahb_dma_chip *chip)
{
	u32 tmp;

	chip->chan = dmac_chan;
	chip->regs = (void *)(uintptr_t)DW_AHB_DMAC;
	chip->nr_channels = AHB_DMAC_MAX_CHANNELS;

	for (tmp = 0; tmp < chip->nr_channels; tmp++) {
		struct ahb_dma_chan *chan = &dmac_chan[tmp];
		chan->chip = chip;
		chan->id = tmp;
		chan->chan_regs = chip->regs + tmp * CHAN_REG_LEN;
	}
}

static void ahb_chan_disable(struct ahb_dma_chan *chan)
{
	ahb_dma_iowrite32(chan->chip, DMAC_CHEN, (( 1 << chan->id ) << 8));
}

static void ahb_chan_enable(struct ahb_dma_chan *chan)
{

	ahb_dma_iowrite32(chan->chip, DMAC_CHEN,  ( 1 << chan->id ) | ( 1 << (chan->id + 8)));
}

static bool ahb_chan_is_enabled(struct ahb_dma_chan *chan)
{
	u32 val;
	val = ahb_dma_ioread32(chan->chip, DMAC_CHEN);
	if (val & (1 << chan->id)) {
		return true;
	} else {
		return false;
	}
}

static void ahb_dma_enable(struct ahb_dma_chip *chip)
{
	ahb_dma_iowrite32(chip, DMA_EN, 0x1);
}

//*******************************************************************************************
// Converts the Element size into the TR_WIDTH field value
//*******************************************************************************************
static uint GetElementSizeInTRWidth(uint BitsPerElement)
{
	uint nTR_WIDTH = 0;
	switch(BitsPerElement)
	{
		case 8:
			nTR_WIDTH = 0; // Suggest 8-bits per elements.
			break;
		case 16:
			nTR_WIDTH = 1; // Suggest 16-bits per elements.
			break;
		case 32:
			nTR_WIDTH = 2; // Suggest 32-bits per elements.
			break;
		case 64:
			nTR_WIDTH = 3; // Suggest 64-bits per elements.
			break;
		case 128:
			nTR_WIDTH = 4; // Suggest 128-bits per elements.
			break;
		case 256:
			nTR_WIDTH = 5; // Suggest 256-bits per elements.
			break;
		default:
			printf("Invalid element size %u\n", BitsPerElement);
			break;
	}

	return nTR_WIDTH;
}

//*******************************************************************************************
// Converts the Element size into the TR_WIDTH field value
//*******************************************************************************************
static uint GetNoElementInMSize(uint numberElements)
{
	uint nM_SIZE = 0;
	// Burst size should be loaded to MSIZE
	switch(numberElements)
	{
		case 1:
			nM_SIZE	= 0;	// Suggest 1 data item
			break;
		case 4:
			nM_SIZE	= 1;	// Suggest 4 data item
			break;
		case 8:
			nM_SIZE	= 2;	// Suggest 8 data item
			break;
		case 16:
			nM_SIZE	= 3;	// Suggest 16 data item
			break;
		case 32:
			nM_SIZE	= 4;	// Suggest 32 data item
			break;
		case 64:
			nM_SIZE	= 5;	// Suggest 64 data item
			break;
		case 128:
			nM_SIZE	= 6;	// Suggest 128 data item
			break;
		case 256:
			nM_SIZE	= 7;	// Suggest 256 data item
			break;
		default:
			// NOTE: not setting this value will not affect the transfer if the parameter
			// DMAH_CHx_MAX_MULT_SIZE is set
			printf("Invalid number of elements- %u.\n", numberElements);
			break;
	}
	return nM_SIZE;
}

static int TransferComplete(struct ahb_dma_chan *chan)
{
	while (1)
	{
		if (ahb_dma_ioread32(chan->chip, RAW_TFR_IRQ) & (1 << chan->id))
		{
			printf("Transfer completed.\n");
			break;
		}
	}
	return 0;
}

static int clearInterrupts(struct ahb_dma_chan *chan)
{
	int ret = 0;

	ahb_dma_iowrite32(chan->chip, CLEAR_TFR_IRQ, (1 << chan->id));
	if ((ahb_dma_ioread32(chan->chip, RAW_TFR_IRQ) & (1 << chan->id)) || (ahb_dma_ioread32(chan->chip, STAT_TFR_IRQ) & (1 << chan->id)))
	{
		printf("Unable to clear TFR interrupt for channel %u\n", chan->id);
		ret = -1;
	}

	ahb_dma_iowrite32(chan->chip, CLEAR_BLOCK_IRQ, (1 << chan->id));
	if ((ahb_dma_ioread32(chan->chip, RAW_BLOCK_IRQ) & (1 << chan->id)) || (ahb_dma_ioread32(chan->chip, STAT_BLOCK_IRQ) & (1 << chan->id)))
	{
		printf("Unable to clear BLOCK interrupt for channel %u\n", chan->id);
		ret = -1;
	}

	ahb_dma_iowrite32(chan->chip, CLEAR_SRC_TRAN_IRQ, (1 << chan->id));
	if ((ahb_dma_ioread32(chan->chip, RAW_SRC_TRAN_IRQ) & (1 << chan->id)) || (ahb_dma_ioread32(chan->chip, STAT_SRC_TRAN_IRQ) & (1 << chan->id)))
	{
		printf("Unable to clear SRC_TRAN interrupt for channel %u\n", chan->id);
		ret = -1;
	}

	ahb_dma_iowrite32(chan->chip, CLEAR_DST_TRAN_IRQ, (1 << chan->id));
	if ((ahb_dma_ioread32(chan->chip, RAW_DST_TRAN_IRQ) & (1 << chan->id)) || (ahb_dma_ioread32(chan->chip, STAT_DST_TRAN_IRQ) & (1 << chan->id)))
	{
		printf("Unable to clear DST_TRAN interrupt for channel %u\n", chan->id);
		ret = -1;
	}

	ahb_dma_iowrite32(chan->chip, CLEAR_ERR_IRQ, (1 << chan->id));
	if ((ahb_dma_ioread32(chan->chip, RAW_ERR_IRQ) & (1 << chan->id)) || (ahb_dma_ioread32(chan->chip, STAT_ERR_IRQ) & (1 << chan->id)))
	{
		printf("Unable to clear Error interrupt for channel %u\n", chan->id);
		ret = -1;
	}

	return ret;
}

static int SetupDMA(struct ahb_dma_chan *chan)
{
	uint nCTLL, TT_FC;

	if ((chan->id) >= chan->chip->nr_channels) {
		printf("Invalid channel number %u\n", chan->id);
		return -1;
	}

	clearInterrupts(chan);

	//=========================================
	// Program the src side of channeln
	//=========================================
	ahb_chan_iowrite32(chan, CH_SAR, chan->SRC_Addr);

	nCTLL = ((chan->SINC & 0x3) << 9);			// SINC
	nCTLL |= ((chan->SRC_TR_WIDTH & 0x7) << 4);	// SRC_TR_WIDTH
	nCTLL |= ((chan->SRC_MSIZE & 0x7) << 14);	// SRC_MSIZE

	//Setup the Master Interface for the Source:
	nCTLL |= ( (chan->SRC_SMS & 0x3) << 25);	// SRC_SMS

	TT_FC = ((ahb_chan_ioread32(chan, CH_CTL_L) >> 20) & 0x7);
	if(TT_FC < 4)
	{
		//clear relevant bits
		ahb_chan_iowrite32And(chan, CH_CTL_H, 0xfffff000);
		// DMAC is Flow controller so setup size in BLOCK_TS
		ahb_chan_iowrite32(chan, CH_CTL_H, chan->BLOCK_TS);
	}

	//=========================================
	// Program the dst side of channeln
	//=========================================
	ahb_chan_iowrite32(chan, CH_DAR, chan->DST_Addr);

	nCTLL |= ((chan->DINC & 0x3) << 7);			// DINC
	nCTLL |= ((chan->DST_TR_WIDTH & 0x7) << 1);	// DST_TR_WIDTH
	nCTLL |= ((chan->DST_MSIZE & 0x7) << 11);	// DST_MSIZE

	//Setup the Master Interface for the Source:
	nCTLL |= ( (chan->DST_DMS & 0x3) << 23);	// DST_SMS

	//Enable interrupts
	nCTLL |= (1 << 0);

	// Write to the configuration registers
	// Must clear relevant bits before writing new values
	ahb_chan_iowrite32And(chan, CH_CTL_L, 0xf8760000);

	ahb_chan_iowrite32Or(chan, CH_CTL_L, nCTLL);

	ahb_chan_enable(chan);

	if(!ahb_chan_is_enabled(chan))
	{
		return -1;
	}

	return 0;
}

//*******************************************************************************************
// Memory to Memory Transfer
//*******************************************************************************************
static int MemToMemTransfer(struct ahb_dma_chan *chan, uint srcaddr, uint dstaddr, uint SrcBytesPerElement,
						 uint DstBytesPerElement, uint numberFrames, uint numberSrcElements, uint numberDstElements,
						 uint nSrcInterface, uint nDestInterface)
{
	uint TT_FC = 0;
	int ret = 0;

	if(ahb_chan_is_enabled(chan))
	{
		printf("channel %d is non-idle!\n", chan->id);
		ret = -1;
	}

	TT_FC = ((ahb_chan_ioread32(chan, CH_CTL_L) >> 20) & 0x7);
	if (TT_FC != 0x0)
		// Set TT_FC
		ahb_chan_iowrite32And(chan, CH_CTL_L, ~(7 << 20));

	// Transfer characteristics...
	// Bits per element should be loaded to TR_WIDTH
	chan->SRC_TR_WIDTH = GetElementSizeInTRWidth(SrcBytesPerElement*8);
	chan->DST_TR_WIDTH = GetElementSizeInTRWidth(DstBytesPerElement*8);

	// Burst size should be loaded to MSIZE
	chan->SRC_MSIZE = GetNoElementInMSize(numberSrcElements);
	chan->DST_MSIZE = GetNoElementInMSize(numberDstElements);

	// Number of frames Should be loaded to CTLx.BLOCK_TS
	// which is frames * numElements
	chan->BLOCK_TS = (numberFrames*numberSrcElements);

	chan->SRC_Addr = srcaddr;
	chan->SINC = 0;
	chan->SRC_SMS = nSrcInterface;

	chan->DST_Addr = dstaddr;
	chan->DINC = 0;
	chan->DST_DMS = nDestInterface;

	ret = SetupDMA(chan);
	if (!ret)
		ret = TransferComplete(chan);
	return ret;
}

//*******************************************************************************************
// Single Block Memory to Memory Transfer
// defult block transfer size is 16 bytes.
//*******************************************************************************************
static int SingleBlockMTMTrans(struct ahb_dma_chip *chip, uint srcaddr, uint dstaddr, uint SrcBytesPerElement,
						 uint DstBytesPerElement, uint numberSrcElements, uint numberDstElements, uint chanid)
{
	uint numberFrames = 4;
	uint nSrcInterface = 0;
	uint nDestInterface = 0;

	return MemToMemTransfer(&chip->chan[chanid], srcaddr, dstaddr, SrcBytesPerElement,
			DstBytesPerElement, numberFrames, numberSrcElements, numberDstElements,
			nSrcInterface, nDestInterface);
}

static int dw_ahb_dmac_hw_init(struct ahb_dma_chip *chip)
{
	int i;

	dw_ahb_dmac_cfg(chip);
	ahb_dma_enable(chip);

	for (i = 0; i < chip->nr_channels; i++) {
		ahb_chan_disable(&chip->chan[i]);
	}
	return 0;
}


int do_cmd_ahb_dmac(int argc, char **argv)
{
	int ret = 0;
	u32 srcaddr, dstaddr;
	uint SrcBytesPerElement, DstBytesPerElement;
	uint numberSrcElements, numberDstElements;
	int chanid;

	if (argc < 2)
		return -EUSAGE;

	if (!strcmp("init", argv[1])) {
		ret = dw_ahb_dmac_hw_init(&dw_chip);
	}

	if (!strcmp("smm", argv[1])) {
		srcaddr = strtoul(argv[2], NULL, 0);
		dstaddr = strtoul(argv[3], NULL, 0);
		SrcBytesPerElement = strtoul(argv[4], NULL, 0);
		DstBytesPerElement = strtoul(argv[5], NULL, 0);
		numberSrcElements = strtoul(argv[6], NULL, 0);
		numberDstElements = strtoul(argv[7], NULL, 0);
		chanid = strtoul(argv[8], NULL, 0);

		ret = SingleBlockMTMTrans(&dw_chip, srcaddr, dstaddr, SrcBytesPerElement,
				DstBytesPerElement, numberSrcElements, numberDstElements, chanid);
	}
	return ret;
}

MK_CMD(dmac, do_cmd_ahb_dmac, "Designware AHB DMAC cmd",
	"dmac init\n"
	"    -dmac initialization.\n"
	"dmac smm source_mem dest_mem src_width dst_width src_num dst_num chan_id\n"
	"    -use {chan_id} channel to transfer single block data in {source_mem} to {dest_mem}.\n"
	"     block size = src_width * src_num * numberFrames, numberFrames is a default value(4).\n"
	"     src_width, dst_width: transfer width, bytes per element.\n"
	"     src_num, dsr_num: burst size, number of elements.\n"
);
