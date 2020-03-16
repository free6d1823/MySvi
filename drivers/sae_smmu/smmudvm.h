#ifndef __SMMUDVM__
#define __SMMUDVM__


int run_hash_smx_smmu(int dev_sel,unsigned char* message,int msg_len);

int run_cipher_smx_smmu(int key_flag,int dev_sel);

void smmu_initialize(uint64_t ste_base,uint64_t ste_size,uint64_t queue_base,uint64_t queue_size,uint64_t cd_base,uint64_t cd_size);

void smmu_switch_tables(uint64_t pt_base);

void configure_smmu_for_dvm(void);

void run_hash_sm3_perf(void);
#endif
