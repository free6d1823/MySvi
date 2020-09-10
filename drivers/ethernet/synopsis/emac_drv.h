/*
 * Copyright (c) 2020, Siengine. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _DW_EMAC_H_
#define _DW_EMAC_H_

#include <stdbool.h>

#define IOREMAP(x) x
#ifdef CONFIG_ARCH_DMA_ADDR_T_32BIT
typedef u32 emac_dma_addr_t;
#else
typedef u64 emac_dma_addr_t;
#endif

#ifdef CONFIG_ARCH_DMA_ADDR_T_32BIT
typedef u32 emac_phys_addr_t;
#else
typedef u64 emac_phys_addr_t;
#endif

#define readl_relaxed(c)	({ u32 __r = le32_to_cpu((__force __le32) \
						__raw_readl(c)); __r; })

#define writel_relaxed(v, c)	((void)__raw_writel((__force u32) \
						    cpu_to_le32(v), (c)))

#define dwceqos_read(lp, reg)						\
	readl_relaxed(((void __iomem *)((lp)->baseaddr)) + (reg))
#define dwceqos_write(lp, reg, val)					\
	writel_relaxed((val), ((void __iomem *)((lp)->baseaddr)) + (reg))

/* DMA ring descriptor. These are used as support descriptors for the HW DMA */
struct ring_desc {
	char *skb;
	emac_dma_addr_t mapping;
	size_t len;
};

/* DMA hardware descriptor */
struct dwceqos_dma_desc {
	u32	des0;
	u32	des1;
	u32	des2;
	u32	des3;
};
struct dwceqos_mmc_counters {
	u64 txlpitranscntr;
	u64 txpiuscntr;
	u64 txoversize_g;
	u64 txvlanpackets_g;
	u64 txpausepackets;
	u64 txexcessdef;
	u64 txpacketcount_g;
	u64 txoctetcount_g;
	u64 txcarriererror;
	u64 txexcesscol;
	u64 txlatecol;
	u64 txdeferred;
	u64 txmulticol_g;
	u64 txsinglecol_g;
	u64 txunderflowerror;
	u64 txbroadcastpackets_gb;
	u64 txmulticastpackets_gb;
	u64 txunicastpackets_gb;
	u64 tx1024tomaxoctets_gb;
	u64 tx512to1023octets_gb;
	u64 tx256to511octets_gb;
	u64 tx128to255octets_gb;
	u64 tx65to127octets_gb;
	u64 tx64octets_gb;
	u64 txmulticastpackets_g;
	u64 txbroadcastpackets_g;
	u64 txpacketcount_gb;
	u64 txoctetcount_gb;

	u64 rxlpitranscntr;
	u64 rxlpiuscntr;
	u64 rxctrlpackets_g;
	u64 rxrcverror;
	u64 rxwatchdog;
	u64 rxvlanpackets_gb;
	u64 rxfifooverflow;
	u64 rxpausepackets;
	u64 rxoutofrangetype;
	u64 rxlengtherror;
	u64 rxunicastpackets_g;
	u64 rx1024tomaxoctets_gb;
	u64 rx512to1023octets_gb;
	u64 rx256to511octets_gb;
	u64 rx128to255octets_gb;
	u64 rx65to127octets_gb;
	u64 rx64octets_gb;
	u64 rxoversize_g;
	u64 rxundersize_g;
	u64 rxjabbererror;
	u64 rxrunterror;
	u64 rxalignmenterror;
	u64 rxcrcerror;
	u64 rxmulticastpackets_g;
	u64 rxbroadcastpackets_g;
	u64 rxoctetcount_g;
	u64 rxoctetcount_gb;
	u64 rxpacketcount_gb;
};

/* Configuration of AXI bus parameters.
 * These values depend on the parameters set on the MAC core as well
 * as the AXI interconnect.
 */
struct dwceqos_bus_cfg {
	/* Enable AXI low-power interface. */
	bool en_lpi;
	/* Limit on number of outstanding AXI write requests. */
	u32 write_requests;
	/* Limit on number of outstanding AXI read requests. */
	u32 read_requests;
	/* Bitmap of allowed AXI burst lengths, 4-256 beats. */
	u32 burst_map;
	/* DMA Programmable burst length*/
	u32 tx_pbl;
	u32 rx_pbl;
};

#define MTL_MAX_RX_QUEUES 4
#define MTL_MAX_TX_QUEUES 4

struct mac_rxq_cfg {
	u8 mode_to_use;
	u32 chan;
	u8 pkt_route;
	bool use_prio;
	u32 prio;
};

struct mac_txq_cfg {
	u32 weight;
	u8 mode_to_use;
	/* Credit Base Shaper parameters */
	u32 send_slope;
	u32 idle_slope;
	u32 high_credit;
	u32 low_credit;
	bool use_prio;
	u32 prio;
};
struct dwceqos_MTL_cfg {
	u32 rx_queues_count;
	u32 tx_queues_count;
	u32 tx_weight;
	u8 rx_sched_algorithm;
	u8 tx_sched_algorithm;
	bool init_ptp;
	struct mac_rxq_cfg rx_queues_cfg[MTL_MAX_RX_QUEUES];
	struct mac_txq_cfg tx_queues_cfg[MTL_MAX_TX_QUEUES];
};
struct net_device_ops {
	int			(*transmit)(void *dev);
	int			(*open)(void *dev);
	int			(*stop)(void *dev);
};

/* Frequently used values are kept adjacent for cache effect */
struct emac_tx_queue {
	u32 tx_count_frames;
	u32 queue_index;
	struct ring_desc *tx_skb_ring;
	/* DMA Descriptor Areas */
	struct dwceqos_dma_desc *tx_descs;
	/* DMA Mapped Descriptor areas*/
	emac_dma_addr_t tx_descs_addr;
	emac_dma_addr_t tx_descs_tail_addr;
	size_t tx_free;
	size_t tx_next;
	size_t tx_cur;
	/* Spinlocks for accessing DMA Descriptors */
	spinlock_t tx_lock;
};

struct emac_rx_queue {
	u32 queue_index;
	struct ring_desc *rx_skb_ring;
	/* DMA Descriptor Areas */
	struct dwceqos_dma_desc *rx_descs;
	emac_dma_addr_t rx_descs_addr;
	emac_dma_addr_t rx_descs_tail_addr;
	size_t rx_cur;
};
struct net_local {
	void __iomem *baseaddr;

	struct list_head    emac_list_entry;
	unsigned int link;
	unsigned int speed;
	unsigned int duplex;
	unsigned int gso_size;
	/* mac address */
	unsigned char mac_addr[6];
	/* RX Queue */
	struct emac_rx_queue rx_queues[MTL_MAX_RX_QUEUES];

	/* TX Queue */
	struct emac_tx_queue tx_queues[MTL_MAX_TX_QUEUES];

	/* Spinlock for register read-modify-writes. */
	spinlock_t hw_lock;

	u32 feature0;
	u32 feature1;
	u32 feature2;

	struct dwceqos_mmc_counters mmc_counters;
	/* Protect the mmc_counter updates. */
	spinlock_t stats_lock;
	u32 mmc_rx_counters_mask;
	u32 mmc_tx_counters_mask;

	struct dwceqos_bus_cfg bus_cfg;
};

struct dwceqos_tx {
	size_t nr_descriptors;
	size_t initial_descriptor;
	size_t last_descriptor;
	size_t prev_gso_size;
	size_t network_header_len;
};

/* Packets types */
enum packets_types {
	PACKET_AVCPQ = 0x1, /* AV Untagged Control packets */
	PACKET_PTPQ = 0x2, /* PTP Packets */
	PACKET_DCBCPQ = 0x3, /* DCB Control Packets */
	PACKET_UPQ = 0x4, /* Untagged Packets */
	PACKET_MCBCQ = 0x5, /* Multicast & Broadcast Packets */
};

#define DWCEQOS_TX_TIMEOUT 5 /* Seconds */

#define DWCEQOS_LPI_TIMER_MIN      8
#define DWCEQOS_LPI_TIMER_MAX      ((1 << 20) - 1)

#define DWCEQOS_RX_BUF_SIZE 2048
/*
#define DWCEQOS_RX_DCNT 256
#define DWCEQOS_TX_DCNT 256
 */
/* current svi heap is too small, HW requires at least 4*/
#define DWCEQOS_RX_DCNT 8
#define DWCEQOS_TX_DCNT 8

#define DWCEQOS_HASH_TABLE_SIZE 64

/* The size field in the DMA descriptor is 14 bits */
#define BYTES_PER_DMA_DESC 16376

/* Hardware registers */
#define START_MAC_REG_OFFSET    0x0000
#define MAX_MAC_REG_OFFSET      0x0bd0
#define START_MTL_REG_OFFSET    0x0c00
#define MAX_MTL_REG_OFFSET      0x0d7c
#define START_DMA_REG_OFFSET    0x1000
#define MAX_DMA_REG_OFFSET      0x117C

#define REG_SPACE_SIZE          0x1800

/* DMA */
#define REG_DWCEQOS_DMA_MODE             0x1000
#define REG_DWCEQOS_DMA_SYSBUS_MODE      0x1004
#define REG_DWCEQOS_DMA_IS               0x1008
#define REG_DWCEQOS_DMA_DEBUG_ST0        0x100c

/* DMA channel registers */
#define REG_DWCEQOS_DMA_CH0_CTRL         0x1100
#define REG_DWCEQOS_DMA_CH0_TX_CTRL      0x1104
#define REG_DWCEQOS_DMA_CH0_RX_CTRL      0x1108
#define REG_DWCEQOS_DMA_CH0_TXDESC_HLIST  0x1110
#define REG_DWCEQOS_DMA_CH0_TXDESC_LIST  0x1114
#define REG_DWCEQOS_DMA_CH0_RXDESC_HLIST  0x1118
#define REG_DWCEQOS_DMA_CH0_RXDESC_LIST  0x111c
#define REG_DWCEQOS_DMA_CH0_TXDESC_TAIL  0x1120
#define REG_DWCEQOS_DMA_CH0_RXDESC_TAIL  0x1128
#define REG_DWCEQOS_DMA_CH0_TXDESC_LEN   0x112c
#define REG_DWCEQOS_DMA_CH0_RXDESC_LEN   0x1130
#define REG_DWCEQOS_DMA_CH0_IE           0x1134
#define REG_DWCEQOS_DMA_CH0_CUR_TXDESC   0x1144
#define REG_DWCEQOS_DMA_CH0_CUR_RXDESC   0x114c
#define REG_DWCEQOS_DMA_CH0_CUR_TXBUF    0x1154
#define REG_DWCEQOS_DMA_CH0_CUR_RXBUG    0x115c
#define REG_DWCEQOS_DMA_CH0_STA          0x1160

#define DWCEQOS_DMA_MODE_TXPR            BIT(11)
#define DWCEQOS_DMA_MODE_DA              BIT(1)

#define DWCEQOS_DMA_SYSBUS_MODE_EN_LPI   BIT(31)
#define DWCEQOS_DMA_SYSBUS_MODE_FB       BIT(0)
#define DWCEQOS_DMA_SYSBUS_MODE_AAL      BIT(12)

#ifndef BITS_PER_LONG_LONG
#define BITS_PER_LONG_LONG 64
#endif

/*
 * Create a contiguous bitmask starting at bit position @l and ending at
 * position @h. For example
 * GENMASK_ULL(39, 21) gives us the 64bit vector 0x000000ffffe00000.
 */

#define GENMASK(h, l) \
	(((~0UL) << (l)) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

#define DWCEQOS_DMA_SYSBUS_MODE_RD_OSR_LIMIT(x) \
	(((x) << 16) & 0x000F0000)
#define DWCEQOS_DMA_SYSBUS_MODE_RD_OSR_LIMIT_DEFAULT    3
#define DWCEQOS_DMA_SYSBUS_MODE_RD_OSR_LIMIT_MASK       GENMASK(19, 16)

#define DWCEQOS_DMA_SYSBUS_MODE_WR_OSR_LIMIT(x) \
	(((x) << 24) & 0x0F000000)
#define DWCEQOS_DMA_SYSBUS_MODE_WR_OSR_LIMIT_DEFAULT    3
#define DWCEQOS_DMA_SYSBUS_MODE_WR_OSR_LIMIT_MASK       GENMASK(27, 24)

#define DWCEQOS_DMA_SYSBUS_MODE_BURST_MASK GENMASK(7, 1)
#define DWCEQOS_DMA_SYSBUS_MODE_BURST(x) \
	(((x) << 1) & DWCEQOS_DMA_SYSBUS_MODE_BURST_MASK)
#define DWCEQOS_DMA_SYSBUS_MODE_BURST_DEFAULT   GENMASK(3, 1)

#define DWCEQOS_DMA_CH_CTRL_PBLX8       BIT(16)
#define DWCEQOS_DMA_CH_CTRL_DSL(x)      ((x) << 18)

#define DWCEQOS_DMA_CH_CTRL_PBL(x)       ((x) << 16)
#define DWCEQOS_DMA_CH_CTRL_START         BIT(0)
#define DWCEQOS_DMA_CH_RX_CTRL_BUFSIZE(x)   ((x) << 1)
#define DWCEQOS_DMA_CH_TX_OSP            BIT(4)
#define DWCEQOS_DMA_CH_TX_TSE            BIT(12)

#define DWCEQOS_DMA_CH0_IE_NIE           BIT(15)
#define DWCEQOS_DMA_CH0_IE_AIE           BIT(14)
#define DWCEQOS_DMA_CH0_IE_RIE           BIT(6)
#define DWCEQOS_DMA_CH0_IE_TIE           BIT(0)
#define DWCEQOS_DMA_CH0_IE_FBEE          BIT(12)
#define DWCEQOS_DMA_CH0_IE_RBUE          BIT(7)

#define DWCEQOS_DMA_IS_DC0IS             BIT(0)
#define DWCEQOS_DMA_IS_MTLIS             BIT(16)
#define DWCEQOS_DMA_IS_MACIS             BIT(17)

#define DWCEQOS_DMA_CH0_IS_TI            BIT(0)
#define DWCEQOS_DMA_CH0_IS_RI            BIT(6)
#define DWCEQOS_DMA_CH0_IS_RBU           BIT(7)
#define DWCEQOS_DMA_CH0_IS_FBE           BIT(12)
#define DWCEQOS_DMA_CH0_IS_CDE           BIT(13)
#define DWCEQOS_DMA_CH0_IS_AIS           BIT(14)

#define DWCEQOS_DMA_CH0_IS_TEB           GENMASK(18, 16)
#define DWCEQOS_DMA_CH0_IS_TX_ERR_READ   BIT(16)
#define DWCEQOS_DMA_CH0_IS_TX_ERR_DESCR  BIT(17)

#define DWCEQOS_DMA_CH0_IS_REB           GENMASK(21, 19)
#define DWCEQOS_DMA_CH0_IS_RX_ERR_READ   BIT(19)
#define DWCEQOS_DMA_CH0_IS_RX_ERR_DESCR  BIT(20)

/* DMA descriptor bits for RX normal descriptor (read format) */
#define DWCEQOS_DMA_RDES3_OWN     BIT(31)
#define DWCEQOS_DMA_RDES3_INTE    BIT(30)
#define DWCEQOS_DMA_RDES3_BUF2V   BIT(25)
#define DWCEQOS_DMA_RDES3_BUF1V   BIT(24)

/* DMA descriptor bits for RX normal descriptor (write back format) */
#define DWCEQOS_DMA_RDES1_IPCE    BIT(7)
#define DWCEQOS_DMA_RDES3_ES      BIT(15)
#define DWCEQOS_DMA_RDES3_E_JT    BIT(14)
#define DWCEQOS_DMA_RDES3_PL(x)   ((x) & 0x7fff)
#define DWCEQOS_DMA_RDES1_PT      0x00000007
#define DWCEQOS_DMA_RDES1_PT_UDP  BIT(0)
#define DWCEQOS_DMA_RDES1_PT_TCP  BIT(1)
#define DWCEQOS_DMA_RDES1_PT_ICMP 0x00000003

/* DMA descriptor bits for TX normal descriptor (read format) */
#define DWCEQOS_DMA_TDES2_IOC     BIT(31)
#define DWCEQOS_DMA_TDES3_OWN     BIT(31)
#define DWCEQOS_DMA_TDES3_CTXT    BIT(30)
#define DWCEQOS_DMA_TDES3_FD      BIT(29)
#define DWCEQOS_DMA_TDES3_LD      BIT(28)
#define DWCEQOS_DMA_TDES3_CIPH    BIT(16)
#define DWCEQOS_DMA_TDES3_CIPP    BIT(17)
#define DWCEQOS_DMA_TDES3_CA      0x00030000
#define DWCEQOS_DMA_TDES3_TSE     BIT(18)
#define DWCEQOS_DMA_DES3_THL(x)   ((x) << 19)
#define DWCEQOS_DMA_DES2_B2L(x)   ((x) << 16)

#define DWCEQOS_DMA_TDES3_TCMSSV    BIT(26)

/* DMA channel states */
#define DMA_TX_CH_STOPPED   0
#define DMA_TX_CH_SUSPENDED 6

#define DMA_GET_TX_STATE_CH0(status0) ((status0 & 0xF000) >> 12)

/* MTL */
#define REG_DWCEQOS_MTL_OPER             0x0c00
#define REG_DWCEQOS_MTL_DEBUG_ST         0x0c0c
#define REG_DWCEQOS_MTL_TXQ0_DEBUG_ST    0x0d08
#define REG_DWCEQOS_MTL_RXQ0_DEBUG_ST    0x0d38

#define REG_DWCEQOS_MTL_IS               0x0c20
#define REG_DWCEQOS_MTL_TXQ0_OPER        0x0d00
#define REG_DWCEQOS_MTL_RXQ0_OPER        0x0d30
#define REG_DWCEQOS_MTL_RXQ0_MIS_CNT     0x0d34
#define REG_DWCEQOS_MTL_RXQ0_CTRL         0x0d3c

#define REG_DWCEQOS_MTL_Q0_ISCTRL         0x0d2c

#define DWCEQOS_MTL_SCHALG_STRICT        0x00000060

#define DWCEQOS_MTL_TXQ_TXQEN            BIT(3)
#define DWCEQOS_MTL_TXQ_TSF              BIT(1)
#define DWCEQOS_MTL_TXQ_FTQ              BIT(0)
#define DWCEQOS_MTL_TXQ_TTC512           0x00000070

#define DWCEQOS_MTL_TXQ_SIZE(x)          ((((x) - 256) & 0xff00) << 8)

#define DWCEQOS_MTL_RXQ_SIZE(x)          ((((x) - 256) & 0xff00) << 12)
#define DWCEQOS_MTL_RXQ_EHFC             BIT(7)
#define DWCEQOS_MTL_RXQ_DIS_TCP_EF       BIT(6)
#define DWCEQOS_MTL_RXQ_FEP              BIT(4)
#define DWCEQOS_MTL_RXQ_FUP              BIT(3)
#define DWCEQOS_MTL_RXQ_RSF              BIT(5)
#define DWCEQOS_MTL_RXQ_RTC32            BIT(0)

/* MAC */
#define REG_DWCEQOS_MAC_CFG              0x0000
#define REG_DWCEQOS_MAC_EXT_CFG          0x0004
#define REG_DWCEQOS_MAC_PKT_FILT         0x0008
#define REG_DWCEQOS_MAC_WD_TO            0x000c
#define REG_DWCEQOS_HASTABLE_LO          0x0010
#define REG_DWCEQOS_HASTABLE_HI          0x0014
#define REG_DWCEQOS_MAC_IS               0x00b0
#define REG_DWCEQOS_MAC_IE               0x00b4
#define REG_DWCEQOS_MAC_STAT             0x00b8
#define REG_DWCEQOS_MAC_MDIO_ADDR        0x0200
#define REG_DWCEQOS_MAC_MDIO_DATA        0x0204
#define REG_DWCEQOS_MAC_MAC_ADDR0_HI     0x0300
#define REG_DWCEQOS_MAC_MAC_ADDR0_LO     0x0304
#define REG_DWCEQOS_MAC_RXQ0_CTRL0       0x00a0
#define REG_DWCEQOS_MAC_HW_VERSION       0x0110
#define REG_DWCEQOS_MAC_HW_FEATURE0      0x011c
#define REG_DWCEQOS_MAC_HW_FEATURE1      0x0120
#define REG_DWCEQOS_MAC_HW_FEATURE2      0x0124
#define REG_DWCEQOS_MAC_HASHTABLE_LO     0x0010
#define REG_DWCEQOS_MAC_HASHTABLE_HI     0x0014
#define REG_DWCEQOS_MAC_LPI_CTRL_STATUS  0x00d0
#define REG_DWCEQOS_MAC_LPI_TIMERS_CTRL  0x00d4
#define REG_DWCEQOS_MAC_LPI_ENTRY_TIMER  0x00d8
#define REG_DWCEQOS_MAC_1US_TIC_COUNTER  0x00dc
#define REG_DWCEQOS_MAC_RX_FLOW_CTRL     0x0090
#define REG_DWCEQOS_MAC_Q0_TX_FLOW	 0x0070

#define DWCEQOS_MAC_CFG_ACS              BIT(20)
#define DWCEQOS_MAC_CFG_JD               BIT(17)
#define DWCEQOS_MAC_CFG_JE               BIT(16)
#define DWCEQOS_MAC_CFG_PS               BIT(15)
#define DWCEQOS_MAC_CFG_FES              BIT(14)
#define DWCEQOS_MAC_CFG_DM               BIT(13)
#define DWCEQOS_MAC_CFG_LPM              BIT(12)
#define DWCEQOS_MAC_CFG_DO               BIT(10)
#define DWCEQOS_MAC_CFG_TE               BIT(1)
#define DWCEQOS_MAC_CFG_IPC              BIT(27)
#define DWCEQOS_MAC_CFG_RE               BIT(0)

#define DWCEQOS_ADDR_HIGH(reg)           (0x00000300 + (reg * 8))
#define DWCEQOS_ADDR_LOW(reg)            (0x00000304 + (reg * 8))

#define DWCEQOS_MAC_IS_LPI_INT           BIT(5)
#define DWCEQOS_MAC_IS_MMC_INT           BIT(8)

#define DWCEQOS_MAC_RXQ_EN               BIT(1)
#define DWCEQOS_MAC_MAC_ADDR_HI_EN       BIT(31)
#define DWCEQOS_MAC_PKT_FILT_RA          BIT(31)
#define DWCEQOS_MAC_PKT_FILT_HPF         BIT(10)
#define DWCEQOS_MAC_PKT_FILT_SAF         BIT(9)
#define DWCEQOS_MAC_PKT_FILT_SAIF        BIT(8)
#define DWCEQOS_MAC_PKT_FILT_DBF         BIT(5)
#define DWCEQOS_MAC_PKT_FILT_PM          BIT(4)
#define DWCEQOS_MAC_PKT_FILT_DAIF        BIT(3)
#define DWCEQOS_MAC_PKT_FILT_HMC         BIT(2)
#define DWCEQOS_MAC_PKT_FILT_HUC         BIT(1)
#define DWCEQOS_MAC_PKT_FILT_PR          BIT(0)

#define DWCEQOS_MAC_MDIO_ADDR_CR(x)      (((x & 15)) << 8)
#define DWCEQOS_MAC_MDIO_ADDR_CR_20      2
#define DWCEQOS_MAC_MDIO_ADDR_CR_35      3
#define DWCEQOS_MAC_MDIO_ADDR_CR_60      0
#define DWCEQOS_MAC_MDIO_ADDR_CR_100     1
#define DWCEQOS_MAC_MDIO_ADDR_CR_150     4
#define DWCEQOS_MAC_MDIO_ADDR_CR_250     5
#define DWCEQOS_MAC_MDIO_ADDR_GOC_READ   0x0000000c
#define DWCEQOS_MAC_MDIO_ADDR_GOC_WRITE  BIT(2)
#define DWCEQOS_MAC_MDIO_ADDR_GB         BIT(0)

#define DWCEQOS_MAC_LPI_CTRL_STATUS_TLPIEN  BIT(0)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_TLPIEX  BIT(1)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_RLPIEN  BIT(2)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_RLPIEX  BIT(3)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_TLPIST  BIT(8)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_RLPIST  BIT(9)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_LPIEN   BIT(16)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_PLS     BIT(17)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_PLSEN   BIT(18)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_LIPTXA  BIT(19)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_LPITE   BIT(20)
#define DWCEQOS_MAC_LPI_CTRL_STATUS_LPITCSE BIT(21)

#define DWCEQOS_MAC_1US_TIC_COUNTER_VAL(x)  ((x) & GENMASK(11, 0))

#define DWCEQOS_LPI_CTRL_ENABLE_EEE      (DWCEQOS_MAC_LPI_CTRL_STATUS_LPITE | \
					  DWCEQOS_MAC_LPI_CTRL_STATUS_LIPTXA | \
					  DWCEQOS_MAC_LPI_CTRL_STATUS_LPIEN)

#define DWCEQOS_MAC_RX_FLOW_CTRL_RFE BIT(0)

#define DWCEQOS_MAC_Q0_TX_FLOW_TFE   BIT(1)
#define DWCEQOS_MAC_Q0_TX_FLOW_PT(time)	((time) << 16)
#define DWCEQOS_MAC_Q0_TX_FLOW_PLT_4_SLOTS (0 << 4)

/* Features */
#define DWCEQOS_MAC_HW_FEATURE0_RXCOESEL BIT(16)
#define DWCEQOS_MAC_HW_FEATURE0_TXCOESEL BIT(14)
#define DWCEQOS_MAC_HW_FEATURE0_HDSEL    BIT(2)
#define DWCEQOS_MAC_HW_FEATURE0_EEESEL   BIT(13)
#define DWCEQOS_MAC_HW_FEATURE0_GMIISEL  BIT(1)
#define DWCEQOS_MAC_HW_FEATURE0_MIISEL   BIT(0)

#define DWCEQOS_MAC_HW_FEATURE1_TSOEN    BIT(18)
#define DWCEQOS_MAC_HW_FEATURE1_TXFIFOSIZE(x) ((128 << ((x) & 0x7c0)) >> 6)
#define DWCEQOS_MAC_HW_FEATURE1_RXFIFOSIZE(x)  (128 << ((x) & 0x1f))

#define DWCEQOS_MAX_PERFECT_ADDRESSES(feature1) \
	(1 + (((feature1) & 0x1fc0000) >> 18))

#define DWCEQOS_MDIO_PHYADDR(x)     (((x) & 0x1f) << 21)
#define DWCEQOS_MDIO_PHYREG(x)      (((x) & 0x1f) << 16)

#define DWCEQOS_DMA_MODE_SWR            BIT(0)

#define DWCEQOS_DWCEQOS_RX_BUF_SIZE 2048

/* Mac Management Counters */
#define REG_DWCEQOS_MMC_CTRL             0x0700
#define REG_DWCEQOS_MMC_RXIRQ            0x0704
#define REG_DWCEQOS_MMC_TXIRQ            0x0708
#define REG_DWCEQOS_MMC_RXIRQMASK        0x070c
#define REG_DWCEQOS_MMC_TXIRQMASK        0x0710

#define DWCEQOS_MMC_CTRL_CNTRST          BIT(0)
#define DWCEQOS_MMC_CTRL_RSTONRD         BIT(2)

#define DWC_MMC_TXLPITRANSCNTR           0x07F0
#define DWC_MMC_TXLPIUSCNTR              0x07EC
#define DWC_MMC_TXOVERSIZE_G             0x0778
#define DWC_MMC_TXVLANPACKETS_G          0x0774
#define DWC_MMC_TXPAUSEPACKETS           0x0770
#define DWC_MMC_TXEXCESSDEF              0x076C
#define DWC_MMC_TXPACKETCOUNT_G          0x0768
#define DWC_MMC_TXOCTETCOUNT_G           0x0764
#define DWC_MMC_TXCARRIERERROR           0x0760
#define DWC_MMC_TXEXCESSCOL              0x075C
#define DWC_MMC_TXLATECOL                0x0758
#define DWC_MMC_TXDEFERRED               0x0754
#define DWC_MMC_TXMULTICOL_G             0x0750
#define DWC_MMC_TXSINGLECOL_G            0x074C
#define DWC_MMC_TXUNDERFLOWERROR         0x0748
#define DWC_MMC_TXBROADCASTPACKETS_GB    0x0744
#define DWC_MMC_TXMULTICASTPACKETS_GB    0x0740
#define DWC_MMC_TXUNICASTPACKETS_GB      0x073C
#define DWC_MMC_TX1024TOMAXOCTETS_GB     0x0738
#define DWC_MMC_TX512TO1023OCTETS_GB     0x0734
#define DWC_MMC_TX256TO511OCTETS_GB      0x0730
#define DWC_MMC_TX128TO255OCTETS_GB      0x072C
#define DWC_MMC_TX65TO127OCTETS_GB       0x0728
#define DWC_MMC_TX64OCTETS_GB            0x0724
#define DWC_MMC_TXMULTICASTPACKETS_G     0x0720
#define DWC_MMC_TXBROADCASTPACKETS_G     0x071C
#define DWC_MMC_TXPACKETCOUNT_GB         0x0718
#define DWC_MMC_TXOCTETCOUNT_GB          0x0714

#define DWC_MMC_RXLPITRANSCNTR           0x07F8
#define DWC_MMC_RXLPIUSCNTR              0x07F4
#define DWC_MMC_RXCTRLPACKETS_G          0x07E4
#define DWC_MMC_RXRCVERROR               0x07E0
#define DWC_MMC_RXWATCHDOG               0x07DC
#define DWC_MMC_RXVLANPACKETS_GB         0x07D8
#define DWC_MMC_RXFIFOOVERFLOW           0x07D4
#define DWC_MMC_RXPAUSEPACKETS           0x07D0
#define DWC_MMC_RXOUTOFRANGETYPE         0x07CC
#define DWC_MMC_RXLENGTHERROR            0x07C8
#define DWC_MMC_RXUNICASTPACKETS_G       0x07C4
#define DWC_MMC_RX1024TOMAXOCTETS_GB     0x07C0
#define DWC_MMC_RX512TO1023OCTETS_GB     0x07BC
#define DWC_MMC_RX256TO511OCTETS_GB      0x07B8
#define DWC_MMC_RX128TO255OCTETS_GB      0x07B4
#define DWC_MMC_RX65TO127OCTETS_GB       0x07B0
#define DWC_MMC_RX64OCTETS_GB            0x07AC
#define DWC_MMC_RXOVERSIZE_G             0x07A8
#define DWC_MMC_RXUNDERSIZE_G            0x07A4
#define DWC_MMC_RXJABBERERROR            0x07A0
#define DWC_MMC_RXRUNTERROR              0x079C
#define DWC_MMC_RXALIGNMENTERROR         0x0798
#define DWC_MMC_RXCRCERROR               0x0794
#define DWC_MMC_RXMULTICASTPACKETS_G     0x0790
#define DWC_MMC_RXBROADCASTPACKETS_G     0x078C
#define DWC_MMC_RXOCTETCOUNT_G           0x0788
#define DWC_MMC_RXOCTETCOUNT_GB          0x0784
#define DWC_MMC_RXPACKETCOUNT_GB         0x0780

/* uncomment it to get more debug info */
//#define EMAC_DEBUG 1
#define VCS_TEST 1
/* MTL Queue Quantum Weight */
#define MTL_TXQ_WEIGHT_BASE_ADDR	0x00000d18
#define MTL_TXQ_WEIGHT_BASE_OFFSET	0x40
#define MTL_TXQX_WEIGHT_BASE_ADDR(x)	(MTL_TXQ_WEIGHT_BASE_ADDR + \
					((x) * MTL_TXQ_WEIGHT_BASE_OFFSET))
#define MTL_TXQ_WEIGHT_ISCQW_MASK	GENMASK(20, 0)
/*  MTL registers */
#define MTL_OPERATION_MODE		0x00000c00
#define MTL_FRPE			BIT(15)
#define MTL_OPERATION_SCHALG_MASK	GENMASK(6, 5)
#define MTL_OPERATION_SCHALG_WRR	(0x0 << 5)
#define MTL_OPERATION_SCHALG_WFQ	(0x1 << 5)
#define MTL_OPERATION_SCHALG_DWRR	(0x2 << 5)
#define MTL_OPERATION_SCHALG_SP		(0x3 << 5)
#define MTL_OPERATION_RAA		BIT(2)
#define MTL_OPERATION_RAA_SP		(0x0 << 2)
#define MTL_OPERATION_RAA_WSP		(0x1 << 2)

/* MTL algorithms identifiers */
#define MTL_TX_ALGORITHM_WRR	0x0
#define MTL_TX_ALGORITHM_WFQ	0x1
#define MTL_TX_ALGORITHM_DWRR	0x2
#define MTL_TX_ALGORITHM_SP	0x3
#define MTL_RX_ALGORITHM_SP	0x4
#define MTL_RX_ALGORITHM_WSP	0x5

/* RX/TX Queue Mode */
#define MTL_QUEUE_AVB		0x1
#define MTL_QUEUE_DCB_GENERIC		0x0

#define MTL_RXQ_DMA_MAP0		0x00000c30 /* queue 0 to 3 */
#define MTL_RXQ_DMA_MAP1		0x00000c34 /* queue 4 to 7 */
#define MTL_RXQ_DMA_Q04MDMACH_MASK	GENMASK(3, 0)
#define MTL_RXQ_DMA_Q04MDMACH(x)	((x) << 0)
#define MTL_RXQ_DMA_QXMDMACH_MASK(x)	GENMASK(11 + (8 * ((x) - 1)), 8 * (x))
#define MTL_RXQ_DMA_QXMDMACH(chan, q)	((chan) << (8 * (q)))

#define GMAC_RXQ_CTRL0			0x000000a0
#define GMAC_RXQ_CTRL1			0x000000a4
#define GMAC_RXQ_CTRL2			0x000000a8
#define GMAC_RXQ_CTRL3			0x000000ac

/* MAC RX Queue Enable */
#define GMAC_RX_QUEUE_CLEAR(queue)	~(GENMASK(1, 0) << ((queue) * 2))
#define GMAC_RX_AV_QUEUE_ENABLE(queue)	BIT((queue) * 2)
#define GMAC_RX_DCB_QUEUE_ENABLE(queue)	BIT(((queue) * 2) + 1)

#define GMAC_TXQ_PRTY_MAP0		0x98
#define GMAC_TXQ_PRTY_MAP1		0x9C
/* RX Queues Priorities */
#define GMAC_RXQCTRL_PSRQX_MASK(x)	GENMASK(7 + ((x) * 8), 0 + ((x) * 8))
#define GMAC_RXQCTRL_PSRQX_SHIFT(x)	((x) * 8)

/* TX Queues Priorities */
#define GMAC_TXQCTRL_PSTQX_MASK(x)	GENMASK(7 + ((x) * 8), 0 + ((x) * 8))
#define GMAC_TXQCTRL_PSTQX_SHIFT(x)	((x) * 8)

/* RX Queues Routing */
#define GMAC_RXQCTRL_AVCPQ_MASK		GENMASK(2, 0)
#define GMAC_RXQCTRL_AVCPQ_SHIFT	0
#define GMAC_RXQCTRL_PTPQ_MASK		GENMASK(6, 4)
#define GMAC_RXQCTRL_PTPQ_SHIFT		4
#define GMAC_RXQCTRL_DCBCPQ_MASK	GENMASK(10, 8)
#define GMAC_RXQCTRL_DCBCPQ_SHIFT	8
#define GMAC_RXQCTRL_UPQ_MASK		GENMASK(14, 12)
#define GMAC_RXQCTRL_UPQ_SHIFT		12
#define GMAC_RXQCTRL_MCBCQ_MASK		GENMASK(18, 16)
#define GMAC_RXQCTRL_MCBCQ_SHIFT	16
#define GMAC_RXQCTRL_MCBCQEN		BIT(20)
#define GMAC_RXQCTRL_MCBCQEN_SHIFT	20
#define GMAC_RXQCTRL_TACPQE		BIT(21)
#define GMAC_RXQCTRL_TACPQE_SHIFT	21

/* Following DMA defines are chanels oriented */
#define DMA_CHAN_BASE_ADDR		0x00001100
#define DMA_CHAN_BASE_OFFSET		0x80
#define DMA_CHANX_BASE_ADDR(x)		(DMA_CHAN_BASE_ADDR + \
					(x * DMA_CHAN_BASE_OFFSET))
#define DMA_CHAN_REG_NUMBER		17

#define DMA_CHAN_CONTROL(x)		DMA_CHANX_BASE_ADDR(x)
#define DMA_CHAN_TX_CONTROL(x)		(DMA_CHANX_BASE_ADDR(x) + 0x4)
#define DMA_CHAN_RX_CONTROL(x)		(DMA_CHANX_BASE_ADDR(x) + 0x8)
#define DMA_CHAN_TX_BASE_ADDR(x)	(DMA_CHANX_BASE_ADDR(x) + 0x14)
#define DMA_CHAN_RX_BASE_ADDR(x)	(DMA_CHANX_BASE_ADDR(x) + 0x1c)
#define DMA_CHAN_TX_END_ADDR(x)		(DMA_CHANX_BASE_ADDR(x) + 0x20)
#define DMA_CHAN_RX_END_ADDR(x)		(DMA_CHANX_BASE_ADDR(x) + 0x28)
#define DMA_CHAN_TX_RING_LEN(x)		(DMA_CHANX_BASE_ADDR(x) + 0x2c)
#define DMA_CHAN_RX_RING_LEN(x)		(DMA_CHANX_BASE_ADDR(x) + 0x30)
#define DMA_CHAN_INTR_ENA(x)		(DMA_CHANX_BASE_ADDR(x) + 0x34)
#define DMA_CHAN_RX_WATCHDOG(x)		(DMA_CHANX_BASE_ADDR(x) + 0x38)
#define DMA_CHAN_SLOT_CTRL_STATUS(x)	(DMA_CHANX_BASE_ADDR(x) + 0x3c)
#define DMA_CHAN_CUR_TX_DESC(x)		(DMA_CHANX_BASE_ADDR(x) + 0x44)
#define DMA_CHAN_CUR_RX_DESC(x)		(DMA_CHANX_BASE_ADDR(x) + 0x4c)
#define DMA_CHAN_CUR_TX_BUF_ADDR(x)	(DMA_CHANX_BASE_ADDR(x) + 0x54)
#define DMA_CHAN_CUR_RX_BUF_ADDR(x)	(DMA_CHANX_BASE_ADDR(x) + 0x5c)
#define DMA_CHAN_STATUS(x)		(DMA_CHANX_BASE_ADDR(x) + 0x60)

#define MTL_CHAN_BASE_ADDR		0x00000d00
#define MTL_CHAN_BASE_OFFSET		0x40
#define MTL_CHANX_BASE_ADDR(x)		(MTL_CHAN_BASE_ADDR + \
					(x * MTL_CHAN_BASE_OFFSET))

#define MTL_CHAN_TX_OP_MODE(x)		MTL_CHANX_BASE_ADDR(x)
#define MTL_CHAN_TX_DEBUG(x)		(MTL_CHANX_BASE_ADDR(x) + 0x8)
#define MTL_CHAN_INT_CTRL(x)		(MTL_CHANX_BASE_ADDR(x) + 0x2c)
#define MTL_CHAN_RX_OP_MODE(x)		(MTL_CHANX_BASE_ADDR(x) + 0x30)
#define MTL_CHAN_RX_DEBUG(x)		(MTL_CHANX_BASE_ADDR(x) + 0x38)
#define MTL_OP_MODE_TXQEN_AV		BIT(2)
#define MTL_OP_MODE_TXQEN		BIT(3)
/* MTL ETS Control register */
#define MTL_ETS_CTRL_BASE_ADDR		0x00000d10
#define MTL_ETS_CTRL_BASE_OFFSET	0x40
#define MTL_ETSX_CTRL_BASE_ADDR(x)	(MTL_ETS_CTRL_BASE_ADDR + \
					((x) * MTL_ETS_CTRL_BASE_OFFSET))

#define MTL_ETS_STATUS_BASE_ADDR		0x00000d14
#define MTL_ETSX_STATUS_BASE_ADDR(x)	(MTL_ETS_STATUS_BASE_ADDR + \
					((x) * MTL_ETS_CTRL_BASE_OFFSET))

#define MTL_ETS_CTRL_CC			BIT(3)
#define MTL_ETS_CTRL_AVALG		BIT(2)
#define MTL_OP_MODE_TXQEN_MASK		GENMASK(3, 2)

/* MTL Queue Quantum Weight */
#define MTL_TXQ_WEIGHT_BASE_ADDR	0x00000d18
#define MTL_TXQ_WEIGHT_BASE_OFFSET	0x40
#define MTL_TXQX_WEIGHT_BASE_ADDR(x)	(MTL_TXQ_WEIGHT_BASE_ADDR + \
					((x) * MTL_TXQ_WEIGHT_BASE_OFFSET))
#define MTL_TXQ_WEIGHT_ISCQW_MASK	GENMASK(20, 0)

/* MTL sendSlopeCredit register */
#define MTL_SEND_SLP_CRED_BASE_ADDR	0x00000d1c
#define MTL_SEND_SLP_CRED_OFFSET	0x40
#define MTL_SEND_SLP_CREDX_BASE_ADDR(x)	(MTL_SEND_SLP_CRED_BASE_ADDR + \
					((x) * MTL_SEND_SLP_CRED_OFFSET))

#define MTL_SEND_SLP_CRED_SSC_MASK	GENMASK(13, 0)

/* MTL hiCredit register */
#define MTL_HIGH_CRED_BASE_ADDR		0x00000d20
#define MTL_HIGH_CRED_OFFSET		0x40
#define MTL_HIGH_CREDX_BASE_ADDR(x)	(MTL_HIGH_CRED_BASE_ADDR + \
					((x) * MTL_HIGH_CRED_OFFSET))

#define MTL_HIGH_CRED_HC_MASK		GENMASK(28, 0)

/* MTL loCredit register */
#define MTL_LOW_CRED_BASE_ADDR		0x00000d24
#define MTL_LOW_CRED_OFFSET		0x40
#define MTL_LOW_CREDX_BASE_ADDR(x)	(MTL_LOW_CRED_BASE_ADDR + \
					((x) * MTL_LOW_CRED_OFFSET))

#define MTL_HIGH_CRED_LC_MASK		GENMASK(28, 0)


struct net_local* emac_init(u64 base_addr);
void emac_test_mode(struct net_local* lp,
					struct dwceqos_MTL_cfg* emac_MTL_cfg);
int dwceqos_rx(struct net_local *lp, int budget, u32 rx_q,
				char** recv, u32 *length);
int dwceqos_xmit(struct net_local *lp, u32 tx_q,
				char *buf, size_t len, bool ptp);
void emac_lpmode_config(struct net_local *lp);
void dwceqos_tx_reclaim(struct net_local *lp, u32 tx_q);
void dwceqos_get_stats64(struct net_local *lp, int mode);
void dwceqos_show_status(struct net_local *lp, u32 tx_q, u32 rx_q);
void emac_get_feature(u64 base_addr);
void emac_get_tx_ts(struct net_local *lp, u32 tx_q, u64 *ts);
void emac_get_rx_ts(struct net_local *lp, u32 rx_q, u64 *ts);
void emac_show_CBS_info(struct net_local* lp, u32 queue);

/* heap buffer realted */
void emac_init_memory(uintptr_t addr, size_t size);
void *emac_heap_aligned_alloc(size_t align, size_t size);
void *emac_heap_alloc(size_t size);
void emac_heap_free(void *p);
#endif