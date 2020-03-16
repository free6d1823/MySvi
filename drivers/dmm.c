/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#include <bits/alltypes.h>
#include <stdio.h>
//#include <unistd.h>
//#include <assert.h>
#include <stdbool.h>

#include "Base.h"
#include "target/dmm.h"

typedef struct metadata
{
	/* size_t is the return type of the sizeof operator. Since the size of
	 * an object depends on the architecture and its implementation, size_t
	 * is used to represent the maximum size of any object in the particular
	 * implementation.
	 * size contains the size of the data object or the amount of free
	 * bytes
	 */
	size_t size;
	struct metadata* next;
	struct metadata* prev;
} metadata_t;

/* freelist maintains all the blocks which are not in use; freelist is kept
 * always sorted to improve the efficiency of coalescing
 */
static metadata_t* freelist = NULL;

bool init = FALSE;

#define HEAP_ADDRESS 0xFF70000000

void* dmalloc(size_t numbytes)
{
	metadata_t* cur = freelist;

	if ((freelist == NULL) || !init) {
		return NULL;
	}

	// ASSERT(numbytes >= 0);

	// case of 0, return null pointer
	if (numbytes == 0) {
		return NULL;
	}

	if (cur == NULL || cur == 0x0) { // When no free blocks, return NULL
		return NULL;
	}

	while (ALIGN_DMM(numbytes) > cur->size) { // Iterate until big enough block
		cur = cur->next;
		if (cur == NULL || cur == 0x0) {
			return NULL;
		}
	}

	if (METADATA_T_ALIGNED >= cur->size || ALIGN_DMM(numbytes) >= cur->size - METADATA_T_ALIGNED) {
		void* returnptr = (void*)cur;
		returnptr = METADATA_T_ALIGNED + returnptr;

		if (cur->prev == NULL) { // Case when cur is head of list
			freelist = cur->next;
		} else {
			cur->prev->next = cur->next;
		}
		if (cur->next == NULL) { // Case when cur is tail
			// freelist doesn't move
		} else {
			cur->next->prev = cur->prev;
		}
		cur->prev = NULL;
		cur->next = NULL;
		// So size change, no worries about footer
		// print_freelist();

		return returnptr;
	}

	// change size, make pointers of allocated block NULL
	size_t old_size = cur->size;
	cur->size = ALIGN_DMM(numbytes);

	void* returnptr = (void*)cur;
	returnptr = METADATA_T_ALIGNED + returnptr; // Go to return address, no footer edit

	void* newfreelist = (void*)cur;
	newfreelist = newfreelist + METADATA_T_ALIGNED + ALIGN_DMM(numbytes);

	metadata_t* newblock = (metadata_t*)newfreelist;
	newblock->size = old_size - METADATA_T_ALIGNED - ALIGN_DMM(numbytes);

	if (cur->prev == NULL) {
		freelist = newblock;
		newblock->prev = NULL;
	} else {
		cur->prev->next = newblock;
		newblock->prev = cur->prev;
	}

	if (cur->next == NULL) {
		newblock->next = NULL;
	} else {
		cur->next->prev = newblock;
		newblock->next = cur->next;
	}
	cur->next = NULL;
	cur->prev = NULL;

	return returnptr;
}

void dfree(void* ptr)
{
	/* Your free and coalescing code goes here */
	if (ptr == NULL)
		return;

	ptr = ptr - METADATA_T_ALIGNED; // GO TO header
	// YOU ARE NOW AT THE HEADER!!!

	// NULL case
	if (freelist == NULL) {
		freelist = (metadata_t*)ptr;
		// size should already be in header, footer
		// print_freelist();
		return;
	} else {
		metadata_t* cur = freelist;
		void* curvoid = (void*)cur;
		// if(curvoid==ptr){
		//  //// DEBUG("Block already free!!!");
		//  return;
		// }

		// Case: Freed block is before freelist
		if (ptr < curvoid) {
			metadata_t* newfreeblock = (metadata_t*)ptr;
			freelist->prev = newfreeblock;
			newfreeblock->prev = NULL;
			newfreeblock->next = freelist;
			freelist = newfreeblock;

			void* next = (void*)newfreeblock->next;
			void* newfreeblockvoid = (void*)newfreeblock;
			// Coalesce to next block, with FOOTER edits.
			// DEBUG("Next: %p, %p \n", newfreeblockvoid + METADATA_T_ALIGNED + newfreeblock->size +
			// FOOTER_T_ALIGNED, next); If adjacent to next block
			//      if(newfreeblockvoid + METADATA_T_ALIGNED + newfreeblock->size + FOOTER_T_ALIGNED
			//      == next){
			// newfreeblock->size = newfreeblock->size + newfreeblock->next->size +
			// METADATA_T_ALIGNED + FOOTER_T_ALIGNED;
			if (newfreeblockvoid + METADATA_T_ALIGNED + newfreeblock->size == next) {
				newfreeblock->size
					= newfreeblock->size + newfreeblock->next->size + METADATA_T_ALIGNED;

				// FOOTER CHANGE
				// size_t * newfooter = (size_t *) (newfreeblock->size + (void *) newfreeblock +
				// METADATA_T_ALIGNED); *newfooter = newfreeblock->size;

				metadata_t* newfreenext = newfreeblock->next;
				newfreeblock->next = newfreeblock->next->next;
				if (newfreeblock->next != NULL) {
					newfreeblock->next->prev = newfreeblock;
				}
				newfreenext->next = NULL;
				newfreenext->prev = NULL;
			}
			// No prev case
			// print_freelist();
			return;
		}

		// Find the free blocks closest to the new block
		// cur: directly previous to freed block (may be malloc'd)
		// newfreeblock: freed block

		// PREVIOUSLY:
		void* curnext = (void*)cur->next;
		while (cur->next != NULL && curnext <= ptr) {
			// if(curnext==ptr){
			//  // DEBUG("Block already free!!!");
			//  return;
			// }
			cur = cur->next;
			curnext = (void*)cur->next;
		}
		// DEBUG("Block previous to ptr: %p \n", cur);

		// FOOTER O(1) time:
		// size_t * prevfooter = (size_t *) (ptr - FOOTER_T_ALIGNED);
		// Get to the head of header of prev block
		// cur = ptr - FOOTER_T_ALIGNED - *prevfooter - METADATA_T_ALIGNED;
		// cur = ptr - FOOTER_T_ALIGNED - *prevfooter - METADATA_T_ALIGNED;
		metadata_t* newfreeblock = (metadata_t*)ptr; // Size already there
		// DEBUG("ptr/newfreeblock: %p\n", newfreeblock);

		// Add to freelist list
		newfreeblock->next = cur->next;
		if (cur->next != NULL) {
			cur->next->prev = newfreeblock;
		}
		cur->next = newfreeblock;
		newfreeblock->prev = cur;

		void* prev = (void*)cur;
		void* next = (void*)newfreeblock->next;
		void* newfreeblockvoid = (void*)newfreeblock;

		// Coalesce to next block
		// DEBUG("Next: %p, %p \n", newfreeblockvoid + METADATA_T_ALIGNED + newfreeblock->size +
		// FOOTER_T_ALIGNED, next); if(newfreeblockvoid + METADATA_T_ALIGNED + newfreeblock->size +
		// FOOTER_T_ALIGNED == next){ newfreeblock->size = newfreeblock->size +
		// newfreeblock->next->size + METADATA_T_ALIGNED + FOOTER_T_ALIGNED;
		if (newfreeblockvoid + METADATA_T_ALIGNED + newfreeblock->size == next) {
			newfreeblock->size = newfreeblock->size + newfreeblock->next->size + METADATA_T_ALIGNED;

			// FOOTER CHANGE
			// size_t * newfooter = (size_t *) (newfreeblock->size + (void *) newfreeblock +
			// METADATA_T_ALIGNED); *newfooter = newfreeblock->size;

			metadata_t* newfreenext = newfreeblock->next;
			newfreeblock->next = newfreeblock->next->next;
			if (newfreeblock->next != NULL) {
				newfreeblock->next->prev = newfreeblock;
			}
			newfreenext->next = NULL;
			newfreenext->prev = NULL;
			// Do we need to change the cur metadata?
		}

		// Coalesce to prev, cur is the previous block
		// DEBUG("Prev: %p, %p \n", prev + METADATA_T_ALIGNED + cur->size + FOOTER_T_ALIGNED,
		// newfreeblockvoid);
		if (prev + METADATA_T_ALIGNED + cur->size == newfreeblockvoid) {
			//          cur->size = cur->size + newfreeblock->size + METADATA_T_ALIGNED +
			//          FOOTER_T_ALIGNED;
			cur->size = cur->size + newfreeblock->size + METADATA_T_ALIGNED;

			// FOOTER CHANGE
			// size_t * newfooter = (size_t *) (cur->size + (void *) cur + METADATA_T_ALIGNED);
			// *newfooter = cur->size;

			cur->next = newfreeblock->next;
			if (newfreeblock->next != NULL) {
				newfreeblock->next->prev = cur;
			}
			newfreeblock->next = NULL;
			newfreeblock->prev = NULL;
			// Do we need to change the cur metadata?
		}
	}
	// print_freelist();
}

bool dmalloc_init()
{
	/* Two choices:
	 * 1. Append prologue and epilogue blocks to the start and the end of the freelist
	 * 2. Initialize freelist pointers to NULL
	 *
	 * Note: We provide the code for 2. Using 1 will help you to tackle the
	 * corner cases succinctly.
	 */
	size_t max_bytes = ALIGN_DMM(MAX_HEAP_SIZE);

	freelist = (metadata_t*)HEAP_ADDRESS; // returns heap_region, which is initialized to freelist
	freelist->next = NULL;
	freelist->prev = NULL;

	freelist->size = max_bytes - METADATA_T_ALIGNED;

	init = TRUE;

	return TRUE;
}

/*Only for debugging purposes; can be turned off through -N DEBUG flag*/
void print_freelist()
{
	metadata_t* freelist_head = freelist;
	while (freelist_head != NULL) {
		printf("\tFreelist Size:%zd, Head:%p, Prev:%p, Next:%p\t",
			   freelist_head->size,
			   freelist_head,
			   freelist_head->prev,
			   freelist_head->next);
		freelist_head = freelist_head->next;
	}
	printf("\r\n");
}
