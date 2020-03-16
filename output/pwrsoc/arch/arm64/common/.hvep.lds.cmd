cmd_arch/arm64/common/hvep.lds := aarch64-linux-gnu-cpp -Wp,-MD,arch/arm64/common/.hvep.lds.d  -nostdinc -nostdlib -D__KERNEL__ -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -mlittle-endian -P -C -Uarm64 -DLINKER_SCRIPT -D__ASSEMBLY__ -o arch/arm64/common/hvep.lds /home/cj/MySvi/arch/arm64/common/hvep.lds.S

deps_arch/arm64/common/hvep.lds := \
  /home/cj/MySvi/arch/arm64/common/hvep.lds.S \
    $(wildcard include/config/data/base.h) \
    $(wildcard include/config/bss/in/data.h) \
    $(wildcard include/config/heap/base.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/percpu.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/percpu/interleave.h) \
  /home/cj/MySvi/include/target/smp.h \
  /home/cj/MySvi/include/target/cache.h \
  include/asm/cache.h \
  include/asm/mach/cache.h \
  include/asm/smp.h \

arch/arm64/common/hvep.lds: $(deps_arch/arm64/common/hvep.lds)

$(deps_arch/arm64/common/hvep.lds):
