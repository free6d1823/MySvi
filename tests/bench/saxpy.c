#define UNROLL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef HOSTED
#include <target/compiler.h>
#include <target/smp.h>
#include <target/schedule.h>
#define printf
#endif

#ifdef HOSTED
#include <errno.h>
#define utime(x)	(time(x) * 1000 * 1000)
#endif

#define SAXPY_SIZE	120

#define USECS_PER_SEC	(1 * 1000 * 1000)

#ifdef CONFIG_SAXPY_TIMEOUT
#define SAXPY_TIMEOUT		CONFIG_SAXPY_TIMEOUT
#else
#define SAXPY_TIMEOUT		(1 * 1000 * 1000)
#endif
#ifdef CONFIG_SAXPY_REPEATS
#define SAXPY_REPEATS		CONFIG_SAXPY_REPEATS
#else
#define SAXPY_REPEATS		50000
#endif

void cblas_saxpy(const int N, const float alpha,
		 const float *X, const int incX,
		 float *Y, int incY)
{
	int i, ix, iy, m, mp1;

	mp1 = 0;
	m = 0;
	if (N <= 0) return;
	if (alpha == 0.0) return;
	if (incX != 1 || incY != 1) {
		ix = 0;
		iy = 0;
                if (incX < 0) ix = (-N + 1) * incX;
                if (incY < 0) iy = (-N + 1) * incY;
		for (i = 0; i < N; i++) {
			Y[iy] = Y[iy] + alpha * X[ix];
			ix = ix + incX;
			iy = iy + incY;
		}
		return;
	}

#ifdef ROLL
	for (i = 0;i < N; i++) {
		Y[i] = Y[i] + alpha * X[i];
	}
#endif
#ifdef UNROLL
	m = N % 4;
	if (m != 0) {
		for (i = 0; i < m; i++)
			Y[i] = Y[i] + alpha * X[i];
		if (N < 4) return;
	}
	for (i = m; i < N; i = i + 4) {
		Y[i] = Y[i] + alpha * X[i];
		Y[i + 1] = Y[i + 1] + alpha * X[i + 1];
		Y[i + 2] = Y[i + 2] + alpha * X[i + 2];
		Y[i + 3] = Y[i + 3] + alpha * X[i + 3];
	}
#endif
}

typedef float saxpy_operand[SAXPY_SIZE];
typedef char saxpy_results[SAXPY_SIZE][20];

struct saxpy_context {
	saxpy_operand X;
	saxpy_operand Y;
#ifdef CONFIG_SAXPY_EXPECT
	saxpy_results expect;
	saxpy_results was;
#endif
};
#define X		ctx->X
#define Y		ctx->Y
#define expect		ctx->expect
#define was		ctx->was

#ifdef HOSTED
int main(int argc, char *argv[])
#else
int saxpy_pcpu(caddr_t percpu_area)
#endif
{
	int i;
	int n = SAXPY_SIZE;
/*	float a[SAXPY_SIZE * SAXPY_SIZE] = { 4, 1, 1, 3 }; */
	float base = 1.0;
	float a = 2.0;
	int errors = 0;
	int index;
	int num_of_runs = SAXPY_REPEATS;
	ktime_t expected_end_time = SAXPY_TIMEOUT;
	ktime_t begin_time, end_time;

	struct saxpy_context *ctx = (struct saxpy_context *)percpu_area;

#ifdef CONFIG_SAXPY_EXPECT
	for (i = 0; i < n; i++) {
		X[i] = base;
		Y[i] = 0.0;
		base *= a;
		sprintf(expect[i], "%16.8e", base);
	}
#endif
	cblas_saxpy(n, a, X, 1, Y, 1);
#ifdef CONFIG_SAXPY_EXPECT
	for (i = 0; i < n; i++) {
		sprintf(was[i], "%16.8e", Y[i]);
		if (strcmp(expect[i], was[i]) != 0) {
			printf("Wrong result was %s instead of %s\n",
			       was[i], expect[i]);
			errors++;
		}
	}
#endif

	begin_time = utime(NULL);
	expected_end_time += utime();

again:
	for (index = 0; index < num_of_runs; ++index) {
		if (unlikely(index == 1))
			begin_time = utime(NULL);
		cblas_saxpy(n, a, X, 1, Y, 1);
		if (unlikely(index % 10000 == 0) &&
		    time_after(utime(), expected_end_time)) {
			num_of_runs = index;
			break;
		}
	}
	end_time = utime(NULL);
	printf("CPU %d:\n", smp_processor_id());
	printf("Number of runs:                             %d\n",
	       num_of_runs);
	printf("User time (us):                             %llu\n",
	       (uint64_t)(end_time - begin_time));

	/* code for both increments equal to 1 */
#ifndef HOSTED
	schedule_mailbox_log("ts@%lld runs=%d User time (us)=%llu errors=%d\n",
	                     end_time, num_of_runs, (uint64_t)(end_time - begin_time), errors);
	schedule_notify_taskended();
#endif

	return 0;
}

#ifndef HOSTED
__define_testfn(saxpy_pcpu, sizeof (struct saxpy_context), SMP_CACHE_BYTES,
		0, 0, 0);
#endif
