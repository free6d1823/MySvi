/*==============================================================================
  All Rights Reserved.

==============================================================================*/

#include "hdts_interrupt.h"
#include "hdts_misc.h"
#include "hdts_shell.h"
#include "hdts_timer.h"
#include "imc_gicv2.h"
#include <asm/hal/HALhwio.h>
#include <asm/mach-qdf2400/monaco/common/common_defs.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

UINT32 g_ws0_int_flag = 0;
UINT32 g_ws1_int_flag = 0;
UINT32 g_wdt_csr_data = 0;
UINT32 recd_recv_int[1000] = {0};
volatile UINT32 g_imc_isr_recv_cnt = 0;
void switch_to_nonsec();
void switch_to_sec();

void switch_to_nonsec() {
  out_dword(IMC_PROTNS_CTRL_ADDR, 0);
  __asm("dsb sy");
}
void switch_to_sec() {
  out_dword(IMC_PROTNS_CTRL_ADDR, 1);
  __asm("dsb sy");
}
UINT32 imc_int_cfg(UINT32 int_id_s, UINT32 int_id_e, UINT8 trigger,
                   UINT8 int_typ, UINT8 priority, HANDLER_FPTR isr_handler) {
  UINT32 id;
  UINT32 ret_val;
  interrupt_init();
  if (int_typ == 1) /*FIQ*/
    out_dword_masked_ns(
        IMC_GICC_CTLR_ADDR, 0x8, 0x8,
        in_dword_masked(IMC_GICC_CTLR_ADDR, 0x7ff)); // set for fiq
  else                                               /*IRQ*/
    out_dword_masked_ns(
        IMC_GICC_CTLR_ADDR, 0x8, 0x0,
        in_dword_masked(IMC_GICC_CTLR_ADDR, 0x7ff)); // set for irq
  for (id = int_id_s; id <= int_id_e; id++) {
    interrupt_set_config(id, trigger, 0, priority);
    ret_val = interrupt_register(id, isr_handler);
    if (ret_val == HDTS_FAIL) {
      printf("%d interrupt register(handler:0x%x) failed\n", id, isr_handler);
      return HDTS_FAIL;
    }
  }
  return HDTS_SUCCESS;
}
void gicv2_int_handler() {
  imc_disable_interrupt(g_active_int_id);
  DO_DSB;
  recd_recv_int[g_imc_isr_recv_cnt] = g_active_int_id;
  g_imc_isr_recv_cnt++;
}
void imc_wdt_WS0_handler() {
  imc_disable_interrupt(g_active_int_id); /*disable WS0*/
  g_ws0_int_flag = 1;
}
void imc_wdt_WS1_handler() {
  imc_disable_interrupt(g_active_int_id); /*disable WS1 */
  g_wdt_csr_data = in_dword_masked(IMC_QTMR_WDT_CSR_ADDR, 0x6);
  /*here clear WS1/WS0 flag, otherwise one more message will be printed*/
  out_dword_masked_ns(IMC_QTMR_WDT_CSR_ADDR, 0x1, 0x0,
                      in_dword_masked(IMC_QTMR_WDT_CSR_ADDR, 0xf));
  /*restore to secure state*/
  switch_to_sec();
  /*restore to set ws0/ws1 to be secure interrpt for future test*/
  out_dword_masked_ns(0xFF6FA40080 + 0x4 * 10, 0x1800, 0x0,
                      in_dword_masked(0xFF6FA40080 + 0x4 * 10, 0xffffffff));
  g_ws1_int_flag = 1;
}
void trigger_SGI(UINT32 int_id, UINT8 cpu_id) {
  UINT32 val;
  val = ((1 << cpu_id) << 16) | int_id;
  out_dword(IMC_GICD_SGIR_ADDR,
            val); /*GICD_SGIR, it cause SGI interrupt for designated CPU*/
  DO_DSB;
}
void trigger_MSI(UINT32 int_id) {
  out_dword(IMC_GICM_MSI_SETSPI_NS_ADDR, int_id);
  DO_DSB;
}
void imc_int_trigger(UINT32 int_id_s, UINT32 int_id_e, UINT8 cpu_id) {
  UINT32 id;
  UINT32 i;
  UINT32 cnt[1000] = {0};
  UINT8 error_flag = 0;
  g_imc_isr_recv_cnt = 0;
  for (id = int_id_s; id <= int_id_e; id++) {
    imc_enable_interrupt(id);
    if ((id <= 15) && (id >= 0))
      trigger_SGI(id, cpu_id);
    if ((id >= 16) && (id <= 543)) {
      imc_raise_interrupt(id);
      DO_DSB;
    }
    if ((id >= 544) && (id <= 575))
      trigger_MSI(id);
  }
  while (g_imc_isr_recv_cnt < (int_id_e - int_id_s + 1)) {
  }
  for (i = 0; i < g_imc_isr_recv_cnt; i++) {
    cnt[recd_recv_int[i]]++;
  }
  for (i = int_id_s; i <= int_id_e; i++) {
    if (cnt[i] != 1) {
      printf(
          "int#%d is received %d times, which is different with expectation\n",
          i, cnt[i]);
      error_flag = 1;
    }
  }
  if ((g_imc_isr_recv_cnt == (int_id_e - int_id_s + 1)) && (error_flag == 0))
    printf("PASSED, all triggered interrupt are recevied by GICv2, total "
           "%d(int#%d~int#%d) "
           "interrupts\n",
           g_imc_isr_recv_cnt, int_id_s, int_id_e);
  g_imc_isr_recv_cnt = 0;
}

UINT32 imc_wdog_config(UINT8 secure) {
  UINT32 ret_val = HDTS_SUCCESS;
  HANDLER_FPTR imc_wdt_handler;
  UINT32 cnt_start, cnt_end, i;
  interrupt_init();
  cnt_start = 331; /*WS0*/
  cnt_end = 332;   /*WS1*/
  if (secure == 1)
    out_dword_masked_ns(IMC_GICD_ISRn_ADDR(10), 0x1800, 0,
                        in_dword_masked(IMC_GICD_ISRn_ADDR(10), 0xffffffff));
  else
    out_dword_masked_ns(
        IMC_GICD_ISRn_ADDR(10), 0x1800, 0x1800,
        in_dword_masked(IMC_GICD_ISRn_ADDR(10),
                        0xffffffff)); /*1: non-secure interrupt for 331,332*/
  /*set offset for WDT*/
  out_dword(IMC_QTMR_WDT_OFFSET_ADDR, 0x400000);
  out_dword_masked_ns(
      MPM_WDOG_CONTROL_ADDR, 0x8, 0x8,
      in_dword_masked(MPM_WDOG_CONTROL_ADDR, 0x7fff)); /*bit3 DISABLE_IMC_WS1*/
  DO_DSB;
  for (i = cnt_start; i <= cnt_end; i++) {
    interrupt_set_config(i, INTERRUPT_LEVEL_TRIGGERED, 0, 15);
    if (i == 331)
      imc_wdt_handler = imc_wdt_WS0_handler;
    else
      imc_wdt_handler = imc_wdt_WS1_handler;
    ret_val = interrupt_register(i, imc_wdt_handler);
    if (ret_val == HDTS_FAIL) {
      shell_msg("WS0/WS1 interrupt register failed, para1=%d, para2=%d\n", i,
                imc_wdt_handler);
      return HDTS_FAIL;
    }
    imc_enable_interrupt(i);
  }
  if (secure == 1)
    switch_to_sec();
  else
    switch_to_nonsec();
  return HDTS_SUCCESS;
}
void imc_wdog_trigger() {
  /*enable watchdog timer, IMC_QTMR_WDT_CSR[WDT_EN]*/
  out_dword_masked_ns(IMC_QTMR_WDT_CSR_ADDR, 0x1, 0x1,
                      in_dword_masked(IMC_QTMR_WDT_CSR_ADDR, 0xf));
  DO_DSB;
  while (g_ws0_int_flag == 0) {
  }
  g_ws0_int_flag = 0;
  printf("WS0 interrupt is received, ");
  while (g_ws1_int_flag == 0) {
  }
  g_ws1_int_flag = 0;
  printf("WS1 interrupt is received\n");
  printf("PASSED, IMC wdog WS0 status= %d, WS1 status= %d\n",
         (g_wdt_csr_data & 0x2) >> 1, (g_wdt_csr_data & 0x4) >> 2);
}
