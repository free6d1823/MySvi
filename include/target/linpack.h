#ifndef __LINPACK_H_INCLUDE__
#define __LINPACK_H_INCLUDE__

#define UNROLL
#define DP

#ifdef SP
#define REAL float
#define ZERO 0.0
#define ONE 1.0
#define PREC "Single"
#endif

#ifdef DP
#define REAL double
#define ZERO 0.0e0
#define ONE 1.0e0
#define PREC "Double"
#endif

#ifdef ROLL
#define ROLLING "Rolled"
#endif
#ifdef UNROLL
#define ROLLING "Unrolled"
#endif

/* VERSION */
#ifdef CONFIG_BENCH_OPTIMIZED
    #define options   "Optimised"
    #define opt "1"
#else
    #define options   "Non-optimised"
    #define opt "0"
#endif

#include <time.h>

#define USECS_PER_SEC	(1 * 1000 * 1000)

typedef REAL raa200_t[200*200];
typedef REAL raa201_t[200*201];
typedef REAL ra200_t[200];
typedef int ia200_t[200];
typedef REAL atime_t[9][15];

struct linpack_context {
	raa200_t aa;
	raa201_t a;
	ra200_t b;
	ra200_t x;
	ia200_t ipvt;
	atime_t atime;
	time_t startUsecs;
	time_t usecs;
	uint16_t phase;
};

#define linpack_time()		utime(NULL)

#endif /* __LINPACK_H_INCLUDE__ */
