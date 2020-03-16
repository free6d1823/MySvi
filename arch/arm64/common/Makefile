
obj-y :=
obj-$(CONFIG_GICv2) += gicv2.o
obj-$(CONFIG_GICv3) += gicv3.o
obj-$(CONFIG_DCC) += dcc/
obj-$(CONFIG_CORESIGHT) += coresight.o
obj-$(CONFIG_CORESIGHT_TPIU) += coresight_tpiu.o
obj-$(CONFIG_CORESIGHT_ETB) += coresight_etb.o
obj-$(CONFIG_CORESIGHT_FUNNEL) += coresight_funnel.o
obj-$(CONFIG_CORESIGHT_REPLICATOR) += coresight_replicator.o
obj-$(CONFIG_CORESIGHT_TMC) += coresight_tmc.o
obj-$(CONFIG_CORESIGHT_STM) += coresight_stm.o
obj-$(CONFIG_CORESIGHT_ETM) += coresight_etm.o
obj-$(CONFIG_CORESIGHT_PMU) += coresight_pmu.o
obj-$(CONFIG_CORESIGHT_CTI) += coresight_cti.o
obj-$(CONFIG_CORESIGHT_DBG_CPUv80A) += coresight_dbg_cpuv80a.o
obj-$(CONFIG_PERF) += pmuv3.o
obj-$(CONFIG_MMU) += mmu.o mmu_core.o mmu_map.o mmu_port.o
obj-$(CONFIG_MMU_FAST) += mmu_fast.o

obj-y += cacheinfo.o

# SMP support
obj-y += cache.o
obj-y += spinlock.o

obj-y += exception.o
obj-y += timer.o
obj-y += entry.o

head-y += head.o
extra-y := $(head-y) hvep.lds

