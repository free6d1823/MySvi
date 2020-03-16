/*
 */
#ifndef __TESTOS_DEBUG_H_INCLUDE__
#define __TESTOS_DEBUG_H_INCLUDE__

#include <stdio.h>
#include <target/smp.h>

#define BUG_ON(expr)					\
	do {						\
		if (expr)				\
			printf("BUG(%d) %s(%d)\n",	\
			       hmp_processor_id(),	\
			       __FILE__, __LINE__);	\
	} while (0)

#define DEBUG_BUFFER_SIZE	512

int console_early_init(void);
int console_late_init(void);
void console_handle_irq(void);


#endif /* __TESTOS_DEBUG_H_INCLUDE__ */
