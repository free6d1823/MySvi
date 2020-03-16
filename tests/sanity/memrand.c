#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <target/memory.h>
#include <target/smp.h>
#include <target/cache.h>

#define ACCESS_SIZE	sizeof(uint64_t)
/* 8192: system percpu variables may allocate 8K TCM */
#if ((TCM_SIZE - 8192) / 48) < L1_CACHE_SIZE
#define CHUNK_SIZE	(L1_CACHE_SIZE / 2)
#else
#define CHUNK_SIZE	L1_CACHE_SIZE
#endif
#define ACCESS_MASK	(CHUNK_SIZE - SMP_CACHE_BYTES)
#define N		(SMP_CACHE_BYTES / ACCESS_SIZE)
#define ACCESS_LOOPS	(CHUNK_SIZE / N / ACCESS_SIZE)

static uintptr_t random_address(uintptr_t area)
{
	uintptr_t rand_addr;

	rand_addr = area + (uintptr_t)(rand() & ACCESS_MASK);
#ifdef CONFIG_MEMTEST_VERBOSE
	printf ("random == %d\n", rand_addr) ;
#endif
	return rand_addr;
}

int memrand(caddr_t area)
{
	uintptr_t rand_addr;
	uint64_t i;

	srand((unsigned)time(0));
	for (i = 0; i < ACCESS_LOOPS; i++) {
		rand_addr = random_address((uintptr_t)area);
		*(uint64_t *)(rand_addr) = i;
	}
	return 1;
}
#ifdef CONFIG_MEMRAND_L1HIT
__define_testfn(memrand, CHUNK_SIZE, SMP_CACHE_BYTES,
		CPU_EXEC_META, 1, CPU_WAIT_INFINITE);
#endif
#ifdef CONFIG_MEMRAND_L1MISS
__define_testfn(memrand, CHUNK_SIZE, SMP_CACHE_BYTES,
		CPU_EXEC_SHARE | CPU_EXEC_META, 1, CPU_WAIT_INFINITE);
#endif
