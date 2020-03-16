#ifndef _KEYG_H_
#define _KEYG_H_

/*key generation  */


#define CYPTO_TOP_BASE0  0xff60000000//0xa0400000
#define CYPTP_TOP_BASE1  0xff60800000

#define CE_TOP_CTRL 0xff60110000//0xa0510000
#define key_top_clk 0 



#define KEYG_BASE  CYPTO_TOP_BASE0+0xf0000
#define KEYG_GO_OFFSET 0x0
#define KEYG_STAT_OFFSET 0x4
#define KEYG_SETTING_OFFSET 0x8 
#define KEYG_LABEL_OFFSET 0xc 
#define KEYG_COUNTER_OFFSET 0x10

#define KEYG_RST_OFFSET 0x80

#define KEYG_SEED_KEY0 0x20
#define KEYG_SEED_KEY1 0x24
#define KEYG_SEED_KEY2 0x28
#define KEYG_SEED_KEY3 0x2c
#define KEYG_SEED_KEY4 0x30
#define KEYG_SEED_KEY5 0x34
#define KEYG_SEED_KEY6 0x38
#define KEYG_SEED_KEY7 0x3c

#define KEYG_KEY_O 0x40

#define KEYG_SMX0_INDX 0x2<<1
#define KEYG_SMX1_INDX 0x3<<1
#define KEYG_SPACC0_INDX 0x0<<1
#define KEYG_SPACC1_INDX 0x1<<1
#define KEYG_SETTING_SEED_KEY 0x2

#define	KEYG_SETTING_256 (0<<2) 
#define	KEYG_SETTING_512 (1<<2) 

#define KEYG_SEEDKEY_HW_KEY0  0
#define KEYG_SEEDKEY_HW_KEY1  1
#define KEYG_SEEDKEY_REGISTER  2
#define KEYG_SEEDKEY_QAD  3

#define KEYG_GO_EN 1
#define KEYG_GO_DONE 1
#define KEYG_GO_MASK 1 

#define KEYG_SMX0_STAT 0x4
#define KEYG_SMX1_STAT 0x8
#define KEYG_SPACC0_STAT  0x1
#define KEYG_SPACC1_STAT 0x2

#define SMX0_SEL 0
#define SMX1_SEL 1
#define SPACC0_SEL 2
#define SPACC1_SEL 3


static void keyg_key_clear(char buf_sel);
static int keyg_get_key(char dev_sel,unsigned int label,uint32_t *seed_key,unsigned int counter,char seedkey_sel,char key_type,int readout_flag);
static void keyg_rst(void);





#endif
