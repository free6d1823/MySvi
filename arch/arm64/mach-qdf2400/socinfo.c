#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <asm/mach/chipinfo.h>
#include <asm/mach/hal/HALtlmmHWIO.h>
#include <asm/mach/hal/HALsecbootHWIO.h>
#include <asm/mach/hal/HALtcsrHWIO.h>
#include <asm/hal/HALhwio.h>

#define SOCTYPE_SILICON 0x00
#define SOCTYPE_VIRTIO  0x10
#define SOCTYPE_SUFI_42 0x42
#define SOCTYPE_RUMI_48 0x48

#define HWIO_QFPROM_CORR_PTE_ROWn_LSB_FOUNDRY_ID_BMSK  0x00000003
#define HWIO_QFPROM_CORR_PTE_ROWn_LSB_FOUNDRY_ID_SHFT  0x0

typedef struct {
	DIEINFO_PROPS DieInfo[BOOT_MAX_NUM_DIES];
} SOCINFO_PROPS;

static SOCINFO_PROPS SocInfo;

int init_socket_info(uint32_t SocketNum)
{
  uint8_t MajorNum = 0;
  uint8_t MinorNum = 0;
  uint8_t PackageSubstrate = 0;
  SOCINFO_SOCTYPE_TYPE SocType;
  uint8_t SocID = HWIO_INF(SPARE3, SPARE3_INPUT);
  uint16_t ProductID = 0;
  uint32_t DieVersion = 0;
  uint32_t DeviceMember = 0;

  if (SocketNum >= BOOT_MAX_NUM_DIES) {
    return -EINVAL;
  }

  /*fw802 use HWIO_INF(QFPROM_CORR_SPARE_REG27_ROW20_MSB, PRODUCT_CODE);*/
  //ProductID = HWIO_INF(QFPROM_CORR_SPARE_REG27_ROW20_MSB, PRODUCT_CODE);
  ProductID = HWIO_INF(OEM_ID, OEM_PRODUCT_ID);

  if(ProductID == 0) {
    ProductID = PcdGet32(PcdProductID);
  }

  MajorNum = HWIO_INF(TCSR_SOC_HW_VERSION, MAJOR_VERSION);
  MinorNum = HWIO_INF(TCSR_SOC_HW_VERSION, MINOR_VERSION);
  DeviceMember = HWIO_INF(TCSR_SOC_HW_VERSION, DEVICE_MEMBER);

  /* Check if Major Version is 2. */
  if(MajorNum == 2) {
    DieVersion = HWIO_INF(JTAG_ID, DIE_VERSION);
    if(DieVersion >= 3) {
      MinorNum = 1;
    }
  }


  if(DeviceMember == 0x810)
  {
    MajorNum = 2;
    MinorNum = 0;
  }

  if(in_dword_masked(BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_ADDRESS, BOOT_LOGGER_SILICON_SELECT_RE_BMSK))
  {
    PackageSubstrate = in_dword_masked(BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_ADDRESS,
                                       BOOT_LOGGER_SILICON_RE_PACKAGE_SUBSTRATE_BMSK) >>
                       BOOT_LOGGER_SILICON_RE_PACKAGE_SUBSTRATE_SHFT;
  }
  else
  {
    PackageSubstrate = in_dword_masked(BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_ADDRESS,
                                       BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_BMSK) >>
                       BOOT_LOGGER_SILICON_PACKAGE_SUBSTRATE_SHFT;
  }

  switch(SocID)
  {
    case SOCTYPE_VIRTIO:
      SocType = SOCINFO_SOCTYPE_VIRTIO;
      break;
    case SOCTYPE_RUMI_48:
      SocType = SOCINFO_SOCTYPE_RUMI48;
      break;
    case SOCTYPE_SUFI_42:
      SocType = SOCINFO_SOCTYPE_RUMI42;
      break;
    case SOCTYPE_SILICON:
    default:
      SocType = SOCINFO_SOCTYPE_SILICON;
      break;
  }

  SocInfo.DieInfo[SocketNum].MajorVersion = MajorNum;
  SocInfo.DieInfo[SocketNum].MinorVersion = MinorNum;
  SocInfo.DieInfo[SocketNum].PackageSubstrate = PackageSubstrate;
  SocInfo.DieInfo[SocketNum].Generation = ProductID >> 12;
  SocInfo.DieInfo[SocketNum].Feature = (ProductID >> 8) & 0xF;
  SocInfo.DieInfo[SocketNum].Bin = ProductID & 0xFF;
  SocInfo.DieInfo[SocketNum].SocType = SocType;
  SocInfo.DieInfo[SocketNum].SerialNumber = HWIO_INF(QFPROM_CORR_SERIAL_NUM_LSB, SERIAL_NUM);
  /*The 802 use the HWIO_INF(QFPROM_CORR_PTE_ROW0_LSB, FOUNDRY_ID) to get the FoundryID*/
  //SocInfo.DieInfo[SocketNum].FoundryID = HWIO_INF(QFPROM_CORR_PTE_ROW0_LSB, FOUNDRY_ID);
  SocInfo.DieInfo[SocketNum].FoundryID = HWIO_INFI(QFPROM_CORR_PTE_ROWn_LSB, 0, FOUNDRY_ID);

  if(SocInfo.DieInfo[SocketNum].Generation == 0x1) {
    SocInfo.DieInfo[SocketNum].Generation = 0x2;
  }

  return 0;
}

int get_socket_num(uint32_t *NumSockets)
{
  if(NumSockets == NULL) {
    return -EINVAL;
  }

  *NumSockets = BOOT_MAX_NUM_DIES;
  return 0;
}

int get_socket_info(DIEINFO_PROPS * DieInfo, uint32_t SocketNum)
{
  if(DieInfo == NULL || SocketNum >= BOOT_MAX_NUM_DIES) {
    return -EINVAL;
  }

  memscpy(DieInfo, sizeof(DIEINFO_PROPS), &SocInfo.DieInfo[SocketNum], sizeof(SocInfo.DieInfo[SocketNum]));

  return 0;
}

int get_all_socket_info(DIEINFO_PROPS * DieInfo, uint32_t * NumSockets)
{
  if(NumSockets == NULL ||
     (*NumSockets != 0 && DieInfo == NULL)) {
    return -EINVAL;
  }

  if(*NumSockets > BOOT_MAX_NUM_DIES) {
    return -EINVAL;
  }

  if(*NumSockets < BOOT_MAX_NUM_DIES) {
    *NumSockets = BOOT_MAX_NUM_DIES;
    return -ENOMEM;
  }

  memscpy(DieInfo, (sizeof(DIEINFO_PROPS) * (*NumSockets)), SocInfo.DieInfo, sizeof(SocInfo.DieInfo));

  return 0;
}
