cmd_arch/arm64/plat-centriq/clk_ctl.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/.clk_ctl.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/plat-centriq -Iarch/arm64/plat-centriq -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o arch/arm64/plat-centriq/clk_ctl.o -c /home/cj/MySvi/arch/arm64/plat-centriq/clk_ctl.c

deps_arch/arm64/plat-centriq/clk_ctl.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/clk_ctl.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/target/bitops.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/target/clk.h \
  include/asm/mach/clk.h \
  include/asm/mach/gccmw.h \
    $(wildcard include/config/fab.h) \
  include/asm/plat-centriq/gccmw.h \
  include/asm/mach/gcce.h \
  include/asm/plat-centriq/gcce.h \
  include/asm/mach/pcc.h \
  include/asm/plat-centriq/pcc.h \
  include/asm/mach/imccc.h \
  include/asm/plat-centriq/imccc.h \
    $(wildcard include/config/ep/ret/en.h) \
  include/asm/mach/gccms.h \
  include/asm/mach/pciecc.h \
  include/asm/plat-centriq/clk_ctl.h \
  include/asm/io.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/target/regdef.h \

arch/arm64/plat-centriq/clk_ctl.o: $(deps_arch/arm64/plat-centriq/clk_ctl.o)

$(deps_arch/arm64/plat-centriq/clk_ctl.o):
