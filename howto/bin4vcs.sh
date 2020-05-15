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

dd if=/dev/zero bs=4096 count=16 status=none |cat - $1 >$target
cat $target /dev/zero | dd of=$target.vcs bs=4096 count=128 iflag=fullblock

echo $target.vcs created.

size=`stat -c "%s" $target.vcs`

count=`expr $size / 131072`
echo "$count"
for (( i = 0; i < $count; i++ )) ;
do
        dd if=$target.vcs of=init.file.$i bs=131072 count=1 skip=$i
        var=`./bin4zebu.sh init.file.$i`
done




