cmd_drivers/uart/uart.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/uart/.uart.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -Wall -DKBUILD_CONF -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc  -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables  -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -Os -O2 -fomit-frame-pointer       -o drivers/uart/uart.o -c drivers/uart/uart.c

deps_drivers/uart/uart.o := \
  drivers/uart/uart.c \
    $(wildcard include/config/uart/pl01x.h) \
    $(wildcard include/config/uart/quart.h) \
    $(wildcard include/config/uart/dw16550.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/std/stdint.h \
  include/bits/alltypes.h \
  include/bits/ProcessorBind.h \
  include/bits/wordsize.h \
  include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  include/std/features.h \
  include/std/string.h \
  include/std/ctype.h \
  include/target/uart.h \
    $(wildcard include/config/uart/pl01x/dev0.h) \
    $(wildcard include/config/uart/pl01x/dev1.h) \
    $(wildcard include/config/uart/pl01x/dev2.h) \
    $(wildcard include/config/uart/dummy/dev0.h) \
    $(wildcard include/config/uart/con/baudrate.h) \
  include/std/stdbool.h \
  include/target/irq.h \
    $(wildcard include/config/irq/polling.h) \
  include/asm/irq.h \
  include/asm/sysreg.h \
  include/target/regdef.h \
  include/asm/mach/irq.h \
  include/target/barrier.h \
    $(wildcard include/config/smp.h) \
  include/target/compiler.h \
  include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/asm/barrier.h \
  include/target/irqc.h \
  include/asm/reg.h \

drivers/uart/uart.o: $(deps_drivers/uart/uart.o)

$(deps_drivers/uart/uart.o):
