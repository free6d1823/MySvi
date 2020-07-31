#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <target/utils.h>
#include "crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"

#define DEBUG_PRINT

int smx_init_clk(void)
{
        int ret_value;

        /*initialzie clock enalbe for SMX-SRAM clock and SMX-FUNCTION*/
        WRITE_REG(SMX_VF_REG_GLB_OPT, 0x0);
        ret_value = READ_REG(SMX_VF_REG_GLB_OPT);
        if(ret_value != 0){
                printf("smx ram clock enable failed!");
                return -1;
        }


         /* vf_free */
        ret_value = READ_REG(SMX_VF0_REG_VF_FREE);
        if(ret_value == 1)
        {
                /*VF ALLOC*/
                printf("vf free! \n");
                WRITE_REG(SMX_VF0_REG_VF_ALLOC, 1);
                ret_value = READ_REG(SMX_VF0_REG_VF_ALLOC);
                if(ret_value == 1)
                        printf("security attribute consistent!\n");
                else
                        printf("security attribute not consistent!\n");
        }

        return 0;
}



int smx_module_reset()
{
	int ret_value;
	int count;
	ret_value = READ_REG(SMX_VF0_REG_RING_INIT_1);
	while((ret_value != 3)&&(count != 100)) {
		 ret_value = READ_REG(SMX_VF0_REG_RING_INIT_1);
			count++;
		}
	if(count == 100)
		return -1;
	else{
 		WRITE_REG(SMX_VF0_REG_RING_INIT_2,1);
		WRITE_REG(SMX_VF0_REG_RING_INIT_3,1);
		return 0;
	}
}

int smx_dev_init()
{
	int ret_value = 0;
	unsigned int cmd_base;
	unsigned int status_base;

	cmd_base = SMX_CMD_BASE;
	status_base = SMX_STATUS_BASE;

	/*set cmd and status base addr*/
	WRITE_REG(SMX_VF0_REG_RING_CTRL_0,cmd_base);   //low
	ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_0);
	if(ret_value != cmd_base){
		printf("set cmd base failed \n");
		return -1;
	}
	WRITE_REG(SMX_VF0_REG_RING_CTRL_1,0);   //high
	WRITE_REG(SMX_VF0_REG_RING_CTRL_4,status_base); //low
	ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_4);
	if(ret_value != status_base) {
		printf("set status base failed \n");
		return -1;
	}
	WRITE_REG(SMX_VF0_REG_RING_CTRL_5,0); //high

	/*set cmd ring descriptior count and status ring descriptior count*/
	WRITE_REG(SMX_VF0_REG_RING_CTRL_8,0x00400040);
	ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_8);
	if(ret_value != 0x00400040){
		printf("set descriptior count failed \n");
		return -1;
	}
	/*set irq triger threshold value*/
	WRITE_REG(SMX_VF0_REG_IRQ_CTRL_0,0x00010001);
	ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_0);
	if(ret_value != 0x00010001){
		printf("set irq triger threshold failed \n");
		return -1;
	}
	/*enable irq channel 0 */
	WRITE_REG(SMX_VF0_REG_IRQ_EN,0x80001451);
	ret_value = READ_REG(SMX_VF0_REG_IRQ_EN);
	if(ret_value != 0x80001451){
		printf("enable irq channel 0 failed \n");
		return -1;
	}
	/*enable channel 0*/
	WRITE_REG(SMX_VF0_REG_RING_INIT_0,1);
	ret_value = READ_REG(SMX_VF0_REG_RING_INIT_0);
	if(ret_value !=1){
		printf("channel 0 enable failed \n");
		return -1;
	}
	return 0;
}

int smx_key_iv_set()
{
	int i;
	int ret_value;
	unsigned char skey[] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	unsigned char siv[] = {0xeb, 0xee, 0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};
	unsigned int *key;
	unsigned int *iv;

	key = (unsigned int *)skey;
	iv = (unsigned int *)siv;
	//for(i=0; i<8; i++)
	//	key[i] = 0x0; //0xffffffff;
	//for(i=0; i<4; i++)
	//	iv[i] = 0x0;  //0x11111111;
	for(i=0; i<4; i++)
	{
		writel(key[i], (uintptr_t)(SMX_VF0_KEY + 4*i));
		//WRITE_REG(SMX_VF0_KEY + 4*i, key[i]);
		printf("key[i]= %x", key[i]);
	}

	for(i=0; i<4; i++)
	{
		writel(iv[i],(uintptr_t)(SMX_VF0_KEY+16+4*i));
		//WRITE_REG(SMX_VF0_KEY+16+4*i, iv[i]);
		printf("key[i] = %x \n", iv[i]);
	}

	ret_value = READ_REG(SMX_VF0_KEY);
	printf("ret_value = %x \n", ret_value);
	if(ret_value != 0x67452301){             //0xffffffff
		printf("key set failed \n");
		return -1;
	}
	for(i=0; i<8; i++)
	{
		ret_value = READ_REG(SMX_VF0_KEY);
		#ifdef DEBUG_PRINT
		printf("key = %x \n",ret_value);
		#endif
	}

	return 0;
}


int smx_data_setup_sm3(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int hash_mode, int ende_flag, int proc_len)
{

	memset(pcmd,0,0x40);
        /*setup the actual cmd ring data from alg_ctx  or call back? */
        pcmd->src_pkt_addr_l = (unsigned long)src;
        pcmd->src_pkt_addr_h = 0;
        pcmd->dst_pkt_addr_l = (unsigned long)dst;
        pcmd->dst_pkt_addr_h = 0;

        pcmd->dst_pkt_off = 0;  //no offset
        pcmd->src_pkt_off = 0;

        pcmd->pre_aad_len = 0;
        pcmd->post_aad_len = 0;
        pcmd->proc_len = 3;//strlen(src);

        pcmd->icv_offset = 3; //0
        pcmd->iv_offset = 0;
        pcmd->iv_enable = 0;

        /*control*/
        pcmd->MSG_END = 1; //only one command
        pcmd->MSG_BEGIN = 1;
        pcmd->key_exp = 0;
        pcmd->icv_append = 1;
        pcmd->icv_enc = 0;
        pcmd->icv_pt = 1;
        pcmd->aad_copy = 0;
        pcmd->encrypt = ende_flag;
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = 0;
        pcmd->key_port = 0;
        pcmd->mode = hash_mode;
        pcmd->ioc = 0;  //not IOC
	/*aux_info*/
        pcmd->icv_len = 0;
        pcmd->cbc_cs_sel = 0;
        pcmd->bk_sz_cfb = 0;
	pcmd->sw_id = 0;

        return 0;


}

int smx_data_setup_sm4(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int cipher_mode, int ende_flag, int proc_len)
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
        pcmd->dst_pkt_off = 0;  //no offset
        pcmd->src_pkt_off = 0;

        pcmd->pre_aad_len = 0;
        pcmd->post_aad_len = 0;
        pcmd->proc_len = proc_len;
	printf("proc_len = %d \n", proc_len);
        pcmd->icv_offset = 0;
        pcmd->iv_offset = 0;
        pcmd->iv_enable = 0;

        pcmd->MSG_BEGIN = 0;
	pcmd->MSG_END = 0;
	if(ende_flag == 0)
       		 pcmd->key_exp = 1;
	else
		 pcmd->key_exp = 0;
        pcmd->icv_append = 0;
        pcmd->icv_enc = 0;
        pcmd->icv_pt = 0;
        pcmd->aad_copy = 0;
        pcmd->encrypt = ende_flag; //encrypt ctx->sm4.ende_flag
	printf("ende_flag = %d \n", ende_flag);
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = 0;
        pcmd->key_port = 0;
        pcmd->mode = cipher_mode;//opt;//
	printf("cipher_mode = %d \n", cipher_mode);
        pcmd->ioc = 0;  //not IOC

        pcmd->icv_len = 0;
        pcmd->cbc_cs_sel = 0;
        pcmd->bk_sz_cfb = 0;

        return 0;

}


int smx_cmd_create(unsigned char *src, unsigned char *dst, int flag, int alg_mode, int ende_flag, int proc_len)
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
	if(flag == 0){ //sm3
		ret_value = smx_data_setup_sm3(src,dst,pcmd,alg_mode,ende_flag,proc_len);
	}
	if(flag == 1){//sm4

		printf("ende_flag = %d \n", ende_flag);
		ret_value = smx_data_setup_sm4(src,dst,pcmd,alg_mode,ende_flag,proc_len);
	}

	if(!ret_value)
                printf("smx module data setup for smx case pass! \n");

	cmd_base = READ_REG(SMX_VF0_REG_RING_CTRL_0);
	#ifdef DEBUG_PRINT
	printf("cmd_base = %x \n", cmd_base);
	#endif
	memcpy((void*)(uintptr_t)(cmd_base + 64*producer_idx), (void*)pcmd, 64);
	#ifdef DEBUG_PRINT
	for (i = 0; i < 64; i++)
                printf("cmdring #_%#x  value= %#x\n", i, *(unsigned char*)(uintptr_t)(cmd_base + 64*producer_idx + i));
	#endif
	producer_idx++;
	producer_idx = producer_idx % MAX_CMD;
	WRITE_REG(SMX_VF0_REG_C0_MAILBOX_0, producer_idx);
	producer_idx = READ_REG(SMX_VF0_REG_C0_MAILBOX_0);
	#ifdef DEBUG_PRINT
	printf("producer_idx = %x \n", producer_idx);
	#endif
	return 0;
}

int smx_status_polling()
{
	int i;
	int ret_value;
	int status_base;
	struct status_ring* ring;

	status_base = READ_REG(SMX_VF0_REG_RING_CTRL_4);
	ring = (struct status_ring*)(uintptr_t)status_base;
	for(i=0; i<10; i++)
	{
		ret_value = READ_REG(SMX_VF0_REG_IRQ_RAW);
		#ifdef DEBUG_PRINT
		printf("irq_raw = %x \n",ret_value);
		#endif
		ret_value = READ_REG(SMX_VF0_REG_C0_RING_STS_0);
		#ifdef DEBUG_PRINT
		printf("ring_sts = %x \n",ret_value);
		#endif
	}
	#ifdef DEBUG_PRINT
	printf("stsring ret_code  value= %#x\n", ring->ret_code);
        printf("stsring sw_id value= %#x\n", ring->sw_id);
	#endif

	return 0;

}


#if 0
int smx_main()
{
	int ret;
	int i;

	size_t offset = 0;
	struct status_ring* ring;
	unsigned char src[] = "abc";
	unsigned char nonce_counter[16] = {0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
      					   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 
					  };

	//unsigned char src[] = "1122334455667788";
	unsigned char dgst[64]={0x0};
	unsigned char sw_dst[32];
	unsigned char *psrc;
	unsigned char *pdst;
	unsigned char key[32] = {0x0};
        unsigned char iv[16] = {0x0};
	unsigned char stream_block[16];
	//mbedtls_aes_context aes_ctx;

	psrc = (unsigned char*)SMX_SRC_BASE; //0x50000; //heap_alloc(32);
	pdst = (unsigned char*)SMX_DST_BASE; //0x50020; //heap_alloc(32);

//	printf("psrc = %x\n",psrc);
//	printf("pdst = %x\n",pdst);
	//memcpy(psrc,src,0x10);
	memcpy(psrc,src,0x03);
//	printf("psrc = %s \n",psrc);
	ret = smx_init_clk();
	if(!ret)
		printf("smx module clock case pass! \n");

	ret = smx_module_reset();
	if(!ret)
		printf("smx module reset case pass! \n");

/*for debug by yyq*/
     //    printf("begin read watch dog register!\n");
     //   ret = READ_REG(SMX_VF0_WD_CTRL_0);


	ret = smx_dev_init();
	if(!ret)
		printf("smx module initialzie case pass! \n");

	ret = smx_key_iv_set();
	if(!ret)
		printf("smx module key_iv set case pass \n");


        /*************************sm3 alg***********************************************/
	ret = smx_cmd_create(psrc, pdst, 0, HASH_RAW_MODE, ENCRYPT,3);
	if(ret)
		printf("smx module smx_cmd_create for sm3 failed!");

	ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for sm4-128-ecb failed! \n");
        for(i=0; i<32; i++)
                printf("dst = %x \n",pdst[i]);

#if 0
	/*************************sha224 alg**********************************************/
	ret = smx_cmd_create(psrc, pdst, 0, SHA_224, HASH_RAW_MODE, ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_create for sha_224 failed!");
	/*************************sha256 alg**********************************************/
        ret = smx_cmd_create(psrc, pdst, 0, SHA_256, HASH_RAW_MODE, ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_create for sha_256 failed!");
	/*************************sha384 alg**********************************************/
        ret = smx_cmd_create(psrc, pdst, 0, SHA_384, HASH_RAW_MODE, ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_create for sha_384 failed!");

	/*************************sha512 alg**********************************************/
        ret = smx_cmd_create(psrc, pdst, 0, SHA_512, HASH_RAW_MODE, ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_create for sha_512 failed!");
	/***********************calculate aes-128-ecb********************************/
	/*1. hw encrypt*/

	ret = smx_cmd_create(psrc,pdst,1,AES_128,ECB_MODE,ENCRYPT);
	if(ret)
		printf("smx module smx_cmd_creaete for aes-128-ecb failed! \n");

	ret = smx_status_polling();
	if(ret)
		printf("smx module smx_status_polling for aes-128-ecb failed! \n");
	for(i=0; i<16; i++)
		printf("dst = %x \n",pdst[i]);
	/*2. hw decrypt*/
	ret = smx_cmd_create(pdst,psrc+0x10,1,AES_128,ECB_MODE,DECRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ecb failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ecb failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",psrc[0x10+i]);


	/***************************************************************************/
	  /***********************calculate aes-128-ecb********************************/
        /*1. hw encrypt*/

        ret = smx_cmd_create(psrc,pdst,1,AES_128,ECB_MODE,ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ecb failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ecb failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",pdst[i]);
        /*2. hw decrypt*/
        ret = smx_cmd_create(pdst,psrc+0x10,1,AES_128,ECB_MODE,DECRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ecb failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ecb failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",psrc[0x10+i]);

        //ret = memcmp(psrc,psrc+0x10,0x10);
        ret = strcmp((char*)psrc, (char*)(psrc+0x10));
        if(ret)
                printf("decrypt data and source data are different!\n");

	/***********************calculate aes-128-cbc********************************/
        /*1. hw encrypt*/

        ret = smx_cmd_create(psrc,pdst,1,AES_128,CBC_MODE,ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-cbc failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-cbc failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",pdst[i]);
        /*2. hw decrypt*/
        ret = smx_cmd_create(pdst,psrc+0x10,1,AES_128,CBC_MODE,DECRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-cbc failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-cbc failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",psrc[0x10+i]);

        //ret = memcmp(psrc,psrc+0x10,0x10);
        ret = strcmp((char*)psrc, (char*)(psrc+0x10));
        if(ret)
                printf("decrypt data and source data are different!\n");

        /*3. sw encrypt*/
         mbedtls_aes_init( &aes_ctx );
         mbedtls_aes_setkey_enc( &aes_ctx, key,128);
         mbedtls_aes_crypt_cbc( &aes_ctx, MBEDTLS_AES_ENCRYPT,16,iv, psrc, sw_dst );

         //ret = memcmp(pdst,sw_dst,16);
         ret = strcmp((char*)pdst, (char*)sw_dst);
         if(ret)
                printf("encrypt data between engine and sw are different ");

        /***************************************************************************/
	/***********************calculate aes-128-cfb********************************/
        /*1. hw encrypt*/

        ret = smx_cmd_create(psrc,pdst,1,AES_128,CFB_MODE,ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ecb failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ecb failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",pdst[i]);
        /*2. hw decrypt*/
        ret = smx_cmd_create(pdst,psrc+0x10,1,AES_128,CFB_MODE,DECRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ecb failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ecb failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",psrc[0x10+i]);

        //ret = memcmp(psrc,psrc+0x10,0x10);
        ret = strcmp((char*)psrc, (char*)(psrc+0x10));
        if(ret)
                printf("decrypt data and source data are different!\n");

        /*3. sw encrypt*/
         mbedtls_aes_init( &aes_ctx );
         mbedtls_aes_setkey_enc( &aes_ctx, key,128);
         mbedtls_aes_crypt_cfb128( &aes_ctx, MBEDTLS_AES_ENCRYPT,16,&offset,iv, psrc, sw_dst);

         //ret = memcmp(pdst,sw_dst,16);
         ret = strcmp((char*)pdst, (char*)sw_dst);
         if(ret)
                printf("encrypt data between engine and sw are different ");

        /***************************************************************************/
	/***********************calculate aes-128-ctr*******************************/
        /*1. hw encrypt*/

        ret = smx_cmd_create(psrc,pdst,1,AES_128,CTR_MODE,ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ctr failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ctr failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",pdst[i]);
        /*2. hw decrypt*/
        ret = smx_cmd_create(pdst,psrc+0x10,1,AES_128,CTR_MODE,DECRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ctr failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ctr failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",psrc[0x10+i]);

        //ret = memcmp(psrc,psrc+0x10,0x10);
        ret = strcmp((char*)psrc, (char*)(psrc+0x10));
        if(ret)
                printf("decrypt data and source data are different!\n");

        /*3. sw encrypt*/
         mbedtls_aes_init( &aes_ctx );
         mbedtls_aes_setkey_enc( &aes_ctx, key,128);
         mbedtls_aes_crypt_ctr( &aes_ctx,16,&offset,nonce_counter,stream_block, psrc, sw_dst );

         //ret = memcmp(pdst,sw_dst,16);
         ret = strcmp((char*)pdst, (char*)sw_dst);
         if(ret)
                printf("encrypt data between engine and sw are different ");

        /***************************************************************************/
	/***********************calculate aes-128-ofb********************************/
        /*1. hw encrypt*/

        ret = smx_cmd_create(psrc,pdst,1,AES_128,OFB_MODE,ENCRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ecb failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ecb failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",pdst[i]);
        /*2. hw decrypt*/
        ret = smx_cmd_create(pdst,psrc+0x10,1,AES_128,OFB_MODE,DECRYPT);
        if(ret)
                printf("smx module smx_cmd_creaete for aes-128-ecb failed! \n");

        ret = smx_status_polling();
        if(ret)
                printf("smx module smx_status_polling for aes-128-ecb failed! \n");
        for(i=0; i<16; i++)
                printf("dst = %x \n",psrc[0x10+i]);

        //ret = memcmp(psrc,psrc+0x10,0x10);
        ret = strcmp((char*)psrc, (char*)(psrc+0x10));
	if(ret)
                printf("decrypt data and source data are different!\n");

        /*3. sw encrypt*/
         mbedtls_aes_init( &aes_ctx );
         mbedtls_aes_setkey_enc( &aes_ctx, key,128);
         mbedtls_aes_crypt_ofb( &aes_ctx, 16,&offset,iv, psrc, sw_dst);

         //ret = memcmp(pdst,sw_dst,16);
         ret = strcmp((char*)pdst, (char*)sw_dst);
         if(ret)
                printf("encrypt data between engine and sw are different ");

        /***************************************************************************/
	#endif


	return 0;
}

MK_CMD(smx,smx_main,"Test crypto_acc,including AES,DES,SHA1,SHA256",
                        "smx_test \n"
                        "-test crypto smx function\n");
#endif


int smx_vfreg_read_write_test()
{
        int ret_value;
	int i;
	printf("enter into smx reg test");
        /*IRQ EN*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_EN);
        if(ret_value != 0x0)
                printf("IRQ EN read default value fail!");
	else
		printf("ok \n");
        WRITE_REG(SMX_VF0_REG_IRQ_EN, 0xff);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_EN);
        if(ret_value != 0xff)
                printf("IRQ EN write & read test fail!");
        WRITE_REG(SMX_VF0_REG_IRQ_EN, 0x0);
        /*IRQ RAW*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_RAW);
        if(ret_value != 0x0)
                printf("IRQ RAW read default value fail!");


        /*IRQ STAT*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_STAT);
        if(ret_value != 0x0)
                printf("IRQ STAT read default value fail!");


        /*IRQ CLR*/
        /*ret_value = READ_REG(SMX_VF0_REG_IRQ_CLR);
        if(ret_value != 0x0)
                printf("IRQ CLR read default value fail!");
	*/

        /*IRQ CTRL_0*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_0);
        if(ret_value != 0x001E0002)
                printf("IRQ CTRL_0 read default value fail!");

        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_0, 0x00400040);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_0);
        if(ret_value != 0x00400040)
                printf("IRQ CTRL_0 write & read test fail!");
        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_0, 0x001E0002);

        /*IRQ_CTRL_1*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_1);
        if(ret_value != 0x001E0002)
                printf("IRQ CTRL_1 read default value fail!");

        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_1, 0x001D0003);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_1);
        if(ret_value != 0x001D0003)
                printf("IRQ CTRL_1 write & read test fail!");
        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_1, 0x001E0002);

        /*WD_CTRL_0*/
        ret_value = READ_REG(SMX_VF0_WD_CTRL_0);
        if(ret_value != 0xffffffff)
                printf("IRQ WD_CTRL_0 read default fail!");

        WRITE_REG(SMX_VF0_WD_CTRL_0, 0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_WD_CTRL_0);
        if(ret_value != 0x55aa55aa)
                printf("IRQ WD_CTRL_0 read & write fail!");

        WRITE_REG(SMX_VF0_WD_CTRL_1, 0xffffffff);
        /*WD_CTRL_1*/
         ret_value = READ_REG(SMX_VF0_WD_CTRL_1);
        if(ret_value != 0xffffffff)
                printf("IRQ WD_CTRL_1 read default fail!");

        WRITE_REG(SMX_VF0_WD_CTRL_1, 0x55aa55aa);
         ret_value = READ_REG(SMX_VF0_WD_CTRL_1);
        if(ret_value != 0x55aa55aa)
                printf("IRQ WD_CTRL_1 read & write fail!");

        WRITE_REG(SMX_VF0_WD_CTRL_1, 0xffffffff);

        /*C0_IRQ_INFO_1*/
        ret_value = READ_REG(SMX_VF0_C0_IRQ_INFO_1);
        if(ret_value != 0x0)
                printf("C0_IRQ_INFO_1 read default fail!");

        /*C1_IRQ_INFO_1*/
        ret_value = READ_REG(SMX_VF0_C1_IRQ_INFO_1);
        if(ret_value != 0x0)
                printf("C1_IRQ_INFO_1 read default fail!");

        /*RING_CTRL_0*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_0);
        if(ret_value !=0)
                printf("SMX_VF0_REG_RING_CTRL_0 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_0,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_0);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_0 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_0,0x0);


        /*RING_CTRL_1*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_1);
        if(ret_value !=0)
                printf("SMX_VF0_REG_RING_CTRL_1 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_1,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_1);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_1 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_1,0x0);

        /*RING CTRL _2*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_2);
        if(ret_value !=0)
                printf("SMX_VF0_REG_RING_CTRL_2 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_2,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_2);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_2 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_2,0x0);

         /*RING CTRL _3*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_3);
        if(ret_value !=0)
                printf("SMX_VF0_REG_RING_CTRL_3 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_3,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_3);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_3 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_3,0x0);

         /*RING CTRL _4*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_4);
        if(ret_value !=0)
                printf("SMX_VF0_REG_RING_CTRL_4 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_4,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_4);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_4 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_4,0x0);

         /*RING CTRL _5*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_5);
        if(ret_value !=0)
                printf("SMX_VF0_REG_RING_CTRL_5 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_5,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_5);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_5 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_5,0x0);

         /*RING CTRL _6*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_6);
        if(ret_value !=0)
                printf("SMX_VF0_REG_RING_CTRL_6 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_6,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_6);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_6 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_6,0x0);

         /*RING CTRL _7*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_7);
        if(ret_value !=0)
                printf("SMX_VF0_REG_RING_CTRL_7 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_7,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_7);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_7 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_7,0x0);

         /*RING CTRL _8*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_8);
        if(ret_value !=0x00200020)
                printf("SMX_VF0_REG_RING_CTRL_8 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_8,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_8);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_8 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_8,0x00200020);

         /*RING CTRL _9*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_9);
        if(ret_value !=0x00200020)
                printf("SMX_VF0_REG_RING_CTRL_9 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_9,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_9);
        if(ret_value != 0x55aa55aa)
                printf("SMX_VF0_REG_RING_CTRL_9 read & write fail! ");

        WRITE_REG(SMX_VF0_REG_RING_CTRL_9,0x00200020);

        /*_C0_MAILBOX_0*/
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_0);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C0_MAILBOX_0 read default fail!");

        WRITE_REG(SMX_VF0_REG_C0_MAILBOX_0, 0xffff);
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_0);
        if(ret_value != 0xffff)
                printf("SMX_VF0_REG_C0_MAILBOX_0 read & write fail!");

        WRITE_REG(SMX_VF0_REG_C0_MAILBOX_0, 0x0);

        /*C0_MAILBOX_1*/
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_1);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C0_MAILBOX_1 read default fail!");

         /*C0_MAILBOX_2*/
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_2);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C0_MAILBOX_2 read default fail!");
        /*C0_MAILBOX_3*/
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_3);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C0_MAILBOX_3 read default fail!");
 	WRITE_REG(SMX_VF0_REG_C0_MAILBOX_3, 0xffff);
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_3);
        if(ret_value != 0xffff)
                printf("SMX_VF0_REG_C0_MAILBOX_3 read & write fail!");

        WRITE_REG(SMX_VF0_REG_C0_MAILBOX_3, 0x0);



         /*C1_MAILBOX_0*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_0);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C1_MAILBOX_0 read default fail!");

        WRITE_REG(SMX_VF0_REG_C1_MAILBOX_0, 0xffff);
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_0);
        if(ret_value != 0xffff)
                printf("SMX_VF0_REG_C1_MAILBOX_0 read & write fail!");

        WRITE_REG(SMX_VF0_REG_C1_MAILBOX_0, 0x0);

        /*C1_MAILBOX_1*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_1);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C1_MAILBOX_1 read default fail!");

        /*C1_MAILBOX_2*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_2);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C1_MAILBOX_2 read default fail!");

         /*C1_MAILBOX_3*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_3);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C1_MAILBOX_3 read default fail!");

        WRITE_REG(SMX_VF0_REG_C1_MAILBOX_3, 0xffff);
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_3);
        if(ret_value != 0xffff)
                printf("SMX_VF0_REG_C1_MAILBOX_3 read & write fail!");

        WRITE_REG(SMX_VF0_REG_C1_MAILBOX_3, 0x0);

        /*C0_MAILBOX_3*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_3);
        if(ret_value != 0)
                printf("SMX_VF0_REG_C1_MAILBOX_3 read default fail!");

        /*C0_RING_STS*/
        ret_value = READ_REG(SMX_VF0_REG_C0_RING_STS_0);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_C0_RING_STS_0 read default fail");
        /*c0_RING_STS*/
        ret_value = READ_REG(SMX_VF0_REG_C0_RING_STS_1);
        if(ret_value != 0x0a)
                printf("SMX_VF0_REG_C0_RING_STS_1 read default fail");

        /*C1_RING_STS_0*/
         ret_value = READ_REG(SMX_VF0_REG_C1_RING_STS_0);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_C1_RING_STS_0 read default fail");
        /*c1_RING_STS*/
        ret_value = READ_REG(SMX_VF0_REG_C1_RING_STS_1);
        if(ret_value != 0x0a)
                printf("SMX_VF0_REG_C1_RING_STS_1 read default fail");

        /*RING_INIT_0*/
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_RING_INIT_0 read default fail");

        WRITE_REG(SMX_VF0_REG_RING_INIT_0, 0x3);
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret_value != 0x3)
                printf("SMX_VF0_REG_RING_INIT_0 read & write fail");

        WRITE_REG(SMX_VF0_REG_RING_INIT_0, 0x0);
        #if 0
        /*RING_INIT_1*/
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_1);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_RING_INIT_1 read default fail");

        /*RING_INIT_2*/
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_2);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_RING_INIT_2 read default fail");


        WRITE_REG(SMX_VF0_REG_RING_INIT_2, 0x3);
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_2);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_RING_INIT_2 read & write fail");

        /*RING_INIT_3*/

        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_3);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_RING_INIT_3 read default fail!");

        WRITE_REG(SMX_VF0_REG_RING_INIT_3,0x3);
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_3);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_RING_INIT_3 read default fail!");
        #endif

        /*CH_PRIOR*/
        ret_value = READ_REG(SMX_VF0_REG_CH_PRIOR);
        if(ret_value != 0)
                printf("SMX_VF0_REG_CH_PRIOR read default fail");

        WRITE_REG(SMX_VF0_REG_CH_PRIOR, 0x01);
        ret_value = READ_REG(SMX_VF0_REG_CH_PRIOR);
        if(ret_value !=0x1)
                printf("SMX_VF0_REG_CH_PRIOR read & write fail");

        WRITE_REG(SMX_VF0_REG_CH_PRIOR, 0x0);

        /*LOCAL_MSI_EN*/
        ret_value = READ_REG(SMX_VF0_REG_LOCAL_MSI_EN);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_LOCAL_MSI_EN read default fail");

        WRITE_REG(SMX_VF0_REG_LOCAL_MSI_EN, 0x01);
        ret_value = READ_REG(SMX_VF0_REG_LOCAL_MSI_EN);

        if(ret_value != 0x1)
                printf("SMX_VF0_REG_LOCAL_MSI_EN read $ write fail");

        WRITE_REG(SMX_VF0_REG_LOCAL_MSI_EN, 0x0);

        /*LOCAL_MSI_STAT*/
        ret_value = READ_REG(SMX_VF0_REG_LOCAL_MSI_STAT);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_LOCAL_MSI_STAT read default fail");


        WRITE_REG(SMX_VF0_REG_LOCAL_MSI_EN,0x1);
        ret_value = READ_REG(SMX_VF0_REG_LOCAL_MSI_STAT);
        if(ret_value != 0x1)
                printf("SMX_VF0_REG_LOCAL_MSI_STAT read default fail");


        WRITE_REG(SMX_VF0_REG_LOCAL_MSI_EN,0x0);
        ret_value = READ_REG(SMX_VF0_REG_LOCAL_MSI_STAT);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_LOCAL_MSI_STAT read default fail");

        /*SMX_SPARE*/
        ret_value = READ_REG(SMX_VF0_REG_SMX_SPARE);
        if(ret_value != 0)
                printf("SMX_VF0_REG_LOCAL_MSI_STAT read default fail");
        WRITE_REG(SMX_VF0_REG_SMX_SPARE,0xffffffff);
        ret_value = READ_REG(SMX_VF0_REG_SMX_SPARE);
        if(ret_value != 0xffffffff)
                printf("SMX_VF0_REG_LOCAL_MSI_STAT read & write fail");

        WRITE_REG(SMX_VF0_REG_SMX_SPARE,0x0);
	#if 0 /*init clk have vf alloc*/
        /*VF_ALLOC*/
        ret_value = READ_REG(SMX_VF0_REG_VF_ALLOC);
	printf("ret_value = %x \n",ret_value);
        if(ret_value != 0)
                printf("SMX_VF0_REG_VF_ALLOC read default fail!");

        WRITE_REG(SMX_VF0_REG_VF_ALLOC, 0x1);
        ret_value = READ_REG(SMX_VF0_REG_VF_ALLOC);
        if(ret_value != 0x1)
                printf("SMX_VF0_REG_VF_ALLOC read & write fail!");

        /*VF_FREE*/
        ret_value = READ_REG(SMX_VF0_REG_VF_FREE);
        if(ret_value != 0x0)
                printf("SMX_VF0_REG_VF_FREE VF alloc fail");


        WRITE_REG(SMX_VF0_REG_VF_FREE,0x1);
        ret_value = READ_REG(SMX_VF0_REG_VF_FREE);
        if(ret_value != 0x01)
                printf("SMX_VF0_REG_VF_FREE VF free fail");

	#endif

        /*global ctrl*/
        /*VF_WEIGHT_0*/
        ret_value = READ_REG(SMX_VF_REG_WEIGHT_0);
        if(ret_value != 0x0)
                printf("SMX_VF_REG_WEIGHT_0 read default fail!");
        WRITE_REG(SMX_VF_REG_WEIGHT_0,0x1);
        ret_value = READ_REG(SMX_VF_REG_WEIGHT_0);
	printf("ret_value = %x \n", ret_value);
        if(ret_value != 0x01)
                printf("SMX_VF_REG_WEIGHT_0 read & wirte fail");

        /*VF_WEIGHT_1*/
        ret_value = READ_REG(SMX_VF_REG_WEIGHT_1);
        if(ret_value != 0x0)
                printf("SMX_VF_REG_WEIGHT_1 read default fail!");

        WRITE_REG(SMX_VF_REG_WEIGHT_1,0x04030201);
        ret_value = READ_REG(SMX_VF_REG_WEIGHT_1);
	printf("ret_valuie = %x \n",ret_value);
        if(ret_value != 0x04030201)
                printf("SMX_VF_REG_WEIGHT_1 read & write fail");

        WRITE_REG(SMX_VF_REG_WEIGHT_1,0x0);
        WRITE_REG(SMX_VF_REG_WEIGHT_0,0x0);

        /*DMA_CTRL mas delete this function  */
	/*
        ret_value = READ_REG(SMX_VF_REG_DMA_CTRL);
        if(ret_value !=0x0808)
                printf("SMX_VF_REG_DMA_CTRL read default fail");

        WRITE_REG(SMX_VF_REG_DMA_CTRL, 0x99);
        ret_value =  READ_REG(SMX_VF_REG_DMA_CTRL);
        if(ret_value !=0x0909)
                printf("SMX_VF_REG_DMA_CTRL read & write fail");

        WRITE_REG(SMX_VF_REG_DMA_CTRL, 0x0808);
        */                                                                                                                                                     /*GLB_OPT*/
        /*ret_value = READ_REG(SMX_VF_REG_GLB_OPT);
        if(ret_value != 0x300)
                printf("SMX_VF_REG_GLB_OPT read default fail");
        WRITE_REG(SMX_VF_REG_GLB_OPT,0x0);
        ret_value = READ_REG(SMX_VF_REG_GLB_OPT);
        if(ret_value !=0)
                printf("SMX_VF_REG_GLB_OPT read & write fail");
        WRITE_REG(SMX_VF_REG_GLB_OPT,0x300);
        */
        /*VF_MSI_CFG*/
        /*PC_CTRL_0*/
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_0);
        if(ret_value !=0)
                printf("SMX_VF_REG_PC_CTRL_0 read default fail");

        WRITE_REG(SMX_VF_REG_PC_CTRL_0, 0x01);
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_0);
	printf("pc_ctrl_0 =%x \n ", ret_value);
        if(ret_value !=0x01)
                printf("SMX_VF_REG_PC_CTRL_0 read & write fail ");

        WRITE_REG(SMX_VF_REG_PC_CTRL_0, 0x0);
        /*PC_CTRL_1*/
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_1);
	printf("pc_ctrl_1 =%x \n ", ret_value);
        if(ret_value !=0x80000000)
                printf("SMX_VF_REG_PC_CTRL_1 read default fail");

        WRITE_REG(SMX_VF_REG_PC_CTRL_1, 0x100);
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_1);
	printf("pc_ctrl_1 =%x \n ", ret_value);
        if(ret_value !=0x100)
                printf("SMX_VF_REG_PC_CTRL_1 read & write fail ");

        WRITE_REG(SMX_VF_REG_MSI_ADDR_1, 0x80000000);

        /*PC_CTRL_2*/
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_2);
        if(ret_value != 0x0)
                printf("SMX_VF_REG_PC_CTRL_2 read default fail");

        WRITE_REG(SMX_VF_REG_PC_CTRL_2,0xffff);
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_2);
	printf("pc_ctrl_2 =%x \n ", ret_value);
        if(ret_value != 0xffff)
                printf("SMX_VF_REG_PC_CTRL_2 read & write fail");
        WRITE_REG(SMX_VF_REG_PC_CTRL_2, 0x0);

        /*PC_INFO_0 ~ PC_INFO_12*/
	for(i=0; i<13; i++){
        	ret_value = readl((uintptr_t)( SMX_VF_REG_PC_INFO_0 + 4*i));
        	if(ret_value != 0x0)
                	printf("SMX_VF_REG_PC_INFO read default fail");
	}
	/*PC_INFO_15 ~ PC_INFO_28*/
	for(i=0; i<14; i++) {

        	ret_value = readl((uintptr_t)(SMX_VF_REG_PC_INFO_15 + 4*i));
        	if(ret_value != 0x0)
                	printf("SMX_VF_REG_PC_INFO read default fail");

	}

	/*VF_MSI_CFG*/
        /*MSI_ADDR_0*/
        ret_value = READ_REG(SMX_VF_REG_MSI_ADDR_0);
        if(ret_value !=0)
                printf("SMX_VF_REG_MSI_ADDR_0 read default fail");

        WRITE_REG(SMX_VF_REG_MSI_ADDR_0, 0xffffffff);
        ret_value = READ_REG(SMX_VF_REG_MSI_ADDR_0);
	printf("MSI_ADDR =%x \n", ret_value);
        if(ret_value !=0xffffffff)
                printf("SMX_VF_REG_MSI_ADDR_0 read & write fail ");

        WRITE_REG(SMX_VF_REG_MSI_ADDR_0, 0x0);
        /*MSI_ADDR_1*/
        ret_value = READ_REG(SMX_VF_REG_MSI_ADDR_1);
	printf("msi_addr_1 ret_value = %x \n", ret_value);
        if(ret_value !=0)
                printf("SMX_VF_REG_MSI_ADDR_1 read default fail");

        WRITE_REG(SMX_VF_REG_MSI_ADDR_1, 0xffffffff);
        ret_value = READ_REG(SMX_VF_REG_MSI_ADDR_1);
        if(ret_value !=0xffffffff)
                printf("SMX_VF_REG_MSI_ADDR_1 read & write fail ");

        WRITE_REG(SMX_VF_REG_MSI_ADDR_1, 0x0);

        /*MSI_INT_ID_BASE*/
        ret_value = READ_REG(SMX_VF_REG_MSI_INT_ID_BASE);
        if(ret_value != 0x0)
                printf("SMX_VF_REG_MSI_INT_ID_BASE read default fail");

        WRITE_REG(SMX_VF_REG_MSI_INT_ID_BASE,0xffff);
        ret_value = READ_REG(SMX_VF_REG_MSI_INT_ID_BASE);
        if(ret_value != 0xffff)
                printf("SMX_VF_REG_MSI_INT_ID_BASE read & write fail");
        WRITE_REG(SMX_VF_REG_MSI_INT_ID_BASE, 0x0);

        /*MSI_RID_GLB*/
        ret_value = READ_REG(SMX_VF_REG_MSI_RID_GLB);
        if(ret_value != 0x0)
                printf("SMX_VF_REG_MSI_RID_GLB read default fail");


        WRITE_REG(SMX_VF_REG_MSI_RID_GLB,0xffff);
        ret_value = READ_REG(SMX_VF_REG_MSI_RID_GLB);
        if(ret_value != 0xffff)
                printf("SMX_VF_REG_MSI_RID_GLB read & write fail");

        /*MSI_RID_LOCAL*/
        ret_value = READ_REG(SMX_VF_REG_MSI_RID_LOCAL);
        if(ret_value != 0x0)
                printf("SMX_VF_REG_MSI_RID_LOCAL read default fail");

        WRITE_REG(SMX_VF_REG_MSI_RID_LOCAL,0x7ff);

        ret_value = READ_REG(SMX_VF_REG_MSI_RID_LOCAL);
        if(ret_value != 0x7ff)
                printf("SMX_VF_REG_MSI_RID_LOCAL read & writefail");

        WRITE_REG(SMX_VF_REG_MSI_RID_LOCAL,0x0);

        /*VF_MSI_CTRL*/
        /*GLB_MSI_OVERRIDE*/
        ret_value =  READ_REG(SMX_VF_REG_GLB_MSI_OVERRIDE);
        if(ret_value !=0)
                printf("SMX_VF_REG_GLB_MSI_OVERRIDE read default fail");

        WRITE_REG(SMX_VF_REG_GLB_MSI_OVERRIDE, 0x0f);
        ret_value = READ_REG(SMX_VF_REG_GLB_MSI_OVERRIDE);
        if(ret_value != 0x0f)
                printf("SMX_VF_REG_GLB_MSI_OVERRIDE read & write fail ");

        WRITE_REG(SMX_VF_REG_GLB_MSI_OVERRIDE, 0x0);

        /*GLB_MSI_EN*/
        ret_value = READ_REG(SMX_VF_REG_GLB_MSI_EN);
        if(ret_value != 0x0)
                printf("SMX_VF_REG_GLB_MSI_EN read default fail");

        WRITE_REG(SMX_VF_REG_GLB_MSI_EN,0x0f);
        ret_value = READ_REG(SMX_VF_REG_GLB_MSI_EN);
        if(ret_value != 0x0f)
                printf("SMX_VF_REG_GLB_MSI_EN read & write fail");

   	 WRITE_REG(SMX_VF_REG_GLB_MSI_EN,0x0);
        /*GLB_MSI_STAT*/
        ret_value = READ_REG(SMX_VF_REG_GLB_MSI_STAT);
        if(ret_value != 0x0)
                printf("SMX_VF_REG_GLB_MSI_STAT read default fail");

        WRITE_REG(SMX_VF_REG_GLB_MSI_EN,0x0f);

        ret_value = READ_REG(SMX_VF_REG_GLB_MSI_STAT);
        if(ret_value != 0x0f)
                printf("SMX_VF_REG_GLB_MSI_STAT read&write fail");

        WRITE_REG(SMX_VF_REG_GLB_MSI_EN,0x0);

        printf("register read & wirte case pass!");


        return 0;
}



