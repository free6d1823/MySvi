#ifndef DRIVERS_PCI_H
#define DRIVERS_PCI_H
#include <target/list.h>
#include <target/pci.h>

#ifdef DEBUG
#define debug(fmt, args...)		\
	do {						\
		printf(fmt, ##args);	\
	} while (0)
#else
#define debug(fmt, args...)
#endif

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef int pci_dev_t;

struct pci_controller;

#define PCI_BRIDGE_RESOURCE_NUM 4

#define PCI_REGION_MEM		0x00000000	/* PCI memory space */
#define PCI_REGION_IO		0x00000001	/* PCI IO space */
#define PCI_REGION_TYPE		0x00000001
#define PCI_REGION_PREFETCH	0x00000008	/* prefetchable PCI memory */

#define PCI_REGION_SYS_MEMORY	0x00000100	/* System memory */
#define PCI_REGION_RO		0x00000200	/* Read-only memory */

/* The pci_dev structure describes PCI devices */
struct pci_dev {
	struct list_head bus_list;	/* Node in per-bus list */
	struct pci_bus	*bus;		/* Bus this device is on */
	struct pci_bus	*subordinate;	/* Bus this device bridges to */

	unsigned int	devfn;		/* Encoded device & function index */
	unsigned short	vendor;
	unsigned short	device;
	unsigned short	subsystem_vendor;
	unsigned short	subsystem_device;
	unsigned int	class_code;		/* 3 bytes: (base,sub,prog-if) */
};

struct pci_bus {
	struct list_head node;		/* Node in list of buses */
	struct pci_bus	*parent;	/* Parent bus this bridge is on */
	struct list_head children;	/* List of child buses */
	struct list_head devices;	/* List of devices on this bus */
	struct pci_dev	*self;		/* Bridge device as seen by parent */

	//struct resource *resource[PCI_BRIDGE_RESOURCE_NUM];
	//struct list_head resources;	/* Address space routed to this bus */
	//struct resource busn_res;	/* Bus numbers routed to this bus */

	struct pci_controller *hose;

	struct pci_ops	*ops;		/* Configuration access functions */

	unsigned char	number;		/* Bus number */
	unsigned char	primary;	/* Number of primary bridge */
	void		*sysdata;	/* Hook for sys-specific extension */


	char		name[48];
};

/* PCI bus operations */
struct pci_ops {
	/**
	 * read_config() - Read a PCI configuration value
	 *
	 * PCI buses must support reading and writing configuration values
	 * so that the bus can be scanned and its devices configured.
	 *
	 * Normally PCI_BUS(@bdf) is the same as @bus->seq, but not always.
	 * If bridges exist it is possible to use the top-level bus to
	 * access a sub-bus. In that case @bus will be the top-level bus
	 * and PCI_BUS(bdf) will be a different (higher) value
	 *
	 * @bus:	Bus to read from
	 * @bdf:	Bus, device and function to read
	 * @offset:	Byte offset within the device's configuration space
	 * @valuep:	Place to put the returned value
	 * @size:	Access size
	 * @return 0 if OK, -ve on error
	 */
	int (*read_config)(struct pci_controller *bus, pci_dev_t bdf, unsigned int offset,
			   unsigned int *valuep, enum pci_size_t size);
	/**
	 * write_config() - Write a PCI configuration value
	 *
	 * @bus:	Bus to write to
	 * @bdf:	Bus, device and function to write
	 * @offset:	Byte offset within the device's configuration space
	 * @value:	Value to write
	 * @size:	Access size
	 * @return 0 if OK, -ve on error
	 */
	int (*write_config)(struct pci_controller *bus, pci_dev_t bdf, unsigned int offset,
			    unsigned int value, enum pci_size_t size);
};

int pci_generic_mmap_read_config(struct pci_controller *hose, pci_dev_t bdf,
	unsigned int offset, unsigned int *valuep, enum pci_size_t size);

int pci_generic_mmap_write_config(struct pci_controller *hose, pci_dev_t bdf,
	unsigned int offset, unsigned int value, enum pci_size_t size);

struct pci_config_table {
	unsigned int vendor, device;		/* Vendor and device ID or PCI_ANY_ID */
	unsigned int class;			/* Class ID, or  PCI_ANY_ID */
	unsigned int bus;			/* Bus number, or PCI_ANY_ID */
	unsigned int dev;			/* Device number, or PCI_ANY_ID */
	unsigned int func;			/* Function number, or PCI_ANY_ID */

	void (*config_device)(struct pci_controller* hose, pci_dev_t dev,
			      struct pci_config_table *);
	unsigned long priv[3];
};

struct pci_controller *pci_get_hose(int id);
int pci_probe_hose(struct pci_controller *hose);
struct pci_dev *pci_get_dev(int hose, int bus, int dev, int func);

int pci_write_config(struct pci_dev *dev, int offset, unsigned int value,
	enum pci_size_t size);
int pci_read_config(struct pci_dev *dev, int offset, unsigned int *valuep,
	enum pci_size_t size);

int pci_find_cap_start(struct pci_dev *dev);
int pci_find_cap(struct pci_dev *dev, int pos, int cap);
int pci_find_capability(struct pci_dev *dev, int cap);

void pciauto_region_init(struct pci_region *res);
void pciauto_region_align(struct pci_region *res, pci_size_t size);
void pciauto_config_init(struct pci_controller *hose);
int pciauto_config_device(struct pci_dev *dev);
void pciauto_prescan_setup_bridge(struct pci_dev *dev, int sub_bus);
void pciauto_postscan_setup_bridge(struct pci_dev *dev, int sub_bus);
int pciauto_region_allocate(struct pci_region *res, pci_size_t size,
	pci_addr_t *bar, bool supports_64bit);
int pci_probe_bridge(struct pci_dev *bridge);

void pci_walk_bus(struct pci_bus *top, int (*cb)(struct pci_dev *, void *),
	void *userdata);
struct pci_bus *pci_search_bus(struct pci_bus *top, int bus);
#endif
