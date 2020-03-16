cmd_arch/arm64/common/cacheinfo.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/common/.cacheinfo.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -Wall -DKBUILD_CONF -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc  -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables  -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -Os -O2 -fomit-frame-pointer      -o arch/arm64/common/cacheinfo.o -c arch/arm64/common/cacheinfo.c

deps_arch/arm64/common/cacheinfo.o := \
  arch/arm64/common/cacheinfo.c \
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
  include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  include/std/errno.h \
  include/asm-generic/errno.h \
  include/target/compiler.h \
  include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/asm/sysreg.h \
  include/std/stdint.h \
  include/target/regdef.h \
  include/std/stdio.h \
  include/std/stddef.h \
  include/std/stdarg.h \

arch/arm64/common/cacheinfo.o: $(deps_arch/arm64/common/cacheinfo.o)

$(deps_arch/arm64/common/cacheinfo.o):
