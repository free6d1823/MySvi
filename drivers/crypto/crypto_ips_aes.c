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
//#define SVI_VCS
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


#ifdef SVI_Z1
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

static int aes_function_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int aes_bitlen, int aes_mode,  int proc_len)
{

 	int i;
        int ret;
        int outlen;
        int keylen;
        unsigned char sw_dst[32]={0x0};
	#ifdef SVI_Z1
        size_t offset = 0;
        unsigned char additional[]={0};
        unsigned char pt[]={0};
        unsigned char tag_buf[] = { 0x58, 0xe2, 0xfc, 0xce, 0xfa, 0x7e, 0x30, 0x61,
                                                                                0x36, 0x7f, 0x1d, 0x57, 0xa4, 0xe7, 0x45, 0x5a};
        //unsigned char nonce_counter[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        //                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        //                                };
        unsigned char nonce_counter[16] = {0x11, 0x22, 0x33, 0x44, 0x11, 0x22, 0x33, 0x44,
                                           0x11, 0x22, 0x33, 0x44, 0x0, 0x0, 0x0, 0x01
                                          };
        unsigned char key[32] = {0x0};
        unsigned char iv[16] = {0x0};
        unsigned char stream_block[16];
        mbedtls_aes_context aes_ctx;
        mbedtls_gcm_context gcm_ctx;
        mbedtls_cipher_id_t cipher = MBEDTLS_CIPHER_ID_AES;
        memset(key, INIT_VALUE, 32);
        memset(iv,INIT_IV,12);
        iv[15] = 0x01;
	#endif
	#ifdef SVI_VCS
        //unsigned char dst_ecb_128[]={0x39,0x02,0xdc,0x19,0x25,0xdc,0x11,0x6a,0x84,0x09,0x85,0x0b,0x1d,0xfb,0x97,0x32};
        unsigned char dst_ecb_128[16]={0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
        unsigned char dst_cbc_128[16]={0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d};
        unsigned char dst_cfb_ofb_128[16]={0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a};
        unsigned char dst_ctr_128[16]={0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce};
        unsigned char dst_ecb_192[16]={0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
        unsigned char dst_cbc_192[16]={0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d};
        unsigned char dst_cfb_ofb_192[16]={0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a};
        unsigned char dst_ctr_192[16]={0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce};
        unsigned char dst_ecb_256[16]={0x3a,0xd7,0x7b,0xb4,0x0d,0x7a,0x36,0x60,0xa8,0x9e,0xca,0xf3,0x24,0x66,0xef,0x97};
        unsigned char dst_cbc_256[16]={0x76,0x49,0xab,0xac,0x81,0x19,0xb2,0x46,0xce,0xe9,0x8e,0x9b,0x12,0xe9,0x19,0x7d};
        unsigned char dst_cfb_ofb_256[16]={0x3b,0x3f,0xd9,0x2e,0xb7,0x2d,0xad,0x20,0x33,0x34,0x49,0xf8,0xe8,0x3c,0xfb,0x4a};
        unsigned char dst_ctr_256[16]={0x87,0x4d,0x61,0x91,0xb6,0x20,0xe3,0x26,0x1b,0xef,0x68,0x64,0x99,0x0d,0xb6,0xce};
	#endif

        if((aes_mode == GCM_MODE) || (aes_mode == CBC_CS1_MODE) || (aes_mode == CBC_CS2_MODE) || (aes_mode == CBC_CS3_MODE))
                outlen = 32;
        else
                outlen = 16;

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

	#ifdef SVI_Z1
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
	#endif
	#ifdef SVI_VCS
	 switch(aes_mode)
        {
                case ECB_MODE:
                        if(aes_bitlen == AES_128)
                                memcpy(sw_dst,dst_ecb_128,16);
                        if(aes_bitlen == AES_192)
                                memcpy(sw_dst,dst_ecb_192,16);
                        if(aes_bitlen == AES_256)
                                memcpy(sw_dst,dst_ecb_256,16);
                break;
                case CBC_MODE:
                        if(aes_bitlen == AES_128)
                                memcpy(sw_dst,dst_cbc_128,16);
                        if(aes_bitlen == AES_192)
                                memcpy(sw_dst,dst_cbc_192,16);
                        if(aes_bitlen == AES_256)
                                memcpy(sw_dst,dst_cbc_256,16);
                break;
                case CFB_MODE:
                case OFB_MODE:
                        if(aes_bitlen == AES_128)
                                memcpy(sw_dst,dst_cfb_ofb_128,16);
                        if(aes_bitlen == AES_192)
                                memcpy(sw_dst,dst_cfb_ofb_192,16);
                        if(aes_bitlen == AES_256)
                                memcpy(sw_dst,dst_cfb_ofb_256,16);

                break;

                case CTR_MODE:
                        if(aes_bitlen == AES_128)
                                memcpy(sw_dst,dst_ctr_128,16);
                        if(aes_bitlen == AES_192)
                                memcpy(sw_dst,dst_ctr_192,16);
                        if(aes_bitlen == AES_256)
                                memcpy(sw_dst,dst_ctr_256,16);

                break;
                default:
                break;
        }
	#endif


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


#ifdef SVI_Z1
static int se_ips_aes(int argc, char *argv[])
#endif
#ifdef SVI_VCS
int se_ips_aes()
#endif
{
        int ret;
        int i;

        unsigned char *hashkey;
        unsigned char src[16] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
        unsigned char key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
        unsigned char iv[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
        int len = 16;
        unsigned char sw_dst[32];
        unsigned char *psrc;
        unsigned char *pdst;
	hashkey = NULL;
	#ifdef SVI_Z1
        if(argc < 2)
	#endif
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
        ret = ips_key_iv_set(key,16,iv,hashkey,16);
        if(!ret)
                printf("ips module key_iv set case pass \n");
         printf("\n");

        /*=====================================AES-128============================================*/
        /***********************calculate aes-128-cfb********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes128cfb");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CFB_MODE, len);
                if(!ret){
                        printf("aes-128-cfb mode case pass! \n");
                        return 0;
                }
                else{
                         printf("aes-128-cfb mode case failed! \n");
                         return -1;
                }
        #ifdef SVI_Z1
        }
        #endif

        /***********************calculate aes-128-ofb********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes128ofb");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, OFB_MODE, len);
                if(!ret){
                        printf("aes-128-ofb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-128-ofb mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-128-ctr********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes128ctr");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CTR_MODE, len);
                if(!ret){
                        printf("aes-128-ctr mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-128-ctr mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-128-gcm********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes128gcm");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, GCM_MODE, len);
                if(!ret){
                        printf("aes-128-gcm mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-128-gcm mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-128-ecb********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes128ecb");
        if(!ret) {
        #endif
                printf("ente into aes128edb \n");
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, ECB_MODE, len);
                if(!ret){
                        printf("aes-128-ecb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-128-ecb mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-128-cbc********************************/

        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes128cbc");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CBC_MODE, len);
                if(!ret){
                        printf("aes-128-cbc mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-128-cbc mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes128cbccs1");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CBC_CS1_MODE, 26);
                if(!ret){
                        printf("aes-128-cbc-cs1 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-128-cbc-cs1 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif

        #ifdef SVI_Z1
         ret = strcmp(argv[1],"aes128cbccs2");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CBC_CS2_MODE, 26);
                if(!ret){
                        printf("aes-128-cbc-cs2 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-128-cbc-cs2 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }

         ret = strcmp(argv[1],"aes128cbccs3");
        if(!ret) {
	#endif

                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_128, CBC_CS3_MODE, 26);
                if(!ret){
                        printf("aes-128-cbc-cs3 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-128-cbc-cs3 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif



        /*=====================================AES-192==============================*/
        /***********************calculate aes-192-cfb********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes192cfb");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CFB_MODE, len);
                if(!ret){
                        printf("aes-192-cfb mode case pass! \n");
                        return 0;
                }
           else{
                         printf("aes-192-cfb mode case failed! \n");
                         return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-192-ofb********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes192ofb");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, OFB_MODE, len);
                if(!ret){
                        printf("aes-192-ofb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-ofb mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-192-ctr********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes192ctr");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CTR_MODE, len);
                if(!ret){
                        printf("aes-192-ctr mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-ctr mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-192-gcm********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes192gcm");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, GCM_MODE, len);
                if(!ret){
                        printf("aes-192-gcm mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-gcm mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-192-ecb********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes192ecb");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, ECB_MODE, len);
                if(!ret){
                        printf("aes-192-ecb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-ecb mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif
        /***********************calculate aes-192-cbc********************************/
        #ifdef SVI_Z1
        ret = strcmp(argv[1],"aes192cbc");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CBC_MODE, len);
                if(!ret){
                        printf("aes-192-cbc mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-cbc mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }

        ret = strcmp(argv[1],"aes192cbccs1");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CBC_CS1_MODE, 26);
                if(!ret){
                        printf("aes-192-cbc-cs1 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-cbc-cs1 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }

         ret = strcmp(argv[1],"aes192cbccs2");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_192, CBC_CS2_MODE, 26);
                if(!ret){
                        printf("aes-192-cbc-cs2 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-cbc-cs2 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }

         ret = strcmp(argv[1],"aes192cbccs3");
        if(!ret) {
        #endif
		aes_function_test(psrc, pdst, AES_FLAG, AES_192, CBC_CS3_MODE, 26);
                if(!ret){
                        printf("aes-192-cbc-cs3 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-192-cbc-cs3 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }




         /*=====================================AES-256============================================*/
         /***********************calculate aes-256-cfb********************************/
        ret = strcmp(argv[1],"aes256cfb");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CFB_MODE, len);
                if(!ret){
                        printf("aes-256-cfb mode case pass! \n");
                        return 0;
                }
                else{
                         printf("aes-256-cfb mode case failed! \n");
                         return -1;
                }
        #ifdef SVI_Z1
        }
        /***********************calculate aes-256-ofb********************************/
        ret = strcmp(argv[1],"aes256ofb");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, OFB_MODE, len);
                if(!ret){
                        printf("aes-256-ofb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-ofb mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        /***********************calculate aes-256-ctr********************************/
        ret = strcmp(argv[1],"aes256ctr");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CTR_MODE, len);
                if(!ret){
                        printf("aes-256-ctr mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-ctr mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        /***********************calculate aes-256-gcm********************************/
        ret = strcmp(argv[1],"aes256gcm");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, GCM_MODE, len);
                if(!ret){
                        printf("aes-256-gcm mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-gcm mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        /***********************calculate aes-256-ecb********************************/
        ret = strcmp(argv[1],"aes256ecb");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, ECB_MODE, len);
                if(!ret){
                        printf("aes-256-ecb mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-ecb mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        /***********************calculate aes-256-cbc********************************/
        ret = strcmp(argv[1],"aes256cbc");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CBC_MODE, len);
                if(!ret){
                        printf("aes-256-cbc mode case pass! \n");
                        return 0;
          }
                else{
                        printf("aes-256-cbc mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }

         ret = strcmp(argv[1],"aes256cbccs1");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CBC_CS1_MODE, 26);
                if(!ret){
                        printf("aes-256-cbc-cs1 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-cbc-cs1 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }

         ret = strcmp(argv[1],"aes256cbccs2");
        if(!ret) {
        #endif

                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CBC_CS2_MODE, 26);
                if(!ret){
                        printf("aes-256-cbc-cs2 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-cbc-cs2 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }

         ret = strcmp(argv[1],"aes256cbccs3");
        if(!ret) {
        #endif
                ret = aes_function_test(psrc, pdst, AES_FLAG, AES_256, CBC_CS3_MODE, 26);
                if(!ret){
                        printf("aes-256-cbc-cs3 mode case pass! \n");
                        return 0;
                }
                else{
                        printf("aes-256-cbc-cs3 mode case failed! \n");
                        return -1;
                }
        #ifdef SVI_Z1
        }
        #endif


        /*==================================end=====================================*/
        return 0;
}

#ifdef SVI_Z1
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
#endif
