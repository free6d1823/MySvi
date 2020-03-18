// SPDX-License-Identifier: GPL-2.0+
/*
 * usb/gadget/config.c -- simplify building config descriptors
 *
 * Copyright (C) 2003 David Brownell
 *
 * Ported to U-Boot by: Thomas Smits <ts.smits@gmail.com> and
 *                      Remy Bohmer <linux@bohmer.net>
 */

#include "../usbport.h"
#include <errno.h>
#include <target/list.h>
#include <string.h>

#include "../ch9.h"
#include "gadget.h"
#include "composite.h"

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
		const struct usb_descriptor_header **src)
{
	u8	*dest = buf;

	if (!src)
		return -EINVAL;

	/* fill buffer from src[] until null descriptor ptr */
	for (; NULL != *src; src++) {
		unsigned		len = (*src)->bLength;

		if (len > buflen)
			return -EINVAL;
		memcpy(dest, *src, len);
		buflen -= len;
		dest += len;
	}
	return dest - (u8 *)buf;
}


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
)
{
	struct usb_config_descriptor		*cp = buf;
	int					len;

	/* config descriptor first */
	if (length < USB_DT_CONFIG_SIZE || !desc)
		return -EINVAL;
	/* config need not be aligned */
	memcpy(cp, config, sizeof(*cp));

	/* then interface/endpoint/class/vendor/... */
	len = usb_descriptor_fillbuf(USB_DT_CONFIG_SIZE + (u8 *)buf,
			length - USB_DT_CONFIG_SIZE, desc);
	if (len < 0)
		return len;
	len += USB_DT_CONFIG_SIZE;
	if (len > 0xffff)
		return -EINVAL;

	/* patch up the config descriptor */
	cp->bLength = USB_DT_CONFIG_SIZE;
	cp->bDescriptorType = USB_DT_CONFIG;
	//?? put_unaligned_le16(len, &cp->wTotalLength);
	cp->bmAttributes |= USB_CONFIG_ATT_ONE;
	return len;
}


struct usb_descriptor_header *usb_otg_descriptor_alloc(
				struct usb_gadget *gadget)
{
	struct usb_descriptor_header *otg_desc;
	unsigned length = 0;

	if (gadget->otg_caps && (gadget->otg_caps->otg_rev >= 0x0200))
	  length = sizeof(struct usb_otg20_descriptor);
	else
		length = sizeof(struct usb_otg_descriptor);
  otg_desc= malloc(length);
	//?? otg_desc = kzalloc(length, GFP_KERNEL);
	return otg_desc;
}


int usb_otg_descriptor_init(struct usb_gadget *gadget,
		struct usb_descriptor_header *otg_desc)
{
	struct usb_otg_descriptor *otg1x_desc;
	struct usb_otg20_descriptor *otg20_desc;
	struct usb_otg_caps *otg_caps = gadget->otg_caps;
	u8 otg_attributes = 0;

	if (!otg_desc)
		return -EINVAL;

	if (otg_caps && otg_caps->otg_rev) {
		if (otg_caps->hnp_support)
			otg_attributes |= USB_OTG_HNP;
		if (otg_caps->srp_support)
			otg_attributes |= USB_OTG_SRP;
		if (otg_caps->adp_support && (otg_caps->otg_rev >= 0x0200))
			otg_attributes |= USB_OTG_ADP;
	} else {
		otg_attributes = USB_OTG_SRP | USB_OTG_HNP;
	}

//	if (otg_caps && (otg_caps->otg_rev >= 0x0200)) {
//		otg20_desc = 0;//(struct usb_otg20_descriptor *)otg_desc;
		//otg20_desc->bLength = 0; //sizeof(struct usb_otg20_descriptor);
//		otg20_desc->bDescriptorType = USB_DT_OTG;
//		otg20_desc->bmAttributes = otg_attributes;
//		otg20_desc->bcdOTG = cpu_to_le16(otg_caps->otg_rev);
//	} else {
//		otg1x_desc = (struct usb_otg_descriptor *)otg_desc;
//		otg1x_desc->bLength = sizeof(struct usb_otg_descriptor);
//		otg1x_desc->bDescriptorType = USB_DT_OTG;
//		otg1x_desc->bmAttributes = otg_attributes;
//	}

	return 0;
}

struct usb_descriptor_header **
usb_copy_descriptors(struct usb_descriptor_header **src)
{
	struct usb_descriptor_header **tmp;
	unsigned bytes;
	unsigned n_desc;
	void *mem;
	struct usb_descriptor_header **ret;

	/* count descriptors and their sizes; then add vector size */
	for (bytes = 0, n_desc = 0, tmp = src; *tmp; tmp++, n_desc++)
		bytes += (*tmp)->bLength;
	bytes += (n_desc + 1) * sizeof(*tmp);

	//mem = kmalloc(bytes, GFP_KERNEL);
	mem = malloc(bytes);
	if (!mem)
		return NULL;

	/* fill in pointers starting at "tmp",
	 * to descriptors copied starting at "mem";
	 * and return "ret"
	 */
	tmp = mem;
	ret = mem;
	mem += (n_desc + 1) * sizeof(*tmp);
	while (*src) {
		memcpy(mem, *src, (*src)->bLength);
		*tmp = mem;
		tmp++;
		mem += (*src)->bLength;
		src++;
	}
	*tmp = NULL;

	return ret;
}




void usb_free_all_descriptors(struct usb_function *f)
{
//	usb_free_descriptors(f->fs_descriptors);
//	usb_free_descriptors(f->hs_descriptors);
//	usb_free_descriptors(f->ss_descriptors);
//	usb_free_descriptors(f->ssp_descriptors);
}





int usb_assign_descriptors(struct usb_function *f,
		struct usb_descriptor_header **fs,
		struct usb_descriptor_header **hs,
		struct usb_descriptor_header **ss,
		struct usb_descriptor_header **ssp)
{
	struct usb_gadget *g = f->config->cdev->gadget;

	if (fs) {
		f->fs_descriptors = usb_copy_descriptors(fs);
		if (!f->fs_descriptors)
			goto err;
	}
	if (hs && gadget_is_dualspeed(g)) {
		f->hs_descriptors = usb_copy_descriptors(hs);
		if (!f->hs_descriptors)
			goto err;
	}
#if 0
	if (ss && gadget_is_superspeed(g)) {
		f->ss_descriptors = usb_copy_descriptors(ss);
		if (!f->ss_descriptors)
			goto err;
	}
	if (ssp && gadget_is_superspeed_plus(g)) {
		f->ssp_descriptors = usb_copy_descriptors(ssp);
		if (!f->ssp_descriptors)
			goto err;
	}
#endif
	return 0;
err:
	usb_free_all_descriptors(f);
	return -ENOMEM;
}


