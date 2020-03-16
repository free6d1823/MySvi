/*
 * Copyright (c) 2016 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 *
 * Copyright (c) 2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include <string.h>
#include <testos.h>

#ifdef CONFIG_QPOWER_TIMEOUT
#define POWER_VIRUS_TIMEOUT	CONFIG_QPOWER_TIMEOUT
#else
#define POWER_VIRUS_TIMEOUT	(1 * 1000 * 1000)
#endif
#ifdef CONFIG_QPOWER_REPEATS
#define POWER_VIRUS_REPEATS	CONFIG_QPOWER_REPEATS
#else
#define POWER_VIRUS_REPEATS	50000
#endif

/*
 * The Assembly macros below are ported with necessary assumptions to keep
 * similar structure from the below location:
 * /prj/qct/chips/hawker/austin/teams/vi_common/work/vi_hawker/v1.0/apetrusk_head_hawker_verif_vi_clone/tests/vi_power/strem_test/src/PowerVirus_64bit_FMLA_1c.s
 */

/* Assumes X1 and X2 registers to be properly populated */
#define SX_BLK	"FADD       V0.2S, V6.2S, V6.2S\n\t"	\
		"FMLA       V6.4S, V6.4S, V14.4S\n\t"	\
		"ST1       {V7.4S}, [X2]\n\t"		\
		"ST1       {V15.2S}, [X2]\n\t"		\
		"FMLA       V7.4S, V7.4S, V15.4S\n\t"	\
		"LD1       {V6.4S, V7.4S}, [X1]\n\t"	\
		"FMLA       V8.4S, V8.4S, V14.4S\n\t"	\
		"ST1       {V9.4S}, [X2]\n\t"		\
		"FMLA       V9.4S, V9.4S, V15.4S\n\t"	\
		"LD1       {V8.4S, V9.4S}, [X1]\n\t"	\
		"FADD       V0.2S, V14.2S, V14.2S\n\t"	\
		"FMLA       V10.4S, V10.4S, V14.4S\n\t"	\
		"ST1       {V11.4S}, [X2]\n\t"		\
		"ST1       {V15.2S}, [X2]\n\t"		\
		"FMLA       V11.4S, V11.4S, V15.4S\n\t"	\
		"LD1       {V10.4S, V11.4S}, [X1]\n\t"	\
		"FMLA       V12.4S, V12.4S, V14.4S\n\t"	\
		"ST1       {V13.4S}, [X2]\n\t"		\
		"FMLA       V13.4S, V13.4S, V15.4S\n\t"	\
		"LD1       {V12.4S, V13.4S}, [X1]\n\t"

/*
 * Assumes X0 to contain the offset within INITVRF amd DSEND for corresponding
 * CPU
 * registers(V* and X1, X2) will be populated accordingly
 */
#define LDR0 \
	"LDR    X1, =INITVRF\n\t"			\
	"ADD    X1, X1, X0 \n\t"			\
	"LDR    X1, [X1] \n\t"				\
	"LD1    {V14.4S},	[X1], #0x10\n\t"	\
	"LD1    {V15.4S},	[X1]\n\t"		\
	"LD1    {V0.4S},    [X1]\n\t"			\
	"LD1    {V1.4S},    [X1]\n\t"			\
	"LD1    {V2.4S},    [X1]\n\t"			\
	"LD1    {V3.4S},    [X1]\n\t"			\
	"LD1    {V4.4S},    [X1]\n\t"			\
	"LD1    {V5.4S},	[X1], #0x10 \n\t"	\
	"LD1    {V6.4S},	[X1]\n\t"		\
	"LD1    {V8.4S},	[X1]\n\t"		\
	"LD1    {V10.4S},	[X1]\n\t"		\
	"LD1    {V12.4S},	[X1], #0x10\n\t"	\
	"LD1    {V7.4S},    [X1]\n\t"			\
	"LD1    {V9.4S},    [X1]\n\t"			\
	"LD1    {V11.4S},   [X1]\n\t"			\
	"LD1    {V13.4S},   [X1]\n\t"			\
	"LDR    X1, =INITVRF\n\t"			\
	"ADD    X1, X1, X0 \n\t"			\
	"LDR    X1, [X1] \n\t"				\
	"ADD    X1, X1, #0x20\n\t"				\
	"LDR    X2, =DSEND\n\t"				\
	"ADD    X2, X2, X0 \n\t"			\
	"LDR    X2, [X2] \n\t"


#define SAXBSTART	   \
	"NOP \n\t"	   \
	"NOP \n\t"	   \
	"NOP \n\t"	   \
	"NOP \n\t"	   \
	"NOP \n\t"	   \
	"NOP \n\t"	   \
	"NOP \n\t"	   \
	"NOP \n\t"	   \
	"NOP \n\t"

#define SAXBRUNS					\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK						\
	SX_BLK

uint32_t init_data[]= {
	0x44000000, 0x44000000, 0x44000000, 0x44000000,
	0x3fffffff, 0x3fffffff, 0x3fffffff, 0x3fffffff,
	0x3fffffff, 0x3fffffff, 0x3fffffff ,0x3fffffff,
	0x3fA49249, 0x3fA49249, 0x3fA49249, 0x3fA49249,
};

/* Stores the offset for each CPUs instance */
uint32_t internal_INITVRF[MAX_CPU_NUM][16+4]; //4 for SPACE 128
uint64_t internal_DSEND[MAX_CPU_NUM][2];  //2 for SPACE 128
uint32_t *INITVRF[MAX_CPU_NUM];
uint64_t *DSEND[MAX_CPU_NUM];

static DEFINE_SPINLOCK(power_virus_lock);

/*
 * This function may be called more than once on a given core
 * If that's not correct change the usage in power_virus
 */
static void init_power_virus_per_cpu()
{
	int my_core_id;

	my_core_id = smp_processor_id();

	/* Initialize the offset arrays */
	INITVRF[my_core_id] = internal_INITVRF[my_core_id];
	DSEND[my_core_id] = internal_DSEND[my_core_id];
	memcpy(internal_INITVRF[my_core_id], init_data, sizeof(init_data));

	/* Future TODO:
	 * Set max supported frequency, since current(1/22/2016) default is Max
	 * and no CPPC APIs available skip for now
	 */
}


/*
 * we don't want this function inlined
 */
void noinline power_virus_single_iter(int offset)
{
	/* offset in X0 */
	__asm volatile(LDR0);
	__asm volatile(SAXBSTART);
	__asm volatile(SAXBRUNS);
}

uint64_t power_virus_num_of_runs(void)
{
	return POWER_VIRUS_REPEATS;
}

uint64_t power_virus_expected_timeout(void)
{
	return POWER_VIRUS_TIMEOUT;
}

/*
 * Runs a multiple iteration of power virus
 */
#ifdef HOSTED
int main(int argc, char *argv[])
#else
int qpower(caddr_t percpu_area)
#endif
{
	uint64_t offset_in_bytes = sizeof(void*)*smp_processor_id();
	int errors = 0;
	int index;
	int num_of_runs = power_virus_num_of_runs();
	ktime_t expected_end_time = power_virus_expected_timeout();
	ktime_t begin_time, end_time;

	init_power_virus_per_cpu();
	begin_time = utime(NULL);
again:
	for (index = 0;
	     likely(num_of_runs == TESTOS_ENDLESS ||
		    index < num_of_runs); ++index) {
		if (unlikely(index == 1))
			begin_time = utime(NULL);
		power_virus_single_iter(offset_in_bytes);
		power_virus_single_iter(offset_in_bytes);
		power_virus_single_iter(offset_in_bytes);
		power_virus_single_iter(offset_in_bytes);
		if (unlikely(index % 10000 == 0) &&
		    expected_end_time != TESTOS_INFINITE &&
		    time_after(utime(), expected_end_time)) {
			num_of_runs = index;
			break;
		}
	}
	end_time = utime(NULL);
	spin_lock(&power_virus_lock);
	printf("CPU %d:\n", smp_processor_id());
	printf("Number of runs:                             %d\n",
	       num_of_runs);
	printf("User time (us):                             %llu\n",
	       (uint64_t)(end_time - begin_time));
	spin_unlock(&power_virus_lock);
	/* code for both increments equal to 1 */
	return errors ? 0 : 1;
}
__define_testfn(qpower, 0, SMP_CACHE_BYTES,
		CPU_EXEC_META, 1, CPU_WAIT_INFINITE);
