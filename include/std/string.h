#ifndef	_STRING_H
#define	_STRING_H

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
#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) \
 || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) \
 || defined(_BSD_SOURCE)
#define __NEED_locale_t
#endif

#include <bits/alltypes.h>
#include <ctype.h>

void *memcpy(void *, const void *, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
int memcmp(const void *, const void *, size_t);
void *memchr(const void *, int, size_t);
size_t memscpy(void *dst, size_t dst_size, const void *src, size_t src_size);

char *strcpy(char *, const char *);
char *strncpy(char *, const char *, size_t);

char *strcat(char *, const char *);
char *strncat(char *, const char *, size_t);

int strcmp(const char *, const char *);
int strncmp(const char *, const char *, size_t);

char *strchr(const char *, int);
char *strrchr(const char *, int);

size_t strcspn(const char *, const char *);
size_t strspn(const char *, const char *);
char *strpbrk(const char *, const char *);
char *strstr(const char *, const char *);
char *strtok(char *, const char *);

size_t strlen(const char *);
size_t strnlen(const char *, size_t);
size_t strlcat (char *, const char *, size_t);
size_t strlcpy (char *, const char *, size_t);

#ifdef __cplusplus
}
#endif

#endif
