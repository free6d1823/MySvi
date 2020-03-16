#include <stdio.h>
#include <testos/cmdline.h>
#include <arch/mach-qdf2400/imem.h>

QDF2400_IMEM(sys_imem, SYS_IMEM);
QDF2400_IMEM(msg_imem, MSG_IMEM);
QDF2400_IMEM(ram0_imem, RAM_0_IMEM);
QDF2400_IMEM(ram1_imem, RAM_1_IMEM);
QDF2400_IMEM(ram2_imem, RAM_2_IMEM);
QDF2400_IMEM(ram3_imem, RAM_3_IMEM);
QDF2400_IMEM(ram4_imem, RAM_4_IMEM);
QDF2400_IMEM(ram5_imem, RAM_0_IMEM);

char *imem_type_strings[IMEM_TYPE_NUM] = {
	"RAM_0_IMEM",
	"RAM_1_IMEM",
	"RAM_2_IMEM",
	"RAM_3_IMEM",
	"RAM_4_IMEM",
	"RAM_5_IMEM",
	"SYS_IMEM",
	"MSG_IMEM",
};

char *imem_syndrome_strings[IMEM_SYNDROME_NUM] = {
	"NO_ERR",
	"ECC_CE_READ",
	"ECC_UE_READ",
	"ECC_POISON_READ",
	"ECC_CE_WRITE",
	"ECC_UE_WRITE",
	"ECC_POISON_WRITE",
	"ECC_CE_SCRUB",
	"ECC_UE_SCRUB",
	"ECC_POISION_SCRUB",
};

void imem_print_err(struct imem_err *err)
{
	printf("%s %016llx %s\n",
	       err->imem_type < IMEM_TYPE_NUM ?
	       imem_type_strings[err->imem_type] : "UNKNOWN",
	       err->address,
	       err->syndrome < IMEM_SYNDROME_NUM ?
	       imem_syndrome_strings[err->syndrome] : "UNKNOWN");
}

int imem_init(void)
{
	ram0_imem_init();
	ram1_imem_init();
	ram2_imem_init();
	ram3_imem_init();
	ram4_imem_init();
	ram5_imem_init();
	sys_imem_init();
	msg_imem_init();
	return 0;
}
