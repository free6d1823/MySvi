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
#include "asm/mach/hal/HALbootHWIO.h"
#include "asm/mach/hal/HALclkHWIO.h"
#include "asm/mach/monaco/common/boot_util.h"
#include "sata_defs.h"
#include "sata_init.h"
#include "sata_regs.h"

// extern
extern UINTN Sata_Reg_Base[SATA_CONTROLLER_NUMBER];
extern volatile UINT32 gSataIntrMaskEn;

// global
SataDevice_t gSataDevInfo;
UINTN mMaxTransferBlockNumber[] = {MAX_28BIT_TRANSFER_BLOCK_NUM,
                                   MAX_48BIT_TRANSFER_BLOCK_NUM};

UINT8 mAtaCommands[][2]
                  [2] = {{{
                              ATA_CMD_READ_SECTORS, // 28-bit LBA; PIO read
                              ATA_CMD_WRITE_SECTORS // 28-bit LBA; PIO write
                          },
                          {
                              ATA_CMD_READ_SECTORS_EXT, // 48-bit LBA; PIO read
                              ATA_CMD_WRITE_SECTORS_EXT // 48-bit LBA; PIO write
                          }},
                         {{
                              ATA_CMD_READ_DMA, // 28-bit LBA; DMA read
                              ATA_CMD_WRITE_DMA // 28-bit LBA; DMA write
                          },
                          {
                              ATA_CMD_READ_DMA_EXT, // 48-bit LBA; DMA read
                              ATA_CMD_WRITE_DMA_EXT // 48-bit LBA; DMA write
                          }}};

UINT8 mAtaFpdmaCmds[2] = {ATA_CMD_READ_FPDMA, ATA_CMD_WRITE_FPDMA};

UINT8 mAtaPassThruCmdProtocols[][2] = {
    {ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN, ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT},
    {
        ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN,
        ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT,
    }};

UINT8 mAtaFpdmaXferProtocols[] = {ATA_XFER_PROTOCOL_FPDMA_DATA_IN,
                                  ATA_XFER_PROTOCOL_FPDMA_DATA_OUT};

static const char *const udma_mode_str[] = {
    "UDMA/16", "UDMA/25",  "UDMA/33",  "UDMA/44",
    "UDMA/66", "UDMA/100", "UDMA/133", "UDMA7",
};

// In boot stage, default PIO mode
void sata_build_command(SataDevice_t *device, ATATransCmdPacket_t *packet,
                        BOOLEAN is_write,
                        SATA_AHCI_COMMAND_TABLE_t *cmd_tab_addr,
                        SATA_AHCI_COMMAND_LIST_t *cmd_list_addr) {
  UINT32 val = 0;
  UINT64 prdt_addr;
  UINTN Base = Sata_Reg_Base[device->Controller];
  UINT32 prdt_num = 0;
  UINT64 xfer_len = 0;
  UINT32 index = 0;

  // build command table
  cmd_tab_addr->CommandFis.AhciCFisType = 0x27; // host2device
  cmd_tab_addr->CommandFis.AhciCFisCmdInd = 0x01;
  cmd_tab_addr->CommandFis.AhciCFisCmd = packet->Acb->AtaCommand;
  cmd_tab_addr->CommandFis.AhciCFisFeature = packet->Acb->AtaFeatures;
  cmd_tab_addr->CommandFis.AhciCFisFeatureExp = packet->Acb->AtaFeaturesExp;
  cmd_tab_addr->CommandFis.AhciCFisSecNum = packet->Acb->AtaSectorNumber;
  cmd_tab_addr->CommandFis.AhciCFisSecNumExp = packet->Acb->AtaSectorNumberExp;
  cmd_tab_addr->CommandFis.AhciCFisClyLow = packet->Acb->AtaCylinderLow;
  cmd_tab_addr->CommandFis.AhciCFisClyLowExp = packet->Acb->AtaCylinderLowExp;
  cmd_tab_addr->CommandFis.AhciCFisClyHigh = packet->Acb->AtaCylinderHigh;
  cmd_tab_addr->CommandFis.AhciCFisClyHighExp = packet->Acb->AtaCylinderHighExp;
  cmd_tab_addr->CommandFis.AhciCFisSecCount = packet->Acb->AtaSectorCount;
  cmd_tab_addr->CommandFis.AhciCFisSecCountExp = packet->Acb->AtaSectorCountExp;
  cmd_tab_addr->CommandFis.AhciCFisDevHead =
      (UINT8)(packet->Acb->AtaDeviceHead | 0xE0);
  cmd_tab_addr->CommandFis.AhciCFisPmNum = 0; // port number

  if (is_write) {
    prdt_addr = (UINT64)packet->OutDataBuffer;
    xfer_len = (UINT64)packet->OutTransferLength;
  } else {
    prdt_addr = (UINT64)packet->InDataBuffer;
    xfer_len = (UINT64)packet->InTransferLength;
  }

  // calculate prdt
  prdt_num = (xfer_len + SATA_MAX_DATA_PER_PRDT - 1) / SATA_MAX_DATA_PER_PRDT;
  cmd_list_addr->AhciCmdPrdtl = prdt_num;
  if (prdt_num > 0)
    cmd_tab_addr->PrdtTable[prdt_num - 1].AhciPrdtIoc = 1;
  else
    cmd_tab_addr->PrdtTable[0].AhciPrdtDbc = 0;

  for (index = 0; index < prdt_num; index++) {
    if (xfer_len < SATA_MAX_DATA_PER_PRDT)
      cmd_tab_addr->PrdtTable[index].AhciPrdtDbc = (UINT32)xfer_len - 1;
    else
      cmd_tab_addr->PrdtTable[index].AhciPrdtDbc = SATA_MAX_DATA_PER_PRDT - 1;

    cmd_tab_addr->PrdtTable[index].AhciPrdtDba =
        (UINT32)(prdt_addr & 0xffffffff);
    cmd_tab_addr->PrdtTable[index].AhciPrdtDbau =
        (UINT32)((prdt_addr >> 32) & 0xffffffff);

    xfer_len -= SATA_MAX_DATA_PER_PRDT;
    prdt_addr += SATA_MAX_DATA_PER_PRDT;
  }

  // build command list. Just 1
  cmd_list_addr->AhciCmdCfl = 5;              // 5 UINT32 (20/4)
  cmd_list_addr->AhciCmdW = is_write ? 1 : 0; // read 0, write 1;
  cmd_list_addr->AhciCmdPmp = 0;              // no multiport
  cmd_list_addr->AhciCmdCtba = (UINT32)((UINT64)cmd_tab_addr & 0xffffffff);
  cmd_list_addr->AhciCmdCtbau =
      (UINT32)(((UINT64)cmd_tab_addr >> 32) & 0xffffffff);

  // CMD clear PORT_CMD_DLAE | PORT_CMD_ATAPI
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  out_dword(Base + HWIO_SATA_P0CMD_OFFS,
            val & (UINT32)(~(HWIO_SATA_P0CMD_ATAPI | HWIO_SATA_P0CMD_DLAE)));
}

void sata_start_command(SataDevice_t *device, UINT32 cmd_slots) {
  UINT32 val = 0;
  UINT32 startcmd = 0;
  UINT32 tfd = 0;
  UINT32 capability = 0;
  UINT32 delay = 3000000; // three sec
  UINTN Base = Sata_Reg_Base[device->Controller];

  // clear serr status
  val = in_dword(Base + HWIO_SATA_P0SERR_OFFS);
  out_dword(Base + HWIO_SATA_P0SERR_OFFS, val);

  // clear any port interrupt status
  val = in_dword(Base + HWIO_SATA_P0IS_OFFS);
  out_dword(Base + HWIO_SATA_P0IS_OFFS, val);

  // clear any HBA interrupt status
  val = in_dword(Base + HWIO_SATA_IS_OFFS);
  out_dword(Base + HWIO_SATA_IS_OFFS, val);

  // enable fis receive
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  out_dword(Base + HWIO_SATA_P0CMD_OFFS, val | HWIO_SATA_P0CMD_FRE);

  // start cmd
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  if ((val & HWIO_SATA_P0CMD_ALPE) != 0) {
    startcmd = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
    startcmd &= ~HWIO_SATA_P0CMD_ICC_RMSK;
    startcmd |= HWIO_SATA_P0CMD_ICC_ACTIVE;
  }

  // check tfd
  capability = in_dword(Base + HWIO_SATA_CAP_OFFS);
  tfd = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
  if ((tfd & (HWIO_SATA_P0TFD_BSY | HWIO_SATA_P0TFD_DRQ)) != 0) {
    if ((capability & BIT24) != 0) // process command list override
    {
      val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
      out_dword(Base + HWIO_SATA_P0CMD_OFFS, val | BIT3);

      do {
        val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
        if ((val & BIT3) == 0)
          break;

        udelay(1000); // delay 1ms

        if (delay > 1000)
          delay -= 1000;
        else
          delay = 0;

      } while (delay > 0);

      if (delay == 0)
        printf("[ERROR] Sata start cmd fail for clear P0CMD BIT3\r\n");
    }
  }

  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  out_dword(Base + HWIO_SATA_P0CMD_OFFS,
            val | HWIO_SATA_P0CMD_START | startcmd);

  if (device->FpdmaEnable)
    out_dword(Base + HWIO_SATA_P0SACT_OFFS, cmd_slots);

  // reset and set cmd list slot to indicate slot 0 is ready
  out_dword(Base + HWIO_SATA_P0CI_OFFS, 0);
  out_dword(Base + HWIO_SATA_P0CI_OFFS, cmd_slots);
}

BOOLEAN sata_check_mem_set(UINT64 addr, UINT32 mask, UINT32 test) {
  UINT32 val = 0;

  val = *(volatile UINT32 *)(UINTN)addr;
  val &= mask;

  if (val == test)
    return TRUE;

  return FALSE;
}

BOOLEAN sata_wait_mem_set(UINT64 addr, UINT32 mask, UINT32 test,
                          UINT64 timeout_us) {
  BOOLEAN infinit_wait = FALSE;
  UINT64 delay = timeout_us;
  UINT32 val = 0;

  if (timeout_us == 0)
    infinit_wait = TRUE;

  do {
    val = *(volatile UINT32 *)(UINTN)addr;
    val &= mask;

    if (val == test)
      return TRUE;

    udelay(100000); // delay 100ms

    if (delay > 100000)
      delay -= 100000;
    else
      delay = 0;

  } while (infinit_wait || (delay > 0));

  return FALSE;
}

void sata_stop_command(SataDevice_t *device) {
  UINT32 val = 0;
  UINTN Base = Sata_Reg_Base[device->Controller];

  // stop command
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  if ((val & (HWIO_SATA_P0CMD_START | HWIO_SATA_P0CMD_CR)) == 0) {
    printf("SATA cmd stoped! P0CMD[0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0CMD_OFFS), val);
    return;
  }

  if ((val & HWIO_SATA_P0CMD_START) != 0) {
    val &= (UINT32) ~(HWIO_SATA_P0CMD_START);
    out_dword(Base + HWIO_SATA_P0CMD_OFFS, val);
  }

  while ((val & HWIO_SATA_P0CMD_CR) != 0) {
    udelay(1000);
    val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
    printf("SATA stop cmd, checking P0CMD[0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0CMD_OFFS), val);
  }
  printf("SATA stop cmd done! P0CMD[0x%x] 0x%x\r\n",
         (Base + HWIO_SATA_P0CMD_OFFS), val);
}

void sata_disable_rfis(SataDevice_t *device) {
  UINT32 val = 0;
  UINTN Base = Sata_Reg_Base[device->Controller];

  // stop receive fis
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  if ((val & (HWIO_SATA_P0CMD_START | HWIO_SATA_P0CMD_CR)) != 0) {
    printf("[ERROR] Sata disable receive fis, unsupported!!!\r\n");
    return;
  }

  if ((val & HWIO_SATA_P0CMD_FR) != HWIO_SATA_P0CMD_FR) {
    printf("SATA recv fis disabled! P0CMD[0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0CMD_OFFS), val);
    return;
  }

  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  val &= (UINT32)(~(HWIO_SATA_P0CMD_FRE));
  out_dword(Base + HWIO_SATA_P0CMD_OFFS, val);

  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  while ((val & HWIO_SATA_P0CMD_FR) != 0) {
    udelay(1000);
    val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
    printf("SATA stop receive fis, checking P0CMD[0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0CMD_OFFS), val);
  }
  printf("SATA stop recv fis done! P0CMD[0x%x] 0x%x\r\n",
         (Base + HWIO_SATA_P0CMD_OFFS), val);
}

void sata_dump_port_st(SataDevice_t *device, ATATransCmdPacket_t *packet,
                       SATA_AHCI_RECEIVED_FIS_t *fis_recv_addr) {
  UINT32 val = 0;
  UINTN Base = Sata_Reg_Base[device->Controller];

  if (sata_check_mem_set((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET,
                         AHCI_FIS_TYPE_MASK, AHCI_FIS_REGISTER_D2H)) {
    // D2H fis received, update
    memcpy(packet->Asb, (UINT8 *)((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET),
           sizeof(ATAStatusBlock_t));
  } else {
    val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
    packet->Asb->AtaStatus = (UINT8)val;
    if ((val & BIT0) != 0)
      packet->Asb->AtaError = (UINT8)(val >> 8);
  }
}

void sata_pio_transfer(SataDevice_t *device, ATATransCmdPacket_t *packet,
                       BOOLEAN is_write, UINT64 timeout_us) {
  UINTN Base = Sata_Reg_Base[device->Controller];
  SATA_AHCI_COMMAND_TABLE_t *cmd_tab_addr;
  SATA_AHCI_COMMAND_LIST_t *cmd_list_addr;
  SATA_AHCI_RECEIVED_FIS_t *fis_recv_addr;
  UINT32 val = 0;
  UINT64 delay = timeout_us;
  BOOLEAN infinit_wait = FALSE;
  BOOLEAN pio_fis_recv;
  BOOLEAN d2h_fis_recv;

  // clear memory 128K bytes
  memset((UINT8 *)SATA_OP_BUF_SMEM_ADDR, 0, SATA_OP_BUF_SMEM_SIZE);
  cmd_tab_addr = (SATA_AHCI_COMMAND_TABLE_t *)SATA_CMD_TAB_SMEM_ADDR;
  cmd_list_addr = (SATA_AHCI_COMMAND_LIST_t *)SATA_CMD_LIST_SMEM_ADDR;
  fis_recv_addr = (SATA_AHCI_RECEIVED_FIS_t *)SATA_FIS_RECV_SMEM_ADDR;

  sata_build_command(device, packet, is_write, cmd_tab_addr, cmd_list_addr);
  sata_start_command(device, 0x1);

  // checking
  if (is_write) // out
  {
    if (sata_wait_mem_set((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET,
                          AHCI_FIS_TYPE_MASK, AHCI_FIS_REGISTER_D2H,
                          timeout_us)) {
      val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
      if ((val & BIT0) != 0) {
        printf("[ERROR]Error in pio out transfer!\r\n");
      } else {
        printf("Pio out transfer ok!\r\n");
      }
    } else
      printf("[ERROR]Pio out transfer, get wrong d2h fis 0x%x\r\n",
             *(volatile UINT32 *)((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET));
  } else // in
  {
    if (delay == 0)
      infinit_wait = TRUE;
    else
      infinit_wait = FALSE;

    do {
      pio_fis_recv = FALSE;
      d2h_fis_recv = FALSE;

      if (sata_check_mem_set((UINT64)fis_recv_addr + AHCI_PIO_FIS_OFFSET,
                             AHCI_FIS_TYPE_MASK, AHCI_FIS_PIO_SETUP))
        pio_fis_recv = TRUE;

      if (sata_check_mem_set((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET,
                             AHCI_FIS_TYPE_MASK, AHCI_FIS_REGISTER_D2H))
        d2h_fis_recv = TRUE;

      if (pio_fis_recv || d2h_fis_recv) {
        val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
        if ((val & BIT0) != 0) {
          printf("[ERROR]Error in pio in transfer!\r\n");
          break;
        }

        if (packet->InTransferLength == cmd_list_addr->AhciCmdPrdbc) {
          printf("Pio in transfer get expect len %d\r\n",
                 packet->InTransferLength);
          break;
        } else {
          printf("[ERROR]Pio in transfer get wrong data len %d, expect %d\r\n",
                 cmd_list_addr->AhciCmdPrdbc, packet->InTransferLength);
        }
      }

      udelay(100000); // delay 100ms

      if (delay > 100000)
        delay -= 100000;
      else
        delay = 0;
    } while (infinit_wait || (delay > 0));
  }

  // stop command and disable fis receive
  sata_stop_command(device);
  sata_disable_rfis(device);

  // Dump port status. update ASB (ata status block)
  sata_dump_port_st(device, packet, fis_recv_addr);
}

void sata_dma_transfer(SataDevice_t *device, ATATransCmdPacket_t *packet,
                       BOOLEAN is_write, UINT64 timeout_us) {
  UINTN Base = Sata_Reg_Base[device->Controller];
  SATA_AHCI_COMMAND_TABLE_t *cmd_tab_addr;
  SATA_AHCI_COMMAND_LIST_t *cmd_list_addr;
  SATA_AHCI_RECEIVED_FIS_t *fis_recv_addr;
  UINT32 val = 0;

  // clear memory 128K bytes
  memset((UINT8 *)SATA_OP_BUF_SMEM_ADDR, 0, SATA_OP_BUF_SMEM_SIZE);
  cmd_tab_addr = (SATA_AHCI_COMMAND_TABLE_t *)SATA_CMD_TAB_SMEM_ADDR;
  cmd_list_addr = (SATA_AHCI_COMMAND_LIST_t *)SATA_CMD_LIST_SMEM_ADDR;
  fis_recv_addr = (SATA_AHCI_RECEIVED_FIS_t *)SATA_FIS_RECV_SMEM_ADDR;

  // just for TaskFileError & Overflow interrupt testing
  if (((gSataIntrMaskEn & SATA_INTR_OFE) != 0) ||
      ((gSataIntrMaskEn & SATA_INTR_TFEE) != 0)) {
    sata_interrupt_init(device->Controller, gSataIntrMaskEn);
  }

  sata_build_command(device, packet, is_write, cmd_tab_addr, cmd_list_addr);
  sata_start_command(device, 0x1);

  // just for TaskFileError & Overflow interrupt testing
  if (((gSataIntrMaskEn & SATA_INTR_OFE) != 0) ||
      ((gSataIntrMaskEn & SATA_INTR_TFEE) != 0)) {
    udelay(100000);
    sata_interrupt_check(device->Controller, gSataIntrMaskEn);
    sata_interrupt_deinit(device->Controller);
    return;
  }

  // checking
  if (sata_wait_mem_set((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET,
                        AHCI_FIS_TYPE_MASK, AHCI_FIS_REGISTER_D2H,
                        timeout_us)) {
    val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
    if ((val & BIT0) != 0) {
      printf("[ERROR]Error for dma transfer!\r\n");
    } else {
      printf("Dma transfer ok!\r\n");
    }
  } else
    printf("[ERROR]Dma transfer, get wrong d2h fis 0x%x\r\n",
           *(volatile UINT32 *)((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET));

  // stop command and disable fis receive
  sata_stop_command(device);
  sata_disable_rfis(device);

  // Dump port status. update ASB (ata status block)
  sata_dump_port_st(device, packet, fis_recv_addr);
}

void sata_fpdma_transfer(SataDevice_t *device, ATATransCmdPacket_t *packet,
                         BOOLEAN is_write, UINT64 timeout_us) {
  UINTN Base = Sata_Reg_Base[device->Controller];
  SATA_AHCI_COMMAND_TABLE_t *cmd_tab_addr;
  SATA_AHCI_COMMAND_LIST_t *cmd_list_addr;
  SATA_AHCI_RECEIVED_FIS_t *fis_recv_addr;
  UINT32 val = 0;

  // clear memory 128K bytes
  memset((UINT8 *)SATA_OP_BUF_SMEM_ADDR, 0, SATA_OP_BUF_SMEM_SIZE);
  cmd_tab_addr = (SATA_AHCI_COMMAND_TABLE_t *)SATA_CMD_TAB_SMEM_ADDR;
  cmd_list_addr = (SATA_AHCI_COMMAND_LIST_t *)SATA_CMD_LIST_SMEM_ADDR;
  fis_recv_addr = (SATA_AHCI_RECEIVED_FIS_t *)SATA_FIS_RECV_SMEM_ADDR;

  sata_build_command(device, packet, is_write, cmd_tab_addr, cmd_list_addr);
  sata_start_command(device, 0x1);

  // checking
  if (sata_wait_mem_set((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET,
                        AHCI_FIS_TYPE_MASK, AHCI_FIS_REGISTER_D2H,
                        timeout_us)) {
    val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
    if ((val & BIT0) != 0) {
      printf("[ERROR]Error D2H for fpdma transfer!\r\n");
      goto done;
    } else {
      printf("Fpdma transfer cmd ok!\r\n");
    }
  } else {
    printf("[ERROR]Fpdma transfer, get wrong d2h fis 0x%x\r\n",
           *(volatile UINT32 *)((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET));
    goto done;
  }

  if (sata_wait_mem_set((UINT64)fis_recv_addr + AHCI_SDB_FIS_OFFSET,
                        AHCI_FIS_TYPE_MASK, AHCI_FIS_SET_DEVICE, timeout_us)) {
    val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
    if ((val & BIT0) != 0) {
      printf("[ERROR]Error SDB for fpdma transfer!\r\n");
      goto done;
    } else {
      printf("Fpdma transfer data ok!\r\n");
    }
  } else {
    printf("[ERROR]Fpdma transfer, get wrong set dev bits fis 0x%x\r\n",
           *(volatile UINT32 *)((UINT64)fis_recv_addr + AHCI_SDB_FIS_OFFSET));
    goto done;
  }

done:
  // stop command and disable fis receive
  sata_stop_command(device);
  sata_disable_rfis(device);

  // Dump port status. update ASB (ata status block)
  sata_dump_port_st(device, packet, fis_recv_addr);
}

void sata_nondata_transfer(SataDevice_t *device, ATATransCmdPacket_t *packet,
                           UINT64 timeout_us) {
  UINTN Base = Sata_Reg_Base[device->Controller];
  SATA_AHCI_COMMAND_TABLE_t *cmd_tab_addr;
  SATA_AHCI_COMMAND_LIST_t *cmd_list_addr;
  SATA_AHCI_RECEIVED_FIS_t *fis_recv_addr;
  BOOLEAN is_write = FALSE;
  UINT32 val = 0;

  // clear memory 128K bytes
  memset((UINT8 *)SATA_OP_BUF_SMEM_ADDR, 0, SATA_OP_BUF_SMEM_SIZE);
  cmd_tab_addr = (SATA_AHCI_COMMAND_TABLE_t *)SATA_CMD_TAB_SMEM_ADDR;
  cmd_list_addr = (SATA_AHCI_COMMAND_LIST_t *)SATA_CMD_LIST_SMEM_ADDR;
  fis_recv_addr = (SATA_AHCI_RECEIVED_FIS_t *)SATA_FIS_RECV_SMEM_ADDR;

  // the receive fis and cmd list addr had been registered in init stage
  sata_build_command(device, packet, is_write, cmd_tab_addr, cmd_list_addr);
  sata_start_command(device, 0x1);

  if (sata_wait_mem_set((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET,
                        AHCI_FIS_TYPE_MASK, AHCI_FIS_REGISTER_D2H,
                        timeout_us)) {
    val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
    if ((val & BIT0) != 0)
      printf("[ERROR]Error in no data transfer!\r\n");
    else
      printf("No data transfer ok!\r\n");
  } else
    printf("[ERROR]No data transfer, get wrong d2h fis 0x%x\r\n",
           *(volatile UINT32 *)((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET));

  // stop command and disable fis receive
  sata_stop_command(device);
  sata_disable_rfis(device);

  // Dump port status. update ASB (ata status block)
  sata_dump_port_st(device, packet, fis_recv_addr);
}

void sata_set_feature(SataDevice_t *device, UINT16 feature,
                      UINT32 feature_data) {
  ATACmdBlock_t acb;
  ATAStatusBlock_t asb;
  ATATransCmdPacket_t packet;

  // clear
  memset(&acb, 0, sizeof(ATACmdBlock_t));
  memset(&asb, 0, sizeof(ATAStatusBlock_t));
  memset(&packet, 0, sizeof(ATATransCmdPacket_t));

  // ATA command
  acb.AtaCommand = ATA_CMD_SET_FEATURES;
  acb.AtaFeatures = (UINT8)feature;
  acb.AtaFeaturesExp = (UINT8)(feature >> 8);
  acb.AtaSectorCount = (UINT8)feature_data;
  acb.AtaSectorNumber = (UINT8)(feature_data >> 8);
  acb.AtaCylinderLow = (UINT8)(feature_data >> 16);
  acb.AtaCylinderHigh = (UINT8)(feature_data >> 24);

  packet.Acb = &acb;
  packet.Asb = &asb;

  // non data transfer
  sata_nondata_transfer(device, &packet, 30 * 1000000); // timeout 30 sec

  printf("sata set feature done!\r\n");
}

static void swap_pair_data(CHAR8 *buf, UINT32 len) {
  UINT32 i = 0;
  CHAR8 tmp = 0;

  for (i = 0; i < len; i = i + 2) {
    tmp = buf[i];
    buf[i] = buf[i + 1];
    buf[i + 1] = tmp;
  }
}

UINT8 sata_calculate_udma_mode(UINT16 mode) {
  UINT8 umode = (mode & 0xff);
  UINT8 i = 0;
  UINT8 um_ret = 7;

  for (i = 0; i < 8; i++) {
    if ((umode & BIT7) != 0)
      return (um_ret - i);
    umode = umode << 1;
  }

  return 0xff;
}

void sata_identify_device(SATA_ATA_IDENTIFY_DATA_t *HdIdData) {
  UINT16 udma_mode = 0;
  UINT64 capacity = 0;
  UINT16 phy_logic_sec_sup = 0;
  UINT32 logic_blks_per_phy_blk = 0;
  UINT64 low_align_lba = 0;
  UINT32 logic_block_size = 0;
  UINT32 max_sec_cnt = 0;

  // check device
  if ((HdIdData->config & BIT15) != 0) {
    printf("[ERROR]This device is not a hard disk!\r\n");
    return;
  }

  // check UDMA support
  if ((HdIdData->field_validity & BIT2) != 0) {
    udma_mode = HdIdData->ultra_dma_mode;
    if ((udma_mode & 0x7f) != 0) // BIT0~BIT6
    {
      gSataDevInfo.UdmaValid = TRUE;
      gSataDevInfo.UdmaMode = sata_calculate_udma_mode(udma_mode);
      printf("Hard disk: support UDMA, 0x%x, mode[%d] %s\r\n", udma_mode,
             gSataDevInfo.UdmaMode, udma_mode_str[gSataDevInfo.UdmaMode]);
    }
  }

  // NCQ support
  if ((HdIdData->serial_ata_capabilities & BIT8) != 0) {
    printf("Hard disk: support NCQ, depth %d\r\n", HdIdData->queue_depth + 1);
  } else {
    printf("Hard disk: Not support NCQ!!!\r\n");
  }

  // 48bit addr
  max_sec_cnt = 0x100;
  if ((HdIdData->command_set_supported_83 & (BIT15 | BIT14 | BIT10)) ==
      0x4400) // BIT15:0 BIT14:1 BIT10:1
    capacity = *((UINT64 *)HdIdData->maximum_lba_for_48bit_addressing);

  if (capacity > 0xfffffff) {
    max_sec_cnt = 0x10000;
    gSataDevInfo.Lba48Bit = TRUE;
    printf("Hard disk: support 48bit addr\r\n");
  } else {
    capacity = ((UINT32)HdIdData->user_addressable_sectors_hi << 16) |
               HdIdData->user_addressable_sectors_lo;
    gSataDevInfo.Lba48Bit = FALSE;
    printf("Hard disk: not support 48bit addr\r\n");
  }
  gSataDevInfo.LastBlock = capacity - 1;
  printf("Hard disk: last block 0x%x 0x%x\r\n",
         (UINT32)((gSataDevInfo.LastBlock >> 32) & 0xffffffff),
         (UINT32)(gSataDevInfo.LastBlock & 0xffffffff));

  // Block media information
  gSataDevInfo.IORevision = BLOCK_IO_PROTOCOL_REVISION;
  phy_logic_sec_sup = HdIdData->phy_logic_sector_support;
  if ((phy_logic_sec_sup & (BIT14 | BIT15)) == BIT14) {
    if ((phy_logic_sec_sup & BIT13) != 0) {
      logic_blks_per_phy_blk = (UINT32)(1 << (phy_logic_sec_sup & 0xf));
      printf("Hard disk: %d logic blocks per physical block\r\n",
             logic_blks_per_phy_blk);

      if ((HdIdData->alignment_logic_in_phy_blocks & (BIT14 | BIT15)) ==
          BIT14) {
        low_align_lba = (UINT64)(
            logic_blks_per_phy_blk -
            ((UINT32)HdIdData->alignment_logic_in_phy_blocks & 0x3fff) %
                logic_blks_per_phy_blk);
        printf("Hard disk: offset %d logic blocks in phy blocks\r\n",
               HdIdData->alignment_logic_in_phy_blocks);
      }

      gSataDevInfo.LowestAlignedLba = low_align_lba;
      gSataDevInfo.LogicalBlksPerPhyBlk = logic_blks_per_phy_blk;
    }

    if ((phy_logic_sec_sup & BIT12) != 0) {
      logic_block_size = (UINT32)(((HdIdData->logic_sector_size_hi << 16) |
                                   HdIdData->logic_sector_size_lo) *
                                  sizeof(UINT16)); // bytes
      gSataDevInfo.BlockSize = logic_block_size;
      printf("Hard disk: logic block size %d bytes\r\n", logic_block_size);
    } else {
      gSataDevInfo.BlockSize = 0x200;
      printf("Hard disk: logic block size is 512 bytes\r\n");
    }

    gSataDevInfo.IORevision = BLOCK_IO_PROTOCOL_REVISION2;
  }

  gSataDevInfo.IoAlign = sizeof(UINTN);

  printf("Sata set transfer mode.\r\n");
  if (gSataDevInfo.UdmaValid != TRUE) {
    sata_set_feature(&gSataDevInfo, 0x3, 0); // default pio mode 0
    printf("Sata setting transfer mode, PIO mode 0.\r\n");
  } else {
    sata_set_feature(&gSataDevInfo, 0x3,
                     (0x40 + gSataDevInfo.UdmaMode)); // set udma
    printf("Sata setting transfer mode, UDMA mode %d.\r\n",
           gSataDevInfo.UdmaMode);
  }
}

void sata_identify(UINT32 ControllerNum) {
  ATACmdBlock_t acb;
  ATAStatusBlock_t asb;
  ATATransCmdPacket_t packet;
  CHAR8 snBuf[32] = {0};
  CHAR8 fwVerBuf[16] = {0};
  CHAR8 modelBuf[64] = {0};
  SATA_ATA_IDENTIFY_DATA_t *hdInfoData;

  memset(&gSataDevInfo, 0, sizeof(SataDevice_t));
  gSataDevInfo.Controller = ControllerNum;

  // clear
  memset(&acb, 0, sizeof(ATACmdBlock_t));
  memset(&asb, 0, sizeof(ATAStatusBlock_t));
  memset(&packet, 0, sizeof(ATATransCmdPacket_t));

  acb.AtaCommand = ATA_CMD_IDENTIFY_DRIVE;
  acb.AtaSectorCount = 1;
  packet.InTransferLength = 0x200; // identify response package len 512 bytes
  packet.InDataBuffer = (UINT64 *)SATA_PRDT_SMEM_ADDR;

  packet.Acb = &acb;
  packet.Asb = &asb;

  sata_pio_transfer(&gSataDevInfo, &packet, FALSE,
                    30 * 1000000); // timeout 30 sec

  // dump identify data
  hdInfoData = (SATA_ATA_IDENTIFY_DATA_t *)packet.InDataBuffer;
  memcpy(snBuf, hdInfoData->SerialNo, 20);
  swap_pair_data(snBuf, 20);
  memcpy(fwVerBuf, hdInfoData->FirmwareVer, 8);
  swap_pair_data(fwVerBuf, 8);
  memcpy(modelBuf, hdInfoData->ModelName, 40);
  swap_pair_data(modelBuf, 40);
  printf("==========SATA %d Hard Disk Info==========\r\n", ControllerNum);
  printf("|| S/N:%s\r\n", snBuf);
  printf("|| F/W:%s\r\n", fwVerBuf);
  printf("|| Model:%s\r\n", modelBuf);
  printf("==========SATA %d Hard Disk Info==========\r\n", ControllerNum);

  sata_identify_device(hdInfoData);
}

// trans_len is the trans numbers of sectors. Finally convert to bytes in the
// function.
void sata_transfer(SataDevice_t *device, UINT8 *buf, UINT64 start_lba,
                   UINT32 trans_len, BOOLEAN is_write) {
  ATACmdBlock_t acb;
  ATAStatusBlock_t asb;
  ATATransCmdPacket_t packet;

  // clear
  memset(&acb, 0, sizeof(ATACmdBlock_t));
  memset(&asb, 0, sizeof(ATAStatusBlock_t));
  memset(&packet, 0, sizeof(ATATransCmdPacket_t));

  // ATA command
  if (device->FpdmaEnable)
    acb.AtaCommand = mAtaFpdmaCmds[is_write];
  else
    acb.AtaCommand =
        mAtaCommands[device->UdmaValid][device->Lba48Bit][is_write];

  // just for TaskFileError interrupt testing
  if ((gSataIntrMaskEn & SATA_INTR_TFEE) != 0) {
    acb.AtaCommand = 0x55; // invalid ata command for interrupt testing
    printf("sata task file error intr, setting invalid ata command 0x55\n");
  }

  acb.AtaSectorNumber = (UINT8)start_lba;
  acb.AtaCylinderLow = (UINT8)(start_lba >> 8);
  acb.AtaCylinderHigh = (UINT8)(start_lba >> 16);
  acb.AtaDeviceHead = (UINT8)(BIT7 | BIT6 | BIT5);

  if (device->Lba48Bit) {
    acb.AtaSectorNumberExp = (UINT8)(start_lba >> 24);
    acb.AtaCylinderLowExp = (UINT8)(start_lba >> 32);
    acb.AtaCylinderHighExp = (UINT8)(start_lba >> 40);
    acb.AtaSectorCountExp = (UINT8)(trans_len >> 8);
  } else {
    acb.AtaDeviceHead = (UINT8)(acb.AtaDeviceHead | (start_lba >> 24));
  }

  if (device->FpdmaEnable) {
    acb.AtaFeatures = (UINT8)trans_len;
    acb.AtaFeaturesExp = (UINT8)(trans_len >> 8);
    acb.AtaSectorCount = 0 << 3;    // set tag, use tag 0
    acb.AtaSectorCountExp = 0 << 6; // prio
  } else {
    acb.AtaSectorCount = (UINT8)trans_len;

    // just for Overflow interrupt testing
    if ((gSataIntrMaskEn & SATA_INTR_OFE) != 0) {
      acb.AtaSectorCount =
          (UINT8)trans_len +
          1; // illegal. Add 1 sector to generate overflow error
      printf("sata overflow intr, setting illegal sector cnt +1\n");
    }
  }

  // ATA packet
  if (is_write) {
    packet.OutDataBuffer = buf;
    packet.OutTransferLength = trans_len;
  } else {
    packet.InDataBuffer = buf;
    packet.InTransferLength = trans_len;
  }

  if (device->FpdmaEnable)
    packet.Protocol = mAtaFpdmaXferProtocols[is_write];
  else
    packet.Protocol = mAtaPassThruCmdProtocols[device->UdmaValid][is_write];
  packet.Length = ATA_PASS_THRU_LENGTH_SECTOR_COUNT; // 0x20
  packet.Acb = &acb;
  packet.Asb = &asb;

  // sector size to bytes size
  if (((packet.Length & ATA_PASS_THRU_LENGTH_BYTES) == 0) &&
      (packet.InTransferLength != 0)) {
    packet.InTransferLength = packet.InTransferLength * device->BlockSize;
  }

  if (((packet.Length & ATA_PASS_THRU_LENGTH_BYTES) == 0) &&
      (packet.OutTransferLength != 0)) {
    packet.OutTransferLength = packet.OutTransferLength * device->BlockSize;
  }

  switch (packet.Protocol) {
  case ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA:
    sata_nondata_transfer(device, &packet, 30 * 1000000); // timeout 30 sec
    break;
  case ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN:
    sata_pio_transfer(device, &packet, FALSE,
                      30 * 1000000); // timeout 30 sec. If trans len is large,
                                     // need to increase the timeout val
    break;
  case ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT:
    sata_pio_transfer(device, &packet, TRUE,
                      30 * 1000000); // timeout 30 sec. If trans len is large,
                                     // need to increase the timeout val
    break;
  case ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN:
    sata_dma_transfer(device, &packet, FALSE,
                      30 * 1000000); // timeout 30 sec. If trans len is large,
                                     // need to increase the timeout val
    break;
  case ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT:
    sata_dma_transfer(device, &packet, TRUE,
                      30 * 1000000); // timeout 30 sec. If trans len is large,
                                     // need to increase the timeout val
    break;
  case ATA_XFER_PROTOCOL_FPDMA_DATA_IN:
    sata_fpdma_transfer(device, &packet, FALSE,
                        30 * 1000000); // timeout 30 sec. If trans len is large,
                                       // need to increase the timeout val
    break;
  case ATA_XFER_PROTOCOL_FPDMA_DATA_OUT:
    sata_fpdma_transfer(device, &packet, TRUE,
                        30 * 1000000); // timeout 30 sec. If trans len is large,
                                       // need to increase the timeout val
    break;
  default:
    printf("[ERROR]Input illegal transfer protocol %d\r\n", packet.Protocol);
    return;
  }
}

void sata_blk_read_write(SataDevice_t *device, UINT64 lba, UINT8 *buf,
                         UINT64 buf_len, BOOLEAN is_write) {
  UINT32 blk_size = 0;
  UINT64 num_blks = 0;
  UINT32 io_align = 0;
  UINTN max_trans_blk_num = 0;
  UINTN trans_blk_num = 0;
  UINT64 start_lba = lba;
  UINT8 *p_buf = buf;

  blk_size = device->BlockSize;
  if ((buf_len % blk_size) != 0) {
    printf("[ERROR] Input buf size bad. buf size %d, blk size %d\r\n", buf_len,
           blk_size);
    return;
  }

  num_blks = buf_len / blk_size;
  if ((lba + num_blks - 1) > device->LastBlock) {
    printf("[ERROR] Input buf size overflow.\r\n");
    return;
  }

  io_align = device->IoAlign;
  if ((io_align > 0) && (((UINTN)buf & (UINTN)(io_align - 1)) != 0)) {
    printf("[ERROR] Input buf addr ilegal - not align %d\r\n", io_align);
    return;
  }

  max_trans_blk_num = mMaxTransferBlockNumber[device->Lba48Bit];

  do {
    if (num_blks > max_trans_blk_num) {
      trans_blk_num = max_trans_blk_num;
      num_blks -= max_trans_blk_num;
    } else {
      trans_blk_num = num_blks;
      num_blks = 0;
    }

    // transfer
    sata_transfer(device, p_buf, start_lba, (UINT32)trans_blk_num, is_write);

    start_lba += trans_blk_num;
    p_buf += trans_blk_num * blk_size;
  } while (num_blks > 0);
}

void sata_bread(UINT64 start_lba, UINT64 count) {
  UINT8 *buf = (UINT8 *)SATA_RW_BUF_SMEM_ADDR;
  UINT64 buf_len = count * gSataDevInfo.BlockSize;
  UINT64 i = 0;

  printf("Sata bread start block 0x%x 0x%x, count 0x%x 0x%x\r\n",
         (UINT32)((start_lba >> 32) & 0xffffffff),
         (UINT32)(start_lba & 0xffffffff), (UINT32)((count >> 32) & 0xffffffff),
         (UINT32)(count & 0xffffffff));

  if (start_lba > gSataDevInfo.LastBlock) {
    printf("[ERROR] The input sata start block number more than the total "
           "block number 0x%x 0x%x!\r\n",
           (UINT32)((gSataDevInfo.LastBlock >> 32) & 0xffffffff),
           (UINT32)(gSataDevInfo.LastBlock & 0xffffffff));
    return;
  }

  if ((start_lba + count - 1) > gSataDevInfo.LastBlock) {
    printf("[ERROR] The input sata block count add start_lba more than the "
           "total block number 0x%x 0x%x!\r\n",
           (UINT32)((gSataDevInfo.LastBlock >> 32) & 0xffffffff),
           (UINT32)(gSataDevInfo.LastBlock & 0xffffffff));
    return;
  }

  memset(buf, 0, SATA_RW_BUF_SMEM_SIZE);
  sata_blk_read_write(&gSataDevInfo, start_lba, buf, buf_len, FALSE);

  printf("\r\n==========Dump block read data==========\r\n");
  for (i = 0; i < buf_len; i++)
    printf("0x%x ", buf[i]);
  printf("\r\n==========Dump block read data==========\r\n");
}

void sata_bwrite(UINT64 start_lba, UINT64 count, UINT8 val) {
  UINT8 *buf = (UINT8 *)SATA_RW_BUF_SMEM_ADDR;
  UINT64 buf_len = count * gSataDevInfo.BlockSize;
  UINT64 i = 0;

  printf("Sata bwrite start block 0x%x 0x%x, count 0x%x 0x%x, val 0x%x\r\n",
         (UINT32)((start_lba >> 32) & 0xffffffff),
         (UINT32)(start_lba & 0xffffffff), (UINT32)((count >> 32) & 0xffffffff),
         (UINT32)(count & 0xffffffff), val);

  if (start_lba > gSataDevInfo.LastBlock) {
    printf("[ERROR] The input sata start block number more than the total "
           "block number 0x%x 0x%x!\r\n",
           (UINT32)((gSataDevInfo.LastBlock >> 32) & 0xffffffff),
           (UINT32)(gSataDevInfo.LastBlock & 0xffffffff));
    return;
  }

  if ((start_lba + count - 1) > gSataDevInfo.LastBlock) {
    printf("[ERROR] The input sata block count add start_lba more than the "
           "total block number 0x%x 0x%x!\r\n",
           (UINT32)((gSataDevInfo.LastBlock >> 32) & 0xffffffff),
           (UINT32)(gSataDevInfo.LastBlock & 0xffffffff));
    return;
  }

  // write
  memset(buf, val, buf_len);
  sata_blk_read_write(&gSataDevInfo, start_lba, buf, buf_len, TRUE);
  // read/check/dump
  memset(buf, 0, SATA_RW_BUF_SMEM_SIZE);
  sata_blk_read_write(&gSataDevInfo, start_lba, buf, buf_len, FALSE);
  for (i = 0; i < buf_len; i++) {
    if (buf[i] != val) {
      printf("[ERROR] Check sata block write fail [off 0x%lx]0x%x, expect "
             "0x%x\r\n",
             i, buf[i], val);
      break;
    }
  }

  if (i == buf_len)
    printf("[PASS] Check sata block write ok, all data is expected 0x%x\r\n",
           val);

  // printf("\r\n==========Dump block data written==========\r\n");
  // for (i = 0; i < buf_len; i++)
  //    printf("0x%x ", buf[i]);
  // printf("\r\n==========Dump block data written==========\r\n");
}

void sata_dma_rw_multicmd(SataDevice_t *device, UINT8 *buf, UINT64 start_lba,
                          UINT32 cmd_cnt, BOOLEAN is_write) {
  ATACmdBlock_t acb;
  ATAStatusBlock_t asb;
  ATATransCmdPacket_t packet;
  UINT32 val = 0;
  UINT32 i = 0;
  UINT32 cmd_slot = 0;
  UINT32 trans_blk = 1; // bwrite one sector to test
  UINT64 curr_start_lba = start_lba;
  UINTN Base = Sata_Reg_Base[device->Controller];
  UINT64 cmd_tab_addr = SATA_CMD_TAB_SMEM_ADDR;
  UINT64 cmd_list_addr = SATA_CMD_LIST_SMEM_ADDR;
  UINT64 fis_recv_addr = SATA_FIS_RECV_SMEM_ADDR;

  // clear
  memset(&acb, 0, sizeof(ATACmdBlock_t));
  memset(&asb, 0, sizeof(ATAStatusBlock_t));
  memset(&packet, 0, sizeof(ATATransCmdPacket_t));
  // clear memory 128K bytes
  memset((UINT8 *)SATA_OP_BUF_SMEM_ADDR, 0, SATA_OP_BUF_SMEM_SIZE);

  // build multi command
  for (i = 0; i < cmd_cnt; i++) {
    // ATA command
    acb.AtaCommand =
        mAtaCommands[device->UdmaValid][device->Lba48Bit][is_write];
    acb.AtaSectorNumber = (UINT8)curr_start_lba;
    acb.AtaCylinderLow = (UINT8)(curr_start_lba >> 8);
    acb.AtaCylinderHigh = (UINT8)(curr_start_lba >> 16);
    acb.AtaDeviceHead = (UINT8)(BIT7 | BIT6 | BIT5);
    acb.AtaSectorCount = (UINT8)trans_blk;
    if (device->Lba48Bit) {
      acb.AtaSectorNumberExp = (UINT8)(curr_start_lba >> 24);
      acb.AtaCylinderLowExp = (UINT8)(curr_start_lba >> 32);
      acb.AtaCylinderHighExp = (UINT8)(curr_start_lba >> 40);
      acb.AtaSectorCountExp = (UINT8)(trans_blk >> 8);
    } else {
      acb.AtaDeviceHead = (UINT8)(acb.AtaDeviceHead | (curr_start_lba >> 24));
    }

    // ATA packet
    if (is_write) {
      packet.OutDataBuffer = buf;
      packet.OutTransferLength = trans_blk;
    } else {
      packet.InDataBuffer = buf;
      packet.InTransferLength = trans_blk;
    }
    packet.Protocol = mAtaPassThruCmdProtocols[device->UdmaValid][is_write];
    packet.Length = ATA_PASS_THRU_LENGTH_SECTOR_COUNT; // 0x20
    packet.Acb = &acb;
    packet.Asb = &asb;

    // sector size to bytes size
    if (((packet.Length & ATA_PASS_THRU_LENGTH_BYTES) == 0) &&
        (packet.InTransferLength != 0)) {
      packet.InTransferLength = packet.InTransferLength * device->BlockSize;
    }

    if (((packet.Length & ATA_PASS_THRU_LENGTH_BYTES) == 0) &&
        (packet.OutTransferLength != 0)) {
      packet.OutTransferLength = packet.OutTransferLength * device->BlockSize;
    }

    sata_build_command(device, &packet, is_write,
                       (SATA_AHCI_COMMAND_TABLE_t *)cmd_tab_addr,
                       (SATA_AHCI_COMMAND_LIST_t *)cmd_list_addr);

    cmd_tab_addr += sizeof(SATA_AHCI_COMMAND_TABLE_t);
    cmd_list_addr += sizeof(SATA_AHCI_COMMAND_LIST_t);
    cmd_slot |= 1 << i;
    curr_start_lba += trans_blk;
  }

  printf("Multicmd take up cmd slots 0x%x\r\n", cmd_slot);
  sata_start_command(device, cmd_slot);

  // checking
  if (sata_wait_mem_set((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET,
                        AHCI_FIS_TYPE_MASK, AHCI_FIS_REGISTER_D2H,
                        30 * 1000000)) {
    val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
    if ((val & BIT0) != 0) {
      printf("[ERROR]Error for multicmd dma transfer!\r\n");
    } else {
      printf("Multicmd dma transfer ok!\r\n");
    }
  } else {
    printf("[ERROR]Multicmd dma transfer, get wrong d2h fis 0x%x\r\n",
           *(volatile UINT32 *)((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET));
  }

  // stop command and disable fis receive
  sata_stop_command(device);
  sata_disable_rfis(device);

  // Dump port status. update ASB (ata status block)
  sata_dump_port_st(device, &packet, (SATA_AHCI_RECEIVED_FIS_t *)fis_recv_addr);
}

void sata_fpdma_rw_multicmd(SataDevice_t *device, UINT8 *buf,
                            UINT64 *start_lba_tab, UINT32 cmd_cnt,
                            BOOLEAN is_write) {
  ATACmdBlock_t acb;
  ATAStatusBlock_t asb;
  ATATransCmdPacket_t packet;
  UINT32 i = 0;
  UINT32 cmd_slot = 0;
  UINT32 trans_blk = 1; // bwrite one sector to test
  UINT64 curr_start_lba = 0;
  UINTN Base = Sata_Reg_Base[device->Controller];
  UINT64 cmd_tab_addr = SATA_CMD_TAB_SMEM_ADDR;
  UINT64 cmd_list_addr = SATA_CMD_LIST_SMEM_ADDR;
  UINT64 fis_recv_addr = SATA_FIS_RECV_SMEM_ADDR;

  // just for SetDeviceBits interrupt testing
  if ((gSataIntrMaskEn & SATA_INTR_SDBE) != 0) {
    sata_interrupt_init(device->Controller, gSataIntrMaskEn);
  }

  // clear
  memset(&acb, 0, sizeof(ATACmdBlock_t));
  memset(&asb, 0, sizeof(ATAStatusBlock_t));
  memset(&packet, 0, sizeof(ATATransCmdPacket_t));
  // clear memory 128K bytes
  memset((UINT8 *)SATA_OP_BUF_SMEM_ADDR, 0, SATA_OP_BUF_SMEM_SIZE);

  // build multi command
  for (i = 0; i < cmd_cnt; i++) {
    curr_start_lba = start_lba_tab[i];

    // ATA command
    acb.AtaCommand = mAtaFpdmaCmds[is_write];
    acb.AtaSectorNumber = (UINT8)curr_start_lba;
    acb.AtaCylinderLow = (UINT8)(curr_start_lba >> 8);
    acb.AtaCylinderHigh = (UINT8)(curr_start_lba >> 16);
    acb.AtaDeviceHead = (UINT8)(BIT7 | BIT6 | BIT5);
    if (device->Lba48Bit) {
      acb.AtaSectorNumberExp = (UINT8)(curr_start_lba >> 24);
      acb.AtaCylinderLowExp = (UINT8)(curr_start_lba >> 32);
      acb.AtaCylinderHighExp = (UINT8)(curr_start_lba >> 40);
    } else {
      acb.AtaDeviceHead = (UINT8)(acb.AtaDeviceHead | (curr_start_lba >> 24));
    }

    acb.AtaFeatures = (UINT8)trans_blk;
    acb.AtaFeaturesExp = (UINT8)(trans_blk >> 8);
    acb.AtaSectorCount = i << 3;    // set tag
    acb.AtaSectorCountExp = 0 << 6; // prio

    // ATA packet
    if (is_write) {
      packet.OutDataBuffer = buf;
      packet.OutTransferLength = trans_blk;
    } else {
      packet.InDataBuffer = buf;
      packet.InTransferLength = trans_blk;
    }
    packet.Protocol = mAtaFpdmaXferProtocols[is_write];
    packet.Length = ATA_PASS_THRU_LENGTH_SECTOR_COUNT; // 0x20
    packet.Acb = &acb;
    packet.Asb = &asb;

    // sector size to bytes size
    if (((packet.Length & ATA_PASS_THRU_LENGTH_BYTES) == 0) &&
        (packet.InTransferLength != 0)) {
      packet.InTransferLength = packet.InTransferLength * device->BlockSize;
    }

    if (((packet.Length & ATA_PASS_THRU_LENGTH_BYTES) == 0) &&
        (packet.OutTransferLength != 0)) {
      packet.OutTransferLength = packet.OutTransferLength * device->BlockSize;
    }

    sata_build_command(device, &packet, is_write,
                       (SATA_AHCI_COMMAND_TABLE_t *)cmd_tab_addr,
                       (SATA_AHCI_COMMAND_LIST_t *)cmd_list_addr);

    cmd_tab_addr += sizeof(SATA_AHCI_COMMAND_TABLE_t);
    cmd_list_addr += sizeof(SATA_AHCI_COMMAND_LIST_t);
    cmd_slot |= 1 << i;
  }

  printf("Multicmd fpdma take up cmd slots 0x%x\r\n", cmd_slot);
  sata_start_command(device, cmd_slot);

  if (sata_wait_mem_set((UINT64)(Base + HWIO_SATA_P0SACT_OFFS), 0xffffffff, 0,
                        30 * 1000000)) {
    printf("Multicmd fpdma transfer ok!\r\n");
  } else {
    printf("[ERROR]Multicmd fpdma transfer, sact 0x%x\r\n",
           in_dword(Base + HWIO_SATA_P0SACT_OFFS));
  }

  // stop command and disable fis receive
  sata_stop_command(device);
  sata_disable_rfis(device);

  // Dump port status. update ASB (ata status block)
  sata_dump_port_st(device, &packet, (SATA_AHCI_RECEIVED_FIS_t *)fis_recv_addr);

  // just for SetDeviceBits interrupt testing
  if ((gSataIntrMaskEn & SATA_INTR_SDBE) != 0) {
    sata_interrupt_check(device->Controller, gSataIntrMaskEn);
    sata_interrupt_deinit(device->Controller);
  }
}

static UINT64 sata_fpdma_lba_tab[32] = {
    5,  3,  8,  6,  4, 10, 9,  16, 13, 15, 20, 14, 23, 30, 31, 19,
    32, 25, 28, 33, 7, 27, 11, 17, 21, 35, 26, 22, 12, 24, 18, 29};

void sata_multi_cmd_fpdma(UINT32 cmd_cnt, UINT8 val) {
  UINT32 i = 0;
  UINT32 j = 0;
  UINT8 *buf = (UINT8 *)SATA_RW_BUF_SMEM_ADDR;
  UINT64 buf_len = cmd_cnt * gSataDevInfo.BlockSize;

  printf("Multicmd fpdma count %d, val 0x%x\r\n", cmd_cnt, val);

  if (cmd_cnt > 32) {
    printf("[ERROR]Input fpdma multi command count %d, expect <= 32\r\n",
           cmd_cnt);
    return;
  }

  // set up multi command with bwrite processing
  memset(buf, val, buf_len);
  sata_fpdma_rw_multicmd(&gSataDevInfo, buf, sata_fpdma_lba_tab, cmd_cnt, TRUE);

  // check the bwrite with bread
  for (i = 0; i < cmd_cnt; i++) {
    memset(buf, 0, SATA_RW_BUF_SMEM_SIZE);
    sata_blk_read_write(&gSataDevInfo, sata_fpdma_lba_tab[i], buf,
                        gSataDevInfo.BlockSize, FALSE);
    for (j = 0; j < gSataDevInfo.BlockSize; j++) {
      if (buf[j] != val) {
        printf("[ERROR]Multicmd fpdma check data fail index[%d, %d], expect "
               "val 0x%x\r\n",
               i, j, val);
        break;
      }
    }
  }
  printf("[PASS]Multicmd fpdma check data ok, all data expect 0x%x\r\n", val);
}

void sata_multi_cmd_dma(UINT32 cmd_cnt, UINT8 val) {
  UINT32 i = 0;
  UINT8 *buf = (UINT8 *)SATA_RW_BUF_SMEM_ADDR;
  UINT64 buf_len = cmd_cnt * gSataDevInfo.BlockSize;
  UINT64 start_lba = 3; // start bwrite block

  printf("Multicmd dma count %d, start lba %d, len 0x%x, val 0x%x\r\n", cmd_cnt,
         start_lba, buf_len, val);

  if (cmd_cnt > 32) {
    printf("[ERROR]Input dma multi command count %d, expect <= 32\r\n",
           cmd_cnt);
    return;
  }

  // set up multi command with bwrite processing
  memset(buf, val, buf_len);
  sata_dma_rw_multicmd(&gSataDevInfo, buf, start_lba, cmd_cnt, TRUE);

  // check the bwrite with bread
  memset(buf, 0, SATA_RW_BUF_SMEM_SIZE);
  sata_blk_read_write(&gSataDevInfo, start_lba, buf, buf_len, FALSE);
  for (i = 0; i < buf_len; i++) {
    if (buf[i] != val) {
      printf("[ERROR] Multicmd dma: check sata bwrite fail [off 0x%lx]0x%x, "
             "expect 0x%x\r\n",
             i, buf[i], val);
      break;
    }
  }

  if (i == buf_len)
    printf("[PASS] Multicmd dma: check sata block write ok, all data is "
           "expected 0x%x\r\n",
           val);
}

// support max multi command count 32
void sata_multi_cmd(UINT32 cmd_cnt, UINT8 val) {
  if (gSataDevInfo.FpdmaEnable)
    sata_multi_cmd_fpdma(cmd_cnt, val);
  else
    sata_multi_cmd_dma(cmd_cnt, val);
}

void sata_xfer_mode(UINT32 mode) {
  // default 0 - DMA mode
  // 1:PIO 2:FPDMA
  gSataDevInfo.FpdmaEnable = FALSE;

  if (mode == 1) // PIO
  {
    printf("SATA conf xfer mode: PIO\r\n");
    if (gSataDevInfo.UdmaValid != TRUE) {
      printf("SATA current xfer mode is PIO, return\r\n");
    } else {
      sata_set_feature(&gSataDevInfo, 0x3, 0); // default pio mode 0
      gSataDevInfo.UdmaValid = FALSE;
      printf("Sata setting xfer mode to PIO mode 0\r\n");
    }
  } else if (mode == 2) // FPDMA
  {
    printf("SATA conf xfer mode: FPDMA\r\n");
    if (gSataDevInfo.UdmaValid != TRUE) {
      sata_set_feature(&gSataDevInfo, 0x3,
                       (0x40 + gSataDevInfo.UdmaMode)); // set udma
      gSataDevInfo.UdmaValid = TRUE;
      printf("Firstly sata setting xfer mode to UDMA mode %d.\r\n",
             gSataDevInfo.UdmaMode);
    }
    gSataDevInfo.FpdmaEnable = TRUE;
    printf("SATA enable FPDMA xfer mode\r\n");
  } else // DMA. default
  {
    printf("SATA conf xfer mode: DMA\r\n");
    if (gSataDevInfo.UdmaValid) {
      printf("SATA current xfer mode is DMA, return\r\n");
    } else {
      sata_set_feature(&gSataDevInfo, 0x3,
                       (0x40 + gSataDevInfo.UdmaMode)); // set udma
      gSataDevInfo.UdmaValid = TRUE;
      printf("Sata setting xfer mode to UDMA mode %d.\r\n",
             gSataDevInfo.UdmaMode);
    }
  }
}

void sata_build_srst_cmd(SataDevice_t *device, BOOLEAN isSetSrst,
                         SATA_AHCI_COMMAND_TABLE_t *cmd_tab_addr,
                         SATA_AHCI_COMMAND_LIST_t *cmd_list_addr) {
  UINT32 val = 0;
  UINTN Base = Sata_Reg_Base[device->Controller];

  // build command table
  cmd_tab_addr->CommandFis.AhciCFisType = 0x27; // host2device
  cmd_tab_addr->CommandFis.AhciCFisPmNum = 0xf; // port number
  cmd_tab_addr->CommandFis.AhciCFisCmdInd = 0;
  cmd_tab_addr->CommandFis.AhciCFisCmd = 0;
  cmd_tab_addr->CommandFis.AhciCFisDevHead = 0xA0;
  if (isSetSrst) // BIT2 is SRST bit
    cmd_tab_addr->CommandFis.AhciCFisControl = (BIT3) | (BIT2);
  else
    cmd_tab_addr->CommandFis.AhciCFisControl = (BIT3);

  cmd_tab_addr->PrdtTable[0].AhciPrdtDbc = 0;
  cmd_tab_addr->PrdtTable[0].AhciPrdtDba = 0;
  cmd_tab_addr->PrdtTable[0].AhciPrdtDbau = 0;

  // build command list. Just 1
  cmd_list_addr->AhciCmdCfl = 5; // 5 UINT32 (20/4)
  cmd_list_addr->AhciCmdW = 0;   // read 0, write 1;
  cmd_list_addr->AhciCmdPmp = 0; // no multiport
  cmd_list_addr->AhciCmdPrdtl = 0;
  cmd_list_addr->AhciCmdCtba = (UINT32)((UINT64)cmd_tab_addr & 0xffffffff);
  cmd_list_addr->AhciCmdCtbau =
      (UINT32)(((UINT64)cmd_tab_addr >> 32) & 0xffffffff);

  // CMD clear PORT_CMD_DLAE | PORT_CMD_ATAPI
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  out_dword(Base + HWIO_SATA_P0CMD_OFFS,
            val & (UINT32)(~(HWIO_SATA_P0CMD_ATAPI | HWIO_SATA_P0CMD_DLAE)));
}

void sata_set_srst(SataDevice_t *device, BOOLEAN isSetSrst, UINT64 timeout_us) {
  UINTN Base = Sata_Reg_Base[device->Controller];
  SATA_AHCI_COMMAND_TABLE_t *cmd_tab_addr;
  SATA_AHCI_COMMAND_LIST_t *cmd_list_addr;
  SATA_AHCI_RECEIVED_FIS_t *fis_recv_addr;
  UINT32 val = 0;

  // clear memory 128K bytes
  memset((UINT8 *)SATA_OP_BUF_SMEM_ADDR, 0, SATA_OP_BUF_SMEM_SIZE);
  cmd_tab_addr = (SATA_AHCI_COMMAND_TABLE_t *)SATA_CMD_TAB_SMEM_ADDR;
  cmd_list_addr = (SATA_AHCI_COMMAND_LIST_t *)SATA_CMD_LIST_SMEM_ADDR;
  fis_recv_addr = (SATA_AHCI_RECEIVED_FIS_t *)SATA_FIS_RECV_SMEM_ADDR;

  // the receive fis and cmd list addr had been registered in init stage
  sata_build_srst_cmd(device, isSetSrst, cmd_tab_addr, cmd_list_addr);
  sata_start_command(device, 0x1);

  if (isSetSrst) {
    udelay(10000);
  } else {
    if (sata_wait_mem_set((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET,
                          AHCI_FIS_TYPE_MASK, AHCI_FIS_REGISTER_D2H,
                          timeout_us)) {
      val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);
      if ((val & BIT0) != 0)
        printf("[ERROR]Error in SRST transfer!\r\n");
      else
        printf("SRST transfer ok!\r\n");
    } else
      printf("[ERROR]SRST transfer, get wrong d2h fis 0x%x\r\n",
             *(volatile UINT32 *)((UINT64)fis_recv_addr + AHCI_D2H_FIS_OFFSET));
  }

  // stop command and disable fis receive
  sata_stop_command(device);
  sata_disable_rfis(device);
}

void sata_do_srst(SataDevice_t *device) {
  UINTN Base = Sata_Reg_Base[device->Controller];
  UINT32 delay = 0;
  UINT32 val = 0;

  sata_set_srst(device, TRUE, 30 * 1000000);

  // delay at least 1ms
  udelay(10000);
  printf("SRST TFD 0x%x\r\n", in_dword(Base + HWIO_SATA_P0TFD_OFFS));

  sata_set_srst(device, FALSE, 30 * 1000000);

  // check software reset ready
  delay = 500;
  do {
    val = in_dword(Base + HWIO_SATA_P0TFD_OFFS);

    if ((val & BIT7) == 0) {
      break;
    }

    udelay(10000);
    delay--;
  } while (delay > 0);

  if (delay == 0) {
    printf("[ERROR]SRST check TFD fail! [0x%x] 0x%x\r\n",
           (Base + HWIO_SATA_P0TFD_OFFS), val);
    return;
  }
  printf("SRST check SERR [0x%x]\r\n", in_dword(Base + HWIO_SATA_P0SERR_OFFS));
  printf("SRST check SSTS [0x%x]\r\n", in_dword(Base + HWIO_SATA_P0SSTS_OFFS));
  printf("SRST check ready! TFD [0x%x] 0x%x\r\n", (Base + HWIO_SATA_P0TFD_OFFS),
         val);
}

void sata_do_prst(SataDevice_t *device) {
  UINTN Base = Sata_Reg_Base[device->Controller];
  UINT32 val = 0;

  // check P0CMD. The cmd list stop running
  val = in_dword(Base + HWIO_SATA_P0CMD_OFFS);
  printf("PRST P0CMD 0x%x\r\n", val);
  if ((val & (BIT0 | BIT15)) != 0) {
    out_dword(Base + HWIO_SATA_P0CMD_OFFS, val & (~(BIT0)));
    printf("PRST waiting for P0CMD cmd list stop running...\r\n");
    while ((in_dword(Base + HWIO_SATA_P0CMD_OFFS) & BIT15) != 0) {
      udelay(10000);
    }
    printf("PRST P0CMD cmd list stop running\r\n");
  }

  val = in_dword(Base + HWIO_SATA_P0SCTL_OFFS);
  printf("PRST P0SCTL 0x%x\r\n", val);
  out_dword(Base + HWIO_SATA_P0SCTL_OFFS, (val & 0x0f0) | 0x301);
  printf("PRST P0SCTL after set det 0x%x\r\n",
         in_dword(Base + HWIO_SATA_P0SCTL_OFFS));

  // delay at lease 1ms
  udelay(100000);

  // check SSTS.DET, TFD.STS
  printf("PRST P0SSTS 0x%x\r\n", in_dword(Base + HWIO_SATA_P0SSTS_OFFS));
  printf("PRST P0TFD 0x%x\r\n", in_dword(Base + HWIO_SATA_P0TFD_OFFS));
  printf("PRST P0SERR 0x%x\r\n", in_dword(Base + HWIO_SATA_P0SERR_OFFS));
  printf("PRST check TFD.STS 0x7F\r\n");
  while ((in_dword(Base + HWIO_SATA_P0TFD_OFFS) & 0xff) != 0x7F) {
    udelay(1000);
  }
  printf("PRST check SSTS.DET 0x0\r\n");
  while ((in_dword(Base + HWIO_SATA_P0SSTS_OFFS) & 0xf) != 0x0) {
    udelay(1000);
  }

  val = in_dword(Base + HWIO_SATA_P0SCTL_OFFS);
  printf("PRST P0SCTL 0x%x\r\n", val);
  out_dword(Base + HWIO_SATA_P0SCTL_OFFS, (val & 0x0f0) | 0x300);
  printf("PRST P0SCTL after clear det 0x%x, and check\r\n",
         in_dword(Base + HWIO_SATA_P0SCTL_OFFS));
  while ((in_dword(Base + HWIO_SATA_P0SCTL_OFFS) & 0xf0f) != 0x300) {
    udelay(1000);
  }

  // check TFD.STS.BSY, SSTS.DET
  printf("PRST check SSTS.DET 0x3\r\n");
  while ((in_dword(Base + HWIO_SATA_P0SSTS_OFFS) & 0xf) != 0x3) {
    udelay(1000);
  }
  printf("PRST check TFD.STS.BSY 0x1\r\n");
  while ((in_dword(Base + HWIO_SATA_P0TFD_OFFS) & BIT7) == 0) {
    udelay(1000);
  }
  printf("PRST P0SSTS 0x%x\r\n", in_dword(Base + HWIO_SATA_P0SSTS_OFFS));
  printf("PRST P0TFD 0x%x\r\n", in_dword(Base + HWIO_SATA_P0TFD_OFFS));
  printf("PRST P0SERR 0x%x\r\n", in_dword(Base + HWIO_SATA_P0SERR_OFFS));

  out_dword(Base + HWIO_SATA_P0SERR_OFFS,
            in_dword(Base + HWIO_SATA_P0SERR_OFFS));
  printf("PRST PASS\r\n");
}

void sata_reset(UINT32 reset) {
  switch (reset) {
  case 0:
    printf("Sata %d software reset...\r\n", gSataDevInfo.Controller);
    sata_do_srst(&gSataDevInfo);
    break;

  case 1:
    printf("Sata %d port reset...\r\n", gSataDevInfo.Controller);
    sata_do_prst(&gSataDevInfo);
    break;

  default:
    printf("[ERROR] Input wrong reset request %d\r\n", reset);
    break;
  }
}
