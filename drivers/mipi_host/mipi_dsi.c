#include <stdbool.h>
#include <string.h>
#include <target/utils.h>
#include <target/mipi_dsi.h>
#include <target/mipi_display.h>

/**
 * mipi_dsi_packet_format_is_short - check if a packet is of the short format
 * @type: MIPI DSI data type of the packet
 *
 * Return: true if the packet for the given data type is a short packet, false
 * otherwise.
 */
bool mipi_dsi_packet_format_is_short(u8 type)
{
	switch (type) {
	case MIPI_DSI_V_SYNC_START:
	case MIPI_DSI_V_SYNC_END:
	case MIPI_DSI_H_SYNC_START:
	case MIPI_DSI_H_SYNC_END:
	case MIPI_DSI_END_OF_TRANSMISSION:
	case MIPI_DSI_COLOR_MODE_OFF:
	case MIPI_DSI_COLOR_MODE_ON:
	case MIPI_DSI_SHUTDOWN_PERIPHERAL:
	case MIPI_DSI_TURN_ON_PERIPHERAL:
	case MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
	case MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
	case MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM:
	case MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM:
	case MIPI_DSI_DCS_SHORT_WRITE:
	case MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	case MIPI_DSI_DCS_READ:
	case MIPI_DSI_DCS_COMPRESSION_MODE:
	case MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE:
		return true;
	}

	return false;
}

/**
 * mipi_dsi_packet_format_is_long - check if a packet is of the long format
 * @type: MIPI DSI data type of the packet
 *
 * Return: true if the packet for the given data type is a long packet, false
 * otherwise.
 */
bool mipi_dsi_packet_format_is_long(u8 type)
{
	switch (type) {
	case MIPI_DSI_PPS_LONG_WRITE:
	case MIPI_DSI_NULL_PACKET:
	case MIPI_DSI_BLANKING_PACKET:
	case MIPI_DSI_GENERIC_LONG_WRITE:
	case MIPI_DSI_DCS_LONG_WRITE:
	case MIPI_DSI_LOOSELY_PACKED_PIXEL_STREAM_YCBCR20:
	case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR24:
	case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR16:
	case MIPI_DSI_PACKED_PIXEL_STREAM_30:
	case MIPI_DSI_PACKED_PIXEL_STREAM_36:
	case MIPI_DSI_PACKED_PIXEL_STREAM_YCBCR12:
	case MIPI_DSI_PACKED_PIXEL_STREAM_16:
	case MIPI_DSI_PACKED_PIXEL_STREAM_18:
	case MIPI_DSI_PIXEL_STREAM_3BYTE_18:
	case MIPI_DSI_PACKED_PIXEL_STREAM_24:
		return true;
	}

	return false;
}

/**
 * mipi_dsi_create_packet - create a packet from a message according to the
 *     DSI protocol
 * @packet: pointer to a DSI packet structure
 * @msg: message to translate into a packet
 *
 * Return: 0 on success or a negative error code on failure.
 */
int mipi_dsi_create_packet(struct mipi_dsi_packet *packet,
			   const struct mipi_dsi_msg *msg)
{
	if (!packet || !msg)
		return -1;

	/* do some minimum sanity checking */
	if (!mipi_dsi_packet_format_is_short(msg->type) &&
	    !mipi_dsi_packet_format_is_long(msg->type))
		return -1;

	if (msg->channel > 3)
		return -1;

	memset(packet, 0, sizeof(*packet));
	packet->header[0] = ((msg->channel & 0x3) << 6) | (msg->type & 0x3f);

	/* TODO: compute ECC if hardware support is not available */

	/*
	 * Long write packets contain the word count in header bytes 1 and 2.
	 * The payload follows the header and is word count bytes long.
	 *
	 * Short write packets encode up to two parameters in header bytes 1
	 * and 2.
	 */
	if (mipi_dsi_packet_format_is_long(msg->type)) {
		packet->header[1] = (msg->tx_len >> 0) & 0xff;
		packet->header[2] = (msg->tx_len >> 8) & 0xff;

		packet->payload_length = msg->tx_len;
		packet->payload = msg->tx_buf;
	} else {
		const u8 *tx = msg->tx_buf;

		packet->header[1] = (msg->tx_len > 0) ? tx[0] : 0;
		packet->header[2] = (msg->tx_len > 1) ? tx[1] : 0;
	}

	packet->size = sizeof(packet->header) + packet->payload_length;

	return 0;
}