#ifndef __GPU2_H__
#define __GPU2_H__

#include <asm/memory.h>
#include <target/utils.h>
#include <target/irq.h>
#include <target/irqc.h>

#define GPU2_AHB_AQHICLOCKCTRL	0x0
#define GPU2_AHB_AQHIIDLE	0x4
#define GPU2_AHB_AQAXICONFIG	0x8
#define GPU2_AHB_AQAXISTATUS	0xc
#define GPU2_AHB_AQINTRACK	0x10
#define GPU2_AHB_AQINTRENBL	0x14
#define GPU2_AHB_GCCHIPID	0x20
#define GPU2_AHB_GCCHIPREV	0x24
#define GPU2_AHB_GCCHIPDATE	0x28

#define GC355_AHB_GCREGFETCHADDR 0x500
#define GC355_AHB_GCREGFETCHCTRL 0x504

#define GC620_AHB_MMUCONTROL	0x18C
#define GC620_AHB_AQCMDBUFADDR	0x654
#define GC620_AHB_AQCMDBUFCTRL	0x658

void soft_reset(uintptr_t);
void dump_info(uintptr_t);
void polling_idle(uintptr_t);
void fetch_cmd_start(uintptr_t, int, u32, u32, u32);
void change_freq_polling(uintptr_t , uintptr_t);
void clockgating_test(uintptr_t, int, uint32_t, u32, u32, u32);
void change_freq_test(uintptr_t, int, uint32_t, u32, u32, u32);
void enable_smmu(phys_addr_t);

void gc355_normal_test(int, uint32_t);
void gc620_normal_test(int, uint32_t);
void gc620_mmu_test(uint32_t, uint32_t);
void gc620_ramclockgating_test(uint32_t);
void gc620_change_freq_test(int, uint32_t);
void gc355_change_freq_test(int, uint32_t);
void gc620_clockgating_test(int, uint32_t);
void gc355_clockgating_test(int, uint32_t);


#endif

