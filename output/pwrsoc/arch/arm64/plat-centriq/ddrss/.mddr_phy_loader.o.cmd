cmd_arch/arm64/plat-centriq/ddrss/mddr_phy_loader.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/ddrss/.mddr_phy_loader.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -I/home/cj/MySvi/arch/arm64/plat-centriq/ddrss -Iarch/arm64/plat-centriq/ddrss -Wall -DKBUILD_CONF -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -I/home/cj/MySvi/include/hdts -Iinclude/hdts -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -g -DCONFIG_BROKEN_GAS_INST=1 -fno-asynchronous-unwind-tables -mpc-relative-literal-loads -DCONFIG_ARCH_SUPPORTS_INT128 -Werror -fomit-frame-pointer -g -DHARVEST -DCONFIG_DDR  -o arch/arm64/plat-centriq/ddrss/mddr_phy_loader.o -c /home/cj/MySvi/arch/arm64/plat-centriq/ddrss/mddr_phy_loader.c

deps_arch/arm64/plat-centriq/ddrss/mddr_phy_loader.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/ddrss/mddr_phy_loader.c \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/include/std/stdio.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/std/stdarg.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/bits/ProcessorBind.h \
  /home/cj/MySvi/include/bits/wordsize.h \
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/ddr.h \
    $(wildcard include/config/qcom/ddrss.h) \
  /home/cj/MySvi/include/std/string.h \
  /home/cj/MySvi/include/std/features.h \
  /home/cj/MySvi/include/std/ctype.h \
  /home/cj/MySvi/include/target/cpus.h \
    $(wildcard include/config/arm64.h) \
  include/asm/cpus.h \
  include/asm/mach/cpus.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/target/regdef.h \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/memory.h \
  include/asm/memory.h \
  include/asm/mach/memory.h \
    $(wildcard include/config/tcm.h) \
  /home/cj/MySvi/include/target/compiler.h \
  /home/cj/MySvi/include/target/compiler_gcc.h \
    $(wildcard include/config/cc/isr/vector.h) \
  /home/cj/MySvi/include/target/ddr/ddr_common.h \
  /home/cj/MySvi/include/target/ddr/DDRCommonLib.h \
  /home/cj/MySvi/include/target/ddr/spd_block.h \
  /home/cj/MySvi/include/target/ddr/spd_ddr3_block.h \
  /home/cj/MySvi/include/target/ddr/spd_ddr4_block.h \
  /home/cj/MySvi/include/target/ddr/SPDConfig.h \
    $(wildcard include/config/h//.h) \
    $(wildcard include/config/buffer/props.h) \
    $(wildcard include/config/table/version.h) \
    $(wildcard include/config/table/header.h) \
    $(wildcard include/config/entry/version.h) \
    $(wildcard include/config/entry/header.h) \
  include/asm/mach/ddr.h \
  include/asm/plat-centriq/ddr.h \
  include/asm/plat-centriq/ddr/mddr_defs.h \
    $(wildcard include/config/offset.h) \
    $(wildcard include/config/2/offset.h) \
    $(wildcard include/config/slot/ready///s.h) \
    $(wildcard include/config/slot/en///s.h) \
    $(wildcard include/config/ca/mirror///s.h) \
    $(wildcard include/config/3ds///s.h) \
    $(wildcard include/config/num/clk///s.h) \
    $(wildcard include/config/num/cs///s.h) \
    $(wildcard include/config/sub/ranks///s.h) \
    $(wildcard include/config/row///s.h) \
    $(wildcard include/config/rows/scale/offset.h) \
    $(wildcard include/config/col///s.h) \
    $(wildcard include/config/bank/group/bits/2.h) \
    $(wildcard include/config/sub/ranks/8.h) \
    $(wildcard include/config/sub/ranks/4.h) \
    $(wildcard include/config/sub/ranks/2.h) \
    $(wildcard include/config/num/cs/4.h) \
    $(wildcard include/config/num/cs/2.h) \
    $(wildcard include/config/num/cs/1.h) \
    $(wildcard include/config/col/10.h) \
    $(wildcard include/config/col/11.h) \
    $(wildcard include/config/col/12.h) \
    $(wildcard include/config/pression/disable///m.h) \
    $(wildcard include/config/pression/disable///s.h) \
    $(wildcard include/config/auto/pchg.h) \
  include/asm/plat-centriq/ddr/mddr_power.h \
  include/asm/plat-centriq/ddr/mddr.h \
  include/asm/mach/monaco/common/monaco_defs.h \
    $(wildcard include/config/base.h) \
  include/asm/mach/monaco/common/monaco_extra_defs.h \
  include/asm/mach/monaco/memory/spd.h \
  include/asm/mach/monaco/memory/mddr_si.h \
  include/asm/plat-centriq/ddr/mddr_init.h \
    $(wildcard include/config///s.h) \
  include/asm/mach/monaco/memory/mddr_phy_init.h \
    $(wildcard include/config/true.h) \
    $(wildcard include/config/false.h) \
  include/asm/mach/monaco/memory/mddr_phy_train.h \
  include/asm/plat-centriq/ddr/mddr_api.h \
    $(wildcard include/config/testos/emu.h) \
  include/asm/mach/ddr/ddr_func_tbl.h \
  include/asm/mach/ddr/ddr_target.h \
    $(wildcard include/config/enhanced/training.h) \
  include/asm/mach/monaco/common/DDRTargetLib.h \
  include/asm/mach/monaco/common/monaco_init.h \
  include/asm/mach/monaco/cache/l3_init.h \
  include/asm/plat-centriq/monaco_su.h \
  include/asm/mach/monaco_su.h \
  include/asm/mach/monaco/common/common_defs.h \
  /home/cj/MySvi/include/target/smbus.h \
  /home/cj/MySvi/include/target/i2c.h \
    $(wildcard include/config/str/size.h) \
    $(wildcard include/config/target/id.h) \
  include/asm/mach/i2c.h \
  include/asm/mach/qupe.h \
  include/asm/mach/hal/HALqupHWIO.h \
    $(wildcard include/config/addr.h) \
    $(wildcard include/config/phys.h) \
    $(wildcard include/config/offs.h) \
    $(wildcard include/config/rmsk.h) \
    $(wildcard include/config/in.h) \
    $(wildcard include/config/inm.h) \
    $(wildcard include/config/out.h) \
    $(wildcard include/config/outm.h) \
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
    $(wildcard include/config/bmsk.h) \
    $(wildcard include/config/shft.h) \
    $(wildcard include/config/en/version/two/tag/bmsk.h) \
    $(wildcard include/config/en/version/two/tag/shft.h) \
  include/asm/mach/hal/msmhwiobase.h \
  include/asm/mach/ddr/ddr_reg_logging.h \
  include/asm/mach/hal/HALmemoryHWIO.h \
    $(wildcard include/config/slot/ready/bmsk.h) \
    $(wildcard include/config/slot/ready/shft.h) \
    $(wildcard include/config/slot/en/bmsk.h) \
    $(wildcard include/config/slot/en/shft.h) \
    $(wildcard include/config/ca/mirror/bmsk.h) \
    $(wildcard include/config/ca/mirror/shft.h) \
    $(wildcard include/config/device/pkg/bmsk.h) \
    $(wildcard include/config/device/pkg/shft.h) \
    $(wildcard include/config/number/clk/bmsk.h) \
    $(wildcard include/config/number/clk/shft.h) \
    $(wildcard include/config/number/cs/bmsk.h) \
    $(wildcard include/config/number/cs/shft.h) \
    $(wildcard include/config/number/sub/rank/bmsk.h) \
    $(wildcard include/config/number/sub/rank/shft.h) \
    $(wildcard include/config/row/width/bmsk.h) \
    $(wildcard include/config/row/width/shft.h) \
    $(wildcard include/config/col/width/bmsk.h) \
    $(wildcard include/config/col/width/shft.h) \
    $(wildcard include/config/bank/width/bmsk.h) \
    $(wildcard include/config/bank/width/shft.h) \
    $(wildcard include/config/pression/disable/bmsk.h) \
    $(wildcard include/config/pression/disable/shft.h) \
    $(wildcard include/config/k.h) \
    $(wildcard include/config/t.h) \
    $(wildcard include/config/fabric/bmsk.h) \
    $(wildcard include/config/fabric/shft.h) \
    $(wildcard include/config/row0/lsb/addr.h) \
    $(wildcard include/config/row0/lsb/offs.h) \
    $(wildcard include/config/row0/lsb/rmsk.h) \
    $(wildcard include/config/row0/lsb/in.h) \
    $(wildcard include/config/row0/lsb/inm.h) \
    $(wildcard include/config/row0/lsb/out.h) \
    $(wildcard include/config/row0/lsb/outm.h) \
    $(wildcard include/config/row0/lsb/spare1/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/spare1/disable/shft.h) \
    $(wildcard include/config/row0/lsb/spare0/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/spare0/disable/shft.h) \
    $(wildcard include/config/row0/lsb/imc/spniden/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/imc/spniden/disable/shft.h) \
    $(wildcard include/config/row0/lsb/imc/spiden/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/imc/spiden/disable/shft.h) \
    $(wildcard include/config/row0/lsb/imc/niden/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/imc/niden/disable/shft.h) \
    $(wildcard include/config/row0/lsb/imc/dbgen/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/imc/dbgen/disable/shft.h) \
    $(wildcard include/config/row0/lsb/debug/bus/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/debug/bus/disable/shft.h) \
    $(wildcard include/config/row0/lsb/spare3/bmsk.h) \
    $(wildcard include/config/row0/lsb/spare3/shft.h) \
    $(wildcard include/config/row0/lsb/all/debug/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/all/debug/disable/shft.h) \
    $(wildcard include/config/row0/lsb/spare2/bmsk.h) \
    $(wildcard include/config/row0/lsb/spare2/shft.h) \
    $(wildcard include/config/row0/lsb/uart/port/select/bmsk.h) \
    $(wildcard include/config/row0/lsb/uart/port/select/shft.h) \
    $(wildcard include/config/row0/lsb/boot/intf/select/bmsk.h) \
    $(wildcard include/config/row0/lsb/boot/intf/select/shft.h) \
    $(wildcard include/config/row0/lsb/spare1/bmsk.h) \
    $(wildcard include/config/row0/lsb/spare1/shft.h) \
    $(wildcard include/config/row0/lsb/apps/pbl/boot/speed/bmsk.h) \
    $(wildcard include/config/row0/lsb/apps/pbl/boot/speed/shft.h) \
    $(wildcard include/config/row0/lsb/force/sd/recovery/boot/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/force/sd/recovery/boot/disable/shft.h) \
    $(wildcard include/config/row0/lsb/spare0/bmsk.h) \
    $(wildcard include/config/row0/lsb/spare0/shft.h) \
    $(wildcard include/config/row0/msb/addr.h) \
    $(wildcard include/config/row0/msb/offs.h) \
    $(wildcard include/config/row0/msb/rmsk.h) \
    $(wildcard include/config/row0/msb/in.h) \
    $(wildcard include/config/row0/msb/inm.h) \
    $(wildcard include/config/row0/msb/out.h) \
    $(wildcard include/config/row0/msb/outm.h) \
    $(wildcard include/config/row0/msb/wdog/en/bmsk.h) \
    $(wildcard include/config/row0/msb/wdog/en/shft.h) \
    $(wildcard include/config/row0/msb/spare2/bmsk.h) \
    $(wildcard include/config/row0/msb/spare2/shft.h) \
    $(wildcard include/config/row0/msb/boot/rom/cfg/bmsk.h) \
    $(wildcard include/config/row0/msb/boot/rom/cfg/shft.h) \
    $(wildcard include/config/row0/msb/rot/transfer/check/gpio/bmsk.h) \
    $(wildcard include/config/row0/msb/rot/transfer/check/gpio/shft.h) \
    $(wildcard include/config/row0/msb/rot/transfer/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/rot/transfer/disable/shft.h) \
    $(wildcard include/config/row0/msb/cust/priv/key/select/bmsk.h) \
    $(wildcard include/config/row0/msb/cust/priv/key/select/shft.h) \
    $(wildcard include/config/row0/msb/sw/fuse/prog/disable/bmsk.h) \
    $(wildcard include/config/g/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/sw/fuse/prog/disable/shft.h) \
    $(wildcard include/config/g/disable/shft.h) \
    $(wildcard include/config/row0/msb/spare1/bmsk.h) \
    $(wildcard include/config/row0/msb/spare1/shft.h) \
    $(wildcard include/config/row0/msb/tpdm/spniden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/tpdm/spniden/disable/shft.h) \
    $(wildcard include/config/row0/msb/tpdm/spiden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/tpdm/spiden/disable/shft.h) \
    $(wildcard include/config/row0/msb/tpdm/niden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/tpdm/niden/disable/shft.h) \
    $(wildcard include/config/row0/msb/tpdm/dbgen/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/tpdm/dbgen/disable/shft.h) \
    $(wildcard include/config/row0/msb/spare0/bmsk.h) \
    $(wildcard include/config/row0/msb/spare0/shft.h) \
    $(wildcard include/config/row0/msb/dap/deviceen/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/dap/deviceen/disable/shft.h) \
    $(wildcard include/config/row0/msb/dap/spniden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/dap/spniden/disable/shft.h) \
    $(wildcard include/config/row0/msb/dap/spiden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/dap/spiden/disable/shft.h) \
    $(wildcard include/config/row0/msb/dap/niden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/dap/niden/disable/shft.h) \
    $(wildcard include/config/row0/msb/dap/dbgen/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/dap/dbgen/disable/shft.h) \
    $(wildcard include/config/row0/msb/apps/spniden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/apps/spniden/disable/shft.h) \
    $(wildcard include/config/row0/msb/apps/spiden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/apps/spiden/disable/shft.h) \
    $(wildcard include/config/row0/msb/apps/niden/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/apps/niden/disable/shft.h) \
    $(wildcard include/config/row0/msb/apps/dbgen/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/apps/dbgen/disable/shft.h) \
    $(wildcard include/config/row1/lsb/addr.h) \
    $(wildcard include/config/row1/lsb/offs.h) \
    $(wildcard include/config/row1/lsb/rmsk.h) \
    $(wildcard include/config/row1/lsb/in.h) \
    $(wildcard include/config/row1/lsb/inm.h) \
    $(wildcard include/config/row1/lsb/out.h) \
    $(wildcard include/config/row1/lsb/outm.h) \
    $(wildcard include/config/row1/lsb/oem/hw/id/bmsk.h) \
    $(wildcard include/config/row1/lsb/oem/hw/id/shft.h) \
    $(wildcard include/config/row1/lsb/anti/rollback/feature/en/bmsk.h) \
    $(wildcard include/config/row1/lsb/anti/rollback/feature/en/shft.h) \
    $(wildcard include/config/row1/lsb/spare0/bmsk.h) \
    $(wildcard include/config/row1/lsb/spare0/shft.h) \
    $(wildcard include/config/row1/msb/addr.h) \
    $(wildcard include/config/row1/msb/offs.h) \
    $(wildcard include/config/row1/msb/rmsk.h) \
    $(wildcard include/config/row1/msb/in.h) \
    $(wildcard include/config/row1/msb/inm.h) \
    $(wildcard include/config/row1/msb/out.h) \
    $(wildcard include/config/row1/msb/outm.h) \
    $(wildcard include/config/row1/msb/spare0/bmsk.h) \
    $(wildcard include/config/row1/msb/spare0/shft.h) \
    $(wildcard include/config/row1/msb/oem/product/id/bmsk.h) \
    $(wildcard include/config/row1/msb/oem/product/id/shft.h) \
    $(wildcard include/config/row0/lsb/pbl/scrub/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/pbl/scrub/disable/shft.h) \
    $(wildcard include/config/row0/lsb/prng/testmode/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/prng/testmode/disable/shft.h) \
    $(wildcard include/config/row0/lsb/mddr/compression/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/mddr/compression/disable/shft.h) \
    $(wildcard include/config/row0/lsb/testbus/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/testbus/disable/shft.h) \
    $(wildcard include/config/row0/lsb/force/dload/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/force/dload/disable/shft.h) \
    $(wildcard include/config/row0/lsb/partial/good/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/partial/good/disable/shft.h) \
    $(wildcard include/config/row0/lsb/ate/test/mode/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/ate/test/mode/disable/shft.h) \
    $(wildcard include/config/row0/lsb/apps/cfgaespmulldisable/bmsk.h) \
    $(wildcard include/config/row0/lsb/apps/cfgaespmulldisable/shft.h) \
    $(wildcard include/config/row0/lsb/apps/cfgshadisable/bmsk.h) \
    $(wildcard include/config/row0/lsb/apps/cfgshadisable/shft.h) \
    $(wildcard include/config/row0/lsb/apps/cfgcryptodisable/bmsk.h) \
    $(wildcard include/config/row0/lsb/apps/cfgcryptodisable/shft.h) \
    $(wildcard include/config/row0/lsb/apps/cp15sdisable/bmsk.h) \
    $(wildcard include/config/row0/lsb/apps/cp15sdisable/shft.h) \
    $(wildcard include/config/row0/lsb/apps/cfgrstsctlrel3v/bmsk.h) \
    $(wildcard include/config/row0/lsb/apps/cfgrstsctlrel3v/shft.h) \
    $(wildcard include/config/row0/lsb/apps/cfgrstsctlrel3te/bmsk.h) \
    $(wildcard include/config/row0/lsb/apps/cfgrstsctlrel3te/shft.h) \
    $(wildcard include/config/row0/lsb/apps/cfgrstsctlrel3ee/bmsk.h) \
    $(wildcard include/config/row0/lsb/apps/cfgrstsctlrel3ee/shft.h) \
    $(wildcard include/config/row0/lsb/boot/rom/patch/disable/bmsk.h) \
    $(wildcard include/config/row0/lsb/boot/rom/patch/disable/shft.h) \
    $(wildcard include/config/row0/msb/secure/channel/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/secure/channel/disable/shft.h) \
    $(wildcard include/config/row0/msb/acc/disable/bmsk.h) \
    $(wildcard include/config/row0/msb/acc/disable/shft.h) \
    $(wildcard include/config/row1/lsb/spare1/bmsk.h) \
    $(wildcard include/config/row1/lsb/spare1/shft.h) \
    $(wildcard include/config/row1/lsb/qc/tpdm/spniden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/tpdm/spniden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/tpdm/spiden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/tpdm/spiden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/tpdm/niden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/tpdm/niden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/tpdm/dbgen/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/tpdm/dbgen/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/dap/deviceen/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/dap/deviceen/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/dap/spniden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/dap/spniden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/dap/spiden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/dap/spiden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/dap/niden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/dap/niden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/dap/dbgen/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/dap/dbgen/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/apps/spniden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/apps/spniden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/apps/spiden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/apps/spiden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/apps/niden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/apps/niden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/apps/dbgen/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/apps/dbgen/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/spare1/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/spare1/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/spare0/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/spare0/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/imc/spniden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/imc/spniden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/imc/spiden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/imc/spiden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/imc/niden/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/imc/niden/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/imc/dbgen/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/imc/dbgen/disable/shft.h) \
    $(wildcard include/config/row1/lsb/qc/debug/bus/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/qc/debug/bus/disable/shft.h) \
    $(wildcard include/config/row1/lsb/sm/bist/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/sm/bist/disable/shft.h) \
    $(wildcard include/config/row1/lsb/tic/disable/bmsk.h) \
    $(wildcard include/config/row1/lsb/tic/disable/shft.h) \
    $(wildcard include/config/row1/msb/sec/tap/access/disable/bmsk.h) \
    $(wildcard include/config/row1/msb/sec/tap/access/disable/shft.h) \
    $(wildcard include/config/row1/msb/tap/cji/core/sel/disable/bmsk.h) \
    $(wildcard include/config/row1/msb/tap/cji/core/sel/disable/shft.h) \
    $(wildcard include/config/row1/msb/tap/instr/disable/bmsk.h) \
    $(wildcard include/config/row1/msb/tap/instr/disable/shft.h) \
    $(wildcard include/config/row2/lsb/addr.h) \
    $(wildcard include/config/row2/lsb/offs.h) \
    $(wildcard include/config/row2/lsb/rmsk.h) \
    $(wildcard include/config/row2/lsb/in.h) \
    $(wildcard include/config/row2/lsb/inm.h) \
    $(wildcard include/config/row2/lsb/out.h) \
    $(wildcard include/config/row2/lsb/outm.h) \
    $(wildcard include/config/row2/lsb/tap/gen/spare/instr/disable/31/0/bmsk.h) \
    $(wildcard include/config/row2/lsb/tap/gen/spare/instr/disable/31/0/shft.h) \
    $(wildcard include/config/row2/msb/addr.h) \
    $(wildcard include/config/row2/msb/offs.h) \
    $(wildcard include/config/row2/msb/rmsk.h) \
    $(wildcard include/config/row2/msb/in.h) \
    $(wildcard include/config/row2/msb/inm.h) \
    $(wildcard include/config/row2/msb/out.h) \
    $(wildcard include/config/row2/msb/outm.h) \
    $(wildcard include/config/row2/msb/sw/expansion/fuses/bmsk.h) \
    $(wildcard include/config/row2/msb/sw/expansion/fuses/shft.h) \
    $(wildcard include/config/row2/msb/spare0/bmsk.h) \
    $(wildcard include/config/row2/msb/spare0/shft.h) \
    $(wildcard include/config/row2/msb/tap/gen/spare/instr/disable/49/32/bmsk.h) \
    $(wildcard include/config/row2/msb/tap/gen/spare/instr/disable/49/32/shft.h) \
    $(wildcard include/config/row3/lsb/addr.h) \
    $(wildcard include/config/row3/lsb/offs.h) \
    $(wildcard include/config/row3/lsb/rmsk.h) \
    $(wildcard include/config/row3/lsb/in.h) \
    $(wildcard include/config/row3/lsb/inm.h) \
    $(wildcard include/config/row3/lsb/out.h) \
    $(wildcard include/config/row3/lsb/outm.h) \
    $(wildcard include/config/row3/lsb/mdsp/fw/disable/bmsk.h) \
    $(wildcard include/config/row3/lsb/mdsp/fw/disable/shft.h) \
    $(wildcard include/config/row3/msb/addr.h) \
    $(wildcard include/config/row3/msb/offs.h) \
    $(wildcard include/config/row3/msb/rmsk.h) \
    $(wildcard include/config/row3/msb/in.h) \
    $(wildcard include/config/row3/msb/inm.h) \
    $(wildcard include/config/row3/msb/out.h) \
    $(wildcard include/config/row3/msb/outm.h) \
    $(wildcard include/config/row3/msb/spare3/bmsk.h) \
    $(wildcard include/config/row3/msb/spare3/shft.h) \
    $(wildcard include/config/row3/msb/apps/pbl/patch/version/bmsk.h) \
    $(wildcard include/config/row3/msb/apps/pbl/patch/version/shft.h) \
    $(wildcard include/config/row3/msb/spare2/bmsk.h) \
    $(wildcard include/config/row3/msb/spare2/shft.h) \
    $(wildcard include/config/row3/msb/imc/boot/from/rom/bmsk.h) \
    $(wildcard include/config/row3/msb/imc/boot/from/rom/shft.h) \
    $(wildcard include/config/row3/msb/spare1/bmsk.h) \
    $(wildcard include/config/row3/msb/spare1/shft.h) \
    $(wildcard include/config/row3/msb/msa/ena/bmsk.h) \
    $(wildcard include/config/row3/msb/msa/ena/shft.h) \
    $(wildcard include/config/row3/msb/force/msa/auth/en/bmsk.h) \
    $(wildcard include/config/row3/msb/force/msa/auth/en/shft.h) \
    $(wildcard include/config/row3/msb/spare0/bmsk.h) \
    $(wildcard include/config/row3/msb/spare0/shft.h) \
    $(wildcard include/config//meas/bmsk.h) \
    $(wildcard include/config//meas/shft.h) \
    $(wildcard include/config/se/done/bmsk.h) \
    $(wildcard include/config/se/done/shft.h) \
    $(wildcard include/config/se/bmsk.h) \
    $(wildcard include/config/se/shft.h) \
    $(wildcard include/config/row0/msb/spare3/bmsk.h) \
    $(wildcard include/config/row0/msb/spare3/shft.h) \
    $(wildcard include/config/rot/transfer/gpio/bmsk.h) \
    $(wildcard include/config/rot/transfer/gpio/shft.h) \
    $(wildcard include/config/deep/recovery/gpio/bmsk.h) \
    $(wildcard include/config/deep/recovery/gpio/shft.h) \
    $(wildcard include/config/force/sd/recovery/gpio/bmsk.h) \
    $(wildcard include/config/force/sd/recovery/gpio/shft.h) \
    $(wildcard include/config/boot/recovery/gpio/bmsk.h) \
    $(wildcard include/config/boot/recovery/gpio/shft.h) \
    $(wildcard include/config/all/use/serial/num/bmsk.h) \
    $(wildcard include/config/ial/num/bmsk.h) \
    $(wildcard include/config/all/use/serial/num/shft.h) \
    $(wildcard include/config/ial/num/shft.h) \
    $(wildcard include/config/force/msa/auth/en/bmsk.h) \
    $(wildcard include/config/force/msa/auth/en/shft.h) \
    $(wildcard include/config/pk/hash/in/fuse/bmsk.h) \
    $(wildcard include/config/pk/hash/in/fuse/shft.h) \
    $(wildcard include/config/pk/hash/index/source/bmsk.h) \
    $(wildcard include/config/pk/hash/index/source/shft.h) \
    $(wildcard include/config/pbl/boot/speed/bmsk.h) \
    $(wildcard include/config/pbl/boot/speed/shft.h) \
    $(wildcard include/config/boot/from/rom/bmsk.h) \
    $(wildcard include/config/boot/from/rom/shft.h) \
    $(wildcard include/config/boot/intf/select/bmsk.h) \
    $(wildcard include/config/boot/intf/select/shft.h) \
    $(wildcard include/config/wdog/en/bmsk.h) \
    $(wildcard include/config/wdog/en/shft.h) \
    $(wildcard include/config//bmsk.h) \
    $(wildcard include/config//shft.h) \
    $(wildcard include/config/gpio/bmsk.h) \
    $(wildcard include/config/gpio/shft.h) \
    $(wildcard include/config/tribution/status/addr.h) \
    $(wildcard include/config/tribution/status/offs.h) \
    $(wildcard include/config/tribution/status/rmsk.h) \
    $(wildcard include/config/tribution/status/in.h) \
    $(wildcard include/config/tribution/status/inm.h) \
    $(wildcard include/config/tribution/status/fuse/distribution/parity/error/addr/bmsk.h) \
    $(wildcard include/config/tribution/parity/error/addr/bmsk.h) \
    $(wildcard include/config/tribution/status/fuse/distribution/parity/error/addr/shft.h) \
    $(wildcard include/config/tribution/parity/error/addr/shft.h) \
    $(wildcard include/config/tribution/status/fuse/distribution/error/again/bmsk.h) \
    $(wildcard include/config/tribution/error/again/bmsk.h) \
    $(wildcard include/config/tribution/status/fuse/distribution/error/again/shft.h) \
    $(wildcard include/config/tribution/error/again/shft.h) \
    $(wildcard include/config/tribution/status/fuse/distribution/error/bmsk.h) \
    $(wildcard include/config/tribution/error/bmsk.h) \
    $(wildcard include/config/tribution/status/fuse/distribution/error/shft.h) \
    $(wildcard include/config/tribution/error/shft.h) \
  include/asm/hal/HALhwio.h \
  include/asm/hal/HALcomdef.h \
  include/asm/mach/hal/HALddrphyHWIO.h \
  include/asm/mach/monaco/memory/mddr_ca_eyemeasure.h \
  include/asm/mach/monaco/memory/mddr_phy_loader.h \
  include/asm/mach/monaco/memory/spd_simm.h \
  include/asm/mach/monaco/memory/spd_smbus.h \
    $(wildcard include/config/n//m.h) \
    $(wildcard include/config/n//s.h) \
    $(wildcard include/config/n.h) \
    $(wildcard include/config/no/input//m.h) \
    $(wildcard include/config/no/input//s.h) \
    $(wildcard include/config/no/input.h) \
    $(wildcard include/config/no/output//m.h) \
    $(wildcard include/config/no/output//s.h) \
    $(wildcard include/config/no/output.h) \
    $(wildcard include/config/mini/core//m.h) \
    $(wildcard include/config/mini/core//s.h) \
    $(wildcard include/config/mini/core/i2c/master.h) \
    $(wildcard include/config/mini/core/smbus/master.h) \
    $(wildcard include/config/en/vers/two/tag.h) \
    $(wildcard include/config/during/run.h) \
  include/asm/mach/monaco/memory/spd_smbus_impl.h \
  include/asm/mach/monaco/common/boot_util.h \
  include/asm/mach/monaco/common/io.h \
  include/asm/mach/monaco/common/monaco_logger.h \
  include/asm/mach/monaco/common/SharedVariables.h \
  /home/cj/MySvi/include/target/guid.h \
  include/asm/mach/monaco/common/XBLSharedVar.h \

arch/arm64/plat-centriq/ddrss/mddr_phy_loader.o: $(deps_arch/arm64/plat-centriq/ddrss/mddr_phy_loader.o)

$(deps_arch/arm64/plat-centriq/ddrss/mddr_phy_loader.o):
