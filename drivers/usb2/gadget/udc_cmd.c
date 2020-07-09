// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2001
 * Denis Peter, MPL AG Switzerland
 *
 * Adapted for U-Boot driver model
 * (C) Copyright 2015 Google, Inc
 *
 * Most of this source has been derived from the Linux USB
 * project.
 */
#include <stdio.h>
#include <target/cmdline.h>
#include "../usbport.h"
#include "../memalign.h"
#include "../usb.h"
#include "dwc2_udc.h"
#include "gadget.h"
#include "serial/u_serial.h"
#include "core.h"
#include "io.h"

extern int dwc2_udc_handle_interrupt(void);

/*
 * Buffers to hold input and output data
 */

static circbuf_t usbtty_input;

#define CTL_CH(c)		((c) - 'a' + 1)
unsigned char Outchars[USBTTY_BUFFER_SIZE];


static int udc_handle_interrupt(void)
{
#ifdef CONFIG_USB_DWC2
	return dwc2_udc_handle_interrupt();
#endif

#ifdef CONFIG_USB_DWC3
	return usb_gadget_handle_interrupts(0);
#endif
}



static void usb_serialfunc_test(void)
{
	circbuf_t *inbuf;
	int i, port_num, ret;
	char readch;
	struct gs_port	*port = NULL;
	int delay_cnts=0;
	struct gserial_port_operations *portops;

	/* prepare buffers... */
	buf_init (&usbtty_input, USBTTY_BUFFER_SIZE);
	inbuf = &usbtty_input;
	portops = gserial_getportops();

	for(i=0; i<MAX_U_SERIAL_PORTS; i++ )
	{
		ret = portops->open(i);
		if (ret==0)	{
			port_num=i;
			break;
		}
		else if (ret== -ENREDY)	{
			printf("usb not ready, please insert usb cable\n");
			port_num=i;
			port = gserial_getport(port_num);
			do {
				udc_handle_interrupt();
			} while((port->port_usb)==0);
			printf("usb serial port:%d is ready, \n", port_num);
			break;
		 }
		else
			printf("gs open error: ret:%d", ret);
	}

	do
	{
		udc_handle_interrupt();
		delay_cnts++;
		if (delay_cnts==10)	{
			portops->rx_push(port, inbuf);
			if (inbuf->size)
				printf("push data num %x from usb rx buffer \n", inbuf->size);
			delay_cnts=0;
		}

		i=0;
		while (inbuf->size!=0)
		{
			buf_pop(inbuf,&readch, 1);
			putc(readch);
			Outchars[i]=readch;
			i++;
		}

		if(i!=0)
		{  //Sendback the receive chars.
			putc('\n');
			portops->write(port, Outchars, i);
			i=0;
		}
		if (getc()==CTL_CH('c'))
			break;
	} while(1);

}



static void do_usb_udc_test(void)
{
	usb_serialfunc_test();
}



#ifdef CONFIG_USB_DWC2

#define  USB2_AXICLK_REG        0x581C2200
#define  USB2_PHYCLK_REG        0x581C2204

#define  USB2_AXIRST_REG        0x581D3200
#define  USB2_PRST_REG          0x581D3204

#define  USB2_POREN_REG         0x581A3000


struct dwc2_plat_otg_data se1000_otg_data = {
	.phy_control = 0,
	.regs_phy = 0,
	.regs_otg = CONFIG_USB_DWC2_REG_ADDR,
	.usb_phy_ctrl = 0x0,
	.usb_flags = PHY0_SLEEP,
};


int board_usb_init(int index, enum usb_init_type init)
{
	printf("USB2 clock regs init...\n");
	writel(1, USB2_PRST_REG);
	writel(1, USB2_AXIRST_REG);
	writel(0, USB2_PRST_REG);
	writel(0, USB2_AXIRST_REG);
	writel(0x10000, USB2_AXICLK_REG);
	writel(0x10002, USB2_PHYCLK_REG);
	writel(0, USB2_POREN_REG);

	printf("AXICLK register:%x", readl(USB2_AXICLK_REG));
	printf("PHYCLK register:%x", readl(USB2_PHYCLK_REG));
	if (init==USB_INIT_DEVICE) {
		printf("USB dwc2 udc probe\n");
		if (dwc2_udc_probe(&se1000_otg_data)==0) {
			if ( g_serial_register("g_serial")!=0)
				printf("g_serial function register error\n");
			else {
				printf("se1000 dwc2 g_serial function register ok\n");
				return 0;
			}
		}
		else
			printf("dwc2 udc probe error\n");
		return -1;
	}
	else
		return 0;
}
#endif


#ifdef CONFIG_USB_DWC3
static struct dwc3_device dwc3_device_data = {
	.maximum_speed = USB_SPEED_SUPER,
	.base = 0xE7400000,
	.dr_mode = USB_DR_MODE_PERIPHERAL,
	.index = 0,
};

int usb_gadget_handle_interrupts(int index)
{
	dwc3_uboot_handle_interrupt(0);
	return 0;
}

int board_usb_init(int index, enum usb_init_type init)
{
	if (init==USB_INIT_DEVICE) {
			printf("USB dwc3 udc probe\n");
			if (dwc3_uboot_init(&dwc3_device_data)==0) {
					if ( g_serial_register("g_serial")!=0)
						printf("g_serial function register error\n");
					else {
						printf("se1000 dwc3 g_serial function register ok\n");
						return 0;
					}
			}
			else
					printf("dwc3 udc probe error\n");
			return -1;
	}
	else
		return 0;
}

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

extern struct dwc3* dwc3_return_dwc3pt(int index);
extern void dwc3_gadget_kick_transfer(struct dwc3_ep *dep, u16 cmd_param,
				int start_new);

void  dwc3_loopback_test()
{
	struct dwc3 *dwc;
	struct dwc3_ep *dep;
	struct usb_request *req;

	u32  value;

	if (dwc3_uboot_init(&dwc3_device_data)==0) {

	dwc = dwc3_return_dwc3pt(dwc3_device_data.index);

	// dctl setting for test
	value = dwc3_readl(dwc->regs, DWC3_DCTL);
	value |= (DWC3_DCTL_CRS|DWC3_DCTL_SCALEDOWNENA);
	dwc3_writel(dwc->regs, DWC3_DCTL, value);
	printf("dctl register value=%x\n", value);

	// bloopbckctrl setting for loopback mode
	value = dwc3_readl(dwc->regs, DWC3_BLOOPBCKCTRL);
	value = (DWC3_LPBACK_LEVEL_SSP_PIPE | DWC3_LPBACK_MODE_SW | DWC3_LPBACK_MODE_EN);
	dwc3_writel(dwc->regs, DWC3_BLOOPBCKCTRL, value);
	printf("bloopbckctrl register value=%x\n", value);

	// dcfg setting for loopback mode
	value = dwc3_readl(dwc->regs, DWC3_DCFG);
	value = (DWC3_DCFGL_DEVSPD_SS);
	dwc3_writel(dwc->regs, DWC3_DCFG, value);
	printf("dcfg register value=%x\n", value);

	//Setup ep2 configration/
	dep = dwc->eps[2];
	dep->endpoint.ops->enable(&dep->endpoint,  &gser_ss_in_desc);

	u32 len = 1024;

	req = usb_ep_alloc_request(&dep->endpoint, GFP_ATOMIC);

	if (req != NULL) {
		req->length = len;
		req->buf = malloc(len); //?? kmalloc(len, kmalloc_flags);
		if (req->buf == NULL) {
			usb_ep_free_request(&dep->endpoint, req);
			return;
		}
	}

	//Setup ep3 configuration/
	dep = dwc->eps[3];
	dep->endpoint.ops->enable(&dep->endpoint,  &gser_ss_out_desc);

	req = usb_ep_alloc_request(&dep->endpoint, GFP_ATOMIC);

	if (req != NULL) {
		req->length = len;
		req->buf = malloc(len); //?? kmalloc(len, kmalloc_flags);
		if (req->buf == NULL) {
			usb_ep_free_request(&dep->endpoint, req);
			return;
		}
	}

	dwc3_gadget_kick_transfer(dep, 0, 1);
	dep = dwc->eps[2];
	dwc3_gadget_kick_transfer(dep, 0, 1);
	}

}
#endif





/******************************************************************************
 * usb command intepreter
 */
static int do_usb_device(int argc, char * argv[])
{
	if (argc < 2)
		return -EUSAGE;

	if (strncmp(argv[1], "init", 4) == 0) {
		printf("init USB device serial function...\n");
		usb_gadget_initialize(0);
		return 0;
	}


	if (strncmp(argv[1], "serial", 6) == 0) {
		printf("starting USB device serial function...\n");
		do_usb_udc_test();
		return 0;
	}
#ifdef CONFIG_USB_DWC3
	if (strncmp(argv[1], "sw_lpbck", 8) == 0) {
		printf("starting usb sw loopback mode test...");
		dwc3_loopback_test();
		return 0;
	}
#endif
	return -EUSAGE;
}


MK_CMD(usbdevice, do_usb_device,	"USB sub-system",
	"usbdevice init - USB dwc2 device serial function\n"
	"usbdevice serial - USB dwc2 device serial function test\n"
#ifdef CONFIG_USB_DWC3
	"usbdevice sw_lpbck - USB dwc2 device serial function test\n"
#endif
);
