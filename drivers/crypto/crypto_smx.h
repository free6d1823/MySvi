/*****************************************************/
/*CopyRight: Siengine				     */
/*Authore: yyq					     */
/*change history			             */
/*****************************************************/
#include <target/irq.h>
#include "target/crypto_control.h"

#ifndef CRYPTO_SMX
#define CRYPTO_SMX

#ifdef M4_SMX
#define SMP_SMX_BASE	(0x40100000)
#endif

#ifdef A76_SMX
#define SMP_SMX_BASE	(0xe3580000)					//(0xb4870000)
#endif
// Base address
#define SMX_VF0_REG							(SMP_SMX_BASE + (0x000000))
#define	SMX_VF0_KEY							(SMP_SMX_BASE + (0x010000))

#define SMP_VCS
//#define SMP_Z1
#ifdef SMP_VCS
#define SMX_GLOBAL							(SMP_SMX_BASE + (0x080000))
#define SMX_MSI_CFG							(SMP_SMX_BASE + (0x090000))
#define	SMX_MSI_CTRL							(SMP_SMX_BASE + (0x0a0000))
#endif

//#define SMX_XPU                                                       (SMP_SMX_BASE + (0x000000))
//#define SMX_VF0_REG                                                   (SMP_SMX_BASE + (0x130000))
//#define SMX_VF0_KEY                                                   (SMP_SMX_BASE + (0x140000))
#ifdef SMP_Z1
#define SMX_GLOBAL                                                      (SMP_SMX_BASE + (0x1b0000))
#define SMX_MSI_CFG                                                     (SMP_SMX_BASE + (0x1c0000))
#define SMX_MSI_CTRL                                                    (SMP_SMX_BASE + (0x1d0000))
#endif
#define SMX_TOP_CTRL                                                    (SMP_SMX_BASE + (0x230000))



//Register address for VF0
#define	SMX_VF0_REG_IRQ_EN						(SMX_VF0_REG + 0x0)
#define SMX_VF0_REG_IRQ_RAW						(SMX_VF0_REG + 0x4)
#define	SMX_VF0_REG_IRQ_STAT						(SMX_VF0_REG + 0x8)
#define SMX_VF0_REG_IRQ_CLR						(SMX_VF0_REG + 0xc)
#define	SMX_VF0_REG_IRQ_CTRL_0						(SMX_VF0_REG + 0x10)
#define SMX_VF0_REG_IRQ_CTRL_1						(SMX_VF0_REG + 0x14)
#define	SMX_VF0_WD_CTRL_0						(SMX_VF0_REG + 0x18)
#define SMX_VF0_WD_CTRL_1						(SMX_VF0_REG + 0x1c)
#define	SMX_VF0_C0_IRQ_INFO_1						(SMX_VF0_REG + 0x24)
#define SMX_VF0_C1_IRQ_INFO_1						(SMX_VF0_REG + 0x2c)
#define	SMX_VF0_REG_RING_CTRL_0						(SMX_VF0_REG + 0x34)
#define SMX_VF0_REG_RING_CTRL_1						(SMX_VF0_REG + 0x38)
#define	SMX_VF0_REG_RING_CTRL_2						(SMX_VF0_REG + 0x3c)
#define SMX_VF0_REG_RING_CTRL_3						(SMX_VF0_REG + 0x40)
#define	SMX_VF0_REG_RING_CTRL_4						(SMX_VF0_REG + 0x44)
#define	SMX_VF0_REG_RING_CTRL_5						(SMX_VF0_REG + 0x48)
#define SMX_VF0_REG_RING_CTRL_6						(SMX_VF0_REG + 0x4c)
#define	SMX_VF0_REG_RING_CTRL_7						(SMX_VF0_REG + 0x50)
#define SMX_VF0_REG_RING_CTRL_8						(SMX_VF0_REG + 0x54)
#define	SMX_VF0_REG_RING_CTRL_9						(SMX_VF0_REG + 0x58)
#define SMX_VF0_REG_C0_MAILBOX_0					(SMX_VF0_REG + 0x5c)
#define SMX_VF0_REG_C0_MAILBOX_1					(SMX_VF0_REG + 0X60)
#define SMX_VF0_REG_C0_MAILBOX_2					(SMX_VF0_REG + 0x64)
#define SMX_VF0_REG_C0_MAILBOX_3					(SMX_VF0_REG + 0x68)
#define SMX_VF0_REG_C1_MAILBOX_0					(SMX_VF0_REG + 0x6c)
#define SMX_VF0_REG_C1_MAILBOX_1					(SMX_VF0_REG + 0X70)
#define SMX_VF0_REG_C1_MAILBOX_2					(SMX_VF0_REG + 0x74)
#define SMX_VF0_REG_C1_MAILBOX_3					(SMX_VF0_REG + 0x78)
#define SMX_VF0_REG_C0_RING_STS_0					(SMX_VF0_REG + 0x7c)
#define SMX_VF0_REG_C0_RING_STS_1					(SMX_VF0_REG + 0x80)
#define SMX_VF0_REG_C1_RING_STS_0					(SMX_VF0_REG + 0x84)
#define SMX_VF0_REG_C1_RING_STS_1					(SMX_VF0_REG + 0x88)
#define SMX_VF0_REG_RING_INIT_0						(SMX_VF0_REG + 0x8c)
#define SMX_VF0_REG_RING_INIT_1						(SMX_VF0_REG + 0x90)
#define SMX_VF0_REG_RING_INIT_2						(SMX_VF0_REG + 0x94)
#define SMX_VF0_REG_RING_INIT_3						(SMX_VF0_REG + 0x98)
#define SMX_VF0_REG_CH_PRIOR						(SMX_VF0_REG + 0xa4)
#define SMX_VF0_REG_LOCAL_MSI_EN					(SMX_VF0_REG + 0xa8)
#define SMX_VF0_REG_LOCAL_MSI_STAT					(SMX_VF0_REG + 0xac)
#define SMX_VF0_REG_SMX_SPARE						(SMX_VF0_REG + 0xb0)
#define SMX_VF0_REG_VF_ALLOC						(SMX_VF0_REG + 0x200)
#define SMX_VF0_REG_VF_FREE						(SMX_VF0_REG + 0x204)

//Register address for Global
#define SMX_VF_REG_WEIGHT_0						(SMX_GLOBAL + 0x0)
#define SMX_VF_REG_WEIGHT_1						(SMX_GLOBAL + 0x4)
#define SMX_VF_REG_DMA_CTRL						(SMX_GLOBAL + 0xc)
#define SMX_VF_REG_GLB_OPT						(SMX_GLOBAL + 0x10)
#define SMX_VF_REG_PC_CTRL_0						(SMX_GLOBAL + 0x14)
#define SMX_VF_REG_PC_CTRL_1						(SMX_GLOBAL + 0x18)
#define SMX_VF_REG_PC_CTRL_2						(SMX_GLOBAL + 0x1c)
#define SMX_VF_REG_PC_INFO_0						(SMX_GLOBAL + 0x20)
#define SMX_VF_REG_PC_INFO_1 						(SMX_GLOBAL + 0x24)
#define SMX_VF_REG_PC_INFO_2 						(SMX_GLOBAL + 0x28)
#define SMX_VF_REG_PC_INFO_3 						(SMX_GLOBAL + 0x2c)
#define SMX_VF_REG_PC_INFO_4 						(SMX_GLOBAL + 0x30)
#define SMX_VF_REG_PC_INFO_5 						(SMX_GLOBAL + 0x34)
#define SMX_VF_REG_PC_INFO_6 						(SMX_GLOBAL + 0x38)
#define SMX_VF_REG_PC_INFO_7 						(SMX_GLOBAL + 0x3c)
#define SMX_VF_REG_PC_INFO_8 						(SMX_GLOBAL + 0x40)
#define SMX_VF_REG_PC_INFO_9 						(SMX_GLOBAL + 0x44)
#define SMX_VF_REG_PC_INFO_10 						(SMX_GLOBAL + 0x48)
#define SMX_VF_REG_PC_INFO_11 						(SMX_GLOBAL + 0x4c)
#define SMX_VF_REG_PC_INFO_12 						(SMX_GLOBAL + 0x50)
#define SMX_VF_REG_PC_INFO_13 						(SMX_GLOBAL + 0x54)
#define SMX_VF_REG_PC_INFO_14 						(SMX_GLOBAL + 0x58)
#define SMX_VF_REG_PC_INFO_15 						(SMX_GLOBAL + 0x5c)
#define SMX_VF_REG_PC_INFO_16 						(SMX_GLOBAL + 0x60)
#define SMX_VF_REG_PC_INFO_17 						(SMX_GLOBAL + 0x64)
#define SMX_VF_REG_PC_INFO_18 						(SMX_GLOBAL + 0x68)
#define SMX_VF_REG_PC_INFO_19 						(SMX_GLOBAL + 0x6c)
#define SMX_VF_REG_PC_INFO_20                                           (SMX_GLOBAL + 0x70)
#define SMX_VF_REG_PC_INFO_21                                           (SMX_GLOBAL + 0x74)
#define SMX_VF_REG_PC_INFO_22                                           (SMX_GLOBAL + 0x78)
#define SMX_VF_REG_PC_INFO_23                                           (SMX_GLOBAL + 0x7c)
#define SMX_VF_REG_PC_INFO_24                                           (SMX_GLOBAL + 0x80)
#define SMX_VF_REG_PC_INFO_25                                           (SMX_GLOBAL + 0x84)
#define SMX_VF_REG_PC_INFO_26                                           (SMX_GLOBAL + 0x88)
#define SMX_VF_REG_PC_INFO_27                                           (SMX_GLOBAL + 0x8c)
#define SMX_VF_REG_PC_INFO_28                                           (SMX_GLOBAL + 0x90)




//Register address for Top
#define SMX_TOP_CTRL_CORE_CLK_CTRL                                      (SMX_TOP_CTRL + 0x0)
#define SMX_TOP_CTRL_CORE_RST_CTRL                                      (SMX_TOP_CTRL + 0x4)



//Register address fro MSI_CFG
#define SMX_VF_REG_MSI_ADDR_0						(SMX_MSI_CFG + 0x0)
#define SMX_VF_REG_MSI_ADDR_1						(SMX_MSI_CFG + 0x4)
#define SMX_VF_REG_MSI_INT_ID_BASE					(SMX_MSI_CFG + 0x8)
#define SMX_VF_REG_MSI_RID_GLB						(SMX_MSI_CFG + 0xc)
#define SMX_VF_REG_MSI_RID_LOCAL					(SMX_MSI_CFG + 0x10)


//Register address for MSI_CTRL
#define SMX_VF_REG_GLB_MSI_OVERRIDE					(SMX_MSI_CTRL + 0x0)
#define SMX_VF_REG_GLB_MSI_EN						(SMX_MSI_CTRL + 0x4)
#define SMX_VF_REG_GLB_MSI_STAT						(SMX_MSI_CTRL + 0x8)

#define SMX_CMD_BASE							(0x50000)
#define SMX_STATUS_BASE							(0x53000)
#define SMX_SRC_BASE							(0x55000)
#define SMX_DST_BASE							(0x58000)
#define SMX_DDT_SRC							(0x59000)
#define SMX_DDT_DST							(0x5a000)
#define SMX_CMD_RING                                                    (0x5b000)
#define MBEDTLS_BUF                                                     (0x5e000)


#define MAX_CMD								0x40

#define PB0_ED1								4
#define PB0_ED0								3
#define PB1_ED0								2
#define PB1_ED1								1
#define ENCRYPT								1
#define DECRYPT								0

#define AES_256								3

#define HASH_RAW_MODE							1
#define ECB_MODE							2
#define CBC_MODE							0x40
#define CBC_CS1_MODE							0x41
#define CBC_CS2_MODE							0x42
#define CBC_CS3_MODE							0x43
#define CTR_MODE							6
#define OFB_MODE							8
#define CFB_MODE							10
#define GCM_MODE							12


#define SM3_FLAG							0
#define SM4_FLAG							1
#define SM3_DDT_FLAG							2
#define SM4_DDT_FLAG							3
#define DDT_MODE                                                        1
#define DIRECT_MODE                                                     0
#define IV_OFFSET							16

#define WRITE_REG(addr, value) (*(volatile unsigned int *)(addr) = value)
#define READ_REG(addr) (*(volatile unsigned int *)(addr))


struct smx_command {
        unsigned int src_pkt_addr_l;
        unsigned int src_pkt_addr_h;

        unsigned int dst_pkt_addr_l;
        unsigned int dst_pkt_addr_h;

        unsigned int dst_pkt_off : 16;
        unsigned int src_pkt_off : 16;

        unsigned int pre_aad_len;
        unsigned int post_aad_len;
        unsigned int proc_len;
        unsigned int icv_offset;
        unsigned int iv_offset : 31;
        unsigned int iv_enable : 1;

        /*control  */
        unsigned int reserved : 8;
        unsigned int MSG_END : 1;
        unsigned int MSG_BEGIN : 1;
        unsigned int key_exp : 1;
        unsigned int icv_append : 1;
        unsigned int icv_enc : 1;
        unsigned int icv_pt : 1;
        unsigned int aad_copy : 1;
        unsigned int encrypt : 1;
        unsigned int ctx_idx : 3;
        unsigned int ddt_mode : 1;
        unsigned int key_port : 1;
        unsigned int reserved6 : 6;
        unsigned int mode : 4;
        unsigned int ioc : 1;

        /* aux_info  */
        unsigned int icv_len : 6;
        unsigned int cbc_cs_sel : 2;
        unsigned int bk_sz_cfb : 7;
        unsigned int reserved5 : 1;
        unsigned int sw_id : 16;
        unsigned int reserved1;
        unsigned int reserved2;
        unsigned int reserved3;
        unsigned int reserved4;

};


struct status_ring {
        unsigned int res : 8;
        unsigned int ret_code : 6;
        unsigned int unum : 2;
        unsigned int sw_id : 16;

        unsigned int reserved;

};



int smx_main();
extern int smx_init_clk(void);
extern int smx_module_reset();
extern int smx_dev_init();
extern int smx_key_iv_set();
extern int smx_data_setup_sm3(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int hash_mode, int ende_flag, int proc_len,int ddt_mode);
extern int smx_data_setup_sm4(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int cipher_mode, int ende_flag, int proc_len,int ddt_mode);
extern int smx_cmd_create(unsigned char *src, unsigned char *dst, int flag, int alg_mode, int ende_flag, int proc_len);
extern int sm4_function_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int sm4_mode,  int proc_len);
extern int sm3_function_test(unsigned char *psrc, unsigned char *pdst, int alg_flag, int ende_flag, int proc_len);
extern int smx_status_polling();
extern void disable_smx_irq();
extern int str_cmp(unsigned char *str1, unsigned  char *str2, int len);
extern int smx_data_setup_partial_sm4(unsigned char *src, unsigned char *dst,struct smx_command* pcmd,int cipher_mode, int ende_flag, int proc_len,int src_offset, int dst_offset, int pre_aad_len, int post_aad_len, int icv_offset, int iv_en, int ioc, int p_begin, int p_end);
int smx_cmd_partial_create(unsigned char *src, unsigned char *dst, int flag, int alg_mode, int ende_flag, int proc_len,int src_offset,int dst_offset, int pre_aad_len, int post_aad_len,int icv_offset, int iv_en,int ioc, int p_begin, int p_end );



int se_smx_sm3();
int se_smx_sm4();
int se_smx_sm3_intr();
int se_smx_sm4_intr();
int se_smx_sm3_ddt();
int se_smx_sm4_ddt();
int se_smx_sm3_multi_ddt();
int se_smx_sm4_multi_ddt();
int se_smx_sm4_cts();
int se_smx_sm3_partial();
int se_smx_sm4_partial();
int se_smx_sm4_keyport();
//static int se_smx_sm3(int argc, char *argv[]);
//static int se_smx_sm4(int argc, char *argv[]);
//static int se_ips_general(int argc, char *argv[]);
extern int smx_vfreg_read_write_test();




#endif

