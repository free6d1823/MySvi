/**---------------------------------------------------------------------------
 * @file    xgmac_util.h
 *
 * @brief    provide basic utilities for xgmac driver
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#ifndef XGMAC_UTIL_H
#define XGMAC_UTIL_H

//#include <stdio.h>

//#define DATALEN 30
#define MAC_IP_UDP (14+20+8)
#define MAC_IP_L4 (14+20)
#define TOTLENGTH 1600

#define ETH_ALEN 6
struct ethhdr {
	unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
	unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
	uint16_t		h_proto;		/* packet type ID field	*/
} __attribute__((packed));

struct iphdr {
	uint8_t	ihl_version;//Don't care little or big endian??
	uint8_t	tos;
	uint16_t	tot_len;
	uint16_t	id;
	uint16_t	frag_off;
	uint8_t	ttl;
	uint8_t	protocol;
	uint16_t	check;
	uint32_t	saddr;
	uint32_t	daddr;
	/*The options start here. *///
}  __attribute__((packed));

struct tcphdr {
	uint16_t	srcPort;
	uint16_t	dstPort;
	uint32_t	sequNum;
	uint32_t	AckNum;
  /*first 4bits: TCP header length; 6bits: reserve, last 6bits, flag*/
	uint16_t	HdrLenAndFlag;
	uint16_t	windowSize;
	uint16_t	checkSum;
	uint16_t	surgentPointer;
  /*option if have*/
} __attribute__((packed));

struct udphdr {
	uint16_t	source;
	uint16_t	dest;
	uint16_t	len;
	uint16_t	check;
};

// void InitIPPacket(uint8_t *PacketBuf, uint32_t length);
void InitPacket(uint8_t *PacketBuf, uint32_t length, uint8_t ip, uint8_t tcp,
                uint8_t badCS);
void init_macConfig(XGMAC_CFG_t *mac_selfcfg);
int GetMacHdr( void );
int GetIPHdr( void );
int GetUDPHdr( void );
int GetTCPHdr( void );

#endif