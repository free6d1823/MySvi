/*
 * Copyright (c) 2019, SiEngine. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <target/cmdline.h>
#include <target/compiler.h>
#include <asm/memory.h>
#include "mmc.h"
#include "dw_emmc/dw_mmc.h"

#define DESC_SIZE 0x1000
static uintptr_t desc_buff[DESC_SIZE / sizeof(DESC_SIZE)] __aligned(1024);

static void se1000_emmc_reset(void)
{
	INFO("VDK: Skipping eMMC Reset.\n");
}

static void se1000_emmc_init(void)
{
	dw_mmc_params_t params;
	struct mmc_device_info info;

	memset(&params, 0, sizeof(dw_mmc_params_t));
	params.reg_base = EMMC_REG_BASE;
	params.desc_base = EMMC_DESC_BASE;
	params.desc_size = 1 << 20;
	params.clk_rate = 24 * 1000 * 1000;
	params.bus_width = MMC_BUS_WIDTH_8;
	params.flags = MMC_FLAG_CMD23;
	info.mmc_dev_type = MMC_IS_EMMC;

	dw_mmc_init(&params, &info);
}

int do_mmc(int argc, char *argv[]){

	if (argc < 2)
        return -EUSAGE;

	if (!strcmp(argv[1], "init")){
		se1000_emmc_init();
	}


	if (!strcmp(argv[1], "read")){
		int lba = strtoul(argv[2], NULL, 10);
		uintptr_t buf = strtoul(argv[3], NULL, 16);
		size_t size = strtoul(argv[4], NULL, 16);
		mmc_read_blocks(lba, buf, size);
	}

	if (!strcmp(argv[1], "write")){
		int lba = strtoul(argv[2], NULL, 10);
		uintptr_t buf = strtoul(argv[3], NULL, 16);
		size_t size = strtoul(argv[4], NULL, 16);
		mmc_write_blocks(lba, buf, size);
	}

	return 0;
}

MK_CMD(ufs, do_mmc, "mmc command",
	"mmc init\n"
	"	-mmc init and enumerate.\n"
	"mmmc read lba buf size\n"
	"	-mmc read data  to buf\n"
	"mmc write lba buf size\n"
	"	-mmc write data\n"

);

