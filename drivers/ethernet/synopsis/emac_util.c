/**---------------------------------------------------------------------------
 * @file    emac_util.c
 *
 * @brief    provide basic utilities for ethernet mac driver
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <target/utils.h>

#include "emac_util.h"

static uint8_t MACFrame[] =
{
	0xff,0xff,0xff,0xff,0xff,0xff, /* broadcast address */
	0x5c,0x52,0x82,0x4a,0x46,0x3f, /* source address */
	// 0x08,0x06, /* ARP diagram type 0x8086 */
	// 0x00,0x01, /* hardware type: ethernet 0x0001 */
	// 0x08,0x00, /* Protocol Type: IP layer 0x0800 */
	// 0x06,      /* Hardware size: 6 */
	// 0x04,      /* Protocol size: 4 */
	// 0x00,0x01, /* opcode: arp request 0x0001 */
	// 0x5c,0x52,0x82,0x4a,0x46,0x3f, /* Sender MAC address */
	// 0x00,0x00,0x00,0x00,           /*Sender IP address */
	// 0x00,0x00,0x00,0x00,0x00,0x00, /* Target MAC address */
	// 0x08,0x08,0x08,0x08            /* Target IP address */
};

static int testindex;

int emac_GetMacHdr( void )
{
	return sizeof(struct ethhdr); //no VLAN currently
}

int emac_GetIPHdr( void )
{
	return sizeof(struct iphdr); //no options currently
}

int emac_GetUDPHdr( void )
{
	return sizeof(struct udphdr); //no options currently
}

int emac_GetTCPHdr( void )
{
	return sizeof(struct tcphdr); //no options currently
}

void emac_InitPacket(uint8_t *pktBuf, uint32_t length, uint8_t ip,
                  uint8_t tcp, uint8_t badCS)
{
	uint8_t* buf;
	uint16_t* mac_type;
	uint16_t i;
	struct iphdr iph;
	struct udphdr udph;
	struct tcphdr tcph;

	if ((length > TOTLENGTH) || (NULL == pktBuf))
		return;

	/*Update MAC layer*/
	buf = pktBuf;
	memset((void*)buf, 0 , length);
	memcpy(buf, MACFrame, ETH_ALEN*2);
	buf += ETH_ALEN*2;

	mac_type = (uint16_t *)buf;
	if(1 == ip)
		*mac_type = 0x0800; //Fixed IP type ethernet IPv4
	else
		*mac_type = 0x86dd; //Fixed IP type IPv6

	buf += sizeof(uint16_t);

	/*Update IP layer*/
	if (1 == ip) {
		/* IPv4 layer */
		iph.ihl_version = (4<<4) | 5;
		iph.tos = 0;
		/* (IP header = 20, UDP Header = 8, TCP header= 20) */
		iph.tot_len = 20 + length;
		iph.id = 0;       //identifier
		iph.frag_off = 0; //no fragment
		iph.ttl = 32;

		if (0 == tcp)
			iph.protocol = 17; //UDP=17, TCP=6??
		if (1 == tcp)
			iph.protocol = 6; //UDP=17, TCP=6??

		iph.saddr = 0x12345678;
		iph.daddr = 0x11223344;
		/* how check sum works */
		memcpy(buf,&iph,20);
		buf += 20;
		} else {
		/* ipv6 layer */
		iph.ihl_version = 6;
	}

	if (1 == tcp) {
		memset(&tcph, 0, sizeof(tcph));
		tcph.srcPort = 80;
		tcph.dstPort = 80;
		tcph.HdrLenAndFlag = 5; /* 5 mean 5*4=20bytes */
		tcph.checkSum = 0;
		if (badCS)
			tcph.checkSum = 0x1122;
		memcpy(buf,&tcph,20);
		buf += 20;
	} else {
		/* udp layer */
		udph.source = 80;
		udph.dest = 80;
		udph.len = length - 8;
		if (badCS)
			udph.check = 0x1122;
		memcpy(buf, &udph, 20);
		buf += 8;
	}

	for (i=0; i<10; i++) {
		buf[i] = i;
	}

	buf += (length - 10);
	testindex++; /* Keep special flag here to recognize new receive buff */
	for (i=0; i<10; i++) {
		buf[i] = testindex;
	}
}