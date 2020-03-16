#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "dwc_ddrphy_phyinit.h"

extern FILE *outFilePtr; // defined in the dwc_ddrphy_phyinit_globals.c
//extern char *CmntStr; // defined in the dwc_ddrphy_phyinit_globals.c
//extern char *ApbStr; // defined in the dwc_ddrphy_phyinit_globals.c

int dwc_ddrphy_phyinit_log () {
    char *outFileName="phyinit.log";
    char *printf_header;
    printf_header = "// [dwc_ddrphy_phyinit_main]";
        // Open Txt output Stream 
        if ( (outFilePtr=fopen(outFileName, "w")) ==NULL )
          {
            dwc_ddrphy_phyinit_assert(0, "%s Error:  Can't open file for writing %s/\n\n", printf_header, outFileName);
          }
        else 
          {
            printf("%s writing output file: %s\n\n", printf_header, outFileName);
          }
    return 0;
}

int dwc_ddrphy_phyinit_end_log () {
    fclose(outFilePtr);
    return 0;
}
