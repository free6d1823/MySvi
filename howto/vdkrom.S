#define UINT_L16(x) ((x) & 0xffff)
#define UINT_H16(x) UINT_L16((x) >> 16)

.globl _start

_start:

#if UINT_L16(ENTRY)
	mov  x0, UINT_L16(ENTRY)
	movk x0, UINT_H16(ENTRY), LSL 16
#else
	movz x0, UINT_H16(ENTRY), LSL 16
#endif
	br   x0
.rept	16
	nop
.endr
