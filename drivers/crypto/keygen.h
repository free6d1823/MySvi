/*
 * keygen.h
 *
 *  Created on: 2020Äê8ÔÂ12ÈÕ
 *      Author: mingfei.wu
 */

#ifndef KEYGEN_H_
#define KEYGEN_H_

#define WRITE_REG(addr, value) (*(volatile unsigned int *)(addr) = value)
#define READ_REG(addr) (*(volatile unsigned int *)(addr))
#define KDF_RETRY_MAX 1000000UL

#define KDF_TIMEOUT -0x11
#define ERR_DOMAIN -0x12
#define ERROR_SEED_SEL -0x13

typedef enum kdf_key_type {
        domain_sec = 0,
		domain_ns,
		domain_smp
} domain_type;

typedef enum kdf_seed_sel {
        seed_key0 = 0,
		seed_key1
} kdf_seed_sel;

int keygen_init();
int keygen_reset();
int keygen_clear_key(domain_type domain);
int keygen_config(unsigned int counter, unsigned int label);
int keygen_generate_key(domain_type domain, kdf_seed_sel seed_sel);
int kdf_key_test();
void kdf_enable_all_irq();
void kdf_disable_all_irq();
void kdf_enable_done_irq();
void kdf_disable_done_irq();
void kdf_enable_err_irq();
void kdf_disable_err_irq();
void kdf_irq_init();


#endif /* KEYGEN_H_ */
