cmd_arch/arm64/common/hvep.lds := aarch64-linux-gnu-cpp -Wp,-MD,arch/arm64/common/.hvep.lds.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian  -P -C -Uarm64 -DLINKER_SCRIPT -D__ASSEMBLY__ -o arch/arm64/common/hvep.lds arch/arm64/common/hvep.lds.S

deps_arch/arm64/common/hvep.lds := \
  arch/arm64/common/hvep.lds.S \
    $(wildcard include/config/data/base.h) \
    $(wildcard include/config/bss/in/data.h) \
    $(wildcard include/config/heap/base.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
  include/asm/mach/cpus.h \
  include/std/stdint.h \
  include/bits/alltypes.h \
  include/std/stdbool.h \
  include/target/compiler.h \
  include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/target/timer.h \
  include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  include/std/stddef.h \
  include/target/regdef.h \
  include/asm/reg.h \
  include/target/percpu.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/percpu/interleave.h) \
  include/target/smp.h \
  include/target/cache.h \
  include/asm/cache.h \
  include/asm/mach/cache.h \
  include/asm/smp.h \

arch/arm64/common/hvep.lds: $(deps_arch/arm64/common/hvep.lds)

$(deps_arch/arm64/common/hvep.lds):
