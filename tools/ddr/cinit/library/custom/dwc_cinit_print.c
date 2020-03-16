#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "dwc_cinit_custom.h"

extern FILE *outFilePtr;

void dwc_cinit_print (const char *fmt,...)
{
  va_list argptr;
  if(outFilePtr==NULL) {
      dwc_cinit_log();
  }
  va_start(argptr,fmt);
  vfprintf(outFilePtr,fmt, argptr);
  va_end(argptr);
  return;
}
