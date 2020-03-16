#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <target/cmdline.h>
#include <target/bench.h>
#include <target/spinlock.h>


/*used for test spinlock*/
spinlock_t sysmem_lock;
spinlock_t *test_lock;

int test_spinlock()
{
	unsigned int cpu_id = smp_processor_id();

	printf("---cpu %d :waiting for lock \n", cpu_id);
	__spin_lock(test_lock);
	printf("---cpu %d : get the lock \n", cpu_id);
	__spin_unlock(test_lock);
	printf("---cpu %d : release the lock \n", cpu_id);
	return 0;
}

static pattern_case_t spinlock_test = {
	.name = "spinlock",
	.dic = "test spinlock",
	.ptr = (void*)test_spinlock,
	.work_cpu = (C0|C1|C2),
	.flag_assign = SET,
	.flag_reset = RESET,
	.flag_power = SET,
	.creat_mission_table = default_creat_mission_tabel,
 };

int spinlock_test_init()
{
	pattern_vf_register("spinlock", test_spinlock, 0);
	return pattern_case_init(&spinlock_test);
}

static int do_spinlock_test(int argc, char * argv[])
{
	char *cmd;
	uint64_t *addr;

	cmd = argv[1];

	if(!strcmp(cmd, "init")){
		if(argc < 2 || argc > 3) {
			printf("Please input the correct num of argument \n");
			return -1;
		}

		test_lock = &sysmem_lock;

		if(argc == 3) {
			cmd = argv[2];
			if(!strcmp(cmd, "d")) {
				test_lock = (void*)0x1000;
			} else if(!strcmp(cmd, "i")) {
				test_lock = (void*)0xff6f800000LL;
			} else if(!strcmp(cmd, "s")) {
				test_lock = &sysmem_lock;
			} else {
				addr = (void *)strtoul(cmd, NULL, 0);
				test_lock = (void *)addr;
			}
		}

		memset((void*)test_lock, 0, sizeof(spinlock_t));
		test_lock->lock = 0;

		return 1;
	}

	if(!strcmp(cmd, "lock")) {
		__spin_lock(test_lock);
		printf("----IMC get the lock ------\n");
		return 1;
	}

	if(!strcmp(cmd, "unlock")) {
		__spin_unlock(test_lock);
		return 1;
	}

	return 1;
}

MK_CMD(ex, do_spinlock_test, "test exclusive monitor",
	" -test exclusive monitor\n"
	"help command ...\n"
	" ex init [d|i|s]|[addr] \n"
	"---IMC init the lock at ddr/imem/sysmem or the input addr\n"
	" ex lock --- IMC get the lock \n"
	" ex unlock --IMC release the lock\n"
	"\n"
);
