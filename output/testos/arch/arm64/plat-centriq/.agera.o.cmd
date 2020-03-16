cmd_arch/arm64/plat-centriq/agera.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/.agera.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/plat-centriq -Iarch/arm64/plat-centriq -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o arch/arm64/plat-centriq/agera.o -c /home/cj/MySvi/arch/arm64/plat-centriq/agera.c

deps_arch/arm64/plat-centriq/agera.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/agera.c \
    $(wildcard include/config/ctl/hi.h) \
    $(wildcard include/config/ctl/lo.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/asm-generic/errno.h \
  /home/cj/MySvi/include/target/delay.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/clock.h \
  include/asm/clock.h \
  include/asm/mach/clock.h \
  include/asm/mach/fuse.h \
    $(wildcard include/config/nclude//.h) \
  /home/cj/MySvi/include/target/arch.h \
  include/asm/arch.h \
  include/asm/sysop.h \
  include/asm/falkor.h \
  /home/cj/MySvi/include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach/hal/HALclkHWIO.h \
    $(wildcard include/config/div/when/cal/bmsk.h) \
    $(wildcard include/config/div/when/cal/shft.h) \
    $(wildcard include/config//saverestore/bmsk.h) \
    $(wildcard include/config//saverestore/shft.h) \
    $(wildcard include/config/y/fine/lock/det/bmsk.h) \
    $(wildcard include/config/y/fine/lock/det/shft.h) \
    $(wildcard include/config/ctl/addr.h) \
    $(wildcard include/config/ctl/offs.h) \
    $(wildcard include/config/ctl/rmsk.h) \
    $(wildcard include/config/ctl/in.h) \
    $(wildcard include/config/ctl/inm.h) \
    $(wildcard include/config/ctl/out.h) \
    $(wildcard include/config/ctl/outm.h) \
    $(wildcard include/config/ctl/fine/ldc/threshold/bmsk.h) \
    $(wildcard include/config/ctl/fine/ldc/threshold/shft.h) \
    $(wildcard include/config/ctl/coarse/ldc/threshold/bmsk.h) \
    $(wildcard include/config/ctl/coarse/ldc/threshold/shft.h) \
    $(wildcard include/config/ctl/coarse/lock/det/neg/threshold/bmsk.h) \
    $(wildcard include/config/ctl/coarse/lock/det/neg/threshold/shft.h) \
    $(wildcard include/config/ctl/coarse/lock/det/pos/threshold/bmsk.h) \
    $(wildcard include/config/ctl/coarse/lock/det/pos/threshold/shft.h) \
    $(wildcard include/config/ctl/fine/lock/det/threshold/bmsk.h) \
    $(wildcard include/config/ctl/fine/lock/det/threshold/shft.h) \
    $(wildcard include/config/ctl/fine/lock/det/sample/size/bmsk.h) \
    $(wildcard include/config/ctl/fine/lock/det/sample/size/shft.h) \
    $(wildcard include/config/ctl/fwd/gain/slewing/kfn/bmsk.h) \
    $(wildcard include/config/ctl/fwd/gain/slewing/kfn/shft.h) \
    $(wildcard include/config/ctl/fwd/gain/kfn/bmsk.h) \
    $(wildcard include/config/ctl/fwd/gain/kfn/shft.h) \
    $(wildcard include/config/ctl/u/addr.h) \
    $(wildcard include/config/ctl/u/offs.h) \
    $(wildcard include/config/ctl/u/rmsk.h) \
    $(wildcard include/config/ctl/u/in.h) \
    $(wildcard include/config/ctl/u/inm.h) \
    $(wildcard include/config/ctl/u/out.h) \
    $(wildcard include/config/ctl/u/outm.h) \
    $(wildcard include/config/ctl/u/bist/cfg/bmsk.h) \
    $(wildcard include/config/ctl/u/bist/cfg/shft.h) \
    $(wildcard include/config/ctl/u/reserve/bits19/12/bmsk.h) \
    $(wildcard include/config/ctl/u/reserve/bits19/12/shft.h) \
    $(wildcard include/config/ctl/u/num/steps/fast/lock/bmsk.h) \
    $(wildcard include/config/ctl/u/num/steps/fast/lock/shft.h) \
    $(wildcard include/config/ctl/u/prediv/when/cal/bmsk.h) \
    $(wildcard include/config/ctl/u/prediv/when/cal/shft.h) \
    $(wildcard include/config/ctl/u/inc/min/glitch/threshold/4x/bmsk.h) \
    $(wildcard include/config/ctl/u/inc/min/glitch/threshold/4x/shft.h) \
    $(wildcard include/config/ctl/u/min/glitch/threshold/bmsk.h) \
    $(wildcard include/config/ctl/u/min/glitch/threshold/shft.h) \
    $(wildcard include/config/ctl/u/use/both/ref/clk/edge/bmsk.h) \
    $(wildcard include/config/h/ref/clk/edge/bmsk.h) \
    $(wildcard include/config/ctl/u/use/both/ref/clk/edge/shft.h) \
    $(wildcard include/config/h/ref/clk/edge/shft.h) \
    $(wildcard include/config/ctl/u/bias/warmup/time/bmsk.h) \
    $(wildcard include/config/ctl/u/bias/warmup/time/shft.h) \
    $(wildcard include/config/ctl/u/div/lock/det/thresholds/bmsk.h) \
    $(wildcard include/config/ctl/u/div/lock/det/thresholds/shft.h) \
    $(wildcard include/config/training/seq/bmsk.h) \
    $(wildcard include/config/training/seq/shft.h) \
    $(wildcard include/config/ne/tune/bmsk.h) \
    $(wildcard include/config/ne/tune/shft.h) \
    $(wildcard include/config/st/lock/bmsk.h) \
    $(wildcard include/config/st/lock/shft.h) \
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/shft.h) \
    $(wildcard include/config/fab/bcr/addr.h) \
    $(wildcard include/config/fab/bcr/offs.h) \
    $(wildcard include/config/fab/bcr/rmsk.h) \
    $(wildcard include/config/fab/bcr/in.h) \
    $(wildcard include/config/fab/bcr/inm.h) \
    $(wildcard include/config/fab/bcr/out.h) \
    $(wildcard include/config/fab/bcr/outm.h) \
    $(wildcard include/config/fab/bcr/blk/ares/bmsk.h) \
    $(wildcard include/config/fab/bcr/blk/ares/shft.h) \
    $(wildcard include/config/ep/ret/en/addr.h) \
    $(wildcard include/config/ep/ret/en/offs.h) \
    $(wildcard include/config/ep/ret/en/rmsk.h) \
    $(wildcard include/config/ep/ret/en/in.h) \
    $(wildcard include/config/ep/ret/en/inm.h) \
    $(wildcard include/config/ep/ret/en/out.h) \
    $(wildcard include/config/ep/ret/en/outm.h) \
    $(wildcard include/config/ep/ret/en/use/sleep/ret/en/bmsk.h) \
    $(wildcard include/config/ep/ret/en/bmsk.h) \
    $(wildcard include/config/ep/ret/en/use/sleep/ret/en/shft.h) \
    $(wildcard include/config/ep/ret/en/shft.h) \
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
    $(wildcard include/config/ctl/lo/rsv/bit22/bmsk.h) \
    $(wildcard include/config/ctl/lo/rsv/bit22/shft.h) \
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
    $(wildcard include/config/ctl/hi/rsv/bmsk.h) \
    $(wildcard include/config/ctl/hi/rsv/shft.h) \
    $(wildcard include/config/ctl/hi/duty/cycle/ctrl/override/bmsk.h) \
    $(wildcard include/config/ctl/hi/duty/cycle/ctrl/override/shft.h) \
    $(wildcard include/config/ctl/hi/cfa/glitch/detect/bypass/bmsk.h) \
    $(wildcard include/config/ctl/hi/cfa/glitch/detect/bypass/shft.h) \
    $(wildcard include/config/ctl/hi/rsv/bit10/bmsk.h) \
    $(wildcard include/config/ctl/hi/rsv/bit10/shft.h) \
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
  include/asm/mach/chipinfo.h \

arch/arm64/plat-centriq/agera.o: $(deps_arch/arm64/plat-centriq/agera.o)

$(deps_arch/arm64/plat-centriq/agera.o):
