#!/bin/bash
set -e

echo $1 is translated to palladium ddr image.

target=$(basename $1)
addr=0

if [ $2 ] ; then
	addr=$2
fi

addr=`printf %d $addr`
addrhex=`printf %x $addr`
addrz1=`printf %x \`expr $addr / 4\``

fcha=z1cha_$target@0x$addrhex.hex
fchb=z1chb_$target@0x$addrhex.hex

echo @$addrz1 > $fcha
echo @$addrz1 > $fchb

hexdump -v -e '/2 "%04X\n"' $1 | awk '{if (NR%2==1) print;}' >>$fcha
hexdump -v -e '/2 "%04X\n"' $1 | awk '{if (NR%2==0) print;}' >>$fchb

echo $fcha and $fchb are created