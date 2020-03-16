cmd_arch/arm64/mach-qdf2400/pmic_pmbus.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/mach-qdf2400/.pmic_pmbus.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/mach-qdf2400 -Iarch/arm64/mach-qdf2400 -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g -DHARVEST  -o arch/arm64/mach-qdf2400/pmic_pmbus.o -c /home/cj/MySvi/arch/arm64/mach-qdf2400/pmic_pmbus.c

deps_arch/arm64/mach-qdf2400/pmic_pmbus.o := \
  /home/cj/MySvi/arch/arm64/mach-qdf2400/pmic_pmbus.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  /home/cj/MySvi/include/target/pmbus.h \
    $(wildcard include/config/command.h) \
    $(wildcard include/config/command/length.h) \
    $(wildcard include/config/channel/select.h) \
    $(wildcard include/config/data/format.h) \
    $(wildcard include/config/bus/access.h) \
    $(wildcard include/config/default.h) \
  /home/cj/MySvi/include/target/smbus.h \
  /home/cj/MySvi/include/target/i2c.h \
    $(wildcard include/config/str/size.h) \
    $(wildcard include/config/target/id.h) \
  /home/cj/MySvi/include/std/stdint.h \
  include/asm/mach/i2c.h \
  include/asm/mach/qupe.h \
  /home/cj/MySvi/include/std/stdbool.h \
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
  /home/cj/MySvi/include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/asm-generic/errno.h \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  include/asm/mach/tlmm_boot.h \

arch/arm64/mach-qdf2400/pmic_pmbus.o: $(deps_arch/arm64/mach-qdf2400/pmic_pmbus.o)

$(deps_arch/arm64/mach-qdf2400/pmic_pmbus.o):
