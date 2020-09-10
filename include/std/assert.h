#ifndef __ASSERT_H_INCLUDE__
#define __ASSERT_H_INCLUDE__

#include <stdio.h>
#include <target/smp.h>

#define BUG_ON(expr)					\
	do {						\
		if (expr)				\
			printf("BUG(%d) %s(%d)\n",	\
			       hmp_processor_id(),	\
			       __FILE__, __LINE__);	\
	} while (0)

#define	assert(x)					\
	do {						\
		if (!(x)) {				\
			BUG_ON(!(x)); 			\
			while(1);			\
		}					\
	} while (0)


#endif

