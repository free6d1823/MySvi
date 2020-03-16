#ifndef __WORDSIZE_H__
#define __WORDSIZE_H__

#ifndef __WORDSIZE

#ifdef __LP64__
#define __WORDSIZE	64
#endif

#ifdef __ILP32__
#define __WORDSIZE	32
#endif

#endif


#ifndef __WORDSIZE

#if __SIZEOF_LONG__ == 8
#define __WORDSIZE	64
#elif __SIZEOF_LONG__ == 4
#define __WORDSIZE	32
#endif

#endif


#ifndef __WORDSIZE
#error __WORDSIZE is not defined.
#endif

#endif /* __WORDSIZE_H__ */
