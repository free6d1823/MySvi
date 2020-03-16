#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <target/cmdline.h>
#include <asm/mach-qdf2400/spi/spi_api.h>

#define READ_PARAMETER_CMD    0x5A
#define READ_FLASHID_CMD      0x9f
#define READ_STATUSREG_CMD    0x05
#define READ_FLAG_CMD         0x70
#define ENTER_4B_CMD          0xb7
#define READ_CMD              0x03
#define WREN_CMD              0x06
#define SECTOR_ERASE_4K_CMD   0x20
#define BLOCK_ERASE_64K_CMD   0xD8
#define PAGE_WRITE_CMD        0x2
#define CHIP_ERASE_CMD        0x60
#define DIE_ERASE_CMD         0xC4
#define REL_DP_PWR_DWN_CMD    0xAB  /* Release Deep power down mode */
#define STATUS_BUSY_MASK      0x01
#define STATUS_WR_EN_MASK     0x02


#define Micron_ID             0X20  /*SDP0      */
#define Macronix_ID           0XC2  /*SDP1 REP0*/



#define SIZE_4K  (uint32_t)(4 * 1024)
#define SIZE_64K (uint32_t)(64 * 1024)

static SPI_HANDLE spi;
static spi_config_t spi_config;
static uint8_t deviceid;

#define CMDBUF(cmdbuf, cmd, off) do { \
                cmdbuf[0] = cmd; \
                if (off != -1) { \
                cmdbuf[1] = off >> 24; \
                cmdbuf[2] = off >> 16; \
                cmdbuf[3] = off >> 8; \
                cmdbuf[4] = off; \
                } \
        } while (0)

#define TXRX(info, buf, len, count) \
        info.buf_addr = (uint32_t *)buf; \
        info.buf_len = len; \
        info.word_count = count;

int spi_transfer(SPI_HANDLE spi, spi_transfer_t *tx_info, spi_transfer_t *rx_info)
{
    if (spi_configure(spi, &spi_config, 0) != SPI_SUCCESS)
        return -1;

    if (spi_full_duplex(spi, tx_info, rx_info) != SPI_SUCCESS)
        return -1;

    return 0;
}

int spinor_transferx(SPI_HANDLE spi, uint8_t* cmdbuf, uint8_t* recbuf, uint32_t outputcount, uint32_t inputcount)
{
    spi_transfer_t tx_info, rx_info;
    TXRX(tx_info, cmdbuf, outputcount, outputcount);
    TXRX(rx_info, recbuf, inputcount, inputcount);

    if (spi_transfer(spi, &tx_info, &rx_info) != 0)
        return -1;

    return 0;
}

/*
 * Reads any register of SPI NOR flash device. read_reg_cmd is used to
 * specify which register to read.
 */
int spinor_readreg(UINT8 readreg_cmd, UINT8 *status_result)
{

    uint8_t cmdbuf[8] = {readreg_cmd};
    uint8_t recbuf[8] = {0};
    CMDBUF(cmdbuf, cmdbuf[0], -1);

    if (spinor_transferx(spi, cmdbuf, recbuf, 1, 1) != 0)
    {
        printf("read reg fail!!!\n");
        return -1;
    }
    *status_result = recbuf[0];

    return 0;
}

int spinor_wren()
{
    uint8_t cmdbuf[8] = {WREN_CMD};
    uint8_t reg_status;
    uint8_t count;
    CMDBUF(cmdbuf, cmdbuf[0], -1);

    if (spinor_transferx(spi, cmdbuf, NULL, 1, 0) != 0)
        return -1;

    for(count=0;count<5;count++)
    {
        if(spinor_readreg(READ_STATUSREG_CMD, &reg_status) != 0 || count == 4)
        {
            printf("write enable fail!!!\n");
            return -1;
        }
        if((reg_status & STATUS_WR_EN_MASK) == STATUS_WR_EN_MASK)
            break;
    }

    return 0;
}

int spinor_read_parameter()
{
    uint8_t cmdbuf[8];
    uint8_t databuf[256];
    uint8_t erase_type_index = 0;

    cmdbuf[0] = READ_PARAMETER_CMD;
    CMDBUF(cmdbuf, cmdbuf[0], 0);

    if (spinor_transferx(spi, cmdbuf, databuf, 5, 256) != 0)
    {
        printf("get spinor info fail!!!\n");
        return -1;
    }

    printf("Memory Capacity: 0X%x, %dMb\n", *((uint32_t *)(databuf + 0x34)),((uint64_t)(*((uint32_t *)(databuf + 0x34))) + 1) >> 20);
    printf("\nSupported erase cmd as follows:\n");

    for(;erase_type_index<4;erase_type_index++)
    {
        if(*(databuf + 0x4C + erase_type_index * 2) == 0)
            continue;

        printf("Erase Type %d Size:%dKB  ", erase_type_index + 1, 1 << (*(databuf + 0x4C + erase_type_index * 2) - 10));
        printf("and its cmd is 0X%x\n", *(databuf + 0x4D + erase_type_index * 2));
    }

    if(*(databuf + 0x58) != 0XFF)
        printf("\nPage Program Size:%dbytes  ",  1 << ((*(databuf + 0x58) & 0xF0) >> 4));

    printf("\n******************************\n");

    return 0;
}

int spinor_info(uint8_t *deviceid_ptr)
{
    uint8_t cmdbuf[8];
    uint8_t databuf[8];

    cmdbuf[0] = READ_FLASHID_CMD;
    CMDBUF(cmdbuf, cmdbuf[0], -1);

    if (spinor_transferx(spi, cmdbuf, databuf, 1, 3) != 0)
    {
        printf("get spinor info fail!!!\n");
        return -1;
    }

    *deviceid_ptr = *databuf;
    printf("\n**********FLASH INFO**********\n\n");
    printf("Manufacturer ID: 0X%x, ", *databuf);

    switch(deviceid)
    {
        case Macronix_ID: printf("Macronix flash\n"); break;
        case Micron_ID:   printf("Micron   flash\n"); break;
        default:          printf("unsupported flash type!\n"); return -1;
    }

    if (spinor_read_parameter()!= 0)
        return -1;

    return 0;
}

int spinor_release_powerdown()
{
    uint8_t cmdbuf[8];

    cmdbuf[0] = REL_DP_PWR_DWN_CMD;

    CMDBUF(cmdbuf, cmdbuf[0], -1);

    if (spinor_transferx(spi, cmdbuf, NULL, 1, 0) != 0)
    {
        printf("release power down fail!!!\n");
        return -1;
    }

    return 0;
}

int spinor_init()
{
    uint8_t cmdbuf[8];
    uint8_t buf[8];
    uint8_t reg_status;
    if (spi_open(SPI_INSTANCE_1, &spi) != SPI_SUCCESS)
        return -1;

    if (spi_power_on(spi) != SPI_SUCCESS)
        goto close;

    /* mode 3 */
    spi_config.clk_polarity        = SPI_CLK_IDLE_HIGH;
    spi_config.shift_mode          = SPI_INPUT_FIRST_MODE; /* SPI_INPUT_FIRST_MODE should be defined as 1 */
    spi_config.cs_polarity         = SPI_CS_ACTIVE_LOW;
    spi_config.cs_mode             = SPI_CS_KEEP_ASSERTED;
    spi_config.clk_mode            = SPI_CLK_NORMAL;
    spi_config.bits_per_word       = 8;
    spi_config.slave_index         = 0;
    spi_config.min_slave_freq_hz   = 20*1000*1000;
    spi_config.max_slave_freq_hz   = 20*1000*1000;
    spi_config.deassertion_time_ns = 0;
    spi_config.loopback_mode       = 0;
    spi_config.hs_mode             = 0;

    if(spinor_wren() != 0)
        goto close;

    cmdbuf[0] = ENTER_4B_CMD;
    CMDBUF(cmdbuf, cmdbuf[0], -1);

    if (spinor_transferx(spi, cmdbuf, NULL, 1, 0) != 0)
        goto close;

    if(spinor_info(&deviceid) != 0)
        goto close;

    if(spinor_release_powerdown() != 0)
        goto close;



    return 0;

close:
    spi_close(spi);
    spi = NULL;
    return -1;
}

int spinor_page_read(uint32_t off, void *buf)
{
    uint8_t cmdbuf[8];

    cmdbuf[0] = READ_CMD;
    CMDBUF(cmdbuf, cmdbuf[0], off);

    if (spinor_transferx(spi, cmdbuf, buf, 5, 256) != 0)
    {
        printf("page read fail!!!\n");
        return -1;
    }
    return 0;
}

int spinor_read(uint32_t address, void *buf, uint32_t size)
{
    uint32_t  startpage, endpage;
    uint32_t  pagecount;
    uint32_t  pagesize = 256;
    startpage = address / pagesize;
    endpage = (address + size) / pagesize;

    if(size % pagesize)
        endpage++;

    for (pagecount = 0; pagecount < endpage - startpage; pagecount ++)
    {
        if ( spinor_page_read(address, buf) != 0)
        {
            printf("spinor read fail!!!\n");
            return -1;
        }
        address += pagesize;
        buf += pagesize;
    }

    return 0;
}

int wait_operation_done()
{
    uint8_t reg_status;
    uint8_t count;

    while(1)
    {
        if(spinor_readreg(READ_STATUSREG_CMD, &reg_status) != 0)
            return -1;
        if((reg_status & STATUS_BUSY_MASK) == 0x0)
            break;
    }

    if(spinor_readreg(READ_FLAG_CMD, &reg_status) != 0)
        return -1;

    return 0;
}

int spinor_page_erase(uint32_t off, uint32_t pagesize)
{
    if ((pagesize != SIZE_4K) && (pagesize != SIZE_64K))
        return -1;
    if (off & (pagesize - 1))
        return -1;

    uint8_t cmdbuf[8];

    switch(pagesize)
    {
      case SIZE_4K:  cmdbuf[0] = SECTOR_ERASE_4K_CMD; break;
      case SIZE_64K: cmdbuf[0] = BLOCK_ERASE_64K_CMD; break;
    }
    CMDBUF(cmdbuf, cmdbuf[0], off);

    spinor_wren();

    if (spinor_transferx(spi, cmdbuf, NULL, 5, 0) != 0)
    {
        printf("page erase fail!!!\n");
        return -1;
    }
    wait_operation_done();

    return 0;
}

int spinor_erase(uint32_t address, uint32_t size)
{
    uint32_t  startpage, endpage;
    uint32_t  pagecount;
    uint32_t  pagesize = SIZE_4K;
    startpage = address / pagesize;
    endpage = (address + size) / pagesize;

    if(size % pagesize)
        endpage++;

    for (pagecount = 0; pagecount < endpage - startpage; pagecount ++)
    {
       if (spinor_page_erase(address, SIZE_4K) != 0)
       {
         printf("spinor erase fail!!!\n");
         return -1;
       }
       address += SIZE_4K;
    }

    return 0;
}

int spinor_chiperase()
{
    uint8_t cmdbuf[8];

    cmdbuf[0] = CHIP_ERASE_CMD;

    CMDBUF(cmdbuf, cmdbuf[0], -1);

    if (spinor_transferx(spi, cmdbuf, NULL, 1, 0) != 0)
    {
        printf("chip erase fail!!!\n");
        return -1;
    }
    wait_operation_done();

    return 0;
}

int spinor_dieerase()
{
    uint8_t cmdbuf[8];
    uint8_t die_index;

    cmdbuf[0] = DIE_ERASE_CMD;

    for(die_index = 0;die_index < 2;die_index++)
    {
         CMDBUF(cmdbuf, cmdbuf[0], (die_index * 32) << 20);

         if (spinor_transferx(spi, cmdbuf, NULL, 5, 0) != 0)
         {
             printf("die erase fail!!!\n");
             return -1;
         }
         wait_operation_done();
    }

    return 0;
}

int spinor_page_write(uint32_t off, uint8_t* src)
{
    if (off & (255))
        return -1;

    uint8_t cmdbuf[262];

    cmdbuf[0] = PAGE_WRITE_CMD;

    CMDBUF(cmdbuf, cmdbuf[0], off);
    memcpy(cmdbuf + 5, src, 256);

    spinor_wren();

    if (spinor_transferx(spi,  cmdbuf, NULL, 261, 0) != 0)
    {
        printf("page write fail!!!\n");
        return -1;
    }
    wait_operation_done();

    return 0;
}

int spinor_write(uint32_t address, void *buffer, uint32_t size)
{
    uint32_t  pagesize = 256;
    uint32_t  startpage, endpage;
    uint32_t  pagecount;
    uint8_t*  bufferaddr;

    startpage = address / pagesize;
    endpage = (address + size) / pagesize;
    bufferaddr = (uint8_t* )buffer;

    if(size % pagesize)
      endpage++;

    for (pagecount = 0; pagecount < endpage - startpage; pagecount ++)
    {
      if(spinor_page_write(address, bufferaddr) != 0)
      {
         printf("spinor write fail!!!\n");
         return -1;
      }
      address += pagesize;
      bufferaddr += pagesize;
    }
    return 0;
}

int spinor_test()
{
    uint8_t buf[1024];
    uint8_t src[1024];
    int i;
    uint8_t reg_status;

    for (i=0; i<sizeof(src); i++)
        src[i] = i%256;

    if(spinor_init() != 0)
    {
       return -1;
    }
    if(spinor_read(0, buf, sizeof(buf)) != 0)
    {
       return -1;
    }
    if(spinor_erase(0, 1024) != 0)
    {
       return -1;
    }
    if(spinor_read(0, buf, sizeof(buf)) != 0)
    {
       return -1;
    }
    if(spinor_write(0, src, 1024) != 0)
    {
       return -1;
    }
    if(spinor_read(0, buf, sizeof(buf)) != 0)
    {
       return -1;
    }

    return 0;
}

int burn_singleimage()
{
    uint8_t* src = (uint8_t*)0x100;
    int      erase_ret;

    switch(deviceid)
    {
        case Macronix_ID: erase_ret = spinor_chiperase(); break;
        case Micron_ID:   erase_ret = spinor_dieerase(); break;
        default:          erase_ret = -1, printf("unsupported flash type!\n");
    }

    if(erase_ret != 0)
    {
        printf("erase error!\n");
        return -1;
    }
    printf("erase finished!\n");
    printf("writing!\n");
    if (spinor_write(0, src, 64<<20) != 0)
    {
        printf("write error\n");
        return -1;
    }
    printf("spinor flash burn finished\n");

    return 0;
}


int do_spinor(int argc, char *argv[])
{
    void* mem_addr = NULL;
    uint32_t flash_addr;

    if(argc < 2)
    {
        printf("The number of arguments is wrong!!!\n");
        return -1;
    }

    if (argv[1][0] == 'i')
    {
       if(spinor_init() != 0)
       {
           printf("spinor flash init failed! \n");
           return -1;
       }
       printf("spi master and spinor flash has been initialized! \n");
    }
    else if (argv[1][0] == 'r')
    {
       mem_addr = (void*)strtoul(argv[3], NULL, 0);
       flash_addr = (uint32_t)strtoul(argv[2], NULL, 0);

       if(spinor_read(flash_addr, mem_addr, strtoul(argv[4], NULL, 0)) != 0)
       {
           printf("spinor read operation fail! \n");
           return -1;
       }
       printf("spinor read operation success! \n");
    }
    else if (argv[1][0] == 'w')
    {
       mem_addr = (void*)strtoul(argv[3], NULL, 0);
       flash_addr = (uint32_t)strtoul(argv[2], NULL, 0);

       if(spinor_write(flash_addr, mem_addr, strtoul(argv[4], NULL, 0)) != 0)
       {
           printf("spinor write operation fail! \n");
           return -1;
       }
       printf("spinor write operation success! \n");
    }
    else if (argv[1][0] == 'e')
    {
       if(spinor_erase(strtoul(argv[2], NULL, 0), strtoul(argv[3], NULL, 0)) != 0)
       {
           printf("spinor erase operation fail! \n");
           return -1;
       }
       printf("spinor erase operation success! \n");
    }
    else if (argv[1][0] == 'b')
    {
       if(burn_singleimage() != 0)
       {
           printf("burn flash failed! \n");
           return -1;
       }
    }

    return 0;
}

MK_CMD(spinor, do_spinor, "use spi master to read/write spinor flash",
    "\n"
    " spinor {init | i}\n"
    "    -Init flash\n"
    " spinor {test | t}\n"
    "    -Test basic fuction\n"
    " spinor {read | r} {flashaddr}  {memaddr} {size}\n"
    "    -Read {size} bytes data from {flashaddr} to {memaddr}\n"
    " spinor {write | w} {flashaddr} {memaddr} {size}\n"
    "    -Write {size} bytes to {flashaddr} from {memaddr}\n"
    " spinor {erase | e} {addr} {size}\n"
    "    -Erase {size} bytes data from {addr}\n"
    " spinor {burn | b}\n"
    "    -Burn image into flash \n"
);
