#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <target/cmdline.h>
#include "../../dw/designware_spi.h"

#define READ_PARAMETER_CMD	  0x5A
#define READ_FLASHID_CMD	  0x9f
#define READ_STATUSREG_CMD	  0x05
#define READ_FLAG_CMD		  0x70
#define ENTER_4B_CMD		  0xb7
#define READ_CMD			  0x03
#define WREN_CMD			  0x06
#define SECTOR_ERASE_4K_CMD   0x20
#define BLOCK_ERASE_64K_CMD   0xD8
#define PAGE_WRITE_CMD		  0x2
#define CHIP_ERASE_CMD		  0x60
#define DIE_ERASE_CMD		  0xC4
#define REL_DP_PWR_DWN_CMD	  0xAB	/* Release Deep power down mode */
#define STATUS_BUSY_MASK	  0x01
#define STATUS_WR_EN_MASK	  0x02

#define SIZE_4K  (uint32_t)(4 * 1024)
#define SIZE_64K (uint32_t)(64 * 1024)

#define CMDBUF(cmdbuf, cmd, off) do { \
				cmdbuf[0] = cmd; \
				if (off != -1) { \
				cmdbuf[3] = off >> 24; \
				cmdbuf[2] = off >> 16; \
				cmdbuf[1] = off >> 8; \
				} \
		} while (0)

/*
 * Reads any register of SPI NOR flash device. read_reg_cmd is used to
 * specify which register to read.
 */
int spinor_readreg(UINT8 readreg_cmd, UINT8 *status_result)
{

	uint8_t cmdbuf[4] = {readreg_cmd};
	uint8_t recbuf[4] = {0};
	CMDBUF(cmdbuf, cmdbuf[0], -1);

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuf, 1, recbuf, 1, 1) != 0)
	{
		printf("read reg fail!!!\n");
		return -1;
	}
	*status_result = recbuf[0];

	return 0;
}

int spinor_wren()
{
	uint8_t cmdbuf[4];
	uint8_t recbuf[4];
	uint8_t reg_status;
	uint8_t count;

	cmdbuf[0] = WREN_CMD;
	CMDBUF(cmdbuf, cmdbuf[0], -1);

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuf, 1, recbuf, 1, 1) != 0)
		return -1;

	for(count=0;count<5;count++)
	{
		if(spinor_readreg(READ_STATUSREG_CMD, &reg_status) != 0 || count == 4)
		{
			printf("write enable fail!!!\n");
			return -1;
		}
		if((reg_status & STATUS_WR_EN_MASK) == STATUS_WR_EN_MASK)
			break;
	}

	return 0;
}

int spinor_info()
{
	uint8_t cmdbuf[4];
	uint8_t databuf[4];

	cmdbuf[0] = READ_FLASHID_CMD;
	CMDBUF(cmdbuf, cmdbuf[0], -1);

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuf, 1, databuf, 3, 1) != 0)
	{
		printf("get spinor info fail!!!\n");
		return -1;
	}
	printf("Manufacturer ID: 0x");
	int i;
	for (i = 0; i < 3; i++)
	{
		printf("%x", databuf[i]);
	}
	printf("\n");
	return 0;
}

int spinor_release_powerdown()
{
	uint8_t cmdbuf[4];
	uint8_t recbuf[4];

	cmdbuf[0] = REL_DP_PWR_DWN_CMD;

	CMDBUF(cmdbuf, cmdbuf[0], -1);

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuf, 1, recbuf, 1, 1) != 0)
	{
		printf("release power down fail!!!\n");
		return -1;
	}

	return 0;
}

int spinor_init()
{
	uint8_t cmdbuf[4];
	uint8_t recbuf[4];
	uint8_t reg_status;

	if(spinor_wren() != 0)
		goto close;

	if(spinor_info() != 0)
		goto close;

	if(spinor_release_powerdown() != 0)
		goto close;

	return 0;

close:
	return -1;
}

int spinor_page_read(uint32_t off, void *buf)
{
	uint8_t cmdbuf[4];

	cmdbuf[0] = READ_CMD;
	CMDBUF(cmdbuf, cmdbuf[0], off);

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuf, 4, buf, 256, 1) != 0)
	{
		printf("page read fail!!!\n");
		return -1;
	}
	return 0;
}

int spinor_read(uint32_t address, void *buf, uint32_t size)
{
	uint32_t  startpage, endpage;
	uint32_t  pagecount;
	uint32_t  pagesize = 256;
	startpage = address / pagesize;
	endpage = (address + size) / pagesize;

	if(size % pagesize)
		endpage++;

	for (pagecount = 0; pagecount < endpage - startpage; pagecount ++)
	{
		if ( spinor_page_read(address, buf) != 0)
		{
			printf("spinor read fail!!!\n");
			return -1;
		}
		address += pagesize;
		buf += pagesize;
	}

	return 0;
}

int wait_operation_done()
{
	uint8_t reg_status;
	uint8_t count;

	while(1)
	{
		if(spinor_readreg(READ_STATUSREG_CMD, &reg_status) != 0)
			return -1;
		if((reg_status & STATUS_BUSY_MASK) == 0x0)
			break;
	}

	if(spinor_readreg(READ_FLAG_CMD, &reg_status) != 0)
		return -1;

	return 0;
}

int spinor_page_erase(uint32_t off, uint32_t pagesize)
{
	if ((pagesize != SIZE_4K) && (pagesize != SIZE_64K))
		return -1;
	if (off & (pagesize - 1))
		return -1;

	uint8_t cmdbuf[4];
	uint8_t recbuf[4];

	switch(pagesize)
	{
		case SIZE_4K:
			cmdbuf[0] = SECTOR_ERASE_4K_CMD;
			break;
		case SIZE_64K:
			cmdbuf[0] = BLOCK_ERASE_64K_CMD;
			break;
	}
	CMDBUF(cmdbuf, cmdbuf[0], off);

	spinor_wren();

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuf, 4, recbuf, 1, 1) != 0)
	{
		printf("page erase fail!!!\n");
		return -1;
	}
	wait_operation_done();

	return 0;
}

int spinor_erase(uint32_t address, uint32_t size)
{
	uint32_t  startpage, endpage;
	uint32_t  pagecount;
	uint32_t  pagesize = SIZE_4K;
	startpage = address / pagesize;
	endpage = (address + size) / pagesize;

	if(size % pagesize)
		endpage++;

	for (pagecount = 0; pagecount < endpage - startpage; pagecount ++)
	{
		if (spinor_page_erase(address, SIZE_4K) != 0)
		{
			printf("spinor erase fail!!!\n");
			return -1;
		}
		address += SIZE_4K;
	}

	return 0;
}

int spinor_chiperase()
{
	uint8_t cmdbuf[4];
	uint8_t recbuf[4];

	cmdbuf[0] = CHIP_ERASE_CMD;

	CMDBUF(cmdbuf, cmdbuf[0], -1);

	spinor_wren();

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuf, 1, recbuf, 1, 1) != 0)
	{
		printf("chip erase fail!!!\n");
		return -1;
	}
	wait_operation_done();

	return 0;
}

int spinor_page_write(uint32_t off, uint8_t* src)
{
	if (off & (255))
		return -1;

	uint8_t cmdbuf[4];

	cmdbuf[0] = PAGE_WRITE_CMD;

	CMDBUF(cmdbuf, cmdbuf[0], off);

	spinor_wren();

	if (dw_spi_transfer_one_message(&priv[gindex], cmdbuf, 4, src, 256, 0) != 0)
	{
		printf("page write fail!!!\n");
		return -1;
	}
	wait_operation_done();

	return 0;
}

int spinor_write(uint32_t address, void *buffer, uint32_t size)
{
	uint32_t  pagesize = 256;
	uint32_t  startpage, endpage;
	uint32_t  pagecount;
	uint8_t*  bufferaddr;

	startpage = address / pagesize;
	endpage = (address + size) / pagesize;
	bufferaddr = (uint8_t* )buffer;

	if(size % pagesize)
	  endpage++;

	for (pagecount = 0; pagecount < endpage - startpage; pagecount ++)
	{
		if(spinor_page_write(address, bufferaddr) != 0)
		{
			printf("spinor write fail!!!\n");
			return -1;
		}
		address += pagesize;
		bufferaddr += pagesize;
	}
	return 0;
}

int do_spinor(int argc, char *argv[])
{
	int ret = 0;
	void* mem_addr = NULL;
	uint32_t flash_addr;
	uint32_t size;

	if (argc < 2)
		return -EUSAGE;

	if (argv[1][0] == 'i') {
		ret = spinor_init();

		if (ret != 0) {
			printf("spinor flash init failed! \n");
		} else {
			printf("spinor flash has been initialized! \n");
		}
	}

	if (argv[1][0] == 'r') {
		flash_addr = (uint32_t)strtoul(argv[2], NULL, 0);
		mem_addr = (void*)strtoul(argv[3], NULL, 0);
		size = strtoul(argv[4], NULL, 0);
		ret = spinor_read(flash_addr, mem_addr, size);

		if(ret != 0) {
			printf("spinor read operation fail! \n");
		} else {
			printf("spinor read operation success! \n");
		}
	}

	if (argv[1][0] == 'w') {

		flash_addr = (uint32_t)strtoul(argv[2], NULL, 0);
		mem_addr = (void*)strtoul(argv[3], NULL, 0);
		size = strtoul(argv[4], NULL, 0);

		ret = spinor_write(flash_addr, mem_addr, size);

		if( ret != 0)
		{
			printf("spinor write operation fail! \n");
		} else {
			printf("spinor write operation success! \n");
		}
	}

	if (argv[1][0] == 'e') {

		if (argv[2][0] == 'c') {
			ret = spinor_chiperase();
		} else {
			flash_addr = (uint32_t)strtoul(argv[2], NULL, 0);
			size = strtoul(argv[3], NULL, 0);
			ret = spinor_erase(flash_addr, size);
		}
		if(ret != 0){
			printf("spinor erase operation fail! \n");
		} else {
			printf("spinor erase operation success! \n");
		}
	}
	return ret;
}

MK_CMD(spinor, do_spinor, "use spi master to read/write spinor flash(w25q32)",
	"\n"
	" spinor {init | i}\n"
	"	-Init flash\n"
	" spinor {read | r} flashaddr memaddr size\n"
	"	-Read {size} bytes data from {flashaddr} to {memaddr}\n"
	" spinor {write | w} flashaddr memaddr size\n"
	"	-Write {size} bytes to {flashaddr} from {memaddr}\n"
	" spinor {erase | e} flashaddr size\n"
	"	-Erase {size} bytes data from {addr}\n"
	" spinor {erase | e} chip\n"
	"	-Erase the chip\n"
);

