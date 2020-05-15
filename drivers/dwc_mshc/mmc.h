/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2008,2010 Freescale Semiconductor, Inc
 * Andy Fleming
 *
 * Based (loosely) on the Linux code
 */

#ifndef _MMC_H_
#define _MMC_H_
#include <target/utils.h>
#include <target/list.h>
#include <target/heap.h>
#include <target/bitops.h>
#include <target/delay.h>
#include <target/heap_generic.h>
#include <std/stdbool.h>
#include <std/string.h>
#include <std/endian.h>
#include <stdio.h>

#ifdef CONFIG_SYS_64BIT_LBA
typedef uint64_t lbaint_t;
#define LBAFlength "ll"
#else
typedef ulong lbaint_t;
#define LBAFlength "l"
#endif

#define __be32_to_cpu(x) be32toh(x)
#define be32_to_cpu(x) be32toh(x)
#define LBAF "%" LBAFlength "x"

#define pr_warn printf
#define pr_debug debug
#define pr_err printf
#define pr_info printf

#define BLK_VEN_SIZE		40
#define BLK_PRD_SIZE		20
#define BLK_REV_SIZE		8


#define ROUND(a,b)		(((a) + (b) - 1) & ~((b) - 1))
#define PAD_COUNT(s, pad) (((s) - 1) / (pad) + 1)
#define PAD_SIZE(s, pad) (PAD_COUNT(s, pad) * pad)
#define ALLOC_ALIGN_BUFFER_PAD(type, name, size, align, pad)		\
	char __##name[ROUND(PAD_SIZE((size) * sizeof(type), pad), align)  \
		      + (align - 1)];					\
									\
	type *name = (type *)ALIGN((uintptr_t)__##name, align)
#define ALLOC_ALIGN_BUFFER(type, name, size, align)		\
	ALLOC_ALIGN_BUFFER_PAD(type, name, size, align, 1)
#define ALLOC_CACHE_ALIGN_BUFFER_PAD(type, name, size, pad)		\
	ALLOC_ALIGN_BUFFER_PAD(type, name, size, ARCH_DMA_MINALIGN, pad)
#define ALLOC_CACHE_ALIGN_BUFFER(type, name, size)			\
	ALLOC_ALIGN_BUFFER(type, name, size, ARCH_DMA_MINALIGN)

#define memalign heap_aligned_alloc
#define malloc(s) heap_aligned_alloc(ARCH_DMA_MINALIGN, s)
#define ARCH_DMA_MINALIGN 16
#define calloc _calloc
#define free {}

static inline void *_calloc(size_t nmemb, size_t size){
        void *p = malloc(nmemb * size);
        if (p) memset(p, 0, nmemb * size);
        return p;
}


#define __ARG_PLACEHOLDER_1 0,
#define config_enabled(cfg) _config_enabled(cfg)
#define _config_enabled(value) __config_enabled(__ARG_PLACEHOLDER_##value)
#define __config_enabled(arg1_or_junk) ___config_enabled(arg1_or_junk 1, 0)
#define ___config_enabled(__ignored, val, ...) val

/*
 * U-Boot add-on: Helper macros to reference to different macros
 * (CONFIG_ or CONFIG_SPL_ prefixed), depending on the build context.
 */
#ifdef CONFIG_SPL_BUILD
#define _IS_SPL 1
#endif

#ifdef CONFIG_TPL_BUILD
#define _IS_TPL 1
#endif

#if defined(CONFIG_TPL_BUILD)
#define config_val(cfg) _config_val(_IS_TPL, cfg)
#define _config_val(x, cfg) __config_val(x, cfg)
#define __config_val(x, cfg) ___config_val(__ARG_PLACEHOLDER_##x, cfg)
#define ___config_val(arg1_or_junk, cfg)  \
	____config_val(arg1_or_junk CONFIG_TPL_##cfg, CONFIG_##cfg)
#define ____config_val(__ignored, val, ...) val
#else
#define config_val(cfg) _config_val(_IS_SPL, cfg)
#define _config_val(x, cfg) __config_val(x, cfg)
#define __config_val(x, cfg) ___config_val(__ARG_PLACEHOLDER_##x, cfg)
#define ___config_val(arg1_or_junk, cfg)  \
	____config_val(arg1_or_junk CONFIG_SPL_##cfg, CONFIG_##cfg)
#define ____config_val(__ignored, val, ...) val
#endif

/*
 * CONFIG_VAL(FOO) evaluates to the value of
 *  CONFIG_FOO if CONFIG_SPL_BUILD is undefined,
 *  CONFIG_SPL_FOO if CONFIG_SPL_BUILD is defined.
 */
#define CONFIG_VAL(option)  config_val(option)

/*
 * CONFIG_IS_ENABLED(FOO) evaluates to
 *  1 if CONFIG_SPL_BUILD is undefined and CONFIG_FOO is set to 'y' or 'm',
 *  1 if CONFIG_SPL_BUILD is defined and CONFIG_SPL_FOO is set to 'y' or 'm',
 *  0 otherwise.
 */
#define CONFIG_IS_ENABLED(option) \
	(config_enabled(CONFIG_VAL(option)) ||		\
	 config_enabled(CONFIG_VAL(option##_MODULE)))

#define writew __raw_writew
#define writeb __raw_writeb
#define readw __raw_readw
#define readb __raw_readb
#define MMC_RSP_48			BIT(0)
#define MMC_RSP_CMD_IDX			BIT(3)		/* response contains cmd idx */
#define MMC_RSP_PRESENT (1 << 0)

#define MMC_DATA_READ		1
#define MMC_DATA_WRITE		2
#define MMC_CMD_STOP_TRANSMISSION	12
#define MMC_CMD_SEND_STATUS		13
#define MMC_CMD_SET_BLOCKLEN		16
#define MMC_CMD_READ_SINGLE_BLOCK	17
#define MMC_CMD_READ_MULTIPLE_BLOCK	18
#define MMC_CMD_SEND_TUNING_BLOCK		19
#define MMC_CMD_SEND_TUNING_BLOCK_HS200	21
#define  SDHCI_INT_RESPONSE	BIT(0)

#define MMC_VDD_165_195		0x00000080	/* VDD voltage 1.65 - 1.95 */
#define MMC_VDD_20_21		0x00000100	/* VDD voltage 2.0 ~ 2.1 */
#define MMC_VDD_21_22		0x00000200	/* VDD voltage 2.1 ~ 2.2 */
#define MMC_VDD_22_23		0x00000400	/* VDD voltage 2.2 ~ 2.3 */
#define MMC_VDD_23_24		0x00000800	/* VDD voltage 2.3 ~ 2.4 */
#define MMC_VDD_24_25		0x00001000	/* VDD voltage 2.4 ~ 2.5 */
#define MMC_VDD_25_26		0x00002000	/* VDD voltage 2.5 ~ 2.6 */
#define MMC_VDD_26_27		0x00004000	/* VDD voltage 2.6 ~ 2.7 */
#define MMC_VDD_27_28		0x00008000	/* VDD voltage 2.7 ~ 2.8 */
#define MMC_VDD_28_29		0x00010000	/* VDD voltage 2.8 ~ 2.9 */
#define MMC_VDD_29_30		0x00020000	/* VDD voltage 2.9 ~ 3.0 */
#define MMC_VDD_30_31		0x00040000	/* VDD voltage 3.0 ~ 3.1 */
#define MMC_VDD_31_32		0x00080000	/* VDD voltage 3.1 ~ 3.2 */
#define MMC_VDD_32_33		0x00100000	/* VDD voltage 3.2 ~ 3.3 */
#define MMC_VDD_33_34		0x00200000	/* VDD voltage 3.3 ~ 3.4 */
#define MMC_VDD_34_35		0x00400000	/* VDD voltage 3.4 ~ 3.5 */
#define MMC_VDD_35_36		0x00800000	/* VDD voltage 3.5 ~ 3.6 */

#define	ECOMM		70	/* Communication error on send */
#define MMC_CAP(mode)		(1 << mode)
#define MMC_MODE_HS		(MMC_CAP(MMC_HS) | MMC_CAP(SD_HS))
#define MMC_MODE_HS_52MHz	MMC_CAP(MMC_HS_52)
#define MMC_MODE_DDR_52MHz	MMC_CAP(MMC_DDR_52)
#define MMC_MODE_HS200		MMC_CAP(MMC_HS_200)
#define MMC_MODE_HS400		MMC_CAP(MMC_HS_400)

#define MMC_MODE_8BIT		BIT(30)
#define MMC_MODE_4BIT		BIT(29)
#define MMC_MODE_1BIT		BIT(28)
#define MMC_MODE_SPI		BIT(27)
#define CONFIG_SYS_MMC_MAX_BLK_COUNT	256

#ifdef DEBUG
#define debug(fmt, args...)		\
	do {				\
		printf(fmt, ##args);	\
	} while (0)
#else
#define debug(fmt, args...)
#endif

#define	assert(x)					\
	do {						\
		if (!(x)) {				\
			BUG_ON(!(x)); 			\
			while(1);			\
		}					\
	} while (0)

#define LOG2(x) (((x & 0xaaaaaaaa) ? 1 : 0) + ((x & 0xcccccccc) ? 2 : 0) + \
		 ((x & 0xf0f0f0f0) ? 4 : 0) + ((x & 0xff00ff00) ? 8 : 0) + \
		 ((x & 0xffff0000) ? 16 : 0))

# define do_div(n,base) ({					\
	uint32_t __base = (base);				\
	uint32_t __rem;						\
	__rem = ((uint64_t)(n)) % __base;			\
	(n) = ((uint64_t)(n)) / __base;				\
	__rem;							\
 })

/*
 * Declare a new U-Boot legacy block driver. New drivers should use driver
 * model (UCLASS_BLK).
 */
#define U_BOOT_LEGACY_BLK(__name)					\
	ll_entry_declare(struct blk_driver, __name, blk_driver)


/**
 * ll_entry_declare() - Declare linker-generated array entry
 * @_type:	Data type of the entry
 * @_name:	Name of the entry
 * @_list:	name of the list. Should contain only characters allowed
 *		in a C variable name!
 *
 * This macro declares a variable that is placed into a linker-generated
 * array. This is a basic building block for more advanced use of linker-
 * generated arrays. The user is expected to build their own macro wrapper
 * around this one.
 *
 * A variable declared using this macro must be compile-time initialized.
 *
 * Special precaution must be made when using this macro:
 *
 * 1) The _type must not contain the "static" keyword, otherwise the
 *    entry is generated and can be iterated but is listed in the map
 *    file and cannot be retrieved by name.
 *
 * 2) In case a section is declared that contains some array elements AND
 *    a subsection of this section is declared and contains some elements,
 *    it is imperative that the elements are of the same type.
 *
 * 3) In case an outer section is declared that contains some array elements
 *    AND an inner subsection of this section is declared and contains some
 *    elements, then when traversing the outer section, even the elements of
 *    the inner sections are present in the array.
 *
 * Example:
 *
 * ::
 *
 *   ll_entry_declare(struct my_sub_cmd, my_sub_cmd, cmd_sub) = {
 *           .x = 3,
 *           .y = 4,
 *   };
 */
#define ll_entry_declare(_type, _name, _list)				\
	_type _u_boot_list_2_##_list##_2_##_name __aligned(4)		\
			__attribute__((unused,				\
			section(".u_boot_list_2_"#_list"_2_"#_name)))

/* Wrapper for do_div(). Doesn't modify dividend and returns
 * the result, not remainder.
 */
static inline uint64_t lldiv(uint64_t dividend, uint32_t divisor)
{
	uint64_t __res = dividend;
	do_div(__res, divisor);
	return(__res);
}

#if CONFIG_IS_ENABLED(MMC_HS200_SUPPORT)
#define MMC_SUPPORTS_TUNING
#endif
#if CONFIG_IS_ENABLED(MMC_UHS_SUPPORT)
#define MMC_SUPPORTS_TUNING
#endif

/* SD/MMC version bits; 8 flags, 8 major, 8 minor, 8 change */
#define SD_VERSION_SD	(1U << 31)
#define MMC_VERSION_MMC	(1U << 30)

#define MAKE_SDMMC_VERSION(a, b, c)	\
	((((u32)(a)) << 16) | ((u32)(b) << 8) | (u32)(c))
#define MAKE_SD_VERSION(a, b, c)	\
	(SD_VERSION_SD | MAKE_SDMMC_VERSION(a, b, c))
#define MAKE_MMC_VERSION(a, b, c)	\
	(MMC_VERSION_MMC | MAKE_SDMMC_VERSION(a, b, c))

#define EXTRACT_SDMMC_MAJOR_VERSION(x)	\
	(((u32)(x) >> 16) & 0xff)
#define EXTRACT_SDMMC_MINOR_VERSION(x)	\
	(((u32)(x) >> 8) & 0xff)
#define EXTRACT_SDMMC_CHANGE_VERSION(x)	\
	((u32)(x) & 0xff)

#define SD_VERSION_3		MAKE_SD_VERSION(3, 0, 0)
#define SD_VERSION_2		MAKE_SD_VERSION(2, 0, 0)
#define SD_VERSION_1_0		MAKE_SD_VERSION(1, 0, 0)
#define SD_VERSION_1_10		MAKE_SD_VERSION(1, 10, 0)

#define MMC_VERSION_UNKNOWN	MAKE_MMC_VERSION(0, 0, 0)
#define MMC_VERSION_1_2		MAKE_MMC_VERSION(1, 2, 0)
#define MMC_VERSION_1_4		MAKE_MMC_VERSION(1, 4, 0)
#define MMC_VERSION_2_2		MAKE_MMC_VERSION(2, 2, 0)
#define MMC_VERSION_3		MAKE_MMC_VERSION(3, 0, 0)
#define MMC_VERSION_4		MAKE_MMC_VERSION(4, 0, 0)
#define MMC_VERSION_4_1		MAKE_MMC_VERSION(4, 1, 0)
#define MMC_VERSION_4_2		MAKE_MMC_VERSION(4, 2, 0)
#define MMC_VERSION_4_3		MAKE_MMC_VERSION(4, 3, 0)
#define MMC_VERSION_4_4		MAKE_MMC_VERSION(4, 4, 0)
#define MMC_VERSION_4_41	MAKE_MMC_VERSION(4, 4, 1)
#define MMC_VERSION_4_5		MAKE_MMC_VERSION(4, 5, 0)
#define MMC_VERSION_5_0		MAKE_MMC_VERSION(5, 0, 0)
#define MMC_VERSION_5_1		MAKE_MMC_VERSION(5, 1, 0)

#define MMC_CAP(mode)		(1 << mode)
#define MMC_MODE_HS		(MMC_CAP(MMC_HS) | MMC_CAP(SD_HS))
#define MMC_MODE_HS_52MHz	MMC_CAP(MMC_HS_52)
#define MMC_MODE_DDR_52MHz	MMC_CAP(MMC_DDR_52)
#define MMC_MODE_HS200		MMC_CAP(MMC_HS_200)
#define MMC_MODE_HS400		MMC_CAP(MMC_HS_400)

#define MMC_MODE_8BIT		BIT(30)
#define MMC_MODE_4BIT		BIT(29)
#define MMC_MODE_1BIT		BIT(28)
#define MMC_MODE_SPI		BIT(27)


#define SD_DATA_4BIT	0x00040000

#define IS_SD(x)	((x)->version & SD_VERSION_SD)
#define IS_MMC(x)	((x)->version & MMC_VERSION_MMC)

#define MMC_DATA_READ		1
#define MMC_DATA_WRITE		2

#define MMC_CMD_GO_IDLE_STATE		0
#define MMC_CMD_SEND_OP_COND		1
#define MMC_CMD_ALL_SEND_CID		2
#define MMC_CMD_SET_RELATIVE_ADDR	3
#define MMC_CMD_SET_DSR			4
#define MMC_CMD_SWITCH			6
#define MMC_CMD_SELECT_CARD		7
#define MMC_CMD_SEND_EXT_CSD		8
#define MMC_CMD_SEND_CSD		9
#define MMC_CMD_SEND_CID		10
#define MMC_CMD_STOP_TRANSMISSION	12
#define MMC_CMD_SEND_STATUS		13
#define MMC_CMD_SET_BLOCKLEN		16
#define MMC_CMD_READ_SINGLE_BLOCK	17
#define MMC_CMD_READ_MULTIPLE_BLOCK	18
#define MMC_CMD_SEND_TUNING_BLOCK		19
#define MMC_CMD_SEND_TUNING_BLOCK_HS200	21
#define MMC_CMD_SET_BLOCK_COUNT         23
#define MMC_CMD_WRITE_SINGLE_BLOCK	24
#define MMC_CMD_WRITE_MULTIPLE_BLOCK	25
#define MMC_CMD_ERASE_GROUP_START	35
#define MMC_CMD_ERASE_GROUP_END		36
#define MMC_CMD_ERASE			38
#define MMC_CMD_APP_CMD			55
#define MMC_CMD_SPI_READ_OCR		58
#define MMC_CMD_SPI_CRC_ON_OFF		59
#define MMC_CMD_RES_MAN			62

#define MMC_CMD62_ARG1			0xefac62ec
#define MMC_CMD62_ARG2			0xcbaea7


#define SD_CMD_SEND_RELATIVE_ADDR	3
#define SD_CMD_SWITCH_FUNC		6
#define SD_CMD_SEND_IF_COND		8
#define SD_CMD_SWITCH_UHS18V		11

#define SD_CMD_APP_SET_BUS_WIDTH	6
#define SD_CMD_APP_SD_STATUS		13
#define SD_CMD_ERASE_WR_BLK_START	32
#define SD_CMD_ERASE_WR_BLK_END		33
#define SD_CMD_APP_SEND_OP_COND		41
#define SD_CMD_APP_SEND_SCR		51

static inline bool mmc_is_tuning_cmd(uint cmdidx)
{
	if ((cmdidx == MMC_CMD_SEND_TUNING_BLOCK_HS200) ||
	    (cmdidx == MMC_CMD_SEND_TUNING_BLOCK))
		return true;
	return false;
}

/* SCR definitions in different words */
#define SD_HIGHSPEED_BUSY	0x00020000
#define SD_HIGHSPEED_SUPPORTED	0x00020000

#define UHS_SDR12_BUS_SPEED	0
#define HIGH_SPEED_BUS_SPEED	1
#define UHS_SDR25_BUS_SPEED	1
#define UHS_SDR50_BUS_SPEED	2
#define UHS_SDR104_BUS_SPEED	3
#define UHS_DDR50_BUS_SPEED	4

#define SD_MODE_UHS_SDR12	BIT(UHS_SDR12_BUS_SPEED)
#define SD_MODE_UHS_SDR25	BIT(UHS_SDR25_BUS_SPEED)
#define SD_MODE_UHS_SDR50	BIT(UHS_SDR50_BUS_SPEED)
#define SD_MODE_UHS_SDR104	BIT(UHS_SDR104_BUS_SPEED)
#define SD_MODE_UHS_DDR50	BIT(UHS_DDR50_BUS_SPEED)

#define OCR_BUSY		0x80000000
#define OCR_HCS			0x40000000
#define OCR_S18R		0x1000000
#define OCR_VOLTAGE_MASK	0x007FFF80
#define OCR_ACCESS_MODE		0x60000000

#define MMC_ERASE_ARG		0x00000000
#define MMC_SECURE_ERASE_ARG	0x80000000
#define MMC_TRIM_ARG		0x00000001
#define MMC_DISCARD_ARG		0x00000003
#define MMC_SECURE_TRIM1_ARG	0x80000001
#define MMC_SECURE_TRIM2_ARG	0x80008000

#define MMC_STATUS_MASK		(~0x0206BF7F)
#define MMC_STATUS_SWITCH_ERROR	(1 << 7)
#define MMC_STATUS_RDY_FOR_DATA (1 << 8)
#define MMC_STATUS_CURR_STATE	(0xf << 9)
#define MMC_STATUS_ERROR	(1 << 19)

#define MMC_STATE_PRG		(7 << 9)

#define MMC_VDD_165_195		0x00000080	/* VDD voltage 1.65 - 1.95 */
#define MMC_VDD_20_21		0x00000100	/* VDD voltage 2.0 ~ 2.1 */
#define MMC_VDD_21_22		0x00000200	/* VDD voltage 2.1 ~ 2.2 */
#define MMC_VDD_22_23		0x00000400	/* VDD voltage 2.2 ~ 2.3 */
#define MMC_VDD_23_24		0x00000800	/* VDD voltage 2.3 ~ 2.4 */
#define MMC_VDD_24_25		0x00001000	/* VDD voltage 2.4 ~ 2.5 */
#define MMC_VDD_25_26		0x00002000	/* VDD voltage 2.5 ~ 2.6 */
#define MMC_VDD_26_27		0x00004000	/* VDD voltage 2.6 ~ 2.7 */
#define MMC_VDD_27_28		0x00008000	/* VDD voltage 2.7 ~ 2.8 */
#define MMC_VDD_28_29		0x00010000	/* VDD voltage 2.8 ~ 2.9 */
#define MMC_VDD_29_30		0x00020000	/* VDD voltage 2.9 ~ 3.0 */
#define MMC_VDD_30_31		0x00040000	/* VDD voltage 3.0 ~ 3.1 */
#define MMC_VDD_31_32		0x00080000	/* VDD voltage 3.1 ~ 3.2 */
#define MMC_VDD_32_33		0x00100000	/* VDD voltage 3.2 ~ 3.3 */
#define MMC_VDD_33_34		0x00200000	/* VDD voltage 3.3 ~ 3.4 */
#define MMC_VDD_34_35		0x00400000	/* VDD voltage 3.4 ~ 3.5 */
#define MMC_VDD_35_36		0x00800000	/* VDD voltage 3.5 ~ 3.6 */

#define MMC_SWITCH_MODE_CMD_SET		0x00 /* Change the command set */
#define MMC_SWITCH_MODE_SET_BITS	0x01 /* Set bits in EXT_CSD byte
						addressed by index which are
						1 in value field */
#define MMC_SWITCH_MODE_CLEAR_BITS	0x02 /* Clear bits in EXT_CSD byte
						addressed by index, which are
						1 in value field */
#define MMC_SWITCH_MODE_WRITE_BYTE	0x03 /* Set target byte to value */

#define SD_SWITCH_CHECK		0
#define SD_SWITCH_SWITCH	1

/*
 * EXT_CSD fields
 */
#define EXT_CSD_ENH_START_ADDR		136	/* R/W */
#define EXT_CSD_ENH_SIZE_MULT		140	/* R/W */
#define EXT_CSD_GP_SIZE_MULT		143	/* R/W */
#define EXT_CSD_PARTITION_SETTING	155	/* R/W */
#define EXT_CSD_PARTITIONS_ATTRIBUTE	156	/* R/W */
#define EXT_CSD_MAX_ENH_SIZE_MULT	157	/* R */
#define EXT_CSD_PARTITIONING_SUPPORT	160	/* RO */
#define EXT_CSD_RST_N_FUNCTION		162	/* R/W */
#define EXT_CSD_BKOPS_EN		163	/* R/W & R/W/E */
#define EXT_CSD_WR_REL_PARAM		166	/* R */
#define EXT_CSD_WR_REL_SET		167	/* R/W */
#define EXT_CSD_RPMB_MULT		168	/* RO */
#define EXT_CSD_ERASE_GROUP_DEF		175	/* R/W */
#define EXT_CSD_BOOT_BUS_WIDTH		177
#define EXT_CSD_PART_CONF		179	/* R/W */
#define EXT_CSD_BUS_WIDTH		183	/* R/W */
#define EXT_CSD_HS_TIMING		185	/* R/W */
#define EXT_CSD_REV			192	/* RO */
#define EXT_CSD_CARD_TYPE		196	/* RO */
#define EXT_CSD_SEC_CNT			212	/* RO, 4 bytes */
#define EXT_CSD_HC_WP_GRP_SIZE		221	/* RO */
#define EXT_CSD_HC_ERASE_GRP_SIZE	224	/* RO */
#define EXT_CSD_BOOT_MULT		226	/* RO */
#define EXT_CSD_BKOPS_SUPPORT		502	/* RO */

/*
 * EXT_CSD field definitions
 */

#define EXT_CSD_CMD_SET_NORMAL		(1 << 0)
#define EXT_CSD_CMD_SET_SECURE		(1 << 1)
#define EXT_CSD_CMD_SET_CPSECURE	(1 << 2)

#define EXT_CSD_CARD_TYPE_26	(1 << 0)	/* Card can run at 26MHz */
#define EXT_CSD_CARD_TYPE_52	(1 << 1)	/* Card can run at 52MHz */
#define EXT_CSD_CARD_TYPE_DDR_1_8V	(1 << 2)
#define EXT_CSD_CARD_TYPE_DDR_1_2V	(1 << 3)
#define EXT_CSD_CARD_TYPE_DDR_52	(EXT_CSD_CARD_TYPE_DDR_1_8V \
					| EXT_CSD_CARD_TYPE_DDR_1_2V)

#define EXT_CSD_CARD_TYPE_HS200_1_8V	BIT(4)	/* Card can run at 200MHz */
						/* SDR mode @1.8V I/O */
#define EXT_CSD_CARD_TYPE_HS200_1_2V	BIT(5)	/* Card can run at 200MHz */
						/* SDR mode @1.2V I/O */
#define EXT_CSD_CARD_TYPE_HS200		(EXT_CSD_CARD_TYPE_HS200_1_8V | \
					 EXT_CSD_CARD_TYPE_HS200_1_2V)
#define EXT_CSD_CARD_TYPE_HS400_1_8V	BIT(6)
#define EXT_CSD_CARD_TYPE_HS400_1_2V	BIT(7)
#define EXT_CSD_CARD_TYPE_HS400		(EXT_CSD_CARD_TYPE_HS400_1_8V | \
					 EXT_CSD_CARD_TYPE_HS400_1_2V)

#define EXT_CSD_BUS_WIDTH_1	0	/* Card is in 1 bit mode */
#define EXT_CSD_BUS_WIDTH_4	1	/* Card is in 4 bit mode */
#define EXT_CSD_BUS_WIDTH_8	2	/* Card is in 8 bit mode */
#define EXT_CSD_DDR_BUS_WIDTH_4	5	/* Card is in 4 bit DDR mode */
#define EXT_CSD_DDR_BUS_WIDTH_8	6	/* Card is in 8 bit DDR mode */
#define EXT_CSD_DDR_FLAG	BIT(2)	/* Flag for DDR mode */

#define EXT_CSD_TIMING_LEGACY	0	/* no high speed */
#define EXT_CSD_TIMING_HS	1	/* HS */
#define EXT_CSD_TIMING_HS200	2	/* HS200 */
#define EXT_CSD_TIMING_HS400	3	/* HS400 */

#define EXT_CSD_BOOT_ACK_ENABLE			(1 << 6)
#define EXT_CSD_BOOT_PARTITION_ENABLE		(1 << 3)
#define EXT_CSD_PARTITION_ACCESS_ENABLE		(1 << 0)
#define EXT_CSD_PARTITION_ACCESS_DISABLE	(0 << 0)

#define EXT_CSD_BOOT_ACK(x)		(x << 6)
#define EXT_CSD_BOOT_PART_NUM(x)	(x << 3)
#define EXT_CSD_PARTITION_ACCESS(x)	(x << 0)

#define EXT_CSD_EXTRACT_BOOT_ACK(x)		(((x) >> 6) & 0x1)
#define EXT_CSD_EXTRACT_BOOT_PART(x)		(((x) >> 3) & 0x7)
#define EXT_CSD_EXTRACT_PARTITION_ACCESS(x)	((x) & 0x7)

#define EXT_CSD_BOOT_BUS_WIDTH_MODE(x)	(x << 3)
#define EXT_CSD_BOOT_BUS_WIDTH_RESET(x)	(x << 2)
#define EXT_CSD_BOOT_BUS_WIDTH_WIDTH(x)	(x)

#define EXT_CSD_PARTITION_SETTING_COMPLETED	(1 << 0)

#define EXT_CSD_ENH_USR		(1 << 0)	/* user data area is enhanced */
#define EXT_CSD_ENH_GP(x)	(1 << ((x)+1))	/* GP part (x+1) is enhanced */

#define EXT_CSD_HS_CTRL_REL	(1 << 0)	/* host controlled WR_REL_SET */

#define EXT_CSD_WR_DATA_REL_USR		(1 << 0)	/* user data area WR_REL */
#define EXT_CSD_WR_DATA_REL_GP(x)	(1 << ((x)+1))	/* GP part (x+1) WR_REL */

#define R1_ILLEGAL_COMMAND		(1 << 22)
#define R1_APP_CMD			(1 << 5)

#define MMC_RSP_PRESENT (1 << 0)
#define MMC_RSP_136	(1 << 1)		/* 136 bit response */
#define MMC_RSP_CRC	(1 << 2)		/* expect valid crc */
#define MMC_RSP_BUSY	(1 << 3)		/* card may send busy */
#define MMC_RSP_OPCODE	(1 << 4)		/* response contains opcode */

#define MMC_RSP_NONE	(0)
#define MMC_RSP_R1	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R1b	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE| \
			MMC_RSP_BUSY)
#define MMC_RSP_R2	(MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC)
#define MMC_RSP_R3	(MMC_RSP_PRESENT)
#define MMC_RSP_R4	(MMC_RSP_PRESENT)
#define MMC_RSP_R5	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R6	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R7	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)

#define MMCPART_NOAVAILABLE	(0xff)
#define PART_ACCESS_MASK	(0x7)
#define PART_SUPPORT		(0x1)
#define ENHNCD_SUPPORT		(0x2)
#define PART_ENH_ATTRIB		(0x1f)

#define MMC_QUIRK_RETRY_SEND_CID	BIT(0)
#define MMC_QUIRK_RETRY_SET_BLOCKLEN	BIT(1)

enum mmc_voltage {
	MMC_SIGNAL_VOLTAGE_000 = 0,
	MMC_SIGNAL_VOLTAGE_120 = 1,
	MMC_SIGNAL_VOLTAGE_180 = 2,
	MMC_SIGNAL_VOLTAGE_330 = 4,
};

#define MMC_ALL_SIGNAL_VOLTAGE (MMC_SIGNAL_VOLTAGE_120 |\
				MMC_SIGNAL_VOLTAGE_180 |\
				MMC_SIGNAL_VOLTAGE_330)

/* Maximum block size for MMC */
#define MMC_MAX_BLOCK_LEN	512

/* The number of MMC physical partitions.  These consist of:
 * boot partitions (2), general purpose partitions (4) in MMC v4.4.
 */
#define MMC_NUM_BOOT_PARTITION	2
#define MMC_PART_RPMB           3       /* RPMB partition number */

static inline void prefetch(const void *x) {;}



/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; prefetch(pos->next), pos != (head); \
		pos = pos->next)


typedef struct {
	u8 b[16];
} efi_guid_t __attribute__((aligned(8)));

/* Interface types: */
enum if_type {
	IF_TYPE_UNKNOWN = 0,
	IF_TYPE_IDE,
	IF_TYPE_SCSI,
	IF_TYPE_ATAPI,
	IF_TYPE_USB,
	IF_TYPE_DOC,
	IF_TYPE_MMC,
	IF_TYPE_SD,
	IF_TYPE_SATA,
	IF_TYPE_HOST,
	IF_TYPE_NVME,
	IF_TYPE_EFI,
	IF_TYPE_VIRTIO,

	IF_TYPE_COUNT,			/* Number of interface types */
};

/*
 * Identifies the partition table type (ie. MBR vs GPT GUID) signature
 */
enum sig_type {
	SIG_TYPE_NONE,
	SIG_TYPE_MBR,
	SIG_TYPE_GUID,

	SIG_TYPE_COUNT			/* Number of signature types */
};

/*
 * With driver model (CONFIG_BLK) this is uclass platform data, accessible
 * with dev_get_uclass_platdata(dev)
 */
struct blk_desc {
	/*
	 * TODO: With driver model we should be able to use the parent
	 * device's uclass instead.
	 */
	enum if_type	if_type;	/* type of the interface */
	int		devnum;		/* device number */
	unsigned char	part_type;	/* partition type */
	unsigned char	target;		/* target SCSI ID */
	unsigned char	lun;		/* target LUN */
	unsigned char	hwpart;		/* HW partition, e.g. for eMMC */
	unsigned char	type;		/* device type */
	unsigned char	removable;	/* removable device */
#ifdef CONFIG_LBA48
	/* device can use 48bit addr (ATA/ATAPI v7) */
	unsigned char	lba48;
#endif
	lbaint_t	lba;		/* number of blocks */
	unsigned long	blksz;		/* block size */
	int		log2blksz;	/* for convenience: log2(blksz) */
	char		vendor[BLK_VEN_SIZE + 1]; /* device vendor string */
	char		product[BLK_PRD_SIZE + 1]; /* device product number */
	char		revision[BLK_REV_SIZE + 1]; /* firmware revision */
	enum sig_type	sig_type;	/* Partition table signature type */
	union {
		uint32_t mbr_sig;	/* MBR integer signature */
		efi_guid_t guid_sig;	/* GPT GUID Signature */
	};
#if CONFIG_IS_ENABLED(BLK)
	/*
	 * For now we have a few functions which take struct blk_desc as a
	 * parameter. This field allows them to look up the associated
	 * device. Once these functions are removed we can drop this field.
	 */
	struct udevice *bdev;
#else
	unsigned long	(*block_read)(struct blk_desc *block_dev,
				      lbaint_t start,
				      lbaint_t blkcnt,
				      void *buffer);
	unsigned long	(*block_write)(struct blk_desc *block_dev,
				       lbaint_t start,
				       lbaint_t blkcnt,
				       const void *buffer);
	unsigned long	(*block_erase)(struct blk_desc *block_dev,
				       lbaint_t start,
				       lbaint_t blkcnt);
	void		*priv;		/* driver private struct pointer */
#endif
};


/**
 * struct blk_driver - Driver for block interface types
 *
 * This provides access to the block devices for each interface type. One
 * driver should be provided using U_BOOT_LEGACY_BLK() for each interface
 * type that is to be supported.
 *
 * @if_typename:	Interface type name
 * @if_type:		Interface type
 * @max_devs:		Maximum number of devices supported
 * @desc:		Pointer to list of devices for this interface type,
 *			or NULL to use @get_dev() instead
 */
struct blk_driver {
	const char *if_typename;
	enum if_type if_type;
	int max_devs;
	struct blk_desc *desc;
	/**
	 * get_dev() - get a pointer to a block device given its number
	 *
	 * Each interface allocates its own devices and typically
	 * struct blk_desc is contained with the interface's data structure.
	 * There is no global numbering for block devices. This method allows
	 * the device for an interface type to be obtained when @desc is NULL.
	 *
	 * @devnum:	Device number (0 for first device on that interface,
	 *		1 for second, etc.
	 * @descp:	Returns pointer to the block device on success
	 * @return 0 if OK, -ve on error
	 */
	int (*get_dev)(int devnum, struct blk_desc **descp);

	/**
	 * select_hwpart() - Select a hardware partition
	 *
	 * Some devices (e.g. MMC) can support partitioning at the hardware
	 * level. This is quite separate from the normal idea of
	 * software-based partitions. MMC hardware partitions must be
	 * explicitly selected. Once selected only the region of the device
	 * covered by that partition is accessible.
	 *
	 * The MMC standard provides for two boot partitions (numbered 1 and 2),
	 * rpmb (3), and up to 4 addition general-purpose partitions (4-7).
	 * Partition 0 is the main user-data partition.
	 *
	 * @desc:	Block device descriptor
	 * @hwpart:	Hardware partition number to select. 0 means the main
	 *		user-data partition, 1 is the first partition, 2 is
	 *		the second, etc.
	 * @return 0 if OK, other value for an error
	 */
	int (*select_hwpart)(struct blk_desc *desc, int hwpart);
};

/* Driver model support */

/**
 * struct mmc_uclass_priv - Holds information about a device used by the uclass
 */
struct mmc_uclass_priv {
	struct mmc *mmc;
};


/* End of driver model support */

struct mmc_cid {
	unsigned long psn;
	unsigned short oid;
	unsigned char mid;
	unsigned char prv;
	unsigned char mdt;
	char pnm[7];
};

struct mmc_cmd {
	ushort cmdidx;
	uint resp_type;
	uint cmdarg;
	uint response[4];
};

struct mmc_data {
	union {
		char *dest;
		const char *src; /* src buffers don't get written to */
	};
	uint flags;
	uint blocks;
	uint blocksize;
};

/* forward decl. */
struct mmc;

#if CONFIG_IS_ENABLED(DM_MMC)
struct dm_mmc_ops {
	/**
	 * send_cmd() - Send a command to the MMC device
	 *
	 * @dev:	Device to receive the command
	 * @cmd:	Command to send
	 * @data:	Additional data to send/receive
	 * @return 0 if OK, -ve on error
	 */
	int (*send_cmd)(struct udevice *dev, struct mmc_cmd *cmd,
			struct mmc_data *data);

	/**
	 * set_ios() - Set the I/O speed/width for an MMC device
	 *
	 * @dev:	Device to update
	 * @return 0 if OK, -ve on error
	 */
	int (*set_ios)(struct udevice *dev);

	/**
	 * send_init_stream() - send the initialization stream: 74 clock cycles
	 * This is used after power up before sending the first command
	 *
	 * @dev:	Device to update
	 */
	void (*send_init_stream)(struct udevice *dev);

	/**
	 * get_cd() - See whether a card is present
	 *
	 * @dev:	Device to check
	 * @return 0 if not present, 1 if present, -ve on error
	 */
	int (*get_cd)(struct udevice *dev);

	/**
	 * get_wp() - See whether a card has write-protect enabled
	 *
	 * @dev:	Device to check
	 * @return 0 if write-enabled, 1 if write-protected, -ve on error
	 */
	int (*get_wp)(struct udevice *dev);

#ifdef MMC_SUPPORTS_TUNING
	/**
	 * execute_tuning() - Start the tuning process
	 *
	 * @dev:	Device to start the tuning
	 * @opcode:	Command opcode to send
	 * @return 0 if OK, -ve on error
	 */
	int (*execute_tuning)(struct udevice *dev, uint opcode);
#endif

#if CONFIG_IS_ENABLED(MMC_UHS_SUPPORT)
	/**
	 * wait_dat0() - wait until dat0 is in the target state
	 *		(CLK must be running during the wait)
	 *
	 * @dev:	Device to check
	 * @state:	target state
	 * @timeout:	timeout in us
	 * @return 0 if dat0 is in the target state, -ve on error
	 */
	int (*wait_dat0)(struct udevice *dev, int state, int timeout);
#endif
};

#define mmc_get_ops(dev)        ((struct dm_mmc_ops *)(dev)->driver->ops)

int dm_mmc_send_cmd(struct udevice *dev, struct mmc_cmd *cmd,
		    struct mmc_data *data);
int dm_mmc_set_ios(struct udevice *dev);
void dm_mmc_send_init_stream(struct udevice *dev);
int dm_mmc_get_cd(struct udevice *dev);
int dm_mmc_get_wp(struct udevice *dev);
int dm_mmc_execute_tuning(struct udevice *dev, uint opcode);
int dm_mmc_wait_dat0(struct udevice *dev, int state, int timeout);

/* Transition functions for compatibility */
int mmc_set_ios(struct mmc *mmc);
void mmc_send_init_stream(struct mmc *mmc);
int mmc_getcd(struct mmc *mmc);
int mmc_getwp(struct mmc *mmc);
int mmc_execute_tuning(struct mmc *mmc, uint opcode);
int mmc_wait_dat0(struct mmc *mmc, int state, int timeout);

#else
struct mmc_ops {
	int (*send_cmd)(struct mmc *mmc,
			struct mmc_cmd *cmd, struct mmc_data *data);
	int (*set_ios)(struct mmc *mmc);
	int (*init)(struct mmc *mmc);
	int (*getcd)(struct mmc *mmc);
	int (*getwp)(struct mmc *mmc);
};
#endif

struct mmc_config {
	const char *name;
#if !CONFIG_IS_ENABLED(DM_MMC)
	const struct mmc_ops *ops;
#endif
	uint host_caps;
	uint voltages;
	uint f_min;
	uint f_max;
	uint b_max;
	unsigned char part_type;
};

struct sd_ssr {
	unsigned int au;		/* In sectors */
	unsigned int erase_timeout;	/* In milliseconds */
	unsigned int erase_offset;	/* In milliseconds */
};

enum bus_mode {
	MMC_LEGACY,
	SD_LEGACY,
	MMC_HS,
	SD_HS,
	MMC_HS_52,
	MMC_DDR_52,
	UHS_SDR12,
	UHS_SDR25,
	UHS_SDR50,
	UHS_DDR50,
	UHS_SDR104,
	MMC_HS_200,
	MMC_HS_400,
	MMC_MODES_END
};

const char *mmc_mode_name(enum bus_mode mode);
void mmc_dump_capabilities(const char *text, uint caps);

static inline bool mmc_is_mode_ddr(enum bus_mode mode)
{
	if (mode == MMC_DDR_52)
		return true;
#if CONFIG_IS_ENABLED(MMC_UHS_SUPPORT)
	else if (mode == UHS_DDR50)
		return true;
#endif
#if CONFIG_IS_ENABLED(MMC_HS400_SUPPORT)
	else if (mode == MMC_HS_400)
		return true;
#endif
	else
		return false;
}

#define UHS_CAPS (MMC_CAP(UHS_SDR12) | MMC_CAP(UHS_SDR25) | \
		  MMC_CAP(UHS_SDR50) | MMC_CAP(UHS_SDR104) | \
		  MMC_CAP(UHS_DDR50))

static inline bool supports_uhs(uint caps)
{
#if CONFIG_IS_ENABLED(MMC_UHS_SUPPORT)
	return (caps & UHS_CAPS) ? true : false;
#else
	return false;
#endif
}

/*
 * With CONFIG_DM_MMC enabled, struct mmc can be accessed from the MMC device
 * with mmc_get_mmc_dev().
 *
 * TODO struct mmc should be in mmc_private but it's hard to fix right now
 */
struct mmc {
#if !CONFIG_IS_ENABLED(BLK)
	struct list_head link;
#endif
	const struct mmc_config *cfg;	/* provided configuration */
	uint version;
	void *priv;
	uint has_init;
	int high_capacity;
	bool clk_disable; /* true if the clock can be turned off */
	uint bus_width;
	uint clock;
	enum mmc_voltage signal_voltage;
	uint card_caps;
	uint host_caps;
	uint ocr;
	uint dsr;
	uint dsr_imp;
	uint scr[2];
	uint csd[4];
	uint cid[4];
	ushort rca;
	u8 part_support;
	u8 part_attr;
	u8 wr_rel_set;
	u8 part_config;
	uint tran_speed;
	uint legacy_speed; /* speed for the legacy mode provided by the card */
	uint read_bl_len;
#if CONFIG_IS_ENABLED(MMC_WRITE)
	uint write_bl_len;
	uint erase_grp_size;	/* in 512-byte sectors */
#endif
#if CONFIG_IS_ENABLED(MMC_HW_PARTITIONING)
	uint hc_wp_grp_size;	/* in 512-byte sectors */
#endif
#if CONFIG_IS_ENABLED(MMC_WRITE)
	struct sd_ssr	ssr;	/* SD status register */
#endif
	u64 capacity;
	u64 capacity_user;
	u64 capacity_boot;
	u64 capacity_rpmb;
	u64 capacity_gp[4];
#ifndef CONFIG_SPL_BUILD
	u64 enh_user_start;
	u64 enh_user_size;
#endif
#if !CONFIG_IS_ENABLED(BLK)
	struct blk_desc block_dev;
#endif
	char op_cond_pending;	/* 1 if we are waiting on an op_cond command */
	char init_in_progress;	/* 1 if we have done mmc_start_init() */
	char preinit;		/* start init as early as possible */
	int ddr_mode;
#if CONFIG_IS_ENABLED(DM_MMC)
	struct udevice *dev;	/* Device for this MMC controller */
#if CONFIG_IS_ENABLED(DM_REGULATOR)
	struct udevice *vmmc_supply;	/* Main voltage regulator (Vcc)*/
	struct udevice *vqmmc_supply;	/* IO voltage regulator (Vccq)*/
#endif
#endif
	u8 *ext_csd;
	u32 cardtype;		/* cardtype read from the MMC */
	enum mmc_voltage current_voltage;
	enum bus_mode selected_mode; /* mode currently used */
	enum bus_mode best_mode; /* best mode is the supported mode with the
				  * highest bandwidth. It may not always be the
				  * operating mode due to limitations when
				  * accessing the boot partitions
				  */
	u32 quirks;
};

struct mmc_hwpart_conf {
	struct {
		uint enh_start;	/* in 512-byte sectors */
		uint enh_size;	/* in 512-byte sectors, if 0 no enh area */
		unsigned wr_rel_change : 1;
		unsigned wr_rel_set : 1;
	} user;
	struct {
		uint size;	/* in 512-byte sectors */
		unsigned enhanced : 1;
		unsigned wr_rel_change : 1;
		unsigned wr_rel_set : 1;
	} gp_part[4];
};

enum mmc_hwpart_conf_mode {
	MMC_HWPART_CONF_CHECK,
	MMC_HWPART_CONF_SET,
	MMC_HWPART_CONF_COMPLETE,
};

struct mmc *mmc_create(const struct mmc_config *cfg, void *priv);

void mmc_destroy(struct mmc *mmc);

int mmc_initialize();
int mmc_init(struct mmc *mmc);
int mmc_send_tuning(struct mmc *mmc, u32 opcode, int *cmd_error);

#if CONFIG_IS_ENABLED(MMC_UHS_SUPPORT) || \
    CONFIG_IS_ENABLED(MMC_HS200_SUPPORT) || \
    CONFIG_IS_ENABLED(MMC_HS400_SUPPORT)
int mmc_deinit(struct mmc *mmc);
#endif

int mmc_read(struct mmc *mmc, u64 src, uchar *dst, int size);

/**
 * mmc_voltage_to_mv() - Convert a mmc_voltage in mV
 *
 * @voltage:	The mmc_voltage to convert
 * @return the value in mV if OK, -EINVAL on error (invalid mmc_voltage value)
 */
int mmc_voltage_to_mv(enum mmc_voltage voltage);

/**
 * mmc_set_clock() - change the bus clock
 * @mmc:	MMC struct
 * @clock:	bus frequency in Hz
 * @disable:	flag indicating if the clock must on or off
 * @return 0 if OK, -ve on error
 */
int mmc_set_clock(struct mmc *mmc, uint clock, bool disable);

#define MMC_CLK_ENABLE		false
#define MMC_CLK_DISABLE		true

struct mmc *find_mmc_device(int dev_num);
int mmc_set_dev(int dev_num);
void print_mmc_devices(char separator);

/**
 * get_mmc_num() - get the total MMC device number
 *
 * @return 0 if there is no MMC device, else the number of devices
 */
int get_mmc_num(void);
int mmc_switch_part(struct mmc *mmc, unsigned int part_num);
int mmc_hwpart_config(struct mmc *mmc, const struct mmc_hwpart_conf *conf,
		      enum mmc_hwpart_conf_mode mode);

#if !CONFIG_IS_ENABLED(DM_MMC)
int mmc_getcd(struct mmc *mmc);
int board_mmc_getcd(struct mmc *mmc);
int mmc_getwp(struct mmc *mmc);
int board_mmc_getwp(struct mmc *mmc);
#endif

int mmc_set_dsr(struct mmc *mmc, u16 val);
/* Function to change the size of boot partition and rpmb partitions */
int mmc_boot_partition_size_change(struct mmc *mmc, unsigned long bootsize,
					unsigned long rpmbsize);
/* Function to modify the PARTITION_CONFIG field of EXT_CSD */
int mmc_set_part_conf(struct mmc *mmc, u8 ack, u8 part_num, u8 access);
/* Function to modify the BOOT_BUS_WIDTH field of EXT_CSD */
int mmc_set_boot_bus_width(struct mmc *mmc, u8 width, u8 reset, u8 mode);
/* Function to modify the RST_n_FUNCTION field of EXT_CSD */
int mmc_set_rst_n_function(struct mmc *mmc, u8 enable);
/* Functions to read / write the RPMB partition */
int mmc_rpmb_set_key(struct mmc *mmc, void *key);
int mmc_rpmb_get_counter(struct mmc *mmc, unsigned long *counter);
int mmc_rpmb_read(struct mmc *mmc, void *addr, unsigned short blk,
		  unsigned short cnt, unsigned char *key);
int mmc_rpmb_write(struct mmc *mmc, void *addr, unsigned short blk,
		   unsigned short cnt, unsigned char *key);

/**
 * mmc_rpmb_route_frames() - route RPMB data frames
 * @mmc		Pointer to a MMC device struct
 * @req		Request data frames
 * @reqlen	Length of data frames in bytes
 * @rsp		Supplied buffer for response data frames
 * @rsplen	Length of supplied buffer for response data frames
 *
 * The RPMB data frames are routed to/from some external entity, for
 * example a Trusted Exectuion Environment in an arm TrustZone protected
 * secure world. It's expected that it's the external entity who is in
 * control of the RPMB key.
 *
 * Returns 0 on success, < 0 on error.
 */
int mmc_rpmb_route_frames(struct mmc *mmc, void *req, unsigned long reqlen,
			  void *rsp, unsigned long rsplen);

#ifdef CONFIG_CMD_BKOPS_ENABLE
int mmc_set_bkops_enable(struct mmc *mmc);
#endif

/**
 * Start device initialization and return immediately; it does not block on
 * polling OCR (operation condition register) status. Useful for checking
 * the presence of SD/eMMC when no card detect logic is available.
 *
 * @param mmc	Pointer to a MMC device struct
 * @return 0 on success, <0 on error.
 */
int mmc_get_op_cond(struct mmc *mmc);

/**
 * Start device initialization and return immediately; it does not block on
 * polling OCR (operation condition register) status.  Then you should call
 * mmc_init, which would block on polling OCR status and complete the device
 * initializatin.
 *
 * @param mmc	Pointer to a MMC device struct
 * @return 0 on success, <0 on error.
 */
int mmc_start_init(struct mmc *mmc);

/**
 * Set preinit flag of mmc device.
 *
 * This will cause the device to be pre-inited during mmc_initialize(),
 * which may save boot time if the device is not accessed until later.
 * Some eMMC devices take 200-300ms to init, but unfortunately they
 * must be sent a series of commands to even get them to start preparing
 * for operation.
 *
 * @param mmc		Pointer to a MMC device struct
 * @param preinit	preinit flag value
 */
void mmc_set_preinit(struct mmc *mmc, int preinit);

#ifdef CONFIG_MMC_SPI
#define mmc_host_is_spi(mmc)	((mmc)->cfg->host_caps & MMC_MODE_SPI)
#else
#define mmc_host_is_spi(mmc)	0
#endif
struct mmc *mmc_spi_init(uint bus, uint cs, uint speed, uint mode);

void board_mmc_power_init(void);
int board_mmc_init();
int cpu_mmc_init();
int mmc_get_env_addr(struct mmc *mmc, int copy, u32 *env_addr);
# ifdef CONFIG_SYS_MMC_ENV_PART
extern uint mmc_get_env_part(struct mmc *mmc);
# endif
int mmc_get_env_dev(void);

/* Set block count limit because of 16 bit register limit on some hardware*/
#ifndef CONFIG_SYS_MMC_MAX_BLK_COUNT
#define CONFIG_SYS_MMC_MAX_BLK_COUNT 65535
#endif

/**
 * mmc_get_blk_desc() - Get the block descriptor for an MMC device
 *
 * @mmc:	MMC device
 * @return block device if found, else NULL
 */
struct blk_desc *mmc_get_blk_desc(struct mmc *mmc);
int mmc_read_blocks(struct mmc *mmc, void *dst, lbaint_t start,
                           lbaint_t blkcnt);
ulong mmc_write_blocks(struct mmc *mmc, lbaint_t start,
                lbaint_t blkcnt, const void *src);
#endif /* _MMC_H_ */
