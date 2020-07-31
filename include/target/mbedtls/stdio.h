#ifndef __GNU_STDIO_H
#define __GNU_STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdarg.h>
#include <bits/alltypes.h>

#ifndef __ASSEMBLY__

int sprintf(char *, const char *, ...);
int snprintf(char *, size_t, const char *, ...);
int vsprintf(char *, const char *, va_list);
int vsnprintf(char *, size_t, const char *, va_list);

int sscanf(const char *, const char *, ...);
int vsscanf(const char *, const char *, va_list);


int getchar(void);
int putchar(int c);
int puts(const char *s);

int printf(const char *format, ...);
int vprintf (const char *format, va_list arg);

int scanf(const char *format, ...);
int vscanf(const char *format, va_list arg);

/* CONSOLE IO */
#define getch getchar
#define putch putchar

/* Hackish definition as prototypes of getc/putc are entirely different
 * from getchar/putchar. Only used by libcui.a.
 */
#define getc getchar
#define putc putchar

int fprintf(void *fp, const char *fmt, ...);
#define stderr	NULL
#define stdout	NULL

#else /* __ASSEMBLY__ */

.extern getchar
.extern putchar

#endif /* __ASSEMBLY__ */

#ifdef __cplusplus
}
#endif

#endif
