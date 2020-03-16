/*
 * Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 */
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <target/cmdline.h>
#include <target/heap.h>
#include <target/spinlock.h>

typedef struct mem_block mem_block_t;

struct mem_block {
	uint64_t number_of_blocks;
	bool allocated;
	int32_t next;
	int32_t prev;
	uint32_t reserved;
};

typedef struct {
	bool heap_initialized;
	uint64_t original_heap_blocks;
	uint64_t heap_start; // heap memory start address
	uint64_t heap_blocks_remaining;
	uint64_t block_size;
	void *heap_lock;
	mem_block_t heap_list[];
} generic_heap_internal_t;

//#if DEBUG
#if 1
#define	assert(x)\
	do {\
		if (!(x))	while(1);\
	} while (0);
#else
#define assert(x)
#endif

static generic_heap_log_level_t generic_heap_log_level = GENERIC_HEAP_LOG_NONE;
extern void plat_configure_mmu_el3();
/* Image port must provide mutex implementation */
generic_heap_error_t generic_heap_image_mutex_init(void *heap_lock)
{
	if (heap_lock == NULL)
		return GENERIC_HEAP_ELOCKFAILED;

	memset(heap_lock, 0, sizeof(spinlock_t));
	return GENERIC_HEAP_SUCCESS;
}

generic_heap_error_t generic_heap_image_mutex_lock(void *heap_lock)
{
	if (heap_lock == NULL)
		return GENERIC_HEAP_ELOCKFAILED;

	spinlock_t *lock = (spinlock_t *)heap_lock;
	spin_lock(lock);

	return GENERIC_HEAP_SUCCESS;
}

generic_heap_error_t generic_heap_image_mutex_unlock(void *heap_lock)
{
	if (heap_lock == NULL)
		return GENERIC_HEAP_ELOCKFAILED;

	spinlock_t *lock = (spinlock_t *)heap_lock;
	spin_unlock(lock);

	return GENERIC_HEAP_SUCCESS;
}

/* Image port must provide log implementation */
void generic_heap_image_log(generic_heap_log_level_t level, const char *fmt, ...)
{
	char logging_string[512] = {0};
	va_list args;

	if (level <= generic_heap_log_level) {
		va_start(args, fmt);
		vsnprintf(logging_string, sizeof(logging_string), fmt, args);
		va_end(args);
		printf(logging_string);
	}
}

uint64_t generic_heap_internal_malloc(
		generic_heap_t *heap, uint64_t size_in_bytes)
{
	uint64_t retval = 0;
	bool heap_lock_acquired = false;
	generic_heap_internal_t *heap_struct = NULL;
	generic_heap_error_t err = GENERIC_HEAP_EFAILED;

	if (heap == NULL) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_internal_malloc:"
				"Invalid heap structure\n");
		goto exit;
	}

	if (size_in_bytes == 0) {
		generic_heap_image_log(GENERIC_HEAP_LOG_WARN,
				"\ngeneric_heap_internal_malloc:"
				"Invalid size requested\n");
		goto exit;
	}

	heap_struct = (generic_heap_internal_t *)(heap->buffer);

	if (heap_struct->heap_initialized != true) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_internal_malloc:"
				"Heap not initialized.\n");
		goto exit;
	}

	uint64_t block_size_mask = heap_struct->block_size - 1;
	uint64_t rounded_size =
			((size_in_bytes + block_size_mask) & ~(block_size_mask));
	uint64_t number_of_blocks = rounded_size / heap_struct->block_size;

	assert((number_of_blocks * heap_struct->block_size) >= size_in_bytes);

	err = generic_heap_image_mutex_lock(heap_struct->heap_lock);
	if (err != GENERIC_HEAP_SUCCESS) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
					"\ngeneric_heap_internal_malloc:"
					"Failed to acquire lock.\n");
		goto exit;
	}

	heap_lock_acquired = true;

	/* This check must only be after acquiring lock. Size remaining can be
	 * changed by other threads. if lock is null, the code assumes this
	 * will never be called on multiple cores.
	 */
	if (heap_struct->heap_blocks_remaining < number_of_blocks) {
		generic_heap_image_log(GENERIC_HEAP_LOG_VERBOSE,
				"\ngeneric_heap_internal_malloc: Not enough heap remaining\n");
		goto exit;
	}

	int32_t prev = -1;
	int32_t next = -1;
	for (uint64_t i = 0; i < heap_struct->original_heap_blocks;) {
		if (heap_struct->heap_list[i].allocated == true) {
			assert(heap_struct->heap_list[i].next == -1);
			assert(heap_struct->heap_list[i].prev == -1);
			i++;
			continue;
		}

		assert(heap_struct->heap_list[i].number_of_blocks != 0);

		if (heap_struct->heap_list[i].number_of_blocks == number_of_blocks) {
			retval = (uint64_t)(heap_struct->heap_start +
					(i * heap_struct->block_size));
			heap_struct->heap_blocks_remaining -= number_of_blocks;
			heap_struct->heap_list[i].allocated = true;

			for (uint64_t k = (i + 1); k < (i + number_of_blocks); k++) {
				heap_struct->heap_list[k].allocated = true;
				heap_struct->heap_list[k].number_of_blocks = 0;
				heap_struct->heap_list[k].next = -1;
				heap_struct->heap_list[k].prev = -1;
			}

			next = heap_struct->heap_list[i].next;
			if (prev != -1) {
				heap_struct->heap_list[prev].next = next;
				assert(heap_struct->heap_list[prev].number_of_blocks != 0);
			}
			if (next != -1) {
				heap_struct->heap_list[next].prev = prev;
				assert(heap_struct->heap_list[next].number_of_blocks != 0);
			}

			heap_struct->heap_list[i].next = -1;
			heap_struct->heap_list[i].prev = -1;
			generic_heap_image_log(GENERIC_HEAP_LOG_VERBOSE,
					"1.Allocating block %d, num %d\n", i, number_of_blocks);
			break;
		}

		if (heap_struct->heap_list[i].number_of_blocks > number_of_blocks) {

			uint64_t remaining_blocks = heap_struct->heap_list[i].number_of_blocks
					- number_of_blocks;

			retval = (uint64_t)(heap_struct->heap_start +
					(i * heap_struct->block_size));
			heap_struct->heap_blocks_remaining -= number_of_blocks;
			heap_struct->heap_list[i].allocated = true;

			heap_struct->heap_list[i].number_of_blocks = number_of_blocks;

			for (uint64_t k = (i + 1); k < (i + number_of_blocks); k++) {
				heap_struct->heap_list[k].allocated = true;
				heap_struct->heap_list[k].number_of_blocks = 0;
				heap_struct->heap_list[k].next = -1;
				heap_struct->heap_list[k].prev = -1;
			}

			assert(
				heap_struct->heap_list[i + number_of_blocks].allocated == false);
			assert(
				heap_struct->heap_list[i + number_of_blocks].number_of_blocks == 0);

			heap_struct->heap_list[i + number_of_blocks].number_of_blocks =
					remaining_blocks;

			next = heap_struct->heap_list[i].next;
			prev = heap_struct->heap_list[i].prev;

			heap_struct->heap_list[i].next = -1;
			heap_struct->heap_list[i].prev = -1;

			heap_struct->heap_list[i + number_of_blocks].prev = prev;
			heap_struct->heap_list[i + number_of_blocks].next = next;
			if (prev != -1) {
				heap_struct->heap_list[prev].next = i + number_of_blocks;
				assert(heap_struct->heap_list[prev].number_of_blocks != 0);
			}
			if (next != -1) {
				heap_struct->heap_list[next].prev = i + number_of_blocks;
				assert(heap_struct->heap_list[next].number_of_blocks != 0);
			}
			generic_heap_image_log(GENERIC_HEAP_LOG_VERBOSE,
					"2.Allocating block %d, num %d\n", i, number_of_blocks);
			break;
		}

		assert(heap_struct->heap_list[i].allocated == false);
		assert(heap_struct->heap_list[i].number_of_blocks != 0);
		assert(heap_struct->heap_list[i].number_of_blocks < number_of_blocks);

		prev = i;
		next = heap_struct->heap_list[i].next;
		i = next;

		if (next == -1)
			break;
	}

	if (retval == 0) {
		generic_heap_image_log(GENERIC_HEAP_LOG_WARN,
				"\ngeneric_heap_internal_malloc: "
				"Very large size requested, Heap too fragmented,"
				"or really out of memory!\n");
	}

	assert((retval & (heap_struct->block_size - 1)) == 0);
exit:
	if ((heap_lock_acquired) && (heap_struct != NULL)) {
			err = generic_heap_image_mutex_unlock(heap_struct->heap_lock);
			if (err != GENERIC_HEAP_SUCCESS)
				generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
						"\ngeneric_heap_internal_malloc:"
						"Failed to release lock.\n");
	}
	return retval;
}

bool generic_heap_internal_free(generic_heap_t *heap, uint64_t mem_ptr)
{
	bool heap_lock_acquired = false;
	bool retval = false;
	generic_heap_internal_t *heap_struct = NULL;
	generic_heap_error_t err = GENERIC_HEAP_EFAILED;

	if (heap == NULL) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_internal_free:"
				"Invalid heap structure\n");
		goto exit;
	}

	if (mem_ptr == 0) {
		generic_heap_image_log(GENERIC_HEAP_LOG_VERBOSE,
				"\ngeneric_heap_internal_free: Null pointer passed for free");
		goto exit;
	}

	heap_struct = (generic_heap_internal_t *)(heap->buffer);

	if (heap_struct->heap_initialized != true) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_internal_free:"
				"Heap not initialized\n");
		goto exit;
	}

	if ((mem_ptr & (heap_struct->block_size - 1)) != 0) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
						"\ngeneric_heap_internal_free:"
						"Invalid mem_ptr\n");
		goto exit;
	}

	uint64_t heap_valid_end =
			heap_struct->heap_start +
			(heap_struct->block_size * heap_struct->original_heap_blocks);

	if ((mem_ptr < heap_struct->heap_start) ||
			mem_ptr >= heap_valid_end) {
		generic_heap_image_log(GENERIC_HEAP_LOG_WARN,
				"\ngeneric_heap_internal_free:"
				"Trying to free memory outside heap 1\n");
		goto exit;
	}

	err = generic_heap_image_mutex_lock(heap_struct->heap_lock);
	if (err != GENERIC_HEAP_SUCCESS) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
					"\ngeneric_heap_internal_free:"
					"Failed to acquire lock.\n");
		goto exit;
	}

	heap_lock_acquired = true;

	uint64_t start_block_number = ((mem_ptr - heap_struct->heap_start)) /
			(heap_struct->block_size);
	uint64_t next_block_number = start_block_number +
			heap_struct->heap_list[start_block_number].number_of_blocks;

	assert(start_block_number < heap_struct->original_heap_blocks);

	if ((heap_struct->heap_list[start_block_number].allocated == false) ||
			(heap_struct->heap_list[start_block_number].number_of_blocks == 0)) {
		generic_heap_image_log(GENERIC_HEAP_LOG_WARN,
				"\ngeneric_heap_internal_free: "
				"Trying to free already freed block.\n");
		goto exit;
	}

	assert(heap_struct->heap_list[start_block_number].next == -1);
	assert(heap_struct->heap_list[start_block_number].prev == -1);

	int32_t next = -1;
	int32_t prev = -1;
	uint64_t number_of_blocks_freed =
			heap_struct->heap_list[start_block_number].number_of_blocks;

	for (uint64_t i = 0; i < heap_struct->original_heap_blocks;) {
		if (heap_struct->heap_list[i].allocated == true) {
			assert(heap_struct->heap_list[i].next == -1);
			assert(heap_struct->heap_list[i].prev == -1);

			i++;
			continue;
		}

		if (i > start_block_number) {
			assert(heap_struct->heap_list[i].number_of_blocks != 0);
			next = i;
			prev = heap_struct->heap_list[next].prev;
			break;
		}

		prev = i;
		next = heap_struct->heap_list[i].next;
		i = next;

		if (next == -1)
			break;
	}
	generic_heap_image_log(GENERIC_HEAP_LOG_VERBOSE,
			"1.Freeing block %d, num %d\n", start_block_number,
			number_of_blocks_freed);

	heap_struct->heap_list[start_block_number].allocated = false;

	for (uint64_t i = (start_block_number + 1);	i < next_block_number; i++) {

		assert(heap_struct->heap_list[i].allocated == true);
		assert(heap_struct->heap_list[i].number_of_blocks == 0);
		assert(heap_struct->heap_list[i].next == -1);
		assert(heap_struct->heap_list[i].prev == -1);

		heap_struct->heap_list[i].allocated = false;
	}

	heap_struct->heap_list[start_block_number].prev = prev;
	heap_struct->heap_list[start_block_number].next = next;

	if (prev != -1) {
		assert(heap_struct->heap_list[prev].allocated == false);
		assert(heap_struct->heap_list[prev].number_of_blocks != 0);

		heap_struct->heap_list[prev].next = start_block_number;

		if ((prev + heap_struct->heap_list[prev].number_of_blocks) ==
				start_block_number) {
			generic_heap_image_log(GENERIC_HEAP_LOG_VERBOSE,
					"1.Coalescing block %d, %d\n", start_block_number, prev);

			heap_struct->heap_list[prev].number_of_blocks +=
					heap_struct->heap_list[start_block_number].number_of_blocks;
			heap_struct->heap_list[prev].next =
					heap_struct->heap_list[start_block_number].next;

			if (heap_struct->heap_list[prev].next != -1)
				heap_struct->heap_list[heap_struct->heap_list[prev].next].prev =
						prev;

			heap_struct->heap_list[start_block_number].number_of_blocks = 0;
			heap_struct->heap_list[start_block_number].prev = -1;
			heap_struct->heap_list[start_block_number].next = -1;
			assert(heap_struct->heap_list[start_block_number].allocated == false);
			start_block_number = prev;
		}
	}

	if (next != -1) {
		assert(heap_struct->heap_list[next].allocated == false);
		assert(heap_struct->heap_list[next].number_of_blocks != 0);

		heap_struct->heap_list[next].prev = start_block_number;

		if ((start_block_number +
				heap_struct->heap_list[start_block_number].number_of_blocks) ==
						next) {
			generic_heap_image_log(GENERIC_HEAP_LOG_VERBOSE,
					"2.Coalescing block %d, %d\n", start_block_number, next);

			heap_struct->heap_list[start_block_number].number_of_blocks +=
					heap_struct->heap_list[next].number_of_blocks;
			heap_struct->heap_list[start_block_number].next =
					heap_struct->heap_list[next].next;

			heap_struct->heap_list[next].number_of_blocks = 0;
			heap_struct->heap_list[next].prev = -1;
			heap_struct->heap_list[next].next = -1;
			assert(heap_struct->heap_list[next].allocated == false);

			next = heap_struct->heap_list[start_block_number].next;
			if (next != -1) {
				heap_struct->heap_list[next].prev = start_block_number;
				assert(heap_struct->heap_list[next].allocated == false);
			}
		}
	}

	heap_struct->heap_blocks_remaining += number_of_blocks_freed;
	retval = true;

exit:
	if ((heap_lock_acquired) && (heap_struct != NULL)) {
			err = generic_heap_image_mutex_unlock(heap_struct->heap_lock);
			if (err != GENERIC_HEAP_SUCCESS)
				generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
						"\ngeneric_heap_internal_free:"
						"Failed to release lock.\n");
	}
	return retval;
}

generic_heap_error_t 
generic_heap_init( generic_heap_t *heap,
    	               uint64_t heap_start, 
    	               uint64_t heap_size, 
    	               uint64_t block_size)
{
	generic_heap_error_t retval = GENERIC_HEAP_EFAILED;

	if ((heap == NULL) || (heap_start == 0) || (heap_size <= 0) || (block_size == 0)) {
		retval = GENERIC_HEAP_EBADPARAM;
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_init: Invalid heap structure,"
				" size, start address or block size\r\n");
		goto exit;
	}

	if (block_size & (block_size - 1)) {
		retval = GENERIC_HEAP_EBADPARAM;
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_init: Block size must be power of 2\r\n");
		goto exit;
	}

	if (heap_size & (heap_size - 1)) {
		retval = GENERIC_HEAP_EBADPARAM;
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_init: Heap size must be power of 2\r\n");
		goto exit;
	}

	uint64_t block_size_mask = (block_size - 1);

	if (heap_start & block_size_mask) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_init:"
				" Heap start address must be block size aligned.\r\n");
		retval = GENERIC_HEAP_EBADPARAM;
		goto exit;
	}

	if (heap->heap_lock == NULL) {
		generic_heap_image_log(GENERIC_HEAP_LOG_VERBOSE,
				"\ngeneric_heap_init: Initializing heap without locks");
	} else {
		generic_heap_image_mutex_init(heap->heap_lock);
	}

	memset((heap->buffer), 0, GENERIC_HEAP_BUFFER_SIZE(heap_size, block_size));

	generic_heap_internal_t *heap_struct = (generic_heap_internal_t *)(heap->buffer);

	heap_struct->heap_start = heap_start;
	heap_struct->original_heap_blocks = (heap_size / block_size);
	heap_struct->heap_blocks_remaining = (heap_size / block_size);
	heap_struct->heap_lock = heap->heap_lock;
	heap_struct->block_size = block_size;

	heap_struct->heap_list[0].number_of_blocks = (heap_size / block_size);
	heap_struct->heap_list[0].allocated = false;
	heap_struct->heap_list[0].prev = -1;
	heap_struct->heap_list[0].next = -1;
	heap_struct->heap_initialized = true;

	retval = GENERIC_HEAP_SUCCESS;
exit:
	return retval;
}

uint64_t generic_heap_get_size_remaining(generic_heap_t *heap)
{
	if (heap == NULL)
		return 0;

	generic_heap_internal_t *heap_struct =
			(generic_heap_internal_t *)(heap->buffer);
	return (heap_struct->heap_blocks_remaining * heap_struct->block_size);
}

static generic_heap_t *default_heap = NULL;

generic_heap_error_t generic_heap_set_default_heap(generic_heap_t *heap)
{
	generic_heap_error_t retval = GENERIC_HEAP_EFAILED;
	generic_heap_internal_t *heap_struct = NULL;

	if (heap == NULL) {
		retval = GENERIC_HEAP_EBADPARAM;
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_set_stdlib_heap: Invalid heap");
		goto exit;
	}

	heap_struct = (generic_heap_internal_t *)(heap->buffer);

	if (heap_struct->heap_initialized != true) {
		retval = GENERIC_HEAP_ENOTINITIALIZED;
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\ngeneric_heap_set_stdlib_heap:"
				"Heap not initialized\r\n");
		goto exit;
	}

	default_heap = heap;
	retval = GENERIC_HEAP_SUCCESS;
exit:
	return retval;
}

generic_heap_t *generic_heap_get_default_heap()
{
	return default_heap;
}

void *malloc_from_heap(generic_heap_t *heap, size_t size)
{
	if (heap == NULL)
		return NULL;

	uint64_t retval = generic_heap_internal_malloc(heap, size);

	if (retval == 0) {
		generic_heap_image_log(GENERIC_HEAP_LOG_ERROR,
				"\nmalloc_from_heap: Memory allocation through "
				"malloc_from_heap() failed\r\n");
		return NULL;
	}
	return (void *)retval;
}

void free_from_heap(generic_heap_t *heap, void *mem)
{
	if (mem == NULL || heap == NULL)
		return;

	if (!generic_heap_internal_free(heap, (uint64_t)mem))
		generic_heap_image_log(GENERIC_HEAP_LOG_WARN,
				"\nfree failed to free pointer 0x%lx", (unsigned long)mem);

	return;
}

void *malloc(size_t size)
{
	return malloc_from_heap(default_heap, size);
}

void free(void *mem)
{
	free_from_heap(default_heap, mem);
	return;
}

// #define HDTS_HEAP_SIZE	SYS_IMEM_SIZE
// #define HDTS_HEAP_START	SYS_IMEM_START // Sys IMEM
// #else
#define HDTS_HEAP_SIZE 0x800000 // 8MB
#define HDTS_HEAP_START 0x1000000 // at 16MB
// #endif

static spinlock_t el3_heap_lock = {0};
static char el3_heap_buffer[GENERIC_HEAP_BUFFER_SIZE(HDTS_HEAP_SIZE, PAGE_SIZE)] = {0};
static generic_heap_t el3_heap = {
	.heap_lock = &el3_heap_lock,
	.buffer = el3_heap_buffer,
};
static int g_el3_heap_initialized = 0;

void plat_configure_heap()
{
	if (g_el3_heap_initialized == 0) {
		if (generic_heap_init(&el3_heap, HDTS_HEAP_START, HDTS_HEAP_SIZE, PAGE_SIZE)
			!= GENERIC_HEAP_SUCCESS) {
			printf("EL3 Failed to initialize heap. Fatal error.\r\n");
			return;
		}
	} else
		printf("heap has been initialized.\n");
	g_el3_heap_initialized = 1;

	if (generic_heap_set_default_heap(&el3_heap) != GENERIC_HEAP_SUCCESS) {
		printf("EL3 Failed to initialize default heap. Fatal error.\r\n");
		return;
	} else
		printf("heap set default to ddr.\n");

	return;
}

static spinlock_t imem_heap_lock = {0};
static char imem_heap_buffer[GENERIC_HEAP_BUFFER_SIZE(SYS_IMEM_SIZE, PAGE_SIZE)] = {0};
static generic_heap_t imem_heap = {
	.heap_lock = &imem_heap_lock,
	.buffer = imem_heap_buffer,
};
static int g_imem_heap_initialized = 0;

void plat_configure_heap_imem()
{
	if (g_imem_heap_initialized == 0) {
		if (generic_heap_init(&imem_heap, SYS_IMEM_START, SYS_IMEM_SIZE, PAGE_SIZE)
			!= GENERIC_HEAP_SUCCESS) {
			printf("IMEM Failed to initialize heap. Fatal error.\r\n");
			return;
		}
	} else
		printf("heap has been initialized.\n");
	g_imem_heap_initialized = 1;

	if (generic_heap_set_default_heap(&imem_heap) != GENERIC_HEAP_SUCCESS) {
		printf("IMEM Failed to initialize default heap. Fatal error.\r\n");
		return;
	} else
		printf("heap set default to imem\n");

	return;
}

static void generic_heap_dump()
{
	if (g_el3_heap_initialized) {
		printf("ddr heap initialized.\n");
	} else
		printf("ddr heap not initialized.\n");
}

static int do_heap(int argc, char* argv[])
{
	uint32_t i;
	uint32_t size;
	void* addr;

	if (argc == 1) // no param
		return -1;

	if (argc == 3 && strcmp(argv[1], "malloc") == 0) {
		size = strtoul(argv[2], NULL, 0);
		printf("malloc 0x%p, size=%d\n", malloc(size), size);
		return 0;
	} else if (argc == 3 && strcmp(argv[1], "free") == 0) {
		addr = (void*)strtoul(argv[2], NULL, 0);
		free(addr);
		printf("free 0x%p\n", addr);
		return 0;
	}

	if (strcmp(argv[1], "init") == 0) {
		if (argc == 3 && strcmp(argv[2], "imem") == 0) {
			plat_configure_heap_imem();
			return 0;
		} else if (argc == 3 && strcmp(argv[2], "ddr") == 0) {
			plat_configure_heap();
                        plat_configure_mmu_el3();
                        return 0;
		}
	} else if (strcmp(argv[1], "dump") == 0) { // heap dump
		generic_heap_dump();
		return 0;
	} else if (strcmp(argv[1], "set") == 0) { // heap set
		// heap set loglevel 0~5
		if (argc == 4 && strcmp(argv[2], "loglevel") == 0) {
			i = strtoul(argv[3], NULL, 0);
			generic_heap_log_level = (i >= 0 && i <= 5) ? i : GENERIC_HEAP_LOG_NONE;
			return 0;
		}
		if (argc == 4 && strcmp(argv[2], "default") == 0) {
			if (strcmp(argv[3], "imem") == 0) {
				plat_configure_heap_imem();
				return 0;
			} else if (strcmp(argv[3], "ddr") == 0) {
				plat_configure_heap();
                                plat_configure_mmu_el3();
                                return 0;
			}
		}
	}

	return -1; // invalid param
}

#ifdef CONFIG_CONSOLE_COMMAND
MK_CMD(heap,
	   do_heap,
	   "heap commands",
	   " heap set loglevel 0~5 \n"
	   " heap init imem/ddr \n"
	   " heap malloc <size> \n"
	   " heap free <addr> \n"
	   " heap set default imem/ddr \n");
#endif
