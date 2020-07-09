/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __IO_PGTABLE_H
#define __IO_PGTABLE_H
#include <target/bitops.h>
#include <target/memory.h>
#include <target/barrier.h>

#include <target/regdef.h>
#include <target/utils.h>
#include <asm/io.h>

#define LOGLEVEL 3
#define dev_printk(dev, fmt, ...)				\
({								\
	printf(fmt, ##__VA_ARGS__);				\
})

#define __dev_printk(level, dev, fmt, ...)			\
({								\
	if (level < LOGLEVEL)			\
		dev_printk(dev, fmt, ##__VA_ARGS__);		\
})

#define dev_emerg(dev, fmt, ...) \
	__dev_printk(0, dev, fmt, ##__VA_ARGS__)
#define dev_alert(dev, fmt, ...) \
	__dev_printk(1, dev, fmt, ##__VA_ARGS__)
#define dev_crit(dev, fmt, ...) \
	__dev_printk(2, dev, fmt, ##__VA_ARGS__)
#define dev_err(dev, fmt, ...) \
	__dev_printk(3, dev, fmt, ##__VA_ARGS__)
#define dev_warn(dev, fmt, ...) \
	__dev_printk(4, dev, fmt, ##__VA_ARGS__)
#define dev_notice(dev, fmt, ...) \
	__dev_printk(5, dev, fmt, ##__VA_ARGS__)
#define dev_info(dev, fmt, ...) \
	__dev_printk(6, dev, fmt, ##__VA_ARGS__)

#ifndef __attribute_const__
# define __attribute_const__	/* unimplemented */
#endif


#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))

#define  BITS_PER_BYTE 8
#ifndef BITS_PER_LONG_LONG
#define BITS_PER_LONG_LONG 64
#endif

/*
 * Create a contiguous bitmask starting at bit position @l and ending at
 * position @h. For example
 * GENMASK_ULL(39, 21) gives us the 64bit vector 0x000000ffffe00000.
 */
#ifdef CONFIG_SANDBOX
#define GENMASK(h, l) \
	(((~0UL) << (l)) & (~0UL >> (CONFIG_SANDBOX_BITS_PER_LONG - 1 - (h))))
#else
#define GENMASK(h, l) \
	(((~0UL) << (l)) & (~0UL >> (BITS_PER_LONG - 1 - (h))))
#endif

#define GENMASK_ULL(h, l) \
	(((~0ULL) << (l)) & (~0ULL >> (BITS_PER_LONG_LONG - 1 - (h))))

#define WRITE_ONCE(x, val)              (*(volatile typeof(x) *)&(x) = val)
#define __READ_ONCE_SIZE						\
({									\
	switch (size) {							\
	case 1: *(u8 *)res = *(volatile u8 *)p; break;		\
	case 2: *(u16 *)res = *(volatile u16 *)p; break;		\
	case 4: *(u32 *)res = *(volatile u32 *)p; break;		\
	case 8: *(u64 *)res = *(volatile u64 *)p; break;		\
	default:							\
		barrier();						\
		__builtin_memcpy((void *)res, (const void *)p, size);	\
		barrier();						\
	}								\
})

static __always_inline
void __read_once_size(const volatile void *p, void *res, int size)
{
	__READ_ONCE_SIZE;
}
#define __READ_ONCE(x, check)						\
({									\
	union { typeof(x) __val; char __c[1]; } __u;			\
	if (check)							\
		__read_once_size(&(x), __u.__c, sizeof(x));		\
	__u.__val;							\
})
#define READ_ONCE(x) __READ_ONCE(x, 1)

#define __bf_shf(x) (__builtin_ffsll(x) - 1)

#define FIELD_PREP(_mask, _val)						\
	({								\
		((typeof(_mask))(_val) << __bf_shf(_mask)) & (_mask);	\
	})

#define FIELD_GET(_mask, _reg)						\
	({								\
		(typeof(_mask))(((_reg) & (_mask)) >> __bf_shf(_mask));	\
	})

#define atomic_set(v, i)                WRITE_ONCE(((v)->counter), (i))

typedef struct {
	int counter;
}atomic_t;
typedef struct {
	long long counter;
}atomic64_t;

#define __ARG_PLACEHOLDER_1 0,
#define config_enabled(cfg) _config_enabled(cfg)
#define _config_enabled(value) __config_enabled(__ARG_PLACEHOLDER_##value)
#define __config_enabled(arg1_or_junk) ___config_enabled(arg1_or_junk 1, 0)
#define ___config_enabled(__ignored, val, ...) val
/*
 * IS_ENABLED(CONFIG_FOO) evaluates to 1 if CONFIG_FOO is set to 'y' or 'm',
 * 0 otherwise.
 *
 */
#define IS_ENABLED(option) \
	(config_enabled(option) || config_enabled(option##_MODULE))


#define readb_relaxed(c)	({ u8  __r = __raw_readb(c); __r; })
#define readw_relaxed(c)	({ u16 __r = le16_to_cpu((__force __le16) \
						__raw_readw(c)); __r; })
#define readl_relaxed(c)	({ u32 __r = le32_to_cpu((__force __le32) \
						__raw_readl(c)); __r; })
#define readq_relaxed(c)	({ u64 __r = le64_to_cpu((__force __le64) \
						__raw_readq(c)); __r; })

#define writeb_relaxed(v, c)	((void)__raw_writeb((v), (c)))
#define writew_relaxed(v, c)	((void)__raw_writew((__force u16) \
						    cpu_to_le16(v), (c)))
#define writel_relaxed(v, c)	((void)__raw_writel((__force u32) \
						    cpu_to_le32(v), (c)))
#define writeq_relaxed(v, c)	((void)__raw_writeq((__force u64) \
						    cpu_to_le64(v), (c)))

#define readl __raw_readl
#define writel __raw_writel
/////////////////////////new added declaration///////////////////////////////////////
#define IOMMU_READ	(1 << 0)
#define IOMMU_WRITE	(1 << 1)
#define IOMMU_CACHE	(1 << 2) /* DMA cache coherency */
#define IOMMU_NOEXEC	(1 << 3)
#define IOMMU_MMIO	(1 << 4) /* e.g. things like MSI doorbells */
#define IOMMU_PRIV	(1 << 5)
/*
 * Public API for use by IOMMU drivers
 */
enum io_pgtable_fmt {
	ARM_32_LPAE_S1,
	ARM_32_LPAE_S2,
	ARM_64_LPAE_S1,
	ARM_64_LPAE_S2,
	ARM_V7S,
	IO_PGTABLE_NUM_FMTS,
};

/**
 * struct iommu_gather_ops - IOMMU callbacks for TLB and page table management.
 *
 * @tlb_flush_all: Synchronously invalidate the entire TLB context.
 * @tlb_add_flush: Queue up a TLB invalidation for a virtual address range.
 * @tlb_sync:      Ensure any queued TLB invalidation has taken effect, and
 *                 any corresponding page table updates are visible to the
 *                 IOMMU.
 *
 * Note that these can all be called in atomic context and must therefore
 * not block.
 */
struct iommu_gather_ops {
	void (*tlb_flush_all)(void *cookie);
	void (*tlb_add_flush)(unsigned long iova, size_t size, size_t granule,
			      bool leaf, void *cookie);
	void (*tlb_sync)(void *cookie);
};

/**
 * struct io_pgtable_cfg - Configuration data for a set of page tables.
 *
 * @quirks:        A bitmap of hardware quirks that require some special
 *                 action by the low-level page table allocator.
 * @pgsize_bitmap: A bitmap of page sizes supported by this set of page
 *                 tables.
 * @ias:           Input address (iova) size, in bits.
 * @oas:           Output address (paddr) size, in bits.
 * @tlb:           TLB management callbacks for this set of tables.
 * @iommu_dev:     The device representing the DMA configuration for the
 *                 page table walker.
 */
struct io_pgtable_cfg {
	/*
	 * IO_PGTABLE_QUIRK_ARM_NS: (ARM formats) Set NS and NSTABLE bits in
	 *	stage 1 PTEs, for hardware which insists on validating them
	 *	even in	non-secure state where they should normally be ignored.
	 *
	 * IO_PGTABLE_QUIRK_NO_PERMS: Ignore the IOMMU_READ, IOMMU_WRITE and
	 *	IOMMU_NOEXEC flags and map everything with full access, for
	 *	hardware which does not implement the permissions of a given
	 *	format, and/or requires some format-specific default value.
	 *
	 * IO_PGTABLE_QUIRK_TLBI_ON_MAP: If the format forbids caching invalid
	 *	(unmapped) entries but the hardware might do so anyway, perform
	 *	TLB maintenance when mapping as well as when unmapping.
	 *
	 * IO_PGTABLE_QUIRK_ARM_MTK_4GB: (ARM v7s format) Set bit 9 in all
	 *	PTEs, for Mediatek IOMMUs which treat it as a 33rd address bit
	 *	when the SoC is in "4GB mode" and they can only access the high
	 *	remap of DRAM (0x1_00000000 to 0x1_ffffffff).
	 *
	 * IO_PGTABLE_QUIRK_NO_DMA: Guarantees that the tables will only ever
	 *	be accessed by a fully cache-coherent IOMMU or CPU (e.g. for a
	 *	software-emulated IOMMU), such that pagetable updates need not
	 *	be treated as explicit DMA data.
	 */
	#define IO_PGTABLE_QUIRK_ARM_NS		BIT(0)
	#define IO_PGTABLE_QUIRK_NO_PERMS	BIT(1)
	#define IO_PGTABLE_QUIRK_TLBI_ON_MAP	BIT(2)
	#define IO_PGTABLE_QUIRK_ARM_MTK_4GB	BIT(3)
	#define IO_PGTABLE_QUIRK_NO_DMA		BIT(4)
	unsigned long			quirks;
	unsigned long			pgsize_bitmap;
	unsigned int			ias;
	unsigned int			oas;
	const struct iommu_gather_ops	*tlb;
	struct device			*iommu_dev;

	/* Low-level data specific to the table format */
	union {
		struct {
			u64	ttbr[2];
			u64	tcr;
			u64	mair[2];
		} arm_lpae_s1_cfg;

		struct {
			u64	vttbr;
			u64	vtcr;
		} arm_lpae_s2_cfg;

		struct {
			u32	ttbr[2];
			u32	tcr;
			u32	nmrr;
			u32	prrr;
		} arm_v7s_cfg;
	};
};

/**
 * struct io_pgtable_ops - Page table manipulation API for IOMMU drivers.
 *
 * @map:          Map a physically contiguous memory region.
 * @unmap:        Unmap a physically contiguous memory region.
 * @iova_to_phys: Translate iova to physical address.
 *
 * These functions map directly onto the iommu_ops member functions with
 * the same names.
 */
struct io_pgtable_ops {
	int (*map)(struct io_pgtable_ops *ops, unsigned long iova,
		   phys_addr_t paddr, size_t size, int prot);
	size_t (*unmap)(struct io_pgtable_ops *ops, unsigned long iova,
			size_t size);
	phys_addr_t (*iova_to_phys)(struct io_pgtable_ops *ops,
				    unsigned long iova);
};

/**
 * alloc_io_pgtable_ops() - Allocate a page table allocator for use by an IOMMU.
 *
 * @fmt:    The page table format.
 * @cfg:    The page table configuration. This will be modified to represent
 *          the configuration actually provided by the allocator (e.g. the
 *          pgsize_bitmap may be restricted).
 * @cookie: An opaque token provided by the IOMMU driver and passed back to
 *          the callback routines in cfg->tlb.
 */
struct io_pgtable_ops *alloc_io_pgtable_ops(enum io_pgtable_fmt fmt,
					    struct io_pgtable_cfg *cfg,
					    void *cookie);

/**
 * free_io_pgtable_ops() - Free an io_pgtable_ops structure. The caller
 *                         *must* ensure that the page table is no longer
 *                         live, but the TLB can be dirty.
 *
 * @ops: The ops returned from alloc_io_pgtable_ops.
 */
void free_io_pgtable_ops(struct io_pgtable_ops *ops);


/*
 * Internal structures for page table allocator implementations.
 */

/**
 * struct io_pgtable - Internal structure describing a set of page tables.
 *
 * @fmt:    The page table format.
 * @cookie: An opaque token provided by the IOMMU driver and passed back to
 *          any callback routines.
 * @cfg:    A copy of the page table configuration.
 * @ops:    The page table operations in use for this set of page tables.
 */
struct io_pgtable {
	enum io_pgtable_fmt	fmt;
	void			*cookie;
	struct io_pgtable_cfg	cfg;
	struct io_pgtable_ops	ops;
};

#define io_pgtable_ops_to_pgtable(x) container_of((x), struct io_pgtable, ops)

static inline void io_pgtable_tlb_flush_all(struct io_pgtable *iop)
{
	iop->cfg.tlb->tlb_flush_all(iop->cookie);
}

static inline void io_pgtable_tlb_add_flush(struct io_pgtable *iop,
		unsigned long iova, size_t size, size_t granule, bool leaf)
{
	iop->cfg.tlb->tlb_add_flush(iova, size, granule, leaf, iop->cookie);
}

static inline void io_pgtable_tlb_sync(struct io_pgtable *iop)
{
	iop->cfg.tlb->tlb_sync(iop->cookie);
}

/**
 * struct io_pgtable_init_fns - Alloc/free a set of page tables for a
 *                              particular format.
 *
 * @alloc: Allocate a set of page tables described by cfg.
 * @free:  Free the page tables associated with iop.
 */
struct io_pgtable_init_fns {
	struct io_pgtable *(*alloc)(struct io_pgtable_cfg *cfg, void *cookie);
	void (*free)(struct io_pgtable *iop);
};

extern struct io_pgtable_init_fns io_pgtable_arm_32_lpae_s1_init_fns;
extern struct io_pgtable_init_fns io_pgtable_arm_32_lpae_s2_init_fns;
extern struct io_pgtable_init_fns io_pgtable_arm_64_lpae_s1_init_fns;
extern struct io_pgtable_init_fns io_pgtable_arm_64_lpae_s2_init_fns;
extern struct io_pgtable_init_fns io_pgtable_arm_v7s_init_fns;

#define PAGE_SHIFT 12
static inline __attribute_const__
int __get_order(unsigned long size)
{
	int order;

	size--;
	size >>= PAGE_SHIFT;
#if BITS_PER_LONG == 32
	order = fls(size);
#else
	order = fls64(size);
#endif
	return order;
}

/**
 * get_order - Determine the allocation order of a memory size
 * @size: The size for which to get the order
 *
 * Determine the allocation order of a particular sized block of memory.  This
 * is on a logarithmic scale, where:
 *
 *	0 -> 2^0 * PAGE_SIZE and below
 *	1 -> 2^1 * PAGE_SIZE to 2^0 * PAGE_SIZE + 1
 *	2 -> 2^2 * PAGE_SIZE to 2^1 * PAGE_SIZE + 1
 *	3 -> 2^3 * PAGE_SIZE to 2^2 * PAGE_SIZE + 1
 *	4 -> 2^4 * PAGE_SIZE to 2^3 * PAGE_SIZE + 1
 *	...
 *
 * The order returned is used to find the smallest allocation granule required
 * to hold an object of the specified size.
 *
 * The result is undefined if the size is 0.
 *
 * This function may be used to initialise variables with compile time
 * evaluations of constants.
 */
#define get_order(n)						\
(								\
	__builtin_constant_p(n) ? (				\
		((n) == 0UL) ? BITS_PER_LONG - PAGE_SHIFT :	\
		(((n) < (1UL << PAGE_SHIFT)) ? 0 :		\
		 __ilog2((n) - 1) - PAGE_SHIFT + 1)		\
	) :							\
	__get_order(n)						\
)

#endif /* __IO_PGTABLE_H */
