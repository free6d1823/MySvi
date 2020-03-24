
/**---------------------------------------------------------------------------
 * @file    emac_test.c
 *
 * @brief    test cases fro emac driver
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <target/cmdline.h>
#include <errno.h>
#include <target/heap.h>
#include <target/utils.h>
#include <target/list.h>
#include <target/delay.h>
#include <target/spinlock.h>

#include "emac_drv.h"
#include "emac_util.h"

#define SENDLEN 1024
#define PKTTOTAL  2048
LIST_HEAD(emac_devs);
/**
 * @brief       simple function to send/recv one buf
 *
 * @param[in]      sendBuf   buffer needs to send out
 * @param[in\out]  length   [in]length for sendbuf, [out]recv length
 *
 * Limitation: Only one buffer is supported
 */
bool emac_simSendRecv(struct net_local* lp, uint8_t queue,
                        char* sendBuf, uint32_t sendLen, bool ptp)
{
	bool tx_ret, success;
	char* recvBuf;
	int i, tx_q, rx_q;
	uint32_t length;

	tx_ret = true;
	success = false;
#ifdef EMAC_DEBUG
	printf("*****status befor Tx*****\n");
	dwceqos_show_status(lp);
	printf("\n\n");
#endif

	tx_q = queue;
	rx_q = 0;


	tx_ret = dwceqos_xmit(lp, tx_q, (char*)sendBuf, sendLen, ptp);
	if (!tx_ret) {
		printf("%s: tx failed\n", __func__);
		return false;
	}

	/* Sleep for while let Tx complete*/
	udelay(1000);
	length = 0;
	/* check the tx/rx status to make sure tx/rx is done */
	//checkcode_miss()
#ifdef EMAC_DEBUG
	printf("*****status after Tx, before Recv*****\n");
	dwceqos_show_status(lp);
	printf("\n");
	printf("Transmit is done, check Receive\n");
#endif
	for (i = 0; i < 4; i++) {
		udelay(1000);
		length = 0;
		tx_ret = dwceqos_rx(lp, 1, i, (char **)&recvBuf, &length);
		/* 4 bytes crc received, so maybe plus 4 will be great
		 * length == (sendLen + 4)
		 */
		if (tx_ret && (0 != length)) {
			success = true;
			printf("%s: %d bytes received at queue %d\n",
						__func__, length, i);
			printf("Pkg Data:");
			if (length > 64)
				length = 64;
			for (i = 0; i < length; i++) {
				if (i % 8 == 0) {
					printf(" ");
				}
				if (i % 16 == 0) {
					printf("\r\n");
				}

				printf("%02x ", recvBuf[i]);
			}
			printf("\r\n-----------------------------------\r\n");
		}
	}
	if (success)
		printf("emac send/receive data path test success\n");
	else
		printf("failed: no buffer received\n");
#ifdef EMAC_DEBUG
	printf("*****status after Recv*****\n");
	dwceqos_get_stats64(lp, 3);
	dwceqos_show_status(lp);
	printf("*****status end*****\n");
#endif

	return tx_ret;
}

/* case 1: multi-channel-queues test */
void emac_mqc_test(struct net_local* emac_dev,
					char* sendBuf, 	u32 sendlen)
{
	struct dwceqos_MTL_cfg emac_MTL_cfg;

	/* stub configuration, need to configure new value based on test cases*/
	memset(&emac_MTL_cfg, 0 , sizeof(struct dwceqos_MTL_cfg));
	emac_MTL_cfg.rx_queues_count = 4;
	emac_MTL_cfg.tx_queues_count = 4;
	/* strict priority for tx rx */
	emac_MTL_cfg.tx_sched_algorithm = MTL_TX_ALGORITHM_SP;
	emac_MTL_cfg.rx_sched_algorithm = MTL_RX_ALGORITHM_SP;
	/* broad cast data should route to queue 1 */
	emac_MTL_cfg.rx_queues_cfg[1].pkt_route = PACKET_MCBCQ;
	emac_MTL_cfg.rx_queues_cfg[2].pkt_route = PACKET_UPQ;
	/* enable specific test mode*/
	emac_test_mode(emac_dev, &emac_MTL_cfg);

	emac_lpmode_config(emac_dev);

	/**
	 * Param: 1.buf,2.total length, 3. isIP
	 * 4. isTCP, or UDP 5. bad checksum
	 */
	emac_InitPacket((u8*)sendBuf, sendlen, 1, 1, 0);
	if (emac_simSendRecv(emac_dev, 0, sendBuf, sendlen, false))
		printf("MQC test passed\n");
	else
	{
		printf("MQC test failed\n");
	}

	dwceqos_tx_reclaim(emac_dev, 0);
}

/* case 1: multi-channel-queues test */
void emac_PTP_test(struct net_local* emac_dev,
					char* sendBuf, 	u32 sendlen)
{
	struct dwceqos_MTL_cfg emac_MTL_cfg;
	u64 tx_ts, rx_ts;
	u32 length = sendlen;

	/* stub configuration, need to configure new value based on test cases*/
	memset(&emac_MTL_cfg, 0 , sizeof(struct dwceqos_MTL_cfg));
	emac_MTL_cfg.rx_queues_count = 4;
	emac_MTL_cfg.tx_queues_count = 4;
	/* strict priority for tx rx */
	emac_MTL_cfg.init_ptp = true;
	/* enable specific test mode*/
	emac_test_mode(emac_dev, &emac_MTL_cfg);

	emac_lpmode_config(emac_dev);

	emac_InitPTPPacket((u8*)sendBuf, &length);
	printf("send out %d bytes PTP over ethernet packet\n", length);
	if (emac_simSendRecv(emac_dev, 0, sendBuf, length, true))
		printf("PTP test passed\n");
	else
	{
		printf("PTP test failed\n");
	}

	/* check tx/rx desc timestamp value */
	emac_get_tx_ts(emac_dev, 0, &tx_ts);
	emac_get_rx_ts(emac_dev, 0, &rx_ts);
	printf("tx ts=0x%llx, rx ts=0x%llx\n", tx_ts, rx_ts);
	dwceqos_tx_reclaim(emac_dev, 0);
}

void emac_basic_test(struct net_local* emac_dev)
{

	char *sendBuf;
	u32 sendlen;



	//sendBuf = (char *)heap_alloc(PKTTOTAL);
	sendBuf = (char*)emac_heap_aligned_alloc(1024, PKTTOTAL);
	sendlen =  SENDLEN;

	if (NULL == sendBuf) {
		printf("err: no room for sending\n");
		return;
	}
//case 1:
	emac_mqc_test(emac_dev, sendBuf, sendlen);

	udelay(5000);
//case 2: PTP one-step test
	memset(sendBuf, 0, PKTTOTAL);
	emac_PTP_test(emac_dev, sendBuf, sendlen);

	heap_free(sendBuf);
}

static struct net_local* emac_basic_init(
		uint64_t emac_base, uint64_t buf_addr, uint32_t buf_size)
{
	struct net_local* emac_dev;

	u8 *sendBuf, *recvBuf;

	if (!emac_base || !buf_addr || !buf_size) {
		printf("err: wrong emac base address\n");
		return NULL;
	}
	emac_init_memory(buf_addr, buf_size);
	emac_dev = emac_init(emac_base);

	if (NULL == emac_dev) {
		printf("failed to allocate emac dev structure\n");
		return NULL;
	}

	list_add_tail(&emac_dev->emac_list_entry, &emac_devs);

	return emac_dev;
}

static void emac_close(struct net_local* emac_dev)
{
	if (NULL == emac_dev) {
		printf("failed to free emac dev structure\n");
		return;
	}

	list_del(&emac_dev->emac_list_entry);

	//stub func for free emac dev buffer
}

#ifndef EMAC_BASE
#define EMAC_BASE 0 /* stub value, update future */
#endif

static int do_emac_test(int argc, char *argv[])
{
	uint64_t emac_base, buf_addr;
	struct net_local* emac_dev, *tmp_emac;
	bool init, test, close;
	uint32_t buf_size;

	init = test = close = false;
	emac_dev = NULL;
	tmp_emac = NULL;

	if (!strcmp(argv[1], "init")) {
		if (!strcmp(argv[2], "default"))
			emac_base = EMAC_BASE;
		else
			emac_base = strtoull(argv[2], 0, 0);
		if ( argc != 5 )
			return -EUSAGE;
		init = true;

		if (!strcmp(argv[3], "default"))
			buf_addr = 0x70000000;
		else
			buf_addr = strtoull(argv[3], 0, 0);
		if (!strcmp(argv[4], "default"))
			buf_size = 0x10000000;
		else
			buf_size = strtoull(argv[4], 0, 0);
		printf("init emac addr 0x%08llx\n", emac_base);
		printf("emac will use ram buffer 0x%08llx with size %d\n",
					buf_addr, buf_size);
	} else if (!strcmp(argv[1], "close")) {
		if (!strcmp(argv[2], "default"))
			emac_base = EMAC_BASE;
		else {
			emac_base = strtoull(argv[2], 0, 0);
		}

		close = true;
		printf("init emac addr 0x%08llx\n", emac_base);
	} else if (!strcmp(argv[1], "test")) {
		if (!strcmp(argv[2], "default"))
			emac_base = EMAC_BASE;
		else {
			emac_base = strtoull(argv[2], 0, 0);
		}
		test = true;
		printf("test emac addr 0x%08llx\n", emac_base);
	} else if (!strcmp(argv[1], "feature")) {
		if (!strcmp(argv[2], "default"))
			emac_base = EMAC_BASE;
		else {
			emac_base = strtoull(argv[2], 0, 0);
		}

		printf("get basic HW feature emac addr 0x%08llx\n",
					emac_base);
		emac_get_feature(emac_base);
	} else {
		printf("wrong command\n");
	}

	list_for_each_entry(struct net_local, tmp_emac,
		&emac_devs, emac_list_entry) {
		if ((u64)tmp_emac->baseaddr == emac_base) {
			emac_dev = tmp_emac;
			break;
		}
	}

	if (init) {
		if (!emac_dev)
			emac_dev = emac_basic_init(emac_base, buf_addr, buf_size);
		return 1;
	} else if (close) {
		emac_close(emac_dev);
		return 1;
	}
	if (test)
		emac_basic_test(emac_dev);
	return 1;
}

MK_CMD(emac, do_emac_test, "emac basic test",
	"emac init <emac_addr> <buf_addr> <buf_size>\n"
	"    - init emac hardware device\n"
	"    	buf_addr: ram buffer used by emac DMA\n"
	"    	buf_size: ram buffer size\n"
	"emac feature <emac_addr>\n"
	"    - get the basic emac hardware capability\n"
	"emac test <emac_addr>\n"
	"    - test emac device basic send/receive feature\n"
	"emac close <emac_addr>\n"
	"    - close emac hardware device\n"
);