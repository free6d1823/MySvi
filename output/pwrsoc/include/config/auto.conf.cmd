deps_config := \
	init/Kconfig \
	lib/Kconfig \
	tests/raven/Kconfig \
	tests/sanity/Kconfig \
	tests/bench/Kconfig \
	tests/Kconfig \
	drivers/vc8000e/Kconfig \
	drivers/watchdog/Kconfig \
	drivers/d71/Kconfig \
	drivers/pci/Kconfig \
	drivers/libfdt/Kconfig \
	drivers/dwc_mshc/Kconfig \
	drivers/mmc/Kconfig \
	drivers/ufs/Kconfig \
	drivers/usb2/Kconfig \
	drivers/hidma/Kconfig \
	drivers/arm_smmu/Kconfig \
	drivers/sae_smmu/Kconfig \
	drivers/GICv2/Kconfig \
	drivers/sata/Kconfig \
	drivers/pcie/Kconfig \
	drivers/trng/Kconfig \
	drivers/XGmac/Kconfig \
	drivers/emac/Kconfig \
	drivers/spi/slave/Kconfig \
	drivers/spi/master/Kconfig \
	drivers/spi/dw/Kconfig \
	drivers/i2c/dw/Kconfig \
	drivers/i2c/Kconfig \
	drivers/uart/Kconfig \
	drivers/ddr/Kconfig \
	drivers/Kconfig \
	arch/arm64/mach-qdf2400/Kconfig \
	arch/arm64/plat-centriq/monaco/Kconfig \
	arch/arm64/plat-centriq/Kconfig \
	arch/arm64/common/Kconfig \
	init/m4bench/Kconfig \
	init/testos/Kconfig \
	init/pwrsoc/Kconfig \
	init/Kconfig.main \
	arch/arm64/Kconfig

include/config/auto.conf: \
	$(deps_config)

$(deps_config): ;
