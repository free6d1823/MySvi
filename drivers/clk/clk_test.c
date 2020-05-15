/**---------------------------------------------------------------------------
 * @file    clk_test.c
 *
 * @brief    test cases fro clock driver
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <target/cmdline.h>
#include <errno.h>
#include <target/heap.h>
#include <target/utils.h>
#include <target/clk.h>

static int do_clk_test(int argc, char *argv[])
{
	long id;
	ulong rate, exp_rate;

	if ((argv[1][0] == 'e')) {
			id = strtoull(argv[2], 0, 0);
			clk_enable(id, 1);
	} else if (!strcmp(argv[1], "dump")) {
		if (!strcmp(argv[2], "all"))
			id = 0x55556666;
		else
			id = strtoull(argv[2], 0, 0);

		clk_dump(id);
	} else if (!strcmp(argv[1], "check")) {
		id = strtoull(argv[2], 0, 0);
		exp_rate = strtoull(argv[3], 0, 0);
		clk_set_rate(id, exp_rate);
		rate = clk_get_rate(id);

		if (rate == exp_rate) {
			printf("clk set/get check passed\n");
		} else {
			printf("clk check failed\n");
		}
	}

	return 1;
}

MK_CMD(clk, do_clk_test, "clock basic test",
	"clk dump <id|all>\n"
	"    - dump all clk or specific ID clk rate\n"
	"clk check <id> <rate>\n"
	"    - write the clk rate and read it back for check\n"
);