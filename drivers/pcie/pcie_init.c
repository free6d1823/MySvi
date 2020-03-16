/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
//#include <stdlib.h>
#include <asm/io.h>
#include <asm/mach/hal/msmhwiobase.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include <target/pci.h>
//#include "hdts_misc.h"
//#include "hdts_common.h"
#include "target/delay.h"
#define Hdts_waitForMicroSecs(x) udelay(x)

#include "asm/mach/hal/HALclkHWIO.h"
#include "asm/hal/HALhwio.h"
#include "HALTlmm.h"
#include "target/clock.h"
#include "PcieClkGenQdf2400Hwio.h"
#include "hwio_pcie_cc.h"
#include "PciePspQserverCom.h"
#include "PciePspAhb2PhySwman.h"
#include "PciePhyPcsQdf2400Hwio.h"
#include "PciePspLaneQdf2400Hwio.h"
#include "Pcie30DbiElbiHwio.h"
#include "hwio_pcie_parf.h"
#include "pcie_regs.h"
#include "pcie_defs.h"
#include "pcie_init.h"
#include "PcieI2cIo.h"
#include "PcieSlotPortExpander.h"

#include <target/uefi_wrapper.h>
#include <target/cmdline.h>

static uint8_t gFirmwareFirstEnable = 1;
static uint8_t gPcieEyeMonModeEnable = 0;

PCIE_Config_t mPcieConfig[] = {
    {
        .ControllerId = 0,
        .PcieBase = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS,
        .PcieSize = 0x8000000000000000,
        .ElbiBase = PCIE0_PCIE30_ELBI_REG_BASE_PHYS,
        .ParfBase = PCIE0_PCIE30_PARF_REG_BASE_PHYS,
        .GccBase = PCIE0_PCIE_CC_BASE,
        .ResourceMap.SegmentNumber = 0,
        .ResourceMap.AllocationAttributes = EFI_PCI_HOST_BRIDGE_MEM64_DECODE,
        .ResourceMap.Res[TypeIo].Base = 0x00001000,
        .ResourceMap.Res[TypeMem32].Base = 0x00100000,
        .ResourceMap.Res[TypePMem32].Base = 0x40000000,
        .ResourceMap.Res[TypeMem64].Base = 0x20000000,
        .ResourceMap.Res[TypePMem64].Base = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x400000000,
        .ResourceMap.Res[TypeBus].Base = 0,
        .ResourceMap.Res[TypeIo].Start = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0xFFFFFF0000,
        .ResourceMap.Res[TypeMem32].Start = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0100100000,
        .ResourceMap.Res[TypePMem32].Start = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0300000000,
        .ResourceMap.Res[TypeMem64].Start = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0200000000,
        .ResourceMap.Res[TypePMem64].Start = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0400000000,
        .ResourceMap.Res[TypeBus].Start = 0,
        .ResourceMap.Res[TypeIo].End = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x10000000000,
        .ResourceMap.Res[TypeMem32].End = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x00120000000,
        .ResourceMap.Res[TypePMem32].End = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x00340000000,
        .ResourceMap.Res[TypeMem64].End = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x00220000000,
        .ResourceMap.Res[TypePMem64].End = PCIE0_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0FFFFFF0000,
        .ResourceMap.Res[TypeBus].End = 0xFF,
        .PcieSubSystem = PCIE_SS_0,
        .MaxFunctionOnRootBridge = 1,
        .AspmSupport = 0,
        .NoSnoop = PCIE_OPTION_DEFAULT,
        .IdBasedOrdering = PCIE_OPTION_DEFAULT,
        .ECRC = PCIE_OPTION_ENABLE,
        .ComplianceMode = PCIE_OPTION_DISABLE,
        .TcVcMap[0] = 0x0f,
        .TcVcMap[1] = 0xf0,
        .MaxPayloadSize = 0x2,
        .MaxReadRequestSize = 0x5,
        .TphRequestCap = HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_NO_ST_MODE_BMSK
    },
    {
        .ControllerId = 1,
        .PcieBase = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS,
        .PcieSize = 0x8000000000000000,
        .ElbiBase = PCIE1_PCIE30_ELBI_REG_BASE_PHYS,
        .ParfBase = PCIE1_PCIE30_PARF_REG_BASE_PHYS,
        .GccBase = PCIE0_PCIE_CC_BASE,
        .ResourceMap.SegmentNumber = 1,
        .ResourceMap.AllocationAttributes = EFI_PCI_HOST_BRIDGE_MEM64_DECODE,
        .ResourceMap.Res[TypeIo].Base = 0x00001000,
        .ResourceMap.Res[TypeMem32].Base = 0x00100000,
        .ResourceMap.Res[TypePMem32].Base = 0x40000000,
        .ResourceMap.Res[TypeMem64].Base = 0x20000000,
        .ResourceMap.Res[TypePMem64].Base = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x400000000,
        .ResourceMap.Res[TypeBus].Base = 0,
        .ResourceMap.Res[TypeIo].Start = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0xFFFFFF0000,
        .ResourceMap.Res[TypeMem32].Start = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0100100000,
        .ResourceMap.Res[TypePMem32].Start = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0300000000,
        .ResourceMap.Res[TypeMem64].Start = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0200000000,
        .ResourceMap.Res[TypePMem64].Start = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0400000000,
        .ResourceMap.Res[TypeBus].Start = 0,
        .ResourceMap.Res[TypeIo].End = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x10000000000,
        .ResourceMap.Res[TypeMem32].End = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00120000000,
        .ResourceMap.Res[TypePMem32].End = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00340000000,
        .ResourceMap.Res[TypeMem64].End = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00220000000,
        .ResourceMap.Res[TypePMem64].End = PCIE1_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0FFFFFF0000,
        .ResourceMap.Res[TypeBus].End = 0xFF,
        .PcieSubSystem = PCIE_SS_0,
        .MaxFunctionOnRootBridge = 1,
        .AspmSupport = 0,
        .NoSnoop = PCIE_OPTION_DEFAULT,
        .IdBasedOrdering = PCIE_OPTION_DEFAULT,
        .ECRC = PCIE_OPTION_ENABLE,
        .ComplianceMode = PCIE_OPTION_DISABLE,
        .TcVcMap[0] = 0x0f,
        .TcVcMap[1] = 0xf0,
        .MaxPayloadSize = 0x2,
        .MaxReadRequestSize = 0x5,
        .TphRequestCap = HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_NO_ST_MODE_BMSK
    },
    {
        .ControllerId = 2,
        .PcieBase = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS,
        .PcieSize = 0x8000000000000000,
        .ElbiBase = PCIE2_PCIE30_ELBI_REG_BASE_PHYS,
        .ParfBase = PCIE2_PCIE30_PARF_REG_BASE_PHYS,
        .GccBase = PCIE0_PCIE_CC_BASE,
        .ResourceMap.SegmentNumber = 2,
        .ResourceMap.AllocationAttributes = EFI_PCI_HOST_BRIDGE_MEM64_DECODE,
        .ResourceMap.Res[TypeIo].Base = 0x00001000,
        .ResourceMap.Res[TypeMem32].Base = 0x00100000,
        .ResourceMap.Res[TypePMem32].Base = 0x40000000,
        .ResourceMap.Res[TypeMem64].Base = 0x20000000,
        .ResourceMap.Res[TypePMem64].Base = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x400000000,
        .ResourceMap.Res[TypeBus].Base = 0,
        .ResourceMap.Res[TypeIo].Start = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0xFFFFFF0000,
        .ResourceMap.Res[TypeMem32].Start = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0100100000,
        .ResourceMap.Res[TypePMem32].Start = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0300000000,
        .ResourceMap.Res[TypeMem64].Start = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0200000000,
        .ResourceMap.Res[TypePMem64].Start = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0400000000,
        .ResourceMap.Res[TypeBus].Start = 0,
        .ResourceMap.Res[TypeIo].End = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x10000000000,
        .ResourceMap.Res[TypeMem32].End = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00120000000,
        .ResourceMap.Res[TypePMem32].End = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00340000000,
        .ResourceMap.Res[TypeMem64].End = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00220000000,
        .ResourceMap.Res[TypePMem64].End = PCIE2_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0FFFFFF0000,
        .ResourceMap.Res[TypeBus].End = 0xFF,
        .PcieSubSystem = PCIE_SS_0,
        .MaxFunctionOnRootBridge = 1,
        .AspmSupport = 0,
        .NoSnoop = PCIE_OPTION_DEFAULT,
        .IdBasedOrdering = PCIE_OPTION_DEFAULT,
        .ECRC = PCIE_OPTION_ENABLE,
        .ComplianceMode = PCIE_OPTION_DISABLE,
        .TcVcMap[0] = 0x0f,
        .TcVcMap[1] = 0xf0,
        .MaxPayloadSize = 0x2,
        .MaxReadRequestSize = 0x5,
        .TphRequestCap = HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_NO_ST_MODE_BMSK
    },
    {
        .ControllerId = 3,
        .PcieBase = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS,
        .PcieSize = 0x8000000000000000,
        .ElbiBase = PCIE3_PCIE30_ELBI_REG_BASE_PHYS,
        .ParfBase = PCIE3_PCIE30_PARF_REG_BASE_PHYS,
        .GccBase = PCIE1_PCIE_CC_BASE,
        .ResourceMap.SegmentNumber = 3,
        .ResourceMap.AllocationAttributes = EFI_PCI_HOST_BRIDGE_MEM64_DECODE,
        .ResourceMap.Res[TypeIo].Base = 0x00001000,
        .ResourceMap.Res[TypeMem32].Base = 0x00100000,
        .ResourceMap.Res[TypePMem32].Base = 0x40000000,
        .ResourceMap.Res[TypeMem64].Base = 0x20000000,
        .ResourceMap.Res[TypePMem64].Base = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x400000000,
        .ResourceMap.Res[TypeBus].Base = 0,
        .ResourceMap.Res[TypeIo].Start = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0xFFFFFF0000,
        .ResourceMap.Res[TypeMem32].Start = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0100100000,
        .ResourceMap.Res[TypePMem32].Start = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0300000000,
        .ResourceMap.Res[TypeMem64].Start = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0200000000,
        .ResourceMap.Res[TypePMem64].Start = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0400000000,
        .ResourceMap.Res[TypeBus].Start = 0,
        .ResourceMap.Res[TypeIo].End = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x10000000000,
        .ResourceMap.Res[TypeMem32].End = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x00120000000,
        .ResourceMap.Res[TypePMem32].End = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x00340000000,
        .ResourceMap.Res[TypeMem64].End = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x00220000000,
        .ResourceMap.Res[TypePMem64].End = PCIE3_PCIE30_WRAPPER_AXI_X16_DBI_REG_BASE_PHYS + 0x0FFFFFF0000,
        .ResourceMap.Res[TypeBus].End = 0xFF,
        .PcieSubSystem = PCIE_SS_1,
        .MaxFunctionOnRootBridge = 1,
        .AspmSupport = 0,
        .NoSnoop = PCIE_OPTION_DEFAULT,
        .IdBasedOrdering = PCIE_OPTION_DEFAULT,
        .ECRC = PCIE_OPTION_ENABLE,
        .ComplianceMode = PCIE_OPTION_DISABLE,
        .TcVcMap[0] = 0x0f,
        .TcVcMap[1] = 0xf0,
        .MaxPayloadSize = 0x2,
        .MaxReadRequestSize = 0x5,
        .TphRequestCap = HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_NO_ST_MODE_BMSK
    },
    {
        .ControllerId = 4,
        .PcieBase = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS,
        .PcieSize = 0x8000000000000000,
        .ElbiBase = PCIE4_PCIE30_ELBI_REG_BASE_PHYS,
        .ParfBase = PCIE4_PCIE30_PARF_REG_BASE_PHYS,
        .GccBase = PCIE1_PCIE_CC_BASE,
        .ResourceMap.SegmentNumber = 4,
        .ResourceMap.AllocationAttributes = EFI_PCI_HOST_BRIDGE_MEM64_DECODE,
        .ResourceMap.Res[TypeIo].Base = 0x00001000,
        .ResourceMap.Res[TypeMem32].Base = 0x00100000,
        .ResourceMap.Res[TypePMem32].Base = 0x40000000,
        .ResourceMap.Res[TypeMem64].Base = 0x20000000,
        .ResourceMap.Res[TypePMem64].Base = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x400000000,
        .ResourceMap.Res[TypeBus].Base = 0,
        .ResourceMap.Res[TypeIo].Start = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0xFFFFFF0000,
        .ResourceMap.Res[TypeMem32].Start = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0100100000,
        .ResourceMap.Res[TypePMem32].Start = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0300000000,
        .ResourceMap.Res[TypeMem64].Start = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0200000000,
        .ResourceMap.Res[TypePMem64].Start = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0400000000,
        .ResourceMap.Res[TypeBus].Start = 0,
        .ResourceMap.Res[TypeIo].End = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x10000000000,
        .ResourceMap.Res[TypeMem32].End = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00120000000,
        .ResourceMap.Res[TypePMem32].End = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00340000000,
        .ResourceMap.Res[TypeMem64].End = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00220000000,
        .ResourceMap.Res[TypePMem64].End = PCIE4_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0FFFFFF0000,
        .ResourceMap.Res[TypeBus].End = 0xFF,
        .PcieSubSystem = PCIE_SS_1,
        .MaxFunctionOnRootBridge = 1,
        .AspmSupport = 0,
        .NoSnoop = PCIE_OPTION_DEFAULT,
        .IdBasedOrdering = PCIE_OPTION_DEFAULT,
        .ECRC = PCIE_OPTION_ENABLE,
        .ComplianceMode = PCIE_OPTION_DISABLE,
        .TcVcMap[0] = 0x0f,
        .TcVcMap[1] = 0xf0,
        .MaxPayloadSize = 0x2,
        .MaxReadRequestSize = 0x5,
        .TphRequestCap = HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_NO_ST_MODE_BMSK
    },
    {
        .ControllerId = 5,
        .PcieBase = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS,
        .PcieSize = 0x8000000000000000,
        .ElbiBase = PCIE5_PCIE30_ELBI_REG_BASE_PHYS,
        .ParfBase = PCIE5_PCIE30_PARF_REG_BASE_PHYS,
        .GccBase = PCIE1_PCIE_CC_BASE,
        .ResourceMap.SegmentNumber = 5,
        .ResourceMap.AllocationAttributes = EFI_PCI_HOST_BRIDGE_MEM64_DECODE,
        .ResourceMap.Res[TypeIo].Base = 0x00001000,
        .ResourceMap.Res[TypeMem32].Base = 0x00100000,
        .ResourceMap.Res[TypePMem32].Base = 0x40000000,
        .ResourceMap.Res[TypeMem64].Base = 0x20000000,
        .ResourceMap.Res[TypePMem64].Base = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x400000000,
        .ResourceMap.Res[TypeBus].Base = 0,
        .ResourceMap.Res[TypeIo].Start = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0xFFFFFF0000,
        .ResourceMap.Res[TypeMem32].Start = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0100100000,
        .ResourceMap.Res[TypePMem32].Start = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0300000000,
        .ResourceMap.Res[TypeMem64].Start = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0200000000,
        .ResourceMap.Res[TypePMem64].Start = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0400000000,
        .ResourceMap.Res[TypeBus].Start = 0,
        .ResourceMap.Res[TypeIo].End = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x10000000000,
        .ResourceMap.Res[TypeMem32].End = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00120000000,
        .ResourceMap.Res[TypePMem32].End = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00340000000,
        .ResourceMap.Res[TypeMem64].End = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x00220000000,
        .ResourceMap.Res[TypePMem64].End = PCIE5_PCIE30_WRAPPER_AXI_X8_DBI_REG_BASE_PHYS + 0x0FFFFFF0000,
        .ResourceMap.Res[TypeBus].End = 0xFF,
        .PcieSubSystem = PCIE_SS_1,
        .MaxFunctionOnRootBridge = 1,
        .AspmSupport = 0,
        .NoSnoop = PCIE_OPTION_DEFAULT,
        .IdBasedOrdering = PCIE_OPTION_DEFAULT,
        .ECRC = PCIE_OPTION_ENABLE,
        .ComplianceMode = PCIE_OPTION_DISABLE,
        .TcVcMap[0] = 0x0f,
        .TcVcMap[1] = 0xf0,
        .MaxPayloadSize = 0x2,
        .MaxReadRequestSize = 0x5,
        .TphRequestCap = HWIO_TPH_REQ_CAP_REG_REG_TPH_REQ_NO_ST_MODE_BMSK
    }
};

PCIE_SLOT_CONF_t mSlotConfig[2][7] = 
{
  {
	// 3 slot
	{
	  .LaneIndex = 8,
	  .NumLanes = 4,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 2,
		.ControllerId = 2,
		.PcieSubSystemId = 0,
		.DataWidth = WIDTH_X4,
		.SlotWidth = WIDTH_X8,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 2,
	  }
	},
	{
	  .LaneIndex = 0,
	  .NumLanes = 8,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 1,
		.ControllerId = 1,
		.PcieSubSystemId = 0,
		.DataWidth = WIDTH_X8,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 1,
	  }
	},
	{
	  .LaneIndex = 12,
	  .NumLanes = 4,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 3,
		.ControllerId = 0,
		.PcieSubSystemId = 0,
		.DataWidth = WIDTH_X4,
		.SlotWidth = WIDTH_X8,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 3,
	  }
	},
	// 2 slot
	{
	  .LaneIndex = 0,
	  .NumLanes = 8,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 1,
		.ControllerId = 1,
		.PcieSubSystemId = 0,
		.DataWidth = WIDTH_X8,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 1,
	  }
	},
	{
	  .LaneIndex = 8,
	  .NumLanes = 8,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 2,
		.ControllerId = 2,
		.PcieSubSystemId = 0,
		.DataWidth = WIDTH_X8,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 2,
	  }
	},
	// 1 slot
	{
	  .LaneIndex = 0,
	  .NumLanes = 16,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 1,
		.ControllerId = 0,
		.PcieSubSystemId = 0,
		.DataWidth = WIDTH_X16,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 1,
	  }
	},
	// direct connection
	{
	  .LaneIndex = 0,
	  .NumLanes = 16,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 1,
		.ControllerId = 0,
		.PcieSubSystemId = 0,
		.DataWidth = WIDTH_X16,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 1,
	  }
	}
  },
  {
	// 3 slot
	{
	  .LaneIndex = 8,
	  .NumLanes = 4,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 5,
		.ControllerId = 5,
		.PcieSubSystemId = 1,
		.DataWidth = WIDTH_X4,
		.SlotWidth = WIDTH_X8,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 5,
	  }
	},
	{
	  .LaneIndex = 0,
	  .NumLanes = 8,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 4,
		.ControllerId = 4,
		.PcieSubSystemId = 1,
		.DataWidth = WIDTH_X8,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 4,
	  }
	},

	{
	  .LaneIndex = 12,
	  .NumLanes = 4,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 6,
		.ControllerId = 3,
		.PcieSubSystemId = 1,
		.DataWidth = WIDTH_X4,
		.SlotWidth = WIDTH_X8,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 6,
	  }
	},
	// 2 slot
	{
	  .LaneIndex = 0,
	  .NumLanes = 8,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 4,
		.ControllerId = 4,
		.PcieSubSystemId = 1,
		.DataWidth = WIDTH_X8,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 4,
	  }
	},
	{
	  .LaneIndex = 8,
	  .NumLanes = 8,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 5,
		.ControllerId = 5,
		.PcieSubSystemId = 1,
		.DataWidth = WIDTH_X8,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 5,
	  }
	},
	// 1 slot
	{
	  .LaneIndex = 0,
	  .NumLanes = 16,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 4,
		.ControllerId = 3,
		.PcieSubSystemId = 1,
		.DataWidth = WIDTH_X16,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 4,
	  }
	},
	// direct connection
	{
	  .LaneIndex = 0,
	  .NumLanes = 16,
	  .SlotInfoProtocol =
	  {
		.Revision = QCOM_PCIE_CONFIG_SLOT_INFO_PROTOCOL_REVISION,
		.SlotId = 4,
		.ControllerId = 3,
		.PcieSubSystemId = 1,
		.DataWidth = WIDTH_X16,
		.SlotWidth = WIDTH_X16,
		.MaxSpeed = SPEED_GEN3,
		.PowerLimit = SLOT_POWER_LIMIT_75W
	  },
	  .SlotCapabilitiesProtocol.Bits =
	  {
		.AttentionButton = 1,
		.PowerController = 1,
		.MrlSensor = 1,
		.AttentionIndicator = 1,
		.PowerIndicator = 1,
		.HotPlugSurprise = 0,
		.HotPlugCapable = 1,
		.SlotPowerLimitValue = SLOT_POWER_LIMIT_75W,
		.SlotPowerLimitScale = 0,
		.ElectromechanicalInterlock = 1,
		.NoCommandCompleted = 0,
		.PhysicalSlotNumber = 4,
	  }
	}
  }
};

STATIC CONST UINTN PortExpanderAddress[] = {0x3e, 0x3f, 0x70, 0x71};
STATIC CONST UINTN DriveSlotPortExpanderAddress[] = {0x60, 0x61};

#define MmioWrite32(_addr_, _data_) __raw_writel( (_data_), (_addr_) )
#define MmioRead32(_addr_) __raw_readl( (_addr_) )

uint32_t MmioAnd32 (uint64_t Address, uint32_t  AndData)
{
	return MmioWrite32 (Address, MmioRead32 (Address) & AndData);
}

uint32_t MmioOr32 (uint64_t Address, uint32_t OrData)
{
	return MmioWrite32 (Address, MmioRead32 (Address) | OrData);
}

uint32_t MmioAndThenOr32 (uint64_t Address, uint32_t AndData, uint32_t OrData)
{
	return MmioWrite32 (Address, (MmioRead32 (Address) & AndData) | OrData);
}

// macro concatenate
#define MC2(a, b) a##b
#define MC3(a, b, c) a##b##c
#define MC4(a, b, c, d) a##b##c##d
#define MC5(a, b, c, d, e) a##b##c##d##e
#define MC6(a, b, c, d, e, f) a##b##c##d##e##f
#define MC7(a, b, c, d, e, f, g) a##b##c##d##e##f##g

// base, reg_name, field_name, using _INM/_OUM in header
#define reg_base_read(b, r, f) \
	MC3(HWIO_, r, _INM)(b, MC5(HWIO_, r, _, f, _BMSK)) >> MC5(HWIO_, r, _, f, _SHFT)
#define reg_base_write(b, r, f, v) \
	MC3(HWIO_, r, _OUTM)(b, MC5(HWIO_, r, _, f, _BMSK), (v) << MC5(HWIO_, r, _, f, _SHFT))
// reg_name, field_name, using MmioRead32/MmioOr32
#define reg_read(r, f) \
	((MmioRead32(MC3(HWIO_, r, _ADDR)) & MC5(HWIO_, r, _, f, _BMSK)) >> MC5(HWIO_, r, _, f, _SHFT))
#define reg_write(r, f, v) \
	MmioOr32(MC3(HWIO_, r, _ADDR), (v << MC5(HWIO_, r, _, f, _SHFT)) & MC5(HWIO_, r, _, f, _BMSK))
#define reg_clear(r, f) reg_write(r, f, 0)

// move to pci.c later

void pcie_gpio_setting(void)
{
	printf("PCIe gpio setting\r\n");
	//enable gpio 35
	MmioWrite32(HWIO_TLMM_GPIO_CFGn_ADDR(35), (1 << 9) | 0x11);
	//set gpio out mode
	MmioWrite32(HWIO_TLMM_GPIO_IN_OUTn_ADDR(35), 0x0);
	Hdts_waitForMicroSecs(10000);
	MmioWrite32(HWIO_TLMM_GPIO_IN_OUTn_ADDR(35), 0x2);
}
int pcie_c_ready_polling(uint32_t timeout_in_ms)
{
	uint32_t times = 0;
	volatile uint32_t val;

	printf("Entering in to C_READY Polling loop !!!\n");

	while ((MmioRead32(HWIO_PCIE_CLKGEN_C_READY_STATUS_ADDR) & 0x1) == 0) {
		udelay(1000);
		if (times++ >= timeout_in_ms) {
			printf("C_READY Polling Timer Expired !!!\n");
			return -1;
		}
	}

	printf("Power Sequence Completed with C_READY bit set !!!\n");
	return 0;
}

// setup clkgen for pcie phy
int pcie_clkgen_init(void)
{
	// setting PCIE_CLKGEN_PWRDN_B to 1
	// MmioWrite32(HWIO_GCCE_PCIE_CLKGEN_MISC_ADDR, 0x1); //Active low power down control for the
	// PCIe clock gen
	reg_write(GCCE_PCIE_CLKGEN_MISC, PCIE_CLKGEN_PWRDN_B, 1);

	if ((MmioRead32(HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR) & HWIO_PCIE_CLKGEN_CLK_ENABLE1_RMSK) != 0) {
		printf("pcie clkgen already enabled.\n");
		return -1;
	}

// ClkInitPowerUpSscOff:
// 	reg_write(PCIE_CLKGEN_SW_RESET, SW_RESET, 0x1);
// 	reg_write(PCIE_CLKGEN_RESETSM_CNTRL, RSM_START_MUX, 0x1);
// 	reg_write(PCIE_CLKGEN_CMN_CONFIG, CLKGEN_MODE, 0x2);
#if 1
	printf("ClkInitPowerUpSscOn\n");
	MmioWrite32(HWIO_PCIE_CLKGEN_SW_RESET_ADDR, 0x01);
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR, 0x04);
	MmioWrite32(HWIO_PCIE_CLKGEN_CMN_CONFIG_ADDR, 0x02);
	MmioWrite32(HWIO_PCIE_CLKGEN_CMN_MODE_ADDR, 0X01);
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_EN_CENTER_ADDR, 0x01);
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_SELECT_ADDR, 0x2f);
	MmioWrite32(HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_ADDR, 0x4a);
	MmioWrite32(HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_ADDR, 0x01);
	MmioWrite32(HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_ADDR, 0x00);
	MmioWrite32(HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_ADDR, 0x01);
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR, 0x3a);
	MmioWrite32(HWIO_PCIE_CLKGEN_BGV_TRIM_ADDR, 0x20);
	MmioWrite32(HWIO_PCIE_CLKGEN_BGT_TRIM_ADDR, 0x0f);
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_IPTRIM_ADDR, 0x20);
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_IETRIM_ADDR, 0x20);
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_IVCO_ADDR, 0x0f);
	MmioWrite32(HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_ADDR, 0x01);
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_ADDR, 0x34);
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_ADDR, 0x16);
	MmioWrite32(HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_ADDR, 0x08);
	MmioWrite32(HWIO_PCIE_CLKGEN_DEC_START_MODE0_ADDR, 0x7c);
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_ADDR, 0x9a);
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_ADDR, 0x99);
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_ADDR, 0x0f);
	MmioWrite32(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_ADDR, 0x3f);
	MmioWrite32(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_ADDR, 0x00);
	MmioWrite32(HWIO_PCIE_CLKGEN_HSCLK_SEL1_ADDR, 0x03);
	MmioWrite32(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR, 0x72);
	MmioWrite32(HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_ADDR, 0x00);
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_ADDR, 0xff);
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_ADDR, 0x31);
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_ADDR, 0x00);
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP_EN_ADDR, 0x04);
	MmioWrite32(HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_ADDR, 0x00);
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_PER1_ADDR, 0x43);
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_PER2_ADDR, 0x01);
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_ADDR, 0xd1);
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_ADDR, 0x06);
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_ADDR, 0x08);
	MmioWrite32(HWIO_PCIE_CLKGEN_SW_RESET_ADDR, 0x00);
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR, 0x06);
#else
	MmioWrite32(HWIO_PCIE_CLKGEN_SW_RESET_ADDR, 0x01); // Assert sw_reset from SWI
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR,
				0x04); // Program RSM start mux to 1, start remains 0
	MmioWrite32(HWIO_PCIE_CLKGEN_CMN_CONFIG_ADDR, 0x02); // QMP mode
	MmioWrite32(HWIO_PCIE_CLKGEN_CMN_MODE_ADDR, 0X01); // Turn off DDR clkout
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_EN_CENTER_ADDR, 0x01); // Turn on SSC with down spread type
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_SELECT_ADDR,
				0x2b); // Select cmos pad as refclk input and swing to 2�b01
	MmioWrite32(HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_ADDR,
				0x4a); // Select EP clk to CML output, override sysclk_en to 0
	MmioWrite32(HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_ADDR,
				0x01); // Select cml_sysclk_sel value from register, not from external signal
	MmioWrite32(HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_ADDR,
				0x00); // program sysclk_cm, sysclk_ac_couple, sys_gndterm to 0
	MmioWrite32(HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_ADDR, 0x01); // Enable CML sysclk_outp/n
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR, 0x3a); // Enable EP clk
	MmioWrite32(HWIO_PCIE_CLKGEN_BGV_TRIM_ADDR, 0x20); // Bandgap trim setting
	MmioWrite32(HWIO_PCIE_CLKGEN_BGT_TRIM_ADDR, 0x0f); // Bandgap trim setting
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_IPTRIM_ADDR, 0x20); // Current trim setting
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_IETRIM_ADDR, 0x20); // Current trim setting
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_IVCO_ADDR, 0x0f); // PLL VCO current setting
	MmioWrite32(HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_ADDR, 0x01); // SVS mode setting
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_ADDR,
				0x34); // Second cap of the loop filter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_ADDR, 0x16); // PLL RC loop filter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_ADDR, 0x08); // Charge pump setting
	MmioWrite32(HWIO_PCIE_CLKGEN_DEC_START_MODE0_ADDR, 0x7c); // PLL decimal divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_ADDR,
				0x9a); // Fractional pll feedback divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_ADDR,
				0x99); // Fractional pll feedback divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_ADDR,
				0x0f); // Fractional pll feedback divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_ADDR, 0x3f); // Integral loop setting
	MmioWrite32(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_ADDR, 0x00); // Integral loop setting
	MmioWrite32(HWIO_PCIE_CLKGEN_HSCLK_SEL1_ADDR, 0x03); // High speed clk divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR, 0x72); // Turn off auxclk from SWI
	MmioWrite32(HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_ADDR, 0x00); // Vco tune mappting setting
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_ADDR, 0xff); // PLL lock counter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_ADDR, 0x31); // PLL lock counter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_ADDR, 0x00); // PLL lock counter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP_EN_ADDR, 0x04); // Set plllock_rng for SSC case
	MmioWrite32(HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_ADDR, 0x00); // Do not bypass vco cal
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_PER1_ADDR, 0x4d); // SSC period setting
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_PER2_ADDR, 0x01); // SSC period setting
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_ADDR, 0x9c); // SSC step size setting
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_ADDR, 0x06); // SSC step size setting
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_ADDR, 0x08); // Do not bypass RSM restrim
	MmioWrite32(HWIO_PCIE_CLKGEN_SW_RESET_ADDR, 0x00); // De-assert sw_reset from SWI
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR, 0x06); // Start RSM from SWI
#endif

	pcie_c_ready_polling(1500);
	MmioWrite32(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR, 0x7a);

	return 0;
}

void pcie_clk_init(PCIE_SS_t pcie_ss)
{
	printf("PCIe clock init\r\n");
	if (pcie_ss == PCIE_SS_0)
	{
		//pcie_0 clock CBC init
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_SFPB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_VBU_AHB_CFG_CBCR_ADDR, 0x1);

		// clock for core 0
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X16_AUX_CBCR_ADDR,
				 HWIO_PCIE0_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_ENABLE_BMSK);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X16_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X16_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_ADDR, 0x1);

		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_A_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PHY_A_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_B_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PHY_B_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_C_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PHY_C_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_ADDR, 0x1);

		// clock for core 1
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_ADDR, 0x1);

		// clock for core 2
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_ADDR, 0x1);

		//pcie_0 clock RCG
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_SFPB_CFG_RCGR_ADDR, 0x00000213);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_SFPB_CMD_RCGR_ADDR, 0x3);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_ADDR, 0x00000301);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ADDR, 0x3);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_ADDR, 0x00000301);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ADDR, 0x3);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_AUX_CFG_RCGR_ADDR, 0x00002003);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_AUX_CMD_RCGR_ADDR, 0x3);
	}
	else if (pcie_ss == PCIE_SS_1)
	{
		//pcie_1 clock CBC init
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_SFPB_ALWAYS_ON_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_SFPB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_VBU_AHB_CFG_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X16_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X16_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X16_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_A_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PHY_A_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_PHY_AA_CFG_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_PHY_AB_CFG_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_B_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PHY_B_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_PHY_B_CFG_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_C_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PHY_C_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_PHY_C_CFG_AHB_CBCR_ADDR, 0x1);

		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_ADDR, 0x1);

		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_AUX_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_PCLK_CBCR_ADDR, 0x1);
		MmioOr32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_ADDR, 0x1);

		//pcie_1 clock RCG
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_SFPB_CFG_RCGR_ADDR, 0x00000213);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_SFPB_CMD_RCGR_ADDR, 0x3);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X16_MSTR_Q23_CFG_RCGR_ADDR, 0x00000301);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X16_MSTR_Q23_CMD_RCGR_ADDR, 0x3);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X16_SLV_Q23_CFG_RCGR_ADDR, 0x00000301);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X16_SLV_Q23_CMD_RCGR_ADDR, 0x3);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_AUX_CFG_RCGR_ADDR, 0x00002003);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_AUX_CMD_RCGR_ADDR, 0x3);
	}
	else
	{
		printf("[ERROR]PCIe clock init. Illegal input parameters!\r\n");
		return;
	}

	//gcce pcie vbu clock
	MmioWrite32(HWIO_GCCE_PCIE_SS_0_VBU_CFG_RCGR_ADDR, 0x00000501);
	MmioWrite32(HWIO_GCCE_PCIE_SS_0_VBU_CMD_RCGR_ADDR, 0x3);

	//pcie clock init
	MmioWrite32(HWIO_GCCE_PCIE_CLKGEN_MISC_ADDR, 0x1); //Active low power down control for the PCIe clock gen
	MmioWrite32(HWIO_PCIE_CLKGEN_SW_RESET_ADDR, 0x01); // Assert sw_reset from SWI
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR, 0x04); // Program RSM start mux to 1, start remains 0
	MmioWrite32(HWIO_PCIE_CLKGEN_CMN_CONFIG_ADDR, 0x02); // QMP mode
	MmioWrite32(HWIO_PCIE_CLKGEN_CMN_MODE_ADDR, 0X01); // Turn off DDR clkout
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_EN_CENTER_ADDR, 0x01); // Turn on SSC with down spread type
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_SELECT_ADDR, 0x2b); // Select cmos pad as refclk input and swing to 2�b01
	MmioWrite32(HWIO_PCIE_CLKGEN_SYSCLK_EN_SEL_ADDR, 0x4a); // Select EP clk to CML output, override sysclk_en to 0
	MmioWrite32(HWIO_PCIE_CLKGEN_CML_SYSCLK_SEL_ADDR, 0x01); // Select cml_sysclk_sel value from register, not from external signal
	MmioWrite32(HWIO_PCIE_CLKGEN_SYS_CLK_CTRL_ADDR, 0x00); // program sysclk_cm, sysclk_ac_couple, sys_gndterm to 0
	MmioWrite32(HWIO_PCIE_CLKGEN_SYSCLK_BUF_ENABLE_ADDR, 0x01); // Enable CML sysclk_outp/n
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_ENABLE1_ADDR, 0x3a); // Enable EP clk
	MmioWrite32(HWIO_PCIE_CLKGEN_BGV_TRIM_ADDR, 0x20); // Bandgap trim setting
	MmioWrite32(HWIO_PCIE_CLKGEN_BGT_TRIM_ADDR, 0x0f); // Bandgap trim setting
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_IPTRIM_ADDR, 0x20); // Current trim setting
	MmioWrite32(HWIO_PCIE_CLKGEN_CLK_IETRIM_ADDR, 0x20); // Current trim setting
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_IVCO_ADDR, 0x0f); // PLL VCO current setting
	MmioWrite32(HWIO_PCIE_CLKGEN_SVS_MODE_CLK_SEL_ADDR, 0x01); // SVS mode setting
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_CCTRL_MODE0_ADDR, 0x34); // Second cap of the loop filter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_PLL_RCTRL_MODE0_ADDR, 0x16); // PLL RC loop filter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_CP_CTRL_MODE0_ADDR, 0x08); // Charge pump setting
	MmioWrite32(HWIO_PCIE_CLKGEN_DEC_START_MODE0_ADDR, 0x7c); // PLL decimal divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START1_MODE0_ADDR, 0x9a); //Fractional pll feedback divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START2_MODE0_ADDR, 0x99); //Fractional pll feedback divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_DIV_FRAC_START3_MODE0_ADDR, 0x0f); //Fractional pll feedback divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN0_MODE0_ADDR, 0x3f); // Integral loop setting
	MmioWrite32(HWIO_PCIE_CLKGEN_INTEGLOOP_GAIN1_MODE0_ADDR, 0x00); // Integral loop setting
	MmioWrite32(HWIO_PCIE_CLKGEN_HSCLK_SEL1_ADDR, 0x03); // High speed clk divider setting
	MmioWrite32(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR, 0x72); // Turn off auxclk from SWI
	MmioWrite32(HWIO_PCIE_CLKGEN_VCO_TUNE_MAP_ADDR, 0x00); // Vco tune mappting setting
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP1_MODE0_ADDR, 0xff); // PLL lock counter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP2_MODE0_ADDR, 0x31); // PLL lock counter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP3_MODE0_ADDR, 0x00); // PLL lock counter setting
	MmioWrite32(HWIO_PCIE_CLKGEN_LOCK_CMP_EN_ADDR, 0x04); // Set plllock_rng for SSC case
	MmioWrite32(HWIO_PCIE_CLKGEN_VCO_TUNE_CTRL_ADDR, 0x00); // Do not bypass vco cal
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_PER1_ADDR, 0x4d); // SSC period setting
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_PER2_ADDR, 0x01); // SSC period setting
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE1_ADDR, 0x9c); // SSC step size setting
	MmioWrite32(HWIO_PCIE_CLKGEN_SSC_STEP_SIZE2_ADDR, 0x06); // SSC step size setting
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL2_ADDR, 0x08); // Do not bypass RSM restrim
	MmioWrite32(HWIO_PCIE_CLKGEN_SW_RESET_ADDR, 0x00); // De-assert sw_reset from SWI
	MmioWrite32(HWIO_PCIE_CLKGEN_RESETSM_CNTRL_ADDR, 0x06); // Start RSM from SWI

	//check clkgen c_ready
	while ((MmioRead32(HWIO_PCIE_CLKGEN_C_READY_STATUS_ADDR) & HWIO_PCIE_CLKGEN_C_READY_STATUS_C_READY_BMSK) == 0)
	{
		Hdts_waitForMicroSecs(10000);
	}
	printf("PCIe clkgen C_Ready!\r\n");

	//Turn off core clk to save power
	MmioWrite32(HWIO_PCIE_CLKGEN_CORE_CLK_EN_ADDR, 0x7a); // NOTE: If SW reset is given, core clock needs to be enabled again otherwise PLL won�t lock

	if (pcie_ss == PCIE_SS_0)
	{
		//------following for pcie_ss_0 cbcr and in v2.0--------
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MSTR_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X16_SLV_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MSTR_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_SLV_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MSTR_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_SLV_AXI_CBCR_ADDR, 0x1);
	}
	else
	{
		//------following for pcie_ss_1 cbcr and in v2.0--------
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X16_MSTR_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X16_SLV_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_MSTR_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X8_0_SLV_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_MSTR_AXI_CBCR_ADDR, 0x1);
		MmioWrite32(HWIO_PCIE1_PCIE_CC_PCIE_X8_1_SLV_AXI_CBCR_ADDR, 0x1);
	}
}

void pcie_lane_init(uint64_t base, PCIE_LaneInitCommand_t Command)
{
	switch (Command) 
	{
		case LaneConfigure:
			if (gPcieEyeMonModeEnable != 0) 
			{
				MmioOr32(HWIO_AUX_ENABLE_ADDR(base), 0x03); // Configure EyeMod Mode
				printf("[PCIe] PHY Enable EyeMon Mode! 0x%x\r\n", MmioRead32(HWIO_AUX_ENABLE_ADDR(base)));
			}
			MmioWrite32(HWIO_UCDR_SO_CONFIG_ADDR(base), 0x0C); // Configure UCDR
			MmioWrite32(HWIO_UCDR_FO_GAIN_MODE0_ADDR(base), 0x8B); // Configure UCDR
			MmioWrite32(HWIO_UCDR_FO_GAIN_MODE1_ADDR(base), 0x08); // Configure UCDR
			MmioWrite32(HWIO_UCDR_FO_GAIN_MODE2_ADDR(base), 0x09); // Configure UCDR
			MmioWrite32(HWIO_UCDR_SO_GAIN_MODE0_ADDR(base), 0x03); // Configure UCDR
			MmioWrite32(HWIO_UCDR_SO_GAIN_MODE1_ADDR(base), 0x04); // Configure UCDR
			MmioWrite32(HWIO_UCDR_SO_GAIN_MODE2_ADDR(base), 0x02); // Configure UCDR
			MmioWrite32(HWIO_RX_BAND_ADDR(base), 0x02); // Set rxband for each mode
			MmioWrite32(HWIO_TX_BAND_MODE_ADDR(base), 0x01); // Set txband for each mode
			MmioWrite32(HWIO_RX_RCVR_PATH1_MODE0_ADDR(base), 0x5C); // Config Rx path for mode0
			MmioWrite32(HWIO_RX_RCVR_PATH1_MODE1_ADDR(base), 0x3E); // Config Rx path for mode1
			MmioWrite32(HWIO_RX_RCVR_PATH1_MODE2_ADDR(base), 0x3F); // Config Rx path for mode2
			MmioWrite32(HWIO_RX_EN_SIGNAL_ADDR(base), 0xC3); // Disable synching of lane rclks using c_rxsync_clk
			MmioWrite32(HWIO_RX_RESECODE_OFFSET_ADDR(base), 0x04); // Offset code for the rescode for RX
			MmioWrite32(HWIO_PARALLEL_RATE_ADDR(base), 0x2F); // Set data width to 20 bits for gen1/2 and 16 bits for gen3
			MmioWrite32(HWIO_PSM_RX_EN_CAL_ADDR(base), 0x00); // Disable optional sampler cal
			MmioWrite32(HWIO_LANE_MODE_ADDR(base), 0x3A); // Set lanes as synchronous; invert tclk, rclk and cdr clock
			MmioWrite32(HWIO_DRVR_LOGIC_CLKDIV_ADDR(base), 0x14); // Enable txvoltmode clock and div5 of source
			MmioWrite32(HWIO_DRVR_CTRL0_ADDR(base), 0x00); // Disable initial loading of txdriver margining
			MmioWrite32(HWIO_DRVR_CTRL1_ADDR(base), 0x0C); // Offset code for rescode for TX
			MmioWrite32(HWIO_DLL_HIGHDATARATE_ADDR(base), 0x15); // Set high data-rate for gen1, gen2 & gen3
			MmioWrite32(HWIO_DRVR_TAP_EN_ADDR(base), 0x0D); // Enable pre and post taps
			MmioWrite32(HWIO_RCVRDONE_THRESH1_ADDR(base), 0x04); // Configure RxEq
			MmioWrite32(HWIO_RXEQ_CTRL_ADDR(base), 0x70); // Configure RxEq
			MmioWrite32(HWIO_RXENGINE_EN0_ADDR(base), 0x12); // Configure RxEq
			MmioWrite32(HWIO_VGA_GAIN_ADDR(base), 0x26); // Configure RxEq
			MmioWrite32(HWIO_PRE_GAIN_ADDR(base), 0x09); // Configure RxEq
			MmioWrite32(HWIO_EQ_INITVAL_ADDR(base), 0x15); // Configure RxEq (optimal value dependent on preset used)
			MmioWrite32(HWIO_VGA_INITVAL_ADDR(base), 0x20); // Configure RxEq
			MmioWrite32(HWIO_CTLE_THRESH_DFE_ADDR(base), 0x02); // Configure RxEq
			MmioWrite32(HWIO_CTLE_TRAIN_TIME_ADDR(base), 0x25); // Configure RxEq
			MmioWrite32(HWIO_CTLE_DFE_OVRLP_TIME_ADDR(base), 0x00); // Configure RxEq
			MmioWrite32(HWIO_RX_MISC_CNTRL0_ADDR(base), 0xBC); // Configure RxEq
			MmioWrite32(HWIO_RXEQ_INITB0_ADDR(base), 0x7F); // Configure RxEq
			MmioWrite32(HWIO_RXEQ_INITB1_ADDR(base), 0x07); // Configure RxEq
			MmioWrite32(HWIO_BIST_MODE_LANENO_SWAP_ADDR(base), 0x00); // Configure RxEq
			MmioWrite32(HWIO_DFE_REFRESH_TIME_ADDR(base), 0x05); // Configure RxEq
			MmioWrite32(HWIO_DFE_ENABLE_TIME_ADDR(base), 0x01); // Configure RxEq
			MmioWrite32(HWIO_TS0_TIMER_ADDR(base), 0x7F); // Set TS0A DLL wait timer to max value
			MmioWrite32(HWIO_DLL0_FTUNE_GAIN_ADDR(base), 0x02); // Set DLL fine tune gain
			MmioWrite32(HWIO_DLL1_FTUNE_GAIN_ADDR(base), 0x02); // Set DLL fine tune gain
			MmioWrite32(HWIO_DFE_GAIN_ADDR(base), 0x12); // Configure RxEq
			MmioWrite32(HWIO_EQ_GAIN_ADDR(base), 0x04); // Configure RxEq
			MmioWrite32(HWIO_OFFSET_GAIN_ADDR(base), 0x04); // Configure RxEq
			MmioWrite32(HWIO_DCC_GAIN_ADDR(base), 0x01); // Set duty cycle correction gain
			MmioWrite32(HWIO_MIXER_CTRL_MODE0_ADDR(base), 0x31); // Set Gen1 mixer resistor load and current
			MmioWrite32(HWIO_MIXER_CTRL_MODE1_ADDR(base), 0x31); // Set Gen2 mixer resistor load and current
			MmioWrite32(HWIO_MIXER_CTRL_MODE2_ADDR(base), 0x03); // Set Gen3 mixer resistor load and current
			MmioWrite32(HWIO_PREAMP_CTRL_MODE0_ADDR(base), 0x00); // Set Gen1 receiver preamp current
			MmioWrite32(HWIO_PREAMP_CTRL_MODE1_ADDR(base), 0x01); // Set Gen2 receiver preamp current
			MmioWrite32(HWIO_PREAMP_CTRL_MODE2_ADDR(base), 0x07); // Set Gen3 receiver preamp current
			MmioWrite32(HWIO_CML_CTRL_MODE0_ADDR(base), 0x09); // Set Gen1 cml clock buffer and cml2cmos current
			MmioWrite32(HWIO_CML_CTRL_MODE1_ADDR(base), 0x09); // Set Gen2 cml clock buffer and cml2cmos current
			MmioWrite32(HWIO_CML_CTRL_MODE2_ADDR(base), 0x1B); // Set Gen3 cml clock buffer and cml2cmos current
			MmioWrite32(HWIO_SIGDET_ENABLES_ADDR(base), 0x21); // Enable sigdet LP mode in PS0,1,2; bypass sigdet pulse width filter
			MmioWrite32(HWIO_SIGDET_CNTRL_ADDR(base), 0xA0); // Set sigdet level
			MmioWrite32(HWIO_SIGDET_DEGLITCH_CNTRL_ADDR(base), 0x08); // Set sigdet glitch filter bandwidth
			MmioWrite32(HWIO_VGA_THRESH_DFE_ADDR(base), 0x01); //Configure RxEq
			MmioWrite32(HWIO_EDAC_INITVAL_ADDR(base), 0x32); // Use 0x32 for short channel, use 0x26 for long channel
		case LaneStart:
		default:
			break;
	}
}

void pcie_phy_common_init(uint64_t cm_ser_base_addr, boolean x8x16_linkmode, uint8_t lane_conf)
{
	uint64_t pcs_base_addr;
	uint64_t lane_base_addr;

	pcs_base_addr = cm_ser_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS;

	// 1. Write 0x11 to AHB2PHY bridge CSR PERIPH_SS_AHB2PHY_TOP_CFG so that writes and reads to/from the PHY use one wait state.
	MmioWrite32(HWIO_PSP_A2P_AHB2PHY_TOP_CFG_ADDR(cm_ser_base_addr + 0x8000), 0x11);

	// 8. Bring CSR bit SW_PWRDN_B high by an SWI write.
	MmioWrite32(HWIO_PSP_PCIE_PHY_POWER_DOWN_CONTROL_ADDR(pcs_base_addr), 0x01);// Release powerdown mode
	// 9. Configure PLL and other functions by SWI writes.
	//    As part of PHY configuration, read PCIe clkgen CSR bits RESTRIM_CODE_STATUS<6:0> and write to PCIe PHY CSR bits QSERVER_COM_RESTRIM_CTRL<7:1>, while writing a �1� to QSERVER_COM_RESTRIM_CTRL<0>.

	MmioWrite32(HWIO_PSP_QSERVER_COM_SYSCLK_EN_SEL_ADDR(cm_ser_base_addr), 0x27);// Select internal diff cml clock inputs
	MmioWrite32(HWIO_PSP_QSERVER_COM_BG_TIMER_ADDR(cm_ser_base_addr), 0x02);// Set bg timer divider for 100MHz refclk
	MmioWrite32(HWIO_PSP_QSERVER_COM_CORE_CLK_EN_ADDR(cm_ser_base_addr), 0x73);// Set PLL divider for each mode and enable coreauxclk
	MmioWrite32(HWIO_PSP_QSERVER_COM_HSCLK_SEL1_ADDR(cm_ser_base_addr), 0x30);// VCO output clock: choose div2 for gen1/2 and div1 for gen3
	MmioWrite32(HWIO_PSP_QSERVER_COM_VCO_TUNE_MAP_ADDR(cm_ser_base_addr), 0x10);// Set mode mapping: mode0 - gen1 & gen2, mode1 - gen3
	MmioWrite32(HWIO_PSP_QSERVER_COM_SVS_MODE_CLK_SEL_ADDR(cm_ser_base_addr), 0x15);// Change digclk divide for gen1 SVS support
	MmioWrite32(HWIO_PSP_QSERVER_COM_BIAS_EN_CLKBUFLR_EN_ADDR(cm_ser_base_addr), 0x0C);// Enable internal clock buffers
	MmioWrite32(HWIO_PSP_QSERVER_COM_CMN_CONFIG_ADDR(cm_ser_base_addr), 0x1C);// Enable switch to coreclk and auxclk; indicate all lanes are synchronous
	MmioWrite32(HWIO_PSP_QSERVER_COM_CORECLK_DIV_ADDR(cm_ser_base_addr), 0x04);// Set coreclk_out to div4 for mode0
	MmioWrite32(HWIO_PSP_QSERVER_COM_PLL_CCTRL_MODE0_ADDR(cm_ser_base_addr), 0x00);// Set mode0 2nd cap of loop filter value
	MmioWrite32(HWIO_PSP_QSERVER_COM_PLL_RCTRL_MODE0_ADDR(cm_ser_base_addr), 0x0D);// Set mode0 PLL RC loop filter value
	MmioWrite32(HWIO_PSP_QSERVER_COM_CP_CTRL_MODE0_ADDR(cm_ser_base_addr), 0x28);// Set mode0 charge pump control value
	MmioWrite32(HWIO_PSP_QSERVER_COM_INTEGLOOP_GAIN0_MODE0_ADDR(cm_ser_base_addr), 0xFB);// Set mode0 integral loop gain
	MmioWrite32(HWIO_PSP_QSERVER_COM_INTEGLOOP_GAIN1_MODE0_ADDR(cm_ser_base_addr), 0x03);// Set mode0 integral loop gain
	MmioWrite32(HWIO_PSP_QSERVER_COM_DEC_START_MODE0_ADDR(cm_ser_base_addr), 0x19);// Set PLL mode0 divider value
	MmioWrite32(HWIO_PSP_QSERVER_COM_LOCK_CMP1_MODE0_ADDR(cm_ser_base_addr), 0x80);// Set PLL lock compare values
	MmioWrite32(HWIO_PSP_QSERVER_COM_LOCK_CMP2_MODE0_ADDR(cm_ser_base_addr), 0x0C);// Set PLL lock compare values
	MmioWrite32(HWIO_PSP_QSERVER_COM_LOCK_CMP3_MODE0_ADDR(cm_ser_base_addr), 0x00);// Set PLL lock compare values
	MmioWrite32(HWIO_PSP_QSERVER_COM_CORECLK_DIV_MODE1_ADDR(cm_ser_base_addr), 0x04);// Set coreclk_out to div4 for mode1
	MmioWrite32(HWIO_PSP_QSERVER_COM_PLL_CCTRL_MODE1_ADDR(cm_ser_base_addr), 0x00);// Set mode1 2nd cap of loop filter value
	MmioWrite32(HWIO_PSP_QSERVER_COM_PLL_RCTRL_MODE1_ADDR(cm_ser_base_addr), 0x0D);// Set mode1 PLL RC loop filter value
	MmioWrite32(HWIO_PSP_QSERVER_COM_CP_CTRL_MODE1_ADDR(cm_ser_base_addr), 0x28);// Set mode1 charge pump control value
	MmioWrite32(HWIO_PSP_QSERVER_COM_INTEGLOOP_GAIN0_MODE1_ADDR(cm_ser_base_addr), 0xFB);// Set mode1 integral loop gain
	MmioWrite32(HWIO_PSP_QSERVER_COM_INTEGLOOP_GAIN1_MODE1_ADDR(cm_ser_base_addr), 0x03);// Set mode1 integral loop gain
	MmioWrite32(HWIO_PSP_QSERVER_COM_DEC_START_MODE1_ADDR(cm_ser_base_addr), 0x14);// Set PLL mode1 divider value
	MmioWrite32(HWIO_PSP_QSERVER_COM_LOCK_CMP1_MODE1_ADDR(cm_ser_base_addr), 0xFF);// Set PLL lock compare values
	MmioWrite32(HWIO_PSP_QSERVER_COM_LOCK_CMP2_MODE1_ADDR(cm_ser_base_addr), 0x13);// Set PLL lock compare values
	MmioWrite32(HWIO_PSP_QSERVER_COM_LOCK_CMP3_MODE1_ADDR(cm_ser_base_addr), 0x00);// Set PLL lock compare values
	MmioWrite32(HWIO_PSP_QSERVER_COM_PLL_IVCO_ADDR(cm_ser_base_addr), 0x0F);// Set VCO current
	MmioWrite32(HWIO_PSP_QSERVER_COM_RESTRIM_CTRL2_ADDR(cm_ser_base_addr), 0x05);// Add offset to lane restrim code
	MmioWrite32(HWIO_PSP_QSERVER_COM_CMN_MODE_ADDR(cm_ser_base_addr), 0x01);// Disable DDR refclk buffer

	// Select sysclk as Vreg clock source (and enable use of external tsync for X8/X16):X4 mode: 0x40 X8 & X16 modes: 0x70
	if(x8x16_linkmode)
		MmioWrite32(HWIO_PSP_QSERVER_COM_CLK_SELECT_ADDR(cm_ser_base_addr), 0x70);
	else
		MmioWrite32(HWIO_PSP_QSERVER_COM_CLK_SELECT_ADDR(cm_ser_base_addr), 0x40);

	MmioWrite32(HWIO_PSP_QSERVER_COM_VREGCLK_DIV1_ADDR(cm_ser_base_addr), 0x22);// Set vregclk divide ratio for gen1/2 & gen3
	MmioWrite32(HWIO_PSP_QSERVER_COM_VREGCLK_DIV2_ADDR(cm_ser_base_addr), 0x00);// Set vregclk divide ratio
	MmioWrite32(HWIO_PSP_QSERVER_COM_RESETSM_CNTRL2_ADDR(cm_ser_base_addr), 0x28);// Bypass restrim

	// Set bit0 to 1; set bits <7:1> to value read from clkgen RESTRIM_CODE_STATUS<6:0> after clkgen calibration
	MmioWrite32(HWIO_PSP_QSERVER_COM_RESTRIM_CTRL_ADDR(cm_ser_base_addr), 0x1 | ((MmioRead32(HWIO_PCIE_CLKGEN_RESTRIM_CODE_STATUS_ADDR))  << 1));

	// Lane 0-3 configuration
	lane_base_addr = cm_ser_base_addr + PSP0_QSERVER_L0_QSERVER_L0_PCIE_LANE_REG_BASE_OFFS;

	for (uint8_t i = 0; i < PCIE_LANE_PER_PHY; i ++) 
	{
		pcie_lane_init(lane_base_addr, LaneConfigure);
		// tie-off unused lanes
		if (0 == (lane_conf & (1 << i))) 
		{
			printf("[PCIe] PHY unused lane %d at LaneBase 0x%lx tie-off!\r\n", i, lane_base_addr);
			MmioWrite32(HWIO_RX_HIGHZ_HIGHRATE_ADDR(lane_base_addr), 0x3);
		}
		lane_base_addr = lane_base_addr + PCIE_LANE_REG_BASE_OFFSET;
	}

	MmioWrite32(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M3P5DB_ADDR(pcs_base_addr), 0x19);// Gen 1, 2 main setting for -3.5dB.
	MmioWrite32(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M3P5DB_ADDR(pcs_base_addr), 0x07);// Gen 1, 2 post setting for -3.5dB.
	MmioWrite32(HWIO_PSP_PCIE_PHY_TXMGN_MAIN_V0_M6DB_ADDR(pcs_base_addr), 0x17);// Gen 1, 2 main setting for -6dB.
	MmioWrite32(HWIO_PSP_PCIE_PHY_TXMGN_POST_V0_M6DB_ADDR(pcs_base_addr), 0x09);// Gen 1, 2 post setting for -6dB.
	MmioWrite32(HWIO_PSP_PCIE_PHY_POWER_STATE_CONFIG_ADDR(pcs_base_addr), 0x3F);// Select PCLK divider for gen1 half-rate
	MmioWrite32(HWIO_PSP_PCIE_PHY_EQ_CONFIG2_ADDR(pcs_base_addr), 0x0B);// Enable early training
	MmioWrite32(HWIO_PSP_PCIE_PHY_PRESET_P10_PRE_ADDR(pcs_base_addr), 0x02);// Adjust Preset10 Pre value
	MmioWrite32(HWIO_PSP_PCIE_PHY_PRESET_P10_POST_ADDR(pcs_base_addr), 0x09);// Adjust Preset10 Post value
	MmioWrite32(HWIO_PSP_PCIE_PHY_PCS_TX_RX_CONFIG_ADDR(pcs_base_addr), 0x64);// Activate Rx path once traffic is detected after transitioning from P1 to P0
	MmioWrite32(HWIO_PSP_PCIE_PHY_TEST_CONTROL_ADDR(pcs_base_addr), HWIO_PSP_PCIE_PHY_TEST_CONTROL_FORCE_REC_DETECTED_BMSK); //Force receiver detected

	// Next write is for X8 & X16 modes only:
	if(x8x16_linkmode) 
		MmioWrite32(HWIO_PSP_QSERVER_COM_RESETSM_CNTRL_ADDR(cm_ser_base_addr), 0x20);// Enable external tsync in X8 & X16 modes

	// 10. Release CSR bit SW_RESET by an SWI write.
	MmioWrite32(HWIO_PSP_PCIE_PHY_SW_RESET_ADDR(pcs_base_addr), 0x00);// Release software reset

	// 11. Set the RSM_START bit in each lane by SWI writes.
	MmioWrite32(HWIO_RSM_START_ADDR(cm_ser_base_addr + PSP0_QSERVER_L0_QSERVER_L0_PCIE_LANE_REG_BASE_OFFS), 0x01);// Start reset power SM
	MmioWrite32(HWIO_RSM_START_ADDR(cm_ser_base_addr + PSP0_QSERVER_L1_QSERVER_L1_PCIE_LANE_REG_BASE_OFFS), 0x01);// Start reset power SM
	MmioWrite32(HWIO_RSM_START_ADDR(cm_ser_base_addr + PSP0_QSERVER_L2_QSERVER_L2_PCIE_LANE_REG_BASE_OFFS), 0x01);// Start reset power SM
	MmioWrite32(HWIO_RSM_START_ADDR(cm_ser_base_addr + PSP0_QSERVER_L3_QSERVER_L3_PCIE_LANE_REG_BASE_OFFS), 0x01);// Start reset power SM

	// 12. Set the PCS_START bit by an SWI write to start the PHY power-up process.
	MmioWrite32(HWIO_PSP_PCIE_PHY_START_CONTROL_ADDR(pcs_base_addr), 0x01);// Start PCS power SM
	// 13. Once calibration is done, the PLL is locked and the PHY is in the P1 power state, signal cm_server_pcie_phystatus goes low.
}

boolean IsPciePhyReady(uint64_t cm_ser_base_addr)
{
	uint32_t phy_st;
	uint32_t count = 0;
	uint64_t base_addr;
	boolean status;

	base_addr = cm_ser_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS;
	//Wait for Phy ready
	phy_st = MmioRead32(HWIO_PSP_PCIE_PHY_PCS_STATUS_ADDR(base_addr));
	while (((phy_st & HWIO_PSP_PCIE_PHY_PCS_STATUS_PHYSTATUS_BMSK) != 0) && (count < 1000)) 
	{
		Hdts_waitForMicroSecs(100000);
		phy_st = MmioRead32(HWIO_PSP_PCIE_PHY_PCS_STATUS_ADDR(base_addr));
		count++;
	}

	if (count < 1000)
	{
		status = TRUE;
		printf("PCIe PHY is Ready! [0x%lx]\r\n", base_addr);
	} 
	else 
	{
		printf("[ERROR] PCIe PHY Timeout waiting for UP! [0x%lx]\r\n", base_addr);
		status = FALSE;
	}

	return status;
}

void pcie_phy_init(uint32_t pcie_ss, PCIE_LINKMODE_t link_mode)
{
	boolean x8x16_linkmode = TRUE;
	uint64_t psp_pcie_base_addr, psp_pcie_base_offs;
	uint16_t lane_config;
	uint16_t preset_disable[16] = {0x20, 0x20, 0x20, 0x20, 
									0x20, 0x20, 0x20, 0x20, 
									0x20, 0x20, 0x20, 0x20, 
									0x20, 0x20, 0x20, 0x20};

	printf("PCIe phy init\r\n");
	//phy reference clocks init
	if (pcie_ss == PCIE_SS_0)
	{
		if (link_mode == LINKMODE_1X16)
			MmioWrite32(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(PCIE0_PCIE_CC_BASE), 0);
		else
			MmioWrite32(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(PCIE0_PCIE_CC_BASE), 2);

		//Set the clk source for A, B, C PCLK's
		MmioWrite32(HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 0x100);
		MmioWrite32(HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 0x1);
		MmioWrite32(HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 0x100);
		MmioWrite32(HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 0x1);
		MmioWrite32(HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 0x100);
		MmioWrite32(HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 0x1);
	}
	else if (pcie_ss == PCIE_SS_1)
	{
		if (link_mode == LINKMODE_1X16)
			MmioWrite32(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(PCIE1_PCIE_CC_BASE), 0);
		else
			MmioWrite32(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(PCIE1_PCIE_CC_BASE), 2);

		MmioWrite32(HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 0x100);
		MmioWrite32(HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 0x1);
		MmioWrite32(HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 0x100);
		MmioWrite32(HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 0x1);
		MmioWrite32(HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 0x100);
		MmioWrite32(HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 0x1);
	}
	else
	{
		printf("[ERROR]PCIe phy init 1. Illegal input parameters!\r\n");
		return;
	}

	//phy reset
	if (pcie_ss == PCIE_SS_0)
	{
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(PCIE0_PCIE_CC_BASE), 0x03);
	    MmioOr32(HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(PCIE0_PCIE_CC_BASE), 0x03);
	    MmioOr32(HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(PCIE0_PCIE_CC_BASE), 0x03);
	    MmioOr32(HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(PCIE0_PCIE_CC_BASE), 0x03);
#if 0
		pcie_set_mode(pice_ss, link_mode);
#else
		switch (link_mode) 
		{
			case LINKMODE_2X8:
				MmioWrite32(TLMM_PCIESS0_LINK_MODE_1, 0x2); 
				MmioWrite32(TLMM_PCIESS0_LINK_MODE_0, 0x1);
				break;
			case LINKMODE_1X8_2X4:
				MmioWrite32(TLMM_PCIESS0_LINK_MODE_1, 0x2);
				break;
			case LINKMODE_3X4:
				break;
			case LINKMODE_1X16:
				MmioWrite32(TLMM_PCIESS0_LINK_MODE_2, 0x4);
				break;
			default:
				return;
			break;
		}
#endif // #if 0
	}
	else if (pcie_ss == PCIE_SS_1)
	{
		//phy reset
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(PCIE1_PCIE_CC_BASE), 0x03);
	    MmioOr32(HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(PCIE1_PCIE_CC_BASE), 0x03);
	    MmioOr32(HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(PCIE1_PCIE_CC_BASE), 0x03);
	    MmioOr32(HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(PCIE1_PCIE_CC_BASE), 0x03);

#if 0
		pcie_set_mode(pcie_ss, link_mode);
#else
		switch (link_mode) 
		{
			case LINKMODE_2X8:
				MmioWrite32(TLMM_PCIESS1_LINK_MODE_1, 0x2); 
				MmioWrite32(TLMM_PCIESS1_LINK_MODE_0, 0x1);
				break;
			case LINKMODE_1X8_2X4:
				MmioWrite32(TLMM_PCIESS1_LINK_MODE_1, 0x2);
				break;
			case LINKMODE_3X4:
				break;
			case LINKMODE_1X16:
				MmioWrite32(TLMM_PCIESS1_LINK_MODE_2, 0x4);
				break;
			default:
				return;
			break;
		}
#endif // #if 0
	}
	else
	{
		printf("[ERROR]PCIe phy init 2. Illegal input parameters!\r\n");
		return;
	}

	//power-on reset
	if (pcie_ss == PCIE_SS_0)
	{
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_AA_MISC_ADDR(PCIE0_PCIE_CC_BASE), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK);
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_AB_MISC_ADDR(PCIE0_PCIE_CC_BASE), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK);
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_B_MISC_ADDR(PCIE0_PCIE_CC_BASE), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK);
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_C_MISC_ADDR(PCIE0_PCIE_CC_BASE), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK);
		MmioAnd32(HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(PCIE0_PCIE_CC_BASE), 0);
		MmioAnd32(HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(PCIE0_PCIE_CC_BASE), 0);
		MmioAnd32(HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(PCIE0_PCIE_CC_BASE), 0);
		MmioAnd32(HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(PCIE0_PCIE_CC_BASE), 0);
	}
	else if (pcie_ss == PCIE_SS_1)
	{
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_AA_MISC_ADDR(PCIE1_PCIE_CC_BASE), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK);
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_AB_MISC_ADDR(PCIE1_PCIE_CC_BASE), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK);
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_B_MISC_ADDR(PCIE1_PCIE_CC_BASE), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK);
		MmioOr32(HWIO_PCIE_CC_PCIE_PHY_C_MISC_ADDR(PCIE1_PCIE_CC_BASE), HWIO_PCIE_CC_PCIE_PHY_AA_MISC_CLK_REBUF_EN_BMSK);
		MmioAnd32(HWIO_PCIE_CC_PCIE_PHY_AA_RESETR_ADDR(PCIE1_PCIE_CC_BASE), 0);
		MmioAnd32(HWIO_PCIE_CC_PCIE_PHY_AB_RESETR_ADDR(PCIE1_PCIE_CC_BASE), 0);
		MmioAnd32(HWIO_PCIE_CC_PCIE_PHY_B_RESETR_ADDR(PCIE1_PCIE_CC_BASE), 0);
		MmioAnd32(HWIO_PCIE_CC_PCIE_PHY_C_RESETR_ADDR(PCIE1_PCIE_CC_BASE), 0);
	}
	else
	{
		printf("[ERROR]PCIe phy init 3. Illegal input parameters!\r\n");
		return;
	}

	psp_pcie_base_offs = PSP1_CM_SERVER_PCIE_SW_BASE - PSP0_CM_SERVER_PCIE_SW_BASE; //0x100000
	if (pcie_ss == PCIE_SS_0)
		psp_pcie_base_addr = PSP0_CM_SERVER_PCIE_SW_BASE;
	else
		psp_pcie_base_addr = PSP4_CM_SERVER_PCIE_SW_BASE;

	switch (link_mode) 
	{
		case LINKMODE_2X8:
			x8x16_linkmode = TRUE;
			lane_config = 0xffff;
			for (uint8_t i = 0; i < PCIE_PHY_PER_SS; i++) 
			{
				pcie_phy_common_init(psp_pcie_base_addr, x8x16_linkmode, lane_config);
				psp_pcie_base_addr += psp_pcie_base_offs;
				lane_config >>= PCIE_LANE_PER_PHY;
			}
			break;
		case LINKMODE_1X8_2X4:
			x8x16_linkmode = TRUE;
			lane_config = 0xffff;
			for (uint8_t i = 0; i < PCIE_PHY_PER_SS; i++) 
			{
				pcie_phy_common_init(psp_pcie_base_addr, x8x16_linkmode, lane_config);
				psp_pcie_base_addr += psp_pcie_base_offs;
				lane_config >>= PCIE_LANE_PER_PHY;
				if (i > 1)
					x8x16_linkmode = FALSE;
			}
			break;
		case LINKMODE_3X4:
			x8x16_linkmode = FALSE;
			lane_config = 0xffff;
			for (uint8_t i = 0; i < PCIE_PHY_PER_SS; i++) 
			{
				pcie_phy_common_init(psp_pcie_base_addr, x8x16_linkmode, lane_config);
				psp_pcie_base_addr += psp_pcie_base_offs;
				lane_config >>= PCIE_LANE_PER_PHY;
			}
			break;
		case LINKMODE_1X16:
			x8x16_linkmode = TRUE;
			lane_config = 0xffff;
			for (uint8_t i = 0; i < PCIE_PHY_PER_SS; i++) 
			{
				pcie_phy_common_init(psp_pcie_base_addr, x8x16_linkmode, lane_config);
				psp_pcie_base_addr += psp_pcie_base_offs;
				lane_config >>= PCIE_LANE_PER_PHY;
			}
			break;
		default:
			return;
		break;
	}

	if (pcie_ss == PCIE_SS_0)
		psp_pcie_base_addr = PSP0_CM_SERVER_PCIE_SW_BASE;
	else
		psp_pcie_base_addr = PSP4_CM_SERVER_PCIE_SW_BASE;

	for (uint8_t i = 0; i < 4; i++) 
	{
    	IsPciePhyReady(psp_pcie_base_addr);
    	psp_pcie_base_addr += psp_pcie_base_offs;
	}

	//Program any any disabled presets
	if (pcie_ss == PCIE_SS_0)
		psp_pcie_base_addr = PSP0_CM_SERVER_PCIE_SW_BASE;
	else
		psp_pcie_base_addr = PSP4_CM_SERVER_PCIE_SW_BASE;

	//all 4 lanes for all 4 PHY's for this SS
	for (uint8_t i = 0; i < 4; i++) 
	{
		printf("PCIe program any any disabled presets 0x%lx\r\n", psp_pcie_base_addr);
		MmioWrite32(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_L_ADDR(psp_pcie_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS),
		  (uint32_t)(preset_disable[0 + (4 * i)] & 0xff));
		MmioWrite32(HWIO_PSP_PCIE_PHY_L0_PRESET_DSBL_H_ADDR(psp_pcie_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS),
		  (uint32_t)(preset_disable[0 + (4 * i)] >> 8));
		MmioWrite32(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_L_ADDR(psp_pcie_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS),
		  (uint32_t)(preset_disable[1 + (4 * i)] & 0xff));
		MmioWrite32(HWIO_PSP_PCIE_PHY_L1_PRESET_DSBL_H_ADDR(psp_pcie_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS),
		  (uint32_t)(preset_disable[1 + (4 * i)] >> 8));
		MmioWrite32(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_L_ADDR(psp_pcie_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS),
		  (uint32_t)(preset_disable[2 + (4 * i)] & 0xff));
		MmioWrite32(HWIO_PSP_PCIE_PHY_L2_PRESET_DSBL_H_ADDR(psp_pcie_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS),
		  (uint32_t)(preset_disable[2 + (4 * i)] >> 8));
		MmioWrite32(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_L_ADDR(psp_pcie_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS),
		  (uint32_t)(preset_disable[3 + (4 * i)] & 0xff));
		MmioWrite32(HWIO_PSP_PCIE_PHY_L3_PRESET_DSBL_H_ADDR(psp_pcie_base_addr + PSP0_PCIE_PHY_PCIE_PHY_PCIE_PCS_REG_BASE_OFFS),
		  (uint32_t)(preset_disable[3 + (4 * i)] >> 8));
		psp_pcie_base_addr += psp_pcie_base_offs;
	}
}

/**
Set ECAM blocker for core

@param PciConfig              PCI_ROOT_BRIDGE_CONFIG handle for the root bridge
**/
void pcie_set_ecam_blocker(PCIE_Config_t* pcie_conf, uint64_t base_addr, uint64_t size)
{
	if (size == 0) 
	{
		//Disable ECAM blocker
		MmioAnd32(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(pcie_conf->ParfBase), ~HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_BMSK);
	} 
	else 
	{
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_LO_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_HI_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr >> 32));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_LO_ADDR(pcie_conf->ParfBase), (uint32_t)((base_addr + size - 1) & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_HI_ADDR(pcie_conf->ParfBase), (uint32_t)((base_addr + size - 1) >> 32));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_LO_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_HI_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr >> 32));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_LO_ADDR(pcie_conf->ParfBase), (uint32_t)((base_addr + size - 1) & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_HI_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr >> 32));
		//Enable ECAM blocker
		MmioOr32(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(pcie_conf->ParfBase), HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_BMSK);
	}
}

/**
Set ECAM #2 blocker for core

@param PciConfig              PCI_ROOT_BRIDGE_CONFIG handle for the root bridge
**/
void pcie_set_ecam_blocker2(PCIE_Config_t* pcie_conf, uint64_t base_addr, uint64_t size)
{
	if (size == 0) 
	{
		//Disable ECAM #2 blocker
		MmioAnd32(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(pcie_conf->ParfBase), ~HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_RANGE2_BMSK);
	} 
	else 
	{
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_LO_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_BASE_2_HI_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr >> 32));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_LO_ADDR(pcie_conf->ParfBase), (uint32_t)((base_addr + size - 1) & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_WR_LIMIT_2_HI_ADDR(pcie_conf->ParfBase), (uint32_t)((base_addr + size - 1) >> 32));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_LO_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_BASE_2_HI_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr >> 32));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_LO_ADDR(pcie_conf->ParfBase), (uint32_t)((base_addr + size - 1) & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_BLOCK_SLV_AXI_RD_LIMIT_2_HI_ADDR(pcie_conf->ParfBase), (uint32_t)(base_addr >> 32));
		//Enable ECAM blocker
		MmioOr32(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(pcie_conf->ParfBase), HWIO_PCIE30_PARF_SYS_CTRL_ECAM_BLOCKER_EN_RANGE2_BMSK);
	}
}

/**
Set ECAM offset removal for core

@param PciConfig              PCI_ROOT_BRIDGE_CONFIG handle for the root bridge
**/
void pcie_set_ecam_offset_removal(PCIE_Config_t* pcie_conf, uint64_t offset, uint64_t size)
{
	if (size == 0) 
	{
		//Disable offset removal
		MmioAnd32(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(pcie_conf->ParfBase), ~HWIO_PCIE30_PARF_SYS_CTRL_ECAM_REMOVE_OFFSET_EN_BMSK);
	} 
	else 
	{
		MmioWrite32(HWIO_PCIE30_PARF_ECAM_BASE_LO_ADDR(pcie_conf->ParfBase), (uint32_t)(pcie_conf->PcieBase & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_ECAM_BASE_HI_ADDR(pcie_conf->ParfBase), (uint32_t)((uint32_t)(pcie_conf->PcieBase >> 32)));
		MmioWrite32(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_LO_ADDR(pcie_conf->ParfBase), (uint32_t)((pcie_conf->PcieBase + offset) & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_BASE_HI_ADDR(pcie_conf->ParfBase), (uint32_t)((pcie_conf->PcieBase + offset) >> 32));
		MmioWrite32(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_LO_ADDR(pcie_conf->ParfBase), (uint32_t)(((pcie_conf->PcieBase + offset) + size - 1) & 0xffffffff));
		MmioWrite32(HWIO_PCIE30_PARF_ECAM_OFFSET_REMOVAL_LIMIT_HI_ADDR(pcie_conf->ParfBase), (uint32_t)(((pcie_conf->PcieBase + offset) + size - 1) >> 32));
		//Enable Offset removal
		MmioOr32(HWIO_PCIE30_PARF_SYS_CTRL_ADDR(pcie_conf->ParfBase), HWIO_PCIE30_PARF_SYS_CTRL_ECAM_REMOVE_OFFSET_EN_BMSK);
	}
}

void pcie_init_aspm(PCIE_Config_t* pcie_conf)
{
	//Unlock DBI access
	MmioOr32(HWIO_MISC_CONTROL_1_OFF_ADDR(pcie_conf->PcieBase), HWIO_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_BMSK);

	// Number of Fast Training (NFTS) Sequence under common clock:NftsCommon
	MmioAndThenOr32(HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(pcie_conf->PcieBase),
		~HWIO_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_BMSK,
		0x80 << HWIO_ACK_F_ASPM_CTRL_OFF_COMMON_CLK_N_FTS_SHFT);
	pcie_conf->AspmConfig.NFTSCommon = 0x80;

	//Number of Fast Training (NFTS) Sequence:NFTS
	MmioAndThenOr32(HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(pcie_conf->PcieBase),
		~HWIO_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS_BMSK,
		0x80 << HWIO_ACK_F_ASPM_CTRL_OFF_ACK_N_FTS_SHFT);
	pcie_conf->AspmConfig.NFTS = 0x80;

	// L0s Entrance Latency:L0sEntry:5 us
	MmioAndThenOr32(HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(pcie_conf->PcieBase),
		~HWIO_ACK_F_ASPM_CTRL_OFF_L0S_ENTRANCE_LATENCY_BMSK,
		0x4 << HWIO_ACK_F_ASPM_CTRL_OFF_L0S_ENTRANCE_LATENCY_SHFT);
	pcie_conf->AspmConfig.L0Entry = 0x4;

	//L1 Entrance Latency:L1Entry:7 us
	MmioAndThenOr32(HWIO_ACK_F_ASPM_CTRL_OFF_ADDR(pcie_conf->PcieBase),
		~HWIO_ACK_F_ASPM_CTRL_OFF_L1_ENTRANCE_LATENCY_BMSK,
		0x7 << HWIO_ACK_F_ASPM_CTRL_OFF_L1_ENTRANCE_LATENCY_SHFT);
	pcie_conf->AspmConfig.L1Entry = 0x7;

	//Number of Fast Training (NFTS) Sequence for gen2:Gen23Nfts
	MmioAndThenOr32(HWIO_GEN2_CTRL_OFF_ADDR(pcie_conf->PcieBase),
		~HWIO_GEN2_CTRL_OFF_FAST_TRAINING_SEQ_BMSK,
		0x90 << HWIO_GEN2_CTRL_OFF_FAST_TRAINING_SEQ_SHFT);
	pcie_conf->AspmConfig.Gen23Nfts = 0x90;

	//L0s Exit Latency:L0s Exit: 110b  256-512ns =  PHY supports max 386ns = 193 pclk @ 500MHz cycles and gen3
	MmioAndThenOr32(HWIO_LINK_CAPABILITIES_REG_ADDR(pcie_conf->PcieBase),
		~HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY_BMSK,
		0x04 << HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY_SHFT);
	pcie_conf->AspmConfig.L0Exit = 0x04;

	// L1 Exit Latency:L1ExitLatency:L1 Exit 4585 = 9.17us @ 500Mhz and gen3
	MmioAndThenOr32(HWIO_LINK_CAPABILITIES_REG_ADDR(pcie_conf->PcieBase),
		~HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY_BMSK,
		0x04 << HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY_SHFT);
	pcie_conf->AspmConfig.L1Exit = 0x04;

	// Lock DBI access
	MmioAnd32(HWIO_MISC_CONTROL_1_OFF_ADDR(pcie_conf->PcieBase), ~HWIO_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_BMSK);

	// Set the same parameters for common clock. MISC chooses CS1 and it allows us to change
	// the parameters for asynchronous clock mode. We need to set CS2 to be able to access
	// the registers for common clock mode. CS2 and MISC(CS1) should not be asserted at the same time
	MmioOr32(HWIO_PCIE30_ELBI_CS2_ENABLE_ADDR(pcie_conf->ElbiBase), HWIO_PCIE30_ELBI_CS2_ENABLE_ENABLE_BMSK);

	//L0s Exit Latency:L0sExitLatency:512 ns to less than 1 us
	MmioAndThenOr32(HWIO_LINK_CAPABILITIES_REG_ADDR(pcie_conf->PcieBase),
		~HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY_BMSK,
		0x06 << HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L0S_EXIT_LATENCY_SHFT);

	// L1 Exit Latency:L1ExitLatency:8 �s to less than 16 �
	MmioAndThenOr32(HWIO_LINK_CAPABILITIES_REG_ADDR(pcie_conf->PcieBase),
		~HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY_BMSK,
		0x04 << HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_L1_EXIT_LATENCY_SHFT);

	MmioAnd32(HWIO_PCIE30_ELBI_CS2_ENABLE_ADDR(pcie_conf->ElbiBase), ~HWIO_PCIE30_ELBI_CS2_ENABLE_ENABLE_BMSK);
}

void pcie_set_pipe_loopback(PCIE_Config_t* pcie_conf)
{
	if (pcie_conf->Loopback == 0 || pcie_conf->Loopback > 3) // not pipe/phy/parallel
		return;
	if (pcie_conf->Loopback == 1) { // pipe loopback mode
		reg_base_write(pcie_conf->PcieBase, GEN3_RELATED_OFF, GEN3_EQUALIZATION_DISABLE, 1);
		reg_base_write(pcie_conf->PcieBase, PIPE_LOOPBACK_CONTROL_OFF, PIPE_LOOPBACK, 1);
		reg_base_write(pcie_conf->PcieBase, PORT_LINK_CTRL_OFF, LOOPBACK_ENABLE, 1);
		printf("in PIPE loopback mode.\n");
	}
}

/**
Configures a given viewport with the given parameters

@param BaseAddress     Base address of the CM register.
@param Index        Viewport index
@param Ctrl1        Control register 1
@param Ctrl2        Control register 2
@param MemBase        Memory base address of the viewport that this
config takes effect.
@param MemLimit        Lower 32 bit address of the memory range limit
@param PciBase         Translated PCI address

**/
void pcie_conf_viewport(uint64_t BaseAddress,
  uint32_t Index,
  uint32_t Ctrl1,
  uint32_t Ctrl2,
  uint64_t MemBase,
  uint64_t MemLimit,
  uint64_t PciBase)
{
	MmioWrite32(HWIO_IATU_VIEWPORT_OFF_ADDR(BaseAddress), Index);
	MmioWrite32(HWIO_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_ADDR(BaseAddress), Ctrl1);	
	MmioWrite32(HWIO_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_ADDR(BaseAddress), Ctrl2);
	MmioWrite32(HWIO_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_ADDR(BaseAddress), MemBase & 0xFFFFFFFF);
	MmioWrite32(HWIO_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_ADDR(BaseAddress), MemBase >> 32);
	MmioWrite32(HWIO_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_ADDR(BaseAddress), MemLimit & 0xFFFFFFFF);
	MmioWrite32(HWIO_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(BaseAddress), PciBase & 0xFFFFFFFF);
	MmioWrite32(HWIO_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_ADDR(BaseAddress), PciBase >> 32);
}

void pcie_conf_iatu(PCIE_Config_t* pcie_conf)
{
	uint32_t viewport_index = 0;

	//config for bus 1
	pcie_conf_viewport(pcie_conf->PcieBase,
		viewport_index,
		4,
		(uint32_t)((1 << 31) | (1 << 28)),
		ECAM_BUS_ADDRESS_SIZE,
		2 * ECAM_BUS_ADDRESS_SIZE - 1,
		(pcie_conf->ResourceMap.Res[TypeBus].Start + 1) * (1 << 24));

	//config for all other buses
	viewport_index++;
	pcie_conf_viewport(pcie_conf->PcieBase,
		viewport_index,
		5,
		(uint32_t)((1 << 31) | (1 << 28)),
		2 * ECAM_BUS_ADDRESS_SIZE,
		pcie_conf->ResourceMap.Res[TypeBus].End * ECAM_BUS_ADDRESS_SIZE - 1,
		(pcie_conf->ResourceMap.Res[TypeBus].Start + 2) * (1 << 24));

	// io read
	if (pcie_conf->ResourceMap.Res[TypeIo].Start < pcie_conf->ResourceMap.Res[TypeIo].End) 
	{
		viewport_index++;
		pcie_conf_viewport(pcie_conf->PcieBase,
			viewport_index,
			2,
			(uint32_t)1 << 31,
			pcie_conf->ResourceMap.Res[TypeIo].Start,
			pcie_conf->ResourceMap.Res[TypeIo].End - 1,
			pcie_conf->ResourceMap.Res[TypeIo].Base);
	}
	// Mem32
	if (pcie_conf->ResourceMap.Res[TypeMem32].Start < pcie_conf->ResourceMap.Res[TypeMem32].End) 
	{
		viewport_index++;
		pcie_conf_viewport(pcie_conf->PcieBase,
			viewport_index,
			0,
			(uint32_t)1 << 31,
			pcie_conf->ResourceMap.Res[TypeMem32].Start,
			pcie_conf->ResourceMap.Res[TypeMem32].End - 1,
			pcie_conf->ResourceMap.Res[TypeMem32].Base);
	}
	// Mem64
	if (pcie_conf->ResourceMap.Res[TypeMem64].Start < pcie_conf->ResourceMap.Res[TypeMem64].End) 
	{
		viewport_index++;
		pcie_conf_viewport(pcie_conf->PcieBase,
			viewport_index,
			0,
			(uint32_t)1 << 31,
			pcie_conf->ResourceMap.Res[TypeMem64].Start,
			pcie_conf->ResourceMap.Res[TypeMem64].End - 1,
			pcie_conf->ResourceMap.Res[TypeMem64].Base);
	}
	// PMem32
	if (pcie_conf->ResourceMap.Res[TypePMem32].Start < pcie_conf->ResourceMap.Res[TypePMem32].End) 
	{
		viewport_index++;
		pcie_conf_viewport(pcie_conf->PcieBase,
			viewport_index,
			0,
			(uint32_t)1 << 31,
			pcie_conf->ResourceMap.Res[TypePMem32].Start,
			pcie_conf->ResourceMap.Res[TypePMem32].End - 1,
			pcie_conf->ResourceMap.Res[TypePMem32].Base);
	}
	// PMem64
	if (pcie_conf->ResourceMap.Res[TypePMem64].Start < pcie_conf->ResourceMap.Res[TypePMem64].End) 
	{
		viewport_index++;
		pcie_conf_viewport(pcie_conf->PcieBase,
	  		viewport_index,
	  		0,
	  		(uint32_t)1 << 31,
	  		pcie_conf->ResourceMap.Res[TypePMem64].Start,
	  		pcie_conf->ResourceMap.Res[TypePMem64].End - 1,
	  		pcie_conf->ResourceMap.Res[TypePMem64].Base);
	}

	//Clear remaining IATU windows
	while (viewport_index < MAX_IATU_VIEWPORTS) 
	{
		pcie_conf_viewport(pcie_conf->PcieBase, viewport_index, 0, 0, 0, 0, 0);
		viewport_index++;
	}
}

/**
Initialize PCIe width (x1, x2, x4, x8 , x16)

@param RootBridge               Pointer to RootBridge instance for this root bridge.
**/
void pcie_set_width(PCIE_Config_t *pcie_conf, PCIE_WIDTH_t width)
{
	uint32_t link_cap;

	//Always Set NUM_LANES to 1 in GEN2_CTRL_OFF
	MmioAndThenOr32(HWIO_GEN2_CTRL_OFF_ADDR(pcie_conf->PcieBase),
		~HWIO_GEN2_CTRL_OFF_NUM_OF_LANES_BMSK,
		(1 << HWIO_GEN2_CTRL_OFF_NUM_OF_LANES_SHFT));

	if (width != WIDTH_DEFAULT)
	{
		printf("PCIe width x%d requested\r\n", width);
		link_cap = (width << 1) - 1;
		MmioAndThenOr32(HWIO_PORT_LINK_CTRL_OFF_ADDR(pcie_conf->PcieBase),
			~HWIO_PORT_LINK_CTRL_OFF_LINK_CAPABLE_BMSK,
			(link_cap << HWIO_PORT_LINK_CTRL_OFF_LINK_CAPABLE_SHFT));
		MmioAndThenOr32(HWIO_PORT_FORCE_OFF_ADDR(pcie_conf->PcieBase),
			~HWIO_PORT_FORCE_OFF_LINK_NUM_BMSK, width);
		MmioAndThenOr32(HWIO_LINK_CAPABILITIES_REG_ADDR(pcie_conf->PcieBase),
			~HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_WIDTH_BMSK,
			(uint32_t)width << HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_WIDTH_SHFT);
	}
}

void pcie_set_speed(PCIE_Config_t *pcie_conf, PCIE_SPEED_t speed)
{
	printf("Set PCIe Speed to Gen%d\r\n", (speed));
	if (speed >= SPEED_GEN1 && speed <= SPEED_GEN3) 
	{
		MmioAndThenOr32(HWIO_LINK_CAPABILITIES_REG_ADDR(pcie_conf->PcieBase),
	 		~HWIO_LINK_CAPABILITIES_REG_PCIE_CAP_MAX_LINK_SPEED_BMSK,
			(uint32_t)speed);
		MmioAndThenOr32(HWIO_LINK_CONTROL2_LINK_STATUS2_REG_ADDR(pcie_conf->PcieBase),
			~HWIO_LINK_CONTROL2_LINK_STATUS2_REG_PCIE_CAP_TARGET_LINK_SPEED_BMSK,
			(uint32_t)speed);
	} 
	else 
	{
		printf("[PCIe] speed = auto negotiation\r\n");
	}

	if (speed == SPEED_AUTO_NEG || speed == SPEED_GEN3) 
	{
		// 9000771418 B2-Medium Gen3: During Equalization, Core Might Send TS1s with Reset EIEOS Interval (REI)
		// Workaround: Program the EQ_EIEOS_CNT field in GEN3_RELATED_OFF to0x1.
		// 10 0 RWS Equalization EIEOS Count Reset Disable
		// Disable requesting reset of EIEOS count during equalization.

		// Gen3 Receiver Impedance ZRX-DC Not Compliant
		// Synopsys Core Consultant does not provide a way to change the default value of the
		// "GEN3_ZRXDC_NONCOMPL" field in the Gen3 Control Register (offset 0x890 in the controller).
		// The Hawker PHY is compliant with ZRX-DC in Gen3 mode.
		// And the register's default value is non-compliant.
		// Match hardware definition.
		// 0 = compliant
		// 1 = non-compliant
		//
		MmioAndThenOr32(HWIO_GEN3_RELATED_OFF_ADDR(pcie_conf->PcieBase), ~1, (1 << 10));
	}
}

void pcie_hide_ex_capability(PCIE_Config_t* pcie_conf, uint16_t cap_id)
{
	uint16_t capability, prev_capability;
	uint32_t pcie_cap_hdr;
	capability = PCIE_CAPABILITY_BASE_OFFSET;
	prev_capability = 0;
	pcie_cap_hdr = 0;

	//Find the capability and it's previous capability
	while (capability != 0) 
	{
		pcie_cap_hdr = MmioRead32(pcie_conf->PcieBase + capability);
		if ((pcie_cap_hdr & 0xffff) == cap_id) 
	  		break;
		prev_capability = capability;
		capability = (pcie_cap_hdr >> 20);
	}

	if (capability != 0 && prev_capability != 0) 
	{
		//Modify the previous capability header next pointer to point to the next capability
		MmioAndThenOr32(pcie_conf->PcieBase + prev_capability, 0x000fffff, pcie_cap_hdr & 0xfff00000);
	}
}

void pcie_lane_equalization(PCIE_Config_t *pcie_conf, PCIE_SLOT_CONF_t *slot_conf)
{
	///Lanes in 0 - 31 order
	uint16_t lane_eq_ctrl[32] =
	{
        0x6008, 0x6008, 0x6008, 0x6008,
        0x6008, 0x6008, 0x6008, 0x6008,
        0x6008, 0x6008, 0x6008, 0x6008,
        0x6008, 0x6008, 0x6008, 0x6008,
        0x6008, 0x6008, 0x6008, 0x6008,
        0x6008, 0x6008, 0x6008, 0x6008,
        0x6008, 0x6008, 0x6008, 0x6008,
        0x6008, 0x6008, 0x6008, 0x6008,
	};
	uint32_t lane_pair_eq_val = 0;
	uint32_t lane_index = 0;

	while (lane_index < slot_conf->NumLanes) 
	{
		//Pair the lanes up and write the HWIO_LANE_EQUALIZATION_CONTROLXX_REG_ADDR
		lane_pair_eq_val = lane_eq_ctrl[lane_index];
		lane_index++;
		if (lane_index < slot_conf->NumLanes) {
			lane_pair_eq_val |= (lane_eq_ctrl[lane_index]) << 16;
			lane_index++;
		}
		MmioWrite32(HWIO_SPCIE_CAP_OFF_0CH_REG_ADDR(pcie_conf->PcieBase + sizeof(uint32_t) * ((lane_index - 1) >> 1)), lane_pair_eq_val);
	}
}

void pcie_root_bridge_init(PCIE_Config_t *pcie_conf, PCIE_SLOT_CONF_t *slot_conf)
{
	uint32_t next_cap_offset;
	uint32_t cnt = 0;

	//set base address
	MmioWrite32(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_ADDR(pcie_conf->ParfBase), (uint32_t)(pcie_conf->PcieSize & 0xffffffff));
	MmioWrite32(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_LO_ADDR(pcie_conf->ParfBase), (uint32_t)(pcie_conf->PcieSize & 0xffffffff));
	MmioWrite32(HWIO_PCIE30_PARF_SLV_ADDR_SPACE_SIZE_HI_ADDR(pcie_conf->ParfBase), (uint32_t)((pcie_conf->PcieSize >> 32) & 0xffffffff));
	MmioWrite32(HWIO_PCIE30_PARF_DBI_BASE_ADDR_LO_ADDR(pcie_conf->ParfBase), (uint32_t)(pcie_conf->PcieBase & 0xffffffff));
	MmioWrite32(HWIO_PCIE30_PARF_DBI_BASE_ADDR_HI_ADDR(pcie_conf->ParfBase), (uint32_t)((pcie_conf->PcieBase >> 32) & 0xffffffff));

	//***PARF programming***
	MmioWrite32(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ADDR(pcie_conf->ParfBase), 0x00003e8);
	MmioOr32(HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ADDR(pcie_conf->ParfBase), HWIO_PCIE30_PARF_ATS_INV_TIMEOUT_AUX_ENABLE_BMSK);
	//RC mode
	MmioWrite32(HWIO_PCIE30_PARF_DEVICE_TYPE_ADDR(pcie_conf->ParfBase), HWIO_PCIE30_PARF_DEVICE_TYPE_DEVICE_TYPE_RC_FVAL);
	//Set Segment Id
	MmioWrite32(HWIO_PCIE30_PARF_SEGMENT_ID_ADDR(pcie_conf->ParfBase), pcie_conf->ResourceMap.SegmentNumber & HWIO_PCIE30_PARF_SEGMENT_ID_SEGMENT_ID_BMSK);
	//Disable MSI generation halting
	MmioOr32(HWIO_PCIE30_PARF_DEBUG_CONFIG_ADDR(pcie_conf->ParfBase), HWIO_PCIE30_PARF_DEBUG_CONFIG_MSI_HALT_DISABLE_BMSK);
	//Program IDO
	if (pcie_conf->IdBasedOrdering == PCIE_OPTION_DISABLE) {
		MmioOr32(HWIO_PCIE30_PARF_DEBUG_CONFIG_ADDR(pcie_conf->ParfBase), HWIO_PCIE30_PARF_DEBUG_CONFIG_IDO_DISABLE_BMSK);
	}
	//Program SPARE0 for QCTDD02784854 Wrong page size encoding on ATS response and ATS Invalidation request
	MmioOr32(HWIO_PCIE30_PARF_SPARE_0_1_BITS_ADDR(pcie_conf->ParfBase), (0x0001 & HWIO_PCIE30_PARF_SPARE_0_1_BITS_SPARE_0_BMSK));

	//Poised TLP processing
	MmioAndThenOr32(HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_ADDR(pcie_conf->ParfBase),
		~HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_RRESP_BMSK,
		HWIO_PCIE30_PARF_SLAVE_AXI_ERROR_REPORT_AXI_SLAVE_ERROR_POISONED_RDATA_EN_BMSK);

	//Block on chip address space to go on bus
	pcie_set_ecam_blocker(pcie_conf,
		pcie_conf->PcieBase + pcie_conf->MaxFunctionOnRootBridge * ECAM_FUNCTION_ADDRESS_SIZE,
		ECAM_BUS_ADDRESS_SIZE - pcie_conf->MaxFunctionOnRootBridge * ECAM_FUNCTION_ADDRESS_SIZE);

	////Block requests for device > 0 on bus 1
	pcie_set_ecam_blocker2(pcie_conf, pcie_conf->PcieBase + ECAM_BUS_ADDRESS_SIZE + ECAM_DEVICE_ADDRESS_SIZE,
		ECAM_BUS_ADDRESS_SIZE - ECAM_DEVICE_ADDRESS_SIZE);

	//Configure system for ECAM
	pcie_set_ecam_offset_removal(pcie_conf, ECAM_BUS_ADDRESS_SIZE, ECAM_BUS_ADDRESS_SIZE * (pcie_conf->ResourceMap.Res[TypeBus].End) - 1);

	//DBI and ELBI space programming
	pcie_init_aspm(pcie_conf);

	// set pipe loopback
	// pcie_set_pipe_loopback(pcie_conf);

	//Configure iATU
	pcie_conf_iatu(pcie_conf);

	//Unlock DBI write access
	MmioOr32(HWIO_MISC_CONTROL_1_OFF_ADDR(pcie_conf->PcieBase), HWIO_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_BMSK);

	//Setup Vendor and Device Id's
	MmioWrite32(HWIO_TYPE1_DEV_ID_VEND_ID_REG_ADDR(pcie_conf->PcieBase), (DEVICE_PCIE_0401 << 16) | VENDOR_17CB);

	// 1. Write 0x11 to AHB2PHY bridge CSR PERIPH_SS_AHB2PHY_TOP_CFG so that writes and reads to/from the PHY use one wait state.
	// MmioWrite32(HWIO_PCIE_CLKGEN_A2P_AHB2PHY_TOP_CFG_ADDR, 0x11); // crash on Rumi. set in InitPCIePhy() for SDP
	// 2. Write 0x15501 to PCIe controller CSR GEN3_EQ_FB_MODE_DIR_CHANGE to set the rxeq completion window to 8, the pre and post cursor deltas to 5 and the min run time to 1ms.
	MmioWrite32(HWIO_GEN3_EQ_FB_MODE_DIR_CHANGE_OFF_ADDR(pcie_conf->PcieBase), 0x15501); // was 0x8900 for Rumi
	// 3. Set PCIe controller bit GEN3_EQ_PHASE23_EXIT_MODE of CSR GEN3_RELATED to a '0' so Gen3 exit occurs after a 24ms timeout during rxeq training.
	// defaut value of GEN3_EQ_PHASE23_EXIT_MODE is 0

	pcie_set_width(pcie_conf, slot_conf->SlotInfoProtocol.DataWidth);
	pcie_set_speed(pcie_conf, slot_conf->SlotInfoProtocol.MaxSpeed);

	//Disable upconfigure support & resizing
	MmioAnd32(HWIO_MULTI_LANE_CONTROL_OFF_ADDR(pcie_conf->PcieBase), ~HWIO_MULTI_LANE_CONTROL_OFF_UPCONFIGURE_SUPPORT_BMSK);
	MmioOr32(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(pcie_conf->PcieBase), HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_HW_AUTO_WIDTH_DISABLE_BMSK);

	pcie_hide_ex_capability(pcie_conf, PCI_EXPRESS_EXTENDED_CAPABILITY_L1SS_ID);

	//Hide MSI-x capabilty
	next_cap_offset = MmioRead32(pcie_conf->PcieBase + 0xb0); //Synopsys offset
	MmioAndThenOr32(HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_ADDR(pcie_conf->PcieBase),
		~HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_NEXT_PTR_BMSK,
		next_cap_offset & HWIO_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_REG_PCIE_CAP_NEXT_PTR_BMSK);

	//Set Bridge to INTA
	MmioAndThenOr32(HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_ADDR(pcie_conf->PcieBase),
		~HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_INT_PIN_BMSK,
		0x01 << HWIO_BRIDGE_CTRL_INT_PIN_INT_LINE_REG_INT_PIN_SHFT);

	//Disable auto width
	MmioOr32(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(pcie_conf->PcieBase),
		HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_HW_AUTO_WIDTH_DISABLE_BMSK);

	//Slot capabilities and control
	MmioAnd32(HWIO_SLOT_CAPABILITIES_REG_ADDR(pcie_conf->PcieBase), ~0x7F);

	//Lane equalization. Different link mode and pcie core, the lane config is different. Reference the config table.
	pcie_lane_equalization(pcie_conf, slot_conf);

	//Set filter to workaround memory overlap between DMA addresses and PCIe on systems using direct physical addressing
	MmioOr32(HWIO_SYMBOL_TIMER_FILTER_1_OFF_ADDR(pcie_conf->PcieBase), 4 << HWIO_SYMBOL_TIMER_FILTER_1_OFF_MASK_RADM_1_SHFT);

	//[Attention] Amberwing 2.0 DBI features
	//Enable CRS SW visibility
	MmioOr32(HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_ADDR(pcie_conf->PcieBase), HWIO_ROOT_CONTROL_ROOT_CAPABILITIES_REG_PCIE_CAP_CRS_SW_VISIBILITY_EN_BMSK);

	//Lock DBI write access
	MmioAnd32(HWIO_MISC_CONTROL_1_OFF_ADDR(pcie_conf->PcieBase), ~HWIO_MISC_CONTROL_1_OFF_DBI_RO_WR_EN_BMSK);

	//Enable link training if card is present
	MmioOr32(HWIO_PCIE30_PARF_LTSSM_ADDR(pcie_conf->ParfBase), (1 << HWIO_PCIE30_PARF_LTSSM_LTSSM_EN_SHFT));
	printf("PCie link training, ltssm 0x%x\r\n", MmioRead32(HWIO_PCIE30_PARF_LTSSM_ADDR(pcie_conf->ParfBase)));

	while (cnt < 500) {
		if (MmioRead32(HWIO_PCIE30_ELBI_SYS_STTS_ADDR(pcie_conf->ElbiBase)) & HWIO_PCIE30_ELBI_SYS_STTS_XMLH_LINK_UP_BMSK)
            break;
		if (cnt % 100 == 0) // reduce output
			printf("PCIe link check SYS STTS 0x%x\r\n",
				   MmioRead32(HWIO_PCIE30_ELBI_SYS_STTS_ADDR(pcie_conf->ElbiBase)));
		Hdts_waitForMicroSecs(1000);
		cnt++;
	}

	if (cnt < 500) {
		uint32_t linkst;
		uint32_t idcxt;

		MmioAnd32(HWIO_GEN2_CTRL_OFF_ADDR(pcie_conf->PcieBase), ~HWIO_GEN2_CTRL_OFF_AUTO_LANE_FLIP_CTRL_EN_BMSK);

		linkst = MmioRead32(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(pcie_conf->PcieBase));
		printf("****** [PCIe] PCIe link is up for segment %d, Gen%d, x%d [0x%x] ******\r\n",
        	pcie_conf->ResourceMap.SegmentNumber,
        	(linkst & HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED_BMSK) >> HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED_SHFT,
        	(linkst & HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH_BMSK) >> HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH_SHFT,
        	linkst);
		idcxt = MmioRead32(pcie_conf->PcieBase + ECAM_BUS_ADDRESS_SIZE);
		printf("****** Vendor ID: 0x%x, Device ID: 0x%x ******\r\n", idcxt&0xffff, (idcxt>>16)&0xffff);
	} else {
		printf("[ERROR] PCIe link training timeout!\r\n");
		uint32_t ltssm_st = MmioRead32(HWIO_PCIE30_PARF_LTSSM_ADDR(pcie_conf->ParfBase)) & HWIO_PCIE30_PARF_LTSSM_LTSSM_STATE_BMSK;
        if((ltssm_st == S_CFG_LANENUM_WAIT) || (ltssm_st == S_CFG_LANENUM_ACEPT))
        {
			printf("[PCIe] set AUTO_LANE_FLIP_CTRL_EN\r\n");
			MmioOr32(HWIO_GEN2_CTRL_OFF_ADDR(pcie_conf->PcieBase), HWIO_GEN2_CTRL_OFF_AUTO_LANE_FLIP_CTRL_EN_BMSK);
        }

		printf("[PCIe] PCIe link is not up for segment %d\r\n", pcie_conf->ResourceMap.SegmentNumber);

		if (pcie_conf->ComplianceMode != PCIE_OPTION_DISABLE) 
		{
			printf("[PCIe] disable link training\r\n");
			MmioAnd32(HWIO_PCIE30_PARF_LTSSM_ADDR(pcie_conf->ParfBase), ~(1 << HWIO_PCIE30_PARF_LTSSM_LTSSM_EN_SHFT));
		}

		//Block all PCIe address space to go on bus when nothing is there
		pcie_set_ecam_blocker(pcie_conf, pcie_conf->PcieBase + pcie_conf->MaxFunctionOnRootBridge * ECAM_FUNCTION_ADDRESS_SIZE,
			pcie_conf->ResourceMap.Res[TypeBus].End * ECAM_BUS_ADDRESS_SIZE - pcie_conf->MaxFunctionOnRootBridge * ECAM_FUNCTION_ADDRESS_SIZE);
	}

	//Clear any signalled PCIe interrupts
	if (HWIO_PCIE30_INT_ALL_0_STATUS_ADDR(pcie_conf->ParfBase)) 
		MmioWrite32(HWIO_PCIE30_INT_ALL_0_CLEAR_ADDR(pcie_conf->ParfBase), 0xffffffff);

	if (HWIO_PCIE30_INT_ALL_1_STATUS_ADDR(pcie_conf->ParfBase)) 
		MmioWrite32(HWIO_PCIE30_INT_ALL_1_CLEAR_ADDR(pcie_conf->ParfBase), 0xffffffff);

	//Clear error registers
	MmioWrite32(HWIO_UNCORR_ERR_STATUS_OFF_ADDR(pcie_conf->PcieBase), 0x0);
	MmioWrite32(HWIO_CORR_ERR_STATUS_OFF_ADDR(pcie_conf->PcieBase), 0x0);

	//Firmware first handling
	if (gFirmwareFirstEnable) 
	{
		MmioWrite32(HWIO_PCIE30_PARF_INTA_MASK_ADDR(pcie_conf->ParfBase), 0);
		MmioWrite32(HWIO_PCIE30_PARF_FW_INT_MASK_ADDR(pcie_conf->ParfBase), 0x1b);
	} 
	else 
	{
		MmioWrite32(HWIO_PCIE30_PARF_INTA_MASK_ADDR(pcie_conf->ParfBase), 0);
		MmioWrite32(HWIO_PCIE30_PARF_FW_INT_MASK_ADDR(pcie_conf->ParfBase), 0x3f);
	}

	//Increase flow control update rate
	MmioAndThenOr32(HWIO_QUEUE_STATUS_OFF_ADDR(pcie_conf->PcieBase),
		~(HWIO_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_BMSK),
		HWIO_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_EN_BMSK | (0xA << HWIO_QUEUE_STATUS_OFF_TIMER_MOD_FLOW_CONTROL_SHFT));
}

void pcie_lane_post_init(uint64_t base)
{
	//chip_version 1.1 is 0x4f other is 0x45
	uint32_t clock_shift = 0x45; 

	if (MmioRead32(HWIO_RXENGINE_EN1_ADDR(base)) & HWIO_RXENGINE_EN1_DFE_TAP1_EN_BMSK) 
	{
		MmioWrite32(HWIO_CLK_SHIFT_ADDR(base), clock_shift);
	}
}

void pcie_phy_post_init(PCIE_SS_t pcie_ss)
{
	uint64_t cm_ser_base, lane_base, base_offset;

	base_offset = PSP1_CM_SERVER_PCIE_SW_BASE - PSP0_CM_SERVER_PCIE_SW_BASE;
	if (pcie_ss == PCIE_SS_0) 
		cm_ser_base = PSP0_CM_SERVER_PCIE_SW_BASE;
	else 
		cm_ser_base = PSP4_CM_SERVER_PCIE_SW_BASE;

	for (uint8_t i = 0; i < PCIE_PHY_PER_SS; i ++) 
	{
		lane_base = cm_ser_base + PSP0_QSERVER_L0_QSERVER_L0_PCIE_LANE_REG_BASE_OFFS;
		printf("Pcie Lane PostInit PspBase 0x%lx PHY lane offset at 0x%x\r\n", cm_ser_base, PCIE_LANE_REG_BASE_OFFSET);

		for (uint8_t j = 0; j < PCIE_LANE_PER_PHY; j ++) 
		{
	  		pcie_lane_post_init(lane_base);
	  		lane_base = lane_base + PCIE_LANE_REG_BASE_OFFSET;
		}
		cm_ser_base += base_offset;
	}
}

#if 0
STATIC EFI_STATUS PcieSubSystemEnable(PcieSubSystemId, LinkMode)
{
  UINTN ClockId;
  UINTN ClockIndex;
  UINT32 ResultFreq;
  EFI_STATUS Status = EFI_SUCCESS;

  if (PcieSubSystemId == PCIE_SS_0) {
    if (LinkMode == LINKMODE_1X16) {
      MmioWrite32(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(PCIE0_PCIE_CC_BASE), 0);
    } else {
      MmioWrite32(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(PCIE0_PCIE_CC_BASE), 2);
    }

    for (ClockIndex = 0; ClockIndex < (sizeof(gPcie0Clk) / sizeof(gPcie0Clk[
0])); ClockIndex++) {
        Status = gClockProtocol->GetClockID(gClockProtocol, gPcie0Clk[
ClockIndex].Name, &ClockId);
        if (!EFI_ERROR(Status)) {
          Status = gClockProtocol->EnableClock(gClockProtocol, ClockId);
          if (!EFI_ERROR(Status) && gPcie0Clk[ClockIndex].Freq != 0) {
            Status = gClockProtocol->SetClockFreqHz(gClockProtocol,
              ClockId,
              gPcie0Clk[ClockIndex].Freq,
              EFI_CLOCK_FREQUENCY_HZ_CLOSEST,
              &ResultFreq);
          }
        }
      }

      //Set the clk source for A, B, C PCLK's
      MmioWrite32(HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 
0x100);
      MmioWrite32(HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 
0x1);
      MmioWrite32(HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 
0x100);
      MmioWrite32(HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 
0x1);
      MmioWrite32(HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 
0x100);
      MmioWrite32(HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(PCIE0_PCIE_CC_BASE), 
0x1);

    } else if (LinkModeProtocol->PcieSubSystemId == PCIE_SS_1) {
      if (LinkModeProtocol->LinkMode == LINKMODE_1X16) {
        MmioWrite32(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(PCIE1_PCIE_CC_BASE), 
0);
      } else {
        MmioWrite32(HWIO_PCIE_CC_PCIE_X16_PCLK_MUXR_ADDR(PCIE1_PCIE_CC_BASE), 
2);
      }

      for (ClockIndex = 0; ClockIndex < (sizeof(gPcie1Clk) / sizeof(gPcie1Clk[
0])); ClockIndex++) {
        Status = gClockProtocol->GetClockID(gClockProtocol, gPcie1Clk[
ClockIndex].Name, &ClockId);
        if (!EFI_ERROR(Status)) {
          Status = gClockProtocol->EnableClock(gClockProtocol, ClockId);
          if (!EFI_ERROR(Status) && gPcie1Clk[ClockIndex].Freq != 0) {
            Status = gClockProtocol->SetClockFreqHz(gClockProtocol,
              ClockId,
              gPcie1Clk[ClockIndex].Freq,
              EFI_CLOCK_FREQUENCY_HZ_CLOSEST,
              &ResultFreq);
          }
        }
      }
      //Set the clk source for A, B, C PCLK's
      MmioWrite32(HWIO_PCIE_CC_PCIE_A_PCLK_CFG_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 
0x100);
      MmioWrite32(HWIO_PCIE_CC_PCIE_A_PCLK_CMD_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 
0x1);
      MmioWrite32(HWIO_PCIE_CC_PCIE_B_PCLK_CFG_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 
0x100);
      MmioWrite32(HWIO_PCIE_CC_PCIE_B_PCLK_CMD_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 
0x1);
      MmioWrite32(HWIO_PCIE_CC_PCIE_C_PCLK_CFG_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 
0x100);
      MmioWrite32(HWIO_PCIE_CC_PCIE_C_PCLK_CMD_RCGR_ADDR(PCIE1_PCIE_CC_BASE), 
0x1);
    } else {
      DEBUG((DEBUG_INIT, "[PCI] Invalid PcieSubSystemId 0x%x\n", 
LinkModeProtocol->PcieSubSystemId));
      return EFI_INVALID_PARAMETER;
    }

  return Status;
}
#endif
/**
 * @brief       Pcie link function.
 *
 * @param[in]   pcie_ss    Pcie sub-system number. (0~1)
 *
 * @return      None
 *
 * @note		LinkMode Support: 3x4 1x8+2x4 2x8 1x16. Current case support 1x16
 */
void pcie_link(void)
{
    //uint32_t risertype = LINKMODE_2X8; //riser type is read from bmc via ssif, 
    // hard code to 3x4 first.
	//link mode support: 3x4 1x8+2x4 2x8 1x16. Current case support 1x16
	PCIE_LINKMODE_t link_mode = LINKMODE_1X16; // 8_2X4;
	uint32_t pcie_conf_pcs = 0;
	uint32_t slot_conf_pcs = 0;
	uint8_t port = 0;
	uint32_t pcie_ss = 0;
    for (pcie_ss = 0; pcie_ss < 2; pcie_ss ++) {
		printf("PCIe link...\r\n");
		if (pcie_ss == PCIE_SS_1)
		{
			pcie_conf_pcs = 3;
			slot_conf_pcs = 1;
		}

		switch (link_mode) 
		{
			case LINKMODE_3X4:
				printf("PCIe ss %d link mode 3x4\r\n", pcie_ss);
				for (port = 0; port < 1; port ++) {
				  pcie_root_bridge_init(&mPcieConfig[port+pcie_conf_pcs], 
				  &mSlotConfig[0+slot_conf_pcs][1]);
				}
				break;
			case LINKMODE_1X8_2X4:
				printf("PCIe ss %d link mode 1x8_2x4\r\n", pcie_ss);
				for (port = 0; port < 3; port ++) {
				  pcie_root_bridge_init(&mPcieConfig[port+pcie_conf_pcs], &mSlotConfig[0+slot_conf_pcs][port]);
				}
				break;
			case LINKMODE_2X8:
				printf("PCIe ss %d link mode is 2x8\r\n", pcie_ss);
				for (uint8_t i =0; i<2; i++) {
				  pcie_root_bridge_init(&mPcieConfig[i+1+pcie_conf_pcs], &mSlotConfig[0+slot_conf_pcs][3]);
				}
				break;
			case LINKMODE_1X16:
				printf("PCIe ss %d link mode x16\r\n", pcie_ss);
				pcie_root_bridge_init(&mPcieConfig[0+pcie_conf_pcs], &mSlotConfig[0+slot_conf_pcs][5]);
				break;
			default:
				printf("[ERROR]PCIe link input illegal parameter. link_mode %d\r\n", link_mode);
				return;
			break;
		}

		pcie_phy_post_init(pcie_ss);
    }
}

void pcie_link_one(PCIE_SS_t ss, PCIE_LINKMODE_t linkmode)
{
	uint8_t i = 0;

	switch (linkmode) {
	case LINKMODE_3X4:
		printf("PCIe ss %d link mode 3x4\r\n", ss);
		// not sure the config is right or not, so skipped now
		// pcie_root_bridge_init(&mPcieConfig[port+pcie_conf_pcs],
		// &mSlotConfig[0+slot_conf_pcs][1]);
		printf("Not implemented.\n");
		break;
	case LINKMODE_1X8_2X4:
		printf("PCIe ss %d link mode 1x8_2x4\r\n", ss);
		for (i = 0; i < 3; ++i) { // 3 slots, 0,1,2
			printf("Set core %d:\n", i);
			pcie_root_bridge_init(&mPcieConfig[i + ss * 3], &mSlotConfig[ss][i]);
		}
		break;
	case LINKMODE_2X8:
		printf("PCIe ss %d link mode is 2x8\r\n", ss);
		for (i = 0; i < 2; ++i) { // 2 slots, 3,4
			pcie_root_bridge_init(&mPcieConfig[i + 1 + ss * 3], &mSlotConfig[ss][3]);
		}
		break;
	case LINKMODE_1X16:
		printf("PCIe ss %d link mode x16\r\n", ss);
		pcie_root_bridge_init(&mPcieConfig[0 + ss * 3], &mSlotConfig[ss][5]); // 1 slot, 5
		break;
	default:
		printf("[ERROR]PCIe link input illegal parameter. linkmode %d\r\n", linkmode);
		return;
	}

	pcie_phy_post_init(ss);

	return;
}

void pcie_reset(PCIE_SS_t pcie_ss, PCIE_LINKMODE_t link_mode, bool warm)
{
	uint64_t ss_base = pcie_ss == PCIE_SS_1 ? PCIE1_PCIE_CC_BASE : PCIE0_PCIE_CC_BASE;

	printf("reset ss %d\n", pcie_ss);

	// 23.2.5.1.1 Warm reset (PCIE)
	// PCIE_n_BCR[BLK_ARES], n=[X8_0, X8_1, X16], set and clear, defined in HALclkHWIO.h

	// refer to PCIE_Reset.cmm
	if (link_mode == LINKMODE_1X16)
		reg_base_write(ss_base, PCIE_CC_PCIE_X16_PCLK_MUXR, SEL, 0);
	else
		reg_base_write(ss_base, PCIE_CC_PCIE_X16_PCLK_MUXR, SEL, 2);

	// 23. SW asserts link down reset bit which resets the Core and bridges by setting the following
	// register bit Write 1 to PCIE*_PCIE_CC_PCIE_X*_*_RESETR.LINK_DOWN Setting this bit will cause
	// the QSB2AXI master and Slave interfaces and the controller core to go into reset state. The
	// Clock controller will turn off all clocks before Reset to adhere to the UAR methodology (This
	// is done by HW)
	if (warm) {
		reg_base_write(ss_base, PCIE_CC_PCIE_X16_RESETR, LINK_DOWN, 1); // core 0
		reg_base_write(ss_base, PCIE_CC_PCIE_X8_0_RESETR, LINK_DOWN, 1); // core 1
		reg_base_write(ss_base, PCIE_CC_PCIE_X8_1_RESETR, LINK_DOWN, 1); // core 2
	} else {
		reg_base_write(ss_base, PCIE_CC_PCIE_X16_BCR, BLK_ARES, 1);
		reg_base_write(ss_base, PCIE_CC_PCIE_X8_0_BCR, BLK_ARES, 1);
		reg_base_write(ss_base, PCIE_CC_PCIE_X8_1_BCR, BLK_ARES, 1);
	}

	udelay(1000); // 1ms

	// 24. SW asserts PHY reset by setting the following register bit
	// Write 1 to PCIE*_PCIE_CC_PCIE_PHY_*_RESETR.PHY_WARM_ARES1
	reg_base_write(ss_base, PCIE_CC_PCIE_PHY_AA_RESETR, PHY_WARM_ARES, 1); // PHY AA
	reg_base_write(ss_base, PCIE_CC_PCIE_PHY_AB_RESETR, PHY_WARM_ARES, 1); // PHY AB
	reg_base_write(ss_base, PCIE_CC_PCIE_PHY_B_RESETR, PHY_WARM_ARES, 1); // PHY B
	reg_base_write(ss_base, PCIE_CC_PCIE_PHY_C_RESETR, PHY_WARM_ARES, 1); // PHY C

	udelay(1000); // 1ms

	// 25. SW releases PHY reset by resetting following register bit
	reg_base_write(ss_base, PCIE_CC_PCIE_PHY_AA_RESETR, PHY_WARM_ARES, 0); // PHY AA
	reg_base_write(ss_base, PCIE_CC_PCIE_PHY_AB_RESETR, PHY_WARM_ARES, 0); // PHY AB
	reg_base_write(ss_base, PCIE_CC_PCIE_PHY_B_RESETR, PHY_WARM_ARES, 0); // PHY B
	reg_base_write(ss_base, PCIE_CC_PCIE_PHY_C_RESETR, PHY_WARM_ARES, 0); // PHY C

	udelay(1000); // 1ms

	// 26. SW releases link down reset bit which releases reset to Core and bridges by resetting the
	// following register bit
	if (warm) {
		reg_base_write(ss_base, PCIE_CC_PCIE_X16_RESETR, LINK_DOWN, 0); // core 0
		reg_base_write(ss_base, PCIE_CC_PCIE_X8_0_RESETR, LINK_DOWN, 0); // core 1
		reg_base_write(ss_base, PCIE_CC_PCIE_X8_1_RESETR, LINK_DOWN, 0); // core 2
	} else {
		reg_base_write(ss_base, PCIE_CC_PCIE_X16_BCR, BLK_ARES, 0);
		reg_base_write(ss_base, PCIE_CC_PCIE_X8_0_BCR, BLK_ARES, 0);
		reg_base_write(ss_base, PCIE_CC_PCIE_X8_1_BCR, BLK_ARES, 0);
	}

	return;
}

/**
 * @brief       Pcie init function. GPIO/Clocks/Phy Init.
 *
 * @param[in]   pcie_ss    Pcie sub-system number. (0~1)
 *
 * @return      None
 *
 * @note		LinkMode Support: 3x4 1x8+2x4 2x8 1x16. Current case support 1x16
 */
void pcie_init(void)
{
    //uint32_t risertype = LINKMODE_2X8; //riser type is read from bmc via ssif, 
    // now hard code to 1x8_2x4 first.
	//link mode support: 3x4 1x8+2x4 2x8 1x16. Current case support 1x16
	PCIE_LINKMODE_t link_mode = LINKMODE_1X16;
	EFI_STATUS Status = EFI_SUCCESS;
	uint8_t pcie_ss = 0;
	uint8_t Index = 0;
	UINTN SlotPortAddress[] = {0x7C, 0x7E, 0x7F, 0xE2, 0xE1, 0xE0};

	pcie_gpio_setting(); //only rep platform has to config this gpio

	for (pcie_ss = 0; pcie_ss < 2; pcie_ss ++) {
	  pcie_clk_init(pcie_ss);
	  pcie_phy_init(pcie_ss, link_mode);
	}

	Status = PcieI2cIoInitialize();
	if (Status == EFI_SUCCESS)
	{
      for (Index = 0; Index < (sizeof(PortExpanderAddress) / sizeof(PortExpanderAddress[0])); Index++) {
        if (EFI_ERROR(PcieSlotPortExpander_Configure(PortExpanderAddress[Index]))) {
           printf( "[PCIeConfig] Failed to configure slot signals for PE %d\n", Index);
        }
      }
      for (Index = 0; Index < (sizeof(DriveSlotPortExpanderAddress) / sizeof(DriveSlotPortExpanderAddress[0])); Index++) {
        if (EFI_ERROR(DriveSlotPortExpander_Configure(DriveSlotPortExpanderAddress[Index]))) {
          printf( "[PCIeConfig] Failed to configure slot signals for Drive slot PE %d\n", Index);
        }
      }
    }
	printf ("PcieI2cInitialize status = %x\n", Status);
    for (Index = 0; Index < 6;   Index++) {
	  //printf ("SlotPortAddress = 0x%x\n", SlotPortAddress[Index]);
	  PcieSlotPERST(SlotPortAddress[Index], FALSE);
    }
	PcieI2cIoDeinitialize();
}

void pcie_init_i2c(void)
{
	EFI_STATUS Status = EFI_SUCCESS;
	uint8_t Index = 0;
	UINTN SlotPortAddress[] = {0x7C, 0x7E, 0x7F, 0xE2, 0xE1, 0xE0};
		Status = PcieI2cIoInitialize();
	if (Status == EFI_SUCCESS)
	{
		for (Index = 0; Index < (sizeof(PortExpanderAddress) / sizeof(PortExpanderAddress[0])); Index++) {
			if (EFI_ERROR(PcieSlotPortExpander_Configure(PortExpanderAddress[Index])))
				printf( "[PCIeConfig] Failed to configure slot signals for PE %d\n", Index);
		}
		for (Index = 0; Index < (sizeof(DriveSlotPortExpanderAddress) / sizeof(DriveSlotPortExpanderAddress[0])); Index++) {
			if (EFI_ERROR(DriveSlotPortExpander_Configure(DriveSlotPortExpanderAddress[Index])))
				printf( "[PCIeConfig] Failed to configure slot signals for Drive slot PE %d\n", Index);
		}
	}
	printf ("PcieI2cInitialize status = %x\n", Status);
	for (Index = 0; Index < 6;   Index++) {
		//printf ("SlotPortAddress = 0x%x\n", SlotPortAddress[Index]);
		PcieSlotPERST(SlotPortAddress[Index], FALSE);
	}
	PcieI2cIoDeinitialize();
}

int pcie_clk_test(int core, int stage)
{
	printf("PCIE clock test for core %d\n", core);
	// for QCOM PCIE, read below regs:
	// AUX_CMD_RCGR, PHY_AA_MISC, PHY_AB_MISC, PHY_B_MISC, PHY_C_MISC
	// PCIE_SS_0/1_SFPB_CMD_RCGR, PCIE_SS_0/1_VBU_CMD_RCGR
	// PCIE_X16/X8_0/X8_1_BCR, PCIE_X16/X8_0/X8_1_MSTR_Q23_CMD_RCGR, ..

	// shut down clocks, refer to PCIE_Init_Rc.cmm
	if (stage == 0) {
		switch (core) {
		case 0: // ss 0, X16 controller, clk_disable
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X16_AUX_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X16_AUX_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X16_AHB_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X16_AHB_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X16_MMU_AHB_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X16_MMU_MSTR_Q23_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X16_MSTR_Q23_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X16_PCLK_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X16_PCLK_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X16_SLV_Q23_CBCR_CLK_ENABLE_BMSK);
			break;
		case 1: // ss 0, X8_0 controller, clk_disable
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_AUX_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_0_AUX_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_AHB_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_0_AHB_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MMU_AHB_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MMU_MSTR_Q23_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_0_MSTR_Q23_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_PCLK_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_0_PCLK_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_0_SLV_Q23_CBCR_CLK_ENABLE_BMSK);
			break;
		case 2: // ss 0, X8_1 controller, clk_disable
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_AUX_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_1_AUX_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_AHB_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_1_AHB_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MMU_AHB_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MMU_MSTR_Q23_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_1_MSTR_Q23_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_PCLK_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_1_PCLK_CBCR_CLK_ENABLE_BMSK);
			MmioAnd32(HWIO_PCIE0_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_ADDR,
					  ~HWIO_PCIE0_PCIE_CC_PCIE_X8_1_SLV_Q23_CBCR_CLK_ENABLE_BMSK);
			break;
		default:
			printf("TBD\n");
			while (1)
				;
		}
	}
	return 0;
}

int pcie_set_mode(PCIE_SS_t ss, PCIE_LINKMODE_t link_mode)
{
	uint32_t mode = 0;
	// 3'b000:               Three PCIe root ports each operating in 4-lane mode (Configuration:
	// 3x4) 3'b010:               One 8-lane PCIe root port and two 4-lane root ports
	// (Configuration: 1x8 + 2x4) 3'b011:               Two 8-lane PCIe root ports (Configuration:
	// 2x8) 3'b100:               One 16-lane PCIe root port (Configuration: 1x16)

	if (link_mode == LINKMODE_3X4)
		mode = 0;
	else if (link_mode == LINKMODE_1X8_2X4)
		mode = 2;
	else if (link_mode == LINKMODE_2X8)
		mode = 3;
	else if (link_mode == LINKMODE_1X16)
		mode = 4;
	else {
		printf("Unsupported link mode!\n");
		return -1;
	}

	if (ss == PCIE_SS_0) {
		MmioWrite32(TLMM_PCIESS0_LINK_MODE_0, mode);
		MmioWrite32(TLMM_PCIESS0_LINK_MODE_1, mode);
		MmioWrite32(TLMM_PCIESS0_LINK_MODE_2, mode);
	} else if (ss == PCIE_SS_1) {
		MmioWrite32(TLMM_PCIESS1_LINK_MODE_0, mode);
		MmioWrite32(TLMM_PCIESS1_LINK_MODE_1, mode);
		MmioWrite32(TLMM_PCIESS1_LINK_MODE_2, mode);
	} else {
		printf("Unsupported SubSystem!\n");
		return -1;
	}

	return 0;
}

int pcie_get_mode(PCIE_SS_t ss)
{
	PCIE_LINKMODE_t link_mode_0, link_mode_1, link_mode_2;

	if (ss == PCIE_SS_0) {
		link_mode_0 = MmioRead32(TLMM_PCIESS0_LINK_MODE_0);
		link_mode_1 = MmioRead32(TLMM_PCIESS0_LINK_MODE_1);
		link_mode_2 = MmioRead32(TLMM_PCIESS0_LINK_MODE_2);
	} else if (ss == PCIE_SS_1) {
		link_mode_0 = MmioRead32(TLMM_PCIESS1_LINK_MODE_0);
		link_mode_1 = MmioRead32(TLMM_PCIESS1_LINK_MODE_1);
		link_mode_2 = MmioRead32(TLMM_PCIESS1_LINK_MODE_2);
	} else {
		printf("Unsupported SubSystem!\n");
		return -1;
	}

	if (link_mode_0 != link_mode_1 || link_mode_1 != link_mode_2) {
		printf("Link mode settings incorrect!\n");
		return -1;
	}

	if (link_mode_0 == 0)
		printf("Link mode for ss %d is %s\n", ss, "LINKMODE_3X4");
	else if (link_mode_0 == 2)
		printf("Link mode for ss %d is %s\n", ss, "LINKMODE_1X8_2X4");
	else if (link_mode_0 == 3)
		printf("Link mode for ss %d is %s\n", ss, "LINKMODE_2X8");
	else if (link_mode_0 == 4)
		printf("Link mode for ss %d is %s\n", ss, "LINKMODE_1X16");
	else {
		printf("Link mode is not unsupported!\n");
		return -1;
	}

	return 0;
}

int pcie_show_status(int core)
{
	uint8_t i;
	uint32_t link_width;
	uint32_t link_speed;
	uint32_t link_up;

	printf("PCIE show status for core %d\n", core);
	for (i = 0; i < sizeof(mPcieConfig) / sizeof(mPcieConfig[0]); ++i) {
		if (mPcieConfig[i].ControllerId == core)
			break;
	}
	// assert(i <= 5);
	link_up = (MmioRead32(HWIO_PCIE30_ELBI_SYS_STTS_ADDR(mPcieConfig[i].ElbiBase))
			   & HWIO_PCIE30_ELBI_SYS_STTS_XMLH_LINK_UP_BMSK)
			  >> HWIO_PCIE30_ELBI_SYS_STTS_XMLH_LINK_UP_SHFT;
	if (link_up != 0x1) {
		printf("link is down.\n");
		return -1;
	}
	printf("link is up.\n");

	link_width = (MmioRead32(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(mPcieConfig[i].PcieBase))
				  & HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH_BMSK)
				 >> HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_NEGO_LINK_WIDTH_SHFT;
	link_speed = (MmioRead32(HWIO_LINK_CONTROL_LINK_STATUS_REG_ADDR(mPcieConfig[i].PcieBase))
				  & HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED_BMSK)
				 >> HWIO_LINK_CONTROL_LINK_STATUS_REG_PCIE_CAP_LINK_SPEED_SHFT;
	printf("negotiated link width: x%d\n", link_width);
	printf("negotiated link speed: gen%d\n", link_speed);

	return 0;
}

// do the enumeration only if the link up
int pcie_assignbars(int core)
{
	// uint8_t primary = 0, subordinate, b, d, f, r, maxBus, maxDevice;
	// uint64_t addr;
	uint32_t bus = 0;

	if (pcie_show_status(core) != 0)
		return -1;

	pci_find_devices_on_bus(mPcieConfig[core].PcieBase, bus);
	// addr = mPcieConfig[core].PcieBase;
	// b = primary;
	// d = f = 0; // starting device 0, function 0
	// r = 0x18; // vender/device id reg offset
	// addr += b * (1 << 20) + (d * (1 << 15) + f * (1 << 12)) + r * (1 << 0);
	// subordinate	= (MmioRead32(addr) >> 16) & 0xFF; // get device id

	// maxBus = subordinate + 1;
	// if (maxBus == 0x100) {
	// 	printf("failed to read the subordinate bus number.\n");
	// 	return -1;
	// }
	// if (maxBus == 1)
	// 	maxDevice = 1;

	// FillDeviceExistenceBits

	return -1;
}

struct reg_list {
	uint32_t size; // DW count
	uintptr_t addr; // 64bits address
	uintptr_t pbuf; // buffer for reading
};
static uint32_t reg_count = 0;
static struct reg_list * reg_list_ptr = NULL;

// global vars for PCIE
static int g_pcie_core = 0;
static PCIE_SS_t g_pcie_ss = PCIE_SS_0;
static PCIE_LINKMODE_t g_pcie_linkmode = LINKMODE_1X16;
static PCIE_SPEED_t g_pcie_linkspeed = 0;
static int g_pcie_linkwidth = 0;
static int g_pcie_loopback = 0;

static int do_pcie(int argc, char * argv[])
{
	uint32_t mask = 0xFFFFFFFF;
	uintptr_t addr = 0;
	uint32_t data = 0;
	uint32_t val = 0;
	int i;

	if (argc == 1) // no param
		return -1;

	if (strcmp(argv[1], "var") == 0) {
		if (argc == 3 && strcmp(argv[2], "show") == 0) { // pcie var show
			printf("PCIE ss: %d\n", g_pcie_ss);
			printf("PCIE core: %d\n", g_pcie_core);
			printf("PCIE linkmode: %d\n", g_pcie_linkmode);
			printf("PCIE linkspeed: %d\n", g_pcie_linkspeed);
			printf("PCIE linkwidth: %d\n", g_pcie_linkwidth);
			return 0;
		} else if (argc == 5 && strcmp(argv[2], "set") == 0) {
			if (strcmp(argv[3], "ss") == 0 && argc == 5) { // pcie var set ss 0~1
				i = strtoul(argv[4], NULL, 0);
				g_pcie_ss = (i == 1) ? i : 0;
				printf("set ss to %d\n", g_pcie_ss);
				return 0;
			}
			if (strcmp(argv[3], "core") == 0 && argc == 5) { // pcie var set core 0~5
				i = strtoul(argv[4], NULL, 0);
				g_pcie_core = (i >= 0 && i < 5) ? i : 0;
				printf("set core to %d\n", g_pcie_core);
				return 0;
			}
			if (strcmp(argv[3], "linkmode") == 0
				&& argc == 5) { // pcie var set linkmode 0~5, 0:2x8 1:2x4_1x8 2:1x8_2x4 3:2x4_2x4
								// 4:3x4 5:1x16
				i = strtoul(argv[4], NULL, 0);
				g_pcie_linkmode = (i >= 0 && i <= 5) ? i : 0;
				printf("set linkmode to %d\n", g_pcie_linkmode);
				return 0;
			}
			if (strcmp(argv[3], "linkspeed") == 0
				&& argc == 5) { // pcie var set linkspeed 0~3, 0:auto 1:gen1 2:gen2 3:gen3
				i = strtoul(argv[4], NULL, 0);
				g_pcie_linkspeed = (i >= 0 && i <= 3) ? i : 0;
				printf("set linkspeed to gen%d\n", g_pcie_linkspeed);
				return 0;
			}
			if (strcmp(argv[3], "linkwidth") == 0
				&& argc == 5) { // pcie var set linkwidth 1~16, 1:x1 2:x2 4:x4 8:x8 16:x16
				i = strtoul(argv[4], NULL, 0);
				g_pcie_linkwidth = (i >= 1 && i <= 16) ? i : 16;
				printf("set linkwidth to x%d\n", g_pcie_linkwidth);
				return 0;
			}

			if (strcmp(argv[3], "loopback") == 0
				&& argc == 5) { // pcie var set loopback 0~3, 0:noloopback 1:pipe 2:phy 3:parallel
				i = strtoul(argv[4], NULL, 0);
				g_pcie_loopback = (i >= 0 && i <= 3) ? i : 0;
				mPcieConfig[g_pcie_core].Loopback = g_pcie_loopback;
				printf("set loopback to %d\n", g_pcie_loopback);
				return 0;
			}
		}
	}

	if (strcmp(argv[1], "init") == 0) {
		if (argc == 2) { // pcie init
			pcie_init();
			return 0;
		} else if (strcmp(argv[2], "gpio") == 0) { // pcie init gpio
			pcie_gpio_setting();
			return 0;
		} else if (strcmp(argv[2], "clk") == 0) { // pcie init clk 0/1
			pcie_clk_init(g_pcie_ss);
			return 0;
		} else if (strcmp(argv[2], "phy") == 0) { // pcie init phy ss:0/1 mode:0-5
			pcie_phy_init(g_pcie_ss, g_pcie_linkmode);
			return 0;
		} else if (strcmp(argv[2], "i2c") == 0) { // pcie init i2c
			pcie_init_i2c();
			return 0;
		} else if (strcmp(argv[2], "clkgen") == 0) { // pcie init clkgen
			pcie_clkgen_init();
			return 0;
		}
	} else if (strcmp(argv[1], "link") == 0) { // pcie link [all|one]
		if (argc == 3 && strcmp(argv[2], "all") == 0) {
			pcie_link();
			return 0;
		}
		if (argc == 3 && strcmp(argv[2], "one") == 0) {
			pcie_link_one(g_pcie_ss, g_pcie_linkmode);
			return 0;
		}
	} else if (strcmp(argv[1], "reset") == 0) {
		pcie_reset(g_pcie_ss, g_pcie_linkmode, false);
		return 0;
	}

	// pcie read addr [mask]
	if ((strcmp(argv[1], "read") == 0) && (argc == 3 || argc == 4)) {
		addr = strtoull(argv[2], 0, 0);
		if (argc == 4) // pcie read addr [mask]
			mask = strtoul(argv[3], 0, 0);
		data = in_dword_masked(addr, mask);
		printf("Addr %p (mask:0x%08x): 0x%08x\n", addr, mask, data);
		return 0;
	} else if((strcmp(argv[1], "write") == 0) && (argc == 4 || argc == 5)) { // pcie write addr val [mask]
		addr = strtoull(argv[2], 0, 0);
		val = strtoul(argv[3], 0, 0);
		if (argc == 5) // mask
			mask = strtoul(argv[4], 0, 0);
		out_dword_masked_ns(addr, mask, val, in_dword(addr));
		return 0;
	}

	// pcie rr count addr size [addr size] ..., reg read
	if (strcmp(argv[1], "rr") == 0) {
		if (reg_count != 0 && reg_list_ptr != NULL) { // free
			for(i = 0; i < reg_count; i++)
				free((void*)reg_list_ptr[i].pbuf);
			free((void*)reg_list_ptr);
			reg_list_ptr = NULL;
			reg_count = 0;
		}
		if(argc >= 5) {
			reg_count = strtoul(argv[2], NULL, 10);
			if (reg_count > 0 && argc == (3+2*reg_count)) {
				reg_list_ptr = (struct reg_list*)malloc(sizeof(struct reg_list) * reg_count);
				memset(reg_list_ptr, 0, sizeof(struct reg_list) * reg_count);
				for (i = 0; i < reg_count; i++) {
					reg_list_ptr[i].addr = strtoull(argv[3+i*2], NULL, 16);
					reg_list_ptr[i].size = strtoul(argv[3+i*2+1], NULL, 16);
					reg_list_ptr[i].pbuf = (uintptr_t)malloc(reg_list_ptr[i].size);
					memset((void*)reg_list_ptr[i].pbuf, 0, reg_list_ptr[i].size * sizeof(uint32_t));
					// read reg sections to memory
					memcpy((void*)reg_list_ptr[i].pbuf, (const void*)reg_list_ptr[i].addr, reg_list_ptr[i].size * sizeof(uint32_t));
				}
				return 0;
			}
		}
	}
	else if (strcmp(argv[1], "rc") == 0) { // pcie reg compare
		for (i = 0; i < reg_count; i++) {
			if (memcmp((void*)reg_list_ptr[i].pbuf, (const void*)reg_list_ptr[i].addr, reg_list_ptr[i].size * sizeof(uint32_t)) != 0) {
				printf("**Diff: addr=0x%p, buf=0x%p size=0x%x\n", reg_list_ptr[i].pbuf, reg_list_ptr[i].addr, reg_list_ptr[i].size);
			} else
				printf("**Match: addr=0x%p, buf=0x%p size=0x%x\n", reg_list_ptr[i].pbuf, reg_list_ptr[i].addr, reg_list_ptr[i].size);
		}
		return 0;
	}

	// pcie test ...
	if (strcmp(argv[1], "test") == 0) {
		if (argc >= 3 && strcmp(argv[2], "clk") == 0) { // pcie test clk
			i = 0;
			if (argc >= 4)
				i = strtoul(argv[3], NULL, 0);
			pcie_clk_test(g_pcie_core, i); // stage
			return 0;
		} else if (argc >= 3 && strcmp(argv[2], "mode") == 0) {
			if (argc >= 4 && strcmp(argv[2], "set") == 0) { // pcie test mode set
				pcie_set_mode(g_pcie_ss, g_pcie_linkmode);
				return 0;
			} else if (argc >= 4 && strcmp(argv[2], "get") == 0) { // pcie test mode get
				pcie_get_mode(g_pcie_ss);
				return 0;
			}
		}

		if (argc >= 3 && strcmp(argv[2], "assignbars") == 0) { // pcie test assignbars
			pcie_assignbars(g_pcie_core);
		}
		if (argc >= 3 && strcmp(argv[2], "find") == 0) { // pcie test find bus
			i = strtoul(argv[3], NULL, 0);
			pci_find_devices_on_bus(mPcieConfig[g_pcie_core].PcieBase, i);
		}
	}

	// pcie dump ...
	if (strcmp(argv[1], "dump") == 0) {
		if (argc == 3 && strcmp(argv[2], "status") == 0) { // pcie dump status
			pcie_show_status(g_pcie_core);
			return 0;
		}
		if (argc == 4 && strcmp(argv[2], "header") == 0) { // pcie dump header b:d:f
			uint32_t b, d, f;
			char* p = argv[3];
			b = strtoul(p, 0, 0);
			p = strchr(p, ':') + 1;
			d = strtoul(p, 0, 0);
			p = strchr(p, ':') + 1;
			f = strtoul(p, 0, 0);
			pci_header_show(mPcieConfig[g_pcie_core].PcieBase, PCI_BDF(b, d, f));
			return 0;
		}
		if (argc == 4 && strcmp(argv[2], "bar") == 0) { // pcie dump bar b:d:f
			uint32_t b, d, f;
			char* p = argv[3];
			b = strtoul(p, 0, 0);
			p = strchr(p, ':') + 1;
			d = strtoul(p, 0, 0);
			p = strchr(p, ':') + 1;
			f = strtoul(p, 0, 0);
			pci_bar_show(mPcieConfig[g_pcie_core].PcieBase, PCI_BDF(b, d, f));
			return 0;
		}
		return 0;
	}

	return -1;
}

#ifdef CONFIG_CONSOLE_COMMAND
MK_CMD(pcie,
	   do_pcie,
	   "pcie commands",
	   " pcie var show \n"
	   " pcie var set [ss|core|linkmode] [value] \n"
	   "   ss 0~1 \n"
	   "   core 0~5 \n"
	   "   linkmode 0~5, 0:2x8 1:2x4_1x8 2:1x8_2x4 3:2x4_2x4 4:3x4 5:1x16 \n"
	   "   linkspeed 0~3, 0:auto 1:gen1 2:gen2 3:gen3\n"
	   "   linkwidth 1~16, 1:x1 2:x2 4:x4 8:x8 16:x16\n"
	   "   loopback 0~3, 0:noloopback 1:pipe 2:phy 3:parallel\n"
	   " pcie init [gpio|clk|phy|i2c]\n"
	   " pcie link \n"
	   " pcie reset \n"
	   " pcie read [addr [mask]] \n"
	   " pcie write addr val [mask] \n"
	   " pcie rr count addr size [addr size] ... - reg read \n"
	   " pcie rc - reg compare\n"
	   " pcie test [clk|mode|assignbars] \n"
	   "   mode [set|get] \n"
	   " pcie dump [status|header|bar] \n"
	   "   header b:d:f \n"
	   "   bar b:d:f \n");
#endif // CONFIG_CONSOLE_COMMAND

