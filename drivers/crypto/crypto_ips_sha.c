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
//#define DEBUG_PRINT
#define IPS_POLLING
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
	unsigned char dgst[0x40] = {0x0};
	unsigned char dgst_224[28]={0x46,0x34,0x27,0x0f,0x70,0x7b,0x6a,0x54,0xda,0xae,0x75,0x30,0x46,0x08,0x42,0xe2,0x0e,0x37,0xed,0x26,0x5c,0xee,0xe9,0xa4,0x3e,0x89,0x24,0xaa};
	unsigned char dgst_256[32]={0x53,0x04,0x8e,0x26,0x81,0x94,0x1e,0xf9,0x9b,0x2e,0x29,0xb7,0x6b,0x4c,0x7d,0xab,0xe4,0xc2,0xd0,0xc6,0x34,0xfc,0x6d,0x46,0xe0,0xe2,0xf1,0x31,0x07,0xe7,0xaf,0x23};
	switch(sha_flag)
	{
		case SHA_1:
			outlen = 20;
			mbedtls_sha1(psrc,proc_len,dgst);
		break;
		case SHA_224:
			outlen = 28;
			 mbedtls_sha256(psrc,proc_len,dgst,1);
		break;
		case SHA_256:
			outlen = 32;
			mbedtls_sha256(psrc,proc_len,dgst,0);
		break;
		case SHA_384:
			outlen = 48;
			mbedtls_sha512(psrc,proc_len,dgst,1);
		break;
		case SHA_512:
			outlen = 64;
			mbedtls_sha512(psrc,proc_len,dgst,0);
		break;
		case SHA_512_224:
			outlen = 28;
			memcpy(dgst,dgst_224,outlen);
		break;
		case SHA_512_256:
			outlen = 32;
			memcpy(dgst,dgst_256,outlen);
		break;
		default:
		break;
	}

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
int sha_function_hmac_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sha_flag, int ende_flag, int proc_len)
{
        int i;
        int ret;
        int outlen;
	int keylen = 32;
        unsigned char dgst[0x40] = {0x0};
	unsigned char dgst_hmac_224[28]={0xbb,0xff,0x17,0x0e,0xfa,0x4e,0x26,0x33,0x3b,0x19,0x38,0x8f,0xe3,0x50,0x29,0xe8,0xd7,0xc4,0x9c,0x64,0x43,0xf5,0xb2,0xac,0xb6,0xe1,0x10,0xdc};
        unsigned char dgst_hmac_256[32]={0x78,0x4c,0xac,0x6a,0xaf,0xef,0xd5,0x51,0x70,0x29,0xba,0xe0,0xcd,0x22,0x3d,0x58,0x11,0x1d,0xc3,0x7f,0x39,0x0d,0x98,0x2f,0xae,0x2a,0x05,0x48,0xb5,0xaa,0x67,0xea};
	unsigned char key[32] = {0xff}; //{0x4a,0x65,0x66,0x65};
	const mbedtls_md_info_t *md_info;
	memset(key,0x0,32); //0x0b
	//key[0] = 0x30;
	/*i = 0;
	while(i<32)
	{
		key[i] = 0xff;
		key[i + 1] = 0xff;
		key[i + 2] = 0xff;
		key[i + 3] = 0xff;
		i = i + 4;

	}
	*/
        //unsigned char key[32] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

	switch(sha_flag)
        {
                case SHA_1:
                         outlen = 20;
                         md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA1);
         		 mbedtls_md_hmac( md_info, key, keylen, psrc, proc_len, dgst);
                break;
                case SHA_224:
                        outlen = 28;
                        md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA224);
         		mbedtls_md_hmac( md_info, key, keylen, psrc, proc_len, dgst);
                break;
                case SHA_256:
                        outlen = 32;
                        md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
         		mbedtls_md_hmac( md_info, key, keylen, psrc, proc_len, dgst);
                break;
                case SHA_384:
                        outlen = 48;
                        md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA384);
         		mbedtls_md_hmac( md_info, key, keylen, psrc, proc_len, dgst);
                break;
                case SHA_512:
                        outlen = 64;
                        md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA512);
         		mbedtls_md_hmac( md_info, key, keylen, psrc, proc_len, dgst);
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
static int se_ips_sha(int argc, char *argv[])
{
	int ret;
	int i;
	unsigned char src[] = "abc"; //"Hi There"; //""what do ya want for nothing?"; //""abc";
	int len = 3; //8; //8; //28; //0x03;
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

        /*************************sha1 alg***********************************************/
	ret = strcmp(argv[1],"sha128");
	if(!ret){
		ret = sha_function_raw_test(psrc, pdst, SHA_FLAG,SHA_1, ENCRYPT, len);
		if(!ret){
		 	printf("sha1 raw mode case pass! \n");
			return 0;
		}
		else {
		 	printf("sha1 raw mode case failed! \n");
			return -1;
		}
	}
	/*************************sha224 alg**********************************************/
	ret = strcmp(argv[1],"sha224");
	if(!ret){
		ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_224, ENCRYPT, len);
		if(!ret){
		 	printf("sha224 raw mode case pass! \n");
			return 0;
		}
		else{
		 	printf("sha224 raw mode case failed! \n");
			return -1;
		}
	}
	/*************************sha256 alg**********************************************/
	ret = strcmp(argv[1],"sha256");
	if(!ret){
		ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_256, ENCRYPT, len);
		if(!ret){
		 	printf("sha256 raw mode case pass! \n");
			return 0;
		}
		else{
		 	printf("sha256 raw mode case failed! \n");
			return -1;
		}
	}
	/*************************sha384 alg**********************************************/
	ret = strcmp(argv[1],"sha384");
	if(!ret){
		ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_384, ENCRYPT, len);
		if(!ret){
		 	printf("sha384 raw mode case pass! \n");
			return 0;
		}
		else{
		 	printf("sha384 raw mode case failed! \n");
			return -1;
		}
	}
	/*************************sha512 alg**********************************************/
	ret = strcmp(argv[1],"sha512");
	if(!ret){
		ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_512, ENCRYPT, len);
		if(!ret){
		 	printf("sha512 raw mode case pass! \n");
			return 0;
		}
		else{
			printf("sha512 raw mode case failed! \n");
			return -1;
		}
	}
      /*************************sha512_224 alg**********************************************/
	ret = strcmp(argv[1],"sha512-224");
	if(!ret){
		ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_512_224, ENCRYPT, len);
		if(!ret){
		 	printf("sha512_224 raw mode case pass! \n");
			return 0;
		}
		else{
		 	printf("sha512_224 raw mode case failed! \n");
			return -1;
		}
	}
      /*************************sha512_256 alg**********************************************/
	ret = strcmp(argv[1],"sha512-256");
	if(!ret){
		ret = sha_function_raw_test(psrc, pdst, SHA_FLAG, SHA_512_256, ENCRYPT, len);
		if(!ret) {
		 	printf("sha512_256 raw mode case pass! \n");
			return 0;
		}
		else{
		 	printf("sha512_256 raw mode case failed! \n");
			return -1;
		}
	}
 	/*************************sha1 alg for hmac********************************************/
        ret = strcmp(argv[1],"sha128hmac");
        if(!ret){
                ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG,SHA_1, ENCRYPT, len);
                if(!ret){
                        printf("sha1 hmac mode case pass! \n");
                        return 0;
                }
                else {
                        printf("sha1 hmac mode case failed! \n");
                        return -1;
                }
        }
        /*************************sha224 alg for hmac**********************************************/
        ret = strcmp(argv[1],"sha224hmac");
        if(!ret){
                ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_224, ENCRYPT, len);
                if(!ret){
                        printf("sha224 hmac mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sha224 hmac mode case failed! \n");
                        return -1;
                }
        }
        /*************************sha256 alg for hmac**********************************************/
        ret = strcmp(argv[1],"sha256hmac");
        if(!ret){
                ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_256, ENCRYPT, len);
                if(!ret){
                        printf("sha256 hmac mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sha256 hmac mode case failed! \n");
                        return -1;
                }
        }
        /*************************sha384 alg for hmac**********************************************/
        ret = strcmp(argv[1],"sha384hmac");
        if(!ret){
                ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_384, ENCRYPT, len);
                if(!ret){
                        printf("sha384 hmac mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sha384 hmac mode case failed! \n");
                        return -1;
                }
        }
        /*************************sha512 alg for hmac**********************************************/
        ret = strcmp(argv[1],"sha512hmac");
        if(!ret){
                ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_512, ENCRYPT, len);
                if(!ret){
                        printf("sha512 hmac mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sha512 hmac mode case failed! \n");
                        return -1;
                }
        }
      /*************************sha512_224 alg for hmac**********************************************/
        ret = strcmp(argv[1],"sha512-224hmac");
        if(!ret){
                ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_512_224, ENCRYPT, len);
                if(!ret){
                        printf("sha512_224 hmac mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sha512_224 hmac mode case failed! \n");
                        return -1;
                }
        }
      /*************************sha512_256 alg for hmac**********************************************/
        ret = strcmp(argv[1],"sha512-256hmac");
        if(!ret){
                ret = sha_function_hmac_test(psrc, pdst, SHA_FLAG, SHA_512_256, ENCRYPT, len);
                if(!ret) {
                        printf("sha512_256 hmac mode case pass! \n");
                        return 0;
                }
                else{
                        printf("sha512_256 hmac mode case failed! \n");
                        return -1;
                }
        }
	return 0;
}
MK_CMD(ips_sharaw, se_ips_sha, "Test crypto_acc_sha,including SHA128,SHA224,SHA256,SHA384,SHA512,SHA512/224/SHA512/256",
	"ips_sharaw RAW mode\n"
	"	- sha128: test sha1 algorithm\n"
	"	- sha224: test sha-224 algorithm\n"
	"	- sha256: test sha-256 algorithm\n"
	"	- sha384: test sha-384 algorithm\n"
	"	- sha512: test sha-512 algorithm\n"
	"	- sha512-224: test sha512/224 algorithm\n"
	"	- sha512-256: test sha512/256 algorithm\n"
);
MK_CMD(ips_shamac, se_ips_sha, "Test crypto_acc_sha,including SHA128,SHA224,SHA256,SHA384,SHA512,SHA512/224/SHA512/256",
        "ips_shamac HMAC mode \n"
        "       - sha128hmac: test sha1-hmac algorithm\n"
        "       - sha224hmac: test sha-224-hmac algorithm\n"
        "       - sha256hamc: test sha-256-hmac algorithm\n"
        "       - sha384hmac: test sha-384-hmac algorithm\n"
        "       - sha512hmac: test sha-512-hmac algorithm\n"
        "       - sha512-224hmac: test sha512/224-hmac algorithm\n"
        "       - sha512-256hmac: test sha512/256-hmac algorithm\n"
);
