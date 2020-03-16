/*==============================================================================
Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
All Rights Reserved.
Confidential and Proprietary - Qualcomm Technologies, Inc.
================================================================================

  FILE:         spm_hal.c

  OVERVIEW:     This file implements HAL APIs exposed to SPM driver and performs
                actual HW register read and write.

  DEPENDENCIES: The implementation can be SAW/SPM version specific.

==============================================================================*/

#include <asm/mach/spm/spm_hal.h>
#include <asm/mach/spm/spm_hwio.h>

/*===========================================================================
 *                            INTERNAL VARIABLES
 *==========================================================================*/

/**
 * @brief Volatile variable which will be used to read back SPM register
 *        being written to. This is to ensure that write value actually got
 *        propagated to HW.
 */
volatile uint32_t spm_hal_read_back_val;

/*==========================================================================
 *                             INTERNAL MACROS
 *=========================================================================*/

/**
 * @brief Size of each command sequence register in byte.
 */
#define SPM_HAL_CMD_SEQ_REG_SIZE  4

/**
 * @brief Size of each command in bytes.
 */
#define SPM_HAL_CMD_SIZE  1

/**
 * @brief Number of commands per register
 */
#define SPM_HAL_CMDS_PER_REG  (SPM_HAL_CMD_SEQ_REG_SIZE/SPM_HAL_CMD_SIZE)

/**
 * @brief Macros to create bit mask, set and clear bit in a mask
 */
#define MAKE_MASK32(bit_pos)  ((uint32_t)1 << (bit_pos % 32))
#define BIT_SET32(val, bit_pos)  (val | (MAKE_MASK32(bit_pos)))
#define BIT_CLR32(val, bit_pos)  (val & ~(MAKE_MASK32(bit_pos)))

/**
 * @brief Macro to readback an SPM register.
 */
#define SPM_HAL_READBACK_REG(base, reg) \
  (spm_hal_read_back_val = SPM_HWIO_INX(base, reg))

/*===========================================================================
 *                            EXTERNAL FUNCTIONS
 *==========================================================================*/

/*
 * spm_hal_enable
 */
void spm_hal_enable(uint8_t *spm_base, uint8_t enable)
{
  if (enable)
  {
    SPM_HWIO_OUTXF(spm_base, SPM_CTL, SPM_EN, enable);
  }
  else
  {
    /* Setting entire register to 0 as other fields are affecting behavior
     * of HW block even if SPM is not kicked in (e.g. Istari HMSS where PC,
     * RET fields can affect cache cleaning) */
    SPM_HWIO_OUTX(spm_base, SPM_CTL, 0x0);
  }
}

/*
 * spm_hal_reset
 */
void spm_hal_reset(uint8_t *spm_base)
{
  spm_base += SAW4_STS_REG_BASE_OFFS;
  SPM_HWIO_OUTX(spm_base, RST, 0x1);
}

/*
 * spm_hal_wakeup
 */
void spm_hal_wakeup(uint8_t *spm_base)
{
  SPM_HWIO_OUTXF(spm_base, SPM_CTL, WAKEUP_REQ, 0x1);
}

/*
 * spm_hal_config_clk_div
 */
void spm_hal_config_clk_div(uint8_t* spm_base, uint8_t clk_div)
{
  SPM_HWIO_OUTXF(spm_base, CFG, CLK_DIV, clk_div);
}

/*
 * spm_hal_saw_id
 */
uint32_t spm_hal_saw_id(uint8_t* spm_base)
{
  spm_base += SAW4_STS_REG_BASE_OFFS;
  return (SPM_HWIO_INX(spm_base, ID));
}

/*
 * spm_hal_vctl
 */
uint32_t spm_hal_vctl(uint8_t* spm_base)
{
  spm_base += SAW4_AVS_REG_BASE_OFFS;
  return (SPM_HWIO_INXF(spm_base, VCTL, PMIC_DATA));
}

/*
 * spm_hal_status
 */
uint32_t spm_hal_status(uint8_t* spm_base)
{
  spm_base += SAW4_STS_REG_BASE_OFFS;
  return (SPM_HWIO_INX(spm_base, SPM_STS));
}

/*
 * spm_hal_status2
 */
uint32_t spm_hal_status2(uint8_t* spm_base)
{
  spm_base += SAW4_STS_REG_BASE_OFFS;
  return (SPM_HWIO_INX(spm_base, SPM_STS2));
}

/*
 * spm_hal_status3
 */
uint32_t spm_hal_status3(uint8_t* spm_base)
{
  spm_base += SAW4_STS_REG_BASE_OFFS;
  return (SPM_HWIO_INX(spm_base, SPM_STS3));
}

/*
 * spm_hal_config_isar
 */
void spm_hal_config_isar(uint8_t* spm_base, uint8_t isar)
{
  isar = (0 != isar) ? 1 : 0;
  SPM_HWIO_OUTXF(spm_base, SPM_CTL, ISAR, isar);
}

/*
 * spm_hal_config_wakeup
 */
void spm_hal_config_wakeup(uint8_t* spm_base, uint8_t wakeup_config)
{
  SPM_HWIO_OUTXF(spm_base, SPM_CTL, WAKEUP_CONFIG, wakeup_config);
}

/*
 * spm_hal_config_index_delay
 */
void spm_hal_config_index_delay
(
  uint8_t* spm_base,
  uint8_t delay_index,
  uint16_t delay
)
{
  switch (delay_index)
  {
    case 1:
      SPM_HWIO_OUTXF(spm_base, SPM_DLY, DLY1, delay);
      break;
    case 2:
      SPM_HWIO_OUTXF(spm_base, SPM_DLY, DLY2, delay);
      break;
    case 3:
      SPM_HWIO_OUTXF(spm_base, SPM_DLY, DLY3, delay);
      break;
    default:
      /* May be error fatal but need a proper macro that works in all
       * environment without losing context. */
      break;
  }
}

void spm_hal_config_delays
(
  uint8_t *spm_base,
  uint16_t delay1,
  uint16_t delay2,
  uint16_t delay3
)
{
  uint32_t mask = SPM_HWIO_FMSK(SPM_DLY, DLY1) |
                SPM_HWIO_FMSK(SPM_DLY, DLY2) |
                SPM_HWIO_FMSK(SPM_DLY, DLY3);

  uint32_t val = SPM_HWIO_FVAL(SPM_DLY, DLY1, delay1) |
               SPM_HWIO_FVAL(SPM_DLY, DLY2, delay2) |
               SPM_HWIO_FVAL(SPM_DLY, DLY3, delay3);

  SPM_HWIO_OUTXM(spm_base, SPM_DLY, mask, val);
}

/*
 * spm_hal_config_rpm_handshake
 */
void spm_hal_config_rpm_handshake(uint8_t *spm_base, uint8_t rpm_hs)
{
  rpm_hs = (0 != rpm_hs) ? 1 : 0;
  SPM_HWIO_OUTXF(spm_base, SPM_CTL, SLP_CMD_MODE, rpm_hs);
}

/*
 * spm_hal_config_lpm_ctl
 * SPM_START_ADR:	复位SPM_START_ADR，从而可以开始一个新的cmd sequence
 * SLEEP_REQ:		SW can write into this bit to start the SPM sequence.
 * PWR_STATE_IDX: 	Indicates the power state index of the core.
 * SPM_EN:			SPM Enable
 */
void spm_hal_config_lpm_ctl(uint8_t* spm_base, uint32_t ctl_val)
{
  /* Mask of mode specific fields */
  uint32_t mask = ((SPM_HWIO_FMSK(SPM_CTL, ISAR)) |
                 (SPM_HWIO_FMSK(SPM_CTL, SPM_START_ADR)) |
                 (SPM_HWIO_FMSK(SPM_CTL, PWR_STATE_IDX)) |
                 (SPM_HWIO_FMSK(SPM_CTL, EVENT_SYNC)) |
                 (SPM_HWIO_FMSK(SPM_CTL, SLEEP_REQ)) |
                 (SPM_HWIO_FMSK(SPM_CTL, SPM_EN)));

  SPM_HWIO_OUTXM(spm_base, SPM_CTL, mask, ctl_val);
}

/*
 * spm_hal_config_pmic
 */
void spm_hal_config_pmic
(
  uint8_t* spm_base,
  uint8_t index,
  uint8_t addr_index,
  uint16_t data,
  uint8_t size,
  uint8_t delay
)
{
  uint32_t mask, val;

  val = SPM_HWIO_INXF((spm_base + SAW4_STS_REG_BASE_OFFS),
                      ID, NUM_SPM_PMIC_DATA);
  if (index >= val)
    return;

  mask = ((SPM_HWIO_FMSK(SPM_PMIC_DATA_n, ADR_IDX)) |
          (SPM_HWIO_FMSK(SPM_PMIC_DATA_n, DATA)) |
          (SPM_HWIO_FMSK(SPM_PMIC_DATA_n, SIZE)) |
          (SPM_HWIO_FMSK(SPM_PMIC_DATA_n, DLY)));

  val = ((SPM_HWIO_FVAL(SPM_PMIC_DATA_n, ADR_IDX, addr_index)) |
         (SPM_HWIO_FVAL(SPM_PMIC_DATA_n, DATA, data)) |
         (SPM_HWIO_FVAL(SPM_PMIC_DATA_n, SIZE, size)) |
         (SPM_HWIO_FVAL(SPM_PMIC_DATA_n, DLY, delay)));

  SPM_HWIO_OUTXMI(spm_base, SPM_PMIC_DATA_n, index, mask, val);
}

/*
 * spm_hal_last_cmd_addr
 */
uint16_t spm_hal_last_cmd_addr(uint8_t* spm_base)
{
  spm_base += SAW4_STS_REG_BASE_OFFS;
  return (SPM_HWIO_INXF(spm_base, SPM_STS, SPM_CMD_ADDR));
}

/*
 * spm_hal_num_cmd_seq_reg
 */
uint16_t spm_hal_num_cmd_seq_reg(uint8_t* spm_base)
{
  spm_base += SAW4_STS_REG_BASE_OFFS;
  return (SPM_HWIO_INXF(spm_base, ID, NUM_SPM_ENTRY));
}

/*
 * spm_hal_config_cmd_seq
 */
void spm_hal_config_cmd_seq(uint8_t *spm_base, uint8_t reg_index, uint32_t val)
{
  if (reg_index >= spm_hal_num_cmd_seq_reg(spm_base))
    return;

  SPM_HWIO_OUTXI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, val);
}

/*
 * spm_hal_cmds_per_seq_reg
 */
uint8_t spm_hal_cmds_per_seq_reg(void)
{
  return SPM_HAL_CMDS_PER_REG;
}

/*
 * spm_hal_cmd_seq_reg_required
 */
uint16_t spm_hal_cmd_seq_reg_required(uint32_t total_cmds)
{
  uint32_t reg_req = (total_cmds + SPM_HAL_CMDS_PER_REG - 1) /
                   SPM_HAL_CMDS_PER_REG;

  return reg_req;
}

/*
 * spm_hal_config_event
 */
void spm_hal_config_event(uint8_t* spm_base, uint8_t sync, uint8_t event_num)
{
  uint32_t sync_val = SPM_HWIO_INXF(spm_base, SPM_CTL, EVENT_SYNC);
  sync_val = sync ?
             BIT_SET32(sync_val, event_num) : BIT_CLR32(sync_val, event_num);

  SPM_HWIO_OUTXF(spm_base, SPM_CTL, EVENT_SYNC, sync_val);
}

/*
 * spm_hal_config_cmd_at_index
 */
void spm_hal_config_cmd_at_index
(
  uint8_t *spm_base,
  uint8_t reg_index,
  uint8_t cmd_index,
  uint8_t cmd
)
{
  if (reg_index >= spm_hal_num_cmd_seq_reg(spm_base))
    return;

  switch (cmd_index)
  {
    case 0:
      SPM_HWIO_OUTXFI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, CMD0, cmd);
      break;
    case 1:
      SPM_HWIO_OUTXFI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, CMD1, cmd);
      break;
    case 2:
      SPM_HWIO_OUTXFI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, CMD2, cmd);
      break;
    case 3:
      SPM_HWIO_OUTXFI(spm_base, SPM_SLP_SEQ_ENTRY_n, reg_index, CMD3, cmd);
      break;
    default:
      break;
  }
}

/*
 * spm_hal_config_cmd_seq_start_addr
 */
void spm_hal_config_cmd_seq_start_addr(uint8_t *spm_base, uint16_t start_addr)
{
  SPM_HWIO_OUTXF(spm_base, SPM_CTL, SPM_START_ADR, start_addr);
}

/*
 * spm_hal_copy_cmd_seq
 */
uint16_t spm_hal_copy_cmd_seq
(
  uint8_t *spm_base,
  uint16_t start_adr,
  uint8_t* cmds,
  uint16_t size
)
{
  uint32_t mask = 0, val = 0;
  uint32_t cmd_mask = 0, cmd_shift = 0;
  uint16_t cmds_copied = 0;
  uint16_t i = 0, addr = start_adr;
  uint16_t max_cmds = SPM_HWIO_INXF(spm_base, ID, NUM_SPM_ENTRY) *
                    SPM_HAL_CMDS_PER_REG;

  if ((start_adr >= max_cmds) || ((start_adr + size) > max_cmds))
  {
    return cmds_copied;
  }

  for (i = 0; i < size; i++, addr++)
  {
    switch (addr % SPM_HAL_CMDS_PER_REG)
    {
      case 0:
        if (0 != cmds_copied)
        {
          /* We hit register boundary - perform actual write if we processed
           * any command . */
          SPM_HWIO_OUTXMI(spm_base, SPM_SLP_SEQ_ENTRY_n,
                          ((addr-1)/SPM_HAL_CMDS_PER_REG), mask, val);
          mask = val = 0;
        }
        cmd_mask = SPM_HWIO_FMSK(SPM_SLP_SEQ_ENTRY_n, CMD0);
        cmd_shift = SPM_HWIO_SHFT(SPM_SLP_SEQ_ENTRY_n, CMD0);
        break;

      case 1:
        cmd_mask = SPM_HWIO_FMSK(SPM_SLP_SEQ_ENTRY_n, CMD1);
        cmd_shift = SPM_HWIO_SHFT(SPM_SLP_SEQ_ENTRY_n, CMD1);
        break;

      case 2:
        cmd_mask = SPM_HWIO_FMSK(SPM_SLP_SEQ_ENTRY_n, CMD2);
        cmd_shift = SPM_HWIO_SHFT(SPM_SLP_SEQ_ENTRY_n, CMD2);
        break;

      case 3:
        cmd_mask = SPM_HWIO_FMSK(SPM_SLP_SEQ_ENTRY_n, CMD3);
        cmd_shift = SPM_HWIO_SHFT(SPM_SLP_SEQ_ENTRY_n, CMD3);
        break;
    }

    mask |= cmd_mask;
    val |= (((uint32_t)(cmds[i])) << cmd_shift);
    cmds_copied++;
  }

  SPM_HWIO_OUTXMI(spm_base, SPM_SLP_SEQ_ENTRY_n,
                  ((addr-1)/SPM_HAL_CMDS_PER_REG), mask, val);

  return cmds_copied;
}

/*
 * spm_hal_invalidate_cmd_seqs
 */
void spm_hal_invalidate_cmd_seqs(uint8_t *spm_base)
{
  const uint32_t val = 0x0F0F0F0F;       /* End of sequence commands */
  uint32_t i;
  uint32_t reg_count = spm_hal_num_cmd_seq_reg(spm_base);

  for (i = 0; i < reg_count; i++)
    SPM_HWIO_OUTXI(spm_base, SPM_SLP_SEQ_ENTRY_n, i, val);
}
