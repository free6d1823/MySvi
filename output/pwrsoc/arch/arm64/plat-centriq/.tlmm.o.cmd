cmd_arch/arm64/plat-centriq/tlmm.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/.tlmm.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/plat-centriq -Iarch/arm64/plat-centriq -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o arch/arm64/plat-centriq/tlmm.o -c /home/cj/MySvi/arch/arm64/plat-centriq/tlmm.c

deps_arch/arm64/plat-centriq/tlmm.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/tlmm.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/asm-generic/errno.h \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/gpio.h \
  include/asm/gpio.h \
  include/asm/mach/tlmm.h \
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/shft.h) \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach/hal/HALtlmmHWIO.h \
  include/asm/mach/hal/msmhwiobase.h \
  include/asm/mach/tlmm_boot.h \

arch/arm64/plat-centriq/tlmm.o: $(deps_arch/arm64/plat-centriq/tlmm.o)

$(deps_arch/arm64/plat-centriq/tlmm.o):
