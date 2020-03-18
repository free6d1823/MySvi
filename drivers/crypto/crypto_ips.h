/*****************************************************/
/*CopyRight: Siengine				     */
/*Authore: yyq					     */
/*change history			             */
/*****************************************************/
#include <target/irq.h>
#include "target/crypto_control.h"
#ifndef CRYPTO_IPS
#define CRYPTO_IPS
#ifdef M4_IPS
#define SMP_IPS_BASE	(0x40110000)
#endif
#ifdef A76_IPS
#define SMP_IPS_BASE	(0xb4890000)
#endif
// Base address
#define	IPS_XPU								(SMP_IPS_BASE + (0x000000))
#define IPS_VF0_REG							(SMP_IPS_BASE + (0x130000))
#define	IPS_VF0_KEY							(SMP_IPS_BASE + (0x140000))
#define IPS_GLOBAL							(SMP_IPS_BASE + (0x1b0000))
#define IPS_MSI_CFG							(SMP_IPS_BASE + (0x1c0000))
#define	IPS_MSI_CTRL							(SMP_IPS_BASE + (0x1d0000))
#define	IPS_TOP_CTRL							(SMP_IPS_BASE + (0x230000))
#define IPS_NS_IRQ							(SMP_IPS_BASE + (0x250000))
#define IPS_SEC_IRQ							(SMP_IPS_BASE + (0x260000))
#define	IPS_MSA_IRQ							(SMP_IPS_BASE + (0x270000))
#define IPS_DBG_CTRL							(SMP_IPS_BASE + (0x280000))
#define IPS_ID								(SMP_IPS_BASE + (0x320000))
#define IPS_SMMU							(SMP_IPS_BASE + (0x800000))
//Register address for VF0
#define	IPS_VF0_REG_IRQ_EN						(IPS_VF0_REG + 0x0)
#define IPS_VF0_REG_IRQ_RAW						(IPS_VF0_REG + 0x4)
#define	IPS_VF0_REG_IRQ_STAT						(IPS_VF0_REG + 0x8)
#define IPS_VF0_REG_IRQ_CLR						(IPS_VF0_REG + 0xc)
#define	IPS_VF0_REG_IRQ_CTRL_0						(IPS_VF0_REG + 0x10)
#define IPS_VF0_REG_IRQ_CTRL_1						(IPS_VF0_REG + 0x14)
#define	IPS_VF0_WD_CTRL_0						(IPS_VF0_REG + 0x18)
#define IPS_VF0_WD_CTRL_1						(IPS_VF0_REG + 0x1c)
#define	IPS_VF0_C0_IRQ_INFO_1						(IPS_VF0_REG + 0x24)
#define IPS_VF0_C1_IRQ_INFO_1						(IPS_VF0_REG + 0x2c)
#define	IPS_VF0_REG_RING_CTRL_0						(IPS_VF0_REG + 0x34)
#define IPS_VF0_REG_RING_CTRL_1						(IPS_VF0_REG + 0x38)
#define	IPS_VF0_REG_RING_CTRL_2						(IPS_VF0_REG + 0x3c)
#define IPS_VF0_REG_RING_CTRL_3						(IPS_VF0_REG + 0x40)
#define	IPS_VF0_REG_RING_CTRL_4						(IPS_VF0_REG + 0x44)
#define	IPS_VF0_REG_RING_CTRL_5						(IPS_VF0_REG + 0x48)
#define IPS_VF0_REG_RING_CTRL_6						(IPS_VF0_REG + 0x4c)
#define	IPS_VF0_REG_RING_CTRL_7						(IPS_VF0_REG + 0x50)
#define IPS_VF0_REG_RING_CTRL_8						(IPS_VF0_REG + 0x54)
#define	IPS_VF0_REG_RING_CTRL_9						(IPS_VF0_REG + 0x58)
#define IPS_VF0_REG_C0_MAILBOX_0					(IPS_VF0_REG + 0x5c)
#define IPS_VF0_REG_C0_MAILBOX_1					(IPS_VF0_REG + 0X60)
#define IPS_VF0_REG_C0_MAILBOX_2					(IPS_VF0_REG + 0x64)
#define IPS_VF0_REG_C0_MAILBOX_3					(IPS_VF0_REG + 0x68)
#define IPS_VF0_REG_C1_MAILBOX_0					(IPS_VF0_REG + 0x6c)
#define IPS_VF0_REG_C1_MAILBOX_1					(IPS_VF0_REG + 0X70)
#define IPS_VF0_REG_C1_MAILBOX_2					(IPS_VF0_REG + 0x74)
#define IPS_VF0_REG_C1_MAILBOX_3					(IPS_VF0_REG + 0x78)
#define IPS_VF0_REG_C0_RING_STS_0					(IPS_VF0_REG + 0x7c)
#define IPS_VF0_REG_C0_RING_STS_1					(IPS_VF0_REG + 0x80)
#define IPS_VF0_REG_C1_RING_STS_0					(IPS_VF0_REG + 0x84)
#define IPS_VF0_REG_C1_RING_STS_1					(IPS_VF0_REG + 0x88)
#define IPS_VF0_REG_RING_INIT_0						(IPS_VF0_REG + 0x8c)
#define IPS_VF0_REG_RING_INIT_1						(IPS_VF0_REG + 0x90)
#define IPS_VF0_REG_RING_INIT_2						(IPS_VF0_REG + 0x94)
#define IPS_VF0_REG_RING_INIT_3						(IPS_VF0_REG + 0x98)
#define IPS_VF0_REG_CH_PRIOR						(IPS_VF0_REG + 0xa4)
#define IPS_VF0_REG_LOCAL_MSI_EN					(IPS_VF0_REG + 0xa8)
#define IPS_VF0_REG_LOCAL_MSI_STAT					(IPS_VF0_REG + 0xac)
#define IPS_VF0_REG_VF_ALLOC						(IPS_VF0_REG + 0x200)
#define IPS_VF0_REG_VF_FREE						(IPS_VF0_REG + 0x204)
//Register address for Global
#define IPS_VF_REG_WEIGHT_0						(IPS_GLOBAL + 0x0)
#define IPS_VF_REG_WEIGHT_1						(IPS_GLOBAL + 0x4)
#define IPS_VF_REG_DMA_CTRL						(IPS_GLOBAL + 0xc)
#define IPS_VF_REG_GLB_OPT						(IPS_GLOBAL + 0x10)
//Register address for Debug
#define IPS_DBG_CTRL_DEBUG_BUS_SEL					(IPS_DBG_CTRL + 0x0)
#define IPS_DBG_CTRL_DEBUG_RST						(IPS_DBG_CTRL + 0x4)
//Register address for Top
#define IPS_TOP_CTRL_CORE_CLK_CTRL					(IPS_TOP_CTRL + 0x0)
#define IPS_TOP_CTRL_CORE_RST_CTRL					(IPS_TOP_CTRL + 0x4)
//Register address fro MSI_CFG
#define IPS_VF_REG_MSI_ADDR_0						(IPS_MSI_CFG + 0x0)
#define IPS_VF_REG_MSI_ADDR_1						(IPS_MSI_CFG + 0x4)
#define IPS_VF_REG_MSI_INT_ID_BASE					(IPS_MSI_CFG + 0x8)
#define IPS_VF_REG_MSI_RID_GLB						(IPS_MSI_CFG + 0xc)
#define IPS_VF_REG_MSI_RID_LOCAL					(IPS_MSI_CFG + 0x10)
//Register address for MSI_CTRL
#define IPS_VF_REG_GLB_MSI_OVERRIDE					(IPS_MSI_CTRL + 0x0)
#define IPS_VF_REG_GLB_MSI_EN						(IPS_MSI_CTRL + 0x4)
#define IPS_VF_REG_STAT							(IPS_MSI_CTRL + 0x8)
#if 0
#define IPS_CMD_BASE							(0x40000)
#define IPS_STATUS_BASE							(0x41000)
#define IPS_SRC_BASE							(0x50000)
#define IPS_DST_BASE							(0x60000)
#endif
#define IPS_CMD_BASE							(0x70000)
#define IPS_STATUS_BASE							(0x73000)
#define IPS_SRC_BASE							(0x75000)
#define IPS_DST_BASE							(0x78000)
#define IPS_CMD_RING							(0x7b000)
#define MBEDTLS_BUF							(0x7e000)
#define IPS_VF0_KEY0							(IPS_VF0_KEY + 0X0)
#define IPS_VF0_KEY1							(IPS_VF0_KEY + 0X4)
#define IPS_VF0_KEY2							(IPS_VF0_KEY + 0X8)
#define IPS_VF0_KEY3							(IPS_VF0_KEY + 0XC)
#define IPS_VF0_KEY4							(IPS_VF0_KEY + 0X10)
#define IPS_VF0_KEY5							(IPS_VF0_KEY + 0X14)
#define IPS_VF0_KEY6							(IPS_VF0_KEY + 0X18)
#define IPS_VF0_KEY7							(IPS_VF0_KEY + 0X1C)
#define IPS_VF0_IV0							(IPS_VF0_KEY + 0x20)
#define IPS_VF0_IV1							(IPS_VF0_KEY + 0x24)
#define IPS_VF0_IV2							(IPS_VF0_KEY + 0x28)
#define IPS_VF0_IV3							(IPS_VF0_KEY + 0x2c)
#define IPS_VF0_HASHKEY0						(IPS_VF0_KEY + 0x1000)
#define IPS_VF0_HASHKEY1						(IPS_VF0_KEY + 0x1004)
#define IPS_VF0_HASHKEY2						(IPS_VF0_KEY + 0x1008)
#define IPS_VF0_HASHKEY3						(IPS_VF0_KEY + 0x100c)
#define IPS_VF0_HASHKEY4						(IPS_VF0_KEY + 0x1010)
#define IPS_VF0_HASHKEY5						(IPS_VF0_KEY + 0x1014)
#define IPS_VF0_HASHKEY6						(IPS_VF0_KEY + 0x1018)
#define IPS_VF0_HASHKEY7						(IPS_VF0_KEY + 0x101c)
#define IPS_VF0_HASHKEY8						(IPS_VF0_KEY + 0x1020)
#define IPS_VF0_HASHKEY9                                                (IPS_VF0_KEY + 0x1024)
#define IPS_VF0_HASHKEY10                                                (IPS_VF0_KEY + 0x1028)
#define IPS_VF0_HASHKEY11                                                (IPS_VF0_KEY + 0x102c)
#define IPS_VF0_HASHKEY12                                                (IPS_VF0_KEY + 0x1030)
#define IPS_VF0_HASHKEY13                                                (IPS_VF0_KEY + 0x1034)
#define IPS_VF0_HASHKEY14                                                (IPS_VF0_KEY + 0x1038)
#define IPS_VF0_HASHKEY15                                                (IPS_VF0_KEY + 0x103c)
#define IPS_VF0_HASHKEY16                                                (IPS_VF0_KEY + 0x1040)
#define IPS_VF0_HASHKEY17                                                (IPS_VF0_KEY + 0x1044)
#define IPS_VF0_HASHKEY18                                                (IPS_VF0_KEY + 0x1048)
#define IPS_VF0_HASHKEY19                                                (IPS_VF0_KEY + 0x104c)
#define IPS_VF0_HASHKEY20                                                (IPS_VF0_KEY + 0x1050)
#define IPS_VF0_HASHKEY21                                                (IPS_VF0_KEY + 0x1054)
#define IPS_VF0_HASHKEY22                                                (IPS_VF0_KEY + 0x1058)
#define IPS_VF0_HASHKEY23                                                (IPS_VF0_KEY + 0x105c)
#define IPS_VF0_HASHKEY24                                                (IPS_VF0_KEY + 0x1060)
#define IPS_VF0_HASHKEY25                                                (IPS_VF0_KEY + 0x1064)
#define IPS_VF0_HASHKEY26                                                (IPS_VF0_KEY + 0x1068)
#define IPS_VF0_HASHKEY27                                                (IPS_VF0_KEY + 0x106c)
#define IPS_VF0_HASHKEY28                                                (IPS_VF0_KEY + 0x1070)
#define IPS_VF0_HASHKEY29                                                (IPS_VF0_KEY + 0x1074)
#define IPS_VF0_HASHKEY30                                                (IPS_VF0_KEY + 0x1078)
#define IPS_VF0_HASHKEY31                                                (IPS_VF0_KEY + 0x107c)
//#define IPS_VFO_KEYADDR(addr, offset)					(addr + offset)
#define MAX_CMD								8
#define SHA_FLAG							0
#define AES_FLAG							1
#define ENCRYPT								1
#define DECRYPT								0
#define AES_128								1
#define AES_192								2
#define AES_256								3
#define ECB_MODE							0
#define CBC_MODE							1
#define CTR_MODE							2
#define OFB_MODE							3
#define CFB_MODE							4
#define GCM_MODE							5
#define SHA_1								1
#define SHA_224								2
#define SHA_256								3
#define SHA_384								4
#define SHA_512								5
#define SHA_512_224							6
#define SHA_512_256							7
#define HASH_RAW_MODE							0
#define HASH_HMAC_MODE							1
#define INIT_VALUE							0xff
#define INIT_IV								0x11
#define WRITE_REG(addr, value) (*(volatile unsigned int *)(addr) = value)
#define READ_REG(addr) (*(volatile unsigned int *)(addr))
struct ips_command {
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
        unsigned int hm_key_size : 8;
        unsigned int reserved : 2;
        unsigned int key_exp : 1;
        unsigned int icv_append : 1;
        unsigned int icv_enc : 1;
        unsigned int icv_pt : 1;
        unsigned int aad_copy : 1;
        unsigned int encrypt : 1;
        unsigned int ctx_idx : 3;
        unsigned int ddt_mode : 1;
        unsigned int hash_mode : 1;
        unsigned int cipher_mode : 3;
        unsigned int hash_alg : 4;
        unsigned int cipher_alg : 3;
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
extern int ips_init_clk(void);
extern int ips_module_reset();
extern int ips_dev_init();
extern int ips_key_iv_set();
extern int ips_data_setup_sha(unsigned char *src, unsigned char *dst,struct ips_command* pcmd,int hash_alg,int hash_mode, int ende_flag, int proc_len);
extern int ips_data_setup_aes(unsigned char *src, unsigned char *dst,struct ips_command* pcmd, int cipher_alg,int cipher_mode, int ende_flag, int proc_len);
extern int ips_cmd_create(unsigned char *src, unsigned char *dst, int flag, int alg_flag, int alg_mode, int ende_flag, int proc_len);
extern int ips_status_polling();
extern int str_cmp(unsigned char *str1, unsigned  char *str2, int len);
static int se_ips_sha();
static int se_ips_aes(int argc, char *argv[]);
#endif
