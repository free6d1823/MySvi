/*
 * keygen.c
 *
 *  Created on: 2020Äê8ÔÂ12ÈÕ
 *      Author: mingfei.wu
 */

#include <stdio.h>
#include <target/keygen_hw.h>
#include <target/keygen.h>
#include <target/irq.h>
#include <target/irqc.h>

int keygen_init()
{
	int ret = 0;
	unsigned int val = 0;
	/* vf_free */
	val = READ_REG(KEYGEN_REG_VF_FREE);
	if(val == 1) {
		/*VF ALLOC*/
		printf("vf free! \n");
		WRITE_REG(KEYGEN_REG_VF_ALLOC, 1);
		val = READ_REG(KEYGEN_REG_VF_ALLOC);
		if(val == 1) {
			printf("security attribute consistent!\n");
			ret = 0;
		} else {
			printf("security attribute not consistent!\n");
			ret = -1;
		}
	}
	return ret;
}

int keygen_reset()
{
	WRITE_REG(KEYGEN_REG_VF_FREE, 1);
//	WRITE_REG(KEYGEN_REG_SOFTRST, 1);

	return 0;
}

int keygen_clear_key(domain_type domain)
{
	int ret = 0;

    switch(domain) {
    case domain_sec:
    	WRITE_REG(KEYGEN_REG_STAT_SEC, 1);
        break;
    case domain_ns:
    	WRITE_REG(KEYGEN_REG_STAT_NS, 1);
        break;
    case domain_smp:
    	WRITE_REG(KEYGEN_REG_STAT_SMP, 1);
        break;

    default:
        ret = ERR_DOMAIN;
    }

	return ret;
}

int keygen_config(unsigned int counter, unsigned int label)
{
	WRITE_REG(KEYGEN_REG_LABEL, label);
	WRITE_REG(KEYGEN_REG_COUNTER, counter);

	return 0;
}

static int wait_on_done()
{
    unsigned int tmp;
    unsigned int t;
    unsigned int int_raw;

    t = KDF_RETRY_MAX;
    do {
        tmp = READ_REG(KEYGEN_REG_CTRL);
    } while((tmp & KEYGEN_REG_CTRL_GO) && --t);

    if(t) {
	WRITE_REG(KEYGEN_REG_INT_CLR, KEYGEN_REG_INT_DONE);
        return 0;
    } else {
        return KDF_TIMEOUT;
    }
}

int keygen_generate_key(domain_type domain, kdf_seed_sel seed_sel)
{
	unsigned int val = 0;

    switch(domain) {
    case domain_sec:
    	val = KEYGEN_REG_CTRL_SEC_KEY;
        break;
    case domain_ns:
    	val = KEYGEN_REG_CTRL_NS_KEY;
        break;
    case domain_smp:
    	val = KEYGEN_REG_CTRL_SMP_KEY;
        break;
    default:
        return ERR_DOMAIN;
    }

    if(seed_key0 == seed_sel) {
    	val |= KEYGEN_REG_CTRL_SEED_KEY0;
    } else if(seed_key1 == seed_sel) {
    	val |= KEYGEN_REG_CTRL_SEED_KEY1;
    } else {
    	return ERROR_SEED_SEL;
    }
    val |= KEYGEN_REG_CTRL_GO;
    WRITE_REG(KEYGEN_REG_CTRL, val);

    return wait_on_done();
}

void kdf_enable_all_irq()
{
	WRITE_REG(KEYGEN_REG_INT_EN, 0xffffffff);
}

void kdf_disable_all_irq()
{
	WRITE_REG(KEYGEN_REG_INT_EN, 0x0);
}

void kdf_enable_done_irq()
{
	unsigned int val = 0;

	val = READ_REG(KEYGEN_REG_INT_EN);
	val |= KEYGEN_REG_INT_DONE_EN;
	WRITE_REG(KEYGEN_REG_INT_EN, val);
}

void kdf_disable_done_irq()
{
	unsigned int val = 0;

	val = READ_REG(KEYGEN_REG_INT_EN);
	val &= ~KEYGEN_REG_INT_DONE_EN;
	WRITE_REG(KEYGEN_REG_INT_EN, val);
}

static void kdf_clear_done_irq()
{
	WRITE_REG(KEYGEN_REG_INT_CLR, KEYGEN_REG_INT_DONE);
}

void kdf_enable_err_irq()
{
	unsigned int val = 0;

	val = READ_REG(KEYGEN_REG_INT_EN);
	val |= KEYGEN_REG_INT_ERR_EN;
	WRITE_REG(KEYGEN_REG_INT_EN, val);
}

void kdf_disable_err_irq()
{
	unsigned int val = 0;

	val = READ_REG(KEYGEN_REG_INT_EN);
	val &= ~KEYGEN_REG_INT_ERR_EN;
	WRITE_REG(KEYGEN_REG_INT_EN, val);
}

static void kdf_clear_err_irq()
{
	WRITE_REG(KEYGEN_REG_INT_CLR, KEYGEN_REG_INT_ERR);
}

extern int done_irq_flag;
extern int err_irg_flag;

static void kdf_irq_process()
{
    unsigned int val = 0;

    val = READ_REG(KEYGEN_REG_INT_STAT);

    if(0 == val) {
        printf("no interrupt occur\n");
        return;
    }
    if(val & KEYGEN_REG_INT_DONE) {
        printf("INT_DONE interrupt \n");
        done_irq_flag = 1;
        kdf_clear_done_irq();
        kdf_disable_done_irq();
        return;
    }
    if(val & KEYGEN_REG_INT_ERR) {
        printf("INT_ERR interrupt \n");
        err_irg_flag = 1;
        kdf_clear_err_irq();
        kdf_disable_err_irq();
        return;
    }
}


static void kdf_irq_handle(irq_t irq, void *ctx)
{
//    irq_t kdf_irq = KDF_IRQ;
    printf("enter into kdf irq handle! \n");
    kdf_irq_process();
}

void kdf_irq_init()
{
   /* irq_t kdf_ns_irq = KDF_NS_IRQ;
    irq_t kdf_sec_irq = KDF_SEC_IRQ;
    kdf_disable_all_irq();
    irqc_configure_irq(kdf_ns_irq, 32, IRQ_LEVEL_TRIGGERED);
    irqc_configure_irq(kdf_sec_irq, 32, IRQ_LEVEL_TRIGGERED);
    irq_register_vector(kdf_ns_irq, kdf_irq_handle, NULL);
    irq_register_vector(kdf_sec_irq, kdf_irq_handle, NULL);
    irqc_enable_irq(kdf_ns_irq);
    irqc_enable_irq(kdf_sec_irq);*/
//    kdf_enable_all_irq();
}

