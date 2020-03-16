/* QDF2400 PCC (Peripheral Clock Controller) driver
 */
#ifndef __PCC_QDF2400_H_INCLUDE__
#define __PCC_QDF2400_H_INCLUDE__

#define PCC_BASE			ULL(0x0FF7AC00000)

/* BLSP generic */
#define PCC_BLSP0			0x00
#define PCC_BLSP1			0x07
#define PCC_BLSP2			0x0C
#define PCC_BLSP3			0x11

/* UART */
#define PCC_BLSP0_UART0			0x03 /* UART */
#define PCC_BLSP0_UART1			0x04 /* UART */
#define PCC_BLSP0_UART2			0x05 /* UART */
#define PCC_BLSP0_UART3			0x06 /* UART */
#define PCC_BLSP3_UART0			0x14 /* UART */
#define PCC_BLSP3_UART1			0x15 /* UART */
#define PCC_BLSP3_UART2			0x16 /* UART */
#define PCC_BLSP3_UART3			0x17 /* UART */

/* SPI */
#define PCC_BLSP0_QUP0			0x01 /* SPI */
#define PCC_BLSP0_QUP1			0x02 /* SPI */
#define PCC_BLSP3_QUP0			0x12 /* SPI */
#define PCC_BLSP3_QUP1			0x13 /* SPI */

/* I2C */
#define PCC_BLSP1_QUP0			0x08 /* I2C */
#define PCC_BLSP1_QUP1			0x09 /* I2C */
#define PCC_BLSP1_QUP2			0x0A /* I2C */
#define PCC_BLSP1_QUP3			0x0B /* I2C */
#define PCC_BLSP2_QUP0			0x0D /* I2C */
#define PCC_BLSP2_QUP1			0x0E /* I2C */
#define PCC_BLSP2_QUP2			0x0F /* I2C */
#define PCC_BLSP2_QUP3			0x10 /* I2C */
/* TODO: QUP0_I2C registers need to be confirmed */

/* ============================================================
 * Non-BLSP
 * ============================================================ */
/* I2C_SLAVE */
#define PCC_I2C_SLAVE			0x18
/* PDM */
#define PCC_PDM				0x1A
/* SPI_SLAVE */
#define PCC_SPI_SLAVE			0x1B
/* SPI_SLAVE */
#define PCC_SPI_SLAVE2			0x24
/* PRNG */
#define PCC_PRNG0			0x1C
#define PCC_PRNG1			0x1D
/* PERIPH_FAB */
#define PCC_PFAB			0x1E
/* SDCC */
#define PCC_SDCC0			0x1F
#define PCC_SDCC1			0x20
#define PCC_SDCC2			0x21
#define PCC_SDCC3			0x22
/* USB2 */
#define PCC_USB2_0			0x27
#define PCC_USB2_1			0x28
#define PCC_USB2_2			0x29
#define PCC_USB2_3			0x2A
/* USB2 special */
#define PCC_USB2_MSTR			0x26
#define PCC_USB2_PFAB			0x2B
/* MISC */
#define PCC_MISC			0x3A

#include <asm/plat-centriq/pcc.h>

#endif /* __PCC_QDF2400_H_INCLUDE__ */
