#ifndef _STDLIB_H
#define _STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL 0L
#else
#define NULL ((void*)0)
#endif
#endif

#define __NEED_size_t
#define __NEED_wchar_t

#include <bits/alltypes.h>

#ifndef __ASSEMBLY__

int atoi(const char *);
long atol(const char *);
long long atoll(const char *);
double atof(const char *);

float strtof(const char *__restrict, char **__restrict);
double strtod(const char *__restrict, char **__restrict);
long double strtold(const char *__restrict, char **__restrict);

long strtol(const char *__restrict, char **__restrict, int);
unsigned long strtoul(const char *__restrict, char **__restrict, int);
long long strtoll(const char *__restrict, char **__restrict, int);
unsigned long long strtoull(const char *__restrict, char **__restrict, int);

int rand(void);
void srand(unsigned);

void *malloc(size_t);
void *calloc(size_t, size_t);
void *realloc (void *, size_t);
void free(void *);
void *aligned_alloc(size_t alignment, size_t size);

#ifdef CONFIG_DMM
#undef malloc
#undef free
#define malloc dmalloc
#define free dfree
#endif /* CONFIG_DMM */

#endif /* __ASSEMBLY__ */

#define RAND_MAX (0x7fffffff)

#ifdef __cplusplus
}
#endif

#endif
