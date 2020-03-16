#include <errno.h>
#include <stdio.h>
#include <target/memory.h>
#include <target/cache.h>
#include <target/cpus.h>
#include <asm/mmu.h>


#define MAIR(attr, mt) ((uint64_t)(attr) << ((mt) << 3LL))

#define DEFAULT_MAIR ( \
    MAIR(CACHE_OUTER_NC_INNER_WB, 7) | \
    MAIR(CACHE_OUTER_WB_INNER_NC, 6) | \
    MAIR(CACHE_OUTER_WB_INNER_WB, 5) | \
    MAIR(CACHE_OUTER_WT_INNER_WT, 4) | \
    MAIR(CACHE_OUTER_NC_INNER_NC, 3) | \
    MAIR(CACHE_DEVICE_GRE, 2) | \
    MAIR(CACHE_DEVICE_nGnRE, 1) | \
    MAIR(CACHE_DEVICE_nGnRnE, 0) )

static translation_table_t mmu_ttb = {{0}};
static mmu_translation_table_attr_t pt_attr;

static int mmu_map_init(void)
{
    mmu_error_t error;
    granule_size_t page_size =
        (PAGE_SIZE == 0x10000) ? GRANULE_16KB : GRANULE_4KB;
    int i, j;

    /* Setup the translation table attributes */
    /* Standard parameters for IMC */
    pt_attr.mair = DEFAULT_MAIR;
    pt_attr.input_bit_size = 48;
    pt_attr.output_bit_size = 40;
    pt_attr.granule_size = page_size;
    pt_attr.asid = 0;
    pt_attr.secure = true;
    pt_attr.ttbr = MMU_TTBR0;

    /* Initialize the master page tables */
    error = mmu_initialize_translation_table(&mmu_ttb, &pt_attr);
    if (MMU_SUCCESS != error) {
        mmu_log(MMU_LOG_ALWAYS,
                "%s %d mmu_initialize_translation_table() failed\n",
                __FILE__, __LINE__);
        return -EINVAL;
    }

    /* Invalidate any existing TLB entries for EL1 */
    mmu_tlb_attr_t tlb = {
        .broadcast = false,
        .exception_levels = {false, false, false, true, false}
    };
    error = mmu_invalidate_tlb_all(&tlb);
    if (MMU_SUCCESS != error) {
        mmu_log(MMU_LOG_ALWAYS,
                "%s %d mmu_invalidate_tlb_all() failed\n",
                __FILE__, __LINE__);
        return -EINVAL;
    }

    /* Going forward we don't need to do any TLB maintenance until after
     * the MMU is enabled
     */
    tlb.exception_levels[EXCEPTION_LEVEL_3] = false;

    /* map text */
    mmu_map_attr_t text_mapping = {
        .input_addr = TEXT_START,
        .output_addr = TEXT_START,
        .size = (TEXT_END - TEXT_START),
        .perm_attr = PERM_RX,
        .share_attr = SHARE_INNER,
        .cache_attr = CACHE_OUTER_WB_INNER_WB,
        .secure = false,
        .global = false,
        MMU_MAP_NAME_STATIC(text)
    };
    error = mmu_map(&mmu_ttb, &text_mapping, &tlb);
    if (MMU_SUCCESS != error) {
        mmu_log(MMU_LOG_ALWAYS,
                "%s %d mmu_map() failed\n", __FILE__, __LINE__);
        return -EINVAL;
    }

    /* map full data (.data/.bss/heap/stack) */
    mmu_map_attr_t data_mapping = {
        .input_addr = DATA_START,
        .output_addr = DATA_START,
        .size = SVI_RAM_END - DATA_START,
        .perm_attr = PERM_RW,
        .share_attr = SHARE_INNER,
        .cache_attr = CACHE_OUTER_WB_INNER_WB,
        .secure = false,
        .global = false,
        MMU_MAP_NAME_STATIC(data)
    };
    error = mmu_map(&mmu_ttb, &data_mapping, &tlb);
    if (MMU_SUCCESS != error) {
        mmu_log(MMU_LOG_ALWAYS,
                "%s %d mmu_map() failed\n", __FILE__, __LINE__);
        return -EINVAL;
    }

    /* map peripherals */
    for (i = 0; i < static_mmu_entry_list_len; i++) {
        error = mmu_map(&mmu_ttb, static_mmu_entry_list + i, &tlb);
        if (MMU_SUCCESS != error) {
            mmu_log(MMU_LOG_ALWAYS,
                    "%s %d mmu_map(%d) failed\n", __FILE__, __LINE__, i);
            return -EINVAL;
        }
    }

    return 0;
}

int mmu_init(void)
{
    mmu_error_t error;

#ifdef CONFIG_MMU_FAST
    return mmu_fast_init();
#endif

    /* Initialize the MMU (still disabled) */
    error = mmu_initialize(EXCEPTION_LEVEL_3);
    if (MMU_SUCCESS != error) {
        mmu_log(MMU_LOG_ALWAYS,
                "%s %d mmu_initialize_translation_table() failed\n",
                __FILE__, __LINE__);
        return -EINVAL;
    }

    if (mmu_ttb.pt_base == NULL) {
        /* set up the page tables */
        error = mmu_map_init();
        if (0 != error) {
            mmu_log(MMU_LOG_ALWAYS,
                    "%s %d mmu_map_init() failed\n", __FILE__, __LINE__);
            return -EINVAL;
        }
    }

    /* Use the page tables we just set up
     * Page tables are in inner-shareable memory, inner/outer writeback
     * memory (only coherent on the A53 that we're running on)
     */
    error = mmu_switch_tables(EXCEPTION_LEVEL_3, &mmu_ttb,
                              SHARE_INNER, CACHE_OUTER_WB_INNER_WB);
    if (MMU_SUCCESS != error) {
        mmu_log(MMU_LOG_ALWAYS,
                "%s %d mmu_switch_table() failed\n", __FILE__, __LINE__);
        return -EINVAL;
    }

    /* Enable the MMU and address translation */
    error = mmu_enable(EXCEPTION_LEVEL_3);
    if (MMU_SUCCESS != error) {
        mmu_log(MMU_LOG_ALWAYS,
                "%s %d mmu_enable() failed\n", __FILE__, __LINE__);
        return -EINVAL;
    }

    return 0;
}
