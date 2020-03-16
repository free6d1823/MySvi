cmd_arch/arm64/plat-centriq/sysini/QcHydraHelper.o := aarch64-linux-gnu-gcc -Wp,-MD,arch/arm64/plat-centriq/sysini/.QcHydraHelper.o.d  -nostdinc -nostdlib -D__KERNEL__ -Iinclude -Iinclude/std -include /home/cj/MySvi/include/target/config.h -Iinclude2 -I/home/cj/MySvi/include -Iinclude/hdts -mlittle-endian -D__ASSEMBLY__ -I/home/cj/MySvi/include -Iinclude -I/home/cj/MySvi/include/std -Iinclude/std -include /home/cj/MySvi/include/target/config.h -I/home/cj/MySvi/include2 -Iinclude2  -I/home/cj/MySvi/include -DAARCH64 -mtune=cortex-a53 -mcmodel=large -mstrict-align -funsigned-char -fshort-wchar -fno-builtin-printf -fno-builtin-fprintf -fstack-protector -fno-strict-aliasing -fno-common -fno-short-enums -fverbose-asm -ffunction-sections -fdata-sections -ffixed-x18 -Wno-unused -march=armv8.1-a+crypto+fp+simd+crc -x assembler-with-cpp -g -DCONFIG_BROKEN_GAS_INST=1 -DDEBUG=1 -DIMAGE_BL31 -DSPM_HWIO_PREFIX=SAW4 -DHANDLE_EA_EL3_FIRST=1 -DENABLE_SWEVENT=1 -DTSP_INIT_ASYNC=0 -DSTACK_PROTECTOR_ENABLED=0 -DSKIP_A57_L1_FLUSH_PWR_DWN=0 -DA53_DISABLE_NON_TEMPORAL_HINT=1 -DA57_DISABLE_NON_TEMPORAL_HINT=1 -DERRATA_A53_826319=0 -DERRATA_A53_836870=0 -DERRATA_A53_855873=0 -DERRATA_A57_806969=0 -DERRATA_A57_813419=0 -DERRATA_A57_813420=0 -DERRATA_A57_826974=0 -DERRATA_A57_826977=0 -DERRATA_A57_828024=0 -DERRATA_A57_829520=0 -DERRATA_A57_833471=0 -DCRASH_REPORTING=1 -DARM_CCI_PRODUCT_ID=400 -DARM_ARCH_MAJOR=8 -DARM_ARCH_MINOR=0 -DARM_GIC_ARCH=2 -DASM_ASSERTION=0 -DCOLD_BOOT_SINGLE_CPU=1 -DCTX_INCLUDE_AARCH32_REGS=0 -DCTX_INCLUDE_FPREGS=1 -DENABLE_PLAT_COMPAT=0 -DENABLE_PMF=0 -DENABLE_PSCI_STAT=0 -DENABLE_RUNTIME_INSTRUMENTATION=0 -DERROR_DEPRECATED=1 -DHW_ASSISTED_COHERENCY=1 -DLOAD_IMAGE_V2=0 -DLOG_LEVEL=40 -DNS_TIMER_SWITCH=1 -DPL011_GENERIC_UART=0 -DPLAT_QDF2400 -DPROGRAMMABLE_RESET_ADDRESS=0 -DPSCI_EXTENDED_STATE_ID=1 -DRESET_TO_BL31=1 -DSEPARATE_CODE_AND_RODATA=0 -DSPD_qspd -DSPIN_ON_BL1_EXIT=0 -DTRUSTED_BOARD_BOOT=0 -DUSE_COHERENT_MEM=0 -c -o arch/arm64/plat-centriq/sysini/QcHydraHelper.o /home/cj/MySvi/arch/arm64/plat-centriq/sysini/QcHydraHelper.S

deps_arch/arm64/plat-centriq/sysini/QcHydraHelper.o := \
  /home/cj/MySvi/arch/arm64/plat-centriq/sysini/QcHydraHelper.S \
    $(wildcard include/config/ss/2/specific.h) \
  /home/cj/MySvi/include/target/config.h \
    $(wildcard include/config/h/include//.h) \
    $(wildcard include/config/sys/noirq.h) \
    $(wildcard include/config/sys/poll/rt.h) \
    $(wildcard include/config/sys/task.h) \
  /home/cj/MySvi/arch/arm64/plat-centriq/sysini/hy_sysini_config.inc \
    $(wildcard include/config/global.h) \
    $(wildcard include/config/cpu.h) \
  include/asm/asm_macros.S \
    $(wildcard include/config/plat/compat.h) \
  include/asm/reg.h \
  /home/cj/MySvi/include/target/regdef.h \
  /home/cj/MySvi/include/target/asm_macros_common.S \
  include/asm/platform_arch.h \
  /home/cj/MySvi/include/target/spinlock.h \
    $(wildcard include/config/smp.h) \
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
  /home/cj/MySvi/include/std/stdint.h \
  /home/cj/MySvi/include/bits/alltypes.h \
  /home/cj/MySvi/include/std/stdbool.h \
  /home/cj/MySvi/include/target/timer.h \
  /home/cj/MySvi/include/target/list.h \
  include/asm/timer.h \
  include/asm/io.h \
  /home/cj/MySvi/include/std/stddef.h \
  /home/cj/MySvi/include/target/barrier.h \
  include/asm/barrier.h \
  include/asm/cpu_macros.S \
  include/asm/spinlock.h \
  include/asm/errata_report.h \
  include/asm/mach/hydra_macro.h \
    $(wildcard include/config/ctl/hi.h) \
    $(wildcard include/config/ctl/lo.h) \
  include/asm/mach/platform_def.h \
  include/asm/mach/qc_platcommon.h \
    $(wildcard include/config/offset.h) \

arch/arm64/plat-centriq/sysini/QcHydraHelper.o: $(deps_arch/arm64/plat-centriq/sysini/QcHydraHelper.o)

$(deps_arch/arm64/plat-centriq/sysini/QcHydraHelper.o):
