#ifndef __QC_SYSINI_PORT_H__
#define __QC_SYSINI_PORT_H__

#define ICC_SRE_EL3     S3_6_C12_C12_5

#define MACRO	.macro
#define MEND	.endm
#define EXPORT .globl
#define IMPORT .extern
#define INCLUDE .include
#define ALIGN	.balign
#define AREA	.section
#define SPACE	.space
#define DCB	.byte
#define DCD	.word
#define DATA	.data
#define END

#define HYDRA_ASM_INIT_DBG	0x00
#define HYDRA_ASM_INIT_ETM	0x0
#define HYDRA_ASM_INIT_PERF_MON	0x00
#define HYDRA_ASM_INIT_IU	0x00

#endif //__QC_SYSINI_PORT_H__
