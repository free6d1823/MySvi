/** @file mmu.c

  ARMv8 MMU Library

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

**/
#include <stdio.h>
#include <asm/reg.h>
#include <asm/sysreg.h>
#include <target/barrier.h>
#include <asm/mmu.h>

mmu_error_t mmu_initialize(exception_level_t el)
{
    tcr_elx_t tcr = {{0}};

    if (el < EXCEPTION_LEVEL_0 || el > EXCEPTION_LEVEL_CURRENT)
        return MMU_EBADPARAM;
    else if (el == EXCEPTION_LEVEL_CURRENT)
        el = mmu_get_current_el();

    if (el == EXCEPTION_LEVEL_1) {
        /* Disable table walks until tables are configured and set */
        tcr.el1.EPD0 = 1;
        tcr.el1.EPD1 = 1;
        /* ASID is defined by TTBR0 */
        tcr.el1.A1 = 0;
        /* ASID is 16-bits */
        tcr.el1.AS = 1;
        /* Address tagging is disabled */
        tcr.el1.TBI0 = 0;
        tcr.el1.TBI1 = 1;
    } else
        /* Address tagging is disabled */
        tcr.el3.TBI = 0;

    /* Write the TCR value */
    switch (el) {
    case EXCEPTION_LEVEL_1:
        __asm__ volatile
        (
            "MSR TTBR0_EL1, %[zero] \n\t"
            "MSR TTBR1_EL1, %[zero] \n\t"
            "MSR TCR_EL1, %[tcr] \n\t"
            :
            : [zero]"r" (0UL), [tcr]"r" (tcr.el1)
        );
        break;
    case EXCEPTION_LEVEL_2:
        __asm__ volatile
        (
            "MSR TTBR0_EL2, %[zero] \n\t"
            "MSR TCR_EL2, %[tcr] \n\t"
            :
            : [zero]"r" (0UL), [tcr]"r" (tcr.el2)
        );
        break;
    case EXCEPTION_LEVEL_3:
        __asm__ volatile
        (
            "MSR TTBR0_EL3, %[zero] \n\t"
            "MSR TCR_EL3, %[tcr] \n\t"
            :
            : [zero]"r" (0UL), [tcr]"r" (tcr.el3)
        );
        break;
    case EXCEPTION_LEVEL_0:
    default:
        return MMU_EBADPARAM;
    }
    return MMU_SUCCESS;
}

mmu_error_t mmu_enable(exception_level_t el)
{
    if (el < EXCEPTION_LEVEL_0 || el > EXCEPTION_LEVEL_CURRENT)
        return MMU_EBADPARAM;
    else if (el == EXCEPTION_LEVEL_CURRENT)
        el = mmu_get_current_el();

    switch (el) {
    case EXCEPTION_LEVEL_1:
        write_sysreg(read_sysreg(SCTLR_EL1) |
		     SCTLR_M | SCTLR_C | SCTLR_I, SCTLR_EL1);
        break;
    case EXCEPTION_LEVEL_2:
        write_sysreg(read_sysreg(SCTLR_EL2) |
		     SCTLR_M | SCTLR_C | SCTLR_I, SCTLR_EL2);
        break;
    case EXCEPTION_LEVEL_3:
        write_sysreg(read_sysreg(SCTLR_EL3) |
		     SCTLR_M | SCTLR_C | SCTLR_I, SCTLR_EL3);
        break;
    case EXCEPTION_LEVEL_0:
    default:
        return MMU_EBADPARAM;
    }
    isb();
    return MMU_SUCCESS;
}

mmu_error_t mmu_disable(exception_level_t el)
{
    uint64_t temp;

    if (el < EXCEPTION_LEVEL_0 || el > EXCEPTION_LEVEL_CURRENT)
        return MMU_EBADPARAM;
    else if(el == EXCEPTION_LEVEL_CURRENT)
        el = mmu_get_current_el();

    switch (el) {
    case EXCEPTION_LEVEL_1:
        __asm__ volatile
        (
            "MRS %[temp], SCTLR_EL1  \n\t"
            "BIC %[temp], %[temp], 0x1 \n\t"
            "MSR SCTLR_EL1, %[temp] \n\t"
            "ISB \n\t"
            : [temp]"=r" (temp)
            :
        );
        break;
    case EXCEPTION_LEVEL_2:
        __asm__ volatile
        (
            "MRS %[temp], SCTLR_EL2  \n\t"
            "BIC %[temp], %[temp], 0x1 \n\t"
            "MSR SCTLR_EL2, %[temp] \n\t"
            "ISB \n\t"
            : [temp]"=r" (temp)
            :
        );
        break;
    case EXCEPTION_LEVEL_3:
        __asm__ volatile
        (
            "MRS %[temp], SCTLR_EL3  \n\t"
            "BIC %[temp], %[temp], 0x1 \n\t"
            "MSR SCTLR_EL3, %[temp] \n\t"
            "ISB \n\t"
            : [temp]"=r" (temp)
            :
        );
        break;
    case EXCEPTION_LEVEL_0:
    default:
        return MMU_EBADPARAM;
    }
    return MMU_SUCCESS;
}

mmu_error_t mmu_switch_tables(exception_level_t el,
                              translation_table_t *pt,
                              shareability_attr_t shareability,
                              cache_attr_t cacheability)
{
    uint64_t tcr_update_mask = 0;
    uint64_t ttbr_val, temp;
    uint8_t encoded_output_size = 0;
    uint8_t tcr_inner_cache, tcr_outer_cache;
    mmu_error_t status = MMU_SUCCESS;
    tcr_elx_t tcr = {{0}};

    /* Parameter validation - cacheability is checked below in the TCR
     * conversion function
     */
    if (pt == NULL || el < EXCEPTION_LEVEL_0 ||
        el > EXCEPTION_LEVEL_CURRENT ||
        shareability < SHARE_NONE || shareability > SHARE_INNER)
        return MMU_EBADPARAM;
    else if (el == EXCEPTION_LEVEL_CURRENT)
        el = mmu_get_current_el();

    /* Grab the lock */
    status = mmu_lock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Do some more parameter checking */
    if (MMU_SUCCESS != mmu_validate_page_table_attributes(&pt->attr)) {
        (void)mmu_unlock(pt->lock);
        return MMU_EBADPARAM;
    }

    /* Set up values common across exception levels */
    /* TCR cache attributes are encoded differently than MAIR, this
     * function converts them
     */
    status = mmu_get_tcr_cache_attr(cacheability, &tcr_inner_cache,
                                    &tcr_outer_cache);
    if (MMU_SUCCESS != status) {
        (void) mmu_unlock(pt->lock);
        return status;
    }

    /* Construct the TTBR register value */
    ttbr_val = mmu_get_physical_address((uintptr_t)pt->pt_base);
    if (pt->attr.ttbr == MMU_TTBR0) {
        /* Construct the TCR value - the below operations are only for
         * TTBR0 (TG1 has different encodings)
         */
        if (pt->attr.granule_size == GRANULE_4KB)
            tcr.el1.TG0 = 0x0;
        else if(pt->attr.granule_size == GRANULE_16KB)
            tcr.el1.TG0 = 0x2;
        else
            tcr.el1.TG0 = 0x1;

        /* Set T0SZ which is derived from the size of the virtual address
         * space that these tables cover
         */
        tcr.el1.T0SZ = ((64 - pt->attr.input_bit_size) & 0x3F);
        /* Page table memory attributes (what type of memory is the table
         * stored in)
         */
        tcr.el1.SH0 = shareability;       /* Set TTBR0 shareability */
        /* Set the memory attributes for TTBR0 page table accesses */
        tcr.el1.IRGN0 = tcr_inner_cache;
        /* Set the memory attributes for TTBR0 page table accesses */
        tcr.el1.ORGN0 = tcr_outer_cache;
        /* Enable page table walks for this TTBR */
        tcr.el1.EPD0 = 0;
    } else {
        /* Construct the TCR value - the below operations are only for
         * TTBR1 (TG0 has different encodings)
         */
        if (pt->attr.granule_size == GRANULE_4KB)
            tcr.el1.TG1 = 0x2;
        else if(pt->attr.granule_size == GRANULE_16KB)
            tcr.el1.TG1 = 0x1;
        else
            tcr.el1.TG1 = 0x3;

        /* Set T1SZ which is derived from the size of the virtual address
         * space that these tables cover
         */
        tcr.el1.T1SZ = ((64 - pt->attr.input_bit_size) & 0x3F);
        /* Page table memory attributes (what type of memory is the table
         * stored in)
         */
        tcr.el1.SH1 = shareability;       /* Set TTBR1 shareability */
        /* Set the memory attributes for TTBR1 page table accesses */
        tcr.el1.IRGN1 = tcr_inner_cache;
        /* Set the memory attributes for TTBR1 page table accesses */
        tcr.el1.ORGN1 = tcr_outer_cache;
        /* Enable page table walks for this TTBR */
        tcr.el1.EPD1 = 0;
    }

    /* Get the encoded value for the output address size */
    status = mmu_get_tcr_output_size_encoding(pt->attr.output_bit_size,
                                              &encoded_output_size);
    if (status != MMU_SUCCESS) {
        mmu_unlock(pt->lock);
        return status;
    }

    if (el == EXCEPTION_LEVEL_1) {
        ttbr_val = ttbr_val | (((uint64_t) pt->attr.asid) << 48);
        tcr.el1.AS = 1;   /* ASID is 16-bits */
        tcr.el1.IPS = encoded_output_size;

        if (pt->attr.ttbr == MMU_TTBR0)
            /* Masks fields: IPS, TG0, SH0, ORGN0, IRGN0, EPD0, T0SZ */
            tcr_update_mask = 0x70000FFBFULL;
        else
            /* Masks fields: IPS, TG1, SH1, ORGN1, IRGN1, EPD1, T1SZ */
            tcr_update_mask = 0x7FFBF0000ULL;
    } else {
        tcr.el3.PS = encoded_output_size;
        /* Masks fields: PS, TG0, T0SZ */
        tcr_update_mask = 0x7FF3FULL;
    }

    /* Release the lock now that that we've read everything we need from
     * the PT structure
     */
    status = mmu_unlock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    switch (el) {
    case EXCEPTION_LEVEL_1:
        if (pt->attr.ttbr == MMU_TTBR0) {
            __asm__ volatile
            (
                "MSR TTBR0_EL1, %[ttbr0] \n\t"
                :
                :[ttbr0]"r" (ttbr_val)
            );
        } else {
            __asm__ volatile
            (
                "MSR TTBR1_EL1, %[ttbr1] \n\t"
                :
                :[ttbr1]"r" (ttbr_val)
            );
        }
        __asm__ volatile
        (
            "MSR MAIR_EL1, %[mair] \n\t"
            "MRS %[temp], TCR_EL1  \n\t"
            "BIC %[temp], %[temp], %[tcr_mask] \n\t"
            "ORR %[temp], %[temp], %[tcr] \n\t"
            "MSR TCR_EL1, %[temp] \n\t"
            "ISB \n\t"
            : [temp]"=r" (temp)
            : [mair]"r" (pt->attr.mair), [tcr_mask]"r" (tcr_update_mask), [tcr]"r" (tcr.el1)
        );
        break;
    case EXCEPTION_LEVEL_2:
        __asm__ volatile
        (
            "MSR TTBR0_EL2, %[ttbr0] \n\t"
            "MSR MAIR_EL2, %[mair] \n\t"
            "MRS %[temp], TCR_EL2  \n\t"
            "BIC %[temp], %[temp], %[tcr_mask] \n\t"
            "ORR %[temp], %[temp], %[tcr] \n\t"
            "MSR TCR_EL2, %[temp] \n\t"
            "ISB \n\t"
            : [temp]"=r" (temp)
            : [ttbr0]"r" (ttbr_val), [mair]"r" (pt->attr.mair), [tcr_mask]"r" (tcr_update_mask), [tcr]"r" (tcr.el2)
        );
        break;
    case EXCEPTION_LEVEL_3:
        __asm__ volatile
        (
            "MSR TTBR0_EL3, %[ttbr0] \n\t"
            "MSR MAIR_EL3, %[mair] \n\t"
            "MRS %[temp], TCR_EL3  \n\t"
            "BIC %[temp], %[temp], %[tcr_mask] \n\t"
            "ORR %[temp], %[temp], %[tcr] \n\t"
            "MSR TCR_EL3, %[temp] \n\t"
            "ISB \n\t"
            : [temp]"=r" (temp)
            : [ttbr0]"r" (ttbr_val), [mair]"r" (pt->attr.mair), [tcr_mask]"r" (tcr_update_mask), [tcr]"r" (tcr.el3)
        );
        break;
    case EXCEPTION_LEVEL_0:
    default:
        return MMU_EBADPARAM;
    }
    return MMU_SUCCESS;
}

mmu_error_t
mmu_initialize_translation_table(translation_table_t *pt,
                                 const mmu_translation_table_attr_t *pt_attr)
{
    uint32_t table_entry_count, address_width;
    size_t root_table_size;
    int32_t table_level;
    bool found_root_table_level = false;
    uint64_t TxSZ = 0;
    void *translation_table = NULL;

    /* Validate the entire suite of parameters */
    if (pt == NULL || pt_attr == NULL)
        return MMU_EBADPARAM;
    if (MMU_SUCCESS != mmu_validate_page_table_attributes(pt_attr))
        return MMU_EBADPARAM;

    /* Caculate T0/T1 Size */
    TxSZ = 64 - pt_attr->input_bit_size;

    /* Figure out what level table we need to start at for this input size
     * and granule configuration
     */
    for (table_level = 3; table_level >= 0; table_level--) {
        /* If we used this table level as the root table, how much address
         * space would we cover
         */
        address_width = (4 - table_level) *
            address_bits_per_lookup[pt_attr->granule_size] +
            granule_resolution_in_bits[pt_attr->granule_size];

        /* If this set of tables covers the entire address space, we're
         * good to go
         */
        if (address_width >= pt_attr->input_bit_size) {
            found_root_table_level = true;
            break;
        }
    }

    if (!found_root_table_level)
        return MMU_EUNEXPECTED;

    /* The table entry count is determine by the number of input address
     * bits the root table covers.
     */
    /* The root table covers all the bits not covered by
     * the lower tables + the granule size
     */
    table_entry_count = 1 << (pt_attr->input_bit_size -
        (address_width - address_bits_per_lookup[pt_attr->granule_size]));

    /* Each table entry is 8 bytes, so we need number of entries * 8 bytes
     * for the root table
     */
    root_table_size = table_entry_count *
        sizeof(translation_table_descriptor_t);

    /* Page tables have to be aligned at their size */
    translation_table = mmu_allocate_aligned(root_table_size,
                                             root_table_size,
                                             pt_attr->secure);
    if (translation_table == NULL)
        return MMU_ENOMEMORY;

    /* Zero out the root table memory */
    memset(translation_table, 0, root_table_size);
    /* Store the translation table parameters */
    pt->attr = *pt_attr;

    /* Calculate the virtual address base */
    if (pt->attr.ttbr == MMU_TTBR0)
        /* TTBR0 covers the low end of the address space */
        pt->va_base = 0;
    else {
        /* TTBR1 covers from the top of the address range downward */
        pt->va_base = 0xFFFFFFFFFFFFFFFFULL -
            ((1ULL << pt->attr.input_bit_size) - 1);
    }

    /* Store the location of the root table in the domain context */
    pt->pt_base = translation_table;
    pt->table_level = (uint32_t) table_level;
    pt->table_entry_count = table_entry_count;

    /* Initialize the lock */
    return mmu_lock_initialize(&pt->lock);
}

mmu_error_t mmu_deinit_translation_table(translation_table_t *pt)
{
    mmu_error_t status;
    mmu_tlb_attr_t tlb = {{0}};
    mmu_lock_t lock;

    if (pt == NULL)
        return MMU_EBADPARAM;

    status = mmu_lock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Save the lock so we can destroy it after we zero out the structure
     */
    lock = pt->lock;
    status = mmu_free_translation_table(pt, &tlb, pt->pt_base,
                                        pt->va_base, pt->table_level);
    if (MMU_SUCCESS != status)
        return status;

    memset(pt, 0, sizeof(translation_table_t));
    /* Release the lock now that the structure has been zeroed */
    status = mmu_unlock(lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Destroy the lock */
    status = mmu_lock_deinit(lock);
    if (status != MMU_SUCCESS)
        return status;
    return MMU_SUCCESS;
}

mmu_error_t mmu_map(translation_table_t *pt, const mmu_map_attr_t *map,
                    const mmu_tlb_attr_t *tlb)
{
    mmu_error_t status;
    mmu_action_parameters_t params = {0};

    /* Basic parameter validation - more sophisticated validation happens
     * in the page table library
     */
    if (pt == NULL || map == NULL || tlb == NULL)
        return MMU_EBADPARAM;

    /* Grab the lock before we start accessing pt members */
    status = mmu_lock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Setup the parameter structure */
    params.pt = pt;
    params.map_attr = map;
    params.tlb = tlb;
    params.action_type = MMU_ACTION_MAP;

    /* Set up the default table mappings to defer to the block attributes
     */
    /* Defer to the Priveledged eXecute Never bit in the block descriptors
     */
    params.table_attributes.S1.PXN = 0;
    /* Defer to the eXecute Never bit in the block descriptors */
    params.table_attributes.S1.XN = 0;
    /* 0b00 Use the attribute mappings in the block descriptors */
    params.table_attributes.S1.AP = 0;
    if (pt->attr.secure)
        /* These tables are in secure memory */
        params.table_attributes.S1.NS = 0;
    else
        /* These tables are in non-secure memory */
        params.table_attributes.S1.NS = 1;

    /* Construct the block and table attributes */
    status = mmu_encode_block_permissions(pt, map,
        &params.action.map.block_attributes);
    if (status != MMU_SUCCESS) {
        mmu_unlock(pt->lock);
        return status;
    }

    /* Set up some more common attributes */
    params.action.map.block_attributes.block_common.VALID = 1;
    status = mmu_modify_translation_tables(&params);
    if (status != MMU_SUCCESS) {
        mmu_unlock(pt->lock);
        return status;
    }

    /* Release the lock before we return */
    status = mmu_unlock(pt->lock);

#ifdef CONFIG_MMU_DEBUG
    printf("MMU: %-12s: 0x%016llx-0x%016llx -> 0x%016llx\n",
           map->name, map->output_addr, map->output_addr + map->size,
           map->input_addr);
#endif
    return status;
}

mmu_error_t mmu_unmap(translation_table_t *pt,
                      uintptr_t input_addr, size_t size,
                      const mmu_tlb_attr_t *tlb)
{
    mmu_error_t status = MMU_EFAILURE;
    mmu_action_parameters_t params = {0};
    mmu_map_attr_t map = {.input_addr = input_addr, .size = size};

    /* Basic parameter validation */
    if (pt == NULL || tlb == NULL || size == 0)
        return MMU_EBADPARAM;

    /* Grab the lock before we start accessing pt members */
    status = mmu_lock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Setup the parameter structure */
    params.pt = pt;
    params.map_attr = &map;
    params.tlb = tlb;
    params.action_type = MMU_ACTION_UNMAP;

    /* Set up the default table mappings to defer to the block attributes
     */
    /* Defer to the Priveledged eXecute Never bit in the block descriptors
     */
    params.table_attributes.S1.PXN = 0;
    /* Defer to the eXecute Never bit in the block descriptors */
    params.table_attributes.S1.XN = 0;
    /* 0b00 Use the attribute mappings in the block descriptors */
    params.table_attributes.S1.AP = 0;
    if (pt->attr.secure)
        /* These tables are in secure memory */
        params.table_attributes.S1.NS = 0;
    else
        /* These tables are in non-secure memory */
        params.table_attributes.S1.NS = 1;

    status = mmu_modify_translation_tables(&params);
    if (status != MMU_SUCCESS) {
        mmu_unlock(pt->lock);
        return status;
    }

    /* Release the lock before we return */
    return mmu_unlock(pt->lock);
}

mmu_error_t mmu_change_attributes(translation_table_t *pt,
                                  const mmu_map_attr_t *map,
                                  const mmu_tlb_attr_t *tlb)
{
    mmu_error_t status;
    mmu_map_attr_t local_map;
    mmu_action_parameters_t params = {0};

    /* Basic parameter validation */
    if (pt == NULL || map == NULL || tlb == NULL)
        return MMU_EBADPARAM;

    /* Grab the lock before we start accessing pt members */
    status = mmu_lock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Ensure that we completely ignore output address values */
    local_map = *map;
    local_map.output_addr = 0;

    /* Setup the parameter structure */
    params.pt = pt;
    params.map_attr = &local_map;
    params.tlb = tlb;
    params.action_type = MMU_ACTION_CHANGE_ATTR;

    /* Set up the default table mappings to defer to the block attributes
     */
    /* Defer to the Priveledged eXecute Never bit in the block descriptors
     */
    params.table_attributes.S1.PXN = 0;
    /* Defer to the eXecute Never bit in the block descriptors */
    params.table_attributes.S1.XN = 0;
    /* 0b00 Use the attribute mappings in the block descriptors */
    params.table_attributes.S1.AP = 0;
    if (pt->attr.secure)
        /* These tables are in secure memory */
        params.table_attributes.S1.NS = 0;
    else
        /* These tables are in non-secure memory */
        params.table_attributes.S1.NS = 1;

    /* Construct the block and table attributes */
    status = mmu_encode_block_permissions(pt, &local_map,
        &params.action.change_attr.block_attributes);
    if (status != MMU_SUCCESS) {
        mmu_unlock(pt->lock);
        return status;
    }

    /* Set up some more common attributes */
    params.action.change_attr.block_attributes.block_common.VALID = 1;

    /* Perform the action on the page tables */
    status = mmu_modify_translation_tables(&params);
    if (status != MMU_SUCCESS) {
        mmu_unlock(pt->lock);
        return status;
    }

    /* Release the lock before we return */
    return mmu_unlock(pt->lock);
}

mmu_error_t mmu_lookup_page(translation_table_t *pt,
                            uintptr_t input_addr,
                             mmu_map_attr_t *page_attributes)
{
    mmu_error_t status = MMU_EFAILURE;
    mmu_map_attr_t map = {.input_addr = input_addr};
    mmu_action_parameters_t params = {0};

    /* Basic parameter validation */
    if (pt == NULL || page_attributes == NULL)
        return MMU_EBADPARAM;

    /* Grab the lock before we start accessing pt members */
    status = mmu_lock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Setup the map structure size to correspond to a page */
    if (pt->attr.granule_size == GRANULE_4KB)
        map.size = SIZE_4KB;
    else if(pt->attr.granule_size == GRANULE_16KB)
        map.size = SIZE_16KB;
    else
        map.size = SIZE_64KB;

    /* Setup the parameter structure */
    params.pt = pt;
    params.map_attr = &map;
    params.tlb = NULL;
    params.action_type = MMU_ACTION_LOOKUP_PAGE;

    /* Perform the action on the page tables */
    status = mmu_modify_translation_tables(&params);
    if (status != MMU_SUCCESS) {
        mmu_unlock(pt->lock);
        return status;
    }

    /* Release the lock since we are done with the page tables */
    status = mmu_unlock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Convert block attributes to map attributes */
    page_attributes->input_addr = input_addr;
    page_attributes->size = map.size;
    page_attributes->share_attr =
        params.action.lookup_page.block_attributes.block_common.SH;
    page_attributes->cache_attr =
        0xFF & (pt->attr.mair >> 8 *
        params.action.lookup_page.block_attributes.block_common.ATTR_INDX);
    page_attributes->secure =
        params.action.lookup_page.block_attributes.block_common.NS == 0 ?
        true : false;
    page_attributes->global =
        params.action.lookup_page.block_attributes.block_common.NG == 0 ?
        true : false;

    /* Block address reconstruction takes more than one step */
    page_attributes->output_addr =
        mmu_get_block_address(&params.action.lookup_page.block_attributes,
                              params.level, pt->attr.granule_size);
    page_attributes->output_addr +=
        (block_size_per_level[pt->attr.granule_size][params.level] - 1) &
        input_addr;
    /* Permissions are a little more complicated */
    page_attributes->perm_attr = 0;
    /* Privileged execute never */
    if (params.action.lookup_page.block_attributes.block_common.PXN == 0)
        page_attributes->perm_attr |= PERM_P_X;
    /* User execute never */
    if (params.action.lookup_page.block_attributes.block_common.UXN == 0)
        page_attributes->perm_attr |= PERM_U_X;

    /* Read/write settings */
    if (params.action.lookup_page.block_attributes.block_common.AP == 0)
        page_attributes->perm_attr |= PERM_P_R | PERM_P_W;
    else if (params.action.lookup_page.block_attributes.block_common.AP == 1)
        page_attributes->perm_attr |= PERM_RW;
    else if (params.action.lookup_page.block_attributes.block_common.AP == 2)
        page_attributes->perm_attr |= PERM_P_R;
    else if (params.action.lookup_page.block_attributes.block_common.AP == 3)
        page_attributes->perm_attr |= PERM_R;

    return MMU_SUCCESS;
}

mmu_error_t mmu_walk_translation_tables(translation_table_t *pt,
                                        const uint64_t va,
                                        const size_t size)
{
    mmu_error_t status = MMU_EFAILURE;
    mmu_map_attr_t map = {.input_addr = va, .size = size};
    mmu_action_parameters_t params = {0};

    /* Basic parameter validation */
    if (pt == NULL || size == 0)
        return MMU_EBADPARAM;

    /* Grab the lock before we start accessing pt members */
    status = mmu_lock(pt->lock);
    if (status != MMU_SUCCESS)
        return status;

    /* Setup the parameter structure */
    params.pt = pt;
    params.map_attr = &map;
    params.tlb = NULL;
    params.action_type = MMU_ACTION_WALK_TABLES;

    /* Perform the action on the page tables */
    status = mmu_modify_translation_tables(&params);
    if (status != MMU_SUCCESS) {
        mmu_unlock(pt->lock);
        return status;
    }

    return mmu_unlock(pt->lock);
}

mmu_error_t mmu_invalidate_tlb_all(const mmu_tlb_attr_t *tlb)
{
    exception_level_t current_el, el;

    if (tlb == NULL)
        return MMU_EBADPARAM;

    /* Check to see if we are performing any maintenance at all */
    if (!tlb->exception_levels[EXCEPTION_LEVEL_0] &&
        !tlb->exception_levels[EXCEPTION_LEVEL_1] &&
        !tlb->exception_levels[EXCEPTION_LEVEL_2] &&
        !tlb->exception_levels[EXCEPTION_LEVEL_3] &&
        !tlb->exception_levels[EXCEPTION_LEVEL_CURRENT])
        /* We aren't performing any maintanence, return success */
        return MMU_SUCCESS;

    /* Get the current EL, so we can ensure we don't try and issue
     * invalid TLBI commands
     */
    current_el = mmu_get_current_el();

    /* Ensure updates to the page tables have made it to memory */
    if (tlb->broadcast)
        __asm__ volatile("DSB ISH \n\t");
    else
        __asm__ volatile("DSB NSH \n\t");

    for(el = EXCEPTION_LEVEL_0; el < EXCEPTION_LEVEL_ENUM_MAX; el++) {
        exception_level_t switch_param = el;

        /* Check to see if we are supposed to invalidate TLB entries at
         * this level
         */
        if (!tlb->exception_levels[el])
            continue;
        /* Check to see if the user has requested us to invalidate TLB
         * entries at a inaccessible exception level
         */
        else if (el > current_el && el != EXCEPTION_LEVEL_CURRENT)
            return MMU_EBADPARAM;
        else if (el == EXCEPTION_LEVEL_CURRENT)
            switch_param = current_el;

        /* Issue the right TLB command for this exception level */
        switch (switch_param) {
        case EXCEPTION_LEVEL_0:
        case EXCEPTION_LEVEL_1:
            if (tlb->broadcast)
                __asm__ volatile("TLBI VMALLE1IS \n\t");
            else
                __asm__ volatile("TLBI VMALLE1 \n\t");
            break;
        case EXCEPTION_LEVEL_2:
            if (tlb->broadcast)
                __asm__ volatile("TLBI ALLE2IS \n\t");
            else
                __asm__ volatile("TLBI ALLE2 \n\t");
            break;
        case EXCEPTION_LEVEL_3:
            if (tlb->broadcast)
                __asm__ volatile("TLBI ALLE3IS \n\t");
            else
                __asm__ volatile("TLBI ALLE3 \n\t");
            break;
        default:
            return MMU_EBADPARAM;
        }
    }

    if (tlb->broadcast) {
        __asm__ volatile
        (
            "DSB ISH \n\t"
            "ISB \n\t"
        );
    } else {
        __asm__ volatile
        (
            "DSB NSH \n\t"
            "ISB \n\t"
        );
    }

    return MMU_SUCCESS;
}

mmu_error_t mmu_invalidate_tlb_asid(const mmu_tlb_attr_t *tlb,
                                    uint16_t asid)
{
    exception_level_t current_el;
    uint64_t arg;

    if (tlb == NULL ||
        tlb->exception_levels[EXCEPTION_LEVEL_2] ||
        tlb->exception_levels[EXCEPTION_LEVEL_3]) {
        return MMU_EBADPARAM;
    } else if (tlb->exception_levels[EXCEPTION_LEVEL_CURRENT]) {
        /* Verify that we aren't trying to invalidate TLB entries by ASID
         * for a unsupported level
         */
        /* Get the current EL, so we can ensure we don't try and issue
         * invalid TLBI commands
         */
        current_el = mmu_get_current_el();
        if (current_el > 1)
            return MMU_EBADPARAM;
    }
    else if (!tlb->exception_levels[EXCEPTION_LEVEL_0] &&
             !tlb->exception_levels[EXCEPTION_LEVEL_1]) {
        /* Check to see if we are performing any maintenance at all */
        /* We aren't performing any maintanence, return success */
        return MMU_SUCCESS;
    }

    /* The TLB instructions expect ARG[63:48] to hold the ASID */
    arg = ((uint64_t)asid) << 48;

    /* This operation is only valid at EL0/EL1, so we can skip the loop and
     * swith
     */
    if (tlb->broadcast) {
        __asm__ volatile
        (
            "DSB ISH \n\t"
            "TLBI ASIDE1IS, %[arg] \n\t"
            "DSB ISH \n\t"
            "ISB \n\t"
            :
            : [arg]"r" (arg)
        );
    } else {
        __asm__ volatile
        (
            "DSB NSH \n\t"
            "TLBI ASIDE1, %[arg] \n\t"
            "DSB NSH \n\t"
            "ISB \n\t"
            :
            : [arg]"r" (arg)
        );
    }

    return MMU_SUCCESS;
}

mmu_error_t mmu_invalidate_tlb_va(const mmu_tlb_attr_t *tlb,
                                  uintptr_t va, uint16_t asid)
{
    exception_level_t current_el, el;

    if (tlb == NULL)
        return MMU_EBADPARAM;
    else if (!tlb->exception_levels[EXCEPTION_LEVEL_0] &&
             !tlb->exception_levels[EXCEPTION_LEVEL_1] &&
             !tlb->exception_levels[EXCEPTION_LEVEL_2] &&
             !tlb->exception_levels[EXCEPTION_LEVEL_3] &&
             !tlb->exception_levels[EXCEPTION_LEVEL_CURRENT])
        /* Check to see if we are performing any maintenance at all */
        /* We aren't performing any maintanence, return success */
        return MMU_SUCCESS;

    /* Get the current EL, so we can ensure we don't try and issue invalid
     * TLBI commands
     */
    current_el = mmu_get_current_el();

    /* The TLB instructions expect VA[43:0] to hold virtual address bits
     * [55:12]
     */
    va = (va >> 12) & ((1ULL << 44) - 1);

    /* Ensure updates to the page tables have made it to memory */
    if (tlb->broadcast)
        __asm__ volatile("DSB ISH \n\t");
    else
        __asm__ volatile("DSB NSH \n\t");

    for (el = EXCEPTION_LEVEL_0; el < EXCEPTION_LEVEL_ENUM_MAX; el++) {
        exception_level_t switch_param = el;

        /* Check to see if we are supposed to invalidate TLB entries at
         * this level
         */
        if (!tlb->exception_levels[el])
            continue;
        else if (el > current_el && el != EXCEPTION_LEVEL_CURRENT) {
            /* Check to see if the user has requested us to invalidate TLB
             * entries at a inaccessible exception level
             */
            return MMU_EBADPARAM;
        } else if(el == EXCEPTION_LEVEL_CURRENT)
            switch_param = current_el;

        switch (switch_param) {
        case EXCEPTION_LEVEL_0:
        case EXCEPTION_LEVEL_1:
            /* Add the ASID to the invalidate command */
            va |= ((uint64_t)asid) << 48;
            if (tlb->broadcast) {
                __asm__ volatile
                (
                    "TLBI VAE1IS, %[va] \n\t"
                    :
                    : [va]"r" (va)
                );
            } else {
                __asm__ volatile
                (
                    "TLBI VAE1, %[va] \n\t"
                    :
                    : [va]"r" (va)
                );
            }
            break;
        case EXCEPTION_LEVEL_2:
            if (tlb->broadcast) {
                __asm__ volatile
                (
                    "TLBI VAE2IS, %[va] \n\t"
                    :
                    : [va]"r" (va)
                );
            } else {
                __asm__ volatile
                (
                    "TLBI VAE2, %[va] \n\t"
                    :
                    : [va]"r" (va)
                );
            }
            break;
        case EXCEPTION_LEVEL_3:
            if (tlb->broadcast) {
                __asm__ volatile
                (
                    "TLBI VAE3IS, %[va] \n\t"
                    :
                    : [va]"r" (va)
                );
            } else {
                __asm__ volatile
                (
                    "TLBI VAE3, %[va] \n\t"
                    :
                    : [va]"r" (va)
                );
            }
            break;
        default:
            return MMU_EBADPARAM;
        }
    }

    if (tlb->broadcast) {
        __asm__ volatile
        (
            "DSB ISH \n\t"
            "ISB \n\t"
        );
    } else {
        __asm__ volatile
        (
            "DSB NSH \n\t"
            "ISB \n\t"
        );
    }

    return MMU_SUCCESS;
}

exception_level_t mmu_get_current_el(void)
{
    uint64_t current_el;

    __asm__ volatile
    (
        "mrs %0, CurrentEL \n\t"
        : "=r" (current_el)
        :
    );

    /* The exception level is in bits [3:2] */
    return (exception_level_t) (current_el >> 2);
}

mmu_error_t mmu_get_tcr_cache_attr(cache_attr_t cache_attr,
                                   uint8_t *inner, uint8_t *outer)
{
    uint8_t tcr_vals[2];
    int i;

    if (inner == NULL || outer == NULL)
        return MMU_EBADPARAM;

    /* TCR cache attributes are different than MAIR attributes, we convert
     * here
     */
    /* i = 0 is the inner cacheability bits, i = 1 is the outer
     * cacheability bits
     */
    for (i = 0; i < 2; i++) {
        tcr_vals[i] = (cache_attr >> (i * 4)) & 0xF;
        /* This is non-cacheable */
        if (tcr_vals[i] == 0x4)
            tcr_vals[i] = 0x0;
        /* Write back, write allocate */
        else if ((tcr_vals[i] & ((uint8_t) ~0x2)) == 0xD)
            tcr_vals[i] = 0x1;
        /* Write through */
        else if ((tcr_vals[i] & ((uint8_t) ~0x3)) == 0x8)
            tcr_vals[i] = 0x2;
        /* Write back, no allocate */
        else if ((tcr_vals[i] & ((uint8_t) ~0x2)) == 0xC)
            tcr_vals[i] = 0x3;
        else
            return MMU_EBADPARAM;
    }

    *inner = tcr_vals[0];
    *outer = tcr_vals[1];
    return MMU_SUCCESS;
}

mmu_error_t mmu_get_tcr_output_size_encoding(uint32_t output_bit_size,
                                             uint8_t *encoded_val)
{

    if (encoded_val == NULL)
        return MMU_EBADPARAM;

    /* Convert output bit size to the TCR encoding */
    switch (output_bit_size) {
    case 32:
        *encoded_val = 0;
        break;
    case 36:
        *encoded_val = 1;
        break;
    case 40:
        *encoded_val = 2;
        break;
    case 42:
        *encoded_val = 3;
        break;
    case 44:
        *encoded_val = 4;
        break;
    case 48:
        *encoded_val = 5;
        break;
    default:
        return MMU_EBADPARAM;
    }

    return MMU_SUCCESS;
}

mmu_error_t mmu_validate_page_table_attributes(
    const mmu_translation_table_attr_t* pt_attr)
{
    uint8_t temp;
    int i;

    /* Validate the entire suite of parameters */
    if (pt_attr == NULL ||
        pt_attr->input_bit_size < 25 ||
        pt_attr->input_bit_size > 48 ||
        pt_attr->granule_size < GRANULE_4KB ||
        pt_attr->granule_size > GRANULE_64KB ||
        pt_attr->ttbr < MMU_TTBR0 || pt_attr->ttbr > MMU_TTBR1)
        return MMU_EBADPARAM;

    /* Ensure the output size is one of the accepted values */
    if (MMU_SUCCESS !=
        mmu_get_tcr_output_size_encoding(pt_attr->output_bit_size, &temp))
        return MMU_EBADPARAM;

    /* Validate the MAIR value */
    for (i = 0; i < 8; i++) {
        temp = pt_attr->mair >> (i * 8);
        /* Not allowed via the ARMv8 ARM (G6-4541)*/
        if (((temp & 0xF0) != 0 && (temp & 0xF) == 0) ||
            ((temp & 0xF0) == 0 && (temp & 0x3) != 0))
            return MMU_EBADPARAM;
    }

    return MMU_SUCCESS;
}
