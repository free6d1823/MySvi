#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include "target/sim_trigger.h"
//#define DEBUG_PRINT
int sha_function_watchdog_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sha_flag, int ende_flag, int proc_len)
{
	int i;
	int ret;
	int outlen=20;
	unsigned char dgst[20] = {0xa9,0x99,0x3e,0x36,0x47,0x06,0x81,0x6a,0xba,0x3e,0x25,0x71,0x78,0x50,0xc2,0x6c,0x9c,0xd0,0xd8,0x9d};


	ret = ips_cmd_create(psrc, pdst, alg_flag, sha_flag, HASH_RAW_MODE, ende_flag, proc_len);
        if(ret) {
                printf("ips module--ips_cmd_create for sha failed!");
		return -1;
	}


	for(i=0; i<200; i++)
		;
	#ifdef DEBUG_PRINT
        for(i=proc_len; i<outlen+proc_len; i++)
               printf("pdst[i] =%x \n", pdst[i]);
        for(i=0; i<outlen; i++)
                printf("dgst = %x \n",dgst[i]);
	#endif

	ret = str_cmp((pdst+proc_len), dgst, outlen);
        if(!ret)
		return 0;
	else {
                printf("sha result between engine and sw are different");
		return -1;
	}
}


int ips_wd_timer_test()
{
	int ret;
	int i;
	unsigned char src[] = "abc"; //"Hi There"; //""what do ya want for nothing?"; //""abc";
	int len = 3; //8; //8; //28; //0x03;
	unsigned char *psrc;
	unsigned char *pdst;
	//printf("enter into se ips sharaw module! \n");
	psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);

	memcpy(psrc,src,len);
	ret = ips_init_clk();
	if(!ret){
		sim_finish();
		printf("ips module clock case pass! \n");
	}else
		return -1;
	ret = ips_module_reset();
	if(!ret){
		sim_finish();
		printf("ips module reset case pass! \n");
	}else
		return -1;
	ret = ips_dev_init();
	if(!ret){
		sim_finish();
		printf("ips module initialzie case pass! \n");
	}else
		return -1;
	//ret = ips_key_iv_set();
	//if(!ret)
	//	printf("ips module key_iv set case pass \n");

        /*************************sha1 alg***********************************************/
	ret = sha_function_watchdog_test(psrc, pdst, SHA_FLAG,SHA_1, ENCRYPT, len);
	if(!ret){
		sim_finish();
		printf("sha1 raw mode case pass! \n");
	}
	else {
		sim_fail();
		printf("sha1 raw mode case failed! \n");
		return -1;
	}

	return 0;

}

