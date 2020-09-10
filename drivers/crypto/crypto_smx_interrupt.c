#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
//#define DEBUG_PRINT

int sm3_function_intr(unsigned char *psrc, unsigned char *pdst, int alg_flag, int ende_flag, int proc_len)
{
	int i;
	int ret;
	int outlen = 32;

	//unsigned char dgst[32]={0xff,0xe0,0x74,0x34,0x44,0x70,0x01,0x63,0x0f,0x78,0x17,0xdb,0xed,0x2b,0xfe,0x5a,0x4e,0x0a,0x76,0xbd,0x34,0x61,0x22,0x2f,0xf2,0xb1,0x89,0x52,0x63,0x5c,0x9d,0x51};
	unsigned char dgst[32] = {0x66, 0xc7, 0xf0, 0xf4, 0x62,0xee,0xed,0xd9,0xd1, 0xf2,0xd4,0x6b,0xdc,0x10,0xe4,0xe2,0x41,0x67,0xc4,0x87,0x5c,0xf2,0xf7,0xa2,0x29,0x7d,0xa0,0x2b,0x8f,0x4b,0xa8,0xe0};

	ret = smx_cmd_create(psrc, pdst, alg_flag, HASH_RAW_MODE, ende_flag, proc_len);
        if(ret) {
                printf("smx module--smx_cmd_create for sm3 failed!");
		return -1;
	}
	for(i=0; i<100; i++)
		;
	#ifdef DEBUG_PRINT
        for(i=0; i<outlen+proc_len; i++) //proc_len
                printf("pdst[i] =%x \n", pdst[i]);
        for(i=0; i<outlen; i++)
                printf("dgst = %x \n",dgst[i]);
	#endif
	disable_smx_irq();
        ret = str_cmp((pdst+proc_len), dgst, outlen);
        if(!ret)
		return 0;
	else {
                printf("sm3 result between engine and sw are different");
		return -1;
	}
}

int se_smx_sm3_intr()
{
	int ret;
	int i;
	unsigned char src[] = "abc";
	int len = 3;
	unsigned char *psrc;
	unsigned char *pdst;

	psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);

	memcpy(psrc,src,len);

	disable_smx_irq();
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
	ret = smx_key_iv_set();
	if(!ret)
		printf("smx module key_iv set case pass \n");
	else
		return -1;

        /*************************sm3 alg***********************************************/
	ret = 0;//strcmp(argv[1],"sm3");
	if(!ret){
		ret = sm3_function_intr(psrc, pdst, SM3_FLAG, ENCRYPT, len);
		if(!ret){
		 	printf("sm3-intr alg case pass! \n");
			//return 0;
		}
		else {
		 	printf("sm3-intr alg case failed! \n");
			return -1;
		}
	}

	/*disable channel 0*/
        WRITE_REG(SMX_VF0_REG_RING_INIT_0,0);
        ret = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret){
                printf("channel 0 enable failed \n");
                return -1;
        }


	return 0;
}

int sm4_function_intr_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sm4_mode,  int proc_len)
{
        int i;
        int ret;
        int outlen=16;
	unsigned char dst[16] = {0x68,0x1e,0xdf,0x34,0xd2,0x06,0x96,0x5e,0x86,0xb3,0xe9,0x4f,0x53,0x6e,0x42,0x46};


	   /*1. hw encrypt*/
        ret = smx_cmd_create(psrc, pdst, alg_flag, sm4_mode, ENCRYPT, proc_len);
        if(ret) {
                printf("sm4  module-sm4_cmd_creaete for encrypt failed! \n");
                return -1;
        }

	for(i=0; i<100; i++)
		;
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
	for(i=0; i<100; i++)
		;
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


int se_smx_sm4_intr()
{
        int ret;
        int i;
	unsigned char sm4_src[16] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char sm4_key[16] =  {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char sm4_iv[16] = {0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};

        int len = 16;
        unsigned char sw_dst[32];
        unsigned char *psrc;
        unsigned char dst[60] = {0x0};
        unsigned char *pdst;
        psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
        pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);
        memcpy(psrc,sm4_src,len);
	disable_smx_irq();
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
        ret = sm4_function_intr_test(psrc, pdst, SM4_FLAG, ECB_MODE, len);
        if(!ret){
                        printf("sm4_ecb intr mode case pass! \n");
                }
                else{
                         printf("sm4-ecb intr mode case failed! \n");
                         return -1;
                }
	/*disable channel 0*/
        WRITE_REG(SMX_VF0_REG_RING_INIT_0,0);
        ret = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret){
                printf("channel 0 enable failed \n");
                return -1;
        }


	return 0;
}
