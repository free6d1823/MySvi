#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include "target/mbedtls/config.h"
#include "target/mbedtls/platform.h"
#include "target/mbedtls/aes.h"
#include "target/mbedtls/md.h"
#include "target/mbedtls/platform_util.h"
#include "target/mbedtls/sha1.h"
#include "target/mbedtls/sha256.h"
#include "target/mbedtls/sha512.h"
#include "target/mbedtls/gcm.h"
#include "target/mbedtls/cipher.h"
#define IPS_POLLING
//#define DEBUG_PRINT
#if 0
int str_cmp(unsigned char *str1, unsigned char *str2, int len)
{
        int i;
        int ret;
        for(i=0; i<len; i++)
        {
                if(str1[i] != str2[i])
                        break;
        }
        if(i != len)
                return -1;
        else
                return 0;
}
#endif
static int aes_function_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int aes_bitlen, int aes_mode,  int proc_len)
{
	int i;
	int ret;
	int outlen;
	int keylen;
	size_t offset = 0;
        unsigned char additional[]={0};
        unsigned char pt[]={0};
        unsigned char tag_buf[] = { 0x58, 0xe2, 0xfc, 0xce, 0xfa, 0x7e, 0x30, 0x61,
                                                                                0x36, 0x7f, 0x1d, 0x57, 0xa4, 0xe7, 0x45, 0x5a};
        //unsigned char nonce_counter[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        //                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        //                                };
        unsigned char nonce_counter[16] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
                                           0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11
                                          };
        unsigned char sw_dst[32];
        unsigned char key[32] = {0x0};
        unsigned char iv[16] = {0x0};
        unsigned char stream_block[16];
        mbedtls_aes_context aes_ctx;
        mbedtls_gcm_context gcm_ctx;
	mbedtls_cipher_id_t cipher = MBEDTLS_CIPHER_ID_AES;
	memset(key, INIT_VALUE, 32);
 	memset(iv,INIT_IV,16);
	if(aes_mode == GCM_MODE)
		outlen = 32;
	else
		outlen = 16;

	/*
	while(i < 32)
	{
		key[i] = 0x11;
		key[i+1] = 0x22;
		key[i+2] = 0x33;
		key[i+3] = 0x44;
		i = i +4;
	}
	*/

	switch(aes_bitlen)
	{
		case AES_128:
			keylen = 128;
		break;
		case AES_192:
			keylen = 192;
		break;
		case AES_256:
			keylen = 256;
		break;
		default:
		break;
	}
        /*1. hw encrypt*/
        ret = ips_cmd_create(psrc, pdst, alg_flag, aes_bitlen, aes_mode, ENCRYPT, proc_len);
        if(ret) {
                printf("ips module-ips_cmd_creaete for aes-encrypt failed! \n");
		return -1;
	}
        ret = ips_status_polling();
        if(ret) {
                printf("ips module-ips_status_polling for aes-encrypt failed! \n");
		return -1;
	}
	#ifdef DEBUG_PRINT
        for(i=0; i<outlen; i++)
                printf("en_dst = %x \n",pdst[i]);
	#endif

        /*2. hw decrypt*/
        ret = ips_cmd_create(pdst, psrc+0x1000, alg_flag, aes_bitlen, aes_mode, DECRYPT, proc_len);
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
                printf("de_dst = %x \n",psrc[0x1000+i]);
	#endif
        ret = str_cmp(psrc, (psrc+0x1000), proc_len);
        if(ret) {
                printf("decrypt data and source data are different!\n");
		return -1;
	} else
		printf("decrypt data is the same as source data!\n");


        /*3. sw encrypt*/
         memset(key,INIT_VALUE,32);
         mbedtls_aes_init( &aes_ctx );
         mbedtls_aes_setkey_enc( &aes_ctx, key, keylen);
	 memset(sw_dst, 0 ,32);
	 switch(aes_mode)
	 {
		case ECB_MODE:
			mbedtls_aes_crypt_ecb( &aes_ctx, MBEDTLS_AES_ENCRYPT, psrc, sw_dst );
		break;
		case CBC_MODE:
			memset(iv,INIT_IV,16);
			mbedtls_aes_crypt_cbc( &aes_ctx, MBEDTLS_AES_ENCRYPT,16,iv, psrc, sw_dst );
		break;
		case CFB_MODE:
			memset(iv,INIT_IV,16);
			mbedtls_aes_crypt_cfb128( &aes_ctx, MBEDTLS_AES_ENCRYPT,16,&offset,iv, psrc, sw_dst);
		break;
		case OFB_MODE:
			memset(iv,INIT_IV,16);
			mbedtls_aes_crypt_ofb( &aes_ctx, 16,&offset,iv, psrc, sw_dst);
		break;
		case CTR_MODE:
			memset(iv,INIT_IV,16);
			mbedtls_aes_crypt_ctr( &aes_ctx,16,&offset,nonce_counter,stream_block, psrc, sw_dst );
		break;
		case GCM_MODE:
			//memset(iv,INIT_IV,16);
			memset(key,0,32);
			memset(iv,0,16);
			memset(psrc,0,16);
			mbedtls_gcm_init(&gcm_ctx);
			mbedtls_gcm_setkey( &gcm_ctx, cipher, key,
                                      keylen );
			mbedtls_gcm_crypt_and_tag( &gcm_ctx, MBEDTLS_GCM_ENCRYPT,
                                        16,
                                        iv, 12,
                                        additional, 0,
                                        psrc, sw_dst, 16, tag_buf );
		for(i=0; i<16; i++)
			printf("tag = %x \n", tag_buf[i]);
		break;

	 }
	#ifdef DEBUG_PRINT
         for(i=0; i<outlen; i++)
                printf("sw_dst = %x \n",sw_dst[i]);
	#endif
         ret = str_cmp(pdst, sw_dst, outlen);
         if(ret) {
                printf("encrypt data between engine and sw are different\n");
		return -1;
	}
         else
                printf("encrypt data is the same as software encrypt data!\n");
	return 0;
}
static int se_ips_aes(int argc, char *argv[])
{
	int ret;
	int i;

        unsigned char src[] = "1122334455667788";
        //unsigned char src[16] = {0x0}; // {0xC3, 0x4C, 0x05, 0x2C, 0xC0, 0xDA, 0x8D, 0x73,
        //0x45, 0x1A, 0xFE, 0x5F, 0x03, 0xBE, 0x29, 0x7F};
        int len = 16;
        unsigned char sw_dst[32];
        unsigned char *psrc;
        unsigned char *pdst;

	if(argc < 2)
                return -EUSAGE;
	psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);
	memcpy(psrc,src,len);

	ret = ips_init_clk();
	if(!ret)
		printf("ips module clock case pass! \n");
	ret = ips_module_reset();
	if(!ret)
		printf("ips module reset case pass! \n");
	ret = ips_dev_init();
	if(!ret)
		printf("ips module initialzie case pass! \n");
	ret = ips_key_iv_set();
	if(!ret)
		printf("ips module key_iv set case pass \n");
	 printf("\n");

	/*=====================================AES-128============================================*/
   	/***********************calculate aes-128-cfb********************************/
	ret = strcmp(argv[1],"aes128cfb");
	if(!ret) {
        	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CFB_MODE, len);
        	if(!ret){
                 	printf("aes-128-cfb mode case pass! \n");
			return 0;
		}
        	else{
                	 printf("aes-128-cfb mode case failed! \n");
			 return -1;
		}
	}

        /***********************calculate aes-128-ofb********************************/
	ret = strcmp(argv[1],"aes128ofb");
	if(!ret) {
		ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, OFB_MODE, len);
        	if(!ret){
                 	printf("aes-128-ofb mode case pass! \n");
		 	return 0;
		}
        	else{
                 	printf("aes-128-ofb mode case failed! \n");
		 	return -1;
		}
	}
        /***********************calculate aes-128-ctr********************************/
	ret = strcmp(argv[1],"aes128ctr");
	if(!ret) {
		ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CTR_MODE, len);
        	if(!ret){
                 	printf("aes-128-ctr mode case pass! \n");
		 	return 0;
		}
        	else{
                 	printf("aes-128-ctr mode case failed! \n");
			return -1;
		}
	}
	/***********************calculate aes-128-gcm********************************/
	ret = strcmp(argv[1],"aes128gcm");
	if(!ret) {
        	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, GCM_MODE, len);
        	if(!ret){
                 	printf("aes-128-gcm mode case pass! \n");
			return 0;
		}
        	else{
                 	printf("aes-128-gcm mode case failed! \n");
			return -1;
		}
	}
	/***********************calculate aes-128-ecb********************************/
	ret = strcmp(argv[1],"aes128ecb");
	if(!ret) {
		ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, ECB_MODE, len);
		if(!ret){
                 	printf("aes-128-ecb mode case pass! \n");
			return 0;
		}
        	else{
                 	printf("aes-128-ecb mode case failed! \n");
			return -1;
		}
	}
	/***********************calculate aes-128-cbc********************************/
	ret = strcmp(argv[1],"aes128cbc");
	if(!ret) {
        	ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CBC_MODE, len);
        	if(!ret){
                 	printf("aes-128-cbc mode case pass! \n");
			return 0;
		}
        	else{
                 	printf("aes-128-cbc mode case failed! \n");
			return -1;
		}
	}
	/*=====================================AES-192==============================*/
    	/***********************calculate aes-192-cfb********************************/
        ret = strcmp(argv[1],"aes192cfb");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CFB_MODE, len);
                if(!ret){
                        printf("aes-192-cfb mode case pass! \n");
                        return 0;
                }
                else{
                         printf("aes-192-cfb mode case failed! \n");
                         return -1;
                }
        }
        /***********************calculate aes-192-ofb********************************/
        ret = strcmp(argv[1],"aes192ofb");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, OFB_MODE, len);
                if(!ret){
                        printf("aes-192-ofb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-ofb mode case failed! \n");
                        return -1;
        	}
	}
        /***********************calculate aes-192-ctr********************************/
        ret = strcmp(argv[1],"aes192ctr");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CTR_MODE, len);
                if(!ret){
                        printf("aes-192-ctr mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-ctr mode case failed! \n");
                        return -1;
                }
        }
        /***********************calculate aes-192-gcm********************************/
        ret = strcmp(argv[1],"aes192gcm");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, GCM_MODE, len);
                if(!ret){
                        printf("aes-192-gcm mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-gcm mode case failed! \n");
                        return -1;
                }
	}
        /***********************calculate aes-192-ecb********************************/
        ret = strcmp(argv[1],"aes192ecb");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, ECB_MODE, len);
                if(!ret){
                        printf("aes-192-ecb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-ecb mode case failed! \n");
                        return -1;
                }
	}
        /***********************calculate aes-192-cbc********************************/
        ret = strcmp(argv[1],"aes192cbc");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CBC_MODE, len);
                if(!ret){
                        printf("aes-192-cbc mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-cbc mode case failed! \n");
                        return -1;
                }
	}
	 /*=====================================AES-256============================================*/
   	 /***********************calculate aes-256-cfb********************************/
        ret = strcmp(argv[1],"aes256cfb");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CFB_MODE, len);
                if(!ret){
                        printf("aes-256-cfb mode case pass! \n");
                        return 0;
                }
                else{
                         printf("aes-256-cfb mode case failed! \n");
                         return -1;
                }
        }
        /***********************calculate aes-256-ofb********************************/
        ret = strcmp(argv[1],"aes256ofb");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, OFB_MODE, len);
                if(!ret){
                        printf("aes-256-ofb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-ofb mode case failed! \n");
                        return -1;
        	}
	}
        /***********************calculate aes-256-ctr********************************/
        ret = strcmp(argv[1],"aes256ctr");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CTR_MODE, len);
                if(!ret){
                        printf("aes-256-ctr mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-ctr mode case failed! \n");
                        return -1;
                }
        }
        /***********************calculate aes-256-gcm********************************/
        ret = strcmp(argv[1],"aes256gcm");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, GCM_MODE, len);
                if(!ret){
                        printf("aes-256-gcm mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-gcm mode case failed! \n");
                        return -1;
                }
	}
        /***********************calculate aes-256-ecb********************************/
        ret = strcmp(argv[1],"aes256ecb");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, ECB_MODE, len);
                if(!ret){
                        printf("aes-256-ecb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-ecb mode case failed! \n");
                        return -1;
                }
	}
        /***********************calculate aes-256-cbc********************************/
        ret = strcmp(argv[1],"aes256cbc");
        if(!ret) {
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CBC_MODE, len);
                if(!ret){
                        printf("aes-256-cbc mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-cbc mode case failed! \n");
                        return -1;
                }
	}
	/*==================================end=====================================*/
	return 0;
}
MK_CMD(ips_aes128, se_ips_aes, "Test crypto_acc_sha,including aes-128,aes-192,aes-256",
        "ips_aes128 aes-128\n"
        "       - aes128ecb: test aes-128-ecb algorithm\n"
        "       - aes128cbc: test aes-128-cbc algorithm\n"
        "       - aes128cfb: test aes-128-cfb algorithm\n"
        "       - aes128ofb: test aes-128-ofb algorithm\n"
        "       - aes128ctr: test aes-128-ctr algorithm\n"
        "       - aes128gcm: test aes-128-gcm algorithm\n"
);
MK_CMD(ips_aes192, se_ips_aes, "Test crypto_acc_sha,including aes-128,aes-192,aes-256",
        "ips_aes192 aes-192\n"
        "       - aes192ecb: test aes-192-ecb algorithm\n"
        "       - aes192cbc: test aes-192-cbc algorithm\n"
        "       - aes192cfb: test aes-192-cfb algorithm\n"
        "       - aes192ofb: test aes-192-ofb algorithm\n"
        "       - aes192ctr: test aes-192-ctr algorithm\n"
        "       - aes192gcm: test aes-192-gcm algorithm\n"
);
MK_CMD(ips_aes256, se_ips_aes, "Test crypto_acc_sha,including aes-128,aes-192,aes-256",
        "ips_aes256 aes-256\n"
        "       - aes256ecb: test aes-256-ecb algorithm\n"
        "       - aes256cbc: test aes-256-cbc algorithm\n"
        "       - aes256cfb: test aes-256-cfb algorithm\n"
        "       - aes256ofb: test aes-256-ofb algorithm\n"
        "       - aes256ctr: test aes-256-ctr algorithm\n"
        "       - aes256gcm: test aes-256-gcm algorithm\n"
);

