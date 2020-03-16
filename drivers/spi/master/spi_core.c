/*==============================================================================
# Copyright (c) 2017 Qualcomm Datacenter Technologies, Inc.
# All Rights Reserved.
# Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
# Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#=============================================================================*/
/** @file   spi_core.c
 *  @Author Ross Aiken (raiken@qti.qualcomm.com)
 *  @date   2016.02.19
 */

#include <asm/mach-qdf2400/spi/spi_core.h>
#include <asm/mach-qdf2400/spi/spi_defs.h>
#include <asm/mach-qdf2400/hal/HALspiHWIO.h>
#include <target/delay.h>

#define QUP_RUN_STATE_CHANGE_TIME_OUT_US 100
#define QUP_COMPLETION_TIME_OUT_US       400

#define LOG_MAX 50
static uint32_t inLog[LOG_MAX];
static uint32_t inCount;
static uint32_t outLog[LOG_MAX];
static uint32_t outCount;
static uint32_t qupOpLog[LOG_MAX];
static uint32_t qupOpCount;
static void writeLog(uint32_t log[], uint32_t *logCnt, uint32_t data)
{
    log[*logCnt] = data;
    *logCnt = *logCnt + 1;
    if(*logCnt >= LOG_MAX)
      *logCnt = 0;
}

static bool spi_core_is_state_valid(spi_hw_info *hw)
{
    uint32_t timeout_us = QUP_RUN_STATE_CHANGE_TIME_OUT_US;
    while(!REG_INF(hw->base_addr, QUP_STATE, STATE_VALID) && timeout_us--)
    {
        udelay(1);
    }
    if(!REG_INF(hw->base_addr, QUP_STATE, STATE_VALID))
    {
        return false;
    }
    return true;
}

spi_status_t spi_core_sw_reset(spi_hw_info *hw)
{
    REG_OUT(hw->base_addr, QUP_SW_RESET, 1);
    if(spi_core_is_state_valid(hw))
    {
        hw->state = SPI_CORE_STATE_RESET;
        return SPI_SUCCESS;
    }
    return SPI_ERROR_QUP_STATE_INVALID;
}
spi_status_t spi_core_set_state(spi_hw_info *hw, spi_core_state new_state)
{
    if(!spi_core_is_state_valid(hw))
    {
        return SPI_ERROR_QUP_STATE_INVALID;
    }
    REG_OUTF(hw->base_addr, QUP_STATE, STATE, new_state);

    __asm("dsb sy");

    if(!spi_core_is_state_valid(hw))
    {
        return SPI_ERROR_QUP_STATE_INVALID;
    }
    hw->state = new_state;
    return SPI_SUCCESS;
}

void spi_core_init(spi_hw_ctxt *h_ctxt)
{
    uint8_t *base_addr = h_ctxt->hw.base_addr;

    REG_OUT(base_addr, QUP_CONFIG, FLD_SET(QUP_CONFIG,MINI_CORE,MINI_CORE_SPI));
    REG_OUT(base_addr, SPI_CONFIG, FLD_SET(SPI_CONFIG, SLAVE_OPERATION, 0));

    h_ctxt->hw.initialized = true;
}
void spi_core_deinit(spi_hw_ctxt *h_ctxt)
{
    h_ctxt->hw.initialized = false;
}

void spi_core_configure(spi_hw_ctxt *h_ctxt)
{
    spi_hw_info        *hw     = &(h_ctxt->hw);
    const spi_config_t *config = h_ctxt->config;

    REG_OUT(hw->base_addr, QUP_ERROR_FLAGS_EN,
            FLD_SET(QUP_ERROR_FLAGS_EN, INPUT_OVER_RUN_ERR_EN,   1) |
            FLD_SET(QUP_ERROR_FLAGS_EN, OUTPUT_UNDER_RUN_ERR_EN, 1) |
            FLD_SET(QUP_ERROR_FLAGS_EN, INPUT_UNDER_RUN_ERR_EN,  1) |
            FLD_SET(QUP_ERROR_FLAGS_EN, OUTPUT_OVER_RUN_ERR_EN,  1));


    REG_OUT(hw->base_addr, SPI_CONFIG,
            FLD_SET(SPI_CONFIG, INPUT_FIRST, config->shift_mode) |
            FLD_SET(SPI_CONFIG, HS_MODE,     config->hs_mode) |
            FLD_SET(SPI_CONFIG, LOOP_BACK,   config->loopback_mode));

    // set IO_CONTROL bits
    REG_OUT(hw->base_addr, SPI_IO_CONTROL,
            FLD_SET(SPI_IO_CONTROL, CLK_IDLE_HIGH, config->clk_polarity) |
            FLD_SET(SPI_IO_CONTROL, CLK_ALWAYS_ON, config->clk_mode) |
            FLD_SET(SPI_IO_CONTROL, MX_CS_MODE,    config->cs_mode) |
            FLD_SET(SPI_IO_CONTROL, CS_SELECT,     config->slave_index));

    // configure CS polarity
    {
        uint32_t temp = REG_INF(hw->base_addr, SPI_IO_CONTROL, CS_N_POLARITY);
        uint32_t temp_mask = 1 << config->slave_index;
        temp = (config->cs_polarity == SPI_CS_ACTIVE_HIGH) ?
               temp |  temp_mask :
               temp & ~temp_mask ;
        REG_OUTF(hw->base_addr, SPI_IO_CONTROL, CS_N_POLARITY, temp);
    }

    //compute CS deassertion time
    {
        uint32_t ns_per_tick = 1000000000U / h_ctxt->real_freq;
        uint32_t deassert_ticks = (config->deassertion_time_ns + \
                                 (ns_per_tick - 1)) / ns_per_tick;

        if(deassert_ticks < 1)                     deassert_ticks = 1;
        if(deassert_ticks < 2 && config->hs_mode)  deassert_ticks = 2;
        if(deassert_ticks > 64)                    deassert_ticks = 64;

        REG_OUT(hw->base_addr, SPI_DEASSERT_WAIT, deassert_ticks);
    }

}

void spi_core_runtime_configure(spi_hw_ctxt *h_ctxt)
{
    const spi_config_t *config = h_ctxt->config;
    spi_hw_info        *hw     = &(h_ctxt->hw);
    transfer_ctxt      *t_ctxt = &(h_ctxt->t_ctxt);
    uint32_t           qup_cfg = 0;

    // Set packing mode
    {
        bool pack  = (config->bits_per_word > 16) ? false : true;
        REG_OUT(hw->base_addr, QUP_IO_MODES,
                FLD_SET(QUP_IO_MODES, OUTPUT_BIT_SHIFT_EN, 1) |
                FLD_SET(QUP_IO_MODES, PACK_EN,             pack) |
                FLD_SET(QUP_IO_MODES, UNPACK_EN,           pack) |
                FLD_SET(QUP_IO_MODES, INPUT_MODE,          MODE_BLOCK) |
                FLD_SET(QUP_IO_MODES, OUTPUT_MODE,         MODE_BLOCK));

        REG_OUT(hw->base_addr, QUP_MX_INPUT_COUNT,  t_ctxt->rx_info->word_count + \
                ((config->bits_per_word == 8) ? (t_ctxt->tx_info->word_count > 5 ? 5 : t_ctxt->tx_info->word_count) : 0) );
        REG_OUT(hw->base_addr, QUP_MX_OUTPUT_COUNT, t_ctxt->tx_info->word_count);
        //QCTDD00302688, explicitly set to 0
        REG_OUT(hw->base_addr, QUP_MX_READ_COUNT,  0);
        REG_OUT(hw->base_addr, QUP_MX_WRITE_COUNT, 0);
    }

    qup_cfg = REG_IN(hw->base_addr, QUP_CONFIG);

    /* Clear fields */
    qup_cfg &= ~(FLD_BMSK(QUP_CONFIG, MINI_CORE) |
            FLD_BMSK(QUP_CONFIG, N) |
            FLD_BMSK(QUP_CONFIG, NO_INPUT) |
            FLD_BMSK(QUP_CONFIG, NO_OUTPUT));
    /* Set fields */
    qup_cfg |= (FLD_SET(QUP_CONFIG, MINI_CORE, 1) |
            FLD_SET(QUP_CONFIG, N, (config->bits_per_word - 1)) |
            FLD_SET(QUP_CONFIG, NO_OUTPUT, t_ctxt->tx_info->word_count == 0) |
            FLD_SET(QUP_CONFIG, NO_INPUT, t_ctxt->rx_info->word_count == 0));

    REG_OUT(hw->base_addr, QUP_CONFIG, qup_cfg);

    //ToDo: Handle error interrupts
    REG_OUT(hw->base_addr, QUP_OPERATIONAL_MASK,
            FLD_SET(QUP_OPERATIONAL_MASK, INPUT_SERVICE_MASK, 1) |
            FLD_SET(QUP_OPERATIONAL_MASK, OUTPUT_SERVICE_MASK, 1));
}

static void spi_core_rd_block(spi_hw_ctxt *h_ctxt)
{
    uint32_t idx;
    uint32_t in;
    transfer_ctxt *t_ctxt = &(h_ctxt->t_ctxt);
    spi_hw_info   *hw     = &(h_ctxt->hw);

    for(idx = 0; idx < t_ctxt->rx_info->word_count; idx++)
    {
        in = REG_IN(hw->base_addr, QUP_INPUT_FIFOc);
        writeLog(inLog, &inCount, in);
        if(t_ctxt->rx_bytes < t_ctxt->rx_info->buf_len)
        {
              t_ctxt->rx_info->buf_addr[t_ctxt->rx_bytes] = in;
              t_ctxt->rx_bytes += 1;
        }
    }
}

static void spi_core_rd_b8(spi_hw_ctxt *h_ctxt)
{
    uint32_t idx;
    uint32_t in;
    transfer_ctxt *t_ctxt = &(h_ctxt->t_ctxt);
    spi_hw_info   *hw     = &(h_ctxt->hw);
    uint32_t total = t_ctxt->tx_info->word_count + t_ctxt->rx_info->word_count;
    uint8_t *ptr = (uint8_t *)t_ctxt->rx_info->buf_addr + t_ctxt->rx_bytes - t_ctxt->tx_info->word_count;

    while (t_ctxt->rx_bytes < total) {
        if (!REG_INF(hw->base_addr, QUP_OPERATIONAL, INPUT_FIFO_NOT_EMPTY))
            break;

        in = REG_IN(hw->base_addr, QUP_INPUT_FIFOc);

        for (idx = 0; idx < sizeof(in); idx++) {
            /* skip the leading tx_info->word_count bytes */
            if (t_ctxt->rx_bytes >= t_ctxt->tx_info->word_count && t_ctxt->rx_bytes < total)
                *ptr = ((uint8_t *)&in)[idx];
            t_ctxt->rx_bytes++;
            ptr++;
        }
    }
}

static void spi_core_wr_block(spi_hw_ctxt *h_ctxt)
{
    uint32_t       idx;
    uint32_t       out;
    transfer_ctxt *t_ctxt = &(h_ctxt->t_ctxt);
    spi_hw_info   *hw     = &(h_ctxt->hw);

    for(idx = 0; idx < t_ctxt->tx_info->word_count; idx++)
    {
        out = 0;
        if (t_ctxt->tx_bytes < t_ctxt->tx_info->buf_len)
        {
              out = t_ctxt->tx_info->buf_addr[t_ctxt->tx_bytes];
			  t_ctxt->tx_bytes += 1;
        }
        writeLog(outLog, &outCount, out);
        REG_OUT(hw->base_addr, QUP_OUTPUT_FIFOc, out);
    }
}

static void spi_core_wr_b8(spi_hw_ctxt *h_ctxt)
{
    uint32_t       out;
    transfer_ctxt *t_ctxt = &(h_ctxt->t_ctxt);
    spi_hw_info   *hw     = &(h_ctxt->hw);

    while (t_ctxt->tx_bytes < t_ctxt->tx_info->word_count)
    {
        if (REG_INF(hw->base_addr, QUP_OPERATIONAL, OUTPUT_FIFO_FULL))
            break;

        /* assuming 32-bit word aligned */
        out = t_ctxt->tx_info->buf_addr[t_ctxt->tx_bytes >> 2];
        t_ctxt->tx_bytes += sizeof(out);
        REG_OUT(hw->base_addr, QUP_OUTPUT_FIFOc, out);
    }
}

static uint32_t spi_core_get_error(spi_hw_info *hw)
{
    uint32_t q_error = REG_IN(hw->base_addr, QUP_ERROR_FLAGS);
    return q_error &
           (FLD_BMSK(QUP_ERROR_FLAGS_EN, INPUT_OVER_RUN_ERR_EN) |
            FLD_BMSK(QUP_ERROR_FLAGS_EN, OUTPUT_UNDER_RUN_ERR_EN) |
            FLD_BMSK(QUP_ERROR_FLAGS_EN, INPUT_UNDER_RUN_ERR_EN) |
            FLD_BMSK(QUP_ERROR_FLAGS_EN, OUTPUT_OVER_RUN_ERR_EN));
}

static spi_status_t spi_core_io(spi_hw_ctxt *h_ctxt, bool *xfer_complete)
{
    spi_hw_info *hw = &(h_ctxt->hw);
    transfer_ctxt *t_ctxt = &(h_ctxt->t_ctxt);
    uint32_t qup_error_flags;
    uint32_t qup_operational;

    while(1)
    {
        qup_error_flags = spi_core_get_error(hw);
        qup_operational = REG_IN(hw->base_addr, QUP_OPERATIONAL);
        bool output_service =
            FLD_GET(qup_operational, QUP_OPERATIONAL, OUT_BLOCK_WRITE_REQ);
        bool input_service  =
            FLD_GET(qup_operational, QUP_OPERATIONAL, IN_BLOCK_READ_REQ);

        if(qup_error_flags != 0)
        {
            t_ctxt->tx_done = true;
            t_ctxt->rx_done = true;
            t_ctxt->status  = qup_error_flags;
            spi_core_sw_reset(hw);
            return SPI_ERROR_CORE_ERROR;
        }
        if(t_ctxt->rx_info->buf_len == 0) input_service  = 0;
        if(t_ctxt->tx_info->buf_len == 0) output_service = 0;
        if((!output_service) && (!input_service)) break;
        writeLog(qupOpLog, &qupOpCount, qup_operational);

        if(output_service && (0 != (qup_operational &
                                    HWIO_QUP_OPERATIONAL_OUT_BLOCK_WRITE_REQ_BMSK)))
        {
            // Clear these before handling due to hw bug
            REG_OUT(hw->base_addr, QUP_OPERATIONAL,
                    FLD_SET(QUP_OPERATIONAL, OUTPUT_SERVICE_FLAG, 1));
            if (h_ctxt->config->bits_per_word == 8)
                spi_core_wr_b8(h_ctxt);
            else
                spi_core_wr_block(h_ctxt);
        }

        if(input_service && (0 != (qup_operational &
                                   HWIO_QUP_OPERATIONAL_IN_BLOCK_READ_REQ_BMSK)))
        {
            // Clear these before handling due to hw bug
            REG_OUT(hw->base_addr, QUP_OPERATIONAL,
                    FLD_SET(QUP_OPERATIONAL, INPUT_SERVICE_FLAG,  1));
            if (h_ctxt->config->bits_per_word == 8)
                spi_core_rd_b8(h_ctxt);
            else
                spi_core_rd_block(h_ctxt);
        }
    }
    if((FLD_GET(qup_operational, QUP_OPERATIONAL, MAX_OUTPUT_DONE_FLAG) != 0) &&
            t_ctxt->tx_bytes > 0)
    {
        t_ctxt->tx_done = true;
    }
    if((FLD_GET(qup_operational, QUP_OPERATIONAL, MAX_INPUT_DONE_FLAG) != 0) &&
            t_ctxt->rx_bytes > 0)
    {
        t_ctxt->rx_done = true;
    }

    if(t_ctxt->tx_done && t_ctxt->rx_done)
    {
        spi_core_sw_reset(hw);
        *xfer_complete = true;
    }

    return SPI_SUCCESS;
}

spi_status_t spi_core_wait_for_completion(spi_hw_ctxt *h_ctxt)
{
    int32_t        timeout_us    = QUP_COMPLETION_TIME_OUT_US;
    bool      xfer_complete = false;
    spi_status_t status = SPI_ERROR_TRANSFER_TIMEOUT;

    while(timeout_us-- > 0)
    {
        status = spi_core_io(h_ctxt, &xfer_complete);
        if(status != SPI_SUCCESS)
        {
            spi_core_sw_reset(&(h_ctxt->hw));
            return status;
        }

        status = SPI_ERROR_TRANSFER_TIMEOUT;

        if (xfer_complete)
            break;
        else
            udelay(1);
    }

    return SPI_SUCCESS;
}
