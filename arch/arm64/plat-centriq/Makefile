obj-y :=

obj-y += plat.o
obj-y += clk_ctl.o
obj-y += fabia.o
obj-y += agera.o

obj-y += sysini/

# Monaco files
obj-y += corebsp_logger.o
obj-$(CONFIG_MONACO_RING) += monaco_su.o
obj-$(CONFIG_QCOM_DDRSS) += ddrss/

obj-$(CONFIG_GPIO_TLMM) += tlmm.o
obj-$(CONFIG_UART_QUART) += quart.o
obj-$(CONFIG_SPI_QUP) += spi_qup.o
obj-$(CONFIG_SPM_CFG) += spm/
obj-$(CONFIG_SPM_CFG) += apc_pwr.o
obj-$(CONFIG_I2C_QUP) += qupe.o
obj-$(CONFIG_I2C_QUP) += i2c_qup.o
obj-$(CONFIG_I2C_QUP) += i2c_tlmm.o
obj-$(CONFIG_I2CS) += i2cs.o
