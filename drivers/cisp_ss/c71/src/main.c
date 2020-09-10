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

#include "system_cache.h"
#include "system_control.h" //BSP
#include "system_stdlib.h"
#include "system_types.h"
#include "acamera.h"
#include "acamera_control_config.h" /* ISP_HAS_STREAM_CONNECTION */
#include "acamera_isp_config.h"
#include "acamera_logger.h"

#if ISP_HAS_STREAM_CONNECTION
#include "acamera_connection.h"
#endif

#include "acamera_frame_consumer.h"

// The settings for each firmware context were pre-generated and
// saved in the header file. They are given as a reference and MUST be changed
// according to the customer needs.
#include "runtime_initialization_settings.h"
#include <target/utils.h>
#include <target/cmdline.h>
#include <target/heap.h>

#include "afbc.h"

// This example will run the infinite loop to process the firmware events. This
// variable also can be changed using a debugger session to stop the processing.
static volatile int32_t acamera_main_loop_active = 1;

int isp_post_sync_semaphore( void )
{
    /* Required by the ISP driver but no semaphore on microblaze needed. Dummy function. */
    return 0;
}

static void isp_cdma_init( void )
{
#if defined( ISP_HAS_MCFE_FSM )
    uint32_t pid_reg, pid_backup;
    uint32_t ctx_backup_physaddr = PHY_ADDR_CDMA;
    int i;

    // Initialize CDMA address.
    LOG( LOG_NOTICE, "Copying default register space to CDMA spaces..." );
    if ( PHY_ADDR_ISP == 0 || PHY_ADDR_CDMA == 0 ) {
        LOG( LOG_CRIT, "- Error, NULL address base. (ISP=%x, CDMA=%x)", PHY_ADDR_ISP, PHY_ADDR_CDMA );
    }

    // Load product ID on back-up space to check if it's loaded.
    pid_reg = acamera_isp_id_product_read( PHY_ADDR_ISP );
	if (pid_reg == 0)
		LOG( LOG_ERR, "PID is 0");
    pid_backup = acamera_isp_id_product_read( ctx_backup_physaddr );

    LOG( LOG_NOTICE, "- Product ID: REG = %x, BACKUP = %x", pid_reg, pid_backup );

    if ( pid_reg != pid_backup ) {
        // Make back-up of register init to ctx_backup_physaddr.
        LOG( LOG_NOTICE, "- Preparing CDMA base with default ISP registers on %x...", ctx_backup_physaddr );
        system_memcpy_phy2phy( ctx_backup_physaddr, PHY_ADDR_ISP, LEN_ADDR_ISP );
    }

    // Copy from CDMA base address to CDMA slot addresses, and assign isp_base for contexts.
    for ( i = 0; i < FIRMWARE_CONTEXT_NUMBER; i++ ) {
        settings[i].isp_base = PHY_ADDR_CDMA + LEN_ADDR_ISP + i * ( LEN_ADDR_ISP + LEN_ADDR_META );
		//remove copy from CDMA to slot cfg for load slot cfg by ddr backdoor by 10000058
        system_memcpy_phy2phy( settings[i].isp_base, ctx_backup_physaddr, LEN_ADDR_ISP );
        LOG( LOG_NOTICE, "- Base address for CTX#%02d to %x...", i, settings[i].isp_base );
    }
#endif
    // Otherwise, do nothing if MFCE fsm is not present
	//bypass frame stitch for linear sensor, because from the second frame, the frame stitch can be bypass in sensor_update_hw this driver, by 10000058
	acamera_isp_pipeline_bypass_frame_stitch_write(settings[0].isp_base, 1);
	uint32_t bpfs = acamera_isp_pipeline_bypass_frame_stitch_read( settings[0].isp_base);
	printf("bypass frame stich for linear sensor: %d\n", bpfs);
}
void hardware_validation_bypass_m2m()
{
	#define ISP0_BASE 0xE80C0000
	uint32_t base = ISP0_BASE;
	#define SLOT_BASE 0x61020000
	uint32_t slot_base = SLOT_BASE;
	//SLOT CFG
	system_isp_write_32(slot_base + 0x0000e044, 0x00000000);
	system_isp_write_32(slot_base + 0x0000e040, 0xF97FFFFC);
	system_isp_write_32(slot_base + 0x0000e720, 0x00000c9b);
	system_isp_write_32(slot_base + 0x0000e724, 0x00000010);
	system_isp_write_32(slot_base + 0x0000e728, 0x00000c9b);
	system_isp_write_32(slot_base + 0x0000e72c, 0x00000010);
	system_isp_write_32(slot_base + 0x0000e730, 0x00000c9b);
	system_isp_write_32(slot_base + 0x0000e734, 0x00000010);
	system_isp_write_32(slot_base + 0x0000e010, 0x000000b4);
	system_isp_write_32(slot_base + 0x0000e014, 0x000000b4);
	//RAW Buffer Configuration

	//RAW Buffer0

	//buffer configuration
	system_isp_write_32( base + 0x00000800, 0x00011001);
	//base address)
	system_isp_write_32( base + 0x00000804, 0x61100000);//0x01000000);
	//line offset)
	system_isp_write_32( base + 0x00000808, 0x00000180);
	//active width)
	system_isp_write_32( base + 0x0000080c, 0x000000B4);
	//active height )
	system_isp_write_32( base + 0x00000810, 0x000000B4);
	//status)
	system_isp_write_32( base + 0x00000818, 0x00000001);
	//Output Buffer Configuration)
	//Output Buffer0)
	//buffer configuration)
	system_isp_write_32( base + 0x00001000, 0x00011001);
	//base address)
	system_isp_write_32( base + 0x00001004, 0x60800000);//0x00200000);
	//line offset)
	system_isp_write_32( base + 0x00001008, 0x00000180);
	//active width)
	system_isp_write_32( base + 0x0000100c, 0x000000B4);
	//active height )
	system_isp_write_32( base + 0x00001010, 0x000000B4);
	//status)
	system_isp_write_32( base + 0x00001018, 0x00000000);
	//Output Buffer1)
	system_isp_write_32( base + 0x00001020, 0x00011001);
	system_isp_write_32( base + 0x00001024, 0x60810e00);//0x00600000);
	system_isp_write_32( base + 0x00001028, 0x00000180);
	system_isp_write_32( base + 0x0000102c, 0x000000B4);
	system_isp_write_32( base + 0x00001030, 0x000000B4);
	system_isp_write_32( base + 0x00001038, 0x00000000);
	//Output Buffer2)
	system_isp_write_32( base + 0x00001040, 0x00011001);
	system_isp_write_32( base + 0x00001044, 0x60821c00);//0x00A00000);
	system_isp_write_32( base + 0x00001048, 0x00000180);
	system_isp_write_32( base + 0x0000104c, 0x000000B4);
	system_isp_write_32( base + 0x00001050, 0x000000B4);
	system_isp_write_32( base + 0x00001058, 0x00000000);
	//MCFE Configurations)
	//schedular mode)
	system_isp_write_32( base + 0x00000414, 0x00000001);
	//MCFE input Configuration )
	system_isp_write_32( base + 0x00000680, 0x03030303);
	//MCFE FIFO Watermark )
	system_isp_write_32( base + 0x00000404, 0x03f0002E);
	system_isp_write_32( base + 0x00000408, 0x03f0002E);
	system_isp_write_32( base + 0x0000040c, 0x03f0002E);
	system_isp_write_32( base + 0x00000410, 0x03f0002E);
	//MCBE FIFO Watermark)
	system_isp_write_32( base + 0x0000072C, 0x00F000F0);
	system_isp_write_32( base + 0x00000730, 0x007800F0);
	//enable flow control)
	system_isp_write_32( base + 0x00000728, 0x00000001);
	//Slot0 configuration )
	//Slot0 Config DMA Configuration  )
	system_isp_write_32( base + 0x000004a0, 0x00000001);
	system_isp_write_32( base + 0x000004b0, 0x00010001);
	system_isp_write_32( base + 0x000004c0, 0x61020000);//0x00000000);
	system_isp_write_32( base + 0x00000500, 0x00020000);
	system_isp_write_32( base + 0x00000540, 0x00000000);
	system_isp_write_32( base + 0x00000580, 0x40000000);
	//slot0 input/output buffer numbers )
	system_isp_write_32( base + 0x000005c0, 0xFFFFFF00);
	system_isp_write_32( base + 0x00000600, 0xFF020100);
	system_isp_write_32( base + 0x00000640, 0xFFFFFFFF);
	//slot0 mode)
	system_isp_write_32( base + 0x00000430, 0x00000004);
	//Enable slot0 Interrupt )
	system_isp_write_32( base + 0x000000d0, 0x000FFFFF);
	system_isp_write_32( base + 0x000000d0, 0x00000000);
	system_isp_write_32( base + 0x000000C8, 0x00000010);
	//submit slot0 into processing queue)
	system_isp_write_32( base + 0x00000418, 0x000000FF);
	system_isp_write_32( base + 0x00000418, 0x00000000);
}
void hardware_validation()
{
	#define ISP0_BASE 0xE80C0000
	uint32_t base = ISP0_BASE;
	//RAW Buffer Configuration

	//RAW Buffer0

	//buffer configuration
	system_isp_write_32(base + 0x00000800, 0x00011001);
	uint32_t curr = system_isp_read_32(base + 0x00000800);
	printf("write raw buffer0 cfg done, curr = 0x%2x\n", curr);
	//base address
	system_isp_write_32(base + 0x00000804, 0x61100000);//0x01000000);
		//line offset
	system_isp_write_32(base + 0x00000808, 0x00000180);
		//active width
	system_isp_write_32(base + 0x0000080c, 0x000000B4);
		//active height
	system_isp_write_32(base + 0x00000810, 0x000000B4);
		//status
	system_isp_write_32(base + 0x00000818, 0x00000001);

		//RAW Buffer1
	system_isp_write_32(base + 0x00000820, 0x00011001);

	system_isp_write_32(base + 0x00000824, 0x61120000);//0x01200000);
	system_isp_write_32(base + 0x00000828, 0x00000180);
	system_isp_write_32(base + 0x0000082c, 0x000000B4);
	system_isp_write_32(base + 0x00000830, 0x000000B4);
	system_isp_write_32(base + 0x00000838, 0x00000001);

		//RAW Buffer2
	system_isp_write_32(base + 0x00000840, 0x00011001);
	system_isp_write_32(base + 0x00000844, 0x61140000);//0x01400000);
	system_isp_write_32(base + 0x00000848, 0x00000180);
	system_isp_write_32(base + 0x0000084c, 0x000000B4);
	system_isp_write_32(base + 0x00000850, 0x000000B4);
	system_isp_write_32(base + 0x00000858, 0x00000001);
	//Output Buffer Configuration

	//Output Buffer0

	//buffer configuration
	system_isp_write_32(base + 0x00001000, 0x00011001);
	//base address
	system_isp_write_32(base + 0x00001004, 0x60800000);//0x00200000);
	//line offset
	system_isp_write_32(base + 0x00001008, 0x00000180);
	//active width
	system_isp_write_32(base + 0x0000100c, 0x000000B4);
	//active height
	system_isp_write_32(base + 0x00001010, 0x000000B4);
	//status
	system_isp_write_32(base + 0x00001018, 0x00000000);

	//Output Buffer1
	system_isp_write_32(base + 0x00001020, 0x00011001);
	system_isp_write_32(base + 0x00001024, 0x60810e00);//0x00600000);
	system_isp_write_32(base + 0x00001028, 0x00000180);
	system_isp_write_32(base + 0x0000102c, 0x000000B4);
	system_isp_write_32(base + 0x00001030, 0x000000B4);
	system_isp_write_32(base + 0x00001038, 0x00000000);

	//Output Buffer2
	system_isp_write_32(base + 0x00001040, 0x00011001);
	system_isp_write_32(base + 0x00001044, 0x60821c00);//0x00A00000);
	system_isp_write_32(base + 0x00001048, 0x00000180);
	system_isp_write_32(base + 0x0000104c, 0x000000B4);
	system_isp_write_32(base + 0x00001050, 0x000000B4);
	system_isp_write_32(base + 0x00001058, 0x00000000);

	//MCFE Configurations

	//schedular mode
	system_isp_write_32(base + 0x00000414, 0x00000001);

	//MCFE input Configuration
	system_isp_write_32(base + 0x00000680, 0x03030303);


	//MCFE FIFO Watermark
	system_isp_write_32(base + 0x00000404, 0x03f001e0);
	system_isp_write_32(base + 0x00000408, 0x03f001e0);
	system_isp_write_32(base + 0x0000040c, 0x03f001e0);
	system_isp_write_32(base + 0x00000410, 0x03f001e0);

	system_isp_write_32(base + 0x00000400, 0x00010000);
	//enable flow control
	system_isp_write_32(base + 0x00000728, 0x00000001);
	system_isp_write_32(base + 0x0000072c, 0x00f000f0);
	system_isp_write_32(base + 0x00000730, 0x007000f0);
	//Slot0 configuration

	//Slot0 Config DMA Configuration
	system_isp_write_32(base + 0x000004a0, 0x00000001);
	system_isp_write_32(base + 0x000004b0, 0x00010001);
	system_isp_write_32(base + 0x000004c0, 0x61020000);//0x00000000);
	system_isp_write_32(base + 0x00000500, 0x00020000);
	system_isp_write_32(base + 0x00000540, 0x00000000);
	system_isp_write_32(base + 0x00000580, 0x40000000);
	//slot0 input/output buffer numbers
	system_isp_write_32(base + 0x000005c0, 0xFF020100);
	system_isp_write_32(base + 0x00000600, 0xFF020100);
	system_isp_write_32(base + 0x00000640, 0xFFFFFFFF);


	//slot0 mode
	system_isp_write_32(base + 0x00000430, 0x00000004);

	//Enable slot0 Interrupt
	system_isp_write_32(base + 0x000000d0, 0x000FFFFF);
	system_isp_write_32(base + 0x000000d0, 0x00000000);
	system_isp_write_32(base + 0x000000C8, 0x00000010);


	//submit slot0 into processing queue
	printf("start slot.\n");
	system_isp_write_32(base + 0x00000418, 0x000000FF);
	system_isp_write_32(base + 0x00000418, 0x00000000);
}

void slot_ddr_test()
{
	#define TEST_ADDR0 0x61100000
	#define TEST_ADDR1 0x61120000
	#define TEST_ADDR2 0x61140000
	#define TEST_ADDR3 0x6102e720
	uint32_t curr;
	printf("test ddr: ");
		curr = system_isp_read_32(TEST_ADDR0);
	printf("0x%2x,",curr);
		curr = system_isp_read_32(TEST_ADDR1);
	printf("0x%2x,",curr);
		curr = system_isp_read_32(TEST_ADDR2);
	printf("0x%2x,",curr);
		curr = system_isp_read_32(TEST_ADDR3);
	printf("0x%2x,",curr);
}

void c71_clock_init()
{
	#define CR_WRAP_TOP 0x058100000
#if 0//for P1038 RTL version
	#define CISP_SS_ISP_CORE_CLK 0xC2F00
	#define CISP_SS_AXI_CLK 0xC2F04
	#define CISP_SS_APB_CLK 0xC2F08
	#define CISP_SS_AHB_CLK 0xC2F0C
	#define CISP_SS_PIXEL_CLK 0xC2F10
#endif
	#define CISP_SS_ISP_CORE_CLK 0xE201C
	#define CISP_SS_GDC_CORE_CLK 0xE2020
	#define CISP_SS_AXI_CLK 0xC2F00
	#define CISP_SS_APB_CLK 0xC2F04
	#define CISP_SS_AHB_CLK 0xC2F08
	#define CISP_SS_PIXEL_CLK 0xC2F0C
	#define CISP_SS_DPHY_CLK  0xC2F10
	#define CISP_SS_DPHY_REFCLK 0xC2F14
	#define CISP_SS_RESETN 0xC3F00
	#define DEVICE_MANAGER 0x0E80F0000
    uint32_t curr = 0;

	uint32_t base = CR_WRAP_TOP;
	curr = system_isp_read_32( base + CISP_SS_ISP_CORE_CLK );
    system_isp_write_32( base + CISP_SS_ISP_CORE_CLK , ( ( ( uint32_t )( 1 << 8 ) | (1 << 16) | ( curr & 0xfffefeff) )));
    curr = system_isp_read_32( base + CISP_SS_ISP_CORE_CLK );
	printf("CISP_SS_ISP_CORE_CLK after: %2x.\n", curr);

	curr = system_isp_read_32( base + CISP_SS_GDC_CORE_CLK);
    system_isp_write_32( base + CISP_SS_GDC_CORE_CLK , ( ( ( uint32_t )( 1 << 8 ) | (1 << 16) | ( curr & 0xfffefeff) )));


	curr = system_isp_read_32( base + CISP_SS_AXI_CLK );
	uint32_t data = ( ( ( uint32_t )( 1 << 8 ) | (1 << 16) | ( curr & 0xfffefeff) ));
    system_isp_write_32( base + CISP_SS_AXI_CLK, data);
    //curr = system_isp_read_32( base + CISP_SS_AXI_CLK );

	curr = system_isp_read_32( base + CISP_SS_APB_CLK );
    system_isp_write_32( base + CISP_SS_APB_CLK, ( ( ( uint32_t )( 1 << 8 ) | (1 << 16) | ( curr & 0xfffefeff) )));
    //curr = system_isp_read_32( base + CISP_SS_APB_CLK);

	curr = system_isp_read_32( base + CISP_SS_AHB_CLK );
    system_isp_write_32( base + CISP_SS_AHB_CLK , ( ( ( uint32_t )( 1 << 8 ) | (1 << 16) | ( curr & 0xfffefeff) )));
    //curr = system_isp_read_32( base + CISP_SS_AHB_CLK );

	curr = system_isp_read_32( base + CISP_SS_PIXEL_CLK );
    system_isp_write_32( base + CISP_SS_PIXEL_CLK , ( ( ( uint32_t )( 1 << 8 ) | (1 << 16) | ( curr & 0xfffefeff) )));
    //curr = system_isp_read_32( base + CISP_SS_PIXEL_CLK );

	curr = system_isp_read_32( base + CISP_SS_DPHY_CLK );
    system_isp_write_32( base + CISP_SS_DPHY_CLK , ( ( ( uint32_t )( 1 << 8 ) | (1 << 16) | ( curr & 0xfffefeff) )));

	curr = system_isp_read_32( base + CISP_SS_DPHY_REFCLK );
    system_isp_write_32( base + CISP_SS_DPHY_REFCLK , ( ( ( uint32_t )( 1 << 8 ) | (1 << 16) | ( curr & 0xfffefeff) )));

	curr = system_isp_read_32( base + CISP_SS_RESETN);
    system_isp_write_32( base + CISP_SS_RESETN, (uint32_t)(curr & 0xfffffffe));
    curr = system_isp_read_32( base + CISP_SS_RESETN);
	printf("CISP_SS_RESETN after: %2x.\n", curr);
	system_isp_write_32(DEVICE_MANAGER, 0x1);
}
void c71_with_smmu_start_rgb32()
{
	#define ISP0_BASE 0xE80C0000
	uint32_t base = ISP0_BASE;
	//RAW Buffer Configuration

	//RAW Buffer0

	//buffer configuration
	system_isp_write_32(base + 0x00000800, 0x00011001);
	uint32_t curr = system_isp_read_32(base + 0x00000800);
	printf("write raw buffer0 cfg done, curr = 0x%2x\n", curr);
	//base address
	system_isp_write_32(base + 0x00000804, 0x61100000);//0x01000000);
		//line offset
	system_isp_write_32(base + 0x00000808, 0x00000a00);
		//active width
	system_isp_write_32(base + 0x0000080c, 0x00000500);
		//active height
	system_isp_write_32(base + 0x00000810, 0x000003c0);
		//status
	system_isp_write_32(base + 0x00000818, 0x00000001);

	//Output Buffer Configuration

	//Output Buffer0

	//buffer configuration
	system_isp_write_32(base + 0x00001000, 0x00002001);
	//base address
	system_isp_write_32(base + 0x00001004, 0x60100000);//0x00200000);
	//line offset
	system_isp_write_32(base + 0x00001008, 0x00001400);
	//active width
	system_isp_write_32(base + 0x0000100c, 0x00000500);
	//active height
	system_isp_write_32(base + 0x00001010, 0x000003c0);
	//status
	system_isp_write_32(base + 0x00001018, 0x00000000);

	//MCFE Configurations

	//schedular mode
	system_isp_write_32(base + 0x00000414, 0x00000001);

	//MCFE input Configuration
	system_isp_write_32(base + 0x00000680, 0x03030303);


	//MCFE FIFO Watermark
	system_isp_write_32(base + 0x00000404, 0x03f001e0);
	system_isp_write_32(base + 0x00000408, 0x03f001e0);
	system_isp_write_32(base + 0x0000040c, 0x03f001e0);
	system_isp_write_32(base + 0x00000410, 0x03f001e0);

	system_isp_write_32(base + 0x00000400, 0x00010000);
	//enable flow control
	system_isp_write_32(base + 0x00000728, 0x00000001);
	system_isp_write_32(base + 0x0000072c, 0x00f000f0);
	system_isp_write_32(base + 0x00000730, 0x007000f0);
	//Slot0 configuration

	//Slot0 Config DMA Configuration
	system_isp_write_32(base + 0x000004a0, 0x00000001);
	system_isp_write_32(base + 0x000004b0, 0x00010001);
	system_isp_write_32(base + 0x000004c0, 0x61020000);//0x00000000);
	system_isp_write_32(base + 0x00000500, 0x00020000);
	system_isp_write_32(base + 0x00000540, 0x00000000);
	system_isp_write_32(base + 0x00000580, 0x40000000);
	//slot0 input/output buffer numbers
	system_isp_write_32(base + 0x000005c0, 0xFFFFFF00);
	system_isp_write_32(base + 0x00000600, 0xFFFFFF00);
	system_isp_write_32(base + 0x00000640, 0xFFFFFFFF);


	//slot0 mode
	system_isp_write_32(base + 0x00000430, 0x00000004);

	//Enable slot0 Interrupt
	system_isp_write_32(base + 0x000000d0, 0x000FFFFF);
	system_isp_write_32(base + 0x000000d0, 0x00000000);
	system_isp_write_32(base + 0x000000C8, 0x00000010);


	//submit slot0 into processing queue
	printf("start slot.\n");
	system_isp_write_32(base + 0x00000418, 0x000000FF);
	system_isp_write_32(base + 0x00000418, 0x00000000);
}
void c71_with_afbc_start_rgb32()
{
	#define ISP0_BASE 0xE80C0000
	uint32_t base = ISP0_BASE;
	//RAW Buffer Configuration

	//RAW Buffer0

	//buffer configuration
	system_isp_write_32(base + 0x00000800, 0x00011001);
	uint32_t curr = system_isp_read_32(base + 0x00000800);
	printf("write raw buffer0 cfg done, curr = 0x%2x\n", curr);
	//base address
	system_isp_write_32(base + 0x00000804, 0x61100000);//0x01000000);
		//line offset
	system_isp_write_32(base + 0x00000808, 0x00000a00);
		//active width
	system_isp_write_32(base + 0x0000080c, 0x00000500);
		//active height
	system_isp_write_32(base + 0x00000810, 0x000003c0);
		//status
	system_isp_write_32(base + 0x00000818, 0x00000001);

	//Output Buffer Configuration

	//Output Buffer0

	//buffer configuration
	system_isp_write_32(base + 0x00001000, 0x00002001);
	//base address
	system_isp_write_32(base + 0x00001004, 0xf0200000); //0x60800000);//0x00200000);
	//line offset
	system_isp_write_32(base + 0x00001008, 0x00001400);
	//active width
	system_isp_write_32(base + 0x0000100c, 0x00000500);
	//active height
	system_isp_write_32(base + 0x00001010, 0x000003c0);
	//status
	system_isp_write_32(base + 0x00001018, 0x00000000);

	//MCFE Configurations

	//schedular mode
	system_isp_write_32(base + 0x00000414, 0x00000001);

	//MCFE input Configuration
	system_isp_write_32(base + 0x00000680, 0x03030303);


	//MCFE FIFO Watermark
	system_isp_write_32(base + 0x00000404, 0x03f001e0);
	system_isp_write_32(base + 0x00000408, 0x03f001e0);
	system_isp_write_32(base + 0x0000040c, 0x03f001e0);
	system_isp_write_32(base + 0x00000410, 0x03f001e0);

	system_isp_write_32(base + 0x00000400, 0x00010000);
	//enable flow control
	system_isp_write_32(base + 0x00000728, 0x00000001);
	system_isp_write_32(base + 0x0000072c, 0x00f000f0);
	system_isp_write_32(base + 0x00000730, 0x007000f0);
	//Slot0 configuration

	//Slot0 Config DMA Configuration
	system_isp_write_32(base + 0x000004a0, 0x00000001);
	system_isp_write_32(base + 0x000004b0, 0x00010001);
	system_isp_write_32(base + 0x000004c0, 0x61020000);//0x00000000);
	system_isp_write_32(base + 0x00000500, 0x00020000);
	system_isp_write_32(base + 0x00000540, 0x00000000);
	system_isp_write_32(base + 0x00000580, 0x40000000);
	//slot0 input/output buffer numbers
	system_isp_write_32(base + 0x000005c0, 0xFFFFFF00);
	system_isp_write_32(base + 0x00000600, 0xFFFFFF00);
	system_isp_write_32(base + 0x00000640, 0xFFFFFFFF);


	//slot0 mode
	system_isp_write_32(base + 0x00000430, 0x00000004);

	//Enable slot0 Interrupt
	system_isp_write_32(base + 0x000000d0, 0x000FFFFF);
	system_isp_write_32(base + 0x000000d0, 0x00000000);
	system_isp_write_32(base + 0x000000C8, 0x00000010);


	//submit slot0 into processing queue
	printf("start slot.\n");
	system_isp_write_32(base + 0x00000418, 0x000000FF);
	system_isp_write_32(base + 0x00000418, 0x00000000);
}
void c71_with_afbc_start_yuv420()
{
	#define ISP0_BASE 0xE80C0000
	uint32_t base = ISP0_BASE;
	//RAW Buffer Configuration

	//RAW Buffer0

	//buffer configuration
	system_isp_write_32(base + 0x00000800, 0x00011001);
	uint32_t curr = system_isp_read_32(base + 0x00000800);
	printf("write raw buffer0 cfg done, curr = 0x%2x\n", curr);
	//base address
	system_isp_write_32(base + 0x00000804, 0x61100000);
	//line offset
	system_isp_write_32(base + 0x00000808, 0x00000a00); //0x200);//
		//active width
	system_isp_write_32(base + 0x0000080c, 0x00000500); //0x100);//
		//active height
	system_isp_write_32(base + 0x00000810, 0x000003c0); //0x100);//
		//status
	system_isp_write_32(base + 0x00000818, 0x00000001);

	//Output Buffer Configuration

	//Output Buffer0

	//buffer configuration
	system_isp_write_32(base + 0x00001000, 0x00010801);
	//base address
	system_isp_write_32(base + 0x00001004, 0xf0200000);
	//line offset
	system_isp_write_32(base + 0x00001008, 0x00000500);//0x100);//
	//active width
	system_isp_write_32(base + 0x0000100c, 0x00000500);//0x100);//
	//active height
	system_isp_write_32(base + 0x00001010, 0x000003c0);//0x100);//
	//status
	system_isp_write_32(base + 0x00001018, 0x00000000);

	 //Output Buffer1
	system_isp_write_32(base + 0x00001020, 0x00011001);
	system_isp_write_32(base + 0x00001024, 0xf0600000);
	system_isp_write_32(base + 0x00001028, 0x00000500);//0x100);//
	system_isp_write_32(base + 0x0000102c, 0x00000280);//0x80);//
	system_isp_write_32(base + 0x00001030, 0x000001e0);//0x80);//
	system_isp_write_32(base + 0x00001038, 0x00000000);


	//MCFE Configurations

	//schedular mode
	system_isp_write_32(base + 0x00000414, 0x00000001);

	 //MCFE input Configuration
	system_isp_write_32(base + 0x00000680, 0x03030303);


	//MCFE FIFO Watermark
	system_isp_write_32(base + 0x00000404, 0x03f001e0);
	system_isp_write_32(base + 0x00000408, 0x03f001e0);
	system_isp_write_32(base + 0x0000040c, 0x03f001e0);
	system_isp_write_32(base + 0x00000410, 0x03f001e0);

	system_isp_write_32(base + 0x00000400, 0x00010000);
	 //enable flow control
	system_isp_write_32(base + 0x00000728, 0x00000001);
	system_isp_write_32(base + 0x0000072c, 0x00f000f0);
	system_isp_write_32(base + 0x00000730, 0x007000f0);
	//Slot0 configuration

	//Slot0 Config DMA Configuration
	system_isp_write_32(base + 0x000004a0, 0x00000001);
	system_isp_write_32(base + 0x000004b0, 0x00010001);
	system_isp_write_32(base + 0x000004c0, 0x61020000);
	system_isp_write_32(base + 0x00000500, 0x00020000);
	system_isp_write_32(base + 0x00000540, 0x00000000);
	system_isp_write_32(base + 0x00000580, 0x40000000);
	//slot0 input/output buffer numbers
	system_isp_write_32(base + 0x000005c0, 0xFFFFFF00);
	system_isp_write_32(base + 0x00000600, 0xFFFF0100);
	system_isp_write_32(base + 0x00000640, 0xFFFFFFFF);


	//slot0 mode
	system_isp_write_32(base + 0x00000430, 0x00000004);

	//Enable slot0 Interrupt
	system_isp_write_32(base + 0x000000d0, 0x000FFFFF);
	system_isp_write_32(base + 0x000000d0, 0x00000000);
	system_isp_write_32(base + 0x000000C8, 0x00000010);


	//submit slot0 into processing queue
	printf("start slot.\n");
	system_isp_write_32(base + 0x00000418, 0x000000FF);
	system_isp_write_32(base + 0x00000418, 0x00000000);
}
// The basic example of usage ACamera firmware is given below.
extern bool smmu_buf_init(void);
extern void smmu_init(uint64_t smmu_base, int sid);
extern int heap_switch_direct(uintptr_t addr1, uintptr_t addr2);
int cmd_c71(int argc, char **argv)
{
	if (argc < 2)
		return -EUSAGE;
    int32_t result = 0;

    // Enable instruction and data cache first
    system_inst_cache_enable();
    system_data_cache_enable();

// ACamera provides a simple protocol to communicate with firmware
// outside application. Several channels are supported depend on the
// system requirements.
// To start using ACamera Control Tool the connection must be initialised
// before by calling acamera_connection_init
// The connection module parses input commands from ACT and call the required
// api command like acamera_command or acamera_calibrations.
// Please see acamera_command_api.h for details.
#if ISP_HAS_STREAM_CONNECTION
    acamera_connection_init();
#endif

    // Register frame consumer module. Sets up callback to the frame streamer to
    // get notification on a new raw or output frame ready to be fetched
    result = frame_consumer_initialize();

    // The firmware supports multicontext.
    // It means that the customer can use the same firmware for controlling
    // several instances of different sensors. To initialise a context
    // the structure acamera_settings must be filled properly.
    // External application must save returned contexts and
    // use it every time the api command is called.
    // Please note that the pointer to a context
    // will be passed to all callbacks and can be used
    // to differentiate among them.
	if (argv[1][0] == 't')
	{
		LOG(LOG_INFO, "test 0x61100000 DDR begin.\n");
		#define DDR_TEST_ADDR0 0x61100000
		#define DDR_TEST_ADDR1 0x61120000
		#define DDR_TEST_ADDR2 0x61140000
		#define DDR_TEST_SLOT  0x6102e738
		//unsigned int *data1 = ((unsigned int*)(DDR_TEST_ADDR));
		uint32_t curr;
		printf("r/w slot addr.\n");
		for (int k=0;k<16;k++)
		{
			curr = system_isp_read_32(DDR_TEST_SLOT + k * 4);
			printf("0x%2x ", curr);
			system_isp_write_32(DDR_TEST_SLOT + k * 4, 0x55115511 + k);
		}
		printf("\n");
		for (int k=0;k<16;k++)
		{
			curr = system_isp_read_32(DDR_TEST_ADDR0 + k * 4);
			LOG(LOG_INFO, "0x%2x.", curr);
			system_isp_write_32(DDR_TEST_ADDR0 + k * 4, 0x12345678 + k);
		}
		LOG(LOG_DEBUG, "\n");
		for (int k=0;k<16;k++)
		{
			curr = system_isp_read_32(DDR_TEST_ADDR1 + k * 4);
			LOG(LOG_INFO, "0x%2x.", curr);
		}
		LOG(LOG_DEBUG, "\n");
		for (int k=0;k<16;k++)
		{
			curr = system_isp_read_32(DDR_TEST_ADDR2 + k * 4);
			LOG(LOG_INFO, "0x%2x.", curr);
		}
		LOG(LOG_INFO, "test 0x61100000 DDR end.\n");
	}
	else if (argv[1][0] == 'i')
	{
		LOG(LOG_INFO, "c71 init begin.\n");
		c71_clock_init();
    	isp_cdma_init();
    	result = acamera_init( settings, FIRMWARE_CONTEXT_NUMBER, NULL );
    	if ( result == 0 )
		{
			LOG(LOG_INFO, "c71 init complete.\n");
		}
    	acamera_deinit();
		LOG(LOG_INFO, "c71 init end.\n");
	}
	else if (argv[1][0] == 'd') {
		LOG(LOG_NOTICE, "c71 dv case start begin.\n");
    	if ( result == 0 ) {
			c71_clock_init();
    	    bsp_init();
			hardware_validation();
			//hardware_validation_bypass_m2m();
			while(1)
			{
			}
		}
	}
	else if (argv[1][0] == 'a') {
		LOG( LOG_NOTICE, "c71 with afbc test for yuv420");
		c71_clock_init();
		read_afbc_product_id_and_version();
		afbc_init_yuv420();
		//afbc_encode_period(1);
		bsp_init_dv_case();
		c71_with_afbc_start_yuv420();
		while(1)
		{
		}
	}
	else if (argv[1][0] == 'e') {	//afbc encoder
		LOG( LOG_NOTICE, "c71 with afbc test for rgb32");
		c71_clock_init();
		read_afbc_product_id_and_version();
		afbc_init_rgb32();
		//afbc_encode_period(0);
		bsp_init_dv_case();
		c71_with_afbc_start_rgb32();
		while(1)
		{
		}
	}
	else if (argv[1][0] == 'm') {	//afbc encoder
		LOG( LOG_NOTICE, "c71 with smmu test for rgb32");
		c71_clock_init();
		//read_afbc_product_id_and_version();
		//afbc_init_rgb32();
		bsp_init_dv_case();
		//smmu init
		LOG( LOG_NOTICE, "smmu init.");
		phys_addr_t smmu_base;
		struct arm_smmu_device* smmu;
		//define your specific smmu base address
		#define C71_SMMU_BASE 0xE8200000
		smmu_base = C71_SMMU_BASE;
		//sram can't be touched by eth smmu, workaround
		heap_switch_direct(0x61400000, 0x61f00000);
		if( smmu_buf_init() )
		{
			smmu_init(smmu_base, 0x1C);
			//smmu_init(smmu_base, 0x1D);
		}
		LOG( LOG_NOTICE, "smmu init end.");
		c71_with_smmu_start_rgb32();
		while(1)
		{
		}
	}
	else if (argv[1][0] == 's') {
		LOG(LOG_NOTICE, "c71 start begin.\n");
    	if ( result == 0 ) {
			c71_clock_init();
    	    bsp_init();
    	    isp_cdma_init();
    	    result = acamera_init( settings, FIRMWARE_CONTEXT_NUMBER, NULL );
			//config afbc
			#if defined(AFBC_ENABLE)
				result += afbc_encoder_init();
				result += afbc_encoder_config(2);
			#endif
    	}

    	if ( result == 0 ) {
    	    // acamera_process_event function must be called on every incoming interrupt
    	    // to give the firmware the possibility to apply
    	    // all internal algorithms and change the ISP state.
    	    // The external application can be run in the same loop on bare metal systems.
    	    while ( acamera_main_loop_active ) {
    	        // acamera_process_event must be called for each initialised context
    	        acamera_process_event();

#if 0//ISP_HAS_STREAM_CONNECTION
    	        // acamera_connection_process is used for communication between
    	        // firmware and ACT through different possible channels like
    	        // cmd_queue memory in ISP, socket, UART, chardev etc.
    	        // Different channels can be supported depending on the target
    	        // platform. The common case when cmd_queue buffer is used
    	        // ( see acamera_isp_config.h )
    	        // The channels supported by this routine can be used not only on
    	        // NIOS2 platform but on the customer system as well.
    	        acamera_connection_process();
#endif
    	        // Flush data cache after every process, ISP settings in RAM need to be up to date.
    	        // before CDMA starts with operation
    	        system_data_cache_flush();
    	    }
    	    acamera_deinit();
    	    bsp_destroy();
    	}
		else {
    	    LOG( LOG_ERR, "Failed to start firmware processing thread. " );
    	}
		LOG(LOG_INFO, "c71 start end.\n");
	}
    return 0;
}

MK_CMD(c71,cmd_c71,"Control ARM C71",
	"c71 test\n"
	"	 - test ddr\n"
	"c71 init\n"
	"    - initialize c71\n"
	"c71 dv\n"
	"    - test c71 dv cases without driver\n"
	"c71 start\n"
	"    - start c71 with driver\n"
	"c71 afbc\n"
	"    - start c71 and afbc with yuv420\n"
	"c71 encoder\n"
	"    - start c71 and afbc with rgb32\n"
);
