# MySvi
SVI project
Environment Setting
export PATH=/opt/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin:$PATH

GLIBC="/opt/glibc-2.31/lib"
export LD_LIBRARY_PATH=$GLIBC


make menuconfig
or
make ARCH=arm64 se1000_defconfig
make
