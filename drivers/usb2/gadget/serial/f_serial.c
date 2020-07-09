// SPDX-License-Identifier: GPL-2.0+
/*
 * f_serial.c - generic USB serial function driver
 *
 * Copyright (C) 2003 Al Borchers (alborchers@steinerpoint.com)
 * Copyright (C) 2008 by David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

#include <stdio.h>
#include "u_serial.h"
#include "../config.h"


#define MAX_ERRNO	4095

/*
 * This function packages a simple "generic serial" port with no real
 * control mechanisms, just raw data transfer over two bulk endpoints.
 *
 * Because it's not standardized, this isn't as interoperable as the
 * CDC ACM driver.  However, for many purposes it's just as functional
 * if you can arrange appropriate host side drivers.
 */

struct f_gser {
	struct gserial			port;
	u8				data_id;
	u8				port_num;
};


#ifndef pr_fmt
#define pr_fmt(fmt) fmt
#endif

#define debug_cond(cond, fmt, args...)			\
	do {						\
		if (cond)				\
			printf(pr_fmt(fmt), ##args);	\
	} while (0)


#define dev_dbg(dev, fmt, args...)		\
	debug(fmt, ##args)
#define dev_err(dev, fmt, args...)		\
	printf(fmt, ##args)
#define dev_warn(dev, fmt, args...)		\
	printf(fmt, ##args)


/* messaging utils */
#define DBG(d, fmt, args...) \
	dev_dbg(&(d)->gadget->dev , fmt , ## args)
#define VDBG(d, fmt, args...) \
	dev_vdbg(&(d)->gadget->dev , fmt , ## args)
#define ERROR(d, fmt, args...) \
	dev_err(&(d)->gadget->dev , fmt , ## args)
#define WARNING(d, fmt, args...) \
	dev_warn(&(d)->gadget->dev , fmt , ## args)

#define IS_ERR_VALUE(x) unlikely((x) >= (unsigned long)-MAX_ERRNO)

static inline void *ERR_PTR(long error)
{
	return (void *) error;
}

static inline long IS_ERR(const void *ptr)
{
	return IS_ERR_VALUE((unsigned long)ptr);
}

static inline long PTR_ERR(const void *ptr)
{
	return (long) ptr;
}


static inline void kfree(const void *block)
{
	free((void *)block);
}

static inline struct f_gser *func_to_gser(struct usb_function *f)
{
	return container_of(f, struct f_gser, port.func);
}


/*-------------------------------------------------------------------------*/

/* interface descriptor: */

static struct usb_interface_descriptor gser_interface_desc = {
	.bLength =		USB_DT_INTERFACE_SIZE,
	.bDescriptorType =	USB_DT_INTERFACE,
	/* .bInterfaceNumber = DYNAMIC */
	.bNumEndpoints =	2,
	.bInterfaceClass =	USB_CLASS_VENDOR_SPEC,
	.bInterfaceSubClass =	0,
	.bInterfaceProtocol =	0,
	/* .iInterface = DYNAMIC */
};

/* full speed support: */

static struct usb_endpoint_descriptor gser_fs_in_desc = {
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpointAddress =	USB_DIR_IN,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
};

static struct usb_endpoint_descriptor gser_fs_out_desc = {
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bEndpointAddress =	USB_DIR_OUT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
};

static struct usb_descriptor_header *gser_fs_function[] = {
	(struct usb_descriptor_header *) &gser_interface_desc,
	(struct usb_descriptor_header *) &gser_fs_in_desc,
	(struct usb_descriptor_header *) &gser_fs_out_desc,
	NULL,
};

/* high speed support: */

static struct usb_endpoint_descriptor gser_hs_in_desc = {
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
};

static struct usb_endpoint_descriptor gser_hs_out_desc = {
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(512),
};

static struct usb_descriptor_header *gser_hs_function[] = {
	(struct usb_descriptor_header *) &gser_interface_desc,
	(struct usb_descriptor_header *) &gser_hs_in_desc,
	(struct usb_descriptor_header *) &gser_hs_out_desc,
	NULL,
};

static struct usb_endpoint_descriptor gser_ss_in_desc = {
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
};

static struct usb_endpoint_descriptor gser_ss_out_desc = {
	.bLength =		USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =	USB_DT_ENDPOINT,
	.bmAttributes =		USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize =	cpu_to_le16(1024),
};

static struct usb_ss_ep_comp_descriptor gser_ss_bulk_comp_desc = {
	.bLength =              sizeof gser_ss_bulk_comp_desc,
	.bDescriptorType =      USB_DT_SS_ENDPOINT_COMP,
};

static struct usb_descriptor_header *gser_ss_function[] = {
	(struct usb_descriptor_header *) &gser_interface_desc,
	(struct usb_descriptor_header *) &gser_ss_in_desc,
	(struct usb_descriptor_header *) &gser_ss_bulk_comp_desc,
	(struct usb_descriptor_header *) &gser_ss_out_desc,
	(struct usb_descriptor_header *) &gser_ss_bulk_comp_desc,
	NULL,
};

/* string descriptors: */

static struct usb_string gser_string_defs[] = {
	[0].s = "Generic Serial",
	{  } /* end of list */
};

static struct usb_gadget_strings gser_string_table = {
	.language =		0x0409,	/* en-us */
	.strings =		gser_string_defs,
};

static struct usb_gadget_strings *gser_strings[] = {
	&gser_string_table,
	NULL,
};


static struct usb_endpoint_descriptor *
fb_ep_desc(struct usb_gadget *g, struct usb_endpoint_descriptor *fs,
	    struct usb_endpoint_descriptor *hs, struct usb_endpoint_descriptor *ss)
{
	if(gadget_is_superspeed(g) && g->speed == USB_SPEED_SUPER)
		return ss;
	else if (gadget_is_dualspeed(g) && g->speed == USB_SPEED_HIGH)
		return hs;
	return fs;
}


/*-------------------------------------------------------------------------*/

static int gser_set_alt(struct usb_function *f, unsigned intf, unsigned alt)
{
	struct f_gser		*gser = func_to_gser(f);
	struct usb_composite_dev *cdev = f->config->cdev;
	struct usb_gadget *gadget = cdev->gadget;
	const struct usb_endpoint_descriptor *d;
	int	   ret;

	/* we know alt == 0, so this is an activation or a reset */

	if (gser->port.in->enabled) {
		//temp
		dev_dbg(cdev!=0,
			"reset generic ttyGS%d\n", gser->port_num);
		gserial_disconnect(&gser->port);
	}

	if (!gser->port.in->desc || !gser->port.out->desc) {
		dev_dbg(cdev!=0,
			"activate generic ttyGS%d\n", gser->port_num);

			d = fb_ep_desc(gadget, &gser_fs_in_desc, &gser_hs_in_desc, &gser_ss_in_desc);
			ret = usb_ep_enable(gser->port.in, d);
			if (ret < 0)
				return ret;
			d = fb_ep_desc(gadget, &gser_fs_out_desc, &gser_hs_out_desc, &gser_ss_out_desc);
			ret = usb_ep_enable(gser->port.out, d);
			if (ret < 0)
				goto fail_out;
	}

	ret = gserial_connect(&gser->port, gser->port_num);
	return ret;
fail_out:
	usb_ep_disable(gser->port.in);
	return ret;
}

static void gser_disable(struct usb_function *f)
{
	struct f_gser	*gser = func_to_gser(f);
	struct usb_composite_dev *cdev = f->config->cdev;

	dev_dbg(&cdev->gadget->dev,
		"generic ttyGS%d deactivated\n", gser->port_num);
	gserial_disconnect(&gser->port);
}

/*-------------------------------------------------------------------------*/

/* serial function driver setup/binding */

static int gser_bind(struct usb_configuration *c, struct usb_function *f)
{
	struct usb_composite_dev *cdev = c->cdev;
	struct f_gser		*gser = func_to_gser(f);
	int			status;
	struct usb_ep		*ep;

	/* REVISIT might want instance-specific strings to help
	 * distinguish instances ...
	 */

	/* maybe allocate device-global string ID */
	if (gser_string_defs[0].id == 0) {
		status = usb_string_id(c->cdev);
		if (status < 0)
			return status;
		gser_string_defs[0].id = status;
	}

	/* allocate instance-specific interface IDs */
	status = usb_interface_id(c, f);
	if (status < 0)
		goto fail;
	gser->data_id = status;
	gser_interface_desc.bInterfaceNumber = status;

	status = -ENODEV;

	/* allocate instance-specific endpoints */
	ep = usb_ep_autoconfig(cdev->gadget, &gser_fs_in_desc);
	if (!ep)
		goto fail;
	gser->port.in = ep;

	ep = usb_ep_autoconfig(cdev->gadget, &gser_fs_out_desc);
	if (!ep)
		goto fail;
	gser->port.out = ep;

	/* support all relevant hardware speeds... we expect that when
	 * hardware is dual speed, all bulk-capable endpoints work at
	 * both speeds
	 */
	gser_hs_in_desc.bEndpointAddress = gser_fs_in_desc.bEndpointAddress;
	gser_hs_out_desc.bEndpointAddress = gser_fs_out_desc.bEndpointAddress;

	gser_ss_in_desc.bEndpointAddress = gser_fs_in_desc.bEndpointAddress;
	gser_ss_out_desc.bEndpointAddress = gser_fs_out_desc.bEndpointAddress;

	status = usb_assign_descriptors(f, gser_fs_function, gser_hs_function,
			gser_ss_function, NULL);
	if (status)
		goto fail;
	dev_dbg(&cdev->gadget->dev, "generic ttyGS%d: %s speed IN/%s OUT/%s\n",
		gser->port_num,
		gadget_is_superspeed(c->cdev->gadget) ? "super" :
		gadget_is_dualspeed(c->cdev->gadget) ? "dual" : "full",
		gser->port.in->name, gser->port.out->name);
	return 0;

fail:
	ERROR(cdev, "%s: can't bind, err %d\n", f->name, status);

	return status;
}


static void serial_attr_release(/*struct config_item *item*/)
{
//	struct f_serial_opts *opts = to_f_serial_opts(item);

//	usb_put_function_instance(&opts->func_inst);
}

//static struct configfs_item_operations serial_item_ops = {
//	.release	= serial_attr_release,
//};

static ssize_t f_serial_port_num_show(/*struct config_item *item, char *page*/)
{
//	return sprintf(page, "%u\n", to_f_serial_opts(item)->port_num);
    return 1;
}

//static struct configfs_attribute *acm_attrs[] = {
//	&f_serial_attr_port_num,
//	NULL,
//};

//static const struct config_item_type serial_func_type = {
//	.ct_item_ops	= &serial_item_ops,
//	.ct_attrs	= acm_attrs,
//	.ct_owner	= THIS_MODULE,
//};

static void gser_free_inst(struct usb_function_instance *f)
{
	struct f_serial_opts *opts;

	opts = container_of(f, struct f_serial_opts, func_inst);
	gserial_free_line(opts->port_num);
	kfree(opts);
}

static struct usb_function_instance *gser_alloc_inst(void)
{
	struct f_serial_opts *opts;
	int ret;

	//temp
	opts = malloc(sizeof(*opts)); //kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);

	opts->func_inst.free_func_inst = gser_free_inst;
	ret = gserial_alloc_line(&opts->port_num);
	if (ret) {
		kfree(opts);
		return ERR_PTR(ret);
	}
	//temp remove
	//config_group_init_type_name(&opts->func_inst.group, "",
	//			    &serial_func_type);

	return &opts->func_inst;
}

static void gser_free(struct usb_function *f)
{
	struct f_gser *serial;

	serial = func_to_gser(f);
	kfree(serial);
}

static void gser_unbind(struct usb_configuration *c, struct usb_function *f)
{
	usb_free_all_descriptors(f);
}

static struct usb_function *gser_alloc(struct usb_function_instance *fi)
{
	struct f_gser	*gser;
	struct f_serial_opts *opts;

	/* allocate and initialize one new instance */
	//gser = kzalloc(sizeof(*gser), GFP_KERNEL);
	gser = malloc(sizeof(*gser));

	if (!gser)
		return ERR_PTR(-ENOMEM);

	opts = container_of(fi, struct f_serial_opts, func_inst);

	gser->port_num = opts->port_num;

	gser->port.func.name = "gser";
	gser->port.func.strings = gser_strings;
	gser->port.func.bind = gser_bind;
	gser->port.func.unbind = gser_unbind;
	gser->port.func.set_alt = gser_set_alt;
	gser->port.func.disable = gser_disable;
	gser->port.func.free_func = gser_free;

	return &gser->port.func;
}

int f_gser_init(struct usb_function* *pf, struct usb_function_instance* *pfi)
{
	struct usb_function* f;
	struct usb_function_instance* fi;

	fi = gser_alloc_inst();
	f = gser_alloc(fi);
	if((fi!=NULL)&&(f!=NULL)) {
		*pf = f;
		*pfi = fi;
		return 1;
	}
	else
		return 0;
}
