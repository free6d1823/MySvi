#ifndef __TESTOS_HEAP_H_INCLUDE__
#define __TESTOS_HEAP_H_INCLUDE__

#include <stddef.h>
#include <stdlib.h>

#ifndef __ASSEMBLY__
#include <target/heap_generic.h>
/* alignment must be 2^n */
void *heap_aligned_alloc(size_t align, size_t size);
void *heap_alloc(size_t size);
void heap_free(void *p);
void *heap_save_current();
void heap_restore(void *p);
int heap_switch_direct(uintptr_t, uintptr_t);


void *tcm_alloc_align(size_t size, size_t align);
void *tcm_alloc(size_t size);
void tcm_free(void *p);

void *apc_my_imemheap(void);
void *apc_my_tcmheap(void);

extern uintptr_t gp_buf;
#endif

#endif /* __TESTOS_HEAP_H_INCLUDE__ */
