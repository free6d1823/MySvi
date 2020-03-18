#include <string.h>
#include <stdlib.h>
#include <asm/io.h>
#include <target/console.h>
#include <target/bitops.h>
#include <target/cmdline.h>
#include <errno.h>
#include <target/pci.h>
#include "pcie-designware.h"

int cmd_pci_dw(int argc, char **argv)
{
	phys_addr_t s_addr, t_addr;
	int value;

	if (argc < 2)
		return -EUSAGE;

	if (argc == 5 && !strcmp("loopback", argv[1])) {
		s_addr = strtoul(argv[2], 0, 0);
		value = strtoul(argv[3], 0, 0);
		t_addr = strtoul(argv[4], 0, 0);
		dw_loopback_test((void *)s_addr, value, (void *)t_addr);
		return 0;
	}

	return -EUSAGE;
}

MK_CMD(pcidw, cmd_pci_dw, "PCI host/ep cmd",
	"    arguments: s(source addr) v(write value) t(target addr)\n"
	"pcidw loopback 0x400000000ul 0x12345678 0x3fffff100ul\n"
	"    -PCIe loopback mode test,write addr s with value v, the value should loopback to t\n");

