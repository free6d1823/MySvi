#ifndef __ARM64_MMU_INTERNAL_H_INCLUDE__
#define __ARM64_MMU_INTERNAL_H_INCLUDE__

/*==============================================================================
@file mmu_internal.h

        Copyright (c) 2016 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Confidential and Proprietary - Qualcomm Technologies, Inc.

==============================================================================*/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <target/mmu.h>
#include <target/mmu_port.h>

/*=============================================================================
* Defines
=============================================================================*/
 #define  SIZE_1KB    0x00000400
 #define  SIZE_2KB    0x00000800
 #define  SIZE_4KB    0x00001000
 #define  SIZE_8KB    0x00002000
 #define  SIZE_16KB   0x00004000
 #define  SIZE_32KB   0x00008000
 #define  SIZE_64KB   0x00010000
 #define  SIZE_128KB  0x00020000
 #define  SIZE_256KB  0x00040000
 #define  SIZE_512KB  0x00080000
 #define  SIZE_1MB    0x00100000
 #define  SIZE_2MB    0x00200000
 #define  SIZE_4MB    0x00400000
 #define  SIZE_8MB    0x00800000
 #define  SIZE_16MB   0x01000000
 #define  SIZE_32MB   0x02000000
 #define  SIZE_64MB   0x04000000
 #define  SIZE_128MB  0x08000000
 #define  SIZE_256MB  0x10000000
 #define  SIZE_512MB  0x20000000
 #define  SIZE_1GB    0x40000000
 #define  SIZE_2GB    0x80000000
 #define  SIZE_4GB    0x0000000100000000ULL
 #define  SIZE_8GB    0x0000000200000000ULL
 #define  SIZE_16GB   0x0000000400000000ULL

/*=============================================================================
 * Types
 =============================================================================*/
// table attributes for page table
typedef union {
    struct {
      unsigned PXN:1;
      unsigned XN:1;
      unsigned AP:1;
      unsigned NS:1;
    } S1; /* stage 1 */
    /* should be zero for stage 2 */
    uint8_t raw;
} table_attr_t;

/* table descriptor definitions */
typedef union {
    struct {
        uint64_t VALID:1;
        uint64_t IS_TBL:1;
        uint64_t IGNORE:57;
        /* Items below are RESERVED 0 for stage 2 translation */
        uint64_t PXN_TBL:1;
        uint64_t XN_TBL:1;
        uint64_t AP_TBL:2;
        uint64_t NS_TBL:1;
    } table_common;
    struct {
        uint64_t VALID:1;
        uint64_t IS_TBL:1;
        uint64_t IGNORE1:10;
        uint64_t TBL_ADDR:36;
        uint64_t RESERVED:4;
        uint64_t IGNORE2:7;
        /* Items below are RESERVED 0 for stage 2 translation */
        uint64_t PXN_TBL:1;
        uint64_t XN_TBL:1;
        uint64_t AP_TBL:2;
        uint64_t NS_TBL:1;
    } table_4k_granule;
    struct {
        uint64_t VALID:1;
        uint64_t IS_TBL:1;
        uint64_t IGNORE1:12;
        uint64_t TBL_ADDR:34;
        uint64_t RESERVED:4;
        uint64_t IGNORE2:7;
        /* Items below are RESERVED 0 for stage 2 translation */
        uint64_t PXN_TBL:1;
        uint64_t XN_TBL:1;
        uint64_t AP_TBL:2;
        uint64_t NS_TBL:1;
    } table_16k_granule;
    struct {
        uint64_t VALID:1;
        uint64_t IS_TBL:1;
        uint64_t IGNORE1:14;
        uint64_t TBL_ADDR:32;
        uint64_t RESERVED:4;
        uint64_t IGNORE2:7;
        /* Items below are RESERVED 0 for stage 2 translation */
        uint64_t PXN_TBL:1;
        uint64_t XN_TBL:1;
        uint64_t AP_TBL:2;
        uint64_t NS_TBL:1;
    } table_64k_granule;
    struct {
        uint64_t VALID:1;
        uint64_t IGNORE1:1;
        uint64_t ATTR_INDX:3;
        uint64_t NS:1;
        uint64_t AP:2;
        uint64_t SH:2;
        uint64_t AF:1;
        uint64_t NG:1;
        uint64_t IGNORE2:40;
        uint64_t CONTIG:1;
        uint64_t PXN:1;
        uint64_t UXN:1;
        uint64_t FOR_SW_USE:4;
        uint64_t IGNORED:5;
    } block_common;
    struct {
        uint64_t VALID:1;
        uint64_t IS_TBL:1;
        uint64_t ATTR_INDX:3;
        uint64_t NS:1;
        uint64_t AP:2;
        uint64_t SH:2;
        uint64_t AF:1;
        uint64_t NG:1;
        uint64_t RESERVED1:18;
        uint64_t OUT_ADDR:18;
        uint64_t RESERVED2:4;
        uint64_t CONTIG:1;
        uint64_t PXN:1;
        uint64_t UXN:1;
        uint64_t FOR_SW_USE:4;
        uint64_t IGNORED:5;
    } block_4k_granule_level_1;
    struct {
        uint64_t VALID:1;
        uint64_t IS_TBL:1;
        uint64_t ATTR_INDX:3;
        uint64_t NS:1;
        uint64_t AP:2;
        uint64_t SH:2;
        uint64_t AF:1;
        uint64_t NG:1;
        uint64_t RESERVED1:9;
        uint64_t OUT_ADDR:27;
        uint64_t RESERVED2:4;
        uint64_t CONTIG:1;
        uint64_t PXN:1;
        uint64_t UXN:1;
        uint64_t FOR_SW_USE:4;
        uint64_t IGNORED:5;
    } block_4k_granule_level_2;
    struct {
        uint64_t VALID:1;
        uint64_t IS_PAGE:1;
        uint64_t ATTR_INDX:3;
        uint64_t NS:1;
        uint64_t AP:2;
        uint64_t SH:2;
        uint64_t AF:1;
        uint64_t NG:1;
        uint64_t OUT_ADDR:36;
        uint64_t RESERVED2:4;
        uint64_t CONTIG:1;
        uint64_t PXN:1;
        uint64_t UXN:1;
        uint64_t FOR_SW_USE:4;
        uint64_t IGNORED:5;
    } block_4k_granule_level_3;
    struct {
        uint64_t VALID:1;
        uint64_t IS_TBL:1;
        uint64_t ATTR_INDX:3;
        uint64_t NS:1;
        uint64_t AP:2;
        uint64_t SH:2;
        uint64_t AF:1;
        uint64_t NG:1;
        uint64_t RESERVED1:13;
        uint64_t OUT_ADDR:23;
        uint64_t RESERVED2:4;
        uint64_t CONTIG:1;
        uint64_t PXN:1;
        uint64_t UXN:1;
        uint64_t FOR_SW_USE:4;
        uint64_t IGNORED:5;
    } block_16k_granule_level_2;
    struct {
        uint64_t VALID:1;
        uint64_t IS_PAGE:1;
        uint64_t ATTR_INDX:3;
        uint64_t NS:1;
        uint64_t AP:2;
        uint64_t SH:2;
        uint64_t AF:1;
        uint64_t NG:1;
        uint64_t RESERVED1:2;
        uint64_t OUT_ADDR:34;
        uint64_t RESERVED2:4;
        uint64_t CONTIG:1;
        uint64_t PXN:1;
        uint64_t UXN:1;
        uint64_t FOR_SW_USE:4;
        uint64_t IGNORED:5;
    } block_16k_granule_level_3;
    struct {
        uint64_t VALID:1;
        uint64_t IS_TBL:1;
        uint64_t ATTR_INDX:3;
        uint64_t NS:1;
        uint64_t AP:2;
        uint64_t SH:2;
        uint64_t AF:1;
        uint64_t NG:1;
        uint64_t RESERVED1:17;
        uint64_t OUT_ADDR:19;
        uint64_t RESERVED2:4;
        uint64_t CONTIG:1;
        uint64_t PXN:1;
        uint64_t UXN:1;
        uint64_t FOR_SW_USE:4;
        uint64_t IGNORED:5;
    } block_64k_granule_level_2;
    struct {
        uint64_t VALID:1;
        uint64_t IS_PAGE:1;
        uint64_t ATTR_INDX:3;
        uint64_t NS:1;
        uint64_t AP:2;
        uint64_t SH:2;
        uint64_t AF:1;
        uint64_t NG:1;
        uint64_t RESERVED1:4;
        uint64_t OUT_ADDR:32;
        uint64_t RESERVED2:4;
        uint64_t CONTIG:1;
        uint64_t PXN:1;
        uint64_t UXN:1;
        uint64_t FOR_SW_USE:4;
        uint64_t IGNORED:5;
    } block_64k_granule_level_3;
} translation_table_descriptor_t;

typedef union {
    struct {
        uint64_t F:1;
        uint64_t RESERVED:6;
        uint64_t SH:2;
        uint64_t NS:1;
        uint64_t IMP_DEF:1;
        uint64_t RESERVED1:1;
        uint64_t PA:36;
        uint64_t RESERVED2:8;
        uint64_t ATTR:8;
    } success;
    struct {
        uint64_t F:1;
        uint64_t FST:6;
        uint64_t RESERVED:1;
        uint64_t PTW:1;
        uint64_t S:1;
        uint64_t RESERVED1:54;
    } failure;
} par_result_t;

typedef union {
    struct {
        uint64_t T0SZ:6;
        uint64_t RESERVED:1;
        uint64_t EPD0:1;
        uint64_t IRGN0:2;
        uint64_t ORGN0:2;
        uint64_t SH0:2;
        uint64_t TG0:2;
        uint64_t T1SZ:6;
        uint64_t A1:1;
        uint64_t EPD1:1;
        uint64_t IRGN1:2;
        uint64_t ORGN1:2;
        uint64_t SH1:2;
        uint64_t TG1:2;
        uint64_t IPS:3;
        uint64_t RESERVED1:1;
        uint64_t AS:1;
        uint64_t TBI0:1;
        uint64_t TBI1:1;
        uint64_t RESERVED2:25;
    } el1;
    struct {
        uint64_t T0SZ:6;
        uint64_t RESERVED:2;
        uint64_t IRGN0:2;
        uint64_t ORGN0:2;
        uint64_t SH0:2;
        uint64_t TG0:2;
        uint64_t PS:3;
        uint64_t RESERVED1:1;
        uint64_t TBI:1;
        uint64_t RESERVED2:11;
    } el2;
    struct {
        uint64_t T0SZ:6;
        uint64_t RESERVED:2;
        uint64_t IRGN0:2;
        uint64_t ORGN0:2;
        uint64_t SH0:2;
        uint64_t TG0:2;
        uint64_t PS:3;
        uint64_t RESERVED1:1;
        uint64_t TBI:1;
        uint64_t RESERVED2:11;
    } el3;
} tcr_elx_t;

static const uint32_t granule_resolution_in_bits[3] = {12, 14, 16};

static const uint32_t address_bits_per_lookup[3] = {9, 11, 13};

static const uint32_t bit_range_at_level[3][4] = {
    {39, 30, 21, 12},
    {47, 36, 25, 14},
    {55, 42, 29, 16},
};

static const uint64_t block_size_per_level[3][4] = {
    {0, SIZE_1GB, SIZE_2MB, SIZE_4KB},
    {0, 0, SIZE_32MB, SIZE_16KB},
    {0, 0, SIZE_512MB, SIZE_64KB},
};

typedef enum {
    MMU_ACTION_MAP,
    MMU_ACTION_UNMAP,
    MMU_ACTION_CHANGE_ATTR,
    MMU_ACTION_LOOKUP_PAGE,
    MMU_ACTION_WALK_TABLES
} mmu_page_table_action_t;

typedef struct {
    /* Parameters that only change in top level calls */
    translation_table_t* pt;
    table_attr_t table_attributes;
    mmu_page_table_action_t action_type;
    const mmu_map_attr_t* map_attr;
    const mmu_tlb_attr_t* tlb;

    /* Parameters that change while walking translation tables */
    translation_table_descriptor_t* pt_descriptor;
    size_t offset;
    uint8_t level;

    /* Parameters unique to certain actions */
    union {
        struct {
            translation_table_descriptor_t block_attributes;
        } map;
        struct {
            translation_table_descriptor_t block_attributes;
        } change_attr;
        struct {
            translation_table_descriptor_t block_attributes;
        } lookup_page;
    } action;
} mmu_action_parameters_t;

typedef enum {
    MMU_TW_NEXT_ENTRY,
    MMU_TW_CHANGE_LEVEL,
    MMU_TW_FINISHED
} mmu_table_walk_action_t;

extern const mmu_map_attr_t static_mmu_entry_list[];
extern UINT32 static_mmu_entry_list_len;

/*=============================================================================
 * Function Declarations
 =============================================================================*/
/* MMU Functions */
exception_level_t mmu_get_current_el(void);
mmu_error_t mmu_get_tcr_cache_attr(cache_attr_t cache_attr,
                                   uint8_t *inner, uint8_t *outer);
mmu_error_t mmu_get_tcr_output_size_encoding(uint32_t output_bit_size,
                                             uint8_t *encoded_val);
mmu_error_t mmu_validate_page_table_attributes(
    const mmu_translation_table_attr_t *pt_attr);

/* Page Table Functions */
mmu_error_t mmu_modify_translation_tables(mmu_action_parameters_t *params);
mmu_error_t mmu_walk_translation_tables(translation_table_t *pt,
                                        const uint64_t va,
                                        const size_t size);

uintptr_t mmu_get_table_address(
    translation_table_descriptor_t *pt_descriptor,
    granule_size_t granule_size);
uintptr_t mmu_get_block_address(
    translation_table_descriptor_t *pt_descriptor,
    uint32_t level, granule_size_t granule_size);
mmu_error_t mmu_set_table_address(
    translation_table_descriptor_t *pt_descriptor,
    uintptr_t address, granule_size_t granule_size);
mmu_error_t mmu_set_block_address(
    translation_table_descriptor_t *pt_descriptor,
    uintptr_t address, uint32_t level,
    granule_size_t granule_size);
mmu_error_t mmu_cache_attribute_to_mair(translation_table_t *pt,
                                        cache_attr_t cache_attr,
                                        uint8_t *mairIndex);
mmu_error_t mmu_encode_block_permissions(
    translation_table_t *pt, const mmu_map_attr_t *map_attr,
    translation_table_descriptor_t *attributes);
mmu_error_t mmu_create_translation_table(translation_table_t *pt,
    translation_table_descriptor_t *pt_descriptor,
    const table_attr_t *tbl_attr);
mmu_error_t mmu_free_translation_table(
    translation_table_t *pt, const mmu_tlb_attr_t* tlb,
    translation_table_descriptor_t *table_start,
    uintptr_t va,  uint8_t level);
uint8_t mmu_determine_block_level(translation_table_t *pt,
                                  uintptr_t va, uintptr_t pa, size_t size);
mmu_error_t mmu_split_block_descriptor(
    translation_table_t *pt,
    translation_table_descriptor_t *pt_descriptor,
    const table_attr_t *default_attributes,
    uint8_t level);
mmu_error_t mmu_apply_action(mmu_action_parameters_t *params,
                             mmu_table_walk_action_t* entry_action);

#endif /* __ARM64_MMU_INTERNAL_H_INCLUDE__*/
