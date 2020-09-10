# MySvi
SVI project

#History
2020/9/10 Add GDC test and fix DDR

#Environment Setting
export PATH=/opt/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin:$PATH

GLIBC="/opt/glibc-2.31/lib"
export LD_LIBRARY_PATH=$GLIBC


make menuconfig
or
make ARCH=arm64 se1000_defconfig
make

#How to add a new device
arch/arm64/
  include/asm/mach-se1000/memory.h   #define Base Memory Address
  configs/se1000_defconfig           #IP CONFIG settings
drivers/Kconfig add
  source drivers/<device_name>/Kconfig
driver/Makefile add
  obj-$(CONFIG_<device_name>) += <device_name>/
  
drivers/<device_name>
  Kconfig				#add Menuconfig item
  Makefile				#add module to obj-y
  
