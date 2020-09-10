#!/bin/bash
set -e

echo prepare kernel launch image...

./bin4z1ddr.sh linux.bin 0x280000
./bin4z1ddr.sh se1000.dtb 0x200000
./bin4z1ddr.sh rootfs.cpio.gz 0x4000000
echo convert image to dram
#convert image data
./bin4z1ddr.sh R.raw 0x1000000
./bin4z1ddr.sh G.raw 0x2000000
./bin4z1ddr.sh B.raw 0x3000000
./bin4z1ddr.sh Y.raw 0x1000000
./bin4z1ddr.sh U.raw 0x2000000
./bin4z1ddr.sh V.raw 0x3000000
./bin4z1ddr.sh UV.raw 0x2000000
echo finished!
