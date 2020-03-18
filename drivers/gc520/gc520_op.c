#include "gc520_reg.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <target/cmdline.h>
#include <target/utils.h>


/////////////////////GC520 memory layout////////////////////
/*********cmd_buffer      0x60000000    cmd data **********/
/*********frame_buffer    0x60080000    output frame data**/
/*********src0_buffer     0x60880000    input image 0 *****/
/*********src1_buffer     0x60C80000    input image 1 *****/
/*********src2_buffer     0x61480000    input image 2 *****/
/*********cmd1_buffer     0x61C80000    cmd 1 data for mmu*/
//////////////MMU memory layout////////////////
/*******safe addr  ?? ****************/
/*******TLB addr      ****************/

#define GC520_CMD_ADDR    0x60000000

/********************GC520 test cases**********************/
/******0  --  DisRamClockGating      **********************/
/******1  --  2DPerfMultiSrc_3src_1920x1080dst_1920x1080src0NV12_1920x1080src1_1920x1080src2_SrcRot */
/******2  --  fscaleCmdload          **********************/
/******3  --  mmu                    **********************/
/******4  --  pe2dgamma              **********************/
/******5  --  read_only              **********************/
/******6  --  read_write             **********************/
/******7  --  ROPPattern32bpp_320x240 *********************/
/******8  --  test2006                *********************/
/******9  --  ToggleReset            **********************/
/******10 --  xaq2_intr              **********************/

struct cmd_size {
    int cmd_len;
	int cmd1_len;
};

struct cmd_size cmd_size_list[11] = {
{680, 0}, {1712, 0}, {680,0},{704,12},
{4576, 0}, {523960, 0}, {808,0}, {368,0},
{448,0}, {680, 0},{712,0}};

void gc520_set_ramclockgating(uint32_t disable)
{
    writel_mask(0x200&(disable<<10),0x200,(GC520_AHB_REG_BASE + GC520_AHB_AQHICLOCKCTRL));
}

void gc520_setfscalecmd(uint32_t enable)
{
     uint32_t value = 0x70100;
	 writel(((value&0xFFFFFDFF) | (enable<<9)),(GC520_AHB_REG_BASE + GC520_AHB_AQHICLOCKCTRL));
}

void gc520_set_mmu(uint32_t enable)
{
     writel(enable, (GC520_AHB_REG_BASE + GC520_AHB_MMUCONTROL));
}

void gc520_fetch_cmd_start(int cmdlen) {
    readl((GC520_AHB_REG_BASE + GC520_AHB_AQINTRACK));
    writel(0xFFFFFFFF,(GC520_AHB_REG_BASE + GC520_AHB_AQINTRENBL));
    writel(GC520_CMD_ADDR, (GC520_AHB_REG_BASE + GC520_AHB_AQCMDBUFADDR));
    writel((cmdlen>>3), (GC520_AHB_REG_BASE + GC520_AHB_AQCMDBUFCTRL));
}

void gc520_fetch_cmd1_start(int cmdlen) {
    readl((GC520_AHB_REG_BASE + GC520_AHB_AQINTRACK));
    writel(0xFFFFFFFF,(GC520_AHB_REG_BASE + GC520_AHB_AQINTRENBL));
    writel(0x61C80000, (GC520_AHB_REG_BASE + GC520_AHB_AQCMDBUFADDR));
    writel((cmdlen>>3), (GC520_AHB_REG_BASE + GC520_AHB_AQCMDBUFCTRL));
}


void gc520_polling_idle() {
    int i;
    uint32_t irq_ack_value = 0;
    uint32_t axi_status = 0;
    while(!irq_ack_value)
       irq_ack_value = readl((GC520_AHB_REG_BASE + GC520_AHB_AQINTRACK));
    axi_status = readl((GC520_AHB_REG_BASE + GC520_AHB_AQAXISTATUS));
}

void gc520_soft_reset() {
    int mask = 0x1FFF7FFF;
    uint32_t clock_ctl = readl((GC520_AHB_REG_BASE + GC520_AHB_AQHICLOCKCTRL));
    writel((clock_ctl & 0x1000), (GC520_AHB_REG_BASE + GC520_AHB_AQHICLOCKCTRL));
    while(readl(GC520_AHB_REG_BASE + GC520_AHB_AQHICLOCKCTRL) & 0x1000);
}

int gc520_test_main(int argc, char * argv[])
{
    int case_num = 0;


    if(argc < 2)
        return -EUSAGE;

    case_num = strtoul(argv[1],0,0);

    gc520_soft_reset();

    switch(case_num)
    {
    case 0:
        gc520_set_ramclockgating(1);
        gc520_fetch_cmd_start(cmd_size_list[case_num].cmd_len);
        gc520_polling_idle();
        gc520_set_ramclockgating(0);
        break;
    case 2:
        gc520_setfscalecmd(1);
        gc520_fetch_cmd_start(cmd_size_list[case_num].cmd_len);
        gc520_polling_idle();
        gc520_setfscalecmd(0);
        break;
    default:
        if(cmd_size_list[case_num].cmd1_len) {
            gc520_fetch_cmd1_start(cmd_size_list[case_num].cmd1_len);
            gc520_polling_idle();
            gc520_set_mmu(1);
        }

        gc520_fetch_cmd_start(cmd_size_list[case_num].cmd_len);

        gc520_polling_idle();
        break;
    }
    return 0;
}


MK_CMD(gc520gpu, gc520_test_main, "GC520 2.5D test cases",
       "2.5D case \n"
       "    case number");

