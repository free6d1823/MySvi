#ifndef __GDC_H__
#define __GDC_H__

#include <target/regdef.h>

/*************************************************
** GDC Register Map
**************************************************/
#define GDC_REGISTER_SIZE (0x100)
#define GDC_REG_ID			(0x00)
#define GDC_REG_CONFIG_ADDR		(0x10) 	/* Base address of configuration stream */
#define GDC_REG_CONFIG_SIZE		(0x14)	/* Size of the configuration stream*/
#define GDC_REG_DATAIN_WIDTH	(0x20)	/* Width of the input image [15:0]*/
#define GDC_REG_DATAIN_HEIGHT	(0x24)	/* Height of the input image [15:0]*/
#define GDC_REG_DATA1IN_ADDR	(0x28)	/* Base address of the 1st plane in the input frame buffer*/
#define GDC_REG_DATA1IN_LINE_OFFSET	(0x2c)	/* stride of 1st plane, in bytes */
#define GDC_REG_DATA2IN_ADDR		(0x30)	/* Base address of the 2nd plane in the input frame buffer*/
#define GDC_REG_DATA2IN_LINE_OFFSET	(0x34)	/* stride of 2nd plane, in bytes */
#define GDC_REG_DATA3IN_ADDR		(0x38)	/* Base address of the 3rd plane in the input frame buffer*/
#define GDC_REG_DATA3IN_LINE_OFFSET	(0x3C)	/* stride of 3nd plane, in bytes */
#define GDC_REG_DATAOUT_WIDTH	(0x40)	/* Width of the output image [15:0]*/
#define GDC_REG_DATAOUT_HEIGHT	(0x44)	/* Height of the output image [15:0]*/
#define GDC_REG_DATA1OUT_ADDR	(0x48)	/* Base address of the 1st plane in the output frame buffer*/
#define GDC_REG_DATA1OUT_LINE_OFFSET	(0x4c)	/* stride of 1st plane, in bytes */
#define GDC_REG_DATA2OUT_ADDR			(0x50)	/* Base address of the 2nd plane in the output frame buffer*/
#define GDC_REG_DATA2OUT_LINE_OFFSET	(0x54)	/* stride of 2nd plane, in bytes */
#define GDC_REG_DATA3OUT_ADDR			(0x58)	/* Base address of the 3rd plane in the output frame buffer*/
#define GDC_REG_DATA3OUT_LINE_OFFSET	(0x5C)	/* stride of 3nd plane, in bytes */
#define GDC_REG_STATUS		(0x60)	/* GDC status*/
#define GDC_REG_COMMAND		(0x64)	/* GDC operation commands */
#define GDC_REG_SUPPORTS	(0x68)	/* Supported features*/
#define GDC_REG_DEFAULT_CH1	(0x70)	/* Default value for 1st data channel (Y/R color)*/
#define GDC_REG_DEFAULT_CH2	(0x74)	/* Default value for 1st data channel (U/G color)*/
#define GDC_REG_DEFAULT_CH3	(0x78)	/* Default value for 1st data channel (V/B color)*/

/* GDC_REG_STATUS bit definition */
#define GDC_STATUS_BUSY			(0x00000001) /* Busy 1 = processing in progress, 0 = ready for next image */
#define GDC_STATUS_ERROR		(0x00000002) /* Error flag: last operation was finished with error (see bits 15:8) */
#define GDC_ERROR_CONFIGURATION	(0x00000100) /* Configuration error (wrong configuration stream) */
#define GDC_ERROR_USER_ABORT	(0x00000200) /* User abort (stop/reset command) */
#define GDC_ERROR_AXI_READER	(0x00000400) /* AXI reader error (e.g. error code returned by fabric) */
#define GDC_ERROR_AXI_WRITER	(0x00000800) /* AXI writer error */
#define GDC_ERROR_UNALIGNED		(0x00001000) /* Unaligned access (address pointer is not aligned) */
#define GDC_ERROR_INCOMPATIBLE	(0x00002000) /* Incompatible configuration (request of unimplemented mode of operation */
/* GDC_REG_COMMAND bit definition */
#define GDC_START_FLAG		(0x00000001) /* Transition from 0 to 1 starts the processing */
#define GDC_STOP_FLAG		(0x00000002)	/* 1 means to abandon the current frame and prepare for processing of the next frame. */
/* GDC_REG_SUPPORTS bit definition */
#define GDC_FEATURE_8BIT_DATA	(0x00000001) /* 8 bit data supported */
#define GDC_FEATURE_10BIT_DATA	(0x00000002) /* 10 bit data supported */
#define GDC_FEATURE_GRAYSCALE	(0x00000004) /* Ggrayscale supported */
#define GDC_FEATURE_RGBA888		(0x00000008) /* RGBA8:8:8/YUV4:4:4 mode supported */
#define GDC_FEATURE_RGB_PLANAR	(0x00000010) /* RGB/YUV444 planar modes supported */
#define GDC_FEATURE_YUV_SEMIPLANAR	(0x00000020) /* YUV semiplanar modes supported */
#define GDC_FEATURE_YUV422_LINEAR	(0x00000040) /* YUV4:2:2 linear mode supported (16 bit/pixel) */
#define GDC_FEATURE_RGB10_10_10		(0x00000080) /* RGB10:10:10 mode supported */
#define GDC_FEATURE_BICUBIC_INTERPOLATION	(0x00000100) /* 4 Tap Bicubic interpolation supported */
#define GDC_FEATURE_BILINEAR_MODE1	(0x00000200) /* Bilinear interpolation mode 1 supported {for U,V components} */
#define GDC_FEATURE_BILINEAR_MODE2	(0x00000400) /* Bilinear interpolation mode 2 supported {for U,V components} */
#define GDC_FEATURE_OUTPUT_INTERPOLATION	(0x00000800) /* output of interpolation coordinates is supported */
#define GDC_FEATURE_OUTPUT_CACHE_SIZE		(0x00070000) /* log2(size of output cache in lines)-5, (0 - 32lines, 1 - 64 lines etc) */
#define GDC_FEATURE_TILE_CACHE_SIZE		(0x00f80000) /* log2(size of tile cache in 16x16 clusters) */
#define GDC_FEATURE_POLYPHASS_FILTER	(0x07000000) /* Number of polyphase filter banks [2:0], log2(number of polyphase filter banks) */
#define GDC_FEATURE_AXI_DATA_WIDTH		(0x38000000) /* AXI data width [2:0] log2(AXI_DATA_WIDTH)-5 */

#endif /* __GDC_H__ */
