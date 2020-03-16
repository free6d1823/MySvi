#!/bin/bash
set -e

if [ $# -lt 1 ] ; then
	echo "Convert binary for VCS"
	echo
	echo "USAGE: $0 <binary>"
	echo " e.g.: $0 arch/arm64/boot/hvep.bin"
	exit 1;
fi

target=$(basename $1)

dd if=/dev/zero bs=4096 count=16 status=none |cat - $1 >$target.vcs

echo $target.vcs created.
