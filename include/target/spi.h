/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Common SPI Interface: Controller-specific definitions
 *
 * (C) Copyright 2001
 * Gerald Van Baren, Custom IDEAS, vanbaren@cideas.com.
 */

#ifndef _SPI_H_
#define _SPI_H_

#include <target/utils.h>

/* SPI mode flags */
#define SPI_CPHA	BIT(0)			/* clock phase */
#define SPI_CPOL	BIT(1)			/* clock polarity */
#define SPI_MODE_0	(0|0)			/* (original MicroWire) */
#define SPI_MODE_1	(0|SPI_CPHA)
#define SPI_MODE_2	(SPI_CPOL|0)
#define SPI_MODE_3	(SPI_CPOL|SPI_CPHA)
#define SPI_CS_HIGH	BIT(2)			/* CS active high */
#define SPI_LSB_FIRST	BIT(3)			/* per-word bits-on-wire */
#define SPI_3WIRE	BIT(4)			/* SI/SO signals shared */
#define SPI_LOOP	BIT(5)			/* loopback mode */
#define SPI_SLAVE	BIT(6)			/* slave mode */
#define SPI_PREAMBLE	BIT(7)			/* Skip preamble bytes */
#define SPI_TX_BYTE	BIT(8)			/* transmit with 1 wire byte */
#define SPI_TX_DUAL	BIT(9)			/* transmit with 2 wires */
#define SPI_TX_QUAD	BIT(10)			/* transmit with 4 wires */
#define SPI_RX_SLOW	BIT(11)			/* receive with 1 wire slow */
#define SPI_RX_DUAL	BIT(12)			/* receive with 2 wires */
#define SPI_RX_QUAD	BIT(13)			/* receive with 4 wires */

/**
 * struct dm_spi_platdata - platform data for all SPI slaves
 *
 * This describes a SPI slave, a child device of the SPI bus. To obtain this
 * struct from a spi_slave, use dev_get_parent_platdata(dev) or
 * dev_get_parent_platdata(slave->dev).
 *
 * This data is immuatable. Each time the device is probed, @max_hz and @mode
 * will be copied to struct spi_slave.
 *
 * @cs:		Chip select number (0..n-1)
 * @max_hz:	Maximum bus speed that this slave can tolerate
 * @mode:	SPI mode to use for this device (see SPI mode flags)
 */
struct dm_spi_slave_platdata {
	unsigned int cs;
	uint max_hz;
	uint mode;
};

/**
 * struct spi_slave - Representation of a SPI slave
 *
 * For driver model this is the per-child data used by the SPI bus. It can
 * be accessed using dev_get_parent_priv() on the slave device. The SPI uclass
 * sets uip per_child_auto_alloc_size to sizeof(struct spi_slave), and the
 * driver should not override it. Two platform data fields (max_hz and mode)
 * are copied into this structure to provide an initial value. This allows
 * them to be changed, since we should never change platform data in drivers.
 *
 * If not using driver model, drivers are expected to extend this with
 * controller-specific data.
 *
 * @dev:		SPI slave device
 * @max_hz:		Maximum speed for this slave
 * @speed:		Current bus speed. This is 0 until the bus is first
 *			claimed.
 * @bus:		ID of the bus that the slave is attached to. For
 *			driver model this is the sequence number of the SPI
 *			bus (bus->seq) so does not need to be stored
 * @cs:			ID of the chip select connected to the slave.
 * @mode:		SPI mode to use for this slave (see SPI mode flags)
 * @wordlen:		Size of SPI word in number of bits
 * @max_read_size:	If non-zero, the maximum number of bytes which can
 *			be read at once.
 * @max_write_size:	If non-zero, the maximum number of bytes which can
 *			be written at once.
 * @memory_map:		Address of read-only SPI flash access.
 * @flags:		Indication of SPI flags.
 */
struct spi_slave {
#ifdef CONFIG_DM_SPI
	struct udevice *dev;	/* struct spi_slave is dev->parentdata */
	uint max_hz;
	uint speed;
#else
	unsigned int bus;
	unsigned int cs;
#endif
	uint mode;
	unsigned int wordlen;
	unsigned int max_read_size;
	unsigned int max_write_size;
	void *memory_map;

	u8 flags;
#define SPI_XFER_BEGIN		BIT(0)	/* Assert CS before transfer */
#define SPI_XFER_END		BIT(1)	/* Deassert CS after transfer */
#define SPI_XFER_ONCE		(SPI_XFER_BEGIN | SPI_XFER_END)
#define SPI_XFER_MMAP		BIT(2)	/* Memory Mapped start */
#define SPI_XFER_MMAP_END	BIT(3)	/* Memory Mapped End */
};

#endif	/* _SPI_H_ */

