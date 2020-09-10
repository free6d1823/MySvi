#!/bin/bash
set -e

if [ $# != 2 ] ; then
	echo "Make an elf which will load <binary> at <address>"
	echo
	echo "USAGE: $0 <binary> <address>"
	echo " e.g.: $0 linux/arch/arm64/boot/Image 0x60280000"
	exit 1;
fi

entry=$1
entry=${entry//./_}
entry=${entry//\//_}
entry=${entry//-/_}

objcopy -I binary -O elf64-x86-64 -B i386:x86-64 $1 $1.o

ld $1.o -e _binary_${entry}_start -Tdata=$2 -N -o $1.elf -s

rm -f $1.o
