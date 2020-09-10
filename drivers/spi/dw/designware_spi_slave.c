#include <asm/io.h>
#include <asm/memory.h>
#include <std/stdlib.h>
#include <std/stdio.h>
#include <target/lopoll.h>
#include <target/cmdline.h>
#include <std/string.h>
#include "designware_spi.h"

struct dw_spi_priv priv_slave[SPI_NUM];
int gindex_slave;

int spi_read_test(void *buf, uint32_t len)
{
	u8 cmdbuffer[4];
	cmdbuffer[0] = DW_SPI_DR;

	spi_enable_chip(&priv_slave[gindex_slave], 1);

	dw_write(&priv_slave[gindex_slave], DW_SPI_DR, 0x33);

	dw_read(&priv_slave[gindex_slave], DW_SPI_DR);
	for (int i = 0;i<32;i++){
		dw_write(&priv_slave[gindex_slave], DW_SPI_DR, 0xCC + i);
	}

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuffer, 1, buf, len, 1) != 0)
	{
		printf("spi read fail!!!\n");
		return -1;
	} else {
		printf("spi read test success!!!\n");
	}
	spi_enable_chip(&priv_slave[gindex_slave], 0);//clean slave tx buf
	return 0;
}

int spi_write_test(uint8_t* buf, uint32_t len)
{
	u8 cmdbuffer[4];
	cmdbuffer[0] = DW_SPI_DR;

	spi_enable_chip(&priv_slave[gindex_slave], 1);

	dw_write(&priv_slave[gindex_slave], DW_SPI_DR, 0x01);
	dw_write(&priv_slave[gindex_slave], DW_SPI_DR, 0x02);

	dw_read(&priv_slave[gindex_slave], DW_SPI_DR);

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuffer, 1, buf, len, 0) != 0)
	{
		printf("spi write fail!!!\n");
		return -1;
	} else {
		dw_read(&priv_slave[gindex_slave], DW_SPI_DR);
		dw_read(&priv_slave[gindex_slave], DW_SPI_DR);
		dw_read(&priv_slave[gindex_slave], DW_SPI_DR);
		printf("spi write test success!!!\n");
	}
	spi_enable_chip(&priv_slave[gindex_slave], 0);//clean slave tx buf
	return 0;
}

/* Restart the controller, disable all interrupts, clean rx fifo */
static void spi_slave_hw_init(struct dw_spi_priv *priv_t)
{
	spi_enable_chip(priv_t, 0);
	dw_write(priv_t, DW_SPI_IMR, 0x0);
	spi_enable_chip(priv_t, 1);

	/*
	 * Try to detect the FIFO depth if not set by interface driver,
	 * the depth could be from 2 to 256 from HW spec
	 */
	if (!priv_t->fifo_len) {
		u32 fifo;

		for (fifo = 1; fifo < 256; fifo++) {
			dw_write(priv_t, DW_SPI_TXFLTR, fifo);
			if (fifo != dw_read(priv_t, DW_SPI_TXFLTR))
				break;
		}

		priv_t->fifo_len = (fifo == 1) ? 0 : fifo;
		dw_write(priv_t, DW_SPI_TXFLTR, 0);
	}
	printf("%s: fifo_len=%d\n", __func__, priv_t->fifo_len);
}


static void spi_slave_regconfig(struct dw_spi_priv *priv_t)
{
	u32 cr0 = 0;

	cr0 = (priv_t->bits_per_word - 1) | (priv_t->type << SPI_FRF_OFFSET) |
		  ((((priv_t->mode & SPI_CPOL) ? 1 : 0) << SPI_SCOL_OFFSET) |
		   (((priv_t->mode & SPI_CPHA) ? 1 : 0) << SPI_SCPH_OFFSET))|
		  (priv_t->tmode << SPI_TMOD_OFFSET)|(priv_t->slvoe << SPI_SLVOE_OFFSET);

	cr0 &= ~SPI_TMOD_MASK;
	cr0 |= (priv_t->tmode << SPI_TMOD_OFFSET);

	/*Disable controller before writing control registers */
	spi_enable_chip(priv_t, 0);

	/* Reprogram cr0 only if changed */
	if (dw_read(priv_t, DW_SPI_CTRL0) != cr0)
		dw_write(priv_t, DW_SPI_CTRL0, cr0);

	spi_enable_chip(priv_t, 1);
}

int spi_slave_init(int index)
{
	gindex_slave = index;

	priv_slave[index].regs = (void *)(uintptr_t)DW_SPI_SLAVE_REG_BASE(index);
	priv_slave[index].bits_per_word = 8;
	priv_slave[index].type = SPI_FRF_SPI;
	priv_slave[index].mode = 3;
	priv_slave[index].tmode = SPI_TMOD_TR;
	priv_slave[index].clk_div = 2;
	//priv_slave[index].cs = 0;
	priv_slave[index].slvoe = 0;

	spi_slave_hw_init(&priv_slave[index]);
	spi_slave_regconfig(&priv_slave[index]);
	return 0;
}

int spi_test()
{
	uint8_t buf[1024];
	uint8_t src[1024];
	int i;
	uint8_t reg_status;

	src[0] = 0x77;

	spi_init(0);
	spi_setcs(0);

	if(spi_slave_init(0) != 0)
	{
		return -1;
	}
	if(spi_read_test(buf, 1) != 0)
	{
		return -1;
	}
	if(spi_write_test(src, 1) != 0)
	{
		return -1;
	}

	return 0;
}

