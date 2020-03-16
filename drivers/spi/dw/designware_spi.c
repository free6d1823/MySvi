#include <asm/io.h>
#include <asm/memory.h>
#include <std/stdlib.h>
#include <std/stdio.h>
#include <target/lopoll.h>
#include <target/cmdline.h>
#include <std/string.h>
#include "designware_spi.h"

struct dw_spi_priv priv[SPI_NUM];

static inline u32 dw_read(struct dw_spi_priv *priv, u32 offset)
{
	return __raw_readl(priv->regs + offset);
}

static inline void dw_write(struct dw_spi_priv *priv, u32 offset, u32 val)
{
	__raw_writel(val, priv->regs + offset);
}

static inline void spi_enable_chip(struct dw_spi_priv *priv, int enable)
{
	dw_write(priv, DW_SPI_SSIENR, (enable ? 1 : 0));
}

/* Restart the controller, disable all interrupts, clean rx fifo */
static void spi_hw_init(struct dw_spi_priv *priv)
{
	spi_enable_chip(priv, 0);
	dw_write(priv, DW_SPI_IMR, 0xff);
	spi_enable_chip(priv, 1);

	/*
	 * Try to detect the FIFO depth if not set by interface driver,
	 * the depth could be from 2 to 256 from HW spec
	 */
	if (!priv->fifo_len) {
		u32 fifo;

		for (fifo = 1; fifo < 256; fifo++) {
			dw_write(priv, DW_SPI_TXFLTR, fifo);
			if (fifo != dw_read(priv, DW_SPI_TXFLTR))
				break;
		}

		priv->fifo_len = (fifo == 1) ? 0 : fifo;
		dw_write(priv, DW_SPI_TXFLTR, 0);
	}
	printf("%s: fifo_len=%d\n", __func__, priv->fifo_len);
}

/* Return the max entries we can fill into tx fifo */
static inline u32 tx_max(struct dw_spi_priv *priv)
{
	u32 tx_left, tx_room, rxtx_gap;

	tx_left = priv->totallen - priv->tx_currentlen;
	tx_room = priv->fifo_len - dw_read(priv, DW_SPI_TXFLR);

	/*
	 * Another concern is about the tx/rx mismatch, we
	 * thought about using (priv->fifo_len - rxflr - txflr) as
	 * one maximum value for tx, but it doesn't cover the
	 * data which is out of tx/rx fifo and inside the
	 * shift registers. So a control from sw point of
	 * view is taken.
	 */
	rxtx_gap = ((priv->totallen - priv->rx_currentlen) - (priv->totallen - priv->tx_currentlen)) /
		(priv->bits_per_word >> 3);

	return min3(tx_left, tx_room, (u32)(priv->fifo_len - rxtx_gap));
}

/* Return the max entries we should read out of rx fifo */
static inline u32 rx_max(struct dw_spi_priv *priv)
{
	u32 rx_left = priv->totallen - priv->rx_currentlen;

	return min_t(u32, rx_left, dw_read(priv, DW_SPI_RXFLR));
}


static void dw_writer(struct dw_spi_priv *priv)
{
	u32 max = tx_max(priv);
	u16 txw = 0;

	while (max--) {
		if (priv->tx_currentlen < priv->cmdlen) {
			if (priv->bits_per_word == 8)
				txw = *(u8 *)(priv->cmdbuf);
			else
				txw = *(u16 *)(priv->cmdbuf);

			priv->cmdbuf += priv->bits_per_word >> 3;
		}
		else if ((!priv->isin) && (priv->tx_currentlen >= priv->cmdlen) && (priv->tx_currentlen < priv->totallen)) {
			if (priv->bits_per_word == 8)
				txw = *(u8 *)(priv->databuf);
			else
				txw = *(u16 *)(priv->databuf);

			priv->databuf += priv->bits_per_word >> 3;
		}
		dw_write(priv, DW_SPI_DR, txw);
		priv->tx_currentlen++;
	}
}


static void dw_reader(struct dw_spi_priv *priv)
{
	u32 max = rx_max(priv);
	u16 rxw;

	while (max--) {
		rxw = dw_read(priv, DW_SPI_DR);
		if ((priv->isin) && (priv->rx_currentlen < priv->totallen) && (priv->rx_currentlen >= priv->cmdlen)) {
			if (priv->bits_per_word == 8)
				*(u8 *)(priv->databuf) = rxw;
			else
				*(u16 *)(priv->databuf) = rxw;

			priv->databuf += priv->bits_per_word >> 3;
		}
		priv->rx_currentlen++;
	}
}

static int poll_transfer(struct dw_spi_priv *priv)
{
	do {
		dw_writer(priv);
		dw_reader(priv);
	} while (priv->rx_currentlen < priv->totallen);

	return 0;
}

static int dw_spi_xfer(struct dw_spi_priv *priv,
				const void *cmdbuf, int cmdlen, void *databuf, int datalen, bool is_datain)
{
	const u8 *cmdbuffer = cmdbuf;
	u8 *databuffer = databuf;
	int ret = 0;

	priv->cmdlen = cmdlen;
	priv->datalen = datalen;
	priv->totallen = cmdlen + datalen;
	priv->tx_currentlen = 0;
	priv->rx_currentlen = 0;
	priv->cmdbuf = (void *)cmdbuffer;
	priv->databuf = databuffer;
	priv->isin = is_datain;

	/* Start transfer in a polling loop */
	ret = poll_transfer(priv);

	return ret;
}

int dw_spi_transfer_one_message(struct dw_spi_priv *priv,
		       const void *cmdbuf, int cmdlen, void *databuf, int datalen, bool datain)
{
	u32 val;
	int ret = 0;
	u32 cr0 = 0;

	cr0 = (priv->bits_per_word - 1) | (priv->type << SPI_FRF_OFFSET) |
		((((priv->mode & SPI_CPOL) ? 1 : 0) << SPI_SCOL_OFFSET) |
			(((priv->mode & SPI_CPHA) ? 1 : 0) << SPI_SCPH_OFFSET))|
		(priv->tmode << SPI_TMOD_OFFSET);

	cr0 &= ~SPI_TMOD_MASK;
	cr0 |= (priv->tmode << SPI_TMOD_OFFSET);

	/*Disable controller before writing control registers */
	spi_enable_chip(priv, 0);

	/* Reprogram cr0 only if changed */
	if (dw_read(priv, DW_SPI_CTRL0) != cr0)
		dw_write(priv, DW_SPI_CTRL0, cr0);

	dw_write(priv, DW_SPI_BAUDR, priv->clk_div);

	dw_write(priv, DW_SPI_SER, 1 << priv->cs);

	spi_enable_chip(priv, 1);

	ret = dw_spi_xfer(priv, cmdbuf, cmdlen, databuf, datalen, datain);

	spi_enable_chip(priv, 0);
	/*cs disable*/
	dw_write(priv, DW_SPI_SER, 0);

	/*
	 * Wait for current transmit operation to complete.
	 * Otherwise if some data still exists in Tx FIFO it can be
	 * silently flushed, i.e. dropped on disabling of the controller,
	 * which happens when writing 0 to DW_SPI_SSIENR which happens
	 * in the beginning of new transfer.
	 */

	if (readl_poll_timeout(priv->regs + DW_SPI_SR, val,
			       (val & SR_TF_EMPT) && !(val & SR_BUSY),
			       RX_TIMEOUT * 1000)) {
		ret = -ETIMEDOUT;
	}
	return ret;
}

int gindex;

static int spi_init(int index)
{
	gindex = index;

	priv[index].regs = (void *)(uintptr_t)DW_SPI_REG_BASE(index);
	priv[index].bits_per_word = 8;
	priv[index].type = SPI_FRF_SPI;
	priv[index].mode = 3;
	priv[index].tmode = SPI_TMOD_TR;
	priv[index].clk_div = 2;
	priv[index].cs = 0;

	spi_hw_init(&priv[index]);
	return 0;
}

static int spi_setcs(int cs)
{
	priv[gindex].cs = cs;
	return 0;
}

static int dw_spi_write(const void *cmdbuf, int cmdlen, void *databuf, int datalen)
{
	return dw_spi_transfer_one_message(&priv[gindex], cmdbuf, cmdlen, databuf, datalen, 0);
}

static int dw_spi_read(const void *cmdbuf, int cmdlen, void *databuf, int datalen)
{
	return dw_spi_transfer_one_message(&priv[gindex], cmdbuf, cmdlen, databuf, datalen, 1);
}

int cmd_spi(int argc, char **argv)
{
	int index = 0;
	int cs;

	if (argc < 2)
		return -EUSAGE;

	if (argv[1][0] == 'i') {

		if (argc >= 3)
			index = strtoul(argv[2], NULL, 0);
		spi_init(index);
		return 0;
	}

	if (argv[1][0] == 'c') {
		if (argc >= 3)
			cs = strtoul(argv[2], NULL, 0);
		return spi_setcs(cs);
	}

	if (argv[1][0] == 'w') {

		if (argc < 6)
			return -EUSAGE;

		const void *cmdbuf = (const void *)strtoul(argv[2], NULL, 0);
		int cmdlen = strtoul(argv[3], NULL, 0);
		void *databuf = (void *)strtoul(argv[4], NULL, 0);
		int datalen = strtoul(argv[5], NULL, 0);
		return dw_spi_write(cmdbuf, cmdlen, databuf, datalen);
	}

	if (argv[1][0] == 'r') {

		if (argc < 6)
			return -EUSAGE;

		const void *cmdbuf = (const void *)strtoul(argv[2], NULL, 0);
		int cmdlen = strtoul(argv[3], NULL, 0);
		void *databuf = (void *)strtoul(argv[4], NULL, 0);
		int datalen = strtoul(argv[5], NULL, 0);
		return dw_spi_read(cmdbuf, cmdlen, databuf, datalen);

	}
	return -1;
}

MK_CMD(spi, cmd_spi, "Designware spi host controller cmd",
	" spi init index\n"
	"	-spi initialization\n"
	" spi cs number\n"
	"	- spi chip select, default value is 0\n"
	" spi w cmdbuf cmdlen databuf datalen\n"
	"	-spi write <datalen> data in databuf through the cmd in <cmdbuf>\n"
	" spi r cmdbuf cmdlen databuf datalen\n"
	"	-spi read <datalen> data to databuf through the cmd in <cmdbuf>\n"
);
