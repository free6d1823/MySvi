#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
#define IPS_POLLING
//#define DEBUG_PRINT


unsigned char sm4_src[16] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
unsigned char sm4_key[16] =  {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
unsigned char sm4_iv[16] = {0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};
unsigned char sm4_dst_ecb[16] = {0x68,0x1e,0xdf,0x34,0xd2,0x06,0x96,0x5e,0x86,0xb3,0xe9,0x4f,0x53,0x6e,0x42,0x46};
unsigned char sm4_dst_cbc[16] = {0x3f,0x1e,0x73,0xc3,0xdf,0xd5,0xa1,0x32,0x88,0x2f,0xe6,0x9d,0x99,0x6c,0xde,0x93};
unsigned char sm4_dst_cfb[16] = {0xc8,0x95,0xf3,0xab,0x39,0xc5,0x70,0x46,0xe3,0xdf,0xce,0x71,0x2e,0xca,0xb5,0xd7};
unsigned char sm4_dst_ofb[16] = {0xc8,0x95,0xf3,0xab,0x39,0xc5,0x70,0x46,0xe3,0xdf,0xce,0x71,0x2e,0xca,0xb5,0xd7};
unsigned char sm4_dst_ctr[16] = {0xc8,0x95,0xf3,0xab,0x39,0xc5,0x70,0x46,0xe3,0xdf,0xce,0x71,0x2e,0xca,0xb5,0xd7};



int sm4_function_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sm4_mode,  int proc_len)
{
	int i;
	int ret;
	int outlen=16;
	unsigned char dst[60] = {0x0};

	switch(sm4_mode)
	{
		case ECB_MODE:
			memcpy(dst,sm4_dst_ecb,16);
		break;

		case CBC_MODE:
			memcpy(dst,sm4_dst_cbc,16);
		break;

		case CFB_MODE:
			memcpy(dst,sm4_dst_cfb,16);
		break;

		case OFB_MODE:
			memcpy(dst,sm4_dst_ofb,16);
		break;

		case CTR_MODE:
			memcpy(dst,sm4_dst_ctr,16);
		break;
		default:
		break;

	}
        /*1. hw encrypt*/
        ret = smx_cmd_create(psrc, pdst, alg_flag, sm4_mode, ENCRYPT, proc_len);
        if(ret) {
                printf("sm4  module-sm4_cmd_creaete for encrypt failed! \n");
		return -1;
	}
	#ifdef IPS_POLLING
        ret = smx_status_polling();
        if(ret) {
                printf("sm4 module-sm4_status_polling for encrypt failed! \n");
		return -1;
	}
	#endif
	#ifdef DEBUG_PRINT
        for(i=0; i<outlen; i++)
                printf("en_dst = %x \n",pdst[i]);
	#endif

        /*2. hw decrypt*/
        ret = smx_cmd_create(pdst, psrc+0x1000, alg_flag, sm4_mode, DECRYPT, proc_len);
        if(ret) {
                printf("sm4 module-sm4_cmd_creaete for decrypt failed! \n");
		return -1;
	}
	#ifdef IPS_POLLING
        ret = smx_status_polling();
        if(ret) {
                printf("smx module-ips_status_polling for decrypt failed! \n");
		return -1;
	}
	#endif
	#ifdef DEBUG_PRINT
        for(i=0; i<outlen; i++)
                printf("de_dst = %x \n",psrc[0x1000+i]);
	#endif
        ret = str_cmp(psrc, (psrc+0x1000), proc_len);
        if(ret) {
                printf("decrypt data and source data are different!\n");
		return -1;
	} else
		printf("decrypt data is the same as source data!\n");


	ret = str_cmp(pdst, dst, proc_len);
	if(ret){
		printf("encrypt data and standard data are different! \n");
		return -1;
	} else
		printf("encrypt data is the same as standard data! \n");
	return 0;
}


int se_smx_sm4()
{
	int ret;
	int i;

        int len = 16;
        unsigned char sw_dst[32];
        unsigned char *psrc;
        unsigned char *pdst;
	psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);
	memcpy(psrc,sm4_src,len);
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
	ret = smx_dev_init();
	if(!ret)
		printf("smx module initialzie case pass! \n");
	else
		return -1;
	ret = smx_key_iv_set(sm4_key,sm4_iv);
	if(!ret)
		printf("smx module key_iv set case pass \n");
	else
		return -1;

	/*=====================================SM4-ECB============================================*/
   	/***********************calculate sm4-ecb********************************/
       	ret = sm4_function_test(psrc, pdst, SM4_FLAG, ECB_MODE, len);
        if(!ret){
                 	printf("sm4_ecb mode case pass! \n");
		}
        	else{
                	 printf("sm4-ecb mode case failed! \n");
			 return -1;
		}
        /***********************calculate sm4-cbc********************************/
	ret = smx_key_iv_set(sm4_key,sm4_iv);
	if(!ret)
		printf("smx module key_iv set case pass \n");
	ret = sm4_function_test(psrc, pdst, SM4_FLAG, CBC_MODE, len);
        if(!ret){
                 	printf("sm4_cbc mode case pass! \n");
		}
        	else{
                 	printf("sm4_cbc mode case failed! \n");
		 	return -1;
		}

        /***********************calculate sm4_cfb********************************/
	ret = smx_key_iv_set(sm4_key,sm4_iv);
	if(!ret)
		printf("smx module key_iv set case pass \n");
	 ret = sm4_function_test(psrc, pdst, SM4_FLAG, CFB_MODE, len);
         if(!ret){
                 	printf("sm4_cfb mode case pass! \n");
		}
        	else{
                 	printf("sm4_cfb mode case failed! \n");
			return -1;
		}
	/***********************calculate sm4_ofb********************************/

	ret = smx_key_iv_set(sm4_key,sm4_iv);
	if(!ret)
		printf("smx module key_iv set case pass \n");
         ret = sm4_function_test(psrc, pdst, SM4_FLAG, OFB_MODE, len);
         if(!ret){
                 	printf("sm4_ofb mode case pass! \n");
		}
        	else{
                 	printf("sm4-ofb mode case failed! \n");
			return -1;
		}
	/***********************calculate sm4_ctr********************************/

	ret = smx_key_iv_set(sm4_key, sm4_iv);
	if(!ret)
		printf("smx module key_iv set case pass \n");
	ret = sm4_function_test(psrc, pdst, SM4_FLAG, CTR_MODE, len);
	if(!ret){
                 	printf("sm4-ctr mode case pass! \n");
		}
        	else{
                 	printf("sm4-ctr mode case failed! \n");
			return -1;
		}

	return 0;
}


