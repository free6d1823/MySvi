#include <string.h>
#include <stdbool.h>
#include "pci.h"

static struct pci_ops pci_generic_ecam_ops = {
	.read_config	= pci_generic_mmap_read_config,
	.write_config	= pci_generic_mmap_write_config,
};

static struct pci_controller hose_qemu_virt = {
	.name = "pcie_virt",
	.cfg_base = (unsigned int *)0x4010000000,
	.regions = {
				{0,          0x3eff0000, 0x10000,    PCI_REGION_IO},
				{0x10000000, 0x10000000, 0x2eff0000, PCI_REGION_MEM},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
			},
	.region_count = 2,
};


int pci_init()
{
	int hose_id;

	hose_qemu_virt.ops = &pci_generic_ecam_ops;
	hose_id = pci_register_hose(&hose_qemu_virt);

	pci_probe_hose(&hose_qemu_virt);

	return 0;
}

