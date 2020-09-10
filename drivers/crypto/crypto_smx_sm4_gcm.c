#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
#define IPS_POLLING
//#define DEBUG_PRINT


unsigned char sm4_gcm_src[60] = {0xd9,0x31,0x32,0x25,0xf8,0x84,0x06,0xe5,0xa5,0x59,0x09,0xc5,0xaf,0xf5,0x26,0x9a,0x86,0xa7,0xa9,0x53,0x15,0x34,0xf7,0xda,0x2e,0x4c,0x30,0x3d,0x8a,0x31,0x8a,0x72,0x1c,0x3c,0x0c,0x95,0x95,0x68,0x09,0x53,0x2f,0xcf,0x0e,0x24,0x49,0xa6,0xb5,0x25,0xb1,0x6a,0xed,0xf5,0xaa,0x0d,0xe6,0x57,0xba,0x63,0x7b,0x39 };
unsigned char sm4_gcm_key[16] = {0xfe,0xff,0xe9,0x92,0x86,0x65,0x73,0x1c,0x6d,0x6a,0x8f,0x94,0x67,0x30,0x83,0x08};
unsigned char sm4_gcm_iv[16] = {0xca,0xfe,0xba,0xbe,0xfa,0xce,0xdb,0xad,0xde,0xca,0xf8,0x88,0x0,0x0,0x0,0x1};
unsigned char sm4_pre_aad[20] = {0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xfe,0xed,0xfa,0xce,0xde,0xad,0xbe,0xef,0xab,0xad,0xda,0xd2};
unsigned char gcm_dst[60]={0xe4,0x11,0x0f,0xf1,0xc1,0x41,0x97,0xe6,0x76,0x21,0x6a,0x33,0x83,0x10,0x41,0xeb,0x09,0x58,0x00,0x11,0x7b,
			0xdc,0x3f,0x75,0x1a,0x49,0x6e,0xfc,0xf2,0xbb,0xdf,0xdb,0x3a,0x2e,0x13,0xfd,0xc5,0xc1,0x9d,0x07,0x1a,0xe5,0x48,
			0x3f,0xed,0xde,0x98,0x5d,0x3f,0x2d,0x5b,0x4e,0xee,0x0b,0xb6,0xdf,0xe3,0x63,0x36,0x83};

unsigned char gcm_tag[16]={0x89,0xf6,0xba,0x35,0xb8,0x18,0xd3,0xcc,0x38,0x6c,0x05,0xb3,0x8a,0xcb,0xc9,0xde};

int sm4_gcm_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sm4_mode,  int proc_len)
{
        int i;
        int ret;
        int outlen=96;

	memset(pdst,0,0x100);
        memset(psrc+0x1000,0,0x100);
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
	ret = str_cmp(psrc,(psrc+0x1000),20 );
        if(ret){
                        printf("aad data not consistent! \n");
                        return -1;
                }
        ret = str_cmp((psrc+20), (psrc+0x1014),60);
        if(ret){
                        printf("decrypt data and source data are different!\n");
                        return -1;
                }
		 else
                	printf("decrypt data is the same as source data!\n");


	ret = str_cmp(psrc,pdst, 20);
        if(ret){
                        printf("aad data not consistent! \n");
                        return -1;
                }
        ret = str_cmp(pdst+20, gcm_dst, 60);
        if(ret){
                        printf("encrypt data and standard data are different!\n");
                        return -1;
                }
	else
                        printf("encrypt data is the same as the standard data!\n");

        ret = str_cmp(pdst+80, gcm_tag, 16);
        if(ret) {
                        printf("tag is not consistent! \n");
                        return -1;

                }



        return 0;
}



int se_smx_sm4_gcm()
{
        int ret;
        int i;

        int len = 80;
        unsigned char *psrc;
        unsigned char *pdst;
        psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
        pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);
	memcpy(psrc, sm4_pre_aad, 20);
        memcpy(psrc+20,sm4_gcm_src,len);
        ret = smx_init_clk();
        if(!ret)
                printf("smx module clock case pass! \n");

        ret = smx_module_reset();
        if(!ret)
                printf("smx module reset case pass! \n");
        ret = smx_dev_init();
        if(!ret)
                printf("smx module initialzie case pass! \n");
        ret = smx_key_iv_set(sm4_gcm_key,sm4_gcm_iv);
        if(!ret)
                printf("smx module key_iv set case pass \n");

 /***********************calculate sme-gcm********************************/

        ret = sm4_gcm_test(psrc, pdst, SM4_FLAG, GCM_MODE, len);
        if(!ret){
                        printf("sm4-gcm mode case pass! \n");
                }
                else{
                        printf("sm4-gcm mode case failed! \n");
                        return -1;
                }

	return 0;
}



