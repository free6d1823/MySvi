#include "gc355_reg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <target/cmdline.h>
#include <target/utils.h>

//////////////////////GC355 memory layout////////////////////
/*******cmd_buffer      0x60000000   cmd data*******************/
/*******image_buffer    0x60003000   input image data***********/
/*******frame_buffer    0x600C3000   output image data**********/
/*******ts_buffer       0x60183000   ts buffer        **********/
/*******ts_l1_buffer    0x601A3000   ts level1        **********/
/*******ts_l2_buffer    0x601A4000   ts level2        **********/
/*******scis_buffer     0x601A5000   scissor buffer data********/
#define GC355_CMD_ADDR    0x60000000

/******The index of the test cases**********/
/***   0 ---- blend1            ********/
/***   1 ---- tess5             ********/
/***   2 ---- image5            ********/
int gc355_cmd_size_list[3]= {2832, 624, 584};

void gc355_init()
{
    writel_mask(0x800, 0x800, GC355_AHB_REG_BASE+GC355_AHB_AQCLOCKCTRL);

    while(readl(GC355_AHB_REG_BASE+GC355_AHB_AQCLOCKCTRL));
}

void gc355_fetch_start(int fetch_size)
{
    readl((GC355_AHB_REG_BASE + GC355_AHB_AQINTRACK));
    writel(0xFFFFFFFF,(GC355_AHB_REG_BASE + GC355_AHB_AQINTRENBL));
    writel(GC355_CMD_ADDR, (GC355_AHB_REG_BASE + GC355_AHB_GCREGFETCHADDR));
    writel((fetch_size>>3)&0x1FFFFF, (GC355_AHB_REG_BASE + GC355_AHB_GCREGFETCHCTRL));
}

void gc355_polling_idle() {
    int i;
    uint32_t irq_ack_value = 0;
    uint32_t axi_status = 0;
    while(!irq_ack_value)
       irq_ack_value = readl((GC355_AHB_REG_BASE + GC355_AHB_AQINTRACK));
    axi_status = readl((GC355_AHB_REG_BASE + GC355_AHB_AXISTATUS));
}

void gc355_info_dump() {
    uint32_t chipid = readl((GC355_AHB_REG_BASE + GC355_AHB_GCCHIPID));
    uint32_t chiprev = readl((GC355_AHB_REG_BASE + GC355_AHB_GCCHIPREV));
    uint32_t chipdate = readl((GC355_AHB_REG_BASE + GC355_AHB_GCCHIPDATE));

    printf("GC355 CHIP INFO: ID 0x%08x, REV 0x%08x, DATE 0x%08x\n", chipid, chiprev, chipdate);
}

int gc355_cmd(int argc, char * argv[])
{
    char * cmd_buf_ptr = NULL;
    int case_num = 0;
    char * ptemp = NULL;
    if(argc < 2)
        return -EUSAGE;

    if (strncmp(argv[1], "dump", 4) == 0) {
        gc355_info_dump();
    } else {
        case_num = strtoul(argv[1],0,0);
        gc355_init();

        gc355_fetch_start(gc355_cmd_size_list[case_num]);

        gc355_polling_idle();
    }
    return 0;
}

MK_CMD(gc355gpu, gc355_cmd, "GC355 2D test cases",
       "2D case \n"
       "    gc355gpu casenum \n"
       "    gc355gpu dump");

