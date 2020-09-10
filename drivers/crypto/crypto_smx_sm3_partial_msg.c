#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
//#define DEBUG_PRINT
#define IPS_POLLING

int sm3_function_whole_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int ende_flag, int proc_len,int src_offset,int dst_offset, int pre_aad_len, int post_aad_len,int icv_offset, int iv_en,int ioc, int p_begin, int p_end)
{
        int i;
        int ret;
        int outlen = 32;

        ret = smx_cmd_partial_create(psrc, pdst, alg_flag, HASH_RAW_MODE, ende_flag, proc_len,src_offset, dst_offset, pre_aad_len, post_aad_len, icv_offset, iv_en, ioc, p_begin, p_end);

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
        //for(i=0; i<outlen+proc_len; i++) //proc_len
          //     printf("pdst[i] =%x \n", pdst[i]);
        #endif
        return 0;
}


int smx_data_setup_partial_sm3(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int hash_mode, int ende_flag, int proc_len, int src_offset, int dst_offset, int pre_aad_len, int post_aad_len, int icv_offset, int iv_en, int ioc, int p_begin, int p_end)
{

        memset(pcmd,0,0x40);
        /*setup the actual cmd ring data from alg_ctx  or call back? */
        pcmd->src_pkt_addr_l = (unsigned long)src;
        pcmd->src_pkt_addr_h = 0;
        pcmd->dst_pkt_addr_l = (unsigned long)dst;
        pcmd->dst_pkt_addr_h = 0;

        pcmd->dst_pkt_off = dst_offset;  //no offset
        pcmd->src_pkt_off = src_offset;

        pcmd->pre_aad_len = pre_aad_len;
        pcmd->post_aad_len = post_aad_len;
        pcmd->proc_len = proc_len;

        pcmd->icv_offset = icv_offset;
        pcmd->iv_offset = 0;
        pcmd->iv_enable = iv_en;

        /*control*/
        pcmd->MSG_END = p_end;
        pcmd->MSG_BEGIN = p_begin;
        pcmd->key_exp = 0;
        pcmd->icv_append = 1;
        pcmd->icv_enc = 0;
        pcmd->icv_pt = 1;
        pcmd->aad_copy = 1;
        pcmd->encrypt = ende_flag;
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = 0;
        pcmd->key_port = 0;
        pcmd->mode = hash_mode;
        pcmd->ioc = ioc;
        /*aux_info*/
        pcmd->icv_len = 0;
        pcmd->cbc_cs_sel = 0;
        pcmd->bk_sz_cfb = 0;
        pcmd->sw_id = 0;

        return 0;


}

int smx_data_setup_partial_sm4(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int cipher_mode, int ende_flag, int proc_len,int src_offset, int dst_offset, int pre_aad_len, int post_aad_len, int icv_offset, int iv_en, int ioc, int p_begin, int p_end)
{
        int mode;
        int cbc_submode;

        switch(cipher_mode)
        {
                case 0x40:
                        mode = 0x04;
                        cbc_submode = 0x0;
                break;

                case 0x41:
                        mode = 0x04;
                        cbc_submode = 0x1;
                break;

                case 0x42:
                        mode = 0x04;
                        cbc_submode = 0x2;
                break;

                case 0x43:
                        mode = 0x04;
                        cbc_submode = 0x3;
                break;

                default:
                        mode = cipher_mode;
                break;

        }


        memset(pcmd,0,0x40);
        /*setup the actual cmd ring data from alg_ctx  or call back? */
        pcmd->src_pkt_addr_l = (unsigned long)src;
        pcmd->src_pkt_addr_h = 0;
        pcmd->dst_pkt_addr_l = (unsigned long)dst;
        pcmd->dst_pkt_addr_h = 0;
        pcmd->dst_pkt_off = dst_offset;
        pcmd->src_pkt_off = src_offset;

        pcmd->pre_aad_len = pre_aad_len;
        pcmd->post_aad_len = post_aad_len;
        pcmd->proc_len = proc_len;
        pcmd->icv_offset = icv_offset;
        pcmd->iv_offset = 0;
	pcmd->iv_enable = iv_en;
        pcmd->MSG_BEGIN = p_begin;
        pcmd->MSG_END = p_end;

        if(!ende_flag){
                 pcmd->key_exp = 1;
        }
        else{
                 pcmd->key_exp = 0;
        }
        //printf("key_exp = %x \n", pcmd->key_exp);
        pcmd->icv_append = 0;
        pcmd->icv_enc = 0;
        pcmd->icv_pt = 0;
        if(cipher_mode == GCM_MODE)
                pcmd->aad_copy = 1;
        else
                pcmd->aad_copy = 0;

        pcmd->aad_copy = 0;
        pcmd->encrypt = ende_flag; //encrypt ctx->sm4.ende_flag
        //printf("ende_flag = %d \n", ende_flag);
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = 0;
        pcmd->key_port = 0;
        pcmd->mode = mode;//opt;//
        //printf("cipher_mode = %d \n", cipher_mode);
        pcmd->ioc = 0;  //not IOC

        pcmd->icv_len = 0;
        pcmd->cbc_cs_sel = cbc_submode;
        pcmd->bk_sz_cfb = 0;

        return 0;

}





int smx_cmd_partial_create(unsigned char *src, unsigned char *dst, int flag, int alg_mode, int ende_flag, int proc_len,int src_offset,int dst_offset, int pre_aad_len, int post_aad_len,int icv_offset, int iv_en,int ioc, int p_begin, int p_end )
{
        int i;
        int ret_value;
        unsigned int producer_idx;
        unsigned int consumer_idx;
        unsigned int cmd_base;
        struct smx_command* pcmd = (struct smx_command*)SMX_CMD_RING; // heap_alloc(0x40);


        producer_idx = READ_REG(SMX_VF0_REG_C0_MAILBOX_0);
        #ifdef DEBUG_PRINT
        printf("producer_idx = %x \n", producer_idx);
        #endif
        consumer_idx = READ_REG(SMX_VF0_REG_C0_MAILBOX_1);
        #ifdef DEBUG_PRINT
        printf("consumer_idx = %x \n", consumer_idx);
        #endif
        /*fifo status full*/
        if (producer_idx % MAX_CMD + 1 == consumer_idx % MAX_CMD){
                printf("command ring full! \n");
                return -1;

        }

        switch(flag)
        {
                case 0:
                        ret_value = smx_data_setup_partial_sm3(src,dst,pcmd,alg_mode,ende_flag,proc_len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
                break;

                case 1:
                        ret_value = smx_data_setup_partial_sm4(src,dst,pcmd,alg_mode,ende_flag,proc_len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
                break;


                default:
                break;

        }


        if(ret_value)
                printf("smx module data setup for smx case failed! \n");

        cmd_base = READ_REG(SMX_VF0_REG_RING_CTRL_0);
        #ifdef DEBUG_PRINT
        printf("cmd_base = %x \n", cmd_base);
        #endif

        memcpy((void*)(uintptr_t)(cmd_base + 64*producer_idx), (void*)pcmd, 64);
        #ifdef DEBUG_PRINT
       // for (i = 0; i < 64; i++)
         //       printf("cmdring #_%#x  value= %#x\n", i, *(unsigned char*)(uintptr_t)(cmd_base + 64*producer_idx + i));
        #endif
        producer_idx++;

        producer_idx = producer_idx % MAX_CMD;
        WRITE_REG(SMX_VF0_REG_C0_MAILBOX_0, producer_idx);

        /*for debug*/
        ret_value = READ_REG(SMX_VF0_WD_CTRL_0);
        producer_idx = READ_REG(SMX_VF0_REG_C0_MAILBOX_0);
        #ifdef DEBUG_PRINT
        printf("producer_idx = %x \n", producer_idx);
        #endif

        return 0;


}




int sm3_function_partial_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int ende_flag, int proc_len, int src_offset,int dst_offset, int pre_aad_len, int post_aad_len,int icv_offset, int iv_en,int ioc, int p_begin, int p_end )

{
	int i;
	int ret;
	int outlen = 32;


	ret = smx_cmd_partial_create(psrc, pdst, alg_flag, HASH_RAW_MODE, ende_flag, proc_len, src_offset, dst_offset, pre_aad_len, post_aad_len, icv_offset, iv_en, ioc, p_begin, p_end);
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

int se_smx_sm3_partial()
{
	int ret;
	int i;
 	int src_offset;
	int dst_offset;
	int pre_aad_len;
	int post_aad_len;
	int icv_offset;
	int iv_en;
	int ioc;
	int p_begin;
	int p_end;
	unsigned char pre_aad[104] = {0x55,0x55,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0xaa,0xaa};

	unsigned char src[80] = {     0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
				      0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00
				      /*0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00,
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
	unsigned char dgst_w[32] = {0x0};
	unsigned char dgst_p[32] = {0x0};
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
        /*************************sm3 whole alg***********************************************/
	memcpy(psrc,pre_aad,104);
	memcpy(psrc+104,src,80);
	memcpy(psrc+184,post_aad,40);
	src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 104;
        post_aad_len = 40;
        icv_offset = 184;
        iv_en = 0;
        ioc = 0;
        p_begin = 1;
        p_end = 1;
        len = 184;

	ret = sm3_function_whole_test(psrc, pdst, SM3_FLAG, ENCRYPT,len,src_offset, dst_offset, pre_aad_len, post_aad_len, icv_offset, iv_en, ioc, p_begin, p_end);
	if(!ret){
		 	printf("sm3 whole alg case pass! \n");
	}
	else {
		 	printf("sm3 whole alg case failed! \n");
			return -1;
	}

	memcpy(dgst_w,pdst+184,0x20);
	#ifdef DEBUG_PRINT
	for(i=0; i<0x20; i++)
		printf("dgst_w = %x \n", dgst_w[i]);
	#endif
	#endif
	/*************************sm3 partial alg******************************************/
	/**********************sub-command 1*********************************************/
	memset(psrc,0,0x100);
	memcpy(psrc,pre_aad,64);
	src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 64;
        post_aad_len = 0;
        icv_offset = 64;
        iv_en = 0;
        ioc = 0;
        p_begin = 1;
        p_end = 0;
	len = 64;
	ret = sm3_function_partial_test(psrc,pdst,SM3_FLAG,ENCRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
	if(!ret)
		printf("sm3 sub-command 1 case pass!\n");
	else
		printf("sm3 sub-command 1 case fail!\n");
	/*********************sub-command 2*************************************************/
	memset(psrc,0,0x100);
	memcpy(psrc,pre_aad+64,40);
	memcpy(psrc+40,src,64);
	src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 40;
        post_aad_len = 0;
        icv_offset = 104;
        iv_en = 0;
        ioc = 0;
        p_begin = 0;
        p_end = 0;
        len = 104;

        ret = sm3_function_partial_test(psrc,pdst,SM3_FLAG,ENCRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
        if(!ret)
                printf("sm3 sub-command 2 case pass!\n");
        else
                printf("sm3 sub-command 2 case fail!\n");

	/*********************sub-command 3*************************************************/
	memset(psrc,0,0x100);
	memcpy(psrc,src+64,16);
	memcpy(psrc+16,post_aad,40);
        src_offset = 0;
        dst_offset = 0;
        pre_aad_len = 0;
        post_aad_len = 40;
        icv_offset = 16;
        iv_en = 0;
        ioc = 0;
        p_begin = 0;
        p_end = 1;
        len = 16;

        ret = sm3_function_partial_test(psrc,pdst,SM3_FLAG,ENCRYPT, len,src_offset,dst_offset,pre_aad_len,post_aad_len,icv_offset,iv_en,ioc,p_begin,p_end);
        if(!ret)
                printf("sm3 sub-command 3 case pass!\n");
        else
                printf("sm3 sub-command 3 case fail!\n");

	memcpy(dgst_p,pdst+16,0x20);
	#ifdef DEBUG_PRINT
	for(i=0; i<0x20; i++)
		printf("dgst_wp = %x \n", dgst_p[i]);
	#endif
        ret = str_cmp(dgst_w, dgst_p, 0x20);
        if(!ret){
		printf("sm3 result between whole msg test and partial msg test are the same\n");
		return 0;
	}
	else {
                printf("sm3 result between whole msg test and partial msg test are different\n");
		return -1;
	}

	return 0;
}


