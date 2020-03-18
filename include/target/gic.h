/*
 */
#ifndef __GIC_ARM64_H_INCLUDE__
#define __GIC_ARM64_H_INCLUDE__

#include <stdint.h>
#include <stddef.h>
#include <target/memory.h>
#include <target/regdef.h>

#define GIC_GIC2_PRIORITY_SHIFT	3
#define GIC_GIC3_PRIORITY_SHIFT	0

/* ARM Generic Interrupt Controller Architecture Specification v2 */

/* base address and bit offset generator for bits-registers */
#define GIC_1BIT_MASK			0x001
#define GIC_2BIT_MASK			0x003
#define GIC_3BIT_MASK			0x007
#define GIC_4BIT_MASK			0x00F
#define GIC_5BIT_MASK			0x01F
#define GIC_6BIT_MASK			0x03F
#define GIC_7BIT_MASK			0x07F
#define GIC_8BIT_MASK			0x0FF
#define GIC_9BIT_MASK			0x1FF
#define GIC_10BIT_MASK			0x3FF
#define GIC_11BIT_MASK			0x7FF
#define GIC_12BIT_MASK			0xFFF
#define GIC_24BIT_MASK			0xFFFFFF

#define GIC_1BIT_REG(base, n)		((base)+(((n) & (~31)) >> 3))
#define GIC_2BIT_REG(base, n)		((base)+(((n) & (~15)) >> 2))
#define GIC_4BIT_REG(base, n)		((base)+(((n) & (~7 )) >> 1))
#define GIC_8BIT_REG(base, n)		((base)+(((n) & (~3 )) >> 0))

#define GIC_1BIT_OFFSET(n)		(((n) & 31) << 0)
#define GIC_2BIT_OFFSET(n)		(((n) & 15) << 1)
#define GIC_4BIT_OFFSET(n)		(((n) &  7) << 2)
#define GIC_8BIT_OFFSET(n)		(((n) &  3) << 3)

#define GIC_FV(name, value)		_FV(name, value)
#define GICn_FV(n, name, value)		\
	(((value) & (name##_MASK)) << (name##_OFFSET(n)))

/* Distributor register map */
#define GICD_REG(inst, offset)		(inst+(offset))
#define GICD_1BIT_REG(inst, offset, n)	\
	GIC_1BIT_REG(inst+(offset), n)
#define GICD_2BIT_REG(inst, offset, n)	\
	GIC_2BIT_REG(inst+(offset), n)
#define GICD_8BIT_REG(inst, offset, n)	\
	GIC_8BIT_REG(inst+(offset), n)
#define GICD_FV(name, value)		GIC_FV(GICD_##name, value)
#define GICDn_FV(n, name, value)	GICn_FV(n, GICD_##name, value)

/* v2: 4.3.1 Distributor Control Register, GICD_CTLR */
/* v3: 8.9.4 GICD_CTLR, Distributor Control Register */
#define GICD_CTLR(inst)			GICD_REG(inst, 0x000)
/* v2: 4.3.2 Interrupt Controller Type Register, GICD_TYPER */
/* v3: 8.9.24 GICD_TYPER, Interrupt Controller Type Register */
#define GICD_TYPER(inst)		GICD_REG(inst, 0x004)
/* v2: 4.3.3 Distributor Implementer Identification Register, GICD_IIDR */
/* v3: 8.9.11 GICD_IIDR, Distributor Implementer Identification Register */
#define GICD_IIDR(inst)			GICD_REG(inst, 0x008)
/* v2: 4.3.4 Interrupt Group Registers, GICD_IGROUPRn */
/* v3: 8.9.9 GICD_IGROUPR<n>, Interrupt Group Registers, n = 0 - 31 */
#define GICD_IGROUPR(inst, n)		GICD_1BIT_REG(inst, 0x080, n)
/* v2: 4.3.5 Interrupt Set-Enable Registers, GICD_ISENABLERn */
/* v3: 8.9.15 GICD_ISENABLER<n>,
 *            Interrupt Set-Enable Registers, n = 0 - 31
 */
#define GICD_ISENABLER(inst, n)		GICD_1BIT_REG(inst, 0x100, n)
/* v2: 4.3.6 Interrupt Clear-Enable Registers, GICD_ICENABLERn */
/* v3: 8.9.6 GICD_ICENABLER<n>,
 *           Interrupt Clear-Enable Registers, n = 0 - 31
 */
#define GICD_ICENABLER(inst, n)		GICD_1BIT_REG(inst, 0x180, n)
/* v2: 4.3.7 Interrupt Set-Pending Registers, GICD_ISPENDRn */
/* v3: 8.9.16 GICD_ISPENDR<n>,
 *            Interrupt Set-Pending Registers, n = 0 - 31
 */
#define GICD_ISPENDR(inst, n)		GICD_1BIT_REG(inst, 0x200, n)
/* v2: 4.3.8 Interrupt Clear-Pending Registers, GICD_ICPENDRn */
/* v3: 8.9.8 GICD_ICPENDR<n>,
 *           Interrupt Clear-Pending Registers, n = 0 - 31
 */
#define GICD_ICPENDR(inst, n)		GICD_1BIT_REG(inst, 0x280, n)
/* v2: 4.3.9 Interrupt Set-Active Registers, GICD_ISACTIVERn */
/* v3: 8.9.14 GICD_ISACTIVER<n>,
 *            Interrupt Set-Active Registers, n = 0 - 31
 */
#define GICD_ISACTIVER(inst, n)		GICD_1BIT_REG(inst, 0x300, n)
/* v2: 4.3.10 Interrupt Clear-Active Registers, GICD_ICACTIVERn */
/* v3: 8.9.5 GICD_ICACTIVER<n>,
 *           Interrupt Clear-Active Registers, n = 0 - 31
 */
#define GICD_ICACTIVER(inst, n)		GICD_1BIT_REG(inst, 0x380, n)
/* v2: 4.3.11 Interrupt Priority Registers, GICD_IPRIORITYRn */
/* v3: 8.9.12 GICD_IPRIORITYR<n>,
 *            Interrupt Priority Registers, n = 0 - 254
 */
#define GICD_IPRIORITYR(inst, n)	GICD_8BIT_REG(inst, 0x400, n)
/* v2: 4.3.12 Interrupt Processor Targets Registers, GICD_ITARGETSRn */
/* v3: 8.9.17 GICD_ITARGETSR<n>,
 *            Interrupt Processor Targets Registers, n = 0 - 254
 */
#define GICD_ITARGETSR(inst, n)		GICD_8BIT_REG(inst, 0x800, n)
/* v2: 4.3.13 Interrupt Configuration Registers, GICD_ICFGRn */
/* v3: 8.9.7 GICD_ICFGR<n>,
 *           Interrupt Configuration Registers, n = 0 - 63
 */
#define GICD_ICFGR(inst, n)		GICD_2BIT_REG(inst, 0xC00, n)
/* v2: 4.3.14 Non-secure Access Control Registers, GICD_NSACRn */
/* v3: 8.9.18 GICD_NSACR<n>,
 *            Non-secure Access Control Registers, n = 0 - 63
 */
#define GICD_NSACR(inst, n)		GICD_2BIT_REG(inst, 0xE00, n)
/* v2: 4.3.15 Software Generated Interrupt Register, GICD_SGIR */
/* v3: 8.9.21 GICD_SGIR, Software Generated Interrupt Register */
#define GICD_SGIR(inst)			GICD_REG(inst, 0xF00)
/* v2: 4.3.16 SGI Clear-Pending Registers, GICD_CPENDSGIRn */
/* v3: 8.9.3 GICD_CPENDSGIR<n>,
 *           SGI Clear-Pending Registers, n = 0 - 3
 */
#define GICD_CPENDSGIR(inst, n)		GICD_8BIT_REG(inst, 0xF10, n)
/* v2: 4.3.17 SGI Set-Pending Registers, GICD_SPENDSGIRn */
/* v3: 8.9.22 GICD_SPENDSGIR<n>,
 *            SGI Set-Pending Registers, n = 0 - 3
 */
#define GICD_SPENDSGIR(inst, n)		GICD_8BIT_REG(inst, 0xF20, n)

/* GICD_CTLR */
#define GICD_CTLR_ENABLE		_BV(0)
#define GICD_ENABLE_GRP0		_BV(0)
#define GICD_ENABLE_GRP1		_BV(1)

/* GICD_TYPER */
#define GICD_TYPER_IRQS(typer)		((((typer) & 0x1f) + 1) * 32 - 1)
#define GICD_IT_LINES_NUMBER_OFFSET	0
#define GICD_IT_LINES_NUMBER_MASK	GIC_5BIT_MASK
#define GICD_IT_LINES_NUMBER(value)	GICD_FV(IT_LINES_NUMBER, value)
#define GICD_CPU_NUMBER_OFFSET		5
#define GICD_CPU_NUMBER_MASK		GIC_3BIT_MASK
#define GICD_CPU_NUMBER(value)		GICD_FV(CPU_NUMBER, value)
#define GICD_SECURITY_EXTN		_BV(10)
#define GICD_LSPI_OFFSET		11
#define GICD_LSPI_MASK			GIC_5BIT_MASK
#define GICD_LSPI(value)		GICD_FV(LSPI, value)

/* GICD_IIDR */
#define GICD_IMPLEMENTER_OFFSET		0
#define GICD_IMPLEMENTER_MASK		GIC_12BIT_MASK
#define GICD_IMPLEMENTER(value)		GICD_FV(IMPLEMENTER, value)
#define GICD_REVISION_OFFSET		12
#define GICD_REVISION_MASK		GIC_4BIT_MASK
#define GICD_REVISION(value)		GICD_FV(REVISION, value)
#define GICD_VARIANT_OFFSET		16
#define GICD_VARIANT_MASK		GIC_4BIT_MASK
#define GICD_VARIANT(value)		GICD_FV(VARIANT, value)
#define GICD_PRODUCT_ID_OFFSET		24
#define GICD_PRODUCT_ID_MASK		GIC_8BIT_MASK
#define GICD_PRODUCT_ID(value)		GICD_FV(PRODUCT_ID, value)

/* GICD/R_IGROUPR */
#define GIC_GROUP1(n)			_BV(GIC_1BIT_OFFSET(n))

/* GICD/R_ISENABLER/GICD/R_ICENABLER
 * GICD/R_ISPENDR/GICD/R_ICPENDR
 * GICD/R_ISACTIVER/GICD/R_ICACTIVER
 */
#define GIC_INTERRUPT_ID(n)		_BV(GIC_1BIT_OFFSET(n))

/* GICD/R_IPRORITYR */
#define GIC_PRIORITY_OFFSET(n)		GIC_8BIT_OFFSET(n)
#define GIC_PRIORITY_MASK		GIC_8BIT_MASK
#define GIC_PRIORITY(inst, n, value)	\
	GICn_FV(n, GIC_PRIORITY, value<<GIC_##inst##_PRIORITY_SHIFT)
#define GIC_PRIORITY_IDLE		GIC_PRIORITY_MASK

/* GICD/R_ITARGETSR */
#define GIC_CPU_TARGETS_OFFSET(n)	GIC_8BIT_OFFSET(n)
#define GIC_CPU_TARGETS_MASK		GIC_8BIT_MASK
#define GIC_CPU_TARGETS(n, value)	GICn_FV(n, GIC_CPU_TARGETS, value)
#define GIC_CPU_TARGETS_MAX		0xFF

/* GICD/R_ICFGR */
#define GIC_INT_CONFIG_OFFSET(n)	GIC_2BIT_OFFSET(n)
#define GIC_INT_CONFIG_MASK		GIC_2BIT_MASK
#define GIC_INT_CONFIG(n, value)	GICn_FV(n, GIC_INT_CONFIG, value)
#define GIC_TRIGGER(value)		((value & 1) << 1)
#define GIC_TRIGGER_LEVEL		0
#define GIC_TRIGGER_EDGE		1

/* GICD_NSACR */
#define GICD_NS_ACCESS_OFFSET(n)	GIC_2BIT_OFFSET(n)
#define GICD_NS_ACCESS_MASK		GIC_2BIT_MASK
#define GICD_NS_ACCESS(n, value)	GICDn_FV(n, NS_ACCESS, value)
#define GICD_NSAC_ALL			0
#define GICD_NSAC_WSPEND_WSGI		1
#define GICD_NSAC_WCPEND_RXACTIVE	2
#define GICD_NSAC_RWTARGETS		3

/* GICD_SGIR */
#define GICD_SGIINTID_OFFSET		0
#define GICD_SGIINTID_MASK		GIC_4BIT_MASK
#define GICD_SGIINTID(value)		GICD_FV(SGIINTID, value)
#define GICD_NSATT			_BV(15)
#define GICD_CPU_TARGET_LIST_OFFSET	16
#define GICD_CPU_TARGET_LIST_MASK	GIC_8BIT_MASK
#define GICD_CPU_TARGET_LIST(value)	GICD_FV(CPU_TARGET_LIST, value)
#define GICD_TARGET_LIST_FILTER_OFFSET	24
#define GICD_TARGET_LIST_FILTER_MASK	GIC_2BIT_MASK
#define GICD_TARGET_LIST_FILTER(value)	GICD_FV(TARGET_LIST_FILTER, value)

/* GICD_CPENDSGIR/GICD_SPENDSGIR */
#define GICD_SGI_PENDING_OFFSET(n)	GIC_8BIT_OFFSET(n)
#define GICD_SGI_PENDING_MASK		GIC_8BIT_MASK
#define GICD_SGI_PENDING(n, value)	GICDn_FV(n, SGI_PENDING, value)

/* Generic values */
#define GIC_PRIORITY0(inst, value)	GIC_PRIORITY(inst, 0, value)
#define GIC_PRIORITY_MAX(inst)		\
	(0xFF>>GIC_##inst##_PRIORITY_SHIFT)

#endif /* __GIC_ARM64_H_INCLUDE__ */
