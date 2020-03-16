cmd_arch/arm64/mach-qdf2400/qdf_mm.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/mach-qdf2400/.qdf_mm.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/mach-qdf2400 -Iarch/arm64/mach-qdf2400 -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g -DHARVEST  -o arch/arm64/mach-qdf2400/qdf_mm.o -c /home/cj/MySvi/arch/arm64/mach-qdf2400/qdf_mm.c

deps_arch/arm64/mach-qdf2400/qdf_mm.o := \
  /home/cj/MySvi/arch/arm64/mach-qdf2400/qdf_mm.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/asm/mmu.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/target/mmu.h \
    $(wildcard include/config/mmu/self/modify.h) \
    $(wildcard include/config/mmu/debug.h) \
  /home/cj/MySvi/include/target/mmu_port.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/target/bitops.h \

arch/arm64/mach-qdf2400/qdf_mm.o: $(deps_arch/arm64/mach-qdf2400/qdf_mm.o)

$(deps_arch/arm64/mach-qdf2400/qdf_mm.o):
