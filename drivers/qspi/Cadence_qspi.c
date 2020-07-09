#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <asm/memory.h>
#include <target/spi.h>
#include <target/cmdline.h>
#include "Cadence_qspi.h"

#define CQSPI_STIG_READ			0
#define CQSPI_STIG_WRITE		1
#define CQSPI_INDIRECT_READ		2
#define CQSPI_INDIRECT_WRITE	3

static struct cadence_spi_platdata cdns_spi_host;

static int cadence_spi_xfer(struct cadence_spi_platdata *plat, void *cmd_buf, int cmd_len,
								const void *dout, void *din, int datalen)
{
	int cs = 0;
	int err = 0;
	int mode = 0;

	/* Set Chip select */
  	cadence_qspi_apb_chipselect(plat->regbase, cs, plat->is_decoded_cs);

	if (din) {
		if (!CQSPI_IS_ADDR(cmd_len))
			mode = CQSPI_STIG_READ;
		else
			mode = CQSPI_INDIRECT_READ;
	} else {
		if (!CQSPI_IS_ADDR(cmd_len))
			mode = CQSPI_STIG_WRITE;
		else
			mode = CQSPI_INDIRECT_WRITE;
	}

	switch(mode) {
	case CQSPI_STIG_READ:
		err = cadence_qspi_apb_command_read(plat->regbase, cmd_len, cmd_buf, datalen, din);
		break;
	case CQSPI_STIG_WRITE:
		err = cadence_qspi_apb_command_write(plat->regbase, cmd_len, cmd_buf, datalen, dout);
		break;
	case CQSPI_INDIRECT_READ:
		err = cadence_qspi_apb_indirect_read_setup(plat, cmd_len, SPI_RX_QUAD, cmd_buf);
		if (!err) {
			err = cadence_qspi_apb_indirect_read_execute(plat, datalen, din);
		}
		break;
	case CQSPI_INDIRECT_WRITE:
		err = cadence_qspi_apb_indirect_write_setup(plat, cmd_len, 0, cmd_buf);
		if (!err) {
			err = cadence_qspi_apb_indirect_write_execute(plat, datalen, dout);
		}
		break;
	default:
		err = -1;
		break;
	}
	return err;
}


static int qspi_controller_init(struct cadence_spi_platdata *plat)
{

	plat->regbase = (void *)(uintptr_t)QSPI_APB_REG_BASE;
	plat->ahbbase = (void *)(uintptr_t)QSPI_AHB_REG_BASE;
	plat->fifo_depth = 128;
	plat->fifo_width = 4;
	plat->trigger_address = 0x0000f000;
	cadence_qspi_apb_controller_init(plat);
	return 0;
}

int cmd_qspi(int argc, char *argv[]){

	int ret = -1;
	int dma_enable = 0;
	int singlebyte, burstbyte;

	if (argc < 2)
		return -EUSAGE;

	if (!strcmp("init", argv[1])) {
		ret = qspi_controller_init(&cdns_spi_host);
	}

	if (!strcmp("read", argv[1])) {
		void *cmd_buf = (void *)strtoul(argv[2], NULL, 0);
		uint32_t cmd_len = strtoul(argv[3], NULL, 0);
		void *din = (void *)strtoul(argv[4], NULL, 0);
		uint32_t datalen = strtoul(argv[5], NULL, 0);
		ret = cadence_spi_xfer(&cdns_spi_host, cmd_buf, cmd_len, NULL, din, datalen);
	}
	if (!strcmp("write", argv[1])) {
		void *cmd_buf = (void *)strtoul(argv[2], NULL, 0);
		uint32_t cmd_len = strtoul(argv[3], NULL, 0);
		void *dout = (void *)strtoul(argv[4], NULL, 0);
		uint32_t datalen = strtoul(argv[5], NULL, 0);
		ret = cadence_spi_xfer(&cdns_spi_host, cmd_buf, cmd_len, dout, NULL, datalen);
	}
	return ret;
}


MK_CMD(qspi, cmd_qspi, "use cadence qspi master to read/write flash\n",
	"qspi init\n"
	"	- QSPI Controller initialization.\n"
	"qspi read cmdbuf cmdlen databuf datalen\n"
	"	- send read command to flash, and then read {datalen} data from it to {databuf}.\n"
	"qspi write cmdbuf cmdlen databuf datalen\n"
	"	- send write command to flash, and then write {datalen} data from {databuf} to it.\n"
);


