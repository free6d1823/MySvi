/*
 */
#ifndef __QDF2400_CBF_H_INCLUDE__
#define __QDF2400_CBF_H_INCLUDE__

#define MAX_L3_BLOCKS	12

#ifndef __ASSEMBLY__
/*
 * Converting L3 partial good fuse into L3 block partial good.
 */
static inline uint64_t cbf_get_l3_block_mask(uint64_t llc_mask)
{
    uint64_t block_mask;

    block_mask = (((llc_mask) & 0xaaaaaa) >> 1) | ((llc_mask) & 0x555555);
    block_mask = (((block_mask) & 0x444444) >> 1) | ((block_mask) & 0x111111);
    block_mask = (((block_mask) & 0x303030) >> 2) | ((block_mask) & 0x030303);
    block_mask = (((block_mask) & 0x000f00) >> 4) | ((block_mask) & 0x0f000f);
    return (((block_mask) & 0x0f0000) >> 8) | ((block_mask) & 0x0000ff);
}

void cbf_init_l3_block(uint8_t l3bnr);
int cbf_init_l3_blocks(void);
#endif /* __ASSEMBLY__ */

#endif /* __QDF2400_CBF_H_INCLUDE__ */
