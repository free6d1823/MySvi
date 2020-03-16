#include <stdarg.h>
#include <stdio.h>

#define log_level 4

int monaco_log(int importance, const char * fmt, ...)
{
    va_list vargs;
    int ret_val = 0;

    if(importance >= log_level)
    {
        va_start(vargs, fmt);
        ret_val = vprintf(fmt, vargs);
        va_end(vargs);
    }

    return ret_val;
}
