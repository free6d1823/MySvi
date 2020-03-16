/* Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
#ifndef MMU_HELPERS_H
#define MMU_HELPERS_H

#include <target/mmu.h>

typedef enum {
	MMU_REGION_NORMAL = 0,
	MMU_REGION_NORMAL_NON_CACHED,
	MMU_REGION_DEVICE,
	MMU_REGION_NON_SECURE_NORMAL,
	MMU_REGION_NON_SECURE_NON_CACHED,
	MMU_REGION_NON_SECURE_DEVICE,
} mmu_region_type_e;

/* Structure to describe memory region and its permissions.
 * There is only one field for address for linear mappings.
 */
typedef struct {
	uint64_t address;
	uint64_t size;
	perm_attr_t permissions;
	mmu_region_type_e type;
} mem_linear_region_t;

typedef struct {
	uint64_t virtual_address;
	uint64_t physical_address;
	uint64_t size;
	perm_attr_t permissions;
	mmu_region_type_e type;
} mem_region_t;

/* HMSS/FPSS helpers.
 * Notes about helper functions:
 * 1) Mapping functions have to be used carefully. They must only
 *    be used on regions that are not already mapped. This is because
 *    we dont invalidate TLB's during the map calls, for efficiency.
 *    if the mapping functions are used on partially mapped or already
 *    mapped regions, we will start seeing coherency issues.
 * 2) Unammping functions always use broadcast invalidate TLB and must
 *    be used judiciously. For EL3, there should be no reason to ever
 *    invalidate entries.
 * 3) To update permissions/attributes, we must first unmap the region
 *    and then remap it with new attributes/permissions. This is in
 *    keeping with the ARM ARM's recommendation of break-before-make to
 *    avoid coherency issues.
 * 4) Validation of mapped, partially mapped or unmapped regions must be
 *    done outside the below function calls.
 * 5) Always check error code.
 */

mmu_error_t map_multiple_linear_regions(translation_table_t *pt,
		mem_linear_region_t *regions, uint32_t number_of_regions);

mmu_error_t map_multiple_regions(translation_table_t *pt,
		mem_region_t *regions, uint32_t number_of_regions);

mmu_error_t map_normal_memory(translation_table_t *pt, uint64_t va,
		uint64_t pa, uint64_t size, perm_attr_t permissions);

mmu_error_t map_normal_non_cached_memory(translation_table_t *pt, uint64_t va,
		uint64_t pa, uint64_t size, perm_attr_t permissions);

mmu_error_t map_device_memory(translation_table_t *pt, uint64_t va,
		uint64_t pa, uint64_t size, perm_attr_t permissions);

mmu_error_t map_normal_memory_linear(translation_table_t *pt, uint64_t address,
		uint64_t size, perm_attr_t permissions);

mmu_error_t map_device_memory_linear(translation_table_t *pt, uint64_t address,
		uint64_t size, perm_attr_t permissions);

mmu_error_t map_normal_non_cached_memory_linear(translation_table_t *pt,
		uint64_t address, uint64_t size, perm_attr_t permissions);

/* TZ specific functions. The following apis can be used to map non secure
 * memory in secure world.
 */
mmu_error_t map_non_secure_normal_memory(translation_table_t *pt, uint64_t va,
		uint64_t pa, uint64_t size, perm_attr_t permissions);

mmu_error_t map_non_secure_normal_non_cached_memory(translation_table_t *pt,
		uint64_t va, uint64_t pa, uint64_t size, perm_attr_t permissions);

mmu_error_t map_non_secure_device_memory(translation_table_t *pt, uint64_t va,
		uint64_t pa, uint64_t size, perm_attr_t permissions);

mmu_error_t map_non_secure_normal_memory_linear(translation_table_t *pt,
		uint64_t address, uint64_t size, perm_attr_t permissions);

mmu_error_t map_non_secure_device_memory_linear(translation_table_t *pt,
		uint64_t address, uint64_t size, perm_attr_t permissions);

mmu_error_t map_non_secure_normal_non_cached_memory_linear(
		translation_table_t *pt, uint64_t address, uint64_t size,
		perm_attr_t permissions);

#endif /* MMU_HELPERS_H */
