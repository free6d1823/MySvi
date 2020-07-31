#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
#define IPS_POLLING
#define DEBUG_PRINT
#if 0
int set_key(unsigned char *key)
{
 	int i=0;
         while(i < 32)
         {
                key[i] = 0x11;
                key[i+1] = 0x22;
                key[i+2] = 0x33;
                key[i+3] = 0x44;
                i = i + 4;

         }

	return 0;
}

int set_iv(unsigned char *iv)
{
	  int i = 0;
	  memset(iv,INIT_IV,16);
          while(i<12)
          {
          	iv[i] = 0x11;
          	iv[i+1] = 0x22;
          	iv[i+2] = 0x33;
          	iv[i+3] = 0x44;
          	i = i + 4;
          }
          iv[15] = 0x1;


	return 0;

}
#endif


static int sm4_function_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sm4_mode,  int proc_len)
{
	int i;
	int ret;
	int outlen;

 	 if((sm4_mode == GCM_MODE) || (sm4_mode == CBC_CS1_MODE) || (sm4_mode == CBC_CS2_MODE) || (sm4_mode == CBC_CS3_MODE))
		outlen = 32;
	else
		outlen = 16;


        /*1. hw encrypt*/
        ret = smx_cmd_create(psrc, pdst, alg_flag, sm4_mode, ENCRYPT, proc_len);
        if(ret) {
                printf("sm4  module-sm4_cmd_creaete for encrypt failed! \n");
		return -1;
	}
        ret = smx_status_polling();
        if(ret) {
                printf("sm4 module-sm4_status_polling for encrypt failed! \n");
		return -1;
	}
	#ifdef DEBUG_PRINT
        for(i=0; i<outlen; i++)
                printf("en_dst = %x \n",pdst[i]);
	#endif

        /*2. hw decrypt*/
	printf("DECRYPT = %d \n", DECRYPT);
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


	if(sm4_mode == GCM_MODE){
		#ifdef DEBUG_PRINT
		for(i=0; i<16; i++)
		{
			printf("pdst = %x \n", pdst[i]);
		}
		#endif
	}

	return 0;
}

static int se_smx_sm4(int argc, char *argv[])
{
	int ret;
	int i;

	unsigned char src[] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0xaa,0xbb};
        //unsigned char src[] = "1122334455667788";
        //unsigned char src[16] = {0x0}; // {0xC3, 0x4C, 0x05, 0x2C, 0xC0, 0xDA, 0x8D, 0x73,
        //0x45, 0x1A, 0xFE, 0x5F, 0x03, 0xBE, 0x29, 0x7F};
        int len = 16;
        unsigned char sw_dst[32];
        unsigned char *psrc;
        unsigned char *pdst;
	if(argc < 2)
                return -EUSAGE;
	psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);
	memcpy(psrc,src,len);
	ret = smx_init_clk();
	if(!ret)
		printf("ips module clock case pass! \n");

	printf("begin to init ips module \n");
	ret = smx_module_reset();
	if(!ret)
		printf("ips module reset case pass! \n");
	ret = smx_dev_init();
	if(!ret)
		printf("ips module initialzie case pass! \n");
	ret = smx_key_iv_set();
	if(!ret)
		printf("ips module key_iv set case pass \n");
	 printf("\n");

	/*=====================================SM4-ECB============================================*/
   	/***********************calculate sm4-ecb********************************/
	ret = strcmp(argv[1],"sm4ecb");
	if(!ret) {
        	ret = sm4_function_test(psrc, pdst, SM4_FLAG, ECB_MODE, len);
        	if(!ret){
                 	printf("sm4_ecb mode case pass! \n");
			return 0;
		}
        	else{
                	 printf("sm4-ecb mode case failed! \n");
			 return -1;
		}
	}

        /***********************calculate sm4-cbc********************************/
	ret = strcmp(argv[1],"sm4cbc");
	if(!ret) {
		ret = sm4_function_test(psrc, pdst, SM4_FLAG, CBC_MODE, len);
        	if(!ret){
                 	printf("sm4_cbc mode case pass! \n");
		 	return 0;
		}
        	else{
                 	printf("sm4_cbc mode case failed! \n");
		 	return -1;
		}
	}

	  ret = strcmp(argv[1],"sm4cbccs1");
        if(!ret) {
                ret = sm4_function_test(psrc, pdst, SM4_FLAG, CBC_CS1_MODE, 18);
                if(!ret){
                        printf("sm4_cbc_cs1 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sm4_cbc_cs1 mode case failed! \n");
                        return -1;
                }
        }

	  ret = strcmp(argv[1],"sm4cbccs2");
        if(!ret) {
                ret = sm4_function_test(psrc, pdst, SM4_FLAG, CBC_CS2_MODE, 18);
                if(!ret){
                        printf("sm4_cbc_cs2 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sm4_cbc_cs2 mode case failed! \n");
                        return -1;
                }
        }

	  ret = strcmp(argv[1],"sm4cbccs3");
        if(!ret) {
                ret = sm4_function_test(psrc, pdst, SM4_FLAG, CBC_CS3_MODE, 18);
                if(!ret){
                        printf("sm4_cbc_cs3 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sm4_cbc_cs3 mode case failed! \n");
                        return -1;
                }
        }


        /***********************calculate sm4_cfb********************************/
	ret = strcmp(argv[1],"sm4cfb");
	if(!ret) {
		ret = sm4_function_test(psrc, pdst, SM4_FLAG, CFB_MODE, len);
        	if(!ret){
                 	printf("sm4_cfb mode case pass! \n");
		 	return 0;
		}
        	else{
                 	printf("sm4_cfb mode case failed! \n");
			return -1;
		}
	}
	/***********************calculate sm4_ofb********************************/
	ret = strcmp(argv[1],"sm4ofb");
	if(!ret) {
        	ret = sm4_function_test(psrc, pdst, SM4_FLAG, OFB_MODE, len);
        	if(!ret){
                 	printf("sm4_ofb mode case pass! \n");
			return 0;
		}
        	else{
                 	printf("sm4-ofb mode case failed! \n");
			return -1;
		}
	}
	/***********************calculate sm4_ctr********************************/
	ret = strcmp(argv[1],"sm4ctr");
	if(!ret) {
		printf("ente into sm4ctr \n");
		ret = sm4_function_test(psrc, pdst, SM4_FLAG, CTR_MODE, len);
		if(!ret){
                 	printf("sm4-ctr mode case pass! \n");
			return 0;
		}
        	else{
                 	printf("sm4-ctr mode case failed! \n");
			return -1;
		}
	}
	/***********************calculate sme-gcm********************************/
	ret = strcmp(argv[1],"sm4gcm");
	if(!ret) {
        	ret = sm4_function_test(psrc, pdst, SM4_FLAG, GCM_MODE, len);
        	if(!ret){
                 	printf("sm4-gcm mode case pass! \n");
			return 0;
		}
        	else{
                 	printf("sm4-gcm mode case failed! \n");
			return -1;
		}
	}
	return 0;
}



MK_CMD(smx_sm4, se_smx_sm4, "Test crypto_smx,including sm4-ecb,sm4-cbc,sm4-cfb,sm4-ofb,sm4-ctr,sm4-gcm",
        "smx_sm4 \n"
        "       - sm4ecb: test aes-128-ecb algorithm\n"
        "       - sm4cbc: test aes-128-cbc algorithm\n"
        "       - sm4cfb: test aes-128-cfb algorithm\n"
        "       - sm4ofb: test aes-128-ofb algorithm\n"
        "       - sm4ctr: test aes-128-ctr algorithm\n"
        "       - sm4gcm: test aes-128-gcm algorithm\n"
);

