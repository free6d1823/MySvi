cmd_drivers/console.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/.console.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/drivers -Idrivers -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o drivers/console.o -c /home/cj/MySvi/drivers/console.c

deps_drivers/console.o := \
  /home/cj/MySvi/drivers/console.c \
    $(wildcard include/config/console/input.h) \
    $(wildcard include/config/console/output.h) \
    $(wildcard include/config/irq/polling.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/target/readline.h \
    $(wildcard include/config/sys/cbsize.h) \
    $(wildcard include/config/cmdline/editing.h) \
    $(wildcard include/config/auto/complete.h) \
  /home/cj/MySvi/include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/asm-generic/errno.h \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/console.h \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/target/smp.h \
  /home/cj/MySvi/include/target/cache.h \
  include/asm/cache.h \
  include/asm/mach/cache.h \
  include/asm/sysop.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  include/asm/smp.h \
  /home/cj/MySvi/include/target/uart.h \
    $(wildcard include/config/uart/pl01x/dev0.h) \
    $(wildcard include/config/uart/pl01x/dev1.h) \
    $(wildcard include/config/uart/pl01x/dev2.h) \
    $(wildcard include/config/uart/dummy/dev0.h) \
    $(wildcard include/config/uart/con/baudrate.h) \
  /home/cj/MySvi/include/target/irq.h \
  include/asm/irq.h \
  include/asm/sysreg.h \
  include/asm/mach/irq.h \
  /home/cj/MySvi/include/target/barrier.h \
    $(wildcard include/config/smp.h) \
  include/asm/barrier.h \
  /home/cj/MySvi/include/target/irqc.h \
  /home/cj/MySvi/include/target/dsr.h \

drivers/console.o: $(deps_drivers/console.o)

$(deps_drivers/console.o):
