/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Synopsys DesignWare PCIe host controller driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Jingoo Han <jg1.han@samsung.com>
 */

#ifndef _PCIE_DESIGNWARE_H
#define _PCIE_DESIGNWARE_H

#include <target/utils.h>
#include <target/list.h>
#include <target/heap.h>
#include <target/bitops.h>
#include <target/heap_generic.h>
#include <std/stdbool.h>
#include <std/string.h>
#include <std/endian.h>
#include <asm-generic/errno.h>
#include <stdio.h>
#include <target/bitops.h>
#include "../pci.h"



/* Parameters for the waiting for link up routine */
#define LINK_WAIT_MAX_RETRIES		10
#define LINK_WAIT_USLEEP_MIN		90000
#define LINK_WAIT_USLEEP_MAX		100000

/* Parameters for the waiting for iATU enabled routine */
#define LINK_WAIT_MAX_IATU_RETRIES	5
#define LINK_WAIT_IATU			9

#define GENMASK(h, l) \
	(((~0UL) - (1UL << (l)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

/* Synopsys-specific PCIe configuration registers */
#define PCIE_PORT_LINK_CONTROL		0x710
#define GEN3_RELATED_OFF               0x890
#define PIPE_LOOPBACK_CONTROL_OFF      0x8b8
#define PORT_LINK_MODE_MASK		GENMASK(21, 16)
//#define PORT_LINK_MODE(n)		FIELD_PREP(PORT_LINK_MODE_MASK, n)
//#define PORT_LINK_MODE_1_LANES		PORT_LINK_MODE(0x1)
//#define PORT_LINK_MODE_2_LANES		PORT_LINK_MODE(0x3)
//#define PORT_LINK_MODE_4_LANES		PORT_LINK_MODE(0x7)
//#define PORT_LINK_MODE_8_LANES		PORT_LINK_MODE(0xf)

#define PCIE_PORT_DEBUG0		0x728
#define PORT_LOGIC_LTSSM_STATE_MASK	0x1f
#define PORT_LOGIC_LTSSM_STATE_L0	0x11

#define PCIE_LINK_WIDTH_SPEED_CONTROL	0x80C
#define PORT_LOGIC_SPEED_CHANGE		BIT(17)
#define PORT_LOGIC_LINK_WIDTH_MASK	GENMASK(12, 8)
#define PORT_LOGIC_LINK_WIDTH(n)	FIELD_PREP(PORT_LOGIC_LINK_WIDTH_MASK, n)
#define PORT_LOGIC_LINK_WIDTH_1_LANES	PORT_LOGIC_LINK_WIDTH(0x1)
#define PORT_LOGIC_LINK_WIDTH_2_LANES	PORT_LOGIC_LINK_WIDTH(0x2)
#define PORT_LOGIC_LINK_WIDTH_4_LANES	PORT_LOGIC_LINK_WIDTH(0x4)
#define PORT_LOGIC_LINK_WIDTH_8_LANES	PORT_LOGIC_LINK_WIDTH(0x8)

#define PCIE_MSI_ADDR_LO		0x820
#define PCIE_MSI_ADDR_HI		0x824
#define PCIE_MSI_INTR0_ENABLE		0x828
#define PCIE_MSI_INTR0_MASK		0x82C
#define PCIE_MSI_INTR0_STATUS		0x830

#define PCIE_ATU_VIEWPORT		0x900
#define PCIE_ATU_REGION_INBOUND		BIT(31)
#define PCIE_ATU_REGION_OUTBOUND	0
#define PCIE_ATU_REGION_INDEX2		0x2
#define PCIE_ATU_REGION_INDEX1		0x1
#define PCIE_ATU_REGION_INDEX0		0x0
#define PCIE_ATU_CR1			0x904
#define PCIE_ATU_TYPE_MEM		0x0
#define PCIE_ATU_TYPE_IO		0x2
#define PCIE_ATU_TYPE_CFG0		0x4
#define PCIE_ATU_TYPE_CFG1		0x5
#define PCIE_ATU_CR2			0x908
#define PCIE_ATU_ENABLE			BIT(31)
#define PCIE_ATU_BAR_MODE_ENABLE	BIT(30)
#define PCIE_ATU_LOWER_BASE		0x90C
#define PCIE_ATU_UPPER_BASE		0x910
#define PCIE_ATU_LIMIT			0x914
#define PCIE_ATU_LOWER_TARGET		0x918
#define PCIE_ATU_UPPER_TARGET		0x91C

#define PCIE_MISC_CONTROL_1_OFF		0x8BC
#define PCIE_DBI_RO_WR_EN		BIT(0)

/*
 * iATU Unroll-specific register definitions
 * From 4.80 core version the address translation will be made by unroll
 */
#define PCIE_ATU_UNR_REGION_CTRL1	0x00
#define PCIE_ATU_UNR_REGION_CTRL2	0x04
#define PCIE_ATU_UNR_LOWER_BASE		0x08
#define PCIE_ATU_UNR_UPPER_BASE		0x0C
#define PCIE_ATU_UNR_LIMIT		0x10
#define PCIE_ATU_UNR_LOWER_TARGET	0x14
#define PCIE_ATU_UNR_UPPER_TARGET	0x18

/*
 * The default address offset between dbi_base and atu_base. Root controller
 * drivers are not required to initialize atu_base if the offset matches this
 * default; the driver core automatically derives atu_base from dbi_base using
 * this offset, if atu_base not set.
 */
#define DEFAULT_DBI_ATU_OFFSET (0x3 << 20)

/* Register address builder */
#define PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(region) \
		((region) << 9)

#define PCIE_GET_ATU_INB_UNR_REG_OFFSET(region) \
		(((region) << 9) | BIT(8))

#define MAX_MSI_IRQS			256
#define MAX_MSI_IRQS_PER_CTRL		32
#define MAX_MSI_CTRLS			(MAX_MSI_IRQS / MAX_MSI_IRQS_PER_CTRL)
#define MSI_REG_CTRL_BLOCK_SIZE		12
#define MSI_DEF_NUM_VECTORS		32

/* Maximum number of inbound/outbound iATUs */
#define MAX_IATU_IN			256
#define MAX_IATU_OUT			256

#define SE1000_PCIE_LANE_NUMBERS 4
#define IS_ALIGNED(x, a)		(((x) & ((typeof(x))(a) - 1)) == 0)
/* Error values that may be returned by PCI functions */
#define PCIBIOS_SUCCESSFUL		0x00
#define PCIBIOS_FUNC_NOT_SUPPORTED	0x81
#define PCIBIOS_BAD_VENDOR_ID		0x83
#define PCIBIOS_DEVICE_NOT_FOUND	0x86
#define PCIBIOS_BAD_REGISTER_NUMBER	0x87
#define PCIBIOS_SET_FAILED		0x88
#define PCIBIOS_BUFFER_TOO_SMALL	0x89
/*
 * The PCI interface treats multi-function devices as independent
 * devices.  The slot/function address of each device is encoded
 * in a single byte as follows:
 *
 *	7:3 = slot
 *	2:0 = function
 */
#define PCI_SLOT(devfn)		(((devfn) >> 3) & 0x1f)

/**
 * enum irqreturn
 * @IRQ_NONE		interrupt was not from this device or was not handled
 * @IRQ_HANDLED		interrupt was handled by this device
 * @IRQ_WAKE_THREAD	handler requests to wake the handler thread
 */
enum irqreturn {
	IRQ_NONE		= (0 << 0),
	IRQ_HANDLED		= (1 << 0),
	IRQ_WAKE_THREAD		= (1 << 1),
};

typedef enum irqreturn irqreturn_t;
#define IRQ_RETVAL(x)	((x) ? IRQ_HANDLED : IRQ_NONE)

#define PCI_CLASS_DEVICE	0x0a	/* Device class */
#define PCI_CLASS_BRIDGE_PCI		0x0604

#define	ENOMEM		12	/* Out of memory */
#define resource_size_t u64
#define IORESOURCE_TYPE_BITS	0x00001f00	/* Resource type */
#define IORESOURCE_IO		0x00000100	/* PCI/ISA I/O ports */
#define IORESOURCE_MEM		0x00000200
#define IORESOURCE_REG		0x00000300	/* Register offsets */
#define IORESOURCE_IRQ		0x00000400
#define IORESOURCE_DMA		0x00000800
#define IORESOURCE_BUS		0x00001000

/* PCIe EP */
#define EP_CONF_SIZE 0
#define EP_IB_WIN_NUM 6
#define EP_OUT_WIN_NUM 2

/* page size is 4K */
#define PAGES_DW EP_CONF_SIZE >> 12
#define BITMAP_SIZE_LONG_DW BITS_TO_LONGS(PAGES_DW)

enum pci_barno {
	BAR_0,
	BAR_1,
	BAR_2,
	BAR_3,
	BAR_4,
	BAR_5,
};

enum pci_epc_irq_type {
	PCI_EPC_IRQ_UNKNOWN,
	PCI_EPC_IRQ_LEGACY,
	PCI_EPC_IRQ_MSI,
	PCI_EPC_IRQ_MSIX,
};

/**
 * enum pci_interrupt_pin - PCI INTx interrupt values
 * @PCI_INTERRUPT_UNKNOWN: Unknown or unassigned interrupt
 * @PCI_INTERRUPT_INTA: PCI INTA pin
 * @PCI_INTERRUPT_INTB: PCI INTB pin
 * @PCI_INTERRUPT_INTC: PCI INTC pin
 * @PCI_INTERRUPT_INTD: PCI INTD pin
 *
 * Corresponds to values for legacy PCI INTx interrupts, as can be found in the
 * PCI_INTERRUPT_PIN register.
 */
enum pci_interrupt_pin {
	PCI_INTERRUPT_UNKNOWN,
	PCI_INTERRUPT_INTA,
	PCI_INTERRUPT_INTB,
	PCI_INTERRUPT_INTC,
	PCI_INTERRUPT_INTD,
};

/**
 * struct pci_epc - represents the PCI EPC device
 * @dev: PCI EPC device
 * @pci_epf: list of endpoint functions present in this EPC device
 * @ops: function pointers for performing endpoint operations
 * @mem: address space of the endpoint controller
 * @max_functions: max number of functions that can be configured in this EPC
 * @group: configfs group representing the PCI EPC device
 * @lock: spinlock to protect pci_epc ops
 */
struct pci_epc {
	struct list_head		pci_epf;
	const struct pci_epc_ops	*ops;
	struct pci_epc_mem		*mem;
	u8				max_functions;
	struct config_group		*group;
	void                            *driver_data;
};

/**
 * struct pci_epf_bar - represents the BAR of EPF device
 * @phys_addr: physical address that should be mapped to the BAR
 * @size: the size of the address space present in BAR
 */
struct pci_epf_bar {
	dma_addr_t	phys_addr;
	size_t		size;
	enum pci_barno	barno;
	int		flags;
};


/**
 * struct pci_epf_header - represents standard configuration header
 * @vendorid: identifies device manufacturer
 * @deviceid: identifies a particular device
 * @revid: specifies a device-specific revision identifier
 * @progif_code: identifies a specific register-level programming interface
 * @subclass_code: identifies more specifically the function of the device
 * @baseclass_code: broadly classifies the type of function the device performs
 * @cache_line_size: specifies the system cacheline size in units of DWORDs
 * @subsys_vendor_id: vendor of the add-in card or subsystem
 * @subsys_id: id specific to vendor
 * @interrupt_pin: interrupt pin the device (or device function) uses
 */
struct pci_epf_header {
	u16	vendorid;
	u16	deviceid;
	u8	revid;
	u8	progif_code;
	u8	subclass_code;
	u8	baseclass_code;
	u8	cache_line_size;
	u16	subsys_vendor_id;
	u16	subsys_id;
	enum pci_interrupt_pin interrupt_pin;
};

/**
 * struct pci_epc_ops - set of function pointers for performing EPC operations
 * @write_header: ops to populate configuration space header
 * @set_bar: ops to configure the BAR
 * @clear_bar: ops to reset the BAR
 * @map_addr: ops to map CPU address to PCI address
 * @unmap_addr: ops to unmap CPU address and PCI address
 * @set_msi: ops to set the requested number of MSI interrupts in the MSI
 *	     capability register
 * @get_msi: ops to get the number of MSI interrupts allocated by the RC from
 *	     the MSI capability register
 * @set_msix: ops to set the requested number of MSI-X interrupts in the
 *	     MSI-X capability register
 * @get_msix: ops to get the number of MSI-X interrupts allocated by the RC
 *	     from the MSI-X capability register
 * @raise_irq: ops to raise a legacy, MSI or MSI-X interrupt
 * @start: ops to start the PCI link
 * @stop: ops to stop the PCI link
 * @owner: the module owner containing the ops
 */
struct pci_epc_ops {
	int	(*write_header)(struct pci_epc *epc, u8 func_no,
				struct pci_epf_header *hdr);
	int	(*set_bar)(struct pci_epc *epc, u8 func_no,
			   struct pci_epf_bar *epf_bar);
	void	(*clear_bar)(struct pci_epc *epc, u8 func_no,
			     struct pci_epf_bar *epf_bar);
	int	(*map_addr)(struct pci_epc *epc, u8 func_no,
			    phys_addr_t addr, u64 pci_addr, size_t size);
	void	(*unmap_addr)(struct pci_epc *epc, u8 func_no,
			      phys_addr_t addr);
	int	(*set_msi)(struct pci_epc *epc, u8 func_no, u8 interrupts);
	int	(*get_msi)(struct pci_epc *epc, u8 func_no);
	int	(*set_msix)(struct pci_epc *epc, u8 func_no, u16 interrupts);
	int	(*get_msix)(struct pci_epc *epc, u8 func_no);
	int	(*raise_irq)(struct pci_epc *epc, u8 func_no,
			     enum pci_epc_irq_type type, u16 interrupt_num);
	int	(*start)(struct pci_epc *epc);
	void	(*stop)(struct pci_epc *epc);
	const struct pci_epc_features* (*get_features)(struct pci_epc *epc,
						       u8 func_no);
	struct module *owner;
};

/**
 * struct pci_epc_mem - address space of the endpoint controller
 * @phys_base: physical base address of the PCI address space
 * @size: the size of the PCI address space
 * @bitmap: bitmap to manage the PCI address space
 * @pages: number of bits representing the address region
 * @page_size: size of each page
 */
struct pci_epc_mem {
	phys_addr_t	phys_base;
	size_t		size;
	unsigned long	*bitmap;
	size_t		page_size;
	int		pages;
};

/**
 * struct pci_epc_features - features supported by a EPC device per function
 * @linkup_notifier: indicate if the EPC device can notify EPF driver on link up
 * @msi_capable: indicate if the endpoint function has MSI capability
 * @msix_capable: indicate if the endpoint function has MSI-X capability
 * @reserved_bar: bitmap to indicate reserved BAR unavailable to function driver
 * @bar_fixed_64bit: bitmap to indicate fixed 64bit BARs
 * @bar_fixed_size: Array specifying the size supported by each BAR
 */
struct pci_epc_features {
	unsigned int	linkup_notifier : 1;
	unsigned int	msi_capable : 1;
	unsigned int	msix_capable : 1;
	u8	reserved_bar;
	u8	bar_fixed_64bit;
	u64	bar_fixed_size[BAR_5 + 1];
};

/*
 * Resources are tree-like, allowing
 * nesting etc..
 */
struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	unsigned long flags;
	unsigned long desc;
	struct resource *parent, *sibling, *child;
};


/*
 * Common resource list management data structure and interfaces to support
 * ACPI, PNP and PCI host bridge etc.
 */
struct resource_entry {
	struct list_head	node;
	struct resource		res;	/* In master (CPU) address space */
	u64		offset;	/* Translation offset for bridge */
	struct resource		__res;	/* Default storage for res */
};

typedef u64 resource_size_t;

struct pcie_port;
struct dw_pcie_ep;

enum dw_pcie_region_type {
	DW_PCIE_REGION_UNKNOWN,
	DW_PCIE_REGION_INBOUND,
	DW_PCIE_REGION_OUTBOUND,
};

enum dw_pcie_device_mode {
	DW_PCIE_UNKNOWN_TYPE,
	DW_PCIE_EP_TYPE,
	DW_PCIE_LEG_EP_TYPE,
	DW_PCIE_RC_TYPE,
};
struct dw_plat_pcie {
	struct dw_pcie			*pci;
	struct regmap			*regmap;
	enum dw_pcie_device_mode	mode;
};

struct pci_host_bridge {
	struct pci_bus	*bus;		/* Root bus */
	struct pci_ops	*ops;
	void		*sysdata;
	int		busnr;
	struct list_head windows;	/* resource_entry */
//	u8 (*swizzle_irq)(struct pci_dev *, u8 *); /* Platform IRQ swizzler */
//	int (*map_irq)(const struct pci_dev *, u8, u8);
//	void (*release_fn)(struct pci_host_bridge *);
	void		*release_data;
	struct msi_controller *msi;
	unsigned int	ignore_reset_delay:1;	/* For entire hierarchy */
	unsigned int	no_ext_tags:1;		/* No Extended Tags */
	unsigned int	native_aer:1;		/* OS may use PCIe AER */
	unsigned int	native_pcie_hotplug:1;	/* OS may use PCIe hotplug */
	unsigned int	native_shpc_hotplug:1;	/* OS may use SHPC hotplug */
	unsigned int	native_pme:1;		/* OS may use PCIe PME */
	unsigned int	native_ltr:1;		/* OS may use PCIe LTR */
	unsigned long	private[0];
};

struct dw_pcie_host_ops {
	int (*rd_own_conf)(struct pcie_port *pp, int where, int size, u32 *val);
	int (*wr_own_conf)(struct pcie_port *pp, int where, int size, u32 val);
	int (*rd_other_conf)(struct pcie_port *pp, struct pci_bus *bus,
			     unsigned int devfn, int where, int size, u32 *val);
	int (*wr_other_conf)(struct pcie_port *pp, struct pci_bus *bus,
			     unsigned int devfn, int where, int size, u32 val);
	int (*host_init)(struct pcie_port *pp);
	void (*msi_set_irq)(struct pcie_port *pp, int irq);
	void (*msi_clear_irq)(struct pcie_port *pp, int irq);
	phys_addr_t (*get_msi_addr)(struct pcie_port *pp);
	u32 (*get_msi_data)(struct pcie_port *pp, int pos);
	void (*scan_bus)(struct pcie_port *pp);
	void (*set_num_vectors)(struct pcie_port *pp);
	int (*msi_host_init)(struct pcie_port *pp);
	void (*msi_irq_ack)(int irq, struct pcie_port *pp);
};

struct pcie_port {
	u8			root_bus_nr;
	u64			cfg0_base;
	void __iomem		*va_cfg0_base;
	u32			cfg0_size;
	u64			cfg1_base;
	void __iomem		*va_cfg1_base;
	u32			cfg1_size;
	resource_size_t		io_base;
	phys_addr_t		io_bus_addr;
	u32			io_size;
	u64			mem_base;
	phys_addr_t		mem_bus_addr;
	u32			mem_size;
	struct resource		*busn;
	struct resource		*cfg;
	struct resource		*io;
	struct resource		*mem;
	int			irq;
	const struct dw_pcie_host_ops *ops;
	int			msi_irq;
	struct irq_domain	*irq_domain;
	struct irq_domain	*msi_domain;
	dma_addr_t		msi_data;
	u32			num_vectors;
	u32			irq_mask[MAX_MSI_CTRLS];
	void		*private_data;
};

enum dw_pcie_as_type {
	DW_PCIE_AS_UNKNOWN,
	DW_PCIE_AS_MEM,
	DW_PCIE_AS_IO,
};

struct dw_pcie_ep_ops {
	void	(*ep_init)(struct dw_pcie_ep *ep);
	int	(*raise_irq)(struct dw_pcie_ep *ep, u8 func_no,
			     enum pci_epc_irq_type type, u16 interrupt_num);
	const struct pci_epc_features* (*get_features)(struct dw_pcie_ep *ep);
};

struct dw_pcie_ep {
	struct pci_epc		*epc;
	struct dw_pcie_ep_ops	*ops;
	phys_addr_t		phys_base;
	size_t			addr_size;
	size_t			page_size;
	u8			bar_to_atu[6];
	phys_addr_t		*outbound_addr;
	unsigned long		*ib_window_map;
	unsigned long		*ob_window_map;
	u32			num_ib_windows;
	u32			num_ob_windows;
	void __iomem		*msi_mem;
	phys_addr_t		msi_mem_phys;
	u8			msi_cap;	/* MSI capability offset */
	u8			msix_cap;	/* MSI-X capability offset */
	u8			max_fun;
};

struct dw_pcie_ops {
	u64	(*cpu_addr_fixup)(struct dw_pcie *pcie, u64 cpu_addr);
	u32	(*read_dbi)(struct dw_pcie *pcie, void __iomem *base, u32 reg,
			    size_t size);
	void	(*write_dbi)(struct dw_pcie *pcie, void __iomem *base, u32 reg,
			     size_t size, u32 val);
	int	(*link_up)(struct dw_pcie *pcie);
	int	(*start_link)(struct dw_pcie *pcie);
	void	(*stop_link)(struct dw_pcie *pcie);
};

struct dw_pcie {
	struct device		*dev;
	void __iomem		*dbi_base;
	void __iomem		*dbi_base2;
	/* Used when iatu_unroll_enabled is true */
	void __iomem		*atu_base;
	u32			num_viewport;
	u8			iatu_unroll_enabled;
	struct pcie_port	pp;
	struct dw_pcie_ep	ep;
	const struct dw_pcie_ops *ops;
	enum dw_pcie_device_mode	mode;
	void		*private_data;

};

#define to_dw_pcie_from_pp(port) container_of((port), struct dw_pcie, pp)

#define to_dw_pcie_from_ep(endpoint)   \
		container_of((endpoint), struct dw_pcie, ep)

int dw_pcie_read(void __iomem *addr, int size, u32 *val);
int dw_pcie_write(void __iomem *addr, int size, u32 val);

u32 __dw_pcie_read_dbi(struct dw_pcie *pci, void __iomem *base, u32 reg,
		       size_t size);
void __dw_pcie_write_dbi(struct dw_pcie *pci, void __iomem *base, u32 reg,
			 size_t size, u32 val);
int dw_pcie_link_up(struct dw_pcie *pci);
int dw_pcie_wait_for_link(struct dw_pcie *pci);
void dw_pcie_prog_outbound_atu(struct dw_pcie *pci, int index,
			       int type, u64 cpu_addr, u64 pci_addr,
			       u32 size);
int dw_pcie_prog_inbound_atu(struct dw_pcie *pci, int index, int bar,
			     u64 cpu_addr, enum dw_pcie_as_type as_type);
void dw_pcie_disable_atu(struct dw_pcie *pci, int index,
			 enum dw_pcie_region_type type);
void dw_pcie_setup(struct dw_pcie *pci);

static inline void dw_pcie_writel_dbi(struct dw_pcie *pci, u32 reg, u32 val)
{
	__dw_pcie_write_dbi(pci, pci->dbi_base, reg, 0x4, val);
}

static inline u32 dw_pcie_readl_dbi(struct dw_pcie *pci, u32 reg)
{
	return __dw_pcie_read_dbi(pci, pci->dbi_base, reg, 0x4);
}

static inline void dw_pcie_writew_dbi(struct dw_pcie *pci, u32 reg, u16 val)
{
	__dw_pcie_write_dbi(pci, pci->dbi_base, reg, 0x2, val);
}

static inline u16 dw_pcie_readw_dbi(struct dw_pcie *pci, u32 reg)
{
	return __dw_pcie_read_dbi(pci, pci->dbi_base, reg, 0x2);
}

static inline void dw_pcie_writeb_dbi(struct dw_pcie *pci, u32 reg, u8 val)
{
	__dw_pcie_write_dbi(pci, pci->dbi_base, reg, 0x1, val);
}

static inline u8 dw_pcie_readb_dbi(struct dw_pcie *pci, u32 reg)
{
	return __dw_pcie_read_dbi(pci, pci->dbi_base, reg, 0x1);
}

static inline void dw_pcie_writel_dbi2(struct dw_pcie *pci, u32 reg, u32 val)
{
	__dw_pcie_write_dbi(pci, pci->dbi_base2, reg, 0x4, val);
}

static inline u32 dw_pcie_readl_dbi2(struct dw_pcie *pci, u32 reg)
{
	return __dw_pcie_read_dbi(pci, pci->dbi_base2, reg, 0x4);
}

static inline void dw_pcie_writel_atu(struct dw_pcie *pci, u32 reg, u32 val)
{
	__dw_pcie_write_dbi(pci, pci->atu_base, reg, 0x4, val);
}

static inline u32 dw_pcie_readl_atu(struct dw_pcie *pci, u32 reg)
{
	return __dw_pcie_read_dbi(pci, pci->atu_base, reg, 0x4);
}

static inline void dw_pcie_dbi_ro_wr_en(struct dw_pcie *pci)
{
	u32 reg;
	u32 val;

	reg = PCIE_MISC_CONTROL_1_OFF;
	val = dw_pcie_readl_dbi(pci, reg);
	val |= PCIE_DBI_RO_WR_EN;
	dw_pcie_writel_dbi(pci, reg, val);
}

static inline void dw_pcie_dbi_ro_wr_dis(struct dw_pcie *pci)
{
	u32 reg;
	u32 val;

	reg = PCIE_MISC_CONTROL_1_OFF;
	val = dw_pcie_readl_dbi(pci, reg);
	val &= ~PCIE_DBI_RO_WR_EN;
	dw_pcie_writel_dbi(pci, reg, val);
}
extern struct pci_controller hose_se1000[4];
extern struct resource_entry win;
extern int dw_pcie_rd_config(struct pci_controller *hose, int bdf, unsigned int where,
                           u32 *val,  enum pci_size_t pci_size);
extern int dw_pcie_wr_config(struct pci_controller *hose, int bdf,
                           unsigned int where, u32 val, enum pci_size_t pci_size);

#ifdef CONFIG_PCIE_DW
irqreturn_t dw_handle_msi_irq(struct pcie_port *pp);
void dw_pcie_msi_init(struct pcie_port *pp);
void dw_pcie_free_msi(struct pcie_port *pp);
void dw_pcie_setup_rc(struct pcie_port *pp);
int dw_pcie_host_init(struct pcie_port *pp);
int dw_pcie_allocate_domains(struct pcie_port *pp);
void dw_enter_loopback_mode(struct dw_pcie *pci);
void dw_exit_loopback_mode(struct dw_pcie *pci);
int dw_plat_pcie_init(struct dw_pcie *pci);
#else
static inline irqreturn_t dw_handle_msi_irq(struct pcie_port *pp)
{
	return IRQ_NONE;
}

static inline void dw_pcie_msi_init(struct pcie_port *pp)
{
}

static inline void dw_pcie_free_msi(struct pcie_port *pp)
{
}

static inline void dw_pcie_setup_rc(struct pcie_port *pp)
{
}

static inline int dw_pcie_host_init(struct pcie_port *pp)
{
	return 0;
}

static inline int dw_pcie_allocate_domains(struct pcie_port *pp)
{
	return 0;
}
#endif

#ifdef CONFIG_PCIE_DW
void dw_pcie_ep_linkup(struct dw_pcie_ep *ep);
int dw_pcie_ep_init(struct dw_pcie_ep *ep);
void dw_pcie_ep_exit(struct dw_pcie_ep *ep);
int dw_pcie_ep_raise_legacy_irq(struct dw_pcie_ep *ep, u8 func_no);
int dw_pcie_ep_raise_msi_irq(struct dw_pcie_ep *ep, u8 func_no,
			     u8 interrupt_num);
int dw_pcie_ep_raise_msix_irq(struct dw_pcie_ep *ep, u8 func_no,
			     u16 interrupt_num);
void dw_pcie_ep_reset_bar(struct dw_pcie *pci, enum pci_barno bar);
#else
static inline void dw_pcie_ep_linkup(struct dw_pcie_ep *ep)
{
}

static inline int dw_pcie_ep_init(struct dw_pcie_ep *ep)
{
	return 0;
}

static inline void dw_pcie_ep_exit(struct dw_pcie_ep *ep)
{
}

static inline int dw_pcie_ep_raise_legacy_irq(struct dw_pcie_ep *ep, u8 func_no)
{
	return 0;
}

static inline int dw_pcie_ep_raise_msi_irq(struct dw_pcie_ep *ep, u8 func_no,
					   u8 interrupt_num)
{
	return 0;
}

static inline int dw_pcie_ep_raise_msix_irq(struct dw_pcie_ep *ep, u8 func_no,
					   u16 interrupt_num)
{
	return 0;
}

static inline void dw_pcie_ep_reset_bar(struct dw_pcie *pci, enum pci_barno bar)
{
}
#endif
#endif /* _PCIE_DESIGNWARE_H */
