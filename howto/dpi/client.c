/*	 jtag udp client    */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
	uint32_t data;
	uint32_t len;
} drdata_t;

#define DAPIRPRE  0
#define DAPDRPRE  0
#define DAPIRLEN  4
#define DAPIRPOST 0
#define DAPDRPOST 0

/* IR instructions */
#define ABORT  0x8
#define DPACC  0xa
#define APACC  0xb
#define IDCODE 0xe

/* DP registers */
#define CTRLSTAT 0x4
#define SELECT 0x8
#define RDBUFF 0xC

#define RnW_W 0x0
#define RnW_R 0x1

#define ACK_OK     (1 << 2)
#define ACK_FAULT  (1 << 1)
#define ACK_WAIT   (1 << 0)

/* ARM CoreSight registers */
#define TAR  0x0D04
#define DRW  0x0D0C
#define BASE 0x0DF8

#define DEVARCH 0xFBC
#define DEVID 0xFCC

#define PIDR0 0xFE0
#define	PIDR1 0xFE4

#define CIDR0 0xFF0
#define CIDR1 0xFF4
#define CIDR2 0xFF8
#define CIDR3 0xFFC


#define DEVARCH_PRESENT (1 << 20)
#define DEVARCH_ARCHID(devarch) (devarch & 0xffff)

#define CIDR_CLASS(cidr1) ((cidr1 >> 4) & 0xf)

#define DEVID_FORMAT(devid) (devid & 0xf)

#define ROMENTRY_PRESENT(romentry) (romentry & 0x3)
#define ROMENTRY_OFFSET(romentry) (romentry & ~0xfff)

#define PIDR_PART(pidr0, pidr1) ((pidr0 & 0xff) | (pidr1 & 0xf) << 8)

static int enumeration(uint32_t base, int depth);


static int sockfd;
static struct sockaddr_in serverAddr;
static socklen_t addr_len = sizeof(serverAddr);

static uint32_t base2lvl;

#define BUFFER_LEN 1024

static int (*_ap_read)(uint32_t addr, uint32_t *d);
/* static int (*_ap_write)(uint32_t addr, uint32_t d); */


static int test_idcode()
{
	int ret, i;
	char buffer[BUFFER_LEN];
	unsigned int idcode;

	/* cmd is tms, tdi in bit format */
	char cmd[] = {2, 2, 2, 2, 2, 0, /* 6 Run-Test/ Idle */
	2, 2, 0, 0, /* 4 Shift-IR */
	/* DAPIRPRE */
	0, 1, 1, 3, /* 4 IDCODE */
	/* DAPIRPOST */ /* Exit1-IR */
	2, 2, 0, 0, /* 4 Update-IR, Shift-DR */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, /* Exit1-DR */
	};

	const char data[] = {2, 2, 2, 2, 2, 0, /* Run-Test/ Idle */
	2, 0, 0, /* Shift-DR */
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, /* Exit1-DR */
	};

	ret = sendto(sockfd, cmd, sizeof(cmd), 0, (struct sockaddr*)&serverAddr, addr_len);
	if (ret < 0)
		printf("sendto failed: %s\n", strerror(errno));

	ret= recvfrom(sockfd, buffer, BUFFER_LEN, 0, (struct sockaddr*)&serverAddr, &addr_len);
	if (ret < 0)
			printf("recvfrom failed: %s\n", strerror(errno));

	idcode = 0;
	for (i = 0; i < 32; i++)
		idcode |= buffer[ret - 32 + i] << i;

	printf("idcode = 0x%x\n", idcode);
}


static int fill_xr(char *buff, uint32_t xr, int xrlen)
{
	int i;

	for (i = 0; i < xrlen; i++)
		buff[i] = (xr >> i) & 0x1;

	return 0;
}


static int get_drlen(drdata_t *dr)
{
	int len = 0;

	while (dr->len) {
		len += dr->len;
		dr++;
	}

	return len;
}


static int fill_dr(char *buff, drdata_t *dr)
{
	while (dr->len) {
		fill_xr(buff, dr->data, dr->len);
		buff += dr->len;
		dr++;
	}
}


/*
 * ir: ir to be shift
 * dr: dr is array, dr is ended with zero-length
 */
static char* jtag_ir_dr(uint32_t ir, drdata_t *dr)
{
	int ret;
	static char buff[BUFFER_LEN];
	int drlen = get_drlen(dr);

	/* cmd is {tms, tdi} in bit format */
	const char pre[] = {2, 2, 2, 2, 2, 0, /* Run-Test/ Idle */
	2, 2, 0, 0, /* Shift-IR */ };

	const char mid[] = {
	2, 2, 0, 0, /* Update-IR, Shift-DR */ };

	const char post[] = {
	2, 0, /* Update-DR, Run-Test/Idle */ };

	int irpos  = sizeof(pre) + DAPIRPRE;
	int irend  = irpos + DAPIRLEN + DAPIRPOST;
	int drpos  = irend + sizeof(mid) + DAPDRPRE;
	int drend  = drpos + drlen + DAPDRPOST;
	int len = drend + sizeof(post);

	memset(buff, 0x1, len); /* BYPASS */

	memcpy(buff, pre, sizeof(pre)); /* Shift-IR */

	fill_xr(buff + irpos, ir, DAPIRLEN);

	buff[irend - 1] |= 0x2; /* Exit1-IR */

	memcpy(buff + irend, mid, sizeof(mid)); /* Shift-DR */

	fill_dr(buff + drpos, dr);

	buff[drend - 1] |= 0x2; /* Exit1-DR */

	memcpy(buff + drend, post, sizeof(post)); /* Run-Test/Idle */

	ret = sendto(sockfd, buff, len, 0, (struct sockaddr*)&serverAddr, addr_len);
	if (ret < 0)
		printf("sendto failed: %s\n", strerror(errno));

	ret= recvfrom(sockfd, buff, BUFFER_LEN, 0, (struct sockaddr*)&serverAddr, &addr_len);
	if (ret < 0)
		printf("recvfrom failed: %s\n", strerror(errno));

	return buff + drpos;
}


static int jtag_idcode()
{
	int i;
	char *buff;
	unsigned int idcode;
	drdata_t dr[2];

	dr[0].data = 0;
	dr[0].len = 32;

	dr[1].len = 0; /*dr ends*/

	buff = jtag_ir_dr(IDCODE, dr);

	idcode = 0;
	for (i = 0; i < 32; i++)
		idcode |= buff[i] << i;

	/* idcode = 0x4ba06477 */
	printf("idcode = 0x%x\n", idcode);

	return 0;
}


/*
 * xPACC: DPACC, APACC
 * addr : SELECT
 * RnW  : RnW_W, RnW_R
 */
static int jtag_xPACC(uint32_t xPACC, uint32_t *data, uint32_t addr, uint32_t RnW, uint32_t *ack)
{
	int i;
	char *buff;
	unsigned int d = 0;
	drdata_t dr[2];

	/* DPACC and APACC, A[3:2] + RnW */
	dr[0].data = (addr & 0xc) >> 1 | RnW;
	dr[0].len = 3;

	dr[1].data = *data;
	dr[1].len = 32;

	dr[2].len = 0; /*dr ends*/

	buff = jtag_ir_dr(xPACC, dr);

	*ack = buff[0] | buff[1] << 1 | buff[2] << 2;

	buff += 3;
	for (i = 0; i < 32; i++)
		d |= buff[i] << i;

	*data = d;

	return 0;
}


static int init_net()
{
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(10086);
	inet_aton("127.0.0.1", &serverAddr.sin_addr);
}


static int dap_read(uint32_t addr, uint32_t *d)
{
	uint32_t data;
	uint32_t ack;
	uint32_t polling = 32;

	do {
		data = addr & ~0xf; /* ADDR, DPBANKSEL(0) */
		jtag_xPACC(DPACC, &data, SELECT, RnW_W, &ack);
	} while (ack & ACK_WAIT);

	data = 0;
	jtag_xPACC(APACC, &data, addr & 0xf, RnW_R, &ack);
	if (ack & ACK_WAIT) printf("dap_read ACK_WAIT\n");

	do {
		data = 0;
		jtag_xPACC(DPACC, &data, RDBUFF, RnW_R, &ack);
	} while ((ack & ACK_WAIT) && --polling);

	if (ack != ACK_OK) {
		printf("jtag_xPACC failed, addr 0x%x ack 0x%x\n", addr, ack);
		return -1;
	}

	*d = data;

	return 0;
}


static int dap_write(uint32_t addr, uint32_t d)
{
	uint32_t data;
	uint32_t ack;

	do {
		data = addr & ~0xf; /* ADDR, DPBANKSEL(0) */
		jtag_xPACC(DPACC, &data, SELECT, RnW_W, &ack);
	} while (ack & ACK_WAIT);

	data = d;
	jtag_xPACC(APACC, &data, addr & 0xf, RnW_W, &ack);

	if (ack != ACK_OK) {
		printf("jtag_xPACC write failed, addr 0x%x ack 0x%x\n", addr, ack);
		return -1;
	}

	return 0;
}


static int enum_rom(uint32_t base, int depth)
{
	int i;
	int ret;
	uint32_t data;
	uint32_t format;
	uint32_t present;

	ret = _ap_read(base + DEVID, &data);
	format = DEVID_FORMAT(data);

	if (format != 0) {
		printf("only support 32-bit\n");
	}

	for (i = 0; i < 512; i++) {
		ret = _ap_read(base + (i << 2), &data);

		present = ROMENTRY_PRESENT(data);

		if (present == 0)
			break;
		else if (present == 1) {
			printf("only support 32-bit\n");
			break;
		} else if (present == 2) {
			continue;
		}

		if (depth == 0) {
			#if 0
			if (i >=6 && i <= 9) continue; //saf e1
			//if (i >=10 && i <= 12) continue; //ap0 e2
			if (i >=13 && i <= 15) continue; //ap1 e3
			if (i == 16) continue; //zy
			//if (i == 17) continue; //ap0
			if (i == 18) continue; //ap1
			if (i == 19) continue; //r52
			#endif
		}

		printf("%*d: ", 2 * (depth + 1), i);
		/* The ROM Entry is present */
		enumeration(base + ROMENTRY_OFFSET(data), depth + 1);
	}

}

/* ARCHID Description */
const static struct {
	uint32_t archid;
	const char *desc;
} adesc[] = {
	{0x0A00, "RAS architecture"},
	{0x1A01, "Instrumentation Trace Macrocell (ITM) architecture"},
	{0x1A02, "DWT architecture"},
	{0x1A03, "Flash Patch and Breakpoint unit (FPB) architecture"},
	{0x2A04, "Processor debug architecture (ARMv8-M)"},
	{0x6A05, "Processor debug architecture (ARMv8-R)"},
	{0x0A10, "PC sample-based profiling"},
	{0x4A13, "Embedded Trace Macrocell (ETM) architecture."},
	{0x1A14, "Cross Trigger Interface (CTI) architecture"},
	{0x6A15, "Processor debug architecture (v8.0-A)"},
	{0x7A15, "Processor debug architecture (v8.1-A)"},
	{0x8A15, "Processor debug architecture (v8.2-A)"},
	{0x2A16, "Processor Performance Monitor (PMU) architecture"},
	{0x0A17, "Memory Access Port v2 architecture"},
	{0x0A27, "JTAG Access Port v2 architecture"},
	{0x0A31, "Basic trace router"},
	{0x0A37, "Power requestor"},
	{0x0A47, "Unknown Access Port v2 architecture"},
	{0x0A50, "HSSTP architecture"},
	{0x0A63, "System Trace Macrocell (STM) architecture"},
	{0x0A75, "CoreSight ELA architecture"},
	{0x0AF7, "CoreSight ROM architecture"},
};


static const char * archid_desc(uint32_t archid)
{
	int i;

	for (i = 0; i < sizeof(adesc) / sizeof(adesc[0]); i++) {
		if (adesc[i].archid == archid)
			return adesc[i].desc;
	}

	return "";
}


/* PART Description */
const static struct {
	uint32_t part;
	const char *desc;
} pdesc[] = {
	{0x193, "css600_tsgen"},
	{0x9e2, "css600_apbap"},
	{0x9e3, "css600_ahbap"},
	{0x9e4, "css600_axiap"},
	{0x9e5, "css600_apv1adapter"},
	{0x9e6, "css600_jtagap"},
	{0x9e7, "css600_tpiu"},
	{0x9e8, "css600_tmc_etr/ets"},
	{0x9e9, "css600_tmc_etb"},
	{0x9ea, "css600_tmc_etf"},
	{0x9eb, "css600_atbfunnel_prog"},
	{0x9ec, "css600_atbreplicator_prog"},
	{0x9ed, "css600_cti"},
	{0x9ee, "css600_catu"},

};

static const char * part_desc(uint32_t part)
{
	int i;

	for (i = 0; i < sizeof(pdesc) / sizeof(pdesc[0]); i++) {
		if (pdesc[i].part == part)
			return pdesc[i].desc;
	}

	return "";
}


static int dp_ABORT()
{
	uint32_t ack;
	uint32_t data;

	data = 0x5;
	jtag_xPACC(ABORT, &data, 0, RnW_W, &ack);

	data = 0x5;
	jtag_xPACC(ABORT, &data, 0, RnW_W, &ack);

	if (ack != ACK_OK) {
		printf("dp_ABORT failed, ack 0x%x\n", ack);
		return -1;
	}

	return 0;
}


static int enumeration(uint32_t base, int depth)
{
	int ret;
	uint32_t data, data2;
	uint32_t class;
	uint32_t archid = 0;
	uint32_t part;

	ret = _ap_read(base + CIDR1, &data);

	if (ret < 0) {
		dp_ABORT();
		printf("base 0x%08x access failed\n", base);
		return -1;
	}

	class = CIDR_CLASS(data);

	ret = _ap_read(base + PIDR0, &data);
	ret = _ap_read(base + PIDR1, &data2);

	part = PIDR_PART(data, data2);

	if (class == 0x9) {
		ret = _ap_read(base + DEVARCH, &data);
		if (DEVARCH_PRESENT & data)
			archid = DEVARCH_ARCHID(data);
	}

	printf("base 0x%08x class %x part 0x%03x(%s) archid 0x%03x(%s)\n",
			base, class, part, part_desc(part), archid, archid_desc(archid));

	if (archid == 0x0AF7)
		return enum_rom(base, depth);

	return 0;
}


static int memap_read(uint32_t addr, uint32_t *d)
{
	int ret;
	uint32_t base = base2lvl;

	ret = dap_write(base + TAR, addr);
	ret = dap_read(base + DRW, d);

	return ret;
}


static int memap_write(uint32_t addr, uint32_t d)
{
	int ret;
	uint32_t base = base2lvl;

	ret = dap_write(base + TAR, addr);
	ret = dap_write(base + DRW, d);

	return ret;
}


/* ARM Architecture Reference Manual
 * ARMv8, for ARMv8-A architecture profile
 */
/* H9.2 External debug registers */
#define EDSCR       0x088
#define OSLAR_EL1   0x300
#define EDPRSR      0x314
#define MIDR_EL1    0xD00
/* H9.3 Cross-Trigger Interface registers */
#define CTICONTROL  0x000
#define CTIINTACK   0x010
#define CTIAPPSET   0x014
#define CTIAPPPULSE 0x01C
#define CTIOUTEN(n) (0x0A0 + (n << 2))
#define CTITRIGOUTSTATUS 0x134
#define CTIGATE     0x140


/* H9.2.40 EDPRSR, External Debug Processor Status Register */
#define HALTED      (1 << 4)

/* H9.3.14 CTICONTROL, CTI Control register */
#define GLBEN       (1 << 0)

#define CHANNEL(x)  (1 << x)
#define EVENT(n)    (1 << n)

/* H5.4 Description and allocation of CTI triggers */
#define DEBUG_REQUEST_TRIGGER   0
#define RESTART_REQUEST_TRIGGER 1


/* Example H5-1 Halting a single PE */
static int debug_request_trigger(uint32_t dbg, uint32_t cti)
{
	uint32_t data;

	memap_write(dbg + OSLAR_EL1, 0);

	memap_write(cti + CTICONTROL, GLBEN);

	memap_write(cti + CTIGATE, 0);

	memap_write(cti + CTIOUTEN(DEBUG_REQUEST_TRIGGER), CHANNEL(0));

	memap_write(cti + CTIAPPPULSE, CHANNEL(0));

	do {
		if (memap_read(dbg + EDPRSR, &data) < 0)
			return -1;
	} while (!(data & HALTED));

	memap_write(cti + CTIOUTEN(DEBUG_REQUEST_TRIGGER), 0);

	return 0;
}


/* Example H5-3 Synchronously restarting a group of PEs */
static int restart_request_trigger(uint32_t dbg, uint32_t cti)
{
	uint32_t data;

	memap_write(cti + CTIINTACK, EVENT(0));

	do {
		if (memap_read(cti + CTITRIGOUTSTATUS, &data) < 0)
			return -1;
	} while (data & EVENT(DEBUG_REQUEST_TRIGGER));

	memap_write(cti + CTIOUTEN(RESTART_REQUEST_TRIGGER), CHANNEL(0));

	memap_write(cti + CTIAPPPULSE, CHANNEL(0));

	do {
		if (memap_read(dbg + EDPRSR, &data) < 0)
			return -1;
	} while (data & HALTED);

	memap_write(cti + CTIOUTEN(RESTART_REQUEST_TRIGGER), 0);

	return 0;
}


int main(int argc, char**argv)
{
	uint32_t ack;
	uint32_t addr, data;

	init_net();

	if (argc >= 2 && argv[1][0] == 'e') {

		test_idcode();

		jtag_idcode();

		dp_ABORT();

		_ap_read = dap_read;
		enumeration(0, 0);

		printf("\n");

		base2lvl = 0x80000;
		_ap_read = memap_read;
		enumeration(0, 0);

		return 0;
	}

	/* default use apbap */
	base2lvl = 0x80000;

	if (argc >= 3 && (argv[1][0] == 'r' || argv[1][0] == 'R')) {

		if (argv[1][0] == 'r')
			base2lvl = 0xa0000;
		addr = strtoul(argv[2], NULL, 0);
		memap_read(addr, &data);
		printf("addr(0x%08x) = 0x%08x(%d)\n", addr, data, data);

	} else if (argc >= 4 && (argv[1][0] == 'w' || argv[1][0] == 'W')) {

		if (argv[1][0] == 'w')
			base2lvl = 0xa0000;
		addr = strtoul(argv[2], NULL, 0);
		if (isdigit(argv[3][0]))
			data = strtoul(argv[3], NULL, 0);
		else
			data = argv[3][0];
		memap_write(addr, data);

	} else if (argc >= 2 && argv[1][0] == 'd') {
		debug_request_trigger(0x1010000, 0x1020000);
	} else if (argc >= 2 && argv[1][0] == 'c') {
		restart_request_trigger(0x1010000, 0x1020000);
	} else {

		printf("Do enumeration\n  %s e\n", argv[0]);
		printf("Do DEBUG_REQUEST_TRIGGER\n  %s d\n", argv[0]);
		printf("Do RESTART_REQUEST_TRIGGER\n  %s c\n", argv[0]);
		printf("Read memory with AXI-AP\n  %s r <addr>\n", argv[0]);
		printf("Write memory with AXI-AP\n  %s w <addr> <value>\n", argv[0]);
		printf("Read memory with APB-AP\n  %s R <addr>\n", argv[0]);
		printf("Write memory with APB-AP\n  %s W <addr> <value>\n", argv[0]);
		printf("e.g.\n");
		printf("  %s r 0xe9490000\n", argv[0]);
		printf("  %s w 0xe9490000 x\n", argv[0]);
		printf("  %s w 0xe9490000 0x78\n", argv[0]);
		printf("  %s R 0x01010fbc    #DEVARCH\n", argv[0]);
		printf("  %s R 0x01010314    #EDPRSR\n", argv[0]);
		printf("  %s W 0x01010300 0  #OSLAR_EL1\n", argv[0]);

	}

/*
	data = 1<<30 | 1<<28;
	jtag_xPACC(DPACC, &data, CTRLSTAT, RnW_W, &ack);
	printf("ack 0x%x 0x%x\n", ack, data);

	data = 0;
	jtag_xPACC(DPACC, &data, CTRLSTAT, RnW_R, &ack);
	printf("ack 0x%x 0x%x\n", ack, data);
*/
	return 0;
}

