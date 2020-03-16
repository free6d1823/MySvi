cmd_arch/arm64/mach-qdf2400/hwdcvs.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/mach-qdf2400/.hwdcvs.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/mach-qdf2400 -Iarch/arm64/mach-qdf2400 -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g -DHARVEST  -o arch/arm64/mach-qdf2400/hwdcvs.o -c /home/cj/MySvi/arch/arm64/mach-qdf2400/hwdcvs.c

deps_arch/arm64/mach-qdf2400/hwdcvs.o := \
  /home/cj/MySvi/arch/arm64/mach-qdf2400/hwdcvs.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/target/delay.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/asm-generic/errno.h \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/hwdcvs.h \
  include/asm/mach-qdf2400/hwdcvs_hwio.h \
    $(wildcard include/config/sk.h) \
    $(wildcard include/config/ft.h) \
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/shft.h) \
    $(wildcard include/config/dr.h) \
    $(wildcard include/config/fs.h) \
    $(wildcard include/config/.h) \
    $(wildcard include/config/m.h) \
    $(wildcard include/config/t.h) \
    $(wildcard include/config/tm.h) \
    $(wildcard include/config/ip/cpr/post/bmsk.h) \
    $(wildcard include/config/ip/cpr/post/shft.h) \
    $(wildcard include/config/ip/seq/post/change/bmsk.h) \
    $(wildcard include/config/ip/seq/post/change/shft.h) \
    $(wildcard include/config/ip/seq/change/freq/up/bmsk.h) \
    $(wildcard include/config/ip/seq/change/freq/up/shft.h) \
    $(wildcard include/config/ip/seq/change/voltage/bmsk.h) \
    $(wildcard include/config/ip/seq/change/voltage/shft.h) \
    $(wildcard include/config/ip/seq/change/freq/dn/bmsk.h) \
    $(wildcard include/config/ip/seq/change/freq/dn/shft.h) \
    $(wildcard include/config/ip/seq/pre/change/bmsk.h) \
    $(wildcard include/config/ip/seq/pre/change/shft.h) \
    $(wildcard include/config/ip/update/floor/bmsk.h) \
    $(wildcard include/config/ip/update/floor/shft.h) \
    $(wildcard include/config/ip/update/ceiling/bmsk.h) \
    $(wildcard include/config/ip/update/ceiling/shft.h) \
    $(wildcard include/config/ip/update/rail/bmsk.h) \
    $(wildcard include/config/ip/update/rail/shft.h) \
    $(wildcard include/config/ip/cpr/pre/bmsk.h) \
    $(wildcard include/config/ip/cpr/pre/shft.h) \
    $(wildcard include/config/ip/all/seq/bmsk.h) \
    $(wildcard include/config/ip/all/seq/shft.h) \
    $(wildcard include/config/ctl/hi/addr.h) \
    $(wildcard include/config/ctl/hi/offs.h) \
    $(wildcard include/config/ctl/hi/rmsk.h) \
    $(wildcard include/config/ctl/hi/in.h) \
    $(wildcard include/config/ctl/hi/inm.h) \
    $(wildcard include/config/ctl/hi/out.h) \
    $(wildcard include/config/ctl/hi/outm.h) \
    $(wildcard include/config/ctl/hi/cfg/ctl/hi/31/0/bmsk.h) \
    $(wildcard include/config/ctl/hi/cfg/ctl/hi/31/0/shft.h) \
    $(wildcard include/config/ctl/lo/addr.h) \
    $(wildcard include/config/ctl/lo/offs.h) \
    $(wildcard include/config/ctl/lo/rmsk.h) \
    $(wildcard include/config/ctl/lo/in.h) \
    $(wildcard include/config/ctl/lo/inm.h) \
    $(wildcard include/config/ctl/lo/out.h) \
    $(wildcard include/config/ctl/lo/outm.h) \
    $(wildcard include/config/ctl/lo/cfg/ctl/lo/31/0/bmsk.h) \
    $(wildcard include/config/ctl/lo/cfg/ctl/lo/31/0/shft.h) \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdarg.h \

arch/arm64/mach-qdf2400/hwdcvs.o: $(deps_arch/arm64/mach-qdf2400/hwdcvs.o)

$(deps_arch/arm64/mach-qdf2400/hwdcvs.o):
