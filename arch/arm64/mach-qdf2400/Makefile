obj-y :=

ccflags-y += -DHARVEST

obj-y += board.o
obj-y += socinfo.o
obj-y += chipinfo.o
obj-y += pseudo_fuse.o
obj-y += clock.o
obj-y += clock_qcom10.o
obj-y += clock_qcom11.o
obj-y += clock_qcom20.o
obj-y += falkor.o
obj-y += cbf.o
obj-y += plat_topology.o
obj-$(CONFIG_MONACO_RING) += monaco_su.o

obj-$(CONFIG_PMIC_SPMI) += pmic_spmi.o
obj-$(CONFIG_PMIC_PMBUS) += pmic_pmbus.o
obj-$(CONFIG_RAS_IMEM) += imem.o
obj-$(CONFIG_AVSBUS) += avsbus.o
obj-$(CONFIG_QDSS) += qdss.o
obj-$(CONFIG_QDSS_DBG) += qdss_dbg.o
obj-$(CONFIG_QDSS_PMU) += qdss_pmu.o
obj-$(CONFIG_QDSS_CTI) += qdss_cti.o
obj-$(CONFIG_QDSS_TPDA) += qdss_tpda.o
obj-$(CONFIG_QDSS_TPDM) += qdss_tpdm.o
obj-$(CONFIG_QDSS_SWITCH_DBG) += qdss_switch_dbg.o
obj-$(CONFIG_QDSS_SWITCH_PMU) += qdss_switch_pmu.o
obj-$(CONFIG_QDSS_SWITCH_CFG) += qdss_switch_cfg.o
obj-$(CONFIG_QDSS_SKITTER_CFG) += qdss_skitter_cfg.o
obj-$(CONFIG_MONACO) += monaco/
obj-$(CONFIG_TSENS) += tsens/

obj-$(CONFIG_APM) += hwdcvs.o
obj-$(CONFIG_CPUCHAR) += cpuchar.o

obj-$(CONFIG_FUSE_CFG) += fuse/
obj-$(CONFIG_I2C_QUP) += i2c_mach.o
obj-$(CONFIG_QCOM_DDRSS) += ddrss/
obj-$(CONFIG_MMU) += qdf_mm.o


