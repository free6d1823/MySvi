cmd_arch/arm64/common/entry.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/common/.entry.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -Iinclude/hdts -mlittle-endian -D__ASSEMBLY__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h  -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused  -march=armv8.1-a+crypto+fp+simd+crc -x assembler-with-cpp  -DCONFIG_BROKEN_GAS_INST=1     -c -o arch/arm64/common/entry.o arch/arm64/common/entry.S

deps_arch/arm64/common/entry.o := \
  arch/arm64/common/entry.S \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  include/asm/asm-offsets.h \

arch/arm64/common/entry.o: $(deps_arch/arm64/common/entry.o)

$(deps_arch/arm64/common/entry.o):
