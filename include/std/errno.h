#ifndef	_ERRNO_H
#define _ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#include <asm-generic/errno.h>

#ifndef __ASSEMBLY__
extern int errno;
#endif /* __ASSEMBLY__ */

#ifdef __cplusplus
}
#endif

#endif

