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
#include "dw_ufs.h"
#include "ufs.h"

#define DESC_SIZE 0x1000
static uintptr_t desc_buff[DESC_SIZE / sizeof(DESC_SIZE)] __aligned(1024);

static void se1000_ufs_reset(void)
{
	INFO("VDK: Skipping UFS Reset.\n");
}

static void se1000_ufs_enum(void){
	ufs_enum();
}
static void se1000_ufs_init(void)
{
	dw_ufs_params_t ufs_params;

	memset(&ufs_params, 0, sizeof(ufs_params));
	ufs_params.reg_base = UFS0_REG_BASE;
	ufs_params.desc_base = (uintptr_t)desc_buff;
	ufs_params.desc_size = DESC_SIZE;

	if ((ufs_params.flags & UFS_FLAGS_SKIPINIT) == 0)
		se1000_ufs_reset();
	dw_ufs_init(&ufs_params);
}

int do_ufs(int argc, char *argv[]){

	if (argc < 2)
        return -EUSAGE;

	if (!strcmp(argv[1], "init")){
		se1000_ufs_init();
	}

	if (!strcmp(argv[1], "enum")){
		se1000_ufs_enum();
	}

	if (!strcmp(argv[1], "read")){
		int lun = strtoul(argv[2], NULL, 10);
		int lba = strtoul(argv[3], NULL, 10);
		uintptr_t buf = strtoul(argv[4], NULL, 16);
		size_t size = strtoul(argv[5], NULL, 16);
		ufs_read_blocks(lun, lba, buf, size);
	}

	if (!strcmp(argv[1], "write")){
		int lun = strtoul(argv[2], NULL, 10);
		int lba = strtoul(argv[3], NULL, 10);
		uintptr_t buf = strtoul(argv[4], NULL, 16);
		size_t size = strtoul(argv[5], NULL, 16);
		ufs_write_blocks(lun, lba, buf, size);
	}

	return 0;
}

MK_CMD(ufs, do_ufs, "ufs command",
	"ufs init\n"
	"	-ufs init.\n"
	"ufs enum\n"
	"	-dump LUN0~LUN31\n"
	"ufs read lun_num lba buf size\n"
	"	-ufs read adta from LUN<lun_num> to buf\n"
	"ufs write lun_num lba buf size\n"
	"	-ufs write data from buf to LUN<lun_num>\n"

);

