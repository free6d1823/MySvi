/*
 */
#ifndef __QDF2400_FUSE_H_INCLUDE__
#define __QDF2400_FUSE_H_INCLUDE__

struct qdf2400_fuse_clock {
	unsigned int OvrEn : 1;
	unsigned int OvrInvEn : 1;
	unsigned int OvrDcaEn : 1;
	unsigned int OvrTdlSel : 1;
	unsigned int OvrMuxSel : 4;
	unsigned char OvrDcaVal[24];
};

bool qdf2400_fuse_override_clock_mux(uint32_t *p_clk_sel);
void qdf2400_fuse_apply_clock_settings(struct agera_pll_regs *regs,
				       uint32_t apc);

#endif /* __QDF2400_FUSE_H_INCLUDE__ */
