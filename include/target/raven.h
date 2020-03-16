#ifndef __TEST_RAVEN_H_INCLUDE__
#define __TEST_RAVEN_H_INCLUDE__

#include <target/compiler.h>
#include <target/linkage.h>
#include <target/percpu.h>
#include <target/cpus.h>
#include <target/smp.h>
#include <stdlib.h>

#define RAVEN_ARRAY_SIZE		(128*1024)

/* L1 is per-cpu and L2 is shared by 2-cpus */
#define RAVEN_L1MISS_L2HIT_SIZE		(L1_CACHE_SIZE*2)
#define RAVEN_L2MISS_L3HIT_SIZE		(L2_CACHE_SIZE)

#endif /* __TEST_RAVEN_H_INCLUDE__ */
