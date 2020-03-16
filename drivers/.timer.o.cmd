cmd_drivers/timer.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/.timer.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -Wall -DKBUILD_CONF -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc  -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables  -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -Os -O2 -fomit-frame-pointer      -o drivers/timer.o -c drivers/timer.c

deps_drivers/timer.o := \
  drivers/timer.c \
    $(wildcard include/config/irq/polling.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  include/std/features.h \
  include/bits/alltypes.h \
  include/bits/ProcessorBind.h \
  include/bits/wordsize.h \
  include/std/stdio.h \
  include/std/stddef.h \
  include/std/stdarg.h \
  include/std/errno.h \
  include/asm-generic/errno.h \
  include/target/timer.h \
  include/std/stdint.h \
  include/std/stdbool.h \
  include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  include/target/regdef.h \
  include/asm/reg.h \
  include/target/dsr.h \
  include/target/smp.h \
  include/target/cache.h \
  include/asm/cache.h \
  include/asm/mach/cache.h \
  include/asm/sysop.h \
  include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
  include/target/compiler.h \
  include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/asm/smp.h \
  include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \

drivers/timer.o: $(deps_drivers/timer.o)

$(deps_drivers/timer.o):
