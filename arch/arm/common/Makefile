obj-y :=
obj-y += setup.o entry-armv.o
obj-$(CONFIG_GICv3) += gicv3.o

obj-y += exception.o

head-y += head.o
extra-y := $(head-y) hvep.lds
