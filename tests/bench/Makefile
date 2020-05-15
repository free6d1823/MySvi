
ccflags-$(CONFIG_DHRYSTONE) += -DREG=register
ccflags-$(CONFIG_BENCH_OPTIMIZED) += -O2
asflags-$(CONFIG_HPOWER10) += -DTESTOS

obj-y :=

obj-$(CONFIG_DHRYSTONE) += dhry_1.o dhry_1_pcpu.o
obj-$(CONFIG_LINPACK) += linpack.o
obj-$(CONFIG_SAXPY) += saxpy.o
obj-$(CONFIG_QPOWER) += power_virus.o
obj-$(CONFIG_HPOWER10) += hpower10.o
