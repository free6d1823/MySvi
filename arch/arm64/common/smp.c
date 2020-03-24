#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <target/irq.h>
#include <target/gicv3.h>
#include <target/smp.h>
#include <asm/sysreg.h>
#include <target/cmdline.h>
#include <target/dsr.h>

uint64_t cpu_midr_map[NR_CPUS] = { [0 ... NR_CPUS-1] = 0 };
uint64_t cpu_logical_map[NR_CPUS] = { [0 ... NR_CPUS-1] = INVALID_MPIDR };

static int smp_dsr[NR_CPUS];
static uint16_t smp_event[NR_CPUS];

static void smp_dsr_handler(void)
{
    unsigned int cpu = smp_processor_id();

	switch (smp_event[cpu]) {
		case IPI_SCHEDULE:
			printf("CPU[%d] IPI_SCHEDULE\n", cpu);
		break;
	}

	smp_event[cpu] = 0;
}

void smp_register_cpu()
{
	int phy_id;

	uint64_t mpidr = read_sysreg(mpidr_el1);
	/*
	 *  A55, A75, A76
	 *  Aff0=0,
	 *  Aff1 = Identification number for each cpu in the A55/75/76 CLUSTER
	 */
	phy_id = (MPIDR_AFFINITY_LEVEL(mpidr, 1) << CPUS_SHIFT) + MPIDR_AFFINITY_LEVEL(mpidr, 0);
	if (cpu_logical_map[phy_id] != INVALID_MPIDR) {
		printf("ERROR! duplicate mpidr founded\n");
		return;
	}

	cpu_logical_map[phy_id] = mpidr;
	cpu_midr_map[phy_id] = read_sysreg(midr_el1);

	for (int sgi=IPI_SCHEDULE; sgi<IPI_END; sgi++) {
		irqc_configure_irq(sgi, 32, IRQ_LEVEL_TRIGGERED);
		irqc_enable_irq(sgi);
	}

	smp_dsr[phy_id] = dsr_register(smp_dsr_handler);
}

uint64_t get_mpidr(int cpu)
{
	return cpu_logical_map[cpu];
}

void handle_IPI(int ipinr)
{
	unsigned int cpu = smp_processor_id();

	smp_event[cpu] = ipinr;
	dsr_schedule(smp_dsr[cpu]);
}

static int do_sgi(int argc, char *argv[])
{
	uint8_t cpu, irq;

	if (argc < 3)
		return -EUSAGE;

	cpu = strtoul(argv[1], NULL, 0);
	irq = strtoul(argv[2], NULL, 0);

	if (cpu >=NR_CPUS || cpu_logical_map[cpu] == INVALID_MPIDR) {
		printf("CPU%d is offline, ignore sgi\n", cpu);
		return -1;
	}

	if (irq >= IPI_END) {
		printf("invalid sgi number\n");
		return -1;
	}

	gicv3_trigger_sgi(irq, cpu);

	return 0;
}

static  int do_smplist(int argc, char *argv[])
{
	int partnum;
	printf("online-cpu    type    mpidr\n");

	for (int i=0; i<NR_CPUS; i++) {
		if (cpu_logical_map[i] != INVALID_MPIDR) {
			partnum = (cpu_midr_map[i] >> MIDR_PARTNUM_SHIFT) & MIDR_PARTNUM_MASK;
			printf("%d%*s", i, 13, " ");

			if (partnum == CORTEXA76_MIDR_PARTNUM)
				printf("A76");
			else if (partnum == CORTEXA55_MIDR_PARTNUM)
				printf("A55");
			else
				printf("unknown");

			printf("%*s%#016llx\n", 5, " ", cpu_logical_map[i]);
		}
	}

	return 0;
}

MK_CMD(smplist, do_smplist, "list online cpus",
	"smplist\n"
);

MK_CMD(sgi, do_sgi, "SGI sending command",
	"sgi cpu irq\n"
	"	 - cpu: 0-7\n"
	"	 - irq: 0-15\n"
);

