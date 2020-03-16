#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "dwc_cinit_custom.h"

extern FILE *outFilePtr;

void dwc_cinit_print (const char *fmt,...)
{
  va_list argptr;

  va_start(argptr,fmt);
  printf(fmt, argptr);
  va_end(argptr);
  
  return;
}
