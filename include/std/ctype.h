#ifndef	_CTYPE_H
#define	_CTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define isspace(c)	((c) == ' ' || ((c) >= '\t' && (c) <= '\r'))
#define isascii(c)	(((c) & ~0x7f) == 0)
#define isupper(c)	((c) >= 'A' && (c) <= 'Z')
#define islower(c)	((c) >= 'a' && (c) <= 'z')
#define isalpha(c)	(isupper(c) || islower(c))
#define isdigit(c)	((c) >= '0' && (c) <= '9')
#define isxdigit(c)	(isdigit(c) \
			  || ((c) >= 'A' && (c) <= 'F') \
			  || ((c) >= 'a' && (c) <= 'f'))
#define isprint(c)	((c) >= ' ' && (c) <= '~')
#define isgraph(c)	(((c)-0x21) < 0x5e)
#define isblank(c)	(c == ' ' || c == '\t')

#define toupper(c)	((c) - 0x20 * (((c) >= 'a') && ((c) <= 'z')))
#define tolower(c)	((c) + 0x20 * (((c) >= 'A') && ((c) <= 'Z')))

#ifndef __ASSEMBLY__
int   isalnum(int);
int   iscntrl(int);
int   ispunct(int);
int   toascii(int);
#endif /* __ASSEMBLY__ */

#ifdef __cplusplus
}
#endif

#endif
