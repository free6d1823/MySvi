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
static int se_smx_general(int argc, char *argv[])
{
	int ret;
	int i;

	ret = smx_init_clk();
	if(!ret)
		printf("smx module clock case pass! \n");
	ret = smx_module_reset();
	if(!ret)
		printf("smx module reset case pass! \n");
        /*************************sha1 alg***********************************************/
	ret = strcmp(argv[1],"basic_reg");
	if(!ret){
		   smx_vfreg_read_write_test();
		}
	return 0;
}
MK_CMD(smx, se_smx_general, "Test crypto_smx general function",
	"smx general  mode\n"
	"	- basic_reg test smx general register read and write!\n"
);
