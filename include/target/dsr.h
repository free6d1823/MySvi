/*
 */
#ifndef __TESTOS_DSR_H_INCLUDE__
#define __TESTOS_DSR_H_INCLUDE__

#include <stdbool.h>

typedef void (*dsr_handler)(void);

struct dsr {
	dsr_handler handler;
	bool scheduled;
};

#define MAX_DSRS	7
#define INVALID_DSR	MAX_DSRS

static inline int dsr_init(void)
{
	return 0;
}

int dsr_run_once(int dsr);
void dsr_loop(void);
void dsr_schedule(int dsr);
int dsr_register(dsr_handler handler);

extern bool dsr_async;

#endif /* __TESTOS_DSR_H_INCLUDE__ */
