/*!****************************************************************************
*
* @copyright Copyright (c) 2012-2016 Qualcomm Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Technologies, Inc.</B>
*
* @copyright Copyright (c) 2016-2017 Qualcomm Datacenter Technologies, Inc.
* <B>All Rights Reserved.</B>
* <B>Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.</B>
*
* <I>This software may be subject to U.S. and international export, re-export, or
* transfer ("export") laws.  Diversion contrary to U.S. and international law
* is strictly prohibited.</I>
*
* @file spd_smbus_impl.c
*
* @par Description:
*    This module provides the functionality to load and extract the SPD
*    information for a DIMM slot in the Monaco DDR subsystem.
*
* @par Notes:
*
*
******************************************************************************/

/******************************************************************************
* Included Headers
******************************************************************************/

#include <stdint.h>
#include <string.h>
#include <target/ddr.h>

/******************************************************************************
* Global Variables
******************************************************************************/
uint32_t qup0_out_blk_size;
uint32_t qup0_out_fifo_size;
uint32_t qup0_in_blk_size;
uint32_t qup0_in_fifo_size;
uint32_t qup1_out_blk_size;
uint32_t qup1_out_fifo_size;
uint32_t qup1_in_blk_size;
uint32_t qup1_in_fifo_size;


/******************************************************************************
* Defined Constants
******************************************************************************/
uint32_t delay_global_;
uint32_t delay_index_;


/******************************************************************************
* Function Prototypes
******************************************************************************/
void spd_smbus_init_qup(uint64_t qup_base);
void spd_smbus_get_in_out_sizes(uint64_t qup_base);
void spd_smbus_calc_blk_fifo_sizes(uint8_t blkbits, uint8_t fifobits, uint32_t *blksize, uint32_t *fifosize);
void spd_smbus_reset_qup(uint64_t qup_base);
void spd_smbus_init_xfer(uint64_t qup_base, bool enable_input, bool enable_output);
void spd_smbus_enable_i2c_clk(uint64_t qup_base);
void spd_smbus_disable_i2c_clk(uint64_t qup_base);
unsigned spd_smbus_check_errors(uint64_t qup_base);
void spd_smbus_wait_clk_n_data(uint64_t qup_base);
void spd_smbus_wait_bus_idle(uint64_t qup_base);
void spd_smbus_wait_valid_state(uint64_t qup_base);
void spd_smbus_set_qup_state(uint64_t qup_base, qup_state_t state);
bool spd_smbus_set_write_mode(uint64_t qup_base, uint32_t write_len, uint32_t out_fifosize);
bool spd_smbus_set_read_mode(uint64_t qup_base, uint32_t read_len, uint32_t in_fifosize);
unsigned spd_detect_dimm(uint64_t qup_base);
unsigned spd_switch_bank(uint64_t qup_base, uint8_t spd_bank_num, uint32_t out_fifosize);
unsigned spd_smbus_dimm_block_read(uint64_t qup_base, uint8_t spd_bus_addr, /* uint16_t spd_reg_id,*/ uint32_t xfer_block_size, void * dst_buff_addr);
unsigned spd_smbus_dimm_block_write(uint64_t qup_base, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint32_t xfer_block_size);


/******************************************************************************
* External Functions
******************************************************************************/
/*!****************************************************************************
*
* @par Description:
*    This function intializes the 2 QUP subsystems on BLSP1.
*
*                                  @param
*    none
*
* @return
*    nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_init_qups(void)
{
    // Init BLSP1 QUP0 subsystem. QUP0 handles DDR channels 0,1,3.
    spd_smbus_init_qup(QUP0_QUP_BASE_ADDRESS);
    // Init BLSP1 QUP1 subsystem.  QUP1 handles DDR channels 2,4,5.
    spd_smbus_init_qup(QUP1_QUP_BASE_ADDRESS);
}



/*!****************************************************************************
*
* @par Description:
*    This function intializes any of the 2 QUP subsystems on BLSP1.
*
*                                  @param
*    qup_base       The base address of the QUP to be initialized
*
* @return
*    nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_init_qup(uint64_t qup_base)
{
    monaco_log(INFORMATIONAL, "QUP %d at Version: %08x using v2 tags\n", (qup_base == QUP0_QUP_BASE_ADDRESS ? 0 : 1), read32(qup_base + QUP_HW_VERSION_OFFSET));


    // Get the sizes of the input/output block (for Block mode read/write) and input/output FIFO
    spd_smbus_get_in_out_sizes(qup_base);

    // Reset the entire QUP core and all mini-cores
    spd_smbus_reset_qup(qup_base);

}


/*!****************************************************************************
*
* @par Description:
*    This function intializes the TLMM: turn on clock gating and configure the
*   GPIOs for the BLSP1 QUP0/1 I2C SCL and SDA lines.
*
*                                  @param
*    none
*
* @return
*    nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_setup_tlmm(void)
{
    // Not sure if we need to enable the clock gating in the TLMM.
    // By writing 0x7 to this reg the clock gating is on for: AHB clock,
    //  Summary Interrupt Demets and Read Data Register on the CRIF
    write32(TLMM_CLK_GATE_EN_REG_ADDR, 0x7);

    // Configure the GPIO's for the BLSP1_I2C0/1_SCL/SDA lines:
    // Value of 0x287 means: enable output, drive strength 6mA, Function 1, weak Pull-Up

    // Function 1 GPIO 0 blsp1_i2c0_sda
    write32(TLMM_GPIO_CFG0_REG_ADDR, 0x287);

    // Function 1 GPIO 1 blsp1_i2c0_scl
    write32(TLMM_GPIO_CFG1_REG_ADDR, 0x287);

    // Function 1 GPIO 2 blsp1_i2c1_sda
    write32(TLMM_GPIO_CFG2_REG_ADDR, 0x287);

    // Function 1 GPIO 3 blsp1_i2c1_sda
    write32(TLMM_GPIO_CFG3_REG_ADDR, 0x287);
}



/*!****************************************************************************
*
* @par Description:
*    This function reads a 8-bit byte from the SMBus device (e.g. EEPROM)
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be retrieved.
*                                  @param
*    spd_reg_id       The SPD register id of the start of the information to
*                      be retrieved.
*                                  @param
*    spd_data_ptr     Pointer to where the SPD data byte is to be stored.
*
* @return
*    Status indicating if the data could be retrieved from the slave device.
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
unsigned spd_smbus_dimm_get_byte
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint32_t spd_reg_id,
    uint8_t *spd_data_ptr
)
{

    unsigned status = COM_OK;


    status = spd_smbus_dimm_get_block(smbus_id, spd_bus_addr, 0, spd_reg_id, 1, spd_data_ptr);

    if (status == COM_ERROR)
    {
        *spd_data_ptr = 0;
    }

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    This function reads a 16-bit word from the SMBus device (e.g. Temp Sensor)
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be retrieved.
*                                  @param
*    spd_reg_id       The SPD register id of the start of the information to
*                      be retrieved.
*                                  @param
*    spd_data_ptr     Pointer to where the SPD data byte is to be stored.
*
* @return
*    Status indicating if the data could be retrieved from the slave device.
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
unsigned spd_smbus_dimm_get_word
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint32_t spd_reg_id,
    uint16_t *spd_data_ptr
)
{
    unsigned status = COM_OK;
    uint16_t spd_data;
    uint16_t lo_byte;
    uint16_t hi_byte;


    status = spd_smbus_dimm_get_block(smbus_id, spd_bus_addr, 0, spd_reg_id, 2, &spd_data);

    // Used a block function so this needs to swap the bytes for endianness.
    lo_byte = (spd_data >> BITS_PER_BYTE) & 0xFF;
    hi_byte = spd_data & 0xFF;;


    *spd_data_ptr = (hi_byte << BITS_PER_BYTE) | lo_byte;

    if (status == COM_ERROR)
    {
        *spd_data_ptr = 0;
    }


    return status;
}



/*!****************************************************************************
*
* @par Description:
*   This function reads a block of SPD data from the slave starting at the given
*     offset
*
*                                  @param
*    smbus_id           SMBus ID where the SPD information is located.
*                                  @param
*    spd_bus_addr       SMBus address of the device whose SPD information is
*                        to be retrieved.
*                                  @param
*    spd_bank_num       DDR4: the SPD info is placed in 2 x 256B banks to be switched
*                        between. DDR3: there are no banks but one 256B info
*                        chunk (this param is set to 0 by default).
*                                  @param
*    spd_reg_id         SMBus register id of the start of the block of SPD
*                        information to be retrieved.
*                                  @param
*    xfer_block_size    Size of the block of SPD information to retrieve.
*                                  @param
*    dst_buff_addr      Void pointer to the address of the buffer to receive the SPD
*                        information.
*
*
* @return
*    An indication of the level of success.
*
* @author
*    cbucsan
*
* @par Notes:
*    There are 2 variants of this function with the same signature: this one
*     using a "repeated start" in the message buffer
*     to combine the write and the read transactions and a second function
*     (see below) which uses separate write and read
*     transactions. Either one of them may be used while the other one is
*     commented out (#if/#endif); note that the functions:
*        spd_smbus_dimm_block_write and spd_smbus_dimm_block_read
*     are invoked by the second variant.
*
******************************************************************************/
#if 1
unsigned spd_smbus_dimm_get_block
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint8_t spd_bank_num,
    uint16_t spd_reg_id,
    uint32_t xfer_block_size,
    void * dst_buff_addr
)

{
    unsigned status = COM_OK;

    uint64_t qup_base;
    bool enable_input;       // enable/disable input FIFO
    bool enable_output;      // enable/disable output FIFO
    uint32_t read_overhead;  // (in-FIFO) num of bytes other than the bytes to be
                             //   read out of slave i.e. control tag and byte count
//    uint32_t write_overhead; // (out_FIFO) START tag, slave addr, control tag, byte
                             //   count i.e. num bytes excepting the register
                             //   address(offset for block to be read)
    uint32_t write_len;      // byte count in the out-FIFO
    uint32_t read_len;       // byte count in the in-FIFO
    uint32_t in_fifosize;    // size of the implemented in-FIFO (dictated by RTL generic)
    uint32_t out_fifosize;   // size of the implemented out-FIFO (dictated by RTL generic)
    uint32_t in_blocksize;   // size of the block in in-FIFO (dictated by RTL generic)
//    local out_blocksize
    bool in_fifo_mode;       // (for in_FIFO): true if in FIFO Mode, false if in Block Mode
//    bool out_fifo_mode;      // (for out_FIFO): true if in FIFO Mode, false if in Block Mode

    // buffer holding 32-bit data to be written to the out-FIFO
    uint32_t msgbuf[SPD_SMBUS_MSGBUF_SIZE];
    // same data in bytes
    uint8_t *msgbuf_bytes = (uint8_t *)msgbuf;
    // buffer to hold the data read from slave present in the in-FIFO
    uint32_t databuf[SPD_SMBUS_MAX_DATABUF_SIZE];
    uint32_t msgword_ix;    // index in the 32-bit data buffer
    uint32_t msgbyte_ix;
    uint32_t i,j;
    uint32_t val;


    uint8_t *byte_ptr = dst_buff_addr;   // assign the void ptr for byte read


    if (smbus_id == 0)
    {
        qup_base = QUP0_QUP_BASE_ADDRESS;
        in_fifosize = qup0_in_fifo_size;
        out_fifosize = qup0_out_fifo_size;
        in_blocksize = qup0_in_blk_size;
//       out_blocksize=qup0_out_blk_size
    }
    else if (smbus_id == 1)
    {
        qup_base = QUP1_QUP_BASE_ADDRESS;
        in_fifosize = qup1_in_fifo_size;
        out_fifosize = qup1_out_fifo_size;
        in_blocksize = qup1_in_blk_size;
//        out_blocksize=qup1_out_blk_sizee
    }
    else
    {
        monaco_log(INFORMATIONAL, "Invalid QUP subsystem!");
        status = COM_ERROR;
        return status;
    }


    if (spd_bank_num == 1)
    {
        // Select the device bank 1
        status = spd_switch_bank(qup_base, 1, out_fifosize);

        if (status == COM_ERROR)
        {
          return status;
        }
    }
    else
    {
        // Select the device bank 0
        status = spd_switch_bank(qup_base, 0, out_fifosize);

        if (status == COM_ERROR)
        {
          return status;
        }
    }

    write_len = 9;  // to be written to the out-FIFO
    read_overhead = 2;       // 2 bytes i.e. the read data tag byte + number of bytes to read byte
    read_len = read_overhead + xfer_block_size; // length of the read data


    // Initialize the QUP/mini-core for the transfer; enable both in/out FIFO's
    enable_input = true;    // in-FIFO
    enable_output = true;  // out-FIFO
    spd_smbus_init_xfer(qup_base, enable_input, enable_output);

    // Select the transfer mode for input(read) and output(write) FIFOs.
    // The transfer mode (FIFO Mode or Block Mode) is based on the transfer size vs FIFO size.
    // Data from the mini-core will be packed before placing in input FIFO.
    // Data from output FIFO to be unpacked before passing to the mini-core.
    // For out-FIFO
    spd_smbus_set_write_mode(qup_base, write_len, out_fifosize);
    // For in-FIFO
    in_fifo_mode = spd_smbus_set_read_mode(qup_base, read_len, in_fifosize);

    // Go to the RUN state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);

    // Enable the clock
    spd_smbus_enable_i2c_clk(qup_base);

    // Go to the PAUSE state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_PAUSE);

     // Create the message buffer for the block read. We'll use repeated start
    //  to change the direction from write to read as the spec requires a dummy
    //  write to preload the starting data word address.
    memset(msgbuf, 0, SPD_SMBUS_MSGBUF_SIZE*sizeof(msgbuf[0]));
    memset(databuf, 0, SPD_SMBUS_MAX_DATABUF_SIZE*sizeof(databuf[0]));

    msgbyte_ix = msgword_ix = 0;
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_START;
    msgbuf_bytes[msgbyte_ix++] = spd_bus_addr | 0x0;    // it's a write
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_DATA_WRITE;
    msgbuf_bytes[msgbyte_ix++] = SPD_DATA_ADDR_LEN;
    msgbuf_bytes[msgbyte_ix++] = (uint8_t)spd_reg_id;
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_START;  // repeated start
    msgbuf_bytes[msgbyte_ix++] = spd_bus_addr  | 0x01;  // it's a read
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_DATA_READ_N_STOP;
    msgbuf_bytes[msgbyte_ix++] = xfer_block_size;


    msgword_ix = (msgbyte_ix+1)/2;
    for (i=0; i <= (msgword_ix-1)/2; i++)
    {
         write32(qup_base + QUP_OUTPUT_FIFO_BASE_OFFSET, msgbuf[i]);  // write to QUP_OUTPUT_FIFOc; consecutive writes fill up the out FIFO
    }
    // Write the message buffer to the out-FIFO in 32-bit chunks
//    msgword_ix = (msgbyte_ix + 1)/2;
//    for (i = 0; i < 3; i++)
//    {
//        write32(qup_base + QUP_OUTPUT_FIFO_BASE_OFFSET, msgbuf[i]);
//    }

    // Go to the RUN state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);


    // Detect the DIMM presence
    if (xfer_block_size == 1)
    {
        status = spd_detect_dimm(qup_base);
        if (status == COM_ERROR)
        {
//            monaco_log(INFORMATIONAL, " at addr: %lX SLOT_UNPOPULATED\n", spd_bus_addr);

//            write64(dst_buff_addr, 0);
            // for 1 byte transactions any type of error is COM_ERROR
            return status;
        }
//        monaco_log(INFORMATIONAL, " At addr: %X SLOT_POPULATED\n", spd_bus_addr);
    }


    // CB TODO which flag to wait on? OUT_FIFO_NOT_EMPTY or OUT_SERVICE_FLAG?!
    // Wait for the output FIFO to empty. If the flag is set to 1 by HW -> out FIFO has at
    //  least one outstanding value to be shifted out.
//    while (read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_OUT_FIFO_NOT_EMPTY << 4))
//                ;

    // Wait for the output service flag. If the flag is set to 1 by HW -> out FIFO has an
    //  outstanding out service request and qup_irq is asserted.
    while (!(read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_OUT_SERVICE_FLAG << 8)))
                ;

    // Clear the output service flag: SW sets flag to 1 to acknowledge the data
    write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_OUT_SERVICE_FLAG << 8));


    // Switch by read mode
    if (in_fifo_mode) // FIFO mode
    {
        // Wait for the input service flag i.e. for the read from slave to complete. If flag is set
        //  to 1 by HW -> input FIFO has an outstanding in service request and qup_irq is asserted.
        while (!(read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_IN_SERVICE_FLAG << 9)))
                ;

        // Empty the input FIFO into the data buffer. First read in the QUP Operational reg to see if the
        //  in-FIFO not empty bit is set
        i = 0;
//        while ((read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_IN_FIFO_NOT_EMPTY << 5)) && (i < read_len))
        while ((read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_IN_FIFO_NOT_EMPTY << 5)) && (i < SPD_SMBUS_MAX_DATABUF_SIZE))
        {
            databuf[i] = read32(qup_base + QUP_INPUT_FIFO_BASE_OFFSET);
            i++;
            ddr_wait_us(1000);  // 1000us
        }

        // Check for QUP/mini-core errors
        status = spd_smbus_check_errors(qup_base);
        if(status == COM_ERROR)
        {
            return status;
        }

        // Clear the in FIFO service operational flag. A 1 written to this also acknowledges SW has or will
        //  read the data
        write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_IN_SERVICE_FLAG << 9));
    }
    else   // Block mode
    {
        // Read in a loop until the read_len byte block is read and databuffer size is not exceeded.
        // Note: the data buffer won't be exceeded because we've already ensured that
        //  the block to read < 256 bytes (i.e. SPD_SMBUS_MAX_FIFO_BLOCK_SIZE)
        i = 0;
        do
        {
            // Wait for block i.e. for either the in-service flag (req to service) or max input done flag (all completed)
            //  to be set before starting the read.
            // QUP_OPER_MAX_IN_DONE_FLAG is set when in-FIFO has reached the MX_INPUT_COUNT that had been set to the size
            //  of the entire block to be read out from slave.
            while (!(read32(qup_base + QUP_OPERATIONAL_OFFSET) & ((QUP_OPER_IN_SERVICE_FLAG << 9) | (QUP_OPER_MAX_IN_DONE_FLAG << 11))))
                        ;

            // Check for QUP/mini-core errors.
            status = spd_smbus_check_errors(qup_base);
            if(status == COM_ERROR)
            {
                return status;
            }

            // Clear the in FIFO service operational flag. A 1 written to this also acknowledges SW has or will
            //  read the data.
             write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_IN_SERVICE_FLAG << 9));

            // Fill the data buffer from in-FIFO.
            // Note that in Block mode the the in-service flag is asserted after an in_blocksize chunk is read.
            j = 0;
            while ((j++ < in_blocksize/4) &&
                       (read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_IN_FIFO_NOT_EMPTY << 5)) && (i * 4 < read_len))
            {
                // Copy to the data buffer the contents of the in-FIFO
                databuf[i] = read32(qup_base + QUP_INPUT_FIFO_BASE_OFFSET);
                i++;
            }

        } while ((i * 4 < read_len) && (i < SPD_SMBUS_MAX_DATABUF_SIZE));

    }  // end of Block mode read


    if ((databuf[0] & 0xff) != QUP_TAG2_DATA_READ_N_STOP)
    {
       monaco_log(INFORMATIONAL, "Unexpected value in input FIFO after read %08x\n", i);
    }
    if ((((databuf[0] >> 8) & 0xff) != xfer_block_size) && (xfer_block_size != 0x100))
    {
        monaco_log(INFORMATIONAL, "Unexpected size reported in input FIFO after read %d\n", i);
    }
    if (i != (((xfer_block_size+read_overhead)+3)/4))
    {
        monaco_log(INFORMATIONAL, "Incorrect bytes read %d\n", i*4);
    }


    // Wait until all data are gone from out_FIFO and clk is idle
    spd_smbus_wait_clk_n_data(qup_base);

    // Wait until the bus is idle
    spd_smbus_wait_bus_idle(qup_base);

    // Go to the RESET state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RESET);

    // Prepare the data from current databuf (fifo data) for the final destination:
    //  reverse the byte order within each 32 bit word
    for ( i = 0; i < (read_len + 1)/4; i++)
    {
        val = ((databuf[i] & 0xFFFF0000) >> 16) | ((databuf[i + 1] & 0x0000FFFF) << 16);
        databuf[i] = val;
    }

    // Zero out the destination buffer
//    memset(dest, 0, ((xfer_block_size+3)/4)*sizeof(dest[0]));


    // Fill the destination buffer
    if (read_len == 3)  // byte read
    {

        *byte_ptr = (uint8_t)databuf[0];
//        monaco_log(INFORMATIONAL, "Device type is: %x \n", *byte_ptr);

    }
    else   // nbytes
    {

        for (i = 0; i < (read_len + 1); i = i + 4)
        {

            *(byte_ptr + i) = (databuf[i/4] & 0x000000FF);
            *(byte_ptr + i + 1)  = (databuf[i/4] & 0x0000FF00) >> 8;
            *(byte_ptr + i + 2)  = (databuf[i/4] & 0x00FF0000) >> 16;
            *(byte_ptr + i + 3)  = (databuf[i/4] & 0xFF000000) >> 24;

        }
    }

    // Back to the default i.e. to device bank 0
    if (spd_bank_num == 1)
    {
        status = spd_switch_bank(qup_base, 0, out_fifosize);
    }

    return status;
}
#else


/*!****************************************************************************
*
* @par Description:
*   This function reads a block of SPD data from the slave starting at the given
*     offset
*
*                                  @param
*    smbus_id           SMBus ID where the SPD information is located.
*                                  @param
*    spd_bus_addr       SMBus address of the device whose SPD information is
*                        to be retrieved.
*                                  @param
*    spd_bank_num       DDR4: the SPD info is placed in 2 x 256B banks to be switched
*                        between. DDR3: there are no banks but one 256B info
*                        chunk (this param is set to 0 by default).
*                                  @param
*    spd_reg_id         SMBus register id of the start of the block of SPD
*                        information to be retrieved.
*                                  @param
*    xfer_block_size    Size of the block of SPD information to retrieve.
*                                  @param
*    dst_buff_addr      Void pointer to the address of the buffer to receive the SPD
*                        information.
*
*
* @return
*    An indication of the level of success.
*
* @author
*    cbucsan
*
* @par Notes:
*    Like noted above there are 2 variants of this function with the same
*     signature: this is the second one using separate write and read
*     transactions to get a block of data. Either one of them may be used while
*     the other one is commented out (#if/#endif); note that the functions:
*        spd_smbus_dimm_block_write and spd_smbus_dimm_block_read
*     are invoked by this second variant.
*
******************************************************************************/
// split into a write transaction and read transaction
unsigned spd_smbus_dimm_get_block
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint8_t spd_bank_num,
    uint16_t spd_reg_id,
    uint32_t xfer_block_size,
    void * dst_buff_addr
)

{
    unsigned status = COM_OK;

    uint64_t qup_base;

    uint32_t out_fifosize;   // size of the implemented out-FIFO (dictated by RTL generic)

    // Determine the out-fifo size - this is based on a RTL (HW) setting as read from a reg
    if (smbus_id == 0)
    {
        qup_base = QUP0_QUP_BASE_ADDRESS;
        out_fifosize = qup0_out_fifo_size;
    }
    else if (smbus_id == 1)
    {
        qup_base = QUP1_QUP_BASE_ADDRESS;
        out_fifosize = qup1_out_fifo_size;

    }
    else
    {
        monaco_log(INFORMATIONAL, "Invalid QUP subsystem!");
        status = COM_ERROR;
        return status;
    }

    // Select the device bank 1 if necessary
    if (spd_bank_num == 1)
    {
        status = spd_switch_bank(qup_base, 1, out_fifosize);

        if (status == COM_ERROR)
        {
          return status;
        }
    }

    // Perform a write to specify the reg offset in the EEPROM
    status = spd_smbus_dimm_block_write(qup_base, spd_bus_addr, spd_reg_id, xfer_block_size);

    if (status == COM_ERROR)
    {
        return status;
    }

    // Perform a read to get the data
    status = spd_smbus_dimm_block_read(qup_base, spd_bus_addr, /* spd_reg_id,*/ xfer_block_size, dst_buff_addr);

    if (status == COM_ERROR)
    {
        return status;
    }

    // Always back to the default i.e. to device bank 0
    if (spd_bank_num == 1)
    {
        status = spd_switch_bank(qup_base, 0, out_fifosize);
    }

    return status;

}

#endif


/******************************************************************************
* Local Functions
******************************************************************************/


/*!****************************************************************************
*
* @par Description:
*   This function writes the device register offset in preparation for a read
*     starting at this registr offset.
*
*                                  @param
*    qup_base           Base address of the QUP subsystem holding the data to be
*                        retrieved
*                                  @param
*    spd_bus_addr       Bus address of the device whose SPD information is
*                        to be retrieved.
*                                  @param
*                                  @param
*    spd_reg_id         SMBus register id of the start of the block of SPD
*                        information to be retrieved.
*                                  @param
*    xfer_block_size    Size of the block of SPD information to retrieve.
*                                  @param
*
*
* @return
*    An indication of the level of success.
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
#if 0

unsigned spd_smbus_dimm_block_write(uint64_t qup_base, uint8_t spd_bus_addr, uint16_t spd_reg_id, uint32_t xfer_block_size)
{
    unsigned status = COM_OK;
    bool enable_input;       // enable/disable input FIFO
    bool enable_output;      // enable/disable output FIFO
    uint32_t out_fifosize;
    uint32_t write_overhead;
    uint32_t write_len;
    // buffer holding 32-bit data to be written to the out-FIFO
    uint32_t msgbuf[SPD_SMBUS_MSGBUF_SIZE];
    // same data in bytes
    uint8_t *msgbuf_bytes = (uint8_t *)msgbuf;
    uint32_t msgword_ix;    // index in the 32-bit data buffer
    uint32_t msgbyte_ix, i;




    if (qup_base == QUP0_QUP_BASE_ADDRESS)
    {
        out_fifosize = qup0_out_fifo_size;
//        out_blocksize = qup0_out_blk_size;
    }
    else
    {
        out_fifosize = qup1_out_fifo_size;
    }

    enable_input = 0;
    enable_output = 1;


    spd_smbus_init_xfer(qup_base, enable_input, enable_output);
    write_overhead = 4;
//    read_overhead = 0;
    write_len = SPD_DATA_ADDR_LEN + write_overhead;

    // Select the transfer mode for the output(write) FIFOs.
    // The transfer mode (FIFO Mode or Block Mode) is based on the transfer size vs FIFO size.
    // Data from output FIFO to be unpacked before passing to the mini-core.
    // For out-FIFO
    spd_smbus_set_write_mode(qup_base, write_len, out_fifosize);
    // Go to the RUN state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);

    // Enable the clock
    spd_smbus_enable_i2c_clk(qup_base);

    // Go to the PAUSE state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_PAUSE);

     // Create the message buffer for the write/clean it.
    memset(msgbuf, 0, SPD_SMBUS_MSGBUF_SIZE*sizeof(msgbuf[0]));

    msgbyte_ix = msgword_ix = 0;
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_START;
    msgbuf_bytes[msgbyte_ix++] = spd_bus_addr | 0x0;    // it's a write
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_DATA_WRITE_N_STOP;
    msgbuf_bytes[msgbyte_ix++] = SPD_DATA_ADDR_LEN;
    msgbuf_bytes[msgbyte_ix++] = (uint8_t)spd_reg_id;

    msgword_ix = (msgbyte_ix + 1)/2;
    for (i = 0; i <= (msgword_ix - 1)/2; i++)
    {
        write32(qup_base + QUP_OUTPUT_FIFO_BASE_OFFSET, msgbuf[i]);  // write to QUP_OUTPUT_FIFOc; consecutive writes fill up the out FIFO
    }
    // To run state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);


    // Determine the DIMM presence
    if (xfer_block_size == 1)
    {
        status = spd_detect_dimm(qup_base);
        if (status == COM_ERROR)
        {
//            monaco_log(INFORMATIONAL, " at addr: %lX SLOT_UNPOPULATED\n", spd_bus_addr);

            // for 1 byte transactions any type of error is COM_ERROR
            return status;
        }
//        monaco_log(INFORMATIONAL, " At addr: %X SLOT_POPULATED\n", spd_bus_addr);
    }

    // Check for QUP/mini-core errors.
    status = spd_smbus_check_errors(qup_base);
    if(status == COM_ERROR)
    {
        return status;
    }

    // Clear the output service flag: SW sets flag to 1 to acknowledge the data
    write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_OUT_SERVICE_FLAG << 8));

    // Wait until all data are gone from out_FIFO and clk is idle
    spd_smbus_wait_clk_n_data(qup_base);

    // Wait until the bus is idle
    spd_smbus_wait_bus_idle(qup_base);

    // Go to the RESET state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RESET);


    return status;

}


/*!****************************************************************************
*
* @par Description:
*   This function reads the data from the device.
*
*
*                                  @param
*    qup_base           Base address of the QUP subsystem holding the data to be
*                        retrieved
*                                  @param
*    spd_bus_addr       Bus address of the device whose SPD information is
*                        to be retrieved.
*                                  @param
*    xfer_block_size    Size of the block of SPD information to retrieve.
*                                  @param
*    dst_buff_addr      Void pointer to the address of the buffer to receive the SPD
*                        information.
*
* @return
*    An indication of the level of success.
*
* @author
*    cbucsan
*
* @par Notes:
*    The offset of the info in the device was specified in the write sequence
*     that preceded this read sequence.
*
******************************************************************************/
unsigned spd_smbus_dimm_block_read
(uint64_t qup_base, uint8_t spd_bus_addr, uint32_t xfer_block_size, void * dst_buff_addr)
{
    unsigned status = COM_OK;
    bool enable_input;       // enable/disable input FIFO
    bool enable_output;      // enable/disable output FIFO
    uint32_t in_blocksize, in_fifosize, out_fifosize;
    uint32_t read_overhead;  // (in-FIFO) num of bytes other than the bytes to be
                             //   read out of slave i.e. control tag and byte count
    uint32_t write_overhead;
    uint32_t write_len, read_len;
    bool in_fifo_mode;
    // buffer holding 32-bit data to be written to the out-FIFO
    uint32_t msgbuf[SPD_SMBUS_MSGBUF_SIZE];
    // same data in bytes
    uint8_t *msgbuf_bytes = (uint8_t *)msgbuf;

    // buffer to hold the data read from slave present in the in-FIFO
    uint32_t databuf[SPD_SMBUS_MAX_DATABUF_SIZE];
    uint32_t msgword_ix;    // index in the 32-bit data buffer
    uint32_t msgbyte_ix;
    uint32_t i,j;
    uint32_t val;


    uint8_t *byte_ptr = dst_buff_addr;   // for byte read


    if (qup_base == QUP0_QUP_BASE_ADDRESS)
    {

        in_fifosize = qup0_in_fifo_size;
        in_blocksize = qup0_in_blk_size;
        out_fifosize = qup0_out_fifo_size;
    }
    else  // qup_base == QUP1_QUP_BASE_ADDRESS
    {

        in_fifosize = qup1_in_fifo_size;
        in_blocksize = qup1_in_blk_size;
        out_fifosize = qup1_out_fifo_size;
    }

    enable_input = 1;       // enable input FIFO
    enable_output = 1;

    spd_smbus_init_xfer(qup_base, enable_input, enable_output);
    write_overhead = 4;
    write_len = write_overhead;
    read_overhead = 2;
    read_len = read_overhead + xfer_block_size; // length of the read data

    spd_smbus_set_write_mode(qup_base, write_len, out_fifosize);
    in_fifo_mode = spd_smbus_set_read_mode(qup_base, read_len, in_fifosize);

    // Go to the RUN state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);

    // Enable the clock
    spd_smbus_enable_i2c_clk(qup_base);

    // Go to the PAUSE state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_PAUSE);

    // Create the message buffer for the write.
    memset(msgbuf, 0, SPD_SMBUS_MSGBUF_SIZE*sizeof(msgbuf[0]));
    memset(databuf, 0, SPD_SMBUS_MAX_DATABUF_SIZE*sizeof(databuf[0]));

    msgbyte_ix = msgword_ix = 0;

    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_START;
    msgbuf_bytes[msgbyte_ix++] = spd_bus_addr | 0x01;
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_DATA_READ_N_STOP;
    msgbuf_bytes[msgbyte_ix++] = xfer_block_size;

    msgword_ix = (msgbyte_ix+1)/2;

    for (i = 0; i <= (msgword_ix - 1)/2; i++)
    {
        write32(qup_base + QUP_OUTPUT_FIFO_BASE_OFFSET, msgbuf[i]);  // write to QUP_OUTPUT_FIFOc; consecutive writes fill up the out FIFO
    }

    // To run state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);

    // Wait for the output service flag. If the flag is set to 1 by HW -> out FIFO has an
    //  outstanding out service request and qup_irq is asserted.
    while (!(read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_OUT_SERVICE_FLAG << 8)))
                ;

    // Clear the output service flag: SW sets flag to 1 to acknowledge the data
    write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_OUT_SERVICE_FLAG << 8));


    // Switch by read mode
    if (in_fifo_mode) // FIFO mode
    {
        // Wait for the input service flag i.e. for the read from slave to complete. If flag is set
        //  to 1 by HW -> input FIFO has an outstanding in service request and qup_irq is asserted.
        while (!(read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_IN_SERVICE_FLAG << 9)))
                ;

        // Empty the input FIFO into the data buffer. First read in the QUP Operational reg to see if the
        //  in-FIFO not empty bit is set
        i = 0;
        while ((read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_IN_FIFO_NOT_EMPTY << 5)) && (i < SPD_SMBUS_MAX_DATABUF_SIZE))
        {
            databuf[i] = read32(qup_base + QUP_INPUT_FIFO_BASE_OFFSET);
            i++;
            DELAY(1);
        }

        // Check for QUP/mini-core errors
        status = spd_smbus_check_errors(qup_base);
        if(status == COM_ERROR)
        {
            return status;
        }

        // Clear the in FIFO service operational flag. A 1 written to this also acknowledges SW has or will
        //  read the data
        write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_IN_SERVICE_FLAG << 9));
    }
    else   // Block mode
    {
        // Read in a loop until the read_len byte block is read and databuffer size is not exceeded.
        // Note: the data buffer won't be exceeded because we've already ensured that
        //  the block to read < 256 bytes (i.e. SPD_SMBUS_MAX_FIFO_BLOCK_SIZE)
        i = 0;
        do
        {
            // Wait for block i.e. for either the in-service flag (req to service) or max input done flag (all completed)
            //  to be set before starting the read.
            // QUP_OPER_MAX_IN_DONE_FLAG is set when in-FIFO has reached the MX_INPUT_COUNT that had been set to the size
            //  of the entire block to be read out from slave.
            while (!(read32(qup_base + QUP_OPERATIONAL_OFFSET) & ((QUP_OPER_IN_SERVICE_FLAG << 9) | (QUP_OPER_MAX_IN_DONE_FLAG << 11))))
                        ;

            // Check for QUP/mini-core errors.
            status = spd_smbus_check_errors(qup_base);
            if(status == COM_ERROR)
            {
                return status;
            }

            // Clear the in FIFO service operational flag. A 1 written to this also acknowledges SW has or will
            //  read the data.
             write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_IN_SERVICE_FLAG << 9));

            // Fill the data buffer from in-FIFO.
            // Note that in Block mode the the in-service flag is asserted after an in_blocksize chunk is read.
            j = 0;
            while ((j++ < in_blocksize/4) &&
                       (read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_IN_FIFO_NOT_EMPTY << 5)) && (i * 4 < read_len))
            {
                // Copy to the data buffer the contents of the in-FIFO
                databuf[i] = read32(qup_base + QUP_INPUT_FIFO_BASE_OFFSET);
                i++;
            }

        } while ((i * 4 < read_len) && (i < SPD_SMBUS_MAX_DATABUF_SIZE));

    }  // end of Block mode read


    if ((databuf[0] & 0xff) != QUP_TAG2_DATA_READ_N_STOP)
    {
        monaco_log(INFORMATIONAL, "Unexpected value in input FIFO after read %08x\n", i);
    }
    if ((((databuf[0] >> 8) & 0xff) != xfer_block_size) && (xfer_block_size != 0x100))
    {
        monaco_log(INFORMATIONAL, "Unexpected size reported in input FIFO after read %d\n", i);
    }
    if (i != (((xfer_block_size+read_overhead)+3)/4))
    {
        monaco_log(INFORMATIONAL, "Incorrect bytes read %d\n", i*4);
    }


    // Wait until all data are gone from out_FIFO and clk is idle
    spd_smbus_wait_clk_n_data(qup_base);

    // Wait until the bus is idle
    spd_smbus_wait_bus_idle(qup_base);

    // Go to the RESET state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RESET);

    // Prepare the data from current databuf (fifo data) for the final destination:
    //  reverse the byte order within each 32 bit word

    for ( i = 0; i < (read_len + 1)/4; i++)
    {
        val = ((databuf[i] & 0xFFFF0000) >> 16) | ((databuf[i + 1] & 0x0000FFFF) << 16);
        databuf[i] = val;
    }

    // Zero out the destination buffer
//    memset(dest, 0, ((xfer_block_size+3)/4)*sizeof(dest[0]));


    // Fill the destination buffer
    if (read_len == 3)  // byte read
    {

        *byte_ptr = (uint8_t)databuf[0];
//        monaco_log(INFORMATIONAL, "Device type is: %x \n", *byte_ptr);

    }
    else  // block (nbytes)
    {
        for (i = 0; i < (read_len + 1); i = i + 4)
        {
            *(byte_ptr + i)      = (databuf[i/4] & 0x000000FF);
            *(byte_ptr + i + 1)  = (databuf[i/4] & 0x0000FF00) >> 8;
            *(byte_ptr + i + 2)  = (databuf[i/4] & 0x00FF0000) >> 16;
            *(byte_ptr + i + 3)  = (databuf[i/4] & 0xFF000000) >> 24;

        }
    }


    return status;
}

#endif


/*!****************************************************************************
*
* @par Description:
*    This function writes a 8-bit byte to the SMBus device (e.g. EEPROM)
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be retrieved.
*                                  @param
*    spd_reg_id       The SPD register id of the start of the information to
*                      be written.
*                                  @param
*    spd_data         The SPD data to be stored.
*
* @return
*    Status indicating if the data could be written to the slave device.
*
* @author
*    lchavani
*
* @par Notes:
*
*
******************************************************************************/
unsigned spd_smbus_dimm_set_byte
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint32_t spd_reg_id,
    uint8_t spd_data
)
{

    unsigned status = COM_OK;


    status = spd_smbus_dimm_set_block(smbus_id, spd_bus_addr, 0, spd_reg_id, &spd_data, 1);

    return status;
}


/*!****************************************************************************
*
* @par Description:
*    This function writes a 16-bit byte to the SMBus device (e.g. EEPROM)
*
*                                  @param
*    smbus_id         The SMBus ID where the information is located.
*                                  @param
*    spd_bus_addr     The SMBus address of the information to be retrieved.
*                                  @param
*    spd_reg_id       The SPD register id of the start of the information to
*                      be written.
*                                  @param
*    spd_data         The SPD data to be stored.
*
* @return
*    Status indicating if the data could be written to the slave device.
*
* @author
*    lchavani
*
* @par Notes:
*
*
******************************************************************************/
unsigned spd_smbus_dimm_set_word
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint32_t spd_reg_id,
    uint16_t spd_data
)
{
    unsigned status = COM_OK;
    uint8_t data_arr[2];

    data_arr[0] = (spd_data >> BITS_PER_BYTE) & 0xFF;
    data_arr[1] = spd_data & 0xFF;;


    status = spd_smbus_dimm_set_block(smbus_id, spd_bus_addr, 0, spd_reg_id, &data_arr, 2);

    return status;
}


/*!****************************************************************************
*
* @par Description:
*   This function writes a block of SPD data to the slave starting at the given
*     offset
*
*                                  @param
*    smbus_id           SMBus ID where the SPD information is located.
*                                  @param
*    spd_bus_addr       SMBus address of the device whose SPD information is
*                        to be retrieved.
*                                  @param
*    spd_bank_num       DDR4: the SPD info is placed in 2 x 256B banks to be switched
*                        between. DDR3: there are no banks but one 256B info
*                        chunk (this param is set to 0 by default).
*                                  @param
*    spd_reg_id         SMBus register id of the start of the block of SPD
*                        information to be written.
*                                  @param
*    in_buffer          Void pointer to the address of the buffer where the data to
*                        be written is stored.
*                                  @param
*    buffer_size        Size of the data to be written to the slave device.
*
*
* @return
*    An indication of the level of success.
*
* @author
*    lchavani
*
* @par Notes:
*
******************************************************************************/
unsigned spd_smbus_dimm_set_block
(
    uint8_t smbus_id,
    uint8_t spd_bus_addr,
    uint8_t spd_bank_num,
    uint16_t spd_reg_id,
    void* in_buffer,
    size_t buffer_size
)

{
    unsigned status = COM_OK;
    uint64_t qup_base;
    uint32_t out_fifosize;   // size of the implemented out-FIFO (dictated by RTL generic)
    bool enable_input;       // enable/disable input FIFO
    bool enable_output;      // enable/disable output FIFO
    uint32_t write_overhead;
    uint32_t write_len;
    uint32_t msgbuf[SPD_SMBUS_MSGBUF_SIZE];
    // same data in bytes
    uint8_t *msgbuf_bytes = (uint8_t *)msgbuf;
    uint32_t msgword_ix;    // index in the 32-bit data buffer
    uint32_t msgbyte_ix, i;
    uint8_t buff_size_cnt;
    uint8_t wr_loop_cnt;
    uint8_t wr_done;

    if(in_buffer == NULL)
    {
        status = COM_ERROR;
        return status;
    }

    uint8_t *byte_wr_ptr = in_buffer;   // assign the void ptr for byte write

    if (buffer_size > SPD_SMBUS_MAX_DATABUF_SIZE_BYTES)
    {
        buffer_size = SPD_SMBUS_MAX_DATABUF_SIZE_BYTES;
    }

    // Determine the out-fifo size - this is based on a RTL (HW) setting as read from a reg
    if (smbus_id == 0)
    {
        qup_base = QUP0_QUP_BASE_ADDRESS;
        out_fifosize = qup0_out_fifo_size;
    }
    else if (smbus_id == 1)
    {
        qup_base = QUP1_QUP_BASE_ADDRESS;
        out_fifosize = qup1_out_fifo_size;

    }
    else
    {
        monaco_log(INFORMATIONAL, "Invalid QUP subsystem!");
        status = COM_ERROR;
        return status;
    }

    // Select the device bank 1 if necessary
    if (spd_bank_num == 1)
    {
        status = spd_switch_bank(qup_base, 1, out_fifosize);

        if (status == COM_ERROR)
        {
          return status;
        }
    }

    enable_input = 0;
    enable_output = 1;

    spd_smbus_init_xfer(qup_base, enable_input, enable_output);
    write_overhead = 4;
    write_len = SPD_DATA_ADDR_LEN + buffer_size + write_overhead;

    // Select the transfer mode for the output(write) FIFOs.
    // The transfer mode (FIFO Mode or Block Mode) is based on the transfer size vs FIFO size.
    // Data from output FIFO to be unpacked before passing to the mini-core.
    // For out-FIFO
    spd_smbus_set_write_mode(qup_base, write_len, out_fifosize);
    // Go to the RUN state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);

    // Enable the clock
    spd_smbus_enable_i2c_clk(qup_base);

    // Go to the PAUSE state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_PAUSE);

     // Create the message buffer for the write/clean it.
    memset(msgbuf, 0, SPD_SMBUS_MSGBUF_SIZE*sizeof(msgbuf[0]));

    msgbyte_ix = msgword_ix = 0;
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_START;
    msgbuf_bytes[msgbyte_ix++] = spd_bus_addr | 0x0;    // it's a write
    msgbuf_bytes[msgbyte_ix++] = QUP_TAG2_DATA_WRITE_N_STOP;
    msgbuf_bytes[msgbyte_ix++] = SPD_DATA_ADDR_LEN + buffer_size;
    msgbuf_bytes[msgbyte_ix++] = (uint8_t)spd_reg_id;

    for (buff_size_cnt = 0; buff_size_cnt < buffer_size; buff_size_cnt++)
    {
        msgbuf_bytes[msgbyte_ix++] = (uint8_t)*byte_wr_ptr++;
    }

    msgword_ix = (msgbyte_ix + 1)/2;
    for (i = 0; i <= (msgword_ix - 1)/2; i++)
    {
        write32(qup_base + QUP_OUTPUT_FIFO_BASE_OFFSET, msgbuf[i]);  // write to QUP_OUTPUT_FIFOc; consecutive writes fill up the out FIFO
    }
    // To run state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);

    // Wait for the output FIFO to empty. If the flag is set to 1 by HW -> out FIFO has at
    //  least one outstanding value to be shifted out.
    wr_loop_cnt = 60;
    wr_done = 0;

    while ((wr_loop_cnt != 0) && (wr_done == 0))
    {
        if (read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_OUT_FIFO_NOT_EMPTY << QUP_OPER_OUT_FIFO_NOT_EMPTY__S))
        {
            wr_done = 1;
        }
        else
        {
            // Check for QUP/mini-core errors
            status = spd_smbus_check_errors(qup_base);
            if(status == COM_ERROR)
            {
                wr_loop_cnt = 1;
            }
        }
        wr_loop_cnt--;
    }

    if (wr_done == 0)
    {
        status = COM_ERROR;
        return status;
    }

    // Clear the output service flag: SW sets flag to 1 to acknowledge the data
    write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_OUT_SERVICE_FLAG << QUP_OPER_OUT_SERVICE_FLAG__S));

    // Wait until all data are gone from out_FIFO and clk is idle
    spd_smbus_wait_clk_n_data(qup_base);

    // Wait until the bus is idle
    spd_smbus_wait_bus_idle(qup_base);

    // Go to the RESET state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RESET);


    // Always back to the default i.e. to device bank 0
    if (spd_bank_num == 1)
    {
        status = spd_switch_bank(qup_base, 0, out_fifosize);
    }

    return status;

}



/*!****************************************************************************
*
* @par Description:
*   Based on the transfer size determine the transfer mode for the write: FIFO
*    or Block (> FIFO size)
*
*
*                                  @param
*    qup_base           Base address of the QUP subsystem holding the data to be
*                        retrieved
*                                  @param
*    read_len           The size (num of bytes) of current transfer
*
*                                  @param
*    out_fifosize       The FIFO (out_FIFO) size
*
*
*
* @return
*    Either fifo or block mode (i.e., not fifo mode)
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
// Determine the write mode for out-FIFO based on the transfer size: is it FIFO mode or Block mode?
// No need to use the QUP_RECONFIG_DURING_RUN
bool spd_smbus_set_write_mode(uint64_t qup_base, uint32_t write_len, uint32_t out_fifosize)
{
    bool is_fifo_mode = true;

    uint32_t repack_en_val;


    repack_en_val = (QUP_IO_MODES_PACK_EN << 15)|(QUP_IO_MODES_UNPACK_EN << 14);
    // Data from the mini-core will be packed before placing in input FIFO.
    // Data from output FIFO to be unpacked before passing to the mini-core.
    if (write_len  <= out_fifosize)  // FIFO mode
    {
        // use repacking
        write32(qup_base + QUP_IO_MODES_OFFSET, repack_en_val);
        write32(qup_base + QUP_MX_WRITE_COUNT_OFFSET, write_len);
        is_fifo_mode = true;

    }
    else   // BLOCK mode
    {

        write32((qup_base + QUP_IO_MODES_OFFSET), ((QUP_IO_MODES_OUTPUT_MODE_BLOCK << 10)| repack_en_val));
        write32(qup_base + QUP_MX_OUTPUT_COUNT_OFFSET, write_len);
        is_fifo_mode = false;

    }

    return is_fifo_mode;
}


/*!****************************************************************************
*
* @par Description:
*   Based on the transfer size determine the transfer mode for the read: FIFO
*    or Block (> FIFO size)
*
*
*                                  @param
*    qup_base           Base address of the QUP subsystem holding the data to be
*                        retrieved
*                                  @param
*    read_len           The size (num of bytes) of current transfer
*
*                                  @param
*    in_fifosize       The FIFO (in-FIFO) size
*
*
*
* @return
*    Either fifo or block mode (i.e., not fifo mode)
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
bool spd_smbus_set_read_mode(uint64_t qup_base, uint32_t read_len, uint32_t in_fifosize)
{
    bool is_fifo_mode = true;
// CB: Do we need to use reconfig?!
//    uint32_t reconfig = read_len & QUP_RECONFIG_DURING_RUN;

//    len &= ~QUP_RECONFIG_DURING_RUN;
//    len = (len > QUP_READ_LIMIT) ? QUP_READ_LIMIT : len;  // CB: done previously

    if (read_len <= in_fifosize)
    {
        // FIFO mode
         // use repacking
        write32(qup_base + QUP_IO_MODES_OFFSET, (QUP_IO_MODES_PACK_EN << 15)|(QUP_IO_MODES_UNPACK_EN << 14));
//        write32(QUP_BASE + QUP_MX_READ_CNT, len | reconfig);
        write32(qup_base + QUP_MX_READ_COUNT_OFFSET, read_len);
        is_fifo_mode = true;
    }
    else
    {
        // BLOCK mode
        write32(qup_base + QUP_IO_MODES_OFFSET, (QUP_IO_MODES_INPUT_MODE_BLOCK << 12)|(QUP_IO_MODES_PACK_EN << 15)|(QUP_IO_MODES_UNPACK_EN << 14));
//        write32(QUP_BASE + QUP_MX_INPUT_CNT, len | reconfig);
        write32(qup_base + QUP_MX_INPUT_COUNT_OFFSET, read_len);
        is_fifo_mode = false;
    }
    return is_fifo_mode;
}



/*!****************************************************************************
*
* @par Description:
*   Initialize the transfer: configure the QUP and the mini-core (e.g. I2C, SMBus)
*
*
*                                  @param
*    qup_base           Base address of the QUP subsystem holding the data to be
*                        retrieved
*                                  @param
*    enable_input       Enable (or not) the input FIFO
*
*                                  @param
*    enable_output      Enable (or not) the output FIFO
*
*
*
* @return
*    nothing
*
* @author
*    cbucsan
*
* @par Notes:
*    In reset state either the input or output FIFO must be cleared.
*    In/Out FIFOs may not be both disabled (i.e., NO_INPUT/NO_OUTPUT
*     be set to 1 at the same time, see last note below).
*    If a FIFO is disabled then the corresponding service interrupt
*     and service flag are never set.
*    If the mini-core (e.g. I2C) is enabled the output FIFO
*     should be enabled.
*    If &enable_input (or &enable_out) is set then the NO_INPUT(or OUTPUT bit)
*     gets cleared which enables the input(or output) FIFO.
*
*
******************************************************************************/
void spd_smbus_init_xfer(uint64_t qup_base, bool enable_input, bool enable_output)
{
    uint32_t config_val;

    spd_smbus_set_qup_state(qup_base, QUP_STATE_RESET);

    // Reset the QUP_CONFIG reg
    write32(qup_base + QUP_CONFIG_OFFSET, 0);

    // Reset the QUP_OPERATIONAL reg; write 0x00000ff0 to the reg
    write32(qup_base + QUP_OPERATIONAL_OFFSET, QUP_OPER_RESET_VAL);

    // Enable input/output error generation
    // QUP_ERROR_FLAGS and QUP_ERROR_FLAGS_EN. val is 0x7C, should it be 0x0000003C?!
    write32(qup_base + QUP_ERROR_FLAGS_EN_OFFSET, QUP_STATUS_ERROR_FLAGS_VAL);

    // Now that we are in Reset state, configure QUP
    // CB TODO: should I replace I2C_MINI_CORE master with SMBus master (0x3)?
    // if QUP_CONFIG_NO_INPUT is 1 -> disable in-FIFO and in-FIFO is always empty
    // if QUP_CONFIG_NO_OUTPUT is 1 -> disable out-FIFO
    config_val = (QUP_CONFIG_MINI_CORE_I2C_MASTER << 8)|QUP_CONFIG_N|(enable_input ? 0 : (QUP_CONFIG_NO_INPUT << 7))|(enable_output ? 0 : (QUP_CONFIG_NO_OUTPUT << 6));
    write32(qup_base + QUP_CONFIG_OFFSET, config_val);

    // Enable version 2 of the mini-core, bit[0]; legacy behavior for clk ctrl, SDA fall/rise, noise reject
    write32(qup_base + I2C_MASTER_CONFIG_OFFSET, I2C_MASTER_CONFIG_EN_VERS_TWO_TAG);


    spd_smbus_disable_i2c_clk(qup_base);

    // Clear the I2C master status bits: write 0x00fffffc. Writing any value clear the status bits.
    write32(qup_base + I2C_MASTER_STATUS_OFFSET, I2C_MASTER_STATUS_RESET_VAL);

    // Ensure the QUP state is valid and the RTL generic setting for the I2C master is set to 1
    // CB: TODO: if using SMBUS master check for QUP_STATE_SMBUS_MAST_GEN to be 1
    while ((read32(qup_base + QUP_STATE_OFFSET) & ((QUP_STATE_VALID << 2) | (QUP_STATE_I2C_MAST_GEN << QUP_STATE_I2C_MAST_GEN__S))) !=
                ((QUP_STATE_VALID << 2) | (QUP_STATE_I2C_MAST_GEN << QUP_STATE_I2C_MAST_GEN__S)))
                ;
}



/*!****************************************************************************
*
* @par Description:
*    This function enables the I2C clock.
*
*                                  @param
*    qup_base       The base address of the QUP to be initialized
*
* @return
*    nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_enable_i2c_clk(uint64_t qup_base)
{
    write32(qup_base + I2C_MASTER_CLK_CTL_OFFSET, I2C_CLK_VAL);
}



/*!****************************************************************************
*
* @par Description:
*    This function disables the I2C clock.
*
*                                  @param
*    qup_base       The base address of the QUP to be initialized
*
* @return
*    nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_disable_i2c_clk(uint64_t qup_base)
{
    write32(qup_base + I2C_MASTER_CLK_CTL_OFFSET, 0);
}



/*!****************************************************************************
*
* @par Description:
*    Check for QUP and mini-core errors after FIFO read.
*
*                                  @param
*    qup_base       The base address of the QUP to be initialized
*
* @return
*    Status: &SPD_OK or &SPD_ERROR
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
unsigned spd_smbus_check_errors(uint64_t qup_base)
{
    unsigned status = COM_OK;

    if (read32(qup_base + I2C_MASTER_STATUS_OFFSET) & I2C_MASTER_STATUS_BUS_ERROR_VAL)
    {
        monaco_log(INFORMATIONAL, "Bus error\n");
        status = COM_ERROR;
    }

    if (read32(qup_base + QUP_ERROR_FLAGS_OFFSET) & QUP_STATUS_ERROR_FLAGS_VAL)
    {
        monaco_log(INFORMATIONAL, "QUP error\n");  // in/out-FIFO under/over run errors
        status = COM_ERROR;
    }

    return status;
}



/*!****************************************************************************
*
* @par Description:
*    Wait for the data to be shifted out of out-FIFO and the
*     clock to become idle or forced low.
*
*                                  @param
*    qup_base       The base address of the QUP to be initialized
*
* @return
*    nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_wait_clk_n_data(uint64_t qup_base)
{
    uint32_t have_data, clk_state;

    do // for as long as the out-FIFO has data to be shifted out and the clock is not idle or forced low
    {
        // Check on clk state
        clk_state = read32(qup_base + I2C_MASTER_STATUS_OFFSET);
        clk_state = (clk_state >> I2C_MASTER_STATUS_CLK_STATE__S) & I2C_MASTER_STATUS_CLK_STATE__M;
        // Check on the out data
        have_data = read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_OUT_FIFO_NOT_EMPTY << 4);

    } while (have_data || ((clk_state != I2C_MASTER_STATUS_CLK_STATE_RESET_BUSIDLE) &&
                                (clk_state != I2C_MASTER_STATUS_CLK_STATE_FORCED_LOW)));

}



/*!****************************************************************************
*
* @par Description:
*    Wait for the bus to become inactive.
*
*
*                                  @param
*    qup_base       The base address of the QUP to be initialized
*
* @return
*    nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/

void spd_smbus_wait_bus_idle(uint64_t qup_base)
{
    // BUS_ACTIVE, bit[8], is set when the bus is in use by any controller.
    while (read32(qup_base + I2C_MASTER_STATUS_OFFSET) & (I2C_MASTER_STATUS_BUS_ACTIVE << 8))
                ;
}



/*!****************************************************************************
* @par Description:
*    This function gets the sizes of the input/output block and FIFO for QUP0/1
*
*
*                                  @param
*    qup_base           Base Address of the QUP0 or QUP1 subsystem
*
*
* @return
*    Nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_get_in_out_sizes(uint64_t qup_base)
{
    uint8_t gen_blkbits;  // Output block size value set by RTL
    uint8_t gen_fifobits; // Output FIFO size value set by RTL
    uint32_t blksize, fifosize;

    // Input sizes
    gen_blkbits = (read32(qup_base + QUP_IO_MODES_OFFSET) & (QUP_IO_MODES_BLOCK_SIZE__M << 5)) >> 5;
    gen_fifobits = (read32(qup_base + QUP_IO_MODES_OFFSET) & (QUP_IO_MODES_FIFO_SIZE__M << 7)) >> 7;
    // Determine the sizes in bytes
    spd_smbus_calc_blk_fifo_sizes(gen_blkbits, gen_fifobits, &blksize, &fifosize);
    if(qup_base == QUP0_QUP_BASE_ADDRESS)
    {
        qup0_in_blk_size = blksize;
        qup0_in_fifo_size = fifosize;
    }
    else if(qup_base == QUP1_QUP_BASE_ADDRESS)
    {
        qup1_in_blk_size = blksize;
        qup1_in_fifo_size = fifosize;
    }

    monaco_log(INFORMATIONAL, "QUP %d In block size: %d B, in-FIFO size: %d B\n", (qup_base == QUP0_QUP_BASE_ADDRESS ? 0 : 1), blksize, fifosize);


    // Output sizes
    gen_blkbits = (read32(qup_base + QUP_IO_MODES_OFFSET) & (QUP_IO_MODES_BLOCK_SIZE__M << 0)) >> 0;
    gen_fifobits = (read32(qup_base + QUP_IO_MODES_OFFSET) & (QUP_IO_MODES_FIFO_SIZE__M << 2)) >> 2;

    // Calculate the block/FIFO sizes based on the bit values
    spd_smbus_calc_blk_fifo_sizes(gen_blkbits, gen_fifobits, &blksize, &fifosize);

    if(qup_base == QUP0_QUP_BASE_ADDRESS)
    {
        qup0_out_blk_size = blksize;
        qup0_out_fifo_size = fifosize;
    }
    else if(qup_base == QUP1_QUP_BASE_ADDRESS)
    {
        qup1_out_blk_size = blksize;
        qup1_out_fifo_size = fifosize;
    }

    monaco_log(INFORMATIONAL, "QUP%d Out block size: %d B, out-FIFO size: %d B\n", (qup_base==QUP0_QUP_BASE_ADDRESS ? 0 : 1), blksize, fifosize);

}


/*!****************************************************************************
*
* @par Description:
*    This helper function determines the block and FIFO sizes from the
*       bit values read from the QUP IO MODES register
*
*                                  @param
*    blkbits       Bit value for the block size associated with Block mode (I/O)
*                                  @param
*    fifobits      Bit value for the FIFO size (I/O)
*                                  @param
*    blksize       The deref value of this ptr holds the calculated block size
*                      from the bit value *_BLOCK_SIZE of the IO_MODES reg
*                                  @param
*    fifosize      The deref value of this ptr holds the FIFO size calculated
*                      from the bit value *_FIFO_SIZE of the IO_MODES reg
*
* @return
*    Nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
******************************************************************************/
void spd_smbus_calc_blk_fifo_sizes
(uint8_t blkbits, uint8_t fifobits, uint32_t *blksize, uint32_t *fifosize)
{
    switch (blkbits)  // bit field of IO MODES reg
    {
        case 0 :
                *blksize = 4;   // FIFO_Mode only
                break;
        case 1 :
                *blksize = 16;
                break;
        case 2 :
                *blksize = 32;
                break;
        default :
                monaco_log(INFORMATIONAL, "Error: Invalid block size\n");

    }

    switch (fifobits) // bit field of IO MODES reg
    {
        case 0 :
                *fifosize = 2 * *blksize;
                break;
        case 1 :
                *fifosize = 4 * *blksize;
                break;
        case 2 :
                *fifosize = 8 * *blksize;
                break;
        case 3 :
                *fifosize = 16 * *blksize;
                break;
        default :
                monaco_log(INFORMATIONAL, "Error: Invalid FIFO size\n");
    }

}



/*!****************************************************************************
* @par Description:
*    Reset QUP and mini-cores.
*
*
*                                  @param
*    qup_base           Base Address of the QUP0 or QUP1 subsystem
*
*
* @return
*    Nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_reset_qup(uint64_t qup_base)
{
    write32(qup_base + QUP_SW_RESET_OFFSET, 1);

    spd_smbus_wait_valid_state(qup_base);
}



/*!****************************************************************************
* @par Description:
*    Set the QUP state (i.e. reset, run or pause).
*
*
*                                  @param
*    qup_base           Base Address of the QUP0 or QUP1 subsystem.
*
*                                  @param
*    state             The QUP state to be transitioned to.
*
* @return
*    Nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
// Set the QUP state
void spd_smbus_set_qup_state(uint64_t qup_base, qup_state_t state)
{
    // Make sure we're in a valid state first
        while (!(read32(qup_base + QUP_STATE_OFFSET) & (QUP_STATE_VALID << 2)))
                ;

        state = state & QUP_STATE__M;
        write32(qup_base + QUP_STATE_OFFSET, state);

        // Wait till it takes
        while ((read32(qup_base + QUP_STATE_OFFSET) & ((QUP_STATE_VALID << 2) | QUP_STATE__M)) !=
                ((QUP_STATE_VALID << 2) | state))
                ;
}



/*!****************************************************************************
* @par Description:
*    Ensure QUP is in a valid state.
*
*
*                                  @param
*    qup_base           Base Address of the QUP0 or QUP1 subsystem
*
*
* @return
*    Nothing
*
* @author
*    cbucsan
*
* @par Notes:
*
*
******************************************************************************/
void spd_smbus_wait_valid_state(uint64_t qup_base)
{
    // Poll QUP_STATE[STATE_VALID] until asserted
    while (!(read32(qup_base + QUP_STATE_OFFSET) & (QUP_STATE_VALID << QUP_STATE_VALID__S)))
        ;

}


/*!****************************************************************************
* @par Description:
*    Determine whether the DIMM slot is populated.
*
*                                  @param
*    qup_base           Base Address of the QUP0 or QUP1 subsystem.
*
*
* @return
*    Status i.e., detection successful (COM_OK) or not (COM_ERROR)
*
* @author
*    cbucsan
*
* @par Notes:
*    To determine the DIMM presence check for errors after an attempt to write
*      to the device's out FIFO
*
*
******************************************************************************/
unsigned spd_detect_dimm(uint64_t qup_base)
{

    unsigned status = COM_OK;
    uint32_t detect_err;
    uint32_t reg_val;
    uint8_t max_loops = 10;
    uint8_t i = 0;

    detect_err=((I2C_MASTER_STATUS_PKT_NACKED<<3)|(I2C_MASTER_STATUS_INV_WRITE<<5)|(I2C_MASTER_STATUS_FAILURE_INFO_3<<6)|(I2C_MASTER_STATUS_CLK_STATE_NOT_MASTER<<13)|(I2C_MASTER_STATUS_INVALID_READ_ADDR<<24));

    // I2C reads sometimes errantly return 0x0 - found during SoD bringup
    do
    {
        ddr_wait_us(1000);  // 1000us

        reg_val = read32(qup_base + I2C_MASTER_STATUS_OFFSET);
        monaco_log(INFORMATIONAL, "i2c master status val: %X\n", reg_val);

        i++;
    } while((i < max_loops) && (reg_val == 0x0));


    if ((reg_val & detect_err) > 0)
    {
        status = COM_ERROR;
    }

    return status;
}



/*!****************************************************************************
* @par Description:
*     Perform a DDR DIMM EEPROM bank (0 to 1 or 1 to 0) switch using
*      the SPA (Set Page Address) mechanism.
*
*
*                                  @param
*    qup_base           Base Address of the QUP0 or QUP1 subsystem.
*
*                                  @param
*    to_bank_num        The DIMM EEPROM bank to switch to.
*
*                                  @param
*    out_fifosize       The out-FIFO size used to setup the write.
*
* @return
*    Success or fail
*
* @author
*    cbucsan
*
* @par Notes:
*    This is applicable to DDR4 only; DDR3 has one single 256B info area.
*
******************************************************************************/
unsigned spd_switch_bank(uint64_t qup_base, uint8_t to_bank_num, uint32_t out_fifosize)
{
    unsigned status = COM_OK;
    bool enable_input;       // enable/disable input FIFO
    bool enable_output;      // enable/disable output FIFO
    uint32_t write_overhead; // (out_FIFO) START tag, slave addr, control tag, byte
                             //   count i.e. num bytes excepting the register
                             //   address(offset for block to be read)
    uint32_t spa_par;        // based on which bank to switch to

    uint32_t msgbuf[2];      // holds the write command
    uint32_t i;


    enable_input = false;    // no read
    enable_output = true;     // only write
    write_overhead = 4;


    if  (to_bank_num == 1)
    {
        spa_par = 0x6E;
    }
    else
    {
        spa_par = 0x6C;
    }


    // Initialize the QUP/mini-core for the transfer; enable both in/out FIFO's
    spd_smbus_init_xfer(qup_base, enable_input, enable_output);

    // Select the transfer mode: the transfer mode (FIFO Mode or Block Mode) is based on the transfer size vs FIFO size
    spd_smbus_set_write_mode(qup_base, (write_overhead + 2), out_fifosize);

    // Zero out the msgbuf
    for (i = 0; i < 2; i++)
    {
        msgbuf[i]=0x0;

    }

    // Prepare the buffer to send the SPA command on the bus to switch between the
    //  2 memory banks; the 2 bytes 0xAA and 0xBB are "don't care" type bytes to
    //  satisfy the spec

    msgbuf[0]=QUP_TAG2_START | (spa_par<<8) | (QUP_TAG2_DATA_WRITE_N_STOP<<16) | (0x02<<24);
    msgbuf[1]=0xAA | (0xBB<<8);


    // Set state to Run state (0x1)
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);

    spd_smbus_enable_i2c_clk(qup_base);

    // Go to the PAUSE state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_PAUSE);

    // Write message to the FIFO base
    for (i = 0; i < 2; i++)
    {
        write32(qup_base + QUP_OUTPUT_FIFO_BASE_OFFSET, msgbuf[i]);  // write to QUP_OUTPUT_FIFOc; consecutive writes fill up the out FIFO
    }


    // Set state to Run state (0x1)
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RUN);

    // Wait for output FIFO to empty
//    &flag_val=&QUP_OPER_OUT_FIFO_NOT_EMPTY<<&QUP_OPER_OUT_FIFO_NOT_EMPTY__S
//    wait ((data.long(d:QUP_OPERATIONAL_REG_ADDR)&(&flag_val))...)

    // Wait for the output service flag. If the flag is set to 1 by HW -> out FIFO has an
    //  outstanding out service request and qup_irq is asserted.
    // Need to check if NACK from SPA since it could possibly be not supported
    uint32_t nack_err, op_out_svc;

    do {
        op_out_svc = read32(qup_base + QUP_OPERATIONAL_OFFSET) & (QUP_OPER_OUT_SERVICE_FLAG << 8);
        nack_err = read32(qup_base + I2C_MASTER_STATUS_OFFSET) & (I2C_MASTER_STATUS_PKT_NACKED<<3);
    } while ((op_out_svc != (QUP_OPER_OUT_SERVICE_FLAG << 8)) && (nack_err == 0));

    // if NACK due to SPA not supported, skip and just reset QUP
    if (nack_err == 0)
    {
        // Check for Bus and QUP system errors
        status = spd_smbus_check_errors(qup_base);
        if(status == COM_ERROR)
        {
            return status;
        }

        // Clear the output service flag: SW sets flag to 1 to acknowledge the data
        write32(qup_base + QUP_OPERATIONAL_OFFSET, (QUP_OPER_OUT_SERVICE_FLAG << 8));

        // Wait until all data are gone from out_FIFO and clk is idle
        spd_smbus_wait_clk_n_data(qup_base);

        // Wait until the bus is idle
        spd_smbus_wait_bus_idle(qup_base);
    }
    // Go to the RESET state
    spd_smbus_set_qup_state(qup_base, QUP_STATE_RESET);


    return status;

}

