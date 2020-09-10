/*  Synopsys DWC Ethernet Quality-of-Service v4.10a linux driver
 *
 *  This driver is derived from kernel V4.4 QoS IP version 4.10a (GMAC).
 *  Currently the following basic features are supported:
 *  - Basic Mac, Queue, DMA configuration, Tx/Rx Desc configuration
 *  - Mac Loopback
 *  - Single RX and TX queue.
 *
 *  Copyright (C) 2020, Siengine
 */
#include <string.h>
#include <stdlib.h>
#include <asm/io.h>
#include <stdbool.h>
#include <target/console.h>
#include <target/bitops.h>
#include <target/cmdline.h>
#include <errno.h>
#include <target/spinlock.h>
#include <target/delay.h>
#include <target/heap.h>
#include <target/utils.h>
#include <target/list.h>

#include "emac_drv.h"
#include "emac_ptp.h"


void emac_init_hw_mtl(struct net_local* emac_dev,
					struct dwceqos_MTL_cfg* emac_MTL_cfg);

static uintptr_t emac_dma_buf;
static uintptr_t emac_dma_buf_end;

void emac_init_memory(uintptr_t addr, size_t size)
{
	emac_dma_buf = addr;
	emac_dma_buf_end = emac_dma_buf + size;
}

void *emac_heap_aligned_alloc(size_t align, size_t size)
{
	uintptr_t cur;

	if (align & (align - 1)) {
		printf("EMAC heap_alloc wrong align!\n");
		return NULL;
	}

	cur = ALIGN_UP(emac_dma_buf, (uintptr_t)align);

	if ((cur + size) > emac_dma_buf_end) {
		printf("EMAC heap_alloc out of memory!\n");
		return NULL;
	} else {
		emac_dma_buf = cur + size;
		return (void *)cur;
	}
}

void *emac_heap_alloc(size_t size)
{
	return emac_heap_aligned_alloc(16, size);
}


void emac_heap_free(void *p)
{
	(void) p;
}
/* should be coherent memory alloc, no cache*/
void *emac_alloc_coherent(int size, emac_dma_addr_t *phys)
{
	/* coherent memory is not ready, need to work on it future
	 * this func will not work properly. If it works, just luck
	 */
	void* local;
	local = emac_heap_alloc(size);
	/* suppose virt = phys*/
	*phys = (emac_dma_addr_t)local;
	return local;
}

void emac_free_coherent(int size, void* addr, emac_dma_addr_t* phys)
{
	/*
	* coherent memory is not ready, need to unmap this buffer
	* cowork with above alloc coherent API
	*/
	emac_heap_free(addr);
	*phys = 0;
}

static void print_descriptor_rx(struct emac_rx_queue* rxq,
								int index)
{
	struct dwceqos_dma_desc *dd;

	dd = (struct dwceqos_dma_desc *)&rxq->rx_descs[index];

	inval_dcache_area(dd, sizeof(struct dwceqos_dma_desc));
	printf("Rx DMA Descriptor #%d@%p Contents:\n", index, dd);
	printf("	0x%08x 0x%08x 0x%08x 0x%08x\n", dd->des0, dd->des1, dd->des2,
		dd->des3);
}

static void print_descriptor_tx(struct emac_tx_queue* txq, int index)
{
	struct dwceqos_dma_desc *dd;

	dd = (struct dwceqos_dma_desc *)&txq->tx_descs[index];

	inval_dcache_area(dd, sizeof(struct dwceqos_dma_desc));
	printf("tx DMA Descriptor #%d@%p Contents:\n", index, dd);
	printf("	0x%08x 0x%08x 0x%08x 0x%08x\n", dd->des0, dd->des1, dd->des2,
		dd->des3);
}

static void print_status(struct net_local *lp,
		struct emac_tx_queue* txq, struct emac_rx_queue* rxq)
{
	size_t desci, i;
	u32 reg;
	struct dwceqos_dma_desc* tx_des;

#ifdef VCS_TEST
	printf("s1:0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_DMA_DEBUG_ST0));
	printf("s2:0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_STA));
	printf("IS:0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_DMA_IS));
#else
	printf("tx_free %d, tx_cur %d, tx_next %d\n\n", (int)txq->tx_free,
		(int)txq->tx_cur, (int)txq->tx_next);

	printf("rx current descriptor:\n");
	print_descriptor_rx(rxq, rxq->rx_cur);

	printf("\nTx descriptor\n");
	for (desci = (txq->tx_cur) % DWCEQOS_TX_DCNT, i = 0;
		i < 1; ++i) {
		print_descriptor_tx(txq, desci);
		desci = (desci + 1) % DWCEQOS_TX_DCNT;
	}

	printf("\nStatus info\n");
	printf("DMA_Debug_Status0:          0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_DMA_DEBUG_ST0));
	printf("DMA_CH0_Status:             0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_STA));
	printf("DMA_CH_interrupt_Status:    0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_DMA_IS));
	printf("DMA_CH0_Current_App_TxDesc: 0x%08x\n",
			dwceqos_read(lp, 0x1144));
	printf("DMA_CH0_Current_App_TxBuff: 0x%08x\n",
			dwceqos_read(lp, 0x1154));
	printf("MTL_Debug_Status:      0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_MTL_DEBUG_ST));
	printf("MTL_TXQ0_Debug_Status: 0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_MTL_TXQ0_DEBUG_ST));
	printf("MTL_RXQ0_Debug_Status: 0x%08x\n",
			dwceqos_read(lp, REG_DWCEQOS_MTL_RXQ0_DEBUG_ST));
	printf("Current TX DMA: 0x%08x, RX DMA: 0x%08x\n",
			reg = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_CUR_TXDESC),
			dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_CUR_RXDESC));
	/* 32bits to 64bits directly, dangerous */
	if (reg) {
		tx_des = (struct dwceqos_dma_desc*)((u64)reg);
		printf("Current TX buf: 0x%08x\n",tx_des->des0);
	} else {
		printf("error, Tx DMA is in wrong status\n");
	}
#endif
}

/* MMC counter */
static void dwceqos_read_mmc_counters(struct net_local *lp, u32 rx_mask,
				      u32 tx_mask)
{
	if (tx_mask & BIT(27))
		lp->mmc_counters.txlpitranscntr +=
			dwceqos_read(lp, DWC_MMC_TXLPITRANSCNTR);
	if (tx_mask & BIT(26))
		lp->mmc_counters.txpiuscntr +=
			dwceqos_read(lp, DWC_MMC_TXLPIUSCNTR);
	if (tx_mask & BIT(25))
		lp->mmc_counters.txoversize_g +=
			dwceqos_read(lp, DWC_MMC_TXOVERSIZE_G);
	if (tx_mask & BIT(24))
		lp->mmc_counters.txvlanpackets_g +=
			dwceqos_read(lp, DWC_MMC_TXVLANPACKETS_G);
	if (tx_mask & BIT(23))
		lp->mmc_counters.txpausepackets +=
			dwceqos_read(lp, DWC_MMC_TXPAUSEPACKETS);
	if (tx_mask & BIT(22))
		lp->mmc_counters.txexcessdef +=
			dwceqos_read(lp, DWC_MMC_TXEXCESSDEF);
	if (tx_mask & BIT(21))
		lp->mmc_counters.txpacketcount_g +=
			dwceqos_read(lp, DWC_MMC_TXPACKETCOUNT_G);
	if (tx_mask & BIT(20))
		lp->mmc_counters.txoctetcount_g +=
			dwceqos_read(lp, DWC_MMC_TXOCTETCOUNT_G);
	if (tx_mask & BIT(19))
		lp->mmc_counters.txcarriererror +=
			dwceqos_read(lp, DWC_MMC_TXCARRIERERROR);
	if (tx_mask & BIT(18))
		lp->mmc_counters.txexcesscol +=
			dwceqos_read(lp, DWC_MMC_TXEXCESSCOL);
	if (tx_mask & BIT(17))
		lp->mmc_counters.txlatecol +=
			dwceqos_read(lp, DWC_MMC_TXLATECOL);
	if (tx_mask & BIT(16))
		lp->mmc_counters.txdeferred +=
			dwceqos_read(lp, DWC_MMC_TXDEFERRED);
	if (tx_mask & BIT(15))
		lp->mmc_counters.txmulticol_g +=
			dwceqos_read(lp, DWC_MMC_TXMULTICOL_G);
	if (tx_mask & BIT(14))
		lp->mmc_counters.txsinglecol_g +=
			dwceqos_read(lp, DWC_MMC_TXSINGLECOL_G);
	if (tx_mask & BIT(13))
		lp->mmc_counters.txunderflowerror +=
			dwceqos_read(lp, DWC_MMC_TXUNDERFLOWERROR);
	if (tx_mask & BIT(12))
		lp->mmc_counters.txbroadcastpackets_gb +=
			dwceqos_read(lp, DWC_MMC_TXBROADCASTPACKETS_GB);
	if (tx_mask & BIT(11))
		lp->mmc_counters.txmulticastpackets_gb +=
			dwceqos_read(lp, DWC_MMC_TXMULTICASTPACKETS_GB);
	if (tx_mask & BIT(10))
		lp->mmc_counters.txunicastpackets_gb +=
			dwceqos_read(lp, DWC_MMC_TXUNICASTPACKETS_GB);
	if (tx_mask & BIT(9))
		lp->mmc_counters.tx1024tomaxoctets_gb +=
			dwceqos_read(lp, DWC_MMC_TX1024TOMAXOCTETS_GB);
	if (tx_mask & BIT(8))
		lp->mmc_counters.tx512to1023octets_gb +=
			dwceqos_read(lp, DWC_MMC_TX512TO1023OCTETS_GB);
	if (tx_mask & BIT(7))
		lp->mmc_counters.tx256to511octets_gb +=
			dwceqos_read(lp, DWC_MMC_TX256TO511OCTETS_GB);
	if (tx_mask & BIT(6))
		lp->mmc_counters.tx128to255octets_gb +=
			dwceqos_read(lp, DWC_MMC_TX128TO255OCTETS_GB);
	if (tx_mask & BIT(5))
		lp->mmc_counters.tx65to127octets_gb +=
			dwceqos_read(lp, DWC_MMC_TX65TO127OCTETS_GB);
	if (tx_mask & BIT(4))
		lp->mmc_counters.tx64octets_gb +=
			dwceqos_read(lp, DWC_MMC_TX64OCTETS_GB);
	if (tx_mask & BIT(3))
		lp->mmc_counters.txmulticastpackets_g +=
			dwceqos_read(lp, DWC_MMC_TXMULTICASTPACKETS_G);
	if (tx_mask & BIT(2))
		lp->mmc_counters.txbroadcastpackets_g +=
			dwceqos_read(lp, DWC_MMC_TXBROADCASTPACKETS_G);
	if (tx_mask & BIT(1))
		lp->mmc_counters.txpacketcount_gb +=
			dwceqos_read(lp, DWC_MMC_TXPACKETCOUNT_GB);
	if (tx_mask & BIT(0))
		lp->mmc_counters.txoctetcount_gb +=
			dwceqos_read(lp, DWC_MMC_TXOCTETCOUNT_GB);

	if (rx_mask & BIT(27))
		lp->mmc_counters.rxlpitranscntr +=
			dwceqos_read(lp, DWC_MMC_RXLPITRANSCNTR);
	if (rx_mask & BIT(26))
		lp->mmc_counters.rxlpiuscntr +=
			dwceqos_read(lp, DWC_MMC_RXLPIUSCNTR);
	if (rx_mask & BIT(25))
		lp->mmc_counters.rxctrlpackets_g +=
			dwceqos_read(lp, DWC_MMC_RXCTRLPACKETS_G);
	if (rx_mask & BIT(24))
		lp->mmc_counters.rxrcverror +=
			dwceqos_read(lp, DWC_MMC_RXRCVERROR);
	if (rx_mask & BIT(23))
		lp->mmc_counters.rxwatchdog +=
			dwceqos_read(lp, DWC_MMC_RXWATCHDOG);
	if (rx_mask & BIT(22))
		lp->mmc_counters.rxvlanpackets_gb +=
			dwceqos_read(lp, DWC_MMC_RXVLANPACKETS_GB);
	if (rx_mask & BIT(21))
		lp->mmc_counters.rxfifooverflow +=
			dwceqos_read(lp, DWC_MMC_RXFIFOOVERFLOW);
	if (rx_mask & BIT(20))
		lp->mmc_counters.rxpausepackets +=
			dwceqos_read(lp, DWC_MMC_RXPAUSEPACKETS);
	if (rx_mask & BIT(19))
		lp->mmc_counters.rxoutofrangetype +=
			dwceqos_read(lp, DWC_MMC_RXOUTOFRANGETYPE);
	if (rx_mask & BIT(18))
		lp->mmc_counters.rxlengtherror +=
			dwceqos_read(lp, DWC_MMC_RXLENGTHERROR);
	if (rx_mask & BIT(17))
		lp->mmc_counters.rxunicastpackets_g +=
			dwceqos_read(lp, DWC_MMC_RXUNICASTPACKETS_G);
	if (rx_mask & BIT(16))
		lp->mmc_counters.rx1024tomaxoctets_gb +=
			dwceqos_read(lp, DWC_MMC_RX1024TOMAXOCTETS_GB);
	if (rx_mask & BIT(15))
		lp->mmc_counters.rx512to1023octets_gb +=
			dwceqos_read(lp, DWC_MMC_RX512TO1023OCTETS_GB);
	if (rx_mask & BIT(14))
		lp->mmc_counters.rx256to511octets_gb +=
			dwceqos_read(lp, DWC_MMC_RX256TO511OCTETS_GB);
	if (rx_mask & BIT(13))
		lp->mmc_counters.rx128to255octets_gb +=
			dwceqos_read(lp, DWC_MMC_RX128TO255OCTETS_GB);
	if (rx_mask & BIT(12))
		lp->mmc_counters.rx65to127octets_gb +=
			dwceqos_read(lp, DWC_MMC_RX65TO127OCTETS_GB);
	if (rx_mask & BIT(11))
		lp->mmc_counters.rx64octets_gb +=
			dwceqos_read(lp, DWC_MMC_RX64OCTETS_GB);
	if (rx_mask & BIT(10))
		lp->mmc_counters.rxoversize_g +=
			dwceqos_read(lp, DWC_MMC_RXOVERSIZE_G);
	if (rx_mask & BIT(9))
		lp->mmc_counters.rxundersize_g +=
			dwceqos_read(lp, DWC_MMC_RXUNDERSIZE_G);
	if (rx_mask & BIT(8))
		lp->mmc_counters.rxjabbererror +=
			dwceqos_read(lp, DWC_MMC_RXJABBERERROR);
	if (rx_mask & BIT(7))
		lp->mmc_counters.rxrunterror +=
			dwceqos_read(lp, DWC_MMC_RXRUNTERROR);
	if (rx_mask & BIT(6))
		lp->mmc_counters.rxalignmenterror +=
			dwceqos_read(lp, DWC_MMC_RXALIGNMENTERROR);
	if (rx_mask & BIT(5))
		lp->mmc_counters.rxcrcerror +=
			dwceqos_read(lp, DWC_MMC_RXCRCERROR);
	if (rx_mask & BIT(4))
		lp->mmc_counters.rxmulticastpackets_g +=
			dwceqos_read(lp, DWC_MMC_RXMULTICASTPACKETS_G);
	if (rx_mask & BIT(3))
		lp->mmc_counters.rxbroadcastpackets_g +=
			dwceqos_read(lp, DWC_MMC_RXBROADCASTPACKETS_G);
	if (rx_mask & BIT(2))
		lp->mmc_counters.rxoctetcount_g +=
			dwceqos_read(lp, DWC_MMC_RXOCTETCOUNT_G);
	if (rx_mask & BIT(1))
		lp->mmc_counters.rxoctetcount_gb +=
			dwceqos_read(lp, DWC_MMC_RXOCTETCOUNT_GB);
	if (rx_mask & BIT(0))
		lp->mmc_counters.rxpacketcount_gb +=
			dwceqos_read(lp, DWC_MMC_RXPACKETCOUNT_GB);
}

void dwceqos_get_stats64(struct net_local *lp, int mode)
{
	unsigned long flags;
	struct dwceqos_mmc_counters *hwstats = &lp->mmc_counters;

	spin_lock_irqsave(&lp->stats_lock, flags);
	dwceqos_read_mmc_counters(lp, lp->mmc_rx_counters_mask,
				  lp->mmc_tx_counters_mask);
	spin_unlock_irqrestore(&lp->stats_lock, flags);

	if (1 & mode) {
		printf("Rx: rx_packets = 0x%llx\n",
				hwstats->rxpacketcount_gb);
	}

	if (2 & mode) {
		printf("Tx: tx_packets=0x%llx, tx_bytes=0x%llx\n",
			hwstats->txpacketcount_gb, hwstats->txoctetcount_gb);
		printf("Tx: tx_errors=0x%llx, tx_errors2=0x%llx\n",
			hwstats->txpacketcount_gb - hwstats->txpacketcount_g,
			hwstats->txunderflowerror - hwstats->txcarriererror);
	}
}

static void dw_DMA_status_check(struct net_local *lp)
{
	u32 reg;
	reg = dwceqos_read(lp, REG_DWCEQOS_DMA_DEBUG_ST0);
	printf("DMA_Debug_Status0: 0x%08x\n", reg);
	printf("\t Tx CH0 status value=%d\n",
				(reg & GENMASK(15, 12) >> 12));

	reg = 0;
	reg = dwceqos_read(lp, 0x1150);
	printf("Tx cur high data buffer = 0x%x\n", reg);
	reg = dwceqos_read(lp, 0x1154);
	printf("Tx cur low data buffer = 0x%x\n", reg);

	reg = 0;
	reg = dwceqos_read(lp, 0x1160);
	printf("DMA_CH0 status value = 0x%x\n", reg);
}

static void dwceqos_enable_mmc_interrupt(struct net_local *lp)
{
	dwceqos_write(lp, REG_DWCEQOS_MMC_RXIRQMASK, 0);
	dwceqos_write(lp, REG_DWCEQOS_MMC_TXIRQMASK, 0);
}

static void dwceqos_get_timestamp(struct dwceqos_dma_desc *desc,
								u64 *ts)
{
	struct dwceqos_dma_desc *p = (struct dwceqos_dma_desc *)desc;
	u64 ns;

	ns = le32_to_cpu(p->des0);
	/* convert high/sec time stamp value to nanosecond */
	ns += le32_to_cpu(p->des1) * 1000000000ULL;

	*ts = ns;
}

void emac_get_tx_ts(struct net_local *lp,
					u32 tx_q, u64 *ts)
{
	struct dwceqos_dma_desc *dd;
	struct emac_tx_queue* txq;

	txq = &lp->tx_queues[tx_q];

	dd = &txq->tx_descs[txq->tx_cur];
	inval_dcache_area(dd, sizeof(struct dwceqos_dma_desc));
	dwceqos_get_timestamp(dd, ts);
}
void emac_get_rx_ts(struct net_local *lp,
					u32 rx_q, u64 *ts)
{
	struct dwceqos_dma_desc *dd;
	struct emac_rx_queue* rxq;

	rxq = &lp->rx_queues[rx_q];

	dd = &rxq->rx_descs[rxq->rx_cur];
	inval_dcache_area(dd, sizeof(struct dwceqos_dma_desc));
	dwceqos_get_timestamp(dd, ts);
}
static void dwceqos_tx_prepare(char *buf, struct net_local *lp,
			       u32 txq, struct dwceqos_tx *tx)
{
	size_t n = 1;

	tx->nr_descriptors = n;
	tx->initial_descriptor = lp->tx_queues[txq].tx_next;
	tx->last_descriptor = lp->tx_queues[txq].tx_next;
	tx->prev_gso_size = lp->gso_size;
}

static int dwceqos_tx_linear(char *buf, struct net_local *lp,
			    u32 tx_q, struct dwceqos_tx *tx, size_t len)
{
	struct ring_desc *rd;
	struct dwceqos_dma_desc *dd;
	emac_dma_addr_t dma_handle;
	struct emac_tx_queue* txq;

	txq = &lp->tx_queues[tx_q];
	/* make sure data is in mem before using DMA*/
	flush_dcache_area(buf, len);

	dma_handle = (emac_dma_addr_t)buf;

	rd = &txq->tx_skb_ring[txq->tx_next];
	dd = &txq->tx_descs[txq->tx_next];

	rd->skb = buf;
	rd->len = len;
	rd->mapping = dma_handle;

	/* Set up DMA Descriptor
	 * Dangerous: supposing the buf is 32bits
	 */

	dd->des0 = (dma_handle & 0xFFFFFFFF);

	dd->des1 = (dma_handle >> 32);
	dd->des2 = len;
	dd->des3 = len;

	dd->des3 |= DWCEQOS_DMA_TDES3_FD;
	if (txq->tx_next  != tx->initial_descriptor)
		dd->des3 |= DWCEQOS_DMA_TDES3_OWN;

	tx->last_descriptor = txq->tx_next;
	txq->tx_next = (txq->tx_next + 1) % DWCEQOS_TX_DCNT;

	flush_dcache_area(dd, sizeof(struct dwceqos_dma_desc));
#ifndef VCS_TEST
	printf("%s: tx Desc config info\n", __func__);
	print_descriptor_tx(txq, tx->last_descriptor);
	printf("\n");
#endif
	return 0;
}

static void dwceqos_tx_poll_demand(struct net_local *lp,
					u32 txq)
{
	dwceqos_write(lp, DMA_CHAN_TX_END_ADDR(txq),
		      lp->tx_queues[txq].tx_descs_tail_addr);
}

static void dwceqos_tx_finalize(char *skb, struct net_local *lp,
				u32 tx_q, struct dwceqos_tx *tx, bool ptp)
{
	u32 regval;
	struct emac_tx_queue* txq;

	txq = &lp->tx_queues[tx_q];
	txq->tx_descs[tx->last_descriptor].des3 |= DWCEQOS_DMA_TDES3_LD;
	txq->tx_descs[tx->last_descriptor].des2 |= DWCEQOS_DMA_TDES2_IOC;
	if (ptp) {
		#define TDES2_TIMESTAMP_ENABLE		BIT(30)
		txq->tx_descs[tx->last_descriptor].des2 |= TDES2_TIMESTAMP_ENABLE;
	}
	flush_dcache_area(&txq->tx_descs[tx->last_descriptor],
                    sizeof(struct dwceqos_dma_desc));

	txq->tx_skb_ring[tx->last_descriptor].skb = skb;

	/* Make all descriptor updates visible to the DMA before setting the
	 * owner bit.
	 */
	wmb();

	txq->tx_descs[tx->initial_descriptor].des3 |= DWCEQOS_DMA_TDES3_OWN;
	flush_dcache_area(&txq->tx_descs[tx->initial_descriptor],
                    sizeof(struct dwceqos_dma_desc));
	/* Make the owner bit visible before TX wakeup. */
	wmb();
#ifndef VCS_TEST
	printf("%s: tx Desc config info\n", __func__);
	print_descriptor_tx(txq, tx->initial_descriptor);
	printf("\n");
#endif
	dwceqos_tx_poll_demand(lp, tx_q);

#ifdef EMAC_DEBUG
	dw_DMA_status_check(lp);
	puts("TxTrigger\n");
#endif
}

static void dwceqos_tx_rollback(struct net_local *lp,
					u32 tx_q, struct dwceqos_tx *tx)
{
	struct emac_tx_queue *txq;
	size_t i = tx->initial_descriptor;

	txq = &lp->tx_queues[tx_q];
	while (i != txq->tx_next) {
		if (txq->tx_skb_ring[i].mapping)
            inval_dcache_area((void*)txq->tx_skb_ring[i].mapping,
                            txq->tx_skb_ring[i].len);
		txq->tx_skb_ring[i].mapping = 0;
		txq->tx_skb_ring[i].skb = NULL;

		memset(&txq->tx_descs[i], 0, sizeof(txq->tx_descs[i]));

		i = (i + 1) % DWCEQOS_TX_DCNT;
	}

	txq->tx_next = tx->initial_descriptor;
	lp->gso_size = tx->prev_gso_size;
}

static void dwceqos_dma_enable_txirq(struct net_local *lp,
								u32 tx_q)
{
	u32 regval;
	unsigned long flags;

	spin_lock_irqsave(&lp->hw_lock, flags);
	regval = dwceqos_read(lp, DMA_CHAN_INTR_ENA(tx_q));
	regval |= DWCEQOS_DMA_CH0_IE_TIE;
	dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_IE, regval);
	spin_unlock_irqrestore(&lp->hw_lock, flags);
}

/* need to add extra code to check tx is done before reclaim*/
void dwceqos_tx_reclaim(struct net_local *lp, u32 tx_q)
{
	unsigned int tx_bytes = 0;
	unsigned int tx_packets = 0;
	struct emac_tx_queue* txq;

	txq = &lp->tx_queues[tx_q];
	spin_lock(&txq->tx_lock);

	while (txq->tx_free < DWCEQOS_TX_DCNT) {
		struct dwceqos_dma_desc *dd = &txq->tx_descs[txq->tx_cur];
		struct ring_desc *rd = &txq->tx_skb_ring[txq->tx_cur];

		inval_dcache_area(dd, sizeof(struct dwceqos_dma_desc));
		/* Descriptor still being held by DMA ? */
		if (dd->des3 & DWCEQOS_DMA_TDES3_OWN)
			break;

		if (rd->mapping)
			inval_dcache_area((char *)rd->mapping, rd->len);

		if ((rd->skb)) {
			++tx_packets;
		}

		rd->skb = NULL;
		rd->mapping = 0;
		txq->tx_free++;
		txq->tx_cur = (txq->tx_cur + 1) % DWCEQOS_TX_DCNT;

		if ((dd->des3 & DWCEQOS_DMA_TDES3_LD) &&
		    (dd->des3 & DWCEQOS_DMA_RDES3_ES)) {
				printf("TX Error, TDES3 = 0x%x\n",
					   dd->des3);
				//print_status(lp);
		}
	}
	spin_unlock(&txq->tx_lock);

	dwceqos_dma_enable_txirq(lp, tx_q);
}

void dwceqos_show_status(struct net_local *lp,
					u32 tx_q, u32 rx_q)
{
	print_status(lp, &lp->tx_queues[tx_q], &lp->rx_queues[rx_q]);
}
int dwceqos_xmit(struct net_local *lp, u32 tx_q,
				char *skb, size_t len, bool ptp)
{
	struct dwceqos_tx trans;
	int err;

	dwceqos_tx_prepare(skb, lp, tx_q, &trans);
	if (lp->tx_queues[tx_q].tx_free < trans.nr_descriptors) {
		printf("no free ring bufs for transmition\n");
		return 0;
	}

	err = dwceqos_tx_linear(skb, lp, tx_q, &trans, len);
	if (err)
		goto tx_error;

	dwceqos_tx_finalize(skb, lp, tx_q, &trans, ptp);

	spin_lock(&lp->tx_queues[tx_q].tx_lock);
	lp->tx_queues[tx_q].tx_free -= trans.nr_descriptors;
	spin_unlock(&lp->tx_queues[tx_q].tx_lock);

	return 1;

tx_error:
	dwceqos_tx_rollback(lp, tx_q, &trans);
	heap_free(skb);
	return 0;
}

static int dwceqos_packet_avail(struct net_local *lp, u32 rx_q)
{
	struct emac_rx_queue *rxq;
	rxq = &lp->rx_queues[rx_q];
	inval_dcache_addr(&rxq->rx_descs[rxq->rx_cur].des3);
	return !(rxq->rx_descs[rxq->rx_cur].des3 & DWCEQOS_DMA_RDES3_OWN);
}

int dwceqos_rx(struct net_local *lp, int budget, u32 rx_q,
                char** recv, u32* length)
{
	char *skb;
	u32 tot_size = 0;
	unsigned int n_packets = 0;
	unsigned int n_descs = 0;
	u32 len;
	struct emac_rx_queue *rxq;

	struct dwceqos_dma_desc *dd;
	char *new_skb;
	emac_dma_addr_t new_skb_baddr = 0;

	rxq = &lp->rx_queues[rx_q];
	*length = 0;
	while (n_descs < budget) {
		if (!dwceqos_packet_avail(lp, rx_q)) {
			int i = 10;
			while ((i > 0) && (!dwceqos_packet_avail(lp, rx_q))) {
				i--;
				udelay(1);
				if (i % 10 == 9)
					printf("Rx no\n");
			}
			if (i == 0) {
				printf("Rx time out,die\n");
				break;
			}
		} else {
			printf("data received at rx_q=%d\n", rx_q);
		}

		new_skb = (char *)emac_heap_alloc(DWCEQOS_RX_BUF_SIZE);
		if (!new_skb) {
			printf("no memory for new sk_buff\n");
			break;
		}

		/* Get dma handle of skb->data, suppose virt=phy addr */
		new_skb_baddr = (emac_dma_addr_t)new_skb;

		/* Read descriptor data after reading owner bit. */
		rmb();

		dd = &rxq->rx_descs[rxq->rx_cur];
		inval_dcache_area(dd, sizeof(struct dwceqos_dma_desc));
		len = DWCEQOS_DMA_RDES3_PL(dd->des3);
		skb = rxq->rx_skb_ring[rxq->rx_cur].skb;

		/* Unmap old buffer */
		inval_dcache_area(skb, rxq->rx_skb_ring[rxq->rx_cur].len);

		/* Discard packet on reception error or bad checksum */
		if ((dd->des3 & DWCEQOS_DMA_RDES3_ES) ||
		    (dd->des1 & DWCEQOS_DMA_RDES1_IPCE)) {
			heap_free(skb);
			skb = NULL;
		} else {
			switch (dd->des1 & DWCEQOS_DMA_RDES1_PT) {
			case DWCEQOS_DMA_RDES1_PT_UDP:
			case DWCEQOS_DMA_RDES1_PT_TCP:
			case DWCEQOS_DMA_RDES1_PT_ICMP:
				printf("Rx packet CHECKSUM_UNNECESSARY\n");
				break;
			default:
				printf("Rx packet CHECKSUM_NONE\n");
				break;
			}
		}

		if (!skb) {
			printf("rx error: des3=%X\n",
					   rxq->rx_descs[rxq->rx_cur].des3);
		}
		*recv = skb; /* output buffer */
		*length = len;

		rxq->rx_descs[rxq->rx_cur].des0 = new_skb_baddr;
		rxq->rx_descs[rxq->rx_cur].des1 = 0;
		rxq->rx_descs[rxq->rx_cur].des2 = 0;
		/* The DMA must observe des0/1/2 written before des3. */
		wmb();
		rxq->rx_descs[rxq->rx_cur].des3 = DWCEQOS_DMA_RDES3_INTE |
						DWCEQOS_DMA_RDES3_OWN  |
						DWCEQOS_DMA_RDES3_BUF1V;
		flush_dcache_area(&rxq->rx_descs[rxq->rx_cur],
                        sizeof(struct dwceqos_dma_desc));

		rxq->rx_skb_ring[rxq->rx_cur].mapping = new_skb_baddr;
		rxq->rx_skb_ring[rxq->rx_cur].len = DWCEQOS_RX_BUF_SIZE;
		rxq->rx_skb_ring[rxq->rx_cur].skb = new_skb;

		n_descs++;
		rxq->rx_cur = (rxq->rx_cur + 1) % DWCEQOS_RX_DCNT;
	}

	/* Make sure any ownership update is written to the descriptors before
	 * DMA wakeup.
	 */
	wmb();

	dwceqos_write(lp, DMA_CHAN_STATUS(rx_q), DWCEQOS_DMA_CH0_IS_RI);
	/* Wake up RX by writing tail pointer */
	dwceqos_write(lp, DMA_CHAN_RX_END_ADDR(rx_q),
		      rxq->rx_descs_tail_addr);

	return n_descs;
}

static void dwceqos_descriptor_free_tx(struct emac_tx_queue *lp)
{
	int size;
	int i;

	if (lp->tx_skb_ring) {
		for (i = 0; i < DWCEQOS_TX_DCNT; i++) {
			if (lp->tx_skb_ring[i].skb) {
				heap_free(lp->tx_skb_ring[i].skb);
				lp->tx_skb_ring[i].skb = NULL;
			}
			if (lp->tx_skb_ring[i].mapping) {
				lp->tx_skb_ring[i].mapping = 0;
			}
		}
	}

	heap_free(lp->tx_skb_ring);
	lp->tx_skb_ring = NULL;

	size = DWCEQOS_TX_DCNT * sizeof(struct dwceqos_dma_desc);
	if (lp->tx_descs) {
		emac_free_coherent(size,
				  (void *)(lp->tx_descs), &lp->tx_descs_addr);
		lp->tx_descs = NULL;
	}
}

static void dwceqos_descriptor_free_rx(struct emac_rx_queue *rxq)
{
	int size;
	int i;

	if (rxq->rx_skb_ring) {
		for (i = 0; i < DWCEQOS_RX_DCNT; i++) {
			if (rxq->rx_skb_ring[i].skb) {
                /* skp rx dma unmap */
				heap_free(rxq->rx_skb_ring[i].skb);
				rxq->rx_skb_ring[i].skb = NULL;
				rxq->rx_skb_ring[i].mapping = 0;
			}
		}
	}

	heap_free(rxq->rx_skb_ring);
	rxq->rx_skb_ring = NULL;

	size = DWCEQOS_RX_DCNT * sizeof(struct dwceqos_dma_desc);
	if (rxq->rx_descs) {
		emac_free_coherent(size,
				  (void *)(rxq->rx_descs), &rxq->rx_descs_addr);
		rxq->rx_descs = NULL;
	}
}

static void dwceqos_alloc_rxring_desc(struct emac_rx_queue *rxq, int index)
{
	char *new_skb;
	emac_dma_addr_t new_skb_baddr = 0;

	new_skb = (char *)emac_heap_alloc(DWCEQOS_RX_BUF_SIZE);
	if (!new_skb) {
		printf("alloc_skb error for desc %d\n", index);
		return;
	}

	/* suppose virt = phys addr */
	new_skb_baddr = (emac_dma_addr_t)new_skb;

	rxq->rx_descs[index].des0 = (new_skb_baddr & 0xFFFFFFFF);
	rxq->rx_descs[index].des1 = (new_skb_baddr >> 32);
	rxq->rx_descs[index].des2 = 0;
	rxq->rx_descs[index].des3 = DWCEQOS_DMA_RDES3_INTE |
				   DWCEQOS_DMA_RDES3_BUF1V |
				   DWCEQOS_DMA_RDES3_OWN;

	rxq->rx_skb_ring[index].mapping = new_skb_baddr;
	rxq->rx_skb_ring[index].len = DWCEQOS_RX_BUF_SIZE;

	rxq->rx_skb_ring[index].skb = new_skb;

	flush_dcache_area(&rxq->rx_descs[index], sizeof(struct dwceqos_dma_desc));
}

static void emac_config_bus(struct dwceqos_bus_cfg* bus_cfg)
{
	if (NULL == bus_cfg)
		printf("%s para wrong\n", __func__);
	/* let's get into real world */
	bus_cfg->en_lpi = false;
	bus_cfg->tx_pbl = 8;
	bus_cfg->rx_pbl = 8;
	bus_cfg->write_requests = 16;
	bus_cfg->read_requests  = 16;
	bus_cfg->burst_map = 0x7;

#ifndef VCS_TEST
	printf("BusCfg: lpi:%u wr:%u rr:%u bm:%X rxpbl:%u txpbl:%d\n",
			bus_cfg->en_lpi,
			bus_cfg->write_requests,
			bus_cfg->read_requests,
			bus_cfg->burst_map,
			bus_cfg->rx_pbl,
			bus_cfg->tx_pbl);
#endif
}

static int dwceqos_descriptor_init(struct net_local *emac_dev,
						u32 txq_count, u32 rxq_count)
{
	int size;
	u32 i, queue;
	struct emac_tx_queue *txq;
	struct emac_rx_queue *rxq;
#ifndef VCS_TEST
	printf("desc init tx_q=%d, rx_q=%d\n", txq_count, rxq_count);
#endif

	for (queue = 0; queue < txq_count; queue++) {
		txq = &emac_dev->tx_queues[queue];

		txq->tx_skb_ring = NULL;
		txq->tx_descs = NULL;
		txq->tx_cur = 0;
		txq->tx_next = 0;
		txq->tx_free = DWCEQOS_TX_DCNT;

		size = DWCEQOS_TX_DCNT * sizeof(struct ring_desc);
		txq->tx_skb_ring = (struct ring_desc*)emac_heap_alloc(size);
		if (!txq->tx_skb_ring)
			goto err_out_tx;
		/* DMA desc must be in coherent memory*/
		txq->tx_descs = emac_alloc_coherent(size, &txq->tx_descs_addr);
		if (!txq->tx_descs)
			goto err_out_tx;
		txq->tx_descs_tail_addr = txq->tx_descs_addr +
			sizeof(struct dwceqos_dma_desc) * DWCEQOS_TX_DCNT;

		/* Initialize TX Descriptors */
		for (i = 0; i < DWCEQOS_TX_DCNT; ++i) {
			txq->tx_descs[i].des0 = 0;
			txq->tx_descs[i].des1 = 0;
			txq->tx_descs[i].des2 = 0;
			txq->tx_descs[i].des3 = 0;
		}
		continue;
err_out_tx:
		printf("ERROR: %s sth wrong at tx, skb_ring=0x%llx, desc=0x%llx\n",
			__func__, txq->tx_skb_ring, txq->tx_descs);
		for (i = 0; i < queue; i++) {
			txq = &emac_dev->tx_queues[i];
			dwceqos_descriptor_free_tx(txq);
		}
		return -ENOMEM;
	}

	for (queue = 0; queue < rxq_count; queue++) {
		rxq = &emac_dev->rx_queues[queue];

		rxq->rx_skb_ring = NULL;
		rxq->rx_descs = NULL;
		/* Reset the DMA indexes */
		rxq->rx_cur = 0;

		/* Allocate Ring descriptors */
		size = DWCEQOS_RX_DCNT * sizeof(struct ring_desc);
		rxq->rx_skb_ring = (struct ring_desc*)emac_heap_alloc(size);
		if (!rxq->rx_skb_ring)
			goto err_out_rx;

		/* Allocate DMA descriptors */
		size = DWCEQOS_RX_DCNT * sizeof(struct dwceqos_dma_desc);
		rxq->rx_descs = emac_alloc_coherent(size,
				&rxq->rx_descs_addr);
		if (!rxq->rx_descs)
			goto err_out_rx;
		rxq->rx_descs_tail_addr = rxq->rx_descs_addr +
			sizeof(struct dwceqos_dma_desc) * DWCEQOS_RX_DCNT;

		size = DWCEQOS_TX_DCNT * sizeof(struct dwceqos_dma_desc);
		/* Initialize RX Ring Descriptors and buffers */
		for (i = 0; i < DWCEQOS_RX_DCNT; ++i) {
			dwceqos_alloc_rxring_desc(rxq, i);
			if (!(rxq->rx_skb_ring[rxq->rx_cur].skb))
				goto err_out_rx;
		}
	#ifdef EMAC_DEBUG
		printf("Rx descriptor show:\n");
		for (i = 0; i < DWCEQOS_RX_DCNT; ++i) {
			print_descriptor_rx(rxq, i);
		}
	#endif
		continue;
err_out_rx:
		printf("ERROR: %s sth wrong at rx\n", __func__);
		for (i = 0; i < queue; i++) {
			rxq = &emac_dev->rx_queues[i];
			dwceqos_descriptor_free_rx(rxq);
		}
		return -ENOMEM;
	}

	/* Make descriptor writes visible to the DMA. */
	wmb();

	return 0;


}

/* DMA reset. When issued also resets all MTL and MAC registers as well */
static void dwceqos_reset_hw(struct net_local *lp)
{
	/* Wait (at most) 0.5 seconds for DMA reset*/
	int i = 5000;
	u32 reg;

	/* Force gigabit to guarantee a TX clock for GMII. */
	reg = dwceqos_read(lp, REG_DWCEQOS_MAC_CFG);
	reg &= ~(DWCEQOS_MAC_CFG_PS | DWCEQOS_MAC_CFG_FES);/*1Gb speed*/
	reg |= DWCEQOS_MAC_CFG_DM;/* duplex */
	reg |= DWCEQOS_MAC_CFG_LPM; /* loop back */
	dwceqos_write(lp, REG_DWCEQOS_MAC_CFG, reg);

	dwceqos_write(lp, REG_DWCEQOS_DMA_MODE, DWCEQOS_DMA_MODE_SWR);

	do {
		udelay(1);
		i--;
		reg = dwceqos_read(lp, REG_DWCEQOS_DMA_MODE);
		if (i % 10 == 1)
			printf("%d: %x\n", i, reg);
	} while ((reg & DWCEQOS_DMA_MODE_SWR) && i);

	/* We might experience a timeout if the chip clock mux is broken */
	if (!i)
		printf("DMA reset timed out!\n");
#ifdef EMAC_DEBUG
	printf("check the default status after HW reset\n");
	dw_DMA_status_check(lp);
	printf("\n");
#endif
}

/* Program the following fields to initialize the DMA sys bus
* 1. AAL
* 2. Fixed burst or undefine burst
*/
static void dwceqos_config_DMA_bus(struct net_local *lp)
{
	u32 sysbus_reg;

	/* N.B. We do not support the Fixed Burst mode because it
	 * opens a race window by making HW access to DMA descriptors
	 * non-atomic.----how to confirm it???
	 */

	sysbus_reg = DWCEQOS_DMA_SYSBUS_MODE_AAL;

	if (lp->bus_cfg.en_lpi)
		sysbus_reg |= DWCEQOS_DMA_SYSBUS_MODE_EN_LPI;

	if (lp->bus_cfg.burst_map)
		sysbus_reg |= DWCEQOS_DMA_SYSBUS_MODE_BURST(
			lp->bus_cfg.burst_map);
	else
		sysbus_reg |= DWCEQOS_DMA_SYSBUS_MODE_BURST(
			DWCEQOS_DMA_SYSBUS_MODE_BURST_DEFAULT);

	if (lp->bus_cfg.read_requests)
		sysbus_reg |= DWCEQOS_DMA_SYSBUS_MODE_RD_OSR_LIMIT(
			lp->bus_cfg.read_requests - 1);
	else
		sysbus_reg |= DWCEQOS_DMA_SYSBUS_MODE_RD_OSR_LIMIT(
			DWCEQOS_DMA_SYSBUS_MODE_RD_OSR_LIMIT_DEFAULT);

	if (lp->bus_cfg.write_requests)
		sysbus_reg |= DWCEQOS_DMA_SYSBUS_MODE_WR_OSR_LIMIT(
			lp->bus_cfg.write_requests - 1);
	else
		sysbus_reg |= DWCEQOS_DMA_SYSBUS_MODE_WR_OSR_LIMIT(
			DWCEQOS_DMA_SYSBUS_MODE_WR_OSR_LIMIT_DEFAULT);
#ifndef VCS_TEST
	printf("SysbusMode %#X\n", sysbus_reg);
#endif

	dwceqos_write(lp, REG_DWCEQOS_DMA_SYSBUS_MODE, sysbus_reg);
}

static void dwceqos_set_umac_addr(struct net_local *lp, unsigned char *addr,
				  unsigned int reg_n)
{
	unsigned long data;

	data = (addr[5] << 8) | addr[4];
	dwceqos_write(lp, DWCEQOS_ADDR_HIGH(reg_n),
		      data | DWCEQOS_MAC_MAC_ADDR_HI_EN);
	data = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	dwceqos_write(lp, DWCEQOS_ADDR_LOW(reg_n), data);
}

static void dwceqos_configure_clock(struct net_local *lp)
{
	unsigned long rate_mhz = 25; /* suppose 25Mhz*/

	dwceqos_write(lp,
		      REG_DWCEQOS_MAC_1US_TIC_COUNTER,
		      DWCEQOS_MAC_1US_TIC_COUNTER_VAL(rate_mhz - 1));
}

static void dwceqos_get_hwfeatures(struct net_local *lp)
{
	lp->feature0 = dwceqos_read(lp, REG_DWCEQOS_MAC_HW_FEATURE0);
	lp->feature1 = dwceqos_read(lp, REG_DWCEQOS_MAC_HW_FEATURE1);
	lp->feature2 = dwceqos_read(lp, REG_DWCEQOS_MAC_HW_FEATURE2);
}

static void emac_start_mtl_dma(struct net_local *lp,
					struct dwceqos_MTL_cfg* emac_MTL_cfg)
{
	u32 regval;
	u32 queue;
	u32 rx_channels_count = emac_MTL_cfg->rx_queues_count;
	u32 tx_channels_count = emac_MTL_cfg->tx_queues_count;
	/* caution: suppose dma channel, queue are equal, tx/rx queue equal*/

	for (queue = 0; queue < rx_channels_count; queue++) {
		/* Enable Interrupts */
		dwceqos_write(lp, DMA_CHAN_INTR_ENA(queue),
				DWCEQOS_DMA_CH0_IE_NIE |
				DWCEQOS_DMA_CH0_IE_RIE | DWCEQOS_DMA_CH0_IE_TIE |
				DWCEQOS_DMA_CH0_IE_AIE |
				DWCEQOS_DMA_CH0_IE_FBEE);
	}
	dwceqos_write(lp, REG_DWCEQOS_MAC_IE, 0);

	for (queue = 0; queue < tx_channels_count; queue++) {
		regval = dwceqos_read(lp, DMA_CHAN_TX_CONTROL(queue));
		dwceqos_write(lp, DMA_CHAN_TX_CONTROL(queue),
				regval | DWCEQOS_DMA_CH_CTRL_START);
	}

	/* Enable MAC TX/RX */
	regval = dwceqos_read(lp, REG_DWCEQOS_MAC_CFG);
	dwceqos_write(lp, REG_DWCEQOS_MAC_CFG,
		      regval | DWCEQOS_MAC_CFG_TE | DWCEQOS_MAC_CFG_RE);

}

static void emac_stop_dma_mtl_mac(struct net_local *lp)
{
	u32 regval;
	u32 queue;
	struct emac_rx_queue* rxq;
	struct emac_tx_queue* txq;

	for (queue = 0; queue < MTL_MAX_TX_QUEUES; queue++) {
		/* stop dma*/
		regval = dwceqos_read(lp, DMA_CHAN_TX_CONTROL(queue));
		regval &= (~DWCEQOS_DMA_CH_CTRL_START);
		dwceqos_write(lp, DMA_CHAN_TX_CONTROL(queue), regval);

		/* disable MTL queues */
		regval = dwceqos_read(lp, MTL_CHAN_TX_OP_MODE(queue));
		regval &= (~DWCEQOS_MTL_TXQ_TXQEN);
		dwceqos_write(lp, MTL_CHAN_TX_OP_MODE(queue), regval);

		txq = &lp->tx_queues[queue];

		txq->tx_cur = 0;
		txq->tx_next = 0;
		txq->tx_free = DWCEQOS_TX_DCNT;
	}
	/* stop mac */
	regval = dwceqos_read(lp, REG_DWCEQOS_MAC_CFG);
	regval &= (~(DWCEQOS_MAC_CFG_TE | DWCEQOS_MAC_CFG_RE));
	dwceqos_write(lp, REG_DWCEQOS_MAC_CFG, regval);

	for (queue = 0; queue < MTL_MAX_RX_QUEUES; queue++) {
		/* disable MTL, strange no rxq enable */
		/* stop rx dma */
		regval = dwceqos_read(lp, DMA_CHAN_RX_CONTROL(queue));
		regval &= (~DWCEQOS_DMA_CH_CTRL_START);
		dwceqos_write(lp, DMA_CHAN_RX_CONTROL(queue), regval);

		rxq = &lp->rx_queues[queue];
		rxq->rx_cur = 0;;
	}
}
static void emac_init_hw_dma(struct net_local *lp,
					struct dwceqos_MTL_cfg* emac_MTL_cfg)
{
	u32 regval;
	u32 buswidth;
	u32 dma_skip;
	u32 queue;

	dwceqos_config_DMA_bus(lp);

	/* Probe data bus width, 32/64/128 bits. */
	dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_TXDESC_TAIL, 0xF);
	regval = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_TXDESC_TAIL);
	buswidth = (regval ^ 0xF) + 1;

	/* Cache-align dma descriptors. */
	dma_skip = (sizeof(struct dwceqos_dma_desc) - 16) / buswidth;
	if (0 != dma_skip)
		printf("attention: dma skip = %d, buswidth=%d\n", dma_skip, buswidth);
	//test code by junwang
	dma_skip = 0;
	/* do we support PBLx8, junwang, mark it currently*/
	dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_CTRL,
		      DWCEQOS_DMA_CH_CTRL_DSL(dma_skip)/* |
		      DWCEQOS_DMA_CH_CTRL_PBLX8*/);

	/* Initialize DMA Channel, supposing chan/queue 1:1 mapping, not good */
	for (queue = 0; queue < emac_MTL_cfg->tx_queues_count; queue++) {
		dwceqos_write(lp, DMA_CHAN_TX_RING_LEN(queue), DWCEQOS_TX_DCNT - 1);
		dwceqos_write(lp, DMA_CHAN_TX_BASE_ADDR(queue),
				(u32)(lp->tx_queues[queue].tx_descs_addr & 0xFFFFFFFF));
		/*dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_TXDESC_HLIST,
				(u32)(lp->tx_descs_addr >> 32));*/
		dwceqos_write(lp, DMA_CHAN_TX_END_ADDR(queue),
				lp->tx_queues[queue].tx_descs_tail_addr);

		regval = dwceqos_read(lp, DMA_CHAN_TX_CONTROL(queue));
		if (lp->bus_cfg.tx_pbl)
			regval |= DWCEQOS_DMA_CH_CTRL_PBL(lp->bus_cfg.tx_pbl);
		else
			regval |= DWCEQOS_DMA_CH_CTRL_PBL(2);

		/* Enable TSO if the HW support it */
		if (lp->feature1 & DWCEQOS_MAC_HW_FEATURE1_TSOEN)
			regval |= DWCEQOS_DMA_CH_TX_TSE;
		dwceqos_write(lp, DMA_CHAN_TX_CONTROL(queue), regval);
	}

	for (queue = 0; queue < emac_MTL_cfg->rx_queues_count; queue++) {
		dwceqos_write(lp, DMA_CHAN_RX_RING_LEN(queue), DWCEQOS_RX_DCNT - 1);

		dwceqos_write(lp, DMA_CHAN_RX_BASE_ADDR(queue),
				(u32)(lp->rx_queues[queue].rx_descs_addr & 0xFFFFFFFF));
		/*dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_RXDESC_HLIST,
				(u32)(lp->rx_descs_addr >> 32));*/

		dwceqos_write(lp, DMA_CHAN_RX_END_ADDR(queue),
				lp->rx_queues[queue].rx_descs_tail_addr);


		regval = dwceqos_read(lp, DMA_CHAN_RX_CONTROL(queue));
		if (lp->bus_cfg.rx_pbl)
			regval |= DWCEQOS_DMA_CH_CTRL_PBL(lp->bus_cfg.rx_pbl);
		else
			regval |= DWCEQOS_DMA_CH_CTRL_PBL(2);

		/* max receive buffer size is 2048*/
		regval |= DWCEQOS_DMA_CH_RX_CTRL_BUFSIZE(DWCEQOS_DWCEQOS_RX_BUF_SIZE);
		/* start Rx DMA */
		regval |= DWCEQOS_DMA_CH_CTRL_START;
		dwceqos_write(lp, DMA_CHAN_RX_CONTROL(queue), regval);
	}
}

/**
 *  Description: it is used for configuring the DMA operation mode register in
 *  order to program the tx/rx DMA thresholds or Store-And-Forward mode.
 */
static void emac_dma_operation_mode(struct net_local *lp,
					struct dwceqos_MTL_cfg* emac_MTL_cfg)
{
	u32 rx_channels_count = emac_MTL_cfg->rx_queues_count;
	u32 tx_channels_count = emac_MTL_cfg->tx_queues_count;

	int rxfifosz;
	int txfifosz;
	u32 regval, queue;

	rxfifosz = 128 << (lp->feature1 & GENMASK(4, 0));
	txfifosz = 128 << ((lp->feature1 & GENMASK(10, 6)) >> 6);
#ifndef VCS_TEST
	printf("Tx FIF0 size=%d bytes\n", txfifosz);
	printf("Rx FIF0 size=%d bytes\n", rxfifosz);
#endif
	/* Adjust for real per queue fifo size */
	rxfifosz /= rx_channels_count;
	txfifosz /= tx_channels_count;
	regval = DWCEQOS_MTL_TXQ_SIZE(txfifosz) |
			DWCEQOS_MTL_TXQ_TXQEN | DWCEQOS_MTL_TXQ_TSF |
			DWCEQOS_MTL_TXQ_TTC512;

	for (queue = 0; queue < tx_channels_count; queue++) {
		dwceqos_write(lp, MTL_CHAN_TX_OP_MODE(queue), regval);
	}

	regval = DWCEQOS_MTL_RXQ_SIZE(rxfifosz) |
		DWCEQOS_MTL_RXQ_FUP | DWCEQOS_MTL_RXQ_FEP | DWCEQOS_MTL_RXQ_RSF;

	for (queue = 0; queue < rx_channels_count; queue++) {
		dwceqos_write(lp, MTL_CHAN_RX_OP_MODE(queue), regval);
	}
}

static void config_sub_second_increment(void __iomem *ioaddr,
		u32 ptp_clock, int gmac4, u32 *ssinc)
{
	u32 value = readl_relaxed(ioaddr + PTP_TCR);
	unsigned long data;
	u32 reg_value;

	/* For GMAC3.x, 4.x versions, convert the ptp_clock to nano second
	 *	formula = (1/ptp_clock) * 1000000000
	 * where ptp_clock is 50MHz if fine method is used to update system
	 */
	if (value & PTP_TCR_TSCFUPDT)
		data = (1000000000ULL / 50000000);
	else
		data = (1000000000ULL / ptp_clock);

	/* 0.465ns accuracy */
	if (!(value & PTP_TCR_TSCTRLSSR))
		data = (data * 1000) / 465;

	data &= PTP_SSIR_SSINC_MASK;

	reg_value = data;
	if (gmac4)
		reg_value <<= GMAC4_PTP_SSIR_SSINC_SHIFT;

	writel_relaxed(reg_value, ioaddr + PTP_SSIR);

	if (ssinc)
		*ssinc = data;
}
static int config_addend(void __iomem *ioaddr, u32 addend)
{
	u32 value;
	int limit;

	writel(addend, ioaddr + PTP_TAR);
	/* issue command to update the addend value */
	value = readl(ioaddr + PTP_TCR);
	value |= PTP_TCR_TSADDREG;
	writel(value, ioaddr + PTP_TCR);

	/* wait for present addend update to complete */
	limit = 10;
	while (limit--) {
		if (!(readl(ioaddr + PTP_TCR) & PTP_TCR_TSADDREG))
			break;
		udelay(100);
	}
	if (limit < 0)
		return -EBUSY;

	return 0;
}

static int init_systime(void __iomem *ioaddr, u32 sec, u32 nsec)
{
	int limit;
	u32 value;

	writel(sec, ioaddr + PTP_STSUR);
	writel(nsec, ioaddr + PTP_STNSUR);
	/* issue command to initialize the system time value */
	value = readl(ioaddr + PTP_TCR);
	value |= PTP_TCR_TSINIT;
	writel(value, ioaddr + PTP_TCR);

	/* wait for present system time initialize to complete */
	limit = 10;
	while (limit--) {
		if (!(readl(ioaddr + PTP_TCR) & PTP_TCR_TSINIT))
			break;
		udelay(100);
	}
	if (limit < 0)
		return -EBUSY;

	return 0;
}

static void get_systime(void __iomem *ioaddr, u64 *systime)
{
	u64 ns;

	/* Get the TSSS value */
	ns = readl(ioaddr + PTP_STNSR);
	/* Get the TSS and convert sec time value to nanosecond */
	ns += readl(ioaddr + PTP_STSR) * 1000000000ULL;

	if (systime)
		*systime = ns;
}

void clk_for_ptp_ref(void)
{
	return;
}
static bool emac_init_ptp(struct net_local *lp)
{
	u32 reg, value;
	u32 sec_inc;
	u32 ptp_clk_rate;

	reg = (lp->feature0 & GENMASK(12, 12)) >> 12;
#ifdef EMAC_DEBUG
	printf("1588 timestamp feture is %s\n\n",
				reg ? "enabled" : "disabled");
#endif
	if (!reg) {
		printf("error: PTP is not supported by HW\n");
		return false;
	}

	ptp_clk_rate = 25000000; /* 25Mhz suppose */
	/* MAC_Timestamp_control register 0xb00*/
	value = (PTP_TCR_TSENA | PTP_TCR_TSCFUPDT | PTP_TCR_TSCTRLSSR |
			 PTP_TCR_TSENALL | PTP_TCR_TSVER2ENA | PTP_TCR_TSIPENA |
			 PTP_TCR_TSIPV6ENA | PTP_TCR_TSIPV4ENA | PTP_TCR_TSEVNTENA |
			 PTP_TCR_TSMSTRENA | PTP_TCR_SNAPTYPSEL_1);
	dwceqos_write(lp, PTP_GMAC4_OFFSET + PTP_TCR, value);

	/* need to check ptp reference clock with IC, suppose 25Mhz */
	config_sub_second_increment(lp->baseaddr + PTP_GMAC4_OFFSET,
			ptp_clk_rate, 1, &sec_inc);
	/* need to change addend with other value, check the clk granunity */
	config_addend(lp->baseaddr + PTP_GMAC4_OFFSET, 10);
	init_systime(lp->baseaddr + PTP_GMAC4_OFFSET, 0, 1000);

	{
		/* sanity check for systime */
		u64 systime1, systime2;
		systime1 = systime2 = 0;
		get_systime(lp->baseaddr + PTP_GMAC4_OFFSET, &systime1);
#ifdef VCS_TEST
		udelay(10); /* is it able to detect 10us, check again */
#else
		udelay(100);
#endif
		get_systime(lp->baseaddr + PTP_GMAC4_OFFSET, &systime2);

		if ((systime1 == 0) ||
			(systime2 == 0) || (systime1 >= systime2)) {
			printf("PTP systime not correct t1=0x%llx, t2=0x%llx\n",
						systime1, systime2);
		} else {
			printf("PTP systime passed sanity check t1=0x%llx, t2=0x%llx\n",
					systime1, systime2);
		}
	}

	return true;
}

static void dwceqos_init_hw(struct net_local *lp,
					struct dwceqos_MTL_cfg* emac_MTL_cfg)
{
	u32 regval;
	u32 queue;

	/* Software reset */
	dwceqos_reset_hw(lp);

#ifdef EMAC_DEBUG
	dw_DMA_status_check(lp);
#endif

	emac_init_hw_dma(lp, emac_MTL_cfg);
	emac_init_hw_mtl(lp, emac_MTL_cfg);

	/* Set the HW DMA mode and the COE */
	emac_dma_operation_mode(lp, emac_MTL_cfg);
	if (emac_MTL_cfg->init_ptp) {
		//stub func to enable reference clock if have
		clk_for_ptp_ref();
		emac_init_ptp(lp);
	}
	/* no flow control currently*/
	//dwceqos_configure_flow_control(lp);
	regval = dwceqos_read(lp, REG_DWCEQOS_MAC_PKT_FILT);
	dwceqos_write(lp, REG_DWCEQOS_MAC_PKT_FILT, regval | (1<<31));

	/* Initialize MAC */
	dwceqos_set_umac_addr(lp, lp->mac_addr, 0);

	dwceqos_configure_clock(lp);

	/* MMC counters is not ready*/

	/* probe implemented counters */
	dwceqos_write(lp, REG_DWCEQOS_MMC_RXIRQMASK, ~0u);
	dwceqos_write(lp, REG_DWCEQOS_MMC_TXIRQMASK, ~0u);
	lp->mmc_rx_counters_mask = dwceqos_read(lp, REG_DWCEQOS_MMC_RXIRQMASK);
	lp->mmc_tx_counters_mask = dwceqos_read(lp, REG_DWCEQOS_MMC_TXIRQMASK);
#ifndef VCS_TEST
	printf("MMC: Tx_mask=0x%x, Rx_mask=0x%x\n", lp->mmc_tx_counters_mask,
					lp->mmc_rx_counters_mask);
#endif
	dwceqos_write(lp, REG_DWCEQOS_MMC_CTRL, DWCEQOS_MMC_CTRL_CNTRST |
		DWCEQOS_MMC_CTRL_RSTONRD);
	dwceqos_enable_mmc_interrupt(lp);

	regval = dwceqos_read(lp, REG_DWCEQOS_MAC_CFG);
	dwceqos_write(lp, REG_DWCEQOS_MAC_CFG, DWCEQOS_MAC_CFG_IPC |
		DWCEQOS_MAC_CFG_DM | DWCEQOS_MAC_CFG_TE | DWCEQOS_MAC_CFG_RE | regval);

	emac_start_mtl_dma(lp, emac_MTL_cfg);

	{ /* sanity check */
#ifndef VCS_TEST
		regval = dwceqos_read(lp, REG_DWCEQOS_MAC_CFG);
		printf("Sanity: MAC core config = 0x%x\n", regval);
		regval = dwceqos_read(lp, REG_DWCEQOS_MTL_TXQ0_OPER);
		printf("Sanity: MTL TxQ0 mode = 0x%x\n", regval);
		regval = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_TX_CTRL);
		printf("Sanity: DMA chan Tx ctrl = 0x%x\n", regval);
		regval = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_RX_CTRL);
		printf("Sanity: DMA chan Rx ctrl = 0x%x\n", regval);
#endif
		struct dwceqos_dma_desc *dd;
		struct emac_rx_queue* rxq;
		struct dwceqos_dma_desc* temp;

		rxq = &lp->rx_queues[0];

		dd = &rxq->rx_descs[rxq->rx_cur];
		regval = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_TXDESC_LIST);
		if ((((u32)lp->tx_queues[0].tx_descs_addr) != regval) || (regval == 0)) {
			printf("error: tx desc 0x%x doesn't match reg 0x%x\n",
						(u32)lp->tx_queues[0].tx_descs_addr, regval);
		}
		regval = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_RXDESC_LIST);
		if ((((u32)lp->rx_queues[0].rx_descs_addr) != regval) || (regval == 0)) {
			printf("error: rx desc 0x%x doesn't match reg 0x%x\n",
						(u32)lp->rx_queues[0].rx_descs_addr, regval);
		} else {
			temp = (struct dwceqos_dma_desc *)(long)regval;
			if (temp->des0 != dd->des0) {
				printf("error: rx  buffer 0x%x doesn't match reg 0x%x, reg=0x%x\n",
							(u32)dd->des0, temp->des0, regval);
			}
		}
	}

#ifdef EMAC_DEBUG
	dw_DMA_status_check(lp);
#endif
}

void emac_lpmode_config(struct net_local *lp)
{
	u32 reg;

	if (NULL == lp) {
		printf("error: lpmode no device\n");
		return;
	}
	reg = dwceqos_read(lp, REG_DWCEQOS_MAC_CFG);
	if (0 == (reg & DWCEQOS_MAC_CFG_LPM )) {
		dwceqos_write(lp, REG_DWCEQOS_MAC_CFG,
					reg | DWCEQOS_MAC_CFG_LPM);
#ifndef VCS_TEST
		printf("Config device loopback mode from 0x%x\n", reg);
#endif
	}
}

void emac_get_feature(u64 base_addr)
{
	struct net_local emac_dev;
	u32 reg, newreg;

	emac_dev.baseaddr = (void*)IOREMAP(base_addr);
	reg = 0;
	reg = dwceqos_read(&emac_dev, REG_DWCEQOS_MAC_HW_VERSION);
	printf("MAC version = 0x%x\n", reg);

	reg = 0;
	reg = dwceqos_read(&emac_dev, REG_DWCEQOS_MAC_CFG);
	printf("MAC CFG = 0x%x\n", reg);

	/* basic sanity check for this key config register */
	newreg = 0x3;
	dwceqos_write(&emac_dev, REG_DWCEQOS_MAC_CFG, newreg | reg);
	if ((newreg | reg) != dwceqos_read(&emac_dev, REG_DWCEQOS_MAC_CFG)) {
		printf("failed to pass sanity check, contact IC\n");
		return;
	} else {
		dwceqos_write(&emac_dev, REG_DWCEQOS_MAC_CFG, reg);
		printf("passed sanity check for MAC CFG reg\n");
	}

	{ /* sanity check for DMA */
		struct net_local* lp;
		u32 desc_addr = 0x4000;
		lp = &emac_dev;
		newreg = 0;

		dwceqos_reset_hw(lp);
		dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_TXDESC_LEN, DWCEQOS_TX_DCNT - 1);
		reg = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_TXDESC_LEN);
		if (reg != DWCEQOS_TX_DCNT - 1)
			newreg |= 1;

		dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_RXDESC_LEN, DWCEQOS_RX_DCNT - 1);
		reg = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_RXDESC_LEN);
		if (reg != DWCEQOS_TX_DCNT - 1)
			newreg |= (1 << 1);
		dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_TXDESC_LIST, desc_addr);
		reg = dwceqos_read(lp, REG_DWCEQOS_DMA_CH0_TXDESC_LIST);
		if (reg != desc_addr)
			newreg |= (1 << 2);
		dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_RXDESC_LIST, desc_addr);
		if (reg != desc_addr)
			newreg |= (1 << 3);
		dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_TXDESC_TAIL, desc_addr);
		if (reg != desc_addr)
			newreg |= (1 << 4);
		dwceqos_write(lp, REG_DWCEQOS_DMA_CH0_RXDESC_TAIL, desc_addr);
		if (reg != desc_addr)
			newreg |= (1 << 5);

		if (0 != newreg) {
			printf("failed to pass sanity check, errno=%x\n", newreg);
			return;
		}
		printf("passed sanity check for DMA reg, reset HW\n");
		dwceqos_reset_hw(lp);
		printf("reset HW end\n");
	}

	reg = 0;
	reg = dwceqos_read(&emac_dev, REG_DWCEQOS_MAC_HW_VERSION);
	printf("MAC version = 0x%x\n", reg);

	dwceqos_get_hwfeatures(&emac_dev);

	printf("HW features0=0x%x, feature1=0x%x, feature2=0x%x\n",
				emac_dev.feature0,
				emac_dev.feature1,
				emac_dev.feature2);
	/* RX and TX FIFO sizes are encoded as log2(n / 128). Undo that by
	 * shifting and store the sizes in bytes.
	 */
	printf("Tx FIF0 size=%d bytes\n",
				128 << ((emac_dev.feature1 & GENMASK(10, 6)) >> 6));
	printf("Rx FIF0 size=%d bytes\n",
				128 << (emac_dev.feature1 & GENMASK(4, 0)));
	printf("Tx CHAN number=%d\n",
				((emac_dev.feature2 & GENMASK(21, 18)) >> 18) + 1);
	printf("Rx CHAN number=%d\n",
				((emac_dev.feature2 & GENMASK(15, 12)) >> 12) + 1);
	printf("Tx Queues number=%d\n",
				((emac_dev.feature2 & GENMASK(9, 6)) >> 6) + 1);
	printf("Rx Queues number=%d\n",
				((emac_dev.feature2 & GENMASK(3, 0)) >> 0) + 1);

	/* show AVB ability*/
	printf("\nshow AVB ability\n");
	reg = (emac_dev.feature1 & GENMASK(20, 20)) >> 20;
	printf("AV feature is %s\n",
				reg ? "enabled" : "disabled");

	/* show PTP ability*/
	printf("\nshow PTP ability\n");
	reg = (emac_dev.feature0 & GENMASK(26, 25)) >> 25;
	printf("Timestamp system time source is ");
	switch (reg) {
		case 0:
			printf("internal\n");
			break;
		case 1:
			printf("External\n");
			break;
		case 2:
			printf("both\n");
			break;
		default:
			printf("??\n");
			break;
	}
	reg = (emac_dev.feature0 & GENMASK(12, 12)) >> 12;
	printf("1588 timestamp feture is %s\n",
				reg ? "enabled" : "disabled");
	reg = (emac_dev.feature1 & GENMASK(23, 23)) >> 23;
	printf("One step for PTP is %s\n",
				reg ? "enabled" : "disabled");
	reg = (emac_dev.feature1 & GENMASK(11, 11)) >> 11;
	printf("One step timestamp is %s\n\n",
				reg ? "enabled" : "disabled");
	reg = 0;
	reg = dwceqos_read(&emac_dev, REG_DWCEQOS_MTL_OPER);
	printf("MTL OPERATION MODE = 0x%x\n", reg);

	reg = dwceqos_read(&emac_dev, REG_DWCEQOS_MTL_TXQ0_OPER);
	/* 0:256Bytes, 1-->512bytes.....*/
	printf("MTL Q0 Tx ops Mode=0x%x, TQS=%d\n", reg, reg >> 16);

	reg = 0;
	reg = dwceqos_read(&emac_dev, REG_DWCEQOS_DMA_MODE);
	printf("DMA OPERATION MODE = 0x%x\n", reg);
	reg = 0;
	reg = dwceqos_read(&emac_dev, REG_DWCEQOS_DMA_CH0_CTRL);
	printf("DMA CH0 ctrl= 0x%x\n", reg);
	reg = 0;
	reg = dwceqos_read(&emac_dev, REG_DWCEQOS_DMA_CH0_TX_CTRL);
	printf("DMA Tx CH0 = 0x%x\n", reg);

}


static void mac_prog_mtl_tx_algorithms(struct net_local* lp,
							u32 tx_alg)
{
	u32 value = dwceqos_read(lp, MTL_OPERATION_MODE);

	value &= ~MTL_OPERATION_SCHALG_MASK;
	switch (tx_alg) {
	case MTL_TX_ALGORITHM_WRR:
		value |= MTL_OPERATION_SCHALG_WRR;
		break;
	case MTL_TX_ALGORITHM_WFQ:
		value |= MTL_OPERATION_SCHALG_WFQ;
		break;
	case MTL_TX_ALGORITHM_DWRR:
		value |= MTL_OPERATION_SCHALG_DWRR;
		break;
	case MTL_TX_ALGORITHM_SP:
		value |= MTL_OPERATION_SCHALG_SP;
		break;
	default:
		break;
	}
	dwceqos_write(lp, MTL_OPERATION_MODE, value);
}

static void mac_prog_mtl_rx_algorithms(struct net_local* lp,
					  u32 rx_alg)
{
	u32 value = dwceqos_read(lp, MTL_OPERATION_MODE);

	value &= ~MTL_OPERATION_RAA;
	switch (rx_alg) {
	case MTL_RX_ALGORITHM_SP:
		value |= MTL_OPERATION_RAA_SP;
		break;
	case MTL_RX_ALGORITHM_WSP:
		value |= MTL_OPERATION_RAA_WSP;
		break;
	default:
		break;
	}

	dwceqos_write(lp, MTL_OPERATION_MODE, value);
}

static void mac_set_mtl_tx_queue_weight(struct net_local* lp,
					   u32 weight, u32 queue)
{
	u32 value = dwceqos_read(lp, MTL_TXQX_WEIGHT_BASE_ADDR(queue));

	value &= ~MTL_TXQ_WEIGHT_ISCQW_MASK;
	value |= weight & MTL_TXQ_WEIGHT_ISCQW_MASK;
	dwceqos_write(lp, MTL_TXQX_WEIGHT_BASE_ADDR(queue), value);
}

void emac_show_CBS_info(struct net_local* lp, u32 queue)
{
	u32 sendslope, idleslope, hicredit, locredit, absvalue;
	void __iomem *ioaddr = lp->baseaddr;

	sendslope = readl(ioaddr + MTL_SEND_SLP_CREDX_BASE_ADDR(queue));
	idleslope = readl(ioaddr + MTL_TXQX_WEIGHT_BASE_ADDR(queue));
	hicredit  = readl(ioaddr + MTL_HIGH_CREDX_BASE_ADDR(queue));
	locredit  = readl(ioaddr + MTL_LOW_CREDX_BASE_ADDR(queue));
	absvalue  = readl(ioaddr + MTL_ETSX_STATUS_BASE_ADDR(queue));
	/*printf("CBS queue %d: send %d, idle %d, hi %d, lo %d\n",
			queue, sendslope, idleslope,
			hicredit, locredit);*/
	printf("Queue %d Average traffic transmitted is %d\n",
					queue, absvalue);
}

static void dwmac4_qmode(void __iomem *ioaddr, u32 channel, u8 qmode)
{
	u32 mtl_tx_op = readl(ioaddr + MTL_CHAN_TX_OP_MODE(channel));

	mtl_tx_op &= ~MTL_OP_MODE_TXQEN_MASK;
	if (qmode != MTL_QUEUE_AVB)
		mtl_tx_op |= MTL_OP_MODE_TXQEN;
	else
		mtl_tx_op |= MTL_OP_MODE_TXQEN_AV;

	writel(mtl_tx_op, ioaddr +  MTL_CHAN_TX_OP_MODE(channel));
}

static void mac_configure_cbs(struct net_local* lp,
			      u32 send_slope, u32 idle_slope,
			      u32 high_credit, u32 low_credit, u32 queue)
{
	void __iomem *ioaddr = lp->baseaddr;
	u32 value;

#ifndef VCS_TEST
	printf("Queue %d configured as AVB. Parameters:\n", queue);
	printf("\tsend_slope: 0x%08x\n", send_slope);
	printf("\tidle_slope: 0x%08x\n", idle_slope);
	printf("\thigh_credit: 0x%08x\n", high_credit);
	printf("\tlow_credit: 0x%08x\n", low_credit);
#else
	printf("Queue %d as AVB\n", queue);
#endif
	dwmac4_qmode(ioaddr, queue, MTL_QUEUE_AVB);
	/* enable AV algorithm */
	value = readl(ioaddr + MTL_ETSX_CTRL_BASE_ADDR(queue));
	value |= MTL_ETS_CTRL_AVALG;
	value |= MTL_ETS_CTRL_CC;
	writel(value, ioaddr + MTL_ETSX_CTRL_BASE_ADDR(queue));

	/* configure send slope */
	value = readl(ioaddr + MTL_SEND_SLP_CREDX_BASE_ADDR(queue));
	value &= ~MTL_SEND_SLP_CRED_SSC_MASK;
	value |= send_slope & MTL_SEND_SLP_CRED_SSC_MASK;
	writel(value, ioaddr + MTL_SEND_SLP_CREDX_BASE_ADDR(queue));

	/* configure idle slope (same register as tx weight) */
	{
		value = readl(ioaddr + MTL_TXQX_WEIGHT_BASE_ADDR(queue));

		value &= ~MTL_TXQ_WEIGHT_ISCQW_MASK;
		value |= idle_slope & MTL_TXQ_WEIGHT_ISCQW_MASK;
		writel(value, ioaddr + MTL_TXQX_WEIGHT_BASE_ADDR(queue));
	}

	/* configure high credit */
	value = readl(ioaddr + MTL_HIGH_CREDX_BASE_ADDR(queue));
	value &= ~MTL_HIGH_CRED_HC_MASK;
	value |= high_credit & MTL_HIGH_CRED_HC_MASK;
	writel(value, ioaddr + MTL_HIGH_CREDX_BASE_ADDR(queue));

	/* configure low credit */
	value = readl(ioaddr + MTL_LOW_CREDX_BASE_ADDR(queue));
	value &= ~MTL_HIGH_CRED_LC_MASK;
	value |= low_credit & MTL_HIGH_CRED_LC_MASK;
	writel(value, ioaddr + MTL_LOW_CREDX_BASE_ADDR(queue));
	return;
}

static void mac_map_mtl_dma(struct net_local* lp, u32 queue, u32 chan)
{
	u32 value;

	if (queue < 4)
		value = dwceqos_read(lp, MTL_RXQ_DMA_MAP0);
	else
		value = dwceqos_read(lp, MTL_RXQ_DMA_MAP1);

	if (queue == 0 || queue == 4) {
		value &= ~MTL_RXQ_DMA_Q04MDMACH_MASK;
		value |= MTL_RXQ_DMA_Q04MDMACH(chan);
	} else {
		value &= ~MTL_RXQ_DMA_QXMDMACH_MASK(queue);
		value |= MTL_RXQ_DMA_QXMDMACH(chan, queue);
	}

	if (queue < 4) {
		dwceqos_write(lp, MTL_RXQ_DMA_MAP0, value);
	}
	else {
		dwceqos_write(lp, MTL_RXQ_DMA_MAP1, value);
	}
}
static void mac_rx_queue_enable(struct net_local* lp,
				   u8 mode, u32 queue)
{
	u32 value = dwceqos_read(lp, GMAC_RXQ_CTRL0);

	value &= GMAC_RX_QUEUE_CLEAR(queue);
	if (mode == MTL_QUEUE_AVB)
		value |= GMAC_RX_AV_QUEUE_ENABLE(queue);
	else if (mode == MTL_QUEUE_DCB_GENERIC)
		value |= GMAC_RX_DCB_QUEUE_ENABLE(queue);

	dwceqos_write(lp, GMAC_RXQ_CTRL0, value);
}
static void mac_rx_queue_priority(struct net_local* lp,
				     u32 prio, u32 queue)
{
	u32 base_register;
	u32 value;

	base_register = (queue < 4) ? GMAC_RXQ_CTRL2 : GMAC_RXQ_CTRL3;

	value = dwceqos_read(lp, base_register);

	value &= ~GMAC_RXQCTRL_PSRQX_MASK(queue);
	value |= (prio << GMAC_RXQCTRL_PSRQX_SHIFT(queue)) &
						GMAC_RXQCTRL_PSRQX_MASK(queue);
	dwceqos_write(lp, base_register, value);
}
static void mac_tx_queue_priority(struct net_local* lp,
				     u32 prio, u32 queue)
{
	u32 base_register;
	u32 value;

	base_register = (queue < 4) ? GMAC_TXQ_PRTY_MAP0 : GMAC_TXQ_PRTY_MAP1;

	value = dwceqos_read(lp, base_register);

	value &= ~GMAC_TXQCTRL_PSTQX_MASK(queue);
	value |= (prio << GMAC_TXQCTRL_PSTQX_SHIFT(queue)) &
						GMAC_TXQCTRL_PSTQX_MASK(queue);

	dwceqos_write(lp, base_register, value);
}

struct mac_rx_routing {
	u32 reg_mask;
	u32 reg_shift;
};
static void mac_rx_queue_routing(struct net_local* lp,
				    u8 packet, u32 queue)
{
	u32 value;

	static const struct mac_rx_routing route_possibilities[] = {
		{ GMAC_RXQCTRL_AVCPQ_MASK, GMAC_RXQCTRL_AVCPQ_SHIFT },
		{ GMAC_RXQCTRL_PTPQ_MASK, GMAC_RXQCTRL_PTPQ_SHIFT },
		{ GMAC_RXQCTRL_DCBCPQ_MASK, GMAC_RXQCTRL_DCBCPQ_SHIFT },
		{ GMAC_RXQCTRL_UPQ_MASK, GMAC_RXQCTRL_UPQ_SHIFT },
		{ GMAC_RXQCTRL_MCBCQ_MASK, GMAC_RXQCTRL_MCBCQ_SHIFT },
	};

	value = dwceqos_read(lp, GMAC_RXQ_CTRL1);

	/* routing configuration */
	value &= ~route_possibilities[packet - 1].reg_mask;
	value |= (queue << route_possibilities[packet-1].reg_shift) &
		 route_possibilities[packet - 1].reg_mask;

	/* some packets require extra ops */
	if (packet == PACKET_AVCPQ) {
		value &= ~GMAC_RXQCTRL_TACPQE;
		value |= 0x1 << GMAC_RXQCTRL_TACPQE_SHIFT;
	} else if (packet == PACKET_MCBCQ) {
		value &= ~GMAC_RXQCTRL_MCBCQEN;
		value |= 0x1 << GMAC_RXQCTRL_MCBCQEN_SHIFT;
	}

	dwceqos_write(lp, GMAC_RXQ_CTRL1, value);
}
/**
 *  Configure MAC transmit layer(MTL Queue related)
 *  Description: It is used for configurring MTL
 */
void emac_init_hw_mtl(struct net_local* emac_dev,
					struct dwceqos_MTL_cfg* emac_MTL_cfg)
{
	u32 weight, queue;
	u32 rx_queues_count;
	u32 tx_queues_count;
	u32 mode_to_use;

	weight = emac_MTL_cfg->tx_weight;
	rx_queues_count = emac_MTL_cfg->rx_queues_count;
	tx_queues_count = emac_MTL_cfg->tx_queues_count;

	if (tx_queues_count > 1) {
		/* configure tx queue schedule weight*/
		for (queue = 0; queue < tx_queues_count; queue++) {
			weight = emac_MTL_cfg->tx_queues_cfg[queue].weight;
			mac_set_mtl_tx_queue_weight(emac_dev, weight, queue);
		}
	}

	/* Configure MTL RX algorithms */
	if (rx_queues_count > 1) {
		mac_prog_mtl_rx_algorithms(emac_dev,
					emac_MTL_cfg->rx_sched_algorithm);
	}

	/* Configure MTL TX algorithms */
	if (tx_queues_count > 1)
		mac_prog_mtl_tx_algorithms(emac_dev,
					emac_MTL_cfg->tx_sched_algorithm);

	/* Configure CBS in AVB TX queues */
	if (tx_queues_count > 1) {
		for (queue = 0; queue < tx_queues_count; queue++) {
			mode_to_use = emac_MTL_cfg->tx_queues_cfg[queue].mode_to_use;
			if (mode_to_use != MTL_QUEUE_AVB)
				continue;

			mac_configure_cbs(emac_dev,
					emac_MTL_cfg->tx_queues_cfg[queue].send_slope,
					emac_MTL_cfg->tx_queues_cfg[queue].idle_slope,
					emac_MTL_cfg->tx_queues_cfg[queue].high_credit,
					emac_MTL_cfg->tx_queues_cfg[queue].low_credit,
					queue);
		}
	}

	/* Map RX MTL to DMA channels */
	{
		u32 chan;

		for (queue = 0; queue < rx_queues_count; queue++) {
			//chan = emac_MTL_cfg->rx_queues_cfg[queue].chan;
			/* 1:1 mapping for lazy */
			chan = queue;
			mac_map_mtl_dma(emac_dev, queue, chan);
		}
	}

	/* Enable MAC RX Queues */
	{
		u8 mode;

		for (queue = 0; queue < rx_queues_count; queue++) {
			mode = emac_MTL_cfg->rx_queues_cfg[queue].mode_to_use;
			mac_rx_queue_enable(emac_dev, mode, queue);
		}
	}

	/* Set RX priorities */
	if (rx_queues_count > 1) {
		u32 prio;

		for (queue = 0; queue < rx_queues_count; queue++) {
			if (!emac_MTL_cfg->rx_queues_cfg[queue].use_prio)
				continue;

			prio = emac_MTL_cfg->rx_queues_cfg[queue].prio;
			mac_rx_queue_priority(emac_dev, prio, queue);
		}
	}

	/* Set TX priorities */
	if (tx_queues_count > 1) {
		u32 prio;

		for (queue = 0; queue < tx_queues_count; queue++) {
			if (!emac_MTL_cfg->tx_queues_cfg[queue].use_prio)
				continue;

			prio = emac_MTL_cfg->tx_queues_cfg[queue].prio;
			mac_tx_queue_priority(emac_dev, prio, queue);
		}
	}

	/* Set RX routing */
	if (rx_queues_count > 1) {
		u8 packet;

		for (queue = 0; queue < rx_queues_count; queue++) {
			/* no specific packet type routing specified for the queue */
			if (emac_MTL_cfg->rx_queues_cfg[queue].pkt_route == 0x0)
				continue;

			packet = emac_MTL_cfg->rx_queues_cfg[queue].pkt_route;
			mac_rx_queue_routing(emac_dev, packet, queue);
		}
	}
}


/* HW initial sequence
 * 1. DMA engine init
 * 2. MTL config
 * */
struct net_local* emac_init(u64 base_addr)
{
	struct net_local* emac_dev;
	int res;

	emac_dev = emac_heap_alloc(sizeof(*emac_dev));

	if (NULL == emac_dev) {
		printf("failed to allocate emac dev structure\n");
		return NULL;
	}

	memset(emac_dev, 0, sizeof(*emac_dev));
	/* no io remap, suppose physical = virtual*/
	emac_dev->baseaddr = (void*)IOREMAP(base_addr);

	emac_config_bus(&emac_dev->bus_cfg);

	emac_dev->link    = 0;
	emac_dev->speed   = 0;
	emac_dev->duplex  = 0xFF;
	emac_dev->mac_addr[0] = 1;
	emac_dev->mac_addr[1] = 1;
	emac_dev->mac_addr[2] = 2;
	emac_dev->mac_addr[3] = 2;
	emac_dev->mac_addr[4] = 3;
	emac_dev->mac_addr[5] = 3;

	res = dwceqos_descriptor_init(emac_dev,
			MTL_MAX_TX_QUEUES, MTL_MAX_RX_QUEUES);

	if (res) {
		printf("Unable to allocate DMA memory, rc %d\n", res);
        heap_free(emac_dev);
		return NULL;
	}
	dwceqos_get_hwfeatures(emac_dev);
	/* phy_start(lp->phy_dev); */
	//dwceqos_init_hw(emac_dev, emac_MTL_cfg);

    return emac_dev;
}

void emac_test_mode(struct net_local* lp,
					struct dwceqos_MTL_cfg* emac_MTL_cfg)
{
	if (NULL == lp) {
		printf("wrong parameters\n");
		return;
	}

	/* Stop DMA, MTL, MAC first.
	 * should check no transaction before stopping
	 * */
	emac_stop_dma_mtl_mac(lp);
	dwceqos_init_hw(lp, emac_MTL_cfg);
}