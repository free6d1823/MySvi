cmd_drivers/irqchip/built-in.lib :=  aarch64-linux-gnu-ld -EL  -maarch64linux  -r -o drivers/irqchip/built-in.lib drivers/irqchip/irq-gic-v2.o drivers/irqchip/irq-gic-v3.o
