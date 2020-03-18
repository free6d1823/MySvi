#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <target/readline.h>
#include <target/cmdline.h>
#include <target/timer.h>
#include <target/cpus.h>
#include <target/utils.h>

#define PROMPT "SVI> "

#ifdef CONFIG_CONSOLE_COMMAND
extern cmd_tbl __cmd_array_start[];
extern cmd_tbl __cmd_array_end[];

#define foreach_cmd(cmdp) for (cmdp = __cmd_array_start; cmdp < __cmd_array_end; cmdp++)
#define MAXARGS  10
#define MAX_LINE_LENGTH_BYTES (64)
#define DEFAULT_LINE_LENGTH_BYTES (16)
#define DISP_LINE_LEN   16

static int parse_line(char *line, char *argv[])
{
    int nargs = 0;

    while (nargs < MAXARGS) {
        /* skip any white space */
        while (isblank(*line))
            ++line;

        if (*line == '\0') {    /* end of line, no more args    */
            argv[nargs] = NULL;
            return nargs;
        }

        argv[nargs++] = line;   /* begin of argument string */
        /* find end of string */
        while (*line && !isblank(*line))
            ++line;

        if (*line == '\0') {    /* end of line, no more args    */
            argv[nargs] = NULL;
            return nargs;
        }
        *line++ = '\0';     /* terminate current arg     */
    }

    printf("** Too many args (max. %d) **\n", MAXARGS);
    return nargs;
}

static cmd_tbl *find_cmd(const char *cmd)
{
    cmd_tbl *cmdp;

    foreach_cmd(cmdp) {
        if (strcmp(cmdp->name, cmd))
            continue;
        return cmdp;
    }
    return NULL;
}

int cmd_help(char *cmd)
{
	cmd_tbl *cmdp;

	if (!cmd) {
		foreach_cmd(cmdp) {
			printf("%-*s- %s\n", 10,
			       cmdp->name, cmdp->help);
		}
	} else {
		cmdp = find_cmd(cmd);
		if (!cmdp) {
			printf("Unknown command '%s'\n\n", cmd);
			return -EINVAL;
		}
		printf("%s: %s\n", cmdp->name, cmdp->help);
		printf("Usage of %s:\n", cmdp->name);
		puts(cmdp->usage);
		puts("\n");
	}
	return 0;
}

static int do_help(int argc, char *argv[])
{
	int i, ret = 0;

	if (argc == 1)
		return cmd_help(NULL);
	for (i = 1; i < argc; ++i) {
		ret |= cmd_help(argv[i]);
	}

	return ret;
}

int cmd_get_data_size(char* arg, int default_size)
{
    switch (arg[0]){
    case 'b':
        return 1;
    case 'w':
        return 2;
    case 'l':
        return 4;
    case 'q':
        return 8;
    default:
        return -1;
    }
    return default_size;
}

int print_buffer(unsigned long addr, const void *data,
                 unsigned int width, unsigned int count,
                 unsigned int linelen)
{
    /* linebuf as a union causes proper alignment */
    union linebuf {
        uint64_t uq[MAX_LINE_LENGTH_BYTES/sizeof(uint64_t) + 1];
        uint32_t ui[MAX_LINE_LENGTH_BYTES/sizeof(uint32_t) + 1];
        uint16_t us[MAX_LINE_LENGTH_BYTES/sizeof(uint16_t) + 1];
        uint8_t  uc[MAX_LINE_LENGTH_BYTES/sizeof(uint8_t) + 1];
    } lb;
    int i;
    uint64_t x;

    if (linelen*width > MAX_LINE_LENGTH_BYTES)
        linelen = MAX_LINE_LENGTH_BYTES / width;
    if (linelen < 1)
        linelen = DEFAULT_LINE_LENGTH_BYTES / width;

    while (count) {
        unsigned int thislinelen = linelen;
        printf("0x%010p:", addr);

        /* check for overflow condition */
        if (count < thislinelen)
            thislinelen = count;

        /* Copy from memory into linebuf and print hex values */
        for (i = 0; i < thislinelen; i++) {
            if (width == 4)
                x = lb.ui[i] = *(volatile uint32_t *)data;
            else if (width == 8)
                x = lb.uq[i] = *(volatile uint64_t *)data;
            else if (width == 2)
                x = lb.us[i] = *(volatile uint16_t *)data;
            else
                x = lb.uc[i] = *(volatile uint8_t *)data;
            printf(" %0*llx", width * 2, (long long)x);
            data += width;
        }

        while (thislinelen < linelen) {
            /* fill line with whitespace for nice ASCII print */
            for (i=0; i<width*2+1; i++)
                printf(" ");
            linelen--;
        }

        /* Print data in ASCII characters */
        for (i = 0; i < thislinelen * width; i++) {
            if (!isprint(lb.uc[i]) || lb.uc[i] >= 0x80)
                lb.uc[i] = '.';
        }
        lb.uc[i] = '\0';
        printf("    %s\n", lb.uc);

        /* update references */
        addr += thislinelen * width;
        count -= thislinelen;
    }
    return 0;
}

/* Memory Display
 *
 * Syntax:
 *  md {b, w, l, q} {addr} {len}
 */
static int do_mem_display(int argc, char * argv[])
{
	int size;
	unsigned long addr = 0;
	unsigned long length = 1;
	void *buf = NULL;

	if (argc < 3)
		return -EUSAGE;

	if ((size = cmd_get_data_size(argv[1], 4)) < 0)
		return 1;

	addr = strtoul(argv[2], 0, 0);

	if (argc >= 4)
		length = strtoul(argv[3], NULL, 0);

	buf = (void *)(unsigned long)addr;
	print_buffer(addr, buf, size, length, DISP_LINE_LEN / size);
	return 1;
}

static int do_mem_write(int argc, char *argv[])
{
	uintptr_t write_data, addr;
	uint32_t count, size, bytes;
	void * p;

	if (argc < 4)
		return -EUSAGE;

	if ((size = cmd_get_data_size(argv[1], 4)) < 0)
		return -1;

	addr = strtoul(argv[2], NULL, 0);
	write_data = strtoul(argv[3], NULL, 0);

	if(argc >= 5)
		count = strtoul(argv[4], NULL, 0);
	else
		count = 1;

	p = (void *)addr;

	while(count-- > 0) {
		switch (size) {
			case 4:
				*((uint32_t *)p) = (uint32_t) write_data;
				break;
			case 8:
				*((uint64_t *)p) = (uint64_t) write_data;
				break;
			case 2:
				*((uint16_t *)p) = (uint16_t) write_data;
				break;
			case 1:
				*((uint8_t *)p) = (uint8_t) write_data;
				break;
		}
		p += size;
	}
	return 0;
}

MK_CMD(md, do_mem_display, "Display memory contents",
    "md b|w|l|q addr [count]\n"
    "    - b(byte), w(word), l(uint), q(uint64)\n"
    "    - count: number of items, default is 1\n"
);

MK_CMD(mw, do_mem_write, "Write the memory contents",
    "mw b|w|l|q addr data [count]\n"
    "    - b(byte), w(word), l(uint), q(uint64)\n"
    "    - data: the data to be filled with\n"
    "    - count: number of items, default is 1\n"
);

MK_CMD(help, do_help, "Print command description/usage",
    "help\n"
    "    - print brief description of all commands\n"
    "help command ...\n"
    "    - print the detailed usage of 'command'"
    "\n"
);

static int do_rr_rw(int argc, char * argv[])
{
	uint32_t mask = 0xFFFFFFFF;
	uintptr_t addr = 0;
	uint32_t data = 0;
	uint32_t val = 0;
	uint8_t a, b, i = 0;

	// rr <addr> <a:b>
	// rr <base> <addr> <a:b>
	if ((argc == 3 || argc == 4) && strcmp(argv[0], "rr") == 0) {
		addr = strtoull(argv[1], 0, 0);
		if (argc == 4) {
			i = 1;
			addr += strtoull(argv[2], 0, 0);
		}
		a = strtoul(argv[2 + i], 0, 0);
		b = strtoul(strchr(argv[2 + i], ':') + 1, 0, 0);
		if (a < b) return -1;
		mask = ((1 << (a + 1 - b)) - 1) << b;
		data = readl(addr);
		val = (data & mask) >> b;
		printf("Reg read addr:0x%08p mask:0x%08x val:0x%08x field: hex 0x%x dec %d)\n", addr, mask, data, val, val);
		return 0;
	}

	// rw <addr> <a:b> <val>
	// rw <base> <addr> <a:b> <val>
	if ((argc == 4 || argc == 5)&& strcmp(argv[0], "rw") == 0) {
		addr = strtoull(argv[1], 0, 0);
		if (argc == 5) {
			i = 1;
			addr += strtoull(argv[2], 0, 0);
		}
		a = strtoul(argv[2 + i], 0, 0);
		b = strtoul(strchr(argv[2 + i], ':') + 1, 0, 0);
		if (a < b) return -1;
		mask = ((1 << (a + 1 - b)) - 1) << b;
		val = strtoul(argv[3 + i], 0, 0);
		data = readl(addr);
		writel(((val << b) & mask) | (data & ~mask), addr);
		printf("Reg write addr 0x%8p mask:0x%08x old:0x%08x field: hex 0x%x dec %d)\n", addr, mask, data, val, val);
		return 0;
	}

	return -1;
}

MK_CMD(rr, do_rr_rw, "Reg read command.",
		"rr <addr> <a:b>\n"
		"rr <base> <addr> <a:b>\n");
MK_CMD(rw, do_rr_rw, "Reg write command.",
		"rw <addr <a:b> <val>\n"
		"rw <base> <addr> <a:b> <val>\n");

static int g_cmd_ret_value = 0;
static int do_echo(int argc, char * argv[])
{
	int i;

	if (argc < 2)
		return -1;

	if (strcmp(argv[1], "$?") == 0) {
		printf("%d\n", g_cmd_ret_value);
		return 0;
	}
	for(i = 1; i < argc; ++i)
		printf("%s ", argv[i]);
	printf("\n");
	return 0;
}

MK_CMD(echo, do_echo, "Show some env",
	"echo\n"
	"echo $?\n"
	"    - show last command Exit Status\n"
);

static int process_cmd(int argc, char * argv[])
{
	int ret;
	cmd_tbl *cmdp;

	cmdp = find_cmd(argv[0]);
	if (cmdp == NULL) {
		printf("Unknown command '%s'\n", argv[0]);
		return -1;
	}
	ret = cmdp->cmd(argc, argv);
	g_cmd_ret_value = ret;

	if (ret == -EUSAGE)
		cmd_help(argv[0]);

	return ret ? 0 : 1;
}

int cmd_console_handler(char *buf, int len)
{
	char *argv[MAXARGS + 1];
	int argc;
	char *p = NULL;
	int ret = 0;
	char op;
	size_t pos = 0;
	bool skip = false;

	if (len < 0) {
		printf("<INTERRUPT>\n");
		puts(PROMPT);
		return -EINTR;
	}

	if ((p = strchr(buf, '#')) != NULL)
		p[0] = '\0'; // remove comment

Next:
	op = '\0';
	if ((pos = strcspn(buf, "&|;")) != strlen(buf))
		op = buf[pos], buf[pos] = '\0';
	p = buf + pos + 1;
	if (skip) {
		skip = false;
		buf = p;
		goto Next;
	}

	argc = parse_line(buf, argv);
	ret = 0; // may be null between &;
	if (argc > 0)
		ret = process_cmd(argc, argv);

	if (op != '\0') {
		if (op == '&' && ret == 0)
			skip = true;
		if (op == '|' && ret == 1)
			skip = true;
		buf = p;
		goto Next;
	}

	puts(PROMPT);

	return 0;
}

int cmd_init(void)
{
	readline_register_handler(cmd_console_handler);

	puts(PROMPT);

	return 0;
}
#endif
