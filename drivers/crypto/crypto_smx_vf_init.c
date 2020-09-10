#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include <target/irqc.h>
#include <target/utils.h>

int smx_vf_free()
{
	int ret_value;

	ret_value = READ_REG(SMX_VF0_REG_VF_FREE);
        if(ret_value){
		printf("VF is free \n");
		return 1;
	}else{
		//printf("VF is allocate \n");
		return 0;
	}
}

int smx_clear_vf_allocate()
{
	int ret;
	ret = smx_vf_free();
	if(!ret){
		WRITE_REG(SMX_VF0_REG_VF_FREE,1);
	}
	return 0;
}

int smx_vf_alloc()
{
	int ret;
	ret = smx_vf_free();
	if(ret)
		WRITE_REG(SMX_VF0_REG_VF_ALLOC,1);
	ret = READ_REG(SMX_VF0_REG_VF_ALLOC);
	if(ret) {
		printf("VF alloc \n");
		return 1;
	}
	else{
		printf("VF not alloc");
		return 0;
	}
}

int smx_vf_enable(int channel)
{
	int ret;

	if(channel == 0){
		WRITE_REG(SMX_VF0_REG_RING_INIT_0,0x1);
	}else if(channel ==1){
		WRITE_REG(SMX_VF0_REG_RING_INIT_0,0x2);
	}

	return 0;
}



int smx_vf_disable(int channel)
{
        int ret;

        if(channel == 0){
                WRITE_REG(SMX_VF0_REG_RING_INIT_0, READ_REG(SMX_VF0_REG_RING_INIT_0)&0XFE);
        }else if(channel ==1){

                WRITE_REG(SMX_VF0_REG_RING_INIT_0, READ_REG(SMX_VF0_REG_RING_INIT_0)&0XFD);
        }

        return 0;
}


int smx_vf_initialzie()
{
	int ret;
	int i;
	printf("smx vf initailize begin! \n");
	ret = smx_init_clk();
        if(!ret)
                printf("smx module clock case pass! \n");
        else
                return -1;


	smx_vf_alloc();
	/*******init other register*********************/

	for(i = 0; i<2; i++)
	{
		ret = smx_vf_enable(i);
		if(!ret)
		printf("channel %d enable \n",i);

		ret = smx_vf_disable(i);
		printf("channel %d disable \n", i);
	}
	printf("smx vf initialzie end! \n ");
	return 0;
}

int smx_vf_swtich()
{
	int ret;
	int i;
	printf("smx vf switch initalize \n");
	ret = smx_init_clk();
        if(!ret)
                printf("smx module clock case pass! \n");
        else
                return -1;

	smx_vf_alloc();

	smx_vf_enable(0);
	smx_vf_enable(1);

	ret = smx_module_reset();
        if(!ret){
	 printf("smx module reset case pass! \n");
	for(i=0; i<0x8; i++){
               writel(0, (uintptr_t)(SMX_VF0_KEY + 4*i));
	    }
	}
        else
                return -1;
	/*disable vf*/
	smx_vf_disable(0);
	smx_vf_disable(1);
	ret = smx_clear_vf_allocate();
	if(!ret){
		printf("smx vf swtich end \n");
		return 0;
	}
	else
		return -1;

}
