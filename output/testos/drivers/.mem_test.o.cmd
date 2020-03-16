cmd_drivers/mem_test.o := aarch64-linux-gnu-gcc -Wp,-MD,drivers/.mem_test.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/drivers -Idrivers -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g  -o drivers/mem_test.o -c /home/cj/MySvi/drivers/mem_test.c

deps_drivers/mem_test.o := \
  /home/cj/MySvi/drivers/mem_test.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/stdlib.h \
    $(wildcard include/config/dmm.h) \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/target/cmdline.h \
    $(wildcard include/config/console/command.h) \
  /home/cj/MySvi/include/std/errno.h \
  /home/cj/MySvi/include/asm-generic/errno.h \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/utils.h \
  /home/cj/MySvi/include/target/barrier.h \
    $(wildcard include/config/smp.h) \
  include/asm/barrier.h \
  /home/cj/MySvi/include/std/endian.h \

drivers/mem_test.o: $(deps_drivers/mem_test.o)

$(deps_drivers/mem_test.o):
