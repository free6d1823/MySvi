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
#include <target/irqc.h>
//#define C_A76
#define CM4
//#define IPS_INTR
#define IPS_POLLING
int ips_init_clk(void)
{
	int ret_value;
	/*initialzie IPS-CORE clock*/
	WRITE_REG(IPS_TOP_CTRL_CORE_CLK_CTRL, 0x1);
	ret_value = READ_REG(IPS_TOP_CTRL_CORE_CLK_CTRL);
	if(ret_value != 1){
		printf("enable clock failed \n");
		return -1;
	}
	/*reset ips*/
	WRITE_REG(IPS_TOP_CTRL_CORE_RST_CTRL, 0x1);
	while(READ_REG(IPS_TOP_CTRL_CORE_RST_CTRL)!=0)
			;
	//printf("IPS-Core running case pass!");
	/*initialzie clock enalbe for IPS-SRAM clock and IPS-FUNCTION*/
	WRITE_REG(IPS_VF_REG_GLB_OPT, 0x0);
	ret_value = READ_REG(IPS_VF_REG_GLB_OPT);
	if(ret_value != 0){
		printf("ips ram clock enable failed!");
		return -1;
	}
	return 0;
}
int ips_module_reset()
{
	int ret_value;
	int count;
	#if 0
	/* vf_free */
	ret_value = READ_REG(IPS_VF0_REG_VF_FREE);
	if(ret_value = 1)
	{
		/*VF ALLOC*/
		printf("vf free! \n");
		WRITE_REG(IPS_VF0_REG_VF_ALLOC, 1);
		ret_value = READ_REG(IPS_VF0_REG_VF_ALLOC);
		if(ret_value == 1)
			printf("security attribute consistent!\n");
		else
			printf("security attribute not consistent!\n");
	}
	#endif
	ret_value = READ_REG(IPS_VF0_REG_RING_INIT_1);
	while((ret_value != 3)&&(count != 100)) {
		 ret_value = READ_REG(IPS_VF0_REG_RING_INIT_1);
			count++;
		}
	if(count == 100)
		return -1;
	else{
 		WRITE_REG(IPS_VF0_REG_RING_INIT_2,1);
		WRITE_REG(IPS_VF0_REG_RING_INIT_3,1);
		return 0;
	}
}
/**********************interrupt*****************************************/
#ifdef IPS_INTR
void disable_vf0_irq()
{
	int ret_value;
	WRITE_REG(IPS_VF0_REG_IRQ_EN,0x0);
        ret_value = READ_REG(IPS_VF0_REG_IRQ_EN);
        if(ret_value != 0x0)
                printf("disable irq channel 0 failed \n");
}
void set_intr_threshold_value()
{
	int ret_value;
	WRITE_REG(IPS_VF0_REG_IRQ_CTRL_0,0x00010001);
        ret_value = READ_REG(IPS_VF0_REG_IRQ_CTRL_0);
        if(ret_value != 0x00010001)
                printf("set irq triger threshold failed \n");

}
void enable_vf0_irq()
{
	int ret_value;
	WRITE_REG(IPS_VF0_REG_IRQ_EN,0x80001451);
        ret_value = READ_REG(IPS_VF0_REG_IRQ_EN);
        if(ret_value != 0x80001451)
                printf("enable irq channel 0 failed \n");
}
void ips_irq_process()
{
	int begin;
	int end;
	int num;
	unsigned int ret_value;
	struct status_ring *ring;
	ret_value = READ_REG(IPS_VF0_REG_IRQ_RAW);
	while(!ret_value)
		ret_value = READ_REG(IPS_VF0_REG_IRQ_RAW);
	if(ret_value&0x1){
		printf("chanel 0 status error! \n");
		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 1);
		return;
	}

	if(ret_value&0x4){
		printf("chanel 0 command interrupt! \n");
		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 0x4);

	}
	if(ret_value&0x100){
		printf("chanel 0 status watch dog! \n");
		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 0x100);
		return;
	}

	if(ret_value&0x1000){
		printf("write chanel 0 status error! \n");
		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 0x1000);
		return;
	}
	if(ret_value&0x10){
		printf("status dispose! \n");
		begin = READ_REG(IPS_VF0_REG_C0_MAILBOX_2);
		end = READ_REG(IPS_VF0_REG_C0_MAILBOX_3);
		num = begin%MAX_CMD - end%MAX_CMD;
		if(num < 0)
			num = MAX_CMD - end%MAX_CMD;
		if(!num){
			printf("status ring is empty");
			return;
		}
		/*printf("begin = %d \n", begin);
		printf("end = %d \n", end);
		printf("num = %d \n", num);
		*/
		ring = (struct status_ring*)(READ_REG(IPS_VF0_REG_RING_CTRL_4) + end);
		//printf("ring ret_code = %x \n", ring->ret_code);
		//printf("ring sw_id value =%x \n", ring->sw_id);
		/*set the status ring consumer*/
		WRITE_REG(IPS_VF0_REG_C0_MAILBOX_3, begin);

		WRITE_REG(IPS_VF0_REG_IRQ_CLR, 0x10);

	}


}
void ips_irq_handle(irq_t irq, void *ctx)
{
	irq_t ips_irq = SE_IPS_IRQ;
	//irqc_disable_irq(ips_irq);
	printf("enter into ips irq handle! \n");
	ips_irq_process();
	//enable_vf0_irq();
}
void ips_irq_init()
{
	//printf("ips irq initialize!\n");
	irq_t ips_irq = SE_IPS_IRQ;
	disable_vf0_irq();
	set_intr_threshold_value();
	irqc_configure_irq(ips_irq, 32, IRQ_LEVEL_TRIGGERED);
	irq_register_vector(ips_irq, ips_irq_handle, NULL);
	irqc_enable_irq(ips_irq);
	enable_vf0_irq();
	//printf("ips irq end initialzie \n");
}
int get_cmd_status()
{

}
#endif
 /*****************************************************************************/
int ips_dev_init()
{
	int ret_value = 0;
	unsigned int cmd_base;
	unsigned int status_base;
	cmd_base = IPS_CMD_BASE;
	//printf("cmd_base = %x \n", cmd_base);
	status_base = IPS_STATUS_BASE;
	/*set cmd and status base addr*/
	WRITE_REG(IPS_VF0_REG_RING_CTRL_0,cmd_base);   //low
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_0);
	if(ret_value != cmd_base){
		printf("set cmd base failed \n");
		return -1;
	}
	WRITE_REG(IPS_VF0_REG_RING_CTRL_1,0);   //high
	WRITE_REG(IPS_VF0_REG_RING_CTRL_4,status_base); //low
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_4);
	if(ret_value != status_base) {
		printf("set status base failed \n");
		return -1;
	}
	WRITE_REG(IPS_VF0_REG_RING_CTRL_5,0); //high
	/*set cmd ring descriptior count and status ring descriptior count*/
	WRITE_REG(IPS_VF0_REG_RING_CTRL_8,0x00400040);
	ret_value = READ_REG(IPS_VF0_REG_RING_CTRL_8);
	if(ret_value != 0x00400040){
		printf("set descriptior count failed \n");
		return -1;
	}
	#ifdef IPS_POLLING
	/*set irq triger threshold value*/
	WRITE_REG(IPS_VF0_REG_IRQ_CTRL_0,0x00010001);
	ret_value = READ_REG(IPS_VF0_REG_IRQ_CTRL_0);
	if(ret_value != 0x00010001){
		printf("set irq triger threshold failed \n");
		return -1;
	}
	/*enable irq channel 0 */
	WRITE_REG(IPS_VF0_REG_IRQ_EN,0x80001451);
	ret_value = READ_REG(IPS_VF0_REG_IRQ_EN);
	if(ret_value != 0x80001451){
		printf("enable irq channel 0 failed \n");
		return -1;
	}
	#endif
	#ifdef IPS_INTR
	ips_irq_init();
	#endif
	/*enable channel 0*/
	WRITE_REG(IPS_VF0_REG_RING_INIT_0,1);
	ret_value = READ_REG(IPS_VF0_REG_RING_INIT_0);
	if(ret_value !=1){
		printf("channel 0 enable failed \n");
		return -1;
	}

	return 0;

}
int ips_key_iv_set()
{
	int i;
	int ret_value;
	unsigned int key[8];
	unsigned int hashkey[0x20]={0x0};
	unsigned int iv[4];
	for(i=0; i<8; i++)
		key[i] = 0xffffffff; //0x44332211;
	for(i=0; i<4; i++)
		iv[i] = 0x11111111;
	for(i=0; i<0x20; i++)
		hashkey[i] = 0x0; //0x0b0b0b0b; //0x20202020; //0x0b0b0b0b;//0xffffffff;
	#ifdef C_A76
	WRITE_REG(IPS_VF0_KEY0, key[0]);
	WRITE_REG(IPS_VF0_KEY1, key[1]);
	WRITE_REG(IPS_VF0_KEY2, key[2]);
	WRITE_REG(IPS_VF0_KEY3, key[3]);
	WRITE_REG(IPS_VF0_KEY4, key[4]);
	WRITE_REG(IPS_VF0_KEY5, key[5]);
	WRITE_REG(IPS_VF0_KEY6, key[6]);
	WRITE_REG(IPS_VF0_KEY7, key[7]);

	WRITE_REG(IPS_VF0_IV0, iv[0]);
	WRITE_REG(IPS_VF0_IV1, iv[1]);
	WRITE_REG(IPS_VF0_IV2, iv[2]);
	WRITE_REG(IPS_VF0_IV3, iv[3]);
	WRITE_REG(IPS_VF0_HASHKEY0, hashkey[0]);
        WRITE_REG(IPS_VF0_HASHKEY1, hashkey[1]);
        WRITE_REG(IPS_VF0_HASHKEY2, hashkey[2]);
        WRITE_REG(IPS_VF0_HASHKEY3, hashkey[3]);
        WRITE_REG(IPS_VF0_HASHKEY4, hashkey[4]);
        WRITE_REG(IPS_VF0_HASHKEY5, hashkey[5]);
        WRITE_REG(IPS_VF0_HASHKEY6, hashkey[6]);
        WRITE_REG(IPS_VF0_HASHKEY7, hashkey[7]);
	WRITE_REG(IPS_VF0_HASHKEY8, hashkey[8]);
        WRITE_REG(IPS_VF0_HASHKEY9, hashkey[9]);
        WRITE_REG(IPS_VF0_HASHKEY10, hashkey[10]);
        WRITE_REG(IPS_VF0_HASHKEY11, hashkey[11]);
        WRITE_REG(IPS_VF0_HASHKEY12, hashkey[12]);
        WRITE_REG(IPS_VF0_HASHKEY13, hashkey[13]);
        WRITE_REG(IPS_VF0_HASHKEY14, hashkey[14]);
        WRITE_REG(IPS_VF0_HASHKEY15, hashkey[15]);
	WRITE_REG(IPS_VF0_HASHKEY16, hashkey[16]);
        WRITE_REG(IPS_VF0_HASHKEY17, hashkey[17]);
        WRITE_REG(IPS_VF0_HASHKEY18, hashkey[18]);
        WRITE_REG(IPS_VF0_HASHKEY19, hashkey[19]);
        WRITE_REG(IPS_VF0_HASHKEY20, hashkey[20]);
        WRITE_REG(IPS_VF0_HASHKEY21, hashkey[21]);
        WRITE_REG(IPS_VF0_HASHKEY22, hashkey[22]);
        WRITE_REG(IPS_VF0_HASHKEY23, hashkey[23]);
	WRITE_REG(IPS_VF0_HASHKEY24, hashkey[24]);
        WRITE_REG(IPS_VF0_HASHKEY25, hashkey[25]);
        WRITE_REG(IPS_VF0_HASHKEY26, hashkey[26]);
        WRITE_REG(IPS_VF0_HASHKEY27, hashkey[27]);
        WRITE_REG(IPS_VF0_HASHKEY28, hashkey[28]);
        WRITE_REG(IPS_VF0_HASHKEY29, hashkey[29]);
        WRITE_REG(IPS_VF0_HASHKEY30, hashkey[30]);
        WRITE_REG(IPS_VF0_HASHKEY31, hashkey[31]);
	#endif
	#ifdef CM4
	for(i=0; i<8; i++)
		WRITE_REG((IPS_VF0_KEY + 4*i), key[i]);
	for(i=0; i<4; i++)
	{
		WRITE_REG((IPS_VF0_KEY+0x20 + 4*i),iv[i]);
	}
	for(i=0; i<0x20; i++)
	{

		WRITE_REG((IPS_VF0_KEY+0x1000 + 4*i),hashkey[i]);
	}
	for(i=0;i<8;i++)
	{
		ret_value = READ_REG(IPS_VF0_KEY+4*i);
		if(ret_value != 0xffffffff) //0x44332211)
		{
			printf("key set failed \n");
			return -1;
		}
	}

        for(i=0; i<4; i++)
	{
		ret_value = READ_REG(IPS_VF0_KEY+0x20+4*i);
		if(ret_value != 0x11111111){
			printf("iv set failed \n");
			return -1;
		}
	}
	for(i=0; i<0x20; i++)
	{
		ret_value = READ_REG(IPS_VF0_KEY+0x1000+4*i);
		if(ret_value != 0){
			printf("hashkey set failed \n");
			return -1;
		}
	}
	#endif
	return 0;

}
int ips_data_setup_sha(unsigned char *src, unsigned char *dst,struct ips_command* pcmd,int hash_alg,int hash_mode, int ende_flag, int proc_len)
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
        pcmd->proc_len = proc_len;//strlen(src);
        pcmd->icv_offset = proc_len; //0
        pcmd->iv_offset = 0;
        pcmd->iv_enable = 0;
        /*control*/
        pcmd->hm_key_size = 0x20;
        pcmd->key_exp = 0;
        pcmd->icv_append = 1;
        pcmd->icv_enc = 0;
        pcmd->icv_pt = 1;
        pcmd->aad_copy = 0;
        pcmd->encrypt = ende_flag;
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = 0;
        pcmd->hash_mode = hash_mode;//0; //raw mode
        pcmd->cipher_mode = 0; //NULL ? ECB
        pcmd->hash_alg = hash_alg;//3;
        pcmd->cipher_alg = 0;
        pcmd->ioc = 0;
        /*aux_info*/
        pcmd->icv_len = 0;//ctx->sha.outlen;
        pcmd->cbc_cs_sel = 0;
        pcmd->bk_sz_cfb = 0;
	pcmd->sw_id = 0;
        return 0;
}
int ips_data_setup_aes(unsigned char *src, unsigned char *dst,struct ips_command* pcmd, int cipher_alg,int cipher_mode, int ende_flag, int proc_len)
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
        pcmd->proc_len = proc_len;
	if(cipher_mode == GCM_MODE)
        	pcmd->icv_offset = 16;
	else
		pcmd->icv_offset = 0;
        pcmd->iv_offset = 0;
        pcmd->iv_enable = 0;
        pcmd->hm_key_size = 0;
	if((cipher_mode == ECB_MODE)||(cipher_mode == CBC_MODE))
        		pcmd->key_exp = 1;
	else
			pcmd->key_exp = 0;
        pcmd->icv_append = 0;
        pcmd->icv_pt = 0;
        pcmd->icv_enc = 0;
	pcmd->aad_copy = 0;
        pcmd->encrypt = ende_flag; //encrypt
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = 0;
        pcmd->hash_mode = 0; //raw mode
        pcmd->cipher_mode = cipher_mode; //NULL ? ECB
        pcmd->hash_alg = 0;
        pcmd->cipher_alg = cipher_alg;
        pcmd->ioc = 0;
        pcmd->icv_len = 0;
        pcmd->cbc_cs_sel = 0;
        pcmd->bk_sz_cfb = 0;
	pcmd->sw_id = 0;
        return 0;
}
int ips_cmd_create(unsigned char *src, unsigned char *dst, int flag, int alg_flag, int alg_mode, int ende_flag, int proc_len)
{
	int i;
	int ret_value;
	unsigned int producer_idx;
	unsigned int consumer_idx;
	unsigned int cmd_base;
	struct ips_command* pcmd = (struct ips_command*)IPS_CMD_RING; //heap_alloc(0x40);
	producer_idx = READ_REG(IPS_VF0_REG_C0_MAILBOX_0);
	//printf("producer_idx = %x \n", producer_idx);
	consumer_idx = READ_REG(IPS_VF0_REG_C0_MAILBOX_1);
        //printf("consumer_idx = %x \n", consumer_idx);
	/*fifo status full*/
        if (producer_idx % MAX_CMD + 1 == consumer_idx % MAX_CMD){
        	printf("command ring full! \n");
	        return -1;
	}
	if(flag == 0){ //sha
		ret_value = ips_data_setup_sha(src,dst,pcmd,alg_flag,alg_mode,ende_flag,proc_len);
	}
	if(flag == 1){//aes

		ret_value = ips_data_setup_aes(src,dst,pcmd,alg_flag,alg_mode,ende_flag,proc_len);
	}
	if(ret_value) {
                printf("ips module data setup  case failed! \n");
		return -1;
	}
	cmd_base = READ_REG(IPS_VF0_REG_RING_CTRL_0);
	//printf("cmd_base = %x \n", cmd_base);
	memcpy((void*)(uintptr_t)(cmd_base + 64*producer_idx), (void*)pcmd, 64);
	//for (i = 0; i < 64; i++)
              // printf("cmdring #_%#x  value= %#x\n", i, *(unsigned char*)(uintptr_t)(cmd_base + i));

	producer_idx++;

	producer_idx = producer_idx % MAX_CMD;

	WRITE_REG(IPS_VF0_REG_C0_MAILBOX_0, producer_idx);
	producer_idx = READ_REG(IPS_VF0_REG_C0_MAILBOX_0);
	//printf("producer_idx = %x \n", producer_idx);
	//heap_free(pcmd);
	return 0;

}
int ips_status_polling()
{
	int i;
	int ret_value;
	int status_base;
	struct status_ring* ring;
	status_base = READ_REG(IPS_VF0_REG_RING_CTRL_4);
	ring = (struct status_ring*)(uintptr_t)status_base;

	for(i=0; i<10; i++)
	{
		ret_value = READ_REG(IPS_VF0_REG_IRQ_RAW);
		//printf("irq_raw = %x \n",ret_value);
		ret_value = READ_REG(IPS_VF0_REG_C0_RING_STS_0);
		//printf("ring_sts = %x \n",ret_value);
	}
	//printf("stsring ret_code  value= %#x\n", ring->ret_code);
        //printf("stsring sw_id value= %#x\n", ring->sw_id);

	return 0;
}
