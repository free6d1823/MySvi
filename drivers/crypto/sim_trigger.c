#define PRF_REG_BASE 	0x58040000
#define SE1K_QUIT    	0x04
#define SE1K_START		0x80
#define SE1K_FINISH		0x81
#define SE1K_FAIL		0x82
#define SE1K_PASS		0x83

//report start
void sim_start()
{
	*(volatile int *)PRF_REG_BASE = SE1K_START;
}

//report finish but don't quit the simulation
void sim_finish()
{
	*(volatile int *)PRF_REG_BASE = SE1K_FINISH;
}

//report fail and quit the simulation
void sim_fail()
{
	*(volatile int *)PRF_REG_BASE = SE1K_FAIL;
	*(volatile int *)PRF_REG_BASE = SE1K_QUIT;
}

//report pass and quit the simulation
void sim_pass()
{
	*(volatile int *)PRF_REG_BASE = SE1K_PASS;
	*(volatile int *)PRF_REG_BASE = SE1K_QUIT;
}

//used for C program communicates with sv synchronously
void trigger(int trigger_number)
{
	*(volatile int *)PRF_REG_BASE = SE1K_PASS+trigger_number;
}


