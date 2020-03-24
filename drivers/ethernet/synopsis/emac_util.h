/**---------------------------------------------------------------------------
 * @file    emac_util.h
 *
 * @brief    provide basic utilities for emac driver
 *
 * All Rights Reserved.
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Include Files
 *--------------------------------------------------------------------------*/
#ifndef EMAC_UTIL_H
#define EMAC_UTIL_H

#define MAC_IP_UDP (14+20+8)
#define MAC_IP_L4 (14+20)
#define TOTLENGTH 2048

#define ETH_ALEN 6
struct ethhdr {
	unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
	unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
	uint16_t		h_proto;		/* packet type ID field	*/
} __attribute__((packed));

struct iphdr {
	/* Don't care little or big endian, always little */
	uint8_t		ihl_version;
	uint8_t		tos;
	uint16_t	tot_len;
	uint16_t	id;
	uint16_t	frag_off;
	uint8_t		ttl;
	uint8_t		protocol;
	uint16_t	check;
	uint32_t	saddr;
	uint32_t	daddr;
	/*The options start here. */
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

struct ptphdr {
	uint8_t		MsgType:4;
	uint8_t		TranSpec:4;
	uint8_t		VerPTP:4;
	uint8_t		Reserved0:4;
	uint16_t	MsgLength;
	uint8_t		DomainNumber;
	uint8_t		Reserved1;
	uint16_t	FlagField;
	uint64_t	CorrectionField;
	uint32_t	Reserved2;
	uint8_t		srcportID[10];
	uint16_t	SequenceID;
	uint8_t		ControlField;
	uint8_t		LogMsgInterval;
	uint8_t		timestamp[10];
	/*option if have*/
} __attribute__((packed));

void emac_InitPacket(uint8_t *PacketBuf, uint32_t length,
			uint8_t ip, uint8_t tcp, uint8_t badCS);
void emac_InitPTPPacket(uint8_t *pktBuf, uint32_t* length);

int emac_GetMacHdr( void );
int emac_GetIPHdr( void );
int emac_GetUDPHdr( void );
int emac_GetTCPHdr( void );

#endif