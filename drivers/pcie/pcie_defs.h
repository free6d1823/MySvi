/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#ifndef __PCIE_DEFS_H__
#define __PCIE_DEFS_H__

#define PCIE_PHY_PER_SS               4
#define PCIE_LANE_PER_PHY             4

#define HOST_BRIDGE_NUMBER            1
#define MAX_PCI_DEVICE_NUMBER         31
#define MAX_PCI_FUNCTION_NUMBER       7
#define MAX_PCI_REG_ADDRESS           0xFFF

#define ECAM_BUS_ADDRESS_SIZE         0x100000
#define ECAM_DEVICE_ADDRESS_SIZE      0x8000
#define ECAM_FUNCTION_ADDRESS_SIZE    0x1000
#define MAX_IATU_VIEWPORTS            8
#define VENDOR_17CB	                  0x17cb
#define DEVICE_PCIE_0400              0x400
#define DEVICE_PCIE_0401              0x401
#define S_CFG_LANENUM_WAIT            0x09
#define S_CFG_LANENUM_ACEPT           0x0A

#define SLOT_POWER_LIMIT_75W          75
#define SLOT_POWER_LIMIT_225W         225

#define PCI_EXPRESS_EXTENDED_CAPABILITY_L1SS_ID                 0x001e
#define PCIE_CAPABILITY_BASE_OFFSET                             0x100
#define EFI_PCI_HOST_BRIDGE_MEM64_DECODE                        2
#define QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION            0x00010000

//declares
typedef enum {
    PCIE_SS_0 = 0,
    PCIE_SS_1,
    PCIE_SS_MAX
} PCIE_SS_t;

typedef enum
{
    LINKMODE_2X8,
    LINKMODE_2X4_1X8,
    LINKMODE_1X8_2X4,
    LINKMODE_2X4_2X4,
    LINKMODE_3X4,
    LINKMODE_1X16,
    LINKMODE_INVALID = 0xffffffff
} PCIE_LINKMODE_t;

typedef enum
{
    LaneConfigure,
    LaneStart
} PCIE_LaneInitCommand_t;

typedef enum {
    TypeIo = 0,
    TypeMem32,
    TypePMem32,
    TypeMem64,
    TypePMem64,
    TypeBus,
    TypeMax
} PCI_RESOURCE_TYPE_t;

typedef struct {
    uint64_t  Base;
    uint64_t  Start;
    uint64_t  End;
} PCI_ROOT_BRIDGE_RESOURCE_CONFIG_t;

typedef struct {
	uint32_t SegmentNumber;
	uint64_t AllocationAttributes;
	PCI_ROOT_BRIDGE_RESOURCE_CONFIG_t Res[TypeMax];
} PCI_ROOT_BRIDGE_RESOURCE_MAP_t;

typedef enum {
    PCIE_OPTION_DISABLE = 0,
    PCIE_OPTION_ENABLE = 1,
    PCIE_OPTION_DEFAULT
} PCIE_OPTION_t;

typedef enum {
    WIDTH_DEFAULT = 0,
    WIDTH_X1 = (1 << 0),
    WIDTH_X2 = (1 << 1),
    WIDTH_X4 = (1 << 2),
    WIDTH_X8 = (1 << 3),
    WIDTH_X16 = (1 << 4),
    WIDTH_X32 = (1 << 5)
} PCIE_WIDTH_t;

typedef enum {
    SPEED_AUTO_NEG = 0,
    SPEED_GEN1 = 1, //2.5GT/s
    SPEED_GEN2 = 2, //5GT/s
    SPEED_GEN3 = 3, //8GT/s
    SPEED_GEN4 = 4, //18GT/s
} PCIE_SPEED_t;

typedef struct {
    uint64_t			Revision;
    uint32_t			SlotId;
    uint32_t			ControllerId;
    uint32_t			PcieSubSystemId;
    PCIE_WIDTH_t		DataWidth;
    PCIE_WIDTH_t		SlotWidth;
    PCIE_SPEED_t		MaxSpeed;
    uint32_t			PowerLimit;
} PCIE_SLOT_INFO_PROT_CONF_t;

typedef union {
    struct {
        uint32_t AttentionButton : 1;
        uint32_t PowerController : 1;
        uint32_t MrlSensor : 1;
        uint32_t AttentionIndicator : 1;
        uint32_t PowerIndicator : 1;
        uint32_t HotPlugSurprise : 1;
        uint32_t HotPlugCapable : 1;
        uint32_t SlotPowerLimitValue : 8;
        uint32_t SlotPowerLimitScale : 2;
        uint32_t ElectromechanicalInterlock : 1;
        uint32_t NoCommandCompleted : 1;
        uint32_t PhysicalSlotNumber : 13;
    } Bits;
    uint32_t   Uint32;
} PCIE_SLOT_CAPABILITY_t;

typedef struct {
    uint8_t NFTS;
    uint8_t NFTSCommon;
    uint8_t L0Entry;
    uint8_t L1Entry;
    uint8_t Gen23Nfts;
    uint8_t L0Exit;
    uint8_t L1Exit;
} PCI_ASPM_PARAM_t;

typedef struct {
    uint32_t ControllerId;
    uint64_t PcieBase;
    uint64_t PcieSize;
    uint64_t ElbiBase;
    uint64_t ParfBase;
    uint64_t GccBase;
    PCI_ROOT_BRIDGE_RESOURCE_MAP_t ResourceMap;
    PCIE_SS_t PcieSubSystem; 
    uint8_t MaxFunctionOnRootBridge;
    PCIE_OPTION_t NoSnoop; 
    PCIE_OPTION_t IdBasedOrdering;
    PCIE_OPTION_t ECRC; 
    PCIE_OPTION_t ComplianceMode;
    uint8_t AspmSupport;
	uint8_t Loopback;
	uint8_t TcVcMap[2];
	PCI_ASPM_PARAM_t AspmConfig;
    uint8_t MaxPayloadSize; 
    uint8_t MaxReadRequestSize; 
    uint16_t TphRequestCap; 
} PCIE_Config_t;

typedef struct {
    uint16_t                                          LaneIndex;
    uint16_t                                          NumLanes;
    PCIE_SLOT_INFO_PROT_CONF_t                        SlotInfoProtocol;
    PCIE_SLOT_CAPABILITY_t                            SlotCapabilitiesProtocol;
} PCIE_SLOT_CONF_t;

#endif //__PCIE_DEFS_H__
