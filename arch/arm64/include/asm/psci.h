#ifndef PSCI_H
#define PSCI_H
#include <stdint.h>

#define SMC_UNK 0xFFFFFFFF

#define FUNCID_CC_SHIFT         30      /*bit30 ndicate 32 or 64 calling convention*/
#define FUNCID_CC_MASK          0x1
#define SMC_64                  1
#define PSCI_CPU_ON_AARCH64     0xc4000003
#define PSCI_VERSION            0x84000000
#define PSCI_MIG_INFO_TYPE      0x84000006
#define PSCI_FEATURES           0x8400000A

#define PSCI_MAJOR_VER      (1) << 16
#define PSCI_MINOR_VER      0x0

/*******************************************************************************
 * PSCI error codes
 ******************************************************************************/
#define PSCI_E_SUCCESS		0
#define PSCI_E_NOT_SUPPORTED	-1
#define PSCI_E_INVALID_PARAMS	-2
#define PSCI_E_DENIED		-3
#define PSCI_E_ALREADY_ON	-4
#define PSCI_E_ON_PENDING	-5
#define PSCI_E_INTERN_FAIL	-6
#define PSCI_E_NOT_PRESENT	-7
#define PSCI_E_DISABLED		-8
#define PSCI_E_INVALID_ADDRESS	-9


/* The macros below are used to identify PSCI calls from the SMC function ID */
#define PSCI_FID_MASK			0xffe0u
#define PSCI_FID_VALUE			0u

#define is_psci_fid(_fid) \
	(((_fid) & PSCI_FID_MASK) == PSCI_FID_VALUE)

extern uint64_t entry_addr;

int psci_cpu_on(uint64_t target_cpu,
                uint64_t entrypoint,
                uint64_t context_id);

int smc_psci(unsigned long a0, unsigned long a1,
			unsigned long a2, unsigned long a3);


#endif
