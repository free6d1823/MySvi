/* SPDX-License-Identifier: GPL-2.0+ */
/* include/linux/usb/otg.h
 *
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com
 *
 * USB OTG (On The Go) defines
 */

#ifndef __LINUX_USB_OTG_H
#define __LINUX_USB_OTG_H

enum usb_dr_mode {
	USB_DR_MODE_UNKNOWN,
	USB_DR_MODE_HOST,
	USB_DR_MODE_PERIPHERAL,
	USB_DR_MODE_OTG,
};


/**
 * struct usb_otg_caps - describes the otg capabilities of the device
 * @otg_rev: The OTG revision number the device is compliant with, it's
 *		in binary-coded decimal (i.e. 2.0 is 0200H).
 * @hnp_support: Indicates if the device supports HNP.
 * @srp_support: Indicates if the device supports SRP.
 * @adp_support: Indicates if the device supports ADP.
 */
struct usb_otg_caps {
	u16 otg_rev;
	bool hnp_support;
	bool srp_support;
	bool adp_support;
};


/**
 * usb_get_dr_mode() - Get dual role mode for given device
 * @node: Node offset to the given device
 *
 * The function gets phy interface string from property 'dr_mode',
 * and returns the correspondig enum usb_dr_mode
 */
enum usb_dr_mode usb_get_dr_mode(int node);

/**
 * usb_get_maximum_speed() - Get maximum speed for given device
 * @node: Node offset to the given device
 *
 * The function gets phy interface string from property 'maximum-speed',
 * and returns the correspondig enum usb_device_speed
 */
enum usb_device_speed usb_get_maximum_speed(int node);

#endif /* __LINUX_USB_OTG_H */
