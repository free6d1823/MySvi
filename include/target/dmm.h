/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#ifndef __HDTS_DMM_H__
#define __HDTS_DMM_H__

#include <bits/alltypes.h>
#include <stdbool.h>

#define MAX_HEAP_SIZE (1024 * 192) /* max size restricted */

/* On 32-bit machines, change this to 4 */
#define WORD_SIZE 8

/* single word (4) or double word (8) alignment */
#define ALIGNMENT \
	WORD_SIZE /* typically, single word on 32-bit systems and double word on 64-bit systems */

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN_DMM(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

#define SIZE_T_ALIGNED (ALIGN_DMM(sizeof(size_t)))

#define METADATA_T_ALIGNED (ALIGN_DMM(sizeof(metadata_t)))

#define PRINT_FREELIST

bool dmalloc_init();
void* dmalloc(size_t numbytes);
void dfree(void* allocptr);
void print_freelist();

#endif /* __HDTS_DMM_H__ */
