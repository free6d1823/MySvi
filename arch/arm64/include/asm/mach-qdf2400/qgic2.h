/*
 */
#ifndef __QGIC2_QDF2400_H_INCLUDE__
#define __QGIC2_QDF2400_H_INCLUDE__

#include <asm/gicv2.h>

/* 2.16.1.7.3.4. GICD_ANSACR (0x0FF 6FA4 0020) */
#define GICD_ANSACR(inst)		GICD_REG(inst, 0x020)
#define GICD_GICD_CGCR			_BV(0) /* NS access to GICD_CGCR */

/* 2.16.1.7.3.5. GICD_CGCR (0x0FF 6FA4 0024) */
#define GICD_CGCR(inst)			GICD_REG(inst, 0x024)
#define GICD_TOP			_BV(16)
#define GICD_DI_SGI_STATE		_BV(3)
#define GICD_DI_PPI_SPI_STATE		_BV(2)
#define GICD_DI_DEMET			_BV(1)
#define GICD_DI_RD			_BV(0)

/* 2.16.1.7.3.6. GICD_HW_VERSION (0x0FF 6FA4 0030) */
#define GICD_HW_VERSION(inst)		GICD_REG(inst, 0x030)

/* 2.16.1.7.3.7. GICD_ISR%n% (0xFF6FA40000 + 0x80+0x4 * n (n=[0..18-1]))
 * Each bit in an GICD_ISR register controls the security state of an
 * interrupt, to be either secure or non-secure. You can only access these
 * registers with secure read or secure write accesses.
 * NOTE: The GICD_ISR register at address offset 0x0080 is banked, that is
 *       there is one per CPU Interface. It is only accessible from the
 *       designated CPU and controls that CPU's PPI and SGI interrupts. The
 *       remaining registers control the SPI interrupts.
 */
#define GICD_ISR(inst, n)		GICD_1BIT_REG(inst, 0x80, n)

/* 2.16.1.7.3.41. GICC_CTLR (0x0FF 6FA4 2000) */
#define GICC_ENABLE_GRP1_NS		_BV(1)
#define GICC_ACKCTL			_BV(2)
#define GICC_S_DEST			_BV(3)
#define GICC_SBPR			_BV(4)
#define GICC_FIQ_BYP_DIS_NS		_BV(7)
#define GICC_IRQ_BYP_DIS_NS		_BV(8)
#define GICC_EOIMODE			GICC_EOI_MODE_NS
#define GICC_EOIMODE_NS			_BV(10)

/* 2.16.1.7.3.42. GICC_PMR (0x0FF 6FA4 2004) */
#define GICC_PRIORITY_NS		_BV(7)

#ifdef CONFIG_GICv2
extern irqc_t qgic2_irqc;

void qgic2_handle_irq(void);
void qgic2_init(void*);
#else
#define qgic2_irqc		INVALID_IRQC

static inline void qgic2_handle_irq(void)
{
}

static inline void qgic2_init(void)
{
}
#endif

#endif /* __QGIC2_QDF2400_H_INCLUDE__ */
