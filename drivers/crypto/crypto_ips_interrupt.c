#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include "target/sim_trigger.h"
//#define DEBUG_PRINT
int sha_function_intr_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sha_flag, int ende_flag, int proc_len)
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


int se_ips_sha_intr()
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
	ret = sha_function_intr_test(psrc, pdst, SHA_FLAG,SHA_1, ENCRYPT, len);
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



int aes_function_intr_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int aes_bitlen, int aes_mode,  int proc_len)
{
        int i;
        int ret;
        int outlen = 16;
	 unsigned char dst_ecb_128[16]={0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
         memset(pdst,0,0x100);
         memset(psrc+0x800,0,0x100);



        /*1. hw encrypt*/
        //printf("prepare ips_cmd_create proc_len = %x \n", proc_len);

        ret = ips_cmd_create(psrc, pdst, alg_flag, aes_bitlen, aes_mode, ENCRYPT, proc_len);
        if(ret) {
                printf("ips module-ips_cmd_creaete for aes-encrypt failed! \n");
                return -1;
        }
	for(i=0; i<200; i++)
		;
//      printf("ips_cmd done \n");
	#ifdef DEBUG_PRINT
                for(i=0; i<outlen; i++)
                        printf("en_dst = %x \n",pdst[i]);
        #endif

        /*2. hw decrypt*/
        ret = ips_cmd_create(pdst, psrc+0x800, alg_flag, aes_bitlen, aes_mode, DECRYPT, proc_len);
        if(ret) {
                printf("ips module-ips_cmd_creaete for aes-decrypt failed! \n");
                return -1;
        }
	for(i=0; i<200; i++)
		;


	#ifdef DEBUG_PRINT

                for(i=0; i<outlen; i++)
                        printf("de_dst = %x \n",psrc[0x800+i]);

        #endif
	ret = str_cmp(psrc, (psrc+0x800), proc_len);
        if(ret) {
                        printf("decrypt data and source data are different!\n");
                        return -1;
                }

        /*3. sw compare with engine*/

        #ifdef DEBUG_PRINT
         for(i=0; i<outlen; i++)
                printf("sw_dst = %x \n", dst_ecb_128[i]);
        #endif
  	 ret = str_cmp(pdst, dst_ecb_128, outlen);
         if(ret) {
                        printf("encrypt data between engine and sw are different\n");
                        return -1;
                }
	 else
        	return 0;

}

int se_ips_aes_intr()
{
        int ret;
        int i;
        int len = 16;
        unsigned char *hashkey;
        unsigned char *psrc;
        unsigned char *pdst;
        //printf("enter into se_ips_aes \n");
	unsigned char src[16] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
	unsigned char key128[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	unsigned char iv[16];
        hashkey = NULL;
        psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
        pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);
        memcpy(psrc,src,len);
        ret = ips_init_clk();
        if(!ret)
                printf("ips module clock case pass! \n");
        else
                return -1;

        ret = ips_module_reset();
        if(!ret)
                printf("ips module reset case pass! \n");
        else
                return -1;
        ret = ips_dev_init();
        if(!ret)
                printf("ips module initialzie case pass! \n");
        else
                return -1;
        /*=====================================AES-128============================================*/
        /***********************calculate aes-128-ecb********************************/
        ret = ips_key_iv_set(key128,16,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
        else
                return -1;

        ret = aes_function_intr_test(psrc, pdst, AES_FLAG, AES_128, ECB_MODE, len);
        if(!ret){
                 printf("aes-128-ecb mode case pass! \n");
        }
        else{
                 printf("aes-128-ecb mode case failed! \n");
                 return -1;
        }
	return 0;
}
