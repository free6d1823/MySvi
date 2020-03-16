cmd_lib/strlcpy.o := aarch64-linux-gnu-gcc -Wp,-MD,lib/.strlcpy.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -Wall -DKBUILD_CONF -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc  -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables  -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -Os -O2 -fomit-frame-pointer      -o lib/strlcpy.o -c lib/strlcpy.c

deps_lib/strlcpy.o := \
  lib/strlcpy.c \
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
  include/std/stdint.h \
  include/std/limits.h \
  include/std/libc.h \
    $(wildcard include/config/c/accessor.h) \
  include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  include/std/stdio.h \
  include/std/stddef.h \
  include/std/stdarg.h \

lib/strlcpy.o: $(deps_lib/strlcpy.o)

$(deps_lib/strlcpy.o):
