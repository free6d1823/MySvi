/** @file mmu_imc_plat.c

  ARMv8 MMU Library

  Copyright (c) 2016 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

**/
#include <stdio.h>
#include <target/memory.h>
#include <target/heap.h>
#include <asm/mmu.h>

static mmu_log_priority_t log_priority = MMU_LOG_HIGH;

void* mmu_allocate_aligned(size_t size_to_allocate,
                           size_t requested_alignment, bool secure)
{
    void *p;

    /* Secure is unused here */
    (void)secure;

    p = heap_aligned_alloc(requested_alignment, size_to_allocate);

    mmu_log(MMU_LOG_INFO,
        "mmu_allocate_aligned(%d)=%p\n", size_to_allocate, p);

    return p;
}

void mmu_free_aligned(void* memory, size_t alloc_size, bool secure)
{
    /* Secure and alloc_size is unused here */
    (void)secure;
    (void)alloc_size;

    heap_free(memory);
}

uintptr_t mmu_get_physical_address(uintptr_t virtual_address)
{
    return virtual_address;
}

uintptr_t mmu_get_virtual_address(uintptr_t physical_address)
{
    return physical_address;
}

mmu_error_t mmu_lock_initialize(mmu_lock_t* lock)
{
    return MMU_SUCCESS;
}

mmu_error_t mmu_lock_deinit(mmu_lock_t* lock)
{
    return MMU_SUCCESS;
}

mmu_error_t mmu_lock(mmu_lock_t lock)
{
    return MMU_SUCCESS;
}

mmu_error_t mmu_unlock(mmu_lock_t lock)
{
    return MMU_SUCCESS;
}

void mmu_log(mmu_log_priority_t priority, const char* fmt, ...)
{
    va_list args;

    if (priority >= log_priority) {
        va_start(args, fmt);
        vprintf(fmt,args);
        va_end(args);
    }
}
