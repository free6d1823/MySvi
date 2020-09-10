/*
 * keygen_test.c
 *
 *  Created on: 2020Äê8ÔÂ12ÈÕ
 *      Author: mingfei.wu
 */
#include "keygen.h"
#include "keygen_hw.h"
#include "target/cmdline.h"
#include <stdio.h>
#include <string.h>

int done_irq_flag = 0;
int err_irg_flag = 0;

int kdf_reg_access_test()
{
	int val = 0;
	int ret = 0;

	keygen_init();
	WRITE_REG(KEYGEN_REG_CTRL, 0x0c);
	val = READ_REG(KEYGEN_REG_CTRL);
	if(0x0c != val) {
		ret = -1;
		printf("REG_CTRL read&write test fail \n ");
	}
	WRITE_REG(KEYGEN_REG_CTRL, 0x0);

	WRITE_REG(KEYGEN_REG_LABEL, 0x12345678);
	val = READ_REG(KEYGEN_REG_LABEL);
	if(0x12345678 != val) {
		ret = -1;
		printf("REG_LABEL read&write test fail \n ");
	}
	WRITE_REG(KEYGEN_REG_LABEL, 0x0);

	WRITE_REG(KEYGEN_REG_COUNTER, 0x56784321);
	val = READ_REG(KEYGEN_REG_COUNTER);
	if(0x56784321 != val) {
		ret = -1;
		printf("REG_COUNTER read&write test fail \n ");
	}
	WRITE_REG(KEYGEN_REG_COUNTER, 0x0);

	WRITE_REG(KEYGEN_REG_INT_EN, 0x03);
	val = READ_REG(KEYGEN_REG_INT_EN);
	if(0x03 != val) {
		ret = -1;
		printf("REG_INT_EN read&write test fail \n ");
	}
	WRITE_REG(KEYGEN_REG_INT_EN, 0x0);
	keygen_reset();

	return ret;
}

int kdf_init_test()
{
	int ret = 0;

	ret = keygen_init();
	keygen_reset();

	return ret;
}

int kdf_key_test()
{
	int ret = 0;
        unsigned int val = 0;

	ret = keygen_init();
	if(0 != ret) {
		return ret;
	}
	keygen_config(0x01234566, 0x89abcdef);
	val = READ_REG(KEYGEN_REG_COUNTER);
        printf("before gen key counter=0x%x \n", val);
	ret = keygen_generate_key(domain_ns, seed_key0);
	if(0 != ret) {
		printf("generate key error, ret=%d \n", ret);
		return ret;
	}
	val = READ_REG(KEYGEN_REG_COUNTER);
        printf("after counter=0x%x \n", val);
	keygen_reset();

	return ret;
}

int kdf_key_test_no_config(domain_type domain)
{
        int ret = 0;
        unsigned int val = 0;

        ret = keygen_init();
        if(0 != ret) {
                return ret;
        }
        ret = keygen_generate_key(domain, seed_key0);
        if(0 != ret) {
                printf("generate key error, ret=%d \n", ret);
                return ret;
        }
	val = READ_REG(KEYGEN_REG_COUNTER);
        printf("counter=0x%x \n", val);
        keygen_reset();

        return ret;
}

int kdf_done_irq_test(domain_type domain)
{
	int ret = 0;

	ret = keygen_init();
	if(0 != ret) {
		return ret;
	}
	kdf_enable_done_irq();
	keygen_generate_key(domain, seed_key0);
	keygen_reset();

	return 0;
}

int kdf_err_irq_test(domain_type domain)
{
    int ret = 0;

    kdf_enable_err_irq();
    switch(domain) {
    case domain_sec:
    	ret = kdf_key_test(domain_smp);
        break;
    case domain_ns:
    	ret = kdf_key_test(domain_sec);
        break;
    case domain_smp:
    	ret = kdf_key_test(domain_sec);
        break;
    default:
        return ERR_DOMAIN;
    }

	return ret;
}
#if 0
static int kdf_test(int argc, char *argv[])
{
    int ret = 0;
    unsigned int kdf_base = 0;
    domain_type domain;
    static int init_irq = 0;
    printf("kdf test start! \n");
    if(argc < 3) {
        printf(" para number error\n");
        return -EUSAGE;
    }
    if(0 == init_irq) {
        kdf_irq_init();
        init_irq++;
    }

    if(!strcmp(argv[2],"smp")) {
    	domain = domain_smp;
        printf(" smp domain:%d\n", domain);
    } else if(!strcmp(argv[2],"sec")) {
    	domain = domain_sec;
        printf(" sec domain:%d\n", domain);
    } else if(!strcmp(argv[2],"ns")) {
    	domain = domain_ns;
        printf(" ns domain:%d\n", domain);
    } else {
    	printf("parameter error, domain should be 'smp','sec' or 'ns' \n");
    	return -1;
    }
    kdf_base = KEYGEN_BASE;
    printf(" kdf base:0x%x\n", kdf_base);
    ret = strcmp(argv[1],"base_test");
    if(!ret) {
        printf("base_test start\n");
        ret = kdf_reg_access_test();
        if(!ret) {
            printf("kdf_reg_access_test case pass! \n");
        } else {
            printf("kdf_reg_access_test case failed! \n");
        }

        ret = kdf_init_test();
        if(!ret) {
            printf("kdf_init_test case pass! \n");
        } else {
            printf("kdf_init_test case failed! \n");
        }

    }

    ret = strcmp(argv[1],"key_test");
    if(!ret) {
        printf("key_test start\n");
        ret = kdf_key_test(domain);
        if(!ret) {
            printf("kdf_key_test case pass! \n");
        } else {
            printf("kdf_key_test case failed! \n");
        }
    }

    ret = strcmp(argv[1],"key_test_auto_inc");
    if(!ret) {
        printf("key_test_auto_inc start\n");
        ret = kdf_key_test_no_config(domain);
        if(!ret) {
            printf("kdf_key_test_auto_inc case pass! \n");
        } else {
            printf("kdf_key_test_auto_inc case failed! \n");
        }
    }

    ret = strcmp(argv[1],"interrupt_test");
    if(!ret) {
        printf("interrupt_test start\n");
        kdf_done_irq_test(domain);
        if(done_irq_flag) {
        	done_irq_flag = 0;
            printf("kdf_done_irq_test case pass! \n");
        } else {
            printf("kdf_done_irq_test case failed! \n");
        }
        kdf_err_irq_test(domain);
        if(err_irg_flag) {
        	err_irg_flag = 0;
            printf("kdf_err_irq_test case pass! \n");
        } else {
            printf("kdf_err_irq_test case failed! \n");
        }
    }

    printf("kdf test end! \n");

    return ret;
}

MK_CMD(kdf, kdf_test, "kdf test command",
        "kdf xxx_test domain: domain should be 'smp','sec'or'ns'\n"
        "       - base_test domain: kdf register access and init test \n"
        "       - key_test domain: test kdf key generate \n"
        "       - key_test_auto_inc domain: test kdf key generate,counter auto incrence \n"
        "       - interrupt_test domain: test kdf interrupt generate \n"
);
#endif
