cmd_init/pwrsoc/enableos/helper.o := aarch64-linux-gnu-gcc -Wp,-MD,init/pwrsoc/enableos/.helper.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -D__ASSEMBLY__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc -x assembler-with-cpp  -DCONFIG_BROKEN_GAS_INST=1       -c -o init/pwrsoc/enableos/helper.o init/pwrsoc/enableos/helper.S

deps_init/pwrsoc/enableos/helper.o := \
  init/pwrsoc/enableos/helper.S \
    $(wildcard include/config/psci.h) \
    $(wildcard include/config/armv8/switch/to/el1.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  init/pwrsoc/enableos/system.h \
  include/asm/reg.h \
  include/target/regdef.h \
  include/std/stdint.h \
  include/bits/alltypes.h \

init/pwrsoc/enableos/helper.o: $(deps_init/pwrsoc/enableos/helper.o)

$(deps_init/pwrsoc/enableos/helper.o):
