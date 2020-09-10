#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include <target/irqc.h>
#include <target/utils.h>


int smx_key_test(int vf_no)
{
        int ret_value;
	int i;
        int addr_offset;
	int key_len = 16;
	int iv_len =16;
	int hashkey_len = 0x80;
	unsigned int key[4] = {0x55aa55aa,0x55aa55aa,0x55aa55aa,0x55aa55aa};
	unsigned int iv[4] = {0xaa55aa55,0xaa55aa55,0xaa55aa55,0xaa55aa55};
	addr_offset =  vf_no*0x20000;

	for(i=0; i<key_len/4; i++)
                writel(key[i], (uintptr_t)(SMX_VF0_KEY+addr_offset + 4*i));

        for(i=0; i<iv_len/4; i++)
                writel(iv[i], (uintptr_t)(SMX_VF0_KEY+addr_offset+IV_OFFSET + 4*i));



	/*判断是否写入的正确*/
	for(i=0; i<key_len/4; i++){
                ret_value = readl((uintptr_t)(SMX_VF0_KEY+addr_offset + 4*i));
		if(ret_value != 0x55aa55aa)
			return -1;
	}
        for(i=0; i<iv_len/4; i++){
                ret_value = readl((uintptr_t)(SMX_VF0_KEY+addr_offset+IV_OFFSET + 4*i));
		if(ret_value != 0xaa55aa55)
			return -1;
	}



	return 0;
}


 int se_smx_keytest()
{
        int ret=0;
        int i;
        ret = smx_init_clk();
        if(!ret)
                printf("smx module clock case pass! \n");
        else
                return -1;
        ret = smx_module_reset();
        if(!ret)
                printf("smx module reset case pass! \n");
        else
                return -1;
        for(i=0; i<4; i++){
                ret = smx_key_test(i);
                if(ret == -1){
                	printf("smx module key set failed \n");
		       break;
		}
        }
        return ret;

}

