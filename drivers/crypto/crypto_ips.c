#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include <target/irqc.h>
#include <target/utils.h>
//#define C_A76
#define CM4
//#define IPS_INTR
#define IPS_POLLING
int glb_de_flag = 0;

int ips_vfreg_read_write_test(int vf_no)
{
	int ret_value;
	int addr_offset = vf_no*0x20000;
	/*IRQ EN*/
	ret_value = READ_REG(IPS_VF0_REG_IRQ_EN + addr_offset);
	if(ret_value != 0x0){
		printf("IRQ EN read default value fail!");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_IRQ_EN + addr_offset, 0xff);
	ret_value = READ_REG(IPS_VF0_REG_IRQ_EN+addr_offset);
        if(ret_value != 0xff){
                printf("IRQ EN write & read test fail!");
		return -1;
	}
 	WRITE_REG(IPS_VF0_REG_IRQ_EN+addr_offset, 0x0);
	/*IRQ RAW*/
	ret_value = READ_REG(IPS_VF0_REG_IRQ_RAW+addr_offset);
        if(ret_value != 0x0){
                printf("IRQ RAW read default value fail!");
		return -1;
	}
	/*IRQ STAT*/
	ret_value = READ_REG(IPS_VF0_REG_IRQ_STAT+addr_offset);
        if(ret_value != 0x0){
                printf("IRQ STAT read default value fail!");
		return -1;
	}

	/*IRQ CTRL_0*/
	ret_value = READ_REG(IPS_VF0_REG_IRQ_CTRL_0+addr_offset);
        if(ret_value != 0x001E0002){
                printf("IRQ CTRL_0 read default value fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_IRQ_CTRL_0+addr_offset, 0x00400040);
        ret_value = READ_REG(IPS_VF0_REG_IRQ_CTRL_0+addr_offset);
        if(ret_value != 0x00400040){
                printf("IRQ CTRL_0 write & read test fail!");
		return -1;
	}
	WRITE_REG(IPS_VF0_REG_IRQ_CTRL_0+addr_offset, 0x001E0002);
	/*IRQ_CTRL_1*/
	ret_value = READ_REG(IPS_VF0_REG_IRQ_CTRL_1+addr_offset);
        if(ret_value != 0x001E0002){
                printf("IRQ CTRL_1 read default value fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_IRQ_CTRL_1+addr_offset, 0x001d0001);
        ret_value = READ_REG(IPS_VF0_REG_IRQ_CTRL_1+addr_offset);
        if(ret_value != 0x001d0001){
                printf("IRQ CTRL_1 write & read test fail!");
		return -1;
	}
        WRITE_REG(IPS_VF0_REG_IRQ_CTRL_1+addr_offset, 0x001d0001);
	/*WD_CTRL_0*/
	ret_value = READ_REG(IPS_VF0_WD_CTRL_0+addr_offset);
	if(ret_value != 0xffffffff){
		printf("IRQ WD_CTRL_0 read default fail!");
		return -1;
	}

	WRITE_REG(IPS_VF0_WD_CTRL_0+addr_offset, 0x55aa55aa);
	ret_value = READ_REG(IPS_VF0_WD_CTRL_0+addr_offset);
	if(ret_value != 0x55aa55aa){
		printf("IRQ WD_CTRL_0 read & write fail!");
		return -1;
	}

	WRITE_REG(IPS_VF0_WD_CTRL_0+addr_offset, 0xffffffff);
	/*WD_CTRL_1*/
	 ret_value = READ_REG(IPS_VF0_WD_CTRL_1+addr_offset);
        if(ret_value != 0xffffffff){
                printf("IRQ WD_CTRL_1 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_WD_CTRL_1+addr_offset, 0x55aa55aa);

	ret_value = READ_REG(IPS_VF0_WD_CTRL_1+addr_offset);
	if(ret_value != 0x55aa55aa){
                printf("IRQ WD_CTRL_1 read & write fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_WD_CTRL_1+addr_offset, 0xffffffff);
	/*C0_IRQ_INFO_1*/
	ret_value = READ_REG(IPS_VF0_C0_IRQ_INFO_1+addr_offset);
	if(ret_value != 0x0){
		printf("C0_IRQ_INFO_1 read default fail!");
		return -1;
	}
	/*C1_IRQ_INFO_1*/
	ret_value = READ_REG(IPS_VF0_C1_IRQ_INFO_1+addr_offset);
        if(ret_value != 0x0){
                printf("C1_IRQ_INFO_1 read default fail!");
		return -1;
	}
	/*RING_CTRL_0*/
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_0+addr_offset);
	if(ret_value !=0){
		printf("IPS_VF0_REG_RING_CTRL_0 read default fail!");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_RING_CTRL_0+addr_offset,0x55aa55aa);
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_0+addr_offset);
	if(ret_value != 0x55aa55aa){
		printf("IPS_VF0_REG_RING_CTRL_0 read & write fail! ");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_RING_CTRL_0+addr_offset,0x0);

	/*RING_CTRL_1*/
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_1+addr_offset);
        if(ret_value !=0){
                printf("IPS_VF0_REG_RING_CTRL_1 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_1+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_1+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_1 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_1+addr_offset,0x0);
	/*RING CTRL _2*/
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_2+addr_offset);
        if(ret_value !=0){
                printf("IPS_VF0_REG_RING_CTRL_2 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_2+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_2+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_2 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_2+addr_offset,0x0);
	 /*RING CTRL _3*/
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_3+addr_offset);
        if(ret_value !=0){
                printf("IPS_VF0_REG_RING_CTRL_3 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_3+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_3+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_3 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_3+addr_offset,0x0);
	 /*RING CTRL _4*/
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_4+addr_offset);
        if(ret_value !=0){
                printf("IPS_VF0_REG_RING_CTRL_4 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_4+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_4+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_4 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_4+addr_offset,0x0);
	 /*RING CTRL _5*/
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_5+addr_offset);
        if(ret_value !=0){
                printf("IPS_VF0_REG_RING_CTRL_5 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_5+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_5+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_5 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_5+addr_offset,0x0);
	 /*RING CTRL _6*/
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_6+addr_offset);
        if(ret_value !=0){
                printf("IPS_VF0_REG_RING_CTRL_6 read default fail!");
		return -1;

	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_6+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_6+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_6 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_6+addr_offset,0x0);
	 /*RING CTRL _7*/
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_7+addr_offset);
        if(ret_value !=0){
                printf("IPS_VF0_REG_RING_CTRL_7 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_7+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_7+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_7 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_7+addr_offset,0x0);
	 /*RING CTRL _8*/
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_8+addr_offset);
        if(ret_value !=0x00200020){
                printf("IPS_VF0_REG_RING_CTRL_8 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_8+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_8+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_8 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_8+addr_offset,0x00200020);
	 /*RING CTRL _9*/
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_9+addr_offset);
        if(ret_value !=0x00200020){
                printf("IPS_VF0_REG_RING_CTRL_9 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_9+addr_offset,0x55aa55aa);
        ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_9+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IPS_VF0_REG_RING_CTRL_9 read & write fail! ");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_RING_CTRL_9+addr_offset,0x00200020);
	/*_C0_MAILBOX_0*/
	ret_value = READ_REG(IPS_VF0_REG_C0_MAILBOX_0+addr_offset);
	if(ret_value != 0){
		printf("IPS_VF0_REG_C0_MAILBOX_0 read default fail!");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_C0_MAILBOX_0+addr_offset, 0xffff);
	ret_value = READ_REG(IPS_VF0_REG_C0_MAILBOX_0+addr_offset);
	if(ret_value != 0xffff){
		printf("IPS_VF0_REG_C0_MAILBOX_0 read & write fail!");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_C0_MAILBOX_0+addr_offset, 0x0);
	/*C0_MAILBOX_1*/
	ret_value = READ_REG(IPS_VF0_REG_C0_MAILBOX_1+addr_offset);
        if(ret_value != 0){
                printf("IPS_VF0_REG_C0_MAILBOX_1 read default fail!");
		return -1;
	}
	 /*C0_MAILBOX_2*/
        ret_value = READ_REG(IPS_VF0_REG_C0_MAILBOX_2+addr_offset);
        if(ret_value != 0){
                printf("IPS_VF0_REG_C0_MAILBOX_2 read default fail!");
		return -1;
	}
        /*C0_MAILBOX_3*/
        ret_value = READ_REG(IPS_VF0_REG_C0_MAILBOX_3+addr_offset);
        if(ret_value != 0){
                printf("IPS_VF0_REG_C0_MAILBOX_3 read default fail!");
		return -1;
	}
	WRITE_REG(IPS_VF0_REG_C0_MAILBOX_3+addr_offset, 0xffff);
        ret_value = READ_REG(IPS_VF0_REG_C0_MAILBOX_3+addr_offset);
        if(ret_value != 0xffff){
                printf("IPS_VF0_REG_C0_MAILBOX_3 read & write fail!");
		return -1;
	}
        WRITE_REG(IPS_VF0_REG_C0_MAILBOX_3+addr_offset, 0x0);
	 /*C1_MAILBOX_0*/
        ret_value = READ_REG(IPS_VF0_REG_C1_MAILBOX_0+addr_offset);
        if(ret_value != 0){
                printf("IPS_VF0_REG_C1_MAILBOX_0 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_C1_MAILBOX_0+addr_offset, 0xffff);
        ret_value = READ_REG(IPS_VF0_REG_C1_MAILBOX_0+addr_offset);
        if(ret_value != 0xffff){
                printf("IPS_VF0_REG_C1_MAILBOX_0 read & write fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_C1_MAILBOX_0+addr_offset, 0x0);
        /*C1_MAILBOX_1*/
        ret_value = READ_REG(IPS_VF0_REG_C1_MAILBOX_1+addr_offset);
        if(ret_value != 0){
                printf("IPS_VF0_REG_C1_MAILBOX_1 read default fail!");
		return -1;
	}
  	/*C1_MAILBOX_2*/
        ret_value = READ_REG(IPS_VF0_REG_C1_MAILBOX_2+addr_offset);
        if(ret_value != 0){
                printf("IPS_VF0_REG_C1_MAILBOX_2 read default fail!");
		return -1;
	}
         /*C1_MAILBOX_3*/
        ret_value = READ_REG(IPS_VF0_REG_C1_MAILBOX_3+addr_offset);
        if(ret_value != 0){
                printf("IPS_VF0_REG_C1_MAILBOX_3 read default fail!");
		return -1;
	}

        WRITE_REG(IPS_VF0_REG_C1_MAILBOX_3+addr_offset, 0xffff);
        ret_value = READ_REG(IPS_VF0_REG_C1_MAILBOX_3+addr_offset);
        if(ret_value != 0xffff){
                printf("IPS_VF0_REG_C1_MAILBOX_3 read & write fail!");
		return -1;

	}

        WRITE_REG(IPS_VF0_REG_C1_MAILBOX_3+addr_offset, 0x0);
        /*C0_MAILBOX_3*/
        ret_value = READ_REG(IPS_VF0_REG_C1_MAILBOX_3+addr_offset);
        if(ret_value != 0){
                printf("IPS_VF0_REG_C1_MAILBOX_3 read default fail!");
		return -1;
	}
	/*C0_RING_STS*/
	ret_value = READ_REG(IPS_VF0_REG_C0_RING_STS_0+addr_offset);
	if(ret_value != 0x0){
		printf("IPS_VF0_REG_C0_RING_STS_0 read default fail");
		return -1;
	}
	/*c0_RING_STS*/
	ret_value = READ_REG(IPS_VF0_REG_C0_RING_STS_1+addr_offset);
	if(ret_value != 0x0a){
		printf("IPS_VF0_REG_C0_RING_STS_1 read default fail");
		return -1;
	}
	/*C1_RING_STS_0*/
	 ret_value = READ_REG(IPS_VF0_REG_C1_RING_STS_0+addr_offset);
        if(ret_value != 0x0){
                printf("IPS_VF0_REG_C1_RING_STS_0 read default fail");
		return -1;
	}
        /*c1_RING_STS*/
        ret_value = READ_REG(IPS_VF0_REG_C1_RING_STS_1+addr_offset);
        if(ret_value != 0x0a){
                printf("IPS_VF0_REG_C1_RING_STS_1 read default fail");
		return -1;
	}
	/*RING_INIT_0*/
	ret_value = READ_REG(IPS_VF0_REG_RING_INIT_0+addr_offset);
	if(ret_value != 0x0){
		printf("IPS_VF0_REG_RING_INIT_0 read default fail");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_RING_INIT_0+addr_offset, 0x3);
	ret_value = READ_REG(IPS_VF0_REG_RING_INIT_0+addr_offset);
	if(ret_value != 0x3){
		printf("IPS_VF0_REG_RING_INIT_0 read & write fail");
		return -1;
	}


	WRITE_REG(IPS_VF0_REG_RING_INIT_0+addr_offset, 0x0);

	/*CH_PRIOR*/
	ret_value = READ_REG(IPS_VF0_REG_CH_PRIOR+addr_offset);
	if(ret_value != 0){
		printf("IPS_VF0_REG_CH_PRIOR read default fail");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_CH_PRIOR+addr_offset, 0x01);
	ret_value = READ_REG(IPS_VF0_REG_CH_PRIOR+addr_offset);
	if(ret_value !=0x1){
		printf("IPS_VF0_REG_CH_PRIOR read & write fail");
		return -1;
	}
	WRITE_REG(IPS_VF0_REG_CH_PRIOR+addr_offset, 0x0);

	/*SMX_SPARE*/
	ret_value = READ_REG(IPS_VF0_REG_SMX_SPARE+addr_offset);
	if(ret_value != 0){
		printf("IPS_VF0_REG_LOCAL_MSI_STAT read default fail");
		return -1;
	}
	WRITE_REG(IPS_VF0_REG_SMX_SPARE+addr_offset,0xffffffff);
	ret_value = READ_REG(IPS_VF0_REG_SMX_SPARE+addr_offset);
	if(ret_value != 0xffffffff){
		printf("IPS_VF0_REG_LOCAL_MSI_STAT read & write fail");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_SMX_SPARE+addr_offset,0x0);
	/*VF_ALLOC*/
	ret_value = READ_REG(IPS_VF0_REG_VF_ALLOC+addr_offset);
	if(ret_value != 0){
		printf("IPS_VF0_REG_VF_ALLOC read default fail!");
		return -1;
	}

	WRITE_REG(IPS_VF0_REG_VF_ALLOC+addr_offset, 0x1);
	ret_value = READ_REG(IPS_VF0_REG_VF_ALLOC+addr_offset);
	if(ret_value != 0x1){
		printf("IPS_VF0_REG_VF_ALLOC read & write fail!");
		return -1;
	}
	/*VF_FREE*/
	ret_value = READ_REG(IPS_VF0_REG_VF_FREE+addr_offset);
	if(ret_value != 0x0){
		printf("IPS_VF0_REG_VF_FREE VF alloc fail");
		return -1;

	}

	WRITE_REG(IPS_VF0_REG_VF_FREE+addr_offset,0x1);
	ret_value = READ_REG(IPS_VF0_REG_VF_FREE+addr_offset);
	if(ret_value != 0x01){
		printf("IPS_VF0_REG_VF_FREE VF free fail");
		return -1;
	}

	if(vf_no ==0)
	{
	/*global ctrl*/
	/*VF_WEIGHT_0*/
	ret_value = READ_REG(IPS_VF_REG_WEIGHT_0);
	if(ret_value != 0x0){
		printf("IPS_VF_REG_WEIGHT_0 read default fail!");
		return -1;
	}
	WRITE_REG(IPS_VF_REG_WEIGHT_0,0x1);
	ret_value = READ_REG(IPS_VF_REG_WEIGHT_0);
	if(ret_value != 0x01){
		printf("IPS_VF_REG_WEIGHT_0 read & wirte fail");
		return -1;
	}

	/*VF_WEIGHT_1*/
	ret_value = READ_REG(IPS_VF_REG_WEIGHT_1);
	if(ret_value != 0x0){
		printf("IPS_VF_REG_WEIGHT_1 read default fail!");
		return -1;
	}

	WRITE_REG(IPS_VF_REG_WEIGHT_1,0x04030201);
	ret_value = READ_REG(IPS_VF_REG_WEIGHT_1);
	if(ret_value != 0x04030201){
		printf("IPS_VF_REG_WEIGHT_1 read & write fail");
		return -1;
	}

	WRITE_REG(IPS_VF_REG_WEIGHT_1,0x0);
	WRITE_REG(IPS_VF_REG_WEIGHT_0,0x0);
	/*DMA_CTRL*/
	ret_value = READ_REG(IPS_VF_REG_DMA_CTRL);
	if(ret_value !=0x0808){
		printf("IPS_VF_REG_DMA_CTRL read default fail");
		return -1;
	}

	WRITE_REG(IPS_VF_REG_DMA_CTRL, 0x0909);
	ret_value =  READ_REG(IPS_VF_REG_DMA_CTRL);
        if(ret_value !=0x0909){
                printf("IPS_VF_REG_DMA_CTRL read & write fail");
		return -1;
	}

	WRITE_REG(IPS_VF_REG_DMA_CTRL, 0x0808);
	}/*if(ch_no ==0)*/

	printf("register read & wirte case pass!\n");
	return 0;
}

/**************watch dog timer******************************/
int set_threshold(int ch_no)
{
	if(!ch_no)
		WRITE_REG(IPS_VF0_WD_CTRL_0, 0x100);
	if(ch_no)
		WRITE_REG(IPS_VF0_WD_CTRL_1, 0x100000);
	return 0;
}

int wd_enable(int ch_no)
{
	if(!ch_no)
		WRITE_REG(IPS_VF0_REG_IRQ_EN, READ_REG(IPS_VF0_REG_IRQ_EN)|0X100);
	if(ch_no)
		WRITE_REG(IPS_VF0_REG_IRQ_EN, READ_REG(IPS_VF0_REG_IRQ_EN)|0X200);
	return 0;
}

int wd_disable(int ch_no)
{
	if(!ch_no)
		WRITE_REG(IPS_VF0_REG_IRQ_EN, READ_REG(IPS_VF0_REG_IRQ_EN)&0xfffffeff);
	if(ch_no)
		WRITE_REG(IPS_VF0_REG_IRQ_EN, READ_REG(IPS_VF0_REG_IRQ_EN)&0xfffffdff);
	return 0;
}

int wd_reset(int ch_no)
{
	set_threshold(ch_no);
	return 0;
}

/***************watch dog timer*****************************/



int ips_init_clk(void)
{
	int ret_value;
	#ifdef C_A76
	WRITE_REG(SFC_CLK_EN, 0x10000);

	WRITE_REG(SFC_RST, 0x0);
	#endif
	/*initialzie IPS-CORE clock*/
	WRITE_REG(IPS_TOP_CTRL_CORE_CLK_CTRL, 0x1);
	ret_value = READ_REG(IPS_TOP_CTRL_CORE_CLK_CTRL);
	if(ret_value != 1){
		printf("enable clock failed \n");
		return -1;
	}
	/*reset ips*/
	WRITE_REG(IPS_TOP_CTRL_CORE_RST_CTRL, 0x1);
	while(READ_REG(IPS_TOP_CTRL_CORE_RST_CTRL)!=0)
			;
	//printf("IPS-Core running case pass!");
	/*initialzie clock enalbe for IPS-SRAM clock and IPS-FUNCTION*/
	WRITE_REG(IPS_VF_REG_GLB_OPT, 0x0);
	ret_value = READ_REG(IPS_VF_REG_GLB_OPT);
	if(ret_value != 0){
		printf("ips ram clock enable failed!");
		return -1;
	}
	return 0;
}
int ips_module_reset()
{
	int ret_value;
	int count;
	#if 0
	/* vf_free */
	ret_value = READ_REG(IPS_VF0_REG_VF_FREE);
	if(ret_value = 1)
	{
		/*VF ALLOC*/
		printf("vf free! \n");
		WRITE_REG(IPS_VF0_REG_VF_ALLOC, 1);
		ret_value = READ_REG(IPS_VF0_REG_VF_ALLOC);
		if(ret_value == 1)
			printf("security attribute consistent!\n");
		else
			printf("security attribute not consistent!\n");
	}
	#endif
	ret_value = READ_REG(IPS_VF0_REG_RING_INIT_1);
	while((ret_value != 3)&&(count != 100)) {
		 ret_value = READ_REG(IPS_VF0_REG_RING_INIT_1);
			count++;
		}
	if(count == 100)
		return -1;
	else{
 		WRITE_REG(IPS_VF0_REG_RING_INIT_2,1);
		WRITE_REG(IPS_VF0_REG_RING_INIT_3,1);
		return 0;
	}
}
/**********************interrupt*****************************************/
#ifdef IPS_INTR
void disable_vf0_irq()
{
	int ret_value;
	WRITE_REG(IPS_VF0_REG_IRQ_EN,0x0);
        ret_value = READ_REG(IPS_VF0_REG_IRQ_EN);
        if(ret_value != 0x0)
                printf("disable irq channel 0 failed \n");
}
void set_intr_threshold_value()
{
	int ret_value;
	WRITE_REG(IPS_VF0_REG_IRQ_CTRL_0,0x00010001);
        ret_value = READ_REG(IPS_VF0_REG_IRQ_CTRL_0);
        if(ret_value != 0x00010001)
                printf("set irq triger threshold failed \n");

}
void enable_vf0_irq()
{
	int ret_value;
	WRITE_REG(IPS_VF0_REG_IRQ_EN,0x80001451);
        ret_value = READ_REG(IPS_VF0_REG_IRQ_EN);
        if(ret_value != 0x80001451)
                printf("enable irq channel 0 failed \n");
}
void ips_irq_process()
{
	int begin;
	int end;
	int num;
	unsigned int ret_value;
	int status_base;

	status_base = READ_REG(IPS_VF0_REG_RING_CTRL_4);
	struct status_ring *ring =(struct status_ring*)IPS_STATUS_BASE;
	ret_value = READ_REG(IPS_VF0_REG_IRQ_RAW);
	while(!ret_value)
		ret_value = READ_REG(IPS_VF0_REG_IRQ_RAW);
	if(ret_value&0x1){
		printf("chanel 0 status error! \n");
		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 1);
		return;
	}

	if(ret_value&0x4){
		printf("chanel 0 command interrupt! \n");
		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 0x4);

	}
	if(ret_value&0x100){
		printf("chanel 0 status watch dog! \n");
		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 0x100);
		return;
	}

	if(ret_value&0x1000){
		printf("write chanel 0 status error! \n");
		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 0x1000);
		return;
	}
	if(ret_value&0x10){
		printf("intr status dispose! \n");
		begin = READ_REG(IPS_VF0_REG_C0_MAILBOX_2);
		end = READ_REG(IPS_VF0_REG_C0_MAILBOX_3);
		num = begin%MAX_CMD - end%MAX_CMD;
		if(num < 0)
			num = MAX_CMD - end%MAX_CMD;
		if(!num){
			printf("status ring is empty");
			return;
		}
		//printf("begin = %d \n", begin);
		//printf("end = %d \n", end);
		//printf("num = %d \n", num);
		//memcpy((void*)ring, (void*)(status_base + 8*end),8 );
		ring = (struct status_ring*)(READ_REG(IPS_VF0_REG_RING_CTRL_4) + end);
		//printf("ring ret_code = %x \n", ring->ret_code);
		//printf("ring sw_id value =%x \n", ring->sw_id);
		/*set the status ring consumer*/
		WRITE_REG(IPS_VF0_REG_C0_MAILBOX_3, begin);

		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 0x10);
		//printf("dispose complete!\n");
		//while(!READ_REG(IPS_VF0_REG_RING_INIT_1))
		//		;
	}


}
void ips_irq_handle(irq_t irq, void *ctx)
{
	irq_t ips_irq = SE_IPS_IRQ;
	//irqc_disable_irq(ips_irq);
	printf("enter into ips irq handle! \n");
	ips_irq_process();
	//enable_vf0_irq();
}
void ips_irq_init()
{
	//printf("ips irq initialize!\n");
	irq_t ips_irq = SE_IPS_IRQ;
	disable_vf0_irq();
	set_intr_threshold_value();
	irqc_configure_irq(ips_irq, 32, IRQ_LEVEL_TRIGGERED);
	irq_register_vector(ips_irq, ips_irq_handle, NULL);
	irqc_enable_irq(ips_irq);
	enable_vf0_irq();
	//printf("ips irq end initialzie \n");
}
int get_cmd_status()
{

}
#endif
 /*****************************************************************************/
int ips_dev_init()
{
	int ret_value = 0;
	unsigned int cmd_base;
	unsigned int status_base;
	cmd_base = IPS_CMD_BASE;
	status_base = IPS_STATUS_BASE;
	/*set cmd and status base addr*/
	WRITE_REG(IPS_VF0_REG_RING_CTRL_0,cmd_base);   //low
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_0);
	if(ret_value != cmd_base){
		printf("set cmd base failed \n");
		return -1;
	}
	WRITE_REG(IPS_VF0_REG_RING_CTRL_1,0);   //high
	WRITE_REG(IPS_VF0_REG_RING_CTRL_4,status_base); //low
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_4);
	if(ret_value != status_base) {
		printf("set status base failed \n");
		return -1;
	}
	WRITE_REG(IPS_VF0_REG_RING_CTRL_5,0); //high
	/*set cmd ring descriptior count and status ring descriptior count*/
	WRITE_REG(IPS_VF0_REG_RING_CTRL_8,0x00400040);
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_8);
	if(ret_value != 0x00400040){
		printf("set descriptior count failed \n");
		return -1;
	}
	#ifdef IPS_POLLING
	/*set irq triger threshold value*/
	WRITE_REG(IPS_VF0_REG_IRQ_CTRL_0,0x00010001);
	ret_value = READ_REG(IPS_VF0_REG_IRQ_CTRL_0);
	if(ret_value != 0x00010001){
		printf("set irq triger threshold failed \n");
		return -1;
	}
	/*enable irq channel 0 */
	WRITE_REG(IPS_VF0_REG_IRQ_EN,0x80001451);
	ret_value = READ_REG(IPS_VF0_REG_IRQ_EN);
	if(ret_value != 0x80001451){
		printf("enable irq channel 0 failed \n");
		return -1;
	}
	#endif
	#ifdef IPS_INTR
	ips_irq_init();
	#endif
	/*enable channel 0*/
	WRITE_REG(IPS_VF0_REG_RING_INIT_0,1);
	ret_value = READ_REG(IPS_VF0_REG_RING_INIT_0);
	if(ret_value !=1){
		printf("channel 0 enable failed \n");
		return -1;
	}

	/*set threshold for WD*/
	//set_threshold(0);

	return 0;

}
int ips_key_iv_set(unsigned char *aes_key, int aes_keylen, unsigned char *aes_iv, unsigned char *hash_key, int hash_keylen)
{
	int i;
	int ret_value;
	unsigned int *key;
	unsigned int *hashkey;
	unsigned int *iv;

	key = (unsigned int*)aes_key;
	iv = (unsigned int*)aes_iv;
	hashkey = (unsigned int*)hash_key;


	if((!aes_keylen) && (!hash_keylen))
		return -1;

	if(aes_keylen != 0)
	{
		for(i=0; i<aes_keylen/4; i++)
			writel(key[i], (uintptr_t)(IPS_VF0_KEY + 4*i));
		for(i=0; i<4; i++)
			writel(iv[i], (uintptr_t)(IPS_VF0_KEY+IV_OFFSET + 4*i));
		  /*read and verify*/
        	for(i=0;i<aes_keylen/4;i++)
        	{
                	ret_value = readl((uintptr_t)(IPS_VF0_KEY+4*i));
			//printf("ret_value_key = %x \n", ret_value);
               		 if(ret_value != key[i])
                	{
                        	printf("key set failed \n");
                        	return -1;
                	}
        	}

        	for(i=0; i<4; i++)
        	{
                	ret_value = readl((uintptr_t)(IPS_VF0_KEY+IV_OFFSET+4*i));
			//printf("ret_value_iv = %x \n", ret_value);
                	if(ret_value != iv[i]){
                        	printf("iv set failed \n");
                        	return -1;
                	}
        	}


	}
	if(hash_keylen !=0)
	{
		for(i=0; i<hash_keylen/4; i++)
			 writel(hashkey[i],(uintptr_t)(IPS_VF0_KEY+HASHKEY_OFFSET + 4*i));

		for(i=0; i<hash_keylen/4; i++)
        	{
                	ret_value = readl((uintptr_t)(IPS_VF0_KEY+HASHKEY_OFFSET+4*i));
                	if(ret_value != hashkey[i]){
                        	printf("hashkey set failed \n");
                        	return -1;
                	}
        	}

	}
	return 0;

}
int ips_data_setup_sha(unsigned char *src, unsigned char *dst,struct ips_command* pcmd,int hash_alg,int hash_mode, int ende_flag, int proc_len, int ddt_mode)
{
	memset(pcmd,0,0x40);
        /*setup the actual cmd ring data from alg_ctx  or call back? */
        pcmd->src_pkt_addr_l = (unsigned long)src;
        pcmd->src_pkt_addr_h = 0;
        pcmd->dst_pkt_addr_l = (unsigned long)dst;
        pcmd->dst_pkt_addr_h = 0;
        pcmd->dst_pkt_off = 0;  //no offset
        pcmd->src_pkt_off = 0;
        pcmd->pre_aad_len = 0;
        pcmd->post_aad_len = 0;
        pcmd->proc_len = proc_len;//strlen(src);
        pcmd->icv_offset = proc_len; //0
        pcmd->iv_offset = 0;
        pcmd->iv_enable = 0;
        /*control*/
        pcmd->hm_key_size = 0x20;
        pcmd->key_exp = 0;
        pcmd->icv_append = 1;
        pcmd->icv_enc = 0;
        pcmd->icv_pt = 1;
        pcmd->aad_copy = 0;
        pcmd->encrypt = ende_flag;
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = ddt_mode;
        pcmd->hash_mode = hash_mode;//0; //raw mode
        pcmd->cipher_mode = 0; //NULL ? ECB
        pcmd->hash_alg = hash_alg;//3;
        pcmd->cipher_alg = 0;
        pcmd->ioc = 0;
        /*aux_info*/
        pcmd->icv_len = 0;//ctx->sha.outlen;
        pcmd->cbc_cs_sel = 0;
        pcmd->bk_sz_cfb = 0;
	pcmd->sw_id = 0;
        return 0;
}


int ips_data_setup_aes(unsigned char *src, unsigned char *dst,struct ips_command* pcmd, int cipher_alg,int cipher_mode, int ende_flag, int proc_len, int ddt_mode)
{
	int mode;
	int cbc_submode = 0;

	switch(cipher_mode)
	{
		case 0x10:
			mode = 0x01;
			cbc_submode = 0x0;
		break;

		case 0x11:
			mode = 0x01;
			cbc_submode = 0x1;
		break;

		case 0x12:
			mode = 0x01;
			cbc_submode = 0x2;
		break;

		case 0x13:
			mode = 0x01;
			cbc_submode = 0x03;
		break;

		default:
			mode = cipher_mode;
		break;

	}
	memset(pcmd,0,0x40);
	/*setup the actual cmd ring data from alg_ctx  or call back? */
        pcmd->src_pkt_addr_l = (unsigned long)src;
        pcmd->src_pkt_addr_h = 0;
        pcmd->dst_pkt_addr_l = (unsigned long)dst;
        pcmd->dst_pkt_addr_h = 0;
        pcmd->dst_pkt_off = 0;  //no offset
        pcmd->src_pkt_off = 0;
	if(cipher_mode == GCM_MODE)
		pcmd->pre_aad_len = 20;
	else
		pcmd->pre_aad_len = 0;
        pcmd->post_aad_len = 0;
	//printf("proc_len = %x \n", proc_len);
        pcmd->proc_len = proc_len;
	if(cipher_mode == GCM_MODE)
        	pcmd->icv_offset = 80;
	else
		pcmd->icv_offset = 0;
        pcmd->iv_offset = 0;
        pcmd->iv_enable = 0;
        pcmd->hm_key_size = 0;
	if(ende_flag == 0)
                 pcmd->key_exp = 1;
        else
                 pcmd->key_exp = 0;

        pcmd->icv_append = 0;
        pcmd->icv_pt = 0;
        pcmd->icv_enc = 0;
	if(cipher_mode == GCM_MODE)
		pcmd->aad_copy = 1;
	else
		pcmd->aad_copy = 0;
        pcmd->encrypt = ende_flag; //encrypt
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = ddt_mode;
        pcmd->hash_mode = 0; //raw mode
        pcmd->cipher_mode = mode; //NULL ? ECB
        pcmd->hash_alg = 0;
        pcmd->cipher_alg = cipher_alg;
        pcmd->ioc = 0;
        pcmd->icv_len = 0;
        pcmd->cbc_cs_sel = cbc_submode;
	//printf("cbc_submode = %x \n", cbc_submode);
        pcmd->bk_sz_cfb = 0;
	pcmd->sw_id = 0;
        return 0;
}
int ips_cmd_create(unsigned char *src, unsigned char *dst, int flag, int alg_flag, int alg_mode, int ende_flag, int proc_len)
{
	int i;
	int ret_value;
	unsigned int producer_idx;
	unsigned int consumer_idx;
	unsigned int cmd_base;
	struct ips_command* pcmd = (struct ips_command*)IPS_CMD_RING; //heap_alloc(0x40);
	producer_idx = READ_REG(IPS_VF0_REG_C0_MAILBOX_0);
	//printf("producer_idx = %x \n", producer_idx);
	consumer_idx = READ_REG(IPS_VF0_REG_C0_MAILBOX_1);
        //printf("consumer_idx = %x \n", consumer_idx);
	/*fifo status full*/
        if (producer_idx % MAX_CMD + 1 == consumer_idx % MAX_CMD){
        	printf("command ring full! \n");
	        return -1;
	}
	switch(flag)
	{
		case 0: //sha
			ret_value = ips_data_setup_sha(src,dst,pcmd,alg_flag,alg_mode,ende_flag,proc_len,DIRECT_MODE);
		break;
		case 1: //aes
			ret_value = ips_data_setup_aes(src,dst,pcmd,alg_flag,alg_mode,ende_flag,proc_len,DIRECT_MODE);
		break;
		case 2: //sha_ddt
			ret_value = ips_data_setup_sha(src,dst,pcmd,alg_flag,alg_mode,ende_flag,proc_len,DDT_MODE);
		break;
		case 3: //aes_ddt
			ret_value = ips_data_setup_aes(src,dst,pcmd,alg_flag,alg_mode,ende_flag,proc_len,DDT_MODE);
		break;
		default:
		break;
	}
	#if 0
	if(flag == 0){ //sha
		ret_value = ips_data_setup_sha(src,dst,pcmd,alg_flag,alg_mode,ende_flag,proc_len);
	}
	if(flag == 1){//aes

		ret_value = ips_data_setup_aes(src,dst,pcmd,alg_flag,alg_mode,ende_flag,proc_len);
	}
	#endif
	if(ret_value) {
                printf("ips module data setup  case failed! \n");
		return -1;
	}
	cmd_base = READ_REG(IPS_VF0_REG_RING_CTRL_0);
	//memset((void*)(cmd_base + 64*producer_idx), 0x0, 0x40);
	//printf("cmd_base = %x \n", cmd_base);
	memcpy((void*)(uintptr_t)(cmd_base + 64*producer_idx), (void*)pcmd, 64);
	//for (i = 0; i < 64; i++)
          //    printf("cmdring #_%#x  value= %#x\n", i, *(unsigned char*)(uintptr_t)(cmd_base + i));
	producer_idx++;

	producer_idx = producer_idx % MAX_CMD;

	WRITE_REG(IPS_VF0_REG_C0_MAILBOX_0, producer_idx);
	/**************reset WD_TIMER******************/
	//reset_WD(0);
	producer_idx = READ_REG(IPS_VF0_REG_C0_MAILBOX_0);
	//printf("producer_idx = %x \n", producer_idx);
	//heap_free(pcmd);
	return 0;

}
int ips_status_polling()
{
	int i;
	int ret_value;
	int status_base;
	int producer_idx;
	int consumer_idx;
	struct status_ring* ring;
	status_base = READ_REG(IPS_VF0_REG_RING_CTRL_4);
	ring = (struct status_ring*)(uintptr_t)status_base;
	/*enalbe watch dog timer*/
	producer_idx = READ_REG(IPS_VF0_REG_C0_MAILBOX_0);
        consumer_idx = READ_REG(IPS_VF0_REG_C0_MAILBOX_1);
	//if(consumer_idx == producer_idx)
	//	enable_WD(0);

	for(i=0; i<10; i++)
	{
		ret_value = READ_REG(IPS_VF0_REG_IRQ_RAW);
		//printf("irq_raw = %x \n",ret_value);
		ret_value = READ_REG(IPS_VF0_REG_C0_RING_STS_0);
		//printf("ring_sts = %x \n",ret_value);
	}
	//printf("stsring ret_code  value= %#x\n", ring->ret_code);
        //printf("stsring sw_id value= %#x\n", ring->sw_id);
	return 0;
}
