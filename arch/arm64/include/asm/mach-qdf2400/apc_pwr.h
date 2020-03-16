#ifndef APC_PWR_H
#define APC_PWR_H

#ifdef CONFIG_SPM_CFG
void apcpwr_init(void);
void pwr_domain_on_finish(void);
#else
static inline void apcpwr_init(void)
{}

static inline void pwr_domain_on_finish(void)
 {}
#endif

void core_entry_lowpower(unsigned int power_state);
int apcpwr_cpu_wakeup(unsigned long cpu);
int pwr_domain_on(uint64_t mpidr);



#endif
