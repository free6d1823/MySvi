#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <target/utils.h>
#include "crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include <target/irqc.h>

//#define DEBUG_PRINT
//#define SMX_INTR
#define SMX_POLLING
int smx_init_clk(void)
{
        int ret_value;

        /*initialzie clock enalbe for SMX-SRAM clock and SMX-FUNCTION*/
	//printf("init clk begin, SMX_VF_REG_GLB_OPT = %x \n",SMX_VF_REG_GLB_OPT);
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
                WRITE_REG(SMX_VF0_REG_VF_ALLOC, 1);
                ret_value = READ_REG(SMX_VF0_REG_VF_ALLOC);
                if(ret_value != 1)
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
	/*disable channel 0*/
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret_value){
        	WRITE_REG(SMX_VF0_REG_RING_INIT_0,0);
                //printf("channel 0  disable channel \n");

 		WRITE_REG(SMX_VF0_REG_RING_INIT_2,1);
		WRITE_REG(SMX_VF0_REG_RING_INIT_3,1);
	}
	}	
		return 0;
}


int smx_key_iv_set(unsigned char *smx_key, unsigned char *smx_iv)
{
	int i;
	int ret_value;
	//unsigned char skey[] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};
	//unsigned char siv[] = {0xeb, 0xee, 0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7};
	unsigned int *key;
	unsigned int *iv;

	key = (unsigned int *)smx_key;
	iv = (unsigned int *)smx_iv;
	for(i=0; i<4; i++)
	{
		writel(key[i], (uintptr_t)(SMX_VF0_KEY + 4*i));
		//WRITE_REG(SMX_VF0_KEY + 4*i, key[i]);
	}

	for(i=0; i<4; i++)
	{
		writel(iv[i],(uintptr_t)(SMX_VF0_KEY+16+4*i));
		//WRITE_REG(SMX_VF0_KEY+16+4*i, iv[i]);
	}
	#if 0
	ret_value = READ_REG(SMX_VF0_KEY);
	//printf("ret_value = %x \n", ret_value);
	if(ret_value != 0x67452301){             //0xffffffff
		printf("key set failed \n");
		return -1;
	}
	ret_value = READ_REG(SMX_VF0_KEY + 16);
	if(ret_value != 0x68c5eeeb){
		printf("iv set failed \n");
		return -1;
	}
	#endif

	return 0;
}
/*********************for irq*************************************/
#ifdef SMX_INTR
void disable_smx_irq()
{
        int ret_value;
        WRITE_REG(SMX_VF0_REG_IRQ_EN,0x0);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_EN);
        if(ret_value != 0x0)
                printf("disable irq channel 0 failed \n");
}
void set_smx_intr_threshold_value()
{
        int ret_value;
        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_0,0x00010001);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_0);
        if(ret_value != 0x00010001)
                printf("set irq triger threshold failed \n");

}
void enable_smx_irq()
{
        int ret_value;
        WRITE_REG(SMX_VF0_REG_IRQ_EN,0x80001451);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_EN);
        if(ret_value != 0x80001451)
                printf("enable irq channel 0 failed \n");
}
void smx_irq_process()
{
        int begin;
        int end;
        int num;
        unsigned int ret_value;
        struct status_ring *ring;
        ret_value = READ_REG(SMX_VF0_REG_IRQ_RAW);
        while(!ret_value)
                ret_value = READ_REG(SMX_VF0_REG_IRQ_RAW);
        if(ret_value&0x1){
                printf("chanel 0 status error! \n");
                WRITE_REG(SMX_VF0_REG_IRQ_CLR, 1);
                return;
        }

        if(ret_value&0x4){
                printf("chanel 0 command interrupt! \n");
                WRITE_REG(SMX_VF0_REG_IRQ_CLR, 0x4);

        }
        if(ret_value&0x100){
                printf("chanel 0 status watch dog! \n");
                WRITE_REG(SMX_VF0_REG_IRQ_CLR, 0x100);
                return;
        }

        if(ret_value&0x1000){
                printf("write chanel 0 status error! \n");
                WRITE_REG(SMX_VF0_REG_IRQ_CLR, 0x1000);
                return;
        }
        if(ret_value&0x10){
                printf("intr status dispose! \n");
                begin = READ_REG(SMX_VF0_REG_C0_MAILBOX_2);
                end = READ_REG(SMX_VF0_REG_C0_MAILBOX_3);
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
                ring = (struct status_ring*)(READ_REG(SMX_VF0_REG_RING_CTRL_4) + end);
                //printf("ring ret_code = %x \n", ring->ret_code);
                //printf("ring sw_id value =%x \n", ring->sw_id);
                /*set the status ring consumer*/
                WRITE_REG(SMX_VF0_REG_C0_MAILBOX_3, begin);

                WRITE_REG(SMX_VF0_REG_IRQ_CLR, 0x10);

        }


}
void smx_irq_handle(irq_t irq, void *ctx)
{
        irq_t smx_irq = SE_SMX_IRQ;
        //irqc_disable_irq(smx_irq);
        printf("enter into smx irq handle! \n");
        smx_irq_process();
        //enable_vf0_irq();
}
void smx_irq_init()
{
        //printf("ips irq initialize!\n");
        irq_t smx_irq = SE_SMX_IRQ;
        disable_smx_irq();
        set_smx_intr_threshold_value();
        irqc_configure_irq(smx_irq, 32, IRQ_LEVEL_TRIGGERED);
        irq_register_vector(smx_irq, smx_irq_handle, NULL);
        irqc_enable_irq(smx_irq);
        enable_smx_irq();
        //printf("ips irq end initialzie \n");
}
int get_smx_cmd_status()
{

	return 0;
}

#endif


/**************watch dog timer******************************/
int set_smx_threshold(int ch_no)
{
        if(!ch_no)
                WRITE_REG(SMX_VF0_WD_CTRL_0, 0x100);
        if(ch_no)
                WRITE_REG(SMX_VF0_WD_CTRL_1, 0x100000);

        return 0;
}




int smx_dev_init()
{
        int ret_value = 0;
        unsigned int cmd_base;
        unsigned int status_base;

        cmd_base = SMX_CMD_BASE;
        status_base = SMX_STATUS_BASE;
	//memset((void*)cmd_base, 0, 0x1000);
	//memset((void*)status_base,0,0x1000);
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
        #ifdef SMX_POLLING
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
        #endif
        #ifdef SMX_INTR
        smx_irq_init();
        #endif

        /*enable channel 0*/
        WRITE_REG(SMX_VF0_REG_RING_INIT_0,1);
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_0);
        if(ret_value !=1){
                printf("channel 0 enable failed \n");
                return -1;
        }

	//set_smx_threshold(0);

        return 0;

}



/************************for irq*********************************/
int smx_data_setup_sm3(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int hash_mode, int ende_flag, int proc_len, int ddt_mode)
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
        pcmd->proc_len = proc_len;//3strlen(src);
	printf("proc_len = %x \n", proc_len);
        pcmd->icv_offset = proc_len; //03
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
        pcmd->ddt_mode = ddt_mode;
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

int smx_data_setup_sm4(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int cipher_mode, int ende_flag, int proc_len,int ddt_mode)
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
 	if(cipher_mode == GCM_MODE)
                pcmd->pre_aad_len = 20;
        else
                pcmd->pre_aad_len = 0;

        //pcmd->pre_aad_len = 0;
        pcmd->post_aad_len = 0;
        pcmd->proc_len = proc_len;
	//printf("proc_len = %d \n", proc_len);
	if(cipher_mode == GCM_MODE)
                pcmd->icv_offset = 80;
        else
                pcmd->icv_offset = 0;

        //pcmd->icv_offset = 0;
        pcmd->iv_offset = 0;
        pcmd->iv_enable = 0;
	pcmd->MSG_BEGIN = 1;
	pcmd->MSG_END = 1;

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

        //pcmd->aad_copy = 0;
        pcmd->encrypt = ende_flag; //encrypt ctx->sm4.ende_flag
	//printf("ende_flag = %d \n", ende_flag);
        pcmd->ctx_idx = 0;
        pcmd->ddt_mode = ddt_mode;
        pcmd->key_port = 1;
        pcmd->mode = mode;//opt;//
	//printf("cipher_mode = %d \n", cipher_mode);
        pcmd->ioc = 0;  //not IOC

        pcmd->icv_len = 0;
        pcmd->cbc_cs_sel = cbc_submode;
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

	switch(flag)
	{
		case 0:
			ret_value = smx_data_setup_sm3(src,dst,pcmd,alg_mode,ende_flag,proc_len,DIRECT_MODE);	
		break;
		case 1:
			ret_value = smx_data_setup_sm4(src,dst,pcmd,alg_mode,ende_flag,proc_len,DIRECT_MODE);	
		break;

		case 2:
			ret_value = smx_data_setup_sm3(src,dst,pcmd,alg_mode,ende_flag,proc_len,DDT_MODE);
		break;

		case 3:
			ret_value = smx_data_setup_sm4(src,dst,pcmd,alg_mode,ende_flag,proc_len,DDT_MODE);
		break;

		default:
		break;

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

	/*for debug*/
	ret_value = READ_REG(SMX_VF0_WD_CTRL_0);
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
	int consumer_idx;
	int ring_buffer[256];
	struct status_ring* ring;// = (struct status_ring*)SMX_STATUS_BASE;

	consumer_idx = READ_REG(SMX_VF0_REG_C0_MAILBOX_3);
	status_base = READ_REG(SMX_VF0_REG_RING_CTRL_4);

	memcpy((void*)ring_buffer,(void*)(status_base + 8*consumer_idx),8);
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
	consumer_idx++;
	consumer_idx = consumer_idx % MAX_CMD;
	WRITE_REG(SMX_VF0_REG_C0_MAILBOX_3,consumer_idx);	

	return 0;

}




int smx_vfreg_read_write_test(int vf_no)
{
        int ret_value;
	int i;
	int addr_offset;
	addr_offset = vf_no*0x20000;
        /*IRQ EN*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_EN+addr_offset);
        if(ret_value != 0x0){
                printf("IRQ EN read default value fail!");
		return -1;
	}
        WRITE_REG(SMX_VF0_REG_IRQ_EN+addr_offset, 0xff);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_EN+addr_offset);
        if(ret_value != 0xff) {
                printf("IRQ EN write & read test fail!");
		return -1;
	}
        WRITE_REG(SMX_VF0_REG_IRQ_EN+addr_offset, 0x0);
        /*IRQ RAW*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_RAW+addr_offset);
        if(ret_value != 0x0){
                printf("IRQ RAW read default value fail!");
		return -1;

	}


        /*IRQ STAT*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_STAT+addr_offset);
        if(ret_value != 0x0){
                printf("IRQ STAT read default value fail!");
		return -1;
	}


        /*IRQ CTRL_0*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_0+addr_offset);
        if(ret_value != 0x001E0002){
                printf("IRQ CTRL_0 read default value fail!");
		return -1;

	}

        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_0+addr_offset, 0x00400040);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_0+addr_offset);
        if(ret_value != 0x00400040){
                printf("IRQ CTRL_0 write & read test fail!");
		return -1;

	}
        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_0+addr_offset, 0x001E0002);

        /*IRQ_CTRL_1*/
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_1+addr_offset);
        if(ret_value != 0x001E0002){
                printf("IRQ CTRL_1 read default value fail!");
		return -1;

	}

        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_1+addr_offset, 0x001D0003);
        ret_value = READ_REG(SMX_VF0_REG_IRQ_CTRL_1+addr_offset);
        if(ret_value != 0x001D0003){
                printf("IRQ CTRL_1 write & read test fail!");
		return -1;
	}
        WRITE_REG(SMX_VF0_REG_IRQ_CTRL_1+addr_offset, 0x001E0002);

        /*WD_CTRL_0*/
        ret_value = READ_REG(SMX_VF0_WD_CTRL_0+addr_offset);
        if(ret_value != 0xffffffff){
                printf("IRQ WD_CTRL_0 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_WD_CTRL_0+addr_offset, 0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_WD_CTRL_0+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IRQ WD_CTRL_0 read & write fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_WD_CTRL_1+addr_offset, 0xffffffff);
        /*WD_CTRL_1*/
         ret_value = READ_REG(SMX_VF0_WD_CTRL_1+addr_offset);
        if(ret_value != 0xffffffff){
                printf("IRQ WD_CTRL_1 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_WD_CTRL_1+addr_offset, 0x55aa55aa);
         ret_value = READ_REG(SMX_VF0_WD_CTRL_1+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("IRQ WD_CTRL_1 read & write fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_WD_CTRL_1+addr_offset, 0xffffffff);

        /*C0_IRQ_INFO_1*/
        ret_value = READ_REG(SMX_VF0_C0_IRQ_INFO_1+addr_offset);
        if(ret_value != 0x0){
                printf("C0_IRQ_INFO_1 read default fail!");
		return -1;
	}

        /*C1_IRQ_INFO_1*/
        ret_value = READ_REG(SMX_VF0_C1_IRQ_INFO_1+addr_offset);
        if(ret_value != 0x0){
                printf("C1_IRQ_INFO_1 read default fail!");
		return -1;
	}

        /*RING_CTRL_0*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_0+addr_offset);
        if(ret_value !=0){
                printf("SMX_VF0_REG_RING_CTRL_0 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_0+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_0+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_0 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_0+addr_offset,0x0);


        /*RING_CTRL_1*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_1+addr_offset);
        if(ret_value !=0){
                printf("SMX_VF0_REG_RING_CTRL_1 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_1+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_1+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_1 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_1+addr_offset,0x0);

        /*RING CTRL _2*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_2+addr_offset);
        if(ret_value !=0){
                printf("SMX_VF0_REG_RING_CTRL_2 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_2+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_2+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_2 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_2+addr_offset,0x0);

         /*RING CTRL _3*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_3+addr_offset);
        if(ret_value !=0){
                printf("SMX_VF0_REG_RING_CTRL_3 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_3+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_3+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_3 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_3+addr_offset,0x0);

         /*RING CTRL _4*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_4+addr_offset);
        if(ret_value !=0){
                printf("SMX_VF0_REG_RING_CTRL_4 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_4+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_4+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_4 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_4+addr_offset,0x0);

         /*RING CTRL _5*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_5+addr_offset);
        if(ret_value !=0){
                printf("SMX_VF0_REG_RING_CTRL_5 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_5+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_5+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_5 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_5+addr_offset,0x0);

         /*RING CTRL _6*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_6+addr_offset);
        if(ret_value !=0){
                printf("SMX_VF0_REG_RING_CTRL_6 read default fail!");
		return -1;

	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_6+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_6+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_6 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_6+addr_offset,0x0);

         /*RING CTRL _7*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_7+addr_offset);
        if(ret_value !=0){
                printf("SMX_VF0_REG_RING_CTRL_7 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_7+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_7+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_7 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_7+addr_offset,0x0);

         /*RING CTRL _8*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_8+addr_offset);
        if(ret_value !=0x00200020){
                printf("SMX_VF0_REG_RING_CTRL_8 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_8+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_8+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_8 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_8+addr_offset,0x00200020);

         /*RING CTRL _9*/
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_9+addr_offset);
        if(ret_value !=0x00200020){
                printf("SMX_VF0_REG_RING_CTRL_9 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_9+addr_offset,0x55aa55aa);
        ret_value = READ_REG(SMX_VF0_REG_RING_CTRL_9+addr_offset);
        if(ret_value != 0x55aa55aa){
                printf("SMX_VF0_REG_RING_CTRL_9 read & write fail! ");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_CTRL_9+addr_offset,0x00200020);

        /*_C0_MAILBOX_0*/
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_0+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C0_MAILBOX_0 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_C0_MAILBOX_0+addr_offset, 0xffff);
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_0+addr_offset);
        if(ret_value != 0xffff){
                printf("SMX_VF0_REG_C0_MAILBOX_0 read & write fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_C0_MAILBOX_0+addr_offset, 0x0);

        /*C0_MAILBOX_1*/
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_1+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C0_MAILBOX_1 read default fail!");
		return -1;
	}

         /*C0_MAILBOX_2*/
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_2+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C0_MAILBOX_2 read default fail!");
		return -1;
	}
        /*C0_MAILBOX_3*/
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_3+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C0_MAILBOX_3 read default fail!");
		return -1;
	}
 	WRITE_REG(SMX_VF0_REG_C0_MAILBOX_3+addr_offset, 0xffff);
        ret_value = READ_REG(SMX_VF0_REG_C0_MAILBOX_3+addr_offset);
        if(ret_value != 0xffff){
                printf("SMX_VF0_REG_C0_MAILBOX_3 read & write fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_C0_MAILBOX_3+addr_offset, 0x0);

         /*C1_MAILBOX_0*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_0+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C1_MAILBOX_0 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_C1_MAILBOX_0+addr_offset, 0xffff);
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_0+addr_offset);
        if(ret_value != 0xffff){
                printf("SMX_VF0_REG_C1_MAILBOX_0 read & write fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_C1_MAILBOX_0+addr_offset, 0x0);

        /*C1_MAILBOX_1*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_1+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C1_MAILBOX_1 read default fail!");
		return -1;
	}

        /*C1_MAILBOX_2*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_2+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C1_MAILBOX_2 read default fail!");
		return -1;
	}

         /*C1_MAILBOX_3*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_3+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C1_MAILBOX_3 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_C1_MAILBOX_3+addr_offset, 0xffff);
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_3+addr_offset);
        if(ret_value != 0xffff){
                printf("SMX_VF0_REG_C1_MAILBOX_3 read & write fail!");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_C1_MAILBOX_3+addr_offset, 0x0);

        /*C0_MAILBOX_3*/
        ret_value = READ_REG(SMX_VF0_REG_C1_MAILBOX_3+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_C1_MAILBOX_3 read default fail!");
		return -1;
	}

        /*C0_RING_STS*/
        ret_value = READ_REG(SMX_VF0_REG_C0_RING_STS_0+addr_offset);
        if(ret_value != 0x0){
                printf("SMX_VF0_REG_C0_RING_STS_0 read default fail");
		return -1;
	}
        /*c0_RING_STS*/
        ret_value = READ_REG(SMX_VF0_REG_C0_RING_STS_1+addr_offset);
        if(ret_value != 0x0a){
                printf("SMX_VF0_REG_C0_RING_STS_1 read default fail");
		return -1;

	}

        /*C1_RING_STS_0*/
         ret_value = READ_REG(SMX_VF0_REG_C1_RING_STS_0+addr_offset);
        if(ret_value != 0x0){
                printf("SMX_VF0_REG_C1_RING_STS_0 read default fail");
		return -1;
	}
        /*c1_RING_STS*/
        ret_value = READ_REG(SMX_VF0_REG_C1_RING_STS_1+addr_offset);
        if(ret_value != 0x0a){
                printf("SMX_VF0_REG_C1_RING_STS_1 read default fail");
		return -1;
	}

        /*RING_INIT_0*/
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_0+addr_offset);
        if(ret_value != 0x0){
                printf("SMX_VF0_REG_RING_INIT_0 read default fail");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_INIT_0 + addr_offset, 0x3);
        ret_value = READ_REG(SMX_VF0_REG_RING_INIT_0+addr_offset);
        if(ret_value != 0x3){
                printf("SMX_VF0_REG_RING_INIT_0 read & write fail");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_RING_INIT_0 + addr_offset, 0x0);
        WRITE_REG(SMX_VF0_REG_RING_INIT_0+addr_offset, 0x0);

        /*CH_PRIOR*/
        ret_value = READ_REG(SMX_VF0_REG_CH_PRIOR+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_CH_PRIOR read default fail");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_CH_PRIOR+addr_offset, 0x01);
        ret_value = READ_REG(SMX_VF0_REG_CH_PRIOR+addr_offset);
        if(ret_value !=0x1){
                printf("SMX_VF0_REG_CH_PRIOR read & write fail");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_CH_PRIOR+addr_offset, 0x0);


        /*SMX_SPARE*/
        ret_value = READ_REG(SMX_VF0_REG_SMX_SPARE+addr_offset);
        if(ret_value != 0){
                printf("SMX_VF0_REG_LOCAL_MSI_STAT read default fail");
		return -1;
	}
        WRITE_REG(SMX_VF0_REG_SMX_SPARE+addr_offset,0xffffffff);
        ret_value = READ_REG(SMX_VF0_REG_SMX_SPARE+addr_offset);
        if(ret_value != 0xffffffff){
                printf("SMX_VF0_REG_LOCAL_MSI_STAT read & write fail");
		return -1;
	}

        WRITE_REG(SMX_VF0_REG_SMX_SPARE+addr_offset,0x0);

	if(vf_no == 0)
	{
        /*global ctrl*/
        /*VF_WEIGHT_0*/
        ret_value = READ_REG(SMX_VF_REG_WEIGHT_0);
        if(ret_value != 0x0){
                printf("SMX_VF_REG_WEIGHT_0 read default fail!");
		return -1;
	}
        WRITE_REG(SMX_VF_REG_WEIGHT_0,0x1);
        ret_value = READ_REG(SMX_VF_REG_WEIGHT_0);
        if(ret_value != 0x01){
                printf("SMX_VF_REG_WEIGHT_0 read & wirte fail");
		return -1;
	}

        /*VF_WEIGHT_1*/
        ret_value = READ_REG(SMX_VF_REG_WEIGHT_1);
        if(ret_value != 0x0){
                printf("SMX_VF_REG_WEIGHT_1 read default fail!");
		return -1;
	}

        WRITE_REG(SMX_VF_REG_WEIGHT_1,0x04030201);
        ret_value = READ_REG(SMX_VF_REG_WEIGHT_1);
        if(ret_value != 0x04030201){
                printf("SMX_VF_REG_WEIGHT_1 read & write fail");
		return -1;
	}

        WRITE_REG(SMX_VF_REG_WEIGHT_1,0x0);
        WRITE_REG(SMX_VF_REG_WEIGHT_0,0x0);

        /*VF_MSI_CFG*/

        /*PC_INFO_0 ~ PC_INFO_12*/
	for(i=0; i<13; i++){
        	ret_value = readl((uintptr_t)( SMX_VF_REG_PC_INFO_0 + 4*i));
        	if(ret_value != 0x0){
                	printf("1 group  SMX_VF_REG_PC_INFO read default fail i =%d \n", i);
			return -1;
		}
	}
	/*PC_INFO_15 ~ PC_INFO_28*/
	for(i=0; i<14; i++) {

        	ret_value = readl((uintptr_t)(SMX_VF_REG_PC_INFO_15 + 4*i));
        	if(ret_value != 0x0){
                	printf("2 group SMX_VF_REG_PC_INFO read default fail i =%d \n", i);
			return -1;
		}

	}
        /*PC_CTRL_0*/
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_0);
        if(ret_value !=0){
                printf("SMX_VF_REG_PC_CTRL_0 read default fail");
		return -1;
	}

        WRITE_REG(SMX_VF_REG_PC_CTRL_0, 0x01);
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_0);
        if((ret_value & 0x01) != 0x01){
                printf("SMX_VF_REG_PC_CTRL_0 read & write fail ");
		return -1;
	}

        /*PC_CTRL_1*/
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_1);
        if(ret_value !=0x80000000){
                printf("SMX_VF_REG_PC_CTRL_1 read default fail");
		return -1;
	}

        WRITE_REG(SMX_VF_REG_PC_CTRL_1, 0x100);
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_1);
        if(ret_value !=0x100){
                printf("SMX_VF_REG_PC_CTRL_1 read & write fail ");
		return -1;
	}

        WRITE_REG(SMX_VF_REG_MSI_ADDR_1, 0x80000000);

        WRITE_REG(SMX_VF_REG_PC_CTRL_0, 0x100);
        /*PC_CTRL_2*/
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_2);
        if(ret_value != 0x0){
                printf("SMX_VF_REG_PC_CTRL_2 read default fail");
		return -1;
	}

        WRITE_REG(SMX_VF_REG_PC_CTRL_2,0x01);
        ret_value = READ_REG(SMX_VF_REG_PC_CTRL_2);
	//printf("pc_ctrl_2 =%x \n ", ret_value);
        if(ret_value != 0x01){
                printf("SMX_VF_REG_PC_CTRL_2 read & write fail");
		return -1;
	}
        WRITE_REG(SMX_VF_REG_PC_CTRL_2, 0x0);
	}/*if(ch_no == 0)*/

        printf("register read & wirte case pass! \n");


        return 0;
}



