#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
#define IPS_POLLING
//#define DEBUG_PRINT


int sm4_function_cts_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sm4_mode,  int proc_len)
{
        int i;
        int ret;
        int outlen=17;

	unsigned char sm4_dst_cs1[17] = {0x3f,0x26,0x98,0xf7,0xc8,0xa2,0x68,0x8b,0x2e,0xbe,0xb5,0x7e,0x17,0xb8,0x5f,0x68,0x2};
	unsigned char sm4_dst_cs2[17] = {0x26,0x98,0xf7,0xc8,0xa2,0x68,0x8b,0x2e,0xbe,0xb5,0x7e,0x17,0xb8,0x5f,0x68,0x02,0x3f};
	unsigned char sm4_dst_cs3[17] = {0x26,0x98,0xf7,0xc8,0xa2,0x68,0x8b,0x2e,0xbe,0xb5,0x7e,0x17,0xb8,0x5f,0x68,0x02,0x3f};
        unsigned char dst[17] = {0x0};
	memset(pdst,0,0x100);
        memset(psrc+0x1000,0,0x100);


        switch(sm4_mode)
        {

                case CBC_CS1_MODE:
                        memcpy(dst,sm4_dst_cs1,outlen);
                break;

                case CBC_CS2_MODE:
                        memcpy(dst,sm4_dst_cs2,outlen);
                break;

                case CBC_CS3_MODE:
                        memcpy(dst,sm4_dst_cs3,outlen);
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




int se_smx_sm4_cts()
{
        int ret;
        int i;

	unsigned char sm4_src_cts[17] =  {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0x20};
	//unsigned char sm4_src_cts[17] = {0xc8,0xe5,0xfa,0x58,0xb7,0x15,0xf2,0x7f,0x63,0x3e,0xb9,0x58, 0x95,0x12,0xbc,0xec,0x49};
	unsigned char sm4_key[16] =  {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char sm4_iv[16] = {0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};
        int len = 17;
        unsigned char *psrc;
        unsigned char *pdst;
        psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
        pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);
        memcpy(psrc,sm4_src_cts,len);
        ret = smx_init_clk();
        if(!ret)
                printf("smx module clock case pass! \n");

        ret = smx_module_reset();
        if(!ret)
                printf("smx module reset case pass! \n");
        ret = smx_dev_init();
        if(!ret)
                printf("smx module initialzie case pass! \n");
        ret = smx_key_iv_set(sm4_key,sm4_iv);
        if(!ret)
                printf("smx module key_iv set case pass \n");

	/************************cbc_cs1********************************/
         ret = sm4_function_cts_test(psrc, pdst, SM4_FLAG, CBC_CS1_MODE, len);
         if(!ret){
                        printf("sm4_cbc_cs1 mode case pass! \n");
                }
                else{
                        printf("sm4_cbc_cs1 mode case failed! \n");
                        //return -1;
                }
	/**************************cbc_cs2********************************/

        ret = smx_key_iv_set(sm4_key,sm4_iv);
        if(!ret)
                printf("ips module key_iv set case pass \n");
         ret = sm4_function_cts_test(psrc, pdst, SM4_FLAG, CBC_CS2_MODE, len);
         if(!ret){
                        printf("sm4_cbc_cs2 mode case pass! \n");
                }
                else{
                        printf("sm4_cbc_cs2 mode case failed! \n");
                        //return -1;
                }
	/******************************cbc_cs3**************************/

        ret = smx_key_iv_set(sm4_key,sm4_iv);
        if(!ret)
                printf("ips module key_iv set case pass \n");
         ret = sm4_function_cts_test(psrc, pdst, SM4_FLAG, CBC_CS3_MODE, len);
         if(!ret){
                        printf("sm4_cbc_cs3 mode case pass! \n");
                }
                else{
                        printf("sm4_cbc_cs3 mode case failed! \n");
                        //return -1;
                }
	return 0;
}



