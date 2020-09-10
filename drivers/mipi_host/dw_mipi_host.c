#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <target/cmdline.h>
#include <target/regdef.h>
#include <target/utils.h>
#include <target/bitops.h>
#include <target/lopoll.h>
#include <target/mipi_dsi.h>
#include <target/mipi_display.h>
#include <target/memory.h>
#include "dw_mipi_host.h"

#define MSB_DPHY_TESTCODE(a)    ((a & 0xf00) >> 8)
#define LSB_DPHY_TESTCODE(a)    (a & 0xff)

#define DPHY_TX_SYS_0	0x001
#define DPHY_TX_SYS_1	0x002
#define DPHY_TX_PLL_25	0x176
#define DPHY_TX_CB2		0x1ac
#define DPHY_TX_CB3		0x1ad
#define DPHY_TX_SLEW_0	0x26b
#define DPHY_TX_SLEW_7	0x272

#define MSEC_PER_SEC	1000L
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

struct clk {
	int clock;     /* in kHz */
};

struct dphy_pll_parameter_map {
	unsigned int max_mbps;
	u8 hsfreqrange;
	u8 icpctrl;
	u8 lpfctrl;
};

struct dw_mipi_dsi_host;
struct dw_mipi_dsi_phy {
	int pllref_clock;
	u16 input_div;          /* PLL Input Divider Ratio */
	u16 feedback_div;       /* PLL Loop Divider Ratio */
	u8 vcorange;	        /* VCO Range Selection */
	u8 icpctrl;	            /* Charge Pump Current Control */
	u8 lpfctrl;	            /* Loop Filter Zero Control */
	u8 vcocap;	            /* VCO Internal Capacitance Control */

	int (*init)(struct dw_mipi_dsi_host *host);
	int (*get_lane_mbps)(struct dw_mipi_dsi_host *host,
			     const struct drm_display_mode *mode,
			     unsigned int *lane_mbps);
};

struct dw_mipi_dsi_host {
	void *base;

	struct clk *pclk, *pllref_clk;

	unsigned int lane_mbps; /* per lane */
	u32 channel;
	u32 lanes;
	u32 format;
	unsigned long mode_flags;

	struct dw_mipi_dsi_phy phy;

	int (*device_attach)(struct dw_mipi_dsi_host *host,
		struct mipi_panel_device *panel);
	ssize_t (*transfer)(struct dw_mipi_dsi_host *host,
			    const struct mipi_dsi_msg *msg);
};

static inline u32 dsi_read(struct dw_mipi_dsi_host *host, u32 reg)
{
	return readl(host->base + reg);
}

static inline void dsi_write(struct dw_mipi_dsi_host *host, u32 reg, u32 val)
{
	writel(val, host->base + reg);
}
static void dw_mipi_dsi_dphy_psel(struct dw_mipi_dsi_host *host,
				u8 sel)
{
	dsi_write(host, DSI_PHY_TST_CTRL1, PHY_TESTEN);

	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_TESTCLK);
	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR );

	dsi_write(host, DSI_PHY_TST_CTRL1, PHY_UNTESTEN | sel);

	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_TESTCLK);
	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR);
}

static void dw_mipi_dsi_phy_write(struct dw_mipi_dsi_host *host,
				  u16 test_code,
				  u8 test_data)
{
	/*
	 * With the falling edge on TESTCLK, the TESTDIN[7:0] signal content
	 * is latched internally as the current test code. Test data is
	 * programmed internally by rising edge on TESTCLK.
	 */
#if 0
	dsi_write(host, DSI_PHY_TST_CTRL0,  | PHY_UNTESTCLR);

	dsi_write(host, DSI_PHY_TST_CTRL1, PHY_TESTEN | PHY_TESTDOUT(0) |
					  PHY_TESTDIN(test_code));

	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLK | PHY_UNTESTCLR);

	dsi_write(host, DSI_PHY_TST_CTRL1, PHY_UNTESTEN | PHY_TESTDOUT(0) |
					  PHY_TESTDIN(test_data));

	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_TESTCLK | PHY_UNTESTCLR);
#endif

	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLK | PHY_UNTESTCLR);
	dsi_write(host, DSI_PHY_TST_CTRL1, PHY_TESTEN | LSB_DPHY_TESTCODE(test_code));
	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_TESTCLK);
	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR );

	//dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLK | PHY_UNTESTCLR);
	dsi_write(host, DSI_PHY_TST_CTRL1, PHY_UNTESTEN | PHY_TESTDIN(test_data));
	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_TESTCLK);
	dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR );

}

/* The table is based on 27MHz DPHY pll reference clock. */
static const struct dphy_pll_parameter_map dppa_map[] = {
	{ 100, 0x20, CP_CURRENT_12UA, LPF_RESISTORS_8KOHM },
	{ 900, 0x29, CP_CURRENT_12UA, LPF_RESISTORS_8KOHM },
	{1250, 0x1b, CP_CURRENT_12UA, LPF_RESISTORS_8KOHM },
	{1500, 0x2c, CP_CURRENT_12UA, LPF_RESISTORS_8KOHM },
	{1800, 0x0e, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM },
	{2100, 0x41, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM },
	{2400, 0x47, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM },
	{2500, 0x49, CP_CURRENT_12UA, LPF_RESISTORS_10_5KOHM },
};

static int max_mbps_to_parameter(unsigned int max_mbps)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dppa_map); i++)
		if (dppa_map[i].max_mbps >= max_mbps)
			return i;

	return -1;
}

static inline int mipi_dsi_pixel_format_to_bpp(enum mipi_dsi_pixel_format fmt)
{
	switch (fmt) {
	case MIPI_DSI_FMT_RGB888:
	case MIPI_DSI_FMT_RGB666:
		return 24;

	case MIPI_DSI_FMT_RGB666_PACKED:
		return 18;

	case MIPI_DSI_FMT_RGB565:
		return 16;
	}

	return -1;
}

static void dphy_pll_config()
{
	void __iomem *addr;

	addr= (void __iomem *)MDP_MISC_REG_BASE + 0x1c8;
	writel(1, addr);

	addr = (void __iomem *)MDP_MISC_REG_BASE + 0x1c0;
	writel(1, addr);
}

static int dw_mipi_dsi_phy_init(struct dw_mipi_dsi_host *host)
{
	/* enable phy_cfg_clk */

	/*
	* We need set PLL_INPUT_AND_LOOP_DIVIDER_RATIOS_CONTROL immediately
	* to make the configured LSB effective according to IP simulation
	* and lab test results.
	* Only in this way can we get correct mipi phy pll frequency.
	*/
	dw_mipi_dsi_dphy_psel(host, 0x0);
	dw_mipi_dsi_phy_write(host, DPHY_TX_SYS_0, 0x20);
	dw_mipi_dsi_phy_write(host, DPHY_TX_SYS_1, 0x49);

	dw_mipi_dsi_dphy_psel(host, 0x2);
	dw_mipi_dsi_phy_write(host, DPHY_TX_SLEW_0, 0x04);
	dw_mipi_dsi_phy_write(host, DPHY_TX_SLEW_7, 0x00);

	dw_mipi_dsi_dphy_psel(host, 0x1);
	dw_mipi_dsi_phy_write(host, DPHY_TX_CB3, 0x01);
	dw_mipi_dsi_phy_write(host, DPHY_TX_PLL_25, 0xc0);
	dw_mipi_dsi_phy_write(host, DPHY_TX_CB2, 0x10);

	dphy_pll_config();
	return 0;
}

static int
dw_mipi_dsi_phy_get_lane_mbps(struct dw_mipi_dsi_host *host, const struct drm_display_mode *mode,
			  unsigned int *lane_mbps)
{

	unsigned int best_prediv = 10, best_fbdiv = 10;

	/*
	 * 1. bandwidth = mode->clock * bpp
	 * 2. calculate pll parameters based on phy.pllref_clk and bandwidth
	 */
	int bpp;
	unsigned long mpclk, tmp;
	unsigned int target_mbps = 1000;
	unsigned int max_mbps = dppa_map[ARRAY_SIZE(dppa_map) - 1].max_mbps;

	bpp = mipi_dsi_pixel_format_to_bpp(host->format);
	mpclk = DIV_ROUND_UP(mode->clock, MSEC_PER_SEC);
	if (mpclk) {
		/* take 1 / 0.8, since mbps must big than bandwidth of RGB */
		tmp = mpclk * (bpp / host->lanes) * 10 / 8;
		if (tmp < max_mbps)
			target_mbps = tmp;
		else
			printf("DPHY clock frequency is out of range\n");
	}

	*lane_mbps = target_mbps;

	host->phy.input_div = best_prediv;
	host->phy.feedback_div = best_fbdiv;

	return 0;
}

static void dw_mipi_dsi_init(struct dw_mipi_dsi_host *host)
{
  /*
   * The maximum permitted escape clock is 20MHz and it is derived from
   * lanebyteclk, which is running at "lane_mbps / 8".	Thus we want:
   *
   *	 (lane_mbps >> 3) / esc_clk_division < 20
   * which is:
   *	 (lane_mbps >> 3) / 20 > esc_clk_division
   */
  u32 esc_clk_division = (host->lane_mbps >> 3) / 20 + 1;

  dsi_write(host, DSI_PWR_UP, RESET);

  /*
   * TODO dw drv improvements
   * timeout clock division should be computed with the
   * high speed transmission counter timeout and byte lane...
   */
  dsi_write(host, DSI_CLKMGR_CFG, TO_CLK_DIVISION(10) |
		TX_ESC_CLK_DIVISION(esc_clk_division));
}

static void dw_mipi_dsi_dpi_config(struct dw_mipi_dsi_host *host,
				   const struct drm_display_mode *mode)
{
	u32 val = 0, color = 0;

	switch (host->format) {
	case MIPI_DSI_FMT_RGB888:
		color = DPI_COLOR_CODING_24BIT;
		break;
	case MIPI_DSI_FMT_RGB666:
		color = DPI_COLOR_CODING_18BIT_2 | LOOSELY18_EN;
		break;
	case MIPI_DSI_FMT_RGB666_PACKED:
		color = DPI_COLOR_CODING_18BIT_1;
		break;
	case MIPI_DSI_FMT_RGB565:
		color = DPI_COLOR_CODING_16BIT_1;
		break;
	}

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		val |= VSYNC_ACTIVE_LOW;
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		val |= HSYNC_ACTIVE_LOW;

	dsi_write(host, DSI_DPI_VCID, DPI_VCID(host->channel));
	dsi_write(host, DSI_DPI_COLOR_CODING, color);
	dsi_write(host, DSI_DPI_CFG_POL, val);
	/*
	 * TODO dw drv improvements
	 * largest packet sizes during hfp or during vsa/vpb/vfp
	 * should be computed according to byte lane, lane number and only
	 * if sending lp cmds in high speed is enable (PHY_TXREQUESTCLKHS)
	 */
	dsi_write(host, DSI_DPI_LP_CMD_TIM, OUTVACT_LPCMD_TIME(4)
		  | INVACT_LPCMD_TIME(4));
}

static void dw_mipi_dsi_packet_handler_config(struct dw_mipi_dsi_host *host)
{
   dsi_write(host, DSI_PCKHDL_CFG, CRC_RX_EN | ECC_RX_EN | BTA_EN);
}

static void dw_mipi_dsi_video_mode_config(struct dw_mipi_dsi_host *host)
{
	u32 val;

	/*
	 * TODO dw drv improvements
	 * enabling low power is panel-dependent, we should use the
	 * panel configuration here...
	 */
	val = ENABLE_LOW_POWER;

	if (host->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		val |= VID_MODE_TYPE_BURST;
	else if (host->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		val |= VID_MODE_TYPE_NON_BURST_SYNC_PULSES;
	else
		val |= VID_MODE_TYPE_NON_BURST_SYNC_EVENTS;

	dsi_write(host, DSI_VID_MODE_CFG, val);
}

static void dw_mipi_dsi_video_packet_config(struct dw_mipi_dsi_host *host,
					    const struct drm_display_mode *mode)
{
	/*
	 * TODO dw drv improvements
	 * only burst mode is supported here. For non-burst video modes,
	 * we should compute DSI_VID_PKT_SIZE, DSI_VCCR.NUMC &
	 * DSI_VNPCR.NPSIZE... especially because this driver supports
	 * non-burst video modes, see dw_mipi_dsi_video_mode_config()...
	 */

	dsi_write(host, DSI_VID_PKT_SIZE, VID_PKT_SIZE(mode->hdisplay));
}

static void dw_mipi_dsi_command_mode_config(struct dw_mipi_dsi_host *host)
{
	/*
	 * TODO dw drv improvements
	 * compute high speed transmission counter timeout according
	 * to the timeout clock division (TO_CLK_DIVISION) and byte lane...
	 */
	dsi_write(host, DSI_TO_CNT_CFG, HSTX_TO_CNT(1000) | LPRX_TO_CNT(1000));
	/*
	 * TODO dw drv improvements
	 * the Bus-Turn-Around Timeout Counter should be computed
	 * according to byte lane...
	 */
	dsi_write(host, DSI_BTA_TO_CNT, 0xd00);
	dsi_write(host, DSI_MODE_CFG, ENABLE_CMD_MODE);
}

/* Get lane byte clock cycles. */
static u32 dw_mipi_dsi_get_hcomponent_lbcc(struct dw_mipi_dsi_host *host,
					   const struct drm_display_mode *mode,
					   u32 hcomponent)
{
	u32 frac, lbcc;

	lbcc = hcomponent * host->lane_mbps * MSEC_PER_SEC / 8;

	frac = lbcc % mode->clock;
	lbcc = lbcc / mode->clock;
	if (frac)
		lbcc++;

	return lbcc;
}

static void dw_mipi_dsi_line_timer_config(struct dw_mipi_dsi_host *host,
					  const struct drm_display_mode *mode)
{
	u32 htotal, hsa, hbp, lbcc;

	htotal = mode->htotal;
	hsa = mode->hsync_end - mode->hsync_start;
	hbp = mode->htotal - mode->hsync_end;

	/*
	 * TODO dw drv improvements
	 * computations below may be improved...
	 */
	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(host, mode, htotal);
	dsi_write(host, DSI_VID_HLINE_TIME, lbcc);

	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(host, mode, hsa);
	dsi_write(host, DSI_VID_HSA_TIME, lbcc);

	lbcc = dw_mipi_dsi_get_hcomponent_lbcc(host, mode, hbp);
	dsi_write(host, DSI_VID_HBP_TIME, lbcc);
}

static void dw_mipi_dsi_vertical_timing_config(struct dw_mipi_dsi_host *host,
				  const struct drm_display_mode *mode)
{
  u32 vactive, vsa, vfp, vbp;

  vactive = mode->vdisplay;
  vsa = mode->vsync_end - mode->vsync_start;
  vfp = mode->vsync_start - mode->vdisplay;
  vbp = mode->vtotal - mode->vsync_end;

  dsi_write(host, DSI_VID_VACTIVE_LINES, vactive);
  dsi_write(host, DSI_VID_VSA_LINES, vsa);
  dsi_write(host, DSI_VID_VFP_LINES, vfp);
  dsi_write(host, DSI_VID_VBP_LINES, vbp);
}

static void dw_mipi_dsi_dphy_init(struct dw_mipi_dsi_host *host)
{
  /* Clear PHY state */
  dsi_write(host, DSI_PHY_RSTZ, PHY_DISFORCEPLL | PHY_DISABLECLK
		| PHY_RSTZ | PHY_SHUTDOWNZ);
  dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR);
  dsi_write(host, DSI_PHY_TST_CTRL0, PHY_TESTCLR);
  dsi_write(host, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR);
}

static void dw_mipi_dsi_dphy_enable(struct dw_mipi_dsi_host *host)
{
  u32 val;
  int ret;
/*
  dsi_write(host, DSI_PHY_RSTZ, PHY_ENFORCEPLL | PHY_ENABLECLK |
		PHY_UNRSTZ | PHY_UNSHUTDOWNZ);
 */

  dsi_write(host, DSI_PHY_RSTZ, PHY_ENABLECLK);
  dsi_write(host, DSI_PHY_RSTZ, PHY_ENABLECLK | PHY_UNSHUTDOWNZ);
  dsi_write(host, DSI_PHY_RSTZ, PHY_ENABLECLK | PHY_UNSHUTDOWNZ | PHY_UNRSTZ);
  dsi_write(host, DSI_PHY_RSTZ, PHY_ENABLECLK | PHY_UNSHUTDOWNZ | PHY_UNRSTZ | PHY_ENFORCEPLL);

  ret = readl_poll_timeout(host->base + DSI_PHY_STATUS, val,
			   val & PHY_LOCK, PHY_STATUS_TIMEOUT_US);
  if (ret)
	  printf("failed to wait phy lock state\n");

  ret = readl_poll_timeout(host->base + DSI_PHY_STATUS,
			   val, val & PHY_STOP_STATE_CLK_LANE,
			   PHY_STATUS_TIMEOUT_US);
  if (ret)
	  printf("failed to wait phy clk lane stop state\n");
}

static void dw_mipi_dsi_dphy_timing_config(struct dw_mipi_dsi_host *host)
{
	u32 hw_version;

	/*
	 * TODO dw drv improvements
	 * data & clock lane timers should be computed according to panel
	 * blankings and to the automatic clock lane control mode...
	 * note: DSI_PHY_TMR_CFG.MAX_RD_TIME should be in line with
	 * DSI_CMD_MODE_CFG.MAX_RD_PKT_SIZE_LP (see CMD_MODE_ALL_LP)
	 */

	hw_version = dsi_read(host, DSI_VERSION) & VERSION;

	if (hw_version >= HWVER_131) {
		dsi_write(host, DSI_PHY_TMR_CFG, PHY_HS2LP_TIME_V131(0x40) |
			  PHY_LP2HS_TIME_V131(0x40));
		dsi_write(host, DSI_PHY_TMR_RD_CFG, MAX_RD_TIME_V131(10000));
	} else {
		dsi_write(host, DSI_PHY_TMR_CFG, PHY_HS2LP_TIME(0x40) |
			  PHY_LP2HS_TIME(0x40) | MAX_RD_TIME(10000));
	}

	dsi_write(host, DSI_PHY_TMR_LPCLK_CFG, PHY_CLKHS2LP_TIME(0x40)
		  | PHY_CLKLP2HS_TIME(0x40));
}
static void dw_mipi_dsi_dphy_interface_config(struct dw_mipi_dsi_host *host)
{
	/*
	 * TODO dw drv improvements
	 * stop wait time should be the maximum between host dsi
	 * and panel stop wait times
	 */
	dsi_write(host, DSI_PHY_IF_CFG, PHY_STOP_WAIT_TIME(0x20) |
		  N_LANES(host->lanes));
}

static void dw_mipi_dsi_clear_err(struct dw_mipi_dsi_host *host)
{
  dsi_read(host, DSI_INT_ST0);
  dsi_read(host, DSI_INT_ST1);
  dsi_write(host, DSI_INT_MSK0, 0);
  dsi_write(host, DSI_INT_MSK1, 0);
}
/*
 * The controller should generate 2 frames before
 * preparing the peripheral.
 */
static void dw_mipi_dsi_wait_for_two_frames(const struct drm_display_mode *mode)
{
	int refresh, two_frames;

	refresh = mode->vrefresh;
	two_frames = DIV_ROUND_UP(MSEC_PER_SEC, refresh) * 2;
	//msleep(two_frames);
}
static void dw_mipi_dsi_set_mode(struct dw_mipi_dsi_host *host,
				 unsigned long mode_flags)
{
	dsi_write(host, DSI_PWR_UP, RESET);

	if (mode_flags & MIPI_DSI_MODE_VIDEO) {
		dsi_write(host, DSI_MODE_CFG, ENABLE_VIDEO_MODE);
		dw_mipi_dsi_video_mode_config(host);
		dsi_write(host, DSI_LPCLK_CTRL, PHY_TXREQUESTCLKHS);
	} else {
		dsi_write(host, DSI_MODE_CFG, ENABLE_CMD_MODE);
	}

	dsi_write(host, DSI_PWR_UP, POWERUP);
}

static void dw_mipi_dsi_mode_set(struct dw_mipi_dsi_host *host,
				 const struct drm_display_mode *mode)
{
	int ret;

    /* enable apb_clk */

	ret = host->phy.get_lane_mbps(host, mode, &host->lane_mbps);
	if (ret)
		printf("Phy get_lane_mbps() failed\n");

	dw_mipi_dsi_init(host);
	dw_mipi_dsi_dpi_config(host, mode);
	dw_mipi_dsi_packet_handler_config(host);
	dw_mipi_dsi_video_mode_config(host);
	dw_mipi_dsi_video_packet_config(host, mode);
	dw_mipi_dsi_command_mode_config(host);
	dw_mipi_dsi_line_timer_config(host, mode);
	dw_mipi_dsi_vertical_timing_config(host, mode);

	dw_mipi_dsi_dphy_init(host);
	dw_mipi_dsi_dphy_timing_config(host);
	dw_mipi_dsi_dphy_interface_config(host);

	dw_mipi_dsi_clear_err(host);

	ret = host->phy.init(host);
	if (ret)
		printf("Phy init() failed\n");

	dw_mipi_dsi_dphy_enable(host);

	dw_mipi_dsi_wait_for_two_frames(mode);

	/* Switch to cmd mode for panel-bridge pre_enable & panel prepare */
	dw_mipi_dsi_set_mode(host, 1);
}

static void dw_mipi_message_config(struct dw_mipi_dsi_host *host,
				   const struct mipi_dsi_msg *msg)
{
	bool lpm = msg->flags & MIPI_DSI_MSG_USE_LPM;
	u32 val = 0;

	if (msg->flags & MIPI_DSI_MSG_REQ_ACK)
		val |= ACK_RQST_EN;
	if (lpm)
		val |= CMD_MODE_ALL_LP;

	dsi_write(host, DSI_LPCLK_CTRL, lpm ? 0 : PHY_TXREQUESTCLKHS);
	dsi_write(host, DSI_CMD_MODE_CFG, val);
}

static int dw_mipi_dsi_gen_pkt_hdr_write(struct dw_mipi_dsi_host *host, u32 hdr_val)
{
	int ret;
	u32 val, mask;

	ret = readl_poll_timeout(host->base + DSI_CMD_PKT_STATUS,
				val, !(val & GEN_CMD_FULL),
				CMD_PKT_STATUS_TIMEOUT_US);
	if (ret) {
	   printf("failed to get available command FIFO\n");
	   return ret;
	}

	dsi_write(host, DSI_GEN_HDR, hdr_val);

	mask = GEN_CMD_EMPTY | GEN_PLD_W_EMPTY;
	ret = readl_poll_timeout(host->base + DSI_CMD_PKT_STATUS,
				val, (val & mask) == mask,
				CMD_PKT_STATUS_TIMEOUT_US);
	if (ret) {
	   printf("failed to write command FIFO\n");
	   return ret;
	}

	return 0;
}

static int dw_mipi_dsi_write(struct dw_mipi_dsi_host *host,
				const struct mipi_dsi_packet *packet)
{
	const u8 *tx_buf = packet->payload;
	int len = packet->payload_length, pld_data_bytes = sizeof(u32), ret;
	__le32 word;
	u32 val;

	while (len) {
	   if (len < pld_data_bytes) {
		   word = 0;
		   memcpy(&word, tx_buf, len);
		   dsi_write(host, DSI_GEN_PLD_DATA, le32_to_cpu(word));
		   len = 0;
	   } else {
		   memcpy(&word, tx_buf, pld_data_bytes);
		   dsi_write(host, DSI_GEN_PLD_DATA, le32_to_cpu(word));
		   tx_buf += pld_data_bytes;
		   len -= pld_data_bytes;
	   }

	   ret = readl_poll_timeout(host->base + DSI_CMD_PKT_STATUS,
					val, !(val & GEN_PLD_W_FULL),
					CMD_PKT_STATUS_TIMEOUT_US);
	   if (ret) {
		   printf("failed to get available write payload FIFO\n");
		   return ret;
	   }
	}

	word = 0;
	memcpy(&word, packet->header, sizeof(packet->header));
	return dw_mipi_dsi_gen_pkt_hdr_write(host, le32_to_cpu(word));
}

static int dw_mipi_dsi_read(struct dw_mipi_dsi_host *host,
			   const struct mipi_dsi_msg *msg)
{
   int i, j, ret, len = msg->rx_len;
   u8 *buf = msg->rx_buf;
   u32 val;

   /* Wait end of the read operation */
   ret = readl_poll_timeout(host->base + DSI_CMD_PKT_STATUS,
				val, !(val & GEN_RD_CMD_BUSY),
				CMD_PKT_STATUS_TIMEOUT_US);
   if (ret) {
	   printf("Timeout during read operation\n");
	   return ret;
   }

   for (i = 0; i < len; i += 4) {
	   /* Read fifo must not be empty before all bytes are read */
	   ret = readl_poll_timeout(host->base + DSI_CMD_PKT_STATUS,
					val, !(val & GEN_PLD_R_EMPTY),
					CMD_PKT_STATUS_TIMEOUT_US);
	   if (ret) {
		   printf("Read payload FIFO is empty\n");
		   return ret;
	   }

	   val = dsi_read(host, DSI_GEN_PLD_DATA);
	   for (j = 0; j < 4 && j + i < len; j++)
		   buf[i + j] = val >> (8 * j);
   }

   return ret;
}

static ssize_t dw_mipi_dsi_host_transfer(struct dw_mipi_dsi_host *host,
					 const struct mipi_dsi_msg *msg)
{
	struct mipi_dsi_packet packet;
	int ret, nb_bytes;

	ret = mipi_dsi_create_packet(&packet, msg);
	if (ret) {
		printf("failed to create packet: %d\n", ret);
		return ret;
	}

	dw_mipi_message_config(host, msg);
	ret = dw_mipi_dsi_write(host, &packet);
	if (ret)
		return ret;

	if (msg->rx_buf && msg->rx_len) {
		ret = dw_mipi_dsi_read(host, msg);
		if (ret)
			return ret;
		nb_bytes = msg->rx_len;
	} else {
		nb_bytes = packet.size;
	}

	return nb_bytes;
}

static struct mipi_dsi_msg shutdown_msg = {
	.channel = 0,
	.type = MIPI_DSI_SHUTDOWN_PERIPHERAL,
	.tx_buf = (u8 [2]) { 0, 0 },
	.tx_len = 2,
};

static struct mipi_dsi_msg turnon_msg = {
   .channel = 0,
   .type = MIPI_DSI_TURN_ON_PERIPHERAL,
   .tx_buf = (u8 [2]) { 0, 0 },
   .tx_len = 2,
};

int mipi_dsi_shutdown_peripheral(struct dw_mipi_dsi_host *host)
{
	shutdown_msg.channel = host->channel;
	dw_mipi_dsi_host_transfer(host, &shutdown_msg);

	return 0;
}

static int dw_mipi_dsi_host_attach(struct dw_mipi_dsi_host *host,
				struct mipi_panel_device *panel)
{
	const struct mipi_dsi_device *dsi = &panel->dsi;

	host->lanes = dsi->lanes;
	host->channel = dsi->channel;
	host->format = dsi->format;
	host->mode_flags = dsi->mode_flags;

	dw_mipi_dsi_mode_set(host, &panel->display_mode);

	return 0;
}

/*
* The horizontal and vertical timings are defined per the following diagram.
*
*
*				Active				   Front		   Sync 		  Back
*			   Region				  Porch 						 Porch
*	  <-----------------------><----------------><-------------><-------------->
*		//////////////////////|
*	   ////////////////////// |
*	  //////////////////////  |..................				................
*												 _______________
*	  <----- [hv]display ----->
*	  <------------- [hv]sync_start ------------>
*	  <--------------------- [hv]sync_end --------------------->
*	  <-------------------------------- [hv]total ----------------------------->*
*/
static struct mipi_panel_device panels[] = {
	{
		.name = "Sharp LQ101r1sx01",
		.display_mode = {
		 .clock = 278000,
		 .hdisplay = 2560,
		 .hsync_start = 2560 + 128,
		 .hsync_end = 2560 + 128 + 64,
		 .htotal = 2560 + 128 + 64 + 64,
		 .vdisplay = 1600,
		 .vsync_start = 1600 + 4,
		 .vsync_end = 1600 + 4 + 8,
		 .vtotal = 1600 + 4 + 8 + 32,
		 .vrefresh = 60,
		},
		.dsi = {
		 .channel = 0,
		 .lanes = 2,
		 .format = MIPI_DSI_FMT_RGB888,
		 .mode_flags = MIPI_DSI_MODE_LPM,
		},
	},
	{
		.name = "Sharp LQ084V1DG21",
		.display_mode = {
			.clock = 624,
			.hdisplay = 640,
			.hsync_start = 640 + 24,
			.hsync_end = 640 + 24 + 18,
			.htotal = 640 + 24 + 18 + 12,
			.vdisplay = 8,
			.vsync_start = 8 + 4,
			.vsync_end = 8 + 4 + 2,
			.vtotal = 8 + 4 + 2 + 1,
			.vrefresh = 60,
			.flags = DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC,
		},
		.dsi = {
		 .channel = 0,
		 .lanes = 2,
		 .format = MIPI_DSI_FMT_RGB888,
		 .mode_flags = MIPI_DSI_MODE_LPM,
		},
	},
};

static struct dw_mipi_dsi_host	dw_hosts[] = {
	{
		.base = (void*)0x0E6D60000ULL,
		.phy  = {
			 .init = dw_mipi_dsi_phy_init,
			 .get_lane_mbps = dw_mipi_dsi_phy_get_lane_mbps,
		},
		.device_attach = dw_mipi_dsi_host_attach,
	},
};

static int mipi_host_init(int id)
{
	printf("mipi\n");
	return dw_mipi_dsi_host_attach(&dw_hosts[id], &panels[1]);
}

static struct reg_list {
	char *name;
	u32  offset;
} host_regs[] = {
	{"VERSION", 0x0},
	{"PWR_UP",  0x4},
	{"CLKMGR_CFG", 0x8},
	{"DPI_VCID", 0xc},
	{"DPI_COLOR_CODING", 0x10},
	{"DPI_CFG_POL", 0x14},
	{"DPI_LP_CMD_TIM", 0x18},
	{"PCKHDL_CFG", 0x2C},
	{"GEN_VCID", 0x30},
	{"MODE_CFG", 0x34},
	{"VID_MODE_CFG", 0x38},
	{"VID_PKT_SIZE", 0x3C},
	{"VID_NUM_CHUNKS", 0x40},
	{"VID_NULL_SIZE", 0x44},
	{"VID_HSA_TIME", 0x48},
	{"VID_HBP_TIME", 0x4C},
};

static int show(int id, int stage)
{
	u32 value;
	printf("=========HOST%d========\n", id);

	if (stage == 0) {
		value = dsi_read(&dw_hosts[id], host_regs[0].offset);
		printf("%s = 0x%08x\n", host_regs[0].name, value);
	}
	if (stage == 1) {
		for (int i = 1; i < ARRAY_SIZE(host_regs); i++) {
			value = dsi_read(&dw_hosts[id], host_regs[i].offset);
			printf("%s = 0x%08x\n", host_regs[i].name, value);
		}
	}

	printf("======================\n", id);
	return 0;
}

int cmd_dw_mipi_host(int argc, char **argv)
{
	if (argc < 2)
		return -EUSAGE;

	if (argc == 4 && !strcmp("show", argv[1])) {
		show(strtoul(argv[2], 0, 0), strtoul(argv[3], 0, 0));
		return 0;
	}

	if (argc == 3 && !strcmp("init", argv[1])) {
		mipi_host_init(strtoul(argv[2], 0, 0));
		return 0;
	}

	return 0;
}

MK_CMD(mipi, cmd_dw_mipi_host, "mipi cmd",
	"mipi show id stage\n"
	"    -show host[id] registers in stage\n"
	"mipi init id \n"
	"    -initialize host[id]\n"
);

