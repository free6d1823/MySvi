#include <asm/psci.h>
#include <stdio.h>
#include <asm/exception.h>
#include <target/cmdline.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

uint64_t entry_addr;   //save the secondary entrypoint

unsigned int psci_version(void)
{
	return PSCI_MAJOR_VER | PSCI_MINOR_VER;
}

int psci_feature(unsigned int psci_fid)
{
	return PSCI_E_NOT_SUPPORTED;
}

int psci_migrate_info_type(void)
{
	return PSCI_E_NOT_SUPPORTED;
}

unsigned long psci_smc_handler(struct pt_regs *regs)
{
	uint64_t ret;
	uint64_t smc_fid, x1, x2, x3;

	smc_fid = regs->regs[0];
	x1 = regs->regs[1];
	x2 = regs->regs[2];
	x3 = regs->regs[3];

	switch (smc_fid) {
	case PSCI_VERSION:
		printf("PSCI_VERSION\n");
		ret = psci_version();
		break;

	case PSCI_FEATURES:
		printf("PSCI_FEATURES 0x%08x\n", x1);
		ret = psci_feature(x1);
		break;

	case PSCI_MIG_INFO_TYPE:
		printf("PSCI_MIG_INFO_TYPE 0x%08x\n", x1);
		ret = psci_feature(x1);
		break;

	case PSCI_CPU_ON_AARCH64:
		printf("PSCI_CPU_ON_AARCH64 0x%08x, 0x%08x, 0x%08x\n", x1, x2, x3);
		ret =  psci_cpu_on(x1, x2, x3);
		break;

	default:
		printf("PSCI function 0x%08x\n", smc_fid);
		ret = (uint64_t)SMC_UNK;
		break;
	}

	return ret;
}

static int do_psci(int argc, char *argv[])
{
	uint64_t mpidr;

	if (argc < 3)
		return -EUSAGE;

	mpidr = strtoul(argv[2], NULL, 0);

	if (strcmp(argv[1], "on") == 0)
		smc_psci(PSCI_CPU_ON_AARCH64, mpidr, 0, 0);
	else
		return -EUSAGE;

	return 0;
}

MK_CMD(psci, do_psci, "PSCI functions command",
	"psci on/off mpidr\n"
	"	 - on: CPU_ON, off: CPU_OFF\n"
	"	 - mpidr: MPIDR_EL1 & 0xff00ffffff\n"
);
