cmd_arch/arm64/common/coresight_tpiu.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/common/.coresight_tpiu.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/common -Iarch/arm64/common -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o arch/arm64/common/coresight_tpiu.o -c /home/cj/MySvi/arch/arm64/common/coresight_tpiu.c

deps_arch/arm64/common/coresight_tpiu.o := \
  /home/cj/MySvi/arch/arm64/common/coresight_tpiu.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/asm/coresight.h \
    $(wildcard include/config/coresight/verbose.h) \
    $(wildcard include/config/coresight.h) \
    $(wildcard include/config/coresight/etm.h) \
    $(wildcard include/config/coresight/stm.h) \
    $(wildcard include/config/coresight/pmu.h) \
    $(wildcard include/config/coresight/cti.h) \
    $(wildcard include/config/coresight/dbg/cpuv80a.h) \
    $(wildcard include/config/coresight/tpiu.h) \
    $(wildcard include/config/coresight/etb.h) \
    $(wildcard include/config/coresight/funnel.h) \
    $(wildcard include/config/coresight/replicator.h) \
    $(wildcard include/config/coresight/tmc.h) \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/jep106.h \

arch/arm64/common/coresight_tpiu.o: $(deps_arch/arm64/common/coresight_tpiu.o)

$(deps_arch/arm64/common/coresight_tpiu.o):
