cmd_drivers/libfdt/fdt_support.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/libfdt/.fdt_support.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -Wall -DKBUILD_CONF -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc  -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables  -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -Os -O2 -fomit-frame-pointer       -o drivers/libfdt/fdt_support.o -c drivers/libfdt/fdt_support.c

deps_drivers/libfdt/fdt_support.o := \
  drivers/libfdt/fdt_support.c \
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
  drivers/libfdt/libfdt_env.h \
  include/std/stdint.h \
  drivers/libfdt/fdt.h \
  drivers/libfdt/libfdt.h \
  drivers/libfdt/libfdt_internal.h \
  drivers/libfdt/fdt_support.h \

drivers/libfdt/fdt_support.o: $(deps_drivers/libfdt/fdt_support.o)

$(deps_drivers/libfdt/fdt_support.o):
