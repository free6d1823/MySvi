
obj-y :=

obj-y += ddr_enable.o
obj-$(CONFIG_ARCH_QDF2400) += harvest_hxt_ring.o
obj-$(CONFIG_ARCH_SE1000) +=  ddr_init.o
#obj-$(CONFIG_DDR_MEMC_SNPS) += snps/memc/
CFLAGS_ddr_init.o += -Wno-int-to-pointer-cast
