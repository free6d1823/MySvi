/*==============================================================================
  All Rights Reserved.

  ==============================================================================*/

#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "hdts/Base.h"
#include "hdts/hdts_common.h"
#include "hdts/hdts_misc.h"
#include "hdts/hdts_shell.h"
#include "target/delay.h"

#include "HALsataHWIO.h"
#include "asm/hal/HALhwio.h"
#include "sata_defs.h"
#include "sata_init.h"
#include "sata_regs.h"

// extern
extern UINTN Sata_Reg_Base[SATA_CONTROLLER_NUMBER];
extern UINTN Sata_Pcs_Lane_Reg_Base[SATA_CONTROLLER_NUMBER];

/**
 * @brief       Sata near end loopback function
 *
 * @param[in]   ControllerNum    Sata Controller/Lane number. (0~7)
 *
 * @param[in]   pattern		 Pattern. (0~8)
 *
 * @param[in]   seconds 	 Test time. (>=1 sec)
 *
 * @return      None
 */
void sata_loopback_nea(UINT32 ControllerNum, UINT32 pattern, UINT32 seconds) {
  UINTN Base = Sata_Reg_Base[ControllerNum];
  UINT64 delay = 500;
  UINT32 val = 0;
  UINT32 i = 0;
  UINT32 count = 0;

  printf("****** SATA %d Pattern %d near end loopback test. Time:%d seconds "
         "******\r\n",
         ControllerNum, pattern, seconds);

  // GHC reset
  out_dword(Base + HWIO_SATA_GHC_OFFS,
            HWIO_SATA_GHC_AHCI_ENABLE | HWIO_SATA_GHC_HBA_RESET);
  do {
    val = in_dword(Base + HWIO_SATA_GHC_OFFS);

    if ((val & HWIO_SATA_GHC_HBA_RESET) == 0) {
      break;
    }

    udelay(10000);
    delay--;
  } while (delay > 0);

  if (delay == 0) {
    printf("[ERROR]SATA reset fail!\r\n");
    return;
  }

  // CAP
  out_dword(Base + HWIO_SATA_CAP_OFFS, 0xEF36FF80);

  // P0CMD
  out_dword(Base + HWIO_SATA_P0CMD_OFFS, 0x6);

  // TESTR
  out_dword(Base + HWIO_SATA_TESTR_OFFS, 0);

  // BISTCR (pattern 0~8)
  out_dword(Base + HWIO_SATA_BISTCR_OFFS, 0x10700 | pattern);

  for (i = 0; i < seconds; i++)
    udelay(1000000);

  // check
  if ((in_dword(Base + HWIO_SATA_BISTFCTR_OFFS) == 0) ||
      (in_dword(Base + HWIO_SATA_BISTSR_OFFS) != 0) ||
      (in_dword(Base + HWIO_SATA_P0SERR_OFFS) != 0)) {
    count++;
    printf("[ERROR] Test Fail!\r\n");
    printf("[ERROR] SATA BISTFCTR[0x%lx] 0x%x\r\n",
           (Base + HWIO_SATA_BISTFCTR_OFFS),
           in_dword(Base + HWIO_SATA_BISTFCTR_OFFS));
    printf("[ERROR] SATA BISTSR[0x%lx] 0x%x\r\n",
           (Base + HWIO_SATA_BISTSR_OFFS),
           in_dword(Base + HWIO_SATA_BISTSR_OFFS));
    printf("[ERROR] SATA SERR[0x%lx] 0x%x\r\n", (Base + HWIO_SATA_P0SERR_OFFS),
           in_dword(Base + HWIO_SATA_P0SERR_OFFS));
  }

  printf("SATA BISTFCTR[0x%lx] count 0x%x\r\n",
         (Base + HWIO_SATA_BISTFCTR_OFFS),
         in_dword(Base + HWIO_SATA_BISTFCTR_OFFS));

  // clear nea test count
  out_dword(Base + HWIO_SATA_BISTCR_OFFS, 0x20700);

  // GHC reset
  out_dword(Base + HWIO_SATA_GHC_OFFS,
            HWIO_SATA_GHC_AHCI_ENABLE | HWIO_SATA_GHC_HBA_RESET);
  do {
    val = in_dword(Base + HWIO_SATA_GHC_OFFS);

    if ((val & HWIO_SATA_GHC_HBA_RESET) == 0) {
      break;
    }

    udelay(10000);
    delay--;
  } while (delay > 0);

  if (delay == 0) {
    printf("[ERROR] SATA reset fail!\r\n");
    return;
  }

  if (count != 0)
    printf("****** [FAIL] SATA %d Pattern %d near end loopback test. Time:%d "
           "seconds ******\r\n",
           ControllerNum, pattern, seconds);
  else
    printf("****** [PASS] SATA %d Pattern %d near end loopback test. Time:%d "
           "seconds ******\r\n",
           ControllerNum, pattern, seconds);
}

/**
 * @brief       Sata loopback of phy external function
 *
 * @param[in]   ControllerNum    Sata Controller/Lane number. (0~7)
 *
 * @param[in]   speed     	 Sata phy speed GEN1~3. (0~2)
 *
 * @param[in]   prbs    	 PRBS 7/9/10. (0~2)
 *
 * @return      None
 *
 * @note	Depend on the connection of sata tx and rx
 */
void sata_loopback_phy_external(UINT32 ControllerNum, UINT32 speed,
                                UINT32 prbs) {
  UINTN Base = Sata_Pcs_Lane_Reg_Base[ControllerNum];
  UINT32 speed_set = 0;
  UINT32 prbs_print = 0;
  UINT32 count = 0;

  if (speed == SATA_PHY_SPEED_GEN1)
    speed_set = 0xc;
  else if (speed == SATA_PHY_SPEED_GEN2)
    speed_set = 0x5d;
  else
    speed_set = 0xae;

  if (prbs == SATA_PHY_PRBS_7)
    prbs_print = 7;
  else if (prbs == SATA_PHY_PRBS_9)
    prbs_print = 9;
  else
    prbs_print = 10;

  printf("****** SATA %d PRBS%d Speed Gen%d phy external test ******\r\n",
         ControllerNum, prbs_print, speed + 1);

  // SPDNEG
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_SPDNEG_CFG1_OFFS, speed_set);

  // LANE CTRL1
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_CTRL1_OFFS, 0x80);

  // PHY OFFLINE
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_OFFLINE_OFFS, 0x10);

  // PHY RESET CTRL
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_OFFS, 0x4);

  // PHY ALIGNP
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_ALIGNP_OFFS, 0x23);

  // PHY BIST GEN3
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS, 0x1);

  // PHY TX DATA CTRL
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_TX_DATA_CTRL_OFFS, 0x3e);

  // PHY BIST GEN2
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN2_OFFS, 0xc);

  // PHY BIST GEN3
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS, 0x5);
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS, 0x1);

  // PHY PRBS CFG0 (PRBS 7/9/10)
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG0_OFFS, prbs);

  // PHY PRBS CFG4
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG4_OFFS, 0xff);

  // PHY PRBS CFG5
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG5_OFFS, 0xf2);

  // PHY PRBS CFG6
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG6_OFFS, 0x0);

  // PHY BIST GEN3
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS, 0x11);

  if ((in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS) & 0x1) !=
      0) {
    count++;
    printf("[ERROR] SATA PHY RX CHK STATUS not clear![0x%lx] 0x%x\r\n",
           (Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS),
           in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS));
  }

  udelay(10000);

  // check
  if (((in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS) &
        0x1) != 1) ||
      (in_dword(Base +
                HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT0_STATUS_OFFS) !=
       0) ||
      (in_dword(Base +
                HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT1_STATUS_OFFS) !=
       0)) {
    count++;
    printf("[ERROR] Test Fail!\r\n");
  }

  printf("SATA PHY RX CHK STATUS[0x%lx] 0x%x\r\n",
         (Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS),
         in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS));
  printf(
      "SATA PHY RX CHK ERR CNT0[0x%lx] 0x%x\r\n",
      (Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT0_STATUS_OFFS),
      in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT0_STATUS_OFFS));
  printf(
      "SATA PHY RX CHK ERR CNT1[0x%lx] 0x%x\r\n",
      (Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT1_STATUS_OFFS),
      in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT1_STATUS_OFFS));

  // PHY reset
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_OFFS, 0x1);
  udelay(1000);

  if (count != 0)
    printf(
        "****** [FAIL] SATA %d PRBS%d Speed Gen%d phy external test ******\r\n",
        ControllerNum, prbs_print, speed + 1);
  else
    printf(
        "****** [PASS] SATA %d PRBS%d Speed Gen%d phy external test ******\r\n",
        ControllerNum, prbs_print, speed + 1);
}

/**
 * @brief       Sata loopback of phy internal function
 *
 * @param[in]   ControllerNum    Sata Controller/Lane number. (0~7)
 *
 * @param[in]   speed    	 Sata phy speed GEN1~3. (0~2)
 *
 * @param[in]   prbs    	 PRBS 7/9/10. (0~2)
 *
 * @return      None
 */
void sata_loopback_phy_internal(UINT32 ControllerNum, UINT32 speed,
                                UINT32 prbs) {
  UINTN Base = Sata_Pcs_Lane_Reg_Base[ControllerNum];
  UINT32 speed_set = 0;
  UINT32 prbs_print = 0;
  UINT32 count = 0;

  if (speed == SATA_PHY_SPEED_GEN1)
    speed_set = 0xc;
  else if (speed == SATA_PHY_SPEED_GEN2)
    speed_set = 0x5d;
  else
    speed_set = 0xae;

  if (prbs == SATA_PHY_PRBS_7)
    prbs_print = 7;
  else if (prbs == SATA_PHY_PRBS_9)
    prbs_print = 9;
  else
    prbs_print = 10;

  printf("****** SATA %d PRBS%d Speed Gen%d phy internal test ******\r\n",
         ControllerNum, prbs_print, speed + 1);

  // SPDNEG
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_SPDNEG_CFG1_OFFS, speed_set);

  // LANE CTRL1
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_LANE_CTRL1_OFFS, 0x80);

  // PHY OFFLINE
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_OFFLINE_OFFS, 0x10);

  // PHY RESET CTRL
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_OFFS, 0x4);

  // PHY ALIGNP
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_ALIGNP_OFFS, 0x23);

  // PHY BIST GEN3
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS, 0xc1);

  // PHY TX DATA CTRL
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_TX_DATA_CTRL_OFFS, 0x34);

  // PHY BIST GEN2
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN2_OFFS, 0xc);

  // PHY BIST GEN3
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS, 0xc5);
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS, 0xc1);

  // PHY PRBS CFG0 (PRBS 7/9/10)
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG0_OFFS, prbs);

  // PHY PRBS CFG4
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG4_OFFS, 0x59);

  // PHY PRBS CFG5
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG5_OFFS, 0x4);

  // PHY PRBS CFG6
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_PRBS_CFG6_OFFS, 0x0);

  // PHY BIST GEN3
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_BIST_GEN3_OFFS, 0xd1);

  if ((in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS) & 0x1) !=
      0) {
    count++;
    printf("[ERROR] SATA PHY RX CHK STATUS not clear![0x%lx] 0x%x\r\n",
           (Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS),
           in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS));
  }

  udelay(10000);

  // check
  if (((in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS) &
        0x1) != 1) ||
      (in_dword(Base +
                HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT0_STATUS_OFFS) !=
       0) ||
      (in_dword(Base +
                HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT1_STATUS_OFFS) !=
       0)) {
    count++;
    printf("[ERROR] Test Fail!\r\n");
  }

  printf("SATA PHY RX CHK STATUS[0x%lx] 0x%x\r\n",
         (Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS),
         in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_STATUS_OFFS));
  printf(
      "SATA PHY RX CHK ERR CNT0[0x%lx] 0x%x\r\n",
      (Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT0_STATUS_OFFS),
      in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT0_STATUS_OFFS));
  printf(
      "SATA PHY RX CHK ERR CNT1[0x%lx] 0x%x\r\n",
      (Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT1_STATUS_OFFS),
      in_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RX_CHK_ERR_CNT1_STATUS_OFFS));

  // PHY reset
  out_dword(Base + HWIO_SP_SATA_PHY_L_SATA_PHY_RESET_CTRL_OFFS, 0x1);
  udelay(1000);

  if (count != 0)
    printf(
        "****** [FAIL] SATA %d PRBS%d Speed Gen%d phy internal test ******\r\n",
        ControllerNum, prbs_print, speed + 1);
  else
    printf(
        "****** [PASS] SATA %d PRBS%d Speed Gen%d phy internal test ******\r\n",
        ControllerNum, prbs_print, speed + 1);
}

/**
 * @brief       Sata phy loopback function
 *
 * @param[in]   ControllerNum    Sata Controller/Lane number. (0~7)
 *
 * @param[in]   TestMode    	 Sata phy loopback test mode. (0~1)
 *
 * @param[in]   speed    	 Sata phy speed GEN1~3. (0~2)
 *
 * @param[in]   prbs    	 PRBS 7/9/10. (0~2)
 *
 * @return      None
 */
void sata_loopback_phy(UINT32 ControllerNum, UINT32 TestMode, UINT32 speed,
                       UINT32 prbs) {
  switch (TestMode) {
  case 0:
    sata_loopback_phy_internal(ControllerNum, speed, prbs);
    break;

  case 1:
    sata_loopback_phy_external(ControllerNum, speed, prbs);
    break;

  default:
    printf("[ERROR] Illegal phy loopback test mode %d, expect (0~1)\r\n",
           TestMode);
    break;
  }
}
