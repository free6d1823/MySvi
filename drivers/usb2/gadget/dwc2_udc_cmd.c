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


extern int dwc2_udc_handle_interrupt(void);

/*
 * Buffers to hold input and output data
 */

static circbuf_t usbtty_input;

#define CTL_CH(c)		((c) - 'a' + 1)
unsigned char Outchars[USBTTY_BUFFER_SIZE];


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
				dwc2_udc_handle_interrupt();
			} while((port->port_usb)==0);
			printf("usb serial port:%d is ready, \n", port_num);
			break;
		 }
		else
			printf("gs open error: ret:%d", ret);
	}

	do
	{

		do {
			ret = dwc2_udc_handle_interrupt();
		} while(ret==0);

		delay_cnts++;
		if (delay_cnts==10)	{
			portops->rx_push(port, inbuf);
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
		putc('\n');
		//Sendback the receive chars.
		portops->write(port, Outchars, i);
		i=0;
		if (getc()==CTL_CH('c'))
			break;
	} while(1);

}



static void do_usb_udc_test(void)
{
	usb_serialfunc_test();
}



//temp
struct dwc2_plat_otg_data se1000_otg_data = {
	.phy_control = 0,
	.regs_phy = 0,
	.regs_otg = CONFIG_USB_DWC2_REG_ADDR,
	.usb_phy_ctrl = 0x0,
	.usb_flags = PHY0_SLEEP,
};


int board_usb_init(int index, enum usb_init_type init)
{
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

	return -EUSAGE;
}


MK_CMD(usbdevice, do_usb_device,	"USB sub-system",
	"usbdevice init - USB dwc2 device serial function\n"
	"usbdevice serial - USB dwc2 device serial function test\n"
);
