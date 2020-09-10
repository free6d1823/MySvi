#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include <target/irqc.h>
#include <target/utils.h>

int vf_free()
{
	int ret_value;

	ret_value = READ_REG(IPS_VF0_REG_VF_FREE);
        if(ret_value){
		printf("VF is free \n");
		return 1;
	}
	else{
		//printf("VF is allocate \n");
		return 0;
	}

}

int clear_vf_allocate()
{
	int ret;
	ret = vf_free();
	if(!ret){
		WRITE_REG(IPS_VF0_REG_VF_FREE,1);
	}

	return 0;
}

int vf_alloc()
{
	int ret;
	ret = vf_free();
	if(ret)
		WRITE_REG(IPS_VF0_REG_VF_ALLOC,1);
	ret = READ_REG(IPS_VF0_REG_VF_ALLOC);
	if(ret) {
		printf("VF alloc \n");
		return 1;
	}
	else{
		printf("VF not alloc");
		return 0;
	}
}

int vf_enable(int channel)
{
	int ret;

	if(channel == 0){
		WRITE_REG(IPS_VF0_REG_RING_INIT_0,0x1);
	}else if(channel ==1){
		WRITE_REG(IPS_VF0_REG_RING_INIT_0,0x2);
	}

	return 0;
}



int vf_disable(int channel)
{
        int ret;

        if(channel == 0){
                WRITE_REG(IPS_VF0_REG_RING_INIT_0, READ_REG(IPS_VF0_REG_RING_INIT_0)&0XFE);
        }else if(channel ==1){

                WRITE_REG(IPS_VF0_REG_RING_INIT_0, READ_REG(IPS_VF0_REG_RING_INIT_0)&0XFD);
        }

        return 0;
}


int vf_initialzie()
{
	int ret;
	int i;

	printf("ips vf initialize begin!\n");
        ret = ips_init_clk();
        if(!ret)
                printf("ips module clock case pass! \n");
        else
                return -1;


	vf_alloc();
	/*******init other register*********************/

	for(i = 0; i<2; i++)
	{
		ret = vf_enable(i);
		if(!ret)
		printf("channel %d enable \n",i);

		ret = vf_disable(i);
		printf("channel %d disable \n", i);
	}
	printf("ips vf initialie end!\n");
	return 0;
}
int vf_swtich()
{
	int i;
	int ret;
	printf("ips vf switch begin! \n ");
        ret = ips_init_clk();
        if(!ret)
                printf("ips module clock case pass! \n");
        else
                return -1;
	vf_alloc();


	vf_enable(0);
	vf_enable(1);


	ret = ips_module_reset();
        if(!ret){
                printf("ips module reset case pass! \n");
		 /*clear key contex buffer*/
		for(i=0; i<0x8; i++)
                	writel(0, (uintptr_t)(IPS_VF0_KEY + 4*i));
		for(i=0; i<0x4; i++)
                	writel(0, (uintptr_t)(IPS_VF0_KEY+HASHKEY_OFFSET + 4*i));
	}
        else
                return -1;
	/*disable vf*/
	vf_disable(0);
	vf_disable(1);
	ret = clear_vf_allocate();
	if(!ret){
		printf("ips vf switch end! \n ");
		return 0;
	}
	else
		return -1;
}
