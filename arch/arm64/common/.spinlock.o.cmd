cmd_arch/arm64/common/spinlock.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/common/.spinlock.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -D__ASSEMBLY__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc -x assembler-with-cpp  -DCONFIG_BROKEN_GAS_INST=1     -c -o arch/arm64/common/spinlock.o arch/arm64/common/spinlock.S

deps_arch/arm64/common/spinlock.o := \
  arch/arm64/common/spinlock.S \
    $(wildcard include/config/arch/supports/cas.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/target/compiler.h \
  include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/target/assembler.h \
  include/target/spinlock.h \
    $(wildcard include/config/smp.h) \
  include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
  include/asm/mach/cpus.h \
  include/std/stdint.h \
  include/bits/alltypes.h \
  include/std/stdbool.h \
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
  include/target/barrier.h \
  include/asm/barrier.h \

arch/arm64/common/spinlock.o: $(deps_arch/arm64/common/spinlock.o)

$(deps_arch/arm64/common/spinlock.o):
