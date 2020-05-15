#!/bin/bash
set -e

if [ $# -lt 1 ] ; then
	echo "Convert binary to hex loaded at <address> for ZeBu"
	echo
	echo "USAGE: $0 <binary> [<address>]"
	echo "    <address> can be omitted if it is 0x0"
	echo
	echo " e.g.: $0 arch/arm64/boot/hvep.bin 0x10000"
	echo " e.g.: $0 arch/arm64/boot/hvep.bin"
	echo
	exit 1;
fi

target=$(basename $1)

rm $target.hex -f

if [ $2 ] ; then
	addr=$2
	addr=`printf %d $addr`
	printf @%x\\n `expr $addr / 4` >$target.hex
fi

hexdump -v -e '/4 "%08X\n"' $1 >>$target.hex

echo $target.hex created.
