// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2008, Freescale Semiconductor, Inc
 * Andy Fleming
 *
 * Based vaguely on the Linux code
 */

#include <errno.h>
#include "mmc.h"
#include "mmc_private.h"

/**
 * div_u64_rem - unsigned 64bit divide with 32bit divisor with remainder
 *
 * This is commonly provided by 32bit archs to provide an optimized 64bit
 * divide.
 */
static inline u64 div_u64_rem(u64 dividend, u32 divisor, u32 *remainder)
{
	*remainder = dividend % divisor;
	return dividend / divisor;
}


/**
 * ll_entry_start() - Point to first entry of linker-generated array
 * @_type:	Data type of the entry
 * @_list:	Name of the list in which this entry is placed
 *
 * This function returns ``(_type *)`` pointer to the very first entry of a
 * linker-generated array placed into subsection of .u_boot_list section
 * specified by _list argument.
 *
 * Since this macro defines an array start symbol, its leftmost index
 * must be 2 and its rightmost index must be 1.
 *
 * Example:
 *
 * ::
 *
 *   struct my_sub_cmd *msc = ll_entry_start(struct my_sub_cmd, cmd_sub);
 */
#define ll_entry_start(_type, _list)					\
({									\
	static char start[0] __aligned(4) __attribute__((unused,	\
		section(".u_boot_list_2_"#_list"_1")));			\
	(_type *)&start;						\
})

/**
 * ll_entry_end() - Point after last entry of linker-generated array
 * @_type:	Data type of the entry
 * @_list:	Name of the list in which this entry is placed
 *		(with underscores instead of dots)
 *
 * This function returns ``(_type *)`` pointer after the very last entry of
 * a linker-generated array placed into subsection of .u_boot_list
 * section specified by _list argument.
 *
 * Since this macro defines an array end symbol, its leftmost index
 * must be 2 and its rightmost index must be 3.
 *
 * Example:
 *
 * ::
 *
 *   struct my_sub_cmd *msc = ll_entry_end(struct my_sub_cmd, cmd_sub);
 */
#define ll_entry_end(_type, _list)					\
({									\
	static char end[0] __aligned(4) __attribute__((unused,		\
		section(".u_boot_list_2_"#_list"_3")));			\
	(_type *)&end;							\
})
/**
 * ll_entry_count() - Return the number of elements in linker-generated array
 * @_type:	Data type of the entry
 * @_list:	Name of the list of which the number of elements is computed
 *
 * This function returns the number of elements of a linker-generated array
 * placed into subsection of .u_boot_list section specified by _list
 * argument. The result is of an unsigned int type.
 *
 * Example:
 *
 * ::
 *
 *   int i;
 *   const unsigned int count = ll_entry_count(struct my_sub_cmd, cmd_sub);
 *   struct my_sub_cmd *msc = ll_entry_start(struct my_sub_cmd, cmd_sub);
 *   for (i = 0; i < count; i++, msc++)
 *           printf("Entry %i, x=%i y=%i\n", i, msc->x, msc->y);
 */
#define ll_entry_count(_type, _list)					\
	({								\
		_type *start = ll_entry_start(_type, _list);		\
		_type *end = ll_entry_end(_type, _list);		\
		unsigned int _ll_result = end - start;			\
		_ll_result;						\
	})



struct blk_driver *blk_driver_lookup_type(int if_type)
{
	struct blk_driver *drv = ll_entry_start(struct blk_driver, blk_driver);
	const int n_ents = ll_entry_count(struct blk_driver, blk_driver);
	struct blk_driver *entry;

	for (entry = drv; entry != drv + n_ents; entry++) {
		if (if_type == entry->if_type)
			return entry;
	}

	/* Not found */
	return NULL;
}

/**
 * get_desc() - Get the block device descriptor for the given device number
 *
 * @drv:	Legacy block driver
 * @devnum:	Device number (0 = first)
 * @descp:	Returns block device descriptor on success
 * @return 0 on success, -ENODEV if there is no such device, -ENOSYS if the
 * driver does not provide a way to find a device, or other -ve on other
 * error.
 */
static int get_desc(struct blk_driver *drv, int devnum, struct blk_desc **descp)
{
	if (drv->desc) {
		if (devnum < 0 || devnum >= drv->max_devs)
			return -ENODEV;
		*descp = &drv->desc[devnum];
		return 0;
	}
	if (!drv->get_dev)
		return -ENOSYS;

	return drv->get_dev(devnum, descp);
}


int blk_select_hwpart_devnum(enum if_type if_type, int devnum, int hwpart)
{
	struct blk_driver *drv = blk_driver_lookup_type(if_type);
	struct blk_desc *desc;
	int ret;

	if (!drv)
		return -ENOSYS;
	ret = get_desc(drv, devnum, &desc);
	if (ret)
		return ret;
	return drv->select_hwpart(desc, hwpart);
}


static ulong mmc_erase_t(struct mmc *mmc, ulong start, lbaint_t blkcnt)
{
	struct mmc_cmd cmd;
	ulong end;
	int err, start_cmd, end_cmd;

	if (mmc->high_capacity) {
		end = start + blkcnt - 1;
	} else {
		end = (start + blkcnt - 1) * mmc->write_bl_len;
		start *= mmc->write_bl_len;
	}

	if (IS_SD(mmc)) {
		start_cmd = SD_CMD_ERASE_WR_BLK_START;
		end_cmd = SD_CMD_ERASE_WR_BLK_END;
	} else {
		start_cmd = MMC_CMD_ERASE_GROUP_START;
		end_cmd = MMC_CMD_ERASE_GROUP_END;
	}

	cmd.cmdidx = start_cmd;
	cmd.cmdarg = start;
	cmd.resp_type = MMC_RSP_R1;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err)
		goto err_out;

	cmd.cmdidx = end_cmd;
	cmd.cmdarg = end;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err)
		goto err_out;

	cmd.cmdidx = MMC_CMD_ERASE;
	cmd.cmdarg = MMC_ERASE_ARG;
	cmd.resp_type = MMC_RSP_R1b;

	err = mmc_send_cmd(mmc, &cmd, NULL);
	if (err)
		goto err_out;

	return 0;

err_out:
	puts("mmc erase failed\n");
	return err;
}

#if CONFIG_IS_ENABLED(BLK)
ulong mmc_berase(struct udevice *dev, lbaint_t start, lbaint_t blkcnt)
#else
ulong mmc_berase(struct blk_desc *block_dev, lbaint_t start, lbaint_t blkcnt)
#endif
{
#if CONFIG_IS_ENABLED(BLK)
	struct blk_desc *block_dev = dev_get_uclass_platdata(dev);
#endif
	int dev_num = block_dev->devnum;
	int err = 0;
	u32 start_rem, blkcnt_rem;
	struct mmc *mmc = find_mmc_device(dev_num);
	lbaint_t blk = 0, blk_r = 0;
	int timeout = 1000;

	if (!mmc)
		return -1;

	err = blk_select_hwpart_devnum(IF_TYPE_MMC, dev_num,
				       block_dev->hwpart);
	if (err < 0)
		return -1;

	/*
	 * We want to see if the requested start or total block count are
	 * unaligned.  We discard the whole numbers and only care about the
	 * remainder.
	 */
	err = div_u64_rem(start, mmc->erase_grp_size, &start_rem);
	err = div_u64_rem(blkcnt, mmc->erase_grp_size, &blkcnt_rem);
	if (start_rem || blkcnt_rem)
		printf("\n\nCaution! Your devices Erase group is 0x%x\n"
		       "The erase range would be change to "
		       "0x" LBAF "~0x" LBAF "\n\n",
		       mmc->erase_grp_size, start & ~(mmc->erase_grp_size - 1),
		       ((start + blkcnt + mmc->erase_grp_size)
		       & ~(mmc->erase_grp_size - 1)) - 1);

	while (blk < blkcnt) {
		if (IS_SD(mmc) && mmc->ssr.au) {
			blk_r = ((blkcnt - blk) > mmc->ssr.au) ?
				mmc->ssr.au : (blkcnt - blk);
		} else {
			blk_r = ((blkcnt - blk) > mmc->erase_grp_size) ?
				mmc->erase_grp_size : (blkcnt - blk);
		}
		err = mmc_erase_t(mmc, start + blk, blk_r);
		if (err)
			break;

		blk += blk_r;

		/* Waiting for the ready status */
		if (mmc_send_status(mmc, timeout))
			return 0;
	}

	return blk;
}

ulong mmc_write_blocks(struct mmc *mmc, lbaint_t start,
		lbaint_t blkcnt, const void *src)
{
	struct mmc_cmd cmd;
	struct mmc_data data;
	int timeout = 1000;

	if ((start + blkcnt) > mmc_get_blk_desc(mmc)->lba) {
		printf("MMC: block number 0x" LBAF " exceeds max(0x" LBAF ")\n",
		       start + blkcnt, mmc_get_blk_desc(mmc)->lba);
		return 0;
	}

	if (blkcnt == 0)
		return 0;
	else if (blkcnt == 1)
		cmd.cmdidx = MMC_CMD_WRITE_SINGLE_BLOCK;
	else
		cmd.cmdidx = MMC_CMD_WRITE_MULTIPLE_BLOCK;

	if (mmc->high_capacity)
		cmd.cmdarg = start;
	else
		cmd.cmdarg = start * mmc->write_bl_len;

	cmd.resp_type = MMC_RSP_R1;

	data.src = src;
	data.blocks = blkcnt;
	data.blocksize = mmc->write_bl_len;
	data.flags = MMC_DATA_WRITE;

	if (mmc_send_cmd(mmc, &cmd, &data)) {
		printf("mmc write failed\n");
		return 0;
	}

	/* SPI multiblock writes terminate using a special
	 * token, not a STOP_TRANSMISSION request.
	 */
	if (!mmc_host_is_spi(mmc) && blkcnt > 1) {
		cmd.cmdidx = MMC_CMD_STOP_TRANSMISSION;
		cmd.cmdarg = 0;
		cmd.resp_type = MMC_RSP_R1b;
		if (mmc_send_cmd(mmc, &cmd, NULL)) {
			printf("mmc fail to send stop cmd\n");
			return 0;
		}
	}

	/* Waiting for the ready status */
	if (mmc_send_status(mmc, timeout))
		return 0;

	return blkcnt;
}

#if CONFIG_IS_ENABLED(BLK)
ulong mmc_bwrite(struct udevice *dev, lbaint_t start, lbaint_t blkcnt,
		 const void *src)
#else
ulong mmc_bwrite(struct blk_desc *block_dev, lbaint_t start, lbaint_t blkcnt,
		 const void *src)
#endif
{
#if CONFIG_IS_ENABLED(BLK)
	struct blk_desc *block_dev = dev_get_uclass_platdata(dev);
#endif
	int dev_num = block_dev->devnum;
	lbaint_t cur, blocks_todo = blkcnt;
	int err;

	struct mmc *mmc = find_mmc_device(dev_num);
	if (!mmc)
		return 0;

	err = blk_select_hwpart_devnum(IF_TYPE_MMC, dev_num, block_dev->hwpart);
	if (err < 0)
		return 0;

	if (mmc_set_blocklen(mmc, mmc->write_bl_len))
		return 0;

	do {
		cur = (blocks_todo > mmc->cfg->b_max) ?
			mmc->cfg->b_max : blocks_todo;
		if (mmc_write_blocks(mmc, start, cur, src) != cur)
			return 0;
		blocks_todo -= cur;
		start += cur;
		src += cur * mmc->write_bl_len;
	} while (blocks_todo > 0);

	return blkcnt;
}
