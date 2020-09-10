#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include "target/sim_trigger.h"
//#define DEBUG_PRINT
#define IPS_POLLING
int str_cmp(unsigned char *str1, unsigned char *str2, int len)
{
	int i;
	int ret;
	for(i=0; i<len; i++)
	{
		if(str1[i] != str2[i])
		{
		printf("i =%d \n", i);
		printf("str[i] =%x \n", str1[i]);
		printf("str[i]=%x \n", str2[i]);
		break;
		}
	}
	if(i != len)
	{
		return -1;
	}
	else
		return 0;
}
int sha_function_raw_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sha_flag, int ende_flag, int proc_len)
{
	int i;
	int ret;
	int outlen;
	unsigned long long *tmp_pt;
	unsigned char *tmp_ppt;
	unsigned char dgst[0x40] = {0x0};
	unsigned char dgst_1[20] = {0xa9,0x99,0x3e,0x36,0x47,0x06,0x81,0x6a,0xba,0x3e,0x25,0x71,0x78,0x50,0xc2,0x6c,0x9c,0xd0,0xd8,0x9d};
	unsigned char dgst_224[28] = {0x23,0x09,0x7d,0x22,0x34,0x05,0xd8,0x22,0x86,0x42,0xa4,0x77,0xbd,0xa2,0x55,0xb3,0x2a,0xad,0xbc,0xe4,
					0xbd,0xa0,0xb3,0xf7,0xe3,0x6c,0x9d,0xa7};
	unsigned char dgst_256[32] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea, 0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,0xb0,0x03,0x61,
							0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
	unsigned char dgst_384[48] = {0xcb,0x00,0x75,0x3f,0x45,0xa3,0x5e,0x8b,0xb5,0xa0,0x3d,0x69,0x9a,0xc6,0x50,0x07,0x27,0x2c,0x32,0xab,
					0x0e,0xde,0xd1,0x63,0x1a,0x8b,0x60,0x5a,0x43,0xff,0x5b,0xed,0x80,0x86,0x07,0x2b,0xa1,0xe7,0xcc,0x23,0x58,0xba,0xec,0xa1,0x34,0xc8,0x25,0xa7};
	unsigned char dgst_512[64] = {0xdd,0xaf,0x35,0xa1,0x93,0x61,0x7a,0xba,0xcc,0x41,0x73,0x49,0xae,0x20,0x41,0x31,0x12,
				     0xe6,0xfa,0x4e,0x89,0xa9,0x7e,0xa2,0x0a,0x9e,0xee,0xe6,0x4b,0x55,0xd3,0x9a,0x21,0x92,0x99,
				     0x2a,0x27,0x4f,0xc1,0xa8,0x36,0xba,0x3c,0x23,0xa3,0xfe,0xeb,0xbd,0x45,0x4d,0x44,0x23,0x64,
				     0x3c,0xe8,0x0e,0x2a,0x9a,0xc9,0x4f,0xa5,0x4c,0xa4,0x9f};
	unsigned char dgst_512_224[28]={0x46,0x34,0x27,0x0f,0x70,0x7b,0x6a,0x54,0xda,0xae,0x75,0x30,0x46,0x08,0x42,0xe2,0x0e,0x37,0xed,0x26,0x5c,0xee,0xe9,0xa4,0x3e,0x89,0x24,0xaa};
	unsigned char dgst_512_256[32]={0x53,0x04,0x8e,0x26,0x81,0x94,0x1e,0xf9,0x9b,0x2e,0x29,0xb7,0x6b,0x4c,0x7d,0xab,0xe4,0xc2,0xd0,0xc6,0x34,0xfc,0x6d,0x46,0xe0,0xe2,0xf1,0x31,0x07,0xe7,0xaf,0x23};
	switch(sha_flag)
	{
		case SHA_1:
			outlen = 20;
			memcpy(dgst,dgst_1,outlen);
		break;
		case SHA_224:
			outlen = 28;
			memcpy(dgst,dgst_224,outlen);
		break;
		case SHA_256:
			outlen = 32;
			memcpy(dgst,dgst_256,outlen);
		break;
		case SHA_384:
			outlen = 48;
			memcpy(dgst,dgst_384,outlen);
		break;
		case SHA_512:
			outlen = 64;
			memcpy(dgst,dgst_512,outlen);
		break;
		case SHA_512_224:
			outlen = 28;
			memcpy(dgst,dgst_512_224,outlen);
		break;
		case SHA_512_256:
			outlen = 32;
			memcpy(dgst,dgst_512_256,outlen);
		break;
		default:
		break;
	}
	#ifdef DEBUG_PRINT
	if(alg_flag == SHA_DDT_FLAG)
	{
		unsigned long long*pt;
		unsigned char *ppt;
		unsigned int ret_value;
		printf("psrc = %llx \n", psrc);
		pt = (unsigned long long*)psrc;
		printf("pt[0] = %llx \n",pt[0]);
		printf("pt[1] = %llx \n", pt[1]);
		ppt = (unsigned char *)pt[0];
		for(i=0; i<pt[1]; i++)
			printf("ppt = %x \n", ppt[i]);
	}
	#endif


	ret = ips_cmd_create(psrc, pdst, alg_flag, sha_flag, HASH_RAW_MODE, ende_flag, proc_len);
        if(ret) {
                printf("ips module--ips_cmd_create for sha failed!");
		return -1;
	}
	#ifdef IPS_POLLING
	ret = ips_status_polling();
        if(ret) {
                printf("ips module ips_status_polling for sha failed! \n");
		return -1;
	}
	#endif

	tmp_pt =(unsigned long long *)pdst;
	tmp_ppt = (unsigned char*)tmp_pt[0];
	#ifdef DEBUG_PRINT
	if(alg_flag == SHA_DDT_FLAG){
		printf("pdst = %llx \n",pdst);
		printf("pdst[0] = %llx \n", tmp_pt[0]);
		printf("pdst[1] = %llx \n", tmp_pt[1]);
		for(i=proc_len; i<(tmp_pt[1]+proc_len); i++)
		  	printf("pdst[i] =%x \n", tmp_ppt[i]);
	}else
	{
        	for(i=proc_len; i<outlen+proc_len; i++)
                	printf("pdst[i] =%x \n", pdst[i]);
	}
        for(i=0; i<outlen; i++)
                printf("dgst = %x \n",dgst[i]);
	#endif
	if(alg_flag == SHA_DDT_FLAG)
		ret = str_cmp(tmp_ppt+proc_len,dgst,outlen);
	else
        	ret = str_cmp((pdst+proc_len), dgst, outlen);
        if(!ret)
		return 0;
	else {
                printf("sha result between engine and sw are different");
		return -1;
	}
}
int sha_function_hmac_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sha_flag, int ende_flag, int proc_len)
{
        int i;
        int ret;
        int outlen;
	int keylen = 32;
        unsigned char dgst[0x40] = {0x0};
	unsigned char dgst_128[20]={0x68,0xf9,0xd1,0xc6,0x5a,0xe2,0xdd,0xe4,0x3a,0x13,0x45,0x15,0xc8,0x38,0x13,0xa9,0x69,0x85,0xcb,0xe3};
	unsigned char dgst_224[28]={0x11,0xe6,0x0,0x25,0x56,0xca,0x1a,0x15,0xb6,0x73,0xa3,0x49,0x52,0x12,0x7e,0x4c,0xa3,0x8a,0x18,0x8b,
					0x39,0xdc,0x5e,0xfc,0x0a,0xe4,0x53,0xf5};
	unsigned char dgst_256[32]={0x19,0x8a,0x60,0x7e,0xb4,0x4b,0xfb,0xc6,0x99,0x03,0xa0,0xf1,0xcf,0x2b,0xbd,0xc5,
                      			0xba,0x0a,0xa3,0xf3,0xd9,0xae,0x3c,0x1c,0x7a,0x3b,0x16,0x96,0xa0,0xb6,0x8c,0xf7};
	unsigned char dgst_384[48]={0xc3,0xf1,0x61,0x59,0x43,0xd1,0xdd,0x07,0xa8,0x3b,0xb6,0x44,0xb9,0x7f,0xb3,0xdc,0x2b,
					0x8a,0x93,0x6a,0xa5,0x38,0x9d,0xe2,0xa3,0xe9,0xdd,0x91,0xbc,0x3b,0xae,0x0d,0x0c,0x30,
					0x33,0x4a,0x30,0x17,0x33,0xaa,0x54,0xed,0x5e,0x1f,0x07,0x69,0xe8,0x68};
	unsigned char dgst_512[64]={0xcf,0x76,0x8c,0x6f,0xd3,0xf0,0x8f,0x64,0x0f,0x77,0x9d,0xdb,0xd9,0xbc,0x38,0x42,0xfe,0x78,0xa2,0x61,
					0xf1,0x97,0xda,0x9c,0x4a,0x95,0x85,0x10,0xac,0x82,0x26,0xdb,0x6b,0x05,0x9f,0x6d,0xe7,0x34,0x04,
					0x09,0xed,0x8d,0xde,0xd4,0x46,0x66,0xa6,0x3d,0xcd,0x5f,0xc6,0x69,0xfc,0x89,0xb5,0x02,0x92,0x78,
					0x1e,0x39,0x36,0x2d,0xcb,0x58};
	unsigned char dgst_hmac_224[28]={0x3f,0x06,0xcb,0xd1,0x2d,0x3e,0x20,0x9a,0x8b,0x10,0x97,0x6f,0xda,0x8e,0x87,0x92,0x48,0xe1,0x3a,						0x74,0x0e,0xd8,0x7b,0x87,0x0,0x46,0x41,0x94};
        unsigned char dgst_hmac_256[32]={0xaa,0xa0,0xfd,0xd1,0xd8,0x01,0x61,0x34,0x42,0x7d,0x29,0xc7,0x23,0xfd,0xbb,0x4d,0x6d,0xc5,0x54,0x03,0x63,0x6b,0x0c,0x44,0xb8,0xb8,0x6e,0x43,0xfe,0x95,0x51,0xe3};

	switch(sha_flag)
        {
                case SHA_1:
                         outlen = 20;
			 memcpy(dgst,dgst_128,outlen);
                break;
                case SHA_224:
                        outlen = 28;
			memcpy(dgst,dgst_224,outlen);
                break;
                case SHA_256:
                        outlen = 32;
			memcpy(dgst,dgst_256,outlen);
                break;
                case SHA_384:
                        outlen = 48;
			memcpy(dgst,dgst_384,outlen);
                break;
                case SHA_512:
                        outlen = 64;
			memcpy(dgst,dgst_512,outlen);
                break;
                case SHA_512_224:
                        outlen = 28;
                        memcpy(dgst,dgst_hmac_224,outlen);
                break;
                case SHA_512_256:
                        outlen = 32;
                        memcpy(dgst,dgst_hmac_256,outlen);
                break;
                default:
                break;
        }

        ret = ips_cmd_create(psrc, pdst, alg_flag, sha_flag, HASH_HMAC_MODE, ende_flag, proc_len);
        if(ret) {
                printf("ips module--ips_cmd_create for sha failed!");
                return -1;
        }
	#ifdef IPS_POLLING
        ret = ips_status_polling();
        if(ret) {
                printf("ips module ips_status_polling for sha failed! \n");
                return -1;
        }
	#endif
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
int se_ips_sharaw()
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
	ret = sha_function_raw_test(psrc, pdst, SHA_FLAG,SHA_1, ENCRYPT, len);
	if(!ret){
		sim_finish();
		printf("sha1 raw mode case pass! \n");
	}
	else {
		sim_fail();
		printf("sha1 raw mode case failed! \n");
		return -1;
	}
	/*************************sha224 alg**********************************************/
	ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_224, ENCRYPT, len);
	if(!ret){
		 sim_finish();
		 printf("sha224 raw mode case pass! \n");
	}
	else{
		sim_fail();
		printf("sha224 raw mode case failed! \n");
		return -1;
	}
	/*************************sha256 alg**********************************************/
	ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_256, ENCRYPT, len);
	if(!ret){
		sim_finish();
		 printf("sha256 raw mode case pass! \n");
	}
	else{
		 sim_fail();
		 printf("sha256 raw mode case failed! \n");
		return -1;
	}
	/*************************sha384 alg**********************************************/
	ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_384, ENCRYPT, len);
	if(!ret){
		 sim_finish();
		 printf("sha384 raw mode case pass! \n");
	}
	else{
		 sim_fail();
		 printf("sha384 raw mode case failed! \n");
		return -1;
	}
	/*************************sha512 alg**********************************************/
	ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_512, ENCRYPT, len);
	if(!ret){
		 sim_finish();
		 printf("sha512 raw mode case pass! \n");
	}
	else{
		sim_fail();
		printf("sha512 raw mode case failed! \n");
		return -1;
	}
      /*************************sha512_224 alg**********************************************/
	ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_512_224, ENCRYPT, len);
	if(!ret){
		 sim_finish();
		 printf("sha512_224 raw mode case pass! \n");
	}
	else{
		 sim_fail();
		 printf("sha512_224 raw mode case failed! \n");
		return -1;
	}
      /*************************sha512_256 alg**********************************************/
	ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_512_256, ENCRYPT, len);
	if(!ret) {
		 sim_finish();
		 printf("sha512_256 raw mode case pass! \n");
	}
	else{
		sim_fail();
		printf("sha512_256 raw mode case failed! \n");
		return -1;
		}


	return 0;

}


int se_ips_shahmac()
{
	int ret;
        int i;
        unsigned char src[] = "Hi There"; //""what do ya want for nothing?"; //""abc";
        int len = 8; //8; //28; //0x03;
        unsigned char *psrc;
        unsigned char *pdst;
	unsigned char key[32];
	unsigned char iv[16];
	unsigned char hashkey[32];
        psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
        pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);
	memset(hashkey,0x0b,32);
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
        ret = ips_key_iv_set(key, 0,iv,hashkey,32);
        if(!ret){
		sim_finish();
                printf("ips module key_iv set case pass \n");
	}else
		return -1;


 	/*************************sha1 alg for hmac********************************************/
        ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG,SHA_1, ENCRYPT, len);
        if(!ret){
		sim_finish();
                printf("sha1 hmac mode case pass! \n");
         }
         else {
		sim_fail();
                printf("sha1 hmac mode case failed! \n");
                return -1;
         }
        /*************************sha224 alg for hmac**********************************************/
        ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_224, ENCRYPT, len);
        if(!ret){
		 sim_finish();
                 printf("sha224 hmac mode case pass! \n");
         }
        else{
		 sim_fail();
                 printf("sha224 hmac mode case failed! \n");
                 return -1;
        }
        /*************************sha256 alg for hmac**********************************************/
        ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_256, ENCRYPT, len);
        if(!ret){
		 sim_finish();
                 printf("sha256 hmac mode case pass! \n");
         }
        else{
		 sim_fail();
                 printf("sha256 hmac mode case failed! \n");
                 return -1;
        }
        /*************************sha384 alg for hmac**********************************************/
         ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_384, ENCRYPT, len);
         if(!ret){
		 sim_finish();
                 printf("sha384 hmac mode case pass! \n");
           }
         else{
		 sim_fail();
                 printf("sha384 hmac mode case failed! \n");
                 return -1;
         }
        /*************************sha512 alg for hmac**********************************************/
         ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_512, ENCRYPT, len);
         if(!ret){
		 sim_finish();
                 printf("sha512 hmac mode case pass! \n");
          }
          else{
		 sim_fail();
                 printf("sha512 hmac mode case failed! \n");
                 return -1;
          }
      /*************************sha512_224 alg for hmac**********************************************/
         ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_512_224, ENCRYPT, len);
         if(!ret){
		  sim_finish();
                  printf("sha512_224 hmac mode case pass! \n");
          }

          else{
		  sim_fail();
                  printf("sha512_224 hmac mode case failed! \n");
                  return -1;
          }
      /*************************sha512_256 alg for hmac**********************************************/
          ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_512_256, ENCRYPT, len);
          if(!ret) {
		   sim_finish();
                   printf("sha512_256 hmac mode case pass! \n");
           }
           else{
		   sim_fail();
                   printf("sha512_256 hmac mode case failed! \n");
                    return -1;
           }

	return 0;
}
