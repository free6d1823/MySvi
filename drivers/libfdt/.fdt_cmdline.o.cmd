cmd_drivers/libfdt/fdt_cmdline.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/libfdt/.fdt_cmdline.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -Wall -DKBUILD_CONF -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc  -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables  -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -Os -O2 -fomit-frame-pointer       -o drivers/libfdt/fdt_cmdline.o -c drivers/libfdt/fdt_cmdline.c

deps_drivers/libfdt/fdt_cmdline.o := \
  drivers/libfdt/fdt_cmdline.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/std/string.h \
  include/std/features.h \
  include/bits/alltypes.h \
  include/bits/ProcessorBind.h \
  include/bits/wordsize.h \
  include/std/ctype.h \
  include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  include/std/stdio.h \
  include/std/stddef.h \
  include/std/stdarg.h \
  include/std/errno.h \
  include/asm-generic/errno.h \
  include/std/stdint.h \
  include/target/readline.h \
    $(wildcard include/config/sys/cbsize.h) \
    $(wildcard include/config/cmdline/editing.h) \
    $(wildcard include/config/auto/complete.h) \
  include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  include/target/compiler.h \
  include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/target/timer.h \
  include/std/stdbool.h \
  include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  include/target/regdef.h \
  include/asm/reg.h \
  include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
  include/target/utils.h \
  include/target/barrier.h \
    $(wildcard include/config/smp.h) \
  include/asm/barrier.h \
  include/std/endian.h \
  drivers/libfdt/libfdt.h \
  drivers/libfdt/libfdt_env.h \
  drivers/libfdt/fdt.h \
  drivers/libfdt/fdt_support.h \

drivers/libfdt/fdt_cmdline.o: $(deps_drivers/libfdt/fdt_cmdline.o)

$(deps_drivers/libfdt/fdt_cmdline.o):
