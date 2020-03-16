
obj-y:=

obj-y += dsr.o
obj-y += irq.o
obj-y += irqc.o
obj-y += delay.o
obj-y += timer.o
obj-y += console.o
obj-y += misc.o
obj-$(CONFIG_ARM64) += cpus.o
obj-y += percpu.o
obj-y += readline.o
obj-y += cmdline.o
obj-y += mem_test.o

obj-$(CONFIG_SEMIHOST) += semihosting.o
obj-$(CONFIG_CRC32) += crc_check.o
obj-$(CONFIG_HEAP_GENERIC) += heap_generic.o
obj-$(CONFIG_DMM) += dmm.o
obj-y += heap_simple.o

obj-$(CONFIG_SMP) += spinlock.o
obj-$(CONFIG_PERF) += perf.o


obj-$(CONFIG_PCI) += pci/
obj-$(CONFIG_ARCH_HAS_IRQC) += irqchip/
obj-$(CONFIG_UART) += uart/
obj-$(CONFIG_I2C) += i2c/
obj-$(CONFIG_DW_I2C) += i2c/dw/
obj-$(CONFIG_DW_SPI) += spi/dw/
obj-$(CONFIG_DW_SPI) += spi/device/spi_nor/
obj-$(CONFIG_SPI) += spi/master/
obj-$(CONFIG_SPI_SLAVE) += spi/slave/
obj-$(CONFIG_SPI_NOR) += spi/device/spi_nor/
obj-$(CONFIG_AVSBUS) += spi/device/avsbus/
obj-$(CONFIG_DDR) += ddr/
obj-$(CONFIG_EMAC) += emac/
obj-$(CONFIG_XGMAC) += XGmac/
obj-$(CONFIG_TRNG) += trng/
obj-$(CONFIG_PWRSOC) += usb2/
obj-$(CONFIG_UFS) += ufs/
obj-$(CONFIG_DWC_MSHC) += dwc_mshc/
obj-$(CONFIG_MMC) += mmc/
obj-$(CONFIG_DWC_MSHC) += dwc_mshc/
obj-$(CONFIG_PCIE_QCOM) += pcie/
obj-$(CONFIG_SATA) += sata/
obj-$(CONFIG_IMC_GICv2) += GICv2/
obj-$(CONFIG_SAE_SMMU) += sae_smmu/
obj-$(CONFIG_ARM_SMMU) += arm_smmu/
obj-$(CONFIG_HIDMA) += hidma/
obj-$(CONFIG_FDT) += libfdt/
obj-$(CONFIG_D71) += d71/
obj-$(CONFIG_DW_WDT) += watchdog/
obj-$(CONFIG_VC8000E) += vc8000e/
