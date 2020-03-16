cmd_arch/arm64/mach-qdf2400/monaco_su.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/mach-qdf2400/.monaco_su.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/mach-qdf2400 -Iarch/arm64/mach-qdf2400 -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g -DHARVEST  -o arch/arm64/mach-qdf2400/monaco_su.o -c /home/cj/MySvi/arch/arm64/mach-qdf2400/monaco_su.c

deps_arch/arm64/mach-qdf2400/monaco_su.o := \
  /home/cj/MySvi/arch/arm64/mach-qdf2400/monaco_su.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/asm/mach/monaco/common/monaco_init.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/stdbool.h \
  include/asm/mach/monaco/common/monaco_defs.h \
    $(wildcard include/config/base.h) \
  include/asm/mach/monaco/common/monaco_extra_defs.h \
  include/asm/plat-centriq/ddr/mddr.h \
  include/asm/mach/monaco/memory/spd.h \
  include/asm/plat-centriq/ddr/mddr_power.h \
  include/asm/mach/monaco/memory/mddr_si.h \
  include/asm/mach/monaco/cache/l3_init.h \
  include/asm/plat-centriq/monaco_su.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/mach/monaco_su.h \

arch/arm64/mach-qdf2400/monaco_su.o: $(deps_arch/arm64/mach-qdf2400/monaco_su.o)

$(deps_arch/arm64/mach-qdf2400/monaco_su.o):
