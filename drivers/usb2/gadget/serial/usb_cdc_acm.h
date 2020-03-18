/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2006
 * Bryan O'Donoghue, deckard@codehermit.ie, CodeHermit
 */

/* ACM Control Requests */
#define ACM_SEND_ENCAPSULATED_COMMAND	0x00
#define ACM_GET_ENCAPSULATED_RESPONSE	0x01
#define ACM_SET_COMM_FEATURE		0x02
#define ACM_GET_COMM_FEATRUE		0x03
#define ACM_CLEAR_COMM_FEATURE		0x04
#define ACM_SET_LINE_ENCODING		0x20
#define ACM_GET_LINE_ENCODING		0x21
#define ACM_SET_CONTROL_LINE_STATE	0x22
#define ACM_SEND_BREAK			0x23

/* ACM Notification Codes */
#define ACM_NETWORK_CONNECTION		0x00
#define ACM_RESPONSE_AVAILABLE		0x01
#define ACM_SERIAL_STATE		0x20

/* Format of response expected by a ACM_GET_LINE_ENCODING request */
struct rs232_emu{
		unsigned long dter;
		unsigned char stop_bits;
		unsigned char parity;
		unsigned char data_bits;
}__attribute__((packed));

/* Line Coding Structure from CDC spec 6.2.13 */
struct usb_cdc_line_coding {
	__le32	dwDTERate;
	__u8	bCharFormat;
#define USB_CDC_1_STOP_BITS			0
#define USB_CDC_1_5_STOP_BITS			1
#define USB_CDC_2_STOP_BITS			2

	__u8	bParityType;
#define USB_CDC_NO_PARITY			0
#define USB_CDC_ODD_PARITY			1
#define USB_CDC_EVEN_PARITY			2
#define USB_CDC_MARK_PARITY			3
#define USB_CDC_SPACE_PARITY			4

	__u8	bDataBits;
} __attribute__ ((packed));

