#include <string.h>
#include <target/cmdline.h>
#include <asm/sysreg.h>
#include <stdio.h>


#define FIELD_OP(x, shift, mask) ((uint32_t)((x >> shift) & mask))

#define CLIDR_FIELD_OP(shift) FIELD_OP(clidr, shift, 0x7)

#define CCSIDR_NumSets FIELD_OP(ccsidr, 13, 0x7fff)
#define CCSIDR_Associativity FIELD_OP(ccsidr, 3, 0x3ff)
#define CCSIDR_LineSize FIELD_OP(ccsidr, 0, 0x7)

static const char* Ctype[] = {
		"No cache",
		"Instruction cache only",
		"Data cache only",
		"Separate instruction and data caches",
		"Unified cache",
		"",
		"",
		"",
	};

#define Ctype_Instruction() (ctype & 0x1)
#define Ctype_Data() (ctype & 0x6)

/* CLIDR_EL1 */
#define ICB   30
#define LoUU  27
#define LoC   24
#define LoUIS 21

/* CTR_EL0 */
#define DIC   29
#define IDC   28
#define CWG   24
#define ERG   20
#define DminLine 16
#define L1Ip  14
#define IminLine 0

#define CTR_CWG FIELD_OP(ctr, CWG, 0xf)
#define CTR_ERG FIELD_OP(ctr, ERG, 0xf)
#define CTR_DminLine FIELD_OP(ctr, DminLine, 0xf)
#define CTR_L1Ip FIELD_OP(ctr, L1Ip, 0x3)
#define CTR_IminLine FIELD_OP(ctr, IminLine, 0xf)

static const char* L1Ip_s[] = {
		"VPIPT",
		"AIVIVT",
		"VIPT",
		"PIPT",
	};

static int dump_ccsidr()
{
	uint32_t ccsidr = read_sysreg(ccsidr_el1);
	printf("  NumSets %d Associativity %d LineSize %d\n",
			CCSIDR_NumSets + 1, CCSIDR_Associativity + 1, 1 << (CCSIDR_LineSize + 4));
	return 0;
}

int cmd_cacheinfo(int argc, char **argv)
{
	uint64_t clidr;
	uint32_t loc;
	uint32_t ctype;
	uint32_t ctr;
	int i;

	clidr = read_sysreg(clidr_el1);
	loc = CLIDR_FIELD_OP(LoC);

	printf("CLIDR ICB: %d LoUU %d LoC: %d LoUIS: %d\n",
			CLIDR_FIELD_OP(ICB), CLIDR_FIELD_OP(LoUU),
			CLIDR_FIELD_OP(LoC), CLIDR_FIELD_OP(LoUIS));

	for (i = 0; i < loc; i++) {
		ctype = CLIDR_FIELD_OP(i * 3);
		printf("Ctype%d: %s\n", i + 1, Ctype[ctype]);

		/* CSSELR_EL1 Level InD *
		 *     bit    3 2 1  0  */
		if (Ctype_Instruction()) {
			write_sysreg((i << 1) + 1, csselr_el1);
			dump_ccsidr();
		}

		if (Ctype_Data()) {
			write_sysreg((i << 1), csselr_el1);
			dump_ccsidr();
		}
	}

	ctr = read_sysreg(CTR_EL0);
	printf("Cache Type DIC: %d IDC: %d\n", !!(ctr & DIC), !!(ctr & IDC));
	printf("  Cache writeback granule: %d\n", 1 << (CTR_CWG + 2));
	printf("  Exclusives reservation granule: %d\n", 1 << (CTR_ERG + 2));
	printf("  DminLine: %d IminLine: %d\n", 1 << (CTR_DminLine + 2), 1 << (CTR_IminLine + 2));
	printf("  I-cache is %s\n", L1Ip_s[CTR_L1Ip]);

	return 0;
}

MK_CMD(cacheinfo, cmd_cacheinfo, "Dump the information of cache",
	NULL
);
