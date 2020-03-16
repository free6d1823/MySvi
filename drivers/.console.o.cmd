cmd_drivers/console.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/.console.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -Wall -DKBUILD_CONF -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc  -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables  -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -Os -O2 -fomit-frame-pointer      -o drivers/console.o -c drivers/console.c

deps_drivers/console.o := \
  drivers/console.c \
    $(wildcard include/config/console/input.h) \
    $(wildcard include/config/console/output.h) \
    $(wildcard include/config/irq/polling.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/target/readline.h \
    $(wildcard include/config/sys/cbsize.h) \
    $(wildcard include/config/cmdline/editing.h) \
    $(wildcard include/config/auto/complete.h) \
  include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  include/std/errno.h \
  include/std/features.h \
  include/asm-generic/errno.h \
  include/target/compiler.h \
  include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/target/console.h \
  include/std/stdio.h \
  include/std/stddef.h \
  include/std/stdarg.h \
  include/bits/alltypes.h \
  include/bits/ProcessorBind.h \
  include/bits/wordsize.h \
  include/target/smp.h \
  include/target/cache.h \
  include/asm/cache.h \
  include/asm/mach/cache.h \
  include/asm/sysop.h \
  include/std/stdint.h \
  include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  include/std/stdbool.h \
  include/target/timer.h \
  include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  include/target/regdef.h \
  include/asm/reg.h \
  include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
  include/asm/smp.h \
  include/target/uart.h \
    $(wildcard include/config/uart/pl01x/dev0.h) \
    $(wildcard include/config/uart/pl01x/dev1.h) \
    $(wildcard include/config/uart/pl01x/dev2.h) \
    $(wildcard include/config/uart/dummy/dev0.h) \
    $(wildcard include/config/uart/con/baudrate.h) \
  include/target/irq.h \
  include/asm/irq.h \
  include/asm/sysreg.h \
  include/asm/mach/irq.h \
  include/target/barrier.h \
    $(wildcard include/config/smp.h) \
  include/asm/barrier.h \
  include/target/irqc.h \
  include/target/dsr.h \

drivers/console.o: $(deps_drivers/console.o)

$(deps_drivers/console.o):
