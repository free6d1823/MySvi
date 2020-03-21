// SPDX-License-Identifier: GPL-2.0
/*
 * Synopsys DesignWare PCIe host controller driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Jingoo Han <jg1.han@samsung.com>
 */
#include <errno.h>
#include <string.h>
#include <target/compiler.h>
#include <asm/memory.h>
#include <stdio.h>
#include <target/smp.h>
#include <target/console.h>
#include <target/delay.h>
#include <target/cache.h>

#include "pcie-designware.h"

/* PCIe Port Logic registers */
#define PLR_OFFSET			0x700
#define PCIE_PHY_DEBUG_R1		(PLR_OFFSET + 0x2c)
#define PCIE_PHY_DEBUG_R1_LINK_UP	(0x1 << 4)
#define PCIE_PHY_DEBUG_R1_LINK_IN_TRAINING	(0x1 << 29)

struct dw_plat_pcie dw_plat_pci;
struct dw_pcie dw_pci;
struct resource_entry win;


int dw_pcie_read(void *addr, int size, u32 *val)
{
	if (!IS_ALIGNED((uintptr_t)addr, size)) {
		*val = 0;
		return PCIBIOS_BAD_REGISTER_NUMBER;
	}

	if (size == 4) {
		*val = __raw_readl(addr);
	} else if (size == 2) {
		*val = __raw_readw(addr);
	} else if (size == 1) {
		*val = __raw_readb(addr);
	} else {
		*val = 0;
		return PCIBIOS_BAD_REGISTER_NUMBER;
	}

	return PCIBIOS_SUCCESSFUL;
}

int dw_pcie_write(void *addr, int size, u32 val)
{
	if (!IS_ALIGNED((uintptr_t)addr, size))
		return PCIBIOS_BAD_REGISTER_NUMBER;

	if (size == 4)
		__raw_writel(val, addr);
	else if (size == 2)
		__raw_writew(val, addr);
	else if (size == 1)
		__raw_writeb(val, addr);
	else
		return PCIBIOS_BAD_REGISTER_NUMBER;

	return PCIBIOS_SUCCESSFUL;
}

u32 __dw_pcie_read_dbi(struct dw_pcie *pci, void *base, u32 reg,
		       size_t size)
{
	int ret;
	u32 val;

	if (pci->ops->read_dbi)
		return pci->ops->read_dbi(pci, base, reg, size);

	ret = dw_pcie_read(base + reg, size, &val);
	if (ret)
		printf( "Read DBI address failed\n");

	return val;
}

void __dw_pcie_write_dbi(struct dw_pcie *pci, void *base, u32 reg,
			 size_t size, u32 val)
{
	int ret;

	if (pci->ops->write_dbi) {
		pci->ops->write_dbi(pci, base, reg, size, val);
		return;
	}

	ret = dw_pcie_write(base + reg, size, val);
	if (ret)
		printf( "Write DBI address failed\n");
}

static u32 dw_pcie_readl_ob_unroll(struct dw_pcie *pci, u32 index, u32 reg)
{
	u32 offset = PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index);

	return dw_pcie_readl_atu(pci, offset + reg);
}

static void dw_pcie_writel_ob_unroll(struct dw_pcie *pci, u32 index, u32 reg,
				     u32 val)
{
	u32 offset = PCIE_GET_ATU_OUTB_UNR_REG_OFFSET(index);

	dw_pcie_writel_atu(pci, offset + reg, val);
}

static void dw_pcie_prog_outbound_atu_unroll(struct dw_pcie *pci, int index,
					     int type, u64 cpu_addr,
					     u64 pci_addr, u32 size)
{
	u32 retries, val;

	dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_BASE,
				 lower_32_bits(cpu_addr));
	dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_BASE,
				 upper_32_bits(cpu_addr));
	dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LIMIT,
				 lower_32_bits(cpu_addr + size - 1));
	dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_TARGET,
				 lower_32_bits(pci_addr));
	dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_TARGET,
				 upper_32_bits(pci_addr));
	dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL1,
				 type);
	dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2,
				 PCIE_ATU_ENABLE);

	/*
	 * Make sure ATU enable takes effect before any subsequent config
	 * and I/O accesses.
	 */
	for (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) {
		val = dw_pcie_readl_ob_unroll(pci, index,
					      PCIE_ATU_UNR_REGION_CTRL2);
		if (val & PCIE_ATU_ENABLE)
			return;

		mdelay(LINK_WAIT_IATU);
	}
	printf("Outbound iATU is not being enabled\n");
}

void dw_pcie_prog_outbound_atu(struct dw_pcie *pci, int index, int type,
			       u64 cpu_addr, u64 pci_addr, u32 size)
{
	u32 retries, val;

	if (pci->ops->cpu_addr_fixup)
		cpu_addr = pci->ops->cpu_addr_fixup(pci, cpu_addr);

	if (pci->iatu_unroll_enabled) {
		dw_pcie_prog_outbound_atu_unroll(pci, index, type, cpu_addr,
						 pci_addr, size);
		return;
	}

	dw_pcie_writel_dbi(pci, PCIE_ATU_VIEWPORT,
			   PCIE_ATU_REGION_OUTBOUND | index);
	dw_pcie_writel_dbi(pci, PCIE_ATU_LOWER_BASE,
			   lower_32_bits(cpu_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_UPPER_BASE,
			   upper_32_bits(cpu_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_LIMIT,
			   lower_32_bits(cpu_addr + size - 1));
	dw_pcie_writel_dbi(pci, PCIE_ATU_LOWER_TARGET,
			   lower_32_bits(pci_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_UPPER_TARGET,
			   upper_32_bits(pci_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_CR1, type);
	dw_pcie_writel_dbi(pci, PCIE_ATU_CR2, PCIE_ATU_ENABLE);

	/*
	 * Make sure ATU enable takes effect before any subsequent config
	 * and I/O accesses.
	 */
	for (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) {
		val = dw_pcie_readl_dbi(pci, PCIE_ATU_CR2);
		if (val & PCIE_ATU_ENABLE)
			return;

		mdelay(LINK_WAIT_IATU);
	}
	printf("Outbound iATU is not being enabled\n");
}

static u32 dw_pcie_readl_ib_unroll(struct dw_pcie *pci, u32 index, u32 reg)
{
	u32 offset = PCIE_GET_ATU_INB_UNR_REG_OFFSET(index);

	return dw_pcie_readl_atu(pci, offset + reg);
}

static void dw_pcie_writel_ib_unroll(struct dw_pcie *pci, u32 index, u32 reg,
				     u32 val)
{
	u32 offset = PCIE_GET_ATU_INB_UNR_REG_OFFSET(index);

	dw_pcie_writel_atu(pci, offset + reg, val);
}

static int dw_pcie_prog_inbound_atu_unroll(struct dw_pcie *pci, int index,
					   int bar, u64 cpu_addr,
					   enum dw_pcie_as_type as_type)
{
	int type;
	u32 retries, val;

	dw_pcie_writel_ib_unroll(pci, index, PCIE_ATU_UNR_LOWER_TARGET,
				 lower_32_bits(cpu_addr));
	dw_pcie_writel_ib_unroll(pci, index, PCIE_ATU_UNR_UPPER_TARGET,
				 upper_32_bits(cpu_addr));

	switch (as_type) {
	case DW_PCIE_AS_MEM:
		type = PCIE_ATU_TYPE_MEM;
		break;
	case DW_PCIE_AS_IO:
		type = PCIE_ATU_TYPE_IO;
		break;
	default:
		return -EINVAL;
	}

	dw_pcie_writel_ib_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL1, type);
	dw_pcie_writel_ib_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2,
				 PCIE_ATU_ENABLE |
				 PCIE_ATU_BAR_MODE_ENABLE | (bar << 8));

	/*
	 * Make sure ATU enable takes effect before any subsequent config
	 * and I/O accesses.
	 */
	for (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) {
		val = dw_pcie_readl_ib_unroll(pci, index,
					      PCIE_ATU_UNR_REGION_CTRL2);
		if (val & PCIE_ATU_ENABLE)
			return 0;

		mdelay(LINK_WAIT_IATU);
	}
	printf("Inbound iATU is not being enabled\n");

	return -EBUSY;
}

int dw_pcie_prog_inbound_atu(struct dw_pcie *pci, int index, int bar,
			     u64 cpu_addr, enum dw_pcie_as_type as_type)
{
	int type;
	u32 retries, val;

	if (pci->iatu_unroll_enabled)
		return dw_pcie_prog_inbound_atu_unroll(pci, index, bar,
						       cpu_addr, as_type);

	dw_pcie_writel_dbi(pci, PCIE_ATU_VIEWPORT, PCIE_ATU_REGION_INBOUND |
			   index);
	dw_pcie_writel_dbi(pci, PCIE_ATU_LOWER_TARGET, lower_32_bits(cpu_addr));
	dw_pcie_writel_dbi(pci, PCIE_ATU_UPPER_TARGET, upper_32_bits(cpu_addr));

	switch (as_type) {
	case DW_PCIE_AS_MEM:
		type = PCIE_ATU_TYPE_MEM;
		break;
	case DW_PCIE_AS_IO:
		type = PCIE_ATU_TYPE_IO;
		break;
	default:
		return -EINVAL;
	}

	dw_pcie_writel_dbi(pci, PCIE_ATU_CR1, type);
	dw_pcie_writel_dbi(pci, PCIE_ATU_CR2, PCIE_ATU_ENABLE
			   | PCIE_ATU_BAR_MODE_ENABLE | (bar << 8));

	/*
	 * Make sure ATU enable takes effect before any subsequent config
	 * and I/O accesses.
	 */
	for (retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; retries++) {
		val = dw_pcie_readl_dbi(pci, PCIE_ATU_CR2);
		if (val & PCIE_ATU_ENABLE)
			return 0;

		mdelay(LINK_WAIT_IATU);
	}
	printf("Inbound iATU is not being enabled\n");

	return -EBUSY;
}

void dw_pcie_disable_atu(struct dw_pcie *pci, int index,
			 enum dw_pcie_region_type type)
{
	int region;

	switch (type) {
	case DW_PCIE_REGION_INBOUND:
		region = PCIE_ATU_REGION_INBOUND;
		break;
	case DW_PCIE_REGION_OUTBOUND:
		region = PCIE_ATU_REGION_OUTBOUND;
		break;
	default:
		return;
	}

	dw_pcie_writel_dbi(pci, PCIE_ATU_VIEWPORT, region | index);
	dw_pcie_writel_dbi(pci, PCIE_ATU_CR2, (u32)~PCIE_ATU_ENABLE);
}

int dw_pcie_wait_for_link(struct dw_pcie *pci)
{
	int retries;

	/* Check if the link is up or not */
	for (retries = 0; retries < LINK_WAIT_MAX_RETRIES; retries++) {
		if (dw_pcie_link_up(pci)) {
			printf( "Link up\n");
			return 0;
		}
		udelay(LINK_WAIT_USLEEP_MAX);
	}

	printf("Phy link never came up\n");

	return -ETIMEDOUT;
}

int dw_pcie_link_up(struct dw_pcie *pci)
{
	u32 val;

	if (pci->ops->link_up)
		return pci->ops->link_up(pci);

	val = readl(pci->dbi_base + PCIE_PHY_DEBUG_R1);
	return ((val & PCIE_PHY_DEBUG_R1_LINK_UP) &&
		(!(val & PCIE_PHY_DEBUG_R1_LINK_IN_TRAINING)));
}

void dw_pcie_setup(struct dw_pcie *pci)
{
	int ret;
	u32 val;
	u32 lanes;

	lanes = SE1000_PCIE_LANE_NUMBERS;
	/* Set the number of lanes */
	val = dw_pcie_readl_dbi(pci, PCIE_PORT_LINK_CONTROL);
	val &= ~PORT_LINK_MODE_MASK;
	switch (lanes) {
	case 1:
		val |= 0x10000;
		break;
	case 2:
		val |= 0x30000;
		break;
	case 4:
		val |= 0x70000;
		break;
	case 8:
		val |= 0xf0000;
		break;
	default:
		printf("num-lanes %u: invalid value\n", lanes);
		return;
	}
	dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);

	/* Set link width speed control register */
	val = dw_pcie_readl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
	val &= ~PORT_LOGIC_LINK_WIDTH_MASK;
	switch (lanes) {
	case 1:
		val |= 0x100;
		break;
	case 2:
		val |= 0x200;
		break;
	}
	dw_pcie_writel_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);
}

void dw_enter_loopback_mode(struct dw_pcie *pci)
{
	u32 val;

	val = dw_pcie_readl_dbi(pci, GEN3_RELATED_OFF);
	/* set Gen3Equalization Disable bit */
	val |= 0x10000;
	dw_pcie_writel_dbi(pci, GEN3_RELATED_OFF, val);

	val = dw_pcie_readl_dbi(pci, PIPE_LOOPBACK_CONTROL_OFF);
	val |= 0x80000000;
	dw_pcie_writel_dbi(pci, PIPE_LOOPBACK_CONTROL_OFF, val);

	val = dw_pcie_readl_dbi(pci, PCIE_PORT_LINK_CONTROL);
	val |= 0x4;
	dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);
}

void dw_exit_loopback_mode(struct dw_pcie *pci)
{
	u32 val;

	val = dw_pcie_readl_dbi(pci, PCIE_PORT_LINK_CONTROL);
	val &= 0xfffffffb;
	dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);

	val = dw_pcie_readl_dbi(pci, PIPE_LOOPBACK_CONTROL_OFF);
	val &= 0x7fffffff;
	dw_pcie_writel_dbi(pci, PIPE_LOOPBACK_CONTROL_OFF, val);
}

