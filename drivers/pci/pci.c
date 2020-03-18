#define DEBUG

#include <string.h>
#include <target/console.h>
#include <target/bitops.h>
#include <errno.h>
#include "pci.h"

#define MAX_PCI_HOSE 4
#define MAX_PCI_DEV 16
#define MAX_PCI_BUS 8


struct pci_dev_pool {
	int flag;
	struct pci_dev dev;
};

struct pci_bus_pool {
	int flag;
	struct pci_bus bus;
};

static struct pci_dev_pool dev_pool[MAX_PCI_DEV];
static struct pci_bus_pool bus_pool[MAX_PCI_BUS];
static struct pci_controller *hose_pool[MAX_PCI_HOSE];

static int pci_get_ff(enum pci_size_t size)
{
	switch (size) {
	case PCI_SIZE_8:
		return 0xff;
	case PCI_SIZE_16:
		return 0xffff;
	default:
		return 0xffffffff;
	}
}

static struct pci_dev *alloc_pci_dev()
{
	int i;
	struct pci_dev *dev;

	for (i = 0; i < MAX_PCI_DEV; i++) {
		if (dev_pool[i].flag == 0)
			break;
	}
	if (i < MAX_PCI_DEV)
		dev = &dev_pool[i].dev;
	else
		return NULL;

	dev_pool[i].flag = 1;
	INIT_LIST_HEAD(&dev->bus_list);

	return dev;
}

static struct pci_bus *alloc_pci_bus()
{
	int i;
	struct pci_bus *b;

	for (i = 0; i < MAX_PCI_BUS; i++) {
		if (bus_pool[i].flag == 0)
			break;
	}
	if ( i < MAX_PCI_DEV)
		b = &bus_pool[i].bus;
	else
		return NULL;

	bus_pool[i].flag = 1;

	INIT_LIST_HEAD(&b->node);
	INIT_LIST_HEAD(&b->children);
	INIT_LIST_HEAD(&b->devices);

	return b;
}

static int pci_generic_ecam_conf_address(
	struct pci_controller *hose,
	pci_dev_t bdf,
	unsigned int offset,
	void **paddress)
{
	void *addr;

	addr = hose->cfg_base;
	addr += PCI_BUS(bdf) << 20;
	addr += PCI_DEV(bdf) << 15;
	addr += PCI_FUNC(bdf) << 12;
	addr += offset;
	*paddress = addr;

	return 0;
}

int pci_generic_mmap_write_config(
	struct pci_controller *hose,
	pci_dev_t bdf,
	unsigned int offset,
	unsigned int value,
	enum pci_size_t size)
{
	void *addr;
	pci_generic_ecam_conf_address(hose, bdf, offset, &addr);

	//debug("pci_generic_mmap_write_config: %d, 0x%llx, 0x%x\n", hose->bus->number, offset, value);
	switch (size) {
	case PCI_SIZE_8:
		__raw_writeb(value, addr);
		return 0;
	case PCI_SIZE_16:
		__raw_writew(value, addr);
		return 0;
	case PCI_SIZE_32:
		__raw_writel(value, addr);
		return 0;
	default:
		return -EINVAL;
	}
}

int pci_generic_mmap_read_config(
	struct pci_controller *hose,
	pci_dev_t bdf,
	unsigned int offset,
	unsigned int *valuep,
	enum pci_size_t size)
{
	void *addr;
	pci_generic_ecam_conf_address(hose, bdf, offset, &addr);

	switch (size) {
	case PCI_SIZE_8:
		*valuep = __raw_readb(addr);
		break;
	case PCI_SIZE_16:
		*valuep = __raw_readw(addr);
		break;
	case PCI_SIZE_32:
		*valuep = __raw_readl(addr);
		break;
	default:
		return -EINVAL;
	}

	//debug("pci_generic_mmap_read_config(%llx)=0x%x\n", addr, *valuep);
	return 0;
}


int pci_bus_read_config(struct pci_bus *bus, pci_dev_t bdf, int offset,
			unsigned int *valuep, enum pci_size_t size)
{
	BUG_ON(bus->ops == 0);
	return bus->ops->read_config(bus->hose, bdf, offset, valuep, size);
}

int pci_bus_write_config(struct pci_bus *bus, pci_dev_t bdf, int offset,
			 unsigned int value, enum pci_size_t size)
{
	BUG_ON(bus->ops == 0);
	return bus->ops->write_config(bus->hose, bdf, offset, value, size);
}

int pci_write_config(struct pci_dev *dev, int offset, unsigned int value,
			enum pci_size_t size)
{
	return pci_bus_write_config(dev->bus, PCI_ADD_BUS(dev->bus->number, dev->devfn),
			offset, value, size);
}

int pci_read_config(struct pci_dev *dev, int offset, unsigned int *valuep,
		   enum pci_size_t size)
{
	return pci_bus_read_config(dev->bus, PCI_ADD_BUS(dev->bus->number, dev->devfn),
			offset, valuep, size);
}

int pci_find_cap_start(struct pci_dev *dev)
{
	unsigned int status;
	unsigned int hdr_type;

	pci_read_config(dev, PCI_STATUS, &status, PCI_SIZE_16);

	if (!(status & PCI_STATUS_CAP_LIST))
		return 0;

	pci_read_config(dev, PCI_HEADER_TYPE, &hdr_type, PCI_SIZE_8);

	switch (hdr_type & 0x7F) {
	case PCI_HEADER_TYPE_NORMAL:
	case PCI_HEADER_TYPE_BRIDGE:
		return PCI_CAPABILITY_LIST;
	case PCI_HEADER_TYPE_CARDBUS:
		return PCI_CB_CAPABILITY_LIST;
	default:
		return 0;
	}
}

int pci_find_cap(struct pci_dev *dev, int pos, int cap)
{
	int ttl = PCI_FIND_CAP_TTL;
	unsigned int id;
	unsigned int next_pos;

	while (ttl--) {
		pci_read_config(dev, pos, &next_pos, PCI_SIZE_8);
		if (next_pos < CAP_START_POS)
			break;
		next_pos &= ~3;
		pos = (int) next_pos;
		pci_read_config(dev, pos + PCI_CAP_LIST_ID, &id, PCI_SIZE_8);
		if (id == 0xff)
			break;
		if (id == cap)
			return pos;
		pos += PCI_CAP_LIST_NEXT;
	}
	return 0;
}

int pci_find_capability(struct pci_dev *dev, int cap)
{
	int pos;

	pos = pci_find_cap_start(dev);

	if (pos > 0)
		return pci_find_cap(dev, pos, cap);

	return pos;
}

void pci_bus_add_device(struct pci_bus *bus, struct pci_dev *dev)
{
	list_add_tail(&dev->bus_list, &bus->devices);
}

int pci_auto_config_devices(struct pci_bus *bus)
{
	unsigned int sub_bus, max_bus;
	struct pci_dev *dev;
	int ret;

	sub_bus = bus->number;
	debug("%s: bus %d/%s start\n", __func__, bus->number, bus->name);
	pciauto_config_init(bus->hose);

	list_for_each_entry(struct pci_dev, dev,
		&bus->devices, bus_list) {
		ret = pciauto_config_device(dev);
		if (ret < 0)
			return ret;

		max_bus = ret;
		sub_bus = max(sub_bus, max_bus);
	}

	debug("%s: done\n", __func__);

	return sub_bus;
}

int pci_scan_bus_devices(struct pci_bus *bus)
{
	unsigned int vendor, device;
	unsigned int header_type;
	pci_dev_t bdf, end;
	struct pci_dev *dev;
	bool found_multi;
	int ret;

	found_multi = false;
	end = PCI_BDF(bus->number, PCI_MAX_PCI_DEVICES - 1,
			  PCI_MAX_PCI_FUNCTIONS - 1);

	for (bdf = PCI_BDF(bus->number, 0, 0); bdf <= end;
		bdf += PCI_BDF(0, 0, 1)) {
		unsigned int class;

		if (!PCI_FUNC(bdf))
			found_multi = false;
		if (PCI_FUNC(bdf) && !found_multi)
			continue;

		/* Check only the first access, we don't expect problems */
		ret = pci_bus_read_config(bus, bdf, PCI_VENDOR_ID, &vendor,
					  PCI_SIZE_16);
		if (ret)
			goto error;

		if (vendor == 0xffff || vendor == 0x0000)
			continue;

		pci_bus_read_config(bus, bdf, PCI_HEADER_TYPE,
					&header_type, PCI_SIZE_8);

		if (!PCI_FUNC(bdf))
			found_multi = header_type & 0x80;

		debug("%s: bus %d/%s: found device %x, function %d\n", __func__,
			  bus->number, bus->name, PCI_DEV(bdf), PCI_FUNC(bdf));

		pci_bus_read_config(bus, bdf, PCI_DEVICE_ID, &device,
					PCI_SIZE_16);
		pci_bus_read_config(bus, bdf, PCI_CLASS_REVISION, &class,
					PCI_SIZE_32);
		class >>= 8;

		dev = alloc_pci_dev(bus);
		dev->bus = bus;
		dev->subordinate = NULL;
		dev->devfn = PCI_DEVFN(PCI_DEV(bdf), PCI_FUNC(bdf));
		dev->vendor = vendor;
		dev->device = device;
		dev->class = class;

		if ((header_type & 0x7f) == PCI_HEADER_TYPE_NORMAL) {
			unsigned int val;
			pci_bus_read_config(bus, bdf,
						PCI_SUBSYSTEM_VENDOR_ID,
						&val, PCI_SIZE_32);
			dev->subsystem_vendor = val & 0xffff;
			dev->subsystem_device = val >> 16;
		}

		pci_bus_add_device(bus, dev);
	}

	return 0;

error:
	printf("Cannot read bus configuration: %d\n", ret);
	return ret;
}

static int pci_get_bus_max(struct pci_bus *top)
{
	struct pci_bus *bus;
	int bus_max = top->number, max;

	list_for_each_entry(struct pci_bus, bus,
		&top->children, node) {
		if (bus->number > bus_max)
			bus_max = bus->number;

		if (bus->children.next != &bus->children) {
			bus = list_entry(bus->children.next, struct pci_bus, node);
			max = pci_get_bus_max(bus);
			if (max > bus_max)
				bus_max = max;
		}
	}

	debug("%s: ret=%d\n", __func__, bus_max);

	return bus_max;
}

static struct pci_bus *pci_alloc_child_bus(struct pci_bus *parent,
					   struct pci_dev *bridge, int busnr)
{
	struct pci_bus *child = alloc_pci_bus();
	if (!child)
		return NULL;

	child->parent = parent;
	child->self = bridge;
	child->ops = parent->ops;
	child->primary = parent->number;
	child->number = busnr;

	list_add_tail(&child->node, &parent->children);

	return child;
}

int pci_probe_bridge(struct pci_dev *bridge)
{
	int sub_bus;
	struct pci_bus *bus;
	int ret;

	debug("%s\n", __func__);

	sub_bus = pci_get_bus_max(bridge->bus->hose->bus) + 1;
	bus = pci_alloc_child_bus(bridge->bus, bridge, sub_bus);
	bridge->subordinate = bus;

	debug("%s: bus = %d/%s\n", __func__, sub_bus, bus->name);

	pciauto_prescan_setup_bridge(bridge, sub_bus);

	pci_scan_bus_devices(bus);
	pci_auto_config_devices(bus);

	sub_bus = pci_get_bus_max(bus);
	pciauto_postscan_setup_bridge(bridge, sub_bus);

	return sub_bus;
}

/** pci_walk_bus - walk devices on/under bus, calling callback.
 *  @top      bus whose devices should be walked
 *  @cb       callback to be called for each device found
 *  @userdata arbitrary pointer to be passed to callback.
 *
 *  Walk the given bus, including any bridged devices
 *  on buses under this bus.  Call the provided callback
 *  on each device found.
 *
 *  We check the return of @cb each time. If it returns anything
 *  other than 0, we break out.
 *
 */
void pci_walk_bus(struct pci_bus *top, int (*cb)(struct pci_dev *, void *),
		  void *userdata)
{
	struct pci_dev *dev;
	struct pci_bus *bus;
	struct list_head *next;
	int retval;

	bus = top;
	next = top->devices.next;
	for (;;) {
		if (next == &bus->devices) {
			/* end of this bus, go up or finish */
			if (bus == top)
				break;
			next = bus->self->bus_list.next;
			bus = bus->self->bus;
			continue;
		}
		dev = list_entry(next, struct pci_dev, bus_list);
		if (dev->subordinate) {
			/* this is a pci-pci bridge, do its devices next */
			next = dev->subordinate->devices.next;
			bus = dev->subordinate;
		} else
			next = dev->bus_list.next;

		retval = cb(dev, userdata);
		if (retval)
			break;
	}
}

static struct pci_bus *pci_search_bus(struct pci_bus *top, int bus)
{
	struct pci_bus *b;

	if (top->number == bus)
		return top;

	if (top->children.next != &top->children) {
		list_for_each_entry(struct pci_bus, b,
			&top->children, node) {
			return pci_search_bus(b, bus);
		}
	}

	return NULL;
}

int pci_probe_hose(struct pci_controller *hose)
{
	struct pci_bus *bus = alloc_pci_bus();
	if (!bus)
		return -ENOMEM;

	hose->bus = bus;

	bus->parent = bus;
	bus->hose = hose;
	bus->ops = hose->ops;
	bus->number = 0;
	strcpy(bus->name, hose->name);

	pci_scan_bus_devices(bus);
	pci_auto_config_devices(bus);

	return 0;
}

int pci_register_hose(struct pci_controller *hose)
{
	int i;
	for (i = 0; i < MAX_PCI_HOSE; i++) {
		if (hose_pool[i] == 0)
			break;
	}

	if (i < MAX_PCI_HOSE) {
		hose_pool[i] = hose;
	}

	return i;
}

struct pci_controller* pci_get_hose(int id)
{
	if (id >= MAX_PCI_HOSE)
		return NULL;

	return hose_pool[id];
}

struct pci_bus* pci_get_bus(int hose, int bus)
{
	struct pci_controller *h;

	h = pci_get_hose(hose);
	if (!h)
		return NULL;

	return pci_search_bus(h->bus, bus);
}

struct pci_dev* pci_get_dev(int hose, int bus, int dev, int func)
{
	struct pci_controller *h;
	struct pci_bus *b;
	struct pci_dev *d;

	b = pci_get_bus(hose, bus);
	if (!b)
		return NULL;

	list_for_each_entry(struct pci_dev, d,
		&b->devices, bus_list) {
		if (d->devfn == PCI_DEVFN(dev, func))
			return d;
	}

	return NULL;
}

static pci_dev_t _match;
static int pci_match_class(struct pci_dev *dev, void *arg)
{
	unsigned int classcode = *(unsigned int *)arg;
	_match = -1;

	if (dev->class == classcode) {
		_match = (dev->bus->number) << 16 | dev->devfn;
		return 1;
	}

	return 0;
}

pci_dev_t pci_get_dev_by_class(int hose, unsigned int classcode)
{
	struct pci_bus *top;
	pci_dev_t bdf;

	top = pci_get_bus(hose, 0);
	if (!top)
		return -1;

	pci_walk_bus(top, pci_match_class, (void *)&classcode);
	if (_match != -1)
		return _match;

	return -1;
}

void *pci_map_bar(int hose, pci_dev_t bdf, int bar)
{
	pci_addr_t pci_bus_addr;
	u32 bar_response;
	struct pci_dev *dev;

	dev = pci_get_dev(hose, PCI_BUS(bdf), PCI_DEV(bdf), PCI_FUNC(bdf));
	if (!dev)
		return NULL;

	pci_read_config(dev, bar, &bar_response, PCI_SIZE_32);
	pci_bus_addr = (pci_addr_t)(bar_response & ~0xf);

	return (void*)pci_bus_addr;
}
