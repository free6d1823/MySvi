/** @file mmu_tables.c

  ARMv8 MMU Library

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

**/
#include <asm/mmu.h>

/*=======================================================================
                         INTERNAL FUNCTIONS
 ========================================================================*/

mmu_error_t mmu_modify_translation_tables(mmu_action_parameters_t* params)
{
    mmu_error_t status = MMU_EFAILURE;
    mmu_table_walk_action_t entry_action;
    size_t block_size = 0;
    size_t remaining_size = 0;
    uintptr_t current_va;
    uintptr_t pt_base_stack[4] = {0};
    uint64_t index_bits, index_bit_mask, alignment_mask;
    uint8_t current_level;
    translation_table_descriptor_t* pt_descriptor;
    granule_size_t granule_size;
    translation_table_t* pt;
    mmu_map_attr_t map_attr;

    /* Validate input parameters */
    if (params == NULL || params->pt == NULL ||
        params->map_attr == NULL) {
        return MMU_EBADPARAM;
    } else if (mmu_validate_page_table_attributes(&params->pt->attr) !=
               MMU_SUCCESS) {
        return MMU_EBADPARAM;
    } else if (params->pt->table_level > 3 ||
               params->pt->table_entry_count >
               (1 << address_bits_per_lookup[params->pt->attr.granule_size])) {
        return MMU_EBADPARAM;
    }

    /* Setup locals for easier referencing */
    pt = params->pt;
    map_attr = *params->map_attr;

    /* Setup granule parameters */
    granule_size = pt->attr.granule_size;
    switch(granule_size) {
    case GRANULE_4KB:
        alignment_mask = SIZE_4KB - 1;
        break;
    case GRANULE_16KB:
        alignment_mask = SIZE_16KB - 1;
        break;
    case GRANULE_64KB:
        alignment_mask = SIZE_64KB - 1;
        break;
    default:
        return MMU_EBADPARAM;
    }

    /* Change the absolute virtual address into an offset (for TTBR1, TTBR0
     * base address is always 0)
     */
    if (map_attr.input_addr < pt->va_base)
        /* Address is not covered by these tables */
        return MMU_EBADADDR;
    else
        /* Turn the virtual address into an offset from table base */
        map_attr.input_addr -= pt->va_base;

    /* Ensure the input address, output address, and region size are all
     * page aligned and that the input and output addresses fall within the
     * configured input/output address space
     */
    if ((map_attr.input_addr + map_attr.size) >
        (1LL << pt->attr.input_bit_size) ||
        (map_attr.output_addr + map_attr.size) >
        (1LL << pt->attr.output_bit_size) ||
        map_attr.size == 0 ||
        (map_attr.size & alignment_mask) != 0 ||
        (map_attr.input_addr & alignment_mask) != 0 ||
        (map_attr.output_addr & alignment_mask) != 0) {
        return MMU_EBADADDR;
    }

    /* Address range for this operation */
    remaining_size = map_attr.size;
    current_va = map_attr.input_addr;

    /* Set up the parameters for our table walk */
    current_level = pt->table_level;
    pt_base_stack[current_level] = (uintptr_t) pt->pt_base;

    /* Setup a bit mask for masking the bits that index each page table */
    index_bit_mask = (1 << address_bits_per_lookup[granule_size]) - 1;

    /* Loop and create mappings until we have covered the requested mapping
     * size
     */
    while (remaining_size > 0) {
        /* Figure out which bits index this level */
        index_bits = current_va >>
            (bit_range_at_level[granule_size][current_level]);
        /* Mask off any unneeded bits */
        index_bits &= index_bit_mask;
        /* Find the table descriptor for this set of index bits */
        pt_descriptor = (translation_table_descriptor_t*)
            (pt_base_stack[current_level] | (index_bits << 3));
        /* Update the current virtual address, physical address, and block
         * size
         */
        block_size = 1UL << bit_range_at_level[granule_size][current_level];

        /* Do something with this entry (skip, fill, create sub-table) */
        params->level = current_level;
        params->pt_descriptor = pt_descriptor;
        params->offset = map_attr.size - remaining_size;
        status = mmu_apply_action(params, &entry_action);
        if (status != MMU_SUCCESS)
            return status;

        switch (entry_action) {
        case MMU_TW_NEXT_ENTRY:
            /* Move to the next entry, nothing to do here */
            break;
        case MMU_TW_CHANGE_LEVEL:
            /* Move down a level */
            current_level = current_level + 1;
            pt_base_stack[current_level] =
                mmu_get_table_address(pt_descriptor, granule_size);
            /* Restart the loop with the new level */
            continue;
        case MMU_TW_FINISHED:
            remaining_size = 0;
            break;
        default:
            /* We've encountered a failure, abort the table walk */
            return MMU_EFAILURE;
        }

        /* If this block is bigger than the remaining size, set remaining
         * size to 0
         */
        if (block_size > remaining_size) {
            current_va += remaining_size;
            remaining_size = 0;
        } else {
            current_va += block_size;
            remaining_size -= block_size;

            /* This was the last entry in the table at this level, move up
             * a level
             */
            if (index_bits == index_bit_mask)
                current_level = current_level - 1;
        }
    }

    return MMU_SUCCESS;
}

uintptr_t
mmu_get_table_address(translation_table_descriptor_t* pt_descriptor,
                      granule_size_t granule_size)
{
    uintptr_t address = 0;
    switch (granule_size) {
    case GRANULE_4KB:
        address = pt_descriptor->table_4k_granule.TBL_ADDR;
        break;
    case GRANULE_16KB:
        address = pt_descriptor->table_16k_granule.TBL_ADDR;
        break;
    case GRANULE_64KB:
        address = pt_descriptor->table_64k_granule.TBL_ADDR;
        break;
    }

    /* Shift the address to reconstruct it */
    address <<= granule_resolution_in_bits[granule_size];
    /* Convert the physical address to a virtual address */
    address = mmu_get_virtual_address(address);
    return address;
}

uintptr_t
mmu_get_block_address(translation_table_descriptor_t* pt_descriptor,
                      uint32_t level, granule_size_t granule_size)
{
    uintptr_t address = 0;

    if (level == 1 && granule_size == GRANULE_4KB)
        address = pt_descriptor->block_4k_granule_level_1.OUT_ADDR;
    else if (level == 2 && granule_size == GRANULE_4KB)
        address = pt_descriptor->block_4k_granule_level_2.OUT_ADDR;
    else if (level == 3 && granule_size == GRANULE_4KB)
        address = pt_descriptor->block_4k_granule_level_3.OUT_ADDR;
    else if (level == 2 && granule_size == GRANULE_16KB)
        address = pt_descriptor->block_16k_granule_level_2.OUT_ADDR;
    else if (level == 3 && granule_size == GRANULE_16KB)
        address = pt_descriptor->block_16k_granule_level_3.OUT_ADDR;
    else if (level == 2 && granule_size == GRANULE_64KB)
        address = pt_descriptor->block_64k_granule_level_2.OUT_ADDR;
    else if (level == 3 && granule_size == GRANULE_64KB)
        address = pt_descriptor->block_64k_granule_level_3.OUT_ADDR;

    /* Reconstruct the full address by shifting the appropriate amount */
    address <<= bit_range_at_level[granule_size][level];
    return address;
}

mmu_error_t
mmu_set_table_address(translation_table_descriptor_t* pt_descriptor,
                      uintptr_t address, granule_size_t granule_size)
{
    uintptr_t physical_address = mmu_get_physical_address(address);
    uintptr_t shifted_address =
        (physical_address & 0xFFFFFFFFFFFFLL) >>
        granule_resolution_in_bits[granule_size];

    if (granule_size == GRANULE_4KB)
        /* Store the table address in the table descriptor */
        pt_descriptor->table_4k_granule.TBL_ADDR = shifted_address;
    else if(granule_size == GRANULE_16KB)
        /* Store the table address in the table descriptor */
        pt_descriptor->table_16k_granule.TBL_ADDR = shifted_address;
    else
        /* Store the table address in the table descriptor */
        pt_descriptor->table_64k_granule.TBL_ADDR = shifted_address;
    return MMU_SUCCESS;
}

mmu_error_t
mmu_set_block_address(translation_table_descriptor_t* pt_descriptor,
                      uintptr_t address, uint32_t level,
                      granule_size_t granule_size)
{
    uintptr_t shifted_address =
        address >> bit_range_at_level[granule_size][level];

    if (level == 1 && granule_size == GRANULE_4KB) {
        pt_descriptor->block_4k_granule_level_1.IS_TBL = 0;
        pt_descriptor->block_4k_granule_level_1.OUT_ADDR = shifted_address;
    } else if(level == 2 && granule_size == GRANULE_4KB) {
        pt_descriptor->block_4k_granule_level_2.IS_TBL = 0;
        pt_descriptor->block_4k_granule_level_2.OUT_ADDR = shifted_address;
    } else if(level == 3 && granule_size == GRANULE_4KB) {
        pt_descriptor->block_4k_granule_level_3.IS_PAGE = 1;
        pt_descriptor->block_4k_granule_level_3.OUT_ADDR = shifted_address;
    } else if(level == 2 && granule_size == GRANULE_16KB) {
        pt_descriptor->block_16k_granule_level_2.IS_TBL = 0;
        pt_descriptor->block_16k_granule_level_2.OUT_ADDR = shifted_address;
    } else if(level == 3 && granule_size == GRANULE_16KB) {
        pt_descriptor->block_16k_granule_level_3.IS_PAGE = 1;
        pt_descriptor->block_16k_granule_level_3.OUT_ADDR = shifted_address;
    } else if(level == 2 && granule_size == GRANULE_64KB) {
        pt_descriptor->block_64k_granule_level_2.IS_TBL = 0;
        pt_descriptor->block_64k_granule_level_2.OUT_ADDR = shifted_address;
    } else if(level == 3 && granule_size == GRANULE_64KB) {
        pt_descriptor->block_64k_granule_level_3.IS_PAGE = 1;
        pt_descriptor->block_64k_granule_level_3.OUT_ADDR = shifted_address;
    } else
        return MMU_EUNEXPECTED;
    return MMU_SUCCESS;
}

mmu_error_t
mmu_cache_attribute_to_mair(translation_table_t* pt,
                            cache_attr_t cache_attr,
                            uint8_t* mairIndex)
{
    uint8_t i;

    if (mairIndex == NULL)
        return MMU_EBADPARAM;
    for (i = 0; i < 8; i++) {
        if (((pt->attr.mair >> (8 * i)) & 0xFF) == cache_attr) {
            *mairIndex = i;
            return MMU_SUCCESS;
        }
    }
    return MMU_ENOTALLOWED;
}

mmu_error_t
mmu_encode_block_permissions(translation_table_t* pt,
                             const mmu_map_attr_t* map_attr,
                             translation_table_descriptor_t* attributes)
{
    uint8_t mairIndex;
    mmu_error_t status;

    memset((void*) attributes, 0, sizeof(translation_table_descriptor_t));

    /* Validate that this set of permissions is allowed by the MMU
     * specification Grab all of the User/Priviledged read/write bits
     */
    switch (map_attr->perm_attr & PERM_RW) {
    case (PERM_P_R | PERM_P_W):
        attributes->block_common.AP = 0;
        break;
    case (PERM_P_R | PERM_P_W | PERM_U_R | PERM_U_W):
        attributes->block_common.AP = 1;
        break;
    case (PERM_P_R):
        attributes->block_common.AP = 2;
        break;
    case (PERM_P_R | PERM_U_R):
        attributes->block_common.AP = 3;
        break;
    default:
        return MMU_ENOTALLOWED;
    }

    /* Set User eXecutable bits */
    if (map_attr->perm_attr & PERM_U_X)
         /* User eXecute Never OFF */
         attributes->block_common.UXN = 0;
    else
         /* User eXecute Never */
         attributes->block_common.UXN = 1;

    /* Set Priviledged eXecutable bits */
    if (map_attr->perm_attr & PERM_P_X) {
#ifndef CONFIG_MMU_SELF_MODIFY
        /* Priviledged code can't execute memory that they is writable by
         * users
         */
        if (map_attr->perm_attr & PERM_U_W)
            return MMU_ENOTALLOWED;
#endif
         /* Priviledged eXecute Never OFF */
         attributes->block_common.PXN = 0;
    } else
         /* Priviledged eXecute Never */
         attributes->block_common.PXN = 1;

    /* Convert the cache attribute to a MAIR index */
    status = mmu_cache_attribute_to_mair(pt, map_attr->cache_attr,
                                         &mairIndex);
    if (MMU_SUCCESS != status)
        return status;

    /* Store the memory attribute type */
    attributes->block_common.ATTR_INDX = mairIndex;

    /* Set the shareability attribute if it is valid. */
    if (map_attr->share_attr == SHARE_NONE ||
        map_attr->share_attr == SHARE_INNER ||
        map_attr->share_attr == SHARE_OUTER) {
        attributes->block_common.SH = map_attr->share_attr;
    } else
        return MMU_EBADPARAM;

    /* Set the non-global bit to manage TLB scope with respect to ASIDs */
    attributes->block_common.NG = map_attr->global ? 0 : 1;
    attributes->block_common.AF = 1; // access flag
    /* Set the NS value to 0 if the user has requested a secure mapping */
    if (pt->attr.secure)
        attributes->block_common.NS = map_attr->secure ? 0 : 1;
    else
        /* If this isn't a secure domain then all mappings are
         * non-secure
         */
        attributes->block_common.NS = 1;
    return MMU_SUCCESS;
}

mmu_error_t
mmu_create_translation_table(translation_table_t* pt,
                             translation_table_descriptor_t* pt_descriptor,
                             const table_attr_t *tbl_attr)
{
    mmu_error_t status;
    size_t next_table_size;
    uintptr_t next_table;
    granule_size_t granule_size;

    if (pt == NULL || pt_descriptor == NULL || tbl_attr == NULL)
        return MMU_EBADPARAM;

    /* Extract the granule size for this domain */
    granule_size = pt->attr.granule_size;

    /* Allocate the next table */
    /* Caculate the number of entires in the table * table descriptor size
     * (all granules have the same sized descriptors)
     */
    /* the number of entries in the table depends on how many address bits
     * are resolved per table
     */
    next_table_size = sizeof(pt_descriptor->table_common) *
                      (1 << address_bits_per_lookup[granule_size]);
    next_table = (uintptr_t)mmu_allocate_aligned(next_table_size,
                                                 next_table_size,
                                                 pt->attr.secure);
    if (!next_table)
        return MMU_ENOMEMORY;

    /* Zero out the new page table */
    memset ((void*) next_table, 0, next_table_size);

    /* Set the parameters that are granule invariant */
    pt_descriptor->table_common.VALID = 1;
    pt_descriptor->table_common.IS_TBL = 1;
    pt_descriptor->table_common.IGNORE = 0;
    /* Items below are RESERVED 0 for stage 2 translation */
    pt_descriptor->table_common.PXN_TBL = tbl_attr->S1.PXN;
    pt_descriptor->table_common.XN_TBL = tbl_attr->S1.XN;
    pt_descriptor->table_common.AP_TBL = tbl_attr->S1.AP;
    pt_descriptor->table_common.NS_TBL = tbl_attr->S1.NS;

    /* Set the address */
    status = mmu_set_table_address(pt_descriptor, next_table,
                                   granule_size);
    if (MMU_SUCCESS != status)
        return status;

    return MMU_SUCCESS;
}

mmu_error_t
mmu_free_translation_table(translation_table_t *pt,
                           const mmu_tlb_attr_t *tlb,
                           translation_table_descriptor_t *table_start,
                           uintptr_t va, uint8_t level)
{
    mmu_error_t status = MMU_SUCCESS;
    granule_size_t granule_size;
    size_t table_size;
    uint32_t table_entries;
    uintptr_t entry_va;
    int entry;

    /* Validate input parameters */
    if (pt == NULL || table_start == NULL ||
        level > 3 || level < pt->table_level)
        return MMU_EBADPARAM;

    /* Extract the granule size for this domain */
    granule_size = pt->attr.granule_size;

    /* This is the root table, it could be smaller than the standard table
     * size
     */
    if (level == pt->table_level)
        table_entries = pt->table_entry_count;
    else
        /* If a table is not a root table, it must be full sized (the root
         * tables is the only table that can cover fewer address bits then
         * defined by address_bits_per_lookup[granule_size])
         */
        table_entries = 1 << address_bits_per_lookup[granule_size];

    for (entry = 0; entry < table_entries; entry++) {
        /* Get the virtual address that corresponds to this entry in the
         * table
         */
        entry_va = va +
            entry * (1ULL << bit_range_at_level[granule_size][level]);

        /* If this table is at level 0, 1, or 2 it could have sub-tables,
         * so we need to find any subtables and free them
         */
        if (level < 3 &&
            table_start[entry].table_common.VALID &&
            table_start[entry].table_common.IS_TBL) {
            status = mmu_free_translation_table(pt, tlb,
                (translation_table_descriptor_t*)
                    mmu_get_table_address(&table_start[entry],
                                          granule_size),
                entry_va, level + 1);
            if (MMU_SUCCESS != status)
                return status;
        } else if(table_start[entry].block_common.VALID) {
            /* Invalidate any block or page descriptors in the table that
             * we are about to free
             */
            /* Mark this descriptor as invalid before flushing the TLB
             * This ensures that any new fetches will not pick up the TLB
             * before we zero out th etable
             */
            table_start[entry].block_common.VALID = 0;
            status = mmu_invalidate_tlb_va(tlb, pt->va_base + entry_va,
                                           pt->attr.asid);
            if (MMU_SUCCESS != status)
                return status;
        }
    }

    /* Calculate the size of the table so we can zero it and free it*/
    table_size = sizeof(translation_table_descriptor_t) * table_entries;

    /* Clear out the memory so we don't accidently pick up any stale
     * mappings
     */
    memset(table_start, 0, table_size);
    mmu_free_aligned(table_start, table_size, pt->attr.secure);
    return status;
}

uint8_t mmu_determine_block_level(translation_table_t* pt,
                                  uintptr_t va, uintptr_t pa,
                                  size_t size)
{
    uint8_t block_level;
    size_t block_size;

    /* Determine what page level this block can be mapped at */
    for (block_level = pt->table_level; block_level <= 3; block_level++) {
        /* Determine the size of block at this level and if it aligns with
         * our input/output addresses and size
         */
        block_size = block_size_per_level[pt->attr.granule_size][block_level];
        if (block_size != 0 &&
            (va & (block_size - 1)) == 0 &&
            (pa & (block_size - 1)) == 0 &&
            size >= block_size) {
            /* Found the appropriate block level for this block descriptor
             */
            break;
        }
    }
    return block_level;
}

mmu_error_t mmu_split_block_descriptor(
    translation_table_t *pt,
    translation_table_descriptor_t *pt_descriptor,
    const table_attr_t *default_attributes, uint8_t level)
{
    /* Split this block descriptor into a new translation table */
    uintptr_t current_pa, pt_base;
    granule_size_t granule_size = pt->attr.granule_size;
    mmu_error_t status = MMU_EFAILURE;
    translation_table_descriptor_t old_block_descriptor = *pt_descriptor;
    uint32_t index;

    /* Use the default attributes when creating the new table, the block
     * attributes will get propagated to the new blocks created in this
     * table
     */
    status = mmu_create_translation_table(pt, pt_descriptor,
                                          default_attributes);
    if (status != MMU_SUCCESS)
        return status;

    /* The the page table base to point to the next level of page tables */
    pt_base = mmu_get_table_address(pt_descriptor, granule_size);

    /* Point the page table descriptor at the base of the new page table */
    pt_descriptor = (translation_table_descriptor_t*) pt_base;

    /* Determine the current output PA */
    current_pa = mmu_get_block_address(&old_block_descriptor, level,
                                       granule_size);

    /* Populate the new page table with the larger block descriptors
     * information
     */
    for (index = 0;
         index < (1ULL << address_bits_per_lookup[granule_size]);
         index++) {
        /* Copy all the old values into the new block */
        pt_descriptor->block_common = old_block_descriptor.block_common;

        /* Clear out the values that will change */
        pt_descriptor->block_common.IGNORE1 = 0;
        pt_descriptor->block_common.IGNORE2 = 0;
        pt_descriptor->block_common.CONTIG = 0; /* TODO: Enable Contig Hints */

        /* Set the PA output mapping */
        status = mmu_set_block_address(pt_descriptor, current_pa,
                                       level + 1, granule_size);
        if (MMU_SUCCESS != status)
            return status;

        /* Go to the next entry in the table, this increment will move
         * sizeof(translation_table_descriptor_t) bytes (8 bytes)
         */
        pt_descriptor++;
        /* Increment the PA */
        current_pa += block_size_per_level[granule_size][level + 1];
    }

    return MMU_SUCCESS;
}

mmu_error_t mmu_apply_action(mmu_action_parameters_t *params,
                             mmu_table_walk_action_t *entry_action)
{
    mmu_error_t status = MMU_EFAILURE;
    bool valid, block;
    uintptr_t current_va, current_pa;
    size_t remaining_size;
    uint8_t desired_level;
    translation_table_t* pt = params->pt;
    translation_table_descriptor_t* pt_descriptor = params->pt_descriptor;
    mmu_page_table_action_t action = params->action_type;
    uint8_t level = params->level;

    current_va = params->map_attr->input_addr + params->offset;
    current_pa = params->map_attr->output_addr + params->offset;
    remaining_size = params->map_attr->size - params->offset;

    /* See what level we should be at to map this block */
    desired_level = mmu_determine_block_level(pt, current_va,
                                              current_pa,
                                              remaining_size);

    /* Determine what we're working with here */
    if (pt_descriptor->block_common.VALID == 0) {
        valid = false;
    } else if (level == 3 ||
             (level < 3 && pt_descriptor->table_common.IS_TBL == 0)) {
        valid = true;
        block = true;
    } else {
        valid = true;
        block = false;
    }

    /* Perform action */
    if (action == MMU_ACTION_MAP) {
        if (level < desired_level) {
            /* Only create a sub-table for map, other actions only deal
             * with existing entries
             */
            if (valid == false) {
                /* Create table */
                status = mmu_create_translation_table(pt, pt_descriptor,
                    &params->table_attributes);
                if (status != MMU_SUCCESS)
                    return status;
            } else if (block == true) {
                /* Split this block into a new table so we can traverse
                 * downward
                 */
                status = mmu_split_block_descriptor(pt, pt_descriptor,
                    &params->table_attributes, level);
                if (status != MMU_SUCCESS)
                    return status;
            }
            /* We have a valid table to traverse now */
            *entry_action = MMU_TW_CHANGE_LEVEL;
        } else {
            /* Pre-existing table, free it */
            if (valid && block == false) {
                status = mmu_free_translation_table(pt, params->tlb,
                    (translation_table_descriptor_t*)
                    mmu_get_table_address(pt_descriptor,
                                          pt->attr.granule_size),
                    current_va, level + 1);
                if (MMU_SUCCESS != status)
                    return status;
                /* Zero out the freed table entry */
                memset(pt_descriptor, 0,
                       sizeof (translation_table_descriptor_t));
            }

            /* We are mapping entries */
            /* Set up the shared attributes across blocks (like permissions
             * and sharability)
             */
            pt_descriptor->block_common =
                params->action.map.block_attributes.block_common;
            /* Clear out the values that will change from block to block */
            pt_descriptor->block_common.IGNORE1 = 0;
            pt_descriptor->block_common.IGNORE2 = 0;
            /* TODO: Enable Contig Hints */
            pt_descriptor->block_common.CONTIG = 0;

            /* Set the level and granule specific values */
            status = mmu_set_block_address(pt_descriptor, current_pa,
                                           level, pt->attr.granule_size);
            if (MMU_SUCCESS != status)
                return status;

            /* Move to the next block */
            *entry_action = MMU_TW_NEXT_ENTRY;
        }
    } else if (action == MMU_ACTION_UNMAP && valid) {
        if (valid == false) {
            /* Nothing to do for invalid entries, on to the next one */
            *entry_action = MMU_TW_NEXT_ENTRY;
        } else if (level < desired_level) {
            /* Split this block into a new table so we can traverse
             * downward
             */
            if (block == true) {
                status = mmu_split_block_descriptor(pt, pt_descriptor,
                                                    &params->table_attributes,
                                                    level);
                if(status != MMU_SUCCESS)
                    return status;
            }
            /* We have a valid table to traverse now */
            *entry_action = MMU_TW_CHANGE_LEVEL;
        } else {
            /* We've encountered a table, free the table and zero it out */
            if (block == false) {
                status = mmu_free_translation_table(pt, params->tlb,
                    (translation_table_descriptor_t*)
                    mmu_get_table_address(pt_descriptor,
                                          pt->attr.granule_size),
                    current_va, level + 1);
                if (MMU_SUCCESS != status)
                    return status;
                /* Zero out the freed table entry */
                memset(pt_descriptor, 0,
                       sizeof (translation_table_descriptor_t));
            } else {
                /* This is a valid block */
                /* Zero out the freed table entry */
                memset(pt_descriptor, 0,
                       sizeof (translation_table_descriptor_t));
            }
            /* Move to the next block */
            *entry_action = MMU_TW_NEXT_ENTRY;
        }
    } else if (action == MMU_ACTION_CHANGE_ATTR) {
        if (valid == false) {
            /* Nothing to do for invalid entries, on to the next one */
            *entry_action = MMU_TW_NEXT_ENTRY;
        } else if(level < desired_level) {
            /* Split this block into a new table so we can traverse
             * downward
             */
            if (block == true) {
                status = mmu_split_block_descriptor(pt, pt_descriptor,
                    &params->table_attributes, level);
                if (status != MMU_SUCCESS)
                    return status;
            }
            /* We have a valid table to traverse now */
            *entry_action = MMU_TW_CHANGE_LEVEL;
        } else {
            /* We've encountered a table, traverse down and modify those
             * entries
             */
            if (block == false) {
                *entry_action = MMU_TW_CHANGE_LEVEL;
            } else {
                /* This is a valid block */
                /* Set the new attributes for the block while preserving
                 * the address translation, valid, and reserved fields
                 */
                pt_descriptor->block_common.ATTR_INDX = params->action.change_attr.block_attributes.block_common.ATTR_INDX;
                pt_descriptor->block_common.NS = params->action.change_attr.block_attributes.block_common.NS;
                pt_descriptor->block_common.AP = params->action.change_attr.block_attributes.block_common.AP;
                pt_descriptor->block_common.SH = params->action.change_attr.block_attributes.block_common.SH;
                pt_descriptor->block_common.AF = params->action.change_attr.block_attributes.block_common.AF;
                pt_descriptor->block_common.NG = params->action.change_attr.block_attributes.block_common.NG;
                pt_descriptor->block_common.PXN = params->action.change_attr.block_attributes.block_common.PXN;
                pt_descriptor->block_common.UXN = params->action.change_attr.block_attributes.block_common.UXN;

                /* Move to the next block */
                *entry_action = MMU_TW_NEXT_ENTRY;
            }
        }
    } else if (action == MMU_ACTION_LOOKUP_PAGE) {
        if (valid == false) {
            /* This page isn't mapped, return failure */
            return MMU_EBADADDR;
        } else {
            /* We've encountered a table, traverse down to find a block
             * descriptor
             */
            if (block == false) {
                *entry_action = MMU_TW_CHANGE_LEVEL;
            } else {
                /* This is a valid block */
                /* Store the block attributes for this mapping */
                params->action.lookup_page.block_attributes.block_common = pt_descriptor->block_common;

                /* We have found a mapping, we are done */
                *entry_action = MMU_TW_FINISHED;
            }
        }
    } else if (action == MMU_ACTION_WALK_TABLES) {
        /* Update the current virtual address, physical address, and block
         * size
         */
        size_t block_size;

        block_size = 1UL << bit_range_at_level[pt->attr.granule_size][level];
        if (valid == false) {
            mmu_log(MMU_LOG_INFO,
                    "Virtual Address: 0x%lx, level: %d, size: %zuKB, IS NOT MAPPED \r\n",
                    current_va, level, block_size / 1024);
            *entry_action = MMU_TW_NEXT_ENTRY;
        } else if (block == true) {
            /* This is a block descriptor */
            mmu_log(MMU_LOG_INFO,
                    "Virtual Address: 0x%lx, level: %d, size: %zuKB IS A BLOCK \r\n",
                    current_va, level, block_size / 1024);
            *entry_action = MMU_TW_NEXT_ENTRY;
        } else {
            /* This is a table descriptor */
            mmu_log(MMU_LOG_INFO,
                    "Virtual Address: 0x%lx, level: %d, size: %zuKB IS A TABLE \r\n",
                    current_va, level, block_size / 1024);
            *entry_action = MMU_TW_CHANGE_LEVEL;
        }
    }

    /* Only invalidate if something was already in this entry */
    if (valid && params->tlb != NULL) {
        /* Invalidate any existing TLB entry for this virtual address */
        status = mmu_invalidate_tlb_va(params->tlb,
                                       pt->va_base + current_va,
                                       pt->attr.asid);
        if (status != MMU_SUCCESS)
            return status;
    }

    return MMU_SUCCESS;
}
