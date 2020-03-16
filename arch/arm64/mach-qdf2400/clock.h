#ifndef __QDF2400_CLOCK_HMSS_H_INCLUDE__
#define __QDF2400_CLOCK_HMSS_H_INCLUDE__

#include <stdint.h>
#include <asm/hal/HALhwio.h>
#include <asm/mach/hal/HALclkHWIO.h>
#include <target/clock.h>
#include <asm/plat-centriq/freqplan.h>

#define CLK_ENABLE_MSK 0x00000001
#define CLK_OFF_MSK    0x80000000

/*
 * RCGR update timeout. In practice this should be very short (less than 1us),
 * but it depends on the clock frequency being fed into the RCG. Choosing
 * a very conservative value.
 */
#define CLOCK_UPDATE_TIMEOUT_US 1000

/*
 * CLOCK_PLL_INIT_TIME_US
 *
 * Init time in microseconds after de-asserting PLL reset (normal mode).
 */
#define CLOCK_PLL_INIT_TIME_US 5

/*
 * NOT_2D / NOT_N_MINUS_M
 *
 * Macros to return the inverted value of the 2D field or (N - M)
 * in a type 1 mux structure.  Used to prepare the value for writing
 * to the hardware register field.
 */
#define NOT_2D(mux)         (~(mux)->n2D)
#define NOT_N_MINUS_M(mux)  (~((mux)->nN - (mux)->nM))

/*
 * HALF_DIVIDER
 *
 * Macro to return the normalized half divider for a given mux structure.
 * NOTE: Expecting (2 * divider) value as input.
 */
#define HALF_DIVIDER(mux)  ((mux)->nDiv2x ? (((mux)->nDiv2x) - 1) : 0)


/* Definitions for generalizing clock configuration */
#define CLOCK_CMD_CFG_UPDATE_FMSK   HWIO_FMSK(GCC_SDCC2_APPS_CMD_RCGR, UPDATE)

#define CLOCK_CFG_REG_OFFSET        (HWIO_ADDR(GCC_SDCC2_APPS_CFG_RCGR)-HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR))
#define CLOCK_CFG_RCGR_SRC_SEL_FMSK  HWIO_FMSK(GCC_SDCC2_APPS_CFG_RCGR, SRC_SEL)
#define CLOCK_CFG_RCGR_SRC_SEL_SHFT  HWIO_SHFT(GCC_SDCC2_APPS_CFG_RCGR, SRC_SEL)
#define CLOCK_CFG_RCGR_SRC_DIV_FMSK  HWIO_FMSK(GCC_SDCC2_APPS_CFG_RCGR, SRC_DIV)
#define CLOCK_CFG_RCGR_SRC_DIV_SHFT  HWIO_SHFT(GCC_SDCC2_APPS_CFG_RCGR, SRC_DIV)

#define CLOCK_CFG_RCGR_MODE_FMSK     HWIO_FMSK(GCC_SDCC2_APPS_CFG_RCGR, MODE)
#define CLOCK_CFG_RCGR_MODE_SHFT     HWIO_SHFT(GCC_SDCC2_APPS_CFG_RCGR, MODE)
#define CLOCK_CFG_RCGR_MODE_DUAL_EDGE_VAL  0x2
#define CLOCK_CFG_RCGR_MODE_BYPASS_VAL     0x0

#define CLOCK_M_REG_OFFSET         (HWIO_ADDR(GCC_SDCC2_APPS_M)-HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR))
#define CLOCK_N_REG_OFFSET         (HWIO_ADDR(GCC_SDCC2_APPS_N)-HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR))
#define CLOCK_D_REG_OFFSET         (HWIO_ADDR(GCC_SDCC2_APPS_D)-HWIO_ADDR(GCC_SDCC2_APPS_CMD_RCGR))

extern uint32_t               Qdf2400V10PLLCfg[];
extern uintptr_t              Qdf2400V10CBCRs[];
extern struct ClockCfg        Qdf2400V10CdivCfg[];
extern struct ClockCfg        Qdf2400V10MuxCfg[];
extern clk_ctl_cfg		Qdf2400V10RcgCfg[];

extern uint32_t               Qdf2400V11PLLCfg[];
extern uintptr_t              Qdf2400V11CBCRs[];
extern struct ClockCfg        Qdf2400V11CdivCfg[];
extern struct ClockCfg        Qdf2400V11MuxCfg[];
extern clk_ctl_cfg		Qdf2400V11RcgCfg[];

extern uint32_t               Qdf2400V20PLLCfg[];
extern uintptr_t              Qdf2400V20CBCRs[];
extern struct ClockCfg        Qdf2400V20CdivCfg[];
extern struct ClockCfg        Qdf2400V20MuxCfg[];
extern clk_ctl_cfg		Qdf2400V20RcgCfg[];

#endif /* __QDF2400_CLOCK_HMSS_H_INCLUDE__ */
