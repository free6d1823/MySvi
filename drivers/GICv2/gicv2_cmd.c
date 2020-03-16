/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#include <bits/alltypes.h>
#include <asm/hal/HALhwio.h>
#include <hdts_shell.h>
#include <imc_gicv2.h>
#include <target/cmdline.h>

#define SUCCESS 0
#define FAIL (-1)
static int do_gicv2(int argc, char *argv[]) {
  UINT8 typ_int;  /*FIQ, IRQ*/
  UINT8 trig_mod; /*level, edge*/
  UINT8 int_prio;
  UINT32 int_start = 0;
  UINT32 int_end = 0;
  UINT32 ret_val;
  UINT32 i;
  UINT8 pos_int_id = 0;
  if ((strcmp(argv[1], "intcfg") == 0) || (strcmp(argv[1], "inttrig") == 0)) {
    if (strcmp(argv[2], "all") == 0) {
      int_start = 0;
      int_end = GICV2_MSI_INT_END;
    }
    if (strcmp(argv[2], "allsgi") == 0) {
      int_start = 0;
      int_end = 15;
    }
    if (strcmp(argv[2], "allppi") == 0) {
      int_start = 16;
      int_end = 31;
    }
    if (strcmp(argv[2], "allspi") == 0) {
      int_start = 32;
      int_end = 543;
    }
    if (strcmp(argv[2], "allmsi") == 0) {
      int_start = GICV2_MSI_INT_START;
      int_end = GICV2_MSI_INT_END;
    }
    if (strcmp(argv[2], "selfdef") == 0) {
      if (strcmp(argv[1], "intcfg") == 0)
        pos_int_id = 7;
      else
        pos_int_id = 4;
      if ((argc != (pos_int_id + 1)) && (argc != pos_int_id)) {
        printf("number of parameter for intcfg/inttrig is illegal\n");
        return FAIL;
      }
      if (strtoull(argv[pos_int_id - 1], 0, 0) <= GICV2_MSI_INT_END)
        int_start = strtoull(argv[pos_int_id - 1], 0, 0);
      else {
        printf("illegal parameter 'int_id_start' for cmd gicv2 intcfg/inttrig "
               "selfdef, "
               "int_id#%d is out of range, maximum=%d\n",
               strtoull(argv[pos_int_id - 1], 0, 0), GICV2_MSI_INT_END);
        return FAIL;
      }
      if (argc == (pos_int_id + 1)) {
        if ((strtoull(argv[pos_int_id], 0, 0) <= GICV2_MSI_INT_END) &&
            (strtoull(argv[pos_int_id], 0, 0) >= int_start))
          int_end = strtoull(argv[pos_int_id], 0, 0);
        else {
          printf(
              "illegal parameter 'int_id_end' for cmd gicv2 intcfg selfdef\n");
          return FAIL;
        }
      } else
        int_end = int_start;
    }
    if ((strcmp(argv[2], "allmsi") != 0) && (strcmp(argv[2], "allppi") != 0) &&
        (strcmp(argv[2], "allspi") != 0) && (strcmp(argv[2], "allsgi") != 0) &&
        (strcmp(argv[2], "all") != 0) && (strcmp(argv[2], "selfdef") != 0)) {
      printf("incorrect parameter for intcfg/inttrig, parameter should be "
             "allmsi/allppi/allspi/allsgi/all/selfdef.\n");
      return FAIL;
    }
  }
  if (strcmp(argv[1], "intcfg") == 0) {
    int_prio = strtoull(argv[3], 0, 0);
    if (strcmp(argv[4], "fiq") == 0)
      typ_int = 1; /*FIQ*/
    else if (strcmp(argv[4], "irq") == 0)
      typ_int = 0; /*IRQ*/
    else {
      printf("input parameter for int type is incorrct, fiq/irq is legal\n");
      return FAIL;
    }
    if (strcmp(argv[5], "level") == 0) {
      for (i = int_start; i <= int_end; i++) {
        if ((i >= GICV2_MSI_INT_START) && (i <= GICV2_MSI_INT_END)) {
          printf("interrupt #%d is MSI interrupt, Must configure edge mode\n",
                 i);
          return FAIL;
        }
      }
      trig_mod = INTERRUPT_LEVEL_TRIGGERED; /*Level*/
    } else if (strcmp(argv[5], "edge") == 0)
      trig_mod = INTERRUPT_EDGE_TRIGGERED; /*edge*/
    else {
      printf("input parameter for trigger_mode is incorrct, level/edge is "
             "legal\n");
      return FAIL;
    }
    ret_val = imc_int_cfg(int_start, int_end, trig_mod, typ_int, int_prio,
                          gicv2_int_handler);
  }
  if (strcmp(argv[1], "inttrig") == 0) {
    if ((strcmp(argv[2], "all") != 0) && (strcmp(argv[2], "allspi") != 0) &&
        (strcmp(argv[2], "allppi") != 0) && (strcmp(argv[2], "allsgi") != 0) &&
        (strcmp(argv[2], "allmsi") != 0) && (strcmp(argv[2], "selfdef") != 0)) {
      printf("incorrect parameter for intcfg/inttrig, parameter should be "
             "allmsi/allppi/allspi/allsgi/all/selfdef.\n");
      return FAIL;
    }
    imc_int_trigger(int_start, int_end, 0);
  }
  if (strcmp(argv[1], "wdgcfg") == 0) {
    if (strcmp(argv[2], "s") == 0)
      ret_val = imc_wdog_config(1);
    else if (strcmp(argv[2], "ns") == 0)
      ret_val = imc_wdog_config(0);
    else {
      printf("parameter for wdgcfg is illegal, Must be s or ns\n");
      return FAIL;
    }
    if (ret_val == HDTS_FAIL) {
      printf("can't register ISR handler fro Watchdog\n");
      return FAIL;
    }
  }
  if (strcmp(argv[1], "wdgtrig") == 0) {
    imc_wdog_trigger();
  }
  if ((strcmp(argv[1], "wdgtrig") != 0) && (strcmp(argv[1], "wdgcfg") != 0) &&
      (strcmp(argv[1], "intcfg") != 0) && (strcmp(argv[1], "inttrig") != 0)) {
    printf("gicv2 subcmd is illegal, it should be "
           "intcfg/inttrig/wdgtrig/wdgcfg\n");
    return FAIL;
  }
  return SUCCESS;
}
#ifdef CONFIG_CONSOLE_COMMAND
MK_CMD(gicv2, do_gicv2, "configure and trigger interrupt of GICv2",
       " configure intterrupt type/trigger mode, trigger then check received "
       "interrupts, \n"
       " intcfg [allmsi|allppi|allsgi|allmsi|all] [priority] [irq|fiq] "
       "[level|edge] \n"
       "     priority:0~31 \n"
       " intcfg selfdef [priority] [irq|fiq] [level|edge] [int_id_start] "
       "[int_id_end(optional)] \n"
       "     int_id_start: 0~575 \n"
       "     int_id_end: 0~575 \n"
       " inttrig [allmsi|allppi|allsgi|allmsi|all] [int_id_start] "
       "[int_id_end(optional)] \n"
       "     int_id_start: 0~575 \n"
       "     int_id_end: 0~575 \n"
       " inttrig selfdef [int_id_start] [int_id_end(optional)] \n"
       "     int_id_start: 0~575 \n"
       "     int_id_end: 0~575 \n"
       " wdgcfg [s|ns] \n"
       " wdgtrig \n");
#endif // CONFIG_CONSOLE_COMMAND


