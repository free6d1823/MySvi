/*
 */
#ifndef __TESTOS_DSR_H_INCLUDE__
#define __TESTOS_DSR_H_INCLUDE__

typedef void (*dsr_handler)(void *ctx);

#define MAX_DSRS	7
#define INVALID_DSR	MAX_DSRS

static inline int dsr_init(void)
{
	return 0;
}

int dsr_run_once(int dsr);
void dsr_loop(void);
void dsr_schedule(int dsr);
int dsr_register(dsr_handler handler, void *ctx);

#endif /* __TESTOS_DSR_H_INCLUDE__ */
