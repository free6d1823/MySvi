/**
* @file trng.c
* @brief TRNG Library Source File.
*
* All Rights Reserved.
*/

/*=========================================================================
      Include Files
==========================================================================*/
#include "string.h"
#include "stdlib.h"
#include "hdts_shell.h"
#include "asm/hal/HALhwio.h"
#include "trng.h"

unsigned int max_reads = 128;


unsigned long RandomDataArrange;
uint32_t RandomDataBuf[81920];

elpclp890_state g_state;

int elpclp890_self_test(void);

void set_dump_data(void)
{
	return;
}


/* ============================================================================
**  Function : trng_init
** ============================================================================
*/
int sdk_trng_init(int dev_sel)
{

   int ret = -1;
   unsigned long base_addr = 0;
   int t = CLP890_RETRY_MAX;

   DEBUG("TRNG Init begin!\r\n");

   if(dev_sel==0){
	   base_addr = CRYPTO_TOP_BASE0;
   }
   else{
	   base_addr = CRYPTO_TOP_BASE1;
   }
   g_state.base = base_addr+TRNG_ADDRESS_OFF;

   //enale clk
   pdu_io_write(base_addr+CE_TRNG_CLK_OFF,0x01);

   /*waiting for STAT bit busy to clear */
   while((pdu_io_read(base_addr+TRNG_STAT_OFF) & CLP890_REG_STAT_BUSY) && (t>0)){
       t--;
   }

   if(!t){
      ELPHW_PRINT("CLP890 hw self checking failed (%d)\r\n", ret);
      return ret;
   }

   if ( (ret = elpclp890_init(g_state.base)) != 0) {
      ELPHW_PRINT("CLP890 init failed (%d)\r\n", ret);
      return ret;
   }

   /* if max_reads is not 0, change the max_req_per_seed according to max_reads */
   if (max_reads) {
      if ( (ret = elpclp890_set_reminder_max_req_per_seed(g_state, max_reads)) != 0) {
         ELPHW_PRINT("CLP890 maximum request-per-seed setup failed (%d)\r\n", ret);
         return ret;
      }
   }

   // issue quick self test
   ret = elpclp890_self_test();
   if (ret) {
      return ret;
   }

   // ready the device for use
   ret = elpclp890_instantiate(g_state, 256, 1, NULL);
   if (ret) {
      ELPHW_PRINT("CLP890 instantiate failed (%d)\r\n", ret);
      return ret;
   }

   return HDTS_SUCCESS;
}

/* ============================================================================
**  Function : sdk_trng_kat
**  dev_sel:0-CE0,1-CE1
**  nonce_operation:0-false,1-true
**  sec_length:0-AES128,1-AES256
** ============================================================================
*/
int sdk_trng_kat(int dev_sel,int nonce_operation,int sec_length,int pre_resist)
{
	uint32_t seed[48] = {0};
	uint32_t add_str[48] = {0};
        uint32_t ps_str[48] = {0};
        uint32_t out[4] = {0};
        uint32_t x = 0;

	uint32_t exp128[4] = { 0x5db79bb2, 0xc3a0df1e, 0x099482b6,	0xc319981e },
			 exp128_nonce[4] = { 0xa354907c, 0xd5d066e8, 0x6495a7a7, 0x145e6005 },
			 exp256[4] = { 0x1f1a1441, 0xa0865ece, 0x9ff8d5b9, 0x3f78ace6 },
			 exp256_nonce[4] = { 0xeaaf4c97, 0x2ac4b4ab, 0xdfa6b556, 0x505e519b };

	uint32_t exp128_pre[4] = { 0x25063a56, 0x2a085eb5, 0x3dc58c8b,	0x83337f31 },
			 exp128_nonce_pre[4] = { 0x4b144cd4, 0x312630bb, 0x8ed8f17c, 0x2dd9c0ce },
			 exp256_pre[4] = { 0x85284c88, 0x5dff3c99, 0x4aac37d5, 0x7202cc93 },
			 exp256_nonce_pre[4] = { 0x70880ad9, 0xba145fb1, 0xaa5d5926, 0x5b3552c7 };

	int t = CLP890_RETRY_MAX;
	unsigned long base_addr = 0;
	int ret = -1;
	//int exp[4];

	if(dev_sel==0){
		base_addr=  CRYPTO_TOP_BASE0;
	}
	else{
		base_addr = CRYPTO_TOP_BASE1;
	}
	g_state.base = base_addr + TRNG_ADDRESS_OFF;

	//enale clk
	pdu_io_write(base_addr + CE_TRNG_CLK_OFF,0x01);

	/*waiting for STAT bit busy to clear */
	while((pdu_io_read(base_addr+TRNG_STAT_OFF) & CLP890_REG_STAT_BUSY) && (t>0)){
	     t--;
	}

	if(!t){
	    ELPHW_PRINT("CLP890 hw self checking failed (%d)\r\n", ret);
	    return ret;
	}

	if ( elpclp890_init(g_state.base) != 0) {
	     ELPHW_PRINT("CLP890 init failed (%d)\r\n", ret);
	     return ret;
	}

	   /* if max_reads is not 0, change the max_req_per_seed according to max_reads */
	if (max_reads) {
	     if ( elpclp890_set_reminder_max_req_per_seed(g_state, max_reads) != 0) {
	        ELPHW_PRINT("CLP890 maximum request-per-seed setup failed (%d)\r\n", ret);
	        return ret;
	     }
	}
	for (x = 0; x < 48; x++) seed[x] = 0x12345679 * (x + 1);
	for (x = 0; x < 48; x++) ps_str[x] = 0x12345689 * (x + 1);
	for (x = 0; x < 48; x++) add_str[x] = 0x12345789 * (x + 1);
	DEBUG("Doing a self-test with security strength of %d\r\n",sec_length);
	if ((ret = elpclp890_uninstantiate(g_state)) && (ret != CRYPTO_NOT_INSTANTIATED)) { goto ERR; }
	if ((ret = elpclp890_set_nonce_mode(g_state, 1)))                                 { goto ERR; }
	if ((ret = elpclp890_set_sec_strength(g_state, sec_length)))                      { goto ERR; }
	if ((ret = elpclp890_get_entropy_input(g_state, seed, nonce_operation)))          { goto ERR; }


	if(!pre_resist){
		if ((ret = elpclp890_instantiate(g_state, sec_length, 0, NULL)))                         { goto ERR; }
		if ((ret = elpclp890_generate(g_state, out, 16, sec_length, 0, NULL,true)))              { goto ERR; }
		DEBUG("clp890: AES-%d Self-test output: ",sec_length);
		for (x = 0; x < 4; x++) { DEBUG("0x%08lx ", (unsigned long)out[x]); }

		if (nonce_operation==0 && sec_length == 128){
			t = memcmp(out, exp128, sizeof exp128);
		}
		else if (nonce_operation==0 && sec_length == 256){
			t = memcmp(out, exp256, sizeof exp256);
		}
		else if (nonce_operation==1 && sec_length == 128){
			t = memcmp(out, exp128_nonce, sizeof exp128_nonce);
		}
		else if (nonce_operation==1 && sec_length == 256){
			t = memcmp(out, exp256_nonce, sizeof exp256_nonce);
		}
		else{
			ELPHW_PRINT("...  AES length error \r\n");
			return ret;
		}
	}
	else{
		if ((ret = elpclp890_instantiate(g_state, sec_length, pre_resist, ps_str)))                         { goto ERR; }
		if ((ret = elpclp890_generate(g_state, out, 16, sec_length, pre_resist, add_str,true)))             { goto ERR; }
		DEBUG("clp890: AES-%d Self-test output: ",sec_length);
		for (x = 0; x < 4; x++) { DEBUG("0x%08lx ", (unsigned long)out[x]); }

		if (nonce_operation==0 && sec_length == 128){
			t = memcmp(out, exp128_pre, sizeof exp128_pre);
		}
		else if (nonce_operation==0 && sec_length == 256){
			t = memcmp(out, exp256_pre, sizeof exp256_pre);
		}
		else if (nonce_operation==1 && sec_length == 128){
			t = memcmp(out, exp128_nonce_pre, sizeof exp128_nonce_pre);
		}
		else if (nonce_operation==1 && sec_length == 256){
			t = memcmp(out, exp256_nonce_pre, sizeof exp256_nonce_pre);
		}
		else{
			ELPHW_PRINT("...  AES length error \r\n");
			return ret;
		}
	}

	if(t) {
		ELPHW_PRINT("...  FAILED comparisonr\r\n");
		ret = -1;
		goto ERR;
	}
	else  {DEBUG("...  PASSED\r\n");}

	/* back to the noise mode */
	if ((ret = elpclp890_set_nonce_mode(g_state, 0)))		{ goto ERR; }

	if ((ret = elpclp890_zeroize(g_state)))		{ goto ERR; }

	return HDTS_SUCCESS;
ERR:
	return ret;
}

/* ============================================================================
**  Function : sdk_trng_generate
** ============================================================================
*/
int sdk_trng_generate(unsigned long req_num_bytes,boolean load_flag)
{
   int ret = 0;
   memset(RandomDataBuf,0,sizeof(RandomDataBuf));
   ret = elpclp890_generate(g_state,RandomDataBuf, req_num_bytes, g_state.status.sec_strength ? 256 : 128, g_state.status.pred_resist,NULL,load_flag);
   DEBUG("TRNG Generate end!  \r\n");
   if(load_flag)set_dump_data();
   return ret;
}

/* ============================================================================
**  Function : sdk_get_entropy
** ============================================================================
*/
int sdk_get_entropy(unsigned long req_num_bytes,boolean load_flag)
{
   int ret = 0;
   ret = elpclp890_entropy(g_state,RandomDataBuf, req_num_bytes);
   ELPHW_PRINT("ELP CLP890 ENTROPY DONE \r\n");
   if(load_flag) set_dump_data();
   return ret;
}

/* ============================================================================
**  Function : elpclp890_self_test
** ============================================================================
*/
int elpclp890_self_test(void)
{
   uint32_t seed[16] = {0};
   uint32_t out[4] = {0};
   uint32_t x = 0;
   static const uint32_t exp128[4] = { 0x5db79bb2, 0xc3a0df1e, 0x099482b6,
			0xc319981e },
                         exp256[4] = {0x1f1a1441, 0xa0865ece, 0x9ff8d5b9, 0x3f78ace6};
   int ret=0;

   for (x = 0; x < 16; x++) seed[x] = 0x12345679 * (x + 1);

   DEBUG("Doing a self-test with security strength of 128\r\n");
   if ((ret = elpclp890_uninstantiate(g_state)) && (ret != CRYPTO_NOT_INSTANTIATED)) { goto ERR; }
   if ((ret = elpclp890_set_nonce_mode(g_state, 1)))                                 { goto ERR; }
   if ((ret = elpclp890_set_sec_strength(g_state, 128)))                             { goto ERR; }
   if ((ret = elpclp890_get_entropy_input(g_state, seed, 0)))                        { goto ERR; }
   if ((ret = elpclp890_instantiate(g_state, 128, 0, NULL)))                         { goto ERR; }
   if ((ret = elpclp890_generate(g_state, out, 16, 128, 0, NULL,true)))                    { goto ERR; }
   DEBUG("clp890: AES-128 Self-test output: ");
   for (x = 0; x < 4; x++) { DEBUG("0x%08lx ", (unsigned long)out[x]); }

   if (memcmp(out, exp128, sizeof exp128)) {
      ELPHW_PRINT("...  FAILED comparison\r\n");
      ret = -1;
      goto ERR;
   } else {
      DEBUG("...  PASSED\r\n");
   }

   if (g_state.config.features.drbg_arch == AES256) {
   // test AES-256 mode
   DEBUG("Doing a self-test with security strength of 256\n");
   if ((ret = elpclp890_uninstantiate(g_state)) && (ret != CRYPTO_NOT_INSTANTIATED)) { goto ERR; }
   if ((ret = elpclp890_set_nonce_mode(g_state, 1)))                                 { goto ERR; }
   if ((ret = elpclp890_set_sec_strength(g_state, 256)))                             { goto ERR; }
   if ((ret = elpclp890_get_entropy_input(g_state, seed, 0)))                        { goto ERR; }
   if ((ret = elpclp890_instantiate(g_state, 256, 0, NULL)))                         { goto ERR; }
   if ((ret = elpclp890_generate(g_state, out, 16, 256, 0, NULL,true)))                    { goto ERR; }
      DEBUG("clp890: AES-256 Self-test output: ");
      for (x = 0; x < 4; x++) { DEBUG("0x%08lx ", (unsigned long)out[x]); }
      if (memcmp(out, exp256, sizeof exp256)) {
         ELPHW_PRINT("...  FAILED comparisonr\r\n");
         ret = -1;
         goto ERR;
      } else {
         DEBUG("...  PASSED\r\n");
      }
   }

   /* back to the noise mode */
   if ((ret = elpclp890_set_nonce_mode(g_state, 0)))                                 { goto ERR; }

   if ((ret = elpclp890_zeroize(g_state))) { goto ERR; }
ERR:
   return ret;
}

/* ============================================================================
**  Function : pdu_io_read
** ============================================================================
*/
/* read a 32-bit word from a given address */
unsigned long pdu_io_read (unsigned long addr)
{
   unsigned long foo = 0;

   //foo = *((volatile unsigned int*)addr);
   foo = in_dword(addr);
   //if (debug_on) {
      ELPHW_PRINT("PDU: read  %.8lx <- %p\r\n", foo, addr);
   //}
   return foo;
}

/* ============================================================================
**  Function : pdu_io_write
** ============================================================================
*/
/* write a 32-bit word to a given address */
void pdu_io_write(unsigned long addr, unsigned long val)
{
   //if (addr == NULL) {
      //debug_on ^= 1;
      //return;
   //}
   out_dword(addr,val);
   //if (debug_on) {
      ELPHW_PRINT("PDU: write %.8lx -> %p \r\n", val, addr);
   //}

    //*((volatile unsigned int *)addr) = val;
}


