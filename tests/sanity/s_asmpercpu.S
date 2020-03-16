#include <target/assembler.h>
#include <target/smp.h>
#include <target/percpu.h>

ENTRY(asmpercpu_smp_processor_id)
	asm_smp_processor_id x1, x0
	ret
ENDPROC(asmpercpu_smp_processor_id)

ENTRY(asmpercpu_get_percpu_addr)
	asm_get_percpu_addr asmpercpu_sym, x1, x0
	ret
ENDPROC(asmpercpu_get_percpu_addr)
