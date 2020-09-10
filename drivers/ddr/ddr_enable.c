#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <target/cmdline.h>
#include <target/ddr.h>

#define MAX_DDR_SIZE 0x200000000
#define SIZE_1M  0x100000


int do_ddr_enable(int argc, char *argv[])
{
    if (argc != 2) {
        printf("--ERROR: The parameters not compatible \n");
        return -1;
    }

    if (strcmp(argv[1], "init") == 0) {

        ddr_init();
        printf("\n ddr is enabled! \n");
    }
    else {
        printf("Unknown command\n\n");
        return -1;
    }

    return 0;
}



MK_CMD(ddr, do_ddr_enable, "enable ddr",
    " ddr init \n"
    "    -ddr enable. \n"
);


