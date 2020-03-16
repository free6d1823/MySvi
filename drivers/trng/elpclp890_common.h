// ------------------------------------------------------------------------
//
//                (C) COPYRIGHT 2012 - 2016 SYNOPSYS, INC.
//                          ALL RIGHTS RESERVED
//
//  (C) COPYRIGHT 2012-2016 Synopsys, Inc. 
//  This Synopsys software and all associated documentation are 
//  proprietary to Synopsys, Inc. and may only be used pursuant 
//  to the terms and conditions of a written license agreement 
//  with Synopsys, Inc. All other use, reproduction, modification, 
//  or distribution of the Synopsys software or the associated 
//  documentation is strictly prohibited.
//
// ------------------------------------------------------------------------

#ifndef ELPCLP890_COMMON_H
#define ELPCLP890_COMMON_H

//#include "../include/elppdu.h"
#include "trng.h"
#include "hdts_shell.h"
#include "asm/hal/HALhwio.h"

#define CLP890_RETRY_MAX 5000000UL

#define CLP890_DFLT_MAX_BITS_PER_REQ (1UL<<24)
#define CLP890_DFLT_MAX_REQ_PER_SEED (1ULL<<48)

/* Do not change the following parameters */
#define CLP890_DFLT_MAX_REJECTS 10

#define CRYPTO_OK                      (   0)
#define CRYPTO_FAILED                  (  -1)
#define CRYPTO_INPROGRESS              (  -2)
#define CRYPTO_INVALID_HANDLE          (  -3)
#define CRYPTO_INVALID_CONTEXT         (  -4)
#define CRYPTO_INVALID_SIZE            (  -5)
#define CRYPTO_NOT_INITIALIZED         (  -6)
#define CRYPTO_NO_MEM                  (  -7)
#define CRYPTO_INVALID_ALG             (  -8)
#define CRYPTO_INVALID_KEY_SIZE        (  -9)
#define CRYPTO_INVALID_ARGUMENT        ( -10)
#define CRYPTO_MODULE_DISABLED         ( -11)
#define CRYPTO_NOT_IMPLEMENTED         ( -12)
#define CRYPTO_INVALID_BLOCK_ALIGNMENT ( -13)
#define CRYPTO_INVALID_MODE            ( -14)
#define CRYPTO_INVALID_KEY             ( -15)
#define CRYPTO_AUTHENTICATION_FAILED   ( -16)
#define CRYPTO_INVALID_IV_SIZE         ( -17)
#define CRYPTO_MEMORY_ERROR            ( -18)
#define CRYPTO_LAST_ERROR              ( -19)
#define CRYPTO_HALTED                  ( -20)
#define CRYPTO_TIMEOUT                 ( -21)
#define CRYPTO_SRM_FAILED              ( -22)
#define CRYPTO_COMMON_ERROR_MAX        (-100)
#define CRYPTO_INVALID_ICV_KEY_SIZE    (-100)
#define CRYPTO_INVALID_PARAMETER_SIZE  (-101)
#define CRYPTO_SEQUENCE_OVERFLOW       (-102)
#define CRYPTO_DISABLED                (-103)
#define CRYPTO_INVALID_VERSION         (-104)
#define CRYPTO_FATAL                   (-105)
#define CRYPTO_INVALID_PAD             (-106)
#define CRYPTO_FIFO_FULL               (-107)
#define CRYPTO_INVALID_SEQUENCE        (-108)
#define CRYPTO_INVALID_FIRMWARE        (-109)
#define CRYPTO_NOT_FOUND               (-110)
#define CRYPTO_CMD_FIFO_INACTIVE       (-111)
#define CRYPTO_NOT_INSTANTIATED        (-114)
#define CRYPTO_RESEED_REQUIRED         (-115)

//#define DEBUG(...)
//#define DEBUG(...) printk(__VA_ARGS__)

typedef enum elpclp890_sec_strength {
   SEC_STRNT_AES128 = 0,
   SEC_STRNT_AES256 = 1
} elpclp890_sec_strength;

typedef enum elpclp890_drbg_arch {
   AES128 = 0,
   AES256 = 1
} elpclp890_drbg_arch;

typedef enum elpclp890_current_state {   
   CLP890_STATE_INITIALIZE = 0,
   CLP890_STATE_UNINSTANTIATE,
   CLP890_STATE_INSTANTIATE,
   CLP890_STATE_RESEED,
   CLP890_STATE_GENERATE
} elpclp890_current_state;

typedef struct {
   unsigned long base;

   /* Hardware features and build ID */
   struct {
      struct {
         elpclp890_drbg_arch drbg_arch;
         unsigned extra_ps_present,
                  secure_rst_state,
                  diag_level_trng3,
                  diag_level_stat_hlt,
                  diag_level_ns;
      } features;

      struct {
         unsigned stepping,
                  epn;
      } build_id;
   } config;

   /* status */
   struct {
      elpclp890_current_state current_state;
      unsigned nonce_mode,
               secure_mode,
               pred_resist;
      elpclp890_sec_strength sec_strength;
      unsigned pad_ps_addin;
      volatile unsigned alarm_code;
   } status;

   /* reminders and alarms */
   struct {
      unsigned long max_bits_per_req;
      unsigned long long max_req_per_seed;
      unsigned long bits_per_req_left;
      unsigned long long req_per_seed_left;
   } counters;
} elpclp890_state;

#define clp890_zero_status(x) memset(&(x->status), 0, sizeof (x->status))

#define DRBG_INSTANTIATED(cs) (((cs == CLP890_STATE_INSTANTIATE) || (cs == CLP890_STATE_RESEED) || (cs == CLP890_STATE_GENERATE)) ? 1 : 0)
#define REQ_SEC_STRENGTH_IS_VALID(sec_st) (((sec_st > 0) && (sec_st <= 256)) ? 1 : 0)

int elpclp890_init (unsigned long base);
int elpclp890_instantiate (elpclp890_state state, int req_sec_strength, int pred_resist, void *personal_str);
int elpclp890_uninstantiate (elpclp890_state state);
int elpclp890_reseed (elpclp890_state state, int pred_resist, void *addin_str);
int elpclp890_generate (elpclp890_state state, void *random_bits, unsigned long req_num_bytes, int req_sec_strength, int pred_resist, void *addin_str,boolean load_flag);
int elpclp890_entropy (elpclp890_state state, void *random_bits, unsigned long req_num_bytes);

int elpclp890_wait_on_busy (elpclp890_state state);
int elpclp890_wait_on_done (elpclp890_state state);
int elpclp890_get_alarms (elpclp890_state state);
int elpclp890_reset_state (elpclp890_state state);

/* ---------- Reminders ---------- */
int elpclp890_reset_counters (elpclp890_state state);
int elpclp890_set_reminder_max_bits_per_req (elpclp890_state state, unsigned long max_bits_per_req);
int elpclp890_set_reminder_max_req_per_seed (elpclp890_state state, unsigned long long max_req_per_seed);
int elpclp890_check_seed_lifetime (elpclp890_state state);

/* ---------- Set field APIs ---------- */
int elpclp890_set_sec_strength (elpclp890_state state, int req_sec_strength);
int elpclp890_set_addin_present (elpclp890_state state, int addin_present);
int elpclp890_set_pred_resist (elpclp890_state state, int pred_resist);
int elpclp890_set_secure_mode (elpclp890_state state, int secure_mode);
int elpclp890_set_nonce_mode (elpclp890_state state, int nonce_mode);

/* ---------- Load data APIs ---------- */
int elpclp890_load_ps_addin (elpclp890_state state, void *input_str);

/* ---------- Command APIs ---------- */
int elpclp890_get_entropy_input (elpclp890_state state, void *input_nonce, int nonce_operation);
int elpclp890_refresh_addin (elpclp890_state state, void *addin_str);
int elpclp890_gen_random (elpclp890_state state, void *random_bits, unsigned long req_num_bytes,boolean load_flag);
int elpclp890_advance_state (elpclp890_state state);
int elpclp890_kat (elpclp890_state state, int kat_sel, int kat_vec);
int elpclp890_full_kat (elpclp890_state state);
int elpclp890_zeroize (elpclp890_state state);

void DEBUG( char *format, ...);
void ELPHW_PRINT( char *format, ...);


#endif
