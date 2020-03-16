/* Centriq platform clock controller driver
 */
#ifndef __CLK_CTL_CENTRIQ_H_INCLUDE__
#define __CLK_CTL_CENTRIQ_H_INCLUDE__

#include <asm/io.h>

/* CC: Clock controller block definitions */

/* CBC: Clock Branch Controller */
/* CBCR */
#define CBC_CLK_OFF			_BV(31)
#define CBC_CLK_ENABLE			_BV(0)

/* RCG: Root Clock Generator */
#define RCG_REG_OFFSET_CMD_RCGR		0x00
#define RCG_REG_OFFSET_CFG_RCGR		0x04
#define RCG_REG_OFFSET_M		0x08
#define RCG_REG_OFFSET_N		0x0C
#define RCG_REG_OFFSET_D		0x10

/* CMD_RCGR */
#define RCG_ROOT_OFF			_BV(31)
#define RCG_DIRTY_D			_BV(7)
#define RCG_DIRTY_M			_BV(6)
#define RCG_DIRTY_N			_BV(5)
#define RCG_DIRTY_CFG_RCFR		_BV(4)
#define RCG_ROOT_EN			_BV(1)
#define RCG_UPDATE			_BV(0)

/* CFG_RCGR */
#define RCG_MODE_OFFSET			12
#define RCG_MODE_MASK			0x03
#define RCG_MODE(value)			_SET_FV(RCG_MODE, value)
/* MODE field is only used for MND clock divider function
 * (__clock_generate_mnd()). However, a non RCG_MODE_BYPASS value can be
 * used to tell an HID divider function (__clock_generate_hid()) to use a
 * non bypass mode HID value.
 */
#define RCG_MODE_BYPASS			0
#define RCG_MODE_SWALLOW		1
#define RCG_MODE_DUAL_EDGE		2
#define RCG_MODE_SINGLE_EDGE		3
#define RCG_SRC_SEL_OFFSET		8
#define RCG_SRC_SEL_MASK		0x07
#define RCG_SRC_SEL(value)		_SET_FV(RCG_SRC_SEL, value)
/* Half integer divider */
#define RCG_SRC_DIV_OFFSET		0
#define RCG_SRC_DIV_MASK		0x1F
#define RCG_SRC_DIV(value)		_SET_FV(RCG_SRC_DIV, value)

/* RCG can have HID and MND divider:
 * HID is configured via SRC_DIV field of CFG_RCGR registers
 * MND is configured via M/N/D registers
 * MND algorithm:
 *  CLK_OUT = CLK_IN * M / N
 *  REG_M = M, REG_N = ~(N-M), REG_D = ~N
 */
#define RCG_MND_OUT_HZ(input_hz, n, m)	\
	(((input_hz) / n) * m)
#define RCG_HID_OUT_HZ(input_hz, hid)	\
	((hid) ? (input_hz) * 2 / ((hid) + 1) : (input_hz))

#define RCG_HID_DIV_MAX			16

#define RCG_CMD_RCGR(cmd_rcgr)				\
	(__clk_rcgr_reversed(cmd_rcgr) ?		\
	 ((cmd_rcgr) + RCG_REG_OFFSET_CFG_RCGR) :	\
	 (cmd_rcgr))
#define RCG_CFG_RCGR(cmd_rcgr)				\
	(__clk_rcgr_reversed(cmd_rcgr) ?		\
	 (cmd_rcgr) :					\
	 ((cmd_rcgr) + RCG_REG_OFFSET_CFG_RCGR))
#define RCG_M(cmd_rcgr)		((cmd_rcgr) + RCG_REG_OFFSET_M)
#define RCG_N(cmd_rcgr) 	((cmd_rcgr) + RCG_REG_OFFSET_N)
#define RCG_D(cmd_rcgr) 	((cmd_rcgr) + RCG_REG_OFFSET_D)

#define __clk_enable_branch(cbcr)	\
	__raw_setl(CBC_CLK_ENABLE, (cbcr))
#define __clk_update_root(cmd_rcgr)	\
	__raw_setl(RCG_UPDATE, RCG_CMD_RCGR(cmd_rcgr))
#define __clk_enable_root(cmd_rcgr)	\
	__raw_setl(RCG_ROOT_EN, RCG_CMD_RCGR(cmd_rcgr))
#define __clk_disable_root(cmd_rcgr)	\
	__raw_clearl(RCG_ROOT_EN, RCG_CMD_RCGR(cmd_rcgr))

void __clk_config_root(caddr_t cmd_rcgr, uint8_t clk_sel, uint8_t hid,
		       uint32_t m, uint32_t n, uint8_t mode);
void __clk_generate_mnd(caddr_t cmd_rcgr, uint8_t clk_sel,
			uint32_t input_hz, uint32_t output_hz,
			uint8_t mode, uint16_t mnd_mask);
void __clk_generate_hid(caddr_t cmd_rcgr, uint8_t clk_sel,
			uint32_t input_hz, uint32_t output_hz,
			uint8_t mode);

#endif /* __CLK_CTL_CENTRIQ_H_INCLUDE__ */
