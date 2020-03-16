cmd_arch/arm64/plat-centriq/qtmr.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/.qtmr.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/plat-centriq -Iarch/arm64/plat-centriq -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o arch/arm64/plat-centriq/qtmr.o -c /home/cj/MySvi/arch/arm64/plat-centriq/qtmr.c

deps_arch/arm64/plat-centriq/qtmr.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/qtmr.c \
    $(wildcard include/config/irq/polling.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/target/irq.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/stdbool.h \
  include/asm/irq.h \
  include/asm/sysreg.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/mach/irq.h \
  /home/cj/MySvi/include/target/barrier.h \
    $(wildcard include/config/smp.h) \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/asm/barrier.h \
  /home/cj/MySvi/include/target/irqc.h \
  /home/cj/MySvi/include/target/smp.h \
  /home/cj/MySvi/include/target/cache.h \
  include/asm/cache.h \
  include/asm/mach/cache.h \
  include/asm/sysop.h \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/std/stddef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  include/asm/smp.h \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach/hal/HALsysdbgHWIO.h \
    $(wildcard include/config/fabric/bmsk.h) \
    $(wildcard include/config/fabric/shft.h) \
    $(wildcard include/config/fval.h) \
    $(wildcard include/config/hw/shutdown/ack/fval.h) \
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/shft.h) \
    $(wildcard include/config/ctl/lo/addr.h) \
    $(wildcard include/config/ctl/lo/rmsk.h) \
    $(wildcard include/config/ctl/lo/in.h) \
    $(wildcard include/config/ctl/lo/inm.h) \
    $(wildcard include/config/ctl/lo/out.h) \
    $(wildcard include/config/ctl/lo/outm.h) \
    $(wildcard include/config/ctl/lo/comm/mode/bmsk.h) \
    $(wildcard include/config/ctl/lo/comm/mode/shft.h) \
    $(wildcard include/config/ctl/lo/sar/ref/bmsk.h) \
    $(wildcard include/config/ctl/lo/sar/ref/shft.h) \
    $(wildcard include/config/ctl/lo/sar/del/bmsk.h) \
    $(wildcard include/config/ctl/lo/sar/del/shft.h) \
    $(wildcard include/config/ctl/lo/icp/ref/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/icp/ref/sel/shft.h) \
    $(wildcard include/config/ctl/lo/ref/trim/bmsk.h) \
    $(wildcard include/config/ctl/lo/ref/trim/shft.h) \
    $(wildcard include/config/ctl/lo/fbc/alpha/cal/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/fbc/alpha/cal/sel/shft.h) \
    $(wildcard include/config/ctl/lo/bbc/beta/cal/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/bbc/beta/cal/sel/shft.h) \
    $(wildcard include/config/ctl/lo/bbc/doublet/len/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/bbc/doublet/len/sel/shft.h) \
    $(wildcard include/config/ctl/lo/bbc/update/len/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/bbc/update/len/sel/shft.h) \
    $(wildcard include/config/ctl/lo/p/ffa/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/p/ffa/sel/shft.h) \
    $(wildcard include/config/ctl/lo/k/p/tm/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/k/p/tm/sel/shft.h) \
    $(wildcard include/config/ctl/lo/k/i/tm/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/k/i/tm/sel/shft.h) \
    $(wildcard include/config/ctl/lo/k/p/ffa/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/k/p/ffa/sel/shft.h) \
    $(wildcard include/config/ctl/lo/k/i/ffa/sel/bmsk.h) \
    $(wildcard include/config/ctl/lo/k/i/ffa/sel/shft.h) \
    $(wildcard include/config/ctl/lo/pfd/dzsel/bmsk.h) \
    $(wildcard include/config/ctl/lo/pfd/dzsel/shft.h) \
    $(wildcard include/config/ctl/hi/addr.h) \
    $(wildcard include/config/ctl/hi/rmsk.h) \
    $(wildcard include/config/ctl/hi/in.h) \
    $(wildcard include/config/ctl/hi/inm.h) \
    $(wildcard include/config/ctl/hi/out.h) \
    $(wildcard include/config/ctl/hi/outm.h) \
    $(wildcard include/config/ctl/hi/rsv/bmsk.h) \
    $(wildcard include/config/ctl/hi/rsv/shft.h) \
    $(wildcard include/config/ctl/hi/duty/cycle/ctrl/override/bmsk.h) \
    $(wildcard include/config/ctl/hi/duty/cycle/ctrl/override/shft.h) \
    $(wildcard include/config/ctl/hi/cfa/glitch/detect/bypass/bmsk.h) \
    $(wildcard include/config/ctl/hi/cfa/glitch/detect/bypass/shft.h) \
    $(wildcard include/config/ctl/hi/duty/cycle/adj/bmsk.h) \
    $(wildcard include/config/ctl/hi/duty/cycle/adj/shft.h) \
    $(wildcard include/config/ctl/hi/duty/cycle/en/bmsk.h) \
    $(wildcard include/config/ctl/hi/duty/cycle/en/shft.h) \
    $(wildcard include/config/ctl/hi/droop/en/dly/bmsk.h) \
    $(wildcard include/config/ctl/hi/droop/en/dly/shft.h) \
    $(wildcard include/config/ctl/hi/enable/low/jitter/mode/bmsk.h) \
    $(wildcard include/config/low/jitter/mode/bmsk.h) \
    $(wildcard include/config/ctl/hi/enable/low/jitter/mode/shft.h) \
    $(wildcard include/config/low/jitter/mode/shft.h) \
    $(wildcard include/config/ctl/hi/charge/pump/ref/adj/bmsk.h) \
    $(wildcard include/config/ctl/hi/charge/pump/ref/adj/shft.h) \
    $(wildcard include/config/a/bmsk.h) \
    $(wildcard include/config/a/shft.h) \
    $(wildcard include/config/bbc/bmsk.h) \
    $(wildcard include/config/bbc/shft.h) \
    $(wildcard include/config/fbc/bmsk.h) \
    $(wildcard include/config/fbc/shft.h) \
    $(wildcard include/config/dem/in/dco/dac/bmsk.h) \
    $(wildcard include/config/dem/in/dco/dac/shft.h) \
  include/asm/mach/hal/msmhwiobase.h \
  include/asm/mach/mpm.h \

arch/arm64/plat-centriq/qtmr.o: $(deps_arch/arm64/plat-centriq/qtmr.o)

$(deps_arch/arm64/plat-centriq/qtmr.o):
