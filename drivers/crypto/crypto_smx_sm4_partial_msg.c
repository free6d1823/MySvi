#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
//#define DEBUG_PRINT
#define IPS_POLLING


int sm4_function_partial_test(unsigned char *psrc, unsigned char *pdst, int alg_flag,int alg_mode,int ende_flag, int proc_len, int src_offset,int dst_offset, int pre_aad_len, int post_aad_len,int icv_offset, int iv_en,int ioc, int p_begin, int p_end )

{
	int i;
	int ret;
	int outlen = 64;


	ret = smx_cmd_partial_create(psrc, pdst, alg_flag, alg_mode, ende_flag, proc_len, src_offset, dst_offset, pre_aad_len, post_aad_len, icv_offset, iv_en, ioc, p_begin, p_end);
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
        //for(i=0; i<outlen; i++) //proc_len
          //      printf("pdst[i] =%x \n", *(pdst + dst_offset +i));
	#endif
	return 0;
}

int se_smx_sm4_partial()
{
	int ret;
	int i;
	int j;
 	int src_offset;
	int dst_offset;
	int pre_aad_len;
	int post_aad_len;
	int icv_offset;
	int iv_en;
	int ioc;
	int p_begin;
	int p_end;
	int alg_mode;

	unsigned char sm4_key[16] =  {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char sm4_iv[16] = {0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};
	unsigned char pre_aad[104] = {0x55,0x55,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0xaa,0xaa};

	unsigned char src[80] = {    0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00
				      /*
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
                                      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
                                      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00*/

				      };
	unsigned char post_aad[40] = {
				      0xdd,0xdd,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0xee,0xee
				     };
	int len;
	unsigned char *psrc;
	unsigned char *pdst;
	unsigned char dest_w[0x100] = {0x0};
	unsigned char dest_p[0x100] = {0x0};
	psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)SMX_DST_BASE; //0x60000; //heap_alloc(32);


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

	#if 1
for(j=0; j<2; j++)
{
	if(j==0){
		alg_mode = ECB_MODE;
		printf("Begin test ECB mode \n");
	}
	if(j==1){
		alg_mode = CBC_MODE;
		printf("Begin test CBC mode \n");
	}

	/********************************************************************************/
	ret = smx_key_iv_set(sm4_key,sm4_iv);
        if(!ret)
                printf("smx module key_iv set case pass \n");
        else
                return -1;

        /*************************sm4 whole alg***********************************************/
	memcpy(psrc,pre_aad,104);
	memcpy(psrc+104,src,80);
	memcpy(psrc+184,post_aad,40);
	src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 104;
        post_aad_len = 40;
        icv_offset = 0;
        iv_en = 0;
        ioc = 0;
        p_begin = 1;
        p_end = 1;
        len = 184;


	ret = sm4_function_partial_test(psrc, pdst, SM4_FLAG,alg_mode, ENCRYPT,len,src_offset, dst_offset, pre_aad_len, post_aad_len, icv_offset, iv_en, ioc, p_begin, p_end);
	if(!ret){
		 	printf("sm4 whole alg case pass! \n");
	}
	else {
		 	printf("sm4 whole alg case failed! \n");
			return -1;
	}

	memcpy(dest_w,pdst,80);
	#ifdef DEBUG_PRINT
	for(i=0; i<80; i++)
		printf("dest_w = %x \n", dest_w[i]);
	#endif
	#endif
	#if 1
	/*************************sm4 partial alg******************************************/
	ret = smx_key_iv_set(sm4_key,sm4_iv);
        if(!ret)
                printf("smx module key_iv set case pass \n");
        else
                return -1;
	/**********************sub-command 1*********************************************/
	memset(psrc,0,0x100);
	memset(pdst,0,0x100);
	memcpy(psrc,pre_aad,64);
	//memcpy(psrc,src,64);
	src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 64;
        post_aad_len = 0;
        icv_offset = 0;
        iv_en = 0;
        ioc = 0;
        p_begin = 1;
        p_end = 0;
	len = 64;
	ret = sm4_function_partial_test(psrc,pdst,SM4_FLAG,alg_mode,ENCRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
	if(!ret)
		printf("sm4 sub-command 1 case pass!\n");
	else
		printf("sm4 sub-command 1 case fail!\n");
	//for(i=0; i<8; i++)
	//	printf("pdest = %x \n", pdst[i]);

	/*********************sub-command 2*************************************************/
	/*ret = smx_key_iv_set(sm4_key,sm4_iv);
        if(!ret)
                printf("smx module key_iv set case pass \n");
        else
                return -1;*/
	/**********************************************************************************/
	memset(psrc,0,0x100);
	memcpy(psrc,pre_aad+64,40);
	memcpy(psrc+40,src,64);
	//memcpy(psrc,src+64,64);
	src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 40;
        post_aad_len = 0;
        icv_offset = 0;
        iv_en = 0;
        ioc = 0;
        p_begin = 0;
        p_end = 0;
        len = 104;

        ret = sm4_function_partial_test(psrc,pdst,SM4_FLAG,alg_mode, ENCRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
        if(!ret)
                printf("sm4 sub-command 2 case pass!\n");
        else
                printf("sm4 sub-command 2 case fail!\n");

	/*********************sub-command 3*************************************************/
	memset(psrc,0,0x100);
	memcpy(psrc,src+64,16);
	memcpy(psrc+16,post_aad,40);
        src_offset = 0;
        dst_offset = 64;
        pre_aad_len = 0;
        post_aad_len = 40;
        icv_offset = 0;
        iv_en = 0;
        ioc = 0;
        p_begin = 0;
        p_end = 1;
        len = 16;

        ret = sm4_function_partial_test(psrc,pdst,SM4_FLAG,alg_mode,ENCRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
        if(!ret)
                printf("sm4 sub-command 3 case pass!\n");
        else
                printf("sm4 sub-command 3 case fail!\n");
	#endif

	memcpy(dest_p,pdst,80);
	#ifdef DEBUG_PRINT
	for(i=0; i<8; i++)
		printf("dest_p = %x \n", dest_p[i]);

	#endif
	#if 1
        ret = str_cmp(dest_p, dest_w, 80);
        if(!ret){
		printf("sm4 sub-command result is same as whole-command result \n");
		//return 0;
	}
	else {
                printf("sm4 result between sub-command and whole command are different\n");
		return -1;
	}
	#endif

	/*******************************************Decrypt*************************************************************/
	#if 0
	/*************************sm4 whole alg***********************************************/
        memcpy(pdst+0x800,pre_aad,104);
        memcpy(pdst+0x800+104,dest_w,80);
        memcpy(pdst+184,post_aad,40);
        src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 104;
        post_aad_len = 40;
        icv_offset = 0;
        iv_en = 0;
        ioc = 0;
        p_begin = 1;
        p_end = 1;
        len = 184;


        ret = sm4_function_partial_test(pdst+0x800, psrc+0x800, SM4_FLAG,alg_mode, DECRYPT,len,src_offset, dst_offset, pre_aad_len, post_aad_len, icv_offset, iv_en, ioc, p_begin, p_end);
        if(!ret){
                        printf("sm4 whole alg case pass! \n");
        }
        else {
                        printf("sm4 whole alg case failed! \n");
                        return -1;
        }

        memcpy(dest_w,psrc+0x800,80);
        #ifdef DEBUG_PRINT
        for(i=0; i<8; i++)
                printf("dest_w = %x \n", dest_w[i]);
        #endif
	#endif

	#if 1
        /**********************sub-command 1*********************************************/
  	memset(pdst+0x800,0,0x100);
	memset(psrc+0x800,0,0x100);
        memcpy(pdst+0x800,pre_aad,64);
        src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 64;
        post_aad_len = 0;
        icv_offset = 0;
        iv_en = 0;
        ioc = 0;
        p_begin = 1;
        p_end = 0;
        len = 64;

        ret = sm4_function_partial_test(pdst+0x800,psrc+0x800,SM4_FLAG,alg_mode,DECRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
        if(!ret)
                printf("sm4 sub-command 1 case pass! \n");
        else
                printf("sm4 sub-command 1 case fail! \n");
        //for(i=0; i<8; i++)
        //      printf("pdest = %x \n", pdst[i]);

        /*********************sub-command 2*************************************************/
        ret = smx_key_iv_set(sm4_key,sm4_iv);
        if(!ret)
                printf("smx module key_iv set case pass \n");
        else
                return -1;
        /**********************************************************************************/
        //memset(psrc,0,0x100);
        memcpy(pdst+0x800,pre_aad+64,40);
        memcpy(pdst+0x800+40,dest_p,64);
        src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 40;
        post_aad_len = 0;
        icv_offset = 0;
        iv_en = 0;
        ioc = 0;
        p_begin = 0;
        p_end = 0;
        len = 104;

        ret = sm4_function_partial_test(pdst+0x800,psrc+0x800,SM4_FLAG,alg_mode, DECRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
        if(!ret)
                printf("sm4 sub-command 2 case pass! \n");
        else
                printf("sm4 sub-command 2 case fail! \n");
        /*********************sub-command 3*************************************************/
        //memset(psrc,0,0x100);
        memcpy(pdst+0x800,dest_p+64,16);
        memcpy(pdst+0x800+16,post_aad,40);
        src_offset = 0;
        dst_offset = 64;
        pre_aad_len = 0;
        post_aad_len = 40;
        icv_offset = 0;
        iv_en = 0;
        ioc = 0;
        p_begin = 0;
        p_end = 1;
        len = 16;

        ret = sm4_function_partial_test(pdst+0x800,psrc+0x800,SM4_FLAG,alg_mode,DECRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
        if(!ret)
                printf("sm4 sub-command 3 case pass! \n");
        else
                printf("sm4 sub-command 3 case fail! \n");
        memcpy(dest_w,psrc+0x800,80);
        #ifdef DEBUG_PRINT
        for(i=0; i<8; i++)
                printf("dest_w = %x \n", dest_w[i]);
        #endif
	#endif

        #if 1
        ret = str_cmp(dest_w, src, 80);
        if(!ret){
		printf("sm4 sub-command decrypt result is the same as source plain text\n");
                //return 0;
		}
        else {
                printf("sm4 sub-command decrypt result is not the same as source plain text\n");
                return -1;
        }
	#endif

	if(j==0){
                alg_mode = ECB_MODE;
                printf("End test ECB mode \n");
        }
        if(j==1){
                alg_mode = CBC_MODE;
                printf("End test CBC mode \n");
        }


}
	return 0;

}


