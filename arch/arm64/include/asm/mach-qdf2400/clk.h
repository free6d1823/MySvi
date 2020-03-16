/* QDF2400 clock controller driver
 */
#ifndef __CLK_QDF2400_H_INLCUDE__
#define __CLK_QDF2400_H_INLCUDE__

#define INVALID_FREQ		((uint32_t)-1)

/* Padring reference clocks */
#define FREQ_WEST_XO		20000000
#define FREQ_EAST_XO		20000000

#include <asm/mach/gccmw.h>
#include <asm/mach/gcce.h>
#include <asm/mach/pcc.h>
#include <asm/mach/imccc.h>
#include <asm/mach/gccms.h>
#include <asm/mach/pciecc.h>

#define __clk_rcgr_reversed(cmd_rcgr)	\
	(!!((cmd_rcgr) == (PCC_I2C_CMD_RCGR(PCC_BLSP1_QUP0))))

#define NR_PLLS			4
#include <asm/plat-centriq/clk_ctl.h>

#endif /* __CLK_QDF2400_H_INCLUDE__ */
