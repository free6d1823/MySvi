#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <target/cmdline.h>
#include <asm/mach/chipinfo.h>
#include <asm/mach/hal/HALbootHWIO.h>
#include <asm/mach/hal/HALtcsrHWIO.h>
#include <asm/hal/HALhwio.h>


uint32_t get_version (void)
{
	uint32_t ChipVersion = 0;
	uint32_t DeviceMember = 0;
	uint32_t major_version = 0;
	uint32_t minor_version = 0;
	uint32_t die_version = 0;

	die_version = HWIO_INF(JTAG_ID, DIE_VERSION);
	DeviceMember = HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_MEMBER);

	major_version = HWIO_TCSR_SOC_HW_VERSION_INM(HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK) >> HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT;

	minor_version = HWIO_TCSR_SOC_HW_VERSION_INM(HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK) >> HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT;

	if((major_version == 2) && (die_version >= 3))
		minor_version = 1;

	ChipVersion = CHIPINFO_VERSION(major_version, minor_version);

	/* SW workaround for the HW bug - "TCSR_SOC_HW_VERSION reads 0" */
	 if (ChipVersion == 0)
	{
		ChipVersion = CHIPINFO_VERSION(1,0);
	}


	if(DeviceMember == 0x810)
	{
	   ChipVersion = CHIPINFO_VERSION(2,1);
	}

	return ChipVersion;
} /* END Chipinfo_GetVersion */

uint32_t get_serialnum(void)
{
	return HWIO_INF(QFPROM_CORR_SERIAL_NUM_LSB, SERIAL_NUM);
}

uint16_t get_product_code(void)
{
	return HWIO_INF(QFPROM_CORR_SPARE_REG27_ROW20_MSB, PRODUCT_CODE);
}

uint8_t get_generation(void)
{
	return (HWIO_INF(QFPROM_CORR_SPARE_REG27_ROW20_MSB, PRODUCT_CODE) >> 12);
}


uint8_t get_feature(void)
{
	return ((HWIO_INF(QFPROM_CORR_SPARE_REG27_ROW20_MSB, PRODUCT_CODE) >> 8) & 0xF);
}

uint8_t get_bin(void)
{
	return (HWIO_INF(QFPROM_CORR_SPARE_REG27_ROW20_MSB, PRODUCT_CODE) & 0xFF);
}

void print_product_code()
{
	printf("ProductCode:  0x%04x @FUSE R27_R20 ( generation: 0x%0x, feature: 0x%0x, bin: 0x%02x )\n",
				get_product_code(), get_generation(),  get_feature(), get_bin());
}

uint8_t get_package_substrate(void)
{
	if(in_dword_masked(BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_ADDRESS, BOOT_LOGGER_SILICON_SELECT_RE_BMSK)) {
	return in_dword_masked(BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_ADDRESS,
									   BOOT_LOGGER_SILICON_RE_PACKAGE_SUBSTRATE_BMSK) >>
					   BOOT_LOGGER_SILICON_RE_PACKAGE_SUBSTRATE_SHFT;
	} else {
		return in_dword_masked(BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_ADDRESS,
									   BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_BMSK) >>
					   BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_SHFT;
  }
}

uint32_t get_foundryid(void)
{
  DIEINFO_PROPS DieInfo;
  get_socket_info(&DieInfo, 0);

  return DieInfo.FoundryID;
}

void check_chip_family(void)
{
	uint32_t DeviceMember = 0;

	DeviceMember = HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_MEMBER);

	switch(DeviceMember)
	{
		case HXT1_TYPE:
			printf("The current soc is HXT1.\n");
			break;
		case FALKOR_TYPE:
			printf("The current soc is Falkor.\n");
			break;
		default:
			printf("The current soc is unkown.\n");
			break;
	}
}

uint32_t get_soc_type(void)
{
	 volatile uint32_t *soc_type_addr = (volatile uint32_t *)(0x000000ff0c703834);
	 return (*soc_type_addr) & 0xff;
}

void print_soc_type(void)
{
	uint32_t soc_type = get_soc_type();
	switch (soc_type)
	{
		case 0x10:
			printf("The soc type is %x SOCTYPE_VIRTIO\n",soc_type);
			break;
		case 0x48:
			printf("The soc type is %x SOCTYPE_RUMI_48\n",soc_type);
			break;
		case 0x42:
			printf("The soc type is %x SOCTYPE_SUFI_42\n",soc_type);
			break;
		case 0x00:
			printf("The soc type is %x SOCTYPE_SILICON\n",soc_type);
			break;
		default:
			printf("The soc type is %x default SOCTYPE_SILICON\n",soc_type);
			break;
	}
}


uint32_t get_current_core_midr_el1(void)
{
	uint32_t midr = 0;

	asm volatile
	(
		"MRS			 %0, MIDR_EL1 \n\t"
		: "=r" (midr)::
	);
	return midr;
}

uint32_t get_current_core_aidr_el1(void)
{
	uint32_t midr = 0;

	asm volatile
	(
		"MRS			 %0, AIDR_EL1 \n\t"
		: "=r" (midr)::
	);
	return midr;
}

void print_chipinfo_family()
{
	uint16_t family_member;
	uint16_t device_member;
	uint8_t major_ver;
	uint8_t minor_ver;
	volatile uint32_t *soc_hw_version_addr = (volatile uint32_t *)(0xFF02E40000);

	family_member = (HWIO_TCSR_SOC_HW_VERSION_INM(HWIO_TCSR_SOC_HW_VERSION_FAMILY_MEMBER_BMSK)) >> HWIO_TCSR_SOC_HW_VERSION_FAMILY_MEMBER_SHFT;
	device_member = (HWIO_TCSR_SOC_HW_VERSION_INM(HWIO_TCSR_SOC_HW_VERSION_DEVICE_MEMBER_BMSK)) >> HWIO_TCSR_SOC_HW_VERSION_DEVICE_MEMBER_SHFT;
	major_ver = (HWIO_TCSR_SOC_HW_VERSION_INM(HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_BMSK)) >> HWIO_TCSR_SOC_HW_VERSION_MAJOR_VERSION_SHFT;
	minor_ver = (HWIO_TCSR_SOC_HW_VERSION_INM(HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_BMSK)) >> HWIO_TCSR_SOC_HW_VERSION_MINOR_VERSION_SHFT;

	printf("SOC_HW_VERSION        @ 0x%llx = 0x%08x ( FamilyMember: 0x%0x, DeviceMember 0x%03x, MajorVer 0x%02x, MinorVer 0x%02x )\n",
	       (uint64_t)soc_hw_version_addr,
	       (uint32_t)(*soc_hw_version_addr),
	       family_member, device_member, major_ver, minor_ver);
}

void print_jtag_id()
{
	volatile uint32_t *jtag_id_addr = (volatile uint32_t *)(0x000000ff0c7038e0);
	uint8_t die_ver;
	uint32_t jtag_id;

	die_ver = HWIO_JTAG_ID_INM(HWIO_JTAG_ID_DIE_VERSION_BMSK) >> HWIO_JTAG_ID_DIE_VERSION_SHFT;
	jtag_id = HWIO_JTAG_ID_INM(HWIO_JTAG_ID_JTAG_ID_BMSK) >> HWIO_JTAG_ID_JTAG_ID_SHFT;

	printf("JTAG_ID               @ 0x%llx = 0x%08x ( DieVersion 0x%0x, JtagID 0x%07x(0-11:ManufacturerID, 12-27:Product/DeviceID) )\n" ,
	       (uint64_t)jtag_id_addr,
	       (uint32_t)(*jtag_id_addr), die_ver, jtag_id);
}

int get_raw_chip_info(void)
{
	volatile uint32_t *boot_config_addr = (volatile uint32_t *)(0x000000ff0c703834);
	volatile uint32_t *oem_id_addr = (volatile uint32_t *)(0x000000ff0c7038e4);
	volatile uint32_t *extend_chipid_addr = (volatile uint32_t *)(0x000000ff0c7041ac);
	volatile uint32_t *midr_el1_addr = (volatile uint32_t *)(0x0FF14010D00);
	volatile uint32_t *aidr_el1_addr = (volatile uint32_t *)(0x0FF14010CFC);

	print_soc_type();
	printf("BOOT_CONFIG           @ 0x%llx = 0x%08x\n",
	       (uint64_t)boot_config_addr, (uint32_t)(*boot_config_addr));
	printf("OEM_ID                @ 0x%llx = 0x%08x\n",
	       (uint64_t)oem_id_addr, (uint32_t)(*oem_id_addr));
	printf("CHIP_ID               @ 0x%llx = 0x%08x\n",
	       (uint64_t)extend_chipid_addr,
	       (uint32_t)(*extend_chipid_addr));
	printf("MIDR_EL1              @ 0x%llx = 0x%08x \n",
	       (uint64_t)midr_el1_addr, (uint32_t)(*midr_el1_addr));
	printf("AIDR_EL1              @ 0x%llx = 0x%08x \n",
	       (uint64_t)aidr_el1_addr, (uint32_t)(*aidr_el1_addr));
	print_jtag_id();
	print_chipinfo_family();
	return 0;
}
