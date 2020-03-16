#!/bin/bash
set -e

if [ $# -lt 1 ] ; then
	echo "Convert binary to hex loaded at <address> for ZeBu"
	echo
	echo "USAGE: $0 <binary> <address>"
	echo " e.g.: $0 arch/arm64/boot/hvep.bin 0x10000"
	exit 1;
fi

target=$(basename $1)
addr=0

if [ $2 ] ; then
	addr=$2
fi

addr=`printf %d $addr`
printf @%x\\n `expr $addr / 4` >$target.hex

hexdump -v -e '/4 "%08X\n"' $1 >>$target.hex

echo $target.hex created.
