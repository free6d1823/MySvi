// SPDX-License-Identifier: GPL-2.0+
/*
 * serial.c -- USB gadget serial driver
 *
 * Copyright (C) 2003 Al Borchers (alborchers@steinerpoint.com)
 * Copyright (C) 2008 by David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */


#include "u_serial.h"
#include <stdio.h>
#include "../config.h"

/* Defines */

#define GS_VERSION_STR			"v2.4"
#define GS_VERSION_NUM			0x2400

#define GS_LONG_NAME			"Gadget Serial"
#define GS_VERSION_NAME			GS_LONG_NAME " " GS_VERSION_STR



/*-------------------------------------------------------------------------*/
//USB_GADGET_COMPOSITE_OPTIONS();

/* Thanks to NetChip Technologies for donating this product ID.
*
* DO NOT REUSE THESE IDs with a protocol-incompatible driver!!  Ever!!
* Instead:  allocate your own, using normal USB-IF procedures.
*/
#define GS_VENDOR_ID			0x0525	/* NetChip */
#define GS_PRODUCT_ID			0xa4a6	/* Linux-USB Serial Gadget */
#define GS_CDC_PRODUCT_ID		0xa4a7	/* ... as CDC-ACM */
#define GS_CDC_OBEX_PRODUCT_ID		0xa4a9	/* ... as CDC-OBEX */

/* string IDs are assigned dynamically */

#define STRING_DESCRIPTION_IDX		USB_GADGET_FIRST_AVAIL_IDX

static struct usb_string strings_dev[] = {
	[USB_GADGET_MANUFACTURER_IDX].s = "",
	[USB_GADGET_PRODUCT_IDX].s = GS_VERSION_NAME,
	[USB_GADGET_SERIAL_IDX].s = "",
	[STRING_DESCRIPTION_IDX].s = NULL /* updated; f(use_acm) */,
	{  } /* end of list */
};

static struct usb_gadget_strings stringtab_dev = {
	.language	= 0x0409,	/* en-us */
	.strings	= strings_dev,
};

static struct usb_gadget_strings *dev_strings[] = {
	&stringtab_dev,
	NULL,
};

static struct usb_device_descriptor device_desc = {
	.bLength =		USB_DT_DEVICE_SIZE,
	.bDescriptorType =	USB_DT_DEVICE,
	/* .bcdUSB = DYNAMIC */
	/* .bDeviceClass = f(use_acm) */
	.bDeviceSubClass =	0,
	.bDeviceProtocol =	0,
	/* .bMaxPacketSize0 = f(hardware) */
	.idVendor =		cpu_to_le16(GS_VENDOR_ID),
	/* .idProduct =	f(use_acm) */
	.bcdDevice = cpu_to_le16(GS_VERSION_NUM),
	/* .iManufacturer = DYNAMIC */
	/* .iProduct = DYNAMIC */
	.bNumConfigurations =	1,
};

static const struct usb_descriptor_header *otg_desc[2];

static bool use_acm = false;

static bool use_obex = false;

static unsigned n_ports = 1;

/*-------------------------------------------------------------------------*/

static struct usb_configuration serial_config_driver = {
	/* .label = f(use_acm) */
	/* .bConfigurationValue = f(use_acm) */
	/* .iConfiguration = DYNAMIC */
	.bmAttributes	= USB_CONFIG_ATT_SELFPOWER,
};

static struct usb_function_instance *fi_serial[MAX_U_SERIAL_PORTS];
static struct usb_function *f_serial[MAX_U_SERIAL_PORTS];

#if 0
struct usb_function *usb_get_function(struct usb_function_instance *fi)
{
	struct usb_function *f;

	f = fi->fd->alloc_func(fi);
	if(0) //(IS_ERR(f))
		return f;
	//?? f->fi = fi;
	return f;
}

void usb_put_function(struct usb_function *f)
{
	if (!f)
		return;

	//?? f->free_func(f);
}
#endif


static int serial_register_ports(struct usb_composite_dev *cdev,
		struct usb_configuration *c, const char *f_name)
{
	int i;
	int ret;

	ret = usb_add_config_only(cdev, c);
	if (ret)
		goto out;

	for (i = 0; i < n_ports; i++) {

		if(strcmp(f_name,"gser")==0)
		{
			f_gser_init(&f_serial[i], &fi_serial[i]);

			ret = usb_add_function(c, f_serial[i]);
			if (ret)
				goto err_add_func;
		}
	}

	return 0;

err_add_func:

fail:
	i--;
	while (i >= 0) {
#if 0
		//??usb_remove_function(c, f_serial[i]);
		//??usb_put_function(f_serial[i]);
		//??usb_put_function_instance(fi_serial[i]);
#endif
		i--;
	}
out:
	return ret;
}

static int gs_bind(struct usb_composite_dev *cdev)
{
	int			status;

	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */

	status = usb_string_ids_tab(cdev, strings_dev);
	if (status < 0)
		goto fail;
	device_desc.iManufacturer = strings_dev[USB_GADGET_MANUFACTURER_IDX].id;
	device_desc.iProduct = strings_dev[USB_GADGET_PRODUCT_IDX].id;
	status = strings_dev[STRING_DESCRIPTION_IDX].id;
	serial_config_driver.iConfiguration = status;

	if (gadget_is_otg(cdev->gadget)) {
		if (!otg_desc[0]) {
			struct usb_descriptor_header *usb_desc;

			usb_desc = usb_otg_descriptor_alloc(cdev->gadget);
			if (!usb_desc) {
				status = -ENOMEM;
				goto fail;
			}
			usb_otg_descriptor_init(cdev->gadget, usb_desc);
			otg_desc[0] = usb_desc;
			otg_desc[1] = NULL;
		}
		serial_config_driver.descriptors = otg_desc;
		serial_config_driver.bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	}

	/* register our configuration */
	if (use_acm) {
		status  = serial_register_ports(cdev, &serial_config_driver,
				"acm");
		usb_ep_autoconfig_reset(cdev->gadget);
	} else if (use_obex)
		status = serial_register_ports(cdev, &serial_config_driver,
				"obex");
	else {
		status = serial_register_ports(cdev, &serial_config_driver,
				"gser");
	}
	if (status < 0)
		goto fail1;
	//temp
	//usb_composite_overwrite_options(cdev, &coverwrite);
	//INFO(cdev, "%s\n", GS_VERSION_NAME);

	return 0;
fail1:
	//temp
	//kfree(otg_desc[0]);
	otg_desc[0] = NULL;
fail:
	return status;
}

static int gs_unbind(struct usb_composite_dev *cdev)
{
	int i;

	for (i = 0; i < n_ports; i++) {
		//??usb_put_function(f_serial[i]);
		//??usb_put_function_instance(fi_serial[i]);
	}
	//temp
	//kfree(otg_desc[0]);
	otg_desc[0] = NULL;

	return 0;
}

static struct usb_composite_driver gserial_driver = {
	.name		= "g_serial",
	.dev		= &device_desc,
	.strings	= dev_strings,
	//.max_speed	= USB_SPEED_SUPER,
	.bind		= gs_bind,
	.unbind		= gs_unbind,
};

//static int __init init(void)
static int  init(void)
{
	/* We *could* export two configs; that'd be much cleaner...
	 * but neither of these product IDs was defined that way.
	 */
	if (use_acm) {
		serial_config_driver.label = "CDC ACM config";
		serial_config_driver.bConfigurationValue = 2;
		device_desc.bDeviceClass = USB_CLASS_COMM;
		device_desc.idProduct =
				cpu_to_le16(GS_CDC_PRODUCT_ID);
	} else if (use_obex) {
		serial_config_driver.label = "CDC OBEX config";
		serial_config_driver.bConfigurationValue = 3;
		device_desc.bDeviceClass = USB_CLASS_COMM;
		device_desc.idProduct =
			cpu_to_le16(GS_CDC_OBEX_PRODUCT_ID);
	} else {
		serial_config_driver.label = "Generic Serial config";
		serial_config_driver.bConfigurationValue = 1;
		device_desc.bDeviceClass = USB_CLASS_VENDOR_SPEC;
		device_desc.idProduct =
				cpu_to_le16(GS_PRODUCT_ID);
	}
	strings_dev[STRING_DESCRIPTION_IDX].s = serial_config_driver.label;

	//??
	return 1;//usb_composite_probe(&gserial_driver);
}


/*
 * NOTICE:
 * Registering via USB function name won't be necessary after rewriting
 * g_dnl to support multiple USB functions.
 */
int g_serial_register(const char *name)
{
	int ret;
	init();
	debug("%s: g_serial_driver.name = %s\n", __func__, name);
	gserial_driver.name = name;

	ret = usb_composite_register(&gserial_driver);
	if (ret) {
		printf("%s: failed!, error: %d\n", __func__, ret);
		return ret;
	}
	return 0;
}


static void  cleanup(void)
{
	usb_composite_unregister(&gserial_driver);
}
