#!/bin/bash

usage() {
	echo ""
	echo "Usage: `basename $0` [-c console] [-r] [-q qfw] [-j jobs] [-s msmid] <suit>"
	echo "Where:"
	echo "   -c: Specify type of console (uart|dcc)"
	echo "       Currently required by testos builds"
	echo "   -j: Specify number of jobs"
	echo "   -q: Specify Qualcomm firmware path"
	echo "   -r: Force re-build"
	echo "   -s: Sign hvep image as XBL"
	echo " 2400: QDF2400"
	echo " suit: HVEP target program suit."
	echo "       testos:       combined IMC/APC testos image"
	echo "       testos_split: split IMC/APC testos images"
	echo "       pwrsoc:       power bench image"
 	echo "       se1000:       se1000 image"
 	echo "       virt:         virt image"
 	echo "       r52:       r52 image"
 	echo "       m4:           m4 image"
	echo "       all:          all of above suits"
	echo "       clean:        cleanup last builds"
	exit 1
}

fatal() {
	echo $1
	exit 1
}

SCRIPT=`(cd \`dirname $0\`; pwd)`
OUTDIR=${SCRIPT}/output
CONSOLE=
FORCEREBUILD=no
SIGNIMAGE=
TESTOS_PROGS="dhrystone linpack saxpy ateinit tcmtest asmpercpu memrand arm64isa"
JOBS=1
QFWDIR=

while getopts "c:j:q:rs:" opt
do
	case $opt in
	c) CONSOLE=_$OPTARG;;
	j) JOBS=$OPTARG;;
	q) QFWDIR=$OPTARG;;
	r) FORCEREBUILD=yes;;
	s) SIGNIMAGE=$OPTARG;;
	?) echo "Invalid argument $opt"
	   usage;;
	esac
done
shift $(($OPTIND - 1))

mrproper_hvep() {
	(
		cd ${SCRIPT}
		make mrproper
	)
}

sign_hvep() {
	bin_dir=${OUTDIR}
	cfg=${SCRIPT}/scripts/sectools/config/integration/secimage.xml
	img=sbl1

	if [ "x$SIGNIMAGE" == "x" ]; then
		return
	fi
	if [ "x$SIGNIMAGE" != "x2400" ]; then
		echo "=================================================="
		echo "Unknown msmid ${SIGNIMAGE}!"
		echo "Use 2400 instead!"
		SIGNIMAGE=2400
		echo "=================================================="
	fi

	export USE_SECTOOLS=1
	export SECTOOLS_POLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
	export USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN=1

	mkdir -p ${bin_dir}/unsigned
	mkdir -p ${bin_dir}/sign/default/${img}
	cp ${SCRIPT}/$1 ${bin_dir}/unsigned/xbl.elf

	python ${SCRIPT}/scripts/sectools/sectools_builder.py \
		-t ${bin_dir} -i ${bin_dir}/unsigned/xbl.elf \
		-g sbl1 --msmid=${SIGNIMAGE} --config=${cfg}
	if [ "x$2" == "xyes" -a "x$QFWDIR" != "x" ]; then
		cp ${bin_dir}/sign/default/sbl1/xbl.elf ${QFWDIR}/xbl/boot_images/QcomPkg/Qdf2400Pkg/Bin64/xbl.elf
	fi
	cp ${bin_dir}/sign/default/sbl1/xbl.elf ${SCRIPT}/$1.sign
}

clean_hvep() {
	hvep_target=`cat ${OUTDIR}/.hvep`
	progs="$TESTOS_PROGS glktest"

	if [ "x${hvep_target}" = "x" ]; then
		echo "Please build again to get clean command working."
		exit 1
	fi
	if [ "x${hvep_target}" = "xclean" ]; then
		echo "Nothing to clean again."
		return
	fi
	rm -f ${SCRIPT}/*.sign
	rm -rf ${OUTDIR}/sign
	rm -rf ${OUTDIR}/unsigned

	if [ "x${hvep_target}" = "xall" ]; then
		make O=${OUTDIR}/testos clean
		rm -f ${SCRIPT}/testos
		for prog in $progs; do
			rm -f ${SCRIPT}/${prog}
		done
		make O=${OUTDIR}/pwrsoc clean
		rm -f ${SCRIPT}/power_bench
	elif [ "x${hvep_target}" = "xtestos" ]; then
		for prog in $progs; do
			rm -f ${SCRIPT}/${prog}
		done
		make O=${OUTDIR}/testos clean
		rm -f ${SCRIPT}/testos
	elif [ "x${hvep_target}" = "xtestos_apc" ]; then
		for prog in $progs; do
			rm -f ${SCRIPT}/${prog}
		done
		make O=${OUTDIR}/testos_apc clean
		rm -f ${SCRIPT}/testos_apc
		make O=${OUTDIR}/testos_imc clean
		rm -f ${SCRIPT}/testos_imc
	elif [ "x${hvep_target}" = "xpwrsoc" ]; then
		make O=${OUTDIR}/pwrsoc clean
		rm -f ${SCRIPT}/power_bench
 	elif [ "x${hvep_target}" = "xse1000" ]; then
		make O=${OUTDIR}/se1000 clean
		rm -f ${SCRIPT}/se1000_power_bench
 	elif [ "x${hvep_target}" = "xvirt" ]; then
		make O=${OUTDIR}/virt clean
		rm -f ${SCRIPT}/virt_power_bench
 	elif [ "x${hvep_target}" = "xr52" ]; then
		make O=${OUTDIR}/r52 clean
		rm -f ${SCRIPT}/r52_power_bench
 	elif [ "x${hvep_target}" = "xm4" ]; then
		make O=${OUTDIR}/m4 clean
		rm -f ${SCRIPT}/m4_power_bench
	fi
	echo "clean" > ${OUTDIR}/.hvep
	if [ "x${hvep_target}" = "xall" ]; then
		rm -rf ${OUTDIR}
	fi
}

build_hvep() {
	outdir=${OUTDIR}/$1
	defconf=$2
	target=$3
	xbl=$4
	progs=$5

	echo $defconf

	pushd ${SCRIPT} > /dev/null
	mkdir -p $outdir
	echo $1 > ${OUTDIR}/.hvep
	make O=$outdir $defconf 1>/dev/null 2>&1 || return 1
	if [ "x$FORCEREBUILD" == "xyes" ]; then
		make O=$outdir clean
	fi
	if [ "x$JOBS" = "x1" ]; then
		make O=$outdir || return 1
	else
		echo "make O=$outdir -j ${JOBS}"
		make O=$outdir -j ${JOBS} || return 1
	fi
	if [ "x$target" != "x" ]; then
		cp ${outdir}/hvep ${SCRIPT}/${target}
		sign_hvep ${target} $xbl
	fi
	if [ "x$progs" != "x" ]; then
		for prog in $progs; do
			cp ${outdir}/${prog} ${SCRIPT}/${prog}
			sign_hvep ${prog}
		done
	fi
	popd > /dev/null
	return 0
}

if [ -z $1 ]; then
	echo "Missing target program suit!"
	usage
	exit 1
fi

HVEPSUIT=$1
JOBS=$(grep "processor" /proc/cpuinfo|sort -u|wc -l)

if [ "x$HVEPSUIT" == "xclean" ]; then
	clean_hvep
elif [ "x$HVEPSUIT" == "xall" ]; then
	if [ "x$CONSOLE" == "x" ]; then
		CONSOLE=_uart
	elif [ "x$CONSOLE" == "x_dcc" ]; then
		TESTOS_PROGS="${TESTOS_PROGS} glktest"
	fi
	#if [ "x$JOBS" = "x1" ]; then
		#JOBS=6
	#JOBS=$(grep "processor" /proc/cpuinfo|sort -u|wc -l)
	#fi
	mrproper_hvep
	build_hvep pwrsoc pwrsoc_defconfig power_bench yes || fatal "Failed to build pwrsoc!"
	build_hvep se1000 se1000_defconfig se1000_power_bench yes || fatal "Failed to build se1000!"
	mrproper_hvep
	build_hvep virt virt_defconfig virt_power_bench yes || fatal "Failed to build virt!"
	JOBS=1
	build_hvep testos testos${CONSOLE}_defconfig testos yes "${TESTOS_PROGS}" || fatal "Failed to build testos!"
	#JOBS=$(grep "processor" /proc/cpuinfo|sort -u|wc -l)
	export ARCH=arm CROSS_COMPILE=arm-none-eabi-
	build_hvep r52 r52_defconfig r52_power_bench yes|| fatal "Failed to build r52!"
	export PATH=/opt/gcc-arm-none-eabi-8-2019-q3-update/bin:$PATH
	export ARCH=armv7m CROSS_COMPILE=arm-none-eabi-
	build_hvep m4 m4_defconfig m4_power_bench yes|| fatal "Failed to build m4!"
	echo "all" > ${OUTDIR}/.hvep
elif [ "x$HVEPSUIT" == "xtestos" ]; then
	if [ "x$CONSOLE" == "x" ]; then
		echo "Missing console type!"
		usage
		exit 1
	elif [ "x$CONSOLE" == "x_dcc" ]; then
		TESTOS_PROGS="${TESTOS_PROGS} glktest"
	fi
	# Not working yet for multiple images
	JOBS=1
	mrproper_hvep
	build_hvep testos testos${CONSOLE}_defconfig testos yes "${TESTOS_PROGS}" || fatal "Failed to build testos!"
elif [ "x$HVEPSUIT" == "xtestos_split" ]; then
	if [ "x$CONSOLE" == "x" ]; then
		echo "Missing console type!"
		usage
		exit 1
	elif [ "x$CONSOLE" == "xdcc" ]; then
		${TESTOS_PROGS} = "${TESTOS_PROGS} glktest"
	fi
	mrproper_hvep
	build_hvep testos_imc testos_imc${CONSOLE}_defconfig testos_imc yes || fatal "Failed to build testos_imc!"
	# Not working yet for multiple images
	JOBS=1
	build_hvep testos_apc testos_apc${CONSOLE}_defconfig testos_apc no "${TESTOS_PROGS}" || fatal "Failed to build testos_apc!"
elif [ "x$HVEPSUIT" == "xpwrsoc" ]; then
	mrproper_hvep
	build_hvep pwrsoc pwrsoc_defconfig power_bench yes || fatal "Failed to build pwrsoc!"
elif [ "x$HVEPSUIT" == "xse1000" ]; then
	mrproper_hvep
	build_hvep se1000 se1000_defconfig se1000_power_bench yes || fatal "Failed to build se1000!"
elif [ "x$HVEPSUIT" == "xvirt" ]; then
	mrproper_hvep
	build_hvep virt virt_defconfig virt_power_bench yes || fatal "Failed to build virt!"
elif [ "x$HVEPSUIT" == "xr52" ]; then
	export ARCH=arm CROSS_COMPILE=arm-none-eabi-
	mrproper_hvep
	build_hvep r52 r52_defconfig r52_power_bench yes|| fatal "Failed to build r52!"
elif [ "x$HVEPSUIT" == "xm4" ]; then
	export PATH=/opt/gcc-arm-none-eabi-8-2019-q3-update/bin:$PATH
	export ARCH=armv7m CROSS_COMPILE=arm-none-eabi-
	mrproper_hvep
	build_hvep m4 m4_defconfig m4_power_bench yes|| fatal "Failed to build m4!"
fi
