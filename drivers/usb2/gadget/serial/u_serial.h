// SPDX-License-Identifier: GPL-2.0+
/*
 * u_serial.h - interface to USB gadget "serial port"/TTY utilities
 *
 * Copyright (C) 2008 David Brownell
 * Copyright (C) 2008 by Nokia Corporation
 */

#ifndef __U_SERIAL_H
#define __U_SERIAL_H

#include "../composite.h"
#include "../../ch9.h"
#include "usb_cdc_acm.h"
#include "circbuf.h"
#include <target/spinlock.h>

#define MAX_U_SERIAL_PORTS	1
#define USBTTY_BUFFER_SIZE 2048

struct f_serial_opts {
	struct usb_function_instance func_inst;
	u8 port_num;
};


/*
 * The port structure holds info for each port, one for each minor number
 * (and thus for each /dev/ node).
 */
struct gs_port {
	//temp removed
	//struct tty_port		port;
	u8		count;
	spinlock_t		port_lock;	/* guard port_* access */

	struct gserial		*port_usb;

	bool			openclose;	/* open/close in progress */
	u8			port_num;

	struct list_head	read_pool;
	int read_started;
	int read_allocated;
	struct list_head	read_queue;
	unsigned		n_read;
	//struct delayed_work	push;

	struct list_head	write_pool;
	int write_started;
	int write_allocated;
	//struct kfifo		port_write_buf;
	circbuf_t port_write_buf;
	//wait_queue_head_t	drain_wait;	/* wait while writes drain */
	bool                    write_busy;
	//wait_queue_head_t	close_wait;

	/* REVISIT this state ... */
	struct usb_cdc_line_coding port_line_coding;	/* 8-N-1 etc */
};

/*
 * One non-multiplexed "serial" I/O port ... there can be several of these
 * on any given USB peripheral device, if it provides enough endpoints.
 *
 * The "u_serial" utility component exists to do one thing:  manage TTY
 * style I/O using the USB peripheral endpoints listed here, including
 * hookups to sysfs and /dev for each logical "tty" device.
 *
 * REVISIT at least ACM could support tiocmget() if needed.
 *
 * REVISIT someday, allow multiplexing several TTYs over these endpoints.
 */
struct gserial {
	struct usb_function		func;

	/* port is managed by gserial_{connect,disconnect} */
	struct gs_port			*ioport;

	struct usb_ep			*in;
	struct usb_ep			*out;

	/* REVISIT avoid this CDC-ACM support harder ... */
	struct usb_cdc_line_coding port_line_coding;	/* 9600-8-N-1 etc */

	/* notification callbacks */
	void (*connect)(struct gserial *p);
	void (*disconnect)(struct gserial *p);
	int (*send_break)(struct gserial *p, int duration);
};


struct gserial_port_operations {
	int  (*open)(int  port_num);
	void (*close)();
	int  (*write)(struct gs_port	*port, const unsigned char *buf, int count);
	int  (*put_char)(struct gs_port	*port, unsigned char ch);
	void (*flush_chars)(struct gs_port	*port);
	void (*rx_push)(struct gs_port *port, circbuf_t *inbuf);
};

/* utilities to allocate/free request and buffer */
struct usb_request *gs_alloc_req(struct usb_ep *ep, unsigned len, gfp_t flags);
void gs_free_req(struct usb_ep *, struct usb_request *req);

/* management of individual TTY ports */
int gserial_alloc_line(unsigned char *port_line);
void gserial_free_line(unsigned char port_line);

/* connect/disconnect is handled by individual functions */
int gserial_connect(struct gserial *, u8 port_num);
void gserial_disconnect(struct gserial *);

/* functions are bound to configurations by a config or gadget driver */
int gser_bind_config(struct usb_configuration *c, u8 port_num);
int obex_bind_config(struct usb_configuration *c, u8 port_num);

struct gs_port* gserial_getport(u8 port_num);
struct gserial_port_operations* gserial_getportops();
int f_gser_init(struct usb_function* *f, struct usb_function_instance* *fi);
int g_serial_register(const char *name);


#endif /* __U_SERIAL_H */
