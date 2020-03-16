#!/bin/bash
export PATH=/opt/gcc-linaro-7.4.1-2019.02-x86_64_aarch64-linux-gnu/bin:$PATH
#export PATH=/opt/gcc-arm-none-eabi-8-2019-q3-update/bin:$PATH

GLIBC="/opt/glibc-2.31/lib"

for dir in $GLIBC
do
	if [ -d $dir ]; then
		export LD_LIBRARY_PATH=$dir
	fi
done

