/*
 * Copyright (c) 2016 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 */
#ifndef _GENERIC_HEAP_H_
#define _GENERIC_HEAP_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define PAGE_SIZE_MASK	(PAGE_SIZE - 1)
#define ROUND_TO_PAGE(x) ((x + PAGE_SIZE_MASK) & ~(PAGE_SIZE_MASK))

typedef enum {
	GENERIC_HEAP_SUCCESS = 0,
	GENERIC_HEAP_ELOCKFAILED,
	GENERIC_HEAP_EBADPARAM,
	GENERIC_HEAP_ENOTINITIALIZED,
	GENERIC_HEAP_EFAILED,
} generic_heap_error_t;

typedef enum {
	GENERIC_HEAP_LOG_NONE = 0,
	GENERIC_HEAP_LOG_ERROR,
	GENERIC_HEAP_LOG_NOTICE,
	GENERIC_HEAP_LOG_WARN,
	GENERIC_HEAP_LOG_INFO,
	GENERIC_HEAP_LOG_VERBOSE,
} generic_heap_log_level_t;

/* Macro to get buffer size to be statically allocated in the
 * generic_heap_t structure. The size is dependent on the number
 * heap size and block size. Heap size and Block size must be a
 * power of 2
 */
#define GENERIC_HEAP_BUFFER_SIZE(heap_size, block_size)\
	(((heap_size/block_size) * sizeof(uint64_t) * 4) + PAGE_SIZE)

/* Generic structure/buffer that must be allocated statically by the image
 * (using global variables or linker symbols etc). This will be used
 * by the heap library internally to manage the heap buffer. The heap lock
 * must also be statically allocated and a pointer must be provided by the
 * calling code. The pointer will be passed as is to the platform port
 * for locking and unlocking if the pointer is not null. If the lock pointer
 * is null, the locking api's will not be called.
 */
typedef struct {
	void *heap_lock;
	char *buffer;
} generic_heap_t;

/* Initialization function to initialize heap.  Caller must use statically
 * allocated memory(such as global variables) for the generic_heap_t
 * structure.
 *
 * heap - pointer to generic_heap_t structure.
 * heap_start - start address of heap buffer to be managed
 * heap_size - size in bytes of heap buffer to be managed
 * block_size - size of block that will be allocated through malloc.
 */
generic_heap_error_t generic_heap_init(generic_heap_t *heap,
		uint64_t heap_start, uint64_t heap_size, uint64_t block_size);

/* Utility function to obtain remaining heap space in bytes.
 *
 * heap - pointer to generic_heap_t structure.
 */
uint64_t generic_heap_get_size_remaining(generic_heap_t *heap);

/* This function must be called before malloc, free, and their
 * aligned cousins are used. This will be used as the default heap
 * to allocate memory from when malloc, free etc are called.
 *
 * heap - pointer to generic_heap_t structure.
 */
generic_heap_error_t generic_heap_set_default_heap(generic_heap_t *heap);

/* Returns pointer to current heap structure */
generic_heap_t *generic_heap_get_default_heap();

/* stdlib functions. These functions use the stdlib/default heap that
 * is setup by the call to generic_heap_set_stdlib_heap()
 */
void *malloc(size_t size);
void free(void *mem);

/* Heap API's for using multiple heaps at the same time on multiple cores.
 * We cannot use malloc and free since their interface is expected
 * to operate only on one heap.
 */
void *malloc_from_heap(generic_heap_t *heap, size_t size);
void free_from_heap(generic_heap_t *heap, void *mem);

/* Image port must provide mutex implementation */
generic_heap_error_t generic_heap_image_mutex_init(void *heap_lock);
generic_heap_error_t generic_heap_image_mutex_lock(void *heap_lock);
generic_heap_error_t generic_heap_image_mutex_unlock(void *heap_lock);

/* Image port must provide log implementation */
void generic_heap_image_log(generic_heap_log_level_t level,
			    const char *fmt, ...);

#endif /* _GENERIC_HEAP_H_ */
