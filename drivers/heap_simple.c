#include <target/memory.h>
#include <target/heap.h>
#include <stdio.h>

uintptr_t gp_buf = HEAP_START;

void *heap_aligned_alloc(size_t align, size_t size)
{
	uintptr_t cur;

	if (align & (align - 1)) {
		printf("heap_alloc wrong align!\n");
		return NULL;
	}

	cur = ALIGN_UP(gp_buf, (uintptr_t)align);

	if ((cur + size) > HEAP_END) {
		printf("heap_alloc out of memory!\n");
		return NULL;
	} else {
		gp_buf = cur + size;
		return (void *)cur;
	}
}

void *heap_alloc(size_t size)
{
	return heap_aligned_alloc(16, size);
}


void heap_free(void *p)
{
	(void) p;
}
