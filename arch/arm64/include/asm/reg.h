/*
 */
#ifndef __REG_ARM64_H_INCLUDE__
#define __REG_ARM64_H_INCLUDE__

#include <target/regdef.h>

/* =================================================================
 * DDI0487B_b ARMv8 ARM
 * ARM Architecture Reference Manual - ARMv8, for ARMv8-A
 * architecture profile
 * ================================================================= */

/* =================================================================
 * D.10.2 General system control registers
 * ================================================================= */
/* D.10.2.19 CPTR_EL2, Architectural Feature Trap Register (EL2)
 * D.10.2.20 CPTR_EL3, Architectural Feature Trap Register (EL3)
 */
#define CPTR_TFP		_BV(10)
#define CPTR_TTA		_BV(20)
#define CPTR_TCPAC		_BV(31)

#define CPTR_EL2_RES0				\
	(_BV(11)|_BV(14)|_BV(15)|_BV(16)|	\
	 _BV(17)|_BV(18)|_BV(19)|_BV(21)|	\
	 _BV(22)|_BV(23)|_BV(24)|_BV(25)|	\
	 _BV(26)|_BV(27)|_BV(28)|_BV(29)|_BV(30))
#define CPTR_EL2_RES1				\
	(_BV(0)|_BV(1)|_BV(2)|_BV(3)|		\
	 _BV(4)|_BV(5)|_BV(6)|_BV(7)|		\
	 _BV(8)|_BV(9)|_BV(12)|_BV(13))
#define CPTR_EL3_RES0				\
	(CPTR_EL2_RES0|CPTR_EL2_RES1)

/* D.10.2.34 HCR_EL2, Hypervisor Configuration Register */
#define	HCR_FV(name, value)	_FV(HCR_##name, value)

#define HCR_VM			_BV(0) /* Enable virtualization */
#define HCR_SWIO		_BV(1) /* Set/way invalidation override */
#define HCR_PTW			_BV(2) /* Protected table walk */
#define HCR_FMO			_BV(3) /* Physical FIQ routing */
#define HCR_IMO			_BV(4) /* Physical IRQ routing */
#define HCR_AMO			_BV(5) /* Async external abort and SError IRQ routing */
#define HCR_VF			_BV(6) /* Virtual FIQ */
#define HCR_VI			_BV(7) /* Virtual IRQ */
#define HCR_VSE			_BV(8) /* Virtual system error or async abort */
#define HCR_FB			_BV(9) /* Force broadcast */

#define HCR_BSU_OFFSET		10
#define HCR_BSU_MASK		0x03
#define HCR_BSU(value)		HCR_FV(BSU, value) /* Barrier sharebility upgrade */
#define HCR_BSU_NO_EFFECT	0
#define HCR_BSU_INNER_SHAREABLE	1
#define HCR_BSU_OUTER_SHAREABLE	2
#define HCR_BSU_FULL_SYSTEM	3

#define HCR_DC			_DV(12) /* Default cacheable */
#define HCR_TWI			_BV(13) /* Trap WFI */
#define HCR_TWE			_BV(14) /* Trap WFE */
#define HCR_TID0		_BV(15) /* Trap ID group 0 */
#define HCR_TID1		_BV(16) /* Trap ID group 1 */
#define HCR_TID2		_BV(17) /* Trap ID group 2 */
#define HCR_TID3		_BV(18) /* Trap ID group 3 */
#define HCR_TSC			_BV(19) /* Trap SMC */
#define HCR_TIDCP		_BV(20) /* Trap implementation defined functionality */
#define HCR_TACR		_BV(21) /* Trap Auxiliary Control Register */
#define HCR_TSW			_BV(22) /* Trap data or cache maintenance by set/way */
#define HCR_TPC			_BV(23) /* Trap data or cache maintenance of POC */
#define HCR_TPU			_BV(24) /* Trap cache maintenance */
#define HCR_TTLB		_BV(25) /* Trap TLB maintenance */
#define HCR_TVM			_BV(26) /* Trap virtual memory controls */
#define HCR_TGE			_BV(27) /* Trap general exception */
#define HCR_TDZ			_BV(28) /* Trap DC ZVA */
#define HCR_HCD			_BV(29) /* Disable HVC */
#define HCR_TRVM		_BV(30) /* Trap virtual memory control reads */
#define HCR_RW			_BV(31) /* Execution state for lower level */
#define HCR_CD			_BV(32) /* Disable data cache */
#define HCR_ID			_BV(33) /* Disable instruction cache */
#define HCR_MIOCNCE		_BV(38) /* Enable mismatched Inner/Outer Cacheable Non-Coherency */

#define HCR_EL2_RES0				\
	(_BV(63)|_BV(62)|_BV(61)|_BV(60)|	\
	 _BV(59)|_BV(58)|_BV(57)|_BV(56)|	\
	 _BV(55)|_BV(54)|_BV(53)|_BV(52)|	\
	 _BV(51)|_BV(50)|_BV(49)|_BV(48)|	\
	 _BV(47)|_BV(46)|_BV(45)|_BV(44)|	\
	 _BV(43)|_BV(42)|_BV(41)|_BV(40)|	\
	 _BV(39)|_BV(37)|_BV(36)|_BV(35)|	\
	 _BV(34))

/* D10.2.74 MIDR_EL1, Main ID Register */
#define MIDR_IMPL_OFFSET	24
#define MIDR_IMPL_MASK		0xFF
#define MIDR_IMPL(value)	_GET_FV(MIDR_IMPL, value)

#define MIDR_IMPL_ARM		0x41 /* A */
#define MIDR_IMPL_BROADCOM	0x42 /* B */
#define MIDR_IMPL_CAVIUM	0x43 /* C */
#define MIDR_IMPL_DEC		0x44 /* D */
#define MIDR_IMPL_INFINEON	0x49 /* I */
#define MIDR_IMPL_MOTOROLA	0x4D /* M */
#define MIDR_IMPL_NVIDIA	0x4E /* N */
#define MIDR_IMPL_APPLE		0x50 /* P */
#define MIDR_IMPL_QUALCOMM	0x51 /* Q */
#define MIDR_IMPL_MARVELL	0x56 /* V */
#define MIDR_IMPL_HXT		0x68 /* h */
#define MIDR_IMPL_INTEL		0x69 /* i */

#define MIDR_VAR_OFFSET		20
#define MIDR_VAR_MASK		0x0F
#define MIDR_VAR(value)		_GET_FV(MIDR_VAR, value)

#define MIDR_ARCH_OFFSET	16
#define MIDR_ARCH_MASK		0x0F
#define MIDR_ARCH(value)	_GET_FV(MIDR_ARCH, value)

#define MIDR_ARCH_ARMV4		0x01
#define MIDR_ARCH_ARMV4T	0x02
#define MIDR_ARCH_ARMV5		0x03
#define MIDR_ARCH_ARMV5T	0x04
#define MIDR_ARCH_ARMV5TE	0x05
#define MIDR_ARCH_ARMV5TEJ	0x06
#define MIDR_ARCH_ARMV6		0x07

#define MIDR_PN_OFFSET		4
#define MIDR_PN_MASK		0x0FFF
#define MIDR_PN(value)		_GET_FV(MIDR_PN, value)

#define MIDR_PN_QCOM_FALKOR	0x0800
#define MIDR_PN_QCOM_FALKOR_V2	0x0C00
#define MIDR_PN_HXT_1		0x0000

#define MIDR_REV_OFFSET		0
#define MIDR_REV_MASK		0x0F
#define MIDR_REV(value)		_GET_FV(MIDR_REV, value)

/* D.10.2.81 RMR_EL1, Reset Management Register (EL1)
 * D.10.2.82 RMR_EL2, Reset Management Register (EL2)
 * D.10.2.83 RMR_EL3, Reset Management Register (EL3)
 */
#define RMR_AA64		_BV(0)
#define RMR_RR			_BV(1)
#define RMR_RES0		\
	(_BV(31)|_BV(30)|_BV(29)|_BV(28)|	\
	 _BV(27)|_BV(26)|_BV(25)|_BV(24)|	\
	 _BV(23)|_BV(22)|_BV(21)|_BV(20)|	\
	 _BV(19)|_BV(18)|_BV(17)|_BV(16)|	\
	 _BV(15)|_BV(14)|_BV(13)|_BV(12)|	\
	 _BV(11)|_BV(10)|_BV(9)|_BV(8)|		\
	 _BV(7)|_BV(6)|_BV(5)|_BV(4)|		\
	 _BV(3)|_BV(2))
#define RMR_EL1_RES0		RMR_RES0
#define RMR_EL2_RES0		RMR_RES0
#define RMR_EL3_RES0		RMR_RES0

/* D.10.2.88 SCR_EL3, Secure Configuration Register */
#define SCR_NS			_BV(0) /* Non-secure */
#define SCR_IRQ			_BV(1) /* Physical IRQ routing */
#define SCR_FIQ			_BV(2) /* Physical FIQ routing */
#define SCR_EA			_BV(3) /* External ABT and SError IRQ routing */
#define SCR_SMD			_BV(7) /* Disable SMC */
#define SCR_HCE			_BV(8) /* Disable HVC */
#define SCR_SIF			_BV(9) /* Secure instruction fetch */
#define SCR_RW			_BV(10) /* Execution state for lower level */
#define SCR_ST			_BV(11) /* Secure timer - trap EL1 CNTPS_ */
#define SCR_TWI			_BV(12) /* Trap WFI */
#define SCR_TWE			_BV(13) /* Trap WFE */

#define SCR_EL3_RES0				\
	(_BV(31)|_BV(30)|_BV(29)|_BV(28)|	\
	 _BV(27)|_BV(26)|_BV(25)|_BV(24)|	\
	 _BV(23)|_BV(22)|_BV(21)|_BV(20)|	\
	 _BV(19)|_BV(18)|_BV(17)|_BV(16)|	\
	 _BV(15)|_BV(14)|_BV(6))
#define SCR_EL3_RES1		(_BV(5)|_BV(4))

/* D.10.2.89 SCTLR_EL1, System Control Register (EL1)
 * D.10.2.90 SCTLR_EL2, System Control Register (EL2)
 * D.10.2.91 SCTLR_EL3, System Control Register (EL3)
 */
/* EL1 only: */
#define SCTLR_SA0		_BV(4)	/* Check EL0 stack alignment */
#define SCTLR_CP16BEN		_BV(5)	/* Enable CP15 memory barrier */
#define SCTLR_IT		_BV(7)	/* Trap EL0 IT */
#define SCTLR_SED		_BV(8)	/* Trap EL0 SETEND */
#define SCTLR_UMA		_BV(9)	/* Trap EL0 DAIF access */
#define SCTLR_DZE		_BV(14)	/* Trap EL0 DC ZVA */
#define SCTLR_UCT		_BV(15)	/* Trap EL0 CTR_EL0 access */
#define SCTLR_nTWI		_BV(16)	/* Trap EL0 WFI */
#define SCTLR_nTWE		_BV(18)	/* Trap EL0 WFE */
#define SCTLR_E0E		_BV(24)	/* EL0 endianness */
#define SCTLR_UCI		_BV(26)	/* Trap EL0 cache maintenance */

#define SCTLR_EL1_RES0				\
	(_BV(31)|_BV(30)|_BV(27)|_BV(21)|	\
	 _BV(17)|_BV(13)|_BV(10)|_BV(6))
#define SCTLR_EL1_RES1				\
	(_BV(29)|_BV(28)|_BV(23)|_BV(22)|	\
	 _BV(20)|_BV(11))

/* EL3/EL2/EL1: */
#define SCTLR_M			_BV(0)	/* Enable MMU */
#define SCTLR_A			_BV(1)	/* Check alignment */
#define SCTLR_C			_BV(2)	/* Cacheability */
#define SCTLR_SA		_BV(3)	/* Check stack alignment */
#define SCTLR_I			_BV(12)	/* Instruction access cacheability */
#define SCTLR_WXN		_BV(19)	/* Write permission Execute-Never */
#define SCTLR_EE		_BV(25)	/* Endianness */
#define SCTLR_RES0				\
	(_BV(31)|_BV(30)|_BV(27)|_BV(26)|	\
	 _BV(24)|_BV(21)|_BV(20)|_BV(17)|	\
	 _BV(15)|_BV(14)|_BV(13)|_BV(10)|	\
	 _BV(9)|_BV(8)|_BV(7)|_BV(6))
#define SCTLR_RES1				\
	(_BV(29)|_BV(28)|_BV(23)|_BV(22)|	\
	 _BV(18)|_BV(16)|_BV(11)|_BV(5)|_BV(4))
#define SCTLR_EL2_RES0		SCTLR_RES0
#define SCTLR_EL2_RES1		SCTLR_RES1
#define SCTLR_EL3_RES0		SCTLR_RES0
#define SCTLR_EL3_RES1		SCTLR_RES1

/* =================================================================
 * D.10.3 Debug registers
 * ================================================================= */
/* D.10.3.16 MDCCSR_EL0, Monitor DCC Status Register */
#define MDCCSR_TXFULL		_BV(29)
#define MDCCSR_RXFULL		_BV(30)

/* D10.3.18 MDCR_EL3, Monitor Debug Configuration Register (EL3)
 */
#define MDCR_EPMAD		_BV(21)
#define MDCR_EDAD		_BV(20)
#define MDCR_SPME		_BV(17)
#define MDCR_SDD		_BV(16)
#define MDCR_SPD32_OFFSET	14
#define MDCR_SPD32_MASK		0x03
#define MDCR_SPD32(value)	_FV(MDCR_SPD32, value)
#define MDCR_NSPB_OFFSET	12
#define MDCR_NSPB_MASK		0x03
#define MDCR_NSPB(value)	_FV(MDCR_NSPB, value)
#define MDCR_TDOSA		_BV(10)
#define MDCR_TDA		_BV(9)
#define MDCR_TPM		_BV(6)

/* =================================================================
 * D.10.6 Generic Timer registers
 * ================================================================= */
/* D.10.6.2 CNTHCTL_EL2, Counter-timer Hypervisor Control register */
#define CNTHCTL_EL1PCTEN	_BV(0)
#define CNTHCTL_EL1PCEN		_BV(1)

#define CNTHCTL_EL2_RES0			\
	(_BV(31)|_BV(30)|_BV(29)|_BV(28)|	\
	 _BV(27)|_BV(26)|_BV(25)|_BV(24)|	\
	 _BV(23)|_BV(21)|_BV(20)|_BV(19)|	\
	 _BV(18)|_BV(17)|_BV(16)|_BV(15)|	\
	 _BV(14)|_BV(13)|_BV(12)|_BV(11)|	\
	 _BV(10)|_BV(9)_BV(8))

/* D10.6.9 CNTKCTL_EL1, Conter-timer Kernel Control register */
#define CNTKCTL_EL0PCTEN	_BV(0)
#define CNTKCTL_EL0VCTEN	_BV(1)
#define CNTKCTL_EL0VTEN		_BV(8)
#define CNTKCTL_EL0PTEN		_BV(9)

#define CNTKCTL_EL1_RES0			\
	(_BV(31)|_BV(30)|_BV(29)|_BV(28)|	\
	 _BV(27)|_BV(26)|_BV(25)|_BV(24)|	\
	 _BV(23)|_BV(21)|_BV(20)|_BV(19)|	\
	 _BV(18)|_BV(17)|_BV(16)|_BV(15)|	\
	 _BV(14)|_BV(13)|_BV(12)|_BV(11)|	\
	 _BV(10))

/* Fields common to CNTHCTL_EL2/CNTKCTL_EL1 */
#define	CNTXCTL_FV(name, value)	_FV(CNTXCTL_##name, value)

#define CNTXCTL_EVNTEN		_BV(2)
#define CNTXCTL_EVNTDIR		_BV(3)
#define CNTXCTL_EVNTI_OFFSET	4
#define CNTXCTL_EVNTI_MASK	0x0F
#define CNTXCTL_EVNTI(value)	CNTXCTL_FV(EVNTI, value)

/* D10.6.3  CNTHP_CTL_EL2,
 *          Counter-timer Hypervisor Physical Timer Control register
 * D10.6.6  CNTHV_CTL_EL2,
 *          Counter-timer Virtual Timer Control register (EL2)
 * D10.6.10 CNTP_CTL_EL0,
 *          Counter-timer Physical Timer Control register
 * D10.6.14 CNTPS_CTL_EL1,
 *          Counter-timer Physical Secure Timer Control register
 */
#define CNTX_CTL_ENABLE		_BV(0)
#define CNTX_CTL_IMASK		_BV(1)
#define CNTX_CTL_ISTATUS	_BV(2)

#endif /* __REG_ARM64_H_INCLUDE__ */
