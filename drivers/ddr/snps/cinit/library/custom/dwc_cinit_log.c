#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "dwc_cinit_custom.h"

extern FILE *outFilePtr;

void dwc_cinit_log () {
    char *outFileName="dwc_cinit.log";
    char *printf_header;
    printf_header = "// [dwc_cinit]";
    if(outFilePtr!=NULL) {
        return; // log is already open.
    }
    // Open Txt output Stream 
    if ( (outFilePtr=fopen(outFileName, "w")) ==NULL )
    {
       dwc_cinit_assert(0, "%s Error:  Can't open file for writing %s/\n\n", printf_header, outFileName);

    }
    else 
    {
        printf("%s writing output file: %s\n\n", printf_header, outFileName);
    }
}

void dwc_cinit_end_log () {
    fclose(outFilePtr);
}


