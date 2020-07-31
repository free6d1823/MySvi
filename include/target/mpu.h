#ifndef __MPU_H__
#define __MPU_H__

/* MPUIR layout */
#define MPUIR_nU		1
#define MPUIR_DREGION		8
#define MPUIR_IREGION		16
#define MPUIR_DREGION_SZMASK	(0xFF << MPUIR_DREGION)
#define MPUIR_IREGION_SZMASK	(0xFF << MPUIR_IREGION)

/* ID_MMFR0 data relevant to MPU */
#define MMFR0_PMSA		(0xF << 4)
#define MMFR0_PMSAv7		(3 << 4)
#define MMFR0_PMSAv8		(4 << 4)

/* MPU D/I Size Register fields */
#define PMSAv7_RSR_SZ		1
#define PMSAv7_RSR_EN		0
#define PMSAv7_RSR_SD		8

/* Number of subregions (SD) */
#define PMSAv7_NR_SUBREGS	8
#define PMSAv7_MIN_SUBREG_SIZE	256

/* The D/I RSR value for an enabled region spanning the whole of memory */
#define PMSAv7_RSR_ALL_MEM	63

/* Individual bits in the DR/IR ACR */
#define PMSAv7_ACR_XN		(1 << 12)
#define PMSAv7_ACR_SHARED	(1 << 2)

/* C, B and TEX[2:0] bits only have semantic meanings when grouped */
#define PMSAv7_RGN_CACHEABLE		0xB
#define PMSAv7_RGN_SHARED_CACHEABLE	(PMSAv7_RGN_CACHEABLE | PMSAv7_ACR_SHARED)
#define PMSAv7_RGN_STRONGLY_ORDERED	0

/* Main region should only be shared for SMP */
#ifdef CONFIG_SMP
#define PMSAv7_RGN_NORMAL	(PMSAv7_RGN_CACHEABLE | PMSAv7_ACR_SHARED)
#else
#define PMSAv7_RGN_NORMAL	PMSAv7_RGN_CACHEABLE
#endif

/* Access permission bits of ACR (only define those that we use)*/
#define PMSAv7_AP_PL1RO_PL0NA	(0x5 << 8)
#define PMSAv7_AP_PL1RW_PL0RW	(0x3 << 8)
#define PMSAv7_AP_PL1RW_PL0R0	(0x2 << 8)
#define PMSAv7_AP_PL1RW_PL0NA	(0x1 << 8)

#define PMSAv8_BAR_XN		1

#define PMSAv8_LAR_EN		1
#define PMSAv8_LAR_IDX(n)	(((n) & 0x7) << 1)


#define PMSAv8_AP_PL1RW_PL0NA	(0 << 1)
#define PMSAv8_AP_PL1RW_PL0RW	(1 << 1)
#define PMSAv8_AP_PL1RO_PL0RO	(3 << 1)

#ifdef CONFIG_SMP
#define PMSAv8_RGN_SHARED	(3 << 3) // inner sharable
#else
#define PMSAv8_RGN_SHARED	(0 << 3)
#endif

#define PMSAv8_RGN_DEVICE_nGnRnE	0
#define PMSAv8_RGN_NORMAL		1

#define PMSAv8_MAIR(attr, mt)	((attr) << ((mt) * 8))

#ifdef CONFIG_CPU_V7M
#define PMSAv8_MINALIGN		32
#else
#define PMSAv8_MINALIGN		64
#endif

#ifndef __ASSEMBLY__

/* pmsa-v7 */
#ifndef CONFIG_CPU_V7M

#define DRBAR	__ACCESS_CP15(c6, 0, c1, 0)
#define IRBAR	__ACCESS_CP15(c6, 0, c1, 1)
#define DRSR	__ACCESS_CP15(c6, 0, c1, 2)
#define IRSR	__ACCESS_CP15(c6, 0, c1, 3)
#define DRACR	__ACCESS_CP15(c6, 0, c1, 4)
#define IRACR	__ACCESS_CP15(c6, 0, c1, 5)
#define RNGNR	__ACCESS_CP15(c6, 0, c2, 0)

/* Region number */
static inline void rgnr_write(u32 v)
{
	write_sysreg(v, RNGNR);
}

/* Data-side / unified region attributes */

/* Region access control register */
static inline void dracr_write(u32 v)
{
	write_sysreg(v, DRACR);
}

/* Region size register */
static inline void drsr_write(u32 v)
{
	write_sysreg(v, DRSR);
}

/* Region base address register */
static inline void drbar_write(u32 v)
{
	write_sysreg(v, DRBAR);
}

static inline u32 drbar_read(void)
{
	return read_sysreg(DRBAR);
}
/* Optional instruction-side region attributes */

/* I-side Region access control register */
static inline void iracr_write(u32 v)
{
	write_sysreg(v, IRACR);
}

/* I-side Region size register */
static inline void irsr_write(u32 v)
{
	write_sysreg(v, IRSR);
}

/* I-side Region base address register */
static inline void irbar_write(u32 v)
{
	write_sysreg(v, IRBAR);
}

static inline u32 irbar_read(void)
{
	return read_sysreg(IRBAR);
}

#else

static inline void rgnr_write(u32 v)
{
	writel_relaxed(v, BASEADDR_V7M_SCB + PMSAv7_RNR);
}

/* Data-side / unified region attributes */

/* Region access control register */
static inline void dracr_write(u32 v)
{
	u32 rsr = readl_relaxed(BASEADDR_V7M_SCB + PMSAv7_RASR) & GENMASK(15, 0);

	writel_relaxed((v << 16) | rsr, BASEADDR_V7M_SCB + PMSAv7_RASR);
}

/* Region size register */
static inline void drsr_write(u32 v)
{
	u32 racr = readl_relaxed(BASEADDR_V7M_SCB + PMSAv7_RASR) & GENMASK(31, 16);

	writel_relaxed(v | racr, BASEADDR_V7M_SCB + PMSAv7_RASR);
}

/* Region base address register */
static inline void drbar_write(u32 v)
{
	writel_relaxed(v, BASEADDR_V7M_SCB + PMSAv7_RBAR);
}

static inline u32 drbar_read(void)
{
	return readl_relaxed(BASEADDR_V7M_SCB + PMSAv7_RBAR);
}

/* ARMv7-M only supports a unified MPU, so I-side operations are nop */

static inline void iracr_write(u32 v) {}
static inline void irsr_write(u32 v) {}
static inline void irbar_write(u32 v) {}
static inline unsigned long irbar_read(void) {return 0;}

#endif


/* pmsa-v8 */
#ifndef CONFIG_CPU_V7M

#define PRSEL	__ACCESS_CP15(c6, 0, c2, 1)
#define PRBAR	__ACCESS_CP15(c6, 0, c3, 0)
#define PRLAR	__ACCESS_CP15(c6, 0, c3, 1)

static inline u32 prlar_read(void)
{
	return read_sysreg(PRLAR);
}

static inline u32 prbar_read(void)
{
	return read_sysreg(PRBAR);
}

static inline void prsel_write(u32 v)
{
	write_sysreg(v, PRSEL);
}

static inline void prbar_write(u32 v)
{
	write_sysreg(v, PRBAR);
}

static inline void prlar_write(u32 v)
{
	write_sysreg(v, PRLAR);
}
#else

static inline u32 prlar_read(void)
{
	return readl_relaxed(BASEADDR_V7M_SCB + PMSAv8_RLAR);
}

static inline u32 prbar_read(void)
{
	return readl_relaxed(BASEADDR_V7M_SCB + PMSAv8_RBAR);
}

static inline void prsel_write(u32 v)
{
	writel_relaxed(v, BASEADDR_V7M_SCB + PMSAv8_RNR);
}

static inline void prbar_write(u32 v)
{
	writel_relaxed(v, BASEADDR_V7M_SCB + PMSAv8_RBAR);
}

static inline void prlar_write(u32 v)
{
	writel_relaxed(v, BASEADDR_V7M_SCB + PMSAv8_RLAR);
}

#endif

#endif /* __ASSEMBLY__ */

#endif
