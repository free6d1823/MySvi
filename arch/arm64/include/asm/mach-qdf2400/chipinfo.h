#ifndef CHIP_INFO_H
#define CHIP_INFO_H

#include <stdint.h>

/* Number of dies this target supports */
#define BOOT_MAX_NUM_DIES        1
#define BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_ADDRESS	\
	HWIO_QFPROM_CORR_CALIB_ROW22_MSB_ADDR
#define BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_BMSK	0x30
#define BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_SHFT	0x4
#define BOOT_LOGGER_SILICON_RE_PACKAGE_SUBSTRATE_BMSK	0xC0
#define BOOT_LOGGER_SILICON_RE_PACKAGE_SUBSTRATE_SHFT	0x6
#define BOOT_LOGGER_SILICON_SELECT_RE_BMSK		0x100

#define PcdGet32(TokenName)				\
	_PCD_GET_MODE_32_##TokenName
#define _PCD_GET_MODE_32_PcdProductID			0x00002400U

#define SOCINFO_VERSION(DieInfo)	\
	(((DieInfo.MajorVersion) << 4) | (DieInfo.MinorVersion))

typedef enum {
	SOCINFO_SOCTYPE_SILICON = 0,
	SOCINFO_SOCTYPE_VIRTIO  = 1,
	SOCINFO_SOCTYPE_RUMI42  = 2,
	SOCINFO_SOCTYPE_RUMI48  = 3,
	SOCINFO_MAX_SOCTYPES    = 4,
	SOCINFO_SOCTYPE_8BITS   = 0x7F
} SOCINFO_SOCTYPE_TYPE;

typedef enum {
	SOCINFO_FOUNDRYID_UNKNOWN    = 0,
	SOCINFO_FOUNDRYID_TSMC       = 1,
	SOCINFO_FOUNDRYID_SS         = 2,
	SOCINFO_MAX_FOUNDRYIDS       = 3,
	SOCINFO_FOUNDRYID_32BITS     = 0x7FFFFFF
} SOCINFO_FOUNDRYID_TYPE;

typedef struct {
	uint8_t MajorVersion;
	uint8_t MinorVersion;
	uint8_t PackageSubstrate;
	uint8_t Generation;
	uint8_t Feature;
	uint8_t Bin;
	uint8_t SocType;
	uint16_t Reserved;
	uint32_t SerialNumber;
	SOCINFO_FOUNDRYID_TYPE FoundryID;
} DIEINFO_PROPS;

int init_socket_info(uint32_t SocketNum);
int get_socket_num(uint32_t *NumSockets);
int get_socket_info(DIEINFO_PROPS *DieInfo, uint32_t SocketNum);
int get_all_socket_info(DIEINFO_PROPS *DieInfo, uint32_t *NumSockets);

#define CHIPINFO_MAJOR_VERSION(version) ((version) >> 16)
#define CHIPINFO_MINOR_VERSION(version) ((version) & 0x0000FFFF)
#define CHIPINFO_VERSION(major, minor)  (((major) << 16) | (minor))
#define HXT1_TYPE    0x810
#define FALKOR_TYPE  0x001

uint32_t get_version (void);
uint32_t get_serialnum(void);
uint16_t get_productid(void);
uint32_t get_foundryid(void);
uint8_t get_generation(void);
uint8_t get_feature(void);
uint8_t get_bin(void);
uint8_t get_package_substrate(void);
void check_chip_family(void);
void print_product_code(void);
int get_raw_chip_info(void);

#endif
