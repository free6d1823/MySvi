//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2019] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#include "system_cma.h"
#include "system_assert.h"
#include "acamera_logger.h"

#define ALLOC_ADDR_SIZE ( PHY_ADDR_CDMA - PHY_ADDR_BUFF_POOL )
#define ALLOC_ADDR_START ( PHY_ADDR_BUFF_POOL + 0x100000)//( ALLOC_ADDR_SIZE >> 1 ) )
#define ALLOC_ADDR_END ( PHY_ADDR_BUFF_POOL + ALLOC_ADDR_SIZE )
#define MAX_NODES 2048

typedef struct {
    uint32_t addr;
    size_t size;
} node_t;

static size_t nodes_allocated = 0;
static size_t resmem_used = 0;
static node_t nodes[MAX_NODES] = {0};

// Not in API
static inline void system_cma_print_tracking_info( void )
{
    uint32_t used = (uint32_t)resmem_used;
    uint32_t rem = ALLOC_ADDR_SIZE - used;
    LOG( LOG_NOTICE, "system_cma: used = 0x%x (%u MiB), remaining = 0x%x (%u MiB); %u node(s)", used, used >> 20, rem, rem >> 20, (uint32_t)nodes_allocated );
}

/**
 * @brief      Allocates mem on ddr(area not managed by OS)
 *
 * @param[out] out_virtaddr  pointer to the virtual address pointer (same as phys. address on this platform). Optional, can be NULL.
 * @param[out] out_physaddr  pointer to the physical address address pointer. Optional, can be NULL.
 * @param[in]  size          size of mem in bytes to allocate
 *
 * @return     Returns 0 on success, < 0 on failure
 * 
 * @details    Allocates mem on ddr(on area not managed by OS). 
 *             Will try to allocate in the first unused area closer to ALLOC_ADDR_START
 */
int system_cma_alloc( void **out_virtaddr, uint32_t *out_physaddr, uint32_t size )
{
    int i, j;

    assert( size != 0 );
    if ( nodes_allocated < MAX_NODES ) {
        node_t n = {.addr = ALLOC_ADDR_START, .size = size};
        for ( i = 0; i < nodes_allocated; i++ ) {
            if ( ( n.addr + n.size ) <= nodes[i].addr ) {
                break;
            } else {
                n.addr = nodes[i].addr + nodes[i].size;
            }
        }
        for ( j = nodes_allocated; j > i; j-- ) {
            //move remaining nodes(if any) 1 position right
            nodes[j] = nodes[j - 1];
        }
        if ( ( n.addr + n.size ) <= ALLOC_ADDR_END ) {
            //first node or insert at the end
            nodes[i] = n;
            nodes_allocated++;
            resmem_used += size;
            if ( out_virtaddr != NULL ) {
                *out_virtaddr = (void *)(uintptr_t)n.addr;
            }
            if ( out_physaddr != NULL ) {
                *out_physaddr = (uint32_t)n.addr;
            }
            system_cma_print_tracking_info();
            return 0;
        }
    }
    LOG( LOG_CRIT, "system_cma_alloc(size 0x%x): failed", size );
    system_cma_print_tracking_info();

    if ( out_virtaddr != NULL ) {
        *out_virtaddr = NULL;
    }
    if ( out_physaddr != NULL ) {
        *out_physaddr = 0;
    }
    return -1;
}
/**
 * @brief      Deallocates mem on ddr(allocated with system_cma_alloc)
 *
 * @param      addr  address of start of mem to dealocated
 *
 * @details    Deallocates mem on ddr(allocated with system_cma_alloc). Address has to be allocated.
 */
void system_cma_free( uint32_t addr )
{
    int i;
    size_t size;

    for ( i = 0; i < nodes_allocated; i++ ) {
        if ( nodes[i].addr == addr ) {
            break;
        }
    }

    if ( i >= nodes_allocated ) {
        LOG( LOG_CRIT, "system_dma_free on unallocated addr %08x", addr );
        return;
    }

    size = nodes[i].size;

    for ( ; i < ( nodes_allocated - 1 ); i++ ) {
        nodes[i] = nodes[i + 1];
    }

    nodes_allocated--;
    resmem_used -= size;
    system_cma_print_tracking_info();
}
