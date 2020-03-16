cmd_arch/arm64/plat-centriq/ddrss/default_variables.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/ddrss/.default_variables.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/plat-centriq/ddrss -Iarch/arm64/plat-centriq/ddrss -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g -DHARVEST -DCONFIG_DDR  -o arch/arm64/plat-centriq/ddrss/default_variables.o -c /home/cj/MySvi/arch/arm64/plat-centriq/ddrss/default_variables.c

deps_arch/arm64/plat-centriq/ddrss/default_variables.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/ddrss/default_variables.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \

arch/arm64/plat-centriq/ddrss/default_variables.o: $(deps_arch/arm64/plat-centriq/ddrss/default_variables.o)

$(deps_arch/arm64/plat-centriq/ddrss/default_variables.o):
