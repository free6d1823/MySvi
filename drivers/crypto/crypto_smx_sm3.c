#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
//#define DEBUG_PRINT
#define IPS_POLLING

int sm3_function_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int ende_flag, int proc_len)
{
	int i;
	int ret;
	int outlen = 32;

	//unsigned char dgst[32]={0xff,0xe0,0x74,0x34,0x44,0x70,0x01,0x63,0x0f,0x78,0x17,0xdb,0xed,0x2b,0xfe,0x5a,0x4e,0x0a,0x76,0xbd,0x34,0x61,0x22,0x2f,0xf2,0xb1,0x89,0x52,0x63,0x5c,0x9d,0x51};
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
	#ifdef DEBUG_PRINT
        for(i=0; i<outlen; i++) //proc_len
                printf("pdst[i] =%x \n", pdst[proc_len+i]);
       // for(i=0; i<outlen; i++)
         //       printf("dgst = %x \n",dgst[i]);
	#endif
        ret = str_cmp((pdst+proc_len), dgst, outlen);
        if(!ret)
		return 0;
	else {
                printf("sm3 result between engine and sw are different");
		return -1;
	}
}

int se_smx_sm3()
{
	int ret;
	int i;
	/*unsigned char src[] = {	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //ki
				0x00, 0x00, 0x00, 0x01, 0x89, 0xab, 0xcd, 0xef,   // i&label
				0x01, 0x23, 0x45, 0x67, 0x00, 0x00, 0x00,0x80
			      };
	*/

	unsigned char src[] = "abc";
	int len = 3;
	unsigned char *psrc;
	unsigned char *pdst;

//	if(argc < 2)
  //              return -EUSAGE;
	psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);

	memcpy(psrc,src,len);

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
		ret = sm3_function_test(psrc, pdst, SM3_FLAG, ENCRYPT, len);
		if(!ret){
		 	printf("sm3 alg case pass! \n");
			return 0;
		}
		else {
		 	printf("sm3 alg case failed! \n");
			return -1;
		}
	return 0;
}


