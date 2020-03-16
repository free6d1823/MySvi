/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "hdts/Base.h"
#include "hdts/hdts_common.h"
#include "hdts/hdts_misc.h"
#include "hdts/hdts_shell.h"
#include "target/delay.h"
#include "target/smp.h"

#include "HALsataHWIO.h"
#include "hdts/Target_cust.h"
#include "asm/hal/HALhwio.h"
#include "asm/mach/hal/HALbootHWIO.h"
#include "asm/mach/hal/HALclkHWIO.h"
#include "asm/mach/monaco/common/boot_util.h"
#include "hdts/hdts_interrupt.h"
#include "sata_defs.h"
#include "sata_init.h"
#include "sata_regs.h"

typedef struct SATA_INTR_CONF_T {
  HANDLER_FPTR handler;
  UINT32 trigger;
  UINT32 priority;
  UINT32 irq_id;
  UINT32 intrmask;
} Sata_Intr_Conf_t;

void sata_imc_interrupt_handle_0(void* param);
void sata_imc_interrupt_handle_1(void* param);
void sata_imc_interrupt_handle_2(void* param);
void sata_imc_interrupt_handle_3(void* param);
void sata_imc_interrupt_handle_4(void* param);
void sata_imc_interrupt_handle_5(void* param);
void sata_imc_interrupt_handle_6(void* param);
void sata_imc_interrupt_handle_7(void* param);

// extern
extern UINTN Sata_Reg_Base[SATA_CONTROLLER_NUMBER];

// global
static volatile UINT32 gSataIntrStatus[SATA_CONTROLLER_NUMBER];
static volatile Sata_Intr_Conf_t gSataIntrConf[SATA_CONTROLLER_NUMBER];
volatile UINT32 gSataIntrMaskEn = 0;

void sata_unmask_interrupts(UINT32 ControllerNum, UINT32 intrmask) {
  UINTN Base = Sata_Reg_Base[ControllerNum];
  UINT32 val = 0;

  // clear IS
  out_dword(Base + HWIO_SATA_IS_OFFS, 0x3);
  // clear P0IS
  out_dword(Base + HWIO_SATA_P0IS_OFFS, SATA_INTR_ALL_IN);
  // enable all sata interrupts
  out_dword(Base + HWIO_SATA_P0IE_OFFS, intrmask);
  // enable sata interrupt global enable
  val = in_dword(Base + HWIO_SATA_GHC_OFFS);
  out_dword(Base + HWIO_SATA_GHC_OFFS, val | 0x2);
}

void sata_mask_interrupts(UINT32 ControllerNum) {
  UINTN Base = Sata_Reg_Base[ControllerNum];
  UINT32 val = 0;

  // disable sata interrupt global enable
  val = in_dword(Base + HWIO_SATA_GHC_OFFS);
  out_dword(Base + HWIO_SATA_GHC_OFFS, val & (~(0x2)));
  // disable all sata interrupts
  val = in_dword(Base + HWIO_SATA_P0IE_OFFS);
  out_dword(Base + HWIO_SATA_P0IE_OFFS, val & (~SATA_INTR_ALL_IN));
  // clear P0IS
  out_dword(Base + HWIO_SATA_P0IS_OFFS, SATA_INTR_ALL_IN);
  // clear IS
  out_dword(Base + HWIO_SATA_IS_OFFS, 0x3);
}

void sata_imc_unmask_interrupts(UINT32 ControllerNum) {
  UINT32 intr_id = 0;

  intr_id = SATA_0_IMC_INTR_ID + ControllerNum;
  imc_enable_interrupt(intr_id);
}

void sata_imc_mask_interrupts(UINT32 ControllerNum) {
  UINT32 intr_id = 0;

  intr_id = SATA_0_IMC_INTR_ID + ControllerNum;
  imc_disable_interrupt(intr_id);
  imc_clear_interrupt(intr_id);
}

void sata_imc_interrupt_deinit(UINT32 ControllerNum) {
  UINT32 intr_id = 0;

  intr_id = SATA_0_IMC_INTR_ID + ControllerNum;

  sata_mask_interrupts(ControllerNum);
  interrupt_deregister(intr_id);
  sata_imc_mask_interrupts(ControllerNum);

  gSataIntrStatus[ControllerNum] = 0;
  memset((void *)&gSataIntrConf[ControllerNum], 0, sizeof(Sata_Intr_Conf_t));
}

void sata_imc_interrupt_init(UINT32 ControllerNum, UINT32 trigger,
                             UINT32 priority, UINT32 intrmask) {
  UINT32 intr_id = 0;

  intr_id = SATA_0_IMC_INTR_ID + ControllerNum;
  gSataIntrStatus[ControllerNum] = 0;
  gSataIntrConf[ControllerNum].trigger = trigger;
  gSataIntrConf[ControllerNum].priority = priority;
  gSataIntrConf[ControllerNum].irq_id = intr_id;
  gSataIntrConf[ControllerNum].intrmask = intrmask;
  // register sata interrupt handler
  gSataIntrConf[0].handler = sata_imc_interrupt_handle_0;
  gSataIntrConf[1].handler = sata_imc_interrupt_handle_1;
  gSataIntrConf[2].handler = sata_imc_interrupt_handle_2;
  gSataIntrConf[3].handler = sata_imc_interrupt_handle_3;
  gSataIntrConf[4].handler = sata_imc_interrupt_handle_4;
  gSataIntrConf[5].handler = sata_imc_interrupt_handle_5;
  gSataIntrConf[6].handler = sata_imc_interrupt_handle_6;
  gSataIntrConf[7].handler = sata_imc_interrupt_handle_7;

  sata_imc_unmask_interrupts(ControllerNum);

  // edge (level), priority:0
  interrupt_set_config(intr_id, trigger, 0, priority);
  // Enable the interrupt at the GIC
  interrupt_register(intr_id, gSataIntrConf[ControllerNum].handler);

  sata_unmask_interrupts(ControllerNum, intrmask);
}

void sata_interrupt_init(UINT32 ControllerNum, UINT32 intrmask) {
  if (intrmask == 0) {
    printf("Ignore interrupt init for no intr mask setting.\n");
    return;
  }
#ifdef CONFIG_HDTS_IMC
  printf("SATA imc interrupt init\n");
  sata_imc_interrupt_init(ControllerNum, INTERRUPT_EDGE_TRIGGERED, 0,
                            intrmask);
  return;
#endif

#ifdef CONFIG_HDTS_APC
  printf("SATA apc interrupt init. None operating now!\n");
  return;
#endif
}

void sata_interrupt_deinit(UINT32 ControllerNum) {
#ifdef CONFIG_HDTS_IMC
  printf("SATA imc interrupt deinit\n");
  sata_imc_interrupt_deinit(ControllerNum);
  return;
#endif

#ifdef CONFIG_HDTS_APC
  printf("SATA apc interrupt deinit. None operating now!\n");
  return;
#endif
}

void sata_interrupt_check(UINT32 ControllerNum, UINT32 intrmask) {
  UINT32 val = gSataIntrStatus[ControllerNum];

  // check expected interrupt mask
  if ((gSataIntrConf[ControllerNum].intrmask & intrmask) == 0)
    return;

  printf("SATA %d interrupt status 0x%x\r\n", ControllerNum, val);

  // no interrupt triggered
  if (val == 0)
    return;

  if ((val & SATA_INTR_DHRE) == SATA_INTR_DHRE) {
    printf("D2H Register FIS INTR\r\n");
  }

  if ((val & SATA_INTR_PSE) == SATA_INTR_PSE) {
    printf("PIO Setup FIS INTR\r\n");
  }

  if ((val & SATA_INTR_DSE) == SATA_INTR_DSE) {
    printf("DMA Setup FIS INTR\r\n");
  }

  if ((val & SATA_INTR_SDBE) == SATA_INTR_SDBE) {
    printf("Set Device Bits FIS INTR\r\n");
  }

  if ((val & SATA_INTR_UFE) == SATA_INTR_UFE) {
    printf("Unknown FIS INTR\r\n");
  }

  if ((val & SATA_INTR_DPE) == SATA_INTR_DPE) {
    printf("Descriptor Processed INTR\r\n");
  }

  if ((val & SATA_INTR_PCE) == SATA_INTR_PCE) {
    printf("Port Change INTR\r\n");
  }

  if ((val & SATA_INTR_PRCE) == SATA_INTR_PRCE) {
    printf("PHY Ready Change INTR\r\n");
  }

  if ((val & SATA_INTR_IPME) == SATA_INTR_IPME) {
    printf("Incorrect Port Multiplier INTR\r\n");
  }

  if ((val & SATA_INTR_OFE) == SATA_INTR_OFE) {
    printf("Overflow INTR\r\n");
  }

  if ((val & SATA_INTR_INFE) == SATA_INTR_INFE) {
    printf("Interface Non-fatal Error INTR\r\n");
  }

  if ((val & SATA_INTR_IFE) == SATA_INTR_IFE) {
    printf("Interface Fatal Error INTR\r\n");
  }

  if ((val & SATA_INTR_HBDE) == SATA_INTR_HBDE) {
    printf("Host Bus Data Error INTR\r\n");
  }

  if ((val & SATA_INTR_HBFE) == SATA_INTR_HBFE) {
    printf("Host Bus Fatal Error INTR\r\n");
  }

  if ((val & SATA_INTR_TFEE) == SATA_INTR_TFEE) {
    printf("Task File Error INTR\r\n");
  }

  if ((~val & intrmask) == 0) {
    printf("[PASS] SATA %d check intr pass, intr mask 0x%x\n", ControllerNum,
           intrmask);
  } else {
    printf("[FAIL] SATA %d check intr fail, intr st 0x%x, intr mask 0x%x\n",
           ControllerNum, val, intrmask);
  }

  gSataIntrStatus[ControllerNum] = 0;
}

void sata_imc_interrupt_proc(UINT32 intr_id) {
  UINT32 ctrl_num = intr_id - SATA_0_IMC_INTR_ID;
  UINTN Base = Sata_Reg_Base[ctrl_num];
  UINT32 val = 0;

  if (gSataIntrConf[ctrl_num].trigger == INTERRUPT_LEVEL_TRIGGERED)
    imc_disable_interrupt(intr_id);

  val = in_dword(Base + HWIO_SATA_P0IS_OFFS);
  gSataIntrStatus[ctrl_num] |= val;
  out_dword(Base + HWIO_SATA_P0IS_OFFS, val & SATA_INTR_ALL_IN);
}

void sata_imc_interrupt_handle_0(void* param)
{
	sata_imc_interrupt_proc(SATA_0_IMC_INTR_ID);
}

void sata_imc_interrupt_handle_1(void* param)
{
	sata_imc_interrupt_proc(SATA_1_IMC_INTR_ID);
}

void sata_imc_interrupt_handle_2(void* param)
{
	sata_imc_interrupt_proc(SATA_2_IMC_INTR_ID);
}

void sata_imc_interrupt_handle_3(void* param)
{
	sata_imc_interrupt_proc(SATA_3_IMC_INTR_ID);
}

void sata_imc_interrupt_handle_4(void* param)
{
	sata_imc_interrupt_proc(SATA_4_IMC_INTR_ID);
}

void sata_imc_interrupt_handle_5(void* param)
{
	sata_imc_interrupt_proc(SATA_5_IMC_INTR_ID);
}

void sata_imc_interrupt_handle_6(void* param)
{
	sata_imc_interrupt_proc(SATA_6_IMC_INTR_ID);
}

void sata_imc_interrupt_handle_7(void* param)
{
	sata_imc_interrupt_proc(SATA_7_IMC_INTR_ID);
}
