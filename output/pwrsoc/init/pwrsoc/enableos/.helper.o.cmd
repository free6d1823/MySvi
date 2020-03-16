cmd_init/pwrsoc/enableos/helper.o := aarch64-linux-gnu-gcc -Wp,-MD,init/pwrsoc/enableos/.helper.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -D__ASSEMBLY__ -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -x assembler-with-cpp -g -DCONFIG_BROKEN_GAS_INST=1 -c -o init/pwrsoc/enableos/helper.o /home/cj/MySvi/init/pwrsoc/enableos/helper.S

deps_init/pwrsoc/enableos/helper.o := \
  /home/cj/MySvi/init/pwrsoc/enableos/helper.S \
    $(wildcard include/config/psci.h) \
    $(wildcard include/config/armv8/switch/to/el1.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/init/pwrsoc/enableos/system.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/regdef.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \

init/pwrsoc/enableos/helper.o: $(deps_init/pwrsoc/enableos/helper.o)

$(deps_init/pwrsoc/enableos/helper.o):
