/*
 */
#ifndef __GICV2_ARM64_H_INCLUDE__
#define __GICV2_ARM64_H_INCLUDE__

#include <target/regdef.h>
#include <target/gic.h>

/* Distributor interface register map */

/* 4.3.18 Identification registers - Peripheral ID2 Register, ICPIDR2 */
#define GICD_ICPIDR2(inst)		GICD_REG(inst, 0xFE8) /* Peripheral ID2 */

/* GICD_ICFGR */
#define GICD_MODEL(value)		((value & 1) << 0)
#define GICD_MODEL_N_N			0
#define GICD_MODEL_1_N			1

/* GICD_ICPIDR2 */
#define GICD_ARCH_REV_OFFSET		4
#define GICD_ARCH_REV_MASK		GIC_4BIT_MASK
#define GICD_ARCH_REV(value)		GICD_FV(ARCH_REV, value)

/* CPU interface register map */
#define GICC_REG(offset)               (GICC_BASE+(offset))
#define GICC_1BIT_REG(offset, n)       GIC_1BIT_REG(GICC_BASE+(offset), n)
#define GICC_FV(name, value)           GIC_FV(GICC_##name, value)
#define GICCn_FV(n, name, value)       GICn_FV(n, GICC_##name, value)

/* 4.4.1 CPU Interface Control Register, GICC_CTLR */
#define GICC_CTLR			GICC_REG(0x000)
/* 4.4.2 Interrupt Priority Mask Register, GICC_PMR */
#define GICC_PMR			GICC_REG(0x004)
/* 4.4.3 Binary Point Register, GICC_BPR */
#define GICC_BPR			GICC_REG(0x008)
/* 4.4.4 Interrupt Acknowledge Register, GICC_IAR */
#define GICC_IAR			GICC_REG(0x00C)
/* 4.4.5 End of Interrupt Register, GICC_EOIR */
#define GICC_EOIR			GICC_REG(0x010)
/* 4.4.6 Running Priority Register, GICC_RPR */
#define GICC_RPR			GICC_REG(0x014)
/* 4.4.7 Highest Priority Pending Interrupt Register, GICC_HPPIR */
#define GICC_HPPIR			GICC_REG(0x018)
/* 4.4.8 Aliased Binary Point Register, GICC_ABPR */
#define GICC_ABPR			GICC_REG(0x01C)
/* 4.4.9 Aliased Interrupt Acknowledge Register, GICC_AIAR */
#define GICC_AIAR			GICC_REG(0x020)
/* 4.4.10 Aliased End of Interrupt Register, GICC_AEOIR */
#define GICC_AEOIR			GICC_REG(0x024)
/* 4.4.11 Aliased Highest Priority Pending Interrupt Register, GICC_AHPPIR */
#define GICC_AHPPIR			GICC_REG(0x028)
/* 4.4.12 Active Priorities Registers, GICC_APRn */
#define GICC_APR(n)			GICC_1BIT_REG(0x0D0, n)
/* 4.4.13 Non-secure Active Priorities Registers, GICC_NSAPRn */
#define GICC_NSAPR(n)			GICC_1BIT_REG(0x0E0, n)
/* 4.4.14 CPU Interface Identification Register, GICC_IIDR */
#define GICC_IIDR			GICC_REG(0x0FC)
/* 4.4.15 Deactivate Interrupt Register, GICC_DIR */
#define GICC_DIR			GICC_REG(0x100)

/* GICC_CTLR */
#define GICC_ENABLE_GRP1		_BV(0)
#define GICC_FIQ_BYP_DIS_GRP1		_BV(5)
#define GICC_IRQ_BYP_DIS_GRP1		_BV(6)
#define GICC_EOI_MODE_NS		_BV(9)

/* GICC_PMR/GICC_RPR */
#define GICC_PRIORITY(inst, value)	GIC_PRIORITY0(inst, value)

/* GICC_BPR/GICC_ABPR */
#define GICC_BINARY_POINT_OFFSET	0
#define GICC_BINARY_POINT_MASK		GIC_3BIT_MASK
#define GICC_BINARY_POINT(value)	GICC_FV(BINARY_POINT, value)

/* GICC_IAR/GICC_EOIR/GICC_HPPIR/GICC_AIAR/GICC_AEOIR/GICC_AHPIR/GICC_DIR */
#define GICC_IRQ_ID_OFFSET		0
#define GICC_IRQ_ID_MASK		GIC_10BIT_MASK
#define GICC_SET_IRQ(value)		GICC_FV(IRQ_ID, value)
#define GICC_GET_IRQ(reg)		\
	(((reg) >> GICC_IRQ_ID_OFFSET) & GICC_IRQ_ID_MASK)
#define GICC_CPU_ID_OFFSET		10
#define GICC_CPU_ID_MASK		GIC_3BIT_MASK
#define GICC_SET_CPU(value)		GICC_FV(CPU_ID, value)
#define GICC_GET_CPU(reg)	\
	(((reg) >> GICC_CPU_ID_OFFSET) & GICC_CPU_ID_MASK)

/* GICC_APR/GICC_NSAPR */
#define GICC_ACTIVE_PRIORITY_OFFSET(n)	GIC_1BIT_OFFSET(n)
#define GICC_ACTIVE_PRIORITY_MASK	GIC_1BIT_MASK
#define GICC_ACTIVE_PRIORITY(n, value)	GICCn_FV(n, ACTIVE_PRIORITY, value)

/* GICC_IIDR */
#define GICC_IMPLEMENTER_OFFSET		0
#define GICC_IMPLEMENTER_MASK		GIC_12BIT_MASK
#define GICC_IMPLEMENTER(value)		GICC_FV(IMPLEMENTER, value)
#define GICC_REVISION_OFFSET		12
#define GICC_REVISION_MASK		GIC_4BIT_MASK
#define GICC_REVISION(value)		GICC_FV(REVISION, value)
#define GICC_ARCH_REV_OFFSET		16
#define GICC_ARCH_REV_MASK		GIC_4BIT_MASK
#define GICC_ARCH_REV(value)		GICC_FV(ARCH_REV, value)
#define GICC_PRODUCT_ID_OFFSET		20
#define GICC_PRODUCT_ID_MASK		GIC_12BIT_MASK
#define GICC_PRODUCT_ID(value)		GICC_FV(PRODUCT_ID, value)

void gicv2_handle_irq();

#endif /* __GICV2_ARM64_H_INCLUDE__ */
