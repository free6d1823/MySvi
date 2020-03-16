/*==============================================================================
@file mmu.h

        Copyright (c) 2016 Qualcomm Technologies, Inc.
        All Rights Reserved.
        Confidential and Proprietary - Qualcomm Technologies, Inc.

==============================================================================*/
#ifndef __TESTOS_MMU_H_INCLUDE__
#define __TESTOS_MMU_H_INCLUDE__

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// address size
typedef enum
{
    ADDR_SIZE_32 = 32,
    ADDR_SIZE_36 = 36,
    ADDR_SIZE_40 = 40,
    ADDR_SIZE_44 = 44,
    ADDR_SIZE_48 = 48
}
mmu_addr_size_t;

/* error codes */
typedef enum {
    MMU_SUCCESS = 0,
    MMU_EINVAL,
    MMU_EBADADDR,
    MMU_ERANGE,
    MMU_EUNEXPECTED,
    MMU_ENOTALLOWED,
    MMU_EFAILURE,
    MMU_EBADPARAM,
    MMU_ENOMEMORY,
    MMU_EALREADY,
    MMU_EUNSUPPORTED,
    MMU_EDEVICE
} mmu_error_t;

/* cache property */
typedef enum {
    /* Device memory types,
     * G = Gathering,
     * R = Reordering,
     * E = Early Write Acknowledgement
     */
    CACHE_DEVICE_nGnRnE       = 0x0,   /* b0000 b0000 */
    CACHE_DEVICE_nGnRE        = 0x4,   /* b0000 b0100 */
    CACHE_DEVICE_nGRE         = 0x8,   /* b0000 b1000 */
    CACHE_DEVICE_GRE          = 0xC,   /* b0000 b1100 */
    /* Outer non-cacheable types (Inner cache all read/write allocate) */
    CACHE_OUTER_NC_INNER_NC   = 0x44,  /* b0100 b0100 */
    CACHE_OUTER_NC_INNER_WT   = 0x4B,  /* b0100 b1000 */
    CACHE_OUTER_NC_INNER_WB   = 0x4F,  /* b0100 b1111 */
    /* Inner non-cacheable types (Outer cache all read/write allocate) */
    CACHE_OUTER_WT_INNER_NC   = 0xB4,  /* b1011 b0100 */
    CACHE_OUTER_WB_INNER_NC   = 0xF4,  /* b1111 b0100 */
    /* Outer/Inner cacheable types (all read/write allocate) */
    CACHE_OUTER_WT_INNER_WT   = 0xBB,  /* b1011 b1011 */
    CACHE_OUTER_WB_INNER_WT   = 0xFB,  /* b1111 b1000 */
    CACHE_OUTER_WT_INNER_WB   = 0xBF,  /* b1011 b1111 */
    CACHE_OUTER_WB_INNER_WB   = 0xFF,  /* b1111 b1111 */
    /* Default is Inner/Outer Write-back Cacheable */
    CACHE_DEFAULT             = 0xFF   /* b1111 b1111 */
} cache_attr_t;

/* sharability */
typedef enum {
    SHARE_NONE         = 0,
    SHARE_OUTER        = 2,
    SHARE_INNER        = 3,
    /* use stage 1 or non-cached */
    SHARE_DEFAULT      = 0,
} shareability_attr_t;

/* permission */
typedef enum {
    PERM_U_R      = 0x1,
    PERM_U_W      = 0x2,
    PERM_U_X      = 0x4,
    PERM_P_R      = 0x8,
    PERM_P_W      = 0x10,
    PERM_P_X      = 0x20,
    PERM_R      = PERM_U_R | PERM_P_R,
    PERM_RW     = PERM_U_R | PERM_U_W | PERM_P_R | PERM_P_W,
    PERM_RX     = PERM_U_R | PERM_U_X | PERM_P_R | PERM_P_X,
#ifdef CONFIG_MMU_SELF_MODIFY
    PERM_RWX    = PERM_U_R | PERM_U_W | PERM_U_X | \
                  PERM_P_R | PERM_P_W | PERM_P_X,
#else
    PERM_RWX    = PERM_U_R | PERM_U_W | PERM_P_R | PERM_P_W,
#endif
    /* Default permissions are read/write for everyone */
    PERM_DEFAULT = PERM_RW
} perm_attr_t;

typedef enum {
    ALLOC_HINT_R        = 0x1,  /* Read Allocation Hint */
    ALLOC_HINT_W        = 0x2,  /* Write Allocation Hint */
    ALLOC_HINT_T        = 0x4,  /* Transient Hint */
    ALLOC_HINT_DEFAULT  = ALLOC_HINT_R | ALLOC_HINT_W
} alloc_hint_t;

typedef enum {
    GRANULE_4KB = 0,
    GRANULE_16KB = 1,
    GRANULE_64KB = 2,
} granule_size_t;

typedef enum {
    EXCEPTION_LEVEL_0 = 0,
    EXCEPTION_LEVEL_1 = 1,
    EXCEPTION_LEVEL_2 = 2,
    EXCEPTION_LEVEL_3 = 3,
    EXCEPTION_LEVEL_CURRENT = 4,
    EXCEPTION_LEVEL_ENUM_MAX = 5
} exception_level_t;

typedef enum {
    MMU_TTBR0 = 0,
    MMU_TTBR1 = 1,
} mmu_ttbr_t;

/* Generic locking type (the underlying implementation is provided by the
 * platform file
 */
typedef void* mmu_lock_t;

/* memory map attributes */
typedef struct {
    bool                 exception_levels[EXCEPTION_LEVEL_ENUM_MAX];
    bool                 broadcast;
} mmu_tlb_attr_t;

/* memory map attributes */
typedef struct {
    uint64_t             input_addr;
    uint64_t             output_addr;
    uint64_t             size;
    perm_attr_t          perm_attr;
    shareability_attr_t  share_attr;
    cache_attr_t         cache_attr;
    bool                 secure;
    bool                 global;
#ifdef CONFIG_MMU_DEBUG
#define MMU_MAP_NAME_SIZE   12
#define MMU_MAP_NAME_STATIC(_name) \
    .name = #_name
    char                 name[MMU_MAP_NAME_SIZE]; /* for verbosity */
#else
#define MMU_MAP_NAME_STATIC(_name)
#endif
} mmu_map_attr_t;

typedef struct {
    uint64_t           mair;
    uint32_t           input_bit_size;
    uint32_t           output_bit_size;
    granule_size_t     granule_size;
    uint16_t           asid;
    bool               secure;
    mmu_ttbr_t         ttbr;
} mmu_translation_table_attr_t;

typedef struct {
    mmu_translation_table_attr_t attr;
    mmu_lock_t                   lock;
    uintptr_t                    va_base;
    uint32_t                     table_level;
    uint32_t                     table_entry_count;
    void *                       pt_base;
} translation_table_t;

typedef enum {
    MMU_LOG_INFO = 0,
    MMU_LOG_LOW = 1,
    MMU_LOG_MEDIUM = 2,
    MMU_LOG_HIGH = 3,
    MMU_LOG_ALWAYS = 4
} mmu_log_priority_t;

/* MMU Control Functions */
mmu_error_t mmu_initialize(exception_level_t el);
mmu_error_t mmu_enable(exception_level_t el);
mmu_error_t mmu_disable(exception_level_t el);
mmu_error_t mmu_switch_tables(exception_level_t el,
                              translation_table_t *pt,
                              shareability_attr_t shareability,
                              cache_attr_t cacheability);

/* Page Table Functions*/
mmu_error_t
mmu_initialize_translation_table(translation_table_t *pt,
                                 const mmu_translation_table_attr_t *pt_attr);
mmu_error_t mmu_deinit_translation_table(translation_table_t *pt);
mmu_error_t mmu_map(translation_table_t *pt, const mmu_map_attr_t *map,
                    const mmu_tlb_attr_t *tlb);
mmu_error_t mmu_unmap(translation_table_t *pt,
                      uintptr_t input_addr, size_t size,
                      const mmu_tlb_attr_t *tlb);
mmu_error_t mmu_change_attributes(translation_table_t *pt,
                                  const mmu_map_attr_t *map,
                                  const mmu_tlb_attr_t *tlb);
mmu_error_t mmu_lookup_page(translation_table_t *pt,
                            uintptr_t input_addr,
                            mmu_map_attr_t *page_attributes);
mmu_error_t mmu_walk_translation_tables(translation_table_t *pt,
                                        const uint64_t va,
                                        const size_t size);

/* TLB Maintenance Functions */
mmu_error_t mmu_invalidate_tlb_all(const mmu_tlb_attr_t *tlb);
mmu_error_t mmu_invalidate_tlb_asid(const mmu_tlb_attr_t *tlb,
                                    uint16_t asid);
mmu_error_t mmu_invalidate_tlb_va(const mmu_tlb_attr_t *tlb,
                                  uintptr_t va, uint16_t asid);

int mmu_init(void);
int mmu_fast_init(void);

#endif /* __TESTOS_MMU_H_INCLUDE__ */
