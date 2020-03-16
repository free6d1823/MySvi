#ifndef __PLATFORM_COMMON_H__
#define __PLATFORM_COMMON_H__

#include <asm/platform_arch.h>
//#include "xlat_tables.h"

/* Special value used to verify platform parameters from BL2 to BL3-1 */
#define QC_BL31_PLAT_PARAM_VAL		0x0f1e2d3c4b5a6978ULL

/* Special value used to indicate a HOB variable was not found or is invalid. */
#define QC_HOB_INVALID_PARAM_VAL	-1

/*******************************************************************************
 * Platform binary types for linking
 ******************************************************************************/
#define PLATFORM_LINKER_FORMAT		"elf64-littleaarch64"
#define PLATFORM_LINKER_ARCH		aarch64

/*******************************************************************************
 * Generic platform constants
 ******************************************************************************/
/* Define number of secure apps supported by TZ.
 * We only have one - MM.
 */
#define NUMBER_OF_SECURE_APPS	2

/* Size of cacheable stacks */
#define PLATFORM_STACK_SIZE		0x800

/* Trusted Boot Firmware BL2 */
#define BL2_IMAGE_NAME			"bl2.bin"

/* EL3 Runtime Firmware BL31 */
#define BL31_IMAGE_NAME			"bl31.bin"

/* Secure Payload BL32 (Trusted OS) */
#define BL32_IMAGE_NAME			"bl32.bin"

/* Non-Trusted Firmware BL33 and its load address */
#define BL33_IMAGE_NAME			"bl33.bin" /* e.g. UEFI */

#define PLATFORM_CACHE_LINE_SIZE	64
#define MAX_IO_DEVICES			3
#define MAX_IO_HANDLES			4

/*******************************************************************************
 * Platform memory map related constants
 ******************************************************************************/
#define TZRAM_OFFSET			0x10000000
#define TZRAM_SIZE			0x800000
#define TZRAM_BASE			(DDR_BASE+TZRAM_OFFSET)

#define IMCRAM_OFFSET			0x600000
#define IMCRAM_SIZE			0x200000
#define IMCRAM_BASE			(DDR_BASE+IMCRAM_OFFSET)

#define DEFAULT_VARIABLE_STORE_BASE	(DDR_BASE+0x3FA000)
#define DEFAULT_VARIABLE_STORE_SIZE	(0x4000)

#define QDSS_TZ_EVENT_MASK_BASE		(TZRAM_BASE+0x7FFF000)
#define QDSS_TZ_EVENT_MASK_SIZE		0x1000

/*
 * This region of memory contains the following:
 *  HOB
 *  Default Variable Store
 *  Shared Variable Store
 */
#define SBL_HOB				(DDR_BASE+0x200000)
#define SBL_HOB_SIZE			0x6000
#define XBL_MEM_SIZE			0x200000

#define DEBUG_CONFIG_OFFSET		0x34030

/*******************************************************************************
 * BL31 specific defines.
 ******************************************************************************/
#define BL31_RO_BASE			TZRAM_BASE
#define BL31_RO_SIZE			0x48000
#define BL31_RO_LIMIT			(BL31_RO_BASE + BL31_RO_SIZE)

#define BL31_RW_BASE			BL31_RO_LIMIT
#define BL31_RW_SIZE			0x84000
#define BL31_RW_LIMIT			(BL31_RW_BASE + BL31_RW_SIZE)

#define BL31_LIMIT			BL31_RW_LIMIT

#define MAILBOX_BASE			BL31_RW_LIMIT
#define MAILBOX_SIZE			0x1000
#define MAILBOX_LIMIT			(MAILBOX_BASE + MAILBOX_SIZE)

#define BL31_HEAP_START			(MAILBOX_LIMIT + 0x1000)
#define BL31_HEAP_SIZE			(0x100000)
#define BL31_HEAP_LIMIT			(BL31_HEAP_START + BL31_HEAP_SIZE)

#define TZ_LOG_OFFSET			0x300000
#define TZ_LOG_BASE			(TZRAM_BASE + TZ_LOG_OFFSET)
#define TZ_LOG_COMMON_BASE		TZ_LOG_BASE
#define TZ_LOG_COMMON_SIZE		0x10000 // can make logs much larger, but takes time to initialize
#define TZ_LOG_PCPU_BASE		(TZ_LOG_BASE + TZ_LOG_COMMON_SIZE)
#define TZ_LOG_PCPU_SIZE		(PLATFORM_CORE_COUNT * 0x1000)
#define TZ_LOG_SIZE			(TZ_LOG_COMMON_SIZE + TZ_LOG_PCPU_SIZE)
#define TZ_LOG_LIMIT			(TZ_LOG_BASE + TZ_LOG_SIZE)

#if (BL31_HEAP_LIMIT >= TZ_LOG_BASE)
#error "BL31 HEAP AND TZ LOG OVERLAP"
#endif

/* Region for sec.dat */
#define TZ_SECDAT_BUFFER_ADDRESS	(TZRAM_BASE+0x600000)
#define TZ_SECDAT_BUFFER_SIZE		2048

/*******************************************************************************
 * BL32 specific defines.
 ******************************************************************************/
#define BL32_VA_PA_OFFSET		0xFFFFFF0000000000

#define BL32_VA_TO_PA(x)		((uint64_t)x - BL32_VA_PA_OFFSET)
#define BL32_PA_TO_VA(x)		((uint64_t)x + BL32_VA_PA_OFFSET)

#define BL32_OFFSET				0x400000
#define BL32_PHYSICAL_BASE		(TZRAM_BASE + BL32_OFFSET)
#define BL32_SIZE				(0x80000)

#define BL32_BASE			(BL32_PHYSICAL_BASE + BL32_VA_PA_OFFSET)
#define BL32_RO_BASE		BL32_BASE
#define BL32_RO_SIZE		0x20000
#define BL32_RO_LIMIT		(BL32_RO_BASE + BL32_RO_SIZE)

#define BL32_RW_BASE		BL32_RO_LIMIT
#define BL32_RW_SIZE		0x40000
#define BL32_RW_LIMIT		(BL32_RW_BASE + BL32_RW_SIZE)

/* BL32_STACKS_START must be page aligned. QSPD's correctness depends
 * on the stack region starting at a page aligned address.
 */
#define BL32_STACKS_START	BL32_RW_LIMIT

/* We have one page of SECURE EL1 stack per app plus one page for
 * use during initialization or for other entry into secure EL1(maybe to
 * kill an app for example). Note that these are secure EL1 stacks.
 * Secure EL0 must set its own stack in SP_EL0.
 */
#define BL32_STACKS_SIZE		((NUMBER_OF_SECURE_APPS * PAGE_SIZE) + PAGE_SIZE)
#define BL32_STACKS_LIMIT	(BL32_STACKS_START + BL32_STACKS_SIZE)

#define BL32_LIMIT			(BL32_BASE + BL32_SIZE)

#if (BL32_STACK_LIMIT >= BL32_LIMIT)
#error "BL32 size exceeds BL32_SIZE"
#endif

/* We need 2 defines for the log base since we need to map the log
 * buffer in EL1 and EL3. EL3 uses 1:1 mapping but EL1 uses non
 * linear mapping.
 */
#define TZ_LOG_BL32_EL1_BASE		(BL32_BASE + 0x100000)
#define TZ_LOG_BL32_EL3_BASE		(BL32_PHYSICAL_BASE + 0x100000)
#define TZ_LOG_BL32_SIZE		0x10000

#if (BL32_LIMIT >= TZ_LOG_BL32_EL1_BASE)
#error "BL32 size overflows in BL32 logs space"
#endif

/*******************************************************************************
 * Platform specific page table and MMU setup constants
 ******************************************************************************/
#define ADDR_SPACE_SIZE		(1ull << ADDR_TOP_BIT)
#define MAX_MMAP_REGIONS	64

/*******************************************************************************
 * GIC-400 & interrupt handling related constants
 ******************************************************************************/

/* Base FVP compatible GIC memory map */
#define IRQ_SEC_SGI_0		8
#define IRQ_SEC_SGI_1		9
#define IRQ_SEC_SGI_2		10
#define IRQ_SEC_SGI_3		11
#define IRQ_SEC_SGI_4		12
#define IRQ_SEC_SGI_5		13
#define IRQ_SEC_SGI_6		14
#define IRQ_SEC_SGI_7		15

/*******************************************************************************
 * Declarations and constants to access the mailboxes safely. Each mailbox is
 * aligned on the biggest cache line size in the platform. This is known only
 * to the platform as it might have a combination of integrated and external
 * caches. Such alignment ensures that two maiboxes do not sit on the same cache
 * line at any cache level. They could belong to different cpus/clusters &
 * get written while being protected by different locks causing corruption of
 * a valid mailbox address.
 ******************************************************************************/
#define CACHE_WRITEBACK_SHIFT	PLAT_CACHE_ALIGN_SHIFT
#define CACHE_WRITEBACK_GRANULE	(1 << CACHE_WRITEBACK_SHIFT)

/* Defines used to support a "debug cookie" for early TZ debugging. */
#define TZ_DBG_COOKIE_ENABLED_MAGIC_VAL		0xDEADFEEB
#define TZ_DBG_COOKIE_SET_ALL_CPUS_MASK		0x00FFFFFF

#define TZ_DBG_COOKIE_ENABLED_MAGIC_ADDR	(MSG_RAM_BASE + 0xBC00)
#define TZ_DBG_COOKIE_CPUS_MASK_MAGIC_ADDR	(MSG_RAM_BASE + 0xBC08)

#define TZ_DBG_COOKIE_MEMORYMAP_ADDR		(TZ_DBG_COOKIE_ENABLED_MAGIC_ADDR & ~0xFFF)

/*******************************************************************************
 * UEFI SMM Memory Map Info
 ******************************************************************************/
#define SMM_SMRAM_TOTAL_SPACE		(0x0004000000)
#define SMM_SMRAM_BASE			(DDR_BASE+0x0018000000)

#define SMM_SMRAM_STACK_SIZE		(0x8000)          // 32KB of stack
#define MM_LOG_COMMON_SIZE		(0x40000)         // 256KB of ram buffer
#define SMM_SMRAM_MAILBOX_BASE_ADDR_OFFSET	(0x1)
#define SMM_SMRAM_MAILBOX_BASE_ADDR_OFFSET_IN_BYTES	(sizeof(uint64_t*))
#define SMM_SMRAM_MAILBOX_DATA_SIZE	(0x10000-SMM_SMRAM_MAILBOX_BASE_ADDR_OFFSET_IN_BYTES)         // 64KB of MAILBOX data
#define SMM_SMRAM_MAILBOX_SIZE		(SMM_SMRAM_MAILBOX_DATA_SIZE+SMM_SMRAM_MAILBOX_BASE_ADDR_OFFSET_IN_BYTES)
#define SMM_SMRAM_HEAP_SIZE		(0x3BA8000)

#define SMM_SMRAM_STACK_BASE		(SMM_SMRAM_BASE)
#define MM_LOG_COMMON_BASE		(SMM_SMRAM_STACK_BASE+SMM_SMRAM_STACK_SIZE)

// SMRAM Mailbox memory.  This memory is used to send and receive messages from
// SMM Communicate and TPM commands sent to a Secure App.
#define SMM_SMRAM_MAILBOX_BASE		(MM_LOG_COMMON_BASE + MM_LOG_COMMON_SIZE)

// SMRAM Heap memory.  This memory is used UEFI SMM to allocate HEAP space for SMM drivers.
#define SMM_SMRAM_HEAP_BASE		(SMM_SMRAM_MAILBOX_BASE + SMM_SMRAM_MAILBOX_SIZE)

// SMRAM Code memory.  This memory is used to store executable code.
#define SMM_SMRAM_RO_CODE_BASE		(SMM_SMRAM_HEAP_BASE + SMM_SMRAM_HEAP_SIZE)
// Since SMM_SMRAM_RO_CODE_SIZE is half the total size left of the SMRAM size just split that area between RO and RW code space..
#define SMM_SMRAM_RO_CODE_SIZE		((SMM_SMRAM_TOTAL_SPACE - SMM_SMRAM_MAILBOX_SIZE - SMM_SMRAM_STACK_SIZE - SMM_SMRAM_HEAP_SIZE - MM_LOG_COMMON_SIZE))

#define STANDALONE_SMM_IPL_ENTRY_POINT	(SMM_SMRAM_RO_CODE_BASE+0x160)

#define SMM_SMRAM_NS_MAILBOX_BASE	(DDR_BASE+0x1C000000)
#define SMM_SMRAM_NS_MAILBOX_DATA_SIZE	(0x10000-SMM_SMRAM_MAILBOX_BASE_ADDR_OFFSET_IN_BYTES)
#define SMM_SMRAM_NS_MAILBOX_SIZE	(SMM_SMRAM_NS_MAILBOX_DATA_SIZE+SMM_SMRAM_MAILBOX_BASE_ADDR_OFFSET_IN_BYTES)

#define TPM_ACPI_CRB_AREA_BASE		(DDR_BASE + 0x1C800000)
#define TPM_ACPI_CRB_AREA_SIZE		(0x200000)

#endif /* __PLATFORM_COMMON_H__ */
