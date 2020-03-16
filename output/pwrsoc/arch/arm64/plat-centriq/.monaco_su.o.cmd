cmd_arch/arm64/plat-centriq/monaco_su.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/.monaco_su.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/plat-centriq -Iarch/arm64/plat-centriq -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o arch/arm64/plat-centriq/monaco_su.o -c /home/cj/MySvi/arch/arm64/plat-centriq/monaco_su.c

deps_arch/arm64/plat-centriq/monaco_su.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/monaco_su.c \
    $(wildcard include/config/sbl.h) \
    $(wildcard include/config/testos/emu.h) \
    $(wildcard include/config/qcom/ddrss.h) \
    $(wildcard include/config/monaco/use/pseudo/ddr/chan/mask.h) \
    $(wildcard include/config/udo/ddr/chan/mask.h) \
    $(wildcard include/config/monaco/ddr/chan/mask.h) \
    $(wildcard include/config/pre/s1.h) \
    $(wildcard include/config/pre/haps.h) \
    $(wildcard include/config/monaco/slave/cache.h) \
    $(wildcard include/config/tcm.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/target/init.h \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/bitops.h \
  /home/cj/MySvi/include/target/byte_list.h \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/asm-generic/errno.h \
  include/asm/mach/monaco/common/monaco_init.h \
  include/asm/mach/monaco/common/monaco_defs.h \
    $(wildcard include/config/base.h) \
  include/asm/mach/monaco/common/monaco_extra_defs.h \
  include/asm/plat-centriq/ddr/mddr.h \
  include/asm/mach/monaco/memory/spd.h \
  include/asm/plat-centriq/ddr/mddr_power.h \
  include/asm/mach/monaco/memory/mddr_si.h \
  include/asm/mach/monaco/cache/l3_init.h \
  include/asm/plat-centriq/monaco_su.h \
  include/asm/mach/monaco_su.h \
  include/asm/mach/monaco/common/monaco_logger.h \

arch/arm64/plat-centriq/monaco_su.o: $(deps_arch/arm64/plat-centriq/monaco_su.o)

$(deps_arch/arm64/plat-centriq/monaco_su.o):
