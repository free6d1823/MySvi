#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_smx.h"
#include "target/cmdline.h"
#include "target/heap.h"
#include "target/mbedtls/config.h"
#include "target/mbedtls/platform.h"
#include "target/mbedtls/aes.h"
#include "target/mbedtls/md.h"
#include "target/mbedtls/platform_util.h"
#include "target/mbedtls/sha1.h"
#include "target/mbedtls/sha256.h"
#include "target/mbedtls/sha512.h"
#include "target/mbedtls/gcm.h"
#include "target/mbedtls/cipher.h"
//#define DEBUG_PRINT
int se_smx_general()
{
	int ret;
	int i;
	ret = smx_init_clk();
	if(!ret)
		printf("smx module clock case pass! \n");
	else
		return -1;
	ret = smx_module_reset();
	if(!ret)
		printf("smx module reset case pass! \n");
	else
		return -1;
	for(i=0; i<4; i++)
	{
		ret = smx_vfreg_read_write_test(i);
		if(ret == -1)
                {

                        printf("vf%d read&write case failed!\n",i);
                        break;
                }
                else
                        printf("vf%d read&write case pass!\n",i);

	}
	return ret;
}
