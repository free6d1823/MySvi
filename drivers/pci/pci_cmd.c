#include <string.h>
#include <stdlib.h>
#include <asm/io.h>
#include <target/console.h>
#include <target/bitops.h>
#include <target/cmdline.h>
#include <errno.h>
#include <target/pci.h>
#include "pci.h"

struct pci_reg_info {
	const char *name;
	enum pci_size_t size;
	u8 offset;
};

static int pci_byte_size(enum pci_size_t size)
{
	switch (size) {
	case PCI_SIZE_8:
		return 1;
	case PCI_SIZE_16:
		return 2;
	case PCI_SIZE_32:
	default:
		return 4;
	}
}

static struct pci_reg_info regs_start[] = {
	{ "vendor ID", PCI_SIZE_16, PCI_VENDOR_ID },
	{ "device ID", PCI_SIZE_16, PCI_DEVICE_ID },
	{ "command register ID", PCI_SIZE_16, PCI_COMMAND },
	{ "status register", PCI_SIZE_16, PCI_STATUS },
	{ "revision ID", PCI_SIZE_8, PCI_REVISION_ID },
	{},
};

static struct pci_reg_info regs_rest[] = {
	{ "sub class code", PCI_SIZE_8, PCI_CLASS_SUB_CODE },
	{ "programming interface", PCI_SIZE_8, PCI_CLASS_PROG },
	{ "cache line", PCI_SIZE_8, PCI_CACHE_LINE_SIZE },
	{ "latency time", PCI_SIZE_8, PCI_LATENCY_TIMER },
	{ "header type", PCI_SIZE_8, PCI_HEADER_TYPE },
	{ "BIST", PCI_SIZE_8, PCI_BIST },
	{ "base address 0", PCI_SIZE_32, PCI_BASE_ADDRESS_0 },
	{},
};

static struct pci_reg_info regs_normal[] = {
	{ "base address 1", PCI_SIZE_32, PCI_BASE_ADDRESS_1 },
	{ "base address 2", PCI_SIZE_32, PCI_BASE_ADDRESS_2 },
	{ "base address 3", PCI_SIZE_32, PCI_BASE_ADDRESS_3 },
	{ "base address 4", PCI_SIZE_32, PCI_BASE_ADDRESS_4 },
	{ "base address 5", PCI_SIZE_32, PCI_BASE_ADDRESS_5 },
	{ "cardBus CIS pointer", PCI_SIZE_32, PCI_CARDBUS_CIS },
	{ "sub system vendor ID", PCI_SIZE_16, PCI_SUBSYSTEM_VENDOR_ID },
	{ "sub system ID", PCI_SIZE_16, PCI_SUBSYSTEM_ID },
	{ "expansion ROM base address", PCI_SIZE_32, PCI_ROM_ADDRESS },
	{ "interrupt line", PCI_SIZE_8, PCI_INTERRUPT_LINE },
	{ "interrupt pin", PCI_SIZE_8, PCI_INTERRUPT_PIN },
	{ "min Grant", PCI_SIZE_8, PCI_MIN_GNT },
	{ "max Latency", PCI_SIZE_8, PCI_MAX_LAT },
	{},
};

static struct pci_reg_info regs_bridge[] = {
	{ "base address 1", PCI_SIZE_32, PCI_BASE_ADDRESS_1 },
	{ "primary bus number", PCI_SIZE_8, PCI_PRIMARY_BUS },
	{ "secondary bus number", PCI_SIZE_8, PCI_SECONDARY_BUS },
	{ "subordinate bus number", PCI_SIZE_8, PCI_SUBORDINATE_BUS },
	{ "secondary latency timer", PCI_SIZE_8, PCI_SEC_LATENCY_TIMER },
	{ "IO base", PCI_SIZE_8, PCI_IO_BASE },
	{ "IO limit", PCI_SIZE_8, PCI_IO_LIMIT },
	{ "secondary status", PCI_SIZE_16, PCI_SEC_STATUS },
	{ "memory base", PCI_SIZE_16, PCI_MEMORY_BASE },
	{ "memory limit", PCI_SIZE_16, PCI_MEMORY_LIMIT },
	{ "prefetch memory base", PCI_SIZE_16, PCI_PREF_MEMORY_BASE },
	{ "prefetch memory limit", PCI_SIZE_16, PCI_PREF_MEMORY_LIMIT },
	{ "prefetch memory base upper", PCI_SIZE_32, PCI_PREF_BASE_UPPER32 },
	{ "prefetch memory limit upper", PCI_SIZE_32, PCI_PREF_LIMIT_UPPER32 },
	{ "IO base upper 16 bits", PCI_SIZE_16, PCI_IO_BASE_UPPER16 },
	{ "IO limit upper 16 bits", PCI_SIZE_16, PCI_IO_LIMIT_UPPER16 },
	{ "expansion ROM base address", PCI_SIZE_32, PCI_ROM_ADDRESS1 },
	{ "interrupt line", PCI_SIZE_8, PCI_INTERRUPT_LINE },
	{ "interrupt pin", PCI_SIZE_8, PCI_INTERRUPT_PIN },
	{ "bridge control", PCI_SIZE_16, PCI_BRIDGE_CONTROL },
	{},
};

static struct pci_reg_info regs_cardbus[] = {
	{ "capabilities", PCI_SIZE_8, PCI_CB_CAPABILITY_LIST },
	{ "secondary status", PCI_SIZE_16, PCI_CB_SEC_STATUS },
	{ "primary bus number", PCI_SIZE_8, PCI_CB_PRIMARY_BUS },
	{ "CardBus number", PCI_SIZE_8, PCI_CB_CARD_BUS },
	{ "subordinate bus number", PCI_SIZE_8, PCI_CB_SUBORDINATE_BUS },
	{ "CardBus latency timer", PCI_SIZE_8, PCI_CB_LATENCY_TIMER },
	{ "CardBus memory base 0", PCI_SIZE_32, PCI_CB_MEMORY_BASE_0 },
	{ "CardBus memory limit 0", PCI_SIZE_32, PCI_CB_MEMORY_LIMIT_0 },
	{ "CardBus memory base 1", PCI_SIZE_32, PCI_CB_MEMORY_BASE_1 },
	{ "CardBus memory limit 1", PCI_SIZE_32, PCI_CB_MEMORY_LIMIT_1 },
	{ "CardBus IO base 0", PCI_SIZE_16, PCI_CB_IO_BASE_0 },
	{ "CardBus IO base high 0", PCI_SIZE_16, PCI_CB_IO_BASE_0_HI },
	{ "CardBus IO limit 0", PCI_SIZE_16, PCI_CB_IO_LIMIT_0 },
	{ "CardBus IO limit high 0", PCI_SIZE_16, PCI_CB_IO_LIMIT_0_HI },
	{ "CardBus IO base 1", PCI_SIZE_16, PCI_CB_IO_BASE_1 },
	{ "CardBus IO base high 1", PCI_SIZE_16, PCI_CB_IO_BASE_1_HI },
	{ "CardBus IO limit 1", PCI_SIZE_16, PCI_CB_IO_LIMIT_1 },
	{ "CardBus IO limit high 1", PCI_SIZE_16, PCI_CB_IO_LIMIT_1_HI },
	{ "interrupt line", PCI_SIZE_8, PCI_INTERRUPT_LINE },
	{ "interrupt pin", PCI_SIZE_8, PCI_INTERRUPT_PIN },
	{ "bridge control", PCI_SIZE_16, PCI_CB_BRIDGE_CONTROL },
	{ "subvendor ID", PCI_SIZE_16, PCI_CB_SUBSYSTEM_VENDOR_ID },
	{ "subdevice ID", PCI_SIZE_16, PCI_CB_SUBSYSTEM_ID },
	{ "PC Card 16bit base address", PCI_SIZE_32, PCI_CB_LEGACY_MODE_BASE },
	{},
};

static int pci_field_width(enum pci_size_t size)
{
	return pci_byte_size(size) * 2;
}

static void pci_show_regs(struct pci_dev *dev, struct pci_reg_info *regs)
{
	unsigned int value;

	for (; regs->name; regs++) {
		pci_read_config(dev, regs->offset, &value, regs->size);
		printf("  %s =%*s%#.*lx\n", regs->name,
		       (int)(28 - strlen(regs->name)), "",
		       pci_field_width(regs->size),
		       value);
	}
}

const char* pci_class_str(uint32_t class)
{
	switch (class) {
	case PCI_CLASS_NOT_DEFINED:
		return "Build before PCI Rev2.0";
		break;
	case PCI_BASE_CLASS_STORAGE:
		return "Mass storage controller";
		break;
	case PCI_BASE_CLASS_NETWORK:
		return "Network controller";
		break;
	case PCI_BASE_CLASS_DISPLAY:
		return "Display controller";
		break;
	case PCI_BASE_CLASS_MULTIMEDIA:
		return "Multimedia device";
		break;
	case PCI_BASE_CLASS_MEMORY:
		return "Memory controller";
		break;
	case PCI_BASE_CLASS_BRIDGE:
		return "Bridge device";
		break;
	case PCI_BASE_CLASS_COMMUNICATION:
		return "Simple comm. controller";
		break;
	case PCI_BASE_CLASS_SYSTEM:
		return "Base system peripheral";
		break;
	case PCI_BASE_CLASS_INPUT:
		return "Input device";
		break;
	case PCI_BASE_CLASS_DOCKING:
		return "Docking station";
		break;
	case PCI_BASE_CLASS_PROCESSOR:
		return "Processor";
		break;
	case PCI_BASE_CLASS_SERIAL:
		return "Serial bus controller";
		break;
	case PCI_BASE_CLASS_INTELLIGENT:
		return "Intelligent controller";
		break;
	case PCI_BASE_CLASS_SATELLITE:
		return "Satellite controller";
		break;
	case PCI_BASE_CLASS_CRYPT:
		return "Cryptographic device";
		break;
	case PCI_BASE_CLASS_SIGNAL_PROCESSING:
		return "DSP";
		break;
	case PCI_CLASS_OTHERS:
		return "Does not fit any class";
		break;
	default:
		return "???";
		break;
	};
}

void pci_header_show(int hose, int b, int d, int f)
{
	struct pci_dev *dev;
	unsigned int class, header_type;

	dev = pci_get_dev(hose, b, d, f);
	if (!dev)
		printf("pci_dev(%d,%d,%d,%d) not found\n", hose, b, d, f);

	pci_read_config(dev, PCI_CLASS_CODE, &class, PCI_SIZE_8);
	pci_read_config(dev, PCI_HEADER_TYPE, &header_type, PCI_SIZE_8);

	pci_show_regs(dev, regs_start);
	printf("  class code =                  0x%.2x (%s)\n", (int)class,
	       pci_class_str(class));
	pci_show_regs(dev, regs_rest);

	switch (header_type & 0x03) {
	case PCI_HEADER_TYPE_NORMAL:	/* "normal" PCI device */
		pci_show_regs(dev, regs_normal);
		break;
	case PCI_HEADER_TYPE_BRIDGE:	/* PCI-to-PCI bridge */
		pci_show_regs(dev, regs_bridge);
		break;
	case PCI_HEADER_TYPE_CARDBUS:	/* PCI-to-CardBus bridge */
		pci_show_regs(dev, regs_cardbus);
		break;

	default:
		printf("unknown header\n");
		break;
    }
}

void pciinfo_header(int busnum, bool short_listing)
{
	printf("Scanning PCI devices on bus %d\n", busnum);

	if (short_listing) {
		printf("BusDevFun  VendorId   DeviceId   Device Class       Sub-Class    ClassCode\n");
		printf("__________________________________________________________________________\n");
	}
}

static void pci_header_show_brief(struct pci_dev *dev)
{
	unsigned int vendor, device;
	unsigned int class, subclass, interface, classcode=0;

	pci_read_config(dev, PCI_VENDOR_ID, &vendor, PCI_SIZE_16);
	pci_read_config(dev, PCI_DEVICE_ID, &device, PCI_SIZE_16);
	pci_read_config(dev, PCI_CLASS_CODE, &class, PCI_SIZE_8);
	pci_read_config(dev, PCI_CLASS_SUB_CODE, &subclass, PCI_SIZE_8);
	pci_read_config(dev, PCI_CLASS_PROG, &interface, PCI_SIZE_8);
	classcode = ((((class & 0xff) << 8) | subclass) << 8) | interface;

	printf("0x%.4lx     0x%.4lx     %-23s 0x%.2lx     0x%.6lx\n",
	       vendor, device,
	       pci_class_str(class), subclass, classcode);
}

static int dump_pci_dev(struct pci_dev *dev, void *arg)
{
	printf("%02x.%02x.%02x   ", dev->bus->number,
			       PCI_DEV(dev->devfn), PCI_FUNC(dev->devfn));
	pci_header_show_brief(dev);

	return 0;
}

int pci_bar_show(int hose, int b, int d, int f)
{
	u32 header_type;
	int bar_cnt, bar_id, mem_type;
	bool is_64, is_io;
	u32 base_low, base_high;
	u32 size_low, size_high;
	u64 base, size;
	u32 reg_addr;
	int prefetchable;

	struct pci_dev *dev;

	dev = pci_get_dev(hose, b, d, f);
		if (!dev)
			printf("pci_dev(%d,%d,%d,%d) not found\n", hose, b, d, f);

	pci_read_config(dev, PCI_HEADER_TYPE, &header_type, PCI_SIZE_8);

	if (header_type == PCI_HEADER_TYPE_CARDBUS) {
		printf("CardBus doesn't support BARs\n");
		return -ENOSYS;
	}

	bar_cnt = (header_type == PCI_HEADER_TYPE_NORMAL) ? 6 : 2;

	printf("ID   Base                Size                Width  Type\n");
	printf("----------------------------------------------------------\n");

	bar_id = 0;
	reg_addr = PCI_BASE_ADDRESS_0;
	while (bar_cnt) {
		pci_read_config(dev, reg_addr, &base_low, PCI_SIZE_32);
		pci_write_config(dev, reg_addr, 0xffffffff, PCI_SIZE_32);
		pci_read_config(dev, reg_addr, &size_low, PCI_SIZE_32);
		pci_write_config(dev, reg_addr, base_low, PCI_SIZE_32);
		reg_addr += 4;

		base = base_low & ~0xf;
		size = size_low & ~0xf;
		base_high = 0x0;
		size_high = 0xffffffff;
		is_64 = 0;
		prefetchable = base_low & PCI_BASE_ADDRESS_MEM_PREFETCH;
		is_io = base_low & PCI_BASE_ADDRESS_SPACE_IO;
		mem_type = base_low & PCI_BASE_ADDRESS_MEM_TYPE_MASK;

		if (mem_type == PCI_BASE_ADDRESS_MEM_TYPE_64) {
			pci_read_config(dev, reg_addr, &base_high, PCI_SIZE_32);
			pci_write_config(dev, reg_addr, 0xffffffff, PCI_SIZE_32);
			pci_read_config(dev, reg_addr, &size_high, PCI_SIZE_32);
			pci_write_config(dev, reg_addr, base_high, PCI_SIZE_32);
			bar_cnt--;
			reg_addr += 4;
			is_64 = 1;
		}

		base = base | ((u64)base_high << 32);
		size = size | ((u64)size_high << 32);

		if ((!is_64 && size_low) || (is_64 && size)) {
			size = ~size + 1;
			printf(" %d   %#016llx  %#016llx  %d     %s   %s\n",
			       bar_id, (unsigned long long)base,
			       (unsigned long long)size, is_64 ? 64 : 32,
			       is_io ? "I/O" : "MEM",
			       prefetchable ? "Prefetchable" : "");
		}

		bar_id++;
		bar_cnt--;
	}

	return 0;
}

static void pciinfo(int hoseid)
{
	struct pci_controller *hose = pci_get_hose(hoseid);
	struct pci_bus *bus = hose->bus;

	pciinfo_header(bus->number, true);
	pci_walk_bus(bus, dump_pci_dev, NULL);
}

static int hexdump_pci_dev(struct pci_dev *dev, void *arg)
{
	int i, end = 0x40, pos;
	unsigned int d;

	printf("%02x:%02x.%d xxx", dev->bus->number,
			PCI_DEV(dev->devfn), PCI_FUNC(dev->devfn));

	pos = pci_find_cap_start(dev);
	if (pos > 0) {
		end = 0x100; /* Support Capability List */
		pci_find_cap(dev, pos, PCI_CAP_ID_PCIX);
		if (pci_find_cap(dev, pos, PCI_CAP_ID_EXP) > 0 ||
				pci_find_cap(dev, pos, PCI_CAP_ID_PCIX) > 0)
			end = 0x1000; /* Support Extended Capability List */
	}

	for (i = 0; i < end; i += 4) {
		if ((i & 0xf) == 0)
			printf("\n%02x:", i);
		pci_read_config(dev, i, &d, PCI_SIZE_32);

		#define BTYE_N(n) (((uint8_t *)&d)[n])
		printf(" %02x %02x %02x %02x", BTYE_N(0), BTYE_N(1), BTYE_N(2), BTYE_N(3));
	}
	printf("\n");

	return 0;
}

static void pcidump(int hoseid)
{
	struct pci_controller *hose = pci_get_hose(hoseid);
	struct pci_bus *bus = hose->bus;

	pci_walk_bus(bus, hexdump_pci_dev, NULL);
}

static int _atoi(char *v)
{
    int n = 0;
    while (*v != 0) {
        n = n*10 + (*v - '0');
        v++;
    }
    return n;
}

int cmd_pci(int argc, char **argv)
{
	int hose, bus, dev, func;

	if (argc < 2)
		return -EUSAGE;

	if (!strcmp("init", argv[1])) {
		pci_init();
		return 0;
	}

	if (argc == 3 && !strcmp("info", argv[1])) {
		pciinfo(strtoul(argv[2], 0, 0));
		return 0;
	}

	if (argc == 3 && !strcmp("dump", argv[1])) {
		pcidump(strtoul(argv[2], 0, 0));
		return 0;
	}

	if (argc >= 6) {
		hose = strtoul(argv[2], 0, 0);
		bus = strtoul(argv[3], 0, 0);
		dev = strtoul(argv[4], 0, 0);
		func = strtoul(argv[5], 0, 0);

		if (!strcmp("head", argv[1]))
			pci_header_show(hose, bus, dev, func);
		else if (!strcmp("bar", argv[1]))
			pci_bar_show(hose, bus, dev, func);
		else
			return -1;

		return 0;
	}

	return -EUSAGE;
}

MK_CMD(pci, cmd_pci, "PCI cmd with host and bdf",
	"    arguments: h(host) b(bus) d(device) f(function)\n"
	"    e.g. pci info 0\n"
	"    e.g. pci head 0 0 1 0\n"
	"pci init\n"
	"    -Enumerate buses, run the cmd first and only once\n"
	"pci info h\n"
	"    -List the devices on host\n"
	"pci head h b d f\n"
	"    -List the config space\n"
	"pci bar h b d f\n"
	"    -List the BAR\n"
	"pci dump h\n"
	"    -Dump the config space for lspci\n"
);

