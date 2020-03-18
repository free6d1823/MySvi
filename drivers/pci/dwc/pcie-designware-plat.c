// SPDX-License-Identifier: GPL-2.0
/*
 * PCIe RC driver for Synopsys DesignWare Core
 *
 * Copyright (C) 2015-2016 Synopsys, Inc. (www.synopsys.com)
 *
 * Authors: Joao Pinto <Joao.Pinto@synopsys.com>
 */

#include "pcie-designware.h"


static int dw_plat_pcie_host_init(struct pcie_port *pp)
{
	struct dw_pcie *pci = &dw_pci;

	dw_pcie_setup_rc(pp);
	dw_pcie_wait_for_link(pci);

//	if (IS_ENABLED(CONFIG_PCI_MSI))
//		dw_pcie_msi_init(pp);

	return 0;
}

static void dw_plat_set_num_vectors(struct pcie_port *pp)
{
	pp->num_vectors = MAX_MSI_IRQS;
}

static const struct dw_pcie_host_ops dw_plat_pcie_host_ops = {
	.host_init = dw_plat_pcie_host_init,
	.set_num_vectors = dw_plat_set_num_vectors,
};

static int dw_plat_pcie_establish_link(struct dw_pcie *pci)
{
	return 0;
}

static const struct dw_pcie_ops dw_pcie_ops = {
	.start_link = dw_plat_pcie_establish_link,
};

static void dw_plat_pcie_ep_init(struct dw_pcie_ep *ep)
{
#if 0
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	enum pci_barno bar;

	for (bar = BAR_0; bar <= BAR_5; bar++)
		dw_pcie_ep_reset_bar(pci, bar);
#endif
}

static int dw_plat_pcie_ep_raise_irq(struct dw_pcie_ep *ep, u8 func_no,
				     enum pci_epc_irq_type type,
				     u16 interrupt_num)
{
#if 0
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);

	switch (type) {
	case PCI_EPC_IRQ_LEGACY:
		return dw_pcie_ep_raise_legacy_irq(ep, func_no);
	case PCI_EPC_IRQ_MSI:
		return dw_pcie_ep_raise_msi_irq(ep, func_no, interrupt_num);
	case PCI_EPC_IRQ_MSIX:
		return dw_pcie_ep_raise_msix_irq(ep, func_no, interrupt_num);
	default:
		dev_err(pci->dev, "UNKNOWN IRQ type\n");
	}
#endif
	return 0;
}

#if 0
static const struct pci_epc_features dw_plat_pcie_epc_features = {
	.linkup_notifier = false,
	.msi_capable = true,
	.msix_capable = true,
};

static const struct pci_epc_features*
dw_plat_pcie_get_features(struct dw_pcie_ep *ep)
{
	return &dw_plat_pcie_epc_features;
}
#endif
static struct dw_pcie_ep_ops pcie_ep_ops = {
	.ep_init = dw_plat_pcie_ep_init,
	.raise_irq = dw_plat_pcie_ep_raise_irq,
	//.get_features = dw_plat_pcie_get_features,
};

static int dw_plat_add_pcie_ep(struct dw_plat_pcie *dw_plat_pcie)
{
        int ret;
        struct dw_pcie_ep *ep;
        struct dw_pcie *pci = dw_plat_pcie->pci;

        ep = &pci->ep;
        ep->ops = &pcie_ep_ops;

        pci->dbi_base2 = DBI_BASE2_ADDR;

        ep->phys_base = EP_CONF_PHYS_BASE;
        ep->addr_size = EP_CONF_SIZE;

        ret = dw_pcie_ep_init(ep);
        if (ret) {
                printf("Failed to initialize endpoint\n");
                return ret;
        }
        return 0;
}

static int dw_plat_add_pcie_port(struct dw_plat_pcie *dw_plat_pcie)
{
	struct dw_pcie *pci = dw_plat_pcie->pci;
	struct pcie_port *pp = &pci->pp;
	int ret;

	pp->ops = &dw_plat_pcie_host_ops;

	ret = dw_pcie_host_init(pp);
	if (ret) {
		printf("Failed to initialize host\n");
		return ret;
	}

	return 0;
}

int dw_plat_pcie_init(enum dw_pcie_device_mode mode)
{
	int ret;
	struct dw_pcie *pci;
	struct dw_plat_pcie *plat_pci;

	pci = &dw_pci;
	plat_pci = &dw_plat_pci;
	pci->ops = &dw_pcie_ops;
	plat_pci->pci = pci;
	plat_pci->mode = mode;
	pci->dbi_base = (void *)DW_PCIE_DBI0_BASE;

	switch (plat_pci->mode) {
	case DW_PCIE_RC_TYPE:
		ret = dw_plat_add_pcie_port(plat_pci);
		if (ret < 0)
			return ret;
		break;
	case DW_PCIE_EP_TYPE:
		ret = dw_plat_add_pcie_ep(plat_pci);
		if (ret < 0)
			return ret;
		break;
	default:
		printf("INVALID device type %d\n", plat_pci->mode);
	}

	return 0;
}

static struct pci_ops pci_generic_ecam_ops = {
	.read_config	= dw_pcie_rd_config,
	.write_config	= dw_pcie_wr_config,
};
struct pci_controller hose_se1000 = {
	.name = "pcie_dwc",
	.cfg_base = (unsigned int *)0xbb000000,
	.regions = {
				{0x400000000, 0x400000000, 0x400000000, PCI_REGION_MEM},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
			},
	.region_count = 1,
};

int pci_init()
{
	int hose_id;
	int ret;
	enum dw_pcie_device_mode mode = DW_PCIE_RC_TYPE;

	ret = dw_plat_pcie_init(mode);
	if (ret) {
		printf("Failed to initialize dw plat pcie\n");
		return ret;
	}

	hose_se1000.ops = &pci_generic_ecam_ops;
	hose_id = pci_register_hose(&hose_se1000);
	pci_probe_hose(&hose_se1000);

	return 0;
}

int loopback_bar_inbound_iatu_set(struct dw_pcie *pci, phys_addr_t *target)
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

	dw_pcie_dbi_ro_wr_en(pci);
	/* set bar 64-bit&memory mapped bar */
	dw_pcie_writel_dbi(pci, PCI_BASE_ADDRESS_0, 0x100);
	dw_pcie_writel_dbi(pci, PCI_BASE_ADDRESS_1, 0x0);
	dw_pcie_dbi_ro_wr_dis(pci);

	/* set bar space base address */
	dw_pcie_writel_dbi(pci, PCI_BASE_ADDRESS_0, 0x0);
	dw_pcie_writel_dbi(pci, PCI_BASE_ADDRESS_1, 0x4);

	return 0;
}

int dw_loopback_test(phys_addr_t *source, int value, phys_addr_t *target)
{
	int ret;
	int receive_data;
	struct dw_pcie *pci;
	struct dw_plat_pcie *plat_pci;
	enum dw_pcie_device_mode mode = DW_PCIE_RC_TYPE;

	pci = &dw_pci;

	ret = dw_plat_pcie_init(mode);
	if(ret != 0){
		printf("dw_plat_pcie_init fail!\n");
		return ret;
	}

	/* set usp bar */
	ret = loopback_bar_inbound_iatu_set(pci, target);
	if(ret != 0){
		printf("loopback bar inbound iatu set fail!\n");
		return ret;
	}

	dw_enter_loopback_mode(pci);

	__raw_writel(value, source);

	dw_exit_loopback_mode(pci);

	receive_data = readl(target);

	printf("The loopback target addr: 0x%llx,data: 0x%x\n", target, receive_data);

	return 0;
}



