cmd_arch/arm64/common/head.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/common/.head.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -D__ASSEMBLY__ -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -x assembler-with-cpp -g -DCONFIG_BROKEN_GAS_INST=1 -c -o arch/arm64/common/head.o /home/cj/MySvi/arch/arm64/common/head.S

deps_arch/arm64/common/head.o := \
  /home/cj/MySvi/arch/arm64/common/head.S \
    $(wildcard include/config/bss/in/data.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/assembler.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  include/asm/asm_macros.S \
    $(wildcard include/config/plat/compat.h) \
  /home/cj/MySvi/include/target/asm_macros_common.S \
  include/asm/platform_arch.h \
  /home/cj/MySvi/include/target/spinlock.h \
    $(wildcard include/config/smp.h) \
  /home/cj/MySvi/include/target/barrier.h \
  include/asm/barrier.h \

arch/arm64/common/head.o: $(deps_arch/arm64/common/head.o)

$(deps_arch/arm64/common/head.o):
