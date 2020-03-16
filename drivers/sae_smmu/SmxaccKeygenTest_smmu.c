#include "elppdu.h"
#include "smx_regs.h"
#include "keyg.h"
#include "hdts_shell.h"
#include "hdts_common.h"
/* uintnt definition */
#ifndef uintnt
#define uintnt unsigned long
#endif
#define out_dword(addr, val) (*((volatile uint32_t *) (uintnt)(addr)) = ((uint32_t) (val)))
#define out_byte(addr,val)	(*((volatile uint8_t *) (addr)) = ((uint8_t) (val)))
#define in_dword(addr)       (*((volatile uint32_t *) (uintnt)(addr)))
#define in_byte(addr)		(*((volatile uint8_t *) (addr)))
#define BASE_ADDRESS SMXACC0_SMX_BASE   
#define SMX_FIFO_STAT_STAT_CNT_GET(y)       (((y) & SMX_FIFO_STAT_STAT_CNT_MASK) >> SMX_FIFO_STAT_STAT_CNT)
extern void flush_dcache_range(uint64_t addr, size_t size);
extern void smmu_test(uint64_t smx0_dma_ddt_src_va,uint64_t smx0_dma_ddt_dst_va,uint64_t smx0_dma_data_src_va,uint64_t smx0_dma_data_dst_va,uint64_t* pa_addr,int imem);

extern uint64_t get_cntp_ct_el0(void);

static int keyg_get_key(char dev_sel,unsigned int label,uint32_t *seed_key,unsigned int counter,char seedkey_sel,char key_type,int readout_flag)
{
  char stat_mask=0x0;
  char dev_type = 0x00;
  int i;
  unsigned char *keyg_reg = (unsigned char*)KEYG_BASE;
  unsigned char *keyg_clk = (unsigned char*)CE_TOP_CTRL;
  int key_o_x=0;

  //IMC security mode:QAD
  //*((unsigned int*)IMC_MSA_CTRL) = 0x3;
  //*((unsigned int*)IMC_PROTNS_CTRL) = 0x0;

  //enable clk
  //shell_msg("keygen clock 0x%02x",pdu_io_read32(keyg_clk));

  pdu_io_write32(keyg_clk,0x2);        
  //shell_msg("keygen clock 0x%02x",pdu_io_read32(keyg_clk));


  if(seed_key != NULL){
    pdu_io_write32(keyg_reg + KEYG_SEED_KEY0, seed_key[0]);        
    pdu_io_write32(keyg_reg + KEYG_SEED_KEY1, seed_key[1]);        
    pdu_io_write32(keyg_reg + KEYG_SEED_KEY2, seed_key[2]);        
    pdu_io_write32(keyg_reg + KEYG_SEED_KEY3, seed_key[3]);        
    pdu_io_write32(keyg_reg + KEYG_SEED_KEY4, seed_key[4]);        
    pdu_io_write32(keyg_reg + KEYG_SEED_KEY5, seed_key[5]);        
    pdu_io_write32(keyg_reg + KEYG_SEED_KEY6, seed_key[6]);        
    pdu_io_write32(keyg_reg + KEYG_SEED_KEY7, seed_key[7]);  
    shell_msg("KEYG 	write seed key complete");

  }

  switch(dev_sel)
  {
    case SMX0_SEL :
      stat_mask = KEYG_SMX0_STAT;
      dev_type = KEYG_SMX0_INDX;
      break;
    case SMX1_SEL: 
      stat_mask = KEYG_SMX1_STAT;
      dev_type = KEYG_SMX1_INDX;
      break;
    default: 
      break;
  }

  shell_msg("write KEYG related:");

  pdu_io_write32(keyg_reg + KEYG_LABEL_OFFSET, label);
  shell_msg("KEYG_LABEL_OFFSET 0x%02x",pdu_io_read32(keyg_reg + KEYG_LABEL_OFFSET));


  pdu_io_write32(keyg_reg + KEYG_COUNTER_OFFSET, counter); 
  shell_msg("KEYG_COUNTER_OFFSET 0x%02x",pdu_io_read32(keyg_reg + KEYG_COUNTER_OFFSET));

  pdu_io_write32(keyg_reg + KEYG_SETTING_OFFSET, (key_type|seedkey_sel));
  shell_msg("KEYG_SETTING_OFFSET 0x%02x",pdu_io_read32(keyg_reg + KEYG_SETTING_OFFSET));


  pdu_io_write32(keyg_reg + KEYG_GO_OFFSET, dev_type|KEYG_GO_EN);   
  shell_msg("KEYG_GO_OFFSET 0x%02x",pdu_io_read32(keyg_reg + KEYG_GO_OFFSET));


  int cnt = 50;
  while(cnt!=0)
  {
    cnt=cnt-1;
    unsigned int go_stat =0;
    go_stat = pdu_io_read32(keyg_reg + KEYG_GO_OFFSET);
    shell_msg("go register 0x%02x",go_stat);

    if (!(go_stat & 0x1))
      break;
  }
  shell_msg("KEYG_STAT_OFFSET,0x%02x",pdu_io_read32(keyg_reg + KEYG_STAT_OFFSET));

  int stat=0;
  while(!((stat = pdu_io_read32(keyg_reg + KEYG_STAT_OFFSET)) & stat_mask));
  shell_msg("stat=0x%02x \n",stat);

  //read key from key_o_x
  if(readout_flag==1)
  {
    //read 512-bit key
    if (key_type == KEYG_SETTING_256)
      key_o_x = 8;
    else
      key_o_x = 16;

    for(i=0;i<key_o_x;i++)
    {
      shell_msg("keyout=0x%02x \n",pdu_io_read32(keyg_reg + KEYG_KEY_O +4*i ));

    }
    //clear
    keyg_key_clear(stat_mask);
    //destroy seed key
    keyg_rst();
  }
  //IMC security mode:normal
  //*((unsigned int*)IMC_MSA_CTRL) = 0x0;
  //*((unsigned int*)IMC_PROTNS_CTRL) = 0x0;
  return 0;
}


static void keyg_key_clear(char buf_sel) 
{
  unsigned char *keyg_reg = (unsigned char*)KEYG_BASE;
  pdu_io_write32(keyg_reg + KEYG_STAT_OFFSET,buf_sel);

}

static void keyg_rst(void) 
{
  unsigned char *keyg_reg = (unsigned char*)KEYG_BASE;
  pdu_io_write32(keyg_reg + KEYG_RST_OFFSET, 0x1);        
}


static int smx_load_skp(char dev_sel, int ksz,int readout_flag)
{
  int ret = 0;
  char key_type;
  uint32_t seed_key[8] ={0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};

  if(ksz == 256)
    key_type = KEYG_SETTING_256;
  else
    key_type = KEYG_SETTING_512;

  if(!keyg_get_key(dev_sel,0x1,seed_key,0x2,KEYG_SEEDKEY_REGISTER,key_type,readout_flag))
    ret = 1; 
  return ret;

}

static int check_result(unsigned char*sys_buf0,unsigned char* sys_buf2,int src_len )
{
  //SMX check result
  while(1)
  {	
    if(src_len==0)
      break;
    if(sys_buf0[src_len-1]!=sys_buf2[src_len-1]) 
    {
      shell_msg("check result error,index=%d,buf[0][]=0x%02x,buf[2][]=0x%02x\n",
          src_len-1,sys_buf0[src_len-1],sys_buf2[src_len-1]);


      break;
    }
    src_len--;
  }
  if(src_len==0)
  {
    shell_msg("check result success\n");

    return 1;
  }
  else
    return 0;
}

static void smmu_config_bypass(int qact_alloc,int mem_type,int secure)
{
  if(qact_alloc==1){
    //smmu qact
    unsigned char* smmu_base = (unsigned char*)(CYPTO_TOP_BASE0+0x00400000+0x20000);
    pdu_io_write32(smmu_base,0xffffffff);
    uint32_t qact = pdu_io_read32(smmu_base);
    shell_msg("QSMMU_QACT 0x20000:0x%02x\n",qact);
    unsigned char* QSMMU_S_GBPA;
    uint32_t gbpa;
    if(mem_type == 1 && secure == 1){
      //smmu config GBPA
      QSMMU_S_GBPA = (unsigned char*)(CYPTO_TOP_BASE0+0x00400000+0x8044); //0xff60408044
      gbpa = pdu_io_read32(QSMMU_S_GBPA);
      shell_msg("QSMMU_QAD0_S_GBPA:0x%02x\n",gbpa);
      //shell_msg("(gbpa | 0x80008000) & 0xFFFFBFFF:0x%02x\n",(gbpa | 0x80008000) & 0xFFFFBFFF);
      //pdu_io_write32(QSMMU_QAD0_S_GBPA,0x80009000);
      //override incoming secure & memory type
      pdu_io_write32(QSMMU_S_GBPA,0x80009015);
      while(1){
        gbpa = pdu_io_read32(QSMMU_S_GBPA);
        shell_msg("QSMMU_QAD0_S_GBPA:0x%02x\n",gbpa);
        if (!(gbpa >> 31))
          break;
      }
    }else if(mem_type == 0 && secure == 1){
      QSMMU_S_GBPA = (unsigned char*)(CYPTO_TOP_BASE0+0x00400000+0x8044); //0xff60408044
      gbpa = pdu_io_read32(QSMMU_S_GBPA);
      shell_msg("QSMMU_QAD0_S_GBPA:0x%02x\n",gbpa);
      //shell_msg("(gbpa | 0x80008000) & 0xFFFFBFFF:0x%02x\n",(gbpa | 0x80008000) & 0xFFFFBFFF);
      pdu_io_write32(QSMMU_S_GBPA,0x80009000);
      while(1)
      {
        gbpa = pdu_io_read32(QSMMU_S_GBPA);
        shell_msg("QSMMU_QAD0_S_GBPA:0x%02x\n",gbpa);
        if (!(gbpa >> 31))
          break;
      }
    }
  }else{
    //free qact
    unsigned char* smmu_free_qact = (unsigned char*)(CYPTO_TOP_BASE0+0x00400000+0x22000);
    pdu_io_write32(smmu_free_qact,0xffffffff);
    uint32_t qact = pdu_io_read32(smmu_free_qact);
    shell_msg("free QACT,QSMMU_QACT 0x22000:0x%02x\n",qact);

  }
}

static void smmu_config_memtype(int qact_cfg)
  {
//smmu qact
if(qact_cfg==1){
unsigned char* smmu_base = (unsigned char*)(CYPTO_TOP_BASE0+0x00400000+0x20000);
pdu_io_write32(smmu_base,0xffffffff);
uint32_t qact = pdu_io_read32(smmu_base);
shell_msg("QSMMU_QACT 0x20000:0x%02x\n",qact);
//smmu config GBPA
unsigned char* QSMMU_S_GBPA = (unsigned char*)(CYPTO_TOP_BASE0+0x00400000+0x8044); //0xff60408044
uint32_t gbpa = pdu_io_read32(QSMMU_S_GBPA);
shell_msg("QSMMU_QAD0_S_GBPA:0x%02x\n",gbpa);
//shell_msg("(gbpa | 0x80008000) & 0xFFFFBFFF:0x%02x\n",(gbpa | 0x80008000) & 0xFFFFBFFF);
//pdu_io_write32(QSMMU_QAD0_S_GBPA,0x80009000);
//override incoming secure & memory type
pdu_io_write32(QSMMU_S_GBPA,0x80009015);
while(1){
gbpa = pdu_io_read32(QSMMU_S_GBPA);
shell_msg("QSMMU_QAD0_S_GBPA:0x%02x\n",gbpa);
if (!(gbpa >> 31))
break;
}
}else{
//free qact
unsigned char* smmu_free_qact = (unsigned char*)(CYPTO_TOP_BASE0+0x00400000+0x22000);
pdu_io_write32(smmu_free_qact,0xffffffff);
uint32_t qact = pdu_io_read32(smmu_free_qact);
shell_msg("free QACT,QSMMU_QACT 0x22000:0x%02x\n",qact);

}
}

#define IMC_NORMAL 		0
#define IMC_SECURITY 	1
#define IMC_QAD			2

static void smx_enqueue_packet(unsigned char* smxacc_base,uint32_t* smx0_dma_ddt_src,uint32_t* smx0_dma_ddt_dst,int src_len,int key_flag,int enc)
{
  shell_msg("smx0_dma_ddt_src %p\n",(void*)(smx0_dma_ddt_src));
  pdu_io_write32 (smxacc_base + SMX_SRC_PTR_REG_OFFSET, (uint64_t) smx0_dma_ddt_src); 
  shell_msg("SMX_SRC_PTR 0x%02x\n",pdu_io_read32(smxacc_base + SMX_SRC_PTR_REG_OFFSET));


  shell_msg("smx0_dma_ddt_dst %p\n",(void*)(smx0_dma_ddt_dst));								//0x24 
  pdu_io_write32 (smxacc_base + SMX_DST_PTR_REG_OFFSET, (uint64_t)smx0_dma_ddt_dst);				
  shell_msg("SMX_DST_PTR 0x%02x\n",pdu_io_read32(smxacc_base + SMX_DST_PTR_REG_OFFSET));


  //security ctrl
  //pdu_io_write32 (smxacc_base+SMX_SECURE_CTRL_REG_OFFSET,0x15);
  //shell_msg("SMX_SECURE_CTRL_REG_OFFSET:0x%02x\n",pdu_io_read32(smxacc_base + SMX_SECURE_CTRL_REG_OFFSET));
  //
  pdu_io_write32 (smxacc_base + SMX_PROC_LEN_REG_OFFSET, src_len);	//src_len							//0x34
  shell_msg("SMX_PROC_LEN 0x%02x\n",pdu_io_read32(smxacc_base + SMX_PROC_LEN_REG_OFFSET));

  pdu_io_write32 (smxacc_base + SMX_ICV_OFFSET_REG_OFFSET,    0);									//0x3C
  pdu_io_write32 (smxacc_base + SMX_PRE_AAD_LEN_REG_OFFSET  ,  0);									//0x2C
  pdu_io_write32 (smxacc_base + SMX_IV_OFFSET_REG_OFFSET,     0);									//0x40
  pdu_io_write32 (smxacc_base + SMX_OFFSET_REG_OFFSET,0);											//0x28
  pdu_io_write32 (smxacc_base + SMX_AUX_INFO_REG_OFFSET, 0);											//0x48
  if(enc == 1){
    //encrypt
    //write smx ctrl
    if (key_flag == 1)
      pdu_io_write32 (smxacc_base + SMX_CTRL_REG_OFFSET,0x11001);//set CTRL.SEC_KEY=1
    else
      pdu_io_write32 (smxacc_base + SMX_CTRL_REG_OFFSET,0x1001);
  }else{
    //decrypt
    //write smx ctrl
    if (key_flag == 1)
      pdu_io_write32 (smxacc_base + SMX_CTRL_REG_OFFSET,0x18001);
    else
      pdu_io_write32 (smxacc_base + SMX_CTRL_REG_OFFSET,0x8001);
  }
}

static void smx_dequeue_packet(unsigned char* smxacc_base,unsigned char* dst_data,int dst_len)
{
  int fifo;
  int cmdstat;
  int query_count = 100; 
  while(1){
    if(query_count==0)
      break;
    query_count--;
    shell_msg("SMX_IRQ_STAT_REG_OFFSET:0x%02x\n",pdu_io_read32(smxacc_base + SMX_IRQ_STAT_REG_OFFSET));

    fifo = SMX_FIFO_STAT_STAT_CNT_GET (pdu_io_read32 (smxacc_base + SMX_FIFO_STAT_REG_OFFSET));
    shell_msg("SMX_FIFO_STAT_STAT_CNT_GET is %d\n",fifo);

    while(fifo-- > 0){
      query_count = 0;
      // write the pop register to get the next job 
      pdu_io_write32 (smxacc_base + SMX_STAT_POP_REG_OFFSET, 1);
      cmdstat = pdu_io_read32 (smxacc_base + SMX_STATUS_REG_OFFSET);
      shell_msg("cmdstat is 0x%02x.\n",cmdstat);

      if(cmdstat & SMX_STAT_OK_MASK){
        //int stat= CRYPTO_OK;
        shell_msg("CRYPTO_OK.enc value = \n");

        //flush cache
        //l3_flush();
        int hash_len=dst_len;
        unsigned char *hash_buf = dst_data ;
        /* if(inIMEM==0)
           hash_buf = (unsigned char*)sys_buf1;//sys_buf1;
           else
           hash_buf = buf[1]; */
        while(1){
          shell_msg(" 0x%02x",*hash_buf);

          hash_len--;
          if(hash_len==0)
            break;
          hash_buf++;
        }
      }
      else
      {
        shell_msg("cmdstat = %d,CRYPTO_ERROR\n",cmdstat);

      }
      break;
    }
  }
}

//void out_data(uint64_t dma_data_dst_pa,uint8_t buf1[],int dst_len);
static void smx_dequeue_packet_smmu_en(unsigned char* smxacc_base,uint64_t* pa_addrs,unsigned char* dst_data,int dst_len)
{
  int fifo;
  int cmdstat;
  int query_count = 100; 
  while(1){
    if(query_count==0)
      break;
    query_count--;
    shell_msg("SMX_IRQ_STAT_REG_OFFSET:0x%02x\n",pdu_io_read32(smxacc_base + SMX_IRQ_STAT_REG_OFFSET));

    fifo = SMX_FIFO_STAT_STAT_CNT_GET (pdu_io_read32 (smxacc_base + SMX_FIFO_STAT_REG_OFFSET));
    shell_msg("SMX_FIFO_STAT_STAT_CNT_GET is %d\n",fifo);

    while(fifo-- > 0){
      query_count = 0;
      // write the pop register to get the next job 
      pdu_io_write32 (smxacc_base + SMX_STAT_POP_REG_OFFSET, 1);
      cmdstat = pdu_io_read32 (smxacc_base + SMX_STATUS_REG_OFFSET);
      shell_msg("cmdstat is 0x%02x.\n",cmdstat);

      if(cmdstat & SMX_STAT_OK_MASK){
        //int stat= CRYPTO_OK;
        shell_msg("CRYPTO_OK.enc value = \n");

        //flush cache
        //l3_flush();
        //copy dst data to va
        //out_data(pa_addrs[3],dst_data,dst_len);
        int hash_len=dst_len;
        unsigned char *hash_buf = dst_data ;
        /* if(inIMEM==0)
           hash_buf = (unsigned char*)sys_buf1;//sys_buf1;
           else
           hash_buf = buf[1]; */
        while(1){
          shell_msg(" 0x%02x",*hash_buf);

          hash_len--;
          if(hash_len==0)
            break;
          hash_buf++;
        }
      }
      else
      {
        shell_msg("cmdstat = %d,CRYPTO_ERROR\n",cmdstat);

      }
      break;
    }
  }
}

//void out_data(uint64_t dma_data_dst_pa,uint8_t buf1[],int dst_len)
//{
//  uint8_t read_data;
//  uint8_t *buf;
//  buf = buf1;
//  for(int i=0;i<dst_len;i++)
//  {
//    read_data = in_byte(dma_data_dst_pa+i);
//    //shell_msg( "dma_data_dst_addr:0x%0X;read data:0x%0X\n",dma_data_dst_pa+i,read_data);
//
//    *buf = read_data;
//    buf++;
//  }
//}
//void initial_data(uint64_t dma_data_src_pa,uint8_t buf0[],int src_len)
//{
//  uint8_t read_data;
//  shell_msg( "initial dma_data_src\n");
//
//  for(int i=0;i<src_len;i++)
//  {
//    //shell_msg( "test sys imem,dma_data_src_addr:0x%0x_%0x\n",((dma_data_src_pa+i)>>32),(dma_data_src_pa+i));
//
//    out_byte(dma_data_src_pa+i,buf0[i]);
//  }
//  for(int j=0;j<src_len;j++)
//  {
//    read_data = in_byte(dma_data_src_pa+j);
//    shell_msg( "dma_data_src_addr:0x%02x_%02x;read data:0x%02x\n",(uint32_t)((dma_data_src_pa+j)>>32),(uint32_t)(dma_data_src_pa+j),read_data);
//
//  }
//}
//void initial_ddt(uint64_t dma_ddt_src_addr,uint32_t dma_ddt_src[],uint64_t dma_ddt_dst_addr,uint32_t dma_ddt_dst[])
//{
//  //uint32_t cnt = 0;
//  //uint64_t addr = 0;
//  uint32_t read_data = 0;
//  //uint32_t write_data = 0;
//  //initial dma_ddt_src
//  shell_msg( "initial dma_ddt_src\n");
//
//
//  //SYS IMEM TEST
//  //out_dword(SYS_IMEM,0x00223344);
//  //shell_msg("SYS_IMEM:0x%2x\n",in_dword(SYS_IMEM)); 
//  //
//  for(int i=0;i<=3;i++)
//  {
//    //(uint32_t*)(dma_ddt_src_addr+i) = (uint32_t)dma_ddt_src[i];
//    //shell_msg( "test sys imem,dma_ddt_src_addr:0x%0x_%0x\n",((dma_ddt_src_addr+i*4)>>32),(dma_ddt_src_addr+i*4));
//
//    out_dword(dma_ddt_src_addr+i*4,dma_ddt_src[i]);
//  }
//  //inital dma_ddt_dst
//  shell_msg( "initial dma_ddt_dst\n");
//
//  for(int j=0;j<=3;j++)
//  {
//    //(uint32_t*)(dma_ddt_dst_addr+j) = (uint32_t)dma_ddt_dst[j];
//    out_dword(dma_ddt_dst_addr+j*4,dma_ddt_dst[j]);
//  }
//  //read dma_ddt_src
//  for(int k=0;k<=3;k++)
//  {
//    //read_data = (uint32_t*)(dma_ddt_src_addr+k);
//    read_data = in_dword(dma_ddt_src_addr+k*4);
//    shell_msg( "dma_ddt_src_addr:0x%02x_%02x;read data:0x%0X\n",(uint32_t)((dma_ddt_src_addr+k*4)>>32),(uint32_t)(dma_ddt_src_addr+k*4),read_data);
//
//  }
//  //read dma_ddt_dst
//  for(int n=0;n<=3;n++)
//  {
//    //read_data = (uint32_t*)(dma_ddt_dst_addr+n);
//    read_data = in_dword(dma_ddt_dst_addr + n*4);
//    //shell_msg( "dma_ddt_dst_addr:0x%0X;read data:0x%0X\n",dma_ddt_dst_addr+n*4,read_data);
//
//  }
//}

#define SYS_IMEM_10 0xff6f8924a0
#define SYS_IMEM_20 0xff6f8924c0
#define SYS_IMEM_30 0xff6f8924e0
#define SYS_IMEM_40 0xff6f892500
#define SYS_IMEM_50 0xff6f892520
#define SYS_IMEM_8 0xff70030DF0


/*===========================================================================
 **  Function :  run_cipher_smx_smmu
 ** ==========================================================================
 */
/*!
 *
 * @brief
 *   This function test sms4,smmu enable,and smmu & mmu share page table,smmu enable,and smmu & mmu share page table
 *
 * @param[in] key_flag 0:write key from extern;1:load key from key port
 * @param[in] dev_sel 0:SMX0 1:SMX1
 * @param[in] inIMEM 0:ddt and data in IMC IMEM;1:ddt and data in DDR
 * @par Dependencies
 *   None
 *
 * @retval
 *   
 *
 * @par Side Effects
 *   None
 *
 */
int run_cipher_smx_smmu(int key_flag,int dev_sel)
{
  unsigned char buf[3][1024];
  unsigned char key[16];
  int i;
  // make up a message
  for (i = 0; i < 1024; i+=10) {
    buf[0][i] = i & 0xFF;
  }
  for (i = 0; i < 16; i++) {
    key[i] = i;
  }
  int src_len,dst_len;
  src_len = sizeof(buf[0]);
  dst_len = sizeof(buf[1]);
  ////IMC security mode:normal
  //imc_config_security(IMC_NORMAL);
  //shell_msg("non-secure mode 2017-10-19");

  ////SYS IMEM TEST
  //out_dword(SYS_IMEM_8,0x11223344);
  //shell_msg("SYS_IMEM8:0x%2x\n",in_dword(SYS_IMEM_8)); 

  unsigned char *smxacc_base = NULL;
  unsigned char *ce_smxacc_ctrl = NULL;
  if(dev_sel == SMX0_SEL)
  {
    smxacc_base = (unsigned char*)SMXACC0_SMX_BASE;
    ce_smxacc_ctrl = (unsigned char*)CE0_SMXACC_CTRL;
  }
  else
  {
    smxacc_base = (unsigned char*)SMXACC1_SMX_BASE;
    ce_smxacc_ctrl = (unsigned char*)CE1_SMXACC_CTRL;
  }
  //enable smxacc clk
  pdu_io_write32(ce_smxacc_ctrl,0x1);
  // create DDT for message
  uint32_t* smx0_dma_ddt_src;
  uint32_t* smx0_dma_ddt_dst;
  unsigned char ddt_src_align[16+8];
  unsigned char ddt_dst_align[16+8];
  smx0_dma_ddt_src = (uint32_t *)(((uint64_t)ddt_src_align + 7) & ~7);// 
  smx0_dma_ddt_dst = (uint32_t *)(((uint64_t)ddt_dst_align + 7) & ~7);//
  smx0_dma_ddt_src[0] = (uint32_t)((uint64_t)buf[0]);
  smx0_dma_ddt_src[1] = src_len;
  smx0_dma_ddt_src[2] = 0x0;
  smx0_dma_ddt_src[3] = 0x0;
  smx0_dma_ddt_dst[0] = (uint32_t)((uint64_t)buf[1]);
  smx0_dma_ddt_dst[1] = dst_len;
  smx0_dma_ddt_dst[2] = 0x0;
  smx0_dma_ddt_dst[3] = 0x0;

  //prepare key
  if (key_flag==1)
  {
    //load key from key port
    shell_msg("load key from port again 20180208 \n");

    //select smx0,256 bit key
    //IMC security mode:normal
    //imc_config_security(IMC_QAD);
    smx_load_skp(dev_sel,256,1);
    //IMC security mode:normal
    //imc_config_security(IMC_NORMAL);
  }
  else
  {
    //write key context
    shell_msg("write key context 20171019\n");	

    //little endian
    pdu_to_dev32_s(smxacc_base + SMX_CTX_CIPH_KEY,key,8,0);
    //read keybuf
    unsigned char key_buf[32];
    pdu_from_dev32_s(key_buf,smxacc_base + SMX_CTX_CIPH_KEY,8,0);
    for (i = 0; i < 16; i++) {
      shell_msg("key_buf[%d] = 0x%02x  \n",i,key_buf[i]);

    }
  }
  ////smmu enable
  uint64_t pa_addrs[4]={0};
  //if(pa_in_IMEM==1)
  //  smmu_test((uint64_t)smx0_dma_ddt_src,(uint64_t)smx0_dma_ddt_dst,(uint64_t)buf[0],(uint64_t)buf[1], pa_addrs,1);
  //else
  //  smmu_test((uint64_t)smx0_dma_ddt_src,(uint64_t)smx0_dma_ddt_dst,(uint64_t)buf[0],(uint64_t)buf[1], pa_addrs,0);

  ////copy ddt to pa
  //initial_ddt(pa_addrs[0],smx0_dma_ddt_src,pa_addrs[1],smx0_dma_ddt_dst);
  ////copy src data to pa
  //initial_data(pa_addrs[2],buf[0],src_len);

  //ddt va address expended to 64 bit for smmu,only lower 8 bit is valid
  pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_rd_ddt,0x00);
  pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_rd_data,0x00);
  pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_wr_data,0x00);
  pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_expend,0x0); 

  //packet enqueue,keyport,encrypt
  smx_enqueue_packet(smxacc_base,smx0_dma_ddt_src,smx0_dma_ddt_dst,src_len,key_flag,1);
  //dequeue
  smx_dequeue_packet_smmu_en(smxacc_base,pa_addrs,buf[1],dst_len);

  //decrypt
  // create DDT for message
  //initial_data(pa_addrs[2],buf[1],src_len);
  memcpy(buf[0],buf[1],src_len);
  //prepare key
  if (key_flag==1){
    //IMC security mode:normal
    //imc_config_security(IMC_QAD);
    smx_load_skp(0,256,1);
    //IMC security mode:normal
    // imc_config_security(IMC_NORMAL);
  }else{
    //write key context
    pdu_to_dev32_s(smxacc_base + SMX_CTX_CIPH_KEY,key,8,0);//little endian
    //read keybuf
    unsigned char key_buf[32];
    pdu_from_dev32_s(key_buf,smxacc_base + SMX_CTX_CIPH_KEY,8,0);
    for (i = 0; i < 16; i++) {
      shell_msg("key_buf[%d] = 0x%02x  \n",i,key_buf[i]);

    }
  }
  //enqueue
  smx_enqueue_packet(smxacc_base,smx0_dma_ddt_src,smx0_dma_ddt_dst,src_len,key_flag,0);
  //dequeue
  smx_dequeue_packet_smmu_en(smxacc_base,pa_addrs,buf[1],dst_len);

  //clear key
  char stat_mask=0x0;
  if (dev_sel==SMX0_SEL)
    stat_mask = KEYG_SMX0_STAT;
  else if(dev_sel==SMX1_SEL)
    stat_mask = KEYG_SMX1_STAT;
  else
    stat_mask = 0xff;
  keyg_key_clear(stat_mask);
  //destroy seed key
  keyg_rst();
  //SMX check result
  check_result(buf[0],buf[1],src_len);
  return 0;
}
/*===========================================================================
 **  Function :  run_cipher_smx
 ** ==========================================================================
 */
/*!
 *
 * @brief
 *   This function test sms4
 *
 * @param[in] key_flag 0:write key from extern;1:load key from key port
 * @param[in] dev_sel 0:SMX0 1:SMX1
 * @param[in] inIMEM 0:ddt and data in IMC IMEM;1:ddt and data in DDR
 * @par Dependencies
 *   None
 *
 * @retval
 *   
 *
 * @par Side Effects
 *   None
 *
 */
int run_cipher_smx_imem(int key_flag,int dev_sel,int inIMEM)//,int smmu_en)
{
  unsigned char buf[3][32];
  unsigned char key[16];
  int i;
  // make up a message
  for (i = 0; i < 32; i++) {
    buf[0][i] =i;
  }
  for (i = 0; i < 16; i++) {
    key[i] = i;
  }
  int src_len,dst_len;
  src_len = sizeof(buf[0]);
  dst_len = sizeof(buf[1]);

  //SYS IMEM TEST
  out_dword(SYS_IMEM_8,0x11223344);
  shell_msg("SYS_IMEM8:0x%2x\n",in_dword(SYS_IMEM_8)); 


  unsigned char *smxacc_base = NULL;
  unsigned char *ce_smxacc_ctrl = NULL;
  if(dev_sel == SMX0_SEL)
  {
    smxacc_base = (unsigned char*)SMXACC0_SMX_BASE;
    ce_smxacc_ctrl = (unsigned char*)CE0_SMXACC_CTRL;
  }
  else
  {
    smxacc_base = (unsigned char*)SMXACC1_SMX_BASE;
    ce_smxacc_ctrl = (unsigned char*)CE1_SMXACC_CTRL;
  }
  //enable smxacc clk
  pdu_io_write32(ce_smxacc_ctrl,0x1);
  //smx security ctrl
  pdu_io_write32 (smxacc_base+SMX_SECURE_CTRL_REG_OFFSET,0x15);
  shell_msg("SMX_SECURE_CTRL_REG_OFFSET:0x%02x\n",pdu_io_read32(smxacc_base + SMX_SECURE_CTRL_REG_OFFSET));
  //DDR must set smmu memory type config non-cacheable
  if(inIMEM == 0){
    //since smx secure_ctrl is set to secure & cache is enabled,smmu need config QACT only.
    smmu_config_bypass(1,0,0);
    //smmu_config_bypass(1,0,1);
  }
  else{
    smmu_config_bypass(1,0,1);
  }
  //
  pdu_io_write32 (smxacc_base + SMX_PROC_LEN_REG_OFFSET, src_len);	//src_len							//0x34
  shell_msg("SMX_PROC_LEN 0x%02x\n",pdu_io_read32(smxacc_base + SMX_PROC_LEN_REG_OFFSET));
  // create DDT for message
  uint32_t* smx0_dma_ddt_src;
  uint32_t* smx0_dma_ddt_dst;
  unsigned char* sys_buf0;
  unsigned char* sys_buf1;
  unsigned char* sys_buf2;
  unsigned char ddt_src_align[16+8];
  unsigned char ddt_dst_align[16+8];
  if(inIMEM == 1){
    //IMC IMEM
    int index=0;
    sys_buf0 = (unsigned char*)SYS_IMEM_30;
    for(index = 0;index < 32;index++)
      sys_buf0[index] = buf[0][index];
    sys_buf1 = (unsigned char*)SYS_IMEM_40;
    for(index = 0;index < 32;index++)
      sys_buf1[index] = buf[1][index];
    sys_buf2 = (unsigned char*)SYS_IMEM_50;
    for(index = 0;index < 32;index++)
      sys_buf2[index] = buf[2][index];
    smx0_dma_ddt_src = (uint32_t*)SYS_IMEM_10;
    smx0_dma_ddt_src[0] = (PDU_DMA_ADDR_T)((uint64_t)sys_buf0);
    smx0_dma_ddt_src[1] = src_len;
    smx0_dma_ddt_src[2] = 0x0;
    smx0_dma_ddt_src[3] = 0x0;
    smx0_dma_ddt_dst = (uint32_t*)SYS_IMEM_20;
    smx0_dma_ddt_dst[0] = (PDU_DMA_ADDR_T)((uint64_t)sys_buf1);
    smx0_dma_ddt_dst[1] = dst_len;
    smx0_dma_ddt_dst[2] = 0x0;
    smx0_dma_ddt_dst[3] = 0x0;
  }else{
    smx0_dma_ddt_src = (uint32_t *)(((uint64_t)ddt_src_align + 7) & ~7);// 
    smx0_dma_ddt_dst = (uint32_t *)(((uint64_t)ddt_dst_align + 7) & ~7);//
    smx0_dma_ddt_src[0] = (uint32_t)((uint64_t)buf[0]);
    smx0_dma_ddt_src[1] = src_len;
    smx0_dma_ddt_src[2] = 0x0;
    smx0_dma_ddt_src[3] = 0x0;
    smx0_dma_ddt_dst[0] = (uint32_t)((uint64_t)buf[1]);
    smx0_dma_ddt_dst[1] = dst_len;
    smx0_dma_ddt_dst[2] = 0x0;
    smx0_dma_ddt_dst[3] = 0x0;
    shell_msg("buf[0] addr:0x%02x_%02x,buf[1] addr:0x%02x_%02x\n",(uint32_t)(((uint64_t)buf[0])>>32),(uint32_t)((uint64_t)buf[0]),(uint32_t)(((uint64_t)buf[1])>>32),(uint32_t)((uint64_t)buf[1]));
  }

  //prepare key
  if (key_flag==1)
  {
    //load key from key port
    shell_msg("load key from port again 20171020 \n");

    //select smx0,256 bit key
    //IMC security mode:normal
    //imc_config_security(IMC_QAD);
    smx_load_skp(dev_sel,256,1);
    //IMC security mode:normal
    //imc_config_security(IMC_NORMAL);
  }
  else
  {
    //write key context
    shell_msg("write key context 20171020\n");	

    //little endian
    pdu_to_dev32_s(smxacc_base + SMX_CTX_CIPH_KEY,key,8,0);
    //read keybuf
    unsigned char key_buf[32];
    pdu_from_dev32_s(key_buf,smxacc_base + SMX_CTX_CIPH_KEY,8,0);
    for (i = 0; i < 16; i++) {
      shell_msg("key_buf[%d] = 0x%02x  \n",i,key_buf[i]);

    }
  }
  //smmu enable
  /*uint64_t pa_addrs[4]={0};
    if(smmu_en==1){
    smmu_test((uint64_t)smx0_dma_ddt_src,(uint64_t)smx0_dma_ddt_dst,(uint64_t)buf[0],(uint64_t)buf[1], pa_addrs,1);
  //shell_msg( "test sys imem,dma_ddt_src_addr:0x%0x_%0x\n",(pa_addrs[0]>>32),pa_addrs[0]);

  //copy ddt to pa
  initial_ddt(pa_addrs[0],smx0_dma_ddt_src,pa_addrs[1],smx0_dma_ddt_dst);
  //copy src data to pa
  initial_data(pa_addrs[2],buf[0],src_len);
  }*/
  //ddt va address expended to 64 bit for smmu,only lower 8 bit is valid
  if(inIMEM == 0){
    pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_rd_ddt,0x00);
    pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_rd_data,0x00);
    pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_wr_data,0x00);
    pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_expend,0x0); 
  }else{
    pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_rd_ddt,0xFF);
    pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_rd_data,0xFF);
    pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_wr_data,0xFF); 
    pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_expend,0x0); 
  }
  //packet enqueue,keyport,encrypt
  smx_enqueue_packet(smxacc_base,smx0_dma_ddt_src,smx0_dma_ddt_dst,src_len,key_flag,1);
  //dequeue
  if(inIMEM == 1)
    smx_dequeue_packet(smxacc_base,sys_buf1,dst_len);
  else{
    /*    if(smmu_en == 1)
          smx_dequeue_packet_smmu_en(smxacc_base,pa_addrs,buf[1],dst_len);
          else*/
    smx_dequeue_packet(smxacc_base,buf[1],dst_len);
  }

  //decrypt
  // create DDT for message
  /*  if(smmu_en==1){
  //DDR,copy src data to pa
  if(inIMEM == 0)
  initial_data(pa_addrs[2],buf[1],src_len);
  else{
  initial_data(pa_addrs[2],buf[1],src_len);
  }
  }else{*/
  if(inIMEM==1){
    smx0_dma_ddt_src[0] = (PDU_DMA_ADDR_T)((uint64_t)sys_buf1);
    smx0_dma_ddt_src[1] = src_len;
    smx0_dma_ddt_src[2] = 0x0;
    smx0_dma_ddt_src[3] = 0x0;
    smx0_dma_ddt_dst[0] = (PDU_DMA_ADDR_T)((uint64_t)sys_buf2);
    smx0_dma_ddt_dst[1] = dst_len;
    smx0_dma_ddt_dst[2] = 0x0;
    smx0_dma_ddt_dst[3] = 0x0;
  }else{
    smx0_dma_ddt_src[0] = (uint32_t)((uint64_t)buf[1]);
    smx0_dma_ddt_src[1] = src_len;
    smx0_dma_ddt_src[2] = 0x0;
    smx0_dma_ddt_src[3] = 0x0;
    smx0_dma_ddt_dst[0] = (uint32_t)((uint64_t)buf[2]);
    smx0_dma_ddt_dst[1] = dst_len;
    smx0_dma_ddt_dst[2] = 0x0;
    smx0_dma_ddt_dst[3] = 0x0;
  }
  //}
  //prepare key
  if (key_flag==1){
    //IMC security mode:normal
    //imc_config_security(IMC_QAD);
    smx_load_skp(0,256,1);
    //IMC security mode:normal
    // imc_config_security(IMC_NORMAL);
  }else{
    //write key context
    pdu_to_dev32_s(smxacc_base + SMX_CTX_CIPH_KEY,key,8,0);//little endian
    //read keybuf
    unsigned char key_buf[32];
    pdu_from_dev32_s(key_buf,smxacc_base + SMX_CTX_CIPH_KEY,8,0);
    for (i = 0; i < 16; i++) {
      shell_msg("key_buf[%d] = 0x%02x  \n",i,key_buf[i]);

    }
  }
  smx_enqueue_packet(smxacc_base,smx0_dma_ddt_src,smx0_dma_ddt_dst,src_len,key_flag,0);
  //dequeue
  if(inIMEM==1)
    smx_dequeue_packet(smxacc_base,sys_buf2,dst_len);
  else{
    /* if(smmu_en==1){
       smx_dequeue_packet_smmu_en(smxacc_base,pa_addrs,buf[1],dst_len);
       }*/
    smx_dequeue_packet(smxacc_base,buf[2],dst_len);
  }
  //clear key
  char stat_mask=0x0;
  if (dev_sel==SMX0_SEL)
    stat_mask = KEYG_SMX0_STAT;
  else if(dev_sel==SMX1_SEL)
    stat_mask = KEYG_SMX1_STAT;
  else
    stat_mask = 0xff;
  keyg_key_clear(stat_mask);
  //destroy seed key
  keyg_rst();
  //SMX check result
  if(inIMEM == 1)
    check_result(sys_buf0,sys_buf2,src_len);
  else
    check_result(buf[0],buf[2],src_len);
  //free qact
  smmu_config_bypass(0,1,1);
  return 0;
}

#define SYS_IMEM_1 0x18044000
#define SYS_IMEM_2 0x18044020
#define SYS_IMEM_3 0x19000000
#define SYS_IMEM_4 0x18044F00
int run_hash_smx_smmu(int dev_sel,unsigned char* message,int msg_len)
{
  unsigned char* src_buf = message;
  //unsigned char src_buf[] = "hello,world"; 
  unsigned char dst_buf[32];
  int src_len,dst_len;
  src_len = msg_len;//sizeof(src_buf)-1;
  //src_len = 0x1000000;//16MB
  shell_msg( "src_len=%d\n",src_len);
  dst_len = 32;
  unsigned char *smxacc_base = NULL;
  unsigned char *ce_smxacc_ctrl = NULL;
  if(dev_sel == SMX0_SEL)
  {
    smxacc_base = (unsigned char*)SMXACC0_SMX_BASE;
    ce_smxacc_ctrl = (unsigned char*)CE0_SMXACC_CTRL;
  }
  else
  {
    smxacc_base = (unsigned char*)SMXACC1_SMX_BASE;
    ce_smxacc_ctrl = (unsigned char*)CE1_SMXACC_CTRL;
  }
  //config smmu bypass
  //smmu_config_bypass(1,0,1);
  //enable smxacc clk
  pdu_io_write32(ce_smxacc_ctrl,0x1);
  //shell_msg( "ce_smxacc_ctrl=%02x\n",pdu_io_read32(ce_smxacc_ctrl));
  // create DDT for message
  uint32_t* smx0_dma_ddt_src;
  uint32_t* smx0_dma_ddt_dst;
  unsigned char ddt_src_align[16+8];
  unsigned char ddt_dst_align[16+8];
  smx0_dma_ddt_src = (uint32_t *)(((uint64_t)ddt_src_align + 7) & ~7);// 
  smx0_dma_ddt_dst = (uint32_t *)(((uint64_t)ddt_dst_align + 7) & ~7);//
  smx0_dma_ddt_src[0] = (uint32_t)((uint64_t)src_buf);
  smx0_dma_ddt_src[1] = src_len;
  smx0_dma_ddt_src[2] = 0x0;
  smx0_dma_ddt_src[3] = 0x0;
  smx0_dma_ddt_dst[0] = (uint32_t)((uint64_t)dst_buf);
  smx0_dma_ddt_dst[1] = dst_len;
  smx0_dma_ddt_dst[2] = 0x0;
  smx0_dma_ddt_dst[3] = 0x0;
  shell_msg("src_buf addr:0x%02x_%02x,dst_buf addr:0x%02x_%02x\n",(uint32_t)(((uint64_t)src_buf)>>32),(uint32_t)((uint64_t)src_buf),(uint32_t)(((uint64_t)dst_buf)>>32),(uint32_t)((uint64_t)dst_buf));
  //shell_msg("smxacc_addr_high expend.\n");
	flush_dcache_range((uint64_t)smx0_dma_ddt_src, 0x20);
	flush_dcache_range((uint64_t)smx0_dma_ddt_dst, 0x20);
	flush_dcache_range((uint64_t)src_buf, 0x20);
  pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_rd_ddt,0x00);
  pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_rd_data,0x00);
  pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_wr_data,0x00);
  pdu_io_write32 (ce_smxacc_ctrl+SMxAcc0_addr_high_expend,0x0); 
  //enqueue
  shell_msg( "smx0_dma_ddt_src=0x%02x_%02x\n",(uint32_t)(((uint64_t)smx0_dma_ddt_src)>>32),(uint32_t)((uint64_t)smx0_dma_ddt_src));
  pdu_io_write32 (smxacc_base+ SMX_SRC_PTR_REG_OFFSET, (uint32_t)((uint64_t)smx0_dma_ddt_src));
  shell_msg( "smx0_dma_ddt_dst=0x%02x_%02x\n",(uint32_t)(((uint64_t)smx0_dma_ddt_dst)>>32),(uint32_t)((uint64_t)smx0_dma_ddt_dst));
  pdu_io_write32 (smxacc_base+ SMX_DST_PTR_REG_OFFSET, (uint32_t)((uint64_t)smx0_dma_ddt_dst));
  pdu_io_write32 (smxacc_base+ SMX_PROC_LEN_REG_OFFSET,      src_len);
  //shell_msg("smx_proc_len = %02x\n",pdu_io_read32(smxacc_base+ SMX_PROC_LEN_REG_OFFSET));
  pdu_io_write32 (smxacc_base+ SMX_ICV_OFFSET_REG_OFFSET,    0);
  pdu_io_write32 (smxacc_base+ SMX_PRE_AAD_LEN_REG_OFFSET  ,  src_len);//PRE_AAD_LEN == PROC_LEN
  pdu_io_write32 (smxacc_base+ SMX_IV_OFFSET_REG_OFFSET,     0);
  pdu_io_write32 (smxacc_base + SMX_OFFSET_REG_OFFSET,0);											//0x28
  pdu_io_write32 (smxacc_base+ SMX_AUX_INFO_REG_OFFSET, 0);
  // write the job ID to the core, we keep track of it in software now to avoid excessive port I/O 
  pdu_io_write32 (smxacc_base+ SMX_CTRL_REG_OFFSET,0x1002);

  //dequeue
  uint32_t fifo;
  uint32_t cmdstat;
  //int query_count = 5000;
  while(1)
  {
    //if(query_count == 0)
     // break;
    //query_count--;
    //shell_msg("SMX_IRQ_STAT_REG_OFFSET:0x%02x\n",pdu_io_read32(smxacc_base + SMX_IRQ_STAT_REG_OFFSET));
		//shell_msg("Read result.\r\n");
    fifo = SMX_FIFO_STAT_STAT_CNT_GET (pdu_io_read32 (smxacc_base+ SMX_FIFO_STAT_REG_OFFSET));
    while(fifo-- > 0)
    {
      //query_count = 0;
      // write the pop register to get the next job 
      pdu_io_write32 (smxacc_base+ SMX_STAT_POP_REG_OFFSET, 1);
      cmdstat = pdu_io_read32 (smxacc_base+ SMX_STATUS_REG_OFFSET);
      if(cmdstat & SMX_STAT_OK_MASK){
        shell_msg( "CRYPTO OK.\n");
        //memcpy(buf,dst_virt,dst_len);
        //shell_msg( "hash value=\n");
        //copy dst data to va
//        out_data(pa_addrs[3],sys_buf1,dst_len);
        int hash_len=32;
        unsigned char *hash_buf = dst_buf;
        while(hash_len--){
          shell_msg( " 0x%02x", *hash_buf);

          hash_buf++;
        }
        return 0;
        //shell_msg("\n");
      }
      else
      {
        shell_msg( "cmdstat =  0x%02x.\n",cmdstat);
        shell_msg( "CRYPTO ERROR.\r\n");
      }
    }
  }
  //smmu_config_bypass(0,0,0);
  return 0;
}
void run_hash_sm3_perf(void)
{
  uint64_t start_time = 0;
  uint64_t end_time = 0;
  uint64_t transfer_time_usec = 0;
//int i ;
	unsigned char message[1048576]={0};

        shell_msg( "sm3 perf start\n");
   start_time = get_cntp_ct_el0();
//for(i=0;i<100;i++)
	run_hash_smx_smmu(0,message,1048576);
   end_time = get_cntp_ct_el0();
   transfer_time_usec = (end_time - start_time) / (0x01312D00/1000000UL);

   shell_msg("transfer_time_usec = %lld  \r\n",transfer_time_usec);

        shell_msg( "sm3 perf end\n");

}
