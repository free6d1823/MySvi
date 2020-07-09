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
	struct dw_pcie *pci = container_of(pp, struct dw_pcie, pp);

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
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	enum pci_barno bar;

	for (bar = BAR_0; bar <= BAR_5; bar++)
		dw_pcie_ep_reset_bar(pci, bar);
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

static int dw_add_pcie_ep(struct dw_pcie *pci)
{
        int ret;
        struct dw_pcie_ep *ep;

        ep = &pci->ep;
        ep->ops = &pcie_ep_ops;

        ret = dw_pcie_ep_init(ep);
        if (ret) {
                printf("Failed to initialize endpoint\n");
                return ret;
        }
        return 0;
}

static int dw_add_pcie_port(struct dw_pcie *pci)
{
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

int dw_plat_pcie_init(struct dw_pcie *pci)
{
	int ret;

	switch (pci->mode) {
	case DW_PCIE_RC_TYPE:
		ret = dw_add_pcie_port(pci);
		if (ret < 0)
			return ret;
		break;
	case DW_PCIE_EP_TYPE:
		ret = dw_add_pcie_ep(pci);
		if (ret < 0)
			return ret;
		break;
	default:
		printf("INVALID device type %d\n", pci->mode);
	}

	return 0;
}

static struct pci_ops pci_generic_ecam_ops = {
	.read_config	= dw_pcie_rd_config,
	.write_config	= dw_pcie_wr_config,
};

struct resource	busn_se1000 = {
	 .start = 0,
	 .end = 255,
};


struct dw_pcie dw_pci[4] = {
	{
		.ops = &dw_pcie_ops,
		.dbi_base = (void *)0xbb000000,
		.num_viewport = 2,
		.mode = DW_PCIE_RC_TYPE,
		.pp.cfg0_base = 0xbb000000,
		.pp.cfg0_size = 0x100000 >> 1,
		.pp.cfg1_base = 0xbb080000,
		.pp.cfg1_size = 0x100000 >> 1,
		.pp.busn = &busn_se1000,
		.private_data = &hose_se1000[0],
	},
	{
		.ops = &dw_pcie_ops,
		.dbi_base = (void *)0xbb000000,
		.dbi_base2 = (void *)0x0,
		.ep.phys_base = 0xbb000000,
		.ep.addr_size = 0x100000,
		.ep.num_ib_windows = EP_IB_WIN_NUM,
		.ep.num_ob_windows = EP_OUT_WIN_NUM,
		.ep.max_fun = 1,
		.mode = DW_PCIE_EP_TYPE,
		.private_data = &hose_se1000[1],
	},
};

struct pci_controller hose_se1000[4] = {
	{
		.name = "pcie_dwc",
		.cfg_base = (unsigned int *)0xbb000000,
		.regions = {
				{0x40000000, 0x40000000, 0x400000000, PCI_REGION_MEM},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
			},
		.region_count = 1,
		.driver_data = &dw_pci[0],
	},
	{
		.name = "pcie_dwc_ep",
		.cfg_base = (unsigned int *)0x725000000,
		.regions = {
				{0x82000000, 0x72600000, 0x100000, PCI_REGION_MEM},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
				{0,          0,          0,          0},
			},
		.region_count = 1,
		.driver_data = &dw_pci[1],
	},
};

int pci_init(u32 id)
{
	int hose_id;
	int ret;
	struct dw_pcie *pci;

	if(id >= 4)
		return -EINVAL;

	pci = hose_se1000[id].driver_data;

	ret = dw_plat_pcie_init(pci);
	if (ret) {
		printf("Failed to initialize dw plat pcie\n");
		return ret;
	}

	if(pci->mode ==  DW_PCIE_RC_TYPE){
		hose_se1000[id].ops = &pci_generic_ecam_ops;
		pci_probe_hose(&hose_se1000[id]);
	}
	hose_id = pci_register_hose(&hose_se1000[id]);

	return 0;
}


