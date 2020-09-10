#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
#include "target/cmdline.h"
#include "target/heap.h"
//#define DEBUG_PRINT
#define IPS_POLLING

int se_ips_sha_ddt()
{
        int ret;
        int i;
	unsigned long long *ddt_src;
	unsigned long long *ddt_dst;
        unsigned char src[] = "abc"; //"Hi There"; //""what do ya want for nothing?"; //""abc";
        int len = 3; //8; //8; //28; //0x03;
        unsigned char *psrc;
	unsigned char *psrc1;
        unsigned char *pdst;
	unsigned char *pdst1;

	ddt_src = (unsigned long long*)IPS_DDT_SRC;
	ddt_dst = (unsigned long long*)IPS_DDT_DST;
        psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
	//psrc1 = (unsigned char*)(IPS_SRC_BASE + 0x10);
        pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);
	//pdst1 = (unsigned char*)(IPS_DST_BASE + 0x10);

	ddt_src[0] = IPS_SRC_BASE;
	ddt_src[1] = 0x3;
	ddt_src[2] = 0x0;
	ddt_src[3] = 0x0;

	ddt_dst[0] = IPS_DST_BASE;
	ddt_dst[1] = 0x17;
	ddt_dst[2] = 0x0;
	ddt_dst[3] = 0x0;
	memcpy(psrc,src,3);

	#ifdef DEBUG_PRINT
	printf("beign0: print: \n");
		printf("ddt_src = %llx \n", ddt_src);
                printf("ddt_dst = %llx \n", ddt_dst);
                printf("ddt_src[0]= %llx \n",ddt_src[0]);
                printf("ddt_src[1]= %llx \n",ddt_src[1]);
                printf("ddt_src[2]= %llx \n",ddt_src[2]);
                printf("ddt_src[3]= %llx \n",ddt_src[3]);
                printf("ddt_dst[0]= %llx \n",ddt_dst[0]);
                printf("ddt_dst[1]= %llx \n",ddt_dst[1]);
                printf("ddt_dst[2]= %llx \n",ddt_dst[2]);
                printf("ddt_dst[3]= %llx \n",ddt_dst[3]);
	for(i=0; i<3; i++)
		printf("src =%x \n",psrc[i]);
	#endif
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

        /*************************sha1 alg***********************************************/
        ret = sha_function_raw_test((unsigned char*)ddt_src, (unsigned char*)(ddt_dst), SHA_DDT_FLAG,SHA_1, ENCRYPT, len);
        if(!ret){
                printf("sha1 ddt mode case pass! \n");
        }
        else {
                printf("sha1 ddt mode case failed! \n");
                return -1;
        }

	return 0;
}


int se_ips_aes_ddt()
{
        int ret;
        int i;
        int len = 16;
	unsigned long long *ddt_src;
	unsigned long long *ddt_dst;
        unsigned char *hashkey;
	unsigned char *psrc;
        unsigned char *psrc1;
        unsigned char *pdst;
        unsigned char *pdst1;
        hashkey = NULL;
	unsigned char src[16] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96,0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
 	unsigned char key128[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	unsigned char iv[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};

        ddt_src = (unsigned long long*)IPS_DDT_SRC;
        ddt_dst = (unsigned long long*)IPS_DDT_DST;
        psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
        //psrc1 = (unsigned char*)(IPS_SRC_BASE + 0x10);
        pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);
        //pdst1 = (unsigned char*)(IPS_DST_BASE + 0x10);

        ddt_src[0] = IPS_SRC_BASE;
        ddt_src[1] = 0x10;
        ddt_src[2] = 0x0;
        ddt_src[3] = 0x0;

        ddt_dst[0] = IPS_DST_BASE;
        ddt_dst[1] = 0x10;
        ddt_dst[2] = 0x0;
        ddt_dst[3] = 0x0;
        memcpy(psrc,src,len);

	#ifdef DEBUG_PRINT
        printf("beign0: print: \n");
                printf("ddt_src = %llx \n", ddt_src);
                printf("ddt_dst = %llx \n", ddt_dst);
                printf("ddt_src[0]= %d \n",ddt_src[0]);
                printf("ddt_src[1]= %d \n",ddt_src[1]);
                printf("ddt_src[2]= %d \n",ddt_src[2]);
                printf("ddt_src[3]= %d \n",ddt_src[3]);
                printf("ddt_dst[0]= %d \n",ddt_dst[0]);
                printf("ddt_dst[1]= %d \n",ddt_dst[1]);
                printf("ddt_dst[2]= %d \n",ddt_dst[2]);
                printf("ddt_dst[3]= %d \n",ddt_dst[3]);
        //for(i=0; i<16; i++)
          //      printf("src =%x \n",psrc[i]);
        #endif

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

        ret = aes_function_test((unsigned char*)ddt_src, (unsigned char*)(ddt_dst), AES_DDT_FLAG, AES_128, ECB_MODE, len);
        if(!ret){
                 printf("aes-128-ecb ddt mode case pass! \n");
        }
        else{
                 printf("aes-128-ecb ddt mode case failed! \n");
                 return -1;
        }
	return 0;
}





int se_ips_sha_multi_ddt()
{
        int ret;
        int i;
        unsigned long long *ddt_src;
        unsigned long long *ddt_dst;
        unsigned char src[] = "a"; //""what do ya want for nothing?"; //""abc";
	unsigned char src1[] = "bc";
        int len = 3; //8; //28; //0x03;
        unsigned char *psrc;
        unsigned char *psrc1;
        unsigned char *pdst;

        ddt_src = (unsigned long long*)IPS_DDT_SRC;
        ddt_dst = (unsigned long long*)IPS_DDT_DST;
        psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
        psrc1 = (unsigned char*)(IPS_SRC_BASE + 0x100);
        pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);

        ddt_src[0] = IPS_SRC_BASE;
        ddt_src[1] = 0x1;
	ddt_src[2] = IPS_SRC_BASE+0x100;
	ddt_src[3] = 0x2;
        ddt_src[4] = 0x0;
        ddt_src[5] = 0x0;

        ddt_dst[0] = IPS_DST_BASE;
        ddt_dst[1] = 0x17;
        ddt_dst[2] = 0x0;
        ddt_dst[3] = 0x0;
        memcpy(psrc,src,1);
	memcpy(psrc1,src1,2);

        #ifdef DEBUG_PRINT
        printf("beign0: print: \n");
                printf("ddt_src = %llx \n", ddt_src);
                printf("ddt_dst = %llx \n", ddt_dst);
                printf("ddt_src[0]= %llx \n",ddt_src[0]);
                printf("ddt_src[1]= %llx \n",ddt_src[1]);
                printf("ddt_src[2]= %llx \n",ddt_src[2]);
                printf("ddt_src[3]= %llx \n",ddt_src[3]);
                printf("ddt_dst[0]= %llx \n",ddt_dst[0]);
                printf("ddt_dst[1]= %llx \n",ddt_dst[1]);
                printf("ddt_dst[2]= %llx \n",ddt_dst[2]);
                printf("ddt_dst[3]= %llx \n",ddt_dst[3]);
        //for(i=0; i<3; i++)
                printf("src =%x \n",psrc[0]);

        for(i=0; i<2; i++)
                printf("src1 =%x \n",psrc1[i]);
        #endif

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

        /*************************sha1 alg***********************************************/
        ret = sha_function_raw_test((unsigned char*)ddt_src, (unsigned char*)(ddt_dst), SHA_DDT_FLAG,SHA_1, ENCRYPT, len);
        if(!ret){
                printf("sha1 multi ddt mode case pass! \n");
        }
        else {
                printf("sha1 multi ddt mode case failed! \n");
                return -1;
        }

        return 0;
}



int se_ips_aes_multi_ddt()
{
        int ret;
        int i;
        int len = 16;
        unsigned long long *ddt_src;
        unsigned long long *ddt_dst;
        unsigned char *hashkey;
        unsigned char *psrc;
        unsigned char *psrc1;
        unsigned char *pdst;
        unsigned char *pdst1;
        hashkey = NULL;
        unsigned char src[8] = {0x6b,0xc1,0xbe,0xe2,0x2e,0x40,0x9f,0x96};
        unsigned char src1[8] = {0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a};
        unsigned char key128[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
        unsigned char iv[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};

        ddt_src = (unsigned long long*)IPS_DDT_SRC;
        ddt_dst = (unsigned long long*)IPS_DDT_DST;
        psrc = (unsigned char*)IPS_SRC_BASE; //0x50000; //heap_alloc(32);
        psrc1 = (unsigned char*)(IPS_SRC_BASE + 0x100);
        pdst = (unsigned char*)IPS_DST_BASE; //0x60000; //heap_alloc(32);
        pdst1 = (unsigned char*)(IPS_DST_BASE + 0x100);

        ddt_src[0] = IPS_SRC_BASE;
        ddt_src[1] = 0x08;
	ddt_src[2] = IPS_SRC_BASE + 0x100;
	ddt_src[3] = 0x08;
        ddt_src[4] = 0x0;
        ddt_src[5] = 0x0;

        ddt_dst[0] = IPS_DST_BASE;
        ddt_dst[1] = 0x08;
	ddt_dst[2] = IPS_DST_BASE + 0x100;
	ddt_dst[3] = 0x08;
        ddt_dst[4] = 0x0;
        ddt_dst[5] = 0x0;
        memcpy(psrc,src,8);
	memcpy(psrc1,src1,8);

        #ifdef DEBUG_PRINT
        printf("beign0: print: \n");
                printf("ddt_src = %llx \n", ddt_src);
                printf("ddt_dst = %llx \n", ddt_dst);
                printf("ddt_src[0]= %d \n",ddt_src[0]);
                printf("ddt_src[1]= %d \n",ddt_src[1]);
                printf("ddt_src[2]= %d \n",ddt_src[2]);
                printf("ddt_src[3]= %d \n",ddt_src[3]);
                printf("ddt_dst[0]= %d \n",ddt_dst[0]);
                printf("ddt_dst[1]= %d \n",ddt_dst[1]);
                printf("ddt_dst[2]= %d \n",ddt_dst[2]);
                printf("ddt_dst[3]= %d \n",ddt_dst[3]);
        for(i=0; i<16; i++)
                printf("src =%x \n",psrc[i]);
        #endif




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

        ret = aes_function_test((unsigned char*)ddt_src, (unsigned char*)(ddt_dst), AES_DDT_FLAG, AES_128, ECB_MODE, len);
        if(!ret){
                 printf("aes-128-ecb multi ddt mode case pass! \n");
        }
        else{
                 printf("aes-128-ecb multi ddt mode case failed! \n");
                 return -1;
        }
	return 0;
}






