cmd_drivers/i2c/smbus.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/i2c/.smbus.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/drivers/i2c -Idrivers/i2c -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o drivers/i2c/smbus.o -c /home/cj/MySvi/drivers/i2c/smbus.c

deps_drivers/i2c/smbus.o := \
  /home/cj/MySvi/drivers/i2c/smbus.c \
    $(wildcard include/config/loopback/i2cs.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/target/irq.h \
    $(wildcard include/config/irq/polling.h) \
  /home/cj/MySvi/include/std/stdint.h \
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
  /home/cj/MySvi/include/target/smbus.h \
  /home/cj/MySvi/include/target/i2c.h \
    $(wildcard include/config/str/size.h) \
    $(wildcard include/config/target/id.h) \
  include/asm/mach/i2c.h \
  include/asm/mach/qupe.h \
  include/asm/mach/hal/HALqupHWIO.h \
    $(wildcard include/config/addr.h) \
    $(wildcard include/config/phys.h) \
    $(wildcard include/config/offs.h) \
    $(wildcard include/config/rmsk.h) \
    $(wildcard include/config/in.h) \
    $(wildcard include/config/inm.h) \
    $(wildcard include/config/out.h) \
    $(wildcard include/config/outm.h) \
    $(wildcard include/config/en/ext/out/flag/bmsk.h) \
    $(wildcard include/config/en/ext/out/flag/shft.h) \
    $(wildcard include/config/fifo/clk/gate/en/bmsk.h) \
    $(wildcard include/config/fifo/clk/gate/en/shft.h) \
    $(wildcard include/config/core/clk/on/en/bmsk.h) \
    $(wildcard include/config/core/clk/on/en/shft.h) \
    $(wildcard include/config/app/clk/on/en/bmsk.h) \
    $(wildcard include/config/app/clk/on/en/shft.h) \
    $(wildcard include/config/mini/core/bmsk.h) \
    $(wildcard include/config/mini/core/shft.h) \
    $(wildcard include/config/no/input/bmsk.h) \
    $(wildcard include/config/no/input/shft.h) \
    $(wildcard include/config/no/output/bmsk.h) \
    $(wildcard include/config/no/output/shft.h) \
    $(wildcard include/config/n/bmsk.h) \
    $(wildcard include/config/n/shft.h) \
    $(wildcard include/config/during/run/bmsk.h) \
    $(wildcard include/config/during/run/shft.h) \
    $(wildcard include/config/hs/mode/bmsk.h) \
    $(wildcard include/config/hs/mode/shft.h) \
    $(wildcard include/config/input/first/bmsk.h) \
    $(wildcard include/config/input/first/shft.h) \
    $(wildcard include/config/loop/back/bmsk.h) \
    $(wildcard include/config/loop/back/shft.h) \
    $(wildcard include/config/slave/operation/bmsk.h) \
    $(wildcard include/config/slave/operation/shft.h) \
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/shft.h) \
    $(wildcard include/config/en/version/two/tag/bmsk.h) \
    $(wildcard include/config/en/version/two/tag/shft.h) \
  include/asm/mach/hal/msmhwiobase.h \
  /home/cj/MySvi/include/target/bitops.h \
  /home/cj/MySvi/include/target/gpio.h \
  include/asm/gpio.h \
  include/asm/mach/tlmm.h \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach/hal/HALtlmmHWIO.h \
  include/asm/mach/tlmm_boot.h \
  /home/cj/MySvi/include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/asm-generic/errno.h \

drivers/i2c/smbus.o: $(deps_drivers/i2c/smbus.o)

$(deps_drivers/i2c/smbus.o):
