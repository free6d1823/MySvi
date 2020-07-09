#include <string.h>
#include <stdlib.h>
#include <asm/io.h>
#include <target/console.h>
#include <target/bitops.h>
#include <target/cmdline.h>
#include <errno.h>
#include <target/pci.h>
#include "pcie-designware.h"


struct pci_epf_header pci_hrd;
struct pci_epf_bar pci_bar;

void dw_enter_loopback_mode(struct dw_pcie *pci)
{
	u32 val;

	val = dw_pcie_readl_dbi(pci, GEN3_RELATED_OFF);
	/* set Gen3Equalization Disable bit */
	val |= 0x10000;
	dw_pcie_writel_dbi(pci, GEN3_RELATED_OFF, val);

	val = dw_pcie_readl_dbi(pci, PIPE_LOOPBACK_CONTROL_OFF);
	val |= 0x80000000;
	dw_pcie_writel_dbi(pci, PIPE_LOOPBACK_CONTROL_OFF, val);

	val = dw_pcie_readl_dbi(pci, PCIE_PORT_LINK_CONTROL);
	val |= 0x4;
	dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);
}

void dw_exit_loopback_mode(struct dw_pcie *pci)
{
	u32 val;

	val = dw_pcie_readl_dbi(pci, PCIE_PORT_LINK_CONTROL);
	val &= 0xfffffffb;
	dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);

	val = dw_pcie_readl_dbi(pci, PIPE_LOOPBACK_CONTROL_OFF);
	val &= 0x7fffffff;
	dw_pcie_writel_dbi(pci, PIPE_LOOPBACK_CONTROL_OFF, val);
}

void loopback_bar_set(struct dw_pcie *pci)
{
	struct pcie_port *pp = &pci->pp;

	/* set bar 64-bit&memory mapped bar */
	dw_pcie_writel_dbi(pci, PCI_BASE_ADDRESS_0, pp->mem_bus_addr);
}


int loopback_inbound_iatu_set(struct dw_pcie *pci, phys_addr_t *target)
{
	int ret;
	enum dw_pcie_as_type as_type = DW_PCIE_AS_MEM;
	enum pci_barno bar = BAR_0;
	u32 free_win = PCIE_ATU_REGION_INDEX0;

	ret = dw_pcie_prog_inbound_atu(pci, free_win, bar, (u64)target,
			as_type);
	if (ret < 0) {
		printf( "Failed to program IB window\n");
		return ret;
	}

	return 0;
}



int write_header(u32 id)
{
	struct dw_pcie *pci;
	int ret;
	struct pci_epc *epc;
	struct pci_epf_header *hrd = &pci_hrd;
	u8 fun_id = 0;

	pci = hose_se1000[id].driver_data;
	epc = pci->ep.epc;
	epc->driver_data = pci;

	hrd->vendorid = 0x5555;
	hrd->deviceid = 0x6666;
	hrd->revid = 0x77;
	hrd->progif_code = 0x88;
	hrd->baseclass_code = 0x99;
	hrd->subsys_vendor_id = 0x4444;
	hrd->subsys_id = 0x3333;
	ret = epc->ops->write_header(epc, fun_id, hrd);
	return ret;
}

int rc_set_outbound(u32 id)
{
        struct dw_pcie *pci;
        int ret;
        struct pcie_port *pp;
	int type = PCIE_ATU_TYPE_MEM;

	pci = hose_se1000[id].driver_data;
	pp = &pci->pp;

	dw_pcie_prog_outbound_atu(pci, PCIE_ATU_REGION_INDEX0,
			type, pp->mem_base, pp->mem_bus_addr, pp->mem_size);

	return 0;
}

int ep_map_addr(u32 id, u8 fun_id, dma_addr_t cpu_addr, u64 bus_addr, size_t si)
{
        struct dw_pcie *pci;
        int ret;
        struct pci_epc *epc;
        struct pci_epf_bar *bar = &pci_bar;
		u64 pci_addr = bus_addr;

        pci = hose_se1000[id].driver_data;
        epc = pci->ep.epc;
        epc->driver_data = pci;

        bar->phys_addr = cpu_addr;
        bar->size = si;
        bar->flags = PCI_BASE_ADDRESS_SPACE_MEMORY;
        bar->barno = 1;

        ret = epc->ops->map_addr(epc, fun_id, bar->phys_addr,pci_addr,bar->size);
        return ret;
}


int ep_set_bar(u32 id, u8 fun_id, dma_addr_t cpu_addr, size_t si)
{
	struct dw_pcie *pci;
        int ret;
        struct pci_epc *epc;
        struct pci_epf_bar *bar = &pci_bar;

        pci = hose_se1000[id].driver_data;
        epc = pci->ep.epc;
        epc->driver_data = pci;

	bar->phys_addr = cpu_addr;
	bar->size = si;
	bar->flags = PCI_BASE_ADDRESS_SPACE_MEMORY;
	bar->barno = 0;

	ret = epc->ops->set_bar(epc, fun_id, bar);
	return ret;
}

int dw_loopback_test(u32 id, phys_addr_t *source, int value, phys_addr_t *target)
{
	int ret;
	int receive_data;
	struct dw_pcie *pci;

	pci = hose_se1000[id].driver_data;
	struct pcie_port *pp = &pci->pp;

	pp->mem_base = (u64)source;

	ret = dw_plat_pcie_init(pci);
	if(ret != 0){
		printf("dw_plat_pcie_init fail!\n");
		return ret;
	}

	/* set usp bar */
	ret = loopback_inbound_iatu_set(pci, target);
	if(ret != 0){
		printf("loopback bar inbound iatu set fail!\n");
		return ret;
	}

	loopback_bar_set(pci);

	dw_enter_loopback_mode(pci);

	__raw_writel(value, source);

	dw_exit_loopback_mode(pci);

	receive_data = __raw_readl(target);

	printf("The loopback target addr: 0x%llx,data: 0x%x\n", target, receive_data);

	return 0;
}

int cmd_pci_dw(int argc, char **argv)
{
	phys_addr_t s_addr, t_addr;
	phys_addr_t cpu_addr;
	u64 bus_addr;
	size_t size;
	u8 fun_id;
	int value;
	u32 id;

	if (argc < 2)
		return -EUSAGE;

	if(argc == 2)
		id = 0;
	else
		id = strtoul(argv[2], 0, 0);

	if (!strcmp("init", argv[1])) {
		pci_init(id);
		return 0;
	}

	if (!strcmp("wh", argv[1])) {
		write_header(id);
		return 0;
	}

        if (!strcmp("rso", argv[1])) {
		id = strtoul(argv[2], 0, 0);
		rc_set_outbound(id);
		return 0;
        }

        if (!strcmp("esb", argv[1])) {
		id = strtoul(argv[2], 0, 0);
		fun_id = strtoul(argv[3], 0, 0);
		cpu_addr = strtoul(argv[4], 0, 0);
		size = strtoul(argv[5], 0, 0);
		ep_set_bar(id,fun_id, cpu_addr, size);
		return 0;
        }

        if (!strcmp("ema", argv[1])) {
		id = strtoul(argv[2], 0, 0);
		fun_id = strtoul(argv[3], 0, 0);
		cpu_addr = strtoul(argv[4], 0, 0);
		bus_addr = strtoul(argv[5], 0, 0);
		size = strtoul(argv[6], 0, 0);
		ep_map_addr(id, fun_id, cpu_addr, bus_addr, size);
		return 0;
	}

	if (argc == 6 && !strcmp("loopback", argv[1])) {
		id = strtoul(argv[2], 0, 0);
		s_addr = strtoul(argv[3], 0, 0);
		value = strtoul(argv[4], 0, 0);
		t_addr = strtoul(argv[5], 0, 0);
		dw_loopback_test(id, (void *)s_addr, value, (void *)t_addr);
		return 0;
	}

	return -EUSAGE;
}

MK_CMD(pcidw, cmd_pci_dw, "PCI host/ep cmd",
	"    arguments: s(source addr) v(write value) t(target addr)\n"
	"pcidw wh"	
	"    -PCIe write header with default value\n"
	"pcidw rso"	
	"    -PCIe RC config outbound atu\n"
	"pcidw esb hose fun cpu_addr size"
	"    -PCIe ep set bar\n"
	"pcidw ema hose fun cpu_addr pci_addr size"	
	"    -PCIe ep map addr\n"
	"pcidw loopback 0x400000000ul 0x12345678 0x3fffff100ul\n"
	"    -PCIe loopback mode test,write addr s with value v, the value should loopback to t\n");

