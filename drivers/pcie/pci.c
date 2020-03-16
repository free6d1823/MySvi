/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

#include <asm/io.h>
#include <target/pci.h>

struct pci_reg_info
{
	const char* name;
	enum pci_size_t size;
	uint8_t offset;
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

static int pci_field_width(enum pci_size_t size)
{
	return pci_byte_size(size) * 2;
}

static int pci_ecam_conf_address(uint64_t addr, int32_t bdf, uint32_t offset, uint64_t* paddress)
{
	addr += PCI_BUS(bdf) << 20;
	addr += PCI_DEV(bdf) << 15;
	addr += PCI_FUNC(bdf) << 12;
	addr += offset;
	*paddress = addr;

	return 0;
}

static int
pci_read_config(uint64_t addr, int32_t bdf, uint32_t offset, uint32_t* value, enum pci_size_t size)
{
	uint64_t address;

	pci_ecam_conf_address(addr, bdf, offset, &address);

	switch (size) {
	case PCI_SIZE_8:
		*value = __raw_readb(address);
		return 0;
	case PCI_SIZE_16:
		*value = __raw_readw(address);
		return 0;
	case PCI_SIZE_32:
		*value = __raw_readl(address);
		return 0;
	default:
		return -1;
	}

	return 0;
}

static int
pci_write_config(uint64_t addr, int32_t bdf, uint32_t offset, uint32_t value, enum pci_size_t size)
{
	uint64_t address;

	pci_ecam_conf_address(addr, bdf, offset, &address);

	switch (size) {
	case PCI_SIZE_8:
		__raw_writeb(value & 0xFF, address);
		return 0;
	case PCI_SIZE_16:
		__raw_writew(value & 0xFFFF, address);
		return 0;
	case PCI_SIZE_32:
		__raw_writel(value, address);
		return 0;
	default:
		return -1;
	}

	return 0;
}

static void pci_show_regs(uint64_t addr, int32_t bdf, struct pci_reg_info* regs)
{
	for (; regs->name; regs++) {
		uint32_t val;

		pci_read_config(addr, bdf, regs->offset, &val, regs->size);
		printf("  %s =%*s%#.*lx\n",
			   regs->name,
			   (int)(28 - strlen(regs->name)),
			   "",
			   pci_field_width(regs->size),
			   val);
	}
}

static struct pci_reg_info regs_start[] = {
	{"vendor ID", PCI_SIZE_16, PCI_VENDOR_ID},
	{"device ID", PCI_SIZE_16, PCI_DEVICE_ID},
	{"command register ID", PCI_SIZE_16, PCI_COMMAND},
	{"status register", PCI_SIZE_16, PCI_STATUS},
	{"revision ID", PCI_SIZE_8, PCI_REVISION_ID},
	{},
};

static struct pci_reg_info regs_rest[] = {
	{"sub class code", PCI_SIZE_8, PCI_CLASS_SUB_CODE},
	{"programming interface", PCI_SIZE_8, PCI_CLASS_PROG},
	{"cache line", PCI_SIZE_8, PCI_CACHE_LINE_SIZE},
	{"latency time", PCI_SIZE_8, PCI_LATENCY_TIMER},
	{"header type", PCI_SIZE_8, PCI_HEADER_TYPE},
	{"BIST", PCI_SIZE_8, PCI_BIST},
	{"base address 0", PCI_SIZE_32, PCI_BASE_ADDRESS_0},
	{},
};

static struct pci_reg_info regs_normal[] = {
	{"base address 1", PCI_SIZE_32, PCI_BASE_ADDRESS_1},
	{"base address 2", PCI_SIZE_32, PCI_BASE_ADDRESS_2},
	{"base address 3", PCI_SIZE_32, PCI_BASE_ADDRESS_3},
	{"base address 4", PCI_SIZE_32, PCI_BASE_ADDRESS_4},
	{"base address 5", PCI_SIZE_32, PCI_BASE_ADDRESS_5},
	{"cardBus CIS pointer", PCI_SIZE_32, PCI_CARDBUS_CIS},
	{"sub system vendor ID", PCI_SIZE_16, PCI_SUBSYSTEM_VENDOR_ID},
	{"sub system ID", PCI_SIZE_16, PCI_SUBSYSTEM_ID},
	{"expansion ROM base address", PCI_SIZE_32, PCI_ROM_ADDRESS},
	{"interrupt line", PCI_SIZE_8, PCI_INTERRUPT_LINE},
	{"interrupt pin", PCI_SIZE_8, PCI_INTERRUPT_PIN},
	{"min Grant", PCI_SIZE_8, PCI_MIN_GNT},
	{"max Latency", PCI_SIZE_8, PCI_MAX_LAT},
	{},
};

static struct pci_reg_info regs_bridge[] = {
	{"base address 1", PCI_SIZE_32, PCI_BASE_ADDRESS_1},
	{"primary bus number", PCI_SIZE_8, PCI_PRIMARY_BUS},
	{"secondary bus number", PCI_SIZE_8, PCI_SECONDARY_BUS},
	{"subordinate bus number", PCI_SIZE_8, PCI_SUBORDINATE_BUS},
	{"secondary latency timer", PCI_SIZE_8, PCI_SEC_LATENCY_TIMER},
	{"IO base", PCI_SIZE_8, PCI_IO_BASE},
	{"IO limit", PCI_SIZE_8, PCI_IO_LIMIT},
	{"secondary status", PCI_SIZE_16, PCI_SEC_STATUS},
	{"memory base", PCI_SIZE_16, PCI_MEMORY_BASE},
	{"memory limit", PCI_SIZE_16, PCI_MEMORY_LIMIT},
	{"prefetch memory base", PCI_SIZE_16, PCI_PREF_MEMORY_BASE},
	{"prefetch memory limit", PCI_SIZE_16, PCI_PREF_MEMORY_LIMIT},
	{"prefetch memory base upper", PCI_SIZE_32, PCI_PREF_BASE_UPPER32},
	{"prefetch memory limit upper", PCI_SIZE_32, PCI_PREF_LIMIT_UPPER32},
	{"IO base upper 16 bits", PCI_SIZE_16, PCI_IO_BASE_UPPER16},
	{"IO limit upper 16 bits", PCI_SIZE_16, PCI_IO_LIMIT_UPPER16},
	{"expansion ROM base address", PCI_SIZE_32, PCI_ROM_ADDRESS1},
	{"interrupt line", PCI_SIZE_8, PCI_INTERRUPT_LINE},
	{"interrupt pin", PCI_SIZE_8, PCI_INTERRUPT_PIN},
	{"bridge control", PCI_SIZE_16, PCI_BRIDGE_CONTROL},
	{},
};

static struct pci_reg_info regs_cardbus[] = {
	{"capabilities", PCI_SIZE_8, PCI_CB_CAPABILITY_LIST},
	{"secondary status", PCI_SIZE_16, PCI_CB_SEC_STATUS},
	{"primary bus number", PCI_SIZE_8, PCI_CB_PRIMARY_BUS},
	{"CardBus number", PCI_SIZE_8, PCI_CB_CARD_BUS},
	{"subordinate bus number", PCI_SIZE_8, PCI_CB_SUBORDINATE_BUS},
	{"CardBus latency timer", PCI_SIZE_8, PCI_CB_LATENCY_TIMER},
	{"CardBus memory base 0", PCI_SIZE_32, PCI_CB_MEMORY_BASE_0},
	{"CardBus memory limit 0", PCI_SIZE_32, PCI_CB_MEMORY_LIMIT_0},
	{"CardBus memory base 1", PCI_SIZE_32, PCI_CB_MEMORY_BASE_1},
	{"CardBus memory limit 1", PCI_SIZE_32, PCI_CB_MEMORY_LIMIT_1},
	{"CardBus IO base 0", PCI_SIZE_16, PCI_CB_IO_BASE_0},
	{"CardBus IO base high 0", PCI_SIZE_16, PCI_CB_IO_BASE_0_HI},
	{"CardBus IO limit 0", PCI_SIZE_16, PCI_CB_IO_LIMIT_0},
	{"CardBus IO limit high 0", PCI_SIZE_16, PCI_CB_IO_LIMIT_0_HI},
	{"CardBus IO base 1", PCI_SIZE_16, PCI_CB_IO_BASE_1},
	{"CardBus IO base high 1", PCI_SIZE_16, PCI_CB_IO_BASE_1_HI},
	{"CardBus IO limit 1", PCI_SIZE_16, PCI_CB_IO_LIMIT_1},
	{"CardBus IO limit high 1", PCI_SIZE_16, PCI_CB_IO_LIMIT_1_HI},
	{"interrupt line", PCI_SIZE_8, PCI_INTERRUPT_LINE},
	{"interrupt pin", PCI_SIZE_8, PCI_INTERRUPT_PIN},
	{"bridge control", PCI_SIZE_16, PCI_CB_BRIDGE_CONTROL},
	{"subvendor ID", PCI_SIZE_16, PCI_CB_SUBSYSTEM_VENDOR_ID},
	{"subdevice ID", PCI_SIZE_16, PCI_CB_SUBSYSTEM_ID},
	{"PC Card 16bit base address", PCI_SIZE_32, PCI_CB_LEGACY_MODE_BASE},
	{},
};

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

void pci_header_show(uint64_t addr, int32_t bdf)
{
	uint32_t class, header_type;

	pci_read_config(addr, bdf, PCI_CLASS_CODE, &class, PCI_SIZE_8);
	pci_read_config(addr, bdf, PCI_HEADER_TYPE, &header_type, PCI_SIZE_8);

	pci_show_regs(addr, bdf, regs_start);
	printf("  class code =                  0x%.2x (%s)\n", (uint32_t) class, pci_class_str(class));
	pci_show_regs(addr, bdf, regs_rest);

	switch (header_type & 0x03) {
	case PCI_HEADER_TYPE_NORMAL: /* "normal" PCI device */
		pci_show_regs(addr, bdf, regs_normal);
		break;
	case PCI_HEADER_TYPE_BRIDGE: /* PCI-to-PCI bridge */
		pci_show_regs(addr, bdf, regs_bridge);
		break;
	case PCI_HEADER_TYPE_CARDBUS: /* PCI-to-CardBus bridge */
		pci_show_regs(addr, bdf, regs_cardbus);
		break;

	default:
		printf("unknown header\n");
		break;
	}
}

int pci_bar_show(uint64_t addr, int32_t bdf)
{
	uint32_t header_type;
	int bar_cnt, bar_id, mem_type;
	bool is_64, is_io;
	uint32_t base_low, base_high;
	uint32_t size_low, size_high;
	uint64_t base, size;
	uint32_t reg_addr;
	int prefetchable;

	pci_read_config(addr, bdf, PCI_HEADER_TYPE, &header_type, PCI_SIZE_8);

	if (header_type == PCI_HEADER_TYPE_CARDBUS) {
		printf("CardBus doesn't support BARs\n");
		return -1;
	}

	bar_cnt = (header_type == PCI_HEADER_TYPE_NORMAL) ? 6 : 2;

	printf("ID   Base                Size                Width  Type\n");
	printf("----------------------------------------------------------\n");

	bar_id = 0;
	reg_addr = PCI_BASE_ADDRESS_0;
	while (bar_cnt) {
		pci_read_config(addr, bdf, reg_addr, &base_low, PCI_SIZE_32);
		pci_write_config(addr, bdf, reg_addr, 0xffffffff, PCI_SIZE_32);
		pci_read_config(addr, bdf, reg_addr, &size_low, PCI_SIZE_32);
		pci_write_config(addr, bdf, reg_addr, base_low, PCI_SIZE_32);
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
			pci_read_config(addr, bdf, reg_addr, &base_high, PCI_SIZE_32);
			pci_write_config(addr, bdf, reg_addr, 0xffffffff, PCI_SIZE_32);
			pci_read_config(addr, bdf, reg_addr, &size_high, PCI_SIZE_32);
			pci_write_config(addr, bdf, reg_addr, base_high, PCI_SIZE_32);
			bar_cnt--;
			reg_addr += 4;
			is_64 = 1;
		}

		base = base | ((uint64_t)base_high << 32);
		size = size | ((uint64_t)size_high << 32);

		if ((!is_64 && size_low) || (is_64 && size)) {
			size = ~size + 1;
			printf(" %d   %#016llx  %#016llx  %d     %s   %s\n",
				   bar_id,
				   (unsigned long long)base,
				   (unsigned long long)size,
				   is_64 ? 64 : 32,
				   is_io ? "I/O" : "MEM",
				   prefetchable ? "Prefetchable" : "");
		}

		bar_id++;
		bar_cnt--;
	}

	return 0;
}

// porting from uboot and the original named pci_bind_bus_devices in pci-uclass.h
int pci_find_devices_on_bus(uint64_t addr, uint32_t bus)
{
	uint32_t vendor, device;
	uint32_t header_type, val;
	pci_dev_t bdf, end;
	bool found_multi;
	int ret;

	found_multi = false;
	end = PCI_BDF(bus, PCI_MAX_PCI_DEVICES - 1, PCI_MAX_PCI_FUNCTIONS - 1);
	for (bdf = PCI_BDF(bus, 0, 0); bdf <= end; bdf += PCI_BDF(0, 0, 1)) {
		uint32_t class;

		if (!PCI_FUNC(bdf))
			found_multi = false;
		if (PCI_FUNC(bdf) && !found_multi)
			continue;
		/* Check only the first access, we don't expect problems */
		ret = pci_read_config(addr, bdf, PCI_HEADER_TYPE, &header_type, PCI_SIZE_8);
		if (ret)
			goto error;
		pci_read_config(addr, bdf, PCI_VENDOR_ID, &vendor, PCI_SIZE_16);
		if (vendor == 0xffff || vendor == 0x0000)
			continue;

		if (!PCI_FUNC(bdf))
			found_multi = header_type & 0x80;

		printf("%s: bus %d: found device %x, function %d\n",
			   __func__,
			   bus,
			   PCI_DEV(bdf),
			   PCI_FUNC(bdf));
		pci_read_config(addr, bdf, PCI_DEVICE_ID, &device, PCI_SIZE_16);
		pci_read_config(addr, bdf, PCI_CLASS_REVISION, &class, PCI_SIZE_32);
		class >>= 8;

		/* If nothing in the device tree, bind a device */
		if ((header_type & 0x7f) == PCI_HEADER_TYPE_NORMAL) {
			pci_read_config(addr, bdf, PCI_SUBSYSTEM_VENDOR_ID, &val, PCI_SIZE_32);
		}
		printf("bdf:%d.%d.%d VendorID: 0x%x, DeviceID: 0x%x, Class: 0x%x, subsystem ID: 0x%x\n",
			   bus,
			   PCI_DEV(bdf),
			   PCI_FUNC(bdf),
			   vendor,
			   device,
			   class,
			   val);
	}

	return 0;
error:
	printf("Cannot read bus configuration: %d\n", ret);

	return ret;
}

// TBD: pci_hose_config_device in pci.c
// TBD: pci_hose_find_capability/pci_hose_find_cap_start/pci_find_cap/pci_find_next_ext_capability