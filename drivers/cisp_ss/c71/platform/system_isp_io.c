//----------------------------------------------------------------------------
//   The confidential and proprietary information contained in this file may
//   only be used by a person authorised under and to the extent permitted
//   by a subsisting licensing agreement from ARM Limited or its affiliates.
//
//          (C) COPYRIGHT [2019] ARM Limited or its affiliates.
//              ALL RIGHTS RESERVED
//
//   This entire notice must be reproduced on all copies of this file
//   and copies of this file may only be made by a person if such person is
//   permitted to do so under the terms of a subsisting license agreement
//   from ARM Limited or its affiliates.
//----------------------------------------------------------------------------

#include "system_isp_io.h"
#include "acamera_logger.h"
#include <target/utils.h>
#include <target/cache.h>
#define WRITE_REG(addr, value) (*(volatile unsigned int *)(uintptr_t)(addr) = value)
#define READ_REG(addr) (*(volatile unsigned int *)(uintptr_t)(addr))
int32_t system_isp_init( void )
{
    return 0;
}

void system_isp_deinit( void )
{
}

uint8_t system_isp_mem_read( void *dst, uint32_t src, uint32_t elem, uint8_t elemSz )
{
    return 0;
}

uint32_t system_isp_read_32( uint32_t addr )
{
	return readl((uintptr_t)addr);
}

uint16_t system_isp_read_16( uint32_t addr )
{
	in_16((uintptr_t)addr);
    return 0;
}

uint8_t system_isp_read_8( uint32_t addr )
{
	readb((uintptr_t)addr);
    return 0;
}

void system_isp_write_32( uint32_t addr, uint32_t data )
{
	uint32_t haddr = (addr & 0xFFFF0000) >> 16;
	uint32_t laddr = addr & 0xFFFF;
	//load slot by ddr backdoor, by 10000058
	//if (haddr == 0x6102 || haddr == 0x6103)
	//	return;
	//if (haddr == 0xe80c && laddr > 0x4000)
	//	return;
	writel(data, (uintptr_t)addr);
	if (haddr == 0x6102 || haddr == 0x6103)
		flush_dcache_addr(addr);
	//if (haddr == 0xe80c)
	//	printf("addr=0x%2x,data=0x%2x\n",addr,data);
	//if (addr == 0x6102e720 || addr == 0x6102e140 ||  addr == 0x6102e040)
	//	printf("addr=0x%2x,data=0x%2x\n",addr,data);
}

void system_isp_write_16( uint32_t addr, uint16_t data )
{
	out_16((uintptr_t)addr, data);
}

void system_isp_write_8( uint32_t addr, uint8_t data )
{
	writeb(data, (uintptr_t)addr);
}
