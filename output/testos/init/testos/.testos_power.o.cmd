cmd_init/testos/testos_power.o := aarch64-linux-gnu-gcc -Wp,-MD,init/testos/.testos_power.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/init/testos -Iinit/testos -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o init/testos/testos_power.o -c /home/cj/MySvi/init/testos/testos_power.c

deps_init/testos/testos_power.o := \
  /home/cj/MySvi/init/testos/testos_power.c \
    $(wildcard include/config/testos/ate.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/target/power.h \
  /home/cj/MySvi/include/target/pmic.h \
  include/asm/mach/pmic.h \
  include/asm/mach/pmic_spmi.h \
  /home/cj/MySvi/include/target/spmi.h \
  include/asm/mach/spmi.h \
  include/asm/mach/hal/msmhwiobase.h \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach/pmic_swio.h \
    $(wildcard include/config/addr.h) \
    $(wildcard include/config/irq/en/bmsk.h) \
    $(wildcard include/config/out.h) \
    $(wildcard include/config/inmi2.h) \
    $(wildcard include/config/test/bus/en/shft.h) \
    $(wildcard include/config/rmsk.h) \
    $(wildcard include/config/outi2.h) \
    $(wildcard include/config/clk/gate/en/shft.h) \
    $(wildcard include/config/maxq.h) \
    $(wildcard include/config/pri/arbiter/en/bmsk.h) \
    $(wildcard include/config/in.h) \
    $(wildcard include/config/maxn.h) \
    $(wildcard include/config/test/bus/en/bmsk.h) \
    $(wildcard include/config/ini2.h) \
    $(wildcard include/config/outmi2.h) \
    $(wildcard include/config/pri/arbiter/en/shft.h) \
    $(wildcard include/config/done/irq/en/shft.h) \
    $(wildcard include/config/irq/en/shft.h) \
    $(wildcard include/config/inm.h) \
    $(wildcard include/config/outm.h) \
    $(wildcard include/config/done/irq/en/bmsk.h) \
    $(wildcard include/config/clk/gate/en/bmsk.h) \
  include/asm/mach/hal/HALpmicarbHWIO.h \
  include/asm/mach/spmi_swio.h \
    $(wildcard include/config/shft.h) \
    $(wildcard include/config/data/addr/frame/parity/error/shft.h) \
    $(wildcard include/config/slave/cmd/frame/parity/error/bmsk.h) \
    $(wildcard include/config/no/response/data/frame/detected/shft.h) \
    $(wildcard include/config/master/cmd/frame/parity/error/bmsk.h) \
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/data/addr/frame/parity/error/bmsk.h) \
    $(wildcard include/config/reg/in.h) \
    $(wildcard include/config/false/master/arbitration/win/bmsk.h) \
    $(wildcard include/config/reg/inm.h) \
    $(wildcard include/config/unsupported/command/shft.h) \
    $(wildcard include/config/false/master/arbitration/win/shft.h) \
    $(wildcard include/config/no/response/data/frame/detected/bmsk.h) \
    $(wildcard include/config/reg/out.h) \
    $(wildcard include/config/false/bus/request/bmsk.h) \
    $(wildcard include/config/reg/mwb/enable/bmsk.h) \
    $(wildcard include/config/unsupported/command/bmsk.h) \
    $(wildcard include/config/arbiter/disconnected/shft.h) \
    $(wildcard include/config/reg/addr.h) \
    $(wildcard include/config/no/response/cmd/frame/detected/shft.h) \
    $(wildcard include/config/unexpected/ssc/shft.h) \
    $(wildcard include/config/unexpected/ssc/bmsk.h) \
    $(wildcard include/config/arbiter/disconnected/bmsk.h) \
    $(wildcard include/config/false/bus/request/shft.h) \
    $(wildcard include/config/reg/mwb/enable/shft.h) \
    $(wildcard include/config/reg/outm.h) \
    $(wildcard include/config/no/response/cmd/frame/detected/bmsk.h) \
    $(wildcard include/config/perih/irq/lost/shft.h) \
    $(wildcard include/config/arbiter/connected/bmsk.h) \
    $(wildcard include/config/arbiter/connected/shft.h) \
    $(wildcard include/config/slave/cmd/frame/parity/error/shft.h) \
    $(wildcard include/config/perih/irq/lost/bmsk.h) \
    $(wildcard include/config/reg/rmsk.h) \
    $(wildcard include/config/master/cmd/frame/parity/error/shft.h) \
  include/asm/mach/hal/HALspmiHWIO.h \
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
  include/asm/mach/i2c.h \
  include/asm/mach/qupe.h \
  /home/cj/MySvi/include/std/stdbool.h \
  include/asm/mach/hal/HALqupHWIO.h \
    $(wildcard include/config/phys.h) \
    $(wildcard include/config/offs.h) \
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
    $(wildcard include/config/en/version/two/tag/bmsk.h) \
    $(wildcard include/config/en/version/two/tag/shft.h) \

init/testos/testos_power.o: $(deps_init/testos/testos_power.o)

$(deps_init/testos/testos_power.o):
