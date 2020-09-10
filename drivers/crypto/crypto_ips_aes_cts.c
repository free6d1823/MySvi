#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
#define IPS_POLLING
//#define DEBUG_PRINT

        unsigned char src_cts[17] = {0x49, 0x20, 0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x6c, 0x69,0x6b, 0x65, 0x20, 0x74,0x68,0x65,0x20};
	//unsigned char src_cts[31]={0x49,0x20,0x77,0x6f,0x75,0x6c,0x64,0x20,0x6c,0x69,0x6b,0x65,0x20,0x74,0x68,0x65,0x20,0x47,0x65,0x6e,0x65,0x72,0x61,0x6c,0x20,0x47,0x61,0x75,0x27,0x73,0x20};
	unsigned char key_128cts[16] = {0x63,0x68,0x69,0x63,0x6b,0x65,0x6e,0x20,0x74,0x65,0x72,0x69,0x79,0x61,0x6b,0x69};
	unsigned char key_192cts[24] = {0x63,0x68,0x69,0x63,0x6b,0x65,0x6e,0x20,0x74,0x65,0x72,0x69,0x79,0x61,0x6b,0x69,0x63,0x68,0x69,0x63,0x6b,0x65,0x6e,0x20};
	unsigned char key_256cts[32] = {0x63,0x68,0x69,0x63,0x6b,0x65,0x6e,0x20,0x74,0x65,0x72,0x69,0x79,0x61,0x6b,0x69,0x63,0x68,0x69,0x63,0x6b,0x65,0x6e,0x20,0x74,0x65,0x72,0x69,0x79,0x61,0x6b,0x69};
	unsigned char iv_128cts[16] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};
	unsigned char iv_192256cts[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
	#if 1
        unsigned char dst_cbc_cs1_128[17] = {0x97,0xc6,0x35,0x35,0x68,0xf2,0xbf,0x8c,0xb4,0xd8,0xa5,0x80,0x36,0x2d,0xa7,0xff,0x7f};
        unsigned char dst_cbc_cs23_128[17] = {0xc6,0x35,0x35,0x68,0xf2,0xbf,0x8c,0xb4,0xd8,0xa5,0x80,0x36,0x2d,0xa7,0xff,0x7f,0x97};
        unsigned char dst_cbc_cs1_192[17] = {0xe9,0xde,0x1b,0x40,0x2d,0xe8,0xf7,0x9f,0x94,0x7c,0xc6,0xb5,0x88,0x05,0x88,0xd9,0xb6};
        unsigned char dst_cbc_cs23_192[17] = {0xde,0x1b,0x40,0x2d,0xe8,0xf7,0x9f,0x94,0x7c,0xc6,0xb5,0x88,0x05,0x88,0xd9,0xb6,0xe9};
        unsigned char dst_cbc_cs1_256[17] = {0xe9,0x6b,0x5f,0x5a,0xbc,0x21,0xc4,0xd0,0x41,0x56,0xc7,0x38,0x50,0xda,0x3b,0xba,0x29};
        unsigned char dst_cbc_cs23_256[17] = {0x6b,0x5f,0x5a,0xbc,0x21,0xc4,0xd0,0x41,0x56,0xc7,0x38,0x50,0xda,0x3b,0xba,0x29,0xe9};
	#endif
	#if 0
	unsigned char dst_cbc_cs1_128[31] = {0x97,0x68,0x72,0x68,0xd6,0xec,0xcc,0xc0,0xc0,0x7b,0x25,0xe2,0x5e,0xcf,0xe5,0xfc,0x00,0x78,0x3e,0x0e,0xfd,0xb2,0xc1,0xd4,0x45,0xd4,0xc8,0xef,0xf7,0xed,0x22};
        unsigned char dst_cbc_cs23_128[31] = {0xfc,0x00,0x78,0x3e,0x0e,0xfd,0xb2,0xc1,0xd4,0x45,0xd4,0xc8,0xef,0xf7,0xed,0x22,0x97,0x68,0x72,0x68,0xd6,0xec,0xcc,0xc0,0xc0,0x7b,0x25,0xe2,0x5e,0xcf,0xe5};
        unsigned char dst_cbc_cs1_192[31] = {0xe9,0xde,0x17,0xd6,0x24,0x8f,0xb4,0x92,0xbd,0xea,0x1f,0xb2,0xe0,0x9c,0x8e,0xde,0xa2,0xb6,0x10,0x54,0x6f,0x3b,0x1e,0x1d,0x23,0x18,0x21,0xe2,0x83,0xe1,0x53};
        unsigned char dst_cbc_cs23_192[31] = {0xde,0xa2,0xb6,0x10,0x54,0x6f,0x3b,0x1e,0x1d,0x23,0x18,0x21,0xe2,0x83,0xe1,0x53,0xe9,0xde,0x17,0xd6,0x24,0x8f,0xb4,0x92,0xbd,0xea,0x1f,0xb2,0xe0,0x9c,0x8e};
        unsigned char dst_cbc_cs1_256[31] = {};
        unsigned char dst_cbc_cs23_256[31] = {0xf2,0x25,0x53,0xaf,0x78,0xee,0x4f,0x46,0x8f,0x02,0xfb,0xe6,0xf0,0xf2,0x16,0x8e,0xe9,0x54,0xe7,0x9f,0xae,0x93,0x10,0xdc,0x75,0xb6,0x07,0x0e,0x1d,0x62,0x53};

	#endif

static int aes_cts_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int aes_bitlen, int aes_mode,  int proc_len)
{
	int i;
	int ret;
	int outlen=17;
	unsigned char dst[32]={0x0};
	memset(pdst,0,0x100);
	memset(psrc+0x800,0,0x100);

	switch(aes_mode)
	{
		case CBC_CS1_MODE:
			if(aes_bitlen == AES_128)
				memcpy(dst,dst_cbc_cs1_128,outlen);
			if(aes_bitlen == AES_192)
				memcpy(dst,dst_cbc_cs1_192,outlen);
			if(aes_bitlen == AES_256)
				memcpy(dst,dst_cbc_cs1_256,outlen);
		break;
		case CBC_CS2_MODE:
			if(aes_bitlen == AES_128)
				memcpy(dst,dst_cbc_cs23_128,outlen);
			if(aes_bitlen ==  AES_192)
				memcpy(dst,dst_cbc_cs23_192,outlen);
			if(aes_bitlen == AES_256)
				memcpy(dst,dst_cbc_cs23_256,outlen);
		break;
		case CBC_CS3_MODE:
			if(aes_bitlen == AES_128)
				memcpy(dst,dst_cbc_cs23_128,outlen);
			if(aes_bitlen ==  AES_192)
                                memcpy(dst,dst_cbc_cs23_192,outlen);
                        if(aes_bitlen == AES_256)
                                memcpy(dst,dst_cbc_cs23_256,outlen);
		break;

		default:
		break;
	}
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
	#ifdef IPS_POLLING
        ret = ips_status_polling();
        if(ret) {
                printf("ips module-ips_status_polling for aes-decrypt failed! \n");
		return -1;
	}
	#endif
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
                printf("sw_dst = %x \n",dst[i]);
	#endif
	 ret = str_cmp(pdst, dst, outlen);
         if(ret) {
                	printf("encrypt data between engine and sw are different\n");
			return -1;
	 	}
	return 0;
}



int se_ips_aes_cts()
{
 	int ret;
        int i;
        int cts_len = 17;
        unsigned char *psrc;
        unsigned char *pdst;
        unsigned char *hashkey;
        //printf("enter into se_ips_aes \n");
        hashkey = NULL;
        psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
        pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);
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


	/*********************************calculate aes-cbc-submode******************/
        /********************************calculate aes-cbc-cs1*********************/
        memset(psrc,0,cts_len);
        memcpy(psrc,src_cts,cts_len);
        ret = ips_key_iv_set(key_128cts,16,iv_128cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;
        ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_128, CBC_CS1_MODE, cts_len);
        if(!ret){
                 printf("aes-128-cbc-cs1 mode case pass! \n");
        }
        else{
                 printf("aes-128-cbc-cs1 mode case failed! \n");
                 return -1;

        }

        /*********************************calcuate aes-cbc-cs2**************************/

   	memset(psrc,0,cts_len);
        memcpy(psrc,src_cts,cts_len);

        ret = ips_key_iv_set(key_128cts,16,iv_128cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

        ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_128, CBC_CS2_MODE, cts_len);
        if(!ret){
                 printf("aes-128-cbc-cs2 mode case pass! \n");
        }
        else{
                 printf("aes-128-cbc-cs2 mode case failed! \n");
                 return -1;

        }
        /***********************************calculate aes-cbc-cs3****************************/

        ret = ips_key_iv_set(key_128cts,16,iv_128cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

        ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_128, CBC_CS3_MODE, cts_len);
        if(!ret){
                  printf("aes-128-cbc-cs3 mode case pass! \n");
        }
        else{
                  printf("aes-128-cbc-cs3 mode case failed! \n");
                  return -1;
        }
	/*++++++++++++++++++++++++++++++++++++++++++192++++++++++++++++++++++++++++++++++++*/

   	memset(psrc,0,cts_len);
        memcpy(psrc,src_cts,cts_len);
	 /********************************calculate aes-cbc-cs1*********************/
        ret = ips_key_iv_set(key_192cts,24,iv_192256cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

        ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_192, CBC_CS1_MODE, cts_len);
        if(!ret){
                        printf("aes-192-cbc-cs1 mode case pass! \n");
                }
                else{
                        printf("aes-192-cbc-cs1 mode case failed! \n");
                        return -1;
                }

        /********************************calculate aes-cbc-cs2*********************/

        ret = ips_key_iv_set(key_192cts,24,iv_192256cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

         ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_192, CBC_CS2_MODE, cts_len);
         if(!ret){
                        printf("aes-192-cbc-cs2 mode case pass! \n");
                }
                else{
                        printf("aes-192-cbc-cs2 mode case failed! \n");
                        return -1;
                }

        /********************************calculate aes-cbc-cs3*********************/

        ret = ips_key_iv_set(key_192cts,24,iv_192256cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

        ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_192, CBC_CS3_MODE, cts_len);
        if(!ret){
                        printf("aes-192-cbc-cs3 mode case pass! \n");
                }
                else{
                        printf("aes-192-cbc-cs3 mode case failed! \n");
                        //return -1;
                }
	/*+++++++++++++++++++++++++++++++256++++++++++++++++++++++++++++++++++++++*/
	  /*****************************aes-256-cbc-cs1********************************/
   	memset(psrc,0,cts_len);
        memcpy(psrc,src_cts,cts_len);
        ret = ips_key_iv_set(key_256cts,32,iv_192256cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

        ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_256, CBC_CS1_MODE, cts_len);
        if(!ret){
                        printf("aes-256-cbc-cs1 mode case pass! \n");
                }
                else{
                        printf("aes-256-cbc-cs1 mode case failed! \n");
                        //ireturn -1;
                }
        /*******************************aes-256-cbc-cs2***************************/

        ret = ips_key_iv_set(key_256cts,32,iv_192256cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

         ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_256, CBC_CS2_MODE, cts_len);
         if(!ret){
                        printf("aes-256-cbc-cs2 mode case pass! \n");
                }
                else{
                        printf("aes-256-cbc-cs2 mode case failed! \n");
                        //return -1;
                }

        /********************************aes-256-cbc-cs3*************************/

        ret = ips_key_iv_set(key_256cts,32,iv_192256cts,hashkey,0);
        if(!ret)
                printf("ips module key_iv set case pass \n");
	else
		return -1;

          ret = aes_cts_test(psrc, pdst, AES_FLAG, AES_256, CBC_CS3_MODE, cts_len);
          if(!ret){
                        printf("aes-256-cbc-cs3 mode case pass! \n");
                }
                else{
                        printf("aes-256-cbc-cs3 mode case failed! \n");
                        return -1;
                }

	return 0;
}



