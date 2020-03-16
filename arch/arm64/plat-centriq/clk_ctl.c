#include <target/bitops.h>
#include <target/clk.h>

void __clk_config_root(caddr_t cmd_rcgr, uint8_t clk_sel,
				 uint8_t hid, uint32_t m, uint32_t n,
				 uint8_t mode)
{
	if (m && m < n) {
		__raw_writel(m, RCG_M(cmd_rcgr));
		__raw_writel(~(n - m), RCG_N(cmd_rcgr));
		__raw_writel(~n, RCG_D(cmd_rcgr));
	} else {
		mode = RCG_MODE_BYPASS;
	}
	__raw_writel(RCG_MODE(mode) | RCG_SRC_SEL(clk_sel) |
		     RCG_SRC_DIV(hid), RCG_CFG_RCGR(((uint64_t)cmd_rcgr)));
}

void __clk_generate_mnd(caddr_t cmd_rcgr, uint8_t clk_sel,
				  uint32_t input_hz, uint32_t output_hz,
				  uint8_t mode, uint16_t mnd_mask)
{
	uint8_t hid = 0;
	uint32_t m, n, n1, g;
	uint32_t output_hz1, output_err, err_last;
	uint32_t div_input_hz;
	uint32_t max_mnd = (uint32_t)mnd_mask;

	/* This is not a frequency multiplexer */
	/* BUG_ON(output_hz > input_hz); */

	/* try to avoid overlows */
	if (input_hz > max_mnd) {
		g = gcd32u(input_hz, output_hz);
		input_hz /= g;
		output_hz /= g;
	}
	div_input_hz = input_hz;
	while ((div_input_hz / output_hz) > max_mnd) {
		hid++;
		div_input_hz = RCG_HID_OUT_HZ(input_hz, hid);
	}
	input_hz = div_input_hz;

	/* fast path: GCD */
	if (input_hz <= max_mnd) {
		n = input_hz;
		m = output_hz;
		goto do_cfg_clk;
	}

	/* slow path: calibration */
	n = input_hz / output_hz;
	m = 1;
	err_last = output_hz;
	do {
		output_hz1 = input_hz * m / n;
		if (output_hz1 < output_hz)
			output_err = output_hz - output_hz1;
		else
			output_err = output_hz1 - output_hz;
		if (!output_err)
			break;
		if (output_err < err_last)
			err_last = output_err;
		else
			break;
		n1 = input_hz / output_err;
		if (output_hz1 < output_hz)
			m = n + n1 * m;
		else
			m = n1 * m - n;
		n *= n1;
		while (n > max_mnd) {
			g = min(__roundup32(n / (max_mnd + 1)), m);
			n /= g;
			m /= g;
		}
	} while (1);

do_cfg_clk:
	__clk_config_root(cmd_rcgr, clk_sel, hid, m, n, mode);
}

void __clk_generate_hid(caddr_t cmd_rcgr, uint8_t clk_sel,
				  uint32_t input_hz, uint32_t output_hz,
				  uint8_t mode)
{
	uint8_t hid = 0;

	if (input_hz != output_hz || mode != RCG_MODE_BYPASS)
		hid = ((input_hz * 2) / output_hz) - 1;
	__clk_config_root(cmd_rcgr, clk_sel, hid, 0, 0, RCG_MODE_BYPASS);
}
