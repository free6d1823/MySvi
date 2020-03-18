/*
 */
#ifndef __CORTEXM4_CACHE_H_INCLUDE__
#define __CORTEXM4_CACHE_H_INCLUDE__

#define L1_LINE_SHIFT		6
#define L1_CACHE_BYTES		(1 << L1_LINE_SHIFT)
#define L1_INTERLEAVE_BYTES	128
#define L1_CACHE_WAYS		8

#define L2_LINE_SHIFT		7
#define L2_CACHE_BYTES		(1 << L2_LINE_SHIFT)
#define L2_INTERLEAVE_BYTES	128
#define L2_CACHE_WAYS		8

#define L3_LINE_SHIFT		6
#define L3_CACHE_BYTES		(1 << L3_LINE_SHIFT)
#define L3_INTERLEAVE_BYTES	128
#define L3_CACHE_WAYS		20

#ifdef __ASSEMBLY__
#define L1_CACHE_SIZE		32768
#define L2_CACHE_SIZE		524288
#define L3_CACHE_SIZE		20971520
#else
#define L1_CACHE_SIZE		(32ULL << 10)
#define L2_CACHE_SIZE		(512ULL << 10)
#define L3_CACHE_SIZE		(60ULL << 20)
#endif

/* Index of L3 blocks */
#define L3_CACHE_BLOCKS		12
#define L3_BLOCK_SHIFT		8
#define L3_BLOCK_MASK		(0xF)
#define L3_BLOCK(phys)		\
	(((phys) & (L3_BLOCK_MASK << L3_BLOCK_SHIFT)) >> L3_BLOCK_SHIFT)

#define __SMP_CACHE_SHIFT	7

#endif /* __CORTEXM4_CACHE_H_INCLUDE__ */

