#ifndef __VC8000D_H__
#define __VC8000D_H__

#include <target/regdef.h>

#define DEC_HW_ID1			0x8001

#define DWL_CLIENT_TYPE_H264_DEC    1U
#define DWL_CLIENT_TYPE_MPEG4_DEC   2U
#define DWL_CLIENT_TYPE_JPEG_DEC    3U
#define DWL_CLIENT_TYPE_PP          4U
#define DWL_CLIENT_TYPE_VC1_DEC     5U
#define DWL_CLIENT_TYPE_MPEG2_DEC   6U
#define DWL_CLIENT_TYPE_VP6_DEC     7U
#define DWL_CLIENT_TYPE_AVS_DEC     8U
#define DWL_CLIENT_TYPE_RV_DEC      9U
#define DWL_CLIENT_TYPE_VP8_DEC     10U
#define DWL_CLIENT_TYPE_VP9_DEC     11U
#define DWL_CLIENT_TYPE_HEVC_DEC    12U

//#define DWL_HJPEG_E         17//




#define DWL_G2_HEVC_E       0
#define DWL_G2_VP9_E        1
#define DWL_G2_RFC_E        2
#define DWL_RFC_E           17
#define DWL_G2_DS_E         3
#define DWL_DS_E            28
#define DWL_HEVC_VER        8
#define DWL_VP9_PROFILE     12
#define DWL_RING_E          16

#define HANTRODEC_ID_REGISTER   0
#define HANTRODEC_IRQ_STAT_DEC  1
#define HANTRODEC_SYNTH_CFG     50
#define HANTRODEC_SYNTH_CFG2    54
#define HANTRODEC_SYHTN_CFG3    56
#define HANTRODEC_CFG_STAT      23
#define HANTRODECPP_CFG_STAT    260
#define HANTRODEC_HW_BUILD_ID   309

/* SWREG0: ID Register */
#define PRODUCT_ID(id)		((id >> 16) & 0xFFFF)
#define MAJOR_NUMBER(id)	((id & 0x0000FF00) >>8)
#define MINOR_NUMBER(id)	(id & 0x000000FF)

/* swreg1 */
#define HANTRO_DEC_E            0x01
#define HANTRO_DEC_IRQ_DISABLE  0x10
#define HANTRO_DEC_ABORT        0x20
#define HANTRO_DEC_IRQ          0x100
#define HANTRO_DEC_RDY_INIT     0x1000


/* swreg50 */
#define DWL_MPEG2_E         31  /* 1 bit */
#define DWL_VC1_E           29  /* 1: simple, 2: main, 3: advanced, 0: no */
#define DWL_JPEG_E          28  /* 1 bit */

#define DWL_MPEG4_E         26  /* 1: simple, 2: advanced, 0: no */
#define DWL_H264_E          24  /* 1: baseline, 2: high-, 3: high, 0: no */
#define DWL_VP6_E           23  /* 1 bit */
#define DWL_H264HIGH10_E    20  /* H264 High10P profile */
#define DWL_AVS2_E          18  /* 1: main, 2: main10, 0: no */
#define DWL_MAX_OWIDTH      0   /* Max video resolution. 16 bits */
/* swreg54 */
#define DWL_H264_PIPELINE_E 31
#define DWL_JPEG_PIPELINE_E 30
#define DWL_DIVX_E          29
#define DWL_RV_E            26 /* 0:no 1:yes 2:NA */
#define DWL_VP7_E           24
#define DWL_VP8_E           23
#define DWL_AVS_E           22
#define DWL_WEBP_E          19


/* swreg56 */
#define DWL_HEVC_E          26 /* 0:no 1:Main 2:Main10 */
#define DWL_VP9_E           29 /* 0:no 1:Profile 0, 2:Profile2 - 10bits */
#define DWL_MAX_OHEIGHT     0   /* Max video resolution. 16 bits */

/* swreg260 */
#define DWL_PP_E            31


/* AFBC encoder */
#define REG_BLOCK_ID	    0x000	/* BLOCK_ID 0x03002001 */
#define REG_IRQ_RAW_STATUS	0x004
#define REG_IRQ_CLEAR		0x008
#define REG_IRQ_MASK        0x00C
#define REG_IRQ_STATUS      0x010
#define REG_COMMAND         0x014
#define REG_STATUS          0x018


#endif /* __VC8000D_H__ */
