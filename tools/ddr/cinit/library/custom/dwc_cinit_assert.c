#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "dwc_cinit_custom.h"

void dwc_cinit_assert (int Svrty, const char *fmt,...)
{
  char *PreStr;
  PreStr = (Svrty==0) ? "[Error]" : "[Warning]";
  va_list argptr;

  va_start(argptr,fmt);
  vprintf(PreStr, argptr);
  vprintf(fmt, argptr);
  va_end(argptr);

  if (Svrty==0) exit(EXIT_FAILURE); else return;
}
