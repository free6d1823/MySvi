cmd_arch/arm64/lib/cache_helpers.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/lib/.cache_helpers.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -D__ASSEMBLY__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc -x assembler-with-cpp  -DCONFIG_BROKEN_GAS_INST=1   -DDONT_USE_DC   -c -o arch/arm64/lib/cache_helpers.o arch/arm64/lib/cache_helpers.S

deps_arch/arm64/lib/cache_helpers.o := \
  arch/arm64/lib/cache_helpers.S \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/asm/asm_macros.S \
    $(wildcard include/config/plat/compat.h) \
  include/asm/reg.h \
  include/target/regdef.h \
  include/target/asm_macros_common.S \
  include/asm/platform_arch.h \
  include/target/spinlock.h \
    $(wildcard include/config/smp.h) \
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
  include/target/barrier.h \
  include/asm/barrier.h \

arch/arm64/lib/cache_helpers.o: $(deps_arch/arm64/lib/cache_helpers.o)

$(deps_arch/arm64/lib/cache_helpers.o):
