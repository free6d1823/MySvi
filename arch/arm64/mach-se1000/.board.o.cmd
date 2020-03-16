cmd_arch/arm64/mach-se1000/board.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/mach-se1000/.board.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -Wall -DKBUILD_CONF -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc  -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables  -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -Os -O2 -fomit-frame-pointer      -o arch/arm64/mach-se1000/board.o -c arch/arm64/mach-se1000/board.c

deps_arch/arm64/mach-se1000/board.o := \
  arch/arm64/mach-se1000/board.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/asm/mmu.h \
  include/std/stdbool.h \
  include/std/stdint.h \
  include/bits/alltypes.h \
  include/bits/ProcessorBind.h \
  include/bits/wordsize.h \
  include/std/string.h \
  include/std/features.h \
  include/std/ctype.h \
  include/std/stdarg.h \
  include/target/mmu.h \
    $(wildcard include/config/mmu/self/modify.h) \
    $(wildcard include/config/mmu/debug.h) \
  include/target/mmu_port.h \
  include/std/stddef.h \
  include/target/bitops.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
  include/asm/mach/cpus.h \
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
  include/target/regdef.h \
  include/asm/reg.h \
  include/target/memory.h \

arch/arm64/mach-se1000/board.o: $(deps_arch/arm64/mach-se1000/board.o)

$(deps_arch/arm64/mach-se1000/board.o):
