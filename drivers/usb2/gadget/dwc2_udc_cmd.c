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


static void do_usb_udc_test(void)
{
	int rc;

	rc = g_serial_register("g_serial");
	if (rc) {
		rc = -1; //CMD_RET_FAILURE;
		printf("g_serial function register error ");
	}
	else
		usb_serialfunc_test();
}



//temp
struct dwc2_plat_otg_data se1000_otg_data = {
	.phy_control = 0,
	.regs_phy = 0,
	.regs_otg = CONFIG_USB_DWC2_REG_ADDR,
	.usb_phy_ctrl = 0x1112,
	.usb_flags = PHY0_SLEEP,
};


int board_usb_init(int index, enum usb_init_type init)
{
	if (init==USB_INIT_DEVICE) {
		printf("USB dwc2 udc probe\n");
		return dwc2_udc_probe(&se1000_otg_data);
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
		printf("init USB device...\n");
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
	"usbdevice init - USB dwc2 device init\n"
	"usbdevice serial - USB dwc2 device serial function test\n"
);
