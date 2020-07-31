#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "target/crypto_ips.h"
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
#ifdef SVI_Z1
static int se_ips_general(int argc, char *argv[])
#endif
#ifdef SVI_VCS
int se_ips_general()
#endif
{
	int ret;
	int i;

	ret = ips_init_clk();
	if(!ret)
		printf("ips module clock case pass! \n");
	ret = ips_module_reset();
	if(!ret)
		printf("ips module reset case pass! \n");
        /*************************sha1 alg***********************************************/
	ret = strcmp(argv[1],"basic_reg");
	if(!ret){
		   ips_vfreg_read_write_test();
		}
	return 0;
}
#ifdef SVI_Z1
MK_CMD(ips, se_ips_general, "Test crypto_acc general function",
	"ips general  mode\n"
	"	- basic_reg test ips general register read and write!\n"
);
#endif
