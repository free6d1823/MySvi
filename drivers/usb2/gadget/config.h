// SPDX-License-Identifier: GPL-2.0+
/*
 * usb/gadget/config.c -- simplify building config descriptors
 *
 * Copyright (C) 2003 David Brownell
 *
 * Ported to U-Boot by: Thomas Smits <ts.smits@gmail.com> and
 *                      Remy Bohmer <linux@bohmer.net>
 */


/**
 * usb_descriptor_fillbuf - fill buffer with descriptors
 * @buf: Buffer to be filled
 * @buflen: Size of buf
 * @src: Array of descriptor pointers, terminated by null pointer.
 *
 * Copies descriptors into the buffer, returning the length or a
 * negative error code if they can't all be copied.  Useful when
 * assembling descriptors for an associated set of interfaces used
 * as part of configuring a composite device; or in other cases where
 * sets of descriptors need to be marshaled.
 */
int
usb_descriptor_fillbuf(void *buf, unsigned buflen,
		const struct usb_descriptor_header **src);


/**
 * usb_gadget_config_buf - builts a complete configuration descriptor
 * @config: Header for the descriptor, including characteristics such
 *	as power requirements and number of interfaces.
 * @desc: Null-terminated vector of pointers to the descriptors (interface,
 *	endpoint, etc) defining all functions in this device configuration.
 * @buf: Buffer for the resulting configuration descriptor.
 * @length: Length of buffer.  If this is not big enough to hold the
 *	entire configuration descriptor, an error code will be returned.
 *
 * This copies descriptors into the response buffer, building a descriptor
 * for that configuration.  It returns the buffer length or a negative
 * status code.  The config.wTotalLength field is set to match the length
 * of the result, but other descriptor fields (including power usage and
 * interface count) must be set by the caller.
 *
 * Gadget drivers could use this when constructing a config descriptor
 * in response to USB_REQ_GET_DESCRIPTOR.  They will need to patch the
 * resulting bDescriptorType value if USB_DT_OTHER_SPEED_CONFIG is needed.
 */
int usb_gadget_config_buf(
	const struct usb_config_descriptor	*config,
	void					*buf,
	unsigned				length,
	const struct usb_descriptor_header	**desc
);


struct usb_descriptor_header *usb_otg_descriptor_alloc(
				struct usb_gadget *gadget);


int usb_otg_descriptor_init(struct usb_gadget *gadget,
		struct usb_descriptor_header *otg_desc);

struct usb_descriptor_header **
usb_copy_descriptors(struct usb_descriptor_header **src);




void usb_free_all_descriptors(struct usb_function *f);





int usb_assign_descriptors(struct usb_function *f,
		struct usb_descriptor_header **fs,
		struct usb_descriptor_header **hs,
		struct usb_descriptor_header **ss,
		struct usb_descriptor_header **ssp);


