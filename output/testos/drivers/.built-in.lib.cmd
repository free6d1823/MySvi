cmd_drivers/built-in.lib :=  aarch64-linux-gnu-ld -EL  -maarch64linux  -r -o drivers/built-in.lib drivers/dsr.o drivers/irq.o drivers/irqc.o drivers/delay.o drivers/timer.o drivers/console.o drivers/misc.o drivers/cpus.o drivers/percpu.o drivers/readline.o drivers/cmdline.o drivers/mem_test.o drivers/heap_simple.o drivers/spinlock.o drivers/irqchip/built-in.lib drivers/uart/built-in.lib drivers/i2c/built-in.lib
