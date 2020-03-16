/*
// * Copyright (c) 2016 Qualcomm Technologies, Inc.
// * All Rights Reserved.
// * Confidential and Proprietary - Qualcomm Technologies, Inc.
 * emac_build_frames.h
 *
 *  Created on: Mar 14, 2016
 *      Author: ntelkar
 */

#include "emac_drv.h"

#ifdef EMAC_DEBUG

#ifndef __IMC_EMAC_BUILD_FRAMES_H__
#define __IMC_EMAC_BUILD_FRAMES_H__

/** Maximal waiting time to receive frames, in milliseconds */
#define EMAC_MAX_RX_WAIT_TIME          10000

/** Maximal waiting time to complete frames transmit, in milliseconds */
#define EMAC_MAX_TX_WAIT_TIME           2000

/** Waiting step to TX / RX frames, in milliseconds */
#define EMAC_WAIT_STEP                  1        // Abe changed from 0 to 1

/** CRC32 test pattern repetitions, see IEEE802.3 section 3 paragraph 36A.5 */
#define EMAC_CRC32_TEST_PAT_REP         29

/** Length of EtherType field in Ethernet frame, in bytes */
#define EMAC_ETHER_TYPE_LENGTH          2

/** Max TCP checksum pseudo header size */
#define EMAC_PSD_HEADER_SIZE            40

/** Key buffers size (in bytes) for RSS hash function */
#define EMAC_RSS_HASH_KEY_LEN           40

/**
 * Internet protocols lengths
 */
/* IPv4 header length (without Options fields), in 32-bit words */
#define EMAC_MIN_IPV4_HEADER_WORDS      5

/** IPv4 header length, in bytes */
#define EMAC_IPV4_HEADER_LENGTH         (4 * EMAC_MIN_IPV4_HEADER_WORDS)

/** IPv6 header length, in bytes */
#define EMAC_IPV6_HEADER_LENGTH         40

/** TCP header length, in bytes */
#define EMAC_TCP_HEADER_LENGTH          20

/** UDP header length, in bytes */
#define EMAC_UDP_HEADER_LENGTH          8

/** Checksum offset in IPv4 header, in bytes */
#define EMAC_IPV4_CHECKSUM_OFFSET       10

/** Checksum offset in IPv6 header, in bytes */
#define EMAC_IPV6_CHECKSUM_OFFSET       16

/** Checksum offset in TCP header, in bytes */
#define EMAC_TCP_CHECKSUM_OFFSET        16

/** Checksum offset in UDP header, in bytes */
#define EMAC_UDP_CHECKSUM_OFFSET        6

/** Protocol offset in IPv4 header, in bytes */
#define EMAC_IPV4_PROTOCOL_OFFSET       9

/** Protocol length in IPv4 header, in bytes */
#define EMAC_IPV4_LENGTH_OFFSET         2

/** Protocol offset in IPv6 header, in bytes */
#define EMAC_IPV6_PROTOCOL_OFFSET       6

/** Length offset in IPv6 header, in bytes */
#define EMAC_IPV6_LENGTH_OFFSET         4

/** Destination address offset in IPv4 header, in bytes */
#define EMAC_IPV4_DST_OFFSET            16

/** Destination address offset in IPv6 header, in bytes */
#define EMAC_IPV6_DST_OFFSET            24

/** Layer 4 header offset, in IPv4 frame, in bytes */
#define EMAC_IPV4_L4_HEADER_OFFSET      (EMAC_ETHER_HEADER_LENGTH + EMAC_IPV4_HEADER_LENGTH)

/** Layer 4 header offset, in IPv6 frame, in bytes */
#define EMAC_IPV6_L4_HEADER_OFFSET      (EMAC_ETHER_HEADER_LENGTH + EMAC_IPV6_HEADER_LENGTH)

/**
 * Internet protocols codes
 */
/** IPv4 Header Version field */
#define EMAC_IPV4_HEADER_VERSION        4

/** IPv6 Header Version field */
#define EMAC_IPV6_HEADER_VERSION        6

/** Ether Type value for IPv4 */
#define EMAC_IPV4_ETHER_TYPE            0x0800

/** Ether Type value for IPv6 */
#define EMAC_IPV6_ETHER_TYPE            0x86DD

/** TCP protocol code written in IP header */
#define EMAC_TCP_PROTOCOL_CODE          6

/** UDP protocol code written in IP header */
#define EMAC_UDP_PROTOCOL_CODE          17

/** Time to live (IPv4 header field), in seconds */
#define EMAC_IPV4_HEADER_TTL            5

/** IPv4 address length, in bytes */
#define EMAC_IPV4_ADDR_LEN          4

/** IPv6 address length, in bytes */
#define EMAC_IPV6_ADDR_LEN          16

/** Source address offset in IPv4 header, in bytes */
#define EMAC_IPV4_SRC_OFFSET        12

/** Source address offset in IPv6 header, in bytes */
#define EMAC_IPV6_SRC_OFFSET        8

/** TCP port length, in bytes */
#define EMAC_TCP_PORT_LEN           2

/** Total Ethernet header length, in bytes */
#define EMAC_ETHER_HEADER_LENGTH    14

/** CRC length, in bytes */
#define EMAC_CRC_LENGTH             4

/** Minimal Ethernet frame payload length, in bytes*/
#define EMAC_MIN_DATA_LEN           46

/** Minimal Ethernet frame length (not including CRC32 bytes) */
#define EMAC_MIN_FRAME_LENGTH       60

/** Lengths of Ethernet frame fields, in bytes */
#define EMAC_MAC_ADDR_LEN               6

/**
 **  Definitions for frame protocols
 */
#define EMAC_MASK_L2    0x000000FF  /**< Mask for layer 2 protocols */
#define EMAC_L2_NONE    0x00000000  /**< No layer 2 protocol */
#define EMAC_L2_E2      0x00000001  /**< Layer 2 Ethernet protocol */

#define EMAC_MASK_L3    0x0000FF00  /**< Mask for layer 3 protocols */
#define EMAC_L3_NONE    0x00000000  /**< No layer 3 protocol */
#define EMAC_L3_IP4     0x00000100  /**< Layer 3 IPv4 protocol */
#define EMAC_L3_IP6     0x00000200  /**< Layer 3 IPv6 protocol */

#define EMAC_MASK_L4    0x00FF0000  /**< Mask for layer 4 protocols */
#define EMAC_L4_NONE    0x00000000  /**< No layer 4 protocol */
#define EMAC_L4_TCP     0x00010000  /**< Layer 4 TCP protocol */
#define EMAC_L4_UDP     0x00020000  /**< Layer 4 UDP protocol */

#define EMAC_MASK_L5    0xFF000000  /**< Mask for layer 5 protocols */
#define EMAC_L5_NONE    0x00000000  /**< No layer 5 protocol */

/**
 **  Definitions for frame types
 */

#define EMAC_PROTO_RAW_ETH (EMAC_L2_E2)                   /**< Raw Ethernet */
#define EMAC_PROTO_IP4     (EMAC_L2_E2 | EMAC_L3_IP4)     /**< IPv4 */
#define EMAC_PROTO_IP6     (EMAC_L2_E2 | EMAC_L3_IP6)     /**< IPv6 */
#define EMAC_PROTO_TCP4    (EMAC_PROTO_IP4 | EMAC_L4_TCP) /**< TCP over IPv4 */
#define EMAC_PROTO_UDP4    (EMAC_PROTO_IP4 | EMAC_L4_UDP) /**< UDP over IPv4 */
#define EMAC_PROTO_TCP6    (EMAC_PROTO_IP6 | EMAC_L4_TCP) /**< TCP over IPv6 */
#define EMAC_PROTO_UDP6    (EMAC_PROTO_IP6 | EMAC_L4_UDP) /**< UDP over IPv6 */

/** IPV4 address */
typedef uint8 EMAC_IPV4_ADDR[EMAC_IPV4_ADDR_LEN];

/** IPV6 address */
typedef uint8 EMAC_IPV6_ADDR[EMAC_IPV6_ADDR_LEN];

/** L3 Packet Parameters */
typedef struct EMAC_PACKET_L3_CFG_STRUCT
{
    const EMAC_IPV4_ADDR    *srcIPv4; /**< IPv4 source address */
    const EMAC_IPV4_ADDR    *dstIPv4; /**< IPv4 destination address */
    const EMAC_IPV6_ADDR    *srcIPv6; /**< IPv6 source address */
    const EMAC_IPV6_ADDR    *dstIPv6; /**< IPv6 destination address */
} EMAC_PACKET_L3_CFG;

/** L4 Packet Parameters */
typedef struct EMAC_PACKET_L4_CFG_STRUCT
{
    uint16                   srcPort; /**< Layer 4 source port */
    uint16                   dstPort; /**< Layer 4 destination port */
} EMAC_PACKET_L4_CFG;

/** L2 Frame Parameters */
typedef struct EMAC_FRAME_CFG_STRUCT
{
    /* Packet Prototype */
    uint32                   type;    /**< Frame type */

    /* L2 Parameters */
    EMAC_ADDR   *addrDst; /**< MAC destination address */
    EMAC_ADDR   *addrSrc; /**< MAC source address */
    uint32                   sVlan;   /**< Add VLAN outer tag*/
    uint32                   cVlan;   /**< Add VLAN inner tag*/
    uint16                   dataLen; /**< Ethernet payload length */
    boolean                  addFcs;  /**< Add FCS at end of frame */

    /* L3 Parameters */
    EMAC_PACKET_L3_CFG       cfgL3;   /**< Layer 3 definitions */

    /* L4 Parameters */
    EMAC_PACKET_L4_CFG       cfgL4;   /**< Layer 4 definitions */

} EMAC_FRAME_CFG;

/**
 * TX statistics struct
 */
typedef struct EMAC_TX_STATS_STRUCT
{
    /** Number of good packet transmitted */
    uint32 txStatsPkts;

    /** Byte count of broadcast packet transmitted, excluding FCS */
    uint32 txStatsBroadcastPkts;

    /** Byte count of multicast packet transmitted, excluding FCS */
    uint32 txStatsMulticastPkts;

    /** Number of Pause packet transmitted */
    uint32 txStatsPausePkts;

    /** Number of packets transmitted successfully with a single prior
     *  collision
     */
    uint32 txStatsSingleCol;

    /** Number of packets transmitted successfully with multiple prior
     *  collisions
     */
    uint32 txStatsMulCol;

    /** Number of packets transmitted with late collisions */
    uint32 txStatsLateCol;

    /** Number of transmit packets aborted due to excessive collisions */
    uint32 txStatsAbortCol;

    /** Number of total collisions */
    uint32 txStatsTotalCol;

    /** Number of bytes of data transmitted, FCS is NOT included */
    uint32 txStatsOctets;

    /** Number of good and bad packets transmitted that are 64 byte long */
    uint32 txStatsPkts64Octets;

    /** Number of good and bad packets transmitted that are between
     *  65 and 127 byte long
     */
    uint32 txStatsPkts65to127Octets;

    /** Number of good and bad packets transmitted that are between
     *  128 and 255 byte long
     */
    uint32 txStatsPkts128to255Octets;

    /** Number of good and bad packets transmitted that are between
     *  256 and 511 byte long
     */
    uint32 txStatsPkts256to511Octets;

    /** Number of good and bad packets transmitted that are between
     *  512 and 1023 byte long
     */
    uint32 txStatsPkts512to1023Octets;

    /** Number of good and bad packets transmitted that are between
     *  1024 and 1518 byte long
     */
    uint32 txStatsPkts1024to1518Octets;

    /** Number of good and bad packets transmitted that are between
     *  1519 byte and MTU
     */
    uint32 txStatsPkts1519toMtuOctets;

    /** Number of transmit packets with length field that does not match the
     *  actual frame size
     */
    uint32 txStatsPktsLengthErr;

    /** Number of transmit packets truncated due to size exceeding MTU */
    uint32 txStatsPktsTruncErr;

    /** Byte count of broadcast packet transmitted, excluding FCS */
    uint32 txStatsPktsBroadcastOctets;

    /** Byte count of multicast packet transmitted, excluding FCS */
    uint32 txStatsPktsMulticastOctets;
} EMAC_TX_STATS;

/**
 * @brief       Build an Ethernet frame
 *
 * @param[out]  buffer          Buffer for frame data
 * @param[in]   sizeBuffer      Available packet buffer size
 * @param[in]   packetConfig    Packet configuration parameters
 *
 * @return      Zero if failed, else the frame length, in bytes
 */
uint32 Emac_buildFrame
(
    uint8                *buffer,
    uint32                sizeBuffer,
    const EMAC_FRAME_CFG *packetConfig
);

/**
 * @brief       Build an Ethernet frame
 *
 * @param[out]  buffer          Buffer for frame data
 * @param[in]   sizeBuffer      Available packet buffer size
 * @param[in]   packetConfig    Packet configuration parameters
 *
 * @return      Zero if failed, else the frame length, in bytes
 */
uint32 Emac_buildFrame_test
(
    uint8                *buffer,
    uint32                sizeBuffer,
    const EMAC_FRAME_CFG *packetConfig,
	uint8				  count
);

#endif

#endif /* __IMC_EMAC_BUILD_FRAMES_H__ */
