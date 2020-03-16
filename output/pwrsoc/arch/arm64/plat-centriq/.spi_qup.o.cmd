cmd_arch/arm64/plat-centriq/spi_qup.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/.spi_qup.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/plat-centriq -Iarch/arm64/plat-centriq -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o arch/arm64/plat-centriq/spi_qup.o -c /home/cj/MySvi/arch/arm64/plat-centriq/spi_qup.c

deps_arch/arm64/plat-centriq/spi_qup.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/spi_qup.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/asm/mach/spi/spi_defs.h \
    $(wildcard include/config/fail.h) \
  include/asm/mach-qdf2400/hal/HALspiHWIO.h \
    $(wildcard include/config/offs.h) \
    $(wildcard include/config/rmsk.h) \
    $(wildcard include/config/dis/inbuf/flag/fix/bmsk.h) \
    $(wildcard include/config/dis/inbuf/flag/fix/shft.h) \
    $(wildcard include/config/en/ext/out/flag/bmsk.h) \
    $(wildcard include/config/en/ext/out/flag/shft.h) \
    $(wildcard include/config/core/extra/clk/on/en/bmsk.h) \
    $(wildcard include/config/core/extra/clk/on/en/shft.h) \
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
    $(wildcard include/config/qup/hready/ctrl/bmsk.h) \
    $(wildcard include/config/qup/hready/ctrl/shft.h) \
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
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach-qdf2400/hal/HALtlmmHWIO.h \
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/shft.h) \
  include/asm/mach/hal/msmhwiobase.h \
  include/asm/mach-qdf2400/hal/msmhwiobase.h \
  /home/cj/MySvi/include/std/stdbool.h \
  include/asm/mach/spi/spi_qup.h \
  include/asm/mach/spi/spi_defs.h \
  include/asm/mach/spi/spi_cfg.h \
  include/asm/mach-qdf2400/hal/msmhwiobase.h \
  include/asm/mach/spi/spi_clk_cfg.h \

arch/arm64/plat-centriq/spi_qup.o: $(deps_arch/arm64/plat-centriq/spi_qup.o)

$(deps_arch/arm64/plat-centriq/spi_qup.o):
