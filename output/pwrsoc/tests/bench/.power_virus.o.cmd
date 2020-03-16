cmd_tests/bench/power_virus.o := aarch64-linux-gnu-gcc -Wp,-MD,tests/bench/.power_virus.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/tests/bench -Itests/bench -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g -DREG=register -O2  -o tests/bench/power_virus.o -c /home/cj/MySvi/tests/bench/power_virus.c

deps_tests/bench/power_virus.o := \
  /home/cj/MySvi/tests/bench/power_virus.c \
    $(wildcard include/config/qpower/timeout.h) \
    $(wildcard include/config/qpower/repeats.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/testos.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/asm-generic/errno.h \
  /home/cj/MySvi/include/std/time.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/gpio.h \
  include/asm/gpio.h \
  include/asm/mach/tlmm.h \
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/shft.h) \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach/hal/HALtlmmHWIO.h \
  include/asm/mach/hal/msmhwiobase.h \
  include/asm/mach/tlmm_boot.h \
  /home/cj/MySvi/include/target/barrier.h \
    $(wildcard include/config/smp.h) \
  include/asm/barrier.h \
  /home/cj/MySvi/include/target/spinlock.h \
  include/asm/spinlock.h \
  /home/cj/MySvi/include/target/smp.h \
  /home/cj/MySvi/include/target/cache.h \
  include/asm/cache.h \
  include/asm/mach/cache.h \
  include/asm/sysop.h \
  include/asm/smp.h \
  /home/cj/MySvi/include/target/irq.h \
    $(wildcard include/config/irq/polling.h) \
  include/asm/irq.h \
  include/asm/sysreg.h \
  include/asm/mach/irq.h \
  /home/cj/MySvi/include/target/irqc.h \
  /home/cj/MySvi/include/target/percpu.h \
    $(wildcard include/config/percpu/interleave.h) \

tests/bench/power_virus.o: $(deps_tests/bench/power_virus.o)

$(deps_tests/bench/power_virus.o):
