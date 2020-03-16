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
#include "libfdt.h"
#include "fdt_support.h"

#define MAX_LEVEL	32		/* how deeply nested we will go */
#define SCRATCHPAD	1024		/* bytes of scratchpad memory */
#define CMD_FDT_MAX_DUMP 64


static void *fdt;
static int fdt_parse_prop(char **newval, int count, char *data, int *len);
static int fdt_print(const char *pathp, char *prop, int depth);
static int is_printable_string (const void *data, int len)
{
	const char *s = data;

	/* zero length is not */
	if (len == 0)
		return 0;

	/* must terminate with zero */
	if (s[len - 1] != '\0')
		return 0;

	/* printable or a null byte (concatenated strings) */
	while (((*s == '\0') || isprint(*s)) && (len > 0)) {
		/*
		 * If we see a null, there are three possibilities:
		 * 1) If len == 1, it is the end of the string, printable
		 * 2) Next character also a null, not printable.
		 * 3) Next character not a null, continue to check.
		 */
		if (s[0] == '\0') {
			if (len == 1)
				return 1;
			if (s[1] == '\0')
				return 0;
		}
		s++;
		len--;
	}

	/* Not the null termination, or not done yet: not printable */
	if (*s != '\0' || (len != 0))
		return 0;

	return 1;
}

/*
 * Print the property in the best format, a heuristic guess.  Print as
 * a string, concatenated strings, a byte, word, double word, or (if all
 * else fails) it is printed as a stream of bytes.
 */
static void print_data (const void *data, int len)
{
	int j;

	/* no data, don't print */
	if (len == 0)
		return;

	/*
	 * It is a string, but it may have multiple strings (embedded '\0's).
	 */
	if (is_printable_string(data, len)) {
		puts("\"");
		j = 0;
		while (j < len) {
			if (j > 0)
				puts("\", \"");
			puts(data);
			j    += strlen(data) + 1;
			data += strlen(data) + 1;
		}
		puts("\"");
		return;
	}

	if ((len %4) == 0) {
		if (len > CMD_FDT_MAX_DUMP)
			printf("* 0x%p [0x%08x]", data, len);
		else {
			const u32 *p;

			printf("<");
			for (j = 0, p = data; j < len/4; j++)
				printf("0x%08x%s", fdt32_to_cpu(p[j]),
					j < (len/4 - 1) ? " " : "");
			printf(">");
		}
	} else { /* anything else... hexdump */
		if (len > CMD_FDT_MAX_DUMP)
			printf("* 0x%p [0x%08x]", data, len);
		else {
			const u8 *s;

			printf("[");
			for (j = 0, s = data; j < len; j++)
				printf("%02x%s", s[j], j < len - 1 ? " " : "");
			printf("]");
		}
	}
}

/*
 * Recursively print (a portion of) the fdt.  The depth parameter
 * determines how deeply nested the fdt is printed.
 */
static int fdt_print (const char *pathp, char *prop, int depth)
{
	static char tabs[MAX_LEVEL+1] =
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"
		"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
	const void *nodep;	/* property node pointer */
	int  nodeoffset;	/* node offset from libfdt */
	int  nextoffset;	/* next node offset from libfdt */
	uint32_t tag;		/* tag */
	int  len;		/* length of the property */
	int  level = 0;		/* keep track of nesting level */
	const struct fdt_property *fdt_prop;

	nodeoffset = fdt_path_offset(fdt, pathp);
	if (nodeoffset < 0) {
		/*
		 * Not found or something else bad happened.
		 */
		printf ("libfdt fdt_path_offset() returned %s\n",
			fdt_strerror(nodeoffset));
		return 1;
	}
	/*
	 * The user passed in a property as well as node path.
	 * Print only the given property and then return.
	 */
	if (prop) {
		nodep = fdt_getprop(fdt, nodeoffset, prop, &len);
		if (len == 0) {
			/* no property value */
			printf("%s %s\n", pathp, prop);
			return 0;
		} else if (len > 0) {
			printf("%s = ", prop);
			print_data (nodep, len);
			printf("\n");
			return 0;
		} else {
			printf ("libfdt fdt_getprop(): %s\n",
				fdt_strerror(len));
			return 1;
		}
	}

	/*
	 * The user passed in a node path and no property,
	 * print the node and all subnodes.
	 */
	while(level >= 0) {
		tag = fdt_next_tag(fdt, nodeoffset, &nextoffset);
		switch(tag) {
		case FDT_BEGIN_NODE:
			pathp = fdt_get_name(fdt, nodeoffset, NULL);
			if (level <= depth) {
				if (pathp == NULL)
					pathp = "/* NULL pointer error */";
				if (*pathp == '\0')
					pathp = "/";	/* root is nameless */
				printf("%s%s {\n",
					&tabs[MAX_LEVEL - level], pathp);
			}
			level++;
			if (level >= MAX_LEVEL) {
				printf("Nested too deep, aborting.\n");
				return 1;
			}
			break;
		case FDT_END_NODE:
			level--;
			if (level <= depth)
				printf("%s};\n", &tabs[MAX_LEVEL - level]);
			if (level == 0) {
				level = -1;		/* exit the loop */
			}
			break;
		case FDT_PROP:
			fdt_prop = fdt_offset_ptr(fdt, nodeoffset,
					sizeof(*fdt_prop));
			pathp    = fdt_string(fdt,
					fdt32_to_cpu(fdt_prop->nameoff));
			len      = fdt32_to_cpu(fdt_prop->len);
			nodep    = fdt_prop->data;
			if (len < 0) {
				printf ("libfdt fdt_getprop(): %s\n",
					fdt_strerror(len));
				return 1;
			} else if (len == 0) {
				/* the property has no value */
				if (level <= depth)
					printf("%s%s;\n",
						&tabs[MAX_LEVEL - level],
						pathp);
			} else {
				if (level <= depth) {
					printf("%s%s = ",
						&tabs[MAX_LEVEL - level],
						pathp);
					print_data (nodep, len);
					printf(";\n");
				}
			}
			break;
		case FDT_NOP:
			printf("%s/* NOP */\n", &tabs[MAX_LEVEL - level]);
			break;
		case FDT_END:
			return 1;
		default:
			if (level <= depth)
				printf("Unknown tag 0x%08X\n", tag);
			return 1;
		}
		nodeoffset = nextoffset;
	}
	return 0;
}

/*
 * Parse the user's input, partially heuristic.  Valid formats:
 * <0x00112233 4 05>	- an array of cells.  Numbers follow standard
 *			C conventions.
 * [00 11 22 .. nn] - byte stream
 * "string"	- If the the value doesn't start with "<" or "[", it is
 *			treated as a string.  Note that the quotes are
 *			stripped by the parser before we get the string.
 * newval: An array of strings containing the new property as specified
 *	on the command line
 * count: The number of strings in the array
 * data: A bytestream to be placed in the property
 * len: The length of the resulting bytestream
 */
static int fdt_parse_prop (char **newval, int count, char *data, int *len)
{
	char *cp;		/* temporary char pointer */
	char *newp;		/* temporary newval char pointer */
	unsigned long tmp;	/* holds converted values */
	int stridx = 0;

	*len = 0;
	newp = newval[0];

	/* An array of cells */
	if (*newp == '<') {
		newp++;
		while ((*newp != '>') && (stridx < count)) {
			/*
			 * Keep searching until we find that last ">"
			 * That way users don't have to escape the spaces
			 */
			if (*newp == '\0') {
				newp = newval[++stridx];
				continue;
			}

			cp = newp;
			tmp = strtoul(cp, &newp, 0);
			*(uint32_t *)data = cpu_to_fdt32(tmp);
			data  += 4;
			*len += 4;

			/* If the ptr didn't advance, something went wrong */
			if ((newp - cp) <= 0) {
				printf("Sorry, I could not convert \"%s\"\n", cp);
				return 1;
			}

			while (*newp == ' ')
				newp++;
		}

		if (*newp != '>') {
			printf("Unexpected character '%c'\n", *newp);
			return 1;
		}
	} else if (*newp == '[') {
		/*
		 * Byte stream.  Convert the values.
		 */
		newp++;
		while ((stridx < count) && (*newp != ']')) {
			while (*newp == ' ')
				newp++;
			if (*newp == '\0') {
				newp = newval[++stridx];
				continue;
			}
			if (!isxdigit(*newp))
				break;
			tmp = strtoul(newp, &newp, 16);
			*data++ = tmp & 0xFF;
			*len    = *len + 1;
		}
		if (*newp != ']') {
			printf("Unexpected character '%c'\n", *newp);
			return 1;
		}
	} else {
		/*
		 * Assume it is one or more strings.  Copy it into our
		 * data area for convenience (including the
		 * terminating '\0's).
		 */
		while (stridx < count) {
			size_t length = strlen(newp) + 1;
			strcpy(data, newp);
			data += length;
			*len += length;
			newp = newval[++stridx];
		}
	}
	return 0;
}

/*
 * Flattened Device Tree command, see the help for parameter definitions.
 */
static int do_fdt (int argc, char * argv[])
{
	int i=2;
	int ret = 0;
	int len = 0;
	int depth = MAX_LEVEL;	/* how deep to print */
	char *pathp;			/* path */
	char *prop;				/* property */
	static char root[2] = "/";
	int  nodeoffset;		/* node offset from libfdt */
	static char data[SCRATCHPAD];	/* storage for the property */
	unsigned long initrd_start = 0, initrd_end = 0;

	/********************************************************************
	* Set the address of the fdt
	********************************************************************/
	if (argv[1][0] == 'o') {

		if (argc < 3)
        	return -1;

		fdt = (void *)(strtoul(argv[2], 0, 0));
		ret = fdt_check_header(fdt);
        if (ret < 0) {
			printf("error fdt header.\n");
			return -1;
		}

		if (argc >= 4)
			len = strtoul(argv[3], 0, 0);

		return fdt_open_into(fdt, fdt, len);
	}

	/********************************************************************
	* Print (recursive)
	********************************************************************/
	if (argv[1][0] == 'p') {
        /*
		 * Get the starting path.  The root node is an oddball,
		 * the offset is zero and has no name.
		 */
		if (argc == 2)
			pathp = root;
		else
			pathp = argv[2];
		if (argc > 3)
			prop = argv[3];
		else
			prop = NULL;

		ret = fdt_print(pathp, prop, depth);

		if (ret != 0)
			return ret;
    }
	/********************************************************************
	* Set the value of a property in the fdt.
	********************************************************************/
	if (argv[1][0] == 's') {
		/*
		 * Parameters: Node path, property, optional value.
		 */
		if (argc < 4) {
			return 1;
		}
		pathp = argv[2];
		prop  = argv[3];
		nodeoffset = fdt_path_offset_create(fdt, pathp);
		if (nodeoffset < 0) {
			printf("libfdt fdt_path_offset() returned %s.\n",
					fdt_strerror(nodeoffset));
			return nodeoffset;
		}

		if (argc == 4) {
			len = 0;
		} else {
			ret = fdt_parse_prop(&argv[4], argc - 4, data, &len);
			if (ret != 0)
				return ret;
		}

		ret = fdt_setprop(fdt, nodeoffset, prop, data, len);
		if (ret < 0) {
			printf ("libfdt fdt_setprop(): %s\n", fdt_strerror(ret));
			return 1;
		}
	}

	/********************************************************************
	* Set bootargs's content
	********************************************************************/
	if (argv[1][0] == 'b') {
		strcpy(data,"");
		for (; i < argc; i++){
			strcat(data, argv[i]);
			if (i != argc - 1)
				strcat(data, " ");
		}
		len = strlen(data) + 1;
		nodeoffset = fdt_path_offset(fdt, "/chosen");
		if (nodeoffset < 0) {
			/*
			 * Not found or something else bad happened.
			 */
			printf ("libfdt fdt_path_offset() returned %s\n",
				fdt_strerror(nodeoffset));
			return 1;
		}

		ret = fdt_setprop(fdt, nodeoffset, "bootargs", data, len);
		if (ret < 0) {
			printf ("libfdt fdt_setprop(): %s\n", fdt_strerror(ret));
			return 1;
		}
	}

	/********************************************************************
	* Check chosen node and create it if it not exist
	********************************************************************/
	if (argv[1][0] == 'i') {

		if ((argc != 2) && (argc != 4)) {
			return 1;
		}

		if (argc == 4) {
			initrd_start = strtoul(argv[2], NULL, 16);
			initrd_end = strtoul(argv[3], NULL, 16);
		}

		fdt_chosen(fdt);
		fdt_initrd(fdt, initrd_start, initrd_end);
	}
	return 0;

}

MK_CMD(fdt, do_fdt, "Display and modify device tree contents",
	"fdt open addr [len]\n"
	"	- Set the fdt location to <addr>\n"
	"fdt print [<path>] [<prop>]\n"
	"	- Recursive print starting at <path>, defult path is '/' \n"
	"fdt set <path> <prop> [<val>]\n"
	"	- Set <property> [to <val>]\n"
	"	e.g fdt set /memory reg <0x0 0x1 0x0 0x2>\n"
	"fdt bootargs content"
	"	-Set /chosen bootargs's content.\n"
	"fdt initrd [<start> <end>]\n"
	"	- Add/update the /chosen branch in the tree, <start>/<end> - initrd start/end addr\n"
	"	e.g fdt chosen 0x1 0x2\n"

);
