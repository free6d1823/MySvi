cmd_drivers/irqchip/irq-gic-v3.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/irqchip/.irq-gic-v3.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/drivers/irqchip -Idrivers/irqchip -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o drivers/irqchip/irq-gic-v3.o -c /home/cj/MySvi/drivers/irqchip/irq-gic-v3.c

deps_drivers/irqchip/irq-gic-v3.o := \
  /home/cj/MySvi/drivers/irqchip/irq-gic-v3.c \
    $(wildcard include/config/mask.h) \
    $(wildcard include/config/grp1/ns.h) \
    $(wildcard include/config/grp0.h) \
    $(wildcard include/config/grp1/s.h) \
    $(wildcard include/config/grp1.h) \
    $(wildcard include/config/lpis.h) \
    $(wildcard include/config/gic600.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/target/irq.h \
    $(wildcard include/config/irq/polling.h) \
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
  include/asm/gic.h \
    $(wildcard include/config/offset.h) \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  include/asm/reg.h \
  include/asm/gicv3.h \
    $(wildcard include/config/grp.h) \
  include/asm/sysreg_gicv3.h \
  include/asm/gic3.h \
    $(wildcard include/config/gicv3.h) \
  /home/cj/MySvi/include/target/smp.h \
  /home/cj/MySvi/include/target/cache.h \
  include/asm/cache.h \
  include/asm/mach/cache.h \
  include/asm/sysop.h \
  include/asm/smp.h \
  /home/cj/MySvi/include/target/spinlock.h \
  include/asm/spinlock.h \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stdarg.h \

drivers/irqchip/irq-gic-v3.o: $(deps_drivers/irqchip/irq-gic-v3.o)

$(deps_drivers/irqchip/irq-gic-v3.o):
