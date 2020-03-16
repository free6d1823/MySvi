#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <target/delay.h>
#include <target/pmic.h>
#include <target/cmdline.h>
#include <asm/mach/hal/HALbootHWIO.h>

//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define INVALID_SID -1
#define INVALID_DATA ((int16)0x8000)

// Max number of bytes we can read/write at a time.
#define MAX_TRANSACTION_LEN 8
#define PM_SBL_WRITE 0

uint8_t *pmicArbBaseAddrs[SWIO_MAX_BUSES_SUPPORTED] = {
	(void *)0xff30000000, NULL, NULL
};

#define _DEFINE_SYSREG_READ_FUNC(_name, _reg_name)\
static inline uint64_t read_ ## _name(void)\
{\
uint64_t v;\
asm volatile ("mrs %0, " #_reg_name : "=r" (v));\
return v;\
}
#define DEFINE_SYSREG_READ_FUNC(_name)   _DEFINE_SYSREG_READ_FUNC(_name, _name)
DEFINE_SYSREG_READ_FUNC(cntpct_el0)

typedef struct
{
  char word1; /* Val */
  char word2; /* Offset, Condition  */
  char word3; /* Base Addr, Test Mask */
  char word4; /* Command + SlaveID */
}pm_pbs_ram_data_type;

typedef struct {
    int8_t sid;
    int16_t prevIdx;
    int16_t nextIdx;
} ChannelMapEntry;

typedef struct
{
    uint32_t numReserved;
    uint16_t *reserved;
} SpmiOs_ReservedChannels;

typedef struct {
    uint8_t owner;
    //boolean hasInterruptSupport;
    //PmicArbIsrCallback isrCallback;
    //SpmiOs_ReservedChannels* reservedChans[SWIO_MAX_BUSES_SUPPORTED];
    //int16 periphMap[SWIO_MAX_BUSES_SUPPORTED][SPMI_MAX_PERIPH_ID + 1];
    //ChannelMapEntry channelMap[SWIO_MAX_BUSES_SUPPORTED][SWIO_MAX_CHANNELS_SUPPORTED];
} PmicArbInfo;

typedef struct
{
   uint8_t  sid;
   uint8_t  data;
   uint16_t address;
   uint8_t  reg_operation;
   uint8_t  cond_start_index;
   uint8_t  cond_end_index;
}pm_sbl_seq_type;

PmicArbInfo spmiPmicArbInfo = {0};

static const uint32_t GENI_CFG_RAM_COUNT = 101;
static const uint32_t GENI_CFG_RAM_VALUES[] =
{
   0x0000FFFF,  // GENI_CFG_RAMn[0]
   0x00000001,  // GENI_CFG_RAMn[1]
   0x00048A0C,  // GENI_CFG_RAMn[2]
   0x0019C470,  // GENI_CFG_RAMn[3]
   0x0005921C,  // GENI_CFG_RAMn[4]
   0x0019C470,  // GENI_CFG_RAMn[5]
   0x0006EA00,  // GENI_CFG_RAMn[6]
   0x0016C000,  // GENI_CFG_RAMn[7]
   0x00076608,  // GENI_CFG_RAMn[8]
   0x00100000,  // GENI_CFG_RAMn[9]
   0x00076688,  // GENI_CFG_RAMn[10]
   0x00100000,  // GENI_CFG_RAMn[11]
   0x00076648,  // GENI_CFG_RAMn[12]
   0x00100000,  // GENI_CFG_RAMn[13]
   0x000766C8,  // GENI_CFG_RAMn[14]
   0x00100000,  // GENI_CFG_RAMn[15]
   0x0007BA28,  // GENI_CFG_RAMn[16]
   0x00100840,  // GENI_CFG_RAMn[17]
   0x0008D2A8,  // GENI_CFG_RAMn[18]
   0x00108810,  // GENI_CFG_RAMn[19]
   0x00094A68,  // GENI_CFG_RAMn[20]
   0x00108810,  // GENI_CFG_RAMn[21]
   0x0009D258,  // GENI_CFG_RAMn[22]
   0x00000000,  // GENI_CFG_RAMn[23]
   0x000A72D8,  // GENI_CFG_RAMn[24]
   0x001008A0,  // GENI_CFG_RAMn[25]
   0x000AF238,  // GENI_CFG_RAMn[26]
   0x001008A0,  // GENI_CFG_RAMn[27]
   0x000B3204,  // GENI_CFG_RAMn[28]
   0x0016C000,  // GENI_CFG_RAMn[29]
   0x000B8A02,  // GENI_CFG_RAMn[30]
   0x00108810,  // GENI_CFG_RAMn[31]
   0x000BF206,  // GENI_CFG_RAMn[32]
   0x00108810,  // GENI_CFG_RAMn[33]
   0x000C4E01,  // GENI_CFG_RAMn[34]
   0x00100000,  // GENI_CFG_RAMn[35]
   0x00041618,  // GENI_CFG_RAMn[36]
   0x00044612,  // GENI_CFG_RAMn[37]
   0x0004500F,  // GENI_CFG_RAMn[38]
   0x0004500F,  // GENI_CFG_RAMn[39]
   0x00005000,  // GENI_CFG_RAMn[40]
   0x00048D48,  // GENI_CFG_RAMn[41]
   0x00086252,  // GENI_CFG_RAMn[42]
   0x00150088,  // GENI_CFG_RAMn[43]
   0x00041618,  // GENI_CFG_RAMn[44]
   0x00044612,  // GENI_CFG_RAMn[45]
   0x0004500F,  // GENI_CFG_RAMn[46]
   0x0004500F,  // GENI_CFG_RAMn[47]
   0x00046080,  // GENI_CFG_RAMn[48]
   0x00051051,  // GENI_CFG_RAMn[49]
   0x0002BC00,  // GENI_CFG_RAMn[50]
   0x0008F26C,  // GENI_CFG_RAMn[51]
   0x0000D000,  // GENI_CFG_RAMn[52]
   0x0018E800,  // GENI_CFG_RAMn[53]
   0x0008C064,  // GENI_CFG_RAMn[54]
   0x00041623,  // GENI_CFG_RAMn[55]
   0x00042628,  // GENI_CFG_RAMn[56]
   0x00001E00,  // GENI_CFG_RAMn[57]
   0x00085052,  // GENI_CFG_RAMn[58]
   0x00041627,  // GENI_CFG_RAMn[59]
   0x00105000,  // GENI_CFG_RAMn[60]
   0x00041627,  // GENI_CFG_RAMn[61]
   0x00045147,  // GENI_CFG_RAMn[62]
   0x00045000,  // GENI_CFG_RAMn[63]
   0x0004A25F,  // GENI_CFG_RAMn[64]
   0x0005313E,  // GENI_CFG_RAMn[65]
   0x0008527F,  // GENI_CFG_RAMn[66]
   0x00040051,  // GENI_CFG_RAMn[67]
   0x0004BE68,  // GENI_CFG_RAMn[68]
   0x0018E800,  // GENI_CFG_RAMn[69]
   0x00043209,  // GENI_CFG_RAMn[70]
   0x00044051,  // GENI_CFG_RAMn[71]
   0x00004800,  // GENI_CFG_RAMn[72]
   0x0008505F,  // GENI_CFG_RAMn[73]
   0x00043209,  // GENI_CFG_RAMn[74]
   0x00044051,  // GENI_CFG_RAMn[75]
   0x00004800,  // GENI_CFG_RAMn[76]
   0x0008504F,  // GENI_CFG_RAMn[77]
   0x0004A627,  // GENI_CFG_RAMn[78]
   0x00045000,  // GENI_CFG_RAMn[79]
   0x0004A25E,  // GENI_CFG_RAMn[80]
   0x00055090,  // GENI_CFG_RAMn[81]
   0x00116000,  // GENI_CFG_RAMn[82]
   0x00043209,  // GENI_CFG_RAMn[83]
   0x00044051,  // GENI_CFG_RAMn[84]
   0x00044828,  // GENI_CFG_RAMn[85]
   0x00080063,  // GENI_CFG_RAMn[86]
   0x00041627,  // GENI_CFG_RAMn[87]
   0x000850AC,  // GENI_CFG_RAMn[88]
   0x00041623,  // GENI_CFG_RAMn[89]
   0x00002600,  // GENI_CFG_RAMn[90]
   0x0008505F,  // GENI_CFG_RAMn[91]
   0x0004161A,  // GENI_CFG_RAMn[92]
   0x00002800,  // GENI_CFG_RAMn[93]
   0x00085052,  // GENI_CFG_RAMn[94]
   0x0004161A,  // GENI_CFG_RAMn[95]
   0x00002800,  // GENI_CFG_RAMn[96]
   0x00086061,  // GENI_CFG_RAMn[97]
   0x000416A0,  // GENI_CFG_RAMn[98]
   0x00147C28,  // GENI_CFG_RAMn[99]
   0x00000000,  // GENI_CFG_RAMn[100]
};

pm_sbl_seq_type pm_sbl_cvr_seq1 [ ] = {
   // MODE - WATCHDOG_EN_PMA8084: 1
   //sid  data    register  reg op      cond start    cond end
   { 0,    0x01,    0x0858,   PM_SBL_WRITE,    0,    0},// 1
   { 0,    0x00,    0x0857,   PM_SBL_WRITE,    0,    0},// 2
   { 0,    0x0F,    0x0854,   PM_SBL_WRITE,    0,    0},// 4
   { 0,    0x03,    0x0855,   PM_SBL_WRITE,    0,    0},// 5
   { 0,    0x08,    0x0856,   PM_SBL_WRITE,    0,    0},// 6
   { 0,    0x80,    0x0857,   PM_SBL_WRITE,    0,    0},// 7

   // MODE - PON_INIT_PMA8084: 2
   //sid  data    register  reg op      cond start    cond end
   { 0,      0x01,   0x0942,   PM_SBL_WRITE,   0,      0},   // 1
   { 0,      0x00,   0x0945,   PM_SBL_WRITE,   0,      0},   // 2
   { 0,      0x14,   0x2C44,   PM_SBL_WRITE,   0,      0},   // 3
   { 0,      0xA5,   0x08D0,   PM_SBL_WRITE,   0,      0},   // 4
   { 0,      0xAA,   0x08F2,   PM_SBL_WRITE,   0,      0},   // 5
   { 0,      0x20,   0x088A,   PM_SBL_WRITE,   0,      0},   // 6
   { 0,      0x0F,   0x0870,   PM_SBL_WRITE,   0,      0},   // 7
   { 0,      0x01,   0x0850,   PM_SBL_WRITE,   0,      0},   // 8
   { 0,      0x01,   0x0851,   PM_SBL_WRITE,   0,      0},   // 9
   { 0,      0x80,   0x0853,   PM_SBL_WRITE,   0,      0},   // 10
   { 0,      0xA5,   0x08D0,   PM_SBL_WRITE,   0,      0},   // 11
   { 0,      0x40,   0x08F3,   PM_SBL_WRITE,   0,      0},   // 12
   { 0,      0x00,   0x2440,   PM_SBL_WRITE,   0,      0},   // 13
   { 0,      0x03,   0x0640,   PM_SBL_WRITE,   0,      0},   // 14

   // MODE - CLOCKS: 3
   //sid  data    register  reg op      cond start    cond end
   { 0,		0x81,	0x5945,	PM_SBL_WRITE,	0,		0},	// 1
   { 0,		0x05,	0x504C,	PM_SBL_WRITE,	0,		0},	// 2
   { 0,		0x00,	0x504D,	PM_SBL_WRITE,	0,		0},	// 3
   { 0,		0xA5,	0x59D0,	PM_SBL_WRITE,	0,		0},	// 4
   { 0,		0x3F,	0x5940,	PM_SBL_WRITE,	0,		0},	// 5
   { 0,		0xA5,	0x59D0,	PM_SBL_WRITE,	0,		0},	// 6
   { 0,		0x00,	0x5941,	PM_SBL_WRITE,	0,		0},	// 7
   { 0,		0xA5,	0x59D0,	PM_SBL_WRITE,	0,		0},	// 8
   { 0,		0x00,	0x5942,	PM_SBL_WRITE,	0,		0},	// 9
   { 0,		0xA5,	0x59D0,	PM_SBL_WRITE,	0,		0},	// 10
   { 0,		0x01,	0x5943,	PM_SBL_WRITE,	0,		0},	// 11
   { 0,		0xAA,	0x5A58,	PM_SBL_WRITE,	0,		0},	// 12
   { 0,		0x0F,	0x5A59,	PM_SBL_WRITE,	0,		0},	// 13
   { 0,		0x00,	0x5A5A,	PM_SBL_WRITE,	0,		0},	// 14
   { 0,		0x00,	0x5A5B,	PM_SBL_WRITE,	0,		0},	// 15
   { 0,		0xFF,	0x5A5C,	PM_SBL_WRITE,	0,		0},	// 16
   { 0,		0x03,	0x2845,	PM_SBL_WRITE,	0,		0},	// 17
   { 0,		0x00,	0x2846,	PM_SBL_WRITE,	0,		0},	// 18
   { 0,		0x45,	0x6044,	PM_SBL_WRITE,	0,		0},	// 19
   { 0,		0x80,	0x6046,	PM_SBL_WRITE,	0,		0},	// 20
   { 0,		0x80,	0x5A46,	PM_SBL_WRITE,	0,		0},	// 21
   { 0,		0x41,	0x5A48,	PM_SBL_WRITE,	0,		0},	// 22
   { 0,		0x03,	0x5444,	PM_SBL_WRITE,	0,		0},	// 23
   { 0,		0x03,	0x5544,	PM_SBL_WRITE,	0,		0},	// 24
   { 0,		0x03,	0x5644,	PM_SBL_WRITE,	0,		0},	// 25
   { 1,		0xA5,	0x44D0,	PM_SBL_WRITE,	0,		0},	// 26
   { 1,		0x01,	0x44DA,	PM_SBL_WRITE,	0,		0},	// 27
   { 0,		0xE2,	0x505E,	PM_SBL_WRITE,	0,		0},	// 28
   { 0,		0xA5,	0x31D0,	PM_SBL_WRITE,	0,		0},	// 29
   { 0,		0x03,	0x31DA,	PM_SBL_WRITE,	0,		0},	// 30

   // MODE - LDOs_CONFIG: 4
   //sid  data    register  reg op      cond start    cond end
   { 1,		0x00,	0x4A48,	PM_SBL_WRITE,	0,		0},	// 1
   { 1,		0x00,	0x5248,	PM_SBL_WRITE,	0,		0},	// 2
   { 1,		0x00,	0x4748,	PM_SBL_WRITE,	0,		0},	// 3
   { 1,		0x80,	0x4746,	PM_SBL_WRITE,	0,		0},	// 4
   { 1,		0x10,	0x4745,	PM_SBL_WRITE,	0,		0},	// 5
   { 1,		0xA5,	0x47D0,	PM_SBL_WRITE,	0,		0},	// 6
   { 1,		0x03,	0x47DA,	PM_SBL_WRITE,	0,		0},	// 7
   { 1,		0xD0,	0x4052,	PM_SBL_WRITE,	0,		0},	// 8
   { 1,		0xD0,	0x5A52,	PM_SBL_WRITE,	0,		0},	// 9
   { 1,		0xD0,	0x4352,	PM_SBL_WRITE,	0,		0},	// 10
   { 1,		0xD0,	0x4A52,	PM_SBL_WRITE,	0,		0},	// 11
   { 1,		0xCB,	0x1441,	PM_SBL_WRITE,	0,		0},	// 12
   { 1,		0x0D,	0x4041,	PM_SBL_WRITE,	0,		0},	// 13
   { 1,		0x0D,	0x4A41,	PM_SBL_WRITE,	0,		0},	// 14

   // MODE - FTS_GANGING_PMA8084: 5
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x15D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x80,   0x15C1,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0xA5,   0x18D0,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x80,   0x18C1,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0xA5,   0x2AD0,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x80,   0x2AC1,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0xA5,   0x2DD0,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x80,   0x2DC1,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0xA5,   0x30D0,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x80,   0x30C1,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0xA5,   0x33D0,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x80,   0x33C1,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0xA5,   0x36D0,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x80,   0x36C1,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0xA5,   0x2CD0,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0x80,   0x2CC1,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0xA5,   0x2FD0,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0x80,   0x2FC1,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0xA5,   0x32D0,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0x80,   0x32C1,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0xA5,   0x35D0,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0x80,   0x35C1,   PM_SBL_WRITE,   0,      0},   // 22

   // MODE - S6S7_GANGING: 6
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x24D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x80,   0x24C1,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x00,   0x24D0,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0xA5,   0x27D0,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x80,   0x27C1,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0xA5,   0x26D0,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x80,   0x26C1,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x80,   0x23E8,   PM_SBL_WRITE,   0,      0},   // 9

   // MODE - FTS_BLOCK_GLOBAL_RESET: 7
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x00,   0x15D9,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x00,   0x16D9,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x00,   0x14D9,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x00,   0x18D9,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x00,   0x19D9,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x00,   0x36D9,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x00,   0x37D9,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x00,   0x35D9,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x00,   0x17D9,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x00,   0x24D9,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x00,   0x25D9,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0x00,   0x27D9,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0x00,   0x28D9,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0x00,   0x26D9,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0x00,   0x23D9,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0x00,   0x2AD9,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0x00,   0x2BD9,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0x00,   0x2DD9,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0x00,   0x2ED9,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0x00,   0x2CD9,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0x00,   0x30D9,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0x00,   0x31D9,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0x00,   0x2FD9,   PM_SBL_WRITE,   0,      0},   // 27
   { 1,      0x00,   0x33D9,   PM_SBL_WRITE,   0,      0},   // 28
   { 1,      0x00,   0x34D9,   PM_SBL_WRITE,   0,      0},   // 29
   { 1,      0x00,   0x32D9,   PM_SBL_WRITE,   0,      0},   // 30
   { 1,      0x00,   0x29D9,   PM_SBL_WRITE,   0,      0},   // 31

   // MODE - FTS_RESET_SETTINGS: 8
   //sid  data    register  reg op      cond start    cond end
   { 1,		0xA5,	0x14D0,	PM_SBL_WRITE,	0,		0},	// 1
   { 1,		0x01,	0x15DA,	PM_SBL_WRITE,	0,		0},	// 2
   { 1,		0x01,	0x16DA,	PM_SBL_WRITE,	0,		0},	// 3
   { 1,		0x01,	0x14DA,	PM_SBL_WRITE,	0,		0},	// 4
   { 1,		0xA5,	0x17D0,	PM_SBL_WRITE,	0,		0},	// 5
   { 1,		0x01,	0x18DA,	PM_SBL_WRITE,	0,		0},	// 6
   { 1,		0x01,	0x19DA,	PM_SBL_WRITE,	0,		0},	// 7
   { 1,		0x01,	0x36DA,	PM_SBL_WRITE,	0,		0},	// 8
   { 1,		0x01,	0x37DA,	PM_SBL_WRITE,	0,		0},	// 9
   { 1,		0x01,	0x35DA,	PM_SBL_WRITE,	0,		0},	// 10
   { 1,		0x01,	0x17DA,	PM_SBL_WRITE,	0,		0},	// 11
   { 1,		0xA5,	0x23D0,	PM_SBL_WRITE,	0,		0},	// 12
   { 1,		0x01,	0x24DA,	PM_SBL_WRITE,	0,		0},	// 13
   { 1,		0x01,	0x25DA,	PM_SBL_WRITE,	0,		0},	// 14
   { 1,		0x01,	0x27DA,	PM_SBL_WRITE,	0,		0},	// 15
   { 1,		0x01,	0x28DA,	PM_SBL_WRITE,	0,		0},	// 16
   { 1,		0x01,	0x26DA,	PM_SBL_WRITE,	0,		0},	// 17
   { 1,		0x01,	0x23DA,	PM_SBL_WRITE,	0,		0},	// 18
   { 1,		0xA5,	0x29D0,	PM_SBL_WRITE,	0,		0},	// 19
   { 1,		0x01,	0x2ADA,	PM_SBL_WRITE,	0,		0},	// 20
   { 1,		0x01,	0x2BDA,	PM_SBL_WRITE,	0,		0},	// 21
   { 1,		0x01,	0x2DDA,	PM_SBL_WRITE,	0,		0},	// 22
   { 1,		0x01,	0x2EDA,	PM_SBL_WRITE,	0,		0},	// 23
   { 1,		0x01,	0x2CDA,	PM_SBL_WRITE,	0,		0},	// 24
   { 1,		0x01,	0x30DA,	PM_SBL_WRITE,	0,		0},	// 25
   { 1,		0x01,	0x31DA,	PM_SBL_WRITE,	0,		0},	// 26
   { 1,		0x01,	0x2FDA,	PM_SBL_WRITE,	0,		0},	// 27
   { 1,		0x01,	0x33DA,	PM_SBL_WRITE,	0,		0},	// 28
   { 1,		0x01,	0x34DA,	PM_SBL_WRITE,	0,		0},	// 29
   { 1,		0x01,	0x32DA,	PM_SBL_WRITE,	0,		0},	// 30
   { 1,		0x01,	0x29DA,	PM_SBL_WRITE,	0,		0},	// 31

   // MODE - BUCK_STEPPER: 9
   //sid  data    register  reg op      cond start    cond end
   { 1,      0x82,   0x1A60,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x81,   0x1D60,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x81,   0x2060,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x83,   0x1A61,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x83,   0x1D61,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x83,   0x2061,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x83,   0x1461,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x83,   0x1761,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x83,   0x2361,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x83,   0x2661,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x83,   0x2961,   PM_SBL_WRITE,   0,      0},   // 11

   // MODE - BUCK_UL_LL_AND_PD_CONFIG: 10
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x1AD0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x5A,   0x1A69,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0xA5,   0x1AD0,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x46,   0x1A6B,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0xA5,   0x1AD0,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0xC0,   0x1A68,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0xA5,   0x20D0,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x1C,   0x2069,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0xA5,   0x20D0,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x0E,   0x206B,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0xA5,   0x20D0,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0xC0,   0x2068,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0xA5,   0x1DD0,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x0C,   0x1D69,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0xA5,   0x1DD0,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0x08,   0x1D6B,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0xA5,   0x1DD0,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0xC0,   0x1D68,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0xE6,   0x1469,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0xBF,   0x146B,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0xC0,   0x1468,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0xD2,   0x1769,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0xD2,   0x3569,   PM_SBL_WRITE,   0,      0},   // 27
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 28
   { 1,      0xA6,   0x176B,   PM_SBL_WRITE,   0,      0},   // 29
   { 1,      0xA6,   0x356B,   PM_SBL_WRITE,   0,      0},   // 30
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 31
   { 1,      0x80,   0x1768,   PM_SBL_WRITE,   0,      0},   // 32
   { 1,      0x80,   0x3568,   PM_SBL_WRITE,   0,      0},   // 33
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 34
   { 1,      0xD2,   0x2369,   PM_SBL_WRITE,   0,      0},   // 35
   { 1,      0xD2,   0x2669,   PM_SBL_WRITE,   0,      0},   // 36
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 37
   { 1,      0xA6,   0x236B,   PM_SBL_WRITE,   0,      0},   // 38
   { 1,      0xA6,   0x266B,   PM_SBL_WRITE,   0,      0},   // 39
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 40
   { 1,      0x80,   0x2368,   PM_SBL_WRITE,   0,      0},   // 41
   { 1,      0x80,   0x2668,   PM_SBL_WRITE,   0,      0},   // 42
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 43
   { 1,      0xE7,   0x2969,   PM_SBL_WRITE,   0,      0},   // 44
   { 1,      0xE7,   0x2C69,   PM_SBL_WRITE,   0,      0},   // 45
   { 1,      0xE7,   0x2F69,   PM_SBL_WRITE,   0,      0},   // 46
   { 1,      0xE7,   0x3269,   PM_SBL_WRITE,   0,      0},   // 47
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 48
   { 1,      0x53,   0x296B,   PM_SBL_WRITE,   0,      0},   // 49
   { 1,      0x53,   0x2C6B,   PM_SBL_WRITE,   0,      0},   // 50
   { 1,      0x53,   0x2F6B,   PM_SBL_WRITE,   0,      0},   // 51
   { 1,      0x4B,   0x326B,   PM_SBL_WRITE,   0,      0},   // 52
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 53
   { 1,      0xC0,   0x2968,   PM_SBL_WRITE,   0,      0},   // 54
   { 1,      0xC0,   0x2C68,   PM_SBL_WRITE,   0,      0},   // 55
   { 1,      0xC0,   0x2F68,   PM_SBL_WRITE,   0,      0},   // 56
   { 1,      0xC0,   0x3268,   PM_SBL_WRITE,   0,      0},   // 57

   // MODE - S3_HF_BUCK_FREQ_PMA8084: 12
   //sid  data    register  reg op      cond start    cond end
   { 1,      0x80,   0x1A45,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x4A,   0x1A41,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0xA5,   0x1CD0,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x06,   0x1C51,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0xA5,   0x1AD0,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x05,   0x1C50,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0xB4,   0x1B4A,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x83,   0x1B4B,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x04,   0x1A51,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x06,   0x1A52,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x02,   0x1A53,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x01,   0x1A56,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x15,   0x1A44,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x0D,   0x1A5B,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0x2F,   0x1A5A,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0xAA,   0x1A5D,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0x02,   0x1A5E,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0x30,   0x1B72,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0x00,   0x1A55,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0x0F,   0x1B75,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0x90,   0x1A62,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0x88,   0x1A59,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0x00,   0x1B79,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0x35,   0x1A63,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0xA5,   0x1AD0,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0x01,   0x1ADA,   PM_SBL_WRITE,   0,      0},   // 27
   { 1,      0xA5,   0x1BD0,   PM_SBL_WRITE,   0,      0},   // 28
   { 1,      0x01,   0x1BDA,   PM_SBL_WRITE,   0,      0},   // 29
   { 1,      0xA5,   0x1CD0,   PM_SBL_WRITE,   0,      0},   // 30
   { 1,      0x01,   0x1CDA,   PM_SBL_WRITE,   0,      0},   // 31
   { 1,      0xA5,   0x1AD0,   PM_SBL_WRITE,   0,      0},   // 32
   { 1,      0x88,   0x1A6C,   PM_SBL_WRITE,   0,      0},   // 33

   // MODE - S5_HF_BUCK_FREQ_PMA8084: 13
   //sid  data    register  reg op      cond start    cond end
   { 1,      0x80,   0x2045,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x01,   0x2040,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x18,   0x2041,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0xA5,   0x22D0,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x0B,   0x2250,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x03,   0x2051,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x07,   0x2052,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x03,   0x2053,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x03,   0x2056,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0xB4,   0x214A,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x83,   0x214B,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x44,   0x2044,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x0C,   0x205B,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x67,   0x205A,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0x0F,   0x205E,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0xA8,   0x205D,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0x30,   0x2172,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0x01,   0x2055,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0x0F,   0x2175,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0xC8,   0x2062,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0x88,   0x2059,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0x00,   0x2179,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0xA5,   0x20D0,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0x01,   0x20DA,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0xA5,   0x21D0,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0x01,   0x21DA,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0xA5,   0x22D0,   PM_SBL_WRITE,   0,      0},   // 27
   { 1,      0x01,   0x22DA,   PM_SBL_WRITE,   0,      0},   // 28
   { 1,      0xA5,   0x20D0,   PM_SBL_WRITE,   0,      0},   // 29
   { 1,      0x88,   0x206C,   PM_SBL_WRITE,   0,      0},   // 30

   // MODE - S4_HF_BUCK_FREQ_PMA8084: 14
   //sid  data    register  reg op      cond start    cond end
   { 1,      0x80,   0x1D45,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0xA5,   0x1FD0,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x0B,   0x1F50,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x03,   0x1D51,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x07,   0x1D52,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x02,   0x1D53,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x03,   0x1D56,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0xB4,   0x1E4A,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x84,   0x1E4B,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x85,   0x1D44,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x0C,   0x1D5B,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x67,   0x1D5A,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x0A,   0x1D5E,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0xBC,   0x1D5D,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0x30,   0x1E72,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0x01,   0x1D55,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0x0F,   0x1E75,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0xD0,   0x1D62,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0x88,   0x1D59,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0x00,   0x1E79,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0xA5,   0x1DD0,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0x01,   0x1DDA,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0xA5,   0x1ED0,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0x01,   0x1EDA,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0xA5,   0x1FD0,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0x01,   0x1FDA,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0xA5,   0x1DD0,   PM_SBL_WRITE,   0,      0},   // 27
   { 1,      0x88,   0x1D6C,   PM_SBL_WRITE,   0,      0},   // 28

   // MODE - S1_FTS_CONFIG_PMA8084: 15
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x02,   0x1651,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x05,   0x1450,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x05,   0x1560,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x11,   0x1561,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x00,   0x15F2,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x00,   0x1464,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x1F,   0x1570,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0x21,   0x1462,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0x02,   0x1463,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0x06,   0x146F,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0x03,   0x1455,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0x67,   0x1456,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0x8C,   0x1572,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0x80,   0x1445,   PM_SBL_WRITE,   0,      0},   // 27

   // MODE - S1_FTS_PID4X: 16
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x98,   0x1574,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0xD5,   0x1575,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x06,   0x1576,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x04,   0x1577,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0xBC,   0x1578,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x06,   0x1579,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x00,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 8

   // MODE - S6S7_FTS_CONFIG_PMA8084: 17
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x07,   0x2551,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x0F,   0x2851,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x03,   0x2350,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x07,   0x2460,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x07,   0x2760,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x11,   0x2461,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x11,   0x2761,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x00,   0x24F2,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x00,   0x27F2,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x00,   0x2364,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0x1F,   0x2470,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0x1F,   0x2770,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0x41,   0x2362,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0x04,   0x2363,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0x06,   0x236F,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0x03,   0x2355,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0x67,   0x2356,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 27
   { 1,      0x8C,   0x2472,   PM_SBL_WRITE,   0,      0},   // 28
   { 1,      0x8C,   0x2772,   PM_SBL_WRITE,   0,      0},   // 29
   { 1,      0x00,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 30

   // MODE - S6_FTS_PID4X: 18
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x98,   0x2474,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0xD5,   0x2475,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x06,   0x2476,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x04,   0x2477,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0xBC,   0x2478,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x06,   0x2479,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x00,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 8

   // MODE - S7_FTS_PID4X: 19
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0xA5,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x98,   0x2774,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0xD5,   0x2775,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x06,   0x2776,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x04,   0x2777,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0xBC,   0x2778,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x06,   0x2779,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x00,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x00,   0x23D0,   PM_SBL_WRITE,   0,      0},   // 10

   // MODE - S2_FTS_CONFIG_PMA8084: 20
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x04,   0x1951,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x0C,   0x3751,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x03,   0x1750,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x07,   0x1860,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x07,   0x3660,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x11,   0x1861,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x11,   0x3661,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x00,   0x18F2,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x00,   0x36F2,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x00,   0x1764,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0x41,   0x1762,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0x1F,   0x1870,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0x1F,   0x3670,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0x04,   0x1763,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0x06,   0x176F,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0x03,   0x1755,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0x67,   0x1756,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0x8C,   0x1872,   PM_SBL_WRITE,   0,      0},   // 27
   { 1,      0x8C,   0x3672,   PM_SBL_WRITE,   0,      0},   // 28

   // MODE - S212_FTS_PID4X: 21
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x98,   0x1874,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x98,   0x3674,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0xD5,   0x1875,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0xD5,   0x3675,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x06,   0x1876,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x06,   0x3676,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x04,   0x3677,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x04,   0x1877,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0xBC,   0x1878,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0xBC,   0x3678,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x06,   0x1879,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x06,   0x3679,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x00,   0x17D0,   PM_SBL_WRITE,   0,      0},   // 14

   // MODE - S891011_FTS_CONFIG_PMA8084: 22
   //sid  data    register  reg op      cond start    cond end
   { 1,      0x00,   0x2954,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x01,   0x2B51,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x09,   0x2E51,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x05,   0x3151,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x0D,   0x3451,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x03,   0x2950,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0xD2,   0x2941,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x1F,   0x2A70,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x1F,   0x2D70,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x1F,   0x3070,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x1F,   0x3370,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x00,   0x2964,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0x41,   0x2962,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0x04,   0x2963,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0x14,   0x2963,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0x06,   0x296F,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0x02,   0x296F,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0x03,   0x2955,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0x67,   0x2956,   PM_SBL_WRITE,   0,      0},   // 26
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 27
   { 1,      0x8C,   0x2A72,   PM_SBL_WRITE,   0,      0},   // 28
   { 1,      0x8C,   0x2D72,   PM_SBL_WRITE,   0,      0},   // 29
   { 1,      0x8C,   0x3072,   PM_SBL_WRITE,   0,      0},   // 30
   { 1,      0x8C,   0x3372,   PM_SBL_WRITE,   0,      0},   // 31
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 32
   { 1,      0x01,   0x2A61,   PM_SBL_WRITE,   0,      0},   // 33
   { 1,      0x01,   0x2D61,   PM_SBL_WRITE,   0,      0},   // 34
   { 1,      0x01,   0x3061,   PM_SBL_WRITE,   0,      0},   // 35
   { 1,      0x01,   0x3361,   PM_SBL_WRITE,   0,      0},   // 36
   { 1,      0x03,   0x2AF2,   PM_SBL_WRITE,   0,      0},   // 37
   { 1,      0x03,   0x2DF2,   PM_SBL_WRITE,   0,      0},   // 38
   { 1,      0x03,   0x30F2,   PM_SBL_WRITE,   0,      0},   // 39
   { 1,      0x03,   0x33F2,   PM_SBL_WRITE,   0,      0},   // 40
   { 1,      0x00,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 41

   // MODE - S891011_FTS_PID4X: 23
   //sid  data    register  reg op      cond start    cond end
   { 1,      0xA5,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x98,   0x2A74,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x98,   0x2D74,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x98,   0x3074,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x98,   0x3374,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0xD5,   0x2A75,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0xD5,   0x2D75,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0xD5,   0x3075,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0xD5,   0x3375,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x06,   0x2A76,   PM_SBL_WRITE,   0,      0},   // 10
   { 1,      0x06,   0x2D76,   PM_SBL_WRITE,   0,      0},   // 11
   { 1,      0x06,   0x3076,   PM_SBL_WRITE,   0,      0},   // 12
   { 1,      0x06,   0x3376,   PM_SBL_WRITE,   0,      0},   // 13
   { 1,      0x04,   0x2A77,   PM_SBL_WRITE,   0,      0},   // 14
   { 1,      0x04,   0x2D77,   PM_SBL_WRITE,   0,      0},   // 15
   { 1,      0x04,   0x3077,   PM_SBL_WRITE,   0,      0},   // 16
   { 1,      0x04,   0x3377,   PM_SBL_WRITE,   0,      0},   // 17
   { 1,      0xBC,   0x2A78,   PM_SBL_WRITE,   0,      0},   // 18
   { 1,      0xBC,   0x2D78,   PM_SBL_WRITE,   0,      0},   // 19
   { 1,      0xBC,   0x3078,   PM_SBL_WRITE,   0,      0},   // 20
   { 1,      0xBC,   0x3378,   PM_SBL_WRITE,   0,      0},   // 21
   { 1,      0x06,   0x2A79,   PM_SBL_WRITE,   0,      0},   // 22
   { 1,      0x06,   0x2D79,   PM_SBL_WRITE,   0,      0},   // 23
   { 1,      0x06,   0x3079,   PM_SBL_WRITE,   0,      0},   // 24
   { 1,      0x06,   0x3379,   PM_SBL_WRITE,   0,      0},   // 25
   { 1,      0x00,   0x29D0,   PM_SBL_WRITE,   0,      0},   // 26

   // MODE - RESET_PMA8084: 24
   //sid  data    register  reg op      cond start    cond end
   { 0,      0x04,   0x0875,   PM_SBL_WRITE,   0,      0},   // 1
   { 0,      0x00,   0x085B,   PM_SBL_WRITE,   0,      0},   // 2
   { 0,      0x00,   0x0843,   PM_SBL_WRITE,   0,      0},   // 3
   { 0,      0x00,   0x0847,   PM_SBL_WRITE,   0,      0},   // 4
   { 0,      0x00,   0x084B,   PM_SBL_WRITE,   0,      0},   // 5
   { 0,      0x00,   0x0863,   PM_SBL_WRITE,   0,      0},   // 6
   { 0,      0x00,   0x0867,   PM_SBL_WRITE,   0,      0},   // 7
   { 0,      0x01,   0x085A,   PM_SBL_WRITE,   0,      0},   // 9
   { 0,      0x80,   0x085B,   PM_SBL_WRITE,   0,      0},   // 10
   { 0,      0x01,   0x0844,   PM_SBL_WRITE,   0,      0},   // 11
   { 0,      0x07,   0x0845,   PM_SBL_WRITE,   0,      0},   // 12
   { 0,      0x01,   0x0846,   PM_SBL_WRITE,   0,      0},   // 13
   { 0,      0x80,   0x0847,   PM_SBL_WRITE,   0,      0},   // 14
   { 0,      0x01,   0x0840,   PM_SBL_WRITE,   0,      0},   // 15
   { 0,      0x01,   0x0841,   PM_SBL_WRITE,   0,      0},   // 16
   { 0,      0x04,   0x0842,   PM_SBL_WRITE,   0,      0},   // 17
   { 0,      0x0C,   0x0848,   PM_SBL_WRITE,   0,      0},   // 19
   { 0,      0x06,   0x0849,   PM_SBL_WRITE,   0,      0},   // 20
   { 0,      0x07,   0x084A,   PM_SBL_WRITE,   0,      0},   // 21
   { 0,      0x80,   0x084B,   PM_SBL_WRITE,   0,      0},   // 22
   { 0,      0x00,   0x0862,   PM_SBL_WRITE,   0,      0},   // 23
   { 0,      0x80,   0x0863,   PM_SBL_WRITE,   0,      0},   // 24
   { 0,      0x08,   0x0866,   PM_SBL_WRITE,   0,      0},   // 25
   { 0,      0x80,   0x0867,   PM_SBL_WRITE,   0,      0},   // 26

   // MODE - PBS_CONFIG_PMA8084: 25
   //sid  data    register  reg op      cond start    cond end
   { 0,      0xA5,   0x70D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 0,      0x00,   0x70DA,   PM_SBL_WRITE,   0,      0},   // 2
   { 0,      0x80,   0x7040,   PM_SBL_WRITE,   0,      0},   // 3
   { 0,      0xC0,   0x7041,   PM_SBL_WRITE,   0,      0},   // 4
   { 0,      0x00,   0x7042,   PM_SBL_WRITE,   0,      0},   // 5
   { 0,      0x04,   0x7043,   PM_SBL_WRITE,   0,      0},   // 631
};


pm_sbl_seq_type
pm_sbl_cvr_seq2 [ ] =
{
   { 0,      0x00,   0x7040,   PM_SBL_WRITE,   0,      0},   // 9
   { 0,      0x00,   0x7041,   PM_SBL_WRITE,   0,      0},   // 10
   { 0,      0x00,   0x7042,   PM_SBL_WRITE,   0,      0},   // 11
   { 0,      0x00,   0x7043,   PM_SBL_WRITE,   0,      0},   // 12
   { 0,      0x04,   0x7059,   PM_SBL_WRITE,   0,      0},   // 13
   { 0,      0x04,   0x7058,   PM_SBL_WRITE,   0,      0},   // 14
   { 0,      0x04,   0x7075,   PM_SBL_WRITE,   0,      0},   // 15
   { 0,      0x00,   0x7074,   PM_SBL_WRITE,   0,      0},   // 16
   { 0,      0x04,   0x7089,   PM_SBL_WRITE,   0,      0},   // 20
   { 0,      0x08,   0x7088,   PM_SBL_WRITE,   0,      0},   // 21
   { 0,      0x80,   0x7F46,   PM_SBL_WRITE,   0,      0},   // 22
   { 0,      0x04,   0x7085,   PM_SBL_WRITE,   0,      0},   // 23
   { 0,      0x0C,   0x7084,   PM_SBL_WRITE,   0,      0},   // 24
   { 0,      0x80,   0x7E46,   PM_SBL_WRITE,   0,      0},   // 25
   { 0,      0x01,   0x7F42,   PM_SBL_WRITE,   0,      0},   // 26

   // MODE - AUTO_MODE: 26
   //sid  data    register  reg op      cond start    cond end
   { 1,      0x40,   0x1A45,   PM_SBL_WRITE,   0,      0},   // 1
   { 1,      0x80,   0x1D45,   PM_SBL_WRITE,   0,      0},   // 2
   { 1,      0x40,   0x2045,   PM_SBL_WRITE,   0,      0},   // 3
   { 1,      0x80,   0x1445,   PM_SBL_WRITE,   0,      0},   // 4
   { 1,      0x80,   0x1745,   PM_SBL_WRITE,   0,      0},   // 5
   { 1,      0x80,   0x2345,   PM_SBL_WRITE,   0,      0},   // 6
   { 1,      0x80,   0x2945,   PM_SBL_WRITE,   0,      0},   // 7
   { 1,      0x01,   0x1754,   PM_SBL_WRITE,   0,      0},   // 8
   { 1,      0x01,   0x2354,   PM_SBL_WRITE,   0,      0},   // 9
   { 1,      0x03,   0x2954,   PM_SBL_WRITE,   0,      0},   // 10

   // MODE - USB_CONFIG: 27
   //sid  data    register  reg op      cond start    cond end
   { 0,      0xC0,   0x0946,   PM_SBL_WRITE,   0,      0},   // 1

   // MODE - INTERRUPT_PMA8084: 28
   //sid  data    register  reg op      cond start    cond end
   { 0,      0x00,   0x0546,   PM_SBL_WRITE,   0,      0},   // 1
   { 0,      0x80,   0x0546,   PM_SBL_WRITE,   0,      0},   // 2

   // MODE - WATCHDOG_DIS_PMA8084: 29
   //sid  data    register  reg op      cond start    cond end
   { 0,      0x01,   0x0858,   PM_SBL_WRITE,   0,      0},   // 1
   { 0,      0x00,   0x0857,   PM_SBL_WRITE,   0,      0},   // 2

   // MODE - INIT_PM2433: 30
   //sid  data    register  reg op      cond start    cond end
   { 15,      0xA5,   0x15D0,   PM_SBL_WRITE,   0,      0},   // 1
   { 14,      0x02,   0x0640,   PM_SBL_WRITE,   0,      0},   // 3
   { 14,      0x00,   0x2440,   PM_SBL_WRITE,   0,      0},   // 4
   { 10,      0x01,   0x088D,   PM_SBL_WRITE,   0,      0},   // 5
   { 15,      0x82,   0x1461,   PM_SBL_WRITE,   0,      0},   // 6
   { 15,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 7
   { 15,      0xD7,   0x1469,   PM_SBL_WRITE,   0,      0},   // 8
   { 15,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 9
   { 15,      0x80,   0x1468,   PM_SBL_WRITE,   0,      0},   // 10
   { 15,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 11
   { 15,      0x00,   0x147E,   PM_SBL_WRITE,   0,      0},   // 12
   { 15,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 13
   { 15,      0x00,   0x147F,   PM_SBL_WRITE,   0,      0},   // 14
   { 15,      0xA5,   0x15D0,   PM_SBL_WRITE,   0,      0},   // 15
   { 15,      0x03,   0x15DA,   PM_SBL_WRITE,   0,      0},   // 16
   { 15,      0xA5,   0x14D0,   PM_SBL_WRITE,   0,      0},   // 17
   { 15,      0xD0,   0x1479,   PM_SBL_WRITE,   0,      0},   // 18
   { 11,      0x12,   0x1570,   PM_SBL_WRITE,   0,      0},   // 19
   { 14,      0x00,   0x2D51,   PM_SBL_WRITE,   0,      0},   // 20
   { 14,      0x02,   0x3B51,   PM_SBL_WRITE,   0,      0},   // 21
   { 15,      0xA5,   0x15D0,   PM_SBL_WRITE,   0,      0},   // 22
   { 15,      0x1C,   0x15E2,   PM_SBL_WRITE,   0,      0},   // 23
   { 14,      0x00,   0x0546,   PM_SBL_WRITE,   0,      0},   // 24
   { 14,      0x80,   0x0546,   PM_SBL_WRITE,   0,      0},   // 25

   // MODE - GPIO_CONFIG: 31
   //sid  data    register  reg op      cond start    cond end
   { 0,		0x03,	0xC045,	PM_SBL_WRITE,	0,		0},	// 1
   { 0,		0xA5,	0xC0D0,	PM_SBL_WRITE,	0,		0},	// 2
   { 0,		0x01,	0xC0DA,	PM_SBL_WRITE,	0,		0},	// 3
   { 0,		0x03,	0xC145,	PM_SBL_WRITE,	0,		0},	// 4
   { 0,		0xA5,	0xC2D0,	PM_SBL_WRITE,	0,		0},	// 5
   { 0,		0x01,	0xC2DA,	PM_SBL_WRITE,	0,		0},	// 6
   { 0,		0xA5,	0xCFD0,	PM_SBL_WRITE,	0,		0},	// 7
   { 0,		0x01,	0xCFDA,	PM_SBL_WRITE,	0,		0},	// 8
   { 0,		0xA5,	0xCFD0,	PM_SBL_WRITE,	0,		0},	// 9
   { 0,		0x01,	0xCFD8,	PM_SBL_WRITE,	0,		0},	// 10
   { 0,		0x02,	0xCF41,	PM_SBL_WRITE,	0,		0},	// 11
   { 0,		0x03,	0xCF45,	PM_SBL_WRITE,	0,		0},	// 12
   { 0,		0x11,	0xCF40,	PM_SBL_WRITE,	0,		0},	// 13
   { 0,		0x80,	0xCF46,	PM_SBL_WRITE,	0,		0},	// 14

   // MODE - GLOBAL_ID_PMA8084: 32
   //sid  data    register  reg op      cond start    cond end
   { 0,      0x01,   0x7E42,   PM_SBL_WRITE,   0,      0},   // 1
};

static pm_pbs_ram_data_type pbs[256] = {
      //data  offset  base_addr  sid
      { 0xD0,   0x04,   0x00,   0x80},   /* W#0   -   OTP Client 9, sleep/wake sequence    */
      { 0x20,   0x04,   0x00,   0x80},   /* W#1   -   OTP Client 2, warm reset    */
      { 0x00,   0x05,   0x00,   0x80},   /* W#2   -   DTEST3/GPIO option to change GIDs of PMF2432    */
      { 0x0C,   0x05,   0x00,   0x80},   /* W#3   -   DTEST2/GPIO option to change GIDs of PMF2432 back to default 0xE/0xF    */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#4   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#5   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#6   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#7   -       */
      { 0x00,   0x46,   0x05,   0x00},   /* W#8   -   disable interrupt    */
      { 0x80,   0x45,   0x14,   0x01},   /* W#9   -   Set S1 for NPM    */
      { 0x80,   0x45,   0x17,   0x01},   /* W#10   -   Set S2 for NPM    */
      { 0x80,   0x45,   0x1A,   0x01},   /* W#11   -   Set S3 for PWM    */
      { 0x02,   0x00,   0x01,   0xC0},   /* W#12   -       */
      { 0x80,   0x45,   0x1D,   0x01},   /* W#13   -   Set S4 for PWM    */
      { 0x02,   0x00,   0x01,   0xC0},   /* W#14   -       */
      { 0x80,   0x45,   0x20,   0x01},   /* W#15   -   Set S5 for PWM    */
      { 0x80,   0x45,   0x23,   0x01},   /* W#16   -   Set S6 for NPM    */
      { 0x80,   0x45,   0x29,   0x01},   /* W#17   -   Set S8 for NPM    */
      { 0x82,   0x60,   0x1A,   0x01},   /* W#18   -   Setup S3 stepper (80 clock cycles of a 19.2MHz clock).    */
      { 0x81,   0x60,   0x1D,   0x01},   /* W#19   -   Setup S4 stepper (40 clock cycles of 19.2MHz clock).    */
      { 0x81,   0x60,   0x20,   0x01},   /* W#20   -   Setup S5 stepper (40 clock cycles of 19.2MHz clock)    */
      { 0xC3,   0x41,   0x14,   0x01},   /* W#21   -   Config S1 to 0.975 (feeds LDO1/LDO11 gang)    */
      { 0x00,   0x41,   0xD2,   0x00},   /* W#22   -   Config GPIO19 for VIN@VDD (for MEM PM2433 EN)    */
      { 0x11,   0x40,   0xD2,   0x00},   /* W#23   -   Enable GPIO19, DigOut    */
      { 0xA0,   0x41,   0x29,   0x01},   /* W#24   -   Config S8 to 0.8V (feeds VDDC_CORE)    */
      { 0xBF,   0x41,   0x17,   0x01},   /* W#25   -   Config S2 to 0.975V (feeds VDDA_DDR423)    */
      { 0xBF,   0x41,   0x23,   0x01},   /* W#26   -   Config S6 to 0.975V (feeds VDDA_DDR510)    */
      { 0x04,   0x41,   0x41,   0x01},   /* W#27   -   Config L2 to 0.8V (feeds VDD_MPM)    */
      { 0x04,   0x41,   0x42,   0x01},   /* W#28   -   Config L3 to 0.8V (feeds VDD_USB_0P8)    */
      { 0x04,   0x40,   0x59,   0x01},   /* W#29   -   Set LDO26 to RANGE4  (0x04)    */
      { 0x1C,   0x41,   0x59,   0x01},   /* W#30   -   Config L26 to 3.15V (feeds VDD_UHV_USB)    */
      { 0x0A,   0x41,   0x40,   0x01},   /* W#31   -   Config L1 to 0.875V (feeds VDD_LV_0P875) *Note: L1/L11 are ganged    */
      { 0x0A,   0x41,   0x4A,   0x01},   /* W#32   -   Config L11 to 0.875V *Note: L1/L11 are ganged    */
      { 0x24,   0x41,   0x43,   0x01},   /* W#33   -   Config L4 to 1.2V (VDDA_HV_1P2)    */
      { 0x3A,   0x41,   0x4B,   0x01},   /* W#34   -   Config L12 to 2.95V (feeds VDDPX_SDC0)    */
      { 0x3A,   0x41,   0x4E,   0x01},   /* W#35   -   Config L15 to 2.95V (feeds VDDPX_SDC1)    */
      { 0x3A,   0x41,   0x4D,   0x01},   /* W#36   -   Config L14 to 2.95V (feeds VDDPX_SDC2)    */
      { 0x3A,   0x41,   0x52,   0x01},   /* W#37   -   Config L19 to 2.95V (VDD_SDC3)    */
      { 0x3A,   0x41,   0x58,   0x01},   /* W#38   -   Config L25 to 2.95V (feeds VDD SD Card 1 & 3)    */
      { 0x00,   0x48,   0x4A,   0x01},   /* W#39   -   Disable pull-down on LDO11 *Note: L1/L11 are ganged    */
      { 0xD0,   0x52,   0x40,   0x01},   /* W#40   -   Disable clamp on LDO1    */
      { 0xD0,   0x52,   0x5A,   0x01},   /* W#41   -   Disable clamp on LDO27    */
      { 0xD0,   0x52,   0x43,   0x01},   /* W#42   -   Disable clamp on LDO4    */
      { 0xD0,   0x52,   0x4A,   0x01},   /* W#43   -   Disable clamp on LDO11    */
      { 0x54,   0x03,   0x01,   0xC0},   /* W#44   -   Wait 26ms    */
      { 0x40,   0x91,   0x08,   0x00},   /* W#45   -   Ack the PON module    */
      { 0xFF,   0xFF,   0xFF,   0xFC},   /* W#46   -   Return    */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#47   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#48   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#49   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#50   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#51   -       */
      { 0x00,   0x8A,   0x08,   0x40},   /* W#52   -   Read AVDD Regulator to determine if we are entering or exiting sleep.    */
      { 0x20,   0x01,   0x20,   0x90},   /* W#53   -   If AVDD_HPM_EN (bit 5) == 1 then execute to sleep sequence    */
      { 0xE8,   0x04,   0x00,   0x80},   /* W#54   -   Else AVDD_HPM_EN == 0 so we are waking, goto wake sequence    */
      { 0x20,   0x8A,   0x08,   0x00},   /* W#55   -   Dummy write: Set AVDD regulator into HPM (note: modify here and below this line for future sleep entry)    */
      { 0xFF,   0xFF,   0xFF,   0xFC},   /* W#56   -   End sequence    */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#57   -       */
      { 0x20,   0x8A,   0x08,   0x00},   /* W#58   -   Set AVDD regulator into HPM (note: modify below this line for future sleep exit)    */
      { 0xFF,   0xFF,   0xFF,   0xFC},   /* W#59   -   Return    */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#60   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#61   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#62   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#63   -       */
      { 0x00,   0x46,   0x06,   0x02},   /* W#64   -   Option to change GID0/1 of PMF2432 to 0/1 which matches SID0/1    */
      { 0x01,   0x47,   0x06,   0x02},   /* W#65   -   Option to change GID0/1 of PMF2432 to 0/1 which matches SID0/1    */
      { 0xFF,   0xFF,   0xFF,   0xFC},   /* W#66   -   Return    */
      { 0x0E,   0x46,   0x06,   0x02},   /* W#67   -   Change the PMF2432 GIDs back to default 0x0E/0x0F (GID0=0x0E)    */
      { 0x0F,   0x47,   0x06,   0x02},   /* W#68   -   Change the PMF2432 GIDs back to default 0x0E/0x0F (GID1=0x0F)    */
      { 0xFF,   0xFF,   0xFF,   0xFC},   /* W#69   -   Return    */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#70   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#71   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#72   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#73   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#74   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#75   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#76   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#77   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#78   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#79   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#80   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#81   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#82   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#83   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#84   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#85   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#86   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#87   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#88   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#89   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#90   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#91   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#92   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#93   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#94   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#95   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#96   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#97   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#98   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#99   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#100   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#101   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#102   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#103   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#104   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#105   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#106   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#107   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#108   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#109   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#110   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#111   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#112   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#113   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#114   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#115   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#116   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#117   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#118   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#119   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#120   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#121   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#122   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#123   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#124   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#125   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#126   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#127   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#128   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#129   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#130   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#131   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#132   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#133   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#134   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#135   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#136   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#137   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#138   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#139   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#140   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#141   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#142   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#143   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#144   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#145   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#146   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#147   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#148   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#149   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#150   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#151   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#152   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#153   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#154   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#155   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#156   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#157   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#158   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#159   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#160   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#161   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#162   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#163   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#164   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#165   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#166   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#167   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#168   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#169   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#170   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#171   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#172   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#173   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#174   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#175   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#176   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#177   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#178   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#179   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#180   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#181   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#182   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#183   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#184   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#185   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#186   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#187   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#188   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#189   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#190   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#191   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#192   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#193   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#194   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#195   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#196   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#197   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#198   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#199   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#200   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#201   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#202   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#203   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#204   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#205   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#206   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#207   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#208   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#209   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#210   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#211   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#212   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#213   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#214   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#215   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#216   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#217   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#218   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#219   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#220   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#221   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#222   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#223   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#224   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#225   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#226   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#227   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#228   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#229   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#230   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#231   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#232   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#233   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#234   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#235   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#236   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#237   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#238   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#239   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#240   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#241   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#242   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#243   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#244   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#245   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#246   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#247   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#248   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#249   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#250   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#251   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#252   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#253   -       */
      { 0xFF,   0xFF,   0xFF,   0xFF},   /* W#254   -       */
      { 0x00,   0x01,   0xFF,   0xFF},   /* W#255   -       */
};

void SpmiMaster_LoadFirmware(uint8_t bid)
{
   uint32_t i;

   // Set config registers
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG0_ADDR( bid ), 0x0202187F );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG1_ADDR( bid ), 0x00027F7B );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG2_ADDR( bid ), 0x000076BF );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG3_ADDR( bid ), 0x0007F8FE );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG4_ADDR( bid ), 0x000FFEFE );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG5_ADDR( bid ), 0x208802AB );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG6_ADDR( bid ), 0x00005512 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG7_ADDR( bid ), 0x03880001 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG8_ADDR( bid ), 0x0000021F );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG9_ADDR( bid ), 0x0007F8FE );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG10_ADDR( bid ), 0x000FFEFE );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG11_ADDR( bid ), 0x00041000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG12_ADDR( bid ), 0x00000000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG13_ADDR( bid ), 0x00000000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG14_ADDR( bid ), 0x00000000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG15_ADDR( bid ), 0x002DC896 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG16_ADDR( bid ), 0x00000009 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG17_ADDR( bid ), 0x001FC3FD );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG18_ADDR( bid ), 0x00080102 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG19_ADDR( bid ), 0x00100000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG20_ADDR( bid ), 0x00000008 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG21_ADDR( bid ), 0x00208800 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG22_ADDR( bid ), 0x0068B800 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG23_ADDR( bid ), 0x00000800 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG24_ADDR( bid ), 0x00483000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG25_ADDR( bid ), 0x00555555 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG26_ADDR( bid ), 0x00397A41 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG27_ADDR( bid ), 0x00000000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG28_ADDR( bid ), 0x00000000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG29_ADDR( bid ), 0x00000000 );
   SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_REG30_ADDR( bid ), 0x00000000 );

   // Load RAM image
   for(i = 0; i < GENI_CFG_RAM_COUNT && i <= SWIO_SPMI_GENI_CFG_RAMn_MAXn( bid ); i++) {
      SPMI_HWIO_OUT( SWIO_SPMI_GENI_CFG_RAMn_ADDR( bid, i ), GENI_CFG_RAM_VALUES[i] );
   }
}

static void writeSpmiData(uint8_t bid, uint16_t channel,
			  uint8_t *data, uint32_t bytesToWrite)
{
    uint32_t i;
    uint32_t tmp = 0;

    for(i = 0; i < sizeof(uint32_t) && bytesToWrite > 0; i++, bytesToWrite--) {
        ((uint8_t*)&tmp)[i] = data[i];
    }

    SPMI_HWIO_OUT( SWIO_PMIC_ARBq_CHNLn_WDATA0_ADDR( bid, spmiPmicArbInfo.owner, channel ), tmp );

    if(bytesToWrite > 0)
    {
        tmp = 0;
        for(i = 0; i < sizeof(uint32_t) && bytesToWrite > 0; i++, bytesToWrite--) {
            ((uint8_t*)&tmp)[i] = data[i + sizeof(uint32_t)];
        }

        SPMI_HWIO_OUT( SWIO_PMIC_ARBq_CHNLn_WDATA1_ADDR( bid, spmiPmicArbInfo.owner, channel ), tmp );
    }
}

static void readSpmiData(uint8_t bid, uint16_t channel,
			 uint8_t *data, uint32_t bytesToRead)
{
    uint32_t i;
    uint32_t spmiData = SPMI_HWIO_IN( SWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR( bid, spmiPmicArbInfo.owner, channel ) );

    for(i = 0; i < sizeof(uint32_t) && bytesToRead > 0; i++, bytesToRead--) {
        data[i] = ((uint8_t *)&spmiData)[i];
    }

    if(bytesToRead > 0)
    {
        spmiData = SPMI_HWIO_IN( SWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR( bid, spmiPmicArbInfo.owner, channel ) );

        for(i = 0; i < sizeof(uint32_t) && bytesToRead > 0; i++, bytesToRead--) {
            data[i + sizeof(uint32_t)] = ((uint8_t*)&spmiData)[i];
        }
    }
}

static Spmi_Result waitForStatusDone(uint8_t bid,
				     bool isObserver, uint16_t channel)
{
    uint32_t status = 0;
    uint32_t timeout = SPMI_TIMEOUT_USEC;
    Spmi_Result result = SPMI_SUCCESS;

    while(status == 0 && timeout-- > 0)
    {

        udelay ( 10 );
        status = isObserver ? SPMI_HWIO_IN( SWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR( bid, spmiPmicArbInfo.owner, channel ) ) :
                              SPMI_HWIO_IN( SWIO_PMIC_ARBq_CHNLn_STATUS_ADDR( bid, spmiPmicArbInfo.owner, channel ) );
    }

    if(status & SWIO_PMIC_ARBq_CHNLn_STATUS_DROPPED_BMSK( bid ))
    {
        result = SPMI_FAILURE_TRANSACTION_DROPPED;
    }
    else if(status & SWIO_PMIC_ARBq_CHNLn_STATUS_DONE_BMSK( bid ))
    {
        if(status & SWIO_PMIC_ARBq_CHNLn_STATUS_FAILURE_BMSK( bid )) {
            result = SPMI_FAILURE_TRANSACTION_FAILED;
        }
        else if(status & SWIO_PMIC_ARBq_CHNLn_STATUS_DENIED_BMSK( bid )) {
            result = SPMI_FAILURE_TRANSACTION_DENIED;
        }
    }
    else if(SPMI_SWIO_IN_FIELD( bid, SWIO_SPMI_GENI_CTRL_ADDR( bid ), SWIO_SPMI_GENI_CTRL_M_GENI_DISABLE )) {
        result = SPMI_FAILURE_BUS_DISABLED;
    }
    else {
        result = SPMI_FAILURE_TRANSACTION_TIMEOUT;
    }

    return result;
}

static inline bool isTransactionDone(uint8_t bid, bool isObserver,
				     uint16_t channel)
{
    if(isObserver) {
        return SPMI_SWIO_IN_FIELD( bid,
                                   SWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR( bid, spmiPmicArbInfo.owner, channel ),
                                   SWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE );
    } else {
        return SPMI_SWIO_IN_FIELD( bid,
                                   SWIO_PMIC_ARBq_CHNLn_STATUS_ADDR( bid, spmiPmicArbInfo.owner, channel ),
                                   SWIO_PMIC_ARBq_CHNLn_STATUS_DONE );
    }
}

static inline void writeCommand(uint8_t bid,
                                bool isObserver,
                                PmicArbCmd cmd,
                                uint16_t channel,
                                Spmi_AccessPriority priority,
                                uint8_t regOffset,
                                uint32_t len)
{
    if(isObserver)
    {
        SPMI_HWIO_OUT( SWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR( bid, spmiPmicArbInfo.owner, channel ),
                      (cmd                      << SWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_SHFT(bid))   |
                      (SPMI_ACCESS_PRIORITY_LOW << SWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_SHFT(bid)) |
                      (regOffset                << SWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_SHFT(bid))  |
                      (len                      << SWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_SHFT(bid)) );
    }
    else
    {
        SPMI_HWIO_OUT( SWIO_PMIC_ARBq_CHNLn_CMD_ADDR( bid, spmiPmicArbInfo.owner, channel ),
                      (cmd       << SWIO_PMIC_ARBq_CHNLn_CMD_OPCODE_SHFT(bid))   |
                      (priority  << SWIO_PMIC_ARBq_CHNLn_CMD_PRIORITY_SHFT(bid)) |
                      (regOffset << SWIO_PMIC_ARBq_CHNLn_CMD_ADDRESS_SHFT(bid))  |
                      (len       << SWIO_PMIC_ARBq_CHNLn_CMD_BYTE_CNT_SHFT(bid)) );
    }
}

//******************************************************************************
// Public API Functions
//******************************************************************************
void pmic_init(uint8_t bid, uint8_t masterId)
{
    int i;

    static unsigned char data[] = { 0xA5, 0x01, 0xA5, 0x01, 0x02, 0x03, 0x11, 0x80 , 0x0A, 0xC3};

    static int reg_addr[] = { 0xCFD0, 0xCFDA, 0xCFD0, 0xCFD8, 0xCF41, 0xCF45, 0xCF40, 0xCF46, 0x1574, 0x1441};

    static uint8_t sid[] = {0, 0, 0, 0, 0, 0, 0, 0, 15, 11};

    // 0. Don't make assumptions - set ser_clk_sel to cc_spmi_ahb_clk for RAM programming
    SPMI_HWIO_OUT_CLEAR( SWIO_SPMI_GENI_CLK_CTRL_ADDR( bid ), SWIO_SPMI_GENI_CLK_CTRL_SER_CLK_SEL_BMSK( bid ) );

    // 1. FW Image download
    SpmiMaster_LoadFirmware( bid );

    // 2. Initiate FORCE-DEFAULT command
    SPMI_HWIO_OUT_SET( SWIO_SPMI_GENI_FORCE_DEFAULT_REG_ADDR( bid ), SWIO_SPMI_GENI_FORCE_DEFAULT_REG_FORCE_DEFAULT_BMSK( bid ) );

    // 3. Switch PROGRAM-RAM clock muxing to serial clock
    SPMI_HWIO_OUT_SET( SWIO_SPMI_GENI_CLK_CTRL_ADDR( bid ), SWIO_SPMI_GENI_CLK_CTRL_SER_CLK_SEL_BMSK( bid ) );

    // 4. Disable all security features (enabled after owner tables are populated)
    SPMI_HWIO_OUT_SET( SWIO_SPMI_SEC_DISABLE_REG_ADDR( bid ), SWIO_SPMI_SEC_DISABLE_REG_DISABLE_SECURITY_BMSK( bid ) );

    // 5: Disable forced High-Z driven to GENI outputs. Set bits SOE0_EN and SOE1_EN of GENI_OUTPUT_CTRL_REG register to 1
    SPMI_HWIO_OUT_SET( SWIO_SPMI_GENI_OUTPUT_CTRL_ADDR( bid ), SWIO_SPMI_GENI_OUTPUT_CTRL_SOE0_EN_BMSK( bid ) |
                                                               SWIO_SPMI_GENI_OUTPUT_CTRL_SOE1_EN_BMSK( bid ) );

    // 6. Configure SPMI_MID_REG register
    SPMI_SWIO_OUT_FIELD( bid, SWIO_SPMI_MID_REG_ADDR(bid), SWIO_SPMI_MID_REG_MID, masterId );

    // 7. Set fields FORCE_MASTER_WRITE_ON_ERROR and ARBITER_ENABLE in SPMI_CFG_REG
    SPMI_HWIO_OUT_SET( SWIO_SPMI_CFG_REG_ADDR( bid ), SWIO_SPMI_CFG_REG_FORCE_MASTER_WRITE_ON_ERROR_BMSK( bid ) );
    SPMI_HWIO_OUT_SET( SWIO_SPMI_CFG_REG_ADDR( bid ), SWIO_SPMI_CFG_REG_ARBITER_ENABLE_BMSK( bid ) );


    // *Not in the HPG* -- Core resets in bypass mode: disable bypass
    SPMI_HWIO_OUT_CLEAR( SWIO_SPMI_CFG_REG_ADDR( bid ), SWIO_SPMI_CFG_REG_ARBITER_BYPASS_BMSK( bid ) );

    // 7a. Set SSC_WINDOW_EN
    SPMI_HWIO_OUT_SET( SWIO_SPMI_CFG_REG_ADDR( bid ), SWIO_SPMI_CFG_REG_SSC_WINDOW_EN_BMSK( bid ) );

    // 8. RPU initialization N/A

    // 9. Mapping Table (radix tree - set later)

    // 10. SPMI_PERIPHm_2OWNER_TABLE_REG (owner table APID2PPID - set later)

    // 11. Set SPMI_CMPR_EN_REG.CMPR_ENABLE (set later when owner table is populated)

    // 12. SPMI_PERIPHm_2OWNER_TABLE_REG (owner table PERIPH2OWNER - set later)

    // 13. Enable global interrupt flag (enabled after owner tables are populated)

    // 14. Change ROM and RAM mux to output RAM Data.
    SPMI_HWIO_OUT_CLEAR( SWIO_SPMI_GENI_PROG_ROM_CTRL_REG_ADDR( bid ), SWIO_SPMI_GENI_PROG_ROM_CTRL_REG_PROG_ROM_EN_BMSK( bid ) );

    // 15. Enabling HW control CGC
    SPMI_HWIO_OUT_CLEAR( SWIO_SPMI_GENI_CGC_CTRL_ADDR( bid ), SWIO_SPMI_GENI_CGC_CTRL_PROG_RAM_SCLK_OFF_BMSK( bid ) );
    SPMI_HWIO_OUT_SET( SWIO_SPMI_GENI_CGC_CTRL_ADDR( bid ),
                       SWIO_SPMI_GENI_CGC_CTRL_PROG_RAM_HCLK_OFF_BMSK( bid ) |
                       SWIO_SPMI_GENI_CGC_CTRL_EXT_CLK_CGC_ON_BMSK( bid ) |
                       SWIO_SPMI_GENI_CGC_CTRL_RX_CLK_CGC_ON_BMSK( bid ) |
                       SWIO_SPMI_GENI_CGC_CTRL_TX_CLK_CGC_ON_BMSK( bid ) |
                       SWIO_SPMI_GENI_CGC_CTRL_SCLK_CGC_ON_BMSK( bid ) |
                       SWIO_SPMI_GENI_CGC_CTRL_DATA_AHB_CLK_CGC_ON_BMSK( bid ) |
                       SWIO_SPMI_GENI_CGC_CTRL_CFG_AHB_WR_CLK_CGC_ON_BMSK( bid ) |
                       SWIO_SPMI_GENI_CGC_CTRL_CFG_AHB_CLK_CGC_ON_BMSK( bid ) );

    // 16. Enable APC rail and configure vdd_mem to 1055mv
    for (i = 0; i < sizeof(data); i++){
        pmic_cmd( PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG, sid[i], reg_addr[i], data[i] );
    }
}

Spmi_Result PmicArb_ExecuteCommand(PmicArbCmd cmd,
                                   Spmi_AccessPriority priority,
                                   uint8_t bid,
                                   uint8_t slaveId,
                                   uint16_t address,
                                   uint8_t *data,
                                   uint32_t dataLen,
                                   uint32_t *bytesTransacted)
{
    uint32_t tmp;
    uint16_t channel = 0;
    bool doRead = false;
    bool doWrite = false;

    if(data == NULL || dataLen == 0) {
        return SPMI_FAILURE_INVALID_BUFFER;
    }

    if(bytesTransacted == NULL) {
        bytesTransacted = &tmp;
    }

    *bytesTransacted = 0;

    SPMI_HWIO_OUT( SWIO_PMIC_ARB_REG_CHNLn_ADDR( bid, channel ),
                    SPMI_SWIO_SET_FIELD_VALUE( bid, slaveId, SWIO_PMIC_ARB_REG_CHNLn_SID ) |
                    SPMI_SWIO_SET_FIELD_VALUE( bid, REG_ADDR_TO_PERIPH_ID(address), SWIO_PMIC_ARB_REG_CHNLn_ADDRESS ));


    switch(cmd)
    {
        case PMIC_ARB_CMD_EXTENDED_REG_READ_LONG:
            doRead = true;
            break;

        case PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG:
            doWrite = true;
            break;

        default:
            return SPMI_FAILURE_COMMAND_NOT_SUPPORTED;
    }

    while(dataLen > 0)
    {
        Spmi_Result result;
	uint32_t len;

        // Check if the Done bit is set. If not, the previous transaction is stuck
        if(!isTransactionDone( bid, doRead, channel )) {
            return SPMI_FAILURE_BUS_BUSY;
        }

        len = dataLen > MAX_TRANSACTION_LEN ? MAX_TRANSACTION_LEN : dataLen;

        if(doWrite) {
            writeSpmiData( bid, channel, data + *bytesTransacted, len );
        }

        // This is the signal to start the transaction
        // len - 1 because value of 0 means 1 byte and increments from there
        writeCommand( bid, doRead, cmd, channel, priority, REG_ADDR_TO_REG_OFFSET( address ) + *bytesTransacted, len - 1 );

        if((result = waitForStatusDone( bid, doRead, channel )) != SPMI_SUCCESS) {
            return result;
        }

        if(doRead) {
            readSpmiData( bid, channel, data + *bytesTransacted, len );
        }

        dataLen -= len;
        *bytesTransacted += len;
    }

    return SPMI_SUCCESS;
}

Spmi_Result pmic_cmd_x(PmicArbCmd cmd, uint8_t slaveId,
		       uint16_t address, uint8_t *data, uint32_t len)
{
   Spmi_Result transmit_result = PmicArb_ExecuteCommand( cmd, SPMI_ACCESS_PRIORITY_LOW, 0, slaveId, address, data, len, NULL );
   return transmit_result;
}

Spmi_Result pmic_cmd(PmicArbCmd cmd, uint8_t slaveId,
                     uint16_t address, uint8_t data)
{
   return pmic_cmd_x(cmd, slaveId, address, &data, 1);
}

void pmic_configure(void)
{
   int i = 0;

   for (i = 0; i < sizeof(pm_sbl_cvr_seq1) / sizeof(pm_sbl_seq_type); i++) {
   pmic_cmd(0,pm_sbl_cvr_seq1[i].sid, pm_sbl_cvr_seq1[i].address, pm_sbl_cvr_seq1[i].data);
   udelay(500);
   }

   for (i = 0; i < sizeof(pbs) / sizeof(pm_pbs_ram_data_type); i++) {
   pmic_cmd_x(0, 0, 0x7048, (uint8_t *)(pbs + i), 4);
   udelay(500);
   }

   for (i = 0; i <  sizeof(pm_sbl_cvr_seq2) / sizeof(pm_sbl_seq_type); i++) {
   pmic_cmd(0, pm_sbl_cvr_seq2[i].sid, pm_sbl_cvr_seq2[i].address, pm_sbl_cvr_seq2[i].data);
   udelay(500);
   }
}

void sys_m_terminate(uint8_t pon_cfg)
{
   pmic_configure();                                                            //send software sequence to configure pmic

   pmic_cmd(PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG, 0, 0xCF40, 0x10);             //shutdown APC rail
   pmic_cmd(PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG, 0, 0x088E, 0x00);             //store some info through resets
   pmic_cmd(PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG, 0, 0x085A, pon_cfg);          //configure reg PON_PS_HOLD_RESET_CTL before toggle PS_HOLD

   HWIO_OUTM(BOOT_PARTITION_SELECT, 0x4, 0);                                    //clear cookie
   HWIO_OUTM(TCSR_BOOT_MISC_DETECT, 0x5, 0);

   HWIO_MPM_PS_HOLD_OUT(0);                                                     //toggle PS_HOLD

   while (1);
}

int do_shutdown(int argc, char *argv[])
{
   printf("\nshutting down\n");
   sys_m_terminate(0x04);
   return 0;
}

int do_reboot(int argc, char *argv[])
{
   printf("\nrebooting\n");
   sys_m_terminate(0x01);
   return 0;
}

int do_pmic(int argc, char *argv[])
{
    int ret = 0;

    if (argc == 2) {
        if (strcmp("init", argv[1]) == 0) {
            pmic_init(0, 0);
            printf("pmic arbiter has been initialized! \n");
        }
        else if (strcmp("mx", argv[1]) == 0) {
            uint8_t data[] = {0};
            pmic_cmd_x(1, 11, 0x1441, data, 1);
            printf("vdd_mem voltage is %dmV\n", (80 + data[0]*5));
        }
        else if (strcmp("pbs", argv[1]) == 0) {
            pmic_configure();
            printf("the software sequence has been sent!\n");
        }
    }
    else if (argc == 3) {
        if (strcmp("mx", argv[1]) == 0) {
           if ((strtoul(argv[2], NULL, 0) >= 600) && (strtoul(argv[2], NULL, 0) <= 1055)) {
               uint8_t data = (strtoul(argv[2], NULL, 0) - 80)/5;
               pmic_cmd(0, 11, 0x1441, data);
           }
           else {
               printf("The voltage to set is out of range\n");
               ret = -1;
           }
        }
    }
    else if (argc == 4) {
        if ('r' == argv[1][0]) {
            uint8_t data[1] = {0};

            pmic_cmd_x(1, strtoul(argv[2], NULL, 0), strtoul(argv[3], NULL, 0), data, 1);
            printf("the number in reg is %#X\n", data[0]);
        }
    }
    else if (argc == 5) {
        uint8_t data = strtoul(argv[4], NULL, 0);

        if ('w' == argv[1][0]) {
            pmic_cmd_x(0, strtoul(argv[2], NULL, 0), strtoul(argv[3], NULL, 0), &data, 1);
        }
    }
    else {
        printf("the number of argument is not correct! \n\n");
        ret = -1;
    }
    return ret;
}

MK_CMD(shutdown, do_shutdown, "print command description/usage",
    " \n"
    "    -bring the system down\n"
);

MK_CMD(reboot, do_reboot, "print command description/usage",
    " \n"
    "    -reboot the system\n"
);

MK_CMD(pmic, do_pmic, "read/write the pmic registers",
    "init\n"
    "    - initialize the pmic module\n"
    "pmic {write | w} {sid} {addr} {data}\n"
    "    - set the register to data...\n"
    "pmic {read | r} {sid} {address}\n"
    "    - read the register...\n"
    "pmic {mx} {voltage}\n"
    "    - configure vdd_mem to the target voltage(mV)...\n"
    "pmic {mx} \n"
    "    - read vdd_mem voltage(mV)...\n"
    "pmic {pbs} \n"
    "    - send  the software sequence to bring pmic in a suitable state...\n"
);
