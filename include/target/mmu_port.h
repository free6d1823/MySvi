#ifndef __MMU_PORT_H_INCLUDE__
#define __MMU_PORT_H_INCLUDE__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <target/mmu.h>

/* Allocator functions */
void* mmu_allocate_aligned(size_t size_to_allocate,
                           size_t requested_alignment, bool secure);
void mmu_free_aligned(void *memory, size_t alloc_size, bool secure);
uintptr_t mmu_get_physical_address(uintptr_t virtual_address);
uintptr_t mmu_get_virtual_address(uintptr_t physical_address);

/* Lock functions */
mmu_error_t mmu_lock_initialize(mmu_lock_t *lock);
mmu_error_t mmu_lock_deinit(mmu_lock_t *lock);
mmu_error_t mmu_lock(mmu_lock_t lock);
mmu_error_t mmu_unlock(mmu_lock_t lock);

/* Log functions */
void mmu_log(mmu_log_priority_t priority, const char *fmt, ...);

#endif /* __MMU_PORT_H_INCLUDE__ */
