#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
//#define DEBUG_PRINT
#define IPS_POLLING

int sm3_function_ddt_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int ende_flag, int proc_len)
{
	int i;
	int ret;
	int outlen = 32;
   	unsigned long long *tmp_pt;
        unsigned char *tmp_ppt;

	unsigned char dgst[32] = {0x66, 0xc7, 0xf0, 0xf4, 0x62,0xee,0xed,0xd9,0xd1, 0xf2,0xd4,0x6b,0xdc,0x10,0xe4,0xe2,0x41,0x67,0xc4,0x87,0x5c,0xf2,0xf7,0xa2,0x29,0x7d,0xa0,0x2b,0x8f,0x4b,0xa8,0xe0};

	ret = smx_cmd_create(psrc, pdst, alg_flag, HASH_RAW_MODE, ende_flag, proc_len);
        if(ret) {
                printf("smx module--smx_cmd_create for sm3 failed!");
		return -1;
	}
	#ifdef IPS_POLLING
	ret = smx_status_polling();
        if(ret) {
                printf("smx module smx_status_polling for sm3 failed! \n");
		return -1;
	}
	#endif

	tmp_pt =(unsigned long long *)pdst;
        tmp_ppt = (unsigned char*)tmp_pt[0];

	#ifdef DEBUG_PRINT
	 if(alg_flag == SM3_DDT_FLAG){
                printf("pdst = %llx \n",pdst);
                printf("pdst[0] = %llx \n", tmp_pt[0]);
                printf("pdst[1] = %llx \n", tmp_pt[1]);

                for(i=proc_len; i<(tmp_pt[1]+proc_len); i++)
                        printf("pdst[i] =%x \n", tmp_ppt[i]);
        }

        for(i=0; i<outlen; i++)
                printf("dgst = %x \n",dgst[i]);
	#endif
	ret = str_cmp(tmp_ppt+proc_len,dgst,outlen);
        if(!ret)
		return 0;
	else {
                printf("sm3 result between engine and sw are different");
		return -1;
	}
}

int se_smx_sm3_ddt()
{
	int ret;
	int i;
	unsigned long long *ddt_src;
        unsigned long long *ddt_dst;
	unsigned char src[] = "abc";
	int len = 3;
	unsigned char *psrc;
	unsigned char *pdst;

	ddt_src = (unsigned long long*)SMX_DDT_SRC;
        ddt_dst = (unsigned long long*)SMX_DDT_DST;

	psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);

	ddt_src[0] = SMX_SRC_BASE;
        ddt_src[1] = 0x3;
        ddt_src[2] = 0x0;
        ddt_src[3] = 0x0;

        ddt_dst[0] = SMX_DST_BASE;
        ddt_dst[1] = 0x23;
        ddt_dst[2] = 0x0;
        ddt_dst[3] = 0x0;

	memcpy(psrc,src,len);
	memset(pdst,0, 0x23);
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
	ret = sm3_function_ddt_test((unsigned char*)ddt_src,(unsigned char*)(ddt_dst), SM3_DDT_FLAG, ENCRYPT, len);
	if(!ret){
		 	printf("sm3-ddt alg case pass! \n");
			return 0;
		}
		else {
		 	printf("sm3-ddt alg case failed! \n");
			return -1;
		}

	/*disable channel*/
	/*
	WRITE_REG(SMX_VF0_REG_RING_INIT_0,0);
        ret = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret){
                printf("channel 0 disable failed \n");
                return -1;
         }else
		printf("channel 0 disable success \n");
	*/
	return 0;
}


int se_smx_sm3_multi_ddt()
{
        int ret;
        int i;
        unsigned long long *ddt_src;
        unsigned long long *ddt_dst;
        unsigned char src[] = "abc";
        int len = 3;
        unsigned char *psrc;
	unsigned char *psrc1;
        unsigned char *pdst;

        ddt_src = (unsigned long long*)SMX_DDT_SRC;
        ddt_dst = (unsigned long long*)SMX_DDT_DST;

        psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
	psrc1 = (unsigned char*)(SMX_SRC_BASE + 0x100);
        pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);


	ddt_src[0] = SMX_SRC_BASE;
        ddt_src[1] = 0x1;
        ddt_src[2] = SMX_SRC_BASE+0x100;
        ddt_src[3] = 0x2;
        ddt_src[4] = 0x0;
        ddt_src[5] = 0x0;

        ddt_dst[0] = SMX_DST_BASE;
        ddt_dst[1] = 0x23;
        ddt_dst[2] = 0x0;
        ddt_dst[3] = 0x0;

        memcpy(psrc,src,1);
	memcpy(psrc1,src+1,2);
	memset(pdst,0,0x23);
        ret = smx_init_clk();
        if(!ret)
                printf("smx module clock case pass! \n");
        else
                return -1;
        ret = smx_module_reset();
        if(!ret)
                printf("smx module reset case pass! \n");
        else {
		printf("reset failed! \n");
	       return -1;

	}
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
        ret = sm3_function_ddt_test((unsigned char*)ddt_src,(unsigned char*)(ddt_dst), SM3_DDT_FLAG, ENCRYPT, len);
        if(!ret){
                        printf("sm3-multi-ddt alg case pass! \n");
                        return 0;
                }
                else {
                        printf("sm3-multi-ddt alg case failed! \n");
                        return -1;
                }

	  /*disable channel*/
	/*
        WRITE_REG(SMX_VF0_REG_RING_INIT_0,0);
        ret = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret){
                printf("channel 0 disable failed \n");
                return -1;
        }else
		printf("channel 0 disable success");
	*/

        return 0;
}




int sm4_function_ddt_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sm4_mode,  int proc_len)
{
        int i;
        int ret;
        int outlen=16;
	unsigned char sm4_src[16] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char sm4_key[16] =  {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char sm4_iv[16] = {0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};
	unsigned char sm4_dst_ecb[16] = {0x68,0x1e,0xdf,0x34,0xd2,0x06,0x96,0x5e,0x86,0xb3,0xe9,0x4f,0x53,0x6e,0x42,0x46};

	unsigned char *tmp_ppt;
        unsigned char *tmp_ppt1;
        unsigned char ddt_dst[16] = {0x0};
        unsigned long long *ddt_src;
        unsigned long long *tmp_pt;
        unsigned long long *src_pt;
        unsigned char *ppt_src;

        unsigned long long*pt;
        unsigned char *ppt;
        unsigned char *ppt1;
        unsigned char tmp_src[0x10];


	ddt_src = (unsigned long long*)(SMX_DDT_SRC+0x800);
        ppt_src = (unsigned char*)(SMX_SRC_BASE+0x1000);
        ddt_src[0] = (SMX_SRC_BASE + 0x1000);
        ddt_src[1] = 0x10;
        ddt_src[2] = 0x0;
        ddt_src[3] = 0x0;


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
       	printf("psrc = %x \n", psrc);
        printf("pt[0] = %x \n",pt[0]);
        printf("pt[1] = %x \n", pt[1]);
        for(i=0; i<pt[1]; i++)
               printf("ppt = %x \n", ppt[i]);
        for(i=0; i<pt[3]; i++)
               printf("ppt = %x \n", ppt1[i]);
        #endif

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
	tmp_pt = (unsigned long long*)pdst;
        tmp_ppt = (unsigned char*)tmp_pt[0];
        memcpy(ddt_dst,tmp_ppt,tmp_pt[1]);
        if(tmp_pt[2] != 0){
                tmp_ppt1 = (unsigned char*)tmp_pt[2];
                memcpy(ddt_dst + tmp_pt[1],tmp_ppt1,tmp_pt[3]);
        }

        #ifdef DEBUG_PRINT
	printf("pdst = %x \n",pdst);
        printf("pdst[0] = %x \n", tmp_pt[0]);
        printf("pdst[1] = %x \n", tmp_pt[1]);
        for(i=0; i<tmp_pt[1]; i++)
               printf("tmp_pt = %x \n", tmp_ppt[i]);

        #endif
	memset(ppt_src, 0x0, 0x10);
        /*2. hw decrypt*/
        ret = smx_cmd_create(pdst, (unsigned char*)ddt_src, alg_flag, sm4_mode, DECRYPT, proc_len);
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

	ppt_src = (unsigned char*)ddt_src[0];
        #ifdef DEBUG_PRINT
	printf("ddt_src = %llx \n",ddt_src);
        printf("ddt_src[0] = %llx \n", ddt_src[0]);
        printf("ddt_src[1] = %llx \n", ddt_src[1]);

        for(i=0; i<ddt_src[1]; i++)
                printf("ppt_src = %x \n", ppt_src[i]);

        #endif

        ret = str_cmp(tmp_src, ppt_src, proc_len);
        if(ret) {
                printf("decrypt data and source data are different!\n");
                return -1;
        } else
                printf("decrypt data is the same as source data!\n");


        ret = str_cmp(ddt_dst,sm4_dst_ecb,outlen);
        if(ret){
                printf("encrypt data and standard data are different! \n");
                return -1;
        } else
                printf("encrypt data is the same as standard data! \n");




        return 0;

}


int se_smx_sm4_ddt()
{
        int ret;
        int i;
        int len = 16;
	unsigned long long *ddt_src;
        unsigned long long *ddt_dst;
        unsigned char *psrc;
        unsigned char *pdst;
	unsigned char sm4_src[16] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
        unsigned char sm4_key[16] =  {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
        unsigned char sm4_iv[16] = {0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};

	ddt_src = (unsigned long long*)SMX_DDT_SRC;
        ddt_dst = (unsigned long long*)SMX_DDT_DST;
        psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
        pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);
        memcpy(psrc,sm4_src,len);

	ddt_src[0] = SMX_SRC_BASE;
        ddt_src[1] = 0x10;
        ddt_src[2] = 0x0;
        ddt_src[3] = 0x0;

        ddt_dst[0] = SMX_DST_BASE;
        ddt_dst[1] = 0x10;
        ddt_dst[2] = 0x0;
        ddt_dst[3] = 0x0;
        memcpy(psrc,sm4_src,len);
	memset(pdst,0,0x10);
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
        ret = sm4_function_ddt_test((unsigned char*)ddt_src, (unsigned char*)(ddt_dst), SM4_DDT_FLAG, ECB_MODE, len);
        if(!ret){
                        printf("sm4_ecb ddt mode case pass! \n");
                }
                else{
                         printf("sm4-ecb ddt mode case failed! \n");
                         return -1;
                }

	  /*disable channel*/
	/*
        WRITE_REG(SMX_VF0_REG_RING_INIT_0,0);
        ret = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret){
                printf("channel 0 disable failed \n");
                return -1;
        }
	else
		printf("channel 0 disable failed");
	*/

	return 0;

}


int se_smx_sm4_multi_ddt()
{
        int ret;
        int i;
        int len = 16;
        unsigned long long *ddt_src;
        unsigned long long *ddt_dst;
	unsigned char *psrc;
        unsigned char *psrc1;
        unsigned char *pdst;
        unsigned char *pdst1;

        unsigned char sm4_src[16] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
        unsigned char sm4_key[16] =  {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
        unsigned char sm4_iv[16] = {0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};

        ddt_src = (unsigned long long*)SMX_DDT_SRC;
        ddt_dst = (unsigned long long*)SMX_DDT_DST;
        psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
        pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);
        psrc1 = (unsigned char*)(SMX_SRC_BASE+0x100); //0x50000; //heap_alloc(32);
        pdst1 = (unsigned char*)(SMX_DST_BASE+0x100); //0x60000; //heap_alloc(32);
	ddt_src[0] = SMX_SRC_BASE;
        ddt_src[1] = 0x08;
        ddt_src[2] = SMX_SRC_BASE + 0x100;
        ddt_src[3] = 0x08;
        ddt_src[4] = 0x0;
        ddt_src[5] = 0x0;

        ddt_dst[0] = SMX_DST_BASE;
        ddt_dst[1] = 0x08;
        ddt_dst[2] = SMX_DST_BASE + 0x100;
        ddt_dst[3] = 0x08;
        ddt_dst[4] = 0x0;
        ddt_dst[5] = 0x0;
        memcpy(psrc,sm4_src,8);
	memcpy(psrc1,sm4_src+8,8);
	memset(pdst,0x0,0x08);
	memset(pdst1,0x0,0x08);
        ret = smx_init_clk();
        if(!ret)
                printf("smx module clock case pass! \n");
        else
                return -1;

        ret = smx_module_reset();
        if(!ret)
                printf("smx module reset case pass! \n");
        else{
        	printf("smx reset failed! \n");
	       return -1;
	}

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
        ret = sm4_function_ddt_test((unsigned char*)ddt_src, (unsigned char*)(ddt_dst), SM4_DDT_FLAG, ECB_MODE, len);
        if(!ret){
                        printf("sm4_ecb multi-ddt mode case pass! \n");
                }
                else{
                         printf("sm4-ecb multi-ddt mode case failed! \n");
                         return -1;
                }

	  /*disable channel*/
	/*
        WRITE_REG(SMX_VF0_REG_RING_INIT_0,0);
        ret = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret){
                printf("channel 0 disable failed \n");
                return -1;
        }else
		printf("channel 0 disable success\n");
	*/

        return 0;

}

