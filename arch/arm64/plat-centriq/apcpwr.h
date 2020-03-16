/*
 * Copyright (c) 2016 Qualcomm Datacenter Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Datacenter Technologies, Inc.
 *
 * Copyright (c) 2014-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef __QDF2400_APCPWR_H__
#define __QDF2400_APCPWR_H__

#include <asm/mach/hal/HALapcpwrHWIO.h>
#include <asm/mach/hal/msmhwiobase.h>

/*
 * The following HWIO macros provide access to power controller registers
 * indexed by Rail, Duplex, Core.
 */

#define HWIO_APCS_HPSS_OFFSET                               0x8000
#define HWIO_APCS_APR_OFFSET                                0x8000

#define HWIO_APCS_APC_DCVS_APC_OFFSET                       0x800
#define HWIO_APCS_APC_APC_CFG_OFFSET                        0x800
#define HWIO_APCS_APC_APC_STS_OFFSET                        0x800
#define HWIO_APCS_APC_APC_TZ_OFFSET                         0x800
#define HWIO_APCS_APC_L2_CFG_OFFSET                         0x800
#define HWIO_APCS_APC_L2_STS_OFFSET                         0x800
#define HWIO_APCS_APC_L2_PWR_CTL_OFFSET                     0x800
#define HWIO_APCS_APC_L2_SW_EVENT_OFFSET                    0x800
#define HWIO_APCS_APC_L2_WAR_OFFSET                         0x800
#define HWIO_APCS_APC_L2_DBG_OFFSET                         0x800
#define HWIO_APCS_APC_L2_DATA_PUSH_OFFSET                   0x100

#define HWIO_APCS_CPU_OFFSET                                0x800

/*
 * Register region bases, addresses and field bitmasks and shifts
 */

/* HPSS ("parallel" to rails) */
#define HWIO_APCS_HPSS_OFFS(r)                               \
            ( HWIO_APCS_HPSS_OFFSET * r )

#define HWIO_APCS_HPSS_ADDR(r, hwiomod, hwiosym)             \
            ( HWIO_APCS_HPSS_OFFS(r) +                       \
              APCS_HPSS0_##hwiomod##_REG_BASE +              \
              HWIO_APCS_HPSS0_##hwiosym##_OFFS )

#define HWIO_APCS_HPSS_BMSK(hwiosym, hwiofld)                \
            HWIO_APCS_HPSS0_##hwiosym##_##hwiofld##_BMSK

#define HWIO_APCS_HPSS_SHFT(hwiosym, hwiofld)                \
            HWIO_APCS_HPSS0_##hwiosym##_##hwiofld##_SHFT

/* Rail */
#define HWIO_APCS_APR_OFFS(r)                               \
            ( HWIO_APCS_APR_OFFSET * r )

#define HWIO_APCS_APR_ADDR(r, hwiomod, hwiosym)             \
            ( HWIO_APCS_APR_OFFS(r) +                       \
              APCS_APR0_##hwiomod##_REG_BASE +              \
              HWIO_APCS_APR0_##hwiosym##_OFFS )

#define HWIO_APCS_APR_ADDRI(r, hwiomod, hwiosym, i)         \
            ( HWIO_APCS_APR_OFFS(r) +                       \
              APCS_APR0_##hwiomod##_REG_BASE +              \
              HWIO_APCS_APR0_##hwiosym##_n_OFFS(0, i) )

#define HWIO_APCS_APR_BMSK(hwiosym, hwiofld)                \
            HWIO_APCS_APR0_##hwiosym##_##hwiofld##_BMSK

#define HWIO_APCS_APR_SHFT(hwiosym, hwiofld)                \
            HWIO_APCS_APR0_##hwiosym##_##hwiofld##_SHFT

/* Cluster */
#define HWIO_APCS_APC_OFFS(d, hwiomod)                      \
            ( HWIO_APCS_APR_OFFS(CLU_TO_RAIL_IDX(d)) +      \
              (HWIO_APCS_APC_##hwiomod##_OFFSET * CLU_ON_RAIL_IDX(d)))

#define HWIO_APCS_APC_ADDR(d, hwiomod, hwiosym)             \
            ( HWIO_APCS_APC_OFFS(d, hwiomod) +              \
              APCS_APC00_##hwiomod##_REG_BASE +             \
              HWIO_APCS_APC00_##hwiosym##_OFFS )

#define HWIO_APCS_APC_BMSK(hwiosym, hwiofld)                \
            HWIO_APCS_APC00_##hwiosym##_##hwiofld##_BMSK

#define HWIO_APCS_APC_SHFT(hwiosym, hwiofld)                \
            HWIO_APCS_APC00_##hwiosym##_##hwiofld##_SHFT

/* Core */
#define HWIO_APCS_CPU_OFFS(c)                               \
            ( HWIO_APCS_APR_OFFS(CPU_TO_RAIL_IDX(c)) +      \
              (HWIO_APCS_CPU_OFFSET * CPU_ON_RAIL_IDX(c)))

#define HWIO_APCS_CPU_ADDR(c, hwiomod, hwiosym)             \
            ( HWIO_APCS_CPU_OFFS(c) +                       \
              APCS_APC00_CPU0_##hwiomod##_REG_BASE +        \
              HWIO_APCS_APC00_CPU0_##hwiosym##_OFFS )

#define HWIO_APCS_CPU_BMSK(hwiosym, hwiofld)                \
            HWIO_APCS_APC00_CPU0_##hwiosym##_##hwiofld##_BMSK

#define HWIO_APCS_CPU_SHFT(hwiosym, hwiofld)                \
            HWIO_APCS_APC00_CPU0_##hwiosym##_##hwiofld##_SHFT

/* Register IN */
#define APCS_HWIO_INH(r, hwiomod, hwiosym)                  \
            __raw_readl(HWIO_APCS_HPSS_ADDR(r, hwiomod, hwiosym))

#define APCS_HWIO_INR(r, hwiomod, hwiosym)                  \
            __raw_readl(HWIO_APCS_APR_ADDR(r, hwiomod, hwiosym))

#define APCS_HWIO_IND(d, hwiomod, hwiosym)                  \
            __raw_readl(HWIO_APCS_APC_ADDR(d, hwiomod, hwiosym))

#define APCS_HWIO_INC(c, hwiomod, hwiosym)                  \
            __raw_readl(HWIO_APCS_CPU_ADDR(c, hwiomod, hwiosym))

/* Register OUT */
#define APCS_HWIO_OUTH(r, hwiomod, hwiosym, val)            \
            __raw_writel(val, HWIO_APCS_HPSS_ADDR(r, hwiomod, hwiosym) )

#define APCS_HWIO_OUTR(r, hwiomod, hwiosym, val)            \
            __raw_writel(val, HWIO_APCS_APR_ADDR(r, hwiomod, hwiosym))

#define APCS_HWIO_OUTD(d, hwiomod, hwiosym, val)            \
            __raw_writel(val, HWIO_APCS_APC_ADDR(d, hwiomod, hwiosym))

#define APCS_HWIO_OUTC(c, hwiomod, hwiosym, val)            \
            __raw_writel(val, HWIO_APCS_CPU_ADDR(c, hwiomod, hwiosym))

/* Register OUT indexed */
#define APCS_HWIO_OUTRI(r, hwiomod, hwiosym, i, val)        \
            __raw_writel(val, HWIO_APCS_APR_ADDRI(r, hwiomod, hwiosym, i))

/* Register IN masked */
#define APCS_HWIO_INHM(r, hwiomod, hwiosym, mask)           \
            (__raw_readl(HWIO_APCS_HPSS_ADDR(r, hwiomod, hwiosym)) & (mask))

#define APCS_HWIO_INRM(r, hwiomod, hwiosym, mask)           \
            (__raw_readl(HWIO_APCS_APR_ADDR(r, hwiomod, hwiosym)) & (mask))

#define APCS_HWIO_INDM(d, hwiomod, hwiosym, mask)           \
            (__raw_readl(HWIO_APCS_APC_ADDR(d, hwiomod, hwiosym)) & (mask))

#define APCS_HWIO_INCM(c, hwiomod, hwiosym, mask)           \
            (__raw_readl(HWIO_APCS_CPU_ADDR(c, hwiomod, hwiosym)) & (mask))

/* Register OUT masked */
#define APCS_HWIO_OUTHM(r, hwiomod, hwiosym, mask, val)             \
            __raw_writel((APCS_HWIO_INHM(r, hwiomod, hwiosym, ~(mask)) | ((val) & (mask))), \
			HWIO_APCS_HPSS_ADDR(r, hwiomod, hwiosym))

#define APCS_HWIO_OUTRM(r, hwiomod, hwiosym, mask, val)             \
            __raw_writel((APCS_HWIO_INRM(r, hwiomod, hwiosym, ~(mask)) | ((val) & (mask))) ,\
            HWIO_APCS_APR_ADDR(r, hwiomod, hwiosym))

#define APCS_HWIO_OUTDM(d, hwiomod, hwiosym, mask, val)             \
            __raw_writel((APCS_HWIO_INDM(d, hwiomod, hwiosym, ~(mask)) | ((val) & (mask))),\
			(long)HWIO_APCS_APC_ADDR(d, hwiomod, hwiosym))

#define APCS_HWIO_OUTCM(c, hwiomod, hwiosym, mask, val)             \
            __raw_writel((APCS_HWIO_INCM(c, hwiomod, hwiosym, ~(mask)) | ((val) & (mask))),\
            HWIO_APCS_CPU_ADDR(c, hwiomod, hwiosym))

/* Register field IN */
#define APCS_HWIO_INHF(r, hwiomod, hwiosym, hwiofld)                \
            (APCS_HWIO_INHM(r, hwiomod, hwiosym,                    \
                HWIO_APCS_HPSS_BMSK(hwiosym, hwiofld)) >>           \
                HWIO_APCS_HPSS_SHFT(hwiosym, hwiofld))

#define APCS_HWIO_INRF(r, hwiomod, hwiosym, hwiofld)                \
            (APCS_HWIO_INRM(r, hwiomod, hwiosym,                    \
                HWIO_APCS_APR_BMSK(hwiosym, hwiofld)) >>            \
                HWIO_APCS_APR_SHFT(hwiosym, hwiofld))

#define APCS_HWIO_INDF(d, hwiomod, hwiosym, hwiofld)                \
            (APCS_HWIO_INDM(d, hwiomod, hwiosym,                    \
                HWIO_APCS_APC_BMSK(hwiosym, hwiofld)) >>            \
                HWIO_APCS_APC_SHFT(hwiosym, hwiofld))

#define APCS_HWIO_INCF(c, hwiomod, hwiosym, hwiofld)                \
            (APCS_HWIO_INCM(c, hwiomod, hwiosym,                    \
                HWIO_APCS_CPU_BMSK(hwiosym, hwiofld)) >>            \
                HWIO_APCS_CPU_SHFT(hwiosym, hwiofld))

/* Register field OUT */
#define APCS_HWIO_OUTHF(r, hwiomod, hwiosym, hwiofld, val)          \
            APCS_HWIO_OUTHM(r, hwiomod, hwiosym,                    \
                HWIO_APCS_HPSS_BMSK(hwiosym, hwiofld),              \
                (val) << HWIO_APCS_HPSS_SHFT(hwiosym, hwiofld))

#define APCS_HWIO_OUTRF(r, hwiomod, hwiosym, hwiofld, val)          \
            APCS_HWIO_OUTRM(r, hwiomod, hwiosym,                    \
                HWIO_APCS_APR_BMSK(hwiosym, hwiofld),               \
                (val) << HWIO_APCS_APR_SHFT(hwiosym, hwiofld))

#define APCS_HWIO_OUTDF(d, hwiomod, hwiosym, hwiofld, val)          \
            APCS_HWIO_OUTDM(d, hwiomod, hwiosym,                    \
                HWIO_APCS_APC_BMSK(hwiosym, hwiofld),               \
                (val) << HWIO_APCS_APC_SHFT(hwiosym, hwiofld))

#define APCS_HWIO_OUTCF(c, hwiomod, hwiosym, hwiofld, val)          \
            APCS_HWIO_OUTCM(c, hwiomod, hwiosym,                    \
                HWIO_APCS_CPU_BMSK(hwiosym, hwiofld),               \
                (val) << HWIO_APCS_CPU_SHFT(hwiosym, hwiofld))


#ifndef __ASSEMBLY__


/* Core and cluster level low power states to enter on CPU_OFF */
#define CPU_OFF_LPM             5
#define CLU_OFF_LPM             5

/* Timeout for placing cores/clusters into SPM control */
#define SPM_WAIT_TIMEOUT_US     20000 /* 10 ms */
#define SPM_WAIT_POLL_PERIOD_US 10
#define SPM_WAIT_POLL_COUNT     ((SPM_WAIT_TIMEOUT_US) / (SPM_WAIT_POLL_PERIOD_US))


/*******************************************************************************
 * Function & variable prototypes
 ******************************************************************************/

extern void apcpwr_init(void);

extern int apcpwr_cpu_wakeup(unsigned long cpu);

extern void apcpwr_cpu_enter_lpm(unsigned long cpu, unsigned int lpm);
extern void apcpwr_cpu_exit_lpm(unsigned long cpu, unsigned int lpm);

extern void apcpwr_clu_enter_lpm(unsigned long clu, unsigned int lpm);
extern void apcpwr_clu_exit_lpm(unsigned long clu, unsigned int lpm);

extern void apcpwr_apr_enter_lpm(unsigned long apr, unsigned int lpm);
extern void apcpwr_apr_exit_lpm(unsigned long apr, unsigned int lpm);

#endif /*__ASSEMBLY__*/

#endif /* __QDF2400_APCPWR_H__ */
