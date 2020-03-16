#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#ifdef __ASSEMBLY__

#ifndef ASM_NL
#define ASM_NL		 ;
#endif

#ifndef LINKER_SCRIPT
#ifndef __ALIGN
#define __ALIGN		.align 4,0x90
#define __ALIGN_STR	".align 4,0x90"
#endif

#define ALIGN __ALIGN
#define ALIGN_STR __ALIGN_STR

#ifndef ENTRY
#define ENTRY(name) \
	.globl name ASM_NL \
	ALIGN ASM_NL \
	name:
#endif
#endif

#ifndef WEAK
#define WEAK(name)	   \
	.weak name ASM_NL   \
	name:
#endif

#ifndef END
#define END(name) \
	.size name, .-name
#endif

#ifndef ENDPROC
#define ENDPROC(name) \
	.type name, @function ASM_NL \
	END(name)
#endif

#define ENDPIPROC(x)			\
	.globl	__pi_##x;		\
	.type 	__pi_##x, %function;	\
	.set	__pi_##x, x;		\
	.size	__pi_##x, . - x;	\
	ENDPROC(x)

#endif /* __ASSEMBLY__ */

#endif /* __ASSEMBLER_H__ */
