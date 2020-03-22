#ifndef __VC8000E_H__
#define __VC8000E_H__

#include <target/regdef.h>

#define SWREG0				0x0000
#define SWREG1				0x0004
#define SWREG4				0x0010
#define SWREG5				0x0014
#define SWREG80				0x0140
#define SWREG214			0x0358

/* SWREG0: ID Register */
#define PRODUCT_ID(id)		((id >> 16) & 0xFFFF)
#define ENC_HW_ID1			0x8000
#define ENC_HW_ID2			0x4832
#define MAJOR_NUMBER(id)	((id & 0x0000FF00) >>8)
#define MINOR_NUMBER(id)	(id & 0x000000FF)
/* SWREG1: Interrupt Register */
#define SW_ENC_TIMEOUT_INT		0x00000800	//enable timeout interrupt when 1
#define SW_ENC_IRQ_FUSE_ERROR	0x00000200	//Interrupt Interrupt status bit encoder. When this bit is high encoder has a FUSE error. SW try to setup feature but HW miss the feature set
#define SW_ENC_SLICE_RDY_STATUS	0x00000100	//Interrupt status bit encoder. When this bit is high encoder has encoded a slice.
#define SW_ENC_IRQ_LINE_BUFFER	0x00000080	//Interrupt status bit encoder linebuffer empty. When setting. Encoder has finished encoding input buffers.
#define SW_ENC_TIMEOUT 			0x00000040	//Interrupt status bit encoder timeout. When high the encoder has been idling for too long. Possible only if timeout interrupt is enabled
#define SW_ENC_BUFFER_FULL		0x00000020	//IRQ buffer full status bit. bufferFullInterrupt
#define SW_ENC_SW_RESET			0x00000010	//IRQ SW reset status bit.
#define SW_ENC_BUS_ERROR_STATUS 0x00000008	//Interrupt status bit bus. Error response from bus.
#define SW_ENC_FRAME_RDY_STATUS 0x00000004	//Interrupt status bit encoder. When this bit is high encoder has encoded a picture.
#define SW_ENC_IRQ_DIS			0x00000002	//Encoder IRQ disable. When high there are no interrupts concerning encoder from HW. Polling must be used to see the interrupt statuses.
#define SW_ENC_IRQ			0x00000001	//Encoder IRQ. When high encoder requests an interrupt. SW will reset this after interrupt is handled.
/* SWREG4: Control Register 0 */
#define SW_ENC_MODE				0xE0000000	//Encoding mode. streamType.1=hevc. 2=h264. 4=jpeg
#define SW_ENC_MIN_CB_SIZE		0x06000000	//RO min cb size:0-8x8:1-16x16:2-32x32:3-64x64:we only support 8x8
#define SW_ENC_MAX_CB_SIZE		0x01800000	//RO max cb size:0-8x8:1-16x16:2-32x32:3-64x64:we only support 64x64
#define SW_ENC_MIN_TRB_SIZE		0x00600000	//RO min tr block size:0-4x4:1-8x8:2-16x16:3-32x32:we only support 4x4
#define SW_ENC_MAX_TRB_SIZE		0x00180000	//RO max tr block size:0-4x4:1-8x8:2-16x16:3-32x32:we only support 16x16
#define SW_ENC_OUTPUT_STRIM_MODE	0x00040000 //output stream mode:0-byte stream:1-Nal stream
#define SW_ENC_CHROMA_QP_OFFSET		0x0003E000 //chroma qp offset[-12~12]
#define SW_ENC_STRONG_INTRA_SMOOTHING_ENABLED_FLAGE	0x00001000 //HEVC IntraTU32x32 strong intra smoothing filter enable flag

#define SW_ENC_SCALING_LIST_ENABLED_FLAG		0x00000100 //sw_enc_scaling_list_enabled_flag
#define SW_ENC_ACTIVE_OVERRIDE_FLAG				0x00000080	//active override flag
#define SW_ENC_SAO_ENABLE						0x00000040	//SAO enable
#define SW_ENC_MAX_TRANS_HIERARCHY_DEPTH_INTRA	0x00000038	//max transform hierarchy depth of intra
#define SW_ENC_MAX_TRANS_HIERARCHY_DEPTH_INTER	0x00000007	//max transform hierarchy depth of inter

/* SWREG5: Control Register 1 */
#define SW_ENC_JPEG_PIC_WIDTH	0xFFF00000	//Encoded jpeg width. jpgLumWidth(unit 8 pixels)
#define SW_ENC_JPEG_PIC_HEIGHT 	0x000FFF00	//Encoded jpeg height. jpgLumHeight(unit 8 pixels):Max width x height is 16384 x 16384
#define SW_ENC_PIC_WIDTH		0xFFC00000	//Encoded width. lumWidthLsb(unit 8 pixels). bit[9:0]
#define SW_ENC_PIC_HEIGHT		0x003FF800	//Encoded height. lumHeight(unit 8 pixels):Max width x height is 4096 x 4096
#define SW_ENC_PPS_DEBLOCKING_FILTER_OVERRIDE_ENABLED_FLAG	0x00000200	//deblocking filter override enable flag.0:disable 1:enable
#define SW_ENC_SLICE_DEBLOCKING_FILTER_OVERRIDE_FLAG		0x00000100	//slice deblocking filter override flag.0:no 1:yes
#define SW_ENC_OUTPUT_CU_INFO_ENABLED		0x00000040	//Enable dumping cu information to external memory.0:disable 1:enable
#define SW_ENC_BUFFER_FULL_CONTINUE			0x00000020	//Reserved for future. Not used now.
#define SW_ENC_REF_FRAMES					0x00000018	//Reserved for future. Not used now.
#define SW_ENC_FRAME_CODING_TYPE			0x00000006	//Encoded picture type. frameType.:1-I:0-P:2:B
#define SW_ENC_E				0x00000001	//encoder enable. Setting this bit high will start the encoding operation. HW will reset this when picture is processed or bus error or timeout interrupt is given.


/* AFBC decoder */


#define REG_BLOCK_ID	    0x000	/* BLOCK_ID 0x03012001 see 2.4.3*/
#define REG_IRQ_RAW_STATUS	0x004
#define REG_IRQ_CLEAR		0x008
#define REG_IRQ_MASK        0x00C
#define REG_IRQ_STATUS      0x010
#define REG_COMMAND         0x014
#define REG_STATUS          0x018

#endif /* __VC8000E_H__ */
