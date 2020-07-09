// SPDX-License-Identifier: GPL-2.0
/**
 * Synopsys DesignWare PCIe Endpoint controller driver
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */
#include <asm/mach/memory.h>
#include "pcie-designware.h"

ulong ib_windows_map_array[BITS_TO_LONGS(EP_IB_WIN_NUM)];
ulong ob_windows_map_array[BITS_TO_LONGS(EP_OUT_WIN_NUM)];
phys_addr_t outbound_addr_array[EP_OUT_WIN_NUM];

struct pci_epc epc_dw;
struct pci_epc_mem mem_dw;
ulong bit_map_array[BITMAP_SIZE_LONG_DW];

/**
 * __pci_epc_mem_init() - initialize the pci_epc_mem structure
 * @epc: the EPC device that invoked pci_epc_mem_init
 * @phys_base: the physical address of the base
 * @size: the size of the address space
 * @page_size: size of each page
 *
 * Invoke to initialize the pci_epc_mem structure used by the
 * endpoint functions to allocate mapped PCI address.
 */
int __pci_epc_mem_init(struct pci_epc *epc, phys_addr_t phys_base, size_t size,
		       size_t page_size)
{
	int ret;
	struct pci_epc_mem *mem;
	unsigned long *bitmap;
	unsigned int page_shift;
	int pages;
	int bitmap_size;

	if (page_size < PAGE_SIZE)
		page_size = PAGE_SIZE;

	page_shift = ilog2(page_size);
	pages = size >> page_shift;
	bitmap_size = BITS_TO_LONGS(pages) * sizeof(long);

	mem = &mem_dw;
	if (!mem) {
		ret = -ENOMEM;
		goto err;
	}

	bitmap = bit_map_array;
	if (!bitmap) {
		ret = -ENOMEM;
		goto err;
	}

	mem->bitmap = bitmap;
	mem->phys_base = phys_base;
	mem->page_size = page_size;
	mem->pages = pages;
	mem->size = size;

	epc->mem = mem;

	return 0;

err:
	return ret;
}

void dw_pcie_ep_linkup(struct dw_pcie_ep *ep)
{
	struct pci_epc *epc = ep->epc;

//	pci_epc_linkup(epc);
}

static void __dw_pcie_ep_reset_bar(struct dw_pcie *pci, enum pci_barno bar,
				   int flags)
{
	u32 reg;

	reg = PCI_BASE_ADDRESS_0 + (4 * bar);
	dw_pcie_dbi_ro_wr_en(pci);
	dw_pcie_writel_dbi2(pci, reg, 0x0);
	dw_pcie_writel_dbi(pci, reg, 0x0);
	if (flags & PCI_BASE_ADDRESS_MEM_TYPE_64) {
		dw_pcie_writel_dbi2(pci, reg + 4, 0x0);
		dw_pcie_writel_dbi(pci, reg + 4, 0x0);
	}
	dw_pcie_dbi_ro_wr_dis(pci);
}

void dw_pcie_ep_reset_bar(struct dw_pcie *pci, enum pci_barno bar)
{
	__dw_pcie_ep_reset_bar(pci, bar, 0);
}

static u8 __dw_pcie_ep_find_next_cap(struct dw_pcie *pci, u8 cap_ptr,
			      u8 cap)
{
	u8 cap_id, next_cap_ptr;
	u16 reg;

	reg = dw_pcie_readw_dbi(pci, cap_ptr);
	next_cap_ptr = (reg & 0xff00) >> 8;
	cap_id = (reg & 0x00ff);

	if (!next_cap_ptr || cap_id > PCI_CAP_ID_MAX)
		return 0;

	if (cap_id == cap)
		return cap_ptr;

	return __dw_pcie_ep_find_next_cap(pci, next_cap_ptr, cap);
}

static u8 dw_pcie_ep_find_capability(struct dw_pcie *pci, u8 cap)
{
	u8 next_cap_ptr;
	u16 reg;

	reg = dw_pcie_readw_dbi(pci, PCI_CAPABILITY_LIST);
	next_cap_ptr = (reg & 0x00ff);

	if (!next_cap_ptr)
		return 0;

	return __dw_pcie_ep_find_next_cap(pci, next_cap_ptr, cap);
}

static int dw_pcie_ep_write_header(struct pci_epc *epc, u8 func_no,
				   struct pci_epf_header *hdr)
{
	struct dw_pcie *pci = epc->driver_data;

	dw_pcie_dbi_ro_wr_en(pci);
	dw_pcie_writew_dbi(pci, PCI_VENDOR_ID, hdr->vendorid);
	dw_pcie_writew_dbi(pci, PCI_DEVICE_ID, hdr->deviceid);
	dw_pcie_writeb_dbi(pci, PCI_REVISION_ID, hdr->revid);
	dw_pcie_writeb_dbi(pci, PCI_CLASS_PROG, hdr->progif_code);
	dw_pcie_writew_dbi(pci, PCI_CLASS_DEVICE,
			   hdr->subclass_code | hdr->baseclass_code << 8);
	dw_pcie_writeb_dbi(pci, PCI_CACHE_LINE_SIZE,
			   hdr->cache_line_size);
	dw_pcie_writew_dbi(pci, PCI_SUBSYSTEM_VENDOR_ID,
			   hdr->subsys_vendor_id);
	dw_pcie_writew_dbi(pci, PCI_SUBSYSTEM_ID, hdr->subsys_id);
	dw_pcie_writeb_dbi(pci, PCI_INTERRUPT_PIN,
			   hdr->interrupt_pin);
	dw_pcie_dbi_ro_wr_dis(pci);

	return 0;
}

static int dw_pcie_ep_inbound_atu(struct dw_pcie_ep *ep, enum pci_barno bar,
				  dma_addr_t cpu_addr,
				  enum dw_pcie_as_type as_type)
{
	int ret;
	u32 free_win;
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);

	free_win = find_first_zero_bit(ep->ib_window_map, ep->num_ib_windows);
	if (free_win >= ep->num_ib_windows) {
		printf("No free inbound window\n");
		return -EINVAL;
	}

	ret = dw_pcie_prog_inbound_atu(pci, free_win, bar, cpu_addr,
				       as_type);
	if (ret < 0) {
		printf("Failed to program IB window\n");
		return ret;
	}

	ep->bar_to_atu[bar] = free_win;
	set_bit(free_win, ep->ib_window_map);

	return 0;
}

static int dw_pcie_ep_outbound_atu(struct dw_pcie_ep *ep, phys_addr_t phys_addr,
				   u64 pci_addr, size_t size)
{
	u32 free_win;
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);

	free_win = find_first_zero_bit(ep->ob_window_map, ep->num_ob_windows);
	if (free_win >= ep->num_ob_windows) {
		printf("No free outbound window\n");
		return -EINVAL;
	}

	dw_pcie_prog_outbound_atu(pci, free_win, PCIE_ATU_TYPE_MEM,
				  phys_addr, pci_addr, size);

	set_bit(free_win, ep->ob_window_map);
	ep->outbound_addr[free_win] = phys_addr;

	return 0;
}

static void dw_pcie_ep_clear_bar(struct pci_epc *epc, u8 func_no,
				 struct pci_epf_bar *epf_bar)
{
	struct dw_pcie *pci = epc->driver_data;
	struct dw_pcie_ep *ep = &pci->ep;
	enum pci_barno bar = epf_bar->barno;
	u32 atu_index = ep->bar_to_atu[bar];

	__dw_pcie_ep_reset_bar(pci, bar, epf_bar->flags);

	dw_pcie_disable_atu(pci, atu_index, DW_PCIE_REGION_INBOUND);
	clear_bit(atu_index, ep->ib_window_map);
}

static int dw_pcie_ep_set_bar(struct pci_epc *epc, u8 func_no,
			      struct pci_epf_bar *epf_bar)
{
	int ret;
	struct dw_pcie *pci = epc->driver_data;
	struct dw_pcie_ep *ep = &pci->ep;
	enum pci_barno bar = epf_bar->barno;
	size_t size = epf_bar->size;
	int flags = epf_bar->flags;
	enum dw_pcie_as_type as_type;
	u32 reg = PCI_BASE_ADDRESS_0 + (4 * bar);

	if (!(flags & PCI_BASE_ADDRESS_SPACE))
		as_type = DW_PCIE_AS_MEM;
	else
		as_type = DW_PCIE_AS_IO;

	ret = dw_pcie_ep_inbound_atu(ep, bar, epf_bar->phys_addr, as_type);
	if (ret)
		return ret;

	dw_pcie_dbi_ro_wr_en(pci);

	dw_pcie_writel_dbi2(pci, reg, lower_32_bits(size - 1));
	dw_pcie_writel_dbi(pci, reg, flags);

	if (flags & PCI_BASE_ADDRESS_MEM_TYPE_64) {
		dw_pcie_writel_dbi2(pci, reg + 4, upper_32_bits(size - 1));
		dw_pcie_writel_dbi(pci, reg + 4, 0);
	}

	dw_pcie_dbi_ro_wr_dis(pci);

	return 0;
}

static int dw_pcie_find_index(struct dw_pcie_ep *ep, phys_addr_t addr,
			      u32 *atu_index)
{
	u32 index;

	for (index = 0; index < ep->num_ob_windows; index++) {
		if (ep->outbound_addr[index] != addr)
			continue;
		*atu_index = index;
		return 0;
	}

	return -EINVAL;
}

static void dw_pcie_ep_unmap_addr(struct pci_epc *epc, u8 func_no,
				  phys_addr_t addr)
{
	int ret;
	u32 atu_index;
	struct dw_pcie *pci = epc->driver_data;
	struct dw_pcie_ep *ep = &pci->ep;

	ret = dw_pcie_find_index(ep, addr, &atu_index);
	if (ret < 0)
		return;

	dw_pcie_disable_atu(pci, atu_index, DW_PCIE_REGION_OUTBOUND);
	clear_bit(atu_index, ep->ob_window_map);
}

static int dw_pcie_ep_map_addr(struct pci_epc *epc, u8 func_no,
			       phys_addr_t addr,
			       u64 pci_addr, size_t size)
{
	int ret;
	struct dw_pcie *pci = epc->driver_data;
	struct dw_pcie_ep *ep = &pci->ep;

	ret = dw_pcie_ep_outbound_atu(ep, addr, pci_addr, size);
	if (ret) {
		printf("Failed to enable address\n");
		return ret;
	}

	return 0;
}

#if 0
static int dw_pcie_ep_get_msi(struct pci_epc *epc, u8 func_no)
{
	struct dw_pcie *pci = &dw_pci;
	struct dw_pcie_ep *ep = &pci->ep;;
	u32 val, reg;

	if (!ep->msi_cap)
		return -EINVAL;

	reg = ep->msi_cap + PCI_MSI_FLAGS;
	val = dw_pcie_readw_dbi(pci, reg);
	if (!(val & PCI_MSI_FLAGS_ENABLE))
		return -EINVAL;

	val = (val & PCI_MSI_FLAGS_QSIZE) >> 4;

	return val;
}

static int dw_pcie_ep_set_msi(struct pci_epc *epc, u8 func_no, u8 interrupts)
{
	struct dw_pcie *pci = &dw_pci;
	struct dw_pcie_ep *ep = &pci->ep;;
	u32 val, reg;

	if (!ep->msi_cap)
		return -EINVAL;

	reg = ep->msi_cap + PCI_MSI_FLAGS;
	val = dw_pcie_readw_dbi(pci, reg);
	val &= ~PCI_MSI_FLAGS_QMASK;
	val |= (interrupts << 1) & PCI_MSI_FLAGS_QMASK;
	dw_pcie_dbi_ro_wr_en(pci);
	dw_pcie_writew_dbi(pci, reg, val);
	dw_pcie_dbi_ro_wr_dis(pci);

	return 0;
}

static int dw_pcie_ep_get_msix(struct pci_epc *epc, u8 func_no)
{
	struct dw_pcie *pci = &dw_pci;
	struct dw_pcie_ep *ep = &pci->ep;;
	u32 val, reg;

	if (!ep->msix_cap)
		return -EINVAL;

	reg = ep->msix_cap + PCI_MSIX_FLAGS;
	val = dw_pcie_readw_dbi(pci, reg);
	if (!(val & PCI_MSIX_FLAGS_ENABLE))
		return -EINVAL;

	val &= PCI_MSIX_FLAGS_QSIZE;

	return val;
}

static int dw_pcie_ep_set_msix(struct pci_epc *epc, u8 func_no, u16 interrupts)
{
	struct dw_pcie *pci = &dw_pci;
	struct dw_pcie_ep *ep = &pci->ep;;
	u32 val, reg;

	if (!ep->msix_cap)
		return -EINVAL;

	reg = ep->msix_cap + PCI_MSIX_FLAGS;
	val = dw_pcie_readw_dbi(pci, reg);
	val &= ~PCI_MSIX_FLAGS_QSIZE;
	val |= interrupts;
	dw_pcie_dbi_ro_wr_en(pci);
	dw_pcie_writew_dbi(pci, reg, val);
	dw_pcie_dbi_ro_wr_dis(pci);

	return 0;
}

static int dw_pcie_ep_raise_irq(struct pci_epc *epc, u8 func_no,
				enum pci_epc_irq_type type, u16 interrupt_num)
{
	struct dw_pcie_ep *ep = epc_get_drvdata(epc);

	if (!ep->ops->raise_irq)
		return -EINVAL;

	return ep->ops->raise_irq(ep, func_no, type, interrupt_num);
}
#endif

static void dw_pcie_ep_stop(struct pci_epc *epc)
{
	struct dw_pcie *pci = epc->driver_data;
	struct dw_pcie_ep *ep = &pci->ep;

	if (!pci->ops->stop_link)
		return;

	pci->ops->stop_link(pci);
}

static int dw_pcie_ep_start(struct pci_epc *epc)
{
	struct dw_pcie *pci = epc->driver_data;
	struct dw_pcie_ep *ep = &pci->ep;

	if (!pci->ops->start_link)
		return -EINVAL;

	return pci->ops->start_link(pci);
}

static const struct pci_epc_features*
dw_pcie_ep_get_features(struct pci_epc *epc, u8 func_no)
{
	struct dw_pcie *pci = epc->driver_data;
	struct dw_pcie_ep *ep = &pci->ep;

	if (!ep->ops->get_features)
		return NULL;

	return ep->ops->get_features(ep);
}

static const struct pci_epc_ops epc_ops = {
	.write_header		= dw_pcie_ep_write_header,
	.set_bar		= dw_pcie_ep_set_bar,
	.clear_bar		= dw_pcie_ep_clear_bar,
	.map_addr		= dw_pcie_ep_map_addr,
	.unmap_addr		= dw_pcie_ep_unmap_addr,
//	.set_msi		= dw_pcie_ep_set_msi,
//	.get_msi		= dw_pcie_ep_get_msi,
//	.set_msix		= dw_pcie_ep_set_msix,
//	.get_msix		= dw_pcie_ep_get_msix,
//	.raise_irq		= dw_pcie_ep_raise_irq,
	.start			= dw_pcie_ep_start,
	.stop			= dw_pcie_ep_stop,
	.get_features		= dw_pcie_ep_get_features,
};

#if 0
int dw_pcie_ep_raise_legacy_irq(struct dw_pcie_ep *ep, u8 func_no)
{
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	struct device *dev = pci->dev;

	dev_err(dev, "EP cannot trigger legacy IRQs\n");

	return -EINVAL;
}

int dw_pcie_ep_raise_msi_irq(struct dw_pcie_ep *ep, u8 func_no,
			     u8 interrupt_num)
{
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	struct pci_epc *epc = ep->epc;
	u16 msg_ctrl, msg_data;
	u32 msg_addr_lower, msg_addr_upper, reg;
	u64 msg_addr;
	bool has_upper;
	int ret;

	if (!ep->msi_cap)
		return -EINVAL;

	/* Raise MSI per the PCI Local Bus Specification Revision 3.0, 6.8.1. */
	reg = ep->msi_cap + PCI_MSI_FLAGS;
	msg_ctrl = dw_pcie_readw_dbi(pci, reg);
	has_upper = !!(msg_ctrl & PCI_MSI_FLAGS_64BIT);
	reg = ep->msi_cap + PCI_MSI_ADDRESS_LO;
	msg_addr_lower = dw_pcie_readl_dbi(pci, reg);
	if (has_upper) {
		reg = ep->msi_cap + PCI_MSI_ADDRESS_HI;
		msg_addr_upper = dw_pcie_readl_dbi(pci, reg);
		reg = ep->msi_cap + PCI_MSI_DATA_64;
		msg_data = dw_pcie_readw_dbi(pci, reg);
	} else {
		msg_addr_upper = 0;
		reg = ep->msi_cap + PCI_MSI_DATA_32;
		msg_data = dw_pcie_readw_dbi(pci, reg);
	}
	msg_addr = ((u64) msg_addr_upper) << 32 | msg_addr_lower;
	ret = dw_pcie_ep_map_addr(epc, func_no, ep->msi_mem_phys, msg_addr,
				  epc->mem->page_size);
	if (ret)
		return ret;

	writel(msg_data | (interrupt_num - 1), ep->msi_mem);

	dw_pcie_ep_unmap_addr(epc, func_no, ep->msi_mem_phys);

	return 0;
}

int dw_pcie_ep_raise_msix_irq(struct dw_pcie_ep *ep, u8 func_no,
			     u16 interrupt_num)
{
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);
	struct pci_epc *epc = ep->epc;
	u16 tbl_offset, bir;
	u32 bar_addr_upper, bar_addr_lower;
	u32 msg_addr_upper, msg_addr_lower;
	u32 reg, msg_data, vec_ctrl;
	u64 tbl_addr, msg_addr, reg_u64;
	void __iomem *msix_tbl;
	int ret;

	reg = ep->msix_cap + PCI_MSIX_TABLE;
	tbl_offset = dw_pcie_readl_dbi(pci, reg);
	bir = (tbl_offset & PCI_MSIX_TABLE_BIR);
	tbl_offset &= PCI_MSIX_TABLE_OFFSET;

	reg = PCI_BASE_ADDRESS_0 + (4 * bir);
	bar_addr_upper = 0;
	bar_addr_lower = dw_pcie_readl_dbi(pci, reg);
	reg_u64 = (bar_addr_lower & PCI_BASE_ADDRESS_MEM_TYPE_MASK);
	if (reg_u64 == PCI_BASE_ADDRESS_MEM_TYPE_64)
		bar_addr_upper = dw_pcie_readl_dbi(pci, reg + 4);

	tbl_addr = ((u64) bar_addr_upper) << 32 | bar_addr_lower;
	tbl_addr += (tbl_offset + ((interrupt_num - 1) * PCI_MSIX_ENTRY_SIZE));
	tbl_addr &= PCI_BASE_ADDRESS_MEM_MASK;

	msix_tbl = ioremap_nocache(ep->phys_base + tbl_addr,
				   PCI_MSIX_ENTRY_SIZE);
	if (!msix_tbl)
		return -EINVAL;

	msg_addr_lower = readl(msix_tbl + PCI_MSIX_ENTRY_LOWER_ADDR);
	msg_addr_upper = readl(msix_tbl + PCI_MSIX_ENTRY_UPPER_ADDR);
	msg_addr = ((u64) msg_addr_upper) << 32 | msg_addr_lower;
	msg_data = readl(msix_tbl + PCI_MSIX_ENTRY_DATA);
	vec_ctrl = readl(msix_tbl + PCI_MSIX_ENTRY_VECTOR_CTRL);

	iounmap(msix_tbl);

	if (vec_ctrl & PCI_MSIX_ENTRY_CTRL_MASKBIT) {
		dev_dbg(pci->dev, "MSI-X entry ctrl set\n");
		return -EPERM;
	}

	ret = dw_pcie_ep_map_addr(epc, func_no, ep->msi_mem_phys, msg_addr,
				  epc->mem->page_size);
	if (ret)
		return ret;

	writel(msg_data, ep->msi_mem);

	dw_pcie_ep_unmap_addr(epc, func_no, ep->msi_mem_phys);

	return 0;
}
#endif

void dw_pcie_ep_exit(struct dw_pcie_ep *ep)
{
	struct pci_epc *epc = ep->epc;
}

int dw_pcie_ep_init(struct dw_pcie_ep *ep)
{
	int ret;
	void *addr;
	struct pci_epc *epc;
	struct dw_pcie *pci = to_dw_pcie_from_ep(ep);

	if (!pci->dbi_base || !pci->dbi_base2) {
		printf("dbi_base/dbi_base2 is not populated\n");
		return -EINVAL;
	}
	if (pci->iatu_unroll_enabled && !pci->atu_base) {
		printf("atu_base is not populated\n");
		return -EINVAL;
	}

	ep->ib_window_map = ib_windows_map_array;
	ep->ob_window_map = ob_windows_map_array;
	ep->outbound_addr = outbound_addr_array;

	epc = &epc_dw;
	epc->ops = &epc_ops;
	ep->epc = epc;

	if (ep->ops->ep_init)
		ep->ops->ep_init(ep);

	epc->max_functions = ep->max_fun;;

	ret = __pci_epc_mem_init(epc, ep->phys_base, ep->addr_size,
				 ep->page_size);
	if (ret < 0) {
		printf("Failed to initialize address space\n");
		return ret;
	}
#if 0
	ep->msi_mem = pci_epc_mem_alloc_addr(epc, &ep->msi_mem_phys,
					     epc->mem->page_size);
	if (!ep->msi_mem) {
		dev_err(dev, "Failed to reserve memory for MSI/MSI-X\n");
		return -ENOMEM;
	}
	ep->msi_cap = dw_pcie_ep_find_capability(pci, PCI_CAP_ID_MSI);

	ep->msix_cap = dw_pcie_ep_find_capability(pci, PCI_CAP_ID_MSIX);
#endif
	dw_pcie_setup(pci);

	return 0;
}
