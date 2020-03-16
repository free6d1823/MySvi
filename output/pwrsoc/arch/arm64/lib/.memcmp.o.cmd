cmd_arch/arm64/lib/memcmp.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/lib/.memcmp.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -D__ASSEMBLY__ -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -x assembler-with-cpp -g -DCONFIG_BROKEN_GAS_INST=1 -DDONT_USE_DC -c -o arch/arm64/lib/memcmp.o /home/cj/MySvi/arch/arm64/lib/memcmp.S

deps_arch/arm64/lib/memcmp.o := \
  /home/cj/MySvi/arch/arm64/lib/memcmp.S \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \

arch/arm64/lib/memcmp.o: $(deps_arch/arm64/lib/memcmp.o)

$(deps_arch/arm64/lib/memcmp.o):
