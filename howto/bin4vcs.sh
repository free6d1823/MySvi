#!/bin/bash
set -e

if [ $# -lt 1 ] ; then
        echo "Convert binary for VCS"
        echo
        echo "USAGE: $0 <APbinary>  [<M4binary>]"
        echo " e.g.: $0 arch/arm64/boot/hvep.bin"
        echo " e.g.: $0 arch/arm64/boot/hvep.bin  arch/armv7m/boot/hvep.bin"
        exit 1;
elif [ $# -eq 1 ] ; then
        IncM4=false;
        IncAP=true;
        echo "Convert binary for VCS of AP"
        if [ ! -f $1 ]; then
        echo "AP file not exit"
        IncAP=false;
        fi
elif [ $# -eq 2 ] ; then
        IncM4=true;
        IncAP=true;
        echo "Convert binary for VCS of AP and M4"
        if [ ! -f $1 ]; then
        echo "AP file not exit"
        IncAP=false;
        fi
        if [ ! -f $2 ]; then
        echo "M4 file not exit"
        IncM4=false;
        fi
fi

if [ $IncM4 = false ] && [ $IncAP = false ]; then
        echo "AP and M4 hvep.bin file not exist!"
        exit 1;
fi

target=$(basename $1)

if [ $IncM4 = false ] && [ $IncAP = true ]; then
echo "convert only AP hvep.bin to hex"
dd  if=/dev/zero bs=4096 count=16 status=none |cat - $1 >$target
cat $target /dev/zero | dd of=$target.vcs bs=4096 count=128 iflag=fullblock
fi

if [ $IncM4 = true ] && [ $IncAP = false ]; then
echo "convert only M4 hvep.bin to hex"
cat $2 /dev/zero | dd of=$target.vcs bs=4096 count=128 iflag=fullblock
fi


if [ $IncM4 = true ] && [ $IncAP = true ]; then
echo "convert AP and M4 hvep.bin to hex"
cat $2 /dev/zero | dd of=$target bs=4096 count=16 iflag=fullblock
cat $target $1 /dev/zero | dd of=$target.vcs bs=4096 count=128 iflag=fullblock
fi


echo $target.vcs created.
echo "gen hex"
size=`stat -c "%s" $target.vcs`

count=`expr $size / 131072`

echo "$count"
for (( i = 0; i < $count; i++ )) ;
do
        dd if=$target.vcs of=init.file.$i bs=131072 count=1 skip=$i
        var=`./bin4zebu.sh init.file.$i`
done




