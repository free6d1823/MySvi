#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H
/*******************************************************
	cr_wrap definition
	version v0.1016
	updated: 2020/7/28
********************************************************/
/* lh_pll_ctrl */
#define CR_WRAP_TOP_BASE_ADDRESS	0x58100000
#define CLK_VPU_DEC_AXI			0x000c2100
#define CLK_VPU_DEC_CORE		0xc2104
#define CLK_VPU_DEC_APB			0xc2108
#define CLK_VPU_ENC_AXI			0xc210c
#define CLK_VPU_ENC_CORE		0xc2110
#define CLK_VPU_ENC_APB			0xc2114
#define CLK_CISP_GDC_CORE		0xc2f18
#define CLK_CG_EN					0x00010000	/* 1: enable vpu_ss_vpu_dec_axi_clock */
#define CLK_OUT_SEL					0x00000100	/* 0: select ref_clk(25MHz), 1: selected divided clock */
#define CLK_DIV_MASK				0x000000ff /*clk =VPU_DEC_AXI_CLK/(2^(n+1)) */
#define VPU_DEC_AXI_DIVIDER			0x00		/*700M/1 = 700MHz */
#define VPU_DEC_CORE_DIVIDER		0x00		/*700M/1 = 700MHz */
#define VPU_DEC_APB_DIVIDER			0x03		/*400M/3 = 100MHz */
#define VPU_ENC_AXI_DIVIDER			0x00		/*500M/1 = 500MHz */
#define VPU_ENC_CORE_DIVIDER		0x00		/*700M/1 = 700MHz */
#define VPU_ENC_APB_DIVIDER			0x03		/*400M/3 = 100MHz */
#define CISP_GDC_CORE_DIVIDER		0x00		/*700M/1 = 700MHz */

#define REG_VPU_DEC_AXI_RST_N		0xc3100
#define REG_VPU_DEC_CORE_RST_N		0xc3104
#define REG_VPU_DEC_APB_RST_N		0xc3108
#define REG_VPU_ENC_AXI_RST_N		0xc310C
#define REG_VPU_ENC_CORE_RST_N		0xc3110
#define REG_VPU_ENC_APB_RST_N		0xc3114

#define RST_N_MASK					0xfffffffe
#define RST_N_ASSERT				0x00000001

#define ENABLE_CLOCK(clk_addr, divider) \
	writel((CLK_CG_EN|CLK_OUT_SEL|divider), (uintptr_t)(CR_WRAP_TOP_BASE_ADDRESS+clk_addr))
	
#define RESET_DEVICE(address, reset) \
	(reset)? writel(0, (uintptr_t)(CR_WRAP_TOP_BASE_ADDRESS+address)) \
			: writel(RST_N_ASSERT, (uintptr_t)(CR_WRAP_TOP_BASE_ADDRESS+address))
			
	


#endif // MY_UTILITIES_H

