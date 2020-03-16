#!/bin/bash
set -e


dtc -I dts -O dtb se1000_debug.dts >se1000_debug.dtb
./bin4zebu.sh se1000_debug.dtb 0x00200000
./bin4zebu.sh ~/linux/arch/arm64/boot/Image 0x00280000
./bin4zebu.sh ../rootfs.cpio 0x04000000
cat se1000_debug.dtb.hex Image.hex rootfs.cpio.hex > linux.hex
