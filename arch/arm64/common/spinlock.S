#include <target/compiler.h>
#include <target/assembler.h>
#include <target/spinlock.h>

#define COND_SEVL()	sevl
#define COND_WFE()	wfe

#ifdef CONFIG_ARCH_SUPPORTS_CAS
	.arch	armv8.1-a
ENTRY(__spin_lock)
	mov	w2, #1
	sevl
1:
	wfe
	mov	w1, wzr
	casa	w1, w2, [x0]
	cbnz	w1, 1b
	ret
ENDPIPROC(__spin_lock)

ENTRY(__spin_unlock)
	stlr	wzr, [x0]
	sev
	ret
ENDPIPROC(__spin_unlock)
#else
	.arch	armv8-a
ENTRY(__spin_lock)
	mov	w2, #1
	COND_SEVL()
l1:	COND_WFE()
l2:	ldaxr	w1, [x0]
	cbnz	w1, l1
	stxr	w1, w2, [x0]
	cbnz	w1, l2
	ret
ENDPIPROC(__spin_lock)

ENTRY(__spin_unlock)
	stlr	wzr, [x0]
	ret
ENDPIPROC(__spin_unlock)

ENTRY(__spin_trylock)
	mov	w2, #1
	ldaxr	w3, [x0]
	cbnz	w3, not_acquired
	stxr	w3, w2, [x0]
	cbnz	w3, not_acquired
	mov	x0, #1
	ret
not_acquired :
	mov	x0, #0
	ret
ENDPIPROC(__spin_trylock)
#endif
