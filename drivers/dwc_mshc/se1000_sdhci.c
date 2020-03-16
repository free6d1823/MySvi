/*
 * Copyright (C) 2015 Siengine Corporation
 *		      Hua.shao <hua.shao@siengine.com>
 */

#include <stdio.h>
#include <std/stdlib.h>
#include <string.h>
#include <errno.h>
#include <target/cmdline.h>
#include <target/compiler.h>
#include <asm/memory.h>
#include <errno.h>
#include "sdhci.h"
#include "mmc.h"
#include "mmc_private.h"

#define ATMEL_SDHC_MIN_FREQ	400000
#define ATMEL_SDHC_GCK_RATE	240000000

static int curr_device = 0;

enum command_ret_t {
	CMD_RET_SUCCESS,	/* 0 = Success */
	CMD_RET_FAILURE,	/* 1 = Failure */
	CMD_RET_USAGE = -1,	/* Failure, please report 'usage' error */
};

static int do_mmc_init()
{
        struct mmc *mmc;
        u32 val = 0;
        int ret;
        mmc = find_mmc_device(curr_device);
        if (!mmc) {
                printf("no mmc device at slot %x\n", curr_device);
                return CMD_RET_FAILURE;
        }
        ret = mmc_set_dsr(mmc, val);
        printf("set dsr %s\n", (!ret) ? "OK, force rescan" : "ERROR");
        if (!ret) {
                mmc->has_init = 0;
                if (mmc_init(mmc))
                        return CMD_RET_FAILURE;
                else
                        return CMD_RET_SUCCESS;
        }
        return ret;
}

size_t se1000_mmc_read_blocks(int lba, uintptr_t buf, size_t blkcnt)
{
	u32 val = 0;
	int ret;
	u32 cur, blocks_todo = blkcnt;


	if (blkcnt == 0)
		return 0;

	struct mmc *mmc = find_mmc_device(curr_device);
	if (!mmc) {
		pr_debug("no mmc device at slot %x\n", curr_device);
		return CMD_RET_FAILURE;
	}

	if (mmc_init(mmc)) {
		pr_debug("%s init failed\n", IS_SD(mmc) ? "SD" : "MMC");
		return 0;
	}

	if (mmc_set_blocklen(mmc, mmc->read_bl_len)) {
		pr_debug("%s: Failed to set blocklen\n", __func__);
		return 0;
	}

	do {
		cur = (blocks_todo > mmc->cfg->b_max) ?
			mmc->cfg->b_max : blocks_todo;
		if (mmc_read_blocks(mmc, (void *)buf, lba, cur) != cur) {
			pr_debug("%s: Failed to read blocks\n", __func__);
			return 0;
		}
		blocks_todo -= cur;
		lba += cur;
		buf += cur * mmc->read_bl_len;
	} while (blocks_todo > 0);

     return blkcnt;
}

size_t se1000_mmc_write_blocks(int lba, uintptr_t buf, size_t blkcnt)
{
	u32 val = 0;
	int ret;
	u32 cur, blocks_todo = blkcnt;

	if (blkcnt == 0)
                return 0;

	struct mmc *mmc = find_mmc_device(curr_device);
	if (!mmc) {
		pr_debug("no mmc device at slot %x\n", curr_device);
		return CMD_RET_FAILURE;
	}
	if (mmc_init(mmc)) {
		pr_debug("%s init failed\n", IS_SD(mmc) ? "SD" : "MMC");
		return 0;
	}
	if (mmc_set_blocklen(mmc, mmc->write_bl_len))
		return 0;

	do {
		cur = (blocks_todo > mmc->cfg->b_max) ?
			mmc->cfg->b_max : blocks_todo;
		if (mmc_write_blocks(mmc, lba, blkcnt, (void *)buf) != cur)
			return 0;
		blocks_todo -= cur;
		lba += cur;
		buf += cur * mmc->write_bl_len;
	} while (blocks_todo > 0);

	return blkcnt;
}

int se1000_sdhci_init()
{
        int ret;
	struct sdhci_host *host;
	u32 max_clk, min_clk = ATMEL_SDHC_MIN_FREQ;

	host = (struct sdhci_host *)calloc(1, sizeof(struct sdhci_host));
	if (!host) {
		printf("%s: sdhci_host calloc failed\n", __func__);
		return -ENOMEM;
	}

	host->name = "se1000_sdhci";
	host->ioaddr = (void *)SDHCI_REG_BASE;
	host->quirks = SDHCI_QUIRK_WAIT_SEND_CMD;
	max_clk = ATMEL_SDHC_MIN_FREQ * 3;
	if (!max_clk) {
		printf("%s: Failed to get the proper clock\n", __func__);
		free(host);
		return -ENODEV;
	}
	host->max_clk = max_clk;
	mmc_initialize();

	add_sdhci(host, 0, min_clk);
        ret = do_mmc_init();
        printf("se1000_sdhci_init, ret = %d\n",ret );

	return 0;
}


int do_sdhci(int argc, char *argv[]){

	if (argc < 2)
        return -EUSAGE;

	if (!strcmp(argv[1], "init")){
		se1000_sdhci_init();
	}

	if (!strcmp(argv[1], "read")){
		int lba = strtoul(argv[2], NULL, 10);
		uintptr_t buf = strtoul(argv[3], NULL, 16);
		size_t size = strtoul(argv[4], NULL, 16);
		se1000_mmc_read_blocks(lba, buf, size);
	}

	if (!strcmp(argv[1], "write")){
		int lba = strtoul(argv[2], NULL, 10);
		uintptr_t buf = strtoul(argv[3], NULL, 16);
		size_t size = strtoul(argv[4], NULL, 16);
		se1000_mmc_write_blocks(lba, buf, size);
	}
	return 0;
}
MK_CMD(sdhci, do_sdhci, "sdhci command",
	"sdhci init\n"
	"	-sdhci init and enumerate.\n"
	"sdhci read lba buf size\n"
	"	-sdhci read data  to buf\n"
	"sdhci write lba buf size\n"
	"	-sdhci write data\n"

);

