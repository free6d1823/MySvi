#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
#define IPS_POLLING
//#define DEBUG_PRINT

  	unsigned char src[16] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
	unsigned char key128[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
        unsigned char key192[24] = {0x8e,0x73,0xb0,0xf7,0xda,0x0e,0x64,0x52,0xc8,0x10,0xf3,0x2b,0x80,0x90,0x79,0xe5,0x62,0xf8,0xea,0xd2,0x52,0x2c,0x6b,0x7b};
        unsigned char key256[32] = {0x60,0x3d,0xeb,0x10,0x15,0xca,0x71,0xbe,0x2b,0x73,0xae,0xf0,0x85,0x7d,0x77,0x81,
                                        0x1f,0x35,0x2c,0x07,0x3b,0x61,0x08,0xd7,0x2d,0x98,0x10,0xa3,0x09,0x14,0xdf,0xf4};
 	unsigned char iv[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
	unsigned char nonce_counter[16] = {0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff};

	unsigned char dst_ecb_128[16]={0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
        unsigned char dst_cbc_128[16]={0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d};
        unsigned char dst_cfb_ofb_128[16]={0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a};
        unsigned char dst_ctr_128[16]={0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce};
        unsigned char dst_ecb_192[16]={0xbd,0x33,0x4f,0x1d,0x6e,0x45,0xf2,0x5f,0xf7,0x12,0xa2,0x14,0x57,0x1f,0xa5,0xcc};
        unsigned char dst_cbc_192[16]={0x4f,0x02,0x1d,0xb2,0x43,0xbc,0x63,0x3d,0x71,0x78,0x18,0x3a,0x9f,0xa0,0x71,0xe8};
        unsigned char dst_cfb_ofb_192[16]={0xcd,0xc8,0x0d,0x6f,0xdd,0xf1,0x8c,0xab,0x34,0xc2,0x59,0x09,0xc9,0x9a,0x41,0x74};
        unsigned char dst_ctr_192[16]={0x1a,0xbc,0x93,0x24,0x17,0x52,0x1c,0xa2,0x4f,0x2b,0x04,0x59,0xfe,0x7e,0x6e,0x0b};
        unsigned char dst_ecb_256[16]={0xf3,0xee,0xd1,0xbd,0xb5,0xd2,0xa0,0x3c,0x06,0x4b,0x5a,0x7e,0x3d,0xb1,0x81,0xf8};
        unsigned char dst_cbc_256[16]={0xf5,0x8c,0x4c,0x04,0xd6,0xe5,0xf1,0xba,0x77,0x9e,0xab,0xfb,0x5f,0x7b,0xfb,0xd6};
        unsigned char dst_cfb_ofb_256[16]={0xdc,0x7e,0x84,0xbf,0xda,0x79,0x16,0x4b,0x7e,0xcd,0x84,0x86,0x98,0x5d,0x38,0x60};
        unsigned char dst_ctr_256[16]={0x60,0x1e,0xc3,0x13,0x77,0x57,0x89,0xa5,0xb7,0xa7,0xf5,0x04,0xbb,0xf3,0xd2,0x28};


int aes_function_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int aes_bitlen, int aes_mode,  int proc_len)
{
	int i;
	int ret;
	int outlen = 16;
        unsigned char *tmp_ppt;
	unsigned char *tmp_ppt1;
	unsigned char dst[16]={0x0};
	unsigned char ddt_dst[16] = {0x0};
	unsigned long long *ddt_src;
        unsigned long long *tmp_pt;
	unsigned long long *src_pt;
	unsigned char *ppt_src;

	unsigned long long*pt;
        unsigned char *ppt;
	unsigned char *ppt1;
	unsigned char tmp_src[0x10];

 	if(alg_flag == AES_DDT_FLAG){

		ddt_src = (unsigned long long*)(IPS_DDT_SRC+0x800);
		ppt_src = (unsigned char*)(IPS_SRC_BASE+0x800);
		ddt_src[0] = (IPS_SRC_BASE + 0x800);
        	ddt_src[1] = 0x10;
        	ddt_src[2] = 0x0;
        	ddt_src[3] = 0x0;

	}else {
		memset(pdst,0,0x100);
		memset(psrc+0x800,0,0x100);
	}

	switch(aes_mode)
	{
		case ECB_MODE:
			if(aes_bitlen == AES_128)
				memcpy(dst,dst_ecb_128,16);
			if(aes_bitlen == AES_192)
				memcpy(dst,dst_ecb_192,16);
			if(aes_bitlen == AES_256)
				memcpy(dst,dst_ecb_256,16);
		break;

		case CBC_MODE:
			if(aes_bitlen == AES_128)
                                memcpy(dst,dst_cbc_128,16);
                        if(aes_bitlen == AES_192)
                                memcpy(dst,dst_cbc_192,16);
                        if(aes_bitlen == AES_256)
                                memcpy(dst,dst_cbc_256,16);
		break;
		case CFB_MODE:
		case OFB_MODE:
			if(aes_bitlen == AES_128)
                                memcpy(dst,dst_cfb_ofb_128,16);
                        if(aes_bitlen == AES_192)
                                memcpy(dst,dst_cfb_ofb_192,16);
                        if(aes_bitlen == AES_256)
                                memcpy(dst,dst_cfb_ofb_256,16);
		break;

		case CTR_MODE:
			if(aes_bitlen == AES_128)
                                memcpy(dst,dst_ctr_128,16);
                        if(aes_bitlen == AES_192)
                                memcpy(dst,dst_ctr_192,16);
                        if(aes_bitlen == AES_256)
                                memcpy(dst,dst_ctr_256,16);

		break;
		default:
		break;
	}


        pt = (unsigned long long*)psrc;
        ppt = (unsigned char *)pt[0];
	ppt1 = (unsigned char *)pt[2];
	if(pt[3]!=0){
		memcpy(tmp_src, ppt,8);
		memcpy(tmp_src+8,ppt1,8);
	} else if(pt[1] == 0x10){
		memcpy(tmp_src,ppt,0x10);
	}
	#ifdef DEBUG_PRINT
        if(alg_flag == AES_DDT_FLAG)
        {
                printf("psrc = %x \n", psrc);
                printf("pt[0] = %x \n",pt[0]);
                printf("pt[1] = %x \n", pt[1]);
                for(i=0; i<pt[1]; i++)
                        printf("ppt = %x \n", ppt[i]);
		for(i=0; i<pt[3]; i++)
			printf("ppt = %x \n", ppt1[i]);
        }
        #endif

        /*1. hw encrypt*/
	//printf("prepare ips_cmd_create proc_len = %x \n", proc_len);

        ret = ips_cmd_create(psrc, pdst, alg_flag, aes_bitlen, aes_mode, ENCRYPT, proc_len);
        if(ret) {
                printf("ips module-ips_cmd_creaete for aes-encrypt failed! \n");
		return -1;
	}
//	printf("ips_cmd done \n");
	#ifdef IPS_POLLING
        ret = ips_status_polling();
        if(ret) {
                printf("ips module-ips_status_polling for aes-encrypt failed! \n");
		return -1;
	}
	#endif
	tmp_pt = (unsigned long long*)pdst;
	tmp_ppt = (unsigned char*)tmp_pt[0];
	memcpy(ddt_dst,tmp_ppt,tmp_pt[1]);
	if(tmp_pt[2] != 0){
		tmp_ppt1 = (unsigned char*)tmp_pt[2];
		memcpy(ddt_dst + tmp_pt[1],tmp_ppt1,tmp_pt[3]);
	}

	#ifdef DEBUG_PRINT
 	if(alg_flag == AES_DDT_FLAG){
                printf("pdst = %x \n",pdst);
                printf("pdst[0] = %x \n", tmp_pt[0]);
                printf("pdst[1] = %x \n", tmp_pt[1]);
                for(i=0; i<tmp_pt[1]; i++)
                        printf("tmp_pt = %x \n", tmp_ppt[i]);
        }else{
		for(i=0; i<outlen; i++)
                	printf("en_dst = %x \n",pdst[i]);
	}
	#endif

        /*2. hw decrypt*/
        if(alg_flag == AES_DDT_FLAG)
		ret = ips_cmd_create(pdst, (unsigned char*)ddt_src, alg_flag, aes_bitlen, aes_mode, DECRYPT, proc_len);
	else
        	ret = ips_cmd_create(pdst, psrc+0x800, alg_flag, aes_bitlen, aes_mode, DECRYPT, proc_len);
        if(ret) {
                printf("ips module-ips_cmd_creaete for aes-decrypt failed! \n");
		return -1;
	}
	#ifdef IPS_POLLING
        ret = ips_status_polling();
        if(ret) {
                printf("ips module-ips_status_polling for aes-decrypt failed! \n");
		return -1;
	}
	#endif
  //	src_pt =(unsigned long long *)ddt_src;
        ppt_src = (unsigned char*)ddt_src[0];
        #ifdef DEBUG_PRINT
        if(alg_flag == AES_DDT_FLAG){
                printf("ddt_src = %llx \n",ddt_src);
                printf("ddt_src[0] = %llx \n", ddt_src[0]);
                printf("ddt_src[1] = %llx \n", ddt_src[1]);

                for(i=0; i<ddt_src[1]; i++)
                        printf("ppt_src = %x \n", ppt_src[i]);

        }else{
        	for(i=0; i<outlen; i++)
                	printf("de_dst = %x \n",psrc[0x800+i]);
	}
	#endif
	if(alg_flag == AES_DDT_FLAG)
		//ret = str_cmp(ppt, ppt_src, proc_len);
		ret = str_cmp(tmp_src, ppt_src, proc_len);
	else
        	ret = str_cmp(psrc, (psrc+0x800), proc_len);
        if(ret) {
                	printf("decrypt data and source data are different!\n");
			return -1;
		}

        /*3. sw compare with engine*/

	#ifdef DEBUG_PRINT
         for(i=0; i<outlen; i++)
                printf("sw_dst = %x \n",dst[i]);
	#endif
        if(alg_flag == AES_DDT_FLAG)
		ret = str_cmp(ddt_dst,dst,outlen);
	else
	 	ret = str_cmp(pdst, dst, outlen);
        if(ret) {
                	printf("encrypt data between engine and sw are different\n");
			return -1;
	 	}
	return 0;
}


int se_ips_aes_128()
{
	int ret;
	int i;
        int len = 16;
        unsigned char *hashkey;
	unsigned char *psrc;
        unsigned char *pdst;
	//printf("enter into se_ips_aes \n");
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

        ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, ECB_MODE, len);
        if(!ret){
                 printf("aes-128-ecb mode case pass! \n");
        }
        else{
                 printf("aes-128-ecb mode case failed! \n");
                 return -1;
        }
 	 /***********************calculate aes-128-ctr********************************/
        ret = ips_key_iv_set(key128,16,nonce_counter,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

        ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CTR_MODE, len);
        if(!ret){
                 printf("aes-128-ctr mode case pass! \n");
        }
        else{
                printf("aes-128-ctr mode case failed! \n");
                return -1;
        }

   	/***********************calculate aes-128-cfb********************************/

	ret = ips_key_iv_set(key128,16,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

        ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CFB_MODE, len);
        if(!ret){
                 printf("aes-128-cfb mode case pass! \n");
	}
        else{
                 printf("aes-128-cfb mode case failed! \n");
	         return -1;
	}

        /***********************calculate aes-128-ofb********************************/
	ret = ips_key_iv_set(key128,16,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, OFB_MODE, len);
        if(!ret){
                 printf("aes-128-ofb mode case pass! \n");
	}
        else{
                 printf("aes-128-ofb mode case failed! \n");
		 return -1;
	}
	/***********************calculate aes-128-cbc********************************/

        ret = ips_key_iv_set(key128,16,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CBC_MODE, len);
        if(!ret){
                 printf("aes-128-cbc mode case pass! \n");
	}
        else{
                 printf("aes-128-cbc mode case failed! \n");
		return -1;
	}
        /***********************calculate aes-128-cbc********************************/

	return 0;
}


int se_ips_aes_192()
{
        int ret;
        int i;
        int len = 16;
        unsigned char *hashkey;
        unsigned char *psrc;
        unsigned char *pdst;
        //printf("enter into se_ips_aes \n");
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
        ret = ips_dev_init();
        if(!ret)
                printf("ips module initialzie case pass! \n");

	/*=====================================AES-192==============================*/
	/***********************calculate aes-192-ecb********************************/
        ret = ips_key_iv_set(key192,24,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, ECB_MODE, len);
        if(!ret){
                        printf("aes-192-ecb mode case pass! \n");
                }
                else{
                        printf("aes-192-ecb mode case failed! \n");
                        return -1;
                }

	/***********************calculate aes-192-ctr********************************/

        ret = ips_key_iv_set(key192,24,nonce_counter,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

         ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CTR_MODE, len);
         if(!ret){
                        printf("aes-192-ctr mode case pass! \n");
                }
                else{
                        printf("aes-192-ctr mode case failed! \n");
                        return -1;
                }


    	/***********************calculate aes-192-cfb********************************/

        ret = ips_key_iv_set(key192,24,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CFB_MODE, len);
        if(!ret){
                        printf("aes-192-cfb mode case pass! \n");
                }
                else{
                         printf("aes-192-cfb mode case failed! \n");
                         return -1;
                }
        /***********************calculate aes-192-ofb********************************/

	ret = ips_key_iv_set(key192,24,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;
	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, OFB_MODE, len);
         if(!ret){
                        printf("aes-192-ofb mode case pass! \n");
                }
                else{
                        printf("aes-192-ofb mode case failed! \n");
                        return -1;
        	}
        /***********************calculate aes-192-cbc********************************/

        ret = ips_key_iv_set(key192,24,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

        ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CBC_MODE, len);
        if(!ret){
                        printf("aes-192-cbc mode case pass! \n");
                }
                else{
                        printf("aes-192-cbc mode case failed! \n");
                        return -1;
                }

	return 0;

}


int se_ips_aes_256()
{
        int ret;
        int i;
        int len = 16;

        unsigned char *hashkey;
        unsigned char *psrc;
        unsigned char *pdst;
        //printf("enter into se_ips_aes \n");
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

	 /*=====================================AES-256============================================*/
	  /***********************calculate aes-256-ecb********************************/
        ret = ips_key_iv_set(key256,32,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;
	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, ECB_MODE, len);
        if(!ret){
                        printf("aes-256-ecb mode case pass! \n");
                }
                else{
                        printf("aes-256-ecb mode case failed! \n");
                        return -1;
                }

	 /***********************calculate aes-256-ctr********************************/

         ret = ips_key_iv_set(key256,32,nonce_counter,hashkey,0);
         if(!ret)
                printf("ips module key_iv set case pass \n");
	 else
		return -1;

	 ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CTR_MODE, len);
         if(!ret){
                        printf("aes-256-ctr mode case pass! \n");
                }
                else{
                        printf("aes-256-ctr mode case failed! \n");
                        return -1;
                }


   	 /***********************calculate aes-256-cfb********************************/

         ret = ips_key_iv_set(key256,32,iv,hashkey,0);
         if(!ret)
                printf("ips module key_iv set case pass \n");
	 else
		return -1;

         ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CFB_MODE, len);
         if(!ret){
                        printf("aes-256-cfb mode case pass! \n");
                }
                else{
                         printf("aes-256-cfb mode case failed! \n");
                         return -1;
                }
        /***********************calculate aes-256-ofb********************************/

         ret = ips_key_iv_set(key256,32,iv,hashkey,0);
         if(!ret)
                printf("ips module key_iv set case pass \n");
	 else
		return -1;

         ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, OFB_MODE, len);
         if(!ret){
                        printf("aes-256-ofb mode case pass! \n");
                }
                else{
                        printf("aes-256-ofb mode case failed! \n");
                        return -1;
        	}
        /***********************calculate aes-256-cbc********************************/

        ret = ips_key_iv_set(key256,32,iv,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CBC_MODE, len);
        if(!ret){
                        printf("aes-256-cbc mode case pass! \n");
                }
                else{
                        printf("aes-256-cbc mode case failed! \n");
                        return -1;
                }

	/*==================================end=====================================*/
	return 0;
}

